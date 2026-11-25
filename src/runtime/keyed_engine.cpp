#include "crown/runtime/keyed_engine.hpp"
#include "crown/annotations/policy.hpp"
#include "crown/api/error.hpp"

#include <algorithm>
#include <array>
#include <map>
#include <optional>
#include <vector>

namespace crown::runtime::keyed {
namespace {
using storage::RowView;
using storage::ScalarView;
using storage::keyed::Collector;
using storage::keyed::Key;
using storage::keyed::KeyDomain;
using storage::keyed::KeyMap;
using storage::keyed::no_entry;

constexpr std::uint32_t none = 0xffffffffU;
constexpr std::size_t max_arity = 64;
constexpr std::size_t max_nodes = 64;
constexpr std::uint64_t live_bit = 1ULL << 32;

[[noreturn, gnu::cold, gnu::noinline]] void fail(const char* message) { throw Error("keyed_engine", message); }
inline void require(bool value, const char* message) {
  if (!value) [[unlikely]] fail(message);
}
inline std::uint32_t low(std::uint64_t w) { return static_cast<std::uint32_t>(w); }
inline std::uint32_t high(std::uint64_t w) { return static_cast<std::uint32_t>(w >> 32); }
inline std::uint64_t pack(std::uint32_t lo, std::uint32_t hi) { return (static_cast<std::uint64_t>(hi) << 32) | lo; }

// A map plus the domains of the keys its entries own (one reference each).
struct Store {
  KeyMap map;
  KeyDomain* primary = nullptr;
  std::vector<KeyDomain*> secondary;
};

struct Operand { bool column = false; std::uint32_t index = 0; ScalarView value{}; };
struct Predicate { frontend::SqlOperator operation; Operand left, right; };
struct Input {
  std::uint32_t node = 0;
  std::vector<std::uint32_t> map;                       // record field -> physical column
  std::vector<std::vector<std::uint32_t>> child_keys;   // per child slot, over the physical row
  std::vector<std::pair<std::uint32_t, std::uint32_t>> equal;
  std::vector<std::pair<std::uint32_t, ScalarView>> constant;
  std::vector<Predicate> predicates;
};
struct Base {
  std::vector<std::uint32_t> routes;
  std::size_t width = 0;
  bool dedupe = false;
  // One unfiltered route whose record is a permutation of the row: the node's
  // records are exactly the retained rows, so `rows` stays empty and the
  // record store answers presence (one hash probe per event instead of two).
  bool elided = false;
  std::vector<std::uint32_t> column_of_field;  // elided: record field -> row column
  KeyDomain* domain = nullptr;
  Store rows;
};
struct CChild { std::uint32_t node; };
struct Node {
  bool native = true, connex = false;
  std::uint32_t parent = none, slot = 0, children = 0, arity = 0;
  std::vector<std::uint32_t> child_nodes;                   // by slot
  KeyDomain* record_domain = nullptr;
  std::vector<KeyDomain*> edge_domain;                      // by slot (shared with the child's support)
  std::vector<std::vector<std::uint32_t>> child_from_record;  // by slot, over record cells
  std::vector<std::vector<std::uint32_t>> generalized_place;  // by slot: separator field -> record field
  KeyDomain* support_domain = nullptr;
  std::vector<std::uint32_t> support_from_record;
  KeyDomain* visible_domain = nullptr;
  std::vector<std::uint32_t> visible_from_record;
  KeyDomain* down_domain = nullptr;                         // separator with the C* parent
  std::vector<std::uint32_t> down_from_record;
  std::vector<std::vector<std::uint32_t>> cchild_from_record;  // per C* child, over record cells
  Store records, support, visible, live;
  std::uint32_t rank = none, cparent = none, child_base = 0;
  std::vector<CChild> cchildren;
  std::vector<std::uint32_t> changed;
};
struct Step {
  std::uint32_t node = 0, from = none, index = 0, source_secondary = 0;
  bool live = false, prune = false;
};
struct Plan {
  std::vector<Step> steps;
  std::vector<std::pair<std::uint32_t, std::uint32_t>> output;  // (step, field); step none = constant
  std::vector<std::pair<std::uint32_t, std::uint32_t>> other;   // the other result view (snapshot plan)
};

std::vector<std::uint32_t> fields(const storage::AccountedProjection& projection) {
  std::vector<std::uint32_t> out;
  for (const auto field : projection.fields()) out.push_back(static_cast<std::uint32_t>(field.value));
  return out;
}
std::vector<std::uint32_t> compose(const std::vector<std::uint32_t>& outer, const std::vector<std::uint32_t>& inner) {
  std::vector<std::uint32_t> out;
  for (const auto position : inner) out.push_back(outer.at(position));
  return out;
}

std::optional<ScalarType> operand_type(const program::NormalizedSql& sql, frontend::OccurrenceId occurrence,
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
    return storage::type_of(*literal->value);
  }
  if (const auto* operation = std::get_if<program::BoundOperation>(&node))
    if ((operation->operation == frontend::SqlOperator::identity_cast ||
         operation->operation == frontend::SqlOperator::widen_integer) && operation->arguments.size() == 1)
      return operand_type(sql, occurrence, operation->arguments[0], depth + 1);
  return std::nullopt;
}
bool simple_predicate(const program::NormalizedSql& sql, frontend::OccurrenceId occurrence, frontend::ExpressionId id) {
  const auto* operation = std::get_if<program::BoundOperation>(&sql.binding.expressions.at(id.value).node);
  if (!operation || operation->arguments.size() != 2) return false;
  using enum frontend::SqlOperator;
  const auto op = operation->operation;
  if (op != equal && op != not_equal && op != less && op != less_equal && op != greater && op != greater_equal) return false;
  const auto left = operand_type(sql, occurrence, operation->arguments[0]);
  const auto right = operand_type(sql, occurrence, operation->arguments[1]);
  return left && right && *left == *right;
}

std::string check(const CompiledProgram& program) {
  if (program.route() != PhysicalRoute::tree) return "constant program routes";
  for (const auto& table : program.source_catalog().tables)
    for (const auto& constraint : table.constraints)
      if (std::visit([](const auto& value) { return value.status == ConstraintStatus::enforced; }, constraint))
        return "enforced source constraints";
  const auto& nodes = program.nodes();
  if (nodes.size() > max_nodes) return "more than 64 tree nodes";
  for (const auto& node : nodes) {
    if (node.scope.size() > max_arity) return "node scope wider than 64 variables";
    if (node.children.size() > 64) return "more than 64 children";
    const auto layout = node.layout.fields();
    if (layout.size() != node.scope.size()) return "node layout differs from scope";
    for (std::size_t i = 0; i < layout.size(); ++i)
      if (layout[i].variable && *layout[i].variable != node.scope[i]) return "node layout order differs from scope";
    if (node.connex && !node.visible_projection) return "connex node without visible projection";
  }
  if (const auto& sql = program.normalized())
    for (const auto& adapter : sql->adapters) {
      for (const auto id : adapter.predicates)
        if (!simple_predicate(*sql, adapter.occurrence, id)) return "SQL input predicates other than column/literal comparisons";
      for (const auto& projection : adapter.projection)
        if (!std::holds_alternative<program::BoundColumn>(sql->binding.expressions.at(projection.expression.value).node))
          return "computed SQL input projections";
    }
  const auto& steps = program.enumeration().steps;
  if (steps.empty() || steps.size() > max_nodes) return "unsupported enumeration program";
  if (program.enumeration().output.size() > 256) return "more than 256 output columns";
  if (nodes[steps[0].node.value].parent) return "C* root is not the tree root";
  std::vector<bool> in_cstar(nodes.size(), false);
  for (std::size_t s = 0; s < steps.size(); ++s) {
    const auto& node = nodes[steps[s].node.value];
    if (!node.connex || !node.visible_relation || steps[s].relation != *node.visible_relation)
      return "enumeration step is not a connex visible relation";
    if (s > 0 && (!steps[s].parent_step || !node.parent || steps[*steps[s].parent_step].node != *node.parent))
      return "C* parent differs from tree parent";
    in_cstar[node.id.value] = true;
  }
  for (const auto& node : nodes) if (node.connex != in_cstar[node.id.value]) return "connex nodes differ from C* steps";
  return {};
}

bool compare(frontend::SqlOperator operation, const ScalarView& a, const ScalarView& b) {
  const auto order = a <=> b;
  switch (operation) {
    case frontend::SqlOperator::equal: return order == 0;
    case frontend::SqlOperator::not_equal: return order != 0;
    case frontend::SqlOperator::less: return order < 0;
    case frontend::SqlOperator::less_equal: return order <= 0;
    case frontend::SqlOperator::greater: return order > 0;
    default: return order >= 0;
  }
}
}  // namespace

struct SetEngine::Impl {
  CompiledProgram program;
  EngineOptions options;
  storage::keyed::Budget budget;
  Collector collector;
  std::map<std::pair<std::vector<std::uint32_t>, std::vector<ScalarType>>, std::unique_ptr<KeyDomain>> domains;
  std::vector<std::unique_ptr<KeyDomain>> private_domains;
  std::vector<Node> nodes;
  std::vector<Input> inputs;
  std::vector<Base> bases;
  std::vector<std::uint32_t> by_rank;
  std::uint32_t root = 0;
  Plan snapshot_plan;
  std::vector<Plan> anchor;
  std::vector<ScalarType> output_types;
  std::vector<std::int64_t> output_core;
  std::vector<ScalarView> output_constants;
  std::vector<std::int64_t> other_core;  // the result view other than options.sql_view
  std::vector<ScalarView> other_constants;
  std::vector<ScalarType> variable_types;
  std::uint64_t route = 0;
  EngineStatistics stats;
  // Transaction state.
  enum class UndoKind : std::uint8_t { word, insert, detach, acquire };
  struct Undo { UndoKind kind; std::uint32_t id; std::uint32_t index; void* target; std::uint64_t old; Key key; };
  std::vector<Undo> undo;
  std::vector<std::pair<Store*, std::uint32_t>> detached;
  bool open = false;
  std::size_t readers = 0;
  std::size_t live_rows = 0, live_rows_at_begin = 0;
  mutable std::uint64_t emitted = 0;  // rows passed to the sink in the current route
  // Cell buffers reused by enumeration, generalized propagation and route
  // reports (constructed once: a ScalarView array is not free to build).
  mutable std::vector<ScalarView> out_cells = std::vector<ScalarView>(256), out_scratch = std::vector<ScalarView>(256);
  std::vector<ScalarView> generalized_cells = std::vector<ScalarView>(max_arity), report_cells = std::vector<ScalarView>(max_arity);
  // Visible payload words. Set: [count | live_bit, route stamp]. Bag: [weight,
  // live flag, route stamp, weight at the route's first touch].
  std::uint32_t live_word = 0, stamp_word = 1;
  std::uint64_t live_mask = live_bit;
  // Bag mode: native record payload [multiplicity, satisfied slots, child sums...].
  annotations::MultiplicityPolicy policy;
  std::vector<std::uint64_t> outside_mask;  // per node: child slots outside C*
  std::uint64_t root_total = 0, root_total_at_begin = 0;
  // Elided source change staged by stage_source, routed next (its probe result).
  struct ElidedProbe { std::uint32_t occurrence = none, id = no_entry; Key found{}; bool has_found = false; };
  ElidedProbe elided_probe;

  Impl(const CompiledProgram& source, EngineOptions value)
      : program(source), options(value), budget(value.memory_limit_bytes), collector(value.gc),
        policy(value.multiplicity_limit) {
    budget.set_reclaimer(&collector);
    if (auto problem = check(program); !problem.empty()) fail(problem.c_str());
    if (options.bag) { live_word = 1; stamp_word = 2; live_mask = 1; }
    for (const auto& node : program.nodes()) {
      const auto layout = node.layout.fields();
      for (std::size_t i = 0; i < node.scope.size(); ++i) {
        const auto variable = node.scope[i].value;
        if (variable_types.size() <= variable) variable_types.resize(variable + 1, ScalarType::int64);
        variable_types[variable] = layout[i].type;
      }
    }
    build_nodes();
    build_inputs();
    build_plans();
    outside_mask.assign(nodes.size(), 0);
    for (std::size_t v = 0; v < nodes.size(); ++v)
      for (std::uint32_t slot = 0; slot < nodes[v].children; ++slot)
        if (!nodes[nodes[v].child_nodes[slot]].connex) outside_mask[v] |= 1ULL << slot;
  }

  // --------------------------------------------------------------- analysis
  KeyDomain* domain(std::vector<std::uint32_t> variables, bool canonical) {
    if (canonical) std::sort(variables.begin(), variables.end());
    std::vector<ScalarType> types;
    for (const auto variable : variables) types.push_back(variable_types.at(variable));
    auto& slot = domains[{variables, types}];
    if (!slot) slot = std::make_unique<KeyDomain>(types, &collector, &budget);
    return slot.get();
  }
  // Positions, over cells whose variables are `source`, of `variables` in canonical order.
  static std::vector<std::uint32_t> locate(const std::vector<std::uint32_t>& source, std::vector<std::uint32_t> variables) {
    std::sort(variables.begin(), variables.end());
    std::vector<std::uint32_t> out;
    for (const auto variable : variables) {
      const auto found = std::find(source.begin(), source.end(), variable);
      require(found != source.end(), "projection variable missing from its source");
      out.push_back(static_cast<std::uint32_t>(found - source.begin()));
    }
    return out;
  }
  static std::vector<std::uint32_t> variables_at(const std::vector<std::uint32_t>& source, const std::vector<std::uint32_t>& positions) {
    std::vector<std::uint32_t> out;
    for (const auto position : positions) out.push_back(source.at(position));
    return out;
  }

  void build_nodes() {
    const auto& source = program.nodes();
    nodes.resize(source.size());
    std::vector<std::vector<std::uint32_t>> scope(source.size()), visible(source.size());
    for (const auto& node : source) {
      for (const auto variable : node.scope) scope[node.id.value].push_back(static_cast<std::uint32_t>(variable.value));
      if (node.connex) visible[node.id.value] = variables_at(scope[node.id.value], fields(*node.visible_projection));
    }
    for (const auto& node : source) {
      auto& n = nodes[node.id.value];
      const auto id = static_cast<std::uint32_t>(node.id.value);
      n.native = node.kind == NodeKind::native;
      n.connex = node.connex;
      n.parent = node.parent ? static_cast<std::uint32_t>(node.parent->value) : none;
      n.children = static_cast<std::uint32_t>(node.children.size());
      n.arity = static_cast<std::uint32_t>(node.scope.size());
      n.record_domain = domain(scope[id], false);
      n.child_nodes.assign(n.children, none);
      n.edge_domain.assign(n.children, nullptr);
      n.child_from_record.resize(n.children);
      if (n.parent != none) {
        const auto separator = variables_at(scope[id], fields(node.parent_key));
        n.support_domain = domain(separator, true);
        n.support_from_record = locate(scope[id], separator);
      }
      if (n.connex) {
        n.visible_domain = domain(visible[id], false);
        n.visible_from_record = fields(*node.visible_projection);
      }
    }
    for (const auto& edge : program.edges()) {
      auto& parent = nodes[edge.parent.value];
      const auto slot = edge.child_slot;
      require(slot < parent.children, "edge slot out of range");
      parent.child_nodes[slot] = static_cast<std::uint32_t>(edge.child.value);
      nodes[edge.child.value].slot = static_cast<std::uint32_t>(slot);
      const auto separator = variables_at(scope[edge.parent.value], fields(edge.parent_key));
      parent.edge_domain[slot] = domain(separator, true);
      require(parent.edge_domain[slot] == nodes[edge.child.value].support_domain, "edge separator differs from child support key");
      parent.child_from_record[slot] = locate(scope[edge.parent.value], separator);
      if (!parent.native) {
        auto& place = parent.generalized_place;
        place.resize(parent.children);
        std::vector<std::uint32_t> sorted = separator;
        std::sort(sorted.begin(), sorted.end());
        require(sorted.size() == parent.arity, "generalized child key does not cover the candidate");
        place[slot].clear();
        for (const auto variable : sorted) {
          const auto& own = scope[edge.parent.value];
          place[slot].push_back(static_cast<std::uint32_t>(std::find(own.begin(), own.end(), variable) - own.begin()));
        }
      }
    }
    for (const auto& n : nodes) for (const auto child : n.child_nodes) require(child != none, "missing child edge");
    const auto& steps = program.enumeration().steps;
    root = static_cast<std::uint32_t>(steps[0].node.value);
    for (std::size_t s = 0; s < steps.size(); ++s) {
      const auto id = static_cast<std::uint32_t>(steps[s].node.value);
      by_rank.push_back(id);
      nodes[id].rank = static_cast<std::uint32_t>(s);
    }
    std::vector<std::vector<std::uint32_t>> cseparator(nodes.size());
    for (const auto id : by_rank) {
      if (id == root) continue;
      auto& n = nodes[id];
      n.cparent = n.parent;
      std::vector<std::uint32_t> shared;
      for (const auto variable : visible[id])
        if (std::find(visible[n.cparent].begin(), visible[n.cparent].end(), variable) != visible[n.cparent].end())
          shared.push_back(variable);
      const auto& step = steps[n.rank];
      require(step.parent_key && step.parent_key->fields().size() == shared.size(), "C* separator differs from the enumeration key");
      cseparator[id] = shared;
      n.down_domain = domain(shared, true);
      n.down_from_record = compose(n.visible_from_record, locate(visible[id], shared));
      nodes[n.cparent].cchildren.push_back({id});
    }
    for (std::size_t v = 0; v < nodes.size(); ++v) {
      auto& n = nodes[v];
      for (const auto& child : n.cchildren)
        n.cchild_from_record.push_back(compose(n.visible_from_record, locate(visible[v], cseparator[child.node])));
      // Stores and the domains of the keys their entries own.
      n.records.primary = n.record_domain;
      if (n.native) n.records.secondary = n.edge_domain;
      n.records.map = KeyMap(options.bag ? 2 + n.children : 2, static_cast<std::uint32_t>(n.records.secondary.size()), &budget);
      if (n.parent != none) { n.support.primary = n.support_domain; n.support.map = KeyMap(1, 0, &budget); }
      if (n.connex) {
        n.visible.primary = n.visible_domain;
        if (static_cast<std::uint32_t>(v) != root) n.visible.secondary.push_back(n.down_domain);
        n.child_base = static_cast<std::uint32_t>(n.visible.secondary.size());
        for (const auto& child : n.cchildren) n.visible.secondary.push_back(nodes[child.node].down_domain);
        n.visible.map = KeyMap(options.bag ? 4 : 2, static_cast<std::uint32_t>(n.visible.secondary.size()), &budget);
        if (static_cast<std::uint32_t>(v) != root) { n.live.primary = n.down_domain; n.live.map = KeyMap(1, 0, &budget); }
      }
    }
  }

  Operand operand(const program::NormalizedSql& sql, frontend::ExpressionId id) {
    const auto& node = sql.binding.expressions.at(id.value).node;
    if (const auto* column = std::get_if<program::BoundColumn>(&node))
      return {true, static_cast<std::uint32_t>(column->column.value), {}};
    if (const auto* literal = std::get_if<program::BoundLiteral>(&node)) return {false, 0, *literal->value};
    return operand(sql, std::get<program::BoundOperation>(node).arguments[0]);
  }
  void build_inputs() {
    const auto& catalog = program.source_catalog();
    bases.resize(catalog.tables.size());
    for (std::size_t t = 0; t < catalog.tables.size(); ++t) bases[t].width = catalog.tables[t].columns.size();
    const auto& sql = program.normalized();
    for (const auto& input : program.inputs()) {
      Input in;
      in.node = static_cast<std::uint32_t>(input.node.value);
      require(nodes[in.node].native, "input routed to a generalized node");
      std::vector<std::uint32_t> logical;
      if (sql) {
        const auto& adapter = sql->adapters.at(input.occurrence.value);
        for (const auto& fixed : adapter.constant_columns)
          in.constant.emplace_back(static_cast<std::uint32_t>(fixed.column.value), fixed.value);
        for (const auto& equality : adapter.equal_columns)
          in.equal.emplace_back(static_cast<std::uint32_t>(equality.left.value), static_cast<std::uint32_t>(equality.right.value));
        for (const auto id : adapter.predicates) {
          const auto& operation = std::get<program::BoundOperation>(sql->binding.expressions.at(id.value).node);
          in.predicates.push_back({operation.operation, operand(*sql, operation.arguments[0]), operand(*sql, operation.arguments[1])});
        }
        for (const auto& projection : adapter.projection)
          logical.push_back(static_cast<std::uint32_t>(
              std::get<program::BoundColumn>(sql->binding.expressions.at(projection.expression.value).node).column.value));
      } else {
        for (std::uint32_t c = 0; c < bases.at(input.base.value).width; ++c) logical.push_back(c);
      }
      for (const auto& equality : input.equalities) in.equal.emplace_back(logical.at(equality.left.value), logical.at(equality.right.value));
      for (const auto& fixed : input.constants) in.constant.emplace_back(logical.at(fixed.field.value), fixed.value);
      for (const auto field : input.projection.fields()) in.map.push_back(logical.at(field.value));
      require(in.map.size() == nodes[in.node].arity, "input projection differs from node scope");
      for (const auto& positions : nodes[in.node].child_from_record) in.child_keys.push_back(compose(in.map, positions));
      inputs.push_back(std::move(in));
    }
    const auto& routes = program.base_routes();
    for (std::size_t t = 0; t < routes.size() && t < bases.size(); ++t) {
      auto& base = bases[t];
      for (const auto occurrence : routes[t]) base.routes.push_back(static_cast<std::uint32_t>(occurrence.value));
      bool injective = base.routes.size() == 1;
      if (injective) {
        const auto& in = inputs.at(base.routes[0]);
        std::vector<bool> covered(base.width, false);
        for (const auto column : in.map) covered.at(column) = true;
        for (const auto& item : in.constant) covered.at(item.first) = true;
        for (bool changed = true; changed;) {
          changed = false;
          for (const auto& [left, right] : in.equal)
            if (covered[left] != covered[right]) { covered[left] = covered[right] = true; changed = true; }
        }
        injective = std::all_of(covered.begin(), covered.end(), [](bool value) { return value; });
      }
      base.dedupe = !base.routes.empty() && !injective;
      if (injective && !options.bag) {
        const auto& in = inputs.at(base.routes[0]);
        std::vector<bool> seen(base.width, false);
        bool permutation = in.map.size() == base.width && in.constant.empty() && in.equal.empty() && in.predicates.empty();
        for (const auto column : in.map) permutation = permutation && column < base.width && !seen[column] && (seen[column] = true);
        if (permutation) { base.elided = true; base.column_of_field = in.map; }
      }
    }
    // Every source table retains its physical rows (set semantics at the source).
    for (std::size_t t = 0; t < bases.size(); ++t) {
      auto& base = bases[t];
      std::vector<ScalarType> types;
      for (const auto& column : catalog.tables[t].columns) types.push_back(column.type);
      private_domains.push_back(std::make_unique<KeyDomain>(types, &collector, &budget));
      base.domain = private_domains.back().get();
      base.rows.primary = base.domain;
      base.rows.map = KeyMap(0, 0, &budget);
    }
  }

  void build_plans() {
    const auto& enumeration = program.enumeration();
    std::vector<std::pair<std::uint32_t, std::uint32_t>> core;
    for (const auto& slot : enumeration.output) {
      const auto node = static_cast<std::uint32_t>(enumeration.steps[slot.step].node.value);
      core.emplace_back(nodes[node].rank, static_cast<std::uint32_t>(slot.field.value));
    }
    std::vector<ScalarType> core_types;
    for (const auto& [rank, field] : core) core_types.push_back(nodes[by_rank[rank]].visible_domain->types()[field]);
    // Both result views: the core head and (programs from SQL) the SQL
    // output list. Stage-time enumeration emits options.sql_view's view;
    // cursors may ask for either.
    std::vector<std::int64_t> core_map, sql_map;
    std::vector<ScalarType> core_view_types, sql_view_types;
    std::vector<ScalarView> core_constants, sql_constants;
    for (std::size_t i = 0; i < core.size(); ++i) {
      core_map.push_back(static_cast<std::int64_t>(i));
      core_view_types.push_back(core_types[i]);
      core_constants.emplace_back();
    }
    const auto& sql = program.normalized();
    if (sql && !sql->outputs.empty()) {
      for (const auto& output : sql->outputs) {
        if (const auto* column = std::get_if<frontend::CoreOutput>(&output.value)) {
          require(column->column < core.size(), "SQL output names a missing core column");
          sql_map.push_back(static_cast<std::int64_t>(column->column));
          sql_view_types.push_back(core_types[column->column]);
          sql_constants.emplace_back();
        } else {
          const auto& constant = std::get<program::ConstantOutput>(output.value).value;
          sql_map.push_back(-1);
          sql_view_types.push_back(storage::type_of(constant));
          sql_constants.push_back(constant);
        }
      }
    } else {
      sql_map = core_map; sql_view_types = core_view_types; sql_constants = core_constants;
    }
    if (options.sql_view) {
      output_core = sql_map; output_types = sql_view_types; output_constants = sql_constants;
      other_core = core_map; other_constants = core_constants;
    } else {
      output_core = core_map; output_types = core_view_types; output_constants = core_constants;
      other_core = sql_map; other_constants = sql_constants;
    }
    auto map_output = [&](const std::vector<std::pair<std::uint32_t, std::uint32_t>>& slots, const std::vector<std::int64_t>& view) {
      std::vector<std::pair<std::uint32_t, std::uint32_t>> out;
      for (std::size_t i = 0; i < view.size(); ++i)
        out.push_back(view[i] < 0 ? std::pair{none, static_cast<std::uint32_t>(i)} : slots.at(static_cast<std::size_t>(view[i])));
      return out;
    };
    auto final_output = [&](const std::vector<std::pair<std::uint32_t, std::uint32_t>>& slots) { return map_output(slots, output_core); };
    // Snapshot plan: the compiled parent-before-child order.
    for (const auto id : by_rank) {
      Step step;
      step.node = id;
      if (id != root) {
        const auto& parent = nodes[nodes[id].cparent];
        std::uint32_t j = 0;
        while (parent.cchildren[j].node != id) ++j;
        step.from = parent.rank;
        step.index = 0;
        step.source_secondary = parent.child_base + j;
      }
      snapshot_plan.steps.push_back(step);
    }
    snapshot_plan.output = final_output(core);
    snapshot_plan.other = map_output(core, other_core);
    // Anchored plans: the anchor, its ancestors upward, then every other C*
    // node downward from a bound neighbour.
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
        std::uint32_t j = 0;
        while (nodes[p].cchildren[j].node != current) ++j;
        Step step;
        step.node = p;
        step.from = step_of[current];
        step.index = nodes[p].child_base + j;
        step.source_secondary = 0;
        step.live = true;
        step.prune = true;
        step_of[p] = static_cast<std::uint32_t>(plan.steps.size());
        plan.steps.push_back(step);
        current = p;
      }
      for (std::size_t s = 0; s < plan.steps.size(); ++s) {
        const auto bound = plan.steps[s].node;
        for (std::uint32_t j = 0; j < nodes[bound].cchildren.size(); ++j) {
          const auto child = nodes[bound].cchildren[j].node;
          if (step_of[child] != none) continue;
          Step step;
          step.node = child;
          step.from = static_cast<std::uint32_t>(s);
          step.index = 0;
          step.source_secondary = nodes[bound].child_base + j;
          step.prune = nodes[child].rank < nodes[a].rank;
          step_of[child] = static_cast<std::uint32_t>(plan.steps.size());
          plan.steps.push_back(step);
        }
      }
      require(plan.steps.size() == by_rank.size(), "anchored plan does not cover C*");
      std::vector<std::pair<std::uint32_t, std::uint32_t>> slots;
      for (const auto& [rank, field] : core) slots.emplace_back(step_of[by_rank[rank]], field);
      plan.output = final_output(slots);
      anchor[a] = std::move(plan);
    }
  }

  // ------------------------------------------------------------ transaction
  void reserve() { if (undo.size() == undo.capacity()) undo.reserve(undo.size() * 2 + 64); }
  Key acquire(KeyDomain& domain, const ScalarView* cells, const std::uint32_t* positions) {
    reserve();
    if (!domain.inline_form()) collector.reserve(1);  // rollback may retire it
    const auto key = domain.acquire(cells, positions);
    if (!domain.inline_form()) undo.push_back({UndoKind::acquire, 0, 0, &domain, 0, key});
    return key;
  }
  void retain(KeyDomain& domain, Key key) {
    reserve();
    if (!domain.inline_form()) collector.reserve(1);
    domain.retain(key);
    if (!domain.inline_form()) undo.push_back({UndoKind::acquire, 0, 0, &domain, 0, key});
  }
  std::uint32_t insert(Store& store, Key key, const Key* secondary = nullptr) {
    reserve();
    const auto id = store.map.insert(key, secondary);
    undo.push_back({UndoKind::insert, id, 0, &store, 0, {}});
    return id;
  }
  void erase(Store& store, std::uint32_t id) {
    reserve();
    if (detached.size() == detached.capacity()) detached.reserve(detached.size() * 2 + 16);
    collector.reserve(1 + store.secondary.size());  // commit retires its keys
    store.map.detach(id);
    undo.push_back({UndoKind::detach, id, 0, &store, 0, {}});
    detached.emplace_back(&store, id);
  }
  void write(Store& store, std::uint32_t id, std::uint32_t word, std::uint64_t value) {
    reserve();
    auto& slot = store.map.payload(id)[word];
    undo.push_back({UndoKind::word, id, word, &store, slot, {}});
    slot = value;
  }
  void begin() {
    require(!open, "a keyed transaction is already open");
    require(readers == 0, "result cursors are open; the writer must wait");
    open = true;
    live_rows_at_begin = live_rows;
    root_total_at_begin = root_total;
  }
  void commit() {
    require(open, "no keyed transaction to commit");
    require(elided_probe.occurrence == none, "a staged source change was not routed");
    // Erased entries give up their keys; a key's last reference retires it.
    for (const auto& [store, id] : detached) {
      store->primary->release(store->map.key(id));
      for (std::size_t s = 0; s < store->secondary.size(); ++s) store->secondary[s]->release(store->map.secondary(id, s));
      store->map.free_detached(id);
    }
    stats.undo_entries += undo.size();
    undo.clear();
    detached.clear();
    open = false;
    ++stats.commits;
    collector.seal();
  }
  void rollback() noexcept {
    if (!open) return;
    for (auto it = undo.rbegin(); it != undo.rend(); ++it) {
      switch (it->kind) {
        case UndoKind::word: static_cast<Store*>(it->target)->map.payload(it->id)[it->index] = it->old; break;
        case UndoKind::insert: static_cast<Store*>(it->target)->map.erase(it->id); break;
        case UndoKind::detach: static_cast<Store*>(it->target)->map.relink(it->id); break;
        case UndoKind::acquire: static_cast<KeyDomain*>(it->target)->release(it->key); break;
      }
    }
    for (auto& n : nodes) n.changed.clear();
    undo.clear();
    detached.clear();
    elided_probe = {};
    live_rows = live_rows_at_begin;
    root_total = root_total_at_begin;
    open = false;
    ++stats.rollbacks;
    collector.seal();
  }

  // ---------------------------------------------------------------- support
  RowView record_cells(const Node& n, std::uint32_t id, ScalarView* scratch) const {
    return n.record_domain->view(n.records.map.key(id), scratch);
  }
  void survivor(std::uint32_t v, std::uint32_t id, bool add) {
    auto& n = nodes[v];
    ScalarView scratch[2];  // inline keys decode up to two cells
    const auto cells = record_cells(n, id, scratch).cells().data();
    if (n.connex) visible_change(v, cells, add);
    if (n.parent != none) support_change(v, cells, add);
  }
  void visible_change(std::uint32_t v, const ScalarView* cells, bool add) {
    auto& n = nodes[v];
    auto& store = n.visible;
    const auto found = n.visible_domain->find(cells, n.visible_from_record.data());
    auto id = found ? store.map.find(*found) : no_entry;
    if (add) {
      if (id != no_entry) { write(store, id, 0, store.map.payload(id)[0] + 1); return; }
      std::array<Key, 65> secondary;
      std::size_t count = 0;
      if (n.down_domain && v != root) secondary[count++] = acquire(*n.down_domain, cells, n.down_from_record.data());
      for (std::size_t j = 0; j < n.cchildren.size(); ++j)
        secondary[count++] = acquire(*nodes[n.cchildren[j].node].down_domain, cells, n.cchild_from_record[j].data());
      const auto key = acquire(*n.visible_domain, cells, n.visible_from_record.data());
      id = insert(store, key, secondary.data());
      write(store, id, 0, 1);
      if (options.delta) { write(store, id, 1, route); n.changed.push_back(id); }
      return;
    }
    require(id != no_entry, "visible key underflow");
    const auto payload = store.map.payload(id)[0];
    require(low(payload) > 0, "visible count underflow");
    write(store, id, 0, payload - 1);
    if (low(payload) != 1) return;
    if (options.delta) { write(store, id, 1, route); n.changed.push_back(id); }
    else erase(store, id);
  }
  void support_change(std::uint32_t v, const ScalarView* cells, bool add) {
    auto& n = nodes[v];
    auto& store = n.support;
    const auto found = n.support_domain->find(cells, n.support_from_record.data());
    auto id = found ? store.map.find(*found) : no_entry;
    if (add) {
      if (id != no_entry) { write(store, id, 0, store.map.payload(id)[0] + 1); return; }
      const auto key = acquire(*n.support_domain, cells, n.support_from_record.data());
      id = insert(store, key);
      write(store, id, 0, 1);
      child_flip(n.parent, n.slot, key, true);
      return;
    }
    require(id != no_entry, "support key underflow");
    const auto count = store.map.payload(id)[0];
    write(store, id, 0, count - 1);
    if (count != 1) return;
    const auto key = store.map.key(id);
    erase(store, id);
    child_flip(n.parent, n.slot, key, false);
  }
  void child_flip(std::uint32_t p, std::uint32_t slot, Key key, bool appeared) {
    auto& n = nodes[p];
    const std::uint64_t bit = 1ULL << slot;
    if (n.native) {
      for (auto id = n.records.map.bucket(slot, key); id != no_entry;) {
        const auto next = n.records.map.next(slot, id);
        const auto* payload = n.records.map.payload(id);
        const auto satisfied = high(payload[0]);
        const auto bits = payload[1];
        require(((bits & bit) != 0) != appeared, "child presence applied twice");
        const auto now = appeared ? satisfied + 1 : satisfied - 1;
        write(n.records, id, 0, pack(low(payload[0]), now));
        write(n.records, id, 1, bits ^ bit);
        if ((satisfied == n.children) != (now == n.children)) survivor(p, id, now == n.children);
        id = next;
      }
      return;
    }
    ScalarView scratch[2];  // inline keys decode up to two cells
    const auto separator = n.edge_domain[slot]->view(key, scratch);
    ScalarView* const cells = generalized_cells.data();
    const auto& place = n.generalized_place[slot];
    for (std::size_t i = 0; i < place.size(); ++i) cells[place[i]] = separator[i];
    const auto found = n.record_domain->find(cells, identity(n.arity));
    auto id = found ? n.records.map.find(*found) : no_entry;
    if (appeared) {
      if (id == no_entry) id = insert(n.records, acquire(*n.record_domain, cells, identity(n.arity)));
      const auto* payload = n.records.map.payload(id);
      require((payload[1] & bit) == 0, "generalized presence applied twice");
      const auto satisfied = high(payload[0]) + 1;
      write(n.records, id, 1, payload[1] | bit);
      write(n.records, id, 0, pack(0, satisfied));
      if (satisfied == n.children) survivor(p, id, true);
      return;
    }
    require(id != no_entry, "generalized candidate missing");
    const auto* payload = n.records.map.payload(id);
    require((payload[1] & bit) != 0, "generalized presence removed twice");
    const auto satisfied = high(payload[0]);
    write(n.records, id, 1, payload[1] & ~bit);
    write(n.records, id, 0, pack(0, satisfied - 1));
    if (satisfied == n.children) survivor(p, id, false);
    if (satisfied == 1) erase(n.records, id);
  }
  static const std::uint32_t* identity(std::size_t) {
    static const auto positions = [] {
      std::array<std::uint32_t, max_arity> out{};
      for (std::uint32_t i = 0; i < max_arity; ++i) out[i] = i;
      return out;
    }();
    return positions.data();
  }

  // ------------------------------------------------------------------- live
  bool is_live(const Store& store, std::uint32_t id) const { return (store.map.payload(id)[live_word] & live_mask) != 0; }
  void make_live(std::uint32_t v, std::uint32_t id) {
    auto& n = nodes[v];
    write(n.visible, id, live_word, n.visible.map.payload(id)[live_word] | live_mask);
    ++live_rows;
    for (std::size_t j = 0; j < n.cchildren.size(); ++j) {
      const auto key = n.visible.map.secondary(id, n.child_base + j);
      auto& d = nodes[n.cchildren[j].node];
      const auto found = d.live.map.find(key);
      if (found != no_entry) { write(d.live, found, 0, d.live.map.payload(found)[0] + 1); continue; }
      retain(*d.down_domain, key);
      write(d.live, insert(d.live, key), 0, 1);
      for (auto f = d.visible.map.bucket(0, key); f != no_entry; f = d.visible.map.next(0, f))
        if (!is_live(d.visible, f)) make_live(n.cchildren[j].node, f);
    }
  }
  void make_dead(std::uint32_t v, std::uint32_t id) {
    auto& n = nodes[v];
    write(n.visible, id, live_word, n.visible.map.payload(id)[live_word] & ~live_mask);
    --live_rows;
    for (std::size_t j = 0; j < n.cchildren.size(); ++j) {
      const auto key = n.visible.map.secondary(id, n.child_base + j);
      auto& d = nodes[n.cchildren[j].node];
      const auto found = d.live.map.find(key);
      require(found != no_entry, "live separator underflow");
      const auto count = d.live.map.payload(found)[0];
      write(d.live, found, 0, count - 1);
      if (count > 1) continue;
      erase(d.live, found);
      for (auto f = d.visible.map.bucket(0, key); f != no_entry; f = d.visible.map.next(0, f))
        if (is_live(d.visible, f)) make_dead(n.cchildren[j].node, f);
    }
  }
  void bootstrap_live() {
    // Delta mode entry: every root key is live; liveness flows down.
    const auto& visible = nodes[root].visible.map;
    for (std::uint32_t id = 0; id < visible.ids(); ++id)
      if (visible.live(id) && !is_live(nodes[root].visible, id)) make_live(root, id);
  }

  // ------------------------------------------------------------ enumeration
  std::uint64_t enumerate(const Plan& plan, std::uint32_t first, SetOperation operation, RowSink* sink) const {
    const auto count = plan.steps.size();
    const KeyMap* maps[max_nodes];
    const KeyDomain* domains_of[max_nodes];
    for (std::size_t s = 0; s < count; ++s) {
      maps[s] = &nodes[plan.steps[s].node].visible.map;
      domains_of[s] = nodes[plan.steps[s].node].visible_domain;
    }
    std::uint32_t current[max_nodes];
    ScalarView* const out = out_cells.data();
    ScalarView* const scratch = out_scratch.data();
    const auto width = plan.output.size();
    const auto stamp = route;
    std::uint64_t rows = 0;
    auto valid = [&](std::size_t s, std::uint32_t id) {
      const auto& step = plan.steps[s];
      const auto* payload = maps[s]->payload(id);
      if (step.live && !(payload[live_word] & live_mask)) return false;
      if (step.prune && payload[stamp_word] == stamp) return false;
      return true;
    };
    auto advance = [&](std::size_t s, std::uint32_t id) {
      const auto index = plan.steps[s].index;
      while (id != no_entry && !valid(s, id)) id = maps[s]->next(index, id);
      return id;
    };
    auto open_step = [&](std::size_t s) {
      const auto& step = plan.steps[s];
      const auto key = maps[step.from]->secondary(current[step.from], step.source_secondary);
      return advance(s, maps[s]->bucket(step.index, key));
    };
    auto emit = [&] {
      for (std::size_t i = 0; i < width; ++i) {
        const auto [s, field] = plan.output[i];
        out[i] = s == none ? output_constants[field] : domains_of[s]->cell(maps[s]->key(current[s]), field, scratch[i]);
      }
      if (sink) sink->row(operation, RowView::borrow({out, width}));
      ++rows;
      ++emitted;
    };
    current[0] = first;
    if (count == 1) { emit(); return rows; }
    std::size_t s = 1;
    current[1] = open_step(1);
    for (;;) {
      if (current[s] == no_entry) {
        if (--s == 0) break;
        current[s] = advance(s, maps[s]->next(plan.steps[s].index, current[s]));
        continue;
      }
      if (s + 1 == count) {
        // The chain successor is fetched while this row is delivered.
        const auto following = maps[s]->next(plan.steps[s].index, current[s]);
        maps[s]->prefetch(following);
        emit();
        current[s] = advance(s, following);
        continue;
      }
      ++s;
      current[s] = open_step(s);
    }
    return rows;
  }

  // ------------------------------------------------------------------ apply
  bool stage(TableId table, SetOperation operation, RowView row, RowSink* sink, RouteObserver* observer = nullptr) {
    if (!stage_source(table, operation, row)) return false;
    const auto& base = bases.at(table.value);
    for (std::size_t i = 0; i < base.routes.size(); ++i) stage_route_at(table, i, operation, row, sink, observer);
    return true;
  }
  // The physical source change alone; false for a duplicate insert or absent erase.
  bool stage_source(TableId table, SetOperation operation, RowView row) {
    require(open, "stage outside a keyed transaction");
    require(!options.bag, "bag mode stages native weights, not source rows");
    auto& base = bases.at(table.value);
    require(row.size() == base.width, "row width differs from its source table");
    ++stats.events;
    const bool add = operation == SetOperation::insert;
    if (base.elided) {
      const auto occurrence = base.routes[0];
      const auto& in = inputs[occurrence];
      const auto& n = nodes[in.node];
      const auto found = n.record_domain->find(row.cells().data(), in.map.data());
      const auto id = found ? n.records.map.find(*found) : no_entry;
      if (add == (id != no_entry)) return false;
      elided_probe = {occurrence, id, found ? *found : Key{}, found.has_value()};
      ++stats.changed_events;
      return true;
    }
    const auto found = base.domain->find(row.cells());
    const auto id = found ? base.rows.map.find(*found) : no_entry;
    if (add) {
      if (id != no_entry) return false;
      insert(base.rows, acquire(*base.domain, row.cells().data(), identity(base.width)));
    } else {
      if (id == no_entry) return false;
      erase(base.rows, id);
    }
    ++stats.changed_events;
    return true;
  }
  void stage_route_at(TableId table, std::size_t index, SetOperation operation, RowView row, RowSink* sink, RouteObserver* observer) {
    require(open, "stage outside a keyed transaction");
    const auto& base = bases.at(table.value);
    stage_route(base, base.routes.at(index), index + 1, operation == SetOperation::insert, row, sink, observer);
  }
  bool stage_route(const Base& base, std::uint32_t occurrence, std::uint64_t prefix, bool add, RowView row,
      RowSink* sink, RouteObserver* observer) {
    const auto& in = inputs[occurrence];
    ++stats.routes;
    const auto* cells = row.cells().data();
    for (const auto& [left, right] : in.equal) if (!(cells[left] == cells[right])) return false;
    for (const auto& [column, value] : in.constant) if (!(cells[column] == value)) return false;
    for (const auto& predicate : in.predicates) {
      const auto& a = predicate.left.column ? cells[predicate.left.index] : predicate.left.value;
      const auto& b = predicate.right.column ? cells[predicate.right.index] : predicate.right.value;
      if (!compare(predicate.operation, a, b)) return false;
    }
    auto& n = nodes[in.node];
    std::optional<Key> found;
    std::uint32_t id = no_entry;
    if (elided_probe.occurrence == occurrence) {  // stage_source already probed this record
      if (elided_probe.has_found) found = elided_probe.found;
      id = elided_probe.id;
      elided_probe = {};
    } else {
      found = n.record_domain->find(cells, in.map.data());
      id = found ? n.records.map.find(*found) : no_entry;
    }
    // Report the derivation change of this route (crossing or count-only).
    auto report = [&](std::uint64_t before, std::uint64_t after, bool crossing, bool before_answer, std::uint64_t changed_keys) {
      if (!observer) return;
      ScalarView* const record = report_cells.data();
      for (std::size_t i = 0; i < in.map.size(); ++i) record[i] = cells[in.map[i]];
      RouteReport value;
      value.occurrence = occurrence; value.node = in.node; value.prefix = prefix;
      value.record = RowView::borrow({record, in.map.size()});
      value.before = before; value.after = after; value.crossing = crossing;
      value.before_answer = before_answer; value.after_answer = nodes[root].visible.map.size() > 0;
      value.changed_keys = changed_keys; value.rows = emitted; value.live_rows = options.delta ? live_rows : 0;
      observer->route(value);
    };
    emitted = 0;
    bool before_answer = false;
    if (add) {
      if (id != no_entry) {
        const auto payload = n.records.map.payload(id)[0];
        if (base.dedupe) write(n.records, id, 0, payload + 1);
        report(low(payload), low(payload) + 1, false, has_answer_now(), 0);
        return false;
      }
      before_answer = has_answer_now();
      ++route;
      std::array<Key, 65> child_keys;
      std::uint32_t satisfied = 0;
      std::uint64_t bits = 0;
      for (std::uint32_t slot = 0; slot < n.children; ++slot) {
        child_keys[slot] = acquire(*n.edge_domain[slot], cells, in.child_keys[slot].data());
        if (nodes[n.child_nodes[slot]].support.map.find(child_keys[slot]) != no_entry) { bits |= 1ULL << slot; ++satisfied; }
      }
      id = insert(n.records, acquire(*n.record_domain, cells, in.map.data()), child_keys.data());
      write(n.records, id, 0, pack(1, satisfied));
      write(n.records, id, 1, bits);
      if (satisfied == n.children) survivor(in.node, id, true);
    } else {
      if (id == no_entry) return false;
      const auto payload = n.records.map.payload(id)[0];
      if (low(payload) > 1) {
        write(n.records, id, 0, payload - 1);
        report(low(payload), low(payload) - 1, false, has_answer_now(), 0);
        return false;
      }
      before_answer = has_answer_now();
      ++route;
      if (high(payload) == n.children) survivor(in.node, id, false);
      erase(n.records, id);
    }
    ++stats.route_changes;
    std::uint64_t changed_keys = 0;
    for (const auto v : by_rank) changed_keys += nodes[v].changed.size();
    if (options.delta) finish_route(add, sink);
    report(add ? 0 : 1, add ? 1 : 0, true, before_answer, changed_keys);
    return true;
  }
  [[nodiscard]] bool has_answer_now() const { return nodes[root].visible.map.size() > 0; }
  void finish_route(bool add, RowSink* sink) {
    const auto operation = add ? SetOperation::insert : SetOperation::erase;
    if (add) {
      for (const auto v : by_rank) {
        auto& n = nodes[v];
        for (const auto id : n.changed) {
          if (is_live(n.visible, id)) continue;
          bool live = v == root;
          if (!live) live = n.live.map.find(n.visible.map.secondary(id, 0)) != no_entry;
          if (live) make_live(v, id);
        }
      }
    }
    for (const auto v : by_rank) {
      auto& n = nodes[v];
      stats.changed_keys += n.changed.size();
      for (const auto id : n.changed)
        if (is_live(n.visible, id)) stats.delta_rows += enumerate(anchor[v], id, operation, sink);
    }
    if (!add) {
      for (const auto v : by_rank) {
        auto& n = nodes[v];
        for (const auto id : n.changed) {
          if (is_live(n.visible, id)) make_dead(v, id);
          erase(n.visible, id);
        }
      }
    }
    for (const auto v : by_rank) nodes[v].changed.clear();
  }

  // ------------------------------------------------------------------- bag
  // Weights. For a record t of node v with multiplicity m(t) (1 for a
  // generalized candidate) and cached child sums S_c:
  //   full(t)  = m(t) * prod_c S_c                (into v's parent sum)
  //   local(t) = m(t) * prod_{c not in C*} S_c    (into v's visible weight)
  // when every child sum is positive, else zero. A C* visible key e carries
  // W_v(e) = sum of local(t) over records projecting to e, and the count of a
  // head tuple a is the product of W_v(a[X_v]) over C*. A route changes one
  // record's multiplicity in one direction, so every weight moves
  // monotonically and each changed head tuple is enumerated once, by its
  // lowest-rank changed factor, with the before weights saved at first touch.
  struct Weights { std::uint64_t full = 0, local = 0; };
  Weights weights(std::uint32_t v, const std::uint64_t* payload) const {
    const auto& n = nodes[v];
    const std::uint64_t multiplicity = n.native ? payload[0] : 1;
    if (multiplicity == 0 || payload[1] != n.children) return {};
    Weights out{multiplicity, multiplicity};
    for (std::uint32_t slot = 0; slot < n.children; ++slot) {
      const annotations::Multiplicity sum{payload[2 + slot]};
      out.full = policy.multiply({out.full}, sum).value;
      if (outside_mask[v] >> slot & 1) out.local = policy.multiply({out.local}, sum).value;
    }
    return out;
  }
  std::uint64_t replaced(std::uint64_t total, std::uint64_t before, std::uint64_t after) const {
    return policy.replace({total}, {before}, {after}).value;
  }
  void bag_changed(std::uint32_t v, const ScalarView* cells, Weights before, Weights after) {
    auto& n = nodes[v];
    if (n.connex && before.local != after.local) bag_visible(v, cells, before.local, after.local);
    if (before.full == after.full) return;
    if (n.parent != none) bag_support(v, cells, before.full, after.full);
    else root_total = replaced(root_total, before.full, after.full);
  }
  void bag_visible(std::uint32_t v, const ScalarView* cells, std::uint64_t old_weight, std::uint64_t new_weight) {
    auto& n = nodes[v];
    auto& store = n.visible;
    const auto found = n.visible_domain->find(cells, n.visible_from_record.data());
    auto id = found ? store.map.find(*found) : no_entry;
    if (id == no_entry) {
      require(new_weight > old_weight, "visible weight underflow");
      std::array<Key, 65> secondary;
      std::size_t count = 0;
      if (n.down_domain && v != root) secondary[count++] = acquire(*n.down_domain, cells, n.down_from_record.data());
      for (std::size_t j = 0; j < n.cchildren.size(); ++j)
        secondary[count++] = acquire(*nodes[n.cchildren[j].node].down_domain, cells, n.cchild_from_record[j].data());
      id = insert(store, acquire(*n.visible_domain, cells, n.visible_from_record.data()), secondary.data());
    }
    const auto* payload = store.map.payload(id);
    if (options.delta && payload[2] != route) {
      write(store, id, 2, route);
      write(store, id, 3, payload[0]);
      n.changed.push_back(id);
    }
    const auto next = replaced(store.map.payload(id)[0], old_weight, new_weight);
    write(store, id, 0, next);
    if (next == 0 && !options.delta) erase(store, id);
  }
  void bag_support(std::uint32_t v, const ScalarView* cells, std::uint64_t old_weight, std::uint64_t new_weight) {
    auto& n = nodes[v];
    auto& store = n.support;
    const auto found = n.support_domain->find(cells, n.support_from_record.data());
    auto id = found ? store.map.find(*found) : no_entry;
    const std::uint64_t before = id == no_entry ? 0 : store.map.payload(id)[0];
    const auto after = replaced(before, old_weight, new_weight);
    if (id == no_entry) id = insert(store, acquire(*n.support_domain, cells, n.support_from_record.data()));
    const auto key = store.map.key(id);
    write(store, id, 0, after);
    if (after == 0) erase(store, id);
    bag_child(n.parent, n.slot, key, before, after);
  }
  void bag_child(std::uint32_t p, std::uint32_t slot, Key key, std::uint64_t before, std::uint64_t after) {
    auto& n = nodes[p];
    const int crossing = before == 0 ? 1 : after == 0 ? -1 : 0;
    auto update = [&](std::uint32_t id) {
      const auto old = weights(p, n.records.map.payload(id));
      write(n.records, id, 2 + slot, after);
      if (crossing) {
        const auto satisfied = n.records.map.payload(id)[1];
        write(n.records, id, 1, crossing > 0 ? satisfied + 1 : satisfied - 1);
      }
      const auto now = weights(p, n.records.map.payload(id));
      if (old.full == now.full && old.local == now.local) return;
      ScalarView scratch[2];
      bag_changed(p, record_cells(n, id, scratch).cells().data(), old, now);
    };
    if (n.native) {
      for (auto id = n.records.map.bucket(slot, key); id != no_entry;) {
        const auto next = n.records.map.next(slot, id);
        update(id);
        id = next;
      }
      return;
    }
    ScalarView scratch[2];
    const auto separator = n.edge_domain[slot]->view(key, scratch);
    ScalarView* const cells = generalized_cells.data();
    const auto& place = n.generalized_place[slot];
    for (std::size_t i = 0; i < place.size(); ++i) cells[place[i]] = separator[i];
    const auto found = n.record_domain->find(cells, identity(n.arity));
    auto id = found ? n.records.map.find(*found) : no_entry;
    if (id == no_entry) {
      require(before == 0 && after > 0, "generalized candidate missing");
      id = insert(n.records, acquire(*n.record_domain, cells, identity(n.arity)));
    }
    update(id);
    if (n.records.map.payload(id)[1] == 0) erase(n.records, id);
  }
  void stage_weight(std::uint32_t v, RowView record, std::uint64_t before, std::uint64_t after, WeightSink* sink) {
    require(open, "stage outside a keyed transaction");
    require(options.bag, "weights are staged in bag mode only");
    require(v < nodes.size() && nodes[v].native, "weights are staged on native nodes only");
    auto& n = nodes[v];
    require(record.size() == n.arity, "record width differs from its node scope");
    if (before == after) return;
    const auto* cells = record.cells().data();
    const auto found = n.record_domain->find(cells, identity(n.arity));
    auto id = found ? n.records.map.find(*found) : no_entry;
    const std::uint64_t current = id == no_entry ? 0 : n.records.map.payload(id)[0];
    const auto next = replaced(current, before, after);
    ++stats.events;
    ++route;
    if (id == no_entry) {
      std::array<Key, 65> child_keys;
      for (std::uint32_t slot = 0; slot < n.children; ++slot)
        child_keys[slot] = acquire(*n.edge_domain[slot], cells, n.child_from_record[slot].data());
      id = insert(n.records, acquire(*n.record_domain, cells, identity(n.arity)), child_keys.data());
      std::uint64_t satisfied = 0;
      for (std::uint32_t slot = 0; slot < n.children; ++slot) {
        const auto& support = nodes[n.child_nodes[slot]].support.map;
        const auto child = support.find(child_keys[slot]);
        const auto sum = child == no_entry ? 0 : support.payload(child)[0];
        if (sum) { write(n.records, id, 2 + slot, sum); ++satisfied; }
      }
      if (satisfied) write(n.records, id, 1, satisfied);
    }
    const auto old = weights(v, n.records.map.payload(id));
    write(n.records, id, 0, next);
    const auto now = weights(v, n.records.map.payload(id));
    bag_changed(v, cells, old, now);
    if (next == 0) erase(n.records, id);
    ++stats.route_changes;
    if (options.delta) finish_bag(next > current, sink);
  }
  void finish_bag(bool add, WeightSink* sink) {
    if (add) {
      for (const auto v : by_rank) {
        auto& n = nodes[v];
        for (const auto id : n.changed) {
          const auto* payload = n.visible.map.payload(id);
          if (is_live(n.visible, id) || payload[3] != 0) continue;  // only newly visible keys
          bool live = v == root;
          if (!live) live = n.live.map.find(n.visible.map.secondary(id, 0)) != no_entry;
          if (live) make_live(v, id);
        }
      }
    }
    for (const auto v : by_rank) {
      auto& n = nodes[v];
      stats.changed_keys += n.changed.size();
      for (const auto id : n.changed)
        if (is_live(n.visible, id)) enumerate_bag(anchor[v], id, true, sink);
    }
    if (!add) {
      for (const auto v : by_rank) {
        auto& n = nodes[v];
        for (const auto id : n.changed) {
          if (n.visible.map.payload(id)[0] != 0) continue;
          if (is_live(n.visible, id)) make_dead(v, id);
          erase(n.visible, id);
        }
      }
    }
    for (const auto v : by_rank) nodes[v].changed.clear();
  }
  // Every completion of the plan from `first`; emits count changes (or, for a
  // snapshot, every positive count).
  void enumerate_bag(const Plan& plan, std::uint32_t first, bool changes, WeightSink* sink) const {
    const auto count = plan.steps.size();
    const KeyMap* maps[max_nodes];
    const KeyDomain* domains_of[max_nodes];
    for (std::size_t s = 0; s < count; ++s) {
      maps[s] = &nodes[plan.steps[s].node].visible.map;
      domains_of[s] = nodes[plan.steps[s].node].visible_domain;
    }
    std::uint32_t current[max_nodes];
    ScalarView* const out = out_cells.data();
    ScalarView* const scratch = out_scratch.data();
    const auto width = plan.output.size();
    const auto stamp = route;
    auto valid = [&](std::size_t s, std::uint32_t id) {
      const auto& step = plan.steps[s];
      const auto* payload = maps[s]->payload(id);
      if (step.live && !(payload[1] & 1)) return false;
      if (step.prune && payload[2] == stamp) return false;
      return true;
    };
    auto advance = [&](std::size_t s, std::uint32_t id) {
      const auto index = plan.steps[s].index;
      while (id != no_entry && !valid(s, id)) id = maps[s]->next(index, id);
      return id;
    };
    auto open_step = [&](std::size_t s) {
      const auto& step = plan.steps[s];
      const auto key = maps[step.from]->secondary(current[step.from], step.source_secondary);
      return advance(s, maps[s]->bucket(step.index, key));
    };
    auto emit = [&] {
      std::uint64_t after = 1, before = 1;
      for (std::size_t s = 0; s < count; ++s) {
        const auto* payload = maps[s]->payload(current[s]);
        after = policy.multiply({after}, {payload[0]}).value;
        if (changes) before = policy.multiply({before}, {payload[2] == stamp ? payload[3] : payload[0]}).value;
      }
      if (!changes) before = 0;
      if (before == after) return;
      for (std::size_t i = 0; i < width; ++i) {
        const auto [s, field] = plan.output[i];
        out[i] = s == none ? output_constants[field] : domains_of[s]->cell(maps[s]->key(current[s]), field, scratch[i]);
      }
      if (sink) sink->change(RowView::borrow({out, width}), before, after);
      ++emitted;
    };
    current[0] = first;
    if (count == 1) { emit(); return; }
    std::size_t s = 1;
    current[1] = open_step(1);
    for (;;) {
      if (current[s] == no_entry) {
        if (--s == 0) break;
        current[s] = advance(s, maps[s]->next(plan.steps[s].index, current[s]));
        continue;
      }
      if (s + 1 == count) {
        emit();
        current[s] = advance(s, maps[s]->next(plan.steps[s].index, current[s]));
        continue;
      }
      ++s;
      current[s] = open_step(s);
    }
  }
  void snapshot_bag(WeightSink& sink) const {
    const auto& visible = nodes[root].visible.map;
    for (std::uint32_t id = 0; id < visible.ids(); ++id)
      if (visible.live(id)) enumerate_bag(snapshot_plan, id, false, &sink);
  }

  void snapshot(RowSink& sink) {
    const auto& visible = nodes[root].visible.map;
    for (std::uint32_t id = 0; id < visible.ids(); ++id)
      if (visible.live(id)) stats.snapshot_rows += enumerate(snapshot_plan, id, SetOperation::insert, &sink);
  }
  void check_invariants() const {
    for (const auto& [identity, domain] : domains) domain->check_invariants();
    if (open) return;
    // Exact ownership: every interned key has one reference per stored entry
    // that holds it (primary or secondary), and nothing else.
    std::map<std::pair<const KeyDomain*, std::uint64_t>, std::uint32_t> owned;
    auto count = [&](const Store& store) {
      if (!store.primary) return;
      for (std::uint32_t id = 0; id < store.map.ids(); ++id) {
        if (!store.map.live(id)) continue;
        if (!store.primary->inline_form()) ++owned[{store.primary, store.map.key(id).word}];
        for (std::size_t s = 0; s < store.secondary.size(); ++s)
          if (!store.secondary[s]->inline_form()) ++owned[{store.secondary[s], store.map.secondary(id, s).word}];
      }
    };
    for (const auto& n : nodes) { count(n.records); count(n.support); count(n.visible); count(n.live); }
    for (const auto& base : bases) count(base.rows);
    std::size_t interned = 0;
    auto verify = [&](const KeyDomain* domain) {
      domain->for_each([&](Key key, std::uint32_t references) {
        ++interned;
        const auto found = owned.find({domain, key.word});
        require(found != owned.end() && found->second == references, "interned key reference count differs from its owners");
      });
    };
    for (const auto& [identity, domain] : domains) verify(domain.get());
    for (const auto& domain : private_domains) verify(domain.get());
    require(interned == owned.size(), "an owned key is not interned");
    for (const auto& n : nodes) {
      n.records.map.check_invariants();
      if (n.parent != none) n.support.map.check_invariants();
      if (n.connex) n.visible.map.check_invariants();
      if (n.connex && n.cparent != none) n.live.map.check_invariants();
    }
  }
};

SetEngine::Cursor::Cursor(const SetEngine& owner, bool alternate)
    : owner_(&owner), alternate_(alternate), pin_(owner.impl_->collector.pin()) {
  ++owner.impl_->readers;
}
SetEngine::Cursor::~Cursor() { --owner_->impl_->readers; }
std::optional<storage::RowView> SetEngine::Cursor::next() {
  if (done_) return std::nullopt;
  const auto& d = *owner_->impl_;
  const auto& plan = d.snapshot_plan;
  const auto count = plan.steps.size();
  const auto& root = d.nodes[d.root].visible.map;
  auto map = [&](std::size_t s) -> const KeyMap& { return *maps_[s]; };
  auto open_step = [&](std::size_t s) {
    const auto& step = plan.steps[s];
    return map(s).bucket(step.index, map(step.from).secondary(current_[step.from], step.source_secondary));
  };
  auto next_root = [&](std::uint32_t from) {
    while (from < root.ids() && !root.live(from)) ++from;
    return from;
  };
  // Generator: advance at depth_ (after the first call), then descend to a
  // complete assignment, backtracking whenever a bucket is empty.
  bool advance = started_;
  if (!started_) {
    started_ = true;
    for (std::size_t s = 0; s < count; ++s) {
      const auto& node = d.nodes[plan.steps[s].node];
      maps_[s] = &node.visible.map;
      domains_[s] = node.visible_domain;
    }
    root_ = next_root(0);
    if (root_ >= root.ids()) { done_ = true; return std::nullopt; }
    current_[0] = root_;
    depth_ = 0;
  }
  for (;;) {
    if (advance) {
      if (depth_ == 0) {
        root_ = next_root(root_ + 1);
        if (root_ >= root.ids()) { done_ = true; return std::nullopt; }
        current_[0] = root_;
      } else {
        current_[depth_] = map(depth_).next(plan.steps[depth_].index, current_[depth_]);
        if (current_[depth_] == no_entry) { --depth_; continue; }
      }
      advance = false;
    }
    while (depth_ + 1 < count) {
      ++depth_;
      current_[depth_] = open_step(depth_);
      if (current_[depth_] == no_entry) { --depth_; advance = true; break; }
    }
    if (!advance) break;
  }
  const auto& program = alternate_ ? plan.other : plan.output;
  const auto& constants = alternate_ ? d.other_constants : d.output_constants;
  const auto width = program.size();
  for (std::size_t i = 0; i < width; ++i) {
    const auto [s, field] = program[i];
    out_[i] = s == none ? constants[field] : domains_[s]->cell(map(s).key(current_[s]), field, scratch_[i]);
  }
  if (d.options.bag) {
    weight_ = 1;
    for (std::size_t s = 0; s < count; ++s)
      weight_ = d.policy.multiply({weight_}, {map(s).payload(current_[s])[0]}).value;
  }
  ++rows_;
  // The caller works on this row (a tuple per row) while the innermost
  // bucket's next member is fetched.
  if (count > 1) map(count - 1).prefetch(map(count - 1).next(plan.steps[count - 1].index, current_[count - 1]));
  return RowView::borrow({out_.data(), width});
}
std::unique_ptr<SetEngine::Cursor> SetEngine::open_cursor() const {
  require(!impl_->open, "result cursors cannot open inside a transaction");
  return std::unique_ptr<Cursor>(new Cursor(*this, false));
}
std::unique_ptr<SetEngine::Cursor> SetEngine::open_cursor(bool sql_view) const {
  require(!impl_->open, "result cursors cannot open inside a transaction");
  return std::unique_ptr<Cursor>(new Cursor(*this, sql_view != impl_->options.sql_view));
}
std::size_t SetEngine::readers() const noexcept { return impl_->readers; }

std::string SetEngine::unsupported(const CompiledProgram& program) { return check(program); }
SetEngine::SetEngine(const CompiledProgram& program, EngineOptions options)
    : impl_(std::make_unique<Impl>(program, options)) {}
SetEngine::~SetEngine() = default;
void SetEngine::begin() { impl_->begin(); }
bool SetEngine::stage(TableId table, SetOperation operation, storage::RowView row, RowSink* sink,
    RouteObserver* observer) {
  return impl_->stage(table, operation, row, sink, observer);
}
bool SetEngine::stage_source(TableId table, SetOperation operation, storage::RowView row) {
  return impl_->stage_source(table, operation, row);
}
std::size_t SetEngine::routes(TableId table) const { return impl_->bases.at(table.value).routes.size(); }
void SetEngine::stage_route(TableId table, std::size_t index, SetOperation operation, storage::RowView row,
    RowSink* sink, RouteObserver* observer) {
  impl_->stage_route_at(table, index, operation, row, sink, observer);
}
void SetEngine::commit() { impl_->commit(); }
void SetEngine::rollback() noexcept { impl_->rollback(); }
bool SetEngine::active() const noexcept { return impl_->open; }
bool SetEngine::apply(TableId table, SetOperation operation, storage::RowView row, RowSink* sink) {
  impl_->begin();
  try {
    const bool changed = impl_->stage(table, operation, row, sink);
    impl_->commit();
    return changed;
  } catch (...) {
    impl_->rollback();
    throw;
  }
}
void SetEngine::snapshot(RowSink& sink) const { impl_->snapshot(sink); }
void SetEngine::snapshot(WeightSink& sink) const {
  require(impl_->options.bag, "weighted snapshots are a bag-mode view");
  impl_->snapshot_bag(sink);
}
void SetEngine::stage_weight(std::uint32_t node, storage::RowView record, std::uint64_t before, std::uint64_t after,
    WeightSink* sink) {
  impl_->stage_weight(node, record, before, after, sink);
}
std::uint64_t SetEngine::weight(std::uint32_t node, storage::RowView record) const {
  const auto& d = *impl_;
  require(node < d.nodes.size() && d.nodes[node].native, "weights exist on native nodes only");
  const auto& n = d.nodes[node];
  require(record.size() == n.arity, "record width differs from its node scope");
  const auto key = n.record_domain->find(record.cells().data(), Impl::identity(n.arity));
  const auto id = key ? n.records.map.find(*key) : no_entry;
  return id == no_entry ? 0 : (d.options.bag ? n.records.map.payload(id)[0] : low(n.records.map.payload(id)[0]));
}
std::uint64_t SetEngine::root_weight() const noexcept { return impl_->root_total; }
void SetEngine::for_each_record(const std::function<void(std::uint32_t, storage::RowView, std::uint64_t)>& visit) const {
  const auto& d = *impl_;
  ScalarView scratch[2];
  for (std::uint32_t v = 0; v < d.nodes.size(); ++v) {
    const auto& n = d.nodes[v];
    if (!n.native) continue;
    for (std::uint32_t id = 0; id < n.records.map.ids(); ++id)
      if (n.records.map.live(id))
        visit(v, d.record_cells(n, id, scratch), d.options.bag ? n.records.map.payload(id)[0] : low(n.records.map.payload(id)[0]));
  }
}
bool SetEngine::has_answer() const { return impl_->nodes[impl_->root].visible.map.size() > 0; }
Database SetEngine::sources() const {
  Database out;
  out.tables.resize(impl_->bases.size());
  std::array<ScalarView, 2> scratch;
  std::vector<Value> row;
  for (std::size_t t = 0; t < impl_->bases.size(); ++t) {
    const auto& base = impl_->bases[t];
    if (base.elided) {  // the single route's records are the rows
      const auto& n = impl_->nodes[impl_->inputs[base.routes[0]].node];
      for (std::uint32_t id = 0; id < n.records.map.ids(); ++id) {
        if (!n.records.map.live(id)) continue;
        const auto record = n.record_domain->view(n.records.map.key(id), scratch.data());
        row.assign(base.width, Value{});
        for (std::size_t f = 0; f < base.column_of_field.size(); ++f) row[base.column_of_field[f]] = storage::export_scalar(record[f]);
        out.tables[t].insert(row);
      }
      continue;
    }
    for (std::uint32_t id = 0; id < base.rows.map.ids(); ++id)
      if (base.rows.map.live(id)) out.tables[t].insert(storage::export_row(base.domain->view(base.rows.map.key(id), scratch.data())));
  }
  return out;
}
bool SetEngine::contains(TableId table, storage::RowView row) const {
  const auto& d = *impl_;
  const auto& base = d.bases.at(table.value);
  require(row.size() == base.width, "row width differs from its source table");
  if (base.elided) {
    const auto& in = d.inputs[base.routes[0]];
    const auto& n = d.nodes[in.node];
    const auto found = n.record_domain->find(row.cells().data(), in.map.data());
    return found && n.records.map.find(*found) != no_entry;
  }
  const auto found = base.domain->find(row.cells());
  return found && base.rows.map.find(*found) != no_entry;
}
std::uint64_t SetEngine::rows(TableId table) const {
  const auto& d = *impl_;
  const auto& base = d.bases.at(table.value);
  if (base.elided) return d.nodes[d.inputs[base.routes[0]].node].records.map.size();
  return base.rows.map.size();
}
bool SetEngine::delta() const noexcept { return impl_->options.delta; }
void SetEngine::set_delta(bool delta) {
  require(!impl_->open, "mode change inside a transaction");
  if (delta == impl_->options.delta) return;
  impl_->open = true;
  try {
    if (delta) { impl_->options.delta = true; impl_->bootstrap_live(); }
    else {
      // Leaving delta mode: drop live flags and separator counts.
      for (const auto v : impl_->by_rank) {
        auto& n = impl_->nodes[v];
        for (std::uint32_t id = 0; id < n.visible.map.ids(); ++id)
          if (n.visible.map.live(id) && impl_->is_live(n.visible, id))
            impl_->write(n.visible, id, impl_->live_word, n.visible.map.payload(id)[impl_->live_word] & ~impl_->live_mask);
        if (v != impl_->root)
          for (std::uint32_t id = 0; id < n.live.map.ids(); ++id) if (n.live.map.live(id)) impl_->erase(n.live, id);
      }
      impl_->options.delta = false;
    }
    impl_->commit();
  } catch (...) {
    impl_->options.delta = !delta;
    impl_->rollback();
    throw;
  }
}
std::span<const ScalarType> SetEngine::result_types() const noexcept { return impl_->output_types; }
storage::keyed::Collector& SetEngine::collector() noexcept { return impl_->collector; }
void SetEngine::collect() {
  require(!impl_->open, "collection inside a transaction");
  impl_->collector.collect();
  for (auto& n : impl_->nodes) {
    n.records.map.shrink();
    if (n.parent != none) n.support.map.shrink();
    if (n.connex) n.visible.map.shrink();
    if (n.connex && n.cparent != none) n.live.map.shrink();
  }
}
EngineStatistics SetEngine::statistics() const {
  auto out = impl_->stats;
  for (const auto& n : impl_->nodes) {
    out.index_bytes += n.records.map.memory_bytes() + n.support.map.memory_bytes() + n.visible.map.memory_bytes() + n.live.map.memory_bytes();
  }
  for (const auto& [identity, domain] : impl_->domains) out.interned_keys += domain->interned();
  out.memory_bytes = impl_->budget.used();
  out.peak_memory_bytes = impl_->budget.peak();
  return out;
}
void SetEngine::check_invariants() const { impl_->check_invariants(); }

}  // namespace crown::runtime::keyed
