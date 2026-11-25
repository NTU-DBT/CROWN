#!/usr/bin/env python3
"""Wait for something notable in a scheduler.py campaign, print one JSON summary, exit.

  watch.py CAMPAIGN [--interval 900]

Exits when a job fails or times out (since this watcher started), the
scheduler process is gone, every job is done, free memory or disk runs low,
or --interval seconds pass (heartbeat). Exit code 0 heartbeat/done, 1 alert.
"""
import argparse, json, os, shutil, time
from pathlib import Path


def load(path):
    try:
        return json.loads(path.read_text())
    except (FileNotFoundError, ValueError):
        return {}


def ended(campaign, since):
    out = []
    try:
        lines = (campaign / 'events.log').read_text().splitlines()
    except FileNotFoundError:
        return out
    for line in lines:
        event = json.loads(line)
        if event.get('event') == 'end' and event['t'] >= since:
            out.append(event)
    return out


def tail(path, lines=8):
    try:
        return path.read_text(errors='replace').strip().splitlines()[-lines:]
    except FileNotFoundError:
        return []


def main():
    parser = argparse.ArgumentParser()
    parser.add_argument('campaign', type=Path)
    parser.add_argument('--interval', type=float, default=900)
    args = parser.parse_args()
    campaign = args.campaign.resolve()
    start = time.monotonic()
    since = time.strftime('%Y-%m-%dT%H:%M:%S')
    while True:
        status = load(campaign / 'status.json')
        events = ended(campaign, since)
        bad = [e for e in events if e.get('status') != 'ok']
        alive = status.get('pid') and os.path.exists(f"/proc/{status['pid']}")
        disk_gib = shutil.disk_usage(campaign).free / 2**30
        reason = None
        if bad:
            reason = 'job_failed'
        elif not alive:
            reason = 'scheduler_not_running'
        elif status.get('pending') == 0 and status.get('running') == 0:
            reason = 'all_done'
        elif disk_gib < 20 or status.get('mem_available_gib', 999) < 16:
            reason = 'low_resources'
        elif time.monotonic() - start >= args.interval:
            reason = 'heartbeat'
        if reason:
            summary = {'reason': reason, 'status': {k: status.get(k) for k in
                       ('time', 'done', 'total', 'pending', 'running', 'reserved_gib', 'mem_available_gib')},
                       'disk_free_gib': round(disk_gib, 1),
                       'running_jobs': status.get('running_jobs', []),
                       'completed_since_start': len(events),
                       'failures': [{'id': e['id'], 'status': e['status'],
                                     'stderr_tail': tail(campaign / 'runs' / e['id'] / 'stderr')} for e in bad]}
            print(json.dumps(summary, indent=1))
            raise SystemExit(1 if reason in ('job_failed', 'scheduler_not_running', 'low_resources') else 0)
        time.sleep(20)


if __name__ == '__main__':
    main()
