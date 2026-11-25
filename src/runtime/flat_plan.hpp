#pragma once
// Shared compiled-program analysis for the flat executors (FlatRuntime and
// FlatCountRuntime): tree nodes, C* ranks and separators, input adapters,
// physical bases and the snapshot/anchored enumeration plans.
#include "crown/ir/program.hpp"
#include "flat_table.hpp"

#include <algorithm>
#include <optional>
#include <string>
#include <vector>

namespace crown::runtime::flat_detail {

// Record payload: word 0 = derivations (low) | satisfied children (high), word 1 = child bits.
// Visible payload: word 0 = support count (low) | live flag (bit 32), word 1 = route stamp.
inline constexpr std::uint64_t live_bit = 1ULL << 32;
inline std::uint32_t low(Word w) { return static_cast<std::uint32_t>(static_cast<std::uint64_t>(w)); }
inline std::uint32_t high(Word w) { return static_cast<std::uint32_t>(static_cast<std::uint64_t>(w) >> 32); }
inline Word pack(std::uint32_t lo, std::uint32_t hi) {
  return static_cast<Word>((static_cast<std::uint64_t>(hi) << 32) | lo);
}

struct ChildEdge {  // C* child of this node
  std::uint32_t node;
  std::vector<std::uint32_t> parent_positions;  // separator positions in this node's visible key
};
struct Node {
  bool native = true, connex = false;
  std::uint32_t parent = none, slot = 0, children = 0;
  std::vector<std::uint32_t> child_nodes;                      // by slot
  std::vector<std::vector<std::uint32_t>> child_positions;     // by slot, over this node's scope
  std::vector<std::vector<std::uint32_t>> generalized_place;   // by slot: key field i -> record field
  std::vector<std::uint32_t> parent_positions;                 // support key over this node's scope
  std::vector<std::uint32_t> visible_positions;                // visible key over this node's scope
  std::vector<std::uint32_t> visible_variables;
  std::uint32_t arity = 0;
  Table records, support, visible, live;
  // C* structure.
  std::uint32_t rank = none, cparent = none, child_index_base = 0;
  std::vector<std::uint32_t> separator_positions;  // in own visible key, separator with C* parent
  std::vector<ChildEdge> cchildren;
  std::vector<std::uint32_t> changed;
};
struct Operand {
  bool column = false;
  std::uint32_t index = 0;  // physical column
  Word value = 0;           // encoded literal
};
struct Predicate {
  frontend::SqlOperator operation;
  Operand left, right;
};
struct Input {
  std::uint32_t node = 0;
  std::vector<Predicate> predicates;
  std::vector<std::uint32_t> map;  // record field -> physical column
  std::vector<std::pair<std::uint32_t, std::uint32_t>> equal;
  std::vector<std::pair<std::uint32_t, Word>> constant;
};
struct Base {
  std::vector<std::uint32_t> routes;
  std::vector<ScalarType> types;
  bool dedupe = false;
  Table rows;
};
struct Step {
  std::uint32_t node = 0, from = none, index = 0;
  std::vector<std::uint32_t> key_positions;  // positions in the visible key of step `from`
  bool live = false, prune = false;
};
struct Plan {
  std::vector<Step> steps;
  // (step, visible field); step == none selects constant output `field`.
  std::vector<std::pair<std::uint32_t, std::uint32_t>> output;
};

// A comparison operand: a column of this occurrence or a non-null literal,
// possibly under identity/integer-widening casts. Returns its scalar type.
inline std::optional<ScalarType> operand_type(const program::NormalizedSql& sql, frontend::OccurrenceId occurrence,
    frontend::ExpressionId id, int depth = 0) {
  if (depth > 8) return std::nullopt;
  const auto& node = sql.binding.expressions.at(id.value).node;
  if (const auto* column = std::get_if<program::BoundColumn>(&node)) {
    if (column->occurrence != occurrence) return std::nullopt;
    const auto& occ = sql.binding.occurrences.at(occurrence.value);
    return sql.binding.catalog.tables.at(occ.table.value).columns.at(column->column.value).type;
  }
  if (const auto* literal = std::get_if<program::BoundLiteral>(&node)) {
    if (!literal->value) return std::nullopt;
    if (std::holds_alternative<std::int64_t>(*literal->value)) return ScalarType::int64;
    if (std::holds_alternative<std::string_view>(*literal->value)) return ScalarType::string;
    if (std::holds_alternative<bool>(*literal->value)) return ScalarType::boolean;
    return std::nullopt;
  }
  if (const auto* operation = std::get_if<program::BoundOperation>(&node)) {
    if ((operation->operation == frontend::SqlOperator::identity_cast ||
         operation->operation == frontend::SqlOperator::widen_integer) && operation->arguments.size() == 1)
      return operand_type(sql, occurrence, operation->arguments[0], depth + 1);
  }
  return std::nullopt;
}
inline bool simple_predicate(const program::NormalizedSql& sql, frontend::OccurrenceId occurrence, frontend::ExpressionId id) {
  const auto* operation = std::get_if<program::BoundOperation>(&sql.binding.expressions.at(id.value).node);
  if (!operation || operation->arguments.size() != 2) return false;
  using enum frontend::SqlOperator;
  const auto op = operation->operation;
  if (op != equal && op != not_equal && op != less && op != less_equal && op != greater && op != greater_equal) return false;
  const auto left = operand_type(sql, occurrence, operation->arguments[0]);
  const auto right = operand_type(sql, occurrence, operation->arguments[1]);
  if (!left || !right || *left != *right) return false;
  // Strings are interned: only equality is order-free.
  return *left == ScalarType::int64 || op == equal || op == not_equal;
}

inline std::string check(const CompiledProgram& program) {
  if (program.route() != PhysicalRoute::tree) return "constant program routes";
  for (const auto& table : program.source_catalog().tables) {
    for (const auto& column : table.columns)
      if (column.type != ScalarType::int64 && column.type != ScalarType::string && column.type != ScalarType::boolean)
        return "column types other than int64, string and boolean";
    for (const auto& constraint : table.constraints) {
      const bool enforced = std::visit([](const auto& value) { return value.status == ConstraintStatus::enforced; }, constraint);
      if (enforced) return "enforced source constraints";
    }
  }
  const auto& nodes = program.nodes();
  if (nodes.size() > max_nodes) return "more than 64 tree nodes";
  for (const auto& node : nodes) {
    if (node.scope.size() > max_arity) return "node scope wider than 32 variables";
    if (node.children.size() > 64) return "more than 64 children";
    const auto fields = node.layout.fields();
    if (fields.size() != node.scope.size()) return "node layout differs from scope";
    for (std::size_t i = 0; i < fields.size(); ++i)
      if (fields[i].variable && *fields[i].variable != node.scope[i]) return "node layout order differs from scope";
    if (node.connex && !node.visible_projection) return "connex node without visible projection";
  }
  if (const auto& sql = program.normalized()) {
    for (const auto& adapter : sql->adapters) {
      for (const auto id : adapter.predicates)
        if (!simple_predicate(*sql, adapter.occurrence, id)) return "SQL input predicates other than simple comparisons";
      for (const auto& projection : adapter.projection)
        if (!std::holds_alternative<program::BoundColumn>(sql->binding.expressions.at(projection.expression.value).node))
          return "computed SQL input projections";
    }
  }
  const auto& steps = program.enumeration().steps;
  if (steps.empty()) return "empty enumeration program";
  if (steps.size() > max_nodes) return "too many enumeration steps";
  if (nodes[steps[0].node.value].parent) return "C* root is not the tree root";
  std::vector<bool> in_cstar(nodes.size(), false);
  for (std::size_t s = 0; s < steps.size(); ++s) {
    const auto& node = nodes[steps[s].node.value];
    if (!node.connex || !node.visible_relation || steps[s].relation != *node.visible_relation)
      return "enumeration step is not a connex visible relation";
    if (s > 0) {
      if (!steps[s].parent_step || !node.parent || steps[*steps[s].parent_step].node != *node.parent)
        return "C* parent differs from tree parent";
    }
    in_cstar[node.id.value] = true;
  }
  for (const auto& node : nodes) if (node.connex != in_cstar[node.id.value]) return "connex nodes differ from C* steps";
  return {};
}


struct FlatProgram {
  bool delta = false, weighted = false;
  std::vector<Node> nodes;
  std::vector<Input> inputs;
  std::vector<Base> bases;
  std::vector<std::uint32_t> by_rank;  // C* nodes, parent before child
  std::uint32_t root = 0;
  Plan snapshot_plan;
  std::vector<Plan> anchor;  // by node
  std::vector<ScalarType> output_types;
  std::vector<std::int64_t> output_core;  // final column -> core head column, or -1 for a constant
  std::vector<Word> output_constants;     // by final column
  std::uint64_t route = 0;
  Dictionary dictionary;
  Word encode_view(const storage::ScalarView& value) { return dictionary.encode(value); }
  Word encode_value(const Value& value) { return dictionary.encode(value); }

  FlatProgram(const CompiledProgram& program, bool delta_mode, bool weighted_mode) : delta(delta_mode), weighted(weighted_mode) {
    if (auto problem = check(program); !problem.empty()) fail(problem.c_str());
    build_nodes(program);
    build_inputs(program);
    build_plans(program);
  }

  Operand operand(const program::NormalizedSql& sql, frontend::ExpressionId id) {
    const auto& node = sql.binding.expressions.at(id.value).node;
    if (const auto* column = std::get_if<program::BoundColumn>(&node))
      return {true, static_cast<std::uint32_t>(column->column.value), 0};
    if (const auto* literal = std::get_if<program::BoundLiteral>(&node)) return {false, 0, encode_view(*literal->value)};
    return operand(sql, std::get<program::BoundOperation>(node).arguments[0]);
  }
  static std::vector<std::uint32_t> positions(const storage::AccountedProjection& projection) {
    std::vector<std::uint32_t> out;
    for (const auto field : projection.fields()) out.push_back(static_cast<std::uint32_t>(field.value));
    return out;
  }

  void build_nodes(const CompiledProgram& program) {
    const auto& source = program.nodes();
    nodes.resize(source.size());
    for (const auto& edge : program.edges()) {
      auto& parent = nodes[edge.parent.value];
      if (parent.child_nodes.size() <= edge.child_slot) {
        parent.child_nodes.resize(edge.child_slot + 1, none);
        parent.child_positions.resize(edge.child_slot + 1);
      }
      parent.child_nodes[edge.child_slot] = static_cast<std::uint32_t>(edge.child.value);
      parent.child_positions[edge.child_slot] = positions(edge.parent_key);
      nodes[edge.child.value].slot = static_cast<std::uint32_t>(edge.child_slot);
    }
    for (const auto& node : source) {
      auto& n = nodes[node.id.value];
      n.native = node.kind == NodeKind::native;
      n.connex = node.connex;
      n.parent = node.parent ? static_cast<std::uint32_t>(node.parent->value) : none;
      n.children = static_cast<std::uint32_t>(node.children.size());
      n.arity = static_cast<std::uint32_t>(node.scope.size());
      require(n.child_nodes.size() == n.children, "edge slots differ from children");
      for (const auto child : n.child_nodes) require(child != none, "missing child edge");
      n.parent_positions = positions(node.parent_key);
      if (node.connex) {
        n.visible_positions = positions(*node.visible_projection);
        for (const auto position : n.visible_positions) n.visible_variables.push_back(static_cast<std::uint32_t>(node.scope[position].value));
      }
      if (!n.native) {
        n.generalized_place.resize(n.children);
        for (std::uint32_t slot = 0; slot < n.children; ++slot) {
          const auto& place = n.child_positions[slot];
          require(place.size() == n.arity, "generalized child key does not cover the candidate");
          std::vector<bool> seen(n.arity, false);
          for (const auto field : place) { require(field < n.arity && !seen[field], "generalized child key is not a permutation"); seen[field] = true; }
          n.generalized_place[slot] = place;
        }
      }
      std::vector<std::vector<std::uint32_t>> record_indexes;
      if (n.native) record_indexes = n.child_positions;
      // Set mode: derivations | satisfied, child bits. Weighted mode: derivations |
      // satisfied, then one cached child support sum per slot.
      n.records = Table(n.arity, weighted ? 1 + n.children : 2, std::move(record_indexes));
      if (n.parent != none) n.support = Table(static_cast<std::uint32_t>(n.parent_positions.size()), 1, {});
    }
    // C* structure from the enumeration program (parent before child).
    const auto& steps = program.enumeration().steps;
    root = static_cast<std::uint32_t>(steps[0].node.value);
    for (std::size_t s = 0; s < steps.size(); ++s) {
      const auto id = static_cast<std::uint32_t>(steps[s].node.value);
      by_rank.push_back(id);
      nodes[id].rank = static_cast<std::uint32_t>(s);
    }
    for (const auto id : by_rank) {
      auto& n = nodes[id];
      if (id == root) continue;
      n.cparent = n.parent;
      auto& p = nodes[n.cparent];
      std::vector<std::uint32_t> in_parent, in_child;
      for (std::uint32_t i = 0; i < p.visible_variables.size(); ++i)
        for (std::uint32_t j = 0; j < n.visible_variables.size(); ++j)
          if (p.visible_variables[i] == n.visible_variables[j]) { in_parent.push_back(i); in_child.push_back(j); }
      const auto& step = steps[n.rank];
      require(step.parent_key && step.parent_key->fields().size() == in_parent.size(), "C* separator differs from the enumeration key");
      n.separator_positions = in_child;
      p.cchildren.push_back({id, in_parent});
    }
    for (const auto id : by_rank) {
      auto& n = nodes[id];
      std::vector<std::vector<std::uint32_t>> indexes;
      if (id != root) indexes.push_back(n.separator_positions);
      n.child_index_base = static_cast<std::uint32_t>(indexes.size());
      if (delta) for (const auto& child : n.cchildren) indexes.push_back(child.parent_positions);
      // Set mode: count | live, stamp. Weighted mode: weight, flags, stamp, old weight.
      n.visible = Table(static_cast<std::uint32_t>(n.visible_variables.size()), weighted ? 4 : 2, std::move(indexes));
      if (delta && id != root) n.live = Table(static_cast<std::uint32_t>(n.separator_positions.size()), 1, {});
    }
  }

  void build_inputs(const CompiledProgram& program) {
    const auto& catalog = program.source_catalog();
    bases.resize(catalog.tables.size());
    for (std::size_t t = 0; t < catalog.tables.size(); ++t)
      for (const auto& column : catalog.tables[t].columns) bases[t].types.push_back(column.type);
    const auto& sql = program.normalized();
    for (const auto& input : program.inputs()) {
      Input in;
      in.node = static_cast<std::uint32_t>(input.node.value);
      const auto physical_width = bases.at(input.base.value).types.size();
      std::vector<std::uint32_t> logical;  // logical field -> physical column
      if (sql) {
        const auto& adapter = sql->adapters.at(input.occurrence.value);
        require(adapter.base == input.base, "adapter base differs from input base");
        for (const auto& fixed : adapter.constant_columns)
          in.constant.emplace_back(static_cast<std::uint32_t>(fixed.column.value), encode_view(fixed.value));
        for (const auto& equality : adapter.equal_columns)
          in.equal.emplace_back(static_cast<std::uint32_t>(equality.left.value), static_cast<std::uint32_t>(equality.right.value));
        for (const auto id : adapter.predicates) {
          const auto& operation = std::get<program::BoundOperation>(sql->binding.expressions.at(id.value).node);
          in.predicates.push_back({operation.operation, operand(*sql, operation.arguments[0]), operand(*sql, operation.arguments[1])});
        }
        for (const auto& projection : adapter.projection) {
          const auto& column = std::get<program::BoundColumn>(sql->binding.expressions.at(projection.expression.value).node);
          require(column.occurrence == input.occurrence, "adapter projection reads another occurrence");
          logical.push_back(static_cast<std::uint32_t>(column.column.value));
        }
      } else {
        for (std::uint32_t c = 0; c < physical_width; ++c) logical.push_back(c);
      }
      for (const auto& equality : input.equalities)
        in.equal.emplace_back(logical.at(equality.left.value), logical.at(equality.right.value));
      for (const auto& fixed : input.constants)
        in.constant.emplace_back(logical.at(fixed.field.value), encode_view(fixed.value));
      for (const auto field : input.projection.fields()) in.map.push_back(logical.at(field.value));
      require(in.map.size() == nodes[in.node].arity, "input projection differs from node scope");
      require(nodes[in.node].native, "input routed to a generalized node");
      inputs.push_back(std::move(in));
    }
    const auto& routes = program.base_routes();
    for (std::size_t t = 0; t < routes.size() && t < bases.size(); ++t) {
      auto& base = bases[t];
      for (const auto occurrence : routes[t]) base.routes.push_back(static_cast<std::uint32_t>(occurrence.value));
      bool injective = base.routes.size() == 1;
      if (injective) {
        const auto& in = inputs.at(base.routes[0]);
        std::vector<bool> covered(base.types.size(), false);
        for (const auto column : in.map) covered.at(column) = true;
        for (const auto& [column, value] : in.constant) covered.at(column) = true;
        for (bool changed = true; changed;) {
          changed = false;
          for (const auto& [left, right] : in.equal)
            if (covered[left] != covered[right]) { covered[left] = covered[right] = true; changed = true; }
        }
        injective = std::all_of(covered.begin(), covered.end(), [](bool value) { return value; });
      }
      base.dedupe = !base.routes.empty() && !injective;
      if (base.dedupe) base.rows = Table(static_cast<std::uint32_t>(base.types.size()), 0, {});
    }
  }

  void build_plans(const CompiledProgram& program) {
    const auto& enumeration = program.enumeration();
    // Snapshot: the compiled parent-before-child order from the root.
    for (const auto id : by_rank) {
      Step step;
      step.node = id;
      if (id != root) {
        const auto& p = nodes[nodes[id].cparent];
        step.from = nodes[nodes[id].cparent].rank;
        step.index = 0;
        for (const auto& child : p.cchildren) if (child.node == id) step.key_positions = child.parent_positions;
      }
      snapshot_plan.steps.push_back(std::move(step));
    }
    // The result view is the SQL output list when the program was normalized
    // from SQL (reordered/repeated core columns and constants), else the core head.
    std::vector<ScalarType> core_types;
    for (const auto& slot : enumeration.output) {
      const auto& node = program.nodes()[enumeration.steps[slot.step].node.value];
      const auto variable = nodes[node.id.value].visible_variables.at(slot.field.value);
      core_types.push_back(program.query().variables.at(variable).type);
    }
    const auto& sql = program.normalized();
    if (sql && !sql->outputs.empty()) {
      for (const auto& output : sql->outputs) {
        if (const auto* core = std::get_if<frontend::CoreOutput>(&output.value)) {
          require(core->column < core_types.size(), "SQL output names a missing core column");
          output_core.push_back(static_cast<std::int64_t>(core->column));
          output_types.push_back(core_types[core->column]);
          output_constants.push_back(0);
        } else {
          const auto& constant = std::get<program::ConstantOutput>(output.value).value;
          output_core.push_back(-1);
          output_constants.push_back(encode_view(constant));
          output_types.push_back(std::holds_alternative<std::int64_t>(constant) ? ScalarType::int64 :
              std::holds_alternative<std::string_view>(constant) ? ScalarType::string : ScalarType::boolean);
        }
      }
    } else {
      for (std::size_t i = 0; i < core_types.size(); ++i) {
        output_core.push_back(static_cast<std::int64_t>(i));
        output_types.push_back(core_types[i]);
        output_constants.push_back(0);
      }
    }
    require(output_core.size() <= 256, "more than 256 output columns");
    auto final_output = [&](const std::vector<std::pair<std::uint32_t, std::uint32_t>>& core) {
      std::vector<std::pair<std::uint32_t, std::uint32_t>> out;
      for (std::size_t i = 0; i < output_core.size(); ++i)
        out.push_back(output_core[i] < 0 ? std::pair{none, static_cast<std::uint32_t>(i)} : core.at(static_cast<std::size_t>(output_core[i])));
      return out;
    };
    {
      std::vector<std::pair<std::uint32_t, std::uint32_t>> core;
      for (const auto& slot : enumeration.output)
        core.emplace_back(static_cast<std::uint32_t>(slot.step), static_cast<std::uint32_t>(slot.field.value));
      snapshot_plan.output = final_output(core);
    }
    if (!delta) return;
    anchor.resize(nodes.size());
    for (const auto a : by_rank) {
      Plan plan;
      std::vector<std::uint32_t> step_of(nodes.size(), none);
      Step first;
      first.node = a;
      plan.steps.push_back(first);
      step_of[a] = 0;
      for (auto current = a; nodes[current].cparent != none;) {
        const auto p = nodes[current].cparent;
        const auto& parent = nodes[p];
        std::uint32_t j = 0;
        while (parent.cchildren[j].node != current) ++j;
        Step step;
        step.node = p;
        step.from = step_of[current];
        step.index = parent.child_index_base + j;
        step.key_positions = nodes[current].separator_positions;
        step.live = true;
        step.prune = true;
        step_of[p] = static_cast<std::uint32_t>(plan.steps.size());
        plan.steps.push_back(std::move(step));
        current = p;
      }
      for (std::size_t s = 0; s < plan.steps.size(); ++s) {
        const auto bound = plan.steps[s].node;
        for (const auto& child : nodes[bound].cchildren) {
          if (step_of[child.node] != none) continue;
          Step step;
          step.node = child.node;
          step.from = static_cast<std::uint32_t>(s);
          step.index = 0;
          step.key_positions = child.parent_positions;
          step.prune = nodes[child.node].rank < nodes[a].rank;
          step_of[child.node] = static_cast<std::uint32_t>(plan.steps.size());
          plan.steps.push_back(std::move(step));
        }
      }
      require(plan.steps.size() == by_rank.size(), "anchored plan does not cover C*");
      std::vector<std::pair<std::uint32_t, std::uint32_t>> core;
      for (const auto& slot : enumeration.output)
        core.emplace_back(step_of[enumeration.steps[slot.step].node.value], static_cast<std::uint32_t>(slot.field.value));
      plan.output = final_output(core);
      anchor[a] = std::move(plan);
    }
  }
};

}  // namespace crown::runtime::flat_detail
