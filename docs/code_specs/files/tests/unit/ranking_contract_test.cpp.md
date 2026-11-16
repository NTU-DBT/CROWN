# `tests/unit/ranking_contract_test.cpp` — block usage map

[Source](../../../../../tests/unit/ranking_contract_test.cpp) · [Source index](../../../README.md) · [Subsystem contracts](../../../subsystem_contracts.md) · [Reviewed primitives](../../../primitives.md)

Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection.

Snapshot SHA-256: `1c21557ea187d28dd5e03cfd3bc0cd04dbdc50cab97c55dfb8d974c5fbd7d725`. 44 lines partitioned into 2 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [tests](../../../subsystem_contracts.md#tests). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/code_review.md](../../../../code_review.md), [docs/reference_fuzz.md](../../../../reference_fuzz.md), [docs/task_ledger.md](../../../../task_ledger.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–6](../../../../../tests/unit/ranking_contract_test.cpp#L1) | Imports dependencies. |  · [reviewed contract](#b0001) |
| [B0002 · 7–44](../../../../../tests/unit/ranking_contract_test.cpp#L7) | Callable definition: int main() | calls static_assert, fixture, candidates, planner::lower_tree; guard static_assert(!std::is_default_constructible_v&lt;pr::Evidence&gt; && !std::is_default_constructible_v&lt;pr…; returns 1; growth insert; 5 loop sites · [reviewed contract](#b0002) |

## B0001

[Lines 1–6](../../../../../tests/unit/ranking_contract_test.cpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L1-L6:sha256:fccb536b818f037c2a27952b5fa81c3f12f95dcb0428bf356c2f0fc31828f388
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Prepare ranking_contract_test.cpp: include "ranking_fixture.hpp", "crown/runtime/ranking_evidence.hpp", &lt;array&gt;, &lt;iostream&gt;, &lt;type_traits&gt;. |
| inputs / outputs | Compiler-visible dependencies, names and the recorded declarations in; declarations available to the following fixture/CLI/example definitions out. |
| invariants | Declarations are scoped to this source/header and its selected ABI. Included code has its own effects; names and editable fixture values do not confer proof, admission or publication authority. |
| ownership | Aliases/includes do not create a query owner. Pointers/references/views are non-owning. Containers own their elements, which can themselves be borrowed pointers or numeric IDs. Only documented owning shared-control handles retain controls; IDs/slot-handle values do not independently keep an arena/runtime alive. |
| failure | Missing headers, ill-formed names/types, failed static assertions or active #error directives stop compilation. No runtime rejection/rollback mechanism is implemented by aliases or function prototypes. |
| cost | Preprocessing and type/constraint instantiation cost compilation. Alias/prototype syntax does not invoke the declared operation; any included definitions keep their own initialization effects. |
| Design | [tests/unit/ranking_contract_test.cpp](../../../../../tests/unit/ranking_contract_test.cpp), [docs/ranking.md](../../../../ranking.md), [docs/code_review.md](../../../../code_review.md) |

## B0002

[Lines 7–44](../../../../../tests/unit/ranking_contract_test.cpp#L7); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
int main(){try{
  using namespace c02_test;namespace pr=planner::ranking;namespace rr=runtime::ranking;
  static_assert(!std::is_default_constructible_v<pr::Evidence> && !std::is_default_constructible_v<pr::Result>);
  const auto f=fixture();const auto set=candidates(f);const auto plan=planner::lower_tree(f.catalog,f.query,set.candidate(0)->tree());
  auto owner=runtime::PhysicalRuntime::initialize(plan,f.database);
  auto off=rr::capture(set,owner);check(off.evidence.has_value(),"disabled evidence missing");
  check(off.evidence->inputs().plan().account().statistics().owner==owner.accounted_memory_statistics().owner &&
    owner.source_layout(TableId{0}).same_token(off.evidence->inputs().plan().sources()[0].layout),
    "ranking evidence copied the program or created another query account");
  check(off.evidence->inputs().memory_reasons()==0 && off.evidence->inputs().depth_reasons()!=0,"state/workload availability collapsed");
  const auto eligible=rr::revalidate(*off.evidence,owner);check(eligible.boundary==0 && eligible.usable(pr::Policy::tuple_index_slots) && !eligible.usable(pr::Policy::committed_input_native_depth),"policy revalidation collapsed");
  pr::Request memory;memory.policy=pr::Policy::tuple_index_slots;const auto m=pr::rank(set,memory,off.evidence->inputs());
  check(m.result && m.evaluated==3,"memory ranking incomplete");
  for(const auto& score:m.result->scores()){check(score.slots==(shape(score.candidate.tree())==0?"24":"32"),"literal slot oracle mismatch");check(!score.slot_terms.empty() && !score.populations.empty() && score.modeled_plan.has_value(),"slot derivation missing");}
  check(shape(m.result->selected().tree())==0,"memory preferred wrong shape");
  runtime::workload::Options collect;collect.mode=runtime::workload::Mode::counters;collect.period=64;collect.detail_budget=0;owner.configure_workload_statistics(collect);
  for(std::size_t table=0;table<3;++table){const std::size_t n=table==0?90:5;for(std::size_t i=0;i<n;++i){static_cast<void>(owner.apply({owner.sequence()+1,TableId{table},SetOperation::insert,*f.database.tables[table].begin()}));}}
  auto facts=rr::capture(set,owner);check(facts.evidence && facts.evidence->inputs().depth_reasons()==0,"sample/truncation invalidated census");
  pr::Request depth;depth.policy=pr::Policy::committed_input_native_depth;
  const auto d=pr::rank(set,depth,facts.evidence->inputs());check(d.result && d.evaluated==3,"depth ranking incomplete");
  const std::array<std::string,3> expected{"195","105","190"};
  for(const auto& score:d.result->scores()){check(score.numerator==expected[static_cast<std::size_t>(shape(score.candidate.tree()))] && score.denominator=="100","literal depth oracle mismatch");check(score.depths.size()==3 && score.table_depths.size()==3,"depth derivation missing");}
  check(shape(d.result->selected().tree())==1 && owner.has_answer(),"hot-R ranking or semantics");
  auto tiny=depth;tiny.limits.score_bits=1;tiny.fallback=pr::Fallback::height_only;
  const auto failed=pr::rank(set,tiny,facts.evidence->inputs());check(failed.stop==pr::Stop::bit_limit && !failed.result,"resource stop invoked fallback");
  auto work=memory;work.limits.lowering_work=0;const auto lower_stop=pr::rank(set,work,off.evidence->inputs());check(!lower_stop.result && lower_stop.stop==pr::Stop::lowering_limit,"lowering cap ignored");
  owner.reset_workload_statistics();const auto old=rr::revalidate(*facts.evidence,owner);
  check(old.boundary==0 && old.usable(pr::Policy::tuple_index_slots) && !old.usable(pr::Policy::committed_input_native_depth),"reset conflated state and interval freshness");
  const auto immutable=pr::rank(set,depth,facts.evidence->inputs());check(immutable.result && immutable.result->selected().structural_key()==d.result->selected().structural_key(),"as-of artifact changed on reset");
  const auto empty=rr::rank_current(set,owner,depth);check(empty.stop==pr::Stop::evidence_unavailable && !empty.result,"empty current interval reused old weights");
  depth.fallback=pr::Fallback::height_only;const auto fallback=rr::rank_current(set,owner,depth);check(fallback.result && fallback.result->effective_policy()==pr::Policy::height_only && fallback.result->fallback_reasons()!=0,"explicit fallback missing");
  auto pending=owner.prepare({owner.sequence()+1,TableId{0},SetOperation::insert,Row{std::int64_t{2}}});const auto p=rr::capture(set,owner);
  check(p.evidence && (p.evidence->inputs().memory_reasons()&pr::reason(pr::Reason::pending)),"pending state was exposed");pending.rollback();
  auto foreign=owner.rebuilt();check(rr::revalidate(*facts.evidence,foreign).boundary&pr::reason(pr::Reason::foreign_owner),"rebuilt owner was accepted as current");
  const auto h=pr::rank(set);check(h.result && h.result->scores().size()==3,"pure height ranking");
  for(const auto& score:h.result->scores()){check(score.structural_key>=h.result->selected().structural_key(),"height tie not full key order");}
  std::cout<<"C02 contract: typed complete-set policies, terms, current/as-of, caps passed\n";
}catch(const std::exception& e){std::cerr<<e.what()<<'\n';return 1;}}

```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Verify public ranking contracts for actual captures, resource stops, and historical evidence. |
| inputs / outputs | Builds fixture owners, captures evidence, ranks retained candidates under depth/slot/height policies and finite caps, then checks pending/foreign/stale boundaries. |
| invariants | Exact denominator and numerator facts are checked from finite updates; failed score-bit assessment has no height fallback, while explicit height request works; reset does not rewrite old as-of evidence. |
| ownership | Evidence and Result own immutable account-backed snapshots; owner remains external and can advance independently. |
| failure | Pending or foreign capture is unavailable; resource failure publishes no partial winner; ordinary check failures throw. |
| cost | Finite counter updates include 90 R plus 5 each S/T in the root-depth case and separate policy/cap attempts; ranking iterates the retained 3-candidate family. |
| Design | [tests/unit/ranking_contract_test.cpp](../../../../../tests/unit/ranking_contract_test.cpp), [include/crown/planner/ranking.hpp](../../../../../include/crown/planner/ranking.hpp), [docs/ranking.md](../../../../ranking.md), [docs/ranking_accounting.md](../../../../ranking_accounting.md), [include/crown/runtime/ranking_evidence.hpp](../../../../../include/crown/runtime/ranking_evidence.hpp), [src/runtime/ranking_evidence.cpp](../../../../../src/runtime/ranking_evidence.cpp) |
