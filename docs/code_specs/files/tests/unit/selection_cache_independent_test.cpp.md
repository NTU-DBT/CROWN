# `tests/unit/selection_cache_independent_test.cpp` — block usage map

[Source](../../../../../tests/unit/selection_cache_independent_test.cpp) · [Source index](../../../README.md) · [Subsystem contracts](../../../subsystem_contracts.md) · [Reviewed primitives](../../../primitives.md)

Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection.

Snapshot SHA-256: `53fa4cbde19fa9b7989411b1b74e5b32d2856a9eff6eb4fb1e51d29c32ebb254`. 274 lines partitioned into 14 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [tests](../../../subsystem_contracts.md#tests). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/code_review.md](../../../../code_review.md), [docs/reference_fuzz.md](../../../../reference_fuzz.md), [docs/task_ledger.md](../../../../task_ledger.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–6](../../../../../tests/unit/selection_cache_independent_test.cpp#L1) | Imports dependencies; declares namespace scope; declares aliases. |  · [reviewed contract](#b0001) |
| [B0002 · 7–12](../../../../../tests/unit/selection_cache_independent_test.cpp#L7) | Callable definition: s::Selection choose(const p::CandidateSnapshot& set,const s::Source& source,const s::Request& request, s::PlanCache& cache,s::Cac… | calls s::select, complete; returns complete(attempt) · [reviewed contract](#b0002) |
| [B0003 · 13–15](../../../../../tests/unit/selection_cache_independent_test.cpp#L13) | Callable definition: s::Request key_request(unsigned number) | calls height; returns result · [reviewed contract](#b0003) |
| [B0004 · 16–55](../../../../../tests/unit/selection_cache_independent_test.cpp#L16) | Callable definition: void fifo_read_only_and_lifetime(const BooleanFixture& f) | calls s::PlanCache::create, choose, key_request, check; guard check(a.cache_observation().disposition==s::CacheDisposition::inserted &&; returns choose(f.all,source,height(),temporary) · [reviewed contract](#b0004) |
| [B0005 · 56–56](../../../../../tests/unit/selection_cache_independent_test.cpp#L56) | Explanatory comments or spacing. |  |
| [B0006 · 57–87](../../../../../tests/unit/selection_cache_independent_test.cpp#L57) | Callable definition: void capacity_exact_and_transactional(const BooleanFixture& f) | calls s::PlanCache::create, choose, height, statistics; guard check(size.entries==1 && size.key_bytes==seed.cache_binding()-&gt;size() && size.plan_payload_bytes&gt;0,; 1 loop sites · [reviewed contract](#b0006) |
| [B0007 · 88–88](../../../../../tests/unit/selection_cache_independent_test.cpp#L88) | Explanatory comments or spacing. |  |
| [B0008 · 89–144](../../../../../tests/unit/selection_cache_independent_test.cpp#L89) | Callable definition: void proof_refresh_and_raw_tree(const BooleanFixture& f) | calls s::PlanCache::create, choose, height, provider; guard check(hit.cache_observation().disposition==s::CacheDisposition::hit && first.cache_binding()==hit.c…; returns NodeId{count-1-id.value}; 4 loop sites; source comment (unverified): // Optional diagnostic claims are omitted; real independent replay computes · [reviewed contract](#b0008) |
| [B0009 · 145–145](../../../../../tests/unit/selection_cache_independent_test.cpp#L145) | Explanatory comments or spacing. |  |
| [B0010 · 146–221](../../../../../tests/unit/selection_cache_independent_test.cpp#L146) | Callable definition: void request_source_family_namespace(const BooleanFixture& f) | calls s::PlanCache::create, choose, height, push_back; guard check(result.cache_observation().disposition==s::CacheDisposition::inserted && keys.insert(caller_t…; growth insert, push_back; 4 loop sites; source comment (unverified): // Native identity admits only exact-nonnull-v1. Keep this field as a · [reviewed contract](#b0010) |
| [B0011 · 222–222](../../../../../tests/unit/selection_cache_independent_test.cpp#L222) | Explanatory comments or spacing. |  |
| [B0012 · 223–260](../../../../../tests/unit/selection_cache_independent_test.cpp#L223) | Callable definition: void current_abort_noop_reset(const BooleanFixture& f) | calls r::PhysicalRuntime::initialize, lower, at, hot; guard check(excluded.stop==s::Stop::boundary_unavailable && !excluded.selection && cache.statistics()==be… · [reviewed contract](#b0012) |
| [B0013 · 261–262](../../../../../tests/unit/selection_cache_independent_test.cpp#L261) | Closes surrounding scope/type. | source comment (unverified): // namespace · [reviewed contract](#b0013) |
| [B0014 · 263–274](../../../../../tests/unit/selection_cache_independent_test.cpp#L263) | Callable definition: int main(int argc,char** argv) | calls check, boolean_fixture, fifo_read_only_and_lifetime, capacity_exact_and_transactional; guard check(argc==2,"usage: selection_cache_independent_test REPOSITORY_ROOT");; returns 1 · [reviewed contract](#b0014) |

## B0001

[Lines 1–6](../../../../../tests/unit/selection_cache_independent_test.cpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L1-L6:sha256:c62dc32cdace53db643b2dd83eea84049c6b9253c5bec21cb0d35691dab65085
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Prepare selection_cache_independent_test.cpp: include "selection_independent_fixture.hpp", &lt;iostream&gt;; bind local aliases/name imports. |
| inputs / outputs | Compiler-visible dependencies, names and the recorded declarations in; declarations available to the following fixture/CLI/example definitions out. |
| invariants | Declarations are scoped to this source/header and its selected ABI. Included code has its own effects; names and editable fixture values do not confer proof, admission or publication authority. |
| ownership | Aliases/includes do not create a query owner. Pointers/references/views are non-owning. Containers own their elements, which can themselves be borrowed pointers or numeric IDs. Only documented owning shared-control handles retain controls; IDs/slot-handle values do not independently keep an arena/runtime alive. |
| failure | Missing headers, ill-formed names/types, failed static assertions or active #error directives stop compilation. No runtime rejection/rollback mechanism is implemented by aliases or function prototypes. |
| cost | Preprocessing and type/constraint instantiation cost compilation. Alias/prototype syntax does not invoke the declared operation; any included definitions keep their own initialization effects. |
| Design | [tests/unit/selection_cache_independent_test.cpp](../../../../../tests/unit/selection_cache_independent_test.cpp), [docs/selection.md](../../../../selection.md), [docs/code_review.md](../../../../code_review.md) |

## B0002

[Lines 7–12](../../../../../tests/unit/selection_cache_independent_test.cpp#L7); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
s::Selection choose(const p::CandidateSnapshot& set,const s::Source& source,const s::Request& request,
                    s::PlanCache& cache,s::CacheUse use=s::CacheUse::read_write,
                    const std::optional<rank::Evidence>& facts={}) {
  const auto attempt=s::select(set,source,request,facts,&cache,use);
  return complete(attempt);
}

```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Perform a selection through the independent Boolean fixture cache. |
| inputs / outputs | Accepts family, source, request, cache, use mode, and optional Evidence; returns completed Selection. |
| invariants | The helper checks stop and presence before exposing the immutable result. |
| ownership | Inputs/cache are borrowed; returned Selection retains its own plan/proof context. |
| failure | Unexpected stop throws test failure. |
| cost | One admission/selection/cache operation; hit still performs key construction and fresh ranking admission. |
| Design | [tests/unit/selection_cache_independent_test.cpp](../../../../../tests/unit/selection_cache_independent_test.cpp), [include/crown/planner/selection.hpp](../../../../../include/crown/planner/selection.hpp), [src/planner/selection.cpp](../../../../../src/planner/selection.cpp), [docs/selection.md](../../../../selection.md), [docs/selection_accounting.md](../../../../selection_accounting.md), [src/planner/selection_cache.cpp](../../../../../src/planner/selection_cache.cpp), [src/planner/selection_binding.cpp](../../../../../src/planner/selection_binding.cpp), [tests/support/selection_independent_fixture.hpp](../../../../../tests/support/selection_independent_fixture.hpp) |

## B0003

[Lines 13–15](../../../../../tests/unit/selection_cache_independent_test.cpp#L13); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
s::Request key_request(unsigned number) {
  auto result=height();result.limits.aggregate.score_bits=500U+number;return result;
}

```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Create distinct aggregate score_bits request ceilings for cache-key tests. |
| inputs / outputs | Copies a height-only Request and sets limits.aggregate.score_bits to 500 plus number; returns that request. |
| invariants | Only the score-bit ceiling varies among these helper-produced requests; it is an integer limit, not decimal slot text or a byte budget. |
| ownership | The returned Request owns ordinary scalar limit fields; no constraint string is constructed or retained. |
| failure | This helper has no domain stop; values 500–502 are passed as request limits and admission occurs in select. |
| cost | Copies one Request and adds number to its integer score_bits ceiling. |
| Design | [tests/unit/selection_cache_independent_test.cpp](../../../../../tests/unit/selection_cache_independent_test.cpp), [include/crown/planner/selection.hpp](../../../../../include/crown/planner/selection.hpp), [src/planner/selection.cpp](../../../../../src/planner/selection.cpp), [docs/selection.md](../../../../selection.md), [docs/selection_accounting.md](../../../../selection_accounting.md), [src/planner/selection_cache.cpp](../../../../../src/planner/selection_cache.cpp), [src/planner/selection_binding.cpp](../../../../../src/planner/selection_binding.cpp), [tests/support/selection_independent_fixture.hpp](../../../../../tests/support/selection_independent_fixture.hpp) |

## B0004

[Lines 16–55](../../../../../tests/unit/selection_cache_independent_test.cpp#L16); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
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

```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Verify FIFO order, read-only misses, move, clear, and result lifetime. |
| inputs / outputs | Uses three keys with capacity two; exercises hit without reordering, third insertion, read-only miss, cache move/clear and retained result. |
| invariants | FIFO hits do not refresh order; read-only misses increment misses but do not insert; moving/clearing/destroying the cache leaves earlier Selection usable. |
| ownership | Cache is exclusive/move-only; Selection shares immutable result/plan ownership beyond cache lifetime. |
| failure | Invalid/missing selection fails the fixture; cache operations themselves are checked via stats. |
| cost | Three key admissions plus hits/misses and lifecycle operations; no lower is assumed free on every policy. |
| Design | [tests/unit/selection_cache_independent_test.cpp](../../../../../tests/unit/selection_cache_independent_test.cpp), [include/crown/planner/selection.hpp](../../../../../include/crown/planner/selection.hpp), [src/planner/selection.cpp](../../../../../src/planner/selection.cpp), [docs/selection.md](../../../../selection.md), [docs/selection_accounting.md](../../../../selection_accounting.md), [src/planner/selection_cache.cpp](../../../../../src/planner/selection_cache.cpp), [src/planner/selection_binding.cpp](../../../../../src/planner/selection_binding.cpp), [tests/support/selection_independent_fixture.hpp](../../../../../tests/support/selection_independent_fixture.hpp) |

## B0006

[Lines 57–87](../../../../../tests/unit/selection_cache_independent_test.cpp#L57); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
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

```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Check cache capacity exact-fit and transactional one-under stops. |
| inputs / outputs | Builds a seed selection to obtain key/payload sizes, then tests exact limits, one-byte-short limits, disabled cache, and read-only miss. |
| invariants | Failed insertion leaves cache image/counters unchanged; a zero capacity disables retention without changing selection semantics. |
| ownership | PlanCache owns entry keys/plans; local Selection copies may outlive a rejected or cleared cache entry. |
| failure | Over-limit requests return the explicit cache dimension and no partial insertion. |
| cost | Several full selections and cache-image comparisons; exact payload means modeled retained plan payload, not allocator bytes. |
| Design | [tests/unit/selection_cache_independent_test.cpp](../../../../../tests/unit/selection_cache_independent_test.cpp), [include/crown/planner/selection.hpp](../../../../../include/crown/planner/selection.hpp), [src/planner/selection.cpp](../../../../../src/planner/selection.cpp), [docs/selection.md](../../../../selection.md), [docs/selection_accounting.md](../../../../selection_accounting.md), [src/planner/selection_cache.cpp](../../../../../src/planner/selection_cache.cpp), [src/planner/selection_binding.cpp](../../../../../src/planner/selection_binding.cpp), [tests/support/selection_independent_fixture.hpp](../../../../../tests/support/selection_independent_fixture.hpp) |

## B0008

[Lines 89–144](../../../../../tests/unit/selection_cache_independent_test.cpp#L89); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
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

```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Separate refreshed proof identity from raw tree cache identity. |
| inputs / outputs | Reuses a source/family with refreshed proof, then permutes a raw certificate’s IDs/order and retries selection. |
| invariants | Equivalent compiled artifact reuse still retains the newly supplied snapshot/proof/capture context; raw tree IDs/order separately change the cache key even when structural choice matches. |
| ownership | New proof/family handles are retained by the new Selection; old cache entry owns only immutable compiled artifact. |
| failure | Invalid raw replay/verification or cache miss follows explicit Attempt stop. |
| cost | Finite certificate replay and a provider advance bounded by fixture loop guard (2,000 steps); this is not universal provider timing. |
| Design | [tests/unit/selection_cache_independent_test.cpp](../../../../../tests/unit/selection_cache_independent_test.cpp), [include/crown/planner/selection.hpp](../../../../../include/crown/planner/selection.hpp), [src/planner/selection.cpp](../../../../../src/planner/selection.cpp), [docs/selection.md](../../../../selection.md), [docs/selection_accounting.md](../../../../selection_accounting.md), [src/planner/selection_cache.cpp](../../../../../src/planner/selection_cache.cpp), [src/planner/selection_binding.cpp](../../../../../src/planner/selection_binding.cpp), [tests/support/selection_independent_fixture.hpp](../../../../../tests/support/selection_independent_fixture.hpp) |

## B0010

[Lines 146–221](../../../../../tests/unit/selection_cache_independent_test.cpp#L146); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
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
  std::set<std::string> keys{caller_text(*seed.cache_binding())};
  std::vector<s::Selection> retained_namespaces;
  retained_namespaces.push_back(seed);
  for (const auto& request:requests) {
    const auto result=choose(f.all,source,request,cache);
    check(result.cache_observation().disposition==s::CacheDisposition::inserted && keys.insert(caller_text(*result.cache_binding())).second,
          "requested policy/fallback/family/resource field was omitted from cache namespace");
    retained_namespaces.push_back(result);
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
    if (field==0) {
      // Native identity admits only exact-nonnull-v1. Keep this field as a
      // rejection/atomicity check, not a supported alternate namespace.
      const auto before=cache.statistics();
      const auto rejected=s::select(f.all,s::Source{s::DirectCQ{options}},height(),{},&cache,s::CacheUse::read_write);
      check(rejected.stop==s::Stop::lowering_failure && rejected.stage==s::Stage::lowering &&
            rejected.resource==s::Resource::none && !rejected.component_stop && !rejected.selection &&
            cache.statistics()==before,
            "unsupported arithmetic published a result or changed cache statistics");
      auto expected=before;
      for (const auto& retained:retained_namespaces) {
        const auto existing=choose(f.all,source,retained.export_request(),cache,s::CacheUse::read_only);
        ++expected.hits;
        check(existing.cache_observation().disposition==s::CacheDisposition::hit &&
              existing.cache_binding()==retained.cache_binding() &&
              &existing.plan().tree()==&retained.plan().tree() && cache.statistics()==expected,
              "unsupported arithmetic changed a retained entry or retry counters");
      }
      options.policy.arithmetic="exact-nonnull-v1";
      const auto retry=choose(f.all,s::Source{s::DirectCQ{options}},height(),cache);
      ++expected.hits;
      check(retry.cache_observation().disposition==s::CacheDisposition::hit &&
            retry.cache_binding()==seed.cache_binding() && &retry.plan().tree()==&seed.plan().tree() &&
            cache.statistics()==expected,
            "supported same-configuration retry lost the original cache artifact");
      continue;
    }
    const auto result=choose(f.all,s::Source{s::DirectCQ{options}},height(),cache);
    check(result.cache_observation().disposition==s::CacheDisposition::inserted && keys.insert(caller_text(*result.cache_binding())).second,
          "exact physical options namespace was omitted from cache key");
  }
  const auto prefix=choose(f.partial,source,height(),cache);
  check(prefix.cache_observation().disposition==s::CacheDisposition::inserted && keys.insert(caller_text(*prefix.cache_binding())).second &&
        !prefix.snapshot().family_exhausted(),"full family cache supplied a prefix's proof/completeness");
  const auto basis=lower(f.by_label.at("native_s"));
  const auto explicit_basis=choose(f.all,s::Source{s::PhysicalBasis{basis}},height(),cache);
  check(explicit_basis.cache_observation().disposition==s::CacheDisposition::inserted &&
        keys.insert(caller_text(*explicit_basis.cache_binding())).second,"direct/basis source tags collapsed");
}

```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Verify cache-key separation across request policies/limits, physical source options and family completeness. |
| inputs / outputs | Varies default versus required-evidence fallback, family policy, ten aggregate numeric limits, six physical options (one unsupported arithmetic value and five supported changes), a partial family, and direct versus explicit-basis sources. It passes no Evidence input and does not vary a slot cap. |
| invariants | Request, source-option and family differences produce distinct bindings; unsupported arithmetic is rejected transactionally. The default-policy partial-family selection succeeds with an incomplete snapshot and its own key; no evidence-key variation is tested. |
| ownership | Cache retains compiled artifact/key bytes; each Selection retains its own snapshot, source and request context. This function supplies no Evidence value. |
| failure | Unsupported arithmetic must fail before changing cache state; the partial-family default request is expected to succeed while retaining family_exhausted=false. |
| cost | Finite request/source matrix (including ten limit variants and five supported option changes), each with key comparison and selected calls. |
| Design | [tests/unit/selection_cache_independent_test.cpp](../../../../../tests/unit/selection_cache_independent_test.cpp), [include/crown/planner/selection.hpp](../../../../../include/crown/planner/selection.hpp), [src/planner/selection.cpp](../../../../../src/planner/selection.cpp), [docs/selection.md](../../../../selection.md), [docs/selection_accounting.md](../../../../selection_accounting.md), [src/planner/selection_cache.cpp](../../../../../src/planner/selection_cache.cpp), [src/planner/selection_binding.cpp](../../../../../src/planner/selection_binding.cpp), [tests/support/selection_independent_fixture.hpp](../../../../../tests/support/selection_independent_fixture.hpp) |

## B0012

[Lines 223–260](../../../../../tests/unit/selection_cache_independent_test.cpp#L223); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
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

```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Check current-owner capture, abort metadata, no-op commit, and reset key changes. |
| inputs / outputs | Calls current selection around pending state, rollback, no-op commit, reset, and rebuilt owner identity. |
| invariants | Pending state is not bypassed; abort diagnostics can refresh capture context while score binding remains equal; no-op epoch and reset change current identity. |
| ownership | CurrentSelection retains fresh RuntimeEvidence; cache entry remains immutable and separate from owner state. |
| failure | Boundary-unavailable calls do not insert; current capture failures stay distinct from cache misses. |
| cost | A small sequential owner-boundary lifecycle with fresh capture/select at each asserted stage. |
| Design | [tests/unit/selection_cache_independent_test.cpp](../../../../../tests/unit/selection_cache_independent_test.cpp), [include/crown/planner/selection.hpp](../../../../../include/crown/planner/selection.hpp), [src/planner/selection.cpp](../../../../../src/planner/selection.cpp), [docs/selection.md](../../../../selection.md), [docs/selection_accounting.md](../../../../selection_accounting.md), [src/planner/selection_cache.cpp](../../../../../src/planner/selection_cache.cpp), [src/planner/selection_binding.cpp](../../../../../src/planner/selection_binding.cpp), [tests/support/selection_independent_fixture.hpp](../../../../../tests/support/selection_independent_fixture.hpp) |

## B0013

[Lines 261–262](../../../../../tests/unit/selection_cache_independent_test.cpp#L261); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L261-L262:sha256:c929980d95efc152dc886ac42af0f045075441dd18a8f886364828ead327bbd3
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Close the recorded declaration scopes in selection_cache_independent_test.cpp: namespace (anonymous). |
| inputs / outputs | Preceding namespace, type or initializer declarations in; completed lexical boundary out. |
| invariants | Brace-opening context is recorded in root-scope-context-v1.json. These are declaration/initializer boundaries, not an independent update, validation or recovery operation. |
| ownership | Enclosing objects and borrowed fields keep their declared ownership. This punctuation creates no new owner. |
| failure | Malformed scope syntax is a compile error. Any initializer/constructor failure belongs to the enclosing object declaration. |
| cost | No separate loop, guard or engine call is introduced by the delimiter; enclosing initialization and object lifetime still have their actual costs. |
| Design | [tests/unit/selection_cache_independent_test.cpp](../../../../../tests/unit/selection_cache_independent_test.cpp), [docs/selection.md](../../../../selection.md), [docs/code_review.md](../../../../code_review.md) |

## B0014

[Lines 263–274](../../../../../tests/unit/selection_cache_independent_test.cpp#L263); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
int main(int argc,char** argv) {
  try {
    check(argc==2,"usage: selection_cache_independent_test REPOSITORY_ROOT");
    const auto fixture=boolean_fixture(argv[1]);
    fifo_read_only_and_lifetime(fixture);
    capacity_exact_and_transactional(fixture);
    proof_refresh_and_raw_tree(fixture);
    request_source_family_namespace(fixture);
    current_abort_noop_reset(fixture);
    std::cout<<"C05 independent cache groups=5 request_fields=13 physical_options_supported=5 physical_options_rejected=1 FIFO=2 raw_tree_aliases=2\n";
  } catch(const std::exception& error){std::cerr<<error.what()<<'\n';return 1;}
}

```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Run the five independent cache behavior groups. |
| inputs / outputs | Loads the supplied fixture and calls FIFO/lifetime, capacity, proof/raw tree, namespace, and current lifecycle scenarios. |
| invariants | Each scenario creates isolated cache state so counter deltas have local baselines. |
| ownership | Fixture-owned Boolean candidate handles are shared into each test; each cache dies after its group. |
| failure | Fixture read or any group assertion fails the test. |
| cost | Five group executions; internal bounded loops and selection calls are counted by their scenario-specific assertions. |
| Design | [tests/unit/selection_cache_independent_test.cpp](../../../../../tests/unit/selection_cache_independent_test.cpp), [include/crown/planner/selection.hpp](../../../../../include/crown/planner/selection.hpp), [src/planner/selection.cpp](../../../../../src/planner/selection.cpp), [docs/selection.md](../../../../selection.md), [docs/selection_accounting.md](../../../../selection_accounting.md), [src/planner/selection_cache.cpp](../../../../../src/planner/selection_cache.cpp), [src/planner/selection_binding.cpp](../../../../../src/planner/selection_binding.cpp), [tests/support/selection_independent_fixture.hpp](../../../../../tests/support/selection_independent_fixture.hpp) |
