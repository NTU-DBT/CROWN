#include "weighted_bag_fixture.hpp"
#include "crown/io/document.hpp"
#include <iostream>

namespace {
using namespace crown;
using namespace crown::weighted_test;
using io::Json;

PhysicalPlan shape(const std::string& fixture, bool indexed) {
  if (fixture=="counted") return counted_path(indexed);
  if (fixture=="tail") return counted_path(indexed,true);
  if (fixture=="repeated") return counted_path(indexed,true,true);
  if (fixture=="generalized") return generalized(indexed);
  if (fixture=="disconnected") return disconnected_bag(indexed);
  if (fixture=="path") return path(indexed);
  if (fixture=="deep-hidden") return deep_bag(96,true,indexed);
  if (fixture=="nullary") return unary(indexed,true,true);
  if (fixture=="boolean") return unary(indexed,false,true);
  if (fixture=="true" || fixture=="false") {
    Query query;query.contradiction=fixture=="false";
    return planner::lower_tree(Catalog{},query,FreeConnexTree{},options(indexed));
  }
  return unary(indexed);
}
Json row_json(const auto& values) {
  auto result=Json::array();
  for (std::size_t i=0;i<values.size();++i) result.push_back(io::write_scalar_view(values[i]));
  return result;
}
Json state(runtime::WeightedRuntime& runtime) {
  Json rows=Json::array();auto cursor=runtime.results();
  while (auto row=cursor.next()) rows.push_back({{"row",row_json(row->tuple.values())},
      {"count",std::to_string(row->multiplicity.value)}});
  return {{"sequence",runtime.sequence()},{"rows",std::move(rows)},
      {"total_count",std::to_string(runtime.root_weight().value)},
      {"records_emitted",cursor.metrics().rows_emitted}};
}
void execute(const Json& request) {
  w::Options options;options.multiplicity_limit=std::stoull(request.value("limit",std::string("18446744073709551615")));
  runtime::WeightedRuntime runtime(shape(request.at("fixture").get<std::string>(),request.at("indexed").get<bool>()),options);
  const auto& program=runtime.structural_program();Json nodes=Json::array(),head=Json::array();
  for (const auto& node:program.nodes()) {
    Json scope=Json::array(),children=Json::array();
    for (const auto variable:node.scope) scope.push_back(variable.value);
    for (const auto child:node.children) children.push_back(child.value);
    nodes.push_back({{"kind",node.kind==NodeKind::native?"native":"generalized"},
        {"scope",std::move(scope)},{"children",std::move(children)}});
  }
  for (const auto& output:program.query().head) head.push_back(output.variable.value);
  const auto route=program.route()==PhysicalRoute::tree?"tree":
      program.route()==PhysicalRoute::constant_true?"constant_true":"constant_false";
  std::cout<<Json{{"nodes",std::move(nodes)},{"head",std::move(head)},
      {"root",program.tree().root?Json(program.tree().root->value):Json(nullptr)},{"route",route}}.dump()<<'\n';
  std::cout<<state(runtime).dump()<<'\n';
  for (const auto& update:request.at("updates")) {
    std::string error;
    try {
      Row row;for (const auto& value:update.at("row")) row.push_back(io::read_scalar(value));
      static_cast<void>(runtime.apply({runtime.sequence()+1,{NodeId{update.at("node").get<std::size_t>()},
          std::move(row),{std::stoull(update.at("before").get<std::string>())},
          {std::stoull(update.at("after").get<std::string>())}}}));
    } catch (const Error& failure) {error=failure.code();}
    auto result=state(runtime);result["error"]=error;std::cout<<result.dump()<<'\n';
  }
}
} // namespace
int main() {
  try {
    for (std::string line;std::getline(std::cin,line);) execute(io::read_json(line));
  } catch (const std::exception& failure) {std::cerr<<failure.what()<<'\n';return 1;}
}
