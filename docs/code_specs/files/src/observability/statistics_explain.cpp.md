# `src/observability/statistics_explain.cpp` — block usage map

[Source](../../../../../src/observability/statistics_explain.cpp) · [Source index](../../../README.md) · [Subsystem contracts](../../../subsystem_contracts.md) · [Reviewed primitives](../../../primitives.md)

Capture bounded distributions, workload counters, owner memory and explain observations without mislabeling partial information as exact.

Snapshot SHA-256: `32b3b6bdd8bf955e7344d86b10adfafcd0994830158e9fda8bd646835329929f`. 87 lines partitioned into 15 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [statistics](../../../subsystem_contracts.md#statistics). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/statistics.md](../../../../statistics.md), [docs/observability.md](../../../../observability.md), [docs/memory_reports.md](../../../../memory_reports.md), [docs/ranking_evaluation.md](../../../../ranking_evaluation.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–8](../../../../../src/observability/statistics_explain.cpp#L1) | Imports dependencies; declares namespace scope; declares values/defaults or compile-time conditions. | source comment (unverified): // Retains current captured graphs; previous-report comparison stores values only. · [reviewed contract](#b0001) |
| [B0002 · 9–15](../../../../../src/observability/statistics_explain.cpp#L9) | Type/record definition: struct StatisticsExplanation::Data | source comment (unverified): // Retains current captured graphs; previous-report comparison stores values only. · [reviewed contract](#b0002) |
| [B0003 · 16–61](../../../../../src/observability/statistics_explain.cpp#L16) | Callable definition: StatisticsExplanation StatisticsExplanation::make(PlanExplanation context,std::optional&lt;st::CombinedCapture&gt; combined, ws::Option… | calls mode, observation, owner, options; returns old.stamp().owner!=now.stamp().owner?IntervalComparison::foreign_owner:; StatisticsExplanation(std:…; growth make_accounted_shared · [reviewed contract](#b0003) |
| [B0004 · 62–68](../../../../../src/observability/statistics_explain.cpp#L62) | Callable definition: StatisticsExplanation StatisticsExplanation::capture(const runtime::DeltaRuntime& runtime,const StatisticsCaptureOptions& options… | calls PlanExplanation::capture_statistics_context, capture_combined_statistics, make, std::move; returns make(std::move(context),std::move(combined),runtime.workload_statistics_options(),options.state.has… · [reviewed contract](#b0004) |
| [B0005 · 69–77](../../../../../src/observability/statistics_explain.cpp#L69) | Callable definition: StatisticsExplanation StatisticsExplanation::capture(const runtime::QuerySession& session,const StatisticsCaptureOptions& options… | calls capture_statistics_context, combined, workload, pending; returns make(std::move(context),native.combined(),native.workload_options(),native.state_requested(),previo… · [reviewed contract](#b0005) |
| [B0006 · 78–78](../../../../../src/observability/statistics_explain.cpp#L78) | Callable definition: const runtime::CompiledProgram& StatisticsExplanation::plan() const noexcept | calls plan; returns data_-&gt;context.plan() · [reviewed contract](#b0006) |
| [B0007 · 79–79](../../../../../src/observability/statistics_explain.cpp#L79) | Callable definition: const ModeDescriptor& StatisticsExplanation::mode() const noexcept | calls mode; returns data_-&gt;context.mode() · [reviewed contract](#b0007) |
| [B0008 · 80–80](../../../../../src/observability/statistics_explain.cpp#L80) | Callable definition: const std::optional&lt;runtime::SessionStatus&gt;& StatisticsExplanation::session() const noexcept | calls session_status; returns data_-&gt;context.session_status() · [reviewed contract](#b0008) |
| [B0009 · 81–81](../../../../../src/observability/statistics_explain.cpp#L81) | Callable definition: const runtime::ObservationSnapshot& StatisticsExplanation::observation() const noexcept | calls observation; returns *data_-&gt;context.observation() · [reviewed contract](#b0009) |
| [B0010 · 82–82](../../../../../src/observability/statistics_explain.cpp#L82) | Callable definition: const runtime::CapturedTraceRecords& StatisticsExplanation::trace() const noexcept | calls trace_records; returns data_-&gt;context.trace_records() · [reviewed contract](#b0010) |
| [B0011 · 83–83](../../../../../src/observability/statistics_explain.cpp#L83) | Callable definition: const std::optional&lt;st::CombinedCapture&gt;& StatisticsExplanation::combined() const noexcept | calls ; returns data_-&gt;combined · [reviewed contract](#b0011) |
| [B0012 · 84–84](../../../../../src/observability/statistics_explain.cpp#L84) | Callable definition: const ws::Options& StatisticsExplanation::workload_options() const noexcept | calls ; returns data_-&gt;options · [reviewed contract](#b0012) |
| [B0013 · 85–85](../../../../../src/observability/statistics_explain.cpp#L85) | Callable definition: bool StatisticsExplanation::state_requested() const noexcept | calls ; returns data_-&gt;requested · [reviewed contract](#b0013) |
| [B0014 · 86–86](../../../../../src/observability/statistics_explain.cpp#L86) | Callable definition: const std::optional&lt;StatisticsComparison&gt;& StatisticsExplanation::comparison() const noexcept | calls ; returns data_-&gt;comparison · [reviewed contract](#b0014) |
| [B0015 · 87–87](../../../../../src/observability/statistics_explain.cpp#L87) | Closes surrounding scope/type. |  · [reviewed contract](#b0015) |

## B0001

[Lines 1–8](../../../../../src/observability/statistics_explain.cpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L1-L8:sha256:f7179bcfa3066458e64699c671eb530d7dea4a28bf1298ef3e76952c511371a5
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Imports compile-time dependencies (crown/observability/statistics_explain.hpp, crown/api/error.hpp, crown/resource/ownership.hpp) and opens crown::observability scope for the declarations or definitions that follow. Embedded source note records intended usage: Retains current captured graphs; previous-report comparison stores values only. Treat that prose as guidance, not as independently verified executable behavior. |
| inputs / outputs | No runtime inputs/outputs are declared by the import/scope lines themselves. |
| invariants | The listed headers and namespace membership determine compile-time name availability; any API behavior belongs to the declarations/definitions that follow. |
| ownership | No object ownership is created by the imports or namespace tokens. |
| failure | No runtime failure path. Missing/incompatible dependencies or a violated compile-time constraint fail translation/linking. |
| cost | Compile/preprocessor work only; no new per-operation runtime overhead. |
| Design | [src/observability/statistics_explain.cpp](../../../../../src/observability/statistics_explain.cpp), [docs/code_specs/files/src/observability/statistics_explain.cpp.md](statistics_explain.cpp.md), [docs/observability.md](../../../../observability.md), [docs/statistics.md](../../../../statistics.md) |

## B0002

[Lines 9–15](../../../../../src/observability/statistics_explain.cpp#L9); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct StatisticsExplanation::Data
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Own one immutable assembled statistics report. |
| inputs / outputs | Stores current plan/mode/observation context, optional combined statistics, workload options, request flag and optional comparison. |
| invariants | Private factories assemble genuine captures; report presence/request flags do not establish exact statistics or admission. |
| ownership | Data owns current PlanExplanation/CombinedCapture handles and fixed workload/options/comparison values. Handles retain actual immutable metadata/captured graphs, including copied heavy keys; no previous-report pointer is stored. |
| failure | Account allocation/capture failures propagate; private preparation unwinds without publishing a partial report. |
| cost | Account-funded shared Data plus retained capture graphs; last release can destroy those actual graphs. |
| Design | [src/observability/statistics_explain.cpp](../../../../../src/observability/statistics_explain.cpp), [include/crown/observability/statistics_explain.hpp](../../../../../include/crown/observability/statistics_explain.hpp), [src/runtime/combined_statistics.cpp](../../../../../src/runtime/combined_statistics.cpp), [src/io/statistics_explain.cpp](../../../../../src/io/statistics_explain.cpp), [docs/observability.md](../../../../observability.md), [docs/statistics.md](../../../../statistics.md) |

```text
PlanExplanation context;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Retain actual plan/mode/observation report context. |
| inputs / outputs | Owns its context handle and retained immutable program/trace data. |
| invariants | These are descriptive report fields populated only through private assembly. |
| ownership | Data owns current PlanExplanation/CombinedCapture handles and fixed workload/options/comparison values. Handles retain actual immutable metadata/captured graphs, including copied heavy keys; no previous-report pointer is stored. |
| failure | Field declaration adds no failure boundary; real capture/account allocation failures propagate from factories. |
| cost | Fixed fields or shared handle retention here; captures pay actual traversal/clone costs at creation. |
| Design | [src/observability/statistics_explain.cpp](../../../../../src/observability/statistics_explain.cpp), [include/crown/observability/statistics_explain.hpp](../../../../../include/crown/observability/statistics_explain.hpp), [src/runtime/combined_statistics.cpp](../../../../../src/runtime/combined_statistics.cpp), [src/io/statistics_explain.cpp](../../../../../src/io/statistics_explain.cpp), [docs/observability.md](../../../../observability.md), [docs/statistics.md](../../../../statistics.md) |

```text
std::optional<st::CombinedCapture> combined;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Retain actual combined state/workload capture when available. |
| inputs / outputs | Optional shared capture owns actual copied captured keys and workload graph. |
| invariants | These are descriptive report fields populated only through private assembly. |
| ownership | Data owns current PlanExplanation/CombinedCapture handles and fixed workload/options/comparison values. Handles retain actual immutable metadata/captured graphs, including copied heavy keys; no previous-report pointer is stored. |
| failure | Field declaration adds no failure boundary; real capture/account allocation failures propagate from factories. |
| cost | Fixed fields or shared handle retention here; captures pay actual traversal/clone costs at creation. |
| Design | [src/observability/statistics_explain.cpp](../../../../../src/observability/statistics_explain.cpp), [include/crown/observability/statistics_explain.hpp](../../../../../include/crown/observability/statistics_explain.hpp), [src/runtime/combined_statistics.cpp](../../../../../src/runtime/combined_statistics.cpp), [src/io/statistics_explain.cpp](../../../../../src/io/statistics_explain.cpp), [docs/observability.md](../../../../observability.md), [docs/statistics.md](../../../../statistics.md) |

```text
ws::Options options;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Record the actual workload collection options. |
| inputs / outputs | Fixed mode/count/period/offset/detail fields copied by value. |
| invariants | These are descriptive report fields populated only through private assembly. |
| ownership | Data owns current PlanExplanation/CombinedCapture handles and fixed workload/options/comparison values. Handles retain actual immutable metadata/captured graphs, including copied heavy keys; no previous-report pointer is stored. |
| failure | Field declaration adds no failure boundary; real capture/account allocation failures propagate from factories. |
| cost | Fixed fields or shared handle retention here; captures pay actual traversal/clone costs at creation. |
| Design | [src/observability/statistics_explain.cpp](../../../../../src/observability/statistics_explain.cpp), [include/crown/observability/statistics_explain.hpp](../../../../../include/crown/observability/statistics_explain.hpp), [src/runtime/combined_statistics.cpp](../../../../../src/runtime/combined_statistics.cpp), [src/io/statistics_explain.cpp](../../../../../src/io/statistics_explain.cpp), [docs/observability.md](../../../../observability.md), [docs/statistics.md](../../../../statistics.md) |

```text
bool requested;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Remember whether explicit state statistics were requested. |
| inputs / outputs | A Boolean request marker, separate from capture completion/availability. |
| invariants | These are descriptive report fields populated only through private assembly. |
| ownership | Data owns current PlanExplanation/CombinedCapture handles and fixed workload/options/comparison values. Handles retain actual immutable metadata/captured graphs, including copied heavy keys; no previous-report pointer is stored. |
| failure | Field declaration adds no failure boundary; real capture/account allocation failures propagate from factories. |
| cost | Fixed fields or shared handle retention here; captures pay actual traversal/clone costs at creation. |
| Design | [src/observability/statistics_explain.cpp](../../../../../src/observability/statistics_explain.cpp), [include/crown/observability/statistics_explain.hpp](../../../../../include/crown/observability/statistics_explain.hpp), [src/runtime/combined_statistics.cpp](../../../../../src/runtime/combined_statistics.cpp), [src/io/statistics_explain.cpp](../../../../../src/io/statistics_explain.cpp), [docs/observability.md](../../../../observability.md), [docs/statistics.md](../../../../statistics.md) |

```text
std::optional<StatisticsComparison> comparison;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Store copied comparison facts. |
| inputs / outputs | Fixed owners/sequences/lag and optional freshness/domain enums; no old report retention. |
| invariants | These are descriptive report fields populated only through private assembly. |
| ownership | Data owns current PlanExplanation/CombinedCapture handles and fixed workload/options/comparison values. Handles retain actual immutable metadata/captured graphs, including copied heavy keys; no previous-report pointer is stored. |
| failure | Field declaration adds no failure boundary; real capture/account allocation failures propagate from factories. |
| cost | Fixed fields or shared handle retention here; captures pay actual traversal/clone costs at creation. |
| Design | [src/observability/statistics_explain.cpp](../../../../../src/observability/statistics_explain.cpp), [include/crown/observability/statistics_explain.hpp](../../../../../include/crown/observability/statistics_explain.hpp), [src/runtime/combined_statistics.cpp](../../../../../src/runtime/combined_statistics.cpp), [src/io/statistics_explain.cpp](../../../../../src/io/statistics_explain.cpp), [docs/observability.md](../../../../observability.md), [docs/statistics.md](../../../../statistics.md) |

## B0003

[Lines 16–61](../../../../../src/observability/statistics_explain.cpp#L16); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
StatisticsExplanation StatisticsExplanation::make(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Bind genuine current context and state/workload captures before publishing a report. |
| inputs / outputs | Checks observation owner/options, state stamp/sequence/plan/workload/pending/mode facts and optional current configuration; allocates Data and optionally computes copied previous/current comparison facts. |
| invariants | Private callers provide an observation-bearing actual context; live modes require actual combined capture, released mode may omit it. These fixed consistency checks are distinct from query/proof/native admission. No input advancement or reoptimization occurs. |
| ownership | Data owns current PlanExplanation/CombinedCapture handles and fixed workload/options/comparison values. Handles retain actual immutable metadata/captured graphs, including copied heavy keys; no previous-report pointer is stored. |
| failure | statistics_binding rejects inconsistent owner/configuration boundaries; account/ordinary Error allocation failures propagate. Capture preparation is discarded on failure; previously committed source/native state is unchanged. |
| cost | Fixed metadata checks including digest/options comparisons, one account-funded shared Data allocation and constant-domain comparisons. It does not rescan rows or clone captured key payload at this assembly step. |
| Design | [src/observability/statistics_explain.cpp](../../../../../src/observability/statistics_explain.cpp), [include/crown/observability/statistics_explain.hpp](../../../../../include/crown/observability/statistics_explain.hpp), [src/runtime/combined_statistics.cpp](../../../../../src/runtime/combined_statistics.cpp), [src/io/statistics_explain.cpp](../../../../../src/io/statistics_explain.cpp), [docs/observability.md](../../../../observability.md), [docs/statistics.md](../../../../statistics.md) |

```text
const auto domain=[&]
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Compare workload generation domains with owner and saturation precedence. |
| inputs / outputs | Foreign owner wins; then either saturated flag; else equal numeric counters mean same, unequal mean changed. |
| invariants | Called for configuration/reset/segment only when both reports have actual combined captures; otherwise defaults remain unavailable. It is not a timestamp/proof comparison. |
| ownership | Borrows old/now capture handles during make; stores only returned fixed enums. |
| failure | No throwing operation in this scalar lambda. |
| cost | Fixed comparisons per domain, no allocation or clock read. |
| Design | [src/observability/statistics_explain.cpp](../../../../../src/observability/statistics_explain.cpp), [include/crown/observability/statistics_explain.hpp](../../../../../include/crown/observability/statistics_explain.hpp), [src/runtime/combined_statistics.cpp](../../../../../src/runtime/combined_statistics.cpp), [src/io/statistics_explain.cpp](../../../../../src/io/statistics_explain.cpp), [docs/observability.md](../../../../observability.md), [docs/statistics.md](../../../../statistics.md) |

## B0004

[Lines 62–68](../../../../../src/observability/statistics_explain.cpp#L62); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
StatisticsExplanation StatisticsExplanation::capture(const runtime::DeltaRuntime&
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Capture current Delta-runtime report context and combined statistics. |
| inputs / outputs | Captures context under structural limits, then state/workload with explicit request or empty metadata-only request, then binds through make. |
| invariants | Uses actual runtime/options; caller follows runtime lifetime/thread/mutation protocol across these synchronous calls. Absent state request avoids default state traversal, not every metadata cost. |
| ownership | Borrows runtime/options/previous for call; resulting report owns actual current captures and copied comparison values. |
| failure | Capture/limit/account/binding errors propagate with no report returned; source input and epochs are not advanced. |
| cost | Actual context capture plus requested native scan/clone/workload costs and Data assembly; no constant-total-cost claim. |
| Design | [src/observability/statistics_explain.cpp](../../../../../src/observability/statistics_explain.cpp), [include/crown/observability/statistics_explain.hpp](../../../../../include/crown/observability/statistics_explain.hpp), [src/runtime/combined_statistics.cpp](../../../../../src/runtime/combined_statistics.cpp), [src/io/statistics_explain.cpp](../../../../../src/io/statistics_explain.cpp), [docs/observability.md](../../../../observability.md), [docs/statistics.md](../../../../statistics.md) |

## B0005

[Lines 69–77](../../../../../src/observability/statistics_explain.cpp#L69); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
StatisticsExplanation StatisticsExplanation::capture(const runtime::QuerySession&
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Capture a session-consistent actual statistics context and assemble its report. |
| inputs / outputs | Uses session.capture_statistics_context, derives released/pending/available gauge status from genuine capture, builds actual session mode/trace/cursor context and calls make. |
| invariants | Session capture enforces its creator-thread/nonreentrant and visibility boundary. Gauge status and requested flag do not imply exact requested statistics. |
| ownership | Borrows session/options/previous for call; session capture and report retain actual immutable output graphs/metadata. |
| failure | Session/capture/account/binding errors propagate; no event is consumed or acknowledged here. |
| cost | Actual session metadata/capture/export costs plus report assembly; optional state work and retained keys remain explicit. |
| Design | [src/observability/statistics_explain.cpp](../../../../../src/observability/statistics_explain.cpp), [include/crown/observability/statistics_explain.hpp](../../../../../include/crown/observability/statistics_explain.hpp), [src/runtime/combined_statistics.cpp](../../../../../src/runtime/combined_statistics.cpp), [src/io/statistics_explain.cpp](../../../../../src/io/statistics_explain.cpp), [docs/observability.md](../../../../observability.md), [docs/statistics.md](../../../../statistics.md) |

## B0006

[Lines 78–78](../../../../../src/observability/statistics_explain.cpp#L78); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
const runtime::CompiledProgram& StatisticsExplanation::plan()
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Borrow the retained actual compiled program. |
| inputs / outputs | Returns Data.context.plan() through its const accessor; state_requested returns a Boolean value. |
| invariants | Factory-only Data is valid; observation-bearing context is a private construction invariant. No getter captures or advances the producer. |
| ownership | Returned reference borrows retained Data/graphs; keep an actual report owner alive. Boolean is inline. |
| failure | Declared noexcept; no validation/catch/allocation at access. |
| cost | Constant access with no graph copy or row traversal. |
| Design | [src/observability/statistics_explain.cpp](../../../../../src/observability/statistics_explain.cpp), [include/crown/observability/statistics_explain.hpp](../../../../../include/crown/observability/statistics_explain.hpp), [src/runtime/combined_statistics.cpp](../../../../../src/runtime/combined_statistics.cpp), [src/io/statistics_explain.cpp](../../../../../src/io/statistics_explain.cpp), [docs/observability.md](../../../../observability.md), [docs/statistics.md](../../../../statistics.md) |

## B0007

[Lines 79–79](../../../../../src/observability/statistics_explain.cpp#L79); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
const ModeDescriptor& StatisticsExplanation::mode()
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Borrow the actual captured mode description. |
| inputs / outputs | Returns Data.context.mode() through its const accessor; state_requested returns a Boolean value. |
| invariants | Factory-only Data is valid; observation-bearing context is a private construction invariant. No getter captures or advances the producer. |
| ownership | Returned reference borrows retained Data/graphs; keep an actual report owner alive. Boolean is inline. |
| failure | Declared noexcept; no validation/catch/allocation at access. |
| cost | Constant access with no graph copy or row traversal. |
| Design | [src/observability/statistics_explain.cpp](../../../../../src/observability/statistics_explain.cpp), [include/crown/observability/statistics_explain.hpp](../../../../../include/crown/observability/statistics_explain.hpp), [src/runtime/combined_statistics.cpp](../../../../../src/runtime/combined_statistics.cpp), [src/io/statistics_explain.cpp](../../../../../src/io/statistics_explain.cpp), [docs/observability.md](../../../../observability.md), [docs/statistics.md](../../../../statistics.md) |

## B0008

[Lines 80–80](../../../../../src/observability/statistics_explain.cpp#L80); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
const std::optional<runtime::SessionStatus>& StatisticsExplanation::session()
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Borrow optional captured session status. |
| inputs / outputs | Returns Data.context.session_status() through its const accessor; state_requested returns a Boolean value. |
| invariants | Factory-only Data is valid; observation-bearing context is a private construction invariant. No getter captures or advances the producer. |
| ownership | Returned reference borrows retained Data/graphs; keep an actual report owner alive. Boolean is inline. |
| failure | Declared noexcept; no validation/catch/allocation at access. |
| cost | Constant access with no graph copy or row traversal. |
| Design | [src/observability/statistics_explain.cpp](../../../../../src/observability/statistics_explain.cpp), [include/crown/observability/statistics_explain.hpp](../../../../../include/crown/observability/statistics_explain.hpp), [src/runtime/combined_statistics.cpp](../../../../../src/runtime/combined_statistics.cpp), [src/io/statistics_explain.cpp](../../../../../src/io/statistics_explain.cpp), [docs/observability.md](../../../../observability.md), [docs/statistics.md](../../../../statistics.md) |

## B0009

[Lines 81–81](../../../../../src/observability/statistics_explain.cpp#L81); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
const runtime::ObservationSnapshot& StatisticsExplanation::observation()
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Borrow the actual captured observation snapshot. |
| inputs / outputs | Returns the reference obtained by dereferencing data_-&gt;context.observation(); genuine factory context guarantees presence. |
| invariants | Factory-only Data is valid; observation-bearing context is a private construction invariant. No getter captures or advances the producer. |
| ownership | Returned reference borrows retained Data/graphs; keep an actual report owner alive. Boolean is inline. |
| failure | Declared noexcept; no validation/catch/allocation at access. |
| cost | Constant access with no graph copy or row traversal. |
| Design | [src/observability/statistics_explain.cpp](../../../../../src/observability/statistics_explain.cpp), [include/crown/observability/statistics_explain.hpp](../../../../../include/crown/observability/statistics_explain.hpp), [src/runtime/combined_statistics.cpp](../../../../../src/runtime/combined_statistics.cpp), [src/io/statistics_explain.cpp](../../../../../src/io/statistics_explain.cpp), [docs/observability.md](../../../../observability.md), [docs/statistics.md](../../../../statistics.md) |

## B0010

[Lines 82–82](../../../../../src/observability/statistics_explain.cpp#L82); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
const runtime::CapturedTraceRecords& StatisticsExplanation::trace()
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Borrow retained captured trace records. |
| inputs / outputs | Returns Data.context.trace_records() through its const accessor; state_requested returns a Boolean value. |
| invariants | Factory-only Data is valid; observation-bearing context is a private construction invariant. No getter captures or advances the producer. |
| ownership | Returned reference borrows retained Data/graphs; keep an actual report owner alive. Boolean is inline. |
| failure | Declared noexcept; no validation/catch/allocation at access. |
| cost | Constant access with no graph copy or row traversal. |
| Design | [src/observability/statistics_explain.cpp](../../../../../src/observability/statistics_explain.cpp), [include/crown/observability/statistics_explain.hpp](../../../../../include/crown/observability/statistics_explain.hpp), [src/runtime/combined_statistics.cpp](../../../../../src/runtime/combined_statistics.cpp), [src/io/statistics_explain.cpp](../../../../../src/io/statistics_explain.cpp), [docs/observability.md](../../../../observability.md), [docs/statistics.md](../../../../statistics.md) |

## B0011

[Lines 83–83](../../../../../src/observability/statistics_explain.cpp#L83); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
const std::optional<st::CombinedCapture>& StatisticsExplanation::combined()
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Borrow optional actual state/workload capture. |
| inputs / outputs | Returns Data.combined through its const accessor; state_requested returns a Boolean value. |
| invariants | Factory-only Data is valid; observation-bearing context is a private construction invariant. No getter captures or advances the producer. |
| ownership | Returned reference borrows retained Data/graphs; keep an actual report owner alive. Boolean is inline. |
| failure | Declared noexcept; no validation/catch/allocation at access. |
| cost | Constant access with no graph copy or row traversal. |
| Design | [src/observability/statistics_explain.cpp](../../../../../src/observability/statistics_explain.cpp), [include/crown/observability/statistics_explain.hpp](../../../../../include/crown/observability/statistics_explain.hpp), [src/runtime/combined_statistics.cpp](../../../../../src/runtime/combined_statistics.cpp), [src/io/statistics_explain.cpp](../../../../../src/io/statistics_explain.cpp), [docs/observability.md](../../../../observability.md), [docs/statistics.md](../../../../statistics.md) |

## B0012

[Lines 84–84](../../../../../src/observability/statistics_explain.cpp#L84); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
const ws::Options& StatisticsExplanation::workload_options()
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Borrow fixed captured workload options. |
| inputs / outputs | Returns Data.options through its const accessor; state_requested returns a Boolean value. |
| invariants | Factory-only Data is valid; observation-bearing context is a private construction invariant. No getter captures or advances the producer. |
| ownership | Returned reference borrows retained Data/graphs; keep an actual report owner alive. Boolean is inline. |
| failure | Declared noexcept; no validation/catch/allocation at access. |
| cost | Constant access with no graph copy or row traversal. |
| Design | [src/observability/statistics_explain.cpp](../../../../../src/observability/statistics_explain.cpp), [include/crown/observability/statistics_explain.hpp](../../../../../include/crown/observability/statistics_explain.hpp), [src/runtime/combined_statistics.cpp](../../../../../src/runtime/combined_statistics.cpp), [src/io/statistics_explain.cpp](../../../../../src/io/statistics_explain.cpp), [docs/observability.md](../../../../observability.md), [docs/statistics.md](../../../../statistics.md) |

## B0013

[Lines 85–85](../../../../../src/observability/statistics_explain.cpp#L85); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
bool StatisticsExplanation::state_requested()
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Read the explicit state-request marker. |
| inputs / outputs | Returns Data.requested through its const accessor; state_requested returns a Boolean value. |
| invariants | Factory-only Data is valid; observation-bearing context is a private construction invariant. No getter captures or advances the producer. |
| ownership | Returned reference borrows retained Data/graphs; keep an actual report owner alive. Boolean is inline. |
| failure | Declared noexcept; no validation/catch/allocation at access. |
| cost | Constant access with no graph copy or row traversal. |
| Design | [src/observability/statistics_explain.cpp](../../../../../src/observability/statistics_explain.cpp), [include/crown/observability/statistics_explain.hpp](../../../../../include/crown/observability/statistics_explain.hpp), [src/runtime/combined_statistics.cpp](../../../../../src/runtime/combined_statistics.cpp), [src/io/statistics_explain.cpp](../../../../../src/io/statistics_explain.cpp), [docs/observability.md](../../../../observability.md), [docs/statistics.md](../../../../statistics.md) |

## B0014

[Lines 86–86](../../../../../src/observability/statistics_explain.cpp#L86); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
const std::optional<StatisticsComparison>& StatisticsExplanation::comparison()
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Borrow copied previous/current comparison facts. |
| inputs / outputs | Returns Data.comparison through its const accessor; state_requested returns a Boolean value. |
| invariants | Factory-only Data is valid; observation-bearing context is a private construction invariant. No getter captures or advances the producer. |
| ownership | Returned reference borrows retained Data/graphs; keep an actual report owner alive. Boolean is inline. |
| failure | Declared noexcept; no validation/catch/allocation at access. |
| cost | Constant access with no graph copy or row traversal. |
| Design | [src/observability/statistics_explain.cpp](../../../../../src/observability/statistics_explain.cpp), [include/crown/observability/statistics_explain.hpp](../../../../../include/crown/observability/statistics_explain.hpp), [src/runtime/combined_statistics.cpp](../../../../../src/runtime/combined_statistics.cpp), [src/io/statistics_explain.cpp](../../../../../src/io/statistics_explain.cpp), [docs/observability.md](../../../../observability.md), [docs/statistics.md](../../../../statistics.md) |

## B0015

[Lines 87–87](../../../../../src/observability/statistics_explain.cpp#L87); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L87-L87:sha256:412ca345ccf75bf9c0806bce695be8de808b79984251a7a54d202cf6101dd451
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Closes the enclosing implementation scope at this source boundary; this is a lexical delimiter, not an operation. |
| inputs / outputs | No runtime input or output. Declarations following the span leave the preceding C++ scope. |
| invariants | The delimiter ends the preceding scope's visibility/linkage region; it adds no validation, publication, ownership transfer, or runtime authority. |
| ownership | The delimiter adds no owner. If it ends a function/block with live automatic objects, their normal destructors release those objects; namespace and type-definition closes change no existing object's lifetime. |
| failure | No explicit failure translation or catch is added. If a function/block exit destroys automatic objects, exception behavior follows those destructors; namespace/type closes have no runtime failure path. |
| cost | The delimiter adds no algorithmic work. A function/block exit can run existing automatic-object destructors and cleanup; namespace/type closes have no runtime cost. |
| Design | [src/observability/statistics_explain.cpp](../../../../../src/observability/statistics_explain.cpp), [docs/code_specs/files/src/observability/statistics_explain.cpp.md](statistics_explain.cpp.md), [docs/observability.md](../../../../observability.md), [docs/statistics.md](../../../../statistics.md) |
