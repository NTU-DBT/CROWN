#!/usr/bin/env python3
"""Reproduce order variants from the frozen window-boundary fixture overlay."""
from pathlib import Path
ROOT=Path(__file__).resolve().parents[3]
PACKAGE=Path(__file__).resolve().parent
BASE=ROOT/'docs/verification/c01-statistics-policy-window-revision-proposal/overlay'
def edit(name, old, new):
    text=(BASE/name).read_text()
    if text.count(old)!=1: raise RuntimeError('order fixture seam changed: '+name)
    (PACKAGE/'overlay'/name).write_text(text.replace(old,new))
if __name__=='__main__':
    raise SystemExit('Frozen generated overlay: see order-changes.diff for exact reproducible edits; do not overwrite it.')
