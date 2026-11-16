#!/usr/bin/env python3
"""Finite literal/P06/residual/meta search study with explicit stops and real C02 scores."""
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
from ranking_analysis import ratio
from run_measurements import Experiment, build_provenance, digest, distribution, environment, require
from verify_workloads import canonical

METHODS = ['literal_minimum', 'optimized', 'residual', 'meta', 'literal_family']


def save(path, value, exclusive=False):
    with path.open('x' if exclusive else 'w') as stream:
        stream.write(json.dumps(value, sort_keys=True, indent=2) + '\n')


def cohorts():
    """Fixed typed-CQ shapes; no hand-written implementation or fabricated height."""
    result = []
    def add(name, edges, head, aliases=False):
        variables = sorted({variable for edge in edges for variable in edge})
        catalog_edges = edges[:1] if aliases else edges
        tables = [{'name': 'r' + str(index), 'columns': [{'name': 'c' + str(column), 'type': 'int64'}
                  for column in range(len(edge))]} for index, edge in enumerate(catalog_edges)]
        document = {'schema_version': 1, 'semantics': 'set', 'catalog': {'version': 1, 'tables': tables},
                    'query': {'variables': [{'name': variable, 'type': 'int64'} for variable in variables],
                              'atoms': [{'id': 'a' + str(index), 'table': 'r0' if aliases else 'r' + str(index),
                                         'terms': [{'var': variable} for variable in edge]} for index, edge in enumerate(edges)],
                              'head': [{'var': variable, 'alias': 'out_' + variable} for variable in head]},
                    'initial': [{'table': table['name'], 'rows': []} for table in tables], 'updates': []}
        result.append({'id': name, 'size': len(edges), 'document': document,
                       'training_repetitions': list(range(1, len(tables) + 1))})
    for size in range(2, 7):
        path = [[f'x{index}', f'x{index+1}'] for index in range(size)]
        star = [['x0', f'x{index+1}'] for index in range(size)]
        add(f'full_path_{size}', path, [f'x{index}' for index in range(size + 1)])
        add(f'projected_path_{size}', path, ['x0'])
        add(f'full_star_{size}', star, [f'x{index}' for index in range(size + 1)])
        add(f'equal_scope_{size}', [['x', 'y']] * size, ['x', 'y'])
    add('tiny_c02', [['x'], ['x', 'y'], ['y']], ['x', 'y'])
    add('tiny_cycle', [['x', 'y'], ['y', 'z'], ['z', 'x']], ['x', 'y', 'z'])
    add('tiny_alias', [['x', 'y']] * 3, ['x', 'y'], True)
    return result


def request(case, method, work, proof_work):
    return {'schema_version': 1, 'command': 'verify', 'method': method, 'work_limit': work,
            'proof_work_limit': proof_work, 'record_limit': 1000000, 'cell_limit': 10000000,
            'depth_limit': 128, 'scope_limit': 4096, 'candidate_limit': 128, 'proposal_limit': 1000,
            'rank_work_limit': 20000000, 'memory_limit_bytes': 256 * 1024**2,
            'training_repetitions': case['training_repetitions']}


def score_tree(case, tree):
    """Independent declared-input native-depth arithmetic; never constructs Evidence."""
    nodes = {node['id']: node for node in tree['nodes']}
    atoms = {atom['id']: atom for atom in case['document']['query']['atoms']}
    tables = {table['name']: index for index, table in enumerate(case['document']['catalog']['tables'])}
    pending, visited, depths = [(tree['root'], 0)], set(), {}
    while pending:
        node_id, depth = pending.pop()
        require(node_id in nodes and node_id not in visited, 'invalid/repeated reported tree node')
        visited.add(node_id)
        node = nodes[node_id]
        depth += node['kind'] == 'native'
        if node['kind'] == 'native':
            require(node['occurrence'] in atoms and node['occurrence'] not in depths, 'reported native occurrence duplicated/foreign')
            depths[node['occurrence']] = depth
        pending.extend((child, depth) for child in node['children'])
    require(set(depths) == set(atoms) and len(visited) == len(nodes), 'reported tree misses source structure')
    denominator = sum(case['training_repetitions'])
    numerator = sum(case['training_repetitions'][tables[atoms[occurrence]['table']]] * depth for occurrence, depth in depths.items())
    return Fraction(numerator, denominator), max(depths.values())


def inspect(case, ask, report, source_path):
    require(report['kind'] == 'b04_finite_search_record_v1' and report['schema_version'] == 1 and
            report['request'] == ask and report['method'] == ask['method'] and report['command'] == ask['command'], 'search record protocol differs')
    require(report['source_sha256'] == digest(source_path) and report['query']['native_occurrences'] == case['size'], 'search source/dimension differs')
    if ask['command'] == 'verify':
        require(all(value is None for value in report['timings'].values()), 'verification emitted eligible phase timing')
    scores = {}
    for candidate in report['candidates']:
        require(candidate['structural_key'] not in scores, 'duplicate published structural key')
        score, height = score_tree(case, candidate['tree'])
        require(height == candidate['height'] == report['original']['height'], 'actual native height differs from original optimum')
        scores[candidate['structural_key']] = score
    scoring = report['scoring']
    if scoring['availability'] == 'actual_c02_census_scores':
        require(scoring['actual_training_events'] == scoring['denominator'] == sum(case['training_repetitions']), 'C02 census horizon differs')
        require({row['table']: row['inserts'] for row in scoring['observed_weights']} == dict(enumerate(case['training_repetitions'])) and
                all(row['erases'] == 0 for row in scoring['observed_weights']), 'C02 weights were not the declared actual inputs')
        actual = {row['structural_key']: Fraction(int(row['numerator']), int(row['denominator'])) for row in scoring['scores']}
        require(actual == scores, 'native C02 scores differ from independent tree/depth arithmetic')
        require(scoring['selected_key'] == min(scores, key=lambda key: (scores[key], key)), 'native C02 choice/tie differs')
    return scores


def outcome(report):
    if report['method'] == 'literal_minimum':
        return report['algorithm']['status']
    if report['status'] != 'reported':
        return report['status']
    if report['method'] == 'literal_family' and report['algorithm']['resource_limited']:
        return 'literal_family_cap_or_work_stop'
    if not report['candidates']:
        return 'empty_minimum_candidate_prefix'
    return 'complete_declared_scope' if report.get('upstream_and_admission_exhausted') else 'retained_candidate_prefix'


def semantic_identity(report):
    algorithm = report['algorithm'] or {}
    original = (report.get('original') or {}).get('progress', {})
    residual = algorithm.get('progress', {})
    candidate = report.get('candidate_progress') or {}
    return {'status': report['status'], 'outcome': outcome(report),
            'height': (report.get('original') or {}).get('height'),
            'original_stop': [original.get('result_kind'), original.get('stop_reason')],
            'residual_stop': [residual.get('result_kind'), residual.get('stop_reason'), residual.get('proof_status')],
            'candidate_stop': [candidate.get('stop_reason'), candidate.get('family_exhausted')],
            'literal_height': algorithm.get('height'), 'literal_complete': algorithm.get('minimum_decision_complete'),
            'reference_stop': algorithm.get('stop'),
            'meta_stops': [algorithm.get(name) for name in ['construction_stop', 'enumeration_stop', 'mapping_stop']],
            'candidates': sorted(row['reference_signature'] for row in report['candidates']),
            'combined_exhausted': report.get('upstream_and_admission_exhausted'),
            'scoring_availability': report['scoring']['availability'], 'scoring_scores': report['scoring'].get('scores'),
            'scoring_stops': [report['scoring'].get(name) for name in ['capture_stop', 'capture_reasons', 'stop', 'reasons']]}


def compare(case, records):
    """Use complete reference decisions/families only; retain every other status."""
    decisions = []
    reference = None
    for record in records:
        original = record.get('original')
        if original and 'height' in original: decisions.append(('minimum', original['height']))
        if record['status'] == 'verified_infeasible': decisions.append(('infeasible', None))
        if record['method'] == 'literal_minimum' and record['algorithm']['minimum_decision_complete']:
            decisions.append((record['algorithm']['status'], record['algorithm']['height']))
        if record['method'] == 'literal_family' and record.get('upstream_and_admission_exhausted'):
            current = {row['reference_signature'] for row in record['candidates']}
            require(reference is None or reference == current, 'complete reference families differ across budgets')
            reference = current
    require(not decisions or len(set(decisions)) == 1, 'literal/optimized/independent original minimum decisions disagree')
    rows = []
    for record in records:
        signatures = {row['reference_signature'] for row in record['candidates'] if row['shape']['normalized_no_unary']}
        if reference is not None:
            require(signatures <= reference, 'published normalized tree is outside independent tiny reference family')
            if record['method'] in ['optimized', 'meta'] and record.get('upstream_and_admission_exhausted'):
                require(signatures == reference, 'claimed completed normalized provider misses independent family')
        rows.append({'method': record['method'], 'work_limit': record['request']['work_limit'], 'status': record['status'], 'outcome': outcome(record),
                     'algorithm': record['algorithm'], 'candidate_progress': record['candidate_progress'],
                     'retained_candidates': len(record['candidates']), 'independent_reference_family_size': len(reference) if reference is not None else None,
                     'normalized_signatures_retained': len(signatures),
                     'reference_coverage': ratio(Fraction(len(signatures), len(reference))) if reference else None,
                     'scope': 'complete tiny normalized family only; caps/stops elsewhere remain explicit; C02 structural scores are not latency'})
    reference_scores = [score_tree(case, candidate['tree'])[0] for record in records
                        if record['method'] == 'literal_family' and record.get('upstream_and_admission_exhausted') for candidate in record['candidates']]
    best = min(reference_scores) if reference_scores else None
    for row, record in zip(rows, records):
        selected = record['scoring'].get('selected_key')
        scores = {cell['structural_key']: Fraction(int(cell['numerator']), int(cell['denominator'])) for cell in record['scoring'].get('scores', [])}
        row['C02_best_complete_reference_score'] = ratio(best)
        row['C02_selected_score'] = ratio(scores.get(selected))
        row['C02_reference_score_gap'] = ratio(scores[selected] - best) if best is not None and selected in scores else None
    return rows


def run(args):
    source, build = args.source.resolve(), args.build_dir.resolve()
    crown, collector, searcher = args.crown.resolve(), args.collector.resolve(), args.searcher.resolve()
    require(1 <= args.repetitions <= 20 and 0 <= args.warmups <= 5 and 1 <= args.command_timeout <= 3600, 'invalid repetition/process grant')
    require(1 <= args.max_total_bytes <= 4 * 1024**3 and 0 <= args.proof_work <= 100000000 and 0 <= args.preflight_work <= 50000000, 'invalid byte/proof grant')
    require(sys.platform.startswith('linux') and hasattr(os, 'wait4'), 'search study requires Linux wait4')
    require(args.preflight_only or args.cpu is not None, 'controlled search timing requires an explicit CPU')
    if args.cpu is not None: require(args.cpu in os.sched_getaffinity(0), 'requested CPU is outside allowed affinity')
    budgets = args.work or [0, 10000, 1000000]
    require(len(budgets) == len(set(budgets)) and all(0 <= value <= 50000000 for value in budgets), 'invalid/duplicate method work grant')
    cases = cohorts()
    ids = args.case or [case['id'] for case in cases]
    require(len(ids) == len(set(ids)) and set(ids) <= {case['id'] for case in cases}, 'unknown/duplicate case')
    cases = [case for case in cases if case['id'] in ids]
    require(len(cases) * len(METHODS) * len(budgets) * (1 + args.warmups + args.repetitions) + len(cases) * 3 <= 10000, 'study command grant exceeded')
    provenance = build_provenance(source, build, crown, collector, [searcher])
    for name in ['tools/run_search_evaluation.py', 'tools/ranking_analysis.py', 'tests/reference/tree_oracle.cpp',
                 'tests/reference/candidate_set.cpp', 'examples/component-planning/reference.cpp']:
        provenance['harness_sources'][name] = digest(source / name)
    output = args.output.resolve(); output.mkdir(parents=True, exist_ok=False)
    experiment = Experiment(output, args.cpu, args.command_timeout, args.max_total_bytes)
    packet = {'schema_version': 1, 'kind': 'b04_finite_search_study_v1', 'status': 'preflighting',
              'started_utc': datetime.datetime.now(datetime.timezone.utc).isoformat(), 'build': provenance, 'environment': environment(),
              'configuration': {'cases': ids, 'methods': METHODS, 'work_limits': budgets, 'proof_work': args.proof_work,
                                'preflight_work': args.preflight_work, 'repetitions': args.repetitions, 'warmups': args.warmups,
                                'cpu': args.cpu, 'schedule_seed': args.schedule_seed, 'preflight_only': args.preflight_only},
              'cases': cases, 'preflight': [], 'runs': [], 'comparisons': [], 'summaries': [], 'external_failures': [],
              'B04_accepted': False, 'limits': ['All rows include caps/stops; literal min is genuine separate topology/power-set enumeration, not CLI tree-oracle.',
              'Method logical work units differ; fixed ceilings are per named phase, not equal CPU budgets.',
              'Shared P06 proof is actually rerun and charged separately per provider child; process wall includes all setup/export/training/cleanup.',
              'Target-process RSS includes startup/source/proof/candidates/output/runtime scoring; never a planner-only phase peak.',
              'Complete tiny reference families alone authorize normalized coverage and C02 optimum comparisons. C02 is structural units, no C03/latency prediction.',
              'The bound-but-unused collector exists only because shared build provenance requires that target; actual timed executable is searcher.',
              'No global cost/speedup/confidence/all-input or full ten-axis B04 claim.']}
    def checkpoint(): save(output / 'experiment.json', packet)
    checkpoint(); grouped = collections.defaultdict(list); jobs = []; preflight = {}; proof_checked = set(); frozen_inputs = {}
    def freeze(path, value):
        save(path, value, True); frozen_inputs[path.name] = digest(path); return path
    def check_inputs(paths):
        for path in paths: require(digest(path) == frozen_inputs[path.name], 'frozen search source/request/manifest changed')
    def invoke(label, argv):
        try: return experiment.invoke(label, argv)
        except (TimeoutError, ValueError) as error:
            packet['external_failures'].append({'label': label, 'command': experiment.commands[-1]['index'] if experiment.commands else None, 'error': str(error)})
            checkpoint(); return None, None
    try:
        plans = []; by_id = {case['id']: case for case in cases}
        for case in cases:
            query_path = freeze(output / (case['id'] + '.cq.json'), case['document'])
            requests = [(method, budget, False) for method in METHODS for budget in budgets]
            if case['size'] <= 3 and len(case['document']['query']['variables']) <= 3:
                requests.append(('literal_family', args.preflight_work, True))
            for method, budget, control in requests:
                ask = request(case, method, budget, args.proof_work)
                stem = case['id'] + '-' + method + '-' + str(budget) + ('-reference-control' if control else '')
                verify_path = freeze(output / (stem + '.verify.request.json'), ask)
                measure_path = freeze(output / (stem + '.measure.request.json'), {**ask, 'command': 'measure'})
                plans.append({'case': case['id'], 'method': method, 'work_limit': budget, 'reference_control': control,
                              'query': query_path.name, 'verify_request': verify_path.name, 'measure_request': measure_path.name,
                              'query_sha256': frozen_inputs[query_path.name], 'verify_sha256': frozen_inputs[verify_path.name],
                              'measure_sha256': frozen_inputs[measure_path.name]})
        case_manifest = freeze(output / 'cases-frozen.json', cases)
        request_manifest = freeze(output / 'requests-frozen.json', {'case_manifest_sha256': frozen_inputs[case_manifest.name], 'plans': plans})
        packet['frozen_inputs'] = frozen_inputs; packet['case_manifest'] = case_manifest.name; packet['request_manifest'] = request_manifest.name
        checkpoint()
        for plan in plans:
            case = by_id[plan['case']]; method = plan['method']; budget = plan['work_limit']; control = plan['reference_control']
            query_path = output / plan['query']; verify_path = output / plan['verify_request']; measure_path = output / plan['measure_request']
            check_inputs([case_manifest, request_manifest, query_path, verify_path, measure_path])
            ask = json.loads(verify_path.read_text()); stem = verify_path.stem
            report, command = invoke('independent_preflight_' + stem, [searcher, query_path, verify_path])
            if report is None:
                packet['preflight'].append({'case': case['id'], 'method': method, 'work_limit': budget,
                                            'reference_control': control, 'outcome': 'external_failure',
                                            'command': experiment.commands[-1]['index'] if experiment.commands else None})
                continue
            inspect(case, ask, report, query_path); grouped[case['id']].append(report)
            packet['preflight'].append({'case': case['id'], 'method': method, 'work_limit': budget,
                                        'reference_control': control, 'outcome': outcome(report), **command})
            preflight[case['id'], method, budget] = report
            certificate = (report.get('original') or {}).get('certificate')
            if certificate is not None and case['id'] not in proof_checked:
                proof = freeze(output / (case['id'] + '.original-certificate.json'), certificate)
                check_inputs([query_path, proof])
                replay, _ = invoke('independent_serialized_proof_' + case['id'], [crown, 'verify-height', query_path, proof, str(args.proof_work)])
                require(replay is None or replay.get('certificate_valid') is True, 'serialized original proof did not replay')
                proof_checked.add(case['id'])
            if not control: jobs.append((case, method, budget, query_path, ask, verify_path, measure_path))
            checkpoint()
        for case in cases:
            packet['comparisons'].extend({'case': case['id'], **row} for row in compare(case, grouped[case['id']]))
        for row in packet['preflight']:
            if row['outcome'] == 'external_failure':
                packet['comparisons'].append({'case': row['case'], 'method': row['method'], 'work_limit': row['work_limit'],
                                              'outcome': 'external_failure', 'retained_candidates': None})
        frequency = collections.defaultdict(collections.Counter)
        sizes = {case['id']: case['size'] for case in cases}
        for row in packet['preflight']:
            if not row['reference_control']: frequency[sizes[row['case']], row['method'], row['work_limit']][row['outcome']] += 1
        packet['stop_frequency'] = [{'query_size': size, 'method': method, 'work_limit': work, 'cases': sum(counts.values()),
                                    'reported_outcomes': dict(counts), 'scope': 'actual named/cap/prefix outcomes; work units differ across algorithms'}
                                   for (size, method, work), counts in sorted(frequency.items())]
        packet['correctness_gate'] = 'unexpected_external_failure_no_timing' if packet['external_failures'] else 'all_reported_variants_checked_before_timing'
        checkpoint()
        if not args.preflight_only and not packet['external_failures']:
            for repetition in range(args.warmups + args.repetitions):
                schedule = sorted(jobs, key=lambda job: hashlib.sha256(f'{args.schedule_seed}:{repetition}:{job[0]["id"]}:{job[1]}:{job[2]}'.encode()).hexdigest())
                for case, method, budget, query_path, original, verify_path, measure_path in schedule:
                    check_inputs([case_manifest, request_manifest, query_path, verify_path, measure_path])
                    ask = json.loads(measure_path.read_text())
                    require(ask == {**original, 'command': 'measure'}, 'measured request differs from preflight template')
                    report, command = invoke('search_warmup' if repetition < args.warmups else 'search_measure', [searcher, query_path, measure_path])
                    if report is None:
                        packet['runs'].append({'case': case['id'], 'method': method, 'work_limit': budget,
                                               'warmup': repetition < args.warmups, 'repetition': repetition - args.warmups,
                                               'outcome': 'external_failure', 'command': experiment.commands[-1]['index'] if experiment.commands else None})
                        continue
                    inspect(case, ask, report, query_path)
                    baseline = preflight[case['id'], method, budget]
                    require(semantic_identity(report) == semantic_identity(baseline), 'measured search changed preflight decision/family/scoring availability')
                    packet['runs'].append({'case': case['id'], 'method': method, 'work_limit': budget, 'warmup': repetition < args.warmups,
                                           'repetition': repetition - args.warmups, 'status': report['status'], 'outcome': outcome(report), 'timings': report['timings'],
                                           'retained_candidates': len(report['candidates']), **command})
                    checkpoint()
        summaries = collections.defaultdict(list)
        for run in packet['runs']:
            if not run['warmup'] and run['outcome'] != 'external_failure': summaries[run['case'], run['method'], run['work_limit']].append(run)
        for (case, method, work), values in summaries.items():
            packet['summaries'].append({'case': case, 'method': method, 'work_limit': work, 'measured_runs': len(values),
                'complete_repetitions': len(values) == args.repetitions,
                'phase_ns': {phase: distribution([row['timings'][phase] for row in values if row['timings'][phase] is not None]) for phase in values[0]['timings']},
                'process_wall_ns': distribution([row['wall_ns'] for row in values]),
                'whole_child_maxrss_KiB': distribution([row['process_maxrss_KiB'] for row in values])})
        for path, expected in provenance['files'].items(): require(digest(Path(path)) == expected, 'compiled input changed during study')
        for path, expected in provenance['compiled_dependencies'].items(): require(digest(Path(path)) == expected, 'compiled source/header dependency changed')
        for unit in provenance['compiled_units']:
            for path, expected in [('source', 'source_sha256'), ('object', 'object_sha256'), ('dependency_record', 'dependency_record_sha256')]:
                require(digest(Path(unit[path])) == unit[expected], 'recorded compiled unit changed')
        require(digest(Path(provenance['compiler']).resolve()) == provenance['compiler_binary_sha256'], 'compiler changed')
        for tool in experiment.tools.values(): require(digest(Path(tool['path'])) == tool['sha256'], 'measurement launcher changed')
        check_inputs([output / path for path in frozen_inputs])
        for path, expected in provenance['harness_sources'].items(): require(digest(source / path) == expected, 'study source changed')
        packet['end_closure_verified'] = True; packet['recorded_measurement_launchers'] = experiment.tools
        packet.update(status='external_failures_retained' if packet['external_failures'] else 'preflight_complete' if args.preflight_only else 'finite_conditional_study_complete',
                      completed_utc=datetime.datetime.now(datetime.timezone.utc).isoformat(), commands_sha256=digest(output / 'commands.json'))
        checkpoint(); print(f'Finite search study: {len(cases)} cases; {len(packet["preflight"])} preflights; {len(packet["runs"])} retained runs; {packet["status"]}; {output}')
    except Exception as error:
        packet.update(status='failed', error=str(error)); checkpoint(); raise


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    for name in ['source', 'build-dir', 'crown', 'collector', 'searcher', 'output']: parser.add_argument('--' + name, type=Path, required=True)
    parser.add_argument('--case', action='append'); parser.add_argument('--work', type=int, action='append')
    parser.add_argument('--proof-work', type=int, default=10000000); parser.add_argument('--preflight-work', type=int, default=5000000)
    parser.add_argument('--repetitions', type=int, default=3); parser.add_argument('--warmups', type=int, default=1)
    parser.add_argument('--cpu', type=int); parser.add_argument('--schedule-seed', type=int, default=20261115)
    parser.add_argument('--command-timeout', type=int, default=180); parser.add_argument('--max-total-bytes', type=int, default=1024**3)
    parser.add_argument('--preflight-only', action='store_true'); run(parser.parse_args())


if __name__ == '__main__':
    try: main()
    except Exception as error: print('Finite search study failed: ' + str(error), file=sys.stderr); raise SystemExit(1)
