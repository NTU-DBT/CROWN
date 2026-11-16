# S05 native constraint and rebuild scratch — 9 November 2026

Status: **in progress**. The complete78-card Refactor.md goal remains active at
41 verified /3 in progress /34 not started. Root implemented this checkpoint;
one existing Luna Max agent completed a read-only semantic/test census. No Astra
was used. Root should handle most work, reserving Astra Max for occasional tasks.
Artifacts live in `build/verification/s05-validation-scratch-*`.

## Actual ownership and behavior

Physical input shape/type/decimal validation borrows scalar views of already
admitted immutable catalog metadata. Decimal checks keep their scalar owner alive
and avoid ordinary formatting strings. Native after-state snapshots include all
source tables, unused relations and self references. Snapshot capacity, projected
field buffers, ordered unique/FK nodes and owned compact key payloads consume the
original account; child FK probes borrow projected fields without an owning Row.

Rows precede constraints in validation order. Declaration order, exact reference
errors, all five scalar types, binary strings, fixed decimal domains, untrusted
keys, empty unique/FK keys and complete cyclic initialization retain their
semantics. The standalone public catalog/reference checker is unchanged.

Initialization borrows the external Database and imports compact rows/native
seeds. Rebuild uses native original-account snapshots sorted in full-row order
for deterministic direct and insertion-replay construction on either backend.
Old owner, snapshot and new owner share the existing finite allowance. Original
cumulative work precharges precede copying. Failure releases partial scratch and
replacement state, preserves the prior epoch and permits a same-input retry.

## Verification scopes

Source5 freezes926 paths and is the tested C++ implementation. Final source6 adds
only current documentation, for927 paths. Full Debug builds every target; the
other strict modes build the selected20 targets. All four current builds have
zero compiler warnings/errors. Completed runtime checks are:

| Configuration | Observed scope |
| --- | --- |
| GCC Debug |211/211 full registered tests, 882.29s |
| GCC Release |20/20 selected checks, 16.20s |
| Clang18 Debug |20/20 selected checks, 100.24s |
| ASan+UBSan/leaks |20/20 selected checks, 528.38s |

Detailed stdout for all four completed scopes is preserved. No registration
enumeration overlapped CTest. All25 recorded commands are closed;
progress-v2 binds source, raw failures, binaries, audited scope and handoff.
Selected checks cover native ownership, constraints, cyclic/full snapshot
initialization, physical/Delta/session failure recovery, work budgets and reports.
These do not constitute complete compiler/sanitizer/fresh-source acceptance.

The new actual-runtime test reconciles upstream allocation counts with real
account allocations, including 38-digit decimals and long binary keys. Debug
fixture exact/one-under validator peaks are160549 reference /161329 indexed;
constrained update peaks are657133 /659715; replay rebuild overlap peaks are
752779 /757501. Persistent update failures cover44 /48 positions and
rebuild failures cover64 /68. These are fixture measurements rather than
universal production peaks. Denial preserves prior state; retry uses the same
allowance and final release leaves only the account controller.

Source4 GCC Release exposed a real dangling Decimal-parts view, and ASan
reproduced stack-use-after-scope. Source5 retains the ScalarView throughout the
check. Both failures and the identified obsolete sanitizer-build cancellation
remain immutable. The earlier new-test failure counted caller update/Row
construction; source3 moves that caller setup outside engine allocation/fault
measurement. All exact assertions remain. Existing tests, public reference
checks, frozen schemas/CLI verifiers, old maps and executed helpers are unchanged.

## Remaining S05 work

Nested input/options/progress, transport queues/readers, window nodes/rows/
commands/prepared controls, capture/report/diagnostic/asynchronous graphs,
authentic operator record/byte reconciliation and complete overflow/churn/native
matrices remain open. Public diagnostic exports are distinct from internal
checker scratch. The7-file221-candidate next-owner inventory is a reviewed
candidate list; it includes funded aliases and external DTOs and is not exhaustive.
Whole-query memory-budget completion and S05 acceptance remain **false**. See
[handoff](../handoff.md), [memory contract](../memory_accounts.md) and
[ledger](../task_ledger.md).
