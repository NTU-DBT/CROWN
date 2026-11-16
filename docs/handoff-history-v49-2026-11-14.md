# CROWN continuation handoff — V49

The full Refactor goal is active: 60 verified /1 in progress (A02) /17 not
started, 78 total. V49 completes the requested scoped usage-card coverage of
nonblank maintained code. This is documentation/inspection progress; no new
Refactor task or release gate is promoted. The accepted V48 handoff is preserved
byte-for-byte in [V48 history](handoff-history-v48-2026-11-14.md).

Start with the [examination guide](code_review.md),
[source/block index](code_specs/README.md),
[V49 verification record](verification/human-inspection-v49-2026-11-14.md),
[error-handling dispositions](code_specs/error_handling.md) and
[task ledger](task_ledger.md).

## Current source and evidence

- HEAD: `e369a623517723b3be3ea3e9806779f3c591e7f9`; `.git` remains read-only.
- Checkpoint: `build/verification/human-inspection-v49-progress-v1.json`.
- Frozen source: `build/verification/human-inspection-v49-source-v1`.
- Postcheck: `build/verification/human-inspection-v49-postseal-check-v1.json`.
- Receiving packet: `build/verification/inspection-structural-completion-v49-v1`.
- Coverage: 755 files /172,812 lines /19,462 blocks; 18,992 contracts cover
  all 16,561 nonblank blocks. Only 2,901 blank blocks retain structural facts
  without individual usage fields. No stale, unused or duplicate bindings;
  selected callable/type/inline-cluster gaps remain zero.

The packet retains original and corrected drafts, source pins, exact diffs,
complete mechanical audits and independent review limits. It receives all
2,148 former nonblank structural blocks. All 1,532 existing hash-only updates
preserve their authors; one existing card describes the changed offline locator.
The original runtime packet's V47 parent label is explicitly corrected to V48
in receiving. The planner Task span includes only its default constructor;
receiving records that precision against the original review finding.

Four maintained native-input paths changed: `tools/generate_code_specs.py`,
`CMakeLists.txt`, `tests/unit/indexed_table_model_test.cpp` and
`tests/unit/indexed_table_test.cpp`. Only the offline locator has changed code
behavior. The other edits correct five comment lines. All 355 apps/include/src
paths, all C++ executable tokens/literals and all CMake command bodies remain
V48-identical. Twenty-six pure locator controls and independent source/AST
checks pass. No native build, CTest run, benchmark or SDK/plotting job was run
in V49; this pass adds no runtime or update-path overhead.

## Continue safely from this checkpoint

Run the current-map checker after reading the seal/postcheck:

```sh
PYTHONDONTWRITEBYTECODE=1 python3 tools/check_code_specs.py
```

After a source change, review affected usage cards and callers, then regenerate
and check. Follow the [anchor format](code_specs/anchor_format.md); whole-file
hash updates alone do not constitute semantic review. Keep code direct and use
the existing ownership boundary for cleanup/classification. Do not add nested
catch/retry/undo layers or retained state without an actual caller requirement.

Main Release `build/inspection-build-scope-off-v1`, sanitizer
`build/w05-sanitizer` and Debug `build/w05-debug` are reusable when future code
changes require them. They were not rebuilt by V49. Completed private builds,
SDKs, dependency prefixes, review packets, plot environments and frozen source
snapshots remain immutable. In this environment `exec_command` needs
`sandbox_permissions="require_escalated"`; use `PYTHONDONTWRITEBYTECODE=1` for
repository/helper imports. The default launcher is broken. No approval was
rejected in V49. Do not stage or commit through read-only `.git`.

## Remaining work and inherited evidence

Use the ledger dependency order. A02's license/provenance disposition remains
open; C04 and B01 explicitly depend on A02. Do not label those cards verified
from independently implemented design or draft artifacts. Remaining experimental
and extension cards, R2 history retirement, packaging and all release reviews
retain their existing gates. W06 remains verified only within the documented
bounded SQL/native/local-sink profile; source-derived RAM-stage equivalence is
separate from actual syscall/process cuts. V01/V02 retain their scoped premises.

B05 remains verified for its V48 finite matrix: 19 families at four scales,
456 configurations/preflights, 1,368 measured plus 456 warmup reports, all 1,824
raw reports hashed/C01-checked, with target-process RSS corrected and controls
received. The exact frozen experiment bytes, full raw JSON samples/probes,
aggregate traversal checks and 50 figures remain preserved. Its generator
docstring successor is separately recorded; V49 makes no new performance or
whole-current-suite claim. Consult the V48 history and the
[B05 record](verification/b05-adversarial-scalability-2026-11-14.md) for commands
and the complete evidence limits.

All V49 review agents have finished and no native job is left running at seal.
Prefer own-model work and bounded Luna Max delegation; reserve Astra Max for
complex independent reasoning when it materially helps. No Astra was used in
V49. Preserve completed evidence and make the next change concrete and reviewable.
