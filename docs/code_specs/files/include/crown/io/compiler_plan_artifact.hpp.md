# `include/crown/io/compiler_plan_artifact.hpp` — block usage map

[Source](../../../../../../include/crown/io/compiler_plan_artifact.hpp) · [Source index](../../../../README.md) · [Subsystem contracts](../../../../subsystem_contracts.md) · [Reviewed primitives](../../../../primitives.md)

Read/write explicit compiler-owned plan artifacts at the native admission boundary.

Snapshot SHA-256: `25509fa6f09ad4f82b428fc7963ecd5db4a06b541a1d8bdf6a0876aa63a65751`. 47 lines partitioned into 9 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [io](../../../../subsystem_contracts.md#io). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/ingestion.md](../../../../../ingestion.md), [docs/query_identity.md](../../../../../query_identity.md), [docs/schema_evolution.md](../../../../../schema_evolution.md), [docs/cli.md](../../../../../cli.md), [docs/query_memory.md](../../../../../query_memory.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–7](../../../../../../include/crown/io/compiler_plan_artifact.hpp#L1) | Imports dependencies; guards repeated header inclusion; declares namespace scope. |  · [reviewed contract](#b0001) |
| [B0002 · 8–13](../../../../../../include/crown/io/compiler_plan_artifact.hpp#L8) | Type/record definition: struct CompilerArtifactLimits | source comment (unverified): // Prepare checks this after serialization; replay checks before DOM parsing. · [reviewed contract](#b0002) |
| [B0003 · 14–17](../../../../../../include/crown/io/compiler_plan_artifact.hpp#L14) | Type/record definition: struct CompilerArtifactStatistics |  · [reviewed contract](#b0003) |
| [B0004 · 18–36](../../../../../../include/crown/io/compiler_plan_artifact.hpp#L18) | declares types or opens a type body; declares callable signatures; declares values/defaults or compile-time conditions. | source comment (unverified): // Explicit compiler DTO boundary, before native publication/admission. JSON, · [reviewed contract](#b0004) |
| [B0005 · 37–37](../../../../../../include/crown/io/compiler_plan_artifact.hpp#L37) | Callable definition: \[\[nodiscard\]\] const CompiledProgram& program() const noexcept | calls ; returns program_ · [reviewed contract](#b0005) |
| [B0006 · 38–38](../../../../../../include/crown/io/compiler_plan_artifact.hpp#L38) | Callable definition: \[\[nodiscard\]\] std::string_view bytes() const noexcept | calls view; returns bytes_.view() · [reviewed contract](#b0006) |
| [B0007 · 39–39](../../../../../../include/crown/io/compiler_plan_artifact.hpp#L39) | Callable definition: \[\[nodiscard\]\] const CompilerArtifactStatistics& statistics() const noexcept | calls ; returns statistics_ · [reviewed contract](#b0007) |
| [B0008 · 40–42](../../../../../../include/crown/io/compiler_plan_artifact.hpp#L40) | Callable definition: private: CompilerPlanArtifact(CompiledProgram program,resource::AccountedText bytes,CompilerArtifactStatistics statistics) :progr… | calls program_, std::move, bytes_, statistics_ · [reviewed contract](#b0008) |
| [B0009 · 43–47](../../../../../../include/crown/io/compiler_plan_artifact.hpp#L43) | Member/declaration region. | source comment (unverified): // namespace crown::io · [reviewed contract](#b0009) |

## B0001

[Lines 1–7](../../../../../../include/crown/io/compiler_plan_artifact.hpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
#pragma once
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Declare the io compiler_plan_artifact public interface and its required types. |
| inputs / outputs | Header imports its explicit dependencies and declares the APIs/contracts below. |
| invariants | Inclusion does not construct a live query, source, report, proof or file owner. |
| ownership | Declarations retain no instance; object ownership and copies are specified at the individual APIs. |
| failure | Compile-time dependency/declaration boundary; runtime failures belong to instantiated objects/operations. |
| cost | No runtime action from inclusion itself; inline methods retain their stated actual costs. |
| Design | [include/crown/io/compiler_plan_artifact.hpp](../../../../../../include/crown/io/compiler_plan_artifact.hpp), [src/io/compiler_plan_artifact.cpp](../../../../../../src/io/compiler_plan_artifact.cpp), [src/io/physical.cpp](../../../../../../src/io/physical.cpp), [docs/reoptimization.md](../../../../../reoptimization.md) |

## B0002

[Lines 8–13](../../../../../../include/crown/io/compiler_plan_artifact.hpp#L8); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct CompilerArtifactLimits {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Configure compiler artifact retention/replay caps. |
| inputs / outputs | Serialized artifact byte cap plus physical replay/lowering limits. |
| invariants | Replay checks input bytes before DOM parse; prepare-time compiler DTO and serialization scratch can allocate before this cap. This is not total process memory. |
| ownership | Inline fixed fields only; copying these values allocates no container or text. No source/native owner is retained. |
| failure | Declaration/field initialization performs no semantic validation. Consumers validate the actual values at their own boundary. |
| cost | Fixed-size initialization/copy/comparison; declaration itself performs no runtime scan or I/O. |
| Design | [include/crown/io/compiler_plan_artifact.hpp](../../../../../../include/crown/io/compiler_plan_artifact.hpp), [src/io/compiler_plan_artifact.cpp](../../../../../../src/io/compiler_plan_artifact.cpp), [src/io/physical.cpp](../../../../../../src/io/physical.cpp), [docs/reoptimization.md](../../../../../reoptimization.md) |

```text
std::uint64_t bytes=64*1024*1024;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | The retained serialized artifact byte cap; prepare checks it after serialization. |
| inputs / outputs | Stores/exposes the retained serialized artifact byte cap; prepare checks it after serialization. |
| invariants | Replay checks input bytes before DOM parse; prepare-time compiler DTO and serialization scratch can allocate before this cap. This is not total process memory. |
| ownership | Inline fixed fields only; copying these values allocates no container or text. No source/native owner is retained. |
| failure | Assignment adds no validation; aggregate construction/copy has the ownership costs stated here. |
| cost | Fixed-size initialization/copy/comparison; declaration itself performs no runtime scan or I/O. |
| Design | [include/crown/io/compiler_plan_artifact.hpp](../../../../../../include/crown/io/compiler_plan_artifact.hpp), [src/io/compiler_plan_artifact.cpp](../../../../../../src/io/compiler_plan_artifact.cpp), [src/io/physical.cpp](../../../../../../src/io/physical.cpp), [docs/reoptimization.md](../../../../../reoptimization.md) |

```text
PhysicalReadLimits replay;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | The separate reconstruction/binding/lowering work limits. |
| inputs / outputs | Stores/exposes the separate reconstruction/binding/lowering work limits. |
| invariants | Replay checks input bytes before DOM parse; prepare-time compiler DTO and serialization scratch can allocate before this cap. This is not total process memory. |
| ownership | Inline fixed fields only; copying these values allocates no container or text. No source/native owner is retained. |
| failure | Assignment adds no validation; aggregate construction/copy has the ownership costs stated here. |
| cost | Fixed-size initialization/copy/comparison; declaration itself performs no runtime scan or I/O. |
| Design | [include/crown/io/compiler_plan_artifact.hpp](../../../../../../include/crown/io/compiler_plan_artifact.hpp), [src/io/compiler_plan_artifact.cpp](../../../../../../src/io/compiler_plan_artifact.cpp), [src/io/physical.cpp](../../../../../../src/io/physical.cpp), [docs/reoptimization.md](../../../../../reoptimization.md) |

## B0003

[Lines 14–17](../../../../../../include/crown/io/compiler_plan_artifact.hpp#L14); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct CompilerArtifactStatistics {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Report actual compiler-boundary observations. |
| inputs / outputs | Retained bytes, preparation elapsed nanoseconds, clock reads and compiler-account memory counters. |
| invariants | Public value/configuration only; changing fields does not perform admission, execute an input or create proof authority. |
| ownership | Inline fixed fields only; copying these values allocates no container or text. No source/native owner is retained. |
| failure | Declaration/field initialization performs no semantic validation. Consumers validate the actual values at their own boundary. |
| cost | Fixed-size initialization/copy/comparison; declaration itself performs no runtime scan or I/O. |
| Design | [include/crown/io/compiler_plan_artifact.hpp](../../../../../../include/crown/io/compiler_plan_artifact.hpp), [src/io/compiler_plan_artifact.cpp](../../../../../../src/io/compiler_plan_artifact.cpp), [src/io/physical.cpp](../../../../../../src/io/physical.cpp), [docs/reoptimization.md](../../../../../reoptimization.md) |

```text
std::uint64_t bytes=0,preparation_ns=0,clock_reads=0;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | The retained byte length, measured preparation interval and two clock reads. |
| inputs / outputs | Stores/exposes the retained byte length, measured preparation interval and two clock reads. |
| invariants | This field is descriptive/configuration data, not an independent admission or publication capability. |
| ownership | Inline fixed fields only; copying these values allocates no container or text. No source/native owner is retained. |
| failure | Assignment adds no validation; aggregate construction/copy has the ownership costs stated here. |
| cost | Fixed-size initialization/copy/comparison; declaration itself performs no runtime scan or I/O. |
| Design | [include/crown/io/compiler_plan_artifact.hpp](../../../../../../include/crown/io/compiler_plan_artifact.hpp), [src/io/compiler_plan_artifact.cpp](../../../../../../src/io/compiler_plan_artifact.cpp), [src/io/physical.cpp](../../../../../../src/io/physical.cpp), [docs/reoptimization.md](../../../../../reoptimization.md) |

```text
resource::MemoryStatistics compiler_memory;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | The supplied compiler account current/peak/history observation, excluding ordinary DTO scratch. |
| inputs / outputs | Stores/exposes the supplied compiler account current/peak/history observation, excluding ordinary DTO scratch. |
| invariants | This field is descriptive/configuration data, not an independent admission or publication capability. |
| ownership | Inline fixed fields only; copying these values allocates no container or text. No source/native owner is retained. |
| failure | Assignment adds no validation; aggregate construction/copy has the ownership costs stated here. |
| cost | Fixed-size initialization/copy/comparison; declaration itself performs no runtime scan or I/O. |
| Design | [include/crown/io/compiler_plan_artifact.hpp](../../../../../../include/crown/io/compiler_plan_artifact.hpp), [src/io/compiler_plan_artifact.cpp](../../../../../../src/io/compiler_plan_artifact.cpp), [src/io/physical.cpp](../../../../../../src/io/physical.cpp), [docs/reoptimization.md](../../../../../reoptimization.md) |

## B0004

[Lines 18–36](../../../../../../include/crown/io/compiler_plan_artifact.hpp#L18); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
class CompilerPlanArtifact
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Retain an explicit compiler artifact before native publication. |
| inputs / outputs | Closed prepare/replay factories return owned native executable metadata, exact serialized bytes and preparation observations. |
| invariants | Ordinary JSON/PhysicalPlan scratch belongs to compiler preparation; this handle does not itself switch a session or prove original minimum height. |
| ownership | Move-only value owns CompiledProgram metadata and AccountedText bytes on the supplied compiler account. Getters borrow this artifact; execution later imports/freezes into its original receiving account. |
| failure | Byte/replay/binding/clock/allocation errors propagate and no completed artifact is returned. |
| cost | Full serializer/export/reconstruction work plus funded program/bytes retention; preparation/temporary compiler storage overlap is explicit. |
| Design | [include/crown/io/compiler_plan_artifact.hpp](../../../../../../include/crown/io/compiler_plan_artifact.hpp), [src/io/compiler_plan_artifact.cpp](../../../../../../src/io/compiler_plan_artifact.cpp), [src/io/physical.cpp](../../../../../../src/io/physical.cpp), [docs/reoptimization.md](../../../../../reoptimization.md) |

```text
const PhysicalPlan&,CompilerArtifactLimits={});
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Prepare or reconstruct an owned compiler artifact. |
| inputs / outputs | Prepare from the already typed PhysicalPlan, serializing then compiling/funding metadata and bytes. |
| invariants | Checks nonempty/byte cap after ordinary write_physical().dump(); no source/session mutation. |
| ownership | Move-only value owns CompiledProgram metadata and AccountedText bytes on the supplied compiler account. Getters borrow this artifact; execution later imports/freezes into its original receiving account. |
| failure | Compiler artifact byte, replay, binding, clock or allocation errors propagate before return. |
| cost | Full ordinary DOM/string serialization, native compile/deep metadata and exact retained byte copy; measures through temporary teardown. |
| Design | [include/crown/io/compiler_plan_artifact.hpp](../../../../../../include/crown/io/compiler_plan_artifact.hpp), [src/io/compiler_plan_artifact.cpp](../../../../../../src/io/compiler_plan_artifact.cpp), [src/io/physical.cpp](../../../../../../src/io/physical.cpp), [docs/reoptimization.md](../../../../../reoptimization.md) |

```text
const CompiledProgram&,CompilerArtifactLimits={});
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Prepare or reconstruct an owned compiler artifact. |
| inputs / outputs | Explicitly export native source to PhysicalPlan, lower again, compare both physical/source hashes, serialize and compile. |
| invariants | Rejects empty checked source; no compiler DTO export runs inside native mutation/publication. |
| ownership | Move-only value owns CompiledProgram metadata and AccountedText bytes on the supplied compiler account. Getters borrow this artifact; execution later imports/freezes into its original receiving account. |
| failure | Compiler artifact byte, replay, binding, clock or allocation errors propagate before return. |
| cost | DTO export, canonical replay/lowering, serializer, native metadata/byte retention and temporary teardown; byte cap follows preparation serialization. |
| Design | [include/crown/io/compiler_plan_artifact.hpp](../../../../../../include/crown/io/compiler_plan_artifact.hpp), [src/io/compiler_plan_artifact.cpp](../../../../../../src/io/compiler_plan_artifact.cpp), [src/io/physical.cpp](../../../../../../src/io/physical.cpp), [docs/reoptimization.md](../../../../../reoptimization.md) |

```text
std::string_view,CompilerArtifactLimits={});
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Prepare or reconstruct an owned compiler artifact. |
| inputs / outputs | Replay bounded serialized bytes through full physical reconstruction, compile and retain an exact byte copy. |
| invariants | Host replay caps are independent of stored producer limits; valid tree/lowering metadata is distinct from minimum-height proof. |
| ownership | Move-only value owns CompiledProgram metadata and AccountedText bytes on the supplied compiler account. Getters borrow this artifact; execution later imports/freezes into its original receiving account. |
| failure | Compiler artifact byte, replay, binding, clock or allocation errors propagate before return. |
| cost | Upfront byte check, DOM/binding/normalization/tree/lowering replay, full artifact comparison, funded metadata and byte copy. |
| Design | [include/crown/io/compiler_plan_artifact.hpp](../../../../../../include/crown/io/compiler_plan_artifact.hpp), [src/io/compiler_plan_artifact.cpp](../../../../../../src/io/compiler_plan_artifact.cpp), [src/io/physical.cpp](../../../../../../src/io/physical.cpp), [docs/reoptimization.md](../../../../../reoptimization.md) |

```text
CompilerPlanArtifact(const CompilerPlanArtifact&)=delete;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Reject implicit artifact deep/shared copying. |
| inputs / outputs | Operate on the artifact value or its retained members. |
| invariants | Borrowed results retain no extra artifact owner; moved-from members follow their own empty-handle semantics. |
| ownership | Move-only value owns CompiledProgram metadata and AccountedText bytes on the supplied compiler account. Getters borrow this artifact; execution later imports/freezes into its original receiving account. |
| failure | Deleted operations fail compilation; declared noexcept moves/getters add no handler. |
| cost | Compile-time restriction. |
| Design | [include/crown/io/compiler_plan_artifact.hpp](../../../../../../include/crown/io/compiler_plan_artifact.hpp), [src/io/compiler_plan_artifact.cpp](../../../../../../src/io/compiler_plan_artifact.cpp), [src/io/physical.cpp](../../../../../../src/io/physical.cpp), [docs/reoptimization.md](../../../../../reoptimization.md) |

```text
CompilerPlanArtifact& operator=(const CompilerPlanArtifact&)=delete;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Reject artifact copy assignment. |
| inputs / outputs | Operate on the artifact value or its retained members. |
| invariants | Borrowed results retain no extra artifact owner; moved-from members follow their own empty-handle semantics. |
| ownership | Move-only value owns CompiledProgram metadata and AccountedText bytes on the supplied compiler account. Getters borrow this artifact; execution later imports/freezes into its original receiving account. |
| failure | Deleted operations fail compilation; declared noexcept moves/getters add no handler. |
| cost | Compile-time restriction. |
| Design | [include/crown/io/compiler_plan_artifact.hpp](../../../../../../include/crown/io/compiler_plan_artifact.hpp), [src/io/compiler_plan_artifact.cpp](../../../../../../src/io/compiler_plan_artifact.cpp), [src/io/physical.cpp](../../../../../../src/io/physical.cpp), [docs/reoptimization.md](../../../../../reoptimization.md) |

```text
CompilerPlanArtifact(CompilerPlanArtifact&&) noexcept=default;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Move owned compiler program/bytes/statistics. |
| inputs / outputs | Operate on the artifact value or its retained members. |
| invariants | Borrowed results retain no extra artifact owner; moved-from members follow their own empty-handle semantics. |
| ownership | Move-only value owns CompiledProgram metadata and AccountedText bytes on the supplied compiler account. Getters borrow this artifact; execution later imports/freezes into its original receiving account. |
| failure | Deleted operations fail compilation; declared noexcept moves/getters add no handler. |
| cost | Descriptor/value transfer; no metadata/byte clone. |
| Design | [include/crown/io/compiler_plan_artifact.hpp](../../../../../../include/crown/io/compiler_plan_artifact.hpp), [src/io/compiler_plan_artifact.cpp](../../../../../../src/io/compiler_plan_artifact.cpp), [src/io/physical.cpp](../../../../../../src/io/physical.cpp), [docs/reoptimization.md](../../../../../reoptimization.md) |

```text
CompilerPlanArtifact& operator=(CompilerPlanArtifact&&) noexcept=default;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Replace and move artifact ownership. |
| inputs / outputs | Operate on the artifact value or its retained members. |
| invariants | Borrowed results retain no extra artifact owner; moved-from members follow their own empty-handle semantics. |
| ownership | Move-only value owns CompiledProgram metadata and AccountedText bytes on the supplied compiler account. Getters borrow this artifact; execution later imports/freezes into its original receiving account. |
| failure | Deleted operations fail compilation; declared noexcept moves/getters add no handler. |
| cost | Transfer plus actual old metadata/text graph release; no new allocation. |
| Design | [include/crown/io/compiler_plan_artifact.hpp](../../../../../../include/crown/io/compiler_plan_artifact.hpp), [src/io/compiler_plan_artifact.cpp](../../../../../../src/io/compiler_plan_artifact.cpp), [src/io/physical.cpp](../../../../../../src/io/physical.cpp), [docs/reoptimization.md](../../../../../reoptimization.md) |

## B0005

[Lines 37–37](../../../../../../include/crown/io/compiler_plan_artifact.hpp#L37); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
const CompiledProgram& program() const noexcept
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Borrow the retained native program. |
| inputs / outputs | Operate on the artifact value or its retained members. |
| invariants | Borrowed results retain no extra artifact owner; moved-from members follow their own empty-handle semantics. |
| ownership | Move-only value owns CompiledProgram metadata and AccountedText bytes on the supplied compiler account. Getters borrow this artifact; execution later imports/freezes into its original receiving account. |
| failure | Deleted operations fail compilation; declared noexcept moves/getters add no handler. |
| cost | Constant reference access. |
| Design | [include/crown/io/compiler_plan_artifact.hpp](../../../../../../include/crown/io/compiler_plan_artifact.hpp), [src/io/compiler_plan_artifact.cpp](../../../../../../src/io/compiler_plan_artifact.cpp), [src/io/physical.cpp](../../../../../../src/io/physical.cpp), [docs/reoptimization.md](../../../../../reoptimization.md) |

## B0006

[Lines 38–38](../../../../../../include/crown/io/compiler_plan_artifact.hpp#L38); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::string_view bytes() const noexcept
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Borrow the exact retained artifact bytes. |
| inputs / outputs | Operate on the artifact value or its retained members. |
| invariants | Borrowed results retain no extra artifact owner; moved-from members follow their own empty-handle semantics. |
| ownership | Move-only value owns CompiledProgram metadata and AccountedText bytes on the supplied compiler account. Getters borrow this artifact; execution later imports/freezes into its original receiving account. |
| failure | Deleted operations fail compilation; declared noexcept moves/getters add no handler. |
| cost | Constant view access; does not serialize/compile. |
| Design | [include/crown/io/compiler_plan_artifact.hpp](../../../../../../include/crown/io/compiler_plan_artifact.hpp), [src/io/compiler_plan_artifact.cpp](../../../../../../src/io/compiler_plan_artifact.cpp), [src/io/physical.cpp](../../../../../../src/io/physical.cpp), [docs/reoptimization.md](../../../../../reoptimization.md) |

## B0007

[Lines 39–39](../../../../../../include/crown/io/compiler_plan_artifact.hpp#L39); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
const CompilerArtifactStatistics& statistics() const noexcept
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Borrow immutable preparation observations. |
| inputs / outputs | Operate on the artifact value or its retained members. |
| invariants | Borrowed results retain no extra artifact owner; moved-from members follow their own empty-handle semantics. |
| ownership | Move-only value owns CompiledProgram metadata and AccountedText bytes on the supplied compiler account. Getters borrow this artifact; execution later imports/freezes into its original receiving account. |
| failure | Deleted operations fail compilation; declared noexcept moves/getters add no handler. |
| cost | Constant reference access. |
| Design | [include/crown/io/compiler_plan_artifact.hpp](../../../../../../include/crown/io/compiler_plan_artifact.hpp), [src/io/compiler_plan_artifact.cpp](../../../../../../src/io/compiler_plan_artifact.cpp), [src/io/physical.cpp](../../../../../../src/io/physical.cpp), [docs/reoptimization.md](../../../../../reoptimization.md) |

## B0008

[Lines 40–42](../../../../../../include/crown/io/compiler_plan_artifact.hpp#L40); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
CompilerPlanArtifact(CompiledProgram program,
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Publish privately prepared artifact members by move. |
| inputs / outputs | Private factory/member storage for the prepared artifact. |
| invariants | No public constructor accepts arbitrary DTO flags or an unrelated byte/program pairing. |
| ownership | Move-only value owns CompiledProgram metadata and AccountedText bytes on the supplied compiler account. Getters borrow this artifact; execution later imports/freezes into its original receiving account. |
| failure | Private publication follows successful preparation; members supply their existing failure/destruction rules. |
| cost | Moves or fixed field storage; final release keeps actual graph cost. |
| Design | [include/crown/io/compiler_plan_artifact.hpp](../../../../../../include/crown/io/compiler_plan_artifact.hpp), [src/io/compiler_plan_artifact.cpp](../../../../../../src/io/compiler_plan_artifact.cpp), [src/io/physical.cpp](../../../../../../src/io/physical.cpp), [docs/reoptimization.md](../../../../../reoptimization.md) |

## B0009

[Lines 43–47](../../../../../../include/crown/io/compiler_plan_artifact.hpp#L43); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
CompiledProgram program_;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Own the compiler-account native program graph. |
| inputs / outputs | Private factory/member storage for the prepared artifact. |
| invariants | No public constructor accepts arbitrary DTO flags or an unrelated byte/program pairing. |
| ownership | Move-only value owns CompiledProgram metadata and AccountedText bytes on the supplied compiler account. Getters borrow this artifact; execution later imports/freezes into its original receiving account. |
| failure | Private publication follows successful preparation; members supply their existing failure/destruction rules. |
| cost | Moves or fixed field storage; final release keeps actual graph cost. |
| Design | [include/crown/io/compiler_plan_artifact.hpp](../../../../../../include/crown/io/compiler_plan_artifact.hpp), [src/io/compiler_plan_artifact.cpp](../../../../../../src/io/compiler_plan_artifact.cpp), [src/io/physical.cpp](../../../../../../src/io/physical.cpp), [docs/reoptimization.md](../../../../../reoptimization.md) |

```text
resource::AccountedText bytes_;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Own the exact compiler-account serialized byte block. |
| inputs / outputs | Private factory/member storage for the prepared artifact. |
| invariants | No public constructor accepts arbitrary DTO flags or an unrelated byte/program pairing. |
| ownership | Move-only value owns CompiledProgram metadata and AccountedText bytes on the supplied compiler account. Getters borrow this artifact; execution later imports/freezes into its original receiving account. |
| failure | Private publication follows successful preparation; members supply their existing failure/destruction rules. |
| cost | Moves or fixed field storage; final release keeps actual graph cost. |
| Design | [include/crown/io/compiler_plan_artifact.hpp](../../../../../../include/crown/io/compiler_plan_artifact.hpp), [src/io/compiler_plan_artifact.cpp](../../../../../../src/io/compiler_plan_artifact.cpp), [src/io/physical.cpp](../../../../../../src/io/physical.cpp), [docs/reoptimization.md](../../../../../reoptimization.md) |

```text
CompilerArtifactStatistics statistics_;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Store fixed preparation/account observations. |
| inputs / outputs | Private factory/member storage for the prepared artifact. |
| invariants | No public constructor accepts arbitrary DTO flags or an unrelated byte/program pairing. |
| ownership | Move-only value owns CompiledProgram metadata and AccountedText bytes on the supplied compiler account. Getters borrow this artifact; execution later imports/freezes into its original receiving account. |
| failure | Private publication follows successful preparation; members supply their existing failure/destruction rules. |
| cost | Moves or fixed field storage; final release keeps actual graph cost. |
| Design | [include/crown/io/compiler_plan_artifact.hpp](../../../../../../include/crown/io/compiler_plan_artifact.hpp), [src/io/compiler_plan_artifact.cpp](../../../../../../src/io/compiler_plan_artifact.cpp), [src/io/physical.cpp](../../../../../../src/io/physical.cpp), [docs/reoptimization.md](../../../../../reoptimization.md) |
