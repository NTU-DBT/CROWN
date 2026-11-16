#!/usr/bin/env python3
"""Compile and run the optional planner from a moved public installation."""
from pathlib import Path
import argparse
import json
import shutil
import subprocess
import tempfile


def main():
    parser = argparse.ArgumentParser()
    for name in ('source', 'build', 'compiler', 'sanitize'):
        parser.add_argument(name)
    args = parser.parse_args()
    root, build = Path(args.source).resolve(), Path(args.build).resolve()
    def run(command):
        result = subprocess.run([str(x) for x in command], capture_output=True, text=True, timeout=240)
        if result.returncode:
            raise RuntimeError(f'{command}: {result.stderr[-2500:]} {result.stdout[-2500:]}')
        return result.stdout
    with tempfile.TemporaryDirectory(prefix='crown-installed-meta-') as directory:
        base = Path(directory)
        stage, prefix = base/'stage', base/'moved installation'
        run(['cmake', '--install', build, '--prefix', stage])
        stage.rename(prefix)
        if stage.exists() or list(prefix.rglob('*testing*.a')) or list(prefix.rglob('libcrown_reference.a')):
            raise RuntimeError('moved installation includes a source/test dependency')
        config, = prefix.rglob('CrownConfig.cmake')
        source, target = base/'consumer-source', base/'consumer-build'
        shutil.copytree(prefix/'share/crown/examples/meta-candidates', source)
        command = ['cmake', '-S', source, '-B', target, '-DCMAKE_BUILD_TYPE=Release',
                   '-DCMAKE_CXX_COMPILER='+args.compiler, '-DCrown_DIR='+str(config.parent),
                   '-DCMAKE_FIND_USE_PACKAGE_REGISTRY=OFF']
        if args.sanitize.upper() in ('ON', 'TRUE', '1', 'YES'):
            command += ['-DCMAKE_CXX_FLAGS=-fsanitize=address,undefined -fno-omit-frame-pointer']
        run(command)
        run(['cmake', '--build', target, '-j2'])
        unit, = json.loads((target/'compile_commands.json').read_text())
        if '-std=c++23' not in unit['command'] or any(str(path) in unit['command'] for path in (root/'include', root/'third_party', build)):
            raise RuntimeError('public consumer did not inherit isolated C++23 headers')
        report = json.loads(run([target/'crown_meta_candidate_example']))
        if not (report['ordinary_rooted_trees'] == 1 and report['ordinary_undirected_trees'] == 1
                and not report['all_ordinary_roots_materialized']
                and report['ordinary_family_exhausted'] and report['mapped_input_fibers_exhausted']
                and report['normalized_minimum_family_exhausted'] and not report['heuristic_used']
                and not report['global_cost_optimal']):
            raise RuntimeError('installed meta family status differs')
        candidate = report['candidate']
        if candidate['family'] != 'finite-proposals-v1' or candidate['checked_upper']['height'] != 1:
            raise RuntimeError('ordinary/native height was substituted for generalized height')
        # The emitter must also return failure when its buffered report is lost.
        with Path('/dev/full').open('wb') as sink:
            failed = subprocess.run([target/'crown_meta_candidate_example'], stdout=sink, stderr=subprocess.PIPE, timeout=180)
        if failed.returncode == 0:
            raise RuntimeError('installed example ignored report delivery failure')
        print('moved optional meta planner: isolated public consumer, generalized height1 and ENOSPC passed')
    return 0


if __name__ == '__main__':
    raise SystemExit(main())
