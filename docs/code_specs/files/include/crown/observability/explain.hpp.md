# `include/crown/observability/explain.hpp` — block usage map

[Source](../../../../../../include/crown/observability/explain.hpp) · [Source index](../../../../README.md) · [Subsystem contracts](../../../../subsystem_contracts.md) · [Reviewed primitives](../../../../primitives.md)

Capture bounded distributions, workload counters, owner memory and explain observations without mislabeling partial information as exact.

Snapshot SHA-256: `da1bf6e77d9afef5608d67ebbd3fd320973e8286870ff4784c25e79d524c69e8`. 85 lines partitioned into 11 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [statistics](../../../../subsystem_contracts.md#statistics). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/statistics.md](../../../../../statistics.md), [docs/observability.md](../../../../../observability.md), [docs/memory_reports.md](../../../../../memory_reports.md), [docs/ranking_evaluation.md](../../../../../ranking_evaluation.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–9](../../../../../../include/crown/observability/explain.hpp#L1) | Imports dependencies; guards repeated header inclusion; declares namespace scope; declares types or opens a type body. |  · [reviewed contract](#b0001) |
| [B0002 · 10–10](../../../../../../include/crown/observability/explain.hpp#L10) | Type/record definition: enum class RuntimePresence |  · [reviewed contract](#b0002) |
| [B0003 · 11–11](../../../../../../include/crown/observability/explain.hpp#L11) | Type/record definition: enum class ExplanationKind |  · [reviewed contract](#b0003) |
| [B0004 · 12–12](../../../../../../include/crown/observability/explain.hpp#L12) | Type/record definition: enum class GaugeAvailability |  · [reviewed contract](#b0004) |
| [B0005 · 13–15](../../../../../../include/crown/observability/explain.hpp#L13) | Explanatory comments or spacing. | source comment (unverified): // Current/retained owner configuration is separate from immutable begin-bound · [reviewed contract](#b0005) |
| [B0006 · 16–37](../../../../../../include/crown/observability/explain.hpp#L16) | Type/record definition: class ModeDescriptor | source comment (unverified): // Current/retained owner configuration is separate from immutable begin-bound · [reviewed contract](#b0006) |
| [B0007 · 38–39](../../../../../../include/crown/observability/explain.hpp#L38) | declares aliases; declares values/defaults or compile-time conditions. |  · [reviewed contract](#b0007) |
| [B0008 · 40–40](../../../../../../include/crown/observability/explain.hpp#L40) | Type/record definition: enum class HeightStatus |  · [reviewed contract](#b0008) |
| [B0009 · 41–43](../../../../../../include/crown/observability/explain.hpp#L41) | Type/record definition: struct ExplainLimits |  · [reviewed contract](#b0009) |
| [B0010 · 44–79](../../../../../../include/crown/observability/explain.hpp#L44) | declares types or opens a type body; declares callable signatures; declares values/defaults or compile-time conditions. | source comment (unverified): // Admission uses exact native Catalog/Query comparison, never JSON, a digest, · [reviewed contract](#b0010) |
| [B0011 · 80–85](../../../../../../include/crown/observability/explain.hpp#L80) | declares callable signatures; declares values/defaults or compile-time conditions. | source comment (unverified): // namespace crown::observability · [reviewed contract](#b0011) |

## B0001

[Lines 1–9](../../../../../../include/crown/observability/explain.hpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
#pragma once
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Declare the observability explain public interface and its required types. |
| inputs / outputs | Header imports its explicit dependencies and declares the APIs/contracts below. |
| invariants | Inclusion does not construct a live query, source, report, proof or file owner. |
| ownership | Declarations retain no instance; object ownership and copies are specified at the individual APIs. |
| failure | Compile-time dependency/declaration boundary; runtime failures belong to instantiated objects/operations. |
| cost | No runtime action from inclusion itself; inline methods retain their stated actual costs. |
| Design | [include/crown/observability/explain.hpp](../../../../../../include/crown/observability/explain.hpp), [src/observability/explain.cpp](../../../../../../src/observability/explain.cpp), [docs/observability.md](../../../../../observability.md) |

## B0002

[Lines 10–10](../../../../../../include/crown/observability/explain.hpp#L10); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
enum class RuntimePresence {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Describe retained runtime lifecycle separately from running metadata. |
| inputs / outputs | Compile-only, live, stopped with state retained, or runtime state released; report still retains immutable program metadata. |
| invariants | Public value/configuration only; changing fields does not perform admission, execute an input or create proof authority. |
| ownership | Inline fixed fields only; copying these values allocates no container or text. No source/native owner is retained. |
| failure | Declaration/field initialization performs no semantic validation. Consumers validate the actual values at their own boundary. |
| cost | Fixed-size initialization/copy/comparison; declaration itself performs no runtime scan or I/O. |
| Design | [include/crown/observability/explain.hpp](../../../../../../include/crown/observability/explain.hpp), [src/observability/explain.cpp](../../../../../../src/observability/explain.cpp), [docs/observability.md](../../../../../observability.md) |

## B0003

[Lines 11–11](../../../../../../include/crown/observability/explain.hpp#L11); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
enum class ExplanationKind {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Name physical-plan, runtime or session report origin. |
| inputs / outputs | Presentation kind captured by closed factories, not a native state/proof capability. |
| invariants | Public value/configuration only; changing fields does not perform admission, execute an input or create proof authority. |
| ownership | Inline fixed fields only; copying these values allocates no container or text. No source/native owner is retained. |
| failure | Declaration/field initialization performs no semantic validation. Consumers validate the actual values at their own boundary. |
| cost | Fixed-size initialization/copy/comparison; declaration itself performs no runtime scan or I/O. |
| Design | [include/crown/observability/explain.hpp](../../../../../../include/crown/observability/explain.hpp), [src/observability/explain.cpp](../../../../../../src/observability/explain.cpp), [docs/observability.md](../../../../../observability.md) |

## B0004

[Lines 12–12](../../../../../../include/crown/observability/explain.hpp#L12); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
enum class GaugeAvailability {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Explain why committed gauges are present or absent. |
| inputs / outputs | Available, compile-only, pending private state or released runtime; absence is not zero population. |
| invariants | Public value/configuration only; changing fields does not perform admission, execute an input or create proof authority. |
| ownership | Inline fixed fields only; copying these values allocates no container or text. No source/native owner is retained. |
| failure | Declaration/field initialization performs no semantic validation. Consumers validate the actual values at their own boundary. |
| cost | Fixed-size initialization/copy/comparison; declaration itself performs no runtime scan or I/O. |
| Design | [include/crown/observability/explain.hpp](../../../../../../include/crown/observability/explain.hpp), [src/observability/explain.cpp](../../../../../../src/observability/explain.cpp), [docs/observability.md](../../../../../observability.md) |

## B0005

[Lines 13–15](../../../../../../include/crown/observability/explain.hpp#L13); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L13-L15:sha256:3b94c85e625e55be51a6f3bd5797118a68268f18834aad2692de5140b8a13a5b
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Design note for adjacent code: Current/retained owner configuration is separate from immutable begin-bound attempt configuration. No arbitrary public metadata constructor exists. running() means retained native state; presence() distinguishes stopped state. This is caller guidance recorded as prose, not an executable result. |
| inputs / outputs | No runtime interface is implemented by these comment-only lines. They sit at include/crown/observability/explain.hpp lines 11-17; the surrounding declaration/body defines its own inputs and outputs. |
| invariants | The words record the intended use boundary only. They do not add a guard, proof, capability, transaction, durability guarantee, or account charge; verify behavior in the referenced implementation. |
| ownership | Comment text owns no data. Object lifetimes, borrows, and account attribution remain those of the adjacent source objects and their constructors. |
| failure | No failure path is implemented here. Any mentioned failure or recovery rule belongs to the adjacent operation and its existing error carrier. |
| cost | No runtime work is performed by these lines; any cost/bound in the note is not certified by this comment-only card. |
| Design | [include/crown/observability/explain.hpp](../../../../../../include/crown/observability/explain.hpp), [docs/code_specs/files/include/crown/observability/explain.hpp.md](explain.hpp.md), [docs/observability.md](../../../../../observability.md), [docs/statistics.md](../../../../../statistics.md) |

## B0006

[Lines 16–37](../../../../../../include/crown/observability/explain.hpp#L16); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
class ModeDescriptor
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Own an actual compile/runtime/session mode description. |
| inputs / outputs | Factory-only report of actual retained plan/configuration, owner/sequence/state and lifecycle presence. |
| invariants | Current/retained configuration is independent of immutable begin-bound observation attempt configuration. No arbitrary public metadata constructor. |
| ownership | Shared immutable accounted Data retains CompiledProgram and fixed options/profile metadata; it never retains a mutable runtime/session pointer. Returned references borrow Data. Ordinary copies share; implicit move can empty the source; last release can destroy retained metadata. |
| failure | Factory allocation/owner/moved-from errors propagate; accessors use checked data(), not fabricated values. |
| cost | Funded report control plus retained program handles; physical DTO compile-only path first freezes complete metadata into a standalone account. |
| Design | [include/crown/observability/explain.hpp](../../../../../../include/crown/observability/explain.hpp), [src/observability/explain.cpp](../../../../../../src/observability/explain.cpp), [docs/observability.md](../../../../../observability.md) |

```text
static ModeDescriptor compile_only(PhysicalPlan);
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Create an actual-origin ModeDescriptor. |
| inputs / outputs | Freeze compiler DTO into standalone native metadata and retain compile-only mode. |
| invariants | Uses explicit UINT64_MAX standalone account/work grant; no live query or runtime state is created. |
| ownership | Shared immutable accounted Data retains CompiledProgram and fixed options/profile metadata; it never retains a mutable runtime/session pointer. Returned references borrow Data. Ordinary copies share; implicit move can empty the source; last release can destroy retained metadata. |
| failure | Moved-from source/guard/allocation errors propagate before a result. |
| cost | Full native metadata freeze/copy and funded report Data. |
| Design | [include/crown/observability/explain.hpp](../../../../../../include/crown/observability/explain.hpp), [src/observability/explain.cpp](../../../../../../src/observability/explain.cpp), [docs/observability.md](../../../../../observability.md) |

```text
static ModeDescriptor compile_only(runtime::CompiledProgram);
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Create an actual-origin ModeDescriptor. |
| inputs / outputs | Retain supplied admitted immutable native program as compile-only mode. |
| invariants | Shares its actual account/program instead of importing a new query grant. |
| ownership | Shared immutable accounted Data retains CompiledProgram and fixed options/profile metadata; it never retains a mutable runtime/session pointer. Returned references borrow Data. Ordinary copies share; implicit move can empty the source; last release can destroy retained metadata. |
| failure | Moved-from source/guard/allocation errors propagate before a result. |
| cost | Funded fixed Data and retained program descriptor, no ordinary DTO export. |
| Design | [include/crown/observability/explain.hpp](../../../../../../include/crown/observability/explain.hpp), [src/observability/explain.cpp](../../../../../../src/observability/explain.cpp), [docs/observability.md](../../../../../observability.md) |

```text
static ModeDescriptor capture(const runtime::DeltaRuntime&);
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Create an actual-origin ModeDescriptor. |
| inputs / outputs | Read actual runtime owner/sequence/state/options/profile and retain its native program. |
| invariants | Caller preserves the native exclusive synchronous access contract; no mutable owner pointer remains. |
| ownership | Shared immutable accounted Data retains CompiledProgram and fixed options/profile metadata; it never retains a mutable runtime/session pointer. Returned references borrow Data. Ordinary copies share; implicit move can empty the source; last release can destroy retained metadata. |
| failure | Moved-from source/guard/allocation errors propagate before a result. |
| cost | Funded fixed Data plus program/configuration handle/value copies. |
| Design | [include/crown/observability/explain.hpp](../../../../../../include/crown/observability/explain.hpp), [src/observability/explain.cpp](../../../../../../src/observability/explain.cpp), [docs/observability.md](../../../../../observability.md) |

```text
static ModeDescriptor capture(const runtime::QuerySession&);
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Create an actual-origin ModeDescriptor. |
| inputs / outputs | Capture actual session report metadata and lifecycle status. |
| invariants | A stopped session can retain native state; running() and presence() intentionally differ. |
| ownership | Shared immutable accounted Data retains CompiledProgram and fixed options/profile metadata; it never retains a mutable runtime/session pointer. Returned references borrow Data. Ordinary copies share; implicit move can empty the source; last release can destroy retained metadata. |
| failure | Moved-from source/guard/allocation errors propagate before a result. |
| cost | Session guarded metadata/status reads plus funded fixed Data/program retention. |
| Design | [include/crown/observability/explain.hpp](../../../../../../include/crown/observability/explain.hpp), [src/observability/explain.cpp](../../../../../../src/observability/explain.cpp), [docs/observability.md](../../../../../observability.md) |

```text
const runtime::CompiledProgram& plan() const;
  [[nodiscard]] bool running() const;

```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Borrow the actual retained native program. |
| inputs / outputs | Returns Data plan handle by reference. |
| invariants | Mutable data alone never authorizes source acceptance, native plan execution, proof, output acknowledgment or durable publication. |
| ownership | Shared immutable accounted Data retains CompiledProgram and fixed options/profile metadata; it never retains a mutable runtime/session pointer. Returned references borrow Data. Ordinary copies share; implicit move can empty the source; last release can destroy retained metadata. |
| failure | data() rejects a moved-from descriptor with invalid_explanation. |
| cost | Fixed checked Data/reference/value access; copying the retained program is explicit. |
| Design | [include/crown/observability/explain.hpp](../../../../../../include/crown/observability/explain.hpp), [src/observability/explain.cpp](../../../../../../src/observability/explain.cpp), [docs/observability.md](../../../../../observability.md) |

```text
bool running() const;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Test whether native state is retained. |
| inputs / outputs | True may include stopped-retained session; not a scheduler-running flag. |
| invariants | Mutable data alone never authorizes source acceptance, native plan execution, proof, output acknowledgment or durable publication. |
| ownership | Shared immutable accounted Data retains CompiledProgram and fixed options/profile metadata; it never retains a mutable runtime/session pointer. Returned references borrow Data. Ordinary copies share; implicit move can empty the source; last release can destroy retained metadata. |
| failure | data() rejects a moved-from descriptor with invalid_explanation. |
| cost | Fixed checked Data/reference/value access; copying the retained program is explicit. |
| Design | [include/crown/observability/explain.hpp](../../../../../../include/crown/observability/explain.hpp), [src/observability/explain.cpp](../../../../../../src/observability/explain.cpp), [docs/observability.md](../../../../../observability.md) |

```text
std::uint64_t owner() const;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Read the captured native owner ID. |
| inputs / outputs | Compile-only has no live owner; runtime/session captures keep their actual ID. |
| invariants | Mutable data alone never authorizes source acceptance, native plan execution, proof, output acknowledgment or durable publication. |
| ownership | Shared immutable accounted Data retains CompiledProgram and fixed options/profile metadata; it never retains a mutable runtime/session pointer. Returned references borrow Data. Ordinary copies share; implicit move can empty the source; last release can destroy retained metadata. |
| failure | data() rejects a moved-from descriptor with invalid_explanation. |
| cost | Fixed checked Data/reference/value access; copying the retained program is explicit. |
| Design | [include/crown/observability/explain.hpp](../../../../../../include/crown/observability/explain.hpp), [src/observability/explain.cpp](../../../../../../src/observability/explain.cpp), [docs/observability.md](../../../../../observability.md) |

```text
std::uint64_t sequence() const;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Read the captured native committed sequence. |
| inputs / outputs | Fixed recorded boundary, not input acceptance performed now. |
| invariants | Mutable data alone never authorizes source acceptance, native plan execution, proof, output acknowledgment or durable publication. |
| ownership | Shared immutable accounted Data retains CompiledProgram and fixed options/profile metadata; it never retains a mutable runtime/session pointer. Returned references borrow Data. Ordinary copies share; implicit move can empty the source; last release can destroy retained metadata. |
| failure | data() rejects a moved-from descriptor with invalid_explanation. |
| cost | Fixed checked Data/reference/value access; copying the retained program is explicit. |
| Design | [include/crown/observability/explain.hpp](../../../../../../include/crown/observability/explain.hpp), [src/observability/explain.cpp](../../../../../../src/observability/explain.cpp), [docs/observability.md](../../../../../observability.md) |

```text
std::optional<runtime::DeltaState> state() const;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Read retained runtime state if any. |
| inputs / outputs | Absent for compile-only/released state. |
| invariants | Mutable data alone never authorizes source acceptance, native plan execution, proof, output acknowledgment or durable publication. |
| ownership | Shared immutable accounted Data retains CompiledProgram and fixed options/profile metadata; it never retains a mutable runtime/session pointer. Returned references borrow Data. Ordinary copies share; implicit move can empty the source; last release can destroy retained metadata. |
| failure | data() rejects a moved-from descriptor with invalid_explanation. |
| cost | Fixed checked Data/reference/value access; copying the retained program is explicit. |
| Design | [include/crown/observability/explain.hpp](../../../../../../include/crown/observability/explain.hpp), [src/observability/explain.cpp](../../../../../../src/observability/explain.cpp), [docs/observability.md](../../../../../observability.md) |

```text
RuntimePresence presence() const;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Read actual lifecycle presence. |
| inputs / outputs | Distinguishes compile-only/live/stopped-retained/released. |
| invariants | Mutable data alone never authorizes source acceptance, native plan execution, proof, output acknowledgment or durable publication. |
| ownership | Shared immutable accounted Data retains CompiledProgram and fixed options/profile metadata; it never retains a mutable runtime/session pointer. Returned references borrow Data. Ordinary copies share; implicit move can empty the source; last release can destroy retained metadata. |
| failure | data() rejects a moved-from descriptor with invalid_explanation. |
| cost | Fixed checked Data/reference/value access; copying the retained program is explicit. |
| Design | [include/crown/observability/explain.hpp](../../../../../../include/crown/observability/explain.hpp), [src/observability/explain.cpp](../../../../../../src/observability/explain.cpp), [docs/observability.md](../../../../../observability.md) |

```text
const std::optional<runtime::DeltaOptions>& options() const;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Borrow captured actual runtime options. |
| inputs / outputs | No begin-attempt inference or caller-supplied override. |
| invariants | Mutable data alone never authorizes source acceptance, native plan execution, proof, output acknowledgment or durable publication. |
| ownership | Shared immutable accounted Data retains CompiledProgram and fixed options/profile metadata; it never retains a mutable runtime/session pointer. Returned references borrow Data. Ordinary copies share; implicit move can empty the source; last release can destroy retained metadata. |
| failure | data() rejects a moved-from descriptor with invalid_explanation. |
| cost | Fixed checked Data/reference/value access; copying the retained program is explicit. |
| Design | [include/crown/observability/explain.hpp](../../../../../../include/crown/observability/explain.hpp), [src/observability/explain.cpp](../../../../../../src/observability/explain.cpp), [docs/observability.md](../../../../../observability.md) |

```text
const std::optional<runtime::DeltaRuntimeProfile>& profile() const;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Borrow captured resolved runtime profile. |
| inputs / outputs | Retained descriptive actual mode/backend/configuration. |
| invariants | Mutable data alone never authorizes source acceptance, native plan execution, proof, output acknowledgment or durable publication. |
| ownership | Shared immutable accounted Data retains CompiledProgram and fixed options/profile metadata; it never retains a mutable runtime/session pointer. Returned references borrow Data. Ordinary copies share; implicit move can empty the source; last release can destroy retained metadata. |
| failure | data() rejects a moved-from descriptor with invalid_explanation. |
| cost | Fixed checked Data/reference/value access; copying the retained program is explicit. |
| Design | [include/crown/observability/explain.hpp](../../../../../../include/crown/observability/explain.hpp), [src/observability/explain.cpp](../../../../../../src/observability/explain.cpp), [docs/observability.md](../../../../../observability.md) |

```text
struct Data;
  explicit ModeDescriptor(std::shared_ptr<const Data>);

```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Hide immutable mode-report state. |
| inputs / outputs | Private closed factory/helper/member storage. |
| invariants | No public constructor accepts arbitrary ownership IDs/options/flags. |
| ownership | Shared immutable accounted Data retains CompiledProgram and fixed options/profile metadata; it never retains a mutable runtime/session pointer. Returned references borrow Data. Ordinary copies share; implicit move can empty the source; last release can destroy retained metadata. |
| failure | Helper/factory may reject invalid access or allocation; declarations add no handler. |
| cost | Fixed descriptor/helper work except funded factory allocation and final retained graph release. |
| Design | [include/crown/observability/explain.hpp](../../../../../../include/crown/observability/explain.hpp), [src/observability/explain.cpp](../../../../../../src/observability/explain.cpp), [docs/observability.md](../../../../../observability.md) |

```text
explicit ModeDescriptor(std::shared_ptr<const Data>);
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Publish a prepared immutable mode-report owner. |
| inputs / outputs | Private closed factory/helper/member storage. |
| invariants | No public constructor accepts arbitrary ownership IDs/options/flags. |
| ownership | Shared immutable accounted Data retains CompiledProgram and fixed options/profile metadata; it never retains a mutable runtime/session pointer. Returned references borrow Data. Ordinary copies share; implicit move can empty the source; last release can destroy retained metadata. |
| failure | Helper/factory may reject invalid access or allocation; declarations add no handler. |
| cost | Fixed descriptor/helper work except funded factory allocation and final retained graph release. |
| Design | [include/crown/observability/explain.hpp](../../../../../../include/crown/observability/explain.hpp), [src/observability/explain.cpp](../../../../../../src/observability/explain.cpp), [docs/observability.md](../../../../../observability.md) |

```text
friend class StatisticsExplanation;
  [[nodiscard]] static ModeDescriptor from_session(const runtime::SessionReportMetadata&,const runtime::SessionStatus&);

```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Permit actual statistics context to construct mode metadata. |
| inputs / outputs | Private closed factory/helper/member storage. |
| invariants | No public constructor accepts arbitrary ownership IDs/options/flags. |
| ownership | Shared immutable accounted Data retains CompiledProgram and fixed options/profile metadata; it never retains a mutable runtime/session pointer. Returned references borrow Data. Ordinary copies share; implicit move can empty the source; last release can destroy retained metadata. |
| failure | Helper/factory may reject invalid access or allocation; declarations add no handler. |
| cost | Fixed descriptor/helper work except funded factory allocation and final retained graph release. |
| Design | [include/crown/observability/explain.hpp](../../../../../../include/crown/observability/explain.hpp), [src/observability/explain.cpp](../../../../../../src/observability/explain.cpp), [docs/observability.md](../../../../../observability.md) |

```text
static ModeDescriptor from_session(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Construct mode from genuine session report metadata/status. |
| inputs / outputs | Private closed factory/helper/member storage. |
| invariants | No public constructor accepts arbitrary ownership IDs/options/flags. |
| ownership | Shared immutable accounted Data retains CompiledProgram and fixed options/profile metadata; it never retains a mutable runtime/session pointer. Returned references borrow Data. Ordinary copies share; implicit move can empty the source; last release can destroy retained metadata. |
| failure | Helper/factory may reject invalid access or allocation; declarations add no handler. |
| cost | Fixed descriptor/helper work except funded factory allocation and final retained graph release. |
| Design | [include/crown/observability/explain.hpp](../../../../../../include/crown/observability/explain.hpp), [src/observability/explain.cpp](../../../../../../src/observability/explain.cpp), [docs/observability.md](../../../../../observability.md) |

```text
const Data& data() const;
  std::shared_ptr<const Data> data_;
};
using HeightEvidence=std::variant<std::monostate,planner::ValidatedIncumbent,

```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Reject empty moved-from mode-report access. |
| inputs / outputs | Private closed factory/helper/member storage. |
| invariants | No public constructor accepts arbitrary ownership IDs/options/flags. |
| ownership | Shared immutable accounted Data retains CompiledProgram and fixed options/profile metadata; it never retains a mutable runtime/session pointer. Returned references borrow Data. Ordinary copies share; implicit move can empty the source; last release can destroy retained metadata. |
| failure | Helper/factory may reject invalid access or allocation; declarations add no handler. |
| cost | Fixed descriptor/helper work except funded factory allocation and final retained graph release. |
| Design | [include/crown/observability/explain.hpp](../../../../../../include/crown/observability/explain.hpp), [src/observability/explain.cpp](../../../../../../src/observability/explain.cpp), [docs/observability.md](../../../../../observability.md) |

```text
std::shared_ptr<const Data> data_;
};
using HeightEvidence=std::variant<std::monostate,planner::ValidatedIncumbent,

```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Retain the immutable mode/program/configuration graph. |
| inputs / outputs | Private closed factory/helper/member storage. |
| invariants | No public constructor accepts arbitrary ownership IDs/options/flags. |
| ownership | Shared immutable accounted Data retains CompiledProgram and fixed options/profile metadata; it never retains a mutable runtime/session pointer. Returned references borrow Data. Ordinary copies share; implicit move can empty the source; last release can destroy retained metadata. |
| failure | Helper/factory may reject invalid access or allocation; declarations add no handler. |
| cost | Fixed descriptor/helper work except funded factory allocation and final retained graph release. |
| Design | [include/crown/observability/explain.hpp](../../../../../../include/crown/observability/explain.hpp), [src/observability/explain.cpp](../../../../../../src/observability/explain.cpp), [docs/observability.md](../../../../../observability.md) |

## B0007

[Lines 38–39](../../../../../../include/crown/observability/explain.hpp#L38); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
using HeightEvidence=
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Carry existing typed original height evidence. |
| inputs / outputs | monostate, checked upper witness, verified optimum, or checked minimum-height candidate. |
| invariants | Variants preserve their existing exact binding/proof scope; no editable certificate/height flag is accepted. |
| ownership | Typed immutable handles retain their original graphs; copying handles does not rerun proof. |
| failure | Type declaration adds no handler; factory rejects invalid/mismatched handles. |
| cost | Fixed variant/handle storage and reference operations; final underlying graph release can be substantial. |
| Design | [include/crown/observability/explain.hpp](../../../../../../include/crown/observability/explain.hpp), [src/observability/explain.cpp](../../../../../../src/observability/explain.cpp), [docs/observability.md](../../../../../observability.md) |

## B0008

[Lines 40–40](../../../../../../include/crown/observability/explain.hpp#L40); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
enum class HeightStatus {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Present the scope of height evidence actually admitted. |
| inputs / outputs | Checked upper, verified original minimum or checked constant operator; these are distinct guarantees. |
| invariants | Public value/configuration only; changing fields does not perform admission, execute an input or create proof authority. |
| ownership | Inline fixed fields only; copying these values allocates no container or text. No source/native owner is retained. |
| failure | Declaration/field initialization performs no semantic validation. Consumers validate the actual values at their own boundary. |
| cost | Fixed-size initialization/copy/comparison; declaration itself performs no runtime scan or I/O. |
| Design | [include/crown/observability/explain.hpp](../../../../../../include/crown/observability/explain.hpp), [src/observability/explain.cpp](../../../../../../src/observability/explain.cpp), [docs/observability.md](../../../../../observability.md) |

## B0009

[Lines 41–43](../../../../../../include/crown/observability/explain.hpp#L41); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct ExplainLimits {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Bound selected/original witness structure in report admission. |
| inputs / outputs | Default100,000 nodes; limits checked by PlanExplanation::make. |
| invariants | Count cap does not bound all prior freeze/trace/gauge allocation or full retained metadata bytes. |
| ownership | Inline fixed fields only; copying these values allocates no container or text. No source/native owner is retained. |
| failure | Declaration/field initialization performs no semantic validation. Consumers validate the actual values at their own boundary. |
| cost | Fixed-size initialization/copy/comparison; declaration itself performs no runtime scan or I/O. |
| Design | [include/crown/observability/explain.hpp](../../../../../../include/crown/observability/explain.hpp), [src/observability/explain.cpp](../../../../../../src/observability/explain.cpp), [docs/observability.md](../../../../../observability.md) |

```text
std::size_t nodes=100000;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | The selected tree and original witness node-count cap. |
| inputs / outputs | Stores/exposes the selected tree and original witness node-count cap. |
| invariants | Count cap does not bound all prior freeze/trace/gauge allocation or full retained metadata bytes. |
| ownership | Inline fixed fields only; copying these values allocates no container or text. No source/native owner is retained. |
| failure | Assignment adds no validation; aggregate construction/copy has the ownership costs stated here. |
| cost | Fixed-size initialization/copy/comparison; declaration itself performs no runtime scan or I/O. |
| Design | [include/crown/observability/explain.hpp](../../../../../../include/crown/observability/explain.hpp), [src/observability/explain.cpp](../../../../../../src/observability/explain.cpp), [docs/observability.md](../../../../../observability.md) |

## B0010

[Lines 44–79](../../../../../../include/crown/observability/explain.hpp#L44); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
class PlanExplanation
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Own a typed plan/runtime/session explanation with explicit evidence scope. |
| inputs / outputs | Closed factories join an admitted immutable program with exact original-bound typed evidence and actual captured context. |
| invariants | Exact Catalog/Query/tree comparisons and candidate policy checks establish report binding; digest, alpha-equivalence or editable flags do not. Original optimum witness can differ from selected tree. |
| ownership | Shared immutable report Data retains actual ModeDescriptor/program, typed evidence/family, funded captured trace/gauges and fixed metadata. It retains no mutable native owner; returned references borrow this report. Default copies share; implicit moved-from objects reject checked access. |
| failure | Moved/invalid/binding/context/node-limit/legacy-statistics-version/allocation errors propagate before a returned report. |
| cost | Full binding/tree comparisons and funded report/context retention. Runtime capture may first allocate/copy trace and node/base-table gauges before final node-limit check. |
| Design | [include/crown/observability/explain.hpp](../../../../../../include/crown/observability/explain.hpp), [src/observability/explain.cpp](../../../../../../src/observability/explain.cpp), [docs/observability.md](../../../../../observability.md) |

```text
static PlanExplanation create(PhysicalPlan,
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Create or capture a PlanExplanation. |
| inputs / outputs | Create compile-only report from compiler DTO plus optional typed evidence/family. |
| invariants | Freezes native program before report binding/count checks; creates no live runtime. |
| ownership | Shared immutable report Data retains actual ModeDescriptor/program, typed evidence/family, funded captured trace/gauges and fixed metadata. It retains no mutable native owner; returned references borrow this report. Default copies share; implicit moved-from objects reject checked access. |
| failure | Source/guard/evidence/context/legacy-version/limit/allocation errors propagate; native source/progress is not advanced. |
| cost | Full native metadata freeze then exact binding/tree checks and funded report Data. |
| Design | [include/crown/observability/explain.hpp](../../../../../../include/crown/observability/explain.hpp), [src/observability/explain.cpp](../../../../../../src/observability/explain.cpp), [docs/observability.md](../../../../../observability.md) |

```text
static PlanExplanation create(runtime::CompiledProgram,
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Create or capture a PlanExplanation. |
| inputs / outputs | Create compile-only report sharing an admitted native program. |
| invariants | Uses its actual original account and immutable plan; no ordinary serialization required. |
| ownership | Shared immutable report Data retains actual ModeDescriptor/program, typed evidence/family, funded captured trace/gauges and fixed metadata. It retains no mutable native owner; returned references borrow this report. Default copies share; implicit moved-from objects reject checked access. |
| failure | Source/guard/evidence/context/legacy-version/limit/allocation errors propagate; native source/progress is not advanced. |
| cost | Fixed mode/report Data funding plus full evidence/binding/tree comparisons. |
| Design | [include/crown/observability/explain.hpp](../../../../../../include/crown/observability/explain.hpp), [src/observability/explain.cpp](../../../../../../src/observability/explain.cpp), [docs/observability.md](../../../../../observability.md) |

```text
static PlanExplanation capture(const runtime::DeltaRuntime&
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Create or capture a PlanExplanation. |
| inputs / outputs | Capture actual runtime mode, observation trace, gauges/cursor and optional typed height/family. |
| invariants | Legacy v2 rejects enabled C01 workload collection; pending private state suppresses committed gauges. Capture is an exclusive caller read. |
| ownership | Shared immutable report Data retains actual ModeDescriptor/program, typed evidence/family, funded captured trace/gauges and fixed metadata. It retains no mutable native owner; returned references borrow this report. Default copies share; implicit moved-from objects reject checked access. |
| failure | Source/guard/evidence/context/legacy-version/limit/allocation errors propagate; native source/progress is not advanced. |
| cost | Funded trace and node/base-table gauge arrays (not resident row traversal), then exact report admission and Data allocation. |
| Design | [include/crown/observability/explain.hpp](../../../../../../include/crown/observability/explain.hpp), [src/observability/explain.cpp](../../../../../../src/observability/explain.cpp), [docs/observability.md](../../../../../observability.md) |

```text
static PlanExplanation capture(const runtime::QuerySession&
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Create or capture a PlanExplanation. |
| inputs / outputs | Capture actual session typed plan, mode/status, trace/gauges/cursor and optional evidence. |
| invariants | Session uses its own retained typed plan, not a caller hash/supplied-plan join; released/pending gauge availability remains explicit. |
| ownership | Shared immutable report Data retains actual ModeDescriptor/program, typed evidence/family, funded captured trace/gauges and fixed metadata. It retains no mutable native owner; returned references borrow this report. Default copies share; implicit moved-from objects reject checked access. |
| failure | Source/guard/evidence/context/legacy-version/limit/allocation errors propagate; native source/progress is not advanced. |
| cost | Guarded session metadata/trace/gauge reads plus native report allocation and binding/count checks. |
| Design | [include/crown/observability/explain.hpp](../../../../../../include/crown/observability/explain.hpp), [src/observability/explain.cpp](../../../../../../src/observability/explain.cpp), [docs/observability.md](../../../../../observability.md) |

```text
const runtime::CompiledProgram& plan() const;
  [[nodiscard]] ExplanationKind kind() const;

```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Borrow the actual selected native program. |
| inputs / outputs | Returns the mode-retained admitted program. |
| invariants | Mutable data alone never authorizes source acceptance, native plan execution, proof, output acknowledgment or durable publication. |
| ownership | Shared immutable report Data retains actual ModeDescriptor/program, typed evidence/family, funded captured trace/gauges and fixed metadata. It retains no mutable native owner; returned references borrow this report. Default copies share; implicit moved-from objects reject checked access. |
| failure | Checked data() rejects moved-from report; typed handle access keeps its existing validity contract. |
| cost | Fixed Data/access or shared optimum-handle copy, no row scan/capture/serialization. |
| Design | [include/crown/observability/explain.hpp](../../../../../../include/crown/observability/explain.hpp), [src/observability/explain.cpp](../../../../../../src/observability/explain.cpp), [docs/observability.md](../../../../../observability.md) |

```text
ExplanationKind kind() const;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Read explanation origin. |
| inputs / outputs | Physical compile, runtime or session. |
| invariants | Mutable data alone never authorizes source acceptance, native plan execution, proof, output acknowledgment or durable publication. |
| ownership | Shared immutable report Data retains actual ModeDescriptor/program, typed evidence/family, funded captured trace/gauges and fixed metadata. It retains no mutable native owner; returned references borrow this report. Default copies share; implicit moved-from objects reject checked access. |
| failure | Checked data() rejects moved-from report; typed handle access keeps its existing validity contract. |
| cost | Fixed Data/access or shared optimum-handle copy, no row scan/capture/serialization. |
| Design | [include/crown/observability/explain.hpp](../../../../../../include/crown/observability/explain.hpp), [src/observability/explain.cpp](../../../../../../src/observability/explain.cpp), [docs/observability.md](../../../../../observability.md) |

```text
GaugeAvailability gauge_availability() const;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Read committed-gauge availability. |
| inputs / outputs | Absent gauges remain typed unavailable rather than zero. |
| invariants | Mutable data alone never authorizes source acceptance, native plan execution, proof, output acknowledgment or durable publication. |
| ownership | Shared immutable report Data retains actual ModeDescriptor/program, typed evidence/family, funded captured trace/gauges and fixed metadata. It retains no mutable native owner; returned references borrow this report. Default copies share; implicit moved-from objects reject checked access. |
| failure | Checked data() rejects moved-from report; typed handle access keeps its existing validity contract. |
| cost | Fixed Data/access or shared optimum-handle copy, no row scan/capture/serialization. |
| Design | [include/crown/observability/explain.hpp](../../../../../../include/crown/observability/explain.hpp), [src/observability/explain.cpp](../../../../../../src/observability/explain.cpp), [docs/observability.md](../../../../../observability.md) |

```text
const std::optional<runtime::CapturedStateGauges>& gauges() const;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Borrow captured structural/population gauges. |
| inputs / outputs | Existing funded snapshot, no live owner traversal now. |
| invariants | Mutable data alone never authorizes source acceptance, native plan execution, proof, output acknowledgment or durable publication. |
| ownership | Shared immutable report Data retains actual ModeDescriptor/program, typed evidence/family, funded captured trace/gauges and fixed metadata. It retains no mutable native owner; returned references borrow this report. Default copies share; implicit moved-from objects reject checked access. |
| failure | Checked data() rejects moved-from report; typed handle access keeps its existing validity contract. |
| cost | Fixed Data/access or shared optimum-handle copy, no row scan/capture/serialization. |
| Design | [include/crown/observability/explain.hpp](../../../../../../include/crown/observability/explain.hpp), [src/observability/explain.cpp](../../../../../../src/observability/explain.cpp), [docs/observability.md](../../../../../observability.md) |

```text
const std::optional<runtime::CursorObservation>& cursor() const;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Borrow the recorded last-cursor observation. |
| inputs / outputs | Optional diagnostic value, not a live cursor/lease. |
| invariants | Mutable data alone never authorizes source acceptance, native plan execution, proof, output acknowledgment or durable publication. |
| ownership | Shared immutable report Data retains actual ModeDescriptor/program, typed evidence/family, funded captured trace/gauges and fixed metadata. It retains no mutable native owner; returned references borrow this report. Default copies share; implicit moved-from objects reject checked access. |
| failure | Checked data() rejects moved-from report; typed handle access keeps its existing validity contract. |
| cost | Fixed Data/access or shared optimum-handle copy, no row scan/capture/serialization. |
| Design | [include/crown/observability/explain.hpp](../../../../../../include/crown/observability/explain.hpp), [src/observability/explain.cpp](../../../../../../src/observability/explain.cpp), [docs/observability.md](../../../../../observability.md) |

```text
const std::optional<runtime::SessionStatus>& session_status() const;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Borrow captured session lifecycle status. |
| inputs / outputs | Absent for non-session reports. |
| invariants | Mutable data alone never authorizes source acceptance, native plan execution, proof, output acknowledgment or durable publication. |
| ownership | Shared immutable report Data retains actual ModeDescriptor/program, typed evidence/family, funded captured trace/gauges and fixed metadata. It retains no mutable native owner; returned references borrow this report. Default copies share; implicit moved-from objects reject checked access. |
| failure | Checked data() rejects moved-from report; typed handle access keeps its existing validity contract. |
| cost | Fixed Data/access or shared optimum-handle copy, no row scan/capture/serialization. |
| Design | [include/crown/observability/explain.hpp](../../../../../../include/crown/observability/explain.hpp), [src/observability/explain.cpp](../../../../../../src/observability/explain.cpp), [docs/observability.md](../../../../../observability.md) |

```text
const ModeDescriptor& mode() const;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Borrow actual current/retained mode metadata. |
| inputs / outputs | No attempt-mode inference or native configuration change. |
| invariants | Mutable data alone never authorizes source acceptance, native plan execution, proof, output acknowledgment or durable publication. |
| ownership | Shared immutable report Data retains actual ModeDescriptor/program, typed evidence/family, funded captured trace/gauges and fixed metadata. It retains no mutable native owner; returned references borrow this report. Default copies share; implicit moved-from objects reject checked access. |
| failure | Checked data() rejects moved-from report; typed handle access keeps its existing validity contract. |
| cost | Fixed Data/access or shared optimum-handle copy, no row scan/capture/serialization. |
| Design | [include/crown/observability/explain.hpp](../../../../../../include/crown/observability/explain.hpp), [src/observability/explain.cpp](../../../../../../src/observability/explain.cpp), [docs/observability.md](../../../../../observability.md) |

```text
HeightStatus height_status() const;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Read admitted height-evidence scope. |
| inputs / outputs | Upper/minimum/constant-operator status stays distinct. |
| invariants | Mutable data alone never authorizes source acceptance, native plan execution, proof, output acknowledgment or durable publication. |
| ownership | Shared immutable report Data retains actual ModeDescriptor/program, typed evidence/family, funded captured trace/gauges and fixed metadata. It retains no mutable native owner; returned references borrow this report. Default copies share; implicit moved-from objects reject checked access. |
| failure | Checked data() rejects moved-from report; typed handle access keeps its existing validity contract. |
| cost | Fixed Data/access or shared optimum-handle copy, no row scan/capture/serialization. |
| Design | [include/crown/observability/explain.hpp](../../../../../../include/crown/observability/explain.hpp), [src/observability/explain.cpp](../../../../../../src/observability/explain.cpp), [docs/observability.md](../../../../../observability.md) |

```text
std::size_t selected_height() const;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Read the checked selected physical tree height. |
| inputs / outputs | Not automatically a cost/depth/time optimum. |
| invariants | Mutable data alone never authorizes source acceptance, native plan execution, proof, output acknowledgment or durable publication. |
| ownership | Shared immutable report Data retains actual ModeDescriptor/program, typed evidence/family, funded captured trace/gauges and fixed metadata. It retains no mutable native owner; returned references borrow this report. Default copies share; implicit moved-from objects reject checked access. |
| failure | Checked data() rejects moved-from report; typed handle access keeps its existing validity contract. |
| cost | Fixed Data/access or shared optimum-handle copy, no row scan/capture/serialization. |
| Design | [include/crown/observability/explain.hpp](../../../../../../include/crown/observability/explain.hpp), [src/observability/explain.cpp](../../../../../../src/observability/explain.cpp), [docs/observability.md](../../../../../observability.md) |

```text
const HeightEvidence& evidence() const;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Borrow existing typed height evidence. |
| inputs / outputs | No proof replay is performed by access. |
| invariants | Mutable data alone never authorizes source acceptance, native plan execution, proof, output acknowledgment or durable publication. |
| ownership | Shared immutable report Data retains actual ModeDescriptor/program, typed evidence/family, funded captured trace/gauges and fixed metadata. It retains no mutable native owner; returned references borrow this report. Default copies share; implicit moved-from objects reject checked access. |
| failure | Checked data() rejects moved-from report; typed handle access keeps its existing validity contract. |
| cost | Fixed Data/access or shared optimum-handle copy, no row scan/capture/serialization. |
| Design | [include/crown/observability/explain.hpp](../../../../../../include/crown/observability/explain.hpp), [src/observability/explain.cpp](../../../../../../src/observability/explain.cpp), [docs/observability.md](../../../../../observability.md) |

```text
std::optional<planner::VerifiedOptimum> optimum() const;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Copy the existing original optimum handle if present. |
| inputs / outputs | Extracts VerifiedOptimum directly or from a minimum candidate; no new proof. |
| invariants | Mutable data alone never authorizes source acceptance, native plan execution, proof, output acknowledgment or durable publication. |
| ownership | Shared immutable report Data retains actual ModeDescriptor/program, typed evidence/family, funded captured trace/gauges and fixed metadata. It retains no mutable native owner; returned references borrow this report. Default copies share; implicit moved-from objects reject checked access. |
| failure | Checked data() rejects moved-from report; typed handle access keeps its existing validity contract. |
| cost | Fixed Data/access or shared optimum-handle copy, no row scan/capture/serialization. |
| Design | [include/crown/observability/explain.hpp](../../../../../../include/crown/observability/explain.hpp), [src/observability/explain.cpp](../../../../../../src/observability/explain.cpp), [docs/observability.md](../../../../../observability.md) |

```text
const std::optional<planner::CandidateSnapshot>& family() const;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Borrow the optional checked candidate-family snapshot. |
| inputs / outputs | Retains its own original proof/context; not a fresh enumeration. |
| invariants | Mutable data alone never authorizes source acceptance, native plan execution, proof, output acknowledgment or durable publication. |
| ownership | Shared immutable report Data retains actual ModeDescriptor/program, typed evidence/family, funded captured trace/gauges and fixed metadata. It retains no mutable native owner; returned references borrow this report. Default copies share; implicit moved-from objects reject checked access. |
| failure | Checked data() rejects moved-from report; typed handle access keeps its existing validity contract. |
| cost | Fixed Data/access or shared optimum-handle copy, no row scan/capture/serialization. |
| Design | [include/crown/observability/explain.hpp](../../../../../../include/crown/observability/explain.hpp), [src/observability/explain.cpp](../../../../../../src/observability/explain.cpp), [docs/observability.md](../../../../../observability.md) |

```text
const std::optional<runtime::ObservationSnapshot>& observation() const;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Borrow the captured observation snapshot. |
| inputs / outputs | No new owner capture or counters reset. |
| invariants | Mutable data alone never authorizes source acceptance, native plan execution, proof, output acknowledgment or durable publication. |
| ownership | Shared immutable report Data retains actual ModeDescriptor/program, typed evidence/family, funded captured trace/gauges and fixed metadata. It retains no mutable native owner; returned references borrow this report. Default copies share; implicit moved-from objects reject checked access. |
| failure | Checked data() rejects moved-from report; typed handle access keeps its existing validity contract. |
| cost | Fixed Data/access or shared optimum-handle copy, no row scan/capture/serialization. |
| Design | [include/crown/observability/explain.hpp](../../../../../../include/crown/observability/explain.hpp), [src/observability/explain.cpp](../../../../../../src/observability/explain.cpp), [docs/observability.md](../../../../../observability.md) |

```text
const runtime::CapturedTraceRecords& trace_records() const;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Borrow owned captured trace records. |
| inputs / outputs | Not a live ring or mutable owner view. |
| invariants | Mutable data alone never authorizes source acceptance, native plan execution, proof, output acknowledgment or durable publication. |
| ownership | Shared immutable report Data retains actual ModeDescriptor/program, typed evidence/family, funded captured trace/gauges and fixed metadata. It retains no mutable native owner; returned references borrow this report. Default copies share; implicit moved-from objects reject checked access. |
| failure | Checked data() rejects moved-from report; typed handle access keeps its existing validity contract. |
| cost | Fixed Data/access or shared optimum-handle copy, no row scan/capture/serialization. |
| Design | [include/crown/observability/explain.hpp](../../../../../../include/crown/observability/explain.hpp), [src/observability/explain.cpp](../../../../../../src/observability/explain.cpp), [docs/observability.md](../../../../../observability.md) |

```text
struct Data;
  explicit PlanExplanation(std::shared_ptr<const Data>);

```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Hide immutable plan-report contents. |
| inputs / outputs | Opaque native accounted report Data. |
| invariants | Closed report factories preserve actual typed source/evidence authority. |
| ownership | Shared immutable report Data retains actual ModeDescriptor/program, typed evidence/family, funded captured trace/gauges and fixed metadata. It retains no mutable native owner; returned references borrow this report. Default copies share; implicit moved-from objects reject checked access. |
| failure | Private helper/factory errors propagate; declarations introduce no catch or alternate recovery. |
| cost | Declaration only. |
| Design | [include/crown/observability/explain.hpp](../../../../../../include/crown/observability/explain.hpp), [src/observability/explain.cpp](../../../../../../src/observability/explain.cpp), [docs/observability.md](../../../../../observability.md) |

```text
explicit PlanExplanation(std::shared_ptr<const Data>);
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Publish prepared immutable plan-report ownership. |
| inputs / outputs | Moves shared Data descriptor. |
| invariants | Closed report factories preserve actual typed source/evidence authority. |
| ownership | Shared immutable report Data retains actual ModeDescriptor/program, typed evidence/family, funded captured trace/gauges and fixed metadata. It retains no mutable native owner; returned references borrow this report. Default copies share; implicit moved-from objects reject checked access. |
| failure | Private helper/factory errors propagate; declarations introduce no catch or alternate recovery. |
| cost | Fixed descriptor publication. |
| Design | [include/crown/observability/explain.hpp](../../../../../../include/crown/observability/explain.hpp), [src/observability/explain.cpp](../../../../../../src/observability/explain.cpp), [docs/observability.md](../../../../../observability.md) |

```text
friend class StatisticsExplanation;
  [[nodiscard]] static PlanExplanation capture_statistics_context(const runtime::DeltaRuntime&,ExplainLimits);

```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Permit the genuine v3 statistics report bridge. |
| inputs / outputs | StatisticsExplanation may invoke private context capture/make. |
| invariants | Closed report factories preserve actual typed source/evidence authority. |
| ownership | Shared immutable report Data retains actual ModeDescriptor/program, typed evidence/family, funded captured trace/gauges and fixed metadata. It retains no mutable native owner; returned references borrow this report. Default copies share; implicit moved-from objects reject checked access. |
| failure | Private helper/factory errors propagate; declarations introduce no catch or alternate recovery. |
| cost | Compile-time access only. |
| Design | [include/crown/observability/explain.hpp](../../../../../../include/crown/observability/explain.hpp), [src/observability/explain.cpp](../../../../../../src/observability/explain.cpp), [docs/observability.md](../../../../../observability.md) |

```text
static PlanExplanation capture_statistics_context(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Capture actual runtime context for v3 without legacy gauges. |
| inputs / outputs | Still captures trace/mode/cursor; state capture has its separate v3 work caps. |
| invariants | Closed report factories preserve actual typed source/evidence authority. |
| ownership | Shared immutable report Data retains actual ModeDescriptor/program, typed evidence/family, funded captured trace/gauges and fixed metadata. It retains no mutable native owner; returned references borrow this report. Default copies share; implicit moved-from objects reject checked access. |
| failure | Private helper/factory errors propagate; declarations introduce no catch or alternate recovery. |
| cost | Trace ownership and mode/report Data costs; skips legacy node/base gauge arrays. |
| Design | [include/crown/observability/explain.hpp](../../../../../../include/crown/observability/explain.hpp), [src/observability/explain.cpp](../../../../../../src/observability/explain.cpp), [docs/observability.md](../../../../../observability.md) |

```text
static PlanExplanation make(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Check exact binding/evidence/context and publish a complete report. |
| inputs / outputs | Private common admission receives prepared actual mode/trace/gauge/status values. |
| invariants | Closed report factories preserve actual typed source/evidence authority. |
| ownership | Shared immutable report Data retains actual ModeDescriptor/program, typed evidence/family, funded captured trace/gauges and fixed metadata. It retains no mutable native owner; returned references borrow this report. Default copies share; implicit moved-from objects reject checked access. |
| failure | Private helper/factory errors propagate; declarations introduce no catch or alternate recovery. |
| cost | Full Catalog/Query/tree/policy checks plus funded report allocation; supplied prepared captures may already exist. |
| Design | [include/crown/observability/explain.hpp](../../../../../../include/crown/observability/explain.hpp), [src/observability/explain.cpp](../../../../../../src/observability/explain.cpp), [docs/observability.md](../../../../../observability.md) |

## B0011

[Lines 80–85](../../../../../../include/crown/observability/explain.hpp#L80); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
const Data& data() const;
  std::shared_ptr<const Data> data_;
};
} // namespace crown::observability

```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Reject empty moved-from plan-report access. |
| inputs / outputs | Returns valid immutable Data or invalid_explanation. |
| invariants | Closed report factories preserve actual typed source/evidence authority. |
| ownership | Shared immutable report Data retains actual ModeDescriptor/program, typed evidence/family, funded captured trace/gauges and fixed metadata. It retains no mutable native owner; returned references borrow this report. Default copies share; implicit moved-from objects reject checked access. |
| failure | Private helper/factory errors propagate; declarations introduce no catch or alternate recovery. |
| cost | Fixed pointer test. |
| Design | [include/crown/observability/explain.hpp](../../../../../../include/crown/observability/explain.hpp), [src/observability/explain.cpp](../../../../../../src/observability/explain.cpp), [docs/observability.md](../../../../../observability.md) |

```text
std::shared_ptr<const Data> data_;
};
} // namespace crown::observability

```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Retain the immutable complete report graph. |
| inputs / outputs | Shares native plan/evidence/captured data; no live owner pointer. |
| invariants | Closed report factories preserve actual typed source/evidence authority. |
| ownership | Shared immutable report Data retains actual ModeDescriptor/program, typed evidence/family, funded captured trace/gauges and fixed metadata. It retains no mutable native owner; returned references borrow this report. Default copies share; implicit moved-from objects reject checked access. |
| failure | Private helper/factory errors propagate; declarations introduce no catch or alternate recovery. |
| cost | Fixed handle retention; last release destroys actual retained graphs. |
| Design | [include/crown/observability/explain.hpp](../../../../../../include/crown/observability/explain.hpp), [src/observability/explain.cpp](../../../../../../src/observability/explain.cpp), [docs/observability.md](../../../../../observability.md) |
