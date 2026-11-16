# `include/crown/observability/statistics_explain.hpp` — block usage map

[Source](../../../../../../include/crown/observability/statistics_explain.hpp) · [Source index](../../../../README.md) · [Subsystem contracts](../../../../subsystem_contracts.md) · [Reviewed primitives](../../../../primitives.md)

Capture bounded distributions, workload counters, owner memory and explain observations without mislabeling partial information as exact.

Snapshot SHA-256: `963d33fc5f9b4209b639282a6e22e5960d7491a7698d006253aa574bef916fd4`. 51 lines partitioned into 11 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [statistics](../../../../subsystem_contracts.md#statistics). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/statistics.md](../../../../../statistics.md), [docs/observability.md](../../../../../observability.md), [docs/memory_reports.md](../../../../../memory_reports.md), [docs/ranking_evaluation.md](../../../../../ranking_evaluation.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–5](../../../../../../include/crown/observability/statistics_explain.hpp#L1) | Imports dependencies; guards repeated header inclusion; declares namespace scope. |  · [reviewed contract](#b0001) |
| [B0002 · 6–12](../../../../../../include/crown/observability/statistics_explain.hpp#L6) | Type/record definition: struct StatisticsCaptureOptions | source comment (unverified): // Absent means metadata/workload only. No default state traversal. · [reviewed contract](#b0002) |
| [B0003 · 13–13](../../../../../../include/crown/observability/statistics_explain.hpp#L13) | Type/record definition: enum class IntervalComparison |  · [reviewed contract](#b0003) |
| [B0004 · 14–20](../../../../../../include/crown/observability/statistics_explain.hpp#L14) | Type/record definition: struct StatisticsComparison |  · [reviewed contract](#b0004) |
| [B0005 · 21–25](../../../../../../include/crown/observability/statistics_explain.hpp#L21) | declares types or opens a type body; declares callable signatures; declares values/defaults or compile-time conditions. | source comment (unverified): // Factory-only owning report. No constructor accepts caller stamps, paired · [reviewed contract](#b0005) |
| [B0006 · 26–26](../../../../../../include/crown/observability/statistics_explain.hpp#L26) | Callable definition: StatisticsExplanation(StatisticsExplanation&& other) noexcept:data_(other.data_) | calls data_ · [reviewed contract](#b0006) |
| [B0007 · 27–27](../../../../../../include/crown/observability/statistics_explain.hpp#L27) | declares callable signatures; declares values/defaults or compile-time conditions. |  · [reviewed contract](#b0007) |
| [B0008 · 28–28](../../../../../../include/crown/observability/statistics_explain.hpp#L28) | Callable definition: StatisticsExplanation& operator=(StatisticsExplanation&& other) noexcept | returns *this · [reviewed contract](#b0008) |
| [B0009 · 29–44](../../../../../../include/crown/observability/statistics_explain.hpp#L29) | declares types or opens a type body; declares callable signatures; declares values/defaults or compile-time conditions. |  · [reviewed contract](#b0009) |
| [B0010 · 45–45](../../../../../../include/crown/observability/statistics_explain.hpp#L45) | Callable definition: explicit StatisticsExplanation(std::shared_ptr&lt;const Data&gt; value):data_(std::move(value)) | calls data_, std::move · [reviewed contract](#b0010) |
| [B0011 · 46–51](../../../../../../include/crown/observability/statistics_explain.hpp#L46) | declares callable signatures; declares values/defaults or compile-time conditions. |  · [reviewed contract](#b0011) |

## B0001

[Lines 1–5](../../../../../../include/crown/observability/statistics_explain.hpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
#pragma once
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Declare the observability statistics_explain public interface and its required types. |
| inputs / outputs | Header imports its explicit dependencies and declares the APIs/contracts below. |
| invariants | Inclusion does not construct a live query, source, report, proof or file owner. |
| ownership | Declarations retain no instance; object ownership and copies are specified at the individual APIs. |
| failure | Compile-time dependency/declaration boundary; runtime failures belong to instantiated objects/operations. |
| cost | No runtime action from inclusion itself; inline methods retain their stated actual costs. |
| Design | [include/crown/observability/statistics_explain.hpp](../../../../../../include/crown/observability/statistics_explain.hpp), [src/observability/statistics_explain.cpp](../../../../../../src/observability/statistics_explain.cpp), [docs/statistics.md](../../../../../statistics.md) |

## B0002

[Lines 6–12](../../../../../../include/crown/observability/statistics_explain.hpp#L6); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct StatisticsCaptureOptions {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Configure an explicit actual-owner statistics read. |
| inputs / outputs | Optional owning state request, state sublimits and structural report limit; absent state means metadata/workload only. |
| invariants | Requests are configuration, not captured facts or authority. Metadata/workload/trace capture still has its actual costs when state is absent. |
| ownership | state owns ordinary request vectors and optional field vectors; copying options can allocate before capture. |
| failure | Declaration/field initialization performs no semantic validation. Consumers validate the actual values at their own boundary. |
| cost | Request-copy cost plus later chosen native diagnostic work; absent request avoids default state population traversal. |
| Design | [include/crown/observability/statistics_explain.hpp](../../../../../../include/crown/observability/statistics_explain.hpp), [src/observability/statistics_explain.cpp](../../../../../../src/observability/statistics_explain.cpp), [docs/statistics.md](../../../../../statistics.md) |

```text
std::optional<runtime::statistics::OwnerRequest> state;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | The optional explicit state-component request, owning its selection/field vectors. |
| inputs / outputs | Stores/exposes the optional explicit state-component request, owning its selection/field vectors. |
| invariants | Requests are configuration, not captured facts or authority. Metadata/workload/trace capture still has its actual costs when state is absent. |
| ownership | state owns ordinary request vectors and optional field vectors; copying options can allocate before capture. |
| failure | Assignment adds no validation; aggregate construction/copy has the ownership costs stated here. |
| cost | Request-copy cost plus later chosen native diagnostic work; absent request avoids default state population traversal. |
| Design | [include/crown/observability/statistics_explain.hpp](../../../../../../include/crown/observability/statistics_explain.hpp), [src/observability/statistics_explain.cpp](../../../../../../src/observability/statistics_explain.cpp), [docs/statistics.md](../../../../../statistics.md) |

```text
runtime::statistics::Limits state_limits;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | The separate state-capture selected work/row/key/byte limits. |
| inputs / outputs | Stores/exposes the separate state-capture selected work/row/key/byte limits. |
| invariants | Requests are configuration, not captured facts or authority. Metadata/workload/trace capture still has its actual costs when state is absent. |
| ownership | state owns ordinary request vectors and optional field vectors; copying options can allocate before capture. |
| failure | Assignment adds no validation; aggregate construction/copy has the ownership costs stated here. |
| cost | Request-copy cost plus later chosen native diagnostic work; absent request avoids default state population traversal. |
| Design | [include/crown/observability/statistics_explain.hpp](../../../../../../include/crown/observability/statistics_explain.hpp), [src/observability/statistics_explain.cpp](../../../../../../src/observability/statistics_explain.cpp), [docs/statistics.md](../../../../../statistics.md) |

```text
ExplainLimits structure;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | The structural explanation node-count cap. |
| inputs / outputs | Stores/exposes the structural explanation node-count cap. |
| invariants | Requests are configuration, not captured facts or authority. Metadata/workload/trace capture still has its actual costs when state is absent. |
| ownership | state owns ordinary request vectors and optional field vectors; copying options can allocate before capture. |
| failure | Assignment adds no validation; aggregate construction/copy has the ownership costs stated here. |
| cost | Request-copy cost plus later chosen native diagnostic work; absent request avoids default state population traversal. |
| Design | [include/crown/observability/statistics_explain.hpp](../../../../../../include/crown/observability/statistics_explain.hpp), [src/observability/statistics_explain.cpp](../../../../../../src/observability/statistics_explain.cpp), [docs/statistics.md](../../../../../statistics.md) |

## B0003

[Lines 13–13](../../../../../../include/crown/observability/statistics_explain.hpp#L13); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
enum class IntervalComparison {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Present independent workload interval-comparison availability. |
| inputs / outputs | same/changed/foreign-owner/saturated/unavailable without guessing from missing counters. |
| invariants | Public value/configuration only; changing fields does not perform admission, execute an input or create proof authority. |
| ownership | Inline fixed fields only; copying these values allocates no container or text. No source/native owner is retained. |
| failure | Declaration/field initialization performs no semantic validation. Consumers validate the actual values at their own boundary. |
| cost | Fixed-size initialization/copy/comparison; declaration itself performs no runtime scan or I/O. |
| Design | [include/crown/observability/statistics_explain.hpp](../../../../../../include/crown/observability/statistics_explain.hpp), [src/observability/statistics_explain.cpp](../../../../../../src/observability/statistics_explain.cpp), [docs/statistics.md](../../../../../statistics.md) |

## B0004

[Lines 14–20](../../../../../../include/crown/observability/statistics_explain.hpp#L14); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct StatisticsComparison {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Own descriptive prior/current report freshness comparisons. |
| inputs / outputs | Owner/sequence/lag fields, optional owner-data freshness and independent configuration/reset/segment domains. |
| invariants | Public value/configuration only; changing fields does not perform admission, execute an input or create proof authority. |
| ownership | Inline fixed fields only; copying these values allocates no container or text. No source/native owner is retained. |
| failure | Declaration/field initialization performs no semantic validation. Consumers validate the actual values at their own boundary. |
| cost | Fixed-size initialization/copy/comparison; declaration itself performs no runtime scan or I/O. |
| Design | [include/crown/observability/statistics_explain.hpp](../../../../../../include/crown/observability/statistics_explain.hpp), [src/observability/statistics_explain.cpp](../../../../../../src/observability/statistics_explain.cpp), [docs/statistics.md](../../../../../statistics.md) |

```text
std::uint64_t previous_owner{},previous_sequence{},actual_owner{},actual_sequence{},max_event_lag{};
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | The two report boundaries and caller-declared tolerated event lag. |
| inputs / outputs | Stores/exposes the two report boundaries and caller-declared tolerated event lag. |
| invariants | This field is descriptive/configuration data, not an independent admission or publication capability. |
| ownership | Inline fixed fields only; copying these values allocates no container or text. No source/native owner is retained. |
| failure | Assignment adds no validation; aggregate construction/copy has the ownership costs stated here. |
| cost | Fixed-size initialization/copy/comparison; declaration itself performs no runtime scan or I/O. |
| Design | [include/crown/observability/statistics_explain.hpp](../../../../../../include/crown/observability/statistics_explain.hpp), [src/observability/statistics_explain.cpp](../../../../../../src/observability/statistics_explain.cpp), [docs/statistics.md](../../../../../statistics.md) |

```text
std::optional<runtime::statistics::Freshness> data;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | The optional actual owner-data freshness comparison. |
| inputs / outputs | Stores/exposes the optional actual owner-data freshness comparison. |
| invariants | This field is descriptive/configuration data, not an independent admission or publication capability. |
| ownership | Inline fixed fields only; copying these values allocates no container or text. No source/native owner is retained. |
| failure | Assignment adds no validation; aggregate construction/copy has the ownership costs stated here. |
| cost | Fixed-size initialization/copy/comparison; declaration itself performs no runtime scan or I/O. |
| Design | [include/crown/observability/statistics_explain.hpp](../../../../../../include/crown/observability/statistics_explain.hpp), [src/observability/statistics_explain.cpp](../../../../../../src/observability/statistics_explain.cpp), [docs/statistics.md](../../../../../statistics.md) |

```text
IntervalComparison configuration=
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | The independent configuration-generation comparison. |
| inputs / outputs | Stores/exposes the independent configuration-generation comparison. |
| invariants | This field is descriptive/configuration data, not an independent admission or publication capability. |
| ownership | Inline fixed fields only; copying these values allocates no container or text. No source/native owner is retained. |
| failure | Assignment adds no validation; aggregate construction/copy has the ownership costs stated here. |
| cost | Fixed-size initialization/copy/comparison; declaration itself performs no runtime scan or I/O. |
| Design | [include/crown/observability/statistics_explain.hpp](../../../../../../include/crown/observability/statistics_explain.hpp), [src/observability/statistics_explain.cpp](../../../../../../src/observability/statistics_explain.cpp), [docs/statistics.md](../../../../../statistics.md) |

```text
IntervalComparison reset=
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | The independent collector reset-generation comparison. |
| inputs / outputs | Stores/exposes the independent collector reset-generation comparison. |
| invariants | This field is descriptive/configuration data, not an independent admission or publication capability. |
| ownership | Inline fixed fields only; copying these values allocates no container or text. No source/native owner is retained. |
| failure | Assignment adds no validation; aggregate construction/copy has the ownership costs stated here. |
| cost | Fixed-size initialization/copy/comparison; declaration itself performs no runtime scan or I/O. |
| Design | [include/crown/observability/statistics_explain.hpp](../../../../../../include/crown/observability/statistics_explain.hpp), [src/observability/statistics_explain.cpp](../../../../../../src/observability/statistics_explain.cpp), [docs/statistics.md](../../../../../statistics.md) |

```text
IntervalComparison segment=
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | The independent workload segment comparison. |
| inputs / outputs | Stores/exposes the independent workload segment comparison. |
| invariants | This field is descriptive/configuration data, not an independent admission or publication capability. |
| ownership | Inline fixed fields only; copying these values allocates no container or text. No source/native owner is retained. |
| failure | Assignment adds no validation; aggregate construction/copy has the ownership costs stated here. |
| cost | Fixed-size initialization/copy/comparison; declaration itself performs no runtime scan or I/O. |
| Design | [include/crown/observability/statistics_explain.hpp](../../../../../../include/crown/observability/statistics_explain.hpp), [src/observability/statistics_explain.cpp](../../../../../../src/observability/statistics_explain.cpp), [docs/statistics.md](../../../../../statistics.md) |

## B0005

[Lines 21–25](../../../../../../include/crown/observability/statistics_explain.hpp#L21); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
class StatisticsExplanation
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Own one actual-bound format3 statistics report. |
| inputs / outputs | Closed factories combine real mode/plan/trace/session boundary with native state/workload captures and optional prior-report comparison. |
| invariants | No public constructor accepts caller stamps, mismatched snapshots, availability flags or unchecked context. Actual owner/sequence/options/mode consistency is rechecked. |
| ownership | Factory-only shared immutable accounted Data retains PlanExplanation, optional CombinedCapture, workload options and fixed comparison metadata. It retains owned capture/proof/plan graphs, not a mutable owner/cursor/lease. Custom moves copy the shared descriptor, leaving the source valid; getters borrow Data. |
| failure | Binding/owner/guard/capture/structure/allocation errors propagate before return. Missing state observations remain typed unavailable, not synthesized zeros. |
| cost | Funded report/context/trace captures plus optional selected state traversal. Metadata-only still copies workload/trace metadata; prior comparisons use fixed captured stamps. |
| Design | [include/crown/observability/statistics_explain.hpp](../../../../../../include/crown/observability/statistics_explain.hpp), [src/observability/statistics_explain.cpp](../../../../../../src/observability/statistics_explain.cpp), [docs/statistics.md](../../../../../statistics.md) |

```text
StatisticsExplanation(const StatisticsExplanation&) noexcept=default;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Share the immutable report graph. |
| inputs / outputs | Copies/shares Data rather than independently recapturing facts. |
| invariants | Closed factories and copy-like moves keep nonempty handle invariants required by noexcept getters. |
| ownership | Factory-only shared immutable accounted Data retains PlanExplanation, optional CombinedCapture, workload options and fixed comparison metadata. It retains owned capture/proof/plan graphs, not a mutable owner/cursor/lease. Custom moves copy the shared descriptor, leaving the source valid; getters borrow Data. |
| failure | No throwing shared descriptor operation; retained graph cleanup follows its native nonthrowing destruction rules. |
| cost | Fixed shared reference operation, no capture/deep clone. |
| Design | [include/crown/observability/statistics_explain.hpp](../../../../../../include/crown/observability/statistics_explain.hpp), [src/observability/statistics_explain.cpp](../../../../../../src/observability/statistics_explain.cpp), [docs/statistics.md](../../../../../statistics.md) |

## B0006

[Lines 26–26](../../../../../../include/crown/observability/statistics_explain.hpp#L26); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
StatisticsExplanation(StatisticsExplanation&& other) noexcept:
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Copy-like move retaining both report handles. |
| inputs / outputs | Copies/shares Data rather than independently recapturing facts. |
| invariants | Closed factories and copy-like moves keep nonempty handle invariants required by noexcept getters. |
| ownership | Factory-only shared immutable accounted Data retains PlanExplanation, optional CombinedCapture, workload options and fixed comparison metadata. It retains owned capture/proof/plan graphs, not a mutable owner/cursor/lease. Custom moves copy the shared descriptor, leaving the source valid; getters borrow Data. |
| failure | No throwing shared descriptor operation; retained graph cleanup follows its native nonthrowing destruction rules. |
| cost | Fixed shared reference operation; source remains valid. |
| Design | [include/crown/observability/statistics_explain.hpp](../../../../../../include/crown/observability/statistics_explain.hpp), [src/observability/statistics_explain.cpp](../../../../../../src/observability/statistics_explain.cpp), [docs/statistics.md](../../../../../statistics.md) |

## B0007

[Lines 27–27](../../../../../../include/crown/observability/statistics_explain.hpp#L27); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
StatisticsExplanation& operator=(const StatisticsExplanation&) noexcept=default;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Replace by shared immutable report copy. |
| inputs / outputs | Copies/shares Data rather than independently recapturing facts. |
| invariants | Closed factories and copy-like moves keep nonempty handle invariants required by noexcept getters. |
| ownership | Factory-only shared immutable accounted Data retains PlanExplanation, optional CombinedCapture, workload options and fixed comparison metadata. It retains owned capture/proof/plan graphs, not a mutable owner/cursor/lease. Custom moves copy the shared descriptor, leaving the source valid; getters borrow Data. |
| failure | No throwing shared descriptor operation; retained graph cleanup follows its native nonthrowing destruction rules. |
| cost | Shared retention plus actual last release of any old graph. |
| Design | [include/crown/observability/statistics_explain.hpp](../../../../../../include/crown/observability/statistics_explain.hpp), [src/observability/statistics_explain.cpp](../../../../../../src/observability/statistics_explain.cpp), [docs/statistics.md](../../../../../statistics.md) |

## B0008

[Lines 28–28](../../../../../../include/crown/observability/statistics_explain.hpp#L28); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
StatisticsExplanation& operator=(StatisticsExplanation&& other) noexcept
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Copy-like move assignment of report ownership. |
| inputs / outputs | Copies/shares Data rather than independently recapturing facts. |
| invariants | Closed factories and copy-like moves keep nonempty handle invariants required by noexcept getters. |
| ownership | Factory-only shared immutable accounted Data retains PlanExplanation, optional CombinedCapture, workload options and fixed comparison metadata. It retains owned capture/proof/plan graphs, not a mutable owner/cursor/lease. Custom moves copy the shared descriptor, leaving the source valid; getters borrow Data. |
| failure | No throwing shared descriptor operation; retained graph cleanup follows its native nonthrowing destruction rules. |
| cost | Shared retention/source preservation plus actual old graph release. |
| Design | [include/crown/observability/statistics_explain.hpp](../../../../../../include/crown/observability/statistics_explain.hpp), [src/observability/statistics_explain.cpp](../../../../../../src/observability/statistics_explain.cpp), [docs/statistics.md](../../../../../statistics.md) |

## B0009

[Lines 29–44](../../../../../../include/crown/observability/statistics_explain.hpp#L29); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
static StatisticsExplanation capture(const runtime::DeltaRuntime&
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Capture a format3 actual-owner statistics report. |
| inputs / outputs | Capture actual runtime mode/trace/cursor, combined state/workload and options. |
| invariants | Caller preserves synchronous exclusive access. Optional previous is borrowed only during capture; result stores comparison values, not its pointer. |
| ownership | Factory-only shared immutable accounted Data retains PlanExplanation, optional CombinedCapture, workload options and fixed comparison metadata. It retains owned capture/proof/plan graphs, not a mutable owner/cursor/lease. Custom moves copy the shared descriptor, leaving the source valid; getters borrow Data. |
| failure | Owner/capture/limits/binding/allocation errors propagate; report does not advance input, reset counters or publish native output. |
| cost | Trace/mode/workload capture and optional request-scoped state work; funded report allocations on original account, plus fixed previous-stamp comparisons. |
| Design | [include/crown/observability/statistics_explain.hpp](../../../../../../include/crown/observability/statistics_explain.hpp), [src/observability/statistics_explain.cpp](../../../../../../src/observability/statistics_explain.cpp), [docs/statistics.md](../../../../../statistics.md) |

```text
static StatisticsExplanation capture(const runtime::QuerySession&
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Capture a format3 actual-owner statistics report. |
| inputs / outputs | Capture actual session context under its owner boundary, including released/pending availability. |
| invariants | Caller preserves synchronous exclusive access. Optional previous is borrowed only during capture; result stores comparison values, not its pointer. |
| ownership | Factory-only shared immutable accounted Data retains PlanExplanation, optional CombinedCapture, workload options and fixed comparison metadata. It retains owned capture/proof/plan graphs, not a mutable owner/cursor/lease. Custom moves copy the shared descriptor, leaving the source valid; getters borrow Data. |
| failure | Owner/capture/limits/binding/allocation errors propagate; report does not advance input, reset counters or publish native output. |
| cost | Trace/mode/workload capture and optional request-scoped state work; funded report allocations on original account, plus fixed previous-stamp comparisons. |
| Design | [include/crown/observability/statistics_explain.hpp](../../../../../../include/crown/observability/statistics_explain.hpp), [src/observability/statistics_explain.cpp](../../../../../../src/observability/statistics_explain.cpp), [docs/statistics.md](../../../../../statistics.md) |

```text
const runtime::CompiledProgram& plan() const noexcept;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Borrow the actual report program. |
| inputs / outputs | Immutable admitted metadata retained through its context. |
| invariants | Closed factory/copy-like move guarantees a live immutable Data handle; values remain descriptive rather than publication authority. |
| ownership | Factory-only shared immutable accounted Data retains PlanExplanation, optional CombinedCapture, workload options and fixed comparison metadata. It retains owned capture/proof/plan graphs, not a mutable owner/cursor/lease. Custom moves copy the shared descriptor, leaving the source valid; getters borrow Data. |
| failure | Declared noexcept; no new capture/validation allocation or user callback at access. |
| cost | Fixed reference/value access; explicitly copying owning nested captures has their separate costs. |
| Design | [include/crown/observability/statistics_explain.hpp](../../../../../../include/crown/observability/statistics_explain.hpp), [src/observability/statistics_explain.cpp](../../../../../../src/observability/statistics_explain.cpp), [docs/statistics.md](../../../../../statistics.md) |

```text
const ModeDescriptor& mode() const noexcept;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Borrow captured actual mode/lifecycle metadata. |
| inputs / outputs | Not an editable mode override. |
| invariants | Closed factory/copy-like move guarantees a live immutable Data handle; values remain descriptive rather than publication authority. |
| ownership | Factory-only shared immutable accounted Data retains PlanExplanation, optional CombinedCapture, workload options and fixed comparison metadata. It retains owned capture/proof/plan graphs, not a mutable owner/cursor/lease. Custom moves copy the shared descriptor, leaving the source valid; getters borrow Data. |
| failure | Declared noexcept; no new capture/validation allocation or user callback at access. |
| cost | Fixed reference/value access; explicitly copying owning nested captures has their separate costs. |
| Design | [include/crown/observability/statistics_explain.hpp](../../../../../../include/crown/observability/statistics_explain.hpp), [src/observability/statistics_explain.cpp](../../../../../../src/observability/statistics_explain.cpp), [docs/statistics.md](../../../../../statistics.md) |

```text
const std::optional<runtime::SessionStatus>& session() const noexcept;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Borrow optional captured session status. |
| inputs / outputs | Absent for runtime-only reports. |
| invariants | Closed factory/copy-like move guarantees a live immutable Data handle; values remain descriptive rather than publication authority. |
| ownership | Factory-only shared immutable accounted Data retains PlanExplanation, optional CombinedCapture, workload options and fixed comparison metadata. It retains owned capture/proof/plan graphs, not a mutable owner/cursor/lease. Custom moves copy the shared descriptor, leaving the source valid; getters borrow Data. |
| failure | Declared noexcept; no new capture/validation allocation or user callback at access. |
| cost | Fixed reference/value access; explicitly copying owning nested captures has their separate costs. |
| Design | [include/crown/observability/statistics_explain.hpp](../../../../../../include/crown/observability/statistics_explain.hpp), [src/observability/statistics_explain.cpp](../../../../../../src/observability/statistics_explain.cpp), [docs/statistics.md](../../../../../statistics.md) |

```text
const runtime::ObservationSnapshot& observation() const noexcept;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Borrow actual observation snapshot. |
| inputs / outputs | Includes its genuine begin-bound attempt/current configuration evidence. |
| invariants | Closed factory/copy-like move guarantees a live immutable Data handle; values remain descriptive rather than publication authority. |
| ownership | Factory-only shared immutable accounted Data retains PlanExplanation, optional CombinedCapture, workload options and fixed comparison metadata. It retains owned capture/proof/plan graphs, not a mutable owner/cursor/lease. Custom moves copy the shared descriptor, leaving the source valid; getters borrow Data. |
| failure | Declared noexcept; no new capture/validation allocation or user callback at access. |
| cost | Fixed reference/value access; explicitly copying owning nested captures has their separate costs. |
| Design | [include/crown/observability/statistics_explain.hpp](../../../../../../include/crown/observability/statistics_explain.hpp), [src/observability/statistics_explain.cpp](../../../../../../src/observability/statistics_explain.cpp), [docs/statistics.md](../../../../../statistics.md) |

```text
const runtime::CapturedTraceRecords& trace() const noexcept;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Borrow owned captured trace records. |
| inputs / outputs | Not a live mutable trace ring. |
| invariants | Closed factory/copy-like move guarantees a live immutable Data handle; values remain descriptive rather than publication authority. |
| ownership | Factory-only shared immutable accounted Data retains PlanExplanation, optional CombinedCapture, workload options and fixed comparison metadata. It retains owned capture/proof/plan graphs, not a mutable owner/cursor/lease. Custom moves copy the shared descriptor, leaving the source valid; getters borrow Data. |
| failure | Declared noexcept; no new capture/validation allocation or user callback at access. |
| cost | Fixed reference/value access; explicitly copying owning nested captures has their separate costs. |
| Design | [include/crown/observability/statistics_explain.hpp](../../../../../../include/crown/observability/statistics_explain.hpp), [src/observability/statistics_explain.cpp](../../../../../../src/observability/statistics_explain.cpp), [docs/statistics.md](../../../../../statistics.md) |

```text
const std::optional<runtime::statistics::CombinedCapture>& combined() const noexcept;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Borrow optional paired state/workload capture. |
| inputs / outputs | Absent when actual native runtime is released. |
| invariants | Closed factory/copy-like move guarantees a live immutable Data handle; values remain descriptive rather than publication authority. |
| ownership | Factory-only shared immutable accounted Data retains PlanExplanation, optional CombinedCapture, workload options and fixed comparison metadata. It retains owned capture/proof/plan graphs, not a mutable owner/cursor/lease. Custom moves copy the shared descriptor, leaving the source valid; getters borrow Data. |
| failure | Declared noexcept; no new capture/validation allocation or user callback at access. |
| cost | Fixed reference/value access; explicitly copying owning nested captures has their separate costs. |
| Design | [include/crown/observability/statistics_explain.hpp](../../../../../../include/crown/observability/statistics_explain.hpp), [src/observability/statistics_explain.cpp](../../../../../../src/observability/statistics_explain.cpp), [docs/statistics.md](../../../../../statistics.md) |

```text
const runtime::workload::Options& workload_options() const noexcept;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Borrow actual workload collector configuration. |
| inputs / outputs | Fixed captured configuration, not a request rewrite. |
| invariants | Closed factory/copy-like move guarantees a live immutable Data handle; values remain descriptive rather than publication authority. |
| ownership | Factory-only shared immutable accounted Data retains PlanExplanation, optional CombinedCapture, workload options and fixed comparison metadata. It retains owned capture/proof/plan graphs, not a mutable owner/cursor/lease. Custom moves copy the shared descriptor, leaving the source valid; getters borrow Data. |
| failure | Declared noexcept; no new capture/validation allocation or user callback at access. |
| cost | Fixed reference/value access; explicitly copying owning nested captures has their separate costs. |
| Design | [include/crown/observability/statistics_explain.hpp](../../../../../../include/crown/observability/statistics_explain.hpp), [src/observability/statistics_explain.cpp](../../../../../../src/observability/statistics_explain.cpp), [docs/statistics.md](../../../../../statistics.md) |

```text
bool state_requested() const noexcept;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Read whether caller explicitly requested state capture. |
| inputs / outputs | Distinct from capture availability/completion. |
| invariants | Closed factory/copy-like move guarantees a live immutable Data handle; values remain descriptive rather than publication authority. |
| ownership | Factory-only shared immutable accounted Data retains PlanExplanation, optional CombinedCapture, workload options and fixed comparison metadata. It retains owned capture/proof/plan graphs, not a mutable owner/cursor/lease. Custom moves copy the shared descriptor, leaving the source valid; getters borrow Data. |
| failure | Declared noexcept; no new capture/validation allocation or user callback at access. |
| cost | Fixed reference/value access; explicitly copying owning nested captures has their separate costs. |
| Design | [include/crown/observability/statistics_explain.hpp](../../../../../../include/crown/observability/statistics_explain.hpp), [src/observability/statistics_explain.cpp](../../../../../../src/observability/statistics_explain.cpp), [docs/statistics.md](../../../../../statistics.md) |

```text
const std::optional<StatisticsComparison>& comparison() const noexcept;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Borrow computed prior/current comparison values. |
| inputs / outputs | No prior-report pointer is retained. |
| invariants | Closed factory/copy-like move guarantees a live immutable Data handle; values remain descriptive rather than publication authority. |
| ownership | Factory-only shared immutable accounted Data retains PlanExplanation, optional CombinedCapture, workload options and fixed comparison metadata. It retains owned capture/proof/plan graphs, not a mutable owner/cursor/lease. Custom moves copy the shared descriptor, leaving the source valid; getters borrow Data. |
| failure | Declared noexcept; no new capture/validation allocation or user callback at access. |
| cost | Fixed reference/value access; explicitly copying owning nested captures has their separate costs. |
| Design | [include/crown/observability/statistics_explain.hpp](../../../../../../include/crown/observability/statistics_explain.hpp), [src/observability/statistics_explain.cpp](../../../../../../src/observability/statistics_explain.cpp), [docs/statistics.md](../../../../../statistics.md) |

```text
static constexpr std::uint32_t schema_version=3;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Identify the statistics report transport schema. |
| inputs / outputs | Version3 is separate from frozen legacy EXPLAIN version2. |
| invariants | Mutable data alone never authorizes source acceptance, native plan execution, proof, output acknowledgment or durable publication. |
| ownership | Inline fixed fields only; copying these values allocates no container or text. No source/native owner is retained. |
| failure | Compile-time constant. |
| cost | No runtime cost. |
| Design | [include/crown/observability/statistics_explain.hpp](../../../../../../include/crown/observability/statistics_explain.hpp), [src/observability/statistics_explain.cpp](../../../../../../src/observability/statistics_explain.cpp), [docs/statistics.md](../../../../../statistics.md) |

```text
struct Data;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Hide immutable statistics report storage. |
| inputs / outputs | Private closed factory/storage helper. |
| invariants | No caller-authored stamps, flags or paired snapshots bypass actual-bound report admission. |
| ownership | Factory-only shared immutable accounted Data retains PlanExplanation, optional CombinedCapture, workload options and fixed comparison metadata. It retains owned capture/proof/plan graphs, not a mutable owner/cursor/lease. Custom moves copy the shared descriptor, leaving the source valid; getters borrow Data. |
| failure | Binding/limits/allocation errors propagate from preparation; no new exception framework. |
| cost | Declaration only. |
| Design | [include/crown/observability/statistics_explain.hpp](../../../../../../include/crown/observability/statistics_explain.hpp), [src/observability/statistics_explain.cpp](../../../../../../src/observability/statistics_explain.cpp), [docs/statistics.md](../../../../../statistics.md) |

## B0010

[Lines 45–45](../../../../../../include/crown/observability/statistics_explain.hpp#L45); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
explicit StatisticsExplanation(std::shared_ptr<const Data> value)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Publish an already prepared immutable report graph. |
| inputs / outputs | Private closed factory/storage helper. |
| invariants | No caller-authored stamps, flags or paired snapshots bypass actual-bound report admission. |
| ownership | Factory-only shared immutable accounted Data retains PlanExplanation, optional CombinedCapture, workload options and fixed comparison metadata. It retains owned capture/proof/plan graphs, not a mutable owner/cursor/lease. Custom moves copy the shared descriptor, leaving the source valid; getters borrow Data. |
| failure | Binding/limits/allocation errors propagate from preparation; no new exception framework. |
| cost | Fixed shared descriptor move. |
| Design | [include/crown/observability/statistics_explain.hpp](../../../../../../include/crown/observability/statistics_explain.hpp), [src/observability/statistics_explain.cpp](../../../../../../src/observability/statistics_explain.cpp), [docs/statistics.md](../../../../../statistics.md) |

## B0011

[Lines 46–51](../../../../../../include/crown/observability/statistics_explain.hpp#L46); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
static StatisticsExplanation make(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Bind actual context/state/workload and compute independent comparison domains. |
| inputs / outputs | Private closed factory/storage helper. |
| invariants | No caller-authored stamps, flags or paired snapshots bypass actual-bound report admission. |
| ownership | Factory-only shared immutable accounted Data retains PlanExplanation, optional CombinedCapture, workload options and fixed comparison metadata. It retains owned capture/proof/plan graphs, not a mutable owner/cursor/lease. Custom moves copy the shared descriptor, leaving the source valid; getters borrow Data. |
| failure | Binding/limits/allocation errors propagate from preparation; no new exception framework. |
| cost | Actual owner/sequence/source/mode/options checks, funded Data allocation and fixed comparison-stamp work. |
| Design | [include/crown/observability/statistics_explain.hpp](../../../../../../include/crown/observability/statistics_explain.hpp), [src/observability/statistics_explain.cpp](../../../../../../src/observability/statistics_explain.cpp), [docs/statistics.md](../../../../../statistics.md) |

```text
std::shared_ptr<const Data> data_;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Retain the report context and native capture graphs. |
| inputs / outputs | Private closed factory/storage helper. |
| invariants | No caller-authored stamps, flags or paired snapshots bypass actual-bound report admission. |
| ownership | Factory-only shared immutable accounted Data retains PlanExplanation, optional CombinedCapture, workload options and fixed comparison metadata. It retains owned capture/proof/plan graphs, not a mutable owner/cursor/lease. Custom moves copy the shared descriptor, leaving the source valid; getters borrow Data. |
| failure | Binding/limits/allocation errors propagate from preparation; no new exception framework. |
| cost | Fixed shared retention; last release can destroy substantial captured key/metadata graphs. |
| Design | [include/crown/observability/statistics_explain.hpp](../../../../../../include/crown/observability/statistics_explain.hpp), [src/observability/statistics_explain.cpp](../../../../../../src/observability/statistics_explain.cpp), [docs/statistics.md](../../../../../statistics.md) |
