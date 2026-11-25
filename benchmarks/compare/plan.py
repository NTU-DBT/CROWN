#!/usr/bin/env python3
"""Job plans for the C++ CROWN / Flink / F-IVM comparison (see scheduler.py).

  plan.py init CAMPAIGN --bin DIR     C++ CROWN, Flink p1/p4/p16 and verification jobs
  plan.py fivm CAMPAIGN --queries Q,Q [--reps N]   F-IVM jobs for those queries
  plan.py none CAMPAIGN --bin DIR --queries Q,Q     C++ maintenance-only runs (output mode
                                                    none), the like-for-like F-IVM `none` peer

C++ CROWN (one process per run; 1 thread blocking GC, 2 threads background):
  blocking-64M       every case, 3 runs (the default retired-memory pool)
  blocking-256M      3 runs if a 64M run's peak RSS exceeded 256 MiB
  blocking-4G        3 runs if a 64M run's peak RSS exceeded 4 GiB
  blocking-unlimited every case, 3 runs (no collection unless the budget is hit)
  background-64M     every case, 3 runs (one collector thread)
Flink (the original CROWN jobs, unchanged runner and jar): parallelism 1 (one
run; ten-run medians from the earlier campaign also exist), 4 and 16 (three
runs each), on p dedicated cores.
"""
import argparse, json, math, re, sys
from pathlib import Path

ROOT = Path('/home/userroot/Codex/CROWN')
sys.path.insert(0, str(ROOT / 'benchmarks/paper_replay'))
import run as paper  # noqa: E402  (cases(), request_for(), BINARIES)

ORIGINAL = ROOT / 'build/experiments/paper-serial-comparison-20261116-v1'
MANIFEST = ORIGINAL / 'original-campaign-v8/run-manifest-v8.json'
FLINK_MEDIANS = ROOT / 'benchmarks/paper_replay/flink_medians.json'
PREVIOUS = Path('/tmp/claude-1000/-home-userroot-Codex-CROWN/ec685d80-d57a-440f-9bb0-717b126b9b7b/scratchpad/bench/runs-G1')
MiB = 1024


def flink_key(case):
    """flink_medians.json key of a C++ case."""
    medians = json.loads(FLINK_MEDIANS.read_text())
    if case in medians:
        return case
    match = re.fullmatch(r'snb(\d)-sf([\d.]+)-full', case)
    if match:
        key = f'scale-snb{match[1]}_window-sf{match[2]}'
        if key in medians:
            return key
    return None


def previous(case):
    try:
        return json.loads((PREVIOUS / case / 'result.json').read_text())
    except (FileNotFoundError, ValueError):
        return {}


def cxx_job(campaign, bindir, group, config, rep):
    kind, request = paper.request_for(group)
    case = group['case_id'].replace('-reference_ordered_v1', '')
    requests = campaign / 'requests'
    requests.mkdir(exist_ok=True)
    path = requests / f'{case}.json'
    if not path.exists():
        path.write_text(json.dumps(request, indent=1))
    gc, pool = config.split('-')
    before = previous(case)
    rss_gib = before.get('maxrss_MiB', 1024) / 1024
    mem = max(2, math.ceil(rss_gib * 1.5 + 1))
    if pool == 'unlimited':
        mem = max(4, math.ceil(rss_gib * 4 + 2))
    return {'id': f'cxx/{case}/{config}/r{rep}', 'kind': 'cxx', 'cores': 2 if gc == 'background' else 1,
            'mem_gib': mem, 'timeout_s': 3600, 'priority': 2, 'est_s': before.get('wall_s', 60),
            'cmd': [str(bindir / paper.BINARIES[kind]), str(path), group['input']['path']],
            'env': {'CROWN_GC': gc, 'CROWN_GC_POOL': pool},
            'meta': {'system': 'cxx', 'case': case, 'config': config, 'gc': gc, 'pool': pool, 'rep': rep,
                     'mode': group['mode']}}


def flink_jobs(case, p, reps):
    key = flink_key(case)
    if not key:
        return []
    medians = json.loads(FLINK_MEDIANS.read_text())
    point_id = medians[key]['flink_point']
    manifest = json.loads(MANIFEST.read_text())
    point = next(q for q in manifest['points'] if q['point_id'] == point_id)
    base = list(point['run_trials'][0]['driver_cli_arguments'])
    jobs = []
    for rep in range(1, reps + 1):
        argv = list(base)
        for flag, value in (('--output', '{dir}/run'), ('--cpus', '{cpus}'), ('--parallelism', str(p))):
            argv[argv.index(flag) + 1] = value
        if '--purpose' in argv:
            argv[argv.index('--purpose') + 1] = 'measurement'
        wall = medians[key]['flink_wall_median_s']
        est = wall if p == 1 else wall / (3 if p == 4 else 6) + 30
        jobs.append({'id': f'flink/{case}/p{p}/r{rep}', 'kind': 'flink', 'cores': p, 'mem_gib': 56,
                     'timeout_s': 14400 + 600, 'priority': 1 if p == 16 else 2, 'est_s': est, 'cmd': argv,
                     'meta': {'system': 'flink', 'case': case, 'flink_point': point_id, 'parallelism': p, 'rep': rep}})
    return jobs


def init(campaign, bindir):
    jobs = []
    for group in paper.cases():
        case = group['case_id'].replace('-reference_ordered_v1', '')
        for config in ('blocking-64M', 'blocking-unlimited', 'background-64M'):
            for rep in (1, 2, 3):
                jobs.append(cxx_job(campaign, bindir, group, config, rep))
        jobs += flink_jobs(case, 1, 1) + flink_jobs(case, 4, 3) + flink_jobs(case, 16, 3)
    verify = ROOT / 'benchmarks/paper_replay/verify_flat.py'
    for name, extra in (('window', ['--lines', '60000', '--window', '4000']),
                        ('long', ['--lines', '150000', '--exclude', 'TwoComb', '--exclude', 'length4_filter'])):
        jobs.append({'id': f'verify/{name}', 'kind': 'verify', 'cores': 2, 'mem_gib': 24, 'timeout_s': 7200,
                     'priority': 3, 'est_s': 1500,
                     'cmd': ['python3', str(verify), '--bin', str(bindir), '--out', '{dir}/out', '--jobs', '2'] + extra,
                     'meta': {'system': 'verify', 'name': name}})
    write(campaign, jobs)


def followups(campaign, job, result):
    """After the first 64M run of a case: larger pools if its peak RSS called for them."""
    meta = job.get('meta', {})
    if meta.get('system') != 'cxx' or meta.get('config') != 'blocking-64M' or meta.get('rep') != 1:
        return []
    rss = result.get('maxrss_kib', 0)
    configs = (['blocking-256M'] if rss > 256 * MiB else []) + (['blocking-4G'] if rss > 4 * MiB * MiB else [])
    if not configs:
        return []
    group = next((g for g in paper.cases() if g['case_id'].replace('-reference_ordered_v1', '') == meta['case']), None)
    if group is None:  # e.g. maintenance-only runs, which have no pool tiers
        return []
    bindir = Path(job['cmd'][0]).parent
    return [cxx_job(campaign, bindir, group, config, rep) for config in configs for rep in (1, 2, 3)]


def fivm(campaign, reps, supported):
    """F-IVM jobs: full mode for full cases, maintenance only (`none`) for delta cases."""
    runner = ROOT / 'benchmarks/fivm_replay/run_case.py'
    jobs = []
    for group in paper.cases():
        case = group['case_id'].replace('-reference_ordered_v1', '')
        match = re.fullmatch(r'runtime-(\w+)-(full|delta)', case)
        if not match or match[1] not in supported:
            continue
        query, mode = match[1], 'full' if match[2] == 'full' else 'none'
        for rep in range(1, reps + 1):
            jobs.append({'id': f'fivm/{case}/{mode}/r{rep}', 'kind': 'fivm', 'cores': 1, 'mem_gib': 8,
                         'timeout_s': 7200, 'priority': 2, 'est_s': 60,
                         'cmd': ['python3', str(runner), '--query', query, '--mode', mode, '--out', '{dir}/out'],
                         'meta': {'system': 'fivm', 'case': case, 'query': query, 'mode': mode, 'rep': rep}})
    write(campaign, jobs)


def none(campaign, bindir, queries, reps):
    """C++ CROWN with output mode `none` (maintain only) for graph queries."""
    jobs = []
    for group in paper.cases():
        case = group['case_id'].replace('-reference_ordered_v1', '')
        match = re.fullmatch(r'runtime-(\w+)-full', case)
        if not match or match[1] not in queries:
            continue
        kind, request = paper.request_for(group)
        request.update(output_mode='none', full_at_markers=False)
        name = f'runtime-{match[1]}-none'
        path = campaign / 'requests' / f'{name}.json'
        path.write_text(json.dumps(request, indent=1))
        before = previous(case)
        for rep in range(1, reps + 1):
            jobs.append({'id': f'cxx/{name}/blocking-64M/r{rep}', 'kind': 'cxx', 'cores': 1,
                         'mem_gib': max(2, math.ceil(before.get('maxrss_MiB', 1024) / 1024 * 1.5 + 1)),
                         'timeout_s': 3600, 'priority': 2, 'est_s': before.get('wall_s', 60),
                         'cmd': [str(bindir / paper.BINARIES[kind]), str(path), group['input']['path']],
                         'env': {'CROWN_GC': 'blocking', 'CROWN_GC_POOL': '64M'},
                         'meta': {'system': 'cxx', 'case': name, 'config': 'blocking-64M', 'gc': 'blocking',
                                  'pool': '64M', 'rep': rep, 'mode': 'none'}})
    write(campaign, jobs)


def write(campaign, jobs):
    campaign.mkdir(parents=True, exist_ok=True)
    path = campaign / 'jobs.jsonl'
    known = set()
    if path.exists():
        known = {json.loads(line)['id'] for line in path.read_text().splitlines() if line.strip()}
    added = [job for job in jobs if job['id'] not in known]
    with path.open('a') as f:
        for job in added:
            f.write(json.dumps(job) + '\n')
    print(f'{len(added)} jobs added ({len(known) + len(added)} total)')


def main():
    parser = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    parser.add_argument('action', choices=['init', 'fivm', 'none'])
    parser.add_argument('campaign', type=Path)
    parser.add_argument('--bin', type=Path)
    parser.add_argument('--reps', type=int, default=3)
    parser.add_argument('--queries', default='')
    args = parser.parse_args()
    campaign = args.campaign.resolve()
    if args.action == 'init':
        init(campaign, args.bin.resolve())
    elif args.action == 'fivm':
        fivm(campaign, args.reps, [q for q in args.queries.split(',') if q])
    else:
        none(campaign, args.bin.resolve(), [q for q in args.queries.split(',') if q], args.reps)


if __name__ == '__main__':
    main()
