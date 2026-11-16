#!/usr/bin/env python3
"""Verify B02 manifests, deterministic bytes, regime promises and native epochs."""
from __future__ import annotations

import argparse
import collections
import copy
import hashlib
import importlib.util
import json
import re
from pathlib import Path, PurePosixPath
import subprocess
import sys
import tempfile
import jsonschema

sys.dont_write_bytecode = True


def require(value, message):
    if not value: raise ValueError(message)


def canonical(value):
    return json.dumps(value, ensure_ascii=False, sort_keys=True, separators=(',', ':'))


def digest(path):
    return hashlib.sha256(path.read_bytes()).hexdigest()


def file_entry(pack, entry):
    relative = PurePosixPath(entry['path'])
    require(not relative.is_absolute() and '..' not in relative.parts and '\\' not in entry['path'], 'unsafe workload path')
    path = pack / relative
    require(path.resolve().is_relative_to(pack.resolve()) and path.is_file(), 'missing/outside workload file')
    require(digest(path) == entry['sha256'], 'workload checksum mismatch: ' + entry['path'])
    return path


def module(source, generator='tools/generate_workloads.py'):
    require(generator in ('tools/generate_workloads.py', 'tools/generate_adversarial_workloads.py'), 'unknown local workload generator')
    spec = importlib.util.spec_from_file_location('workload_generator', source / generator)
    out = importlib.util.module_from_spec(spec); spec.loader.exec_module(out)
    return out


def row_keys(rows):
    encoded = [canonical(row) for row in rows]
    require(len(encoded) == len(set(encoded)), 'duplicate native row or signed delta')
    return set(encoded)


def legacy_verify(source, manifest):
    legacy = json.loads(file_entry(source, manifest['legacy_inventory']).read_text())
    require(legacy['schema_version'] == 1 and legacy['kind'] == 'crown_legacy_workload_inventory', 'unknown legacy inventory format')
    for name, expected in legacy['source_sha256_local'].items():
        path = file_entry(source, {'path': name, 'sha256': expected})
        if name in legacy['source_git_blob_at_pin']:
            content = path.read_bytes()
            blob = hashlib.sha1(b'blob ' + str(len(content)).encode() + b'\0' + content).hexdigest()
            require(blob == legacy['source_git_blob_at_pin'][name], 'legacy Git blob drift')
    labels, scenarios = set(), []
    for entry in legacy['specs']:
        raw = {}; text = (source / entry['path']).read_text()
        for key, value in re.findall(r'(?m)^([^#\s=]+)=(.*)$', text):
            match = re.fullmatch(r'task(\d+)\.(.*)', key)
            if match: raw.setdefault(int(match[1]), {})[match[2]] = value
        count = int(re.search(r'spec.tasks.count=(\d+)', text)[1])
        require(len(raw) == count == entry['task_rows'] and set(raw) == set(range(1, count + 1)), 'legacy scenario count mismatch')
        require({row['experiment.name'] for row in raw.values()} == set(entry['entries']), 'legacy spec label mismatch')
        for task, properties in sorted(raw.items()):
            labels.add(properties['experiment.name'])
            scenarios.append({'id': Path(entry['path']).stem + '/task' + str(task), 'spec': entry['path'],
                              'task': task, 'label': properties['experiment.name'], 'properties': properties})
    require(scenarios == legacy['scenarios'], 'legacy task properties/scenarios were omitted or changed')
    require(labels == {query['label'] for query in legacy['query_entries']}, 'legacy query coverage mismatch')
    for query in legacy['query_entries']:
        require(query['execution_status'] == 'source_inspected_not_runnable' and query['data_record'] == 'legacy_external_data_unavailable', 'legacy inspection presented as native reproduction')
        require(query['scenario_ids'] == [row['id'] for row in scenarios if row['label'] == query['label']], 'legacy scenario/query binding mismatch')
        for field in ['head_and_semantics', 'shape', 'r1', 'update_contract', 'expected_backend', 'output_contract']:
            require(isinstance(query[field], str) and query[field], 'missing legacy classification field: ' + field)
    require(all(not row['use_for_native_run'] and row['bytes_sha256'] is None for row in legacy['data_records']), 'unknown external bytes used as native data')
    external = json.loads(file_entry(source, manifest['external_imports']).read_text())
    require(external['schema_version'] == 1 and external['kind'] == 'external_workload_import_registry', 'unknown external import registry')
    packets = {}; classified = 0
    for suite in external['suites']:
        require(not suite['native_timing_eligible'] and
                all(suite[field] is None for field in ['catalog', 'data_checksum', 'data_license']), 'unverified external benchmark admitted')
        if suite['import_status'] == 'not_imported':
            require(suite['pinned_sql'] is None, 'unclassified source has a false pin')
            continue
        require(suite['import_status'] in ['classified_source_only', 'classified_variant_sources_only', 'classified_windowed_sources_only'], 'unknown import status')
        binding = suite['pinned_sql']; entry = binding['packet']; path = file_entry(source, entry)
        if entry['path'] not in packets:
            packet = json.loads(path.read_text())
            if packet['kind'] == 'crown_imported_query_inventory':
                from verify_imported_workloads import verify
                verify(source, packet)
                packets[entry['path']] = {query['label'] for query in packet['queries']}
            else:
                require(packet['kind'] == 'crown_legacy_workload_inventory', 'unknown source packet')
                packets[entry['path']] = {query['label'] for query in packet['query_entries']}
        require(binding['labels'] and set(binding['labels']) <= packets[entry['path']], 'suite/source query labels mismatch')
        classified += 1
    return {'legacy_labels': len(labels), 'legacy_scenarios': len(scenarios),
            'legacy_source_fingerprints': len(legacy['source_sha256_local']),
            'legacy_pinned_blobs': len(legacy['source_git_blob_at_pin']),
            'external_datasets_pending': len(external['suites']), 'classified_suite_source_records': classified}


# Static means no native replay here; trusted generator code and SQLite still execute.
def static_verify(source, pack):
    schema = json.loads((source / 'schemas/workload-manifest-v1.schema.json').read_text())
    jsonschema.Draft202012Validator.check_schema(schema)
    validator = jsonschema.Draft202012Validator(schema)
    manifest = json.loads((pack / 'manifest.json').read_text()); validator.validate(manifest)
    options = manifest['generator']; generator = module(source, options['path'])
    require(digest(source / options['path']) == options['sha256'], 'generator checksum mismatch')
    expected = generator.build(options['seed'], options['scale'], options['query_ids'])
    actual = {str(p.relative_to(pack)): p.read_bytes() for p in pack.rglob('*') if p.is_file()}
    require(actual == expected, 'reproducible bytes/oracle/regime/coverage metadata differ')
    queries = {q['id']: q for q in manifest['queries']}
    require(len(queries) == len(manifest['queries']), 'duplicate query ID')
    licenses = {record['id'] for record in manifest['licenses']}
    seen, events, checked_files = set(), 0, set()
    for query in queries.values():
        for field in ['sql', 'catalog']:
            file_entry(pack, query[field]); checked_files.add(query[field]['path'])
        edges = [a['variables'] for a in query['structure']['atoms']]
        body_acyclic = generator.acyclic(edges)
        require(body_acyclic == query['structure']['body_alpha_acyclic'], 'body classification mismatch')
        require((body_acyclic and generator.acyclic(edges + [query['head']])) == query['structure']['free_connex'],
                'free-connex classification mismatch')
    for workload in manifest['workloads']:
        require(workload['id'] not in seen and workload['query'] in queries, 'duplicate or unknown workload/query')
        seen.add(workload['id']); require(workload['license_record'] in licenses, 'missing data license disposition')
        for field in ['events', 'oracle']:
            file_entry(pack, workload[field]); checked_files.add(workload[field]['path'])
        expected_rows = json.loads((pack / workload['oracle']['path']).read_text())
        records = [json.loads(line) for line in (pack / workload['events']['path']).read_text().splitlines()]
        require(len(records) == len(expected_rows['epochs']) == workload['events_count'], 'event/oracle count mismatch')
        events += len(records)
        for index, (event, epoch) in enumerate(zip(records, expected_rows['epochs']), 1):
            require(event['sequence'] == epoch['sequence'] == index, 'noncontiguous physical sequence')
            require(event['source_position'] == {'source': workload['source_id'], 'offset': index}, 'source position mismatch')
    # Explicit malformed descriptors and FIFO promises must be rejected too.
    mutations = []
    bad = copy.deepcopy(manifest); bad['schema_version'] = 2; mutations.append(bad)
    bad = copy.deepcopy(manifest); bad['queries'][0]['hidden_extension'] = True; mutations.append(bad)
    bad = copy.deepcopy(manifest); bad['workloads'][0]['events_count'] = True; mutations.append(bad)
    require(all(not validator.is_valid(bad) for bad in mutations), 'closed schema accepted malformed metadata')
    try: file_entry(pack, {'path': '../manifest.json', 'sha256': '0' * 64})
    except ValueError: pass
    else: raise ValueError('outside-pack file accepted')
    violations = [
        ([('delete', 'r', [1], 'workload')], 'insert_only'),
        ([('insert', 'r', [1], 'delete_phase')], 'delete_after_charged_load'),
        ([('insert', 'r', [1], 'workload'), ('insert', 's', [2], 'workload'), ('delete', 's', [2], 'workload')], 'global_fifo'),
        ([('insert', 'r', [1], 'workload'), ('insert', 'r', [2], 'workload'), ('delete', 'r', [2], 'workload')], 'per_relation_fifo')]
    for values, regime in violations:
        try: generator.verify_regime(values, regime)
        except ValueError: pass
        else: raise ValueError('regime violation accepted: ' + regime)
    # A separate seed/scale on a selected non-graph family must be replayable,
    # without forcing high-fanout output beyond the declared finite oracle cap.
    scaled = module(source).build(options['seed'] ^ 1, 2, ['hidden_witnesses', 'wide_strings'])
    scaled_manifest = json.loads(scaled['manifest.json'])
    validator.validate(scaled_manifest)
    require(scaled_manifest['generator']['scale'] == 2 and len(scaled_manifest['workloads']) == 14, 'size/seed selector failed')
    return manifest, {**legacy_verify(source, manifest), 'queries': len(queries), 'workloads': len(seen), 'physical_events': events,
                      'files_checked': len(checked_files), 'deterministic_files': len(actual),
                      'malformed_metadata_rejected': len(mutations) + 1, 'regime_violations_rejected': len(violations),
                      'independent_oracles': ['finite_assignment_join', 'sqlite3_SQL_execution']}


def native_verify(source, pack, manifest, crown, replay, directory):
    calls = []
    def invoke(executable, arguments, expected=0, output=None):
        result = subprocess.run([str(executable), *map(str, arguments)], capture_output=True, text=True, timeout=180)
        require(result.returncode == expected, f'{arguments[0]} exit {result.returncode}: {result.stderr[-1200:]}')
        require(not result.stderr, f'unexpected native diagnostic: {result.stderr}')
        value = json.loads(result.stdout)
        if output: output.write_text(result.stdout)
        calls.append({'executable': str(executable), 'arguments': list(map(str, arguments)), 'exit_code': result.returncode,
                      'stdout_sha256': hashlib.sha256(result.stdout.encode()).hexdigest()})
        return value
    definitions, records, replays = {}, 0, 0
    for query in manifest['queries']:
        directory_query = directory / query['id']; directory_query.mkdir()
        sql = pack / query['sql']['path']; catalog = pack / query['catalog']['path']
        admission = invoke(crown, ['admit-sql', sql, catalog], 0 if query['expected_admission'] == 'admitted' else 1,
                           directory_query / 'admission.json')
        require(admission['admission_status'] == query['expected_admission'], 'native admission mismatch: ' + query['id'])
        if query['expected_admission'] != 'admitted': continue
        body_acyclic = admission['structure']['body']['acyclic']
        require(body_acyclic == query['structure']['body_alpha_acyclic'] and
                (body_acyclic and admission['structure']['augmented']['acyclic']) == query['structure']['free_connex'],
                'native/independent structural classification mismatch')
        canonical_catalog = invoke(crown, ['canonicalize-catalog', catalog])
        catalog_sha = hashlib.sha256(canonical(canonical_catalog).encode()).hexdigest()
        built = invoke(crown, ['compile', sql, catalog], output=directory_query / 'compiled.json')
        validated = invoke(crown, ['validate-plan', 'compiled', directory_query / 'compiled.json'])
        require(validated['physical_valid'] and validated['height_status'] == 'proven_minimum', 'unverified compiled workload')
        physical = directory_query / 'physical.json'; physical.write_text(canonical(built['physical']))
        definitions[query['id']] = (query, physical, catalog_sha)
    for workload in manifest['workloads']:
        if workload['query'] not in definitions: continue
        query, physical, catalog_sha = definitions[workload['query']]
        output = directory / workload['query'] / workload['regime']; output.mkdir()
        input_rows = [json.loads(line) for line in (pack / workload['events']['path']).read_text().splitlines()]
        for row in input_rows: row['catalog_sha256'] = catalog_sha
        bound = output / 'input.jsonl'; bound.write_text(''.join(canonical(row) + '\n' for row in input_rows))
        expected = json.loads((pack / workload['oracle']['path']).read_text())
        for backend in query['expected_backends']:
            for mode in ['delta', 'maintenance']:
                report = invoke(replay, [physical, bound, mode, backend], output=output / (backend + '-' + mode + '.json'))
                require(report['backend'] == backend and report['mode'] == mode, 'native backend/mode label mismatch')
                require(row_keys(report['initial_rows']) == row_keys(expected['initial_rows']), 'initial rows mismatch')
                require(report['records'] == len(report['epochs']) == workload['events_count'], 'native event count mismatch')
                for event, actual, oracle in zip(input_rows, report['epochs'], expected['epochs']):
                    label = workload['id'] + '/' + str(event['sequence']) + '/' + backend + '/' + mode
                    require(actual['sequence'] == oracle['sequence'] == event['sequence'], label + ': sequence mismatch')
                    require(actual['source_positions'] == {workload['source_id']: event['source_position']['offset']}, label + ': source mismatch')
                    require(row_keys(actual['current_rows']) == row_keys(oracle['current_rows']), label + ': current rows mismatch')
                    require(row_keys(actual['signed_delta']) == row_keys(oracle['signed_delta'] if mode == 'delta' else []), label + ': signed delta mismatch')
                    records += 1
                replays += 1
    (directory / 'commands.json').write_text(json.dumps(calls, indent=2) + '\n')
    return {'native_replays': replays, 'native_physical_epochs_checked': records, 'commands': len(calls),
            'backends': sorted({backend for q in manifest['queries'] for backend in q['expected_backends']}),
            'modes': ['delta', 'maintenance_with_full_snapshot_each_epoch'],
            'negative_admission_controls': sum(q['expected_admission'] != 'admitted' for q in manifest['queries']),
            'executables': {str(path): digest(path) for path in [crown, replay]}}


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--source', type=Path, required=True)
    parser.add_argument('--pack', type=Path)
    parser.add_argument('--static-only', action='store_true')
    parser.add_argument('--crown', type=Path)
    parser.add_argument('--replay', type=Path)
    parser.add_argument('--artifact-dir', type=Path)
    args = parser.parse_args(); source = args.source.resolve(); pack = (args.pack or source / 'benchmarks/workloads').resolve()
    manifest, result = static_verify(source, pack)
    if not args.static_only:
        require(args.crown and args.replay, 'native verification needs --crown and --replay')
        if args.artifact_dir:
            args.artifact_dir.mkdir(parents=True, exist_ok=False)
            result.update(native_verify(source, pack, manifest, args.crown.resolve(), args.replay.resolve(), args.artifact_dir))
            (args.artifact_dir / 'summary.json').write_text(json.dumps(result, indent=2) + '\n')
        else:
            with tempfile.TemporaryDirectory(prefix='crown-workloads-') as temporary:
                result.update(native_verify(source, pack, manifest, args.crown.resolve(), args.replay.resolve(), Path(temporary)))
    print('B02 PASS ' + json.dumps(result, sort_keys=True))


if __name__ == '__main__':
    try: main()
    except Exception as error:
        print('B02 verification failed: ' + str(error), file=sys.stderr)
        raise SystemExit(1)
