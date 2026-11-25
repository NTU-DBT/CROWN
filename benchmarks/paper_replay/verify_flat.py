#!/usr/bin/env python3
"""Differentially verify two engines of the paper harnesses (default: the
keyed core, i.e. the harness default path, against the reference core).

Engines: keyed (no override), reference (CROWN_DELTA_ENGINE, CROWN_FALLBACK_ENGINE
and CROWN_WEIGHTED_ENGINE set to reference: the pre-keyed cores), flat
(CROWN_ENGINE=flat executors).

For each selected set case, both engines replay the same input prefix in
verify mode. Captures are compared block by block: delta rows sorted per
(relation_sequence, sign, values) within each physical event, snapshot and
final rows sorted within each block, plus every begin/end marker and count.
Usage:
  verify_flat.py --bin DIR --out DIR [--lines N] [--jobs J] [--filter=SUBSTR ...]
"""
import argparse, concurrent.futures, gzip, json, os, signal, subprocess, sys, time
from pathlib import Path

HERE = Path(__file__).resolve().parent
sys.path.insert(0, str(HERE))
import run as runmod  # noqa: E402


def prefix_input(path, lines, out, window=0):
    """First `lines` input lines. With window>0, keep only inserts and markers
    and erase each insert again `window` inserts later (a short sliding window),
    so deletions start early while state stays small."""
    import collections, hashlib
    digest = hashlib.sha1(str(path).encode()).hexdigest()[:10]
    target = out / (f'{digest}-{Path(path).name.replace(".gz", "")}.{lines}' + (f'.w{window}' if window else ''))
    if target.exists():
        return target
    opener = gzip.open if str(path).endswith('.gz') else open
    live = collections.deque()
    with opener(path, 'rt') as source, open(str(target) + '.tmp', 'w') as sink:
        for count, line in enumerate(source):
            if count >= lines:
                break
            if not window or line.startswith('*'):
                sink.write(line)
                continue
            if not line.startswith('+'):
                continue
            sink.write(line)
            live.append(line)
            if len(live) > window:
                sink.write('-' + live.popleft()[1:])
    os.replace(str(target) + '.tmp', target)
    return target


# 'reference' pins every runtime that has a keyed core to its reference core.
REFERENCE_ENV = {'CROWN_DELTA_ENGINE': 'reference', 'CROWN_FALLBACK_ENGINE': 'reference',
                 'CROWN_WEIGHTED_ENGINE': 'reference'}
ENGINE_ENV = {'keyed': {}, 'reference': REFERENCE_ENV, 'flat': {'CROWN_ENGINE': 'flat'}}


def run_engine(binary, request, inp, directory, engine, timeout):
    directory.mkdir(parents=True, exist_ok=True)
    capture = directory / f'{engine}.capture.jsonl'
    if capture.exists():
        capture.unlink()
    request = dict(request, command='verify', capture_file=str(capture))
    request['limits'] = dict(request['limits'], input_events=10**12, capture_bytes=64 * 1024**3)
    (directory / f'{engine}.request.json').write_text(json.dumps(request))
    env = dict(os.environ)
    env.pop('CROWN_ENGINE', None)
    env.pop('CROWN_DELTA_ENGINE', None)
    env.update(ENGINE_ENV[engine])
    start = time.monotonic()
    with open(directory / f'{engine}.stdout', 'w') as out, open(directory / f'{engine}.stderr', 'w') as err:
        process = subprocess.Popen([str(binary), str(directory / f'{engine}.request.json'), str(inp)],
                                   stdout=out, stderr=err, env=env, start_new_session=True)
        try:
            status = process.wait(timeout=timeout)
        except subprocess.TimeoutExpired:
            os.killpg(process.pid, signal.SIGKILL)
            process.wait()
            status = 'timeout'
    return status, time.monotonic() - start, capture


def blocks(path):
    """Yield canonical blocks: (kind, header, sorted rows, footer)."""
    with open(path) as source:
        current = None
        rows = []
        for line in source:
            record = json.loads(line)
            kind = record['kind']
            if kind.endswith('_begin'):
                current = record
                rows = []
            elif kind == 'delta_row':
                rows.append((record['relation_sequence'], record['operation'], json.dumps(record['values'])))
            elif kind in ('snapshot_row', 'final_row'):
                rows.append(json.dumps(record['values']))
            elif kind == 'group_change':
                rows.append((record['relation_sequence'], json.dumps(record['key']), json.dumps(record['before']),
                             json.dumps(record['after'])))
            elif kind in ('snapshot_group', 'final_group'):
                rows.append(json.dumps([record['key'], record['values']]))
            elif kind.endswith('_end'):
                rows.sort()
                yield current, rows, record
                current = None
            else:
                raise ValueError(f'unknown capture record {kind}')


def compare(reference, flat):
    count = 0
    rows = 0
    left, right = blocks(reference), blocks(flat)
    while True:
        a = next(left, None)
        b = next(right, None)
        if a is None and b is None:
            return True, f'{count} blocks, {rows} rows identical'
        if a is None or b is None:
            return False, f'block count differs after {count} blocks'
        if a[0] != b[0] or a[2] != b[2] or a[1] != b[1]:
            detail = f'block {count} differs: ref {a[0]} {a[2]} rows={len(a[1])}; flat {b[0]} {b[2]} rows={len(b[1])}'
            ra, rb = set(a[1]), set(b[1])
            detail += f'; only-ref={sorted(ra - rb)[:5]} only-flat={sorted(rb - ra)[:5]}'
            return False, detail
        count += 1
        rows += len(a[1])


def main():
    parser = argparse.ArgumentParser()
    parser.add_argument('--bin', type=Path, required=True)
    parser.add_argument('--out', type=Path, required=True)
    parser.add_argument('--lines', type=int, default=150000)
    parser.add_argument('--jobs', type=int, default=8)
    parser.add_argument('--timeout', type=int, default=7200)
    parser.add_argument('--filter', action='append', default=[])
    parser.add_argument('--exclude', action='append', default=[])
    parser.add_argument('--window', type=int, default=0)
    parser.add_argument('--snb-scale', type=int, default=10, help='SNB prefix length multiplier')
    parser.add_argument('--left', default='reference', choices=sorted(ENGINE_ENV))
    parser.add_argument('--right', default='keyed', choices=sorted(ENGINE_ENV))
    args = parser.parse_args()
    args.out.mkdir(parents=True, exist_ok=True)
    selected = []
    for group in runmod.cases():
        kind, request = runmod.request_for(group)
        if kind not in ('routed_set', 'original_snb_routing', 'explicit_exact_cyclic_fallback', 'sql_star_count'):
            continue
        if args.filter and not any(f in group['case_id'] for f in args.filter):
            continue
        if any(f in group['case_id'] for f in args.exclude):
            continue
        selected.append((group, kind, request))

    inputs = {}
    for group, kind, request in selected:
        case = group['case_id'].replace('-reference_ordered_v1', '')
        lines = args.lines * (args.snb_scale if 'snb' in case else 1)
        inputs[case] = (lines, prefix_input(group['input']['path'], lines, args.out, args.window))

    def one(item):
        group, kind, request = item
        case = group['case_id'].replace('-reference_ordered_v1', '')
        lines, inp = inputs[case]
        binary = args.bin.resolve() / runmod.BINARIES[kind]
        directory = args.out / case
        with concurrent.futures.ThreadPoolExecutor(2) as pool:
            ref = pool.submit(run_engine, binary, request, inp, directory, args.left, args.timeout)
            fl = pool.submit(run_engine, binary, request, inp, directory, args.right, args.timeout)
            (rs, rt, rc), (fs, ft, fc) = ref.result(), fl.result()
        result = {'case': case, 'lines': lines, 'window': args.window, 'left': args.left, 'right': args.right,
                  'reference_status': rs, 'flat_status': fs, 'reference_s': round(rt, 2), 'flat_s': round(ft, 2)}
        if rs == 0 and fs == 0:
            ok, detail = compare(rc, fc)
            result.update(identical=ok, detail=detail)
            if ok:
                rc.unlink()
                fc.unlink()
        else:
            result.update(identical=False, detail='engine failure')
        (directory / 'verify.json').write_text(json.dumps(result, indent=2))
        print(json.dumps(result), flush=True)
        return result

    with concurrent.futures.ThreadPoolExecutor(args.jobs) as pool:
        results = list(pool.map(one, selected))
    (args.out / 'summary.json').write_text(json.dumps(results, indent=2))
    bad = [r['case'] for r in results if not r.get('identical')]
    print('ALL IDENTICAL' if not bad else f'DIFFERENCES: {bad}', flush=True)


if __name__ == '__main__':
    main()
