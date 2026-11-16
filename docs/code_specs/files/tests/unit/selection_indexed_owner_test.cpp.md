# `tests/unit/selection_indexed_owner_test.cpp` — block usage map

[Source](../../../../../tests/unit/selection_indexed_owner_test.cpp) · [Source index](../../../README.md) · [Subsystem contracts](../../../subsystem_contracts.md) · [Reviewed primitives](../../../primitives.md)

Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection.

Snapshot SHA-256: `69d8ac1badb45262d1d99842f868ec39deea1032267c77a4edcb13ada0c5e3b6`. 101 lines partitioned into 8 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [tests](../../../subsystem_contracts.md#tests). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/code_review.md](../../../../code_review.md), [docs/reference_fuzz.md](../../../../reference_fuzz.md), [docs/task_ledger.md](../../../../task_ledger.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–12](../../../../../tests/unit/selection_indexed_owner_test.cpp#L1) | Imports dependencies; declares namespace scope; declares aliases. |  · [reviewed contract](#b0001) |
| [B0002 · 13–16](../../../../../tests/unit/selection_indexed_owner_test.cpp#L13) | Callable definition: PhysicalPlan with_options(const PhysicalPlan& basis,const PhysicalOptions& options) | calls normalized, planner::lower_normalized, tree, planner::lower_tree; returns basis.normalized() ? planner::lower_normalized(*basis.normalized(),basis.tree(),options) : · [reviewed contract](#b0002) |
| [B0003 · 17–67](../../../../../tests/unit/selection_indexed_owner_test.cpp#L17) | Callable definition: void verify_owner(const planner::CandidateSnapshot& family,const PhysicalPlan& basis,const auto& owner) | calls s::PlanCache::create, normalized, options, current::select_current; guard check(chosen.plan().options().indexed_storage==basis.options().indexed_storage &&; 4 loop sites · [reviewed contract](#b0003) |
| [B0004 · 68–75](../../../../../tests/unit/selection_indexed_owner_test.cpp#L68) | Callable definition: void owners(const planner::CandidateSnapshot& family,const PhysicalPlan& basis,const Database& database) | calls PhysicalRuntime::initialize, verify_owner, DeltaRuntime::initialize, QuerySession::create_typed · [reviewed contract](#b0004) |
| [B0005 · 76–84](../../../../../tests/unit/selection_indexed_owner_test.cpp#L76) | Callable definition: void direct() | calls candidates, candidate, planner::lower_tree, tree · [reviewed contract](#b0005) |
| [B0006 · 85–95](../../../../../tests/unit/selection_indexed_owner_test.cpp#L85) | Callable definition: void normalized() | calls frontend::bind_sql, frontend::normalize_sql, candidates, candidate · [reviewed contract](#b0006) |
| [B0007 · 96–96](../../../../../tests/unit/selection_indexed_owner_test.cpp#L96) | Closes surrounding scope/type. | source comment (unverified): // namespace · [reviewed contract](#b0007) |
| [B0008 · 97–101](../../../../../tests/unit/selection_indexed_owner_test.cpp#L97) | Callable definition: int main() | calls direct, normalized · [reviewed contract](#b0008) |

## B0001

[Lines 1–12](../../../../../tests/unit/selection_indexed_owner_test.cpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L1-L12:sha256:91ad4884cf53377fd6f86b6a07a04d2a02b875f2f6783904cbd78e90b6d70155
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Prepare selection_indexed_owner_test.cpp: include "selection_independent_fixture.hpp", "indexed_runtime_fixture.hpp", "crown/io/physical.hpp", "crown/runtime/session.hpp", &lt;array&gt;, &lt;iostream&gt;; bind local aliases/name imports. |
| inputs / outputs | Compiler-visible dependencies, names and the recorded declarations in; declarations available to the following fixture/CLI/example definitions out. |
| invariants | Declarations are scoped to this source/header and its selected ABI. Included code has its own effects; names and editable fixture values do not confer proof, admission or publication authority. |
| ownership | Aliases/includes do not create a query owner. Pointers/references/views are non-owning. Containers own their elements, which can themselves be borrowed pointers or numeric IDs. Only documented owning shared-control handles retain controls; IDs/slot-handle values do not independently keep an arena/runtime alive. |
| failure | Missing headers, ill-formed names/types, failed static assertions or active #error directives stop compilation. No runtime rejection/rollback mechanism is implemented by aliases or function prototypes. |
| cost | Preprocessing and type/constraint instantiation cost compilation. Alias/prototype syntax does not invoke the declared operation; any included definitions keep their own initialization effects. |
| Design | [tests/unit/selection_indexed_owner_test.cpp](../../../../../tests/unit/selection_indexed_owner_test.cpp), [docs/selection.md](../../../../selection.md), [docs/code_review.md](../../../../code_review.md) |

## B0002

[Lines 13–16](../../../../../tests/unit/selection_indexed_owner_test.cpp#L13); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
PhysicalPlan with_options(const PhysicalPlan& basis,const PhysicalOptions& options) {
  return basis.normalized() ? planner::lower_normalized(*basis.normalized(),basis.tree(),options) :
      planner::lower_tree(basis.catalog(),basis.query(),basis.tree(),options);
}

```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Rebuild a physical basis with replacement storage options. |
| inputs / outputs | Returns lower_tree or normalized lower result from basis catalog/query/tree and supplied PhysicalOptions. |
| invariants | Source shape and logical query stay fixed while backend limits vary. |
| ownership | Input basis is borrowed; returned PhysicalPlan owns its compiled program. |
| failure | Lowering error propagates; callers treat it as fixture failure. |
| cost | One lower per call, including normalized preparation where the basis is SQL-derived. |
| Design | [tests/unit/selection_indexed_owner_test.cpp](../../../../../tests/unit/selection_indexed_owner_test.cpp), [include/crown/planner/selection.hpp](../../../../../include/crown/planner/selection.hpp), [src/planner/selection.cpp](../../../../../src/planner/selection.cpp), [docs/selection.md](../../../../selection.md), [docs/selection_accounting.md](../../../../selection_accounting.md), [include/crown/runtime/selection.hpp](../../../../../include/crown/runtime/selection.hpp), [src/runtime/selection.cpp](../../../../../src/runtime/selection.cpp), [tests/support/selection_independent_fixture.hpp](../../../../../tests/support/selection_independent_fixture.hpp) |

## B0003

[Lines 17–67](../../../../../tests/unit/selection_indexed_owner_test.cpp#L17); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
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

```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Check actual-owner indexed selection and rejection without cache mutation. |
| inputs / outputs | For each owner/source pair, checks accepted height/slot source combinations, then nine per-table limits, five per-operation limits and one reference-backend mismatch. Direct source accepts four policy/source combinations; normalized source accepts two because core-only source is ineligible. |
| invariants | Only indexed-compatible exact options are accepted; rejected changes preserve cache statistics; normalized core-only source cannot stand in for a physical basis. |
| ownership | Owner/source/cache borrowed exclusively; successful Selection keeps its plan/Evidence, not mutable owner state. |
| failure | Direct or normalized binding mismatch, unsupported source, and rejected option combinations produce explicit stops and leave cache unchanged. |
| cost | For one supplied owner and basis, performs four cold/hit accepted source-policy pairs for direct input or two for normalized input, then checks 15 rejected variants (nine per-table, five per-operation, one reference-backend mismatch). The callers combine six owner/basis verifications overall. |
| Design | [tests/unit/selection_indexed_owner_test.cpp](../../../../../tests/unit/selection_indexed_owner_test.cpp), [include/crown/planner/selection.hpp](../../../../../include/crown/planner/selection.hpp), [src/planner/selection.cpp](../../../../../src/planner/selection.cpp), [docs/selection.md](../../../../selection.md), [docs/selection_accounting.md](../../../../selection_accounting.md), [include/crown/runtime/selection.hpp](../../../../../include/crown/runtime/selection.hpp), [src/runtime/selection.cpp](../../../../../src/runtime/selection.cpp), [tests/support/selection_independent_fixture.hpp](../../../../../tests/support/selection_independent_fixture.hpp) |

## B0004

[Lines 68–75](../../../../../tests/unit/selection_indexed_owner_test.cpp#L68); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void owners(const planner::CandidateSnapshot& family,const PhysicalPlan& basis,const Database& database) {
  auto physical=PhysicalRuntime::initialize(basis,database);verify_owner(family,basis,physical);
  DeltaOptions delta;delta.mode=DeltaMode::delta;delta.completion=DeltaCompletion::anchored;
  auto maintained=DeltaRuntime::initialize(basis,database,delta);verify_owner(family,basis,maintained);
  SessionOptions options;options.delta=delta;
  auto session=QuerySession::create_typed(basis,database,io::QueueLimits{},options);session->start();
  verify_owner(family,basis,*session);
}

```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Check one supplied indexed basis using PhysicalRuntime, DeltaRuntime and QuerySession owners. |
| inputs / outputs | Calls verify_owner for each supported owner against one basis/family. |
| invariants | Each owner’s actual physical binding and indexed options must agree; a core-only normalized binding is not treated as equivalent. |
| ownership | Database/family/basis borrowed; runtime owner and cache stay live only within the scenario. |
| failure | Any binding/backend/counter mismatch throws the test assertion. |
| cost | For one supplied basis/family/database, initializes Physical, Delta and Session owners and calls verify_owner once for each. direct() and normalized() invoke this helper separately for their respective basis, yielding six verifications at top level. |
| Design | [tests/unit/selection_indexed_owner_test.cpp](../../../../../tests/unit/selection_indexed_owner_test.cpp), [include/crown/planner/selection.hpp](../../../../../include/crown/planner/selection.hpp), [src/planner/selection.cpp](../../../../../src/planner/selection.cpp), [docs/selection.md](../../../../selection.md), [docs/selection_accounting.md](../../../../selection_accounting.md), [include/crown/runtime/selection.hpp](../../../../../include/crown/runtime/selection.hpp), [src/runtime/selection.cpp](../../../../../src/runtime/selection.cpp), [tests/support/selection_independent_fixture.hpp](../../../../../tests/support/selection_independent_fixture.hpp) |

## B0005

[Lines 76–84](../../../../../tests/unit/selection_indexed_owner_test.cpp#L76); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void direct() {
  const Catalog catalog{1,{{"r",{{"x",ScalarType::int64},{"ignored",ScalarType::string}}}}};
  const Query query{{{"x",ScalarType::int64}},{{"r",TableId{0},{VariableId{0},IgnoredColumn{}}}},{{VariableId{0},"x"}},false};
  const auto family=candidates(catalog,query);const auto member=*family.candidate(0);
  const auto basis=planner::lower_tree(catalog,query,member.tree(),s04_runtime::options());
  const Database database{{Relation{Row{std::int64_t{9'007'199'254'740'993LL},std::string("a")},
      Row{std::int64_t{9'007'199'254'740'993LL},std::string("b")}}}};
  owners(family,basis,database);
}

```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Prepare the direct core-query fixture for indexed owner checks. |
| inputs / outputs | Builds catalog/query/family and unnormalized physical basis, then delegates to owners. |
| invariants | The direct source is bound to the original proof catalog/query. |
| ownership | Fixture objects remain alive through all owner checks. |
| failure | Preparation and lower failures abort the group. |
| cost | One fixture and its finite owner variants. |
| Design | [tests/unit/selection_indexed_owner_test.cpp](../../../../../tests/unit/selection_indexed_owner_test.cpp), [include/crown/planner/selection.hpp](../../../../../include/crown/planner/selection.hpp), [src/planner/selection.cpp](../../../../../src/planner/selection.cpp), [docs/selection.md](../../../../selection.md), [docs/selection_accounting.md](../../../../selection_accounting.md), [include/crown/runtime/selection.hpp](../../../../../include/crown/runtime/selection.hpp), [src/runtime/selection.cpp](../../../../../src/runtime/selection.cpp), [tests/support/selection_independent_fixture.hpp](../../../../../tests/support/selection_independent_fixture.hpp) |

## B0006

[Lines 85–95](../../../../../tests/unit/selection_indexed_owner_test.cpp#L85); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
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

```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Prepare normalized SQL and its physical basis for indexed owner checks. |
| inputs / outputs | Compiles normalized SQL with a Boolean flag filter and repeated output l.x, then creates the candidate family, lowers member zero with indexed options, and passes that basis/database to owners. No ignored output field is present. |
| invariants | Normalized binding identity is required; a semantically similar core CQ cannot replace it. |
| ownership | Basis and source text are owned for test duration. |
| failure | SQL preparation or lower failure aborts the group. |
| cost | One normalized compilation plus finite owner variants. |
| Design | [tests/unit/selection_indexed_owner_test.cpp](../../../../../tests/unit/selection_indexed_owner_test.cpp), [include/crown/planner/selection.hpp](../../../../../include/crown/planner/selection.hpp), [src/planner/selection.cpp](../../../../../src/planner/selection.cpp), [docs/selection.md](../../../../selection.md), [docs/selection_accounting.md](../../../../selection_accounting.md), [include/crown/runtime/selection.hpp](../../../../../include/crown/runtime/selection.hpp), [src/runtime/selection.cpp](../../../../../src/runtime/selection.cpp), [tests/support/selection_independent_fixture.hpp](../../../../../tests/support/selection_independent_fixture.hpp) |

## B0007

[Lines 96–96](../../../../../tests/unit/selection_indexed_owner_test.cpp#L96); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L96-L96:sha256:c7bfe2f3de133d78a2bc8bb1c4a08450563986ee8254facee698e1dcc57e8162
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Close the recorded declaration scopes in selection_indexed_owner_test.cpp: namespace (anonymous). |
| inputs / outputs | Preceding namespace, type or initializer declarations in; completed lexical boundary out. |
| invariants | Brace-opening context is recorded in root-scope-context-v1.json. These are declaration/initializer boundaries, not an independent update, validation or recovery operation. |
| ownership | Enclosing objects and borrowed fields keep their declared ownership. This punctuation creates no new owner. |
| failure | Malformed scope syntax is a compile error. Any initializer/constructor failure belongs to the enclosing object declaration. |
| cost | No separate loop, guard or engine call is introduced by the delimiter; enclosing initialization and object lifetime still have their actual costs. |
| Design | [tests/unit/selection_indexed_owner_test.cpp](../../../../../tests/unit/selection_indexed_owner_test.cpp), [docs/selection.md](../../../../selection.md), [docs/code_review.md](../../../../code_review.md) |

## B0008

[Lines 97–101](../../../../../tests/unit/selection_indexed_owner_test.cpp#L97); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
int main() {
  direct();normalized();
  std::cout << "Actual indexed C01/C02/C05 owners: physical/delta/session, direct/normalized,"
      " height/slots policies, exact cache reuse and all14 backend limits plus reference mismatch passed\n";
}

```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Run both indexed source families. |
| inputs / outputs | Invokes direct() and normalized(). |
| invariants | The group keeps direct and normalized source-binding rules separate. |
| ownership | Fixture values and owners are local to direct()/normalized(); exceptions are not intercepted by main. |
| failure | Any assertion or preparation exception propagates out of main and fails the executable; main has no outer catch. |
| cost | direct() and normalized() each create three owner forms, for six verifications. Together they perform 18 cold insertions, 18 warm hits and 90 rejected mismatches; each accepted current-selection call captures afresh. |
| Design | [tests/unit/selection_indexed_owner_test.cpp](../../../../../tests/unit/selection_indexed_owner_test.cpp), [include/crown/planner/selection.hpp](../../../../../include/crown/planner/selection.hpp), [src/planner/selection.cpp](../../../../../src/planner/selection.cpp), [docs/selection.md](../../../../selection.md), [docs/selection_accounting.md](../../../../selection_accounting.md), [include/crown/runtime/selection.hpp](../../../../../include/crown/runtime/selection.hpp), [src/runtime/selection.cpp](../../../../../src/runtime/selection.cpp), [tests/support/selection_independent_fixture.hpp](../../../../../tests/support/selection_independent_fixture.hpp) |
