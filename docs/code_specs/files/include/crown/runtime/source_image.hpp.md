# `include/crown/runtime/source_image.hpp` — block usage map

[Source](../../../../../../include/crown/runtime/source_image.hpp) · [Source index](../../../../README.md) · [Subsystem contracts](../../../../subsystem_contracts.md) · [Reviewed primitives](../../../../primitives.md)

Declare deep accounted current or prepared physical source images with explicit row and work grants and no checkpoint authority.

Snapshot SHA-256: `f11ec4f073930073c44a50fda0094448772728007aae2a7265f168a50bfacc0c`. 30 lines partitioned into 5 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [physical](../../../../subsystem_contracts.md#physical). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/physical_runtime.md](../../../../../physical_runtime.md), [docs/runtime_initialization.md](../../../../../runtime_initialization.md), [docs/support_invariants.md](../../../../../support_invariants.md), [docs/query_memory.md](../../../../../query_memory.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–8](../../../../../../include/crown/runtime/source_image.hpp#L1) | Imports dependencies; guards repeated header inclusion; declares namespace scope. |  · [reviewed contract](#b0001) |
| [B0002 · 9–12](../../../../../../include/crown/runtime/source_image.hpp#L9) | Type/record definition: struct SourceImageLimits | source comment (unverified): // Total full physical rows, including unused tables. · [reviewed contract](#b0002) |
| [B0003 · 13–18](../../../../../../include/crown/runtime/source_image.hpp#L13) | Explanatory comments or spacing. | source comment (unverified): // Explicit owning compact source data, in catalog table order. Per-table row · [reviewed contract](#b0003) |
| [B0004 · 19–29](../../../../../../include/crown/runtime/source_image.hpp#L19) | Type/record definition: struct SourceImage | source comment (unverified): // Explicit owning compact source data, in catalog table order. Per-table row · [reviewed contract](#b0004) |
| [B0005 · 30–30](../../../../../../include/crown/runtime/source_image.hpp#L30) | Closes surrounding scope/type. | source comment (unverified): // namespace crown::runtime::physical · [reviewed contract](#b0005) |

## B0001

[Lines 1–8](../../../../../../include/crown/runtime/source_image.hpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L1-L8:sha256:1e62692aa3278212f46979bf0438abf5f648806842199da5d959c4bdab391bc5
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Import genuine native program, original-account allocator and compact tuple vocabulary for explicit source capture. |
| inputs / outputs | Header guard/includes and runtime::physical namespace; no capture occurs here. |
| invariants | No ordinary Database export, fallback selection or checkpoint restore authority is introduced by inclusion. |
| ownership | Declarations alone retain no query/account. |
| failure | Ordinary compile-time failures only. |
| cost | Compile-time scaffolding. |
| Design | [include/crown/runtime/source_image.hpp](../../../../../../include/crown/runtime/source_image.hpp), [include/crown/runtime/physical.hpp](../../../../../../include/crown/runtime/physical.hpp), [src/runtime/physical.cpp](../../../../../../src/runtime/physical.cpp), [docs/source_images.md](../../../../../source_images.md) |

## B0002

[Lines 9–12](../../../../../../include/crown/runtime/source_image.hpp#L9); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L9-L12:sha256:1cdc1ecb3980b0ab7f25f41fbf7cb4a9f47e1199701479d2476c5efa454988c0
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Declare one explicit image row/work grant covering all physical tables. |
| inputs / outputs | SourceImageLimits defaults to 65,536 total rows and one million selected table/row/field/payload-byte units. |
| invariants | Unused tables count too. Each explicit image gets this selected grant; it cannot replenish the separately retained indexed operation lease or serve as a memory/elapsed-time cap. |
| ownership | Inline caller-owned policy; copied synchronously during capture. |
| failure | Runtime capture refuses row/work exhaustion with source_image_row_limit/source_image_work_limit. |
| cost | Fixed descriptor; real traversal/copy/allocation and indexed-domain costs remain separate. |
| Design | [include/crown/runtime/source_image.hpp](../../../../../../include/crown/runtime/source_image.hpp), [src/runtime/physical.cpp](../../../../../../src/runtime/physical.cpp), [docs/source_images.md](../../../../../source_images.md) |

## B0003

[Lines 13–18](../../../../../../include/crown/runtime/source_image.hpp#L13); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L13-L18:sha256:f4cd724922ebd8f3aa963a86a1e43dca7fc11ecd4b79d8333ca28183425aed30
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | State the owning source-only image and its limited authority. |
| inputs / outputs | Comment-only preface to SourceImage. |
| invariants | Runtime-produced images are in catalog order; backend row order is unspecified. Genuine program metadata supplies source schemas/constraints. Editable exported images do not authenticate answers/checkpoints and cannot restore state. |
| ownership | Runtime-produced directory, rows and payloads retain the original query account after owner teardown. |
| failure | No executable validation or acceptance result is asserted by the comment. |
| cost | No runtime work from comments; producing/retaining the image has actual native costs. |
| Design | [include/crown/runtime/source_image.hpp](../../../../../../include/crown/runtime/source_image.hpp), [include/crown/runtime/physical.hpp](../../../../../../include/crown/runtime/physical.hpp), [src/runtime/physical.cpp](../../../../../../src/runtime/physical.cpp), [docs/source_images.md](../../../../../source_images.md) |

## B0004

[Lines 19–29](../../../../../../include/crown/runtime/source_image.hpp#L19); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L19-L29:sha256:4fd52d2092a9e5cdd132ab95a76e66175b9f71b187494fadc8aeef4f73021b8b
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Own a move-only compact physical source image with its original native program and account. |
| inputs / outputs | Sequence/work values, genuine CompiledProgram and original-account nested vectors of AccountedTuple; constructor accepts account/epoch/program. |
| invariants | Runtime production uses matching original account/program. Manual editable DTO construction is not authenticated state. No result sorting or derivation/output guarantee is represented. Copy is disabled; move is noexcept; row/string owners remain valid independently of source journals/runtime. |
| ownership | OwnerAllocator on directory and per-table rows retains MemoryAccount; each AccountedTuple/layout and CompiledProgram retains genuine native ownership. Moves transfer owning handles; no borrowed source pointer survives. |
| failure | Construction/allocation failures use normal typed allocation boundaries; declaration adds no catch/retry. Arbitrary caller edits do not mutate the runtime. |
| cost | O(1) move construction; move assignment/destruction may release previous nested payloads. Actual capture is full deep copy with explicit traversal/byte/account costs. |
| Design | [include/crown/runtime/source_image.hpp](../../../../../../include/crown/runtime/source_image.hpp), [src/runtime/physical.cpp](../../../../../../src/runtime/physical.cpp), [docs/source_images.md](../../../../../source_images.md) |

## B0005

[Lines 30–30](../../../../../../include/crown/runtime/source_image.hpp#L30); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L30-L30:sha256:648676d033ab17b84425c62c0eb97ad85ce8eb6aa6a77b9ef698fb8860e9422e
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Close the public source-image value namespace. |
| inputs / outputs | Namespace delimiter only. |
| invariants | No implicit registration or global shared-query state. |
| ownership | No owner. |
| failure | No executable branch. |
| cost | No runtime work. |
| Design | [include/crown/runtime/source_image.hpp](../../../../../../include/crown/runtime/source_image.hpp) |
