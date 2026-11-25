#!/usr/bin/env python3
"""Comparison report for a campaign run by scheduler.py.

  report.py CAMPAIGN   writes CAMPAIGN/report.md and CAMPAIGN/report.csv

Per case: medians over completed runs of
  C++ CROWN  end-to-end process wall, peak RSS, CPU seconds (user+sys), cores,
             GC collections, for each pool/GC configuration
  Flink      internal timer (max AccumulateTime over workers), end-to-end wall
             (runner), peak RSS, cores = parallelism; p1 also from the earlier
             ten-run campaign
  F-IVM      process wall and peak RSS (full: snapshots; none: maintenance only)
Speedups are Flink (or F-IVM) time divided by C++ CROWN blocking-64M time.
"""
import csv, json, re, statistics, sys
from pathlib import Path

ROOT = Path('/home/userroot/Codex/CROWN')
sys.path.insert(0, str(ROOT / 'benchmarks/compare'))
import plan  # noqa: E402

CXX_CONFIGS = ['blocking-64M', 'blocking-256M', 'blocking-4G', 'blocking-unlimited', 'background-64M']


def load(path):
    try:
        return json.loads(path.read_text())
    except (FileNotFoundError, ValueError):
        return None


def median(values):
    values = [v for v in values if v is not None]
    return statistics.median(values) if values else None


def fmt(value, digits=2):
    if value is None:
        return ''
    if isinstance(value, float):
        return f'{value:.{digits}f}'
    return str(value)


def cxx_runs(campaign, case, config):
    runs = []
    for directory in sorted((campaign / 'runs/cxx' / case / config).glob('r*')):
        job = load(directory / 'job.json')
        if not job or job.get('status') != 'ok':
            continue
        report = load(directory / 'stdout') or {}
        runs.append({'wall': job.get('time_wall_s', job['wall_s']), 'rss_mib': job.get('maxrss_kib', 0) / 1024,
                     'cpu': (job.get('user_s') or 0) + (job.get('sys_s') or 0), 'cores': job['cores'],
                     'threads': report.get('threads'), 'collections': (report.get('gc') or {}).get('collections'),
                     'retired_mib': ((report.get('gc') or {}).get('retired_bytes') or 0) / 2**20,
                     'rows': (report.get('snapshot_rows'), report.get('delta_rows'))})
    return runs


def accumulate_s(stdout):
    try:
        values = [int(m) for m in re.findall(r'AccumulateTime (\d+)', stdout.read_text())]
    except FileNotFoundError:
        return None
    return max(values) / 1e9 if values else None


def flink_runs(campaign, case, p):
    runs = []
    for directory in sorted((campaign / 'runs/flink' / case / f'p{p}').glob('r*')):
        job = load(directory / 'job.json')
        receipt = load(directory / 'run/run-receipt.json')
        if not job or not receipt or receipt.get('status') != 'complete':
            continue
        runs.append({'timer': accumulate_s(directory / 'run/stdout'), 'wall': receipt['wall_ns'] / 1e9,
                     'rss_gib': (receipt.get('process_maxrss_KiB') or job.get('maxrss_kib', 0)) / 2**20,
                     'cpu': (job.get('user_s') or 0) + (job.get('sys_s') or 0), 'cores': p})
    return runs


def fivm_runs(campaign, case):
    runs = []
    for directory in sorted((campaign / 'runs/fivm' / case).glob('*/r*')):
        result = load(directory / 'out/result.json')
        job = load(directory / 'job.json')
        if not result or not job or job.get('status') != 'ok':
            continue
        runs.append({'mode': directory.parent.name, 'wall': result.get('wall_s'),
                     'rss_mib': (result.get('maxrss_kib') or 0) / 1024,
                     'cpu': (result.get('user_s') or 0) + (result.get('sys_s') or 0),
                     'valid': (result.get('validation') or {}).get('matched'), 'rows': result.get('snapshot_rows')})
    return runs


def main():
    campaign = Path(sys.argv[1]).resolve()
    medians = json.loads(plan.FLINK_MEDIANS.read_text())
    cases = sorted({p.name for p in (campaign / 'runs/cxx').glob('*')} |
                   {p.name for p in (campaign / 'runs/flink').glob('*')})
    rows, lines, notes = [], [], []
    lines.append('| case | C++ e2e s (1 core) | C++ RSS MiB | C++ CPU s | C++ 256M / 4G / no-GC / 2-thread s | '
                 'Flink p1 timer / e2e s (10-run, sequential) | Flink p1 timer / e2e s (this campaign) | '
                 'Flink p4 timer / e2e s | Flink p16 timer / e2e s | Flink RSS GiB p1/p4/p16 | '
                 'F-IVM s (mode), RSS MiB | speedup vs Flink e2e p1(10-run)/p4/p16 | rows |')
    lines.append('|' + '---|' * 13)
    for case in cases:
        cxx = {config: cxx_runs(campaign, case, config) for config in CXX_CONFIGS}
        base = cxx['blocking-64M']
        wall = median([r['wall'] for r in base])
        row = {'case': case, 'cxx_wall_s': wall, 'cxx_rss_mib': median([r['rss_mib'] for r in base]),
               'cxx_cpu_s': median([r['cpu'] for r in base]), 'cxx_runs': len(base)}
        for config in CXX_CONFIGS[1:]:
            row[f'{config}_wall_s'] = median([r['wall'] for r in cxx[config]])
            row[f'{config}_rss_mib'] = median([r['rss_mib'] for r in cxx[config]])
        row['collections_64M'] = median([r['collections'] for r in base])
        row['retired_mib'] = median([r['retired_mib'] for r in base])
        row['threads'] = sorted({r['threads'] for c in CXX_CONFIGS for r in cxx[c] if r['threads'] is not None})
        row_sets = {r['rows'] for c in CXX_CONFIGS for r in cxx[c]}
        previous = plan.previous(case)
        if previous:
            row_sets.add((previous.get('snapshot_rows'), previous.get('delta_rows')))
        row['rows_consistent'] = len(row_sets) <= 1
        if len(row_sets) > 1:
            notes.append(f'{case}: row counts differ across runs {sorted(row_sets, key=str)}')
        flink = {p: flink_runs(campaign, case, p) for p in (1, 4, 16)}
        key = plan.flink_key(case)
        for p in (1, 4, 16):
            row[f'flink_p{p}_timer_s'] = median([r['timer'] for r in flink[p]])
            row[f'flink_p{p}_wall_s'] = median([r['wall'] for r in flink[p]])
            row[f'flink_p{p}_rss_gib'] = median([r['rss_gib'] for r in flink[p]])
            row[f'flink_p{p}_cpu_s'] = median([r['cpu'] for r in flink[p]])
            row[f'flink_p{p}_runs'] = len(flink[p])
        if key:
            row['flink_p1_ten_run_timer_s'] = medians[key]['flink_accumulate_median_s']
            row['flink_p1_ten_run_wall_s'] = medians[key]['flink_wall_median_s']
        fivm = fivm_runs(campaign, case)
        row['fivm_mode'] = fivm[0]['mode'] if fivm else None
        row['fivm_wall_s'] = median([r['wall'] for r in fivm])
        row['fivm_rss_mib'] = median([r['rss_mib'] for r in fivm])
        row['fivm_valid'] = all(r['valid'] for r in fivm) if fivm and fivm[0]['mode'] == 'full' else None
        rows.append(row)

        def pair(p):
            timer, e2e = row[f'flink_p{p}_timer_s'], row[f'flink_p{p}_wall_s']
            return f'{fmt(timer, 1)} / {fmt(e2e, 1)}' if timer is not None else ''

        def speed(p):
            e2e = row.get('flink_p1_ten_run_wall_s') if p == 1 else row[f'flink_p{p}_wall_s']
            return f'{e2e / wall:.1f}x' if e2e and wall else '-'
        ten = (f"{fmt(row.get('flink_p1_ten_run_timer_s'), 1)} / {fmt(row.get('flink_p1_ten_run_wall_s'), 1)}"
               if row.get('flink_p1_ten_run_timer_s') is not None else '')
        others = ' / '.join(fmt(row[f'{c}_wall_s']) or '-' for c in CXX_CONFIGS[1:])
        rss = ' / '.join(fmt(row[f'flink_p{p}_rss_gib'], 1) or '-' for p in (1, 4, 16))
        fivm_text = (f"{fmt(row['fivm_wall_s'])} ({row['fivm_mode']}), {fmt(row['fivm_rss_mib'], 0)}"
                     if row['fivm_wall_s'] is not None else '')
        lines.append(f"| {case} | {fmt(wall)} | {fmt(row['cxx_rss_mib'], 0)} | {fmt(row['cxx_cpu_s'])} | {others} | "
                     f'{ten} | {pair(1)} | {pair(4)} | {pair(16)} | {rss} | {fivm_text} | '
                     f"{' / '.join(speed(p) for p in (1, 4, 16))} | {'OK' if row['rows_consistent'] else 'DIFF'} |")
    text = ['# C++ CROWN vs Flink vs F-IVM', '',
            'C++: median end-to-end process wall of the blocking (1-thread) build with the 64 MiB pool; '
            'Flink: internal timer (max AccumulateTime) / end-to-end wall; the earlier ten-run p1 '
            'medians (sequential, quiet host) are shown next to this campaign\'s run. Speedup = Flink e2e / C++ e2e '
            '(p1 uses the ten-run median).',
            'F-IVM: (full) visits and counts every result row without building tuples; (none) maintenance only, '
            'used for delta cases because F-IVM has no per-update delta output. C++ CROWN builds a tuple object per '
            'output row. Runs were concurrent on dedicated physical cores (Flink on socket 1, C++/F-IVM on socket 0).',
            ''] + lines
    # Efficiency: CPU seconds (user+sys) of the whole process tree.
    cpu = ['', '## CPU seconds (user+sys, whole process) and peak RSS', '',
           '| case | C++ 1 core: CPU s / RSS MiB | Flink p4: CPU s / RSS GiB | Flink p16: CPU s / RSS GiB | Flink p16 CPU / C++ CPU |',
           '|---|---|---|---|---|']
    for row in rows:
        if row['case'].endswith('-none') or row['cxx_cpu_s'] is None:
            continue
        c16 = row['flink_p16_cpu_s']
        cpu.append(f"| {row['case']} | {fmt(row['cxx_cpu_s'], 1)} / {fmt(row['cxx_rss_mib'], 0)} | "
                   f"{fmt(row['flink_p4_cpu_s'], 1)} / {fmt(row['flink_p4_rss_gib'], 1)} | {fmt(c16, 1)} / "
                   f"{fmt(row['flink_p16_rss_gib'], 1)} | {fmt(c16 / row['cxx_cpu_s'], 1) + 'x' if c16 else '-'} |")
    text += cpu
    ab = campaign / 'ab.md'
    if ab.exists():
        text += ['', '## Isolated A/B of C++ builds (one process at a time, one core)', '', ab.read_text().strip()]
    # Like-for-like with F-IVM: maintenance only (no output) on both sides.
    peer = ['', '## Maintenance only (no output): C++ CROWN `none` vs F-IVM `none`', '',
            '| query | C++ e2e s (1 core) | C++ RSS MiB | F-IVM e2e s (1 core) | F-IVM RSS MiB | F-IVM / C++ |',
            '|---|---|---|---|---|---|']
    for case in sorted(p.name for p in (campaign / 'runs/cxx').glob('runtime-*-none')):
        base = cxx_runs(campaign, case, 'blocking-64M')
        delta_case = case.replace('-none', '-delta')
        fivm = [r for r in fivm_runs(campaign, delta_case) if r['mode'] == 'none']
        wall, other = median([r['wall'] for r in base]), median([r['wall'] for r in fivm])
        peer.append(f"| {case[8:-5]} | {fmt(wall)} | {fmt(median([r['rss_mib'] for r in base]), 0)} | {fmt(other)} | "
                    f"{fmt(median([r['rss_mib'] for r in fivm]), 0)} | {fmt(other / wall) + 'x' if wall and other else '-'} |")
    text += peer
    verify = []
    for name in ('window', 'long'):
        out = campaign / f'runs/verify/{name}/stdout'
        if out.exists():
            tail = out.read_text().strip().splitlines()[-1:] or ['(empty)']
            verify.append(f'- verify {name}: {tail[0]}')
    text += ['', '## Checks'] + (verify or ['- verification pending']) + [f'- {n}' for n in notes]
    (campaign / 'report.md').write_text('\n'.join(text) + '\n')
    with (campaign / 'report.csv').open('w', newline='') as f:
        keys = sorted({k for r in rows for k in r})
        writer = csv.DictWriter(f, fieldnames=['case'] + [k for k in keys if k != 'case'])
        writer.writeheader()
        writer.writerows(rows)
    print('\n'.join(text))


if __name__ == '__main__':
    main()
