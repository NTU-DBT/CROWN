#include "crown/runtime/comparisons.hpp"
#include "crown/io/document.hpp"
#include "crown/io/tree.hpp"
#include "crown/planner/oracle.hpp"
#include "crown/planner/lower.hpp"
#include "crown/api/error.hpp"
#include "indexed_runtime_fixture.hpp"
#include <algorithm>
#include <iostream>
#include <stdexcept>
#include <string>

namespace {
using namespace crown;
using io::Json;
namespace cp = planner::comparisons;
namespace cr = runtime::comparisons;

// Execution and wire presentation only. The external oracle evaluates complete
// original assignments and predicates before projecting expected head rows.
cp::Operator operation(const std::string& name) {
  if (name == "equal") return cp::Operator::equal;
  if (name == "not_equal") return cp::Operator::not_equal;
  if (name == "less") return cp::Operator::less;
  if (name == "less_equal") return cp::Operator::less_equal;
  if (name == "greater") return cp::Operator::greater;
  if (name == "greater_equal") return cp::Operator::greater_equal;
  throw std::runtime_error("unknown comparison test operator");
}
cp::Operand operand(const Json& value, const Query& query) {
  if (value.size() != 1) throw std::runtime_error("invalid comparison test operand");
  if (value.contains("value")) return io::read_scalar(value.at("value"));
  const auto name = value.at("var").get<std::string>();
  for (std::size_t i = 0; i < query.variables.size(); ++i)
    if (query.variables[i].name == name) return VariableId{i};
  throw std::runtime_error("unknown comparison test variable");
}
FreeConnexTree tree(const Json& request, const Document& document) {
  if (request.contains("tree"))
    return io::read_tree(request.at("tree").dump(),document.catalog,document.query);
  if (document.query.contradiction) return {};
  const auto choice = planner::minimum_tree(document.catalog,document.query);
  if (choice.status != planner::OracleStatus::proven_minimum || !choice.tree)
    throw std::runtime_error("comparison test CQ has no checked tree");
  return *choice.tree;
}
Json tuples(const cr::TupleVector& input) {
  Relation result;
  for (const auto& tuple : input)
    if (!result.insert(storage::export_row(tuple.values())).second)
      throw std::runtime_error("duplicate native comparison endpoint row");
  return io::write_relation(result);
}
Json metrics(const cr::Metrics& m) {
  return {{"work",m.work},{"producer_work",m.producer_work},{"view_work",m.view_work},
      {"witnesses",m.witnesses},{"predicate_tests",m.predicate_tests},{"projected",m.projected},
      {"duplicates",m.duplicates},{"scalar_fields",m.scalar_fields},{"scalar_bytes",m.scalar_bytes},
      {"row_comparisons",m.row_comparisons},{"outputs",m.outputs},{"added",m.added},
      {"removed",m.removed},{"recomputed",m.recomputed}};
}
Json snapshot(const cr::Runtime& owner) {
  const auto current = owner.snapshot();
  const auto sources = owner.source_snapshot(); Json physical = Json::array();
  for (const auto& relation : sources.tables) physical.push_back(io::write_relation(relation));
  return {{"sequence",owner.sequence()},{"ready",owner.ready()},{"rows",tuples(current.rows)},
      {"source",std::move(physical)},{"has_answer",owner.has_answer()},
      {"predicate_count",current.binding.predicates().size()},
      {"original_account",current.binding.account().statistics().owner == owner.account().statistics().owner}};
}
Json apply(cr::Runtime& owner, const PhysicalSetUpdate& update) {
  try {
    const auto epoch = owner.apply(update);
    return {{"error",nullptr},{"changed",epoch.input.input.physical_changed},
        {"added",tuples(epoch.added)},{"removed",tuples(epoch.removed)},{"metrics",metrics(epoch.metrics)}};
  } catch (const Error& error) { return {{"error",error.code()}}; }
  catch (const resource::MemoryFailure& error) { return {{"error",std::string(error.code())}}; }
}
Json evaluate(const Json& request) {
  const auto document = io::read_document(request.at("document").dump());
  for (const auto& relation : document.initial.tables)
    if (!relation.empty()) throw std::runtime_error("comparison driver starts empty; load via physical events");
  auto options = request.value("indexed",false) ? s04_runtime::options() : PhysicalOptions{};
  if (options.indexed_storage)
    options.indexed_storage->per_table.indices = std::max(options.indexed_storage->per_table.indices,document.query.atoms.size()+2);
  const auto general = planner::lower_tree(document.catalog,document.query,tree(request,document),options);
  const auto before = general.physical_sha256(); std::vector<cp::Predicate> predicates;
  for (const auto& predicate : request.at("predicates"))
    predicates.push_back({operand(predicate.at("left"),document.query),operation(predicate.at("op").get<std::string>()),
        operand(predicate.at("right"),document.query)});
  const auto plan = cp::admit(general,predicates); cr::Runtime owner(plan);
  Json initial = snapshot(owner), trace = Json::array();
  for (const auto& input : request.at("events")) {
    Row values; for (const auto& value : input.at("values")) values.push_back(io::read_scalar(value));
    const auto op = input.at("op").get<std::string>();
    if (op != "insert" && op != "delete") throw std::runtime_error("invalid comparison test source operation");
    const PhysicalSetUpdate update{input.at("sequence").get<std::uint64_t>(),TableId{input.at("table").get<std::size_t>()},
        op == "insert" ? SetOperation::insert : SetOperation::erase,std::move(values)};
    auto event = apply(owner,update);
    trace.push_back({{"event",std::move(event)},{"snapshot",snapshot(owner)}});
  }
  return {{"id",request.at("id")},{"general_unchanged",general.physical_sha256()==before},
      {"original_atoms",plan.general().query().atoms.size()},{"predicates",plan.predicates().size()},
      {"initial",std::move(initial)},{"trace",std::move(trace)}};
}
} // namespace
int main() {
  try {
    for (std::string line; std::getline(std::cin,line);) std::cout << evaluate(Json::parse(line)).dump() << '\n';
    return 0;
  } catch (const std::exception& error) { std::cerr << error.what() << '\n'; return 1; }
}
