from pathlib import Path
import hashlib
import json
import re
import subprocess
import sys
import time

label = sys.argv[1]
folder = Path('build/verification')
folder.mkdir(parents=True, exist_ok=True)
if label == 'clang':
    commands = [
        ('configure', ['cmake', '-S', '.', '-B', 'build/clang-debug']),
        ('build', ['cmake', '--build', 'build/clang-debug', '--parallel', '2', '--verbose']),
        ('test', ['ctest', '--test-dir', 'build/clang-debug', '--output-on-failure', '--verbose']),
    ]
else:
    commands = [
        ('configure', ['cmake', '--preset', label]),
        ('build', ['cmake', '--build', '--preset', label, '--parallel', '2', '--verbose']),
        ('test', ['ctest', '--preset', label, '--output-on-failure', '--verbose']),
    ]

def fingerprint():
    files = [Path('CMakeLists.txt'), Path('CMakePresets.json')]
    for directory in ['include', 'src', 'apps', 'tests', 'cmake']:
        files.extend(path for path in Path(directory).rglob('*') if path.is_file() and '__pycache__' not in path.parts and path.suffix != '.pyc')
    digest = hashlib.sha256()
    for path in sorted(files):
        digest.update(path.as_posix().encode())
        digest.update(b'\0')
        digest.update(path.read_bytes())
        digest.update(b'\0')
    return digest.hexdigest()


def execution_fingerprint():
    paths={Path('CMakeLists.txt'),Path('CMakePresets.json'),Path('dependencies.lock.json')}
    for directory in ['include','src','apps','tests','cmake','schemas','tools','third_party']:
        paths.update(p for p in Path(directory).rglob('*') if p.is_file() and '__pycache__' not in p.parts and p.suffix!='.pyc')
    digest=hashlib.sha256()
    for p in sorted(paths):
        digest.update(p.as_posix().encode());digest.update(b'\0');digest.update(p.read_bytes());digest.update(b'\0')
    return {'count':len(paths),'sha256':digest.hexdigest()}

summary = {'configuration': label, 'fingerprint_before': fingerprint(), 'stages': []}
summary['execution_inputs_before'] = execution_fingerprint()
freeze=json.loads((folder/'ranking-execution-freeze.json').read_text())
assert summary['fingerprint_before']==freeze['native']['sha256']
assert summary['execution_inputs_before']==freeze['execution']
assert not (folder/f'ranking-{label}-summary.json').exists()

status = 0
for phase, command in commands:
    started = time.monotonic()
    path = folder / f'ranking-{label}-{phase}.log'
    with path.open('x') as log:
        result = subprocess.run(command, stdout=log, stderr=subprocess.STDOUT)
    elapsed = time.monotonic() - started
    summary['stages'].append({'phase': phase, 'command': command, 'exit_code': result.returncode, 'seconds': round(elapsed, 2), 'log': str(path)})
    print(label, phase, 'exit', result.returncode, 'elapsed', round(elapsed, 2), flush=True)
    output = path.read_text()
    if result.returncode:
        print(output[-6500:], flush=True)
        status = result.returncode
        break
    if phase == 'test':
        build_folder = Path('build/clang-debug' if label == 'clang' else f'build/{label}')
        last_output = build_folder / 'Testing/Temporary/LastTest.log'
        if last_output.is_file():
            retained_output = folder / f'ranking-{label}-ctest-output.log'
            retained_output.write_bytes(last_output.read_bytes())
            summary['ctest_output_log'] = str(retained_output)
        count = re.search(r'(\d+)% tests passed, (\d+) tests failed out of (\d+)', output)
        duration = re.search(r'Total Test time \(real\) =\s*([0-9.]+) sec', output)
        summary['test_count'] = int(count.group(3)) if count else None
        summary['ctest_seconds'] = float(duration.group(1)) if duration else None
        if not count or count.groups() != ('100', '0', str(freeze['expected_ctest_count'])):
            print('Unexpected final test count', count.groups() if count else None, flush=True)
            status = 1
        print(output[-1200:], flush=True)

summary['execution_inputs_after'] = execution_fingerprint()
summary['fingerprint_after'] = fingerprint()
summary['source_stable'] = summary['fingerprint_before'] == summary['fingerprint_after'] and summary['execution_inputs_before'] == summary['execution_inputs_after']
if not summary['source_stable']:
    print('Source changed during the matrix job', flush=True)
    status = 1
summary['exit_code'] = status
(folder / f'ranking-{label}-summary.json').write_text(json.dumps(summary, indent=2) + '\n')
sys.exit(status)
