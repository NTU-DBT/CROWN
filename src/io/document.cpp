#include "crown/io/document.hpp"
#include "crown/io/tree.hpp"
#include "crown/io/oracle.hpp"
#include "crown/io/catalog.hpp"
#include "crown/catalog/catalog.hpp"
#include "json.hpp"
#include "query_binding.hpp"

#include "crown/api/error.hpp"
#include <algorithm>
#include <initializer_list>
#include <limits>
#include <map>
#include <set>
#include <string>
#include <type_traits>
#include <utility>

namespace crown::io {
Json read_json(std::string_view text) { return detail::parse_json(text); }
namespace {
using detail::array;
using detail::fail;
using detail::fields;
using detail::parse_json;
using detail::string;
using detail::unsigned_integer;
using detail::version;
ScalarType read_type(const Json& value, const std::string& path, std::uint64_t format) {
  const auto name = string(value, path);
  if (name == "int64") return ScalarType::int64;
  if (name == "string") return ScalarType::string;
  if (name == "bool") return ScalarType::boolean;
  if (format >= 2 && name == "date") return ScalarType::date;
  if (format >= 2 && name == "decimal") return ScalarType::decimal;
  throw Error("unsupported_type", path + ": unsupported scalar type " + name);
}
Value read_value(const Json& value, const std::string& path, std::uint64_t format) {
  if (value.is_boolean()) return value.get<bool>();
  if (value.is_string()) return value.get<std::string>();
  if (value.is_number_unsigned()) {
    const auto number = value.get<std::uint64_t>();
    if (number > static_cast<std::uint64_t>(std::numeric_limits<std::int64_t>::max())) fail(path, "integer exceeds int64 range");
    return static_cast<std::int64_t>(number);
  }
  if (value.is_number_integer()) return value.get<std::int64_t>();
  if (format >= 2 && value.is_object() && value.size() == 1) {
    try {
      if (value.contains("date")) return Date::parse(string(value.at("date"), path + ".date"));
      if (value.contains("decimal")) return Decimal::parse(string(value.at("decimal"), path + ".decimal"));
    } catch (const Error& error) {
      throw Error(error.code(), path + ": " + error.what());
    }
  }
  fail(path, "expected a typed scalar; NULL, floating-point values and implicit casts are not admitted");
}
Row read_row(const Json& value, const std::string& path, std::uint64_t format) {
  Row result;
  for (const auto& cell : array(value, path)) result.push_back(read_value(cell, path, format));
  return result;
}
Json write_value(const Value& value) {
  return std::visit([](const auto& cell) -> Json {
    using T = std::decay_t<decltype(cell)>;
    if constexpr (std::is_same_v<T, Date>) return {{"date", cell.to_string()}};
    else if constexpr (std::is_same_v<T, Decimal>) return {{"decimal", cell.to_string()}};
    else return Json(cell);
  }, value);
}
Json write_row(const Row& row) {
  auto result = Json::array();
  for (const auto& value : row) result.push_back(write_value(value));
  return result;
}
template<class Id>
Id lookup(const std::map<std::string, Id>& names, const Json& value, const std::string& path) {
  const auto name = string(value, path);
  const auto it = names.find(name);
  if (it == names.end()) fail(path, "unknown identifier " + name);
  return it->second;
}
}  // namespace

// Ordinary owning DOM/model boundary; native admission and update execution follow later.
Document read_document(std::string_view text) {
  const auto root = parse_json(text);
  fields(root, "$", {"schema_version", "semantics", "catalog", "query"}, {"initial", "updates"});
  const auto format = unsigned_integer(root.at("schema_version"), "$.schema_version");
  if (format < 1 || format > 3) throw Error("unsupported_version", "$.schema_version: expected 1, 2 or 3");
  if (string(root.at("semantics"), "$.semantics") != "set") throw Error("unsupported_semantics", "only set semantics are implemented");
  Document document;
  document.schema_version = format;
  std::map<std::string, TableId> table_names;
  if (format == 3) document.catalog = read_catalog_payload(root.at("catalog"));
  else {
    const auto& catalog = root.at("catalog");
    fields(catalog, "$.catalog", {"version", "tables"});
    document.catalog.version = unsigned_integer(catalog.at("version"), "$.catalog.version");
    for (const auto& input : array(catalog.at("tables"), "$.catalog.tables")) {
      fields(input, "table", {"name", "columns"});
      Table table{string(input.at("name"), "table.name"), {}};
      for (const auto& column : array(input.at("columns"), "table.columns")) {
        fields(column, "column", {"name", "type"});
        table.columns.push_back({string(column.at("name"), "column.name"), read_type(column.at("type"), "column.type", format)});
      }
      document.catalog.tables.push_back(std::move(table));
    }
  }
  for (std::size_t i = 0; i < document.catalog.tables.size(); ++i) table_names.emplace(document.catalog.tables[i].name, TableId{i});
  const auto& query = root.at("query");
  fields(query, "$.query", {"variables", "atoms", "head"}, {"contradiction"});
  std::map<std::string, VariableId> variable_names;
  for (const auto& input : array(query.at("variables"), "query.variables")) {
    fields(input, "variable", {"name", "type"});
    Variable variable{string(input.at("name"), "variable.name"), read_type(input.at("type"), "variable.type", format)};
    variable_names.emplace(variable.name, VariableId{document.query.variables.size()});
    document.query.variables.push_back(std::move(variable));
  }
  for (const auto& input : array(query.at("atoms"), "query.atoms")) {
    fields(input, "atom", {"id", "table", "terms"});
    Atom atom{string(input.at("id"), "atom.id"), lookup(table_names, input.at("table"), "atom.table"), {}};
    for (const auto& term : array(input.at("terms"), "atom.terms")) {
      if (!term.is_object() || term.size() != 1) fail("term", "expected exactly one of var, const, ignore");
      if (term.contains("var")) atom.terms.emplace_back(lookup(variable_names, term.at("var"), "term.var"));
      else if (term.contains("const")) atom.terms.emplace_back(read_value(term.at("const"), "term.const", format));
      else if (term.contains("ignore") && term.at("ignore").is_boolean() && term.at("ignore").get<bool>()) atom.terms.emplace_back(IgnoredColumn{});
      else fail("term", "expected var, const, or ignore:true");
    }
    document.query.atoms.push_back(std::move(atom));
  }
  for (const auto& input : array(query.at("head"), "query.head")) {
    fields(input, "head", {"var"}, {"alias"});
    const auto variable = lookup(variable_names, input.at("var"), "head.var");
    document.query.head.push_back({variable, input.contains("alias") ? string(input.at("alias"), "head.alias") : document.query.variables[variable.value].name});
  }
  if (query.contains("contradiction")) {
    if (!query.at("contradiction").is_boolean()) fail("query.contradiction", "expected bool");
    document.query.contradiction = query.at("contradiction").get<bool>();
  }
  validate(document.catalog, document.query);
  document.initial.tables.resize(document.catalog.tables.size());
  if (root.contains("initial")) {
    std::set<TableId> seen;
    for (const auto& input : array(root.at("initial"), "$.initial")) {
      fields(input, "initial table", {"table", "rows"});
      const auto table = lookup(table_names, input.at("table"), "initial.table");
      if (!seen.insert(table).second) fail("initial", "table may appear only once");
      for (const auto& input_row : array(input.at("rows"), "initial.rows")) {
        auto row = read_row(input_row, "initial.rows[]", format);
        validate_row(document.catalog, table, row);
        document.initial.tables[table.value].insert(std::move(row));
      }
    }
  }
  if (root.contains("updates")) {
    std::uint64_t expected_sequence = 1;
    for (const auto& input : array(root.at("updates"), "$.updates")) {
      fields(input, "update", {"schema_version", "sequence", "table", "op", "values"});
      version(input.at("schema_version"), "update.schema_version", format);
      const auto sequence = unsigned_integer(input.at("sequence"), "update.sequence");
      if (sequence != expected_sequence++) throw Error("invalid_sequence", "update sequence must be contiguous, starting at 1");
      const auto table = lookup(table_names, input.at("table"), "update.table");
      const auto op = string(input.at("op"), "update.op");
      if (op != "insert" && op != "delete") fail("update.op", "expected insert or delete");
      auto row = read_row(input.at("values"), "update.values", format);
      validate_row(document.catalog, table, row);
      document.updates.push_back({sequence, table, op == "insert" ? SetOperation::insert : SetOperation::erase, std::move(row)});
    }
  }
  validate_database(document.catalog, document.initial);
  return document;
}

Document upgrade_document(const Document& document, std::uint64_t target_version) {
  if (target_version < document.schema_version || target_version < 1 || target_version > 3)
    throw Error("unsupported_version", "CQ migration supports only upward versions 1 through 3");
  static_cast<void>(write_document(document));
  auto result = document; result.schema_version = target_version;
  static_cast<void>(write_document(result));
  return result;
}

Json write_relation(const Relation& relation) {
  auto result = Json::array();
  for (const auto& row : relation) result.push_back(write_row(row));
  return result;
}
Json write_scalar(const Value& value) { return write_value(value); }
// JSON copies borrowed/stack scalar text; the returned DOM owns its bytes.
Json write_scalar_view(const storage::ScalarView& value) {
  return std::visit([](const auto& cell)->Json {
    using T=std::decay_t<decltype(cell)>;
    if constexpr(std::is_same_v<T,Date>)return {{"date",cell.to_string()}};
    else if constexpr(std::is_same_v<T,storage::InlineDecimal>) {
      std::array<char,storage::InlineDecimal::text_capacity> bytes{};
      const auto count=cell.render(bytes);return {{"decimal",std::string_view(bytes.data(),count)}};
    }else return Json(cell);
  },value);
}
Value read_scalar(const Json& value) { return read_value(value,"$",3); }
Json write_epoch(const CommittedReferenceEpoch& epoch) {
  return {{"sequence", epoch.sequence}, {"input_changed", epoch.input_changed}, {"current", write_relation(epoch.current)},
          {"delta", {{"added", write_relation(epoch.delta.added)}, {"removed", write_relation(epoch.delta.removed)}}}};
}

Json write_document(const Document& document) {
  if (document.schema_version < 1 || document.schema_version > 3) throw Error("unsupported_version", "expected document schema_version 1, 2 or 3");
  if (document.schema_version < 3 && catalog::requires_format3(document.catalog)) throw Error("unsupported_version", "catalog metadata requires document schema_version 3");
  validate(document.catalog, document.query);
  validate_database(document.catalog, document.initial);
  auto tables = Json::array();
  for (const auto& table : document.catalog.tables) {
    auto columns = Json::array();
    for (const auto& column : table.columns) {
      if (document.schema_version == 1 && (column.type == ScalarType::date || column.type == ScalarType::decimal)) {
        throw Error("unsupported_version", "date and decimal require document schema_version 2");
      }
      columns.push_back({{"name", column.name}, {"type", type_name(column.type)}});
    }
    tables.push_back({{"name", table.name}, {"columns", std::move(columns)}});
  }
  auto variables = Json::array();
  for (const auto& variable : document.query.variables) variables.push_back({{"name", variable.name}, {"type", type_name(variable.type)}});
  auto atoms = Json::array();
  for (const auto& atom : document.query.atoms) {
    auto terms = Json::array();
    for (const auto& term : atom.terms) {
      if (const auto* variable = std::get_if<VariableId>(&term)) terms.push_back({{"var", document.query.variables[variable->value].name}});
      else if (const auto* literal = std::get_if<Value>(&term)) terms.push_back({{"const", write_value(*literal)}});
      else terms.push_back({{"ignore", true}});
    }
    atoms.push_back({{"id", atom.occurrence}, {"table", document.catalog.tables[atom.table.value].name}, {"terms", std::move(terms)}});
  }
  auto head = Json::array();
  for (const auto& output : document.query.head) head.push_back({{"var", document.query.variables[output.variable.value].name}, {"alias", output.alias}});
  auto initial = Json::array();
  for (std::size_t i = 0; i < document.catalog.tables.size(); ++i) initial.push_back({{"table", document.catalog.tables[i].name}, {"rows", write_relation(document.initial.tables[i])}});
  auto updates = Json::array();
  std::uint64_t expected_sequence = 1;
  for (const auto& update : document.updates) {
    if (update.sequence != expected_sequence++) throw Error("invalid_sequence", "update sequence must be contiguous, starting at 1");
    if (update.operation != SetOperation::insert && update.operation != SetOperation::erase) throw Error("invalid_update", "unknown set operation");
    validate_row(document.catalog, update.table, update.values);
    updates.push_back({{"schema_version", document.schema_version}, {"sequence", update.sequence}, {"table", document.catalog.tables[update.table.value].name},
                       {"op", update.operation == SetOperation::insert ? "insert" : "delete"}, {"values", write_row(update.values)}});
  }
  // Format 3 builds a separate rich DOM while the legacy table DOM remains local.
  Json catalog_payload = document.schema_version == 3 ? write_catalog_payload(document.catalog) : Json{{"version", document.catalog.version}, {"tables", std::move(tables)}};
  return {{"schema_version", document.schema_version}, {"semantics", "set"}, {"catalog", std::move(catalog_payload)},
          {"query", {{"variables", std::move(variables)}, {"atoms", std::move(atoms)}, {"head", std::move(head)}, {"contradiction", document.query.contradiction}}},
          {"initial", std::move(initial)}, {"updates", std::move(updates)}};
}

// Decode names and claims only; independent tree verification grants an upper bound.
FreeConnexTree read_tree(std::string_view text, const Catalog& catalog, const Query& query) {
  validate(catalog, query);
  const auto input = parse_json(text);
  fields(input, "$", {"schema_version", "catalog_version", "semantics", "root", "nodes"}, {"connex", "native_height"});
  version(input.at("schema_version"), "$.schema_version");
  if (unsigned_integer(input.at("catalog_version"), "$.catalog_version") != catalog.version) throw Error("catalog_mismatch", "plan catalog version does not match the supplied query catalog");
  if (string(input.at("semantics"), "$.semantics") != "set") throw Error("unsupported_semantics", "only set structural plans are implemented");
  std::map<std::string, VariableId> variables;
  std::map<std::string, std::size_t> occurrences;
  std::map<std::string, NodeId> nodes;
  for (std::size_t i = 0; i < query.variables.size(); ++i) variables.emplace(query.variables[i].name, VariableId{i});
  for (std::size_t i = 0; i < query.atoms.size(); ++i) occurrences.emplace(query.atoms[i].occurrence, i);
  const auto& inputs = array(input.at("nodes"), "$.nodes");
  for (std::size_t i = 0; i < inputs.size(); ++i) {
    const auto& node = inputs[i];
    if (!node.is_object() || !node.contains("id")) fail("node", "expected object with an ID");
    const auto id = string(node.at("id"), "node.id");
    if (id.empty() || !nodes.emplace(id, NodeId{i}).second) fail("node.id", "node IDs must be nonempty and unique");
  }
  const auto read_scope = [&](const Json& value, const std::string& path) {
    VariableSet scope;
    for (const auto& name : array(value, path)) {
      const auto variable = lookup(variables, name, path);
      if (!scope.insert(variable).second) fail(path, "duplicate scope variable");
    }
    return scope;
  };
  FreeConnexTree tree;
  if (!input.at("root").is_null()) tree.root = lookup(nodes, input.at("root"), "$.root");
  for (const auto& node : inputs) {
    if (!node.contains("kind")) fail("node", "missing field kind");
    const auto kind = string(node.at("kind"), "node.kind");
    if (kind == "native") fields(node, "native node", {"id", "kind", "scope", "children", "occurrence"}, {"separator"});
    else if (kind == "generalized") fields(node, "generalized node", {"id", "kind", "scope", "children"}, {"separator"});
    else fail("node.kind", "expected native or generalized");
    TreeNode decoded{string(node.at("id"), "node.id"), kind == "native" ? NodeKind::native : NodeKind::generalized,
                     read_scope(node.at("scope"), "node.scope"), {}, {}, {}};
    if (kind == "native") decoded.occurrence = lookup(occurrences, node.at("occurrence"), "node.occurrence");
    for (const auto& child : array(node.at("children"), "node.children")) decoded.children.push_back(lookup(nodes, child, "node.children"));
    if (node.contains("separator")) decoded.claimed_separator = read_scope(node.at("separator"), "node.separator");
    tree.nodes.push_back(std::move(decoded));
  }
  if (input.contains("connex")) {
    tree.claimed_connex.emplace();
    for (const auto& id : array(input.at("connex"), "$.connex")) tree.claimed_connex->push_back(lookup(nodes, id, "$.connex"));
  }
  if (input.contains("native_height")) {
    const auto height = unsigned_integer(input.at("native_height"), "$.native_height");
    if (height > std::numeric_limits<std::size_t>::max()) fail("$.native_height", "height exceeds platform size_t range");
    tree.claimed_native_height = static_cast<std::size_t>(height);
  }
  return tree;
}

// Addressability checks do not verify graph structure or claimed height.
Json write_tree(const FreeConnexTree& tree, const Catalog& catalog, const Query& query) {
  validate(catalog, query);
  std::set<std::string> names;
  for (const auto& node : tree.nodes) {
    if (node.id.empty() || !names.insert(node.id).second) fail("tree", "node IDs must be nonempty and unique");
  }
  const auto node_name = [&](NodeId id) {
    if (id.value >= tree.nodes.size()) fail("tree", "node ID out of range");
    return tree.nodes[id.value].id;
  };
  const auto scope_json = [&](const VariableSet& scope) {
    auto value = Json::array();
    for (const auto variable : scope) {
      if (variable.value >= query.variables.size()) fail("tree", "variable ID out of range");
      value.push_back(query.variables[variable.value].name);
    }
    return value;
  };
  auto nodes = Json::array();
  for (const auto& node : tree.nodes) {
    auto children = Json::array();
    for (const auto child : node.children) children.push_back(node_name(child));
    if (node.kind != NodeKind::native && node.kind != NodeKind::generalized) fail("tree", "unknown node kind");
    Json input{{"id", node.id}, {"kind", node.kind == NodeKind::native ? "native" : "generalized"},
               {"scope", scope_json(node.scope)}, {"children", std::move(children)}};
    if (node.kind == NodeKind::native) {
      if (!node.occurrence || *node.occurrence >= query.atoms.size()) fail("tree", "native occurrence ID out of range");
      input["occurrence"] = query.atoms[*node.occurrence].occurrence;
    } else if (node.occurrence) fail("tree", "generalized node cannot have an external occurrence");
    if (node.claimed_separator) input["separator"] = scope_json(*node.claimed_separator);
    nodes.push_back(std::move(input));
  }
  Json output{{"schema_version", 1}, {"catalog_version", catalog.version}, {"semantics", "set"},
              {"root", tree.root ? Json(node_name(*tree.root)) : Json(nullptr)}, {"nodes", std::move(nodes)}};
  if (tree.claimed_connex) {
    auto connex = Json::array();
    for (const auto id : *tree.claimed_connex) connex.push_back(node_name(id));
    output["connex"] = std::move(connex);
  }
  if (tree.claimed_native_height) output["native_height"] = *tree.claimed_native_height;
  return output;
}

// Report formatting trusts the supplied aggregate; it does not rerun the verifier.
Json write_validation(const planner::ValidationReport& report, const FreeConnexTree& tree, const Query& query) {
  const auto node_name = [&](NodeId id) { return id.value < tree.nodes.size() ? tree.nodes[id.value].id : "#node[" + std::to_string(id.value) + "]"; };
  const auto variable_name = [&](VariableId id) { return id.value < query.variables.size() ? query.variables[id.value].name : "#variable[" + std::to_string(id.value) + "]"; };
  auto connex = Json::array();
  for (const auto id : report.maximal_connex) connex.push_back(node_name(id));
  auto separators = Json::array();
  for (std::size_t i = 0; i < report.separators.size(); ++i) {
    auto variables = Json::array();
    for (const auto variable : report.separators[i]) variables.push_back(variable_name(variable));
    separators.push_back({{"node", node_name(NodeId{i})}, {"variables", std::move(variables)}});
  }
  auto violations = Json::array();
  for (const auto& violation : report.violations) {
    Json item{{"rule", violation.rule}, {"message", violation.message}};
    if (violation.node) item["node"] = node_name(*violation.node);
    if (violation.variable) item["variable"] = variable_name(*violation.variable);
    if (violation.occurrence) item["occurrence"] = *violation.occurrence < query.atoms.size() ? query.atoms[*violation.occurrence].occurrence : "#occurrence[" + std::to_string(*violation.occurrence) + "]";
    if (violation.related_node) item["related_node"] = node_name(*violation.related_node);
    violations.push_back(std::move(item));
  }
  return {{"schema_version", 1}, {"tree_valid", report.valid},
          {"native_height", report.native_height ? Json(*report.native_height) : Json(nullptr)},
          {"edge_depth", report.edge_depth ? Json(*report.edge_depth) : Json(nullptr)},
          {"height_status", report.valid ? "valid_upper_bound" : "invalid"},
          {"maximal_connex", std::move(connex)}, {"separators", std::move(separators)}, {"violations", std::move(violations)}};
}

namespace {
using detail::query_binding;
std::size_t index_value(const Json& value, const std::string& path) {
  const auto number = unsigned_integer(value, path);
  if (number > std::numeric_limits<std::size_t>::max()) fail(path, "integer exceeds platform index range");
  return static_cast<std::size_t>(number);
}
}  // namespace

// Legacy flag gate: this serializer does not independently replay the proof.
Json write_oracle(const planner::OracleResult& result, const Catalog& catalog, const Query& query) {
  const bool limited = result.status == planner::OracleStatus::resource_limit;
  const bool minimum = result.status == planner::OracleStatus::proven_minimum;
  if (!limited && !result.certificate_verified) throw Error("invalid_search_certificate", "public exact-search results require independent certificate verification");
  Json tree = result.tree ? write_tree(*result.tree, catalog, query) : Json(nullptr);
  Json certificate = nullptr;
  if (!limited) {
    const auto certificate_version=result.algorithm=="crown_partition_exact_v2"?2:1;
    if (result.algorithm!="crown_partition_exact_v1" && result.algorithm!="crown_partition_exact_v2")
      throw Error("invalid_search_certificate","unknown exact-search certificate algorithm");
    auto bounds = Json::array();
    for (const auto& entry : result.lower_bounds) {
      bounds.push_back({{"occurrences", entry.occurrences}, {"generalized_allowed", entry.generalized_allowed},
                        {"connex_reachable", entry.connex_reachable}, {"bound", entry.bound ? Json(*entry.bound) : Json(nullptr)}});
    }
    certificate = {{"schema_version", certificate_version}, {"algorithm", result.algorithm}, {"query_binding", query_binding(catalog, query)},
                   {"minimum_height", result.minimum_height ? Json(*result.minimum_height) : Json(nullptr)},
                   {"tree", tree}, {"lower_bounds", std::move(bounds)}};
  }
  const auto height = result.minimum_height ? Json(*result.minimum_height) : Json(nullptr);
  const auto& stats = result.statistics;
  return {{"schema_version", 1}, {"tree_valid", result.tree.has_value()}, {"selected_height", height},
          {"height_lower_bound", limited ? Json(query.atoms.empty() ? 0 : 1) : height}, {"height_upper_bound", height},
          {"height_status", limited ? "resource_limit" : minimum ? "proven_minimum" : "unsupported"},
          {"height_search_complete", !limited}, {"height_evidence", limited ? "incomplete_search" : "independently_replayed_finite_lower_bound"},
          {"cost_status", "not_optimized"}, {"cost_search_complete", false}, {"query_semantics", "set"},
          {"runtime_backend", "not_installed"}, {"algorithm", result.algorithm}, {"reason", result.reason},
          {"tree", std::move(tree)}, {"certificate", std::move(certificate)},
          {"limits", {{"work_limit", result.limits.work_limit ? Json(*result.limits.work_limit) : Json(nullptr)},
                      {"recursion_limit", result.limits.recursion_limit ? Json(*result.limits.recursion_limit) : Json(nullptr)},
                      {"literal_scope_limit", result.limits.literal_scope_limit ? Json(*result.limits.literal_scope_limit) : Json(nullptr)},
                      {"time_limit_ms", result.limits.time_limit ? Json(result.limits.time_limit->count()) : Json(nullptr)}}},
          {"search", {{"work", stats.work}, {"states", stats.states}, {"partitions", stats.partitions},
                       {"candidates", stats.candidates}, {"cache_hits", stats.cache_hits}, {"certificate_work", stats.certificate_work},
                       {"hierarchy_tests",stats.hierarchy_tests},{"hierarchy_hits",stats.hierarchy_hits},
                       {"singleton_hits",stats.singleton_hits},{"empty_body_hits",stats.empty_body_hits},
                       {"component_splits",stats.component_splits},{"symmetry_skips",stats.symmetry_skips},
                       {"bound_prunes",stats.bound_prunes}}}};
}

// Binding/type checks produce an unverified claim; whole independent replay is separate.
planner::HeightCertificate read_height_certificate(std::string_view text, const Catalog& catalog, const Query& query) {
  const auto input = parse_json(text);
  fields(input, "$", {"schema_version", "algorithm", "query_binding", "minimum_height", "tree", "lower_bounds"});
  const auto format=unsigned_integer(input.at("schema_version"),"$.schema_version");
  if (format!=1 && format!=2) throw Error("unsupported_version","height certificate requires version 1 or 2");
  const auto algorithm=string(input.at("algorithm"),"$.algorithm");
  if ((format==1 && algorithm=="crown_partition_exact_v2") ||
      (format==2 && algorithm!="crown_partition_exact_v2"))
    throw Error("unsupported_version","height certificate version and algorithm differ");
  const auto binding_text = input.at("query_binding").dump();
  static_cast<void>(read_document(binding_text));
  // Canonical JSON text keeps bool/int/float distinctions that JSON numeric
  // equality would otherwise erase. The binding contains no runtime data.
  if (binding_text != query_binding(catalog, query).dump()) throw Error("certificate_binding", "certificate is bound to a different catalog/query");
  planner::HeightCertificate certificate;
  certificate.algorithm = algorithm;
  if (!input.at("minimum_height").is_null()) certificate.minimum_height = index_value(input.at("minimum_height"), "$.minimum_height");
  if (!input.at("tree").is_null()) certificate.tree = read_tree(input.at("tree").dump(), catalog, query);
  for (const auto& value : array(input.at("lower_bounds"), "$.lower_bounds")) {
    fields(value, "lower-bound state", {"occurrences", "generalized_allowed", "connex_reachable", "bound"});
    if (!value.at("generalized_allowed").is_boolean() || !value.at("connex_reachable").is_boolean()) fail("lower-bound state", "state flags must be Boolean");
    planner::LowerBoundEntry entry{{}, value.at("generalized_allowed").get<bool>(), value.at("connex_reachable").get<bool>(), {}};
    for (const auto& occurrence : array(value.at("occurrences"), "state.occurrences")) entry.occurrences.push_back(index_value(occurrence, "state.occurrences"));
    if (!value.at("bound").is_null()) entry.bound = index_value(value.at("bound"), "state.bound");
    certificate.lower_bounds.push_back(std::move(entry));
  }
  return certificate;
}

Json write_certificate_report(const planner::CertificateReport& report) {
  return {{"schema_version", 1}, {"certificate_valid", report.valid}, {"resource_limit", report.resource_limit},
          {"message", report.message}, {"work", report.work}};
}
}  // namespace crown::io
