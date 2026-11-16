#include "selection_independent_fixture.hpp"
#include "indexed_runtime_fixture.hpp"
#include "crown/io/physical.hpp"
#include "crown/runtime/session.hpp"

#include <array>
#include <iostream>

namespace {
using namespace c05_independent;
using namespace crown::runtime;

PhysicalPlan with_options(const PhysicalPlan& basis,const PhysicalOptions& options) {
  return basis.normalized() ? planner::lower_normalized(*basis.normalized(),basis.tree(),options) :
      planner::lower_tree(basis.catalog(),basis.query(),basis.tree(),options);
}
void verify_owner(const planner::CandidateSnapshot& family,const PhysicalPlan& basis,const auto& owner) {
  auto cache=s::PlanCache::create();std::size_t accepted=0,rejected=0;
  for (const auto policy : {s::Policy::height_only,s::Policy::tuple_index_slots}) {
    s::Request request;request.policy=policy;
    for (bool physical : {false,true}) {
      if (!physical && basis.normalized()) continue;
      const s::Source source=physical ? s::Source{s::PhysicalBasis{basis}} : s::Source{s::DirectCQ{basis.options()}};
      const auto first=current::select_current(family,source,owner,request,{},&cache,s::CacheUse::read_write);
      if (first.stop!=s::Stop::complete || !first.selection)
        throw std::runtime_error("indexed live owner selection stopped: "+std::to_string(static_cast<unsigned>(first.stop))+
            " stage="+std::to_string(static_cast<unsigned>(first.stage)));
      const auto& chosen=first.selection->selection();
      check(chosen.plan().options().indexed_storage==basis.options().indexed_storage &&
          chosen.plan().guarantee().storage_backend=="indexed_chained_v1" &&
          chosen.plan().normalized().has_value()==basis.normalized().has_value(),
          "live-owner selection lost its backend limits or normalized source");
      check(first.selection->capture().inputs().plan().physical_sha256()==basis.physical_sha256(),
          "live-owner evidence is detached from the actual indexed plan");
      check(chosen.cache_observation().disposition==s::CacheDisposition::inserted &&
          chosen.effective_policy()==(policy==s::Policy::height_only ? rank::Policy::height_only : rank::Policy::tuple_index_slots),
          "actual indexed cardinality/model policy failed or silently fell back");
      const auto second=current::select_current(family,source,owner,request,{},&cache,s::CacheUse::read_write);
      check(second.stop==s::Stop::complete && second.selection &&
          second.selection->selection().cache_observation().disposition==s::CacheDisposition::hit &&
          second.selection->selection().cache_binding()==chosen.cache_binding(),
          "unchanged actual indexed owner did not reuse its exact cache binding");
      const auto artifact=io::write_physical(second.selection->selection().plan());
      check(artifact.at("schema_version")==2 && io::write_physical(io::read_physical(artifact.dump())).dump()==artifact.dump(),
          "cached actual-owner plan does not replay its indexed artifact exactly");
      ++accepted;
    }
  }
  const std::array<std::size_t storage::IndexedLimits::*,9> components{&storage::IndexedLimits::rows,&storage::IndexedLimits::indices,
      &storage::IndexedLimits::keys,&storage::IndexedLimits::memberships,&storage::IndexedLimits::nodes,&storage::IndexedLimits::directory_slots,
      &storage::IndexedLimits::arena_slots,&storage::IndexedLimits::arena_pins,&storage::IndexedLimits::journal_entries};
  const std::array<std::uint64_t storage::IndexWork::*,5> domains{&storage::IndexWork::structural_steps,&storage::IndexWork::scalar_fields,
      &storage::IndexWork::scalar_bytes,&storage::IndexWork::pointer_slots,&storage::IndexWork::link_actions};
  const auto mismatch=[&](const PhysicalOptions& changed) {
    const auto before=cache.statistics();const s::Source wrong{s::PhysicalBasis{with_options(basis,changed)}};
    s::Request height;height.policy=s::Policy::height_only;
    const auto attempt=current::select_current(family,wrong,owner,height,{},&cache,s::CacheUse::read_write);
    check(attempt.stop==s::Stop::binding_mismatch && !attempt.selection && cache.statistics()==before,
        "actual-owner backend limit mismatch published a selection or changed the cache");
    ++rejected;
  };
  for (auto field : components) { auto changed=basis.options();++(changed.indexed_storage->per_table.*field);mismatch(changed); }
  for (auto field : domains) { auto changed=basis.options();++(changed.indexed_storage->per_operation.*field);mismatch(changed); }
  auto reference=basis.options();reference.indexed_storage.reset();mismatch(reference);
  check(rejected==15 && cache.statistics().hits==accepted && cache.statistics().insertions==accepted,
      "actual-owner selection/binding coverage changed");
}
void owners(const planner::CandidateSnapshot& family,const PhysicalPlan& basis,const Database& database) {
  auto physical=PhysicalRuntime::initialize(basis,database);verify_owner(family,basis,physical);
  DeltaOptions delta;delta.mode=DeltaMode::delta;delta.completion=DeltaCompletion::anchored;
  auto maintained=DeltaRuntime::initialize(basis,database,delta);verify_owner(family,basis,maintained);
  SessionOptions options;options.delta=delta;
  auto session=QuerySession::create_typed(basis,database,io::QueueLimits{},options);session->start();
  verify_owner(family,basis,*session);
}
void direct() {
  const Catalog catalog{1,{{"r",{{"x",ScalarType::int64},{"ignored",ScalarType::string}}}}};
  const Query query{{{"x",ScalarType::int64}},{{"r",TableId{0},{VariableId{0},IgnoredColumn{}}}},{{VariableId{0},"x"}},false};
  const auto family=candidates(catalog,query);const auto member=*family.candidate(0);
  const auto basis=planner::lower_tree(catalog,query,member.tree(),s04_runtime::options());
  const Database database{{Relation{Row{std::int64_t{9'007'199'254'740'993LL},std::string("a")},
      Row{std::int64_t{9'007'199'254'740'993LL},std::string("b")}}}};
  owners(family,basis,database);
}
void normalized() {
  const Catalog catalog{23,{{"r",{{"x",ScalarType::int64},{"y",ScalarType::int64},{"flag",ScalarType::boolean}}}}};
  const auto bound=frontend::bind_sql("SELECT DISTINCT l.x,l.y,q.y AS z,l.x AS again "
      "FROM r l JOIN r q ON l.y=q.x WHERE l.flag IS TRUE",catalog);
  auto normalized=frontend::normalize_sql(std::get<frontend::BoundSql>(bound));
  const auto& program=std::get<frontend::NormalizedSql>(normalized);
  const auto family=candidates(program.core_catalog,program.core);const auto member=*family.candidate(0);
  const auto basis=planner::lower_normalized(program,member.tree(),s04_runtime::options());
  const Database database{{Relation{Row{std::int64_t{1},std::int64_t{7},true},Row{std::int64_t{7},std::int64_t{9},false}}}};
  owners(family,basis,database);
}
}  // namespace
int main() {
  direct();normalized();
  std::cout << "Actual indexed C01/C02/C05 owners: physical/delta/session, direct/normalized,"
      " height/slots policies, exact cache reuse and all14 backend limits plus reference mismatch passed\n";
}
