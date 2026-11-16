#include "residual_oracle.hpp"

#include <algorithm>
#include <iterator>
#include <map>
#include <set>
#include <vector>

namespace crown::reference {
namespace {
using planner::EarAnchor;
using planner::EarCondition;
using planner::EarRecord;
using planner::ResidualLayer;
using planner::ResidualTerminal;
using planner::ResidualTraceRecord;
using planner::ResidualView;

VariableSet scope_of(const Atom& atom) {
  VariableSet result;
  for (const auto& term : atom.terms) {
    if (const auto* variable = std::get_if<VariableId>(&term)) result.insert(*variable);
  }
  return result;
}

std::vector<VariableSet> scopes_of(const Query& query) {
  std::vector<VariableSet> scopes;
  scopes.reserve(query.atoms.size());
  for (const auto& atom : query.atoms) scopes.push_back(scope_of(atom));
  return scopes;
}

VariableSet variables_of(const std::vector<VariableSet>& scopes,
                         const std::vector<std::size_t>& members) {
  VariableSet result;
  for (const auto occurrence : members) {
    const auto& scope = scopes.at(occurrence);
    result.insert(scope.begin(), scope.end());
  }
  return result;
}

VariableSet head_of(const Query& query, const VariableSet& variables) {
  VariableSet result;
  for (const auto& output : query.head) {
    if (variables.contains(output.variable)) result.insert(output.variable);
  }
  return result;
}

VariableSet intersection(const VariableSet& left, const VariableSet& right) {
  VariableSet result;
  std::set_intersection(left.begin(), left.end(), right.begin(), right.end(),
                        std::inserter(result, result.end()));
  return result;
}

VariableSet difference(const VariableSet& left, const VariableSet& right) {
  VariableSet result;
  std::set_difference(left.begin(), left.end(), right.begin(), right.end(),
                      std::inserter(result, result.end()));
  return result;
}

bool subset_of(const VariableSet& subset, const VariableSet& superset) {
  return std::includes(superset.begin(), superset.end(), subset.begin(), subset.end());
}

bool proper_subset_of(const VariableSet& subset, const VariableSet& superset) {
  return subset.size() < superset.size() && subset_of(subset, superset);
}

bool disjoint(const VariableSet& left, const VariableSet& right) {
  auto a = left.begin();
  auto b = right.begin();
  while (a != left.end() && b != right.end()) {
    if (*a == *b) return false;
    if (*a < *b) ++a;
    else ++b;
  }
  return true;
}

bool is_q_hierarchical(const std::vector<VariableSet>& scopes,
                       const std::vector<std::size_t>& members,
                       const VariableSet& free) {
  const auto variables = variables_of(scopes, members);
  std::vector<std::pair<VariableId, VariableSet>> incidence;
  incidence.reserve(variables.size());
  for (const auto variable : variables) {
    VariableSet occurrences;
    for (const auto occurrence : members) {
      if (scopes.at(occurrence).contains(variable)) occurrences.insert(VariableId{occurrence});
    }
    incidence.emplace_back(variable, std::move(occurrences));
  }

  for (std::size_t i = 0; i < incidence.size(); ++i) {
    for (std::size_t j = i + 1; j < incidence.size(); ++j) {
      const auto& left = incidence[i].second;
      const auto& right = incidence[j].second;
      const bool left_in_right = subset_of(left, right);
      const bool right_in_left = subset_of(right, left);
      if (!left_in_right && !right_in_left && !disjoint(left, right)) return false;

      if (free.contains(incidence[i].first) && proper_subset_of(left, right) &&
          !free.contains(incidence[j].first)) return false;
      if (free.contains(incidence[j].first) && proper_subset_of(right, left) &&
          !free.contains(incidence[i].first)) return false;
    }
  }
  return true;
}

ResidualView make_terminal_view(const Query& original,
                               const std::vector<std::size_t>& members,
                               const std::vector<VariableSet>& scopes) {
  ResidualView view;
  view.original_occurrences = members;
  view.occurrence_to_local.resize(original.atoms.size());
  for (std::size_t local = 0; local < members.size(); ++local) {
    view.occurrence_to_local.at(members[local]) = local;
  }

  const auto variables = variables_of(scopes, members);
  view.variable_to_local.resize(original.variables.size());
  for (const auto variable : variables) {
    const auto local = VariableId{view.original_variables.size()};
    view.original_variables.push_back(variable);
    view.variable_to_local.at(variable.value) = local;
    view.query.variables.push_back(original.variables.at(variable.value));
  }

  view.query.contradiction = original.contradiction;
  view.query.atoms.reserve(members.size());
  for (const auto occurrence : members) {
    Atom atom = original.atoms.at(occurrence);
    for (auto& term : atom.terms) {
      if (const auto* variable = std::get_if<VariableId>(&term)) {
        term = *view.variable_to_local.at(variable->value);
      }
    }
    view.query.atoms.push_back(std::move(atom));
  }
  for (const auto& output : original.head) {
    const auto& local = view.variable_to_local.at(output.variable.value);
    if (local) view.query.head.push_back({*local, output.alias});
  }
  return view;
}

}  // namespace

planner::ResidualTraceRecord frozen_residual_trace(const Query& query) {
  ResidualTraceRecord result;
  const auto scopes = scopes_of(query);
  result.original_scopes = scopes;

  std::vector<std::size_t> live(query.atoms.size());
  for (std::size_t occurrence = 0; occurrence < live.size(); ++occurrence) live[occurrence] = occurrence;

  for (;;) {
    const auto round_variables = variables_of(scopes, live);
    const auto round_head = head_of(query, round_variables);
    if (live.empty()) {
      result.terminal = ResidualTerminal::empty_body;
      result.terminal_members = live;
      result.terminal_head = {};
      break;
    }
    if (is_q_hierarchical(scopes, live, round_head)) {
      result.terminal = ResidualTerminal::hierarchical;
      result.terminal_members = live;
      result.terminal_head = round_head;
      break;
    }

    ResidualLayer layer;
    layer.members = live;
    layer.variables = round_variables;
    layer.head = round_head;

    std::map<VariableId, std::size_t> occurrence_counts;
    for (const auto occurrence : live) {
      for (const auto variable : scopes.at(occurrence)) ++occurrence_counts[variable];
    }
    for (const auto& [variable, count] : occurrence_counts) {
      if (count == 1) layer.unique.insert(variable);
    }

    for (const auto ear : live) {
      const auto shared = difference(scopes.at(ear), layer.unique);
      const auto unique = intersection(scopes.at(ear), layer.unique);
      EarRecord record;
      record.occurrence = ear;
      record.shared = shared;
      record.unique = unique;
      for (const auto anchor : live) {
        if (ear == anchor) continue;
        const bool first = subset_of(shared, scopes.at(anchor)) &&
                           disjoint(unique, round_head);
        const bool second = subset_of(shared, intersection(scopes.at(anchor), round_head));
        unsigned conditions = 0;
        if (first) conditions |= static_cast<unsigned>(EarCondition::first);
        if (second) conditions |= static_cast<unsigned>(EarCondition::second);
        if (conditions != 0) {
          record.anchors.push_back({anchor, static_cast<EarCondition>(conditions)});
        }
      }
      if (!record.anchors.empty()) layer.ears.push_back(std::move(record));
    }

    std::set<std::size_t> remaining(live.begin(), live.end());
    for (;;) {
      bool removed = false;
      for (const auto& ear : layer.ears) {
        if (!remaining.contains(ear.occurrence)) continue;
        const auto anchor = std::find_if(ear.anchors.begin(), ear.anchors.end(), [&](const EarAnchor& value) {
          return value.occurrence != ear.occurrence && remaining.contains(value.occurrence);
        });
        if (anchor == ear.anchors.end()) continue;
        layer.deletions.push_back({ear.occurrence, anchor->occurrence});
        remaining.erase(ear.occurrence);
        removed = true;
        break;
      }
      if (!removed) break;
    }

    layer.remaining.assign(remaining.begin(), remaining.end());
    layer.residual_head = head_of(query, variables_of(scopes, layer.remaining));
    const bool productive = layer.remaining.size() < layer.members.size();
    live = layer.remaining;
    result.layers.push_back(std::move(layer));

    if (live.empty()) {
      result.terminal = ResidualTerminal::empty_body;
      result.terminal_members = live;
      result.terminal_head = {};
      break;
    }
    if (!productive) {
      result.terminal = ResidualTerminal::stalled;
      result.terminal_members = live;
      result.terminal_head = head_of(query, variables_of(scopes, live));
      break;
    }
  }

  result.terminal_view = make_terminal_view(query, result.terminal_members, scopes);
  return result;
}

}  // namespace crown::reference
