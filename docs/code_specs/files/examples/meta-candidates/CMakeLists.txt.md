# `examples/meta-candidates/CMakeLists.txt` — block usage map

[Source](../../../../../examples/meta-candidates/CMakeLists.txt) · [Source index](../../../README.md) · [Subsystem contracts](../../../subsystem_contracts.md) · [Reviewed primitives](../../../primitives.md)

Define native target boundaries, pinned dependencies, compilation options, installation and test registration.

Snapshot SHA-256: `397331adfae2919c3fe2a4d755bfda623c9a8ea607036520a3312af251486fe7`. 8 lines partitioned into 8 blocks using `cmake_commands`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [build](../../../subsystem_contracts.md#build). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/native_build.md](../../../../native_build.md), [docs/source_baselines.md](../../../../source_baselines.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–1](../../../../../examples/meta-candidates/CMakeLists.txt#L1) | CMake command: cmake_minimum_required(VERSION 3.25) |  · [reviewed contract](#b0001) |
| [B0002 · 2–2](../../../../../examples/meta-candidates/CMakeLists.txt#L2) | CMake command: project(crown_meta_candidate_example LANGUAGES CXX) |  · [reviewed contract](#b0002) |
| [B0003 · 3–3](../../../../../examples/meta-candidates/CMakeLists.txt#L3) | CMake command: set(CMAKE_CXX_EXTENSIONS OFF) |  · [reviewed contract](#b0003) |
| [B0004 · 4–4](../../../../../examples/meta-candidates/CMakeLists.txt#L4) | CMake command: set(CMAKE_EXPORT_COMPILE_COMMANDS ON) |  · [reviewed contract](#b0004) |
| [B0005 · 5–5](../../../../../examples/meta-candidates/CMakeLists.txt#L5) | CMake command: find_package(Crown 0.1 CONFIG REQUIRED) |  · [reviewed contract](#b0005) |
| [B0006 · 6–6](../../../../../examples/meta-candidates/CMakeLists.txt#L6) | CMake command: add_executable(crown_meta_candidate_example main.cpp) |  · [reviewed contract](#b0006) |
| [B0007 · 7–7](../../../../../examples/meta-candidates/CMakeLists.txt#L7) | CMake command: target_link_libraries(crown_meta_candidate_example PRIVATE CROWN::meta_candidates) |  · [reviewed contract](#b0007) |
| [B0008 · 8–8](../../../../../examples/meta-candidates/CMakeLists.txt#L8) | CMake command: target_compile_options(crown_meta_candidate_example PRIVATE -Wall -Wextra -Wpedantic -Wconversion -Wsign-conversion -Werror) |  · [reviewed contract](#b0008) |

## B0001

[Lines 1–1](../../../../../examples/meta-candidates/CMakeLists.txt#L1); `build-command`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L1-L1:sha256:864a28dfe13a0c73206b6838977d8ca0acc5f9ec8da56f4e6f3aa70dae47ea49
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Require CMake 3.25 or newer for this standalone installed-consumer example. |
| inputs / outputs | Sets the minimum CMake version for the project. |
| invariants | Configuration below the declared version is unsupported by this project file. |
| ownership | Configuration metadata only. |
| failure | Older CMake rejects configuration. |
| cost | Configuration-time version check. |
| Design | [examples/meta-candidates/main.cpp](../../../../../examples/meta-candidates/main.cpp) |

## B0002

[Lines 2–2](../../../../../examples/meta-candidates/CMakeLists.txt#L2); `build-command`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L2-L2:sha256:aed7dd81f526dc45118bcb2ba269075cdf63d797c23372ab67284712e961c05d
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Declare the example as an independent C++ consumer project. |
| inputs / outputs | Creates project crown_meta_candidate_example with only the CXX language enabled. |
| invariants | The project is configured separately from the repository build and discovers Crown as an installed package. |
| ownership | CMake project scope only. |
| failure | CMake/compiler discovery failures stop configuration. |
| cost | Project configuration and compiler discovery only. |
| Design | [tests/integration/installed_meta_candidates.py](../../../../../tests/integration/installed_meta_candidates.py) |

## B0003

[Lines 3–3](../../../../../examples/meta-candidates/CMakeLists.txt#L3); `build-command`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L3-L3:sha256:caba43b0dd00df194eee70c6a4bb7999acec17d31058583e21c35fe710806d42
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Disable compiler-specific C++ language extensions for the example target. |
| inputs / outputs | Sets CMAKE_CXX_EXTENSIONS OFF for consumers in this project. |
| invariants | The target is expected to compile as standard C++ rather than GNU/Clang extension mode. |
| ownership | CMake target/project configuration; no runtime state. |
| failure | Unsupported standard mode is surfaced during generation or compile. |
| cost | No additional build step beyond selecting the language mode. |
| Design | [tests/integration/installed_meta_candidates.py](../../../../../tests/integration/installed_meta_candidates.py) |

## B0004

[Lines 4–4](../../../../../examples/meta-candidates/CMakeLists.txt#L4); `build-command`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L4-L4:sha256:fd42900c4221089d0da87c8fc3b96f806a4dc984fe488afa6da9d399d5b66d4c
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Ask CMake to emit compile_commands.json for source-isolation inspection. |
| inputs / outputs | Enables CMAKE_EXPORT_COMPILE_COMMANDS. |
| invariants | The integration test inspects the actual compile entry for standard and repository-path leakage. |
| ownership | Generated file belongs to the temporary consumer build. |
| failure | A missing or malformed compile database fails the integration check. |
| cost | Small configure-time metadata output; no extra planner work. |
| Design | [tests/integration/installed_meta_candidates.py](../../../../../tests/integration/installed_meta_candidates.py) |

## B0005

[Lines 5–5](../../../../../examples/meta-candidates/CMakeLists.txt#L5); `build-command`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L5-L5:sha256:7aba7d5c1cfa13193c246b121112e4cadbe127f878172857fb11dc0345bbb8d4
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Find the installed Crown 0.1 package through its config package metadata. |
| inputs / outputs | find_package requires Crown version 0.1 in CONFIG mode. |
| invariants | The consumer relies on exported package targets rather than repository include paths. |
| ownership | CMake imports target metadata into the consumer configuration. |
| failure | Missing package/config or incompatible version stops configuration. |
| cost | Package discovery/configuration only. |
| Design | [cmake/CrownInstall.cmake](../../../../../cmake/CrownInstall.cmake), [tests/integration/installed_meta_candidates.py](../../../../../tests/integration/installed_meta_candidates.py) |

## B0006

[Lines 6–6](../../../../../examples/meta-candidates/CMakeLists.txt#L6); `build-command`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L6-L6:sha256:de2a04303df3682151c7b3e879e4711272660baa036fdfc9fc11b0b23b721eb9
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Define the standalone executable from the public example source. |
| inputs / outputs | Creates crown_meta_candidate_example from main.cpp. |
| invariants | The source is built as a separate consumer executable after copying the installed example into the temporary consumer tree. |
| ownership | The executable target is owned by this CMake project. |
| failure | Missing source/compiler errors stop the build. |
| cost | Compiles the small example translation unit and its linked dependencies. |
| Design | [examples/meta-candidates/main.cpp](../../../../../examples/meta-candidates/main.cpp), [tests/integration/installed_meta_candidates.py](../../../../../tests/integration/installed_meta_candidates.py) |

## B0007

[Lines 7–7](../../../../../examples/meta-candidates/CMakeLists.txt#L7); `build-command`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L7-L7:sha256:2cf9e8a2e5ab25cff903e23f202b03361fd597725ec0ef0fa5741ba6891e901c
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Link the consumer only through the exported CROWN::meta_candidates target. |
| inputs / outputs | Adds CROWN::meta_candidates as a PRIVATE link dependency of the executable. |
| invariants | The package target supplies the intended public usage requirements; the test checks no repository include root leaks into compilation. |
| ownership | CMake manages imported target linkage and transitive usage requirements. |
| failure | Missing exported target or link failure stops the consumer build. |
| cost | Links the optional library and its declared dependencies; no runtime complexity claim. |
| Design | [cmake/CrownInstall.cmake](../../../../../cmake/CrownInstall.cmake), [docs/meta_candidate_adapter.md](../../../../meta_candidate_adapter.md) |

## B0008

[Lines 8–8](../../../../../examples/meta-candidates/CMakeLists.txt#L8); `build-command`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L8-L8:sha256:d45f84756e00a9ef74826f98f07b4de6760e2f24231018e624ad9143a3cb6e94
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Compile the example with strict warnings and treat warnings as errors. |
| inputs / outputs | Adds Wall, Wextra, Wpedantic, conversion, and sign-conversion warning flags plus Werror. |
| invariants | These flags make the installed-consumer sample sensitive to common diagnostics for the configured compiler. |
| ownership | Compiler invocation options only. |
| failure | Any enabled warning fails compilation because Werror is set. |
| cost | Compiler diagnostic work only; exact warning behavior remains toolchain-dependent. |
| Design | [tests/integration/installed_meta_candidates.py](../../../../../tests/integration/installed_meta_candidates.py) |
