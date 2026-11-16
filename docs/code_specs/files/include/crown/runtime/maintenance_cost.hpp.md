# `include/crown/runtime/maintenance_cost.hpp` — block usage map

[Source](../../../../../../include/crown/runtime/maintenance_cost.hpp) · [Source index](../../../../README.md) · [Subsystem contracts](../../../../subsystem_contracts.md) · [Reviewed primitives](../../../../primitives.md)

Capture bounded distributions, workload counters, owner memory and explain observations without mislabeling partial information as exact.

Snapshot SHA-256: `11047326fec0ddd176879a45e0eebc1bbdcb0726275ec6455f6827368b0608b7`. 190 lines partitioned into 33 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [statistics](../../../../subsystem_contracts.md#statistics). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/statistics.md](../../../../../statistics.md), [docs/observability.md](../../../../../observability.md), [docs/memory_reports.md](../../../../../memory_reports.md), [docs/ranking_evaluation.md](../../../../../ranking_evaluation.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–12](../../../../../../include/crown/runtime/maintenance_cost.hpp#L1) | Imports dependencies; guards repeated header inclusion; declares namespace scope; declares aliases; declares types or opens a type body; declares values/defaults or compile-time conditions. | source comment (unverified): // Factory arithmetic reduces nonnegative ratios and checks 64-bit intermediates. · [reviewed contract](#b0001) |
| [B0002 · 13–13](../../../../../../include/crown/runtime/maintenance_cost.hpp#L13) | Type/record definition: struct Ratio | source comment (unverified): // Factory arithmetic reduces nonnegative ratios and checks 64-bit intermediates. · [reviewed contract](#b0002) |
| [B0003 · 14–20](../../../../../../include/crown/runtime/maintenance_cost.hpp#L14) | Type/record definition: enum class Component : std::size_t |  · [reviewed contract](#b0003) |
| [B0004 · 21–26](../../../../../../include/crown/runtime/maintenance_cost.hpp#L21) | declares callable signatures; declares values/defaults or compile-time conditions. | source comment (unverified): // Caller-supplied measured calibration observations, not native query facts. · [reviewed contract](#b0004) |
| [B0005 · 27–27](../../../../../../include/crown/runtime/maintenance_cost.hpp#L27) | Type/record definition: struct CalibrationSample | source comment (unverified): // Caller-supplied measured calibration observations, not native query facts. · [reviewed contract](#b0005) |
| [B0006 · 28–28](../../../../../../include/crown/runtime/maintenance_cost.hpp#L28) | Type/record definition: enum class CalibrationOrigin |  · [reviewed contract](#b0006) |
| [B0007 · 29–30](../../../../../../include/crown/runtime/maintenance_cost.hpp#L29) | Explanatory comments or spacing. | source comment (unverified): // A whole measured phase and its observed feature vector. The fit infers a · [reviewed contract](#b0007) |
| [B0008 · 31–31](../../../../../../include/crown/runtime/maintenance_cost.hpp#L31) | Type/record definition: struct FitObservation | source comment (unverified): // A whole measured phase and its observed feature vector. The fit infers a · [reviewed contract](#b0008) |
| [B0009 · 32–38](../../../../../../include/crown/runtime/maintenance_cost.hpp#L32) | Type/record definition: struct FitOptions |  · [reviewed contract](#b0009) |
| [B0010 · 39–45](../../../../../../include/crown/runtime/maintenance_cost.hpp#L39) | Type/record definition: struct FitSummary |  · [reviewed contract](#b0010) |
| [B0011 · 46–50](../../../../../../include/crown/runtime/maintenance_cost.hpp#L46) | Type/record definition: struct FeatureCensus |  · [reviewed contract](#b0011) |
| [B0012 · 51–51](../../../../../../include/crown/runtime/maintenance_cost.hpp#L51) | Type/record definition: struct FeatureAttempt |  · [reviewed contract](#b0012) |
| [B0013 · 52–57](../../../../../../include/crown/runtime/maintenance_cost.hpp#L52) | declares values/defaults or compile-time conditions. | source comment (unverified): // Exact committed full-detail counters only. Disabled, sampled, truncated, · [reviewed contract](#b0013) |
| [B0014 · 58–58](../../../../../../include/crown/runtime/maintenance_cost.hpp#L58) | Type/record definition: struct Coefficient | source comment (unverified): // elapsed_ns is the isolated sample total, or zero for a jointly fitted rate. · [reviewed contract](#b0014) |
| [B0015 · 59–73](../../../../../../include/crown/runtime/maintenance_cost.hpp#L59) | Type/record definition: class Calibration | source comment (unverified): // Copies share immutable Data; views require a retained readable handle. · [reviewed contract](#b0015) |
| [B0016 · 74–78](../../../../../../include/crown/runtime/maintenance_cost.hpp#L74) | Type/record definition: struct CalibrationAttempt |  · [reviewed contract](#b0016) |
| [B0017 · 79–90](../../../../../../include/crown/runtime/maintenance_cost.hpp#L79) | declares values/defaults or compile-time conditions. | source comment (unverified): // Deterministic, zero-initialized, fixed-coordinate-order nonnegative fitting. · [reviewed contract](#b0017) |
| [B0018 · 91–102](../../../../../../include/crown/runtime/maintenance_cost.hpp#L91) | Type/record definition: class Profile | source comment (unverified): // Factory captures an actual quiescent owner, including its account at capture. · [reviewed contract](#b0018) |
| [B0019 · 103–103](../../../../../../include/crown/runtime/maintenance_cost.hpp#L103) | Type/record definition: struct CaptureAttempt |  · [reviewed contract](#b0019) |
| [B0020 · 104–115](../../../../../../include/crown/runtime/maintenance_cost.hpp#L104) | declares callable signatures; declares values/defaults or compile-time conditions. | source comment (unverified): // Future counts for a declared horizon, not rates measured by C01 (which has · [reviewed contract](#b0020) |
| [B0021 · 116–116](../../../../../../include/crown/runtime/maintenance_cost.hpp#L116) | Type/record definition: struct InputDemand | source comment (unverified): // Future counts for a declared horizon, not rates measured by C01 (which has · [reviewed contract](#b0021) |
| [B0022 · 117–124](../../../../../../include/crown/runtime/maintenance_cost.hpp#L117) | Type/record definition: struct OutputDemand | source comment (unverified): // Optional aggregate demand supports snapshots whose row counts vary across · [reviewed contract](#b0022) |
| [B0023 · 125–130](../../../../../../include/crown/runtime/maintenance_cost.hpp#L125) | Type/record definition: struct Request |  · [reviewed contract](#b0023) |
| [B0024 · 131–131](../../../../../../include/crown/runtime/maintenance_cost.hpp#L131) | Type/record definition: enum class Basis |  · [reviewed contract](#b0024) |
| [B0025 · 132–136](../../../../../../include/crown/runtime/maintenance_cost.hpp#L132) | Type/record definition: enum class Issue : U64 |  · [reviewed contract](#b0025) |
| [B0026 · 137–137](../../../../../../include/crown/runtime/maintenance_cost.hpp#L137) | declares aliases; declares values/defaults or compile-time conditions. |  · [reviewed contract](#b0026) |
| [B0027 · 138–138](../../../../../../include/crown/runtime/maintenance_cost.hpp#L138) | Callable definition: constexpr Issues issue(Issue x) noexcept | calls ; returns static_cast&lt;Issues&gt;(x) · [reviewed contract](#b0027) |
| [B0028 · 139–144](../../../../../../include/crown/runtime/maintenance_cost.hpp#L139) | Type/record definition: struct Confidence | source comment (unverified): // A sampled count is not a statistical confidence interval or future fact. · [reviewed contract](#b0028) |
| [B0029 · 145–151](../../../../../../include/crown/runtime/maintenance_cost.hpp#L145) | Type/record definition: struct Term |  · [reviewed contract](#b0029) |
| [B0030 · 152–168](../../../../../../include/crown/runtime/maintenance_cost.hpp#L152) | Type/record definition: struct CandidateEstimate | source comment (unverified): // The term vector owns funded payload; copying this record can allocate. · [reviewed contract](#b0030) |
| [B0031 · 169–184](../../../../../../include/crown/runtime/maintenance_cost.hpp#L169) | Type/record definition: class Result | source comment (unverified): // Handle copies share all copied demand/terms and retained model evidence. · [reviewed contract](#b0031) |
| [B0032 · 185–185](../../../../../../include/crown/runtime/maintenance_cost.hpp#L185) | Type/record definition: struct Attempt |  · [reviewed contract](#b0032) |
| [B0033 · 186–190](../../../../../../include/crown/runtime/maintenance_cost.hpp#L186) | declares callable signatures; declares values/defaults or compile-time conditions. | source comment (unverified): // Produces a decomposition (possibly explicitly unavailable) for EVERY retained · [reviewed contract](#b0033) |

## B0001

[Lines 1–12](../../../../../../include/crown/runtime/maintenance_cost.hpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
#pragma once
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Expose maintenance cost decomposition separately from minimum-height proof. |
| inputs / outputs | Includes typed runtime ranking evidence; defines planner-ranking alias, private Data/Factory forwards and U64. |
| invariants | Cost models are local engineering policy. Minimum-height proof remains checked candidate/certificate authority; no score selects/enables C05 automatically. |
| ownership | No live model/result created at inclusion; factories own payload on actual supplied accounts. |
| failure | Compile-time declaration boundary only. |
| cost | No runtime action; explicit factories/scans below carry costs. |
| Design | [include/crown/runtime/maintenance_cost.hpp](../../../../../../include/crown/runtime/maintenance_cost.hpp), [src/runtime/maintenance_cost.cpp](../../../../../../src/runtime/maintenance_cost.cpp), [docs/maintenance_cost.md](../../../../../maintenance_cost.md), [docs/ranking.md](../../../../../ranking.md), [docs/code_review.md](../../../../../code_review.md) |

## B0002

[Lines 13–13](../../../../../../include/crown/runtime/maintenance_cost.hpp#L13); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct Ratio { U64 numerator{}, denominator{1}; bool operator==(const Ratio&) const = default; };
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Represent a nonnegative rational cost quantity. |
| inputs / outputs | Public numerator default0 and denominator default1; default equality compares stored fields. |
| invariants | Factory arithmetic reduces/cross-cancels and checks 64-bit intermediates/score_bits. Arbitrary public Ratio values are not automatically reduced or denominator-validated. |
| ownership | The caller owns all inline scalar/enum/optional/fixed-array members; this record alone retains no backing storage or runtime. |
| failure | This value declaration performs no validation or failure translation. Admission/consumer checks run separately before facts are accepted. |
| cost | Fixed-size value construction/copy/comparison; no dynamic allocation, clocks, scans or retained heap owner. |
| Design | [include/crown/runtime/maintenance_cost.hpp](../../../../../../include/crown/runtime/maintenance_cost.hpp), [src/runtime/maintenance_cost.cpp](../../../../../../src/runtime/maintenance_cost.cpp), [docs/maintenance_cost.md](../../../../../maintenance_cost.md), [docs/ranking.md](../../../../../ranking.md), [docs/code_review.md](../../../../../code_review.md) |

## B0003

[Lines 14–20](../../../../../../include/crown/runtime/maintenance_cost.hpp#L14); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
enum class Component : std::size_t {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Identify independently priced observed or declared operations. |
| inputs / outputs | 22 components cover input/change/adapter/support/index/probe/annotation/output/encoding/checkpoint units, ending at count. |
| invariants | A component has its own unit. Counts from distinct operations must not be treated as independent measured timings when jointly fitted. |
| ownership | The caller owns all inline scalar/enum/optional/fixed-array members; this record alone retains no backing storage or runtime. |
| failure | This value declaration performs no validation or failure translation. Admission/consumer checks run separately before facts are accepted. |
| cost | Constant-size tag; no runtime allocation, work scan or clock. Invalid casts are not automatically checked by this declaration. |
| Design | [include/crown/runtime/maintenance_cost.hpp](../../../../../../include/crown/runtime/maintenance_cost.hpp), [src/runtime/maintenance_cost.cpp](../../../../../../src/runtime/maintenance_cost.cpp), [docs/maintenance_cost.md](../../../../../maintenance_cost.md), [docs/ranking.md](../../../../../ranking.md), [docs/code_review.md](../../../../../code_review.md) |

## B0004

[Lines 21–26](../../../../../../include/crown/runtime/maintenance_cost.hpp#L21); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
inline constexpr auto component_count = static_cast<std::size_t>(Component::count);
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Set fixed feature/coefficient dimension. |
| inputs / outputs | component_count converts Component::count to array extent. |
| invariants | The sentinel itself is not a priceable component; public component_name bounds-checks unknown casts. |
| ownership | Only the named inline values are read/copied/mutated; no input backing is retained. State receivers keep their already admitted metadata/account unchanged. |
| failure | No throwing operation or exception translation. Guards, when present, have exactly the behavior described above. |
| cost | Fixed-size value construction/copy/comparison; no dynamic allocation, clocks, scans or retained heap owner. |
| Design | [include/crown/runtime/maintenance_cost.hpp](../../../../../../include/crown/runtime/maintenance_cost.hpp), [src/runtime/maintenance_cost.cpp](../../../../../../src/runtime/maintenance_cost.cpp), [docs/maintenance_cost.md](../../../../../maintenance_cost.md), [docs/ranking.md](../../../../../ranking.md), [docs/code_review.md](../../../../../code_review.md) |

```text
std::string_view component_name(Component) noexcept;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Name a component for diagnostics. |
| inputs / outputs | Returns static literal name, or "invalid" for out-of-range enum. |
| invariants | Name is a label, not proof of an isolated measurement. |
| ownership | Returned string_view borrows static literal storage for process lifetime. |
| failure | For the stated live/readable object this noexcept accessor cannot fail. Borrowed references/views do not extend backing lifetime. |
| cost | O(1) member lookup/view construction; no allocation or clock. |
| Design | [include/crown/runtime/maintenance_cost.hpp](../../../../../../include/crown/runtime/maintenance_cost.hpp), [src/runtime/maintenance_cost.cpp](../../../../../../src/runtime/maintenance_cost.cpp), [docs/maintenance_cost.md](../../../../../maintenance_cost.md), [docs/ranking.md](../../../../../ranking.md), [docs/code_review.md](../../../../../code_review.md) |

## B0005

[Lines 27–27](../../../../../../include/crown/runtime/maintenance_cost.hpp#L27); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct CalibrationSample { Component component; U64 units{}, elapsed_ns{}; };
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Carry one caller-supplied isolated timing observation. |
| inputs / outputs | Component, positive units and positive elapsed_ns consumed by calibrate. |
| invariants | Caller is responsible for isolation and consistent backend/layout/instrumentation context; context label is retained, never behaviorally verified. |
| ownership | The caller owns all inline scalar/enum/optional/fixed-array members; this record alone retains no backing storage or runtime. |
| failure | This value declaration performs no validation or failure translation. Admission/consumer checks run separately before facts are accepted. |
| cost | Fixed-size value construction/copy/comparison; no dynamic allocation, clocks, scans or retained heap owner. |
| Design | [include/crown/runtime/maintenance_cost.hpp](../../../../../../include/crown/runtime/maintenance_cost.hpp), [src/runtime/maintenance_cost.cpp](../../../../../../src/runtime/maintenance_cost.cpp), [docs/maintenance_cost.md](../../../../../maintenance_cost.md), [docs/ranking.md](../../../../../ranking.md), [docs/code_review.md](../../../../../code_review.md) |

## B0006

[Lines 28–28](../../../../../../include/crown/runtime/maintenance_cost.hpp#L28); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
enum class CalibrationOrigin { isolated_measurement_ratios, fitted_linear_assumption };
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Identify coefficient provenance. |
| inputs / outputs | isolated_measurement_ratios versus fitted_linear_assumption. |
| invariants | Joint inferred attribution does not become independently observed cost or paper theorem. |
| ownership | The caller owns all inline scalar/enum/optional/fixed-array members; this record alone retains no backing storage or runtime. |
| failure | This value declaration performs no validation or failure translation. Admission/consumer checks run separately before facts are accepted. |
| cost | Constant-size tag; no runtime allocation, work scan or clock. Invalid casts are not automatically checked by this declaration. |
| Design | [include/crown/runtime/maintenance_cost.hpp](../../../../../../include/crown/runtime/maintenance_cost.hpp), [src/runtime/maintenance_cost.cpp](../../../../../../src/runtime/maintenance_cost.cpp), [docs/maintenance_cost.md](../../../../../maintenance_cost.md), [docs/ranking.md](../../../../../ranking.md), [docs/code_review.md](../../../../../code_review.md) |

## B0007

[Lines 29–30](../../../../../../include/crown/runtime/maintenance_cost.hpp#L29); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L29-L30:sha256:224c97fa18ed233a39f03e982326672d710dd0f27f8aa4b79468f3c03bedbbef
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Usage note immediately before \`struct FitObservation\`: A whole measured phase and its observed feature vector. The fit infers a linear attribution; it does not turn that attribution into observed facts. |
| inputs / outputs | This comment introduces no parameter, field or return value. It documents the adjacent construct beginning at include/crown/runtime/maintenance_cost.hpp:L31; use that declaration for the actual input/output shape. |
| invariants | The source note states: A whole measured phase and its observed feature vector. The fit infers a linear attribution; it does not turn that attribution into observed facts. It is prose guidance; the adjacent implementation is the place to check enforcement. |
| ownership | The note states no ownership relation and retains no value. The adjacent declaration or function controls the actual owner and borrowed-view lifetime. |
| failure | This comment adds no branch or handler. Any failure behavior remains in the adjacent callable implementation and its callers. |
| cost | The note states a local cost boundary: A whole measured phase and its observed feature vector. The fit infers a linear attribution; it does not turn that attribution into observed facts. Treat it as usage guidance; actual work follows the implementation and input. |
| Design | [docs/maintenance_cost.md](../../../../../maintenance_cost.md), [docs/workloads.md](../../../../../workloads.md), [docs/code_specs/subsystem_contracts.md](../../../../subsystem_contracts.md) |

## B0008

[Lines 31–31](../../../../../../include/crown/runtime/maintenance_cost.hpp#L31); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct FitObservation { std::array<U64,component_count> units{}; U64 elapsed_ns{}; };
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Carry one whole measured phase feature vector. |
| inputs / outputs | Fixed 22-component U64 units array and elapsed_ns. |
| invariants | fit requires each observation have some nonzero feature; elapsed_ns may be zero. Caller vectors/timings are declarations, not captured runtime authority. |
| ownership | The caller owns all inline scalar/enum/optional/fixed-array members; this record alone retains no backing storage or runtime. |
| failure | This value declaration performs no validation or failure translation. Admission/consumer checks run separately before facts are accepted. |
| cost | Fixed component_count array copy; no allocation/clock/row scan. |
| Design | [include/crown/runtime/maintenance_cost.hpp](../../../../../../include/crown/runtime/maintenance_cost.hpp), [src/runtime/maintenance_cost.cpp](../../../../../../src/runtime/maintenance_cost.cpp), [docs/maintenance_cost.md](../../../../../maintenance_cost.md), [docs/ranking.md](../../../../../ranking.md), [docs/code_review.md](../../../../../code_review.md) |

## B0009

[Lines 32–38](../../../../../../include/crown/runtime/maintenance_cost.hpp#L32); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct FitOptions {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Configure approximate deterministic nonnegative fitting. |
| inputs / outputs | Iteration/tolerance/rank settings, ridge Ratio, quantization denominator and optional workload modes. |
| invariants | fit validates positive finite tolerances, rank tolerance&lt;1, nonzero iterations/quantization/ridge denominator. Modes are compatibility metadata, not measured causality. |
| ownership | The caller owns all inline scalar/enum/optional/fixed-array members; this record alone retains no backing storage or runtime. |
| failure | This value declaration performs no validation or failure translation. Admission/consumer checks run separately before facts are accepted. |
| cost | Fixed-size value construction/copy/comparison; no dynamic allocation, clocks, scans or retained heap owner. |
| Design | [include/crown/runtime/maintenance_cost.hpp](../../../../../../include/crown/runtime/maintenance_cost.hpp), [src/runtime/maintenance_cost.cpp](../../../../../../src/runtime/maintenance_cost.cpp), [docs/maintenance_cost.md](../../../../../maintenance_cost.md), [docs/ranking.md](../../../../../ranking.md), [docs/code_review.md](../../../../../code_review.md) |

## B0010

[Lines 39–45](../../../../../../include/crown/runtime/maintenance_cost.hpp#L39); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct FitSummary {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Retain fit options, numerical rank, iterations and residual diagnostics. |
| inputs / outputs | Observations/features/rank/iterations/elapsed total, underdetermined flag and floating RMSE/max absolute error. |
| invariants | Rank uses tolerance on unregularized normalized Gram matrix. Residuals describe retained training observations after quantization; no statistical confidence/future accuracy guarantee. |
| ownership | The caller owns all inline scalar/enum/optional/fixed-array members; this record alone retains no backing storage or runtime. |
| failure | This value declaration performs no validation or failure translation. Admission/consumer checks run separately before facts are accepted. |
| cost | Fixed-size value construction/copy/comparison; no dynamic allocation, clocks, scans or retained heap owner. |
| Design | [include/crown/runtime/maintenance_cost.hpp](../../../../../../include/crown/runtime/maintenance_cost.hpp), [src/runtime/maintenance_cost.cpp](../../../../../../src/runtime/maintenance_cost.cpp), [docs/maintenance_cost.md](../../../../../maintenance_cost.md), [docs/ranking.md](../../../../../ranking.md), [docs/code_review.md](../../../../../code_review.md) |

## B0011

[Lines 46–50](../../../../../../include/crown/runtime/maintenance_cost.hpp#L46); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct FeatureCensus {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Carry exact committed observed feature counts and binding metadata. |
| inputs / outputs | Fixed component-count units, workload Stamp and ModeFacts. |
| invariants | Only features() admits exact nonprivate physical-scope full detail with unsaturated interval stamps. Public mutation of this value alone does not mint captured owner evidence. |
| ownership | The caller owns all inline scalar/enum/optional/fixed-array members; this record alone retains no backing storage or runtime. |
| failure | This value declaration performs no validation or failure translation. Admission/consumer checks run separately before facts are accepted. |
| cost | Fixed 22-feature array and metadata copy; no allocation. |
| Design | [include/crown/runtime/maintenance_cost.hpp](../../../../../../include/crown/runtime/maintenance_cost.hpp), [src/runtime/maintenance_cost.cpp](../../../../../../src/runtime/maintenance_cost.cpp), [docs/maintenance_cost.md](../../../../../maintenance_cost.md), [docs/ranking.md](../../../../../ranking.md), [docs/code_review.md](../../../../../code_review.md) |

## B0012

[Lines 51–51](../../../../../../include/crown/runtime/maintenance_cost.hpp#L51); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct FeatureAttempt { pr::Stop stop=pr::Stop::internal_error; std::optional<FeatureCensus> census; pr::Usage usage; };
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Return feature census admission outcome. |
| inputs / outputs | Stop defaults internal_error; optional fixed FeatureCensus and processing Usage. |
| invariants | Only complete with engaged census is successful; failed attempt retains stop/usage, not partial feature authority. |
| ownership | The caller owns all inline scalar/enum/optional/fixed-array members; this record alone retains no backing storage or runtime. |
| failure | This value declaration performs no validation or failure translation. Admission/consumer checks run separately before facts are accepted. |
| cost | Fixed-size value construction/copy/comparison; no dynamic allocation, clocks, scans or retained heap owner. |
| Design | [include/crown/runtime/maintenance_cost.hpp](../../../../../../include/crown/runtime/maintenance_cost.hpp), [src/runtime/maintenance_cost.cpp](../../../../../../src/runtime/maintenance_cost.cpp), [docs/maintenance_cost.md](../../../../../maintenance_cost.md), [docs/ranking.md](../../../../../ranking.md), [docs/code_review.md](../../../../../code_review.md) |

## B0013

[Lines 52–57](../../../../../../include/crown/runtime/maintenance_cost.hpp#L52); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
[[nodiscard]] FeatureAttempt features(const workload::Snapshot&,pr::Limits = {}) noexcept;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Derive timing feature counts only from exact committed full-detail workload data. |
| inputs / outputs | Snapshot and finite ranking Limits return FeatureAttempt; reject pending/off/sampled/incomplete/saturated/logical-scope intervals and saturated generation stamps. |
| invariants | Maps actual descriptor/cell counts to operation components with checked sums. It does not measure elapsed_ns or validate timing/calibration labels. |
| ownership | Reads immutable snapshot arrays synchronously, returns fixed census; does not retain runtime or allocate report arrays. |
| failure | noexcept: typed Failure→stop, catch-all→internal_error; census published only after complete scan/time gate. |
| cost | O(D*constant components) plus O(D) availability scan; fixed arrays, no output heap payload. Budget timing can read a clock. |
| Design | [include/crown/runtime/maintenance_cost.hpp](../../../../../../include/crown/runtime/maintenance_cost.hpp), [src/runtime/maintenance_cost.cpp](../../../../../../src/runtime/maintenance_cost.cpp), [docs/maintenance_cost.md](../../../../../maintenance_cost.md), [docs/ranking.md](../../../../../ranking.md), [docs/code_review.md](../../../../../code_review.md), [src/runtime/workload_statistics.cpp](../../../../../../src/runtime/workload_statistics.cpp) |

## B0014

[Lines 58–58](../../../../../../include/crown/runtime/maintenance_cost.hpp#L58); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct Coefficient { Ratio nanoseconds_per_unit; U64 samples{}, units{}, elapsed_ns{}; };
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Retain a reduced rate with its actual calibration provenance counts. |
| inputs / outputs | nanoseconds_per_unit Ratio plus sample count, unit total and elapsed_ns. |
| invariants | Isolated rate is summed elapsed/summed units. Fitted rate elapsed_ns is zero; raw joint timing stays in Calibration::fit_observations, avoiding duplicated observed time. |
| ownership | The caller owns all inline scalar/enum/optional/fixed-array members; this record alone retains no backing storage or runtime. |
| failure | This value declaration performs no validation or failure translation. Admission/consumer checks run separately before facts are accepted. |
| cost | Fixed-size value construction/copy/comparison; no dynamic allocation, clocks, scans or retained heap owner. |
| Design | [include/crown/runtime/maintenance_cost.hpp](../../../../../../include/crown/runtime/maintenance_cost.hpp), [src/runtime/maintenance_cost.cpp](../../../../../../src/runtime/maintenance_cost.cpp), [docs/maintenance_cost.md](../../../../../maintenance_cost.md), [docs/ranking.md](../../../../../ranking.md), [docs/code_review.md](../../../../../code_review.md) |

## B0015

[Lines 59–73](../../../../../../include/crown/runtime/maintenance_cost.hpp#L59); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
class Calibration {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Share an immutable factory-created calibration model. |
| inputs / outputs | Private Factory stores coefficients, copied context/backend text, origin/fit summary and optional raw observation vector behind const Data. |
| invariants | Origin and numerical diagnostics qualify interpretation; labels do not validate isolation/backend compatibility. No default/public arbitrary Data construction. |
| ownership | shared_ptr retains actual CalibrationData funded account. Handle copies share text/vector; default moves may null source, so accessors require a readable handle. |
| failure | Factory can return failed attempt; handle read/copy does not allocate. Last release frees owned text/observations/control; moved-from access is not promised. |
| cost | O(1) handle/refcount copy. Last release deallocates two text buffers, one trivial-observation vector and Data/control; it does not refit or explicitly scan observation bytes. Construction costs are explicit below. |
| Design | [include/crown/runtime/maintenance_cost.hpp](../../../../../../include/crown/runtime/maintenance_cost.hpp), [src/runtime/maintenance_cost.cpp](../../../../../../src/runtime/maintenance_cost.cpp), [docs/maintenance_cost.md](../../../../../maintenance_cost.md), [docs/ranking.md](../../../../../ranking.md), [docs/code_review.md](../../../../../code_review.md) |

```text
const std::array<std::optional<Coefficient>, component_count>& coefficients() const noexcept;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Borrow calibration coefficient array. |
| inputs / outputs | Readable factory handle returns const array&lt;optional&lt;Coefficient&gt;,component_count&gt;&. |
| invariants | Missing feature rate stays unavailable; zero fitted rates can be present. |
| ownership | Reference/text/span borrows CalibrationData; retain this or another shared Calibration handle for use. No returned view retains Data. |
| failure | For the stated live/readable object this noexcept accessor cannot fail. Borrowed references/views do not extend backing lifetime. |
| cost | O(1) member lookup/view construction; no allocation or clock. |
| Design | [include/crown/runtime/maintenance_cost.hpp](../../../../../../include/crown/runtime/maintenance_cost.hpp), [src/runtime/maintenance_cost.cpp](../../../../../../src/runtime/maintenance_cost.cpp), [docs/maintenance_cost.md](../../../../../maintenance_cost.md), [docs/ranking.md](../../../../../ranking.md), [docs/code_review.md](../../../../../code_review.md) |

```text
std::string_view context() const noexcept;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Borrow calibration declared environment context. |
| inputs / outputs | Readable factory handle returns string_view. |
| invariants | Retained label is unvalidated caller context. |
| ownership | Reference/text/span borrows CalibrationData; retain this or another shared Calibration handle for use. No returned view retains Data. |
| failure | For the stated live/readable object this noexcept accessor cannot fail. Borrowed references/views do not extend backing lifetime. |
| cost | O(1) member lookup/view construction; no allocation or clock. |
| Design | [include/crown/runtime/maintenance_cost.hpp](../../../../../../include/crown/runtime/maintenance_cost.hpp), [src/runtime/maintenance_cost.cpp](../../../../../../src/runtime/maintenance_cost.cpp), [docs/maintenance_cost.md](../../../../../maintenance_cost.md), [docs/ranking.md](../../../../../ranking.md), [docs/code_review.md](../../../../../code_review.md) |

```text
std::string_view backend() const noexcept;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Borrow calibration declared storage backend. |
| inputs / outputs | Readable factory handle returns string_view. |
| invariants | estimate compares exact backend label; this does not validate the calibration environment. |
| ownership | Reference/text/span borrows CalibrationData; retain this or another shared Calibration handle for use. No returned view retains Data. |
| failure | For the stated live/readable object this noexcept accessor cannot fail. Borrowed references/views do not extend backing lifetime. |
| cost | O(1) member lookup/view construction; no allocation or clock. |
| Design | [include/crown/runtime/maintenance_cost.hpp](../../../../../../include/crown/runtime/maintenance_cost.hpp), [src/runtime/maintenance_cost.cpp](../../../../../../src/runtime/maintenance_cost.cpp), [docs/maintenance_cost.md](../../../../../maintenance_cost.md), [docs/ranking.md](../../../../../ranking.md), [docs/code_review.md](../../../../../code_review.md) |

```text
const std::optional<FitSummary>& fit_summary() const noexcept;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Borrow calibration fit diagnostics. |
| inputs / outputs | Readable factory handle returns const optional&lt;FitSummary&gt;&. |
| invariants | Absent for isolated ratios; present retains numerical/model assumptions. |
| ownership | Reference/text/span borrows CalibrationData; retain this or another shared Calibration handle for use. No returned view retains Data. |
| failure | For the stated live/readable object this noexcept accessor cannot fail. Borrowed references/views do not extend backing lifetime. |
| cost | O(1) member lookup/view construction; no allocation or clock. |
| Design | [include/crown/runtime/maintenance_cost.hpp](../../../../../../include/crown/runtime/maintenance_cost.hpp), [src/runtime/maintenance_cost.cpp](../../../../../../src/runtime/maintenance_cost.cpp), [docs/maintenance_cost.md](../../../../../maintenance_cost.md), [docs/ranking.md](../../../../../ranking.md), [docs/code_review.md](../../../../../code_review.md) |

```text
std::span<const FitObservation> fit_observations() const noexcept;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Borrow calibration raw jointly fitted observations. |
| inputs / outputs | Readable factory handle returns span&lt;const FitObservation&gt;. |
| invariants | Joint timings remain whole-phase data; not independent timing per feature. |
| ownership | Reference/text/span borrows CalibrationData; retain this or another shared Calibration handle for use. No returned view retains Data. |
| failure | For the stated live/readable object this noexcept accessor cannot fail. Borrowed references/views do not extend backing lifetime. |
| cost | O(1) member lookup/view construction; no allocation or clock. |
| Design | [include/crown/runtime/maintenance_cost.hpp](../../../../../../include/crown/runtime/maintenance_cost.hpp), [src/runtime/maintenance_cost.cpp](../../../../../../src/runtime/maintenance_cost.cpp), [docs/maintenance_cost.md](../../../../../maintenance_cost.md), [docs/ranking.md](../../../../../ranking.md), [docs/code_review.md](../../../../../code_review.md) |

```text
CalibrationOrigin origin() const noexcept;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Read coefficient provenance. |
| inputs / outputs | Returns CalibrationOrigin by value. |
| invariants | isolated rates and jointly fitted assumptions remain distinguishable. |
| ownership | Requires readable Calibration; returned enum independent. |
| failure | For the stated live/readable object this noexcept accessor cannot fail. Borrowed references/views do not extend backing lifetime. |
| cost | O(1) member lookup/view construction; no allocation or clock. |
| Design | [include/crown/runtime/maintenance_cost.hpp](../../../../../../include/crown/runtime/maintenance_cost.hpp), [src/runtime/maintenance_cost.cpp](../../../../../../src/runtime/maintenance_cost.cpp), [docs/maintenance_cost.md](../../../../../maintenance_cost.md), [docs/ranking.md](../../../../../ranking.md), [docs/code_review.md](../../../../../code_review.md) |

```text
explicit Calibration(std::shared_ptr<const detail::CalibrationData> x):data_(std::move(x)) {}
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Adopt private immutable calibration Data. |
| inputs / outputs | Factory passes shared_ptr&lt;const CalibrationData&gt;; constructor moves it into data_. |
| invariants | Only factory publishes admitted data. This constructor does not rerun fitting or validate labels. |
| ownership | Retains Data actual receiving account; no clone or runtime pointer. |
| failure | Pointer move itself cannot allocate; signature is not marked noexcept. |
| cost | O(1) ownership transfer; payload construction precedes publication. |
| Design | [include/crown/runtime/maintenance_cost.hpp](../../../../../../include/crown/runtime/maintenance_cost.hpp), [src/runtime/maintenance_cost.cpp](../../../../../../src/runtime/maintenance_cost.cpp), [docs/maintenance_cost.md](../../../../../maintenance_cost.md), [docs/ranking.md](../../../../../ranking.md), [docs/code_review.md](../../../../../code_review.md) |

## B0016

[Lines 74–78](../../../../../../include/crown/runtime/maintenance_cost.hpp#L74); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct CalibrationAttempt {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Return calibration success/failure and its processing usage. |
| inputs / outputs | Stop, optional shared Calibration and Usage. |
| invariants | Engaged calibration published only after successful end/time gate; default internal_error does not mean zero-cost success. |
| ownership | Optional shared handle retains actual copied text/observations. Copying Attempt shares payload; final release can destroy it. |
| failure | No local handler in record. Factory noexcept boundary reports validation/resource/allocation/internal stops. |
| cost | Fixed record/refcount copy; final release includes real model payload, not guaranteed constant teardown. |
| Design | [include/crown/runtime/maintenance_cost.hpp](../../../../../../include/crown/runtime/maintenance_cost.hpp), [src/runtime/maintenance_cost.cpp](../../../../../../src/runtime/maintenance_cost.cpp), [docs/maintenance_cost.md](../../../../../maintenance_cost.md), [docs/ranking.md](../../../../../ranking.md), [docs/code_review.md](../../../../../code_review.md) |

## B0017

[Lines 79–90](../../../../../../include/crown/runtime/maintenance_cost.hpp#L79); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
[[nodiscard]] CalibrationAttempt calibrate(const resource::MemoryAccount&,std::string_view context,
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Aggregate isolated caller timings into exact reduced per-unit rates. |
| inputs / outputs | Existing account, nonempty context/backend, sample span and finite Limits; each sample component valid with units&gt;0 and elapsed_ns&gt;0. Empty span is allowed with all rates missing. |
| invariants | Accumulate checked sample/unit/time totals per component; never infer independence or truth from labels. Output rates use exact reduced 64-bit ratios and score_bits. |
| ownership | Copies context/backend into funded capture/42 Data; samples only borrowed for call and not retained raw. No fresh account/grant. |
| failure | noexcept maps Failure, bad_alloc and other exceptions to stops; partial Data destroyed, no calibration published on failure. |
| cost | O(text bytes+sample count*fixed-width arithmetic), Data/text allocation; final time gate may read clock. |
| Design | [include/crown/runtime/maintenance_cost.hpp](../../../../../../include/crown/runtime/maintenance_cost.hpp), [src/runtime/maintenance_cost.cpp](../../../../../../src/runtime/maintenance_cost.cpp), [docs/maintenance_cost.md](../../../../../maintenance_cost.md), [docs/ranking.md](../../../../../ranking.md), [docs/code_review.md](../../../../../code_review.md), [src/planner/ranking_detail.hpp](../../../../../../src/planner/ranking_detail.hpp) |

```text
[[nodiscard]] CalibrationAttempt fit(const resource::MemoryAccount&,std::string_view context,
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Fit a deterministic approximate nonnegative model and publish quantized exact rates. |
| inputs / outputs | Account/text, nonempty FitObservation span, validated FitOptions/Limits. Missing feature columns remain unavailable. |
| invariants | Zero-initialized fixed-coordinate NNLS; numerical rank from unregularized normalized Gram, ridge for coordinate updates. Training residuals/no underdetermination flag prove neither causal isolation nor future accuracy. |
| ownership | Copies raw observations/text into actual receiving account. Gram/elimination/coefficient work uses fixed stack arrays; published shared Data owns copied payload. |
| failure | noexcept maps Failure/bad_alloc/other; nonconvergence reports work_limit; nonfinite/unrepresentable arithmetic bit_limit. Publish only after all residual/time checks. |
| cost | For M observations,F=22,K iterations: O(M F²+F³+K F²+M F); heap O(MF+text), fixed O(F²) scratch. Actual budget gates and clock reads are diagnostics. |
| Design | [include/crown/runtime/maintenance_cost.hpp](../../../../../../include/crown/runtime/maintenance_cost.hpp), [src/runtime/maintenance_cost.cpp](../../../../../../src/runtime/maintenance_cost.cpp), [docs/maintenance_cost.md](../../../../../maintenance_cost.md), [docs/ranking.md](../../../../../ranking.md), [docs/code_review.md](../../../../../code_review.md), [src/planner/ranking_detail.hpp](../../../../../../src/planner/ranking_detail.hpp) |

## B0018

[Lines 91–102](../../../../../../include/crown/runtime/maintenance_cost.hpp#L91); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
class Profile {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Share actual quiescent-owner evidence bound to one checked candidate. |
| inputs / outputs | Private ProfileData owns candidate, RuntimeEvidence and pre-profile MemoryStatistics; const accessors expose them. |
| invariants | Factory verifies candidate membership/exact physical binding against actual captured owner. Public labels or equal DTO counts cannot substitute this authority. |
| ownership | Shared immutable Data retains candidate/evidence/plan/account/captures it actually owns, no mutable runtime pointer. Handle copy shares; default move can empty source. |
| failure | Factory may fail before publication; readable accessors noexcept. Last release can free evidence vectors/rows/plan/model metadata. |
| cost | Handle copies O(1); cold capture includes census/re-lowering allocations/scans/dual-owner peaks, not update work. |
| Design | [include/crown/runtime/maintenance_cost.hpp](../../../../../../include/crown/runtime/maintenance_cost.hpp), [src/runtime/maintenance_cost.cpp](../../../../../../src/runtime/maintenance_cost.cpp), [docs/maintenance_cost.md](../../../../../maintenance_cost.md), [docs/ranking.md](../../../../../ranking.md), [docs/code_review.md](../../../../../code_review.md) |

```text
const planner::MinimumHeightCandidate& candidate() const noexcept;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Borrow profile candidate. |
| inputs / outputs | Readable Profile returns const MinimumHeightCandidate&. |
| invariants | Original checked candidate retains proof authority, separate from cost estimate. |
| ownership | Reference borrows shared ProfileData; retain Profile ownership during use. |
| failure | For the stated live/readable object this noexcept accessor cannot fail. Borrowed references/views do not extend backing lifetime. |
| cost | O(1) member lookup/view construction; no allocation or clock. |
| Design | [include/crown/runtime/maintenance_cost.hpp](../../../../../../include/crown/runtime/maintenance_cost.hpp), [src/runtime/maintenance_cost.cpp](../../../../../../src/runtime/maintenance_cost.cpp), [docs/maintenance_cost.md](../../../../../maintenance_cost.md), [docs/ranking.md](../../../../../ranking.md), [docs/code_review.md](../../../../../code_review.md) |

```text
const runtime::ranking::RuntimeEvidence& evidence() const noexcept;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Borrow profile runtime evidence. |
| inputs / outputs | Readable Profile returns const RuntimeEvidence&. |
| invariants | Typed evidence comes from actual owner and has its own freshness/pending checks. |
| ownership | Reference borrows shared ProfileData; retain Profile ownership during use. |
| failure | For the stated live/readable object this noexcept accessor cannot fail. Borrowed references/views do not extend backing lifetime. |
| cost | O(1) member lookup/view construction; no allocation or clock. |
| Design | [include/crown/runtime/maintenance_cost.hpp](../../../../../../include/crown/runtime/maintenance_cost.hpp), [src/runtime/maintenance_cost.cpp](../../../../../../src/runtime/maintenance_cost.cpp), [docs/maintenance_cost.md](../../../../../maintenance_cost.md), [docs/ranking.md](../../../../../ranking.md), [docs/code_review.md](../../../../../code_review.md) |

```text
const resource::MemoryStatistics& memory_at_capture() const noexcept;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Borrow profile as-of account observation. |
| inputs / outputs | Readable Profile returns const MemoryStatistics&. |
| invariants | Read before allocating this profiling evidence; not future state/phase-peak/RSS prediction. |
| ownership | Reference borrows shared ProfileData; retain Profile ownership during use. |
| failure | For the stated live/readable object this noexcept accessor cannot fail. Borrowed references/views do not extend backing lifetime. |
| cost | O(1) member lookup/view construction; no allocation or clock. |
| Design | [include/crown/runtime/maintenance_cost.hpp](../../../../../../include/crown/runtime/maintenance_cost.hpp), [src/runtime/maintenance_cost.cpp](../../../../../../src/runtime/maintenance_cost.cpp), [docs/maintenance_cost.md](../../../../../maintenance_cost.md), [docs/ranking.md](../../../../../ranking.md), [docs/code_review.md](../../../../../code_review.md) |

```text
explicit Profile(std::shared_ptr<const detail::ProfileData> x):data_(std::move(x)) {}
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Adopt privately prepared profile evidence. |
| inputs / outputs | Factory moves shared_ptr&lt;const ProfileData&gt; into data_. |
| invariants | Membership/physical binding checks ran before publication. |
| ownership | Shares actual candidate/evidence/account ownership only; no new grant. |
| failure | Pointer transfer does not allocate; signature not marked noexcept. |
| cost | O(1) transfer; prior capture/replan costs occur before constructor. |
| Design | [include/crown/runtime/maintenance_cost.hpp](../../../../../../include/crown/runtime/maintenance_cost.hpp), [src/runtime/maintenance_cost.cpp](../../../../../../src/runtime/maintenance_cost.cpp), [docs/maintenance_cost.md](../../../../../maintenance_cost.md), [docs/ranking.md](../../../../../ranking.md), [docs/code_review.md](../../../../../code_review.md) |

## B0019

[Lines 103–103](../../../../../../include/crown/runtime/maintenance_cost.hpp#L103); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct CaptureAttempt { pr::Stop stop=pr::Stop::internal_error; std::optional<Profile> profile; pr::Usage usage; };
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Return actual-owner profile admission outcome. |
| inputs / outputs | Stop, optional shared Profile and Usage. |
| invariants | Failure leaves no new profile; stop/usage describes attempted diagnostic construction. |
| ownership | Copies share ProfileData; last optional release can destroy its retained graph. |
| failure | No local handler in carrier; capture owns noexcept translation. |
| cost | Fixed carrier/refcount work plus actual last graph teardown. |
| Design | [include/crown/runtime/maintenance_cost.hpp](../../../../../../include/crown/runtime/maintenance_cost.hpp), [src/runtime/maintenance_cost.cpp](../../../../../../src/runtime/maintenance_cost.cpp), [docs/maintenance_cost.md](../../../../../maintenance_cost.md), [docs/ranking.md](../../../../../ranking.md), [docs/code_review.md](../../../../../code_review.md) |

## B0020

[Lines 104–115](../../../../../../include/crown/runtime/maintenance_cost.hpp#L104); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
[[nodiscard]] CaptureAttempt capture(const planner::CandidateSnapshot&,std::size_t candidate,
    const PhysicalRuntime&,pr::Limits = {}) noexcept;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Capture a cost profile from an actual PhysicalRuntime. |
| inputs / outputs | Checked CandidateSnapshot/index plus owner and finite Limits return CaptureAttempt. Requires supported readable, quiescent actual owner with committed nonpending captured workload. |
| invariants | Captures runtime ranking evidence then re-lowers selected candidate into owner plan account and compares physical bytes. Reads account before this new profile allocation; no proof or automatic plan selection is minted. |
| ownership | Owner borrowed synchronously; Profile retains immutable candidate/evidence/plan and copied observations, not owner pointer. Native allocations stay on actual owner account. |
| failure | noexcept: evidence stop forwarded; Failure/replan/bad_alloc/other mapped. Partial new owner/capture/profile released before return. |
| cost | Cold native capture/census and re-lowering scan/allocate, current and candidate metadata may coexist. Not a constant accessor, clock-free hook or per-update cost. |
| Design | [include/crown/runtime/maintenance_cost.hpp](../../../../../../include/crown/runtime/maintenance_cost.hpp), [src/runtime/maintenance_cost.cpp](../../../../../../src/runtime/maintenance_cost.cpp), [docs/maintenance_cost.md](../../../../../maintenance_cost.md), [docs/ranking.md](../../../../../ranking.md), [docs/code_review.md](../../../../../code_review.md), [src/runtime/ranking_evidence.cpp](../../../../../../src/runtime/ranking_evidence.cpp), [include/crown/runtime/ranking_evidence.hpp](../../../../../../include/crown/runtime/ranking_evidence.hpp) |

```text
[[nodiscard]] CaptureAttempt capture(const planner::CandidateSnapshot&,std::size_t candidate,
    const DeltaRuntime&,pr::Limits = {}) noexcept;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Capture a cost profile from an actual DeltaRuntime. |
| inputs / outputs | Checked CandidateSnapshot/index plus owner and finite Limits return CaptureAttempt. Requires supported readable, quiescent actual owner with committed nonpending captured workload. |
| invariants | Captures runtime ranking evidence then re-lowers selected candidate into owner plan account and compares physical bytes. Reads account before this new profile allocation; no proof or automatic plan selection is minted. |
| ownership | Owner borrowed synchronously; Profile retains immutable candidate/evidence/plan and copied observations, not owner pointer. Native allocations stay on actual owner account. |
| failure | noexcept: evidence stop forwarded; Failure/replan/bad_alloc/other mapped. Partial new owner/capture/profile released before return. |
| cost | Cold native capture/census and re-lowering scan/allocate, current and candidate metadata may coexist. Not a constant accessor, clock-free hook or per-update cost. |
| Design | [include/crown/runtime/maintenance_cost.hpp](../../../../../../include/crown/runtime/maintenance_cost.hpp), [src/runtime/maintenance_cost.cpp](../../../../../../src/runtime/maintenance_cost.cpp), [docs/maintenance_cost.md](../../../../../maintenance_cost.md), [docs/ranking.md](../../../../../ranking.md), [docs/code_review.md](../../../../../code_review.md), [src/runtime/ranking_evidence.cpp](../../../../../../src/runtime/ranking_evidence.cpp), [include/crown/runtime/ranking_evidence.hpp](../../../../../../include/crown/runtime/ranking_evidence.hpp) |

```text
[[nodiscard]] CaptureAttempt capture(const planner::CandidateSnapshot&,std::size_t candidate,
    const QuerySession&,pr::Limits = {}) noexcept;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Capture a cost profile from an actual QuerySession. |
| inputs / outputs | Checked CandidateSnapshot/index plus owner and finite Limits return CaptureAttempt. Requires supported readable, quiescent actual owner with committed nonpending captured workload. |
| invariants | Captures runtime ranking evidence then re-lowers selected candidate into owner plan account and compares physical bytes. Reads account before this new profile allocation; no proof or automatic plan selection is minted. |
| ownership | Owner borrowed synchronously; Profile retains immutable candidate/evidence/plan and copied observations, not owner pointer. Native allocations stay on actual owner account. |
| failure | noexcept: evidence stop forwarded; Failure/replan/bad_alloc/other mapped. Partial new owner/capture/profile released before return. |
| cost | Cold native capture/census and re-lowering scan/allocate, current and candidate metadata may coexist. Not a constant accessor, clock-free hook or per-update cost. |
| Design | [include/crown/runtime/maintenance_cost.hpp](../../../../../../include/crown/runtime/maintenance_cost.hpp), [src/runtime/maintenance_cost.cpp](../../../../../../src/runtime/maintenance_cost.cpp), [docs/maintenance_cost.md](../../../../../maintenance_cost.md), [docs/ranking.md](../../../../../ranking.md), [docs/code_review.md](../../../../../code_review.md), [src/runtime/ranking_evidence.cpp](../../../../../../src/runtime/ranking_evidence.cpp), [include/crown/runtime/ranking_evidence.hpp](../../../../../../include/crown/runtime/ranking_evidence.hpp) |

```text
[[nodiscard]] runtime::ranking::Revalidation revalidate(const Profile&,const PhysicalRuntime&) noexcept;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Revalidate retained profile against current PhysicalRuntime. |
| inputs / outputs | Delegates profile.evidence() to runtime::ranking::revalidate and returns typed Revalidation. Requires readable Profile. |
| invariants | Checks actual owner/layer/committed sequence, pending state, physical-plan identity, full workload interval/options/modes and census usability. Matching labels alone do not establish current evidence. |
| ownership | Temporarily captures current original-account evidence/scratch; profile and owner not mutated. |
| failure | noexcept delegates typed revalidation outcomes; memory/resource/capture failure may return unavailable rather than fresh. |
| cost | Explicit cold recapture/census/allocation and identity/source comparisons; not O(1) stamp getter and not update overhead. |
| Design | [include/crown/runtime/maintenance_cost.hpp](../../../../../../include/crown/runtime/maintenance_cost.hpp), [src/runtime/maintenance_cost.cpp](../../../../../../src/runtime/maintenance_cost.cpp), [docs/maintenance_cost.md](../../../../../maintenance_cost.md), [docs/ranking.md](../../../../../ranking.md), [docs/code_review.md](../../../../../code_review.md), [src/runtime/ranking_evidence.cpp](../../../../../../src/runtime/ranking_evidence.cpp) |

```text
[[nodiscard]] runtime::ranking::Revalidation revalidate(const Profile&,const DeltaRuntime&) noexcept;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Revalidate retained profile against current DeltaRuntime. |
| inputs / outputs | Delegates profile.evidence() to runtime::ranking::revalidate and returns typed Revalidation. Requires readable Profile. |
| invariants | Checks actual owner/layer/committed sequence, pending state, physical-plan identity, full workload interval/options/modes and census usability. Matching labels alone do not establish current evidence. |
| ownership | Temporarily captures current original-account evidence/scratch; profile and owner not mutated. |
| failure | noexcept delegates typed revalidation outcomes; memory/resource/capture failure may return unavailable rather than fresh. |
| cost | Explicit cold recapture/census/allocation and identity/source comparisons; not O(1) stamp getter and not update overhead. |
| Design | [include/crown/runtime/maintenance_cost.hpp](../../../../../../include/crown/runtime/maintenance_cost.hpp), [src/runtime/maintenance_cost.cpp](../../../../../../src/runtime/maintenance_cost.cpp), [docs/maintenance_cost.md](../../../../../maintenance_cost.md), [docs/ranking.md](../../../../../ranking.md), [docs/code_review.md](../../../../../code_review.md), [src/runtime/ranking_evidence.cpp](../../../../../../src/runtime/ranking_evidence.cpp) |

```text
[[nodiscard]] runtime::ranking::Revalidation revalidate(const Profile&,const QuerySession&) noexcept;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Revalidate retained profile against current QuerySession. |
| inputs / outputs | Delegates profile.evidence() to runtime::ranking::revalidate and returns typed Revalidation. Requires readable Profile. |
| invariants | Checks actual owner/layer/committed sequence, pending state, physical-plan identity, full workload interval/options/modes and census usability. Matching labels alone do not establish current evidence. |
| ownership | Temporarily captures current original-account evidence/scratch; profile and owner not mutated. |
| failure | noexcept delegates typed revalidation outcomes; memory/resource/capture failure may return unavailable rather than fresh. |
| cost | Explicit cold recapture/census/allocation and identity/source comparisons; not O(1) stamp getter and not update overhead. |
| Design | [include/crown/runtime/maintenance_cost.hpp](../../../../../../include/crown/runtime/maintenance_cost.hpp), [src/runtime/maintenance_cost.cpp](../../../../../../src/runtime/maintenance_cost.cpp), [docs/maintenance_cost.md](../../../../../maintenance_cost.md), [docs/ranking.md](../../../../../ranking.md), [docs/code_review.md](../../../../../code_review.md), [src/runtime/ranking_evidence.cpp](../../../../../../src/runtime/ranking_evidence.cpp) |

## B0021

[Lines 116–116](../../../../../../include/crown/runtime/maintenance_cost.hpp#L116); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct InputDemand { TableId table; workload::Operation operation; U64 inputs{}; };
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Declare future physical input demand for one table/operation. |
| inputs / outputs | TableId, insert/erase and U64 inputs over caller-chosen horizon. |
| invariants | estimate requires every source-catalog table/op exactly once, including zero. Counts are forecasts, not clock-derived C01 rates or proof of actual future traffic. |
| ownership | The caller owns all inline scalar/enum/optional/fixed-array members; this record alone retains no backing storage or runtime. |
| failure | This value declaration performs no validation or failure translation. Admission/consumer checks run separately before facts are accepted. |
| cost | Fixed-size value construction/copy/comparison; no dynamic allocation, clocks, scans or retained heap owner. |
| Design | [include/crown/runtime/maintenance_cost.hpp](../../../../../../include/crown/runtime/maintenance_cost.hpp), [src/runtime/maintenance_cost.cpp](../../../../../../src/runtime/maintenance_cost.cpp), [docs/maintenance_cost.md](../../../../../maintenance_cost.md), [docs/ranking.md](../../../../../ranking.md), [docs/code_review.md](../../../../../code_review.md) |

## B0022

[Lines 117–124](../../../../../../include/crown/runtime/maintenance_cost.hpp#L117); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct OutputDemand {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Declare output/checkpoint/annotation demand over the same horizon. |
| inputs / outputs | Snapshot request and per-request rows, delta epochs/rows, encoded bytes, checkpoint requests/bytes, annotation changes; optional aggregate snapshot_rows_total. |
| invariants | Engaged aggregate overrides requests*rows_per_request. All quantities are assumptions; no model asserts output completeness or future real counts. |
| ownership | The caller owns all inline scalar/enum/optional/fixed-array members; this record alone retains no backing storage or runtime. |
| failure | This value declaration performs no validation or failure translation. Admission/consumer checks run separately before facts are accepted. |
| cost | Fixed-size value construction/copy/comparison; no dynamic allocation, clocks, scans or retained heap owner. |
| Design | [include/crown/runtime/maintenance_cost.hpp](../../../../../../include/crown/runtime/maintenance_cost.hpp), [src/runtime/maintenance_cost.cpp](../../../../../../src/runtime/maintenance_cost.cpp), [docs/maintenance_cost.md](../../../../../maintenance_cost.md), [docs/ranking.md](../../../../../ranking.md), [docs/code_review.md](../../../../../code_review.md) |

## B0023

[Lines 125–130](../../../../../../include/crown/runtime/maintenance_cost.hpp#L125); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct Request {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Borrow demand inputs for one explicit cost estimation request. |
| inputs / outputs | Span&lt;InputDemand&gt;, fixed OutputDemand, memory budget default256MiB and finite ranking Limits. |
| invariants | input backing lives unchanged through estimate; all table/op pairs exactly once. Memory budget is separate from nanosecond sum and describes only captured as-of constraint. |
| ownership | Request owns fixed scalars/output but borrows input span; copying Request does not retain demand array. Result explicitly copies inputs into receiver account. |
| failure | View construction no allocation; estimate validates/bounds arithmetic. Dangling span is caller error. |
| cost | O(1) request copy; estimate input-copy/validation work is separate. |
| Design | [include/crown/runtime/maintenance_cost.hpp](../../../../../../include/crown/runtime/maintenance_cost.hpp), [src/runtime/maintenance_cost.cpp](../../../../../../src/runtime/maintenance_cost.cpp), [docs/maintenance_cost.md](../../../../../maintenance_cost.md), [docs/ranking.md](../../../../../ranking.md), [docs/code_review.md](../../../../../code_review.md) |

## B0024

[Lines 131–131](../../../../../../include/crown/runtime/maintenance_cost.hpp#L131); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
enum class Basis { declared_demand, observed_census, observed_complete_detail };
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Qualify the basis of a priced term. |
| inputs / outputs | declared_demand/observed_census/observed_complete_detail. |
| invariants | Observed sample ratios remain assumptions when extended to future demand; basis is not a statistical confidence level. |
| ownership | The caller owns all inline scalar/enum/optional/fixed-array members; this record alone retains no backing storage or runtime. |
| failure | This value declaration performs no validation or failure translation. Admission/consumer checks run separately before facts are accepted. |
| cost | Constant-size tag; no runtime allocation, work scan or clock. Invalid casts are not automatically checked by this declaration. |
| Design | [include/crown/runtime/maintenance_cost.hpp](../../../../../../include/crown/runtime/maintenance_cost.hpp), [src/runtime/maintenance_cost.cpp](../../../../../../src/runtime/maintenance_cost.cpp), [docs/maintenance_cost.md](../../../../../maintenance_cost.md), [docs/ranking.md](../../../../../ranking.md), [docs/code_review.md](../../../../../code_review.md) |

## B0025

[Lines 132–136](../../../../../../include/crown/runtime/maintenance_cost.hpp#L132); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
enum class Issue : U64 {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Explain missing/incompatible model information. |
| inputs / outputs | Bit flags for missing profile/detail/stratum/calibration, backend/mode incompatibility, memory constraint or incompatible output mode. |
| invariants | A missing/flagged total is unavailable, not zero. A flag cannot create a planner proof or force runtime configuration. |
| ownership | The caller owns all inline scalar/enum/optional/fixed-array members; this record alone retains no backing storage or runtime. |
| failure | This value declaration performs no validation or failure translation. Admission/consumer checks run separately before facts are accepted. |
| cost | Constant-size tag; no runtime allocation, work scan or clock. Invalid casts are not automatically checked by this declaration. |
| Design | [include/crown/runtime/maintenance_cost.hpp](../../../../../../include/crown/runtime/maintenance_cost.hpp), [src/runtime/maintenance_cost.cpp](../../../../../../src/runtime/maintenance_cost.cpp), [docs/maintenance_cost.md](../../../../../maintenance_cost.md), [docs/ranking.md](../../../../../ranking.md), [docs/code_review.md](../../../../../code_review.md) |

## B0026

[Lines 137–137](../../../../../../include/crown/runtime/maintenance_cost.hpp#L137); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
using Issues = U64;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Store combinable model issue flags. |
| inputs / outputs | Issues is U64; bitwise flags summarize unavailability/compatibility. |
| invariants | Only declared Issue bits have defined interpretation; public raw bits are not authority. |
| ownership | The caller owns all inline scalar/enum/optional/fixed-array members; this record alone retains no backing storage or runtime. |
| failure | This value declaration performs no validation or failure translation. Admission/consumer checks run separately before facts are accepted. |
| cost | Fixed-size value construction/copy/comparison; no dynamic allocation, clocks, scans or retained heap owner. |
| Design | [include/crown/runtime/maintenance_cost.hpp](../../../../../../include/crown/runtime/maintenance_cost.hpp), [src/runtime/maintenance_cost.cpp](../../../../../../src/runtime/maintenance_cost.cpp), [docs/maintenance_cost.md](../../../../../maintenance_cost.md), [docs/ranking.md](../../../../../ranking.md), [docs/code_review.md](../../../../../code_review.md) |

## B0027

[Lines 138–138](../../../../../../include/crown/runtime/maintenance_cost.hpp#L138); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
constexpr Issues issue(Issue x) noexcept { return static_cast<Issues>(x); }
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Convert one Issue tag to its bit mask. |
| inputs / outputs | constexpr static_cast&lt;Issues&gt;(x). |
| invariants | No validation or filtering of arbitrary cast values. |
| ownership | Only the named inline values are read/copied/mutated; no input backing is retained. State receivers keep their already admitted metadata/account unchanged. |
| failure | No throwing operation or exception translation. Guards, when present, have exactly the behavior described above. |
| cost | O(1) constexpr integer conversion, no allocation/clock. |
| Design | [include/crown/runtime/maintenance_cost.hpp](../../../../../../include/crown/runtime/maintenance_cost.hpp), [src/runtime/maintenance_cost.cpp](../../../../../../src/runtime/maintenance_cost.cpp), [docs/maintenance_cost.md](../../../../../maintenance_cost.md), [docs/ranking.md](../../../../../ranking.md), [docs/code_review.md](../../../../../code_review.md) |

## B0028

[Lines 139–144](../../../../../../include/crown/runtime/maintenance_cost.hpp#L139); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct Confidence {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Retain source/basis counts for interpretation of one term. |
| inputs / outputs | Basis, workload Availability, complete_inputs and observed_events. |
| invariants | These are observed counts/quality metadata, never confidence interval, population expansion, future fact or minimum-height evidence. |
| ownership | The caller owns all inline scalar/enum/optional/fixed-array members; this record alone retains no backing storage or runtime. |
| failure | This value declaration performs no validation or failure translation. Admission/consumer checks run separately before facts are accepted. |
| cost | Fixed-size value construction/copy/comparison; no dynamic allocation, clocks, scans or retained heap owner. |
| Design | [include/crown/runtime/maintenance_cost.hpp](../../../../../../include/crown/runtime/maintenance_cost.hpp), [src/runtime/maintenance_cost.cpp](../../../../../../src/runtime/maintenance_cost.cpp), [docs/maintenance_cost.md](../../../../../maintenance_cost.md), [docs/ranking.md](../../../../../ranking.md), [docs/code_review.md](../../../../../code_review.md) |

## B0029

[Lines 145–151](../../../../../../include/crown/runtime/maintenance_cost.hpp#L145); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct Term {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Represent a possibly unavailable rational operation contribution. |
| inputs / outputs | Component, optional descriptor index, optional units/nanoseconds, Confidence and Issues. |
| invariants | Unknown units/rate propagate unavailability; zero units yield exact zero nanoseconds even without calibration. Public mutable terms do not establish factory evidence. |
| ownership | The caller owns all inline scalar/enum/optional/fixed-array members; this record alone retains no backing storage or runtime. |
| failure | This value declaration performs no validation or failure translation. Admission/consumer checks run separately before facts are accepted. |
| cost | Fixed-size value construction/copy/comparison; no dynamic allocation, clocks, scans or retained heap owner. |
| Design | [include/crown/runtime/maintenance_cost.hpp](../../../../../../include/crown/runtime/maintenance_cost.hpp), [src/runtime/maintenance_cost.cpp](../../../../../../src/runtime/maintenance_cost.cpp), [docs/maintenance_cost.md](../../../../../maintenance_cost.md), [docs/ranking.md](../../../../../ranking.md), [docs/code_review.md](../../../../../code_review.md) |

## B0030

[Lines 152–168](../../../../../../include/crown/runtime/maintenance_cost.hpp#L152); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct CandidateEstimate {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Own one candidate cost decomposition. |
| inputs / outputs | Checked candidate, optional shared Profile, funded ScoreVector&lt;Term&gt;, optional category/total ratios, stamp/modes, budget/as-of memory and issue flags. |
| invariants | All retained candidates get an entry, including missing-profile unavailable results. future_memory_unknown stays true; bytes are never added to nanoseconds. Public carrier mutation does not mint a Profile or proof. |
| ownership | Owns term vector on receiver account; copies deep-copy terms and share actual candidate/Profile owners. No runtime pointer or borrowed demand retained here. |
| failure | Copies/reserves can allocate and throw; factory builds privately and publishes complete Result only after final gate. |
| cost | O(T) deep term copy plus shared-owner operations; both term vectors coexist. Release deallocates trivial Term storage and releases candidate/Profile handles; final retained graph cleanup can be larger. |
| Design | [include/crown/runtime/maintenance_cost.hpp](../../../../../../include/crown/runtime/maintenance_cost.hpp), [src/runtime/maintenance_cost.cpp](../../../../../../src/runtime/maintenance_cost.cpp), [docs/maintenance_cost.md](../../../../../maintenance_cost.md), [docs/ranking.md](../../../../../ranking.md), [docs/code_review.md](../../../../../code_review.md), [include/crown/planner/ranking.hpp](../../../../../../include/crown/planner/ranking.hpp), [include/crown/resource/owner_allocator.hpp](../../../../../../include/crown/resource/owner_allocator.hpp) |

```text
CandidateEstimate(const resource::MemoryAccount&,planner::MinimumHeightCandidate);
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Bind an empty candidate estimate to receiving model account. |
| inputs / outputs | MemoryAccount and MinimumHeightCandidate construct moved candidate plus terms allocator capture/42. |
| invariants | No pricing or validation of forecast occurs in this constructor. |
| ownership | Shares candidate actual proof metadata and retains supplied account for later term storage. |
| failure | Empty allocator construction does not allocate term payload; candidate argument validity handled by factory. |
| cost | O(1) ownership/allocator setup, later evaluate reserves O(T) terms. |
| Design | [include/crown/runtime/maintenance_cost.hpp](../../../../../../include/crown/runtime/maintenance_cost.hpp), [src/runtime/maintenance_cost.cpp](../../../../../../src/runtime/maintenance_cost.cpp), [docs/maintenance_cost.md](../../../../../maintenance_cost.md), [docs/ranking.md](../../../../../ranking.md), [docs/code_review.md](../../../../../code_review.md) |

## B0031

[Lines 169–184](../../../../../../include/crown/runtime/maintenance_cost.hpp#L169); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
class Result {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Share an immutable complete cost-decomposition result. |
| inputs / outputs | Private Data retains Calibration, funded candidate-estimate vector/copied InputDemand array/fixed OutputDemand and processing Usage. |
| invariants | Result contains every checked candidate with explicit availability; it does not choose a candidate or enable maintenance/reoptimization. Demand is copied, never borrowed from Request. |
| ownership | Shared Data retains the actual calibration/profile/candidate payload it owns; handle copies do not deep-copy vectors. Default moves may null source, so use readable handle. |
| failure | Factory failures leave result absent. Accessors noexcept on readable handle; last release destroys nested vectors and any last evidence/calibration owners. |
| cost | Handle copies O(1) refcount; final release O(total terms/input entries and retained graph cleanup), not guaranteed constant teardown. |
| Design | [include/crown/runtime/maintenance_cost.hpp](../../../../../../include/crown/runtime/maintenance_cost.hpp), [src/runtime/maintenance_cost.cpp](../../../../../../src/runtime/maintenance_cost.cpp), [docs/maintenance_cost.md](../../../../../maintenance_cost.md), [docs/ranking.md](../../../../../ranking.md), [docs/code_review.md](../../../../../code_review.md) |

```text
const pr::ScoreVector<CandidateEstimate>& candidates() const noexcept;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Borrow Result candidate decompositions. |
| inputs / outputs | Readable shared Result returns const ScoreVector&lt;CandidateEstimate&gt;&. |
| invariants | Contains explicit entry for each snapshot candidate; inspect issues and optional totals. |
| ownership | Returned span/reference does not retain ResultData. Keep a Result handle alive; nested owned handles can be copied explicitly if needed. |
| failure | For the stated live/readable object this noexcept accessor cannot fail. Borrowed references/views do not extend backing lifetime. |
| cost | O(1) member lookup/view construction; no allocation or clock. |
| Design | [include/crown/runtime/maintenance_cost.hpp](../../../../../../include/crown/runtime/maintenance_cost.hpp), [src/runtime/maintenance_cost.cpp](../../../../../../src/runtime/maintenance_cost.cpp), [docs/maintenance_cost.md](../../../../../maintenance_cost.md), [docs/ranking.md](../../../../../ranking.md), [docs/code_review.md](../../../../../code_review.md) |

```text
const Calibration& calibration() const noexcept;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Borrow Result calibration model. |
| inputs / outputs | Readable shared Result returns const Calibration&. |
| invariants | Preserves isolated/fitted provenance and raw observations owned by calibration. |
| ownership | Returned span/reference does not retain ResultData. Keep a Result handle alive; nested owned handles can be copied explicitly if needed. |
| failure | For the stated live/readable object this noexcept accessor cannot fail. Borrowed references/views do not extend backing lifetime. |
| cost | O(1) member lookup/view construction; no allocation or clock. |
| Design | [include/crown/runtime/maintenance_cost.hpp](../../../../../../include/crown/runtime/maintenance_cost.hpp), [src/runtime/maintenance_cost.cpp](../../../../../../src/runtime/maintenance_cost.cpp), [docs/maintenance_cost.md](../../../../../maintenance_cost.md), [docs/ranking.md](../../../../../ranking.md), [docs/code_review.md](../../../../../code_review.md) |

```text
const pr::Usage& usage() const noexcept;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Borrow Result processing usage. |
| inputs / outputs | Readable shared Result returns const Usage&. |
| invariants | Logical work/bytes are not total allocator bytes, phase peak, future cost or RSS. |
| ownership | Returned span/reference does not retain ResultData. Keep a Result handle alive; nested owned handles can be copied explicitly if needed. |
| failure | For the stated live/readable object this noexcept accessor cannot fail. Borrowed references/views do not extend backing lifetime. |
| cost | O(1) member lookup/view construction; no allocation or clock. |
| Design | [include/crown/runtime/maintenance_cost.hpp](../../../../../../include/crown/runtime/maintenance_cost.hpp), [src/runtime/maintenance_cost.cpp](../../../../../../src/runtime/maintenance_cost.cpp), [docs/maintenance_cost.md](../../../../../maintenance_cost.md), [docs/ranking.md](../../../../../ranking.md), [docs/code_review.md](../../../../../code_review.md) |

```text
std::span<const InputDemand> input_demand() const noexcept;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Borrow Result copied input demand. |
| inputs / outputs | Readable shared Result returns span&lt;const InputDemand&gt;. |
| invariants | Exact forecast table/op counts are stored; Request lifetime no longer needed. |
| ownership | Returned span/reference does not retain ResultData. Keep a Result handle alive; nested owned handles can be copied explicitly if needed. |
| failure | For the stated live/readable object this noexcept accessor cannot fail. Borrowed references/views do not extend backing lifetime. |
| cost | O(1) member lookup/view construction; no allocation or clock. |
| Design | [include/crown/runtime/maintenance_cost.hpp](../../../../../../include/crown/runtime/maintenance_cost.hpp), [src/runtime/maintenance_cost.cpp](../../../../../../src/runtime/maintenance_cost.cpp), [docs/maintenance_cost.md](../../../../../maintenance_cost.md), [docs/ranking.md](../../../../../ranking.md), [docs/code_review.md](../../../../../code_review.md) |

```text
const OutputDemand& output_demand() const noexcept;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Borrow Result copied output demand. |
| inputs / outputs | Readable shared Result returns const OutputDemand&. |
| invariants | Values remain caller assumptions even inside factory result. |
| ownership | Returned span/reference does not retain ResultData. Keep a Result handle alive; nested owned handles can be copied explicitly if needed. |
| failure | For the stated live/readable object this noexcept accessor cannot fail. Borrowed references/views do not extend backing lifetime. |
| cost | O(1) member lookup/view construction; no allocation or clock. |
| Design | [include/crown/runtime/maintenance_cost.hpp](../../../../../../include/crown/runtime/maintenance_cost.hpp), [src/runtime/maintenance_cost.cpp](../../../../../../src/runtime/maintenance_cost.cpp), [docs/maintenance_cost.md](../../../../../maintenance_cost.md), [docs/ranking.md](../../../../../ranking.md), [docs/code_review.md](../../../../../code_review.md) |

```text
static constexpr unsigned format_version=1, arithmetic_version=1;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Version cost output representation and arithmetic policy. |
| inputs / outputs | format_version=1, arithmetic_version=1. |
| invariants | Versions identify local modeling formats, not a paper theorem or confidence guarantee. |
| ownership | The caller owns all inline scalar/enum/optional/fixed-array members; this record alone retains no backing storage or runtime. |
| failure | This value declaration performs no validation or failure translation. Admission/consumer checks run separately before facts are accepted. |
| cost | Fixed-size value construction/copy/comparison; no dynamic allocation, clocks, scans or retained heap owner. |
| Design | [include/crown/runtime/maintenance_cost.hpp](../../../../../../include/crown/runtime/maintenance_cost.hpp), [src/runtime/maintenance_cost.cpp](../../../../../../src/runtime/maintenance_cost.cpp), [docs/maintenance_cost.md](../../../../../maintenance_cost.md), [docs/ranking.md](../../../../../ranking.md), [docs/code_review.md](../../../../../code_review.md) |

```text
explicit Result(std::shared_ptr<const detail::ResultData> x):data_(std::move(x)) {}
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Adopt privately complete immutable cost result Data. |
| inputs / outputs | Factory moves shared_ptr&lt;const ResultData&gt; into data_. |
| invariants | Demand/candidates/usage already prepared and final budget/time check passed. |
| ownership | Shares actual receiving-account payload; no runtime or borrowed Request retained. |
| failure | Pointer transfer does not allocate; constructor signature not marked noexcept. |
| cost | O(1) transfer; result construction costs are paid before publication. |
| Design | [include/crown/runtime/maintenance_cost.hpp](../../../../../../include/crown/runtime/maintenance_cost.hpp), [src/runtime/maintenance_cost.cpp](../../../../../../src/runtime/maintenance_cost.cpp), [docs/maintenance_cost.md](../../../../../maintenance_cost.md), [docs/ranking.md](../../../../../ranking.md), [docs/code_review.md](../../../../../code_review.md) |

## B0032

[Lines 185–185](../../../../../../include/crown/runtime/maintenance_cost.hpp#L185); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct Attempt { pr::Stop stop=pr::Stop::internal_error; std::optional<Result> result; pr::Usage usage; };
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Return estimation outcome without throwing through the API. |
| inputs / outputs | Stop default internal_error, optional shared Result and processing Usage. |
| invariants | Only successful published result provides complete decompositions; missing optional does not imply zero model cost. |
| ownership | Copies share result graph, final release can free native terms and retained profile/calibration metadata. |
| failure | No local carrier handler; estimate converts typed/resource/allocation/other failures. |
| cost | Fixed/refcount copy plus actual final graph cleanup. |
| Design | [include/crown/runtime/maintenance_cost.hpp](../../../../../../include/crown/runtime/maintenance_cost.hpp), [src/runtime/maintenance_cost.cpp](../../../../../../src/runtime/maintenance_cost.cpp), [docs/maintenance_cost.md](../../../../../maintenance_cost.md), [docs/ranking.md](../../../../../ranking.md), [docs/code_review.md](../../../../../code_review.md) |

## B0033

[Lines 186–190](../../../../../../include/crown/runtime/maintenance_cost.hpp#L186); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
[[nodiscard]] Attempt estimate(const resource::MemoryAccount&,const planner::CandidateSnapshot&,
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Build every candidate cost decomposition under declared demand/model assumptions. |
| inputs / outputs | Existing account, valid nonempty CandidateSnapshot, unique member Profiles, readable Calibration, Request and finite bounds. Input pairs must be complete; code validates a dense request-derived matrix, checks catalog size/source/semantic/output agreement when profiles exist, and exact candidate binding for each profiled entry. |
| invariants | No automatic winner/proof/C05 switch. Missing profile/rate/stratum is explicit unavailable; calibrated sampled means are assumptions. Memory check is only profile pre-capture requested bytes against budget, never a future fit prediction. |
| ownership | Copies input/output into funded ResultData; term/candidate/binding scratch allocate on receiver account. Retains actual Profile/Calibration/candidate shared metadata, not runtime/Request spans. |
| failure | noexcept maps Failure/bad_alloc/other; partial Data/scratch released. Result published only after all candidate/binding/rational and final time gates. |
| cost | I² duplicate input checks, P*C candidate-key scans, and each profiled D descriptors performs linear demand/root/detail scans O(D(I+D)); terms O(D+I), identity/binding byte scans and allocations explicit. Clock gates may run. |
| Design | [include/crown/runtime/maintenance_cost.hpp](../../../../../../include/crown/runtime/maintenance_cost.hpp), [src/runtime/maintenance_cost.cpp](../../../../../../src/runtime/maintenance_cost.cpp), [docs/maintenance_cost.md](../../../../../maintenance_cost.md), [docs/ranking.md](../../../../../ranking.md), [docs/code_review.md](../../../../../code_review.md), [src/planner/ranking_detail.hpp](../../../../../../src/planner/ranking_detail.hpp) |
