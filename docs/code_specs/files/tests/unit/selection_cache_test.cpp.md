# `tests/unit/selection_cache_test.cpp` — block usage map

[Source](../../../../../tests/unit/selection_cache_test.cpp) · [Source index](../../../README.md) · [Subsystem contracts](../../../subsystem_contracts.md) · [Reviewed primitives](../../../primitives.md)

Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection.

Snapshot SHA-256: `0df8e9eb42a33640b0d7b8e9d19790541ce2e763f83ab5bf5e41ab9678b8507f`. 112 lines partitioned into 6 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [tests](../../../subsystem_contracts.md#tests). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/code_review.md](../../../../code_review.md), [docs/reference_fuzz.md](../../../../reference_fuzz.md), [docs/task_ledger.md](../../../../task_ledger.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–8](../../../../../tests/unit/selection_cache_test.cpp#L1) | Imports dependencies; declares namespace scope; declares aliases; declares values/defaults or compile-time conditions. |  · [reviewed contract](#b0001) |
| [B0002 · 9–14](../../../../../tests/unit/selection_cache_test.cpp#L9) | Callable definition: auto image(ps::PlanCache& cache) | calls sd::Factory::cache, emplace_back, physical_sha256; returns out; growth emplace_back; 1 loop sites · [reviewed contract](#b0002) |
| [B0003 · 15–33](../../../../../tests/unit/selection_cache_test.cpp#L15) | Callable definition: planner::VerifiedOptimum replay(const planner::VerifiedOptimum& original, bool rename) | calls binding, certificate, check, has_value; guard check(certificate.tree.has_value(), "C05 replay fixture omitted tree");; returns *replay.checked()-&gt;optimum(); 4 loop sites · [reviewed contract](#b0003) |
| [B0004 · 34–39](../../../../../tests/unit/selection_cache_test.cpp#L34) | Callable definition: planner::CandidateSnapshot family(const planner::VerifiedOptimum& proof) | calls planner::CandidateProvider::create, progress, advance, check; guard check(provider.progress().family_exhausted, "C05 replay family incomplete"); return provider.snapsh…; returns provider.snapshot(); 1 loop sites · [reviewed contract](#b0004) |
| [B0005 · 40–40](../../../../../tests/unit/selection_cache_test.cpp#L40) | Closes surrounding scope/type. |  · [reviewed contract](#b0005) |
| [B0006 · 41–112](../../../../../tests/unit/selection_cache_test.cpp#L41) | Callable definition: int main() | calls c02_test::fixture, c02_test::candidates, planner::lower_tree, candidate; guard check(cache.statistics().entries == 2 && cache.statistics().insertions == 2, "C05 cache two inserti…; returns 1; 1 loop sites; source comment (unverified): // A separately replayed, byte-identical original proof must remain the new · [reviewed contract](#b0006) |

## B0001

[Lines 1–8](../../../../../tests/unit/selection_cache_test.cpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L1-L8:sha256:cfa6ce20fa9a2a47ca81e55330735d8d779fb744fd3e43ddbb685235ae0f2c3f
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Prepare selection_cache_test.cpp: include "selection_fixture.hpp", "selection_detail.hpp", &lt;iostream&gt;, &lt;tuple&gt;; bind local aliases/name imports. |
| inputs / outputs | Compiler-visible dependencies, names and the recorded declarations in; declarations available to the following fixture/CLI/example definitions out. |
| invariants | Declarations are scoped to this source/header and its selected ABI. Included code has its own effects; names and editable fixture values do not confer proof, admission or publication authority. |
| ownership | Aliases/includes do not create a query owner. Pointers/references/views are non-owning. Containers own their elements, which can themselves be borrowed pointers or numeric IDs. Only documented owning shared-control handles retain controls; IDs/slot-handle values do not independently keep an arena/runtime alive. |
| failure | Missing headers, ill-formed names/types, failed static assertions or active #error directives stop compilation. No runtime rejection/rollback mechanism is implemented by aliases or function prototypes. |
| cost | Preprocessing and type/constraint instantiation cost compilation. Alias/prototype syntax does not invoke the declared operation; any included definitions keep their own initialization effects. |
| Design | [tests/unit/selection_cache_test.cpp](../../../../../tests/unit/selection_cache_test.cpp), [docs/selection.md](../../../../selection.md), [docs/code_review.md](../../../../code_review.md) |

## B0002

[Lines 9–14](../../../../../tests/unit/selection_cache_test.cpp#L9); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
auto image(ps::PlanCache& cache) {
  std::vector<std::tuple<std::string, std::string, std::uint64_t>> out;
  const auto* data = sd::Factory::cache(&cache);
  for (const auto& entry : data->entries) out.emplace_back(entry.key, entry.plan.physical_sha256(), entry.payload);
  return out;
}

```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Snapshot cache entry keys, compiled-plan digests and modeled payload sizes for comparisons. |
| inputs / outputs | Walks the internal PlanCache entry list and copies each key, plan physical digest and payload count into local tuples; it does not read cache statistics. |
| invariants | The image is diagnostic only and cannot insert an entry. |
| ownership | Copied strings/tuples own the snapshot; cache is borrowed. |
| failure | Allocation/read failure propagates. |
| cost | Walks the current cache entries and copies each key for comparison. |
| Design | [tests/unit/selection_cache_test.cpp](../../../../../tests/unit/selection_cache_test.cpp), [include/crown/planner/selection.hpp](../../../../../include/crown/planner/selection.hpp), [src/planner/selection.cpp](../../../../../src/planner/selection.cpp), [docs/selection.md](../../../../selection.md), [docs/selection_accounting.md](../../../../selection_accounting.md), [src/planner/selection_cache.cpp](../../../../../src/planner/selection_cache.cpp), [src/planner/selection_binding.cpp](../../../../../src/planner/selection_binding.cpp), [tests/support/selection_independent_fixture.hpp](../../../../../tests/support/selection_independent_fixture.hpp) |

## B0003

[Lines 15–33](../../../../../tests/unit/selection_cache_test.cpp#L15); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
planner::VerifiedOptimum replay(const planner::VerifiedOptimum& original, bool rename) {
  const auto binding = original.binding(); auto certificate = original.certificate();
  if (rename) {
    check(certificate.tree.has_value(), "C05 replay fixture omitted tree");
    auto& tree = *certificate.tree;
    std::reverse(tree.nodes.begin(), tree.nodes.end());
    for (auto& node : tree.nodes) {
      node.id += "_relabel"; std::reverse(node.children.begin(), node.children.end());
      for (auto& child : node.children) child.value = tree.nodes.size() - 1 - child.value;
    }
    if (tree.root) tree.root->value = tree.nodes.size() - 1 - tree.root->value;
    if (tree.claimed_connex) for (auto& id : *tree.claimed_connex) id.value = tree.nodes.size() - 1 - id.value;
  }
  planner::ReplayOptions options; options.limits.work = 50'000'000;
  auto replay = planner::CertificateReplay::create(binding.catalog(), binding.query(), std::move(certificate), options);
  for (std::size_t n = 0; n < 100'000 && !replay.checked(); ++n) static_cast<void>(replay.advance({1000, {}}));
  check(replay.checked() && replay.checked()->optimum(), "C05 finite certificate replay failed");
  return *replay.checked()->optimum();
}

```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Copy and independently replay a VerifiedOptimum, optionally permuting its raw certificate tree, then return the checked optimum. |
| inputs / outputs | Copies the input binding/certificate, optionally relabels and reorders the raw tree, runs CertificateReplay, advances it in 1,000-work quanta for at most 100,000 calls, and returns checked()-&gt;optimum(). |
| invariants | The returned VerifiedOptimum exists only after CertificateReplay reports checked optimum; optional raw-byte changes are independently reverified before later cache comparisons. |
| ownership | The input optimum is borrowed; certificate edits are local copies; replay owns its incremental check state; the returned optimum retains verifier-produced proof data. |
| failure | A failed/unfinished replay or missing checked optimum fails the helper assertion; invalid remapping is rejected by CertificateReplay before return. |
| cost | Copies and walks certificate records, then performs at most 100,000 CertificateReplay advances of 1,000 work units and checks the verified optimum; this fixture guard is not a general replay bound. |
| Design | [tests/unit/selection_cache_test.cpp](../../../../../tests/unit/selection_cache_test.cpp), [include/crown/planner/selection.hpp](../../../../../include/crown/planner/selection.hpp), [src/planner/selection.cpp](../../../../../src/planner/selection.cpp), [docs/selection.md](../../../../selection.md), [docs/selection_accounting.md](../../../../selection_accounting.md), [src/planner/selection_cache.cpp](../../../../../src/planner/selection_cache.cpp), [src/planner/selection_binding.cpp](../../../../../src/planner/selection_binding.cpp), [tests/support/selection_independent_fixture.hpp](../../../../../tests/support/selection_independent_fixture.hpp) |

## B0004

[Lines 34–39](../../../../../tests/unit/selection_cache_test.cpp#L34); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
planner::CandidateSnapshot family(const planner::VerifiedOptimum& proof) {
  auto provider = planner::CandidateProvider::create(proof);
  for (std::size_t n = 0; n < 100'000 && !provider.progress().family_exhausted; ++n)
    static_cast<void>(provider.advance({1000, {}}));
  check(provider.progress().family_exhausted, "C05 replay family incomplete"); return provider.snapshot();
}

```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Enumerate a CandidateProvider to family exhaustion and return its snapshot. |
| inputs / outputs | Creates a CandidateProvider from the supplied VerifiedOptimum, advances until family_exhausted or the 100,000-call guard, then returns provider.snapshot(). |
| invariants | A successful return requires family_exhausted; candidate_count is determined by the proof/provider and is not fixed to one. |
| ownership | Returned snapshot retains proof handles; argument remains borrowed. |
| failure | If the provider has not exhausted within 100,000 advances, the helper assertion fails; otherwise it returns the exhausted snapshot. |
| cost | Runs at most 100,000 provider advances with 1,000-work quanta to enumerate the proof family; the result is not assumed to have one member. |
| Design | [tests/unit/selection_cache_test.cpp](../../../../../tests/unit/selection_cache_test.cpp), [include/crown/planner/selection.hpp](../../../../../include/crown/planner/selection.hpp), [src/planner/selection.cpp](../../../../../src/planner/selection.cpp), [docs/selection.md](../../../../selection.md), [docs/selection_accounting.md](../../../../selection_accounting.md), [src/planner/selection_cache.cpp](../../../../../src/planner/selection_cache.cpp), [src/planner/selection_binding.cpp](../../../../../src/planner/selection_binding.cpp), [tests/support/selection_independent_fixture.hpp](../../../../../tests/support/selection_independent_fixture.hpp) |

## B0005

[Lines 40–40](../../../../../tests/unit/selection_cache_test.cpp#L40); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L40-L40:sha256:412ca345ccf75bf9c0806bce695be8de808b79984251a7a54d202cf6101dd451
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Close the recorded declaration scopes in selection_cache_test.cpp: namespace (anonymous). |
| inputs / outputs | Preceding namespace, type or initializer declarations in; completed lexical boundary out. |
| invariants | Brace-opening context is recorded in root-scope-context-v1.json. These are declaration/initializer boundaries, not an independent update, validation or recovery operation. |
| ownership | Enclosing objects and borrowed fields keep their declared ownership. This punctuation creates no new owner. |
| failure | Malformed scope syntax is a compile error. Any initializer/constructor failure belongs to the enclosing object declaration. |
| cost | No separate loop, guard or engine call is introduced by the delimiter; enclosing initialization and object lifetime still have their actual costs. |
| Design | [tests/unit/selection_cache_test.cpp](../../../../../tests/unit/selection_cache_test.cpp), [docs/selection.md](../../../../selection.md), [docs/code_review.md](../../../../code_review.md) |

## B0006

[Lines 41–112](../../../../../tests/unit/selection_cache_test.cpp#L41); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
int main() { try {
  using namespace c05_test;
  const auto f = c02_test::fixture(); const auto snapshot = c02_test::candidates(f);
  const auto plan = planner::lower_tree(f.catalog, f.query, snapshot.candidate(0)->tree());
  auto owner = runtime::PhysicalRuntime::initialize(plan, f.database); heat(owner, f);
  const auto evidence = capture(snapshot, owner).inputs(); const ps::Source source = ps::DirectCQ{};
  auto cache = ps::PlanCache::create({2, 8 * 1024 * 1024, 32 * 1024 * 1024});
  const auto height = request(ps::Policy::height_only); const auto memory = request(ps::Policy::tuple_index_slots);
  const auto depth = request(ps::Policy::committed_input_native_depth);
  const auto a = complete(ps::select(snapshot, source, height, evidence, &cache, ps::CacheUse::read_write));
  const auto b = complete(ps::select(snapshot, source, memory, evidence, &cache, ps::CacheUse::read_write));
  check(cache.statistics().entries == 2 && cache.statistics().insertions == 2, "C05 cache two insertions");
  const auto before_hit = image(cache);
  const auto ah = complete(ps::select(snapshot, source, height, evidence, &cache, ps::CacheUse::read_only));
  check(ah.cache_observation().disposition == ps::CacheDisposition::hit && image(cache) == before_hit &&
      ah.usage().lowering_work == 0 && ah.cache_binding() == a.cache_binding(), "C05 read-only hit/order/lowering");
  const auto bh = complete(ps::select(snapshot, source, memory, evidence, &cache, ps::CacheUse::read_only));
  check(bh.cache_observation().disposition == ps::CacheDisposition::hit && bh.usage().lowering_work == b.usage().lowering_work &&
      bh.usage().lowering_work != 0, "C05 cache silently skipped full Q lowering");
  slot_oracle(assessment(bh, pr::Policy::tuple_index_slots));
  const auto c = complete(ps::select(snapshot, source, depth, evidence, &cache, ps::CacheUse::read_write));
  const auto after_c = image(cache);
  check(cache.statistics().entries == 2 && cache.statistics().evictions == 1 && std::get<0>(after_c[0]) == *b.cache_binding() &&
      std::get<0>(after_c[1]) == *c.cache_binding(), "C05 FIFO hit reordered eviction");
  const auto missing = complete(ps::select(snapshot, source, height, evidence, &cache, ps::CacheUse::read_only));
  check(missing.cache_observation().disposition == ps::CacheDisposition::miss_read_only && image(cache) == after_c,
      "C05 read-only miss inserted an entry");
  check(io::write_physical(ah.plan()).dump() == io::write_physical(a.plan()).dump(), "C05 reused plan descriptor bytes changed");
  const auto saved = image(cache); const auto stats = cache.statistics();
  sd::Factory::cache(&cache)->statistics.hits = UINT64_MAX;
  const auto saturated_stats = cache.statistics();
  const auto saturated = ps::select(snapshot, source, depth, evidence, &cache, ps::CacheUse::read_only);
  check(!saturated.selection && saturated.stop == ps::Stop::resource_limit && saturated.resource == ps::Resource::counter_overflow &&
      image(cache) == saved && cache.statistics() == saturated_stats, "C05 cache counter wrapped or mutated");
  sd::Factory::cache(&cache)->statistics = stats;
  auto moved = std::move(cache);
  check(!cache.valid() && ps::select(snapshot, source, height, {}, &cache, ps::CacheUse::read_only).stop == ps::Stop::invalid_handle,
      "C05 moved cache admitted");
  check(ps::select(snapshot, source, height, {}, nullptr, ps::CacheUse::read_only).stop == ps::Stop::invalid_request,
      "C05 missing explicit cache was ignored");
  moved.clear(); check(moved.statistics() == ps::CacheStatistics{}, "C05 clear did not reset cache state");
  valid_plan(a, f.database); valid_plan(b, f.database); valid_plan(c, f.database);
  auto disabled = ps::PlanCache::create({0, 0, 0});
  const auto off = complete(ps::select(snapshot, source, height, {}, &disabled, ps::CacheUse::read_write));
  check(off.cache_observation().disposition == ps::CacheDisposition::disabled && !off.cache_binding() &&
      disabled.statistics() == ps::CacheStatistics{}, "C05 disabled cache did work or published entries");
  for (bool key : {false, true}) {
    auto tiny = ps::PlanCache::create({1, key ? 1U : 8U * 1024U * 1024U, key ? 32U * 1024U * 1024U : 1U});
    const auto result = ps::select(snapshot, source, height, {}, &tiny, ps::CacheUse::read_write);
    check(!result.selection && result.stop == ps::Stop::resource_limit && result.resource ==
        (key ? ps::Resource::cache_key_bytes : ps::Resource::cache_plan_payload) && tiny.statistics() == ps::CacheStatistics{},
        "C05 oversized entry silently bypassed cache or changed counters");
  }
  // A separately replayed, byte-identical original proof must remain the new
  // result's proof even when the compiled artifact can be reused.
  auto exact_cache = ps::PlanCache::create();
  const auto old = complete(ps::select(snapshot, source, height, {}, &exact_cache, ps::CacheUse::read_write));
  const auto new_proof = replay(snapshot.original_proof(), false); const auto new_family = family(new_proof);
  const auto fresh = complete(ps::select(new_family, source, height, {}, &exact_cache, ps::CacheUse::read_only));
  check(fresh.cache_observation().disposition == ps::CacheDisposition::hit &&
      &fresh.snapshot().original_proof().certificate() == &new_proof.certificate() &&
      &fresh.snapshot().original_proof().certificate() != &old.snapshot().original_proof().certificate(),
      "C05 cache transplanted an old proof");
  const auto renamed_proof = replay(snapshot.original_proof(), true); const auto renamed = family(renamed_proof);
  const auto distinct = complete(ps::select(renamed, source, height, {}, &exact_cache, ps::CacheUse::read_only));
  check(distinct.selected().structural_key() == old.selected().structural_key() && distinct.cache_binding() != old.cache_binding() &&
      distinct.cache_observation().disposition == ps::CacheDisposition::miss_read_only, "C05 erased raw family representation in cache key");
  const auto partial = prefix(snapshot.original_proof());
  const auto partial_choice = complete(ps::select(partial, source, height, {}, &exact_cache, ps::CacheUse::read_only));
  check(partial_choice.cache_binding() != old.cache_binding() && !partial_choice.snapshot().family_exhausted(), "C05 family key erased retained prefix");
  std::cout << "C05 whole-artifact FIFO, read-only reuse, lifetime, counter/capacity and exact-family/proof cache cases passed\n";
} catch (const std::exception& error) { std::cerr << error.what() << '\n'; return 1; } }

```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Exercise FIFO behavior, full-key cache identity, replay, and failure counters. |
| inputs / outputs | Runs bounded family replay, cache hits/eviction/read-only cases, then injects counter overflow and checks disabled and one-under caches. |
| invariants | A depth/height hit may avoid the selected winner lower, but slot assessment has already lowered retained candidates; read-only misses count as misses without installing; cache counters cannot wrap. |
| ownership | Cache stores whole immutable plans; source/family/proof context stays with each returned Selection. |
| failure | Overflow fails transactionally; key/payload/candidate limits return explicit stops with unchanged cache image. |
| cost | Runs bounded replay and family enumeration helpers (each uses up to 100,000 advances of 1,000 work units), plus finite cold/hit, eviction, cap, overflow and proof-key comparisons. These are fixture guards, not bounds for arbitrary inputs. |
| Design | [tests/unit/selection_cache_test.cpp](../../../../../tests/unit/selection_cache_test.cpp), [include/crown/planner/selection.hpp](../../../../../include/crown/planner/selection.hpp), [src/planner/selection.cpp](../../../../../src/planner/selection.cpp), [docs/selection.md](../../../../selection.md), [docs/selection_accounting.md](../../../../selection_accounting.md), [src/planner/selection_cache.cpp](../../../../../src/planner/selection_cache.cpp), [src/planner/selection_binding.cpp](../../../../../src/planner/selection_binding.cpp), [tests/support/selection_independent_fixture.hpp](../../../../../tests/support/selection_independent_fixture.hpp) |
