# `tests/unit/sql_aggregate_runtime_test.cpp` — block usage map

[Source](../../../../../tests/unit/sql_aggregate_runtime_test.cpp) · [Source index](../../../README.md) · [Subsystem contracts](../../../subsystem_contracts.md) · [Reviewed primitives](../../../primitives.md)

Exercise original-SQL source/group atomicity, arithmetic, grants and lifetimes.

Snapshot SHA-256: `50e73f86b795aec65e95840831b041073da707e6aa401a9329d00594d24853b1`. 437 lines partitioned into 33 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [tests](../../../subsystem_contracts.md#tests). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/code_review.md](../../../../code_review.md), [docs/reference_fuzz.md](../../../../reference_fuzz.md), [docs/task_ledger.md](../../../../task_ledger.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–21](../../../../../tests/unit/sql_aggregate_runtime_test.cpp#L1) | Imports dependencies; declares namespace scope; declares aliases; declares values/defaults or compile-time conditions. | source comment (unverified): // Full group key -&gt; output (not projected-output identity). · [reviewed contract](#b0001) |
| [B0002 · 22–22](../../../../../tests/unit/sql_aggregate_runtime_test.cpp#L22) | Callable definition: sql_rows::Cell n(std::int64_t value) | calls ; returns storage::ScalarView{value} · [reviewed contract](#b0002) |
| [B0003 · 23–23](../../../../../tests/unit/sql_aggregate_runtime_test.cpp#L23) | Callable definition: sql_rows::Cell s(std::string_view value) | calls ; returns storage::ScalarView{value} · [reviewed contract](#b0003) |
| [B0004 · 24–24](../../../../../tests/unit/sql_aggregate_runtime_test.cpp#L24) | Callable definition: aggregate::SqlValue v(std::int64_t value) | calls ; returns Value{value} · [reviewed contract](#b0004) |
| [B0005 · 25–25](../../../../../tests/unit/sql_aggregate_runtime_test.cpp#L25) | Callable definition: aggregate::SqlValue t(std::string value) | calls std::move; returns Value{std::move(value)} · [reviewed contract](#b0005) |
| [B0006 · 26–26](../../../../../tests/unit/sql_aggregate_runtime_test.cpp#L26) | Callable definition: aggregate::SqlValue d(std::string_view value) | calls Decimal::parse; returns Value{Decimal::parse(value)} · [reviewed contract](#b0006) |
| [B0007 · 27–32](../../../../../tests/unit/sql_aggregate_runtime_test.cpp#L27) | Callable definition: Catalog schema() | calls ; returns {1, {{@ , {{@ , ScalarType::int64, true}, {@ , ScalarType::string, true}, · [reviewed contract](#b0007) |
| [B0008 · 33–35](../../../../../tests/unit/sql_aggregate_runtime_test.cpp#L33) | Callable definition: Cells row(sql_rows::Cell id, sql_rows::Cell group, sql_rows::Cell x, bool flag = true) | calls ; returns {id, group, x, storage::ScalarView{flag}} · [reviewed contract](#b0008) |
| [B0009 · 36–42](../../../../../tests/unit/sql_aggregate_runtime_test.cpp#L36) | Callable definition: Program compile(std::string_view sql, const Catalog& catalog = schema(), const frontend::SqlAggregateBindOptions& options = {}) | calls schema, frontend::bind_sql_aggregate, Error, std::move; returns std::get&lt;Program&gt;(std::move(bound)) · [reviewed contract](#b0009) |
| [B0010 · 43–53](../../../../../tests/unit/sql_aggregate_runtime_test.cpp#L43) | Callable definition: FreeConnexTree tree_for(const Program& program) | calls source_program, contradiction, export_core, planner::minimum_tree; guard assert(result.status == planner::OracleStatus::proven_minimum && result.tree);; returns {}; *result.tree · [reviewed contract](#b0010) |
| [B0011 · 54–56](../../../../../tests/unit/sql_aggregate_runtime_test.cpp#L54) | Callable definition: SqlAggregateRuntime create(const Program& program, bool indexed, sql_aggregate::Options options = {}) | calls SqlAggregateRuntime, tree_for, s04_runtime::options; returns SqlAggregateRuntime(program, tree_for(program), indexed ? s04_runtime::options() : PhysicalOptions{… · [reviewed contract](#b0011) |
| [B0012 · 57–61](../../../../../tests/unit/sql_aggregate_runtime_test.cpp#L57) | Callable definition: Results results(const SqlAggregateRuntime& runtime) | calls snapshot, assert, emplace, export_values; guard for (const auto& group : snapshot.groups) assert(result.emplace(group.key.export_values(), group.va…; returns result; growth emplace; 1 loop sites · [reviewed contract](#b0012) |
| [B0013 · 62–64](../../../../../tests/unit/sql_aggregate_runtime_test.cpp#L62) | Callable definition: sql_rows::SourceReplacement edit(std::size_t source, const Cells& values, std::uint64_t before, std::uint64_t after) | calls ; returns {TableId{source}, values, before, after} · [reviewed contract](#b0013) |
| [B0014 · 65–68](../../../../../tests/unit/sql_aggregate_runtime_test.cpp#L65) | Callable definition: template&lt;std::size_t N&gt; SqlAggregateRuntime::PreparedBatch prepare(SqlAggregateRuntime& runtime, const std::array&lt;sql_rows::Sourc… | calls prepare_batch, sequence; returns runtime.prepare_batch({runtime.sequence() + 1, edits}) · [reviewed contract](#b0014) |
| [B0015 · 69–72](../../../../../tests/unit/sql_aggregate_runtime_test.cpp#L69) | Callable definition: sql_aggregate::Epoch replace(SqlAggregateRuntime& runtime, std::size_t source, const Cells& values, std::uint64_t before, std::ui… | calls edit, prepare, commit; returns prepare(runtime, edits).commit() · [reviewed contract](#b0015) |
| [B0016 · 73–76](../../../../../tests/unit/sql_aggregate_runtime_test.cpp#L73) | Callable definition: template&lt;class Action&gt; void error(Action action, std::string_view expected) | calls action, assert, code; guard try { action(); } catch (const Error& failure) { assert(failure.code() == expected); return; } · [reviewed contract](#b0016) |
| [B0017 · 77–80](../../../../../tests/unit/sql_aggregate_runtime_test.cpp#L77) | Callable definition: void controller_only(const resource::MemoryAccount& account) | calls check_invariants, assert, statistics, resource::MemoryAccount::control_bytes; guard account.check_invariants(); assert(account.statistics().current.allocations == 1); · [reviewed contract](#b0017) |
| [B0018 · 81–83](../../../../../tests/unit/sql_aggregate_runtime_test.cpp#L81) | Explanatory comments or spacing. | source comment (unverified): // Physical nullable join edits, unused sources and multiple groups share one · [reviewed contract](#b0018) |
| [B0019 · 84–119](../../../../../tests/unit/sql_aggregate_runtime_test.cpp#L84) | Callable definition: void joined_groups(bool indexed) | calls compile, create, row, n; guard assert(!runtime.ready() && runtime.sequence() == 0 && pending.preview().sequence == 1);; source comment (unverified): // Physical nullable join edits, unused sources and multiple groups share one · [reviewed contract](#b0019) |
| [B0020 · 120–122](../../../../../tests/unit/sql_aggregate_runtime_test.cpp#L120) | Explanatory comments or spacing. | source comment (unverified): // Distinct physical rows with identical projected values and self-join aliases · [reviewed contract](#b0020) |
| [B0021 · 123–163](../../../../../tests/unit/sql_aggregate_runtime_test.cpp#L123) | Callable definition: void aliases_and_group_identity(bool indexed) | calls compile, create, row, n; guard assert((results(runtime) == Results{{SqlRow{t("a")}, SqlRow{t("a"),v(10),v(10),d("60"),d("6")}},; 1 loop sites; source comment (unverified): // Distinct physical rows with identical projected values and self-join aliases · [reviewed contract](#b0021) |
| [B0022 · 164–164](../../../../../tests/unit/sql_aggregate_runtime_test.cpp#L164) | Explanatory comments or spacing. |  |
| [B0023 · 165–200](../../../../../tests/unit/sql_aggregate_runtime_test.cpp#L165) | Callable definition: void global_constants_and_rounding(bool indexed) | calls compile, create, assert, results; guard assert((results(runtime) == Results{{SqlRow{}, SqlRow{v(0),v(0),{},{}}}})); · [reviewed contract](#b0023) |
| [B0024 · 201–201](../../../../../tests/unit/sql_aggregate_runtime_test.cpp#L201) | Explanatory comments or spacing. |  |
| [B0025 · 202–261](../../../../../tests/unit/sql_aggregate_runtime_test.cpp#L202) | Callable definition: void arithmetic_constraints_and_rollback(bool indexed) | calls compile, create, row, n; guard assert(runtime.ready() && runtime.sequence() == 1 && results(runtime) == baseline);; growth push_back · [reviewed contract](#b0025) |
| [B0026 · 262–265](../../../../../tests/unit/sql_aggregate_runtime_test.cpp#L262) | Explanatory comments or spacing. | source comment (unverified): // Physical edits reach the genuine source/native batch before the shared · [reviewed contract](#b0026) |
| [B0027 · 266–321](../../../../../tests/unit/sql_aggregate_runtime_test.cpp#L266) | Callable definition: void varying_integer_batches(bool indexed) | calls row, n, s, create; guard assert(runtime.sequence() == 0 && runtime.source_weight(TableId{0}, positive) == 0);; 2 loop sites; source comment (unverified): // Physical edits reach the genuine source/native batch before the shared · [reviewed contract](#b0027) |
| [B0028 · 322–322](../../../../../tests/unit/sql_aggregate_runtime_test.cpp#L322) | Explanatory comments or spacing. |  |
| [B0029 · 323–374](../../../../../tests/unit/sql_aggregate_runtime_test.cpp#L323) | Callable definition: void allocation_failure_commit_and_lifetime(bool indexed, bool integer) | calls compile, row, n, s; guard assert(allocations &gt; 0 && allocations &lt; 4096);; growth emplace; 1 loop sites; source comment (unverified): // Existing native high-water capacity is honest. · [reviewed contract](#b0029) |
| [B0030 · 375–375](../../../../../tests/unit/sql_aggregate_runtime_test.cpp#L375) | Explanatory comments or spacing. |  |
| [B0031 · 376–425](../../../../../tests/unit/sql_aggregate_runtime_test.cpp#L376) | Callable definition: void receiving_freeze_and_work(bool indexed, bool integer) | calls compile, resource::MemoryAccount::create, Program::freeze, assert; guard assert(frozen.identity().binding == foreign.identity().binding && frozen.work().composition == fore…; source comment (unverified): // Only receiver-backed metadata remains reachable below. · [reviewed contract](#b0031) |
| [B0032 · 426–427](../../../../../tests/unit/sql_aggregate_runtime_test.cpp#L426) | Closes surrounding scope/type. | source comment (unverified): // namespace · [reviewed contract](#b0032) |
| [B0033 · 428–437](../../../../../tests/unit/sql_aggregate_runtime_test.cpp#L428) | Callable definition: int main() | calls joined_groups, aliases_and_group_identity, global_constants_and_rounding, arithmetic_constraints_and_rollback; 2 loop sites · [reviewed contract](#b0033) |

## B0001

[Lines 1–21](../../../../../tests/unit/sql_aggregate_runtime_test.cpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
#include "crown/runtime/sql_aggregate.hpp" #include "crown/planner/oracle.hpp"
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Include the genuine public compiler/runtime, checked-tree, fixture and C++ allocation-fault interfaces used by this executable. |
| inputs / outputs | Translation unit imports SqlAggregateRuntime, public planner/oracle and source allocation fixture; no runtime input/output occurs at file scope. |
| invariants | All tests below invoke original SQL/Catalog factories; the fixture does not expose a logical-row contribution API. |
| ownership | Headers and aliases own no query state; function-local fixture/runtime objects own accounts and rows. |
| failure | Missing declarations/type/link failures are compile-time gates; no import-time runtime operation. |
| cost | Compile-time dependency context only. |
| Design | [tests/unit/sql_aggregate_runtime_test.cpp](../../../../../tests/unit/sql_aggregate_runtime_test.cpp), [docs/sql_aggregate_runtime.md](../../../../sql_aggregate_runtime.md), [tests/support/index_allocation.hpp](../../../../../tests/support/index_allocation.hpp), [docs/sql_rows_batches.md](../../../../sql_rows_batches.md), [include/crown/runtime/sql_aggregate.hpp](../../../../../include/crown/runtime/sql_aggregate.hpp), [include/crown/runtime/sql_rows.hpp](../../../../../include/crown/runtime/sql_rows.hpp), [docs/sql_aggregate_binding.md](../../../../sql_aggregate_binding.md) |

## B0002

[Lines 22–22](../../../../../tests/unit/sql_aggregate_runtime_test.cpp#L22); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
sql_rows::Cell n(std::int64_t value)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Wrap an int64 fixture scalar in the public nullable SQL-row cell representation. |
| inputs / outputs | int64 value in; Cell containing storage::ScalarView leaves. |
| invariants | The returned cell is non-null and references only the scalar payload; it does not create a physical row or authority. |
| ownership | Cell owns the variant wrapper, while any referenced string payload would remain borrowed; this overload has no string. |
| failure | No CROWN/runtime failure or allocation is expected. |
| cost | Fixed variant construction. |
| Design | tests/unit/sql_rows_runtime_test.cpp:14, [tests/unit/sql_aggregate_runtime_test.cpp](../../../../../tests/unit/sql_aggregate_runtime_test.cpp), [docs/sql_aggregate_runtime.md](../../../../sql_aggregate_runtime.md), [tests/support/index_allocation.hpp](../../../../../tests/support/index_allocation.hpp), [docs/sql_rows_batches.md](../../../../sql_rows_batches.md), [include/crown/runtime/sql_aggregate.hpp](../../../../../include/crown/runtime/sql_aggregate.hpp), [include/crown/runtime/sql_rows.hpp](../../../../../include/crown/runtime/sql_rows.hpp), [docs/sql_aggregate_binding.md](../../../../sql_aggregate_binding.md) |

## B0003

[Lines 23–23](../../../../../tests/unit/sql_aggregate_runtime_test.cpp#L23); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
sql_rows::Cell s(std::string_view value)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Wrap a borrowed string view in one nullable SQL-row Cell. |
| inputs / outputs | string_view in; Cell referring to those bytes leaves. |
| invariants | Caller must keep the source bytes alive until prepare_batch finishes copying retained keys/outputs. |
| ownership | The returned Cell does not own its string; fixture local storage must outlive synchronous preparation. |
| failure | Dangling caller bytes are outside the helper contract; the helper performs no admission. |
| cost | Fixed view/variant construction; no payload copy. |
| Design | tests/unit/sql_rows_runtime_test.cpp:14, [tests/unit/sql_aggregate_runtime_test.cpp](../../../../../tests/unit/sql_aggregate_runtime_test.cpp), [docs/sql_aggregate_runtime.md](../../../../sql_aggregate_runtime.md), [tests/support/index_allocation.hpp](../../../../../tests/support/index_allocation.hpp), [docs/sql_rows_batches.md](../../../../sql_rows_batches.md), [include/crown/runtime/sql_aggregate.hpp](../../../../../include/crown/runtime/sql_aggregate.hpp), [include/crown/runtime/sql_rows.hpp](../../../../../include/crown/runtime/sql_rows.hpp), [docs/sql_aggregate_binding.md](../../../../sql_aggregate_binding.md) |

## B0004

[Lines 24–24](../../../../../tests/unit/sql_aggregate_runtime_test.cpp#L24); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
aggregate::SqlValue v(std::int64_t value)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Make an owning SQL-value fixture for an int64 literal/parameter. |
| inputs / outputs | int64 in; aggregate::SqlValue holding Value(int64) out. |
| invariants | This is a compiler test literal, not a runtime physical cell or native fact. |
| ownership | Value/variant owns the scalar value. |
| failure | No runtime failure; ordinary variant construction. |
| cost | Fixed scalar construction. |
| Design | tests/unit/sql_rows_runtime_test.cpp:14, [tests/unit/sql_aggregate_runtime_test.cpp](../../../../../tests/unit/sql_aggregate_runtime_test.cpp), [docs/sql_aggregate_runtime.md](../../../../sql_aggregate_runtime.md), [tests/support/index_allocation.hpp](../../../../../tests/support/index_allocation.hpp), [docs/sql_rows_batches.md](../../../../sql_rows_batches.md), [include/crown/runtime/sql_aggregate.hpp](../../../../../include/crown/runtime/sql_aggregate.hpp), [include/crown/runtime/sql_rows.hpp](../../../../../include/crown/runtime/sql_rows.hpp), [docs/sql_aggregate_binding.md](../../../../sql_aggregate_binding.md) |

## B0005

[Lines 25–25](../../../../../tests/unit/sql_aggregate_runtime_test.cpp#L25); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
aggregate::SqlValue t(std::string value)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Make an owning SQL string literal fixture. |
| inputs / outputs | std::string moved in; SqlValue owns the string used by the binder. |
| invariants | The later bind reads original SQL/catalog arguments through the authentic frontend factory. |
| ownership | String storage is moved into Value and remains owned through binding. |
| failure | Ordinary string allocation may throw before runtime creation. |
| cost | One input string move; any copy/parse cost belongs to cold binding. |
| Design | tests/unit/sql_rows_runtime_test.cpp:14, [tests/unit/sql_aggregate_runtime_test.cpp](../../../../../tests/unit/sql_aggregate_runtime_test.cpp), [docs/sql_aggregate_runtime.md](../../../../sql_aggregate_runtime.md), [tests/support/index_allocation.hpp](../../../../../tests/support/index_allocation.hpp), [docs/sql_rows_batches.md](../../../../sql_rows_batches.md), [include/crown/runtime/sql_aggregate.hpp](../../../../../include/crown/runtime/sql_aggregate.hpp), [include/crown/runtime/sql_rows.hpp](../../../../../include/crown/runtime/sql_rows.hpp), [docs/sql_aggregate_binding.md](../../../../sql_aggregate_binding.md) |

## B0006

[Lines 26–26](../../../../../tests/unit/sql_aggregate_runtime_test.cpp#L26); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
aggregate::SqlValue d(std::string_view value)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Parse a decimal SQL literal into an owned frontend value. |
| inputs / outputs | string_view decimal spelling in; parsed Decimal inside SqlValue out. |
| invariants | The literal is represented by exact decimal value, not a floating point approximation. |
| ownership | Returned decimal owns its inline exact representation; source view is synchronous. |
| failure | Invalid decimal spelling propagates the decimal parser failure. |
| cost | Bounded parse proportional to short literal length. |
| Design | tests/unit/sql_rows_runtime_test.cpp:14, [tests/unit/sql_aggregate_runtime_test.cpp](../../../../../tests/unit/sql_aggregate_runtime_test.cpp), [docs/sql_aggregate_runtime.md](../../../../sql_aggregate_runtime.md), [tests/support/index_allocation.hpp](../../../../../tests/support/index_allocation.hpp), [docs/sql_rows_batches.md](../../../../sql_rows_batches.md), [include/crown/runtime/sql_aggregate.hpp](../../../../../include/crown/runtime/sql_aggregate.hpp), [include/crown/runtime/sql_rows.hpp](../../../../../include/crown/runtime/sql_rows.hpp), [docs/sql_aggregate_binding.md](../../../../sql_aggregate_binding.md) |

## B0007

[Lines 27–32](../../../../../tests/unit/sql_aggregate_runtime_test.cpp#L27); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Catalog schema()
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Return the concrete three-table test catalog for source and join cases. |
| inputs / outputs | No input; r(id,g,x,flag), s(id,y), and unused(z) schema out with nullable declarations as written. |
| invariants | Catalog is passed to the original SQL binder; fixture values do not certify a tree or alter compiler authority. |
| ownership | Returned Catalog owns its strings/column vectors; callers may copy it for per-case constraints. |
| failure | Ordinary catalog allocation may throw; invalid schemas are reported by actual binder. |
| cost | Small fixture allocation, outside measured runtime operations. |
| Design | tests/unit/sql_rows_runtime_test.cpp:14, [tests/unit/sql_aggregate_runtime_test.cpp](../../../../../tests/unit/sql_aggregate_runtime_test.cpp), [docs/sql_aggregate_runtime.md](../../../../sql_aggregate_runtime.md), [tests/support/index_allocation.hpp](../../../../../tests/support/index_allocation.hpp), [docs/sql_rows_batches.md](../../../../sql_rows_batches.md), [include/crown/runtime/sql_aggregate.hpp](../../../../../include/crown/runtime/sql_aggregate.hpp), [include/crown/runtime/sql_rows.hpp](../../../../../include/crown/runtime/sql_rows.hpp), [docs/sql_aggregate_binding.md](../../../../sql_aggregate_binding.md) |

## B0008

[Lines 33–35](../../../../../tests/unit/sql_aggregate_runtime_test.cpp#L33); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Cells row(sql_rows::Cell id, sql_rows::Cell group, sql_rows::Cell x, bool flag = true)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Build one complete physical r row with nullable id/group/value and boolean flag. |
| inputs / outputs | Four fixture cells/bool in; complete four-column Cells vector out in catalog order. |
| invariants | Cells remain typed and nullable; row is never reduced to selected SQL outputs. |
| ownership | Vector owns cell wrappers; string Cell views borrow fixture strings through prepare_batch. |
| failure | No validation here; actual source runtime validates arity, type, nullability and domain. |
| cost | O(1) fixed-width vector construction; no string payload copy. |
| Design | tests/unit/sql_rows_runtime_test.cpp:14, [tests/unit/sql_aggregate_runtime_test.cpp](../../../../../tests/unit/sql_aggregate_runtime_test.cpp), [docs/sql_aggregate_runtime.md](../../../../sql_aggregate_runtime.md), [tests/support/index_allocation.hpp](../../../../../tests/support/index_allocation.hpp), [docs/sql_rows_batches.md](../../../../sql_rows_batches.md), [include/crown/runtime/sql_aggregate.hpp](../../../../../include/crown/runtime/sql_aggregate.hpp), [include/crown/runtime/sql_rows.hpp](../../../../../include/crown/runtime/sql_rows.hpp), [docs/sql_aggregate_binding.md](../../../../sql_aggregate_binding.md) |

## B0009

[Lines 36–42](../../../../../tests/unit/sql_aggregate_runtime_test.cpp#L36); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Program compile(std::string_view sql, const Catalog& catalog = schema(), const frontend::SqlAggregateBindOptions& options = {})
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Bind original SQL/catalog through the genuine composed SQL aggregate frontend factory. |
| inputs / outputs | SQL text, owned Catalog and bind options in; SqlAggregateProgram out or a fixed Error converted from BindingDiagnostic. |
| invariants | Only this original SQL path produces opaque immutable descriptors; no manually rewritten source/kernel DTO enters. |
| ownership | Returned program owns compiler metadata under its compiler account; views used later borrow that owner. |
| failure | A binding diagnostic is converted to crown::Error with the exact code/message; parser/account failures propagate. |
| cost | Cold parse/bind/compiler work; outside an epoch group Budget. |
| Design | tests/unit/sql_rows_runtime_test.cpp:14, [tests/unit/sql_aggregate_runtime_test.cpp](../../../../../tests/unit/sql_aggregate_runtime_test.cpp), [docs/sql_aggregate_runtime.md](../../../../sql_aggregate_runtime.md), [tests/support/index_allocation.hpp](../../../../../tests/support/index_allocation.hpp), [docs/sql_rows_batches.md](../../../../sql_rows_batches.md), [include/crown/runtime/sql_aggregate.hpp](../../../../../include/crown/runtime/sql_aggregate.hpp), [include/crown/runtime/sql_rows.hpp](../../../../../include/crown/runtime/sql_rows.hpp), [docs/sql_aggregate_binding.md](../../../../sql_aggregate_binding.md) |

## B0010

[Lines 43–53](../../../../../tests/unit/sql_aggregate_runtime_test.cpp#L43); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
FreeConnexTree tree_for(const Program& program)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Obtain the checked source tree required by the runtime from the actual bound source program. |
| inputs / outputs | Genuine program in; empty tree for contradiction or proven minimum planner tree out. |
| invariants | Tree is produced from source_program().export_core(); only proven_minimum with a tree is accepted. |
| ownership | Returned FreeConnexTree owns its test data; source export is an explicit ordinary test copy. |
| failure | Planner rejection is printed with original/derived source context and assert fails. |
| cost | Cold planner oracle work per runtime fixture; not update-path work. |
| Design | tests/unit/sql_rows_runtime_test.cpp:26, [include/crown/planner/oracle.hpp](../../../../../include/crown/planner/oracle.hpp), [tests/unit/sql_aggregate_runtime_test.cpp](../../../../../tests/unit/sql_aggregate_runtime_test.cpp), [docs/sql_aggregate_runtime.md](../../../../sql_aggregate_runtime.md), [tests/support/index_allocation.hpp](../../../../../tests/support/index_allocation.hpp), [docs/sql_rows_batches.md](../../../../sql_rows_batches.md), [include/crown/runtime/sql_aggregate.hpp](../../../../../include/crown/runtime/sql_aggregate.hpp), [include/crown/runtime/sql_rows.hpp](../../../../../include/crown/runtime/sql_rows.hpp), [docs/sql_aggregate_binding.md](../../../../sql_aggregate_binding.md) |

## B0011

[Lines 54–56](../../../../../tests/unit/sql_aggregate_runtime_test.cpp#L54); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
SqlAggregateRuntime create(const Program& program, bool indexed, sql_aggregate::Options options = {})
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Construct the public runtime on ordered or indexed source storage with a checked authentic tree. |
| inputs / outputs | Program, indexed flag and options in; standalone SqlAggregateRuntime out. |
| invariants | Indexed choices use the existing S04 physical options; program/tree originate from helpers above. |
| ownership | Runtime owns its receiver and imported metadata; caller retains the original compiler handle. |
| failure | Runtime factory option, plan, account or source initialization failures propagate. |
| cost | Cold runtime construction and account/state initialization. |
| Design | tests/unit/sql_rows_runtime_test.cpp:14, [tests/unit/sql_aggregate_runtime_test.cpp](../../../../../tests/unit/sql_aggregate_runtime_test.cpp), [docs/sql_aggregate_runtime.md](../../../../sql_aggregate_runtime.md), [tests/support/index_allocation.hpp](../../../../../tests/support/index_allocation.hpp), [docs/sql_rows_batches.md](../../../../sql_rows_batches.md), [include/crown/runtime/sql_aggregate.hpp](../../../../../include/crown/runtime/sql_aggregate.hpp), [include/crown/runtime/sql_rows.hpp](../../../../../include/crown/runtime/sql_rows.hpp), [docs/sql_aggregate_binding.md](../../../../sql_aggregate_binding.md) |

## B0012

[Lines 57–61](../../../../../tests/unit/sql_aggregate_runtime_test.cpp#L57); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Results results(const SqlAggregateRuntime& runtime)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Read an eager runtime snapshot and export a full-key to output map for assertions. |
| inputs / outputs | Committed runtime in; ordinary std::map keyed by exported full group identity out. |
| invariants | Duplicate full group keys fail the assertion; equal projected outputs do not merge distinct keys. |
| ownership | Snapshot owns receiver-backed copies; export_values and map own separate test data after snapshot closes. |
| failure | Snapshot busy/result/work/account errors propagate; duplicate-key assertion fails the test. |
| cost | Explicit O(G*fields/bytes) snapshot/export and ordinary test allocations; not epoch capture cost. |
| Design | tests/unit/sql_rows_runtime_test.cpp:14, [tests/unit/sql_aggregate_runtime_test.cpp](../../../../../tests/unit/sql_aggregate_runtime_test.cpp), [docs/sql_aggregate_runtime.md](../../../../sql_aggregate_runtime.md), [tests/support/index_allocation.hpp](../../../../../tests/support/index_allocation.hpp), [docs/sql_rows_batches.md](../../../../sql_rows_batches.md), [include/crown/runtime/sql_aggregate.hpp](../../../../../include/crown/runtime/sql_aggregate.hpp), [include/crown/runtime/sql_rows.hpp](../../../../../include/crown/runtime/sql_rows.hpp), [docs/sql_aggregate_binding.md](../../../../sql_aggregate_binding.md) |

## B0013

[Lines 62–64](../../../../../tests/unit/sql_aggregate_runtime_test.cpp#L62); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
sql_rows::SourceReplacement edit(std::size_t source, const Cells& values, std::uint64_t before, std::uint64_t after)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Describe one complete physical source replacement with expected and final weight. |
| inputs / outputs | Table index, complete borrowed Cells, expected before and final after uint64 weights in; SourceReplacement out. |
| invariants | It carries source-row input only; source schema, exact expected chains and final constraints are checked by prepare_batch. |
| ownership | Returned replacement borrows the Cells vector and its strings only through synchronous preparation. |
| failure | No runtime validation here; malformed source ids/rows/weights fail in the real source child. |
| cost | Fixed descriptor construction. |
| Design | tests/unit/sql_rows_runtime_test.cpp:14, [tests/unit/sql_aggregate_runtime_test.cpp](../../../../../tests/unit/sql_aggregate_runtime_test.cpp), [docs/sql_aggregate_runtime.md](../../../../sql_aggregate_runtime.md), [tests/support/index_allocation.hpp](../../../../../tests/support/index_allocation.hpp), [docs/sql_rows_batches.md](../../../../sql_rows_batches.md), [include/crown/runtime/sql_aggregate.hpp](../../../../../include/crown/runtime/sql_aggregate.hpp), [include/crown/runtime/sql_rows.hpp](../../../../../include/crown/runtime/sql_rows.hpp), [docs/sql_aggregate_binding.md](../../../../sql_aggregate_binding.md) |

## B0014

[Lines 65–68](../../../../../tests/unit/sql_aggregate_runtime_test.cpp#L65); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
template<std::size_t N> SqlAggregateRuntime::PreparedBatch prepare(SqlAggregateRuntime& runtime, const std::array<sql_rows::SourceReplacement, N>& edits)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Prepare one array of source replacements at the owner’s next committed sequence. |
| inputs / outputs | Runtime plus fixed array of physical replacements in; active PreparedBatch preview token out. |
| invariants | Sequence is runtime.sequence()+1; original arrays/rows remain alive only until prepare returns. |
| ownership | Token owns copied proposals/preview and source child; caller retains fixture row storage until preparation completes. |
| failure | Real source, native, decoder, group/work, allocation or constraint failure propagates before token escape. |
| cost | Actual one-command preparation; array construction itself is external test work. |
| Design | tests/unit/sql_rows_runtime_test.cpp:14, [tests/unit/sql_aggregate_runtime_test.cpp](../../../../../tests/unit/sql_aggregate_runtime_test.cpp), [docs/sql_aggregate_runtime.md](../../../../sql_aggregate_runtime.md), [tests/support/index_allocation.hpp](../../../../../tests/support/index_allocation.hpp), [docs/sql_rows_batches.md](../../../../sql_rows_batches.md), [include/crown/runtime/sql_aggregate.hpp](../../../../../include/crown/runtime/sql_aggregate.hpp), [include/crown/runtime/sql_rows.hpp](../../../../../include/crown/runtime/sql_rows.hpp), [docs/sql_aggregate_binding.md](../../../../sql_aggregate_binding.md) |

## B0015

[Lines 69–72](../../../../../tests/unit/sql_aggregate_runtime_test.cpp#L69); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
sql_aggregate::Epoch replace(SqlAggregateRuntime& runtime, std::size_t source, const Cells& values, std::uint64_t before, std::uint64_t after)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Apply and commit one complete physical row replacement for small fixture setup. |
| inputs / outputs | Runtime, source index, complete row and expected/final weights in; owning committed sql_aggregate::Epoch out. |
| invariants | Uses prepare helper and one contiguous epoch; this shortcut does not bypass native source processing. |
| ownership | Temporary replacement/token die after commit; returned epoch owns requested outputs/program handles. |
| failure | Preparation failures preserve the old frontier; commit closes its token. |
| cost | One real full runtime transaction plus descriptor and returned output. |
| Design | tests/unit/sql_rows_runtime_test.cpp:14, [tests/unit/sql_aggregate_runtime_test.cpp](../../../../../tests/unit/sql_aggregate_runtime_test.cpp), [docs/sql_aggregate_runtime.md](../../../../sql_aggregate_runtime.md), [tests/support/index_allocation.hpp](../../../../../tests/support/index_allocation.hpp), [docs/sql_rows_batches.md](../../../../sql_rows_batches.md), [include/crown/runtime/sql_aggregate.hpp](../../../../../include/crown/runtime/sql_aggregate.hpp), [include/crown/runtime/sql_rows.hpp](../../../../../include/crown/runtime/sql_rows.hpp), [docs/sql_aggregate_binding.md](../../../../sql_aggregate_binding.md) |

## B0016

[Lines 73–76](../../../../../tests/unit/sql_aggregate_runtime_test.cpp#L73); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
template<class Action> void error(Action action, std::string_view expected)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Require a CROWN Error with one exact diagnostic code for a negative fixture. |
| inputs / outputs | Action and expected code in; returns only after matching crown::Error. |
| invariants | Catches only crown::Error; std::bad_alloc, storage::IndexFailure and unrelated exceptions are not silently accepted. |
| ownership | Borrows action; captures no runtime/token after return. |
| failure | Wrong code or no exception hits assertion; unexpected exception type propagates. |
| cost | One exceptional-path assertion helper; does not catch setup phases not inside action. |
| Design | tests/unit/sql_rows_runtime_test.cpp:14, [tests/unit/sql_aggregate_runtime_test.cpp](../../../../../tests/unit/sql_aggregate_runtime_test.cpp), [docs/sql_aggregate_runtime.md](../../../../sql_aggregate_runtime.md), [tests/support/index_allocation.hpp](../../../../../tests/support/index_allocation.hpp), [docs/sql_rows_batches.md](../../../../sql_rows_batches.md), [include/crown/runtime/sql_aggregate.hpp](../../../../../include/crown/runtime/sql_aggregate.hpp), [include/crown/runtime/sql_rows.hpp](../../../../../include/crown/runtime/sql_rows.hpp), [docs/sql_aggregate_binding.md](../../../../sql_aggregate_binding.md) |

## B0017

[Lines 77–80](../../../../../tests/unit/sql_aggregate_runtime_test.cpp#L77); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void controller_only(const resource::MemoryAccount& account)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Assert the receiving account has released all payloads and retains only its controller allocation. |
| inputs / outputs | MemoryAccount in; invariants checked, one current allocation, and requested bytes equal control_bytes asserted. |
| invariants | Call only after all runtime/token/output owners using the account are dropped; it does not measure global heap or native allocator outside this account. |
| ownership | Borrows account handle for statistics/check only. |
| failure | Ledger inconsistency or retained account payload fails check_invariants/assertion. |
| cost | Account invariant scan and fixed statistics read; not a runtime hot path. |
| Design | tests/unit/sql_rows_runtime_test.cpp:14, [tests/unit/sql_aggregate_runtime_test.cpp](../../../../../tests/unit/sql_aggregate_runtime_test.cpp), [docs/sql_aggregate_runtime.md](../../../../sql_aggregate_runtime.md), [tests/support/index_allocation.hpp](../../../../../tests/support/index_allocation.hpp), [docs/sql_rows_batches.md](../../../../sql_rows_batches.md), [include/crown/runtime/sql_aggregate.hpp](../../../../../include/crown/runtime/sql_aggregate.hpp), [include/crown/runtime/sql_rows.hpp](../../../../../include/crown/runtime/sql_rows.hpp), [docs/sql_aggregate_binding.md](../../../../sql_aggregate_binding.md) |

## B0018

[Lines 81–83](../../../../../tests/unit/sql_aggregate_runtime_test.cpp#L81); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
// Physical nullable join edits, unused sources and multiple groups share one // genuine source/native token. NULL equality does not join; NULL grouping does.
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Document the joined nullable-source fixture’s intended boundary cases. |
| inputs / outputs | Comment names a genuine physical NetBatch, unused source edits, multiple groups, SQL NULL join behavior and NULL grouping behavior; no executable input/output. |
| invariants | The following joined_groups case checks these semantics through actual source/native preparation and the group runtime. |
| ownership | Comment owns no values; fixture locals own rows through prepare. |
| failure | No executable failure; adjacent fixture assertions provide the oracle. |
| cost | No runtime cost beyond the following test function. |
| Design | [tests/unit/sql_aggregate_runtime_test.cpp](../../../../../tests/unit/sql_aggregate_runtime_test.cpp), [docs/sql_aggregate_runtime.md](../../../../sql_aggregate_runtime.md), [tests/support/index_allocation.hpp](../../../../../tests/support/index_allocation.hpp), [docs/sql_rows_batches.md](../../../../sql_rows_batches.md), [include/crown/runtime/sql_aggregate.hpp](../../../../../include/crown/runtime/sql_aggregate.hpp), [include/crown/runtime/sql_rows.hpp](../../../../../include/crown/runtime/sql_rows.hpp), [docs/sql_aggregate_binding.md](../../../../sql_aggregate_binding.md) |

## B0019

[Lines 84–119](../../../../../tests/unit/sql_aggregate_runtime_test.cpp#L84); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void joined_groups(bool indexed)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Check atomic nullable join/source/group behavior, busy frontier, captured outputs, ignored rows and empty epochs. |
| inputs / outputs | Ordered/indexed selector; actual SQL join and complete physical edits; asserts full-key snapshots, epoch flags/counters, source weights and rejection codes. |
| invariants | Uses genuine binder and minimum source tree. NULL join keys do not match; unused/filtered physical changes set changed but can leave group_changed false; no-op batch still advances one sequence. |
| ownership | Cells/string views are fixture-owned through each prepare; snapshot exports and returned Epoch own asserted results. |
| failure | Busy snapshot/reprepare codes and source/native/group results are asserted; a mismatch aborts the test. |
| cost | Finite fixed physical rows and small multiplicities on each backend; explicit snapshots add their own output-copy work. |
| Design | tests/unit/sql_rows_batch_test.cpp:230, [tests/unit/aggregate_runtime_test.cpp](../../../../../tests/unit/aggregate_runtime_test.cpp), [tests/unit/sql_aggregate_runtime_test.cpp](../../../../../tests/unit/sql_aggregate_runtime_test.cpp), [docs/sql_aggregate_runtime.md](../../../../sql_aggregate_runtime.md), [tests/support/index_allocation.hpp](../../../../../tests/support/index_allocation.hpp), [docs/sql_rows_batches.md](../../../../sql_rows_batches.md), [include/crown/runtime/sql_aggregate.hpp](../../../../../include/crown/runtime/sql_aggregate.hpp), [include/crown/runtime/sql_rows.hpp](../../../../../include/crown/runtime/sql_rows.hpp), [docs/sql_aggregate_binding.md](../../../../sql_aggregate_binding.md) |

## B0020

[Lines 120–122](../../../../../tests/unit/sql_aggregate_runtime_test.cpp#L120); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
// Distinct physical rows with identical projected values and self-join aliases // are consolidated by the genuine source/native producer, never a second ledger.
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Document self-join aliases and full original grouping identity covered by the following case. |
| inputs / outputs | Comment identifies duplicate projected values, source consolidation and original SQL GROUP BY identity; no executable I/O. |
| invariants | The function tests genuine source production and exact full keys, not a test-authored native fact list. |
| ownership | No values; following function owns its fixture. |
| failure | No executable failure in the comment. |
| cost | No runtime cost beyond following fixture. |
| Design | [tests/unit/sql_aggregate_runtime_test.cpp](../../../../../tests/unit/sql_aggregate_runtime_test.cpp), [docs/sql_aggregate_runtime.md](../../../../sql_aggregate_runtime.md), [tests/support/index_allocation.hpp](../../../../../tests/support/index_allocation.hpp), [docs/sql_rows_batches.md](../../../../sql_rows_batches.md), [include/crown/runtime/sql_aggregate.hpp](../../../../../include/crown/runtime/sql_aggregate.hpp), [include/crown/runtime/sql_rows.hpp](../../../../../include/crown/runtime/sql_rows.hpp), [docs/sql_aggregate_binding.md](../../../../sql_aggregate_binding.md) |

## B0021

[Lines 123–163](../../../../../tests/unit/sql_aggregate_runtime_test.cpp#L123); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void aliases_and_group_identity(bool indexed)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Check self-join cross terms, hidden/full group keys and compiler rejection of ungrouped original columns. |
| inputs / outputs | Real self-join/source rows and SQL binds in; asserts joined multiplicities, distinct hidden identities, nullable identity, qualified same-origin acceptance and three ungrouped_column diagnostics. |
| invariants | Native source producer consolidates aliases; equal output tuples do not merge full group keys; SQL origin is checked before normalized source equivalence. |
| ownership | Fixture rows borrow only through prepare; exported snapshots/epochs own explicit test data. |
| failure | Expected bind rejection checks exact diagnostic; all other runtime/assert failures fail the fixture. |
| cost | Small bounded self-join multipliers and snapshots on both storage backends. |
| Design | tests/unit/sql_rows_batch_test.cpp:230, [tests/unit/aggregate_runtime_test.cpp](../../../../../tests/unit/aggregate_runtime_test.cpp), [tests/unit/sql_aggregate_runtime_test.cpp](../../../../../tests/unit/sql_aggregate_runtime_test.cpp), [docs/sql_aggregate_runtime.md](../../../../sql_aggregate_runtime.md), [tests/support/index_allocation.hpp](../../../../../tests/support/index_allocation.hpp), [docs/sql_rows_batches.md](../../../../sql_rows_batches.md), [include/crown/runtime/sql_aggregate.hpp](../../../../../include/crown/runtime/sql_aggregate.hpp), [include/crown/runtime/sql_rows.hpp](../../../../../include/crown/runtime/sql_rows.hpp), [docs/sql_aggregate_binding.md](../../../../sql_aggregate_binding.md) |

## B0023

[Lines 165–200](../../../../../tests/unit/sql_aggregate_runtime_test.cpp#L165); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void global_constants_and_rounding(bool indexed)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Check global and grouped empty semantics, static source bootstrap, SQL constants and rounded-equal AVG suppression. |
| inputs / outputs | Real original SQL and bounded physical changes in; asserts empty/global COUNT/SUM/AVG, static weight 0/1, sequence-zero bootstrap, FROM-empty updates and capture output. |
| invariants | Global group remains at zero; grouped groups are represented by full key; group_changed may be true while rounded output is unchanged; static bootstrap consumes no operational sequence. |
| ownership | Runtime owns initial group/native source; rows/views are fixture-borrowed through preparation; epochs/snapshots own copied output. |
| failure | Compiler/runtime rejection or arithmetic/account failure propagates; assertions check expected exact values. |
| cost | Finite scalar/group cases, two backends, explicit snapshots and a few epochs; no large multiplicity expansion. |
| Design | tests/unit/sql_rows_batch_test.cpp:230, [tests/unit/aggregate_runtime_test.cpp](../../../../../tests/unit/aggregate_runtime_test.cpp), [tests/unit/sql_aggregate_runtime_test.cpp](../../../../../tests/unit/sql_aggregate_runtime_test.cpp), [docs/sql_aggregate_runtime.md](../../../../sql_aggregate_runtime.md), [tests/support/index_allocation.hpp](../../../../../tests/support/index_allocation.hpp), [docs/sql_rows_batches.md](../../../../sql_rows_batches.md), [include/crown/runtime/sql_aggregate.hpp](../../../../../include/crown/runtime/sql_aggregate.hpp), [include/crown/runtime/sql_rows.hpp](../../../../../include/crown/runtime/sql_rows.hpp), [docs/sql_aggregate_binding.md](../../../../sql_aggregate_binding.md) |

## B0025

[Lines 202–261](../../../../../tests/unit/sql_aggregate_runtime_test.cpp#L202); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void arithmetic_constraints_and_rollback(bool indexed)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Check final count/SUM and real source UNIQUE/FK constraints across atomic multirow updates. |
| inputs / outputs | Exact INT64 boundary multiplicities, group edits, unique swaps and parent/child final-state replacements in; asserts overflow/FK/UNIQUE codes, old snapshots/sequence/weights, valid retries and valid deletion. |
| invariants | Constraint/source validation belongs to genuine child token. Deletions/additions can swap final-valid key state independent of input order; group/result publication waits for child success. |
| ownership | Physical rows stay fixture-owned through prepare; failed token cleanup and committed snapshots use runtime owners. |
| failure | Final source-constraint, group count and SUM failures are asserted before publication; a failed command preserves old source/native/group frontier. |
| cost | Bounded number of rows/keys with compressed uint64 weights; arithmetic visits do not expand each occurrence copy. |
| Design | tests/unit/sql_rows_batch_test.cpp:230, [tests/unit/aggregate_runtime_test.cpp](../../../../../tests/unit/aggregate_runtime_test.cpp), [tests/unit/sql_aggregate_runtime_test.cpp](../../../../../tests/unit/sql_aggregate_runtime_test.cpp), [docs/sql_aggregate_runtime.md](../../../../sql_aggregate_runtime.md), [tests/support/index_allocation.hpp](../../../../../tests/support/index_allocation.hpp), [docs/sql_rows_batches.md](../../../../sql_rows_batches.md), [include/crown/runtime/sql_aggregate.hpp](../../../../../include/crown/runtime/sql_aggregate.hpp), [include/crown/runtime/sql_rows.hpp](../../../../../include/crown/runtime/sql_rows.hpp), [docs/sql_aggregate_binding.md](../../../../sql_aggregate_binding.md) |

## B0026

[Lines 262–265](../../../../../tests/unit/sql_aggregate_runtime_test.cpp#L262); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L262-L265:sha256:08aff15f8018ba231c979ce7e315427a6eb5bb64a975489ed42267d1e8856ef7
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Explain the adjacent source contract: Physical edits reach the genuine source/native batch before the shared integer guard. Final-only arithmetic permits signed cancellation; a refused cast/final sum must unwind that same token, including every source weight. |
| inputs / outputs | Human-readable source note in; no executable output or checked receipt. |
| invariants | This comment states context or a limitation. It does not itself enforce or prove the described behavior; use the adjacent implementation and its scoped contract. |
| ownership | Source text only; no object or resource lifetime is created. |
| failure | No runtime failure path in this comment; source encoding/comment syntax still belongs to compilation. |
| cost | No runtime operations from the comment. Any work described in the note belongs to the adjacent operation. |
| Design | [tests/unit/sql_aggregate_runtime_test.cpp](../../../../../tests/unit/sql_aggregate_runtime_test.cpp), [docs/aggregates.md](../../../../aggregates.md), [docs/code_review.md](../../../../code_review.md) |

## B0027

[Lines 266–321](../../../../../tests/unit/sql_aggregate_runtime_test.cpp#L266); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void varying_integer_batches(bool indexed)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Check integer semantics and rollback through genuine physical/native batches on each backend. |
| inputs / outputs | Captured/uncaptured signed compressed cancellation; inclusive min/max/NULL; nested COUNT; filtered activation, canceled transient, unmatched join activation and AVG-only wide numerator. |
| invariants | Refusal leaves source weights/root/group/sequence ready and unchanged. Filtered/unmatched/net-zero facts do not evaluate casts. Final-only SUM and wide AVG policies stay distinct. |
| ownership | Prepared token owns native/source/group proposals; physical buffers borrow only through prepare. |
| failure | aggregate_overflow is required for contributing cast/final SUM refusal; retry/rollback observations use public APIs. |
| cost | Finite compressed controls on two backends; no expansion, CPU or single-tuple-delay claim. |
| Design | [src/runtime/sql_aggregate.cpp](../../../../../src/runtime/sql_aggregate.cpp), [src/runtime/aggregate_detail.hpp](../../../../../src/runtime/aggregate_detail.hpp), [docs/sql_aggregate_runtime.md](../../../../sql_aggregate_runtime.md) |

## B0029

[Lines 323–374](../../../../../tests/unit/sql_aggregate_runtime_test.cpp#L323); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void allocation_failure_commit_and_lifetime(bool indexed, bool integer)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Fault every measured throwing C++ operator-new preparation request, then verify close, commit and owner/string lifetimes. |
| inputs / outputs | Run the same bounded C++ new preparation sweep, deny-zero close/commit and surviving-token/string lifetime controls for both raw bigint SUM and checked integer SUM on each backend. |
| invariants | Each injected std::bad_alloc leaves prior source/root/group/sequence unchanged and permits same-owner retry. The seam intercepts C++ operator new calls only, not arbitrary malloc/syscalls or every native allocator. Commit/rollback checks zero intercepted new calls; account comparisons acknowledge native high-water capacity. |
| ownership | Fixture rows/string borrow through prepare; prepared token retains outer owner and child; returned output/program own copied bytes; closed token releases workspace before external account comparison. |
| failure | Only expected std::bad_alloc cuts are caught; storage/native allocation failures outside this seam are not claimed. Wrong-state/retained-output assertions fail the fixture. |
| cost | Finite observed request-index sweeps (&lt;4096 per profile) over two SQL widths and two backends, plus state/output/account checks. Covered new attempts are separate from malloc, bytes/RSS and CPU. |
| Design | tests/support/index_allocation.hpp:11, tests/unit/sql_rows_batch_test.cpp:561, [tests/unit/sql_aggregate_runtime_test.cpp](../../../../../tests/unit/sql_aggregate_runtime_test.cpp), [docs/sql_aggregate_runtime.md](../../../../sql_aggregate_runtime.md), [tests/support/index_allocation.hpp](../../../../../tests/support/index_allocation.hpp), [docs/sql_rows_batches.md](../../../../sql_rows_batches.md), [include/crown/runtime/sql_aggregate.hpp](../../../../../include/crown/runtime/sql_aggregate.hpp), [include/crown/runtime/sql_rows.hpp](../../../../../include/crown/runtime/sql_rows.hpp), [docs/sql_aggregate_binding.md](../../../../sql_aggregate_binding.md) |

## B0031

[Lines 376–425](../../../../../tests/unit/sql_aggregate_runtime_test.cpp#L376); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void receiving_freeze_and_work(bool indexed, bool integer)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Check receiver-funded compiler freeze, stable short/long literals, exact account and one-under group/source/native work. |
| inputs / outputs | For raw and checked integer programs, foreign genuine freeze into one receiver retains identity/work and expected guard count. Controls cover shared freeze, literal rebasing, exact/one-under group work, source/native refusal and a tiny receiver. |
| invariants | Only genuine immutable metadata is frozen. Guard positions survive dropping foreign handles. Group/source/native/account limits are distinct; every failed preparation leaves the owner ready at its prior source/group sequence. |
| ownership | Receiver owns frozen metadata/runtime. Input row borrows through prepare; foreign compiler owner is dropped before runtime use; snapshots/results remain explicit. |
| failure | Group Error, storage::IndexFailure(storage_work_limit), resource_limit and MemoryFailure(limit) are checked in their own phases; no catch conflates them. |
| cost | Cold foreign copy plus small exact/one-under controls on both backends; work counters do not claim CPU or charge external test code. |
| Design | src/frontend/sql_rows.cpp:514, include/crown/resource/memory.hpp:16, [tests/unit/sql_aggregate_runtime_test.cpp](../../../../../tests/unit/sql_aggregate_runtime_test.cpp), [docs/sql_aggregate_runtime.md](../../../../sql_aggregate_runtime.md), [tests/support/index_allocation.hpp](../../../../../tests/support/index_allocation.hpp), [docs/sql_rows_batches.md](../../../../sql_rows_batches.md), [include/crown/runtime/sql_aggregate.hpp](../../../../../include/crown/runtime/sql_aggregate.hpp), [include/crown/runtime/sql_rows.hpp](../../../../../include/crown/runtime/sql_rows.hpp), [docs/sql_aggregate_binding.md](../../../../sql_aggregate_binding.md) |

## B0032

[Lines 426–427](../../../../../tests/unit/sql_aggregate_runtime_test.cpp#L426); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
} // namespace
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Close the fixture’s anonymous namespace after helper and scenario definitions. |
| inputs / outputs | C++ scope close only; no values enter or leave. |
| invariants | No runtime logic, owner or new state is introduced. |
| ownership | No ownership effect. |
| failure | Compile-time brace/scope validation only. |
| cost | Zero runtime work. |
| Design | [tests/unit/sql_aggregate_runtime_test.cpp](../../../../../tests/unit/sql_aggregate_runtime_test.cpp), [docs/sql_aggregate_runtime.md](../../../../sql_aggregate_runtime.md), [tests/support/index_allocation.hpp](../../../../../tests/support/index_allocation.hpp), [docs/sql_rows_batches.md](../../../../sql_rows_batches.md), [include/crown/runtime/sql_aggregate.hpp](../../../../../include/crown/runtime/sql_aggregate.hpp), [include/crown/runtime/sql_rows.hpp](../../../../../include/crown/runtime/sql_rows.hpp), [docs/sql_aggregate_binding.md](../../../../sql_aggregate_binding.md) |

## B0033

[Lines 428–437](../../../../../tests/unit/sql_aggregate_runtime_test.cpp#L428); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
int main()
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Run the six real SQL aggregate runtime fixtures for ordered and indexed physical storage. |
| inputs / outputs | No caller input; invokes joined, identity, global/rounding, arithmetic/constraints, allocation/lifetime, and freeze/work cases once per backend then reports success. |
| invariants | Assertion-enabled target means any semantic/fault/lifetime mismatch prevents success; local cases use genuine source and aggregate factories. |
| ownership | Function-local tests release their runtimes/accounts/outputs before the process reports pass. |
| failure | First assertion or uncaught Error/bad_alloc/storage failure exits nonzero; no recovery harness hides it. |
| cost | Twelve fixture/backend executions plus finite allocation sweeps and explicit snapshots; not a benchmark. |
| Design | tests/unit/sql_rows_runtime_test.cpp:14, [tests/unit/sql_aggregate_runtime_test.cpp](../../../../../tests/unit/sql_aggregate_runtime_test.cpp), [docs/sql_aggregate_runtime.md](../../../../sql_aggregate_runtime.md), [tests/support/index_allocation.hpp](../../../../../tests/support/index_allocation.hpp), [docs/sql_rows_batches.md](../../../../sql_rows_batches.md), [include/crown/runtime/sql_aggregate.hpp](../../../../../include/crown/runtime/sql_aggregate.hpp), [include/crown/runtime/sql_rows.hpp](../../../../../include/crown/runtime/sql_rows.hpp), [docs/sql_aggregate_binding.md](../../../../sql_aggregate_binding.md) |
