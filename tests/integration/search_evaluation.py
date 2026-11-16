#!/usr/bin/env python3
"""Exercise genuine literal search, tiny-family coverage and observed C02 scoring."""
from fractions import Fraction
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
    if not value:
        raise RuntimeError(message)


def digest(path):
    return hashlib.sha256(path.read_bytes()).hexdigest()


def main():
    require(len(sys.argv) in [6, 7], 'usage: search_evaluation.py CROWN COLLECTOR SEARCHER SOURCE BUILD [NEW_ARTIFACT_DIRECTORY]')
    crown, collector, searcher, source, build = [Path(value).resolve() for value in sys.argv[1:6]]
    temporary = None
    if len(sys.argv) == 7:
        base = Path(sys.argv[6]).resolve(); base.mkdir(parents=True, exist_ok=False)
    else:
        temporary = tempfile.TemporaryDirectory(prefix='crown-finite-search-'); base = Path(temporary.name)
    records = []
    def invoke(label, argv, success=True):
        child = subprocess.run(list(map(str, argv)), capture_output=True, text=True, timeout=1200)
        stdout, stderr = base / (label + '.stdout'), base / (label + '.stderr')
        stdout.write_text(child.stdout); stderr.write_text(child.stderr)
        records.append({'label': label, 'arguments': list(map(str, argv)), 'exit_code': child.returncode,
                        'stdout': stdout.name, 'stdout_sha256': digest(stdout), 'stderr': stderr.name, 'stderr_sha256': digest(stderr)})
        (base / 'commands.json').write_text(json.dumps(records, indent=2) + '\n')
        require((child.returncode == 0) == success, label + ': ' + child.stderr[-2500:])
        if success: require(not child.stderr, label + ': unexpected diagnostic')
        else: require(not child.stdout, label + ': rejection emitted a success record')
        return child

    output = base / 'preflight'
    argv = [sys.executable, source / 'tools/run_search_evaluation.py', '--source', source, '--build-dir', build,
            '--crown', crown, '--collector', collector, '--searcher', searcher, '--output', output,
            '--case', 'full_path_2', '--case', 'tiny_c02', '--case', 'tiny_cycle', '--case', 'equal_scope_4',
            '--work', '0', '--work', '1000000', '--preflight-work', '5000000', '--preflight-only',
            '--warmups', '0', '--repetitions', '1', '--max-total-bytes', str(256 * 1024**2)]
    invoke('finite-preflight', argv)
    packet = json.loads((output / 'experiment.json').read_text())
    require(packet['status'] == 'preflight_complete' and packet['external_failures'] == [] and packet['runs'] == [],
            'finite search preflight failed or ran timing')
    require(packet['B04_accepted'] is False and len(packet['preflight']) == 43, 'method/budget/reference control was omitted')
    require(packet['end_closure_verified'] is True, 'compiled/input/launcher end closure was not verified')
    require(json.loads((output / packet['case_manifest']).read_text()) == packet['cases'], 'serialized source-case manifest differs')
    require(len(json.loads((output / packet['request_manifest']).read_text())['plans']) == 43, 'frozen request plan omitted a variant')
    require(all(digest(output / name) == expected for name, expected in packet['frozen_inputs'].items()), 'frozen source/request/proof file differs')
    require(sum(row['cases'] for row in packet['stop_frequency']) == 40, 'stop frequency lost a scheduled case/method/budget')
    reports = [(row, json.loads((output / row['stdout']).read_text())) for row in packet['preflight']]
    for row, report in reports:
        require(all(value is None for value in report['timings'].values()), 'verify mode exposed eligible timing')
        if row['method'] == 'literal_minimum' and row['work_limit'] == 0:
            require(report['algorithm']['algorithm'] == 'literal_normal_form_v1' and
                    report['algorithm']['status'] == 'resource_limit' and report['algorithm']['height'] is None,
                    'zero-work literal oracle was relabelled optimized/minimum')
    source_case = next(case for case in packet['cases'] if case['id'] == 'tiny_c02')
    reference = next(report for row, report in reports if row['case'] == 'tiny_c02' and row['reference_control'])
    require(reference['original']['height'] == 2 and reference['upstream_and_admission_exhausted'] and
            len(reference['candidates']) == 3, 'independent tiny three-plan family did not complete')
    native = reference['scoring']
    require(native['availability'] == 'actual_c02_census_scores' and native['actual_training_events'] == native['denominator'] == 6,
            'tiny C02 did not use actual six-input owner census')
    scores = {row['structural_key']: Fraction(int(row['numerator']), int(row['denominator'])) for row in native['scores']}
    require(sorted(scores.values()) == [Fraction(7, 6), Fraction(9, 6), Fraction(10, 6)] and
            scores[native['selected_key']] == Fraction(7, 6), 'observed C02 ratios differ from independent literal arithmetic')
    capped = next(report for row, report in reports if row['case'] == 'equal_scope_4' and
                  row['method'] == 'literal_family' and row['work_limit'] == 1000000)
    require(capped['algorithm']['resource_limited'] and capped['algorithm']['native_cap'] == 3 and
            not capped['upstream_and_admission_exhausted'], 'literal family cap was silently expanded or called complete')
    cycle = [report for row, report in reports if row['case'] == 'tiny_cycle']
    require(any(report['status'] == 'verified_infeasible' for report in cycle), 'actual infeasible query disappeared')
    require(any(row['case'] == 'tiny_c02' and row['C02_best_complete_reference_score'] == {'numerator': '7', 'denominator': '6'}
                for row in packet['comparisons']), 'complete-reference scoring optimum was not retained')
    before = digest(output / 'experiment.json')
    invoke('no-overwrite', argv, False)
    require(digest(output / 'experiment.json') == before, 'rejected rerun mutated completed study')
    good = next(report for row, report in reports if row['case'] == 'tiny_c02' and row['reference_control'])
    query_path = output / 'tiny_c02.cq.json'
    for label, field, value in [('bool-version', 'schema_version', True), ('unknown-method', 'method', 'tree-oracle'),
                                ('unknown-field', 'ignored', 1)]:
        bad = {**good['request'], field: value}; path = base / (label + '.json'); path.write_text(json.dumps(bad))
        invoke(label, [searcher, query_path, path], False)
    require(len(source_case['document']['query']['atoms']) == 3, 'tiny source dimensions changed')
    # These receiver guards are exercised without allowing a missing guard to
    # start build inspection, a child process or an accidental timing study.
    sys.path.insert(0, str(source / 'tools'))
    import run_search_evaluation as runner
    arguments = SimpleNamespace(source=source, build_dir=build, crown=crown, collector=collector, searcher=searcher,
        output=base / 'guard-must-not-create', repetitions=1, warmups=0, command_timeout=180, max_total_bytes=1024**3,
        proof_work=10000000, preflight_work=5000000, work=[0], case=['tiny_c02'], cpu=None, preflight_only=False, schedule_seed=0)
    with patch.object(runner, 'build_provenance', side_effect=AssertionError('CPU guard must precede any build/native invocation')):
        for cpu, preflight, expected in [(None, False, 'explicit CPU'), (max(os.sched_getaffinity(0)) + 1, True, 'affinity')]:
            arguments.cpu, arguments.preflight_only = cpu, preflight
            try: runner.run(arguments)
            except ValueError as error: require(expected in str(error), 'wrong cold CPU rejection')
            else: raise RuntimeError('missing CPU/affinity guard')
    require(not arguments.output.exists(), 'CPU rejection created a study')
    print('Finite search controls PASS:43 real method/budget/reference preflights; literal zero-work and family caps, three independent plans, observed7/6 C02 optimum, infeasibility, no-overwrite and closed-request negatives. No timing/B04 acceptance.')
    if temporary is not None: temporary.cleanup()


if __name__ == '__main__':
    try: main()
    except Exception as error: print(str(error), file=sys.stderr); raise SystemExit(1)
