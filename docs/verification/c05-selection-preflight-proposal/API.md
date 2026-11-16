# Proposed typed API

This is an interface design, not installed declarations or compiled code. Names
may change during reviewed implementation; the ownership, authority, outcomes
and accounting below are the proposed contract. Existing P06/P07/P08/C02 public
types keep their meaning and bytes. No editable aggregate becomes proof.

## Pure layer

Proposed public path: `include/crown/planner/selection.hpp`.

```cpp
namespace crown::planner::selection {
namespace rank = crown::planner::ranking;

enum class Policy {
  height_only, committed_input_native_depth, tuple_index_slots,
  maintenance_cost  // recognized request; unsupported_model in version 1
};
enum class FamilyPolicy { retained_prefix, require_exhausted_family };
enum class LayoutPolicy { native_layout_v1 };
enum class IndexPolicy { share_identical_requirements_v1 };
enum class CacheUse { bypass, read_only, read_write };

struct DirectCQ { PhysicalOptions options; };
struct PhysicalBasis { PhysicalPlan plan; };
using Source = std::variant<DirectCQ, PhysicalBasis>;

struct TupleIndexSlotLimit { std::string maximum; };
enum class BytePrediction { live_allocation, peak_allocation };
struct AllocatorByteLimit { std::uint64_t maximum; BytePrediction prediction; };
using Constraint = std::variant<std::monostate,
    TupleIndexSlotLimit, AllocatorByteLimit>;

struct Limits {
  rank::Limits aggregate;
};
struct Request {
  Policy policy = Policy::committed_input_native_depth;
  rank::Fallback fallback = rank::Fallback::height_only;
  FamilyPolicy family = FamilyPolicy::retained_prefix;
  LayoutPolicy layout = LayoutPolicy::native_layout_v1;
  IndexPolicy indexes = IndexPolicy::share_identical_requirements_v1;
  Constraint constraint;
  Limits limits;
};

enum class Stage { admission, capture, source_binding, constraint_assessment,
  primary_assessment, decision, cache_key, cache_lookup, lowering,
  cache_admission, publication };
enum class Stop { complete, invalid_handle, invalid_request, binding_mismatch,
  no_candidates, incomplete_family, unsupported_model, unsupported_layout,
  unsupported_memory_prediction, evidence_unavailable, boundary_unavailable,
  constraint_unsatisfied, resource_limit, lowering_failure,
  allocation_failure, internal_error };
enum class EvidenceUse { absent, as_of };
enum class PreparationTiming { absent, measured, unmeasured };
enum class AssessmentPurpose { primary, slot_constraint, primary_and_constraint };
struct Assessment { AssessmentPurpose purpose; rank::Result result; };
enum class Eligibility { unconstrained, within_slot_limit, above_slot_limit };
struct CandidateDecision { std::size_t candidate_index; Eligibility eligibility; };

struct CacheLimits {
  std::size_t entries = 128;
  std::uint64_t key_bytes = 8 * 1024 * 1024;
  std::uint64_t plan_payload_bytes = 32 * 1024 * 1024;
};
struct CacheStatistics {
  std::uint64_t hits, misses, insertions, evictions;
  std::size_t entries;
  std::uint64_t key_bytes, plan_payload_bytes;
};
class PlanCache {
 public:
  static PlanCache create(CacheLimits = {}); // allocating admission, may throw
  // Exclusive caller, move-only. Clear/destruction preserve old result handles.
  CacheLimits limits() const noexcept;
  CacheStatistics statistics() const noexcept;
  void clear() noexcept;
  // No public lookup/install-by-key, raw-plan insertion, import or serialization.
 private:
  // Private implementation; only the selection pipeline may prepare/install.
};

enum class CacheDisposition { bypassed, disabled, hit, miss_read_only, inserted };
struct CacheObservation {
  CacheDisposition disposition;
  std::uint64_t compared_bytes;
  std::uint64_t binding_bytes;
};
class Selection {
 public:
  // Copyable immutable owning handle; only a private factory constructs it.
  const CandidateSnapshot& snapshot() const noexcept;
  const MinimumHeightCandidate& selected() const noexcept;
  std::size_t selected_index() const noexcept;
  const PhysicalPlan& plan() const noexcept;
  const Source& source() const noexcept;
  const Request& request() const noexcept;
  const std::vector<Assessment>& assessments() const noexcept;
  const std::vector<CandidateDecision>& decisions() const noexcept;
  const std::optional<rank::Evidence>& evidence() const noexcept;
  EvidenceUse evidence_use() const noexcept;
  rank::Policy effective_policy() const noexcept;
  rank::Reasons fallback_reasons() const noexcept;
  const rank::Usage& usage() const noexcept;
  PreparationTiming preparation_timing() const noexcept;
  const CacheObservation& cache_observation() const noexcept;
  const std::optional<std::string>& cache_binding() const noexcept;
  // format_version = 1; cache_binding_version = 1.
 private:
  // shared_ptr<const Data>; copies and moves retain a valid owning history.
};
struct Attempt {
  Stop stop = Stop::internal_error;
  Stage stage = Stage::admission;
  std::optional<Selection> selection;
  rank::Usage usage;
  std::optional<rank::Stop> component_stop;
  rank::Reasons reasons{};
  PreparationTiming preparation_timing = PreparationTiming::absent;
  std::size_t retained{}, constraint_evaluated{}, primary_evaluated{};
};
[[nodiscard]] Attempt select(const CandidateSnapshot&, const Source&,
    const Request& = {}, const std::optional<rank::Evidence>& = {},
    PlanCache* = nullptr, CacheUse = CacheUse::bypass) noexcept;
}
```

The sketch omits ordinary special-member declarations, includes and private
friends; it is not a header to copy into a build. `Source` is request data:
DirectCQ obtains the exact Catalog/Query from the snapshot proof binding.
PhysicalBasis is a factory-produced immutable P08 plan; every accessor is
validated before use so a moved-from handle cannot pass admission. Request
construction and initial cache construction are allocating caller operations;
copies made inside selection are admitted and charged by selection.

The four native work ceilings in aggregate are finite, mandatory host ceilings.
Normalized binding expression/recursion limits remain the finite size_t values
owned by the source basis, as C02 currently replays them. There is no new C05
override that the existing C02 rank API could silently ignore. A caller needing
different producer limits must explicitly rebuild its matching basis; all such
limits participate in exact source/cache binding.

Source equivalence checks full Catalog/Query and PhysicalOptions. For a
normalized basis it additionally checks every original source catalog,
BoundSql and NormalizedSql field listed in `CACHE_KEY.md`. For a direct CQ it
requires absence of a normalized program. It intentionally does not require
the evidence owner's existing tree to equal the basis or selected tree:
physical input cardinalities and committed input weights may rank other
candidates with the same source semantics. Raw tree equality is separately
required for reuse of the chosen compiled artifact.

The public constraint string accepts only `0` or a nonzero leading decimal
digit followed by digits, at most 155 characters and at most 2^512−1. No sign,
space, leading zero, exponent, decimal point, locale or saturation. Its cap is
parsed/compared with bounded exact operations; a lower caller `score_bits`
still limits produced C02 scores. Byte requests and the recognized C03 policy
have explicit unsupported outcomes; an unknown enum value is invalid_request.

The result vector covers the original snapshot order. Complete C02 assessments
retain every per-table, per-node and per-index term. The separate decision
vector explains constraint membership and `selected_index` chooses from that
vector. The minimum-height proof is obtained from the current retained snapshot,
never from the cache. Public cache binding bytes are diagnostic data, not an
insertion or import capability; absent when caching is bypassed/disabled.

An unsuccessful Attempt contains no Selection and changes no cache state.
Its nonallocating scalar diagnostics identify the failed stage, component stop,
observed reason bits and counts. For constraint_unsatisfied,
`constraint_evaluated == retained`; this is a complete retained-set constraint
rejection, not a proof that no other family or physical implementation fits.
No partial score vector is represented as a successful selection. A request
can be retried unchanged with more resource budget or new evidence explicitly.

`CacheUse::bypass` ignores a supplied cache; non-bypass with a null cache is
invalid_request. A zero-entry cache is explicitly disabled without key work.
A positive-entry cache has nonzero byte caps; invalid limits fail cache creation.
Cache creation cannot partially publish a handle. The default select call has
no cache effects. No ambient/global cache is introduced.

## Actual-owner bridge

Proposed public path: `include/crown/runtime/selection.hpp`.

```cpp
namespace crown::runtime::selection {
namespace ps = crown::planner::selection;
class CurrentSelection {
 public:
  const ps::Selection& selection() const noexcept;
  const ranking::RuntimeEvidence& capture() const noexcept;
  // Actual fresh capture made by this call, valid as history after return.
 private:
  // Private factory only; no public constructor from old evidence + Boolean.
};
struct Attempt {
  ps::Stop stop = ps::Stop::internal_error;
  ps::Stage stage = ps::Stage::admission;
  std::optional<CurrentSelection> selection;
  planner::ranking::Usage usage;
  std::optional<planner::ranking::Stop> component_stop;
  planner::ranking::Reasons reasons{};
  ps::PreparationTiming preparation_timing = ps::PreparationTiming::absent;
  std::size_t retained{}, constraint_evaluated{}, primary_evaluated{};
};
[[nodiscard]] Attempt select_current(const planner::CandidateSnapshot&,
    const ps::Source&, const PhysicalRuntime&, const ps::Request& = {},
    statistics::Limits = {}, ps::PlanCache* = nullptr,
    ps::CacheUse = ps::CacheUse::bypass) noexcept;
// Same exact parameters with DeltaRuntime and QuerySession owner overloads.
}
```

The current overload has no retained-evidence input. It makes one fresh C02
capture, requests physical cardinalities exactly when the primary policy or
constraint needs them, and privately carries that capture into the same pure
decision implementation. A fresh workload/boundary capture still occurs for
height-only. The inner pure Selection remains `as_of`; the outer private
CurrentSelection establishes how the facts were obtained. A user cannot make
an old pure result current by changing a field.

The bridge checks actual combined owner/epoch/pending/layer consistency and the
complete source equivalence under the existing exclusive-owner contract.
It retains RuntimeEvidence including actual session context; no report target
or JSON report factory is required. Final cache publication and the additional
CurrentSelection allocation form one transaction, so a late wrapper allocation
failure does not leave an inserted cache entry. The pure core must expose a
private prepared transaction, not commit a pure call then allocate the wrapper.

This is synchronous selection, not an owner lock implementation. No concurrent
writer is admitted by the underlying owner APIs. With no callback or intervening
mutation, a fresh capture remains the actual boundary for this call. After
return, freshness is historical and a subsequent current selection captures
again. No automatic plan installation or state migration is added.
