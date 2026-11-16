#include "residual_machine.hpp"
#include "producer_cursor.hpp"

namespace crown::planner::residual_detail {
namespace pp = cd::producer_private;
// Private callers provide valid, sorted, unique original occurrence IDs and
// retain them by shared ownership. The draft remains private until all dense
// maps, original terms and surviving ordered head positions are complete.
struct InducedViewMachine::Impl {
  std::shared_ptr<const cd::BindingData> binding;
  std::shared_ptr<const std::vector<std::size_t>> members;
  std::shared_ptr<ConstructionBudget> budget;
  std::shared_ptr<ResidualView> draft;
  std::shared_ptr<const ResidualView> result;
  std::vector<unsigned char> active;
  pp::Engine engine;
  pp::Task task;
  bool started = false;
  Impl(std::shared_ptr<const cd::BindingData> b,
       std::shared_ptr<const std::vector<std::size_t>> m,
       std::shared_ptr<ConstructionBudget> c) : binding(std::move(b)), members(std::move(m)), budget(std::move(c)) {}
  ~Impl() { engine.cancel(); }
  template<class T, class U> void append(std::vector<T>& out, U&& value, std::uint64_t records = 0) {
    budget->prepare(records, 1);
    out.push_back(std::forward<U>(value));
    budget->commit(records, 1);
  }
  pp::Task run() {
#define VIEW_OP(...) co_await pp::operation([&] { __VA_ARGS__; }, members->empty() ? 0 : 1)
    VIEW_OP(budget->prepare(1, 0); draft = std::make_shared<ResidualView>(); budget->commit(1, 0));
    draft->query.contradiction = binding->query.contradiction;
    VIEW_OP(budget->prepare(0, 0); active.reserve(binding->query.variables.size()));
    VIEW_OP(budget->prepare(0, 0); draft->variable_to_local.reserve(binding->query.variables.size()));
    VIEW_OP(budget->prepare(0, 0); draft->occurrence_to_local.reserve(binding->query.atoms.size()));
    for (std::size_t v = 0; v < binding->query.variables.size(); ++v) {
      VIEW_OP(append(active, static_cast<unsigned char>(0)));
      VIEW_OP(append(draft->variable_to_local, std::optional<VariableId>{}));
    }
    for (std::size_t a = 0; a < binding->query.atoms.size(); ++a) {
      VIEW_OP(append(draft->occurrence_to_local, std::optional<std::size_t>{}));
    }
    for (const auto a : *members) {
      VIEW_OP((void)a);
      for (const auto& term : binding->query.atoms[a].terms) {
        VIEW_OP(if (const auto* v = std::get_if<VariableId>(&term)) active[v->value] = 1);
      }
    }
    VIEW_OP(budget->prepare(0, 0); draft->query.variables.reserve(binding->query.variables.size()));
    VIEW_OP(budget->prepare(0, 0); draft->original_variables.reserve(binding->query.variables.size()));
    for (std::size_t v = 0; v < active.size(); ++v) {
      VIEW_OP((void)v);
      if (!active[v]) continue;
      VIEW_OP(append(draft->query.variables, binding->query.variables[v], 1));
      VIEW_OP(append(draft->original_variables, VariableId{v}));
      draft->variable_to_local[v] = VariableId{draft->query.variables.size() - 1};
    }
    VIEW_OP(budget->prepare(0, 0); draft->query.atoms.reserve(members->size()));
    VIEW_OP(budget->prepare(0, 0); draft->original_occurrences.reserve(members->size()));
    for (const auto a : *members) {
      VIEW_OP(budget->prepare(1, 1); draft->query.atoms.push_back(Atom{binding->query.atoms[a].occurrence, binding->query.atoms[a].table, {}}); budget->commit(1, 1));
      VIEW_OP(append(draft->original_occurrences, a));
      draft->occurrence_to_local[a] = draft->query.atoms.size() - 1;
      auto& out = draft->query.atoms.back();
      VIEW_OP(budget->prepare(0, 0); out.terms.reserve(binding->query.atoms[a].terms.size()));
      for (const auto& term : binding->query.atoms[a].terms) {
        VIEW_OP(if (const auto* v = std::get_if<VariableId>(&term)) {
          budget->prepare(0, 1);
          out.terms.emplace_back(std::in_place_type<VariableId>, *draft->variable_to_local[v->value]);
          budget->commit(0, 1);
        } else { append(out.terms, term); });
      }
    }
    VIEW_OP(budget->prepare(0, 0); draft->query.head.reserve(binding->query.head.size()));
    for (const auto& head : binding->query.head) {
      VIEW_OP((void)head);
      if (draft->variable_to_local[head.variable.value]) {
        VIEW_OP(budget->prepare(1, 1); draft->query.head.push_back(Output{*draft->variable_to_local[head.variable.value], head.alias}); budget->commit(1, 1));
      }
    }
    VIEW_OP(result = draft);
#undef VIEW_OP
  }
};
InducedViewMachine::InducedViewMachine(std::shared_ptr<const cd::BindingData> b,
    std::shared_ptr<const std::vector<std::size_t>> m, std::shared_ptr<ConstructionBudget> c)
    : data_(std::make_unique<Impl>(std::move(b), std::move(m), std::move(c))) {}
InducedViewMachine::~InducedViewMachine() = default;
InducedViewMachine::InducedViewMachine(InducedViewMachine&&) noexcept = default;
InducedViewMachine& InducedViewMachine::operator=(InducedViewMachine&&) noexcept = default;
Step InducedViewMachine::step(const cd::UnitContext& ctx) {
  auto& d = *data_;
  if (d.result) return {Event::complete};
  if (!ctx.permits(current_depth())) return {Event::stopped, ResidualStopReason::depth_limit, StopReason::none, current_depth()};
  if (!d.started) { d.budget->prepare(1, 0); d.task = d.run(); d.engine.start(d.task); d.started = true; d.budget->commit(1, 0); return {}; }
  const auto s = d.engine.step(ctx);
  if (s.event == cd::UnitEvent::depth_blocked) return {Event::stopped, ResidualStopReason::depth_limit, StopReason::none, s.requested_depth};
  return {d.result ? Event::complete : Event::advanced};
}
std::shared_ptr<const ResidualView> InducedViewMachine::view() const noexcept { return data_->result; }
std::size_t InducedViewMachine::current_depth() const noexcept { return data_->result || data_->members->empty() ? 0 : 1; }
} // namespace crown::planner::residual_detail
