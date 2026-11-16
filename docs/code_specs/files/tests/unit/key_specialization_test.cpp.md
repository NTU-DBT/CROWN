# `tests/unit/key_specialization_test.cpp` — block usage map

[Source](../../../../../tests/unit/key_specialization_test.cpp) · [Source index](../../../README.md) · [Subsystem contracts](../../../subsystem_contracts.md) · [Reviewed primitives](../../../primitives.md)

Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection.

Snapshot SHA-256: `73e6dea39c3e1362041486afe241e3305d8ab1efd0345d2b9d6cafdd2bb5e585`. 355 lines partitioned into 33 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [tests](../../../subsystem_contracts.md#tests). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/code_review.md](../../../../code_review.md), [docs/reference_fuzz.md](../../../../reference_fuzz.md), [docs/task_ledger.md](../../../../task_ledger.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–20](../../../../../tests/unit/key_specialization_test.cpp#L1) | Imports dependencies; declares namespace scope; declares aliases; declares values/defaults or compile-time conditions. |  · [reviewed contract](#b0001) |
| [B0002 · 21–21](../../../../../tests/unit/key_specialization_test.cpp#L21) | Callable definition: void check(bool value, const char* message) | calls std::runtime_error; guard void check(bool value, const char* message) { if (!value) throw std::runtime_error(message); ++chec… · [reviewed contract](#b0002) |
| [B0003 · 22–22](../../../../../tests/unit/key_specialization_test.cpp#L22) | Callable definition: Value n(std::int64_t value) | calls ; returns value · [reviewed contract](#b0003) |
| [B0004 · 23–23](../../../../../tests/unit/key_specialization_test.cpp#L23) | Callable definition: Term v(std::size_t value) | calls ; returns VariableId{value} · [reviewed contract](#b0004) |
| [B0005 · 24–24](../../../../../tests/unit/key_specialization_test.cpp#L24) | Type/record definition: struct Fixture |  · [reviewed contract](#b0005) |
| [B0006 · 25–25](../../../../../tests/unit/key_specialization_test.cpp#L25) | Callable definition: template&lt;class T&gt; concept RvalueBorrow = requires(T&& value) | calls execution · [reviewed contract](#b0006) |
| [B0007 · 26–30](../../../../../tests/unit/key_specialization_test.cpp#L26) | declares callable signatures; declares values/defaults or compile-time conditions. | guard static_assert(!RvalueBorrow&lt;keys::Plan&gt;);; source comment (unverified): // The removed parent introduces the lowest-ID private variable. Ordered and · [reviewed contract](#b0007) |
| [B0008 · 31–47](../../../../../tests/unit/key_specialization_test.cpp#L31) | Callable definition: Fixture base(bool private_payload = true) | calls v, push_back, erase, begin; returns f; growth push_back; 3 loop sites; source comment (unverified): // The removed parent introduces the lowest-ID private variable. Ordered and · [reviewed contract](#b0008) |
| [B0009 · 48–52](../../../../../tests/unit/key_specialization_test.cpp#L48) | Callable definition: PhysicalPlan lower(const Fixture& f, bool indexed) | calls planner::minimum_tree, check, has_value, planner::lower_tree; guard check(chosen.status==planner::OracleStatus::proven_minimum && chosen.tree.has_value(),"fixture has …; returns planner::lower_tree(f.catalog,f.query,*chosen.tree,indexed?s04_runtime::options():PhysicalOptions{}) · [reviewed contract](#b0009) |
| [B0010 · 53–57](../../../../../tests/unit/key_specialization_test.cpp#L53) | Callable definition: Relation results(const runtime::PhysicalRuntime& owner) | calls next, insert, storage::export_row, values; returns out; growth insert; 1 loop sites · [reviewed contract](#b0010) |
| [B0011 · 58–62](../../../../../tests/unit/key_specialization_test.cpp#L58) | Callable definition: template&lt;class Action&gt; void error(Action action, std::string_view code={}) | calls action, check, empty, code; guard try { action(); } catch (const Error& e) { refused=true;check(code.empty() \|\| e.code()==code,"wrong… · [reviewed contract](#b0011) |
| [B0012 · 63–89](../../../../../tests/unit/key_specialization_test.cpp#L63) | Callable definition: void provenance(const Fixture& f, const keys::Plan& plan) | calls execution, check, io::write_catalog_payload, general; guard check(io::write_catalog_payload(plan.general().source_catalog())==io::write_catalog_payload(executi…; growth insert; 3 loop sites · [reviewed contract](#b0012) |
| [B0013 · 90–97](../../../../../tests/unit/key_specialization_test.cpp#L90) | declares types or opens a type body; declares values/defaults or compile-time conditions. | source comment (unverified): // Compare both native routes to full materialization of the original CQ. Source · [reviewed contract](#b0013) |
| [B0014 · 98–102](../../../../../tests/unit/key_specialization_test.cpp#L98) | Callable definition: Trial(const Fixture& f,bool indexed,Database initial={}) : fixture(f),plan(keys::specialize(lower(f,indexed))), general(runtime::… | calls fixture, plan, keys::specialize, lower · [reviewed contract](#b0014) |
| [B0015 · 103–106](../../../../../tests/unit/key_specialization_test.cpp#L103) | Callable definition: static Database filled(const Fixture& f,Database value) | calls empty, resize, size; returns value; growth resize · [reviewed contract](#b0015) |
| [B0016 · 107–115](../../../../../tests/unit/key_specialization_test.cpp#L107) | Callable definition: void verify() | calls check, ready, sequence, snapshot; guard check(general.ready() && execution.ready(),"owner was left busy"); · [reviewed contract](#b0016) |
| [B0017 · 116–126](../../../../../tests/unit/key_specialization_test.cpp#L116) | Callable definition: std::pair&lt;runtime::PhysicalMetrics,runtime::PhysicalMetrics&gt; apply(std::size_t table,SetOperation operation,Row row,bool reject=f… | calls sequence, std::move, error, verify; returns {}; {a,b} · [reviewed contract](#b0017) |
| [B0018 · 127–128](../../../../../tests/unit/key_specialization_test.cpp#L127) | Closes surrounding scope/type. |  · [reviewed contract](#b0018) |
| [B0019 · 129–155](../../../../../tests/unit/key_specialization_test.cpp#L129) | Callable definition: void base_trace(bool indexed) | calls base, t, general, physical_sha256; guard check(t.plan.specialized() && t.plan.eliminations().size()==1,"base FK was not specialized");; growth insert, resize · [reviewed contract](#b0019) |
| [B0020 · 156–156](../../../../../tests/unit/key_specialization_test.cpp#L156) | Explanatory comments or spacing. |  |
| [B0021 · 157–186](../../../../../tests/unit/key_specialization_test.cpp#L157) | Callable definition: void guards(bool indexed) | calls base, clear, keys::specialize, lower; guard check(!plan.specialized() && plan.reason()==keys::Reason::no_match,"unproved metadata enabled rewri…; growth insert; 4 loop sites · [reviewed contract](#b0021) |
| [B0022 · 187–187](../../../../../tests/unit/key_specialization_test.cpp#L187) | Explanatory comments or spacing. |  |
| [B0023 · 188–213](../../../../../tests/unit/key_specialization_test.cpp#L188) | Callable definition: void literals_and_repetitions(bool indexed) | calls base, v, literal, check; guard Trial literal(f,indexed);check(literal.plan.specialized(),"matching FK literals rejected");provenan…; growth insert, push_back · [reviewed contract](#b0023) |
| [B0024 · 214–214](../../../../../tests/unit/key_specialization_test.cpp#L214) | Explanatory comments or spacing. |  |
| [B0025 · 215–239](../../../../../tests/unit/key_specialization_test.cpp#L215) | Callable definition: void composite_types(bool indexed) | calls size, push_back, std::to_string, v; guard Trial t(f,indexed);check(t.plan.specialized(),"mixed composite key rejected");provenance(f,t.plan);; growth insert, push_back; 2 loop sites · [reviewed contract](#b0025) |
| [B0026 · 240–240](../../../../../tests/unit/key_specialization_test.cpp#L240) | Explanatory comments or spacing. |  |
| [B0027 · 241–271](../../../../../tests/unit/key_specialization_test.cpp#L241) | Callable definition: void self_cycles_and_empty(bool indexed) | calls v, t, check, specialized; guard Trial t(self,indexed);check(t.plan.specialized() && t.plan.execution().base_routes()\[0\].size()==1,"…; growth insert, push_back · [reviewed contract](#b0027) |
| [B0028 · 272–272](../../../../../tests/unit/key_specialization_test.cpp#L272) | Explanatory comments or spacing. |  |
| [B0029 · 273–290](../../../../../tests/unit/key_specialization_test.cpp#L273) | Callable definition: void unselected_routes() | calls base, frontend::bind_sql, check, frontend::normalize_sql; guard check(std::holds_alternative&lt;frontend::BoundSql&gt;(binding),"SQL fixture did not bind"); · [reviewed contract](#b0029) |
| [B0030 · 291–293](../../../../../tests/unit/key_specialization_test.cpp#L291) | Explanatory comments or spacing. | source comment (unverified): // Cold refusals leave the general artifact intact. Sample cuts cover compiler · [reviewed contract](#b0030) |
| [B0031 · 294–343](../../../../../tests/unit/key_specialization_test.cpp#L294) | Callable definition: void resource_and_ownership(bool indexed) | calls base, lower, physical_sha256, keys::specialize; guard limits.work=warm.usage().work;check(keys::specialize(general,limits).specialized(),"exact guard wor…; growth allocate, emplace, insert; 2 loop sites; source comment (unverified): // Cold refusals leave the general artifact intact. Sample cuts cover compiler · [reviewed contract](#b0031) |
| [B0032 · 344–345](../../../../../tests/unit/key_specialization_test.cpp#L344) | Closes surrounding scope/type. | source comment (unverified): // namespace · [reviewed contract](#b0032) |
| [B0033 · 346–355](../../../../../tests/unit/key_specialization_test.cpp#L346) | Callable definition: int main() | calls base_trace, guards, literals_and_repetitions, composite_types; returns 1; 1 loop sites · [reviewed contract](#b0033) |

## B0001

[Lines 1–20](../../../../../tests/unit/key_specialization_test.cpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L1-L20:sha256:49ae29fec8c46b21ea8b398a38a1731778fe537fff025d638209ecb493cdc324
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Declare the unit executable and single-TU allocation interception dependencies. |
| inputs / outputs | Imports genuine key planning/runtime, the original materializing evaluator, backend selector and isolated allocation hooks; defines the local namespace/counter. |
| invariants | Allocation replacement belongs only to this executable and never a production library. |
| ownership | Test/driver-local fixtures and exports are caller-owned. Genuine compiler/runtime handles keep their documented immutable metadata, query account and cursor ownership; no production ownership layer is introduced. |
| failure | Explicit test checks or unexpected exceptions fail the executable. Expected Error/resource/allocation refusal is scoped by the helper/case and must not publish partial state; production failure behavior is not replaced. |
| cost | Explicit test-only compilation, fixture, full-state/cursor/proof or selected fault-cut costs. These checks add no production query-update instructions and make no elapsed-time improvement claim. |
| Design | [tests/unit/key_specialization_test.cpp](../../../../../tests/unit/key_specialization_test.cpp), [include/crown/planner/keys.hpp](../../../../../include/crown/planner/keys.hpp), [docs/key_specialization.md](../../../../key_specialization.md), [Refactor.md](../../../../../Refactor.md), [tests/reference/evaluator.cpp](../../../../../tests/reference/evaluator.cpp) |

## B0002

[Lines 21–21](../../../../../tests/unit/key_specialization_test.cpp#L21); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L21-L21:sha256:31821d91e3498be7d15b22c079ffb64927f25cfc15b82850beb31e0ffd2e8f1d
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Require one semantic/control observation and count accepted checks. |
| inputs / outputs | Boolean plus fixed failure message in; successful check count advances, or runtime_error fails the test. |
| invariants | Checks remain active under NDEBUG; counting is not native operation instrumentation. |
| ownership | Test/driver-local fixtures and exports are caller-owned. Genuine compiler/runtime handles keep their documented immutable metadata, query account and cursor ownership; no production ownership layer is introduced. |
| failure | Explicit test checks or unexpected exceptions fail the executable. Expected Error/resource/allocation refusal is scoped by the helper/case and must not publish partial state; production failure behavior is not replaced. |
| cost | Explicit test-only compilation, fixture, full-state/cursor/proof or selected fault-cut costs. These checks add no production query-update instructions and make no elapsed-time improvement claim. |
| Design | [tests/unit/key_specialization_test.cpp](../../../../../tests/unit/key_specialization_test.cpp), [include/crown/planner/keys.hpp](../../../../../include/crown/planner/keys.hpp), [docs/key_specialization.md](../../../../key_specialization.md), [Refactor.md](../../../../../Refactor.md), [tests/reference/evaluator.cpp](../../../../../tests/reference/evaluator.cpp) |

## B0003

[Lines 22–22](../../../../../tests/unit/key_specialization_test.cpp#L22); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L22-L22:sha256:4006044af303dbedbccb372e25c271007de9d117554a0fcd82dd6174f34aca88
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Construct an exact int64 fixture scalar. |
| inputs / outputs | int64 input becomes the same Value alternative. |
| invariants | No float conversion or string key is introduced. |
| ownership | Test/driver-local fixtures and exports are caller-owned. Genuine compiler/runtime handles keep their documented immutable metadata, query account and cursor ownership; no production ownership layer is introduced. |
| failure | Explicit test checks or unexpected exceptions fail the executable. Expected Error/resource/allocation refusal is scoped by the helper/case and must not publish partial state; production failure behavior is not replaced. |
| cost | Explicit test-only compilation, fixture, full-state/cursor/proof or selected fault-cut costs. These checks add no production query-update instructions and make no elapsed-time improvement claim. |
| Design | [tests/unit/key_specialization_test.cpp](../../../../../tests/unit/key_specialization_test.cpp), [include/crown/planner/keys.hpp](../../../../../include/crown/planner/keys.hpp), [docs/key_specialization.md](../../../../key_specialization.md), [Refactor.md](../../../../../Refactor.md), [tests/reference/evaluator.cpp](../../../../../tests/reference/evaluator.cpp) |

## B0004

[Lines 23–23](../../../../../tests/unit/key_specialization_test.cpp#L23); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L23-L23:sha256:9fe10801d85068c220c6a4b4bdacf963898842029be29ccd83ba5504f8fdb563
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Construct a fixture variable term from its numeric original ID. |
| inputs / outputs | size_t input becomes VariableId in Term. |
| invariants | IDs name the fixture query until the genuine optimizer returns a separate mapping. |
| ownership | Test/driver-local fixtures and exports are caller-owned. Genuine compiler/runtime handles keep their documented immutable metadata, query account and cursor ownership; no production ownership layer is introduced. |
| failure | Explicit test checks or unexpected exceptions fail the executable. Expected Error/resource/allocation refusal is scoped by the helper/case and must not publish partial state; production failure behavior is not replaced. |
| cost | Explicit test-only compilation, fixture, full-state/cursor/proof or selected fault-cut costs. These checks add no production query-update instructions and make no elapsed-time improvement claim. |
| Design | [tests/unit/key_specialization_test.cpp](../../../../../tests/unit/key_specialization_test.cpp), [include/crown/planner/keys.hpp](../../../../../include/crown/planner/keys.hpp), [docs/key_specialization.md](../../../../key_specialization.md), [Refactor.md](../../../../../Refactor.md), [tests/reference/evaluator.cpp](../../../../../tests/reference/evaluator.cpp) |

## B0005

[Lines 24–24](../../../../../tests/unit/key_specialization_test.cpp#L24); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L24-L24:sha256:246d49180ec13ace5da6a94ef5aa6b366fc2329840f73eaede649aaa9d3b0474
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Own one original catalog/query fixture. |
| inputs / outputs | Catalog and Query are independently mutable test inputs. |
| invariants | Their original source semantics remain the reference definition. |
| ownership | Test/driver-local fixtures and exports are caller-owned. Genuine compiler/runtime handles keep their documented immutable metadata, query account and cursor ownership; no production ownership layer is introduced. |
| failure | Explicit test checks or unexpected exceptions fail the executable. Expected Error/resource/allocation refusal is scoped by the helper/case and must not publish partial state; production failure behavior is not replaced. |
| cost | Explicit test-only compilation, fixture, full-state/cursor/proof or selected fault-cut costs. These checks add no production query-update instructions and make no elapsed-time improvement claim. |
| Design | [tests/unit/key_specialization_test.cpp](../../../../../tests/unit/key_specialization_test.cpp), [include/crown/planner/keys.hpp](../../../../../include/crown/planner/keys.hpp), [docs/key_specialization.md](../../../../key_specialization.md), [Refactor.md](../../../../../Refactor.md), [tests/reference/evaluator.cpp](../../../../../tests/reference/evaluator.cpp) |

## B0006

[Lines 25–25](../../../../../tests/unit/key_specialization_test.cpp#L25); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L25-L25:sha256:5d333244a89fe6dfe416a6da742439ec53b02a359c5f866917d9150d130d1283
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Check whether a temporary Plan exposes a borrowed execution reference. |
| inputs / outputs | Compile-time expression participation becomes a concept Boolean. |
| invariants | The deleted rvalue borrow must make this expression unavailable. |
| ownership | Test/driver-local fixtures and exports are caller-owned. Genuine compiler/runtime handles keep their documented immutable metadata, query account and cursor ownership; no production ownership layer is introduced. |
| failure | Explicit test checks or unexpected exceptions fail the executable. Expected Error/resource/allocation refusal is scoped by the helper/case and must not publish partial state; production failure behavior is not replaced. |
| cost | Explicit test-only compilation, fixture, full-state/cursor/proof or selected fault-cut costs. These checks add no production query-update instructions and make no elapsed-time improvement claim. |
| Design | [tests/unit/key_specialization_test.cpp](../../../../../tests/unit/key_specialization_test.cpp), [include/crown/planner/keys.hpp](../../../../../include/crown/planner/keys.hpp), [docs/key_specialization.md](../../../../key_specialization.md), [Refactor.md](../../../../../Refactor.md), [tests/reference/evaluator.cpp](../../../../../tests/reference/evaluator.cpp) |

## B0007

[Lines 26–30](../../../../../tests/unit/key_specialization_test.cpp#L26); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L26-L30:sha256:8406482578480f74b6c3175713bb2980747c5330212f47695b7f1bd3fbb91614
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Assert borrow/copy API safety and explain the provenance fixture. |
| inputs / outputs | Static assertions require safe temporary behavior and nothrow immutable handle copy; comments identify deliberate low-ID removal. |
| invariants | These compile checks prevent a dangling borrow regression, not runtime correctness by themselves. |
| ownership | Test/driver-local fixtures and exports are caller-owned. Genuine compiler/runtime handles keep their documented immutable metadata, query account and cursor ownership; no production ownership layer is introduced. |
| failure | Explicit test checks or unexpected exceptions fail the executable. Expected Error/resource/allocation refusal is scoped by the helper/case and must not publish partial state; production failure behavior is not replaced. |
| cost | Explicit test-only compilation, fixture, full-state/cursor/proof or selected fault-cut costs. These checks add no production query-update instructions and make no elapsed-time improvement claim. |
| Design | [tests/unit/key_specialization_test.cpp](../../../../../tests/unit/key_specialization_test.cpp), [include/crown/planner/keys.hpp](../../../../../include/crown/planner/keys.hpp), [docs/key_specialization.md](../../../../key_specialization.md), [Refactor.md](../../../../../Refactor.md), [tests/reference/evaluator.cpp](../../../../../tests/reference/evaluator.cpp) |

## B0008

[Lines 31–47](../../../../../tests/unit/key_specialization_test.cpp#L31); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L31-L47:sha256:59ef4003a8e0acee8fb930c2730f30219a9eb80f7820d7eb2724c3b586c08e4b
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Build the base enforced-FK fixture with nontrivial variable provenance. |
| inputs / outputs | Creates P/C, enforced UNIQUE/FK and ordered/repeated outputs; optional ignored payload compacts the fixture itself. |
| invariants | A fresh parent-private variable is removable; original output order and source IDs stay observable. |
| ownership | Test/driver-local fixtures and exports are caller-owned. Genuine compiler/runtime handles keep their documented immutable metadata, query account and cursor ownership; no production ownership layer is introduced. |
| failure | Explicit test checks or unexpected exceptions fail the executable. Expected Error/resource/allocation refusal is scoped by the helper/case and must not publish partial state; production failure behavior is not replaced. |
| cost | Explicit test-only compilation, fixture, full-state/cursor/proof or selected fault-cut costs. These checks add no production query-update instructions and make no elapsed-time improvement claim. |
| Design | [tests/unit/key_specialization_test.cpp](../../../../../tests/unit/key_specialization_test.cpp), [include/crown/planner/keys.hpp](../../../../../include/crown/planner/keys.hpp), [docs/key_specialization.md](../../../../key_specialization.md), [Refactor.md](../../../../../Refactor.md), [tests/reference/evaluator.cpp](../../../../../tests/reference/evaluator.cpp) |

## B0009

[Lines 48–52](../../../../../tests/unit/key_specialization_test.cpp#L48); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L48-L52:sha256:a033fa7cbf8c09e11c0a6225533367c92dcb03bde195798a344c24615ceb1b37
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Lower a genuinely checked original fixture for one selected backend. |
| inputs / outputs | Independent minimum_tree result feeds lower_tree with reference or indexed storage options. |
| invariants | No unchecked supplied tree or specialization-generated answer is used to admit the original plan. |
| ownership | Test/driver-local fixtures and exports are caller-owned. Genuine compiler/runtime handles keep their documented immutable metadata, query account and cursor ownership; no production ownership layer is introduced. |
| failure | Explicit test checks or unexpected exceptions fail the executable. Expected Error/resource/allocation refusal is scoped by the helper/case and must not publish partial state; production failure behavior is not replaced. |
| cost | Explicit test-only compilation, fixture, full-state/cursor/proof or selected fault-cut costs. These checks add no production query-update instructions and make no elapsed-time improvement claim. |
| Design | [tests/unit/key_specialization_test.cpp](../../../../../tests/unit/key_specialization_test.cpp), [include/crown/planner/keys.hpp](../../../../../include/crown/planner/keys.hpp), [docs/key_specialization.md](../../../../key_specialization.md), [Refactor.md](../../../../../Refactor.md), [tests/reference/evaluator.cpp](../../../../../tests/reference/evaluator.cpp) |

## B0010

[Lines 53–57](../../../../../tests/unit/key_specialization_test.cpp#L53); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L53-L57:sha256:007b317afa00b1654ba97d9a45974aaa1925824d63712e2e60c38b39948d3533
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Collect current owning native results as a mathematical set. |
| inputs / outputs | A genuine PhysicalRuntime cursor emits tuples exported into caller-owned Relation. |
| invariants | Cursor drains to terminal next(), releasing its lease before updates. |
| ownership | Test/driver-local fixtures and exports are caller-owned. Genuine compiler/runtime handles keep their documented immutable metadata, query account and cursor ownership; no production ownership layer is introduced. |
| failure | Explicit test checks or unexpected exceptions fail the executable. Expected Error/resource/allocation refusal is scoped by the helper/case and must not publish partial state; production failure behavior is not replaced. |
| cost | Explicit test-only compilation, fixture, full-state/cursor/proof or selected fault-cut costs. These checks add no production query-update instructions and make no elapsed-time improvement claim. |
| Design | [tests/unit/key_specialization_test.cpp](../../../../../tests/unit/key_specialization_test.cpp), [include/crown/planner/keys.hpp](../../../../../include/crown/planner/keys.hpp), [docs/key_specialization.md](../../../../key_specialization.md), [Refactor.md](../../../../../Refactor.md), [tests/reference/evaluator.cpp](../../../../../tests/reference/evaluator.cpp) |

## B0011

[Lines 58–62](../../../../../tests/unit/key_specialization_test.cpp#L58); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L58-L62:sha256:455502b78ef385ed56021e04e5ae2654c7fccaf71df62c1fba50601a5624700c
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Require an ordinary declared Error refusal. |
| inputs / outputs | Action must throw Error; optional code narrows the expected category. |
| invariants | Unexpected success or mismatched category fails; non-Error exceptions remain failures. |
| ownership | Test/driver-local fixtures and exports are caller-owned. Genuine compiler/runtime handles keep their documented immutable metadata, query account and cursor ownership; no production ownership layer is introduced. |
| failure | Explicit test checks or unexpected exceptions fail the executable. Expected Error/resource/allocation refusal is scoped by the helper/case and must not publish partial state; production failure behavior is not replaced. |
| cost | Explicit test-only compilation, fixture, full-state/cursor/proof or selected fault-cut costs. These checks add no production query-update instructions and make no elapsed-time improvement claim. |
| Design | [tests/unit/key_specialization_test.cpp](../../../../../tests/unit/key_specialization_test.cpp), [include/crown/planner/keys.hpp](../../../../../include/crown/planner/keys.hpp), [docs/key_specialization.md](../../../../key_specialization.md), [Refactor.md](../../../../../Refactor.md), [tests/reference/evaluator.cpp](../../../../../tests/reference/evaluator.cpp) |

## B0012

[Lines 63–89](../../../../../tests/unit/key_specialization_test.cpp#L63); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L63-L89:sha256:6c21acac97369ad7598fccad6e845d97b92be1063e4c208e5394d0c8962eabac
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Check original source, occurrence/variable provenance and reduced proof scope. |
| inputs / outputs | Fixture and immutable key Plan produce structural/identity assertions and independent certificate replay. |
| invariants | New IDs map to original table/name/type/head IDs; a reduced certificate validates execution.query and cannot certify the original query. |
| ownership | Test/driver-local fixtures and exports are caller-owned. Genuine compiler/runtime handles keep their documented immutable metadata, query account and cursor ownership; no production ownership layer is introduced. |
| failure | Explicit test checks or unexpected exceptions fail the executable. Expected Error/resource/allocation refusal is scoped by the helper/case and must not publish partial state; production failure behavior is not replaced. |
| cost | Explicit test-only compilation, fixture, full-state/cursor/proof or selected fault-cut costs. These checks add no production query-update instructions and make no elapsed-time improvement claim. |
| Design | [tests/unit/key_specialization_test.cpp](../../../../../tests/unit/key_specialization_test.cpp), [include/crown/planner/keys.hpp](../../../../../include/crown/planner/keys.hpp), [docs/key_specialization.md](../../../../key_specialization.md), [Refactor.md](../../../../../Refactor.md), [tests/reference/evaluator.cpp](../../../../../tests/reference/evaluator.cpp) |

## B0013

[Lines 90–97](../../../../../tests/unit/key_specialization_test.cpp#L90); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L90-L97:sha256:0d276deacaeb5e352731b4b516406651774365b50d9c55f98a56c626b0c9f30b
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Declare the independent-owner trial and its comparison purpose. |
| inputs / outputs | Trial stores fixture reference, cold key Plan, two native owners and one reference Session. |
| invariants | Generic comparison is a separate test owner, not new production maintained state. |
| ownership | Test/driver-local fixtures and exports are caller-owned. Genuine compiler/runtime handles keep their documented immutable metadata, query account and cursor ownership; no production ownership layer is introduced. |
| failure | Explicit test checks or unexpected exceptions fail the executable. Expected Error/resource/allocation refusal is scoped by the helper/case and must not publish partial state; production failure behavior is not replaced. |
| cost | Explicit test-only compilation, fixture, full-state/cursor/proof or selected fault-cut costs. These checks add no production query-update instructions and make no elapsed-time improvement claim. |
| Design | [tests/unit/key_specialization_test.cpp](../../../../../tests/unit/key_specialization_test.cpp), [include/crown/planner/keys.hpp](../../../../../include/crown/planner/keys.hpp), [docs/key_specialization.md](../../../../key_specialization.md), [Refactor.md](../../../../../Refactor.md), [tests/reference/evaluator.cpp](../../../../../tests/reference/evaluator.cpp) |

## B0014

[Lines 98–102](../../../../../tests/unit/key_specialization_test.cpp#L98); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L98-L102:sha256:3f91bbf143416fd798e53ff2c98887113fb6d294be31c1940f5d37614d2f2214
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Initialize both execution routes from one complete original source snapshot. |
| inputs / outputs | Original fixture/optional initial database initialize generic and specialized owners and the original-query reference. |
| invariants | Both receive equivalent full source state, including eliminated/unused tables. |
| ownership | Test/driver-local fixtures and exports are caller-owned. Genuine compiler/runtime handles keep their documented immutable metadata, query account and cursor ownership; no production ownership layer is introduced. |
| failure | Explicit test checks or unexpected exceptions fail the executable. Expected Error/resource/allocation refusal is scoped by the helper/case and must not publish partial state; production failure behavior is not replaced. |
| cost | Explicit test-only compilation, fixture, full-state/cursor/proof or selected fault-cut costs. These checks add no production query-update instructions and make no elapsed-time improvement claim. |
| Design | [tests/unit/key_specialization_test.cpp](../../../../../tests/unit/key_specialization_test.cpp), [include/crown/planner/keys.hpp](../../../../../include/crown/planner/keys.hpp), [docs/key_specialization.md](../../../../key_specialization.md), [Refactor.md](../../../../../Refactor.md), [tests/reference/evaluator.cpp](../../../../../tests/reference/evaluator.cpp) |

## B0015

[Lines 103–106](../../../../../tests/unit/key_specialization_test.cpp#L103); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L103-L106:sha256:dd028a20ab1d6e135ed8286f8217846f25c138ac51c37262f8b654db33ac546d
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Fill only a missing test database table vector. |
| inputs / outputs | An empty Database gets one set per original catalog table; existing data stays intact. |
| invariants | This is fixture shape setup, not source validation or rewriting. |
| ownership | Test/driver-local fixtures and exports are caller-owned. Genuine compiler/runtime handles keep their documented immutable metadata, query account and cursor ownership; no production ownership layer is introduced. |
| failure | Explicit test checks or unexpected exceptions fail the executable. Expected Error/resource/allocation refusal is scoped by the helper/case and must not publish partial state; production failure behavior is not replaced. |
| cost | Explicit test-only compilation, fixture, full-state/cursor/proof or selected fault-cut costs. These checks add no production query-update instructions and make no elapsed-time improvement claim. |
| Design | [tests/unit/key_specialization_test.cpp](../../../../../tests/unit/key_specialization_test.cpp), [include/crown/planner/keys.hpp](../../../../../include/crown/planner/keys.hpp), [docs/key_specialization.md](../../../../key_specialization.md), [Refactor.md](../../../../../Refactor.md), [tests/reference/evaluator.cpp](../../../../../tests/reference/evaluator.cpp) |

## B0016

[Lines 107–115](../../../../../tests/unit/key_specialization_test.cpp#L107); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L107-L115:sha256:07226ea779009444e8269b39045827e1ea85af34532763b06162e2e52f1551b8
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Compare both owners to the original materializing definition. |
| inputs / outputs | Readiness, sequence, full source snapshots and native results are compared to reference; native invariants are checked. |
| invariants | Eliminated tables remain present in the physical source state. |
| ownership | Test/driver-local fixtures and exports are caller-owned. Genuine compiler/runtime handles keep their documented immutable metadata, query account and cursor ownership; no production ownership layer is introduced. |
| failure | Explicit test checks or unexpected exceptions fail the executable. Expected Error/resource/allocation refusal is scoped by the helper/case and must not publish partial state; production failure behavior is not replaced. |
| cost | Explicit test-only compilation, fixture, full-state/cursor/proof or selected fault-cut costs. These checks add no production query-update instructions and make no elapsed-time improvement claim. |
| Design | [tests/unit/key_specialization_test.cpp](../../../../../tests/unit/key_specialization_test.cpp), [include/crown/planner/keys.hpp](../../../../../include/crown/planner/keys.hpp), [docs/key_specialization.md](../../../../key_specialization.md), [Refactor.md](../../../../../Refactor.md), [tests/reference/evaluator.cpp](../../../../../tests/reference/evaluator.cpp) |

## B0017

[Lines 116–126](../../../../../tests/unit/key_specialization_test.cpp#L116); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L116-L126:sha256:0881f090b282e354a157d24b3820bc761ccc60a9972cfa9bc905e380f929ab1a
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Apply one physical set event or require its unchanged-state rejection. |
| inputs / outputs | One contiguous event reaches both native owners and reference; accepted metrics are returned. |
| invariants | Constraint rejection consumes no sequence; all later comparisons use original-CQ semantics. |
| ownership | Test/driver-local fixtures and exports are caller-owned. Genuine compiler/runtime handles keep their documented immutable metadata, query account and cursor ownership; no production ownership layer is introduced. |
| failure | Explicit test checks or unexpected exceptions fail the executable. Expected Error/resource/allocation refusal is scoped by the helper/case and must not publish partial state; production failure behavior is not replaced. |
| cost | Explicit test-only compilation, fixture, full-state/cursor/proof or selected fault-cut costs. These checks add no production query-update instructions and make no elapsed-time improvement claim. |
| Design | [tests/unit/key_specialization_test.cpp](../../../../../tests/unit/key_specialization_test.cpp), [include/crown/planner/keys.hpp](../../../../../include/crown/planner/keys.hpp), [docs/key_specialization.md](../../../../key_specialization.md), [Refactor.md](../../../../../Refactor.md), [tests/reference/evaluator.cpp](../../../../../tests/reference/evaluator.cpp) |

## B0018

[Lines 127–128](../../../../../tests/unit/key_specialization_test.cpp#L127); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L127-L128:sha256:cdbb10f75f6890449819c9d57e5ae7b786fb73c5111c5d829c37bc18f3e053e8
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Close the test trial declaration. |
| inputs / outputs | Ends the local helper type. |
| invariants | No extra runtime owner, registration or publication phase is added. |
| ownership | Test/driver-local fixtures and exports are caller-owned. Genuine compiler/runtime handles keep their documented immutable metadata, query account and cursor ownership; no production ownership layer is introduced. |
| failure | Explicit test checks or unexpected exceptions fail the executable. Expected Error/resource/allocation refusal is scoped by the helper/case and must not publish partial state; production failure behavior is not replaced. |
| cost | Explicit test-only compilation, fixture, full-state/cursor/proof or selected fault-cut costs. These checks add no production query-update instructions and make no elapsed-time improvement claim. |
| Design | [tests/unit/key_specialization_test.cpp](../../../../../tests/unit/key_specialization_test.cpp), [include/crown/planner/keys.hpp](../../../../../include/crown/planner/keys.hpp), [docs/key_specialization.md](../../../../key_specialization.md), [Refactor.md](../../../../../Refactor.md), [tests/reference/evaluator.cpp](../../../../../tests/reference/evaluator.cpp) |

## B0019

[Lines 129–155](../../../../../tests/unit/key_specialization_test.cpp#L129); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L129-L155:sha256:32f3a4c7023248054fab6c94aaf1664d8ebdb325402e3e4ffea7350415404f45
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Exercise all-relation routing, projected support and trusted-data rejection. |
| inputs / outputs | Runs explicit P/C insert/no-op/delete/rejection prefixes on both routes/backends and invalid initial states. |
| invariants | Native parent routes disappear while original source work, constraints and sequence remain; reference output collapses projected witnesses as sets. |
| ownership | Test/driver-local fixtures and exports are caller-owned. Genuine compiler/runtime handles keep their documented immutable metadata, query account and cursor ownership; no production ownership layer is introduced. |
| failure | Explicit test checks or unexpected exceptions fail the executable. Expected Error/resource/allocation refusal is scoped by the helper/case and must not publish partial state; production failure behavior is not replaced. |
| cost | Explicit test-only compilation, fixture, full-state/cursor/proof or selected fault-cut costs. These checks add no production query-update instructions and make no elapsed-time improvement claim. |
| Design | [tests/unit/key_specialization_test.cpp](../../../../../tests/unit/key_specialization_test.cpp), [include/crown/planner/keys.hpp](../../../../../include/crown/planner/keys.hpp), [docs/key_specialization.md](../../../../key_specialization.md), [Refactor.md](../../../../../Refactor.md), [tests/reference/evaluator.cpp](../../../../../tests/reference/evaluator.cpp) |

## B0021

[Lines 157–186](../../../../../tests/unit/key_specialization_test.cpp#L157); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L157-L186:sha256:5bd287f9df09d3aaafe2f25af7fc63d4c0a0915ba7726d63e50ccabf3151c0d5
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Reject rewrites based on untrusted metadata or additional target dependencies. |
| inputs / outputs | No-FK/hints/untrusted, target constant/output, invalid catalog and nullable-core cases exercise actual guards/admission. |
| invariants | Statistics never authorize semantics; target filters/output and malformed/nullable catalogs are not bypassed. |
| ownership | Test/driver-local fixtures and exports are caller-owned. Genuine compiler/runtime handles keep their documented immutable metadata, query account and cursor ownership; no production ownership layer is introduced. |
| failure | Explicit test checks or unexpected exceptions fail the executable. Expected Error/resource/allocation refusal is scoped by the helper/case and must not publish partial state; production failure behavior is not replaced. |
| cost | Explicit test-only compilation, fixture, full-state/cursor/proof or selected fault-cut costs. These checks add no production query-update instructions and make no elapsed-time improvement claim. |
| Design | [tests/unit/key_specialization_test.cpp](../../../../../tests/unit/key_specialization_test.cpp), [include/crown/planner/keys.hpp](../../../../../include/crown/planner/keys.hpp), [docs/key_specialization.md](../../../../key_specialization.md), [Refactor.md](../../../../../Refactor.md), [tests/reference/evaluator.cpp](../../../../../tests/reference/evaluator.cpp) |

## B0023

[Lines 188–213](../../../../../tests/unit/key_specialization_test.cpp#L188); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L188-L213:sha256:158e5977f158424e43789c82ac30c1e86003374b30e9fd50ef460352ad874c40
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Discriminate matching key literals/repetitions from unproved equality. |
| inputs / outputs | Valid constant/repeated source restrictions survive parent removal; mismatched repetition keeps the general query. |
| invariants | FK existence does not imply a missing logical equality or target constant. |
| ownership | Test/driver-local fixtures and exports are caller-owned. Genuine compiler/runtime handles keep their documented immutable metadata, query account and cursor ownership; no production ownership layer is introduced. |
| failure | Explicit test checks or unexpected exceptions fail the executable. Expected Error/resource/allocation refusal is scoped by the helper/case and must not publish partial state; production failure behavior is not replaced. |
| cost | Explicit test-only compilation, fixture, full-state/cursor/proof or selected fault-cut costs. These checks add no production query-update instructions and make no elapsed-time improvement claim. |
| Design | [tests/unit/key_specialization_test.cpp](../../../../../tests/unit/key_specialization_test.cpp), [include/crown/planner/keys.hpp](../../../../../include/crown/planner/keys.hpp), [docs/key_specialization.md](../../../../key_specialization.md), [Refactor.md](../../../../../Refactor.md), [tests/reference/evaluator.cpp](../../../../../tests/reference/evaluator.cpp) |

## B0025

[Lines 215–239](../../../../../tests/unit/key_specialization_test.cpp#L215); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L215-L239:sha256:5dcf328cf30da2070a1242a4f64d187f88883626db3de46806668e410576a741
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Check reordered composite FK keys over every admitted scalar family. |
| inputs / outputs | Builds a mixed typed composite source/target map and native source rows with binary NUL, exact decimals, dates, Boolean and int64 extremes. |
| invariants | Column correspondence is positional and typed; exact values are never stringified or approximated. |
| ownership | Test/driver-local fixtures and exports are caller-owned. Genuine compiler/runtime handles keep their documented immutable metadata, query account and cursor ownership; no production ownership layer is introduced. |
| failure | Explicit test checks or unexpected exceptions fail the executable. Expected Error/resource/allocation refusal is scoped by the helper/case and must not publish partial state; production failure behavior is not replaced. |
| cost | Explicit test-only compilation, fixture, full-state/cursor/proof or selected fault-cut costs. These checks add no production query-update instructions and make no elapsed-time improvement claim. |
| Design | [tests/unit/key_specialization_test.cpp](../../../../../tests/unit/key_specialization_test.cpp), [include/crown/planner/keys.hpp](../../../../../include/crown/planner/keys.hpp), [docs/key_specialization.md](../../../../key_specialization.md), [Refactor.md](../../../../../Refactor.md), [tests/reference/evaluator.cpp](../../../../../tests/reference/evaluator.cpp) |

## B0027

[Lines 241–271](../../../../../tests/unit/key_specialization_test.cpp#L241); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L241-L271:sha256:0c008c0203dbcbf63a597804ba05f2ec56f50cef706bae943cb1dfc274805ec6
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Exercise same-table aliases, cyclic FK catalogs and empty unit keys. |
| inputs / outputs | Self-loop/live-child rejections, complete cyclic initialization and unit-key existence execute on both routes. |
| invariants | Only eligible occurrences disappear; all original FK constraints remain enforced, including target deletion and unit uniqueness. |
| ownership | Test/driver-local fixtures and exports are caller-owned. Genuine compiler/runtime handles keep their documented immutable metadata, query account and cursor ownership; no production ownership layer is introduced. |
| failure | Explicit test checks or unexpected exceptions fail the executable. Expected Error/resource/allocation refusal is scoped by the helper/case and must not publish partial state; production failure behavior is not replaced. |
| cost | Explicit test-only compilation, fixture, full-state/cursor/proof or selected fault-cut costs. These checks add no production query-update instructions and make no elapsed-time improvement claim. |
| Design | [tests/unit/key_specialization_test.cpp](../../../../../tests/unit/key_specialization_test.cpp), [include/crown/planner/keys.hpp](../../../../../include/crown/planner/keys.hpp), [docs/key_specialization.md](../../../../key_specialization.md), [Refactor.md](../../../../../Refactor.md), [tests/reference/evaluator.cpp](../../../../../tests/reference/evaluator.cpp) |

## B0029

[Lines 273–290](../../../../../tests/unit/key_specialization_test.cpp#L273); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L273-L290:sha256:d5dba415df1aaee285fb361a9ffbe0f919a25a5432d3c10be6f2b089350098d5
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Keep normalized SQL and constant routes outside direct-CQ rewriting. |
| inputs / outputs | Actual normalized SQL and constant plans use a zero search allowance with ordinary guard/mapping work. |
| invariants | No new tree search occurs; classification/identity maps are not assumed free. |
| ownership | Test/driver-local fixtures and exports are caller-owned. Genuine compiler/runtime handles keep their documented immutable metadata, query account and cursor ownership; no production ownership layer is introduced. |
| failure | Explicit test checks or unexpected exceptions fail the executable. Expected Error/resource/allocation refusal is scoped by the helper/case and must not publish partial state; production failure behavior is not replaced. |
| cost | Explicit test-only compilation, fixture, full-state/cursor/proof or selected fault-cut costs. These checks add no production query-update instructions and make no elapsed-time improvement claim. |
| Design | [tests/unit/key_specialization_test.cpp](../../../../../tests/unit/key_specialization_test.cpp), [include/crown/planner/keys.hpp](../../../../../include/crown/planner/keys.hpp), [docs/key_specialization.md](../../../../key_specialization.md), [Refactor.md](../../../../../Refactor.md), [tests/reference/evaluator.cpp](../../../../../tests/reference/evaluator.cpp) |

## B0030

[Lines 291–293](../../../../../tests/unit/key_specialization_test.cpp#L291); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L291-L293:sha256:49b578265d36dde97cd98546744f4d26234788958f1007d0eb3f6f39a3dd4512
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Describe the bounded cold allocation/failure scope. |
| inputs / outputs | Comments distinguish selected cuts from the separate exhaustive planner OOM tests. |
| invariants | No exhaustive or runtime-performance result is claimed by these samples. |
| ownership | Test/driver-local fixtures and exports are caller-owned. Genuine compiler/runtime handles keep their documented immutable metadata, query account and cursor ownership; no production ownership layer is introduced. |
| failure | Explicit test checks or unexpected exceptions fail the executable. Expected Error/resource/allocation refusal is scoped by the helper/case and must not publish partial state; production failure behavior is not replaced. |
| cost | Explicit test-only compilation, fixture, full-state/cursor/proof or selected fault-cut costs. These checks add no production query-update instructions and make no elapsed-time improvement claim. |
| Design | [tests/unit/key_specialization_test.cpp](../../../../../tests/unit/key_specialization_test.cpp), [include/crown/planner/keys.hpp](../../../../../include/crown/planner/keys.hpp), [docs/key_specialization.md](../../../../key_specialization.md), [Refactor.md](../../../../../Refactor.md), [tests/reference/evaluator.cpp](../../../../../tests/reference/evaluator.cpp) |

## B0031

[Lines 294–343](../../../../../tests/unit/key_specialization_test.cpp#L294); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L294-L343:sha256:bf684a985a50a2d21caf2e69302e413a572fd8cf4ae3029e18fa2a7f8a7cd2c5
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Verify cold refusal cleanup and receiving-account/runtime ownership boundaries. |
| inputs / outputs | Checks exact/short guard work, search/lowering refusal, 32 spread allocation cuts plus success, account exhaustion, canceled preparation, lease blocking and result lifetime. |
| invariants | General plan never mutates; no partial Plan/epoch escapes; sampled allocation failure is explicitly bounded, and original query account is not refilled. |
| ownership | Test/driver-local fixtures and exports are caller-owned. Genuine compiler/runtime handles keep their documented immutable metadata, query account and cursor ownership; no production ownership layer is introduced. |
| failure | Explicit test checks or unexpected exceptions fail the executable. Expected Error/resource/allocation refusal is scoped by the helper/case and must not publish partial state; production failure behavior is not replaced. |
| cost | Explicit test-only compilation, fixture, full-state/cursor/proof or selected fault-cut costs. These checks add no production query-update instructions and make no elapsed-time improvement claim. |
| Design | [tests/unit/key_specialization_test.cpp](../../../../../tests/unit/key_specialization_test.cpp), [include/crown/planner/keys.hpp](../../../../../include/crown/planner/keys.hpp), [docs/key_specialization.md](../../../../key_specialization.md), [Refactor.md](../../../../../Refactor.md), [tests/reference/evaluator.cpp](../../../../../tests/reference/evaluator.cpp) |

## B0032

[Lines 344–345](../../../../../tests/unit/key_specialization_test.cpp#L344); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L344-L345:sha256:c929980d95efc152dc886ac42af0f045075441dd18a8f886364828ead327bbd3
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Close the unit-local namespace. |
| inputs / outputs | Ends local helper visibility. |
| invariants | No production symbol or shared state is exported. |
| ownership | Test/driver-local fixtures and exports are caller-owned. Genuine compiler/runtime handles keep their documented immutable metadata, query account and cursor ownership; no production ownership layer is introduced. |
| failure | Explicit test checks or unexpected exceptions fail the executable. Expected Error/resource/allocation refusal is scoped by the helper/case and must not publish partial state; production failure behavior is not replaced. |
| cost | Explicit test-only compilation, fixture, full-state/cursor/proof or selected fault-cut costs. These checks add no production query-update instructions and make no elapsed-time improvement claim. |
| Design | [tests/unit/key_specialization_test.cpp](../../../../../tests/unit/key_specialization_test.cpp), [include/crown/planner/keys.hpp](../../../../../include/crown/planner/keys.hpp), [docs/key_specialization.md](../../../../key_specialization.md), [Refactor.md](../../../../../Refactor.md), [tests/reference/evaluator.cpp](../../../../../tests/reference/evaluator.cpp) |

## B0033

[Lines 346–355](../../../../../tests/unit/key_specialization_test.cpp#L346); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L346-L355:sha256:39e370b0a1bb707ca96781f679f3b82d9539a907bc49858381f5058605234326
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Run all unit families for both backends and report actual check count. |
| inputs / outputs | Tests execute with explicit check/exception handling; uncaught failure prints stderr and exits one. |
| invariants | A pass means this finite cohort completed, not every query or a new performance theorem. |
| ownership | Test/driver-local fixtures and exports are caller-owned. Genuine compiler/runtime handles keep their documented immutable metadata, query account and cursor ownership; no production ownership layer is introduced. |
| failure | Explicit test checks or unexpected exceptions fail the executable. Expected Error/resource/allocation refusal is scoped by the helper/case and must not publish partial state; production failure behavior is not replaced. |
| cost | Explicit test-only compilation, fixture, full-state/cursor/proof or selected fault-cut costs. These checks add no production query-update instructions and make no elapsed-time improvement claim. |
| Design | [tests/unit/key_specialization_test.cpp](../../../../../tests/unit/key_specialization_test.cpp), [include/crown/planner/keys.hpp](../../../../../include/crown/planner/keys.hpp), [docs/key_specialization.md](../../../../key_specialization.md), [Refactor.md](../../../../../Refactor.md), [tests/reference/evaluator.cpp](../../../../../tests/reference/evaluator.cpp) |
