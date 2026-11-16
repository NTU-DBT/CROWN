#pragma once

#include "continuation_machine.hpp"

#include <cstdint>
#include <exception>
#include <memory>
#include <optional>

namespace crown::planner::candidate_detail {

enum class GeneratorEvent { advanced, draft_ready, exhausted, stopped };
enum class GeneratorStop { none, depth_limit, record_limit, cell_limit, counter_overflow };
struct Step {
  GeneratorEvent event = GeneratorEvent::advanced;
  GeneratorStop reason = GeneratorStop::none;
  std::size_t requested_depth = 0;
};
struct ContentLimits {
  std::optional<std::uint64_t> records;
  std::optional<std::uint64_t> cells;
};
// Every content preparation failure uses this type. bad_alloc is not translated.
struct ContentStop final : std::exception {
  GeneratorStop reason;
  explicit ContentStop(GeneratorStop value) noexcept : reason(value) {}
  const char* what() const noexcept override { return "candidate generator content limit"; }
};
// Cumulative logical construction only; never allocator-byte accounting.
// Failed allocations commit no charge; discarded/consumed content is not refunded.
// Operations may relocate vectors or compare sets, so a cell is not a fixed
// physical-time unit. Admission binding copies, P02 scratch, capacity, allocator
// metadata, scalar/string widths and caller-retained history are excluded.
class ContentBudget {
 public:
  explicit ContentBudget(ContentLimits = {}) noexcept;
  void prepare(std::uint64_t records, std::uint64_t cells) const;
  // Call only after matching prepare and successful allocation, without any
  // intervening budget mutation. Shared owners are serialized by the facade.
  void commit(std::uint64_t records, std::uint64_t cells) noexcept;
  bool raise_limits(ContentLimits) noexcept;
  ContentLimits limits() const noexcept;
  std::uint64_t records() const noexcept;
  std::uint64_t cells() const noexcept;
 private:
  ContentLimits limits_;
  std::uint64_t records_ = 0;
  std::uint64_t cells_ = 0;
};
// Committed enumeration activity only; draft publication is not P02 authority.
// drafts_consumed <= guarded drafts_ready; blocked pushes own no new frame.
struct GeneratorStatistics {
  std::uint64_t completed_steps = 0;
  std::uint64_t topologies_examined = 0;
  std::uint64_t topology_survivors = 0;
  std::uint64_t drafts_ready = 0;
  std::uint64_t drafts_consumed = 0;
  std::size_t peak_depth = 0;
};

// Enumerates labeled roots/parents, then dynamic native-anchor subset digits.
// No fixed-width subset masks, power-set cardinality or query-size cutoff.
// Charges: a record for each control frame/tree shell; a record and cell for
// scope containers, node states, subset digits, DFS pushes and draft nodes;
// a cell for each scope variable, dynamic bit or child edge. Rewrites are free.
// Logical depth is the owned control frame plus saved DFS frames; a requested
// but blocked push does not own a frame. Every draft still requires P02 checking.
// Local family argument: planner_proofs.md, Complete normal-form family (P03).
// Topology DFS scans every label as a potential child for each active frame;
// dynamic subset bits avoid a 64-bit cutoff but not exponential total work.
class NormalFormGenerator {
 public:
  // Preconditions: nonnull, admitted/validated binding and nonnull budget.
  // target_native_height is supplied by the original-proof facade;
  // this integer confers NO authority. Construction creates only an inert shell.
  NormalFormGenerator(std::shared_ptr<const continuation_detail::BindingData>,
                      std::size_t target_native_height, std::shared_ptr<ContentBudget>);
  ~NormalFormGenerator();
  NormalFormGenerator(NormalFormGenerator&&) noexcept;
  NormalFormGenerator& operator=(NormalFormGenerator&&) noexcept;
  NormalFormGenerator(const NormalFormGenerator&) = delete;
  NormalFormGenerator& operator=(const NormalFormGenerator&) = delete;
  Step step(const continuation_detail::UnitContext&);
  std::shared_ptr<const FreeConnexTree> draft() const noexcept;
  // Acknowledge only after the P02/height/key gate has finished or
  // rejected this draft. Repeated step calls cannot bypass acknowledgement.
  void consume_draft() noexcept;
  const GeneratorStatistics& statistics() const noexcept;
  std::size_t current_depth() const noexcept;
  bool cancelled() const noexcept;
  void cancel() noexcept;
 private:
  struct Impl;
  std::unique_ptr<Impl> data_;
};
}  // namespace crown::planner::candidate_detail
