#include "crown/frontend/sql_rows.hpp"
#include "sql_rows_value.hpp"
#include "sql_scalar.hpp"
#include "crown/api/error.hpp"
#include "crown/ir/digest.hpp"
#include "crown/io/catalog.hpp"
#include "crown/resource/ownership.hpp"
#include "crown/resource/text.hpp"
#include <algorithm>
#include <array>
#include <map>
#include <numeric>
#include <set>

namespace crown::frontend {
namespace {
template<class T> using Items = std::vector<T, resource::MemoryAllocator<T>>;
template<class T> auto allocator(const resource::MemoryAccount& account) {
  return resource::MemoryAllocator<T>(account, resource::MemoryPurpose::immutable_metadata,
      {resource::MemoryOwnerKind::immutable_metadata, 0});
}
[[noreturn]] void fail(std::string code, std::string message) { throw Error(std::move(code), std::move(message)); }
constexpr auto no_owner = SIZE_MAX;
constexpr auto several_owners = SIZE_MAX - 1;
std::size_t merge_owner(std::size_t left, std::size_t right) {
  if (left == no_owner) return right;
  if (right == no_owner || left == right) return left;
  return several_owners;
}
template<class T> std::span<const T> append(Items<T>& target, const std::vector<T>& values) {
  if (values.empty()) return {};
  const auto begin = target.size(); target.insert(target.end(), values.begin(), values.end());
  return {target.data() + begin, values.size()};
}
template<class T> std::span<const T> rebase(std::span<const T> old,
    const Items<T>& source, const Items<T>& target) {
  if (old.empty()) return {};
  return {target.data() + (old.data() - source.data()), old.size()};
}
}  // namespace

// Flat backing arrays are reserved before borrowed spans are published. Text
// owns native character blocks, so moving its descriptor never moves bytes.
struct SqlRowsProgram::Data {
  resource::MemoryAccount account;
  resource::AccountedText source,binding;
  std::array<char, 64> key{};
  std::uint64_t catalog_version = 1, work = 0;
  SqlSemantics semantics = SqlSemantics::bag;
  SqlWrapper wrapper = SqlWrapper::rows;
  bool contradiction = false;
  Items<resource::AccountedText> names;
  Items<SqlRowsSource> sources;
  Items<SqlRowsColumn> columns;
  Items<SqlRowsConstraint> constraints;
  Items<ColumnId> constraint_columns;
  Items<std::size_t> source_constraints, references;
  Items<OccurrenceId> routes;
  Items<SqlRowsOccurrence> occurrences;
  Items<SqlRowsInput> inputs;
  Items<SqlRowsOperation> operations;
  Items<ExpressionId> arguments, predicates;
  Items<ColumnId> non_nulls;
  Items<SqlRowsEquality> equalities;
  Items<SqlRowsConstant> fixed;
  Items<SqlRowsProjection> projections;
  Items<ScalarType> variables;
  Items<VariableId> head;
  Items<SqlRowsOutput> outputs;
  storage::AccountedRow literal_backing;
  Items<SqlRowCell> initial;
  explicit Data(const resource::MemoryAccount& owner)
      : account(owner), names(allocator<resource::AccountedText>(owner)), sources(allocator<SqlRowsSource>(owner)),
        columns(allocator<SqlRowsColumn>(owner)), constraints(allocator<SqlRowsConstraint>(owner)),
        constraint_columns(allocator<ColumnId>(owner)), source_constraints(allocator<std::size_t>(owner)),
        references(allocator<std::size_t>(owner)), routes(allocator<OccurrenceId>(owner)),
        occurrences(allocator<SqlRowsOccurrence>(owner)), inputs(allocator<SqlRowsInput>(owner)),
        operations(allocator<SqlRowsOperation>(owner)), arguments(allocator<ExpressionId>(owner)),
        predicates(allocator<ExpressionId>(owner)), non_nulls(allocator<ColumnId>(owner)),
        equalities(allocator<SqlRowsEquality>(owner)), fixed(allocator<SqlRowsConstant>(owner)),
        projections(allocator<SqlRowsProjection>(owner)), variables(allocator<ScalarType>(owner)),
        head(allocator<VariableId>(owner)), outputs(allocator<SqlRowsOutput>(owner)), initial(allocator<SqlRowCell>(owner)) {}
  std::string_view name(std::string_view text) {
    if (!rows_detail::text_fits(text)) fail("unsupported_sql_text", "SQL identifiers must be UTF8 without NUL");
    names.push_back(resource::AccountedText::copy_of(account, text,
        {resource::MemoryOwnerKind::immutable_metadata, 0}, resource::MemoryPurpose::immutable_metadata));
    return names.back().view();
  }
  void freeze_values(std::span<const SqlRowCell> values) {
    // One actual row owns every present constant, including string bytes.
    // NULL/nonconstant placeholders stay empty; instructions distinguish them.
    std::vector<storage::ScalarView> present;
    for (const auto& value : values) if (value) present.push_back(*value);
    if (!present.empty()) literal_backing = storage::AccountedRow::copy_of(account,
        storage::RowView::borrow(present), {resource::MemoryOwnerKind::immutable_metadata, 0});
    initial.reserve(values.size()); std::size_t next = 0;
    for (const auto& value : values)
      initial.push_back(value ? SqlRowCell{literal_backing.view()[next++]} : SqlRowCell{});
  }
};

namespace detail {
class SqlRowsCompiler {
  struct DraftOccurrence {
    std::vector<SqlRowsInput> inputs;
    std::vector<ExpressionId> operations, predicates;
    std::vector<ColumnId> non_nulls;
    std::vector<SqlRowsEquality> equalities;
    std::vector<SqlRowsConstant> fixed;
    std::vector<SqlRowsProjection> projections;
  };
  struct Pair { VariableId payload; std::optional<VariableId> presence; };
  const BoundSql& bound_;
  const SqlRowsBindOptions& options_;
  std::shared_ptr<SqlRowsProgram::Data> result_;
  std::vector<std::size_t> offsets_, parent_, rank_, owner_;
  std::vector<std::optional<std::size_t>> column_;
  std::vector<std::optional<ExpressionId>> physical_expression_, fixed_;
  std::vector<SqlRowCell> values_;
  std::vector<bool> known_, non_null_, join_live_;
  std::vector<DraftOccurrence> occurrences_;
  std::vector<ExpressionId> residual_;
  std::optional<ExpressionId> null_slot_;
  std::map<std::size_t, Pair> class_variables_;
  std::map<ExpressionId, Pair> computed_variables_;
  std::map<VariableId, std::size_t> head_positions_;
  std::uint64_t work_ = 0;

  void charge(std::uint64_t amount = 1) {
    if (amount > UINT64_MAX - work_ || (options_.work_limit &&
        amount > *options_.work_limit - work_)) fail("resource_limit", "SQL row normalization work limit exceeded");
    work_ += amount;
  }
  std::size_t root(std::size_t value) {
    charge(); auto top = value;
    while (parent_[top] != top) { charge(); top = parent_[top]; }
    while (value != top) { const auto next = parent_[value]; parent_[value] = top; value = next; }
    return top;
  }
  void unite(std::size_t left, std::size_t right) {
    left = root(left); right = root(right);
    if (left == right) return;
    if (rank_[left] < rank_[right]) std::swap(left, right);
    parent_[right] = left; if (rank_[left] == rank_[right]) ++rank_[left];
  }
  const BoundExpression& expression(ExpressionId id) const { return bound_.expressions.at(id.value); }
  std::size_t effective_arguments(const BoundOperation& node) const {
    return node.operation == SqlOperator::using_value ? 1 : node.arguments.size();
  }
  void analyze() {
    const auto count = bound_.expressions.size();
    owner_.resize(count, no_owner); column_.resize(count); known_.resize(count); values_.resize(count);
    for (std::size_t i = 0; i < count; ++i) {
      charge(); const auto& item = bound_.expressions[i];
      if (const auto* column = std::get_if<BoundColumn>(&item.node)) {
        const auto physical = offsets_[column->occurrence.value] + column->column.value;
        owner_[i] = column->occurrence.value; column_[i] = physical;
        if (!physical_expression_[physical]) physical_expression_[physical] = ExpressionId{i};
      } else if (const auto* literal = std::get_if<BoundLiteral>(&item.node)) {
        known_[i] = true;
        if (literal->value) values_[i] = storage::borrow_scalar(*literal->value);
      } else if (const auto* parameter = std::get_if<BoundParameter>(&item.node)) {
        known_[i] = true; const auto& value = options_.parameters[parameter->number - 1];
        if (value) values_[i] = storage::borrow_scalar(*value);
      } else {
        const auto& node = std::get<BoundOperation>(item.node);
        bool constant = true;
        for (std::size_t a = 0; a < effective_arguments(node); ++a) {
          charge(); const auto child = node.arguments[a].value;
          if (child >= i) fail("rows_contract", "bound expressions are not topological");
          owner_[i] = merge_owner(owner_[i], owner_[child]); constant = constant && known_[child];
        }
        if (node.operation == SqlOperator::identity_cast || node.operation == SqlOperator::literal_cast ||
            node.operation == SqlOperator::widen_integer || node.operation == SqlOperator::using_value)
          column_[i] = column_[node.arguments[0].value];
        if (constant) { known_[i] = true; values_[i] = sql_detail::evaluate(node.operation, node.arguments, values_); }
      }
    }
  }
  void predicates() {
    std::vector<std::pair<std::size_t, ExpressionId>> constants;
    std::vector<ExpressionId> pending(bound_.predicates.rbegin(), bound_.predicates.rend());
    while (!pending.empty()) {
      charge(); const auto id = pending.back(); pending.pop_back();
      const auto* operation = std::get_if<BoundOperation>(&expression(id).node);
      if (operation && operation->operation == SqlOperator::conjunction) {
        for (auto i = operation->arguments.rbegin(); i != operation->arguments.rend(); ++i) pending.push_back(*i);
        continue;
      }
      if (operation && operation->operation == SqlOperator::equal) {
        const auto left = column_[operation->arguments[0].value], right = column_[operation->arguments[1].value];
        if (left && right) {
          unite(*left, *right); non_null_[*left] = true; non_null_[*right] = true;
          // Local equality is already a guard. Only cross-occurrence classes
          // need a hidden native join field when no output selects the class.
          if (owner_[operation->arguments[0].value] != owner_[operation->arguments[1].value])
            join_live_[*left] = join_live_[*right] = true;
          continue;
        }
        if (left || right) {
          const auto constant = operation->arguments[left ? 1 : 0];
          if (known_[constant.value]) {
            if (!values_[constant.value]) result_->contradiction = true;
            else { constants.emplace_back(left ? *left : *right, constant); non_null_[left ? *left : *right] = true; }
            continue;
          }
        }
      }
      if (operation && (operation->operation == SqlOperator::is_null || operation->operation == SqlOperator::is_not_null)) {
        const auto direct = column_[operation->arguments[0].value];
        if (direct) {
          if (operation->operation == SqlOperator::is_not_null) non_null_[*direct] = true;
          else {
            // A dedicated constant avoids overwriting the Boolean IS NULL
            // expression when the second folding pass recomputes its result.
            if (!null_slot_) {
              null_slot_ = ExpressionId{values_.size()}; values_.push_back({}); known_.push_back(true);
              owner_.push_back(no_owner); column_.push_back({});
            }
            constants.emplace_back(*direct, *null_slot_);
          }
          continue;
        }
      }
      residual_.push_back(id);
    }
    for (std::size_t i = 0; i < parent_.size(); ++i) {
      const auto representative = root(i);
      if (non_null_[i]) non_null_[representative] = true;
      if (join_live_[i]) join_live_[representative] = true;
    }
    for (const auto& [physical, id] : constants) {
      const auto representative = root(physical);
      if (fixed_[representative] && values_[fixed_[representative]->value] != values_[id.value]) result_->contradiction = true;
      else fixed_[representative] = id;
    }
    for (std::size_t i = 0; i < parent_.size(); ++i)
      if (fixed_[i] && !values_[fixed_[i]->value] && non_null_[i]) result_->contradiction = true;
  }
  void fold_grounded() {
    for (std::size_t i = 0; i < bound_.expressions.size(); ++i) {
      charge();
      if (column_[i]) {
        const auto fixed = fixed_[root(*column_[i])];
        if (fixed) { known_[i] = true; values_[i] = values_[fixed->value]; owner_[i] = no_owner; }
      } else if (const auto* node = std::get_if<BoundOperation>(&bound_.expressions[i].node)) {
        bool constant = true; auto owner = no_owner;
        for (std::size_t a = 0; a < effective_arguments(*node); ++a) {
          charge(); const auto child = node->arguments[a].value;
          constant = constant && known_[child]; owner = merge_owner(owner, owner_[child]);
        }
        owner_[i] = owner;
        if (constant) { known_[i] = true; values_[i] = sql_detail::evaluate(node->operation, node->arguments, values_); }
      }
    }
    for (const auto id : residual_) {
      if (known_[id.value]) {
        if (sql_detail::truth(values_[id.value]) != std::optional<bool>{true}) result_->contradiction = true;
      } else if (owner_[id.value] == several_owners)
        fail("unsupported_cross_relation_predicate", "only unconditional column equalities may span occurrences");
      else occurrences_[owner_[id.value]].predicates.push_back(id);
    }
  }
  Pair new_pair(SqlType type, bool nullable) {
    const VariableId payload{result_->variables.size()}; result_->variables.push_back(rows_detail::scalar(type.kind));
    Pair result{payload, {}};
    if (nullable) { result.presence = VariableId{result_->variables.size()}; result_->variables.push_back(ScalarType::boolean); }
    return result;
  }
  std::size_t head(VariableId variable) {
    const auto found = head_positions_.find(variable);
    if (found != head_positions_.end()) return found->second;
    const auto position = result_->head.size(); result_->head.push_back(variable); head_positions_.emplace(variable, position); return position;
  }
  void project(DraftOccurrence& occurrence, Pair pair, ExpressionId expression, SqlType type) {
    occurrence.projections.push_back({pair.payload, expression, rows_detail::scalar(type.kind),
        pair.presence ? SqlRowsFieldKind::nullable_payload : SqlRowsFieldKind::value});
    if (pair.presence) occurrence.projections.push_back({*pair.presence, expression, ScalarType::boolean, SqlRowsFieldKind::presence});
  }
  void core() {
    // First keep structural join classes. Output-only nullable classes add a
    // private presence field with identical incidence, not a NULL join sentinel.
    for (std::size_t i = 0; i < parent_.size(); ++i) {
      const auto representative = root(i);
      if (join_live_[representative] && !fixed_[representative] && !class_variables_.contains(representative)) {
        const auto id = *physical_expression_[i];
        class_variables_.emplace(representative, new_pair(expression(id).type, false));
      }
    }
    if (bound_.wrapper == SqlWrapper::rows) for (const auto& output : bound_.outputs) {
      charge(); const auto id = output.expression; const auto& item = expression(id);
      const auto name = result_->name(output.name);
      if (known_[id.value]) {
        // Grounded columns already share one checked fixed slot. Reuse it
        // instead of retaining another copy of a possibly large string.
        const auto constant = column_[id.value] ? fixed_[root(*column_[id.value])].value_or(id) : id;
        result_->outputs.push_back({name, item.type, constant}); continue;
      }
      Pair pair{};
      if (column_[id.value]) {
        const auto representative = root(*column_[id.value]);
        auto found = class_variables_.find(representative);
        if (found == class_variables_.end()) found = class_variables_.emplace(representative,
            new_pair(item.type, !non_null_[representative])).first;
        pair = found->second;
      } else {
        if (owner_[id.value] == several_owners)
          fail("unsupported_cross_relation_output", "a computed row output must depend on one occurrence");
        auto found = computed_variables_.find(id);
        if (found == computed_variables_.end()) {
          found = computed_variables_.emplace(id, new_pair(item.type, item.type.nullable)).first;
          project(occurrences_[owner_[id.value]], found->second, id, item.type);
        }
        pair = found->second;
      }
      const auto payload = head(pair.payload);
      const auto presence = pair.presence ? std::optional<std::size_t>{head(*pair.presence)} : std::nullopt;
      result_->outputs.push_back({name, item.type, SqlRowsResultField{payload, presence}});
    }
    if (bound_.wrapper == SqlWrapper::exists)
      result_->outputs.push_back({result_->name(bound_.wrapper_alias), {SqlKind::boolean, false, {}}, SqlRowsExistsOutput{}});
    for (std::size_t o = 0; o < occurrences_.size(); ++o) {
      auto& draft = occurrences_[o]; std::map<std::size_t, ColumnId> first;
      const auto& columns = bound_.catalog.tables[bound_.occurrences[o].table.value].columns;
      for (std::size_t c = 0; c < columns.size(); ++c) {
        charge(); const auto representative = root(offsets_[o] + c); const ColumnId column{c};
        if (fixed_[representative]) { draft.fixed.push_back({column, *fixed_[representative]}); continue; }
        if (non_null_[representative] && columns[c].nullable) draft.non_nulls.push_back(column);
        const auto previous = first.find(representative);
        if (previous != first.end()) draft.equalities.push_back({previous->second, column});
        else first.emplace(representative, column);
        const auto variable = class_variables_.find(representative);
        if (variable != class_variables_.end() && previous == first.end())
          project(draft, variable->second, *physical_expression_[offsets_[o] + c], rows_detail::sql_type(columns[c]));
      }
      std::sort(draft.projections.begin(), draft.projections.end(), [](const auto& a, const auto& b) { return a.variable < b.variable; });
      std::set<ExpressionId> needed; std::vector<ExpressionId> pending = draft.predicates;
      for (const auto& field : draft.projections) pending.push_back(field.expression);
      while (!pending.empty()) {
        charge(); const auto id = pending.back(); pending.pop_back();
        if (known_[id.value] || !needed.insert(id).second) continue;
        if (owner_[id.value] != o) fail("rows_contract", "nonlocal expression in a local row program");
        if (const auto* node = std::get_if<BoundOperation>(&expression(id).node))
          for (std::size_t a = 0; a < effective_arguments(*node); ++a) pending.push_back(node->arguments[a]);
      }
      for (const auto id : needed) {
        if (const auto* column = std::get_if<BoundColumn>(&expression(id).node)) draft.inputs.push_back({id, column->column});
        else draft.operations.push_back(id);
      }
    }
  }
  void schemas() {
    auto& d = *result_; const auto tables = bound_.catalog.tables.size();
    std::size_t columns = 0, constraints = 0, key_columns = 0;
    for (const auto& table : bound_.catalog.tables) {
      columns += table.columns.size();
      for (const auto& constraint : table.constraints) std::visit([&](const auto& c) {
        if (c.status == ConstraintStatus::enforced) { ++constraints; key_columns += c.columns.size(); }
      }, constraint);
    }
    d.sources.reserve(tables); d.columns.reserve(columns); d.constraints.reserve(constraints);
    d.constraint_columns.reserve(key_columns); d.source_constraints.reserve(constraints);
    d.references.reserve(constraints); d.routes.reserve(bound_.occurrences.size());
    std::vector<std::vector<std::size_t>> local(tables), references;
    std::vector<std::vector<OccurrenceId>> routes(tables);
    for (std::size_t o = 0; o < bound_.occurrences.size(); ++o) routes[bound_.occurrences[o].table.value].push_back(OccurrenceId{o});
    for (std::size_t t = 0; t < tables; ++t) for (const auto& constraint : bound_.catalog.tables[t].constraints) {
      const auto* key = std::get_if<UniqueConstraint>(&constraint);
      if (!key || key->status != ConstraintStatus::enforced) continue;
      auto columns = key->columns; std::sort(columns.begin(), columns.end());
      local[t].push_back(d.constraints.size());
      d.constraints.push_back({TableId{t}, d.name(key->name), append(d.constraint_columns, columns), {}, {}});
    }
    const auto unique_count = d.constraints.size(); references.resize(constraints);
    for (std::size_t t = 0; t < tables; ++t) for (const auto& constraint : bound_.catalog.tables[t].constraints) {
      const auto* key = std::get_if<ForeignKeyConstraint>(&constraint);
      if (!key || key->status != ConstraintStatus::enforced) continue;
      auto target_columns = key->referenced_columns; std::sort(target_columns.begin(), target_columns.end());
      std::size_t parent = 0;
      while (parent < unique_count && (d.constraints[parent].source != key->referenced_table ||
          !std::equal(target_columns.begin(), target_columns.end(), d.constraints[parent].columns.begin(), d.constraints[parent].columns.end()))) ++parent;
      if (parent == unique_count) fail("rows_contract", "validated foreign key has no enforced unique target");
      std::vector<ColumnId> ordered;
      for (const auto column : target_columns) {
        const auto position = static_cast<std::size_t>(std::find(key->referenced_columns.begin(), key->referenced_columns.end(), column) - key->referenced_columns.begin());
        ordered.push_back(key->columns[position]);
      }
      local[t].push_back(d.constraints.size()); references[parent].push_back(d.constraints.size());
      d.constraints.push_back({TableId{t}, d.name(key->name), append(d.constraint_columns, ordered), parent, {}});
    }
    for (std::size_t i = 0; i < d.constraints.size(); ++i) d.constraints[i].referenced_by = append(d.references, references[i]);
    for (std::size_t t = 0; t < tables; ++t) {
      const auto& source = bound_.catalog.tables[t]; const auto first = d.columns.size();
      for (const auto& column : source.columns) d.columns.push_back({d.name(column.name), rows_detail::sql_type(column)});
      d.sources.push_back({TableId{t}, d.name(source.name), source.source_schema_version,
          source.columns.empty() ? std::span<const SqlRowsColumn>{} : std::span<const SqlRowsColumn>{d.columns.data() + first, source.columns.size()},
          append(d.source_constraints, local[t]), append(d.routes, routes[t])});
    }
  }
  void freeze_programs() {
    auto& d = *result_; std::size_t inputs = 0, operations = 0, arguments = 0, non_nulls = 0, equalities = 0, fixed = 0, predicates = 0, projections = 0;
    for (const auto& o : occurrences_) {
      inputs += o.inputs.size(); operations += o.operations.size(); non_nulls += o.non_nulls.size();
      equalities += o.equalities.size(); fixed += o.fixed.size(); predicates += o.predicates.size(); projections += o.projections.size();
      for (const auto id : o.operations) arguments += std::get<BoundOperation>(expression(id).node).arguments.size();
    }
    d.inputs.reserve(inputs); d.operations.reserve(operations); d.arguments.reserve(arguments);
    d.non_nulls.reserve(non_nulls); d.equalities.reserve(equalities); d.fixed.reserve(fixed);
    d.predicates.reserve(predicates); d.projections.reserve(projections); d.occurrences.reserve(occurrences_.size());
    for (std::size_t i = 0; i < occurrences_.size(); ++i) {
      const auto& o = occurrences_[i]; const auto begin = d.operations.size();
      for (const auto id : o.operations) {
        const auto& node = std::get<BoundOperation>(expression(id).node);
        d.operations.push_back({id, node.operation, append(d.arguments, node.arguments)});
      }
      const auto steps = o.operations.empty() ? std::span<const SqlRowsOperation>{} :
          std::span<const SqlRowsOperation>{d.operations.data() + begin, o.operations.size()};
      d.occurrences.push_back({OccurrenceId{i}, bound_.occurrences[i].table, append(d.inputs, o.inputs), steps,
          append(d.non_nulls, o.non_nulls), append(d.equalities, o.equalities), append(d.fixed, o.fixed),
          append(d.predicates, o.predicates), append(d.projections, o.projections)});
    }
  }
  void retain_constants() {
    // Only executable reads need initial constants. This cold pass drops dead
    // folded copies; it adds no runtime slot scan, interning table or cache.
    std::vector<bool> needed(values_.size()); const auto& d = *result_;
    for (const auto& guard : d.fixed) needed[guard.constant.value] = true;
    for (const auto argument : d.arguments) needed[argument.value] = true;
    for (const auto predicate : d.predicates) needed[predicate.value] = true;
    for (const auto& field : d.projections) needed[field.expression.value] = true;
    for (const auto& output : d.outputs)
      if (const auto* constant = std::get_if<ExpressionId>(&output.value)) needed[constant->value] = true;
    for (std::size_t i = 0; i < values_.size(); ++i) if (!needed[i]) values_[i].reset();
  }
 public:
  SqlRowsCompiler(const resource::MemoryAccount& account, const BoundSql& bound, const SqlRowsBindOptions& options)
      : bound_(bound), options_(options), result_(resource::make_accounted_shared<SqlRowsProgram::Data>(
          account, resource::MemoryPurpose::immutable_metadata, account)) {}
  SqlRowsProgram run() {
    auto& d = *result_; d.catalog_version = bound_.catalog.version; d.semantics = bound_.semantics; d.wrapper = bound_.wrapper;
    d.source = resource::AccountedText::copy_of(d.account, bound_.source,
        {resource::MemoryOwnerKind::immutable_metadata, 0}, resource::MemoryPurpose::immutable_metadata);
    if (options_.parameters.size() != bound_.parameters.size()) fail("unbound_parameter", "one value is required for each SQL row parameter");
    for (std::size_t i = 0; i < options_.parameters.size(); ++i) {
      const auto& value = options_.parameters[i];
      const auto cell = value ? SqlRowCell{storage::borrow_scalar(*value)} : SqlRowCell{};
      if (!rows_detail::fits(cell, bound_.parameters[i])) fail("invalid_parameter", "SQL row parameter violates its exact type/nullability/domain");
    }
    std::size_t physical = 0;
    for (const auto& occurrence : bound_.occurrences) {
      offsets_.push_back(physical);
      for (const auto& column : bound_.catalog.tables[occurrence.table.value].columns) {
        ++physical; non_null_.push_back(!column.nullable);
      }
    }
    parent_.resize(physical); std::iota(parent_.begin(), parent_.end(), std::size_t{0}); rank_.resize(physical);
    fixed_.resize(physical); join_live_.resize(physical); physical_expression_.resize(physical); occurrences_.resize(bound_.occurrences.size());
    analyze(); predicates(); fold_grounded(); core(); schemas(); freeze_programs();
    for (std::size_t i = 0; i < values_.size(); ++i) if (known_[i] && values_[i]) {
      if (const auto* text = std::get_if<std::string_view>(&*values_[i]); text && !rows_detail::text_fits(*text))
        fail("unsupported_sql_text", "SQL TEXT constants must be UTF8 without NUL");
    }
    retain_constants(); d.freeze_values(values_); d.work = work_;
    io::Json signature{{"family", "CROWN-SQL-ROWS;1"}, {"source", bound_.source}, {"catalog", io::write_catalog_payload(bound_.catalog)}};
    signature["parameters"] = io::Json::array();
    for (std::size_t i = 0; i < bound_.parameters.size(); ++i) {
      const auto& type = bound_.parameters[i]; const auto& value = options_.parameters[i];
      signature["parameters"].push_back(io::Json{{"kind", static_cast<int>(type.kind)}, {"nullable", type.nullable},
          {"decimal", type.decimal ? io::Json::array({type.decimal->precision, type.decimal->scale}) : io::Json{}},
          {"value", value ? io::write_scalar(*value) : io::Json{}}});
    }
    // Binary framing also preserves opaque catalog hint/untrusted-name bytes;
    // JSON text rendering must not replace them or create source-key collisions.
    const auto encoded = io::Json::to_cbor(signature);
    d.key = sha256_fixed({reinterpret_cast<const char*>(encoded.data()), encoded.size()});
    // Recovery alone opts into this additional linear accounted copy. The
    // canonical signature/hash and selected binder-work policy stay unchanged.
    if(options_.retain_binding_image)
      d.binding=resource::AccountedText::copy_of(d.account,
          {reinterpret_cast<const char*>(encoded.data()),encoded.size()},
          {resource::MemoryOwnerKind::immutable_metadata,0},resource::MemoryPurpose::immutable_metadata);

    SqlRowsProgram result(result_); static_cast<void>(result.export_core()); return result;
  }
};
}  // namespace detail

const SqlRowsProgram::Data& SqlRowsProgram::data() const {
  if (!data_) fail("invalid_sql_rows_program", "SQL rows program handle is empty");
  return *data_;
}
const resource::MemoryAccount& SqlRowsProgram::account() const & { return data().account; }
std::string_view SqlRowsProgram::source() const & { return data().source.view(); }
std::string_view SqlRowsProgram::binding_image() const & {return data().binding.view();}
std::string_view SqlRowsProgram::source_sha256() const & { const auto& d = data(); return {d.key.data(), d.key.size()}; }
SqlSemantics SqlRowsProgram::semantics() const { return data().semantics; }
SqlWrapper SqlRowsProgram::wrapper() const { return data().wrapper; }
bool SqlRowsProgram::contradiction() const { return data().contradiction; }
std::uint64_t SqlRowsProgram::work() const { return data().work; }
std::span<const SqlRowsSource> SqlRowsProgram::sources() const & { return data().sources; }
std::span<const SqlRowsConstraint> SqlRowsProgram::constraints() const & { return data().constraints; }
std::span<const SqlRowsOccurrence> SqlRowsProgram::occurrences() const & { return data().occurrences; }
std::span<const SqlRowsOutput> SqlRowsProgram::outputs() const & { return data().outputs; }
std::span<const SqlRowCell> SqlRowsProgram::initial_values() const & { return data().initial; }

SqlRowsCore SqlRowsProgram::export_core() const {
  const auto& d = data(); SqlRowsCore result; result.catalog.version = d.catalog_version; result.query.contradiction = d.contradiction;
  for (std::size_t i = 0; i < d.variables.size(); ++i) result.query.variables.push_back({"v_" + std::to_string(i), d.variables[i]});
  for (std::size_t i = 0; i < d.head.size(); ++i) result.query.head.push_back({d.head[i], "h_" + std::to_string(i)});
  for (const auto& occurrence : d.occurrences) {
    const auto name = "sql_rows_occurrence_" + std::to_string(occurrence.occurrence.value);
    Table table{name, {}}; Atom atom{name, TableId{result.catalog.tables.size()}, {}};
    for (const auto& field : occurrence.projection) {
      table.columns.push_back({"v_" + std::to_string(field.variable.value), field.type});
      atom.terms.emplace_back(std::in_place_index<0>, field.variable);
    }
    result.catalog.tables.push_back(std::move(table)); result.query.atoms.push_back(std::move(atom));
  }
  validate(result.catalog, result.query); return result;
}

SqlRowsProgram SqlRowsProgram::freeze(const resource::MemoryAccount& account, const SqlRowsProgram& source) {
  if (!account) throw resource::MemoryFailure(resource::MemoryFault::contract);
  const auto& old = source.data();
  if (account.statistics().owner == old.account.statistics().owner) return source;
  auto out = resource::make_accounted_shared<Data>(account, resource::MemoryPurpose::immutable_metadata, account);
  out->source = resource::AccountedText::copy_of(account, old.source.view(),
      {resource::MemoryOwnerKind::immutable_metadata, 0}, resource::MemoryPurpose::immutable_metadata);
  if(!old.binding.view().empty())
    out->binding=resource::AccountedText::copy_of(account,old.binding.view(),
        {resource::MemoryOwnerKind::immutable_metadata,0},resource::MemoryPurpose::immutable_metadata);
  out->key = old.key; out->catalog_version = old.catalog_version; out->work = old.work;
  out->semantics = old.semantics; out->wrapper = old.wrapper; out->contradiction = old.contradiction;
  out->columns.assign(old.columns.begin(), old.columns.end()); out->sources.assign(old.sources.begin(), old.sources.end());
  out->constraints.assign(old.constraints.begin(), old.constraints.end());
  out->constraint_columns.assign(old.constraint_columns.begin(), old.constraint_columns.end());
  out->source_constraints.assign(old.source_constraints.begin(), old.source_constraints.end());
  out->references.assign(old.references.begin(), old.references.end()); out->routes.assign(old.routes.begin(), old.routes.end());
  out->occurrences.assign(old.occurrences.begin(), old.occurrences.end()); out->inputs.assign(old.inputs.begin(), old.inputs.end());
  out->operations.assign(old.operations.begin(), old.operations.end()); out->arguments.assign(old.arguments.begin(), old.arguments.end());
  out->predicates.assign(old.predicates.begin(), old.predicates.end()); out->non_nulls.assign(old.non_nulls.begin(), old.non_nulls.end());
  out->equalities.assign(old.equalities.begin(), old.equalities.end()); out->fixed.assign(old.fixed.begin(), old.fixed.end());
  out->projections.assign(old.projections.begin(), old.projections.end()); out->variables.assign(old.variables.begin(), old.variables.end());
  out->head.assign(old.head.begin(), old.head.end()); out->outputs.assign(old.outputs.begin(), old.outputs.end());
  out->freeze_values(old.initial);
  for (auto& column : out->columns) column.name = out->name(column.name);
  for (auto& table : out->sources) {
    table.name = out->name(table.name); table.columns = rebase(table.columns, old.columns, out->columns);
    table.constraints = rebase(table.constraints, old.source_constraints, out->source_constraints);
    table.occurrences = rebase(table.occurrences, old.routes, out->routes);
  }
  for (auto& constraint : out->constraints) {
    constraint.name = out->name(constraint.name); constraint.columns = rebase(constraint.columns, old.constraint_columns, out->constraint_columns);
    constraint.referenced_by = rebase(constraint.referenced_by, old.references, out->references);
  }
  for (auto& operation : out->operations) operation.arguments = rebase(operation.arguments, old.arguments, out->arguments);
  for (auto& occurrence : out->occurrences) {
    occurrence.inputs = rebase(occurrence.inputs, old.inputs, out->inputs);
    occurrence.operations = rebase(occurrence.operations, old.operations, out->operations);
    occurrence.non_null_columns = rebase(occurrence.non_null_columns, old.non_nulls, out->non_nulls);
    occurrence.equal_columns = rebase(occurrence.equal_columns, old.equalities, out->equalities);
    occurrence.constant_columns = rebase(occurrence.constant_columns, old.fixed, out->fixed);
    occurrence.predicates = rebase(occurrence.predicates, old.predicates, out->predicates);
    occurrence.projection = rebase(occurrence.projection, old.projections, out->projections);
  }
  for (auto& output : out->outputs) output.name = out->name(output.name);
  return SqlRowsProgram(std::move(out));
}

SqlRowsBindResult bind_sql_rows_into(const resource::MemoryAccount& account, std::string_view source,
    const Catalog& catalog, const SqlRowsBindOptions& options) {
  if (!account) throw resource::MemoryFailure(resource::MemoryFault::contract);
  const auto bound = bind_sql(source, catalog, options.binding);
  if (const auto* diagnostic = std::get_if<BindingDiagnostic>(&bound)) return *diagnostic;
  try { return detail::SqlRowsCompiler(account, std::get<BoundSql>(bound), options).run(); }
  catch (const Error& error) {
    const auto phase = error.code() == "invalid_parameter" || error.code() == "unbound_parameter" ? "parameters" : "normalization";
    return BindingDiagnostic{phase, {error.code(), error.what(), {}, {}, {}, {}}};
  }
}
SqlRowsBindResult bind_sql_rows(std::string_view source, const Catalog& catalog, const SqlRowsBindOptions& options) {
  return bind_sql_rows_into(resource::MemoryAccount::create(options.memory_limit_bytes), source, catalog, options);
}
}  // namespace crown::frontend
