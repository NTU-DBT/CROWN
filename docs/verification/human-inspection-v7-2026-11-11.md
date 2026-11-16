# Human inspection v7: lowering, ranking and selection

The complete [Refactor.md](../../Refactor.md) objective remains active. This
packet adds scoped human-readable contracts and comments after the
[v6 checkpoint](human-inspection-v6-2026-11-11.md). It does not establish release
acceptance or complete repository semantics. Both scoped native profiles pass;
the independently reproduced C02/C05 regression remains open.

## Source and contracts

Root integrated 485 new seven-field contracts: lowering 115, selection 218 and
ranking 152. There are now 2,163 contracts in 1,893 mapped blocks, across 664
files, 153,203 lines and 17,048 structural blocks. All 382 selected production
blocks in the 18 assigned files have cards. Of these, some were already carded;
the remaining selected production gaps fall from 3,842 to 3,484. Broader test/tool
review remains open, and structural partitions are not individual semantic proof.

The [inspection index](../code_specs/README.md) and
[primitive cards](../code_specs/primitives.md) provide purpose, inputs/outputs,
invariants, ownership, failure, cost and narrow local/paper references. Source
hashes and unique anchors keep the stated scope reviewable. No primary-paper
claim is stretched to justify native allocators, cache commits, arithmetic
kernels or exact binding encoders.

There are 155 applied comment edits in 17 native files. Root selected 114 of
218 selection proposals, retaining external getter/value specs while keeping
inline comments on protocol, ownership, accounting and publication. One root
comment states the selection handle's copy-like move lifetime. Detailed ranking
comments number 12 and lowering comments 28. Exact C++ token comparison proves
all 17 files are comment/whitespace-only edits: no catch, throw, operation,
public-interface, runtime helper/state or maintained test change.

The selection accounting table now accurately describes bounded InlineDecimal
stack rendering. It preserves the conservative 41-unit work/payload charge and
additional encoded-byte costs; it no longer claims an allocating public formatter
is called.

## Reviewed cost and authority boundaries

Ranking and selection preserve original typed candidates/proofs. A winner is
best only within the retained snapshot, and full exact Catalog/Query/source/key
admission precedes scoring or cache reuse. Evidence is as-of; pure operations
do not establish actual-owner freshness, advance candidates or install a plan.

The ranking audit read all 152 cards and all 706 lines in its six files. Root
applied 82 field corrections across 46 cards and one comment correction into
new derived files, preserving raw material. These corrections distinguish
per-primitive UInt failure/ownership, unguarded noexcept evidence borrows,
metadata size debits from actual character scans/worklists, and native source
admission credits from rerun compiler passes. Fixed 512-bit arithmetic is inline;
only decimal/key output storage allocates. Source/identity DOM worklists and
account-backed component payloads retain their actual allocation costs.

Native replanning reuses admitted immutable source/identity/normalized metadata.
Stored producer work credits remain checked and aggregated, while new binding,
tree/report, physical digest, token and instruction construction still cost work.
Logical cells/payload/slot scores, actual account capacity and cooperative time
are distinct units. Plan/Evidence/Selection handle assignments may tear down
large old final-owned payloads; their constructors need only fixed handle work.

Selection cache preparation leaves live FIFO links/counters untouched. Complete
result/wrapper funding and the final deadline check precede the no-fail cache
commit. Retired links release later without recursive chain destruction. No
new exception abstraction or callback/algebra framework is introduced.

## Confirmed regression and task status

Review found a real existing defect beyond the comment-only change: a nonempty
contradiction can retain a positive-height structural candidate while native
replanning emits a constant-false operator with that nonempty tree. Its physical
artifact cannot replay. Root compiled a separate probe against sealed v6
libraries; the empty-body control succeeds. Read the
[regression record](constant-route-regression-2026-11-11.md).

C02 and C05 are therefore reopened. The ledger is **52 verified, three in
progress (A02, C02, C05), 23 not started; 78 total**. Passing selected checks
cannot establish that this counterexample is fixed. The coherent compiler,
selection binding, direct lowering and score-model correction is next. Original
body proof/height must remain separate from zero-height constant-operator
metadata; public lowering must continue rejecting a noncanonical supplied tree.

## Verification and preservation

The complete 2,450-path v6 source is preserved in
`build/verification/inspection-v7-preimages-v1`; all 92 predecessor evidence
artifacts matched before edits. Raw/derived review packets and corrections remain
separate. Strict Debug and ASan/UBSan/leak builds pass on the same 1,101 stable
maintained code inputs. Each profile passes all 13 focused tests, in 84.12 seconds
and 313.99 seconds. Both complete raw `LastTest.log` files are archived before
further CTest enumeration. The checks are physical lowering/API, native program
construction/replanning, ranking binding/integer/public/account retention and
selection public/binding/cache/resources/account retention.

Separate per-profile fault cohorts are native construction 697, native replan
1,816, native admission copies 2,876, ranking memory 4,798 and selection memory
4,779. The recorded counts agree across profiles; no cross-cohort uniqueness
or total fault-count claim follows. The integer reference checks 54 values and
2,916 ordered pairs, and the selected public/resource/binding tests retain their
independent model/byte/counter controls. These selected fixtures do not cover
the newly confirmed nonempty constant-false regression.

The native inventory hashes 54 actual maintained linked artifacts and 258 C++
objects; each actual translation unit carries strict C++23 warnings-as-errors
flags, with sanitizers in the sanitizer profile. Vendored C is outside that C++
inventory. The documentation checker passes 35,758 local links, current hashes
and complete partitions. Exact same-profile comparison preserves all 314 CTest
registrations/commands/properties, CMake/install declarations, documentation tools
and applicability of the unchanged eight anchor/ten checker-negative controls.
No runtime speedup, full 314-test execution or optimized Release matrix is claimed.

Final receipts are `inspection-v7-build-final-*-v1`,
`inspection-v7-ctest-final-*-v1`, `inspection-v7-source-edit-audit-v1`,
`inspection-v7-specs-check-v1` and `inspection-v7-metadata-final-v1` under
`build/verification`. Acceptance/source closure are
`inspection-v7-acceptance-v1.json` and `inspection-v7-progress-v1.json`; frozen
source is `build/inspection-v7-source-v1`. The previous handoff is preserved
byte-for-byte in [handoff-history-v6-2026-11-11.md](../handoff-history-v6-2026-11-11.md).
Known C02/C05 regression work remains open after this scoped inspection seal.
W04 remains the next feature implementation, with W05/W06 distinct; later
experiments, licensing and external theorem/release gates are also still open.
