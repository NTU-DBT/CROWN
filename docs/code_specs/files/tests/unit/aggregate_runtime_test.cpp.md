# `tests/unit/aggregate_runtime_test.cpp` — block usage map

[Source](../../../../../tests/unit/aggregate_runtime_test.cpp) · [Source index](../../../README.md) · [Subsystem contracts](../../../subsystem_contracts.md) · [Reviewed primitives](../../../primitives.md)

Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection.

Snapshot SHA-256: `f83fc08caf9ade1d275a7b4cb89ecde8b7273ee0970492bf6b9d330dea982e4e`. 668 lines partitioned into 44 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [tests](../../../subsystem_contracts.md#tests). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/code_review.md](../../../../code_review.md), [docs/reference_fuzz.md](../../../../reference_fuzz.md), [docs/task_ledger.md](../../../../task_ledger.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–15](../../../../../tests/unit/aggregate_runtime_test.cpp#L1) | Imports dependencies; declares namespace scope; declares aliases; declares values/defaults or compile-time conditions. |  · [reviewed contract](#b0001) |
| [B0002 · 16–16](../../../../../tests/unit/aggregate_runtime_test.cpp#L16) | Callable definition: void check(bool value, const char* message) | calls std::runtime_error; guard void check(bool value, const char* message) { if (!value) throw std::runtime_error(message); } · [reviewed contract](#b0002) |
| [B0003 · 17–17](../../../../../tests/unit/aggregate_runtime_test.cpp#L17) | Callable definition: ag::SqlValue n(std::int64_t value) | calls ; returns Value{value} · [reviewed contract](#b0003) |
| [B0004 · 18–18](../../../../../tests/unit/aggregate_runtime_test.cpp#L18) | Callable definition: ag::SqlValue d(std::string_view value) | calls Decimal::parse; returns Value{Decimal::parse(value)} · [reviewed contract](#b0004) |
| [B0005 · 19–21](../../../../../tests/unit/aggregate_runtime_test.cpp#L19) | Callable definition: ag::Row row(std::optional&lt;std::string&gt; group, std::optional&lt;std::int64_t&gt; value) | calls n; returns {group ? ag::SqlValue{Value{*group}} : std::nullopt, value ? n(*value) : std::nullopt, Value{true}} · [reviewed contract](#b0005) |
| [B0006 · 22–23](../../../../../tests/unit/aggregate_runtime_test.cpp#L22) | Callable definition: Catalog schema() | calls ; returns {1, {{@ , {{@ , ScalarType::string, true}, {@ , ScalarType::int64, true}, · [reviewed contract](#b0006) |
| [B0007 · 24–30](../../../../../tests/unit/aggregate_runtime_test.cpp#L24) | Callable definition: frontend::AggregateProgram bind_program(std::string_view sql, std::uint8_t scale = 18, const Catalog& catalog = schema()) | calls schema, frontend::bind_aggregate_sql, std::runtime_error, std::move; returns std::get&lt;frontend::AggregateProgram&gt;(std::move(result)) · [reviewed contract](#b0007) |
| [B0008 · 31–35](../../../../../tests/unit/aggregate_runtime_test.cpp#L31) | Callable definition: std::vector&lt;ag::Row&gt; values(const AggregateRuntime& owner) | calls snapshot, push_back, export_values; returns result; growth push_back; 1 loop sites · [reviewed contract](#b0008) |
| [B0009 · 36–40](../../../../../tests/unit/aggregate_runtime_test.cpp#L36) | Callable definition: void controller_only(const resource::MemoryAccount& account) | calls check_invariants, statistics, check, resource::MemoryAccount::control_bytes; guard check(now.allocations == 1 && now.requested_bytes == resource::MemoryAccount::control_bytes(), "agg… · [reviewed contract](#b0009) |
| [B0010 · 41–45](../../../../../tests/unit/aggregate_runtime_test.cpp#L41) | Callable definition: template&lt;class Action&gt; void error(Action action, std::string_view code) | calls action, check, code, std::runtime_error; guard catch (const Error& failure) { check(failure.code() == code, "unexpected aggregate error code"); re… · [reviewed contract](#b0010) |
| [B0011 · 46–48](../../../../../tests/unit/aggregate_runtime_test.cpp#L46) | Callable definition: ag::Epoch set(AggregateRuntime& owner, const ag::Row& input, std::uint64_t before, std::uint64_t after) | calls apply, sequence; returns owner.apply({owner.sequence() + 1, input, before, after}) · [reviewed contract](#b0011) |
| [B0012 · 49–51](../../../../../tests/unit/aggregate_runtime_test.cpp#L49) | Explanatory comments or spacing. | source comment (unverified): // Group presence follows total input weight; NULL arguments and cancellation · [reviewed contract](#b0012) |
| [B0013 · 52–97](../../../../../tests/unit/aggregate_runtime_test.cpp#L52) | Callable definition: void semantics() | calls global, bind_program, check, values; guard check(values(global) == std::vector&lt;ag::Row&gt;{{n(0), n(0), {}, {}}}, "empty global SQL result");; source comment (unverified): // Group presence follows total input weight; NULL arguments and cancellation · [reviewed contract](#b0013) |
| [B0014 · 98–100](../../../../../tests/unit/aggregate_runtime_test.cpp#L98) | Explanatory comments or spacing. | source comment (unverified): // Public bigint counts and SUM(integer) remain bounded even with output capture · [reviewed contract](#b0014) |
| [B0015 · 101–137](../../../../../tests/unit/aggregate_runtime_test.cpp#L101) | Callable definition: void arithmetic_and_admission() | calls owner, bind_program, row, set; guard check(values(owner) == std::vector&lt;ag::Row&gt;{{n(INT64_MAX), n(INT64_MAX),; source comment (unverified): // Public bigint counts and SUM(integer) remain bounded even with output capture · [reviewed contract](#b0015) |
| [B0016 · 138–138](../../../../../tests/unit/aggregate_runtime_test.cpp#L138) | Explanatory comments or spacing. |  |
| [B0017 · 139–173](../../../../../tests/unit/aggregate_runtime_test.cpp#L139) | Callable definition: void bounded_work_and_hot_path() | calls row, std::string, bind_program, reset; guard if (exact) { check(set(owner, input, 0, 2).metrics.work == work, "exact aggregate work cap"); }; 2 loop sites · [reviewed contract](#b0017) |
| [B0018 · 174–177](../../../../../tests/unit/aggregate_runtime_test.cpp#L174) | Explanatory comments or spacing. | source comment (unverified): // Sweep the allocator's observed successful sites, followed by a success · [reviewed contract](#b0018) |
| [B0019 · 178–244](../../../../../tests/unit/aggregate_runtime_test.cpp#L178) | Callable definition: void allocation_failures() | calls bind_program, account, statistics, row; guard check(construction == account.statistics().successful_allocations - allocations, "runtime construct…; growth emplace; 4 loop sites; source comment (unverified): // Sweep the allocator's observed successful sites, followed by a success · [reviewed contract](#b0019) |
| [B0020 · 245–247](../../../../../tests/unit/aggregate_runtime_test.cpp#L245) | Explanatory comments or spacing. | source comment (unverified): // Snapshot construction allocates independently of update publication. Older · [reviewed contract](#b0020) |
| [B0021 · 248–281](../../../../../tests/unit/aggregate_runtime_test.cpp#L248) | Callable definition: void snapshot_failures() | calls resource::MemoryAccount::create, bind_program, AggregateRuntime::create_into, row; guard check(observed &gt; 0 && observed == account.statistics().successful_allocations - allocations,; growth emplace; 1 loop sites; source comment (unverified): // Snapshot construction allocates independently of update publication. Older · [reviewed contract](#b0021) |
| [B0022 · 282–282](../../../../../tests/unit/aggregate_runtime_test.cpp#L282) | Explanatory comments or spacing. |  |
| [B0023 · 283–324](../../../../../tests/unit/aggregate_runtime_test.cpp#L283) | Callable definition: void receiver_caps_and_lifetimes() | calls bind_program, source_sql, source, account; guard const auto event = set(owner, input, 0, 3); check(bool(event.output), "cap calibration event missin…; 1 loop sites · [reviewed contract](#b0023) |
| [B0024 · 325–328](../../../../../tests/unit/aggregate_runtime_test.cpp#L325) | Explanatory comments or spacing. | source comment (unverified): // Use actual W03 compressed result tuples, retaining each producer's payload · [reviewed contract](#b0024) |
| [B0025 · 329–343](../../../../../tests/unit/aggregate_runtime_test.cpp#L329) | Callable definition: void weighted_producer() | calls producer, weighted_test::unary, apply, aggregate; guard check(item && item-&gt;multiplicity.value == 5, "weighted producer did not return compressed bag row");; 1 loop sites; source comment (unverified): // Use actual W03 compressed result tuples, retaining each producer's payload · [reviewed contract](#b0025) |
| [B0026 · 344–345](../../../../../tests/unit/aggregate_runtime_test.cpp#L344) | Explanatory comments or spacing. | source comment (unverified): // Proposed W06-local tests. These test caller-fed logical deltas only; no · [reviewed contract](#b0026) |
| [B0027 · 346–352](../../../../../tests/unit/aggregate_runtime_test.cpp#L346) | Callable definition: std::array&lt;ag::Cell, 3&gt; nullable_cells(const ag::Row& input) | calls check, size, storage::borrow_scalar; guard check(input.size() == 3, "batch fixture arity");; returns result; 1 loop sites; source comment (unverified): // Proposed W06-local tests. These test caller-fed logical deltas only; no · [reviewed contract](#b0027) |
| [B0028 · 353–355](../../../../../tests/unit/aggregate_runtime_test.cpp#L353) | Callable definition: AggregateRuntime::PreparedBatch prepare(AggregateRuntime& owner, std::span&lt;const ag::RowDelta&gt; deltas) | calls prepare_batch, sequence; returns owner.prepare_batch({owner.sequence() + 1, deltas}) · [reviewed contract](#b0028) |
| [B0029 · 356–356](../../../../../tests/unit/aggregate_runtime_test.cpp#L356) | Explanatory comments or spacing. |  |
| [B0030 · 357–420](../../../../../tests/unit/aggregate_runtime_test.cpp#L357) | Callable definition: void batch_groups_and_empty() | calls owner, bind_program, row, nullable_cells; guard check(owner.sequence() == sequence && pending.preview().sequence == sequence + 1 && pending.preview…; growth emplace · [reviewed contract](#b0030) |
| [B0031 · 421–421](../../../../../tests/unit/aggregate_runtime_test.cpp#L421) | Explanatory comments or spacing. |  |
| [B0032 · 422–474](../../../../../tests/unit/aggregate_runtime_test.cpp#L422) | Callable definition: void batch_sum_and_admission() | calls row, nullable_cells, owner, bind_program; guard check(owner.sequence() == sequence && values(owner) == old, "single-row SUM gate changed");; 3 loop sites; source comment (unverified): // Retain the constant-measure boundary independently of varying casts. · [reviewed contract](#b0032) |
| [B0033 · 475–478](../../../../../tests/unit/aggregate_runtime_test.cpp#L475) | Explanatory comments or spacing. | source comment (unverified): // Each signed contribution exceeds bigint here, while the consolidated final · [reviewed contract](#b0033) |
| [B0034 · 479–521](../../../../../tests/unit/aggregate_runtime_test.cpp#L479) | Callable definition: void varying_integer_batches() | calls row, nullable_cells, owner, bind_program; guard check(owner.sequence() == 0, "single overflowing integer contribution published");; 2 loop sites; source comment (unverified): // Each signed contribution exceeds bigint here, while the consolidated final · [reviewed contract](#b0034) |
| [B0035 · 522–524](../../../../../tests/unit/aggregate_runtime_test.cpp#L522) | Explanatory comments or spacing. | source comment (unverified): // Repeated/nested casts add one checkpoint per guarded column, no per-update · [reviewed contract](#b0035) |
| [B0036 · 525–549](../../../../../tests/unit/aggregate_runtime_test.cpp#L525) | Callable definition: void integer_guard_work() | calls bind_program, n, plain, narrowed; guard check(s04_alloc::calls == 0, "integer guard existing-row update allocated");; source comment (unverified): // Repeated/nested casts add one checkpoint per guarded column, no per-update · [reviewed contract](#b0036) |
| [B0037 · 550–550](../../../../../tests/unit/aggregate_runtime_test.cpp#L550) | Explanatory comments or spacing. |  |
| [B0038 · 551–627](../../../../../tests/unit/aggregate_runtime_test.cpp#L551) | Callable definition: void batch_faults_and_work() | calls bind_program, account, statistics, row; guard check(observed &gt; 0 && observed &lt; 256 && observed == account.statistics().successful_allocations - a…; growth emplace; 3 loop sites · [reviewed contract](#b0038) |
| [B0039 · 628–628](../../../../../tests/unit/aggregate_runtime_test.cpp#L628) | Explanatory comments or spacing. |  |
| [B0040 · 629–658](../../../../../tests/unit/aggregate_runtime_test.cpp#L629) | Callable definition: void batch_owner_lifetimes() | calls bind_program, resource::MemoryAccount::create, AggregateRuntime::create_into, row; guard check(pending-&gt;active() && pending-&gt;preview().output\[0\].key.export_values()\[0\] ==; growth emplace · [reviewed contract](#b0040) |
| [B0041 · 659–659](../../../../../tests/unit/aggregate_runtime_test.cpp#L659) | Explanatory comments or spacing. |  |
| [B0042 · 660–666](../../../../../tests/unit/aggregate_runtime_test.cpp#L660) | Callable definition: void run() | calls batch_groups_and_empty, batch_sum_and_admission, varying_integer_batches, integer_guard_work · [reviewed contract](#b0042) |
| [B0043 · 667–667](../../../../../tests/unit/aggregate_runtime_test.cpp#L667) | Closes surrounding scope/type. | source comment (unverified): // namespace · [reviewed contract](#b0043) |
| [B0044 · 668–668](../../../../../tests/unit/aggregate_runtime_test.cpp#L668) | Callable definition: int main() | calls run, what; returns 0; 1 · [reviewed contract](#b0044) |

## B0001

[Lines 1–15](../../../../../tests/unit/aggregate_runtime_test.cpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
constexpr std::uint64_t allowance =
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Set up the public aggregate/weighted fixture interfaces and finite receiver grant for this test executable. |
| inputs / outputs | Headers, namespace aliases and a 32 MiB allowance supply the following test helpers. |
| invariants | The global allocation hook is defined in this single test translation unit, not in a production library. |
| ownership | Includes and aliases create no per-update owner; each tested receiver account is explicit. |
| failure | No runtime admission occurs in these declarations. |
| cost | Fixed declarations and one scalar constant; allocator hooks add test instrumentation only. |
| Design | [docs/aggregates.md](../../../../aggregates.md), [Refactor.md § W04 — Implement COUNT, SUM and AVG](../../../../../Refactor.md), [tests/support/index_allocation.hpp](../../../../../tests/support/index_allocation.hpp), [tests/support/weighted_fixture.hpp](../../../../../tests/support/weighted_fixture.hpp) |

## B0002

[Lines 16–16](../../../../../tests/unit/aggregate_runtime_test.cpp#L16); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void check(bool value,
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Turn a failed native assertion into a readable test failure. |
| inputs / outputs | Condition and static message in; normal return if true. |
| invariants | A false condition never allows subsequent assertions to report success. |
| ownership | Message is borrowed; runtime_error owns failure text when constructed. |
| failure | False throws runtime_error; constructing it may allocate, including inside an allocation-hook scope. |
| cost | Constant success path; exception construction only on assertion failure. |
| Design | [docs/aggregates.md](../../../../aggregates.md), [Refactor.md § W04 — Implement COUNT, SUM and AVG](../../../../../Refactor.md) |

## B0003

[Lines 17–17](../../../../../tests/unit/aggregate_runtime_test.cpp#L17); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
ag::SqlValue n(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Build an expected non-NULL signed bigint cell. |
| inputs / outputs | int64 value in; optional public Value with that integer out. |
| invariants | No floating conversion changes numeric equality. |
| ownership | The inline cell owns its scalar. |
| failure | No throwing allocation on the inline integer path. |
| cost | Constant inline construction. |
| Design | [docs/aggregates.md](../../../../aggregates.md), [Refactor.md § W04 — Implement COUNT, SUM and AVG](../../../../../Refactor.md) |

## B0004

[Lines 18–18](../../../../../tests/unit/aggregate_runtime_test.cpp#L18); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
ag::SqlValue d(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Build an exact expected decimal cell from authored text. |
| inputs / outputs | Borrowed decimal spelling in; optional owning Decimal Value out. |
| invariants | Comparison uses exact canonical decimal values rather than double approximations. |
| ownership | The returned Decimal owns its coefficient; the input string is borrowed only during parse. |
| failure | Malformed authored text or allocation errors fail the test. |
| cost | Linear authored spelling parsing with caller-owned decimal/string storage. |
| Design | [docs/aggregates.md](../../../../aggregates.md), [Refactor.md § W04 — Implement COUNT, SUM and AVG](../../../../../Refactor.md) |

## B0005

[Lines 19–21](../../../../../tests/unit/aggregate_runtime_test.cpp#L19); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
ag::Row row(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Construct the fixed three-column nullable input DTO used by aggregate tests. |
| inputs / outputs | Optional group string and optional int64 value in; row(g,x,true) out. |
| invariants | Optional absence means SQL NULL while the flag remains non-NULL. |
| ownership | Returned Row and any group string are caller-owned and borrowed synchronously by apply. |
| failure | Vector/string allocation failure propagates. |
| cost | Fixed three cells plus copied group bytes. |
| Design | [docs/aggregates.md](../../../../aggregates.md), [Refactor.md § W04 — Implement COUNT, SUM and AVG](../../../../../Refactor.md) |

## B0006

[Lines 22–23](../../../../../tests/unit/aggregate_runtime_test.cpp#L22); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Catalog schema()
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Provide one typed logical relation for binder and runtime tests. |
| inputs / outputs | No arguments; version-1 Catalog with r(g nullable string,x nullable int64,flag non-null boolean) out. |
| invariants | Input positions agree with row() and the independent SQL driver schema. |
| ownership | Returned Catalog owns names and vectors until binding returns. |
| failure | Standard allocation failure propagates. |
| cost | Fixed-size three-column catalog construction. |
| Design | [docs/aggregates.md](../../../../aggregates.md), [Refactor.md § W04 — Implement COUNT, SUM and AVG](../../../../../Refactor.md) |

## B0007

[Lines 24–30](../../../../../tests/unit/aggregate_runtime_test.cpp#L24); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
frontend::AggregateProgram bind_program(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Compile authored SQL through the real public binder with the requested AVG scale. |
| inputs / outputs | SQL, scale and optional Catalog in; factory-produced AggregateProgram out. |
| invariants | A binding diagnostic fails the fixture instead of creating a synthetic program. |
| ownership | Program owns accounted immutable metadata independently of SQL/Catalog argument lifetime. |
| failure | Binder diagnostics become runtime_error; allocation/account failures propagate. |
| cost | Full cold SQL parsing/binding and metadata allocation; outside measured update scopes. |
| Design | [docs/aggregates.md](../../../../aggregates.md), [Refactor.md § W04 — Implement COUNT, SUM and AVG](../../../../../Refactor.md) |

## B0008

[Lines 31–35](../../../../../tests/unit/aggregate_runtime_test.cpp#L31); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::vector<ag::Row> values(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Export current ordered aggregate values for clear expected-result assertions. |
| inputs / outputs | Live runtime in; ordinary vector of owning nullable output rows out. |
| invariants | This helper intentionally observes output values; separate tests/oracle cover full group identity. |
| ownership | Temporary Snapshot is receiver-funded; returned rows and exports are caller-owned. |
| failure | Snapshot/export/account/standard allocation failures propagate. |
| cost | Full group snapshot and owned export on every call; never part of a claimed zero-allocation update interval. |
| Design | [docs/aggregates.md](../../../../aggregates.md), [Refactor.md § W04 — Implement COUNT, SUM and AVG](../../../../../Refactor.md) |

## B0009

[Lines 36–40](../../../../../tests/unit/aggregate_runtime_test.cpp#L36); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void controller_only(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Verify that a released component returned all payload to its account. |
| inputs / outputs | Live MemoryAccount in; normal return only for one controller allocation at control_bytes. |
| invariants | Account invariants must hold, and no tuple/map/output payload may remain. |
| ownership | The account handle intentionally keeps the controller alive for inspection. |
| failure | Invariant errors or failed usage assertion fail the test. |
| cost | Explicit full account diagnostic and statistics inspection; not hot-path work. |
| Design | [docs/aggregates.md](../../../../aggregates.md), [Refactor.md § W04 — Implement COUNT, SUM and AVG](../../../../../Refactor.md), [docs/query_memory.md](../../../../query_memory.md), [docs/memory_accounts.md](../../../../memory_accounts.md) |

## B0010

[Lines 41–45](../../../../../tests/unit/aggregate_runtime_test.cpp#L41); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
template<class Action> void error(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Assert a precise public Error code for a rejected operation. |
| inputs / outputs | Callable and expected error code in; returns only after matching Error. |
| invariants | Success or a different Error code fails the fixture; unrelated exceptions propagate. |
| ownership | Callable captures retain their test-scope owners; the helper adds no state to the runtime. |
| failure | Missing/wrong Error becomes test failure; handler is test expectation machinery. |
| cost | One attempted action and exception inspection; only rejection paths throw. |
| Design | [docs/aggregates.md](../../../../aggregates.md), [Refactor.md § W04 — Implement COUNT, SUM and AVG](../../../../../Refactor.md) |

## B0011

[Lines 46–48](../../../../../tests/unit/aggregate_runtime_test.cpp#L46); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
ag::Epoch set(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Submit one exact before/after weight replacement at the runtime next epoch. |
| inputs / outputs | Runtime, owning input DTO and exact weights in; public Epoch out. |
| invariants | The helper does not mutate the DTO and assumes test sequences are far below UINT64_MAX. |
| ownership | Input is borrowed for the synchronous call; any returned event owns captured tuples. |
| failure | Runtime admission/resource/arithmetic failures propagate to the caller. |
| cost | One sequence query and one public apply; underlying replacement cost is measured separately. |
| Design | [docs/aggregates.md](../../../../aggregates.md), [Refactor.md § W04 — Implement COUNT, SUM and AVG](../../../../../Refactor.md) |

## B0012

[Lines 49–51](../../../../../tests/unit/aggregate_runtime_test.cpp#L49); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
// Group presence follows total input weight;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | State the semantic distinction exercised by the following group tests. |
| inputs / outputs | Comment relates total multiplicity, argument NULL handling and signed cancellation. |
| invariants | A zero sufficient-statistic sum does not by itself remove a group. |
| ownership | No owner or state is created. |
| failure | No executable branch. |
| cost | No runtime work. |
| Design | [docs/aggregates.md](../../../../aggregates.md), [Refactor.md § W04 — Implement COUNT, SUM and AVG](../../../../../Refactor.md) |

## B0013

[Lines 52–97](../../../../../tests/unit/aggregate_runtime_test.cpp#L52); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void semantics()
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Exercise global/grouped emptiness, NULL counts, cancellation, event presence and exact AVG rounding. |
| inputs / outputs | Authored SQL and weighted rows in; assertions for values, group creation/removal, no-op and singleton behavior. |
| invariants | Global empty remains one row; grouped last deletion removes a group; all-NULL SUM/AVG are NULL; rounded equal AVG emits no output change. |
| ownership | Captured old output tuples remain owned after subsequent deletion; no-FROM source is immutable. |
| failure | Any unexpected value/event/code or explicit invariant failure aborts the test. |
| cost | Small deterministic histories with full snapshots/exports and explicit diagnostics; no timing or exhaustive SQL claim. |
| Design | [docs/aggregates.md](../../../../aggregates.md), [Refactor.md § W04 — Implement COUNT, SUM and AVG](../../../../../Refactor.md) |

## B0014

[Lines 98–100](../../../../../tests/unit/aggregate_runtime_test.cpp#L98); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
// Public bigint counts and SUM(integer)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Document the distinct public count/SUM result bounds tested below. |
| inputs / outputs | Comment contrasts checked bigint outputs with the wider private integer numerator. |
| invariants | Disabling output capture does not disable numeric publication checks. |
| ownership | No owner or state is created. |
| failure | No executable branch. |
| cost | No runtime work. |
| Design | [docs/aggregates.md](../../../../aggregates.md), [Refactor.md § W04 — Implement COUNT, SUM and AVG](../../../../../Refactor.md) |

## B0015

[Lines 101–137](../../../../../tests/unit/aggregate_runtime_test.cpp#L101); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void arithmetic_and_admission()
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Check admitted numeric extremes and atomic rejection of malformed/overflowing replacements. |
| inputs / outputs | INT64_MIN at INT64_MAX multiplicity, int32 SUM boundary, AVG-only wide sum, and invalid requests in; exact outputs/error assertions out. |
| invariants | Count or SUM(integer) overflow leaves sequence/results unchanged, and AVG alone is not constrained to SUM(integer) output range. |
| ownership | Runtime/programs use their finite standalone accounts; DTOs and expected values are ordinary test memory. |
| failure | Expected count/arithmetic/type/weight/epoch/result/work/options/program errors are checked by code; unexpected failures propagate. |
| cost | Compressed extreme weights require no repeated-row expansion; snapshot/expected-decimal construction and diagnostics remain explicit test cost. |
| Design | [docs/aggregates.md](../../../../aggregates.md), [Refactor.md § W04 — Implement COUNT, SUM and AVG](../../../../../Refactor.md) |

## B0017

[Lines 139–173](../../../../../tests/unit/aggregate_runtime_test.cpp#L139); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void bounded_work_and_hot_path()
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Check calibrated logical work boundaries and allocation-free uncaptured updates with repeated output aliases. |
| inputs / outputs | One captured new-group update calibrates exact/one-under work; 512 SUM aliases and one SUM each update one existing row. |
| invariants | Work failure preserves sequence/current receiver charge/empty grouped result. Under replacement-new denial, both existing-row updates make zero heap requests and charge one shared measure. |
| ownership | Measured native intervals borrow prebuilt input/program state; snapshots and SQL construction occur outside the allocation-denied interval. |
| failure | Expected logical-work exhaustion and any unexpected heap request/assertion fail the test. |
| cost | Equal counters prove only selected logical work, not elapsed CPU. Current production cleanup clears output only inside render; the test records no latency benchmark. |
| Design | [docs/aggregates.md](../../../../aggregates.md), [Refactor.md § W04 — Implement COUNT, SUM and AVG](../../../../../Refactor.md), [tests/support/index_allocation.hpp](../../../../../tests/support/index_allocation.hpp), [src/runtime/aggregate.cpp](../../../../../src/runtime/aggregate.cpp) |

## B0018

[Lines 174–177](../../../../../tests/unit/aggregate_runtime_test.cpp#L174); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
// Sweep the allocator's observed successful sites,
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Describe the calibrated fault/sentinel/retry acceptance pattern for the following test. |
| inputs / outputs | Comment states required state/current-charge preservation after each observed allocation failure. |
| invariants | Observed replacement-new sites and one following success sentinel are swept; this is not exhaustive allocator behavior or a latency theorem. |
| ownership | Failed attempts must leave prior owners intact. |
| failure | No executable branch in the comment. |
| cost | No runtime work. |
| Design | [docs/aggregates.md](../../../../aggregates.md), [Refactor.md § W04 — Implement COUNT, SUM and AVG](../../../../../Refactor.md) |

## B0019

[Lines 178–244](../../../../../tests/unit/aggregate_runtime_test.cpp#L178); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void allocation_failures()
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Sweep all observed constructor/update allocation sites and verify same-account retries without partial publication. |
| inputs / outputs | Grouped/global/no-FROM constructor shapes and grouped insertion/change/last deletion in; calibrated replacement-new fault/sentinel assertions out. |
| invariants | Constructor failure leaves only controller. Update failure preserves values, epoch and current charge; retry advances exactly once. Shared compiler program statistics remain exactly unchanged. |
| ownership | Fresh receiving accounts fund each attempted runtime; source immutable program remains external. Captured results release before controller-only checks. |
| failure | Each observed site must throw bad_alloc and the sentinel must succeed; unexpected exception/count/state leakage fails the test. |
| cost | Calibration plus one attempt per observed allocation site and retry, with full snapshots/diagnostics outside injection. Counts are discovered from the current implementation, not hardcoded asymptotic claims. |
| Design | [docs/aggregates.md](../../../../aggregates.md), [Refactor.md § W04 — Implement COUNT, SUM and AVG](../../../../../Refactor.md), [tests/support/index_allocation.hpp](../../../../../tests/support/index_allocation.hpp), [docs/query_memory.md](../../../../query_memory.md) |

## B0020

[Lines 245–247](../../../../../tests/unit/aggregate_runtime_test.cpp#L245); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
// Snapshot construction allocates independently
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Explain why snapshot fault handling has its own test boundary. |
| inputs / outputs | Comment identifies immutable prior results and same-owner retry obligations. |
| invariants | Snapshot failure must not alter committed aggregate state. |
| ownership | Older snapshot tuples remain independent owning handles. |
| failure | No executable branch. |
| cost | No runtime work. |
| Design | [docs/aggregates.md](../../../../aggregates.md), [Refactor.md § W04 — Implement COUNT, SUM and AVG](../../../../../Refactor.md) |

## B0021

[Lines 248–281](../../../../../tests/unit/aggregate_runtime_test.cpp#L248); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void snapshot_failures()
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Sweep independently allocating snapshot construction while retaining an older immutable result. |
| inputs / outputs | Populated receiver-funded runtime in; observed snapshot allocation failures, success sentinel and retry assertions out. |
| invariants | Each failed snapshot preserves epoch/current charge/values; retry equals retained old output and releasing each result restores the baseline charge. |
| ownership | Held prior Snapshot is included in the baseline; optional new result is reset between attempts and all outputs release before controller check. |
| failure | Observed fault positions must fail with bad_alloc; missed sites, changed output or leaked charges fail the test. |
| cost | One calibration and one snapshot attempt per observed site, with explicit result equality/export checks. This is output-boundary testing, not update performance measurement. |
| Design | [docs/aggregates.md](../../../../aggregates.md), [Refactor.md § W04 — Implement COUNT, SUM and AVG](../../../../../Refactor.md), [tests/support/index_allocation.hpp](../../../../../tests/support/index_allocation.hpp), [docs/query_memory.md](../../../../query_memory.md) |

## B0023

[Lines 283–324](../../../../../tests/unit/aggregate_runtime_test.cpp#L283); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void receiver_caps_and_lifetimes()
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Check exact receiving grant boundaries and retained event/snapshot/source ownership after runtime destruction. |
| inputs / outputs | Calibrated insertion peak, peak-minus-one account, moved runtime, mutated caller input and final source handle release in; cap/lifetime assertions out. |
| invariants | One-under grant rejects without publication or retained payload. After runtime and external program release, snapshot still owns readable SQL metadata and old output; releasing results returns both accounts to controllers. |
| ownership | Saved SQL text is caller-owned; source_account keeps only the compiler controller alive. Snapshot owns the final program metadata; event owns captured output independently of runtime. |
| failure | Expected receiver MemoryFailure must be a limit fault, moved-from access must reject, and cap/lifetime/account assertions fail on mismatch. |
| cost | Implementation-calibrated peak covers this exact fixture, not all queries; full snapshots, string mutation and destruction are explicit test work. |
| Design | [docs/aggregates.md](../../../../aggregates.md), [Refactor.md § W04 — Implement COUNT, SUM and AVG](../../../../../Refactor.md), [docs/query_memory.md](../../../../query_memory.md), [docs/memory_accounts.md](../../../../memory_accounts.md) |

## B0024

[Lines 325–328](../../../../../tests/unit/aggregate_runtime_test.cpp#L325); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
// Use actual W03 compressed result tuples,
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Document the supported scope of the producer ingestion test. |
| inputs / outputs | Comment distinguishes direct compressed tuple borrowing from coordinated transactions or automatic SQL bag source admission. |
| invariants | Producer payload must remain alive during apply_weighted. |
| ownership | The held result/view provides that lifetime. |
| failure | No executable branch. |
| cost | No runtime work. |
| Design | [docs/aggregates.md](../../../../aggregates.md), [Refactor.md § W04 — Implement COUNT, SUM and AVG](../../../../../Refactor.md), [docs/weighted_enumeration.md](../../../../weighted_enumeration.md) |

## B0025

[Lines 329–343](../../../../../tests/unit/aggregate_runtime_test.cpp#L329); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void weighted_producer()
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Feed real W03 compressed result rows into the aggregate public weighted boundary for both storage backends. |
| inputs / outputs | Unary weighted producer row x=7 at multiplicity 5 in; aggregate COUNT/SUM/AVG and last-row retraction assertions out. |
| invariants | Exactly one compressed row is observed; aggregate insertion gives (5,35,7) and retraction restores global empty output. |
| ownership | The retained optional producer Result owns its tuple while both synchronous apply_weighted calls borrow values; no repeated-row DTO expansion occurs. |
| failure | Producer/result/aggregate or invariant mismatch fails the test. |
| cost | Two small backend fixtures with explicit producer enumeration and full aggregate observations; not a multi-runtime atomicity or general SQL bag adapter gate. |
| Design | [docs/aggregates.md](../../../../aggregates.md), [Refactor.md § W04 — Implement COUNT, SUM and AVG](../../../../../Refactor.md), [docs/weighted_enumeration.md](../../../../weighted_enumeration.md), [tests/support/weighted_fixture.hpp](../../../../../tests/support/weighted_fixture.hpp) |

## B0026

[Lines 344–345](../../../../../tests/unit/aggregate_runtime_test.cpp#L344); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
// Proposed W06-local tests.
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Constrain new fixtures to caller-fed logical deltas and state which integration gates they do not cover. |
| inputs / outputs | Comment scopes the four new local batch fixtures and their RowDelta adapters. |
| invariants | Passing tests only the aggregate-local row ledger. It establishes no physical source/native/session/recovery integration or compiler-composed publication. |
| ownership | No runtime owner is created by the comment; following helpers specify borrows. |
| failure | No executable branch; assertions and error codes reside in test functions. |
| cost | No runtime cost; finite tests are not a performance result. |
| Design | [build/verification/w06-aggregate-batch-design-v1/design.md](../../../../../build/verification/w06-aggregate-batch-design-v1/design.md), [docs/aggregates.md](../../../../aggregates.md), Refactor.md:1325-1327, [build/verification/w06-contract-assessment-v1/assessment.md](../../../../../build/verification/w06-contract-assessment-v1/assessment.md), [tests/unit/aggregate_runtime_test.cpp](../../../../../tests/unit/aggregate_runtime_test.cpp), [tests/support/index_allocation.hpp](../../../../../tests/support/index_allocation.hpp), [tests/support/weighted_fixture.hpp](../../../../../tests/support/weighted_fixture.hpp), [docs/aggregate_batches.md](../../../../aggregate_batches.md), [build/verification/aggregate-batch-acceptance-v1/findings.json](../../../../../build/verification/aggregate-batch-acceptance-v1/findings.json) |

## B0027

[Lines 346–352](../../../../../tests/unit/aggregate_runtime_test.cpp#L346); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::array<ag::Cell, 3> nullable_cells(const ag::Row& input)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Adapt the three-column owning test Row into borrowed nullable cells for prepare_batch. |
| inputs / outputs | Checks arity 3, then borrows each optional Value to fixed std::array&lt;Cell,3&gt; using storage::borrow_scalar. |
| invariants | NULL is absence; scalar alternatives remain typed. It performs no owning string copy or schema admission. |
| ownership | Array owns descriptors only; source Row/string must survive until prepare_batch returns. |
| failure | Fixture arity mismatch throws runtime_error; runtime validates schema/type/nullability later. |
| cost | Fixed array and three descriptor conversions, no vector/string payload copy. |
| Design | [build/verification/w06-aggregate-batch-design-v1/design.md](../../../../../build/verification/w06-aggregate-batch-design-v1/design.md), [docs/aggregates.md](../../../../aggregates.md), Refactor.md:1325-1327, [build/verification/w06-contract-assessment-v1/assessment.md](../../../../../build/verification/w06-contract-assessment-v1/assessment.md), [tests/unit/aggregate_runtime_test.cpp](../../../../../tests/unit/aggregate_runtime_test.cpp), [tests/support/index_allocation.hpp](../../../../../tests/support/index_allocation.hpp), [tests/support/weighted_fixture.hpp](../../../../../tests/support/weighted_fixture.hpp), [docs/aggregate_batches.md](../../../../aggregate_batches.md), [build/verification/aggregate-batch-acceptance-v1/findings.json](../../../../../build/verification/aggregate-batch-acceptance-v1/findings.json) |

## B0028

[Lines 353–355](../../../../../tests/unit/aggregate_runtime_test.cpp#L353); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
AggregateRuntime::PreparedBatch prepare(AggregateRuntime& owner, std::span<const ag::RowDelta> deltas)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Call prepare_batch at the facade’s next committed sequence for compact test setup. |
| inputs / outputs | AggregateRuntime and borrowed RowDelta span enter; PreparedBatch leaves from the public call. |
| invariants | No consolidation or input ownership; empty span passes through. Sequence remains old until commit. |
| ownership | Nested cell/string borrows remain valid through synchronous call only; token owns its private proposals afterward. |
| failure | Public busy/row/work/account/arithmetic errors propagate unchanged. |
| cost | One scalar sequence read plus API invocation; validation/preparation cost is tested runtime cost. |
| Design | [build/verification/w06-aggregate-batch-design-v1/design.md](../../../../../build/verification/w06-aggregate-batch-design-v1/design.md), [docs/aggregates.md](../../../../aggregates.md), Refactor.md:1325-1327, [build/verification/w06-contract-assessment-v1/assessment.md](../../../../../build/verification/w06-contract-assessment-v1/assessment.md), [tests/unit/aggregate_runtime_test.cpp](../../../../../tests/unit/aggregate_runtime_test.cpp), [tests/support/index_allocation.hpp](../../../../../tests/support/index_allocation.hpp), [tests/support/weighted_fixture.hpp](../../../../../tests/support/weighted_fixture.hpp), [docs/aggregate_batches.md](../../../../aggregate_batches.md), [build/verification/aggregate-batch-acceptance-v1/findings.json](../../../../../build/verification/aggregate-batch-acceptance-v1/findings.json) |

## B0030

[Lines 357–420](../../../../../tests/unit/aggregate_runtime_test.cpp#L357); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void batch_groups_and_empty() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Exercise grouped swaps, busy/move/commit, empty/global/NULL semantics, and count-limit failure atomicity. |
| inputs / outputs | Two groups at count_limit 3 swap old/new rows through four deltas; further cases cover empty batch, global/grouped deletion, NULL key/argument, identical output identities, and no-FROM rejection. |
| invariants | The source array lists adds before retracts, but runtime applies all retracts first; each touched group finalizes once. Pending preview leaves committed sequence old; busy operations reject; empty batch advances without changed. |
| ownership | Cell arrays borrow live fixture Rows through prepare; captured token/result tuples own payloads. Token follows facade move. |
| failure | Checks aggregate_busy, invalid token, and final count overflow. s04_alloc denial observes replacement-new only and is not a raw malloc/syscall or universal allocator proof. |
| cost | Small histories with snapshots/exports/invariant recomputation outside denied interval; no timing or broad SQL claim. |
| Design | [build/verification/w06-aggregate-batch-design-v1/design.md](../../../../../build/verification/w06-aggregate-batch-design-v1/design.md), [docs/aggregates.md](../../../../aggregates.md), Refactor.md:1325-1327, [build/verification/w06-contract-assessment-v1/assessment.md](../../../../../build/verification/w06-contract-assessment-v1/assessment.md), [tests/unit/aggregate_runtime_test.cpp](../../../../../tests/unit/aggregate_runtime_test.cpp), [tests/support/index_allocation.hpp](../../../../../tests/support/index_allocation.hpp), [tests/support/weighted_fixture.hpp](../../../../../tests/support/weighted_fixture.hpp), [docs/aggregate_batches.md](../../../../aggregate_batches.md), [build/verification/aggregate-batch-acceptance-v1/findings.json](../../../../../build/verification/aggregate-batch-acceptance-v1/findings.json) |

## B0032

[Lines 422–474](../../../../../tests/unit/aggregate_runtime_test.cpp#L422); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void batch_sum_and_admission() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Check supported constant SUM(integer) replacement/range boundaries, unsigned row-delta errors, and AVG NULL/scale/rounding behavior. |
| inputs / outputs | SUM(2147483647) over compressed row weights, plus zero/±1/NULL int64 rows at AVG scales 0–18; exact bigint/decimal outputs and error codes are asserted. |
| invariants | This fixture deliberately retains constant SUM(integer) replacement/final overflow coverage independently of the separate varying_integer_batches test. It also checks unsigned row-delta errors, NULL/AVG scale rounding and rounded-equal suppression. |
| ownership | Row fixtures own strings; nullable_cells arrays borrow only through prepare; output/snapshot tuples own their payloads. |
| failure | Expected aggregate_overflow, aggregate_weight_mismatch and invalid_aggregate_batch leave sequence/output unchanged; unexpected result fails the test. |
| cost | Finite scale/fixture loops with exact decimals and explicit snapshots/invariants; no performance or compiler-admission theorem. |
| Design | [build/verification/w06-aggregate-batch-design-v1/design.md](../../../../../build/verification/w06-aggregate-batch-design-v1/design.md), [docs/aggregates.md](../../../../aggregates.md), Refactor.md:1325-1327, [build/verification/w06-contract-assessment-v1/assessment.md](../../../../../build/verification/w06-contract-assessment-v1/assessment.md), src/runtime/aggregate_integer.hpp:112-149, [include/crown/frontend/aggregate.hpp](../../../../../include/crown/frontend/aggregate.hpp), [tests/unit/aggregate_runtime_test.cpp](../../../../../tests/unit/aggregate_runtime_test.cpp), [tests/support/index_allocation.hpp](../../../../../tests/support/index_allocation.hpp), [tests/support/weighted_fixture.hpp](../../../../../tests/support/weighted_fixture.hpp), [docs/aggregate_batches.md](../../../../aggregate_batches.md), [build/verification/aggregate-batch-acceptance-v1/findings.json](../../../../../build/verification/aggregate-batch-acceptance-v1/findings.json) |

## B0033

[Lines 475–478](../../../../../tests/unit/aggregate_runtime_test.cpp#L475); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L475-L478:sha256:9eec509f0d312a594f5c1e4fbb41d2b2bc8791b8c4451f2d4c011462af07d0de
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Explain the adjacent source contract: Each signed contribution exceeds bigint here, while the consolidated final sum is zero. The prepared batch checks the final sum; a single-row update and an unbalanced final batch must refuse without changing committed state. |
| inputs / outputs | Human-readable source note in; no executable output or checked receipt. |
| invariants | This comment states context or a limitation. It does not itself enforce or prove the described behavior; use the adjacent implementation and its scoped contract. |
| ownership | Source text only; no object or resource lifetime is created. |
| failure | No runtime failure path in this comment; source encoding/comment syntax still belongs to compilation. |
| cost | No runtime operations from the comment. Any work described in the note belongs to the adjacent operation. |
| Design | [tests/unit/aggregate_runtime_test.cpp](../../../../../tests/unit/aggregate_runtime_test.cpp), [docs/aggregates.md](../../../../aggregates.md), [docs/code_review.md](../../../../code_review.md) |

## B0034

[Lines 479–521](../../../../../tests/unit/aggregate_runtime_test.cpp#L479); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void varying_integer_batches()
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Check real varying integer arithmetic, cast bounds and NULL without changing raw grouping. |
| inputs / outputs | Opposite INT32_MAX values each weighted 4294967299; captured/uncaptured batches; inclusive min/max, NULL, outside bounds, nested COUNT and AVG-only wide numerator. |
| invariants | Each isolated signed SUM contribution exceeds bigint but the final balanced sum is zero. Final-only batch succeeds while single/unbalanced updates refuse. Raw SUM remains numeric; AVG has no SUM(bigint-result) cap. |
| ownership | Owning fixture rows feed borrowed cell arrays; returned snapshots/events retain tuples. |
| failure | aggregate_overflow leaves committed sequence/results; explicit invariants inspect the standalone owner. |
| cost | Finite compressed-weight controls with no expansion; no timing claim. |
| Design | [include/crown/runtime/aggregate.hpp](../../../../../include/crown/runtime/aggregate.hpp), [src/runtime/aggregate_detail.hpp](../../../../../src/runtime/aggregate_detail.hpp), [docs/aggregate_batches.md](../../../../aggregate_batches.md) |

## B0035

[Lines 522–524](../../../../../tests/unit/aggregate_runtime_test.cpp#L522); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L522-L524:sha256:f61cacd661fa82f2358bb1b86d56cc97d8ff33937f5e1855d4900f2e5f95c5c2
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Explain the adjacent source contract: Repeated/nested casts add one checkpoint per guarded column, no per-update allocation. Identical final measure widths make raw/checked work comparable. |
| inputs / outputs | Human-readable source note in; no executable output or checked receipt. |
| invariants | This comment states context or a limitation. It does not itself enforce or prove the described behavior; use the adjacent implementation and its scoped contract. |
| ownership | Source text only; no object or resource lifetime is created. |
| failure | No runtime failure path in this comment; source encoding/comment syntax still belongs to compilation. |
| cost | No runtime operations from the comment. Any work described in the note belongs to the adjacent operation. |
| Design | [tests/unit/aggregate_runtime_test.cpp](../../../../../tests/unit/aggregate_runtime_test.cpp), [docs/aggregates.md](../../../../aggregates.md), [docs/code_review.md](../../../../code_review.md) |

## B0036

[Lines 525–549](../../../../../tests/unit/aggregate_runtime_test.cpp#L525); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void integer_guard_work()
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Measure guard checkpoints and existing-row allocation behavior for two distinct columns. |
| inputs / outputs | Matched final-measure raw/checked queries; warmed row update under deny-new; exact and one-under selected work. |
| invariants | Repeated/nested appearances add exactly two work units, one per guarded column; result values and measure work agree. |
| ownership | Each runtime owns its program/state; incoming nullable row is synchronous. |
| failure | Unexpected allocation under deny-zero or work/state mismatch fails; aggregate_work_limit preserves empty baseline. |
| cost | Covered C++ new count is zero for this warmed uncaptured update; selected-work evidence, not CPU/all-allocator proof. |
| Design | [src/runtime/aggregate_detail.hpp](../../../../../src/runtime/aggregate_detail.hpp), [tests/support/index_allocation.hpp](../../../../../tests/support/index_allocation.hpp), [docs/sql_aggregate_runtime.md](../../../../sql_aggregate_runtime.md) |

## B0038

[Lines 551–627](../../../../../tests/unit/aggregate_runtime_test.cpp#L551); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void batch_faults_and_work() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Exercise a bounded fixture’s selected-work boundary, observed allocation-fault/retry sites, receiving cap, and compiler-account separation. |
| inputs / outputs | Three grouped logical rows with long strings/NULL calibrate exact/one-under work, C++ replacement-new sites, peak receiver bytes, then replay work/fault/cap boundaries. |
| invariants | Exact work succeeds, one-under fails without sequence/value/current-charge change. Each observed s04_alloc site is compared with receiver successful-allocation delta; injected failure preserves state/charge and same-owner retry commits. Compiler account counters remain unchanged. |
| ownership | Fresh 32 MiB receiver funds runtime/preparation; AggregateProgram metadata uses separate source account. Controller-only check waits until result/runtime owners release. |
| failure | Fault seam injects std::bad_alloc at observed C++ replacement-new positions; receiver test expects MemoryFault::limit. It does not inject direct malloc/syscalls or prove all allocator paths. |
| cost | Finite &lt;256 observed sites for this fixture with explicit snapshots, account statistics and invariants; not a latency, zero-heap, or exhaustive failure proof. |
| Design | [build/verification/w06-aggregate-batch-design-v1/design.md](../../../../../build/verification/w06-aggregate-batch-design-v1/design.md), [docs/aggregates.md](../../../../aggregates.md), Refactor.md:1325-1327, [build/verification/w06-contract-assessment-v1/assessment.md](../../../../../build/verification/w06-contract-assessment-v1/assessment.md), [include/crown/resource/allocator.hpp](../../../../../include/crown/resource/allocator.hpp), [include/crown/resource/ownership.hpp](../../../../../include/crown/resource/ownership.hpp), [include/crown/resource/owner_allocator.hpp](../../../../../include/crown/resource/owner_allocator.hpp), [tests/unit/aggregate_runtime_test.cpp](../../../../../tests/unit/aggregate_runtime_test.cpp), [tests/support/index_allocation.hpp](../../../../../tests/support/index_allocation.hpp), [tests/support/weighted_fixture.hpp](../../../../../tests/support/weighted_fixture.hpp), [docs/aggregate_batches.md](../../../../aggregate_batches.md), [build/verification/aggregate-batch-acceptance-v1/findings.json](../../../../../build/verification/aggregate-batch-acceptance-v1/findings.json) |

## B0040

[Lines 629–658](../../../../../tests/unit/aggregate_runtime_test.cpp#L629); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void batch_owner_lifetimes() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Verify input freezing and token/runtime/result ownership across caller mutation, facade move/death, commit, and abandoned rollback. |
| inputs / outputs | Prepare with long string, overwrite caller Row, move/destroy facade, inspect preview and commit result; then destroy another facade with live token and rollback it. |
| invariants | Prepared key/output no longer borrows Row string. Token retains runtime Data/account while facade is gone; committed result retains program/output after token reset; abandoned rollback returns receiver to controller-only after all owners release. |
| ownership | Row/Cell borrow ends at prepare return; token owns proposals/shared owner; result owns program/Tuples. Controller-only assertion occurs after all results and owners reset. |
| failure | Wrong preview/source/output, leaked account payload, or replacement-new request under denial fails. No system-call allocator seam is installed. |
| cost | Small lifetime paths with explicit output exports and account diagnostics; no hot-path timing claim. |
| Design | [build/verification/w06-aggregate-batch-design-v1/design.md](../../../../../build/verification/w06-aggregate-batch-design-v1/design.md), [docs/aggregates.md](../../../../aggregates.md), Refactor.md:1325-1327, [build/verification/w06-contract-assessment-v1/assessment.md](../../../../../build/verification/w06-contract-assessment-v1/assessment.md), [include/crown/resource/allocator.hpp](../../../../../include/crown/resource/allocator.hpp), [include/crown/resource/ownership.hpp](../../../../../include/crown/resource/ownership.hpp), [include/crown/resource/owner_allocator.hpp](../../../../../include/crown/resource/owner_allocator.hpp), [tests/unit/aggregate_runtime_test.cpp](../../../../../tests/unit/aggregate_runtime_test.cpp), [tests/support/index_allocation.hpp](../../../../../tests/support/index_allocation.hpp), [tests/support/weighted_fixture.hpp](../../../../../tests/support/weighted_fixture.hpp), [docs/aggregate_batches.md](../../../../aggregate_batches.md), [build/verification/aggregate-batch-acceptance-v1/findings.json](../../../../../build/verification/aggregate-batch-acceptance-v1/findings.json) |

## B0042

[Lines 660–666](../../../../../tests/unit/aggregate_runtime_test.cpp#L660); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void run()
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Run the four aggregate-local batch fixtures before the preserved W04 semantic/resource cohort. |
| inputs / outputs | Runs group/empty, SUM/admission, allocation/work and ownership batch controls, then all legacy semantics/arithmetic/work/fault/snapshot/receiver/weighted tests. |
| invariants | Terminal success occurs only after every assertion. New cases test caller-fed logical API, not physical-source/native/session/recovery composition. |
| ownership | Each test owns local Rows/tokens/accounts/results; run retains no aggregate state. |
| failure | First exception stops cohort and reaches main; no production retry/recovery coordinator. |
| cost | Sum of deterministic cases/fault sweeps; no benchmark timing. |
| Design | [docs/aggregates.md](../../../../aggregates.md), [Refactor.md § W04 — Implement COUNT, SUM and AVG](../../../../../Refactor.md) |

## B0043

[Lines 667–667](../../../../../tests/unit/aggregate_runtime_test.cpp#L667); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L667-L667:sha256:c7bfe2f3de133d78a2bc8bb1c4a08450563986ee8254facee698e1dcc57e8162
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Close the recorded declaration scopes in aggregate_runtime_test.cpp: namespace (anonymous). |
| inputs / outputs | Preceding namespace, type or initializer declarations in; completed lexical boundary out. |
| invariants | Brace-opening context is recorded in root-scope-context-v1.json. These are declaration/initializer boundaries, not an independent update, validation or recovery operation. |
| ownership | Enclosing objects and borrowed fields keep their declared ownership. This punctuation creates no new owner. |
| failure | Malformed scope syntax is a compile error. Any initializer/constructor failure belongs to the enclosing object declaration. |
| cost | No separate loop, guard or engine call is introduced by the delimiter; enclosing initialization and object lifetime still have their actual costs. |
| Design | [tests/unit/aggregate_runtime_test.cpp](../../../../../tests/unit/aggregate_runtime_test.cpp), [docs/aggregates.md](../../../../aggregates.md), [docs/code_review.md](../../../../code_review.md) |

## B0044

[Lines 668–668](../../../../../tests/unit/aggregate_runtime_test.cpp#L668); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
int main()
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Report one readable terminal native test result to CTest. |
| inputs / outputs | No arguments; returns 0 after run, 1 with stderr diagnostic on standard exception. |
| invariants | A failed check never emits process success. |
| ownership | Test scope cleanup runs through standard exception unwinding. |
| failure | One outer test exception handler; no retry or recovery policy is installed into production. |
| cost | Constant dispatch plus the complete test cohort. |
| Design | [docs/aggregates.md](../../../../aggregates.md), [Refactor.md § W04 — Implement COUNT, SUM and AVG](../../../../../Refactor.md) |
