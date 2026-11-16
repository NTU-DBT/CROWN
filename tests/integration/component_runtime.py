#!/usr/bin/env python3
"""Compare experimental native adapters with SQLite at actual observation points."""
from collections import Counter
import copy
import hashlib
import json
from pathlib import Path
import sqlite3
import subprocess
import sys
import tempfile
import jsonschema

sys.dont_write_bytecode = True
ROOT = Path(__file__).resolve().parents[2]
sys.path.insert(0, str(ROOT / 'tools'))
from run_measurements import indexed_options, require
from verify_workloads import canonical


def catalog(names, columns=('c0', 'c1')):
    return {'schema_version': 1, 'catalog': {'version': 1, 'tables': [
        {'name': name, 'source_schema_version': 1,
         'columns': [{'name': column, 'nullable': False, 'type': 'int64'} for column in columns],
         'constraints': [], 'key_hints': [], 'statistics': {'distinct_counts': []}}
        for name in names]}}


def sqlite_prefixes(sql, tables, events):
    """Recompute from physical facts, retaining both set and bag interpretations."""
    database = sqlite3.connect(':memory:')
    for table in tables['catalog']['tables']:
        columns = ','.join(column['name'] + ' INTEGER NOT NULL' for column in table['columns'])
        database.execute('CREATE TABLE ' + table['name'] + '(' + columns + ')')
    previous = set(database.execute(sql))
    result = []
    for event in events:
        name = event['table']
        require(name in {table['name'] for table in tables['catalog']['tables']}, 'unexpected oracle table')
        if event['operation'] == '+':
            database.execute('INSERT INTO ' + name + ' VALUES (?,?)', event['values'])
        else:
            columns = next(table['columns'] for table in tables['catalog']['tables'] if table['name'] == name)
            database.execute('DELETE FROM ' + name + ' WHERE ' + columns[0]['name'] + '=? AND ' + columns[1]['name'] + '=?', event['values'])
        bag = Counter(database.execute(sql))
        current = set(bag)
        delta = [{'operation': operation, 'values': list(row)}
                 for operation, rows in [('-', previous - current), ('+', current - previous)]
                 for row in sorted(rows)]
        result.append({'rows': sorted(map(list, current)), 'delta': delta,
                       'bag': [{'values': list(row), 'multiplicity': count} for row, count in sorted(bag.items())]})
        previous = current
    database.close()
    return result


def request(label, sql, tables, events, output, backend):
    physical = indexed_options()
    if backend == 'reference_ordered_v1':
        del physical['indexed_storage']
        physical['schema_version'] = 1
    return {'schema_version': 1, 'case_id': label, 'query_family': label,
            'command': 'verify', 'output': output, 'warmup_passes': 0, 'measured_passes': 1,
            'limits': {'input_events': 1000, 'output_records': 100000, 'output_bytes': 16 * 1024 * 1024},
            'program': {'sql': sql, 'catalog': tables}, 'events': events,
            'native': {'physical_options': physical, 'memory_limit_bytes': 256 * 1024 * 1024,
                       'work_limit': 1000000, 'mode': 'delta'}}


def event(operation, table, first, second):
    return {'operation': operation, 'table': table, 'values': [first, second], 'phase': 'oracle_control'}


def main():
    require(len(sys.argv) in (5, 6), 'usage: component_runtime.py SET ROWS SESSION CROWN [NEW_ARTIFACT_DIRECTORY]')
    set_binary, rows_binary, session_binary, crown = [Path(value).resolve() for value in sys.argv[1:5]]
    temporary = None
    if len(sys.argv) == 6:
        directory = Path(sys.argv[5]).resolve()
        directory.mkdir(parents=True, exist_ok=False)
    else:
        temporary = tempfile.TemporaryDirectory(prefix='crown-component-runtime-')
        directory = Path(temporary.name)
    commands, comparisons = [], 0
    schema_path = ROOT / 'schemas/component-runtime-request-v1.schema.json'
    schema_document = json.loads(schema_path.read_text())
    store = {path.as_uri(): json.loads(path.read_text()) for path in (ROOT / 'schemas').glob('*.schema.json')}
    schema = jsonschema.Draft202012Validator(schema_document,
        resolver=jsonschema.RefResolver(base_uri=schema_path.as_uri(), referrer=schema_document, store=store))

    def invoke(label, binary, data, success=True):
        if success:
            schema.validate(data)
        name = f'{len(commands):03d}-{label}'
        path = directory / (name + '.request.json')
        path.write_text(canonical(data) + '\n')
        child = subprocess.run([str(binary), str(path)], capture_output=True, text=True, timeout=180)
        stdout, stderr = directory / (name + '.stdout'), directory / (name + '.stderr')
        stdout.write_text(child.stdout)
        stderr.write_text(child.stderr)
        commands.append({'label': label, 'binary': str(binary), 'request': path.name,
                         'request_sha256': hashlib.sha256(path.read_bytes()).hexdigest(),
                         'exit_code': child.returncode, 'stdout': stdout.name, 'stderr': stderr.name})
        (directory / 'commands.json').write_text(json.dumps(commands, indent=2) + '\n')
        require((child.returncode == 0) == success, label + ': ' + child.stderr[-2000:])
        if success:
            require(not child.stderr, label + ': unexpected successful diagnostic')
            return json.loads(child.stdout)
        require(not child.stdout, label + ': rejected request emitted results')
        return None

    # Endpoint witnesses multiply walks while the DISTINCT internal quadruple
    # stays one; substituting ordinary COUNT(*) would return four at prefix7.
    graph = catalog(['graph'], ('src', 'dst'))
    distinct_sql = ('SELECT DISTINCT b.src,c.src,d.src,e.src FROM graph a,graph b,graph c,graph d,graph e '
                    'WHERE a.dst=b.src AND b.dst=c.src AND c.dst=d.src AND d.dst=e.src')
    graph_events = [event('+', 'graph', left, right) for left, right in
                    [(1, 10), (2, 10), (10, 20), (20, 30), (30, 40), (40, 100), (40, 101)]]
    graph_events += [event('-', 'graph', 1, 10), event('-', 'graph', 2, 10), event('+', 'graph', 2, 10)]
    expected_distinct = sqlite_prefixes(distinct_sql, graph, graph_events)
    expected_bag = sqlite_prefixes(distinct_sql.replace(' DISTINCT', ''), graph, graph_events)
    require(len(expected_distinct[6]['rows']) == 1 and sum(row['multiplicity'] for row in expected_bag[6]['bag']) == 4,
            'DISTINCT control does not distinguish witness counts')
    path_tables = catalog(['r0', 'r1', 'r2'])
    path_sql = ('SELECT DISTINCT r0.c0,r0.c1,r1.c1,r2.c1 FROM r0,r1,r2 '
                'WHERE r0.c1=r1.c0 AND r1.c1=r2.c0')
    path_events = [event('+', 'r0', 1, 7), event('+', 'r1', 7, 8), event('+', 'r2', 8, 9),
                   event('+', 'r2', 8, 10), event('-', 'r1', 7, 8), event('+', 'r1', 7, 8)]
    expected_path = sqlite_prefixes(path_sql, path_tables, path_events)
    for backend in ('reference_ordered_v1', 'indexed_chained_v1'):
        for sql, tables, events, expected, label in [
                (distinct_sql, graph, graph_events, expected_distinct, 'l5_distinct'),
                (path_sql, path_tables, path_events, expected_path, 'l3_full')]:
            for mode in ('delta', 'maintenance'):
                data = request(label, sql, tables, events, 'cardinality', backend)
                data['native']['mode'] = mode
                report = invoke(label + '-' + backend + '-' + mode, set_binary, data)
                actual = report['passes'][0]['epochs']
                require([epoch['actual'] for epoch in actual] == [len(epoch['rows']) for epoch in expected], 'DISTINCT cardinality differs from SQLite')
                comparisons += len(expected)
            data = request(label, sql, tables, events, 'delta_and_snapshot', backend)
            report = invoke(label + '-' + backend + '-full', set_binary, data)
            for actual, wanted in zip(report['passes'][0]['epochs'], expected, strict=True):
                require(sorted(map(canonical, actual['actual']['rows'])) == sorted(map(canonical, wanted['rows'])), 'set rows differ')
                require(sorted(map(canonical, actual['actual']['delta'])) == sorted(map(canonical, wanted['delta'])), 'signed set deltas differ')
                comparisons += 1

    # Replay one genuine original-source artifact under either requested backend.
    sql_path, catalog_path = directory / 'path.sql', directory / 'path.catalog.json'
    sql_path.write_text(path_sql)
    catalog_path.write_text(canonical(path_tables))
    compiled = subprocess.run([str(crown), 'compile', str(sql_path), str(catalog_path)], capture_output=True, text=True, timeout=180)
    (directory / 'supplied-compile.stdout').write_text(compiled.stdout)
    (directory / 'supplied-compile.stderr').write_text(compiled.stderr)
    require(compiled.returncode == 0 and not compiled.stderr, 'supplied original artifact did not compile')
    commands.append({'label': 'supplied-original-compile', 'binary': str(crown), 'arguments': ['compile', str(sql_path), str(catalog_path)],
                     'exit_code': compiled.returncode, 'stdout': 'supplied-compile.stdout', 'stderr': 'supplied-compile.stderr'})
    physical = json.loads(compiled.stdout)['physical']
    for backend in ('reference_ordered_v1', 'indexed_chained_v1'):
        data = request('supplied_source', path_sql, path_tables, path_events, 'delta_and_snapshot', backend)
        data['program']['compiled_set'] = physical
        report = invoke('supplied-' + backend, set_binary, data)
        require([sorted(map(canonical, epoch['actual']['rows'])) for epoch in report['passes'][0]['epochs']] ==
                [sorted(map(canonical, epoch['rows'])) for epoch in expected_path],
                're-lowered supplied source differs')
        comparisons += len(expected_path)
        altered = copy.deepcopy(data)
        altered['program']['sql'] = path_sql.replace('r0.c0,r0.c1,r1.c1,r2.c1', 'r0.c0')
        invoke('foreign-supplied-' + backend, set_binary, altered, False)

    canceling = [event('+', 'graph', 999, 9999), event('-', 'graph', 999, 9999), event('+', 'graph', 999, 9999)] + graph_events
    bag_sql = distinct_sql.replace(' DISTINCT', '')
    for backend in ('reference_ordered_v1', 'indexed_chained_v1'):
        for sql, label in ((bag_sql, 'bag'), (distinct_sql, 'weighted_distinct')):
            expected = sqlite_prefixes(sql, graph, canceling)
            observed_ends = [offset for offset in range(1, len(canceling)+1) if offset%3 == 0 or offset == len(canceling)]
            controls = []
            for batch_size in (1, 3):
                data = request(label, sql, graph, canceling, 'compressed_bag', backend)
                del data['native']['mode']
                data['native'].update(transaction_batch_size=batch_size, observation_interval=3)
                report = invoke(label + '-' + backend + '-batch-' + str(batch_size), rows_binary, data)
                result = report['passes'][0]
                require([epoch['physical_input_end'] for epoch in result['epochs']] == observed_ends, 'wrong source observation boundaries')
                require(sum(row['source_replacements'] for row in result['transactions']) == len(canceling), 'net batch lost source edits')
                require([row['sequence'] for row in result['transactions']] == list(range(1, len(result['transactions'])+1)), 'transaction sequence used physical offsets')
                for epoch in result['epochs']:
                    require(sorted(map(canonical, epoch['actual'])) == sorted(map(canonical, expected[epoch['physical_input_end']-1]['bag'])), 'SQL bag differs from SQLite')
                    comparisons += 1
                controls.append([sorted(map(canonical, epoch['actual'])) for epoch in result['epochs']])
            require(controls[0] == controls[1], 'single/net endpoint bag states differ')

    # Output contrasts retain WAL for durable versus nondurable-output arms;
    # transport batching still publishes every physical event separately.
    session_arms = [
        ('single', 'volatile', 'discard', 1, 0, []),
        ('transport', 'volatile', 'discard', 3, 0, []),
        ('encode', 'volatile', 'serialize', 3, 0, []),
        ('wal', 'wal', 'discard', 3, 0, []),
        ('wal_encode', 'wal', 'serialize', 3, 0, []),
        ('durable', 'wal', 'durable', 3, 0, []),
        ('wal_replay', 'wal', 'discard', 3, 0, [3]),
        ('durable_replay', 'wal', 'durable', 3, 0, [3]),
        ('checkpoint_recover', 'wal', 'discard', 3, 3, [3]),
        ('durable_recover', 'wal', 'durable', 3, 3, [3]),
        ('maintenance', 'volatile', 'maintenance', 3, 0, []),
    ]
    preserved = None
    for backend in ('reference_ordered_v1', 'indexed_chained_v1'):
        for label, durability, action, batch, checkpoint, recover in session_arms:
            data = request(label, path_sql, path_tables, path_events,
                           'none' if action == 'maintenance' else 'delta_and_snapshot', backend)
            data['native']['mode'] = 'maintenance' if action == 'maintenance' else 'delta'
            data['session'] = {'transport_batch_size': batch, 'output_action': action, 'durability': durability,
                               'checkpoint_interval': checkpoint, 'recover_after': recover,
                               'state_directory': str(directory / (label + '-' + backend + '.state'))}
            report = invoke('session-' + label + '-' + backend, session_binary, data)
            result = report['passes'][0]
            require(result['accepted_progress']['sequence'] == len(path_events), 'session lost accepted progress')
            require([epoch['sequence'] for epoch in result['epochs']] == list(range(1, len(path_events)+1)), 'transport changed commit boundaries')
            for epoch, wanted in zip(result['epochs'], expected_path, strict=True):
                require(sorted(map(canonical, epoch['actual']['rows'])) == sorted(map(canonical, wanted['rows'])), 'session snapshot differs')
                if action != 'maintenance':
                    require(sorted(map(canonical, epoch['actual']['delta'])) == sorted(map(canonical, wanted['delta'])), 'session delta differs')
                comparisons += 1
            require(sum(row['transport_events'] for row in result['batches']) == len(path_events), 'transport lost inputs')
            require(sum(row['reconstructed'] for row in result['batches']) == len(recover), 'reconstruction was skipped')
            require(sum(row['checkpointed'] for row in result['batches']) == (2 if checkpoint else 0), 'checkpoint was skipped')
            if action == 'serialize':
                require(result['serialized_bytes'] > 0, 'serialize arm discarded without encoding')
            if action == 'durable':
                require(result['durable_state']['verified_sink_sequence'] == len(path_events), 'durable sink prefix differs')
            if durability == 'wal':
                require(Path(result['durable_state']['root_path']).is_file(), 'WAL root was not persisted')
                preserved = copy.deepcopy(data)

    # Fresh-state output directories are exclusive; a rejected rerun must leave
    # an already committed generation byte-identical.
    state = Path(preserved['session']['state_directory'])
    before = {str(path): hashlib.sha256(path.read_bytes()).hexdigest() for path in state.rglob('*') if path.is_file()}
    invoke('existing-durable-state', session_binary, preserved, False)
    require({str(path): hashlib.sha256(path.read_bytes()).hexdigest() for path in state.rglob('*') if path.is_file()} == before,
            'rejected state-directory reuse changed committed files')
    base = request('negative', path_sql, path_tables, path_events, 'cardinality', 'reference_ordered_v1')
    negatives = []
    for label, extra in [('duplicate-input', [path_events[0]]), ('absent-delete', [event('-', 'r0', 4, 5)])]:
        data = copy.deepcopy(base)
        data['events'] = path_events + extra
        negatives.append((label, set_binary, data))
    data = copy.deepcopy(base)
    data['limits']['output_records'] = 0
    negatives.append(('output-cap', set_binary, data))
    data = copy.deepcopy(base)
    data['native']['physical_options'] = None
    negatives.append(('null-options', set_binary, data))
    data = copy.deepcopy(base)
    data['output'] = 'compressed_bag'
    del data['native']['mode']
    data['native'].update(transaction_batch_size=3, observation_interval=4)
    negatives.append(('unaligned-net-observation', rows_binary, data))
    data = copy.deepcopy(preserved)
    data['session']['durability'] = 'volatile'
    negatives.append(('volatile-checkpoint', session_binary, data))
    for label, binary, data in negatives:
        invoke(label, binary, data, False)
    # These exact integer boundaries also catch rounded schema literals produced
    # accidentally through a host language's double-precision JSON serializer.
    data = copy.deepcopy(base)
    data['events'][0]['values'][0] = (1 << 63)-1
    data['limits']['output_bytes'] = (1 << 64)-1
    require(schema.is_valid(data), 'schema rejects exact signed/unsigned limits')
    data['events'][0]['values'][0] = 1 << 63
    require(not schema.is_valid(data), 'schema admits int64 overflow')
    data['events'][0]['values'][0] = -(1 << 63)-1
    require(not schema.is_valid(data), 'schema admits int64 underflow')
    data['events'][0]['values'][0] = -(1 << 63)
    data['limits']['output_bytes'] = 1 << 64
    require(not schema.is_valid(data), 'schema admits uint64 overflow')

    # Repeated logical-owner measurement is a functional clock/output control.
    # Concurrent builds make these clocks ineligible for performance analysis.
    for label, binary, output in [('set', set_binary, 'cardinality'), ('rows', rows_binary, 'compressed_bag'),
                                   ('session', session_binary, 'delta_and_snapshot')]:
        data = request('repeat-' + label, path_sql, path_tables, path_events, output, 'reference_ordered_v1')
        if label == 'rows':
            del data['native']['mode']
        elif label == 'session':
            data['session'] = {'output_action': 'serialize', 'transport_batch_size': 3, 'durability': 'volatile'}
        data.update(command='measure', warmup_passes=1, measured_passes=2)
        report = invoke('repeat-' + label, binary, data)
        require(len(report['passes']) == 3 and [row['warmup'] for row in report['passes']] == [True, False, False], 'repeat owners differ')
        for result in report['passes']:
            require(all(epoch['actual'] is None for epoch in result['epochs']), 'measurement captured a second result graph')
            require(type(result['loop_wall_ns']) is int and result['loop_wall_ns'] >= 0, 'measurement clock missing')
    (directory / 'result.json').write_text(json.dumps({'status': 'pass', 'commands': len(commands),
        'prefix_comparisons': comparisons, 'session_arms': len(session_arms), 'backends': 2,
        'performance_claim': False}, indent=2) + '\n')
    print(f'component runtime controls passed: {len(commands)} commands / {comparisons} prefixes')
    if temporary is not None:
        temporary.cleanup()


if __name__ == '__main__':
    main()
