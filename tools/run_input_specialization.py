#!/usr/bin/env python3
"""Same-engine SQL input interpretation/threaded-program experiment."""
from __future__ import annotations
import argparse
import collections
import datetime
from fractions import Fraction
import hashlib
import json
import os
from pathlib import Path
import sqlite3
import sys

sys.dont_write_bytecode = True
from ranking_analysis import ratio
from run_measurements import Experiment, build_provenance, digest, distribution, environment, require
from verify_workloads import canonical

MODES = {'interpreted_v1': 'crown-input-interpreted-v1', 'threaded_v1': 'crown-input-threaded-v1'}
PROTOCOL = 'signed_delta_and_full_snapshot_each_input_v1'


def save(path, value, exclusive=False):
    with path.open('x' if exclusive else 'w') as stream: stream.write(json.dumps(value, sort_keys=True, indent=2) + '\n')


def cases(widths):
    result = []
    for width in widths:
        def add(name, sql, tables, kinds):
            catalog = {'version': 1, 'tables': [{'name': name, 'columns': [{'name': column, 'type': 'bool' if kind == 'boolean' else kind}
                       for column, kind in columns]} for name, columns in tables]}
            events = []
            def edit(table, values, operation, phase):
                events.append({'table': table, 'values': values, 'operation': operation, 'phase': phase})
            for table, columns in tables:
                for index in range(width):
                    values = [index if column == 'x' else index % 2 if column == 'y' else
                              ('yes' if index % 2 == 0 else 'no') if kind == 'string' else index % 2 == 0
                              for column, kind in columns]
                    edit(table, values, 'insert', 'charged_load')
            initial = list(events)
            for event in initial:
                edit(event['table'], event['values'], 'insert', 'duplicate_noop')
            for event in initial[::2]:
                edit(event['table'], event['values'], 'delete', 'erase')
            for event in initial[::2]:
                edit(event['table'], event['values'], 'insert', 'reinsert')
            for event in initial[:1]:
                missing = list(event['values']); missing[0] = -999
                edit(event['table'], missing, 'delete', 'absent_noop')
            result.append({'id': name + '-w' + str(width), 'width': width, 'sql': sql,
                           'catalog': catalog, 'events': events, 'output_types': kinds})
        simple = [('r', [('x', 'int64'), ('tag', 'string'), ('flag', 'boolean')])]
        joined = simple + [('s', [('x', 'int64'), ('y', 'int64')])]
        add('join_only', 'SELECT DISTINCT r.x,r.tag,s.y FROM r,s WHERE r.x=s.x', joined, ['int64', 'string', 'int64'])
        add('local_predicates', "SELECT DISTINCT r.x,r.tag,s.y FROM r,s WHERE r.x=s.x AND r.x>=0 AND (r.tag='yes' OR r.flag)", joined, ['int64', 'string', 'int64'])
        add('cast_repeat', 'SELECT DISTINCT CAST(x AS BIGINT),x AS repeated,7 AS fixed FROM r WHERE CAST(x AS BIGINT)>=0 AND flag IS NOT FALSE', simple, ['int64'] * 3)
        add('null_logic', 'SELECT DISTINCT x FROM r WHERE flag OR x=CAST(NULL AS BIGINT)', simple, ['int64'])
        add('self_alias', 'SELECT DISTINCT a.x,b.x FROM r a,r b WHERE a.x=b.x AND a.flag IS NOT FALSE AND b.x>=0', simple, ['int64'] * 2)
        add('exists', 'SELECT EXISTS(SELECT 1 FROM r WHERE flag AND x>=0)', simple, ['boolean'])
        add('constant_false', 'SELECT DISTINCT x FROM r WHERE x=1 AND x=2', simple, ['int64'])
    return result


def oracle(case):
    """Independent SQLite physical set state and exact before/after output sets."""
    connection = sqlite3.connect(':memory:')
    def quote(value): return '"' + value.replace('"', '""') + '"'
    try:
        for table in case['catalog']['tables']:
            columns = table['columns']; names = ','.join(quote(column['name']) for column in columns)
            definition = ','.join(quote(column['name']) + (' TEXT' if column['type'] == 'string' else ' INTEGER') + ' NOT NULL' for column in columns)
            connection.execute('CREATE TABLE ' + quote(table['name']) + '(' + definition + ',UNIQUE(' + names + '))')
        def snapshot():
            return {tuple(bool(cell) if kind == 'boolean' else cell for cell, kind in zip(row, case['output_types']))
                    for row in connection.execute(case['sql']).fetchall()}
        previous = snapshot(); initial = [list(row) for row in previous]; frames = []
        for sequence, event in enumerate(case['events'], 1):
            values = event['values']; table = next(table for table in case['catalog']['tables'] if table['name'] == event['table'])
            if event['operation'] == 'insert':
                connection.execute('INSERT OR IGNORE INTO ' + quote(event['table']) + ' VALUES(' + ','.join('?' for _ in values) + ')', values)
            else:
                condition = ' AND '.join(quote(column['name']) + '=?' for column in table['columns'])
                connection.execute('DELETE FROM ' + quote(event['table']) + ' WHERE ' + condition, values)
            after = snapshot(); delta = [{'operation': 'delete', 'values': list(row)} for row in previous - after]
            delta += [{'operation': 'insert', 'values': list(row)} for row in after - previous]
            frames.append({'sequence': sequence, 'phase': event['phase'], 'rows': [list(row) for row in after], 'delta': delta})
            previous = after
        return {'initial_rows': initial, 'epochs': frames}
    finally: connection.close()


def timing(value, verify):
    require(value is None if verify else type(value) is int and value >= 0, 'invalid verify/measure phase clock')


def unordered(value):
    keys = [canonical(row) for row in value]
    require(len(keys) == len(set(keys)), 'duplicate native output record')
    return sorted(keys)


def inspect(case, ask, report, expected, paths, reference=None):
    require(report['kind'] == 'b04_input_specialization_report_v1' and report['schema_version'] == 1 and
            report['request'] == ask and report['command'] == ask['command'] and report['case_id'] == case['id'], 'specialization protocol mismatch')
    require(report['execution'] == ask['execution'] and report['execution_key'] == MODES[ask['execution']] and
            report['output_protocol'] == PROTOCOL, 'actual execution/output mode mismatch')
    require(report['sql_sha256'] == digest(paths['sql']) and report['input_sha256'] == digest(paths['input']) and
            report['catalog_sha256'] == paths['catalog_sha256'], 'actual source/input/catalog binding mismatch')
    require(report['constant_operator'] is case['id'].startswith('constant_false-'), 'constant executable route differs')
    usage = report['preparation']
    require(all(type(usage[name]) is int and usage[name] >= 0 for name in ['work', 'instructions', 'metadata_bytes']), 'invalid preparation units')
    if ask['execution'] == 'interpreted_v1':
        require(all(usage[name] == 0 for name in ['work', 'instructions', 'metadata_bytes']), 'interpreter retained prepared instruction tables')
    verify = ask['command'] == 'verify'
    for name in ['read_request_ns', 'shared_program_ns', 'execution_prepare_ns']: timing(report[name], verify)
    identity = {key: report[key] for key in ['sql_sha256', 'catalog_sha256', 'input_sha256', 'physical_sha256', 'source_sha256', 'tree', 'physical_options', 'output_protocol']}
    if reference: require(identity == reference['identity'], 'mode/repetition changed actual program/tree/trace/output')
    require(len(report['passes']) == ask['warmup_passes'] + ask['measured_passes'], 'fresh pass schedule differs')
    counts = []
    for index, value in enumerate(report['passes']):
        require(value['warmup'] is (index < ask['warmup_passes']) and value['execution_key'] == MODES[ask['execution']], 'native owner admission lost selected mode')
        require(value['owner_prepared_instructions'] == usage['instructions'] and value['owner_extra_table_bytes'] == usage['metadata_bytes'], 'fresh owner lost prepared data-program shape')
        for name in ['initialize_ns', 'loop_wall_ns', 'teardown_ns']: timing(value[name], verify)
        if not verify: require(value['initial_rows'] is None, 'measure retained initial result capture')
        require(value['accepted_sequence'] == len(expected['epochs']) and len(value['epochs']) == len(expected['epochs']), 'native horizon differs')
        if ask['command'] == 'verify': require(unordered(value['initial_rows']) == unordered(expected['initial_rows']), 'initial SQL result differs from SQLite')
        obligation = {'initial_output_records': len(expected['initial_rows']), 'epochs': []}
        require(value['initial_output_records'] == obligation['initial_output_records'], 'initial output count differs')
        total = value['initial_output_records']
        for actual, wanted in zip(value['epochs'], expected['epochs']):
            require(actual['sequence'] == actual['physical_input_end'] == wanted['sequence'] and actual['phase'] == wanted['phase'], 'physical/phase coordinates differ')
            require(actual['output_records'] == actual['delta_records'] == len(wanted['delta']) and
                    actual['snapshot_records'] == len(wanted['rows']), 'measured output obligation differs')
            require(type(actual['native_work']) is int and actual['native_work'] >= 0, 'invalid native work units')
            for field in ['apply_ns', 'output_ns', 'release_ns']: timing(actual[field], verify)
            if ask['command'] == 'verify':
                require(unordered(actual['actual']['rows']) == unordered(wanted['rows']) and
                        unordered(actual['actual']['delta']) == unordered(wanted['delta']), 'native SQL prefix/delta differs from SQLite')
            else: require(actual['actual'] is None, 'measure retained per-input result capture')
            total += actual['delta_records'] + actual['snapshot_records']
            obligation['epochs'].append({key: actual[key] for key in ['sequence', 'phase', 'delta_records', 'snapshot_records', 'native_work']})
        require(value['output_records'] == total, 'pass total omits initial/delta/snapshot work')
        counts.append(obligation)
    if reference:
        require(all(value == reference['counts'] for value in counts), 'mode/repetition changed output or native work obligations')
    return {'identity': identity, 'counts': counts[-1]}


def run(args):
    require(args.preflight_only or args.cpu is not None, 'controlled specialization timing requires explicit CPU')
    if args.cpu is not None: require(args.cpu in os.sched_getaffinity(0), 'CPU outside allowed affinity')
    require(1 <= args.repetitions <= 10 and 0 <= args.warmups <= 5 and 1 <= args.command_timeout <= 600, 'invalid repetition/process grant')
    widths = args.width or [2, 8]
    require(1 <= len(widths) <= 3 and len(widths) == len(set(widths)) and all(1 <= width <= 64 for width in widths), 'invalid/duplicate width grant')
    require(1 <= args.max_total_bytes <= 2 * 1024**3, 'invalid raw-byte grant')
    source, build = args.source.resolve(), args.build_dir.resolve()
    crown, collector, client = args.crown.resolve(), args.collector.resolve(), args.client.resolve()
    provenance = build_provenance(source, build, crown, collector, [client])
    harness = ['tools/run_input_specialization.py', 'tools/ranking_analysis.py', 'tools/verify_workloads.py']
    for name in harness: provenance['harness_sources'][name] = digest(source / name)
    selected = cases(widths); backends = args.backend or ['reference_ordered_v1', 'indexed_chained_v1']
    require(len(backends) == len(set(backends)), 'duplicate backend')
    output = args.output.resolve(); output.mkdir(parents=True, exist_ok=False)
    experiment = Experiment(output, args.cpu, args.command_timeout, args.max_total_bytes)
    packet = {'schema_version': 1, 'kind': 'b04_input_specialization_study_v1', 'status': 'preflighting',
        'started_utc': datetime.datetime.now(datetime.timezone.utc).isoformat(), 'build': provenance, 'environment': environment(),
        'configuration': {'widths': widths, 'backends': backends, 'executions': list(MODES), 'cpu': args.cpu,
                          'warmups_per_process': args.warmups, 'repetitions': args.repetitions, 'preflight_only': args.preflight_only, 'schedule_seed': args.schedule_seed},
        'cases': selected, 'declared_variants': [{'case': case['id'], 'backend': backend, 'execution': execution}
            for case in selected for backend in backends for execution in MODES],
        'verification': [], 'runs': [], 'summaries': [], 'comparisons': [], 'external_failures': [],
        'correctness_gate': 'pending', 'output_protocol': PROTOCOL, 'B04_accepted': False,
        'cache_policy': 'no global prepared cache; cold compiler source reused across fresh pass owners; each owner admits its own metadata',
        'limits': ['Same real SQL/program/tree/backend/trace/output; only input-expression execution changes.',
          'execution_prepare_ns includes receiving base freeze; table metadata_bytes excludes base Data/control; actual query account includes all.',
          'Whole child wall/RSS include compiler, warmups, serialization and teardown; loop/apply phases have narrower scopes.',
          'Static worker code is in one shared executable; there is no per-query machine code/JIT.',
          'Results are finite matched observations, including slower outcomes; no global speedup or full ten-axis acceptance.']}
    def checkpoint(): save(output / 'experiment.json', packet)
    def invoke(label, argv):
        try: return experiment.invoke(label, argv)
        except (ValueError, TimeoutError) as error:
            packet['external_failures'].append({'label': label, 'error': str(error), 'command': experiment.commands[-1]['index'] if experiment.commands else None})
            checkpoint(); return None, None
    frozen, jobs, references, reports = {}, [], {}, collections.defaultdict(list)
    def pin(path): frozen[path.name] = digest(path); return path
    def check_inputs():
        for name, sha in frozen.items(): require(digest(output / name) == sha, 'frozen specialization source/request/manifest changed')
    checkpoint()
    try:
        for case in selected:
            sql = output / (case['id'] + '.sql'); sql.write_text(case['sql'] + '\n'); pin(sql)
            catalog = output / (case['id'] + '.catalog.json'); save(catalog, {'schema_version': 1, 'catalog': case['catalog']}, True); pin(catalog)
            canonical_catalog, _ = invoke('canonical_catalog', [crown, 'canonicalize-catalog', catalog])
            require(canonical_catalog is not None, 'canonical catalog setup failed')
            catalog_sha = hashlib.sha256(canonical(canonical_catalog).encode()).hexdigest()
            trace = []
            for sequence, event in enumerate(case['events'], 1):
                trace.append({'schema_version': 1, 'catalog_version': 1, 'source_schema_version': 1, 'catalog_sha256': catalog_sha,
                              'sequence': sequence, 'table': event['table'], 'operation': event['operation'], 'values': event['values']})
            input_path = output / (case['id'] + '.input.jsonl'); input_path.write_text(''.join(canonical(event) + '\n' for event in trace)); pin(input_path)
            expected = oracle(case); expected_path = output / (case['id'] + '.expected.json'); save(expected_path, expected, True); pin(expected_path)
            paths = {'sql': sql, 'catalog': catalog, 'input': input_path, 'catalog_sha256': catalog_sha}
            for backend in backends:
                physical = {'schema_version': 1, 'policy': {'planner': 'crown-tree-v1', 'arithmetic': 'exact-nonnull-v1', 'optimization': 'structural-height-v1', 'cost_model': 'no-cost-v1'}, 'limits': {'work': 1000000, 'identity_work': 1000000}}
                if backend == 'indexed_chained_v1':
                    from run_measurements import indexed_options
                    physical = indexed_options()
                for execution in MODES:
                    stem = case['id'] + '-' + backend + '-' + execution
                    ask = {'schema_version': 1, 'case_id': case['id'], 'command': 'verify', 'execution': execution,
                        'physical_options': physical, 'preparation': {'work': 1000000, 'instructions': 100000},
                        'memory_limit_bytes': 256 * 1024**2, 'work_limit': 100000000, 'warmup_passes': 0, 'measured_passes': 1,
                        'max_events': 4096, 'max_output_records': 1000000, 'max_output_bytes': 64 * 1024**2,
                        'phases': [event['phase'] for event in case['events']]}
                    verify_path = output / (stem + '.verify.json'); save(verify_path, ask, True); pin(verify_path)
                    measured = {**ask, 'command': 'measure', 'warmup_passes': args.warmups}
                    measure_path = output / (stem + '.measure.json'); save(measure_path, measured, True); pin(measure_path)
                    check_inputs(); report, command = invoke('verify_' + stem, [client, sql, catalog, input_path, verify_path])
                    received_row = {'case': case['id'], 'backend': backend, 'execution': execution,
                        'availability': 'unverified' if report is not None else 'external_failure',
                        'command_index': experiment.commands[-1]['index']}
                    packet['verification'].append(received_row)
                    if report is None: checkpoint(); continue
                    reference = references.get((case['id'], backend))
                    received = inspect(case, ask, report, expected, paths, reference)
                    references[case['id'], backend] = received
                    received_row.update(availability='verified', execution_key=report['execution_key'], physical_sha256=report['physical_sha256'], **command)
                    jobs.append((case, backend, execution, paths, expected, measured, measure_path)); checkpoint()
        manifest = output / 'frozen-inputs.json'; save(manifest, {'cases': selected, 'files': dict(frozen)}, True); pin(manifest)
        packet['frozen_inputs'] = frozen; packet['frozen_manifest'] = manifest.name
        require(len(packet['verification']) == len(packet['declared_variants']), 'preflight silently omitted a declared variant')
        packet['correctness_gate'] = 'all_variants_all_prefixes_verified_before_timing' if not packet['external_failures'] else 'external_failures_no_timing'
        checkpoint()
        if not args.preflight_only and not packet['external_failures']:
            for repetition in range(args.repetitions):
                schedule = sorted(jobs, key=lambda job: hashlib.sha256(f'{args.schedule_seed}:{repetition}:{job[0]["id"]}:{job[1]}:{job[2]}'.encode()).hexdigest())
                for case, backend, execution, paths, expected, ask, request_path in schedule:
                    check_inputs(); report, command = invoke('measure', [client, paths['sql'], paths['catalog'], paths['input'], request_path])
                    received_row = {'case': case['id'], 'backend': backend, 'execution': execution,
                        'availability': 'unverified' if report is not None else 'external_failure',
                        'warmup': False, 'repetition': repetition, 'command_index': experiment.commands[-1]['index']}
                    packet['runs'].append(received_row)
                    if report is None: checkpoint(); continue
                    inspect(case, ask, report, expected, paths, references[case['id'], backend])
                    received_row.update(availability='verified', execution_key=report['execution_key'], physical_sha256=report['physical_sha256'],
                        preparation=report['preparation'], shared_program_ns=report['shared_program_ns'], execution_prepare_ns=report['execution_prepare_ns'], **command)
                    reports[case['id'], backend, execution].append(report); checkpoint()
        for (case, backend, execution), values in reports.items():
            measured_passes = [p for report in values for p in report['passes'] if not p['warmup']]
            inputs = len(next(c for c in selected if c['id'] == case)['events'])
            samples = [p['loop_wall_ns'] for p in measured_passes]
            packet['summaries'].append({'case': case, 'backend': backend, 'execution': execution,
                'execution_key': MODES[execution], 'measured_invocations': len(values), 'ns_per_physical_input': ratio(Fraction(sum(samples), len(samples) * inputs)),
                'loop_wall_ns': distribution(samples), 'shared_program_ns': distribution([r['shared_program_ns'] for r in values]),
                'execution_prepare_ns': distribution([r['execution_prepare_ns'] for r in values]), 'preparation': values[0]['preparation'],
                'native_memory_before_teardown': [p['native_memory_before_teardown'] for p in measured_passes]})
        by_key = {(r['case'], r['backend'], r['execution']): r for r in packet['summaries']}
        for case in selected:
            for backend in backends:
                left, right = by_key.get((case['id'], backend, 'interpreted_v1')), by_key.get((case['id'], backend, 'threaded_v1'))
                if left is None or right is None: continue
                def value(row): return Fraction(int(row['ns_per_physical_input']['numerator']), int(row['ns_per_physical_input']['denominator']))
                a, b = value(left), value(right)
                packet['comparisons'].append({'case': case['id'], 'backend': backend, 'axis': 'runtime_input_execution',
                    'interpreted_key': MODES['interpreted_v1'], 'threaded_key': MODES['threaded_v1'],
                    'physical_sha256': references[case['id'], backend]['identity']['physical_sha256'],
                    'interpreted_ns_per_input': ratio(a), 'threaded_ns_per_input': ratio(b), 'threaded_over_interpreted': ratio(b/a) if a else None,
                    'scope': 'same actual engine/source/tree/storage/input/output; concrete input-program specialization only; no predetermined speedup'})
        check_inputs()
        for path, sha in {**provenance['files'], **provenance['compiled_dependencies']}.items(): require(digest(Path(path)) == sha, 'compiled input changed')
        for unit in provenance['compiled_units']:
            for name, key in [('source', 'source_sha256'), ('object', 'object_sha256'), ('dependency_record', 'dependency_record_sha256')]:
                require(digest(Path(unit[name])) == unit[key], 'compiled unit changed')
        for path, sha in provenance['harness_sources'].items(): require(digest(source/path) == sha, 'harness changed')
        require(digest(Path(provenance['compiler']).resolve()) == provenance['compiler_binary_sha256'], 'compiler changed')
        for tool in experiment.tools.values(): require(digest(Path(tool['path'])) == tool['sha256'], 'launcher changed')
        packet['shared_executable_bytes'] = client.stat().st_size; packet['shared_executable_sha256'] = digest(client)
        packet['recorded_measurement_launchers'] = experiment.tools; packet['end_closure_verified'] = True
        packet['status'] = 'external_failures_retained' if packet['external_failures'] else 'preflight_complete' if args.preflight_only else 'finite_conditional_input_specialization_complete'
        packet['completed_utc'] = datetime.datetime.now(datetime.timezone.utc).isoformat(); packet['commands_sha256'] = digest(output/'commands.json'); checkpoint()
        print(f'Input specialization: {len(packet["verification"])} gates, {len(packet["runs"])} measured children, {packet["status"]}; {output}')
    except Exception as error:
        packet.update(status='failed', error=str(error)); checkpoint(); raise


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    for name in ['source', 'build-dir', 'crown', 'collector', 'client', 'output']: parser.add_argument('--' + name, type=Path, required=True)
    parser.add_argument('--width', type=int, action='append'); parser.add_argument('--backend', choices=['reference_ordered_v1', 'indexed_chained_v1'], action='append')
    parser.add_argument('--cpu', type=int); parser.add_argument('--warmups', type=int, default=1); parser.add_argument('--repetitions', type=int, default=3)
    parser.add_argument('--command-timeout', type=int, default=180); parser.add_argument('--max-total-bytes', type=int, default=1024**3)
    parser.add_argument('--schedule-seed', type=int, default=20261115); parser.add_argument('--preflight-only', action='store_true'); run(parser.parse_args())


if __name__ == '__main__':
    try: main()
    except Exception as error: print('Input specialization study failed: ' + str(error), file=sys.stderr); raise SystemExit(1)
