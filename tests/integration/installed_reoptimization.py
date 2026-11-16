#!/usr/bin/env python3
"""Move the installed SDK and switch/recover real plans in external processes."""
import argparse
import json
from pathlib import Path
import shutil
import subprocess
import tempfile


def require(value, message):
    if not value:
        raise RuntimeError(message)


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('source')
    parser.add_argument('build')
    parser.add_argument('compiler')
    parser.add_argument('sanitize')
    args = parser.parse_args()
    root, build = Path(args.source).resolve(), Path(args.build).resolve()
    records = []

    def run(command):
        command = [str(value) for value in command]
        result = subprocess.run(command, text=True, capture_output=True, timeout=240)
        records.append({'command': command, 'exit_code': result.returncode})
        require(result.returncode == 0, f'{command}: {result.stderr[-2500:]} {result.stdout[-2500:]}')
        return result.stdout

    with tempfile.TemporaryDirectory(prefix='crown-installed-reoptimization-') as temporary:
        base = Path(temporary)
        stage, prefix = base/'stage', base/'relocated prefix'
        run(['cmake', '--install', build, '--prefix', stage])
        stage.rename(prefix)
        require(not stage.exists(), 'original SDK prefix remains')
        source = base/'outside-source'
        shutil.copytree(prefix/'share/crown/examples/reoptimization', source)
        consumer = base/'outside-build'
        configs = list(prefix.rglob('CrownConfig.cmake'))
        require(len(configs) == 1, 'installed SDK config is ambiguous')
        command = ['cmake', '-S', source, '-B', consumer, '-DCMAKE_BUILD_TYPE=Release',
                   '-DCMAKE_CXX_COMPILER='+args.compiler, '-DCrown_DIR='+str(configs[0].parent),
                   '-DCMAKE_FIND_USE_PACKAGE_REGISTRY=OFF']
        if args.sanitize.upper() in ('ON', 'TRUE', '1', 'YES'):
            command += ['-DCMAKE_CXX_FLAGS=-fsanitize=address,undefined -fno-omit-frame-pointer']
        run(command)
        run(['cmake', '--build', consumer, '--parallel', '2'])
        entries = json.loads((consumer/'compile_commands.json').read_text())
        require(len(entries) == 1 and '-std=c++23' in entries[0]['command'], 'external consumer lost C++23')
        for forbidden in (str(root/'include'), str(root/'third_party'), str(build), str(stage)):
            require(forbidden not in entries[0]['command'], 'external consumer used source/build/old-prefix headers')
        link = (consumer/'CMakeFiles/crown_reoptimization.dir/link.txt').read_text()
        require('testing' not in link and 'libcrown_reference' not in link, 'external consumer linked test ABI')
        for backend in ('reference', 'indexed'):
            directory = base/backend
            first = json.loads(run([consumer/'crown_reoptimization', 'run', directory, backend]))
            require(first['switched'] and first['selection_ns'] > 0 and first['compiler_ns'] > 0,
                    'external C05/native switch hid its selection/compiler cost')
            require(first['sequence'] == first['sink_sequence'] == 9 and first['exists'] is False and
                    first['generation'] == first['first_generation'] == 3 and first['source_offset'] == 90,
                    'external switch/rotation/retirement boundary differs')
            resumed = json.loads(run([consumer/'crown_reoptimization', 'resume', directory, backend]))
            require(resumed['sequence'] == resumed['sink_sequence'] == 10 and resumed['exists'] is True and
                    resumed['generation'] == resumed['first_generation'] == 3 and resumed['source_offset'] == 100,
                    'external selected-plan recovery/next update differs')
            require(first['origin_generation'] == resumed['origin_generation'] == 1,
                    'external switch/recovery rewrote immutable sink identity')
            print('installed reoptimization', backend, 'C05/SQL switch, retirement, fresh-process recovery and exact next output PASS')
    print('C06 moved SDK/public consumer PASS;', len(records), 'commands; no source/test/reference dependency')


if __name__ == '__main__':
    main()
