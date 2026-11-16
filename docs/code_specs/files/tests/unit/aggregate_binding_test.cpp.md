# `tests/unit/aggregate_binding_test.cpp` — block usage map

[Source](../../../../../tests/unit/aggregate_binding_test.cpp) · [Source index](../../../README.md) · [Subsystem contracts](../../../subsystem_contracts.md) · [Reviewed primitives](../../../primitives.md)

Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection.

Snapshot SHA-256: `1b10db2725c9f66b422da61edd6b9957a31ec6d4cefe21049c1eb09a8437b869`. 229 lines partitioned into 17 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [tests](../../../subsystem_contracts.md#tests). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/code_review.md](../../../../code_review.md), [docs/reference_fuzz.md](../../../../reference_fuzz.md), [docs/task_ledger.md](../../../../task_ledger.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–13](../../../../../tests/unit/aggregate_binding_test.cpp#L1) | Imports dependencies; declares namespace scope; declares aliases; declares values/defaults or compile-time conditions. |  · [reviewed contract](#b0001) |
| [B0002 · 14–14](../../../../../tests/unit/aggregate_binding_test.cpp#L14) | Callable definition: void check(bool value, const char* message) | calls std::runtime_error; guard void check(bool value, const char* message) { if (!value) throw std::runtime_error(message); } · [reviewed contract](#b0002) |
| [B0003 · 15–20](../../../../../tests/unit/aggregate_binding_test.cpp#L15) | Callable definition: Catalog schema() | calls ; returns c · [reviewed contract](#b0003) |
| [B0004 · 21–26](../../../../../tests/unit/aggregate_binding_test.cpp#L21) | Callable definition: fa::AggregateProgram bind(std::string_view sql, const Catalog& c = schema(), fa::AggregateBindOptions options = {}) | calls schema, fa::bind_aggregate_sql, std::runtime_error, std::move; returns std::get&lt;fa::AggregateProgram&gt;(std::move(result)) · [reviewed contract](#b0004) |
| [B0005 · 27–31](../../../../../tests/unit/aggregate_binding_test.cpp#L27) | Callable definition: void rejection(std::string_view sql, std::string_view code, fa::AggregateBindOptions options = {}) | calls fa::bind_aggregate_sql, schema, check; guard check(error && error-&gt;diagnostic.code == code, "aggregate SQL rejection changed"); · [reviewed contract](#b0005) |
| [B0006 · 32–37](../../../../../tests/unit/aggregate_binding_test.cpp#L32) | Callable definition: void controller_only(const resource::MemoryAccount& account) | calls check_invariants, statistics, check, resource::MemoryAccount::control_bytes; guard check(now.allocations == 1 && now.requested_bytes == resource::MemoryAccount::control_bytes(), · [reviewed contract](#b0006) |
| [B0007 · 38–38](../../../../../tests/unit/aggregate_binding_test.cpp#L38) | Explanatory comments or spacing. |  |
| [B0008 · 39–65](../../../../../tests/unit/aggregate_binding_test.cpp#L39) | Callable definition: void descriptors() | calls bind, check, has_input, full_input_group_key; guard check(p && p.has_input() && !p.full_input_group_key() && p.input_types().size() == 3 && · [reviewed contract](#b0008) |
| [B0009 · 66–69](../../../../../tests/unit/aggregate_binding_test.cpp#L66) | Explanatory comments or spacing. | source comment (unverified): // Narrowing belongs to the original column, independently of final measure · [reviewed contract](#b0009) |
| [B0010 · 70–119](../../../../../tests/unit/aggregate_binding_test.cpp#L70) | Callable definition: void integer_column_casts() | calls bind, check, input_types, outputs; guard check(p.input_types()\[1\].kind == fa::SqlKind::int64 && p.outputs()\[0\].type.kind == fa::SqlKind::int…; 1 loop sites; source comment (unverified): // Narrowing belongs to the original column, independently of final measure · [reviewed contract](#b0010) |
| [B0011 · 120–120](../../../../../tests/unit/aggregate_binding_test.cpp#L120) | Explanatory comments or spacing. |  |
| [B0012 · 121–168](../../../../../tests/unit/aggregate_binding_test.cpp#L121) | Callable definition: void lifetimes_and_caps() | calls resource::MemoryAccount::create, std::to_string, schema, fa::bind_aggregate_sql_into; guard check(std::holds_alternative&lt;fa::AggregateProgram&gt;(result), "accounted aggregate binding failed");; 2 loop sites · [reviewed contract](#b0012) |
| [B0013 · 169–169](../../../../../tests/unit/aggregate_binding_test.cpp#L169) | Explanatory comments or spacing. |  |
| [B0014 · 170–207](../../../../../tests/unit/aggregate_binding_test.cpp#L170) | Callable definition: void tuple_ownership() | calls resource::MemoryAccount::create, std::string_view, storage::InlineDecimal::parse, statistics; guard check(observed &gt; 0 && observed == account.statistics().successful_allocations - before,; growth copy_of; 1 loop sites · [reviewed contract](#b0014) |
| [B0015 · 208–224](../../../../../tests/unit/aggregate_binding_test.cpp#L208) | Callable definition: void run() | calls descriptors, integer_column_casts, lifetimes_and_caps, tuple_ownership · [reviewed contract](#b0015) |
| [B0016 · 225–225](../../../../../tests/unit/aggregate_binding_test.cpp#L225) | Closes surrounding scope/type. | source comment (unverified): // namespace · [reviewed contract](#b0016) |
| [B0017 · 226–229](../../../../../tests/unit/aggregate_binding_test.cpp#L226) | Callable definition: int main() | calls run, what; returns 0; 1 · [reviewed contract](#b0017) |

## B0001

[Lines 1–13](../../../../../tests/unit/aggregate_binding_test.cpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
constexpr std::uint64_t allowance =
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Set one finite allowance for this standalone binding/tuple test fixture. |
| inputs / outputs | 16 MiB constant feeds explicitly created test accounts. |
| invariants | This fixture is not the production runtime grant or a refill policy. |
| ownership | No allocation owner is created by the declaration. |
| failure | No executable failure path. |
| cost | Compile-time numeric constant. |
| Design | [docs/aggregates.md §Logical input and publication](../../../../aggregates.md), [docs/memory_accounts.md §Account and ownership contract](../../../../memory_accounts.md) |

## B0002

[Lines 14–14](../../../../../tests/unit/aggregate_binding_test.cpp#L14); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void check(bool value,
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Turn a failed public-behavior assertion into a failing test. |
| inputs / outputs | Boolean predicate and fixed message in; returns only for true. |
| invariants | No assertion depends on disabled C assert configuration. |
| ownership | No state retained across checks. |
| failure | False throws runtime_error to the test main boundary. |
| cost | Constant successful check; failure-only diagnostic work. |
| Design | [docs/aggregates.md §Logical input and publication](../../../../aggregates.md) |

## B0003

[Lines 15–20](../../../../../tests/unit/aggregate_binding_test.cpp#L15); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Catalog schema()
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Build the logical input fixture for aggregate descriptor tests. |
| inputs / outputs | Returns relation r with nullable string g, nullable int64 x, and nonnullable boolean flag. |
| invariants | SQL NULL remains declared in catalog metadata; no physical bag source is implied. |
| ownership | Caller owns the returned ordinary catalog. |
| failure | Test fixture allocation failure propagates to main. |
| cost | Small fixed catalog construction. |
| Design | [docs/aggregates.md §SQL and numeric contract](../../../../aggregates.md), [docs/aggregates.md §Logical input and publication](../../../../aggregates.md) |

## B0004

[Lines 21–26](../../../../../tests/unit/aggregate_binding_test.cpp#L21); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
fa::AggregateProgram bind(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Require successful aggregate binding for positive fixture cases. |
| inputs / outputs | SQL/catalog/options in; owning AggregateProgram out. |
| invariants | Diagnostics are test failures with their original phase/code/message. |
| ownership | Returned program owns metadata after local binding result destruction. |
| failure | Unexpected SQL diagnostic raises runtime_error; allocation exceptions propagate. |
| cost | Cold helper invokes real public binding; no alternative implementation oracle. |
| Design | [docs/aggregates.md §Logical input and publication](../../../../aggregates.md) |

## B0005

[Lines 27–31](../../../../../tests/unit/aggregate_binding_test.cpp#L27); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void rejection(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Require a specific public SQL diagnostic for an unsupported query. |
| inputs / outputs | SQL/expected code/options in; verifies diagnostic alternative and matching code. |
| invariants | Success or an unrelated rejection cannot satisfy the case. |
| ownership | Local result owns temporary program or diagnostic until release. |
| failure | Mismatch fails test through check(). |
| cost | One compiler call per explicit negative fixture. |
| Design | [docs/aggregates.md §SQL and numeric contract](../../../../aggregates.md), [docs/aggregates.md §Logical input and publication](../../../../aggregates.md) |

## B0006

[Lines 32–37](../../../../../tests/unit/aggregate_binding_test.cpp#L32); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void controller_only(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Check exact receiver cleanup after result owners leave scope. |
| inputs / outputs | Account in; requires internal invariants and one controller allocation with exact controller bytes. |
| invariants | No retained payload is tolerated; historical allocation counters need not return to zero. |
| ownership | Caller retains the account while observing it. |
| failure | Ledger mismatch or retained payload fails the test. |
| cost | Explicit account diagnostic, not a production update scan. |
| Design | [docs/memory_accounts.md §Account and ownership contract](../../../../memory_accounts.md) |

## B0008

[Lines 39–65](../../../../../tests/unit/aggregate_binding_test.cpp#L39); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void descriptors()
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Inspect public resolved types, sharing, order and whole-input key admission. |
| inputs / outputs | Binds grouped and no-FROM COUNT/SUM/AVG cases, repeated aliases, scale zero and permuted group keys. |
| invariants | COUNT(x)/SUM(x)/AVG(x) share one measure; int32 SUM range marker and bigint/NUMERIC result types remain distinct. |
| ownership | Local programs retain descriptors during borrowed getter assertions. |
| failure | Any unexpected binding or descriptor behavior fails the case. |
| cost | Finite positive fixture checks; not SQL execution or exhaustive grammar acceptance. |
| Design | [docs/aggregates.md §SQL and numeric contract](../../../../aggregates.md), [docs/aggregates.md §Logical input and publication](../../../../aggregates.md) |

## B0009

[Lines 66–69](../../../../../tests/unit/aggregate_binding_test.cpp#L66); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L66-L69:sha256:4a0076f47b3f93eeae36cb067f756fe3ea28055fd231893715b89897ff4cae0c
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Explain the adjacent source contract: Narrowing belongs to the original column, independently of final measure sharing. Preserve the physical bigint group/result while checking every inner integer cast, including a COUNT argument widened back to bigint. |
| inputs / outputs | Human-readable source note in; no executable output or checked receipt. |
| invariants | This comment states context or a limitation. It does not itself enforce or prove the described behavior; use the adjacent implementation and its scoped contract. |
| ownership | Source text only; no object or resource lifetime is created. |
| failure | No runtime failure path in this comment; source encoding/comment syntax still belongs to compilation. |
| cost | No runtime operations from the comment. Any work described in the note belongs to the adjacent operation. |
| Design | [tests/unit/aggregate_binding_test.cpp](../../../../../tests/unit/aggregate_binding_test.cpp), [docs/aggregates.md](../../../../aggregates.md), [docs/code_review.md](../../../../code_review.md) |

## B0010

[Lines 70–119](../../../../../tests/unit/aggregate_binding_test.cpp#L70); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void integer_column_casts()
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Check exact cast descriptors and receiving ownership of immutable guards. |
| inputs / outputs | Genuine raw/narrow/widened SQL, two reverse-order columns, foreign/shared freeze, observed new-cut sweep and exact/one-under compiler work. |
| invariants | Raw grouping/input width stays bigint; integer SUM returns bigint; raw/widened SUM returns numeric; guards are sorted unique and preserved by nested COUNT/SUM dedup. |
| ownership | Foreign receiver owns copied metadata; every cut returns to controller-only; shared freeze allocates nothing. |
| failure | Expected bad_alloc and resource_limit cuts are distinct from unsupported noninteger conversions; mismatches fail check(). |
| cost | Finite descriptor/work/allocation-site checks, not CPU/global-heap bounds. |
| Design | [include/crown/frontend/aggregate.hpp](../../../../../include/crown/frontend/aggregate.hpp), [src/frontend/aggregate.cpp](../../../../../src/frontend/aggregate.cpp), [tests/support/index_allocation.hpp](../../../../../tests/support/index_allocation.hpp), [docs/aggregates.md](../../../../aggregates.md) |

## B0012

[Lines 121–168](../../../../../tests/unit/aggregate_binding_test.cpp#L121); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void lifetimes_and_caps()
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Verify retained string lifetimes and exact selected-work/receiving-byte boundaries. |
| inputs / outputs | Builds forty short aliases over one long literal; destroys/mutates source/catalog; checks exact and one-under work/byte grants. |
| invariants | One distinct argument survives as stable backing. Limits are measured for retained metadata, not unaccounted parser/compiler workspace. |
| ownership | Programs own payload until scope exit; controller_only verifies release of the same receiving account. |
| failure | Expected one-under MemoryFailure must be limit; unrelated SQL failure or leaked payload fails test. |
| cost | Finite cold calibration and replay cases; no production timing or overhead theorem. |
| Design | [docs/aggregates.md §Logical input and publication](../../../../aggregates.md), [docs/memory_accounts.md §Account and ownership contract](../../../../memory_accounts.md), [docs/query_memory.md §Boundaries](../../../../query_memory.md) |

## B0014

[Lines 170–207](../../../../../tests/unit/aggregate_binding_test.cpp#L170); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void tuple_ownership()
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Verify nullable tuple deep ownership and complete observed allocation-failure cleanup. |
| inputs / outputs | Copies int64/NULL/long string/decimal cells, mutates source, exports values, sweeps every observed allocation plus success sentinel. |
| invariants | Successful copy allocation count equals charged successful allocations. Failed copy leaves old held payload and current receiver usage unchanged. |
| ownership | Explicit caller export is outside the account; immutable held/copied/nullary tuple owners are released before final controller check. |
| failure | Only injected bad_alloc is expected in the sweep; missed faults, partial publication or retained bytes fail assertions. |
| cost | Single-fixture allocation sweep, not runtime transaction or all input coverage. |
| Design | [docs/aggregates.md §Logical input and publication](../../../../aggregates.md), [docs/memory_accounts.md §Account and ownership contract](../../../../memory_accounts.md) |

## B0015

[Lines 208–224](../../../../../tests/unit/aggregate_binding_test.cpp#L208); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void run()
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Run binding/tuple acceptance fixtures and explicit unsupported-syntax checks. |
| inputs / outputs | Calls positive/lifetime/ownership cases and rejections for DISTINCT, filter/window/predicate/multisource, grouping, types, alias, scale and zero work. |
| invariants | Success banner is emitted only after all cases return. |
| ownership | Each subcase owns its local fixtures; no production global recovery state is added. |
| failure | Any unexpected result or exception escapes to main. |
| cost | Finite component test cohort; does not exercise AggregateRuntime group execution. |
| Design | [docs/aggregates.md §SQL and numeric contract](../../../../aggregates.md), [docs/aggregates.md §Logical input and publication](../../../../aggregates.md) |

## B0016

[Lines 225–225](../../../../../tests/unit/aggregate_binding_test.cpp#L225); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L225-L225:sha256:c7bfe2f3de133d78a2bc8bb1c4a08450563986ee8254facee698e1dcc57e8162
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Close the recorded declaration scopes in aggregate_binding_test.cpp: namespace (anonymous). |
| inputs / outputs | Preceding namespace, type or initializer declarations in; completed lexical boundary out. |
| invariants | Brace-opening context is recorded in root-scope-context-v1.json. These are declaration/initializer boundaries, not an independent update, validation or recovery operation. |
| ownership | Enclosing objects and borrowed fields keep their declared ownership. This punctuation creates no new owner. |
| failure | Malformed scope syntax is a compile error. Any initializer/constructor failure belongs to the enclosing object declaration. |
| cost | No separate loop, guard or engine call is introduced by the delimiter; enclosing initialization and object lifetime still have their actual costs. |
| Design | [tests/unit/aggregate_binding_test.cpp](../../../../../tests/unit/aggregate_binding_test.cpp), [docs/aggregates.md](../../../../aggregates.md), [docs/code_review.md](../../../../code_review.md) |

## B0017

[Lines 226–229](../../../../../tests/unit/aggregate_binding_test.cpp#L226); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
int main()
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Convert a component test exception into an unambiguous process failure. |
| inputs / outputs | run() success returns zero; caught std::exception prints message and returns one. |
| invariants | The one outer reporting catch is test harness behavior, not production update recovery. |
| ownership | Automatic test owners unwind before the diagnostic is printed. |
| failure | Unexpected non-standard exceptions remain uncaught. |
| cost | Constant process boundary plus selected fixtures. |
| Design | [docs/aggregates.md §Logical input and publication](../../../../aggregates.md) |
