# S05 compact maintained physical sources (in progress)

The full Refactor.md objective remains active: 41 verified, three in progress
(A02/S05/O06), 34 not started, 78 total. S05 is not complete. Root implemented,
reviewed and executed this cohort. A Luna Max agent supplied only a bounded
read-only API inventory and follow-up. No Astra agent was used.

## Actual adoption and remaining boundary

PhysicalRuntime now uses accounted reference/indexed source tables, compact
source pins/owning exports and compact derivation dictionary keys. Actual arrays,
map nodes, pending controls and undo arrays use the same existing query account.
Old/new rebuild state retains that account. Physical source layout metadata is
frozen under the account; earlier source table/Row storage is not retained.

Legacy support consumes a private nonowning diagnostic view of the canonical
finite work balance; compact sources use its fixed canonical view. This creates
no additional remaining budget, copied allowance or refill. Source count undo
preserves compatible allocators and original key/node ownership. Public native
failures format only after state unwinds. Original public owner sequences and
strict default report bytes remain unchanged.

The [contract](../memory_accounts.md) explicitly preserves the open work:
PhysicalPlan/source metadata descriptors, a transient legacy source adapter,
support values/tables, delta/session collections, imported queues, output/capture
ownership, operator reconciliation and full native acceptance. Standard export
allocations are explicit and remain outside the account. Map node lifetime
classification scans the account ledger; no uniform runtime speed/delay is claimed.

## Current verification

Debug passes 32 selected existing runtime/storage/initialization/delta/session/
capture/report tests (168.28 seconds). An additional persistent physical-fault
sweep was then added to runtime_memory; it passed separately (0.39 seconds).
No native implementation source changed between those runs, only that added test.
Release and Clang pass the final 32 selected tests (26.63 and 128.62 seconds).
GCC ASan+UBSan/leaks also passes the final 32 selected tests (694.36 seconds).
Debug CLI builds and passes both physical/support fixture tests (2.90 seconds).
These use existing build trees incrementally, not a fresh full native/compiler
audit. No new gate or card is marked verified by these scoped tests.

The actual fixture/testing runtime preserves 8,194 binary payload bytes in an
ignored physical column. Routed source peaks are 26,608 reference / 27,604 indexed
bytes in the observed modes. Exact limits commit; one byte less preserves the
previous epoch and allows a smaller payload retry. Source exports and pins keep
the same account; a pin survives facade destruction; final release leaves only
the observed controller. Scalar view comparisons allocate nothing and export
round trips preserve all five scalar types, including 38-digit decimals.

The integrated physical allocation sweep fails 132 reference / 145 indexed
positions with persistent denial, preserving canonical previous state/stable
handles and successful retry. Earlier support sweeps remain 116/127 positions.
The indexed support fixture peak grows from 10,757 to 10,805 bytes because its
lease now contains the actual nonowning diagnostic view; reference stays 10,383.
These are measured requested bytes with testing controls, not full query or
portable production peaks. Remaining legacy allocations are explicitly excluded.

## Preserved inputs and continuation

Preimages v1–v4 and raw logs under `build/verification/s05-compact-source-*`
preserve all source attempts. The first build compiled the actual runtime and
then failed on an old Row-only preview serializer. Four test/export boundaries
and the old source pin vector were updated explicitly. Existing assertions,
original executed checkers and pinned report baselines were not weakened.
Root also preserved fixed reference errors at the public source boundary and
added a foreign-handle check for both backends.

All jobs are closed. `s05-compact-source-matrix-v1.json` pins the exact selected
names and preserved logs, explicitly recording Debug's test-only supplement.
The source record has 888 maintained files excluding mutable handoff. Root review,
current-source audit and scoped checkpoint v1 bind the results and reviewed final
documentation. `s05-compact-source-jobs-v1.json` keeps terminal statuses; next-plan
v8 continues the full goal. Original checkers, raw failures and baselines remain.
This is post-build/live-source verification, not frozen-source execution.

The predecessor runtime-owner checkpoint is historical; do not evaluate its INPUT
hashes against current code. Next, freeze the retained runtime program, preserve
existing frozen token aliases, port actual support storage/values, remove the
legacy source adapter and descriptor boundary, then finish remaining ownership,
operator reconciliation and complete native S05 gates. No isolated unused runtime
helper is an acceptable substitute for that actual adoption.
