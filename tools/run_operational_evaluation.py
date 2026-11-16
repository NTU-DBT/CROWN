#!/usr/bin/env python3
"""Controlled finite B04 output, batching, recovery and SQL-annotation cohorts."""
from __future__ import annotations
import argparse
import copy
import datetime
from fractions import Fraction
import json
import os
from pathlib import Path
import random
import sys

sys.dont_write_bytecode = True
from component_workloads import evaluate_request
from ranking_analysis import ratio
from run_measurements import Experiment, build_provenance, digest, distribution, environment, require
from verify_workloads import canonical


def save(path, value, exclusive=False):
    with path.open('x' if exclusive else 'w') as stream:
        stream.write(json.dumps(value, indent=2, ensure_ascii=False, sort_keys=True) + '\n')


def integer(value, maximum=2**64-1):
    require(type(value) is int and 0 <= value <= maximum, 'invalid finite nonnegative counter')
    return value


def changed_paths(left, right, prefix=''):
    """Diff leaves, preserving array order and empty container distinctions."""
    if isinstance(left, dict) and isinstance(right, dict):
        result = set()
        for key in left.keys() | right.keys():
            path = prefix + ('.' if prefix else '') + key
            if key not in left or key not in right:
                result.add(path)
            else:
                result.update(changed_paths(left[key], right[key], path))
        return result
    return set() if canonical(left) == canonical(right) else {prefix}


def causal_request(arm):
    value = copy.deepcopy(arm['request'])
    if 'session' in value:
        value['session'].pop('state_directory', None)
    return {'adapter': arm['adapter'], **value}


def admit_manifest(document, args):
    """Validate the finite protocol and exact declared one-factor contrasts."""
    require(type(document.get('schema_version')) is int and document['schema_version'] == 1,
            'unknown operational cohort schema')
    require(isinstance(document.get('kind'), str), 'missing operational cohort kind')
    arms = document['arms']
    require(isinstance(arms, list) and 1 <= len(arms) <= 128, 'invalid arm grant')
    ids = [arm['id'] for arm in arms]
    require(all(isinstance(name, str) and name and name.replace('-', '').replace('_', '').isalnum() for name in ids),
            'arm ids must be simple nonempty path-safe labels')
    require(len(set(ids)) == len(ids), 'duplicate arm id')
    for arm in arms:
        require(arm['adapter'] in ('set', 'rows', 'session', 'aggregate'), 'unknown native adapter')
        request = arm['request']
        require(request['command'] == 'verify', 'cohort requests must start in verify mode')
        require(request['events'] and len(request['events']) <= args.max_events, 'invalid physical input grant')
        require(len(request['events']) <= integer(request['limits']['input_events'], 1000000), 'input grant too small')
        integer(request['limits']['output_records'], 100000000)
        integer(request['limits']['output_bytes'], 64 * 1024**2)
        request['warmup_passes'], request['measured_passes'] = args.warmups, 1
        if arm['adapter'] == 'session':
            require(request['session']['state_directory'] == '__NEW_STATE_DIRECTORY__', 'state path must be a fresh-path placeholder')
            for offset in request['session'].get('recover_after', []):
                require(0 < offset < len(request['events']), 'recovery needs a subsequent physical update')
        require(len(canonical(request).encode()) <= 64 * 1024**2, 'component request exceeds native byte grant')
    by_id = {arm['id']: arm for arm in arms}
    comparisons = document['comparisons']
    require(isinstance(comparisons, list) and comparisons, 'empty operational contrasts')
    require(len({item['id'] for item in comparisons}) == len(comparisons), 'duplicate comparison id')
    for item in comparisons:
        require(item['axis'] in ('output', 'updates', 'recovery', 'sql_semantics'), 'unsupported operational axis')
        require(item['baseline'] in by_id and item['variant'] in by_id and item['baseline'] != item['variant'], 'unknown comparison arm')
        left, right = by_id[item['baseline']], by_id[item['variant']]
        actual = changed_paths(causal_request(left), causal_request(right))
        declared = item['changed_paths']
        require(declared and len(set(declared)) == len(declared) and actual == set(declared),
                item['id'] + ': actual request changes differ from declared one-factor paths')
        if item['axis'] == 'updates':
            require(actual in ({'session.transport_batch_size'}, {'native.transaction_batch_size'}), 'updates contrast changes multiple controls')
        elif item['axis'] == 'recovery':
            require(actual in ({'session.durability'}, {'session.checkpoint_interval'}, {'session.recover_after'}), 'recovery contrast changes multiple controls')
        elif item['axis'] == 'output':
            require(actual in ({'session.output_action'}, {'native.mode', 'session.output_action'},
                               {'session.consumer_delay_us'}, {'output'}), 'output contrast changes multiple controls')
        else:
            require(actual <= {'adapter', 'program.sql', 'output', 'native.mode', 'native.aggregate_source_only'}, 'SQL semantics contrast changes unrelated runtime controls')
        require(left['request']['events'] == right['request']['events'] and
                left['request']['program']['catalog'] == right['request']['program']['catalog'], 'contrasts must preserve physical inputs/catalog')
        require(isinstance(item['unit'], str) and item['unit'], 'missing explicit contrast unit')
    return by_id


def observation_key(actual, output):
    """Only row collections are unordered; tuple cells and output order remain exact."""
    if output == 'cardinality':
        return canonical(actual)
    if output in ('delta_and_snapshot', 'none'):
        keys = ('rows', 'delta') if output == 'delta_and_snapshot' else ('rows',)
        require(isinstance(actual, dict) and set(actual) == set(keys), 'wrong set observation shape')
        return {key: sorted(canonical(row) for row in actual[key]) for key in keys}
    require(output in ('compressed_bag', 'groups_full', 'groups_replacements') and isinstance(actual, list),
            'wrong compressed/group observation shape')
    return sorted(canonical(row) for row in actual)


def wanted(frame, output):
    if output == 'cardinality':
        return frame['cardinality']
    if output == 'delta_and_snapshot':
        return {'rows': frame['rows'], 'delta': frame['delta']}
    if output == 'none':
        return {'rows': frame['rows']}
    return frame[{'compressed_bag': 'bag', 'groups_full': 'groups', 'groups_replacements': 'replacements'}[output]]


def plan_identity(report):
    return {key: report[key] for key in ('implementation', 'source_sha256', 'physical_sha256', 'binding_sha256',
                                        'tree', 'physical_options', 'sql_semantics', 'output') if key in report}


def count_signature(value):
    """Compare genuine output/progress obligations without owner memory or clocks."""
    keys = ('output_records', 'internal_delta_records', 'serialized_bytes', 'accepted_progress')
    result = {key: value[key] for key in keys if key in value}
    for field in ('epochs', 'transactions', 'batches'):
        if field in value:
            result[field] = [{key: row[key] for key in (
                'sequence', 'physical_input_begin', 'physical_input_end', 'observed', 'delta_records',
                'snapshot_records', 'output_records', 'cardinality', 'source_replacements', 'source_changed',
                'transport_events', 'checkpointed', 'reconstructed', 'replay_output_rows_consumed') if key in row}
                for row in value[field]]
    return result


def check_report(report, arm, request, oracle, verify, reference=None):
    """Check actual observations, physical/transaction schedules and public lifecycle results."""
    expected = {'set': 'native_unweighted_set', 'rows': 'native_sql_rows', 'session': 'native_query_session',
                'aggregate': 'native_w03_count_source' if request['native'].get('aggregate_source_only') else 'native_sql_aggregate'}
    require(report['implementation'] == expected[arm['adapter']] and report['command'] == request['command'] and
            report['case_id'] == request['case_id'] and report['query_family'] == request['query_family'] and
            report['output'] == request['output'], 'adapter identity/request differs')
    fields = {'set': ('physical_sha256', 'source_sha256'), 'rows': ('source_sha256', 'tree', 'sql_semantics'),
              'session': ('physical_sha256',), 'aggregate': ('binding_sha256', 'tree')}
    require(all(key in report for key in (*fields[arm['adapter']], 'physical_options')), 'missing actual source/tree/backend metadata')
    expected_backend = (request['native'].get('physical_options', {}).get('indexed_storage') or {}).get('algorithm', 'reference_ordered_v1')
    actual_backend = (report['physical_options'].get('indexed_storage') or {}).get('algorithm', 'reference_ordered_v1')
    require(actual_backend == expected_backend, 'actual selected storage backend differs')
    for key in ('read_request_ns', 'shared_program_ns'):
        require(report[key] is None if verify else type(report[key]) is int and report[key] >= 0, 'wrong shared verify/measure clock')
    if reference:
        require(plan_identity(report) == reference['identity'], 'measured source/tree/backend differs from preflight')
    frames = oracle['epochs']; size = len(request['events'])
    require(len(frames) == size and [row['physical_input_end'] for row in frames] == list(range(1, size+1)), 'oracle physical horizon differs')
    passes = report['passes']; require(len(passes) == request['warmup_passes']+1, 'wrong fresh-owner pass count')
    checked = 0
    for index, value in enumerate(passes):
        require(value['warmup'] is (index < request['warmup_passes']), 'wrong retained warmup marker')
        for key in ('initialize_ns', 'loop_wall_ns', 'teardown_ns'):
            require(value[key] is None if verify else type(value[key]) is int and value[key] >= 0, 'wrong verify/measure clock')
        epochs = value['epochs']
        if arm['adapter'] == 'rows':
            batch = request['native'].get('transaction_batch_size', 1)
            interval = request['native'].get('observation_interval', 1)
            ends = [end for end in range(batch, size+batch, batch) if end < size] + [size]
            transactions = value['transactions']
            require(len(transactions) == len(ends), 'wrong atomic transaction count')
            begin = 1
            for sequence, (transaction, end) in enumerate(zip(transactions, ends, strict=True), 1):
                require(transaction['sequence'] == sequence and transaction['physical_input_begin'] == begin and
                        transaction['physical_input_end'] == end and transaction['source_replacements'] == end-begin+1,
                        'atomic transaction lost/reordered physical inputs')
                require(transaction['observed'] is (end % interval == 0 or end == size), 'wrong atomic observation marker')
                begin = end+1
            expected_ends = [end for end in ends if end % interval == 0 or end == size]
        else:
            expected_ends = list(range(1, size+1))
        actual_ends = [row.get('physical_input_end', row['sequence']) for row in epochs]
        require(actual_ends == expected_ends, 'wrong physical observation horizon')
        interval = request['native'].get('observation_interval', 1) if arm['adapter'] == 'set' else 1
        expected_records = 0
        for epoch, end in zip(epochs, expected_ends, strict=True):
            frame = frames[end-1]
            observed = end % interval == 0 or end == size
            if arm['adapter'] == 'set':
                require(epoch['sequence'] == end and epoch['observed'] is observed, 'set changed physical commit/observation schedule')
            if not verify or not observed:
                require(epoch['actual'] is None, 'unobserved/measure result capture must be null')
            else:
                require(observation_key(epoch['actual'], request['output']) == observation_key(wanted(frame, request['output']), request['output']),
                        arm['id'] + ': actual observation differs from exact SQL oracle at input ' + str(end))
                checked += 1
            if arm['adapter'] in ('set', 'session'):
                delta_records = 0 if request['native'].get('mode') == 'maintenance' else len(frame['delta'])
                require(epoch['delta_records'] == delta_records, 'signed-output counter differs from independent oracle')
                if arm['adapter'] == 'set':
                    snapshots = frame['cardinality'] if observed and (request['output'] == 'delta_and_snapshot' or request['native']['mode'] == 'maintenance') else 0
                    require(epoch['snapshot_records'] == snapshots, 'set snapshot counter differs')
                    expected_records += (1 if request['output'] == 'cardinality' else delta_records+snapshots) if observed else 0
                else:
                    require(epoch['snapshot_records'] == (None if request['output'] == 'none' else frame['cardinality']), 'session snapshot counter differs')
                    expected_records += delta_records+(0 if request['output'] == 'none' else frame['cardinality'])
            else:
                emitted = len(wanted(frame, request['output']))
                require(epoch['output_records'] == emitted, 'compressed/group output counter differs')
                expected_records += emitted
        require(value['output_records'] == expected_records, 'pass output count differs from independent observation obligations')
        if arm['adapter'] == 'session':
            control = request['session']; batch = control['transport_batch_size']
            require(value['accepted_progress']['sequence'] == size and [row['sequence'] for row in epochs] == list(range(1, size+1)),
                    'transport batching changed per-physical commitment')
            batches = value['batches']; ends = [min(begin+batch, size) for begin in range(0, size, batch)]
            require([row['physical_input_end'] for row in batches] == ends and sum(row['transport_events'] for row in batches) == size,
                    'transport batch lost physical input')
            checkpoint = control['checkpoint_interval']
            for row, end in zip(batches, ends, strict=True):
                require(row['checkpointed'] is (checkpoint > 0 and (end % checkpoint == 0 or end == size)) and
                        row['reconstructed'] is (end in control['recover_after']), 'checkpoint/restart control was skipped')
            if control['durability'] == 'wal':
                state = value['durable_state']; root_path = Path(state['root_path'])
                require(root_path.is_relative_to(Path(control['state_directory'])) and root_path.is_file(), 'actual WAL root missing/outside fresh state')
                if control['output_action'] == 'durable':
                    require(state['verified_sink_sequence'] == size and Path(state['sink_path']).is_file(), 'durable local delivery prefix missing')
            if control['output_action'] == 'serialize' and any(frame['delta'] for frame in frames):
                require(value['serialized_bytes'] > 0, 'serialization was replaced by discard')
        if reference:
            require(count_signature(value) == reference['counts'], 'measured output/progress obligations differ from verified pass')
    return {'identity': plan_identity(report), 'counts': count_signature(passes[-1]), 'checked_prefixes': checked}


def cross_arm_checks(comparisons, arms, gates):
    """Freeze identical selected plans and common endpoints for applicable contrasts."""
    for item in comparisons:
        left, right = arms[item['baseline']], arms[item['variant']]
        if left['adapter'] == right['adapter'] and left['request']['program'] == right['request']['program']:
            for field in ('source_sha256', 'physical_sha256', 'binding_sha256', 'tree', 'physical_options'):
                a, b = gates[left['id']]['identity'].get(field), gates[right['id']]['identity'].get(field)
                require(a == b, item['id'] + ': selected source/tree/backend differs')
        if left['adapter'] == right['adapter'] == 'rows':
            require([row['physical_input_end'] for row in gates[left['id']]['counts']['epochs']] ==
                    [row['physical_input_end'] for row in gates[right['id']]['counts']['epochs']], 'single/net observation boundaries differ')


def stage_samples(report):
    """Retain actual stage units; nested output/wait samples are not summed twice."""
    result = {}
    for value in report['passes']:
        if value['warmup']:
            continue
        for key in ('initialize_ns', 'loop_wall_ns', 'teardown_ns'):
            result.setdefault('pass.'+key, []).append(integer(value[key]))
        for field in ('transactions', 'batches', 'epochs'):
            for row in value.get(field, []):
                for key, sample in row.items():
                    if key.endswith('_ns') and sample is not None:
                        result.setdefault(field+'.'+key, []).append(integer(sample))
                        phase = row.get('phase')
                        if field == 'transactions':
                            phase = row['first_input_phase'] if row['first_input_phase'] == row['last_input_phase'] else 'mixed_phases'
                        if phase is not None:
                            result.setdefault(field+'.phase['+phase+'].'+key, []).append(sample)
    return result


def summarize(arm, reports, commands):
    stages = {}; final_memory = []; recovery_memory = []; owner_peaks = []; work = []; source_work = []
    for report in reports:
        for key, values in stage_samples(report).items():
            stages.setdefault(key, []).extend(values)
        for value in report['passes']:
            if value['warmup']:
                continue
            final_memory.append(value['native_memory_before_teardown'])
            if 'sampled_owner_peak_max_requested_bytes' in value:
                owner_peaks.append(integer(value['sampled_owner_peak_max_requested_bytes']))
            for transaction in value.get('transactions', []):
                if 'native_work' in transaction:
                    work.append(integer(transaction['native_work']))
                if 'source_work' in transaction:
                    source_work.append(transaction['source_work'])
            for batch in value.get('batches', []):
                for key in ('native_memory_before_recovery', 'native_memory_after_recovery'):
                    if batch.get(key) is not None:
                        recovery_memory.append({'physical_input_end': batch['physical_input_end'], 'reconstructed': batch['reconstructed'], 'sample': key, 'memory': batch[key]})
    inputs = len(arm['request']['events']); loops = stages['pass.loop_wall_ns']
    return {'arm': arm['id'], 'adapter': arm['adapter'], 'measured_invocations': len(reports), 'physical_inputs_per_pass': inputs,
            'physical_inputs_by_phase': {phase: sum(event.get('phase', 'updates') == phase for event in arm['request']['events'])
                                         for phase in sorted({event.get('phase', 'updates') for event in arm['request']['events']})},
            'loop_ns_per_physical_input': ratio(Fraction(sum(loops), len(loops)*inputs)),
            'stage_latency_ns': {key: distribution(values) for key, values in sorted(stages.items())},
            'shared_program_ns_per_invocation': distribution([integer(report['shared_program_ns']) for report in reports]),
            'request_read_ns_per_invocation': distribution([integer(report['read_request_ns']) for report in reports]),
            'native_work_per_transaction': distribution(work) if work else None,
            'source_work_totals': {key: sum(integer(row[key]) for row in source_work) for key in source_work[0]} if source_work else None,
            'native_memory_final_owner_before_teardown': final_memory, 'native_memory_around_recovery': recovery_memory,
            'sampled_owner_peak_max_requested_bytes': owner_peaks or None,
            'process_maxrss_KiB': distribution([integer(command['process_maxrss_KiB']) for command in commands]),
            'output_counts': [count_signature(report['passes'][-1]) for report in reports],
            'clock_scope': 'loop includes actual source preparation/consolidation/output/recovery and adapter per-event reporting; nested output/consumer-wait timers overlap; process wall/RSS also include compiler, all warmups, encoding and teardown',
            'account_scope': 'query-account requested bytes for explicitly sampled owners, excludes caller/compiler/report memory; final owner peak is not a whole-pass peak across destroyed owners',
            'units': 'physical source inputs, source-replacement transactions, transport batches, observations and process invocations remain distinct; bag multiplicities/groups are not set-tuple counts'}


def run(args):
    source, build, output = args.source.resolve(), args.build_dir.resolve(), args.output.resolve()
    require(sys.platform.startswith('linux') and hasattr(os, 'wait4'), 'controlled runner requires Linux wait4')
    require(1 <= args.repetitions <= 30 and 0 <= args.warmups <= 5 and 1 <= args.max_events <= 1000000, 'invalid finite trial grant')
    require(1 <= args.command_timeout <= 3600 and 1 <= args.max_total_bytes <= 4*1024**3, 'invalid process/output grant')
    require(args.cpu is not None or args.preflight_only, 'timing requires explicit CPU affinity')
    require(not output.exists(), 'operational output directory must be new')
    if args.cpu is not None:
        require(args.cpu in os.sched_getaffinity(0), 'requested CPU outside allowed affinity')
    require(args.cohorts.stat().st_size <= 64*1024**2, 'cohort manifest exceeds 64MiB')
    document = json.loads(args.cohorts.read_text()); arms = admit_manifest(document, args)
    binaries = {name: getattr(args, name+'_adapter').resolve() for name in ('set', 'rows', 'session', 'aggregate')}
    provenance = build_provenance(source, build, args.crown.resolve(), args.collector.resolve(), list(binaries.values()))
    harness = ['tools/run_operational_evaluation.py', 'tools/component_workloads.py', 'tools/ranking_analysis.py',
               'schemas/component-runtime-request-v1.schema.json']
    for name in harness:
        provenance['harness_sources'][name] = digest(source/name)
    output.mkdir(parents=True, exist_ok=False)
    args._created_output = True
    experiment = Experiment(output, args.cpu, args.command_timeout, args.max_total_bytes)
    packet = {'schema_version': 1, 'kind': 'b04_controlled_operational', 'status': 'running',
              'started_utc': datetime.datetime.now(datetime.timezone.utc).isoformat(), 'manifest_sha256': digest(args.cohorts),
              'environment': environment(), 'build': provenance, 'configuration': {key: str(value) if isinstance(value, Path) else value for key, value in vars(args).items() if not key.startswith('_')},
              'cohorts': document, 'verification': [], 'service_verification': [], 'runs': [], 'summaries': [], 'comparisons': [], 'correctness_gate': 'pending', 'B04_accepted': False,
              'limits': ['Finite Output/Updates/Recovery/SQL-semantics cohorts, not all ten-axis B04 acceptance.',
                         'One measured fresh-owner pass and identical retained/excluded warmups per fresh process invocation; shared setup paid once per invocation.',
                         'Synthetic consumer delay is a declared service experiment, not network backpressure or queue-saturation proof.',
                         'Clean-owner reconstruction is not process-crash/power-loss recovery; requested account and process RSS have different scopes.',
                         'SQL semantics may change answers, output units and normalized structure; no pure dispatch or annotation-causality claim.',
                         'Raw stdout/stderr bytes are bounded after child exit by Experiment; durable state files are outside that output grant.']}
    checkpoint = lambda: save(output/'experiment.json', packet)
    checkpoint(); save(output/'frozen-cohorts.json', document, True)
    packet['frozen_cohorts_sha256'] = digest(output/'frozen-cohorts.json')
    gates, oracles, requests = {}, {}, {}
    for identifier, arm in arms.items():
        request = copy.deepcopy(arm['request'])
        if arm['adapter'] == 'session':
            request['session']['state_directory'] = str(output/(identifier+'-verify.state'))
        path = output/(identifier+'.verify.request.json'); save(path, request, True)
        oracle = evaluate_request(request, arm['oracle']); oracles[identifier] = oracle
        report, command = experiment.invoke('preflight:'+identifier, [binaries[arm['adapter']], path])
        gate = check_report(report, arm, request, oracle, True); gates[identifier] = gate
        requests[identifier] = {'request': path.name, 'sha256': digest(path)}
        packet['verification'].append({'arm': identifier, 'gate': gate, 'request': requests[identifier], **command}); checkpoint()
    service_controls = set()
    for identifier, arm in arms.items():
        if arm['adapter'] != 'session' or arm['request']['output'] != 'none' or arm['request']['session']['output_action'] == 'maintenance':
            continue
        control_key = canonical(causal_request(arm))
        if control_key in service_controls:
            continue
        service_controls.add(control_key)
        request = copy.deepcopy(arm['request']); request['output'] = 'delta_and_snapshot'
        require(changed_paths(causal_request(arm), causal_request({**arm, 'request': request})) == {'output'}, 'supplemental service control changed its runtime')
        request['session']['state_directory'] = str(output/(identifier+'-signed-verify.state'))
        path = output/(identifier+'.signed-verify.request.json'); save(path, request, True)
        report, command = experiment.invoke('preflight:service:'+identifier, [binaries['session'], path])
        gate = check_report(report, arm, request, oracles[identifier], True)
        require({key: value for key, value in gate['identity'].items() if key != 'output'} ==
                {key: value for key, value in gates[identifier]['identity'].items() if key != 'output'}, 'signed service control changed its selected plan')
        packet['service_verification'].append({'derived_from_arm': identifier, 'changed_paths': ['output'],
            'scope': 'supplemental signed delivery plus snapshot correctness only; not a measured none-output obligation',
            'request': path.name, 'request_sha256': digest(path), 'gate': gate, **command}); checkpoint()
    cross_arm_checks(document['comparisons'], arms, gates)
    packet['correctness_gate'] = 'all_preflights_pass'; checkpoint()
    reports = {identifier: [] for identifier in arms}; commands = {identifier: [] for identifier in arms}
    order = list(arms); random.Random(args.schedule_seed).shuffle(order)
    if not args.preflight_only:
        for repetition in range(args.repetitions):
            for identifier in order[repetition % len(order):]+order[:repetition % len(order)]:
                arm = arms[identifier]
                require(digest(args.cohorts) == packet['manifest_sha256'] and digest(output/requests[identifier]['request']) == requests[identifier]['sha256'], 'frozen cohort/preflight request changed')
                request = copy.deepcopy(arm['request']); request['command'] = 'measure'
                if arm['adapter'] == 'session':
                    request['session']['state_directory'] = str(output/(identifier+'-measure-'+str(repetition)+'.state'))
                path = output/(identifier+'.measure-'+str(repetition)+'.request.json'); save(path, request, True)
                report, command = experiment.invoke('measure:'+identifier+':'+str(repetition), [binaries[arm['adapter']], path])
                check_report(report, arm, request, oracles[identifier], False, gates[identifier])
                reports[identifier].append(report); commands[identifier].append(command)
                packet['runs'].append({'arm': identifier, 'repetition': repetition, 'request': path.name,
                                       'request_sha256': digest(path), 'preflight_stdout_sha256': packet['verification'][list(arms).index(identifier)]['stdout_sha256'], **command}); checkpoint()
        packet['summaries'] = [summarize(arms[identifier], reports[identifier], commands[identifier]) for identifier in arms]
        summaries = {item['arm']: item for item in packet['summaries']}
        for item in document['comparisons']:
            baseline, variant = summaries[item['baseline']], summaries[item['variant']]
            a, b = baseline['loop_ns_per_physical_input'], variant['loop_ns_per_physical_input']
            a, b = Fraction(int(a['numerator']), int(a['denominator'])), Fraction(int(b['numerator']), int(b['denominator']))
            packet['comparisons'].append({**item, 'baseline_ns_per_physical_input': ratio(a), 'variant_ns_per_physical_input': ratio(b),
                                          'variant_over_baseline': ratio(b/a) if a else None,
                                          'baseline_runtime_identity': gates[item['baseline']]['identity'],
                                          'variant_runtime_identity': gates[item['variant']]['identity'],
                                          'scope': 'finite matched physical inputs and declared factor; service/output obligations explicit, not a universal speedup or pure dispatch cause'})
    require(digest(args.cohorts) == packet['manifest_sha256'] and digest(output/'frozen-cohorts.json') == packet['frozen_cohorts_sha256'], 'frozen manifest changed during experiment')
    for path, expected in {**provenance['files'], **provenance['compiled_dependencies']}.items():
        require(digest(Path(path)) == expected, 'compiled input changed during experiment')
    for path, expected in provenance['harness_sources'].items():
        require(digest(source/path) == expected, 'harness source changed during experiment')
    for tool in experiment.tools.values():
        require(digest(Path(tool['path'])) == tool['sha256'], 'measurement launcher changed during experiment')
    packet.update(status='preflight_complete' if args.preflight_only else 'complete_conditional_operational', finished_utc=datetime.datetime.now(datetime.timezone.utc).isoformat(),
                  commands_sha256=digest(output/'commands.json'), frozen_inputs_unchanged=True)
    checkpoint()
    print('B04 operational packet: '+str(len(arms))+' arms, '+str(len(packet['verification'])+len(packet['service_verification']))+' preflights, '+str(len(packet['runs']))+' measured invocations: '+str(output))


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    for name in ('source', 'build-dir', 'crown', 'collector', 'set-adapter', 'rows-adapter', 'session-adapter', 'aggregate-adapter', 'cohorts', 'output'):
        parser.add_argument('--'+name, type=Path, required=True)
    parser.add_argument('--warmups', type=int, default=1); parser.add_argument('--repetitions', type=int, default=3)
    parser.add_argument('--cpu', type=int); parser.add_argument('--schedule-seed', type=int, default=20261115)
    parser.add_argument('--command-timeout', type=int, default=300); parser.add_argument('--max-total-bytes', type=int, default=1024**3)
    parser.add_argument('--max-events', type=int, default=65536); parser.add_argument('--preflight-only', action='store_true')
    args = parser.parse_args()
    args._created_output = False
    try:
        run(args)
    except Exception as error:
        path = args.output.resolve()/'experiment.json'
        if args._created_output and path.is_file():
            packet = json.loads(path.read_text()); packet.update(status='failed', failure=str(error)); save(path, packet)
        print('B04 operational experiment failed: '+str(error), file=sys.stderr)
        return 1
    return 0


if __name__ == '__main__':
    raise SystemExit(main())
