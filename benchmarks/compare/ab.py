#!/usr/bin/env python3
"""Isolated A/B timing of C++ CROWN builds: one process at a time on one core.

  ab.py OUT --bin NAME=DIR [--bin NAME=DIR ...] [--case CASE ...] [--reps 2] [--cpu 10]

Runs every (rep, case, build) in an interleaved order, so drift affects every
build alike, with CROWN_GC=blocking and the 64M pool. Prints a table of median
end-to-end wall (GNU time), apply and output seconds per case and build.
"""
import argparse, json, os, statistics, subprocess, sys
from pathlib import Path

ROOT = Path('/home/userroot/Codex/CROWN')
sys.path.insert(0, str(ROOT / 'benchmarks/paper_replay'))
import run as paper  # noqa: E402


def main():
    parser = argparse.ArgumentParser()
    parser.add_argument('out', type=Path)
    parser.add_argument('--bin', action='append', required=True)
    parser.add_argument('--case', action='append', required=True)
    parser.add_argument('--reps', type=int, default=2)
    parser.add_argument('--cpu', default='10')
    args = parser.parse_args()
    builds = dict(item.split('=', 1) for item in args.bin)
    groups = {g['case_id'].replace('-reference_ordered_v1', ''): g for g in paper.cases()}
    env = {k: v for k, v in os.environ.items() if not k.startswith('CROWN_')}
    env.update(CROWN_GC='blocking', CROWN_GC_POOL='64M')
    results = {}
    for rep in range(1, args.reps + 1):
        for case in args.case:
            kind, request = paper.request_for(groups[case])
            for name, bindir in builds.items():
                directory = args.out / name / case / f'r{rep}'
                directory.mkdir(parents=True, exist_ok=True)
                (directory / 'request.json').write_text(json.dumps(request))
                command = ['/usr/bin/time', '-f', '%e %M', '-o', str(directory / 'time.txt'), 'taskset', '-c', args.cpu,
                           str(Path(bindir) / paper.BINARIES[kind]), str(directory / 'request.json'),
                           groups[case]['input']['path']]
                with (directory / 'stdout').open('w') as out, (directory / 'stderr').open('w') as err:
                    status = subprocess.run(command, stdout=out, stderr=err, env=env).returncode
                report = json.loads((directory / 'stdout').read_text()) if status == 0 else {}
                wall, rss = (directory / 'time.txt').read_text().split()[-2:]
                row = {'wall': float(wall), 'rss_mib': int(rss) // 1024, 'apply': report.get('apply_ns', 0) / 1e9,
                       'output': report.get('output_ns', 0) / 1e9,
                       'rows': (report.get('snapshot_rows'), report.get('delta_rows')), 'status': status}
                results.setdefault((case, name), []).append(row)
                print(json.dumps({'case': case, 'build': name, 'rep': rep, **row}), flush=True)
    print()
    print('| case | ' + ' | '.join(f'{n} e2e s (apply / output)' for n in builds) + ' | rows equal |')
    print('|---|' + '---|' * (len(builds) + 1))
    for case in args.case:
        cells, rows = [], set()
        for name in builds:
            runs = results[(case, name)]
            rows.update(r['rows'] for r in runs)
            med = lambda key: statistics.median(r[key] for r in runs)
            cells.append(f"{med('wall'):.2f} ({med('apply'):.2f} / {med('output'):.2f})")
        print(f"| {case} | {' | '.join(cells)} | {'yes' if len(rows) == 1 else 'NO'} |")


if __name__ == '__main__':
    main()
