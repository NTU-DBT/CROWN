#include "aggregate_integer.hpp"
#include "index_allocation.hpp"
#include <array>
#include <cassert>
#include <iostream>
#include <nlohmann/json.hpp>
#include <optional>
#include <string>

namespace {
using Json = nlohmann::json;
using crown::runtime::aggregate::detail::IntegerSum;

std::string text(const crown::storage::InlineDecimal& value) {
  std::array<char, crown::storage::InlineDecimal::text_capacity> buffer{};
  const auto length = value.render(buffer);
  return {buffer.data(), length};
}

// Observe only public numeric results. The Python side uses unbounded integers
// and exact rational rounding, without inspecting the implementation's words.
Json observe(const IntegerSum& sum, std::uint64_t count, std::uint8_t scale) {
  crown::storage::InlineDecimal total;
  std::optional<crown::storage::InlineDecimal> average;
  std::optional<std::int64_t> integer;
  bool fits = false;
  {
    s04_alloc::Scope no_heap(0);
    total = sum.value();
    if (count) average = sum.average(count, scale);
    fits = sum.fits_int64();
    if (fits) integer = sum.int64_value();
  }
  assert(s04_alloc::calls == 0);
  return {{"sum", text(total)}, {"count", count}, {"fits_int64", fits},
          {"integer", integer ? Json(*integer) : Json(nullptr)},
          {"average", average ? Json(text(*average)) : Json(nullptr)}};
}

Json evaluate(const Json& request) {
  IntegerSum sum;
  std::uint64_t count = 0;
  const auto scale = request.at("scale").get<std::uint8_t>();
  assert(scale <= 18);
  Json trace = Json::array();
  trace.push_back(observe(sum, count, scale));
  for (const auto& operation : request.at("operations")) {
    const auto value = operation.at("value").get<std::int64_t>();
    const auto weight = operation.at("weight").get<std::uint64_t>();
    const bool erase = operation.value("erase", false);
    if (erase) { assert(weight <= count); count -= weight; }
    else { assert(weight <= static_cast<std::uint64_t>(INT64_MAX) - count); count += weight; }
    {
      s04_alloc::Scope no_heap(0);
      sum.replace(value, weight, erase);
    }
    assert(s04_alloc::calls == 0);
    trace.push_back(observe(sum, count, scale));
  }
  return {{"id", request.at("id")}, {"trace", std::move(trace)}};
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
