# CROWN continuation handoff

The full Refactor.md goal remains active: **58 verified /2 in progress (A02,
V02) /18 not started**, 78 total. V01 and bounded V33 W06 remain verified.
A02 still blocks C04/B01. V02, R2 history retirement, experiments and release
remain open. The exact previous handoff is [V45 history](handoff-history-v45-2026-11-14.md).

## Current review and source boundary

Use the [current inspection guide](code_review.md),
[source-to-invariant matrix](independent_review.md),
[block specifications](code_specs/README.md) and
[error-handling dispositions](code_specs/error_handling.md).
The current guide has been reorganized; its previous chronology is preserved
[byte-for-byte](code_review-history-v45-2026-11-14.md). Current guides now link
implemented W06 runtime, Session, input and rebuild APIs, distinguish recovery
repair branches, and point to the exact full tree definitions and actual fast paths.

The current [V46 receiving report](verification/v02-independent-review-2026-11-14.md)
records documentation and independent-review progress. Receiving packet:
build/verification/v02-independent-review-v1; global seal:
build/verification/human-inspection-v46-progress-v1.json; frozen source:
build/verification/human-inspection-v46-source-v1; postcheck:
build/verification/human-inspection-v46-postseal-check-v1.json.
The global postcheck contains the raw seal SHA. Reviews read frozen V45 native
code, which remains byte-identical in V46. V45 is the immutable parent boundary.

All 1,196 native inputs remain V45 bytes. No executable token, catch, state
field, guard or update-path instrumentation has changed in this review.
Coverage remains 751 files /172,040 lines /19,412 blocks and 16,717 contracts in
14,301 blocks. Selected callable/type/substantive inline-cluster gaps remain
zero. The 5,111 structural-only blocks /670 files /15,137 lines are unchanged;
they are mapped, not individually certified semantic contracts.

## Completed native work

All 33 selected tests pass per GCC Debug (1322.71s) and
ASan/UBSan/leak profile (5472.43s). Both selected builds pass;
four terminal recorder receipts show no changed inputs. The exact test/target
map and both 348-test registration snapshots are in the receiving packet.
Post-run native-debug-after-v1/evidence.json and native-san-after-v1/evidence.json
retain selected compiler/link commands, assertions/sanitizer configuration,
cache/CTest/log copies and object/archive/executable fingerprints. Their reusable
build-tree binary bytes are not preserved immutable. No native command remains
active. No whole-current-suite or new Clang/Release/install matrix is claimed;
timings are diagnostic, with no controlled performance comparison.

Main build/w05-debug, build/w05-sanitizer and
build/inspection-build-scope-off-v1 are reusable.
Private V01 Release, all completed SDKs/builds, prior review packets and frozen
snapshots remain immutable. .git is read-only; do not stage/reset/commit.
Use sandbox_permissions=require_escalated for exec_command: the default launcher
is broken. Use PYTHONDONTWRITEBYTECODE=1 for custom imports, especially sealed
helpers. No auto-review rejection has occurred.

## Next receiving obligations

All native commands are terminal and the sixteen proof packets have been
received. Revalidate the V46 postcheck/source pins before a new edit. Continue
the catalogue-wide public guarantee audit, including R1 generation_retirement.cpp
and its deletion/receipt authority; then close the cross-packet dependency graph
before marking V02 verified. Existing O08/bounded component acceptance remains
intact, but is not itself that complete mathematical/semantic inventory.

Separate reviewers have supplied planner, projected-delta, support/physical,
weighted, SQL/aggregate, storage, memory-primitive/runtime-funding and recovery
arguments. Root has received and corrected their explicit scope issues.
Planner-funding, descriptor-admission and source/checkpoint/window
receiving packets are complete. The proof receiving receipt validates 16 packets,
533 scoped source pins and 350 distinct paths; these are not all full-file reads. Do not equate a report's conditional acceptance
with all V02: reconcile every internal dependency in the guarantee matrix first.
Finite models, source comments and fault sweeps do not replace general arguments.

Preserve the original weighted model as an algebraic over-approximation: one
shape violates Above. The support packet adds a valid nested generalized model
with 59,049 states /118,098 before/after checks. R06's separate policy-cap audit
was investigated without a reachable counterexample; do not add speculative
checks. D05 direct-node classification differs from the documented std::map
interior-pointer bridge; retain real preparation/teardown costs.

Continue the remaining Refactor gates after receiving this progress. Licensing,
legacy comparisons, benchmark drafts and R1/R2 release retain their ledger status. A new supported query
still follows the [SQL-plus-fixtures workflow](development.md); use the
[quickstart](quickstart.md), [guarantees](guarantees.md) and
[troubleshooting guide](troubleshooting.md).
