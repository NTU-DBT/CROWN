#!/usr/bin/env python3
"""Qualify native/SQLite matched gates without requiring optional legacy SDKs."""
from copy import deepcopy
import hashlib
import json
import os
from pathlib import Path
import subprocess
import sys
import tempfile

sys.dont_write_bytecode = True
ROOT = Path(__file__).resolve().parents[2]
sys.path.insert(0,str(ROOT/'tools'))
from component_workloads import build_baseline_cohorts
from run_baseline_evaluation import legacy_actual
from run_measurements import require


def hashes(path):
    return {str(child.relative_to(path)):hashlib.sha256(child.read_bytes()).hexdigest() for child in path.rglob('*') if child.is_file()}


def main():
    require(len(sys.argv) in (6,7), 'usage: baseline_evaluation.py BUILD CROWN COLLECTOR SET AGGREGATE [NEW_ARTIFACT_DIRECTORY]')
    build,crown,collector,set_binary,aggregate_binary = [Path(value).resolve() for value in sys.argv[1:6]]
    temporary = None
    if len(sys.argv) == 7:
        directory = Path(sys.argv[6]).resolve(); directory.mkdir(parents=True,exist_ok=False)
    else:
        temporary = tempfile.TemporaryDirectory(prefix='crown-baseline-evaluation-'); directory = Path(temporary.name)
    manifest = build_baseline_cohorts((2,),1)
    manifest['arms'] = [arm for arm in manifest['arms'] if arm['adapter'] in ('set','aggregate','sqlite')]
    names = {arm['id'] for arm in manifest['arms']}
    manifest['comparisons'] = [item for item in manifest['comparisons'] if item['baseline'] in names and item['variant'] in names]
    path = directory/'cohorts.json'; path.write_text(json.dumps(manifest)+'\n')
    base = [sys.executable,str(ROOT/'tools/run_baseline_evaluation.py'),'--source',str(ROOT),'--build-dir',str(build),
            '--crown',str(crown),'--collector',str(collector),'--set-adapter',str(set_binary),'--aggregate-adapter',str(aggregate_binary),
            '--warmups','0','--repetitions','1','--cpu',str(min(os.sched_getaffinity(0))),'--command-timeout','180']
    commands = []
    def invoke(label,cohorts,output,success):
        arguments = [*base,'--cohorts',str(cohorts),'--output',str(output)]
        child = subprocess.run(arguments,capture_output=True,text=True,timeout=1200)
        (directory/(label+'.stdout')).write_text(child.stdout); (directory/(label+'.stderr')).write_text(child.stderr)
        commands.append({'label':label,'arguments':arguments,'exit_code':child.returncode})
        (directory/'commands.json').write_text(json.dumps(commands,indent=2)+'\n')
        require((child.returncode == 0) is success,label+': '+child.stderr[-2000:])
        return child
    output = directory/'accepted'
    invoke('actual-native-sqlite',path,output,True)
    packet = json.loads((output/'experiment.json').read_text()); raw = json.loads((output/'commands.json').read_text())
    count = len(manifest['arms'])
    require(packet['status'] == 'complete_conditional_matched' and packet['B04_accepted'] is False and
            packet['correctness_gate'] == 'all_preflights_pass', 'matched status overstates qualification')
    require(len(packet['verification']) == len(packet['runs']) == len(packet['summaries']) == count == 9, 'matched arm omitted')
    require(len(raw) == count*2 and all(item['label'].startswith('preflight:') for item in raw[:count]) and
            all(item['label'].startswith('measure:') for item in raw[count:]), 'measurement preceded complete correctness gate')
    require({item['axis'] for item in packet['comparisons']} == {'incremental_vs_recomputation'}, 'unavailable legacy claim entered self-contained test')
    # Validate published text decoders independently of native JSON paths.
    require(legacy_actual({'raw_output':'7.0000\n'},'l5_distinct_count') == 7, 'scalar decoder differs')
    require(legacy_actual({'raw_output':'(2,3) -> 4.0000\n'},'l5_group_count') == [{'key':[2,3],'values':[2,3,4]}], 'group decoder differs')
    require(legacy_actual({'rows':[[1,2,3,4]],'delta_text':'+ (D,4) , (B,2) , (A,1) , (C,3)\n'},'l3_full_rows') ==
            {'rows':[[1,2,3,4]],'delta':[{'operation':'+','values':[1,2,3,4]}]}, 'named signed decoder differs')
    for family,actual in [('l5_distinct_count',{'raw_output':'7.0001\n'}),
                          ('l5_group_count',{'raw_output':'(2,3) -> 4.0000\n(2,3) -> 5.0000\n'}),
                          ('l3_full_rows',{'rows':[],'delta_text':'+ (A,1),(B,2),(C,3),(C,4)\n'}),
                          ('l3_full_rows',{'rows':[],'delta_text':'+ INVALID((A,1),(B,2),(C,3),(D,4),(E,999))TRAILING\n'}),
                          ('l3_full_rows',{'rows':[],'delta_text':'+ (A,1),(B,2),(C,3),(D,4),(E,999)\n'})]:
        rejected = False
        try: legacy_actual(actual,family)
        except ValueError: rejected = True
        require(rejected,'corrupt legacy output accepted')
    # The direct SQLite adapter also rejects JSON booleans/floats as counters,
    # independently of the study runner's normalized integer pass settings.
    sqlite_request = next(arm['request'] for arm in manifest['arms'] if arm['adapter'] == 'sqlite')
    for label,invalid in [('boolean',True),('floating',1.0)]:
        request = deepcopy(sqlite_request); request['measured_passes'] = invalid
        invalid_path = directory/('sqlite-'+label+'.json'); invalid_path.write_text(json.dumps(request)+'\n')
        child = subprocess.run([sys.executable,str(ROOT/'tools/sqlite_component.py'),str(invalid_path)],capture_output=True,text=True,timeout=30)
        (directory/('sqlite-'+label+'.stderr')).write_text(child.stderr)
        require(child.returncode != 0 and not child.stdout,'noninteger SQLite counter accepted')
    # Original observers assign fields by physical position. Lock that mapping
    # even when a symmetric finite trace could conceal a swapped column order.
    swapped = deepcopy(manifest)
    for arm in swapped['arms']:
        if arm['request']['query_family'] == 'l3_full_rows':
            columns = arm['request']['program']['catalog']['catalog']['tables'][0]['columns']
            columns[0],columns[1] = columns[1],columns[0]
    swapped_path = directory/'swapped-catalog.json'; swapped_path.write_text(json.dumps(swapped)+'\n')
    invoke('reject-original-column-mapping',swapped_path,directory/'swapped-catalog',False)
    require(not (directory/'swapped-catalog').exists(), 'wrong fixed catalog launched native work')
    sparse = deepcopy(manifest)
    for arm in sparse['arms']:
        if arm['adapter'] == 'set' and arm['request']['query_family'] == 'l5_distinct_count':
            arm['request']['native']['observation_interval'] = 4
    sparse_path = directory/'sparse-observations.json'; sparse_path.write_text(json.dumps(sparse)+'\n')
    invoke('reject-sparse-observations',sparse_path,directory/'sparse-observations',False)
    require(not (directory/'sparse-observations').exists(), 'unmatched observation schedule launched native work')
    # A real native budget failure after successful prefixes must retain raw
    # evidence and prevent all timing; no mocked adapter success is accepted.
    failed = deepcopy(manifest); bad = deepcopy(next(arm for arm in failed['arms'] if arm['adapter'] == 'set'))
    bad['id'] = 'exhausted_native'; bad['request']['native']['memory_limit_bytes'] = 0
    failed['arms'].append(bad)
    failed_path = directory/'failed-cohorts.json'; failed_path.write_text(json.dumps(failed)+'\n')
    failed_output = directory/'failed'
    invoke('reject-real-native-budget',failed_path,failed_output,False)
    failure = json.loads((failed_output/'experiment.json').read_text()); records = json.loads((failed_output/'commands.json').read_text())
    require(failure['status'] == 'failed' and not failure['runs'] and failure['correctness_gate'] == 'pending' and
            records[-1]['exit_code'] != 0 and all(item['label'].startswith('preflight:') for item in records), 'failed preflight became timing authority')
    before = hashes(output)
    invoke('reject-existing-output',path,output,False)
    require(hashes(output) == before, 'completed matched evidence changed on rejected reuse')
    print('Matched runner: nine real native/SQLite arms, all gates before timing, published decoders, real budget rejection and exclusive output passed')
    if temporary: temporary.cleanup()


if __name__ == '__main__':
    main()
