#!/usr/bin/env python3
"""Check B05 scaling, oracle gates, arena diagnostics and honest batch failure."""
from pathlib import Path
import copy
import hashlib
import json
import subprocess
import sys
import tempfile
from unittest.mock import patch

import jsonschema

sys.dont_write_bytecode = True


def require(value, message):
    if not value:
        raise RuntimeError(message)


def free_connex_controls(source):
    """Literal H/H+F controls exercise both producers without sharing their predicate."""
    sys.path.insert(0, str(source / 'tools'))
    import generate_workloads as b02
    import generate_adversarial_workloads as b05

    # The full-head triangle's universal head edge makes H+F acyclic;
    # its cyclic body still prevents free-connex membership.
    controls = {
        'cyclic_triangle_control': ([['a', 'b'], ['b', 'c'], ['a', 'c']], ['a', 'b', 'c'], False, False),
        'nonfree_endpoint_control': ([['x0', 'x1'], ['x1', 'x2']], ['x0', 'x2'], True, False),
        'full_path_2': ([['x0', 'x1'], ['x1', 'x2']], ['x0', 'x1', 'x2'], True, True),
    }

    def check_labels(files, expected):
        queries = {q['id']: q for q in json.loads(files['manifest.json'])['queries']}
        for identifier, (scopes, head, body, free_connex) in expected.items():
            query = queries[identifier]
            require([a['variables'] for a in query['structure']['atoms']] == scopes and query['head'] == head,
                    'literal structural control changed shape: ' + identifier)
            require(query['structure']['body_alpha_acyclic'] is body and query['structure']['free_connex'] is free_connex,
                    'literal free-connex classification differs: ' + identifier)

    check_labels(b02.build(selected=list(controls)), controls)
    # B05's public corpus contains positives only. Inject these small shapes
    # into its existing case boundary without changing any maintained workload.
    cases = dict(zip(('volume_full', 'volume_projected', 'path_2'), controls.values()))

    def case(family, scale):
        scopes, head, _, _ = cases[family]
        spec = b02.query(family, scopes, head)
        events = [('insert', table['name'], (0,) * len(table['columns']), 'charged_load')
                  for table in spec['catalog']['catalog']['tables']]
        return spec, events, {'family': family, 'scale_selector': scale, 'axis': 'source_rows',
            'axis_value': len(events), 'expected_final_rows': 1, 'regime': 'insert_only'}

    with patch.object(b05, 'case', case):
        check_labels(b05.build(selected=list(cases)), cases)


def main():
    crown, collector, source, build = [Path(x).resolve() for x in sys.argv[1:5]]
    require(crown == build / 'crown' and collector == build / 'crown_measure_workload', 'test binaries differ from the explicit build')
    free_connex_controls(source)
    sys.path.insert(0, str(source / 'tools'))
    from generate_adversarial_workloads import build as generate
    from verify_workloads import static_verify
    from analyze_adversarial_scalability import analyze
    temporary = None
    if len(sys.argv) == 6:
        base = Path(sys.argv[5]).resolve()
        base.mkdir(parents=True, exist_ok=False)
    else:
        temporary = tempfile.TemporaryDirectory(prefix='crown-b05-')
        base = Path(temporary.name)
    pack = base / 'all-families'
    pack.mkdir()
    generated = generate(scale=1)
    for name, content in generated.items():
        path = pack / name
        path.parent.mkdir(parents=True, exist_ok=True)
        path.write_bytes(content)
    manifest, _ = static_verify(source, pack)
    axes = {a['family']: a for a in json.loads(generated['axes.json'])['cases']}
    require(len(manifest['queries']) == len(manifest['workloads']) == 19, 'missing stress dimension')
    require(axes['fanout_full']['maximum_result_rows'] == 8 and axes['fanout_projected']['maximum_result_rows'] == 1, 'output extrema differ')
    require(axes['empty_intersection']['maximum_result_rows'] == 0, 'empty-output stress is nonempty')
    larger = json.loads(generate(scale=2, selected=['volume_full', 'churn_fresh'])['axes.json'])
    for axis in larger['cases']:
        require(axis['axis_value'] == 4 * axes[axis['family']]['axis_value'], 'scale label did not change physical stress')
    require(max(axes['churn_fresh']['live_source_rows']) == 9 and axes['churn_fresh']['live_source_rows'][-1] == 0, 'churn live population differs')
    before = (pack / 'axes.json').read_bytes()
    (pack / 'axes.json').write_bytes(before + b' ')
    try:
        static_verify(source, pack)
    except ValueError:
        pass
    else:
        raise RuntimeError('altered workload evidence accepted')
    (pack / 'axes.json').write_bytes(before)
    schema = json.loads((source / 'schemas/workload-manifest-v1.schema.json').read_text())
    malicious = copy.deepcopy(manifest)
    malicious['generator']['path'] = 'tools/unreviewed.py'
    require(not jsonschema.Draft202012Validator(schema).is_valid(malicious), 'unlisted generator admitted')

    records = []

    def invoke(arguments, success=True):
        result = subprocess.run(list(map(str, arguments)), text=True, capture_output=True, timeout=600)
        index = len(records)
        (base / f'command-{index}.stdout').write_text(result.stdout)
        (base / f'command-{index}.stderr').write_text(result.stderr)
        records.append({'arguments': list(map(str, arguments)), 'exit_code': result.returncode,
            'stdout_sha256': hashlib.sha256(result.stdout.encode()).hexdigest(),
            'stderr_sha256': hashlib.sha256(result.stderr.encode()).hexdigest()})
        (base / 'commands.json').write_text(json.dumps(records, indent=2) + '\n')
        require((result.returncode == 0) == success, result.stderr[-3000:])
        return result

    runner = [sys.executable, source / 'tools/run_adversarial_scalability.py', '--source', source,
        '--build-dir', build, '--suite', 'long_churn', '--scale', '1', '--scale', '2',
        '--repetitions', '1', '--warmups', '0']
    output = base / 'measured'
    invoke([*runner, '--output', output])
    derived = base / 'analysis'
    result = analyze(output, derived)
    require(result['measured_runs'] == 72 and result['parameter_points'] == 12, 'native mode/backend matrix differs')
    v2 = jsonschema.Draft202012Validator(json.loads((source / 'schemas/workload-measurement-v2.schema.json').read_text()))
    v1 = jsonschema.Draft202012Validator(json.loads((source / 'schemas/workload-measurement-v1.schema.json').read_text()))
    for case in json.loads((output / 'experiment.json').read_text())['cases']:
        directory = output / case['directory'] / 'native'
        axis = json.loads((directory.parent / 'workload/axes.json').read_text())['cases'][0]
        packet = json.loads((directory / 'experiment.json').read_text())
        for entry in packet['runs']:
            report = json.loads((directory / entry['raw_report']).read_text())
            v2.validate(report)
            require(all(e['storage']['source']['slots'] <= axis['source_slot_reuse_reference'] for e in report['epochs']), 'fixed-live churn retained historical source slots')
            legacy = copy.deepcopy(report)
            legacy['schema_version'] = 1
            for event in legacy['epochs']:
                del event['storage']
            v1.validate(legacy)
            invalid = copy.deepcopy(report)
            invalid['epochs'][0]['storage']['source']['untracked'] = 1
            require(not v2.is_valid(invalid), 'arena schema accepts untracked fields')
    marker = output / 'keep-existing'
    marker.write_text('preserve\n')
    invoke([*runner, '--output', output], False)
    require(marker.read_text() == 'preserve\n', 'existing output was removed')
    fake = base / 'incomplete-build'
    fake.mkdir()
    for name in ('crown', 'crown_measure_workload', 'CMakeCache.txt'):
        (fake / name).write_text('not an actual build\n')
    failed = base / 'failed-child'
    invoke([sys.executable, source / 'tools/run_adversarial_scalability.py', '--source', source,
        '--build-dir', fake, '--output', failed, '--family', 'volume_full', '--scale', '1',
        '--repetitions', '1', '--warmups', '0'], False)
    failure = json.loads((failed / 'experiment.json').read_text())
    require(failure['status'] == 'failed' and failure['cases'][0]['exit_code'] != 0, 'failed child became a successful batch')
    print('B05 controls PASS: 19 deterministic families, genuine size/history scaling, independent oracles, 72 native configurations across six churn shapes, arena/raw-v2/legacy-v1 checks, output preservation and nonzero child failure.')
    if temporary is not None:
        temporary.cleanup()


if __name__ == '__main__':
    main()
