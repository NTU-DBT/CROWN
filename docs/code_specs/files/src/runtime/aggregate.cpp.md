# `src/runtime/aggregate.cpp` — block usage map

[Source](../../../../../src/runtime/aggregate.cpp) · [Source index](../../../README.md) · [Subsystem contracts](../../../subsystem_contracts.md) · [Reviewed primitives](../../../primitives.md)

Maintain accounted logical input-row multiplicities and exact COUNT/SUM/AVG group proposals through one prepared aggregate batch.

Snapshot SHA-256: `758e04d69fb7858fba4039e82d5e558765804c914bcb84c49061a8ccdb374ec0`. 458 lines partitioned into 55 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [support](../../../subsystem_contracts.md#support). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/support_invariants.md](../../../../support_invariants.md), [docs/runtime_support.md](../../../../runtime_support.md), [docs/prepared_epochs.md](../../../../prepared_epochs.md), [docs/result_cursors.md](../../../../result_cursors.md), [docs/epoch_views.md](../../../../epoch_views.md), [docs/code_review.md](../../../../code_review.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–32](../../../../../src/runtime/aggregate.cpp#L1) | Imports dependencies; declares namespace scope; declares aliases; declares types or opens a type body; declares values/defaults or compile-time conditions. | source comment (unverified): // namespace · [reviewed contract](#b0001) |
| [B0002 · 33–40](../../../../../src/runtime/aggregate.cpp#L33) | Callable definition: Data(const resource::MemoryAccount& owner, frontend::AggregateProgram source, Options requested) : account(owner), program(std::m… | calls account, program, std::move, options · [reviewed contract](#b0002) |
| [B0003 · 41–44](../../../../../src/runtime/aggregate.cpp#L41) | declares aliases; declares values/defaults or compile-time conditions. | source comment (unverified): // Reused arrays must not retain caller/erased-key string borrows after the · [reviewed contract](#b0003) |
| [B0004 · 45–45](../../../../../src/runtime/aggregate.cpp#L45) | Callable definition: bool global() const noexcept | calls empty; returns key.empty() · [reviewed contract](#b0004) |
| [B0005 · 46–48](../../../../../src/runtime/aggregate.cpp#L46) | Callable definition: void require_idle() const | calls fail · [reviewed contract](#b0005) |
| [B0006 · 49–55](../../../../../src/runtime/aggregate.cpp#L49) | Callable definition: Budget open(std::uint64_t next) const | calls require_idle, has_input, fail, take; returns budget · [reviewed contract](#b0006) |
| [B0007 · 56–58](../../../../../src/runtime/aggregate.cpp#L56) | Callable definition: void validate(std::span&lt;const Cell&gt; values, Budget& budget) const | calls aggregate::detail::validate · [reviewed contract](#b0007) |
| [B0008 · 59–61](../../../../../src/runtime/aggregate.cpp#L59) | Callable definition: void project(std::span&lt;const Cell&gt; values, Budget& budget) | calls aggregate::detail::project · [reviewed contract](#b0008) |
| [B0009 · 62–64](../../../../../src/runtime/aggregate.cpp#L62) | Callable definition: const Cell& argument(const frontend::AggregateMeasure& measure, std::span&lt;const Cell&gt; values) const | calls aggregate::detail::argument; returns aggregate::detail::argument(measure, values) · [reviewed contract](#b0009) |
| [B0010 · 65–69](../../../../../src/runtime/aggregate.cpp#L65) | Callable definition: template&lt;bool CheckInt64 = true&gt; void adjust(std::span&lt;State&gt; states, std::span&lt;const Cell&gt; values, std::uint64_t amount, bool er… | calls  · [reviewed contract](#b0010) |
| [B0011 · 70–73](../../../../../src/runtime/aggregate.cpp#L70) | Callable definition: Tuple render(std::span&lt;const Cell&gt; group_key, std::uint64_t count, std::span&lt;const State&gt; states, Budget& budget) | calls aggregate::detail::render; returns aggregate::detail::render(account, program, output, group_key, count, states, budget) · [reviewed contract](#b0011) |
| [B0012 · 74–74](../../../../../src/runtime/aggregate.cpp#L74) | Explanatory comments or spacing. |  |
| [B0013 · 75–141](../../../../../src/runtime/aggregate.cpp#L75) | Callable definition: Epoch replace(std::uint64_t next, std::uint64_t before, std::uint64_t after, bool capture, Budget& budget) | calls find, take, end, fail; guard assert(before &lt;= old_rows);; returns result; result; growth copy_of, insert; source comment (unverified): // New immutable keys and requested output stay private until all checks and · [reviewed contract](#b0013) |
| [B0014 · 142–151](../../../../../src/runtime/aggregate.cpp#L142) | Callable definition: void initialize() | calls take, size, global, emplace; growth copy_of, emplace · [reviewed contract](#b0014) |
| [B0015 · 152–157](../../../../../src/runtime/aggregate.cpp#L152) | declares aliases; declares types or opens a type body; declares values/defaults or compile-time conditions. | source comment (unverified): // One proposal per full logical row/group. No committed table changes until · [reviewed contract](#b0015) |
| [B0016 · 158–162](../../../../../src/runtime/aggregate.cpp#L158) | Type/record definition: struct GroupProposal |  · [reviewed contract](#b0016) |
| [B0017 · 163–169](../../../../../src/runtime/aggregate.cpp#L163) | Type/record definition: struct RowProposal |  · [reviewed contract](#b0017) |
| [B0018 · 170–183](../../../../../src/runtime/aggregate.cpp#L170) | declares aliases; declares values/defaults or compile-time conditions. | source comment (unverified): // Declared first for failed-construction unwinding. Explicit close clears · [reviewed contract](#b0018) |
| [B0019 · 184–206](../../../../../src/runtime/aggregate.cpp#L184) | Callable definition: Data(std::shared_ptr&lt;Owner&gt; target, const NetBatch& batch, Budget allowance) : owner(std::move(target)), budget(std::move(allowan… | calls owner, std::move, budget, groups; growth reserve; 3 loop sites; source comment (unverified): // Every retraction sees a subbag of the committed bag. Additions then see · [reviewed contract](#b0019) |
| [B0020 · 207–207](../../../../../src/runtime/aggregate.cpp#L207) | Callable definition: ~Data() | calls rollback · [reviewed contract](#b0020) |
| [B0021 · 208–208](../../../../../src/runtime/aggregate.cpp#L208) | Callable definition: bool active() const noexcept | calls ; returns live · [reviewed contract](#b0021) |
| [B0022 · 209–211](../../../../../src/runtime/aggregate.cpp#L209) | Explanatory comments or spacing. | source comment (unverified): // Validation/projection, actual tuple copies and actual State preparations · [reviewed contract](#b0022) |
| [B0023 · 212–219](../../../../../src/runtime/aggregate.cpp#L212) | Callable definition: void charge_copy(std::span&lt;const Cell&gt; values) | calls take, size; 1 loop sites; source comment (unverified): // Validation/projection, actual tuple copies and actual State preparations · [reviewed contract](#b0023) |
| [B0024 · 220–223](../../../../../src/runtime/aggregate.cpp#L220) | Callable definition: Tuple copy_key(std::span&lt;const Cell&gt; values) | calls charge_copy, Tuple::copy_of; returns Tuple::copy_of(owner-&gt;account, values); growth copy_of · [reviewed contract](#b0024) |
| [B0025 · 224–241](../../../../../src/runtime/aggregate.cpp#L224) | Callable definition: GroupProposal& touch_group(const Tuple& row) | calls project, view, take, find; returns queued-&gt;second; groups.emplace(std::move(owned), GroupProposal{current, std::move(after), {}}).firs…; growth emplace · [reviewed contract](#b0025) |
| [B0026 · 242–268](../../../../../src/runtime/aggregate.cpp#L242) | Callable definition: void touch(const RowDelta& delta) | calls take, validate, fail, find; growth emplace · [reviewed contract](#b0026) |
| [B0027 · 269–282](../../../../../src/runtime/aggregate.cpp#L269) | Callable definition: void adjust_rows(bool erasing) | calls take, assert, fail, view; guard if (erasing) { assert(row.amount &lt;= group.rows); group.rows -= row.amount; }; 1 loop sites · [reviewed contract](#b0027) |
| [B0028 · 283–289](../../../../../src/runtime/aggregate.cpp#L283) | Callable definition: Tuple render(const Tuple& key, const Group& group) | calls view, charge_copy; returns values; source comment (unverified): // render owns the copy already; debit its fields/bytes before it can escape · [reviewed contract](#b0028) |
| [B0029 · 290–307](../../../../../src/runtime/aggregate.cpp#L290) | Callable definition: void finalize(const Tuple& key, GroupProposal& group) | calls take, aggregate::detail::check_sums, global, end; growth push_back · [reviewed contract](#b0029) |
| [B0030 · 308–334](../../../../../src/runtime/aggregate.cpp#L308) | Callable definition: BatchEpoch commit() noexcept | calls assert, empty, insert, std::move; guard assert(live && owner-&gt;busy);; returns std::move(result); growth insert; 2 loop sites; source comment (unverified): // No allocation, arithmetic, output or admission remains between table · [reviewed contract](#b0030) |
| [B0031 · 335–339](../../../../../src/runtime/aggregate.cpp#L335) | Callable definition: void rollback() noexcept | calls clear, reset · [reviewed contract](#b0031) |
| [B0032 · 340–341](../../../../../src/runtime/aggregate.cpp#L340) | Closes surrounding scope/type. |  · [reviewed contract](#b0032) |
| [B0033 · 342–345](../../../../../src/runtime/aggregate.cpp#L342) | Callable definition: aggregate::BatchEpoch::BatchEpoch(const resource::MemoryAccount& account, std::uint64_t next, frontend::AggregateProgram source, … | calls sequence, captured, program, std::move · [reviewed contract](#b0033) |
| [B0034 · 346–347](../../../../../src/runtime/aggregate.cpp#L346) | declares callable signatures; declares values/defaults or compile-time conditions. | guard static_assert(std::is_nothrow_move_constructible_v&lt;aggregate::BatchEpoch&gt;); · [reviewed contract](#b0034) |
| [B0035 · 348–348](../../../../../src/runtime/aggregate.cpp#L348) | Callable definition: AggregateRuntime::AggregateRuntime(std::shared_ptr&lt;Data&gt; value) noexcept : data_(std::move(value)) | calls data_, std::move · [reviewed contract](#b0035) |
| [B0036 · 349–357](../../../../../src/runtime/aggregate.cpp#L349) | Callable definition: AggregateRuntime AggregateRuntime::create_into(const resource::MemoryAccount& account, frontend::AggregateProgram program, Option… | calls fail, std::move, initialize, AggregateRuntime; returns AggregateRuntime(std::move(value)); growth make_accounted_shared · [reviewed contract](#b0036) |
| [B0037 · 358–359](../../../../../src/runtime/aggregate.cpp#L358) | Callable definition: AggregateRuntime::AggregateRuntime(frontend::AggregateProgram program, Options options) : AggregateRuntime(create_into(resource::… | calls AggregateRuntime, create_into, resource::MemoryAccount::create, std::move · [reviewed contract](#b0037) |
| [B0038 · 360–362](../../../../../src/runtime/aggregate.cpp#L360) | declares callable signatures; declares values/defaults or compile-time conditions. |  · [reviewed contract](#b0038) |
| [B0039 · 363–366](../../../../../src/runtime/aggregate.cpp#L363) | Callable definition: AggregateRuntime::Data& AggregateRuntime::data() const | calls fail; returns *data_ · [reviewed contract](#b0039) |
| [B0040 · 367–367](../../../../../src/runtime/aggregate.cpp#L367) | Callable definition: const frontend::AggregateProgram& AggregateRuntime::program() const & | calls data; returns data().program · [reviewed contract](#b0040) |
| [B0041 · 368–368](../../../../../src/runtime/aggregate.cpp#L368) | Callable definition: std::uint64_t AggregateRuntime::sequence() const | calls data; returns data().sequence · [reviewed contract](#b0041) |
| [B0042 · 369–376](../../../../../src/runtime/aggregate.cpp#L369) | Callable definition: aggregate::Epoch AggregateRuntime::apply(const aggregate::Update& update) | calls data, open, size, fail; returns value.replace(update.sequence, update.before, update.after, value.options.capture_changes, budget); 1 loop sites · [reviewed contract](#b0042) |
| [B0043 · 377–384](../../../../../src/runtime/aggregate.cpp#L377) | Callable definition: aggregate::Epoch AggregateRuntime::apply_weighted(std::uint64_t next, storage::TupleValuesView values, std::uint64_t before, std:… | calls data, open, size, fail; returns value.replace(next, before, after, value.options.capture_changes, budget); 1 loop sites · [reviewed contract](#b0043) |
| [B0044 · 385–391](../../../../../src/runtime/aggregate.cpp#L385) | Callable definition: AggregateRuntime::PreparedBatch AggregateRuntime::prepare_batch(const aggregate::NetBatch& batch) | calls data, open, std::move, PreparedBatch; returns PreparedBatch(std::move(prepared)); growth make_accounted_unique · [reviewed contract](#b0044) |
| [B0045 · 392–393](../../../../../src/runtime/aggregate.cpp#L392) | Callable definition: AggregateRuntime::PreparedBatch::PreparedBatch(resource::AccountedUnique&lt;Data&gt; value) noexcept : data_(std::move(value)) | calls data_, std::move · [reviewed contract](#b0045) |
| [B0046 · 394–396](../../../../../src/runtime/aggregate.cpp#L394) | declares callable signatures; declares values/defaults or compile-time conditions. |  · [reviewed contract](#b0046) |
| [B0047 · 397–400](../../../../../src/runtime/aggregate.cpp#L397) | Callable definition: AggregateRuntime::PreparedBatch::Data& AggregateRuntime::PreparedBatch::data() const | calls active, fail; returns *data_ · [reviewed contract](#b0047) |
| [B0048 · 401–401](../../../../../src/runtime/aggregate.cpp#L401) | Callable definition: bool AggregateRuntime::PreparedBatch::active() const noexcept | calls active; returns data_ && data_-&gt;active() · [reviewed contract](#b0048) |
| [B0049 · 402–402](../../../../../src/runtime/aggregate.cpp#L402) | Callable definition: const aggregate::BatchEpoch& AggregateRuntime::PreparedBatch::preview() const & | calls data; returns data().result · [reviewed contract](#b0049) |
| [B0050 · 403–405](../../../../../src/runtime/aggregate.cpp#L403) | Callable definition: aggregate::BatchEpoch AggregateRuntime::PreparedBatch::commit() | calls data, commit, reset; returns result · [reviewed contract](#b0050) |
| [B0051 · 406–406](../../../../../src/runtime/aggregate.cpp#L406) | Callable definition: void AggregateRuntime::PreparedBatch::rollback() noexcept | calls reset · [reviewed contract](#b0051) |
| [B0052 · 407–414](../../../../../src/runtime/aggregate.cpp#L407) | Callable definition: aggregate::Snapshot AggregateRuntime::snapshot(aggregate::SnapshotLimits limits) const | calls data, require_idle, take, size; returns result; growth push_back, reserve; 1 loop sites · [reviewed contract](#b0052) |
| [B0053 · 415–415](../../../../../src/runtime/aggregate.cpp#L415) | Callable definition: resource::MemoryStatistics AggregateRuntime::accounted_memory_statistics() const | calls data, statistics; returns data().account.statistics() · [reviewed contract](#b0053) |
| [B0054 · 416–457](../../../../../src/runtime/aggregate.cpp#L416) | Callable definition: void AggregateRuntime::check_invariants() const | calls data, require_idle, expected, global; growth copy_of, emplace; 4 loop sites; source comment (unverified): // Diagnostic recomputation can visit cancelling rows in any key order. · [reviewed contract](#b0054) |
| [B0055 · 458–458](../../../../../src/runtime/aggregate.cpp#L458) | Closes surrounding scope/type. | source comment (unverified): // namespace crown::runtime · [reviewed contract](#b0055) |

## B0001

[Lines 1–32](../../../../../src/runtime/aggregate.cpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
#include "crown/runtime/aggregate.hpp"
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Define the logical-bag aggregate component and import integer/resource dependencies plus the BatchEpoch move trait. |
| inputs / outputs | Runtime/compiler declarations and local numeric/resource dependencies enter; aliases and type_traits support the implementation and compile-time nonthrowing result assertion. |
| invariants | Container aliases use MemoryAllocator; imports add no physical-source/backend or recovery proof. |
| ownership | Declarations acquire no runtime payload owner; actual containers receive an account at construction. |
| failure | Declaration block adds no runtime handler; static_assert is compile-time only. |
| cost | No runtime traversal/allocation from imports and aliases. |
| Design | [docs/aggregates.md](../../../../aggregates.md), [Refactor.md §11.9 W04](../../../../../Refactor.md), [include/crown/runtime/aggregate.hpp](../../../../../include/crown/runtime/aggregate.hpp) |

```text
struct AggregateRuntime::Data {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Own receiver account, immutable program, reusable scratch, committed row/group ledgers, sequence and active-preparation flag. |
| inputs / outputs | Rows maps complete owned row tuples to weights; Groups maps group keys to count/measure states; busy marks a fully prepared token. |
| invariants | Committed maps remain unchanged while proposals are prepared. Facade and token can share Data; one active token is allowed. Compiler metadata may retain its separate source account. |
| ownership | Data owns maps/scratch/account; facade and PreparedBatch may each retain shared_ptr references. Immutable Tuple keys/results can have other owners. |
| failure | No rollback journal over committed state. Preparation failures leave Data idle/unchanged because busy latches only after constructor success. |
| cost | Committed storage scales with distinct rows/groups*measures/fixed scratch/retained bytes; batch proposals scale with touched rows/groups. |
| Design | [docs/aggregates.md](../../../../aggregates.md), [docs/query_memory.md](../../../../query_memory.md), [include/crown/resource/allocator.hpp](../../../../../include/crown/resource/allocator.hpp) |

## B0002

[Lines 33–40](../../../../../src/runtime/aggregate.cpp#L33); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Data(const resource::MemoryAccount& owner,
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Allocate fixed query-shaped scratch once and construct empty accounted committed maps. |
| inputs / outputs | Receiving account, factory-produced program, and Options enter; input/key/output/proposed arrays use their respective schema widths. |
| invariants | Rows uses source_counts and Groups uses support_metadata; all scratch uses scratch. This constructor creates no input row or global result. |
| ownership | Data retains the receiving account and program; arrays retain no external input borrows at construction. |
| failure | Any failed nested construction unwinds already constructed members under the accounted owner factory. |
| cost | O(input width + group width + output width + measure count) initialization; up to four nonempty scratch-vector allocations. |
| Design | [docs/aggregates.md](../../../../aggregates.md), [docs/query_memory.md](../../../../query_memory.md), [include/crown/resource/allocator.hpp](../../../../../include/crown/resource/allocator.hpp) |

## B0003

[Lines 41–44](../../../../../src/runtime/aggregate.cpp#L41); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
// Reused arrays must not retain caller/erased-key string borrows
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Explain why borrowed per-call cells are cleared on every exit instead of storing an undo record. |
| inputs / outputs | The following Borrows guard covers only the spans passed by each caller. |
| invariants | Clearing borrowed views does not roll back committed query state; state publication is handled separately. |
| ownership | The guard does not retain input/string ownership; its enclosing synchronous operation keeps the referenced arrays live. |
| failure | Unwinding clears views without throwing or trying to recover query mutations. |
| cost | Cleanup scans only explicitly supplied spans; output scratch is supplied by render alone. |
| Design | [docs/aggregates.md](../../../../aggregates.md), [Refactor.md §11.9 W04](../../../../../Refactor.md) |

## B0004

[Lines 45–45](../../../../../src/runtime/aggregate.cpp#L45); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
bool global() const noexcept
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Distinguish ungrouped aggregation from explicit nonempty grouping. |
| inputs / outputs | The immutable key scratch width enters; true means no grouping columns. |
| invariants | key.size() was fixed from the admitted program, so emptiness is query shape, not current group membership. |
| ownership | The helper borrows Data and changes no ownership. |
| failure | No failure path. |
| cost | Constant-time emptiness test. |
| Design | [docs/aggregates.md](../../../../aggregates.md), [Refactor.md §11.9 W04](../../../../../Refactor.md) |

## B0005

[Lines 46–48](../../../../../src/runtime/aggregate.cpp#L46); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void require_idle() const {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Reject operations that would reuse aggregate scratch or mutate committed tables while a batch token is active. |
| inputs / outputs | Reads Data.busy; idle returns, active preparation throws aggregate_busy. |
| invariants | busy is latched only after a complete token is built. apply/apply_weighted/prepare_batch, snapshot, and check_invariants guard; program/sequence/account statistics stay readable. |
| ownership | Reads the shared Data flag; no owner/proposal changes. |
| failure | aggregate_busy is checked before source/sequence/work in open(), and before snapshot/diagnostic scratch work. |
| cost | One boolean check on each guarded operation; fixed real overhead. |
| Design | [build/verification/w06-aggregate-batch-design-v1/design.md](../../../../../build/verification/w06-aggregate-batch-design-v1/design.md), [docs/aggregates.md](../../../../aggregates.md), Refactor.md:1325-1327, [build/verification/w06-contract-assessment-v1/assessment.md](../../../../../build/verification/w06-contract-assessment-v1/assessment.md), [docs/aggregate_batches.md](../../../../aggregate_batches.md), [build/verification/aggregate-batch-acceptance-v1/findings.json](../../../../../build/verification/aggregate-batch-acceptance-v1/findings.json), [include/crown/resource/allocator.hpp](../../../../../include/crown/resource/allocator.hpp), [include/crown/resource/ownership.hpp](../../../../../include/crown/resource/ownership.hpp), [include/crown/resource/owner_allocator.hpp](../../../../../include/crown/resource/owner_allocator.hpp), [src/runtime/aggregate_integer.hpp](../../../../../src/runtime/aggregate_integer.hpp) |

## B0006

[Lines 49–55](../../../../../src/runtime/aggregate.cpp#L49); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Budget open(std::uint64_t next) const
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Reject active-batch use first, then validate source/next-sequence admission and open one operation Budget. |
| inputs / outputs | Requested sequence enters; idle valid input runtime yields a fresh Budget with initial selected charge. |
| invariants | require_idle precedes no-FROM and sequence checks; next must be committed sequence+1 and UINT64_MAX cannot advance. Each operation uses one local Budget. |
| ownership | Only a local budget is created; committed sequence is unchanged here. |
| failure | aggregate_busy is first; aggregate_input, invalid_sequence, or initial aggregate_work_limit also fails before mutation. |
| cost | One busy/source/sequence check plus initial selected charge; no successful-path allocation. |
| Design | [docs/aggregates.md](../../../../aggregates.md), [Refactor.md §11.9 W04](../../../../../Refactor.md) |

## B0007

[Lines 56–58](../../../../../src/runtime/aggregate.cpp#L56); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void validate(std::span<const Cell> values,
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Admit a complete logical input row against the compiled scalar kinds, nullability, and decimal range. |
| inputs / outputs | Forwards the compiled program, full nullable row and cumulative Budget to aggregate::detail::validate. |
| invariants | The helper enforces exact bound type/nullability and charges input fields/string bytes; this wrapper does not reinterpret SQL or retain row views. |
| ownership | Borrowed cell/string views remain scoped to the caller; shared helper owns no scratch. |
| failure | Validation/type/work errors propagate before the existing single-row or prepared-batch publication point. |
| cost | Same selected per-field/byte validation cost as shared helper; no second algorithm or allocation. |
| Design | [docs/aggregates.md](../../../../aggregates.md), [Refactor.md §11.9 W04](../../../../../Refactor.md), [include/crown/frontend/bind.hpp](../../../../../include/crown/frontend/bind.hpp) |

## B0008

[Lines 59–61](../../../../../src/runtime/aggregate.cpp#L59); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void project(std::span<const Cell> values,
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Gather grouping columns into reusable borrowed key scratch. |
| inputs / outputs | Forwards the compiled group columns, borrowed input, reusable key scratch and Budget to aggregate::detail::project. |
| invariants | Projection copies nullable cell views into scratch only; it creates no owning key and charges the existing per-group-column work. |
| ownership | Key scratch remains receiver-owned by AggregateRuntime::Data; borrowed input ends with the synchronous call. |
| failure | Work failure propagates before publication; scratch borrows are cleared by the existing scope guard. |
| cost | One selected visit per group column; shared helper avoids another projection implementation. |
| Design | [docs/aggregates.md](../../../../aggregates.md), [Refactor.md §11.9 W04](../../../../../Refactor.md) |

## B0009

[Lines 62–64](../../../../../src/runtime/aggregate.cpp#L62); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
const Cell& argument(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Resolve one compiled measure argument without an expression VM or owning DTO. |
| inputs / outputs | Forwards one resolved measure and complete row to aggregate::detail::argument, returning its borrowed argument cell. |
| invariants | The compiler has already resolved either a ColumnId or owned constant; no parser/name lookup occurs. |
| ownership | Returned Cell reference borrows the input span or immutable Program constant owner. |
| failure | Invalid internal variant propagates; compiled program is the authority. |
| cost | Constant variant selection and indexed access; no allocation or budget admission. |
| Design | [docs/aggregates.md](../../../../aggregates.md), [Refactor.md §11.9 W04](../../../../../Refactor.md), [include/crown/frontend/aggregate.hpp](../../../../../include/crown/frontend/aggregate.hpp) |

## B0010

[Lines 65–69](../../../../../src/runtime/aggregate.cpp#L65); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void adjust(std::span<State> states,
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Apply one row’s multiplicity difference to proposed per-measure counts and exact sums under a compile-time range-check policy. |
| inputs / outputs | Forwards measure states, row cells, uint64 amount, direction and Budget to aggregate::detail::adjust. |
| invariants | Default CheckInt64 preserves immediate single-row SUM(integer) rejection; the composed/batch helper can select final-only check explicitly. COUNT and exact numerator use the same non-NULL argument. |
| ownership | Mutates only receiver-funded scratch/proposed State supplied by the existing caller; input views are synchronous borrows. |
| failure | Work, arithmetic and default SUM range failures propagate before existing publication. |
| cost | O(measures) selected operations and exact wide arithmetic; no separate helper allocation. |
| Design | [docs/aggregates.md](../../../../aggregates.md), [src/runtime/aggregate_integer.hpp](../../../../../src/runtime/aggregate_integer.hpp) |

## B0011

[Lines 70–73](../../../../../src/runtime/aggregate.cpp#L70); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Tuple render(std::span<const Cell> group_key,
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Materialize one group's ordered SQL output only when an event or snapshot requests it. |
| inputs / outputs | Forwards account, Program, reusable output scratch, key, count, State and Budget to aggregate::detail::render; returns an owning Tuple. |
| invariants | Compiled output descriptors determine SQL COUNT/SUM/AVG/NULL and scale semantics; copy charge precedes retained output. |
| ownership | Output scratch borrows key/state/constant views only during call and is cleared by Borrows; returned Tuple owns copied payloads in receiver. |
| failure | Work, formatting and receiver allocation errors propagate before result publication. |
| cost | O(output width and copied string bytes), real Tuple allocation/copy; snapshot/capture requests pay it explicitly. |
| Design | [docs/aggregates.md](../../../../aggregates.md), [src/runtime/aggregate_integer.hpp](../../../../../src/runtime/aggregate_integer.hpp), [src/runtime/aggregate_tuple.cpp](../../../../../src/runtime/aggregate_tuple.cpp) |

## B0013

[Lines 75–141](../../../../../src/runtime/aggregate.cpp#L75); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Epoch replace(std::uint64_t next,
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Replace one complete logical row's multiplicity and its single affected group with strong pre-publication failure behavior. |
| inputs / outputs | Validated borrowed input, next epoch, expected prior/new weights, capture flag, and Budget enter; an Epoch with optional visible output change leaves. |
| invariants | Only exact committed prior weight is accepted. Group total and per-measure domains are checked before commit; ungrouped empty stays present. |
| ownership | Private keys, output tuples, and detached nodes own all new allocations until publication. Existing immutable keys/stats are reused or copied into fixed scratch. |
| failure | All admission, arithmetic, work and allocation failures precede map/epoch mutation; no undo journal or broad catch is needed. |
| cost | Map searches/insertions cost O(log distinct rows + log groups) key comparisons, plus group/measure width and requested output; new rows/groups allocate, existing weight changes with capture off do not. |
| Design | [docs/aggregates.md](../../../../aggregates.md), [Refactor.md §11.9 W04](../../../../../Refactor.md), [include/crown/resource/allocator.hpp](../../../../../include/crown/resource/allocator.hpp) |

```text
const auto actual = row == rows.end() ? 0 : row->second;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Check replacement identity against the committed complete-row multiplicity. |
| inputs / outputs | The borrowed input probes rows; absent row means actual weight zero, which must equal before. |
| invariants | No group or count arithmetic is trusted until exact prior weight matches. A missing row with before=after=0 is an admitted no-op. |
| ownership | Lookup borrows caller cells and retained keys without constructing an owning probe. |
| failure | aggregate_weight_mismatch throws before any state change. |
| cost | One ordered-map lookup with actual row-prefix/string comparison costs and one selected row-probe charge. |
| Design | [docs/aggregates.md](../../../../aggregates.md), [docs/weighted_enumeration.md](../../../../weighted_enumeration.md) |

```text
if (before == after) { result.metrics
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Advance an admitted no-op epoch without preparing group state or output. |
| inputs / outputs | Equal verified weights enter; sequence updates to next and an unchanged Epoch leaves. |
| invariants | Input type/sequence/work/prior-weight admission already succeeded. captured records the requested mode even though no output change exists. |
| ownership | No new keys, tuple payloads, nodes, or output rows are retained. |
| failure | No additional fallible work follows the no-op sequence assignment. |
| cost | Fixed work after input admission/row lookup; no group search, measure scan, output-width scan, or allocation. |
| Design | [docs/aggregates.md](../../../../aggregates.md), [Refactor.md §11.9 W04](../../../../../Refactor.md) |

```text
const auto base = old_rows - before;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Admit the proposed total group multiplicity without unsigned intermediate overflow. |
| inputs / outputs | Verified prior row weight, committed group total, new row weight, and count_limit enter; next_rows leaves. |
| invariants | before &lt;= old_rows and old_rows &lt;= count_limit. after &lt;= count_limit - (old_rows - before) proves next_rows &lt;= count_limit &lt;= INT64_MAX. |
| ownership | Only local scalar values are created. |
| failure | aggregate_overflow rejects excessive total count before adjusting any proposed statistic or committed map. |
| cost | Constant-time bounded subtraction/comparison/addition. |
| Design | [docs/aggregates.md](../../../../aggregates.md), [src/runtime/aggregate_integer.hpp](../../../../../src/runtime/aggregate_integer.hpp) |

```text
if (group == groups.end()) std::fill(proposed.begin(),
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Prepare the affected group's sufficient statistics without copying unrelated runtime state. |
| inputs / outputs | Missing group yields zero scratch; existing group copies only its fixed measure vector, followed by one row-weight difference. |
| invariants | proposed has the immutable program's measure width; every changed measure is still private until commit. |
| ownership | Scratch is preallocated on the receiving account and owns no external cell/string data. |
| failure | A later adjust failure leaves only disposable scratch changed; next call zeroes or recopies it. |
| cost | O(distinct measures) inline copy/adjust; no whole-row-map or whole-group-map clone. |
| Design | [docs/aggregates.md](../../../../aggregates.md), [src/runtime/aggregate_integer.hpp](../../../../../src/runtime/aggregate_integer.hpp) |

```text
Tuple row_key, group_key;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Retain new complete-row/group keys only when they will become persistent. |
| inputs / outputs | New row/group presence and compiled full_input_group_key enter; private owning Tuple keys or references to existing keys leave. |
| invariants | Full-input key aliasing is allowed only for the compiler-certified same columns in the same order; group presence after update follows global() or next_rows != 0. |
| ownership | New string/cell payloads are deep copied into account. Existing immutable keys and exact full-row group aliases share owners. |
| failure | Key allocation failure occurs before map publication; private keys release during unwinding. |
| cost | Copy work/allocations only for newly retained keys; otherwise fixed handle/reference work. Key width and string bytes remain real costs. |
| Design | [docs/aggregates.md](../../../../aggregates.md), [docs/query_memory.md](../../../../query_memory.md), [include/crown/resource/allocator.hpp](../../../../../include/crown/resource/allocator.hpp) |

```text
if (capture) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Capture a visible group-output transition after arithmetic succeeds and before state publication. |
| inputs / outputs | Old/new group presence, counts and states enter; at most one GroupChange with optional owned before/after Tuples leaves. |
| invariants | Absent group differs from a present row containing NULL. Equal rounded/value outputs emit no event even when input weight changed; group creation/removal remains observable. |
| ownership | Event key/rows own immutable accounted payloads and survive later group deletion or runtime destruction; program/schema is not automatically included in Epoch. |
| failure | Rendering, work, comparison, or tuple allocation failure unwinds private output without changing committed maps/epoch. |
| cost | No output work when capture is false; otherwise up to two full output renders and a payload equality check. |
| Design | [docs/aggregates.md](../../../../aggregates.md), [Refactor.md §11.9 W04](../../../../../Refactor.md) |

```text
typename Rows::node_type new_row;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Prepare detached row/group nodes, including any new per-group statistic vector, before commit. |
| inputs / outputs | Private retained keys and proposed states enter; only nodes required by previously missing entries are constructed. |
| invariants | Each node uses its destination map's exact allocator. Group values receive the admitted next_rows and copied proposed statistics. |
| ownership | Node handles own prepared allocations until insert; unwinding destroys them and private keys. |
| failure | Allocation or final work-charge failure precedes all committed-map mutations. |
| cost | Up to one row node, one group node, and one nonempty group-state vector; no allocation for already existing entries unless output capture requested it. |
| Design | [docs/aggregates.md](../../../../aggregates.md), [docs/query_memory.md](../../../../query_memory.md), [include/crown/resource/allocator.hpp](../../../../../include/crown/resource/allocator.hpp) |

```text
// Publication has no allocation, output formatting or fallible numeric work.
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Publish the already prepared row/group replacement and then its sequence. |
| inputs / outputs | Funded same-allocator node handles, existing iterators, admitted counts, and proposed inline stats enter; rows/groups/sequence become the new committed state. |
| invariants | Noexcept valid-key comparisons and allocation-free node transfer remove failure points between row and group publication. Private uniqueness makes insert success assertions valid. |
| ownership | Inserted nodes transfer ownership; erased entries release their keys/state without allocation. Captured event owners keep requested old payloads alive. |
| failure | No fallible budget, formatting or numeric check remains; standard deallocation is noexcept under the memory-account contract. |
| cost | Real ordered-map insertion/rebalancing or erasure plus O(measures) state copy; key comparisons and last-owner release costs remain, despite zero allocation. |
| Design | [docs/aggregates.md](../../../../aggregates.md), [docs/query_memory.md](../../../../query_memory.md), [include/crown/resource/allocator.hpp](../../../../../include/crown/resource/allocator.hpp) |

## B0014

[Lines 142–151](../../../../../src/runtime/aggregate.cpp#L142); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void initialize() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Establish empty grouped/global semantics and the immutable no-FROM singleton before returning a runtime. |
| inputs / outputs | Fresh private Data enters; grouped input remains empty, ungrouped input gains one zero-count group, and no-FROM internally contributes one nullary row at sequence zero. |
| invariants | An empty global result is not an input row. Public no-FROM updates are rejected by open; the internal singleton uses the same statistics replacement path. |
| ownership | Any global key/group and no-FROM row storage uses the receiving account; initialization remains private to the owner factory. |
| failure | Work/account/count/arithmetic failure destroys the private Data and all partial construction, exposing no runtime. |
| cost | O(fixed schema widths + no-FROM measures) selected setup work; global/no-FROM allocate their actual required key/node/state payloads. |
| Design | [docs/aggregates.md](../../../../aggregates.md), [Refactor.md §11.9 W04](../../../../../Refactor.md) |

## B0015

[Lines 152–157](../../../../../src/runtime/aggregate.cpp#L152); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
// One proposal per full logical row/group.
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Introduce private per-row/per-group proposals without mutating committed ledgers during preparation. |
| inputs / outputs | Declaration comment and Owner alias scope the touched-proposal Data. |
| invariants | Committed tables are untouched until commit; destroying preparation discards private state. |
| ownership | Data will retain the actual aggregate owner. |
| failure | No exception translation or extra transaction framework is introduced. |
| cost | No runtime cost from the boundary comment. |
| Design | [build/verification/w06-aggregate-batch-design-v1/design.md](../../../../../build/verification/w06-aggregate-batch-design-v1/design.md), [docs/aggregates.md](../../../../aggregates.md), Refactor.md:1325-1327, [build/verification/w06-contract-assessment-v1/assessment.md](../../../../../build/verification/w06-contract-assessment-v1/assessment.md), [docs/aggregate_batches.md](../../../../aggregate_batches.md), [build/verification/aggregate-batch-acceptance-v1/findings.json](../../../../../build/verification/aggregate-batch-acceptance-v1/findings.json), [include/crown/resource/allocator.hpp](../../../../../include/crown/resource/allocator.hpp), [include/crown/resource/ownership.hpp](../../../../../include/crown/resource/ownership.hpp), [include/crown/resource/owner_allocator.hpp](../../../../../include/crown/resource/owner_allocator.hpp), [src/runtime/aggregate_integer.hpp](../../../../../src/runtime/aggregate_integer.hpp) |

## B0016

[Lines 158–162](../../../../../src/runtime/aggregate.cpp#L158); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct GroupProposal {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Retain one affected group’s committed iterator, proposed statistics, and possible insertion node. |
| inputs / outputs | Existing position or end(), proposed Group after-state, and detached node for a newly surviving group. |
| invariants | Exactly one proposal per touched group. Existing vector copies use the persistent support_metadata allocator so commit can swap legally. |
| ownership | Proposal map owns record; after vector/node use receiver account. Iterator borrows stable committed map entry while busy excludes updates. |
| failure | Copy/vector/node failure is private and occurs before publication. |
| cost | One record per touched group; one O(measures) State copy/allocation for an existing group, or one initialization for a new group. |
| Design | [build/verification/w06-aggregate-batch-design-v1/design.md](../../../../../build/verification/w06-aggregate-batch-design-v1/design.md), [docs/aggregates.md](../../../../aggregates.md), Refactor.md:1325-1327, [build/verification/w06-contract-assessment-v1/assessment.md](../../../../../build/verification/w06-contract-assessment-v1/assessment.md), [include/crown/resource/allocator.hpp](../../../../../include/crown/resource/allocator.hpp), [include/crown/resource/ownership.hpp](../../../../../include/crown/resource/ownership.hpp), [include/crown/resource/owner_allocator.hpp](../../../../../include/crown/resource/owner_allocator.hpp), [docs/aggregate_batches.md](../../../../aggregate_batches.md), [build/verification/aggregate-batch-acceptance-v1/findings.json](../../../../../build/verification/aggregate-batch-acceptance-v1/findings.json), [src/runtime/aggregate_integer.hpp](../../../../../src/runtime/aggregate_integer.hpp) |

## B0017

[Lines 163–169](../../../../../src/runtime/aggregate.cpp#L163); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct RowProposal {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Retain one unique row delta and its final weight, linked to the one touched-group proposal. |
| inputs / outputs | Committed iterator/end, final after, magnitude/direction, GroupProposal pointer, optional detached insertion node. |
| invariants | Unique complete input keys mean one row proposal per row; iterators and group pointers stay stable during busy preparation. |
| ownership | Row proposal map owns record/key/node; group pointer is non-owning into stable group proposal map. |
| failure | Key/node/map failure happens during preparation and cannot publish partial state. |
| cost | One map record per touched row, with actual ordered-key comparisons; no row multiplicity expansion. |
| Design | [build/verification/w06-aggregate-batch-design-v1/design.md](../../../../../build/verification/w06-aggregate-batch-design-v1/design.md), [docs/aggregates.md](../../../../aggregates.md), Refactor.md:1325-1327, [build/verification/w06-contract-assessment-v1/assessment.md](../../../../../build/verification/w06-contract-assessment-v1/assessment.md), [docs/aggregate_batches.md](../../../../aggregate_batches.md), [build/verification/aggregate-batch-acceptance-v1/findings.json](../../../../../build/verification/aggregate-batch-acceptance-v1/findings.json), [include/crown/resource/allocator.hpp](../../../../../include/crown/resource/allocator.hpp), [include/crown/resource/ownership.hpp](../../../../../include/crown/resource/ownership.hpp), [include/crown/resource/owner_allocator.hpp](../../../../../include/crown/resource/owner_allocator.hpp), [src/runtime/aggregate_integer.hpp](../../../../../src/runtime/aggregate_integer.hpp) |

## B0018

[Lines 170–183](../../../../../src/runtime/aggregate.cpp#L170); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
using GroupProposals =
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Fund touched maps and output under one receiver and retain owner through all proposal lifetimes. |
| inputs / outputs | Scratch-purpose proposal maps, retained shared Owner, copied Budget, BatchEpoch and live=false. |
| invariants | Same account funds nested state/keys/nodes/output; live becomes true only after all preparation; no per-row refill. |
| ownership | Owner is declared first for failed-construction unwinding; explicit close clears entries before owner reset; map allocators retain their account independently. |
| failure | Member construction unwinds safely; an uncompleted token never latches busy. |
| cost | O(D+G) map entries plus G*M States and optional output, all touched-only. |
| Design | [build/verification/w06-aggregate-batch-design-v1/design.md](../../../../../build/verification/w06-aggregate-batch-design-v1/design.md), [docs/aggregates.md](../../../../aggregates.md), Refactor.md:1325-1327, [build/verification/w06-contract-assessment-v1/assessment.md](../../../../../build/verification/w06-contract-assessment-v1/assessment.md), [include/crown/resource/allocator.hpp](../../../../../include/crown/resource/allocator.hpp), [include/crown/resource/ownership.hpp](../../../../../include/crown/resource/ownership.hpp), [include/crown/resource/owner_allocator.hpp](../../../../../include/crown/resource/owner_allocator.hpp), [docs/aggregate_batches.md](../../../../aggregate_batches.md), [build/verification/aggregate-batch-acceptance-v1/findings.json](../../../../../build/verification/aggregate-batch-acceptance-v1/findings.json), [src/runtime/aggregate_integer.hpp](../../../../../src/runtime/aggregate_integer.hpp) |

## B0019

[Lines 184–206](../../../../../src/runtime/aggregate.cpp#L184); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Data(std::shared_ptr<Owner> target, const NetBatch& batch, Budget allowance)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Prepare and seal the complete logical-delta batch and preview before the public token makes the runtime busy. |
| inputs / outputs | Shared runtime Data, borrowed NetBatch, and the one opened Budget enter; private row/group proposals, BatchEpoch, and detached nodes are constructed. |
| invariants | Validates all deltas, applies removals then additions, finalizes touched groups once, stages missing nodes, then sets live. The public factory latches busy only after constructor success. |
| ownership | Cell/string borrows are cleared from scratch on exit. New keys/nodes/vectors/output use receiver; program handle remains tied to compiler account. |
| failure | Row, duplicate/weight/count/SUM/work/account/allocation failure unwinds private members; committed state and busy remain unchanged. |
| cost | One Budget covers selected validation/probe/copy/measure/finalization work. Real ordered map/string comparisons, allocations, and capture formatting remain separate costs. |
| Design | [build/verification/w06-aggregate-batch-design-v1/design.md](../../../../../build/verification/w06-aggregate-batch-design-v1/design.md), [docs/aggregates.md](../../../../aggregates.md), Refactor.md:1325-1327, [build/verification/w06-contract-assessment-v1/assessment.md](../../../../../build/verification/w06-contract-assessment-v1/assessment.md), [include/crown/resource/allocator.hpp](../../../../../include/crown/resource/allocator.hpp), [include/crown/resource/ownership.hpp](../../../../../include/crown/resource/ownership.hpp), [include/crown/resource/owner_allocator.hpp](../../../../../include/crown/resource/owner_allocator.hpp), [docs/aggregate_batches.md](../../../../aggregate_batches.md), [build/verification/aggregate-batch-acceptance-v1/findings.json](../../../../../build/verification/aggregate-batch-acceptance-v1/findings.json), [src/runtime/aggregate_integer.hpp](../../../../../src/runtime/aggregate_integer.hpp) |

## B0020

[Lines 207–207](../../../../../src/runtime/aggregate.cpp#L207); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
~Data() { rollback(); }
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Make successful active preparation destruction discard proposals and release its busy lease. |
| inputs / outputs | Destructor calls rollback(); no output. |
| invariants | After commit or explicit rollback live is false so destructor is inert. Active teardown clears proposals and busy before dropping owner. |
| ownership | Nodes/maps/tuples/output release through receiver-account owners; shared runtime reference is dropped. |
| failure | Noexcept rollback; no catch, retry, or recovery. |
| cost | Visits and releases proposal nodes, copied group vectors, keys/output; last-owner teardown may include committed runtime. |
| Design | [build/verification/w06-aggregate-batch-design-v1/design.md](../../../../../build/verification/w06-aggregate-batch-design-v1/design.md), [docs/aggregates.md](../../../../aggregates.md), Refactor.md:1325-1327, [build/verification/w06-contract-assessment-v1/assessment.md](../../../../../build/verification/w06-contract-assessment-v1/assessment.md), [include/crown/resource/allocator.hpp](../../../../../include/crown/resource/allocator.hpp), [include/crown/resource/ownership.hpp](../../../../../include/crown/resource/ownership.hpp), [include/crown/resource/owner_allocator.hpp](../../../../../include/crown/resource/owner_allocator.hpp), [docs/aggregate_batches.md](../../../../aggregate_batches.md), [build/verification/aggregate-batch-acceptance-v1/findings.json](../../../../../build/verification/aggregate-batch-acceptance-v1/findings.json), [src/runtime/aggregate_integer.hpp](../../../../../src/runtime/aggregate_integer.hpp) |

## B0021

[Lines 208–208](../../../../../src/runtime/aggregate.cpp#L208); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
bool active() const noexcept { return live; }
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Expose whether this token owns an active preparation. |
| inputs / outputs | Returns live. |
| invariants | Live denotes sealed preparation and the corresponding busy lease. |
| ownership | Reads inline state only. |
| failure | Noexcept/nonallocating. |
| cost | Constant. |
| Design | [build/verification/w06-aggregate-batch-design-v1/design.md](../../../../../build/verification/w06-aggregate-batch-design-v1/design.md), [docs/aggregates.md](../../../../aggregates.md), Refactor.md:1325-1327, [build/verification/w06-contract-assessment-v1/assessment.md](../../../../../build/verification/w06-contract-assessment-v1/assessment.md), [docs/aggregate_batches.md](../../../../aggregate_batches.md), [build/verification/aggregate-batch-acceptance-v1/findings.json](../../../../../build/verification/aggregate-batch-acceptance-v1/findings.json), [include/crown/resource/allocator.hpp](../../../../../include/crown/resource/allocator.hpp), [include/crown/resource/ownership.hpp](../../../../../include/crown/resource/ownership.hpp), [include/crown/resource/owner_allocator.hpp](../../../../../include/crown/resource/owner_allocator.hpp), [src/runtime/aggregate_integer.hpp](../../../../../src/runtime/aggregate_integer.hpp) |

## B0022

[Lines 209–211](../../../../../src/runtime/aggregate.cpp#L209); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
// Validation/projection, actual tuple copies and actual State preparations
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | State the one-batch Budget’s selected logical-work boundary. |
| inputs / outputs | Comment applies to validation/projection, tuple field/string copies, and State preparation. |
| invariants | Map/string comparisons keep actual costs outside Metrics.work; the counter is not a CPU-time or allocator-work bound. |
| ownership | No owner or state is created. |
| failure | No executable branch; Budget::take raises aggregate_work_limit during preparation. |
| cost | No executable cost from the comment; comparisons, allocator work, actual bytes, and teardown remain real. |
| Design | [build/verification/w06-aggregate-batch-design-v1/design.md](../../../../../build/verification/w06-aggregate-batch-design-v1/design.md), [docs/aggregates.md](../../../../aggregates.md), Refactor.md:1325-1327, [build/verification/w06-contract-assessment-v1/assessment.md](../../../../../build/verification/w06-contract-assessment-v1/assessment.md), [docs/aggregate_batches.md](../../../../aggregate_batches.md), [build/verification/aggregate-batch-acceptance-v1/findings.json](../../../../../build/verification/aggregate-batch-acceptance-v1/findings.json), [include/crown/resource/allocator.hpp](../../../../../include/crown/resource/allocator.hpp), [include/crown/resource/ownership.hpp](../../../../../include/crown/resource/ownership.hpp), [include/crown/resource/owner_allocator.hpp](../../../../../include/crown/resource/owner_allocator.hpp), [src/runtime/aggregate_integer.hpp](../../../../../src/runtime/aggregate_integer.hpp) |

## B0023

[Lines 212–219](../../../../../src/runtime/aggregate.cpp#L212); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void charge_copy(std::span<const Cell> values) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Charge each copied tuple field and string byte to the one batch logical-work budget. |
| inputs / outputs | For every Cell increments copied_fields/selected work; present string views also charge byte length and increment copied_bytes. |
| invariants | Copied counters do not measure comparison bytes or allocator requests. Called before key copies and after output rendering when retaining those tuples. |
| ownership | Reads live borrowed cells synchronously; retains none. |
| failure | Budget exhaustion stops private preparation before publication; local counters die with failed preparation. |
| cost | O(fields) visits plus string-length charge; actual tuple copy/allocation is separate. |
| Design | [build/verification/w06-aggregate-batch-design-v1/design.md](../../../../../build/verification/w06-aggregate-batch-design-v1/design.md), [docs/aggregates.md](../../../../aggregates.md), Refactor.md:1325-1327, [build/verification/w06-contract-assessment-v1/assessment.md](../../../../../build/verification/w06-contract-assessment-v1/assessment.md), [docs/aggregate_batches.md](../../../../aggregate_batches.md), [build/verification/aggregate-batch-acceptance-v1/findings.json](../../../../../build/verification/aggregate-batch-acceptance-v1/findings.json), [include/crown/resource/allocator.hpp](../../../../../include/crown/resource/allocator.hpp), [include/crown/resource/ownership.hpp](../../../../../include/crown/resource/ownership.hpp), [include/crown/resource/owner_allocator.hpp](../../../../../include/crown/resource/owner_allocator.hpp), [src/runtime/aggregate_integer.hpp](../../../../../src/runtime/aggregate_integer.hpp) |

## B0024

[Lines 220–223](../../../../../src/runtime/aggregate.cpp#L220); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Tuple copy_key(std::span<const Cell> values) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Freeze a new retained logical key after selected copy charging. |
| inputs / outputs | Borrowed nullable cells enter; immutable Tuple with copied payload under receiver leaves. |
| invariants | Used only when no committed row key can be shared and when group key cannot alias the row key by compiler-certified full-input grouping. |
| ownership | Returned tuple owns copied scalar/string cells; borrow ends at call return. |
| failure | Work, tuple capacity, or account failure precedes publication and unwinds private ownership. |
| cost | Linear fields/string bytes plus actual tuple allocation/copy and map comparisons. This path is not zero-heap. |
| Design | [build/verification/w06-aggregate-batch-design-v1/design.md](../../../../../build/verification/w06-aggregate-batch-design-v1/design.md), [docs/aggregates.md](../../../../aggregates.md), Refactor.md:1325-1327, [build/verification/w06-contract-assessment-v1/assessment.md](../../../../../build/verification/w06-contract-assessment-v1/assessment.md), [include/crown/resource/allocator.hpp](../../../../../include/crown/resource/allocator.hpp), [include/crown/resource/ownership.hpp](../../../../../include/crown/resource/ownership.hpp), [include/crown/resource/owner_allocator.hpp](../../../../../include/crown/resource/owner_allocator.hpp), [docs/aggregate_batches.md](../../../../aggregate_batches.md), [build/verification/aggregate-batch-acceptance-v1/findings.json](../../../../../build/verification/aggregate-batch-acceptance-v1/findings.json), [src/runtime/aggregate_integer.hpp](../../../../../src/runtime/aggregate_integer.hpp) |

## B0025

[Lines 224–241](../../../../../src/runtime/aggregate.cpp#L224); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
GroupProposal& touch_group(const Tuple& row) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Create or reuse exactly one proposal for a compiled group key touched by the batch. |
| inputs / outputs | Projects retained row through group column descriptors; returns existing proposal or inserts one with current iterator and copied/zeroed State vector. |
| invariants | Full-input alias only when compiler marks matching columns. Existing group State copies once; unique proposal-map key makes later rows reuse it. |
| ownership | Key projection borrows reusable scratch. New keys, proposal node, and vector use receiver; copied allocator matches persistent support_metadata. |
| failure | Projection work, tuple copy, vector or map allocation can fail only in private state; borrowed keys clear on unwind. |
| cost | Projection over group columns, ordered touched/committed map probes and their actual key/string comparisons, plus at most one O(measures) copy/init per group. |
| Design | [build/verification/w06-aggregate-batch-design-v1/design.md](../../../../../build/verification/w06-aggregate-batch-design-v1/design.md), [docs/aggregates.md](../../../../aggregates.md), Refactor.md:1325-1327, [build/verification/w06-contract-assessment-v1/assessment.md](../../../../../build/verification/w06-contract-assessment-v1/assessment.md), [include/crown/resource/allocator.hpp](../../../../../include/crown/resource/allocator.hpp), [include/crown/resource/ownership.hpp](../../../../../include/crown/resource/ownership.hpp), [include/crown/resource/owner_allocator.hpp](../../../../../include/crown/resource/owner_allocator.hpp), [docs/aggregate_batches.md](../../../../aggregate_batches.md), [build/verification/aggregate-batch-acceptance-v1/findings.json](../../../../../build/verification/aggregate-batch-acceptance-v1/findings.json), [src/runtime/aggregate_integer.hpp](../../../../../src/runtime/aggregate_integer.hpp) |

## B0026

[Lines 242–268](../../../../../src/runtime/aggregate.cpp#L242); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void touch(const RowDelta& delta) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Validate one unique nonzero delta against the committed row-weight ledger and queue its final row/group proposals. |
| inputs / outputs | Complete nullable cells, uint64 magnitude, erase direction and runtime schema/options enter; private row/group entries are added. |
| invariants | Validates type/nullability, uniqueness in this batch, retraction &lt;= committed before, uint64 addition, row count, and group proposal. It accepts no arbitrary repeated signed chain. |
| ownership | Borrowed input lasts through prepare only. New row key is receiver-copied; existing key shares immutable Tuple; group links are non-owning. |
| failure | Invalid row/zero/duplicate, mismatch, overflow, work, allocator or receiver failure precedes publication and busy latch. |
| cost | O(input fields/string admission) plus row/group ordered-map probes/comparisons and any new key/map allocations. |
| Design | [build/verification/w06-aggregate-batch-design-v1/design.md](../../../../../build/verification/w06-aggregate-batch-design-v1/design.md), [docs/aggregates.md](../../../../aggregates.md), Refactor.md:1325-1327, [build/verification/w06-contract-assessment-v1/assessment.md](../../../../../build/verification/w06-contract-assessment-v1/assessment.md), [docs/aggregate_batches.md](../../../../aggregate_batches.md), [build/verification/aggregate-batch-acceptance-v1/findings.json](../../../../../build/verification/aggregate-batch-acceptance-v1/findings.json), [include/crown/resource/allocator.hpp](../../../../../include/crown/resource/allocator.hpp), [include/crown/resource/ownership.hpp](../../../../../include/crown/resource/ownership.hpp), [include/crown/resource/owner_allocator.hpp](../../../../../include/crown/resource/owner_allocator.hpp), [src/runtime/aggregate_integer.hpp](../../../../../src/runtime/aggregate_integer.hpp) |

## B0027

[Lines 269–282](../../../../../src/runtime/aggregate.cpp#L269); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void adjust_rows(bool erasing) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Apply all retractions, then all additions, to private group counts and exact per-measure states. |
| inputs / outputs | Visits row proposals in two passes; matching direction updates its linked GroupProposal after-state. |
| invariants | Removal pass preserves a subbag of committed state; addition pass begins afterward and checks count_limit at every prefix. adjust&lt;false&gt; defers SUM(integer) range only; final groups check it in finalize. |
| ownership | Mutates only private receiver-funded proposals; row keys remain owned handles. |
| failure | Budget/count/int primitive failure unwinds before commit; final SUM range overflow occurs in finalization. |
| cost | Two O(touched rows) ordered-map walks and O(measures) exact arithmetic per changed row, independent of multiplicity. |
| Design | [build/verification/w06-aggregate-batch-design-v1/design.md](../../../../../build/verification/w06-aggregate-batch-design-v1/design.md), [docs/aggregates.md](../../../../aggregates.md), Refactor.md:1325-1327, [build/verification/w06-contract-assessment-v1/assessment.md](../../../../../build/verification/w06-contract-assessment-v1/assessment.md), src/runtime/aggregate_integer.hpp:112-149, [include/crown/frontend/aggregate.hpp](../../../../../include/crown/frontend/aggregate.hpp), [docs/aggregate_batches.md](../../../../aggregate_batches.md), [build/verification/aggregate-batch-acceptance-v1/findings.json](../../../../../build/verification/aggregate-batch-acceptance-v1/findings.json), [include/crown/resource/allocator.hpp](../../../../../include/crown/resource/allocator.hpp), [include/crown/resource/ownership.hpp](../../../../../include/crown/resource/ownership.hpp), [include/crown/resource/owner_allocator.hpp](../../../../../include/crown/resource/owner_allocator.hpp), [src/runtime/aggregate_integer.hpp](../../../../../src/runtime/aggregate_integer.hpp) |

## B0028

[Lines 283–289](../../../../../src/runtime/aggregate.cpp#L283); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Tuple render(const Tuple& key, const Group& group) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Render one old/final group output and charge its actual owned Tuple copy during preparation. |
| inputs / outputs | Group key, total count, measure States and shared Budget enter; immutable result Tuple leaves. |
| invariants | Uses compiled output descriptors and SQL NULL/COUNT/SUM/AVG semantics; only used when capture_changes is enabled. |
| ownership | Borrows key/state; returned Tuple owns copied output payload under receiver. |
| failure | Work, formatting, or account allocation failure remains private and leaves committed maps unchanged. |
| cost | Output-field visits plus exact decimal/AVG formatting, copy charging, Tuple copy/allocation, and later equality comparisons. |
| Design | [build/verification/w06-aggregate-batch-design-v1/design.md](../../../../../build/verification/w06-aggregate-batch-design-v1/design.md), [docs/aggregates.md](../../../../aggregates.md), Refactor.md:1325-1327, [build/verification/w06-contract-assessment-v1/assessment.md](../../../../../build/verification/w06-contract-assessment-v1/assessment.md), src/runtime/aggregate_integer.hpp:112-149, [include/crown/frontend/aggregate.hpp](../../../../../include/crown/frontend/aggregate.hpp), [docs/aggregate_batches.md](../../../../aggregate_batches.md), [build/verification/aggregate-batch-acceptance-v1/findings.json](../../../../../build/verification/aggregate-batch-acceptance-v1/findings.json), [include/crown/resource/allocator.hpp](../../../../../include/crown/resource/allocator.hpp), [include/crown/resource/ownership.hpp](../../../../../include/crown/resource/ownership.hpp), [include/crown/resource/owner_allocator.hpp](../../../../../include/crown/resource/owner_allocator.hpp), [src/runtime/aggregate_integer.hpp](../../../../../src/runtime/aggregate_integer.hpp) |

## B0029

[Lines 290–307](../../../../../src/runtime/aggregate.cpp#L290); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void finalize(const Tuple& key, GroupProposal& group) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Check each final touched group once, optionally retain its visible transition, and stage a new group node. |
| inputs / outputs | Touched group key and proposed state yield final SUM checks, optional before/after change, lifetime metrics, and detached insertion node if needed. |
| invariants | SUM(integer) is checked after the complete batch. Old/final render occurs at most once per group; absent group differs from NULL tuple; equal rounded output emits no event. |
| ownership | Captured Tuples and node are private receiver owners; existing immutable keys share handles. |
| failure | Final overflow, budget, formatting/comparison, vector/node/account failure all precede committed map changes. |
| cost | One final measure scan/group, up to two renders under capture, output comparison, and one state/node prepare for new surviving group. |
| Design | [build/verification/w06-aggregate-batch-design-v1/design.md](../../../../../build/verification/w06-aggregate-batch-design-v1/design.md), [docs/aggregates.md](../../../../aggregates.md), Refactor.md:1325-1327, [build/verification/w06-contract-assessment-v1/assessment.md](../../../../../build/verification/w06-contract-assessment-v1/assessment.md), [include/crown/resource/allocator.hpp](../../../../../include/crown/resource/allocator.hpp), [include/crown/resource/ownership.hpp](../../../../../include/crown/resource/ownership.hpp), [include/crown/resource/owner_allocator.hpp](../../../../../include/crown/resource/owner_allocator.hpp), [docs/aggregate_batches.md](../../../../aggregate_batches.md), [build/verification/aggregate-batch-acceptance-v1/findings.json](../../../../../build/verification/aggregate-batch-acceptance-v1/findings.json), [src/runtime/aggregate_integer.hpp](../../../../../src/runtime/aggregate_integer.hpp) |

## B0030

[Lines 308–334](../../../../../src/runtime/aggregate.cpp#L308); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
BatchEpoch commit() noexcept {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Publish the sealed row/group proposals and advance one contiguous sequence without reopening fallible preparation. |
| inputs / outputs | Prepared proposal maps, valid committed iterators, and same-target allocator node handles enter; committed rows/groups/sequence and owning BatchEpoch leave. |
| invariants | Inserts new nodes, erases by stable iterator, assigns existing weights/counts, swaps equal-allocator State vectors, then advances sequence once. No new arithmetic, formatting, allocation, admission, or work refill occurs. |
| ownership | Nodes transfer into committed maps; removed entries/replaced vectors release. Public commit moves out result then resets token storage promptly. |
| failure | Public token-liveness check precedes this noexcept section. Equal allocator and valid noexcept comparator premises make publication nonthrowing; assertions check internal invariants. |
| cost | O(D+G) proposal visits plus unhinted destination-map insertion searches: O(I_R*log(2+R0+I_R)) row-key comparisons and O(I_G*log(2+H0+I_G)) group-key comparisons, each with actual typed-field/string comparison cost; plus proposal/replaced-vector destruction and possible final-owner teardown. Node handles/swaps avoid allocation and State copy, not map searches. Comparisons/destruction are outside selected work metrics. |
| Design | [build/verification/w06-aggregate-batch-design-v1/design.md](../../../../../build/verification/w06-aggregate-batch-design-v1/design.md), [docs/aggregates.md](../../../../aggregates.md), Refactor.md:1325-1327, [build/verification/w06-contract-assessment-v1/assessment.md](../../../../../build/verification/w06-contract-assessment-v1/assessment.md), [include/crown/resource/allocator.hpp](../../../../../include/crown/resource/allocator.hpp), [include/crown/resource/ownership.hpp](../../../../../include/crown/resource/ownership.hpp), [include/crown/resource/owner_allocator.hpp](../../../../../include/crown/resource/owner_allocator.hpp), [docs/aggregate_batches.md](../../../../aggregate_batches.md), [build/verification/aggregate-batch-acceptance-v1/findings.json](../../../../../build/verification/aggregate-batch-acceptance-v1/findings.json), [src/runtime/aggregate_integer.hpp](../../../../../src/runtime/aggregate_integer.hpp) |

## B0031

[Lines 335–339](../../../../../src/runtime/aggregate.cpp#L335); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void rollback() noexcept {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Close an active preparation by discarding private proposals and releasing the runtime busy lease. |
| inputs / outputs | If live, clears row/group proposal entries, clears owner busy/live, and resets shared owner. |
| invariants | Committed maps/sequence remain unchanged; repeated rollback after closure does nothing. |
| ownership | Proposal nodes, copied vectors, keys/output, and owner ref release via their receiver-account owners. |
| failure | Noexcept cleanup; no allocation, budget, retry, or undo journal. |
| cost | Proposal teardown and possible final AggregateRuntime::Data destruction if facade is already gone. |
| Design | [build/verification/w06-aggregate-batch-design-v1/design.md](../../../../../build/verification/w06-aggregate-batch-design-v1/design.md), [docs/aggregates.md](../../../../aggregates.md), Refactor.md:1325-1327, [build/verification/w06-contract-assessment-v1/assessment.md](../../../../../build/verification/w06-contract-assessment-v1/assessment.md), [include/crown/resource/allocator.hpp](../../../../../include/crown/resource/allocator.hpp), [include/crown/resource/ownership.hpp](../../../../../include/crown/resource/ownership.hpp), [include/crown/resource/owner_allocator.hpp](../../../../../include/crown/resource/owner_allocator.hpp), [docs/aggregate_batches.md](../../../../aggregate_batches.md), [build/verification/aggregate-batch-acceptance-v1/findings.json](../../../../../build/verification/aggregate-batch-acceptance-v1/findings.json), [src/runtime/aggregate_integer.hpp](../../../../../src/runtime/aggregate_integer.hpp) |

## B0032

[Lines 340–341](../../../../../src/runtime/aggregate.cpp#L340); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L340-L341:sha256:cdbb10f75f6890449819c9d57e5ae7b786fb73c5111c5d829c37bc18f3e053e8
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Close the \`struct AggregateRuntime::PreparedBatch::Data\` scope at this exact source boundary. |
| inputs / outputs | This token introduces no callable inputs or outputs. Declarations inside \`struct AggregateRuntime::PreparedBatch::Data\` define the available names, members and operations. |
| invariants | The closing brace matches the opening \`struct AggregateRuntime::PreparedBatch::Data\` at its lexical source position in src/runtime/aggregate.cpp; it preserves C++ namespace/type nesting. |
| ownership | The closing delimiter creates no owner. Types closed by \`struct AggregateRuntime::PreparedBatch::Data\` retain the lifetimes and allocator rules of their own fields and operations. |
| failure | No failure path executes at this closing delimiter. Failure and cleanup behavior belong to enclosed functions and owning types. |
| cost | The delimiter itself performs no runtime work; the enclosed initializers, methods and destructors carry their own costs. |
| Design | [docs/aggregates.md](../../../../aggregates.md), [docs/aggregate_batches.md](../../../../aggregate_batches.md), [docs/query_memory.md](../../../../query_memory.md), [docs/code_specs/subsystem_contracts.md](../../../subsystem_contracts.md) |

## B0033

[Lines 342–345](../../../../../src/runtime/aggregate.cpp#L342); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
aggregate::BatchEpoch::BatchEpoch(const resource::MemoryAccount& account,
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Initialize BatchEpoch with target sequence, actual compiled program, and receiver-backed output vector. |
| inputs / outputs | MemoryAccount, next sequence, program handle, capture flag enter; empty result leaves. |
| invariants | Program is retained immutable metadata, not rebound. OutputVector uses OwnerAllocator with output_buffer attribution. |
| ownership | Program keeps original compiler account; output vector keeps receiving account; returned Tuple entries own their output. |
| failure | Construction is private to preparation; owner/account failures propagate before token exposure. |
| cost | Scalar/handle initialization; output capacity grows only for captured changed groups. |
| Design | [build/verification/w06-aggregate-batch-design-v1/design.md](../../../../../build/verification/w06-aggregate-batch-design-v1/design.md), [docs/aggregates.md](../../../../aggregates.md), Refactor.md:1325-1327, [build/verification/w06-contract-assessment-v1/assessment.md](../../../../../build/verification/w06-contract-assessment-v1/assessment.md), [include/crown/resource/allocator.hpp](../../../../../include/crown/resource/allocator.hpp), [include/crown/resource/ownership.hpp](../../../../../include/crown/resource/ownership.hpp), [include/crown/resource/owner_allocator.hpp](../../../../../include/crown/resource/owner_allocator.hpp), [docs/aggregate_batches.md](../../../../aggregate_batches.md), [build/verification/aggregate-batch-acceptance-v1/findings.json](../../../../../build/verification/aggregate-batch-acceptance-v1/findings.json), [src/runtime/aggregate_integer.hpp](../../../../../src/runtime/aggregate_integer.hpp) |

## B0034

[Lines 346–347](../../../../../src/runtime/aggregate.cpp#L346); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
static_assert(std::is_nothrow_move_constructible_v<aggregate::BatchEpoch>);
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Require BatchEpoch to move its schema/output owners without throwing after publication. |
| inputs / outputs | Compile-time trait check on BatchEpoch move construction. |
| invariants | Rejects compilation if public result transfer could throw after sequence is advanced. |
| ownership | No runtime owner is created. |
| failure | Compile-time only; no runtime fallback or handler. |
| cost | No runtime work or storage. |
| Design | [build/verification/w06-aggregate-batch-design-v1/design.md](../../../../../build/verification/w06-aggregate-batch-design-v1/design.md), [docs/aggregates.md](../../../../aggregates.md), Refactor.md:1325-1327, [build/verification/w06-contract-assessment-v1/assessment.md](../../../../../build/verification/w06-contract-assessment-v1/assessment.md), [include/crown/resource/allocator.hpp](../../../../../include/crown/resource/allocator.hpp), [include/crown/resource/ownership.hpp](../../../../../include/crown/resource/ownership.hpp), [include/crown/resource/owner_allocator.hpp](../../../../../include/crown/resource/owner_allocator.hpp), [docs/aggregate_batches.md](../../../../aggregate_batches.md), [build/verification/aggregate-batch-acceptance-v1/findings.json](../../../../../build/verification/aggregate-batch-acceptance-v1/findings.json), [src/runtime/aggregate_integer.hpp](../../../../../src/runtime/aggregate_integer.hpp) |

## B0035

[Lines 348–348](../../../../../src/runtime/aggregate.cpp#L348); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
AggregateRuntime::AggregateRuntime(std::shared_ptr<Data> value) noexcept
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Adopt an already accounted shared Data owner into the move-only facade. |
| inputs / outputs | std::shared_ptr&lt;Data&gt; moves into data_; same Data object backs the new facade. |
| invariants | No account is minted or state deep-copied; PreparedBatch may retain another reference beyond facade destruction. |
| ownership | Shared reference moves into facade; Data carries receiver/account state. |
| failure | Noexcept pointer move; allocation happened earlier. |
| cost | Constant handle move, no payload allocation. |
| Design | [include/crown/resource/ownership.hpp](../../../../../include/crown/resource/ownership.hpp), [docs/aggregates.md](../../../../aggregates.md) |

## B0036

[Lines 349–357](../../../../../src/runtime/aggregate.cpp#L349); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
AggregateRuntime AggregateRuntime::create_into(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Construct and initialize aggregate runtime state under a caller’s existing receiving account. |
| inputs / outputs | Live account, factory program and Options enter; initialized move-only facade leaves. |
| invariants | count_limit &lt;= INT64_MAX; receiver limit remains authoritative and is not refilled by standalone memory_limit_bytes. |
| ownership | make_accounted_shared charges one combined Data/control allocation to receiver; nested state also uses it; compiler metadata keeps original source account. |
| failure | Invalid program/options fail before owner allocation; any shared Data/member/initialize failure unwinds receiver payload. |
| cost | One combined shared allocation plus actual scratch/initial global or no-FROM nodes; no per-update account creation. |
| Design | [docs/aggregates.md](../../../../aggregates.md), [docs/query_memory.md](../../../../query_memory.md), [include/crown/resource/allocator.hpp](../../../../../include/crown/resource/allocator.hpp), [include/crown/resource/ownership.hpp](../../../../../include/crown/resource/ownership.hpp) |

## B0037

[Lines 358–359](../../../../../src/runtime/aggregate.cpp#L358); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
AggregateRuntime::AggregateRuntime(frontend::AggregateProgram program,
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Provide the standalone finite-account construction route. |
| inputs / outputs | An immutable program and Options enter; MemoryAccount::create(memory_limit_bytes) funds the runtime through create_into. |
| invariants | The limit is finite and includes its controller; it is created once for this standalone component, not on each update. |
| ownership | The newly created account survives through the runtime and any retained output owners; source metadata may have its own compiler account. |
| failure | Account/create_into failure propagates and releases private construction. |
| cost | One controller allocation plus create_into's actual construction costs. |
| Design | [docs/aggregates.md](../../../../aggregates.md), [docs/query_memory.md](../../../../query_memory.md), [include/crown/resource/allocator.hpp](../../../../../include/crown/resource/allocator.hpp) |

## B0038

[Lines 360–362](../../../../../src/runtime/aggregate.cpp#L360); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
AggregateRuntime::AggregateRuntime(AggregateRuntime&&) noexcept = default;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Move the facade’s shared Data reference without rebuilding aggregate state. |
| inputs / outputs | Rvalue transfers its facade handle; source becomes empty. |
| invariants | Maps/sequence stay intact; active token keeps Data/busy across facade move. |
| ownership | One shared_ptr handle transfers; token may retain another reference. |
| failure | Noexcept default move. |
| cost | Constant handle transfer, no payload copy/allocation. |
| Design | [include/crown/runtime/aggregate.hpp](../../../../../include/crown/runtime/aggregate.hpp), [include/crown/resource/ownership.hpp](../../../../../include/crown/resource/ownership.hpp) |

```text
AggregateRuntime& AggregateRuntime::operator=(AggregateRuntime&&) noexcept = default;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Drop the destination facade reference and move in the source runtime handle. |
| inputs / outputs | Rvalue facade enters; destination adopts its Data and source empties. |
| invariants | Old Data is destroyed only if no token retains it; active token can preserve old owner/busy after facade replacement. |
| ownership | Shared-reference transfer/drop; no runtime rebuild. |
| failure | Defaulted move assignment is noexcept under valid owner destruction. |
| cost | Constant handle transfer unless its destination drops the final owner reference, which destroys committed rows/groups/scratch. An active prepared token retains its own owner reference and delays that teardown until close; proposals are owned by the token, not by the facade. |
| Design | [include/crown/resource/ownership.hpp](../../../../../include/crown/resource/ownership.hpp), [docs/aggregates.md](../../../../aggregates.md) |

```text
AggregateRuntime::~AggregateRuntime() = default;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Drop the facade shared Data reference. |
| inputs / outputs | Live/empty facade destructs; token/result owners may remain. |
| invariants | An active PreparedBatch can keep Data and busy alive after facade death; destruction does not force rollback while token owns it. |
| ownership | Last shared reference destroys committed Data; token can postpone that until close. |
| failure | Nonthrowing reference cleanup; no recovery or allocation. |
| cost | Fixed shared-reference drop, or final committed row/group/scratch teardown. An active token prevents this facade release from being the final owner reference; its proposal cleanup happens at token close. |
| Design | [docs/aggregates.md](../../../../aggregates.md), [docs/query_memory.md](../../../../query_memory.md), [include/crown/resource/allocator.hpp](../../../../../include/crown/resource/allocator.hpp) |

## B0039

[Lines 363–366](../../../../../src/runtime/aggregate.cpp#L363); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
AggregateRuntime::Data& AggregateRuntime::data() const
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Reject empty moved-from facade before borrowing its shared Data. |
| inputs / outputs | Facade enters; Data reference leaves for internal access, including const routes that use scratch. |
| invariants | Operations remain serialized. This access does not require idle, so committed getters/statistics can be used while busy; reference must not outlive facade/token owners. |
| ownership | Borrowed reference is backed by facade shared_ptr; token can retain Data independently. |
| failure | invalid_aggregate_runtime rejects empty data_; no owner is fabricated. |
| cost | Fixed null/pointer access, no allocation. |
| Design | [include/crown/runtime/aggregate.hpp](../../../../../include/crown/runtime/aggregate.hpp), [docs/aggregates.md](../../../../aggregates.md) |

## B0040

[Lines 367–367](../../../../../src/runtime/aggregate.cpp#L367); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
const frontend::AggregateProgram& AggregateRuntime::program() const &
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Borrow immutable compiled aggregate descriptors without deep copy or rebind. |
| inputs / outputs | Live lvalue facade returns const AggregateProgram reference. |
| invariants | Readable while busy and remains committed immutable program; rvalue access deleted; no physical/compiler certification added. |
| ownership | Reference stays backed while facade or active token retains Data; caller can copy handle for independent metadata lifetime. |
| failure | Empty facade error propagates. |
| cost | Fixed reference access, no allocation. |
| Design | [include/crown/runtime/aggregate.hpp](../../../../../include/crown/runtime/aggregate.hpp), [include/crown/frontend/aggregate.hpp](../../../../../include/crown/frontend/aggregate.hpp) |

## B0041

[Lines 368–368](../../../../../src/runtime/aggregate.cpp#L368); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::uint64_t AggregateRuntime::sequence() const
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Read the last committed epoch while a private batch preview may be pending. |
| inputs / outputs | Live facade returns uint64 scalar. |
| invariants | Pending token does not advance sequence; commit advances once; failure/rollback leaves it unchanged. |
| ownership | Scalar has no payload; token can keep Data alive after facade death. |
| failure | Empty facade rejected; busy does not reject getter. |
| cost | Constant scalar read. |
| Design | [docs/aggregates.md](../../../../aggregates.md), [Refactor.md §11.9 W04](../../../../../Refactor.md) |

## B0042

[Lines 369–376](../../../../../src/runtime/aggregate.cpp#L369); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
aggregate::Epoch AggregateRuntime::apply(const aggregate::Update& update)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Adapt one borrowed nullable DTO into the existing single-row weight replacement path. |
| inputs / outputs | Next sequence, borrowed optional Values and before/after weights enter; Epoch leaves. |
| invariants | open rejects busy first. Otherwise arity/type/prior weight precede publication; immediate SUM check remains. Input/key borrows clear on exit. |
| ownership | DTO strings borrowed during call; retained keys/output are receiver copies. |
| failure | Busy/conversion/admission/work/account/SUM failure preserves committed state; no catch/retry. |
| cost | O(input width) conversion/validation/cleanup plus single-row costs; no batch proposal map. |
| Design | [docs/aggregates.md](../../../../aggregates.md), [docs/weighted_enumeration.md](../../../../weighted_enumeration.md), [include/crown/storage/accounted_row.hpp](../../../../../include/crown/storage/accounted_row.hpp) |

## B0043

[Lines 377–384](../../../../../src/runtime/aggregate.cpp#L377); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
aggregate::Epoch AggregateRuntime::apply_weighted(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Consume W03 compressed tuple values directly for one single-row logical replacement. |
| inputs / outputs | Next sequence, TupleValuesView, exact before/after weights enter; Epoch leaves. |
| invariants | open rejects active token first; existing compiled schema/sequence/count/immediate-SUM rules remain. |
| ownership | View borrows/retains producer payload synchronously; scratch views clear before return; no DTO export or row expansion. |
| failure | Busy or view/admission/work/arithmetic/account failure precedes publication. |
| cost | O(input width) descriptor copies plus existing single-row/map costs; no batch structures. |
| Design | [docs/aggregates.md](../../../../aggregates.md), [docs/weighted_enumeration.md](../../../../weighted_enumeration.md), [include/crown/storage/tuple_values.hpp](../../../../../include/crown/storage/tuple_values.hpp) |

## B0044

[Lines 385–391](../../../../../src/runtime/aggregate.cpp#L385); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
AggregateRuntime::PreparedBatch AggregateRuntime::prepare_batch(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Open the one sequence-bound budget, build all private preparation state, then latch the shared owner busy. |
| inputs / outputs | NetBatch and live facade enter; move-only PreparedBatch returns only after private Data construction succeeds. |
| invariants | open checks idle/source/next sequence. Busy is set after all throwing preparation; committed sequence stays old while token is previewed. |
| ownership | Prepared token retains shared Data and can outlive/move independently of facade. Caller cell/string views expire at method return. |
| failure | Source/sequence/busy/row/work/count/SUM/account/allocation errors happen before busy/token exposure; state is unchanged. |
| cost | One account-funded preparation Data allocation plus proposal/key/group/result allocations and actual map/string comparison costs. |
| Design | [build/verification/w06-aggregate-batch-design-v1/design.md](../../../../../build/verification/w06-aggregate-batch-design-v1/design.md), [docs/aggregates.md](../../../../aggregates.md), Refactor.md:1325-1327, [build/verification/w06-contract-assessment-v1/assessment.md](../../../../../build/verification/w06-contract-assessment-v1/assessment.md), [include/crown/resource/allocator.hpp](../../../../../include/crown/resource/allocator.hpp), [include/crown/resource/ownership.hpp](../../../../../include/crown/resource/ownership.hpp), [include/crown/resource/owner_allocator.hpp](../../../../../include/crown/resource/owner_allocator.hpp), [docs/aggregate_batches.md](../../../../aggregate_batches.md), [build/verification/aggregate-batch-acceptance-v1/findings.json](../../../../../build/verification/aggregate-batch-acceptance-v1/findings.json), [src/runtime/aggregate_integer.hpp](../../../../../src/runtime/aggregate_integer.hpp) |

## B0045

[Lines 392–393](../../../../../src/runtime/aggregate.cpp#L392); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
AggregateRuntime::PreparedBatch::PreparedBatch(resource::AccountedUnique<Data> value) noexcept
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Adopt privately constructed preparation ownership into its public token. |
| inputs / outputs | AccountedUnique&lt;PreparedBatch::Data&gt; moves into data_. |
| invariants | Called only after complete preparation and busy latch. |
| ownership | Token takes unique Data ownership; that Data retains the aggregate owner. |
| failure | Noexcept move with no new admission. |
| cost | Constant. |
| Design | [build/verification/w06-aggregate-batch-design-v1/design.md](../../../../../build/verification/w06-aggregate-batch-design-v1/design.md), [docs/aggregates.md](../../../../aggregates.md), Refactor.md:1325-1327, [build/verification/w06-contract-assessment-v1/assessment.md](../../../../../build/verification/w06-contract-assessment-v1/assessment.md), [include/crown/resource/allocator.hpp](../../../../../include/crown/resource/allocator.hpp), [include/crown/resource/ownership.hpp](../../../../../include/crown/resource/ownership.hpp), [include/crown/resource/owner_allocator.hpp](../../../../../include/crown/resource/owner_allocator.hpp), [docs/aggregate_batches.md](../../../../aggregate_batches.md), [build/verification/aggregate-batch-acceptance-v1/findings.json](../../../../../build/verification/aggregate-batch-acceptance-v1/findings.json), [src/runtime/aggregate_integer.hpp](../../../../../src/runtime/aggregate_integer.hpp) |

## B0046

[Lines 394–396](../../../../../src/runtime/aggregate.cpp#L394); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
AggregateRuntime::PreparedBatch::PreparedBatch(PreparedBatch&&) noexcept = default;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Transfer or release a prepared token through default move-only RAII operations. |
| inputs / outputs | Move construction/assignment transfer AccountedUnique; destruction releases it and rolls back if active. |
| invariants | Moved-from is inactive. Replacing an active token destroys/rolls back it first; token Data may keep shared runtime alive beyond facade. |
| ownership | Unique token Data owns proposals; its shared owner reference keeps runtime/account alive. |
| failure | Move operations/destruction are noexcept; destructor discards private state only. |
| cost | Handle transfer is constant; active replacement/destruction tears down proposals and may final-release runtime. |
| Design | [build/verification/w06-aggregate-batch-design-v1/design.md](../../../../../build/verification/w06-aggregate-batch-design-v1/design.md), [docs/aggregates.md](../../../../aggregates.md), Refactor.md:1325-1327, [build/verification/w06-contract-assessment-v1/assessment.md](../../../../../build/verification/w06-contract-assessment-v1/assessment.md), [include/crown/resource/allocator.hpp](../../../../../include/crown/resource/allocator.hpp), [include/crown/resource/ownership.hpp](../../../../../include/crown/resource/ownership.hpp), [include/crown/resource/owner_allocator.hpp](../../../../../include/crown/resource/owner_allocator.hpp), [docs/aggregate_batches.md](../../../../aggregate_batches.md), [build/verification/aggregate-batch-acceptance-v1/findings.json](../../../../../build/verification/aggregate-batch-acceptance-v1/findings.json), [src/runtime/aggregate_integer.hpp](../../../../../src/runtime/aggregate_integer.hpp) |

## B0047

[Lines 397–400](../../../../../src/runtime/aggregate.cpp#L397); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
AggregateRuntime::PreparedBatch::Data& AggregateRuntime::PreparedBatch::data() const
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Reject invalid token operations before any publication step. |
| inputs / outputs | Returns token Data only when nonempty and active. |
| invariants | Closed/moved-from tokens cannot preview or commit. |
| ownership | Returns a borrowed reference valid while this token survives unchanged. |
| failure | invalid_aggregate_batch occurs before internal commit, never after a partial publication. |
| cost | Constant pointer/live tests. |
| Design | [build/verification/w06-aggregate-batch-design-v1/design.md](../../../../../build/verification/w06-aggregate-batch-design-v1/design.md), [docs/aggregates.md](../../../../aggregates.md), Refactor.md:1325-1327, [build/verification/w06-contract-assessment-v1/assessment.md](../../../../../build/verification/w06-contract-assessment-v1/assessment.md), [docs/aggregate_batches.md](../../../../aggregate_batches.md), [build/verification/aggregate-batch-acceptance-v1/findings.json](../../../../../build/verification/aggregate-batch-acceptance-v1/findings.json), [include/crown/resource/allocator.hpp](../../../../../include/crown/resource/allocator.hpp), [include/crown/resource/ownership.hpp](../../../../../include/crown/resource/ownership.hpp), [include/crown/resource/owner_allocator.hpp](../../../../../include/crown/resource/owner_allocator.hpp), [src/runtime/aggregate_integer.hpp](../../../../../src/runtime/aggregate_integer.hpp) |

## B0048

[Lines 401–401](../../../../../src/runtime/aggregate.cpp#L401); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
bool AggregateRuntime::PreparedBatch::active() const noexcept
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Expose public token liveness without throwing. |
| inputs / outputs | Returns data_ presence and Data::active(). |
| invariants | Empty/moved/closed token reports false. |
| ownership | Reads owned token Data only. |
| failure | Noexcept/nonallocating. |
| cost | Constant. |
| Design | [build/verification/w06-aggregate-batch-design-v1/design.md](../../../../../build/verification/w06-aggregate-batch-design-v1/design.md), [docs/aggregates.md](../../../../aggregates.md), Refactor.md:1325-1327, [build/verification/w06-contract-assessment-v1/assessment.md](../../../../../build/verification/w06-contract-assessment-v1/assessment.md), [docs/aggregate_batches.md](../../../../aggregate_batches.md), [build/verification/aggregate-batch-acceptance-v1/findings.json](../../../../../build/verification/aggregate-batch-acceptance-v1/findings.json), [include/crown/resource/allocator.hpp](../../../../../include/crown/resource/allocator.hpp), [include/crown/resource/ownership.hpp](../../../../../include/crown/resource/ownership.hpp), [include/crown/resource/owner_allocator.hpp](../../../../../include/crown/resource/owner_allocator.hpp), [src/runtime/aggregate_integer.hpp](../../../../../src/runtime/aggregate_integer.hpp) |

## B0049

[Lines 402–402](../../../../../src/runtime/aggregate.cpp#L402); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
const aggregate::BatchEpoch& AggregateRuntime::PreparedBatch::preview() const &
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Borrow the completed immutable batch preview. |
| inputs / outputs | Returns lvalue reference to sealed BatchEpoch after liveness validation. |
| invariants | Preview has final outputs/metrics; committed sequence has not advanced before commit. |
| ownership | Borrow expires on token move/commit/rollback/death; explicitly copied Tuple/program handles own independently. |
| failure | Invalid token rejects before returning a reference. |
| cost | Constant; no output clone. |
| Design | [build/verification/w06-aggregate-batch-design-v1/design.md](../../../../../build/verification/w06-aggregate-batch-design-v1/design.md), [docs/aggregates.md](../../../../aggregates.md), Refactor.md:1325-1327, [build/verification/w06-contract-assessment-v1/assessment.md](../../../../../build/verification/w06-contract-assessment-v1/assessment.md), [docs/aggregate_batches.md](../../../../aggregate_batches.md), [build/verification/aggregate-batch-acceptance-v1/findings.json](../../../../../build/verification/aggregate-batch-acceptance-v1/findings.json), [include/crown/resource/allocator.hpp](../../../../../include/crown/resource/allocator.hpp), [include/crown/resource/ownership.hpp](../../../../../include/crown/resource/ownership.hpp), [include/crown/resource/owner_allocator.hpp](../../../../../include/crown/resource/owner_allocator.hpp), [src/runtime/aggregate_integer.hpp](../../../../../src/runtime/aggregate_integer.hpp) |

## B0050

[Lines 403–405](../../../../../src/runtime/aggregate.cpp#L403); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
aggregate::BatchEpoch AggregateRuntime::PreparedBatch::commit()
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Return the owning batch result after one checked nonthrowing publication, then promptly release private token storage. |
| inputs / outputs | Live token enters; committed BatchEpoch owning output/program handle leaves. |
| invariants | data() validates before commit. Internal publication advances sequence once; public method resets data_ after moving result so proposal maps/private storage free promptly. |
| ownership | Returned BatchEpoch owns its program/Tuple/output handles. Internal commit drops token’s shared runtime ref; facade can remain or already be gone. |
| failure | Closed token fails before publication; after liveness check, noexcept commit and no-throw result move leave no post-publication error path. |
| cost | Publication has map-search/teardown costs from B0043; moving result is handle transfer, and data_.reset frees private Data/proposals while returned output remains owned. |
| Design | [build/verification/w06-aggregate-batch-design-v1/design.md](../../../../../build/verification/w06-aggregate-batch-design-v1/design.md), [docs/aggregates.md](../../../../aggregates.md), Refactor.md:1325-1327, [build/verification/w06-contract-assessment-v1/assessment.md](../../../../../build/verification/w06-contract-assessment-v1/assessment.md), [include/crown/resource/allocator.hpp](../../../../../include/crown/resource/allocator.hpp), [include/crown/resource/ownership.hpp](../../../../../include/crown/resource/ownership.hpp), [include/crown/resource/owner_allocator.hpp](../../../../../include/crown/resource/owner_allocator.hpp), [docs/aggregate_batches.md](../../../../aggregate_batches.md), [build/verification/aggregate-batch-acceptance-v1/findings.json](../../../../../build/verification/aggregate-batch-acceptance-v1/findings.json), [src/runtime/aggregate_integer.hpp](../../../../../src/runtime/aggregate_integer.hpp) |

## B0051

[Lines 406–406](../../../../../src/runtime/aggregate.cpp#L406); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void AggregateRuntime::PreparedBatch::rollback() noexcept
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Explicitly close a token through its nonthrowing RAII cleanup path. |
| inputs / outputs | No arguments; resets private unique owner if present. |
| invariants | Active rollback clears proposal state/busy and preserves committed sequence; empty token is harmless. |
| ownership | Private Data and its shared runtime reference release; facade may already be gone. |
| failure | Noexcept; never reverses already published state. |
| cost | Proposal teardown and possible final runtime owner destruction; no allocation. |
| Design | [build/verification/w06-aggregate-batch-design-v1/design.md](../../../../../build/verification/w06-aggregate-batch-design-v1/design.md), [docs/aggregates.md](../../../../aggregates.md), Refactor.md:1325-1327, [build/verification/w06-contract-assessment-v1/assessment.md](../../../../../build/verification/w06-contract-assessment-v1/assessment.md), [include/crown/resource/allocator.hpp](../../../../../include/crown/resource/allocator.hpp), [include/crown/resource/ownership.hpp](../../../../../include/crown/resource/ownership.hpp), [include/crown/resource/owner_allocator.hpp](../../../../../include/crown/resource/owner_allocator.hpp), [docs/aggregate_batches.md](../../../../aggregate_batches.md), [build/verification/aggregate-batch-acceptance-v1/findings.json](../../../../../build/verification/aggregate-batch-acceptance-v1/findings.json), [src/runtime/aggregate_integer.hpp](../../../../../src/runtime/aggregate_integer.hpp) |

## B0052

[Lines 407–414](../../../../../src/runtime/aggregate.cpp#L407); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
aggregate::Snapshot AggregateRuntime::snapshot(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Build the explicit bounded snapshot only when shared scratch is idle. |
| inputs / outputs | Group/work limits in; receiver-funded Snapshot holds sequence/program/shared keys/copied outputs. |
| invariants | require_idle precedes output scratch; global empty stays one result, grouped empty none; internal key order is not SQL ORDER BY. |
| ownership | Snapshot result storage/tuples use receiver and can outlive facade; program retains compiler metadata. |
| failure | aggregate_busy/result/work/format/account failure drops partial snapshot without query mutation. |
| cost | Busy check plus O(groups*output width + bytes/formatting) and vector/tuple allocation; explicit collection only. |
| Design | [docs/aggregates.md](../../../../aggregates.md), [Refactor.md §11.9 W04](../../../../../Refactor.md), [src/runtime/aggregate_tuple.cpp](../../../../../src/runtime/aggregate_tuple.cpp) |

## B0053

[Lines 415–415](../../../../../src/runtime/aggregate.cpp#L415); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
resource::MemoryStatistics AggregateRuntime::accounted_memory_statistics() const
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Read current/history counters from the shared receiving account, including during preparation. |
| inputs / outputs | Live facade returns fixed-size MemoryStatistics. |
| invariants | Busy does not reject; counters include token proposal maps, copied keys, result/output reservations and all shared receiver owners, not a committed-only snapshot. Compiler account remains separate. |
| ownership | Report retains no payload; facade/token backs Data/account during access. |
| failure | Empty facade/account error propagates; stats do not commit or mutate budget. |
| cost | Fixed counter read, no allocation-ledger/map scan. |
| Design | [src/resource/memory.cpp](../../../../../src/resource/memory.cpp), [docs/query_memory.md](../../../../query_memory.md), [docs/aggregates.md](../../../../aggregates.md) |

## B0054

[Lines 416–457](../../../../../src/runtime/aggregate.cpp#L416); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void AggregateRuntime::check_invariants() const
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Recompute committed aggregate state explicitly only while no token owns shared scratch. |
| inputs / outputs | Validates no-FROM shape, complete rows/types/weights, group identities/counts, per-measure counts/sums/SUM range and receiver ledger. |
| invariants | require_idle rejects busy. Diagnostic remains outside update path; wide sums accumulate before final range checks so cancelling rows may appear in any key order. |
| ownership | Expected maps/keys/vectors use receiver; committed maps stay read-only; borrowed key scratch clears on unwind. |
| failure | aggregate_busy first; invariant/account/allocation failure releases temporary state and changes no committed data; no recovery. |
| cost | Busy check plus full distinct row/group traversal, ordered comparisons, measures, temporary allocations and account scan. |
| Design | [docs/aggregates.md](../../../../aggregates.md), [Refactor.md §11.9 W04](../../../../../Refactor.md), [src/resource/memory.cpp](../../../../../src/resource/memory.cpp) |

```text
if (!value.program.has_input() && (value.rows.size() != 1
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Check that no-FROM state still represents exactly SQL's one implicit nullary input row. |
| inputs / outputs | Program source mode and committed row map enter; the no-FROM map must have one zero-width key at weight one. |
| invariants | Short-circuit evaluation prevents begin() dereference unless size is exactly one. |
| ownership | The map and tuple key are only inspected; no input owner is changed. |
| failure | aggregate_invariant reports a malformed implicit singleton. |
| cost | Fixed map-size, width and weight checks, with no allocation. |
| Design | [docs/aggregates.md](../../../../aggregates.md), [Refactor.md §11.9 W04](../../../../../Refactor.md) |

```text
// Diagnostic recomputation can visit cancelling rows in any key order.
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Rebuild exact non-NULL counts and wide numerators independently of incremental result-range gating. |
| inputs / outputs | Each valid committed row and weight contributes to its temporary expected group's measure states. |
| invariants | Expected total count is admitted first; all partial numerators obey the private bound. Intermediate SUM(integer) may exceed bigint before later cancellation, so only completed sums are range checked. |
| ownership | Statistics remain inline within temporary accounted group vectors; argument references borrow the committed row or immutable constant backing. |
| failure | Malformed stored rows/count bounds fail before this block; it adds no per-measure catch or rollback. |
| cost | O(distinct measures) fixed arithmetic per distinct input row, independent of its multiplicity. |
| Design | [docs/aggregates.md](../../../../aggregates.md), [src/runtime/aggregate_integer.hpp](../../../../../src/runtime/aggregate_integer.hpp) |

```text
if (expected.size() != value.groups.size())
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Require exact group membership, row counts, statistic shape, non-NULL counts, and signed sums after recomputation. |
| inputs / outputs | Temporary expected groups probe committed groups; mismatches or completed SUM(integer) range violations raise aggregate_invariant. |
| invariants | Equal group count plus finding every expected key establishes membership equality. Decimal sum comparison is exact at scale zero, not floating point. |
| ownership | The two group maps are only borrowed during comparison; no output snapshot is retained. |
| failure | Mismatch or account ledger failure propagates; temporary expected allocations release on exit. |
| cost | O(groups times ordered lookup/measure comparison) plus bounded decimal formatting of each compared numerator and explicit account-ledger validation. |
| Design | [docs/aggregates.md](../../../../aggregates.md), [src/runtime/aggregate_integer.hpp](../../../../../src/runtime/aggregate_integer.hpp), [src/resource/memory.cpp](../../../../../src/resource/memory.cpp) |

## B0055

[Lines 458–458](../../../../../src/runtime/aggregate.cpp#L458); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L458-L458:sha256:97734ee3ed73fbf0bd112ff8fee5fae528737ea20327081d48b1efcf3f9b9a5a
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Close the \`namespace crown::runtime\` scope at this exact source boundary. |
| inputs / outputs | This token introduces no callable inputs or outputs. Declarations inside \`namespace crown::runtime\` define the available names, members and operations. |
| invariants | The closing brace matches the opening \`namespace crown::runtime\` at its lexical source position in src/runtime/aggregate.cpp; it preserves C++ namespace/type nesting. |
| ownership | The closing delimiter creates no owner. Types closed by \`namespace crown::runtime\` retain the lifetimes and allocator rules of their own fields and operations. |
| failure | No failure path executes at this closing delimiter. Failure and cleanup behavior belong to enclosed functions and owning types. |
| cost | The delimiter itself performs no runtime work; the enclosed initializers, methods and destructors carry their own costs. |
| Design | [docs/aggregates.md](../../../../aggregates.md), [docs/aggregate_batches.md](../../../../aggregate_batches.md), [docs/query_memory.md](../../../../query_memory.md), [docs/code_specs/subsystem_contracts.md](../../../subsystem_contracts.md) |
