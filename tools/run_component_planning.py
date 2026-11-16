#!/usr/bin/env python3
"""Controlled source-bound B04 planning/structure dependencies; all ten axes remain open."""
from __future__ import annotations
import argparse
import collections
import datetime
from fractions import Fraction
import hashlib
import json
import os
from pathlib import Path
import sys

sys.dont_write_bytecode = True
from component_analysis import exact_ratio, freeze_choices
from generate_ranking_evaluation import verify as verify_split
from ranking_analysis import error_summary, ordering_quality, ratio, regret
from run_measurements import Experiment, build_provenance, digest, distribution, environment, indexed_options, require
from verify_workloads import canonical


def save(path, value, exclusive=False):
    with path.open('x' if exclusive else 'w') as stream:
        stream.write(json.dumps(value, sort_keys=True, ensure_ascii=False, indent=2) + '\n')


def training_demand(catalog, events):
    """Forecast the TRAIN physical input mix, including explicit zero strata."""
    tables = {table['name']: index for index, table in enumerate(catalog['catalog']['tables'])}
    counts = collections.Counter()
    for event in events:
        require(event['table'] in tables and event['operation'] in ['insert', 'delete'], 'unknown training stratum')
        counts[tables[event['table']], 'insert' if event['operation'] == 'insert' else 'erase'] += 1
    require(events, 'empty training demand')
    return [{'table': index, 'operation': operation, 'inputs': counts[index, operation]}
            for index in range(len(tables)) for operation in ['insert', 'erase']]


def retained(exported):
    """Keep every family/key/control origin; JSON supplies no proof authority."""
    rows = []
    proof = exported['original_certificate']
    for family in exported['families']:
        for candidate in family['candidates']:
            require(candidate['height'] == exported['proved_height'], 'minimum family contains taller candidate')
            rows.append({'origin': {'family': family['id'], 'structural_key': candidate['structural_key'],
                                   'provenance': candidate['provenance']}, **candidate})
    for index, candidate in enumerate(exported['ordinary']['candidates']):
        require(candidate['height'] >= exported['proved_height'], 'ordinary upper below original minimum')
        rows.append({'origin': {'ordinary_index': index, 'root_occurrence': candidate['root_occurrence']}, **candidate})
    for row in rows:
        artifact = row['artifact']
        require(artifact['height_certificate'] == proof, 'producer replaced the original certificate')
        require(row['physical_sha256'] == artifact['physical']['binding']['physical_sha256'], 'producer physical binding differs')
        require(row['height'] == artifact['physical']['verification']['native_height'], 'producer actual height differs')
    return rows


def retained_identity(exported):
    """Compare complete artifacts/proofs/family identities, excluding measured observations."""
    return {'source': exported['source_sha256'], 'catalog': exported['catalog_sha256'],
            'training': exported['training_sha256'], 'calibration': exported['calibration_sha256'],
            'proved_height': exported['proved_height'], 'original_certificate': exported['original_certificate'],
            'families': [{'id': family['id'], 'family': family['progress']['family'],
                          'exhaustion_scope': family['progress']['exhaustion_scope'],
                          'family_exhausted': family['progress']['family_exhausted'],
                          'candidates': family['candidates']} for family in exported['families']],
            'ordinary_candidates': exported['ordinary']['candidates'],
            'ordinary_exhausted': exported['ordinary']['ordinary_exhausted'],
            'ordinary_rejections': exported['ordinary']['rejections']}


def check_report(report, request, artifact, artifact_path, trace, backend):
    require(report['request'] == request and report['backend'] == backend, 'collector request/backend differs')
    require(report['physical_sha256'] == artifact['physical']['binding']['physical_sha256'] and
            report['artifact_sha256'] == digest(artifact_path) and report['input_sha256'] == digest(trace['input']),
            'collector artifact/input binding differs')
    require(report['output_mode'] == report['runtime_mode'] == 'maintenance' and report['output_rows'] == 0,
            'collector changed maintenance-only demand')
    require(report['records'] == len(trace['events']) and report['sequence'] == trace['events'][-1]['sequence'] and
            report['source_positions'] == trace['positions'], 'collector horizon/source progress differs')
    if artifact['schema_version'] == 3:
        original = artifact['height_certificate']['minimum_height']
        actual = artifact['physical']['verification']['native_height']
        require(report['experimental_height'] == {'status': 'checked_upper_only', 'original_minimum_height': original,
                'actual_native_height': actual, 'height_gap': actual - original}, 'collector upper metadata differs')
    else:
        require('experimental_height' not in report, 'minimum artifact mislabelled experimental')


def analyze(exported, frozen, samples, traces, repetitions):
    """C03 has ns predictions; C02 remains structural ordering and measured regret."""
    result = []
    families = {family['id']: family for family in exported['families']}
    for choice_family in frozen['families']:
        family = families[choice_family['id']]
        candidates = {row['structural_key']: row['physical_sha256'] for row in family['candidates']}
        statistics = {row['variant']: row for row in family['statistics']}
        for trace in traces:
            actual = {}
            for key, physical in candidates.items():
                values = samples[physical, trace['id']]
                require(len(values) == repetitions, 'missing measured candidate repetition')
                actual[key] = sum((value['native_ns_per_input'] for value in values), Fraction()) / repetitions
            for variant in choice_family['statistics']:
                for policy in ['height', 'weighted_depth', 'event_cost']:
                    choice = variant[policy]
                    row = {'trace': trace['id'], 'family': family['id'], 'statistics': variant['variant'],
                           'policy': policy, 'choice': choice, 'actual_unit': 'native_prepare_commit_epoch_release_ns_per_input'}
                    selected = choice['selected_key']
                    eligible = set(actual) - set(choice.get('known_asof_memory_exclusions', []))
                    row['runtime_regret'] = regret(actual, selected, eligible) if selected is not None else None
                    if policy == 'event_cost':
                        predicted = {cell['structural_key']: exact_ratio(cell['predicted_total_ns']) / frozen['forecast_inputs']
                                     for cell in choice['observations'] if cell['issues'] == 0 and cell['predicted_total_ns'] is not None and
                                     cell['structural_key'] not in choice['unknown_scores'] + choice['known_asof_memory_exclusions']}
                        row['forecast_inputs_from_train'] = frozen['forecast_inputs']
                        row['predictions'] = [{'key': key, 'predicted_ns_per_training_mix_input': ratio(value),
                                               'actual_ns_per_evaluation_input': ratio(actual[key])}
                                              for key, value in predicted.items()]
                        row['prediction_errors'] = error_summary(list(predicted.values()), [actual[key] for key in predicted]) if predicted else None
                        row['calibration_fit'] = frozen['calibration_fit']
                    else:
                        scores = {cell['structural_key']: exact_ratio({'numerator': cell['numerator'], 'denominator': cell['denominator']})
                                  for cell in statistics[variant['variant']][policy].get('scores', [])}
                        row['score_unit'] = 'native_height' if policy == 'height' else 'committed_input_weighted_native_depth'
                        row['structural_score_ordering'] = ordering_quality(scores, {key: actual[key] for key in scores}) if scores else None
                        row['nanosecond_prediction_errors'] = None
                        row['qualification'] = 'C02 proxies are not nanoseconds; no affine substitute for C03'
                    result.append(row)
    return result


def run(args):
    source, build = args.source.resolve(), args.build_dir.resolve()
    pack = (args.pack or source / 'benchmarks/ranking').resolve()
    crown, collector, exporter = args.crown.resolve(), args.collector.resolve(), args.exporter.resolve()
    require(sys.platform.startswith('linux') and hasattr(os, 'wait4'), 'controlled runner requires Linux wait4')
    require(1 <= args.repetitions <= 30 and 0 <= args.warmups <= 5 and 1 <= args.candidates <= 32, 'invalid repetition/candidate grant')
    require(1 <= args.command_timeout <= 3600 and 1 <= args.max_total_bytes <= 4 * 1024**3, 'invalid process/output grant')
    require(0 <= args.search_work <= 100000000 and 0 <= args.meta_work <= 100000000, 'invalid planner work grant')
    if args.cpu is not None:
        require(args.cpu in os.sched_getaffinity(0), 'requested CPU is outside allowed affinity')
    manifest, validation = verify_split(source, pack)
    queries = {query['id']: query for query in manifest['queries']}
    ids, backends = args.query or list(queries), args.backend or ['reference_ordered_v1', 'indexed_chained_v1']
    require(ids and len(ids) == len(set(ids)) and set(ids) <= set(queries), 'unknown/duplicate query')
    require(len(backends) == len(set(backends)), 'duplicate backend')
    provenance = build_provenance(source, build, crown, collector, [exporter])
    for name in ['tools/run_component_planning.py', 'tools/component_analysis.py', 'tools/ranking_analysis.py',
                 'tools/generate_ranking_evaluation.py', 'schemas/compiled-experimental-upper-v3.schema.json']:
        provenance['harness_sources'][name] = digest(source / name)
    lock = source / 'dependencies.lock.json'
    provenance['dependency_lock'] = {'path': str(lock), 'sha256': digest(lock), 'contents': json.loads(lock.read_text())}
    output = args.output.resolve()
    output.mkdir(parents=True, exist_ok=False)
    experiment = Experiment(output, args.cpu, args.command_timeout, args.max_total_bytes)
    packet = {'schema_version': 1, 'kind': 'b04_controlled_planning_dependencies', 'status': 'running',
              'started_utc': datetime.datetime.now(datetime.timezone.utc).isoformat(), 'manifest_sha256': digest(pack / 'manifest.json'),
              'split_validation': validation, 'split_contract': manifest['split_contract'], 'environment': environment(), 'build': provenance,
              'configuration': {**vars(args), 'output_mode': 'maintenance', 'codec': 'none', 'sink': 'discard',
                                'observation': 'off', 'workload_counters': True, 'query_ids': ids, 'backends': backends},
              'groups': [], 'verification': [], 'runs': [], 'analysis': [], 'summaries': [], 'correctness_gate': 'pending',
              'B04_accepted': False, 'limits': ['Only planning/structure/storage/search/statistics dependencies; all ten B04 axes remain open.',
              'No C05 maintenance_cost enablement, global cost optimum, confidence or fixed speedup claim.',
              'Training mix defines forecast demand; workload shifts remain held out. Query families are shared across disjoint traces.',
              'Preliminary native calibration is unqualified preparation only; final single pooled calibration is shared by every family/statistics variant.',
              'Volatile exact set maintenance only, full counters on, optional observations off; no output/annotation/WAL/sink prediction.',
              'Warmups retained/excluded; caches, clock noise and frequency are observed rather than controlled.']}
    packet['configuration'] = {key: str(value) if isinstance(value, Path) else value for key, value in packet['configuration'].items()}
    groups = []
    def checkpoint(): save(output / 'experiment.json', packet)
    checkpoint()
    try:
        for identifier in ids:
            query = queries[identifier]
            sql, catalog_path = pack / query['sql']['path'], pack / query['catalog']['path']
            catalog, _ = experiment.invoke('canonical_catalog', [crown, 'canonicalize-catalog', catalog_path])
            catalog_sha = hashlib.sha256(canonical(catalog).encode()).hexdigest()
            traces = []
            for case in [row for row in manifest['traces'] if row['query'] == identifier]:
                events = [json.loads(line) for line in (pack / case['events']['path']).read_text().splitlines()]
                require(0 < len(events) == case['events_count'] <= 4096, 'trace horizon outside exporter grant')
                for event in events: event['catalog_sha256'] = catalog_sha
                path = output / (case['id'].replace('/', '__') + '.input.jsonl')
                with path.open('x') as stream: stream.write(''.join(canonical(event) + '\n' for event in events))
                traces.append({**case, 'events': events, 'input': path,
                               'positions': {event['source_position']['source']: event['source_position']['offset'] for event in events}})
            training = [row for row in traces if row['role'] == 'train']
            calibration = [row for row in traces if row['role'] == 'calibration']
            require(len(training) == len(calibration) == 1 and any(row['role'] == 'evaluation' for row in traces), 'invalid physical trace split')
            for backend in backends:
                label = identifier + '-' + backend
                group = {'query': identifier, 'backend': backend, 'availability': 'preparing', 'exports': []}
                packet['groups'].append(group)
                physical = indexed_options()
                if backend == 'reference_ordered_v1': del physical['indexed_storage']; physical['schema_version'] = 1
                request = {'schema_version': 1, 'physical_options': physical, 'context': 'b04-v59:' + label + ':maintenance-off-census',
                           'input_demand': training_demand(catalog, training[0]['events']), 'candidate_limit': args.candidates,
                           'search_work': args.search_work, 'enumeration_work': args.search_work, 'meta_work': args.meta_work,
                           'calibration_plan_limit': 4, 'calibration_repetitions': 2, 'memory_limit_bytes': 256 * 1024**2,
                           'max_events': max(row['events_count'] for row in traces)}
                request_path = output / (label + '.export.request.json')
                save(request_path, request, True)
                argv = [exporter, sql, catalog_path, training[0]['input'], calibration[0]['input'], request_path]
                preliminary, command = experiment.invoke('preliminary_unqualified_component_export', argv)
                group['exports'].append({'stage': 'preliminary_unqualified_preparation', **command})
                require(preliminary['kind'] == 'b04_cold_component_planning_export' and preliminary['schema_version'] == 1 and
                        preliminary['request'] == request and preliminary['source_sha256'] == digest(sql) and
                        preliminary['catalog_sha256'] == digest(catalog_path) and preliminary['training_sha256'] == digest(training[0]['input']) and
                        preliminary['calibration_sha256'] == digest(calibration[0]['input']), 'exporter source/trace/request binding differs')
                missing = {'exact', 'residual', 'meta'} - {family['id'] for family in preliminary['families']}
                if preliminary['status'] != 'exported_conditional_data' or missing or any(not family['candidates'] for family in preliminary['families']):
                    group.update(availability='original_or_candidate_family_unavailable', raw_status=preliminary['status'],
                                 unavailable_families=sorted(missing | {family['id'] for family in preliminary['families'] if not family['candidates']}))
                    checkpoint()
                    continue
                rows = retained(preliminary)
                envelopes, plans = {}, {}
                for row in rows:
                    document = row['artifact']
                    envelope = hashlib.sha256(canonical(document).encode()).hexdigest()
                    if envelope not in envelopes:
                        path = output / (label + '-artifact-' + str(len(envelopes)) + '.json')
                        save(path, document, True)
                        envelopes[envelope] = {'path': path, 'document': document, 'preflights': {}}
                    plan = plans.setdefault(row['physical_sha256'], {'envelope': envelope, 'origins': [], 'height': row['height']})
                    plan['origins'].append(row['origin'])
                require(len(envelopes) * len(traces) + len(plans) * 3 * (args.warmups + args.repetitions) <= 10000,
                        'group command grant exceeded; no candidate/control may be silently omitted')
                for index, (envelope, artifact) in enumerate(envelopes.items()):
                    for trace in traces:
                        ask = {'schema_version': 1, 'command': 'verify', 'output_mode': 'maintenance', 'codec': 'none', 'sink': 'discard',
                               'sink_delay_us': 0, 'observation': 'off', 'workload_counters': True, 'memory_limit_bytes': 256 * 1024**2,
                               'max_events': 4096, 'max_output_calls': 1000000, 'max_encoded_bytes': 64 * 1024**2,
                               'phases': [row['phase'] for row in json.loads((pack / trace['oracle']['path']).read_text())['epochs']],
                               'label': label + ':' + str(index) + ':' + trace['id'], 'preflight_receipt_sha256': None}
                        path = output / (label + '-' + str(index) + '-' + trace['id'].split('/')[-1] + '.verify.json')
                        save(path, ask, True)
                        report, command = experiment.invoke('preflight_all_retained_envelopes_and_splits',
                            [collector, artifact['path'], trace['input'], path, pack / trace['oracle']['path'], output / 'unused-verification-sink'])
                        check_report(report, ask, artifact['document'], artifact['path'], trace, backend)
                        require(report.get('verified') is True and not (output / 'unused-verification-sink').exists(), 'preflight failed/created sink')
                        packet['verification'].append({'query': identifier, 'backend': backend, 'envelope': envelope, 'trace': trace['id'], **command})
                        artifact['preflights'][trace['id']] = {'request': ask, 'receipt': command['stdout_sha256'], 'binding': report['binding_sha256']}
                final, command = experiment.invoke('qualified_final_component_export_and_calibration', argv)
                group['exports'].append({'stage': 'final_after_all_preflights', **command})
                require(final['status'] == 'exported_conditional_data' and final['request'] == request and
                        retained_identity(final) == retained_identity(preliminary), 'retained proof/family/artifact/control identity changed after preflight')
                frozen = freeze_choices(final)
                freeze_path = output / (label + '.choices-frozen.json')
                save(freeze_path, frozen, True)
                calibration_path = output / (label + '.calibration-frozen.json')
                save(calibration_path, final['calibration'], True)
                group.update(availability='frozen_conditional_retained_family', choices_file=freeze_path.name,
                             choices_sha256=digest(freeze_path), calibration_file=calibration_path.name,
                             calibration_sha256=digest(calibration_path), physical_plans=plans,
                             artifacts=[{'envelope': key, 'path': value['path'].name, 'sha256': digest(value['path'])}
                                        for key, value in envelopes.items()],
                             ordinary_control_availability='retained_controls' if final['ordinary']['candidates'] else 'no_retained_ordinary_control',
                             envelope_count=len(envelopes), frozen_after_command=command['index'])
                groups.append({'record': group, 'exported': final, 'frozen': frozen, 'plans': plans, 'envelopes': envelopes,
                               'traces': traces, 'freeze': freeze_path, 'calibration': calibration_path, 'samples': collections.defaultdict(list)})
                checkpoint()
        packet['correctness_gate'] = 'all_available_groups_all_retained_envelopes_all_splits_verified_before_heldout_timing'
        checkpoint()
        if not args.preflight_only:
            schedule = [(group, physical, trace) for group in groups for physical in group['plans'] for trace in group['traces'] if trace['role'] == 'evaluation']
            for repetition in range(args.warmups + args.repetitions):
                ordered = sorted(schedule, key=lambda row: hashlib.sha256(f'{args.schedule_seed}:{repetition}:{row[0]["record"]["query"]}:{row[0]["record"]["backend"]}:{row[1]}:{row[2]["id"]}'.encode()).hexdigest())
                for group, physical, trace in ordered:
                    record = group['record']
                    require(digest(group['freeze']) == record['choices_sha256'] and digest(group['calibration']) == record['calibration_sha256'], 'frozen choices/calibration changed')
                    artifact = group['envelopes'][group['plans'][physical]['envelope']]
                    gate = artifact['preflights'][trace['id']]
                    ask = {**gate['request'], 'command': 'measure', 'preflight_receipt_sha256': gate['receipt']}
                    path = output / ('measurement-' + str(len(packet['runs'])) + '.request.json')
                    save(path, ask, True)
                    report, command = experiment.invoke('heldout_warmup' if repetition < args.warmups else 'heldout_measure',
                        [collector, artifact['path'], trace['input'], path, '-', output / 'unused-discard-sink'])
                    check_report(report, ask, artifact['document'], artifact['path'], trace, record['backend'])
                    require(report['kind'] == 'native_workload_measurement' and report['binding_sha256'] == gate['binding'], 'measurement differs from its preflight')
                    require(len(report['epochs']) == len(trace['events']) and all(epoch['output_rows'] == 0 and not epoch['output_calls'] for epoch in report['epochs']) and
                            report['sink']['calls'] == report['sink']['bytes'] == 0 and report['workload']['mode'] == 'counters', 'maintenance instrumentation/output scope differs')
                    require([epoch['sequence'] for epoch in report['epochs']] == [event['sequence'] for event in trace['events']] and
                            [epoch['phase'] for epoch in report['epochs']] == ask['phases'], 'measured epoch schedule differs')
                    if args.cpu is not None: require(report['environment']['actual_affinity'] == [args.cpu], 'actual affinity differs')
                    native = sum(epoch['native_prepare_commit_ns'] + epoch['epoch_release_ns'] for epoch in report['epochs'])
                    values = {'native_ns_per_input': Fraction(native, len(trace['events'])), 'native_ns_total': native,
                              'event_ns_total': sum(epoch['event_active_ns'] for epoch in report['epochs']),
                              'cumulative_peak_requested_bytes': report['memory_final']['peak_requested_bytes']}
                    warmup = repetition < args.warmups
                    packet['runs'].append({'query': record['query'], 'backend': record['backend'], 'physical_sha256': physical, 'trace': trace['id'],
                                           'warmup': warmup, 'repetition': repetition - args.warmups, 'costs': {key: ratio(value) if isinstance(value, Fraction) else value for key, value in values.items()}, **command})
                    if not warmup: group['samples'][physical, trace['id']].append(values)
                    checkpoint()
            for group in groups:
                record = group['record']
                packet['analysis'].extend({'query': record['query'], 'backend': record['backend'], **row}
                    for row in analyze(group['exported'], group['frozen'], group['samples'], [trace for trace in group['traces'] if trace['role'] == 'evaluation'], args.repetitions))
                for (physical, trace), values in group['samples'].items():
                    packet['summaries'].append({'query': record['query'], 'backend': record['backend'], 'physical_sha256': physical, 'trace': trace,
                        'measured_repetitions': len(values), 'native_ns_per_input': ratio(sum((value['native_ns_per_input'] for value in values), Fraction()) / len(values)),
                        'raw_run_distributions': {key: distribution([value[key] for value in values]) for key in ['native_ns_total', 'event_ns_total', 'cumulative_peak_requested_bytes']}})
        for path, expected in provenance['files'].items(): require(digest(Path(path)) == expected, 'compiled input changed during experiment')
        for path, expected in provenance['harness_sources'].items(): require(digest(source / path) == expected, 'harness source changed during experiment')
        packet.update(status='planning_unavailable' if not groups else 'preflight_complete_choices_frozen' if args.preflight_only else 'complete_conditional_dependencies',
                      unavailable_groups=sum(group['availability'] != 'frozen_conditional_retained_family' for group in packet['groups']),
                      completed_utc=datetime.datetime.now(datetime.timezone.utc).isoformat(), commands_sha256=digest(output / 'commands.json'))
        checkpoint()
        print(f'B04 dependency packet: {len(groups)} available query/backend groups; {len(packet["verification"])} preflights; {len(packet["runs"])} retained heldout runs; all ten axes remain open: {output}')
    except Exception as error:
        packet.update(status='failed', error=str(error))
        checkpoint()
        raise


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    for name in ['source', 'build-dir', 'crown', 'collector', 'exporter', 'output']: parser.add_argument('--' + name, type=Path, required=True)
    parser.add_argument('--pack', type=Path); parser.add_argument('--query', action='append')
    parser.add_argument('--backend', action='append', choices=['reference_ordered_v1', 'indexed_chained_v1'])
    parser.add_argument('--repetitions', type=int, default=3); parser.add_argument('--warmups', type=int, default=1)
    parser.add_argument('--candidates', type=int, default=8); parser.add_argument('--search-work', type=int, default=10000000)
    parser.add_argument('--meta-work', type=int, default=10000000); parser.add_argument('--preflight-only', action='store_true')
    parser.add_argument('--cpu', type=int); parser.add_argument('--schedule-seed', type=int, default=20261115)
    parser.add_argument('--command-timeout', type=int, default=300); parser.add_argument('--max-total-bytes', type=int, default=1024**3)
    run(parser.parse_args())


if __name__ == '__main__':
    try: main()
    except Exception as error: print('B04 dependency experiment failed: ' + str(error), file=sys.stderr); raise SystemExit(1)
