#include "weighted_fixture.hpp"
#include "crown/io/document.hpp"
#include <iostream>

// Test transport only. All numeric counts are decimal strings so the Python
// reference can compare exact values without a floating-point JSON consumer.
namespace {
using namespace crown;
using namespace crown::weighted_test;
using io::Json;
Json row_json(storage::RowView row) {
  auto result=Json::array();
  for (std::size_t i=0;i<row.size();++i) result.push_back(io::write_scalar_view(row[i]));
  return result;
}
Json state(runtime::WeightedRuntime& runtime) {
  const auto snapshot=runtime.snapshot();Json nodes=Json::array(),messages=Json::array();
  for (const auto& node:snapshot.nodes) {
    Json rows=Json::array();
    for (const auto& entry:node.records) {
      Json children=Json::array();
      for (const auto value:entry.value->children) children.push_back(std::to_string(value.value));
      rows.push_back({{"row",row_json(entry.tuple.values())},{"local",std::to_string(entry.value->local.value)},
          {"subtree",std::to_string(entry.value->subtree.value)},{"children",std::move(children)},
          {"supported",entry.value->supported_children}});
    }
    nodes.push_back({{"id",node.node.value},{"rows",std::move(rows)}});
    for (const auto& entry:node.messages) messages.push_back({{"node",node.node.value},
        {"key",row_json(entry.key.values())},{"count",std::to_string(entry.value.value)}});
  }
  return {{"sequence",runtime.sequence()},{"root_count",std::to_string(snapshot.root.value)},
      {"nodes",std::move(nodes)},{"messages",std::move(messages)}};
}
void execute(const Json& request) {
  const auto fixture=request.at("fixture").get<std::string>();const auto indexed=request.at("indexed").get<bool>();
  auto shape=fixture=="path" ? path(indexed) : fixture=="generalized" ? generalized(indexed) :
      fixture=="fanout" ? fanout(indexed) : unary(indexed,fixture=="nullary",fixture=="boolean");
  w::Options opts;opts.multiplicity_limit=std::stoull(request.value("limit",std::string("18446744073709551615")));
  runtime::WeightedRuntime runtime(std::move(shape),opts);
  Json description=Json::array();
  for (const auto& node:runtime.structural_program().nodes()) {
    Json scope=Json::array(),children=Json::array();
    for (const auto variable:node.scope) scope.push_back(variable.value);
    for (const auto child:node.children) children.push_back(child.value);
    description.push_back({{"kind",node.kind==NodeKind::native ? "native" : "generalized"},
        {"scope",std::move(scope)},{"children",std::move(children)}});
  }
  std::cout<<Json{{"shape",std::move(description)},{"root",runtime.structural_program().tree().root->value}}.dump()<<'\n';
  for (const auto& operation:request.at("updates")) {
    Row row;for (const auto& value:operation.at("row")) row.push_back(io::read_scalar(value));
    std::string code;
    try {
      static_cast<void>(runtime.apply({runtime.sequence()+1,{NodeId{operation.at("node").get<std::size_t>()},
          std::move(row),{std::stoull(operation.at("before").get<std::string>())},
          {std::stoull(operation.at("after").get<std::string>())}}}));
    } catch (const Error& failure) {code=failure.code();}
    auto result=state(runtime);result["error"]=code;std::cout<<result.dump()<<'\n';
  }
}
} // namespace
int main() {
  try {
    for (std::string line;std::getline(std::cin,line);) execute(io::read_json(line));
  } catch (const std::exception& failure) {std::cerr<<failure.what()<<'\n';return 1;}
}
