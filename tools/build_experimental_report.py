#!/usr/bin/env python3
"""Build portable, hash-bound experimental tables without executing a benchmark."""
from __future__ import annotations
import argparse
from collections import defaultdict
import csv
from fractions import Fraction
import gzip
import hashlib
import io
import json
from pathlib import Path
import statistics
import sys
import zlib

sys.dont_write_bytecode = True
STUDIES = ('b05', 'planning', 'operational', 'matched', 'search')
METRIC_FIELDS = ('row_id', 'study', 'source_id', 'group', 'facet', 'series', 'x', 'variant', 'query', 'backend',
                 'mode', 'repetition', 'metric', 'unit', 'numerator', 'denominator', 'availability', 'outcome',
                 'raw_path', 'raw_sha256', 'raw_original_path', 'json_pointer')


def require(condition, message):
    if not condition:
        raise ValueError(message)


def canonical(value):
    return json.dumps(value, sort_keys=True, separators=(',', ':'), ensure_ascii=False, allow_nan=False)


def digest(data):
    return hashlib.sha256(data).hexdigest()


def write_json(path, value):
    path.write_text(json.dumps(value, indent=2, sort_keys=True, ensure_ascii=False, allow_nan=False)+'\n')


def write_csv(path, rows, fields):
    with path.open('x', newline='') as stream:
        writer = csv.DictWriter(stream, fields, extrasaction='ignore')
        writer.writeheader(); writer.writerows(rows)


class Evidence:
    """One finite content store; replay resolves only its recorded relative files."""
    def __init__(self, output, maximum, single_file, mappings=(), replay=None):
        self.output, self.maximum, self.single_file = output, maximum, single_file
        self.bytes = 0; self.files = {}; self.paths = {}
        self.mappings = sorted(mappings, key=lambda pair: len(str(pair[0])), reverse=True)
        self.replay = replay
        self.prior = json.loads((replay/'evidence-index.json').read_text()) if replay else None
        (output/'evidence').mkdir()

    def read(self, path, expected=None):
        original = str(Path(path))
        if self.replay:
            require(original in self.prior['original_paths'], 'evidence missing from portable store: '+original)
            key = self.prior['original_paths'][original]; entry = self.prior['files'][key]
            relative = Path(entry['path'])
            require(not relative.is_absolute() and '..' not in relative.parts, 'unsafe evidence member')
            require((self.replay/relative).stat().st_size == entry['compressed_bytes'] <= self.single_file+1024**2,
                    'compressed evidence exceeds recorded finite grant')
            compressed = (self.replay/relative).read_bytes()
            require(digest(compressed) == entry['compressed_sha256'], 'compressed evidence hash differs: '+original)
            with gzip.GzipFile(fileobj=io.BytesIO(compressed)) as stream:
                data = stream.read(self.single_file+1)
            require(digest(data) == key, 'decompressed evidence hash differs: '+original)
        else:
            actual = Path(path)
            for old, new in self.mappings:
                if actual.is_relative_to(old):
                    actual = new/actual.relative_to(old); break
            require(actual.is_file(), 'missing evidence: '+str(actual))
            require(actual.stat().st_size <= self.single_file, 'single evidence file exceeds grant')
            data = actual.read_bytes()
        require(len(data) <= self.single_file, 'decompressed evidence exceeds grant')
        key = digest(data)
        require(expected is None or key == expected, 'evidence hash differs: '+original)
        if key not in self.files:
            require(len(self.files) < 20000 and len(data) <= self.maximum-self.bytes, 'evidence bundle grant exceeded')
            member = Path('evidence')/(key+'.gz')
            with (self.output/member).open('xb') as target:
                with gzip.GzipFile(filename='', fileobj=target, mode='wb', mtime=0, compresslevel=6) as archive:
                    archive.write(data)
            compressed = (self.output/member).read_bytes()
            self.files[key] = {'path': str(member), 'original_bytes': len(data),
                               'compressed_bytes': len(compressed), 'compressed_sha256': digest(compressed)}
            self.bytes += len(data)
        require(original not in self.paths or self.paths[original] == key, 'input changed during report generation')
        self.paths[original] = key
        return data, {'path': self.files[key]['path'], 'sha256': key, 'original_path': original}

    def json(self, path, expected=None):
        data, reference = self.read(path, expected)
        return json.loads(data), reference

    def reference(self, path, expected=None):
        original = str(Path(path))
        if original not in self.paths:
            return self.read(path, expected)[1]
        key = self.paths[original]
        require(expected is None or key == expected, 'cached evidence hash differs: '+original)
        return {'path': self.files[key]['path'], 'sha256': key, 'original_path': original}

    def finish(self):
        write_json(self.output/'evidence-index.json', {'schema_version': 1, 'kind': 'experimental_evidence_gzip_v1',
            'files': self.files, 'original_paths': self.paths, 'original_bytes': self.bytes,
            'compression_runtime': {'python': sys.version, 'zlib': zlib.ZLIB_RUNTIME_VERSION, 'level': 6, 'mtime': 0},
            'scope': 'Relative deterministic gzip members; SHA keys bind decompressed original bytes. Original paths are audit metadata, never replay fallbacks.'})


def command_evidence(store, directory, record):
    require(record['exit_code'] == 0 and not record.get('timed_out', False), 'unqualified command cannot supply measurements')
    data, reference = store.read(directory/record['stdout'], record['stdout_sha256'])
    stderr, _ = store.read(directory/record['stderr'], record['stderr_sha256'])
    require(not stderr, 'successful command contains diagnostics')
    if 'resource_usage' in record:
        resource, resource_reference = store.read(directory/record['resource_usage'], record['resource_usage_sha256'])
        require(int(resource) == record['process_maxrss_KiB'], 'resource/RSS binding differs')
        reference['resource_reference'] = resource_reference
    # Only declared data arguments are copied, never producer binaries/archives.
    for argument in record.get('arguments', [])[1:]:
        if Path(argument).suffix in ('.json', '.jsonl', '.sql'):
            store.read(argument)
    return json.loads(data), reference


def exact(value):
    if isinstance(value, dict):
        return Fraction(int(value['numerator']), int(value['denominator']))
    require(isinstance(value, (int, Fraction)) and not isinstance(value, bool), 'metric must be exact integer/rational')
    return Fraction(value)


class Tables:
    def __init__(self, store, selection):
        self.store, self.selection = store, selection
        self.metrics = []; self.decisions = []; self.scopes = {}; self.environments = {}
        self.b05_rows = []; self.b05_probes = []; self.group_ids = {}

    def groups(self, study, available):
        available = sorted(set(available)); chosen = self.selection.get(study, available)
        require(isinstance(chosen, list) and chosen and len(set(chosen)) == len(chosen) and set(chosen) <= set(available),
                'unknown/empty/duplicate selection for '+study)
        self.group_ids[study] = available
        self.scopes[study] = {'available_groups': len(available), 'included_groups': len(chosen),
                              'selected_group_ids': sorted(chosen), 'full_source_scope': set(chosen) == set(available)}
        return set(chosen)

    def environment(self, study, packet):
        value = {'environment': packet.get('environment'), 'build': packet.get('build'),
                 'configuration': packet.get('configuration'), 'scope': packet.get('limits', packet.get('scope'))}
        key = digest(canonical(value).encode())
        self.environments[key] = {'study': study, **value}
        return key

    def metric(self, base, name, value, unit, reference, pointer='', availability='available'):
        value = exact(value) if value is not None else None
        record = {**base, 'metric': name, 'unit': unit,
                  'numerator': str(value.numerator) if value is not None else '',
                  'denominator': str(value.denominator) if value is not None else '',
                  'availability': availability if value is not None else 'unavailable',
                  'raw_path': reference['path'], 'raw_sha256': reference['sha256'],
                  'raw_original_path': reference['original_path'], 'json_pointer': pointer}
        record['row_id'] = digest(canonical(record).encode())[:24]
        self.metrics.append(record)

    def decision(self, study, group, kind, details, reference, pointer):
        self.decisions.append({'study': study, 'group': group, 'kind': kind, 'details': canonical(details),
                               'raw_path': reference['path'], 'raw_sha256': reference['sha256'],
                               'raw_original_path': reference['original_path'], 'json_pointer': pointer})

    def samples(self, base, name, values, unit, reference, pointer):
        ordered = sorted(values)
        for percent in (50, 95, 99):
            value = ordered[(len(ordered)*percent+99)//100-1] if ordered else None
            self.metric(base, name+'_p'+str(percent), value, unit, reference, pointer)
        self.metric(base, name+'_max', ordered[-1] if ordered else None, unit, reference, pointer)


def b03_metrics(tables, base, report, record, reference, release=False):
    epochs = report['epochs']; count = len(epochs)
    require(count > 0, 'empty measured B03 horizon')
    native = [row['native_prepare_commit_ns']+(row['epoch_release_ns'] if release else 0) for row in epochs]
    name = 'native_prepare_and_epoch_release_ns_per_input' if release else 'native_prepare_commit_ns_per_input'
    tables.metric(base, name, Fraction(sum(native), count), 'ns/physical_input', reference, '/epochs')
    for field in ('event_active_ns', 'output_setup_ns', 'output_next_ns', 'encoding_ns', 'sink_write_wait_ns', 'diagnostics_ns'):
        tables.metric(base, field+'_per_input', Fraction(sum(row[field] for row in epochs), count), 'ns/physical_input', reference, '/epochs')
    tables.samples(base, 'event_active_ns', [row['event_active_ns'] for row in epochs], 'ns/physical_epoch', reference, '/epochs')
    tables.samples(base, name.removesuffix('_per_input'), native, 'ns/physical_epoch', reference, '/epochs')
    calls = [call for row in epochs for call in row['output_calls']]
    tables.samples(base, 'successful_next_ns', [call['nanoseconds'] for call in calls if call['returned_row']], 'ns/returned_record', reference, '/epochs')
    tables.samples(base, 'termination_next_ns', [call['nanoseconds'] for call in calls if not call['returned_row']], 'ns/termination_call', reference, '/epochs')
    first = [row['output_setup_ns']+row['output_calls'][0]['nanoseconds'] for row in epochs
             if row['output_calls'] and row['output_calls'][0]['returned_row']]
    tables.samples(base, 'cursor_first_result_delay_ns', first, 'ns/nonempty_cursor_after_commit', reference, '/epochs')
    for name, value in [('physical_inputs', count), ('output_records', report['output_rows']),
                        ('query_current_requested_bytes', max(row['memory']['current_requested_bytes'] for row in epochs)),
                        ('query_peak_requested_bytes', report['memory_final']['peak_requested_bytes'])]:
        tables.metric(base, name, value, 'KiB' if name.endswith('KiB') else 'bytes' if name.endswith('bytes') else 'count', reference)
    tables.metric(base, 'process_maxrss_KiB', record['process_maxrss_KiB'], 'KiB/whole_process', reference['resource_reference'])


def read_b05(tables, root, analysis):
    store = tables.store; packet, packet_ref = store.json(root/'experiment.json')
    require(packet['kind'] == 'b05_parameterized_native_stress' and packet['status'] == 'complete', 'B05 packet is not complete')
    manifest, _ = store.json(analysis/'artifact-manifest.json')
    require(manifest['input_experiment_sha256'] == packet_ref['sha256'], 'B05 analysis/input binding differs')
    data, _ = store.read(analysis/'rows.csv', manifest['files']['rows.csv'])
    rows = list(csv.DictReader(io.StringIO(data.decode())))
    group = lambda row: '|'.join(str(row[key]) for key in ('family', 'scale', 'backend', 'mode'))
    chosen = tables.groups('b05', map(group, rows)); cases = {(row['family'], row['scale']): row for row in packet['cases']}
    children = {}; seen_gates = set()
    for row in rows:
        key = group(row)
        if key not in chosen:
            continue
        case = cases[row['family'], int(row['scale'])]; directory = root/case['directory']/'native'
        if str(directory) not in children:
            child, child_ref = store.json(directory/'experiment.json', case['native_experiment_sha256'])
            require(child['status'] == 'complete' and child['correctness_gate'] == 'passed_all_configurations_before_warmup_or_measurement', 'B05 correctness gate incomplete')
            commands, _ = store.json(directory/'commands.json', child['commands_sha256'])
            children[str(directory)] = child, commands, tables.environment('b05', child)
            tables.decision('b05', case['family']+'|'+str(case['scale']), 'shared_setup', child['compilation_summaries'], child_ref, '/compilation_summaries')
        child, commands, source_id = children[str(directory)]
        run = next(item for item in child['runs'] if item['raw_report'] == Path(row['raw_report']).name)
        require(run['warmup'] is False and run['raw_report_sha256'] == row['raw_sha256'], 'B05 measured row binding differs')
        report, reference = command_evidence(store, directory, commands[run['command']])
        require(reference['sha256'] == row['raw_sha256'] and report['records'] == int(row['events']), 'B05 raw horizon differs')
        base = {'study': 'b05', 'source_id': source_id, 'group': key, 'facet': row['family'],
                'series': row['backend']+'/'+row['mode'], 'x': row['axis_value'], 'variant': row['family'],
                'query': row['family'], 'backend': row['backend'], 'mode': row['mode'], 'repetition': int(row['repetition']), 'outcome': 'measured'}
        b03_metrics(tables, base, report, commands[run['command']], reference)
        for field in ('source', 'support'):
            tables.metric(base, field+'_slots_max', max(epoch['storage'][field]['slots'] for epoch in report['epochs']), 'arena_slots', reference, '/epochs')
        visits = [epoch['operator_metrics']['support.native_record_visits'] for epoch in report['epochs']]
        value = Fraction(sum(cell['value'] for cell in visits), len(visits)) if all(cell['availability'] == 'available' and not cell['saturated'] for cell in visits) else None
        tables.metric(base, 'support_native_visits_per_input', value, 'selected_visits/physical_input', reference, '/epochs')
        tables.b05_rows.append({**row, 'raw_report': reference['path']})
        if key not in seen_gates:
            gate = next(item for item in child['verification'] if item['label'] == run['label'])
            require(gate['passed'] is True, 'B05 named preflight did not pass')
            command_evidence(store, directory, commands[gate['command']])
            for warmup in child['runs']:
                if warmup['label'] == run['label'] and warmup['warmup']:
                    command_evidence(store, directory, commands[warmup['command']])
            seen_gates.add(key)
    probes, _ = store.read(analysis/'probes.csv', manifest['files']['probes.csv'])
    for row in csv.DictReader(io.StringIO(probes.decode())):
        if group(row) in chosen:
            reference = store.reference(row['raw_report'], row['raw_sha256'])
            tables.b05_probes.append({**row, 'raw_report': reference['path']})


def read_planning(tables, directory):
    store = tables.store; packet, source = store.json(directory/'experiment.json')
    require(packet['status'] == 'complete_conditional_dependencies' and packet['correctness_gate'] ==
            'all_available_groups_all_retained_envelopes_all_splits_verified_before_heldout_timing', 'planning gate incomplete')
    store.read(directory/'commands.json', packet['commands_sha256']); source_id = tables.environment('planning', packet)
    group = lambda row: '|'.join((row['query'], row['backend'], row['trace']))
    chosen = tables.groups('planning', [group(row) for row in packet['runs'] if not row['warmup']])
    wanted_pairs = {(row['query'], row['backend']) for row in packet['runs'] if group(row) in chosen}
    for row in packet['verification']:
        if (row['query'], row['backend']) in wanted_pairs:
            command_evidence(store, directory, row)
    for item in packet['groups']:
        if (item['query'], item['backend']) in wanted_pairs:
            store.read(directory/item['choices_file'], item['choices_sha256'])
            store.read(directory/item['calibration_file'], item['calibration_sha256'])
            for export in item['exports']:
                command_evidence(store, directory, export)
    for row in packet['runs']:
        if group(row) not in chosen:
            continue
        report, reference = command_evidence(store, directory, row)
        if row['warmup']:
            continue
        base = {'study': 'planning', 'source_id': source_id, 'group': group(row)+'|'+row['physical_sha256'],
                'facet': row['query']+'|'+row['backend'], 'series': row['physical_sha256'][:12],
                'x': row['trace'].rsplit('/', 1)[-1], 'variant': row['physical_sha256'], 'query': row['query'],
                'backend': row['backend'], 'mode': 'maintenance', 'repetition': row['repetition'], 'outcome': 'measured'}
        b03_metrics(tables, base, report, row, reference, release=True)
        require(exact(row['costs']['native_ns_per_input']) == Fraction(sum(epoch['native_prepare_commit_ns']+epoch['epoch_release_ns'] for epoch in report['epochs']), len(report['epochs'])), 'planning recorded cost differs')
    for index, row in enumerate(packet['analysis']):
        if group(row) in chosen:
            tables.decision('planning', group(row), 'policy_statistics_evaluation', row, source, '/analysis/'+str(index))


def component_metrics(tables, base, report, record, reference):
    passes = [value for value in report['passes'] if value['warmup'] is False]
    require(len(passes) == 1, 'component invocation must have one measured owner')
    value = passes[0]
    pass_pointer = '/passes/'+str(report['passes'].index(value))
    physical = value['epochs'][-1].get('physical_input_end', value['epochs'][-1]['sequence'])
    tables.metric(base, 'loop_ns_per_input', Fraction(value['loop_wall_ns'], physical), 'ns/physical_input', reference, '/passes')
    for key in ('initialize_ns', 'teardown_ns'):
        tables.metric(base, key, value[key], 'ns/owner', reference, '/passes')
    for key in ('read_request_ns', 'shared_program_ns'):
        tables.metric(base, key, report.get(key), 'ns/invocation', reference, '/'+key)
    for field in ('epochs', 'transactions', 'batches'):
        rows = value.get(field, [])
        for key in sorted({key for row in rows for key in row if key.endswith('_ns')}):
            samples = [row[key] for row in rows if row.get(key) is not None]
            tables.metric(base, field+'.'+key+'_per_input', Fraction(sum(samples), physical) if samples else None, 'ns/physical_input', reference, '/passes')
            tables.samples(base, field+'.'+key, samples, 'ns/'+field, reference, '/passes')
    usage = value['native_memory_before_teardown']
    for field, name in [('current_requested_bytes', 'query_current_requested_bytes'), ('peak_requested_bytes', 'final_owner_peak_requested_bytes')]:
        tables.metric(base, name, usage[field] if usage else None, 'requested_bytes', reference, '/passes')
    tables.metric(base, 'process_maxrss_KiB', record['process_maxrss_KiB'], 'KiB/whole_process', reference['resource_reference'])
    tables.metric(base, 'output_records', value['output_records'], 'declared_output_records', reference, '/passes')
    for index, batch in enumerate(value.get('batches', [])):
        if batch.get('reconstructed'):
            tables.decision(base['study'], base['group'], 'owner_reconstruction_memory', batch, reference, pass_pointer+'/batches/'+str(index))
    if 'sampled_owner_peak_max_requested_bytes' in value:
        tables.metric(base, 'sampled_owner_peak_max_requested_bytes', value['sampled_owner_peak_max_requested_bytes'], 'requested_bytes', reference, '/passes')


def read_components(tables, directory, study):
    store = tables.store; packet, source = store.json(directory/'experiment.json')
    expected = 'complete_conditional_operational' if study == 'operational' else 'complete_conditional_matched'
    require(packet['status'] == expected and packet['correctness_gate'] == 'all_preflights_pass' and packet['frozen_inputs_unchanged'], study+' gate incomplete')
    store.read(directory/'commands.json', packet['commands_sha256']); source_id = tables.environment(study, packet)
    arms = {arm['id']: arm for arm in packet['cohorts']['arms']}; chosen = tables.groups(study, arms)
    for row in packet['verification']:
        if row['arm'] in chosen:
            command_evidence(store, directory, row)
    for row in packet.get('service_verification', []):
        if row['derived_from_arm'] in chosen:
            command_evidence(store, directory, row)
    for row in packet['runs']:
        if row['arm'] not in chosen:
            continue
        report, reference = command_evidence(store, directory, row)
        require([value['warmup'] for value in report['passes']] == [True]*arms[row['arm']]['request']['warmup_passes']+[False], 'owner schedule differs')
        arm = arms[row['arm']]; identifier = row['arm']; width = identifier.split('-', 1)[0]
        backend = (arm['request']['native']['physical_options'].get('indexed_storage') or {}).get('algorithm', 'reference_ordered_v1')
        variant = identifier.removeprefix(width+'-').replace(backend+'-', '')
        base = {'study': study, 'source_id': source_id, 'group': identifier, 'facet': variant if study == 'operational' else arm['request']['query_family'],
                'series': backend if study == 'operational' else arm['adapter'] if arm['adapter'] not in ('set', 'aggregate') else backend,
                'x': width.removeprefix('w'), 'variant': variant, 'query': arm['request']['query_family'],
                'backend': backend if arm['adapter'] in ('set', 'rows', 'session', 'aggregate') else arm['adapter'],
                'mode': arm['request']['output'], 'repetition': row['repetition'], 'outcome': 'measured'}
        component_metrics(tables, base, report, row, reference)
    for index, row in enumerate(packet['comparisons']):
        if row['baseline'] in chosen and row['variant'] in chosen:
            tables.decision(study, row['id'], 'declared_comparison', row, source, '/comparisons/'+str(index))


def read_search(tables, directory):
    store = tables.store; packet, source = store.json(directory/'experiment.json')
    require(packet['status'] == 'finite_conditional_study_complete' and packet['correctness_gate'] ==
            'all_reported_variants_checked_before_timing' and not packet['external_failures'], 'search gate incomplete')
    store.read(directory/'commands.json', packet['commands_sha256']); source_id = tables.environment('search', packet)
    group = lambda row: '|'.join((row['case'], row['method'], str(row['work_limit'])))
    chosen = tables.groups('search', [group(row) for row in packet['runs'] if not row['warmup']])
    cases = {row['case'] for row in packet['runs'] if group(row) in chosen}
    for row in packet['preflight']:
        if row.get('case') in cases and 'stdout' in row:
            command_evidence(store, directory, row)
    for run_index, row in enumerate(packet['runs']):
        if group(row) not in chosen:
            continue
        report, reference = command_evidence(store, directory, row)
        if row['warmup']:
            continue
        require(canonical(row['timings']) == canonical(report['timings']) and
                row['retained_candidates'] == len(report['candidates']) and row['status'] == report['status'],
                'search metadata/raw timing, count or status differs')
        base = {'study': 'search', 'source_id': source_id, 'group': group(row), 'facet': row['case'], 'series': row['method'],
                'x': str(row['work_limit']), 'variant': row['method'], 'query': row['case'], 'backend': 'planner',
                'mode': 'bounded_search', 'repetition': row['repetition'], 'outcome': row['outcome']}
        for name, value in report['timings'].items():
            tables.metric(base, name, value, 'ns/invocation', reference, '/timings/'+name)
        tables.metric(base, 'process_wall_ns', row['wall_ns'], 'ns/whole_process', source, '/runs/'+str(run_index)+'/wall_ns')
        tables.metric(base, 'process_maxrss_KiB', row['process_maxrss_KiB'], 'KiB/whole_process', reference['resource_reference'])
        tables.metric(base, 'retained_candidates', len(report['candidates']), 'candidates', reference, '/candidates')
        tables.decision('search', group(row), 'bounded_search_outcome', {key: report.get(key) for key in ('status', 'algorithm', 'family', 'scoring', 'upstream_and_admission_exhausted')}, reference, '')


def read_specialization(tables, directory):
    """Optional same-engine interpreted/threaded study; no manifest means no claim."""
    store = tables.store; packet, source = store.json(directory/'experiment.json')
    require(packet['kind'] == 'b04_input_specialization_study_v1' and
            packet['status'] == 'finite_conditional_input_specialization_complete' and
            packet['correctness_gate'] == 'all_variants_all_prefixes_verified_before_timing', 'specialization gate incomplete')
    store.read(directory/'commands.json', packet['commands_sha256']); source_id = tables.environment('specialization', packet)
    group = lambda row: '|'.join((row['case'], row['backend'], row['execution']))
    chosen = tables.groups('specialization', [group(row) for row in packet['runs'] if not row['warmup']])
    for row in packet['verification']:
        if group(row) in chosen:
            command_evidence(store, directory, row)
    for row in packet['runs']:
        if group(row) not in chosen:
            continue
        report, reference = command_evidence(store, directory, row)
        if row['warmup']:
            continue
        require(report['kind'] == 'b04_input_specialization_report_v1' and report['execution'] == row['execution'] and
                report['execution_key'] == row['execution_key'], 'specialization execution identity differs')
        for field in ('physical_sha256', 'source_sha256', 'sql_sha256', 'catalog_sha256', 'input_sha256'):
            if field in row:
                require(row[field] == report[field], 'specialization raw identity differs: '+field)
        base = {'study': 'specialization', 'source_id': source_id, 'group': group(row), 'facet': row['case'],
                'series': row['backend']+'/'+row['execution'], 'x': row['case'], 'variant': row['execution_key'],
                'query': row['case'], 'backend': row['backend'], 'mode': 'same_engine_input_dispatch',
                'repetition': row['repetition'], 'outcome': 'measured'}
        component_metrics(tables, base, report, row, reference)
        tables.metric(base, 'execution_prepare_ns', report['execution_prepare_ns'], 'ns/receiving_freeze_and_preparation', reference, '/execution_prepare_ns')
        tables.decision('specialization', group(row), 'execution_preparation',
                        {key: report.get(key) for key in ('execution', 'execution_key', 'preparation', 'base_freeze_work',
                                                       'physical_sha256', 'source_sha256', 'tree', 'physical_options')}, reference, '')
    for index, row in enumerate(packet['comparisons']):
        tables.decision('specialization', str(index), 'declared_same_engine_comparison', row, source, '/comparisons/'+str(index))


def summarize(metrics):
    groups = defaultdict(list)
    for row in metrics:
        groups[row['study'], row['source_id'], row['group'], row['metric'], row['unit']].append(row)
    result = []
    for key, rows in sorted(groups.items()):
        values = [Fraction(int(row['numerator']), int(row['denominator'])) for row in rows if row['availability'] == 'available']
        value = {'study': key[0], 'source_id': key[1], 'group': key[2], 'metric': key[3], 'unit': key[4],
                 'samples': len(values), 'unavailable_samples': len(rows)-len(values), 'repetitions': len({row['repetition'] for row in rows}),
                 'row_ids': canonical([row['row_id'] for row in rows]), 'raw_paths': canonical(sorted({row['raw_path'] for row in rows})),
                 'sample_standard_deviation_display': statistics.stdev(map(float, values)) if len(values) > 1 else '',
                 'interval': 'observed_min_median_max_not_confidence_interval'}
        for name, scalar in [('minimum', min(values) if values else None), ('median', statistics.median(values) if values else None),
                             ('maximum', max(values) if values else None), ('mean', sum(values, Fraction())/len(values) if values else None)]:
            value[name+'_numerator'] = str(scalar.numerator) if scalar is not None else ''
            value[name+'_denominator'] = str(scalar.denominator) if scalar is not None else ''
        result.append(value)
    return result


def reproduction_text():
    return '''# Reproduce the method in a fresh prefix

Use the pinned source preimages and toolchain/dependency records linked by this bundle. Timing values on another machine are new observations. Build a fresh Release tree with CMAKE_EXPORT_COMPILE_COMMANDS=ON and the source's documented C++23 compiler/dependency lock; retain machine/allocator/affinity details. Do not reuse old producer paths or relabel current sources as the historical source image.

Run tools/run_adversarial_scalability.py, tools/run_component_planning.py, tools/run_operational_evaluation.py, tools/run_baseline_evaluation.py and tools/run_search_evaluation.py with fresh --output roots, a permitted --cpu, three repetitions and one warmup. The component guide documents exact executable arguments and cohort factories. All correctness gates precede timing; preserve all stops and unavailable fields.

For original baselines, stage the immutable commits from docs/legacy_baselines.md into new directories. Select the pinned Java8 explicitly. Use a private Maven repository and unchanged compile/package commands; published OutputResultTest remains a recorded failure, not acceptance. Export the test/runtime classpath, then compile tools/support/ComponentReplay.scala with Scala2.12.7 into a NEW helper-class directory. The helper precedes unchanged original main classes and dependency JARs. Build the C++ wrapper through installed component-runtime CMake with the three explicit original-source/build/fmt paths. Create expected qualification inventories from those actual fresh artifacts and run independent replay/prefix checks before any timing. Never point build commands at accepted immutable prefixes.

Regenerate tables from the portable store with report-tools/build_experimental_report.py --replay THIS_BUNDLE --output NEW_REPORT --max-evidence-bytes 17179869184 (or another sufficient finite grant). Replay reads only checked gzip members and never falls back to original private paths. Generate PNG/PDF using report-tools/plot_experimental_report.py --input NEW_REPORT --output NEW_FIGURES with Matplotlib Agg and a new MPLCONFIGDIR. See methodology.md and the included guides for executable fresh-workspace commands and dependency versions.
'''


def run(args):
    output = args.output.resolve(); require(not output.exists(), 'report output must be new')
    require(1 <= args.max_evidence_bytes <= 32*1024**3 and 1 <= args.max_file_bytes <= 1024**3, 'invalid evidence grants')
    if args.replay:
        manifest_bytes = (args.replay/'artifact-manifest.json').read_bytes()
        require(args.expected_manifest_sha256 is None or digest(manifest_bytes) == args.expected_manifest_sha256,
                'published report manifest hash differs')
        prior_manifest = json.loads(manifest_bytes)
        for name in ('input-catalog.json', 'evidence-index.json'):
            require(digest((args.replay/name).read_bytes()) == prior_manifest['files'][name], 'portable index binding differs')
    previous = json.loads((args.replay/'input-catalog.json').read_text()) if args.replay else None
    paths = previous['inputs'] if previous else {name: str(getattr(args, name).resolve()) for name in (*STUDIES, 'b05_analysis')}
    if not previous and args.specialization:
        paths['specialization'] = str(args.specialization.resolve())
    selection = json.loads(args.selection.read_text()) if args.selection else previous['selection'] if previous else {}
    require(set(selection) <= set(STUDIES) | {'specialization'}, 'unknown selection study')
    mappings = []
    for item in args.path_map:
        old, new = item.split('=', 1); mappings.append((Path(old), Path(new).resolve()))
    output.mkdir(parents=True); args._created_output = True
    store = Evidence(output, args.max_evidence_bytes, args.max_file_bytes, mappings, args.replay)
    tables = Tables(store, selection)
    read_b05(tables, Path(paths['b05']), Path(paths['b05_analysis']))
    read_planning(tables, Path(paths['planning']))
    read_components(tables, Path(paths['operational']), 'operational')
    read_components(tables, Path(paths['matched']), 'matched')
    read_search(tables, Path(paths['search']))
    if 'specialization' in paths:
        read_specialization(tables, Path(paths['specialization']))
    require('specialization' not in selection or 'specialization' in paths, 'specialization selected without actual study input')
    preimages = previous.get('source_preimages', {}) if previous else dict(item.split('=', 1) for item in args.source_preimage)
    preimage_refs = {label: store.read(path)[1] for label, path in preimages.items()}
    write_csv(output/'per_repetition_metrics.csv', tables.metrics, METRIC_FIELDS)
    summaries = summarize(tables.metrics)
    write_csv(output/'summary_metrics.csv', summaries, list(summaries[0]))
    write_csv(output/'decisions_and_stops.csv', tables.decisions, ('study', 'group', 'kind', 'details', 'raw_path', 'raw_sha256', 'raw_original_path', 'json_pointer'))
    if tables.b05_rows:
        write_csv(output/'b05-rows.csv', tables.b05_rows, list(tables.b05_rows[0]))
        write_csv(output/'b05-probes.csv', tables.b05_probes, list(tables.b05_probes[0]) if tables.b05_probes else ('family', 'scale', 'backend', 'mode'))
    write_json(output/'source_environment_index.json', tables.environments)
    write_json(output/'input-catalog.json', {'inputs': paths, 'selection': selection, 'source_preimages': preimages})
    store.finish()
    scope = {'schema_version': 1, 'kind': 'experimental_report_data_v1', 'status': 'complete_report_data',
             'scopes': tables.scopes, 'metric_rows': len(tables.metrics), 'decision_rows': len(tables.decisions),
             'full_source_selection': all(item['full_source_scope'] for item in tables.scopes.values()),
             'source_preimages': preimage_refs, 'source_preimage_files_present_for_all_studies': all(label in preimages for label in tables.scopes),
             'source_preimage_qualification': 'Separate source/build lineage receiving required; file presence and SHA do not prove archive contents.',
             'table_builder_sha256': digest(Path(__file__).read_bytes()), 'B06_accepted': False,
             'limits': ['No native/build/timing execution by report tools.', 'Descriptive three-process repetition ranges, not confidence intervals.',
                        'Historical source images and units stay separate; no cross-version speedup pooling.',
                        'Query accounts, sampled owner peaks, work layers and whole-process RSS are different scopes.',
                        'Cursor first-result/call samples start after commit; eager preparation/staging remains in native/event phases.',
                        'Partial searches, unavailable scores, rank-deficient C03 fits and explicit fallbacks remain in decisions.',
                        'Whole-implementation comparisons include plan/layout/parser/scalar/format/JVM/JIT costs; C05 maintenance_cost unsupported.',
                        'Source/toolchain preimages and fresh-prefix replay qualification are separate from data-bundle completeness; B04/B06/release acceptance is not inferred.']}
    write_json(output/'report-index.json', scope)
    lines = ['# Source-pinned experimental report', '', 'Conditional finite measurements; implementation and release goals are separate.', '',
             '| Study | Included groups | Available groups | Full input scope |', '| --- | ---: | ---: | --- |']
    for name, item in tables.scopes.items():
        lines.append(f'| {name} | {item["included_groups"]} | {item["available_groups"]} | {item["full_source_scope"]} |')
    lines += ['', '[Per-repetition exact tables](per_repetition_metrics.csv), [descriptive summaries](summary_metrics.csv),',
              '[decisions/stops/availability](decisions_and_stops.csv), [raw record links](raw-records.md),',
              '[source and machine metadata](source_environment_index.json), [reproduction](reproduction.md).', '',
              'Raw links are gzip files; their decompressed bytes have the SHA in each table. Plot conversion may use floats; exact tables retain numerator/denominator.', '',
              '## Limits', '']+[f'- {item}' for item in scope['limits']]
    if not scope['source_preimage_files_present_for_all_studies']:
        lines += ['', 'Source preimages are incomplete: this data-only bundle is not a complete publication/rebuild package.']
    (output/'report.md').write_text('\n'.join(lines)+'\n')
    raw = sorted({(row['study'], row['group'], row['repetition'], row['raw_path'], row['raw_sha256']) for row in tables.metrics})
    (output/'raw-records.md').write_text('# Exact measured raw records\n\n| Study | Group | Repetition | Original SHA256 | Raw gzip |\n| --- | --- | ---: | --- | --- |\n'+''.join(
        f'| {study} | {group.replace("|", "/")} | {repetition} | {key} | [original bytes]({path}) |\n' for study, group, repetition, path, key in raw))
    (output/'reproduction.md').write_text(reproduction_text())
    guide = args.replay/'methodology.md' if args.replay else Path(__file__).resolve().parents[1]/'docs/experimental_report.md'
    (output/'methodology.md').write_bytes(guide.read_bytes())
    for name in ('adversarial_scalability.md', 'component_evaluation.md', 'legacy_baselines.md', 'measurement.md'):
        document = args.replay/name if args.replay else Path(__file__).resolve().parents[1]/'docs'/name
        if document.is_file():
            (output/name).write_bytes(document.read_bytes())
    for source in (Path(__file__).resolve(), Path(__file__).resolve().with_name('plot_experimental_report.py'),
                   Path(__file__).resolve().with_name('plot_adversarial_scalability.py')):
        destination = output/'report-tools'/source.name; destination.parent.mkdir(exist_ok=True); destination.write_bytes(source.read_bytes())
    files = {str(path.relative_to(output)): digest(path.read_bytes()) for path in output.rglob('*') if path.is_file()}
    write_json(output/'artifact-manifest.json', {'schema_version': 1, 'kind': 'experimental_report_artifacts_v1', 'files': files,
        'scope': 'Exact report/table/evidence bytes. Metadata source ids do not confer runtime correctness or B06 acceptance.'})
    print(f'Report data: {len(tables.metrics)} metric rows, {len(tables.decisions)} decision rows, {len(store.files)} reachable evidence members: {output}')


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    for name in (*STUDIES, 'b05-analysis'):
        parser.add_argument('--'+name, type=Path)
    parser.add_argument('--replay', type=Path); parser.add_argument('--output', type=Path, required=True)
    parser.add_argument('--expected-manifest-sha256'); parser.add_argument('--specialization', type=Path)
    parser.add_argument('--selection', type=Path); parser.add_argument('--path-map', action='append', default=[])
    parser.add_argument('--source-preimage', action='append', default=[])
    parser.add_argument('--max-evidence-bytes', type=int, default=512*1024**2)
    parser.add_argument('--max-file-bytes', type=int, default=256*1024**2)
    args = parser.parse_args(); args._created_output = False
    try:
        require(args.replay is not None or all(getattr(args, name) is not None for name in (*STUDIES, 'b05_analysis')), 'all five studies and B05 analysis are required, or --replay')
        run(args)
    except Exception as error:
        if args._created_output:
            write_json(args.output.resolve()/'failure.json', {'status': 'failed', 'error': str(error)})
        print('Experimental report failed: '+str(error), file=sys.stderr)
        return 1
    return 0


if __name__ == '__main__':
    raise SystemExit(main())
