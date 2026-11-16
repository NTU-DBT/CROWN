#!/usr/bin/env python3
"""Root-only C05 incremental leg; terminal execution is not independent acceptance."""
from pathlib import Path
import argparse, datetime, hashlib, json, os, re, signal, subprocess, time

ROOT = Path('/home/userroot/Codex/CROWN')
V = ROOT/'build/verification'
FREEZE = V/'selection-execution-freeze.json'

def need(value, message):
    if not value: raise RuntimeError(message)
def sha(path): return hashlib.sha256(Path(path).read_bytes()).hexdigest()
def relative(path): return str(Path(path).relative_to(ROOT))
def stop_group(child):
    try: os.killpg(child.pid,signal.SIGTERM)
    except ProcessLookupError: pass
    try: child.wait(timeout=3)
    except subprocess.TimeoutExpired: pass
    try: os.killpg(child.pid,signal.SIGKILL)
    except ProcessLookupError: pass
    return child.wait()
def interrupted(_signum,_frame): raise InterruptedError('driver received termination signal')
def scope(root, roots, extra):
    names = set(extra)
    for name in roots:
        names.update(p.relative_to(root).as_posix() for p in (root/name).rglob('*') if p.is_file()
                     and '__pycache__' not in p.parts and p.suffix not in {'.pyc','.pyo'})
    digest = hashlib.sha256()
    for name in sorted(names):
        digest.update(name.encode()); digest.update(b'\0'); digest.update((root/name).read_bytes()); digest.update(b'\0')
    return {'count':len(names),'sha256':digest.hexdigest()}
def inputs():
    roots = ['include','src','apps','tests','cmake']
    return {'native':scope(ROOT,roots,['CMakeLists.txt','CMakePresets.json']),
            'execution':scope(ROOT,roots+['schemas','tools','third_party'],['CMakeLists.txt','CMakePresets.json','dependencies.lock.json'])}
def guard(freeze, expected):
    need(sha(FREEZE) == expected, 'freeze FILE drift')
    need(freeze['root_execution_helpers'].get(str(Path(__file__).resolve())) == sha(__file__), 'unbound matrix driver')
    for name, digest in freeze['root_execution_helpers'].items(): need(sha(name) == digest, 'helper FILE drift: '+name)
    for name, digest in freeze['canonical_compiler_files'].items(): need(sha(name) == digest, 'compiler FILE drift: '+name)
    for cache in freeze['predecessor_toolchain_caches'].values():
        for name,digest in cache['compiler_files'].items():
            need(sha(name) == digest and freeze['canonical_compiler_files'].get(str(Path(name).resolve())) == digest,
                 'compiler alias drift: '+name)
    registry = freeze['immutable_preparation_registry']
    need(sha(ROOT/registry['path']) == registry['sha256'], 'immutable preparation registry drift')

def quiescence(freeze, digest):
    path = ROOT/freeze['sanitizer_schedule']['quiescence_receipt']
    need(digest and sha(path) == digest, 'missing or changed root quiescence receipt')
    record = json.loads(path.read_text())
    need(record.get('reviewer') == 'root' and record.get('decision') == freeze['sanitizer_schedule']['decision']
         and record.get('no_other_expensive_work') is True and record.get('freeze_sha256') == sha(FREEZE),
         'root quiescence decision does not bind this freeze')
    summaries = record['other_terminal_summaries']
    need(set(summaries) == set(freeze['sanitizer_schedule']['other_terminal_legs']), 'quiescence leg population differs')
    for label, pin in summaries.items():
        expected_path = 'build/verification/selection-'+label+'-summary.json'
        need(pin['path'] == expected_path and sha(ROOT/pin['path']) == pin['sha256'], 'terminal summary FILE drift')
        value = json.loads((ROOT/pin['path']).read_text())
        need(value.get('configuration') == label and value.get('terminal') is True
             and value.get('status') in {'passed','failed'} and type(value.get('exit_code')) is int
             and value.get('freeze_sha256') == record['freeze_sha256'], 'other leg is not terminal for this freeze')
    return {'path':relative(path),'sha256':digest,'other_terminal_summaries':summaries,
            'scope':'Root scheduling attestation; no operating-system process census is inferred.'}

def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('label', choices=['debug','release','sanitize','clang'])
    parser.add_argument('--freeze-sha256', required=True)
    parser.add_argument('--quiescence-sha256')
    args = parser.parse_args()
    signal.signal(signal.SIGTERM,interrupted)
    need(sha(FREEZE) == args.freeze_sha256, 'unexpected freeze FILE')
    freeze = json.loads(FREEZE.read_text()); guard(freeze,args.freeze_sha256)
    need(freeze['card'] == 'C05' and freeze['expected_ctest_count'] == 158, 'wrong execution scope')
    if args.label != 'sanitize': need(args.quiescence_sha256 is None, 'quiescence flag is sanitizer-only')
    quiet = quiescence(freeze,args.quiescence_sha256) if args.label == 'sanitize' else None
    if args.label == 'clang':
        commands = [('configure',['cmake','-S','.','-B','build/clang-debug']),
                    ('build',['cmake','--build','build/clang-debug','--parallel','2','--verbose']),
                    ('test',['ctest','--test-dir','build/clang-debug','--output-on-failure','--verbose'])]
    else:
        commands = [('configure',['cmake','--preset',args.label]),
                    ('build',['cmake','--build','--preset',args.label,'--parallel','2','--verbose']),
                    ('test',['ctest','--preset',args.label,'--output-on-failure','--verbose'])]
    summary_path = V/('selection-'+args.label+'-summary.json')
    output_path = V/('selection-'+args.label+'-ctest-output.log')
    paths = [summary_path,output_path]+[V/('selection-'+args.label+'-'+phase+'.log') for phase,_ in commands]
    need(all(not p.exists() for p in paths), 'preserve existing execution evidence')
    before = inputs(); need(before['native'] == freeze['native'] and before['execution'] == freeze['execution'], 'source drift before leg')
    record = {'configuration':args.label,'started_utc':datetime.datetime.now(datetime.timezone.utc).isoformat(),
              'freeze_sha256':args.freeze_sha256,'driver_sha256':sha(__file__),
              'fingerprint_before':before['native']['sha256'],'native_inputs_before':before['native'],
              'execution_inputs_before':before['execution'],'stages':[], 'quiescence':quiet,
              'compile_inventory_scope':'238 configured units; executed versus unchanged units require verbose-log/dependency/predecessor audit.',
              'expected_incremental_partition':freeze['incremental_partition_expectation'],
              'acceptance':'Independent matrix audit pending; this driver does not accept numeric or allocation differences.'}
    started_leg = time.monotonic(); status = 1
    try:
        for phase, command in commands:
            if quiet is not None: quiescence(freeze,args.quiescence_sha256)
            guard(freeze,args.freeze_sha256)
            path = V/('selection-'+args.label+'-'+phase+'.log')
            stage = {'phase':phase,'command':command,'log':relative(path),
                     'timeout_seconds':freeze['wrapper_timeout_seconds'][phase]}
            started = time.monotonic()
            try:
                with path.open('x') as log:
                    child = subprocess.Popen(command,cwd=ROOT,stdout=log,stderr=subprocess.STDOUT,start_new_session=True)
                    try: stage['exit_code'] = child.wait(timeout=stage['timeout_seconds'])
                    except (subprocess.TimeoutExpired,InterruptedError,KeyboardInterrupt) as error:
                        stage['child_exit_code_after_stop'] = stop_group(child)
                        stage['process_group_signalled_and_direct_child_reaped'] = True
                        stage['exit_code'] = 124 if isinstance(error,subprocess.TimeoutExpired) else 130
                        stage['error'] = str(error); stage['timed_out'] = isinstance(error,subprocess.TimeoutExpired)
            except OSError as error:
                stage['exit_code'] = 1; stage['error'] = repr(error)
            stage['seconds'] = round(time.monotonic()-started,3)
            if path.is_file(): stage['log_sha256'] = sha(path)
            record['stages'].append(stage)
            print(args.label,phase,'exit',stage['exit_code'],'elapsed',stage['seconds'],flush=True)
            if phase == 'test':
                build = ROOT/('build/clang-debug' if args.label == 'clang' else 'build/'+args.label)
                last = build/'Testing/Temporary/LastTest.log'
                if last.is_file():
                    with output_path.open('xb') as handle: handle.write(last.read_bytes())
                    record['ctest_output_log'] = relative(output_path); record['ctest_output_sha256'] = sha(output_path)
                output = path.read_text(errors='replace') if path.is_file() else ''
                counts = re.findall(r'(\d+)% tests passed, (\d+) tests failed out of (\d+)',output)
                durations = re.findall(r'Total Test time \(real\) =\s*([0-9.]+) sec',output)
                record['test_count'] = int(counts[-1][2]) if counts else None
                record['ctest_seconds'] = float(durations[-1]) if durations else None
                need(stage['exit_code'] == 0 and counts == [('100','0',str(freeze['expected_ctest_count']))]
                     and last.is_file(), 'CTest terminal population/result differs')
            if stage['exit_code'] != 0:
                status = stage['exit_code']; break
        else: status = 0
    except Exception as error:
        record['error'] = repr(error); status = 1
    try:
        after = inputs(); record['fingerprint_after'] = after['native']['sha256']
        record['native_inputs_after'] = after['native']; record['execution_inputs_after'] = after['execution']
        record['source_stable'] = before == after
        need(record['source_stable'], 'source changed during leg')
        guard(freeze,args.freeze_sha256)
        if quiet is not None: quiescence(freeze,args.quiescence_sha256)
        record['identity_guards_stable'] = True
    except Exception as error:
        record['final_guard_error'] = repr(error); record['identity_guards_stable'] = False; status = 1
    record.update({'exit_code':status,'status':'passed' if status == 0 else 'failed','terminal':True,
                   'completed_utc':datetime.datetime.now(datetime.timezone.utc).isoformat(),
                   'total_seconds':round(time.monotonic()-started_leg,3)})
    with summary_path.open('x') as handle: handle.write(json.dumps(record,indent=2)+'\n')
    print(json.dumps({'configuration':args.label,'status':record['status'],'summary':relative(summary_path)}),flush=True)
    return status

if __name__ == '__main__': raise SystemExit(main())
