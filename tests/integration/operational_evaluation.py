#!/usr/bin/env python3
"""Exercise the operational runner's actual native/oracle gate and retained scopes."""
import copy
import hashlib
import json
import os
from pathlib import Path
import subprocess
import sys
import tempfile

sys.dont_write_bytecode = True
ROOT = Path(__file__).resolve().parents[2]
sys.path.insert(0, str(ROOT/'tools'))
from component_workloads import build_operational_cohorts, evaluate_request
from run_measurements import require
from run_operational_evaluation import check_report


def hashes(directory):
    return {str(path.relative_to(directory)): hashlib.sha256(path.read_bytes()).hexdigest()
            for path in directory.rglob('*') if path.is_file()}


def main():
    require(len(sys.argv) in (8, 9), 'usage: operational_evaluation.py BUILD CROWN COLLECTOR SET ROWS SESSION AGGREGATE [NEW_ARTIFACT_DIRECTORY]')
    build, crown, collector, set_binary, rows_binary, session_binary, aggregate_binary = [Path(value).resolve() for value in sys.argv[1:8]]
    temporary = None
    if len(sys.argv) == 9:
        directory = Path(sys.argv[8]).resolve(); directory.mkdir(parents=True, exist_ok=False)
    else:
        temporary = tempfile.TemporaryDirectory(prefix='crown-operational-evaluation-'); directory = Path(temporary.name)
    manifest = build_operational_cohorts([2], 1)
    manifest_path = directory/'cohorts.json'; manifest_path.write_text(json.dumps(manifest, indent=2)+'\n')
    commands = []
    base = [sys.executable, str(ROOT/'tools/run_operational_evaluation.py'), '--source', str(ROOT), '--build-dir', str(build),
            '--crown', str(crown), '--collector', str(collector), '--set-adapter', str(set_binary), '--rows-adapter', str(rows_binary),
            '--session-adapter', str(session_binary), '--aggregate-adapter', str(aggregate_binary), '--cpu', str(min(os.sched_getaffinity(0))),
            '--warmups', '0', '--repetitions', '1', '--command-timeout', '180', '--max-total-bytes', str(256*1024**2)]

    def invoke(label, cohorts, output, success):
        arguments = [*base, '--cohorts', str(cohorts), '--output', str(output)]
        child = subprocess.run(arguments, text=True, capture_output=True, timeout=1200)
        (directory/(label+'.stdout')).write_text(child.stdout); (directory/(label+'.stderr')).write_text(child.stderr)
        commands.append({'label': label, 'arguments': arguments, 'exit_code': child.returncode})
        (directory/'commands.json').write_text(json.dumps(commands, indent=2)+'\n')
        require((child.returncode == 0) is success, label+': '+child.stderr[-3000:])
        if success:
            require(not child.stderr, label+': unexpected successful diagnostic')
        return child

    output = directory/'accepted'
    invoke('actual-native-cohorts', manifest_path, output, True)
    packet = json.loads((output/'experiment.json').read_text()); records = json.loads((output/'commands.json').read_text())
    require(packet['status'] == 'complete_conditional_operational' and packet['correctness_gate'] == 'all_preflights_pass' and
            packet['B04_accepted'] is False, 'runner overstated receiving status')
    arm_count = len(manifest['arms'])
    require(len(packet['verification']) == len(packet['runs']) == len(packet['summaries']) == arm_count, 'runner omitted an actual arm')
    gate_count = arm_count+len(packet['service_verification'])
    require(packet['service_verification'] and len(records) == gate_count+arm_count and
            all(row['label'].startswith('preflight:') for row in records[:gate_count]) and
            all(row['label'].startswith('measure:') for row in records[gate_count:]), 'timing began before every correctness gate')
    for service in packet['service_verification']:
        require(service['changed_paths'] == ['output'] and service['gate']['identity']['output'] == 'delta_and_snapshot',
                'supplemental signed delivery was omitted or entered measured none-output obligations')
    require({row['adapter'] for row in packet['summaries']} == {'set', 'rows', 'session', 'aggregate'}, 'missing a genuine runtime adapter')
    require({row['axis'] for row in packet['comparisons']} == {'output', 'updates', 'recovery', 'sql_semantics'}, 'missing an operational axis')
    for summary in packet['summaries']:
        require(summary['stage_latency_ns']['pass.loop_wall_ns']['samples'] == 1 and summary['process_maxrss_KiB']['samples'] == 1,
                'fresh invocation/account/process sample scopes collapsed')
        require(summary['native_memory_final_owner_before_teardown'], 'missing actual final-owner account')

    # Corrupt an actual native cardinality frame, retaining its real source and
    # controls. A native report flag or matching plan must not overrule SQLite.
    arm = next(row for row in packet['cohorts']['arms'] if row['adapter'] == 'set' and row['request']['output'] == 'cardinality')
    gate = next(row for row in packet['verification'] if row['arm'] == arm['id'])
    report = json.loads((output/gate['stdout']).read_text()); request = json.loads((output/gate['request']['request']).read_text())
    bad_report = copy.deepcopy(report)
    epoch = next(row for row in bad_report['passes'][0]['epochs'] if row['actual'] is not None); epoch['actual'] += 1
    rejected = False
    try:
        check_report(bad_report, arm, request, evaluate_request(request, arm['oracle']), True)
    except ValueError:
        rejected = True
    require(rejected, 'altered actual cardinality escaped the independent oracle')

    # Declare one factor but secretly alter a second native grant. Rejection
    # happens before build/native work and must not manufacture a new packet.
    bad = copy.deepcopy(manifest); variant = bad['comparisons'][0]['variant']
    changed = next(row for row in bad['arms'] if row['id'] == variant)
    changed['request']['native']['work_limit'] += 1
    bad_path = directory/'undeclared-factor.json'; bad_path.write_text(json.dumps(bad)+'\n')
    invoke('reject-undeclared-factor', bad_path, directory/'undeclared-factor', False)
    require(not (directory/'undeclared-factor').exists(), 'invalid factor changes started native packet work')

    # A final real native failure after earlier successful preflights still
    # prevents every timing invocation, and preserves its raw command records.
    comparison = manifest['comparisons'][0]
    keep = {comparison['baseline'], comparison['variant']}
    failing = {'schema_version': manifest['schema_version'], 'kind': manifest['kind'],
               'arms': [copy.deepcopy(row) for row in manifest['arms'] if row['id'] in keep], 'comparisons': [copy.deepcopy(comparison)]}
    rejected_arm = copy.deepcopy(arm); rejected_arm['id'] = 'deliberately_exhausted'; rejected_arm['request']['native']['memory_limit_bytes'] = 0
    failing['arms'].append(rejected_arm)
    failing_path = directory/'exhausted-native.json'; failing_path.write_text(json.dumps(failing)+'\n')
    failed_output = directory/'exhausted-native'
    invoke('reject-native-preflight', failing_path, failed_output, False)
    failed = json.loads((failed_output/'experiment.json').read_text()); failed_commands = json.loads((failed_output/'commands.json').read_text())
    require(failed['status'] == 'failed' and failed['correctness_gate'] == 'pending' and not failed['runs'], 'failed native preflight became timing authority')
    require(failed_commands and failed_commands[-1]['exit_code'] != 0 and all(row['label'].startswith('preflight:') for row in failed_commands),
            'native rejection did not retain its actual preflight command or launched timing')

    # Reusing a completed output directory must leave all committed state and
    # prior receiving bytes intact, including the experiment failure field.
    before = hashes(output)
    invoke('reject-existing-output', manifest_path, output, False)
    require(hashes(output) == before, 'rejected output-directory reuse mutated accepted evidence/state')
    print('Operational runner: '+str(arm_count)+' native arms, all-prefix gates before timing, actual-output corruption, factor rejection, native failure and exclusive output controls passed')
    if temporary:
        temporary.cleanup()


if __name__ == '__main__':
    main()
