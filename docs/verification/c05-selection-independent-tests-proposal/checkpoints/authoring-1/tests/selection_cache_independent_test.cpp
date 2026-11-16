#include "selection_independent_fixture.hpp"

#include <iostream>

namespace {
using namespace c05_independent;
s::Selection choose(const p::CandidateSnapshot& set,const s::Source& source,const s::Request& request,
                    s::PlanCache& cache,s::CacheUse use=s::CacheUse::read_write,
                    const std::optional<rank::Evidence>& facts={}) {
  const auto attempt=s::select(set,source,request,facts,&cache,use);
  return complete(attempt);
}
s::Request key_request(unsigned number) {
  auto result=height();result.limits.aggregate.score_bits=500U+number;return result;
}
void fifo_read_only_and_lifetime(const BooleanFixture& f) {
  const s::Source source{s::DirectCQ{}};
  auto cache=s::PlanCache::create({2,8*1024*1024,32*1024*1024});
  const auto a=choose(f.all,source,key_request(0),cache);
  const auto b=choose(f.all,source,key_request(1),cache);
  check(a.cache_observation().disposition==s::CacheDisposition::inserted &&
        b.cache_observation().disposition==s::CacheDisposition::inserted &&
        a.cache_binding() && b.cache_binding() && *a.cache_binding()!=*b.cache_binding(),
        "cold entries did not bind exact requested score-bit ceilings");
  const auto a_hit=choose(f.all,source,key_request(0),cache);
  check(a_hit.cache_observation().disposition==s::CacheDisposition::hit &&
        a_hit.cache_observation().compared_bytes>0 && cache.statistics().hits==1,
        "warm exact-key lookup was not a charged hit");
  const auto c=choose(f.all,source,key_request(2),cache);
  check(c.cache_observation().disposition==s::CacheDisposition::inserted &&
        cache.statistics().entries==2 && cache.statistics().evictions==1 &&
        cache.statistics().insertions==3 && cache.statistics().misses==3,
        "FIFO cold install counters or capacity differ");
  const auto absent_a=choose(f.all,source,key_request(0),cache,s::CacheUse::read_only);
  check(absent_a.cache_observation().disposition==s::CacheDisposition::miss_read_only &&
        cache.statistics().insertions==3 && cache.statistics().entries==2,
        "hit reordered FIFO or read-only miss installed an entry");
  check(choose(f.all,source,key_request(1),cache,s::CacheUse::read_only).cache_observation().disposition==s::CacheDisposition::hit &&
        choose(f.all,source,key_request(2),cache,s::CacheUse::read_only).cache_observation().disposition==s::CacheDisposition::hit,
        "FIFO retained the wrong entries");
  check(cache.statistics().hits==3 && cache.statistics().misses==4 && cache.statistics().evictions==1,
        "successful-only FIFO hit/miss counters differ");
  const auto retained_statistics=cache.statistics();
  auto moved=std::move(cache);
  check(!cache.valid() && moved.valid() && moved.statistics()==retained_statistics,
        "cache move lost exact entries/counters or left its facade valid");
  moved.clear();
  check(moved.statistics()==s::CacheStatistics{},"clear did not reset entries and counters");
  auto owner=r::PhysicalRuntime::initialize(a.plan(),f.initial);
  check(answers(owner)==Relation{Row{}} && a.snapshot().candidate_count()==3 && a.selected().original_proof().height()==2,
        "old selected artifact/proof did not survive eviction/move/clear");
  s::Selection detached=[&]{auto temporary=s::PlanCache::create();return choose(f.all,source,height(),temporary);}();
  auto detached_owner=r::PhysicalRuntime::initialize(detached.plan(),f.initial);
  check(answers(detached_owner)==Relation{Row{}},"cache destruction invalidated retained result");
}

void capacity_exact_and_transactional(const BooleanFixture& f) {
  const s::Source source{s::DirectCQ{}};
  auto unlimited=s::PlanCache::create();
  const auto seed=choose(f.all,source,height(),unlimited);
  const auto size=unlimited.statistics();
  check(size.entries==1 && size.key_bytes==seed.cache_binding()->size() && size.plan_payload_bytes>0,
        "cache did not report exact owned key and modeled plan payload");
  const s::CacheLimits exact{1,size.key_bytes,size.plan_payload_bytes};
  auto fitted=s::PlanCache::create(exact);
  check(choose(f.all,source,height(),fitted).cache_observation().disposition==s::CacheDisposition::inserted,
        "entry did not fit exact cache capacities");
  for (const bool key_limit:{false,true}) {
    auto limits=exact;
    if (key_limit) --limits.key_bytes;else --limits.plan_payload_bytes;
    auto short_cache=s::PlanCache::create(limits);
    const auto before=short_cache.statistics();
    const auto result=s::select(f.all,source,height(),{},&short_cache,s::CacheUse::read_write);
    check(result.stop==s::Stop::resource_limit && !result.selection && short_cache.statistics()==before &&
          result.resource==(key_limit?s::Resource::cache_key_bytes:s::Resource::cache_plan_payload),
          "one-under cache capacity silently skipped install or published partial mutation");
  }
  auto disabled=s::PlanCache::create({0,0,0});
  const auto no_cache=choose(f.all,source,height(),disabled);
  check(no_cache.cache_observation().disposition==s::CacheDisposition::disabled && disabled.statistics()==s::CacheStatistics{},
        "zero-entry cache did not remain explicitly disabled");
  auto read_only=s::PlanCache::create(exact);
  const auto miss=choose(f.all,source,height(),read_only,s::CacheUse::read_only);
  check(miss.cache_observation().disposition==s::CacheDisposition::miss_read_only &&
        read_only.statistics().misses==1 && read_only.statistics().entries==0,
        "read-only miss was not separately recorded without insertion");
}

void proof_refresh_and_raw_tree(const BooleanFixture& f) {
  const s::Source source{s::DirectCQ{}};
  auto cache=s::PlanCache::create();
  const auto first=choose(f.all,source,height(),cache);
  auto fresh_provider=provider(prove(f.document.catalog,f.document.query));
  finish(fresh_provider);
  const auto fresh=fresh_provider.snapshot();
  const auto hit=choose(fresh,source,height(),cache);
  check(hit.cache_observation().disposition==s::CacheDisposition::hit && first.cache_binding()==hit.cache_binding(),
        "same source/family with a newly replayed proof did not reuse the artifact");
  check(&hit.selected().tree()!=&first.selected().tree() &&
        &hit.snapshot().original_proof().certificate()==&fresh.original_proof().certificate() &&
        &hit.snapshot().original_proof().certificate()!=&first.snapshot().original_proof().certificate(),
        "artifact cache transplanted a prior proof/candidate instead of retaining the current snapshot");
  check(&hit.plan().tree()==&first.plan().tree(),"artifact hit did not retain the same immutable compiled plan");

  const auto proof=prove(f.document.catalog,f.document.query);
  auto certificate=proof.certificate();
  check(certificate.tree && certificate.tree->nodes.size()>1,"permutation fixture requires a nontrivial checked witness");
  auto raw=*certificate.tree;
  const auto count=raw.nodes.size();
  std::reverse(raw.nodes.begin(),raw.nodes.end());
  const auto remap=[count](NodeId id){return NodeId{count-1-id.value};};
  if (raw.root) raw.root=remap(*raw.root);
  for (std::size_t i=0;i<count;++i) {
    raw.nodes[i].id="independent-permuted-"+std::to_string(i);
    for (auto& child:raw.nodes[i].children) child=remap(child);
    std::reverse(raw.nodes[i].children.begin(),raw.nodes[i].children.end());
    raw.nodes[i].claimed_separator.reset();
  }
  // Optional diagnostic claims are omitted; real independent replay computes
  // and validates the actual properties of the permuted upper witness.
  raw.claimed_connex.reset();raw.claimed_native_height.reset();
  certificate.tree=raw;
  const auto checked=replay(f.document.catalog,f.document.query,std::move(certificate));
  auto original_provider=provider(proof);
  auto permuted_provider=provider(checked);
  for (unsigned i=0;original_provider.candidate_count()==0 && i<2'000;++i)
    static_cast<void>(original_provider.advance({100'000,{}}));
  for (unsigned i=0;permuted_provider.candidate_count()==0 && i<2'000;++i)
    static_cast<void>(permuted_provider.advance({100'000,{}}));
  const auto original=original_provider.snapshot();
  const auto permuted=permuted_provider.snapshot();
  check(original.candidate_count()==1 && permuted.candidate_count()==1 &&
        original.candidate(0)->structural_key()==permuted.candidate(0)->structural_key() &&
        shape(original.candidate(0)->tree())==shape(permuted.candidate(0)->tree()),
        "raw permutation did not preserve independently replayed structural equivalence");
  auto raw_cache=s::PlanCache::create();
  const auto one=choose(original,source,height(),raw_cache);
  const auto two=choose(permuted,source,height(),raw_cache);
  check(two.cache_observation().disposition==s::CacheDisposition::inserted && one.cache_binding()!=two.cache_binding() &&
        two.plan().tree().nodes[0].id==raw.nodes[0].id,
        "equal structural keys collapsed different raw node/order bindings");
  auto actual=r::PhysicalRuntime::initialize(two.plan(),f.initial);
  check(answers(actual)==Relation{Row{}},"permuted selected artifact changed literal output");
}

void request_source_family_namespace(const BooleanFixture& f) {
  const s::Source source{s::DirectCQ{}};
  auto cache=s::PlanCache::create();
  const auto seed=choose(f.all,source,height(),cache);
  std::vector<s::Request> requests;
  auto fallback=s::Request{};requests.push_back(fallback);
  auto strict=height();strict.fallback=rank::Fallback::require_evidence;requests.push_back(strict);
  auto family=height();family.family=s::FamilyPolicy::require_exhausted_family;requests.push_back(family);
  for (unsigned field=0;field<10;++field) {
    auto request=height();auto& limits=request.limits.aggregate;
    switch(field) {
      case 0:++limits.work;break;case 1:++limits.cells;break;case 2:++limits.binding_key_bytes;break;
      case 3:++limits.payload_bytes;break;case 4:++limits.lowering_work;break;case 5:++limits.identity_work;break;
      case 6:++limits.binding_replay_work;break;case 7:++limits.normalization_work;break;
      case 8:++limits.candidates;break;case 9:--limits.score_bits;break;default:break;
    }
    requests.push_back(request);
  }
  std::set<std::string> keys{*seed.cache_binding()};
  for (const auto& request:requests) {
    const auto result=choose(f.all,source,request,cache);
    check(result.cache_observation().disposition==s::CacheDisposition::inserted && keys.insert(*result.cache_binding()).second,
          "requested policy/fallback/family/resource field was omitted from cache namespace");
  }
  for (unsigned field=0;field<6;++field) {
    PhysicalOptions options;
    switch(field) {
      case 0:options.policy.arithmetic+="-namespace";break;
      case 1:options.policy.planner+="-namespace";break;
      case 2:options.policy.optimization+="-namespace";break;
      case 3:options.policy.cost_model+="-namespace";break;
      case 4:++*options.limits.work_limit;break;
      case 5:++*options.limits.identity.work_limit;break;default:break;
    }
    const auto result=choose(f.all,s::Source{s::DirectCQ{options}},height(),cache);
    check(result.cache_observation().disposition==s::CacheDisposition::inserted && keys.insert(*result.cache_binding()).second,
          "exact physical options namespace was omitted from cache key");
  }
  const auto prefix=choose(f.partial,source,height(),cache);
  check(prefix.cache_observation().disposition==s::CacheDisposition::inserted && keys.insert(*prefix.cache_binding()).second &&
        !prefix.snapshot().family_exhausted(),"full family cache supplied a prefix's proof/completeness");
  const auto basis=lower(f.by_label.at("native_s"));
  const auto explicit_basis=choose(f.all,s::Source{s::PhysicalBasis{basis}},height(),cache);
  check(explicit_basis.cache_observation().disposition==s::CacheDisposition::inserted &&
        keys.insert(*explicit_basis.cache_binding()).second,"direct/basis source tags collapsed");
}

void current_abort_noop_reset(const BooleanFixture& f) {
  const s::Source source{s::DirectCQ{}};
  auto owner=r::PhysicalRuntime::initialize(lower(f.by_label.at("native_s")),f.initial);
  hot(owner,f);
  auto cache=s::PlanCache::create();
  const auto a=current::select_current(f.all,source,owner,depth(),{},&cache,s::CacheUse::read_write);
  const auto& first=complete(a);
  const auto old_aborts=first.capture().captured()->workload().metadata().aborted;
  auto pending=owner.prepare({101,TableId{1},SetOperation::erase,*f.initial.tables[1].begin()});
  const auto before=cache.statistics();
  const auto excluded=current::select_current(f.all,source,owner,height(),{},&cache,s::CacheUse::read_write);
  check(excluded.stop==s::Stop::boundary_unavailable && !excluded.selection && cache.statistics()==before,
        "pending capture mutated cache before publication");
  pending.rollback();
  const auto b=current::select_current(f.all,source,owner,depth(),{},&cache,s::CacheUse::read_write);
  check(complete(b).selection().cache_observation().disposition==s::CacheDisposition::hit &&
        b.selection->selection().cache_binding()==first.selection().cache_binding() &&
        b.selection->capture().captured()->workload().metadata().aborted==old_aborts+1 &&
        first.capture().captured()->workload().metadata().aborted==old_aborts,
        "abort-only diagnostics invalidated score facts or cache hit returned stale capture context");
  noop(owner,0,*f.initial.tables[0].begin(),1);
  const auto c=current::select_current(f.all,source,owner,depth(),{},&cache,s::CacheUse::read_write);
  check(complete(c).selection().cache_observation().disposition==s::CacheDisposition::inserted &&
        c.selection->selection().cache_binding()!=first.selection().cache_binding() &&
        c.selection->capture().inputs().identity().epoch==101,
        "committed no-op epoch/census incorrectly reused previous key");
  owner.reset_workload_statistics();
  const auto d=current::select_current(f.all,source,owner,s::Request{}, {},&cache,s::CacheUse::read_write);
  check(complete(d).selection().cache_observation().disposition==s::CacheDisposition::inserted &&
        d.selection->selection().cache_binding()!=c.selection->selection().cache_binding() &&
        has(d.selection->selection().fallback_reasons(),rank::Reason::empty_census),
        "reset/effective-policy context was absent from exact cache key");
  auto rebuilt=owner.rebuilt();
  const auto e=current::select_current(f.all,source,rebuilt,s::Request{}, {},&cache,s::CacheUse::read_write);
  check(complete(e).selection().cache_observation().disposition==s::CacheDisposition::inserted &&
        e.selection->capture().inputs().identity().owner!=d.selection->capture().inputs().identity().owner,
        "rebuilt equal data reused a foreign owner key");
}
} // namespace

int main(int argc,char** argv) {
  try {
    check(argc==2,"usage: selection_cache_independent_test REPOSITORY_ROOT");
    const auto fixture=boolean_fixture(argv[1]);
    fifo_read_only_and_lifetime(fixture);
    capacity_exact_and_transactional(fixture);
    proof_refresh_and_raw_tree(fixture);
    request_source_family_namespace(fixture);
    current_abort_noop_reset(fixture);
    std::cout<<"C05 independent cache groups=5 request_fields=13 physical_options=6 FIFO=2 raw_tree_aliases=2\n";
  } catch(const std::exception& error){std::cerr<<error.what()<<'\n';return 1;}
}
