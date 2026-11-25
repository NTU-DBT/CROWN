# Flat executors

> Superseded for set queries by the keyed core (`docs/keyed_core.md`), which
> keeps typed tuples, a unified key type, tuple results, undo-log transactions
> and configurable GC under the public `DeltaRuntime` API. `FlatCyclicRuntime`
> and `FlatCountRuntime` remain experimental until phase E ports the cyclic and
> aggregate runtimes.

`CROWN::flat` (library `crown_flat`) supplies three lean, single-writer
executors for the same queries as the reference runtimes, built for raw
throughput rather than for the reference contracts. Include
`crown/runtime/flat.hpp`, `flat_cyclic.hpp` or `flat_count.hpp`.

| Executor | Input | Computes | Reference counterpart |
| --- | --- | --- | --- |
| `FlatRuntime` | `CompiledProgram` (free-connex set program) | exact-set answer, signed deltas, snapshots | `DeltaRuntime` |
| `FlatCyclicRuntime` | `Catalog` + `Query` (any CQ, including cyclic) | exact-set answer, added/removed answers, snapshots | `fallback::Runtime` |
| `FlatCountRuntime` | `CompiledProgram` (free-connex CQ) | bag `COUNT(*)` per head tuple, per-group before/after | `SqlAggregateRuntime` (`COUNT(*)`, group columns) |

## What is the same

`FlatRuntime` executes the compiled program unchanged: the free-connex tree,
generalized nodes, C* ranks, separators, input adapters (projections, repeated
columns, constants and simple column/literal comparisons) and the enumeration
program. The maintenance algorithm is the support algorithm of
[support invariants](support_invariants.md):

- per-record child-presence bits and derivation counts;
- survivor transitions;
- parent-support counts;
- visible (E) counts.

Delta enumeration follows the route algorithm of the
[delta transition spec](delta_transition_spec.md):

- Changed E keys come from true zero crossings, consolidated per route.
- A changed key is enumerated only when it is globally live (L on the target side).
- Every completion is enumerated with all of `X_i` bound to the key.
- An assignment is owned by its lowest-rank changed factor. Earlier-rank changed
  factors are pruned during enumeration rather than rejected afterwards.
- An insertion is enumerated in the after context.
- An erasure is enumerated in the before context: E removals are deferred until
  the route's enumeration finishes, and L is still `L^0`.
- L is maintained incrementally. Live separator counts sit on each C* child
  edge, and liveness flips cascade down the parent→child buckets.

Duplicate inserts and absent erases are no-ops. Base tables with several
occurrences telescope route by route. Output rows use the SQL result view
(reordered or repeated core columns, constants) when the program came from SQL.

`FlatCyclicRuntime` is the [fallback](fallback.md) algorithm. The connected
prefix P covers the head. The residual components become views counting
completions per key, and each answer carries the support count of P-assignments
whose view keys are all present. The self-join delta rule is the same.

`FlatCountRuntime` replaces presence by weights on the same tree. Each record
caches one child sum per slot. A record t has `full(t) = m(t) · Π_c S_c`, which
feeds its parent sum, and `local(t) = m(t) · Π_{c ∉ C*} S_c`, which feeds the
visible weight `W_v(e)`. The count of a head tuple a is `Π_{v ∈ C*} W_v(a[X_v])`.
A route changes weights monotonically, so each changed group is enumerated
exactly once, by its lowest-rank changed factor. Its before count uses the
weights saved at the route's first touch.

## What is different

The storage is the F-IVM/DynaGox layout:

- Every value is one 64-bit word. Strings are interned in an append-only
  dictionary; Boolean values become 0/1.
- Every relation is an open-addressing hash table over pooled, stable entry ids.
  Each separator bucket is an intrusive doubly-linked list through the entries.
- Updates mutate in place, and output goes to a C callback (`FlatSink`,
  `FlatCountSink`) without per-row allocation.

The flat executors deliberately omit everything the reference runtimes add for
their contracts:

- memory accounts and limits;
- work, row and spool grants;
- epoch journals, pending epochs and rollback;
- exception atomicity;
- observation, statistics capture, checkpoints and recovery;
- re-optimization.

An exception, such as an unsupported value or a count above the int64 range,
leaves an executor unusable.

`FlatRuntime::unsupported(program)` names the first feature outside this scope:

- constant routes;
- Date or Decimal columns;
- enforced constraints;
- computed SQL inputs, or predicates other than column/literal comparisons
  (string comparisons may only be `=` or `<>`);
- more than 64 nodes or children;
- a scope wider than 32 variables.

`FlatCountRuntime` takes signed multiplicity changes (bag semantics, no
deduplication). Mapping SQL source rows to core occurrence rows is up to the
caller, as `benchmarks/paper_replay/native_replay_aggregate.cpp` does.

## Verification

Three differential tests:

- `tests/unit/flat_runtime_test.cpp` checks `FlatRuntime` against `DeltaRuntime`.
  It uses random insert/erase streams over 18 query shapes, with duplicate inserts
  and absent erases. Shapes include paths, stars, generalized roots, string
  columns, self-joins, constants, repeated columns and comparisons. In delta mode
  the signed rows of every event must be identical; snapshots are compared
  periodically.
- `tests/unit/flat_cyclic_test.cpp` checks `FlatCyclicRuntime` against
  `fallback::Runtime` on triangles, a 4-cycle, the dumbbell, self-joins,
  constant/ignored and repeated terms.
- `tests/unit/flat_count_test.cpp` checks `FlatCountRuntime` against a
  brute-force bag join. It compares the net before/after count of every changed
  group per event, and full snapshots.

The paper workloads are checked end to end by
`benchmarks/paper_replay/verify_flat.py`. Both engines replay the same stream
prefix, or a sliding-window rewrite of it in which deletions start early, in
verify mode. The captures are compared block by block: rows are sorted per
relation update, and per snapshot.

## Paper harnesses

The four paper replay harnesses use the flat executors when `CROWN_ENGINE=flat`
is set. They report `"engine":"flat"` and otherwise keep the same input
decoding, routing, markers, output counting and capture format. For deltas,
`apply_ns` includes enumeration to the counting sink.
