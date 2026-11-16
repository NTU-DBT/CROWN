#pragma once

// Isolated design proposal. Not part of crown_core; P07 remains not_started.
#include "continuation_machine.hpp"

#include <cstdint>
#include <exception>
#include <memory>
#include <optional>

namespace crown::planner::alternatives_proposal {

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
  const char* what() const noexcept override { return "proposal generator content limit"; }
};
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
struct GeneratorStatistics {
  std::uint64_t completed_steps = 0;
  std::uint64_t topologies_examined = 0;
  std::uint64_t topology_survivors = 0;
  std::uint64_t drafts_ready = 0;
  std::uint64_t drafts_consumed = 0;
  std::size_t peak_depth = 0;
};

class NormalFormGenerator {
 public:
  // Preconditions: nonnull, admitted/validated binding and nonnull budget.
  // target_native_height is supplied by the future original-proof facade;
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
  // Acknowledge only after the future P02/height/key gate has finished or
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
}  // namespace crown::planner::alternatives_proposal
