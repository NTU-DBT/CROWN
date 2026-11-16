#include "selection_independent_fixture.hpp"
#include "crown/io/physical.hpp"

#include <iostream>
#include <set>

namespace {
using namespace c05_independent;

PhysicalOptions options() {
  PhysicalOptions value;storage::IndexedBackendSpec spec;
  spec.per_table={9'007'199'254'740'993ULL,11,13,17,19,23,29,31,37};
  spec.per_operation={9'007'199'254'740'993ULL,41,43,47,53};
  value.indexed_storage=spec;return value;
}
s::Selection select(const p::CandidateSnapshot& family,const s::Source& source,s::PlanCache& cache) {
  s::Request request;request.policy=s::Policy::height_only;
  const auto attempt=s::select(family,source,request,{},&cache,s::CacheUse::read_write);
  if (attempt.stop!=s::Stop::complete || !attempt.selection)
    throw std::runtime_error("backend selection failed: stop="+std::to_string(static_cast<unsigned>(attempt.stop))+
        " stage="+std::to_string(static_cast<unsigned>(attempt.stage)));
  return *attempt.selection;
}
void check_source(const p::CandidateSnapshot& family,const s::Source& source,const PhysicalOptions& expected,
    s::PlanCache& cache,std::set<std::string>& bindings) {
  const auto before=cache.statistics();const auto first=select(family,source,cache);
  check(first.cache_observation().disposition==s::CacheDisposition::inserted && first.cache_binding() &&
      bindings.insert(caller_text(*first.cache_binding())).second,"distinct backend source reused an existing cache record");
  check(first.plan().options().indexed_storage==expected.indexed_storage,
      "selection lowering/cache lost the source backend limits");
  check(first.plan().guarantee().storage_backend==(expected.indexed_storage ? "indexed_chained_v1" : "reference_ordered_v1"),
      "selection result guarantee labels a different backend");
  const auto second=select(family,source,cache);
  check(second.cache_observation().disposition==s::CacheDisposition::hit &&
      second.cache_binding()==first.cache_binding() && second.plan().physical_sha256()==first.plan().physical_sha256() &&
      second.plan().options().indexed_storage==expected.indexed_storage,
      "exact backend source did not retrieve its own immutable compiled plan");
  const auto after=cache.statistics();
  check(after.insertions==before.insertions+1 && after.misses==before.misses+1 && after.hits==before.hits+1 &&
      after.entries==before.entries+1,"backend cache insert/hit accounting disagrees with real operations");
  check(io::write_physical(io::read_physical(io::write_physical(second.plan()).dump())).dump()==io::write_physical(second.plan()).dump(),
      "cached backend plan cannot replay through its advertised physical format");
}
}  // namespace

int main() {
  const Catalog catalog{1,{{"r",{{"x",ScalarType::int64}}}}};
  const Query query{{{"x",ScalarType::int64}},{{"r",TableId{0},{VariableId{0}}}},{{VariableId{0},"x"}},false};
  const auto family=candidates(catalog,query);check(family.candidate_count()==1,"single-input literal family changed");
  const auto member=*family.candidate(0);auto cache=s::PlanCache::create({64,8*1024*1024,32*1024*1024});
  std::set<std::string> bindings;
  const std::array<std::size_t storage::IndexedLimits::*,9> components{&storage::IndexedLimits::rows,&storage::IndexedLimits::indices,
      &storage::IndexedLimits::keys,&storage::IndexedLimits::memberships,&storage::IndexedLimits::nodes,&storage::IndexedLimits::directory_slots,
      &storage::IndexedLimits::arena_slots,&storage::IndexedLimits::arena_pins,&storage::IndexedLimits::journal_entries};
  const std::array<std::uint64_t storage::IndexWork::*,5> domains{&storage::IndexWork::structural_steps,&storage::IndexWork::scalar_fields,
      &storage::IndexWork::scalar_bytes,&storage::IndexWork::pointer_slots,&storage::IndexWork::link_actions};
  for (bool basis : {false,true}) {
    const auto exercise=[&](const PhysicalOptions& value) {
      const s::Source source=basis ? s::Source{s::PhysicalBasis{lower(member,value)}} : s::Source{s::DirectCQ{value}};
      check_source(family,source,value,cache,bindings);
    };
    exercise(PhysicalOptions{});const auto indexed=options();exercise(indexed);
    for (auto field : components) { auto changed=indexed;++(changed.indexed_storage->per_table.*field);exercise(changed); }
    for (auto field : domains) { auto changed=indexed;++(changed.indexed_storage->per_operation.*field);exercise(changed); }
  }
  check(bindings.size()==32 && cache.statistics().entries==32,"backend cache coverage narrowed or evicted a record");
  std::cout << "Backend selection binding: reference/indexed, 14 independent one-unit limit changes, including values above 2^53,"
      " both direct and physical sources,32 distinct insertions and32 exact hits passed\n";
}
