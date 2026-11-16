#!/usr/bin/env python3
"""Check cold experimental upper admission without weakening minimum artifacts."""
from pathlib import Path
import copy
import hashlib
import json
import sqlite3
import subprocess
import sys
import tempfile

import jsonschema

sys.dont_write_bytecode = True
UPPER_TAG = 'independently_checked_original_lower_actual_upper_v1'
MINIMUM_TAG = 'independently_checked_equal_height_upper_v1'


def require(value, message):
    if not value:
        raise RuntimeError(message)


def canonical(value):
    return json.dumps(value, sort_keys=True, separators=(',', ':'), ensure_ascii=False)


def validators(root):
    documents = {path.name: json.loads(path.read_text()) for path in (root / 'schemas').glob('*.schema.json')}
    store = {}
    for name, document in documents.items():
        store[(root / 'schemas' / name).as_uri()] = document
        if '$id' in document:
            store[document['$id']] = document
    result = {}
    for name in ['compiled-workflow-v1.schema.json', 'compiled-candidate-v2.schema.json',
                 'compiled-experimental-upper-v3.schema.json', 'workload-measurement-v2.schema.json']:
        document = documents[name]
        jsonschema.Draft202012Validator.check_schema(document)
        result[name] = jsonschema.Draft202012Validator(
            document, resolver=jsonschema.RefResolver(
                base_uri=(root / 'schemas' / name).as_uri(), referrer=document, store=store))
    return result


def oracle(sql, events):
    database = sqlite3.connect(':memory:')
    for table in ['r0', 'r1']:
        database.execute(f'CREATE TABLE {table}(c0 INTEGER NOT NULL,c1 INTEGER NOT NULL,PRIMARY KEY(c0,c1))')
    previous = set(database.execute(sql))
    result = {'initial_rows': sorted(map(list, previous)), 'epochs': []}
    for event in events:
        table = event['table']
        require(table in ['r0', 'r1'], 'unexpected two-relation oracle table')
        if event['operation'] == 'insert':
            database.execute(f'INSERT OR IGNORE INTO {table} VALUES (?,?)', event['values'])
        else:
            require(event['operation'] == 'delete', 'unexpected oracle update operation')
            database.execute(f'DELETE FROM {table} WHERE c0=? AND c1=?', event['values'])
        current = set(database.execute(sql))
        delta = [{'operation': operation, 'values': list(row)}
                 for operation, rows in [('delete', previous - current), ('insert', current - previous)]
                 for row in sorted(rows)]
        result['epochs'].append({'sequence': event['sequence'], 'phase': 'artifact_control',
                                 'current_rows': sorted(map(list, current)), 'signed_delta': delta})
        previous = current
    database.close()
    return result


def chain(tree):
    nodes = [copy.deepcopy(node) for node in tree['nodes'] if node['kind'] == 'native']
    require(len(nodes) == 2, 'fixture must retain exactly two native occurrences')
    for index, node in enumerate(nodes):
        node.pop('separator', None)
        node['children'] = [nodes[index + 1]['id']] if index + 1 < len(nodes) else []
    return {'schema_version': 1, 'catalog_version': tree['catalog_version'], 'semantics': 'set',
            'root': nodes[0]['id'], 'nodes': nodes, 'native_height': 2}


def main():
    require(len(sys.argv) in [4, 5], 'usage: measurement_artifacts.py CROWN COLLECTOR SOURCE [ARTIFACT_DIRECTORY]')
    crown, collector, root = [Path(value).resolve() for value in sys.argv[1:4]]
    temporary = None
    if len(sys.argv) == 5:
        base = Path(sys.argv[4]).resolve()
        base.mkdir(parents=True, exist_ok=False)
    else:
        temporary = tempfile.TemporaryDirectory(prefix='crown-measurement-artifacts-')
        base = Path(temporary.name)
    schemas = validators(root)
    commands = []

    def write(name, value):
        path = base / name
        path.write_text(canonical(value) + '\n')
        return path

    def invoke(label, arguments, success=True):
        result = subprocess.run([str(argument) for argument in arguments], capture_output=True,
                                text=True, timeout=120)
        stdout, stderr = base / (label + '.stdout'), base / (label + '.stderr')
        stdout.write_text(result.stdout)
        stderr.write_text(result.stderr)
        commands.append({'label': label, 'arguments': list(map(str, arguments)), 'exit_code': result.returncode,
                         'stdout': stdout.name, 'stderr': stderr.name,
                         'stdout_sha256': hashlib.sha256(stdout.read_bytes()).hexdigest(),
                         'stderr_sha256': hashlib.sha256(stderr.read_bytes()).hexdigest()})
        write('commands.json', commands)
        require((result.returncode == 0) == success, f'{label}: {result.stderr[-2000:]}')
        if success:
            require(not result.stderr, label + ': unexpected successful-command diagnostic')
        else:
            require(not result.stdout, label + ': rejected artifact emitted a report')
        return result

    fixture = root / 'benchmarks/workloads'
    sql_path = fixture / 'queries/full_path_2/query.sql'
    catalog_path = fixture / 'queries/full_path_2/catalog.json'
    sql = sql_path.read_text()
    catalog = json.loads(invoke('canonical-catalog', [crown, 'canonicalize-catalog', catalog_path]).stdout)
    catalog_sha = hashlib.sha256(canonical(catalog).encode()).hexdigest()
    events = [json.loads(line) for line in (fixture / 'traces/full_path_2/mixed/events.template.jsonl').read_text().splitlines()]
    require(0 < len(events) <= 256, 'artifact trace exceeds finite test horizon')
    for event in events:
        event['catalog_sha256'] = catalog_sha
    updates = base / 'events.jsonl'
    updates.write_text(''.join(canonical(event) + '\n' for event in events))
    expected = oracle(sql, events)
    retained = json.loads((fixture / 'traces/full_path_2/mixed/expected.json').read_text())
    require(expected['initial_rows'] == retained['initial_rows'], 'SQLite initial result differs from retained independent oracle')
    for actual, original in zip(expected['epochs'], retained['epochs'], strict=True):
        require(actual['current_rows'] == original['current_rows'] and
                sorted(map(canonical, actual['signed_delta'])) == sorted(map(canonical, original['signed_delta'])),
                'SQLite prefix differs from retained independent oracle')
    expected_path = write('sqlite-expected.json', expected)
    request = {'schema_version': 1, 'command': 'verify', 'output_mode': 'delta', 'codec': 'jsonl',
               'sink': 'file', 'sink_delay_us': 0, 'observation': 'off', 'workload_counters': False,
               'memory_limit_bytes': 256 * 1024 * 1024, 'max_events': 256, 'max_output_calls': 100000,
               'max_encoded_bytes': 64 * 1024 * 1024, 'phases': ['artifact_control'] * len(events),
               'label': 'experimental-upper-admission', 'preflight_receipt_sha256': None}
    request_path = write('request.json', request)
    sys.path.insert(0, str(root / 'tools'))
    from run_measurements import indexed_options
    options_path = write('indexed-options.json', indexed_options())
    accepted = rejected = 0

    def receive(label, document, success=True, upper=False):
        nonlocal accepted, rejected
        path = write(label + '.artifact.json', document)
        sink = base / (label + '.unused-sink')
        response = invoke(label, [collector, path, updates, request_path, expected_path, sink], success)
        require(not sink.exists(), label + ': verification/failure created a sink')
        if not success:
            rejected += 1
            return
        schemas['compiled-experimental-upper-v3.schema.json' if upper else
                'compiled-candidate-v2.schema.json' if document['schema_version'] == 2 else
                'compiled-workflow-v1.schema.json'].validate(document)
        report = json.loads(response.stdout)
        schemas['workload-measurement-v2.schema.json'].validate(report)
        require(report['verified'] and report['records'] == len(events), label + ': incomplete verification')
        if upper:
            height = document['physical']['verification']['native_height']
            minimum = document['height_certificate']['minimum_height']
            require(report['experimental_height'] == {'status': 'checked_upper_only',
                    'original_minimum_height': minimum, 'actual_native_height': height,
                    'height_gap': height - minimum}, label + ': experimental height mislabelled')
        else:
            require('experimental_height' not in report, label + ': original report shape changed')
        accepted += 1

    for backend in ['reference', 'indexed']:
        arguments = [crown, 'compile', sql_path, catalog_path]
        if backend == 'indexed':
            arguments += ['--physical-options', options_path]
        minimum = json.loads(invoke(backend + '-compile', arguments).stdout)
        require(minimum['height_certificate']['minimum_height'] == 1, 'two-edge generalized fixture must have h*=1')
        normalized = write(backend + '-normalized.json', minimum['physical']['source']['program'])
        tree = write(backend + '-ordinary-tree.json', chain(minimum['physical']['tree']))
        arguments = [crown, 'lower-normalized', normalized, tree]
        if backend == 'indexed':
            arguments.append(options_path)
        taller = json.loads(invoke(backend + '-lower-ordinary', arguments).stdout)
        require(taller['verification']['valid'] and taller['verification']['native_height'] == 2,
                'actual ordinary upper must independently validate at height two')
        equal = {**minimum, 'schema_version': 2, 'height_binding': MINIMUM_TAG}
        upper = {**minimum, 'schema_version': 3, 'height_binding': UPPER_TAG, 'physical': taller}
        for mode in ['snapshot', 'delta']:
            request['output_mode'] = mode
            request_path = write('request-' + mode + '.json', request)
            receive(backend + '-' + mode + '-minimum-v1', minimum)
            receive(backend + '-' + mode + '-minimum-v2', equal)
            receive(backend + '-' + mode + '-upper-v3', upper, upper=True)
            receive(backend + '-' + mode + '-equal-upper-v3', {**upper, 'physical': minimum['physical']}, upper=True)
        for version in [1, 2]:
            document = {**minimum, 'schema_version': version, 'physical': taller}
            if version == 2:
                document['height_binding'] = MINIMUM_TAG
            receive(backend + '-taller-minimum-v' + str(version), document, False)
        renamed = copy.deepcopy(minimum['physical']['tree'])
        names = {node['id']: 'alternative-' + node['id'] for node in renamed['nodes']}
        renamed['root'] = names[renamed['root']]
        for node in renamed['nodes']:
            node['id'] = names[node['id']]
            node['children'] = [names[child] for child in node['children']]
        if 'connex' in renamed:
            renamed['connex'] = [names[node] for node in renamed['connex']]
        renamed_path = write(backend + '-alternative-minimum-tree.json', renamed)
        arguments = [crown, 'lower-normalized', normalized, renamed_path]
        if backend == 'indexed':
            arguments.append(options_path)
        renamed_plan = json.loads(invoke(backend + '-lower-alternative-minimum', arguments).stdout)
        receive(backend + '-alternative-witness-v1', {**minimum, 'physical': renamed_plan}, False)
        receive(backend + '-alternative-witness-v2', {**equal, 'physical': renamed_plan})
        if backend == 'reference':
            controls = [
                ('unknown-tag', ['height_binding'], 'unverified'),
                ('cross-version-tag', ['height_binding'], MINIMUM_TAG),
                ('boolean-version', ['schema_version'], True),
                ('floating-version', ['schema_version'], 3.0),
                ('false-lower', ['height_certificate', 'minimum_height'], 2),
                ('missing-lower', ['height_certificate', 'lower_bounds'], []),
                ('unrelated-query', ['height_certificate', 'query_binding', 'query', 'head'], []),
                ('declared-physical-height', ['physical', 'verification', 'native_height'], 1),
                ('declared-tree-height', ['physical', 'tree', 'native_height'], 1),
                ('physical-binding', ['physical', 'binding', 'physical_sha256'], '0' * 64),
                ('unknown-artifact-field', ['unknown_field'], True),
            ]
            for label, location, value in controls:
                document = copy.deepcopy(upper)
                target = document
                for field in location[:-1]:
                    target = target[field]
                target[location[-1]] = value
                receive(label, document, False)
            document = copy.deepcopy(upper)
            document['physical']['tree']['nodes'][0]['children'] = []
            receive('disconnected-actual-tree', document, False)
            document = copy.deepcopy(upper)
            witness = document['height_certificate']['tree']
            root_node = next(node for node in witness['nodes'] if node['id'] == witness['root'])
            require(root_node['children'], 'original witness must have children before corruption')
            root_node['children'] = []
            receive('corrupt-original-witness', document, False)
            mutated = {'schema_version': 3, 'height_binding': UPPER_TAG, 'physical': taller,
                       'height_certificate': None}
            require(not schemas['compiled-experimental-upper-v3.schema.json'].is_valid(mutated),
                    'closed experimental schema accepts absent original proof')
            receive('null-original-proof', mutated, False)
            report = json.loads((base / (backend + '-delta-upper-v3.stdout')).read_text())
            report['experimental_height']['unknown_field'] = 0
            require(not schemas['workload-measurement-v2.schema.json'].is_valid(report),
                    'experimental report schema accepts unknown metadata')
    false_sql = base / 'constant-false.sql'
    false_sql.write_text(sql.rstrip().removesuffix(';') + ' AND 1=0;\n')
    constant = json.loads(invoke('compile-constant-false', [crown, 'compile', false_sql, catalog_path]).stdout)
    require(constant['physical']['route'] == 'constant_false' and constant['height_certificate'] is None,
            'constant-false setup must carry no structural minimum claim')
    empty_input = base / 'empty.jsonl'
    empty_input.write_text('')
    empty_expected = write('empty-expected.json', {'initial_rows': [], 'epochs': []})
    empty_request = write('empty-request.json', {**request, 'phases': []})
    for version in [1, 2, 3]:
        document = {**constant, 'schema_version': version}
        if version != 1:
            document['height_binding'] = MINIMUM_TAG if version == 2 else UPPER_TAG
        path = write('constant-false-v' + str(version) + '.artifact.json', document)
        response = invoke('constant-false-v' + str(version),
                          [collector, path, empty_input, empty_request, empty_expected, base / 'constant-unused-sink'],
                          version == 1)
        require(not (base / 'constant-unused-sink').exists(), 'constant verification/failure created a sink')
        if version == 1:
            report = json.loads(response.stdout)
            schemas['workload-measurement-v2.schema.json'].validate(report)
            require(report['verified'] and report['records'] == 0 and 'experimental_height' not in report,
                    'constant-false original report shape changed')
            accepted += 1
        else:
            rejected += 1
    summary = {'status': 'pass', 'accepted': accepted, 'rejected': rejected,
               'oracle_prefixes': len(events), 'backends': 2, 'output_modes': ['snapshot', 'delta'],
               'performance_claim': False, 'B04_accepted': False}
    write('result.json', summary)
    print('B04 artifact admission PASS: ' + canonical(summary))
    if temporary is not None:
        temporary.cleanup()


if __name__ == '__main__':
    try:
        main()
    except Exception as error:
        print(str(error), file=sys.stderr)
        raise SystemExit(1)
