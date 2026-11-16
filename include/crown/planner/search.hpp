#pragma once

// Owned in-process exact-search and independent proof-replay continuations.
// Existing oracle.hpp entry points and v1/v2 certificate formats stay intact.
#include "crown/planner/oracle.hpp"

#include <chrono>
#include <cstdint>
#include <memory>
#include <optional>
#include <string_view>

namespace crown::planner {
namespace continuation_detail {
struct BindingData;
struct IncumbentData;
struct OptimumData;
struct InfeasibleData;
struct CheckedCertificateData;
struct ArtifactFactory; // Internal only; no public arbitrary-tree constructor.
}

// Policy controls upper-handle exposure; both modes continue exact search and independent
// replay. See docs/planner_continuations.md, authority.
enum class SearchPolicy { strict, best_found };
// Algorithm names describe proof families; production search has no public v1 toggle. See
// docs/planner_continuations.md, authority.
enum class ProofAlgorithm { partition_v1, partition_v2 };
// continuation_v1 names attempted controlled transitions rather than CPU or byte accounting.
// See docs/planner_continuations.md, resource accounting.
enum class AccountingVersion { continuation_v1 };

// Finite counters never wrap. Exhaustion is an explicit terminal reason.
// Time below is ACTIVE execution time, excluding time between advance calls.
// Cumulative work and active-time ceilings are separate; null is unbounded and time stops are
// cooperative. See docs/planner_continuations.md, resource accounting.
struct PhaseCeiling {
  std::optional<std::uint64_t> work = 10'000'000;
  std::optional<std::chrono::nanoseconds> active_time;
};
// Separate phase ceilings from active-worker logical depth; these options do not cap all
// retained bytes. See docs/planner_continuations.md, resource accounting.
struct ContinuationLimits {
  PhaseCeiling producer;
  PhaseCeiling replay;
  // Active worker logical heap-frame nesting, including partition/validation.
  // Parked workers and frontier width remain retained storage, not added depth.
  // Zero stops nonempty input before its first active frame push.
  std::optional<std::size_t> logical_depth = 256;
};
// Fix policy and binding at admission; later changes can only extend resources. See
// docs/planner_continuations.md, authority.
struct SearchOptions {
  SearchPolicy policy = SearchPolicy::strict;
  ContinuationLimits limits;
  // Production search uses P04 v2. V1 remains a private baseline, not a public
  // algorithm-switch flag. Independent replay accepts both existing versions.
};
// Configure replay resources without changing or trusting the admitted proof claim. See
// docs/planner_continuations.md, resource accounting.
struct ReplayOptions {
  PhaseCeiling limits;
  std::optional<std::size_t> logical_depth = 256;
};
// A nonnegative zero grant is inert; negative time is invalid, and moved-from owners are
// detected first. See docs/planner_continuations.md, resource accounting.
struct WorkQuantum {
  std::uint64_t work = 1;
  std::optional<std::chrono::nanoseconds> active_time;
};

// Read phase with typed authority/result; cancelled is terminal even when the result is
// unfinished. See docs/planner_continuations.md, lifetime.
enum class SearchPhase {
  admitted, preprocess, search, build_incumbent, validate_incumbent,
  export_proof, replay, complete, failed, cancelled, moved_from
};
// Replay phase is progress; valid is withheld until final checked-artifact publication. See
// docs/planner_continuations.md, authority.
enum class ReplayPhase {
  admitted, dispatch, validate_upper, build_scopes, classify_scope_orbits,
  index_claims, order_claims, prove_claim, match_root, complete,
  failed, cancelled, moved_from
};
// Separate grant/resource stops from terminal proof outcomes; a reason is never proof
// authority. See docs/planner_continuations.md, resource accounting.
enum class StopReason {
  none, quantum_work, quantum_time, total_work, total_time, depth_limit,
  allocation_failure, counter_overflow, invalid_quantum,
  invalid_certificate, internal_failure, complete, cancelled, moved_from
};
// Only completed independent whole-root proof upgrades lower evidence. See
// docs/planner_continuations.md, authority.
enum class BoundEvidence { universal, independently_checked };
// Interpret unfinished with phase: cancelled owners cannot resume. See
// docs/planner_continuations.md, lifetime.
enum class ResultKind { unfinished, verified_optimum, verified_infeasible, failed };
// Resource raises are atomic and monotone; even an accepted equal request increments
// revision. See docs/planner_continuations.md, resource accounting.
enum class LimitChange { applied, not_monotone, below_consumed, invalid, terminal };

// Attempts include failed or blocked units; active time/failure diagnostics saturate and
// depth tracks the active worker. See docs/planner_continuations.md, resource accounting.
struct WorkCounters {
  std::uint64_t attempted = 0;
  std::uint64_t committed_transitions = 0;
  std::uint64_t allocation_failures = 0;
  std::uint64_t active_nanoseconds = 0; // Saturating diagnostic, not proof data.
  std::size_t current_depth = 0;
  std::size_t peak_depth = 0;
  bool operator==(const WorkCounters&) const = default;
};
// Null lower also occurs in default/moved-from snapshots; only checked infeasible=true proves
// an empty family. See docs/planner_continuations.md, authority.
struct HeightInterval {
  // Null also occurs in default or moved-from snapshots without query bounds.
  // Only independently checked infeasible=true proves an empty family.
  // A bound live query starts at zero for empty body, one for nonempty body.
  std::optional<std::size_t> lower;
  // Present iff a complete independent P02 check established this upper bound.
  std::optional<std::size_t> upper;
  BoundEvidence lower_evidence = BoundEvidence::universal;
  bool infeasible = false;
  bool operator==(const HeightInterval&) const = default;
};
// Progress is scalar observation: producer completion and an upper are distinct from
// completed independent proof. See docs/planner_continuations.md, authority.
struct SearchProgress {
  SearchPhase phase = SearchPhase::admitted;
  StopReason last_stop = StopReason::none;
  ResultKind result = ResultKind::unfinished;
  HeightInterval heights;
  bool producer_complete = false;
  bool proof_complete = false;
  WorkCounters producer;
  WorkCounters replay;
  SearchStatistics structural;
  std::uint64_t limit_revision = 0;
};
// complete can mean terminal rejection; valid requires the fully published checked artifact.
// See docs/planner_continuations.md, authority.
struct ReplayProgress {
  ReplayPhase phase = ReplayPhase::admitted;
  StopReason last_stop = StopReason::none;
  bool complete = false;
  bool valid = false; // True ONLY after all claims AND root check complete.
  std::size_t checked_claims = 0;
  WorkCounters work;
  std::uint64_t limit_revision = 0;
};

// Value snapshots keep stop reporting nonallocating. For a live owner,
// nonnegative zero-work/time grants return a quantum stop without changing
// stored progress. Negative time is invalid; moved-from owners report moved_from.
struct SearchAdvance { StopReason stopped_for; SearchProgress progress; };
struct ReplayAdvance { StopReason stopped_for; ReplayProgress progress; };

// Immutable owned exact binding. No default construction or caller mutation.
// Creation validates Catalog/Query; canonical binding serialization is explicit
// IO work, not hidden in advance. Getters require valid() after a move.
// Retain the exact admitted model; prefix search binding is never upgraded to the original
// query by this handle. See docs/planner_continuations.md, authority.
class SearchBinding {
 public:
  SearchBinding(const SearchBinding&) noexcept = default;
  SearchBinding& operator=(const SearchBinding&) noexcept = default;
  SearchBinding(SearchBinding&&) noexcept = default;
  SearchBinding& operator=(SearchBinding&&) noexcept = default;
  bool valid() const noexcept;
  const Catalog& catalog() const;
  const Query& query() const;
  AccountingVersion accounting() const;
 private:
  friend struct continuation_detail::ArtifactFactory;
  explicit SearchBinding(std::shared_ptr<const continuation_detail::BindingData>) noexcept;
  std::shared_ptr<const continuation_detail::BindingData> data_;
};

// A complete, P02-checked tree. Establishes ONLY an upper bound.
// Retain a complete checked upper; its height is not a minimum claim. See
// docs/planner_continuations.md, authority.
class ValidatedIncumbent {
 public:
  ValidatedIncumbent(const ValidatedIncumbent&) noexcept = default;
  ValidatedIncumbent& operator=(const ValidatedIncumbent&) noexcept = default;
  ValidatedIncumbent(ValidatedIncumbent&&) noexcept = default;
  ValidatedIncumbent& operator=(ValidatedIncumbent&&) noexcept = default;
  bool valid() const noexcept;
  SearchBinding binding() const;
  const FreeConnexTree& tree() const;
  std::size_t height() const;
 private:
  friend struct continuation_detail::ArtifactFactory;
  explicit ValidatedIncumbent(std::shared_ptr<const continuation_detail::IncumbentData>) noexcept;
  std::shared_ptr<const continuation_detail::IncumbentData> data_;
};

// Retain matching upper/lower evidence for this exact admitted query; a prefix optimum stays
// prefix-scoped. See docs/planner_continuations.md, authority.
class VerifiedOptimum {
 public:
  VerifiedOptimum(const VerifiedOptimum&) noexcept = default;
  VerifiedOptimum& operator=(const VerifiedOptimum&) noexcept = default;
  VerifiedOptimum(VerifiedOptimum&&) noexcept = default;
  VerifiedOptimum& operator=(VerifiedOptimum&&) noexcept = default;
  bool valid() const noexcept;
  SearchBinding binding() const;
  ValidatedIncumbent upper() const;
  std::size_t height() const;
  const HeightCertificate& certificate() const;
 private:
  friend struct continuation_detail::ArtifactFactory;
  explicit VerifiedOptimum(std::shared_ptr<const continuation_detail::OptimumData>) noexcept;
  std::shared_ptr<const continuation_detail::OptimumData> data_;
};

// Retain a complete no-tree proof for this binding; prefix infeasibility is not original
// authority. See docs/planner_continuations.md, authority.
class VerifiedInfeasible {
 public:
  VerifiedInfeasible(const VerifiedInfeasible&) noexcept = default;
  VerifiedInfeasible& operator=(const VerifiedInfeasible&) noexcept = default;
  VerifiedInfeasible(VerifiedInfeasible&&) noexcept = default;
  VerifiedInfeasible& operator=(VerifiedInfeasible&&) noexcept = default;
  bool valid() const noexcept;
  SearchBinding binding() const;
  const HeightCertificate& certificate() const;
 private:
  friend struct continuation_detail::ArtifactFactory;
  explicit VerifiedInfeasible(std::shared_ptr<const continuation_detail::InfeasibleData>) noexcept;
  std::shared_ptr<const continuation_detail::InfeasibleData> data_;
};

// External certificate replay produces a checked authority handle; arbitrary
// HeightCertificate/OracleResult aggregates cannot manufacture these artifacts.
// Retain independent replay authority; arbitrary edited proof/result aggregates cannot create
// this handle. See docs/planner_continuations.md, authority.
class CheckedCertificate {
 public:
  CheckedCertificate(const CheckedCertificate&) noexcept = default;
  CheckedCertificate& operator=(const CheckedCertificate&) noexcept = default;
  CheckedCertificate(CheckedCertificate&&) noexcept = default;
  CheckedCertificate& operator=(CheckedCertificate&&) noexcept = default;
  bool valid() const noexcept;
  SearchBinding binding() const;
  const HeightCertificate& certificate() const;
  std::optional<VerifiedOptimum> optimum() const;
  std::optional<VerifiedInfeasible> infeasibility() const;
 private:
  friend struct continuation_detail::ArtifactFactory;
  explicit CheckedCertificate(std::shared_ptr<const continuation_detail::CheckedCertificateData>) noexcept;
  std::shared_ptr<const continuation_detail::CheckedCertificateData> data_;
};

// Exclusive single caller; no background work, callbacks or borrowed inputs.
// Movement between threads is allowed only with exclusive ownership. No method
// is concurrency-safe. Destruction/cancel require exclusive ownership.
// Own one immutable query scope and exclusive saved execution; typed proof publication is
// distinct from an incumbent or progress snapshot. See docs/planner_continuations.md,
// authority.
class ExactSearch {
 public:
  // Admission copy/move/validation may throw; no search work occurs here.
  static ExactSearch create(Catalog, Query, SearchOptions = {});
  ~ExactSearch();
  ExactSearch(ExactSearch&&) noexcept;
  ExactSearch& operator=(ExactSearch&&) noexcept;
  ExactSearch(const ExactSearch&) = delete;
  ExactSearch& operator=(const ExactSearch&) = delete;

  SearchAdvance advance(WorkQuantum) noexcept;
  SearchProgress progress() const noexcept;
  SearchBinding binding() const; // moved-from facade rejects
  SearchPolicy policy() const;
  ContinuationLimits limits() const;
  // Empty under strict policy. Copying a present owning handle allocates nothing.
  std::optional<ValidatedIncumbent> incumbent() const noexcept;
  std::optional<VerifiedOptimum> optimum() const noexcept;
  std::optional<VerifiedInfeasible> infeasibility() const noexcept;
  // Resource-only change: all ceilings must increase or remain unchanged.
  // null means unbounded and cannot be changed back to finite.
  LimitChange raise_limits(ContinuationLimits) noexcept;
  void cancel() noexcept; // cancel nonterminal work; terminal owners stay unchanged
 private:
  struct Impl;
  explicit ExactSearch(std::unique_ptr<Impl>) noexcept;
  std::unique_ptr<Impl> data_;
};

// Own claim replay against the supplied model; serialized exact binding belongs to IO and
// checked authority waits for final publication. See docs/planner_continuations.md,
// authority.
class CertificateReplay {
 public:
  // Catalog/query validated on admission. Structural proof checks are resumable.
  // IO read_height_certificate continues to check exact serialized binding.
  // Typed input is a claim about the supplied owned catalog/query, never trusted.
  static CertificateReplay create(Catalog, Query, HeightCertificate, ReplayOptions = {});
  ~CertificateReplay();
  CertificateReplay(CertificateReplay&&) noexcept;
  CertificateReplay& operator=(CertificateReplay&&) noexcept;
  CertificateReplay(const CertificateReplay&) = delete;
  CertificateReplay& operator=(const CertificateReplay&) = delete;

  ReplayAdvance advance(WorkQuantum) noexcept;
  ReplayProgress progress() const noexcept;
  SearchBinding binding() const;
  std::optional<CheckedCertificate> checked() const noexcept;
  ReplayOptions limits() const;
  LimitChange raise_limits(ReplayOptions) noexcept;
  void cancel() noexcept;
 private:
  struct Impl;
  explicit CertificateReplay(std::unique_ptr<Impl>) noexcept;
  std::unique_ptr<Impl> data_;
};

// No new overload is needed for minimum_tree/verify_height_certificate:
// implement their existing declarations as strict blocking adapters. Artifact
// to legacy aggregate conversion is allocating, done before return; failure
// cannot leave a partially certified legacy result. Progress/best-found IO uses
// a separate serializer/schema, not write_oracle with forged certification flags.
} // namespace crown::planner
