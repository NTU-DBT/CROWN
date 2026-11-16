#!/usr/bin/env python3
"""Root-only compilation and execution of excluded C01 policy consumers."""
import hashlib
import json
import os
from pathlib import Path
import shlex
import subprocess
import sys
import time

ROOT = Path(__file__).resolve().parents[3]
PACKAGE = Path(__file__).resolve().parent
ATTEMPT = ROOT / 'build/verification/c01-statistics-policy-root-attempt-2'
SUMMARY = ATTEMPT.with_suffix('.json')
FIXTURES = ['delta_runtime_test', 'delta_replay_test', 'window_test']
RUNTIME_BUILDS = {
    'strict': Path('/tmp/crown-c01-combined-production'),
    'sanitize': Path('/tmp/crown-c01-combined-root-production-sanitized-attempt-1'),
}

def digest(path):
    return hashlib.sha256(path.read_bytes()).hexdigest()

def label(path):
    return path.relative_to(ROOT).as_posix() if path.is_relative_to(ROOT) else str(path)

def manifest(path):
    result = {label(path): digest(path)}
    for line in path.read_text().splitlines():
        expected, rel = line.split('  ', 1)
        target = Path(rel) if rel.startswith('/') else ROOT / rel
        if digest(target) != expected:
            raise RuntimeError('changed manifest input: ' + rel)
        result[label(target)] = expected
    return result

def accepted_pins():
    evidence = ROOT / 'build/verification/c01-statistics-combined-root-attempt-1.json'
    result = {label(evidence): digest(evidence)}
    value = json.loads(evidence.read_text())
    if not value['passed'] or not value['pins_before_after_match']:
        raise RuntimeError('combined predecessor not accepted')
    for rel, expected in value['pins_after'].items():
        path = Path(rel) if rel.startswith('/') else ROOT / rel
        if digest(path) != expected:
            raise RuntimeError('accepted predecessor input changed: ' + rel)
        result[label(path)] = expected
    result.update(manifest(PACKAGE / 'PACKAGE_SHA256SUMS'))
    result.update(manifest(PACKAGE / 'INPUT_SHA256SUMS'))
    return result

def run(command, name, env=None):
    log = Path(str(ATTEMPT) + '-' + name + '.log')
    start = time.monotonic()
    with log.open('wb') as output:
        completed = subprocess.run(command, cwd=ROOT, env=env, stdout=output,
                                   stderr=subprocess.STDOUT, check=False)
    value = {'name': name, 'command': command, 'exit_code': completed.returncode,
             'elapsed_seconds': time.monotonic() - start,
             'log': label(log), 'log_sha256': digest(log)}
    print(name + ' exit=' + str(completed.returncode), flush=True)
    if completed.returncode:
        print(log.read_text(errors='replace')[-10000:], flush=True)
    return value

def main():
    if SUMMARY.exists():
        raise RuntimeError('attempt already exists')
    pins = accepted_pins()
    record = {'card': 'C01', 'scope': 'excluded enabled independent policy/window fixtures',
              'runtime_policy': 'reuse the accepted production strict/full sanitizer closures; compile new consumers only',
              'pins_before': pins, 'stages': [], 'passed': False}
    try:
        for mode, inherited in RUNTIME_BUILDS.items():
            out = Path('/tmp/crown-c01-policy-root-' + mode + '-attempt-2')
            out.mkdir(exist_ok=False)
            commands = [shlex.split(line) for line in (inherited / 'commands.sh').read_text().splitlines()
                        if line.startswith('c++ ') and '-c' not in shlex.split(line)]
            link = next(c for c in commands if str(inherited / 'owner_statistics_test.o') in c)
            first_object = next(i for i, arg in enumerate(link) if arg.endswith('.o'))
            flags = link[:first_object] + ['-I', str(PACKAGE / 'overlay/tests/support'), '-DCROWN_STATISTICS_ACCEPTANCE']
            objects = [arg for arg in link[first_object:] if arg.endswith('.o') and arg != str(inherited / 'owner_statistics_test.o')]
            if len(objects) != 15 or any('testing' in item for item in objects):
                raise RuntimeError('unexpected inherited production closure')
            archives = [arg for arg in link if arg.endswith('.a')]
            for path in [inherited / 'commands.sh'] + [ROOT / item if not item.startswith('/') else Path(item) for item in objects + archives]:
                pins[label(path)] = digest(path)
            env = os.environ.copy()
            if mode == 'sanitize':
                env['ASAN_OPTIONS'] = 'detect_leaks=1:halt_on_error=1'
                env['UBSAN_OPTIONS'] = 'halt_on_error=1:print_stacktrace=1'
            for fixture in FIXTURES:
                source = PACKAGE / 'overlay/tests/unit' / (fixture + '.cpp')
                obj, binary = out / (fixture + '.o'), out / fixture
                command = flags + ['-MMD', '-MF', str(out / (fixture + '.d')), '-c', str(source), '-o', str(obj)]
                stage = run(command, mode + '-' + fixture + '-compile')
                record['stages'].append(stage)
                if stage['exit_code']:
                    raise RuntimeError('consumer compilation failed')
                command = flags + objects + [str(obj), '-Wl,--start-group'] + archives + ['-Wl,--end-group', '-o', str(binary)]
                stage = run(command, mode + '-' + fixture + '-link')
                record['stages'].append(stage)
                if stage['exit_code']:
                    raise RuntimeError('consumer linking failed')
                for path in [obj, binary, out / (fixture + '.d')]:
                    record.setdefault('outputs', {})[label(path)] = digest(path)
                choices = ['', 'eager', 'incremental', 'anchored', 'root_first'] if fixture == 'delta_runtime_test' else ['']
                for choice in choices:
                    stage = run([str(binary)] + ([choice] if choice else []), mode + '-' + fixture + '-' + (choice or 'default'), env)
                    record['stages'].append(stage)
                    if stage['exit_code']:
                        raise RuntimeError('enabled oracle fixture failed')
        record['passed'] = True
    except Exception as failure:
        record['error'] = str(failure)
    finally:
        record['pins_before'] = pins
        try:
            after = {rel: digest(Path(rel) if rel.startswith('/') else ROOT / rel) for rel in pins}
            record['pins_after'] = after
            record['pins_before_after_match'] = pins == after
            if pins != after:
                record['passed'] = False
        except Exception as failure:
            record['passed'] = False
            record['pin_error'] = str(failure)
        SUMMARY.write_text(json.dumps(record, indent=2) + '\n')
    print('passed=' + str(record['passed']) + ' summary=' + str(SUMMARY), flush=True)
    return 0 if record['passed'] else 1

if __name__ == '__main__':
    sys.exit(main())
