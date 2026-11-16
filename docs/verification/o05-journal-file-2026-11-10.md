# O05 durable journal file component — 10 November 2026

O05 remains in progress. Root implemented the Linux journal storage component;
no sub-agent or Astra was used in this cohort. The predecessor codec's1035 source
paths were verified and preserved before changes. Source2 has1041 paths; only
CMakeLists.txt and six new journal-file source/test/support files differ. Every
previous test, fixture, assertion, cap and timeout remains unchanged.

The maintained File API adds exclusive advisory writer ownership, durable
create-without-replacement, streamed account-funded prefix loading, validated
append plus fsync, checked one-shot Linux close, bounded ordinary I/O attempts
and cleanup, explicit unknown outcomes/poisoned owners and incomplete-tail repair.
Repair preserves complete pending input and partial physical watermark commits.
The API requires supported local Linux filesystem semantics, a trusted directory
and a stable final name. Process-exit tests do not simulate power loss.
See the [file contract](../journal-files.md) and [record contract](../journal.md).

Final source2 selected57/57 tests PASS in all four native modes:
Debug 25.01s, Release 13.22s, Clang18 20.41s, ASan+UBSan/leaks 95.16s.
The normal inventory has244 names; every prior241 name remains. These57 comprise
the predecessor54 and three new journal file tests. This is component regression
acceptance, not whole244/fresh-source acceptance or a completed O05 card.

Actual native coverage includes every byte cut across the independent physical
input/commit sequence and every corruption byte in that log, explicit repair,
partial-window physical/command/substep resumption, a second writer in another
process, exact/one-under receiving-memory/validation budgets, observed allocation
failures and account-resident/descriptor cleanup. All136 injected syscall errors
before/after the12 create,17 open,19 append and20 repair boundaries check their
outcomes and surviving file content. All136 process exits at those same actual
syscall boundaries check surviving prefixes and released writer locks. Tests
also cover real partial writes followed by failure, a complete commit surviving
an uncertain write result, poison/reopen, short/EINTR/zero-progress transfers,
repeated interruption caps, explicit cleanup failure, and temporary/destination
basename collision. Ordinary file operations are real syscalls; successful fake
I/O or in-memory-only crash models are not used.

The initial Debug main test incorrectly counted account-controller allocation
outside its observation scope; only the test counter changed. The first build
caught a test helper name collision and a later build a test indentation error.
The first Release build rejected nullable arguments in the shared syscall
wrapper under O3 nonnull diagnostics. Explicit stage argument validation fixed
that build with all strict flags unchanged; an actual Release compile of the
preserved guarded draft passed before the final native matrix. Initial source,
interim source1 and the Release failing inputs/logs are preserved. Debug/Clang/
sanitizer interim57-test matrices also pass; final source2 supersedes them.

Audit binds180 actual executables,16 changed-unit objects,16 project archives,
four caches and392 compiler/link records. Strict C++23 warnings as errors, test
checks, production versus private-hook linkage and sanitizer/leak settings were
read from the actual builds. Accepted builds have no compiler diagnostics.
Every CTest terminal stdout was archived before inventory/next runs. All jobs
are terminal; raw logs and per-job JSON preserve both failed and accepted runs.

Receipts are under build/verification/o05-journal-file-: preimages-v1,
initial-v1,source-v1,release-negative-v1,inputs-v1/v2,all phase v5/v6 receipts,
matrix-scope-v1,matrix-audit-v1,root-review-v1,progress-v1,checkpoint-seal-v1 and
post-seal-audit-v1. Final docs-only source3 adds this record and the file guide.

Next integrate prepared native commit with durable input/decision ordering;
reconstruct and deterministically replay from the checkpoint through complete
physical/window markers, restore post-replay source/CSV counters and preserve
pending commands. Define durable checkpoint/generation selection before retiring
any committed log. Add audited stable output identity and O06 delivery, every
integrated persistence boundary and final whole/fresh acceptance. The codec and
file component do not implement those remaining protocols. Full Refactor.md goal
remains active:43 verified,3 in progress(A02/O05/O06),32 not started,78 total.
