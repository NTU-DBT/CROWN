#!/usr/bin/env python3
"""Deterministic B05 size, structure, skew, output and fixed-live-set histories.

The B02 relational evaluator and SQLite independently check every epoch. These
finite inputs exercise mechanisms; they do not establish asymptotic bounds.
"""
from __future__ import annotations

import argparse
import collections
import json
from pathlib import Path

from generate_workloads import (BACKENDS, OUTPUT_MODES, ROOT, acyclic, canonical,
                                oracle, query, sha, verify_regime)

if ROOT != Path(__file__).resolve().parents[1]:
    raise ValueError('B05 generator and its B02 oracle must come from the same checkout')

FAMILIES = ('volume_full', 'volume_projected', 'empty_intersection',
            'fanout_full', 'fanout_projected', 'skew_hot', 'skew_balanced',
            'arity_1', 'arity_8', 'arity_32', 'path_2', 'path_4', 'path_6',
            'churn_fresh', 'churn_reuse', 'churn_projected', 'churn_star',
            'churn_path', 'churn_self_join')


def churn_case(family, scale):
    """Keep each query's physical live window fixed while replacing witnesses."""
    cycles = 16 * scale * scale
    row_kind = 'key_value'
    if family in ('churn_fresh', 'churn_reuse'):
        spec = query(family, [['x']])
        loaded = [('r0', (i,)) for i in range(8)]
        targets = ['r0']
        row_kind = 'single'
    elif family == 'churn_projected':
        spec = query(family, [['key', 'witness']], ['key'], hot=['key'])
        loaded = [('r0', (0, i)) for i in range(8)]
        targets = ['r0']
    elif family == 'churn_star':
        spec = query(family, [['hub', f'leaf{i}'] for i in range(3)], ['hub'], hot=['hub'])
        loaded = [(f'r{j}', (0, i)) for i in range(3) for j in range(3)]
        targets = ['r0', 'r1', 'r2']
    elif family == 'churn_path':
        spec = query(family, [[f'x{i}', f'x{i+1}'] for i in range(4)], ['x0', 'x1'])
        loaded = [(f'r{j}', (i, i)) for i in range(3) for j in range(4)]
        targets = ['r3']
    else:
        spec = query(family, [['x0', 'x1'], ['x1', 'x2']], tables=['edge', 'edge'])
        loaded = [('edge', (i, i)) for i in range(3)]
        targets = ['edge']
        row_kind = 'loop'
    events = [('insert', table, row, 'charged_load') for table, row in loaded]
    for i in range(cycles):
        value = 1000 if family == 'churn_reuse' else 1000 + i
        table = targets[i % len(targets)]
        row = (value,) if row_kind == 'single' else (value, value) if row_kind == 'loop' else (0, value)
        events.extend([('insert', table, row, 'churn_insert'), ('delete', table, row, 'churn_delete')])
        if (i + 1) & i == 0:
            events.append(('insert', loaded[0][0], loaded[0][1], 'sentinel_probe'))
    events.extend(('delete', table, row, 'drain') for table, row in loaded)
    events.append(('delete', loaded[0][0], (-1,) * len(loaded[0][1]), 'empty_probe'))
    return spec, events, dict(family=family, scale_selector=scale, axis='history_cycles',
        axis_value=cycles, stable_live_rows=len(loaded), transient_live_rows=len(loaded) + 1,
        distinct_churn_rows=cycles if family != 'churn_reuse' else 1,
        expected_final_rows=0, regime='adversarial_churn')


def case(family, scale):
    """Return a typed query, ordered charged events and explicit experiment axes."""
    events = []
    dimensions = {'family': family, 'scale_selector': scale}
    if family.startswith('volume_'):
        n = 8 * scale * scale
        projected = family == 'volume_projected'
        spec = query(family, [['key', 'witness']], ['key'] if projected else None, hot=['key'] if projected else [])
        rows = [(0 if projected else i, i) for i in range(n)]
        dimensions.update(axis='source_rows', axis_value=n, expected_final_rows=1 if projected else n)
    elif family == 'empty_intersection':
        n = 8 * scale * scale
        spec = query(family, [['x'], ['x']])
        events = [('insert', 'r0', (i,), 'charged_load') for i in range(n)]
        events.append(('insert', 'r1', (-1,), 'charged_load'))
        dimensions.update(axis='unmatched_rows', axis_value=n, expected_final_rows=0)
    elif family.startswith('fanout_'):
        n = 2 * scale
        projected = family == 'fanout_projected'
        spec = query(family, [['hub', f'leaf{i}'] for i in range(3)], ['hub'] if projected else None, hot=['hub'])
        events = [('insert', f'r{j}', (0, i), 'charged_load') for i in range(n) for j in range(3)]
        dimensions.update(axis='rows_per_branch', axis_value=n, branches=3,
                          expected_final_rows=1 if projected else n ** 3)
    elif family.startswith('skew_'):
        n = 8 * scale
        hot = family == 'skew_hot'
        spec = query(family, [['hub', 'left'], ['hub', 'right']], hot=['hub'] if hot else [])
        events = [('insert', f'r{j}', (0 if hot else i, i), 'charged_load') for i in range(n) for j in range(2)]
        dimensions.update(axis='rows_per_branch', axis_value=n, branches=2,
                          hot_key_fraction=1 if hot else 1 / n, expected_final_rows=n * n if hot else n)
    elif family.startswith('arity_'):
        width = int(family.split('_')[1])
        n = 16 * scale
        spec = query(family, [[f'v{i}' for i in range(width)]])
        rows = [tuple(i + j for j in range(width)) for i in range(n)]
        dimensions.update(axis='source_rows', axis_value=n, arity=width, expected_final_rows=n)
    elif family.startswith('path_'):
        atoms = int(family.split('_')[1])
        n = 4 * scale
        spec = query(family, [[f'x{i}', f'x{i+1}'] for i in range(atoms)])
        events = [('insert', f'r{j}', (i, i), 'charged_load') for i in range(n) for j in range(atoms)]
        dimensions.update(axis='rows_per_relation', axis_value=n, atoms=atoms,
                          expected_final_rows=n, height='read_actual_checked_plan_not_inferred_from_path_length')
    else:
        return churn_case(family, scale)
    if not events:
        events = [('insert', 'r0', row, 'charged_load') for row in rows]
    dimensions['regime'] = 'adversarial_churn' if family.startswith('churn_') else 'insert_only'
    return spec, events, dimensions


def live_counts(events):
    """Record exact live populations and the sum of per-table live high-waters."""
    live = collections.defaultdict(set)
    peaks = collections.Counter()
    counts = []
    for operation, table, values, _ in events:
        key = tuple(values)
        if operation == 'insert':
            live[table].add(key)
        else:
            live[table].discard(key)
        peaks[table] = max(peaks[table], len(live[table]))
        counts.append(sum(map(len, live.values())))
    return counts, sum(peaks.values())


def build(seed=20261114, scale=1, selected=None):
    """Produce a reproducible B02-format pack without native execution or output writes."""
    if not 1 <= scale <= 8 or not 0 <= seed < 2 ** 64:
        raise ValueError('seed/scale outside the finite B05 profile')
    selected = list(FAMILIES) if selected is None else selected
    if not selected or len(set(selected)) != len(selected) or set(selected) - set(FAMILIES):
        raise ValueError('unknown or duplicate B05 family')
    files, queries, workloads, axes = {}, [], [], []

    def put(path, value, raw=False):
        content = value if raw else json.dumps(value, ensure_ascii=False, sort_keys=True, indent=2) + '\n'
        files[path] = content.encode()
        return {'path': path, 'sha256': sha(files[path])}

    for family in FAMILIES:
        if family not in selected:
            continue
        spec, events, dimensions = case(family, scale)
        regime = dimensions['regime']
        verify_regime(events, regime)
        expected = oracle(spec, events)
        if len(expected['epochs'][-1]['current_rows']) != dimensions['expected_final_rows']:
            raise ValueError('analytic final cardinality disagrees with both independent oracles')
        if len(events) > 4096:
            raise ValueError('B05 profile exceeds the existing collector horizon')
        prefix = 'queries/' + family + '/'
        body = [a['variables'] for a in spec['atoms']]
        body_acyclic = acyclic(body)
        queries.append({'id': family, 'sql': put(prefix + 'query.sql', spec['sql'], True),
            'catalog': put(prefix + 'catalog.json', spec['catalog']),
            'semantics': {'input': 'physical_set', 'output': 'set', 'boolean_exists': False},
            'head': spec['head'], 'output_expressions': spec['head'],
            'structure': {'atoms': spec['atoms'], 'variables': spec['variables'],
                'body_alpha_acyclic': body_acyclic,
                'free_connex': body_acyclic and acyclic(body + [spec['head']]),
                'tags': ['b05', family], 'distribution': 'hot_key' if spec['hot'] else 'coherent_distinct_keys'},
            'expected_admission': 'admitted', 'expected_backends': BACKENDS,
            'output_modes': OUTPUT_MODES, 'origin': 'new_synthetic_not_a_legacy_benchmark'})
        source = f'b05-{family}-s{scale}'
        records = [{'schema_version': 1, 'catalog_version': 1, 'source_schema_version': 1,
            'sequence': i, 'table': table, 'operation': op, 'values': values,
            'source_position': {'source': source, 'offset': i}}
            for i, (op, table, values, _) in enumerate(events, 1)]
        prefix = f'traces/{family}/{regime}/'
        workloads.append({'id': family + '/' + regime, 'query': family, 'regime': regime,
            'events': put(prefix + 'events.template.jsonl', ''.join(canonical(r) + '\n' for r in records), True),
            'oracle': put(prefix + 'expected.json', expected), 'events_count': len(events),
            'charged_load_events': sum(e[3] == 'charged_load' for e in events),
            'max_result_rows': max(len(e['current_rows']) for e in expected['epochs']),
            'initial_state': 'empty_all_tables', 'source_id': source,
            'update_contract': 'one_ordered_atomic_physical_set_update_per_record',
            'noop_policy': 'duplicate_insert_and_absent_delete_commit_empty_epochs',
            'catalog_binding': 'prepare_workflow_input.py_with_native_canonical_catalog',
            'license_record': 'synthetic_local', 'phase_labels': list(dict.fromkeys(e[3] for e in events))})
        populations, slot_reference = live_counts(events)
        axes.append(dict(dimensions, case_id=family + '/' + regime, events=len(events),
            live_source_rows=populations, source_slot_reuse_reference=slot_reference,
            maximum_result_rows=workloads[-1]['max_result_rows']))
    put('axes.json', {'schema_version': 1, 'profile': 'b05_finite_stress_v1', 'cases': axes,
        'generator_dependencies': {'tools/generate_workloads.py': sha((ROOT / 'tools/generate_workloads.py').read_bytes())},
        'seed_scope': 'recorded provenance; this profile uses no random choices'})
    assets = {name: {'path': path, 'sha256': sha((ROOT / path).read_bytes())} for name, path in
        [('legacy_inventory', 'benchmarks/legacy/manifest.json'), ('external_imports', 'benchmarks/external_imports.json')]}
    manifest = {'schema_version': 1, 'kind': 'crown_workload_manifest', **assets,
        'generator': {'path': 'tools/generate_adversarial_workloads.py', 'sha256': sha(Path(__file__).read_bytes()),
            'seed': seed, 'scale': scale, 'query_ids': [q['id'] for q in queries],
            'ordering': 'UTF8_JSON_SHA256_no_runtime_random_hash'},
        'licenses': [{'id': 'synthetic_local', 'origin': 'new_deterministic_synthetic_records_no_external_dataset',
            'data_license': 'no_separate_license_grant_recorded', 'project_license': 'A02_undecided_local_development_only',
            'redistribution': 'not_authorized_by_this_manifest'}],
        'regimes': ['insert_only', 'adversarial_churn'], 'queries': queries, 'workloads': workloads,
        'coverage_limits': ['finite_stress_profile_not_a_complexity_or_speedup_theorem',
            'all_loading_is_charged_input_work', 'source_sets_and_nonnullable_integer_SQL_only',
            'native_requested_bytes_are_not_RSS', 'churn_has_at_most_1024_cycles_not_unbounded_history',
            'external_baselines_and_release_are_separate']}
    put('manifest.json', manifest)
    return files


def main():
    """Write a fresh pack, or compare every existing byte without changing it."""
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--output', type=Path, required=True)
    parser.add_argument('--seed', type=int, default=20261114)
    parser.add_argument('--scale', type=int, default=1)
    parser.add_argument('--query', action='append', choices=FAMILIES)
    parser.add_argument('--check', action='store_true')
    args = parser.parse_args()
    files = build(args.seed, args.scale, args.query)
    if args.check:
        actual = {str(p.relative_to(args.output)): p.read_bytes() for p in args.output.rglob('*') if p.is_file()}
        if actual != files:
            raise ValueError('B05 pack differs from deterministic source and independent oracles')
    else:
        args.output.mkdir(parents=True, exist_ok=False)
        for name, content in files.items():
            path = args.output / name
            path.parent.mkdir(parents=True, exist_ok=True)
            path.write_bytes(content)
    print(f'B05: {len(json.loads(files["manifest.json"])["queries"])} families, scale selector {args.scale}')


if __name__ == '__main__':
    main()
