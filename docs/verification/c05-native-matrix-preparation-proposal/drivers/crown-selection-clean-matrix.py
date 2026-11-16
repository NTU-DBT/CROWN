#!/usr/bin/env python3
"""Root-only terminal summary for the C05 clean Release leg."""
from pathlib import Path
import argparse, datetime, hashlib, json, os, re, signal, subprocess, time

ROOT = Path('/home/userroot/Codex/CROWN')
V = ROOT/'build/verification'
FREEZE = V/'selection-execution-freeze.json'

def need(value, message):
    if not value: raise RuntimeError(message)
def sha(path): return hashlib.sha256(Path(path).read_bytes()).hexdigest()
def stop_group(child):
    try: os.killpg(child.pid,signal.SIGTERM)
    except ProcessLookupError: pass
    # Allow the adapter's own three-second child-group stop plus cleanup first.
    try: child.wait(timeout=30)
    except subprocess.TimeoutExpired: pass
    try: os.killpg(child.pid,signal.SIGKILL)
    except ProcessLookupError: pass
    return child.wait()
def interrupted(_signum,_frame): raise InterruptedError('outer clean driver received termination signal')
def inputs():
    def one(roots, extra):
        names = set(extra)
        for name in roots:
            names.update(p.relative_to(ROOT).as_posix() for p in (ROOT/name).rglob('*') if p.is_file()
                         and '__pycache__' not in p.parts and p.suffix not in {'.pyc','.pyo'})
        digest = hashlib.sha256()
        for name in sorted(names):
            digest.update(name.encode()); digest.update(b'\0'); digest.update((ROOT/name).read_bytes()); digest.update(b'\0')
        return {'count':len(names),'sha256':digest.hexdigest()}
    roots = ['include','src','apps','tests','cmake']
    return {'native':one(roots,['CMakeLists.txt','CMakePresets.json']),
            'execution':one(roots+['schemas','tools','third_party'],['CMakeLists.txt','CMakePresets.json','dependencies.lock.json'])}

def main():
    parser = argparse.ArgumentParser(description=__doc__); parser.add_argument('--freeze-sha256',required=True)
    args = parser.parse_args(); need(sha(FREEZE) == args.freeze_sha256, 'unexpected freeze FILE')
    signal.signal(signal.SIGTERM,interrupted)
    freeze = json.loads(FREEZE.read_text())
    def guard():
        need(sha(FREEZE) == args.freeze_sha256, 'freeze FILE drift')
        need(freeze['root_execution_helpers'].get(str(Path(__file__).resolve())) == sha(__file__), 'unbound outer clean driver')
        for name,digest in freeze['root_execution_helpers'].items(): need(sha(name) == digest, 'helper FILE drift: '+name)
        for name,digest in freeze['canonical_compiler_files'].items(): need(sha(name) == digest, 'compiler FILE drift: '+name)
        for cache in freeze['predecessor_toolchain_caches'].values():
            for name,digest in cache['compiler_files'].items():
                need(sha(name) == digest and freeze['canonical_compiler_files'].get(str(Path(name).resolve())) == digest,
                     'compiler alias drift: '+name)
    guard()
    log = V/'selection-clean-source.log'; summary = V/'selection-clean-source-summary.json'
    manifest = V/'selection-clean-artifacts-manifest.json'
    need(all(not p.exists() for p in [log,summary,manifest,V/'selection-clean-artifacts']), 'preserve existing clean evidence')
    before = inputs(); need(before['native'] == freeze['native'] and before['execution'] == freeze['execution'], 'source drift before clean leg')
    command = ['python3',str(Path(__file__).resolve().with_name('crown-selection-clean-evidence.py')),
               '--freeze-sha256',args.freeze_sha256,'--configuration','Release','--parallel','2','--log',str(log.relative_to(ROOT))]
    record = {'configuration':'clean-source','started_utc':datetime.datetime.now(datetime.timezone.utc).isoformat(),
              'freeze_sha256':args.freeze_sha256,'driver_sha256':sha(__file__),'command':command,
              'fingerprint_before':before['native']['sha256'],'native_inputs_before':before['native'],
              'execution_inputs_before':before['execution'],'log':str(log.relative_to(ROOT)),
              'wrapper_timeout_seconds':freeze['wrapper_timeout_seconds']['clean_total'],
              'expected_compile_partition':freeze['clean_partition_expectation'],
              'acceptance':'Independent matrix audit pending; configured entries are not treated as executed compiler commands.'}
    started = time.monotonic(); status = 1
    try:
        child = subprocess.Popen(command,cwd=ROOT,start_new_session=True)
        try: code = child.wait(timeout=record['wrapper_timeout_seconds'])
        except (subprocess.TimeoutExpired,InterruptedError,KeyboardInterrupt) as error:
            record['adapter_exit_code_after_stop'] = stop_group(child)
            record['process_group_signalled_and_direct_child_reaped'] = True
            raise RuntimeError('outer clean wrapper interrupted/timed out: '+str(error)) from error
        record['adapter_exit_code'] = code
        output = log.read_text(errors='replace'); record['log_sha256'] = sha(log)
        counts = re.findall(r'(\d+)% tests passed, (\d+) tests failed out of (\d+)',output)
        durations = re.findall(r'Total Test time \(real\) =\s*([0-9.]+) sec',output)
        temporary = re.search(r'temporary source: (.+)/source',output)
        record['test_count'] = int(counts[-1][2]) if counts else None
        record['ctest_seconds'] = float(durations[-1]) if durations else None
        record['stage_seconds'] = [float(value) for value in re.findall(r'command completed in ([0-9.]+)s',output)]
        record['temporary_path'] = temporary[1] if temporary else None
        record['temporary_removed'] = bool(temporary) and not Path(temporary[1]).exists()
        record['clean_artifacts_manifest'] = str(manifest.relative_to(ROOT)); record['clean_artifacts_manifest_sha256'] = sha(manifest)
        artifacts = json.loads(manifest.read_text())
        need(code == 0 and counts == [('100','0',str(freeze['expected_ctest_count']))]
             and record['temporary_removed'] and artifacts.get('terminal') is True and artifacts.get('status') == 'passed'
             and artifacts.get('freeze_sha256') == args.freeze_sha256 and artifacts.get('source_stable') is True
             and artifacts.get('identity_guards_stable') is True and artifacts.get('dependency_capture_complete') is True
             and artifacts.get('dependency_inputs_stable_before_cleanup') is True
             and len(artifacts['dependency_records']) == 238, 'clean terminal evidence incomplete or failed')
        record['dependency_count'] = len(artifacts['dependency_records']); status = 0
    except Exception as error:
        record['error'] = repr(error); status = 1
        if log.is_file(): record['log_sha256'] = sha(log)
        if manifest.is_file(): record['clean_artifacts_manifest_sha256'] = sha(manifest)
    try:
        after = inputs(); record['fingerprint_after'] = after['native']['sha256']; record['native_inputs_after'] = after['native']
        record['execution_inputs_after'] = after['execution']; record['source_stable'] = before == after
        need(record['source_stable'], 'source drift during clean leg'); guard(); record['identity_guards_stable'] = True
    except Exception as error:
        record['final_guard_error'] = repr(error); record['identity_guards_stable'] = False; status = 1
    record.update({'exit_code':status,'status':'passed' if status == 0 else 'failed','terminal':True,
                   'completed_utc':datetime.datetime.now(datetime.timezone.utc).isoformat(),
                   'total_seconds':round(time.monotonic()-started,3)})
    with summary.open('x') as handle: handle.write(json.dumps(record,indent=2)+'\n')
    print(json.dumps({'configuration':'clean-source','status':record['status'],'summary':str(summary.relative_to(ROOT))}),flush=True)
    return status

if __name__ == '__main__': raise SystemExit(main())
