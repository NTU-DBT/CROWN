#include "sql_scalar.hpp"
#include "index_allocation.hpp"
#include <array>
#include <iostream>
#include <nlohmann/json.hpp>
#include <stdexcept>
#include <string>
#include <vector>

namespace {
using Json = nlohmann::json;
using namespace crown;
namespace scalar = frontend::sql_detail;
using Op = frontend::SqlOperator;
constexpr std::pair<std::string_view, Op> operations[] = {
    {"equal",Op::equal}, {"not_equal",Op::not_equal}, {"less",Op::less}, {"less_equal",Op::less_equal},
    {"greater",Op::greater}, {"greater_equal",Op::greater_equal}, {"conjunction",Op::conjunction},
    {"disjunction",Op::disjunction}, {"negation",Op::negation}, {"is_null",Op::is_null},
    {"is_not_null",Op::is_not_null}, {"is_true",Op::is_true}, {"is_not_true",Op::is_not_true},
    {"is_false",Op::is_false}, {"is_not_false",Op::is_not_false}, {"is_unknown",Op::is_unknown},
    {"is_not_unknown",Op::is_not_unknown}, {"identity_cast",Op::identity_cast},
    {"literal_cast",Op::literal_cast}, {"widen_integer",Op::widen_integer}, {"using_value",Op::using_value}};
void check(bool value, const char* message) { if (!value) throw std::runtime_error(message); }
Op operation(std::string_view name) {
  for (const auto& [key, value] : operations) if (name == key) return value;
  throw std::runtime_error("unknown scalar driver opcode");
}
scalar::Cell cell(const Json& value) {
  if (value.is_null()) return {};
  if (value.is_boolean()) return storage::ScalarView{value.get<bool>()};
  if (value.is_number_integer()) return storage::ScalarView{value.get<std::int64_t>()};
  if (value.is_string()) return storage::ScalarView{std::string_view(value.get_ref<const std::string&>())};
  if (value.is_object() && value.contains("date"))
    return scalar::Cell{std::in_place, std::in_place_type<Date>, Date::parse(value.at("date").get<std::string>())};
  if (value.is_object() && value.contains("decimal"))
    return scalar::Cell{std::in_place, std::in_place_type<storage::InlineDecimal>,
        storage::InlineDecimal::parse(value.at("decimal").get<std::string>())};
  throw std::runtime_error("invalid scalar driver input");
}
Json encode(const scalar::Cell& value) {
  if (!value) return nullptr;
  if (const auto* v = std::get_if<std::int64_t>(&*value)) return *v;
  if (const auto* v = std::get_if<bool>(&*value)) return *v;
  if (const auto* v = std::get_if<std::string_view>(&*value)) return std::string(*v);
  if (const auto* v = std::get_if<Date>(&*value)) return {{"date",v->to_string()}};
  const auto& v = std::get<storage::InlineDecimal>(*value);
  std::array<char,storage::InlineDecimal::text_capacity> text{};
  const auto length = v.render(text);
  return {{"decimal",std::string(text.data(),length)}};
}
Json evaluate(const Json& request) {
  std::vector<scalar::Cell> values;
  for (const auto& value : request.at("values")) values.push_back(cell(value));
  std::vector<frontend::ExpressionId> arguments;
  if (request.contains("arguments")) {
    for (const auto& index : request.at("arguments")) arguments.push_back({index.get<std::size_t>()});
  } else for (std::size_t i = 0; i < values.size(); ++i) arguments.push_back({i});
  const storage::IndexWork limit{UINT64_MAX,UINT64_MAX,UINT64_MAX,UINT64_MAX,UINT64_MAX};
  storage::IndexWorkAllowance work(limit,true);
  const auto opcode = operation(request.at("operation").get<std::string>());
  scalar::Cell result; std::size_t allocations = 0;
  {
    // Only native computation is measured. Parsing, owning JSON output and
    // explicit scalar rendering belong to the test's external boundary.
    s04_alloc::Scope deny(0);
    result = scalar::evaluate(opcode,arguments,values,&work); allocations = s04_alloc::calls;
  }
  check(allocations == 0,"native SQL scalar computation allocated");
  const auto& left = work.remaining();
  return {{"id",request.at("id")}, {"value",encode(result)}, {"allocations",allocations},
      {"work",{{"structural_steps",limit.structural_steps-left.structural_steps},
               {"scalar_fields",limit.scalar_fields-left.scalar_fields},
               {"scalar_bytes",limit.scalar_bytes-left.scalar_bytes},
               {"pointer_slots",limit.pointer_slots-left.pointer_slots},
               {"link_actions",limit.link_actions-left.link_actions}}}};
}

template<class Action> void fault(Action action, storage::IndexFault expected) {
  bool caught = false;
  {
    s04_alloc::Scope deny(0);
    try { action(); }
    catch (const storage::IndexFailure& failure) { caught = failure.code() == storage::IndexFailure(expected).code(); }
  }
  check(caught,"scalar contract/work failure changed its fixed fault family");
}
// Verify borrow and charge boundaries independently of SQL result comparisons.
void contracts() {
  const std::string text(256,'x');
  std::array<scalar::Cell,2> values{storage::ScalarView{std::string_view(text)},storage::ScalarView{std::string_view(text)}};
  const std::array<frontend::ExpressionId,2> arguments{{{0},{1}}};
  scalar::Cell result;
  { s04_alloc::Scope deny(0); result = scalar::evaluate(Op::identity_cast,std::span(arguments).first(1),values); }
  check(std::get<std::string_view>(*result).data() == text.data(),"scalar return must borrow its string, not copy/freeze it");
  storage::IndexWorkAllowance exact({.scalar_fields=2,.scalar_bytes=512},true);
  { s04_alloc::Scope deny(0); result = scalar::evaluate(Op::equal,arguments,values,&exact); }
  check(scalar::truth(result) == true && exact.remaining() == storage::IndexWork{},"exact comparison work boundary");
  storage::IndexWorkAllowance denied({.scalar_fields=1,.scalar_bytes=512},true);
  fault([&] { static_cast<void>(scalar::evaluate(Op::equal,arguments,values,&denied)); },storage::IndexFault::work_limit);
  check(denied.remaining().scalar_fields == 0 && denied.remaining().scalar_bytes == 256,
      "comparison must preserve ordered earlier work debits on later exhaustion");
  values[0].reset(); storage::IndexWorkAllowance empty({},true);
  { s04_alloc::Scope deny(0); result = scalar::evaluate(Op::equal,arguments,values,&empty); }
  check(!result && empty.remaining() == storage::IndexWork{},"NULL comparison should not debit scalar payloads");
  values = {storage::ScalarView{false},storage::ScalarView{true}};
  const std::array<frontend::ExpressionId,2> short_circuit{{{0},{99}}};
  storage::IndexWorkAllowance first({.structural_steps=1},true);
  { s04_alloc::Scope deny(0); result = scalar::evaluate(Op::conjunction,short_circuit,values,&first); }
  check(scalar::truth(result) == false && first.remaining() == storage::IndexWork{},"false AND must not read a later slot");
  values[0] = storage::ScalarView{true};
  { s04_alloc::Scope deny(0); result = scalar::evaluate(Op::using_value,short_circuit,values); }
  check(scalar::truth(result) == true,"USING value transfer must read only its left slot");
  fault([&] { static_cast<void>(scalar::evaluate(Op::conjunction,short_circuit,values)); },storage::IndexFault::contract);
  fault([&] { static_cast<void>(scalar::truth(scalar::Cell{storage::ScalarView{std::int64_t{1}}})); },storage::IndexFault::contract);
  values[1] = storage::ScalarView{std::int64_t{1}};
  fault([&] { static_cast<void>(scalar::evaluate(Op::equal,arguments,values)); },storage::IndexFault::contract);
  fault([&] { static_cast<void>(scalar::evaluate(static_cast<Op>(999),{},values)); },storage::IndexFault::contract);
  std::cerr << "W05 scalar: borrowed values, zero heap, fixed contract errors, exact/one-under work and short-circuit debits passed\n";
}
}  // namespace
int main() {
  try {
    contracts();
    for (std::string line; std::getline(std::cin,line);) std::cout << evaluate(Json::parse(line)).dump() << '\n';
    return 0;
  } catch (const std::exception& failure) { std::cerr << failure.what() << '\n'; return 1; }
}
