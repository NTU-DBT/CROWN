# `examples/cost-calibration/CMakeLists.txt` — block usage map

[Source](../../../../../examples/cost-calibration/CMakeLists.txt) · [Source index](../../../README.md) · [Subsystem contracts](../../../subsystem_contracts.md) · [Reviewed primitives](../../../primitives.md)

Define native target boundaries, pinned dependencies, compilation options, installation and test registration.

Snapshot SHA-256: `c97ccb68f31dc27bcb8e17ac788a6ce3c5dd13d7ce42fb8afc45cc71dc2dad7d`. 8 lines partitioned into 8 blocks using `cmake_commands`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [build](../../../subsystem_contracts.md#build). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/native_build.md](../../../../native_build.md), [docs/source_baselines.md](../../../../source_baselines.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–1](../../../../../examples/cost-calibration/CMakeLists.txt#L1) | CMake command: cmake_minimum_required(VERSION 3.25) |  · [reviewed contract](#b0001) |
| [B0002 · 2–2](../../../../../examples/cost-calibration/CMakeLists.txt#L2) | CMake command: project(crown_cost_calibration LANGUAGES CXX) |  · [reviewed contract](#b0002) |
| [B0003 · 3–3](../../../../../examples/cost-calibration/CMakeLists.txt#L3) | CMake command: set(CMAKE_CXX_EXTENSIONS OFF) |  · [reviewed contract](#b0003) |
| [B0004 · 4–4](../../../../../examples/cost-calibration/CMakeLists.txt#L4) | CMake command: set(CMAKE_EXPORT_COMPILE_COMMANDS ON) |  · [reviewed contract](#b0004) |
| [B0005 · 5–5](../../../../../examples/cost-calibration/CMakeLists.txt#L5) | CMake command: find_package(Crown 0.1 CONFIG REQUIRED) |  · [reviewed contract](#b0005) |
| [B0006 · 6–6](../../../../../examples/cost-calibration/CMakeLists.txt#L6) | CMake command: add_executable(crown_cost_calibrate main.cpp) |  · [reviewed contract](#b0006) |
| [B0007 · 7–7](../../../../../examples/cost-calibration/CMakeLists.txt#L7) | CMake command: target_link_libraries(crown_cost_calibrate PRIVATE CROWN::ranking_runtime) |  · [reviewed contract](#b0007) |
| [B0008 · 8–8](../../../../../examples/cost-calibration/CMakeLists.txt#L8) | CMake command: target_compile_options(crown_cost_calibrate PRIVATE -Wall -Wextra -Wpedantic -Wconversion -Wsign-conversion -Werror) |  · [reviewed contract](#b0008) |

## B0001

[Lines 1–1](../../../../../examples/cost-calibration/CMakeLists.txt#L1); `build-command`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
cmake_minimum_required(VERSION 3.25)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Set the external consumer minimum CMake/policy baseline. |
| inputs / outputs | CMake version &gt;=3.25; configures this standalone example project. |
| invariants | No native library/example is executed by this command. |
| ownership | CMake stores configure/generate metadata and imported target references; no runtime row, query account, stream or durable lock is owned. |
| failure | Older CMake stops configuration. |
| cost | Configure/generate/build-time metadata or compiler/link work only; no per-input runtime wrapper or handler is added. |
| Design | [examples/cost-calibration/CMakeLists.txt](../../../../../examples/cost-calibration/CMakeLists.txt), [cmake/CrownInstall.cmake](../../../../../cmake/CrownInstall.cmake), [cmake/CrownConfig.cmake.in](../../../../../cmake/CrownConfig.cmake.in), [CMakeLists.txt](../../../../../CMakeLists.txt), [docs/native_build.md](../../../../native_build.md) |

## B0002

[Lines 2–2](../../../../../examples/cost-calibration/CMakeLists.txt#L2); `build-command`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
project(crown_cost_calibration LANGUAGES CXX)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Name the standalone installed-package consumer and enable C++. |
| inputs / outputs | project(crown_cost_calibration LANGUAGES CXX) |
| invariants | This is a separate consumer project, not the source-tree test build. |
| ownership | CMake stores configure/generate metadata and imported target references; no runtime row, query account, stream or durable lock is owned. |
| failure | Compiler/toolchain discovery or language checks can fail at configure time. |
| cost | Configure/generate/build-time metadata or compiler/link work only; no per-input runtime wrapper or handler is added. |
| Design | [examples/cost-calibration/CMakeLists.txt](../../../../../examples/cost-calibration/CMakeLists.txt), [cmake/CrownInstall.cmake](../../../../../cmake/CrownInstall.cmake), [cmake/CrownConfig.cmake.in](../../../../../cmake/CrownConfig.cmake.in), [CMakeLists.txt](../../../../../CMakeLists.txt), [docs/native_build.md](../../../../native_build.md) |

## B0003

[Lines 3–3](../../../../../examples/cost-calibration/CMakeLists.txt#L3); `build-command`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
set(CMAKE_CXX_EXTENSIONS OFF)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Request standard C++ dialect instead of compiler extensions for created targets. |
| inputs / outputs | CMAKE_CXX_EXTENSIONS OFF before add_executable. |
| invariants | The C++23 feature requirement comes transitively from exported crown_core, not a local -std flag. |
| ownership | CMake stores configure/generate metadata and imported target references; no runtime row, query account, stream or durable lock is owned. |
| failure | No runtime failure; unsupported compiler features fail configure/build. |
| cost | Configure/generate/build-time metadata or compiler/link work only; no per-input runtime wrapper or handler is added. |
| Design | [examples/cost-calibration/CMakeLists.txt](../../../../../examples/cost-calibration/CMakeLists.txt), [cmake/CrownInstall.cmake](../../../../../cmake/CrownInstall.cmake), [cmake/CrownConfig.cmake.in](../../../../../cmake/CrownConfig.cmake.in), [CMakeLists.txt](../../../../../CMakeLists.txt), [docs/native_build.md](../../../../native_build.md) |

## B0004

[Lines 4–4](../../../../../examples/cost-calibration/CMakeLists.txt#L4); `build-command`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Request a compile-command inventory for the external consumer. |
| inputs / outputs | CMAKE_EXPORT_COMPILE_COMMANDS ON. |
| invariants | Generator support determines compile_commands.json emission; it does not certify execution provenance. |
| ownership | CMake stores configure/generate metadata and imported target references; no runtime row, query account, stream or durable lock is owned. |
| failure | No native runtime action; generation/file IO can fail. |
| cost | Configure/generate/build-time metadata or compiler/link work only; no per-input runtime wrapper or handler is added. |
| Design | [examples/cost-calibration/CMakeLists.txt](../../../../../examples/cost-calibration/CMakeLists.txt), [cmake/CrownInstall.cmake](../../../../../cmake/CrownInstall.cmake), [cmake/CrownConfig.cmake.in](../../../../../cmake/CrownConfig.cmake.in), [CMakeLists.txt](../../../../../CMakeLists.txt), [docs/native_build.md](../../../../native_build.md) |

## B0005

[Lines 5–5](../../../../../examples/cost-calibration/CMakeLists.txt#L5); `build-command`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
find_package(Crown 0.1 CONFIG REQUIRED)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Resolve the installed Crown package configuration and exported production targets. |
| inputs / outputs | Crown 0.1 CONFIG REQUIRED, usually through CMAKE_PREFIX_PATH or Crown_DIR. |
| invariants | Uses package version compatibility and transitive dependencies; no test/reference ABI is requested. |
| ownership | CMake stores configure/generate metadata and imported target references; no runtime row, query account, stream or durable lock is owned. |
| failure | Missing/incompatible package or required transitive dependency stops configuration. |
| cost | Configure/generate/build-time metadata or compiler/link work only; no per-input runtime wrapper or handler is added. |
| Design | [examples/cost-calibration/CMakeLists.txt](../../../../../examples/cost-calibration/CMakeLists.txt), [cmake/CrownInstall.cmake](../../../../../cmake/CrownInstall.cmake), [cmake/CrownConfig.cmake.in](../../../../../cmake/CrownConfig.cmake.in), [CMakeLists.txt](../../../../../CMakeLists.txt), [docs/native_build.md](../../../../native_build.md) |

## B0006

[Lines 6–6](../../../../../examples/cost-calibration/CMakeLists.txt#L6); `build-command`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
add_executable(crown_cost_calibrate main.cpp)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Declare one public example executable from its main.cpp. |
| inputs / outputs | add_executable(crown_cost_calibrate main.cpp) |
| invariants | No fixture generator/test registration/source-private target is required by this project. |
| ownership | CMake stores configure/generate metadata and imported target references; no runtime row, query account, stream or durable lock is owned. |
| failure | Missing source/compiler/link errors surface during generation/build. |
| cost | Configure/generate/build-time metadata or compiler/link work only; no per-input runtime wrapper or handler is added. |
| Design | [examples/cost-calibration/CMakeLists.txt](../../../../../examples/cost-calibration/CMakeLists.txt), [cmake/CrownInstall.cmake](../../../../../cmake/CrownInstall.cmake), [cmake/CrownConfig.cmake.in](../../../../../cmake/CrownConfig.cmake.in), [CMakeLists.txt](../../../../../CMakeLists.txt), [docs/native_build.md](../../../../native_build.md) |

## B0007

[Lines 7–7](../../../../../examples/cost-calibration/CMakeLists.txt#L7); `build-command`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
target_link_libraries(crown_cost_calibrate PRIVATE CROWN::ranking_runtime)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Link the production public API closure needed by this example. |
| inputs / outputs | PRIVATE CROWN::ranking_runtime; imported includes/features/libraries propagate to this executable. |
| invariants | explain supplies report/runtime APIs; ranking_runtime supplies cost/evidence/runtime APIs; selection_runtime supplies optional C05/runtime bridge; runtime collector uses runtime only. PRIVATE does not expose an example library API. |
| ownership | CMake stores configure/generate metadata and imported target references; no runtime row, query account, stream or durable lock is owned. |
| failure | Missing imported target or unresolved production dependencies fail configure/link. |
| cost | Configure/generate/build-time metadata or compiler/link work only; no per-input runtime wrapper or handler is added. |
| Design | [examples/cost-calibration/CMakeLists.txt](../../../../../examples/cost-calibration/CMakeLists.txt), [cmake/CrownInstall.cmake](../../../../../cmake/CrownInstall.cmake), [cmake/CrownConfig.cmake.in](../../../../../cmake/CrownConfig.cmake.in), [CMakeLists.txt](../../../../../CMakeLists.txt), [docs/native_build.md](../../../../native_build.md) |

## B0008

[Lines 8–8](../../../../../examples/cost-calibration/CMakeLists.txt#L8); `build-command`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
target_compile_options(crown_cost_calibrate PRIVATE -Wall -Wextra -Wpedantic -Wconversion -Wsign-conversion -Werror)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Compile the example with strict GNU/Clang warning diagnostics treated as errors. |
| inputs / outputs | PRIVATE -Wall -Wextra -Wpedantic -Wconversion -Wsign-conversion -Werror. |
| invariants | Compiler-specific options are intentionally those used by supported tested toolchains; no portability or performance flag guarantee. |
| ownership | CMake stores configure/generate metadata and imported target references; no runtime row, query account, stream or durable lock is owned. |
| failure | Unsupported option or emitted warning fails build. |
| cost | Configure/generate/build-time metadata or compiler/link work only; no per-input runtime wrapper or handler is added. |
| Design | [examples/cost-calibration/CMakeLists.txt](../../../../../examples/cost-calibration/CMakeLists.txt), [cmake/CrownInstall.cmake](../../../../../cmake/CrownInstall.cmake), [cmake/CrownConfig.cmake.in](../../../../../cmake/CrownConfig.cmake.in), [CMakeLists.txt](../../../../../CMakeLists.txt), [docs/native_build.md](../../../../native_build.md) |
