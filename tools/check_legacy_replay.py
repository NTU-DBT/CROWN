#!/usr/bin/env python3
"""Check captured legacy outputs with tiny independent relational oracles.

This offline checker neither launches nor times a baseline. Separate build/run
receipts bind the external executable, dependencies, input and captured output.
The admitted replays are int32 set inputs for Scala L3 and positive unique-edge,
insert-only milestone COUNT DISTINCT for C++ line5cd, or mixed grouped COUNT
for line5gc. See docs/legacy_baselines.md.
"""
from __future__ import annotations
import argparse
import base64
from collections import Counter
import hashlib
import json
from pathlib import Path
import re


def check(condition, message):
    """Keep verification active under python -O; failures never write a pass."""
    if not condition:
        raise ValueError(message)


def join3(relations):
    """Literal G1(A,B) join G2(B,C) join G3(C,D); cubic tiny-input work."""
    return {(a, b, c, d) for a, b in relations['G1']
            for other_b, c in relations['G2'] if b == other_b
            for other_c, d in relations['G3'] if c == other_c}


def scala_rows(stdout):
    """Accept only replay records plus the unchanged function's close message."""
    result = []
    diagnostics = 0
    for line in stdout.splitlines():
        if line.startswith('{'):
            row = json.loads(line)
            check(set(row) == {'event', 'delta_base64', 'rows'}, 'unexpected Scala record fields')
            result.append(row)
        else:
            check(re.fullmatch(r'Process Function L3ProcessFunction Parallelism 0 StartTime \d+ EndTime \d+ Difference -?\d+ AccumulateTime \d+ EnumerationTime \d+, StorageTime \d+', line),
                  'unexpected Scala stdout outside replay records')
            diagnostics += 1
    check(diagnostics == 1, 'missing or duplicated Scala close diagnostic')
    return result


def signed_rows(encoded):
    """Decode raw delta lines without deduplication; names determine column order."""
    result = Counter()
    raw = base64.b64decode(encoded, validate=True).decode('utf-8')
    for line in raw.splitlines():
        match = re.fullmatch(r'([+-])\s+(.+)', line)
        check(match is not None, 'unexpected signed Scala output line')
        # JoinedAttributes prints named pairs, unlike the stale published test
        # parser's expectation of four values followed by four column names.
        check(re.fullmatch(r'\([A-D],-?\d+\)(?: , \([A-D],-?\d+\)){3}', match[2]),
              'unexpected Scala joined-output representation')
        pairs = re.findall(r'\(([A-D]),(-?\d+)\)', match[2])
        check({name for name, _ in pairs} == set('ABCD'), 'unexpected Scala output schema')
        values = {name: int(value) for name, value in pairs}
        result[(match[1], tuple(values[name] for name in 'ABCD'))] += 1
    return result


def verify_scala(trace, stdout):
    """Check every raw signed delta and current snapshot against the direct join."""
    lines = trace.splitlines()
    actual = scala_rows(stdout)
    check(lines and len(actual) == len(lines), 'missing or extra Scala event records')
    relations = {name: set() for name in ('G1', 'G2', 'G3')}
    rows, snapshots, emitted = set(), [], 0
    for number, (line, observed) in enumerate(zip(lines, actual), 1):
        fields = line.split(',')
        check(len(fields) == 4 and fields[0] in ('+', '-') and fields[1] in relations,
              'Scala replay requires +/- and G1/G2/G3 with two int32 fields')
        check(all(re.fullmatch(r'[+-]?[0-9]+', item) for item in fields[2:]), 'Scala input requires signed decimal fields')
        value = tuple(map(int, fields[2:]))
        check(all(-(1 << 31) <= item < (1 << 31) for item in value), 'Scala input exceeds int32')
        target = relations[fields[1]]
        if fields[0] == '+':
            check(value not in target, 'duplicate Scala insert is unqualified')
            target.add(value)
        else:
            check(value in target, 'absent Scala delete is unqualified')
            target.remove(value)
        after = join3(relations)
        wanted = Counter({('+', row): 1 for row in after - rows})
        wanted.update({('-', row): 1 for row in rows - after})
        check(type(observed['event']) is int and observed['event'] == number, 'Scala event sequence mismatch')
        check(signed_rows(observed['delta_base64']) == wanted, f'Scala signed delta mismatch at event {number}')
        check(isinstance(observed['rows'], list) and all(isinstance(row, list) and len(row) == 4 and all(type(v) is int for v in row) for row in observed['rows']),
              'unexpected Scala snapshot representation')
        check(Counter(map(tuple, observed['rows'])) == Counter(after), f'Scala snapshot mismatch at event {number}')
        emitted += sum(wanted.values())
        snapshots.append(dict(event=number, rows=len(after), signed_records=sum(wanted.values())))
        rows = after
    return dict(events=len(lines), signed_records=emitted, snapshots=snapshots)


def five_edge_paths(edges):
    """Direct five-copy self-join; preserve endpoint witnesses before projection."""
    paths = list(edges)
    for _ in range(4):
        paths = [path + (dst,) for path in paths for src, dst in edges if path[-1] == src]
    return paths


def graph_milestones(trace, deletions):
    """Yield direct join paths at stars; reject unqualified graph operations."""
    edges, pending = set(), False
    for number, line in enumerate(trace.splitlines(), 1):
        if line == '*':
            pending = False
            yield number, len(edges), five_edge_paths(edges)
            continue
        fields = line.split('|')
        allowed = ('+', '-') if deletions else ('+',)
        check(len(fields) == 3 and fields[0] in allowed and all(re.fullmatch(r'[1-9][0-9]*', v) for v in fields[1:]),
              'graph replay requires qualified +/- operations and positive integer IDs')
        value = tuple(map(int, fields[1:]))
        check(all(item < (1 << 32) for item in value), 'graph fixture IDs must fit uint32')
        if fields[0] == '+':
            check(value not in edges, 'duplicate graph insert is unqualified')
            edges.add(value)
        else:
            check(value in edges, 'absent graph delete is unqualified')
            edges.remove(value)
        pending = True
    check(not pending, 'graph replay ends with an unobserved update; require a final milestone')


def cpp_frames(stdout, query):
    """Frame complete milestone output; diagnostics are checked, never measured."""
    lines = stdout.splitlines()
    if lines and lines[-1] == '':
        lines.pop()  # Published main emits one final blank line.
    check(lines[:2] == [f'Query: {query}', 'Algorithm: Crown'], 'unexpected C++ query or algorithm header')
    frames, pending, index = [], [], 2
    while index < len(lines):
        line = lines[index]
        if line.startswith('Running Time:'):
            check(re.fullmatch(r'Running Time: -?\d+ ms', line), 'unexpected C++ timing diagnostic')
            check(index + 1 < len(lines) and re.fullmatch(r'Memory Usage: (?:\d+ kB|N/A)', lines[index + 1]),
                  'missing or invalid C++ memory diagnostic')
            frames.append(pending)
            pending = []
            index += 2
        else:
            pending.append(line)
            index += 1
    check(not pending, 'dangling C++ output without a completed milestone')
    return frames


def verify_cpp(trace, stdout):
    """Match every insert-only line5cd distinct count, retaining witness controls."""
    milestones = [dict(line=n, edges=e, distinct=len({p[1:5] for p in paths}), bag_paths=len(paths))
                  for n, e, paths in graph_milestones(trace, False)]
    frames = cpp_frames(stdout, 'line5cd')
    check(milestones and len(frames) == len(milestones), 'missing or extra C++ milestone output')
    for number, (frame, expected) in enumerate(zip(frames, milestones), 1):
        check(frame == [f"{expected['distinct']}.0000"], f'line5cd result mismatch at milestone {number}')
    return dict(milestones=milestones)


def verify_grouped(trace, stdout, replacements):
    """Check line5gc full groups or absolute replacements folded per milestone."""
    wanted = [(n, Counter((p[2], p[3]) for p in paths)) for n, _, paths in graph_milestones(trace, True)]
    frames = cpp_frames(stdout, 'line5gc')
    check(wanted and len(frames) == len(wanted), 'missing or extra line5gc milestones')
    state, totals, records, removals = {}, [], 0, 0
    for number, (frame, (line, expected)) in enumerate(zip(frames, wanted), 1):
        if not replacements:
            state = {}
        for record in frame:
            match = re.fullmatch(r'\(([1-9][0-9]*),([1-9][0-9]*)\) -> (0|[1-9][0-9]*)\.0000', record)
            check(match is not None, 'unexpected line5gc group representation')
            key, value = (int(match[1]), int(match[2])), int(match[3])
            if replacements:
                # A record carries the new absolute count, including zero for
                # removal. Several alias updates may replace one group again.
                if value:
                    state[key] = value
                else:
                    state.pop(key, None)
                    removals += 1
            else:
                check(value and key not in state, 'duplicate or zero group in full line5gc output')
                state[key] = value
            records += 1
        check(state == dict(expected), f'line5gc state mismatch at milestone {number}')
        totals.append(dict(line=line, groups=len(expected), bag_paths=sum(expected.values())))
    return dict(milestones=totals, output_records=records, zero_replacements=removals,
                output_semantics='absolute count replacements' if replacements else 'full grouped counts')


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--baseline', choices=['scala-l3', 'cpp-line5cd', 'cpp-line5gc-full', 'cpp-line5gc-replacements'], required=True)
    parser.add_argument('--trace', type=Path, required=True)
    parser.add_argument('--stdout', type=Path, required=True)
    parser.add_argument('--output', type=Path, required=True)
    args = parser.parse_args()
    check(not args.output.exists(), 'refusing to overwrite an existing evidence report')
    trace_bytes, stdout_bytes = args.trace.read_bytes(), args.stdout.read_bytes()
    trace, stdout = trace_bytes.decode('utf-8'), stdout_bytes.decode('utf-8')
    if args.baseline == 'scala-l3':
        result = verify_scala(trace, stdout)
    elif args.baseline == 'cpp-line5cd':
        result = verify_cpp(trace, stdout)
    else:
        result = verify_grouped(trace, stdout, args.baseline.endswith('replacements'))
    report = dict(status='pass', baseline=args.baseline, role='offline external-capture correctness check',
                  baseline_launched=False, timing_eligible=False, result=result,
                  inputs={str(p): hashlib.sha256(raw).hexdigest() for p, raw in ((args.trace, trace_bytes), (args.stdout, stdout_bytes), (Path(__file__), Path(__file__).read_bytes()))})
    args.output.parent.mkdir(parents=True, exist_ok=True)
    with args.output.open('x') as stream:
        stream.write(json.dumps(report, indent=2) + '\n')
    print(json.dumps(dict(status='pass', baseline=args.baseline, output=str(args.output))))


if __name__ == '__main__':
    main()
