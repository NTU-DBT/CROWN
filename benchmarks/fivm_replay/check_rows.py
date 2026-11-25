#!/usr/bin/env python3
"""Row-by-row check of an F-IVM replay binary against SQLite.

  check_rows.py --query Q --out DIR [--work DIR] [--seeds 1 2 3] [--real-inserts N]

Builds small fixtures with insertions, deletions and markers, replays each one
through WORK/bin/<q> in full mode with row capture, and compares every frame
(each marker plus the final state) with SQLite evaluating the binding's own
program.sql over relations maintained with the binding's own routing
(graph_aliases with min_src_exclusive / min_dst_exclusive, or tag_routes).
Fixtures:
  synthetic-<seed>  random set-valid edits over a node pool that straddles the
                    filter cutoffs (0, 32684) and includes self-loops; drains at the end
  real-<offset>     consecutive inserts from the campaign input as a sliding
                    window (deletes start after the window fills); drains at the end
Writes DIR/summary.json and prints it. The caller pins CPUs.
"""
import argparse
import collections
import json
import random
import sqlite3
import subprocess
import sys
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent))
from run_case import QUERIES, WORK, canonical, manifest_group  # noqa: E402

POOL = [0, 1, 2, 3, 4, 5, 32684, 32685, 32686, 40000, 40001]


def synthetic(binding, seed, edits=400, every=25, live_cap=45):
    rng = random.Random(seed)
    tagged = binding['input_format'] == 'tagged_csv'
    universe = [('G', s, d) for s in POOL for d in POOL] if tagged else [(s, d) for s in POOL for d in POOL]
    if tagged:
        universe += [('V1', x) for x in POOL] + [('V2', x) for x in POOL]
    live, order, lines = set(), [], []
    for i in range(1, edits + 1):
        if live and (len(live) >= live_cap or rng.random() < 0.35):
            item = rng.choice(order)
            live.remove(item)
            order.remove(item)
            lines.append(('-', item))
        else:
            item = rng.choice([u for u in universe if u not in live])
            live.add(item)
            order.append(item)
            lines.append(('+', item))
        if i % every == 0:
            lines.append('*')
    rng.shuffle(order)
    for i, item in enumerate(order, 1):
        lines.append(('-', item))
        if i % every == 0:
            lines.append('*')
    lines.append('*')
    return lines


def real(source, offset, count, window, every):
    inserts = []
    with open(source) as handle:
        seen = 0
        for line in handle:
            if line[0] != '+':
                continue
            seen += 1
            if seen <= offset:
                continue
            parts = line.rstrip('\n').split(',')[1:]
            inserts.append(tuple(parts[:1] + [int(v) for v in parts[1:]]) if not parts[0].lstrip('-').isdigit()
                           else tuple(int(v) for v in parts))
            if len(inserts) == count:
                break
    lines = []
    for i, item in enumerate(inserts):
        lines.append(('+', item))
        if i >= window:
            lines.append(('-', inserts[i - window]))
        if (i + 1) % every == 0:
            lines.append('*')
    for i, item in enumerate(inserts[max(0, len(inserts) - window):], 1):
        lines.append(('-', item))
        if i % every == 0:
            lines.append('*')
    lines.append('*')
    return lines


def render(lines):
    return ''.join('*\n' if line == '*' else f'{line[0]},{",".join(map(str, line[1]))}\n' for line in lines)


# Equivalent form of the star_cnt SQL (COUNT(*) of the 4-way join on a is the
# product of the per-alias degrees of a), used on real-data fixtures where the
# literal join has deg(a)^4 rows per group and is too slow for SQLite.
STAR_EQUIVALENT = ('SELECT g1.n*g2.n*g3.n*g4.n, a FROM '
                   + ' JOIN '.join(f'(SELECT a, COUNT(*) n FROM g{i} GROUP BY a) g{i}' + ('' if i == 1 else ' USING (a)')
                                   for i in range(1, 5)))


class Oracle:
    def __init__(self, binding, equivalent=False):
        self.binding = binding
        self.db = sqlite3.connect(':memory:')
        self.columns = {}
        for table in binding['program']['catalog']['catalog']['tables']:
            names = [c['name'] for c in table['columns']]
            self.columns[table['name']] = names
            self.db.execute(f'CREATE TABLE {table["name"]} ({", ".join(n + " INTEGER" for n in names)})')
        self.star = binding['query_family'] == 'star-count'
        self.sql = STAR_EQUIVALENT if self.star and equivalent else binding['program']['sql']
        self.updates = 0

    def routes(self, item):
        if self.binding['input_format'] == 'tagged_csv':
            tag, *values = item
            return [(r['table'], values) for r in self.binding['tag_routes'][tag]
                    if r.get('min_dst_exclusive') is None or values[1] > r['min_dst_exclusive']]
        src, dst = item
        out = []
        for r in self.binding['graph_aliases']:
            if r.get('min_src_exclusive') is not None and src <= r['min_src_exclusive']:
                continue
            if r.get('min_dst_exclusive') is not None and dst <= r['min_dst_exclusive']:
                continue
            out.append((r['table'], [src, dst]))
        return out

    def apply(self, op, item):
        for table, values in self.routes(item):
            self.updates += 1
            cols = self.columns[table]
            if op == '+':
                self.db.execute(f'INSERT INTO {table} VALUES ({",".join("?" * len(values))})', values)
            else:
                where = ' AND '.join(f'{c}=?' for c in cols)
                cur = self.db.execute(f'DELETE FROM {table} WHERE rowid = (SELECT rowid FROM {table} WHERE {where} LIMIT 1)', values)
                assert cur.rowcount == 1, (table, values)

    def result(self):
        rows = self.db.execute(self.sql).fetchall()
        if self.star:  # SELECT COUNT(*), g1.a  ->  (a, count) as captured
            rows = [(a, n) for n, a in rows]
        return collections.Counter(tuple(r) for r in rows)


def parse_capture(path):
    frames = []
    for line in Path(path).read_text().splitlines():
        if line.startswith('*,'):
            frames.append((int(line[2:]), collections.Counter()))
        else:
            frames[-1][1][tuple(int(v) for v in line.split(','))] += 1
    return frames


def check(query, binary, binding, name, lines, out):
    fixture = out / f'{name}.csv'
    fixture.write_text(render(lines))
    capture = out / f'{name}.capture.csv'
    proc = subprocess.run([str(binary), str(fixture), 'full', str(capture)], capture_output=True, text=True)
    if proc.returncode:
        return {'fixture': name, 'ok': False, 'error': proc.stderr.strip()}
    report = json.loads(proc.stdout)
    frames = parse_capture(capture)
    oracle = Oracle(binding, equivalent=name.startswith('real'))
    expected, sequence = [], 0
    for line in lines:
        if line == '*':
            expected.append((sequence, oracle.result()))
        else:
            sequence += 1
            oracle.apply(*line)
    expected.append((sequence, oracle.result()))  # final state after the stream
    problems = []
    if len(frames) != len(expected):
        problems.append(f'{len(frames)} captured frames, expected {len(expected)}')
    for i, ((s1, got), (s2, want)) in enumerate(zip(frames, expected)):
        if s1 != s2 or got != want:
            problems.append(f'frame {i} seq {s1}/{s2}: rows {sum(got.values())} vs {sum(want.values())}, '
                            f'missing {list((want - got).keys())[:3]}, extra {list((got - want).keys())[:3]}')
    if report['relation_updates'] != oracle.updates:
        problems.append(f'relation_updates {report["relation_updates"]} vs {oracle.updates}')
    deletes = sum(1 for line in lines if line != '*' and line[0] == '-')
    return {'fixture': name, 'ok': not problems, 'oracle_sql': oracle.sql, 'edits': sequence, 'deletes': deletes, 'frames': len(expected),
            'rows_compared': sum(sum(c.values()) for _, c in expected),
            'nonempty_frames': sum(1 for _, c in expected if c), 'final_rows': report['final_rows'],
            'problems': problems[:5]}


def main():
    parser = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    parser.add_argument('--query', required=True)
    parser.add_argument('--out', type=Path, required=True)
    parser.add_argument('--work', type=Path, default=WORK)
    parser.add_argument('--binary', type=Path, help='override WORK/bin/<q> (e.g. a negative control)')
    parser.add_argument('--seeds', type=int, nargs='*', default=[1, 2, 3])
    parser.add_argument('--real-inserts', type=int, default=2000)
    parser.add_argument('--real-window', type=int, default=400)
    parser.add_argument('--real-offsets', type=int, nargs='*', default=[0, 300000])
    args = parser.parse_args()
    query = canonical(args.query)
    group = manifest_group(query)
    binding = json.loads(Path(group['binding']).read_text())
    binary = (args.binary or args.work / 'bin' / QUERIES[query]).resolve()
    out = args.out.resolve()
    out.mkdir(parents=True, exist_ok=True)
    results = [check(query, binary, binding, f'synthetic-{seed}', synthetic(binding, seed), out) for seed in args.seeds]
    for offset in args.real_offsets:
        lines = real(group['input']['path'], offset, args.real_inserts, args.real_window, args.real_window // 2)
        results.append(check(query, binary, binding, f'real-{offset}', lines, out))
    summary = {'query': query, 'binary': str(binary), 'binding': group['binding'], 'sql': binding['program']['sql'],
               'ok': all(r['ok'] for r in results), 'fixtures': results}
    (out / 'summary.json').write_text(json.dumps(summary, indent=2) + '\n')
    print(json.dumps(summary, indent=1))
    return 0 if summary['ok'] else 1


if __name__ == '__main__':
    sys.exit(main())
