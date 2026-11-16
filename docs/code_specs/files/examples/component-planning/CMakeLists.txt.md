# `examples/component-planning/CMakeLists.txt` — block usage map

[Source](../../../../../examples/component-planning/CMakeLists.txt) · [Source index](../../../README.md) · [Subsystem contracts](../../../subsystem_contracts.md) · [Reviewed primitives](../../../primitives.md)

Define native target boundaries, pinned dependencies, compilation options, installation and test registration.

Snapshot SHA-256: `95c7a4b1222ae17a79b6b5ce603eaa449f9f35b6dcb82dfd01e0d833f906fb1d`. 7 lines partitioned into 7 blocks using `cmake_commands`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [build](../../../subsystem_contracts.md#build). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/native_build.md](../../../../native_build.md), [docs/source_baselines.md](../../../../source_baselines.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–1](../../../../../examples/component-planning/CMakeLists.txt#L1) | CMake command: cmake_minimum_required(VERSION 3.25) |  · [reviewed contract](#b0001) |
| [B0002 · 2–2](../../../../../examples/component-planning/CMakeLists.txt#L2) | CMake command: project(crown_component_planning LANGUAGES CXX) |  · [reviewed contract](#b0002) |
| [B0003 · 3–3](../../../../../examples/component-planning/CMakeLists.txt#L3) | CMake command: find_package(Crown 0.1 CONFIG REQUIRED) |  · [reviewed contract](#b0003) |
| [B0004 · 4–4](../../../../../examples/component-planning/CMakeLists.txt#L4) | CMake command: add_executable(crown_export_components main.cpp) |  · [reviewed contract](#b0004) |
| [B0005 · 5–5](../../../../../examples/component-planning/CMakeLists.txt#L5) | CMake command: set_target_properties(crown_export_components PROPERTIES CXX_EXTENSIONS OFF) |  · [reviewed contract](#b0005) |
| [B0006 · 6–6](../../../../../examples/component-planning/CMakeLists.txt#L6) | CMake command: target_link_libraries(crown_export_components PRIVATE CROWN::ranking_runtime CROWN::meta_candidates) |  · [reviewed contract](#b0006) |
| [B0007 · 7–7](../../../../../examples/component-planning/CMakeLists.txt#L7) | CMake command: target_compile_options(crown_export_components PRIVATE -Wall -Wextra -Wpedantic -Wconversion -Wsign-conversion -Werror) |  · [reviewed contract](#b0007) |

## B0001

[Lines 1–1](../../../../../examples/component-planning/CMakeLists.txt#L1); `build-command`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L1-L1:sha256:864a28dfe13a0c73206b6838977d8ca0acc5f9ec8da56f4e6f3aa70dae47ea49
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Require the CMake version used by the public standalone consumer contract. |
| inputs / outputs | CMake&gt;=3.25 is admitted. |
| invariants | This is a consumer project, not a modification to root build/test registration. |
| ownership | CMake owns configure state in the caller-selected build directory. |
| failure | Older CMake rejects configuration. |
| cost | Configure-time version check only. |
| Design | [docs/measurement.md](../../../../measurement.md), [build/verification/v58-b04-design-review-v1/README.md](../../../../../build/verification/v58-b04-design-review-v1/README.md) |

## B0002

[Lines 2–2](../../../../../examples/component-planning/CMakeLists.txt#L2); `build-command`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L2-L2:sha256:52f43cfdc68feaf30b04e6a651db528db8c3baed67bdf1da5e8cfde30c5cf055
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Create a standalone C++ cold-exporter consumer project. |
| inputs / outputs | Project name and CXX language enable compiler configuration. |
| invariants | No private test target or query-specialized engine is declared. |
| ownership | Caller-selected out-of-source CMake build owns generated files. |
| failure | Unavailable compiler/configuration fails explicitly. |
| cost | Configure-time compiler detection and generated build metadata. |
| Design | [docs/measurement.md](../../../../measurement.md), [build/verification/v58-b04-design-review-v1/README.md](../../../../../build/verification/v58-b04-design-review-v1/README.md) |

## B0003

[Lines 3–3](../../../../../examples/component-planning/CMakeLists.txt#L3); `build-command`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L3-L3:sha256:7aba7d5c1cfa13193c246b121112e4cadbe127f878172857fb11dc0345bbb8d4
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Resolve the installed public Crown0.1 config and its exported dependencies. |
| inputs / outputs | Crown_DIR/prefix discovery yields imported public targets. |
| invariants | Missing package is not silently replaced by private source/test libraries. |
| ownership | Package targets reference the installation selected by the caller. |
| failure | REQUIRED makes absent/incompatible config fail. |
| cost | Configure/package-resolution cost; no runtime work. |
| Design | [docs/measurement.md](../../../../measurement.md), [build/verification/v58-b04-design-review-v1/README.md](../../../../../build/verification/v58-b04-design-review-v1/README.md) |

## B0004

[Lines 4–4](../../../../../examples/component-planning/CMakeLists.txt#L4); `build-command`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L4-L4:sha256:13c0e5e363ee2efc90c74440b8170ac507ac509bb063760c59c59c50fe86c68e
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Declare exactly one cold planning exporter executable from main.cpp. |
| inputs / outputs | The owned source produces crown_export_components. |
| invariants | No production runtime source or generated specialization is added by this declaration. |
| ownership | CMake build owns its object/executable outputs. |
| failure | Compilation/link failure rejects the build. |
| cost | Native compilation/link cost is setup, not query planning/runtime measurement. |
| Design | [docs/measurement.md](../../../../measurement.md), [build/verification/v58-b04-design-review-v1/README.md](../../../../../build/verification/v58-b04-design-review-v1/README.md) |

## B0005

[Lines 5–5](../../../../../examples/component-planning/CMakeLists.txt#L5); `build-command`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L5-L5:sha256:50568937096bacf249f14d9dc1197577e0159d78e93ac67640a48af8d18feb75
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Use standard C++ semantics without compiler language extensions for this consumer. |
| inputs / outputs | CXX_EXTENSIONS OFF modifies the executable build configuration. |
| invariants | The public target propagates required C++ standard features; this setting does not claim portability to every compiler. |
| ownership | Build metadata belongs to the consumer project. |
| failure | Unsupported language/features fail compilation. |
| cost | Configure/compile flag selection only. |
| Design | [docs/measurement.md](../../../../measurement.md), [build/verification/v58-b04-design-review-v1/README.md](../../../../../build/verification/v58-b04-design-review-v1/README.md) |

## B0006

[Lines 6–6](../../../../../examples/component-planning/CMakeLists.txt#L6); `build-command`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L6-L6:sha256:9043afb87e0aec24c871cd5cb3e8def450aa07b544ae9bb02de5eb3d9ce4438a
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Link only the public cold ranking/runtime and bounded meta adapter library closure. |
| inputs / outputs | CROWN::ranking_runtime and CROWN::meta_candidates satisfy all exporter APIs. |
| invariants | No reference oracle/test library, private baseline or C05 maintenance-cost integration is pulled in by this declaration. |
| ownership | Imported targets retain their installation paths; the executable owns linked/runtime process state when invoked. |
| failure | Missing exports/unresolved symbols fail the standalone link. |
| cost | Link/setup and actual public library runtime costs stay distinct; no new per-update dispatch layer. |
| Design | [docs/maintenance_cost.md](../../../../maintenance_cost.md), [include/crown/runtime/maintenance_cost.hpp](../../../../../include/crown/runtime/maintenance_cost.hpp), [build/verification/v58-b04-design-review-v1/README.md](../../../../../build/verification/v58-b04-design-review-v1/README.md), [docs/meta_candidate_adapter.md](../../../../meta_candidate_adapter.md), [docs/meta_decompositions.md](../../../../meta_decompositions.md), [exact paper reference](https://arxiv.org/pdf/2301.04003v2), [exact paper reference](https://arxiv.org/pdf/2603.15465v2), [build/verification/v58-b04-design-review-v1/README.md](../../../../../build/verification/v58-b04-design-review-v1/README.md) |

## B0007

[Lines 7–7](../../../../../examples/component-planning/CMakeLists.txt#L7); `build-command`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L7-L7:sha256:7c500807c6890855e0924a4c02d34aab201198be52388f1e1b208b17b7c2ec4e
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Build the exporter under strict warning/conversion diagnostics. |
| inputs / outputs | Compiler warning flags enforce the same GNU/Clang consumer convention used by existing examples. |
| invariants | Warnings are errors; this declaration is not evidence that a build was executed or that all compilers understand these flags. |
| ownership | Flags belong to this executable only. |
| failure | Unsupported flags or diagnostics fail compilation. |
| cost | Compile-time diagnostics only; no runtime checks are inserted here. |
| Design | [docs/measurement.md](../../../../measurement.md), [build/verification/v58-b04-design-review-v1/README.md](../../../../../build/verification/v58-b04-design-review-v1/README.md) |
