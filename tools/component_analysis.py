#!/usr/bin/env python3
"""Freeze conditional B04 choices from genuine C02/C03 exports, before evaluation.

This offline module neither installs plans nor enables C05 maintenance_cost.
Ratios and ties stay exact; absent scores retain an explicit height fallback.
"""
from fractions import Fraction
from copy import deepcopy
import hashlib
from ranking_analysis import ratio
from verify_workloads import canonical, require


def exact_ratio(value):
    """Read native unsigned integer ratios without a floating-point conversion."""
    if value is None:
        return None
    require(isinstance(value, dict) and set(value) == {'numerator', 'denominator'}, 'invalid native ratio')
    numbers = []
    for name in ('numerator', 'denominator'):
        item = value[name]
        require(type(item) is int or isinstance(item, str) and item.isascii() and item.isdecimal(), 'ratio needs unsigned integers')
        number = int(item)
        require(number >= 0, 'negative native ratio')
        numbers.append(number)
    require(numbers[1] > 0, 'zero native ratio denominator')
    return Fraction(*numbers)


def native_choice(report, keys):
    """Retain a real native C02 choice, including unavailable stop/reason data."""
    key = report.get('selected_key')
    if key is not None:
        index = report.get('selected_index')
        require(type(index) is int and 0 <= index < len(keys) and keys[index] == key, 'native choice is outside its family')
    else:
        require('selected_index' not in report, 'native choice is missing its key')
    return {'selected_key': key, 'availability': 'native_choice' if key is not None else 'native_unavailable',
            'stop': report.get('stop'), 'reasons': report.get('reasons', [])}


def event_choice(report, keys, height):
    """Rank a complete known-score family; unknown scores trigger height fallback.

    The memory check concerns the captured state only. Future memory is unknown,
    so this choice is a conditional forecast rather than a feasibility theorem.
    """
    rows = report.get('candidates', [])
    by_key = {row['structural_key']: row for row in rows}
    require(len(by_key) == len(rows) and set(by_key) <= set(keys), 'event estimates contain duplicate or foreign candidates')
    scores, unavailable, memory_excluded, observations = {}, [], [], []
    for key in keys:
        row = by_key.get(key)
        if row is None:
            unavailable.append(key)
            continue
        score = exact_ratio(row['total_ns'])
        issues = row['issues']
        require(type(issues) is int and issues >= 0, 'invalid native issue mask')
        captured, budget = row['asof_requested_bytes'], row['memory_budget_bytes']
        require(type(budget) is int and budget > 0, 'invalid native memory budget')
        require(captured is None or type(captured) is int and captured >= 0, 'invalid captured memory')
        over_budget = bool(issues & 32) or captured is not None and captured > budget
        if over_budget:
            memory_excluded.append(key)
        elif score is None or issues != 0 or captured is None:
            unavailable.append(key)
        else:
            scores[key] = score
        observations.append({'structural_key': key, 'issues': issues, 'predicted_total_ns': ratio(score),
                             'observed_stamp': row['observed_stamp'], 'asof_requested_bytes': captured,
                             'memory_budget_bytes': budget, 'future_memory_unknown': row['future_memory_unknown']})
    selected = None
    completed = report.get('stop') == 0  # planner::ranking::Stop::complete.
    if completed and scores and not unavailable and not memory_excluded:
        selected = min(scores, key=lambda key: (scores[key], key))
        availability = 'conditional_complete_scores_asof_memory'
    else:
        selected = height['selected_key']
        if selected in memory_excluded:
            selected = None
        availability = 'height_fallback_incomplete_scores_or_budget' if selected is not None else 'no_available_fallback'
    return {'selected_key': selected, 'availability': availability,
            'predicted_total_ns': ratio(scores.get(selected)) if completed else None,
            'unknown_scores': unavailable, 'known_asof_memory_exclusions': memory_excluded,
            'observations': observations, 'native_stop': report.get('stop'),
            'native_unavailable': report.get('unavailable'),
            'scope': 'offline_C03_only; exact_ratio_then_structural_key; future_memory_unknown; no_runtime_installation'}


def freeze_choices(exported):
    """Consume training/calibration exports only; held-out measurements are absent."""
    require(exported['kind'] == 'b04_cold_component_planning_export', 'wrong component export kind')
    frozen = {'schema_version': 1, 'kind': 'b04_frozen_conditional_choices',
              'export_content_sha256': hashlib.sha256(canonical(exported).encode()).hexdigest(),
              'source_sha256': exported['source_sha256'], 'catalog_sha256': exported['catalog_sha256'],
              'training_sha256': exported['training_sha256'], 'calibration_sha256': exported['calibration_sha256'],
              'families': [], 'scope': 'training_mix_forecasts; held_out_data_not_consumed; C05_maintenance_cost_unsupported'}
    if exported['status'] != 'exported_conditional_data':
        frozen['availability'] = 'original_minimum_not_published'
        return frozen
    calibration = exported['calibration']
    for name in ('source_sha256', 'catalog_sha256', 'calibration_sha256'):
        require(calibration['identity'][name] == frozen[name], 'calibration identity differs from the export')
    frozen['calibration_coefficients_sha256'] = calibration.get('coefficients_sha256')
    frozen['calibration_fit'] = calibration['model'].get('fit')
    demand = exported['request']['input_demand']
    inputs = sum(row['inputs'] for row in demand)
    require(inputs > 0, 'component forecast has no declared input demand')
    frozen['forecast_inputs'] = inputs
    frozen['declared_demand'] = demand
    for family in exported['families']:
        keys = [row['structural_key'] for row in family['candidates']]
        require(keys and len(keys) == len(set(keys)), 'empty or duplicate candidate family')
        variants = []
        for group in family['statistics']:
            height = native_choice(group['height'], keys)
            weighted = native_choice(group['weighted_depth'], keys)
            cost = event_choice(group['event_cost'], keys, height)
            variants.append({'variant': group['variant'], 'height': height, 'weighted_depth': weighted, 'event_cost': cost,
                             'captures': group['captures']})
        require({row['variant'] for row in variants} == {'full', 'sampled', 'stale', 'absent'} and len(variants) == 4,
                'statistics variants must be complete and unique')
        frozen['families'].append({'id': family['id'], 'candidate_keys': keys, 'statistics': variants})
    require(len({row['id'] for row in frozen['families']}) == len(frozen['families']), 'duplicate candidate family identifier')
    frozen['availability'] = 'frozen_before_held_out_measurements'
    # Own the nested evidence once at this cold boundary. Later caller edits to
    # the parsed export cannot change a choice after its input hash was frozen.
    return deepcopy(frozen)
