#pragma once

#include "crown/planner/search.hpp"
#include "crown/planner/verify.hpp"

#include <memory>
#include <optional>
#include <string_view>

namespace crown::planner::continuation_detail {

// Validated input is copied/moved exactly once at facade admission. Machines
// share this immutable ownership, never references into caller-owned inputs.
struct BindingData {
  Catalog catalog;
  Query query;
  AccountingVersion accounting = AccountingVersion::continuation_v1;
};

// Only ValidationMachine constructs checked upper authority. A complete tree
// and complete report stay alive without copying either during publication.
struct CheckedUpper {
  std::shared_ptr<const BindingData> binding;
  std::shared_ptr<const FreeConnexTree> tree;
  std::shared_ptr<const ValidationReport> report;
  std::size_t height = 0;
};
struct CheckedProof {
  std::shared_ptr<const BindingData> binding;
  std::shared_ptr<const HeightCertificate> proof;
  std::shared_ptr<const CheckedUpper> upper;
};
struct IncumbentData { std::shared_ptr<const CheckedUpper> upper; };
struct OptimumData {
  std::shared_ptr<const IncumbentData> upper;
  std::shared_ptr<const HeightCertificate> proof;
};
struct InfeasibleData {
  std::shared_ptr<const BindingData> binding;
  std::shared_ptr<const HeightCertificate> proof;
};
struct CheckedCertificateData {
  std::shared_ptr<const CheckedProof> checked;
  std::shared_ptr<const OptimumData> optimum;
  std::shared_ptr<const InfeasibleData> infeasibility;
};

enum class UnitEvent {
  advanced, candidate_ready, producer_complete, witness_complete,
  upper_valid, upper_invalid, proof_valid, proof_invalid, depth_blocked
};
struct UnitResult {
  UnitEvent event = UnitEvent::advanced;
  std::size_t requested_depth = 0;
};
struct UnitContext {
  std::optional<std::size_t> depth_ceiling;
  [[nodiscard]] bool permits(std::size_t desired) const noexcept {
    return !depth_ceiling || desired <= *depth_ceiling;
  }
};

// step performs one saved cursor transition. Constructors allocate only inert
// shells; no bulk preprocessing, search, validation or replay is hidden there.
// Throwing preparation precedes nonthrowing cursor publication. bad_alloc may
// escape step and leaves the same logical next transition retryable. The facade
// alone charges work/time; delegated child steps must not double-charge.
class ValidationMachine {
 public:
  ValidationMachine(std::shared_ptr<const BindingData>, std::shared_ptr<const FreeConnexTree>);
  ~ValidationMachine();
  ValidationMachine(ValidationMachine&&) noexcept;
  ValidationMachine& operator=(ValidationMachine&&) noexcept;
  ValidationMachine(const ValidationMachine&) = delete;
  ValidationMachine& operator=(const ValidationMachine&) = delete;
  UnitResult step(const UnitContext&);
  const ValidationReport& report() const noexcept;
  std::shared_ptr<const CheckedUpper> checked() const noexcept;
  std::size_t current_depth() const noexcept;
 private:
  struct Impl;
  std::unique_ptr<Impl> data_;
};

// Producer choices and partition/scoping cursors remain private to exact.cpp.
// Replay shares no producer metadata, hierarchy, symmetry or enumeration code.
struct FrozenCandidate;
// Exclusive producer protocol: retain pending candidates through witness/P02 publication,
// then accept the upper and acknowledge. Exported proof needs independent replay. See
// docs/planner_continuations.md, authority.
class ProducerMachine {
 public:
  explicit ProducerMachine(std::shared_ptr<const BindingData>);
  ~ProducerMachine();
  ProducerMachine(ProducerMachine&&) noexcept;
  ProducerMachine& operator=(ProducerMachine&&) noexcept;
  ProducerMachine(const ProducerMachine&) = delete;
  ProducerMachine& operator=(const ProducerMachine&) = delete;
  UnitResult step(const UnitContext&);
  SearchPhase phase() const noexcept;
  const SearchStatistics& statistics() const noexcept;
  std::size_t current_depth() const noexcept;
  std::shared_ptr<const FrozenCandidate> candidate() const noexcept;
  // The facade retains candidate ownership until validation/publication succeeds.
  void accept_upper(std::shared_ptr<const CheckedUpper>) noexcept;
  void acknowledge_candidate() noexcept;
  std::shared_ptr<const HeightCertificate> completed_proof() const noexcept;
 private:
  struct Impl;
  std::unique_ptr<Impl> data_;
};
// Own candidate-to-tree copying across retries; returned complete tree ownership still needs
// P02 validation before becoming an upper. See docs/planner_continuations.md, authority.
class WitnessMachine {
 public:
  WitnessMachine(std::shared_ptr<const BindingData>, std::shared_ptr<const FrozenCandidate>);
  ~WitnessMachine();
  WitnessMachine(WitnessMachine&&) noexcept;
  WitnessMachine& operator=(WitnessMachine&&) noexcept;
  WitnessMachine(const WitnessMachine&) = delete;
  WitnessMachine& operator=(const WitnessMachine&) = delete;
  UnitResult step(const UnitContext&);
  std::size_t current_depth() const noexcept;
  std::shared_ptr<const FreeConnexTree> tree() const noexcept;
 private:
  struct Impl;
  std::unique_ptr<Impl> data_;
};
// Independent replay publishes an owning CheckedProof only after whole-root success;
// phase/counters/message are observations. See docs/planner_continuations.md, authority.
class ReplayMachine {
 public:
  ReplayMachine(std::shared_ptr<const BindingData>, std::shared_ptr<const HeightCertificate>);
  ~ReplayMachine();
  ReplayMachine(ReplayMachine&&) noexcept;
  ReplayMachine& operator=(ReplayMachine&&) noexcept;
  ReplayMachine(const ReplayMachine&) = delete;
  ReplayMachine& operator=(const ReplayMachine&) = delete;
  UnitResult step(const UnitContext&);
  ReplayPhase phase() const noexcept;
  std::size_t current_depth() const noexcept;
  std::size_t checked_claims() const noexcept;
  std::string_view message() const noexcept;
  std::shared_ptr<const CheckedProof> checked() const noexcept;
 private:
  struct Impl;
  std::unique_ptr<Impl> data_;
};
}  // namespace crown::planner::continuation_detail
