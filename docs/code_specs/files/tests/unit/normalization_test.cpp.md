# `tests/unit/normalization_test.cpp` — block usage map

[Source](../../../../../tests/unit/normalization_test.cpp) · [Source index](../../../README.md) · [Subsystem contracts](../../../subsystem_contracts.md) · [Reviewed primitives](../../../primitives.md)

Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection.

Snapshot SHA-256: `e9011bf0bd89cdfa9a2301ac4b5be2fa41e420051eabd4abf376aa241b237552`. 271 lines partitioned into 27 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [tests](../../../subsystem_contracts.md#tests). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/code_review.md](../../../../code_review.md), [docs/reference_fuzz.md](../../../../reference_fuzz.md), [docs/task_ledger.md](../../../../task_ledger.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–13](../../../../../tests/unit/normalization_test.cpp#L1) | Imports dependencies; declares namespace scope; declares aliases. |  · [reviewed contract](#b0001) |
| [B0002 · 14–14](../../../../../tests/unit/normalization_test.cpp#L14) | Callable definition: Value n(std::int64_t value) | calls ; returns value · [reviewed contract](#b0002) |
| [B0003 · 15–15](../../../../../tests/unit/normalization_test.cpp#L15) | Callable definition: Value s(std::string value) | calls ; returns value · [reviewed contract](#b0003) |
| [B0004 · 16–16](../../../../../tests/unit/normalization_test.cpp#L16) | Callable definition: void check(bool condition, const std::string& message) | calls std::runtime_error; guard void check(bool condition, const std::string& message) { if (!condition) throw std::runtime_error(m… · [reviewed contract](#b0004) |
| [B0005 · 17–23](../../../../../tests/unit/normalization_test.cpp#L17) | Callable definition: Catalog schema() | calls ; returns {9,{{@ ,{{@ ,ScalarType::int64},{@ ,ScalarType::int64},{@ ,ScalarType::string}}}, · [reviewed contract](#b0005) |
| [B0006 · 24–28](../../../../../tests/unit/normalization_test.cpp#L24) | Callable definition: SqlNormalizeResult normalize(std::string_view sql, const Catalog& catalog, const NormalizeOptions& options = {}, const BindOption… | calls bind_sql, normalize_sql; returns *failure; normalize_sql(std::get&lt;BoundSql&gt;(binding),options) · [reviewed contract](#b0006) |
| [B0007 · 29–33](../../../../../tests/unit/normalization_test.cpp#L29) | Callable definition: NormalizedSql accepted(std::string_view sql, const Catalog& catalog, const NormalizeOptions& options = {}, const BindOptions& bin… | calls normalize, std::runtime_error, std::move; returns std::get&lt;NormalizedSql&gt;(std::move(result)) · [reviewed contract](#b0007) |
| [B0008 · 34–40](../../../../../tests/unit/normalization_test.cpp#L34) | Callable definition: BindingDiagnostic rejected(std::string_view sql, const Catalog& catalog, std::string_view code, const NormalizeOptions& options =… | calls normalize, check, std::string; guard check(std::holds_alternative&lt;BindingDiagnostic&gt;(result),"expected rejection: " + std::string(code));; returns failure · [reviewed contract](#b0008) |
| [B0009 · 41–44](../../../../../tests/unit/normalization_test.cpp#L41) | Callable definition: void error(const std::function&lt;void()&gt;& work, std::string_view code) | calls void, work, check, code; guard try { work(); } catch (const Error& failure) { check(failure.code() == code,"unexpected exception c… · [reviewed contract](#b0009) |
| [B0010 · 45–48](../../../../../tests/unit/normalization_test.cpp#L45) | Callable definition: Relation snapshot(const AdapterState& state) | calls query, map_sql_result, reference::evaluate, logical; returns map_sql_result(query,reference::evaluate(query.core_catalog,query.core,state.logical())) · [reviewed contract](#b0010) |
| [B0011 · 49–49](../../../../../tests/unit/normalization_test.cpp#L49) | Callable definition: Database empty(const Catalog& catalog) | calls size; returns {std::vector&lt;Relation&gt;(catalog.tables.size())} · [reviewed contract](#b0011) |
| [B0012 · 50–50](../../../../../tests/unit/normalization_test.cpp#L50) | Explanatory comments or spacing. |  |
| [B0013 · 51–78](../../../../../tests/unit/normalization_test.cpp#L51) | Callable definition: void independent_cq_equivalence() | calls schema, empty, n, s; guard check(snapshot(state) == reference::evaluate(catalog,manual,data),"SQL matches independently handwr…; growth insert · [reviewed contract](#b0013) |
| [B0014 · 79–79](../../../../../tests/unit/normalization_test.cpp#L79) | Explanatory comments or spacing. |  |
| [B0015 · 80–102](../../../../../tests/unit/normalization_test.cpp#L80) | Callable definition: void support_counted_projection() | calls schema, empty, n, s; guard check(state.supports()\[0\].at(Row{n(1)}) == 2 && snapshot(state) == Relation{{n(1)}},"physical rows …; growth insert · [reviewed contract](#b0015) |
| [B0016 · 103–103](../../../../../tests/unit/normalization_test.cpp#L103) | Explanatory comments or spacing. |  |
| [B0017 · 104–146](../../../../../tests/unit/normalization_test.cpp#L104) | Callable definition: void self_join_and_atomic_failure() | calls schema, empty, s, state; guard check(epoch.occurrences.size() == 2 && epoch.occurrences\[0\].occurrence.value == 0 && epoch.occurren…; growth insert, push_back; 2 loop sites · [reviewed contract](#b0017) |
| [B0018 · 147–147](../../../../../tests/unit/normalization_test.cpp#L147) | Explanatory comments or spacing. |  |
| [B0019 · 148–177](../../../../../tests/unit/normalization_test.cpp#L148) | Callable definition: void predicates_constants_and_nulls() | calls schema, empty, n, s; guard check(snapshot(state) == Relation{{n(1),n(2)},{n(2),n(2)}},"OR-local equality is a predicate, not a… · [reviewed contract](#b0019) |
| [B0020 · 178–178](../../../../../tests/unit/normalization_test.cpp#L178) | Explanatory comments or spacing. |  |
| [B0021 · 179–199](../../../../../tests/unit/normalization_test.cpp#L179) | Callable definition: void seeded_self_join_updates() | calls schema, s, accepted, state; guard check(epoch.input_changed == expected.input_changed && snapshot(state) == expected.current,; returns random &gt;&gt; 32U; growth insert; 2 loop sites · [reviewed contract](#b0021) |
| [B0022 · 200–200](../../../../../tests/unit/normalization_test.cpp#L200) | Explanatory comments or spacing. |  |
| [B0023 · 201–231](../../../../../tests/unit/normalization_test.cpp#L201) | Callable definition: void parameters_types_and_output_maps() | calls schema, empty, n, s; guard check(snapshot(state) == Relation{{n(1),n(1),n(1),s("fixed")}},"parameter specialization, repeated … · [reviewed contract](#b0023) |
| [B0024 · 232–232](../../../../../tests/unit/normalization_test.cpp#L232) | Explanatory comments or spacing. |  |
| [B0025 · 233–262](../../../../../tests/unit/normalization_test.cpp#L233) | Callable definition: void nullary_wide_ownership_and_limits() | calls schema, empty, n, s; guard check(snapshot(zero) == Relation{Row{}},"zero-arity source is one nullary tuple");; growth insert, push_back; 1 loop sites · [reviewed contract](#b0025) |
| [B0026 · 263–264](../../../../../tests/unit/normalization_test.cpp#L263) | Closes surrounding scope/type. | source comment (unverified): // namespace · [reviewed contract](#b0026) |
| [B0027 · 265–271](../../../../../tests/unit/normalization_test.cpp#L265) | Callable definition: int main() | calls independent_cq_equivalence, support_counted_projection, self_join_and_atomic_failure, predicates_constants_and_nulls; returns 1 · [reviewed contract](#b0027) |

## B0001

[Lines 1–13](../../../../../tests/unit/normalization_test.cpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L1-L13:sha256:c8105f651efb3cf7728d0333237ba23753b21fb7a5e954dfb1319ad9b41edbfd
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Prepare normalization_test.cpp: include "crown/frontend/adapter.hpp", "crown/api/error.hpp", "crown/io/normalization.hpp", "evaluator.hpp", &lt;functional&gt;, &lt;iostream&gt;, &lt;stdexcept&gt;, &lt;string_view&gt;; bind local aliases/name imports. |
| inputs / outputs | Compiler-visible dependencies, names and the recorded declarations in; declarations available to the following fixture/CLI/example definitions out. |
| invariants | Declarations are scoped to this source/header and its selected ABI. Included code has its own effects; names and editable fixture values do not confer proof, admission or publication authority. |
| ownership | Aliases/includes do not create a query owner. Pointers/references/views are non-owning. Containers own their elements, which can themselves be borrowed pointers or numeric IDs. Only documented owning shared-control handles retain controls; IDs/slot-handle values do not independently keep an arena/runtime alive. |
| failure | Missing headers, ill-formed names/types, failed static assertions or active #error directives stop compilation. No runtime rejection/rollback mechanism is implemented by aliases or function prototypes. |
| cost | Preprocessing and type/constraint instantiation cost compilation. Alias/prototype syntax does not invoke the declared operation; any included definitions keep their own initialization effects. |
| Design | [tests/unit/normalization_test.cpp](../../../../../tests/unit/normalization_test.cpp), [docs/sql_normalization.md](../../../../sql_normalization.md), [docs/code_review.md](../../../../code_review.md) |

## B0002

[Lines 14–14](../../../../../tests/unit/normalization_test.cpp#L14); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Value n(std::int64_t value) { return value; }
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Converts an int64 test literal to the exact core Value alternative. |
| inputs / outputs | int64 value in; Value out. |
| invariants | No conversion to a different numeric width is performed. |
| ownership | Value returned by value. |
| failure | No test error handling. |
| cost | Scalar construction only. |
| Design | [include/crown/frontend/bind.hpp](../../../../../include/crown/frontend/bind.hpp), [include/crown/frontend/normalize.hpp](../../../../../include/crown/frontend/normalize.hpp), [include/crown/frontend/adapter.hpp](../../../../../include/crown/frontend/adapter.hpp), [src/frontend/normalize.cpp](../../../../../src/frontend/normalize.cpp), [src/frontend/adapter.cpp](../../../../../src/frontend/adapter.cpp), [tests/reference/evaluator.hpp](../../../../../tests/reference/evaluator.hpp), [tests/reference/evaluator.cpp](../../../../../tests/reference/evaluator.cpp), [docs/sql_binding.md](../../../../sql_binding.md), [docs/sql_normalization.md](../../../../sql_normalization.md) |

## B0003

[Lines 15–15](../../../../../tests/unit/normalization_test.cpp#L15); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Value s(std::string value) { return value; }
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Converts an owned string to the exact core Value alternative. |
| inputs / outputs | std::string in by value; Value out. |
| invariants | Preserves string bytes in the Value representation. |
| ownership | Receives an owned by-value std::string parameter and implicitly moves that move-eligible parameter into the string alternative of the returned Value under C++23. |
| failure | Forming the by-value string argument may allocate before entry. The body performs the eligible return conversion without an explicit check or catch. |
| cost | Argument construction/copying depends on caller input. The eligible return moves the string into Value rather than deep-copying its character payload; this helper performs no binding or query work. |
| Design | [include/crown/frontend/bind.hpp](../../../../../include/crown/frontend/bind.hpp), [include/crown/frontend/normalize.hpp](../../../../../include/crown/frontend/normalize.hpp), [include/crown/frontend/adapter.hpp](../../../../../include/crown/frontend/adapter.hpp), [src/frontend/normalize.cpp](../../../../../src/frontend/normalize.cpp), [src/frontend/adapter.cpp](../../../../../src/frontend/adapter.cpp), [tests/reference/evaluator.hpp](../../../../../tests/reference/evaluator.hpp), [tests/reference/evaluator.cpp](../../../../../tests/reference/evaluator.cpp), [docs/sql_binding.md](../../../../sql_binding.md), [docs/sql_normalization.md](../../../../sql_normalization.md), [CMakeLists.txt](../../../../../CMakeLists.txt), [include/crown/ir/model.hpp](../../../../../include/crown/ir/model.hpp), [exact paper reference](https://open-std.org/JTC1/SC22/WG21/docs/papers/2022/p2266r3.html) |

## B0004

[Lines 16–16](../../../../../tests/unit/normalization_test.cpp#L16); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void check(bool condition, const std::string& message) { if (!condition) throw std::runtime_error(message); }
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Raises runtime_error when a test predicate is false. |
| inputs / outputs | bool and const std::string& message in. |
| invariants | Calls only the check selected by each test; message expression at the call site is evaluated eagerly, including on true conditions. |
| ownership | Borrows message during call; does not retain it. |
| failure | False condition throws runtime_error; main catches std::exception. |
| cost | True path is a branch; caller may already have allocated the message string. |
| Design | [include/crown/frontend/bind.hpp](../../../../../include/crown/frontend/bind.hpp), [include/crown/frontend/normalize.hpp](../../../../../include/crown/frontend/normalize.hpp), [include/crown/frontend/adapter.hpp](../../../../../include/crown/frontend/adapter.hpp), [src/frontend/normalize.cpp](../../../../../src/frontend/normalize.cpp), [src/frontend/adapter.cpp](../../../../../src/frontend/adapter.cpp), [tests/reference/evaluator.hpp](../../../../../tests/reference/evaluator.hpp), [tests/reference/evaluator.cpp](../../../../../tests/reference/evaluator.cpp), [docs/sql_binding.md](../../../../sql_binding.md), [docs/sql_normalization.md](../../../../sql_normalization.md) |

## B0005

[Lines 17–23](../../../../../tests/unit/normalization_test.cpp#L17); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Catalog schema() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Creates the fixed catalog used by the normalization behavior groups. |
| inputs / outputs | No inputs; returns Catalog version 9 with r, s, nullary zero, Boolean flags, and exact decimal/date money columns. |
| invariants | The nullable metadata and decimal specs are explicit for money; other columns use declared defaults. |
| ownership | Returns owning catalog/table/column strings and vectors. |
| failure | No local validation; bind/normalize paths validate as exercised. |
| cost | Fixed five-table schema construction; ordinary vector/string allocations. |
| Design | [include/crown/frontend/bind.hpp](../../../../../include/crown/frontend/bind.hpp), [include/crown/frontend/normalize.hpp](../../../../../include/crown/frontend/normalize.hpp), [include/crown/frontend/adapter.hpp](../../../../../include/crown/frontend/adapter.hpp), [src/frontend/normalize.cpp](../../../../../src/frontend/normalize.cpp), [src/frontend/adapter.cpp](../../../../../src/frontend/adapter.cpp), [tests/reference/evaluator.hpp](../../../../../tests/reference/evaluator.hpp), [tests/reference/evaluator.cpp](../../../../../tests/reference/evaluator.cpp), [docs/sql_binding.md](../../../../sql_binding.md), [docs/sql_normalization.md](../../../../sql_normalization.md) |

## B0006

[Lines 24–28](../../../../../tests/unit/normalization_test.cpp#L24); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
SqlNormalizeResult normalize(std::string_view sql, const Catalog& catalog, const NormalizeOptions& options = {}, const BindOptions& bind_options = {}) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Runs SQL binding then normalization while preserving either phase diagnostic. |
| inputs / outputs | SQL view, Catalog, NormalizeOptions and BindOptions in; SqlNormalizeResult out. |
| invariants | If bind_sql returns BindingDiagnostic it is returned directly; only BoundSql proceeds to normalize_sql. |
| ownership | Borrows SQL/catalog/options for call; returned normalized program or diagnostic owns its value. |
| failure | Returns diagnostics from binder or normalizer; parser/API exceptions outside those result boundaries may propagate. |
| cost | Includes binding and normalization work; caller-selected limits are separate and no wall-time bound is asserted. |
| Design | [include/crown/frontend/bind.hpp](../../../../../include/crown/frontend/bind.hpp), [include/crown/frontend/normalize.hpp](../../../../../include/crown/frontend/normalize.hpp), [include/crown/frontend/adapter.hpp](../../../../../include/crown/frontend/adapter.hpp), [src/frontend/normalize.cpp](../../../../../src/frontend/normalize.cpp), [src/frontend/adapter.cpp](../../../../../src/frontend/adapter.cpp), [tests/reference/evaluator.hpp](../../../../../tests/reference/evaluator.hpp), [tests/reference/evaluator.cpp](../../../../../tests/reference/evaluator.cpp), [docs/sql_binding.md](../../../../sql_binding.md), [docs/sql_normalization.md](../../../../sql_normalization.md) |

## B0007

[Lines 29–33](../../../../../tests/unit/normalization_test.cpp#L29); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
NormalizedSql accepted(std::string_view sql, const Catalog& catalog, const NormalizeOptions& options = {}, const BindOptions& bind_options = {}) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Requires an accepted normalized program and turns a returned diagnostic into a test exception. |
| inputs / outputs | SQL/catalog/options in; NormalizedSql by value out. |
| invariants | Moves the NormalizedSql alternative from result; diagnostic code/message is concatenated into runtime_error. |
| ownership | Returned program owns binding, core, adapters and specialization; input catalog/string need not outlive it. |
| failure | Any BindingDiagnostic becomes runtime_error; exceptions from normalize itself also propagate. |
| cost | Builds complete normalized program and may allocate diagnostic text or owned program state. |
| Design | [include/crown/frontend/bind.hpp](../../../../../include/crown/frontend/bind.hpp), [include/crown/frontend/normalize.hpp](../../../../../include/crown/frontend/normalize.hpp), [include/crown/frontend/adapter.hpp](../../../../../include/crown/frontend/adapter.hpp), [src/frontend/normalize.cpp](../../../../../src/frontend/normalize.cpp), [src/frontend/adapter.cpp](../../../../../src/frontend/adapter.cpp), [tests/reference/evaluator.hpp](../../../../../tests/reference/evaluator.hpp), [tests/reference/evaluator.cpp](../../../../../tests/reference/evaluator.cpp), [docs/sql_binding.md](../../../../sql_binding.md), [docs/sql_normalization.md](../../../../sql_normalization.md) |

## B0008

[Lines 34–40](../../../../../tests/unit/normalization_test.cpp#L34); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
BindingDiagnostic rejected(std::string_view sql, const Catalog& catalog, std::string_view code, const NormalizeOptions& options = {}, const BindOptions& bind_options = {}) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Requires a BindingDiagnostic with the expected code for rejection fixtures. |
| inputs / outputs | SQL/catalog/expected code/options in; returns diagnostic. |
| invariants | Checks the variant before reading it, then checks exact code; it does not assert every diagnostic field. |
| ownership | Returns a copy of diagnostic data; input arguments are borrowed. |
| failure | Missing/wrong diagnostic throws via check; binding exceptions can still propagate. |
| cost | Runs binding plus normalization to rejection; no performance assertion. |
| Design | [include/crown/frontend/bind.hpp](../../../../../include/crown/frontend/bind.hpp), [include/crown/frontend/normalize.hpp](../../../../../include/crown/frontend/normalize.hpp), [include/crown/frontend/adapter.hpp](../../../../../include/crown/frontend/adapter.hpp), [src/frontend/normalize.cpp](../../../../../src/frontend/normalize.cpp), [src/frontend/adapter.cpp](../../../../../src/frontend/adapter.cpp), [tests/reference/evaluator.hpp](../../../../../tests/reference/evaluator.hpp), [tests/reference/evaluator.cpp](../../../../../tests/reference/evaluator.cpp), [docs/sql_binding.md](../../../../sql_binding.md), [docs/sql_normalization.md](../../../../sql_normalization.md) |

## B0009

[Lines 41–44](../../../../../tests/unit/normalization_test.cpp#L41); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void error(const std::function<void()>& work, std::string_view code) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Asserts that a callback throws Error with the expected code. |
| inputs / outputs | std::function&lt;void()&gt; and code view in; no return. |
| invariants | Only crown::Error is accepted; code comparison happens in the catch, and its concatenated message expression is evaluated even on a matching code. |
| ownership | Borrows callable/code; std::function owns its erased callable wrapper for call duration. |
| failure | Wrong Error code triggers check; no Error triggers runtime_error; other exception types propagate. |
| cost | Callback work plus possible catch-diagnostic string allocation; not a general exception benchmark. |
| Design | [include/crown/frontend/bind.hpp](../../../../../include/crown/frontend/bind.hpp), [include/crown/frontend/normalize.hpp](../../../../../include/crown/frontend/normalize.hpp), [include/crown/frontend/adapter.hpp](../../../../../include/crown/frontend/adapter.hpp), [src/frontend/normalize.cpp](../../../../../src/frontend/normalize.cpp), [src/frontend/adapter.cpp](../../../../../src/frontend/adapter.cpp), [tests/reference/evaluator.hpp](../../../../../tests/reference/evaluator.hpp), [tests/reference/evaluator.cpp](../../../../../tests/reference/evaluator.cpp), [docs/sql_binding.md](../../../../sql_binding.md), [docs/sql_normalization.md](../../../../sql_normalization.md), [include/crown/api/error.hpp](../../../../../include/crown/api/error.hpp) |

## B0010

[Lines 45–48](../../../../../tests/unit/normalization_test.cpp#L45); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Relation snapshot(const AdapterState& state) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Computes SQL-visible results by applying the independent materializing CQ evaluator to AdapterState logical tables. |
| inputs / outputs | AdapterState const reference in; Relation out. |
| invariants | Uses normalized core catalog/query and current logical input tables, then applies ordered outputs/EXISTS mapping; it is a reference oracle, not native runtime state. |
| ownership | Borrows state/query during evaluation; returned Relation owns rows. |
| failure | Evaluator/shape failures propagate; no catch here. |
| cost | Materializes reference CQ evaluation and result mapping; may allocate relation rows and maps. |
| Design | [include/crown/frontend/bind.hpp](../../../../../include/crown/frontend/bind.hpp), [include/crown/frontend/normalize.hpp](../../../../../include/crown/frontend/normalize.hpp), [include/crown/frontend/adapter.hpp](../../../../../include/crown/frontend/adapter.hpp), [src/frontend/normalize.cpp](../../../../../src/frontend/normalize.cpp), [src/frontend/adapter.cpp](../../../../../src/frontend/adapter.cpp), [tests/reference/evaluator.hpp](../../../../../tests/reference/evaluator.hpp), [tests/reference/evaluator.cpp](../../../../../tests/reference/evaluator.cpp), [docs/sql_binding.md](../../../../sql_binding.md), [docs/sql_normalization.md](../../../../sql_normalization.md) |

## B0011

[Lines 49–49](../../../../../tests/unit/normalization_test.cpp#L49); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Database empty(const Catalog& catalog) { return {std::vector<Relation>(catalog.tables.size())}; }
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Makes an empty Database with one relation slot per catalog table. |
| inputs / outputs | Catalog const reference in; Database out. |
| invariants | Table vector length equals catalog table count and all relations begin empty. |
| ownership | Returns owning relation vector. |
| failure | No row validation needed; allocation errors propagate. |
| cost | Creates one vector sized to the catalog table count, holding that many empty Relation objects. It reserves no row nodes and does not allocate a separate populated relation payload per table. |
| Design | [include/crown/frontend/bind.hpp](../../../../../include/crown/frontend/bind.hpp), [include/crown/frontend/normalize.hpp](../../../../../include/crown/frontend/normalize.hpp), [include/crown/frontend/adapter.hpp](../../../../../include/crown/frontend/adapter.hpp), [src/frontend/normalize.cpp](../../../../../src/frontend/normalize.cpp), [src/frontend/adapter.cpp](../../../../../src/frontend/adapter.cpp), [tests/reference/evaluator.hpp](../../../../../tests/reference/evaluator.hpp), [tests/reference/evaluator.cpp](../../../../../tests/reference/evaluator.cpp), [docs/sql_binding.md](../../../../sql_binding.md), [docs/sql_normalization.md](../../../../sql_normalization.md) |

## B0013

[Lines 51–78](../../../../../tests/unit/normalization_test.cpp#L51); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void independent_cq_equivalence() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Checks selected DISTINCT SQL normalization cases against an independently handwritten CQ and exercises occurrence routing. |
| inputs / outputs | Fixed schema/data plus SQL strings; constructs NormalizedSql/AdapterState and compares to evaluate/manual query. |
| invariants | Covers repeated variable/constant term, output order/repetition, two same-base aliases, preserved contained occurrence, hidden alias reuse with distinct core occurrence IDs, and one insert making a missing join input visible. Evidence is fixture-scoped. |
| ownership | Local programs/states/manual query/database own their data; reference evaluator is independent. |
| failure | Assertions throw on mismatch; bind/normalize diagnostics become test exceptions through accepted. |
| cost | A few finite rows/occurrences and one adapter update; reference snapshots allocate and are not a throughput claim. |
| Design | [include/crown/frontend/bind.hpp](../../../../../include/crown/frontend/bind.hpp), [include/crown/frontend/normalize.hpp](../../../../../include/crown/frontend/normalize.hpp), [include/crown/frontend/adapter.hpp](../../../../../include/crown/frontend/adapter.hpp), [src/frontend/normalize.cpp](../../../../../src/frontend/normalize.cpp), [src/frontend/adapter.cpp](../../../../../src/frontend/adapter.cpp), [tests/reference/evaluator.hpp](../../../../../tests/reference/evaluator.hpp), [tests/reference/evaluator.cpp](../../../../../tests/reference/evaluator.cpp), [docs/sql_binding.md](../../../../sql_binding.md), [docs/sql_normalization.md](../../../../sql_normalization.md) |

## B0015

[Lines 80–102](../../../../../tests/unit/normalization_test.cpp#L80); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void support_counted_projection() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Checks support multiplicity when distinct physical rows map to one projected logical tuple. |
| inputs / outputs | Fixed r rows and two successive adapters; applies delete/duplicate insert/last delete/absent delete/filtered insert plus EXISTS case. |
| invariants | Only first support creates a logical tuple and last support withdrawal removes it; valid no-op physical events still consume contiguous sequence; zero-column EXISTS support is counted. |
| ownership | AdapterState owns copies of physical/logical/support state; returned epoch owns deltas. |
| failure | Invalid sequence/update errors are exercised elsewhere; support underflow/overflow behavior comes from AdapterState. |
| cost | Reference AdapterState copies whole state for every apply; work is fixture scoped and explicitly not the maintained runtime’s update bound. |
| Design | [include/crown/frontend/bind.hpp](../../../../../include/crown/frontend/bind.hpp), [include/crown/frontend/normalize.hpp](../../../../../include/crown/frontend/normalize.hpp), [include/crown/frontend/adapter.hpp](../../../../../include/crown/frontend/adapter.hpp), [src/frontend/normalize.cpp](../../../../../src/frontend/normalize.cpp), [src/frontend/adapter.cpp](../../../../../src/frontend/adapter.cpp), [tests/reference/evaluator.hpp](../../../../../tests/reference/evaluator.hpp), [tests/reference/evaluator.cpp](../../../../../tests/reference/evaluator.cpp), [docs/sql_binding.md](../../../../sql_binding.md), [docs/sql_normalization.md](../../../../sql_normalization.md) |

## B0017

[Lines 104–146](../../../../../tests/unit/normalization_test.cpp#L104); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void self_join_and_atomic_failure() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Compares two self-join aliases to an independent Session and checks atomic failure across alias fan-out. |
| inputs / outputs | One same-base two-occurrence SQL plan/manual CQ, five updates, then invalid sequence/row, corrupted second-alias expression, and unique-constraint failure. |
| invariants | Checks stable occurrence order, per-epoch result equality, no publication when update invalid or a prepared alias fails, and preserved prior sequence/supports. The corruption is deliberately injected into alias 1. |
| ownership | AdapterState owns staged full copies; Session is a separate handwritten reference; source objects local. |
| failure | Asserts invalid_sequence, invalid_update, normalization_contract, constraint_violation; failures must leave state as specifically checked. |
| cost | Each AdapterState apply copies physical/logical/support state; this test checks atomic behavior, not production update complexity. |
| Design | [include/crown/frontend/bind.hpp](../../../../../include/crown/frontend/bind.hpp), [include/crown/frontend/normalize.hpp](../../../../../include/crown/frontend/normalize.hpp), [include/crown/frontend/adapter.hpp](../../../../../include/crown/frontend/adapter.hpp), [src/frontend/normalize.cpp](../../../../../src/frontend/normalize.cpp), [src/frontend/adapter.cpp](../../../../../src/frontend/adapter.cpp), [tests/reference/evaluator.hpp](../../../../../tests/reference/evaluator.hpp), [tests/reference/evaluator.cpp](../../../../../tests/reference/evaluator.cpp), [docs/sql_binding.md](../../../../sql_binding.md), [docs/sql_normalization.md](../../../../sql_normalization.md) |

## B0019

[Lines 148–177](../../../../../tests/unit/normalization_test.cpp#L148); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void predicates_constants_and_nulls() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Exercises local SQL predicates, unsupported cross-occurrence forms, null semantics and contradiction reduction. |
| inputs / outputs | Finite rows/catalog variants plus SQL queries over equality, OR, NULL, Boolean tests, constants and nullable metadata. |
| invariants | Tests OR-local equality stays a predicate; cross-relation comparisons/output and non-DISTINCT/NULL outputs reject; unused nullable catalog columns are not referenced; conflicting final-class constants contradict; SQL UNKNOWN behavior is checked with examples. |
| ownership | Normalized programs/adapters and local states own outputs; fixture data copied. |
| failure | Expected diagnostic codes are checked by rejected; unsupported examples are finite probes, not exhaustive grammar proof. |
| cost | Small fixed example evaluation and normalization; no broad completeness or runtime-bound claim. |
| Design | [include/crown/frontend/bind.hpp](../../../../../include/crown/frontend/bind.hpp), [include/crown/frontend/normalize.hpp](../../../../../include/crown/frontend/normalize.hpp), [include/crown/frontend/adapter.hpp](../../../../../include/crown/frontend/adapter.hpp), [src/frontend/normalize.cpp](../../../../../src/frontend/normalize.cpp), [src/frontend/adapter.cpp](../../../../../src/frontend/adapter.cpp), [tests/reference/evaluator.hpp](../../../../../tests/reference/evaluator.hpp), [tests/reference/evaluator.cpp](../../../../../tests/reference/evaluator.cpp), [docs/sql_binding.md](../../../../sql_binding.md), [docs/sql_normalization.md](../../../../sql_normalization.md) |

## B0021

[Lines 179–199](../../../../../tests/unit/normalization_test.cpp#L179); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void seeded_self_join_updates() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Runs 576 deterministic self-join set updates against a handwritten CQ reference. |
| inputs / outputs | For seeds 1..12, generates 48 inserts/erases each with fixed LCG and compares changed flag plus SQL-mapped snapshot every step. |
| invariants | Rows draw two int64s modulo 4 and keep/skip labels modulo 3; sequences are contiguous; the expected query is manually authored. |
| ownership | AdapterState and reference Session each own their current state. |
| failure | Any update or answer mismatch throws with seed and sequence; fixed generator does not prove arbitrary input coverage. |
| cost | Exactly 12×48=576 updates plus full reference recomputation/snapshots; not benchmark evidence. |
| Design | [include/crown/frontend/bind.hpp](../../../../../include/crown/frontend/bind.hpp), [include/crown/frontend/normalize.hpp](../../../../../include/crown/frontend/normalize.hpp), [include/crown/frontend/adapter.hpp](../../../../../include/crown/frontend/adapter.hpp), [src/frontend/normalize.cpp](../../../../../src/frontend/normalize.cpp), [src/frontend/adapter.cpp](../../../../../src/frontend/adapter.cpp), [tests/reference/evaluator.hpp](../../../../../tests/reference/evaluator.hpp), [tests/reference/evaluator.cpp](../../../../../tests/reference/evaluator.cpp), [docs/sql_binding.md](../../../../sql_binding.md), [docs/sql_normalization.md](../../../../sql_normalization.md) |

## B0023

[Lines 201–231](../../../../../tests/unit/normalization_test.cpp#L201); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void parameters_types_and_output_maps() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Checks parameter specialization, type/nullability, output mapping and strict parameter codec behavior. |
| inputs / outputs | Fixture queries cover nullable int parameter, repeated/constant outputs, NULL, decimal scales/date, casts, constant-only outputs and parameter JSON documents. |
| invariants | Output order/repeated column and constant are retained; nullability/type mismatches reject; different decimal scales compare exact values; normalization JSON says admission not checked; codec rejects float/extra/version and accepts null plus canonical decimal. |
| ownership | Programs, adapter states and returned JSON/values own their memory. |
| failure | Specific diagnostic/error codes are asserted; this is the stated test subset only. |
| cost | Runs several normalizations/evaluations and JSON serialization/parsing; allocation and parser work are not measured. |
| Design | [include/crown/frontend/bind.hpp](../../../../../include/crown/frontend/bind.hpp), [include/crown/frontend/normalize.hpp](../../../../../include/crown/frontend/normalize.hpp), [include/crown/frontend/adapter.hpp](../../../../../include/crown/frontend/adapter.hpp), [src/frontend/normalize.cpp](../../../../../src/frontend/normalize.cpp), [src/frontend/adapter.cpp](../../../../../src/frontend/adapter.cpp), [tests/reference/evaluator.hpp](../../../../../tests/reference/evaluator.hpp), [tests/reference/evaluator.cpp](../../../../../tests/reference/evaluator.cpp), [docs/sql_binding.md](../../../../sql_binding.md), [docs/sql_normalization.md](../../../../sql_normalization.md), [include/crown/io/normalization.hpp](../../../../../include/crown/io/normalization.hpp), [src/io/normalization.cpp](../../../../../src/io/normalization.cpp), [include/crown/api/error.hpp](../../../../../include/crown/api/error.hpp) |

## B0025

[Lines 233–262](../../../../../tests/unit/normalization_test.cpp#L233); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void nullary_wide_ownership_and_limits() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Covers nullary relations, cross-join offsets, EXISTS, 70-column output, normalized program lifetime and bounded-work diagnostics. |
| inputs / outputs | Fixed zero/nullary and r data, a generated 70-column catalog/row, bound/normalized program copies, zero work limit and Unicode SQL error. |
| invariants | Checks no fixed bitmask cap in this case; clearing original BoundSql/catalog does not invalidate retained NormalizedSql; zero limit returns resource_limit; byte offset differs from code-point position for the Unicode alias. |
| ownership | NormalizedSql owns source/catalog/IR/specialization; AdapterState receives moved copy; \`plan\` remains a separate live value for the ownership assertion. |
| failure | Resource limit is a BindingDiagnostic; type/normalization errors use expected codes; exceptions from accepted paths fail the test. |
| cost | 70 fixed columns and small rows; bind/normalize and reference evaluation allocate; no generic wide-query or CPU/RSS bound. |
| Design | [include/crown/frontend/bind.hpp](../../../../../include/crown/frontend/bind.hpp), [include/crown/frontend/normalize.hpp](../../../../../include/crown/frontend/normalize.hpp), [include/crown/frontend/adapter.hpp](../../../../../include/crown/frontend/adapter.hpp), [src/frontend/normalize.cpp](../../../../../src/frontend/normalize.cpp), [src/frontend/adapter.cpp](../../../../../src/frontend/adapter.cpp), [tests/reference/evaluator.hpp](../../../../../tests/reference/evaluator.hpp), [tests/reference/evaluator.cpp](../../../../../tests/reference/evaluator.cpp), [docs/sql_binding.md](../../../../sql_binding.md), [docs/sql_normalization.md](../../../../sql_normalization.md) |

## B0026

[Lines 263–264](../../../../../tests/unit/normalization_test.cpp#L263); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L263-L264:sha256:c2bd7638f09d52cb034ed574f539304035fc6fab162bf8d5fa20a35d8c7288a1
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Close the recorded declaration scopes in normalization_test.cpp: namespace (anonymous). |
| inputs / outputs | Preceding namespace, type or initializer declarations in; completed lexical boundary out. |
| invariants | Brace-opening context is recorded in root-scope-context-v1.json. These are declaration/initializer boundaries, not an independent update, validation or recovery operation. |
| ownership | Enclosing objects and borrowed fields keep their declared ownership. This punctuation creates no new owner. |
| failure | Malformed scope syntax is a compile error. Any initializer/constructor failure belongs to the enclosing object declaration. |
| cost | No separate loop, guard or engine call is introduced by the delimiter; enclosing initialization and object lifetime still have their actual costs. |
| Design | [tests/unit/normalization_test.cpp](../../../../../tests/unit/normalization_test.cpp), [docs/sql_normalization.md](../../../../sql_normalization.md), [docs/code_review.md](../../../../code_review.md) |

## B0027

[Lines 265–271](../../../../../tests/unit/normalization_test.cpp#L265); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
int main() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Runs the seven normalization test groups and reports failure by process status. |
| inputs / outputs | No args; invokes independent equivalence, support, atomicity, predicate, seeded, parameter/output and nullary/ownership helpers. |
| invariants | All helpers must return normally to print success line and return zero. |
| ownership | Owns only local test group state; each helper releases its fixtures on return. |
| failure | Catches std::exception, prints message to stderr and returns 1; no special catch for non-standard exceptions. |
| cost | Combines all finite fixtures including 576 updates; the success message is source text, not evidence that this task executed it. |
| Design | [include/crown/frontend/bind.hpp](../../../../../include/crown/frontend/bind.hpp), [include/crown/frontend/normalize.hpp](../../../../../include/crown/frontend/normalize.hpp), [include/crown/frontend/adapter.hpp](../../../../../include/crown/frontend/adapter.hpp), [src/frontend/normalize.cpp](../../../../../src/frontend/normalize.cpp), [src/frontend/adapter.cpp](../../../../../src/frontend/adapter.cpp), [tests/reference/evaluator.hpp](../../../../../tests/reference/evaluator.hpp), [tests/reference/evaluator.cpp](../../../../../tests/reference/evaluator.cpp), [docs/sql_binding.md](../../../../sql_binding.md), [docs/sql_normalization.md](../../../../sql_normalization.md), [CMakeLists.txt](../../../../../CMakeLists.txt) |
