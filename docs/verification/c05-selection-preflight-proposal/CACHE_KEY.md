# Exact artifact-cache binding and invalidation argument

## Existing identities establish different things

P06/P07 checked handles bind a particular original Catalog/Query and minimum
height. P07 structural keys intentionally erase raw node identifiers and some
representation order. P08 query identity deliberately canonicalizes occurrence
and variable names/order; raw SQL text and producer limits are not all in that
identity. Physical SHA-256 also contains tree/ID mapping information, but it
remains a digest. None is by itself a complete, collision-free C05 cache key.
The native P07 CandidateCache stores candidate prefixes, not compiled plans.

C05 therefore uses a separate exact-byte binding, and reruns fresh typed
admission and full ranking before it even looks up the compiled artifact.
There is no certificate, evidence or decision cache and no proof transplantation.

## Binary framing

Use a new private `crown-selection-artifact-binding-v1` domain. Each record has
a fixed versioned field order and typed field tags; each variable-size sequence
has an exact unsigned length before its contents. Optional values have an
explicit absence/presence tag. Variants and enums have explicit validated tags.
Counts/IDs are admitted only when representable as uint64 and encoded as eight
big-endian bytes. Signed int64 uses the existing P07 modulo-2^64 bijection.
Booleans are one byte 0/1 and Date is its exact supported day value. Decimal
uses its public canonical `to_string()` bytes with its Value variant tag and
the zero convention retained; sign/scale/coefficient fields are private and
no new accessor or layout dependency is assumed. The formatting temporary is
bounded by the existing 41-character domain and is explicitly accounted as
bounded scratch, as in P07/C02.
Strings are length plus raw bytes, including NUL and high bytes; do not depend
on JSON escaping, locale, delimiter concatenation or a hash collision assumption.

Reuse the P07 v2 Catalog/Query byte encoder as a nested versioned record without
changing its legacy encoding or allocation behavior. Extend C05's own bounded
visitor for source/tree/options/evidence fields. Append work is admitted against
remaining work, key bytes and modeled payload before the write/allocation;
comparisons charge examined bytes to work/key traffic without inventing a
payload allocation. An exceeded counter/cap returns resource failure; never emit a
truncated key, rescale a score or retain a partial entry. Native P08 JSON admission
continues to have its existing scalar/transport domain; a binary cache encoder
does not enlarge that domain or excuse a failed P08 identity/lowering operation.

## Complete key field inventory

| Record | Required exact fields |
| --- | --- |
| Implementation domain | C05 binding/decision v1, P07 binding v2 and structural-key context version, C02 result/arithmetic v1, P08 physical format v1 and `crown-lower-v1`, query identity v1, grounded normalized format v2 when present, native layout/index-sharing policy and `reference_ordered_v1` backend |
| Structural authority context | Full original Catalog/Query binding, checked original required height, every CandidateContext field: updates, arithmetic, planner, optimization, cost_model, canonicalization |
| Retained family | CandidateFamily tag, actual family_exhausted bit, candidate count, ordered list of each full structural key, checked height and exact raw FreeConnexTree |
| Raw tree | Optional root, ordered node vector, each string ID/kind/scope/ordered child IDs/optional occurrence/claimed separator, claimed_connex and claimed_native_height including absence distinctions |
| Explicit source | DirectCQ versus PhysicalBasis tag, full source/catalog/core binding, PhysicalOptions policy strings and all optional producer work/identity limits; for a basis, its exact raw tree too as a conservative namespace distinction |
| Normalized source | Full BoundSql and NormalizedSql records below, not merely their semantic digest or core CQ |
| Selection request | Requested policy/fallback/family/layout/index choices, complete constraint tag and value, request Limits including optional time and the four finite native work ceilings |
| Fresh decision | Actual effective policy and fallback reason mask, selected snapshot index/full structural key/raw tree; full constrained eligibility vector |
| Evidence origin | Absent, explicit as-of, or actual current call; actual-owner class (physical/delta/session) for the latter, with no object address |
| C02 score facts | Complete EvidenceIdentity, ordered InputWeight rows including changed/noop, ordered SourceCardinality rows, complete SourceObservation states/optional values, denominator, depth_reasons and memory_reasons |
| Capture configuration | CaptureAccounting processing_limits, state_requested/state, requested/returned component counts, state work/row/key/byte/projection-width/heavy-key limits, snapshot_descriptors and snapshot_cells; those counts are context, not proof |

The complete EvidenceIdentity includes owner, committed epoch, interval start,
reset/configuration/segment and format generations; collection mode, max_cells,
period/offset/detail budget; every ModeIdentity field; pending and all three
generation-saturation flags. Comparing just segment, epoch, owner or a plan
digest is insufficient. A single no-op commit changes the epoch and committed
input census and therefore misses, even if all physical rows remain identical.

Full BoundSql means source text, original Catalog, parameter types, semantics,
inner_semantics, wrapper and alias, each occurrence's base/alias/column names/
location/include_descendants, every expression's SqlType/variant/arguments/
optional location, predicates, ordered output names/expressions, BindLimits
and recorded producer work. Full NormalizedSql means that BoundSql plus typed
parameter/constant slots (SQL NULL distinct from Value), core Catalog/Query,
every adapter's occurrence/base/predicates/non-null columns/equalities/column
classes/projection/program/constants, base_routes, ordered named typed core or
constant outputs, NormalizeLimits, recorded work and schema_version. SqlType
includes nullable and optional DecimalSpec. Scalars include Decimal coefficient
and scale and preserve byte strings. Vectors keep order and multiplicity;
sets use their exact stable ID order. No predicate/output/unused physical table
is omitted merely because the selected core shape looks the same.

For source equivalence between explicit basis and evidence, compare the source
records above except the basis's raw tree and compiled descriptors. An owner
can use a different valid tree for the same full program and options. For cache
artifact identity, selected raw tree is mandatory; the explicit basis tree and
ordered family are additional conservative distinctions. The cache never
alpha-renames source IDs or returns a physically ID-bound plan from a merely
structural-equivalent tree.

## Deliberate exclusions

The following are not artifact-authorizing inputs and are not reused:

- Original certificate bytes, residual trace and candidate provenance sequence.
  Every call supplies and checks its own typed proof/candidates; the resulting
  Selection always retains that current snapshot and its original witness.
  They affect diagnostic origin, not the deterministic P08 compilation of the
  already admitted exact source/tree/options. No cached certificate is returned.
- Measured selection Usage, elapsed clock values, C01 state-consumption counters,
  O07 trace/cursor delivery, diagnostic attempts/aborts and unread batch details
  that do not enter the C02 score facts. Fresh raw context is retained separately;
  it is never replaced by context from an entry. Requested caps remain in the key.
- Memory addresses, allocator/capacity observations and layout-token addresses.
  They are neither portable identity nor S05 accounting. Whole immutable plans
  retain internal token consistency; no cross-plan tuple splicing is permitted.
- CacheUse and the cache's retention-capacity settings. These control lookup,
  insertion and storage, not compilation or fresh score choice. In particular a
  read-only request must be able to find an entry installed by a read-write
  request. The actual requested operation/caps are checked independently and
  its current disposition is recorded; they are not borrowed from an entry.

CaptureAccounting's requested processing cap is included conservatively; when
an optional timing ceiling produces different delegated remaining caps, this
can cause a cache miss even for equivalent score facts. That is allowed. The
design claims correct reuse, not a hit-rate or speedup guarantee. A failed or
aborted update which changes only excluded diagnostics can still hit; the result
must retain the new actual context and fresh assessment rather than stale counts.

## Equality proof and limitations

1. The typed tagged/length-framed encoder is injective over admitted finite
   records. Equality is full byte equality with bounded per-byte comparison;
   a digest may be an optional reject accelerator, never acceptance authority.
2. Equal keys therefore have equal supported implementation domain, exact
   source/program/options, chosen raw tree and complete admitted decision
   context. P08 lowering is a deterministic function of those source/tree/
   options inputs for compiled descriptors and serialized identity. Allocation
   addresses and layout token identities are intentionally not that function.
3. Both the miss and hit path have already run the same current call's complete
   P07/C02 admission and assessments and selected the same exact member. Cache
   bytes cannot increase family coverage, change required height, bypass a
   constraint, substitute a different proof or make a partial assessment whole.
4. An entry stores only a whole PhysicalPlan from an admitted successful
   compilation/slot assessment. With exact equality it may replace the same
   deterministic compilation output. No tuple/index fragment is transplanted.
5. Current-at-capture authority comes only from the new actual-owner capture
   held through this synchronous call. Neither key equality nor cache hit
   proves liveness. Later owner mutation leaves an owning historical result.
6. Every admitted field mutation either changes the key, is explicitly excluded
   because fresh authority is never cached, or is rejected before lookup. A
   changed retained prefix/exhaustion bit cannot inherit an old best-choice
   claim. Source scopes, normalized parameter values and raw tree representations
   cannot collapse under a semantic/structural digest.

This is an analytical correctness argument for the proposed encoder/transaction,
not implementation proof. Independent mutation tests must establish that the
actual visitor contains every field and rejects limit/format errors. Unsupported
future enum/schema/policy versions must fail closed or increment the binding
version; adding a field without updating this inventory/key is an implementation
defect. Finite cache capacity and conservative extra fields can cause misses;
they cannot justify weaker equality.

## FIFO and transactional invalidation

The baseline cache is a bounded linear exact-key lookup, deterministic FIFO.
Hits do not reorder. A positive-capacity read-write miss prepares the complete
entry and result before eviction; capacity fitting evicts the oldest entries
only during a no-throw final commit. A read-only miss compiles without insertion.
If the complete entry alone exceeds key or logical plan-payload capacity,
read-write fails explicitly rather than silently skipping the requested cache
operation. Capacity zero is the declared disabled mode. There is no TTL, automatic
owner callback, background invalidation or pointer-based epoch shortcut.

Only successful final calls publish cache hit/miss/install/eviction counters.
Counter overflow is resource failure before mutation. Clear resets entries and
counters; it establishes no new proof epoch. Failed admission, scoring, source
capture, allocation, key comparison, lowering, late wrapper construction or
time check leaves entries, order, counters and prior handles unchanged. Old
Selection handles own their artifact even after eviction, cache move/clear or
cache destruction. Exact context keys make explicit invalidation unnecessary
for correctness; clear is only a caller-controlled retention operation.
