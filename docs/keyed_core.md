# Keyed execution core (design and plan)

Status (23 November 2026): phases A–E are implemented.
- `DeltaRuntime` (and therefore `QuerySession`, the CLI and the paper
  harnesses) executes free-connex set queries on the keyed core by default.
- `fallback::Runtime` (arbitrary, including cyclic, CQs) runs its
  support-count algorithm on the keyed cyclic engine
  (`include/crown/runtime/keyed_cyclic.hpp`).
- `WeightedRuntime`, and with it `SqlRowsRuntime` and `SqlAggregateRuntime`,
  runs on the keyed engine in bag mode (`EngineOptions::bag`).
- Phase F is open: the experimental `Flat*` executors (`docs/flat_runtime.md`)
  are superseded and are removed together with the `CROWN_ENGINE` harness
  switch.

## Principles

1. **Relations keep their own width.** A stored tuple keeps its typed values:
   int64, string, Boolean, date or decimal, at any arity.
2. **Joins happen on keys, and keys have one unified type.** CROWN joins only on
   separator/key attributes. Every additional index has fixed-width entries:
   - child support (P);
   - the reverse child buckets;
   - visible keys (E) and their enumeration buckets;
   - live separator counts (L);
   - source derivation counts.

   Each entry holds a `storage::keyed::Key`: a 64-bit hash plus either an
   inline value (single int64 or Boolean field) or a pointer to the key's
   canonical interned record in its `KeyDomain`. Domains are per variable set,
   so the parent and child sides of a separator share keys. A key computed once
   (for example a record's child keys, stored in the record entry) is reused for
   every later probe, update and deletion without projecting tuples again.
3. **Every structure is maintainable.** Records are interned, reference counted
   and removed. Maps erase entries in place, reuse ids and shrink. No
   append-only dictionary, dense id space or static layout is assumed.
4. **Updates happen in place.** Counts, child-presence bits, survivor and live
   flags are payload words of the keyed entries. A transaction records a
   compact undo log of:
   - word writes;
   - inserted, detached and erased entries;
   - key retains and releases.

   Rollback replays it. Nothing is copied to stage an update.
5. **Results remain tuple objects.** Deltas are `SignedResult`s with
   `storage::Tuple`s, and snapshots and cursors yield the same row types as today.
6. **Garbage collection is explicit and configurable.** These are retired with
   the epoch that unlinked them:
   - deleted tuples and dead key records;
   - detached entries;
   - retired epoch spools.

   Readers (cursors, epoch views, pending epochs) pin the epoch they observe. The
   `Collector` frees a batch only when no pin can observe it. `GcOptions::mode`
   selects:
   - `blocking` (default; one thread): the writer collects at a sealed epoch
     once the retired-memory pool holds `retired_bytes` (default 64 MiB), or
     every `epoch_interval` sealed epochs if that is nonzero (default 0: off);
   - `background` (two threads): one collector thread frees eligible batches
     while the writer continues;
   - `manual`: the owner calls `collect()`.

   Retired records stay charged to the engine's `Budget` until freed. In every
   mode a charge that would exceed the budget first reclaims (collects, or
   waits for the collector thread to drain) and then retries, so garbage never
   causes a memory-limit failure by itself.
   The keyed core creates no other threads. The mode is set by
   `DeltaOptions::gc`, `fallback::Options::gc` and `weighted::Options::gc`
   (the SQL rows/aggregate runtimes pass theirs through
   `sql_rows::Options::native`).
7. **Accounting stays, but at coarse grain.** The query `MemoryAccount` is
   charged per map or domain capacity change and per interned record, not per
   node or journal entry. Memory limits and failure atomicity still hold: any
   allocation that can fail happens before the in-place mutation it enables, or
   is undone by rollback.

## Implemented pieces

- **Primitives** (`include/crown/storage/keyed.hpp`, `src/storage/keyed.cpp`):
  - `Key`, `KeyDomain` (interning with reference counts, restore for rollback),
    `KeyMap` (detach/relink for rollback, shrink).
  - `Collector`: epoch batches; reader pins; blocking, background or manual mode;
    retirement capacity reserved before mutation; `seal()` never throws.
  - `Budget`: an atomic gauge of index capacity and interned bytes, enforcing the
    query memory limit with `MemoryFailure(limit)` before mutating.
- **Engine** (`include/crown/runtime/keyed_engine.hpp`, `src/runtime/keyed_engine.cpp`):
  - The set engine runs the same compiled program as the reference core: tree,
    generalized nodes, C*, input adapters (projections, repeated columns,
    constants, column/literal comparisons on any type) and the enumeration
    program, and produces SQL or core views.
  - Undo log of word writes, inserts, detaches and key acquisitions; rollback
    restores the committed state exactly.
  - Retained physical source rows (set semantics at the source).
  - Step-wise staging (`stage_source`, then one route at a time) with
    `RouteReport`s.
  - Resumable cursors that block the writer.
- **DeltaRuntime integration** (`src/runtime/delta.cpp`):
  - `DeltaOptions::engine` (`automatic`, `keyed`, `reference`) and
    `DeltaOptions::gc` (`blocking` single-threaded by default, `background`
    for one collector thread); `DeltaRuntime::engine()`, `collect_garbage()`
    and `gc_statistics()`; `storage::keyed::process_gc_statistics()` totals
    every collector of the process.
  - Pending epochs stage one occurrence route per step. Each accepted core row
    is one `core_result` step, so pause, drain and discard keep their meaning.
  - `Epoch::stages()` and `Epoch::input().input.derivations` come from the route
    reports.
  - Results are `storage::Tuple`s: compact payloads that carry the query account
    and their exact size. The epoch spool holds keyed rows coded (one tag byte
    and one word per cell; text and wide cells in side buffers) and builds each
    tuple in the runtime's `TuplePool` when the row is read, so a large epoch
    costs about nine bytes per integer cell and a reader that releases rows
    reuses one warm chunk. Spool limits and metrics count the tuple each row
    becomes, as before. A recycled epoch also keeps its derivation list.
- **Reference twin.** Reference-core diagnostics, recovery and replanning run on
  a twin built on demand from the retained sources at the current sequence and
  mode, under the runtime's own owner id: `snapshot`, `current_view`,
  `live_snapshot`, `canonical_state`, `inspect_invariants`, statistics
  captures, `checkpoint_image`, gauges and `rebuilt_for`. It costs O(state) per
  call and is cached until the next commit. `rebuilt()` returns a keyed owner
  again. Restored and initialized sources load into the keyed core. Workload
  statistics (physical facts, accepted occurrences, derivation changes) are
  recorded by the keyed path.
- **Cyclic queries** (`keyed::CyclicEngine`, used by `fallback::Runtime`):
  - Rows of every table keep their typed values under a row `Key`; each join
    probe uses a fixed-width secondary index keyed by the projected columns.
  - Views (residual components) count completions per view key, and answers
    carry support counts per head key, all in `KeyMap`s.
  - An event is prepared without touching committed state (view deltas,
    supports and answer changes in pending maps). It is then published without
    failure: capacity is reserved and keys acquired during preparation. A
    failed or rejected event changes nothing.
  - For catalogs without enforced constraints, the engine also coordinates
    the sources: validation, sequencing and the source image. Constrained
    catalogs keep the source-only physical owner.
- **Cyclic queries by decomposition** (`CyclicOptions::decompose`, default on;
  `CROWN_CYCLIC_ENGINE=support` disables it). When the atoms partition into
  two or more connected bags whose bag-level query is free-connex acyclic,
  `CyclicEngine` runs a generalized hypertree decomposition (GHD) instead of
  one support-count engine:
  - The search is exhaustive over set partitions (3 to 10 atoms). A single
    atom whose variables lie inside a multi-atom bag joins that bag (it only
    filters the bag's join, so a wedge plus its closing edge becomes the
    triangle). The search prefers the smallest largest bag, then the fewest
    atoms in multi-atom bags.
  - Each multi-atom bag keeps the projection of its join onto its needed
    variables (head variables and variables shared with another bag). It runs
    on its own support-count engine with every atom in the enumerated prefix
    (`residual_views = false`), so the support counts cover the projected-away
    local variables and no wide residual view is materialized.
  - Single-atom bags, and the bags' tuple changes, feed one `SetEngine` (delta
    mode) over the bag-level query. Its row changes are the answer changes.
  - Bag engines in background GC mode use manual collectors, so a process
    keeps at most one collector thread.
  - `CyclicEngine::algorithm()` and `fallback::Runtime::algorithm()` report
    `ghd` or `support`. `fallback::Options::answer_changes = false` maintains
    without materializing each epoch's answer changes, and
    `fallback::Runtime::visit` streams a snapshot without sorting or
    materializing it.
- **Base-store elision.** A source table with one unfiltered route whose record
  is a permutation of the row keeps no separate row store. The node's records
  are the retained rows, so `stage_source` answers presence from the record
  store and passes its probe to the route: one hash probe per event instead of
  two. `sources()`, `contains()` and `rows()` read the records.
- **Fused SQL aggregate batches** (`sql_aggregate::Options::fused`, opt-in; the
  paper aggregate harness enables it, and `CROWN_AGGREGATE_FUSED=0` keeps the
  layered path):
  - `SqlRowsRuntime::prepare_fused` validates and chains the net batch as
    `prepare_batch` does.
  - It stages every changed native contribution straight into the keyed bag
    engine (`WeightedRuntime::fused_begin/fused_stage/fused_commit`). Each
    changed head tuple folds into its group as it changes.
  - There are no SqlRows/Weighted prepared epochs, captured bag deltas or
    per-layer metrics. The groups, group changes, source weights, root weights
    and source images are the same.
  - `group_changed` stays net: a batch with both decreasing and increasing
    edits keeps a per-head ledger.
  - Programs with key constraints, or on the reference weighted core, keep the
    layered path.
- **Bag mode** (`EngineOptions::bag`, used by `WeightedRuntime`):
  - Native records carry multiplicities and per-slot child sums, supports carry
    subtree sums, and visible keys carry weights `W_v`.
  - The count of a head tuple is the product of its C* weights.
  - A staged contribution changes weights monotonically. Each changed head
    tuple is therefore enumerated once (lowest-rank changed factor), with
    before/after counts folded into the epoch's bag or support deltas.
  - The root summary, result cursors (with counts) and rollback come from the
    same structures.
  - Diagnostic snapshots use a reference twin rebuilt from the native records.
    Journals (`capture_changes`/`capture_events`) keep the reference core.
- **Inline keys.** One or two int64/Boolean fields are carried in the `Key`
  itself (no record, reference count or pointer chase). Maps place every key
  by both of its words.
- **Results.** Result tuples come from `storage::TuplePool`, which packs rows
  into pooled, shared chunks: no allocation or ledger entry per row.
- **Override.** `CROWN_DELTA_ENGINE=reference`, `CROWN_FALLBACK_ENGINE=reference`
  and `CROWN_WEIGHTED_ENGINE=reference` resolve automatic selection to the
  reference cores. 110 tests that check the reference core's own contracts
  run that way (`CROWN_REFERENCE_CORE_TESTS` in `CMakeLists.txt`). Those
  contracts are exact memory-ledger requests, journal and audit records,
  observation traces and phase work, and `RuntimeTestProbe` internals. Six
  tests of the reference weighted core's per-phase metrics and indexed-storage
  grants run with `CROWN_WEIGHTED_ENGINE=reference`
  (`CROWN_REFERENCE_WEIGHTED_TESTS`).

## Phases

| Phase | Scope | Verification |
| --- | --- | --- |
| A | Key, KeyDomain, KeyMap, Collector (done) | `keyed_storage_test` model tests |
| B | Keyed table backend for `AccountedStorageTable` (tuples interned per relation, secondary indexes keyed by projected keys, undo-log journal, pins as GC epochs); then key-based fast paths (`find`/`bucket` by `Key`) | Whole suite on the keyed backend; backend-specific cost tests split |
| C | SupportRuntime state in keyed payload words (child bits/satisfied, P/E counts); public journal records and epoch views produced from the undo log on demand | support/epoch/delta suites; paper differential replays |
| D | DeltaRuntime live images (L flags, live-separator maps) and enumeration on keyed buckets; spool of tuple results; GC options on `DeltaOptions` and sessions | delta suites, session/window suites, paper replays |
| E | WeightedRuntime, fallback and SQL runtimes on the keyed core (done) | `keyed_cyclic`, `keyed_bag`; aggregate/fallback/SQL suites and oracles |
| F | Retire `Flat*` executors and the `CROWN_ENGINE` switch; refresh docs and cost contracts | full suite, paper survey vs Flink |

Tests that assert exact internal costs of the old structures (node counts,
memory by purpose, per-record journal sizes) are updated to the new contracts.
Semantic and differential tests stay unchanged.
