#include "crown/io/identity.hpp"
#include "crown/annotations/policy.hpp"

#include "crown/api/error.hpp"
#include "crown/io/catalog.hpp"
#include "crown/ir/digest.hpp"
#include <algorithm>
#include <limits>
#include <numeric>
#include <utility>

namespace crown::io {
namespace {
// Shared abstract operation counter, not a serialized-byte or CPU/memory meter.
struct Work {
  IdentityLimits limits;
  std::uint64_t used = 0;
  void charge() {
    if (used == std::numeric_limits<std::uint64_t>::max() || (limits.work_limit && used >= *limits.work_limit))
      throw Error("resource_limit","canonical identity work limit exceeded; no partial identity returned");
    ++used;
  }
};
Json type_json(const frontend::SqlType& type) {
  Json result{{"kind",frontend::sql_kind_name(type.kind)},{"nullable",type.nullable}};
  if (type.decimal) result["decimal"]={{"precision",type.decimal->precision},{"scale",type.decimal->scale}};
  return result;
}
Json sql_value(const frontend::SqlValue& value) { return value ? write_scalar(*value) : Json(nullptr); }
std::string digest(std::string_view domain, const Json& value) {
  return sha256(Json{{"domain",domain},{"version",1},{"value",value}}.dump());
}
Json semantic_catalog(const Catalog& catalog) {
  auto result=write_catalog_payload(catalog);
  for (auto& table : result["tables"]) { table.erase("statistics"); table.erase("key_hints"); }
  return result;
}
Json sorted(Json values, Work& work) {
  std::vector<std::pair<std::string,Json>> keyed;
  for (auto& value : values) { work.charge(); keyed.emplace_back(value.dump(),std::move(value)); }
  std::sort(keyed.begin(),keyed.end(),[&](const auto& left,const auto& right) { work.charge(); return left.first < right.first; });
  auto result=Json::array(); for (auto& entry : keyed) result.push_back(std::move(entry.second)); return result;
}

class Canonicalizer {
 public:
  Canonicalizer(const Catalog& source, const Query& query, std::vector<Json> labels,
      std::vector<std::vector<std::optional<VariableId>>> classes, Json semantics, Json output, Work& work)
      : source_(source),query_(query),labels_(std::move(labels)),classes_(std::move(classes)),
        semantics_(std::move(semantics)),output_(std::move(output)),work_(work) {}
  QueryIdentity run(const CachePolicy& policy);
 private:
  const Catalog& source_;
  const Query& query_;
  std::vector<Json> labels_;
  std::vector<std::vector<std::optional<VariableId>>> classes_;
  Json semantics_;
  Json output_;
  Work& work_;
};

// Equal-color groups may require a product of factorial permutations. Every
// complete candidate owns/copies serialized metadata; no best-so-far hash escapes.
QueryIdentity Canonicalizer::run(const CachePolicy& policy) {
  work_.charge();
  annotations::require_set_backend_policy(policy.arithmetic);
  if (policy.planner.empty() || policy.optimization.empty() || policy.cost_model.empty())
    throw Error("invalid_policy","identity requires the supported arithmetic policy and nonempty planner/optimization/cost versions");
  std::vector<std::string> colors;
  for (std::size_t a=0; a<query_.atoms.size(); ++a) {
    work_.charge(); auto shapes=Json::array();
    for (const auto& term : query_.atoms[a].terms) {
      work_.charge();
      if (const auto* variable=std::get_if<VariableId>(&term)) shapes.push_back({{"variable_type",type_name(query_.variables.at(variable->value).type)}});
      else if (const auto* value=std::get_if<Value>(&term)) shapes.push_back({{"constant",write_scalar(*value)}});
      else shapes.push_back({{"ignore",true}});
    }
    labels_.at(a)["term_shapes"]=std::move(shapes); colors.push_back(labels_[a].dump());
  }
  std::vector<std::size_t> order(query_.atoms.size()); std::iota(order.begin(),order.end(),std::size_t{0});
  std::sort(order.begin(),order.end(),[&](std::size_t left,std::size_t right) {
    work_.charge(); return colors[left] == colors[right] ? left < right : colors[left] < colors[right];
  });
  std::vector<std::pair<std::size_t,std::size_t>> groups;
  for (std::size_t begin=0; begin<order.size();) {
    auto end=begin+1; while (end<order.size() && colors[order[begin]]==colors[order[end]]) { work_.charge(); ++end; }
    groups.emplace_back(begin,end); begin=end;
  }
  const auto catalog=semantic_catalog(source_);
  std::string best_text; QueryIdentity best;
  for (;;) {
    work_.charge();
    std::vector<std::optional<std::size_t>> variables(query_.variables.size());
    std::vector<std::size_t> inverse; auto atoms=Json::array(); auto types=Json::array();
    const auto variable_id=[&](VariableId variable) {
      work_.charge(); auto& id=variables.at(variable.value);
      if (!id) { id=inverse.size(); inverse.push_back(variable.value); types.push_back(type_name(query_.variables.at(variable.value).type)); }
      return *id;
    };
    for (const auto original : order) {
      work_.charge(); auto terms=Json::array();
      for (const auto& term : query_.atoms[original].terms) {
        if (const auto* variable=std::get_if<VariableId>(&term)) terms.push_back({{"variable",variable_id(*variable)}});
        else if (const auto* value=std::get_if<Value>(&term)) { work_.charge(); terms.push_back({{"constant",write_scalar(*value)}}); }
        else { work_.charge(); terms.push_back({{"ignore",true}}); }
      }
      atoms.push_back({{"input",labels_[original]},{"terms",std::move(terms)}});
    }
    if (!classes_.empty()) {
      for (std::size_t a=0; a<order.size(); ++a) {
        auto classes=Json::array();
        for (const auto variable : classes_.at(order[a])) { work_.charge(); classes.push_back(variable ? Json(variable_id(*variable)) : Json(nullptr)); }
        atoms[a]["physical_classes"]=std::move(classes);
      }
    }
    auto head=Json::array(); for (const auto& output : query_.head) head.push_back(variable_id(output.variable));
    Json candidate{{"identity_version",1},{"catalog",catalog},{"semantics",semantics_},
        {"variables",std::move(types)},{"atoms",std::move(atoms)},{"head",std::move(head)},{"contradiction",query_.contradiction}};
    const auto text=candidate.dump();
    if (best_text.empty() || text<best_text) {
      best_text=text; best.canonical=std::move(candidate); best.occurrence_order=order; best.variable_order=std::move(inverse);
    }
    bool advanced=false;
    for (auto group=groups.rbegin(); group!=groups.rend(); ++group) {
      auto first=order.begin()+static_cast<std::ptrdiff_t>(group->first);
      auto last=order.begin()+static_cast<std::ptrdiff_t>(group->second);
      if (std::next_permutation(first,last,[&](std::size_t left,std::size_t right) { work_.charge(); return left<right; })) { advanced=true; break; }
    }
    if (!advanced) break;
  }
  best.semantic_sha256=digest("crown.query.semantic",best.canonical);
  best.output_contract_sha256=digest("crown.query.output",output_);
  best.cost_inputs_sha256=digest("crown.query.cost-inputs",write_catalog_payload(source_));
  best.plan_cache_sha256=digest("crown.plan.cache",{{"semantic",best.semantic_sha256},{"output",best.output_contract_sha256},
      {"cost_inputs",best.cost_inputs_sha256},{"arithmetic",policy.arithmetic},{"planner",policy.planner},
      {"optimization",policy.optimization},{"cost_model",policy.cost_model}});
  best.work=work_.used; return best;
}

// Compile an address/ID-independent description of one adapter's expressions.
// Producer-validated inner USING is the left value plus a separate equality.
// Ordinary JSON operands copy subtrees; slot capacity spans the full binding
// expression count for each adapter. This is a cold compiler boundary.
std::vector<Json> local_expressions(const frontend::NormalizedSql& query, const frontend::OccurrenceAdapter& adapter, Work& work) {
  using namespace frontend;
  std::vector<Json> expressions(query.binding.expressions.size());
  const auto operand=[&](ExpressionId id) -> Json {
    work.charge();
    if (!expressions.at(id.value).is_null()) return expressions[id.value];
    return {{"literal",sql_value(query.constants.at(id.value))},{"type",type_json(query.binding.expressions.at(id.value).type)}};
  };
  for (const auto id : adapter.program) {
    work.charge(); const auto& expression=query.binding.expressions.at(id.value);
    if (const auto* column=std::get_if<BoundColumn>(&expression.node)) {
      if (column->occurrence!=adapter.occurrence) throw Error("invalid_program","foreign column in identity's local adapter");
      expressions[id.value]={{"column",column->column.value}};
      continue;
    }
    const auto& node=std::get<BoundOperation>(expression.node);
    if (node.operation==SqlOperator::identity_cast || node.operation==SqlOperator::literal_cast ||
        node.operation==SqlOperator::widen_integer || node.operation==SqlOperator::using_value) {
      expressions[id.value]=operand(node.arguments.at(0)); continue;
    }
    auto arguments=Json::array();
    auto op=node.operation;
    if (op==SqlOperator::greater || op==SqlOperator::greater_equal) {
      arguments.push_back(operand(node.arguments.at(1))); arguments.push_back(operand(node.arguments.at(0)));
      op=op==SqlOperator::greater ? SqlOperator::less : SqlOperator::less_equal;
    } else for (const auto child : node.arguments) arguments.push_back(operand(child));
    const auto name=sql_operator_name(op);
    if (op==SqlOperator::conjunction || op==SqlOperator::disjunction) {
      auto flattened=Json::array();
      for (auto& argument : arguments) {
        if (argument.value("operator",std::string{})==name) for (auto& child : argument.at("arguments")) flattened.push_back(std::move(child));
        else flattened.push_back(std::move(argument));
      }
      arguments=sorted(std::move(flattened),work);
    } else if (op==SqlOperator::equal || op==SqlOperator::not_equal) arguments=sorted(std::move(arguments),work);
    expressions[id.value]={{"operator",name},{"arguments",std::move(arguments)}};
  }
  return expressions;
}
}  // namespace

QueryIdentity query_identity(const Catalog& catalog, const Query& query, const CachePolicy& policy, IdentityLimits limits) {
  validate(catalog,query); Work work{limits}; work.charge();
  std::vector<Json> labels; auto output=Json::array();
  for (const auto& atom : query.atoms) { work.charge(); labels.push_back({{"base",atom.table.value}}); }
  for (const auto& field : query.head) output.push_back({{"name",field.alias},{"type",type_name(query.variables.at(field.variable.value).type)}});
  return Canonicalizer(catalog,query,std::move(labels),{},{{"profile","direct-cq-v1"},{"rows","set"},{"arithmetic",policy.arithmetic}},std::move(output),work).run(policy);
}

QueryIdentity query_identity(const frontend::NormalizedSql& query, const CachePolicy& policy, IdentityLimits limits) {
  validate(query.core_catalog,query.core); Work work{limits}; work.charge();
  if (query.adapters.size()!=query.core.atoms.size()) throw Error("invalid_program","identity requires one adapter per core atom");
  std::vector<Json> labels; std::vector<std::vector<std::optional<VariableId>>> classes;
  for (const auto& adapter : query.adapters) {
    work.charge(); const auto expressions=local_expressions(query,adapter,work);
    auto filters=Json::array(), projection=Json::array(), equalities=Json::array();
    for (const auto id : adapter.predicates) { work.charge(); filters.push_back(expressions.at(id.value)); }
    for (const auto& fixed : adapter.constant_columns) {
      work.charge();
      const auto& column=query.binding.catalog.tables.at(adapter.base.value).columns.at(fixed.column.value);
      frontend::SqlKind kind=frontend::SqlKind::unknown;
      switch (column.type) {
        case ScalarType::int64: kind=frontend::SqlKind::int64; break;
        case ScalarType::string: kind=frontend::SqlKind::string; break;
        case ScalarType::boolean: kind=frontend::SqlKind::boolean; break;
        case ScalarType::date: kind=frontend::SqlKind::date; break;
        case ScalarType::decimal: kind=frontend::SqlKind::decimal; break;
      }
      Json arguments=Json::array({Json{{"column",fixed.column.value}},
          Json{{"literal",write_scalar(fixed.value)},{"type",type_json({kind,false,column.decimal})}}});
      filters.push_back({{"operator","equal"},{"arguments",sorted(std::move(arguments),work)}});
    }
    for (const auto& slot : adapter.projection) { work.charge(); projection.push_back(expressions.at(slot.expression.value)); }
    for (const auto& pair : adapter.equal_columns) equalities.push_back({pair.left.value,pair.right.value});
    auto guards=Json::array(); for (const auto column : adapter.non_null_columns) guards.push_back(column.value);
    labels.push_back({{"base",adapter.base.value},{"filters",sorted(std::move(filters),work)},
        {"projection",std::move(projection)},{"equal_columns",std::move(equalities)},{"non_null_columns",std::move(guards)}});
    classes.push_back(adapter.column_classes);
  }
  const auto mode=[](frontend::SqlSemantics value) { return value==frontend::SqlSemantics::set ? "set" : "bag"; };
  auto parameters=Json::array(), output_semantics=Json::array(), output_contract=Json::array();
  for (std::size_t i=0; i<query.parameters.size(); ++i) parameters.push_back({{"type",type_json(query.binding.parameters.at(i))},{"value",sql_value(query.parameters[i])}});
  for (const auto& field : query.outputs) {
    Json item{{"type",type_json(field.type)}};
    if (const auto* core=std::get_if<frontend::CoreOutput>(&field.value)) { item["kind"]="core"; item["column"]=core->column; }
    else { item["kind"]="constant"; item["value"]=write_scalar(std::get<frontend::ConstantOutput>(field.value).value); }
    output_semantics.push_back(std::move(item)); output_contract.push_back({{"name",field.name},{"type",type_json(field.type)}});
  }
  if (query.binding.wrapper==frontend::SqlWrapper::exists) output_contract.push_back({{"name",query.binding.wrapper_alias},{"type",type_json({frontend::SqlKind::boolean,false,{}})}});
  Json semantics{{"profile","normalized-sql-v1"},{"arithmetic",policy.arithmetic},{"requested_semantics",mode(query.binding.semantics)},
      {"inner_semantics",query.binding.inner_semantics ? Json(mode(*query.binding.inner_semantics)) : Json(nullptr)},
      {"wrapper",query.binding.wrapper==frontend::SqlWrapper::exists ? "exists" : "rows"},
      {"parameters",std::move(parameters)},{"outputs",std::move(output_semantics)}};
  return Canonicalizer(query.binding.catalog,query.core,std::move(labels),std::move(classes),std::move(semantics),std::move(output_contract),work).run(policy);
}

// Caller supplies a complete initialized producer DTO. These labels do not
// recompute digests or validate fields edited after identity construction.
Json write_identity(const QueryIdentity& identity) {
  return {{"schema_version",1},{"identity_valid",true},{"status","complete"},{"algorithm","sha256"},
      {"semantic_sha256",identity.semantic_sha256},{"output_contract_sha256",identity.output_contract_sha256},
      {"cost_inputs_sha256",identity.cost_inputs_sha256},{"plan_cache_sha256",identity.plan_cache_sha256},
      {"canonical",identity.canonical},{"occurrence_order",identity.occurrence_order},{"variable_order",identity.variable_order},{"work",identity.work}};
}
}  // namespace crown::io
