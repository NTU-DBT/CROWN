# `examples/independent-queries/CMakeLists.txt` — block usage map

[Source](../../../../../examples/independent-queries/CMakeLists.txt) · [Source index](../../../README.md) · [Subsystem contracts](../../../subsystem_contracts.md) · [Reviewed primitives](../../../primitives.md)

Define native target boundaries, pinned dependencies, compilation options, installation and test registration.

Snapshot SHA-256: `c10ab16bc36efa116a098ac9f11b8831562dbe24c265ac66deb0fcf2112e9dce`. 8 lines partitioned into 8 blocks using `cmake_commands`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [build](../../../subsystem_contracts.md#build). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/native_build.md](../../../../native_build.md), [docs/source_baselines.md](../../../../source_baselines.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–1](../../../../../examples/independent-queries/CMakeLists.txt#L1) | CMake command: cmake_minimum_required(VERSION 3.25) |  · [reviewed contract](#b0001) |
| [B0002 · 2–2](../../../../../examples/independent-queries/CMakeLists.txt#L2) | CMake command: project(crown_independent_queries_example LANGUAGES CXX) |  · [reviewed contract](#b0002) |
| [B0003 · 3–3](../../../../../examples/independent-queries/CMakeLists.txt#L3) | CMake command: set(CMAKE_EXPORT_COMPILE_COMMANDS ON) |  · [reviewed contract](#b0003) |
| [B0004 · 4–4](../../../../../examples/independent-queries/CMakeLists.txt#L4) | CMake command: find_package(Crown 0.1 CONFIG REQUIRED) |  · [reviewed contract](#b0004) |
| [B0005 · 5–5](../../../../../examples/independent-queries/CMakeLists.txt#L5) | CMake command: add_executable(crown_independent_queries main.cpp) |  · [reviewed contract](#b0005) |
| [B0006 · 6–6](../../../../../examples/independent-queries/CMakeLists.txt#L6) | CMake command: set_target_properties(crown_independent_queries PROPERTIES CXX_EXTENSIONS OFF) |  · [reviewed contract](#b0006) |
| [B0007 · 7–7](../../../../../examples/independent-queries/CMakeLists.txt#L7) | CMake command: target_link_libraries(crown_independent_queries PRIVATE CROWN::queries) |  · [reviewed contract](#b0007) |
| [B0008 · 8–8](../../../../../examples/independent-queries/CMakeLists.txt#L8) | CMake command: target_compile_options(crown_independent_queries PRIVATE -Wall -Wextra -Wpedantic -Wconversion -Wsign-conversion -Werror) |  · [reviewed contract](#b0008) |

## B0001

[Lines 1–1](../../../../../examples/independent-queries/CMakeLists.txt#L1); `build-command`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L1-L1:sha256:864a28dfe13a0c73206b6838977d8ca0acc5f9ec8da56f4e6f3aa70dae47ea49
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Require the supported consumer CMake version. |
| inputs / outputs | CMake3.25 minimum. |
| invariants | Modern imported target semantics available. |
| ownership | Build configuration only. |
| failure | Older CMake rejects. |
| cost | Configure only. |
| Design | [docs/independent_queries.md](../../../../independent_queries.md), [Refactor.md §X10](../../../../../Refactor.md), [include/crown/runtime/session.hpp](../../../../../include/crown/runtime/session.hpp), [docs/query_memory.md](../../../../query_memory.md) |

## B0002

[Lines 2–2](../../../../../examples/independent-queries/CMakeLists.txt#L2); `build-command`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L2-L2:sha256:84421d7a1260c7a9e925d95bc47264f209db457e205d34ac24228165a509ed69
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Define a standalone C++ consumer project. |
| inputs / outputs | Project name and CXX language. |
| invariants | Consumer can configure outside the producer tree. |
| ownership | Independent build directory. |
| failure | Compiler detection failure rejects. |
| cost | Configure only. |
| Design | [docs/independent_queries.md](../../../../independent_queries.md), [Refactor.md §X10](../../../../../Refactor.md), [include/crown/runtime/session.hpp](../../../../../include/crown/runtime/session.hpp), [docs/query_memory.md](../../../../query_memory.md) |

## B0003

[Lines 3–3](../../../../../examples/independent-queries/CMakeLists.txt#L3); `build-command`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L3-L3:sha256:fd42900c4221089d0da87c8fc3b96f806a4dc984fe488afa6da9d399d5b66d4c
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Retain exact consumer compiler arguments for install isolation inspection. |
| inputs / outputs | CMAKE_EXPORT_COMPILE_COMMANDS enabled. |
| invariants | Compile database records installed include/standard flags. |
| ownership | Build tree owns generated JSON. |
| failure | Generator behavior follows CMake contract. |
| cost | Small build-time metadata only. |
| Design | [docs/independent_queries.md](../../../../independent_queries.md), [Refactor.md §X10](../../../../../Refactor.md), [include/crown/runtime/session.hpp](../../../../../include/crown/runtime/session.hpp), [docs/query_memory.md](../../../../query_memory.md) |

## B0004

[Lines 4–4](../../../../../examples/independent-queries/CMakeLists.txt#L4); `build-command`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L4-L4:sha256:7aba7d5c1cfa13193c246b121112e4cadbe127f878172857fb11dc0345bbb8d4
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Resolve the installed versioned Crown package. |
| inputs / outputs | Crown0.1 CONFIG REQUIRED. |
| invariants | No source-tree fallback dependency is declared. |
| ownership | Imported targets borrow relocated SDK files. |
| failure | Missing/incompatible package rejects configuration. |
| cost | Configure lookup only. |
| Design | [docs/independent_queries.md](../../../../independent_queries.md), [Refactor.md §X10](../../../../../Refactor.md), [include/crown/runtime/session.hpp](../../../../../include/crown/runtime/session.hpp), [docs/query_memory.md](../../../../query_memory.md) |

## B0005

[Lines 5–5](../../../../../examples/independent-queries/CMakeLists.txt#L5); `build-command`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L5-L5:sha256:d9c1918dfd3c92a9858cede993c675bcbdbac4d8e1793e8acc129042936f9be7
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Build the standalone public directory example. |
| inputs / outputs | main.cpp to crown_independent_queries executable. |
| invariants | No private source implementation is compiled into the consumer. |
| ownership | Consumer build owns object/executable. |
| failure | Compile/link failure is visible. |
| cost | One consumer translation unit. |
| Design | [docs/independent_queries.md](../../../../independent_queries.md), [Refactor.md §X10](../../../../../Refactor.md), [include/crown/runtime/session.hpp](../../../../../include/crown/runtime/session.hpp), [docs/query_memory.md](../../../../query_memory.md) |

## B0006

[Lines 6–6](../../../../../examples/independent-queries/CMakeLists.txt#L6); `build-command`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L6-L6:sha256:1b803d2b85fe1837675442f30314a78cd5fa748fd3aa3988dfaed3e0b0690148
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Select standard C++ without compiler language extensions. |
| inputs / outputs | CXX_EXTENSIONS OFF. |
| invariants | Imported target supplies C++23 requirement. |
| ownership | Target property only. |
| failure | Unsupported compiler rejects. |
| cost | No runtime cost. |
| Design | [docs/independent_queries.md](../../../../independent_queries.md), [Refactor.md §X10](../../../../../Refactor.md), [include/crown/runtime/session.hpp](../../../../../include/crown/runtime/session.hpp), [docs/query_memory.md](../../../../query_memory.md) |

## B0007

[Lines 7–7](../../../../../examples/independent-queries/CMakeLists.txt#L7); `build-command`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L7-L7:sha256:80284cf3b040b6f8913c37deefb6578e331f3cd60bc3cfc6869005def72164f9
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Link the optional installed serial directory target. |
| inputs / outputs | CROWN::queries imported target. |
| invariants | Transitive public dependencies supply only the normal installed library closure. |
| ownership | Link result owns ordinary executable bytes. |
| failure | Missing archive/symbol rejects linking. |
| cost | No runtime dispatch added by linking. |
| Design | [docs/independent_queries.md](../../../../independent_queries.md), [Refactor.md §X10](../../../../../Refactor.md), [include/crown/runtime/session.hpp](../../../../../include/crown/runtime/session.hpp), [docs/query_memory.md](../../../../query_memory.md) |

## B0008

[Lines 8–8](../../../../../examples/independent-queries/CMakeLists.txt#L8); `build-command`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L8-L8:sha256:ea70cd0419e8707036af24085444bed3bc59d7df5f4a06decb5c26fe50240553
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Enforce strict warnings for this consumer code. |
| inputs / outputs | Wall,Wextra,Wpedantic,Wconversion,Wsign-conversion,Werror. |
| invariants | Consumer source must compile without warnings. |
| ownership | Compile options only. |
| failure | Warnings fail compilation. |
| cost | Compile-time diagnostics; no runtime instrumentation. |
| Design | [docs/independent_queries.md](../../../../independent_queries.md), [Refactor.md §X10](../../../../../Refactor.md), [include/crown/runtime/session.hpp](../../../../../include/crown/runtime/session.hpp), [docs/query_memory.md](../../../../query_memory.md) |
