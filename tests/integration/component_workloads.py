#!/usr/bin/env python3
"""Check exact SQLite component-workload oracles without native processes."""
from fractions import Fraction
from pathlib import Path
import sys
import unittest

sys.dont_write_bytecode = True
ROOT = Path(__file__).resolve().parents[2]
sys.path.insert(0, str(ROOT / 'tools'))

from component_workloads import (
    base_request,
    bind_oracle,
    build_baseline_cohorts,
    build_operational_cohorts,
    catalog,
    evaluate_request,
    event,
    layered_events,
    numeric,
    operational_events,
)


def _changed_paths(left, right, prefix=''):
    """Return changed JSON object paths, treating arrays as one field."""
    if isinstance(left, dict) and isinstance(right, dict):
        changed = []
        for key in sorted(set(left) | set(right)):
            path = f'{prefix}.{key}' if prefix else key
            if key not in left or key not in right:
                changed.append(path)
            else:
                changed.extend(_changed_paths(left[key], right[key], path))
        return changed
    if type(left) is not type(right) or left != right:
        return [prefix]
    return []


def _arm(manifest, identifier):
    """Select exactly one named arm from a finite cohort manifest."""
    found = [row for row in manifest['arms'] if row['id'] == identifier]
    if len(found) != 1:
        raise AssertionError(f'expected one arm {identifier!r}, found {len(found)}')
    return found[0]


class NumericFormattingTest(unittest.TestCase):
    """Pin exact decimal half-away-from-zero formatting, including long scales."""

    def test_fraction_rounding_ties_zero_and_eighteen_places(self):
        """Check exact rounding at ties, zero, and the 18-place boundary."""
        cases = [
            (Fraction(1, 2), 0, '1'),
            (Fraction(-1, 2), 0, '-1'),
            (Fraction(1, 200), 2, '0.01'),
            (Fraction(-1, 200), 2, '-0.01'),
            (Fraction(1, 2000), 2, '0'),
            (Fraction(-1, 2000), 2, '0'),
            (Fraction(0), 18, '0'),
            (Fraction(1, 6), 18, '0.166666666666666667'),
            (Fraction(-1, 6), 18, '-0.166666666666666667'),
            (Fraction(1, 2 * 10**18), 18, '0.000000000000000001'),
            (Fraction(-1, 2 * 10**18), 18, '-0.000000000000000001'),
            (Fraction(1234567890123456789, 10**18), 18, '1.234567890123456789'),
            (Fraction(12345678901234567890), 0, '12345678901234567890'),
        ]
        for value, scale, expected in cases:
            with self.subTest(value=value, scale=scale):
                self.assertEqual(numeric(value, scale), {'decimal': expected})


class SqlitePrefixOracleTest(unittest.TestCase):
    """Check independent physical-prefix rows and exact integer aggregates."""

    def test_cancelling_and_negative_edits_preserve_set_but_change_bag(self):
        """Check all-prefix set deltas while physical edits change bag counts."""
        sql = 'SELECT r0.c0 FROM r0,r1 WHERE r0.c1=r1.c0'
        tables = catalog({'r0': ('c0', 'c1'), 'r1': ('c0', 'c1')})
        events = [
            event('+', 'r0', (1, 10)),
            event('+', 'r0', (2, 10)),
            event('+', 'r1', (10, -4)),
            event('+', 'r1', (10, 3)),
            event('+', 'r1', (10, 0)),
            event('+', 'r1', (10, 99)),
            event('-', 'r1', (10, 99)),
            event('-', 'r1', (10, 3)),
            event('-', 'r1', (10, -4)),
            event('-', 'r1', (10, 0)),
        ]
        request = base_request('prefix-cancel', sql, tables, events, 'compressed_bag')
        result = evaluate_request(request, bind_oracle(sql))
        self.assertEqual(result['initial']['rows'], [])
        self.assertEqual(result['initial']['bag'], [])

        frames = result['epochs']
        self.assertEqual(frames[2]['rows'], [[1], [2]])
        self.assertEqual(frames[2]['bag'], [
            {'values': [1], 'multiplicity': 1},
            {'values': [2], 'multiplicity': 1},
        ])
        self.assertEqual(frames[2]['delta'], [
            {'operation': '+', 'values': [1]},
            {'operation': '+', 'values': [2]},
        ])
        self.assertEqual(frames[3]['cardinality'], 2)
        self.assertEqual(frames[3]['bag'][0]['multiplicity'], 2)
        self.assertEqual(frames[3]['delta'], [])
        self.assertEqual(frames[4]['bag'][0]['multiplicity'], 3)
        self.assertEqual(frames[5]['bag'][0]['multiplicity'], 4)
        self.assertEqual(frames[6]['bag'][0]['multiplicity'], 3)
        self.assertEqual(frames[6]['delta'], [])
        self.assertEqual(frames[7]['bag'][0]['multiplicity'], 2)
        self.assertEqual(frames[8]['bag'][0]['multiplicity'], 1)
        self.assertEqual(frames[9]['rows'], [])
        self.assertEqual(frames[9]['bag'], [])
        self.assertEqual(frames[9]['delta'], [
            {'operation': '-', 'values': [1]},
            {'operation': '-', 'values': [2]},
        ])

    def test_count_sum_and_average_use_exact_integer_sqlite_state(self):
        """Check exact aggregate replacement values across group membership changes."""
        sql = 'SELECT r0.c0,COUNT(*),SUM(r0.c1),AVG(r0.c1) FROM r0,r1 WHERE r0.c1=r1.c0 GROUP BY r0.c0'
        oracle_sql = 'SELECT r0.c0,COUNT(*),SUM(r0.c1),SUM(r0.c1),COUNT(r0.c1) FROM r0,r1 WHERE r0.c1=r1.c0 GROUP BY r0.c0'
        tables = catalog({'r0': ('c0', 'c1'), 'r1': ('c0', 'c1')})
        events = [
            event('+', 'r0', (7, 50)),
            event('+', 'r0', (7, 60)),
            event('+', 'r1', (50, -2)),
            event('+', 'r1', (50, 1)),
            event('+', 'r1', (60, 3)),
            event('+', 'r1', (60, 4)),
            event('-', 'r1', (50, -2)),
            event('+', 'r0', (8, -10)),
            event('+', 'r0', (8, -20)),
            event('+', 'r1', (-10, 9)),
            event('+', 'r1', (-20, -5)),
            event('+', 'r1', (-20, 7)),
            event('-', 'r0', (7, 50)),
            event('-', 'r0', (7, 60)),
        ]
        request = base_request('aggregate-prefix', sql, tables, events, 'groups_full')
        specification = bind_oracle(sql, 'aggregate', oracle_sql=oracle_sql, key_columns=[0], outputs=[
            {'kind': 'integer', 'column': 0},
            {'kind': 'integer', 'column': 1},
            {'kind': 'numeric', 'column': 2},
            {'kind': 'average', 'sum_column': 3, 'count_column': 4, 'scale': 18},
        ])
        result = evaluate_request(request, specification)
        self.assertEqual(result['initial']['groups'], [])
        self.assertEqual(result['epochs'][4]['groups'], [{
            'key': [7],
            'values': [7, 3, {'decimal': '160'}, {'decimal': '53.333333333333333333'}],
        }])
        self.assertEqual(result['epochs'][6]['groups'], [{
            'key': [7],
            'values': [7, 3, {'decimal': '170'}, {'decimal': '56.666666666666666667'}],
        }])
        self.assertEqual(result['epochs'][11]['groups'], [
            {'key': [7], 'values': [7, 3, {'decimal': '170'}, {'decimal': '56.666666666666666667'}]},
            {'key': [8], 'values': [8, 3, {'decimal': '-50'}, {'decimal': '-16.666666666666666667'}]},
        ])
        self.assertEqual(result['epochs'][12]['groups'], [
            {'key': [7], 'values': [7, 2, {'decimal': '120'}, {'decimal': '60'}]},
            {'key': [8], 'values': [8, 3, {'decimal': '-50'}, {'decimal': '-16.666666666666666667'}]},
        ])
        self.assertEqual(result['epochs'][13]['groups'], [{
            'key': [8],
            'values': [8, 3, {'decimal': '-50'}, {'decimal': '-16.666666666666666667'}],
        }])
        self.assertEqual(result['epochs'][13]['replacements'], [{
            'key': [7],
            'before': [7, 2, {'decimal': '120'}, {'decimal': '60'}],
            'after': None,
        }])

    def test_duplicate_insert_and_absent_erase_are_rejected(self):
        """Reject a repeated live fact and a deletion of a missing fact."""
        sql = 'SELECT c0 FROM r0'
        tables = catalog({'r0': ('c0', 'c1')})
        rejected = [
            [event('+', 'r0', (1, 2)), event('+', 'r0', (1, 2))],
            [event('-', 'r0', (1, 2))],
        ]
        for events in rejected:
            with self.subTest(events=events):
                request = base_request('invalid-unit-set', sql, tables, events, 'compressed_bag')
                with self.assertRaises(ValueError):
                    evaluate_request(request, bind_oracle(sql))

    def test_invalid_layer_families_and_cohort_bounds_are_rejected(self):
        """Reject unsupported families and malformed finite width/cycle/scale inputs."""
        with self.assertRaises(ValueError):
            layered_events('unknown', 2)
        with self.assertRaises(ValueError):
            layered_events('l3_full_rows', 0)
        with self.assertRaises(ValueError):
            layered_events('l3_full_rows', 9)
        with self.assertRaises(ValueError):
            layered_events('l3_full_rows', True)
        with self.assertRaises(ValueError):
            layered_events('l3_full_rows', 2, 0)
        with self.assertRaises(ValueError):
            layered_events('l3_full_rows', 2, 17)
        with self.assertRaises(ValueError):
            layered_events('l3_full_rows', 2, True)
        with self.assertRaises(ValueError):
            layered_events('l3_full_rows', 2, 1.0)
        with self.assertRaises(ValueError):
            operational_events(0, 1)
        with self.assertRaises(ValueError):
            operational_events(2, 0)
        with self.assertRaises(ValueError):
            operational_events(2, 1.0)
        with self.assertRaises(ValueError):
            build_operational_cohorts((2,), True)
        with self.assertRaises(ValueError):
            build_operational_cohorts((2.0,), 1)
        with self.assertRaises(ValueError):
            build_baseline_cohorts((2,), 0)
        with self.assertRaises(ValueError):
            build_operational_cohorts(())
        with self.assertRaises(ValueError):
            build_baseline_cohorts(())
        with self.assertRaises(ValueError):
            build_operational_cohorts((2, 2), 1)
        with self.assertRaises(ValueError):
            build_baseline_cohorts((2, 2), 1)
        with self.assertRaises(ValueError):
            numeric(Fraction(1, 2), -1)
        with self.assertRaises(ValueError):
            numeric(Fraction(1, 2), 39)
        with self.assertRaises(ValueError):
            numeric(Fraction(1, 2), True)

    def test_full_head_snapshot_exposes_the_peak_output_cardinality(self):
        """Check loaded and transient full-head row counts at maximum width."""
        width = 8
        manifest = build_operational_cohorts((width,), 1)
        arm_id = f'w{width}-reference_ordered_v1-full_discard'
        full = _arm(manifest, arm_id)
        serialized = _arm(manifest, f'w{width}-reference_ordered_v1-full_serialize')
        self.assertEqual(full['request']['output'], 'delta_and_snapshot')
        self.assertEqual(full['request']['program']['sql'], serialized['request']['program']['sql'])
        self.assertEqual(full['request']['session']['output_action'], 'discard')
        self.assertEqual(serialized['request']['session']['output_action'], 'serialize')
        self.assertEqual(full['oracle'], serialized['oracle'])

        result = evaluate_request(full['request'], full['oracle'])
        loaded_end = sum(row['phase'] == 'charged_load' for row in full['request']['events'])
        self.assertEqual(loaded_end, 3 * width**2)
        self.assertEqual(result['epochs'][loaded_end - 1]['cardinality'], 2 * width**3)
        self.assertEqual(result['epochs'][loaded_end]['cardinality'], 2 * width**3 + width)
        self.assertEqual(max(frame['cardinality'] for frame in result['epochs']), 2 * width**3 + width)

    def test_net_batching_retains_common_source_endpoints_including_final_partial(self):
        """Compare common four-event endpoints and the final partial endpoint."""
        width = 3
        manifest = build_operational_cohorts((width,), 1)
        stem = f'w{width}-reference_ordered_v1-'
        single = _arm(manifest, stem + 'rows_single')
        net = _arm(manifest, stem + 'rows_net')
        self.assertEqual(single['request']['events'], net['request']['events'])
        self.assertEqual(single['request']['native']['observation_interval'], 4)
        self.assertEqual(net['request']['native']['observation_interval'], 4)
        self.assertEqual(single['request']['native']['transaction_batch_size'], 1)
        self.assertEqual(net['request']['native']['transaction_batch_size'], 4)

        single_result = evaluate_request(single['request'], single['oracle'])
        net_result = evaluate_request(net['request'], net['oracle'])
        total = len(single['request']['events'])
        expected_ends = list(range(4, total + 1, 4))
        if not expected_ends or expected_ends[-1] != total:
            expected_ends.append(total)
        self.assertEqual(expected_ends[-1], total)
        self.assertEqual([row['physical_input_end'] for row in single_result['epochs']], list(range(1, total + 1)))
        self.assertEqual([row['physical_input_end'] for row in net_result['epochs']], list(range(1, total + 1)))
        selected_single = [row for row in single_result['epochs'] if row['physical_input_end'] in expected_ends]
        selected_net = [row for row in net_result['epochs'] if row['physical_input_end'] in expected_ends]
        self.assertEqual(selected_single, selected_net)
        self.assertEqual(expected_ends, [4, 8, 12, 16, 20, 24, 28, 32, 36, total])

    def test_comparison_paths_and_baseline_cd_mode(self):
        """Check dotted changes and scalar CD baseline requests for both backends."""
        manifest = build_operational_cohorts((2,), 1)
        arms = {row['id']: row for row in manifest['arms']}
        comparisons = manifest['comparisons']
        self.assertTrue(comparisons)
        for comparison in comparisons:
            with self.subTest(comparison=comparison['id']):
                before = arms[comparison['baseline']]
                after = arms[comparison['variant']]
                changed = _changed_paths(before['request'], after['request'])
                if before['adapter'] != after['adapter']:
                    changed.append('adapter')
                self.assertEqual(sorted(changed), comparison['changed_paths'])

        baseline = build_baseline_cohorts((2,), 1)
        cd_native = [row for row in baseline['arms']
                     if row['request']['query_family'] == 'l5_distinct_count' and row['adapter'] == 'set']
        self.assertEqual({row['id'].rsplit('-', 1)[-1] for row in cd_native},
                         {'reference_ordered_v1', 'indexed_chained_v1'})
        for arm in cd_native:
            with self.subTest(baseline_arm=arm['id']):
                self.assertEqual(arm['request']['output'], 'cardinality')
                self.assertEqual(arm['request']['native']['mode'], 'delta')


if __name__ == '__main__':
    unittest.main()
