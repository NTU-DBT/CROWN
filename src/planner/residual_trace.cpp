#include "residual_machine.hpp"
#include "producer_cursor.hpp"
#include <chrono>
#include <limits>
#include <stdexcept>

namespace crown::planner::residual_detail {
namespace cursor = cd::producer_private;
// Independent replay uses original terms and its own scopes/incidences/pairs,
// sharing only the suspension mechanism with the producer. Successful replay
// proves trace consistency, never a tree upper or original minimum height.
struct TraceReplayMachine::Impl {
  std::shared_ptr<const cd::BindingData> binding;
  std::shared_ptr<const ResidualTraceRecord> claim;
  std::shared_ptr<ConstructionBudget> budget;
  cursor::Engine engine;
  cursor::Task root;
  ResidualTraceReport result;
  bool finished = false;
  std::vector<VariableSet> scopes;
  VariableSet original_head, variables, head, unique;
  std::vector<std::size_t> members, counts;
  std::vector<unsigned char> live;
  struct Pair { std::size_t ear, anchor; unsigned bits; };
  std::vector<Pair> pairs;
  bool hierarchical = true;
  Impl(std::shared_ptr<const cd::BindingData> b, std::shared_ptr<const ResidualTraceRecord> c,
       std::shared_ptr<ConstructionBudget> cap) : binding(std::move(b)), claim(std::move(c)), budget(std::move(cap)) {}
  ~Impl() { engine.cancel(); }
  auto tick() { return cursor::operation([] {}); }
  void fail(ResidualTraceRule rule) noexcept { result.rule = rule; }
  template<class T> void append(std::vector<T>& out, const T& value, std::uint64_t cells = 1) {
    budget->prepare(1, cells); out.push_back(value); budget->commit(1, cells);
  }
  void insert(VariableSet& out, VariableId value) {
    if (out.contains(value)) return;
    budget->prepare(1, 1); out.insert(value); budget->commit(1, 1);
  }
  template<class A, class B> cursor::Task equal(const A& a, const B& b, ResidualTraceRule rule) {
    co_await tick();
    if (a.size() != b.size()) { fail(rule); co_return; }
    auto x = a.begin(); auto y = b.begin();
    for (; x != a.end(); ++x, ++y) {
      co_await tick();
      if (*x != *y) { fail(rule); co_return; }
    }
  }
  // Rebuild incidence independently, scanning all ordered variable pairs and
  // all current members even after a hierarchy violation is known. Container
  // clear/destruction is cleanup cost outside the scalar transition account.
  cursor::Task derive() {
    variables.clear(); head.clear(); unique.clear(); counts.clear();
    for (std::size_t v = 0; v < binding->query.variables.size(); ++v)
      co_await cursor::operation([&] { append(counts, std::size_t{0}); });
    for (auto m : members) for (auto v : scopes[m]) {
      co_await cursor::operation([&] { insert(variables, v); });
      co_await tick(); ++counts[v.value];
    }
    for (auto v : variables) {
      if (original_head.contains(v)) co_await cursor::operation([&] { insert(head, v); });
      if (counts[v.value] == 1) co_await cursor::operation([&] { insert(unique, v); });
      co_await tick();
    }
    hierarchical = true;
    for (auto x : variables) for (auto y : variables) {
      bool overlap = false, xonly = false, yonly = false;
      for (auto m : members) {
        co_await tick();
        const bool a = scopes[m].contains(x), b = scopes[m].contains(y);
        overlap |= a && b; xonly |= a && !b; yonly |= b && !a;
      }
      co_await tick();
      if ((overlap && xonly && yonly) || (!xonly && yonly && head.contains(x) && !head.contains(y))) hierarchical = false;
    }
  }
  cursor::Task view() {
    const auto& v = claim->terminal_view;
    const auto& q = binding->query;
    cursor::Task child;
    co_await cursor::operation([&] { budget->prepare(1, 0); auto next = equal(v.original_occurrences, members, ResidualTraceRule::mapping); budget->commit(1, 0); child = std::move(next); }, engine.depth + 1); co_await child;
    if (result.rule != ResidualTraceRule::none) co_return;
    co_await cursor::operation([&] { budget->prepare(1, 0); auto next = equal(v.original_variables, variables, ResidualTraceRule::mapping); budget->commit(1, 0); child = std::move(next); }, engine.depth + 1); co_await child;
    if (result.rule != ResidualTraceRule::none) co_return;
    co_await tick();
    if (v.occurrence_to_local.size() != q.atoms.size() || v.variable_to_local.size() != q.variables.size()) { fail(ResidualTraceRule::mapping); co_return; }
    std::size_t local = 0;
    for (std::size_t i = 0; i < q.atoms.size(); ++i) {
      co_await tick();
      const bool present = local < members.size() && members[local] == i;
      if (present ? v.occurrence_to_local[i] != std::optional<std::size_t>(local) : v.occurrence_to_local[i].has_value()) { fail(ResidualTraceRule::mapping); co_return; }
      if (present) ++local;
    }
    local = 0;
    for (std::size_t i = 0; i < q.variables.size(); ++i) {
      co_await tick(); const bool present = variables.contains(VariableId{i});
      if (present ? v.variable_to_local[i] != std::optional<VariableId>(VariableId{local}) : v.variable_to_local[i].has_value()) { fail(ResidualTraceRule::mapping); co_return; }
      if (present) ++local;
    }
    co_await tick();
    if (v.query.variables.size() != variables.size() || v.query.atoms.size() != members.size() || v.query.contradiction != q.contradiction) { fail(ResidualTraceRule::query); co_return; }
    local = 0;
    for (auto id : variables) {
      co_await tick(); const auto& a = q.variables[id.value]; const auto& b = v.query.variables[local++];
      if (a.name != b.name || a.type != b.type) { fail(ResidualTraceRule::query); co_return; }
    }
    for (std::size_t i = 0; i < members.size(); ++i) {
      result.occurrence = members[i];
      const auto& a = q.atoms[members[i]]; const auto& b = v.query.atoms[i];
      co_await tick();
      if (a.occurrence != b.occurrence || a.table != b.table || a.terms.size() != b.terms.size()) { fail(ResidualTraceRule::query); co_return; }
      for (std::size_t j = 0; j < a.terms.size(); ++j) {
        co_await tick();
        if (a.terms[j].index() != b.terms[j].index()) { fail(ResidualTraceRule::query); co_return; }
        if (const auto* id = std::get_if<VariableId>(&a.terms[j])) {
          if (std::get<VariableId>(b.terms[j]) != *v.variable_to_local[id->value]) { fail(ResidualTraceRule::query); co_return; }
        } else if (const auto* value = std::get_if<Value>(&a.terms[j])) {
          if (*value != std::get<Value>(b.terms[j])) { fail(ResidualTraceRule::query); co_return; }
        }
      }
    }
    result.occurrence.reset(); local = 0;
    for (const auto& out : q.head) {
      co_await tick();
      if (!variables.contains(out.variable)) continue;
      if (local >= v.query.head.size() || v.query.head[local].variable != *v.variable_to_local[out.variable.value] || v.query.head[local].alias != out.alias) { fail(ResidualTraceRule::query); co_return; }
      ++local;
    }
    co_await tick(); if (local != v.query.head.size()) fail(ResidualTraceRule::query);
  }
  cursor::Task run() {
    co_await tick(); if (claim->version != 1) { fail(ResidualTraceRule::version); co_return; }
    const auto& q = binding->query;
    for (std::size_t i = 0; i < q.atoms.size(); ++i) {
      co_await cursor::operation([&] { append(scopes, VariableSet{}, 0); });
      for (const auto& term : q.atoms[i].terms) {
        co_await tick();
        if (const auto* id = std::get_if<VariableId>(&term)) co_await cursor::operation([&] { insert(scopes.back(), *id); });
      }
      co_await cursor::operation([&] { append(members, i); });
      co_await cursor::operation([&] { append(live, static_cast<unsigned char>(1)); });
    }
    for (const auto& out : q.head) co_await cursor::operation([&] { insert(original_head, out.variable); });
    co_await tick(); if (claim->original_scopes.size() != scopes.size()) { fail(ResidualTraceRule::scopes); co_return; }
    cursor::Task child;
    for (std::size_t i = 0; i < scopes.size(); ++i) {
      result.occurrence = i;
      co_await cursor::operation([&] { budget->prepare(1, 0); auto next = equal(scopes[i], claim->original_scopes[i], ResidualTraceRule::scopes); budget->commit(1, 0); child = std::move(next); }, engine.depth + 1); co_await child;
      if (result.rule != ResidualTraceRule::none) co_return;
    }
    result.occurrence.reset();
    co_await cursor::operation([&] { budget->prepare(1, 0); auto next = derive(); budget->commit(1, 0); child = std::move(next); }, engine.depth + 1); co_await child;
    bool stalled = false;
    for (std::size_t round = 0; round < claim->layers.size(); ++round) {
      result.layer = round;
      co_await tick(); if (hierarchical || stalled) { fail(ResidualTraceRule::terminal); co_return; }
      const auto& layer = claim->layers[round];
      co_await cursor::operation([&] { budget->prepare(1, 0); auto next = equal(members, layer.members, ResidualTraceRule::membership); budget->commit(1, 0); child = std::move(next); }, engine.depth + 1); co_await child;
      if (result.rule != ResidualTraceRule::none) co_return;
      co_await cursor::operation([&] { budget->prepare(1, 0); auto next = equal(variables, layer.variables, ResidualTraceRule::variables); budget->commit(1, 0); child = std::move(next); }, engine.depth + 1); co_await child;
      if (result.rule != ResidualTraceRule::none) co_return;
      co_await cursor::operation([&] { budget->prepare(1, 0); auto next = equal(head, layer.head, ResidualTraceRule::head); budget->commit(1, 0); child = std::move(next); }, engine.depth + 1); co_await child;
      if (result.rule != ResidualTraceRule::none) co_return;
      co_await cursor::operation([&] { budget->prepare(1, 0); auto next = equal(unique, layer.unique, ResidualTraceRule::unique); budget->commit(1, 0); child = std::move(next); }, engine.depth + 1); co_await child;
      if (result.rule != ResidualTraceRule::none) co_return;
      pairs.clear(); std::size_t ear_index = 0;
      for (auto e : members) {
        result.occurrence = e;
        VariableSet shared, own;
        for (auto x : scopes[e]) co_await cursor::operation([&] { insert(unique.contains(x) ? own : shared, x); });
        std::size_t anchor_index = 0;
        for (auto a : members) {
          co_await tick(); if (e == a) continue;
          result.anchor = a;
          bool first = true, second = true;
          for (auto x : shared) { co_await tick(); first &= scopes[a].contains(x); second &= scopes[a].contains(x) && head.contains(x); }
          for (auto x : own) { co_await tick(); first &= !head.contains(x); }
          const unsigned bits = (first ? 1U : 0U) | (second ? 2U : 0U);
          if (!bits) continue;
          co_await cursor::operation([&] { append(pairs, Pair{e,a,bits}, 3); });
          co_await tick();
          if (ear_index >= layer.ears.size()) { fail(ResidualTraceRule::eligibility); co_return; }
          const auto& ear = layer.ears[ear_index];
          if (ear.occurrence != e || anchor_index >= ear.anchors.size() || ear.anchors[anchor_index].occurrence != a || static_cast<unsigned>(ear.anchors[anchor_index].condition) != bits) { fail(ResidualTraceRule::eligibility); co_return; }
          ++anchor_index;
        }
        result.anchor.reset();
        if (anchor_index) {
          const auto& ear = layer.ears[ear_index];
          co_await tick(); if (ear.anchors.size() != anchor_index) { fail(ResidualTraceRule::eligibility); co_return; }
          co_await cursor::operation([&] { budget->prepare(1, 0); auto next = equal(shared, ear.shared, ResidualTraceRule::eligibility); budget->commit(1, 0); child = std::move(next); }, engine.depth + 1); co_await child;
          if (result.rule != ResidualTraceRule::none) co_return;
          co_await cursor::operation([&] { budget->prepare(1, 0); auto next = equal(own, ear.unique, ResidualTraceRule::eligibility); budget->commit(1, 0); child = std::move(next); }, engine.depth + 1); co_await child;
          if (result.rule != ResidualTraceRule::none) co_return;
          ++ear_index;
        }
      }
      result.occurrence.reset();
      co_await tick(); if (ear_index != layer.ears.size()) { fail(ResidualTraceRule::eligibility); co_return; }
      std::size_t deleted = 0;
      for (;;) {
        const Pair* chosen = nullptr;
        for (const auto& p : pairs) { co_await tick(); if (live[p.ear] && live[p.anchor]) { chosen = &p; break; } }
        if (!chosen) break;
        result.occurrence = chosen->ear; result.anchor = chosen->anchor;
        co_await tick();
        if (deleted >= layer.deletions.size() || layer.deletions[deleted].occurrence != chosen->ear || layer.deletions[deleted].anchor != chosen->anchor) { fail(ResidualTraceRule::deletion); co_return; }
        live[chosen->ear] = 0; ++deleted;
      }
      result.occurrence.reset(); result.anchor.reset();
      co_await tick(); if (deleted != layer.deletions.size()) { fail(ResidualTraceRule::maximal_round); co_return; }
      members.clear();
      for (std::size_t i = 0; i < live.size(); ++i) { co_await tick(); if (live[i]) co_await cursor::operation([&] { append(members, i); }); }
      co_await cursor::operation([&] { budget->prepare(1, 0); auto next = equal(members, layer.remaining, ResidualTraceRule::membership); budget->commit(1, 0); child = std::move(next); }, engine.depth + 1); co_await child;
      if (result.rule != ResidualTraceRule::none) co_return;
      co_await cursor::operation([&] { budget->prepare(1, 0); auto next = derive(); budget->commit(1, 0); child = std::move(next); }, engine.depth + 1); co_await child;
      co_await cursor::operation([&] { budget->prepare(1, 0); auto next = equal(head, layer.residual_head, ResidualTraceRule::head); budget->commit(1, 0); child = std::move(next); }, engine.depth + 1); co_await child;
      if (result.rule != ResidualTraceRule::none) co_return;
      stalled = deleted == 0;
    }
    result.layer.reset();
    co_await cursor::operation([&] { budget->prepare(1, 0); auto next = equal(members, claim->terminal_members, ResidualTraceRule::membership); budget->commit(1, 0); child = std::move(next); }, engine.depth + 1); co_await child;
    if (result.rule != ResidualTraceRule::none) co_return;
    co_await cursor::operation([&] { budget->prepare(1, 0); auto next = equal(head, claim->terminal_head, ResidualTraceRule::head); budget->commit(1, 0); child = std::move(next); }, engine.depth + 1); co_await child;
    if (result.rule != ResidualTraceRule::none) co_return;
    co_await tick();
    const auto expected = q.atoms.empty() ? ResidualTerminal::empty_body : hierarchical ? ResidualTerminal::hierarchical : ResidualTerminal::stalled;
    if (claim->terminal != expected || (!hierarchical && !stalled)) { fail(ResidualTraceRule::terminal); co_return; }
    co_await cursor::operation([&] { budget->prepare(1, 0); auto next = view(); budget->commit(1, 0); child = std::move(next); }, engine.depth + 1); co_await child;
    if (result.rule != ResidualTraceRule::none) co_return;
    result.valid = true;
  }
};
TraceReplayMachine::TraceReplayMachine(std::shared_ptr<const cd::BindingData> b, std::shared_ptr<const ResidualTraceRecord> c, std::shared_ptr<ConstructionBudget> cap)
    : data_(std::make_unique<Impl>(std::move(b), std::move(c), std::move(cap))) {}
TraceReplayMachine::~TraceReplayMachine() = default;
Step TraceReplayMachine::step(const cd::UnitContext& context) {
  auto& d = *data_;
  if (d.finished) return {d.result.valid ? Event::complete : Event::invalid_trace};
  if (d.result.work == std::numeric_limits<std::uint64_t>::max()) throw Limited(ResidualStopReason::counter_overflow);
  ++d.result.work;
  if (!d.binding->query.atoms.empty() && !context.permits(1)) return {Event::stopped, ResidualStopReason::depth_limit, StopReason::none, 1};
  if (!d.root.handle) {
    d.budget->prepare(1, 0); auto task = d.run(); d.budget->commit(1, 0);
    d.root = std::move(task); d.engine.start(d.root);
    d.engine.administrative_only = d.binding->query.atoms.empty();
    return {};
  }
  const auto r = d.engine.step(context);
  if (r.event == cd::UnitEvent::depth_blocked) return {Event::stopped, ResidualStopReason::depth_limit, StopReason::none, r.requested_depth};
  if (!d.engine.active) { d.finished = true; return {d.result.valid ? Event::complete : Event::invalid_trace}; }
  return {};
}
std::size_t TraceReplayMachine::current_depth() const noexcept { return data_->binding->query.atoms.empty() || data_->finished ? 0 : data_->engine.depth; }
ResidualTraceReport TraceReplayMachine::report() const noexcept { return data_->result; }
} // namespace crown::planner::residual_detail

namespace crown::planner {
// Blocking diagnostic adapter: source validation and full binding/claim copies
// precede replay work/time limits. Resource return discards this private owner;
// callers needing retained search state use ResidualSearch. Invalid source
// validation errors propagate; allocation/limit failures return explicit reports.
ResidualTraceReport verify_residual_trace(const Catalog& catalog, const Query& query,
                                          const ResidualTraceRecord& trace, const SearchLimits& limits) {
  if (limits.time_limit && limits.time_limit->count() < 0) throw std::invalid_argument("negative trace time limit");
  ResidualTraceReport report;
  std::unique_ptr<residual_detail::TraceReplayMachine> machine;
  try {
    validate(catalog, query);
    auto binding = std::make_shared<continuation_detail::BindingData>(continuation_detail::BindingData{catalog, query});
    auto claim = std::make_shared<ResidualTraceRecord>(trace);
    ResidualLimits caps; caps.record_limit.reset(); caps.cell_limit.reset();
    auto budget = std::make_shared<residual_detail::ConstructionBudget>(caps);
    machine = std::make_unique<residual_detail::TraceReplayMachine>(std::move(binding), std::move(claim), std::move(budget));
    const auto start = std::chrono::steady_clock::now();
    for (;;) {
      report = machine->report();
      if ((limits.work_limit && report.work >= *limits.work_limit) ||
          (limits.time_limit && std::chrono::steady_clock::now() - start >= *limits.time_limit)) {
        report.valid = false; report.resource_limit = true; report.rule = ResidualTraceRule::resource_limit; return report;
      }
      const auto step = machine->step({limits.recursion_limit});
      if (step.event == residual_detail::Event::complete || step.event == residual_detail::Event::invalid_trace) return machine->report();
      if (step.event == residual_detail::Event::stopped) {
        report = machine->report(); report.valid = false; report.resource_limit = true; report.rule = ResidualTraceRule::resource_limit; return report;
      }
    }
  } catch (const std::bad_alloc&) {
    if (machine) report = machine->report();
    report.valid = false; report.resource_limit = true; report.rule = ResidualTraceRule::allocation_failure; return report;
  } catch (const residual_detail::Limited&) {
    if (machine) report = machine->report();
    report.valid = false; report.resource_limit = true; report.rule = ResidualTraceRule::resource_limit; return report;
  }
}
} // namespace crown::planner
