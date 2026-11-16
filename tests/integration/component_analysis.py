#!/usr/bin/env python3
"""Pure exact-rational tests for the offline C03 component selector."""
from __future__ import annotations
import copy
from pathlib import Path
import sys
import unittest

ROOT = Path(sys.argv[1]).resolve() if len(sys.argv) > 1 else Path(__file__).resolve().parents[2]
sys.path.insert(0, str(ROOT / 'tools'))
import component_analysis as analysis


MAX_U64 = (1 << 64) - 1


def ratio(numerator, denominator=1):
    return {'numerator': numerator, 'denominator': denominator}


def estimate(key, value, issues=0, captured=10, budget=100, stamp=None):
    return {'structural_key': key, 'maintenance_ns': None, 'total_ns': value,
            'issues': issues, 'future_memory_unknown': True,
            'memory_budget_bytes': budget, 'asof_requested_bytes': captured,
            'observed_stamp': stamp or {'owner': 7, 'configuration': 1, 'reset': 1,
                                        'segment': 0, 'epoch': 8, 'interval_start': 0},
            'terms': []}


def report(rows, stop=0):
    return {'stop': stop, 'usage': {}, 'candidates': rows}


def height(key):
    return {'selected_key': key, 'availability': 'native_choice', 'stop': 0, 'reasons': []}


def valid_export():
    source, catalog, training, calibration = ('1' * 64, '2' * 64, '3' * 64, '4' * 64)
    keys = ['a', 'b']
    demand = [{'table': 0, 'operation': 'insert', 'inputs': 27},
              {'table': 0, 'operation': 'erase', 'inputs': 0},
              {'table': 1, 'operation': 'insert', 'inputs': 8},
              {'table': 1, 'operation': 'erase', 'inputs': 0},
              {'table': 2, 'operation': 'insert', 'inputs': 5},
              {'table': 2, 'operation': 'erase', 'inputs': 0}]
    variants=[]
    for name in ('full', 'sampled', 'stale', 'absent'):
        old={'owner': 17, 'configuration': 1, 'reset': 2, 'segment': 0,
             'epoch': 4, 'interval_start': 0}
        rows=[estimate(key, ratio(5 if key == 'a' else 3), stamp=old if name == 'stale' else None) for key in keys]
        if name == 'absent': rows=[]
        variants.append({'variant':name, 'height':{'selected_key':'a','selected_index':0,'stop':0,'scores':[]},
                         'weighted_depth':{'selected_key':'b','selected_index':1,'stop':0,'scores':[]},
                         'event_cost':report(rows), 'captures':[{'candidate':'a'}, {'candidate':'b'}]})
    return {'schema_version':1, 'kind':'b04_cold_component_planning_export', 'status':'exported_conditional_data',
            'source_sha256':source, 'catalog_sha256':catalog, 'training_sha256':training,
            'calibration_sha256':calibration, 'request':{'input_demand':demand},
            'calibration':{'identity':{'source_sha256':source, 'catalog_sha256':catalog,
                                       'calibration_sha256':calibration},
                           'coefficients_sha256':'5'*64, 'model':{'fit':{'status':'finite_fixture'}}},
            'families':[{'id':'f0','candidates':[{'structural_key':key} for key in keys],
                         'statistics':variants}]}


class ExactRatioTests(unittest.TestCase):
    def test_uint64_near_one_order_does_not_round_to_float_tie(self):
        # Both numerator and denominator stay in the native uint64 domain.
        rows=[estimate('a', ratio(MAX_U64, MAX_U64)),
              estimate('z', ratio(MAX_U64 - 1, MAX_U64))]
        got=analysis.event_choice(report(rows), ['a','z'], height('a'))
        self.assertEqual(got['selected_key'], 'z')
        self.assertEqual(got['availability'], 'conditional_complete_scores_asof_memory')
        self.assertEqual(got['predicted_total_ns'],
                         {'numerator':str(MAX_U64 - 1), 'denominator':str(MAX_U64)})

    def test_exact_rational_tie_uses_structural_key(self):
        rows=[estimate('z', ratio(2,4)), estimate('a', ratio(3,6))]
        got=analysis.event_choice(report(rows), ['z','a'], height('z'))
        self.assertEqual(got['selected_key'], 'a')
        self.assertEqual(got['predicted_total_ns'], {'numerator':'1','denominator':'2'})

    def test_ratio_parser_rejects_float_negative_and_zero_denominator(self):
        for value in (1.25, ratio(-1,2), ratio(1,0), {'numerator':True,'denominator':1}):
            with self.subTest(value=value), self.assertRaises(ValueError):
                analysis.exact_ratio(value)


class EventFallbackTests(unittest.TestCase):
    def assert_height_fallback(self, got, key):
        self.assertEqual(got['selected_key'], key)
        self.assertEqual(got['availability'], 'height_fallback_incomplete_scores_or_budget')

    def test_absent_estimate_rows_fall_back_to_native_height(self):
        got=analysis.event_choice(report([]), ['a','b'], height('b'))
        self.assert_height_fallback(got,'b')
        self.assertEqual(got['unknown_scores'],['a','b'])

    def test_missing_candidate_estimate_row_falls_back_without_subset_ranking(self):
        got=analysis.event_choice(report([estimate('a',ratio(1))]), ['a','b'], height('b'))
        self.assert_height_fallback(got,'b')
        self.assertEqual(got['unknown_scores'],['b'])

    def test_unknown_score_falls_back_even_when_other_scores_are_numeric(self):
        rows=[estimate('a',ratio(1)), estimate('b',None,issues=2)]
        got=analysis.event_choice(report(rows), ['a','b'], height('a'))
        self.assert_height_fallback(got,'a')
        self.assertEqual(got['unknown_scores'],['b'])

    def test_native_stop_never_uses_attached_numeric_rows(self):
        rows=[estimate('a',ratio(1)), estimate('b',ratio(2))]
        got=analysis.event_choice(report(rows,stop=2), ['a','b'], height('b'))
        self.assert_height_fallback(got,'b')
        self.assertIsNone(got['predicted_total_ns'])
        self.assertEqual(got['native_stop'],2)

    def test_any_known_asof_memory_exclusion_forces_height_fallback(self):
        rows=[estimate('a',ratio(1)), estimate('b',ratio(1,10),captured=101,budget=100)]
        got=analysis.event_choice(report(rows), ['a','b'], height('a'))
        self.assert_height_fallback(got,'a')
        self.assertEqual(got['known_asof_memory_exclusions'],['b'])

    def test_native_memory_issue_bit_also_excludes_candidate(self):
        rows=[estimate('a',ratio(1)), estimate('b',ratio(1,10),issues=32,captured=90,budget=100)]
        got=analysis.event_choice(report(rows), ['a','b'], height('a'))
        self.assert_height_fallback(got,'a')
        self.assertEqual(got['known_asof_memory_exclusions'],['b'])

    def test_height_candidate_known_over_budget_has_no_fallback(self):
        rows=[estimate('a',ratio(1),captured=101,budget=100), estimate('b',None,issues=2)]
        got=analysis.event_choice(report(rows), ['a','b'], height('a'))
        self.assertIsNone(got['selected_key'])
        self.assertEqual(got['availability'],'no_available_fallback')

    def test_unknown_asof_memory_cannot_complete_cost_choice(self):
        rows=[estimate('a',ratio(1),captured=None), estimate('b',ratio(2))]
        got=analysis.event_choice(report(rows), ['a','b'], height('b'))
        self.assert_height_fallback(got,'b')
        self.assertEqual(got['unknown_scores'],['a'])

    def test_foreign_and_duplicate_estimate_keys_are_rejected(self):
        for rows in ([estimate('foreign',ratio(1))],
                     [estimate('a',ratio(1)),estimate('a',ratio(2))]):
            with self.subTest(rows=rows), self.assertRaises(ValueError):
                analysis.event_choice(report(rows), ['a','b'], height('b'))


class FrozenChoiceTests(unittest.TestCase):
    def test_duplicate_family_keys_are_rejected(self):
        data=valid_export(); data['families'][0]['candidates'].append({'structural_key':'a'})
        with self.assertRaises(ValueError): analysis.freeze_choices(data)

    def test_duplicate_family_ids_are_rejected(self):
        data=valid_export(); data['families'].append(copy.deepcopy(data['families'][0]))
        with self.assertRaises(ValueError): analysis.freeze_choices(data)

    def test_calibration_identity_hash_mismatches_are_rejected(self):
        for name in ('source_sha256','catalog_sha256','calibration_sha256'):
            data=valid_export(); data['calibration']['identity'][name]='f'*64
            with self.subTest(field=name), self.assertRaises(ValueError): analysis.freeze_choices(data)

    def test_training_mix_is_exact_forecast_denominator_and_family_is_retained(self):
        data=valid_export()
        # A missing estimate row forces fallback, but does not remove candidate B
        # or its capture from later independent verification and measurement.
        data['families'][0]['statistics'][0]['event_cost']['candidates']=[estimate('a',ratio(1))]
        got=analysis.freeze_choices(data)
        self.assertEqual(got['forecast_inputs'],40)
        self.assertEqual(got['declared_demand'],data['request']['input_demand'])
        family=got['families'][0]
        self.assertEqual(family['candidate_keys'],['a','b'])
        full=family['statistics'][0]
        self.assertEqual(full['event_cost']['availability'],'height_fallback_incomplete_scores_or_budget')
        self.assertEqual(full['captures'],[{'candidate':'a'},{'candidate':'b'}])
        self.assertEqual(got['availability'],'frozen_before_held_out_measurements')
        self.assertIn('held_out_data_not_consumed',got['scope'])

    def test_stale_asof_stamp_and_variant_are_preserved_without_refresh_claim(self):
        got=analysis.freeze_choices(valid_export())
        family=got['families'][0]
        stale=next(x for x in family['statistics'] if x['variant']=='stale')
        expected={'owner':17,'configuration':1,'reset':2,'segment':0,'epoch':4,'interval_start':0}
        self.assertEqual(stale['variant'],'stale')
        self.assertEqual(stale['event_cost']['observations'][0]['observed_stamp'],expected)
        self.assertTrue(stale['event_cost']['observations'][0]['future_memory_unknown'])
        self.assertIn('no_runtime_installation',stale['event_cost']['scope'])

    def test_frozen_result_owns_nested_export_values(self):
        data=valid_export()
        frozen=analysis.freeze_choices(data)
        before=analysis.canonical(frozen)
        data['request']['input_demand'][0]['inputs']=999
        data['families'][0]['statistics'][0]['captures'][0]['candidate']='mutated'
        data['families'][0]['statistics'][2]['event_cost']['candidates'][0]['observed_stamp']['epoch']=999
        data['calibration']['model']['fit']['status']='mutated'
        self.assertEqual(analysis.canonical(frozen),before)
        self.assertEqual(frozen['forecast_inputs'],40)


if __name__ == '__main__':
    unittest.main(argv=[sys.argv[0]], verbosity=2)
