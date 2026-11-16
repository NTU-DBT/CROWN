# `include/crown/runtime/support.hpp` — block usage map

[Source](../../../../../../include/crown/runtime/support.hpp) · [Source index](../../../../README.md) · [Subsystem contracts](../../../../subsystem_contracts.md) · [Reviewed primitives](../../../../primitives.md)

Maintain record/S/P/E support state and current/epoch cursor leases.

Snapshot SHA-256: `516831fa32df707d2e38b2109f128d54a6dd4ecf8da8d0bca6fe68a514f522c3`. 463 lines partitioned into 59 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [support](../../../../subsystem_contracts.md#support). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/support_invariants.md](../../../../../support_invariants.md), [docs/runtime_support.md](../../../../../runtime_support.md), [docs/prepared_epochs.md](../../../../../prepared_epochs.md), [docs/result_cursors.md](../../../../../result_cursors.md), [docs/epoch_views.md](../../../../../epoch_views.md), [docs/code_review.md](../../../../../code_review.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–22](../../../../../../include/crown/runtime/support.hpp#L1) | Imports dependencies; guards repeated header inclusion; declares namespace scope; declares types or opens a type body. |  · [reviewed contract](#b0001) |
| [B0002 · 23–23](../../../../../../include/crown/runtime/support.hpp#L23) | Type/record definition: struct SatisfiedChildCount |  · [reviewed contract](#b0002) |
| [B0003 · 24–24](../../../../../../include/crown/runtime/support.hpp#L24) | Type/record definition: struct ProjectionSupportCount |  · [reviewed contract](#b0003) |
| [B0004 · 25–27](../../../../../../include/crown/runtime/support.hpp#L25) | declares callable signatures; declares values/defaults or compile-time conditions. |  · [reviewed contract](#b0004) |
| [B0005 · 28–28](../../../../../../include/crown/runtime/support.hpp#L28) | Type/record definition: struct SupportOwnerId |  · [reviewed contract](#b0005) |
| [B0006 · 29–29](../../../../../../include/crown/runtime/support.hpp#L29) | Type/record definition: enum class SupportRole |  · [reviewed contract](#b0006) |
| [B0007 · 30–36](../../../../../../include/crown/runtime/support.hpp#L30) | Type/record definition: struct SupportHandle |  · [reviewed contract](#b0007) |
| [B0008 · 37–37](../../../../../../include/crown/runtime/support.hpp#L37) | Type/record definition: enum class PropagationOrder |  · [reviewed contract](#b0008) |
| [B0009 · 38–48](../../../../../../include/crown/runtime/support.hpp#L38) | Type/record definition: struct SupportOptions | source comment (unverified): // One finite account funds native executable metadata, table/row storage, · [reviewed contract](#b0009) |
| [B0010 · 49–54](../../../../../../include/crown/runtime/support.hpp#L49) | Type/record definition: struct NativeSetUpdate | source comment (unverified): // Complete logical scope, ascending variable ID; not a physical row. · [reviewed contract](#b0010) |
| [B0011 · 55–77](../../../../../../include/crown/runtime/support.hpp#L55) | Type/record definition: struct SupportMetrics | source comment (unverified): // Whole-state copies stay zero; affected-row and child-flag copies still occur. · [reviewed contract](#b0011) |
| [B0012 · 78–83](../../../../../../include/crown/runtime/support.hpp#L78) | Type/record definition: struct MembershipTransition | source comment (unverified): // Owns a deleted key too; no borrowed record pointer. · [reviewed contract](#b0012) |
| [B0013 · 84–89](../../../../../../include/crown/runtime/support.hpp#L84) | Type/record definition: struct SupportValueState |  · [reviewed contract](#b0013) |
| [B0014 · 90–98](../../../../../../include/crown/runtime/support.hpp#L90) | Type/record definition: struct JournalRecord | returns retained.get() · [reviewed contract](#b0014) |
| [B0015 · 99–99](../../../../../../include/crown/runtime/support.hpp#L99) | Type/record definition: enum class SupportEventKind |  · [reviewed contract](#b0015) |
| [B0016 · 100–109](../../../../../../include/crown/runtime/support.hpp#L100) | Type/record definition: struct PropagationEvent |  · [reviewed contract](#b0016) |
| [B0017 · 110–126](../../../../../../include/crown/runtime/support.hpp#L110) | Type/record definition: struct SupportJournal | source comment (unverified): // Optional causal trace; accounting and record retention are always active. · [reviewed contract](#b0017) |
| [B0018 · 127–136](../../../../../../include/crown/runtime/support.hpp#L127) | Type/record definition: struct SupportEpoch | source comment (unverified): // Local membership changes, not full-answer deltas. The journal owns the · [reviewed contract](#b0018) |
| [B0019 · 137–143](../../../../../../include/crown/runtime/support.hpp#L137) | Type/record definition: struct SupportRecordSnapshot |  · [reviewed contract](#b0019) |
| [B0020 · 144–148](../../../../../../include/crown/runtime/support.hpp#L144) | Type/record definition: struct ProjectionKeySnapshot |  · [reviewed contract](#b0020) |
| [B0021 · 149–156](../../../../../../include/crown/runtime/support.hpp#L149) | Type/record definition: struct NodeSupportSnapshot |  · [reviewed contract](#b0021) |
| [B0022 · 157–161](../../../../../../include/crown/runtime/support.hpp#L157) | Type/record definition: struct SupportSnapshot |  · [reviewed contract](#b0022) |
| [B0023 · 162–162](../../../../../../include/crown/runtime/support.hpp#L162) | Explanatory comments or spacing. |  |
| [B0024 · 163–163](../../../../../../include/crown/runtime/support.hpp#L163) | Type/record definition: enum class ResultView |  · [reviewed contract](#b0024) |
| [B0025 · 164–164](../../../../../../include/crown/runtime/support.hpp#L164) | Type/record definition: enum class SnapshotSide |  · [reviewed contract](#b0025) |
| [B0026 · 165–165](../../../../../../include/crown/runtime/support.hpp#L165) | Type/record definition: struct VariableBinding |  · [reviewed contract](#b0026) |
| [B0027 · 166–167](../../../../../../include/crown/runtime/support.hpp#L166) | declares aliases; declares values/defaults or compile-time conditions. | source comment (unverified): // Borrowed inputs are copied into the existing query account during startup. · [reviewed contract](#b0027) |
| [B0028 · 168–168](../../../../../../include/crown/runtime/support.hpp#L168) | Type/record definition: struct VariableBindingView | source comment (unverified): // Borrowed inputs are copied into the existing query account during startup. · [reviewed contract](#b0028) |
| [B0029 · 169–170](../../../../../../include/crown/runtime/support.hpp#L169) | Explanatory comments or spacing. | source comment (unverified): // Nullopt selects the complete C* program and original core head. A subtree · [reviewed contract](#b0029) |
| [B0030 · 171–171](../../../../../../include/crown/runtime/support.hpp#L171) | Type/record definition: struct VisibleFragment | source comment (unverified): // Nullopt selects the complete C* program and original core head. A subtree · [reviewed contract](#b0030) |
| [B0031 · 172–176](../../../../../../include/crown/runtime/support.hpp#L172) | Explanatory comments or spacing. | source comment (unverified): // Full-assignment traversal over survivor factors. A root selects its entire · [reviewed contract](#b0031) |
| [B0032 · 177–180](../../../../../../include/crown/runtime/support.hpp#L177) | Type/record definition: struct WitnessFragment | source comment (unverified): // Full-assignment traversal over survivor factors. A root selects its entire · [reviewed contract](#b0032) |
| [B0033 · 181–181](../../../../../../include/crown/runtime/support.hpp#L181) | Type/record definition: struct EpochViewOptions |  · [reviewed contract](#b0033) |
| [B0034 · 182–186](../../../../../../include/crown/runtime/support.hpp#L182) | Type/record definition: struct EpochViewMetrics |  · [reviewed contract](#b0034) |
| [B0035 · 187–187](../../../../../../include/crown/runtime/support.hpp#L187) | Type/record definition: enum class ResultCursorState |  · [reviewed contract](#b0035) |
| [B0036 · 188–188](../../../../../../include/crown/runtime/support.hpp#L188) | Type/record definition: struct ResultCursorOptions |  · [reviewed contract](#b0036) |
| [B0037 · 189–197](../../../../../../include/crown/runtime/support.hpp#L189) | Type/record definition: struct CursorWork |  · [reviewed contract](#b0037) |
| [B0038 · 198–203](../../../../../../include/crown/runtime/support.hpp#L198) | Type/record definition: struct ResultCursorMetrics | source comment (unverified): // Uncharged mandatory cleanup: counts opened main and witness-probe frames. · [reviewed contract](#b0038) |
| [B0039 · 204–204](../../../../../../include/crown/runtime/support.hpp#L204) | Explanatory comments or spacing. |  |
| [B0040 · 205–205](../../../../../../include/crown/runtime/support.hpp#L205) | Type/record definition: enum class CursorObservationSource |  · [reviewed contract](#b0040) |
| [B0041 · 206–206](../../../../../../include/crown/runtime/support.hpp#L206) | Type/record definition: enum class CursorTerminalReason |  · [reviewed contract](#b0041) |
| [B0042 · 207–209](../../../../../../include/crown/runtime/support.hpp#L207) | Type/record definition: enum class CursorMetricId |  · [reviewed contract](#b0042) |
| [B0043 · 210–210](../../../../../../include/crown/runtime/support.hpp#L210) | declares callable signatures; declares values/defaults or compile-time conditions. |  · [reviewed contract](#b0043) |
| [B0044 · 211–215](../../../../../../include/crown/runtime/support.hpp#L211) | Type/record definition: struct CursorMetricDescriptor |  · [reviewed contract](#b0044) |
| [B0045 · 216–216](../../../../../../include/crown/runtime/support.hpp#L216) | declares callable signatures; declares values/defaults or compile-time conditions. |  · [reviewed contract](#b0045) |
| [B0046 · 217–235](../../../../../../include/crown/runtime/support.hpp#L217) | Type/record definition: struct CursorObservation | returns index&lt;values.size()?values\[index\]:unavailable · [reviewed contract](#b0046) |
| [B0047 · 236–241](../../../../../../include/crown/runtime/support.hpp#L236) | Type/record definition: struct NodeStateGauge |  · [reviewed contract](#b0047) |
| [B0048 · 242–242](../../../../../../include/crown/runtime/support.hpp#L242) | Type/record definition: struct BaseStateGauge |  · [reviewed contract](#b0048) |
| [B0049 · 243–251](../../../../../../include/crown/runtime/support.hpp#L243) | Type/record definition: struct CommittedStateGauges | source comment (unverified): // Unsupported facts remain unavailable, never fabricated as zero. · [reviewed contract](#b0049) |
| [B0050 · 252–252](../../../../../../include/crown/runtime/support.hpp#L252) | Explanatory comments or spacing. | source comment (unverified): // Native retained/report variant; the existing gauge value remains a caller DTO. · [reviewed contract](#b0050) |
| [B0051 · 253–269](../../../../../../include/crown/runtime/support.hpp#L253) | Type/record definition: struct CapturedStateGauges | returns *this; source comment (unverified): // Native retained/report variant; the existing gauge value remains a caller DTO. · [reviewed contract](#b0051) |
| [B0052 · 270–305](../../../../../../include/crown/runtime/support.hpp#L270) | declares types or opens a type body; declares callable signatures; declares values/defaults or compile-time conditions. | source comment (unverified): // Logical support kernel with affected-record metadata/storage undo. Returned · [reviewed contract](#b0052) |
| [B0053 · 306–341](../../../../../../include/crown/runtime/support.hpp#L306) | declares types or opens a type body; declares callable signatures; declares values/defaults or compile-time conditions. | source comment (unverified): // Journal-backed immutable relation context. Copies and cursors · [reviewed contract](#b0053) |
| [B0054 · 342–377](../../../../../../include/crown/runtime/support.hpp#L342) | declares types or opens a type body; declares callable signatures; declares values/defaults or compile-time conditions. | source comment (unverified): // Owner-only tentative epoch. All staged rows have one polarity; every · [reviewed contract](#b0054) |
| [B0055 · 378–380](../../../../../../include/crown/runtime/support.hpp#L378) | declares types or opens a type body. |  · [reviewed contract](#b0055) |
| [B0056 · 381–386](../../../../../../include/crown/runtime/support.hpp#L381) | Type/record definition: struct Checkpoint |  · [reviewed contract](#b0056) |
| [B0057 · 387–422](../../../../../../include/crown/runtime/support.hpp#L387) | declares types or opens a type body; declares callable signatures; declares values/defaults or compile-time conditions. | source comment (unverified): // Original-account requested-byte usage; caller DTO exports and process RSS · [reviewed contract](#b0057) |
| [B0058 · 423–458](../../../../../../include/crown/runtime/support.hpp#L423) | controls preprocessing; declares types or opens a type body; declares callable signatures; declares values/defaults or compile-time conditions. | source comment (unverified): // Owning diagnostic copy. · [reviewed contract](#b0058) |
| [B0059 · 459–463](../../../../../../include/crown/runtime/support.hpp#L459) | declares callable signatures; declares values/defaults or compile-time conditions. | source comment (unverified): // namespace crown::runtime · [reviewed contract](#b0059) |

## B0001

[Lines 1–22](../../../../../../include/crown/runtime/support.hpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
#pragma once
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Declare the Boolean support, prepared-epoch and cursor interfaces. |
| inputs / outputs | Imports native account/storage/program, diagnostics and ownership types. |
| invariants | Support maintenance is a logical set kernel; nullable SQL, bag counts and physical source routing have separate owners. |
| ownership | Declarations retain no live state. |
| failure | Value declaration/default initialization itself has no recovery path. |
| cost | No runtime work for declarations/includes. |
| Design | [docs/runtime_support.md](../../../../../runtime_support.md), [docs/support_invariants.md](../../../../../support_invariants.md), [docs/query_memory.md](../../../../../query_memory.md) |

## B0002

[Lines 23–23](../../../../../../include/crown/runtime/support.hpp#L23); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct SatisfiedChildCount
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Distinguish the number of satisfied child slots from projection witness counts. |
| inputs / outputs | size_t value, initially zero. |
| invariants | Equals the number of true child-presence bytes and stays &lt;= ordered child count after each drain. |
| ownership | Plain value metadata; no runtime or work-grant authority is created. |
| failure | Value declaration/default initialization itself has no recovery path. |
| cost | Fixed-size scalar metadata; no allocation for this record alone. |
| Design | [docs/runtime_support.md](../../../../../runtime_support.md), [docs/support_invariants.md](../../../../../support_invariants.md), [docs/query_memory.md](../../../../../query_memory.md) |

## B0003

[Lines 24–24](../../../../../../include/crown/runtime/support.hpp#L24); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct ProjectionSupportCount
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Represent exact distinct-local-survivor support for a projected key. |
| inputs / outputs | uint64 value, initially zero. |
| invariants | A stored P/E key has positive count; this is not full subtree or physical derivation multiplicity. |
| ownership | Plain value metadata; no runtime or work-grant authority is created. |
| failure | Value declaration/default initialization itself has no recovery path. |
| cost | Fixed-size scalar metadata; no allocation for this record alone. |
| Design | [docs/runtime_support.md](../../../../../runtime_support.md), [docs/support_invariants.md](../../../../../support_invariants.md), [docs/query_memory.md](../../../../../query_memory.md) |

## B0004

[Lines 25–27](../../../../../../include/crown/runtime/support.hpp#L25); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
[[nodiscard]] ProjectionSupportCount increment_support(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Declare checked exact support counter changes. |
| inputs / outputs | Increment accepts explicit maximum; decrement requires positive value. |
| invariants | Overflow/cap/underflow never wrap; zero-crossing membership is handled separately by the transaction. |
| ownership | Plain value metadata; no runtime or work-grant authority is created. |
| failure | Increment rejects at configured cap; decrement rejects zero. |
| cost | Constant checked integer operations. |
| Design | [docs/runtime_support.md](../../../../../runtime_support.md), [docs/support_invariants.md](../../../../../support_invariants.md), [docs/query_memory.md](../../../../../query_memory.md) |

## B0005

[Lines 28–28](../../../../../../include/crown/runtime/support.hpp#L28); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct SupportOwnerId
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Identify one public logical runtime independently of storage/metadata owners. |
| inputs / outputs | Copied uint64 identity. |
| invariants | Assigned once by public runtime owner authority; separate storage IDs do not consume that sequence. |
| ownership | Plain value metadata; no runtime or work-grant authority is created. |
| failure | Value declaration/default initialization itself has no recovery path. |
| cost | Fixed-size scalar metadata; no allocation for this record alone. |
| Design | [docs/runtime_support.md](../../../../../runtime_support.md), [docs/support_invariants.md](../../../../../support_invariants.md), [docs/query_memory.md](../../../../../query_memory.md) |

## B0006

[Lines 29–29](../../../../../../include/crown/runtime/support.hpp#L29); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
enum class SupportRole
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Choose one node-local logical relation. |
| inputs / outputs | records, survivors S, parent-support P or visible E. |
| invariants | E exists only on C* nodes; relation() rejects inapplicable/invalid roles. |
| ownership | Plain value metadata; no runtime or work-grant authority is created. |
| failure | Value declaration/default initialization itself has no recovery path. |
| cost | Fixed-size scalar metadata; no allocation for this record alone. |
| Design | [docs/runtime_support.md](../../../../../runtime_support.md), [docs/support_invariants.md](../../../../../support_invariants.md), [docs/query_memory.md](../../../../../query_memory.md) |

## B0007

[Lines 30–36](../../../../../../include/crown/runtime/support.hpp#L30); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct SupportHandle
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Retain logical row/key identity without a raw record pointer. |
| inputs / outputs | Runtime owner, node, role and table-local TupleId. |
| invariants | Foreign owners reject; committed erase/reinsert gets a new identity; positive support changes retain the same key ID. |
| ownership | Plain value metadata; no runtime or work-grant authority is created. |
| failure | Value declaration/default initialization itself has no recovery path. |
| cost | Fixed-size scalar metadata; no allocation for this record alone. |
| Design | [docs/runtime_support.md](../../../../../runtime_support.md), [docs/support_invariants.md](../../../../../support_invariants.md), [docs/query_memory.md](../../../../../query_memory.md) |

## B0008

[Lines 37–37](../../../../../../include/crown/runtime/support.hpp#L37); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
enum class PropagationOrder
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Choose iterative FIFO or LIFO upward work scheduling. |
| inputs / outputs | Two schedule tags. |
| invariants | After drain both schedules satisfy the same recursive sets/flags/counts; tentative IDs/order can differ. |
| ownership | Plain value metadata; no runtime or work-grant authority is created. |
| failure | Value declaration/default initialization itself has no recovery path. |
| cost | Fixed-size scalar metadata; no allocation for this record alone. |
| Design | [docs/runtime_support.md](../../../../../runtime_support.md), [docs/support_invariants.md](../../../../../support_invariants.md), [docs/query_memory.md](../../../../../query_memory.md) |

## B0009

[Lines 38–48](../../../../../../include/crown/runtime/support.hpp#L38); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct SupportOptions
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Configure logical work/counter caps, scheduling, optional capture and original-account byte cap. |
| inputs / outputs | Optional logical work limit, positive support limit, order, observation/capture options and256MiB default requested-byte limit. |
| invariants | Logical work, native IndexWork, component counts and allocator bytes have distinct units. Rebuild/composition retain the account. |
| ownership | Options are copied into runtime; external constructor admission establishes the receiving account. |
| failure | Impl rejects zero support cap, invalid order and off-observation/full-transition conflict; resource admission failures propagate. |
| cost | Fixed configuration; optional capture adds owning output only when enabled. |
| Design | [docs/runtime_support.md](../../../../../runtime_support.md), [docs/support_invariants.md](../../../../../support_invariants.md), [docs/query_memory.md](../../../../../query_memory.md) |

## B0010

[Lines 49–54](../../../../../../include/crown/runtime/support.hpp#L49); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct NativeSetUpdate
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Request one contiguous logical native set event. |
| inputs / outputs | Sequence, native NodeId, insertion/erasure and complete logical scope Row. |
| invariants | Values use ascending variable-ID scope order; this is not a full physical source row. |
| ownership | Caller owns Row and strings before native import. |
| failure | Apply validates sequence/node/polarity/layout before mutation. |
| cost | Owning caller Row; native import copies exact scalar descriptors/string bytes. |
| Design | [docs/runtime_support.md](../../../../../runtime_support.md), [docs/support_invariants.md](../../../../../support_invariants.md), [docs/query_memory.md](../../../../../query_memory.md) |

## B0011

[Lines 55–77](../../../../../../include/crown/runtime/support.hpp#L55); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct SupportMetrics
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Report abstract logical propagation work and affected-state activity. |
| inputs / outputs | Work, visits/probes/events/crossings, storage/metadata/undo and queue counters. |
| invariants | Whole-copy counters stay zero with journals; zero does not mean no affected flag/key copies. Managed categories debit cumulative logical work. |
| ownership | Copied scalar observations; no journal/row ownership. |
| failure | Value declaration/default initialization itself has no recovery path. |
| cost | Fixed counter storage/increments; field width, ordered comparisons, allocation and cleanup are extra costs. |
| Design | [docs/runtime_support.md](../../../../../runtime_support.md), [docs/support_invariants.md](../../../../../support_invariants.md), [docs/query_memory.md](../../../../../query_memory.md) |

## B0012

[Lines 78–83](../../../../../../include/crown/runtime/support.hpp#L78); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct MembershipTransition
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Retain one optional local relation membership crossing. |
| inputs / outputs | Logical handle, polarity, owning tuple and causal event ID. |
| invariants | A local record/S/P/E crossing is not a full-query answer delta. |
| ownership | Tuple retains original-account output payload even for an erased key. |
| failure | Capture allocation occurs before commit and can abort the pending epoch. |
| cost | Only enabled capture materializes these payloads; each requires key/tuple storage. |
| Design | [docs/runtime_support.md](../../../../../runtime_support.md), [docs/support_invariants.md](../../../../../support_invariants.md), [docs/query_memory.md](../../../../../query_memory.md) |

## B0013

[Lines 84–89](../../../../../../include/crown/runtime/support.hpp#L84); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct SupportValueState
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Describe before/after local record or projection metadata. |
| inputs / outputs | Membership plus optional satisfied count/child flags or projection count. |
| invariants | Record and projection forms differ; survivor membership needs no projection count. |
| ownership | Child flags use transferable OwnerAllocator backed by the original account. |
| failure | Constructing/copying child arrays can fail before mutation; noexcept move is asserted. |
| cost | Record snapshots copy O(child count) bits and can allocate; count-only states are fixed. |
| Design | [docs/runtime_support.md](../../../../../runtime_support.md), [docs/support_invariants.md](../../../../../support_invariants.md), [docs/query_memory.md](../../../../../query_memory.md) |

## B0014

[Lines 90–98](../../../../../../include/crown/runtime/support.hpp#L90); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct JournalRecord
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Pin the exact affected tuple alongside mutation metadata. |
| inputs / outputs | Ordinal, causal ID, logical handle, before/after SupportValueState and native arena Pin. |
| invariants | tuple() borrows the retained native tuple; record history is not evidence of current membership. |
| ownership | Pin preserves deleted values and original account after later updates/runtime destruction. |
| failure | Pin/metadata preparation may fail before mutation; invalid pin access follows arena guards. |
| cost | Affected pin plus before/after flag copies; no complete query snapshot. |
| Design | [docs/runtime_support.md](../../../../../runtime_support.md), [docs/support_invariants.md](../../../../../support_invariants.md), [docs/query_memory.md](../../../../../query_memory.md) |

## B0015

[Lines 99–99](../../../../../../include/crown/runtime/support.hpp#L99); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
enum class SupportEventKind
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Distinguish native input causes from queued child-key crossings. |
| inputs / outputs | native_update and child_key tags. |
| invariants | Child events arise only from parent-support membership changes; E crossings stay local. |
| ownership | Plain value metadata; no runtime or work-grant authority is created. |
| failure | Value declaration/default initialization itself has no recovery path. |
| cost | Fixed-size scalar metadata; no allocation for this record alone. |
| Design | [docs/runtime_support.md](../../../../../runtime_support.md), [docs/support_invariants.md](../../../../../support_invariants.md), [docs/query_memory.md](../../../../../query_memory.md) |

## B0016

[Lines 100–109](../../../../../../include/crown/runtime/support.hpp#L100); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct PropagationEvent
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Store an optional causal propagation trace entry. |
| inputs / outputs | Event/cause/sequence/application IDs, target/slot/source, sign, owning key and membership bits. |
| invariants | Event IDs are epoch-wide; application ordinal records processing entry/order, not a separate committed snapshot. |
| ownership | Key owns original-account output; trace exists only when full transition capture is enabled. |
| failure | Trace allocation is inside staging rollback boundaries. |
| cost | Optional per-event payload copy and vector capacity; mandatory accounting is separate. |
| Design | [docs/runtime_support.md](../../../../../runtime_support.md), [docs/support_invariants.md](../../../../../support_invariants.md), [docs/query_memory.md](../../../../../query_memory.md) |

## B0017

[Lines 110–126](../../../../../../include/crown/runtime/support.hpp#L110); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct SupportJournal
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Own mandatory affected-record history and temporary table undo, plus optional trace. |
| inputs / outputs | Constructor receives an existing account; records/events/storage_ start empty. |
| invariants | No copying; storage journals are private to coordinator and cleared at commit. Record retention is active even when trace capture is disabled. |
| ownership | Funded vectors and pins use original account; returned shared journal can outlive runtime. |
| failure | Construction/allocation/staging errors unwind before commit; journal does not create its own cap. |
| cost | Empty allocator setup; retained size follows affected records, flags, pins and optional trace. |
| Design | [docs/runtime_support.md](../../../../../runtime_support.md), [docs/support_invariants.md](../../../../../support_invariants.md), [docs/query_memory.md](../../../../../query_memory.md) |

## B0018

[Lines 127–136](../../../../../../include/crown/runtime/support.hpp#L127); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct SupportEpoch
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Return one completely drained and committed logical epoch. |
| inputs / outputs | Sequence, native_changed, existence, metrics, optional transitions and immutable shared journal. |
| invariants | All no-op stages consume one sequence with zero logical metrics/no returned journal; transitions are local changes. |
| ownership | Moves funded output and shared affected history to caller. |
| failure | Output is prepared before publication; valid commit moves it without allocation. |
| cost | Move-only transfer of vector/shared owners plus eventual affected-history destruction. |
| Design | [docs/runtime_support.md](../../../../../runtime_support.md), [docs/support_invariants.md](../../../../../support_invariants.md), [docs/query_memory.md](../../../../../query_memory.md) |

## B0019

[Lines 137–143](../../../../../../include/crown/runtime/support.hpp#L137); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct SupportRecordSnapshot
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Export one record and its child-state diagnostic. |
| inputs / outputs | Owning public tuple, logical handle, satisfied count, plain child flags and survives bit. |
| invariants | Flags/survival describe the selected diagnostic epoch; not a live reference. |
| ownership | Tuple payload remains account-funded; plain flag/vector DTO storage belongs to explicit caller export. |
| failure | Diagnostic copying can allocate/fail without changing runtime. |
| cost | O(row fields/bytes + child count) explicit diagnostic copy. |
| Design | [docs/runtime_support.md](../../../../../runtime_support.md), [docs/support_invariants.md](../../../../../support_invariants.md), [docs/query_memory.md](../../../../../query_memory.md) |

## B0020

[Lines 144–148](../../../../../../include/crown/runtime/support.hpp#L144); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct ProjectionKeySnapshot
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Export one P/E key and its exact local support. |
| inputs / outputs | Owning key, logical handle and ProjectionSupportCount. |
| invariants | Positive local support does not encode complete subtree witness multiplicity. |
| ownership | Key payload remains original-account owned; containing snapshot is caller DTO. |
| failure | Explicit diagnostic allocation can fail. |
| cost | Key payload copy plus fixed metadata. |
| Design | [docs/runtime_support.md](../../../../../runtime_support.md), [docs/support_invariants.md](../../../../../support_invariants.md), [docs/query_memory.md](../../../../../query_memory.md) |

## B0021

[Lines 149–156](../../../../../../include/crown/runtime/support.hpp#L149); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct NodeSupportSnapshot
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Group explicit node diagnostic rows and counts. |
| inputs / outputs | Node/kind, record/survivor/P lists and optional E list. |
| invariants | Absent visible_keys means node outside C*, distinct from empty E. |
| ownership | Ordinary outer vectors own caller DTO storage; nested tuples own account-funded payload. |
| failure | Copy/allocation failure returns no partial published snapshot. |
| cost | Full node population and copied fields/flags; not ordinary update work. |
| Design | [docs/runtime_support.md](../../../../../runtime_support.md), [docs/support_invariants.md](../../../../../support_invariants.md), [docs/query_memory.md](../../../../../query_memory.md) |

## B0022

[Lines 157–161](../../../../../../include/crown/runtime/support.hpp#L157); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct SupportSnapshot
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Export an owning complete logical-state diagnostic. |
| inputs / outputs | Sequence, existence and node snapshots. |
| invariants | Use as explicit inspection; rollback authority is affected journals, not this graph. |
| ownership | Caller owns outer vectors and metadata; tuples retain original account. |
| failure | Full-copy allocation/work failures propagate without mutation. |
| cost | Visits all logical relations and copies rows/counts/flags. |
| Design | [docs/runtime_support.md](../../../../../runtime_support.md), [docs/support_invariants.md](../../../../../support_invariants.md), [docs/query_memory.md](../../../../../query_memory.md) |

## B0024

[Lines 163–163](../../../../../../include/crown/runtime/support.hpp#L163); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
enum class ResultView
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Select core head or normalized SQL output mapping. |
| inputs / outputs | core/sql tags. |
| invariants | SQL mapping may add/repeat constants or emit scalar EXISTS; it does not enable arbitrary SQL semantics. |
| ownership | Plain value metadata; no runtime or work-grant authority is created. |
| failure | Value declaration/default initialization itself has no recovery path. |
| cost | Fixed-size scalar metadata; no allocation for this record alone. |
| Design | [docs/result_cursors.md](../../../../../result_cursors.md), [docs/epoch_views.md](../../../../../epoch_views.md), [docs/query_memory.md](../../../../../query_memory.md) |

## B0025

[Lines 164–164](../../../../../../include/crown/runtime/support.hpp#L164); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
enum class SnapshotSide
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Select the before or after relation context. |
| inputs / outputs | before/after tags. |
| invariants | Pending contexts are drained prefixes; commit preserves views, rollback invalidates relation reads. |
| ownership | Plain value metadata; no runtime or work-grant authority is created. |
| failure | Value declaration/default initialization itself has no recovery path. |
| cost | Fixed-size scalar metadata; no allocation for this record alone. |
| Design | [docs/result_cursors.md](../../../../../result_cursors.md), [docs/epoch_views.md](../../../../../epoch_views.md), [docs/query_memory.md](../../../../../query_memory.md) |

## B0026

[Lines 165–165](../../../../../../include/crown/runtime/support.hpp#L165); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct VariableBinding {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Supply an owning exact typed fixed-variable restriction. |
| inputs / outputs | VariableId and Value. |
| invariants | Conflicting duplicates/type mismatches reject; hidden restrictions remain existential for projected completions. |
| ownership | Caller owns Value before cursor startup imports it. |
| failure | Startup validates all bindings before publishing cursor. |
| cost | Value size plus startup native copy. |
| Design | [docs/result_cursors.md](../../../../../result_cursors.md), [docs/epoch_views.md](../../../../../epoch_views.md), [docs/query_memory.md](../../../../../query_memory.md) |

## B0027

[Lines 166–167](../../../../../../include/crown/runtime/support.hpp#L166); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
using FixedAssignment
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Collect owning fixed-variable restrictions for cursor startup. |
| inputs / outputs | vector&lt;VariableBinding&gt;; borrowed alternative declared below. |
| invariants | No persistent caller buffer borrow; cursor owns imported exact values. |
| ownership | Caller vector owns pre-admission values. |
| failure | Caller vector growth and later startup can fail independently. |
| cost | O(binding count + owned payload bytes). |
| Design | [docs/result_cursors.md](../../../../../result_cursors.md), [docs/epoch_views.md](../../../../../epoch_views.md), [docs/query_memory.md](../../../../../query_memory.md) |

## B0028

[Lines 168–168](../../../../../../include/crown/runtime/support.hpp#L168); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct VariableBindingView
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Pass a borrowed scalar restriction without an owning legacy Value mirror. |
| inputs / outputs | VariableId and ScalarView. |
| invariants | The input and its string bytes survive startup; retained native keys own their bytes afterward. |
| ownership | Call-only borrow; cursor freezes values in existing account. |
| failure | Same binding/type/cap validation as owning startup. |
| cost | No input payload copy until explicit native freeze. |
| Design | [docs/result_cursors.md](../../../../../result_cursors.md), [docs/epoch_views.md](../../../../../epoch_views.md), [docs/query_memory.md](../../../../../query_memory.md) |

## B0029

[Lines 169–170](../../../../../../include/crown/runtime/support.hpp#L169); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
// Nullopt selects the complete C* program
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Document visible fragment scope and projected output schema. |
| inputs / outputs | Optional subtree root controls selected C* descendants. |
| invariants | Root must be in C*; output variables are sorted for a fragment; no root retains original core head. |
| ownership | Documentation only. |
| failure | Value declaration/default initialization itself has no recovery path. |
| cost | No runtime work from comment. |
| Design | [docs/result_cursors.md](../../../../../result_cursors.md), [docs/epoch_views.md](../../../../../epoch_views.md), [docs/query_memory.md](../../../../../query_memory.md) |

## B0030

[Lines 171–171](../../../../../../include/crown/runtime/support.hpp#L171); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct VisibleFragment
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Select complete C* enumeration or one visible subtree. |
| inputs / outputs | Optional root NodeId. |
| invariants | A chosen root must be a valid C* node; no arbitrary atom removal/proof is implied. |
| ownership | Plain value metadata; no runtime or work-grant authority is created. |
| failure | Value declaration/default initialization itself has no recovery path. |
| cost | Fixed-size scalar metadata; no allocation for this record alone. |
| Design | [docs/result_cursors.md](../../../../../result_cursors.md), [docs/epoch_views.md](../../../../../epoch_views.md), [docs/query_memory.md](../../../../../query_memory.md) |

## B0031

[Lines 172–176](../../../../../../include/crown/runtime/support.hpp#L172); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
// Full-assignment traversal over survivor factors.
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Document full witness-factor selection rather than projected-answer selection. |
| inputs / outputs | Whole tree, rooted subtree, or exact node set. |
| invariants | Hidden variables remain output; root and explicit nodes are exclusive; empty explicit set is nullary identity. |
| ownership | Documentation only. |
| failure | Value declaration/default initialization itself has no recovery path. |
| cost | No runtime work from comment. |
| Design | [docs/result_cursors.md](../../../../../result_cursors.md), [docs/epoch_views.md](../../../../../epoch_views.md), [docs/query_memory.md](../../../../../query_memory.md) |

## B0032

[Lines 177–180](../../../../../../include/crown/runtime/support.hpp#L177); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct WitnessFragment
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Select S factors for exact full-assignment traversal. |
| inputs / outputs | Optional root or owning optional vector&lt;NodeId&gt;. |
| invariants | Duplicate/out-of-range node IDs reject; absent both means whole tree. Each factor retains original descendant-support restriction. |
| ownership | Caller owns node list; cursor builds funded descriptors at startup. |
| failure | Malformed selections or startup resource failure reject before cursor publication. |
| cost | Selection size plus startup tree/field traversal. |
| Design | [docs/result_cursors.md](../../../../../result_cursors.md), [docs/epoch_views.md](../../../../../epoch_views.md), [docs/query_memory.md](../../../../../query_memory.md) |

## B0033

[Lines 181–181](../../../../../../include/crown/runtime/support.hpp#L181); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct EpochViewOptions
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Bound abstract journal-overlay construction work. |
| inputs / outputs | Optional uint64 work limit, default1M. |
| invariants | Separate from native storage grant and original-account requested-byte cap. |
| ownership | Plain value metadata; no runtime or work-grant authority is created. |
| failure | Value declaration/default initialization itself has no recovery path. |
| cost | Fixed-size scalar metadata; no allocation for this record alone. |
| Design | [docs/result_cursors.md](../../../../../result_cursors.md), [docs/epoch_views.md](../../../../../epoch_views.md), [docs/query_memory.md](../../../../../query_memory.md) |

## B0034

[Lines 182–186](../../../../../../include/crown/runtime/support.hpp#L182); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct EpochViewMetrics
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Report journal-overlay construction activity. |
| inputs / outputs | Work/record/membership/restored/excluded/key/bucket/field counters. |
| invariants | Only changed memberships produce before-side overlays; positive support changes do not change membership. |
| ownership | Plain value metadata; no runtime or work-grant authority is created. |
| failure | Value declaration/default initialization itself has no recovery path. |
| cost | Fixed-size scalar metadata; no allocation for this record alone. |
| Design | [docs/result_cursors.md](../../../../../result_cursors.md), [docs/epoch_views.md](../../../../../epoch_views.md), [docs/query_memory.md](../../../../../query_memory.md) |

## B0035

[Lines 187–187](../../../../../../include/crown/runtime/support.hpp#L187); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
enum class ResultCursorState
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Record the one-way cursor lifecycle. |
| inputs / outputs | active/exhausted/cancelled/failed tags. |
| invariants | Failed cursor rejects later next; exhausted/cancelled repeatedly return null; all terminal states release data leases. |
| ownership | Plain value metadata; no runtime or work-grant authority is created. |
| failure | Value declaration/default initialization itself has no recovery path. |
| cost | Fixed-size scalar metadata; no allocation for this record alone. |
| Design | [docs/result_cursors.md](../../../../../result_cursors.md), [docs/epoch_views.md](../../../../../epoch_views.md), [docs/query_memory.md](../../../../../query_memory.md) |

## B0036

[Lines 188–188](../../../../../../include/crown/runtime/support.hpp#L188); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct ResultCursorOptions
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Bound cumulative abstract cursor startup/advance work. |
| inputs / outputs | Optional uint64 work limit, default1M. |
| invariants | Limit is retained for full cursor lifetime and is not refilled on next(). |
| ownership | Plain value metadata; no runtime or work-grant authority is created. |
| failure | Value declaration/default initialization itself has no recovery path. |
| cost | Fixed-size scalar metadata; no allocation for this record alone. |
| Design | [docs/result_cursors.md](../../../../../result_cursors.md), [docs/epoch_views.md](../../../../../epoch_views.md), [docs/query_memory.md](../../../../../query_memory.md) |

## B0037

[Lines 189–197](../../../../../../include/crown/runtime/support.hpp#L189); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct CursorWork
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Separate real cursor action categories for inspection. |
| inputs / outputs | Counters for calls, frames/probes/lookups/bindings/outputs and abstract work. |
| invariants | Managed increments debit cumulative checked work; byte-width/allocation/ordered comparisons are additional costs. |
| ownership | Plain value metadata; no runtime or work-grant authority is created. |
| failure | Value declaration/default initialization itself has no recovery path. |
| cost | Fixed-size scalar metadata; no allocation for this record alone. |
| Design | [docs/result_cursors.md](../../../../../result_cursors.md), [docs/epoch_views.md](../../../../../epoch_views.md), [docs/query_memory.md](../../../../../query_memory.md) |

## B0038

[Lines 198–203](../../../../../../include/crown/runtime/support.hpp#L198); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct ResultCursorMetrics
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Retain startup/result/termination/failure and last-action accounting. |
| inputs / outputs | CursorWork groups plus aggregate/max result work and mandatory cleanup count. |
| invariants | Cleanup is nonallocating and uncharged on failure/cancel; count covers opened main and witness-probe frames together. |
| ownership | Plain value metadata; no runtime or work-grant authority is created. |
| failure | Value declaration/default initialization itself has no recovery path. |
| cost | Fixed-size scalar metadata; no allocation for this record alone. |
| Design | [docs/result_cursors.md](../../../../../result_cursors.md), [docs/epoch_views.md](../../../../../epoch_views.md), [docs/query_memory.md](../../../../../query_memory.md) |

## B0040

[Lines 205–205](../../../../../../include/crown/runtime/support.hpp#L205); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
enum class CursorObservationSource
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Identify which public factor/result API created a lifecycle report. |
| inputs / outputs | Committed results, epoch-visible/witness/key/bucket tags. |
| invariants | Observation provenance is distinct from update metrics or result cardinality. |
| ownership | Plain value metadata; no runtime or work-grant authority is created. |
| failure | Value declaration/default initialization itself has no recovery path. |
| cost | Fixed-size scalar metadata; no allocation for this record alone. |
| Design | [docs/observability.md](../../../../../observability.md), [include/crown/runtime/observation.hpp](../../../../../../include/crown/runtime/observation.hpp), [docs/query_memory.md](../../../../../query_memory.md) |

## B0041

[Lines 206–206](../../../../../../include/crown/runtime/support.hpp#L206); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
enum class CursorTerminalReason
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Explain why one cursor released its lease. |
| inputs / outputs | Normal, cancel/destruction/move, invalidation, startup and next-failure tags. |
| invariants | Disabled observations use not_recorded; terminal cause is recorded once for an admitted lifecycle. |
| ownership | Plain value metadata; no runtime or work-grant authority is created. |
| failure | Value declaration/default initialization itself has no recovery path. |
| cost | Fixed-size scalar metadata; no allocation for this record alone. |
| Design | [docs/observability.md](../../../../../observability.md), [include/crown/runtime/observation.hpp](../../../../../../include/crown/runtime/observation.hpp), [docs/query_memory.md](../../../../../query_memory.md) |

## B0042

[Lines 207–209](../../../../../../include/crown/runtime/support.hpp#L207); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
enum class CursorMetricId
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Index the fixed optional cursor timing/count registry. |
| inputs / outputs | Timing, calls, cleanup, clock-read/regression IDs plus count sentinel. |
| invariants | These IDs index CursorObservation values, not logical SupportMetrics. |
| ownership | Plain value metadata; no runtime or work-grant authority is created. |
| failure | Value declaration/default initialization itself has no recovery path. |
| cost | Fixed-size scalar metadata; no allocation for this record alone. |
| Design | [docs/observability.md](../../../../../observability.md), [include/crown/runtime/observation.hpp](../../../../../../include/crown/runtime/observation.hpp), [docs/query_memory.md](../../../../../query_memory.md) |

## B0043

[Lines 210–210](../../../../../../include/crown/runtime/support.hpp#L210); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
inline constexpr std::size_t cursor_metric_count
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Size the cursor metric array from its enum sentinel. |
| inputs / outputs | Compile-time size_t constant. |
| invariants | Registry and values share the same fixed enumerator domain. |
| ownership | Plain value metadata; no runtime or work-grant authority is created. |
| failure | Value declaration/default initialization itself has no recovery path. |
| cost | Compile-time constant. |
| Design | [docs/observability.md](../../../../../observability.md), [include/crown/runtime/observation.hpp](../../../../../../include/crown/runtime/observation.hpp), [docs/query_memory.md](../../../../../query_memory.md) |

## B0044

[Lines 211–215](../../../../../../include/crown/runtime/support.hpp#L211); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct CursorMetricDescriptor
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Publish a metric's stable name, units, scope and kind. |
| inputs / outputs | ID plus borrowed string_view name/unit/scope and MetricKind. |
| invariants | Timings may nest in enclosing propagation phases and are not additive totals. |
| ownership | Views point to static registry literals. |
| failure | Value declaration/default initialization itself has no recovery path. |
| cost | Fixed-size scalar metadata; no allocation for this record alone. |
| Design | [docs/observability.md](../../../../../observability.md), [include/crown/runtime/observation.hpp](../../../../../../include/crown/runtime/observation.hpp), [docs/query_memory.md](../../../../../query_memory.md) |

## B0045

[Lines 216–216](../../../../../../include/crown/runtime/support.hpp#L216); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
[[nodiscard]] std::span<const CursorMetricDescriptor> cursor_observation_registry()
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Expose the static optional cursor metric catalog. |
| inputs / outputs | Returns immutable borrowed descriptor span. |
| invariants | Registry records availability/units; a declared metric need not be enabled. |
| ownership | Program-lifetime static view. |
| failure | Value declaration/default initialization itself has no recovery path. |
| cost | Constant span construction. |
| Design | [docs/observability.md](../../../../../observability.md), [include/crown/runtime/observation.hpp](../../../../../../include/crown/runtime/observation.hpp), [docs/query_memory.md](../../../../../query_memory.md) |

## B0046

[Lines 217–235](../../../../../../include/crown/runtime/support.hpp#L217); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct CursorObservation
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Retain one lifecycle snapshot with unavailable/disabled distinctions. |
| inputs / outputs | Options/configuration, owner/epoch/cursor identity, provenance, terminal status, mandatory work and optional values. |
| invariants | Unknown metric ID returns a static unavailable value; saturation and clock regressions are explicit. |
| ownership | Copied fixed-size report; descriptor strings remain static; no rows or data-lease ownership. |
| failure | metric() is noexcept; plain value copy adds no recovery wrapper. |
| cost | Fixed report copy and registry-sized initialization. |
| Design | [docs/observability.md](../../../../../observability.md), [include/crown/runtime/observation.hpp](../../../../../../include/crown/runtime/observation.hpp), [docs/query_memory.md](../../../../../query_memory.md) |

## B0047

[Lines 236–241](../../../../../../include/crown/runtime/support.hpp#L236); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct NodeStateGauge
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Capture exact local relation cardinalities without enumerating answers. |
| inputs / outputs | Node/kind and record/S/P/E gauges. |
| invariants | E availability is absent outside C*; counts are local relation sizes, not complete answer count. |
| ownership | Plain value metadata; no runtime or work-grant authority is created. |
| failure | Value declaration/default initialization itself has no recovery path. |
| cost | Fixed-size scalar metadata; no allocation for this record alone. |
| Design | [docs/observability.md](../../../../../observability.md), [include/crown/runtime/observation.hpp](../../../../../../include/crown/runtime/observation.hpp), [docs/query_memory.md](../../../../../query_memory.md) |

## B0048

[Lines 242–242](../../../../../../include/crown/runtime/support.hpp#L242); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct BaseStateGauge
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Represent one physical-source cardinality in a shared gauge DTO. |
| inputs / outputs | TableId and tuple count. |
| invariants | Logical Support alone does not fabricate physical source populations. |
| ownership | Plain value metadata; no runtime or work-grant authority is created. |
| failure | Value declaration/default initialization itself has no recovery path. |
| cost | Fixed-size scalar metadata; no allocation for this record alone. |
| Design | [docs/observability.md](../../../../../observability.md), [include/crown/runtime/observation.hpp](../../../../../../include/crown/runtime/observation.hpp), [docs/query_memory.md](../../../../../query_memory.md) |

## B0049

[Lines 243–251](../../../../../../include/crown/runtime/support.hpp#L243); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct CommittedStateGauges
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Export requested committed local cardinalities as caller-owned metadata. |
| inputs / outputs | Owner/sequence, base/node lists and optional wider facts. |
| invariants | Uncomputed full-result/memory/checkpoint/recovery facts stay unavailable, not zero. |
| ownership | Ordinary outer vectors are explicit caller DTO allocations. |
| failure | Explicit capture may allocate and reject busy state. |
| cost | O(plan nodes) size reads and vector capacity; no answer enumeration. |
| Design | [docs/observability.md](../../../../../observability.md), [include/crown/runtime/observation.hpp](../../../../../../include/crown/runtime/observation.hpp), [docs/query_memory.md](../../../../../query_memory.md) |

## B0050

[Lines 252–252](../../../../../../include/crown/runtime/support.hpp#L252); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
// Native retained/report variant;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Distinguish native funded gauges from the caller DTO above. |
| inputs / outputs | The following record uses OwnerAllocator for retained report arrays. |
| invariants | Same logical facts; different explicit ownership/accounting boundary. |
| ownership | Documentation only. |
| failure | Value declaration/default initialization itself has no recovery path. |
| cost | No runtime work from comment. |
| Design | [docs/observability.md](../../../../../observability.md), [include/crown/runtime/observation.hpp](../../../../../../include/crown/runtime/observation.hpp), [docs/query_memory.md](../../../../../query_memory.md) |

## B0051

[Lines 253–269](../../../../../../include/crown/runtime/support.hpp#L253); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct CapturedStateGauges
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Own a retained account-funded gauge snapshot. |
| inputs / outputs | Existing account constructs two empty OwnerAllocator vectors; copy assignment builds temporary before noexcept transfer. |
| invariants | Copy preserves source ownership/account; no new cap or post-hoc accounting ticket. |
| ownership | Native capture owner tag4 funds arrays; moves transfer allocators/storage. |
| failure | Copy allocation failure preserves destination; no generic catch is needed. |
| cost | O(gauge array length) copy when requested; fixed empty/move setup. |
| Design | [docs/observability.md](../../../../../observability.md), [include/crown/runtime/observation.hpp](../../../../../../include/crown/runtime/observation.hpp), [docs/query_memory.md](../../../../../query_memory.md) |

## B0052

[Lines 270–305](../../../../../../include/crown/runtime/support.hpp#L270); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
class ResultCursor {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Read committed/projected/full-witness rows through one move-only token. |
| inputs / outputs | results/completions/witnesses/key APIs return owning rows via next()/next_native(); output order is unspecified. |
| invariants | Single caller may interleave readers; last row still holds lease until terminal next/cancel/destruction/failure. Exhausted/cancelled return null; failed/moved next rejects. |
| ownership | Rows own original-account payloads. layout()/metrics() references borrow the cursor and must not outlive it; moving/destroying token invalidates those references. |
| failure | Startup publishes no reader/link on failure; next failure closes borrowed state before propagation/translation. |
| cost | O(selected main/probe frames and constraint widths) startup/scratch; actual tuple/overlay/witness/output costs. No constant public-delay or whole-result materialization guarantee. |
| Design | [docs/result_cursors.md](../../../../../result_cursors.md), [docs/epoch_views.md](../../../../../epoch_views.md), [docs/query_memory.md](../../../../../query_memory.md), [P1 arXiv:2301.04003v2 §5.1 Algorithm 5; native ownership, overlays and work counters are local engineering contracts](https://arxiv.org/pdf/2301.04003v2) |

## B0053

[Lines 306–341](../../../../../../include/crown/runtime/support.hpp#L306); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
class EpochView {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Retain one immutable journal-backed before/after relation context. |
| inputs / outputs | Copyable view exposes visible completions, full local witnesses and E scans/buckets for its side. |
| invariants | Copies/cursors share one group lease. Commit preserves it; pending rollback aborts it and closes linked cursors. A held view blocks further stages even without a live cursor. |
| ownership | Group retains affected journal pins/overlay keys, not a complete old database. close() releases only this view reference. |
| failure | Construction failure leaves pending epoch active; aborted relation reads reject, identity scalar metadata remains inspectable while Data exists. |
| cost | O(plan relation descriptors plus changed memberships/index overlay entries), actual map/deep-key work, not a free snapshot. |
| Design | [docs/result_cursors.md](../../../../../result_cursors.md), [docs/epoch_views.md](../../../../../epoch_views.md), [docs/query_memory.md](../../../../../query_memory.md), [P1 arXiv:2301.04003v2 §5.1 Algorithm 5; native ownership, overlays and work counters are local engineering contracts](https://arxiv.org/pdf/2301.04003v2) |

## B0054

[Lines 342–377](../../../../../../include/crown/runtime/support.hpp#L342); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
class PendingEpoch {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Hold one exclusive single-polarity multi-stage logical update. |
| inputs / outputs | stage(node,row) drains changes; preview/snapshot/view inspect tentative state; commit advances one sequence. |
| invariants | No-op stages add no events. Prefix-busy rejection leaves active state; other staging failures auto-abort all stages. Preview data must remain unpublished. |
| ownership | Move-only token retains runtime/grant/inverses and optional view group; destructor restores uncommitted state. |
| failure | Commit validates before the nonthrowing barrier; rollback/cancel path is allocation-free. |
| cost | Actual affected-record/child-flag/table undo work across stages; no query-wide state clone. |
| Design | [docs/runtime_support.md](../../../../../runtime_support.md), [docs/support_invariants.md](../../../../../support_invariants.md), [docs/prepared_epochs.md](../../../../../prepared_epochs.md), [docs/query_memory.md](../../../../../query_memory.md) |

## B0055

[Lines 378–380](../../../../../../include/crown/runtime/support.hpp#L378); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
   private:
    friend class SupportRuntime;
    friend class PhysicalRuntime;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Restrict prepared stage checkpoint/native routing authority. |
| inputs / outputs | Private friend coordinator declarations before Checkpoint. |
| invariants | Public callers cannot inject a manufactured checkpoint or native tuple route. |
| ownership | Declarations transfer no runtime ownership. |
| failure | Value declaration/default initialization itself has no recovery path. |
| cost | No runtime work. |
| Design | [docs/runtime_support.md](../../../../../runtime_support.md), [docs/support_invariants.md](../../../../../support_invariants.md), [docs/query_memory.md](../../../../../query_memory.md) |

## B0056

[Lines 381–386](../../../../../../include/crown/runtime/support.hpp#L381); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct Checkpoint
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Record one drained stage-prefix identity for physical coordination. |
| inputs / outputs | Owner, epoch sequence, prefix ordinal, journal size and existence. |
| invariants | stage_records requires exactly one changed stage after this checkpoint and matching owner/sequence. |
| ownership | Scalar copied private marker; journal remains pending-owned. |
| failure | Mismatched/old/multistage marker rejects as invalid_snapshot. |
| cost | Fixed capture/check. |
| Design | [docs/runtime_support.md](../../../../../runtime_support.md), [docs/support_invariants.md](../../../../../support_invariants.md), [docs/query_memory.md](../../../../../query_memory.md) |

## B0057

[Lines 387–422](../../../../../../include/crown/runtime/support.hpp#L387); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
[[nodiscard]] Checkpoint checkpoint() const;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Declare private stage composition plus public construction and capture boundaries. |
| inputs / outputs | Checkpoint/suffix/view/native-stage methods, runtime constructors/moves, plan/usage/capture/statistics APIs. |
| invariants | Native staging shares existing transaction/grant; captures are explicit. Copies of runtime are prohibited. |
| ownership | Pending owns original account/undo; runtime owns shared Impl; returned captures retain their specified native/caller storage. |
| failure | Closed tokens reject; constructor/capture resource failures propagate without commit. |
| cost | Direct ownership moves/accessors; stage/capture costs are explicit implementations below. |
| Design | [docs/runtime_support.md](../../../../../runtime_support.md), [docs/support_invariants.md](../../../../../support_invariants.md), [docs/query_memory.md](../../../../../query_memory.md) |

## B0058

[Lines 423–458](../../../../../../include/crown/runtime/support.hpp#L423); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
  [[nodiscard]] SupportOwnerId owner() const;
  [[nodiscard]] std::uint64_t sequence() const;
  [[nodiscard]] bool ready() const;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Declare committed operations and private physical-coordinator hooks. |
| inputs / outputs | Owner/sequence/readiness, epoch/apply, result/context APIs, diagnostics and storage/observation/workload hooks. |
| invariants | Committed state readers reject active prepared writes; active leases reject writes including no-ops. Full snapshots/diagnostics are explicit. |
| ownership | Borrowed views require live owners; owning results/captures use documented native or explicit export boundary. |
| failure | Invalid owner/IDs/options/sequence, busy and resource failures remain visible; no silent recovery. |
| cost | Direct accessors or affected propagation; full capture/recompute/export methods have population-dependent cost. |
| Design | [docs/runtime_support.md](../../../../../runtime_support.md), [docs/support_invariants.md](../../../../../support_invariants.md), [docs/query_memory.md](../../../../../query_memory.md) |

## B0059

[Lines 459–463](../../../../../../include/crown/runtime/support.hpp#L459); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
  [[nodiscard]] const CompiledProgram& compiled_program() const;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Close private runtime ownership with immutable program/Impl accessors. |
| inputs / outputs | Shared Impl plus guarded private accessors. |
| invariants | Program and metadata borrows require retained runtime/Impl; moving facade does not clone query state. |
| ownership | impl_ strongly owns complete runtime; readers/pending tokens can retain it independently. |
| failure | Moved-from facade access rejects invalid_runtime. |
| cost | Fixed shared-pointer guard/access; final owner release can destroy complete state. |
| Design | [docs/runtime_support.md](../../../../../runtime_support.md), [docs/support_invariants.md](../../../../../support_invariants.md), [docs/query_memory.md](../../../../../query_memory.md) |
