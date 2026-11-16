# O06 sink-aware native reconstruction — 10 November 2026

This goal turn is progress. Root implemented and reviewed the production changes.
Luna Max supplied bounded read-only inventory and review; no Astra was used.
The full Refactor.md goal remains active, uncommitted on baseline
`e369a623517723b3be3ea3e9806779f3c591e7f9`. Ledger:43 verified,
3 in progress(A02/O05/O06),32 not started,78 total.

## Accepted component

`restore_journal_with_local_sink` and `restore_generation_with_local_sink` open
the actual durable sink in the same receiving query account before native replay.
Complete accepted physical epochs, including empty closures, must match actual
canonical native output; metadata-only steps create no extra epoch. The new
duplicate-only `File::verify_epoch` cannot append a missing epoch and permits
comparison through a valid incomplete suffix. Append/receipt remain blocked
until explicit compatible repair.

Accepted output is released after comparison instead of entering the recovery
backlog. Only missing output consumes replay row/byte allowances. Fully accepted
replay works with zero backlog rows/bytes, while native atomic spool, row views,
canonical buffers/index and all transient storage remain under the original
receiving heap. Copied cumulative source/decode/file and sink delivery-work
limits remain enforced; no recovery-specific refill is added. The sink cannot
be ahead of validated native replay or behind the checkpoint. Caller-frontier
suppression rejects. Whole WAL/native/source/pending/EOF/stamp/sync/seek checks
precede tail repair or owner/output exposure. No new output is written during
reconstruction. Bare/two-step recovery remains available with its prior caps.

## Native evidence

Frozen source1 has1087 paths, preserving all1084 predecessor paths plus three
new test/support paths. Five existing production/build paths changed: CMake,
local_sink.hpp,session.hpp,local_sink.cpp,session.cpp. Predecessor tests,fixtures,
caps,timeouts and accepted flag records are unchanged. Root's bounded production
review and Luna's read-only review found no concrete defect. Focused Debug4/4
then new3/3 runs and their initial missing-target configure correction are kept.

Selected72/72 tests pass all four modes: Debug 115.85s, Release 131.98s, Clang18 147.79s, ASan+UBSan/leaks 166.98s.
259 names retain all256 predecessors. This is scoped component regression
acceptance, not whole259/fresh integrated O04–O06 acceptance.

Each mode verifies48 typed cases across two backends, six query kinds and four
accepted prefixes, using exact missing-row caps and zero bytes for an empty
backlog. Native state/source, complete canonical output and the next update match
independent semantics.32 eight-format stream/backend/pending cases preserve
decoder/header/source/EOF behavior;16 partial-window/backend/FIFO cases preserve
metadata and physical boundaries. Generation rotation preserves the original
sink origin and current output generation. Checksummed semantic mismatch, sink
ahead of native WAL, corrupt complete records, caller frontiers, wrong identity,
disabled repair, source/heap/output/work caps all reject without file mutation
or leaked ownership. Source seeking failure preserves both incomplete tails;
fully validated retry repairs them.

All1161 receiving allocation failures preserve files and release locks; counted
allocations equal the receiving account, with exact/one-under heap checks.
Actual sink validation/verification/repair has22 clean and27 torn boundaries;
WAL recovery has24 clean and29 torn boundaries. All204 before/after errors and
204 process exits reopen the real factory, verify native state/source/outputs,
deduplication and the next update. Short3-byte I/O and repeated EINTR retain
finite copied quotas. Process exits are not power-loss simulation.

The separate strict public control links production archives only, excluding
reference/runtime_testing. The old two-step path rejects a zero backlog allowance
on the same log; the new factory accepts it with exact7 delivery-work units,
rejects6, preserves all bytes and does not republish accepted epochs.
`verify_epoch` rejects a missing epoch without writing it. No failing production
control/fix is claimed for this component.

Audit pins220 executables,32 relevant unit objects,16 archives/four caches and472
compiler/link records plus the production control. All18 final configure/build/
test/inventory/control receipt jobs are terminal and stdout is archived. Strict
C++23/warnings-as-errors, new-test assertions and sanitizer/leak settings pass;
accepted builds have zero diagnostics. No build overlaps CTest in its directory.

## Handoff

Receipt prefix `build/verification/o06-sink-restore-native-` contains preserved
preimages-v1,focused and final jobs/control source+commands+ELF,inputs-v1,
matrix-scope-v1,matrix-audit-v1,root-review-v1,progress-v1,jobs-v1,checkpoint-seal-v1
and independent post-seal-audit-v1. Final docs-only source2 adds this record.
Verify the final seal/readback before further edits. The [API](../local-sink.md)
and [handoff](../handoff.md) describe the supported path and next work.

Next integrate crash-safe history-retirement intent/continuation under the
generation lock with actual verified sink/checkpoint/root coverage. Old selected
pairs remain retained. Cover every unlink/sync/root/intent boundary, then run
whole/fresh O04–O06 acceptance. O08 CLI, A02 licensing and the other Refactor
cards/release gates remain open. Local delivery proves no arbitrary external
callback side effects.
