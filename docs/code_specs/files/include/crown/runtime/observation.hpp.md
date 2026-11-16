# `include/crown/runtime/observation.hpp` — block usage map

[Source](../../../../../../include/crown/runtime/observation.hpp) · [Source index](../../../../README.md) · [Subsystem contracts](../../../../subsystem_contracts.md) · [Reviewed primitives](../../../../primitives.md)

Collect optional counters/traces/clocks while preserving measured-zero versus unavailable fields.

Snapshot SHA-256: `5bdb64a74a25780ac5df54e793982014ffbd72525745b2a1e84ab32a748bae23`. 339 lines partitioned into 53 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [statistics](../../../../subsystem_contracts.md#statistics). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/statistics.md](../../../../../statistics.md), [docs/observability.md](../../../../../observability.md), [docs/memory_reports.md](../../../../../memory_reports.md), [docs/ranking_evaluation.md](../../../../../ranking_evaluation.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–18](../../../../../../include/crown/runtime/observation.hpp#L1) | Imports dependencies; guards repeated header inclusion; declares namespace scope. | source comment (unverified): // Optional observation never disables deterministic budget/accounting state. · [reviewed contract](#b0001) |
| [B0002 · 19–19](../../../../../../include/crown/runtime/observation.hpp#L19) | Type/record definition: enum class ObservationMode | source comment (unverified): // Optional observation never disables deterministic budget/accounting state. · [reviewed contract](#b0002) |
| [B0003 · 20–26](../../../../../../include/crown/runtime/observation.hpp#L20) | Type/record definition: struct ObservationOptions | source comment (unverified): // Retains legacy delta clocks. · [reviewed contract](#b0003) |
| [B0004 · 27–45](../../../../../../include/crown/runtime/observation.hpp#L27) | declares types or opens a type body; declares callable signatures; declares values/defaults or compile-time conditions. | source comment (unverified): // Forward declarations keep the observation header below the support/physical/ · [reviewed contract](#b0004) |
| [B0005 · 46–46](../../../../../../include/crown/runtime/observation.hpp#L46) | Callable definition: \[\[nodiscard\]\] static constexpr std::uint32_t format_version() noexcept | calls ; returns 1 · [reviewed contract](#b0005) |
| [B0006 · 47–47](../../../../../../include/crown/runtime/observation.hpp#L47) | declares callable signatures; declares values/defaults or compile-time conditions. |  · [reviewed contract](#b0006) |
| [B0007 · 48–48](../../../../../../include/crown/runtime/observation.hpp#L48) | Callable definition: \[\[nodiscard\]\] DeltaMode mode() const noexcept | calls ; returns resolved_mode_ · [reviewed contract](#b0007) |
| [B0008 · 49–49](../../../../../../include/crown/runtime/observation.hpp#L49) | Callable definition: \[\[nodiscard\]\] LiveMaintenance live_maintenance() const noexcept | calls ; returns live_ · [reviewed contract](#b0008) |
| [B0009 · 50–50](../../../../../../include/crown/runtime/observation.hpp#L50) | Callable definition: \[\[nodiscard\]\] DeltaCompletion completion() const noexcept | calls ; returns resolved_completion_ · [reviewed contract](#b0009) |
| [B0010 · 51–51](../../../../../../include/crown/runtime/observation.hpp#L51) | Callable definition: \[\[nodiscard\]\] ResultView view() const noexcept | calls ; returns view_ · [reviewed contract](#b0010) |
| [B0011 · 52–52](../../../../../../include/crown/runtime/observation.hpp#L52) | Callable definition: \[\[nodiscard\]\] std::uint64_t support_owner() const noexcept | calls ; returns owner_ · [reviewed contract](#b0011) |
| [B0012 · 53–53](../../../../../../include/crown/runtime/observation.hpp#L53) | Callable definition: \[\[nodiscard\]\] std::uint64_t generation() const noexcept | calls ; returns generation_ · [reviewed contract](#b0012) |
| [B0013 · 54–54](../../../../../../include/crown/runtime/observation.hpp#L54) | Callable definition: \[\[nodiscard\]\] bool generation_saturated() const noexcept | calls ; returns generation_saturated_ · [reviewed contract](#b0013) |
| [B0014 · 55–55](../../../../../../include/crown/runtime/observation.hpp#L55) | Callable definition: \[\[nodiscard\]\] std::size_t query_factors() const noexcept | calls ; returns factors_ · [reviewed contract](#b0014) |
| [B0015 · 56–75](../../../../../../include/crown/runtime/observation.hpp#L56) | declares types or opens a type body; declares callable signatures; declares values/defaults or compile-time conditions. | source comment (unverified): // Successful construction metadata is independent of optional event counters. · [reviewed contract](#b0015) |
| [B0016 · 76–76](../../../../../../include/crown/runtime/observation.hpp#L76) | Type/record definition: enum class InitializationRoute | source comment (unverified): // Successful construction metadata is independent of optional event counters. · [reviewed contract](#b0016) |
| [B0017 · 77–81](../../../../../../include/crown/runtime/observation.hpp#L77) | Type/record definition: struct InitializationContext | source comment (unverified): // No BuildOptions were applied by the empty constructor. · [reviewed contract](#b0017) |
| [B0018 · 82–82](../../../../../../include/crown/runtime/observation.hpp#L82) | declares types or opens a type body. |  · [reviewed contract](#b0018) |
| [B0019 · 83–87](../../../../../../include/crown/runtime/observation.hpp#L83) | Type/record definition: struct BenchmarkLabels | source comment (unverified): // These optional strings own their bytes; copying labels may allocate. · [reviewed contract](#b0019) |
| [B0020 · 88–89](../../../../../../include/crown/runtime/observation.hpp#L88) | Explanatory comments or spacing. | source comment (unverified): // Explicit caller declarations only: no callback inspection, validation of · [reviewed contract](#b0020) |
| [B0021 · 90–96](../../../../../../include/crown/runtime/observation.hpp#L90) | Type/record definition: class DeclaredBenchmarkContext | returns labels_; source comment (unverified): // Explicit caller declarations only: no callback inspection, validation of · [reviewed contract](#b0021) |
| [B0022 · 97–102](../../../../../../include/crown/runtime/observation.hpp#L97) | Type/record definition: struct OutputDisposition |  · [reviewed contract](#b0022) |
| [B0023 · 103–103](../../../../../../include/crown/runtime/observation.hpp#L103) | Type/record definition: enum class ObservationLayer |  · [reviewed contract](#b0023) |
| [B0024 · 104–104](../../../../../../include/crown/runtime/observation.hpp#L104) | Type/record definition: enum class ObservationOutcome |  · [reviewed contract](#b0024) |
| [B0025 · 105–105](../../../../../../include/crown/runtime/observation.hpp#L105) | Type/record definition: enum class MetricAvailability |  · [reviewed contract](#b0025) |
| [B0026 · 106–106](../../../../../../include/crown/runtime/observation.hpp#L106) | Type/record definition: enum class MetricKind |  · [reviewed contract](#b0026) |
| [B0027 · 107–142](../../../../../../include/crown/runtime/observation.hpp#L107) | declares types or opens a type body. |  · [reviewed contract](#b0027) |
| [B0028 · 143–168](../../../../../../include/crown/runtime/observation.hpp#L143) | declares callable signatures; declares values/defaults or compile-time conditions. |  · [reviewed contract](#b0028) |
| [B0029 · 169–177](../../../../../../include/crown/runtime/observation.hpp#L169) | Type/record definition: struct MetricDescriptor | source comment (unverified): // An inclusive work total contains lower-level work; it must not be summed · [reviewed contract](#b0029) |
| [B0030 · 178–178](../../../../../../include/crown/runtime/observation.hpp#L178) | declares callable signatures; declares values/defaults or compile-time conditions. |  · [reviewed contract](#b0030) |
| [B0031 · 179–183](../../../../../../include/crown/runtime/observation.hpp#L179) | Type/record definition: struct MetricValue |  · [reviewed contract](#b0031) |
| [B0032 · 184–205](../../../../../../include/crown/runtime/observation.hpp#L184) | Type/record definition: struct ObservationSummary | returns index&lt;values.size()?values\[index\]:unavailable; source comment (unverified): // Captured once by the outer delta begin; never relabeled by set_mode(). · [reviewed contract](#b0032) |
| [B0033 · 206–206](../../../../../../include/crown/runtime/observation.hpp#L206) | Type/record definition: enum class TraceDisposition |  · [reviewed contract](#b0033) |
| [B0034 · 207–213](../../../../../../include/crown/runtime/observation.hpp#L207) | Type/record definition: enum class TraceKind |  · [reviewed contract](#b0034) |
| [B0035 · 214–215](../../../../../../include/crown/runtime/observation.hpp#L214) | declares values/defaults or compile-time conditions. | source comment (unverified): // Numeric IDs only. No tuple pins, string pointers, borrowed rows or callbacks. · [reviewed contract](#b0035) |
| [B0036 · 216–221](../../../../../../include/crown/runtime/observation.hpp#L216) | Type/record definition: struct TraceRecord | source comment (unverified): // Numeric IDs only. No tuple pins, string pointers, borrowed rows or callbacks. · [reviewed contract](#b0036) |
| [B0037 · 222–250](../../../../../../include/crown/runtime/observation.hpp#L222) | declares types or opens a type body; declares callable signatures; declares values/defaults or compile-time conditions. | source comment (unverified): // Copies retain immutable admission contexts; they do not clone their payload. · [reviewed contract](#b0037) |
| [B0038 · 251–254](../../../../../../include/crown/runtime/observation.hpp#L251) | Type/record definition: struct ObservationTrace |  · [reviewed contract](#b0038) |
| [B0039 · 255–257](../../../../../../include/crown/runtime/observation.hpp#L255) | declares aliases; declares values/defaults or compile-time conditions. | source comment (unverified): // Retained query/report value. The ordinary ObservationTrace is an explicit · [reviewed contract](#b0039) |
| [B0040 · 258–271](../../../../../../include/crown/runtime/observation.hpp#L258) | Type/record definition: struct CapturedObservationTrace | returns *this; source comment (unverified): // Retained query/report value. The ordinary ObservationTrace is an explicit · [reviewed contract](#b0040) |
| [B0041 · 272–275](../../../../../../include/crown/runtime/observation.hpp#L272) | declares namespace scope; declares callable signatures; declares values/defaults or compile-time conditions. | source comment (unverified): // Shared monotonic/test clock without attributing a read to delta metrics. · [reviewed contract](#b0041) |
| [B0042 · 276–276](../../../../../../include/crown/runtime/observation.hpp#L276) | Type/record definition: struct ObservationTicket |  · [reviewed contract](#b0042) |
| [B0043 · 277–282](../../../../../../include/crown/runtime/observation.hpp#L277) | declares types or opens a type body; declares callable signatures; declares values/defaults or compile-time conditions. |  · [reviewed contract](#b0043) |
| [B0044 · 283–283](../../../../../../include/crown/runtime/observation.hpp#L283) | Callable definition: void bind_owner(std::uint64_t owner) noexcept | calls  · [reviewed contract](#b0044) |
| [B0045 · 284–284](../../../../../../include/crown/runtime/observation.hpp#L284) | Callable definition: void initialize(InitializationContext value) noexcept | calls  · [reviewed contract](#b0045) |
| [B0046 · 285–287](../../../../../../include/crown/runtime/observation.hpp#L285) | Callable definition: void declare_benchmark(std::shared_ptr&lt;const DeclaredBenchmarkContext&gt; value) noexcept | calls std::move · [reviewed contract](#b0046) |
| [B0047 · 288–292](../../../../../../include/crown/runtime/observation.hpp#L288) | Callable definition: void output(ObservationTicket ticket,OutputDisposition value) noexcept | calls target · [reviewed contract](#b0047) |
| [B0048 · 293–293](../../../../../../include/crown/runtime/observation.hpp#L293) | Callable definition: void configure(ObservationConfiguration value) noexcept | calls  · [reviewed contract](#b0048) |
| [B0049 · 294–296](../../../../../../include/crown/runtime/observation.hpp#L294) | Callable definition: \[\[nodiscard\]\] const std::optional&lt;ObservationConfiguration&gt;& configuration() const noexcept | calls ; returns snapshot_.current_configuration · [reviewed contract](#b0049) |
| [B0050 · 297–299](../../../../../../include/crown/runtime/observation.hpp#L297) | Callable definition: void route(std::uint64_t occurrence,std::uint64_t prefix) noexcept | calls  · [reviewed contract](#b0050) |
| [B0051 · 300–306](../../../../../../include/crown/runtime/observation.hpp#L300) | declares callable signatures; declares values/defaults or compile-time conditions. |  · [reviewed contract](#b0051) |
| [B0052 · 307–310](../../../../../../include/crown/runtime/observation.hpp#L307) | Callable definition: void note_cursor_clock_read() noexcept | calls add · [reviewed contract](#b0052) |
| [B0053 · 311–339](../../../../../../include/crown/runtime/observation.hpp#L311) | controls preprocessing; declares aliases; declares callable signatures; declares values/defaults or compile-time conditions. | source comment (unverified): // Explicit allocating diagnostic read; hooks never call this method. · [reviewed contract](#b0053) |

## B0001

[Lines 1–18](../../../../../../include/crown/runtime/observation.hpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
#pragma once
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Expose optional observation without replacing mandatory runtime budgets. |
| inputs / outputs | Includes fixed initialization options, accounted allocators and standard owning/borrowed value types; declares runtime observation names. |
| invariants | Observation off suppresses optional collectors only. Runtime work/memory limits remain in their owners. Forward delta enums break the include cycle. |
| ownership | Headers introduce no live owner; actual State admission and explicit trace exports allocate later. |
| failure | Compile-time dependency/declaration boundary; no runtime catch or recovery path. |
| cost | No runtime action at inclusion; instantiated owning members have their own costs below. |
| Design | [include/crown/runtime/observation.hpp](../../../../../../include/crown/runtime/observation.hpp), [src/runtime/observation.cpp](../../../../../../src/runtime/observation.cpp), [docs/observability.md](../../../../../observability.md), [docs/code_review.md](../../../../../code_review.md) |

## B0002

[Lines 19–19](../../../../../../include/crown/runtime/observation.hpp#L19); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
enum class ObservationMode { off, counters, timed, trace };
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Select optional observation policy. |
| inputs / outputs | off/counters/timed/trace tags control State creation, timing availability and fixed trace selection. |
| invariants | timed is the default for legacy delta timing; C01 workload::Mode remains independent. |
| ownership | The caller owns all inline scalar/enum/optional/fixed-array members; this record alone retains no backing storage or runtime. |
| failure | This value declaration performs no validation or failure translation. Admission/consumer checks run separately before facts are accepted. |
| cost | Constant-size tag; no runtime allocation, work scan or clock. Invalid casts are not automatically checked by this declaration. |
| Design | [include/crown/runtime/observation.hpp](../../../../../../include/crown/runtime/observation.hpp), [src/runtime/observation.cpp](../../../../../../src/runtime/observation.cpp), [docs/observability.md](../../../../../observability.md), [docs/code_review.md](../../../../../code_review.md) |

## B0003

[Lines 20–26](../../../../../../include/crown/runtime/observation.hpp#L20); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct ObservationOptions {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Carry observation admission and deterministic trace sampling options. |
| inputs / outputs | Defaults: timed, capacity 256, sequence period 1/offset 0 and trace timings enabled; equality compares all five settings. |
| invariants | create rejects invalid mode/zero period/offset&gt;=period even when off. Trace sampling uses physical sequence, not C01 attempt ordinal. A full admitted buffer drops records without growing. |
| ownership | The caller owns all inline scalar/enum/optional/fixed-array members; this record alone retains no backing storage or runtime. |
| failure | This value declaration performs no validation or failure translation. Admission/consumer checks run separately before facts are accepted. |
| cost | Fixed-size value construction/copy/comparison; no dynamic allocation, clocks, scans or retained heap owner. |
| Design | [include/crown/runtime/observation.hpp](../../../../../../include/crown/runtime/observation.hpp), [src/runtime/observation.cpp](../../../../../../src/runtime/observation.cpp), [docs/observability.md](../../../../../observability.md), [docs/code_review.md](../../../../../code_review.md) |

```text
bool operator==(const ObservationOptions&) const = default;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Compare all observation policy and sampling options. |
| inputs / outputs | Default equality compares mode, trace capacity, period, offset and trace_timings. |
| invariants | Equal policies do not imply equal attempt/sequence identity, sampled trace contents or runtime configuration. |
| ownership | Only the named inline values are read/copied/mutated; no input backing is retained. State receivers keep their already admitted metadata/account unchanged. |
| failure | No throwing operation or exception translation. Guards, when present, have exactly the behavior described above. |
| cost | Fixed scalar comparison; no allocation, scan or clock. |
| Design | [include/crown/runtime/observation.hpp](../../../../../../include/crown/runtime/observation.hpp), [src/runtime/observation.cpp](../../../../../../src/runtime/observation.cpp), [docs/observability.md](../../../../../observability.md), [docs/code_review.md](../../../../../code_review.md) |

## B0004

[Lines 27–45](../../../../../../include/crown/runtime/observation.hpp#L27); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
enum class DeltaMode;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Define the immutable requested/resolved delta configuration carrier and delta forwards. |
| inputs / outputs | Opaque enum/DeltaOptions declarations precede ObservationConfiguration; only DeltaRuntime can initially construct/capture its private fields. |
| invariants | Exact options/resolved mode are separate from process-local capped owner/generation diagnostics. This class does not mint a planner proof, durable epoch or runtime owner. |
| ownership | All fields are scalar/enum/optional scalar/fixed ObservationOptions; copies own inline facts, never a runtime, rows or heap allocation. |
| failure | No runtime validation here. Private capture copies existing admitted options; no allocating fallback is hidden. |
| cost | Fixed-size copy and later accessor reads; no clock, scan or allocation. |
| Design | [include/crown/runtime/observation.hpp](../../../../../../include/crown/runtime/observation.hpp), [src/runtime/observation.cpp](../../../../../../src/runtime/observation.cpp), [docs/observability.md](../../../../../observability.md), [docs/code_review.md](../../../../../code_review.md), [include/crown/runtime/delta.hpp](../../../../../../include/crown/runtime/delta.hpp) |

```text
class ObservationConfiguration {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Store a fixed immutable copy of actual delta configuration. |
| inputs / outputs | DeltaRuntime alone captures requested options, resolved mode/completion, process-local owner/generation and query factors; public accessors read the stored facts. |
| invariants | Exact requested settings remain available when generation saturates. This type records configuration, never durable acceptance, runtime ownership or planner proof. |
| ownership | Only scalar/enum/optional-scalar/fixed ObservationOptions members; it retains no shared context, string/vector storage, rows or runtime. |
| failure | Private capture and public copies/getters are noexcept; admission validation belongs to DeltaRuntime before capture. |
| cost | Fixed field construction/copy/read, no allocation, scans or clock. |
| Design | [include/crown/runtime/observation.hpp](../../../../../../include/crown/runtime/observation.hpp), [src/runtime/observation.cpp](../../../../../../src/runtime/observation.cpp), [docs/observability.md](../../../../../observability.md), [docs/code_review.md](../../../../../code_review.md), [include/crown/runtime/delta.hpp](../../../../../../include/crown/runtime/delta.hpp) |

```text
ObservationConfiguration(const ObservationConfiguration&) noexcept = default;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Copy exact ObservationConfiguration facts by copy construction. |
| inputs / outputs | A previously captured configuration yields the same requested and resolved fields; assignment replaces the destination. |
| invariants | No runtime lookup refreshes these values; saturated generations remain capped diagnostics. |
| ownership | Fixed inline values only; no pointer or allocation retained. |
| failure | Declared noexcept; no allocating or throwing member. |
| cost | Fixed-size scalar/optional copies; no heap, scans or clocks. |
| Design | [include/crown/runtime/observation.hpp](../../../../../../include/crown/runtime/observation.hpp), [src/runtime/observation.cpp](../../../../../../src/runtime/observation.cpp), [docs/observability.md](../../../../../observability.md), [docs/code_review.md](../../../../../code_review.md) |

```text
ObservationConfiguration& operator=(const ObservationConfiguration&) noexcept = default;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Copy exact ObservationConfiguration facts by copy assignment. |
| inputs / outputs | A previously captured configuration yields the same requested and resolved fields; assignment replaces the destination. |
| invariants | No runtime lookup refreshes these values; saturated generations remain capped diagnostics. |
| ownership | Fixed inline values only; no pointer or allocation retained. |
| failure | Declared noexcept; no allocating or throwing member. |
| cost | Fixed-size scalar/optional copies; no heap, scans or clocks. |
| Design | [include/crown/runtime/observation.hpp](../../../../../../include/crown/runtime/observation.hpp), [src/runtime/observation.cpp](../../../../../../src/runtime/observation.cpp), [docs/observability.md](../../../../../observability.md), [docs/code_review.md](../../../../../code_review.md) |

## B0005

[Lines 46–46](../../../../../../include/crown/runtime/observation.hpp#L46); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
[[nodiscard]] static constexpr std::uint32_t format_version() noexcept { return 1; }
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Identify the observation configuration representation. |
| inputs / outputs | Returns version 1. |
| invariants | This version is an engineering format marker, not evidence validation. |
| ownership | No owner retained; returns a scalar. |
| failure | For the stated live/readable object this noexcept accessor cannot fail. Borrowed references/views do not extend backing lifetime. |
| cost | O(1) member lookup/view construction; no allocation or clock. |
| Design | [include/crown/runtime/observation.hpp](../../../../../../include/crown/runtime/observation.hpp), [src/runtime/observation.cpp](../../../../../../src/runtime/observation.cpp), [docs/observability.md](../../../../../observability.md), [docs/code_review.md](../../../../../code_review.md) |

## B0006

[Lines 47–47](../../../../../../include/crown/runtime/observation.hpp#L47); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
[[nodiscard]] DeltaOptions requested_options() const noexcept;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Reconstruct the exact requested DeltaOptions from the captured inline fields. |
| inputs / outputs | A captured configuration returns requested mode/completion, limits, observation settings, order, transition and spool options; does not substitute resolved mode. |
| invariants | All currently represented DeltaOptions fields round-trip; source cpp asserts trivial copyability. |
| ownership | Returns an independent fixed options value; keeps no runtime or borrowed view. |
| failure | noexcept; uses only scalar/optional assignment. |
| cost | Fixed-size construction/copy, no allocation or clock. |
| Design | [include/crown/runtime/observation.hpp](../../../../../../include/crown/runtime/observation.hpp), [src/runtime/observation.cpp](../../../../../../src/runtime/observation.cpp), [docs/observability.md](../../../../../observability.md), [docs/code_review.md](../../../../../code_review.md), [include/crown/runtime/delta.hpp](../../../../../../include/crown/runtime/delta.hpp) |

## B0007

[Lines 48–48](../../../../../../include/crown/runtime/observation.hpp#L48); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
[[nodiscard]] DeltaMode mode() const noexcept { return resolved_mode_; }
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Read the captured resolved mode. |
| inputs / outputs | Returns resolved_mode_ by value. |
| invariants | Returns the actual resolved mode, distinct from requested_options().mode. |
| ownership | The returned scalar is independent; the configuration owns no heap payload. |
| failure | For the stated live/readable object this noexcept accessor cannot fail. Borrowed references/views do not extend backing lifetime. |
| cost | O(1) member lookup/view construction; no allocation or clock. |
| Design | [include/crown/runtime/observation.hpp](../../../../../../include/crown/runtime/observation.hpp), [src/runtime/observation.cpp](../../../../../../src/runtime/observation.cpp), [docs/observability.md](../../../../../observability.md), [docs/code_review.md](../../../../../code_review.md) |

## B0008

[Lines 49–49](../../../../../../include/crown/runtime/observation.hpp#L49); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
[[nodiscard]] LiveMaintenance live_maintenance() const noexcept { return live_; }
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Read the captured live maintenance policy. |
| inputs / outputs | Returns live_ by value. |
| invariants | Captured requested live-maintenance policy remains an attempt-independent fixed fact. |
| ownership | The returned scalar is independent; the configuration owns no heap payload. |
| failure | For the stated live/readable object this noexcept accessor cannot fail. Borrowed references/views do not extend backing lifetime. |
| cost | O(1) member lookup/view construction; no allocation or clock. |
| Design | [include/crown/runtime/observation.hpp](../../../../../../include/crown/runtime/observation.hpp), [src/runtime/observation.cpp](../../../../../../src/runtime/observation.cpp), [docs/observability.md](../../../../../observability.md), [docs/code_review.md](../../../../../code_review.md) |

## B0009

[Lines 50–50](../../../../../../include/crown/runtime/observation.hpp#L50); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
[[nodiscard]] DeltaCompletion completion() const noexcept { return resolved_completion_; }
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Read the captured resolved completion. |
| inputs / outputs | Returns resolved_completion_ by value. |
| invariants | Resolution differs from the requested completion kept by requested_options(). |
| ownership | The returned scalar is independent; the configuration owns no heap payload. |
| failure | For the stated live/readable object this noexcept accessor cannot fail. Borrowed references/views do not extend backing lifetime. |
| cost | O(1) member lookup/view construction; no allocation or clock. |
| Design | [include/crown/runtime/observation.hpp](../../../../../../include/crown/runtime/observation.hpp), [src/runtime/observation.cpp](../../../../../../src/runtime/observation.cpp), [docs/observability.md](../../../../../observability.md), [docs/code_review.md](../../../../../code_review.md) |

## B0010

[Lines 51–51](../../../../../../include/crown/runtime/observation.hpp#L51); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
[[nodiscard]] ResultView view() const noexcept { return view_; }
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Read the captured result view. |
| inputs / outputs | Returns view_ by value. |
| invariants | The selected SQL/core view is metadata, not a result enumeration. |
| ownership | The returned scalar is independent; the configuration owns no heap payload. |
| failure | For the stated live/readable object this noexcept accessor cannot fail. Borrowed references/views do not extend backing lifetime. |
| cost | O(1) member lookup/view construction; no allocation or clock. |
| Design | [include/crown/runtime/observation.hpp](../../../../../../include/crown/runtime/observation.hpp), [src/runtime/observation.cpp](../../../../../../src/runtime/observation.cpp), [docs/observability.md](../../../../../observability.md), [docs/code_review.md](../../../../../code_review.md) |

## B0011

[Lines 52–52](../../../../../../include/crown/runtime/observation.hpp#L52); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
[[nodiscard]] std::uint64_t support_owner() const noexcept { return owner_; }
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Read the captured support owner diagnostic. |
| inputs / outputs | Returns owner_ by value. |
| invariants | Process-local owner label alone cannot authorize imported evidence or durable state. |
| ownership | The returned scalar is independent; the configuration owns no heap payload. |
| failure | For the stated live/readable object this noexcept accessor cannot fail. Borrowed references/views do not extend backing lifetime. |
| cost | O(1) member lookup/view construction; no allocation or clock. |
| Design | [include/crown/runtime/observation.hpp](../../../../../../include/crown/runtime/observation.hpp), [src/runtime/observation.cpp](../../../../../../src/runtime/observation.cpp), [docs/observability.md](../../../../../observability.md), [docs/code_review.md](../../../../../code_review.md) |

## B0012

[Lines 53–53](../../../../../../include/crown/runtime/observation.hpp#L53); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
[[nodiscard]] std::uint64_t generation() const noexcept { return generation_; }
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Read the captured configuration generation diagnostic. |
| inputs / outputs | Returns generation_ by value. |
| invariants | After saturation the value is capped; compare exact options as well. |
| ownership | The returned scalar is independent; the configuration owns no heap payload. |
| failure | For the stated live/readable object this noexcept accessor cannot fail. Borrowed references/views do not extend backing lifetime. |
| cost | O(1) member lookup/view construction; no allocation or clock. |
| Design | [include/crown/runtime/observation.hpp](../../../../../../include/crown/runtime/observation.hpp), [src/runtime/observation.cpp](../../../../../../src/runtime/observation.cpp), [docs/observability.md](../../../../../observability.md), [docs/code_review.md](../../../../../code_review.md) |

## B0013

[Lines 54–54](../../../../../../include/crown/runtime/observation.hpp#L54); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
[[nodiscard]] bool generation_saturated() const noexcept { return generation_saturated_; }
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Read the captured generation saturation flag. |
| inputs / outputs | Returns generation_saturated_ by value. |
| invariants | True means generation no longer distinguishes every subsequent semantic configuration. |
| ownership | The returned scalar is independent; the configuration owns no heap payload. |
| failure | For the stated live/readable object this noexcept accessor cannot fail. Borrowed references/views do not extend backing lifetime. |
| cost | O(1) member lookup/view construction; no allocation or clock. |
| Design | [include/crown/runtime/observation.hpp](../../../../../../include/crown/runtime/observation.hpp), [src/runtime/observation.cpp](../../../../../../src/runtime/observation.cpp), [docs/observability.md](../../../../../observability.md), [docs/code_review.md](../../../../../code_review.md) |

## B0014

[Lines 55–55](../../../../../../include/crown/runtime/observation.hpp#L55); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
[[nodiscard]] std::size_t query_factors() const noexcept { return factors_; }
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Read the captured query factor count. |
| inputs / outputs | Returns factors_ by value. |
| invariants | Returns captured factor metadata, not measured result cardinality. |
| ownership | The returned scalar is independent; the configuration owns no heap payload. |
| failure | For the stated live/readable object this noexcept accessor cannot fail. Borrowed references/views do not extend backing lifetime. |
| cost | O(1) member lookup/view construction; no allocation or clock. |
| Design | [include/crown/runtime/observation.hpp](../../../../../../include/crown/runtime/observation.hpp), [src/runtime/observation.cpp](../../../../../../src/runtime/observation.cpp), [docs/observability.md](../../../../../observability.md), [docs/code_review.md](../../../../../code_review.md) |

## B0015

[Lines 56–75](../../../../../../include/crown/runtime/observation.hpp#L56); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
friend class DeltaRuntime;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Restrict configuration construction and retain the complete inline option copy. |
| inputs / outputs | DeltaRuntime friendship, private default/capture and owner/generation/options fields implement admission-time capture. |
| invariants | Requested and resolved mode/completion are distinct; support/physical/delta/cursor/view limits and observation/spool settings are all retained. |
| ownership | Fixed-size inline members; no mutable runtime pointer, shared graph or borrowed text. |
| failure | Private capture is noexcept. Changes adding allocating options require rechecking source trivial-copy and snapshot nothrow assertions. |
| cost | Capture is O(number of fixed fields); no runtime scans/allocations/clocks. |
| Design | [include/crown/runtime/observation.hpp](../../../../../../include/crown/runtime/observation.hpp), [src/runtime/observation.cpp](../../../../../../src/runtime/observation.cpp), [docs/observability.md](../../../../../observability.md), [docs/code_review.md](../../../../../code_review.md), [include/crown/runtime/delta.hpp](../../../../../../include/crown/runtime/delta.hpp) |

```text
ObservationConfiguration() noexcept = default;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Initialize a private zero-valued configuration before capture fills it. |
| inputs / outputs | Only DeltaRuntime/capture can use the private default constructor. |
| invariants | The private default is not a public admitted configuration factory. |
| ownership | All inline default values are owned by the object. |
| failure | noexcept, no allocation. |
| cost | Constant fixed-member initialization. |
| Design | [include/crown/runtime/observation.hpp](../../../../../../include/crown/runtime/observation.hpp), [src/runtime/observation.cpp](../../../../../../src/runtime/observation.cpp), [docs/observability.md](../../../../../observability.md), [docs/code_review.md](../../../../../code_review.md) |

```text
[[nodiscard]] static ObservationConfiguration capture(const DeltaOptions&,
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Capture exact requested DeltaOptions and actual resolved runtime configuration. |
| inputs / outputs | Options plus resolved mode/completion, owner, generation, saturation flag and factor count return a fully populated configuration. |
| invariants | The supplied labels remain process-local diagnostics; capture does not inspect or retain runtime state. |
| ownership | Copies only fixed scalar/optional settings into the result. |
| failure | noexcept; no rollback or exception handler needed. |
| cost | Fixed-field copy; no allocation, scans or clock. |
| Design | [include/crown/runtime/observation.hpp](../../../../../../include/crown/runtime/observation.hpp), [src/runtime/observation.cpp](../../../../../../src/runtime/observation.cpp), [docs/observability.md](../../../../../observability.md), [docs/code_review.md](../../../../../code_review.md), [include/crown/runtime/delta.hpp](../../../../../../include/crown/runtime/delta.hpp) |

## B0016

[Lines 76–76](../../../../../../include/crown/runtime/observation.hpp#L76); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
enum class InitializationRoute { empty_constructor, initialized_database, rebuilt_snapshot };
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Name successful runtime initialization routes. |
| inputs / outputs | empty_constructor/initialized_database/rebuilt_snapshot describe how admission succeeded. |
| invariants | A route is metadata; it neither replays inputs nor proves construction complexity. |
| ownership | The caller owns all inline scalar/enum/optional/fixed-array members; this record alone retains no backing storage or runtime. |
| failure | This value declaration performs no validation or failure translation. Admission/consumer checks run separately before facts are accepted. |
| cost | Constant-size tag; no runtime allocation, work scan or clock. Invalid casts are not automatically checked by this declaration. |
| Design | [include/crown/runtime/observation.hpp](../../../../../../include/crown/runtime/observation.hpp), [src/runtime/observation.cpp](../../../../../../src/runtime/observation.cpp), [docs/observability.md](../../../../../observability.md), [docs/code_review.md](../../../../../code_review.md) |

## B0017

[Lines 77–81](../../../../../../include/crown/runtime/observation.hpp#L77); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct InitializationContext {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Carry successful initialization route and applied BuildOptions. |
| inputs / outputs | route plus optional applied_build; empty constructor has no applied BuildOptions. |
| invariants | BuildOptions currently contains a fixed method tag and optional work cap. Metadata records settings, not actual BuildMetrics or mandatory budget consumption. |
| ownership | The caller owns all inline scalar/enum/optional/fixed-array members; this record alone retains no backing storage or runtime. |
| failure | This value declaration performs no validation or failure translation. Admission/consumer checks run separately before facts are accepted. |
| cost | Fixed-size value construction/copy/comparison; no dynamic allocation, clocks, scans or retained heap owner. |
| Design | [include/crown/runtime/observation.hpp](../../../../../../include/crown/runtime/observation.hpp), [src/runtime/observation.cpp](../../../../../../src/runtime/observation.cpp), [docs/observability.md](../../../../../observability.md), [docs/code_review.md](../../../../../code_review.md) |

## B0018

[Lines 82–82](../../../../../../include/crown/runtime/observation.hpp#L82); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct SessionRunContext;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Forward declare owning session admission metadata for snapshot handles. |
| inputs / outputs | SessionRunContext is defined by session.hpp; observation uses only shared_ptr&lt;const SessionRunContext&gt;. |
| invariants | The incomplete declaration does not make session metadata inline or allocation-free to construct. |
| ownership | A shared pointer retains the actual immutable session context when populated; no session runtime pointer is retained by this declaration. |
| failure | No runtime operation at declaration. |
| cost | No definition-time work. Copying a later shared handle is fixed refcount work; last release can destroy owned context payload. |
| Design | [include/crown/runtime/observation.hpp](../../../../../../include/crown/runtime/observation.hpp), [src/runtime/observation.cpp](../../../../../../src/runtime/observation.cpp), [docs/observability.md](../../../../../observability.md), [docs/code_review.md](../../../../../code_review.md), [include/crown/runtime/session.hpp](../../../../../../include/crown/runtime/session.hpp) |

## B0019

[Lines 83–87](../../../../../../include/crown/runtime/observation.hpp#L83); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct BenchmarkLabels {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Own caller-supplied benchmark labels. |
| inputs / outputs | Four optional std::string values: run, input_adapter, output_codec and sink. |
| invariants | These are explicit unvalidated declarations; equal strings do not establish codec behavior, durability, measured cost or proof authority. |
| ownership | Owns each present string. Constructing/copying labels may allocate ordinary heap; moving usually transfers string storage. |
| failure | String construction/copy can throw before the new value is complete; no handler is specified here. |
| cost | O(total label bytes) copies; release destroys at most four optional strings and deallocates their buffers without an explicit byte scan. Small-string behavior is implementation-dependent. |
| Design | [include/crown/runtime/observation.hpp](../../../../../../include/crown/runtime/observation.hpp), [src/runtime/observation.cpp](../../../../../../src/runtime/observation.cpp), [docs/observability.md](../../../../../observability.md), [docs/code_review.md](../../../../../code_review.md) |

## B0020

[Lines 88–89](../../../../../../include/crown/runtime/observation.hpp#L88); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L88-L89:sha256:2af343712f31447687659a6640ad2795ff0444587ba4271a43d345b198984a11
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Usage note immediately before \`class DeclaredBenchmarkContext\`: Explicit caller declarations only: no callback inspection, validation of claims, durability, completeness, measured cost, or proof authority. |
| inputs / outputs | This comment introduces no parameter, field or return value. It documents the adjacent construct beginning at include/crown/runtime/observation.hpp:L90; use that declaration for the actual input/output shape. |
| invariants | The source note states: Explicit caller declarations only: no callback inspection, validation of claims, durability, completeness, measured cost, or proof authority. It is prose guidance; the adjacent implementation is the place to check enforcement. |
| ownership | The note states no ownership relation and retains no value. The adjacent declaration or function controls the actual owner and borrowed-view lifetime. |
| failure | This comment adds no branch or handler. Any failure behavior remains in the adjacent callable implementation and its callers. |
| cost | The note states a local cost boundary: Explicit caller declarations only: no callback inspection, validation of claims, durability, completeness, measured cost, or proof authority. Treat it as usage guidance; actual work follows the implementation and input. |
| Design | [docs/observability.md](../../../../../observability.md), [docs/statistics.md](../../../../../statistics.md), [docs/code_specs/subsystem_contracts.md](../../../../subsystem_contracts.md) |

## B0021

[Lines 90–96](../../../../../../include/crown/runtime/observation.hpp#L90); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
class DeclaredBenchmarkContext {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Own immutable benchmark labels without inspecting callback behavior. |
| inputs / outputs | Constructor receives BenchmarkLabels by value, moves it into a const member; labels() exposes a const borrow. |
| invariants | No validation of caller claims, completeness, measured cost or durability follows from this metadata type. |
| ownership | Owns its strings, often retained through shared_ptr&lt;const DeclaredBenchmarkContext&gt;. A copy of the context itself copies const strings; a shared-handle copy does not. |
| failure | Argument/context copies can allocate and throw; moving the nonconst argument into labels is ordinary string move. No catch rewrites failures. |
| cost | Owning copies cost O(label bytes); shared retention is refcount work. Last release destroys four optional strings and deallocates their buffers, with no explicit byte scan. |
| Design | [include/crown/runtime/observation.hpp](../../../../../../include/crown/runtime/observation.hpp), [src/runtime/observation.cpp](../../../../../../src/runtime/observation.cpp), [docs/observability.md](../../../../../observability.md), [docs/code_review.md](../../../../../code_review.md) |

```text
explicit DeclaredBenchmarkContext(BenchmarkLabels labels):labels_(std::move(labels)) {}
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Adopt a caller benchmark-label value as immutable metadata. |
| inputs / outputs | Pass BenchmarkLabels by value, then move into labels_; lvalue arguments first copy their strings. |
| invariants | Labels are retained exactly, with no normalization or behavioral assertion. |
| ownership | Owns the moved string payload; no callback or runtime retained. |
| failure | By-value argument copies can throw; no special exception translation. |
| cost | Lvalue input O(label bytes) allocation/copy; rvalue input transfers strings where supported, plus fixed field moves. |
| Design | [include/crown/runtime/observation.hpp](../../../../../../include/crown/runtime/observation.hpp), [src/runtime/observation.cpp](../../../../../../src/runtime/observation.cpp), [docs/observability.md](../../../../../observability.md), [docs/code_review.md](../../../../../code_review.md) |

```text
[[nodiscard]] const BenchmarkLabels& labels() const noexcept { return labels_; }
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Borrow immutable benchmark labels. |
| inputs / outputs | Returns labels_ by const reference. |
| invariants | Reading labels does not validate their truth. |
| ownership | Caller must retain this context or a shared handle to it for the reference lifetime. |
| failure | For the stated live/readable object this noexcept accessor cannot fail. Borrowed references/views do not extend backing lifetime. |
| cost | O(1) member lookup/view construction; no allocation or clock. |
| Design | [include/crown/runtime/observation.hpp](../../../../../../include/crown/runtime/observation.hpp), [src/runtime/observation.cpp](../../../../../../src/runtime/observation.cpp), [docs/observability.md](../../../../../observability.md), [docs/code_review.md](../../../../../code_review.md) |

## B0022

[Lines 97–102](../../../../../../include/crown/runtime/observation.hpp#L97); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct OutputDisposition {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Record observed/requested delta output disposition flags. |
| inputs / outputs | Fixed booleans describe drain/retention, prepare/publish/release, transfer/serialization/sink and unread discard. |
| invariants | Flags record the native owner path and requested options; published/sink_invoked are not durable acknowledgment or delivery guarantees. |
| ownership | The caller owns all inline scalar/enum/optional/fixed-array members; this record alone retains no backing storage or runtime. |
| failure | This value declaration performs no validation or failure translation. Admission/consumer checks run separately before facts are accepted. |
| cost | Fixed-size value construction/copy/comparison; no dynamic allocation, clocks, scans or retained heap owner. |
| Design | [include/crown/runtime/observation.hpp](../../../../../../include/crown/runtime/observation.hpp), [src/runtime/observation.cpp](../../../../../../src/runtime/observation.cpp), [docs/observability.md](../../../../../observability.md), [docs/code_review.md](../../../../../code_review.md) |

## B0023

[Lines 103–103](../../../../../../include/crown/runtime/observation.hpp#L103); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
enum class ObservationLayer { support, physical, delta };
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Identify the observation layer. |
| inputs / outputs | support/physical/delta tags select registry fields and outer-attempt ownership. |
| invariants | Nested layers share the same active outer attempt. |
| ownership | The caller owns all inline scalar/enum/optional/fixed-array members; this record alone retains no backing storage or runtime. |
| failure | This value declaration performs no validation or failure translation. Admission/consumer checks run separately before facts are accepted. |
| cost | Constant-size tag; no runtime allocation, work scan or clock. Invalid casts are not automatically checked by this declaration. |
| Design | [include/crown/runtime/observation.hpp](../../../../../../include/crown/runtime/observation.hpp), [src/runtime/observation.cpp](../../../../../../src/runtime/observation.cpp), [docs/observability.md](../../../../../observability.md), [docs/code_review.md](../../../../../code_review.md) |

## B0024

[Lines 104–104](../../../../../../include/crown/runtime/observation.hpp#L104); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
enum class ObservationOutcome { pending, committed, aborted };
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Identify diagnostic attempt outcome. |
| inputs / outputs | pending/committed/aborted describes an admitted attempt. |
| invariants | Aborted metric values are attempted work, not committed changes. |
| ownership | The caller owns all inline scalar/enum/optional/fixed-array members; this record alone retains no backing storage or runtime. |
| failure | This value declaration performs no validation or failure translation. Admission/consumer checks run separately before facts are accepted. |
| cost | Constant-size tag; no runtime allocation, work scan or clock. Invalid casts are not automatically checked by this declaration. |
| Design | [include/crown/runtime/observation.hpp](../../../../../../include/crown/runtime/observation.hpp), [src/runtime/observation.cpp](../../../../../../src/runtime/observation.cpp), [docs/observability.md](../../../../../observability.md), [docs/code_review.md](../../../../../code_review.md) |

## B0025

[Lines 105–105](../../../../../../include/crown/runtime/observation.hpp#L105); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
enum class MetricAvailability { unavailable, disabled, available };
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Qualify a metric value. |
| inputs / outputs | unavailable/disabled/available separates absent scope from timing disabled by policy. |
| invariants | A raw zero is meaningful only together with availability and saturation. |
| ownership | The caller owns all inline scalar/enum/optional/fixed-array members; this record alone retains no backing storage or runtime. |
| failure | This value declaration performs no validation or failure translation. Admission/consumer checks run separately before facts are accepted. |
| cost | Constant-size tag; no runtime allocation, work scan or clock. Invalid casts are not automatically checked by this declaration. |
| Design | [include/crown/runtime/observation.hpp](../../../../../../include/crown/runtime/observation.hpp), [src/runtime/observation.cpp](../../../../../../src/runtime/observation.cpp), [docs/observability.md](../../../../../observability.md), [docs/code_review.md](../../../../../code_review.md) |

## B0026

[Lines 106–106](../../../../../../include/crown/runtime/observation.hpp#L106); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
enum class MetricKind { counter, high_water, timing };
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Classify metric accounting. |
| inputs / outputs | counter/high_water/timing tags describe how callers should interpret a slot. |
| invariants | set assigns; it does not automatically maximize a high-water slot. Callers compute high-water values. |
| ownership | The caller owns all inline scalar/enum/optional/fixed-array members; this record alone retains no backing storage or runtime. |
| failure | This value declaration performs no validation or failure translation. Admission/consumer checks run separately before facts are accepted. |
| cost | Constant-size tag; no runtime allocation, work scan or clock. Invalid casts are not automatically checked by this declaration. |
| Design | [include/crown/runtime/observation.hpp](../../../../../../include/crown/runtime/observation.hpp), [src/runtime/observation.cpp](../../../../../../src/runtime/observation.cpp), [docs/observability.md](../../../../../observability.md), [docs/code_review.md](../../../../../code_review.md) |

## B0027

[Lines 107–142](../../../../../../include/crown/runtime/observation.hpp#L107); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
enum class MetricId {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Enumerate support/physical/early-delta metric slots in registry order. |
| inputs / outputs | Dense MetricId values index ObservationSummary::values and the immutable registry; this region covers support_work through delta_replay_preparation_work. |
| invariants | Internal hot hooks require valid MetricId values; they index directly. Public Summary::metric performs a bounds check. Inclusive work must not be added again to its lower-layer terms. |
| ownership | The caller owns all inline scalar/enum/optional/fixed-array members; this record alone retains no backing storage or runtime. |
| failure | This value declaration performs no validation or failure translation. Admission/consumer checks run separately before facts are accepted. |
| cost | Fixed-size value construction/copy/comparison; no dynamic allocation, clocks, scans or retained heap owner. |
| Design | [include/crown/runtime/observation.hpp](../../../../../../include/crown/runtime/observation.hpp), [src/runtime/observation.cpp](../../../../../../src/runtime/observation.cpp), [docs/observability.md](../../../../../observability.md), [docs/code_review.md](../../../../../code_review.md) |

## B0028

[Lines 143–168](../../../../../../include/crown/runtime/observation.hpp#L143); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
delta_replay_first_work,
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Complete delta/output/timing/cursor metric IDs and fixed slot count. |
| inputs / outputs | Remaining replay/output/serialization/sink/timing IDs end in count; observation_metric_count converts that sentinel to array size. |
| invariants | Registry order/count matches all IDs. nested_cursor_clock_reads overlaps per-cursor clock reads; it is not an additional independent timing population. |
| ownership | The caller owns all inline scalar/enum/optional/fixed-array members; this record alone retains no backing storage or runtime. |
| failure | This value declaration performs no validation or failure translation. Admission/consumer checks run separately before facts are accepted. |
| cost | Fixed-size value construction/copy/comparison; no dynamic allocation, clocks, scans or retained heap owner. |
| Design | [include/crown/runtime/observation.hpp](../../../../../../include/crown/runtime/observation.hpp), [src/runtime/observation.cpp](../../../../../../src/runtime/observation.cpp), [docs/observability.md](../../../../../observability.md), [docs/code_review.md](../../../../../code_review.md) |

## B0029

[Lines 169–177](../../../../../../include/crown/runtime/observation.hpp#L169); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct MetricDescriptor {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Describe one static metric and its accounting scope. |
| inputs / outputs | MetricId, borrowed name/unit/accounting/scope/includes text, layer and kind define one registry row. |
| invariants | Inclusive and phase-subset fields overlap totals; labels document units but do not measure or prove cost. |
| ownership | string_view members borrow text; the built-in registry points to static literal storage. Arbitrary caller-created descriptors do not retain their text. |
| failure | Descriptor reads cannot allocate; external dangling text remains a caller lifetime error. |
| cost | Fixed-size record/copy; no text copy, allocation, clock or scan. |
| Design | [include/crown/runtime/observation.hpp](../../../../../../include/crown/runtime/observation.hpp), [src/runtime/observation.cpp](../../../../../../src/runtime/observation.cpp), [docs/observability.md](../../../../../observability.md), [docs/code_review.md](../../../../../code_review.md) |

## B0030

[Lines 178–178](../../../../../../include/crown/runtime/observation.hpp#L178); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
[[nodiscard]] std::span<const MetricDescriptor> observation_registry() noexcept;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Borrow the immutable built-in metric registry. |
| inputs / outputs | Returns a span over the static constexpr registry array. |
| invariants | One descriptor per MetricId in matching order; callers use scope/includes to avoid double-counting. |
| ownership | Span and descriptor text refer to static storage for process lifetime; no new owner/refcount. |
| failure | For the stated live/readable object this noexcept accessor cannot fail. Borrowed references/views do not extend backing lifetime. |
| cost | O(1) member lookup/view construction; no allocation or clock. |
| Design | [include/crown/runtime/observation.hpp](../../../../../../include/crown/runtime/observation.hpp), [src/runtime/observation.cpp](../../../../../../src/runtime/observation.cpp), [docs/observability.md](../../../../../observability.md), [docs/code_review.md](../../../../../code_review.md) |

## B0031

[Lines 179–183](../../../../../../include/crown/runtime/observation.hpp#L179); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct MetricValue {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Store a single available/unavailable/capped diagnostic number. |
| inputs / outputs | value defaults 0, availability unavailable and saturated false. |
| invariants | Saturated values are lower bounds; exact UINT64_MAX addition need not mark saturation until overflow, while timing set(MAX) uses the sentinel. Consumers inspect all flags. |
| ownership | The caller owns all inline scalar/enum/optional/fixed-array members; this record alone retains no backing storage or runtime. |
| failure | This value declaration performs no validation or failure translation. Admission/consumer checks run separately before facts are accepted. |
| cost | Fixed-size value construction/copy/comparison; no dynamic allocation, clocks, scans or retained heap owner. |
| Design | [include/crown/runtime/observation.hpp](../../../../../../include/crown/runtime/observation.hpp), [src/runtime/observation.cpp](../../../../../../src/runtime/observation.cpp), [docs/observability.md](../../../../../observability.md), [docs/code_review.md](../../../../../code_review.md) |

## B0032

[Lines 184–205](../../../../../../include/crown/runtime/observation.hpp#L184); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct ObservationSummary {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Own one detached diagnostic attempt summary. |
| inputs / outputs | Fixed configuration/initialization/output metadata, shared immutable benchmark metadata, attempt/sequence/layer/outcome and all metric slots. |
| invariants | Outer delta begin binds configuration/benchmark once. Lower-only attempts have no delta configuration. Aborted values remain attempted work. |
| ownership | Fixed arrays/options plus a shared benchmark handle; no runtime rows or pointer. Copying retains the actual context, not cloned strings; final release can destroy that metadata. |
| failure | Declared copy/move operations are noexcept. No heap allocation is required by copying this record; last-owner destruction may release existing heap payload. |
| cost | O(observation_metric_count) fixed slot copy plus shared refcount; no query-table scan or clock. Destruction cost includes last retained benchmark owner. |
| Design | [include/crown/runtime/observation.hpp](../../../../../../include/crown/runtime/observation.hpp), [src/runtime/observation.cpp](../../../../../../src/runtime/observation.cpp), [docs/observability.md](../../../../../observability.md), [docs/code_review.md](../../../../../code_review.md) |

```text
ObservationSummary() noexcept = default;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Provide nothrow ObservationSummary default construction. |
| inputs / outputs | Creates/replaces inline fields and its shared benchmark context handle using default member semantics. |
| invariants | Copy preserves binding; move transfers shared ownership and leaves the source valid for ordinary destruction/assignment, without promising a populated benchmark handle. |
| ownership | Fixed metric array plus shared_ptr&lt;const DeclaredBenchmarkContext&gt;; copies do not clone labels. Assignment can release an old last owner. |
| failure | noexcept; no throwing allocating member. |
| cost | Fixed slot work/refcount; no allocation for the copy/move itself. Old last-owner cleanup destroys the four optional label strings and deallocates any owned buffers. |
| Design | [include/crown/runtime/observation.hpp](../../../../../../include/crown/runtime/observation.hpp), [src/runtime/observation.cpp](../../../../../../src/runtime/observation.cpp), [docs/observability.md](../../../../../observability.md), [docs/code_review.md](../../../../../code_review.md) |

```text
ObservationSummary(const ObservationSummary&) noexcept = default;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Provide nothrow ObservationSummary copy construction. |
| inputs / outputs | Creates/replaces inline fields and its shared benchmark context handle using default member semantics. |
| invariants | Copy preserves binding; move transfers shared ownership and leaves the source valid for ordinary destruction/assignment, without promising a populated benchmark handle. |
| ownership | Fixed metric array plus shared_ptr&lt;const DeclaredBenchmarkContext&gt;; copies do not clone labels. Assignment can release an old last owner. |
| failure | noexcept; no throwing allocating member. |
| cost | Fixed slot work/refcount; no allocation for the copy/move itself. Old last-owner cleanup destroys the four optional label strings and deallocates any owned buffers. |
| Design | [include/crown/runtime/observation.hpp](../../../../../../include/crown/runtime/observation.hpp), [src/runtime/observation.cpp](../../../../../../src/runtime/observation.cpp), [docs/observability.md](../../../../../observability.md), [docs/code_review.md](../../../../../code_review.md) |

```text
ObservationSummary& operator=(const ObservationSummary&) noexcept = default;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Provide nothrow ObservationSummary copy assignment. |
| inputs / outputs | Creates/replaces inline fields and its shared benchmark context handle using default member semantics. |
| invariants | Copy preserves binding; move transfers shared ownership and leaves the source valid for ordinary destruction/assignment, without promising a populated benchmark handle. |
| ownership | Fixed metric array plus shared_ptr&lt;const DeclaredBenchmarkContext&gt;; copies do not clone labels. Assignment can release an old last owner. |
| failure | noexcept; no throwing allocating member. |
| cost | Fixed slot work/refcount; no allocation for the copy/move itself. Old last-owner cleanup destroys the four optional label strings and deallocates any owned buffers. |
| Design | [include/crown/runtime/observation.hpp](../../../../../../include/crown/runtime/observation.hpp), [src/runtime/observation.cpp](../../../../../../src/runtime/observation.cpp), [docs/observability.md](../../../../../observability.md), [docs/code_review.md](../../../../../code_review.md) |

```text
ObservationSummary(ObservationSummary&&) noexcept = default;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Provide nothrow ObservationSummary move construction. |
| inputs / outputs | Creates/replaces inline fields and its shared benchmark context handle using default member semantics. |
| invariants | Copy preserves binding; move transfers shared ownership and leaves the source valid for ordinary destruction/assignment, without promising a populated benchmark handle. |
| ownership | Fixed metric array plus shared_ptr&lt;const DeclaredBenchmarkContext&gt;; copies do not clone labels. Assignment can release an old last owner. |
| failure | noexcept; no throwing allocating member. |
| cost | Fixed slot work/refcount; no allocation for the copy/move itself. Old last-owner cleanup destroys the four optional label strings and deallocates any owned buffers. |
| Design | [include/crown/runtime/observation.hpp](../../../../../../include/crown/runtime/observation.hpp), [src/runtime/observation.cpp](../../../../../../src/runtime/observation.cpp), [docs/observability.md](../../../../../observability.md), [docs/code_review.md](../../../../../code_review.md) |

```text
ObservationSummary& operator=(ObservationSummary&&) noexcept = default;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Provide nothrow ObservationSummary move assignment. |
| inputs / outputs | Creates/replaces inline fields and its shared benchmark context handle using default member semantics. |
| invariants | Copy preserves binding; move transfers shared ownership and leaves the source valid for ordinary destruction/assignment, without promising a populated benchmark handle. |
| ownership | Fixed metric array plus shared_ptr&lt;const DeclaredBenchmarkContext&gt;; copies do not clone labels. Assignment can release an old last owner. |
| failure | noexcept; no throwing allocating member. |
| cost | Fixed slot work/refcount; no allocation for the copy/move itself. Old last-owner cleanup destroys the four optional label strings and deallocates any owned buffers. |
| Design | [include/crown/runtime/observation.hpp](../../../../../../include/crown/runtime/observation.hpp), [src/runtime/observation.cpp](../../../../../../src/runtime/observation.cpp), [docs/observability.md](../../../../../observability.md), [docs/code_review.md](../../../../../code_review.md) |

```text
[[nodiscard]] const MetricValue& metric(MetricId id) const noexcept {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Read a metric defensively by ID. |
| inputs / outputs | Returns values\[index\] for an in-range ID; otherwise a static default unavailable MetricValue. |
| invariants | Bad enum casts never index outside the public summary array. Internal State setters have the narrower valid-ID precondition. |
| ownership | An in-range reference borrows this summary; the fallback has static lifetime. |
| failure | For the stated live/readable object this noexcept accessor cannot fail. Borrowed references/views do not extend backing lifetime. |
| cost | O(1) checked index and fixed fallback; no allocation or clock. |
| Design | [include/crown/runtime/observation.hpp](../../../../../../include/crown/runtime/observation.hpp), [src/runtime/observation.cpp](../../../../../../src/runtime/observation.cpp), [docs/observability.md](../../../../../observability.md), [docs/code_review.md](../../../../../code_review.md) |

## B0033

[Lines 206–206](../../../../../../include/crown/runtime/observation.hpp#L206); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
enum class TraceDisposition { disabled, not_sampled, pending, committed, aborted, released };
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Identify trace lifecycle and selection. |
| inputs / outputs | disabled/not_sampled/pending/committed/aborted/released marks retained trace disposition. |
| invariants | No trace record count or disposition proves output durability or mandatory query progress. |
| ownership | The caller owns all inline scalar/enum/optional/fixed-array members; this record alone retains no backing storage or runtime. |
| failure | This value declaration performs no validation or failure translation. Admission/consumer checks run separately before facts are accepted. |
| cost | Constant-size tag; no runtime allocation, work scan or clock. Invalid casts are not automatically checked by this declaration. |
| Design | [include/crown/runtime/observation.hpp](../../../../../../include/crown/runtime/observation.hpp), [src/runtime/observation.cpp](../../../../../../src/runtime/observation.cpp), [docs/observability.md](../../../../../observability.md), [docs/code_review.md](../../../../../code_review.md) |

## B0034

[Lines 207–213](../../../../../../include/crown/runtime/observation.hpp#L207); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
enum class TraceKind {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Name native causal trace events. |
| inputs / outputs | begin/source/alias/native/child/journal/reverse/output/commit/abort/serialization/sink/acknowledgment tags identify numeric record kinds. |
| invariants | Tags are diagnostics of actual instrumented calls, not a complete unbounded execution log. |
| ownership | The caller owns all inline scalar/enum/optional/fixed-array members; this record alone retains no backing storage or runtime. |
| failure | This value declaration performs no validation or failure translation. Admission/consumer checks run separately before facts are accepted. |
| cost | Constant-size tag; no runtime allocation, work scan or clock. Invalid casts are not automatically checked by this declaration. |
| Design | [include/crown/runtime/observation.hpp](../../../../../../include/crown/runtime/observation.hpp), [src/runtime/observation.cpp](../../../../../../src/runtime/observation.cpp), [docs/observability.md](../../../../../observability.md), [docs/code_review.md](../../../../../code_review.md) |

## B0035

[Lines 214–215](../../../../../../include/crown/runtime/observation.hpp#L214); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
inline constexpr std::uint64_t observation_no_id = UINT64_MAX;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Reserve the absent numeric trace-identity sentinel. |
| inputs / outputs | observation_no_id equals UINT64_MAX for unset node/occurrence/role/tuple IDs. |
| invariants | The sentinel is not a tuple handle or capability. TraceRecord contains only numeric copies. |
| ownership | The caller owns all inline scalar/enum/optional/fixed-array members; this record alone retains no backing storage or runtime. |
| failure | This value declaration performs no validation or failure translation. Admission/consumer checks run separately before facts are accepted. |
| cost | Fixed-size value construction/copy/comparison; no dynamic allocation, clocks, scans or retained heap owner. |
| Design | [include/crown/runtime/observation.hpp](../../../../../../include/crown/runtime/observation.hpp), [src/runtime/observation.cpp](../../../../../../src/runtime/observation.cpp), [docs/observability.md](../../../../../observability.md), [docs/code_review.md](../../../../../code_review.md) |

## B0036

[Lines 216–221](../../../../../../include/crown/runtime/observation.hpp#L216); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct TraceRecord {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Store a numeric causal trace record without pinning query state. |
| inputs / outputs | kind, event/cause, node/occurrence/prefix, before/after/role/tuple scalar IDs form one event. |
| invariants | No row, string pointer, callback or pin is retained. event() substitutes configured route occurrence/prefix for sentinel/default inputs. |
| ownership | The caller owns all inline scalar/enum/optional/fixed-array members; this record alone retains no backing storage or runtime. |
| failure | This value declaration performs no validation or failure translation. Admission/consumer checks run separately before facts are accepted. |
| cost | Fixed-size value construction/copy/comparison; no dynamic allocation, clocks, scans or retained heap owner. |
| Design | [include/crown/runtime/observation.hpp](../../../../../../include/crown/runtime/observation.hpp), [src/runtime/observation.cpp](../../../../../../src/runtime/observation.cpp), [docs/observability.md](../../../../../observability.md), [docs/code_review.md](../../../../../code_review.md) |

## B0037

[Lines 222–250](../../../../../../include/crown/runtime/observation.hpp#L222); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct ObservationSnapshot {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Own a detached observation snapshot and shared immutable admission contexts. |
| inputs / outputs | Current configuration/initialization, shared benchmark/session context, options, owner/current+last summaries, lifetime counters and trace/session decorations. |
| invariants | Current configuration is distinct from attempt-bound configuration. Session committed sequence is read-only decoration, not durable acceptance; optional accounting does not disable mandatory_accounting. |
| ownership | Owns fixed arrays/optionals and shared const admission handles. It does not clone SessionRunContext input/window metadata or retain a QuerySession/runtime. |
| failure | Explicit default/copy/move operations are noexcept. Releasing the last shared context may destroy its existing accounted strings/vectors; snapshot copying itself allocates no payload. |
| cost | Fixed metric-array copy and bounded shared refcount operations. No row scan/clock; final-owner release includes actual metadata graph cleanup. |
| Design | [include/crown/runtime/observation.hpp](../../../../../../include/crown/runtime/observation.hpp), [src/runtime/observation.cpp](../../../../../../src/runtime/observation.cpp), [docs/observability.md](../../../../../observability.md), [docs/code_review.md](../../../../../code_review.md), [include/crown/runtime/session.hpp](../../../../../../include/crown/runtime/session.hpp) |

```text
ObservationSnapshot() noexcept = default;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Provide nothrow ObservationSnapshot default construction. |
| inputs / outputs | Default member semantics create/copy/replace the fixed snapshot and shared const contexts. |
| invariants | Copies preserve attempt/configuration/session decorations. Default moves may empty shared handles in the source; no copy-like-move promise applies here. |
| ownership | Copies share benchmark/session metadata. Assignments can release a prior last context; no owner graph is deep-copied. |
| failure | noexcept; fixed options/summary copies are statically asserted nothrow in observation.cpp. |
| cost | Fixed observation_metric_count work plus bounded refcounts; no allocating payload copy. Last-owner cleanup can walk owned metadata. |
| Design | [include/crown/runtime/observation.hpp](../../../../../../include/crown/runtime/observation.hpp), [src/runtime/observation.cpp](../../../../../../src/runtime/observation.cpp), [docs/observability.md](../../../../../observability.md), [docs/code_review.md](../../../../../code_review.md), [include/crown/runtime/session.hpp](../../../../../../include/crown/runtime/session.hpp) |

```text
ObservationSnapshot(const ObservationSnapshot&) noexcept = default;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Provide nothrow ObservationSnapshot copy construction. |
| inputs / outputs | Default member semantics create/copy/replace the fixed snapshot and shared const contexts. |
| invariants | Copies preserve attempt/configuration/session decorations. Default moves may empty shared handles in the source; no copy-like-move promise applies here. |
| ownership | Copies share benchmark/session metadata. Assignments can release a prior last context; no owner graph is deep-copied. |
| failure | noexcept; fixed options/summary copies are statically asserted nothrow in observation.cpp. |
| cost | Fixed observation_metric_count work plus bounded refcounts; no allocating payload copy. Last-owner cleanup can walk owned metadata. |
| Design | [include/crown/runtime/observation.hpp](../../../../../../include/crown/runtime/observation.hpp), [src/runtime/observation.cpp](../../../../../../src/runtime/observation.cpp), [docs/observability.md](../../../../../observability.md), [docs/code_review.md](../../../../../code_review.md), [include/crown/runtime/session.hpp](../../../../../../include/crown/runtime/session.hpp) |

```text
ObservationSnapshot& operator=(const ObservationSnapshot&) noexcept = default;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Provide nothrow ObservationSnapshot copy assignment. |
| inputs / outputs | Default member semantics create/copy/replace the fixed snapshot and shared const contexts. |
| invariants | Copies preserve attempt/configuration/session decorations. Default moves may empty shared handles in the source; no copy-like-move promise applies here. |
| ownership | Copies share benchmark/session metadata. Assignments can release a prior last context; no owner graph is deep-copied. |
| failure | noexcept; fixed options/summary copies are statically asserted nothrow in observation.cpp. |
| cost | Fixed observation_metric_count work plus bounded refcounts; no allocating payload copy. Last-owner cleanup can walk owned metadata. |
| Design | [include/crown/runtime/observation.hpp](../../../../../../include/crown/runtime/observation.hpp), [src/runtime/observation.cpp](../../../../../../src/runtime/observation.cpp), [docs/observability.md](../../../../../observability.md), [docs/code_review.md](../../../../../code_review.md), [include/crown/runtime/session.hpp](../../../../../../include/crown/runtime/session.hpp) |

```text
ObservationSnapshot(ObservationSnapshot&&) noexcept = default;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Provide nothrow ObservationSnapshot move construction. |
| inputs / outputs | Default member semantics create/copy/replace the fixed snapshot and shared const contexts. |
| invariants | Copies preserve attempt/configuration/session decorations. Default moves may empty shared handles in the source; no copy-like-move promise applies here. |
| ownership | Copies share benchmark/session metadata. Assignments can release a prior last context; no owner graph is deep-copied. |
| failure | noexcept; fixed options/summary copies are statically asserted nothrow in observation.cpp. |
| cost | Fixed observation_metric_count work plus bounded refcounts; no allocating payload copy. Last-owner cleanup can walk owned metadata. |
| Design | [include/crown/runtime/observation.hpp](../../../../../../include/crown/runtime/observation.hpp), [src/runtime/observation.cpp](../../../../../../src/runtime/observation.cpp), [docs/observability.md](../../../../../observability.md), [docs/code_review.md](../../../../../code_review.md), [include/crown/runtime/session.hpp](../../../../../../include/crown/runtime/session.hpp) |

```text
ObservationSnapshot& operator=(ObservationSnapshot&&) noexcept = default;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Provide nothrow ObservationSnapshot move assignment. |
| inputs / outputs | Default member semantics create/copy/replace the fixed snapshot and shared const contexts. |
| invariants | Copies preserve attempt/configuration/session decorations. Default moves may empty shared handles in the source; no copy-like-move promise applies here. |
| ownership | Copies share benchmark/session metadata. Assignments can release a prior last context; no owner graph is deep-copied. |
| failure | noexcept; fixed options/summary copies are statically asserted nothrow in observation.cpp. |
| cost | Fixed observation_metric_count work plus bounded refcounts; no allocating payload copy. Last-owner cleanup can walk owned metadata. |
| Design | [include/crown/runtime/observation.hpp](../../../../../../include/crown/runtime/observation.hpp), [src/runtime/observation.cpp](../../../../../../src/runtime/observation.cpp), [docs/observability.md](../../../../../observability.md), [docs/code_review.md](../../../../../code_review.md), [include/crown/runtime/session.hpp](../../../../../../include/crown/runtime/session.hpp) |

## B0038

[Lines 251–254](../../../../../../include/crown/runtime/observation.hpp#L251); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct ObservationTrace {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Export retained trace records into caller-owned standard storage. |
| inputs / outputs | ObservationTrace contains a snapshot plus ordinary std::vector&lt;TraceRecord&gt;. State::trace copies only used buffer records. |
| invariants | Explicit allocating diagnostic export; hot event hooks do not call it. Snapshot trace_records equals the exported prefix length at capture. |
| ownership | Owns ordinary vector memory outside the native query account; shared snapshot contexts remain retained. Copying deep-copies vector records. |
| failure | Vector allocation/copy can throw; State is unchanged if the export fails. |
| cost | O(R) record copy/allocation for R used records, plus fixed snapshot/refcount work. Release deallocates one trivial-record vector and any last shared context; no explicit record scan. |
| Design | [include/crown/runtime/observation.hpp](../../../../../../include/crown/runtime/observation.hpp), [src/runtime/observation.cpp](../../../../../../src/runtime/observation.cpp), [docs/observability.md](../../../../../observability.md), [docs/code_review.md](../../../../../code_review.md) |

## B0039

[Lines 255–257](../../../../../../include/crown/runtime/observation.hpp#L255); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
using CapturedTraceRecords=std::vector<TraceRecord,resource::OwnerAllocator<TraceRecord>>;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Define transferable query-funded retained trace storage. |
| inputs / outputs | CapturedTraceRecords is vector&lt;TraceRecord,OwnerAllocator&lt;TraceRecord&gt;&gt;. |
| invariants | OwnerAllocator propagation keeps storage/account/attribution together on assignment and swap. This alias alone does not allocate. |
| ownership | Nonempty records own their native payload and retain the original MemoryAccount; copies can allocate on that account. |
| failure | Allocations may fail under original account limits; no fresh grant or fallback heap is specified. |
| cost | Empty construction fixed; deep copies O(R) funded payload, moves transfer storage, destruction releases R records and its account. |
| Design | [include/crown/runtime/observation.hpp](../../../../../../include/crown/runtime/observation.hpp), [src/runtime/observation.cpp](../../../../../../src/runtime/observation.cpp), [docs/observability.md](../../../../../observability.md), [docs/code_review.md](../../../../../code_review.md), [include/crown/resource/owner_allocator.hpp](../../../../../../include/crown/resource/owner_allocator.hpp) |

## B0040

[Lines 258–271](../../../../../../include/crown/runtime/observation.hpp#L258); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct CapturedObservationTrace {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Own a native query-funded trace capture. |
| inputs / outputs | snapshot plus OwnerAllocator record vector; account constructor binds capture owner 3; copy/move operations support retained transfer. |
| invariants | Do not confuse this owning record with a cheap shared immutable report handle. Copies duplicate its records; copy assignment uses a temporary to keep paired snapshot/records consistent on failure. |
| ownership | Owns captured records on the original account and shared immutable snapshot contexts; no runtime/buffer borrow is retained. |
| failure | Copy/assign may allocate and throw. The explicit copy-assignment temporary protects the destination; moves are noexcept and transfer account/storage. |
| cost | O(R) deep copy and possible dual-vector peak; O(1) vector move plus fixed snapshot; cleanup releases vector and possibly last metadata owner. |
| Design | [include/crown/runtime/observation.hpp](../../../../../../include/crown/runtime/observation.hpp), [src/runtime/observation.cpp](../../../../../../src/runtime/observation.cpp), [docs/observability.md](../../../../../observability.md), [docs/code_review.md](../../../../../code_review.md), [include/crown/resource/owner_allocator.hpp](../../../../../../include/crown/resource/owner_allocator.hpp) |

```text
explicit CapturedObservationTrace(const resource::MemoryAccount& account)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Bind an empty captured-trace vector to an existing account. |
| inputs / outputs | Accepts MemoryAccount; initializes records with capture purpose and attribution {capture,3}. |
| invariants | No new memory allowance or diagnostic State is created. |
| ownership | The vector allocator retains the supplied account; snapshot starts empty/default. |
| failure | Empty vector construction does not allocate record payload; later record assignment can fail under this account. |
| cost | Fixed allocator/account copy; zero record allocation here. |
| Design | [include/crown/runtime/observation.hpp](../../../../../../include/crown/runtime/observation.hpp), [src/runtime/observation.cpp](../../../../../../src/runtime/observation.cpp), [docs/observability.md](../../../../../observability.md), [docs/code_review.md](../../../../../code_review.md), [include/crown/resource/owner_allocator.hpp](../../../../../../include/crown/resource/owner_allocator.hpp) |

```text
CapturedObservationTrace(const CapturedObservationTrace&)=default;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Deep-copy a native captured trace. |
| inputs / outputs | Default copy copies snapshot metadata handles and every record into source-account vector storage. |
| invariants | A copied capture remains detached from the runtime. It is not an allocation-free handle copy. |
| ownership | OwnerAllocator select_on_container_copy_construction preserves source account and attribution; snapshot contexts remain shared. |
| failure | Allocation failure destroys the partial new copy and leaves source intact. |
| cost | O(R) record allocation/copy plus fixed snapshot; source and new vector coexist. |
| Design | [include/crown/runtime/observation.hpp](../../../../../../include/crown/runtime/observation.hpp), [src/runtime/observation.cpp](../../../../../../src/runtime/observation.cpp), [docs/observability.md](../../../../../observability.md), [docs/code_review.md](../../../../../code_review.md), [include/crown/resource/owner_allocator.hpp](../../../../../../include/crown/resource/owner_allocator.hpp) |

```text
CapturedObservationTrace(CapturedObservationTrace&&) noexcept=default;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Move-construct a native captured trace. |
| inputs / outputs | Default noexcept move transfers records/account and snapshot shared handles. |
| invariants | Moved-from fields remain valid for destruction/assignment; shared metadata need not remain populated. |
| ownership | Destination adopts original vector storage/account; no clone of record or context payload. |
| failure | noexcept. |
| cost | O(1) vector ownership transfer plus fixed snapshot move; no fresh record allocation. |
| Design | [include/crown/runtime/observation.hpp](../../../../../../include/crown/runtime/observation.hpp), [src/runtime/observation.cpp](../../../../../../src/runtime/observation.cpp), [docs/observability.md](../../../../../observability.md), [docs/code_review.md](../../../../../code_review.md) |

```text
CapturedObservationTrace& operator=(const CapturedObservationTrace& other) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Assign a captured trace without mixing old records and new snapshot on failure. |
| inputs / outputs | Self-assignment returns unchanged; otherwise fully copy next(other), then move it into *this. |
| invariants | The first potentially throwing phase is private construction; publication occurs only after that complete copy. |
| ownership | Temporary deep copy retains source account/contexts; successful move releases old destination vector and metadata. |
| failure | Copy allocation failure leaves destination unchanged; subsequent move assignment is noexcept. |
| cost | O(R) new record copy plus old-vector cleanup and dual-old/new peak; no redundant catch or rollback journal. |
| Design | [include/crown/runtime/observation.hpp](../../../../../../include/crown/runtime/observation.hpp), [src/runtime/observation.cpp](../../../../../../src/runtime/observation.cpp), [docs/observability.md](../../../../../observability.md), [docs/code_review.md](../../../../../code_review.md), [include/crown/resource/owner_allocator.hpp](../../../../../../include/crown/resource/owner_allocator.hpp) |

```text
CapturedObservationTrace& operator=(CapturedObservationTrace&&) noexcept=default;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Move-assign a native captured trace. |
| inputs / outputs | Default noexcept assignment replaces snapshot and adopts source vector/account. |
| invariants | OwnerAllocator propagates; no unequal-account element-copy fallback is needed. |
| ownership | Destination releases its old records/last contexts and adopts source ownership; source remains destructible. |
| failure | noexcept. |
| cost | Fixed transfer plus actual old-vector/context release; no new record allocation. |
| Design | [include/crown/runtime/observation.hpp](../../../../../../include/crown/runtime/observation.hpp), [src/runtime/observation.cpp](../../../../../../src/runtime/observation.cpp), [docs/observability.md](../../../../../observability.md), [docs/code_review.md](../../../../../code_review.md), [include/crown/resource/owner_allocator.hpp](../../../../../../include/crown/resource/owner_allocator.hpp) |

## B0041

[Lines 272–275](../../../../../../include/crown/runtime/observation.hpp#L272); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
inline constexpr resource::MemoryAttribution observation_memory_owner{resource::MemoryOwnerKind::observation,0};
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Attribute admitted observation State/buffer allocations. |
| inputs / outputs | observation_memory_owner is {MemoryOwnerKind::observation,0}. |
| invariants | This attribution labels actual query-account allocations; a matching numeric label is not budget or evidence authority. |
| ownership | The caller owns all inline scalar/enum/optional/fixed-array members; this record alone retains no backing storage or runtime. |
| failure | This value declaration performs no validation or failure translation. Admission/consumer checks run separately before facts are accepted. |
| cost | Fixed-size value construction/copy/comparison; no dynamic allocation, clocks, scans or retained heap owner. |
| Design | [include/crown/runtime/observation.hpp](../../../../../../include/crown/runtime/observation.hpp), [src/runtime/observation.cpp](../../../../../../src/runtime/observation.cpp), [docs/observability.md](../../../../../observability.md), [docs/code_review.md](../../../../../code_review.md) |

```text
[[nodiscard]] std::uint64_t read_observation_clock() noexcept;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Read the shared observation steady/test clock without delta attribution. |
| inputs / outputs | Returns nonnegative steady-clock nanoseconds, or the exclusive test hook value when installed. |
| invariants | Does not increment delta_clock_reads. Callers gate timing policy; this function always performs the selected clock read. |
| ownership | No heap or runtime owner retained; test hook is a process-global noexcept function pointer. |
| failure | noexcept; nonpositive native tick values clamp to zero. |
| cost | One test-hook or steady-clock read and conversion; no allocation. |
| Design | [include/crown/runtime/observation.hpp](../../../../../../include/crown/runtime/observation.hpp), [src/runtime/observation.cpp](../../../../../../src/runtime/observation.cpp), [docs/observability.md](../../../../../observability.md), [docs/code_review.md](../../../../../code_review.md), [tests/unit/runtime_observation_test.cpp](../../../../../../tests/unit/runtime_observation_test.cpp) |

## B0042

[Lines 276–276](../../../../../../include/crown/runtime/observation.hpp#L276); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct ObservationTicket { std::uint64_t attempt=0; bool owns=false; };
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Carry causal attempt ownership for nested hooks. |
| inputs / outputs | attempt identifies the current summary; owns tells whether this begin created the outer attempt. |
| invariants | Only matching owns=true tickets can finish/publish an attempt. This is an internal diagnostic ticket, not a runtime transaction capability. |
| ownership | The caller owns all inline scalar/enum/optional/fixed-array members; this record alone retains no backing storage or runtime. |
| failure | This value declaration performs no validation or failure translation. Admission/consumer checks run separately before facts are accepted. |
| cost | Fixed-size value construction/copy/comparison; no dynamic allocation, clocks, scans or retained heap owner. |
| Design | [include/crown/runtime/observation.hpp](../../../../../../include/crown/runtime/observation.hpp), [src/runtime/observation.cpp](../../../../../../src/runtime/observation.cpp), [docs/observability.md](../../../../../observability.md), [docs/code_review.md](../../../../../code_review.md) |

## B0043

[Lines 277–282](../../../../../../include/crown/runtime/observation.hpp#L277); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
class ObservationState {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Declare the single-writer optional observation collector. |
| inputs / outputs | Factory/constructor and begin/finish, scalar hooks, clock access and explicit snapshot/trace exports operate on fixed metadata and an admitted vector buffer. |
| invariants | Nested layers share an outer attempt; no collector hook maintains query rows or controls mandatory work/memory budgets. |
| ownership | State/control and pre-sized trace buffer are charged to the native account at admission; captured metadata are shared immutable handles. No internal synchronization is provided. |
| failure | Admission/export may throw; admitted hot hooks are noexcept and do not grow storage. Caller serialization/valid IDs remain preconditions. |
| cost | Trace buffer admission O(capacity); begin scans the fixed registry, hot set/add/event are O(1), explicit trace copy O(R). |
| Design | [include/crown/runtime/observation.hpp](../../../../../../include/crown/runtime/observation.hpp), [src/runtime/observation.cpp](../../../../../../src/runtime/observation.cpp), [docs/observability.md](../../../../../observability.md), [docs/code_review.md](../../../../../code_review.md) |

```text
[[nodiscard]] static std::shared_ptr<ObservationState> create(const resource::MemoryAccount&,ObservationOptions);
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Validate optional observation settings and admit its funded State. |
| inputs / outputs | Existing account plus ObservationOptions return empty shared_ptr when mode off; otherwise accounted State/control. |
| invariants | Mode/period/offset validation runs before the off return. Observation off leaves deterministic runtime budgets intact. |
| ownership | State and trace buffer use supplied original account and observation/0 attribution; shared_ptr retains State. |
| failure | Invalid options throw Error before allocation; account/OOM construction failure frees unpublished state/buffer. |
| cost | Off path O(1), no state allocation; enabled admits control/state and trace resize O(capacity) only in trace mode. |
| Design | [include/crown/runtime/observation.hpp](../../../../../../include/crown/runtime/observation.hpp), [src/runtime/observation.cpp](../../../../../../src/runtime/observation.cpp), [docs/observability.md](../../../../../observability.md), [docs/code_review.md](../../../../../code_review.md) |

```text
ObservationState(const resource::MemoryAccount&,ObservationOptions);
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Initialize an admitted observation State and fixed trace buffer. |
| inputs / outputs | Account/options bind the buffer allocator, copy options and resize buffer to capacity only for trace mode. |
| invariants | Internal caller create validates options. The public-in-detail constructor is not an alternative option-validation authority. |
| ownership | Owns fixed snapshot plus original-account MemoryAllocator buffer; no runtime rows/pins. |
| failure | Constructor allocation failure unwinds private buffer/state; no runtime publication yet. |
| cost | O(trace_capacity) record initialization/allocation in trace mode; counters/timed leave buffer empty. |
| Design | [include/crown/runtime/observation.hpp](../../../../../../include/crown/runtime/observation.hpp), [src/runtime/observation.cpp](../../../../../../src/runtime/observation.cpp), [docs/observability.md](../../../../../observability.md), [docs/code_review.md](../../../../../code_review.md) |

```text
[[nodiscard]] ObservationTicket begin(ObservationLayer,std::uint64_t) noexcept;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Begin or join a causal observation attempt. |
| inputs / outputs | Layer and physical sequence return {attempt,owns}; outer begin captures initialization and delta config/benchmark and resets trace prefix/counters. |
| invariants | Sampling is sequence%period, disabled when lifetime IDs saturate. Nested begin preserves outer binding, activates only its layer metric slots. |
| ownership | Updates admitted inline state; shares benchmark handle and reuses buffer. No request rows or external borrow retained. |
| failure | noexcept after validated admission. Caller serializes begin/finish; internal layer IDs are valid. |
| cost | O(observation_metric_count) registry scan and fixed summary/reset; no allocation or clock. |
| Design | [include/crown/runtime/observation.hpp](../../../../../../include/crown/runtime/observation.hpp), [src/runtime/observation.cpp](../../../../../../src/runtime/observation.cpp), [docs/observability.md](../../../../../observability.md), [docs/code_review.md](../../../../../code_review.md) |

```text
void finish(ObservationTicket,ObservationOutcome) noexcept;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Finish only the matching outer diagnostic attempt. |
| inputs / outputs | owns/current/attempt guard returns on mismatches; otherwise records commit/abort, increments capped lifetime count, copies current to last and clears current. |
| invariants | Aborted counters remain attempted work. Nested tickets cannot prematurely publish the outer attempt; current remains the attempt-bound metadata source. |
| ownership | Inline summary/trace update reuses admitted buffer; replacing last may release a shared benchmark owner. |
| failure | noexcept; mismatched stale/nonowning tickets are intentional no-ops. |
| cost | Fixed summary-array copy/refcount and O(1) append; no allocation/clock, possible last-context cleanup. |
| Design | [include/crown/runtime/observation.hpp](../../../../../../include/crown/runtime/observation.hpp), [src/runtime/observation.cpp](../../../../../../src/runtime/observation.cpp), [docs/observability.md](../../../../../observability.md), [docs/code_review.md](../../../../../code_review.md) |

## B0044

[Lines 283–283](../../../../../../include/crown/runtime/observation.hpp#L283); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void bind_owner(std::uint64_t owner) noexcept { snapshot_.support_owner=owner; }
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Bind State to the actual support owner diagnostic. |
| inputs / outputs | Writes snapshot_.support_owner from supplied owner. |
| invariants | Caller admission provides the actual label; no external import/check or runtime ownership is performed. |
| ownership | Only the named inline values are read/copied/mutated; no input backing is retained. State receivers keep their already admitted metadata/account unchanged. |
| failure | No throwing operation or exception translation. Guards, when present, have exactly the behavior described above. |
| cost | Fixed-size value construction/copy/comparison; no dynamic allocation, clocks, scans or retained heap owner. |
| Design | [include/crown/runtime/observation.hpp](../../../../../../include/crown/runtime/observation.hpp), [src/runtime/observation.cpp](../../../../../../src/runtime/observation.cpp), [docs/observability.md](../../../../../observability.md), [docs/code_review.md](../../../../../code_review.md) |

## B0045

[Lines 284–284](../../../../../../include/crown/runtime/observation.hpp#L284); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void initialize(InitializationContext value) noexcept { snapshot_.initialization=value; }
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Record successful initialization metadata in State. |
| inputs / outputs | Copies InitializationContext into snapshot_.initialization. |
| invariants | Context uses fixed BuildOptions; it records successful admission settings, not build timing or work counters. |
| ownership | Only the named inline values are read/copied/mutated; no input backing is retained. State receivers keep their already admitted metadata/account unchanged. |
| failure | No throwing operation or exception translation. Guards, when present, have exactly the behavior described above. |
| cost | Fixed-size value construction/copy/comparison; no dynamic allocation, clocks, scans or retained heap owner. |
| Design | [include/crown/runtime/observation.hpp](../../../../../../include/crown/runtime/observation.hpp), [src/runtime/observation.cpp](../../../../../../src/runtime/observation.cpp), [docs/observability.md](../../../../../observability.md), [docs/code_review.md](../../../../../code_review.md) |

## B0046

[Lines 285–287](../../../../../../include/crown/runtime/observation.hpp#L285); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void declare_benchmark(std::shared_ptr<const DeclaredBenchmarkContext> value) noexcept {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Replace current benchmark declarations for future delta attempts. |
| inputs / outputs | Moves shared_ptr&lt;const DeclaredBenchmarkContext&gt; into snapshot_.current_declared_benchmark. |
| invariants | Already begun/last summaries keep their previously bound handle. Caller claims remain unvalidated. |
| ownership | Adopts one shared immutable context; may release a previous last label owner. |
| failure | noexcept shared pointer assignment; no label-copy failure phase. |
| cost | O(1) handle transfer; final replaced-owner destruction may release its strings. |
| Design | [include/crown/runtime/observation.hpp](../../../../../../include/crown/runtime/observation.hpp), [src/runtime/observation.cpp](../../../../../../src/runtime/observation.cpp), [docs/observability.md](../../../../../observability.md), [docs/code_review.md](../../../../../code_review.md) |

## B0047

[Lines 288–292](../../../../../../include/crown/runtime/observation.hpp#L288); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void output(ObservationTicket ticket,OutputDisposition value) noexcept {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Attach output disposition only to the same delta attempt. |
| inputs / outputs | target() chooses current else last; writes output only when owner is delta and attempt matches ticket.attempt. |
| invariants | Guard prevents a late output decoration from relabeling a different/newer attempt; ticket.owns is not required for this decoration. |
| ownership | Only the named inline values are read/copied/mutated; no input backing is retained. State receivers keep their already admitted metadata/account unchanged. |
| failure | No throwing operation or exception translation. Guards, when present, have exactly the behavior described above. |
| cost | O(1) guard/optional scalar copy; no allocation or clock. |
| Design | [include/crown/runtime/observation.hpp](../../../../../../include/crown/runtime/observation.hpp), [src/runtime/observation.cpp](../../../../../../src/runtime/observation.cpp), [docs/observability.md](../../../../../observability.md), [docs/code_review.md](../../../../../code_review.md) |

## B0048

[Lines 293–293](../../../../../../include/crown/runtime/observation.hpp#L293); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void configure(ObservationConfiguration value) noexcept { snapshot_.current_configuration=value; }
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Replace current configuration for future delta attempt binding. |
| inputs / outputs | Copies a fixed ObservationConfiguration into snapshot_.current_configuration. |
| invariants | Existing current/last attempt-bound configurations remain unchanged; caller already admitted the actual runtime setting. |
| ownership | Only the named inline values are read/copied/mutated; no input backing is retained. State receivers keep their already admitted metadata/account unchanged. |
| failure | No throwing operation or exception translation. Guards, when present, have exactly the behavior described above. |
| cost | Fixed-size value construction/copy/comparison; no dynamic allocation, clocks, scans or retained heap owner. |
| Design | [include/crown/runtime/observation.hpp](../../../../../../include/crown/runtime/observation.hpp), [src/runtime/observation.cpp](../../../../../../src/runtime/observation.cpp), [docs/observability.md](../../../../../observability.md), [docs/code_review.md](../../../../../code_review.md) |

## B0049

[Lines 294–296](../../../../../../include/crown/runtime/observation.hpp#L294); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
[[nodiscard]] const std::optional<ObservationConfiguration>& configuration() const noexcept {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Borrow the currently configured delta metadata. |
| inputs / outputs | Returns snapshot_.current_configuration by const reference. |
| invariants | The current configuration can differ from the last/current attempt configuration. |
| ownership | Reference borrows this State and is invalidated by mutation/destruction; retain/copy value as needed. |
| failure | For the stated live/readable object this noexcept accessor cannot fail. Borrowed references/views do not extend backing lifetime. |
| cost | O(1) member lookup/view construction; no allocation or clock. |
| Design | [include/crown/runtime/observation.hpp](../../../../../../include/crown/runtime/observation.hpp), [src/runtime/observation.cpp](../../../../../../src/runtime/observation.cpp), [docs/observability.md](../../../../../observability.md), [docs/code_review.md](../../../../../code_review.md) |

## B0050

[Lines 297–299](../../../../../../include/crown/runtime/observation.hpp#L297); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void route(std::uint64_t occurrence,std::uint64_t prefix) noexcept {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Set fallback numeric route context for later trace events. |
| inputs / outputs | Stores occurrence_ and prefix_. |
| invariants | event uses these only for default occurrence/prefix arguments; scalar IDs retain no input row or runtime owner. |
| ownership | Only the named inline values are read/copied/mutated; no input backing is retained. State receivers keep their already admitted metadata/account unchanged. |
| failure | No throwing operation or exception translation. Guards, when present, have exactly the behavior described above. |
| cost | Fixed-size value construction/copy/comparison; no dynamic allocation, clocks, scans or retained heap owner. |
| Design | [include/crown/runtime/observation.hpp](../../../../../../include/crown/runtime/observation.hpp), [src/runtime/observation.cpp](../../../../../../src/runtime/observation.cpp), [docs/observability.md](../../../../../observability.md), [docs/code_review.md](../../../../../code_review.md) |

## B0051

[Lines 300–306](../../../../../../include/crown/runtime/observation.hpp#L300); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void set(MetricId,std::uint64_t) noexcept;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Assign a valid metric slot when available and unsaturated. |
| inputs / outputs | Internal valid MetricId plus amount targets current else last; set writes amount, timing MAX marks sentinel saturation. |
| invariants | set does not compute a max for high_water; callers supply computed values. Unavailable/saturated slots remain unchanged. |
| ownership | Inline numeric summary mutation only. |
| failure | noexcept; internal valid enum required because direct array indexing is deliberately unchecked. |
| cost | O(1), no allocation or clock. |
| Design | [include/crown/runtime/observation.hpp](../../../../../../include/crown/runtime/observation.hpp), [src/runtime/observation.cpp](../../../../../../src/runtime/observation.cpp), [docs/observability.md](../../../../../observability.md), [docs/code_review.md](../../../../../code_review.md) |

```text
void add(MetricId,std::uint64_t=1) noexcept;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Add a capped diagnostic metric amount. |
| inputs / outputs | Internal valid MetricId and amount (default 1) increment available target current/last slot. |
| invariants | Overflow caps at UINT64_MAX and marks saturated; exact MAX can remain unsaturated until a later overflowing increment. |
| ownership | Only inline counters mutate; no runtime rows or budget grants. |
| failure | noexcept; no target/unavailable are intentional no-ops, valid ID precondition avoids out-of-range indexing. |
| cost | O(1), no allocation or clock. |
| Design | [include/crown/runtime/observation.hpp](../../../../../../include/crown/runtime/observation.hpp), [src/runtime/observation.cpp](../../../../../../src/runtime/observation.cpp), [docs/observability.md](../../../../../observability.md), [docs/code_review.md](../../../../../code_review.md) |

```text
void unavailable(MetricId) noexcept;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Mark a valid metric unavailable without erasing raw diagnostic bits. |
| inputs / outputs | Targets current else last; assigns availability unavailable. |
| invariants | Raw value/saturation can remain visible; consumers must inspect availability. |
| ownership | Mutates one inline slot. |
| failure | noexcept; internal valid-ID precondition. |
| cost | O(1), no allocation or clock. |
| Design | [include/crown/runtime/observation.hpp](../../../../../../include/crown/runtime/observation.hpp), [src/runtime/observation.cpp](../../../../../../src/runtime/observation.cpp), [docs/observability.md](../../../../../observability.md), [docs/code_review.md](../../../../../code_review.md) |

```text
void event(TraceKind,std::uint64_t event=0,std::uint64_t cause=0,
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Append one numeric causal event to admitted fixed storage. |
| inputs / outputs | Kind/IDs/counts plus optional route defaults fill next record if selected and space remains. |
| invariants | Unselected returns; full/zero-capacity increments capped dropped count and sets truncation. Does not grow buffer or affect query maintenance. |
| ownership | Writes own admitted buffer only; supplied IDs carry no row/pin/callback ownership. |
| failure | noexcept. Buffer-full is diagnostic loss, not a retry or allocating fallback. |
| cost | O(1) fixed record write/capped increment; no allocation or clock. |
| Design | [include/crown/runtime/observation.hpp](../../../../../../include/crown/runtime/observation.hpp), [src/runtime/observation.cpp](../../../../../../src/runtime/observation.cpp), [docs/observability.md](../../../../../observability.md), [docs/code_review.md](../../../../../code_review.md) |

## B0052

[Lines 307–310](../../../../../../include/crown/runtime/observation.hpp#L307); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void note_cursor_clock_read() noexcept {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Attribute cursor reads only while an outer delta attempt is active. |
| inputs / outputs | When current exists and owner is delta, add nested_cursor_clock_reads; otherwise no change. |
| invariants | This subset overlaps the cursor own clock counter. A later current-result read is outside the delta attempt. |
| ownership | Only the named inline values are read/copied/mutated; no input backing is retained. State receivers keep their already admitted metadata/account unchanged. |
| failure | No throwing operation or exception translation. Guards, when present, have exactly the behavior described above. |
| cost | O(1), no allocation or clock read; merely increments a diagnostic slot. |
| Design | [include/crown/runtime/observation.hpp](../../../../../../include/crown/runtime/observation.hpp), [src/runtime/observation.cpp](../../../../../../src/runtime/observation.cpp), [docs/observability.md](../../../../../observability.md), [docs/code_review.md](../../../../../code_review.md) |

## B0053

[Lines 311–339](../../../../../../include/crown/runtime/observation.hpp#L311); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
[[nodiscard]] bool clocks_enabled() const noexcept;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Test the collector timing policy. |
| inputs / outputs | True for timed or trace with trace_timings; false otherwise. |
| invariants | This predicate does not itself read a clock or suppress a caller that directly invokes now(). |
| ownership | Reads inline options only. |
| failure | noexcept. |
| cost | O(1), no allocation/clock. |
| Design | [include/crown/runtime/observation.hpp](../../../../../../include/crown/runtime/observation.hpp), [src/runtime/observation.cpp](../../../../../../src/runtime/observation.cpp), [docs/observability.md](../../../../../observability.md), [docs/code_review.md](../../../../../code_review.md) |

```text
[[nodiscard]] std::uint64_t now() noexcept;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Read a clock with delta diagnostic attribution. |
| inputs / outputs | Adds delta_clock_reads when its target slot is available, then always delegates read_observation_clock. |
| invariants | Callers must gate clocks_enabled; direct now calls still read time even in counters/off-like options. |
| ownership | No heap owner added. |
| failure | noexcept; valid fixed MetricId is internal. |
| cost | One constant hook plus actual clock read; no allocation. |
| Design | [include/crown/runtime/observation.hpp](../../../../../../include/crown/runtime/observation.hpp), [src/runtime/observation.cpp](../../../../../../src/runtime/observation.cpp), [docs/observability.md](../../../../../observability.md), [docs/code_review.md](../../../../../code_review.md) |

```text
[[nodiscard]] ObservationSnapshot snapshot() const noexcept;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Copy a detached observation snapshot. |
| inputs / outputs | Returns snapshot_ by value, retaining its immutable admission handles. |
| invariants | No runtime/table scan or trace-buffer record copy occurs. |
| ownership | Fixed metadata plus shared contexts; caller owns value, not a runtime handle. |
| failure | noexcept; last-owner release of replaced/destroyed snapshots may free context payload. |
| cost | Fixed array/optional copy/refcounts; no new payload allocation. |
| Design | [include/crown/runtime/observation.hpp](../../../../../../include/crown/runtime/observation.hpp), [src/runtime/observation.cpp](../../../../../../src/runtime/observation.cpp), [docs/observability.md](../../../../../observability.md), [docs/code_review.md](../../../../../code_review.md) |

```text
[[nodiscard]] ObservationTrace trace() const;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Export used trace records to ordinary caller storage. |
| inputs / outputs | Returns snapshot and \[0,trace_records) record copy. |
| invariants | Explicit allocating diagnostic; instrumentation hooks never call it. |
| ownership | Result owns std::vector on ordinary allocator; shares immutable snapshot metadata. |
| failure | Allocation failure unwinds result and leaves State unchanged. |
| cost | O(R) allocation/copy plus fixed snapshot; zero record payload when R=0. |
| Design | [include/crown/runtime/observation.hpp](../../../../../../include/crown/runtime/observation.hpp), [src/runtime/observation.cpp](../../../../../../src/runtime/observation.cpp), [docs/observability.md](../../../../../observability.md), [docs/code_review.md](../../../../../code_review.md) |

```text
[[nodiscard]] CapturedObservationTrace capture_trace() const;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Capture used trace records on the live buffer original account. |
| inputs / outputs | Returns CapturedObservationTrace constructed from buffer allocator account then copies the used prefix. |
| invariants | Receiver account is not replaced by a fresh grant; hooks do not invoke this diagnostic. |
| ownership | Native result owns capture/3 vector and shared context handles, independent of State lifetime. |
| failure | Native allocation failure destroys partial result; State unchanged. |
| cost | O(R) funded allocation/copy, with live buffer plus captured vector coexisting. |
| Design | [include/crown/runtime/observation.hpp](../../../../../../include/crown/runtime/observation.hpp), [src/runtime/observation.cpp](../../../../../../src/runtime/observation.cpp), [docs/observability.md](../../../../../observability.md), [docs/code_review.md](../../../../../code_review.md) |

```text
ObservationOptions options_;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Retain collector policy, fixed snapshot, admitted buffer and route scalars. |
| inputs / outputs | State private members include options_, snapshot_, buffer_, selected_, occurrence_/prefix_; target selects current else last. |
| invariants | Buffer size is fixed at admission. Numeric route state is reset by each outer begin. |
| ownership | The buffer MemoryAllocator keeps original account; snapshot shares immutable contexts; this graph retains no query row. |
| failure | Destructor releases buffer and contexts; it is not a hot hook. |
| cost | State inline storage plus capacity*sizeof(TraceRecord) funded allocation; final release frees buffer and any last context metadata. |
| Design | [include/crown/runtime/observation.hpp](../../../../../../include/crown/runtime/observation.hpp), [src/runtime/observation.cpp](../../../../../../src/runtime/observation.cpp), [docs/observability.md](../../../../../observability.md), [docs/code_review.md](../../../../../code_review.md) |

```text
[[nodiscard]] ObservationSummary* target() noexcept;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Select current attempt or last completed diagnostic target. |
| inputs / outputs | Returns pointer to current when engaged, otherwise last, otherwise nullptr. |
| invariants | Postattempt serialization/output counters can decorate last; no summary is fabricated. |
| ownership | Returned pointer borrows State and is only for immediate serialized mutation. |
| failure | noexcept; absence is normal. |
| cost | O(1), no allocation/clock. |
| Design | [include/crown/runtime/observation.hpp](../../../../../../include/crown/runtime/observation.hpp), [src/runtime/observation.cpp](../../../../../../src/runtime/observation.cpp), [docs/observability.md](../../../../../observability.md), [docs/code_review.md](../../../../../code_review.md) |

```text
[[nodiscard]] ObservationSnapshot observation_snapshot(const std::shared_ptr<ObservationState>&,ObservationOptions) noexcept;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Read observation snapshot with disabled-State fallback. |
| inputs / outputs | If shared State exists return its snapshot; else default snapshot with caller options. |
| invariants | Fallback does not create State or disable mandatory accounting. |
| ownership | Return owns fixed metadata; no-State result retains no context. |
| failure | noexcept. |
| cost | Fixed snapshot copy/refcounts or O(1) default; no record allocation. |
| Design | [include/crown/runtime/observation.hpp](../../../../../../include/crown/runtime/observation.hpp), [src/runtime/observation.cpp](../../../../../../src/runtime/observation.cpp), [docs/observability.md](../../../../../observability.md), [docs/code_review.md](../../../../../code_review.md) |

```text
[[nodiscard]] ObservationTrace observation_trace(const std::shared_ptr<ObservationState>&,ObservationOptions);
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Read an ordinary diagnostic trace with disabled-State fallback. |
| inputs / outputs | Existing State delegates trace(); absent State returns default snapshot/options and empty ordinary records. |
| invariants | No implicit collector admission or sample restart. |
| ownership | Result owns its exported vector; borrowed State is used only synchronously. |
| failure | Existing-State export allocation can throw; no-State fallback has no record payload. |
| cost | O(R) copy/allocation if State; otherwise fixed empty result. |
| Design | [include/crown/runtime/observation.hpp](../../../../../../include/crown/runtime/observation.hpp), [src/runtime/observation.cpp](../../../../../../src/runtime/observation.cpp), [docs/observability.md](../../../../../observability.md), [docs/code_review.md](../../../../../code_review.md) |

```text
[[nodiscard]] CapturedObservationTrace capture_observation_trace(const std::shared_ptr<ObservationState>&,
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Read a funded diagnostic trace with disabled-State fallback. |
| inputs / outputs | Existing State uses its actual buffer account; absent State constructs an empty native result with supplied account/options. |
| invariants | A caller-supplied fallback account does not rebind existing State records or budget. |
| ownership | Result allocator retains the chosen original/fallback account; no State pointer retained. |
| failure | Nonempty copy may throw; result unwinds without collector mutation. |
| cost | O(R) funded copy for live State, fixed empty allocator binding otherwise. |
| Design | [include/crown/runtime/observation.hpp](../../../../../../include/crown/runtime/observation.hpp), [src/runtime/observation.cpp](../../../../../../src/runtime/observation.cpp), [docs/observability.md](../../../../../observability.md), [docs/code_review.md](../../../../../code_review.md) |

```text
using ObservationClock = std::uint64_t (*)() noexcept;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Declare the exclusive test clock function type. |
| inputs / outputs | ObservationClock is a noexcept uint64_t-returning function pointer, present only with CROWN_RUNTIME_TESTING. |
| invariants | Test hook is process-global; exclusive test ownership is required. It is not a production callback API. |
| ownership | Pointer borrows executable function lifetime; no object capture/heap allocation. |
| failure | noexcept callback contract. |
| cost | Fixed pointer storage; hooked reads incur one indirect call. |
| Design | [include/crown/runtime/observation.hpp](../../../../../../include/crown/runtime/observation.hpp), [src/runtime/observation.cpp](../../../../../../src/runtime/observation.cpp), [docs/observability.md](../../../../../observability.md), [docs/code_review.md](../../../../../code_review.md), [tests/unit/runtime_observation_test.cpp](../../../../../../tests/unit/runtime_observation_test.cpp) |

```text
void set_observation_clock_for_testing(ObservationClock) noexcept;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Replace the global observation clock in exclusive tests. |
| inputs / outputs | Stores hook; nullptr restores real steady clock. |
| invariants | No synchronization is provided; do not overlap test ownership or use as runtime policy. |
| ownership | Stores only a function pointer; no callback context or payload ownership. |
| failure | noexcept, test-only. |
| cost | O(1) assignment; no read/allocation. |
| Design | [include/crown/runtime/observation.hpp](../../../../../../include/crown/runtime/observation.hpp), [src/runtime/observation.cpp](../../../../../../src/runtime/observation.cpp), [docs/observability.md](../../../../../observability.md), [docs/code_review.md](../../../../../code_review.md), [tests/unit/runtime_observation_test.cpp](../../../../../../tests/unit/runtime_observation_test.cpp) |

```text
void set_observation_initial_generation_for_testing(std::uint64_t) noexcept;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Set a test-only initial diagnostic-generation boundary. |
| inputs / outputs | Stores uint64 generation seed for future owner construction; zero restores normal seed. |
| invariants | Existing owner generations are unchanged; exclusive construction/test ownership only. |
| ownership | Process-global scalar, no runtime owner retained. |
| failure | noexcept test-only setter. |
| cost | O(1), no allocation/clock. |
| Design | [include/crown/runtime/observation.hpp](../../../../../../include/crown/runtime/observation.hpp), [src/runtime/observation.cpp](../../../../../../src/runtime/observation.cpp), [docs/observability.md](../../../../../observability.md), [docs/code_review.md](../../../../../code_review.md), [tests/unit/observation_mode_binding_test.cpp](../../../../../../tests/unit/observation_mode_binding_test.cpp) |

```text
[[nodiscard]] std::uint64_t observation_initial_generation_for_testing() noexcept;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Read the test-only construction generation seed. |
| inputs / outputs | Returns global initial generation override. |
| invariants | Does not inspect or mutate any existing runtime. |
| ownership | Returns independent scalar. |
| failure | noexcept; exclusive test discipline is external. |
| cost | O(1), no allocation/clock. |
| Design | [include/crown/runtime/observation.hpp](../../../../../../include/crown/runtime/observation.hpp), [src/runtime/observation.cpp](../../../../../../src/runtime/observation.cpp), [docs/observability.md](../../../../../observability.md), [docs/code_review.md](../../../../../code_review.md), [tests/unit/observation_mode_binding_test.cpp](../../../../../../tests/unit/observation_mode_binding_test.cpp) |
