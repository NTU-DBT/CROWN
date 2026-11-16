#!/usr/bin/env python3
"""Run parameterized B05 cases through B03's correctness-first native harness.

Each family/size has a separate child packet, bounding caller report retention.
Existing outputs are never removed. A failed child stops the batch nonzero.
Analyze raw packets separately; completing a run does not accept its trends.
"""
from __future__ import annotations

import argparse
import datetime
import hashlib
import json
import os
from pathlib import Path
import subprocess
import sys

sys.dont_write_bytecode = True
from generate_adversarial_workloads import FAMILIES, build

SUITES = {
    'scale_curves': ('volume_full', 'volume_projected', 'empty_intersection'),
    'fanout_skew_stress': ('fanout_full', 'fanout_projected', 'skew_hot', 'skew_balanced',
                         'arity_1', 'arity_8', 'arity_32', 'path_2', 'path_4', 'path_6'),
    'output_extremes': ('volume_projected', 'empty_intersection', 'fanout_full', 'fanout_projected'),
    'long_churn': ('churn_fresh', 'churn_reuse', 'churn_projected', 'churn_star', 'churn_path', 'churn_self_join'),
    'all': FAMILIES,
}


def digest(path):
    """Bind actual file bytes, without implying build lineage or semantics."""
    with path.open('rb') as stream:
        return hashlib.file_digest(stream, 'sha256').hexdigest()


def run(args):
    """Generate fresh inputs and retain sequential child receipts, including failure."""
    source = args.source.resolve()
    build_dir = args.build_dir.resolve()
    if source != Path(__file__).resolve().parents[1]:
        raise ValueError('invoke the B05 runner from the supplied source checkout')
    if not 1 <= args.repetitions <= 30 or not 0 <= args.warmups <= 5:
        raise ValueError('repetition/warmup outside the B03 grants')
    scales = args.scale or [1, 2, 4, 8]
    if len(scales) != len(set(scales)) or any(not 1 <= x <= 8 for x in scales):
        raise ValueError('scale selectors must be unique integers from 1 through 8')
    families = args.family or SUITES[args.suite]
    if len(set(families)) != len(families):
        raise ValueError('duplicate family selector')
    backends = args.backend or ['reference_ordered_v1', 'indexed_chained_v1']
    modes = args.mode or ['maintenance', 'snapshot', 'delta']
    if len(set(backends)) != len(backends) or len(set(modes)) != len(modes):
        raise ValueError('duplicate backend or output mode')
    for name in ('crown', 'crown_measure_workload', 'CMakeCache.txt'):
        if not (build_dir / name).is_file():
            raise ValueError('missing required explicit build input: ' + name)
    output = args.output.resolve()
    output.mkdir(parents=True, exist_ok=False)
    relevant = ['tools/run_adversarial_scalability.py', 'tools/generate_adversarial_workloads.py',
        'tools/generate_workloads.py', 'tools/run_measurements.py', 'tools/verify_workloads.py',
        'schemas/workload-manifest-v1.schema.json', 'schemas/workload-measurement-v2.schema.json']
    packet = {'schema_version': 1, 'kind': 'b05_parameterized_native_stress', 'status': 'running',
        'started_utc': datetime.datetime.now(datetime.timezone.utc).isoformat(),
        'source': str(source), 'build': str(build_dir),
        'source_sha256': {n: digest(source / n) for n in relevant},
        'configuration': {'families': list(families), 'scales': scales, 'backends': backends, 'modes': modes,
            'repetitions': args.repetitions, 'warmups': args.warmups, 'seed': args.seed,
            'observation': args.observe, 'cpu': args.cpu, 'codec': 'jsonl', 'sink': 'file'},
        'cases': [], 'limits': ['Finite synthetic set profile, not a complexity/speedup theorem.',
            'All loading is charged; encoding and file-sink work are separate measured phases.',
            'Per-epoch storage diagnostics are outside active event timings and inside loop wall.',
            'Requested query bytes, arena slots and process RSS have different scopes.',
            'No external-baseline, C03 forecast accuracy, release or universal memory-bound claim.']}

    def save():
        (output / 'experiment.json').write_text(json.dumps(packet, indent=2) + '\n')

    save()
    schedule = [(family, scale) for family in families for scale in scales]
    schedule.sort(key=lambda item: hashlib.sha256(f'{args.seed}:{item[0]}:{item[1]}'.encode()).digest())
    for index, (family, scale) in enumerate(schedule):
        directory = output / f'{family}-s{scale}'
        pack = directory / 'workload'
        pack.mkdir(parents=True)
        for name, content in build(args.seed, scale, [family]).items():
            path = pack / name
            path.parent.mkdir(parents=True, exist_ok=True)
            path.write_bytes(content)
        axes = json.loads((pack / 'axes.json').read_text())['cases'][0]
        command = [sys.executable, str(source / 'tools/run_measurements.py'), '--source', str(source),
            '--pack', str(pack), '--build-dir', str(build_dir), '--crown', str(build_dir / 'crown'),
            '--collector', str(build_dir / 'crown_measure_workload'), '--output', str(directory / 'native'),
            '--case', axes['case_id'], '--repetitions', str(args.repetitions), '--warmups', str(args.warmups),
            '--codec', 'jsonl', '--sink', 'file', '--observe', args.observe,
            '--schedule-seed', str(args.seed), '--command-timeout', '600', '--max-total-bytes', str(2 * 1024 ** 3)]
        for backend in backends:
            command += ['--backend', backend]
        for mode in modes:
            command += ['--mode', mode]
        if args.cpu is not None:
            command += ['--cpu', str(args.cpu)]
        print(f'[{index + 1}/{len(schedule)}] {family}, selector={scale}, {axes["axis"]}={axes["axis_value"]}', flush=True)
        log = directory / 'child.log'
        with log.open('x') as stream:
            child = subprocess.run(command, stdout=stream, stderr=subprocess.STDOUT,
                env=dict(os.environ, PYTHONDONTWRITEBYTECODE='1'), check=False)
        record = {'family': family, 'scale': scale, 'directory': str(directory.relative_to(output)),
            'pack_manifest_sha256': digest(pack / 'manifest.json'), 'axes_sha256': digest(pack / 'axes.json'),
            'command': command, 'exit_code': child.returncode, 'log_sha256': digest(log)}
        packet['cases'].append(record)
        if child.returncode:
            packet['status'] = 'failed'
            packet['completed_utc'] = datetime.datetime.now(datetime.timezone.utc).isoformat()
            save()
            return child.returncode
        native = directory / 'native/experiment.json'
        result = json.loads(native.read_text())
        if result['status'] != 'complete' or result['correctness_gate'] != 'passed_all_configurations_before_warmup_or_measurement':
            raise ValueError('child did not finish its correctness-first B03 packet')
        record['native_experiment_sha256'] = digest(native)
        save()
    if packet['source_sha256'] != {n: digest(source / n) for n in relevant}:
        raise ValueError('harness source changed during the experiment')
    packet['status'] = 'complete'
    packet['completed_utc'] = datetime.datetime.now(datetime.timezone.utc).isoformat()
    save()
    print(f'B05 complete: {len(schedule)} parameter points; raw B03 receipts under {output}')
    return 0


def main():
    """Parse explicit build/output choices; no default private build is reused."""
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--source', type=Path, default=Path(__file__).resolve().parents[1])
    parser.add_argument('--build-dir', type=Path, required=True)
    parser.add_argument('--output', type=Path, required=True)
    parser.add_argument('--suite', choices=SUITES, default='all')
    parser.add_argument('--family', action='append', choices=FAMILIES)
    parser.add_argument('--scale', type=int, action='append')
    parser.add_argument('--backend', action='append', choices=['reference_ordered_v1', 'indexed_chained_v1'])
    parser.add_argument('--mode', action='append', choices=['maintenance', 'snapshot', 'delta'])
    parser.add_argument('--repetitions', type=int, default=3)
    parser.add_argument('--warmups', type=int, default=1)
    parser.add_argument('--seed', type=int, default=20261114)
    parser.add_argument('--observe', choices=['counters', 'timed'], default='counters')
    parser.add_argument('--cpu', type=int)
    return run(parser.parse_args())


if __name__ == '__main__':
    raise SystemExit(main())
