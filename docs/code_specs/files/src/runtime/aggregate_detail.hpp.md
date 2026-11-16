# `src/runtime/aggregate_detail.hpp` — block usage map

[Source](../../../../../src/runtime/aggregate_detail.hpp) · [Source index](../../../README.md) · [Subsystem contracts](../../../subsystem_contracts.md) · [Reviewed primitives](../../../primitives.md)

Share exact aggregate validation, arithmetic and rendering between runtimes.

Snapshot SHA-256: `d019b7078427ffa1b4c9e6c123bd3dea085678df7114e5447590443e45ea6b6b`. 191 lines partitioned into 23 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [support](../../../subsystem_contracts.md#support). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/support_invariants.md](../../../../support_invariants.md), [docs/runtime_support.md](../../../../runtime_support.md), [docs/prepared_epochs.md](../../../../prepared_epochs.md), [docs/result_cursors.md](../../../../result_cursors.md), [docs/epoch_views.md](../../../../epoch_views.md), [docs/code_review.md](../../../../code_review.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–17](../../../../../src/runtime/aggregate_detail.hpp#L1) | Imports dependencies; guards repeated header inclusion; declares namespace scope; declares aliases; declares types or opens a type body; declares values/defaults or compile-time conditions. | source comment (unverified): // Private shared W04 group arithmetic. This is not an input admission port. · [reviewed contract](#b0001) |
| [B0002 · 18–19](../../../../../src/runtime/aggregate_detail.hpp#L18) | Callable definition: template&lt;class T&gt; resource::MemoryAllocator&lt;T&gt; allocator(const resource::MemoryAccount& account, resource::MemoryPurpose purpose) | calls ; returns resource::MemoryAllocator&lt;T&gt;(account, purpose) · [reviewed contract](#b0002) |
| [B0003 · 20–20](../../../../../src/runtime/aggregate_detail.hpp#L20) | Callable definition: \[\[noreturn\]\] inline void fail(const char* code, const char* message) | calls Error · [reviewed contract](#b0003) |
| [B0004 · 21–23](../../../../../src/runtime/aggregate_detail.hpp#L21) | Explanatory comments or spacing. | source comment (unverified): // Keys are immutable owned tuples; temporary probes borrow the per-call cells. · [reviewed contract](#b0004) |
| [B0005 · 24–32](../../../../../src/runtime/aggregate_detail.hpp#L24) | Type/record definition: struct Less | returns std::lexicographical_compare(a.begin(), a.end(), b.begin(), b.end()); compare(a.view(), b.view()); source comment (unverified): // Keys are immutable owned tuples; temporary probes borrow the per-call cells. · [reviewed contract](#b0005) |
| [B0006 · 33–36](../../../../../src/runtime/aggregate_detail.hpp#L33) | Type/record definition: struct State |  · [reviewed contract](#b0006) |
| [B0007 · 37–48](../../../../../src/runtime/aggregate_detail.hpp#L37) | Type/record definition: struct Group | source comment (unverified): // A touched proposal uses the exact persistent vector allocator so commit · [reviewed contract](#b0007) |
| [B0008 · 49–57](../../../../../src/runtime/aggregate_detail.hpp#L49) | Type/record definition: struct Budget |  · [reviewed contract](#b0008) |
| [B0009 · 58–60](../../../../../src/runtime/aggregate_detail.hpp#L58) | Explanatory comments or spacing. | source comment (unverified): // The temporary map uses the destination allocator. Extracted nodes can then · [reviewed contract](#b0009) |
| [B0010 · 61–66](../../../../../src/runtime/aggregate_detail.hpp#L61) | Callable definition: template&lt;class Map, class Value&gt; typename Map::node_type node_for(Map& target, Tuple key, Value value) | calls prepared, key_comp, get_allocator, emplace; returns prepared.extract(item); growth emplace; source comment (unverified): // The temporary map uses the destination allocator. Extracted nodes can then · [reviewed contract](#b0010) |
| [B0011 · 67–72](../../../../../src/runtime/aggregate_detail.hpp#L67) | Callable definition: inline bool decimal_fits(const storage::InlineDecimal& value, DecimalSpec type) noexcept | calls parts, size; returns true; parts.scale &lt;= type.scale && integral &lt;= type.precision - type.scale · [reviewed contract](#b0011) |
| [B0012 · 73–73](../../../../../src/runtime/aggregate_detail.hpp#L73) | Explanatory comments or spacing. |  |
| [B0013 · 74–80](../../../../../src/runtime/aggregate_detail.hpp#L74) | Type/record definition: struct Borrows |  · [reviewed contract](#b0013) |
| [B0014 · 81–81](../../../../../src/runtime/aggregate_detail.hpp#L81) | Explanatory comments or spacing. |  |
| [B0015 · 82–111](../../../../../src/runtime/aggregate_detail.hpp#L82) | Callable definition: inline void validate(const frontend::AggregateProgram& program, std::span&lt;const Cell&gt; values, Budget& budget) | calls input_types, size, fail, take; 1 loop sites · [reviewed contract](#b0015) |
| [B0016 · 112–128](../../../../../src/runtime/aggregate_detail.hpp#L112) | Callable definition: inline void project(const frontend::AggregateProgram& program, std::span&lt;const Cell&gt; values, std::span&lt;Cell&gt; key, Budget& budget) | calls checked_int32_columns, take, fail, group_columns; 2 loop sites; source comment (unverified): // Validate contributing integer casts once per distinct input column. The · [reviewed contract](#b0016) |
| [B0017 · 129–132](../../../../../src/runtime/aggregate_detail.hpp#L129) | Callable definition: inline const Cell& argument(const frontend::AggregateMeasure& measure, std::span&lt;const Cell&gt; values) | calls ; returns values\[column-&gt;value\]; std::get&lt;Cell&gt;(measure.argument) · [reviewed contract](#b0017) |
| [B0018 · 133–134](../../../../../src/runtime/aggregate_detail.hpp#L133) | Explanatory comments or spacing. | source comment (unverified): // The count and numerator change together from the same non-NULL argument. · [reviewed contract](#b0018) |
| [B0019 · 135–152](../../../../../src/runtime/aggregate_detail.hpp#L135) | Callable definition: template&lt;bool CheckInt64 = true&gt; inline void adjust(const frontend::AggregateProgram& program, std::span&lt;State&gt; states, std::span… | calls measures, size, take, argument; guard if (erase) { assert(amount &lt;= state.count); state.count -= amount; }; 1 loop sites; source comment (unverified): // The count and numerator change together from the same non-NULL argument. · [reviewed contract](#b0019) |
| [B0020 · 153–179](../../../../../src/runtime/aggregate_detail.hpp#L153) | Callable definition: inline Tuple render(const resource::MemoryAccount& account, const frontend::AggregateProgram& program, std::span&lt;Cell&gt; output, st… | calls outputs, size, take, reset; returns Tuple::copy_of(account, output, resource::MemoryPurpose::output_buffer); growth copy_of; 1 loop sites · [reviewed contract](#b0020) |
| [B0021 · 180–182](../../../../../src/runtime/aggregate_detail.hpp#L180) | Explanatory comments or spacing. | source comment (unverified): // Final-only SUM(integer) check, shared by genuine prepared contributors and · [reviewed contract](#b0021) |
| [B0022 · 183–190](../../../../../src/runtime/aggregate_detail.hpp#L183) | Callable definition: inline void check_sums(const frontend::AggregateProgram& program, std::span&lt;const State&gt; states, Budget& budget) | calls measures, size, take, fits_int64; 1 loop sites; source comment (unverified): // Final-only SUM(integer) check, shared by genuine prepared contributors and · [reviewed contract](#b0022) |
| [B0023 · 191–191](../../../../../src/runtime/aggregate_detail.hpp#L191) | Closes surrounding scope/type. | source comment (unverified): // namespace crown::runtime::aggregate::detail · [reviewed contract](#b0023) |

## B0001

[Lines 1–17](../../../../../src/runtime/aggregate_detail.hpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
#pragma once // Private shared W04 group arithmetic. This is not an input admission port.
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Declare a private shared W04 helper namespace and explicitly exclude a public/native contribution input port. |
| inputs / outputs | Includes aggregate type/resource and exact integer helpers; exposes inline utilities only inside aggregate::detail. |
| invariants | Factory programs authenticate scalar/count preconditions; owners supply reusable scratch and receiver Budget. No caller can pass arbitrary logical facts into the composed runtime. |
| ownership | Header definitions own no persistent runtime state; allocator helpers borrow existing MemoryAccount handles. |
| failure | Type/ODR/compile failures are build failures; validation/arithmetic errors occur only when concrete helper calls run. |
| cost | Inline definition and includes have no per-operation cost beyond selected helpers. |
| Design | [build/verification/w06-sql-aggregate-runtime-design-v1/design.md](../../../../../build/verification/w06-sql-aggregate-runtime-design-v1/design.md), [build/verification/w06-sql-aggregate-runtime-design-v1/cost-and-lifetime.md](../../../../../build/verification/w06-sql-aggregate-runtime-design-v1/cost-and-lifetime.md), [build/verification/w06-sql-aggregate-runtime-design-v1/reference-plan.md](../../../../../build/verification/w06-sql-aggregate-runtime-design-v1/reference-plan.md), [src/runtime/aggregate_detail.hpp](../../../../../src/runtime/aggregate_detail.hpp), [docs/sql_aggregate_runtime.md](../../../../sql_aggregate_runtime.md), [docs/aggregates.md](../../../../aggregates.md), [docs/sql_rows_batches.md](../../../../sql_rows_batches.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0002

[Lines 18–19](../../../../../src/runtime/aggregate_detail.hpp#L18); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
template<class T> resource::MemoryAllocator<T> allocator(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Construct a standard-container allocator over the receiving grant and requested allocation purpose. |
| inputs / outputs | A live MemoryAccount and non-control MemoryPurpose enter; an allocator retaining that exact authority leaves. |
| invariants | The adapter does not create a fresh account, limit, attribution, or nested-member allocator. |
| ownership | The allocator shares the controller; containers own and release allocations obtained from it. |
| failure | MemoryAllocator validates the account/purpose and propagates contract failure. |
| cost | Fixed validation and reference retention, with no payload allocation. |
| Design | [docs/aggregates.md](../../../../aggregates.md), [docs/query_memory.md](../../../../query_memory.md), [include/crown/resource/allocator.hpp](../../../../../include/crown/resource/allocator.hpp), [src/runtime/aggregate_detail.hpp](../../../../../src/runtime/aggregate_detail.hpp), [docs/aggregate_batches.md](../../../../aggregate_batches.md), [docs/sql_aggregate_runtime.md](../../../../sql_aggregate_runtime.md) |

## B0003

[Lines 20–20](../../../../../src/runtime/aggregate_detail.hpp#L20); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
[[noreturn]] inline void fail(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Raise one aggregate boundary error with the supplied stable code and human explanation. |
| inputs / outputs | Two literal-compatible C strings enter; Error construction throws rather than returning. |
| invariants | The helper performs no query-state mutation, recovery, retry, or exception translation. |
| ownership | Error owns any diagnostic strings it constructs; successful update paths never call this helper. |
| failure | Error or diagnostic-allocation failure propagates to the caller. |
| cost | Failure-only diagnostic construction; no successful-path allocation from declaring the helper. |
| Design | [include/crown/api/error.hpp](../../../../../include/crown/api/error.hpp), [docs/aggregates.md](../../../../aggregates.md), [src/runtime/aggregate_detail.hpp](../../../../../src/runtime/aggregate_detail.hpp), [docs/aggregate_batches.md](../../../../aggregate_batches.md), [docs/sql_aggregate_runtime.md](../../../../sql_aggregate_runtime.md) |

## B0004

[Lines 21–23](../../../../../src/runtime/aggregate_detail.hpp#L21); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
// Keys are immutable owned tuples;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Explain why owned keys and borrowed probes can share one ordering without copying temporary lookup rows. |
| inputs / outputs | This comment applies to Less immediately below; NULL precedes present scalar values and strings compare by exact bytes. |
| invariants | The noexcept comparison premise requires valid private Tuple handles, live probe borrows, and the compiler-fixed schema. |
| ownership | Map keys own their tuple payloads; probe spans do not extend caller lifetimes. |
| failure | This comment installs no validation or catch mechanism. |
| cost | It documents variable-width comparison cost, not a constant-time key guarantee. |
| Design | [docs/aggregates.md](../../../../aggregates.md), [Refactor.md §11.9 W04](../../../../../Refactor.md), [src/runtime/aggregate_detail.hpp](../../../../../src/runtime/aggregate_detail.hpp), [docs/aggregate_batches.md](../../../../aggregate_batches.md), [docs/sql_aggregate_runtime.md](../../../../sql_aggregate_runtime.md) |

## B0005

[Lines 24–32](../../../../../src/runtime/aggregate_detail.hpp#L24); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct Less {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Supply transparent lexicographic ordering for retained nullable tuples and borrowed lookup spans. |
| inputs / outputs | Tuple/Tuple, Tuple/span, or span/Tuple enters; a strict-less Boolean leaves. |
| invariants | Equivalent fixed-schema rows compare equal regardless of allocation identity; valid stored tuple handles make the noexcept overloads safe. |
| ownership | Comparison only borrows cells and string bytes; it neither retains nor copies either operand. |
| failure | The wrappers promise noexcept under the private valid-handle contract; invalid private handles are invariant violations. |
| cost | O(common compared fields plus compared string bytes); map lookup multiplies this by tree comparisons. No allocation. |
| Design | [docs/aggregates.md](../../../../aggregates.md), [Refactor.md §11.9 W04](../../../../../Refactor.md), [include/crown/storage/accounted_row.hpp](../../../../../include/crown/storage/accounted_row.hpp), [src/runtime/aggregate_detail.hpp](../../../../../src/runtime/aggregate_detail.hpp), [docs/aggregate_batches.md](../../../../aggregate_batches.md), [docs/sql_aggregate_runtime.md](../../../../sql_aggregate_runtime.md) |

```text
static bool compare(std::span<const Cell> a,
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Compare two nullable-cell sequences without forming owning rows. |
| inputs / outputs | Two live cell spans enter; std::lexicographical_compare returns the row ordering. |
| invariants | Optional NULL ordering and the inline scalar variant ordering are used consistently for stored keys and probes. |
| ownership | Both spans and all string bytes are borrowed for this synchronous comparison. |
| failure | Comparison is noexcept for the supported inline scalar alternatives. |
| cost | Linear in the common compared prefix and string bytes; no heap work. |
| Design | [include/crown/storage/accounted_row.hpp](../../../../../include/crown/storage/accounted_row.hpp), [docs/aggregates.md](../../../../aggregates.md), [src/runtime/aggregate_detail.hpp](../../../../../src/runtime/aggregate_detail.hpp), [docs/aggregate_batches.md](../../../../aggregate_batches.md), [docs/sql_aggregate_runtime.md](../../../../sql_aggregate_runtime.md) |

```text
bool operator()(const Tuple& a, const Tuple& b)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Adapt two retained tuples to the one cell-span ordering. |
| inputs / outputs | The indicated operands enter; their span comparison leaves as bool. |
| invariants | All Tuple operands are valid factory-owned handles; span operands and their strings remain live. |
| ownership | view() borrows the tuple payload; this overload acquires no new payload. |
| failure | No error recovery exists in this noexcept private comparator. |
| cost | Fixed adapter work plus the actual prefix/byte comparison; no allocation. |
| Design | [docs/aggregates.md](../../../../aggregates.md), [Refactor.md §11.9 W04](../../../../../Refactor.md), [src/runtime/aggregate_detail.hpp](../../../../../src/runtime/aggregate_detail.hpp), [docs/aggregate_batches.md](../../../../aggregate_batches.md), [docs/sql_aggregate_runtime.md](../../../../sql_aggregate_runtime.md) |

```text
bool operator()(const Tuple& a, std::span<const Cell> b)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Adapt a retained key and borrowed probe to the one cell-span ordering. |
| inputs / outputs | The indicated operands enter; their span comparison leaves as bool. |
| invariants | All Tuple operands are valid factory-owned handles; span operands and their strings remain live. |
| ownership | view() borrows the tuple payload; this overload acquires no new payload. |
| failure | No error recovery exists in this noexcept private comparator. |
| cost | Fixed adapter work plus the actual prefix/byte comparison; no allocation. |
| Design | [docs/aggregates.md](../../../../aggregates.md), [Refactor.md §11.9 W04](../../../../../Refactor.md), [src/runtime/aggregate_detail.hpp](../../../../../src/runtime/aggregate_detail.hpp), [docs/aggregate_batches.md](../../../../aggregate_batches.md), [docs/sql_aggregate_runtime.md](../../../../sql_aggregate_runtime.md) |

```text
bool operator()(std::span<const Cell> a, const Tuple& b)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Adapt a borrowed probe and retained key to the one cell-span ordering. |
| inputs / outputs | The indicated operands enter; their span comparison leaves as bool. |
| invariants | All Tuple operands are valid factory-owned handles; span operands and their strings remain live. |
| ownership | view() borrows the tuple payload; this overload acquires no new payload. |
| failure | No error recovery exists in this noexcept private comparator. |
| cost | Fixed adapter work plus the actual prefix/byte comparison; no allocation. |
| Design | [docs/aggregates.md](../../../../aggregates.md), [Refactor.md §11.9 W04](../../../../../Refactor.md), [src/runtime/aggregate_detail.hpp](../../../../../src/runtime/aggregate_detail.hpp), [docs/aggregate_batches.md](../../../../aggregate_batches.md), [docs/sql_aggregate_runtime.md](../../../../sql_aggregate_runtime.md) |

## B0006

[Lines 33–36](../../../../../src/runtime/aggregate_detail.hpp#L33); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct State {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Store one resolved argument's non-NULL count and exact integer numerator. |
| inputs / outputs | Zero-initialized count/sum state enters each new group and proposed scratch row. |
| invariants | Count reflects exactly that argument's non-NULL multiplicity; sum is meaningful only when its descriptor requests it. Group existence is separate. |
| ownership | Both fields are inline values with no owned child allocation or borrowed row data. |
| failure | Plain state construction/copy cannot throw; public group admission supplies its arithmetic bounds. |
| cost | Fixed-size storage per distinct measure and fixed-size copy, independent of multiplicity. |
| Design | [docs/aggregates.md](../../../../aggregates.md), [src/runtime/aggregate_integer.hpp](../../../../../src/runtime/aggregate_integer.hpp), [src/runtime/aggregate_detail.hpp](../../../../../src/runtime/aggregate_detail.hpp), [docs/aggregate_batches.md](../../../../aggregate_batches.md), [docs/sql_aggregate_runtime.md](../../../../sql_aggregate_runtime.md) |

## B0007

[Lines 37–48](../../../../../src/runtime/aggregate_detail.hpp#L37); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct Group {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Retain total group rows and measure statistics, and copy one touched group into allocator-compatible private proposal state. |
| inputs / outputs | Fresh construction takes account/measure width/purpose; proposal copy takes source Group and copies its rows and State vector. |
| invariants | A live all-NULL/cancelling group remains distinct from absence. Copied proposal vector uses same account and support_metadata allocator as persistent state so publication can swap legally. |
| ownership | Group owns State vector through receiving account; each State remains inline. |
| failure | Fresh or copied vector allocation can fail during private preparation before group publication. |
| cost | Fresh initialization and touched-group copying visit O(measures) State fields; nonzero width funds one compatible vector buffer, while zero width requires no field buffer. Direct copy avoids zero-then-copy and never visits unrelated groups. |
| Design | [docs/aggregates.md](../../../../aggregates.md), [docs/query_memory.md](../../../../query_memory.md), [include/crown/resource/allocator.hpp](../../../../../include/crown/resource/allocator.hpp), [src/runtime/aggregate_detail.hpp](../../../../../src/runtime/aggregate_detail.hpp), [docs/aggregate_batches.md](../../../../aggregate_batches.md), [docs/sql_aggregate_runtime.md](../../../../sql_aggregate_runtime.md) |

## B0008

[Lines 49–57](../../../../../src/runtime/aggregate_detail.hpp#L49); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct Budget {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Track selected logical operation charges and observable per-operation counters. |
| inputs / outputs | An optional work cap and zero Metrics initialize the local object; take() accumulates admitted work. |
| invariants | metrics.work never exceeds uint64 or a present cap. It does not measure every tree comparison, byte operation, or elapsed CPU time. |
| ownership | Budget is call-local scalar state; it owns no allocation or persistent query balance. |
| failure | Insufficient work is rejected by take before incrementing its work counter. |
| cost | Fixed-size local storage; individual selected charges are O(1). |
| Design | [docs/aggregates.md](../../../../aggregates.md), [Refactor.md §11.9 W04](../../../../../Refactor.md), [src/runtime/aggregate_detail.hpp](../../../../../src/runtime/aggregate_detail.hpp), [docs/aggregate_batches.md](../../../../aggregate_batches.md), [docs/sql_aggregate_runtime.md](../../../../sql_aggregate_runtime.md) |

```text
void take(std::uint64_t amount = 1)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Admit one selected logical charge without overflowing the operation's work counter. |
| inputs / outputs | A uint64 amount enters; metrics.work increases exactly by amount on success. |
| invariants | Existing metrics.work is at most a present limit, so the subtraction-based remaining-cap test is safe. |
| ownership | Only this local Budget changes; no committed row, group, or epoch is touched. |
| failure | aggregate_work_limit is thrown before the increment on exhaustion or uint64 overflow. |
| cost | Two bounded checks and one addition, with no allocation on success. |
| Design | [docs/aggregates.md](../../../../aggregates.md), [Refactor.md §11.9 W04](../../../../../Refactor.md), [src/runtime/aggregate_detail.hpp](../../../../../src/runtime/aggregate_detail.hpp), [docs/aggregate_batches.md](../../../../aggregate_batches.md), [docs/sql_aggregate_runtime.md](../../../../sql_aggregate_runtime.md) |

## B0009

[Lines 58–60](../../../../../src/runtime/aggregate_detail.hpp#L58); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
// The temporary map uses the destination allocator.
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | State the allocation and allocator-equality reason for preparing map nodes before publication. |
| inputs / outputs | The comment applies to node_for; the returned extracted node will be inserted into its original target allocator domain. |
| invariants | node_for copies the exact target comparator and allocator, satisfying same-allocator node transfer. |
| ownership | Private node handles own prepared nodes until inserted or destroyed during unwinding. |
| failure | Preparation may throw while committed maps remain unchanged. |
| cost | A temporary map header is stack state; preparation performs one node allocation rather than a whole-map clone. |
| Design | [docs/aggregates.md](../../../../aggregates.md), [docs/query_memory.md](../../../../query_memory.md), [include/crown/resource/allocator.hpp](../../../../../include/crown/resource/allocator.hpp), [src/runtime/aggregate_detail.hpp](../../../../../src/runtime/aggregate_detail.hpp), [docs/aggregate_batches.md](../../../../aggregate_batches.md), [docs/sql_aggregate_runtime.md](../../../../sql_aggregate_runtime.md) |

## B0010

[Lines 61–66](../../../../../src/runtime/aggregate_detail.hpp#L61); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
typename Map::node_type node_for(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Fund and construct exactly one detached map node before any committed-map mutation. |
| inputs / outputs | A target map, owned Tuple key, and mapped value enter; an extracted node using the target allocator leaves. |
| invariants | The temporary map has one entry and the destination's exact comparator/account/purpose/attribution. |
| ownership | Arguments move into the private node; extraction transfers its ownership into the returned node handle. |
| failure | Allocation or construction failure destroys private arguments/map storage and leaves target untouched. |
| cost | One node allocation and fixed single-entry map/extraction work; final insertion still has its real tree-search cost. |
| Design | [docs/aggregates.md](../../../../aggregates.md), [docs/query_memory.md](../../../../query_memory.md), [include/crown/resource/allocator.hpp](../../../../../include/crown/resource/allocator.hpp), [src/runtime/aggregate_detail.hpp](../../../../../src/runtime/aggregate_detail.hpp), [docs/aggregate_batches.md](../../../../aggregate_batches.md), [docs/sql_aggregate_runtime.md](../../../../sql_aggregate_runtime.md) |

## B0011

[Lines 67–72](../../../../../src/runtime/aggregate_detail.hpp#L67); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
bool decimal_fits(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Check exact representability of an inline decimal against its already validated input precision/scale. |
| inputs / outputs | An InlineDecimal and valid DecimalSpec (scale &lt;= precision) enter; exact range/scale admission leaves as bool. |
| invariants | Canonical zero fits any valid spec. Other values require no extra fractional digits and enough integral capacity; this is not rounding. |
| ownership | parts() borrows digits from the live inline argument only for this call. |
| failure | The noexcept predicate returns false rather than constructing an admission error. |
| cost | Fixed metadata/length comparisons with no decimal text allocation. |
| Design | [docs/aggregates.md](../../../../aggregates.md), [include/crown/storage/accounted_row.hpp](../../../../../include/crown/storage/accounted_row.hpp), [include/crown/frontend/bind.hpp](../../../../../include/crown/frontend/bind.hpp), [src/runtime/aggregate_detail.hpp](../../../../../src/runtime/aggregate_detail.hpp), [docs/aggregate_batches.md](../../../../aggregate_batches.md), [docs/sql_aggregate_runtime.md](../../../../sql_aggregate_runtime.md) |

## B0013

[Lines 74–80](../../../../../src/runtime/aggregate_detail.hpp#L74); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct Borrows {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Clear only the cell arrays actually used to borrow data in this call scope. |
| inputs / outputs | One or two writable Cell spans enter; destruction resets their cells to NULL. |
| invariants | Spans refer to live component scratch. apply clears input/key; render clears output; full diagnostics clear projected keys. |
| ownership | The guard owns no payload or account, and retains no strings after destruction. |
| failure | The destructor is noexcept; it performs no state rollback, allocation, or error formatting. |
| cost | O(sum of supplied span lengths); capture-disabled updates and capture-enabled no-ops do not scan output width. |
| Design | [docs/aggregates.md](../../../../aggregates.md), [Refactor.md §11.9 W04](../../../../../Refactor.md), [src/runtime/aggregate_detail.hpp](../../../../../src/runtime/aggregate_detail.hpp), [docs/aggregate_batches.md](../../../../aggregate_batches.md), [docs/sql_aggregate_runtime.md](../../../../sql_aggregate_runtime.md) |

```text
~Borrows() noexcept
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Drop borrowed scalar/string views at scope exit, including exception unwinding. |
| inputs / outputs | The guard's two spans are reset with empty Cell values; no return value. |
| invariants | Cell reset is nonthrowing and owns no child memory; arrays themselves remain allocated for reuse. |
| ownership | Only descriptor cells are cleared; borrowed source bytes are neither modified nor freed. |
| failure | Noexcept cleanup adds no catch/retry machinery. |
| cost | Linear in these two spans and zero heap allocations. |
| Design | [docs/aggregates.md](../../../../aggregates.md), [Refactor.md §11.9 W04](../../../../../Refactor.md), [src/runtime/aggregate_detail.hpp](../../../../../src/runtime/aggregate_detail.hpp), [docs/aggregate_batches.md](../../../../aggregate_batches.md), [docs/sql_aggregate_runtime.md](../../../../sql_aggregate_runtime.md) |

## B0015

[Lines 82–111](../../../../../src/runtime/aggregate_detail.hpp#L82); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
if (!values[i]) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Admit SQL NULL only for a declared nullable input column. |
| inputs / outputs | A missing Cell enters this branch; a nullable field continues without accessing a scalar alternative. |
| invariants | NULL is an optional-cell state outside classical core ScalarView, not a fabricated scalar value. |
| ownership | The branch retains no input owner or payload. |
| failure | A NULL in a non-null column throws invalid_aggregate_row before row lookup/publication. |
| cost | One fixed nullability test per NULL field. |
| Design | [docs/aggregates.md](../../../../aggregates.md), [Refactor.md §11.9 W04](../../../../../Refactor.md), [src/runtime/aggregate_detail.hpp](../../../../../src/runtime/aggregate_detail.hpp), [docs/aggregate_batches.md](../../../../aggregate_batches.md), [docs/sql_aggregate_runtime.md](../../../../sql_aggregate_runtime.md) |

```text
switch (types[i].kind) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Select the already bound scalar admission rule without reparsing SQL or interpreting expressions. |
| inputs / outputs | One present ScalarView and SqlType enter; valid reflects exact kind/range compatibility. |
| invariants | int32 uses an int64 cell restricted to its 32-bit domain; int64/string/bool/date use matching alternatives; decimal obeys its spec; unknown present values reject. |
| ownership | Alternative inspection only borrows the inline cell. |
| failure | A failed predicate later raises invalid_aggregate_row; no coercion or partial state mutation occurs. |
| cost | Fixed alternative checks per field; decimal check uses inline metadata. |
| Design | [docs/aggregates.md](../../../../aggregates.md), [Refactor.md §11.9 W04](../../../../../Refactor.md), [src/runtime/aggregate_detail.hpp](../../../../../src/runtime/aggregate_detail.hpp), [docs/aggregate_batches.md](../../../../aggregate_batches.md), [docs/sql_aggregate_runtime.md](../../../../sql_aggregate_runtime.md) |

```text
if (valid) { const auto bytes =
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Account for incoming string lengths in the selected logical operation budget. |
| inputs / outputs | A type-compatible string_view enters; its length is charged before input_bytes increases. |
| invariants | Work admission bounds the cumulative byte metric against uint64 overflow. String comparison and deep copying have separate real costs. |
| ownership | The view and its bytes remain borrowed, with no copied string. |
| failure | Work exhaustion throws before updating input_bytes or committed state. |
| cost | Constant-time size/charge bookkeeping; the logical byte amount is not measured CPU time. |
| Design | [docs/aggregates.md](../../../../aggregates.md), [Refactor.md §11.9 W04](../../../../../Refactor.md), [src/runtime/aggregate_detail.hpp](../../../../../src/runtime/aggregate_detail.hpp), [docs/aggregate_batches.md](../../../../aggregate_batches.md), [docs/sql_aggregate_runtime.md](../../../../sql_aggregate_runtime.md) |

## B0016

[Lines 112–128](../../../../../src/runtime/aggregate_detail.hpp#L112); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
inline void project(const frontend::AggregateProgram& program, std::span<const Cell> values,
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Check unconditional integer argument casts, then gather the complete raw grouping key into reusable borrowed scratch. |
| inputs / outputs | Genuine kernel, previously validated/decoded physical cells, key scratch and shared Budget; checks each guarded original column and copies group views. |
| invariants | Genuine metadata establishes valid positions/int64 storage. NULL passes; present guarded values must fit signed int32 even for COUNT or outer widening. Checks precede group mutation. The admitted expression family contains only unconditional columns/constants/casts. |
| ownership | Program, input and key are borrowed. Copied ScalarViews share input bytes; no Tuple or payload is allocated. Caller keeps inputs/program alive and uses its Borrows guard to clear scratch before source facts can be released. |
| failure | A guard budget can refuse before range evaluation; out-of-range raises aggregate_overflow. Existing standalone private proposals or composed child token unwind. Later key-copy budget failure leaves scratch to the caller Borrows guard. No publication/catch is added. |
| cost | U guard checkpoints plus one selected checkpoint/cell-view copy per group-key field, per projected logical row/native fact; NULL still spends its guard. Successful projection allocates no payload. U=0 pays the accessor/empty-loop check; an empty grouping key does not skip guards. |
| Design | [src/runtime/aggregate_detail.hpp](../../../../../src/runtime/aggregate_detail.hpp), [docs/sql_aggregate_runtime.md §State and lifetime](../../../../sql_aggregate_runtime.md), [docs/aggregate_batches.md](../../../../aggregate_batches.md), [docs/aggregates.md](../../../../aggregates.md), [build/verification/w06-sql-aggregate-runtime-design-v1/cost-and-lifetime.md](../../../../../build/verification/w06-sql-aggregate-runtime-design-v1/cost-and-lifetime.md) |

## B0017

[Lines 129–132](../../../../../src/runtime/aggregate_detail.hpp#L129); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
inline const Cell& argument(const frontend::AggregateMeasure& measure, std::span<const Cell> values) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Resolve one genuine compiled measure argument as a reference to an input cell or its immutable constant cell. |
| inputs / outputs | Borrowed AggregateMeasure and valid logical row span; returns const Cell& from values\[ColumnId\] or the measure-owned optional ScalarView, including NULL. |
| invariants | Factory metadata contains one of the two supported argument alternatives and any ColumnId is within the admitted input width. It does not interpret expressions, rebind SQL or manufacture a descriptor. |
| ownership | The returned reference borrows either caller row scratch or the genuine program constant. Caller must keep the corresponding row/program owner alive and consume it before scratch reset; no ownership transfer or new allocation occurs. |
| failure | Under valid factory/caller preconditions there is no ordinary failure. The std::get fallback requires the constant alternative; it is not a public malformed-descriptor validator or an allocation-error conversion boundary. |
| cost | Constant-time variant selection and indexed/reference access; no allocation or Budget debit here. The adjustment loop charges its measure visit before calling this helper. |
| Design | [src/runtime/aggregate_detail.hpp](../../../../../src/runtime/aggregate_detail.hpp), [docs/sql_aggregate_runtime.md §State and lifetime](../../../../sql_aggregate_runtime.md), [docs/aggregate_batches.md](../../../../aggregate_batches.md), [docs/aggregates.md](../../../../aggregates.md), [build/verification/w06-sql-aggregate-runtime-design-v1/cost-and-lifetime.md](../../../../../build/verification/w06-sql-aggregate-runtime-design-v1/cost-and-lifetime.md) |

## B0018

[Lines 133–134](../../../../../src/runtime/aggregate_detail.hpp#L133); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
// The count and numerator change together
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Record the private arithmetic premise established by row/group admission before adjusting statistics. |
| inputs / outputs | The comment applies to adjust's exact non-NULL count and numerator updates. |
| invariants | Admitted total group multiplicity is at most INT64_MAX; matching input contributions keep sums below the private 127-bit intermediate bound. |
| ownership | Statistics are inline proposed scratch, not independent owning big integers. |
| failure | This premise removes redundant generic overflow handlers from limb primitives, while public range errors remain at admission. |
| cost | No executable work from the comment. |
| Design | [docs/aggregates.md](../../../../aggregates.md), [src/runtime/aggregate_integer.hpp](../../../../../src/runtime/aggregate_integer.hpp), [src/runtime/aggregate_detail.hpp](../../../../../src/runtime/aggregate_detail.hpp), [docs/aggregate_batches.md](../../../../aggregate_batches.md), [docs/sql_aggregate_runtime.md](../../../../sql_aggregate_runtime.md) |

```text
// The count and numerator change together from the same non-NULL argument. // The group count was already admitted, establishing the private 127-bit bound.
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | State the exact shared-arithmetic premise used for count and numerator adjustment. |
| inputs / outputs | Comment explains same non-NULL argument updates both count and numerator; admitted group count bounds the private wide intermediate. |
| invariants | This proof premise depends on group/count admission and is not an independent runtime input-validation port. |
| ownership | No value is owned by the comment; State is provided by the caller. |
| failure | Arithmetic assertion/range errors are governed by adjust/final check helpers. |
| cost | No executable cost; count and exact numerator updates are charged by adjust. |
| Design | [build/verification/w06-sql-aggregate-runtime-design-v1/design.md](../../../../../build/verification/w06-sql-aggregate-runtime-design-v1/design.md), [build/verification/w06-sql-aggregate-runtime-design-v1/cost-and-lifetime.md](../../../../../build/verification/w06-sql-aggregate-runtime-design-v1/cost-and-lifetime.md), [build/verification/w06-sql-aggregate-runtime-design-v1/reference-plan.md](../../../../../build/verification/w06-sql-aggregate-runtime-design-v1/reference-plan.md), [src/runtime/aggregate_detail.hpp](../../../../../src/runtime/aggregate_detail.hpp), [docs/sql_aggregate_runtime.md](../../../../sql_aggregate_runtime.md), [docs/aggregates.md](../../../../aggregates.md), [docs/sql_rows_batches.md](../../../../sql_rows_batches.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0019

[Lines 135–152](../../../../../src/runtime/aggregate_detail.hpp#L135); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
if (erase) { assert(amount <= state.count);
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Retract or add the exact non-NULL multiplicity for the current measure. |
| inputs / outputs | A non-NULL argument and admitted weight difference enter; state.count changes by that magnitude. |
| invariants | For erasure the old row contributes at least amount; for insertion the new total group bound also bounds non-NULL count, preventing uint64 overflow. |
| ownership | Count is inline proposed state, with no owner transfer. |
| failure | The assertion checks a private invariant; public old-weight/group-bound validation precedes this branch. |
| cost | Fixed arithmetic per non-NULL measure. |
| Design | [docs/aggregates.md](../../../../aggregates.md), [src/runtime/aggregate_integer.hpp](../../../../../src/runtime/aggregate_integer.hpp), [src/runtime/aggregate_detail.hpp](../../../../../src/runtime/aggregate_detail.hpp), [docs/aggregate_batches.md](../../../../aggregate_batches.md), [docs/sql_aggregate_runtime.md](../../../../sql_aggregate_runtime.md) |

```text
if (measures[i].int64_sum && !state.sum.fits_int64())
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Enforce SUM(integer) bigint range only in the default single-row adjust instantiation. |
| inputs / outputs | Updated exact proposed numerator and compiler result-kind mark determine signed-int64 fit. |
| invariants | Guarded by if constexpr(CheckInt64): apply/apply_weighted retain it, batch adjust&lt;false&gt; omits it and checks the completed group in finalize. |
| ownership | The check reads inline scratch and transfers no ownership. |
| failure | aggregate_overflow precedes single-row publication regardless of capture; batch range error occurs in finalization. |
| cost | Fixed limb/range check for marked single-row SUM(integer); no allocation. |
| Design | [docs/aggregates.md](../../../../aggregates.md), [src/runtime/aggregate_integer.hpp](../../../../../src/runtime/aggregate_integer.hpp), [src/runtime/aggregate_detail.hpp](../../../../../src/runtime/aggregate_detail.hpp), [docs/aggregate_batches.md](../../../../aggregate_batches.md), [docs/sql_aggregate_runtime.md](../../../../sql_aggregate_runtime.md) |

## B0020

[Lines 153–179](../../../../../src/runtime/aggregate_detail.hpp#L153); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Borrows borrowed{output, {}};
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Scope output-view cleanup to actual rendering, avoiding output-width work in ordinary updates and no-ops. |
| inputs / outputs | Only the preallocated output span enters this guard; its cells clear after the owned Tuple is produced or a render fails. |
| invariants | Every public output-rendering route uses this local guard. Calls that do not render never traverse output scratch. |
| ownership | Borrowed group-string views cannot remain in scratch after the synchronous render. |
| failure | Noexcept cleanup also handles partially populated output when a later field or allocation fails. |
| cost | O(output width) reset only for requested rendering, zero added persistent state or allocations. |
| Design | [docs/aggregates.md](../../../../aggregates.md), [Refactor.md §11.9 W04](../../../../../Refactor.md), [src/runtime/aggregate_detail.hpp](../../../../../src/runtime/aggregate_detail.hpp), [docs/aggregate_batches.md](../../../../aggregate_batches.md), [docs/sql_aggregate_runtime.md](../../../../sql_aggregate_runtime.md) |

```text
case AggregateOutputKind::count_all:
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Produce COUNT(*) and COUNT(expr) from the appropriate exact multiplicity. |
| inputs / outputs | Total group rows or the selected argument's non-NULL count enter; a present int64 output cell leaves. |
| invariants | Both counts are at most INT64_MAX by group admission; COUNT remains non-NULL even for an empty global group. |
| ownership | Only an inline scalar is assigned in borrowed scratch; final tuple ownership is handled below. |
| failure | No extra count overflow path is required after the established bounds. |
| cost | Fixed conversion/assignment per COUNT output. |
| Design | [docs/aggregates.md](../../../../aggregates.md), [src/runtime/aggregate_integer.hpp](../../../../../src/runtime/aggregate_integer.hpp), [src/runtime/aggregate_detail.hpp](../../../../../src/runtime/aggregate_detail.hpp), [docs/aggregate_batches.md](../../../../aggregate_batches.md), [docs/sql_aggregate_runtime.md](../../../../sql_aggregate_runtime.md) |

```text
case AggregateOutputKind::sum:
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Render nullable SUM with the type-specific admitted result domain. |
| inputs / outputs | The measure's non-NULL count and exact sum enter; NULL, checked int64, or inline NUMERIC(38,0) cell leaves. |
| invariants | A zero sum in a nonempty non-NULL measure remains present zero; only zero non-NULL count yields NULL. int64 range was already checked. |
| ownership | The numeric output is inline in scratch and later copied into the accounted output Tuple. |
| failure | Bounded decimal conversion may propagate a formatter error if a private arithmetic premise is violated; committed state is untouched. |
| cost | Fixed int64 assignment or bounded 38-digit decimal conversion, performed for this requested output. |
| Design | [docs/aggregates.md](../../../../aggregates.md), [src/runtime/aggregate_integer.hpp](../../../../../src/runtime/aggregate_integer.hpp), [src/runtime/aggregate_detail.hpp](../../../../../src/runtime/aggregate_detail.hpp), [docs/aggregate_batches.md](../../../../aggregate_batches.md), [docs/sql_aggregate_runtime.md](../../../../sql_aggregate_runtime.md) |

```text
case AggregateOutputKind::average:
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Render AVG from the exact numerator and its matching non-NULL count at the bound output scale. |
| inputs / outputs | A measure state and NUMERIC(38,s) descriptor enter; NULL for count zero or a rounded InlineDecimal leaves. |
| invariants | Positive count matches the sum's contributions and is at most INT64_MAX; scale is compiler-admitted 0..18. Rounding is exact, with half ties away from zero. |
| ownership | The produced digits are inline; declared precision/scale remain in the retained program metadata. |
| failure | Private formatter failure unwinds output preparation before publication. |
| cost | Bounded 128-bit division and stack decimal work per requested AVG; no floating point or allocating big integer. |
| Design | [docs/aggregates.md](../../../../aggregates.md), [src/runtime/aggregate_integer.hpp](../../../../../src/runtime/aggregate_integer.hpp), [src/runtime/aggregate_detail.hpp](../../../../../src/runtime/aggregate_detail.hpp), [docs/aggregate_batches.md](../../../../aggregate_batches.md), [docs/sql_aggregate_runtime.md](../../../../sql_aggregate_runtime.md) |

## B0021

[Lines 180–182](../../../../../src/runtime/aggregate_detail.hpp#L180); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
// Final-only SUM(integer) check, shared by genuine prepared contributors and // the standalone authenticated-row batch. Single-row adjust keeps its default.
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Document final-only SUM(integer) validation shared by genuine composed contributors and the standalone authenticated-row batch. |
| inputs / outputs | Comment distinguishes default immediate check in single-row adjust from final group check after a complete batch. |
| invariants | The composed path can hold a wide intermediate and checks the final touched group once; no new update bypass is provided. |
| ownership | No ownership effect; check_sums reads proposed State. |
| failure | Final out-of-range SUM throws before publication. |
| cost | No executable cost from comment; the following check scans measures and charges existing Budget. |
| Design | [build/verification/w06-sql-aggregate-runtime-design-v1/design.md](../../../../../build/verification/w06-sql-aggregate-runtime-design-v1/design.md), [build/verification/w06-sql-aggregate-runtime-design-v1/cost-and-lifetime.md](../../../../../build/verification/w06-sql-aggregate-runtime-design-v1/cost-and-lifetime.md), [build/verification/w06-sql-aggregate-runtime-design-v1/reference-plan.md](../../../../../build/verification/w06-sql-aggregate-runtime-design-v1/reference-plan.md), [src/runtime/aggregate_detail.hpp](../../../../../src/runtime/aggregate_detail.hpp), [docs/sql_aggregate_runtime.md](../../../../sql_aggregate_runtime.md), [docs/aggregates.md](../../../../aggregates.md), [docs/sql_rows_batches.md](../../../../sql_rows_batches.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0022

[Lines 183–190](../../../../../src/runtime/aggregate_detail.hpp#L183); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
inline void check_sums(const frontend::AggregateProgram& program, std::span<const State> states, Budget& budget)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Inspect every completed measure for required SUM(integer) bigint result range once. |
| inputs / outputs | Program + final State span + same Budget -&gt; seal or aggregate_overflow. |
| invariants | Only requested int64_sum result requires fits_int64; AVG can use wider numerator; no intermediate SUM gate for batch path. |
| ownership | Reads proposed state only. |
| failure | Final overflow/work denial precedes any source/native/group publication. |
| cost | One M scan with same old batch final-loop debits; no allocation. |
| Design | src/runtime/aggregate.cpp:417, [build/verification/w06-sql-aggregate-runtime-design-v1/design.md](../../../../../build/verification/w06-sql-aggregate-runtime-design-v1/design.md), [src/runtime/aggregate_detail.hpp](../../../../../src/runtime/aggregate_detail.hpp), [docs/sql_aggregate_runtime.md](../../../../sql_aggregate_runtime.md), [docs/aggregates.md](../../../../aggregates.md), [docs/sql_rows_batches.md](../../../../sql_rows_batches.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0023

[Lines 191–191](../../../../../src/runtime/aggregate_detail.hpp#L191); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
} // namespace crown::runtime::aggregate::detail
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Close the private aggregate detail namespace after shared W04 helpers. |
| inputs / outputs | Namespace scope close only. |
| invariants | No additional API or input admission path is declared at this boundary. |
| ownership | No owner action. |
| failure | Compile-time scope validation. |
| cost | Zero runtime work. |
| Design | [build/verification/w06-sql-aggregate-runtime-design-v1/design.md](../../../../../build/verification/w06-sql-aggregate-runtime-design-v1/design.md), [build/verification/w06-sql-aggregate-runtime-design-v1/cost-and-lifetime.md](../../../../../build/verification/w06-sql-aggregate-runtime-design-v1/cost-and-lifetime.md), [build/verification/w06-sql-aggregate-runtime-design-v1/reference-plan.md](../../../../../build/verification/w06-sql-aggregate-runtime-design-v1/reference-plan.md), [src/runtime/aggregate_detail.hpp](../../../../../src/runtime/aggregate_detail.hpp), [docs/sql_aggregate_runtime.md](../../../../sql_aggregate_runtime.md), [docs/aggregates.md](../../../../aggregates.md), [docs/sql_rows_batches.md](../../../../sql_rows_batches.md), [docs/query_memory.md](../../../../query_memory.md) |
