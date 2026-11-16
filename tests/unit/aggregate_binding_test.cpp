#include "crown/runtime/aggregate.hpp"
#include "crown/api/error.hpp"
#include "index_allocation.hpp"
#include <array>
#include <iostream>
#include <stdexcept>
#include <string>

namespace {
using namespace crown;
namespace fa = frontend;
namespace ag = runtime::aggregate;
constexpr std::uint64_t allowance = 16 * 1024 * 1024;
void check(bool value, const char* message) { if (!value) throw std::runtime_error(message); }
Catalog schema() {
  Catalog c;
  c.tables = {{"r", {{"g", ScalarType::string, true}, {"x", ScalarType::int64, true},
      {"flag", ScalarType::boolean}}}};
  return c;
}
fa::AggregateProgram bind(std::string_view sql, const Catalog& c = schema(), fa::AggregateBindOptions options = {}) {
  auto result = fa::bind_aggregate_sql(sql, c, options);
  if (const auto* error = std::get_if<fa::BindingDiagnostic>(&result))
    throw std::runtime_error(error->phase + ": " + error->diagnostic.code + ": " + error->diagnostic.message);
  return std::get<fa::AggregateProgram>(std::move(result));
}
void rejection(std::string_view sql, std::string_view code, fa::AggregateBindOptions options = {}) {
  const auto result = fa::bind_aggregate_sql(sql, schema(), options);
  const auto* error = std::get_if<fa::BindingDiagnostic>(&result);
  check(error && error->diagnostic.code == code, "aggregate SQL rejection changed");
}
void controller_only(const resource::MemoryAccount& account) {
  account.check_invariants();
  const auto now = account.statistics().current;
  check(now.allocations == 1 && now.requested_bytes == resource::MemoryAccount::control_bytes(),
      "aggregate component retained payload after release");
}

void descriptors() {
  const auto p = bind("SELECT g,COUNT(*) AS n,COUNT(x),SUM(x),AVG(x),COUNT(x) AS again FROM r GROUP BY g");
  check(p && p.has_input() && !p.full_input_group_key() && p.input_types().size() == 3 &&
      p.group_columns().size() == 1 && p.group_columns()[0] == ColumnId{0}, "aggregate input/group descriptors");
  check(p.measures().size() == 1 && p.measures()[0].sum && !p.measures()[0].int64_sum,
      "repeated argument was not shared with sum/count state");
  check(p.outputs().size() == 6 && p.outputs()[1].name == "n" && p.outputs()[5].name == "again",
      "aggregate output order/aliases changed");
  check(p.outputs()[1].type == fa::SqlType{fa::SqlKind::int64, false, {}}, "COUNT result type");
  check(p.outputs()[3].type == fa::SqlType{fa::SqlKind::decimal, true, DecimalSpec{38, 0}}, "SUM(bigint) result type");
  check(p.outputs()[4].type == fa::SqlType{fa::SqlKind::decimal, true, DecimalSpec{38, 18}}, "AVG result type");
  check(std::get<ColumnId>(p.measures()[0].argument) == ColumnId{1}, "aggregate column was not resolved numerically");
  const auto integer = bind("SELECT SUM(1),AVG(1),COUNT(1),COUNT(NULL),SUM(NULL::bigint)", {});
  check(!integer.has_input() && integer.input_types().empty() && integer.group_columns().empty() &&
      integer.full_input_group_key(), "no-FROM aggregate descriptor is not nullary");
  check(integer.measures().size() == 3 && integer.measures()[0].sum && integer.measures()[0].int64_sum,
      "literal sharing/int32 SUM range marker");
  check(integer.outputs()[0].type.kind == fa::SqlKind::int64 && integer.outputs()[0].type.nullable,
      "SUM(integer) must keep its bigint range");
  fa::AggregateBindOptions rounded; rounded.average_scale = 0;
  const auto rounded_program = bind("SELECT AVG(x) FROM r", schema(), rounded);
  check(rounded_program.outputs()[0].type.decimal == DecimalSpec{38, 0},
      "AVG scale was not attached to the declared type");
  check(bind("SELECT COUNT(*) FROM r GROUP BY g,x,flag").full_input_group_key(), "whole-input key alias missing");
  check(!bind("SELECT COUNT(*) FROM r GROUP BY x,g,flag").full_input_group_key(), "permuted key incorrectly aliases input");
  check(p.checked_int32_columns().empty(), "ordinary bigint query acquired an integer guard");
}

// Narrowing belongs to the original column, independently of final measure
// sharing. Preserve the physical bigint group/result while checking every inner
// integer cast, including a COUNT argument widened back to bigint.
void integer_column_casts() {
  const auto p = bind("SELECT x,SUM(x),SUM(x::integer),AVG(x::integer),"
      "COUNT((x::integer)::bigint),SUM((x::integer)::bigint) FROM r GROUP BY x");
  check(p.input_types()[1].kind == fa::SqlKind::int64 && p.outputs()[0].type.kind == fa::SqlKind::int64,
      "integer cast changed physical/group type");
  check(p.checked_int32_columns().size() == 1 && p.checked_int32_columns()[0] == ColumnId{1},
      "nested/repeated integer cast guard was lost or duplicated");
  check(p.measures().size() == 2 && !p.measures()[0].int64_sum && p.measures()[1].int64_sum,
      "raw/narrow/widened aggregate measure sharing changed");
  check(p.outputs()[1].type.kind == fa::SqlKind::decimal && p.outputs()[2].type.kind == fa::SqlKind::int64 &&
      p.outputs()[5].type.kind == fa::SqlKind::decimal, "integer cast result rules changed");
  const Catalog pair_schema{1, {{"r", {{"a", ScalarType::int64, true}, {"b", ScalarType::int64, true}}}}};
  const auto pair = bind("SELECT COUNT(b::integer),COUNT(a::integer),SUM((b::integer)::bigint),SUM(a::integer) FROM r", pair_schema);
  check(pair.checked_int32_columns().size() == 2 && pair.checked_int32_columns()[0] == ColumnId{0} &&
      pair.checked_int32_columns()[1] == ColumnId{1}, "integer guards are not sorted/unique by original column");
  const auto receiver = resource::MemoryAccount::create(allowance);
  std::size_t observed = 0;
  {
    fa::AggregateProgram frozen;
    { s04_alloc::Scope count; frozen = fa::AggregateProgram::freeze(receiver, p); observed = s04_alloc::calls; }
    check(frozen.checked_int32_columns().size() == 1 && frozen.checked_int32_columns()[0] == ColumnId{1} &&
        frozen.work() == p.work(), "foreign freeze lost checked cast metadata");
    const auto allocations = receiver.statistics().successful_allocations;
    const auto shared = fa::AggregateProgram::freeze(receiver, frozen);
    check(shared.checked_int32_columns().data() == frozen.checked_int32_columns().data() &&
        receiver.statistics().successful_allocations == allocations, "same-account guard freeze allocated");
  }
  controller_only(receiver);
  // Sweep the actual foreign freeze, including the new immutable guard backing.
  // A failed import leaves only the receiving account's controller allocation.
  check(observed > 0, "integer guard freeze fixture allocated no metadata");
  for (std::size_t cut = 0; cut <= observed; ++cut) {
    bool failed = false;
    {
      fa::AggregateProgram frozen;
      s04_alloc::Scope deny(static_cast<std::ptrdiff_t>(cut));
      try { frozen = fa::AggregateProgram::freeze(receiver, p); }
      catch (const std::bad_alloc&) { failed = true; }
      check(failed == (cut < observed), "integer guard freeze fault sweep missed an allocation");
    }
    controller_only(receiver);
  }
  fa::AggregateBindOptions options; options.limits.work_limit = p.work();
  check(std::holds_alternative<fa::AggregateProgram>(fa::bind_aggregate_sql(p.source(), schema(), options)),
      "integer guard rejected exact binding work");
  --*options.limits.work_limit;
  rejection(p.source(), "resource_limit", options);
  rejection("SELECT COUNT(x::text) FROM r", "unsupported_cast");
  rejection("SELECT SUM(g::integer) FROM r", "unsupported_cast");
}

void lifetimes_and_caps() {
  const auto account = resource::MemoryAccount::create(allowance);
  {
    std::string query = "SELECT ";
    for (unsigned i = 0; i < 40; ++i) {
      if (i) query += ',';
      query += "COUNT('one retained long literal value') AS a" + std::to_string(i);
    }
    auto c = schema();
    auto result = fa::bind_aggregate_sql_into(account, query, c);
    check(std::holds_alternative<fa::AggregateProgram>(result), "accounted aggregate binding failed");
    const auto p = std::get<fa::AggregateProgram>(std::move(result));
    query.assign(10000, 'z'); c.tables.clear();
    check(p.measures().size() == 1 && p.outputs().size() == 40 && p.outputs()[0].name == "a0" &&
        p.outputs()[39].name == "a39", "SSO output-name views lost their backing");
    const auto literal = std::get<std::optional<storage::ScalarView>>(p.measures()[0].argument);
    check(literal && std::get<std::string_view>(*literal) == "one retained long literal value",
        "aggregate literal did not survive compiler/source destruction");
    const auto limit = p.work();
    fa::AggregateBindOptions options; options.limits.work_limit = limit;
    check(std::holds_alternative<fa::AggregateProgram>(fa::bind_aggregate_sql(p.source(), {}, options)),
        "aggregate compiler rejected exact recorded work");
    options.limits.work_limit = limit - 1;
    const auto stopped = fa::bind_aggregate_sql(p.source(), {}, options);
    check(std::get<fa::BindingDiagnostic>(stopped).diagnostic.code == "resource_limit",
        "aggregate compiler ignored one-under work");
  }
  controller_only(account);
  const auto calibration = resource::MemoryAccount::create(allowance);
  {
    const auto value = fa::bind_aggregate_sql_into(calibration, "SELECT g,SUM(x),AVG(x) FROM r GROUP BY g", schema());
    check(std::holds_alternative<fa::AggregateProgram>(value), "aggregate compiler cap calibration failed");
  }
  const auto peak = calibration.statistics().peak_requested_bytes;
  controller_only(calibration);
  for (const bool exact : {true, false}) {
    const auto receiver = resource::MemoryAccount::create(exact ? peak : peak - 1);
    bool denied = false;
    try {
      const auto value = fa::bind_aggregate_sql_into(receiver, "SELECT g,SUM(x),AVG(x) FROM r GROUP BY g", schema());
      check(std::holds_alternative<fa::AggregateProgram>(value), "bounded compiler returned an unrelated SQL error");
    } catch (const resource::MemoryFailure& error) {
      check(error.fault() == resource::MemoryFault::limit, "wrong aggregate compiler memory fault"); denied = true;
    }
    check(denied != exact, "aggregate compiler exact/one-under receiver boundary");
    controller_only(receiver);
  }
}

void tuple_ownership() {
  const auto account = resource::MemoryAccount::create(allowance);
  {
    std::string source = "a long SQL string with owned storage";
    std::array<ag::Cell, 4> cells{storage::ScalarView{std::int64_t{-7}}, std::nullopt,
        storage::ScalarView{std::string_view(source)}, storage::ScalarView{storage::InlineDecimal::parse("-1.25")}};
    std::size_t observed = 0;
    ag::Tuple held;
    const auto before = account.statistics().successful_allocations;
    { s04_alloc::Scope count; held = ag::Tuple::copy_of(account, cells); observed = s04_alloc::calls; }
    check(observed > 0 && observed == account.statistics().successful_allocations - before,
        "SQL tuple allocated outside its receiving account");
    source.assign(source.size(), 'z');
    cells[2] = storage::ScalarView{std::string_view(source)};
    const auto exported = held.export_values();
    check(exported[0] == ag::SqlValue{Value{std::int64_t{-7}}} && !exported[1] &&
        exported[2] == ag::SqlValue{Value{std::string("a long SQL string with owned storage")}} &&
        exported[3] == ag::SqlValue{Value{Decimal::parse("-1.25")}}, "SQL tuple owns no stable nullable payload");
    for (std::size_t point = 0; point <= observed; ++point) {
      const auto current = account.statistics().current;
      ag::Tuple result; bool failed = false;
      {
        s04_alloc::Scope fault(static_cast<std::ptrdiff_t>(point));
        try { result = ag::Tuple::copy_of(account, cells); }
        catch (const std::bad_alloc&) { failed = true; }
      }
      check(failed == (point < observed), "SQL tuple fault sweep missed an allocation");
      if (failed) check(!result && account.statistics().current == current, "failed SQL tuple leaked/published partial data");
      result = {};
      check(account.statistics().current == current, "SQL tuple release changed retained prior payload");
    }
    const auto empty = ag::Tuple::copy_of(account, {});
    check(empty && empty.size() == 0 && empty.export_values().empty(), "valid nullary SQL tuple was lost");
    const auto copy = held;
    check(copy == held, "immutable SQL tuple copy changed values");
  }
  controller_only(account);
}
void run() {
  descriptors(); integer_column_casts(); lifetimes_and_caps(); tuple_ownership();
  rejection("SELECT COUNT(DISTINCT x) FROM r", "unsupported_distinct_aggregate");
  rejection("SELECT SUM(x) FILTER (WHERE flag) FROM r", "unsupported_sql");
  rejection("SELECT COUNT(*) OVER () FROM r", "unsupported_sql");
  rejection("SELECT COUNT(*) FROM r WHERE flag", "unsupported_sql");
  rejection("SELECT COUNT(*) FROM r,r s", "unsupported_source");
  rejection("SELECT x,COUNT(*) FROM r", "ungrouped_column");
  rejection("SELECT SUM(NULL)", "type_mismatch");
  rejection("SELECT SUM(g) FROM r", "type_mismatch");
  rejection("SELECT COUNT(r.x) FROM r q", "unknown_qualifier");
  fa::AggregateBindOptions options; options.average_scale = 19;
  rejection("SELECT AVG(x) FROM r", "invalid_options", options);
  options = {}; options.limits.work_limit = 0;
  rejection("SELECT COUNT(*) FROM r", "resource_limit", options);
  std::cout << "W04 binding/tuple: resolved shared arguments, types, aliases, source lifetime, exact caps, nullable owned payload and allocation failures passed\n";
}
}  // namespace
int main() {
  try { run(); return 0; }
  catch (const std::exception& error) { std::cerr << error.what() << '\n'; return 1; }
}
