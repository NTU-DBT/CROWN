# AntiGravity / coding-agent handoff

Updated 11 November 2026. The full [Refactor.md](../Refactor.md) objective is active.
Work is uncommitted at baseline `e369a623517723b3be3ea3e9806779f3c591e7f9`.
The [ledger](task_ledger.md) remains **54 verified, 1 in progress (A02),
23 not started; 78 total**. This is not release acceptance.

## Verified checkpoint: human inspection v6

The user requests individually authored usage specs, clear comments, accurate
paper/design references, direct main code, necessary exception boundaries and
minimal runtime overhead. Use current-model reviewers for substantial code and
Luna Max for bounded simple work; reduce Astra Max. No Astra run was added in v6.

V6 adds 389 contracts: 160 session, 123 candidate, 42 IR/lifecycle, 63 root
key/binding and one diagnostic test. There are now 1,678 scoped cards in 1,499
mapped blocks across 664 files, 152,939 lines and 16,947 structural blocks.
All 297 selected production blocks in the 12 assigned files have cards. Another
3,842 selected production blocks still lack individual cards; tests/tools and
the broader per-block review remain open. Structural maps are not semantic proof.

Root applied 116 focused comment edits. Trivial getters/equality/copy declarations
retain external specs without repetitive inline comments. Of 11 changed native
files, nine are comment-only. Three explicit source substitutions change only
candidate geometric capacity growth and finite/infeasible replay success wording.
One regression function checks finite, infeasible, invalid and resource-stopped
reports. No new runtime helper, state, catch/throw or coroutine-operation site.

Growth remains in the saved reserve stage before payload/seen/publication. It
gives amortized constant handle relocation, while a single reserve can allocate
and move the whole prefix. Owning public values/snapshot copies survive growth.
Spare capacity is outside logical content caps. Independent reviews checked
growth arithmetic/ownership/order and 105 root/IR cards; exact corrections cover
assignment teardown, scalar-width/result-construction costs, retained descriptor
accounts and export of existing validation without rerunning P02. Null lower
alone does not prove infeasibility. No measured speedup is claimed.

Fresh strict Debug and ASan/UBSan/leak builds pass on the same 1,101 stable inputs.
Each profile passes all nine selected checks in 73.00 s and 253.58 s. Both raw
LastTest.log files are archived. Separate fault cohorts per profile are P07
613 generator/17 key/2,369 provider; owned P06 3,194; legacy search/construction
3,638; independent legacy replay 1,236. Do not sum these as globally unique faults.
The actual maintained native inventory is 44 linked artifacts and 252 C++ objects.
All 33,349 spec links, current hashes and complete partitions pass. All 314
same-profile registrations/commands/properties and CMake/install/tools remain
unchanged. This is not a full 314-test or optimized Release execution.

Start with the [verification record](verification/human-inspection-v6-2026-11-11.md),
[inspection index](code_specs/README.md) and [primitive cards](code_specs/primitives.md).
Final native receipts are `inspection-v6-build-final-*-v1` and
`inspection-v6-ctest-final-*-v1`. Acceptance/source closure are
`build/verification/inspection-v6-acceptance-v1.json` and
`build/verification/inspection-v6-progress-v1.json`; frozen source is
`build/inspection-v6-source-v1`. All v6 recorded native jobs are terminal.
Never rebuild, rerun CTest or mutate sealed source/evidence; use new paths.

All 2,448 v5 paths are preserved under `inspection-v6-preimages-v1`; all 86 v5
artifacts and earlier seals remain intact. The raw packets are
`inspection-v6-{session,candidates,ir-types,root}-v1`; final integrated cards,
source audit, corrections and metadata are in `inspection-v6-integration-v1`.
Independent packets are `inspection-v6-growth-audit-v1` and
`inspection-v6-root-ir-audit-v1`. Build/verification paths are local.

## Next work

Read-only v7 lowering and selection reviews are being staged in
`inspection-v7-lowering-v1` and `inspection-v7-selection-v1`. They are outside
v6 acceptance. Recheck hashes, anchors, real costs and findings before integration,
preserve v6 before-images, and use fresh native/evidence directories.

W04 remains the next implementation card, separately from W05/W06. Read the
[W04 inventory](../build/verification/w04-inventory-v1/handoff.md): current
W01-W03 foundations do not supply SQL group descriptors, group state, exact AVG
result rules, NULL/global-empty behavior, aggregate events or SQL oracle coverage.
Implement the bounded semantic/type contract and direct group owner; do not add
a generic algebra/callback framework or mark bag/transaction/recovery work done
from arithmetic kernels alone. A02 licensing, later implementation/experiments
and external theorem/release gates remain open. Do not shrink the full goal to
inspection or mark it complete at this checkpoint.

The complete previous handoff is archived byte-for-byte in
[handoff-history-v5-2026-11-11.md](handoff-history-v5-2026-11-11.md); its linked
v4 history preserves the earlier implementation/evidence chain.
