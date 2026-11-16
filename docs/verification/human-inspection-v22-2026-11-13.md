# Inspectable genuine SQL aggregate transactions

The source maps now contain **12,412 source-pinned contracts in 10,054 blocks**
across 706 maintained code files / 164,132 lines / 18,430 mapped blocks. Every
inventoried line belongs to an inspection block. All **5,655 selected production
scopes** and selected CMake, example and tool scopes have authored contracts.
Remaining selected manual gaps are **3,386 test scopes**. Structural mapping is
not an individual usage specification or a universal correctness/execution proof.
Start with the [source index](../code_specs/README.md) and
[primitive cards](../code_specs/primitives.md).

This adds 465 contracts after [v21](human-inspection-v21-2026-11-12.md): 312 for
context/explain, lifecycle and session tests, plus 153 for the composed runtime,
shared helper, authentic metadata imports and independent SQL oracle. The
review reconciles 1,704 exact predecessor records: 1,664 hash-only, 10 semantic,
27 helper reanchors and three contextual CMake anchor updates. Existing root
CMake commands retain their bodies; 23 commands are added, and the install target
list gains the runtime. Offline roles
add six exact-path strings without changing function/class ASTs.

The final selected-block inventory exposes two missing shared-helper callable
cards after the first merge: grouping-key projection and argument lookup.
Root supplies their actual borrowing, bounds, failure and cost contracts. A
fresh stable regeneration/check replaces the earlier pre-completion check as
final evidence. No executable code changes are needed to close those gaps.

The [runtime contract](../sql_aggregate_runtime.md) explains one genuine physical
source/native token, touched group-only state, exact shared arithmetic, full-key
output, static bootstrap and account/lifetime boundaries. It adds no production
catch, joined-row ledger or second undo system. Captured native facts are released
before returning group output; touched-group vector capacity can remain even when
equal results suppress every event. These costs are explicit, not assigned a
Boolean-update or arbitrary aggregate-delay theorem.

The [executed verification](w06-sql-aggregate-runtime-2026-11-13.md) records strict
Debug **24/24, 129.34s** and full ASan/UBSan/leaks **24/24, 293.94s**; complete
test-disabled Release; relocated 220-file strict C++23 SDK; exact old/new Release
observations for five ordinary W04 cases; and resource/ownership controls. Each
maintained oracle profile compares 99 cases across both backends, 3,436 atomic
epochs and 3,634 snapshots, including full hidden keys and exact AVG scales 0..18.
Private PostgreSQL and DuckDB receiving comparisons are separately attributed.
All 328 old test commands/properties remain, plus two new tests: 330 registered.
Execution of all 330 and a Clang gate remain open.

Comment corrections narrow the retained-report lifetime claim to its lambda-local
runtime facade. Lifecycle/session diagnostic corrections state the actual ordinary
new fault seam and remove a claim that an unguarded drain was guarded. Conditions,
calls, assertion flow and helper identifiers stay unchanged. Intentional string
literal edits are executable-token changes; only non-literal token identity is
claimed. Root refines nine cards to distinguish directly defined replacement
forms from unasserted indirect library delegation. Original review packets and
source preimages remain immutable.

Root evidence: `build/verification/w06-sql-aggregate-runtime-implementation-v1`.
All 48 recorder jobs are terminal: 43 successes and five preserved fixture/setup
failures, with no in-command source drift. Current 1,142-input phases preserve
the two later wording-only test differences. Seal:
`build/verification/human-inspection-v22-progress-v1.json`; frozen source:
`build/verification/human-inspection-v22-source-v1`. Main native builds remain
active; protected private builds, SDKs, predecessor sources and evidence must
not be edited or rebuilt.

W06 remains in progress. A separate sealed assessment specifies the missing
bounded authoritative physical-source image, genuine cold sequence-aware rebuild,
versioned WAL/Commit/Reject rules, independent W/I/C/D frontiers, nullable group
sink/checkpoint and operational CLI. That assessment is not implemented durable
recovery. Varying-int32 column admission remains open. Full ledger: 56 verified /
two in progress / 20 not started. Continue from the [handoff](../handoff.md).
