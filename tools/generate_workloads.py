#!/usr/bin/env python3
"""Deterministic finite B02 workloads; relational/SQLite oracles do not use CROWN."""
from __future__ import annotations

import argparse
import collections
import hashlib
import itertools
import json
from pathlib import Path
import sqlite3

ROOT = Path(__file__).resolve().parents[1]
REGIMES = ('insert_only', 'delete_after_charged_load', 'global_fifo',
           'per_relation_fifo', 'mixed', 'adversarial_churn', 'rate_shift')
BACKENDS = ['reference_ordered_v1', 'indexed_chained_v1']
OUTPUT_MODES = ['maintenance', 'full_snapshot_each_epoch', 'delta_each_epoch']


def canonical(value):
    return json.dumps(value, ensure_ascii=False, sort_keys=True, separators=(',', ':'))


def sha(data):
    return hashlib.sha256(data).hexdigest()


def quote(identifier):
    return '"' + identifier.replace('"', '""') + '"'


def ordered(values):
    return sorted(values, key=canonical)


def acyclic(edges):
    """Independent finite GYO recognition, including repeated/empty scopes."""
    edges = [set(edge) for edge in edges]
    while edges:
        contained = next((i for i, edge in enumerate(edges)
                          if any(i != j and edge <= other for j, other in enumerate(edges))), None)
        if contained is not None:
            edges.pop(contained)
            continue
        counts = collections.Counter(v for edge in edges for v in edge)
        reduced = [edge - {v for v in edge if counts[v] <= 1} for edge in edges]
        reduced = [edge for edge in reduced if edge]
        if reduced == edges:
            return False
        edges = reduced
    return True


def query(identifier, scopes, head=None, *, tables=None, tags=(), hot=(), text=False,
          mode='set', expected='admitted'):
    variables = list(dict.fromkeys(v for scope in scopes for v in scope))
    if mode == 'count':
        head = []  # No grouping keys; the output expression is recorded below.
    elif head is None:
        head = variables
    tables = tables or [f'r{i}' for i in range(len(scopes))]
    atoms = [{'alias': f'a{i}', 'table': table, 'variables': list(scope)}
             for i, (scope, table) in enumerate(zip(scopes, tables))]
    physical = {}
    for atom in atoms:
        columns = [{'name': f'c{i}', 'type': 'string' if text else 'int64', 'nullable': False,
                    **({'collation': 'binary'} if text else {})}
                   for i in range(len(atom['variables']))]
        if atom['table'] in physical and physical[atom['table']] != columns:
            raise ValueError('self-join physical layout mismatch')
        physical[atom['table']] = columns
    first, conditions = {}, []
    for atom in atoms:
        for i, variable in enumerate(atom['variables']):
            ref = quote(atom['alias']) + '.' + quote(f'c{i}')
            if variable in first:
                conditions.append(ref + ' = ' + first[variable])
            else:
                first[variable] = ref
    body = ' FROM ' + ' CROSS JOIN '.join(quote(a['table']) + ' AS ' + quote(a['alias']) for a in atoms)
    if conditions:
        body += ' WHERE ' + ' AND '.join(conditions)
    if mode == 'count':
        sql = 'SELECT COUNT(*)' + body + ';\n'
    elif not head:
        sql = 'SELECT EXISTS(SELECT 1' + body + ');\n'
    else:
        sql = ('SELECT ' + ('DISTINCT ' if mode == 'set' else '') +
               ', '.join(first[v] + ' AS ' + quote(v) for v in head) + body + ';\n')
    catalog = {'schema_version': 1, 'catalog': {'version': 1, 'tables': [
        {'name': name, 'source_schema_version': 1, 'columns': columns, 'constraints': [],
         'statistics': {'distinct_counts': []}, 'key_hints': []} for name, columns in physical.items()]}}
    return {'id': identifier, 'atoms': atoms, 'variables': variables, 'head': list(head),
            'tags': list(tags), 'hot': list(hot), 'text': text, 'mode': mode,
            'expected': expected, 'sql': sql, 'catalog': catalog}


def specifications():
    path = lambda n: [[f'x{i}', f'x{i+1}'] for i in range(n)]
    star = lambda n: [['hub', f'leaf{i}'] for i in range(n)]
    return [
        query('singleton', [['x']], tags=['singleton', 'output_small']),
        query('hidden_witnesses', [['key', 'witness']], ['key'], hot=['key'], tags=['proper_projection', 'many_witnesses', 'output_small']),
        query('full_path_2', path(2), tags=['path', 'full_head', 'query_size_axis']),
        query('full_path_4', path(4), tags=['path', 'full_head', 'query_size_axis']),
        query('projected_prefix_path', path(4), ['x0', 'x1'], tags=['path', 'proper_projection', 'hidden_branch']),
        query('boolean_path', path(3), [], tags=['boolean', 'path']),
        query('full_star_3', star(3), hot=['hub'], tags=['star', 'high_fanout', 'output_large', 'query_size_axis']),
        query('full_star_6', star(6), hot=['hub'], tags=['star', 'high_fanout', 'output_large', 'query_size_axis']),
        query('projected_star', star(3), ['hub'], hot=['hub'], tags=['star', 'proper_projection', 'many_witnesses', 'output_small']),
        query('composite_separator', [['a', 'b', 'c'], ['a', 'b', 'd']], tags=['composite_key', 'arity_above_two']),
        query('nested_scopes', [['a', 'b', 'c'], ['a', 'b'], ['a']], tags=['nested_scopes', 'contained_scope', 'arity_above_two']),
        query('equal_scopes', [['a', 'b'], ['a', 'b']], tags=['repeated_scope']),
        query('wide_arity_8', [[f'v{i}' for i in range(8)]], tags=['high_arity', 'query_size_axis']),
        query('wide_strings', [['key', 'name', 'payload']], text=True, tags=['wide_tuple', 'utf8', 'embedded_nul', 'arity_above_two']),
        query('disconnected_full', [['a', 'b'], ['c', 'd']], tags=['disconnected', 'empty_separator', 'full_head']),
        query('disconnected_projected', [['a', 'b'], ['c', 'd']], ['a', 'c'], tags=['disconnected', 'proper_projection']),
        query('boolean_disconnected', [['a'], ['b']], [], tags=['boolean', 'disconnected']),
        query('self_join_2', path(2), tables=['edge'] * 2, tags=['self_join', 'loop', 'new_new_cross_term']),
        query('self_join_3', path(3), tables=['edge'] * 3, tags=['self_join', 'multiple_aliases']),
        query('repeated_variable', [['x', 'x'], ['x', 'y']], tags=['local_equality', 'dangling_branch']),
        query('cyclic_triangle_control', [['a', 'b'], ['b', 'c'], ['a', 'c']], expected='cyclic_body', tags=['negative_control', 'cyclic']),
        query('nonfree_endpoint_control', path(2), ['x0', 'x2'], expected='non_free_connex', tags=['negative_control', 'non_free_connex']),
        query('bag_projection_control', [['key', 'witness']], ['key'], hot=['key'], mode='bag', expected='unsupported_semantics', tags=['negative_control', 'bag']),
        query('aggregate_count_control', [['key', 'witness']], mode='count', expected='unsupported_semantics', tags=['negative_control', 'aggregate']),
    ]


def pool(spec, scale):
    result = {table['name']: [] for table in spec['catalog']['catalog']['tables']}
    variables = spec['variables']
    for atom in spec['atoms']:
        for index in range(3 * scale):
            values = []
            for variable in atom['variables']:
                value = 0 if variable in spec['hot'] else index + 7 * variables.index(variable)
                if spec['text']:
                    value = f'{value}:雪\x00' + ('wide/' * (16 * scale))
                values.append(value)
            row = tuple(values)
            if row not in result[atom['table']]:
                result[atom['table']].append(row)
    if len(result) == 1 and len(spec['atoms']) > 1:
        # One physical loop reaches every alias in the same epoch.
        result[next(iter(result))] = [(0, 0), (0, 1), (1, 1), (1, 2), (2, 0)]
    if spec['id'] == 'repeated_variable':
        result['r0'].append((1001, 1002))  # Local adapter filters it out.
    return result


def trace(spec, regime, seed, scale):
    rows = pool(spec, scale)
    entries = [(table, row) for table, values in rows.items() for row in values]
    # Interleave physical tables so prefixes exercise empty/dangling branches.
    entries = sorted(entries, key=lambda x: (rows[x[0]].index(x[1]), x[0]))
    events = []
    def emit(operation, item, phase='workload'):
        events.append((operation, item[0], list(item[1]), phase))
    if regime == 'insert_only':
        for item in entries: emit('insert', item)
    elif regime == 'delete_after_charged_load':
        for item in entries: emit('insert', item, 'charged_load')
        for item in reversed(entries): emit('delete', item, 'delete_phase')
    elif regime == 'global_fifo':
        queue = collections.deque()
        for item in entries:
            emit('insert', item); queue.append(item)
            if len(queue) > 3: emit('delete', queue.popleft())
        for item in queue: emit('delete', item)
    elif regime == 'per_relation_fifo':
        for item in entries: emit('insert', item)
        # Table-grouped deletion deliberately need not follow global age order.
        for table, values in reversed(list(rows.items())):
            for row in values: emit('delete', (table, row))
    elif regime == 'adversarial_churn':
        for item in entries: emit('insert', item, 'charged_load')
        for item in [entries[0], entries[-1]] * 3:
            emit('insert', item); emit('delete', item); emit('delete', item); emit('insert', item)
    elif regime in ('mixed', 'rate_shift'):
        for item in entries: emit('insert', item, 'charged_load')
        for phase in range(2):
            choices = entries if regime == 'mixed' else [(t, r) for t, r in entries if t == list(rows)[phase % len(rows)]]
            if regime == 'rate_shift' and len(rows) == 1:
                choices = [entries[0 if phase == 0 else -1]]
            choices = sorted(choices, key=lambda x: sha(f'{seed}:{spec["id"]}:{phase}:{canonical(x)}'.encode()))
            for item in choices[:max(3, len(entries) // 2)]:
                emit('delete', item, f'phase_{phase}'); emit('insert', item, f'phase_{phase}')
        emit('insert', entries[0]); emit('delete', (entries[0][0], tuple(-9999 if isinstance(v, int) else 'absent' for v in entries[0][1])))
    else:
        raise ValueError(regime)
    return events


def relational(spec, database):
    assignments = [{}]
    for atom in spec['atoms']:
        next_assignments = []
        for assignment in assignments:
            for row in database[atom['table']]:
                joined = dict(assignment)
                for variable, value in zip(atom['variables'], row):
                    if variable in joined and joined[variable] != value:
                        break
                    joined[variable] = value
                else:
                    next_assignments.append(joined)
        assignments = next_assignments
        if len(assignments) > 100_000:
            raise ValueError('finite oracle assignment limit exceeded; reduce scale')
    if spec['mode'] == 'count': return [(len(assignments),)]
    if not spec['head']: return [(bool(assignments),)]
    rows = [tuple(a[v] for v in spec['head']) for a in assignments]
    return ordered(set(rows) if spec['mode'] == 'set' else rows)


def oracle(spec, events):
    database = {table['name']: set() for table in spec['catalog']['catalog']['tables']}
    connection = sqlite3.connect(':memory:')
    for table in spec['catalog']['catalog']['tables']:
        columns = ', '.join(quote(c['name']) + (' TEXT' if c['type'] == 'string' else ' INTEGER') + ' NOT NULL' for c in table['columns'])
        connection.execute('CREATE TABLE ' + quote(table['name']) + '(' + columns + ')')
    def evaluate():
        expected = relational(spec, database)
        actual = list(connection.execute(spec['sql']))
        if not spec['head'] and spec['mode'] != 'count': actual = [(bool(v[0]),) for v in actual]
        if ordered(actual) != ordered(expected): raise ValueError('independent relational/SQLite disagreement: ' + spec['id'])
        return ordered(expected)
    before = evaluate()
    initial, frames = before, []
    for sequence, (operation, table, values, phase) in enumerate(events, 1):
        row = tuple(values); existed = row in database[table]
        if operation == 'insert' and not existed:
            database[table].add(row)
            connection.execute('INSERT INTO ' + quote(table) + ' VALUES(' + ','.join('?' for _ in values) + ')', values)
        elif operation == 'delete' and existed:
            database[table].remove(row)
            connection.execute('DELETE FROM ' + quote(table) + ' WHERE ' + ' AND '.join(quote(f'c{i}') + ' = ?' for i in range(len(values))), values)
        after = evaluate()
        signed = []
        if spec['mode'] == 'set':
            signed = [{'operation': op, 'values': list(row)} for op, rows in
                      [('insert', set(after) - set(before)), ('delete', set(before) - set(after))] for row in ordered(rows)]
        frames.append({'sequence': sequence, 'phase': phase, 'physical_changed': existed != (operation == 'insert'),
                       'current_rows': after, 'signed_delta': signed})
        before = after
    connection.close()
    return {'schema_version': 1, 'query': spec['id'], 'oracle': 'independent_relational_and_sqlite',
            'initial_rows': initial, 'epochs': frames}


def verify_regime(events, regime):
    """Validate actual trace promises, independently of the scheduling branches."""
    live = {}; queues = collections.defaultdict(collections.deque); global_queue = collections.deque()
    for operation, table, raw, phase in events:
        row = tuple(raw); item = (table, row); present = item in live
        if regime == 'insert_only' and operation != 'insert': raise ValueError('insert-only violation')
        if regime == 'delete_after_charged_load' and ((phase == 'charged_load') != (operation == 'insert')):
            raise ValueError('uncharged loading or deletion-phase insertion')
        if operation == 'insert' and not present:
            live[item] = True; queues[table].append(row); global_queue.append(item)
        elif operation == 'delete' and present:
            if regime == 'global_fifo' and global_queue[0] != item: raise ValueError('global FIFO violation')
            if regime == 'per_relation_fifo' and queues[table][0] != row: raise ValueError('relation FIFO violation')
            del live[item]; queues[table].remove(row); global_queue.remove(item)


def build(seed=20261110, scale=1, selected=None):
    if not 1 <= scale <= 8 or not 0 <= seed < 2**64: raise ValueError('seed/scale outside finite generator bounds')
    files, queries, workloads = {}, [], []
    def put(path, value, raw=False):
        content = value if raw else json.dumps(value, ensure_ascii=False, sort_keys=True, indent=2) + '\n'
        files[path] = content.encode('utf-8')
        return {'path': path, 'sha256': sha(files[path])}
    specs = specifications()
    if selected is not None:
        if not selected or len(set(selected)) != len(selected) or set(selected) - {s['id'] for s in specs}:
            raise ValueError('unknown or duplicate selected query')
        specs = [s for s in specs if s['id'] in selected]
    for spec in specs:
        identifier = spec['id']; prefix = 'queries/' + identifier + '/'
        body = [a['variables'] for a in spec['atoms']]
        body_acyclic = acyclic(body)
        queries.append({'id': identifier, 'sql': put(prefix + 'query.sql', spec['sql'], True),
                        'catalog': put(prefix + 'catalog.json', spec['catalog']),
                        'semantics': {'input': 'physical_set', 'output': 'aggregate_count' if spec['mode'] == 'count' else spec['mode'],
                                      'boolean_exists': not spec['head'] and spec['mode'] != 'count'}, 'head': spec['head'],
                        'output_expressions': ['COUNT(*)'] if spec['mode'] == 'count' else ['EXISTS'] if not spec['head'] else spec['head'],
                        'structure': {'atoms': spec['atoms'], 'variables': spec['variables'],
                                      'body_alpha_acyclic': body_acyclic,
                                      'free_connex': body_acyclic and acyclic(body + [spec['head']]),
                                      'tags': spec['tags'], 'distribution': 'hot_key' if spec['hot'] else
                                      'loop_and_chain_keys' if len({a['table'] for a in spec['atoms']}) < len(spec['atoms']) else 'coherent_distinct_keys'},
                        'expected_admission': spec['expected'],
                        'expected_backends': BACKENDS if spec['expected'] == 'admitted' else [],
                        'output_modes': OUTPUT_MODES if spec['expected'] == 'admitted' else [],
                        'origin': 'new_synthetic_not_a_legacy_benchmark'})
        regimes = REGIMES if spec['expected'] == 'admitted' else ('insert_only',)
        for regime in regimes:
            events = trace(spec, regime, seed, scale); verify_regime(events, regime)
            source = 'b02-' + identifier + '-' + regime
            records = [{'schema_version': 1, 'catalog_version': 1, 'source_schema_version': 1,
                        'sequence': i, 'table': table, 'operation': op, 'values': values,
                        'source_position': {'source': source, 'offset': i}}
                       for i, (op, table, values, _) in enumerate(events, 1)]
            expected = oracle(spec, events)
            prefix = f'traces/{identifier}/{regime}/'
            workloads.append({'id': identifier + '/' + regime, 'query': identifier, 'regime': regime,
                              'events': put(prefix + 'events.template.jsonl', ''.join(canonical(r) + '\n' for r in records), True),
                              'oracle': put(prefix + 'expected.json', expected), 'events_count': len(records),
                              'charged_load_events': sum(e[3] == 'charged_load' for e in events),
                              'max_result_rows': max(len(x['current_rows']) for x in expected['epochs']),
                              'initial_state': 'empty_all_tables', 'source_id': source,
                              'update_contract': 'one_ordered_atomic_physical_set_update_per_record',
                              'noop_policy': 'duplicate_insert_and_absent_delete_commit_empty_epochs',
                              'catalog_binding': 'prepare_workflow_input.py_with_native_canonical_catalog',
                              'license_record': 'synthetic_local', 'phase_labels': list(dict.fromkeys(e[3] for e in events))})
    assets = {name: {'path': path, 'sha256': sha((ROOT / path).read_bytes())} for name, path in
              [('legacy_inventory', 'benchmarks/legacy/manifest.json'), ('external_imports', 'benchmarks/external_imports.json')]}
    manifest = {'schema_version': 1, 'kind': 'crown_workload_manifest', **assets,
                'generator': {'path': 'tools/generate_workloads.py', 'sha256': sha(Path(__file__).read_bytes()),
                              'seed': seed, 'scale': scale, 'query_ids': [s['id'] for s in specs],
                              'ordering': 'UTF8_JSON_SHA256_no_runtime_random_hash'},
                'licenses': [{'id': 'synthetic_local', 'origin': 'new_deterministic_synthetic_records_no_external_dataset',
                              'data_license': 'no_separate_license_grant_recorded',
                              'project_license': 'A02_undecided_local_development_only',
                              'redistribution': 'not_authorized_by_this_manifest'}],
                'regimes': list(REGIMES), 'queries': queries, 'workloads': workloads,
                'coverage_limits': ['finite_mechanism_corpus_not_all_free_connex_coverage',
                                    'negative_controls_are_not_native_workloads',
                                    'trace_regime_is_not_an_engine_complexity_guarantee',
                                    'loading_is_input_work_not_free_preload',
                                    'no_timing_or_baseline_reproduction_claim',
                                    'external_dataset_imports_require_separate_provenance_and_license_records']}
    put('manifest.json', manifest)
    return files


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--output', type=Path, required=True)
    parser.add_argument('--seed', type=int, default=20261110)
    parser.add_argument('--scale', type=int, default=1)
    parser.add_argument('--query', action='append', help='select a family for a separate size/seed experiment; repeatable')
    parser.add_argument('--check', action='store_true', help='compare an existing pack without changing it')
    args = parser.parse_args(); files = build(args.seed, args.scale, args.query)
    if args.check:
        actual = {str(p.relative_to(args.output)): p.read_bytes() for p in args.output.rglob('*') if p.is_file()}
        if actual != files: raise ValueError('pack differs from deterministic generator output')
    else:
        args.output.mkdir(parents=True, exist_ok=False)
        for name, content in files.items():
            path = args.output / name; path.parent.mkdir(parents=True, exist_ok=True); path.write_bytes(content)
    count = len(json.loads(files['manifest.json'])['queries'])
    print(f'B02 {count} query definitions, {len(files)} reproducible files; seed={args.seed} scale={args.scale}')


if __name__ == '__main__':
    main()
