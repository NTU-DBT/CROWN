#pragma once

#include "crown/planner/residual.hpp"
#include <cstddef>
#include <cstdint>
#include <memory>
#include <optional>
#include <string>
#include <vector>

namespace crown::planner {
struct ValidationReport;
namespace candidate_detail {
struct CandidateData;
struct SnapshotData;
struct Factory;
}

enum class CandidateUpdateProfile { mixed_full_row_set_v1 };
// Exhaustion covers only the declared family, never all tree shapes or a
// globally minimum maintenance-cost search.
enum class CandidateFamily { exact_seed_residual_seed_normal_form_v1, finite_proposals_v1 };
enum class CandidateSource { exact_witness, residual_seed, normal_form, supplied_proposal };
struct CandidateContext {
  CandidateUpdateProfile updates = CandidateUpdateProfile::mixed_full_row_set_v1;
  std::string arithmetic = "exact-nonnull-v1";
  std::string planner = "crown-tree-v1";
  std::string optimization = "structural-height-v1";
  std::string cost_model = "no-cost-v1";
  std::string canonicalization = "structural-tree-key-v1";
  // Admission rejects unknown profiles/versions. No runtime complexity or
  // cost-ranking claim follows merely from an accepted cache namespace.
};
struct CandidateLimits {
  PhaseCeiling enumeration{50'000'000, {}};
  std::optional<std::size_t> logical_depth = 256;
  std::optional<std::uint64_t> records = 1'000'000;
  std::optional<std::uint64_t> cells = 10'000'000;
  std::optional<std::size_t> retained_candidates = 128;
  // Cumulative logical construction, not S05 allocator bytes. Binding/context
  // admission, P02 scratch, capacity/scalar widths and retained history are
  // separate explicit costs. No delegated exact work: the proof is supplied.
};
// Original generation provenance survives cache reuse. The new provider
// retains its own supplied original proof, whose witness remains unchanged.
struct CandidateProvenance {
  CandidateSource source = CandidateSource::exact_witness;
  CandidateFamily family = CandidateFamily::exact_seed_residual_seed_normal_form_v1;
  std::uint64_t sequence = 0;
  std::optional<ResidualOrigin> residual_last_step;
  std::optional<ResidualTrace> residual_trace;
};
// Owned original-binding P02 upper at the supplied original minimum. Getters
// borrow from a live handle; original_proof owns the unchanged certificate.
// Copying this handle allocates no tree/report/key/proof payload.
class MinimumHeightCandidate {
 public:
  MinimumHeightCandidate(const MinimumHeightCandidate&) noexcept = default;
  MinimumHeightCandidate& operator=(const MinimumHeightCandidate&) noexcept = default;
  MinimumHeightCandidate(MinimumHeightCandidate&&) noexcept = default;
  MinimumHeightCandidate& operator=(MinimumHeightCandidate&&) noexcept = default;
  bool valid() const noexcept;
  const Catalog& catalog() const;
  const Query& query() const;
  const FreeConnexTree& tree() const;
  // The existing complete checked-upper report; no new validation authority or
  // allocating copy is created by observing it.
  const ValidationReport& validation() const;
  std::size_t height() const;
  const std::string& structural_key() const;
  const CandidateContext& context() const;
  CandidateProvenance provenance() const;
  VerifiedOptimum original_proof() const;
  // The original certificate retains its own witness. An alternative upper
  // tree is never substituted into it. Structural keys require this binding
  // and context namespace; key bytes alone are not global identity/authority.
 private:
  friend struct candidate_detail::Factory;
  explicit MinimumHeightCandidate(std::shared_ptr<const candidate_detail::CandidateData>) noexcept;
  std::shared_ptr<const candidate_detail::CandidateData> data_;
};

enum class CandidatePhase {
  admitted, exact_seed, residual_seed, enumerate, validate, canonicalize,
  publish, exhausted, failed, cancelled, moved_from
};
enum class CandidateStop {
  none, candidate_ready, quantum_work, quantum_time, total_work, total_time,
  depth_limit, record_limit, cell_limit, candidate_capacity, allocation_failure,
  counter_overflow, invalid_quantum, internal_failure, exhausted, cancelled, moved_from
};
struct CandidateStatistics {
  std::uint64_t proposed = 0, rejected = 0, taller = 0, duplicates = 0, published = 0;
  std::uint64_t topologies = 0, scope_tuples = 0, cache_seeded = 0;
};
struct CandidateProgress {
  CandidatePhase phase = CandidatePhase::admitted;
  CandidateStop last_stop = CandidateStop::none;
  CandidateFamily family = CandidateFamily::exact_seed_residual_seed_normal_form_v1;
  std::optional<std::size_t> verified_original_height;
  // Exhaustion covers the declared normal-form family or the supplied finite
  // batch, not an upstream proposal algorithm or global maintenance-cost search.
  bool family_exhausted = false;
  WorkCounters work;
  CandidateStatistics statistics;
  std::uint64_t records = 0, cells = 0, limit_revision = 0;
  std::size_t candidate_count = 0;
  // Diagnostic snapshot only. Existing original proof is independent of
  // enumeration completion; this aggregate manufactures no checked handle.
};
struct CandidateAdvance { CandidateStop stopped_for; CandidateProgress progress; };

// Immutable owning prefix admitted outside advance; it copies handle/event
// vectors and retains actual completion. Reuse starts a fresh generator and
// rechecks trees; no live cursor or earlier completion state is transplanted.
class CandidateSnapshot {
 public:
  CandidateSnapshot(const CandidateSnapshot&) noexcept = default;
  CandidateSnapshot& operator=(const CandidateSnapshot&) noexcept = default;
  CandidateSnapshot(CandidateSnapshot&&) noexcept = default;
  CandidateSnapshot& operator=(CandidateSnapshot&&) noexcept = default;
  bool valid() const noexcept;
  std::size_t candidate_count() const;
  std::optional<MinimumHeightCandidate> candidate(std::size_t) const;
  bool family_exhausted() const;
  CandidateFamily family() const;
  const CandidateContext& context() const;
  VerifiedOptimum original_proof() const;
 private:
  friend struct candidate_detail::Factory;
  explicit CandidateSnapshot(std::shared_ptr<const candidate_detail::SnapshotData>) noexcept;
  std::shared_ptr<const candidate_detail::SnapshotData> data_;
};

// Exclusive single caller. No borrowed input, background work or callbacks.
// create visits the original witness, optional residual, cached prefix, then
// a fresh normal-form enumeration. from_proposals visits only its supplied
// batch in input order. Every member passes the same P02/height/key gate.
// A cached prefix does not resume its former provider's cursor.
// Advance stops at each new candidate; reaching a requested count is not family
// exhaustion. Zero grants are inert; resource extensions retain saved cursors.
// Allocation and variable-width operations may cross a time boundary before
// the next check. Active time saturates diagnostically; logical counters do not.
class CandidateProvider {
 public:
  static CandidateProvider create(VerifiedOptimum, CandidateContext = {}, CandidateLimits = {},
                                  std::optional<ResidualCandidate> residual_seed = {},
                                  std::optional<CandidateSnapshot> cached_prefix = {});
  // Own unchecked proposals without implicit seeds or a normal-form tail.
  // Invalid/taller trees are discarded; exhaustion means this batch consumed.
  // Input construction/storage and source admission are outside advance grants;
  // the upstream producer must bound and report its own work and storage.
  static CandidateProvider from_proposals(VerifiedOptimum, std::vector<FreeConnexTree>,
                                         CandidateContext = {}, CandidateLimits = {});
  ~CandidateProvider();
  CandidateProvider(CandidateProvider&&) noexcept;
  CandidateProvider& operator=(CandidateProvider&&) noexcept;
  CandidateProvider(const CandidateProvider&) = delete;
  CandidateProvider& operator=(const CandidateProvider&) = delete;
  CandidateAdvance advance(WorkQuantum) noexcept;
  CandidateProgress progress() const noexcept;
  std::size_t candidate_count() const noexcept;
  std::optional<MinimumHeightCandidate> candidate(std::size_t) const noexcept;
  VerifiedOptimum original_proof() const;
  const CandidateContext& context() const;
  CandidateLimits limits() const;
  LimitChange raise_limits(CandidateLimits) noexcept;
  void cancel() noexcept;
  // Explicit allocating snapshot admission, outside advance. It owns a prefix
  // and its actual completeness state; it does not borrow the live cursor.
  CandidateSnapshot snapshot() const;
 private:
  struct Impl;
  explicit CandidateProvider(std::unique_ptr<Impl>) noexcept;
  std::unique_ptr<Impl> data_;
};

enum class CandidateCacheInstall { disabled, inserted, replaced };
// Cumulative activity survives clear(); entries is the current list size,
// independent of caller-retained snapshots after eviction or cache destruction.
struct CandidateCacheStatistics {
  std::uint64_t hits = 0, misses = 0, insertions = 0, replacements = 0, evictions = 0;
  std::size_t entries = 0;
};
// Bounded explicit exact-binding cache; lookup/install are allocating admission
// operations, not advance units. FIFO insertion order is deterministic; a hit
// does not change it. Replacements preserve their original FIFO position.
// Full equality is required; no digest-only or alpha-remapped proof reuse.
// This cache accepts only the original normal-form family, not finite batches.
class CandidateCache {
 public:
  static CandidateCache create(std::size_t max_entries = 128);
  ~CandidateCache();
  CandidateCache(CandidateCache&&) noexcept;
  CandidateCache& operator=(CandidateCache&&) noexcept;
  CandidateCache(const CandidateCache&) = delete;
  CandidateCache& operator=(const CandidateCache&) = delete;
  std::optional<CandidateSnapshot> lookup(const VerifiedOptimum&, const CandidateContext& = {});
  CandidateCacheInstall install(const CandidateSnapshot&);
  CandidateCacheStatistics statistics() const noexcept;
  void clear() noexcept;
 private:
  struct Impl;
  explicit CandidateCache(std::unique_ptr<Impl>) noexcept;
  std::unique_ptr<Impl> data_;
};
}  // namespace crown::planner
