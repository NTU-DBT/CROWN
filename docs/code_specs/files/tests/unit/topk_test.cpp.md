# `tests/unit/topk_test.cpp` — block usage map

[Source](../../../../../tests/unit/topk_test.cpp) · [Source index](../../../README.md) · [Subsystem contracts](../../../subsystem_contracts.md) · [Reviewed primitives](../../../primitives.md)

Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection.

Snapshot SHA-256: `fa9e33cdb88430449cb3434ceedde6db772bfa47b7c0ba672a8c1f57d3252c64`. 260 lines partitioned into 28 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [tests](../../../subsystem_contracts.md#tests). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/code_review.md](../../../../code_review.md), [docs/reference_fuzz.md](../../../../reference_fuzz.md), [docs/task_ledger.md](../../../../task_ledger.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–25](../../../../../tests/unit/topk_test.cpp#L1) | Imports dependencies; declares namespace scope; declares aliases; declares values/defaults or compile-time conditions. |  · [reviewed contract](#b0001) |
| [B0002 · 26–26](../../../../../tests/unit/topk_test.cpp#L26) | Callable definition: sql_rows::Cell n(std::int64_t x) | calls ; returns storage::ScalarView{x} · [reviewed contract](#b0002) |
| [B0003 · 27–27](../../../../../tests/unit/topk_test.cpp#L27) | Callable definition: sql_rows::Cell t(std::string_view x) | calls ; returns storage::ScalarView{x} · [reviewed contract](#b0003) |
| [B0004 · 28–32](../../../../../tests/unit/topk_test.cpp#L28) | Callable definition: Catalog catalog() | calls ; returns {1,{{@ ,{{@ ,ScalarType::int64},{@ ,ScalarType::int64,true}, · [reviewed contract](#b0004) |
| [B0005 · 33–35](../../../../../tests/unit/topk_test.cpp#L33) | Callable definition: Cells row(std::int64_t id,sql_rows::Cell x,sql_rows::Cell text={}) | calls n; returns {n(id),x,text,{}, {}, {}} · [reviewed contract](#b0005) |
| [B0006 · 36–40](../../../../../tests/unit/topk_test.cpp#L36) | Callable definition: frontend::SqlRowsProgram rows_program(std::string_view sql) | calls frontend::bind_sql_rows, catalog, Error, std::move; returns std::get&lt;frontend::SqlRowsProgram&gt;(std::move(bound)) · [reviewed contract](#b0006) |
| [B0007 · 41–46](../../../../../tests/unit/topk_test.cpp#L41) | Callable definition: frontend::SqlAggregateProgram aggregate_program(std::string_view sql) | calls frontend::bind_sql_aggregate, catalog, Error, std::move; returns std::get&lt;frontend::SqlAggregateProgram&gt;(std::move(bound)) · [reviewed contract](#b0007) |
| [B0008 · 47–51](../../../../../tests/unit/topk_test.cpp#L47) | Callable definition: FreeConnexTree tree(const frontend::SqlRowsProgram& program) | calls contradiction, export_core, planner::minimum_tree, assert; guard assert(chosen.status==planner::OracleStatus::proven_minimum && chosen.tree);return *chosen.tree;; returns {}; *chosen.tree · [reviewed contract](#b0008) |
| [B0009 · 52–56](../../../../../tests/unit/topk_test.cpp#L52) | Callable definition: SqlRowsRuntime rows_owner(std::string_view sql,bool indexed,const resource::MemoryAccount& account={}) | calls rows_program, s04_runtime::options, SqlRowsRuntime::create_into, tree; returns SqlRowsRuntime::create_into(account,program,tree(program),physical); SqlRowsRuntime(program,tree(pr… · [reviewed contract](#b0009) |
| [B0010 · 57–61](../../../../../tests/unit/topk_test.cpp#L57) | Callable definition: SqlAggregateRuntime aggregate_owner(std::string_view sql,bool indexed,const resource::MemoryAccount& account={}) | calls aggregate_program, s04_runtime::options, SqlAggregateRuntime::create_into, tree; returns SqlAggregateRuntime::create_into(account,program,tree(program.source_program()),physical); SqlAggre… · [reviewed contract](#b0010) |
| [B0011 · 62–65](../../../../../tests/unit/topk_test.cpp#L62) | Callable definition: template&lt;class Owner&gt; void replace(Owner& owner,const Cells& values,std::uint64_t before,std::uint64_t after) | calls prepare_batch, sequence, commit · [reviewed contract](#b0011) |
| [B0012 · 66–70](../../../../../tests/unit/topk_test.cpp#L66) | Callable definition: template&lt;class Action&gt; void error(Action action,std::string_view code) | calls action, assert, code; guard try{action();}catch(const Error& e){assert(e.code()==code);refused=true;} · [reviewed contract](#b0012) |
| [B0013 · 71–73](../../../../../tests/unit/topk_test.cpp#L71) | Callable definition: std::int64_t integer(const aggregate::Tuple& tuple,std::size_t index=0) | calls export_values; returns std::get&lt;std::int64_t&gt;(*tuple.export_values()\[index\]) · [reviewed contract](#b0013) |
| [B0014 · 74–78](../../../../../tests/unit/topk_test.cpp#L74) | Callable definition: std::vector&lt;std::int64_t&gt; identities(const topk::Snapshot& snapshot) | calls push_back, integer; returns result; growth push_back; 1 loop sites · [reviewed contract](#b0014) |
| [B0015 · 79–80](../../../../../tests/unit/topk_test.cpp#L79) | Explanatory comments or spacing. | source comment (unverified): // NULL placement is independent of direction, while final ties use identity. · [reviewed contract](#b0015) |
| [B0016 · 81–100](../../../../../tests/unit/topk_test.cpp#L81) | Callable definition: void rank_and_ties(bool indexed) | calls rows_owner, row, n, t; guard assert(result.selected_rows==4 && result.entries.size()==4 && result.sequence==owner.sequence());; 3 loop sites; source comment (unverified): // NULL placement is independent of direction, while final ties use identity. · [reviewed contract](#b0016) |
| [B0017 · 101–102](../../../../../tests/unit/topk_test.cpp#L101) | Explanatory comments or spacing. | source comment (unverified): // A huge bag is selected as one compressed record, including a partial cutoff. · [reviewed contract](#b0017) |
| [B0018 · 103–120](../../../../../tests/unit/topk_test.cpp#L103) | Callable definition: void multiplicities_and_wrappers(bool indexed) | calls rows_owner, row, n, replace; guard assert(result.entries.size()==1 && result.entries\[0\].multiplicity==k && result.selected_rows==k);; 2 loop sites; source comment (unverified): // A huge bag is selected as one compressed record, including a partial cutoff. · [reviewed contract](#b0018) |
| [B0019 · 121–122](../../../../../tests/unit/topk_test.cpp#L121) | Explanatory comments or spacing. | source comment (unverified): // Decimal and binary TEXT keys must use exact value order, never rendered text. · [reviewed contract](#b0019) |
| [B0020 · 123–158](../../../../../tests/unit/topk_test.cpp#L123) | Callable definition: void scalar_order(bool indexed) | calls rows_owner, size, row, n; guard for(std::size_t i=0;i&lt;expected.size();++i)assert(std::get&lt;Decimal&gt;(*numeric.entries\[i\].values.expor…; growth push_back; 3 loop sites; source comment (unverified): // Decimal and binary TEXT keys must use exact value order, never rendered text. · [reviewed contract](#b0020) |
| [B0021 · 159–160](../../../../../tests/unit/topk_test.cpp#L159) | Explanatory comments or spacing. | source comment (unverified): // Group identity survives omitted keys and equal rendered values at the cutoff. · [reviewed contract](#b0021) |
| [B0022 · 161–183](../../../../../tests/unit/topk_test.cpp#L161) | Callable definition: void aggregate_identity_and_updates(bool indexed) | calls aggregate_owner, row, n, replace; guard assert((identities(first)==std::vector&lt;std::int64_t&gt;{1,2}));; 2 loop sites; source comment (unverified): // Group identity survives omitted keys and equal rendered values at the cutoff. · [reviewed contract](#b0022) |
| [B0023 · 184–185](../../../../../tests/unit/topk_test.cpp#L184) | Explanatory comments or spacing. | source comment (unverified): // A valid k=0 uses no producer or allocation, but order and busy admission remain. · [reviewed contract](#b0023) |
| [B0024 · 186–206](../../../../../tests/unit/topk_test.cpp#L186) | Callable definition: void admission_and_zero(bool indexed) | calls rows_owner, row, n, replace; guard {s04_alloc::Scope deny(0);const auto zero=snapshot_topk(owner,{},0,{0,0,0});assert(zero.entries.emp…; source comment (unverified): // A valid k=0 uses no producer or allocation, but order and busy admission remain. · [reviewed contract](#b0024) |
| [B0025 · 207–208](../../../../../tests/unit/topk_test.cpp#L207) | Explanatory comments or spacing. | source comment (unverified): // Denied collection, sort and allocation release their local handles and lease. · [reviewed contract](#b0025) |
| [B0026 · 209–251](../../../../../tests/unit/topk_test.cpp#L209) | Callable definition: void resource_and_ownership(bool indexed) | calls resource::MemoryAccount::create, rows_owner, row, n; guard {const auto warm=snapshot_topk(owner,order,1);work=warm.metrics.work;assert(warm.entries.size()==1 …; growth allocate, emplace; 2 loop sites; source comment (unverified): // Denied collection, sort and allocation release their local handles and lease. · [reviewed contract](#b0026) |
| [B0027 · 252–253](../../../../../tests/unit/topk_test.cpp#L252) | Closes surrounding scope/type. | source comment (unverified): // namespace · [reviewed contract](#b0027) |
| [B0028 · 254–260](../../../../../tests/unit/topk_test.cpp#L254) | Callable definition: int main() | calls rank_and_ties, multiplicities_and_wrappers, scalar_order, aggregate_identity_and_updates; 1 loop sites · [reviewed contract](#b0028) |

## B0001

[Lines 1–25](../../../../../tests/unit/topk_test.cpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L1-L25:sha256:add80437ba350157a1e8d1ccac2757cb05bbdc70859b3260c497b7b079a517eb
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Declare isolated test dependencies, exact fixture types and constants. |
| inputs / outputs | Imports/includes and local aliases configure this one test module; they are not a production query primitive. |
| invariants | Python oracle imports no CROWN implementation. Native unit replacement new is confined to its one test translation unit and standard assertions must remain enabled. |
| ownership | Ordinary module definitions own no active native query or subprocess. |
| failure | Missing dependencies or build errors prevent this test from starting. |
| cost | Module/build setup only; no update-path or ranking-time charge is implied. |
| Design | [include/crown/runtime/topk.hpp](../../../../../include/crown/runtime/topk.hpp), [Refactor.md](../../../../../Refactor.md), [docs/scalars.md](../../../../scalars.md), [docs/sql_rows_runtime.md](../../../../sql_rows_runtime.md), [docs/sql_aggregate_runtime.md](../../../../sql_aggregate_runtime.md), [tests/unit/topk_test.cpp](../../../../../tests/unit/topk_test.cpp) |

## B0002

[Lines 26–26](../../../../../tests/unit/topk_test.cpp#L26); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L26-L26:sha256:0005d0fae31e37d831155f98cacd6c029da57cc3ce93dab3b0cfb7be3fa5f241
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Build an exact integer fixture cell. |
| inputs / outputs | An int64 becomes one present SQL cell. |
| invariants | No floating conversion or NULL interpretation. |
| ownership | The scalar is inline in the returned optional variant. |
| failure | No dynamic allocation or validation is needed. |
| cost | Fixed scalar construction. |
| Design | [include/crown/runtime/topk.hpp](../../../../../include/crown/runtime/topk.hpp), [Refactor.md](../../../../../Refactor.md), [docs/scalars.md](../../../../scalars.md), [docs/sql_rows_runtime.md](../../../../sql_rows_runtime.md), [docs/sql_aggregate_runtime.md](../../../../sql_aggregate_runtime.md), [tests/unit/topk_test.cpp](../../../../../tests/unit/topk_test.cpp) |

## B0003

[Lines 27–27](../../../../../tests/unit/topk_test.cpp#L27); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L27-L27:sha256:29be8cc0bfe8d1568da672a347c3ce98ec6ef74bc565f6236a43a338923366e3
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Borrow TEXT fixture bytes. |
| inputs / outputs | A string_view becomes one present SQL cell. |
| invariants | The backing string must survive synchronous source admission. |
| ownership | The cell borrows caller bytes; the native source copies them on successful admission. |
| failure | This helper does not admit UTF8/NUL domain by itself. |
| cost | Fixed descriptor construction; no byte copy. |
| Design | [include/crown/runtime/topk.hpp](../../../../../include/crown/runtime/topk.hpp), [Refactor.md](../../../../../Refactor.md), [docs/scalars.md](../../../../scalars.md), [docs/sql_rows_runtime.md](../../../../sql_rows_runtime.md), [docs/sql_aggregate_runtime.md](../../../../sql_aggregate_runtime.md), [tests/unit/topk_test.cpp](../../../../../tests/unit/topk_test.cpp) |

## B0004

[Lines 28–32](../../../../../tests/unit/topk_test.cpp#L28); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L28-L32:sha256:ba8f5b6e15a4636bf787e829fb18c8aa270931c1c3b1831d9be30879568c8915
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Declare the closed nullable scalar fixture schema. |
| inputs / outputs | One physical r table has id,x,t,flag,d,n columns. |
| invariants | id is non-null; the remaining scalar columns are nullable and n uses the existing generic decimal domain. |
| ownership | Ordinary cold Catalog DTO owns its vectors and names. |
| failure | Allocation errors propagate before a native owner is created. |
| cost | Fixed-size ordinary fixture allocation. |
| Design | [include/crown/runtime/topk.hpp](../../../../../include/crown/runtime/topk.hpp), [Refactor.md](../../../../../Refactor.md), [docs/scalars.md](../../../../scalars.md), [docs/sql_rows_runtime.md](../../../../sql_rows_runtime.md), [docs/sql_aggregate_runtime.md](../../../../sql_aggregate_runtime.md), [tests/unit/topk_test.cpp](../../../../../tests/unit/topk_test.cpp) |

## B0005

[Lines 33–35](../../../../../tests/unit/topk_test.cpp#L33); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L33-L35:sha256:33d74bd5210423485f13da3747dee29b521d8ee8c0a7f9ce673f1f4961c23127
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Build a complete physical fixture row. |
| inputs / outputs | id,x,TEXT in; six cells out with other fields initially NULL. |
| invariants | Full source arity is preserved even when SQL projects fewer fields. |
| ownership | The vector owns descriptors; TEXT descriptors still borrow their supplied backing. |
| failure | Standard fixture allocation failure propagates. |
| cost | Six descriptors plus ordinary vector storage. |
| Design | [include/crown/runtime/topk.hpp](../../../../../include/crown/runtime/topk.hpp), [Refactor.md](../../../../../Refactor.md), [docs/scalars.md](../../../../scalars.md), [docs/sql_rows_runtime.md](../../../../sql_rows_runtime.md), [docs/sql_aggregate_runtime.md](../../../../sql_aggregate_runtime.md), [tests/unit/topk_test.cpp](../../../../../tests/unit/topk_test.cpp) |

## B0006

[Lines 36–40](../../../../../tests/unit/topk_test.cpp#L36); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L36-L40:sha256:11c2766bfb5339449f41d770d4720a1c4c56d595216295c5134f38a57c85872b
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Bind actual SQL row fixtures through the public factory. |
| inputs / outputs | SQL and the closed catalog produce genuine SqlRowsProgram. |
| invariants | No editable program DTO or expected result is imported. |
| ownership | Factory metadata is owned by its compiler account and later imported by the real runtime. |
| failure | A BindingDiagnostic is translated to Error so this test process fails. |
| cost | Cold parsing/binding and compiler metadata work; outside top-k timing/grants. |
| Design | [include/crown/runtime/topk.hpp](../../../../../include/crown/runtime/topk.hpp), [Refactor.md](../../../../../Refactor.md), [docs/scalars.md](../../../../scalars.md), [docs/sql_rows_runtime.md](../../../../sql_rows_runtime.md), [docs/sql_aggregate_runtime.md](../../../../sql_aggregate_runtime.md), [tests/unit/topk_test.cpp](../../../../../tests/unit/topk_test.cpp) |

## B0007

[Lines 41–46](../../../../../tests/unit/topk_test.cpp#L41); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L41-L46:sha256:6d862676070ab8e0545939c6b148f0ffc64616f1aa3b80a9b2cd5cc674c96b22
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Bind actual aggregate SQL fixtures at display scale2. |
| inputs / outputs | SQL/catalog produce genuine SqlAggregateProgram. |
| invariants | AVG display scale is explicitly2; compiler rejection is not mistaken for execution support. |
| ownership | The genuine program retains immutable compiler metadata. |
| failure | Binding diagnostics become failing test Errors. |
| cost | Cold parsing/composition/kernel binding; separate from ranking work. |
| Design | [include/crown/runtime/topk.hpp](../../../../../include/crown/runtime/topk.hpp), [Refactor.md](../../../../../Refactor.md), [docs/scalars.md](../../../../scalars.md), [docs/sql_rows_runtime.md](../../../../sql_rows_runtime.md), [docs/sql_aggregate_runtime.md](../../../../sql_aggregate_runtime.md), [tests/unit/topk_test.cpp](../../../../../tests/unit/topk_test.cpp) |

## B0008

[Lines 47–51](../../../../../tests/unit/topk_test.cpp#L47); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L47-L51:sha256:d24bbd5425dcf2af23e242810afe0cbbe0d4c9e5fb58eeb54353e0cf64c2dea2
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Choose a checked source tree for a genuine row program. |
| inputs / outputs | Contradiction uses the empty route; otherwise exported CQ feeds minimum_tree. |
| invariants | Nonconstant cases require proven_minimum and a retained tree. |
| ownership | The returned tree is an ordinary cold DTO; runtime factories revalidate it. |
| failure | Assertion or planner/compiler exception fails the test. |
| cost | Actual cold planner work; no top-k or P10 complexity claim. |
| Design | [include/crown/runtime/topk.hpp](../../../../../include/crown/runtime/topk.hpp), [Refactor.md](../../../../../Refactor.md), [docs/scalars.md](../../../../scalars.md), [docs/sql_rows_runtime.md](../../../../sql_rows_runtime.md), [docs/sql_aggregate_runtime.md](../../../../sql_aggregate_runtime.md), [tests/unit/topk_test.cpp](../../../../../tests/unit/topk_test.cpp) |

## B0009

[Lines 52–56](../../../../../tests/unit/topk_test.cpp#L52); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L52-L56:sha256:480d9730207a6182f617bc3f415cf72872c25ca4cf92b8cf461324961e829d2f
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Create a real row owner in the selected storage backend. |
| inputs / outputs | SQL,indexed flag and optional account produce SqlRowsRuntime. |
| invariants | An explicit receiving account is reused rather than replaced by a new grant. |
| ownership | The move-only runtime owns native state and genuine imported metadata. |
| failure | Binding/planner/runtime construction failure propagates. |
| cost | Cold owner admission and backend allocations. |
| Design | [include/crown/runtime/topk.hpp](../../../../../include/crown/runtime/topk.hpp), [Refactor.md](../../../../../Refactor.md), [docs/scalars.md](../../../../scalars.md), [docs/sql_rows_runtime.md](../../../../sql_rows_runtime.md), [docs/sql_aggregate_runtime.md](../../../../sql_aggregate_runtime.md), [tests/unit/topk_test.cpp](../../../../../tests/unit/topk_test.cpp) |

## B0010

[Lines 57–61](../../../../../tests/unit/topk_test.cpp#L57); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L57-L61:sha256:1f6d15ff7052824f0c724a9d9b33b94dcaa717db6f5d379f2454827b3088f535
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Create a real aggregate owner in the selected backend. |
| inputs / outputs | SQL,indexed flag and optional account produce SqlAggregateRuntime. |
| invariants | The tree belongs to the actual source_program; no logical-fact injection is used. |
| ownership | The runtime owns source/native/group state and genuine compiler metadata. |
| failure | Cold factory/admission errors propagate. |
| cost | Cold composition/native/group setup, separate from top-k sort costs. |
| Design | [include/crown/runtime/topk.hpp](../../../../../include/crown/runtime/topk.hpp), [Refactor.md](../../../../../Refactor.md), [docs/scalars.md](../../../../scalars.md), [docs/sql_rows_runtime.md](../../../../sql_rows_runtime.md), [docs/sql_aggregate_runtime.md](../../../../sql_aggregate_runtime.md), [tests/unit/topk_test.cpp](../../../../../tests/unit/topk_test.cpp) |

## B0011

[Lines 62–65](../../../../../tests/unit/topk_test.cpp#L62); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L62-L65:sha256:79040ffa686243033e87415b8ce725fa89608bc2436bbb63a4e216d7e0d3f58c
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Commit one complete physical weight replacement. |
| inputs / outputs | Owner, full cells, old weight and new weight produce one next contiguous epoch. |
| invariants | The caller supplies the actual before weight; the real prepared batch decides all mutation. |
| ownership | Cells borrow only through prepare return; the prepared token owns rollback/publication. |
| failure | A rejected edit unwinds without a test-authored rollback mechanism. |
| cost | One genuine atomic batch; no top-k maintenance hook. |
| Design | [include/crown/runtime/topk.hpp](../../../../../include/crown/runtime/topk.hpp), [Refactor.md](../../../../../Refactor.md), [docs/scalars.md](../../../../scalars.md), [docs/sql_rows_runtime.md](../../../../sql_rows_runtime.md), [docs/sql_aggregate_runtime.md](../../../../sql_aggregate_runtime.md), [tests/unit/topk_test.cpp](../../../../../tests/unit/topk_test.cpp) |

## B0012

[Lines 66–70](../../../../../tests/unit/topk_test.cpp#L66); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L66-L70:sha256:fc0f95c0bdf7c5f479bea3ea313d2c66b2d9478187bb47b6f5d163422c19c523
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Require a specific public Error category. |
| inputs / outputs | An action and expected code must produce matching Error. |
| invariants | A successful action or different Error code fails the assertion; other exceptions propagate. |
| ownership | Only synchronous action lifetime is borrowed. |
| failure | Assertions require the test target to retain assertions enabled. |
| cost | One negative-control call; not a production handler. |
| Design | [include/crown/runtime/topk.hpp](../../../../../include/crown/runtime/topk.hpp), [Refactor.md](../../../../../Refactor.md), [docs/scalars.md](../../../../scalars.md), [docs/sql_rows_runtime.md](../../../../sql_rows_runtime.md), [docs/sql_aggregate_runtime.md](../../../../sql_aggregate_runtime.md), [tests/unit/topk_test.cpp](../../../../../tests/unit/topk_test.cpp) |

## B0013

[Lines 71–73](../../../../../tests/unit/topk_test.cpp#L71); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L71-L73:sha256:36070009fa351a334dbc1730a78f5e8510b16483dd7bca559a4bf5a0bc4e0319
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Inspect an integer fixture tuple. |
| inputs / outputs | An owning Tuple and valid integer field return a copied int64. |
| invariants | Used only for non-NULL integer-valued fixture keys/outputs. |
| ownership | export_values creates an ordinary caller-owned row temporary. |
| failure | Invalid type/index or allocation fails the test. |
| cost | Explicit full tuple export and one field extraction, outside ranking work. |
| Design | [include/crown/runtime/topk.hpp](../../../../../include/crown/runtime/topk.hpp), [Refactor.md](../../../../../Refactor.md), [docs/scalars.md](../../../../scalars.md), [docs/sql_rows_runtime.md](../../../../sql_rows_runtime.md), [docs/sql_aggregate_runtime.md](../../../../sql_aggregate_runtime.md), [tests/unit/topk_test.cpp](../../../../../tests/unit/topk_test.cpp) |

## B0014

[Lines 74–78](../../../../../tests/unit/topk_test.cpp#L74); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L74-L78:sha256:9abef5824071c49e28bed1ad100c8c48a83b5111b102b2731f9aa14fcd8d7ae6
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Export identified integer group order for literal comparisons. |
| inputs / outputs | A ranked Snapshot yields its ordered group-key integer list. |
| invariants | Only the fixture one-column integer group identities use this helper. |
| ownership | The returned ordinary vector owns its copied integers. |
| failure | Unexpected identity type/shape fails rather than coalescing outputs. |
| cost | Linear selected-entry exports; diagnostic test work. |
| Design | [include/crown/runtime/topk.hpp](../../../../../include/crown/runtime/topk.hpp), [Refactor.md](../../../../../Refactor.md), [docs/scalars.md](../../../../scalars.md), [docs/sql_rows_runtime.md](../../../../sql_rows_runtime.md), [docs/sql_aggregate_runtime.md](../../../../sql_aggregate_runtime.md), [tests/unit/topk_test.cpp](../../../../../tests/unit/topk_test.cpp) |

## B0015

[Lines 79–80](../../../../../tests/unit/topk_test.cpp#L79); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L79-L80:sha256:f923c0d056068c87518aef6f748689d37071bf85e5efdfebd03b121d3936434b
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Explain the following assertion family: NULL placement is independent of direction, while final ties use identity. |
| inputs / outputs | Prose guides the following native test function; it produces no runtime result. |
| invariants | The note is checked by the adjacent concrete assertions and is not a universal correctness proof. |
| ownership | No owner, borrow or data allocation is introduced by this comment. |
| failure | The comment itself cannot throw or execute a recovery action. |
| cost | No executable work. |
| Design | [include/crown/runtime/topk.hpp](../../../../../include/crown/runtime/topk.hpp), [Refactor.md](../../../../../Refactor.md), [docs/scalars.md](../../../../scalars.md), [docs/sql_rows_runtime.md](../../../../sql_rows_runtime.md), [docs/sql_aggregate_runtime.md](../../../../sql_aggregate_runtime.md), [tests/unit/topk_test.cpp](../../../../../tests/unit/topk_test.cpp) |

## B0016

[Lines 81–100](../../../../../tests/unit/topk_test.cpp#L81); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L81-L100:sha256:a9a9900cee5608f1cf033fed7ba8b721ec55a4de583760d554ee68a99941375e
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Check NULL direction, multikey order and deterministic row ties. |
| inputs / outputs | Four source rows are ranked under four ASC/DESC/NULL policies plus mixed/repeated keys. |
| invariants | NULL placement does not reverse with DESC; equal requested integer keys fall back to complete row identity. |
| ownership | Each returned snapshot owns its values while the owner remains independently usable. |
| failure | Any rank, arity, sequence or tie mismatch aborts the assertion-enabled test. |
| cost | Small finite recomputation controls; no speedup or asymptotic evidence. |
| Design | [include/crown/runtime/topk.hpp](../../../../../include/crown/runtime/topk.hpp), [Refactor.md](../../../../../Refactor.md), [docs/scalars.md](../../../../scalars.md), [docs/sql_rows_runtime.md](../../../../sql_rows_runtime.md), [docs/sql_aggregate_runtime.md](../../../../sql_aggregate_runtime.md), [tests/unit/topk_test.cpp](../../../../../tests/unit/topk_test.cpp) |

## B0017

[Lines 101–102](../../../../../tests/unit/topk_test.cpp#L101); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L101-L102:sha256:8e3ca576d4135060081a53e5c02a437818feab2e940796168fe15c6c5e311425
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Explain the following assertion family: A huge bag is selected as one compressed record, including a partial cutoff. |
| inputs / outputs | Prose guides the following native test function; it produces no runtime result. |
| invariants | The note is checked by the adjacent concrete assertions and is not a universal correctness proof. |
| ownership | No owner, borrow or data allocation is introduced by this comment. |
| failure | The comment itself cannot throw or execute a recovery action. |
| cost | No executable work. |
| Design | [include/crown/runtime/topk.hpp](../../../../../include/crown/runtime/topk.hpp), [Refactor.md](../../../../../Refactor.md), [docs/scalars.md](../../../../scalars.md), [docs/sql_rows_runtime.md](../../../../sql_rows_runtime.md), [docs/sql_aggregate_runtime.md](../../../../sql_aggregate_runtime.md), [tests/unit/topk_test.cpp](../../../../../tests/unit/topk_test.cpp) |

## B0018

[Lines 103–120](../../../../../tests/unit/topk_test.cpp#L103); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L103-L120:sha256:934ab25cc8bd6f5d94f5eec670824c9d19e78530d8352a255281c98577f39c2a
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Check compressed wide bags, DISTINCT and EXISTS. |
| inputs / outputs | Real source replacements exercise UINT64_MAX and above2^53 cutoffs, deletion, distinct support and Boolean output. |
| invariants | A wide selected bag remains one record; DISTINCT weight is1; EXISTS emits one true/false row even for empty input. |
| ownership | Snapshots retain tuple/schema handles; no expanded copy list is created by the test. |
| failure | Incorrect magnitude, identity, Boolean state or stale empty result fails. |
| cost | Finite compressed records independent of multiplicity; no huge expansion. |
| Design | [include/crown/runtime/topk.hpp](../../../../../include/crown/runtime/topk.hpp), [Refactor.md](../../../../../Refactor.md), [docs/scalars.md](../../../../scalars.md), [docs/sql_rows_runtime.md](../../../../sql_rows_runtime.md), [docs/sql_aggregate_runtime.md](../../../../sql_aggregate_runtime.md), [tests/unit/topk_test.cpp](../../../../../tests/unit/topk_test.cpp) |

## B0019

[Lines 121–122](../../../../../tests/unit/topk_test.cpp#L121); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L121-L122:sha256:5cedbed3e49c3e743681b5852d21fc80db4cf75148f68b79883564b715e20d3a
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Explain the following assertion family: Decimal and binary TEXT keys must use exact value order, never rendered text. |
| inputs / outputs | Prose guides the following native test function; it produces no runtime result. |
| invariants | The note is checked by the adjacent concrete assertions and is not a universal correctness proof. |
| ownership | No owner, borrow or data allocation is introduced by this comment. |
| failure | The comment itself cannot throw or execute a recovery action. |
| cost | No executable work. |
| Design | [include/crown/runtime/topk.hpp](../../../../../include/crown/runtime/topk.hpp), [Refactor.md](../../../../../Refactor.md), [docs/scalars.md](../../../../scalars.md), [docs/sql_rows_runtime.md](../../../../sql_rows_runtime.md), [docs/sql_aggregate_runtime.md](../../../../sql_aggregate_runtime.md), [tests/unit/topk_test.cpp](../../../../../tests/unit/topk_test.cpp) |

## B0020

[Lines 123–158](../../../../../tests/unit/topk_test.cpp#L123); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L123-L158:sha256:b9be18a288662af9fecb0d0f23d6c38c9db25b7c365b63372c94753cc277d3e4
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Check actual ranking of every admitted scalar family. |
| inputs / outputs | Nullable SQL outputs rank decimal, valid UTF8 binary TEXT, date, bool and int64 boundary values. |
| invariants | Decimal2 precedes10 numerically; control/non-ASCII bytes retain binary order; date/bool/int extrema are actually ranked. NUL and0xff source inputs must reject. |
| ownership | Fixture strings survive each synchronous edit; result tuples own admitted values. |
| failure | Out-of-domain source controls require invalid_sql_rows_row and unchanged ready/sequence; rank errors fail assertions. |
| cost | Five small numeric rows/four TEXT rows and explicit negative admissions; no broad Unicode/collation claim. |
| Design | [include/crown/runtime/topk.hpp](../../../../../include/crown/runtime/topk.hpp), [Refactor.md](../../../../../Refactor.md), [docs/scalars.md](../../../../scalars.md), [docs/sql_rows_runtime.md](../../../../sql_rows_runtime.md), [docs/sql_aggregate_runtime.md](../../../../sql_aggregate_runtime.md), [tests/unit/topk_test.cpp](../../../../../tests/unit/topk_test.cpp) |

## B0021

[Lines 159–160](../../../../../tests/unit/topk_test.cpp#L159); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L159-L160:sha256:bb766f88a9d6e874850792dc0296bcb3d79065a04b901c56233088ab2778dadd
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Explain the following assertion family: Group identity survives omitted keys and equal rendered values at the cutoff. |
| inputs / outputs | Prose guides the following native test function; it produces no runtime result. |
| invariants | The note is checked by the adjacent concrete assertions and is not a universal correctness proof. |
| ownership | No owner, borrow or data allocation is introduced by this comment. |
| failure | The comment itself cannot throw or execute a recovery action. |
| cost | No executable work. |
| Design | [include/crown/runtime/topk.hpp](../../../../../include/crown/runtime/topk.hpp), [Refactor.md](../../../../../Refactor.md), [docs/scalars.md](../../../../scalars.md), [docs/sql_rows_runtime.md](../../../../sql_rows_runtime.md), [docs/sql_aggregate_runtime.md](../../../../sql_aggregate_runtime.md), [tests/unit/topk_test.cpp](../../../../../tests/unit/topk_test.cpp) |

## B0022

[Lines 161–183](../../../../../tests/unit/topk_test.cpp#L161); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L161-L183:sha256:f100ff61e04e59636ce97d82c0e515978fbc99cea684bdce2fd7011f756f2d6e
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Check hidden group identity, numeric aggregates and empty semantics. |
| inputs / outputs | Actual grouped/global SQL is updated then ranked by COUNT,SUM,AVG or identity. |
| invariants | Equal projected COUNTs retain separate group keys; insertion/deletion changes order; SUM/AVG NULL and ties use rendered values. Global empty has one group; grouped empty has none. |
| ownership | Owning snapshots retain separate key and value tuples and genuine schema. |
| failure | Wrong key choice, stale rank, NULL position or empty result fails assertions. |
| cost | Finite grouped recompute/sort controls, not incremental top-k maintenance. |
| Design | [include/crown/runtime/topk.hpp](../../../../../include/crown/runtime/topk.hpp), [Refactor.md](../../../../../Refactor.md), [docs/scalars.md](../../../../scalars.md), [docs/sql_rows_runtime.md](../../../../sql_rows_runtime.md), [docs/sql_aggregate_runtime.md](../../../../sql_aggregate_runtime.md), [tests/unit/topk_test.cpp](../../../../../tests/unit/topk_test.cpp) |

## B0023

[Lines 184–185](../../../../../tests/unit/topk_test.cpp#L184); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L184-L185:sha256:b1b424f41492c5bea69aa801565930372de49f03bc941ae5c74c1c5f25da6c8c
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Explain the following assertion family: A valid k=0 uses no producer or allocation, but order and busy admission remain. |
| inputs / outputs | Prose guides the following native test function; it produces no runtime result. |
| invariants | The note is checked by the adjacent concrete assertions and is not a universal correctness proof. |
| ownership | No owner, borrow or data allocation is introduced by this comment. |
| failure | The comment itself cannot throw or execute a recovery action. |
| cost | No executable work. |
| Design | [include/crown/runtime/topk.hpp](../../../../../include/crown/runtime/topk.hpp), [Refactor.md](../../../../../Refactor.md), [docs/scalars.md](../../../../scalars.md), [docs/sql_rows_runtime.md](../../../../sql_rows_runtime.md), [docs/sql_aggregate_runtime.md](../../../../sql_aggregate_runtime.md), [tests/unit/topk_test.cpp](../../../../../tests/unit/topk_test.cpp) |

## B0024

[Lines 186–206](../../../../../tests/unit/topk_test.cpp#L186); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L186-L206:sha256:10c945200419793b2cc78ba07678e190e8be019975d9964e3455dbe61f00713d
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Check zero-k admission and busy ownership. |
| inputs / outputs | Rows and aggregate owners are queried with k0, zero grants, invalid key/enums and active prepared tokens. |
| invariants | Valid empty order/k0 allocates nothing and opens no producer; order is still validated; busy owners reject even k0. |
| ownership | Prepared token destruction restores quiescence; zero snapshots retain only existing metadata handles. |
| failure | Expected categories are topk_order,topk_work_limit and topk_busy; global-new denial makes hidden allocations observable. |
| cost | Selected admission-only calls; no collection/sort work is claimed. |
| Design | [include/crown/runtime/topk.hpp](../../../../../include/crown/runtime/topk.hpp), [Refactor.md](../../../../../Refactor.md), [docs/scalars.md](../../../../scalars.md), [docs/sql_rows_runtime.md](../../../../sql_rows_runtime.md), [docs/sql_aggregate_runtime.md](../../../../sql_aggregate_runtime.md), [tests/unit/topk_test.cpp](../../../../../tests/unit/topk_test.cpp) |

## B0025

[Lines 207–208](../../../../../tests/unit/topk_test.cpp#L207); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L207-L208:sha256:3270aa476a55d661dee0b44b82635cc4d59e0024d23882bb58eea20aecbf6dd6
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Explain the following assertion family: Denied collection, sort and allocation release their local handles and lease. |
| inputs / outputs | Prose guides the following native test function; it produces no runtime result. |
| invariants | The note is checked by the adjacent concrete assertions and is not a universal correctness proof. |
| ownership | No owner, borrow or data allocation is introduced by this comment. |
| failure | The comment itself cannot throw or execute a recovery action. |
| cost | No executable work. |
| Design | [include/crown/runtime/topk.hpp](../../../../../include/crown/runtime/topk.hpp), [Refactor.md](../../../../../Refactor.md), [docs/scalars.md](../../../../scalars.md), [docs/sql_rows_runtime.md](../../../../sql_rows_runtime.md), [docs/sql_aggregate_runtime.md](../../../../sql_aggregate_runtime.md), [tests/unit/topk_test.cpp](../../../../../tests/unit/topk_test.cpp) |

## B0026

[Lines 209–251](../../../../../tests/unit/topk_test.cpp#L209); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L209-L251:sha256:1171d3ad459942bf632e048c80f8433b077748896c74ad7136a08554f2d55dab
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Check finite grants, cleanup and independent snapshot lifetime. |
| inputs / outputs | Warm three-row owner exercises exact/one-under work, candidate cap, producer denial, filled original account and persistent new faults. |
| invariants | Failures release private ranking/cursor state, preserve committed sequence/current retained baseline after warm-up, and allow the next update. A small k retains compact entry storage. |
| ownership | Source owner and returned snapshot have separate lifetimes; retained row/schema remain valid after the local facade moves/dies. |
| failure | Typed account limit and covered std::bad_alloc failures must leave the owner ready; unexpected exceptions fail. |
| cost | Finite allocation-fault positions and small recomputations; covers C++ new only, not libc/exception-runtime allocation or wall-time bounds. |
| Design | [include/crown/runtime/topk.hpp](../../../../../include/crown/runtime/topk.hpp), [Refactor.md](../../../../../Refactor.md), [docs/scalars.md](../../../../scalars.md), [docs/sql_rows_runtime.md](../../../../sql_rows_runtime.md), [docs/sql_aggregate_runtime.md](../../../../sql_aggregate_runtime.md), [tests/unit/topk_test.cpp](../../../../../tests/unit/topk_test.cpp) |

## B0027

[Lines 252–253](../../../../../tests/unit/topk_test.cpp#L252); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L252-L253:sha256:c929980d95efc152dc886ac42af0f045075441dd18a8f886364828ead327bbd3
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Close the anonymous fixture-helper namespace. |
| inputs / outputs | The scope delimiter exposes only the subsequent process entry point. |
| invariants | Fixture helper names remain local to this test translation unit. |
| ownership | No runtime ownership transfer occurs at the delimiter. |
| failure | No executable failure behavior. |
| cost | No executable work. |
| Design | [include/crown/runtime/topk.hpp](../../../../../include/crown/runtime/topk.hpp), [Refactor.md](../../../../../Refactor.md), [docs/scalars.md](../../../../scalars.md), [docs/sql_rows_runtime.md](../../../../sql_rows_runtime.md), [docs/sql_aggregate_runtime.md](../../../../sql_aggregate_runtime.md), [tests/unit/topk_test.cpp](../../../../../tests/unit/topk_test.cpp) |

## B0028

[Lines 254–260](../../../../../tests/unit/topk_test.cpp#L254); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L254-L260:sha256:ab83af96763ab18bba734754c306ec310cffff9aabe00d06b9e5098f8a3aab23
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Run all unit families on both production storage backends. |
| inputs / outputs | No arguments; ordered/indexed controls must all return before a pass summary. |
| invariants | All semantic/resource assertions remain active through the test target compile flags. |
| ownership | Local owners and results unwind before process exit. |
| failure | Assertion failure or uncaught exception prevents successful completion. |
| cost | Finite test orchestration, not a full-suite or performance measurement. |
| Design | [include/crown/runtime/topk.hpp](../../../../../include/crown/runtime/topk.hpp), [Refactor.md](../../../../../Refactor.md), [docs/scalars.md](../../../../scalars.md), [docs/sql_rows_runtime.md](../../../../sql_rows_runtime.md), [docs/sql_aggregate_runtime.md](../../../../sql_aggregate_runtime.md), [tests/unit/topk_test.cpp](../../../../../tests/unit/topk_test.cpp) |
