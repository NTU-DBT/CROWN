#!/usr/bin/env python3
"""Receive the real B04 planning driver without running held-out timings."""
import collections
import hashlib
import json
from pathlib import Path
import subprocess
import sys
import tempfile

sys.dont_write_bytecode = True


def require(value, message):
    if not value:
        raise RuntimeError(message)


def digest(path):
    return hashlib.sha256(path.read_bytes()).hexdigest()


def main():
    require(len(sys.argv) in [6, 7], 'usage: component_planning.py CROWN COLLECTOR EXPORTER SOURCE BUILD [NEW_ARTIFACT_DIRECTORY]')
    crown, collector, exporter, source, build = [Path(value).resolve() for value in sys.argv[1:6]]
    temporary = None
    if len(sys.argv) == 7:
        base = Path(sys.argv[6]).resolve()
        base.mkdir(parents=True, exist_ok=False)
    else:
        temporary = tempfile.TemporaryDirectory(prefix='crown-component-planning-')
        base = Path(temporary.name)
    records = []
    command = [sys.executable, source / 'tools/run_component_planning.py', '--source', source,
               '--build-dir', build, '--crown', crown, '--collector', collector, '--exporter', exporter,
               '--query', 'full_star_3', '--backend', 'reference_ordered_v1', '--candidates', '4',
               '--warmups', '0', '--repetitions', '1', '--preflight-only', '--max-total-bytes', str(128 * 1024**2)]

    def invoke(name, arguments, success=True):
        result = subprocess.run(list(map(str, arguments)), capture_output=True, text=True, timeout=900)
        stdout, stderr = base / (name + '.stdout'), base / (name + '.stderr')
        stdout.write_text(result.stdout)
        stderr.write_text(result.stderr)
        records.append({'arguments': list(map(str, arguments)), 'exit_code': result.returncode,
                        'stdout': stdout.name, 'stdout_sha256': digest(stdout),
                        'stderr': stderr.name, 'stderr_sha256': digest(stderr)})
        (base / 'commands.json').write_text(json.dumps(records, indent=2) + '\n')
        require((result.returncode == 0) == success, name + ': ' + result.stderr[-2500:])
        if success:
            require(not result.stderr, name + ': unexpected diagnostic')
        return result

    output = base / 'qualified-preflight'
    invoke('qualified', [*command, '--output', output])
    packet = json.loads((output / 'experiment.json').read_text())
    commands = json.loads((output / 'commands.json').read_text())
    require(packet['status'] == 'preflight_complete_choices_frozen' and packet['unavailable_groups'] == 0,
            'real retained-family preflight did not finish')
    require(packet['B04_accepted'] is False and packet['runs'] == packet['analysis'] == [],
            'preflight became timing or full B04 acceptance')
    require(len(packet['groups']) == 1, 'unexpected query/backend scope')
    group = packet['groups'][0]
    first, final = group['exports']
    require(first['stage'] == 'preliminary_unqualified_preparation' and final['stage'] == 'final_after_all_preflights',
            'two-pass calibration stages were collapsed')
    require(first['index'] < min(row['index'] for row in packet['verification']) and
            max(row['index'] for row in packet['verification']) < final['index'],
            'qualified final calibration ran before all-envelope/all-trace correctness')
    require(not any(row['label'].startswith('heldout_') for row in commands), 'preflight launched held-out timings')
    exported = json.loads((output / final['stdout']).read_text())
    require({family['id'] for family in exported['families']} == {'exact', 'residual', 'meta'}, 'search family omitted')
    require(exported['proved_height'] == 1 and exported['ordinary']['candidates'] and
            all(row['height'] > 1 for row in exported['ordinary']['candidates']), 'taller ordinary controls omitted')
    frozen = json.loads((output / group['choices_file']).read_text())
    calibration = json.loads((output / group['calibration_file']).read_text())
    require(digest(output / group['choices_file']) == group['choices_sha256'] and
            digest(output / group['calibration_file']) == group['calibration_sha256'], 'frozen file hashes differ')
    require(calibration == exported['calibration'] and calibration['origin'] == 'actual_full_census_native_phases',
            'final pooled actual calibration changed or was replaced')
    require(frozen['calibration_coefficients_sha256'] == calibration.get('coefficients_sha256'), 'choices use another calibration')
    for family in frozen['families']:
        require({row['variant'] for row in family['statistics']} == {'full', 'sampled', 'stale', 'absent'},
                'statistics sensitivity arm omitted')
    train = next(row for row in json.loads((source / 'benchmarks/ranking/manifest.json').read_text())['traces']
                 if row['query'] == 'full_star_3' and row['role'] == 'train')
    events = [json.loads(line) for line in (source / 'benchmarks/ranking' / train['events']['path']).read_text().splitlines()]
    tables = json.loads((source / 'benchmarks/ranking/queries/full_star_3/catalog.json').read_text())['catalog']['tables']
    indices = {table['name']: index for index, table in enumerate(tables)}
    counts = collections.Counter((indices[row['table']], 'insert' if row['operation'] == 'insert' else 'erase') for row in events)
    require(frozen['forecast_inputs'] == len(events), 'forecast demand used evaluation horizon')
    require(exported['request']['input_demand'] == [{'table': table, 'operation': operation, 'inputs': counts[table, operation]}
            for table in range(len(tables)) for operation in ['insert', 'erase']], 'declared demand differs from TRAIN counts')
    traces = {row['trace'] for row in packet['verification']}
    require(len(traces) == 5 and len(packet['verification']) == group['envelope_count'] * 5,
            'a retained envelope or training/calibration/evaluation split skipped preflight')
    require(sum(len(row['origins']) for row in group['physical_plans'].values()) ==
            sum(len(family['candidates']) for family in exported['families']) + len(exported['ordinary']['candidates']),
            'physical dedup lost family/key/ordinary provenance')
    upper = minimum = False
    for row in packet['verification']:
        report = json.loads((output / row['stdout']).read_text())
        require(report['verified'] and report['output_mode'] == report['runtime_mode'] == 'maintenance', 'invalid actual preflight')
        upper |= report.get('experimental_height', {}).get('height_gap', 0) > 0
        minimum |= 'experimental_height' not in report
    require(upper and minimum, 'both original-height and taller-upper native gates must actually run')
    original_hash = digest(output / 'experiment.json')
    invoke('no-overwrite', [*command, '--output', output], False)
    require(digest(output / 'experiment.json') == original_hash, 'rejected rerun overwrote completed experiment')
    stopped = base / 'zero-search'
    invoke('unavailable', [*command, '--search-work', '0', '--meta-work', '0', '--output', stopped])
    unavailable = json.loads((stopped / 'experiment.json').read_text())
    require(unavailable['status'] == 'planning_unavailable' and unavailable['unavailable_groups'] == 1 and
            unavailable['runs'] == unavailable['verification'] == [], 'unproved original was timed or silently dropped')
    require(unavailable['groups'][0]['raw_status'] == 'original_minimum_unavailable', 'resource stop was relabelled')
    invalid = base / 'invalid-grant'
    invoke('invalid-grant', [*command, '--candidates', '33', '--output', invalid], False)
    require(not invalid.exists(), 'invalid candidate grant created an experiment')
    print('B04 planning driver PASS: real two-pass all-envelope/all-split preflight, frozen pooled calibration, TRAIN-only demand, provenance, no-overwrite and explicit unavailable controls; no held-out timing or B04 acceptance.')
    if temporary is not None:
        temporary.cleanup()


if __name__ == '__main__':
    try:
        main()
    except Exception as error:
        print(str(error), file=sys.stderr)
        raise SystemExit(1)
