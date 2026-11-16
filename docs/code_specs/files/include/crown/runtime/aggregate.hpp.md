# `include/crown/runtime/aggregate.hpp` — block usage map

[Source](../../../../../../include/crown/runtime/aggregate.hpp) · [Source index](../../../../README.md) · [Subsystem contracts](../../../../subsystem_contracts.md) · [Reviewed primitives](../../../../primitives.md)

Declare nullable owning aggregate tuples, grouped state, atomic prepared batches and owning output.

Snapshot SHA-256: `93a5599fe10b3a15294d91a976378fb720054b67189a2d219ea0844d1b9488a0`. 167 lines partitioned into 20 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [support](../../../../subsystem_contracts.md#support). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/support_invariants.md](../../../../../support_invariants.md), [docs/runtime_support.md](../../../../../runtime_support.md), [docs/prepared_epochs.md](../../../../../prepared_epochs.md), [docs/result_cursors.md](../../../../../result_cursors.md), [docs/epoch_views.md](../../../../../epoch_views.md), [docs/code_review.md](../../../../../code_review.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–19](../../../../../../include/crown/runtime/aggregate.hpp#L1) | Imports dependencies; guards repeated header inclusion; declares namespace scope; declares aliases; declares types or opens a type body; declares values/defaults or compile-time conditions. | source comment (unverified): // SQL NULL cells stay outside the classical core row type. One owned payload · [reviewed contract](#b0001) |
| [B0002 · 20–38](../../../../../../include/crown/runtime/aggregate.hpp#L20) | Type/record definition: class Tuple | returns bool(data_); growth copy_of; source comment (unverified): // SQL NULL cells stay outside the classical core row type. One owned payload · [reviewed contract](#b0002) |
| [B0003 · 39–39](../../../../../../include/crown/runtime/aggregate.hpp#L39) | Explanatory comments or spacing. |  |
| [B0004 · 40–46](../../../../../../include/crown/runtime/aggregate.hpp#L40) | Type/record definition: struct Options | source comment (unverified): // Used only for standalone construction. _into keeps its receiving grant. · [reviewed contract](#b0004) |
| [B0005 · 47–51](../../../../../../include/crown/runtime/aggregate.hpp#L47) | Type/record definition: struct Update | source comment (unverified): // Borrowed for the synchronous call only. · [reviewed contract](#b0005) |
| [B0006 · 52–54](../../../../../../include/crown/runtime/aggregate.hpp#L52) | Explanatory comments or spacing. | source comment (unverified): // A decoded logical bag delta. Inputs must have unique complete nullable row · [reviewed contract](#b0006) |
| [B0007 · 55–59](../../../../../../include/crown/runtime/aggregate.hpp#L55) | Type/record definition: struct RowDelta | source comment (unverified): // A decoded logical bag delta. Inputs must have unique complete nullable row · [reviewed contract](#b0007) |
| [B0008 · 60–63](../../../../../../include/crown/runtime/aggregate.hpp#L60) | Type/record definition: struct NetBatch |  · [reviewed contract](#b0008) |
| [B0009 · 64–69](../../../../../../include/crown/runtime/aggregate.hpp#L64) | Type/record definition: struct Metrics | source comment (unverified): // Selected logical charges; not elapsed CPU or every map/string comparison. · [reviewed contract](#b0009) |
| [B0010 · 70–70](../../../../../../include/crown/runtime/aggregate.hpp#L70) | Explanatory comments or spacing. | source comment (unverified): // Keep batch-only counters out of the single-row Metrics/Epoch value layout. · [reviewed contract](#b0010) |
| [B0011 · 71–74](../../../../../../include/crown/runtime/aggregate.hpp#L71) | Type/record definition: struct BatchMetrics : Metrics | source comment (unverified): // Keep batch-only counters out of the single-row Metrics/Epoch value layout. · [reviewed contract](#b0011) |
| [B0012 · 75–78](../../../../../../include/crown/runtime/aggregate.hpp#L75) | Type/record definition: struct GroupChange | source comment (unverified): // Absent group differs from NULL cells. · [reviewed contract](#b0012) |
| [B0013 · 79–85](../../../../../../include/crown/runtime/aggregate.hpp#L79) | Type/record definition: struct Epoch | source comment (unverified): // Input weight changed, independently of rounded output. · [reviewed contract](#b0013) |
| [B0014 · 86–94](../../../../../../include/crown/runtime/aggregate.hpp#L86) | Type/record definition: struct BatchEpoch |  · [reviewed contract](#b0014) |
| [B0015 · 95–95](../../../../../../include/crown/runtime/aggregate.hpp#L95) | Type/record definition: struct GroupResult |  · [reviewed contract](#b0015) |
| [B0016 · 96–101](../../../../../../include/crown/runtime/aggregate.hpp#L96) | Type/record definition: struct Snapshot |  · [reviewed contract](#b0016) |
| [B0017 · 102–105](../../../../../../include/crown/runtime/aggregate.hpp#L102) | Type/record definition: struct SnapshotLimits |  · [reviewed contract](#b0017) |
| [B0018 · 106–115](../../../../../../include/crown/runtime/aggregate.hpp#L106) | declares namespace scope; declares types or opens a type body. | source comment (unverified): // namespace crown::runtime::aggregate · [reviewed contract](#b0018) |
| [B0019 · 116–137](../../../../../../include/crown/runtime/aggregate.hpp#L116) | Type/record definition: public: class PreparedBatch | source comment (unverified): // Borrowed until this token moves, commits, rolls back, or dies. Copy the · [reviewed contract](#b0019) |
| [B0020 · 138–167](../../../../../../include/crown/runtime/aggregate.hpp#L138) | declares callable signatures; declares values/defaults or compile-time conditions. | source comment (unverified): // W03's compressed tuples can enter without an owning nullable DTO export. · [reviewed contract](#b0020) |

## B0001

[Lines 1–19](../../../../../../include/crown/runtime/aggregate.hpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
using Cell =
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Keep nullable SQL cells and explicit caller exports outside classical core values. |
| inputs / outputs | Cell is optional ScalarView; SqlValue is optional Value; Row is a standard owning export vector. |
| invariants | NULL is represented by absence. OutputVector uses OwnerAllocator for receiver-funded result arrays. |
| ownership | Cell strings borrow; exported Row strings own caller storage; allocator-aware arrays retain their receiving account. |
| failure | Aliases alone do not admit types, fund nested allocations, or add runtime error handling. |
| cost | Inline cells internally; standard-vector export is explicit allocation work. |
| Design | [docs/aggregates.md §Logical input and publication](../../../../../aggregates.md), [docs/memory_accounts.md §Account and ownership contract](../../../../../memory_accounts.md) |

## B0002

[Lines 20–38](../../../../../../include/crown/runtime/aggregate.hpp#L20); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
class Tuple {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Expose an immutable nullable SQL tuple with shared accounted lifetime. |
| inputs / outputs | Default handle is empty; copy_of freezes cells and string bytes; getters borrow or export. |
| invariants | One payload stores descriptors and strings; separate shared Data/control storage is also accounted. |
| ownership | Copies share Data; borrowed view requires a surviving Tuple. Ordinary exports own separate caller data. |
| failure | Accessors reject empty handles; allocation/capacity failures happen during construction. |
| cost | Handle copy is constant; construction/export scales with fields and string bytes. |
| Design | [docs/aggregates.md §Logical input and publication](../../../../../aggregates.md), [docs/memory_accounts.md §Account and ownership contract](../../../../../memory_accounts.md) |

```text
[[nodiscard]] static Tuple copy_of(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Declare the explicit receiver-funded nullable tuple copy boundary. |
| inputs / outputs | Receives account, synchronous borrowed cell span, and purpose; returns an independent immutable payload owner. |
| invariants | The source and its strings must remain alive throughout the call. No fresh account grant is created. |
| ownership | Returned Tuple owns copied string bytes and inline values through its Data. |
| failure | Capacity, invalid-account, budget, and upstream allocation failures propagate before publication. |
| cost | Linear field/string copy; no child allocation per string. |
| Design | [docs/aggregates.md §Logical input and publication](../../../../../aggregates.md), [docs/memory_accounts.md §Account and ownership contract](../../../../../memory_accounts.md) |

```text
[[nodiscard]] std::span<const Cell> view() const &;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Declare borrowed cells and an explicit owning DTO export. |
| inputs / outputs | view/size/account inspect a valid tuple; export_values returns ordinary nullable Values. |
| invariants | Rvalue view/account access is deleted; retaining a span alone does not retain its payload. |
| ownership | Views borrow Tuple Data. Exported standard-vector/string allocations belong to the caller. |
| failure | Empty-handle access is invalid; export may fail allocating caller data. |
| cost | Borrowed getters are constant; export scales with fields and string bytes. |
| Design | [docs/aggregates.md §Logical input and publication](../../../../../aggregates.md), [docs/memory_accounts.md §Account and ownership contract](../../../../../memory_accounts.md) |

```text
[[nodiscard]] bool operator==(const Tuple&) const;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Declare value equality for immutable nullable tuple payloads. |
| inputs / outputs | Compares typed scalar alternatives and NULL placement; identical handles compare equal immediately. |
| invariants | Different nonempty handles are compared by values, not account or payload address. |
| ownership | Comparison borrows both tuples and creates no owned result data. |
| failure | One empty and one nonempty handle is outside the valid tuple comparison domain and is rejected by getters. |
| cost | Constant shared-identity case; otherwise linear fields plus compared string bytes. |
| Design | [docs/aggregates.md §Logical input and publication](../../../../../aggregates.md) |

```text
[[nodiscard]] explicit operator bool() const noexcept
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Distinguish an owning tuple handle from its empty sentinel. |
| inputs / outputs | Returns Data pointer presence, independently of tuple width. |
| invariants | A valid nullary tuple is true; a default empty handle is false. |
| ownership | Reads a shared pointer without exporting or retaining a new owner. |
| failure | Noexcept and nonallocating. |
| cost | Constant pointer test. |
| Design | [docs/aggregates.md §Logical input and publication](../../../../../aggregates.md) |

```text
explicit Tuple(std::shared_ptr<const Data> value) noexcept
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Publish a privately prepared immutable tuple owner. |
| inputs / outputs | Moves supplied shared Data pointer into the handle. |
| invariants | Only Tuple construction helpers can invoke this private boundary. |
| ownership | Transferred Data retains its payload and existing receiving account. |
| failure | Noexcept pointer move; allocation occurs before this constructor. |
| cost | Constant owner transfer. |
| Design | [docs/aggregates.md §Logical input and publication](../../../../../aggregates.md), [docs/memory_accounts.md §Account and ownership contract](../../../../../memory_accounts.md) |

## B0004

[Lines 40–46](../../../../../../include/crown/runtime/aggregate.hpp#L40); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct Options {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Configure selected update work, group count capacity, account grant, and event demand. |
| inputs / outputs | Defaults: one million selected charges, INT64_MAX count, 256 MiB standalone grant, capture off. |
| invariants | create_into preserves its receiver grant. Count admission protects fixed-width sufficient-statistic bounds. |
| ownership | Inline options retained by the runtime; no owner is allocated by this record. |
| failure | Runtime construction/update enforces values; this declaration does not install fallback or retry machinery. |
| cost | Fixed configuration and optional output demand. |
| Design | [docs/aggregates.md §Logical input and publication](../../../../../aggregates.md), [docs/query_memory.md §Boundaries](../../../../../query_memory.md) |

## B0005

[Lines 47–51](../../../../../../include/crown/runtime/aggregate.hpp#L47); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct Update {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Describe one logical bag-row weight replacement. |
| inputs / outputs | Supplies next sequence, borrowed nullable row, and expected before/desired after multiplicities. |
| invariants | Before/after are weights of one complete logical value row, not repeated row events. |
| ownership | Row storage remains caller-owned for the synchronous apply call. |
| failure | Runtime validates epoch, types and prior weight before publication; record construction does not validate. |
| cost | Fixed descriptor plus borrowed span; no bag expansion. |
| Design | [docs/aggregates.md §Logical input and publication](../../../../../aggregates.md), [docs/weighted_enumeration.md §Maintenance and cost contract](../../../../../weighted_enumeration.md) |

## B0006

[Lines 52–54](../../../../../../include/crown/runtime/aggregate.hpp#L52); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
// A decoded logical bag delta.
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | State the logical nullable-delta boundary and its limited authority. |
| inputs / outputs | Comment applies to RowDelta values, magnitude and erase fields. |
| invariants | Complete keys are unique and magnitudes nonzero; native decoding and upstream consolidation are caller obligations validated where possible. |
| ownership | Borrowed input cells and string bytes last only through synchronous preparation. |
| failure | No admission, recovery or source certification is performed by the comment. |
| cost | No executable cost. |
| Design | [build/verification/w06-aggregate-batch-design-v1/design.md](../../../../../../build/verification/w06-aggregate-batch-design-v1/design.md), [docs/aggregates.md](../../../../../aggregates.md), Refactor.md:1325-1327, [build/verification/w06-contract-assessment-v1/assessment.md](../../../../../../build/verification/w06-contract-assessment-v1/assessment.md), [docs/aggregate_batches.md](../../../../../aggregate_batches.md) |

## B0007

[Lines 55–59](../../../../../../include/crown/runtime/aggregate.hpp#L55); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct RowDelta {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Carry one complete logical-row multiplicity delta without signed-int64 narrowing. |
| inputs / outputs | Nullable typed cell span, uint64 magnitude, and erase direction describe one row retraction or addition; construction alone produces no runtime change. |
| invariants | Magnitude must be nonzero and the complete row key unique within NetBatch. prepare_batch revalidates schema/nullability and the before weight against the committed row ledger. |
| ownership | Cell/string spans borrow caller storage only through synchronous preparation; retained new row/group keys are copied under the receiving account. |
| failure | The value record validates nothing. Runtime rejects zero/duplicate/invalid rows, mismatched weight, count/SUM/work/account failures before publication. |
| cost | Fixed descriptor; row equality and any retained key copy pay actual typed-field/string costs. |
| Design | [build/verification/w06-aggregate-batch-design-v1/design.md](../../../../../../build/verification/w06-aggregate-batch-design-v1/design.md), [docs/aggregates.md](../../../../../aggregates.md), Refactor.md:1325-1327, [build/verification/w06-contract-assessment-v1/assessment.md](../../../../../../build/verification/w06-contract-assessment-v1/assessment.md), [docs/aggregate_batches.md](../../../../../aggregate_batches.md) |

## B0008

[Lines 60–63](../../../../../../include/crown/runtime/aggregate.hpp#L60); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct NetBatch {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Name one atomic aggregate-local sequence boundary across logical deltas. |
| inputs / outputs | Next sequence and a synchronous span of unique nonzero RowDelta entries enter prepare_batch. |
| invariants | Empty delta span is an admitted mutable-source epoch; no-FROM remains immutable. |
| ownership | Span borrows input descriptors only until preparation returns. |
| failure | Sequence/busy/source/type/arithmetic/resource errors reject the whole preparation. |
| cost | One descriptor and one budget, with work proportional to touched proposals. |
| Design | [build/verification/w06-aggregate-batch-design-v1/design.md](../../../../../../build/verification/w06-aggregate-batch-design-v1/design.md), [docs/aggregates.md](../../../../../aggregates.md), Refactor.md:1325-1327, [build/verification/w06-contract-assessment-v1/assessment.md](../../../../../../build/verification/w06-contract-assessment-v1/assessment.md), [docs/aggregate_batches.md](../../../../../aggregate_batches.md) |

## B0009

[Lines 64–69](../../../../../../include/crown/runtime/aggregate.hpp#L64); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct Metrics {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Report selected logical charges for one aggregate operation. |
| inputs / outputs | Counters distinguish fields/bytes, row/group probes, measure/output work, and group lifetime changes. |
| invariants | work is not elapsed CPU and does not count every map or variable-width comparison. |
| ownership | Inline counters owned by the returned epoch. |
| failure | Declaration supplies no timing guarantee or budget enforcement. |
| cost | Fixed counter storage; accounting semantics are local engineering choices. |
| Design | [docs/aggregates.md §Logical input and publication](../../../../../aggregates.md) |

## B0010

[Lines 70–70](../../../../../../include/crown/runtime/aggregate.hpp#L70); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L70-L70:sha256:73912001cbd14cc6be0bc1ee58c19371e0fb01c2c4385cf6fb9f6132dd31b741
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Usage note immediately before \`struct BatchMetrics : Metrics\`: Keep batch-only counters out of the single-row Metrics/Epoch value layout. |
| inputs / outputs | This comment introduces no parameter, field or return value. It documents the adjacent construct beginning at include/crown/runtime/aggregate.hpp:L71; use that declaration for the actual input/output shape. |
| invariants | The source note states: Keep batch-only counters out of the single-row Metrics/Epoch value layout. It is prose guidance; the adjacent implementation is the place to check enforcement. |
| ownership | The note states no ownership relation and retains no value. The adjacent declaration or function controls the actual owner and borrowed-view lifetime. |
| failure | This comment adds no branch or handler. Any failure behavior remains in the adjacent callable implementation and its callers. |
| cost | The prose adds no executable work. Runtime cost belongs to the adjacent operation; the note does not establish a measured or global complexity bound. |
| Design | [docs/aggregates.md](../../../../../aggregates.md), [docs/aggregate_batches.md](../../../../../aggregate_batches.md), [docs/query_memory.md](../../../../../query_memory.md), [docs/code_specs/subsystem_contracts.md](../../../../subsystem_contracts.md) |

## B0011

[Lines 71–74](../../../../../../include/crown/runtime/aggregate.hpp#L71); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct BatchMetrics : Metrics {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Expose batch-specific copy/state/finalization counters while leaving legacy single-row Metrics and Epoch layouts unchanged. |
| inputs / outputs | Inherits the existing work/input/probe/measure/output/group counters and adds copied_fields, copied_bytes, state_fields_prepared, and groups_finalized to BatchEpoch.metrics. |
| invariants | The four added counters describe selected logical work only; they do not count every map/string comparison, allocator action, or elapsed CPU. Original Metrics and Epoch shapes remain unchanged. |
| ownership | Inline counter values belong to BatchEpoch; this declaration creates no separate owner or allocation. |
| failure | Counters enforce no limit themselves; the one preparation Budget separately rejects selected-work exhaustion. |
| cost | Four uint64 counters add 32 bytes to BatchMetrics storage; inherited Metrics remain the existing single-row representation. |
| Design | [build/verification/w06-aggregate-batch-design-v1/design.md](../../../../../../build/verification/w06-aggregate-batch-design-v1/design.md), [docs/aggregates.md](../../../../../aggregates.md), Refactor.md:1325-1327, [build/verification/w06-contract-assessment-v1/assessment.md](../../../../../../build/verification/w06-contract-assessment-v1/assessment.md), [docs/aggregate_batches.md](../../../../../aggregate_batches.md) |

## B0012

[Lines 75–78](../../../../../../include/crown/runtime/aggregate.hpp#L75); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct GroupChange {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Represent the visible output transition of one identified group. |
| inputs / outputs | Stores key and optional before/after ordered result tuples. |
| invariants | An absent group differs from a present row containing NULL cells. |
| ownership | Tuple handles retain payload/accounts; this record does not retain AggregateProgram schema metadata. |
| failure | No conversion or formatting occurs in this declaration; runtime preparation may fail before commit. |
| cost | Fixed shared handles; output materialization cost is separate. |
| Design | [docs/aggregates.md §Logical input and publication](../../../../../aggregates.md) |

## B0013

[Lines 79–85](../../../../../../include/crown/runtime/aggregate.hpp#L79); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct Epoch {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Return update identity, input-change status, charges, and optional captured output. |
| inputs / outputs | sequence identifies committed input epoch; changed follows input weight, captured follows event demand. |
| invariants | A changed input can leave rounded output unchanged, so output may remain absent. |
| ownership | Owns metrics inline and any GroupChange payload handles. |
| failure | The declaration is a result shape, not an atomicity proof. |
| cost | Fixed metadata unless output tuples were explicitly requested. |
| Design | [docs/aggregates.md §Logical input and publication](../../../../../aggregates.md) |

## B0014

[Lines 86–94](../../../../../../include/crown/runtime/aggregate.hpp#L86); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct BatchEpoch {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Own one prepared or committed multi-group epoch, its compiled schema handle, selected metrics, and requested changes. |
| inputs / outputs | Sequence, changed/captured flags, BatchMetrics, AggregateProgram, and receiver-funded OutputVector&lt;GroupChange&gt;. |
| invariants | changed means at least one row proposal, not necessarily a visible value event; an empty batch advances on commit with changed=false. Equal rounded output can suppress events; full group identity remains. |
| ownership | Program handle retains compiler metadata from its original account. OutputVector uses the receiving account; Tuple payloads own copied output. Preview borrows while token is open; committed BatchEpoch owns its handles. |
| failure | Created privately before token exposure. Preparation/output failures discard it without changing committed state; type trait separately requires a nonthrowing result move. |
| cost | Fixed flags/counters and program handle; captured outputs scale with changed touched groups, fields, bytes, and formatting. Uncaptured vector remains empty. |
| Design | [build/verification/w06-aggregate-batch-design-v1/design.md](../../../../../../build/verification/w06-aggregate-batch-design-v1/design.md), [docs/aggregates.md](../../../../../aggregates.md), Refactor.md:1325-1327, [build/verification/w06-contract-assessment-v1/assessment.md](../../../../../../build/verification/w06-contract-assessment-v1/assessment.md), [include/crown/resource/allocator.hpp](../../../../../../include/crown/resource/allocator.hpp), [include/crown/resource/ownership.hpp](../../../../../../include/crown/resource/ownership.hpp), [include/crown/resource/owner_allocator.hpp](../../../../../../include/crown/resource/owner_allocator.hpp), [docs/aggregate_batches.md](../../../../../aggregate_batches.md) |

## B0015

[Lines 95–95](../../../../../../include/crown/runtime/aggregate.hpp#L95); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct GroupResult {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Pair one group identity with its ordered SELECT row. |
| inputs / outputs | Two immutable Tuple handles provide key and values. |
| invariants | Different groups remain distinct even when their projected output rows are equal. |
| ownership | Both handles retain their payloads independently. |
| failure | No allocation or validation in aggregate initialization beyond handle operations. |
| cost | Constant handle pair; payload cost belongs to tuple construction. |
| Design | [docs/aggregates.md §SQL and numeric contract](../../../../../aggregates.md), [docs/aggregates.md §Logical input and publication](../../../../../aggregates.md) |

## B0016

[Lines 96–101](../../../../../../include/crown/runtime/aggregate.hpp#L96); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct Snapshot {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Own a result snapshot together with its sequence and output schema. |
| inputs / outputs | Stores AggregateProgram and receiver-funded vector of GroupResult records. |
| invariants | Program metadata may retain its original compiler account; result-array funding uses the supplied receiver. |
| ownership | Copies of payload handles survive runtime destruction. The OwnerAllocator retains the receiving account. |
| failure | Declaration alone does not populate groups; collection may hit explicit work/group/memory limits. |
| cost | Explicit result collection, not an automatic update scan. |
| Design | [docs/aggregates.md §Logical input and publication](../../../../../aggregates.md), [docs/memory_accounts.md §Account and ownership contract](../../../../../memory_accounts.md) |

## B0017

[Lines 102–105](../../../../../../include/crown/runtime/aggregate.hpp#L102); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct SnapshotLimits {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Bound explicit snapshot result collection. |
| inputs / outputs | Defaults to at most 65,536 groups and one million selected work charges. |
| invariants | These collection bounds are separate from per-update limits and receiving memory capacity. |
| ownership | Inline caller configuration consumed synchronously. |
| failure | Snapshot implementation rejects excessive demand; this record does not truncate results. |
| cost | Fixed configuration. |
| Design | [docs/aggregates.md §Logical input and publication](../../../../../aggregates.md) |

## B0018

[Lines 106–115](../../../../../../include/crown/runtime/aggregate.hpp#L106); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
class AggregateRuntime {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Declare the move-only facade that maintains logical-row aggregates and prepares aggregate-local batch epochs. |
| inputs / outputs | Construct/move owner; apply nullable DTO or W03 tuple replacements; prepare a unique NetBatch and borrow/commit/rollback its preview; request snapshots, account statistics, or diagnostics. |
| invariants | Calls remain serialized. Single-row updates keep immediate SUM checks; batch preparation checks final marked SUMs per touched group. While a token is live, updates/snapshot/invariants reject aggregate_busy; committed program/sequence/account statistics stay readable. The caller-fed ledger adds no physical-source/compiler/cross-runtime/recovery authority. |
| ownership | Move-only facade holds shared_ptr&lt;Data&gt;; PreparedBatch retains its own Data reference. create_into funds combined Data/control allocation and runtime payloads in receiver. Program borrows Data; preview borrows while token open; committed BatchEpoch owns program/output handles. |
| failure | Input/sequence/busy/work/count/SUM/account boundaries occur before publication. Token liveness is checked before nonthrowing commit; construction failure exposes no token/busy lease. |
| cost | Single-row costs retain W04 behavior. Batch costs depend on touched rows/groups, measures, copied keys/output, ordered map searches and teardown; selected Budget omits every comparison, allocator action and CPU instruction. |
| Design | [docs/aggregates.md §Logical input and publication](../../../../../aggregates.md), [docs/weighted_enumeration.md §Maintenance and cost contract](../../../../../weighted_enumeration.md) |

```text
// Logical bag rows maintain aggregate groups.
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Document distinct immediate single-row and final-group batch boundaries. |
| inputs / outputs | Comments and AggregateRuntime declaration retain serialized logical-bag use. |
| invariants | No physical source, compiler composition, cross-runtime commit or recovery is installed. |
| ownership | Facade is move-only; active batch token may retain its same Data owner. |
| failure | The declaration itself establishes no W06 acceptance. |
| cost | Comments/scope closure add no runtime work. |
| Design | [build/verification/w06-aggregate-batch-design-v1/design.md](../../../../../../build/verification/w06-aggregate-batch-design-v1/design.md), [docs/aggregates.md](../../../../../aggregates.md), Refactor.md:1325-1327, [build/verification/w06-contract-assessment-v1/assessment.md](../../../../../../build/verification/w06-contract-assessment-v1/assessment.md), [docs/aggregate_batches.md](../../../../../aggregate_batches.md) |

## B0019

[Lines 116–137](../../../../../../include/crown/runtime/aggregate.hpp#L116); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
class PreparedBatch {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Declare a move-only RAII token for one fully prepared aggregate batch and a borrowed immutable preview. |
| inputs / outputs | active() reports token state; preview() borrows BatchEpoch; commit() returns the owning result; rollback() closes it. |
| invariants | Copying is deleted. A live token marks the shared owner busy; commit/rollback/destruction release the lease, and moved-from/closed access is rejected. |
| ownership | AccountedUnique private Data owns proposals and a shared reference to AggregateRuntime::Data. Preview lasts only while token remains unmoved and open; copied program/Tuple handles can outlive it. |
| failure | Invalid token operations fail before publication. Preparation failures happen before token exposure; destructor rollback is noexcept. |
| cost | Fixed handle; proposal maps, copied State, nodes, result vector, and output payloads are charged separately to the receiver. |
| Design | [build/verification/w06-aggregate-batch-design-v1/design.md](../../../../../../build/verification/w06-aggregate-batch-design-v1/design.md), [docs/aggregates.md](../../../../../aggregates.md), Refactor.md:1325-1327, [build/verification/w06-contract-assessment-v1/assessment.md](../../../../../../build/verification/w06-contract-assessment-v1/assessment.md), [include/crown/resource/allocator.hpp](../../../../../../include/crown/resource/allocator.hpp), [include/crown/resource/ownership.hpp](../../../../../../include/crown/resource/ownership.hpp), [include/crown/resource/owner_allocator.hpp](../../../../../../include/crown/resource/owner_allocator.hpp), [docs/aggregate_batches.md](../../../../../aggregate_batches.md) |

## B0020

[Lines 138–167](../../../../../../include/crown/runtime/aggregate.hpp#L138); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
[[nodiscard]] static AggregateRuntime create_into(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Create or operate one aggregate runtime, optionally placing its retained state in a supplied account. |
| inputs / outputs | Program/options or an existing MemoryAccount in; update epochs, prepared-batch tokens, snapshots, and memory stats out. |
| invariants | One runtime's calls are serialized; a prepared token retains the owner and blocks conflicting operations. |
| ownership | create_into builds account-backed shared Data; PreparedBatch owns its token and refers to that Data. |
| failure | Invalid program/options and account admission can fail; moved-from or closed-token access rejects. |
| cost | Initialization funds maps/scratch; updates and snapshots depend on rows/groups; final owner release destroys retained state. |
| Design | [src/runtime/aggregate.cpp §AggregateRuntime::create_into](../../../../../../src/runtime/aggregate.cpp), [src/runtime/aggregate.cpp §PreparedBatch](../../../../../../src/runtime/aggregate.cpp), [docs/aggregates.md](../../../../../aggregates.md), [docs/query_memory.md](../../../../../query_memory.md) |
