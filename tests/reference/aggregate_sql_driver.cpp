#include "crown/runtime/aggregate.hpp"
#include <array>
#include <iostream>
#include <nlohmann/json.hpp>
#include <stdexcept>
#include <string>

namespace {
using Json = nlohmann::json;
namespace ag = crown::runtime::aggregate;

crown::Catalog schema() {
  crown::Catalog result;
  result.tables = {{"r", {{"g", crown::ScalarType::string, true},
      {"x", crown::ScalarType::int64, true}, {"flag", crown::ScalarType::boolean}}}};
  return result;
}

// Observe public SQL cells only; decimal type identity remains explicit.
Json scalar(const crown::storage::ScalarView& value) {
  if (const auto* integer = std::get_if<std::int64_t>(&value)) return *integer;
  if (const auto* text = std::get_if<std::string_view>(&value)) return std::string(*text);
  if (const auto* boolean = std::get_if<bool>(&value)) return *boolean;
  if (const auto* decimal = std::get_if<crown::storage::InlineDecimal>(&value)) {
    std::array<char, crown::storage::InlineDecimal::text_capacity> buffer{};
    const auto length = decimal->render(buffer);
    return {{"decimal", std::string(buffer.data(), length)}};
  }
  throw std::runtime_error("unexpected oracle scalar type");
}
Json tuple(const ag::Tuple& value) {
  Json result = Json::array();
  for (const auto& cell : value.view()) result.push_back(cell ? scalar(*cell) : Json(nullptr));
  return result;
}
Json snapshot(const crown::runtime::AggregateRuntime& runtime) {
  const auto source = runtime.snapshot();
  Json groups = Json::array();
  for (const auto& group : source.groups)
    groups.push_back({{"key", tuple(group.key)}, {"values", tuple(group.values)}});
  return {{"sequence", source.sequence}, {"groups", std::move(groups)}};
}
ag::Row row(const Json& values) {
  ag::Row result;
  for (const auto& cell : values) {
    if (cell.is_null()) result.emplace_back();
    else if (cell.is_boolean()) result.emplace_back(crown::Value{cell.get<bool>()});
    else if (cell.is_number_integer()) result.emplace_back(crown::Value{cell.get<std::int64_t>()});
    else if (cell.is_string()) result.emplace_back(crown::Value{cell.get<std::string>()});
    else throw std::runtime_error("unexpected oracle input type");
  }
  return result;
}
Json evaluate(const Json& request) {
  crown::frontend::AggregateBindOptions binding;
  binding.average_scale = request.value("average_scale", std::uint8_t{18});
  auto bound = crown::frontend::bind_aggregate_sql(request.at("sql").get<std::string>(), schema(), binding);
  if (const auto* error = std::get_if<crown::frontend::BindingDiagnostic>(&bound))
    throw std::runtime_error(error->diagnostic.code + ": " + error->diagnostic.message);
  ag::Options options; options.capture_changes = true;
  crown::runtime::AggregateRuntime runtime(std::get<crown::frontend::AggregateProgram>(std::move(bound)), options);
  Json trace = Json::array(), epochs = Json::array();
  runtime.check_invariants();
  trace.push_back(snapshot(runtime));
  std::uint64_t sequence = 0;
  for (const auto& operation : request.at("updates")) {
    const auto values = row(operation.at("values"));
    const auto epoch = runtime.apply({++sequence, values,
        operation.at("before").get<std::uint64_t>(), operation.at("after").get<std::uint64_t>()});
    Json change = nullptr;
    if (epoch.output) change = {{"key", tuple(epoch.output->key)},
        {"before", epoch.output->before ? tuple(*epoch.output->before) : Json(nullptr)},
        {"after", epoch.output->after ? tuple(*epoch.output->after) : Json(nullptr)}};
    const auto& m = epoch.metrics;
    epochs.push_back({{"sequence", epoch.sequence}, {"changed", epoch.changed}, {"captured", epoch.captured},
        {"output", std::move(change)}, {"metrics", {{"work", m.work}, {"input_fields", m.input_fields},
        {"input_bytes", m.input_bytes}, {"row_probes", m.row_probes}, {"group_probes", m.group_probes},
        {"measures", m.measures}, {"output_fields", m.output_fields},
        {"groups_created", m.groups_created}, {"groups_removed", m.groups_removed}}}});
    // This explicit test diagnostic is outside the measured update operation.
    runtime.check_invariants();
    trace.push_back(snapshot(runtime));
  }
  return {{"id", request.at("id")}, {"trace", std::move(trace)}, {"epochs", std::move(epochs)}};
}
}  // namespace

int main() {
  try {
    for (std::string line; std::getline(std::cin, line);)
      std::cout << evaluate(Json::parse(line)).dump() << '\n';
    return 0;
  } catch (const std::exception& error) {
    std::cerr << error.what() << '\n';
    return 1;
  }
}
