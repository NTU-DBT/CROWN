#!/usr/bin/env python3
"""Run paper replay cases (reference backend) and print a timing table.

Requests are built from the campaign bindings exactly like
run_native_stream_v3.py does. Usage:
  run.py --bin DIR --out DIR [--timeout S] [--jobs N] [--filter SUBSTR ...]
"""
import argparse, concurrent.futures, json, os, signal, subprocess, sys, time
from pathlib import Path

ROOT = Path('/home/userroot/Codex/CROWN')
sys.path.insert(0, str(ROOT / 'tools'))
from component_workloads import base_request  # noqa: E402

CAMPAIGN = ROOT / 'build/experiments/paper-serial-comparison-20261116-v1'
MANIFEST = CAMPAIGN / 'native-campaign-v8/run-manifest-v8.json'
BINARIES = {'routed_set': 'paper_native_routed', 'original_snb_routing': 'paper_native_snb',
            'explicit_exact_cyclic_fallback': 'paper_native_fallback',
            'sql_star_count': 'paper_native_aggregate'}


def cases():
    manifest = json.loads(MANIFEST.read_text())
    for group in manifest['measurement_groups']:
        if group['backend'] != 'reference_ordered_v1':
            continue
        if not group['case_id'].startswith(('runtime-', 'scale-', 'snb')):
            continue
        yield group


def request_for(group):
    route = json.loads(Path(group['binding']).read_text())
    mode = group['mode']
    sql = route['program']['sql']
    native = base_request('paper', sql, route['program']['catalog'], [], 'unused',
                          'reference_ordered_v1')['native']
    edges = group.get('source_edges_capacity_basis') or 10**7
    native.update(memory_limit_bytes=128 * 1024**3, work_limit=10**12,
                  mode='delta' if mode == 'delta' else 'maintenance',
                  fallback_source_rows=8 * edges, fallback_result_rows=100000000,
                  spool_rows=100000000, spool_bytes=64 * 1024**3)
    family = route['query_family']
    request = {'schema_version': 1, 'case_id': family, 'command': 'measure',
               'query_family': family, 'output_mode': mode, 'input_format': 'graph_csv',
               **route, 'native': native,
               'limits': {'input_events': group['physical_events'], 'output_rows': 10**12,
                          'capture_bytes': 128 * 1024 * 1024}}
    request['full_at_markers'] = mode == 'full' or route.get('full_at_markers', False)
    return route.get('native_execution', 'routed_set'), request


def run_case(group, bindir, out, timeout):
    kind, request = request_for(group)
    case = group['case_id'].replace('-reference_ordered_v1', '')
    directory = out / case
    directory.mkdir(parents=True, exist_ok=True)
    (directory / 'request.json').write_text(json.dumps(request, indent=2))
    command = ['/usr/bin/time', '-f', '%M', '-o', str(directory / 'maxrss.txt'),
               str(bindir / BINARIES[kind]), str(directory / 'request.json'), group['input']['path']]
    start = time.monotonic()
    with (directory / 'stdout').open('w') as stdout, (directory / 'stderr').open('w') as stderr:
        # Own process group, so a timeout kills the harness and not only /usr/bin/time.
        process = subprocess.Popen(command, stdout=stdout, stderr=stderr, start_new_session=True)
        try:
            status = process.wait(timeout=timeout)
            timed_out = False
        except subprocess.TimeoutExpired:
            os.killpg(process.pid, signal.SIGKILL)
            process.wait()
            status, timed_out = None, True
    wall = time.monotonic() - start
    result = {'case': case, 'wall_s': round(wall, 2), 'timed_out': timed_out, 'status': status}
    try:
        report = json.loads((directory / 'stdout').read_text())
        for key in ('apply_ns', 'output_ns', 'epoch_release_ns', 'loop_wall_ns'):
            if key in report:
                result[key.replace('_ns', '_s')] = round(report[key] / 1e9, 2)
        result['physical_inputs'] = report.get('physical_inputs')
        result['snapshot_rows'] = report.get('snapshot_rows')
        result['delta_rows'] = report.get('delta_rows')
    except (ValueError, FileNotFoundError):
        pass
    try:
        result['maxrss_MiB'] = int((directory / 'maxrss.txt').read_text().split()[-1]) // 1024
    except (ValueError, IndexError, FileNotFoundError):
        pass
    (directory / 'result.json').write_text(json.dumps(result, indent=2))
    print(json.dumps(result), flush=True)
    return result


def main():
    parser = argparse.ArgumentParser()
    parser.add_argument('--bin', type=Path, required=True)
    parser.add_argument('--out', type=Path, required=True)
    parser.add_argument('--timeout', type=int, default=3600)
    parser.add_argument('--jobs', type=int, default=1)
    parser.add_argument('--filter', action='append', default=[])
    parser.add_argument('--list', action='store_true')
    args = parser.parse_args()
    selected = [g for g in cases() if not args.filter or any(f in g['case_id'] for f in args.filter)]
    if args.list:
        for g in selected:
            print(g['case_id'])
        return
    args.out.mkdir(parents=True, exist_ok=True)
    with concurrent.futures.ThreadPoolExecutor(args.jobs) as pool:
        results = list(pool.map(lambda g: run_case(g, args.bin.resolve(), args.out.resolve(), args.timeout), selected))
    (args.out / 'summary.json').write_text(json.dumps(results, indent=2))


if __name__ == '__main__':
    main()
