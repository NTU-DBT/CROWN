# Guarded key-aware plans

`CROWN::keys` provides the cold, opt-in
`crown::planner::keys::specialize` compiler for genuine direct-CQ set plans.
It removes a parent occurrence whose matching row is guaranteed by an enforced
foreign key and enforced target UNIQUE key. The result retains the original
general plan, the smaller executable plan and the exact elimination/ID maps.
It uses the existing runtime; it adds no maintained owner or update hook.

```cpp
#include <crown/planner/keys.hpp>
#include <crown/runtime/physical.hpp>

auto choice = crown::planner::keys::specialize(general_plan);
auto owner = crown::runtime::PhysicalRuntime::initialize(
    choice.execution(), initial_database, runtime_options, build_options);
// choice.general() remains the independently executable comparison route.
// Existing physical set events, snapshots and cursors keep their normal API.
```

For a C05 selection, use the existing explicit compiler export
`PhysicalPlan::from_compiled(selection.plan())` as the input. This is a new cold
plan choice; it does not replace a live owner's plan or transfer its state.

## Exact admission and rule

The admitted family is the existing non-null, physical full-row set CQ interface.
Normalized SQL plans remain unchanged with `Reason::normalized_sql`; constant
operators remain unchanged with `Reason::constant_route`. Nullable SQL bags,
weighted replacements and aggregates retain their own general interfaces. This
compiler does not extend SQL parsing or silently turn bag results into sets.

For two distinct currently live occurrences `C` and `P`, a rule needs:

1. An **enforced** FK on `C`'s physical table referencing `P`'s table, plus an
   **enforced** UNIQUE constraint on exactly those target columns. Statistics,
   `key_hints`, untrusted constraints and observed current uniqueness do not count.
2. The same non-ignored typed term on each paired source/target key column.
   A term is the same variable ID or equal typed constant. Composite key order
   follows the FK's declared source/target pairing; UNIQUE column order may differ.
   Repeated key variables are permitted because the source has the same equalities.
   Two ignored fields do not prove an equality.
3. Every non-key parent field is ignored or a variable used exactly once in all
   currently live atoms and never in the head. These independent private variables
   add no filter. A non-key constant, repeated variable, head value or connection
   to another live occurrence prevents the rule.

For each matching source row, the real FK supplies a real target row; the target
key matches every key predicate and its remaining values supply the independent
private fields. Thus adding `P` cannot remove that source assignment. Conversely,
every original satisfying assignment already satisfies the remaining atoms.
The set result is unchanged, including projected, repeated and empty heads.
UNIQUE additionally records the genuine key premise; this is not a bag proof.

Rules apply sequentially in original occurrence order. A removed occurrence may
have witnessed an earlier rule, but its own removal needs a still-live distinct
witness. Equivalence therefore composes, and an FK cycle cannot erase its final
atom. Empty FK/UNIQUE keys are real constraints: an enforced empty FK guarantees
target existence when a source row exists, while UNIQUE([]) permits at most one
target row. The same rule works with that vacuous key pairing.

## Source state, identity and proof

The executable keeps the **complete original catalog**, including unused tables,
row schemas, enforced constraints, metadata status and table IDs. Only native
occurrences and unused private variables are removed. Their new IDs are compact;
`occurrences()` and `variables()` map each new ID back to the original ID.
`eliminations()` records original removed/witness IDs and both constraint indices.
Head order, aliases, repetitions and scalar types stay the same.

The existing [PhysicalRuntime](physical_runtime.md) still stores all source rows,
validates the complete after-state and publishes its ordinary physical sequence.
An update to a referenced-only table has no native occurrence route, but still
updates/checks source state. Deleting a referenced parent is rejected by the same
constraint owner; it cannot leave an orphan merely because its join was removed.
An alias of that same physical table can remain live and must still receive events.

The interface uses single physical set events. Changing a parent payload through
erase/insert is not an atomic replacement: with live children, removing the old
parent or inserting a second row with its key can reject. Whole-database startup
uses the existing validated initializer, including valid cyclic FK states.

After a nonempty rewrite, the two plans have distinct source identities. Reduced artifacts must not
be cached or imported under the original identity. `reduced_certificate()` is an
independently checked minimum-tree certificate for the original catalog paired
with **the reduced query only**. The executable's ordinary lowerer still reports
its normal checked-upper-bound profile. It is not a minimum-height certificate
for the unconstrained original CQ. The general plan and its evidence remain intact.

All borrowed accessors require a named owning `keys::Plan`; temporary borrows are
deleted. Copies/moves keep the source handle valid. New result vectors/control
storage are ordinary compiler memory; retained plan/layout handles preserve their
existing ownership. A receiving runtime freezes its selected executable metadata
and source state into its own original query account under the normal contract.

## Costs and refusal

`Limits.work` is one shared balance for selected guard checks and final mapping
steps. Scalar widths, compiler copies and allocation costs are additional. The
existing bounded tree producer/replay and lowering/identity limits remain separate;
the original physical options, backend and per-table limits are preserved.
No-match/unselected results perform no new tree search. Their classification and
original-ID maps still consume guard work, so a zero guard grant can refuse them.
Actual selected guard,
search and lowering counts are reported by `usage()`.

Compilation scans candidate occurrence pairs, their constraints and typed terms;
it retains original/reduced compiler metadata and proof/maps. This is cold work,
not a per-event optimizer. Native runtime state/routes for eliminated occurrences
are absent. Complete source storage and full reference constraint scans still cost
their real rows, comparisons and account-backed scratch. An empty native route
does not imply constant-time total updates or reduced source-state memory.

`key_work_limit` and `key_search_limit` report the corresponding resource refusal;
the existing lowerer's errors propagate unchanged. No partial optimized `Plan`
escapes. The caller's original immutable plan remains available, with no new
catch/retry framework or comparison runtime maintained in production.

## Paper and local engineering boundary

P5, Wang and Yi, *Maintaining Acyclic Foreign-Key Joins under Updates* (SIGMOD
2020), [author PDF](https://cse.hkust.edu.hk/~yike/sigmod20.pdf), defines composite
keys and FK joins in §§2.1–2.3. Its FK query graph is a DAG with one indegree-zero
root, and §2.4 uses expected constant-time hashing. Its selection discussion
explicitly matters: filtering the referenced table can remove the guaranteed
matching row. The guards above retain that distinction.

This implementation uses a separately stated local equivalence proof and the
existing ordered-container constraint owner. It does not implement P5's update
algorithm or claim its bound. Its broad catalog may contain cyclic FKs; the
sequential live-witness proof supplies this local rule's correctness. Automatic
default planning, wire formats and original minimum-height policies stay under
their existing contracts. [Refactor X02](../Refactor.md) and the
[source-bound inspection index](code_specs/README.md) separate those obligations.
