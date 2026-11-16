# `tests/unit/sql_rows_runtime_test.cpp` — block usage map

[Source](../../../../../tests/unit/sql_rows_runtime_test.cpp) · [Source index](../../../README.md) · [Subsystem contracts](../../../subsystem_contracts.md) · [Reviewed primitives](../../../primitives.md)

Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection.

Snapshot SHA-256: `038c705170a994f2e81a1e33446e99814a2eba82ce60ea31fc233a9d1b2d9dbd`. 319 lines partitioned into 32 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [tests](../../../subsystem_contracts.md#tests). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/code_review.md](../../../../code_review.md), [docs/reference_fuzz.md](../../../../reference_fuzz.md), [docs/task_ledger.md](../../../../task_ledger.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–16](../../../../../tests/unit/sql_rows_runtime_test.cpp#L1) | Imports dependencies; declares namespace scope; declares aliases; declares values/defaults or compile-time conditions. |  · [reviewed contract](#b0001) |
| [B0002 · 17–17](../../../../../tests/unit/sql_rows_runtime_test.cpp#L17) | Callable definition: Cell n(std::int64_t value) | calls ; returns storage::ScalarView{value} · [reviewed contract](#b0002) |
| [B0003 · 18–18](../../../../../tests/unit/sql_rows_runtime_test.cpp#L18) | Callable definition: Cell s(std::string_view value) | calls ; returns storage::ScalarView{value} · [reviewed contract](#b0003) |
| [B0004 · 19–19](../../../../../tests/unit/sql_rows_runtime_test.cpp#L19) | Callable definition: Value v(std::int64_t value) | calls ; returns value · [reviewed contract](#b0004) |
| [B0005 · 20–25](../../../../../tests/unit/sql_rows_runtime_test.cpp#L20) | Callable definition: frontend::SqlRowsProgram compile_rows(std::string_view sql, const Catalog& catalog) | calls frontend::bind_sql_rows, Error, std::move; returns std::get&lt;frontend::SqlRowsProgram&gt;(std::move(result)) · [reviewed contract](#b0005) |
| [B0006 · 26–32](../../../../../tests/unit/sql_rows_runtime_test.cpp#L26) | Callable definition: FreeConnexTree tree_for(const frontend::SqlRowsProgram& program) | calls contradiction, export_core, planner::minimum_tree, assert; guard assert(result.status == planner::OracleStatus::proven_minimum && result.tree);; returns {}; *result.tree · [reviewed contract](#b0006) |
| [B0007 · 33–35](../../../../../tests/unit/sql_rows_runtime_test.cpp#L33) | Callable definition: SqlRowsRuntime create(const frontend::SqlRowsProgram& program, bool indexed, sql_rows::Options options = {}) | calls SqlRowsRuntime, tree_for, s04_runtime::options; returns SqlRowsRuntime(program, tree_for(program), indexed ? s04_runtime::options() : PhysicalOptions{}, op… · [reviewed contract](#b0007) |
| [B0008 · 36–43](../../../../../tests/unit/sql_rows_runtime_test.cpp#L36) | Callable definition: Bag drain(SqlRowsRuntime::ResultCursor& cursor) | calls next, emplace, export_values, assert; guard static_cast&lt;void&gt;(item); assert(fresh); // Compressed output must already be unique.; returns result; growth emplace; 1 loop sites; source comment (unverified): // Compressed output must already be unique. · [reviewed contract](#b0008) |
| [B0009 · 44–44](../../../../../tests/unit/sql_rows_runtime_test.cpp#L44) | Callable definition: Bag results(const SqlRowsRuntime& runtime) | calls drain; returns drain(cursor) · [reviewed contract](#b0009) |
| [B0010 · 45–48](../../../../../tests/unit/sql_rows_runtime_test.cpp#L45) | Callable definition: sql_rows::Epoch replace(SqlRowsRuntime& runtime, std::size_t source, const Cells& row, std::uint64_t before, std::uint64_t after) | calls apply, sequence; returns runtime.apply({runtime.sequence() + 1, TableId{source}, row, before, after}) · [reviewed contract](#b0010) |
| [B0011 · 49–52](../../../../../tests/unit/sql_rows_runtime_test.cpp#L49) | Callable definition: template&lt;class Action&gt; void error(Action action, std::string_view expected) | calls action, assert, code; guard try { action(); } catch (const Error& failure) { assert(failure.code() == expected); return; } · [reviewed contract](#b0011) |
| [B0012 · 53–55](../../../../../tests/unit/sql_rows_runtime_test.cpp#L53) | Callable definition: Catalog rows_schema() | calls ; returns {1, {{@ , {{@ , ScalarType::int64, true}, {@ , ScalarType::string, true}}}}} · [reviewed contract](#b0012) |
| [B0013 · 56–58](../../../../../tests/unit/sql_rows_runtime_test.cpp#L56) | Explanatory comments or spacing. | source comment (unverified): // Full rows differing only in hidden columns contribute to the same native · [reviewed contract](#b0013) |
| [B0014 · 59–79](../../../../../tests/unit/sql_rows_runtime_test.cpp#L59) | Callable definition: void projection_and_nulls(bool indexed) | calls rows_schema, create, compile_rows, n; guard assert(replace(bag, 0, a, 0, 2).changed); replace(bag, 0, b, 0, 3); replace(bag, 0, null, 0, 7);; source comment (unverified): // Full rows differing only in hidden columns contribute to the same native · [reviewed contract](#b0014) |
| [B0015 · 80–80](../../../../../tests/unit/sql_rows_runtime_test.cpp#L80) | Explanatory comments or spacing. |  |
| [B0016 · 81–100](../../../../../tests/unit/sql_rows_runtime_test.cpp#L81) | Callable definition: void aliases_and_lifetime(bool indexed) | calls compile_rows, rows_schema, create, original; guard assert(runtime.root_weight().value == 25); · [reviewed contract](#b0016) |
| [B0017 · 101–101](../../../../../tests/unit/sql_rows_runtime_test.cpp#L101) | Explanatory comments or spacing. |  |
| [B0018 · 102–130](../../../../../tests/unit/sql_rows_runtime_test.cpp#L102) | Callable definition: void constants_exists_and_types(bool indexed) | calls create, compile_rows, assert, results; guard assert((results(runtime) == (present ? Bag{{Row{std::nullopt, Value{true}}, 1}} : Bag{})));; 2 loop sites · [reviewed contract](#b0018) |
| [B0019 · 131–131](../../../../../tests/unit/sql_rows_runtime_test.cpp#L131) | Explanatory comments or spacing. |  |
| [B0020 · 132–167](../../../../../tests/unit/sql_rows_runtime_test.cpp#L132) | Callable definition: void constraints(bool indexed) | calls push_back, create, compile_rows, n; guard assert(runtime.sequence() == 0 && runtime.source_weight(TableId{1}, one) == 0);; growth push_back; source comment (unverified): // A weight change still represents one live FK row. · [reviewed contract](#b0020) |
| [B0021 · 168–170](../../../../../tests/unit/sql_rows_runtime_test.cpp#L168) | Explanatory comments or spacing. | source comment (unverified): // Fail every allocation in a two-alias insertion, including after the first · [reviewed contract](#b0021) |
| [B0022 · 171–193](../../../../../tests/unit/sql_rows_runtime_test.cpp#L171) | Callable definition: void allocation_failures(bool indexed, bool capture) | calls compile_rows, rows_schema, n, s; guard assert(runtime.root_weight().value == 25);; 1 loop sites; source comment (unverified): // Fail every allocation in a two-alias insertion, including after the first · [reviewed contract](#b0022) |
| [B0023 · 194–194](../../../../../tests/unit/sql_rows_runtime_test.cpp#L194) | Explanatory comments or spacing. |  |
| [B0024 · 195–212](../../../../../tests/unit/sql_rows_runtime_test.cpp#L195) | Callable definition: void source_work_limits(bool indexed) | calls compile_rows, rows_schema, n, s; guard assert(value); --value;; 1 loop sites · [reviewed contract](#b0024) |
| [B0025 · 213–213](../../../../../tests/unit/sql_rows_runtime_test.cpp#L213) | Explanatory comments or spacing. |  |
| [B0026 · 214–260](../../../../../tests/unit/sql_rows_runtime_test.cpp#L214) | Callable definition: void receiving_account_and_output_failures(bool indexed) | calls compile_rows, rows_schema, tree_for, s04_runtime::options; guard assert(runtime.program().account().statistics().owner == account.statistics().owner);; returns account.statistics().peak_requested_bytes; growth allocate; 1 loop sites; source comment (unverified): // Native product overflow after one alias has changed must abort the source · [reviewed contract](#b0026) |
| [B0027 · 261–261](../../../../../tests/unit/sql_rows_runtime_test.cpp#L261) | Explanatory comments or spacing. |  |
| [B0028 · 262–276](../../../../../tests/unit/sql_rows_runtime_test.cpp#L262) | Callable definition: void result_schema_lifetime(bool indexed) | calls compile_rows, rows_schema, create, text; guard auto cursor = runtime.results(); auto result = cursor.next(); assert(result); return std::move(*res…; returns std::move(*result) · [reviewed contract](#b0028) |
| [B0029 · 277–277](../../../../../tests/unit/sql_rows_runtime_test.cpp#L277) | Explanatory comments or spacing. |  |
| [B0030 · 278–305](../../../../../tests/unit/sql_rows_runtime_test.cpp#L278) | Callable definition: void cursor_ownership(bool indexed) | calls compile_rows, rows_schema, n, s; guard assert(failed && runtime.ready() && runtime.sequence() == 1);; returns owner.results(); 2 loop sites · [reviewed contract](#b0030) |
| [B0031 · 306–307](../../../../../tests/unit/sql_rows_runtime_test.cpp#L306) | Closes surrounding scope/type. | source comment (unverified): // namespace · [reviewed contract](#b0031) |
| [B0032 · 308–319](../../../../../tests/unit/sql_rows_runtime_test.cpp#L308) | Callable definition: int main() | calls projection_and_nulls, aliases_and_lifetime, constants_exists_and_types, constraints; returns 1; 2 loop sites · [reviewed contract](#b0032) |

## B0001

[Lines 1–16](../../../../../tests/unit/sql_rows_runtime_test.cpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L1-L16:sha256:aad8216b38701877cb017c7ae509a8e20c3c4caf238a7d381121246dc9d0d24e
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Prepare sql_rows_runtime_test.cpp: include "crown/runtime/sql_rows.hpp", "crown/planner/oracle.hpp", "indexed_runtime_fixture.hpp", "index_allocation.hpp", &lt;array&gt;, &lt;cassert&gt;, &lt;iostream&gt;, &lt;map&gt;; bind local aliases/name imports. |
| inputs / outputs | Compiler-visible dependencies, names and the recorded declarations in; declarations available to the following fixture/CLI/example definitions out. |
| invariants | Declarations are scoped to this source/header and its selected ABI. Included code has its own effects; names and editable fixture values do not confer proof, admission or publication authority. |
| ownership | Aliases/includes do not create a query owner. Pointers/references/views are non-owning. Containers own their elements, which can themselves be borrowed pointers or numeric IDs. Only documented owning shared-control handles retain controls; IDs/slot-handle values do not independently keep an arena/runtime alive. |
| failure | Missing headers, ill-formed names/types, failed static assertions or active #error directives stop compilation. No runtime rejection/rollback mechanism is implemented by aliases or function prototypes. |
| cost | Preprocessing and type/constraint instantiation cost compilation. Alias/prototype syntax does not invoke the declared operation; any included definitions keep their own initialization effects. |
| Design | [tests/unit/sql_rows_runtime_test.cpp](../../../../../tests/unit/sql_rows_runtime_test.cpp), [docs/sql_rows_batches.md](../../../../sql_rows_batches.md), [docs/code_review.md](../../../../code_review.md) |

## B0002

[Lines 17–17](../../../../../tests/unit/sql_rows_runtime_test.cpp#L17); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Cell n(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Create an inline integer test cell. |
| inputs / outputs | int64 to present Cell. |
| invariants | No implicit bool/integer confusion. |
| ownership | Inline value only. |
| failure | No throwing operation. |
| cost | Constant. |
| Design | [docs/sql_rows_runtime.md](../../../../sql_rows_runtime.md), [docs/sql_rows.md](../../../../sql_rows.md), [Refactor.md §W05](../../../../../Refactor.md) |

## B0003

[Lines 18–18](../../../../../tests/unit/sql_rows_runtime_test.cpp#L18); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Cell s(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Borrow test text without ownership conversion. |
| inputs / outputs | string_view to present Cell. |
| invariants | Caller must keep bytes live through apply. |
| ownership | Borrowed text. |
| failure | No throwing operation. |
| cost | Constant, no allocation. |
| Design | [docs/sql_rows_runtime.md](../../../../sql_rows_runtime.md), [docs/sql_rows.md](../../../../sql_rows.md), [Refactor.md §W05](../../../../../Refactor.md) |

## B0004

[Lines 19–19](../../../../../tests/unit/sql_rows_runtime_test.cpp#L19); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Value v(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Construct expected owning integer values. |
| inputs / outputs | int64 to Value. |
| invariants | Used outside native measurement. |
| ownership | Inline expected scalar. |
| failure | No throwing operation. |
| cost | Constant. |
| Design | [docs/sql_rows_runtime.md](../../../../sql_rows_runtime.md), [docs/sql_rows.md](../../../../sql_rows.md), [Refactor.md §W05](../../../../../Refactor.md) |

## B0005

[Lines 20–25](../../../../../tests/unit/sql_rows_runtime_test.cpp#L20); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
frontend::SqlRowsProgram compile_rows(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Compile finite fixture SQL with actual frontend. |
| inputs / outputs | SQL/catalog to immutable program. |
| invariants | No fallback on rejection. |
| ownership | Factory owns metadata. |
| failure | Unexpected diagnostic reaches main. |
| cost | Cold compile costs. |
| Design | [docs/sql_rows_runtime.md](../../../../sql_rows_runtime.md), [docs/sql_rows.md](../../../../sql_rows.md), [Refactor.md §W05](../../../../../Refactor.md) |

## B0006

[Lines 26–32](../../../../../tests/unit/sql_rows_runtime_test.cpp#L26); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
FreeConnexTree tree_for(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Choose an independently checked fixture tree. |
| inputs / outputs | Actual export to checked minimum tree; contradiction to empty tree. |
| invariants | No hand-forged validity flag. |
| ownership | Test owns cold exported DTO/proof. |
| failure | Incomplete/unsupported result fails assertion. |
| cost | Cold exact search/replay, not update work. |
| Design | [docs/sql_rows_runtime.md](../../../../sql_rows_runtime.md), [docs/sql_rows.md](../../../../sql_rows.md), [Refactor.md §W05](../../../../../Refactor.md) |

## B0007

[Lines 33–35](../../../../../tests/unit/sql_rows_runtime_test.cpp#L33); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
SqlRowsRuntime create(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Run the same fixture on both native storage backends. |
| inputs / outputs | Program/backend/options to owner. |
| invariants | Only physical backend changes. |
| ownership | Runtime creates its documented account. |
| failure | Constructor rejection propagates. |
| cost | Cold owner construction. |
| Design | [docs/sql_rows_runtime.md](../../../../sql_rows_runtime.md), [docs/sql_rows.md](../../../../sql_rows.md), [Refactor.md §W05](../../../../../Refactor.md) |

## B0008

[Lines 36–43](../../../../../tests/unit/sql_rows_runtime_test.cpp#L36); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Bag drain(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Observe complete owning compressed output. |
| inputs / outputs | SQL cursor to ordinary expected-comparison bag. |
| invariants | Duplicate compressed keys fail rather than being silently summed. |
| ownership | Caller-owned exported rows. |
| failure | Unexpected duplicate/output failure fails the test. |
| cost | Full explicit output traversal/copy outside update intervals. |
| Design | [docs/sql_rows_runtime.md](../../../../sql_rows_runtime.md), [docs/sql_rows.md](../../../../sql_rows.md), [Refactor.md §W05](../../../../../Refactor.md) |

## B0009

[Lines 44–44](../../../../../tests/unit/sql_rows_runtime_test.cpp#L44); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Bag results(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Acquire and exhaust one inspection cursor. |
| inputs / outputs | Runtime to observed Bag. |
| invariants | Terminal next releases the reader. |
| ownership | Local cursor closes on all exits. |
| failure | Output failure propagates. |
| cost | Full result diagnostic, not update work. |
| Design | [docs/sql_rows_runtime.md](../../../../sql_rows_runtime.md), [docs/sql_rows.md](../../../../sql_rows.md), [Refactor.md §W05](../../../../../Refactor.md) |

## B0010

[Lines 45–48](../../../../../tests/unit/sql_rows_runtime_test.cpp#L45); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
sql_rows::Epoch replace(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Use the next real owner sequence in tests. |
| inputs / outputs | Source/full cells/before/after to apply. |
| invariants | Does not alter row identity or infer before. |
| ownership | Borrows row during synchronous call. |
| failure | Runtime failure propagates. |
| cost | Constant wrapper plus actual apply. |
| Design | [docs/sql_rows_runtime.md](../../../../sql_rows_runtime.md), [docs/sql_rows.md](../../../../sql_rows.md), [Refactor.md §W05](../../../../../Refactor.md) |

## B0011

[Lines 49–52](../../../../../tests/unit/sql_rows_runtime_test.cpp#L49); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
template<class Action> void error(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Assert an exact public rejection code. |
| inputs / outputs | Action and expected code. |
| invariants | Unexpected/no rejection fails; exceptions are not swallowed as success. |
| ownership | Temporary test action only. |
| failure | Assertion/main handles mismatch. |
| cost | One finite error-path test. |
| Design | [docs/sql_rows_runtime.md](../../../../sql_rows_runtime.md), [docs/sql_rows.md](../../../../sql_rows.md), [Refactor.md §W05](../../../../../Refactor.md) |

## B0012

[Lines 53–55](../../../../../tests/unit/sql_rows_runtime_test.cpp#L53); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Catalog rows_schema()
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Declare the nullable physical fixture. |
| inputs / outputs | One bigint/text source. |
| invariants | Both columns are nullable; full hidden text still belongs to row identity. |
| ownership | Ordinary cold test catalog. |
| failure | Ordinary allocation may throw. |
| cost | Fixed fixture creation. |
| Design | [docs/sql_rows_runtime.md](../../../../sql_rows_runtime.md), [docs/sql_rows.md](../../../../sql_rows.md), [Refactor.md §W05](../../../../../Refactor.md) |

## B0013

[Lines 56–58](../../../../../tests/unit/sql_rows_runtime_test.cpp#L56); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L56-L58:sha256:77bdd3ec6b6b06f8a8140f910fcb744e8143b62350ff84c323662796d9226a1b
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Explain the adjacent source contract: Full rows differing only in hidden columns contribute to the same native row; changing one source share must preserve all the other shares. |
| inputs / outputs | Human-readable source note in; no executable output or checked receipt. |
| invariants | This comment states context or a limitation. It does not itself enforce or prove the described behavior; use the adjacent implementation and its scoped contract. |
| ownership | Source text only; no object or resource lifetime is created. |
| failure | No runtime failure path in this comment; source encoding/comment syntax still belongs to compilation. |
| cost | No runtime operations from the comment. Any work described in the note belongs to the adjacent operation. |
| Design | [tests/unit/sql_rows_runtime_test.cpp](../../../../../tests/unit/sql_rows_runtime_test.cpp), [docs/sql_rows_batches.md](../../../../sql_rows_batches.md), [docs/code_review.md](../../../../code_review.md) |

## B0014

[Lines 59–79](../../../../../tests/unit/sql_rows_runtime_test.cpp#L59); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void projection_and_nulls(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Verify consolidation, DISTINCT, NULL separation and filtered/no-op sources. |
| inputs / outputs | Both backends and hand-computed bags. |
| invariants | Hidden-row shares sum; NULL differs from zero; source changes survive filtering; wrong before rejects. |
| ownership | Runtime owns input copies and explicit cursors export outputs. |
| failure | Assertions catch lost shares/sequence changes. |
| cost | Finite updates/full diagnostics; no speed claim. |
| Design | [docs/sql_rows_runtime.md](../../../../sql_rows_runtime.md), [docs/sql_rows.md](../../../../sql_rows.md), [Refactor.md §W05](../../../../../Refactor.md) |

## B0016

[Lines 81–100](../../../../../tests/unit/sql_rows_runtime_test.cpp#L81); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void aliases_and_lifetime(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Verify self-alias products and borrowed/owning lifetimes. |
| inputs / outputs | Two x=7 source shares and a NULL key. |
| invariants | Root 25 yields weights 10/15; NULL does not join; multiple readers block updates through last result. |
| ownership | Caller text may change after apply; returned tuples remain independent. |
| failure | Busy and retained-payload assertions expose violations. |
| cost | Finite hand result and lease checks. |
| Design | [docs/sql_rows_runtime.md](../../../../sql_rows_runtime.md), [docs/sql_rows.md](../../../../sql_rows.md), [Refactor.md §W05](../../../../../Refactor.md) |

## B0018

[Lines 102–130](../../../../../tests/unit/sql_rows_runtime_test.cpp#L102); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void constants_exists_and_types(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Verify constant routes, EXISTS and exact admitted scalar domains. |
| inputs / outputs | No-FROM/contradiction/typed rows and invalid text. |
| invariants | NULL, false, empty text, dates, tiny/wide numeric values stay typed; invalid UTF8/NUL reject. |
| ownership | Explicit owning output diagnostics. |
| failure | Domain/sequence assertions fail on incorrect admission. |
| cost | Finite typed cases, not exhaustive PostgreSQL domain coverage. |
| Design | [docs/sql_rows_runtime.md](../../../../sql_rows_runtime.md), [docs/sql_rows.md](../../../../sql_rows.md), [Refactor.md §W05](../../../../../Refactor.md) |

## B0020

[Lines 132–167](../../../../../tests/unit/sql_rows_runtime_test.cpp#L132); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void constraints(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Verify immediate UNIQUE/FK/self/empty-key enforcement. |
| inputs / outputs | Parent-child/self schemas and before/after rows. |
| invariants | NULLS DISTINCT, MATCH SIMPLE, weight-only FK presence, last-parent checks and unit-key extension hold. |
| ownership | All checks use actual runtime source/key state. |
| failure | Rejected constraints must not publish source rows or epochs. |
| cost | Finite successful/error traces on both backends. |
| Design | [docs/sql_rows_runtime.md](../../../../sql_rows_runtime.md), [docs/sql_rows.md](../../../../sql_rows.md), [Refactor.md §W05](../../../../../Refactor.md) |

## B0021

[Lines 168–170](../../../../../tests/unit/sql_rows_runtime_test.cpp#L168); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L168-L170:sha256:dc3c662a6efd4e682f1ef1024cd778b4a6fe2c7d6b1efe8657ec919e9bd3bb0b
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Explain the adjacent source contract: Fail every allocation in a two-alias insertion, including after the first alias has changed tentative state. Retry verifies source and native rollback. |
| inputs / outputs | Human-readable source note in; no executable output or checked receipt. |
| invariants | This comment states context or a limitation. It does not itself enforce or prove the described behavior; use the adjacent implementation and its scoped contract. |
| ownership | Source text only; no object or resource lifetime is created. |
| failure | No runtime failure path in this comment; source encoding/comment syntax still belongs to compilation. |
| cost | No runtime operations from the comment. Any work described in the note belongs to the adjacent operation. |
| Design | [tests/unit/sql_rows_runtime_test.cpp](../../../../../tests/unit/sql_rows_runtime_test.cpp), [docs/sql_rows_batches.md](../../../../sql_rows_batches.md), [docs/code_review.md](../../../../code_review.md) |

## B0022

[Lines 171–193](../../../../../tests/unit/sql_rows_runtime_test.cpp#L171); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void allocation_failures(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Fail every allocation in one two-alias replacement. |
| inputs / outputs | Backend/capture fixture to measured cut count. |
| invariants | Every cut restores source/native/sequence/readiness and permits same-sequence retry. |
| ownership | Fresh owner per cut avoids fault-history contamination. |
| failure | Only expected bad_alloc counts as the injected failure. |
| cost | Exhaustive positions for this fixture; no global unique-count or timing claim. |
| Design | [docs/sql_rows_runtime.md](../../../../sql_rows_runtime.md), [docs/sql_rows.md](../../../../sql_rows.md), [Refactor.md §W05](../../../../../Refactor.md) |

## B0024

[Lines 195–212](../../../../../tests/unit/sql_rows_runtime_test.cpp#L195); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void source_work_limits(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Verify shared source-work exact/one-under limits. |
| inputs / outputs | Two-alias filtered fixture and measured admissions. |
| invariants | Structural one-under can fail after an earlier alias staged; source/native state still roll back. |
| ownership | Limits are value copies of the measured whole replacement. |
| failure | Fixed IndexFailure work code is required. |
| cost | Three finite admission dimensions per backend; not total CPU accounting. |
| Design | [docs/sql_rows_runtime.md](../../../../sql_rows_runtime.md), [docs/sql_rows.md](../../../../sql_rows.md), [Refactor.md §W05](../../../../../Refactor.md) |

## B0026

[Lines 214–260](../../../../../tests/unit/sql_rows_runtime_test.cpp#L214); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void receiving_account_and_output_failures(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Verify actual receiver caps, output failure and arithmetic rollback. |
| inputs / outputs | Existing 128-byte resident; exact/one-under peak; output allocation cuts; overflowing self product. |
| invariants | Options cannot replace receiver cap; failed output closes its reader; source/runtime stay old on overflow. |
| ownership | Compiler account remains unchanged; emitted tuple uses receiver. |
| failure | Expected MemoryFailure/bad_alloc/annotation_overflow; original state remains. |
| cost | Exact fixture peaks/five observed next positions, not broad throughput evidence. |
| Design | [docs/sql_rows_runtime.md](../../../../sql_rows_runtime.md), [docs/sql_rows.md](../../../../sql_rows.md), [Refactor.md §W05](../../../../../Refactor.md) |

## B0028

[Lines 262–276](../../../../../tests/unit/sql_rows_runtime_test.cpp#L262); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void result_schema_lifetime(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Verify complete result ownership after all earlier owners die. |
| inputs / outputs | One retained nullable result/schema. |
| invariants | Names, SQL kind and numeric(10,2) metadata survive with text payload. |
| ownership | Result retains its query account and immutable program. |
| failure | Lifetime/schema assertions expose dangling or missing metadata. |
| cost | Finite teardown check; schema sharing adds no measured allocation. |
| Design | [docs/sql_rows_runtime.md](../../../../sql_rows_runtime.md), [docs/sql_rows.md](../../../../sql_rows.md), [Refactor.md §W05](../../../../../Refactor.md) |

## B0030

[Lines 278–305](../../../../../tests/unit/sql_rows_runtime_test.cpp#L278); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void cursor_ownership(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Verify wrapper-construction cleanup and detached/EXISTS readers. |
| inputs / outputs | Every results-constructor allocation cut plus owner teardown and false/true EXISTS. |
| invariants | All constructor failures release exclusion; detached cursor still emits; EXISTS holds lease through final Boolean. |
| ownership | Native cursor/program own needed state after wrapper destruction. |
| failure | Expected bad_alloc; readiness/lifetime assertions catch leaked readers. |
| cost | Finite constructor cuts and reader cases per backend. |
| Design | [docs/sql_rows_runtime.md](../../../../sql_rows_runtime.md), [docs/sql_rows.md](../../../../sql_rows.md), [Refactor.md §W05](../../../../../Refactor.md) |

## B0031

[Lines 306–307](../../../../../tests/unit/sql_rows_runtime_test.cpp#L306); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L306-L307:sha256:c2bd7638f09d52cb034ed574f539304035fc6fab162bf8d5fa20a35d8c7288a1
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Close the recorded declaration scopes in sql_rows_runtime_test.cpp: namespace (anonymous). |
| inputs / outputs | Preceding namespace, type or initializer declarations in; completed lexical boundary out. |
| invariants | Brace-opening context is recorded in root-scope-context-v1.json. These are declaration/initializer boundaries, not an independent update, validation or recovery operation. |
| ownership | Enclosing objects and borrowed fields keep their declared ownership. This punctuation creates no new owner. |
| failure | Malformed scope syntax is a compile error. Any initializer/constructor failure belongs to the enclosing object declaration. |
| cost | No separate loop, guard or engine call is introduced by the delimiter; enclosing initialization and object lifetime still have their actual costs. |
| Design | [tests/unit/sql_rows_runtime_test.cpp](../../../../../tests/unit/sql_rows_runtime_test.cpp), [docs/sql_rows_batches.md](../../../../sql_rows_batches.md), [docs/code_review.md](../../../../code_review.md) |

## B0032

[Lines 308–319](../../../../../tests/unit/sql_rows_runtime_test.cpp#L308); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
int main()
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Execute all SQL rows unit scenarios on both backends. |
| inputs / outputs | Fixed cases and capture variants to exit status. |
| invariants | Runs every mandatory assertion; no skip/fallback. |
| ownership | Executable owns its allocation injector. |
| failure | One top-level reporting catch returns failure. |
| cost | Finite test suite; verification, not a benchmark. |
| Design | [docs/sql_rows_runtime.md](../../../../sql_rows_runtime.md), [docs/sql_rows.md](../../../../sql_rows.md), [Refactor.md §W05](../../../../../Refactor.md) |
