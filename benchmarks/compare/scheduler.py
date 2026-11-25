#!/usr/bin/env python3
"""Resource-aware runner for the C++ CROWN / Flink / F-IVM comparison.

Jobs are JSON lines in CAMPAIGN/jobs.jsonl (append-only: the planner and other
tools may add jobs while this runs). Each job gets dedicated physical cores
(never an SMT sibling of another job's core) and a memory reservation, runs
under /usr/bin/time, and leaves CAMPAIGN/runs/<id>/job.json with wall_s,
user_s, sys_s, maxrss_kib, cpus, exit status and timeout flag.

Core pools (physical cores of this 2 x 24-core host; 20-23 stay free for
builds and monitoring):
  node0  0-19   C++ CROWN, F-IVM and verification jobs; Flink may use 0-15
                once none of those is pending
  node1 24-47   Flink: p16 jobs use 24-39; p1/p4 jobs use 40-47, and also
                24-39 once no p16 job is pending
A job whose command contains "{cpus}" pins itself (the Flink runner takes
--cpus); others are pinned with taskset.

Memory: each job reserves mem_gib; Flink jobs and the others have separate
budgets (--flink-memory-gib, --other-memory-gib), so neither starves the other.

Usage: scheduler.py CAMPAIGN [--flink-memory-gib 230] [--other-memory-gib 70] [--poll 2]
"""
import argparse, json, os, signal, subprocess, sys, time
from pathlib import Path

NODE0 = list(range(0, 20))
FLINK_WIDE = list(range(24, 40))
FLINK_NARROW = list(range(40, 48))


def mem_available_gib():
    for line in open('/proc/meminfo'):
        if line.startswith('MemAvailable:'):
            return int(line.split()[1]) / 1024**2
    return 0.0


def load_jobs(path):
    jobs = {}
    if path.exists():
        for line in path.read_text().splitlines():
            if line.strip():
                job = json.loads(line)
                jobs[job['id']] = job
    return jobs


def finished(run_dir):
    try:
        return json.loads((run_dir / 'job.json').read_text()).get('status') in ('ok', 'failed', 'timeout')
    except (FileNotFoundError, ValueError):
        return False


class Scheduler:
    def __init__(self, campaign, budgets):
        self.campaign = campaign
        self.budgets = budgets  # {'flink': GiB, 'other': GiB}
        self.running = {}   # id -> dict(job, process, cpus, start, dir)
        self.busy = set()
        self.events = (campaign / 'events.log').open('a')

    def log(self, **event):
        event['t'] = time.strftime('%Y-%m-%dT%H:%M:%S')
        self.events.write(json.dumps(event) + '\n')
        self.events.flush()

    def pool(self, job, pending):
        if job['kind'] != 'flink':
            return NODE0
        # Once no C++/F-IVM/verification job waits, Flink may also use cores
        # 0-15 (16-19 stay with the other systems for jobs added later).
        spare = NODE0[:16] if not any(j['kind'] != 'flink' for j in pending) else []
        if job['cores'] >= 16:
            return FLINK_WIDE + spare
        wide_wanted = any(j['kind'] == 'flink' and j['cores'] >= 16 for j in pending)
        return FLINK_NARROW + ([] if wide_wanted else FLINK_WIDE) + spare

    def allocate(self, job, pending):
        free = [c for c in self.pool(job, pending) if c not in self.busy]
        if len(free) < job['cores']:
            return None
        # Prefer a contiguous run of cores.
        for i in range(len(free) - job['cores'] + 1):
            run = free[i:i + job['cores']]
            if run[-1] - run[0] == job['cores'] - 1:
                return run
        # Multi-core Flink jobs stay on contiguous cores of one socket.
        return None if job['kind'] == 'flink' and job['cores'] > 1 else free[:job['cores']]

    @staticmethod
    def budget_class(job):
        return 'flink' if job['kind'] == 'flink' else 'other'

    def reserved(self, budget=None):
        return sum(r['job'].get('mem_gib', 1) for r in self.running.values()
                   if budget is None or self.budget_class(r['job']) == budget)

    def launch(self, job, cpus):
        run_dir = self.campaign / 'runs' / job['id']
        run_dir.mkdir(parents=True, exist_ok=True)
        cpu_list = ','.join(map(str, cpus))
        command = [part.replace('{cpus}', cpu_list).replace('{dir}', str(run_dir)) for part in job['cmd']]
        if '{cpus}' not in ' '.join(job['cmd']):
            command = ['taskset', '-c', cpu_list] + command
        command = ['/usr/bin/time', '-f', '%e %U %S %M', '-o', str(run_dir / 'time.txt')] + command
        env = dict(os.environ)
        for key in [k for k in env if k.startswith('CROWN_')]:
            del env[key]
        env.update(job.get('env', {}))
        stdout = (run_dir / 'stdout').open('w')
        stderr = (run_dir / 'stderr').open('w')
        process = subprocess.Popen(command, stdout=stdout, stderr=stderr, env=env,
                                   cwd=job.get('cwd', '/home/userroot/Codex/CROWN'), start_new_session=True)
        stdout.close(); stderr.close()
        (run_dir / 'command.json').write_text(json.dumps({'command': command, 'env': job.get('env', {}),
                                                           'cpus': cpus}, indent=1))
        self.running[job['id']] = {'job': job, 'process': process, 'cpus': cpus, 'start': time.monotonic(),
                                   'dir': run_dir}
        self.busy.update(cpus)
        self.log(event='start', id=job['id'], cpus=cpus)

    def reap(self):
        done = []
        for job_id, run in self.running.items():
            process, job = run['process'], run['job']
            elapsed = time.monotonic() - run['start']
            timed_out = False
            if process.poll() is None:
                if elapsed <= job.get('timeout_s', 7200):
                    continue
                os.killpg(process.pid, signal.SIGKILL)
                process.wait()
                timed_out = True
            wall = time.monotonic() - run['start']
            result = {'id': job_id, 'kind': job['kind'], 'meta': job.get('meta', {}), 'cpus': run['cpus'],
                      'cores': len(run['cpus']), 'exit': process.returncode, 'timed_out': timed_out,
                      'wall_s': round(wall, 3)}
            try:
                fields = (run['dir'] / 'time.txt').read_text().split()[-4:]
                result.update(time_wall_s=float(fields[0]), user_s=float(fields[1]), sys_s=float(fields[2]),
                              maxrss_kib=int(fields[3]))
            except (FileNotFoundError, ValueError, IndexError):
                pass
            result['status'] = 'timeout' if timed_out else ('ok' if process.returncode == 0 else 'failed')
            (run['dir'] / 'job.json').write_text(json.dumps(result, indent=1))
            self.busy.difference_update(run['cpus'])
            self.log(event='end', id=job_id, status=result['status'], wall_s=result['wall_s'],
                     maxrss_kib=result.get('maxrss_kib'))
            done.append((job, result))
        for job, _ in done:
            del self.running[job['id']]
        return done

    def write_status(self, pending, jobs):
        now = time.monotonic()
        status = {'time': time.strftime('%Y-%m-%dT%H:%M:%S'), 'pid': os.getpid(),
                  'pending': len(pending), 'running': len(self.running),
                  'done': sum(1 for j in jobs.values() if finished(self.campaign / 'runs' / j['id'])),
                  'total': len(jobs), 'reserved_gib': self.reserved(), 'mem_available_gib': round(mem_available_gib(), 1),
                  'running_jobs': [{'id': i, 'cpus': r['cpus'], 'elapsed_s': round(now - r['start'])}
                                   for i, r in self.running.items()]}
        temp = self.campaign / 'status.tmp'
        temp.write_text(json.dumps(status, indent=1))
        os.replace(temp, self.campaign / 'status.json')

    def run(self, poll):
        jobs_path = self.campaign / 'jobs.jsonl'
        sys.path.insert(0, str(Path(__file__).resolve().parent))
        import plan  # follow-up jobs (pool tiers)
        while True:
            jobs = load_jobs(jobs_path)
            for job, result in self.reap():
                for extra in plan.followups(self.campaign, job, result):
                    if extra['id'] not in jobs:
                        with jobs_path.open('a') as f:
                            f.write(json.dumps(extra) + '\n')
                jobs = load_jobs(jobs_path)
            pending = [j for j in jobs.values()
                       if j['id'] not in self.running and not finished(self.campaign / 'runs' / j['id'])]
            pending.sort(key=lambda j: (j.get('priority', 5), -j.get('est_s', 0), j['id']))
            for job in pending:
                need = job.get('mem_gib', 1)
                budget = self.budget_class(job)
                if self.reserved(budget) + need > self.budgets[budget] or mem_available_gib() < need + 8:
                    continue
                cpus = self.allocate(job, pending)
                if cpus:
                    self.launch(job, cpus)
            pending = [j for j in pending if j['id'] not in self.running]
            self.write_status(pending, jobs)
            # Jobs may still be appended (e.g. F-IVM once its harness is ready):
            # exit when idle only if asked to.
            if not pending and not self.running and (self.campaign / 'STOP_WHEN_IDLE').exists():
                self.log(event='idle_exit')
                return
            if (self.campaign / 'STOP').exists():
                self.log(event='stop_requested', running=list(self.running))
                return
            time.sleep(poll)


def main():
    parser = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    parser.add_argument('campaign', type=Path)
    parser.add_argument('--flink-memory-gib', type=float, default=230)
    parser.add_argument('--other-memory-gib', type=float, default=70)
    parser.add_argument('--poll', type=float, default=2)
    args = parser.parse_args()
    args.campaign.mkdir(parents=True, exist_ok=True)
    Scheduler(args.campaign.resolve(), {'flink': args.flink_memory_gib, 'other': args.other_memory_gib}).run(args.poll)


if __name__ == '__main__':
    main()
