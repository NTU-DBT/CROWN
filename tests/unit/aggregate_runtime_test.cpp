#include "crown/runtime/aggregate.hpp"
#include "crown/api/error.hpp"
#include "weighted_fixture.hpp"
#include "index_allocation.hpp"
#include <array>
#include <iostream>
#include <optional>
#include <stdexcept>
#include <string>

namespace {
using namespace crown;
namespace ag = runtime::aggregate;
using runtime::AggregateRuntime;
constexpr std::uint64_t allowance = 32 * 1024 * 1024;
void check(bool value, const char* message) { if (!value) throw std::runtime_error(message); }
ag::SqlValue n(std::int64_t value) { return Value{value}; }
ag::SqlValue d(std::string_view value) { return Value{Decimal::parse(value)}; }
ag::Row row(std::optional<std::string> group, std::optional<std::int64_t> value) {
  return {group ? ag::SqlValue{Value{*group}} : std::nullopt, value ? n(*value) : std::nullopt, Value{true}};
}
Catalog schema() { return {1, {{"r", {{"g", ScalarType::string, true}, {"x", ScalarType::int64, true},
    {"flag", ScalarType::boolean}}}}}; }
frontend::AggregateProgram bind_program(std::string_view sql, std::uint8_t scale = 18, const Catalog& catalog = schema()) {
  frontend::AggregateBindOptions options; options.average_scale = scale;
  auto result = frontend::bind_aggregate_sql(sql, catalog, options);
  if (const auto* error = std::get_if<frontend::BindingDiagnostic>(&result))
    throw std::runtime_error(error->diagnostic.code + ": " + error->diagnostic.message);
  return std::get<frontend::AggregateProgram>(std::move(result));
}
std::vector<ag::Row> values(const AggregateRuntime& owner) {
  const auto snapshot = owner.snapshot(); std::vector<ag::Row> result;
  for (const auto& group : snapshot.groups) result.push_back(group.values.export_values());
  return result;
}
void controller_only(const resource::MemoryAccount& account) {
  account.check_invariants();
  const auto now = account.statistics().current;
  check(now.allocations == 1 && now.requested_bytes == resource::MemoryAccount::control_bytes(), "aggregate owner leaked payload");
}
template<class Action> void error(Action action, std::string_view code) {
  try { action(); }
  catch (const Error& failure) { check(failure.code() == code, "unexpected aggregate error code"); return; }
  throw std::runtime_error("expected aggregate error: " + std::string(code));
}
ag::Epoch set(AggregateRuntime& owner, const ag::Row& input, std::uint64_t before, std::uint64_t after) {
  return owner.apply({owner.sequence() + 1, input, before, after});
}

// Group presence follows total input weight; NULL arguments and cancellation
// affect sufficient statistics independently of presence or COUNT(*).
void semantics() {
  ag::Options options; options.capture_changes = true;
  AggregateRuntime global(bind_program("SELECT COUNT(*),COUNT(x),SUM(x),AVG(x) FROM r"), options);
  check(values(global) == std::vector<ag::Row>{{n(0), n(0), {}, {}}}, "empty global SQL result");
  const auto positive = row("a", 6), null = row("a", {}), negative = row("a", -6);
  auto change = set(global, positive, 0, 3);
  check(change.changed && change.captured && change.output && change.output->before && change.output->after,
      "global update must replace its existing empty output");
  check(values(global) == std::vector<ag::Row>{{n(3), n(3), d("18"), d("6")}}, "positive multiplicity statistics");
  static_cast<void>(set(global, null, 0, 2));
  check(values(global) == std::vector<ag::Row>{{n(5), n(3), d("18"), d("6")}}, "COUNT(expr) did not skip NULL");
  static_cast<void>(set(global, negative, 0, 3));
  check(values(global) == std::vector<ag::Row>{{n(8), n(6), d("0"), d("0")}}, "zero sum erased a live global group");
  const auto noop = set(global, negative, 3, 3);
  check(!noop.changed && noop.captured && !noop.output && noop.metrics.group_probes == 0, "no-op changed aggregate output");
  static_cast<void>(set(global, positive, 3, 0)); static_cast<void>(set(global, negative, 3, 0));
  check(values(global) == std::vector<ag::Row>{{n(2), n(0), {}, {}}}, "all-NULL live group must have NULL SUM/AVG");
  static_cast<void>(set(global, null, 2, 0)); global.check_invariants();
  check(values(global) == std::vector<ag::Row>{{n(0), n(0), {}, {}}}, "last deletion lost empty global output");

  AggregateRuntime grouped(bind_program("SELECT g,COUNT(*),COUNT(x),SUM(x),AVG(x) FROM r GROUP BY g"), options);
  check(values(grouped).empty(), "empty grouped query emitted a row");
  const auto null_group = row({}, {});
  const auto inserted = set(grouped, null_group, 0, 2);
  check(inserted.output && !inserted.output->before && inserted.output->after &&
      values(grouped) == std::vector<ag::Row>{{{}, n(2), n(0), {}, {}}}, "NULL group/NULL argument semantics");
  const auto removed = set(grouped, null_group, 2, 0);
  check(removed.output && removed.output->before && !removed.output->after && values(grouped).empty(), "vanished group output");
  check(inserted.output->after->export_values() == ag::Row{{}, n(2), n(0), {}, {}}, "old output changed after deletion");
  grouped.check_invariants();

  AggregateRuntime rounded(bind_program("SELECT AVG(x) FROM r", 0), options);
  const auto zero = row("a", 0), one = row("a", 1);
  static_cast<void>(set(rounded, zero, 0, 3));
  const auto hidden = set(rounded, one, 0, 1);
  check(hidden.changed && !hidden.output && values(rounded) == std::vector<ag::Row>{{d("0")}}, "rounded equal AVG emitted a value change");
  static_cast<void>(set(rounded, zero, 3, 1));
  check(values(rounded) == std::vector<ag::Row>{{d("1")}}, "positive half tie did not round away");
  AggregateRuntime negative_tie(bind_program("SELECT AVG(x) FROM r", 0));
  static_cast<void>(set(negative_tie, zero, 0, 1)); static_cast<void>(set(negative_tie, row("a", -1), 0, 1));
  check(values(negative_tie) == std::vector<ag::Row>{{d("-1")}}, "negative half tie did not round away");

  AggregateRuntime singleton(bind_program("SELECT COUNT(*),COUNT(NULL),SUM(1),AVG(1),SUM(NULL::bigint)"));
  check(values(singleton) == std::vector<ag::Row>{{n(1), n(0), n(1), d("1"), {}}}, "no-FROM implicit singleton");
  error([&] { static_cast<void>(set(singleton, {}, 1, 0)); }, "aggregate_input"); singleton.check_invariants();
}

// Public bigint counts and SUM(integer) remain bounded even with output capture
// disabled. SUM(bigint) and AVG keep an exact wider numerator.
void arithmetic_and_admission() {
  AggregateRuntime owner(bind_program("SELECT COUNT(*),COUNT(x),SUM(x),AVG(x) FROM r"));
  const auto input = row("large", INT64_MIN);
  static_cast<void>(set(owner, input, 0, INT64_MAX));
  check(values(owner) == std::vector<ag::Row>{{n(INT64_MAX), n(INT64_MAX),
      d("-85070591730234615856620279821087277056"), d("-9223372036854775808")}}, "large exact count/sum/average");
  const auto before = values(owner); const auto sequence = owner.sequence();
  error([&] { static_cast<void>(set(owner, row("another", 1), 0, 1)); }, "aggregate_overflow");
  check(owner.sequence() == sequence && values(owner) == before, "count overflow partially published");
  owner.check_invariants(); static_cast<void>(set(owner, input, INT64_MAX, 0));
  AggregateRuntime integer(bind_program("SELECT SUM(2147483647) FROM r"));
  const auto small = row("a", 1); constexpr std::uint64_t boundary = 4294967298ULL;
  static_cast<void>(set(integer, small, 0, boundary));
  check(values(integer) == std::vector<ag::Row>{{n(INT64_MAX - 1)}}, "SUM(integer) exact bigint boundary");
  error([&] { static_cast<void>(set(integer, small, boundary, boundary + 1)); }, "aggregate_overflow");
  check(integer.sequence() == 1 && values(integer) == std::vector<ag::Row>{{n(INT64_MAX - 1)}}, "uncaptured SUM overflow published");
  integer.check_invariants();
  AggregateRuntime average(bind_program("SELECT AVG(2147483647) FROM r"));
  static_cast<void>(set(average, small, 0, INT64_MAX));
  check(values(average) == std::vector<ag::Row>{{d("2147483647")}}, "AVG incorrectly used SUM(integer) result range");

  AggregateRuntime checked(bind_program("SELECT COUNT(*) FROM r"));
  const auto current = values(checked);
  error([&] { static_cast<void>(checked.apply({2, small, 0, 1})); }, "invalid_sequence");
  error([&] { static_cast<void>(set(checked, small, 1, 2)); }, "aggregate_weight_mismatch");
  auto wrong = small; wrong[1] = Value{true};
  error([&] { static_cast<void>(set(checked, wrong, 0, 1)); }, "invalid_aggregate_row");
  wrong = small; wrong[2].reset();
  error([&] { static_cast<void>(set(checked, wrong, 0, 1)); }, "invalid_aggregate_row");
  error([&] { static_cast<void>(set(checked, {}, 0, 1)); }, "invalid_aggregate_row");
  check(checked.sequence() == 0 && values(checked) == current, "invalid input changed aggregate state");
  error([&] { static_cast<void>(checked.snapshot({0, {}})); }, "aggregate_result_limit");
  error([&] { static_cast<void>(checked.snapshot({1, 0})); }, "aggregate_work_limit");
  ag::Options invalid; invalid.count_limit = UINT64_MAX;
  error([&] { AggregateRuntime rejected(bind_program("SELECT COUNT(*) FROM r"), invalid); }, "invalid_options");
  error([&] { AggregateRuntime rejected(frontend::AggregateProgram{}); }, "invalid_aggregate_program");
}

void bounded_work_and_hot_path() {
  const auto input = row(std::string(160, 'g'), 7);
  const auto p = bind_program("SELECT g,COUNT(*),SUM(x),AVG(x) FROM r GROUP BY g");
  ag::Options options; options.capture_changes = true; options.work_limit.reset();
  AggregateRuntime measured(p, options); const auto event = set(measured, input, 0, 2);
  const auto work = event.metrics.work;
  for (const bool exact : {true, false}) {
    options.work_limit = exact ? work : work - 1;
    const auto account = resource::MemoryAccount::create(allowance);
    {
      auto owner = AggregateRuntime::create_into(account, p, options); const auto current = account.statistics().current;
      if (exact) { check(set(owner, input, 0, 2).metrics.work == work, "exact aggregate work cap"); }
      else {
        error([&] { static_cast<void>(set(owner, input, 0, 2)); }, "aggregate_work_limit");
        check(owner.sequence() == 0 && account.statistics().current == current && values(owner).empty(), "work exhaustion partially published");
      }
    }
    controller_only(account);
  }
  std::string sql = "SELECT ";
  for (unsigned i = 0; i < 512; ++i) { if (i) sql += ','; sql += "SUM(x) AS a" + std::to_string(i); }
  AggregateRuntime many(bind_program(sql + " FROM r"));
  AggregateRuntime one(bind_program("SELECT SUM(x) FROM r"));
  static_cast<void>(set(many, input, 0, 1)); static_cast<void>(set(one, input, 0, 1));
  ag::Epoch large{}, small{};
  {
    s04_alloc::Scope deny(0);
    large = set(many, input, 1, 2); small = set(one, input, 1, 2);
    check(s04_alloc::calls == 0, "uncaptured existing-row update allocated");
  }
  check(!large.captured && !large.output && large.metrics.output_fields == 0 &&
      large.metrics.work == small.metrics.work && large.metrics.measures == 1, "repeated output aliases increased uncaptured work");
  many.check_invariants();
  std::cout << "W04 runtime: uncaptured existing-row allocations=0, repeated_aliases=512, logical_work=" << large.metrics.work << '\n';
}

// Sweep the allocator's observed successful sites, followed by a success
// sentinel. Every failed attempt must preserve values, epoch and current charge
// and allow the same operation to succeed on the same owner/account afterward.
void allocation_failures() {
  const auto program = bind_program("SELECT g,COUNT(*),SUM(x),AVG(x) FROM r GROUP BY g");
  const auto source_statistics = program.account().statistics();
  const auto input = row(std::string(100, 'q'), 9);
  ag::Options options; options.capture_changes = true;
  std::size_t failures = 0;
  for (const auto& constructor_program : std::array{program,
      bind_program("SELECT COUNT(*),SUM(x),AVG(x) FROM r"),
      bind_program("SELECT COUNT(*),SUM(1),AVG(1)")}) {
    std::size_t construction = 0;
    std::vector<ag::Row> initial;
    {
      const auto account = resource::MemoryAccount::create(allowance);
      std::optional<AggregateRuntime> owner;
      const auto allocations = account.statistics().successful_allocations;
      { s04_alloc::Scope count; owner.emplace(AggregateRuntime::create_into(account, constructor_program, options)); construction = s04_alloc::calls; }
      check(construction == account.statistics().successful_allocations - allocations, "runtime constructor bypassed account");
      initial = values(*owner); owner.reset(); controller_only(account);
    }
    for (std::size_t point = 0; point <= construction; ++point) {
      const auto account = resource::MemoryAccount::create(allowance); std::optional<AggregateRuntime> owner; bool failed = false;
      { s04_alloc::Scope fault(static_cast<std::ptrdiff_t>(point));
        try { owner.emplace(AggregateRuntime::create_into(account, constructor_program, options)); }
        catch (const std::bad_alloc&) { failed = true; }
      }
      check(failed == (point < construction), "constructor fault sweep missed a site");
      if (failed) { controller_only(account); owner.emplace(AggregateRuntime::create_into(account, constructor_program, options)); }
      check(values(*owner) == initial, "failed/retried constructor changed initial SQL output"); owner.reset(); controller_only(account);
    }
    failures += construction;
  }
  for (unsigned mode = 0; mode < 3; ++mode) {
    const std::uint64_t before = mode ? 2 : 0, after = mode == 2 ? 0 : 5;
    std::size_t observed = 0;
    {
      const auto account = resource::MemoryAccount::create(allowance);
      auto owner = AggregateRuntime::create_into(account, program, options);
      if (before) static_cast<void>(set(owner, input, 0, before));
      const auto allocations = account.statistics().successful_allocations; ag::Epoch result{};
      { s04_alloc::Scope count; result = set(owner, input, before, after); observed = s04_alloc::calls; }
      check(observed > 0 && observed == account.statistics().successful_allocations - allocations, "update bypassed receiving account");
    }
    failures += observed;
    for (std::size_t point = 0; point <= observed; ++point) {
      const auto account = resource::MemoryAccount::create(allowance);
      {
        auto owner = AggregateRuntime::create_into(account, program, options);
        if (before) static_cast<void>(set(owner, input, 0, before));
        const auto old = values(owner); const auto sequence = owner.sequence(); const auto charge = account.statistics().current;
        ag::Epoch result{}; bool failed = false;
        { s04_alloc::Scope fault(static_cast<std::ptrdiff_t>(point));
          try { result = set(owner, input, before, after); }
          catch (const std::bad_alloc&) { failed = true; }
        }
        check(failed == (point < observed), "aggregate update fault sweep missed a site");
        if (failed) {
          check(owner.sequence() == sequence && account.statistics().current == charge && values(owner) == old, "allocation failure changed committed group");
          result = set(owner, input, before, after);
        }
        check(owner.sequence() == sequence + 1 && result.changed && result.output, "same-owner retry failed"); owner.check_invariants();
      }
      controller_only(account);
    }
  }
  check(program.account().statistics() == source_statistics, "runtime allocated or charged source compiler metadata");
  std::cout << "W04 runtime: allocation failure positions=" << failures << ", constructor/update retries and sentinels passed\n";
}

// Snapshot construction allocates independently of update publication. Older
// immutable results remain valid across a failed copy and a same-owner retry.
void snapshot_failures() {
  const auto account = resource::MemoryAccount::create(allowance);
  const auto program = bind_program("SELECT g,COUNT(*),SUM(x),AVG(x) FROM r GROUP BY g");
  std::size_t observed = 0;
  {
    auto owner = AggregateRuntime::create_into(account, program);
    const auto input = row(std::string(160, 's'), 3);
    static_cast<void>(set(owner, input, 0, 2));
    const auto held = owner.snapshot(); const auto expected = values(owner);
    const auto sequence = owner.sequence(), allocations = account.statistics().successful_allocations;
    std::optional<ag::Snapshot> result;
    { s04_alloc::Scope count; result.emplace(owner.snapshot()); observed = s04_alloc::calls; }
    check(observed > 0 && observed == account.statistics().successful_allocations - allocations,
        "snapshot bypassed receiving account");
    result.reset(); const auto current = account.statistics().current;
    for (std::size_t point = 0; point <= observed; ++point) {
      bool failed = false;
      { s04_alloc::Scope fault(static_cast<std::ptrdiff_t>(point));
        try { result.emplace(owner.snapshot()); }
        catch (const std::bad_alloc&) { failed = true; }
      }
      check(failed == (point < observed), "snapshot fault sweep missed a site");
      if (failed) {
        check(owner.sequence() == sequence && account.statistics().current == current && values(owner) == expected,
            "failed snapshot changed committed state/charge");
        result.emplace(owner.snapshot());
      }
      check(result->groups[0].values == held.groups[0].values, "snapshot retry or retained output changed");
      result.reset(); check(account.statistics().current == current, "snapshot retained a failed/caller result");
    }
  }
  controller_only(account);
  std::cout << "W04 runtime: snapshot allocation failure positions=" << observed << ", retained output and retries passed\n";
}

void receiver_caps_and_lifetimes() {
  auto program = bind_program("SELECT g,COUNT(*),SUM(x),AVG(x) FROM r GROUP BY g");
  const std::string source_sql(program.source());
  const auto source_account = program.account();
  const auto input = row(std::string(240, 'k'), -11);
  ag::Options options; options.capture_changes = true;
  const auto calibration = resource::MemoryAccount::create(allowance);
  {
    auto owner = AggregateRuntime::create_into(calibration, program, options);
    const auto event = set(owner, input, 0, 3); check(bool(event.output), "cap calibration event missing");
  }
  const auto peak = calibration.statistics().peak_requested_bytes; controller_only(calibration);
  for (const bool exact : {true, false}) {
    const auto account = resource::MemoryAccount::create(exact ? peak : peak - 1);
    {
      auto owner = AggregateRuntime::create_into(account, program, options); const auto current = account.statistics().current;
      bool denied = false;
      try { const auto event = set(owner, input, 0, 3); check(bool(event.output), "bounded update event missing"); }
      catch (const resource::MemoryFailure& failure) { check(failure.fault() == resource::MemoryFault::limit, "wrong receiver cap error"); denied = true; }
      check(denied != exact, "aggregate exact/one-under receiving grant");
      if (denied) check(owner.sequence() == 0 && account.statistics().current == current && values(owner).empty(), "receiver cap failure published state");
    }
    controller_only(account);
  }
  const auto account = resource::MemoryAccount::create(allowance);
  std::optional<ag::Snapshot> held; ag::Epoch event{};
  {
    auto owner = AggregateRuntime::create_into(account, program, options);
    auto mutable_input = input; event = set(owner, mutable_input, 0, 3); held = owner.snapshot();
    mutable_input[0] = Value{std::string(500, 'z')};
    AggregateRuntime moved(std::move(owner));
    error([&] { static_cast<void>(owner.sequence()); }, "invalid_aggregate_runtime");
    static_cast<void>(set(moved, input, 3, 0));
  }
  program = {};
  check(held->program.source() == source_sql && held->groups[0].values.export_values() ==
      ag::Row{input[0], n(3), d("-33"), d("-11")}, "snapshot/source ownership did not survive runtime release");
  check(event.output && event.output->after && event.output->after->export_values() == held->groups[0].values.export_values(),
      "captured value changed after source deletion/destruction");
  event = {}; held.reset(); controller_only(account); controller_only(source_account);
  std::cout << "W04 runtime: receiver_peak_requested_bytes=" << peak << ", exact/one-under passed\n";
}

// Use actual W03 compressed result tuples, retaining each producer's payload
// while apply_weighted borrows it. This is explicit ingestion, not an atomic
// multi-runtime transaction coordinator or an automatic SQL bag adapter.
void weighted_producer() {
  const Catalog catalog{1, {{"r", {{"x", ScalarType::int64}}}}};
  for (const bool indexed : {false, true}) {
    runtime::WeightedRuntime producer(weighted_test::unary(indexed));
    static_cast<void>(producer.apply({1, {NodeId{0}, {Value{std::int64_t{7}}}, {0}, {5}}}));
    AggregateRuntime aggregate(bind_program("SELECT COUNT(*),SUM(x),AVG(x) FROM r", 18, catalog));
    auto cursor = producer.results(); auto item = cursor.next();
    check(item && item->multiplicity.value == 5, "weighted producer did not return compressed bag row");
    static_cast<void>(aggregate.apply_weighted(1, item->tuple.values(), 0, item->multiplicity.value));
    check(!cursor.next() && values(aggregate) == std::vector<ag::Row>{{n(5), d("35"), d("7")}}, "compressed producer aggregate mismatch");
    static_cast<void>(aggregate.apply_weighted(2, item->tuple.values(), 5, 0));
    check(values(aggregate) == std::vector<ag::Row>{{n(0), {}, {}}}, "compressed last-row retraction mismatch");
    aggregate.check_invariants();
  }
}
// Proposed W06-local tests. These test caller-fed logical deltas only; no
// physical source/native/session/recovery integration follows from passing them.
std::array<ag::Cell, 3> nullable_cells(const ag::Row& input) {
  check(input.size() == 3, "batch fixture arity");
  std::array<ag::Cell, 3> result;
  for (std::size_t i = 0; i < result.size(); ++i)
    result[i] = input[i] ? ag::Cell{storage::borrow_scalar(*input[i])} : std::nullopt;
  return result;
}
AggregateRuntime::PreparedBatch prepare(AggregateRuntime& owner, std::span<const ag::RowDelta> deltas) {
  return owner.prepare_batch({owner.sequence() + 1, deltas});
}

void batch_groups_and_empty() {
  ag::Options options; options.capture_changes = true; options.count_limit = 3;
  AggregateRuntime owner(bind_program("SELECT g,COUNT(*),COUNT(x),SUM(x),AVG(x) FROM r GROUP BY g"), options);
  const auto old_a = row("a", 6), old_b = row("b", {}), new_a = row("a", {}), new_b = row("b", 6);
  const auto a = nullable_cells(old_a), b = nullable_cells(old_b), c = nullable_cells(new_a), e = nullable_cells(new_b);
  static_cast<void>(set(owner, old_a, 0, 3)); static_cast<void>(set(owner, old_b, 0, 3));
  const std::array deltas{ag::RowDelta{c, 3, false}, ag::RowDelta{e, 3, false},
      ag::RowDelta{a, 3, true}, ag::RowDelta{b, 3, true}};
  const auto sequence = owner.sequence(); auto pending = prepare(owner, deltas);
  check(owner.sequence() == sequence && pending.preview().sequence == sequence + 1 && pending.preview().output.size() == 2,
      "batch exposed an intermediate sequence/output");
  check(pending.preview().metrics.state_fields_prepared == 2 && pending.preview().metrics.groups_finalized == 2,
      "batch recopied a group for each changed row");
  error([&] { static_cast<void>(owner.snapshot()); }, "aggregate_busy");
  error([&] { static_cast<void>(set(owner, old_a, 3, 2)); }, "aggregate_busy");
  error([&] { owner.check_invariants(); }, "aggregate_busy");
  error([&] { static_cast<void>(prepare(owner, {})); }, "aggregate_busy");
  auto moved = std::move(pending);
  check(!pending.active() && moved.active(), "batch token move did not transfer its lease");
  error([&] { static_cast<void>(pending.preview()); }, "invalid_aggregate_batch");
  std::optional<ag::BatchEpoch> epoch;
  { s04_alloc::Scope deny(0); epoch.emplace(moved.commit()); check(s04_alloc::calls == 0, "batch publication allocated"); }
  check(!moved.active() && epoch->changed && epoch->captured && epoch->output.size() == 2 &&
      owner.sequence() == sequence + 1, "batch did not commit one complete epoch");
  check(values(owner) == std::vector<ag::Row>{{new_a[0], n(3), n(0), {}, {}},
      {new_b[0], n(3), n(3), d("18"), d("6")}}, "group swap/COUNT(NULL) result");
  owner.check_invariants();
  const auto excess_row = row("a", 1); const auto excess = nullable_cells(excess_row);
  const std::array overflow{ag::RowDelta{excess, 1, false}};
  const auto before_overflow = values(owner); const auto old_sequence = owner.sequence();
  error([&] { static_cast<void>(prepare(owner, overflow)); }, "aggregate_overflow");
  check(owner.sequence() == old_sequence && values(owner) == before_overflow, "final batch count overflow published");
  const std::array remove{ag::RowDelta{c, 3, true}, ag::RowDelta{e, 3, true}};
  auto erased = prepare(owner, remove).commit();
  check(erased.output.size() == 2 && erased.metrics.groups_removed == 2 &&
      !erased.output[0].after && !erased.output[1].after && values(owner).empty(), "last grouped deletions");
  auto empty = prepare(owner, {}).commit();
  check(!empty.changed && empty.captured && empty.output.empty() && empty.metrics.group_probes == 0 &&
      empty.sequence == owner.sequence(), "empty batch did not commit an empty net epoch");

  AggregateRuntime global(bind_program("SELECT COUNT(*),COUNT(x),SUM(x),AVG(x) FROM r"), options);
  auto zero = prepare(global, {}).commit();
  check(!zero.changed && zero.output.empty() && values(global) == std::vector<ag::Row>{{n(0), n(0), {}, {}}},
      "empty global batch changed its persistent empty row");
  const std::array add_null{ag::RowDelta{c, 2, false}};
  static_cast<void>(prepare(global, add_null).commit());
  const std::array remove_null{ag::RowDelta{c, 2, true}};
  const auto last = prepare(global, remove_null).commit();
  check(last.output.size() == 1 && last.output[0].after &&
      last.output[0].after->export_values() == ag::Row{n(0), n(0), {}, {}}, "global last deletion lost its empty row");
  const auto null_key_row = row({}, {}); const auto null_key = nullable_cells(null_key_row);
  const std::array add_key{ag::RowDelta{null_key, 2, false}};
  const auto created = prepare(owner, add_key).commit();
  check(created.output.size() == 1 && !created.output[0].key.export_values()[0], "batch NULL grouping key");
  const std::array remove_key{ag::RowDelta{null_key, 2, true}};
  static_cast<void>(prepare(owner, remove_key).commit()); owner.check_invariants();
  AggregateRuntime singleton(bind_program("SELECT COUNT(*)"));
  error([&] { static_cast<void>(prepare(singleton, {})); }, "aggregate_input");
  AggregateRuntime identical(bind_program("SELECT COUNT(*) FROM r GROUP BY g"), options);
  const std::array pair{ag::RowDelta{a, 1, false}, ag::RowDelta{e, 1, false}};
  const auto same_values = prepare(identical, pair).commit();
  check(same_values.output.size() == 2 && *same_values.output[0].after == *same_values.output[1].after &&
      !(same_values.output[0].key == same_values.output[1].key), "equal group outputs lost full group identity");
}

void batch_sum_and_admission() {
  constexpr std::uint64_t boundary = 4294967298ULL;
  const auto positive = row("same", INT32_MAX), negative = row("same", -INT32_MAX);
  const auto plus = nullable_cells(positive), minus = nullable_cells(negative);
  for (const bool capture : {false, true}) {
    ag::Options options; options.capture_changes = capture;
    // Retain the constant-measure boundary independently of varying casts.
    AggregateRuntime owner(bind_program("SELECT SUM(2147483647) FROM r"), options);
    static_cast<void>(set(owner, negative, 0, 1));
    static_cast<void>(set(owner, positive, 0, boundary - 1));
    const auto old = values(owner); const auto sequence = owner.sequence();
    error([&] { static_cast<void>(set(owner, positive, boundary - 1, boundary)); }, "aggregate_overflow");
    check(owner.sequence() == sequence && values(owner) == old, "single-row SUM gate changed");
    const std::array replace{ag::RowDelta{plus, 1, false}, ag::RowDelta{minus, 1, true}};
    const auto result = prepare(owner, replace).commit();
    check(result.changed && result.output.empty() && values(owner) == std::vector<ag::Row>{{n(INT64_MAX - 1)}},
        "constant SUM batch replacement changed its final value");
    owner.check_invariants();
    const auto now = owner.sequence(); const std::array overflow{ag::RowDelta{plus, 1, false}};
    error([&] { static_cast<void>(prepare(owner, overflow)); }, "aggregate_overflow");
    check(owner.sequence() == now && values(owner) == old, "final SUM overflow partially published");
    const std::array huge{ag::RowDelta{plus, UINT64_MAX, false}};
    error([&] { static_cast<void>(prepare(owner, huge)); }, "aggregate_overflow");
    const std::array underflow{ag::RowDelta{plus, UINT64_MAX, true}};
    error([&] { static_cast<void>(prepare(owner, underflow)); }, "aggregate_weight_mismatch");
    const std::array duplicate{ag::RowDelta{plus, 1, true}, ag::RowDelta{plus, 1, true}};
    error([&] { static_cast<void>(prepare(owner, duplicate)); }, "invalid_aggregate_batch");
    const std::array zero{ag::RowDelta{plus, 0, true}};
    error([&] { static_cast<void>(prepare(owner, zero)); }, "invalid_aggregate_batch");
    check(owner.sequence() == now && values(owner) == old, "invalid batch changed aggregate state");
  }
  for (std::uint8_t scale = 0; scale <= 18; ++scale) for (const std::int64_t sign : {-1, 1}) {
    ag::Options options; options.capture_changes = true;
    AggregateRuntime owner(bind_program("SELECT COUNT(*),COUNT(x),AVG(x),SUM(x) FROM r", scale), options);
    const auto zero_row = row("zero", 0), one_row = row("one", sign), null_row = row("null", {});
    const auto zero = nullable_cells(zero_row), one = nullable_cells(one_row), null = nullable_cells(null_row);
    const std::array add{ag::RowDelta{zero, 3, false}, ag::RowDelta{one, 1, false}, ag::RowDelta{null, 2, false}};
    static_cast<void>(prepare(owner, add).commit());
    const std::array remove{ag::RowDelta{zero, 2, true}};
    static_cast<void>(prepare(owner, remove).commit());
    const auto average = sign < 0 ? (scale ? "-0.5" : "-1") : (scale ? "0.5" : "1");
    check(values(owner) == std::vector<ag::Row>{{n(4), n(2), d(average), d(sign < 0 ? "-1" : "1")}},
        "batch NULL count or AVG scale/tie rounding");
    owner.check_invariants();
  }
  ag::Options options; options.capture_changes = true;
  AggregateRuntime rounded(bind_program("SELECT AVG(x) FROM r", 0), options);
  const auto zero_row = row("zero", 0), one_row = row("one", 1); const auto one = nullable_cells(one_row);
  static_cast<void>(set(rounded, zero_row, 0, 3));
  const std::array add_one{ag::RowDelta{one, 1, false}};
  const auto hidden = prepare(rounded, add_one).commit();
  check(hidden.changed && hidden.output.empty(), "rounded-equal batch AVG emitted an event");
}

// Each signed contribution exceeds bigint here, while the consolidated final
// sum is zero. The prepared batch checks the final sum; a single-row update
// and an unbalanced final batch must refuse without changing committed state.
void varying_integer_batches() {
  constexpr std::uint64_t amount = 4294967299ULL;
  const auto positive = row("same", INT32_MAX), negative = row("same", -INT32_MAX);
  const auto plus = nullable_cells(positive), minus = nullable_cells(negative);
  for (const bool capture : {false, true}) {
    ag::Options options; options.capture_changes = capture;
    AggregateRuntime owner(bind_program("SELECT COUNT(*),SUM(x::integer),SUM(x) FROM r"), options);
    error([&] { static_cast<void>(set(owner, positive, 0, amount)); }, "aggregate_overflow");
    check(owner.sequence() == 0, "single overflowing integer contribution published");
    const std::array balanced{ag::RowDelta{plus, amount, false}, ag::RowDelta{minus, amount, false}};
    const auto epoch = prepare(owner, balanced).commit();
    check(epoch.captured == capture && values(owner) == std::vector<ag::Row>{{
        n(static_cast<std::int64_t>(2 * amount)), n(0), d("0")}}, "varying integer final cancellation failed");
    const auto baseline = values(owner); const auto sequence = owner.sequence();
    const std::array unbalanced{ag::RowDelta{minus, amount, true}};
    error([&] { static_cast<void>(prepare(owner, unbalanced)); }, "aggregate_overflow");
    check(owner.sequence() == sequence && values(owner) == baseline, "final integer overflow partially published");
    const std::array erase{ag::RowDelta{plus, amount, true}, ag::RowDelta{minus, amount, true}};
    static_cast<void>(prepare(owner, erase).commit());
    check(values(owner) == std::vector<ag::Row>{{n(0), {}, {}}}, "integer cancellation retraction failed");
    owner.check_invariants();
  }
  // COUNT still evaluates its nested narrowing cast; NULL passes. Bounds are
  // inclusive and physical input remains bigint for raw grouping and SUM.
  AggregateRuntime owner(bind_program("SELECT x,COUNT((x::integer)::bigint),SUM(x::integer),SUM(x) FROM r GROUP BY x"));
  static_cast<void>(set(owner, row("min", INT32_MIN), 0, 1));
  static_cast<void>(set(owner, row("max", INT32_MAX), 0, 1));
  static_cast<void>(set(owner, row("null", {}), 0, 1));
  check(values(owner) == std::vector<ag::Row>{{{}, n(0), {}, {}},
      {n(INT32_MIN), n(1), n(INT32_MIN), d("-2147483648")},
      {n(INT32_MAX), n(1), n(INT32_MAX), d("2147483647")}}, "integer boundaries/NULL/raw grouping changed");
  for (const auto outside : {std::int64_t{INT32_MIN} - 1, std::int64_t{INT32_MAX} + 1}) {
    const auto baseline = values(owner); const auto sequence = owner.sequence();
    error([&] { static_cast<void>(set(owner, row("outside", outside), 0, 1)); }, "aggregate_overflow");
    check(owner.sequence() == sequence && values(owner) == baseline, "integer cast refusal changed state");
  }
  AggregateRuntime count(bind_program("SELECT COUNT((x::integer)::bigint) FROM r"));
  error([&] { static_cast<void>(set(count, row("bad", std::int64_t{INT32_MAX} + 1), 0, 1)); }, "aggregate_overflow");
  check(count.sequence() == 0 && values(count) == std::vector<ag::Row>{{n(0)}}, "COUNT bypassed inner integer cast");
  AggregateRuntime average(bind_program("SELECT AVG(x::integer) FROM r"));
  static_cast<void>(set(average, positive, 0, amount));
  check(values(average) == std::vector<ag::Row>{{d("2147483647")}}, "AVG(integer) incorrectly acquired a bigint sum bound");
}

// Repeated/nested casts add one checkpoint per guarded column, no per-update
// allocation. Identical final measure widths make raw/checked work comparable.
void integer_guard_work() {
  const Catalog catalog{1, {{"r", {{"a", ScalarType::int64, true}, {"b", ScalarType::int64, true}}}}};
  const auto raw = bind_program("SELECT COUNT(b),COUNT(a),SUM(b),AVG(a) FROM r", 18, catalog);
  const auto checked = bind_program("SELECT COUNT((b::integer)::bigint),COUNT(a::integer),"
      "SUM((b::integer)::bigint),AVG(a::integer) FROM r", 18, catalog);
  const ag::Row input{n(INT32_MAX), n(INT32_MIN)};
  AggregateRuntime plain(raw), narrowed(checked);
  static_cast<void>(set(plain, input, 0, 1)); static_cast<void>(set(narrowed, input, 0, 1));
  ag::Epoch old_epoch{}, new_epoch{};
  {
    s04_alloc::Scope deny(0);
    old_epoch = set(plain, input, 1, 2); new_epoch = set(narrowed, input, 1, 2);
    check(s04_alloc::calls == 0, "integer guard existing-row update allocated");
  }
  check(new_epoch.metrics.work == old_epoch.metrics.work + 2 &&
      new_epoch.metrics.measures == old_epoch.metrics.measures && values(plain) == values(narrowed),
      "integer guards cost per occurrence instead of unique column");
  ag::Options options; options.work_limit = new_epoch.metrics.work;
  AggregateRuntime exact(checked, options);
  check(set(exact, input, 0, 2).metrics.work == new_epoch.metrics.work, "integer guard exact work limit changed");
  --*options.work_limit; AggregateRuntime low(checked, options);
  error([&] { static_cast<void>(set(low, input, 0, 2)); }, "aggregate_work_limit");
  check(low.sequence() == 0 && values(low) == std::vector<ag::Row>{{n(0), n(0), {}, {}}},
      "integer guard one-under work failure changed state");
}

void batch_faults_and_work() {
  const auto p = bind_program("SELECT g,COUNT(*),SUM(x),AVG(x) FROM r GROUP BY g");
  const auto source_stats = p.account().statistics();
  const auto old_row = row(std::string(100, 'a'), 7), new_row = row(std::string(120, 'b'), -5), null_row = row("c", {});
  const auto old = nullable_cells(old_row), added = nullable_cells(new_row), null = nullable_cells(null_row);
  const std::array deltas{ag::RowDelta{added, 3, false}, ag::RowDelta{null, 1, false}, ag::RowDelta{old, 2, true}};
  ag::Options options; options.capture_changes = true; options.work_limit.reset();
  std::size_t observed = 0; std::uint64_t work = 0, peak = 0;
  {
    const auto account = resource::MemoryAccount::create(allowance);
    {
      auto owner = AggregateRuntime::create_into(account, p, options); static_cast<void>(set(owner, old_row, 0, 2));
      const auto allocations = account.statistics().successful_allocations;
      std::optional<AggregateRuntime::PreparedBatch> pending;
      { s04_alloc::Scope count; pending.emplace(prepare(owner, deltas)); observed = s04_alloc::calls; }
      check(observed > 0 && observed < 256 && observed == account.statistics().successful_allocations - allocations,
          "batch preparation bypassed its account or exceeded bounded fixture sites");
      work = pending->preview().metrics.work;
      const auto committed = pending->commit(); check(committed.output.size() == 3, "fault fixture output");
    }
    peak = account.statistics().peak_requested_bytes; controller_only(account);
  }
  for (const bool exact : {true, false}) {
    options.work_limit = exact ? work : work - 1;
    const auto account = resource::MemoryAccount::create(allowance);
    {
      auto owner = AggregateRuntime::create_into(account, p, options); static_cast<void>(set(owner, old_row, 0, 2));
      const auto before = values(owner); const auto charge = account.statistics().current;
      if (exact) { const auto result = prepare(owner, deltas).commit(); check(result.metrics.work == work, "batch exact work cap"); }
      else {
        error([&] { static_cast<void>(prepare(owner, deltas)); }, "aggregate_work_limit");
        check(owner.sequence() == 1 && values(owner) == before && account.statistics().current == charge,
            "batch one-under work limit changed state or charge");
        static_cast<void>(prepare(owner, {}).commit());
      }
    }
    controller_only(account);
  }
  options.work_limit.reset();
  for (std::size_t point = 0; point <= observed; ++point) {
    const auto account = resource::MemoryAccount::create(allowance);
    {
      auto owner = AggregateRuntime::create_into(account, p, options); static_cast<void>(set(owner, old_row, 0, 2));
      const auto before = values(owner); const auto charge = account.statistics().current;
      std::optional<AggregateRuntime::PreparedBatch> pending; bool failed = false;
      { s04_alloc::Scope fault(static_cast<std::ptrdiff_t>(point));
        try { pending.emplace(prepare(owner, deltas)); }
        catch (const std::bad_alloc&) { failed = true; }
      }
      check(failed == (point < observed), "batch fault sweep missed a successful allocation site");
      if (failed) {
        check(owner.sequence() == 1 && account.statistics().current == charge && values(owner) == before,
            "failed batch changed state/sequence/charge");
        pending.emplace(prepare(owner, deltas));
      }
      std::optional<ag::BatchEpoch> epoch;
      { s04_alloc::Scope deny(0); epoch.emplace(pending->commit()); check(s04_alloc::calls == 0, "batch commit allocated after seal"); }
      check(owner.sequence() == 2 && epoch->output.size() == 3, "batch fault retry publication"); owner.check_invariants();
    }
    controller_only(account);
  }
  for (const bool exact : {true, false}) {
    const auto account = resource::MemoryAccount::create(exact ? peak : peak - 1);
    {
      auto owner = AggregateRuntime::create_into(account, p, options); static_cast<void>(set(owner, old_row, 0, 2));
      const auto charge = account.statistics().current; bool denied = false;
      try { const auto epoch = prepare(owner, deltas).commit(); check(epoch.output.size() == 3, "receiver cap result"); }
      catch (const resource::MemoryFailure& failure) {
        check(failure.fault() == resource::MemoryFault::limit, "batch receiver denial kind"); denied = true;
      }
      check(denied != exact, "batch exact/one-under receiver cap");
      if (denied) check(owner.sequence() == 1 && account.statistics().current == charge, "receiver denial published batch");
    }
    controller_only(account);
  }
  check(p.account().statistics() == source_stats, "batch charged immutable compiler account");
}

void batch_owner_lifetimes() {
  const auto p = bind_program("SELECT g,COUNT(*),SUM(x) FROM r GROUP BY g");
  const auto account = resource::MemoryAccount::create(allowance);
  std::optional<AggregateRuntime::PreparedBatch> pending;
  {
    auto owner = AggregateRuntime::create_into(account, p, ag::Options{.capture_changes = true});
    auto input = row(std::string(100, 'q'), 9); const auto cells = nullable_cells(input);
    const std::array add{ag::RowDelta{cells, 2, false}};
    pending.emplace(prepare(owner, add));
    input[0] = Value{std::string(400, 'z')};
    AggregateRuntime moved(std::move(owner));
    error([&] { static_cast<void>(owner.sequence()); }, "invalid_aggregate_runtime");
  }
  check(pending->active() && pending->preview().output[0].key.export_values()[0] ==
      ag::SqlValue{Value{std::string(100, 'q')}}, "batch retained borrowed input or lost its owner");
  std::optional<ag::BatchEpoch> result;
  { s04_alloc::Scope deny(0); result.emplace(pending->commit()); check(s04_alloc::calls == 0, "ownerless facade commit allocated"); }
  pending.reset();
  check(result->program.source() == p.source() && result->output[0].after->export_values() ==
      ag::Row{Value{std::string(100, 'q')}, n(2), d("18")}, "committed batch output/schema lost lifetime");
  result.reset(); controller_only(account);
  {
    auto owner = AggregateRuntime::create_into(account, p);
    const auto input = row("discard", 1); const auto cells = nullable_cells(input);
    const std::array add{ag::RowDelta{cells, 1, false}};
    pending.emplace(prepare(owner, add));
  }
  { s04_alloc::Scope deny(0); pending.reset(); check(s04_alloc::calls == 0, "ownerless facade rollback allocated"); }
  controller_only(account);
}

void run() {
  batch_groups_and_empty(); batch_sum_and_admission(); varying_integer_batches(); integer_guard_work();
  batch_faults_and_work(); batch_owner_lifetimes();
  semantics(); arithmetic_and_admission(); bounded_work_and_hot_path(); allocation_failures();
  snapshot_failures(); receiver_caps_and_lifetimes(); weighted_producer();
  std::cout << "W04 runtime: SQL group/global semantics, numeric bounds, ownership, work, faults and weighted ingestion passed\n";
}
}  // namespace
int main() { try { run(); return 0; } catch (const std::exception& failure) { std::cerr << failure.what() << '\n'; return 1; } }
