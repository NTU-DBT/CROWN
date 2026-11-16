#pragma once

// DESIGN PROPOSAL ONLY -- 2026-11-06. Not compiled or implemented.
// Intended location after implementation review: include/crown/planner/search.hpp.
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

enum class SearchPolicy { strict, best_found };
enum class ProofAlgorithm { partition_v1, partition_v2 };
enum class AccountingVersion { continuation_v1 };

// Finite counters never wrap. Exhaustion is an explicit terminal reason.
// Time below is ACTIVE execution time, excluding time between advance calls.
struct PhaseCeiling {
  std::optional<std::uint64_t> work = 5'000'000;
  std::optional<std::chrono::nanoseconds> active_time;
};
struct ContinuationLimits {
  PhaseCeiling producer;
  PhaseCeiling replay;
  // Explicit heap-frame depth, including partition/selection/validation frames.
  // Not C++ stack depth. Zero stops nonempty input before its first frame push.
  std::optional<std::size_t> logical_depth = 256;
};
struct SearchOptions {
  SearchPolicy policy = SearchPolicy::strict;
  ContinuationLimits limits;
  // Production search uses P04 v2. V1 remains a private baseline, not a public
  // algorithm-switch flag. Independent replay accepts both existing versions.
};
struct ReplayOptions {
  PhaseCeiling limits;
  std::optional<std::size_t> logical_depth = 256;
};
struct WorkQuantum {
  std::uint64_t work = 1;
  std::optional<std::chrono::nanoseconds> active_time;
};

enum class SearchPhase {
  admitted, preprocess, search, build_incumbent, validate_incumbent,
  export_proof, replay, complete, failed, cancelled, moved_from
};
enum class ReplayPhase {
  admitted, dispatch, validate_upper, build_scopes, classify_scope_orbits,
  index_claims, order_claims, prove_claim, match_root, complete,
  failed, cancelled, moved_from
};
enum class StopReason {
  none, quantum_work, quantum_time, total_work, total_time, depth_limit,
  allocation_failure, counter_overflow, invalid_quantum,
  invalid_certificate, internal_failure, complete, cancelled, moved_from
};
enum class BoundEvidence { universal, independently_checked };
enum class ResultKind { unfinished, verified_optimum, verified_infeasible, failed };
enum class LimitChange { applied, not_monotone, below_consumed, invalid, terminal };

struct WorkCounters {
  std::uint64_t attempted = 0;
  std::uint64_t committed_transitions = 0;
  std::uint64_t allocation_failures = 0;
  std::uint64_t active_nanoseconds = 0; // Saturating diagnostic, not proof data.
  std::size_t current_depth = 0;
  std::size_t peak_depth = 0;
};
struct HeightInterval {
  // null lower ONLY for independently proved infeasibility (empty family).
  // Otherwise zero for empty body, at least one for nonempty body.
  std::optional<std::size_t> lower;
  // Present iff a complete independent P02 check established this upper bound.
  std::optional<std::size_t> upper;
  BoundEvidence lower_evidence = BoundEvidence::universal;
  bool infeasible = false;
};
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
struct ReplayProgress {
  ReplayPhase phase = ReplayPhase::admitted;
  StopReason last_stop = StopReason::none;
  bool complete = false;
  bool valid = false; // True ONLY after all claims AND root check complete.
  std::size_t checked_claims = 0;
  WorkCounters work;
  std::uint64_t limit_revision = 0;
};

// Returned by value so advance never allocates to report a stop. With zero work
// (or zero quantum time), stopped_for is a quantum reason but progress is bitwise
// unchanged: not even last_stop, time, or counters are changed in the machine.
struct SearchAdvance { StopReason stopped_for; SearchProgress progress; };
struct ReplayAdvance { StopReason stopped_for; ReplayProgress progress; };

// Immutable owned exact binding. No default construction or caller mutation.
// Creation validates Catalog/Query; canonical binding serialization is explicit
// IO work, not hidden in advance. Getters require valid() after a move.
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
  // Empty under strict policy. Copying a present owning handle allocates nothing.
  std::optional<ValidatedIncumbent> incumbent() const noexcept;
  std::optional<VerifiedOptimum> optimum() const noexcept;
  std::optional<VerifiedInfeasible> infeasibility() const noexcept;
  // Resource-only change: all ceilings must increase or remain unchanged.
  // null means unbounded and cannot be changed back to finite.
  LimitChange raise_limits(ContinuationLimits) noexcept;
  void cancel() noexcept; // terminal, release drafts/frames; retain published handles
 private:
  struct Impl;
  explicit ExactSearch(std::unique_ptr<Impl>) noexcept;
  std::unique_ptr<Impl> data_;
};

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
