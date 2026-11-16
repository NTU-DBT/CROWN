#include "residual_machine.hpp"
#include "producer_cursor.hpp"

namespace crown::planner::residual_detail {
namespace pp = cd::producer_private;
struct ReductionMachine::Impl {
  std::shared_ptr<const cd::BindingData> binding;
  std::shared_ptr<ConstructionBudget> budget;
  std::shared_ptr<ResidualTraceRecord> draft;
  std::shared_ptr<const ResidualTraceRecord> result;
  std::shared_ptr<std::vector<std::size_t>> terminal_members;
  std::unique_ptr<InducedViewMachine> induced;
  std::vector<unsigned char> live;
  std::vector<std::size_t> counts;
  VariableSet original_head;
  ResidualLayer layer;
  EarRecord ear;
  ResidualStatistics stats;
  ResidualPhase phase = ResidualPhase::admitted;
  pp::Engine engine;
  pp::Task task;
  cd::UnitContext context;
  bool started = false;
  Impl(std::shared_ptr<const cd::BindingData> b, std::shared_ptr<ConstructionBudget> c)
      : binding(std::move(b)), budget(std::move(c)) {}
  ~Impl() { engine.cancel(); }
  template<class T, class U> void append(std::vector<T>& out, U&& value, std::uint64_t records = 0) {
    budget->prepare(records, 1); out.push_back(std::forward<U>(value)); budget->commit(records, 1);
  }
  void insert(VariableSet& out, VariableId v) {
    if (out.contains(v)) return;
    budget->prepare(0, 1); out.insert(v); budget->commit(0, 1);
  }
  static void increment(std::uint64_t& n) {
    if (n == std::numeric_limits<std::uint64_t>::max()) throw Limited(ResidualStopReason::counter_overflow);
    ++n;
  }
  // P2 arXiv:2603.14754v1, Section 2.1.4, Definition 2.9 and Algorithm 1
  // supply the frozen-ear recipe; ascending-ID tie-breaking and resumable
  // record publication are local choices. Round counts do not prove height.
  // Actual work includes variable-pair/member tests, all anchor pairs and
  // repeated frozen-support scans, plus an independent terminal-view copy.
  pp::Task run() {
#define RED_OP(...) co_await pp::operation([&] { __VA_ARGS__; }, binding->query.atoms.empty() ? 0 : 1)
    RED_OP(budget->prepare(1, 0); draft = std::make_shared<ResidualTraceRecord>(); budget->commit(1, 0));
    phase = ResidualPhase::scopes;
    RED_OP(budget->prepare(0, 0); draft->layers.reserve(binding->query.atoms.size()));
    RED_OP(budget->prepare(0, 0); draft->original_scopes.reserve(binding->query.atoms.size()));
    RED_OP(budget->prepare(0, 0); live.reserve(binding->query.atoms.size()));
    RED_OP(budget->prepare(0, 0); counts.reserve(binding->query.variables.size()));
    for (std::size_t a = 0; a < binding->query.atoms.size(); ++a) {
      RED_OP(append(draft->original_scopes, VariableSet{}, 1));
      RED_OP(append(live, static_cast<unsigned char>(1)));
      for (const auto& term : binding->query.atoms[a].terms) {
        RED_OP(if (const auto* v = std::get_if<VariableId>(&term)) insert(draft->original_scopes[a], *v));
      }
    }
    for (std::size_t v = 0; v < binding->query.variables.size(); ++v) {
      RED_OP(append(counts, std::size_t{0}));
    }
    for (const auto& h : binding->query.head) { RED_OP(insert(original_head, h.variable)); }
    bool terminal = false;
    while (!terminal) {
      // The previous layer has been moved into the trace; this empty draft has
      // its own logical record charge even when recognition ends reduction.
      RED_OP(budget->prepare(1, 0); budget->commit(1, 0));
      RED_OP(budget->prepare(0, 0); layer.members.reserve(live.size()));
      for (std::size_t a = 0; a < live.size(); ++a) {
        RED_OP(if (live[a]) append(layer.members, a));
      }
      for (std::size_t v = 0; v < counts.size(); ++v) { RED_OP(counts[v] = 0); }
      for (const auto a : layer.members) {
        RED_OP((void)a);
        for (const auto v : draft->original_scopes[a]) {
          RED_OP(++counts[v.value]);
        }
      }
      for (std::size_t v = 0; v < counts.size(); ++v) {
        RED_OP((void)v);
        if (!counts[v]) continue;
        RED_OP(insert(layer.variables, VariableId{v}));
        if (counts[v] == 1) { RED_OP(insert(layer.unique, VariableId{v})); }
        if (original_head.contains(VariableId{v})) { RED_OP(insert(layer.head, VariableId{v})); }
      }
      phase = ResidualPhase::recognize;
      if (layer.members.empty()) {
        draft->terminal = ResidualTerminal::empty_body;
        terminal = true;
      } else {
        RED_OP(increment(stats.hierarchy_tests));
        bool hierarchical = true;
        for (auto x = layer.variables.begin(); x != layer.variables.end() && hierarchical; ++x) {
          auto y = x; ++y;
          for (; y != layer.variables.end() && hierarchical; ++y) {
            bool overlap = false, x_only = false, y_only = false;
            for (const auto a : layer.members) {
              RED_OP(const bool has_x = draft->original_scopes[a].contains(*x);
                const bool has_y = draft->original_scopes[a].contains(*y);
                overlap = overlap || (has_x && has_y);
                x_only = x_only || (has_x && !has_y);
                y_only = y_only || (has_y && !has_x));
            }
            RED_OP(if (overlap && x_only && y_only) hierarchical = false;
              if (overlap && !x_only && y_only && layer.head.contains(*x) && !layer.head.contains(*y)) hierarchical = false;
              if (overlap && x_only && !y_only && layer.head.contains(*y) && !layer.head.contains(*x)) hierarchical = false);
          }
          RED_OP((void)x);
        }
        if (hierarchical) { draft->terminal = ResidualTerminal::hierarchical; terminal = true; }
      }
      if (terminal) break;
      phase = ResidualPhase::eligibility;
      RED_OP(increment(stats.rounds));
      RED_OP(budget->prepare(0, 0); layer.ears.reserve(layer.members.size()));
      for (const auto e : layer.members) {
        RED_OP(budget->prepare(1, 0); ear.occurrence = e; budget->commit(1, 0));
        bool unique_free = false;
        for (const auto v : draft->original_scopes[e]) {
          RED_OP(if (layer.unique.contains(v)) {
              insert(ear.unique, v); unique_free = unique_free || layer.head.contains(v);
            } else { insert(ear.shared, v); });
        }
        RED_OP(budget->prepare(0, 0); ear.anchors.reserve(layer.members.size()));
        for (const auto a : layer.members) {
          RED_OP((void)a);
          if (e == a) continue;
          RED_OP(increment(stats.eligibility_pairs));
          bool subset = true, free_shared = true;
          for (const auto v : ear.shared) {
            RED_OP(subset = subset && draft->original_scopes[a].contains(v);
                   free_shared = free_shared && layer.head.contains(v));
          }
          const unsigned conditions = (subset && !unique_free ? 1U : 0U) | (subset && free_shared ? 2U : 0U);
          if (conditions) { RED_OP(append(ear.anchors, EarAnchor{a, static_cast<EarCondition>(conditions)}, 1)); }
        }
        if (!ear.anchors.empty()) {
          RED_OP(append(layer.ears, std::move(ear), 1));
          // Move leaves scalar occurrence unspecified for our purposes, while
          // standard-container members are replaced by empty containers.
          ear = EarRecord{};
        } else {
          // Incremental release prevents an unbounded cleanup between yields.
          while (!ear.shared.empty()) { RED_OP(ear.shared.erase(ear.shared.begin())); }
          while (!ear.unique.empty()) { RED_OP(ear.unique.erase(ear.unique.begin())); }
        }
      }
      phase = ResidualPhase::delete_ears;
      RED_OP(budget->prepare(0, 0); layer.deletions.reserve(layer.members.size()));
      bool found = true;
      while (found) {
        found = false;
        for (const auto& e : layer.ears) {
          RED_OP((void)e);
          if (!live[e.occurrence]) continue;
          for (const auto& a : e.anchors) {
            RED_OP((void)a);
            if (!live[a.occurrence]) continue;
            // Preparation/publication precede mutation; failed allocation leaves
            // both liveness and the exact pending pair unchanged for retry.
            RED_OP(if (stats.deletions == std::numeric_limits<std::uint64_t>::max()) throw Limited(ResidualStopReason::counter_overflow);
                   append(layer.deletions, EarDeletion{e.occurrence, a.occurrence}, 1);
                   live[e.occurrence] = 0; ++stats.deletions);
            found = true;
            break;
          }
          if (found) break;
        }
      }
      phase = ResidualPhase::seal_layer;
      RED_OP(budget->prepare(0, 0); layer.remaining.reserve(layer.members.size()));
      for (const auto a : layer.members) { RED_OP(if (live[a]) append(layer.remaining, a)); }
      for (const auto a : layer.remaining) {
        RED_OP((void)a);
        for (const auto v : draft->original_scopes[a]) { RED_OP(if (original_head.contains(v)) insert(layer.residual_head, v)); }
      }
      const bool stalled = layer.deletions.empty();
      RED_OP(append(draft->layers, std::move(layer), 1));
      layer = ResidualLayer{};
      if (stalled) {
        draft->terminal = ResidualTerminal::stalled;
        terminal = true;
      }
    }
    // Build terminal identities independently from the last round's draft.
    RED_OP(budget->prepare(1, 0); terminal_members = std::make_shared<std::vector<std::size_t>>(); budget->commit(1, 0));
    RED_OP(terminal_members->reserve(live.size()));
    RED_OP(budget->prepare(0, 0); draft->terminal_members.reserve(live.size()));
    for (std::size_t a = 0; a < live.size(); ++a) {
      RED_OP((void)a);
      if (!live[a]) continue;
      RED_OP(append(*terminal_members, a));
      RED_OP(append(draft->terminal_members, a));
      for (const auto v : draft->original_scopes[a]) { RED_OP(if (original_head.contains(v)) insert(draft->terminal_head, v)); }
    }
    RED_OP(budget->prepare(1, 0); induced = std::make_unique<InducedViewMachine>(binding, terminal_members, budget); budget->commit(1, 0));
    while (!induced->view()) {
      co_await pp::operation([&] {
        auto child_context = context;
        if (child_context.depth_ceiling && !binding->query.atoms.empty()) --*child_context.depth_ceiling;
        const auto s = induced->step(child_context);
        if (s.event == Event::stopped) throw Limited(s.reason);
      }, binding->query.atoms.empty() ? 0 : 2);
    }
    // Public views are immutable. Copy the completed child's logical cells one
    // at a time rather than hiding a bulk query copy in trace publication.
    const auto view = induced->view();
    auto& out = draft->terminal_view;
    out.query.contradiction = view->query.contradiction;
    RED_OP(budget->prepare(0, 0); out.original_occurrences.reserve(view->original_occurrences.size()));
    for (const auto a : view->original_occurrences) { RED_OP(append(out.original_occurrences, a)); }
    RED_OP(budget->prepare(0, 0); out.original_variables.reserve(view->original_variables.size()));
    for (const auto v : view->original_variables) { RED_OP(append(out.original_variables, v)); }
    RED_OP(budget->prepare(0, 0); out.occurrence_to_local.reserve(view->occurrence_to_local.size()));
    for (const auto a : view->occurrence_to_local) { RED_OP(append(out.occurrence_to_local, a)); }
    RED_OP(budget->prepare(0, 0); out.variable_to_local.reserve(view->variable_to_local.size()));
    for (const auto v : view->variable_to_local) { RED_OP(append(out.variable_to_local, v)); }
    RED_OP(budget->prepare(0, 0); out.query.variables.reserve(view->query.variables.size()));
    for (const auto& v : view->query.variables) { RED_OP(append(out.query.variables, v, 1)); }
    RED_OP(budget->prepare(0, 0); out.query.head.reserve(view->query.head.size()));
    for (const auto& h : view->query.head) { RED_OP(append(out.query.head, h, 1)); }
    RED_OP(budget->prepare(0, 0); out.query.atoms.reserve(view->query.atoms.size()));
    for (const auto& a : view->query.atoms) {
      RED_OP(budget->prepare(1, 1); out.query.atoms.push_back(Atom{a.occurrence, a.table, {}}); budget->commit(1, 1));
      RED_OP(budget->prepare(0, 0); out.query.atoms.back().terms.reserve(a.terms.size()));
      for (const auto& t : a.terms) { RED_OP(append(out.query.atoms.back().terms, t)); }
    }
    RED_OP(result = draft; phase = ResidualPhase::complete);
#undef RED_OP
  }
};
ReductionMachine::ReductionMachine(std::shared_ptr<const cd::BindingData> b, std::shared_ptr<ConstructionBudget> c)
    : data_(std::make_unique<Impl>(std::move(b), std::move(c))) {}
ReductionMachine::~ReductionMachine() = default;
ReductionMachine::ReductionMachine(ReductionMachine&&) noexcept = default;
ReductionMachine& ReductionMachine::operator=(ReductionMachine&&) noexcept = default;
Step ReductionMachine::step(const cd::UnitContext& ctx) {
  auto& d = *data_;
  if (d.result) return {Event::complete};
  if (!ctx.permits(current_depth())) return {Event::stopped, ResidualStopReason::depth_limit, StopReason::none, current_depth()};
  d.context = ctx;
  if (!d.started) { d.budget->prepare(1, 0); d.task = d.run(); d.engine.start(d.task); d.started = true; d.budget->commit(1, 0); return {}; }
  const auto s = d.engine.step(ctx);
  if (s.event == cd::UnitEvent::depth_blocked) return {Event::stopped, ResidualStopReason::depth_limit, StopReason::none, s.requested_depth};
  return {d.result ? Event::complete : Event::advanced};
}
ResidualPhase ReductionMachine::phase() const noexcept { return data_->phase; }
const ResidualStatistics& ReductionMachine::statistics() const noexcept { return data_->stats; }
std::size_t ReductionMachine::current_depth() const noexcept {
  if (data_->result || data_->binding->query.atoms.empty()) return 0;
  return 1 + (data_->induced && !data_->induced->view() ? data_->induced->current_depth() : 0);
}
std::shared_ptr<const ResidualTraceRecord> ReductionMachine::trace_record() const noexcept { return data_->result; }
} // namespace crown::planner::residual_detail
