# CROWN continuation handoff

The full Refactor goal remains active: **59 verified / 1 in progress (A02) /
18 not started**, 78 total. V02 is now verified within the documented conditional
source arguments. V01 and bounded V33 W06 remain verified. A02 still blocks
C04/B01; R2 aggregate history retirement, experiments and release remain open.
The previous handoff is preserved exactly in [V46 history](handoff-history-v46-2026-11-14.md).

## Inspect and continue

Start with the [inspection guide](code_review.md), [usage cards](code_specs/README.md),
[primitive costs](code_specs/primitives.md), [error-handling dispositions](code_specs/error_handling.md),
[27-family matrix](independent_review.md) and [V47 acceptance](verification/v02-public-guarantees-2026-11-14.md).
The map covers 751 files / 172,040 lines / 19,412 blocks; 16,796 authored contracts
cover 14,380 blocks. V47 adds 79 contracts, amends four older semantic fields and
rebinds 12 source hashes after one tooling fix. Selected callable/type/substantive
inline-cluster gaps are zero. The remaining 5,032 structural blocks / 660 files /
13,973 lines include 2,884 blank blocks. Keep structural mapping distinct from
individual semantic certification.

Root receives 23 evidence folders, including inventory/draft reviews, 22 authored
independently and one root digest argument. Exact full/partial/inherited scopes
are in proof-receiving-v1.json. The closure audit supplies six actual leaf/caller
arguments; C07 has a separate positive finite-workflow argument. Root's
dependency-dispositions-v1.json records acceptance and external premises.

## Changes and checks

Only two recorder inputs differ from V46: tests/workflow/generate_fixtures.py
fixes ROOT from OUT.parents[2] to OUT.parents[1], and tests/workflow/manifest.json
refreshes source/specification hashes. The isolated regression reproduces the
old partial-write failure and passes five cases / 34 events after the fix.
All 21 fixture payload/README files, all 355 production paths and all C++/CMake
bytes are unchanged. No engine handler, guard, field or instrumentation is added.

Six terminal digest compile/run commands precede the tool fix. SDK and sanitizer
profiles each pass 1,294 independent byte vectors; the ABI and primary-word checks
pass. The argument is conditional on the recorded unsigned-word expression ABI.
After the tool/manifest successor, Debug workflow CTest passes 1/1 in 12.37 seconds
with all 1,196 inputs stable during execution. V46's selected 33/33 Debug and
33/33 ASan/UBSan/leak checks retain their original cohort. No full current suite,
new Clang/Release/install matrix or controlled performance result is claimed.
No native job remains live. The final generated-spec checker passes 126,747
local references; the separate 102-guide audit checks local links/fragments.

## Frozen evidence

Root packet: build/verification/v02-public-guarantee-closure-v1.
Seal: build/verification/human-inspection-v47-progress-v1.json.
Frozen source: build/verification/human-inspection-v47-source-v1.
Postcheck: build/verification/human-inspection-v47-postseal-check-v1.json.
The postcheck records the raw seal SHA. Parent V46 raw SHA is
112dd4e92fade71d0df7768442017c0cfd25b6c93750f088d03084d9321f0606.
HEAD remains e369a623517723b3be3ea3e9806779f3c591e7f9.

Keep completed packets, seals, snapshots and private SDK/builds immutable.
Preserved pre-structural registry/coverage and received guide postimages resolve
earlier reviewer hashes. Main build/w05-debug, build/w05-sanitizer and
build/inspection-build-scope-off-v1 are reusable; their mutable binary bytes
are not frozen evidence. The private V01 Release build and relocated 229-file
SDK remain immutable. The .git directory is read-only; no stage/reset/commit.

Continue remaining ledger cards by dependency; the project-distribution license
needs the user's choice. Existing B01/B05 drafts remain unaccepted. Keep code
direct: validate before mutation, use the owning prepared token for inverse and
rollback, preserve necessary cleanup/uncertain-I/O boundaries, and forward the
existing account/operation lease. Avoid speculative guards, retained fields and
instrumentation; document actual preparation, hidden-scan and teardown costs.
