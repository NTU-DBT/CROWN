#pragma once
// Keyed exact-set engine for arbitrary (including cyclic) conjunctive queries:
// the support-count algorithm of runtime::fallback (docs/fallback.md) over the
// keyed core (docs/keyed_core.md). Rows keep their typed values at any width;
// every index, view count, support count and answer is a fixed-width Key
// entry. An event is prepared without touching committed state and then
// published without failure, so a failed or abandoned event changes nothing.
#include "crown/ir/model.hpp"
#include "crown/storage/keyed.hpp"

#include <memory>
#include <optional>
#include <string>
#include <string_view>

namespace crown::runtime::keyed {

struct CyclicOptions {
  storage::keyed::GcOptions gc{};
  // Index capacity plus interned keys (MemoryFailure(limit) before mutating).
  std::size_t memory_limit_bytes = static_cast<std::size_t>(-1);
  // Distinct retained answers and retained source rows (Error before publishing).
  std::uint64_t answer_limit = UINT64_MAX, source_row_limit = UINT64_MAX;
  // Candidate rows visited, keys probed and witnesses counted per event.
  std::optional<std::uint64_t> work_limit{};
  // Generalized hypertree decomposition (docs/keyed_core.md): when the atoms
  // split into bags whose bag-level query is free-connex acyclic, each
  // multi-atom bag keeps its own join (all bag variables) on a support-count
  // engine and the bag-level query runs on the keyed set engine (SetEngine),
  // fed by the bags' tuple changes. Same answers and answer changes; the
  // environment variable CROWN_CYCLIC_ENGINE=support disables it.
  bool decompose = true;
  // Support-count plan: a minimal connected prefix covering the head, the
  // other occurrences counted by residual views (true), or every occurrence
  // in the enumerated prefix (false: no views; GHD bags use this, so a bag
  // projected onto few variables never materializes a wide residual view).
  bool residual_views = true;
};
struct CyclicMetrics {
  std::uint64_t work = 0, row_visits = 0, term_tests = 0, assignments = 0;
  std::uint64_t witnesses = 0, added = 0, removed = 0;
};
class AnswerSink {
 public:
  virtual ~AnswerSink() = default;
  // An answer that appears (insert) or disappears (erase) with the prepared
  // event; head values are borrowed for the call.
  virtual void answer(SetOperation operation, storage::RowView head) = 0;
};

class CyclicEngine {
 public:
  // Empty when supported, else the first unsupported feature.
  [[nodiscard]] static std::string unsupported(const Catalog& catalog, const Query& query);
  CyclicEngine(const Catalog& catalog, const Query& query, CyclicOptions options = {});
  ~CyclicEngine();
  CyclicEngine(const CyclicEngine&) = delete;
  CyclicEngine& operator=(const CyclicEngine&) = delete;

  // Phase 1 (fallible, committed state untouched): the source change and its
  // answer changes, reported to `sink`. Returns false for a duplicate insert
  // or an absent erase (nothing is pending then).
  bool prepare(TableId table, SetOperation operation, storage::RowView row, AnswerSink* sink, CyclicMetrics* metrics = nullptr);
  // Phase 2: apply the pending event. Never fails.
  void publish() noexcept;
  // Drop the pending event (also after a failed prepare).
  void discard() noexcept;
  [[nodiscard]] bool pending() const noexcept;

  [[nodiscard]] std::size_t answers() const noexcept;
  [[nodiscard]] bool has_answer() const noexcept;
  void snapshot(AnswerSink& sink) const;
  [[nodiscard]] std::uint64_t rows(TableId table) const;
  [[nodiscard]] bool contains(TableId table, storage::RowView row) const;
  // Every retained source row, by table.
  [[nodiscard]] Database sources() const;
  [[nodiscard]] std::span<const ScalarType> result_types() const noexcept;
  [[nodiscard]] storage::keyed::Collector& collector() noexcept;
  void collect();
  void check_invariants() const;
  // "ghd" (bags + keyed set engine) or "support" (one support-count engine).
  [[nodiscard]] std::string_view algorithm() const noexcept;

 private:
  struct Impl;
  struct Ghd;
  std::unique_ptr<Impl> impl_;
  std::unique_ptr<Ghd> ghd_;
};

}  // namespace crown::runtime::keyed
