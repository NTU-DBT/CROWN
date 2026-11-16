# R06 read-only design preflight, 2026-11-06

Status: historical pre-implementation proposal. R06 was not started at this
review and is now under implementation. Astra inspected actual owners,
storage and checkers without editing files or running builds/tests. Root saved
these recommendations for the next implementer; they are not R06 acceptance
evidence. Preserve the complete [Refactor.md](../../Refactor.md) card.

## Ownership and API

Private construction belongs in [support.cpp](../../src/runtime/support.cpp),
[physical.cpp](../../src/runtime/physical.cpp) and
[delta.cpp](../../src/runtime/delta.cpp). OrderedReplay is external ordered
ingestion, not initialization. Current snapshots contain owners/handles and
omit live parent/child indexes; generic checkers and metadata `.at()` calls do
not satisfy localized corruption inspection.

Propose initialization/inspection value headers with `BuildMethod { direct,
insertion_replay }`, cumulative build-work limits, checked `BuildMetrics`,
owner initializer/rebuilt factories, canonical typed state and structured
invariant reports. Keep empty constructors. Initialization publishes a fresh
owner at sequence zero, emits no epochs/output and creates no source positions.
First external event is one. A quiescent rebuild returns a separate owner at
the original committed sequence/mode; failure preserves the original owner,
handles and results. Do not silently rebind OrderedReplay. A session initial
Database overload can preserve zero accepted input progress.

## Snapshot validation and independent build paths

Validate the complete source Database against `source_catalog()` first:
table count, typed full rows, set identity and all enforced unique/FK constraints,
including unused tables and constant plans. **Valid cyclic foreign keys are
mandatory:** there may be no legal first public insertion. Validate the final
snapshot once and construct unpublished prefixes privately. Ordinary apply
keeps per-event constraints. Do not replay fabricated public epochs and reset
a published owner to zero.

Both paths construct source tables and per-occurrence derivation counts through
compiled adapters, preserving full-row identity, alias predicates/constants,
repeated variables and projection collisions.

- Direct: populate positive native keys and compute a genuine children-first
  postorder. Build actual records/child flags/satisfied counts/S, parent P
  counts and separate E counts. Native rows probe every child P. Generalized
  candidates are the union of child P keys; flags count child presence, not
  child multiplicity. Populate registered tables/indexes and real tuple IDs,
  translating generalized rows through destination layout tokens. Do not use
  apply, propagation queues, survivor transitions or staged replay here.
- Replay: deterministic source row/alias order in a separate unpublished owner;
  exact derivation changes and existing R04 transactions/queues on native zero
  crossings. Use private sequence-zero initialization, leaving public epochs
  contiguous from one. Discard each initialization journal immediately rather
  than retaining load history. Charge cumulative build work across all rows.

Constant true/false routes retain explicit route semantics; a source-free
identity must not become an empty generalized candidate union. Delta adopts
the initialized physical owner before publication and reuses actual `build_live`
for L and both parent/child bucket indexes/counts. Maintenance retains no live
image. Bootstrap must not materialize the answer product or depend on delta
spool capacity.

## Canonical inspection and corruption acceptance

Canonical equality includes plan/catalog/arithmetic identity, sequence, source
sets, occurrence derivations, node records/flags/satisfied counts/S, separate
P/E support counts, delta mode and optional full L/parent/child indexes with
bucket rows/counts and aggregate totals. Preserve E absent versus present-empty.
Use sorted typed Rows. Exclude owners, tuple IDs/generations, pointers, revisions,
history, metrics, pins and arena high-water capacity. A versioned typed JSON
dump is diagnostic state, not a checkpoint or restore format.

Inspection must read actual private maps/tables and return component, table/
occurrence/node, child slot, typed key and expected/actual values. Safely check
missing/orphan metadata before lookups. Independently recompute source
derivations, record presence, generalized candidates, child bits, S/P/E and full
live factors/buckets. Keep lower storage/index checks and independent diagnostic
work/issue limits; do not reuse a tiny update budget or generic cache mismatch.

Use a separate consistently compiled `CROWN_RUNTIME_TESTING` runtime target
with private friend probes defined beside actual Impls. Production exposes no
mutation setter. Corrupt actual satisfied-child, P, E, occurrence derivation,
parent/child bucket and aggregate live counters; require exact location and
expected/actual values, restore, then require a clean report. A damaged detached
dump does not prove actual invariant localization.

## Record bound, tests and implementation order

Native records are bounded by source rows per occurrence; generalized records
by child P unions; S by records; P/E by S; L by E. Flags/reverse indexes add
fixed-query degree factors. Parent-index row copies sum parent L sizes over
live edges; child-index copies sum nonroot L sizes. Use `O_Q(1+N)` retained
records including constant routes/descriptors, and reconcile component counts
with arena live records. Existing physical statistics omit live maps/indexes.
Widths, allocator/capacity slack, source snapshots, old/new rebuild owners,
scratch and caller pins/history remain additional. S05 owns complete bytes.

Independent tests need native/internal and 3/8-child generalized nodes,
projection/count collisions, disconnected products, Boolean/nullary/SQL EXISTS
at zero, self-join loops/filters/repeated variables, unused tables/constants,
cyclic FKs and rejected invalid snapshots, typed SQL output, direct/replay/A04
equality and exact signed suffix traces. Add nonzero rebuild/new owners/barriers,
persistent direct/replay/bootstrap/rebuild failures, budgets and actual counter
corruption. Scale N-by-N answers without materializing them: inspect linear
state and zero direct replay/propagation counts. Separate churn high-water and
caller history from live records.

Suggested order: common value types; support builders; physical routing/rebuild;
delta adoption/live inspection; diagnostic writer/schema; optional session
initial snapshot; independent/fault/corruption/scale tests; proof/contract;
targeted checks, then a full frozen-source matrix. O02's final matrix has now
passed; native R06 work can begin after this read-only proposal is reviewed.
