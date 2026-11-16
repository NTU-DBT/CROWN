#include "indexed_runtime_fixture.hpp"
#include "runtime_probe.hpp"
#include "index_allocation.hpp"
#include "crown/runtime/owner_statistics.hpp"

#include <algorithm>
#include <array>
#include <iostream>
#include <stdexcept>
#include <string_view>

using namespace crown;
using namespace crown::runtime;
namespace stats=crown::runtime::statistics;
namespace {
// Native program metadata must fit before each exact update-boundary test.
// Use real propagation fanout that dominates setup in every work domain.
constexpr std::size_t population=48;
void check(bool value,std::string_view message) { if (!value) throw std::runtime_error(std::string(message)); }
template<class F> void error(std::string_view code,F operation) {
  try { operation(); }
  catch (const Error& failure) { check(failure.code()==code,"wrong runtime rejection code");return; }
  throw std::runtime_error("expected runtime rejection");
}
RuntimeStorageWork observed(const auto& runtime) {
  const auto value=RuntimeTestProbe::index_work(runtime);check(value.has_value(),"actual runtime has no indexed work context");return *value;
}
constexpr std::array<std::uint64_t storage::IndexWork::*,5> domains{
    &storage::IndexWork::structural_steps,&storage::IndexWork::scalar_fields,&storage::IndexWork::scalar_bytes,
    &storage::IndexWork::pointer_slots,&storage::IndexWork::link_actions};
storage::IndexWork generous() { return s04_runtime::options().indexed_storage->per_operation; }
PhysicalPlan plan(storage::IndexWork limit=generous()) {
  const Catalog catalog{1,{{"R",{{"x",ScalarType::string},{"y",ScalarType::int64}}},
      {"S",{{"y",ScalarType::int64}}}}};
  const Query query{{{"x",ScalarType::string},{"y",ScalarType::int64}},
      {{"r",TableId{0},{VariableId{0},VariableId{1}}},{"s",TableId{1},{VariableId{1}}}},{{VariableId{0},"x"}},false};
  const FreeConnexTree tree{NodeId{0},{{"r",NodeKind::native,{VariableId{0},VariableId{1}},{NodeId{1}},0,{}},
      {"s",NodeKind::native,{VariableId{1}},{},1,{}}},{},{}};
  auto options=s04_runtime::options();options.indexed_storage->per_operation=limit;
  return planner::lower_tree(catalog,query,tree,options);
}
Row parent_row(std::size_t value) {
  auto key=std::string("row-")+std::to_string(value)+std::string(96,'x');key.append("\0\xff",2);
  return {std::move(key),std::int64_t{42}};
}
PhysicalSetUpdate crossing() { return {population+1,TableId{1},SetOperation::insert,{std::int64_t{42}}}; }
storage::IndexWork populate(auto& runtime) {
  auto largest=observed(runtime).consumed;
  for (std::size_t i=0;i<population;++i) {
    const auto before=observed(runtime).fresh_operations;
    auto output=runtime.apply({i+1,TableId{0},SetOperation::insert,parent_row(i)});
    const auto work=observed(runtime);
    check(work.fresh_operations==before+1,"one physical input minted more than one storage allowance");
    for (auto field : domains) largest.*field=std::max(largest.*field,work.consumed.*field);
    if constexpr (requires { output.discard(); }) output.discard();
  }
  return largest;
}
struct SavedHandles { std::vector<TupleHandle> source;std::vector<SupportHandle> support; };
SavedHandles save_handles(const PhysicalRuntime& runtime) {
  SavedHandles saved;
  for (std::size_t i=0;i<population;++i) {
    const auto row=parent_row(i);const auto source=runtime.find_source(TableId{0},row);
    const auto support=runtime.find_support(NodeId{0},SupportRole::records,row);
    check(source && support,"literal pre-update source/support record is absent");
    saved.source.push_back(*source);saved.support.push_back(*support);
  }
  return saved;
}
void unchanged(PhysicalRuntime& runtime,const SavedHandles& before,PhysicalStorageStatistics arenas) {
  check(runtime.ready() && runtime.sequence()==population,"failed aggregate work changed publication state");
  // A bulk diagnostic snapshot has its own aggregate cost and can exceed a
  // grant tailored exactly to an update. Check the whole previous epoch using
  // independently bounded point reads, complete cardinalities and metadata.
  const auto counts=runtime.committed_state_gauges();
  check(counts.bases[0].tuples==population && counts.bases[1].tuples==0 && counts.nodes[0].records==population &&
      counts.nodes[0].survivors==0 && counts.nodes[0].projected_parent_keys==0 &&
      counts.nodes[0].visible_factor_assignments.value==0 && counts.nodes[1].records==0 &&
      counts.nodes[1].survivors==0 && counts.nodes[1].projected_parent_keys==0,
      "failed aggregate work changed complete source/support cardinalities");
  for (std::size_t i=0;i<population;++i) {
    const auto source=runtime.get_source(TableId{0},before.source[i]);const auto record=runtime.get_support(before.support[i]);
    const auto expected=parent_row(i);
    check(source && record && source->values()==expected && record->values()==expected,
        "failed aggregate work changed a prior row or stable handle");
    const auto metadata=RuntimeTestProbe::record_metadata(RuntimeTestProbe::support(runtime),before.support[i]);
    check(metadata.member && metadata.satisfied==SatisfiedChildCount{0} && std::ranges::equal(metadata.child_present,std::vector<bool>{false}),
        "failed aggregate work changed prior satisfied-child counts or flags");
  }
  const auto now=runtime.storage_statistics();
  check(now.source.live_records==arenas.source.live_records && now.support.live_records==arenas.support.live_records &&
      now.source.pins==arenas.source.pins && now.support.pins==arenas.support.pins &&
      now.source.retained_records==arenas.source.retained_records && now.support.retained_records==arenas.support.retained_records,
      "failed aggregate work retained leaked rows or pins");
}
void physical_exact_and_one_under() {
  PhysicalRuntime reference(plan());check(observed(reference).fresh_operations==1,"constructor minted per-component grants");
  const auto setup=populate(reference);static_cast<void>(reference.apply(crossing()));
  const auto exact=observed(reference).consumed;
  for (auto field : domains) check(exact.*field>setup.*field,"fanout fixture does not dominate setup in all work domains");
  {
    PhysicalRuntime admitted(plan(exact));populate(admitted);static_cast<void>(admitted.apply(crossing()));
    check(observed(admitted).consumed==exact && admitted.sequence()==population+1 && admitted.has_answer(),
        "exact aggregate runtime grant did not commit the complete crossing");
  }
  for (auto field : domains) {
    auto one_under=exact;--(one_under.*field);PhysicalRuntime limited(plan(one_under));populate(limited);
    const auto before=save_handles(limited);const auto arenas=limited.storage_statistics();const auto mints=observed(limited).fresh_operations;
    error("storage_work_limit",[&] { static_cast<void>(limited.apply(crossing())); });
    check(observed(limited).fresh_operations==mints+1,"failed runtime update refilled a nested grant");
    unchanged(limited,before,arenas);
    auto absent=crossing();absent.operation=SetOperation::erase;static_cast<void>(limited.apply(absent));
    check(limited.sequence()==population+1 && !limited.has_answer(),"owner could not commit a valid retry after budget rollback");
    static_cast<void>(limited.apply({population+2,TableId{0},SetOperation::erase,parent_row(0)}));
    auto retry=crossing();retry.sequence=population+3;static_cast<void>(limited.apply(retry));
    const auto child=limited.find_source(TableId{1},retry.values);
    check(limited.sequence()==population+3 && limited.has_answer() && child && child->tuple.value==1,
        "smaller successful fanout retry failed or consumed a private tentative source identity");
  }
  std::cout << "physical aggregate exact={" << exact.structural_steps << ',' << exact.scalar_fields << ',' << exact.scalar_bytes
      << ',' << exact.pointer_slots << ',' << exact.link_actions << "}; five independent one-under rollbacks passed\n";
}
void delta_and_cursor_retention() {
  DeltaOptions options;options.mode=DeltaMode::delta;options.completion=DeltaCompletion::anchored;
  DeltaRuntime runtime(plan(),options);check(observed(runtime).fresh_operations==1,"delta bootstrap replaced its construction grant");
  populate(runtime);const auto before=observed(runtime).fresh_operations;
  auto pending=runtime.begin(crossing());
  check(observed(runtime).fresh_operations==before+1,"delta begin did not share source/support admission");
  std::size_t steps=0;
  while (pending.step()!=DeltaStep::prepared) {
    check(++steps<10000,"delta step fixture did not terminate");
    check(observed(runtime).fresh_operations==before+1,"resumed delta step minted a fresh allowance");
  }
  std::optional<DeltaRuntime::Epoch> output;
  {
    s04_alloc::Scope no_allocation(0);output.emplace(pending.commit());
    check(!s04_alloc::triggered && s04_alloc::calls==0,"prepared indexed commit allocated");
  }
  check(observed(runtime).fresh_operations==before+1 && runtime.sequence()==population+1,"delta commit replaced its prepaid grant");
  output->discard();output.reset();
  const auto cursor_before=observed(runtime).fresh_operations;auto cursor=runtime.core_results();
  std::size_t rows=0;while (cursor.next()) {
    ++rows;check(observed(runtime).fresh_operations==cursor_before+1,"cursor next refilled its whole-cursor allowance");
  }
  check(rows==population && observed(runtime).fresh_operations==cursor_before+1,"actual indexed cursor lost live rows or refilled at EOF");
  runtime.check_invariants();
  const auto source_before=observed(runtime).fresh_operations;auto rebuilt=runtime.rebuilt();
  check(observed(runtime).fresh_operations==source_before+1 && observed(rebuilt).fresh_operations==1,
      "rebuild did not keep one source-capture grant and one complete target initialization/bootstrap grant");
  rebuilt.check_invariants();
}
void actual_source_capacity() {
  const Catalog catalog{1,{{"r",{{"x",ScalarType::int64},{"ignored",ScalarType::string}}}}};
  const Query query{{{"x",ScalarType::int64}},{{"r",TableId{0},{VariableId{0},IgnoredColumn{}}}},{{VariableId{0},"x"}},false};
  const FreeConnexTree tree{NodeId{0},{{"r",NodeKind::native,{VariableId{0}},{},0,{}}},{},{}};
  auto options=s04_runtime::options();options.indexed_storage->per_table.rows=1;
  const auto compiled=planner::lower_tree(catalog,query,tree,options);PhysicalRuntime runtime(compiled);
  static_cast<void>(runtime.apply({1,TableId{0},SetOperation::insert,{std::int64_t{1},std::string("a")}}));
  error("storage_capacity",[&] { static_cast<void>(runtime.apply({2,TableId{0},SetOperation::insert,{std::int64_t{1},std::string("b")}})); });
  const auto state=runtime.snapshot();
  check(runtime.sequence()==1 && state.physical.tables[0]==Relation{Row{std::int64_t{1},std::string("a")}} &&
      state.derivations[0].size()==1 && state.derivations[0][0].count==1,
      "physical source used an uncapped reference table or failed alias-count rollback");
  SupportRuntime support(compiled);static_cast<void>(support.apply({1,NodeId{0},SetOperation::insert,{std::int64_t{1}}}));
  error("storage_capacity",[&] { static_cast<void>(support.apply({2,NodeId{0},SetOperation::insert,{std::int64_t{2}}})); });
  check(support.sequence()==1 && support.snapshot().nodes[0].records.size()==1,"logical support ignored actual indexed row capacity");
  PhysicalRuntime reference(planner::lower_tree(catalog,query,tree));
  check(!RuntimeTestProbe::index_work(reference),"default reference runtime allocated an indexed work context");
}
void capture_and_large_exact_annotation() {
  PhysicalRuntime runtime(plan());populate(runtime);static_cast<void>(runtime.apply(crossing()));
  stats::OwnerRequest request{{
      {stats::SourceScope{TableId{0}},std::vector<FieldId>{FieldId{1}}},
      {stats::SourceScope{TableId{1}},std::vector<FieldId>{FieldId{0}}},
      {stats::OccurrenceScope{OccurrenceId{0}},{}},
      {stats::NodeScope{NodeId{0},SupportRole::records},std::vector<FieldId>{FieldId{1}}},
      {stats::NodeScope{NodeId{0},SupportRole::survivors},std::vector<FieldId>{FieldId{1}}},
      {stats::NodeScope{NodeId{0},SupportRole::parent_support},{}},
      {stats::NodeScope{NodeId{0},SupportRole::visible},{}},
      {stats::IndexScope{*runtime.plan().edges()[0].reverse_index},{}}}};
  const auto before=observed(runtime).fresh_operations;const auto captured=runtime.capture_statistics(request);
  check(observed(runtime).fresh_operations==before+1 && captured.availability()==stats::Availability::available &&
      captured.components().size()==8,"actual multi-component C01 capture used replacement grants or failed");
  check(captured.components()[0].distribution->ndv==1 && captured.components()[0].distribution->heavy_keys->front().count==population &&
      captured.components()[7].distribution->heavy_keys->front().count==population,"actual source/index degree capture lost exact fanout");
  auto& support=RuntimeTestProbe::support(runtime);constexpr std::uint64_t large=9'007'199'254'740'993ULL;
  check(RuntimeTestProbe::set_projection(support,NodeId{0},false,{},large)==population,"large annotation fixture starts from the wrong count");
  static_cast<void>(runtime.apply({population+2,TableId{0},SetOperation::insert,parent_row(population)}));
  const stats::OwnerRequest key{{{stats::NodeScope{NodeId{0},SupportRole::parent_support},{}}}};
  const auto exact=runtime.capture_statistics(key);
  check(exact.components()[0].distribution->heavy_keys->front().count==large+1 && runtime.has_answer(),
      "actual propagated support annotation lost an integer above2^53 or key membership");
  check(RuntimeTestProbe::set_projection(support,NodeId{0},false,{},population+1)==large+1,"large annotation was not stored exactly");
  runtime.check_invariants();
}
void persistent_allocation_rollback() {
  const PhysicalSetUpdate update{4,TableId{1},SetOperation::insert,{std::int64_t{42}}};
  const auto setup=[](PhysicalRuntime& runtime) {
    for (std::size_t i=0;i<3;++i)
      static_cast<void>(runtime.apply({i+1,TableId{0},SetOperation::insert,parent_row(i)}));
  };
  std::size_t allocations=0;
  {
    PhysicalRuntime baseline(plan());setup(baseline);
    s04_alloc::Scope tracking;static_cast<void>(baseline.apply(update));allocations=s04_alloc::calls;
  }
  check(allocations>20 && allocations<2000,"persistent runtime fault coverage changed unexpectedly");
  for (std::size_t position=0;position<allocations;++position) {
    PhysicalRuntime runtime(plan());setup(runtime);const auto before=runtime.snapshot();const auto arenas=runtime.storage_statistics();
    bool failed=false,preserved=false;std::size_t attempts=0;
    {
      s04_alloc::Scope deny_from(static_cast<std::ptrdiff_t>(position));
      try { static_cast<void>(runtime.apply(update)); }
      catch (const std::bad_alloc&) {
        failed=true;const auto now=runtime.storage_statistics();
        // These metadata reads allocate nothing while denial remains active.
        // Full value/state comparison follows after the guard is released.
        preserved=runtime.ready() && runtime.sequence()==3 && !runtime.has_answer() &&
            now.source.live_records==arenas.source.live_records && now.support.live_records==arenas.support.live_records &&
            now.source.pins==arenas.source.pins && now.support.pins==arenas.support.pins &&
            now.source.retained_records==arenas.source.retained_records && now.support.retained_records==arenas.support.retained_records;
      }
      attempts=s04_alloc::calls;
    }
    check(failed && preserved && attempts==position+1,"persistent allocation failure did not recover without another allocation attempt");
    const auto after=runtime.snapshot();
    check(after.physical.tables==before.physical.tables && after.support.nodes[0].records.size()==3 &&
        after.support.nodes[0].survivors.empty() && after.support.nodes[1].records.empty(),
        "persistent failure changed the previous complete source/support state");
    for (std::size_t i=0;i<before.support.nodes.size();++i)
      for (const auto& old : before.support.nodes[i].records) {
        const auto value=runtime.get_support(old.handle);
        check(value && value->values()==old.tuple.values(),"persistent failure changed an existing stable support handle");
      }
    static_cast<void>(runtime.apply(update));runtime.check_invariants();
    check(runtime.sequence()==4 && runtime.has_answer() && runtime.snapshot().support.nodes[0].survivors.size()==3,
        "successful retry after persistent allocation failure differs from the complete baseline");
  }
  std::cout << "actual runtime persistent allocation positions=" << allocations
      << "; no recovery allocation, complete prior state and stable handles, then retry passed\n";
}
}  // namespace
int main() {
  physical_exact_and_one_under();delta_and_cursor_retention();actual_source_capacity();capture_and_large_exact_annotation();
  persistent_allocation_rollback();
  std::cout << "Actual indexed runtime: shared work, exact/one-under rollback, source/support capacity,"
      " allocation-free commit, resumed delta/cursor/C01 grants and exact annotations above2^53 passed\n";
}
