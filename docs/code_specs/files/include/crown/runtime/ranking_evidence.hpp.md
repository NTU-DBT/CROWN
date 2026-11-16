# `include/crown/runtime/ranking_evidence.hpp` — block usage map

[Source](../../../../../../include/crown/runtime/ranking_evidence.hpp) · [Source index](../../../../README.md) · [Subsystem contracts](../../../../subsystem_contracts.md) · [Reviewed primitives](../../../../primitives.md)

Capture bounded distributions, workload counters, owner memory and explain observations without mislabeling partial information as exact.

Snapshot SHA-256: `6da407a721763bb360ad772049f292422506f8560e1408e59bc8921c0ee289c0`. 57 lines partitioned into 6 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [statistics](../../../../subsystem_contracts.md#statistics). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/statistics.md](../../../../../statistics.md), [docs/observability.md](../../../../../observability.md), [docs/memory_reports.md](../../../../../memory_reports.md), [docs/ranking_evaluation.md](../../../../../ranking_evaluation.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–8](../../../../../../include/crown/runtime/ranking_evidence.hpp#L1) | Imports dependencies; guards repeated header inclusion; declares namespace scope; declares types or opens a type body; declares values/defaults or compile-time conditions. |  · [reviewed contract](#b0001) |
| [B0002 · 9–13](../../../../../../include/crown/runtime/ranking_evidence.hpp#L9) | Type/record definition: struct CaptureOptions |  · [reviewed contract](#b0002) |
| [B0003 · 14–27](../../../../../../include/crown/runtime/ranking_evidence.hpp#L14) | Type/record definition: class RuntimeEvidence | returns *this · [reviewed contract](#b0003) |
| [B0004 · 28–33](../../../../../../include/crown/runtime/ranking_evidence.hpp#L28) | Type/record definition: struct CaptureAttempt |  · [reviewed contract](#b0004) |
| [B0005 · 34–45](../../../../../../include/crown/runtime/ranking_evidence.hpp#L34) | Type/record definition: struct Revalidation | returns true; depth==0; source comment (unverified): // Actual committed owner-boundary/read reasons, independent of whether a · [reviewed contract](#b0005) |
| [B0006 · 46–57](../../../../../../include/crown/runtime/ranking_evidence.hpp#L46) | declares callable signatures; declares values/defaults or compile-time conditions. | source comment (unverified): // Height-only uses the owner account without a source-fact capture/binding; · [reviewed contract](#b0006) |

## B0001

[Lines 1–8](../../../../../../include/crown/runtime/ranking_evidence.hpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
#pragma once
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Declare the runtime ranking_evidence public interface and its required types. |
| inputs / outputs | Header imports its explicit dependencies and declares the APIs/contracts below. |
| invariants | Inclusion does not construct a live query, source, report, proof or file owner. |
| ownership | Declarations retain no instance; object ownership and copies are specified at the individual APIs. |
| failure | Compile-time dependency/declaration boundary; runtime failures belong to instantiated objects/operations. |
| cost | No runtime action from inclusion itself; inline methods retain their stated actual costs. |
| Design | [include/crown/runtime/ranking_evidence.hpp](../../../../../../include/crown/runtime/ranking_evidence.hpp), [src/runtime/ranking_evidence.cpp](../../../../../../src/runtime/ranking_evidence.cpp), [docs/ranking.md](../../../../../ranking.md), [docs/ranking_accounting.md](../../../../../ranking_accounting.md) |

## B0002

[Lines 9–13](../../../../../../include/crown/runtime/ranking_evidence.hpp#L9); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct CaptureOptions {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Configure runtime evidence capture and processing. |
| inputs / outputs | Whether source cardinalities are requested, native state limits and independent ranking processing limits. |
| invariants | Public value/configuration only; changing fields does not perform admission, execute an input or create proof authority. |
| ownership | Inline fixed fields only; copying these values allocates no container or text. No source/native owner is retained. |
| failure | Declaration/field initialization performs no semantic validation. Consumers validate the actual values at their own boundary. |
| cost | Fixed-size initialization/copy/comparison; declaration itself performs no runtime scan or I/O. |
| Design | [include/crown/runtime/ranking_evidence.hpp](../../../../../../include/crown/runtime/ranking_evidence.hpp), [src/runtime/ranking_evidence.cpp](../../../../../../src/runtime/ranking_evidence.cpp), [docs/ranking.md](../../../../../ranking.md), [docs/ranking_accounting.md](../../../../../ranking_accounting.md) |

```text
bool source_cardinalities=true;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Whether actual source cardinality selections are requested. |
| inputs / outputs | Stores/exposes whether actual source cardinality selections are requested. |
| invariants | This field is descriptive/configuration data, not an independent admission or publication capability. |
| ownership | Inline fixed fields only; copying these values allocates no container or text. No source/native owner is retained. |
| failure | Assignment adds no validation; aggregate construction/copy has the ownership costs stated here. |
| cost | Fixed-size initialization/copy/comparison; declaration itself performs no runtime scan or I/O. |
| Design | [include/crown/runtime/ranking_evidence.hpp](../../../../../../include/crown/runtime/ranking_evidence.hpp), [src/runtime/ranking_evidence.cpp](../../../../../../src/runtime/ranking_evidence.cpp), [docs/ranking.md](../../../../../ranking.md), [docs/ranking_accounting.md](../../../../../ranking_accounting.md) |

```text
statistics::Limits state_limits;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | The separate native source/state capture budget. |
| inputs / outputs | Stores/exposes the separate native source/state capture budget. |
| invariants | This field is descriptive/configuration data, not an independent admission or publication capability. |
| ownership | Inline fixed fields only; copying these values allocates no container or text. No source/native owner is retained. |
| failure | Assignment adds no validation; aggregate construction/copy has the ownership costs stated here. |
| cost | Fixed-size initialization/copy/comparison; declaration itself performs no runtime scan or I/O. |
| Design | [include/crown/runtime/ranking_evidence.hpp](../../../../../../include/crown/runtime/ranking_evidence.hpp), [src/runtime/ranking_evidence.cpp](../../../../../../src/runtime/ranking_evidence.cpp), [docs/ranking.md](../../../../../ranking.md), [docs/ranking_accounting.md](../../../../../ranking_accounting.md) |

```text
pr::Limits processing;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | The evidence binding/census/processing limits, distinct from capture sublimits. |
| inputs / outputs | Stores/exposes the evidence binding/census/processing limits, distinct from capture sublimits. |
| invariants | This field is descriptive/configuration data, not an independent admission or publication capability. |
| ownership | Inline fixed fields only; copying these values allocates no container or text. No source/native owner is retained. |
| failure | Assignment adds no validation; aggregate construction/copy has the ownership costs stated here. |
| cost | Fixed-size initialization/copy/comparison; declaration itself performs no runtime scan or I/O. |
| Design | [include/crown/runtime/ranking_evidence.hpp](../../../../../../include/crown/runtime/ranking_evidence.hpp), [src/runtime/ranking_evidence.cpp](../../../../../../src/runtime/ranking_evidence.cpp), [docs/ranking.md](../../../../../ranking.md), [docs/ranking_accounting.md](../../../../../ranking_accounting.md) |

## B0003

[Lines 14–27](../../../../../../include/crown/runtime/ranking_evidence.hpp#L14); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
class RuntimeEvidence
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Retain checked actual-owner ranking inputs and native provenance. |
| inputs / outputs | Closed factory binds candidate original Catalog/Query to actual program, captures state/workload and records source/interval/mode availability. |
| invariants | No public constructor accepts arbitrary counts, owner IDs, stamps or paired report contexts. Facts remain scoped to the captured committed owner boundary. |
| ownership | Factory-only shared immutable Data retains typed ranking Evidence, optional CombinedCapture and optional genuine SessionStatisticsContext. No mutable runtime pointer/lease remains. Custom moves share Data and keep the source usable; references borrow the retained graph. |
| failure | Capture returns typed stop/reasons for invalid/binding/resource/allocation/internal failures; no native switch is authorized merely by owning evidence. |
| cost | Binding serialization/comparison, source selections and actual combined capture plus census/processing allocations under original account; repeated input_share scans can be quadratic in descriptor count. |
| Design | [include/crown/runtime/ranking_evidence.hpp](../../../../../../include/crown/runtime/ranking_evidence.hpp), [src/runtime/ranking_evidence.cpp](../../../../../../src/runtime/ranking_evidence.cpp), [docs/ranking.md](../../../../../ranking.md), [docs/ranking_accounting.md](../../../../../ranking_accounting.md) |

```text
RuntimeEvidence(const RuntimeEvidence&) noexcept=default;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Share runtime-evidence ownership. |
| inputs / outputs | Operates on a genuine nonempty runtime-evidence handle. |
| invariants | Closed factory and copy-like moves preserve Data needed by noexcept accessors. |
| ownership | Factory-only shared immutable Data retains typed ranking Evidence, optional CombinedCapture and optional genuine SessionStatisticsContext. No mutable runtime pointer/lease remains. Custom moves share Data and keep the source usable; references borrow the retained graph. |
| failure | Declared shared operations/accessors do not throw; no user callback or new native admission. |
| cost | Fixed shared retention, no native recapture. |
| Design | [include/crown/runtime/ranking_evidence.hpp](../../../../../../include/crown/runtime/ranking_evidence.hpp), [src/runtime/ranking_evidence.cpp](../../../../../../src/runtime/ranking_evidence.cpp), [docs/ranking.md](../../../../../ranking.md), [docs/ranking_accounting.md](../../../../../ranking_accounting.md) |

```text
RuntimeEvidence& operator=(const RuntimeEvidence&) noexcept=default;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Replace by shared runtime evidence. |
| inputs / outputs | Operates on a genuine nonempty runtime-evidence handle. |
| invariants | Closed factory and copy-like moves preserve Data needed by noexcept accessors. |
| ownership | Factory-only shared immutable Data retains typed ranking Evidence, optional CombinedCapture and optional genuine SessionStatisticsContext. No mutable runtime pointer/lease remains. Custom moves share Data and keep the source usable; references borrow the retained graph. |
| failure | Declared shared operations/accessors do not throw; no user callback or new native admission. |
| cost | Retention plus actual replaced graph release. |
| Design | [include/crown/runtime/ranking_evidence.hpp](../../../../../../include/crown/runtime/ranking_evidence.hpp), [src/runtime/ranking_evidence.cpp](../../../../../../src/runtime/ranking_evidence.cpp), [docs/ranking.md](../../../../../ranking.md), [docs/ranking_accounting.md](../../../../../ranking_accounting.md) |

```text
RuntimeEvidence(RuntimeEvidence&& x) noexcept:
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Copy-like move preserving both evidence handles. |
| inputs / outputs | Operates on a genuine nonempty runtime-evidence handle. |
| invariants | Closed factory and copy-like moves preserve Data needed by noexcept accessors. |
| ownership | Factory-only shared immutable Data retains typed ranking Evidence, optional CombinedCapture and optional genuine SessionStatisticsContext. No mutable runtime pointer/lease remains. Custom moves share Data and keep the source usable; references borrow the retained graph. |
| failure | Declared shared operations/accessors do not throw; no user callback or new native admission. |
| cost | Fixed shared retention; source remains valid. |
| Design | [include/crown/runtime/ranking_evidence.hpp](../../../../../../include/crown/runtime/ranking_evidence.hpp), [src/runtime/ranking_evidence.cpp](../../../../../../src/runtime/ranking_evidence.cpp), [docs/ranking.md](../../../../../ranking.md), [docs/ranking_accounting.md](../../../../../ranking_accounting.md) |

```text
RuntimeEvidence& operator=(RuntimeEvidence&& x) noexcept
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Copy-like evidence move assignment. |
| inputs / outputs | Operates on a genuine nonempty runtime-evidence handle. |
| invariants | Closed factory and copy-like moves preserve Data needed by noexcept accessors. |
| ownership | Factory-only shared immutable Data retains typed ranking Evidence, optional CombinedCapture and optional genuine SessionStatisticsContext. No mutable runtime pointer/lease remains. Custom moves share Data and keep the source usable; references borrow the retained graph. |
| failure | Declared shared operations/accessors do not throw; no user callback or new native admission. |
| cost | Retention/source preservation plus actual old graph release. |
| Design | [include/crown/runtime/ranking_evidence.hpp](../../../../../../include/crown/runtime/ranking_evidence.hpp), [src/runtime/ranking_evidence.cpp](../../../../../../src/runtime/ranking_evidence.cpp), [docs/ranking.md](../../../../../ranking.md), [docs/ranking_accounting.md](../../../../../ranking_accounting.md) |

```text
const pr::Evidence& inputs() const noexcept;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Borrow exact typed ranking inputs. |
| inputs / outputs | Operates on a genuine nonempty runtime-evidence handle. |
| invariants | Closed factory and copy-like moves preserve Data needed by noexcept accessors. |
| ownership | Factory-only shared immutable Data retains typed ranking Evidence, optional CombinedCapture and optional genuine SessionStatisticsContext. No mutable runtime pointer/lease remains. Custom moves share Data and keep the source usable; references borrow the retained graph. |
| failure | Declared shared operations/accessors do not throw; no user callback or new native admission. |
| cost | Fixed reference, no score recomputation. |
| Design | [include/crown/runtime/ranking_evidence.hpp](../../../../../../include/crown/runtime/ranking_evidence.hpp), [src/runtime/ranking_evidence.cpp](../../../../../../src/runtime/ranking_evidence.cpp), [docs/ranking.md](../../../../../ranking.md), [docs/ranking_accounting.md](../../../../../ranking_accounting.md) |

```text
const std::optional<statistics::CombinedCapture>& captured() const noexcept;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Borrow original native capture provenance. |
| inputs / outputs | Operates on a genuine nonempty runtime-evidence handle. |
| invariants | Closed factory and copy-like moves preserve Data needed by noexcept accessors. |
| ownership | Factory-only shared immutable Data retains typed ranking Evidence, optional CombinedCapture and optional genuine SessionStatisticsContext. No mutable runtime pointer/lease remains. Custom moves share Data and keep the source usable; references borrow the retained graph. |
| failure | Declared shared operations/accessors do not throw; no user callback or new native admission. |
| cost | Fixed reference; no fresh state read. |
| Design | [include/crown/runtime/ranking_evidence.hpp](../../../../../../include/crown/runtime/ranking_evidence.hpp), [src/runtime/ranking_evidence.cpp](../../../../../../src/runtime/ranking_evidence.cpp), [docs/ranking.md](../../../../../ranking.md), [docs/ranking_accounting.md](../../../../../ranking_accounting.md) |

```text
const std::optional<SessionStatisticsContext>& session_context() const noexcept;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Borrow optional actual session context. |
| inputs / outputs | Operates on a genuine nonempty runtime-evidence handle. |
| invariants | Closed factory and copy-like moves preserve Data needed by noexcept accessors. |
| ownership | Factory-only shared immutable Data retains typed ranking Evidence, optional CombinedCapture and optional genuine SessionStatisticsContext. No mutable runtime pointer/lease remains. Custom moves share Data and keep the source usable; references borrow the retained graph. |
| failure | Declared shared operations/accessors do not throw; no user callback or new native admission. |
| cost | Fixed reference; no caller-supplied context matching. |
| Design | [include/crown/runtime/ranking_evidence.hpp](../../../../../../include/crown/runtime/ranking_evidence.hpp), [src/runtime/ranking_evidence.cpp](../../../../../../src/runtime/ranking_evidence.cpp), [docs/ranking.md](../../../../../ranking.md), [docs/ranking_accounting.md](../../../../../ranking_accounting.md) |

```text
friend struct detail::Factory;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Restrict evidence construction to actual-owner factory. |
| inputs / outputs | Private construction/storage relationship. |
| invariants | No arbitrary caller-stamped facts constructor. |
| ownership | Factory-only shared immutable Data retains typed ranking Evidence, optional CombinedCapture and optional genuine SessionStatisticsContext. No mutable runtime pointer/lease remains. Custom moves share Data and keep the source usable; references borrow the retained graph. |
| failure | Declaration/descriptor publication adds no recovery layer. |
| cost | Fixed descriptor work; last release can free substantial captured native graph. |
| Design | [include/crown/runtime/ranking_evidence.hpp](../../../../../../include/crown/runtime/ranking_evidence.hpp), [src/runtime/ranking_evidence.cpp](../../../../../../src/runtime/ranking_evidence.cpp), [docs/ranking.md](../../../../../ranking.md), [docs/ranking_accounting.md](../../../../../ranking_accounting.md) |

```text
explicit RuntimeEvidence(std::shared_ptr<const detail::Data> data)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Publish prepared immutable evidence Data. |
| inputs / outputs | Private construction/storage relationship. |
| invariants | No arbitrary caller-stamped facts constructor. |
| ownership | Factory-only shared immutable Data retains typed ranking Evidence, optional CombinedCapture and optional genuine SessionStatisticsContext. No mutable runtime pointer/lease remains. Custom moves share Data and keep the source usable; references borrow the retained graph. |
| failure | Declaration/descriptor publication adds no recovery layer. |
| cost | Fixed descriptor work; last release can free substantial captured native graph. |
| Design | [include/crown/runtime/ranking_evidence.hpp](../../../../../../include/crown/runtime/ranking_evidence.hpp), [src/runtime/ranking_evidence.cpp](../../../../../../src/runtime/ranking_evidence.cpp), [docs/ranking.md](../../../../../ranking.md), [docs/ranking_accounting.md](../../../../../ranking_accounting.md) |

```text
std::shared_ptr<const detail::Data> data_;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Retain typed inputs/capture/session context graph. |
| inputs / outputs | Private construction/storage relationship. |
| invariants | No arbitrary caller-stamped facts constructor. |
| ownership | Factory-only shared immutable Data retains typed ranking Evidence, optional CombinedCapture and optional genuine SessionStatisticsContext. No mutable runtime pointer/lease remains. Custom moves share Data and keep the source usable; references borrow the retained graph. |
| failure | Declaration/descriptor publication adds no recovery layer. |
| cost | Fixed descriptor work; last release can free substantial captured native graph. |
| Design | [include/crown/runtime/ranking_evidence.hpp](../../../../../../include/crown/runtime/ranking_evidence.hpp), [src/runtime/ranking_evidence.cpp](../../../../../../src/runtime/ranking_evidence.cpp), [docs/ranking.md](../../../../../ranking.md), [docs/ranking_accounting.md](../../../../../ranking_accounting.md) |

## B0004

[Lines 28–33](../../../../../../include/crown/runtime/ranking_evidence.hpp#L28); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct CaptureAttempt {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Return runtime evidence capture outcome and selected usage. |
| inputs / outputs | Stop, optional genuine evidence, usage and reasons; failure never supplies fabricated zero facts. |
| invariants | Capture outcome data does not independently authorize lowering, native equivalence, time prediction or durable switching. |
| ownership | Fixed diagnostics plus optional shared RuntimeEvidence handle; copies share retained immutable graphs. |
| failure | Declaration/field initialization performs no semantic validation. Consumers validate the actual values at their own boundary. |
| cost | Fixed value/handle copy; final evidence release retains actual graph cleanup cost. |
| Design | [include/crown/runtime/ranking_evidence.hpp](../../../../../../include/crown/runtime/ranking_evidence.hpp), [src/runtime/ranking_evidence.cpp](../../../../../../src/runtime/ranking_evidence.cpp), [docs/ranking.md](../../../../../ranking.md), [docs/ranking_accounting.md](../../../../../ranking_accounting.md) |

```text
pr::Stop stop=
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | The typed capture outcome, default internal_error. |
| inputs / outputs | Stores/exposes the typed capture outcome, default internal_error. |
| invariants | Capture outcome data does not independently authorize lowering, native equivalence, time prediction or durable switching. |
| ownership | Fixed diagnostics plus optional shared RuntimeEvidence handle; copies share retained immutable graphs. |
| failure | Assignment adds no validation; aggregate construction/copy has the ownership costs stated here. |
| cost | Fixed value/handle copy; final evidence release retains actual graph cleanup cost. |
| Design | [include/crown/runtime/ranking_evidence.hpp](../../../../../../include/crown/runtime/ranking_evidence.hpp), [src/runtime/ranking_evidence.cpp](../../../../../../src/runtime/ranking_evidence.cpp), [docs/ranking.md](../../../../../ranking.md), [docs/ranking_accounting.md](../../../../../ranking_accounting.md) |

```text
std::optional<RuntimeEvidence> evidence;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | The optional genuine captured evidence only after completed preparation. |
| inputs / outputs | Stores/exposes the optional genuine captured evidence only after completed preparation. |
| invariants | Capture outcome data does not independently authorize lowering, native equivalence, time prediction or durable switching. |
| ownership | Fixed diagnostics plus optional shared RuntimeEvidence handle; copies share retained immutable graphs. |
| failure | Assignment adds no validation; aggregate construction/copy has the ownership costs stated here. |
| cost | Fixed value/handle copy; final evidence release retains actual graph cleanup cost. |
| Design | [include/crown/runtime/ranking_evidence.hpp](../../../../../../include/crown/runtime/ranking_evidence.hpp), [src/runtime/ranking_evidence.cpp](../../../../../../src/runtime/ranking_evidence.cpp), [docs/ranking.md](../../../../../ranking.md), [docs/ranking_accounting.md](../../../../../ranking_accounting.md) |

```text
pr::Usage usage;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | The selected evidence-processing work/byte/time observations. |
| inputs / outputs | Stores/exposes the selected evidence-processing work/byte/time observations. |
| invariants | Capture outcome data does not independently authorize lowering, native equivalence, time prediction or durable switching. |
| ownership | Fixed diagnostics plus optional shared RuntimeEvidence handle; copies share retained immutable graphs. |
| failure | Assignment adds no validation; aggregate construction/copy has the ownership costs stated here. |
| cost | Fixed value/handle copy; final evidence release retains actual graph cleanup cost. |
| Design | [include/crown/runtime/ranking_evidence.hpp](../../../../../../include/crown/runtime/ranking_evidence.hpp), [src/runtime/ranking_evidence.cpp](../../../../../../src/runtime/ranking_evidence.cpp), [docs/ranking.md](../../../../../ranking.md), [docs/ranking_accounting.md](../../../../../ranking_accounting.md) |

```text
pr::Reasons reasons{};
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | The explicit availability/failure reasons, not a substitute proof. |
| inputs / outputs | Stores/exposes the explicit availability/failure reasons, not a substitute proof. |
| invariants | Capture outcome data does not independently authorize lowering, native equivalence, time prediction or durable switching. |
| ownership | Fixed diagnostics plus optional shared RuntimeEvidence handle; copies share retained immutable graphs. |
| failure | Assignment adds no validation; aggregate construction/copy has the ownership costs stated here. |
| cost | Fixed value/handle copy; final evidence release retains actual graph cleanup cost. |
| Design | [include/crown/runtime/ranking_evidence.hpp](../../../../../../include/crown/runtime/ranking_evidence.hpp), [src/runtime/ranking_evidence.cpp](../../../../../../src/runtime/ranking_evidence.cpp), [docs/ranking.md](../../../../../ranking.md), [docs/ranking_accounting.md](../../../../../ranking_accounting.md) |

## B0005

[Lines 34–45](../../../../../../include/crown/runtime/ranking_evidence.hpp#L34); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct Revalidation {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Keep owner-boundary and two policy fact domains separate. |
| inputs / outputs | Actual boundary reasons plus committed-input depth and source-cardinality memory-policy reasons. |
| invariants | Policy usability helpers inspect these fields only; height_only usability is not proof that the current owner boundary is valid. |
| ownership | Inline fixed fields only; copying these values allocates no container or text. No source/native owner is retained. |
| failure | Declaration/field initialization performs no semantic validation. Consumers validate the actual values at their own boundary. |
| cost | Fixed-size initialization/copy/comparison; declaration itself performs no runtime scan or I/O. |
| Design | [include/crown/runtime/ranking_evidence.hpp](../../../../../../include/crown/runtime/ranking_evidence.hpp), [src/runtime/ranking_evidence.cpp](../../../../../../src/runtime/ranking_evidence.cpp), [docs/ranking.md](../../../../../ranking.md), [docs/ranking_accounting.md](../../../../../ranking_accounting.md) |

```text
pr::Reasons boundary{}, depth{}, memory{};
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | The independent actual boundary, depth-policy and memory-policy reason masks. |
| inputs / outputs | Stores/exposes the independent actual boundary, depth-policy and memory-policy reason masks. |
| invariants | Policy usability helpers inspect these fields only; height_only usability is not proof that the current owner boundary is valid. |
| ownership | Inline fixed fields only; copying these values allocates no container or text. No source/native owner is retained. |
| failure | Assignment adds no validation; aggregate construction/copy has the ownership costs stated here. |
| cost | Fixed-size initialization/copy/comparison; declaration itself performs no runtime scan or I/O. |
| Design | [include/crown/runtime/ranking_evidence.hpp](../../../../../../include/crown/runtime/ranking_evidence.hpp), [src/runtime/ranking_evidence.cpp](../../../../../../src/runtime/ranking_evidence.cpp), [docs/ranking.md](../../../../../ranking.md), [docs/ranking_accounting.md](../../../../../ranking_accounting.md) |

```text
bool usable(pr::Policy p) const noexcept
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Test policy-specific fact availability without inventing missing facts. |
| inputs / outputs | height_only returns true; depth policy needs depth==0; slot policy needs memory==0; unknown policy false. |
| invariants | Callers separately validate boundary; do not interpret this pure field test as source/epoch/publication authority. |
| ownership | Inline fixed fields only; copying these values allocates no container or text. No source/native owner is retained. |
| failure | Declared noexcept, no capture or validation failure. |
| cost | Fixed enum/mask checks. |
| Design | [include/crown/runtime/ranking_evidence.hpp](../../../../../../include/crown/runtime/ranking_evidence.hpp), [src/runtime/ranking_evidence.cpp](../../../../../../src/runtime/ranking_evidence.cpp), [docs/ranking.md](../../../../../ranking.md), [docs/ranking_accounting.md](../../../../../ranking_accounting.md) |

```text
bool all_facts_usable() const noexcept
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Test whether both statistical fact reason masks are clear. |
| inputs / outputs | Returns depth==0 && memory==0. |
| invariants | Pure field test on an editable result; actual returned revalidation ORs boundary failures into both fact domains. |
| ownership | Inline fixed fields only; copying these values allocates no container or text. No source/native owner is retained. |
| failure | No throwing operation. |
| cost | Two fixed mask checks. |
| Design | [include/crown/runtime/ranking_evidence.hpp](../../../../../../include/crown/runtime/ranking_evidence.hpp), [src/runtime/ranking_evidence.cpp](../../../../../../src/runtime/ranking_evidence.cpp), [docs/ranking.md](../../../../../ranking.md), [docs/ranking_accounting.md](../../../../../ranking_accounting.md) |

## B0006

[Lines 46–57](../../../../../../include/crown/runtime/ranking_evidence.hpp#L46); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
capture(const planner::CandidateSnapshot&,const PhysicalRuntime&
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Capture exact actual-owner runtime evidence for PhysicalRuntime. |
| inputs / outputs | Binds candidate original model, derives source selections, captures genuine state/workload and computes tagged census/availability. |
| invariants | Caller keeps synchronous exclusive owner access. Source table requests cap at256; unsupported/missing/saturated facts remain explicit reasons. |
| ownership | Factory-only shared immutable Data retains typed ranking Evidence, optional CombinedCapture and optional genuine SessionStatisticsContext. No mutable runtime pointer/lease remains. Custom moves share Data and keep the source usable; references borrow the retained graph. |
| failure | noexcept facade returns typed stops for limits, allocation, binding or internal exceptions; no runtime source advancement/switch. |
| cost | Full binding/capture/source and descriptor scans, native scratch/report allocations and potentially repeated descriptor census work within separate budgets. |
| Design | [include/crown/runtime/ranking_evidence.hpp](../../../../../../include/crown/runtime/ranking_evidence.hpp), [src/runtime/ranking_evidence.cpp](../../../../../../src/runtime/ranking_evidence.cpp), [docs/ranking.md](../../../../../ranking.md), [docs/ranking_accounting.md](../../../../../ranking_accounting.md) |

```text
revalidate(const RuntimeEvidence&,const PhysicalRuntime&
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Recheck retained evidence against current PhysicalRuntime facts. |
| inputs / outputs | Reads actual freshness and a fresh metadata/workload capture, checks pending/source/interval/options/modes and recomputes census reasons. |
| invariants | Owner boundary remains distinct from policy usability; a depth-only failure does not discard independently usable memory facts. |
| ownership | Factory-only shared immutable Data retains typed ranking Evidence, optional CombinedCapture and optional genuine SessionStatisticsContext. No mutable runtime pointer/lease remains. Custom moves share Data and keep the source usable; references borrow the retained graph. |
| failure | noexcept read/capture/census failures become read_failed/released/pending/etc reason masks, not zero-valued observations. |
| cost | May allocate new native metadata/workload capture and census scratch; O(descriptors²) repeated helper scans remain possible. Not allocation-free merely because noexcept. |
| Design | [include/crown/runtime/ranking_evidence.hpp](../../../../../../include/crown/runtime/ranking_evidence.hpp), [src/runtime/ranking_evidence.cpp](../../../../../../src/runtime/ranking_evidence.cpp), [docs/ranking.md](../../../../../ranking.md), [docs/ranking_accounting.md](../../../../../ranking_accounting.md) |

```text
rank_current(const planner::CandidateSnapshot&,const PhysicalRuntime&
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Rank the candidate family using the requested policy for PhysicalRuntime. |
| inputs / outputs | Height-only uses the runtime only for its account and does not check candidate-family/owner-source equality; depth/slot policies first capture bound actual evidence. |
| invariants | This differs from source-aware select_current, which always takes a fresh actual-owner capture. C02 scores are not measured nanoseconds or durable-switch authority. |
| ownership | Returned ranking attempt owns its selected typed handles; transient evidence/capture storage is private. |
| failure | noexcept returns allocation/internal/component stop outcomes and preserves typed missing-fact reasons. |
| cost | Policy-dependent pure ranking or evidence capture plus ranking; retains actual original-account allocations and work caps, no automatic runtime switch. |
| Design | [include/crown/runtime/ranking_evidence.hpp](../../../../../../include/crown/runtime/ranking_evidence.hpp), [src/runtime/ranking_evidence.cpp](../../../../../../src/runtime/ranking_evidence.cpp), [docs/ranking.md](../../../../../ranking.md), [docs/ranking_accounting.md](../../../../../ranking_accounting.md) |

```text
capture(const planner::CandidateSnapshot&,const DeltaRuntime&
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Capture exact actual-owner runtime evidence for DeltaRuntime. |
| inputs / outputs | Binds candidate original model, derives source selections, captures genuine state/workload and computes tagged census/availability. |
| invariants | Caller keeps synchronous exclusive owner access. Source table requests cap at256; unsupported/missing/saturated facts remain explicit reasons. |
| ownership | Factory-only shared immutable Data retains typed ranking Evidence, optional CombinedCapture and optional genuine SessionStatisticsContext. No mutable runtime pointer/lease remains. Custom moves share Data and keep the source usable; references borrow the retained graph. |
| failure | noexcept facade returns typed stops for limits, allocation, binding or internal exceptions; no runtime source advancement/switch. |
| cost | Full binding/capture/source and descriptor scans, native scratch/report allocations and potentially repeated descriptor census work within separate budgets. |
| Design | [include/crown/runtime/ranking_evidence.hpp](../../../../../../include/crown/runtime/ranking_evidence.hpp), [src/runtime/ranking_evidence.cpp](../../../../../../src/runtime/ranking_evidence.cpp), [docs/ranking.md](../../../../../ranking.md), [docs/ranking_accounting.md](../../../../../ranking_accounting.md) |

```text
revalidate(const RuntimeEvidence&,const DeltaRuntime&
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Recheck retained evidence against current DeltaRuntime facts. |
| inputs / outputs | Reads actual freshness and a fresh metadata/workload capture, checks pending/source/interval/options/modes and recomputes census reasons. |
| invariants | Owner boundary remains distinct from policy usability; a depth-only failure does not discard independently usable memory facts. |
| ownership | Factory-only shared immutable Data retains typed ranking Evidence, optional CombinedCapture and optional genuine SessionStatisticsContext. No mutable runtime pointer/lease remains. Custom moves share Data and keep the source usable; references borrow the retained graph. |
| failure | noexcept read/capture/census failures become read_failed/released/pending/etc reason masks, not zero-valued observations. |
| cost | May allocate new native metadata/workload capture and census scratch; O(descriptors²) repeated helper scans remain possible. Not allocation-free merely because noexcept. |
| Design | [include/crown/runtime/ranking_evidence.hpp](../../../../../../include/crown/runtime/ranking_evidence.hpp), [src/runtime/ranking_evidence.cpp](../../../../../../src/runtime/ranking_evidence.cpp), [docs/ranking.md](../../../../../ranking.md), [docs/ranking_accounting.md](../../../../../ranking_accounting.md) |

```text
rank_current(const planner::CandidateSnapshot&,const DeltaRuntime&
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Rank the candidate family using the requested policy for DeltaRuntime. |
| inputs / outputs | Height-only uses the runtime only for its account and does not check candidate-family/owner-source equality; depth/slot policies first capture bound actual evidence. |
| invariants | This differs from source-aware select_current, which always takes a fresh actual-owner capture. C02 scores are not measured nanoseconds or durable-switch authority. |
| ownership | Returned ranking attempt owns its selected typed handles; transient evidence/capture storage is private. |
| failure | noexcept returns allocation/internal/component stop outcomes and preserves typed missing-fact reasons. |
| cost | Policy-dependent pure ranking or evidence capture plus ranking; retains actual original-account allocations and work caps, no automatic runtime switch. |
| Design | [include/crown/runtime/ranking_evidence.hpp](../../../../../../include/crown/runtime/ranking_evidence.hpp), [src/runtime/ranking_evidence.cpp](../../../../../../src/runtime/ranking_evidence.cpp), [docs/ranking.md](../../../../../ranking.md), [docs/ranking_accounting.md](../../../../../ranking_accounting.md) |

```text
capture(const planner::CandidateSnapshot&,const QuerySession&
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Capture exact actual-owner runtime evidence for QuerySession. |
| inputs / outputs | Binds candidate original model, derives source selections, captures genuine state/workload and computes tagged census/availability. |
| invariants | Caller keeps synchronous exclusive owner access. Source table requests cap at256; unsupported/missing/saturated facts remain explicit reasons. |
| ownership | Factory-only shared immutable Data retains typed ranking Evidence, optional CombinedCapture and optional genuine SessionStatisticsContext. No mutable runtime pointer/lease remains. Custom moves share Data and keep the source usable; references borrow the retained graph. |
| failure | noexcept facade returns typed stops for limits, allocation, binding or internal exceptions; no runtime source advancement/switch. |
| cost | Full binding/capture/source and descriptor scans, native scratch/report allocations and potentially repeated descriptor census work within separate budgets. |
| Design | [include/crown/runtime/ranking_evidence.hpp](../../../../../../include/crown/runtime/ranking_evidence.hpp), [src/runtime/ranking_evidence.cpp](../../../../../../src/runtime/ranking_evidence.cpp), [docs/ranking.md](../../../../../ranking.md), [docs/ranking_accounting.md](../../../../../ranking_accounting.md) |

```text
revalidate(const RuntimeEvidence&,const QuerySession&
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Recheck retained evidence against current QuerySession facts. |
| inputs / outputs | Reads actual freshness and a fresh metadata/workload capture, checks pending/source/interval/options/modes and recomputes census reasons. |
| invariants | Owner boundary remains distinct from policy usability; a depth-only failure does not discard independently usable memory facts. |
| ownership | Factory-only shared immutable Data retains typed ranking Evidence, optional CombinedCapture and optional genuine SessionStatisticsContext. No mutable runtime pointer/lease remains. Custom moves share Data and keep the source usable; references borrow the retained graph. |
| failure | noexcept read/capture/census failures become read_failed/released/pending/etc reason masks, not zero-valued observations. |
| cost | May allocate new native metadata/workload capture and census scratch; O(descriptors²) repeated helper scans remain possible. Not allocation-free merely because noexcept. |
| Design | [include/crown/runtime/ranking_evidence.hpp](../../../../../../include/crown/runtime/ranking_evidence.hpp), [src/runtime/ranking_evidence.cpp](../../../../../../src/runtime/ranking_evidence.cpp), [docs/ranking.md](../../../../../ranking.md), [docs/ranking_accounting.md](../../../../../ranking_accounting.md) |

```text
rank_current(const planner::CandidateSnapshot&,const QuerySession&
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Rank the candidate family using the requested policy for QuerySession. |
| inputs / outputs | Height-only uses the runtime only for its account and does not check candidate-family/owner-source equality; depth/slot policies first capture bound actual evidence. |
| invariants | This differs from source-aware select_current, which always takes a fresh actual-owner capture. C02 scores are not measured nanoseconds or durable-switch authority. |
| ownership | Returned ranking attempt owns its selected typed handles; transient evidence/capture storage is private. |
| failure | noexcept returns allocation/internal/component stop outcomes and preserves typed missing-fact reasons. |
| cost | Policy-dependent pure ranking or evidence capture plus ranking; retains actual original-account allocations and work caps, no automatic runtime switch. |
| Design | [include/crown/runtime/ranking_evidence.hpp](../../../../../../include/crown/runtime/ranking_evidence.hpp), [src/runtime/ranking_evidence.cpp](../../../../../../src/runtime/ranking_evidence.cpp), [docs/ranking.md](../../../../../ranking.md), [docs/ranking_accounting.md](../../../../../ranking_accounting.md) |
