# `include/crown/runtime/sql_aggregate.hpp` — block usage map

[Source](../../../../../../include/crown/runtime/sql_aggregate.hpp) · [Source index](../../../../README.md) · [Subsystem contracts](../../../../subsystem_contracts.md) · [Reviewed primitives](../../../../primitives.md)

Declare genuine physical-source aggregate ownership, prepared batches and owning output.

Snapshot SHA-256: `cc54b796cfcbee0c6dae1b78232951ef5381ba50a0827227f0de42c030bdfa36`. 114 lines partitioned into 13 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [support](../../../../subsystem_contracts.md#support). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/support_invariants.md](../../../../../support_invariants.md), [docs/runtime_support.md](../../../../../runtime_support.md), [docs/prepared_epochs.md](../../../../../prepared_epochs.md), [docs/result_cursors.md](../../../../../result_cursors.md), [docs/epoch_views.md](../../../../../epoch_views.md), [docs/code_review.md](../../../../../code_review.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–6](../../../../../../include/crown/runtime/sql_aggregate.hpp#L1) | Imports dependencies; guards repeated header inclusion; declares namespace scope. |  · [reviewed contract](#b0001) |
| [B0002 · 7–13](../../../../../../include/crown/runtime/sql_aggregate.hpp#L7) | Type/record definition: struct Options |  · [reviewed contract](#b0002) |
| [B0003 · 14–16](../../../../../../include/crown/runtime/sql_aggregate.hpp#L14) | Type/record definition: struct Metrics : aggregate::BatchMetrics |  · [reviewed contract](#b0003) |
| [B0004 · 17–30](../../../../../../include/crown/runtime/sql_aggregate.hpp#L17) | Type/record definition: struct Epoch | source comment (unverified): // Normalized physical-source weights changed, including filtered/unused sources. · [reviewed contract](#b0004) |
| [B0005 · 31–36](../../../../../../include/crown/runtime/sql_aggregate.hpp#L31) | Type/record definition: struct Snapshot |  · [reviewed contract](#b0005) |
| [B0006 · 37–37](../../../../../../include/crown/runtime/sql_aggregate.hpp#L37) | Explanatory comments or spacing. | source comment (unverified): // Build-only grants remain separate from the operational runtime options. · [reviewed contract](#b0006) |
| [B0007 · 38–41](../../../../../../include/crown/runtime/sql_aggregate.hpp#L38) | Type/record definition: struct RebuildLimits | source comment (unverified): // Build-only grants remain separate from the operational runtime options. · [reviewed contract](#b0007) |
| [B0008 · 42–45](../../../../../../include/crown/runtime/sql_aggregate.hpp#L42) | Type/record definition: struct RebuildMetrics | source comment (unverified): // Includes authenticated static bootstrap and seed. · [reviewed contract](#b0008) |
| [B0009 · 46–47](../../../../../../include/crown/runtime/sql_aggregate.hpp#L46) | Explanatory comments or spacing. | source comment (unverified): // Genuine original binding plus its complete physical source image. This is · [reviewed contract](#b0009) |
| [B0010 · 48–51](../../../../../../include/crown/runtime/sql_aggregate.hpp#L48) | Type/record definition: struct SourceSnapshot | source comment (unverified): // Genuine original binding plus its complete physical source image. This is · [reviewed contract](#b0010) |
| [B0011 · 52–60](../../../../../../include/crown/runtime/sql_aggregate.hpp#L52) | declares namespace scope; declares types or opens a type body. | source comment (unverified): // namespace crown::runtime::sql_aggregate · [reviewed contract](#b0011) |
| [B0012 · 61–82](../../../../../../include/crown/runtime/sql_aggregate.hpp#L61) | Type/record definition: public: class PreparedBatch | source comment (unverified): // Borrowed only while this token remains active and unmoved. Copy the · [reviewed contract](#b0012) |
| [B0013 · 83–114](../../../../../../include/crown/runtime/sql_aggregate.hpp#L83) | declares callable signatures; declares values/defaults or compile-time conditions. | source comment (unverified): // All source/native/group/output preparation is complete before return. · [reviewed contract](#b0013) |

## B0001

[Lines 1–6](../../../../../../include/crown/runtime/sql_aggregate.hpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
#pragma once #include "crown/frontend/sql_aggregate.hpp"
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Import the immutable SQL compiler and physical source runtime public APIs for the new composed facade. |
| inputs / outputs | Header dependencies make SqlAggregateProgram, SqlRowsRuntime/NetBatch, aggregate results, physical tree and account types available. |
| invariants | This declaration header adds no logical-row/bypass authority and does not import implementation internals. |
| ownership | Include declarations only; runtime ownership is defined by the types below. |
| failure | Missing public dependency fails translation-unit compile. |
| cost | Compile-time dependency context only. |
| Design | [build/verification/w06-sql-aggregate-runtime-design-v1/design.md](../../../../../../build/verification/w06-sql-aggregate-runtime-design-v1/design.md), [build/verification/w06-sql-aggregate-runtime-design-v1/cost-and-lifetime.md](../../../../../../build/verification/w06-sql-aggregate-runtime-design-v1/cost-and-lifetime.md), [build/verification/w06-sql-aggregate-runtime-design-v1/reference-plan.md](../../../../../../build/verification/w06-sql-aggregate-runtime-design-v1/reference-plan.md), include/crown/runtime/sql_aggregate.hpp:1, [docs/sql_aggregate_runtime.md](../../../../../sql_aggregate_runtime.md), [docs/aggregates.md](../../../../../aggregates.md), [docs/sql_rows_batches.md](../../../../../sql_rows_batches.md), [docs/query_memory.md](../../../../../query_memory.md) |

## B0002

[Lines 7–13](../../../../../../include/crown/runtime/sql_aggregate.hpp#L7); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct Options
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Define explicit composition source/group/count/runtime memory/output choices. |
| inputs / outputs | Options -&gt; existing source allowances plus cumulative group cap/count cap/standalone runtime byte cap/capture choice. |
| invariants | _into keeps receiver cap; no per-row budget refills; required native bag capture stays internal, group capture separately selected. |
| ownership | Value-only policy record; owning metadata remains actual Program. |
| failure | Invalid count cap rejected by runtime factory; source/native options follow existing factories. |
| cost | Fixed scalar/policy record only; no legacy aggregate Metrics/Epoch layout change. |
| Design | src/runtime/sql_rows.cpp:77, [build/verification/w06-sql-aggregate-runtime-design-v1/cost-and-lifetime.md](../../../../../../build/verification/w06-sql-aggregate-runtime-design-v1/cost-and-lifetime.md), include/crown/runtime/sql_aggregate.hpp:7, [docs/sql_aggregate_runtime.md](../../../../../sql_aggregate_runtime.md), [docs/aggregates.md](../../../../../aggregates.md), [docs/sql_rows_batches.md](../../../../../sql_rows_batches.md), [docs/query_memory.md](../../../../../query_memory.md) |

## B0003

[Lines 14–16](../../../../../../include/crown/runtime/sql_aggregate.hpp#L14); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct Metrics : aggregate::BatchMetrics
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Add only composed delta count outside old single-row metric layouts. |
| inputs / outputs | Inherited BatchMetrics + native_deltas -&gt; selected group/decode work counters. |
| invariants | Counters follow charged admissions; row_probes remains zero; native/source counters reported separately. |
| ownership | Value-only result metadata. |
| failure | No implicit failure or allocations. |
| cost | One additional uint64 in new composed record; old Metrics/Epoch untouched. |
| Design | src/runtime/aggregate.cpp:305, [build/verification/w06-sql-aggregate-runtime-design-v1/cost-and-lifetime.md](../../../../../../build/verification/w06-sql-aggregate-runtime-design-v1/cost-and-lifetime.md), include/crown/runtime/sql_aggregate.hpp:14, [docs/sql_aggregate_runtime.md](../../../../../sql_aggregate_runtime.md), [docs/aggregates.md](../../../../../aggregates.md), [docs/sql_rows_batches.md](../../../../../sql_rows_batches.md), [docs/query_memory.md](../../../../../query_memory.md) |

## B0004

[Lines 17–30](../../../../../../include/crown/runtime/sql_aggregate.hpp#L17); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct Epoch
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Create receiver-owned aggregate epoch output retaining original composed schema identity. |
| inputs / outputs | Account/next/genuine Program/capture choice -&gt; initialized Epoch with empty native bag/output and zero metrics. |
| invariants | The owning epoch keeps the genuine source native summary/work and explicitly requested native journals, while native.bag_deltas is empty at return because internal D-fact capture is transient. It reports physical changed separately from logical group_changed. |
| ownership | Program shares receiver metadata; output uses OwnerAllocator output_buffer. |
| failure | Allocator construction may reject invalid account before publication; scalar/handle initialization has no body throws. |
| cost | Fixed result record plus requested output capacity reserved for touched groups even if equal rendered results suppress all events; output payloads are receiver-owned. |
| Design | [include/crown/resource/owner_allocator.hpp](../../../../../../include/crown/resource/owner_allocator.hpp), include/crown/runtime/sql_aggregate.hpp:17, src/runtime/sql_aggregate.cpp:235, [docs/sql_aggregate_runtime.md](../../../../../sql_aggregate_runtime.md), [docs/aggregates.md](../../../../../aggregates.md), [docs/sql_rows_batches.md](../../../../../sql_rows_batches.md), [docs/query_memory.md](../../../../../query_memory.md) |

## B0005

[Lines 31–36](../../../../../../include/crown/runtime/sql_aggregate.hpp#L31); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct Snapshot
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Create an eager receiver-owned full-group snapshot with original composed metadata. |
| inputs / outputs | Account/sequence/genuine Program -&gt; empty owning Snapshot vector. |
| invariants | No reader lease or caller-fed logical authority; full keys distinguish equal projected outputs. |
| ownership | Program shares receiver metadata; vector uses output_buffer allocator. |
| failure | Only allocator/account contract construction can fail before result escape. |
| cost | O(1) constructor; requested group payload copying is explicit snapshot work. |
| Design | src/runtime/aggregate_tuple.cpp:74-77, include/crown/runtime/sql_aggregate.hpp:31, src/runtime/sql_aggregate.cpp:239, [docs/sql_aggregate_runtime.md](../../../../../sql_aggregate_runtime.md), [docs/aggregates.md](../../../../../aggregates.md), [docs/sql_rows_batches.md](../../../../../sql_rows_batches.md), [docs/query_memory.md](../../../../../query_memory.md) |

## B0006

[Lines 37–37](../../../../../../include/crown/runtime/sql_aggregate.hpp#L37); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L37-L37:sha256:b2a21c66ed164039c3681eea5385132627e55e216d446cf3c05f81709309f0c8
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Usage note immediately before \`struct RebuildLimits\`: Build-only grants remain separate from the operational runtime options. |
| inputs / outputs | This comment introduces no parameter, field or return value. It documents the adjacent construct beginning at include/crown/runtime/sql_aggregate.hpp:L38; use that declaration for the actual input/output shape. |
| invariants | The source note states: Build-only grants remain separate from the operational runtime options. It is prose guidance; the adjacent implementation is the place to check enforcement. |
| ownership | The note states no ownership relation and retains no value. The adjacent declaration or function controls the actual owner and borrowed-view lifetime. |
| failure | This comment adds no branch or handler. Any failure behavior remains in the adjacent callable implementation and its callers. |
| cost | The prose adds no executable work. Runtime cost belongs to the adjacent operation; the note does not establish a measured or global complexity bound. |
| Design | [docs/aggregates.md](../../../../../aggregates.md), [docs/aggregate_batches.md](../../../../../aggregate_batches.md), [docs/query_memory.md](../../../../../query_memory.md), [docs/code_specs/subsystem_contracts.md](../../../../subsystem_contracts.md) |

## B0007

[Lines 38–41](../../../../../../include/crown/runtime/sql_aggregate.hpp#L38); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct RebuildLimits
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Separate aggregate cold-build controls from normal aggregate options. |
| inputs / outputs | Contains the source cold limits plus one group-work ceiling; \`SqlAggregateRuntime::rebuild_into\` accepts it separately from operational \`Options\`. |
| invariants | Cold grants do not overwrite normal source/native/group limits; indexed grant presence tracks the authentic native backend. |
| ownership | Value-only public limits; no state or account owner. |
| failure | Invalid grants fail at the cold factory’s existing checks/admissions. |
| cost | Fixed scalars/optional work ceiling; no runtime field added to normal Data. |
| Design | [include/crown/runtime/sql_aggregate.hpp](../../../../../../include/crown/runtime/sql_aggregate.hpp), [include/crown/runtime/sql_rows.hpp](../../../../../../include/crown/runtime/sql_rows.hpp), [docs/sql_aggregate_runtime.md §Account and work costs](../../../../../sql_aggregate_runtime.md) |

## B0008

[Lines 42–45](../../../../../../include/crown/runtime/sql_aggregate.hpp#L42); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct RebuildMetrics
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Report the source and group work spent during aggregate reconstruction. |
| inputs / outputs | Nests \`sql_rows::RebuildMetrics\` and aggregate metrics; group metrics include static initialization and the seeded image. |
| invariants | A report is optional and written only after successful reconstruction; fields are selected counters, not elapsed CPU or full allocator measurements. |
| ownership | The returned struct is copied value data; no source/native owner retained. |
| failure | No report is published when a factory exception exits earlier. |
| cost | Fixed counter storage and arithmetic; no metric fields added to hot owner records. |
| Design | [include/crown/runtime/sql_aggregate.hpp](../../../../../../include/crown/runtime/sql_aggregate.hpp), [src/runtime/sql_aggregate.cpp](../../../../../../src/runtime/sql_aggregate.cpp), [docs/sql_aggregate_runtime.md §Account and work costs](../../../../../sql_aggregate_runtime.md) |

## B0009

[Lines 46–47](../../../../../../include/crown/runtime/sql_aggregate.hpp#L46); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L46-L47:sha256:6939400ecfc7a35b7dc725eda710867858abcf3ec29545220e0041f201842f0d
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Usage note immediately before \`struct SourceSnapshot\`: Genuine original binding plus its complete physical source image. This is in-memory capture; a durable descriptor/checkpoint factory remains separate. |
| inputs / outputs | This comment introduces no parameter, field or return value. It documents the adjacent construct beginning at include/crown/runtime/sql_aggregate.hpp:L48; use that declaration for the actual input/output shape. |
| invariants | The source note states: Genuine original binding plus its complete physical source image. This is in-memory capture; a durable descriptor/checkpoint factory remains separate. It is prose guidance; the adjacent implementation is the place to check enforcement. |
| ownership | The note states no ownership relation and retains no value. The adjacent declaration or function controls the actual owner and borrowed-view lifetime. |
| failure | This comment adds no branch or handler. Any failure behavior remains in the adjacent callable implementation and its callers. |
| cost | The prose adds no executable work. Runtime cost belongs to the adjacent operation; the note does not establish a measured or global complexity bound. |
| Design | [docs/aggregates.md](../../../../../aggregates.md), [docs/aggregate_batches.md](../../../../../aggregate_batches.md), [docs/query_memory.md](../../../../../query_memory.md), [docs/code_specs/subsystem_contracts.md](../../../../subsystem_contracts.md) |

## B0010

[Lines 48–51](../../../../../../include/crown/runtime/sql_aggregate.hpp#L48); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct SourceSnapshot {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Pair the genuine original SQL aggregate binding with its physical-source image. |
| inputs / outputs | Contains the immutable SqlAggregateProgram and the child sql_rows::SourceSnapshot at its committed sequence. |
| invariants | This captures original SQL/compiler identity plus complete physical input. It contains no serialized image, import authority, aggregate group-state snapshot, or durable recovery claim. |
| ownership | The outer program handle shares immutable compiler ownership; the child owns its rows vector and shared physical-row/program handles. |
| failure | The aggregate value is a plain holder. Correct capture comes from SqlAggregateRuntime::source_snapshot, which checks owner state and child sequence. |
| cost | No second row vector is introduced by pairing; the child image remains the only physical row collection. |
| Design | [include/crown/runtime/sql_aggregate.hpp](../../../../../../include/crown/runtime/sql_aggregate.hpp), [include/crown/runtime/sql_rows.hpp](../../../../../../include/crown/runtime/sql_rows.hpp), [include/crown/frontend/sql_aggregate.hpp](../../../../../../include/crown/frontend/sql_aggregate.hpp), [src/runtime/sql_aggregate.cpp](../../../../../../src/runtime/sql_aggregate.cpp), [docs/sql_aggregate_runtime.md](../../../../../sql_aggregate_runtime.md) |

## B0011

[Lines 52–60](../../../../../../include/crown/runtime/sql_aggregate.hpp#L52); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
} // namespace crown::runtime::sql_aggregate namespace crown::runtime {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Close the SQL aggregate result namespace and enter the public runtime namespace for SqlAggregateRuntime. |
| inputs / outputs | Namespace boundary only; the following class declares facade construction, observations, NetBatch preparation and Snapshot output. |
| invariants | Facade mutates only through complete physical NetBatch and returns eager result/snapshot ownership. |
| ownership | Public declaration; implementation owns shared Data, token owns unique prepared Data. |
| failure | Malformed declaration fails compile; runtime failures are defined by implementation contracts. |
| cost | No executable cost. |
| Design | [build/verification/w06-sql-aggregate-runtime-design-v1/design.md](../../../../../../build/verification/w06-sql-aggregate-runtime-design-v1/design.md), [build/verification/w06-sql-aggregate-runtime-design-v1/cost-and-lifetime.md](../../../../../../build/verification/w06-sql-aggregate-runtime-design-v1/cost-and-lifetime.md), [build/verification/w06-sql-aggregate-runtime-design-v1/reference-plan.md](../../../../../../build/verification/w06-sql-aggregate-runtime-design-v1/reference-plan.md), include/crown/runtime/sql_aggregate.hpp:37, [docs/sql_aggregate_runtime.md](../../../../../sql_aggregate_runtime.md), [docs/aggregates.md](../../../../../aggregates.md), [docs/sql_rows_batches.md](../../../../../sql_rows_batches.md), [docs/query_memory.md](../../../../../query_memory.md) |

## B0012

[Lines 61–82](../../../../../../include/crown/runtime/sql_aggregate.hpp#L61); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
public: class PreparedBatch
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Declare one typed move-only composed prepared token and explicit borrowed preview lifetime. |
| inputs / outputs | Physical batch preparation -&gt; active/preview/commit/rollback API; no exposed child/logical port. |
| invariants | Only SqlAggregateRuntime constructs; preview lvalue-only; close resets backing promptly; one outer shared owner outlives child/proposals. |
| ownership | AccountedUnique&lt;Data&gt; owns the private outer token/workspace and its active child source token; the active token retains shared runtime Data if the facade moves/dies. Preview borrows only while token remains active and unmoved; commit returns owning Epoch then resets Data. An empty unique deleter may keep only the fixed account-controller handle. |
| failure | Invalid/moved token access rejects; destruction/rollback noexcept; all normal fallible work before internal commit. |
| cost | Fixed token/deleter plus touched proposal maps, copied State, new keys, captured D during prepare, and result capacity/output; close promptly releases D/workspace. |
| Design | [build/verification/w06-sql-aggregate-runtime-design-v1/cost-and-lifetime.md](../../../../../../build/verification/w06-sql-aggregate-runtime-design-v1/cost-and-lifetime.md), [build/verification/w06-sql-aggregate-runtime-design-v1/design.md](../../../../../../build/verification/w06-sql-aggregate-runtime-design-v1/design.md), include/crown/runtime/sql_aggregate.hpp:46, [docs/sql_aggregate_runtime.md](../../../../../sql_aggregate_runtime.md), [docs/aggregates.md](../../../../../aggregates.md), [docs/sql_rows_batches.md](../../../../../sql_rows_batches.md), [docs/query_memory.md](../../../../../query_memory.md) |

## B0013

[Lines 83–114](../../../../../../include/crown/runtime/sql_aggregate.hpp#L83); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
explicit SqlAggregateRuntime(frontend::SqlAggregateProgram, const FreeConnexTree&, const PhysicalOptions& = {}, sql_aggregate::Options = {});
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Keep the original composed constructor and expose reconstruction as a separate genuine-image factory. |
| inputs / outputs | The original constructor still takes SQL program/tree/options; the facade now also declares \`rebuild_into(receiver,image,options,cold_limits,optional_report)\`. |
| invariants | The new factory consumes the real SourceSnapshot and separates cold grants from ordinary Options; it adds no descriptor import or live sequence mutation. |
| ownership | The move-only runtime facade retains shared Data; the rebuilt result owns receiver-funded state and the input snapshot remains caller-owned. |
| failure | Existing constructor/factory errors propagate before publication; the optional report is written only on successful rebuild. |
| cost | The declaration adds no per-update field or branch; actual reconstruction cost belongs to the dedicated factory contract. |
| Design | [include/crown/runtime/sql_aggregate.hpp](../../../../../../include/crown/runtime/sql_aggregate.hpp), [docs/sql_source_images.md §Closed cold reconstruction](../../../../../sql_source_images.md), [docs/sql_aggregate_runtime.md §Usage and plan admission](../../../../../sql_aggregate_runtime.md) |

```text
[[nodiscard]] sql_aggregate::SourceSnapshot source_snapshot(sql_rows::SourceSnapshotLimits = {}) const;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Capture the original SQL aggregate program and its complete physical source image together. |
| inputs / outputs | Source snapshot limits in; aggregate program handle and child physical image at the owner sequence out. |
| invariants | Rejects a prepared aggregate batch before delegation and relies on the source child’s quiescence check. Sequence equality is an internal invariant. It does not evaluate groups, serialize or restore state. |
| ownership | Returns the original immutable SQL binding plus the child’s owning image; no mutable runtime reference or reader lease escapes. |
| failure | Busy owner errors before child capture. Child row-limit, selected-work and allocation failures propagate; incomplete child output is released without changing the runtime. |
| cost | Delegates the full capture cost to the child once, then moves the child and copies one shared aggregate-program handle. It does not duplicate rows or run the aggregate query. |
| Design | [include/crown/runtime/sql_aggregate.hpp](../../../../../../include/crown/runtime/sql_aggregate.hpp), [src/runtime/sql_aggregate.cpp](../../../../../../src/runtime/sql_aggregate.cpp), [src/runtime/sql_rows.cpp](../../../../../../src/runtime/sql_rows.cpp), [tests/unit/sql_source_snapshot_test.cpp](../../../../../../tests/unit/sql_source_snapshot_test.cpp), [docs/sql_aggregate_runtime.md](../../../../../sql_aggregate_runtime.md) |

```text
[[nodiscard]] static SqlAggregateRuntime rebuild_into(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Rebuild one ready composed aggregate owner from a genuine editable physical source image. |
| inputs / outputs | Receiver account, aggregate SourceSnapshot, original operational Options, separate RebuildLimits and optional metrics pointer -&gt; ready SqlAggregateRuntime plus success-only measured counters. |
| invariants | Checks original aggregate/source identity, reimports authentic binding, reruns the actual lowerer/source/weighted factories, verifies physical digests and weighted binding; C=0 bootstrap or one C−1→C seed. No public descriptor import, logical-fact setter or durable checkpoint claim. |
| ownership | The returned facade owns new receiver-account source/native/group state. Snapshot/program/row handles remain caller-owned; row views are borrowed only through synchronous preparation. All temporary cold tokens/captures/grants close before return. |
| failure | Any failure unwinds unpublished state and leaves the optional report untouched; existing validation, diagnostic and RAII rollback paths remain in force. |
| cost | Finite separate lowering/source/native/indexed/group admissions; required native D-fact capture is transient; no joined-row ledger or external change output is retained. Counters are selected work, not CPU or complete allocator bounds. |
| Design | [include/crown/runtime/sql_aggregate.hpp](../../../../../../include/crown/runtime/sql_aggregate.hpp), [docs/sql_source_images.md §Closed cold reconstruction](../../../../../sql_source_images.md), [docs/sql_source_images.md §Recovery boundary](../../../../../sql_source_images.md), [docs/sql_aggregate_runtime.md §Account and work costs](../../../../../sql_aggregate_runtime.md), build/verification/w06-sql-aggregate-cold-rebuild-design-v1/cost-and-lifetime.md:18 |
