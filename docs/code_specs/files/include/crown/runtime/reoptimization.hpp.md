# `include/crown/runtime/reoptimization.hpp` — block usage map

[Source](../../../../../../include/crown/runtime/reoptimization.hpp) · [Source index](../../../../README.md) · [Subsystem contracts](../../../../subsystem_contracts.md) · [Reviewed primitives](../../../../primitives.md)

Coordinate input, window control, native epoch preparation, output delivery and durable recovery at one session lifecycle boundary.

Snapshot SHA-256: `819b13a17c1fe115722381d1e7083fb0fc429cfa572e6ed6e01beae993deea7a`. 86 lines partitioned into 15 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [session](../../../../subsystem_contracts.md#session). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/session_lifecycle.md](../../../../../session_lifecycle.md), [docs/session-journal.md](../../../../../session-journal.md), [docs/generations.md](../../../../../generations.md), [docs/local-sink.md](../../../../../local-sink.md), [docs/reoptimization.md](../../../../../reoptimization.md), [docs/native-replay.md](../../../../../native-replay.md), [docs/update_patterns.md](../../../../../update_patterns.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–12](../../../../../../include/crown/runtime/reoptimization.hpp#L1) | Imports dependencies; guards repeated header inclusion; declares namespace scope; declares types or opens a type body. | source comment (unverified): // A caller prediction in explicit time units, not a C02 height/depth/slot · [reviewed contract](#b0001) |
| [B0002 · 13–15](../../../../../../include/crown/runtime/reoptimization.hpp#L13) | Type/record definition: struct Forecast | source comment (unverified): // A caller prediction in explicit time units, not a C02 height/depth/slot · [reviewed contract](#b0002) |
| [B0003 · 16–24](../../../../../../include/crown/runtime/reoptimization.hpp#L16) | Type/record definition: struct Policy | source comment (unverified): // 100/10000 = 1%. · [reviewed contract](#b0003) |
| [B0004 · 25–29](../../../../../../include/crown/runtime/reoptimization.hpp#L25) | Type/record definition: struct PreparationCosts |  · [reviewed contract](#b0004) |
| [B0005 · 30–30](../../../../../../include/crown/runtime/reoptimization.hpp#L30) | Type/record definition: struct PublicationOptions |  · [reviewed contract](#b0005) |
| [B0006 · 31–34](../../../../../../include/crown/runtime/reoptimization.hpp#L31) | Type/record definition: enum class PolicyStop |  · [reviewed contract](#b0006) |
| [B0007 · 35–39](../../../../../../include/crown/runtime/reoptimization.hpp#L35) | Type/record definition: struct PolicyDecision |  · [reviewed contract](#b0007) |
| [B0008 · 40–46](../../../../../../include/crown/runtime/reoptimization.hpp#L40) | declares values/defaults or compile-time conditions. | source comment (unverified): // Pure allocation-free policy arithmetic. Eligibility grants no source/plan, · [reviewed contract](#b0008) |
| [B0009 · 47–52](../../../../../../include/crown/runtime/reoptimization.hpp#L47) | Type/record definition: struct Limits | source comment (unverified): // Per native result cursor; two at most. · [reviewed contract](#b0009) |
| [B0010 · 53–53](../../../../../../include/crown/runtime/reoptimization.hpp#L53) | Type/record definition: struct Boundary |  · [reviewed contract](#b0010) |
| [B0011 · 54–62](../../../../../../include/crown/runtime/reoptimization.hpp#L54) | Type/record definition: struct Options | source comment (unverified): // Optional C05 bridge fence, checked again against the actual owner. · [reviewed contract](#b0011) |
| [B0012 · 63–64](../../../../../../include/crown/runtime/reoptimization.hpp#L63) | Type/record definition: enum class Phase |  · [reviewed contract](#b0012) |
| [B0013 · 65–67](../../../../../../include/crown/runtime/reoptimization.hpp#L65) | Type/record definition: enum class Stop |  · [reviewed contract](#b0013) |
| [B0014 · 68–85](../../../../../../include/crown/runtime/reoptimization.hpp#L68) | Type/record definition: struct Status |  · [reviewed contract](#b0014) |
| [B0015 · 86–86](../../../../../../include/crown/runtime/reoptimization.hpp#L86) | Closes surrounding scope/type. | source comment (unverified): // namespace crown::runtime::reoptimization · [reviewed contract](#b0015) |

## B0001

[Lines 1–12](../../../../../../include/crown/runtime/reoptimization.hpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
#pragma once
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Declare the runtime reoptimization public interface and its required types. |
| inputs / outputs | Header imports its explicit dependencies and declares the APIs/contracts below. |
| invariants | Inclusion does not construct a live query, source, report, proof or file owner. |
| ownership | Declarations retain no instance; object ownership and copies are specified at the individual APIs. |
| failure | Compile-time dependency/declaration boundary; runtime failures belong to instantiated objects/operations. |
| cost | No runtime action from inclusion itself; inline methods retain their stated actual costs. |
| Design | [include/crown/runtime/reoptimization.hpp](../../../../../../include/crown/runtime/reoptimization.hpp), [src/runtime/reoptimization.cpp](../../../../../../src/runtime/reoptimization.cpp), [src/runtime/reoptimization_detail.hpp](../../../../../../src/runtime/reoptimization_detail.hpp), [docs/reoptimization.md](../../../../../reoptimization.md) |

## B0002

[Lines 13–15](../../../../../../include/crown/runtime/reoptimization.hpp#L13); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct Forecast {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Carry caller predictions in nanoseconds per input. |
| inputs / outputs | Current and target per-input time predictions plus future input horizon. |
| invariants | Prediction is not measured evidence, structural height/depth/slot score, original certificate or automatic enablement. |
| ownership | Inline fixed fields only; copying these values allocates no container or text. No source/native owner is retained. |
| failure | Declaration/field initialization performs no semantic validation. Consumers validate the actual values at their own boundary. |
| cost | Fixed-size initialization/copy/comparison; declaration itself performs no runtime scan or I/O. |
| Design | [include/crown/runtime/reoptimization.hpp](../../../../../../include/crown/runtime/reoptimization.hpp), [src/runtime/reoptimization.cpp](../../../../../../src/runtime/reoptimization.cpp), [src/runtime/reoptimization_detail.hpp](../../../../../../src/runtime/reoptimization_detail.hpp), [docs/reoptimization.md](../../../../../reoptimization.md) |

```text
std::uint64_t current_ns_per_input=0,target_ns_per_input=0,horizon_inputs=0;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | The two time-per-input predictions and amortization horizon, not observed C02 scores. |
| inputs / outputs | Stores/exposes the two time-per-input predictions and amortization horizon, not observed C02 scores. |
| invariants | Prediction is not measured evidence, structural height/depth/slot score, original certificate or automatic enablement. |
| ownership | Inline fixed fields only; copying these values allocates no container or text. No source/native owner is retained. |
| failure | Assignment adds no validation; aggregate construction/copy has the ownership costs stated here. |
| cost | Fixed-size initialization/copy/comparison; declaration itself performs no runtime scan or I/O. |
| Design | [include/crown/runtime/reoptimization.hpp](../../../../../../include/crown/runtime/reoptimization.hpp), [src/runtime/reoptimization.cpp](../../../../../../src/runtime/reoptimization.cpp), [src/runtime/reoptimization_detail.hpp](../../../../../../src/runtime/reoptimization_detail.hpp), [docs/reoptimization.md](../../../../../reoptimization.md) |

## B0003

[Lines 16–24](../../../../../../include/crown/runtime/reoptimization.hpp#L16); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct Policy {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Configure explicit time-saving and durable-publication reserve policy. |
| inputs / outputs | Epoch hysteresis, basis-point/absolute saving thresholds and a declared post-barrier time reserve. |
| invariants | Reserve is neither measured cleanup cost nor latency guarantee nor permission to roll back a selected durable root. |
| ownership | Inline fixed fields only; copying these values allocates no container or text. No source/native owner is retained. |
| failure | Declaration/field initialization performs no semantic validation. Consumers validate the actual values at their own boundary. |
| cost | Fixed-size initialization/copy/comparison; declaration itself performs no runtime scan or I/O. |
| Design | [include/crown/runtime/reoptimization.hpp](../../../../../../include/crown/runtime/reoptimization.hpp), [src/runtime/reoptimization.cpp](../../../../../../src/runtime/reoptimization.cpp), [src/runtime/reoptimization_detail.hpp](../../../../../../src/runtime/reoptimization_detail.hpp), [docs/reoptimization.md](../../../../../reoptimization.md) |

```text
std::uint64_t minimum_epoch_gap=1000;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | The minimum physical epoch gap since the last switch. |
| inputs / outputs | Stores/exposes the minimum physical epoch gap since the last switch. |
| invariants | Reserve is neither measured cleanup cost nor latency guarantee nor permission to roll back a selected durable root. |
| ownership | Inline fixed fields only; copying these values allocates no container or text. No source/native owner is retained. |
| failure | Assignment adds no validation; aggregate construction/copy has the ownership costs stated here. |
| cost | Fixed-size initialization/copy/comparison; declaration itself performs no runtime scan or I/O. |
| Design | [include/crown/runtime/reoptimization.hpp](../../../../../../include/crown/runtime/reoptimization.hpp), [src/runtime/reoptimization.cpp](../../../../../../src/runtime/reoptimization.cpp), [src/runtime/reoptimization_detail.hpp](../../../../../../src/runtime/reoptimization_detail.hpp), [docs/reoptimization.md](../../../../../reoptimization.md) |

```text
std::uint32_t minimum_saving_basis_points=100;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | The relative saving threshold in units of1/10,000. |
| inputs / outputs | Stores/exposes the relative saving threshold in units of1/10,000. |
| invariants | Reserve is neither measured cleanup cost nor latency guarantee nor permission to roll back a selected durable root. |
| ownership | Inline fixed fields only; copying these values allocates no container or text. No source/native owner is retained. |
| failure | Assignment adds no validation; aggregate construction/copy has the ownership costs stated here. |
| cost | Fixed-size initialization/copy/comparison; declaration itself performs no runtime scan or I/O. |
| Design | [include/crown/runtime/reoptimization.hpp](../../../../../../include/crown/runtime/reoptimization.hpp), [src/runtime/reoptimization.cpp](../../../../../../src/runtime/reoptimization.cpp), [src/runtime/reoptimization_detail.hpp](../../../../../../src/runtime/reoptimization_detail.hpp), [docs/reoptimization.md](../../../../../reoptimization.md) |

```text
std::uint64_t minimum_saving_ns_per_input=0;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | The independent absolute time-per-input saving threshold. |
| inputs / outputs | Stores/exposes the independent absolute time-per-input saving threshold. |
| invariants | Reserve is neither measured cleanup cost nor latency guarantee nor permission to roll back a selected durable root. |
| ownership | Inline fixed fields only; copying these values allocates no container or text. No source/native owner is retained. |
| failure | Assignment adds no validation; aggregate construction/copy has the ownership costs stated here. |
| cost | Fixed-size initialization/copy/comparison; declaration itself performs no runtime scan or I/O. |
| Design | [include/crown/runtime/reoptimization.hpp](../../../../../../include/crown/runtime/reoptimization.hpp), [src/runtime/reoptimization.cpp](../../../../../../src/runtime/reoptimization.cpp), [src/runtime/reoptimization_detail.hpp](../../../../../../src/runtime/reoptimization_detail.hpp), [docs/reoptimization.md](../../../../../reoptimization.md) |

```text
std::uint64_t publication_and_cleanup_reserve_ns=10'000'000;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | The caller-declared reserve for work after the irreversible durable barrier. |
| inputs / outputs | Stores/exposes the caller-declared reserve for work after the irreversible durable barrier. |
| invariants | Reserve is neither measured cleanup cost nor latency guarantee nor permission to roll back a selected durable root. |
| ownership | Inline fixed fields only; copying these values allocates no container or text. No source/native owner is retained. |
| failure | Assignment adds no validation; aggregate construction/copy has the ownership costs stated here. |
| cost | Fixed-size initialization/copy/comparison; declaration itself performs no runtime scan or I/O. |
| Design | [include/crown/runtime/reoptimization.hpp](../../../../../../include/crown/runtime/reoptimization.hpp), [src/runtime/reoptimization.cpp](../../../../../../src/runtime/reoptimization.cpp), [src/runtime/reoptimization_detail.hpp](../../../../../../src/runtime/reoptimization_detail.hpp), [docs/reoptimization.md](../../../../../reoptimization.md) |

## B0004

[Lines 25–29](../../../../../../include/crown/runtime/reoptimization.hpp#L25); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct PreparationCosts {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Record measured preparation components in explicit time units. |
| inputs / outputs | Snapshot/rebuild, catch-up, equivalence, compiler-artifact, publication preparation and measured selection preparation nanoseconds. |
| invariants | Public value/configuration only; changing fields does not perform admission, execute an input or create proof authority. |
| ownership | Inline fixed fields only; copying these values allocates no container or text. No source/native owner is retained. |
| failure | Declaration/field initialization performs no semantic validation. Consumers validate the actual values at their own boundary. |
| cost | Fixed-size initialization/copy/comparison; declaration itself performs no runtime scan or I/O. |
| Design | [include/crown/runtime/reoptimization.hpp](../../../../../../include/crown/runtime/reoptimization.hpp), [src/runtime/reoptimization.cpp](../../../../../../src/runtime/reoptimization.cpp), [src/runtime/reoptimization_detail.hpp](../../../../../../src/runtime/reoptimization_detail.hpp), [docs/reoptimization.md](../../../../../reoptimization.md) |

```text
std::uint64_t snapshot_rebuild_ns=0,catch_up_ns=0,equivalence_ns=0;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | The measured snapshot/rebuild, catch-up and equivalence preparation times. |
| inputs / outputs | Stores/exposes the measured snapshot/rebuild, catch-up and equivalence preparation times. |
| invariants | This field is descriptive/configuration data, not an independent admission or publication capability. |
| ownership | Inline fixed fields only; copying these values allocates no container or text. No source/native owner is retained. |
| failure | Assignment adds no validation; aggregate construction/copy has the ownership costs stated here. |
| cost | Fixed-size initialization/copy/comparison; declaration itself performs no runtime scan or I/O. |
| Design | [include/crown/runtime/reoptimization.hpp](../../../../../../include/crown/runtime/reoptimization.hpp), [src/runtime/reoptimization.cpp](../../../../../../src/runtime/reoptimization.cpp), [src/runtime/reoptimization_detail.hpp](../../../../../../src/runtime/reoptimization_detail.hpp), [docs/reoptimization.md](../../../../../reoptimization.md) |

```text
std::uint64_t compiler_artifact_ns=0,publication_prepare_ns=0;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | The explicit compiler artifact and publication preparation times. |
| inputs / outputs | Stores/exposes the explicit compiler artifact and publication preparation times. |
| invariants | This field is descriptive/configuration data, not an independent admission or publication capability. |
| ownership | Inline fixed fields only; copying these values allocates no container or text. No source/native owner is retained. |
| failure | Assignment adds no validation; aggregate construction/copy has the ownership costs stated here. |
| cost | Fixed-size initialization/copy/comparison; declaration itself performs no runtime scan or I/O. |
| Design | [include/crown/runtime/reoptimization.hpp](../../../../../../include/crown/runtime/reoptimization.hpp), [src/runtime/reoptimization.cpp](../../../../../../src/runtime/reoptimization.cpp), [src/runtime/reoptimization_detail.hpp](../../../../../../src/runtime/reoptimization_detail.hpp), [docs/reoptimization.md](../../../../../reoptimization.md) |

```text
std::uint64_t selection_prepare_ns=0;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | The measured C05 selection/capture/lowering/cache/teardown preparation cost. |
| inputs / outputs | Stores/exposes the measured C05 selection/capture/lowering/cache/teardown preparation cost. |
| invariants | This field is descriptive/configuration data, not an independent admission or publication capability. |
| ownership | Inline fixed fields only; copying these values allocates no container or text. No source/native owner is retained. |
| failure | Assignment adds no validation; aggregate construction/copy has the ownership costs stated here. |
| cost | Fixed-size initialization/copy/comparison; declaration itself performs no runtime scan or I/O. |
| Design | [include/crown/runtime/reoptimization.hpp](../../../../../../include/crown/runtime/reoptimization.hpp), [src/runtime/reoptimization.cpp](../../../../../../src/runtime/reoptimization.cpp), [src/runtime/reoptimization_detail.hpp](../../../../../../src/runtime/reoptimization_detail.hpp), [docs/reoptimization.md](../../../../../reoptimization.md) |

## B0005

[Lines 30–30](../../../../../../include/crown/runtime/reoptimization.hpp#L30); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct PublicationOptions {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Configure the existing selected-plan descriptor preparation. |
| inputs / outputs | Delegates descriptor byte/work limits to recovery::PlanDescriptorLimits. |
| invariants | Descriptor configuration is separate from actual root lock, verified candidate and irreversible publication. |
| ownership | Inline fixed fields only; copying these values allocates no container or text. No source/native owner is retained. |
| failure | Declaration/field initialization performs no semantic validation. Consumers validate the actual values at their own boundary. |
| cost | Fixed-size initialization/copy/comparison; declaration itself performs no runtime scan or I/O. |
| Design | [include/crown/runtime/reoptimization.hpp](../../../../../../include/crown/runtime/reoptimization.hpp), [src/runtime/reoptimization.cpp](../../../../../../src/runtime/reoptimization.cpp), [src/runtime/reoptimization_detail.hpp](../../../../../../src/runtime/reoptimization_detail.hpp), [docs/reoptimization.md](../../../../../reoptimization.md) |

## B0006

[Lines 31–34](../../../../../../include/crown/runtime/reoptimization.hpp#L31); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
enum class PolicyStop {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Explain pure time-policy eligibility or refusal. |
| inputs / outputs | Invalid policy/forecast/epoch, hysteresis, not faster/insufficient saving, checked arithmetic overflow, not paid back or eligible. |
| invariants | Public value/configuration only; changing fields does not perform admission, execute an input or create proof authority. |
| ownership | Inline fixed fields only; copying these values allocates no container or text. No source/native owner is retained. |
| failure | Declaration/field initialization performs no semantic validation. Consumers validate the actual values at their own boundary. |
| cost | Fixed-size initialization/copy/comparison; declaration itself performs no runtime scan or I/O. |
| Design | [include/crown/runtime/reoptimization.hpp](../../../../../../include/crown/runtime/reoptimization.hpp), [src/runtime/reoptimization.cpp](../../../../../../src/runtime/reoptimization.cpp), [src/runtime/reoptimization_detail.hpp](../../../../../../src/runtime/reoptimization_detail.hpp), [docs/reoptimization.md](../../../../../reoptimization.md) |

## B0007

[Lines 35–39](../../../../../../include/crown/runtime/reoptimization.hpp#L35); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct PolicyDecision {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Return checked time-policy arithmetic results. |
| inputs / outputs | Stop, per-input saving, summed measured/reserved cost and required amortization input count. |
| invariants | A decision is descriptive arithmetic only; eligibility establishes no source, equivalence, memory, epoch, output or durable authority. |
| ownership | Inline fixed fields only; copying these values allocates no container or text. No source/native owner is retained. |
| failure | Declaration/field initialization performs no semantic validation. Consumers validate the actual values at their own boundary. |
| cost | Fixed-size initialization/copy/comparison; declaration itself performs no runtime scan or I/O. |
| Design | [include/crown/runtime/reoptimization.hpp](../../../../../../include/crown/runtime/reoptimization.hpp), [src/runtime/reoptimization.cpp](../../../../../../src/runtime/reoptimization.cpp), [src/runtime/reoptimization_detail.hpp](../../../../../../src/runtime/reoptimization_detail.hpp), [docs/reoptimization.md](../../../../../reoptimization.md) |

```text
PolicyStop stop=
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | The policy outcome, default invalid_policy. |
| inputs / outputs | Stores/exposes the policy outcome, default invalid_policy. |
| invariants | A decision is descriptive arithmetic only; eligibility establishes no source, equivalence, memory, epoch, output or durable authority. |
| ownership | Inline fixed fields only; copying these values allocates no container or text. No source/native owner is retained. |
| failure | Assignment adds no validation; aggregate construction/copy has the ownership costs stated here. |
| cost | Fixed-size initialization/copy/comparison; declaration itself performs no runtime scan or I/O. |
| Design | [include/crown/runtime/reoptimization.hpp](../../../../../../include/crown/runtime/reoptimization.hpp), [src/runtime/reoptimization.cpp](../../../../../../src/runtime/reoptimization.cpp), [src/runtime/reoptimization_detail.hpp](../../../../../../src/runtime/reoptimization_detail.hpp), [docs/reoptimization.md](../../../../../reoptimization.md) |

```text
std::uint64_t saving_ns_per_input=0,charged_and_reserved_ns=0,
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | The per-input time saving and checked total measured/reserved preparation cost; required_future_inputs follows on the continuation line. |
| inputs / outputs | Stores/exposes the per-input time saving and checked total measured/reserved preparation cost; required_future_inputs follows on the continuation line. |
| invariants | A decision is descriptive arithmetic only; eligibility establishes no source, equivalence, memory, epoch, output or durable authority. |
| ownership | Inline fixed fields only; copying these values allocates no container or text. No source/native owner is retained. |
| failure | Assignment adds no validation; aggregate construction/copy has the ownership costs stated here. |
| cost | Fixed-size initialization/copy/comparison; declaration itself performs no runtime scan or I/O. |
| Design | [include/crown/runtime/reoptimization.hpp](../../../../../../include/crown/runtime/reoptimization.hpp), [src/runtime/reoptimization.cpp](../../../../../../src/runtime/reoptimization.cpp), [src/runtime/reoptimization_detail.hpp](../../../../../../src/runtime/reoptimization_detail.hpp), [docs/reoptimization.md](../../../../../reoptimization.md) |

```text
required_future_inputs=0;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Store the required future input count from ceiling payback arithmetic. |
| inputs / outputs | Inline continuation of PolicyDecision cost fields. |
| invariants | Mutable data alone never authorizes source acceptance, native plan execution, proof, output acknowledgment or durable publication. |
| ownership | Inline fixed fields only; copying these values allocates no container or text. No source/native owner is retained. |
| failure | Initialized field only; evaluate reports invalid/overflow conditions explicitly. |
| cost | Fixed-size initialization/copy/comparison; declaration itself performs no runtime scan or I/O. |
| Design | [include/crown/runtime/reoptimization.hpp](../../../../../../include/crown/runtime/reoptimization.hpp), [src/runtime/reoptimization.cpp](../../../../../../src/runtime/reoptimization.cpp), [src/runtime/reoptimization_detail.hpp](../../../../../../src/runtime/reoptimization_detail.hpp), [docs/reoptimization.md](../../../../../reoptimization.md) |

## B0008

[Lines 40–46](../../../../../../include/crown/runtime/reoptimization.hpp#L40); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
PolicyDecision evaluate(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Evaluate hysteresis, saving and payback with checked allocation-free arithmetic. |
| inputs / outputs | Reads fixed policy/optional forecast/current and previous epochs plus costs; returns typed decision. |
| invariants | Basis points must be&lt;=10,000; avoids overflowing products, sums cost terms with explicit checks and uses ceiling division instead of multiplying horizon by saving. |
| ownership | Borrows fixed inputs and returns inline result; no native owner/file/account is retained. |
| failure | Declared noexcept; invalid inputs and overflow return PolicyStop rather than throwing or partially authorizing a switch. |
| cost | Fixed arithmetic/branches only, no allocation, clock, capture, row scan or durable I/O. |
| Design | [include/crown/runtime/reoptimization.hpp](../../../../../../include/crown/runtime/reoptimization.hpp), [src/runtime/reoptimization.cpp](../../../../../../src/runtime/reoptimization.cpp), [src/runtime/reoptimization_detail.hpp](../../../../../../src/runtime/reoptimization_detail.hpp), [docs/reoptimization.md](../../../../../reoptimization.md) |

## B0009

[Lines 47–52](../../../../../../include/crown/runtime/reoptimization.hpp#L47); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct Limits {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Bound native candidate backlog and staged verification domains. |
| inputs / outputs | Independent backlog record/byte, staging, catch-up, equivalence row/work and per-result-cursor work caps. |
| invariants | Selected work/retained backlog caps do not replace the shared original query account or total elapsed CPU/RSS bounds. |
| ownership | Inline fixed fields only; copying these values allocates no container or text. No source/native owner is retained. |
| failure | Declaration/field initialization performs no semantic validation. Consumers validate the actual values at their own boundary. |
| cost | Fixed-size initialization/copy/comparison; declaration itself performs no runtime scan or I/O. |
| Design | [include/crown/runtime/reoptimization.hpp](../../../../../../include/crown/runtime/reoptimization.hpp), [src/runtime/reoptimization.cpp](../../../../../../src/runtime/reoptimization.cpp), [src/runtime/reoptimization_detail.hpp](../../../../../../src/runtime/reoptimization_detail.hpp), [docs/reoptimization.md](../../../../../reoptimization.md) |

```text
std::uint64_t backlog_records=4096,backlog_bytes=16*1024*1024,
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | The retained candidate backlog record/byte caps; following lines carry separate selected work domains. |
| inputs / outputs | Stores/exposes the retained candidate backlog record/byte caps; following lines carry separate selected work domains. |
| invariants | Selected work/retained backlog caps do not replace the shared original query account or total elapsed CPU/RSS bounds. |
| ownership | Inline fixed fields only; copying these values allocates no container or text. No source/native owner is retained. |
| failure | Assignment adds no validation; aggregate construction/copy has the ownership costs stated here. |
| cost | Fixed-size initialization/copy/comparison; declaration itself performs no runtime scan or I/O. |
| Design | [include/crown/runtime/reoptimization.hpp](../../../../../../include/crown/runtime/reoptimization.hpp), [src/runtime/reoptimization.cpp](../../../../../../src/runtime/reoptimization.cpp), [src/runtime/reoptimization_detail.hpp](../../../../../../src/runtime/reoptimization_detail.hpp), [docs/reoptimization.md](../../../../../reoptimization.md) |

```text
staging_work=64*1024*1024,catch_up_steps=16*1024*1024,
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | The source staging and catch-up step limits. |
| inputs / outputs | Stores/exposes the source staging and catch-up step limits. |
| invariants | Selected work/retained backlog caps do not replace the shared original query account or total elapsed CPU/RSS bounds. |
| ownership | Inline fixed fields only; copying these values allocates no container or text. No source/native owner is retained. |
| failure | Assignment adds no validation; aggregate construction/copy has the ownership costs stated here. |
| cost | Fixed-size initialization/copy/comparison; declaration itself performs no runtime scan or I/O. |
| Design | [include/crown/runtime/reoptimization.hpp](../../../../../../include/crown/runtime/reoptimization.hpp), [src/runtime/reoptimization.cpp](../../../../../../src/runtime/reoptimization.cpp), [src/runtime/reoptimization_detail.hpp](../../../../../../src/runtime/reoptimization_detail.hpp), [docs/reoptimization.md](../../../../../reoptimization.md) |

```text
equivalence_work=64*1024*1024,equivalence_rows=65536,
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | The independent equivalence comparison work and retained ordered-row caps. |
| inputs / outputs | Stores/exposes the independent equivalence comparison work and retained ordered-row caps. |
| invariants | Selected work/retained backlog caps do not replace the shared original query account or total elapsed CPU/RSS bounds. |
| ownership | Inline fixed fields only; copying these values allocates no container or text. No source/native owner is retained. |
| failure | Assignment adds no validation; aggregate construction/copy has the ownership costs stated here. |
| cost | Fixed-size initialization/copy/comparison; declaration itself performs no runtime scan or I/O. |
| Design | [include/crown/runtime/reoptimization.hpp](../../../../../../include/crown/runtime/reoptimization.hpp), [src/runtime/reoptimization.cpp](../../../../../../src/runtime/reoptimization.cpp), [src/runtime/reoptimization_detail.hpp](../../../../../../src/runtime/reoptimization_detail.hpp), [docs/reoptimization.md](../../../../../reoptimization.md) |

```text
equivalence_cursor_work=1'000'000;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | The allowance per native result cursor, at most two cursors. |
| inputs / outputs | Stores/exposes the allowance per native result cursor, at most two cursors. |
| invariants | Selected work/retained backlog caps do not replace the shared original query account or total elapsed CPU/RSS bounds. |
| ownership | Inline fixed fields only; copying these values allocates no container or text. No source/native owner is retained. |
| failure | Assignment adds no validation; aggregate construction/copy has the ownership costs stated here. |
| cost | Fixed-size initialization/copy/comparison; declaration itself performs no runtime scan or I/O. |
| Design | [include/crown/runtime/reoptimization.hpp](../../../../../../include/crown/runtime/reoptimization.hpp), [src/runtime/reoptimization.cpp](../../../../../../src/runtime/reoptimization.cpp), [src/runtime/reoptimization_detail.hpp](../../../../../../src/runtime/reoptimization_detail.hpp), [docs/reoptimization.md](../../../../../reoptimization.md) |

## B0010

[Lines 53–53](../../../../../../include/crown/runtime/reoptimization.hpp#L53); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct Boundary {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Name an expected actual source owner and physical epoch. |
| inputs / outputs | Fixed owner/epoch pair used as an optional bridge fence. |
| invariants | Editable expected values are checked against actual native source; they are not an owner capability. |
| ownership | Inline fixed fields only; copying these values allocates no container or text. No source/native owner is retained. |
| failure | Declaration/field initialization performs no semantic validation. Consumers validate the actual values at their own boundary. |
| cost | Fixed-size initialization/copy/comparison; declaration itself performs no runtime scan or I/O. |
| Design | [include/crown/runtime/reoptimization.hpp](../../../../../../include/crown/runtime/reoptimization.hpp), [src/runtime/reoptimization.cpp](../../../../../../src/runtime/reoptimization.cpp), [src/runtime/reoptimization_detail.hpp](../../../../../../src/runtime/reoptimization_detail.hpp), [docs/reoptimization.md](../../../../../reoptimization.md) |

## B0011

[Lines 54–62](../../../../../../include/crown/runtime/reoptimization.hpp#L54); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct Options {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Configure explicit candidate build, limits, policy and expected source. |
| inputs / outputs | Build/replan limits, staged caps, time policy/forecast and optional actual-source fence. |
| invariants | Configuration alone does not begin a switch or bypass candidate proof, source sameness, equivalence, output, account or durable barriers. |
| ownership | Inline fixed fields only; copying these values allocates no container or text. No source/native owner is retained. |
| failure | Declaration/field initialization performs no semantic validation. Consumers validate the actual values at their own boundary. |
| cost | Fixed-size initialization/copy/comparison; declaration itself performs no runtime scan or I/O. |
| Design | [include/crown/runtime/reoptimization.hpp](../../../../../../include/crown/runtime/reoptimization.hpp), [src/runtime/reoptimization.cpp](../../../../../../src/runtime/reoptimization.cpp), [src/runtime/reoptimization_detail.hpp](../../../../../../src/runtime/reoptimization_detail.hpp), [docs/reoptimization.md](../../../../../reoptimization.md) |

```text
BuildOptions build;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | The candidate snapshot construction method/work cap. |
| inputs / outputs | Stores/exposes the candidate snapshot construction method/work cap. |
| invariants | Configuration alone does not begin a switch or bypass candidate proof, source sameness, equivalence, output, account or durable barriers. |
| ownership | Inline fixed fields only; copying these values allocates no container or text. No source/native owner is retained. |
| failure | Assignment adds no validation; aggregate construction/copy has the ownership costs stated here. |
| cost | Fixed-size initialization/copy/comparison; declaration itself performs no runtime scan or I/O. |
| Design | [include/crown/runtime/reoptimization.hpp](../../../../../../include/crown/runtime/reoptimization.hpp), [src/runtime/reoptimization.cpp](../../../../../../src/runtime/reoptimization.cpp), [src/runtime/reoptimization_detail.hpp](../../../../../../src/runtime/reoptimization_detail.hpp), [docs/reoptimization.md](../../../../../reoptimization.md) |

```text
program::ReplanLimits replan;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | The native metadata/tree replan limits. |
| inputs / outputs | Stores/exposes the native metadata/tree replan limits. |
| invariants | Configuration alone does not begin a switch or bypass candidate proof, source sameness, equivalence, output, account or durable barriers. |
| ownership | Inline fixed fields only; copying these values allocates no container or text. No source/native owner is retained. |
| failure | Assignment adds no validation; aggregate construction/copy has the ownership costs stated here. |
| cost | Fixed-size initialization/copy/comparison; declaration itself performs no runtime scan or I/O. |
| Design | [include/crown/runtime/reoptimization.hpp](../../../../../../include/crown/runtime/reoptimization.hpp), [src/runtime/reoptimization.cpp](../../../../../../src/runtime/reoptimization.cpp), [src/runtime/reoptimization_detail.hpp](../../../../../../src/runtime/reoptimization_detail.hpp), [docs/reoptimization.md](../../../../../reoptimization.md) |

```text
Limits limits;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | The staged backlog/catch-up/equivalence caps. |
| inputs / outputs | Stores/exposes the staged backlog/catch-up/equivalence caps. |
| invariants | Configuration alone does not begin a switch or bypass candidate proof, source sameness, equivalence, output, account or durable barriers. |
| ownership | Inline fixed fields only; copying these values allocates no container or text. No source/native owner is retained. |
| failure | Assignment adds no validation; aggregate construction/copy has the ownership costs stated here. |
| cost | Fixed-size initialization/copy/comparison; declaration itself performs no runtime scan or I/O. |
| Design | [include/crown/runtime/reoptimization.hpp](../../../../../../include/crown/runtime/reoptimization.hpp), [src/runtime/reoptimization.cpp](../../../../../../src/runtime/reoptimization.cpp), [src/runtime/reoptimization_detail.hpp](../../../../../../src/runtime/reoptimization_detail.hpp), [docs/reoptimization.md](../../../../../reoptimization.md) |

```text
Policy policy;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | The explicit time-unit eligibility policy. |
| inputs / outputs | Stores/exposes the explicit time-unit eligibility policy. |
| invariants | Configuration alone does not begin a switch or bypass candidate proof, source sameness, equivalence, output, account or durable barriers. |
| ownership | Inline fixed fields only; copying these values allocates no container or text. No source/native owner is retained. |
| failure | Assignment adds no validation; aggregate construction/copy has the ownership costs stated here. |
| cost | Fixed-size initialization/copy/comparison; declaration itself performs no runtime scan or I/O. |
| Design | [include/crown/runtime/reoptimization.hpp](../../../../../../include/crown/runtime/reoptimization.hpp), [src/runtime/reoptimization.cpp](../../../../../../src/runtime/reoptimization.cpp), [src/runtime/reoptimization_detail.hpp](../../../../../../src/runtime/reoptimization_detail.hpp), [docs/reoptimization.md](../../../../../reoptimization.md) |

```text
std::optional<Forecast> forecast;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | The optional caller time prediction. |
| inputs / outputs | Stores/exposes the optional caller time prediction. |
| invariants | Configuration alone does not begin a switch or bypass candidate proof, source sameness, equivalence, output, account or durable barriers. |
| ownership | Inline fixed fields only; copying these values allocates no container or text. No source/native owner is retained. |
| failure | Assignment adds no validation; aggregate construction/copy has the ownership costs stated here. |
| cost | Fixed-size initialization/copy/comparison; declaration itself performs no runtime scan or I/O. |
| Design | [include/crown/runtime/reoptimization.hpp](../../../../../../include/crown/runtime/reoptimization.hpp), [src/runtime/reoptimization.cpp](../../../../../../src/runtime/reoptimization.cpp), [src/runtime/reoptimization_detail.hpp](../../../../../../src/runtime/reoptimization_detail.hpp), [docs/reoptimization.md](../../../../../reoptimization.md) |

```text
std::optional<Boundary> expected;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | The optional actual-owner/epoch fence checked again during native preparation. |
| inputs / outputs | Stores/exposes the optional actual-owner/epoch fence checked again during native preparation. |
| invariants | Configuration alone does not begin a switch or bypass candidate proof, source sameness, equivalence, output, account or durable barriers. |
| ownership | Inline fixed fields only; copying these values allocates no container or text. No source/native owner is retained. |
| failure | Assignment adds no validation; aggregate construction/copy has the ownership costs stated here. |
| cost | Fixed-size initialization/copy/comparison; declaration itself performs no runtime scan or I/O. |
| Design | [include/crown/runtime/reoptimization.hpp](../../../../../../include/crown/runtime/reoptimization.hpp), [src/runtime/reoptimization.cpp](../../../../../../src/runtime/reoptimization.cpp), [src/runtime/reoptimization_detail.hpp](../../../../../../src/runtime/reoptimization_detail.hpp), [docs/reoptimization.md](../../../../../reoptimization.md) |

## B0012

[Lines 63–64](../../../../../../include/crown/runtime/reoptimization.hpp#L63); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
enum class Phase {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Describe the private native candidate lifecycle. |
| inputs / outputs | Inactive/catch-up/barrier/output waiting/verified/rejected/cancelled/failed/complete/recovery_required. |
| invariants | Public value/configuration only; changing fields does not perform admission, execute an input or create proof authority. |
| ownership | Inline fixed fields only; copying these values allocates no container or text. No source/native owner is retained. |
| failure | Declaration/field initialization performs no semantic validation. Consumers validate the actual values at their own boundary. |
| cost | Fixed-size initialization/copy/comparison; declaration itself performs no runtime scan or I/O. |
| Design | [include/crown/runtime/reoptimization.hpp](../../../../../../include/crown/runtime/reoptimization.hpp), [src/runtime/reoptimization.cpp](../../../../../../src/runtime/reoptimization.cpp), [src/runtime/reoptimization_detail.hpp](../../../../../../src/runtime/reoptimization_detail.hpp), [docs/reoptimization.md](../../../../../reoptimization.md) |

## B0013

[Lines 65–67](../../../../../../include/crown/runtime/reoptimization.hpp#L65); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
enum class Stop {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Describe concrete native preparation stop causes. |
| inputs / outputs | Backlog/staging/catch-up/equivalence limits, allocation, source/sequence/result/native failure and counter/clock faults. |
| invariants | Public value/configuration only; changing fields does not perform admission, execute an input or create proof authority. |
| ownership | Inline fixed fields only; copying these values allocates no container or text. No source/native owner is retained. |
| failure | Declaration/field initialization performs no semantic validation. Consumers validate the actual values at their own boundary. |
| cost | Fixed-size initialization/copy/comparison; declaration itself performs no runtime scan or I/O. |
| Design | [include/crown/runtime/reoptimization.hpp](../../../../../../include/crown/runtime/reoptimization.hpp), [src/runtime/reoptimization.cpp](../../../../../../src/runtime/reoptimization.cpp), [src/runtime/reoptimization_detail.hpp](../../../../../../src/runtime/reoptimization_detail.hpp), [docs/reoptimization.md](../../../../../reoptimization.md) |

## B0014

[Lines 68–85](../../../../../../include/crown/runtime/reoptimization.hpp#L68); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct Status {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Return actual reoptimization observations without exporting mutable candidate state. |
| inputs / outputs | Phase/stop/flags, owner/epoch/backlog/work/comparison/time counters, fixed source/target digests, costs/decision and two actual account snapshots. |
| invariants | Status/flags/digests are observations, not a verified candidate, root lock, sink receipt or permission to publish/roll back durable selection. |
| ownership | Inline fixed fields only; copying these values allocates no container or text. No source/native owner is retained. |
| failure | Declaration/field initialization performs no semantic validation. Consumers validate the actual values at their own boundary. |
| cost | Fixed-size initialization/copy/comparison; declaration itself performs no runtime scan or I/O. |
| Design | [include/crown/runtime/reoptimization.hpp](../../../../../../include/crown/runtime/reoptimization.hpp), [src/runtime/reoptimization.cpp](../../../../../../src/runtime/reoptimization.cpp), [src/runtime/reoptimization_detail.hpp](../../../../../../src/runtime/reoptimization_detail.hpp), [docs/reoptimization.md](../../../../../reoptimization.md) |

```text
Phase phase=
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | The observed private candidate lifecycle phase. |
| inputs / outputs | Stores/exposes the observed private candidate lifecycle phase. |
| invariants | Status/flags/digests are observations, not a verified candidate, root lock, sink receipt or permission to publish/roll back durable selection. |
| ownership | Inline fixed fields only; copying these values allocates no container or text. No source/native owner is retained. |
| failure | Assignment adds no validation; aggregate construction/copy has the ownership costs stated here. |
| cost | Fixed-size initialization/copy/comparison; declaration itself performs no runtime scan or I/O. |
| Design | [include/crown/runtime/reoptimization.hpp](../../../../../../include/crown/runtime/reoptimization.hpp), [src/runtime/reoptimization.cpp](../../../../../../src/runtime/reoptimization.cpp), [src/runtime/reoptimization_detail.hpp](../../../../../../src/runtime/reoptimization_detail.hpp), [docs/reoptimization.md](../../../../../reoptimization.md) |

```text
Stop stop=Stop::none;

```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | The concrete candidate stop cause. |
| inputs / outputs | Stores/exposes the concrete candidate stop cause. |
| invariants | Status/flags/digests are observations, not a verified candidate, root lock, sink receipt or permission to publish/roll back durable selection. |
| ownership | Inline fixed fields only; copying these values allocates no container or text. No source/native owner is retained. |
| failure | Assignment adds no validation; aggregate construction/copy has the ownership costs stated here. |
| cost | Fixed-size initialization/copy/comparison; declaration itself performs no runtime scan or I/O. |
| Design | [include/crown/runtime/reoptimization.hpp](../../../../../../include/crown/runtime/reoptimization.hpp), [src/runtime/reoptimization.cpp](../../../../../../src/runtime/reoptimization.cpp), [src/runtime/reoptimization_detail.hpp](../../../../../../src/runtime/reoptimization_detail.hpp), [docs/reoptimization.md](../../../../../reoptimization.md) |

```text
bool admission_frozen=false;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Whether the actual source admission barrier is currently frozen. |
| inputs / outputs | Stores/exposes whether the actual source admission barrier is currently frozen. |
| invariants | Status/flags/digests are observations, not a verified candidate, root lock, sink receipt or permission to publish/roll back durable selection. |
| ownership | Inline fixed fields only; copying these values allocates no container or text. No source/native owner is retained. |
| failure | Assignment adds no validation; aggregate construction/copy has the ownership costs stated here. |
| cost | Fixed-size initialization/copy/comparison; declaration itself performs no runtime scan or I/O. |
| Design | [include/crown/runtime/reoptimization.hpp](../../../../../../include/crown/runtime/reoptimization.hpp), [src/runtime/reoptimization.cpp](../../../../../../src/runtime/reoptimization.cpp), [src/runtime/reoptimization_detail.hpp](../../../../../../src/runtime/reoptimization_detail.hpp), [docs/reoptimization.md](../../../../../reoptimization.md) |

```text
bool compiler_input_charged=false,publication_timings_complete=true;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Whether compiler input cost is charged and actual publication/cleanup timing is complete. |
| inputs / outputs | Stores/exposes whether compiler input cost is charged and actual publication/cleanup timing is complete. |
| invariants | Status/flags/digests are observations, not a verified candidate, root lock, sink receipt or permission to publish/roll back durable selection. |
| ownership | Inline fixed fields only; copying these values allocates no container or text. No source/native owner is retained. |
| failure | Assignment adds no validation; aggregate construction/copy has the ownership costs stated here. |
| cost | Fixed-size initialization/copy/comparison; declaration itself performs no runtime scan or I/O. |
| Design | [include/crown/runtime/reoptimization.hpp](../../../../../../include/crown/runtime/reoptimization.hpp), [src/runtime/reoptimization.cpp](../../../../../../src/runtime/reoptimization.cpp), [src/runtime/reoptimization_detail.hpp](../../../../../../src/runtime/reoptimization_detail.hpp), [docs/reoptimization.md](../../../../../reoptimization.md) |

```text
std::uint64_t source_owner=0,target_owner=0,snapshot_epoch=0,source_epoch=0,target_epoch=0,
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | The actual source/target owner IDs and snapshot/source/target physical epochs. |
| inputs / outputs | Stores/exposes the actual source/target owner IDs and snapshot/source/target physical epochs. |
| invariants | Status/flags/digests are observations, not a verified candidate, root lock, sink receipt or permission to publish/roll back durable selection. |
| ownership | Inline fixed fields only; copying these values allocates no container or text. No source/native owner is retained. |
| failure | Assignment adds no validation; aggregate construction/copy has the ownership costs stated here. |
| cost | Fixed-size initialization/copy/comparison; declaration itself performs no runtime scan or I/O. |
| Design | [include/crown/runtime/reoptimization.hpp](../../../../../../include/crown/runtime/reoptimization.hpp), [src/runtime/reoptimization.cpp](../../../../../../src/runtime/reoptimization.cpp), [src/runtime/reoptimization_detail.hpp](../../../../../../src/runtime/reoptimization_detail.hpp), [docs/reoptimization.md](../../../../../reoptimization.md) |

```text
backlog_records=0,backlog_bytes=0,peak_backlog_records=0,peak_backlog_bytes=0,
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | The current/peak native candidate backlog populations. |
| inputs / outputs | Stores/exposes the current/peak native candidate backlog populations. |
| invariants | Status/flags/digests are observations, not a verified candidate, root lock, sink receipt or permission to publish/roll back durable selection. |
| ownership | Inline fixed fields only; copying these values allocates no container or text. No source/native owner is retained. |
| failure | Assignment adds no validation; aggregate construction/copy has the ownership costs stated here. |
| cost | Fixed-size initialization/copy/comparison; declaration itself performs no runtime scan or I/O. |
| Design | [include/crown/runtime/reoptimization.hpp](../../../../../../include/crown/runtime/reoptimization.hpp), [src/runtime/reoptimization.cpp](../../../../../../src/runtime/reoptimization.cpp), [src/runtime/reoptimization_detail.hpp](../../../../../../src/runtime/reoptimization_detail.hpp), [docs/reoptimization.md](../../../../../reoptimization.md) |

```text
staged_records=0,replayed_records=0,staging_work=0,catch_up_steps=0,
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | The ledger staging/replay counts and selected staging/catch-up work. |
| inputs / outputs | Stores/exposes the ledger staging/replay counts and selected staging/catch-up work. |
| invariants | Status/flags/digests are observations, not a verified candidate, root lock, sink receipt or permission to publish/roll back durable selection. |
| ownership | Inline fixed fields only; copying these values allocates no container or text. No source/native owner is retained. |
| failure | Assignment adds no validation; aggregate construction/copy has the ownership costs stated here. |
| cost | Fixed-size initialization/copy/comparison; declaration itself performs no runtime scan or I/O. |
| Design | [include/crown/runtime/reoptimization.hpp](../../../../../../include/crown/runtime/reoptimization.hpp), [src/runtime/reoptimization.cpp](../../../../../../src/runtime/reoptimization.cpp), [src/runtime/reoptimization_detail.hpp](../../../../../../src/runtime/reoptimization_detail.hpp), [docs/reoptimization.md](../../../../../reoptimization.md) |

```text
catch_up_native_work=0,equivalence_work=0,equivalence_native_work=0,equivalence_unobserved_startups=0,
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | The native catch-up/equivalence work and unobserved cursor-startup count. |
| inputs / outputs | Stores/exposes the native catch-up/equivalence work and unobserved cursor-startup count. |
| invariants | Status/flags/digests are observations, not a verified candidate, root lock, sink receipt or permission to publish/roll back durable selection. |
| ownership | Inline fixed fields only; copying these values allocates no container or text. No source/native owner is retained. |
| failure | Assignment adds no validation; aggregate construction/copy has the ownership costs stated here. |
| cost | Fixed-size initialization/copy/comparison; declaration itself performs no runtime scan or I/O. |
| Design | [include/crown/runtime/reoptimization.hpp](../../../../../../include/crown/runtime/reoptimization.hpp), [src/runtime/reoptimization.cpp](../../../../../../src/runtime/reoptimization.cpp), [src/runtime/reoptimization_detail.hpp](../../../../../../src/runtime/reoptimization_detail.hpp), [docs/reoptimization.md](../../../../../reoptimization.md) |

```text
source_rows_compared=0,result_rows_compared=0,
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | The actual source/result rows compared at verification. |
| inputs / outputs | Stores/exposes the actual source/result rows compared at verification. |
| invariants | Status/flags/digests are observations, not a verified candidate, root lock, sink receipt or permission to publish/roll back durable selection. |
| ownership | Inline fixed fields only; copying these values allocates no container or text. No source/native owner is retained. |
| failure | Assignment adds no validation; aggregate construction/copy has the ownership costs stated here. |
| cost | Fixed-size initialization/copy/comparison; declaration itself performs no runtime scan or I/O. |
| Design | [include/crown/runtime/reoptimization.hpp](../../../../../../include/crown/runtime/reoptimization.hpp), [src/runtime/reoptimization.cpp](../../../../../../src/runtime/reoptimization.cpp), [src/runtime/reoptimization_detail.hpp](../../../../../../src/runtime/reoptimization_detail.hpp), [docs/reoptimization.md](../../../../../reoptimization.md) |

```text
lowering_work=0,build_work=0,ledger_staging_ns=0,old_drain_ns=0,clock_reads=0;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | The native replan/build work, ledger/old-owner drain times and actual clock-read count. |
| inputs / outputs | Stores/exposes the native replan/build work, ledger/old-owner drain times and actual clock-read count. |
| invariants | Status/flags/digests are observations, not a verified candidate, root lock, sink receipt or permission to publish/roll back durable selection. |
| ownership | Inline fixed fields only; copying these values allocates no container or text. No source/native owner is retained. |
| failure | Assignment adds no validation; aggregate construction/copy has the ownership costs stated here. |
| cost | Fixed-size initialization/copy/comparison; declaration itself performs no runtime scan or I/O. |
| Design | [include/crown/runtime/reoptimization.hpp](../../../../../../include/crown/runtime/reoptimization.hpp), [src/runtime/reoptimization.cpp](../../../../../../src/runtime/reoptimization.cpp), [src/runtime/reoptimization_detail.hpp](../../../../../../src/runtime/reoptimization_detail.hpp), [docs/reoptimization.md](../../../../../reoptimization.md) |

```text
std::uint64_t publication_ns=0,cleanup_ns=0;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | The actual post-barrier publication and cleanup elapsed times. |
| inputs / outputs | Stores/exposes the actual post-barrier publication and cleanup elapsed times. |
| invariants | Status/flags/digests are observations, not a verified candidate, root lock, sink receipt or permission to publish/roll back durable selection. |
| ownership | Inline fixed fields only; copying these values allocates no container or text. No source/native owner is retained. |
| failure | Assignment adds no validation; aggregate construction/copy has the ownership costs stated here. |
| cost | Fixed-size initialization/copy/comparison; declaration itself performs no runtime scan or I/O. |
| Design | [include/crown/runtime/reoptimization.hpp](../../../../../../include/crown/runtime/reoptimization.hpp), [src/runtime/reoptimization.cpp](../../../../../../src/runtime/reoptimization.cpp), [src/runtime/reoptimization_detail.hpp](../../../../../../src/runtime/reoptimization_detail.hpp), [docs/reoptimization.md](../../../../../reoptimization.md) |

```text
std::array<char,64> source_physical_sha256{},target_physical_sha256{};
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | The fixed actual source/target physical plan fingerprint bytes. |
| inputs / outputs | Stores/exposes the fixed actual source/target physical plan fingerprint bytes. |
| invariants | Status/flags/digests are observations, not a verified candidate, root lock, sink receipt or permission to publish/roll back durable selection. |
| ownership | Inline fixed fields only; copying these values allocates no container or text. No source/native owner is retained. |
| failure | Assignment adds no validation; aggregate construction/copy has the ownership costs stated here. |
| cost | Fixed-size initialization/copy/comparison; declaration itself performs no runtime scan or I/O. |
| Design | [include/crown/runtime/reoptimization.hpp](../../../../../../include/crown/runtime/reoptimization.hpp), [src/runtime/reoptimization.cpp](../../../../../../src/runtime/reoptimization.cpp), [src/runtime/reoptimization_detail.hpp](../../../../../../src/runtime/reoptimization_detail.hpp), [docs/reoptimization.md](../../../../../reoptimization.md) |

```text
PreparationCosts costs;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | The separate measured preparation-time components. |
| inputs / outputs | Stores/exposes the separate measured preparation-time components. |
| invariants | Status/flags/digests are observations, not a verified candidate, root lock, sink receipt or permission to publish/roll back durable selection. |
| ownership | Inline fixed fields only; copying these values allocates no container or text. No source/native owner is retained. |
| failure | Assignment adds no validation; aggregate construction/copy has the ownership costs stated here. |
| cost | Fixed-size initialization/copy/comparison; declaration itself performs no runtime scan or I/O. |
| Design | [include/crown/runtime/reoptimization.hpp](../../../../../../include/crown/runtime/reoptimization.hpp), [src/runtime/reoptimization.cpp](../../../../../../src/runtime/reoptimization.cpp), [src/runtime/reoptimization_detail.hpp](../../../../../../src/runtime/reoptimization_detail.hpp), [docs/reoptimization.md](../../../../../reoptimization.md) |

```text
PolicyDecision decision;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | The last pure time-policy decision. |
| inputs / outputs | Stores/exposes the last pure time-policy decision. |
| invariants | Status/flags/digests are observations, not a verified candidate, root lock, sink receipt or permission to publish/roll back durable selection. |
| ownership | Inline fixed fields only; copying these values allocates no container or text. No source/native owner is retained. |
| failure | Assignment adds no validation; aggregate construction/copy has the ownership costs stated here. |
| cost | Fixed-size initialization/copy/comparison; declaration itself performs no runtime scan or I/O. |
| Design | [include/crown/runtime/reoptimization.hpp](../../../../../../include/crown/runtime/reoptimization.hpp), [src/runtime/reoptimization.cpp](../../../../../../src/runtime/reoptimization.cpp), [src/runtime/reoptimization_detail.hpp](../../../../../../src/runtime/reoptimization_detail.hpp), [docs/reoptimization.md](../../../../../reoptimization.md) |

```text
resource::MemoryStatistics query_memory;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | The actual shared original query-account observation, including overlapping old/target work. |
| inputs / outputs | Stores/exposes the actual shared original query-account observation, including overlapping old/target work. |
| invariants | Status/flags/digests are observations, not a verified candidate, root lock, sink receipt or permission to publish/roll back durable selection. |
| ownership | Inline fixed fields only; copying these values allocates no container or text. No source/native owner is retained. |
| failure | Assignment adds no validation; aggregate construction/copy has the ownership costs stated here. |
| cost | Fixed-size initialization/copy/comparison; declaration itself performs no runtime scan or I/O. |
| Design | [include/crown/runtime/reoptimization.hpp](../../../../../../include/crown/runtime/reoptimization.hpp), [src/runtime/reoptimization.cpp](../../../../../../src/runtime/reoptimization.cpp), [src/runtime/reoptimization_detail.hpp](../../../../../../src/runtime/reoptimization_detail.hpp), [docs/reoptimization.md](../../../../../reoptimization.md) |

```text
resource::MemoryStatistics compiler_input_memory;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | The separate explicit compiler-input account observation, not total process memory. |
| inputs / outputs | Stores/exposes the separate explicit compiler-input account observation, not total process memory. |
| invariants | Status/flags/digests are observations, not a verified candidate, root lock, sink receipt or permission to publish/roll back durable selection. |
| ownership | Inline fixed fields only; copying these values allocates no container or text. No source/native owner is retained. |
| failure | Assignment adds no validation; aggregate construction/copy has the ownership costs stated here. |
| cost | Fixed-size initialization/copy/comparison; declaration itself performs no runtime scan or I/O. |
| Design | [include/crown/runtime/reoptimization.hpp](../../../../../../include/crown/runtime/reoptimization.hpp), [src/runtime/reoptimization.cpp](../../../../../../src/runtime/reoptimization.cpp), [src/runtime/reoptimization_detail.hpp](../../../../../../src/runtime/reoptimization_detail.hpp), [docs/reoptimization.md](../../../../../reoptimization.md) |

## B0015

[Lines 86–86](../../../../../../include/crown/runtime/reoptimization.hpp#L86); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L86-L86:sha256:b78bb8a78e54fdcad7975679024418192f59bdaee1c0f4338c5913daa8e3b818
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Close the \`namespace crown::runtime::reoptimization\` scope at this exact source boundary. |
| inputs / outputs | This token introduces no callable inputs or outputs. Declarations inside \`namespace crown::runtime::reoptimization\` define the available names, members and operations. |
| invariants | The closing brace matches the opening \`namespace crown::runtime::reoptimization\` at its lexical source position in include/crown/runtime/reoptimization.hpp; it preserves C++ namespace/type nesting. |
| ownership | The closing delimiter creates no owner. Types closed by \`namespace crown::runtime::reoptimization\` retain the lifetimes and allocator rules of their own fields and operations. |
| failure | No failure path executes at this closing delimiter. Failure and cleanup behavior belong to enclosed functions and owning types. |
| cost | The delimiter itself performs no runtime work; the enclosed initializers, methods and destructors carry their own costs. |
| Design | [docs/selection.md](../../../../../selection.md), [docs/selection_binding.md](../../../../../selection_binding.md), [docs/selection_accounting.md](../../../../../selection_accounting.md), [docs/reoptimization.md](../../../../../reoptimization.md), [docs/code_specs/subsystem_contracts.md](../../../../subsystem_contracts.md) |
