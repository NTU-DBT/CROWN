#include "crown/runtime/star.hpp"
#include "crown/api/error.hpp"
#include "evaluator.hpp"
#include "indexed_runtime_fixture.hpp"
#include "index_allocation.hpp"
#include "star_hindex.hpp"

#include <algorithm>
#include <cstddef>
#include <cstdint>
#include <iostream>
#include <map>
#include <optional>
#include <random>
#include <stdexcept>
#include <string>
#include <utility>
#include <vector>

namespace {
using namespace crown;
namespace st = runtime::star;
using HIndex = st::detail::HIndex;
std::uint64_t checks = 0;
void check(bool value, const char* message) {
  if (!value) throw std::runtime_error(message);
  ++checks;
}
Row row(std::initializer_list<std::int64_t> values) {
  Row result;
  for (const auto value : values) result.emplace_back(value);
  return result;
}
struct Fixture { Catalog catalog; Query query; FreeConnexTree tree; };
Fixture fixture(std::size_t d, std::vector<std::size_t> head,
                std::vector<std::size_t> satellites = {}) {
  Fixture out;
  if (satellites.empty()) for (std::size_t i = 0; i < d; ++i) satellites.push_back(i);
  Table center{"center", {}};
  Atom atom{"central", TableId{0}, {}};
  VariableSet scope;
  for (std::size_t i = 0; i < d; ++i) {
    const auto name = "v" + std::to_string(i);
    center.columns.push_back({name, ScalarType::int64});
    out.query.variables.push_back({name, ScalarType::int64});
    atom.terms.emplace_back(VariableId{i}); scope.insert(VariableId{i});
  }
  out.catalog.tables.push_back(std::move(center)); out.query.atoms.push_back(std::move(atom));
  out.tree.root = NodeId{0};
  out.tree.nodes.push_back({"root", NodeKind::native, std::move(scope), {}, 0, {}});
  for (const auto coordinate : satellites) {
    const auto id = out.catalog.tables.size();
    const auto name = "satellite" + std::to_string(coordinate);
    out.catalog.tables.push_back({name, {{"key", ScalarType::int64}}});
    out.query.atoms.push_back({name, TableId{id}, {VariableId{coordinate}}});
    out.tree.nodes[0].children.push_back(NodeId{id});
    out.tree.nodes.push_back({name, NodeKind::native, {VariableId{coordinate}}, {}, id, {}});
  }
  for (std::size_t i = 0; i < head.size(); ++i)
    out.query.head.push_back({VariableId{head[i]}, "out" + std::to_string(i)});
  return out;
}
PhysicalPlan lower(const Fixture& f, bool indexed) {
  auto options = indexed ? s04_runtime::options() : PhysicalOptions{};
  if (options.indexed_storage)
    options.indexed_storage->per_table.indices = std::max(options.indexed_storage->per_table.indices,
        f.query.atoms.size()+2);
  return planner::lower_tree(f.catalog, f.query, f.tree,options);
}
template<class Action> void refusal(Action action, std::string_view code = {}) {
  bool refused = false;
  try { action(); }
  catch (const Error& e) { refused = true; check(code.empty() || e.code() == code, "unexpected refusal code"); }
  catch (const resource::MemoryFailure&) { refused = true; check(code.empty(), "unexpected memory refusal"); }
  catch (const storage::IndexFailure&) { refused = true; check(code.empty(), "unexpected index refusal"); }
  check(refused, "operation unexpectedly succeeded");
}
Relation results(const st::Runtime& owner, st::CursorMetrics* metrics = nullptr) {
  Relation out;
  auto cursor = owner.results();
  while (auto tuple = cursor.next())
    check(out.insert(storage::export_row(tuple->values())).second, "duplicate projected result escaped");
  if (metrics) *metrics = cursor.metrics();
  return out;
}

// Deliberately slow original-source definition, independent of maintained H,
// histogram, labels, groups and cursor scheduling. Only test/oracle work scans.
std::uint64_t exact_h(const std::map<Value,std::uint64_t>& degrees, std::size_t d) {
  std::uint64_t h = 0;
  for (std::uint64_t r = 1; r <= degrees.size(); ++r) {
    std::uint64_t bound = 1;
    bool fits = true;
    for (std::size_t power = 0; power < d-1; ++power) {
      if (bound > UINT64_MAX / r) { fits = false; break; }
      bound *= r;
    }
    if (!fits) continue;
    std::uint64_t qualifying = 0;
    for (const auto& [key, degree] : degrees) { (void)key; qualifying += degree >= bound; }
    if (qualifying >= r) h = r;
  }
  return h;
}
st::Options bounded_options() {
  st::Options options; options.sources.support.memory_limit_bytes = 32ULL*1024*1024; return options;
}
struct Trial {
  Fixture original;
  planner::star::Plan plan;
  st::Runtime owner;
  reference::Session oracle;
  explicit Trial(Fixture f, bool indexed, st::Options options = bounded_options())
      : original(std::move(f)), plan(planner::star::admit(lower(original,indexed),OccurrenceId{0})),
        owner(plan,options), oracle(original.catalog,original.query,
            Database{std::vector<Relation>(original.catalog.tables.size())}) { verify(); }
  void verify() {
    check(owner.ready(), "star owner retained a private lease");
    check(owner.sequence() == oracle.sequence(), "star sequence differs from original oracle");
    check(owner.source_snapshot().tables == oracle.database().tables, "full original source state differs");
    check(results(owner) == oracle.snapshot(), "star answer differs from original full-state A04 CQ");
    check(owner.has_answer() == !oracle.snapshot().empty(), "star existence differs");
    const auto state = owner.state();
    const auto d = original.query.variables.size();
    check(state.sequence == oracle.sequence() && state.center_rows == oracle.database().tables[0].size(), "star gauges have wrong epoch/population");
    check(state.dimensions.size() == d, "star coordinate gauge width differs");
    for (std::size_t i = 0; i < d; ++i) {
      std::map<Value,std::uint64_t> degrees;
      for (const auto& source : oracle.database().tables[0]) ++degrees[source[i]];
      check(state.dimensions[i].h == exact_h(degrees,d), "generalized H differs from original center degrees");
      check(state.dimensions[i].keys == degrees.size(), "positive center key count differs");
      std::uint64_t heavy = 0;
      for (const auto& [value, degree] : degrees) {
        const auto key = owner.key(i,storage::borrow_scalar(value));
        check(key && key->degree == degree, "coordinate degree differs from original physical center");
        const auto satellite = plan.satellite_tables()[i];
        const bool present = !satellite || oracle.database().tables[satellite->value].contains(Row{value});
        check(key->present == present, "real satellite presence differs");
        heavy += key->heavy;
      }
      check(state.dimensions[i].heavy_keys == heavy, "heavy-key gauge differs from actual labels");
    }
    owner.check_invariants();
  }
  st::Epoch apply(std::size_t table, SetOperation operation, Row values) {
    const PhysicalSetUpdate update{oracle.sequence()+1,TableId{table},operation,std::move(values)};
    const auto actual = owner.apply(update);
    const auto expected = oracle.apply(update);
    check(actual.sequence == expected.sequence && actual.physical_changed == expected.input_changed, "physical source/no-op outcome differs");
    check(actual.source_metrics.aliases_visited == 0 && actual.source_metrics.native_crossings == 0,
        "star production maintained generic original-query occurrence routes");
    verify(); return actual;
  }
};

void admission(bool indexed) {
  const auto f = fixture(3,{2,0,2}); const auto general = lower(f,indexed);
  const auto binding = general.physical_sha256();
  auto admitted = planner::star::admit(general,OccurrenceId{0});
  check(admitted.dimension() == 3 && admitted.distinct_head() == 2 && admitted.head_coordinates().size() == 3 &&
      admitted.head_coordinates()[0] == 2 && admitted.head_coordinates()[1] == 0 && admitted.head_coordinates()[2] == 2,
      "admission lost ordered/repeated head mapping");
  check(admitted.source_only().query().atoms.empty() && admitted.source_only().source_catalog().tables.size() == f.catalog.tables.size(),
      "source-only coordinator lost the complete original catalog");
  check(admitted.general().physical_sha256() == binding && general.physical_sha256() == binding,
      "opt-in admission mutated its genuine general basis");
  auto moved = std::move(admitted);
  check(admitted.dimension() == moved.dimension() && admitted.general().physical_sha256() == binding,
      "plan move invalidated a documented surviving owner");
  refusal([&]{static_cast<void>(planner::star::admit(general,OccurrenceId{1}));},"star_admission");
  planner::star::Limits none; none.work = 0;
  refusal([&]{static_cast<void>(planner::star::admit(general,OccurrenceId{0},none));},"star_work_limit");
  const auto missing_hidden = fixture(3,{1},{0,1});
  refusal([&]{static_cast<void>(planner::star::admit(lower(missing_hidden,indexed),OccurrenceId{0}));},"star_admission");
  auto self_join = fixture(2,{1}); self_join.query.atoms[2].table = TableId{1};
  refusal([&]{static_cast<void>(planner::star::admit(lower(self_join,indexed),OccurrenceId{0}));},"star_admission");
  auto non_unary = fixture(3,{2});
  non_unary.catalog.tables[1].columns.push_back({"extra",ScalarType::int64});
  non_unary.query.atoms[1].terms.emplace_back(VariableId{1});
  non_unary.tree.nodes[1].scope.insert(VariableId{1});
  refusal([&]{static_cast<void>(planner::star::admit(lower(non_unary,indexed),OccurrenceId{0}));},"star_admission");
}

void every_relation(bool indexed) {
  for (const auto& head : std::vector<std::vector<std::size_t>>{{2},{1,2},{0,1,2},{},{2,2},{2,0}}) {
    Trial t(fixture(3,head),indexed);
    for (const auto& source : {row({1,10,100}),row({2,10,100}),row({2,20,200}),row({3,30,300})})
      t.apply(0,SetOperation::insert,source);
    for (const auto key : {1,2}) t.apply(1,SetOperation::insert,row({key}));
    for (const auto key : {10,20}) t.apply(2,SetOperation::insert,row({key}));
    for (const auto key : {100,200}) t.apply(3,SetOperation::insert,row({key}));
    t.apply(0,SetOperation::insert,row({4,40,400}));
    t.apply(1,SetOperation::insert,row({4})); t.apply(2,SetOperation::insert,row({40}));
    t.apply(3,SetOperation::insert,row({400})); t.apply(0,SetOperation::erase,row({1,10,100}));
    t.apply(1,SetOperation::erase,row({2})); t.apply(1,SetOperation::insert,row({3}));
    t.apply(2,SetOperation::insert,row({30})); t.apply(3,SetOperation::insert,row({300}));
    t.apply(2,SetOperation::erase,row({40})); t.apply(3,SetOperation::erase,row({300}));
    t.apply(1,SetOperation::insert,row({2})); t.apply(0,SetOperation::erase,row({2,10,100}));
    const auto duplicate = t.apply(0,SetOperation::insert,row({2,20,200}));
    const auto absent = t.apply(3,SetOperation::erase,row({999}));
    check(!duplicate.physical_changed && !absent.physical_changed &&
        duplicate.maintenance.center_changes == 0 && absent.maintenance.satellite_changes == 0,
        "set no-op mutated maintained star state");
    t.apply(2,SetOperation::insert,row({40})); t.apply(1,SetOperation::erase,row({4}));
    t.apply(2,SetOperation::erase,row({20}));
    check(!t.owner.has_answer(), "last support did not disappear");
  }
}

void cubes(bool indexed) {
  Trial t(fixture(3,{2}),indexed);
  for (std::size_t table = 1; table <= 3; ++table)
    for (const auto value : {1,2,3}) t.apply(table,SetOperation::insert,row({value}));
  for (std::int64_t side = 1; side <= 3; ++side) {
    for (std::int64_t a = 1; a <= side; ++a)
      for (std::int64_t b = 1; b <= side; ++b)
        for (std::int64_t c = 1; c <= side; ++c)
          if (std::max({a,b,c}) == side) t.apply(0,SetOperation::insert,row({a,b,c}));
    for (const auto& dimension : t.owner.state().dimensions)
      check(dimension.h == static_cast<std::uint64_t>(side), "complete cube generalized H is wrong");
  }
  t.apply(0,SetOperation::erase,row({3,3,3}));
  for (const auto& dimension : t.owner.state().dimensions) check(dimension.h == 2,"3-cube boundary did not lower H");
  t.apply(0,SetOperation::insert,row({3,3,3}));
  for (std::int64_t a = 1; a <= 3; ++a)
    for (std::int64_t b = 1; b <= 3; ++b)
      for (std::int64_t c = 1; c <= 3; ++c)
        if (std::max({a,b,c}) == 3) t.apply(0,SetOperation::erase,row({a,b,c}));
  t.apply(0,SetOperation::erase,row({2,2,2}));
  for (const auto& dimension : t.owner.state().dimensions) check(dimension.h == 1,"2-cube boundary did not lower H");
  t.apply(0,SetOperation::insert,row({2,2,2}));
}

void heavy_light(bool indexed) {
  Trial t(fixture(3,{}),indexed);
  t.apply(1,SetOperation::insert,row({7}));
  std::uint64_t relabels = 0, migrated = 0;
  for (std::int64_t i = 1; i <= 128; ++i) {
    t.apply(2,SetOperation::insert,row({i})); t.apply(3,SetOperation::insert,row({i}));
    const auto update = t.apply(0,SetOperation::insert,row({7,i,i}));
    relabels += update.maintenance.key_relabels; migrated += update.maintenance.migrated_rows;
    for (const auto& dimension : t.owner.state().dimensions) check(dimension.h == 1,"one huge degree was substituted for generalized H");
    if (i == 8) check(!t.owner.key(0,storage::ScalarView{std::int64_t{7}})->heavy,
        "key promoted at the inclusive upper hysteresis boundary");
    if (i == 9) check(t.owner.key(0,storage::ScalarView{std::int64_t{7}})->heavy,
        "key failed to promote above the upper hysteresis boundary");
  }
  check(t.owner.key(0,storage::ScalarView{std::int64_t{7}})->heavy,"high-degree key never became heavy");
  check(relabels > 0 && migrated > 0,"classification did not migrate real rows");
  const auto heavy_erase = t.apply(1,SetOperation::erase,row({7}));
  check(heavy_erase.maintenance.center_visits == 0 && heavy_erase.maintenance.group_visits == 1,
      "heavy satellite traversed center facts instead of its one group");
  const auto heavy_insert = t.apply(1,SetOperation::insert,row({7}));
  check(heavy_insert.maintenance.center_visits == 0 && heavy_insert.maintenance.group_visits == 1,
      "heavy satellite reinsertion did not use group index");
  const auto light = t.apply(2,SetOperation::erase,row({8}));
  check(light.maintenance.center_visits == 1,"light satellite failed to use its one-row degree bucket");
  t.apply(2,SetOperation::insert,row({8}));
  std::uint64_t demotions = 0;
  for (std::int64_t i = 128; i > 0; --i) {
    const auto event = t.apply(0,SetOperation::erase,row({7,i,i}));
    demotions += event.maintenance.key_relabels;
    if (i == 3) check(t.owner.key(0,storage::ScalarView{std::int64_t{7}})->heavy,
        "heavy key did not retain its historical label at degree two");
    if (i == 2) check(!t.owner.key(0,storage::ScalarView{std::int64_t{7}})->heavy,
        "heavy key failed to demote below the lower hysteresis boundary");
  }
  check(demotions > 0,"degree decrease never relabeled maintained state");
  const auto satellite_only = t.owner.key(0,storage::ScalarView{std::int64_t{7}});
  check(satellite_only && !satellite_only->degree && satellite_only->present && !satellite_only->heavy,
      "real satellite-only membership was lost when center degree became zero");
  t.apply(1,SetOperation::erase,row({7}));
  check(!t.owner.key(0,storage::ScalarView{std::int64_t{7}}),"absent zero-degree key retained stale metadata");
  for (const auto& dimension : t.owner.state().dimensions) check(dimension.h == 0 && dimension.keys == 0,"empty center retained H/key state");
}

void projected_groups(bool indexed) {
  for (const auto& head : std::vector<std::vector<std::size_t>>{{2},{2,2},{0,1,2},{}}) {
    Trial t(fixture(3,head),indexed);
    t.apply(1,SetOperation::insert,row({7})); t.apply(1,SetOperation::insert,row({8}));
    t.apply(3,SetOperation::insert,row({0}));
    for (std::int64_t i = 1; i <= 16; ++i) {
      t.apply(2,SetOperation::insert,row({i})); t.apply(0,SetOperation::insert,row({7,i,0}));
    }
    t.apply(2,SetOperation::insert,row({999})); t.apply(0,SetOperation::insert,row({8,999,0}));
    st::CursorMetrics metrics; const auto answer = results(t.owner,&metrics);
    if (head == std::vector<std::size_t>{2} || head == std::vector<std::size_t>{2,2}) {
      check(answer.size() == 1 && metrics.candidates == 2 && metrics.duplicates == 1 && metrics.outputs == 1,
          "cross-mask projected witnesses were not deduplicated exactly");
      check(metrics.candidate_quantum == 2,"projected scheduler omitted its actual nonconstant head exponent");
    } else if (head.size() == 3) check(metrics.candidate_quantum == 1,"full-head scheduler quantum was not one");
    t.apply(1,SetOperation::erase,row({7})); t.apply(1,SetOperation::erase,row({8}));
    check(!t.owner.has_answer(),"last cross-partition support survived");
    t.apply(1,SetOperation::insert,row({8})); t.apply(1,SetOperation::insert,row({7}));
    t.apply(0,SetOperation::erase,row({8,999,0})); t.apply(1,SetOperation::erase,row({7}));
    t.apply(0,SetOperation::insert,row({8,999,0})); t.apply(1,SetOperation::insert,row({7}));
  }
}

void lifecycle_and_limits(bool indexed) {
  Trial t(fixture(2,{1,0,1}),indexed);
  t.apply(1,SetOperation::insert,row({7})); t.apply(2,SetOperation::insert,row({8}));
  t.apply(0,SetOperation::insert,row({7,8}));
  const auto next = PhysicalSetUpdate{t.owner.sequence()+1,TableId{0},SetOperation::insert,row({7,9})};
  {
    auto cursor = t.owner.results(); auto output = cursor.next();
    check(output && storage::export_row(output->values()) == row({8,7,8}),"ordered/repeated head changed");
    check(!t.owner.ready(),"last output released the lease before terminal next");
    refusal([&]{static_cast<void>(t.owner.apply(next));});
    cursor.cancel(); check(t.owner.ready(),"cancel retained cursor lease");
  }
  refusal([&]{auto cursor = t.owner.results({0}); static_cast<void>(cursor.next());});
  check(t.owner.ready(),"failed cursor retained its reader lease"); t.verify();
  refusal([&]{static_cast<void>(t.owner.apply({next.sequence+1,next.table,next.operation,next.values}));},"invalid_sequence");
  t.verify();
  std::optional<storage::Tuple> held;
  std::optional<st::Runtime::Cursor> retained;
  resource::MemoryAccount account;
  {
    auto plan = planner::star::admit(lower(fixture(1,{0}),indexed),OccurrenceId{0});
    st::Runtime owner(plan); account = owner.account();
    static_cast<void>(owner.apply({1,TableId{1},SetOperation::insert,row({9007199254740993LL})}));
    static_cast<void>(owner.apply({2,TableId{0},SetOperation::insert,row({9007199254740993LL})}));
    retained.emplace(owner.results()); held = retained->next();
  }
  check(held && held->account_statistics().owner == account.statistics().owner &&
      storage::export_row(held->values()) == row({9007199254740993LL}),"output lost original account/value after owner teardown");
  retained->cancel(); retained.reset(); held.reset(); account.check_invariants();
  st::Options no_work; no_work.work = 0;
  Trial limited(fixture(2,{1}),indexed,no_work);
  refusal([&]{static_cast<void>(limited.owner.apply({1,TableId{0},SetOperation::insert,row({1,2})}));});
  limited.verify();
  // Exhaust the actual original account, then retry the same sequence after
  // releasing the caller-held block. No second allowance may rescue the update.
  const auto original = t.owner.account(); const auto statistics = original.statistics();
  const auto framing = resource::MemoryAccount::allocation_bytes(0,alignof(std::max_align_t));
  const auto room = statistics.limit_bytes-statistics.current.requested_bytes;
  check(room > framing,"memory fixture has no space for a finite-account blocker");
  {
    auto block = original.allocate(static_cast<std::size_t>(room-framing),alignof(std::max_align_t));
    refusal([&]{static_cast<void>(t.owner.apply(next));});
  }
  t.verify(); t.apply(0,SetOperation::insert,row({7,9}));
  const auto schema_plan = planner::star::admit(lower(fixture(2,{1}),indexed),OccurrenceId{0});
  st::Options no_metadata; no_metadata.metadata_work = {};
  refusal([&]{st::Runtime denied(schema_plan,no_metadata);});

  Trial later(fixture(1,{0}),indexed);
  for (const auto value : {1,2}) {
    later.apply(1,SetOperation::insert,row({value})); later.apply(0,SetOperation::insert,row({value}));
  }
  auto short_cursor = later.owner.results({7}); auto first = short_cursor.next();
  check(first.has_value(),"cursor failed before the intended later-next boundary");
  refusal([&]{static_cast<void>(short_cursor.next());},"star_cursor_work_limit");
  check(later.owner.ready() && storage::export_row(first->values()) == row({1}),
      "later cursor refusal lost its lease/output ownership boundary");
  later.verify();
}

// Actual source/view transaction cuts, including an insertion whose temporary
// projection/group is extracted again during one/two-coordinate promotion.
// Every covered new-allocation position must preserve the original CQ epoch;
// disarming failure then retries the SAME owner and sequence successfully.
void allocation_rollback(bool indexed) {
  for (const bool two_promotions : {false,true}) {
    const auto f = two_promotions ? fixture(3,{}) : fixture(2,{0,1});
    const auto plan = planner::star::admit(lower(f,indexed),OccurrenceId{0});
    std::vector<PhysicalSetUpdate> setup;
    const auto append = [&](std::size_t table, Row values) {
      setup.push_back({setup.size()+1,TableId{table},SetOperation::insert,std::move(values)});
    };
    append(1,row({7})); if (two_promotions) append(2,row({8}));
    for (std::int64_t i = 1; i <= (two_promotions ? 9 : 5); ++i) append(two_promotions ? 3 : 2,row({i}));
    for (std::int64_t i = 1; i <= (two_promotions ? 8 : 4); ++i)
      append(0,two_promotions ? row({7,8,i}) : row({7,i}));
    const PhysicalSetUpdate target{setup.size()+1,TableId{0},SetOperation::insert,
        two_promotions ? row({7,8,9}) : row({7,5})};
    reference::Session original(f.catalog,f.query,Database{std::vector<Relation>(f.catalog.tables.size())});
    for (const auto& update : setup) static_cast<void>(original.apply(update));
    const auto before = original.database(); const auto answers = original.snapshot();
    static_cast<void>(original.apply(target)); const auto after = original.database(); const auto next_answers = original.snapshot();
    const auto load = [&](st::Runtime& owner) {
      for (const auto& update : setup) static_cast<void>(owner.apply(update));
    };
    std::size_t allocations;
    {
      st::Runtime control(plan,bounded_options()); load(control);
      s04_alloc::Scope count; static_cast<void>(control.apply(target)); allocations = s04_alloc::calls;
    }
    check(allocations > 10,"allocation discriminator did not enter staged view work");
    std::size_t failures = 0;
    for (std::size_t cut = 0; cut < allocations; ++cut) {
      st::Runtime owner(plan,bounded_options()); load(owner); const auto prior = owner.state();
      bool failed = false;
      {
        s04_alloc::Scope deny(static_cast<std::ptrdiff_t>(cut));
        try { static_cast<void>(owner.apply(target)); }
        catch (const std::bad_alloc&) { failed = true; }
      }
      check(failed,"persistent allocation cut did not reach its covered position"); ++failures;
      const auto actual = owner.state();
      check(owner.ready() && owner.sequence() == setup.size() && owner.source_snapshot().tables == before.tables &&
          results(owner) == answers && actual.groups == prior.groups && actual.live_groups == prior.live_groups,
          "allocation refusal changed the source/view epoch");
      for (std::size_t i = 0; i < prior.dimensions.size(); ++i)
        check(actual.dimensions[i].h == prior.dimensions[i].h && actual.dimensions[i].keys == prior.dimensions[i].keys &&
            actual.dimensions[i].scale == prior.dimensions[i].scale && actual.dimensions[i].heavy_keys == prior.dimensions[i].heavy_keys &&
            actual.dimensions[i].threshold == prior.dimensions[i].threshold,"allocation refusal changed H/labels/scale");
      owner.check_invariants();
      static_cast<void>(owner.apply(target));
      check(owner.source_snapshot().tables == after.tables && results(owner) == next_answers,
          "same-owner retry after allocation refusal differs from original A04");
      owner.check_invariants();
    }
    check(failures == allocations,"allocation cut coverage was incomplete");
    std::cout << "star persistent allocation cuts indexed=" << indexed << " two_promotions=" << two_promotions << " count=" << failures << '\n';
  }
}

void source_constraints_and_independence(bool indexed) {
  auto f = fixture(2,{1});
  f.catalog.tables[1].constraints.push_back(UniqueConstraint{"u",{ColumnId{0}},ConstraintStatus::enforced});
  f.catalog.tables[0].constraints.push_back(ForeignKeyConstraint{"fk",{ColumnId{0}},TableId{1},{ColumnId{0}},ConstraintStatus::enforced});
  Trial t(f,indexed);
  refusal([&]{static_cast<void>(t.owner.apply({1,TableId{0},SetOperation::insert,row({7,8})}));},"constraint_violation"); t.verify();
  t.apply(1,SetOperation::insert,row({7})); t.apply(0,SetOperation::insert,row({7,8}));
  refusal([&]{static_cast<void>(t.owner.apply({3,TableId{1},SetOperation::erase,row({7})}));},"constraint_violation"); t.verify();
  t.apply(0,SetOperation::erase,row({7,8})); t.apply(1,SetOperation::erase,row({7}));
  const auto plan = planner::star::admit(lower(fixture(2,{1}),indexed),OccurrenceId{0});
  st::Runtime first(plan), second(plan);
  check(first.account().statistics().owner != second.account().statistics().owner,"independent owners share a mutable account");
  static_cast<void>(first.apply({1,TableId{0},SetOperation::insert,row({1,2})}));
  check(second.sequence() == 0 && second.source_snapshot().tables[0].empty() && !second.has_answer(),"one query changed another query state");
  if (indexed) {
    auto options = s04_runtime::options(); options.indexed_storage->per_table.rows = 1;
    const auto g = fixture(1,{0});
    st::Runtime capped(planner::star::admit(planner::lower_tree(g.catalog,g.query,g.tree,options),OccurrenceId{0}));
    static_cast<void>(capped.apply({1,TableId{1},SetOperation::insert,row({1})}));
    static_cast<void>(capped.apply({2,TableId{0},SetOperation::insert,row({1})}));
    const auto before = capped.source_snapshot();
    refusal([&]{static_cast<void>(capped.apply({3,TableId{0},SetOperation::insert,row({2})}));});
    check(capped.sequence() == 2 && capped.source_snapshot().tables == before.tables && results(capped) == Relation{row({1})},"source capacity refusal changed prior epoch");
    static_cast<void>(capped.apply({3,TableId{0},SetOperation::erase,row({1})})); capped.check_invariants();
  }
}

void wide_and_unfiltered(bool indexed) {
  Trial free_coordinate(fixture(3,{2},{0,1}),indexed);
  free_coordinate.apply(1,SetOperation::insert,row({1})); free_coordinate.apply(2,SetOperation::insert,row({2}));
  free_coordinate.apply(0,SetOperation::insert,row({1,2,3}));
  check(free_coordinate.owner.key(2,storage::ScalarView{std::int64_t{3}})->present,"satellite-free coordinate was filtered");
  std::vector<std::size_t> head{69,0,69}; Trial wide(fixture(70,head),indexed);
  Row center;
  for (std::size_t i = 0; i < 70; ++i) {
    center.emplace_back(static_cast<std::int64_t>(i));
    wide.apply(i+1,SetOperation::insert,row({static_cast<std::int64_t>(i)}));
  }
  wide.apply(0,SetOperation::insert,std::move(center));
  check(results(wide.owner) == Relation{row({69,0,69})},"star state has an artificial 64-coordinate boundary");
}

void hindex_model() {
  check(HIndex::power(0,0) == 1 && HIndex::power(0,70) == 0 && HIndex::power(1,7000) == 1,
      "exact integer power zero/unit conventions differ");
  check(HIndex::power(2,63) == (std::uint64_t{1}<<63) && !HIndex::power(2,64) &&
      HIndex::power(UINT64_MAX,1) == UINT64_MAX && !HIndex::power(UINT64_MAX,2),"exact power boundary overflow differs");
  for (const auto d : {1U,2U,3U,5U,70U}) {
    const auto account = resource::MemoryAccount::create(8*1024*1024);
    HIndex index(account,d);
    std::vector<std::uint64_t> counts(24);
    std::mt19937 random(0x6803+d);
    for (unsigned step = 0; step < 1500; ++step) {
      const auto slot = random()%counts.size(); const auto before = counts[slot];
      const auto after = before && random()%2 ? before-1 : before+1;
      const auto old_h = index.h(); const auto old_keys = index.keys();
      { auto abandoned = index.prepare(before,after,[]{}); (void)abandoned; }
      check(index.h() == old_h && index.keys() == old_keys,"abandoned H preparation mutated committed state");
      auto pending = index.prepare(before,after,[]{}); counts[slot] = after;
      { s04_alloc::Scope deny(0); pending.commit(); check(s04_alloc::calls == 0,"H publication allocated"); }
      auto retired = std::move(pending); auto moved_from = std::move(pending);
      retired.commit(); moved_from.commit(); // Inactive/moved-from publication is inert.
      std::map<Value,std::uint64_t> model;
      for (std::size_t i = 0; i < counts.size(); ++i) if (counts[i]) model.emplace(Value{static_cast<std::int64_t>(i)},counts[i]);
      check(index.h() == exact_h(model,d) && index.keys() == model.size(),"incremental H differs from independent degree definition");
      index.check_invariants();
    }
  }
}
} // namespace

int main() {
  try {
    hindex_model();
    for (const bool indexed : {false,true}) {
      admission(indexed); every_relation(indexed); cubes(indexed); heavy_light(indexed); projected_groups(indexed);
      lifecycle_and_limits(indexed); source_constraints_and_independence(indexed); wide_and_unfiltered(indexed);
      allocation_rollback(indexed);
    }
    std::cout << "literal star original A04 semantics, generalized H, real heavy/light routes, ownership and refusal checks=" << checks << '\n';
    return 0;
  } catch (const std::exception& error) { std::cerr << error.what() << '\n'; return 1; }
}
