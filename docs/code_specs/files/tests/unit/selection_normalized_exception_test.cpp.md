# `tests/unit/selection_normalized_exception_test.cpp` — block usage map

[Source](../../../../../tests/unit/selection_normalized_exception_test.cpp) · [Source index](../../../README.md) · [Subsystem contracts](../../../subsystem_contracts.md) · [Reviewed primitives](../../../primitives.md)

Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection.

Snapshot SHA-256: `940b32cea9b4814d958ca254fe6bbcc1bcd010e46005341d385d51a80ac748d0`. 44 lines partitioned into 2 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [tests](../../../subsystem_contracts.md#tests). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/code_review.md](../../../../code_review.md), [docs/reference_fuzz.md](../../../../reference_fuzz.md), [docs/task_ledger.md](../../../../task_ledger.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–2](../../../../../tests/unit/selection_normalized_exception_test.cpp#L1) | Imports dependencies. |  · [reviewed contract](#b0001) |
| [B0002 · 3–44](../../../../../tests/unit/selection_normalized_exception_test.cpp#L3) | Callable definition: int main() | calls frontend::bind_sql, check, frontend::normalize_sql, std::move; guard check(std::holds_alternative&lt;frontend::BoundSql&gt;(bound), "C05 normalized fault bind");; returns ps::select(snapshot, source, height, {}, &cache, ps::CacheUse::read_write); ps::select(snapshot, so…; growth insert · [reviewed contract](#b0002) |

## B0001

[Lines 1–2](../../../../../tests/unit/selection_normalized_exception_test.cpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L1-L2:sha256:a67c785f1a79d5b295addb1f5a94e676d3f5a3dae9250f53e23d1d398c8b502d
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Prepare selection_normalized_exception_test.cpp: include "selection_exception_support.hpp". |
| inputs / outputs | Compiler-visible dependencies, names and the recorded declarations in; declarations available to the following fixture/CLI/example definitions out. |
| invariants | Declarations are scoped to this source/header and its selected ABI. Included code has its own effects; names and editable fixture values do not confer proof, admission or publication authority. |
| ownership | Aliases/includes do not create a query owner. Pointers/references/views are non-owning. Containers own their elements, which can themselves be borrowed pointers or numeric IDs. Only documented owning shared-control handles retain controls; IDs/slot-handle values do not independently keep an arena/runtime alive. |
| failure | Missing headers, ill-formed names/types, failed static assertions or active #error directives stop compilation. No runtime rejection/rollback mechanism is implemented by aliases or function prototypes. |
| cost | Preprocessing and type/constraint instantiation cost compilation. Alias/prototype syntax does not invoke the declared operation; any included definitions keep their own initialization effects. |
| Design | [tests/unit/selection_normalized_exception_test.cpp](../../../../../tests/unit/selection_normalized_exception_test.cpp), [docs/selection.md](../../../../selection.md), [docs/code_review.md](../../../../code_review.md) |

## B0002

[Lines 3–44](../../../../../tests/unit/selection_normalized_exception_test.cpp#L3); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
int main() { try {
  using namespace c05_fault;
  const Catalog catalog{1, {{"R", {{"x", ScalarType::int64}}}}};
  const std::string sql = "SELECT DISTINCT a.x, a.x AS repeated FROM \"R\" AS a WHERE a.x >= 0";
  auto bound = frontend::bind_sql(sql, catalog);
  check(std::holds_alternative<frontend::BoundSql>(bound), "C05 normalized fault bind");
  auto normalized = frontend::normalize_sql(std::get<frontend::BoundSql>(bound));
  check(std::holds_alternative<frontend::NormalizedSql>(normalized), "C05 normalized fault normalize");
  const auto program = std::get<frontend::NormalizedSql>(std::move(normalized));
  const Fixture logical{program.core_catalog, program.core, {}}; const auto snapshot = c02_test::candidates(logical, 1, 1);
  check(snapshot.candidate_count() == 1, "C05 normalized unary family changed");
  const auto plan = planner::lower_normalized(program, snapshot.candidate(0)->tree());
  const Database database{{Relation{Row{std::int64_t{1}}, Row{std::int64_t{-1}}}}};
  auto owner = runtime::PhysicalRuntime::initialize(plan, database); owner.configure_workload_statistics(counters());
  const auto update = [&](SetOperation operation, std::int64_t value) {
    static_cast<void>(owner.apply({owner.sequence() + 1, TableId{0}, operation, Row{value}}));
  };
  update(SetOperation::insert, 1); update(SetOperation::insert, 2); update(SetOperation::erase, 2); update(SetOperation::erase, 3);
  check(owner.canonical_state().sources == database.tables && answers(owner) == Relation{Row{std::int64_t{1}, std::int64_t{1}}},
      "C05 normalized fault fixture changed source/output");
  const auto evidence = capture(snapshot, owner).inputs(); const ps::Source source = ps::PhysicalBasis{plan};
  Totals totals; const auto height = request(ps::Policy::height_only);
  sweep("C05 normalized winner replay/identity", snapshot, owner, source, evidence, [&](ps::PlanCache& cache) {
    return ps::select(snapshot, source, height, {}, &cache, ps::CacheUse::read_write);
  }, false, totals);
  auto both = request(ps::Policy::committed_input_native_depth); both.constraint = ps::TupleIndexSlotLimit{"13"};
  const auto literal = complete(ps::select(snapshot, source, both, evidence));
  check(assessment(literal, pr::Policy::tuple_index_slots).scores()[0].slots == "13" &&
      assessment(literal, pr::Policy::committed_input_native_depth).scores()[0].numerator == "4" &&
      assessment(literal, pr::Policy::committed_input_native_depth).scores()[0].denominator == "4",
      "C05 normalized literal constraint/depth oracle");
  sweep("C05 normalized two assessments", snapshot, owner, source, evidence, [&](ps::PlanCache& cache) {
    return ps::select(snapshot, source, both, evidence, &cache, ps::CacheUse::read_write);
  }, false, totals);
  sweep("C05 normalized actual current publication", snapshot, owner, source, evidence, [&](ps::PlanCache& cache) {
    return rs::select_current(snapshot, source, owner, both, {}, &cache, ps::CacheUse::read_write);
  }, false, totals);
  check(totals.publication_failures != 0 && totals.assessment_failures != 0 && totals.lowering_failures != 0,
      "C05 normalized fault sweep missed lower/assessment/publication");
  std::cout << "C05 normalized persistent positions=" << totals.positions << " recovered_cleanup_positions=" << totals.recovered
      << "; owned replay/source/identity/cache/late wrapper preserved\n";
} catch (const std::exception& error) { std::cerr << error.what() << '\n'; return 1; } }

```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Fault-sweep normalized selection and fresh-current wrapper exception safety. |
| inputs / outputs | Builds a DISTINCT/repeated-output normalized SQL fixture, performs four update attempts, then sweeps height-only selection, pure dual assessment, and dual current selection. The final current-selection call includes its evidence capture; no separate capture sweep runs. |
| invariants | Each measured call either returns the same complete bundle as its baseline (cleanup may recover) or an allowed allocation/lowering stop; earlier owner/workload/snapshot/cache/results remain unchanged, and each full sweep is followed by a successful retry. |
| ownership | Global new counter/fault injector is test-only; source owner, Evidence and previous result are comparison baselines. |
| failure | Persistent failures injected through covered C++ new calls cannot publish partial Selection/cache state or change owner workload. The current-wrapper sweep includes capture; there is no separate capture-only phase or raw malloc/realloc sweep. |
| cost | Three finite C++ new sweeps cover height-only, pure dual assessment, and current dual selection including capture. Each measures its own call, tests every observed position, then retries; position counts are invocation-specific, not a fixed universal total. |
| Design | [tests/unit/selection_normalized_exception_test.cpp](../../../../../tests/unit/selection_normalized_exception_test.cpp), [include/crown/planner/selection.hpp](../../../../../include/crown/planner/selection.hpp), [src/planner/selection.cpp](../../../../../src/planner/selection.cpp), [docs/selection.md](../../../../selection.md), [docs/selection_accounting.md](../../../../selection_accounting.md), [include/crown/runtime/selection.hpp](../../../../../include/crown/runtime/selection.hpp), [src/runtime/selection.cpp](../../../../../src/runtime/selection.cpp), [tests/support/selection_independent_fixture.hpp](../../../../../tests/support/selection_independent_fixture.hpp), [tests/support/selection_exception_support.hpp](../../../../../tests/support/selection_exception_support.hpp) |
