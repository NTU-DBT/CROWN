# `tests/unit/selection_backend_binding_test.cpp` — block usage map

[Source](../../../../../tests/unit/selection_backend_binding_test.cpp) · [Source index](../../../README.md) · [Subsystem contracts](../../../subsystem_contracts.md) · [Reviewed primitives](../../../primitives.md)

Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection.

Snapshot SHA-256: `f093624b4f0a7296557240b6e9fbba2f9945de6e08cf750168cd541bc5b0ad25`. 69 lines partitioned into 6 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [tests](../../../subsystem_contracts.md#tests). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/code_review.md](../../../../code_review.md), [docs/reference_fuzz.md](../../../../reference_fuzz.md), [docs/task_ledger.md](../../../../task_ledger.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–9](../../../../../tests/unit/selection_backend_binding_test.cpp#L1) | Imports dependencies; declares namespace scope; declares aliases. |  · [reviewed contract](#b0001) |
| [B0002 · 10–15](../../../../../tests/unit/selection_backend_binding_test.cpp#L10) | Callable definition: PhysicalOptions options() | calls ; returns value · [reviewed contract](#b0002) |
| [B0003 · 16–23](../../../../../tests/unit/selection_backend_binding_test.cpp#L16) | Callable definition: s::Selection select(const p::CandidateSnapshot& family,const s::Source& source,s::PlanCache& cache) | calls s::select, std::runtime_error, std::to_string; returns *attempt.selection · [reviewed contract](#b0003) |
| [B0004 · 24–43](../../../../../tests/unit/selection_backend_binding_test.cpp#L24) | Callable definition: void check_source(const p::CandidateSnapshot& family,const s::Source& source,const PhysicalOptions& expected, s::PlanCache& cache… | calls statistics, select, check, cache_observation; guard check(first.cache_observation().disposition==s::CacheDisposition::inserted && first.cache_binding()…; growth insert · [reviewed contract](#b0004) |
| [B0005 · 44–45](../../../../../tests/unit/selection_backend_binding_test.cpp#L44) | Closes surrounding scope/type. | source comment (unverified): // namespace · [reviewed contract](#b0005) |
| [B0006 · 46–69](../../../../../tests/unit/selection_backend_binding_test.cpp#L46) | Callable definition: int main() | calls candidates, check, candidate_count, candidate; guard const auto family=candidates(catalog,query);check(family.candidate_count()==1,"single-input literal…; 3 loop sites · [reviewed contract](#b0006) |

## B0001

[Lines 1–9](../../../../../tests/unit/selection_backend_binding_test.cpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L1-L9:sha256:7b14b95aebc1db6938add86956f32e897d19584e5566b2746f745eb7c505b717
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Prepare selection_backend_binding_test.cpp: include "selection_independent_fixture.hpp", "crown/io/physical.hpp", &lt;iostream&gt;, &lt;set&gt;; bind local aliases/name imports. |
| inputs / outputs | Compiler-visible dependencies, names and the recorded declarations in; declarations available to the following fixture/CLI/example definitions out. |
| invariants | Declarations are scoped to this source/header and its selected ABI. Included code has its own effects; names and editable fixture values do not confer proof, admission or publication authority. |
| ownership | Aliases/includes do not create a query owner. Pointers/references/views are non-owning. Containers own their elements, which can themselves be borrowed pointers or numeric IDs. Only documented owning shared-control handles retain controls; IDs/slot-handle values do not independently keep an arena/runtime alive. |
| failure | Missing headers, ill-formed names/types, failed static assertions or active #error directives stop compilation. No runtime rejection/rollback mechanism is implemented by aliases or function prototypes. |
| cost | Preprocessing and type/constraint instantiation cost compilation. Alias/prototype syntax does not invoke the declared operation; any included definitions keep their own initialization effects. |
| Design | [tests/unit/selection_backend_binding_test.cpp](../../../../../tests/unit/selection_backend_binding_test.cpp), [docs/selection.md](../../../../selection.md), [docs/code_review.md](../../../../code_review.md) |

## B0002

[Lines 10–15](../../../../../tests/unit/selection_backend_binding_test.cpp#L10); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
PhysicalOptions options() {
  PhysicalOptions value;storage::IndexedBackendSpec spec;
  spec.per_table={9'007'199'254'740'993ULL,11,13,17,19,23,29,31,37};
  spec.per_operation={9'007'199'254'740'993ULL,41,43,47,53};
  value.indexed_storage=spec;return value;
}

```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Create indexed options with one large and otherwise distinct limit per domain. |
| inputs / outputs | Returns PhysicalOptions with nine per-table and five per-operation limits; the first in each group is 2^53+1. |
| invariants | Exact uint64 values, backend kind, and all distinct fields must survive selection/cache serialization. |
| ownership | Returned options own the optional backend spec. |
| failure | No domain failure path; value construction only. |
| cost | Builds a small options object; no backend operation is executed. |
| Design | [tests/unit/selection_backend_binding_test.cpp](../../../../../tests/unit/selection_backend_binding_test.cpp), [include/crown/planner/selection.hpp](../../../../../include/crown/planner/selection.hpp), [src/planner/selection.cpp](../../../../../src/planner/selection.cpp), [docs/selection.md](../../../../selection.md), [docs/selection_accounting.md](../../../../selection_accounting.md) |

## B0003

[Lines 16–23](../../../../../tests/unit/selection_backend_binding_test.cpp#L16); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
s::Selection select(const p::CandidateSnapshot& family,const s::Source& source,s::PlanCache& cache) {
  s::Request request;request.policy=s::Policy::height_only;
  const auto attempt=s::select(family,source,request,{},&cache,s::CacheUse::read_write);
  if (attempt.stop!=s::Stop::complete || !attempt.selection)
    throw std::runtime_error("backend selection failed: stop="+std::to_string(static_cast<unsigned>(attempt.stop))+
        " stage="+std::to_string(static_cast<unsigned>(attempt.stage)));
  return *attempt.selection;
}

```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Run a height-only read-write selection and return the owning result. |
| inputs / outputs | Passes family/source/cache to select; returns the retained Selection or throws with stop/stage diagnostics. |
| invariants | It does not assume an error-free result; both stop and missing optional result are checked. |
| ownership | Family/source/cache are borrowed; returned Selection retains its result and cache-linked plan handles. |
| failure | Non-complete stop throws runtime_error with numeric stop/stage. |
| cost | One full selection call including fresh admission, binding/ranking, cache lookup/insert, and possibly lower. |
| Design | [tests/unit/selection_backend_binding_test.cpp](../../../../../tests/unit/selection_backend_binding_test.cpp), [include/crown/planner/selection.hpp](../../../../../include/crown/planner/selection.hpp), [src/planner/selection.cpp](../../../../../src/planner/selection.cpp), [docs/selection.md](../../../../selection.md), [docs/selection_accounting.md](../../../../selection_accounting.md) |

## B0004

[Lines 24–43](../../../../../tests/unit/selection_backend_binding_test.cpp#L24); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
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

```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Check one exact backend source cold insertion and warm cache hit. |
| inputs / outputs | Runs selection twice, verifies backend options/label/hash, unique cache binding and counter deltas, and round-trips the physical artifact. |
| invariants | A cache hit must return the same compiled backend artifact; each supported option vector has a distinct binding; set insertion success is explicitly checked. |
| ownership | Cache and family are borrowed; both returned Selection values retain their immutable plan. |
| failure | Any wrong disposition, duplicate binding, lost option, or format mismatch raises the fixture failure. |
| cost | Two selection calls, three physical JSON serializations and one parse/replay per source; string and set checks also retain the binding. |
| Design | [tests/unit/selection_backend_binding_test.cpp](../../../../../tests/unit/selection_backend_binding_test.cpp), [include/crown/planner/selection.hpp](../../../../../include/crown/planner/selection.hpp), [src/planner/selection.cpp](../../../../../src/planner/selection.cpp), [docs/selection.md](../../../../selection.md), [docs/selection_accounting.md](../../../../selection_accounting.md) |

## B0005

[Lines 44–45](../../../../../tests/unit/selection_backend_binding_test.cpp#L44); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L44-L45:sha256:c2bd7638f09d52cb034ed574f539304035fc6fab162bf8d5fa20a35d8c7288a1
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Close the recorded declaration scopes in selection_backend_binding_test.cpp: namespace (anonymous). |
| inputs / outputs | Preceding namespace, type or initializer declarations in; completed lexical boundary out. |
| invariants | Brace-opening context is recorded in root-scope-context-v1.json. These are declaration/initializer boundaries, not an independent update, validation or recovery operation. |
| ownership | Enclosing objects and borrowed fields keep their declared ownership. This punctuation creates no new owner. |
| failure | Malformed scope syntax is a compile error. Any initializer/constructor failure belongs to the enclosing object declaration. |
| cost | No separate loop, guard or engine call is introduced by the delimiter; enclosing initialization and object lifetime still have their actual costs. |
| Design | [tests/unit/selection_backend_binding_test.cpp](../../../../../tests/unit/selection_backend_binding_test.cpp), [docs/selection.md](../../../../selection.md), [docs/code_review.md](../../../../code_review.md) |

## B0006

[Lines 46–69](../../../../../tests/unit/selection_backend_binding_test.cpp#L46); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
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

```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Exercise direct and physical-basis backend cache namespaces. |
| inputs / outputs | Builds one-candidate family, then tests reference and indexed options plus 14 one-field variants for both DirectCQ and PhysicalBasis sources. |
| invariants | For each source tag, reference options, the indexed base and all 14 one-field increments have distinct cache bindings. Only rows and structural_steps start at 2^53+1; all 32 configurations are checked cold and warm. |
| ownership | A single PlanCache owns retained compiled artifacts; returned results are temporary handles. |
| failure | The main has no enclosing try/catch; assertion or preparation exceptions propagate out and fail the executable. |
| cost | 32 source/configuration pairs are checked cold and warm (64 selection calls), with physical-format round trips; the varied limits are logical option identities, not work counters. |
| Design | [tests/unit/selection_backend_binding_test.cpp](../../../../../tests/unit/selection_backend_binding_test.cpp), [include/crown/planner/selection.hpp](../../../../../include/crown/planner/selection.hpp), [src/planner/selection.cpp](../../../../../src/planner/selection.cpp), [docs/selection.md](../../../../selection.md), [docs/selection_accounting.md](../../../../selection_accounting.md) |
