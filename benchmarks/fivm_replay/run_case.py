#!/usr/bin/env python3
"""Run ONE native F-IVM replay process for a CROWN paper query and record it.

  run_case.py --query Q --mode none|full --out DIR [--timeout S] [--work DIR]
              [--input PATH] [--oracle PATH|none]

Q is one of length3_filter, length3_project, length4_filter, length4_project,
star_cnt, TwoComb, dumbbell_full, dumbbell. The binary is WORK/bin/<q> (built
by build-queries.sh). The input defaults to the campaign input of the case
runtime-<Q>-full-reference_ordered_v1 in the v8 run manifest. The process runs
under /usr/bin/time in its own process group; it is killed (SIGKILL to the
group) after --timeout seconds. This script does not pin CPUs: the caller does.

Writes DIR/result.json (also printed on stdout), DIR/stdout, DIR/stderr and
DIR/time.txt. In mode full, every per-marker snapshot row count, the physical
input and relation update counts and final_rows == 0 are checked against the
CROWN oracle counts in oracle/<Q>.json ("validation"). Mode none checks the
input/update counts and final_rows only. F-IVM has no per-update delta output,
so "none" is the maintenance-only measurement used for delta cases.
"""
import argparse
import hashlib
import json
import os
import signal
import subprocess
import sys
import time
from pathlib import Path

HERE = Path(__file__).resolve().parent
ROOT = HERE.parents[1]
WORK = ROOT / 'build/experiments/fivm-crown'
MANIFEST = ROOT / 'build/experiments/paper-serial-comparison-20261116-v1/native-campaign-v8/run-manifest-v8.json'
QUERIES = {  # query -> binary name
    'length3_filter': 'length3_filter', 'length3_project': 'length3_project',
    'length4_filter': 'length4_filter', 'length4_project': 'length4_project',
    'star_cnt': 'star_cnt', 'TwoComb': 'twocomb', 'dumbbell_full': 'dumbbell_full', 'dumbbell': 'dumbbell',
}


def canonical(query):
    for name in QUERIES:
        if name.lower() == query.lower():
            return name
    raise SystemExit(f'unknown query {query!r}; choose from {", ".join(QUERIES)}')


def manifest_group(query):
    case = f'runtime-{query}-full-reference_ordered_v1'
    for group in json.loads(MANIFEST.read_text())['measurement_groups']:
        if group['case_id'] == case:
            return group
    raise SystemExit(f'{case} not in {MANIFEST}')


def sha256(path):
    digest = hashlib.sha256()
    with open(path, 'rb') as handle:
        for block in iter(lambda: handle.read(1 << 20), b''):
            digest.update(block)
    return digest.hexdigest()


def validate(report, oracle, mode):
    problems = []
    for key in ('physical_inputs', 'relation_updates', 'enumeration_markers'):
        if report.get(key) != oracle[key]:
            problems.append(f'{key}: fivm {report.get(key)} oracle {oracle[key]}')
    if report.get('final_rows') != 0:
        problems.append(f'final_rows {report.get("final_rows")} != 0')
    if mode == 'full':
        mine, theirs = report.get('snapshots', []), oracle['snapshots']
        if len(mine) != len(theirs):
            problems.append(f'{len(mine)} snapshots, oracle {len(theirs)}')
        for i, (a, b) in enumerate(zip(mine, theirs), 1):
            if a['sequence'] != b['sequence'] or a['rows'] != b['rows']:
                problems.append(f'marker {i}: fivm seq {a["sequence"]} rows {a["rows"]}, '
                                f'oracle seq {b["sequence"]} rows {b["rows"]}')
        if report.get('snapshot_rows') != oracle['snapshot_rows']:
            problems.append(f'snapshot_rows {report.get("snapshot_rows")} != {oracle["snapshot_rows"]}')
    return {'checked': True, 'kind': 'per-marker-counts' if mode == 'full' else 'update-counts-only',
            'oracle': oracle.get('source'), 'matched': not problems, 'problems': problems}


def main():
    parser = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    parser.add_argument('--query', required=True)
    parser.add_argument('--mode', required=True, choices=('none', 'full'))
    parser.add_argument('--out', type=Path, required=True)
    parser.add_argument('--timeout', type=float, default=7200)
    parser.add_argument('--work', type=Path, default=WORK)
    parser.add_argument('--input', type=Path)
    parser.add_argument('--oracle', default=None, help='oracle JSON (default oracle/<Q>.json); "none" disables')
    args = parser.parse_args()

    query = canonical(args.query)
    binary = (args.work / 'bin' / QUERIES[query]).resolve()
    if not binary.is_file():
        raise SystemExit(f'missing {binary}; run build-queries.sh first')
    source = args.input or Path(manifest_group(query)['input']['path'])
    out = args.out.resolve()
    out.mkdir(parents=True, exist_ok=True)
    command = ['/usr/bin/time', '-f', '%e %U %S %M', '-o', str(out / 'time.txt'),
               str(binary), str(source), args.mode]
    start = time.monotonic()
    with (out / 'stdout').open('w') as stdout, (out / 'stderr').open('w') as stderr:
        process = subprocess.Popen(command, stdout=stdout, stderr=stderr, start_new_session=True)
        try:
            status, timed_out = process.wait(timeout=args.timeout), False
        except subprocess.TimeoutExpired:
            os.killpg(process.pid, signal.SIGKILL)
            process.wait()
            status, timed_out = None, True
    elapsed = time.monotonic() - start

    result = {'query': query, 'mode': args.mode, 'plan': None, 'engine': 'fivm-native',
              'binary': str(binary), 'binary_sha256': sha256(binary), 'input': str(source),
              'command': command, 'exit_status': status, 'timed_out': timed_out,
              'wall_s': None, 'loop_s': None, 'output_s': None, 'user_s': None, 'sys_s': None,
              'maxrss_kib': None, 'python_wall_s': round(elapsed, 3)}
    try:
        wall, user, system, rss = (out / 'time.txt').read_text().split('\n')[-2].split()
        result.update(wall_s=float(wall), user_s=float(user), sys_s=float(system), maxrss_kib=int(rss))
    except (FileNotFoundError, IndexError, ValueError):
        pass
    report = None
    try:
        report = json.loads((out / 'stdout').read_text())
    except (ValueError, FileNotFoundError):
        pass
    if report:
        result.update(plan=report['plan'], loop_s=report['loop_wall_ns'] / 1e9, output_s=report['output_ns'] / 1e9)
        for key in ('physical_inputs', 'relation_updates', 'enumeration_markers', 'snapshot_rows',
                    'snapshots', 'final_rows'):
            result[key] = report.get(key)
    oracle_path = None if args.oracle == 'none' else Path(args.oracle or HERE / 'oracle' / f'{query}.json')
    if report and status == 0 and oracle_path and args.input is None:
        result['validation'] = validate(report, json.loads(oracle_path.read_text()), args.mode)
    else:
        result['validation'] = {'checked': False, 'matched': None,
                                'reason': 'no report' if not report or status != 0 else 'oracle disabled or custom input'}
    result['ok'] = status == 0 and not timed_out and result['validation'].get('matched') is not False
    (out / 'result.json').write_text(json.dumps(result, indent=2) + '\n')
    print(json.dumps(result), flush=True)
    return 0 if result['ok'] else 1


if __name__ == '__main__':
    sys.exit(main())
