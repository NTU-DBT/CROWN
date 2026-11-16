from pathlib import Path
import hashlib,json,re,subprocess,time,sys

def fingerprint():
    paths=[Path('CMakeLists.txt'),Path('CMakePresets.json')]
    for directory in ['include','src','apps','tests','cmake']:
        paths.extend(p for p in Path(directory).rglob('*') if p.is_file() and '__pycache__' not in p.parts and p.suffix!='.pyc')
    digest=hashlib.sha256()
    for p in sorted(paths):
        digest.update(p.as_posix().encode());digest.update(b'\0');digest.update(p.read_bytes());digest.update(b'\0')
    return digest.hexdigest()


def execution_fingerprint():
    paths={Path('CMakeLists.txt'),Path('CMakePresets.json'),Path('dependencies.lock.json')}
    for directory in ['include','src','apps','tests','cmake','schemas','tools','third_party']:
        paths.update(p for p in Path(directory).rglob('*') if p.is_file() and '__pycache__' not in p.parts and p.suffix!='.pyc')
    digest=hashlib.sha256()
    for p in sorted(paths):
        digest.update(p.as_posix().encode());digest.update(b'\0');digest.update(p.read_bytes());digest.update(b'\0')
    return {'count':len(paths),'sha256':digest.hexdigest()}

path=Path('build/verification/ranking-clean-source.log')
command=['python3','/tmp/crown-ranking-clean-evidence.py','--configuration','Release','--parallel','2','--log',str(path)]
before=fingerprint()
execution_before=execution_fingerprint()
freeze=json.loads(Path('build/verification/ranking-execution-freeze.json').read_text())
assert before==freeze['native']['sha256'] and execution_before==freeze['execution']
assert not Path('build/verification/ranking-clean-source-summary.json').exists()

started=time.monotonic()
result=subprocess.run(command)
output=path.read_text()
count=re.search(r'100% tests passed, 0 tests failed out of (\d+)',output)
duration=re.search(r'Total Test time \(real\) =\s*([0-9.]+) sec',output)
temporary=re.search(r'temporary source: (.+)/source',output)
stages=[float(v) for v in re.findall(r'command completed in ([0-9.]+)s',output)]
after=fingerprint()
execution_after=execution_fingerprint()
removed=bool(temporary) and not Path(temporary.group(1)).exists()
summary={'configuration':'clean-source','command':command,'exit_code':result.returncode,'fingerprint_before':before,'fingerprint_after':after,'source_stable':before==after and execution_before==execution_after,'execution_inputs_before':execution_before,'execution_inputs_after':execution_after,'test_count':int(count.group(1)) if count else None,'ctest_seconds':float(duration.group(1)) if duration else None,'total_seconds':round(time.monotonic()-started,2),'stage_seconds':stages,'temporary_path':temporary.group(1) if temporary else None,'temporary_removed':removed,'log':str(path),'attempt':1}
status=result.returncode
if not count or int(count.group(1))!=freeze['expected_ctest_count'] or before!=after or execution_before!=execution_after or not removed:
    status=1
summary['exit_code']=status
Path('build/verification/ranking-clean-source-summary.json').write_text(json.dumps(summary,indent=2)+'\n')
print(json.dumps(summary,indent=2),flush=True)
sys.exit(status)
