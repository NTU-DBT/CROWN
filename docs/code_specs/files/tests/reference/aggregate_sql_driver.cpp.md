# `tests/reference/aggregate_sql_driver.cpp` — block usage map

[Source](../../../../../tests/reference/aggregate_sql_driver.cpp) · [Source index](../../../README.md) · [Subsystem contracts](../../../subsystem_contracts.md) · [Reviewed primitives](../../../primitives.md)

Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection.

Snapshot SHA-256: `f8514e8412c03a6186d19de28e199027d61939db8d39620a745d34d11eb2b631`. 97 lines partitioned into 10 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [tests](../../../subsystem_contracts.md#tests). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/code_review.md](../../../../code_review.md), [docs/reference_fuzz.md](../../../../reference_fuzz.md), [docs/task_ledger.md](../../../../task_ledger.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–11](../../../../../tests/reference/aggregate_sql_driver.cpp#L1) | Imports dependencies; declares namespace scope; declares aliases; declares values/defaults or compile-time conditions. |  · [reviewed contract](#b0001) |
| [B0002 · 12–17](../../../../../tests/reference/aggregate_sql_driver.cpp#L12) | Callable definition: crown::Catalog schema() | calls ; returns result · [reviewed contract](#b0002) |
| [B0003 · 18–19](../../../../../tests/reference/aggregate_sql_driver.cpp#L18) | Explanatory comments or spacing. | source comment (unverified): // Observe public SQL cells only; decimal type identity remains explicit. · [reviewed contract](#b0003) |
| [B0004 · 20–30](../../../../../tests/reference/aggregate_sql_driver.cpp#L20) | Callable definition: Json scalar(const crown::storage::ScalarView& value) | calls std::string, render, data, std::runtime_error; returns *integer; std::string(*text); source comment (unverified): // Observe public SQL cells only; decimal type identity remains explicit. · [reviewed contract](#b0004) |
| [B0005 · 31–35](../../../../../tests/reference/aggregate_sql_driver.cpp#L31) | Callable definition: Json tuple(const ag::Tuple& value) | calls Json::array, view, push_back, scalar; returns result; growth push_back; 1 loop sites · [reviewed contract](#b0005) |
| [B0006 · 36–42](../../../../../tests/reference/aggregate_sql_driver.cpp#L36) | Callable definition: Json snapshot(const crown::runtime::AggregateRuntime& runtime) | calls Json::array, push_back, tuple, std::move; returns {{@ , source.sequence}, {@ , std::move(groups)}}; growth push_back; 1 loop sites · [reviewed contract](#b0006) |
| [B0007 · 43–53](../../../../../tests/reference/aggregate_sql_driver.cpp#L43) | Callable definition: ag::Row row(const Json& values) | calls is_null, emplace_back, is_boolean, is_number_integer; returns result; growth emplace_back; 1 loop sites · [reviewed contract](#b0007) |
| [B0008 · 54–85](../../../../../tests/reference/aggregate_sql_driver.cpp#L54) | Callable definition: Json evaluate(const Json& request) | calls value, crown::frontend::bind_aggregate_sql, at, schema; returns {{@ , request.at(@ )}, {@ , std::move(trace)}, {@ , std::move(epochs)}}; growth push_back; 1 loop sites; source comment (unverified): // This explicit test diagnostic is outside the measured update operation. · [reviewed contract](#b0008) |
| [B0009 · 86–87](../../../../../tests/reference/aggregate_sql_driver.cpp#L86) | Closes surrounding scope/type. | source comment (unverified): // namespace · [reviewed contract](#b0009) |
| [B0010 · 88–97](../../../../../tests/reference/aggregate_sql_driver.cpp#L88) | Callable definition: int main() | calls std::getline, evaluate, Json::parse, dump; returns 0; 1; 1 loop sites · [reviewed contract](#b0010) |

## B0001

[Lines 1–11](../../../../../tests/reference/aggregate_sql_driver.cpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
namespace ag = crown::runtime::aggregate;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Name the public runtime and JSON interfaces used by this isolated test executable. |
| inputs / outputs | Public aggregate header and standard/JSON headers supply DTO and I/O declarations. |
| invariants | The test does not inspect private sufficient-statistic limbs or install allocator hooks. |
| ownership | Aliases create no runtime owner; includes provide declarations. |
| failure | No executable admission or failure handling occurs in these declarations. |
| cost | No per-update work or retained test state is introduced by these aliases. |
| Design | [docs/aggregates.md](../../../../aggregates.md), [Refactor.md § W04 — Implement COUNT, SUM and AVG](../../../../../Refactor.md) |

## B0002

[Lines 12–17](../../../../../tests/reference/aggregate_sql_driver.cpp#L12); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
crown::Catalog schema()
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Construct the fixed one-relation schema that both independent oracles assume. |
| inputs / outputs | No arguments; Catalog r(g nullable text,x nullable int64,flag non-null boolean) returned. |
| invariants | Column positions are g=0,x=1,flag=2 and match the request row encoding. |
| ownership | Returned Catalog owns all table and column names; the binder must retain what it needs. |
| failure | Catalog/standard allocation failure propagates to main. |
| cost | Fixed three-column catalog construction with caller-owned string/vector allocations. |
| Design | [docs/aggregates.md](../../../../aggregates.md), [Refactor.md § W04 — Implement COUNT, SUM and AVG](../../../../../Refactor.md) |

## B0003

[Lines 18–19](../../../../../tests/reference/aggregate_sql_driver.cpp#L18); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
// Observe public SQL cells only; decimal type identity remains explicit.
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Document the observation boundary before the scalar serializer. |
| inputs / outputs | The following serializer receives public ScalarView values and distinguishes decimals. |
| invariants | This comment grants no private arithmetic or resource verification. |
| ownership | The comment owns no values. |
| failure | No executable branch. |
| cost | No runtime work. |
| Design | [docs/aggregates.md](../../../../aggregates.md), [Refactor.md § W04 — Implement COUNT, SUM and AVG](../../../../../Refactor.md) |

## B0004

[Lines 20–30](../../../../../tests/reference/aggregate_sql_driver.cpp#L20); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Json scalar(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Serialize a public SQL scalar without converting exact decimals through floating point. |
| inputs / outputs | Supported ScalarView in; JSON integer/string/bool or a decimal-text object out. |
| invariants | InlineDecimal render output is canonical and tagged; unexpected scalar kinds fail the fixture. |
| ownership | Returned JSON owns copied strings; the render buffer remains on the stack. |
| failure | Unexpected kinds throw runtime_error; JSON/string allocation failures propagate. |
| cost | Constant alternative dispatch plus copied string length or bounded InlineDecimal rendering; JSON output may allocate. |
| Design | [docs/aggregates.md](../../../../aggregates.md), [Refactor.md § W04 — Implement COUNT, SUM and AVG](../../../../../Refactor.md) |

## B0005

[Lines 31–35](../../../../../tests/reference/aggregate_sql_driver.cpp#L31); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Json tuple(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Observe one immutable nullable tuple in ordered cell order. |
| inputs / outputs | Valid Tuple handle in; JSON array with nulls preserved out. |
| invariants | NULL cells remain distinct from an absent group in an event envelope. |
| ownership | The function borrows the tuple for the loop; returned JSON owns exports. |
| failure | Invalid handle or scalar/export allocation failures propagate. |
| cost | Linear in tuple width and copied text bytes; output JSON may reallocate. |
| Design | [docs/aggregates.md](../../../../aggregates.md), [Refactor.md § W04 — Implement COUNT, SUM and AVG](../../../../../Refactor.md) |

## B0006

[Lines 36–42](../../../../../tests/reference/aggregate_sql_driver.cpp#L36); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Json snapshot(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Export every current group with its full identity for independent comparison. |
| inputs / outputs | Live runtime in; JSON sequence and key/value arrays out. |
| invariants | Hidden GROUP BY identities are retained even when projected values coincide. |
| ownership | A temporary funded Snapshot keeps tuple/program owners alive during JSON export; JSON owns the final values. |
| failure | Snapshot limits/account allocation or JSON allocation errors propagate. |
| cost | Full snapshot enumeration and decimal/output copying; not a constant-time update probe. |
| Design | [docs/aggregates.md](../../../../aggregates.md), [Refactor.md § W04 — Implement COUNT, SUM and AVG](../../../../../Refactor.md) |

## B0007

[Lines 43–53](../../../../../tests/reference/aggregate_sql_driver.cpp#L43); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
ag::Row row(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Decode trusted generated nullable input rows into the public owning DTO. |
| inputs / outputs | JSON array in; ordered Row of optional Value int64/text/bool cells out. |
| invariants | Generated integers fit signed int64; booleans are tested before integer decoding. |
| ownership | Row and string cells are caller-owned test allocations, borrowed by synchronous apply. |
| failure | Unsupported JSON cell kinds and decode/allocation errors propagate. |
| cost | Linear in input width and copied string bytes; no repeated-row expansion. |
| Design | [docs/aggregates.md](../../../../aggregates.md), [Refactor.md § W04 — Implement COUNT, SUM and AVG](../../../../../Refactor.md) |

## B0008

[Lines 54–85](../../../../../tests/reference/aggregate_sql_driver.cpp#L54); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Json evaluate(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Run one SQL history through the public aggregate runtime and expose snapshots/events. |
| inputs / outputs | Trusted request with SQL, scale and exact weight replacements in; id, trace and epoch JSON out. |
| invariants | Sequence increments once per request operation, capture is enabled, and explicit invariant checks are outside apply. |
| ownership | Compiled program/runtime own their accounts; row DTOs and JSON are ordinary test-owned memory. |
| failure | Binding diagnostics become test errors; arithmetic/resource/invariant/JSON failures propagate to main. |
| cost | Compile once, apply each replacement, run full diagnostic and snapshot per epoch; returned trace retains all observations. |
| Design | [docs/aggregates.md](../../../../aggregates.md), [Refactor.md § W04 — Implement COUNT, SUM and AVG](../../../../../Refactor.md) |

## B0009

[Lines 86–87](../../../../../tests/reference/aggregate_sql_driver.cpp#L86); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L86-L87:sha256:c2bd7638f09d52cb034ed574f539304035fc6fab162bf8d5fa20a35d8c7288a1
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Close the recorded declaration scopes in aggregate_sql_driver.cpp: namespace (anonymous). |
| inputs / outputs | Preceding namespace, type or initializer declarations in; completed lexical boundary out. |
| invariants | Brace-opening context is recorded in root-scope-context-v1.json. These are declaration/initializer boundaries, not an independent update, validation or recovery operation. |
| ownership | Enclosing objects and borrowed fields keep their declared ownership. This punctuation creates no new owner. |
| failure | Malformed scope syntax is a compile error. Any initializer/constructor failure belongs to the enclosing object declaration. |
| cost | No separate loop, guard or engine call is introduced by the delimiter; enclosing initialization and object lifetime still have their actual costs. |
| Design | [tests/reference/aggregate_sql_driver.cpp](../../../../../tests/reference/aggregate_sql_driver.cpp), [docs/aggregates.md](../../../../aggregates.md), [docs/code_review.md](../../../../code_review.md) |

## B0010

[Lines 88–97](../../../../../tests/reference/aggregate_sql_driver.cpp#L88); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
int main()
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Provide one newline-delimited request/response process for the Python oracle. |
| inputs / outputs | stdin JSON lines in; one JSON response line per request, status 0 on success. |
| invariants | First failed request stops the process with diagnostic stderr and nonzero status. |
| ownership | Each parsed request and evaluated response are scoped to one loop iteration. |
| failure | One outer standard exception handler reports test failure; no recovery loop or production exception policy. |
| cost | Linear input/output work plus evaluate costs, with ordinary stream/JSON allocations. |
| Design | [docs/aggregates.md](../../../../aggregates.md), [Refactor.md § W04 — Implement COUNT, SUM and AVG](../../../../../Refactor.md) |
