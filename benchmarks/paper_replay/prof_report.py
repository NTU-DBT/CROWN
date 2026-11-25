#!/usr/bin/env python3
"""Aggregate sampler output: flat (self) and inclusive function profiles."""
import collections
import subprocess
import sys

binary, samples_path = sys.argv[1], sys.argv[2]
top = int(sys.argv[3]) if len(sys.argv) > 3 else 40
stacks = []
with open(samples_path) as f:
    for line in f:
        parts = line.split()
        if parts:
            stacks.append([int(p, 16) for p in parts])
addrs = sorted({a for s in stacks for a in s})
# Return addresses point after the call; subtract 1 for non-leaf frames.
query = sorted({a for a in addrs} | {a - 1 for a in addrs})
out = subprocess.run(['addr2line', '-f', '-C', '-e', binary],
                     input='\n'.join(hex(a) for a in query), capture_output=True, text=True).stdout.splitlines()
names = {}
for i, a in enumerate(query):
    fn = out[2 * i]
    fn = fn.split('(')[0] if len(fn) > 160 else fn
    names[a] = fn[:150]

def name(a, leaf):
    return names.get(a if leaf else a - 1, '??')

self_c = collections.Counter()
incl = collections.Counter()
for s in stacks:
    self_c[name(s[0], True)] += 1
    seen = set()
    for i, a in enumerate(s):
        n = name(a, i == 0)
        if n not in seen:
            seen.add(n)
            incl[n] += 1
total = len(stacks)
print(f'samples={total}')
print('--- self ---')
for n, c in self_c.most_common(top):
    print(f'{100*c/total:6.2f}%  {n}')
print('--- inclusive ---')
for n, c in incl.most_common(top):
    print(f'{100*c/total:6.2f}%  {n}')
