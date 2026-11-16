#!/usr/bin/env python3
"""Check both input programs against SQLite before permitting matched timing."""
from copy import deepcopy
import hashlib
import json
import os
from pathlib import Path
import subprocess
import sys
import tempfile
from types import SimpleNamespace
from unittest.mock import patch

sys.dont_write_bytecode = True


def require(value, message):
    if not value: raise RuntimeError(message)


def digest(path):
    return hashlib.sha256(path.read_bytes()).hexdigest()


def main():
    require(len(sys.argv) in [6, 7], 'usage: input_specialization.py CROWN COLLECTOR CLIENT SOURCE BUILD [NEW_ARTIFACT_DIRECTORY]')
    crown, collector, client, source, build = [Path(value).resolve() for value in sys.argv[1:6]]
    temporary = None
    if len(sys.argv) == 7:
        base = Path(sys.argv[6]).resolve(); base.mkdir(parents=True, exist_ok=False)
    else:
        temporary = tempfile.TemporaryDirectory(prefix='crown-input-program-'); base = Path(temporary.name)
    commands = []
    def invoke(label, argv, success=True):
        child = subprocess.run(list(map(str, argv)), capture_output=True, text=True, timeout=1200)
        stdout, stderr = base / (label + '.stdout'), base / (label + '.stderr')
        stdout.write_text(child.stdout); stderr.write_text(child.stderr)
        commands.append({'label': label, 'arguments': list(map(str, argv)), 'exit_code': child.returncode,
                         'stdout': stdout.name, 'stdout_sha256': digest(stdout), 'stderr': stderr.name, 'stderr_sha256': digest(stderr)})
        (base / 'commands.json').write_text(json.dumps(commands, indent=2) + '\n')
        require((child.returncode == 0) == success, label + ': ' + child.stderr[-2500:])
        if success: require(not child.stderr, label + ': unexpected diagnostic')
        else: require(not child.stdout, label + ': rejected call emitted a success report')
        return child

    output = base / 'preflight'
    argv = [sys.executable, source / 'tools/run_input_specialization.py', '--source', source, '--build-dir', build,
            '--crown', crown, '--collector', collector, '--client', client, '--output', output,
            '--width', '2', '--warmups', '0', '--repetitions', '1', '--preflight-only',
            '--max-total-bytes', str(256 * 1024**2)]
    invoke('matched-preflight', argv)
    packet = json.loads((output / 'experiment.json').read_text())
    require(packet['status'] == 'preflight_complete' and packet['external_failures'] == [] and packet['runs'] == [],
            'input-program preflight failed or ran timing')
    require(packet['correctness_gate'] == 'all_variants_all_prefixes_verified_before_timing' and
            packet['B04_accepted'] is False and packet['end_closure_verified'] is True, 'gate/closure scope differs')
    require(len(packet['declared_variants']) == len(packet['verification']) == 28 and
            all(row['availability'] == 'verified' for row in packet['verification']), 'declared mode/backend/case was omitted')
    require(all(digest(output / name) == sha for name, sha in packet['frozen_inputs'].items()), 'frozen query/request/oracle changed')
    reports = [(row, json.loads((output / row['stdout']).read_text())) for row in packet['verification']]
    require(sum(len(report['passes'][0]['epochs']) for _, report in reports) == 244, 'SQLite prefix coverage changed')
    require(all(report['output_protocol'] == packet['output_protocol'] for _, report in reports), 'output protocol differs')
    for row, report in reports:
        require(all(report[field] is None for field in ['shared_program_ns', 'execution_prepare_ns', 'read_request_ns']), 'verify exposed eligible timing')
        if row['execution'] == 'threaded_v1' and not report['constant_operator']:
            require(report['preparation']['instructions'] > 0 and report['preparation']['metadata_bytes'] > 0,
                    'threaded arm did not execute an admitted data program')
        if report['constant_operator']:
            require(report['preparation']['instructions'] == 0 and all(not epoch['actual']['rows'] and not epoch['actual']['delta']
                    for epoch in report['passes'][0]['epochs']), 'constant false compiled dormant source adapters')
    before = digest(output / 'experiment.json')
    invoke('no-overwrite', argv, False)
    require(digest(output / 'experiment.json') == before, 'rejected rerun mutated retained results')
    good_row, good = next((row, report) for row, report in reports if row['case'] == 'cast_repeat-w2' and
                         row['backend'] == 'indexed_chained_v1' and row['execution'] == 'threaded_v1')
    paths = {'sql': output / 'cast_repeat-w2.sql', 'catalog': output / 'cast_repeat-w2.catalog.json',
             'input': output / 'cast_repeat-w2.input.jsonl', 'catalog_sha256': good['catalog_sha256']}
    for label, field, value in [('bool-version', 'schema_version', True), ('unknown-mode', 'execution', 'callback'),
                                ('unknown-field', 'ignored', 1), ('zero-preparation', 'preparation', {'work': 0, 'instructions': 100000})]:
        request = {**good['request'], field: value}; path = base / (label + '.json'); path.write_text(json.dumps(request))
        invoke(label, [client, paths['sql'], paths['catalog'], paths['input'], path], False)
    bad_input = base / 'wrong-catalog.jsonl'
    trace = [json.loads(line) for line in paths['input'].read_text().splitlines()]
    trace[0]['catalog_sha256'] = '0' * 64; bad_input.write_text(''.join(json.dumps(event) + '\n' for event in trace))
    request = base / 'good-request.json'; request.write_text(json.dumps(good['request']))
    invoke('wrong-catalog-binding', [client, paths['sql'], paths['catalog'], bad_input, request], False)

    sys.path.insert(0, str(source / 'tools'))
    import run_input_specialization as runner
    case = next(case for case in packet['cases'] if case['id'] == good_row['case'])
    expected = json.loads((output / 'cast_repeat-w2.expected.json').read_text())
    received = runner.inspect(case, good['request'], good, expected, paths)
    mutations = [(['catalog_sha256'], '0' * 64), (['execution_key'], 'crown-input-interpreted-v1'),
                 (['passes', 0, 'owner_prepared_instructions'], 0),
                 (['passes', 0, 'epochs', 0, 'phase'], 'wrong-phase'),
                 (['passes', 0, 'epochs', 0, 'native_work'], -1),
                 (['passes', 0, 'epochs', 0, 'actual', 'delta'], []),
                 (['passes', 0, 'epochs', 0, 'actual', 'rows'], [[0, 0, 7], [0, 0, 7]])]
    for location, value in mutations:
        bad = deepcopy(good); parent = bad
        for key in location[:-1]: parent = parent[key]
        parent[location[-1]] = value
        try: runner.inspect(case, good['request'], bad, expected, paths, received)
        except ValueError: pass
        else: raise RuntimeError('receiver accepted tampered capture at ' + str(location))
    # Shape-only receiver controls: convert a real verified capture to a
    # zero-clock measure-shaped record, without claiming a native timing run.
    measured = deepcopy(good); measured['command'] = 'measure'
    measured['request']['command'] = 'measure'
    for field in ['read_request_ns', 'shared_program_ns', 'execution_prepare_ns']: measured[field] = 0
    for native_pass in measured['passes']:
        native_pass['initial_rows'] = None
        for field in ['initialize_ns', 'loop_wall_ns', 'teardown_ns']: native_pass[field] = 0
        for epoch in native_pass['epochs']:
            epoch['actual'] = None
            for field in ['apply_ns', 'output_ns', 'release_ns']: epoch[field] = 0
    runner.inspect(case, measured['request'], measured, expected, paths, received)
    for location, value in [(['read_request_ns'], -1), (['passes', 0, 'initialize_ns'], True),
            (['passes', 0, 'loop_wall_ns'], None), (['passes', 0, 'teardown_ns'], 0.5),
            (['passes', 0, 'epochs', 0, 'apply_ns'], -1), (['passes', 0, 'epochs', 0, 'output_ns'], None),
            (['passes', 0, 'epochs', 0, 'release_ns'], True), (['passes', 0, 'initial_rows'], []),
            (['passes', 0, 'epochs', 0, 'actual'], {})]:
        bad = deepcopy(measured); parent = bad
        for key in location[:-1]: parent = parent[key]
        parent[location[-1]] = value
        try: runner.inspect(case, bad['request'], bad, expected, paths, received)
        except ValueError: pass
        else: raise RuntimeError('receiver accepted malformed measured clock/capture at ' + str(location))
    arguments = SimpleNamespace(source=source, build_dir=build, crown=crown, collector=collector, client=client,
        output=base / 'guard-must-not-create', repetitions=1, warmups=0, command_timeout=180, max_total_bytes=1024**3,
        width=[2], backend=None, cpu=None, preflight_only=False, schedule_seed=0)
    with patch.object(runner, 'build_provenance', side_effect=AssertionError('CPU guard must precede build/native inspection')):
        for cpu, preflight, message in [(None, False, 'explicit CPU'), (max(os.sched_getaffinity(0)) + 1, True, 'affinity')]:
            arguments.cpu, arguments.preflight_only = cpu, preflight
            try: runner.run(arguments)
            except ValueError as error: require(message in str(error), 'unexpected CPU rejection')
            else: raise RuntimeError('missing CPU/affinity guard')
    require(not arguments.output.exists(), 'CPU rejection created a study')
    print('Input specialization PASS:28 matched mode/backend gates,244 SQLite prefixes, work identity, constant false, request/catalog/capture negatives and no-overwrite. No timing or full B04 acceptance.')
    if temporary is not None: temporary.cleanup()


if __name__ == '__main__':
    try: main()
    except Exception as error: print(str(error), file=sys.stderr); raise SystemExit(1)
