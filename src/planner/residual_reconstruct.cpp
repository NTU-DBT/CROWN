#include "residual_machine.hpp"
#include "producer_cursor.hpp"

#include <algorithm>
#include <stdexcept>
#include <utility>

namespace crown::planner::residual_detail {
namespace cp = cd::producer_private;
namespace {
void incrementable(std::uint64_t value) {
  if (value == std::numeric_limits<std::uint64_t>::max())
    throw Limited(ResidualStopReason::counter_overflow);
}
}

// These coroutines share only the P06 suspension mechanism. Candidate construction
// is private; the independent P02 machine remains the sole upper authority.
struct ReconstructionMachine::Impl {
  std::shared_ptr<const cd::BindingData> binding;
  std::shared_ptr<const ResidualTraceRecord> trace;
  std::shared_ptr<ConstructionBudget> budget;
  cp::Engine engine;
  cp::Task main;
  cd::UnitContext context;
  Step result;
  ResidualPhase phase_value = ResidualPhase::seed;
  ResidualOrigin origin_value = ResidualOrigin::hierarchy_seed;
  ResidualStatistics stats;
  std::optional<ExactSearch> exact;
  std::optional<ValidatedIncumbent> exact_upper;
  std::unique_ptr<InducedViewMachine> view_machine;
  std::shared_ptr<const ResidualView> view;
  std::shared_ptr<std::vector<std::size_t>> members;
  std::set<std::size_t> restored;
  VariableSet restored_variables, shared;
  std::vector<std::optional<NodeId>> parents;
  std::shared_ptr<const FreeConnexTree> current;
  std::shared_ptr<FreeConnexTree> copied, draft;
  std::shared_ptr<const cd::BindingData> validation_binding;
  std::unique_ptr<cd::ValidationMachine> validator;
  std::shared_ptr<const cd::CheckedUpper> upper;
  bool exact_ok = false, validation_ok = false, finished = false;

  Impl(std::shared_ptr<const cd::BindingData> b,
       std::shared_ptr<const ResidualTraceRecord> t,
       std::shared_ptr<ConstructionBudget> l)
      : binding(std::move(b)), trace(std::move(t)), budget(std::move(l)) {
    engine.administrative_only = binding->query.atoms.empty();
  }
  ~Impl() { engine.cancel(); }

  template<class F> auto op(F f, std::size_t extra = 0) noexcept {
    return cp::operation(std::move(f), engine.depth + extra);
  }
  template<class F> cp::Task make_task(F create) {
    budget->prepare(1, 0);
    auto value = create();
    budget->commit(1, 0);
    return value;
  }
  cd::UnitContext child_context() const noexcept {
    auto value = context;
    if (value.depth_ceiling) {
      *value.depth_ceiling = *value.depth_ceiling > engine.depth
          ? *value.depth_ceiling - engine.depth : 0;
    }
    return value;
  }
  void child_depth(std::size_t requested) noexcept {
    result = {Event::stopped, ResidualStopReason::depth_limit,
              StopReason::none, engine.depth + requested};
  }
  std::size_t depth() const noexcept {
    if (binding->query.atoms.empty()) return 0;
    std::size_t child = 0;
    if (validator) child = validator->current_depth();
    if (view_machine) child = std::max(child, view_machine->current_depth());
    return engine.depth + child;
  }

  // One node shell, scope member or edge per transition. Claims are deliberately
  // omitted: P02 derives fresh claims for the new binding. mode 0 copies original
  // IDs, mode 1 maps exact/local IDs to originals, mode 2 maps originals to local.
  // source stays owned by current/draft/exact_upper until this child returns.
  // Vector growth, set insertion and string widths remain container costs;
  // the saved cursor counts logical node/scope/edge copies, not allocator bytes.
  cp::Task copy_tree(const FreeConnexTree* source, unsigned mode) {
    co_await op([&] {
      budget->prepare(1, 0);
      auto value = std::make_shared<FreeConnexTree>();
      value->root = source->root;
      copied = std::move(value);
      budget->commit(1, 0);
    });
    for (std::size_t n = 0; n < source->nodes.size(); ++n) {
      co_await op([&, n] {
        budget->prepare(1, 1);
        const auto& old = source->nodes[n];
        TreeNode node{"r" + std::to_string(n), old.kind, {}, {}, old.occurrence, {}};
        if (node.occurrence && mode == 1)
          node.occurrence = view->original_occurrences.at(*node.occurrence);
        if (node.occurrence && mode == 2)
          node.occurrence = view->occurrence_to_local.at(*node.occurrence).value();
        copied->nodes.push_back(std::move(node));
        budget->commit(1, 1);
      });
      for (const auto variable : source->nodes[n].scope) {
        co_await op([&, n, variable] {
          auto mapped = variable;
          if (mode == 1) mapped = view->original_variables.at(variable.value);
          if (mode == 2) mapped = view->variable_to_local.at(variable.value).value();
          budget->prepare(0, 1);
          copied->nodes[n].scope.insert(mapped);
          budget->commit(0, 1);
        });
      }
      for (const auto child : source->nodes[n].children) {
        co_await op([&, n, child] {
          budget->prepare(0, 1);
          copied->nodes[n].children.push_back(child);
          budget->commit(0, 1);
        });
      }
    }
  }

  // This exact proof belongs to view->query only. Prefix infeasibility requests
  // full original search; prefix lower/optimum never becomes original authority.
  // Each scheduled advance grants the retained exact owner one work unit.
  cp::Task solve(bool seed) {
    co_await op([&, seed] {
      phase_value = seed ? ResidualPhase::seed : ResidualPhase::repair;
    });
    // Explicit subsearch admission: owning catalog/query copies and P01 validation
    // are not scalar transitions or a hard CPU-time quantum guarantee.
    co_await op([&, seed] {
      budget->prepare(1, 0);
      if (!seed) incrementable(stats.exact_repairs);
      incrementable(stats.admissions);
      SearchOptions options;
      options.policy = SearchPolicy::strict;
      options.limits = budget->limits.exact;
      auto owner = ExactSearch::create(binding->catalog, view->query, options);
      exact.emplace(std::move(owner));
      exact_upper.reset();
      exact_ok = false;
      if (!seed) ++stats.exact_repairs;
      ++stats.admissions;
      budget->commit(1, 0);
    });
    while (exact->progress().result == ResultKind::unfinished) {
      co_await op([&] {
        const auto p = exact->advance(WorkQuantum{1, {}});
        switch (p.stopped_for) {
          case StopReason::none:
          case StopReason::quantum_work:
          case StopReason::quantum_time:
          case StopReason::complete: break;
          case StopReason::total_work:
          case StopReason::total_time:
          case StopReason::depth_limit:
          case StopReason::allocation_failure:
            result = {Event::stopped, ResidualStopReason::exact_limit, p.stopped_for};
            break;
          case StopReason::counter_overflow:
            result = {Event::stopped, ResidualStopReason::counter_overflow, p.stopped_for};
            break;
          default: throw std::logic_error("residual exact subsearch failed");
        }
      });
    }
    co_await op([&, seed] {
      if (const auto optimum = exact->optimum()) {
        if (seed && trace->terminal != ResidualTerminal::stalled &&
            optimum->height() != (trace->terminal_members.empty() ? 0U : 1U))
          throw std::logic_error("hierarchical residual did not have height one");
        exact_upper = optimum->upper();
        exact_ok = true;
      } else if (!exact->infeasibility()) {
        throw std::logic_error("residual exact search completed without authority");
      }
    });
    if (!exact_ok) co_return;
    cp::Task copy;
    co_await op([&] { copy = make_task([&] { return copy_tree(&exact_upper->tree(), 1); }); }, 1);
    co_await copy;
    co_await op([&, seed] {
      current = std::move(copied);
      if (!seed || trace->terminal == ResidualTerminal::stalled)
        origin_value = ResidualOrigin::exact_repair;
    });
  }

  // A partial proposal needs an original-to-local tree copy and full owned
  // induced catalog/query admission on each attempt. Those copies and P02
  // scratch are real variable-width costs outside residual record/cell caps.
  // Only full validation shares the original binding and can populate upper.
  cp::Task validate(bool full) {
    co_await op([&] { phase_value = ResidualPhase::validate_candidate; });
    cp::Task copy;
    if (!full) {
      co_await op([&] { copy = make_task([&] { return copy_tree(draft.get(), 2); }); }, 1);
      co_await copy;
    }
    // Validation binding admission has the same explicit variable-width copy
    // cost as exact admission. The original final check shares the original owner.
    co_await op([&, full] {
      budget->prepare(1, 0);
      incrementable(stats.admissions);
      auto b = binding;
      if (!full) {
        auto local = std::make_shared<cd::BindingData>();
        local->catalog = binding->catalog;
        local->query = view->query;
        b = std::move(local);
      }
      auto owner = std::make_unique<cd::ValidationMachine>(b, full ? draft : copied);
      validation_binding = std::move(b);
      validator = std::move(owner);
      validation_ok = false;
      ++stats.admissions;
      budget->commit(1, 0);
    });
    cd::UnitEvent event = cd::UnitEvent::advanced;
    while (event != cd::UnitEvent::upper_valid && event != cd::UnitEvent::upper_invalid) {
      co_await op([&] {
        const auto step = validator->step(child_context());
        event = step.event;
        if (event == cd::UnitEvent::depth_blocked) child_depth(step.requested_depth);
      });
    }
    if (event == cd::UnitEvent::upper_valid) {
      co_await op([&, full] {
        validation_ok = true;
        if (full) upper = validator->checked();
        validator.reset();
        copied.reset();
        validation_binding.reset();
      });
    } else {
      co_await op([&] {
        incrementable(stats.rejected_drafts);
        budget->prepare(1, 0);
        validator.reset();
        ++stats.rejected_drafts;
        budget->commit(1, 0);
        copied.reset();
        validation_binding.reset();
      });
    }
  }

  cp::Task make_view(std::size_t ear) {
    co_await op([&] {
      budget->prepare(1, 0);
      auto value = std::make_shared<std::vector<std::size_t>>();
      members = std::move(value);
      budget->commit(1, 0);
    });
    for (std::size_t occurrence = 0; occurrence < binding->query.atoms.size(); ++occurrence) {
      co_await op([&, occurrence] {
        if (occurrence == ear || restored.contains(occurrence)) {
          budget->prepare(0, 1);
          members->push_back(occurrence);
          budget->commit(0, 1);
        }
      });
    }
    co_await op([&] {
      budget->prepare(1, 0);
      auto owner = std::make_unique<InducedViewMachine>(binding, members, budget);
      view_machine = std::move(owner);
      budget->commit(1, 0);
    });
    bool ready = false;
    while (!ready) {
      co_await op([&] {
        const auto step = view_machine->step(child_context());
        if (step.event == Event::complete) ready = true;
        else if (step.event == Event::stopped) {
          result = step;
          if (step.reason == ResidualStopReason::depth_limit)
            result.requested_depth += engine.depth;
        } else if (step.event != Event::advanced) {
          throw std::logic_error("induced view construction failed");
        }
      });
    }
    co_await op([&] {
      view = view_machine->view();
      view_machine.reset();
    });
  }

  // Local proposal family from Refactor.md Section 5.3: alternate placements
  // and generalized forks repair specific failures of naive reattachment.
  // They are not P2 Appendix B completeness/height claims. P02 independently
  // checks restored-head reachability and every structural rule before commit.
  cp::Task attempt(std::size_t ear, std::size_t target, unsigned rule) {
    // Rule A/native leaf, B/generalized leaf and C/generalized fork. Full P02
    // verifies new-head reachability; a compatible scope alone never accepts it.
    bool compatible = true;
    for (const auto variable : shared) {
      co_await op([&, variable] {
        if (!current->nodes[target].scope.contains(variable)) compatible = false;
      });
    }
    if (rule == 1) {
      for (const auto variable : current->nodes[target].scope) {
        co_await op([&, variable] {
          if (!trace->original_scopes[ear].contains(variable)) compatible = false;
        });
      }
    }
    if (rule == 2 && parents[target]) {
      const auto parent = parents[target]->value;
      co_await op([&, parent] {
        if (current->nodes[parent].kind != NodeKind::generalized) compatible = false;
      });
      for (const auto variable : current->nodes[parent].scope) {
        co_await op([&, variable] {
          if (!shared.contains(variable)) compatible = false;
        });
      }
    }
    if (!compatible) co_return;
    cp::Task copy;
    co_await op([&] { copy = make_task([&] { return copy_tree(current.get(), 0); }); }, 1);
    co_await copy;
    co_await op([&] {
      incrementable(stats.drafts);
      draft = std::move(copied);
      ++stats.drafts;
    });
    const NodeId native{draft->nodes.size()};
    co_await op([&] {
      budget->prepare(1, 1);
      TreeNode node{"r" + std::to_string(native.value), NodeKind::native, {}, {}, ear, {}};
      draft->nodes.push_back(std::move(node));
      budget->commit(1, 1);
    });
    for (const auto variable : trace->original_scopes[ear]) {
      co_await op([&, variable] {
        budget->prepare(0, 1);
        draft->nodes[native.value].scope.insert(variable);
        budget->commit(0, 1);
      });
    }
    if (rule < 2) {
      co_await op([&] {
        budget->prepare(0, 1);
        draft->nodes[target].children.push_back(native);
        budget->commit(0, 1);
      });
    } else {
      const NodeId fork{draft->nodes.size()};
      co_await op([&] {
        budget->prepare(1, 1);
        TreeNode node{"r" + std::to_string(fork.value), NodeKind::generalized, {}, {}, {}, {}};
        draft->nodes.push_back(std::move(node));
        budget->commit(1, 1);
      });
      for (const auto variable : shared) {
        co_await op([&, variable] {
          budget->prepare(0, 1);
          draft->nodes[fork.value].scope.insert(variable);
          budget->commit(0, 1);
        });
      }
      co_await op([&] {
        budget->prepare(0, 1);
        draft->nodes[fork.value].children.push_back(NodeId{target});
        budget->commit(0, 1);
      });
      co_await op([&] {
        budget->prepare(0, 1);
        draft->nodes[fork.value].children.push_back(native);
        budget->commit(0, 1);
      });
      if (parents[target]) {
        const auto parent = parents[target]->value;
        for (std::size_t edge = 0; edge < draft->nodes[parent].children.size(); ++edge) {
          co_await op([&, parent, edge] {
            if (draft->nodes[parent].children[edge].value == target)
              draft->nodes[parent].children[edge] = fork;
          });
        }
      } else {
        co_await op([&] { draft->root = fork; });
      }
    }
    cp::Task check;
    co_await op([&] { check = make_task([&] { return validate(false); }); }, 1);
    co_await check;
    if (validation_ok) {
      co_await op([&] {
        if (rule == 2) incrementable(stats.generalized_grafts);
        current = std::move(draft);
        origin_value = rule == 0 ? ResidualOrigin::native_leaf
                     : rule == 1 ? ResidualOrigin::generalized_leaf
                                 : ResidualOrigin::generalized_graft;
        if (rule == 2) ++stats.generalized_grafts;
      });
    }
  }

  // Greedy first-valid restoration is incomplete. Scan the original atom list
  // to build the enlarged head/query, try recorded/other placements, then use
  // an owned complete prefix repair. Each compatible draft can copy/check the
  // entire tree; exhaustion alone never means original infeasibility.
  cp::Task restore(std::size_t ear, std::size_t anchor) {
    co_await op([&] {
      phase_value = ResidualPhase::restore;
      shared.clear();
      parents.clear();
      validation_ok = false;
    });
    for (const auto variable : trace->original_scopes[ear]) {
      co_await op([&, variable] {
        if (restored_variables.contains(variable)) {
          budget->prepare(0, 1);
          shared.insert(variable);
          budget->commit(0, 1);
        }
      });
    }
    cp::Task view_task;
    co_await op([&] { view_task = make_task([&] { return make_view(ear); }); }, 1);
    co_await view_task;
    for (std::size_t n = 0; n < current->nodes.size(); ++n) {
      co_await op([&] {
        budget->prepare(0, 1);
        parents.push_back(std::nullopt);
        budget->commit(0, 1);
      });
    }
    std::optional<std::size_t> preferred;
    for (std::size_t n = 0; n < current->nodes.size(); ++n) {
      co_await op([&, n] {
        if (current->nodes[n].occurrence == anchor) preferred = n;
      });
      for (const auto child : current->nodes[n].children) {
        co_await op([&, n, child] { parents[child.value] = NodeId{n}; });
      }
    }
    cp::Task candidate;
    if (preferred) {
      co_await op([&] { candidate = make_task([&] { return attempt(ear, *preferred, 0); }); }, 1);
      co_await candidate;
    }
    // Try every restored placement, not only frozen anchors. This is a greedy
    // first-valid path, explicitly incomplete; an exhausted family calls repair.
    for (unsigned rule = 0; rule != 3 && !validation_ok; ++rule) {
      const auto count = current->nodes.size();
      for (std::size_t n = 0; n < count && !validation_ok; ++n) {
        bool eligible = false;
        co_await op([&, n, rule] {
          phase_value = ResidualPhase::restore;
          const auto kind = current->nodes[n].kind;
          eligible = rule == 2 || (rule == 0 && kind == NodeKind::native && preferred != n)
                                 || (rule == 1 && kind == NodeKind::generalized);
        });
        if (!eligible) continue;
        co_await op([&, n, rule] { candidate = make_task([&] { return attempt(ear, n, rule); }); }, 1);
        co_await candidate;
      }
    }
    if (!validation_ok) {
      cp::Task repair;
      co_await op([&] { repair = make_task([&] { return solve(false); }); }, 1);
      co_await repair;
      if (!exact_ok) co_return;
    }
    co_await op([&] {
      incrementable(stats.restorations);
      budget->prepare(0, 1);
      restored.insert(ear);
      ++stats.restorations;
      budget->commit(0, 1);
    });
    for (const auto variable : trace->original_scopes[ear]) {
      co_await op([&, variable] {
        if (!restored_variables.contains(variable)) {
          budget->prepare(0, 1);
          restored_variables.insert(variable);
          budget->commit(0, 1);
        }
      });
    }
  }

  cp::Task run() {
    co_await op([&] { view = std::shared_ptr<const ResidualView>(trace, &trace->terminal_view); });
    for (const auto occurrence : trace->terminal_members) {
      co_await op([&, occurrence] {
        budget->prepare(0, 1);
        restored.insert(occurrence);
        budget->commit(0, 1);
      });
    }
    for (const auto variable : trace->terminal_view.original_variables) {
      co_await op([&, variable] {
        budget->prepare(0, 1);
        restored_variables.insert(variable);
        budget->commit(0, 1);
      });
    }
    cp::Task seed;
    co_await op([&] { seed = make_task([&] { return solve(true); }); }, 1);
    co_await seed;
    if (!exact_ok) {
      co_await op([&] { result.event = Event::need_original_exact; finished = true; });
      co_return;
    }
    for (std::size_t l = trace->layers.size(); l > 0; --l) {
      const auto& deletions = trace->layers[l - 1].deletions;
      for (std::size_t d = deletions.size(); d > 0; --d) {
        cp::Task restoration;
        co_await op([&] {
          restoration = make_task([&] { return restore(deletions[d - 1].occurrence, deletions[d - 1].anchor); });
        }, 1);
        co_await restoration;
        if (!validation_ok && !exact_ok) {
          co_await op([&] { result.event = Event::need_original_exact; finished = true; });
          co_return;
        }
      }
    }
    // No induced checked handle escapes. Re-check the fully restored tree using
    // the *same* original binding owner and original occurrence/variable IDs.
    cp::Task final_copy;
    co_await op([&] { final_copy = make_task([&] { return copy_tree(current.get(), 0); }); }, 1);
    co_await final_copy;
    co_await op([&] { draft = std::move(copied); });
    cp::Task check;
    co_await op([&] { check = make_task([&] { return validate(true); }); }, 1);
    co_await check;
    co_await op([&] {
      if (validation_ok) {
        if (!upper || upper->binding != binding)
          throw std::logic_error("residual original binding mismatch");
        phase_value = ResidualPhase::complete;
        result.event = Event::checked_upper;
      } else {
        // Full original exact fallback is owned by the facade, never replaced by
        // a partial infeasibility certificate or a post-hoc unsupported result.
        result.event = Event::need_original_exact;
      }
      finished = true;
    });
  }
};

ReconstructionMachine::ReconstructionMachine(std::shared_ptr<const cd::BindingData> binding,
    std::shared_ptr<const ResidualTraceRecord> trace, std::shared_ptr<ConstructionBudget> budget)
    : data_(std::make_unique<Impl>(std::move(binding), std::move(trace), std::move(budget))) {}
ReconstructionMachine::~ReconstructionMachine() = default;
ReconstructionMachine::ReconstructionMachine(ReconstructionMachine&&) noexcept = default;
ReconstructionMachine& ReconstructionMachine::operator=(ReconstructionMachine&&) noexcept = default;
Step ReconstructionMachine::step(const cd::UnitContext& context) {
  auto& d = *data_;
  if (d.finished) return {Event::complete};
  d.result = {};
  d.context = context;
  if (!d.main.handle) {
    if (!d.binding->query.atoms.empty() && !context.permits(1)) return {Event::stopped, ResidualStopReason::depth_limit, StopReason::none, 1};
    auto task = d.make_task([&] { return d.run(); });
    d.main = std::move(task);
    d.engine.start(d.main);
    return {};
  }
  const auto step = d.engine.step(context);
  if (step.event == cd::UnitEvent::depth_blocked)
    return {Event::stopped, ResidualStopReason::depth_limit, StopReason::none, step.requested_depth};
  return d.result;
}
ResidualPhase ReconstructionMachine::phase() const noexcept { return data_->phase_value; }
const ResidualStatistics& ReconstructionMachine::statistics() const noexcept { return data_->stats; }
std::size_t ReconstructionMachine::current_depth() const noexcept { return data_->depth(); }
std::shared_ptr<const cd::CheckedUpper> ReconstructionMachine::checked_upper() const noexcept { return data_->upper; }
ResidualOrigin ReconstructionMachine::origin() const noexcept { return data_->origin_value; }
SearchProgress ReconstructionMachine::exact_progress() const noexcept {
  return data_->exact ? data_->exact->progress() : SearchProgress{};
}
LimitChange ReconstructionMachine::raise_exact_limits(ContinuationLimits limits) noexcept {
  if (data_->exact && data_->exact->progress().result == ResultKind::unfinished)
    return data_->exact->raise_limits(limits);
  return LimitChange::applied;
}
} // namespace crown::planner::residual_detail
