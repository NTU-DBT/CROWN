# `examples/component-runtime/CMakeLists.txt` — block usage map

[Source](../../../../../examples/component-runtime/CMakeLists.txt) · [Source index](../../../README.md) · [Subsystem contracts](../../../subsystem_contracts.md) · [Reviewed primitives](../../../primitives.md)

Define native target boundaries, pinned dependencies, compilation options, installation and test registration.

Snapshot SHA-256: `e71215107b8ff3050c00e744b433123c4d0e863a8680423e680ef9c8c0d4d818`. 41 lines partitioned into 34 blocks using `cmake_commands`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [build](../../../subsystem_contracts.md#build). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/native_build.md](../../../../native_build.md), [docs/source_baselines.md](../../../../source_baselines.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–1](../../../../../examples/component-runtime/CMakeLists.txt#L1) | CMake command: cmake_minimum_required(VERSION 3.25) |  · [reviewed contract](#b0001) |
| [B0002 · 2–2](../../../../../examples/component-runtime/CMakeLists.txt#L2) | CMake command: project(crown_component_runtime LANGUAGES CXX) |  · [reviewed contract](#b0002) |
| [B0003 · 3–3](../../../../../examples/component-runtime/CMakeLists.txt#L3) | CMake command: find_package(Crown 0.1 CONFIG REQUIRED) |  · [reviewed contract](#b0003) |
| [B0004 · 4–4](../../../../../examples/component-runtime/CMakeLists.txt#L4) | Explanatory comments or spacing. |  |
| [B0005 · 5–5](../../../../../examples/component-runtime/CMakeLists.txt#L5) | CMake command: foreach(_component IN ITEMS set rows session aggregate) |  · [reviewed contract](#b0005) |
| [B0006 · 6–6](../../../../../examples/component-runtime/CMakeLists.txt#L6) | CMake command: if(_component STREQUAL "set") |  · [reviewed contract](#b0006) |
| [B0007 · 7–7](../../../../../examples/component-runtime/CMakeLists.txt#L7) | CMake command: set(_source native_set.cpp) |  · [reviewed contract](#b0007) |
| [B0008 · 8–8](../../../../../examples/component-runtime/CMakeLists.txt#L8) | CMake command: elseif(_component STREQUAL "rows") |  · [reviewed contract](#b0008) |
| [B0009 · 9–9](../../../../../examples/component-runtime/CMakeLists.txt#L9) | CMake command: set(_source native_rows.cpp) |  · [reviewed contract](#b0009) |
| [B0010 · 10–10](../../../../../examples/component-runtime/CMakeLists.txt#L10) | CMake command: else() |  · [reviewed contract](#b0010) |
| [B0011 · 11–11](../../../../../examples/component-runtime/CMakeLists.txt#L11) | CMake command: set(_source "${_component}.cpp") |  · [reviewed contract](#b0011) |
| [B0012 · 12–12](../../../../../examples/component-runtime/CMakeLists.txt#L12) | CMake command: endif() |  · [reviewed contract](#b0012) |
| [B0013 · 13–13](../../../../../examples/component-runtime/CMakeLists.txt#L13) | CMake command: add_executable("crown_component_${_component}" "${_source}") |  · [reviewed contract](#b0013) |
| [B0014 · 14–14](../../../../../examples/component-runtime/CMakeLists.txt#L14) | CMake command: set_target_properties("crown_component_${_component}" PROPERTIES CXX_EXTENSIONS OFF) |  · [reviewed contract](#b0014) |
| [B0015 · 15–15](../../../../../examples/component-runtime/CMakeLists.txt#L15) | CMake command: if(_component STREQUAL "aggregate") |  · [reviewed contract](#b0015) |
| [B0016 · 16–16](../../../../../examples/component-runtime/CMakeLists.txt#L16) | CMake command: target_link_libraries("crown_component_${_component}" PRIVATE CROWN::sql_aggregate_runtime) |  · [reviewed contract](#b0016) |
| [B0017 · 17–17](../../../../../examples/component-runtime/CMakeLists.txt#L17) | CMake command: elseif(_component STREQUAL "rows") |  · [reviewed contract](#b0017) |
| [B0018 · 18–18](../../../../../examples/component-runtime/CMakeLists.txt#L18) | CMake command: target_link_libraries("crown_component_${_component}" PRIVATE CROWN::sql_rows) |  · [reviewed contract](#b0018) |
| [B0019 · 19–19](../../../../../examples/component-runtime/CMakeLists.txt#L19) | CMake command: else() |  · [reviewed contract](#b0019) |
| [B0020 · 20–20](../../../../../examples/component-runtime/CMakeLists.txt#L20) | CMake command: target_link_libraries("crown_component_${_component}" PRIVATE CROWN::runtime) |  · [reviewed contract](#b0020) |
| [B0021 · 21–21](../../../../../examples/component-runtime/CMakeLists.txt#L21) | CMake command: endif() |  · [reviewed contract](#b0021) |
| [B0022 · 22–22](../../../../../examples/component-runtime/CMakeLists.txt#L22) | CMake command: target_compile_options("crown_component_${_component}" PRIVATE -Wall -Wextra -Wpedantic -Wconversion -Wsign-conversion -Werror) |  · [reviewed contract](#b0022) |
| [B0023 · 23–23](../../../../../examples/component-runtime/CMakeLists.txt#L23) | CMake command: endforeach() |  · [reviewed contract](#b0023) |
| [B0024 · 24–26](../../../../../examples/component-runtime/CMakeLists.txt#L24) | Member/declaration region. | source comment (unverified): # The optional observer links separately qualified original libraries unchanged. · [reviewed contract](#b0024) |
| [B0025 · 27–27](../../../../../examples/component-runtime/CMakeLists.txt#L27) | CMake command: set(CROWN_LEGACY_CPP_SOURCE "" CACHE PATH "Pinned DynaGox dynagox_cpp/implement source") |  · [reviewed contract](#b0025) |
| [B0026 · 28–28](../../../../../examples/component-runtime/CMakeLists.txt#L28) | CMake command: set(CROWN_LEGACY_CPP_BUILD "" CACHE PATH "Qualified original C++ baseline build") |  · [reviewed contract](#b0026) |
| [B0027 · 29–29](../../../../../examples/component-runtime/CMakeLists.txt#L29) | CMake command: set(CROWN_LEGACY_FMT_SOURCE "" CACHE PATH "Pinned fmt source used by that baseline") |  · [reviewed contract](#b0027) |
| [B0028 · 30–30](../../../../../examples/component-runtime/CMakeLists.txt#L30) | CMake command: if(CROWN_LEGACY_CPP_SOURCE AND CROWN_LEGACY_CPP_BUILD AND CROWN_LEGACY_FMT_SOURCE) |  · [reviewed contract](#b0028) |
| [B0029 · 31–31](../../../../../examples/component-runtime/CMakeLists.txt#L31) | CMake command: add_executable(crown_component_legacy_cpp legacy_cpp.cpp) |  · [reviewed contract](#b0029) |
| [B0030 · 32–32](../../../../../examples/component-runtime/CMakeLists.txt#L32) | CMake command: set_target_properties(crown_component_legacy_cpp PROPERTIES CXX_EXTENSIONS OFF) |  · [reviewed contract](#b0030) |
| [B0031 · 33–36](../../../../../examples/component-runtime/CMakeLists.txt#L33) | CMake command: target_include_directories(crown_component_legacy_cpp SYSTEM PRIVATE |  · [reviewed contract](#b0031) |
| [B0032 · 37–39](../../../../../examples/component-runtime/CMakeLists.txt#L37) | CMake command: target_link_libraries(crown_component_legacy_cpp PRIVATE CROWN::core CROWN::json |  · [reviewed contract](#b0032) |
| [B0033 · 40–40](../../../../../examples/component-runtime/CMakeLists.txt#L40) | CMake command: target_compile_options(crown_component_legacy_cpp PRIVATE -Wall -Wextra -Wpedantic -Wconversion -Wsign-conversion -Werror) |  · [reviewed contract](#b0033) |
| [B0034 · 41–41](../../../../../examples/component-runtime/CMakeLists.txt#L41) | CMake command: endif() |  · [reviewed contract](#b0034) |

## B0001

[Lines 1–1](../../../../../examples/component-runtime/CMakeLists.txt#L1); `build-command`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L1-L1:sha256:864a28dfe13a0c73206b6838977d8ca0acc5f9ec8da56f4e6f3aa70dae47ea49
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Require a CMake version that supports the target and export syntax used by this standalone consumer. |
| inputs / outputs | The CMake executable version is the input; configuration continues under the declared minimum. |
| invariants | The example uses only facilities available from CMake 3.25 onward. |
| ownership | CMake owns version admission before the project and package declarations run. |
| failure | An older CMake release stops configuration. |
| cost | One configure-time version check; no runtime work. |
| Design | [examples/component-runtime/CMakeLists.txt](../../../../../examples/component-runtime/CMakeLists.txt), [docs/native_build.md](../../../../native_build.md) |

## B0002

[Lines 2–2](../../../../../examples/component-runtime/CMakeLists.txt#L2); `build-command`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L2-L2:sha256:d40cd19ecc3fc3f7146e3076b997d9ea91bbe03ea4d84d0cab412d5f8e50c3d2
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Define a separate C++ consumer project for the component runtime examples. |
| inputs / outputs | Creates the \`crown_component_runtime\` project and enables the CXX language. |
| invariants | The consumer project is separate from the repository's top-level build. |
| ownership | CMake owns this consumer's project and language configuration. |
| failure | A missing C++ toolchain or invalid project configuration fails at configure time. |
| cost | Configure-time project declaration only. |
| Design | [examples/component-runtime/CMakeLists.txt](../../../../../examples/component-runtime/CMakeLists.txt) |

## B0003

[Lines 3–3](../../../../../examples/component-runtime/CMakeLists.txt#L3); `build-command`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L3-L3:sha256:7aba7d5c1cfa13193c246b121112e4cadbe127f878172857fb11dc0345bbb8d4
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Find the installed Crown package and require its 0.1 package version. |
| inputs / outputs | Consumes the package config and imported \`CROWN::\` targets. |
| invariants | No source-tree target or test helper is required by these consumer executables. |
| ownership | The package manager/config mode supplies the installed target namespace. |
| failure | Missing or incompatible Crown package configuration fails configuration. |
| cost | Package discovery is configure-time work; it has no runtime cost. |
| Design | [cmake/CrownInstall.cmake](../../../../../cmake/CrownInstall.cmake), [examples/component-runtime/CMakeLists.txt](../../../../../examples/component-runtime/CMakeLists.txt) |

## B0005

[Lines 5–5](../../../../../examples/component-runtime/CMakeLists.txt#L5); `build-command`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L5-L5:sha256:a098e4ed13cd5566dd92ef083f9b3e18f66b7037b8d96ad6012cef1ddc159215
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Enumerate the four built-in component executables from one fixed list. |
| inputs / outputs | Each loop value selects a source and imported link target, then receives shared executable properties. |
| invariants | The list is exactly \`set\`, \`rows\`, \`session\`, and \`aggregate\`. |
| ownership | CMake's loop variable is local to this directory's configure pass. |
| failure | An unhandled component could select a nonexistent source or wrong library; the list is intentionally fixed. |
| cost | Four configure-time iterations; it declares four executable targets. |
| Design | [examples/component-runtime/native_set.cpp](../../../../../examples/component-runtime/native_set.cpp), [examples/component-runtime/native_rows.cpp](../../../../../examples/component-runtime/native_rows.cpp), [examples/component-runtime/session.cpp](../../../../../examples/component-runtime/session.cpp), [examples/component-runtime/aggregate.cpp](../../../../../examples/component-runtime/aggregate.cpp) |

## B0006

[Lines 6–6](../../../../../examples/component-runtime/CMakeLists.txt#L6); `build-command`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L6-L6:sha256:74456e3afb0fb5a18c641eb1970e11da924c5b59971932bb6fc82dee100e3b46
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Select the explicit native-set source for the \`set\` component. |
| inputs / outputs | Branches on \`_component\` and assigns \`_source\`. |
| invariants | This special filename is kept distinct from the component name. |
| ownership | The loop owns the temporary \`_source\` selection. |
| failure | A changed loop item would require its source selection to be updated. |
| cost | One configure-time string comparison. |
| Design | [examples/component-runtime/native_set.cpp](../../../../../examples/component-runtime/native_set.cpp) |

## B0007

[Lines 7–7](../../../../../examples/component-runtime/CMakeLists.txt#L7); `build-command`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L7-L7:sha256:9fc1927d1487a201d23b772ec0634b6a5ba9176b6e732c81b0f85f9c195a1ad2
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Bind the set component to its native implementation file. |
| inputs / outputs | Sets \`_source\` to \`native_set.cpp\` for the active loop iteration. |
| invariants | The source path is relative to this example's CMakeLists directory. |
| ownership | CMake consumes the temporary value when declaring the executable. |
| failure | A missing source file causes target generation/build failure. |
| cost | One configure-time variable assignment. |
| Design | [examples/component-runtime/native_set.cpp](../../../../../examples/component-runtime/native_set.cpp) |

## B0008

[Lines 8–8](../../../../../examples/component-runtime/CMakeLists.txt#L8); `build-command`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L8-L8:sha256:36efe8788f5a5b8b0c009b2c0f11c492f188b63e2224d76f5f8a94cf9451246a
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Select the explicit SQL rows source for the \`rows\` component. |
| inputs / outputs | Branches on \`_component\` and assigns \`_source\`. |
| invariants | The distinct source name is \`native_rows.cpp\`. |
| ownership | The loop owns the temporary source selection. |
| failure | Changing the component key without changing this branch can select the wrong source. |
| cost | One configure-time string comparison. |
| Design | [examples/component-runtime/native_rows.cpp](../../../../../examples/component-runtime/native_rows.cpp) |

## B0009

[Lines 9–9](../../../../../examples/component-runtime/CMakeLists.txt#L9); `build-command`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L9-L9:sha256:fcb31051761f53e4ec4908cf06212e6104728fcedeead41c46798375190e63b5
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Bind the rows component to its native implementation file. |
| inputs / outputs | Sets \`_source\` to \`native_rows.cpp\`. |
| invariants | The executable source is local to the component-runtime example. |
| ownership | CMake consumes \`_source\` when the executable target is created. |
| failure | A missing source file causes target generation/build failure. |
| cost | One configure-time assignment. |
| Design | [examples/component-runtime/native_rows.cpp](../../../../../examples/component-runtime/native_rows.cpp) |

## B0010

[Lines 10–10](../../../../../examples/component-runtime/CMakeLists.txt#L10); `build-command`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L10-L10:sha256:903a8925883ccb65b88c616ab13c37ba428b36f74f2f18f165bcd5b8ecb8333e
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Use the component name as the source filename for session and aggregate. |
| inputs / outputs | Begins the default source-selection branch. |
| invariants | The branch applies to remaining fixed loop items after the set and rows cases. |
| ownership | CMake owns the branch-local selection. |
| failure | If new component keys are added, this default is valid only when a same-named source exists. |
| cost | One configure-time branch. |
| Design | [examples/component-runtime/session.cpp](../../../../../examples/component-runtime/session.cpp), [examples/component-runtime/aggregate.cpp](../../../../../examples/component-runtime/aggregate.cpp) |

## B0011

[Lines 11–11](../../../../../examples/component-runtime/CMakeLists.txt#L11); `build-command`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L11-L11:sha256:670885799874d4e7c1bca886b12711e78a48a52218f55dfe20cfe44f1ad2b73d
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Derive the local source filename for the default component cases. |
| inputs / outputs | Sets \`_source\` to \`&lt;component&gt;.cpp\`. |
| invariants | Session maps to \`session.cpp\` and aggregate to \`aggregate.cpp\`. |
| ownership | CMake passes the resulting source to the target declaration below. |
| failure | A missing corresponding source fails target generation or compilation. |
| cost | One configure-time string expansion. |
| Design | [examples/component-runtime/session.cpp](../../../../../examples/component-runtime/session.cpp), [examples/component-runtime/aggregate.cpp](../../../../../examples/component-runtime/aggregate.cpp) |

## B0012

[Lines 12–12](../../../../../examples/component-runtime/CMakeLists.txt#L12); `build-command`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L12-L12:sha256:a4facbef543d97e0da8eb59439d753c27239e68b15ef3136ed9fee632dc69d29
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Close the source-selection branch. |
| inputs / outputs | Ends the \`if\`/\`elseif\`/\`else\` command chain. |
| invariants | Exactly one source-selection branch assigns \`_source\` for each listed component. |
| ownership | CMake owns branch scope. |
| failure | Malformed nesting stops configuration. |
| cost | No runtime cost; configure-time syntax only. |
| Design | [examples/component-runtime/CMakeLists.txt](../../../../../examples/component-runtime/CMakeLists.txt) |

## B0013

[Lines 13–13](../../../../../examples/component-runtime/CMakeLists.txt#L13); `build-command`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L13-L13:sha256:0db2cdd5f63f4d219e8b4730a0e1cb90699c144db0a873fa1ea3ba6d81972eaf
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Create the per-component executable target from the selected source. |
| inputs / outputs | Expands the component name into the target name and consumes \`_source\`. |
| invariants | The four fixed loop values produce four named executables. |
| ownership | The build graph owns each executable and its compiled object files. |
| failure | Unknown sources or unavailable toolchain dependencies fail generation or build. |
| cost | Declares four executable targets; execution is not part of configuration. |
| Design | [examples/component-runtime/native_set.cpp](../../../../../examples/component-runtime/native_set.cpp), [examples/component-runtime/native_rows.cpp](../../../../../examples/component-runtime/native_rows.cpp), [examples/component-runtime/session.cpp](../../../../../examples/component-runtime/session.cpp), [examples/component-runtime/aggregate.cpp](../../../../../examples/component-runtime/aggregate.cpp) |

## B0014

[Lines 14–14](../../../../../examples/component-runtime/CMakeLists.txt#L14); `build-command`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L14-L14:sha256:43ab23b93b81f3bde2b24e8068b95a2bfe9e97f30098bb289670fec381265433
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Disable compiler-specific C++ language extensions for each example target. |
| inputs / outputs | Sets \`CXX_EXTENSIONS\` off on the active component executable. |
| invariants | Each target is compiled as standard C++ rather than a compiler dialect extension mode. |
| ownership | Target properties apply only to the named executable. |
| failure | Unsupported compiler settings fail during generation or compilation. |
| cost | One target property assignment per component. |
| Design | [examples/component-runtime/CMakeLists.txt](../../../../../examples/component-runtime/CMakeLists.txt) |

## B0015

[Lines 15–15](../../../../../examples/component-runtime/CMakeLists.txt#L15); `build-command`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L15-L15:sha256:01713b651d6f9d8e4983893d37e347df46f5f11cc7e0ab433f6c9627e7d2017a
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Select the aggregate component's dedicated imported runtime target. |
| inputs / outputs | Begins the aggregate-specific link branch. |
| invariants | Aggregate uses its SQL aggregate runtime component; it is not linked through the generic runtime branch. |
| ownership | The installed Crown package owns the imported target. |
| failure | An absent exported target fails generation, exposing an incomplete package install. |
| cost | Configure-time branch only. |
| Design | [cmake/CrownInstall.cmake](../../../../../cmake/CrownInstall.cmake) |

## B0016

[Lines 16–16](../../../../../examples/component-runtime/CMakeLists.txt#L16); `build-command`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L16-L16:sha256:8c18ae37e49c444f5b8985b9f78a69b8851d33a1cd70776403cb97a9421e9122
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Link the aggregate executable against the installed SQL aggregate runtime. |
| inputs / outputs | Associates the executable with \`CROWN::sql_aggregate_runtime\`. |
| invariants | The exported runtime target supplies its aggregate and rows dependencies. |
| ownership | The imported package target owns transitive usage requirements. |
| failure | Missing/incompatible export metadata fails generation or link. |
| cost | Adds target dependencies and link inputs; no program runs during configure. |
| Design | [cmake/CrownInstall.cmake](../../../../../cmake/CrownInstall.cmake), [examples/component-runtime/aggregate.cpp](../../../../../examples/component-runtime/aggregate.cpp) |

## B0017

[Lines 17–17](../../../../../examples/component-runtime/CMakeLists.txt#L17); `build-command`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L17-L17:sha256:36efe8788f5a5b8b0c009b2c0f11c492f188b63e2224d76f5f8a94cf9451246a
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Select the rows component's dedicated imported SQL rows target. |
| inputs / outputs | Branches on the \`rows\` component before the generic runtime case. |
| invariants | The rows executable must link \`CROWN::sql_rows\`. |
| ownership | The installed Crown package owns this imported target. |
| failure | Missing/incompatible export metadata fails generation or link. |
| cost | Configure-time branch only. |
| Design | [cmake/CrownInstall.cmake](../../../../../cmake/CrownInstall.cmake) |

## B0018

[Lines 18–18](../../../../../examples/component-runtime/CMakeLists.txt#L18); `build-command`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L18-L18:sha256:ada1e7b5a8f853f32ac52befa6677cfc90ca053e76f59c05e4d656c9a51b1120
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Link the rows executable against the installed SQL rows component. |
| inputs / outputs | Associates the active executable with \`CROWN::sql_rows\`. |
| invariants | The SQL rows target supplies the rows API and its public link dependencies. |
| ownership | The imported package target owns transitive usage requirements. |
| failure | An absent exported target fails generation or link. |
| cost | Adds target dependencies and link inputs only. |
| Design | [cmake/CrownInstall.cmake](../../../../../cmake/CrownInstall.cmake), [examples/component-runtime/native_rows.cpp](../../../../../examples/component-runtime/native_rows.cpp) |

## B0019

[Lines 19–19](../../../../../examples/component-runtime/CMakeLists.txt#L19); `build-command`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L19-L19:sha256:903a8925883ccb65b88c616ab13c37ba428b36f74f2f18f165bcd5b8ecb8333e
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Use the general native runtime for the remaining set and session components. |
| inputs / outputs | Begins the default link branch after aggregate and rows cases. |
| invariants | The branch applies to \`set\` and \`session\` in the fixed list. |
| ownership | The installed Crown package owns the imported runtime target. |
| failure | New loop values must receive their own correct target if runtime is insufficient. |
| cost | Configure-time branch only. |
| Design | [cmake/CrownInstall.cmake](../../../../../cmake/CrownInstall.cmake) |

## B0020

[Lines 20–20](../../../../../examples/component-runtime/CMakeLists.txt#L20); `build-command`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L20-L20:sha256:3efcd203e5ccb4b8017582ced75516ad4556722054976476f69cff7d81d482bc
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Link set and session executables to the installed general runtime target. |
| inputs / outputs | Associates the active target with \`CROWN::runtime\`. |
| invariants | Aggregate and rows have already selected their more specific component targets. |
| ownership | The imported package target owns public usage requirements. |
| failure | Missing export metadata fails generation or link. |
| cost | Adds dependencies/link inputs; no runtime work. |
| Design | [cmake/CrownInstall.cmake](../../../../../cmake/CrownInstall.cmake), [examples/component-runtime/native_set.cpp](../../../../../examples/component-runtime/native_set.cpp), [examples/component-runtime/session.cpp](../../../../../examples/component-runtime/session.cpp) |

## B0021

[Lines 21–21](../../../../../examples/component-runtime/CMakeLists.txt#L21); `build-command`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L21-L21:sha256:a4facbef543d97e0da8eb59439d753c27239e68b15ef3136ed9fee632dc69d29
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Close the component-specific link selection. |
| inputs / outputs | Ends the aggregate/rows/general-runtime branch chain. |
| invariants | Each listed executable receives one component link target. |
| ownership | CMake owns the branch structure. |
| failure | Malformed nesting stops configuration. |
| cost | No runtime cost. |
| Design | [examples/component-runtime/CMakeLists.txt](../../../../../examples/component-runtime/CMakeLists.txt) |

## B0022

[Lines 22–22](../../../../../examples/component-runtime/CMakeLists.txt#L22); `build-command`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L22-L22:sha256:0b986b9a5717a12d8e7f64ffaaf6d25969eb3459097141f88b8f519ff472c210
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Enable strict warning flags on every component executable. |
| inputs / outputs | Applies warning, conversion, sign-conversion, and pedantic options with warnings as errors. |
| invariants | The option set is target-local and applies to all four built-in examples. |
| ownership | Each executable inherits the options directly from this directory. |
| failure | Compiler-specific unsupported flags or warnings can fail the build by design. |
| cost | Adds compile flags; cost is compile-time diagnostics only. |
| Design | [examples/component-runtime/native_request.hpp](../../../../../examples/component-runtime/native_request.hpp), [examples/component-runtime/native_set.cpp](../../../../../examples/component-runtime/native_set.cpp), [examples/component-runtime/native_rows.cpp](../../../../../examples/component-runtime/native_rows.cpp), [examples/component-runtime/session.cpp](../../../../../examples/component-runtime/session.cpp) |

## B0023

[Lines 23–23](../../../../../examples/component-runtime/CMakeLists.txt#L23); `build-command`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L23-L23:sha256:7cde977468a8f8470f8a59500856e0bed04988acd0d0f2ad9bba4013c0be8abb
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Finish target creation and common properties for the four built-in components. |
| inputs / outputs | Closes the fixed-component \`foreach\` loop. |
| invariants | Only the four named values participate in this loop. |
| ownership | CMake owns the loop scope. |
| failure | Malformed loop structure stops configuration. |
| cost | No runtime work; closes four configure-time iterations. |
| Design | [examples/component-runtime/CMakeLists.txt](../../../../../examples/component-runtime/CMakeLists.txt) |

## B0024

[Lines 24–26](../../../../../examples/component-runtime/CMakeLists.txt#L24); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L24-L26:sha256:3204f204a91e40e4ad85ed422b2bd24c0232341a49e8fe5d24c640a4da7ff4fb
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Document the optional original C++ observer as a separate local comparison target. |
| inputs / outputs | Comments identify explicitly supplied original source/build/fmt paths and no-fetch behavior. |
| invariants | No original source is downloaded or configured by this project file. |
| ownership | The operator supplies the path values in the local CMake cache. |
| failure | This comment does not qualify the upstream binary or validate provenance by itself. |
| cost | Documentation only. |
| Design | [docs/legacy_baselines.md](../../../../legacy_baselines.md), [examples/component-runtime/legacy_cpp.cpp](../../../../../examples/component-runtime/legacy_cpp.cpp) |

## B0025

[Lines 27–27](../../../../../examples/component-runtime/CMakeLists.txt#L27); `build-command`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L27-L27:sha256:6521a74ee6b72c535859cc62a7c37e3a43bac7a5f0477fd5d0b5289d8dc88137
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Declare the optional source-tree cache path for the original C++ baseline. |
| inputs / outputs | Adds \`CROWN_LEGACY_CPP_SOURCE\` as a cache \`PATH\`, initially empty. |
| invariants | The value must point to a previously pinned local source checkout. |
| ownership | The operator owns the external path; this project only reads it. |
| failure | An invalid path is exposed when the optional target resolves its include directories. |
| cost | Configure-time cache declaration; no fetch or scan. |
| Design | [docs/legacy_baselines.md](../../../../legacy_baselines.md), [examples/component-runtime/legacy_cpp.cpp](../../../../../examples/component-runtime/legacy_cpp.cpp) |

## B0026

[Lines 28–28](../../../../../examples/component-runtime/CMakeLists.txt#L28); `build-command`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L28-L28:sha256:3e6e0ed91b1a4c2961b712597902a614f3dff8f9cfbfab21cc519ba4360c2916
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Declare the optional build-tree cache path for the qualified original C++ baseline. |
| inputs / outputs | Adds \`CROWN_LEGACY_CPP_BUILD\` as a cache \`PATH\`, initially empty. |
| invariants | The path is expected to contain the original static libraries named below. |
| ownership | The operator owns and prepares the external build tree. |
| failure | Missing libraries fail the optional executable link. |
| cost | Configure-time cache declaration only. |
| Design | [docs/legacy_baselines.md](../../../../legacy_baselines.md), [examples/component-runtime/legacy_cpp.cpp](../../../../../examples/component-runtime/legacy_cpp.cpp) |

## B0027

[Lines 29–29](../../../../../examples/component-runtime/CMakeLists.txt#L29); `build-command`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L29-L29:sha256:b9231c1248022e20780ea20ac524f57060b4af9f32c37342d632cd2d2b2e79bf
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Declare the optional source path for the original baseline's fmt dependency. |
| inputs / outputs | Adds \`CROWN_LEGACY_FMT_SOURCE\` as a cache \`PATH\`, initially empty. |
| invariants | The path supplies headers used by the optional original C++ executable. |
| ownership | The operator supplies the local source path. |
| failure | Missing headers fail compilation when the optional target is enabled. |
| cost | Configure-time cache declaration only. |
| Design | [docs/legacy_baselines.md](../../../../legacy_baselines.md), [examples/component-runtime/legacy_cpp.cpp](../../../../../examples/component-runtime/legacy_cpp.cpp) |

## B0028

[Lines 30–30](../../../../../examples/component-runtime/CMakeLists.txt#L30); `build-command`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L30-L30:sha256:cc6a943267a9f9fd83501a8c85f1f840bf7a9d01d0b0b3044a34291d7ae13869
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Enable the optional original C++ target only when all three external paths are supplied. |
| inputs / outputs | Tests source, build, and fmt cache paths together. |
| invariants | Partial configuration leaves the observer target absent rather than fetching or guessing missing dependencies. |
| ownership | CMake gates target construction; the operator owns all path contents. |
| failure | An all-present but invalid set fails downstream include/link/build checks. |
| cost | Three configure-time truth tests; no runtime cost. |
| Design | [docs/legacy_baselines.md](../../../../legacy_baselines.md), [examples/component-runtime/legacy_cpp.cpp](../../../../../examples/component-runtime/legacy_cpp.cpp) |

## B0029

[Lines 31–31](../../../../../examples/component-runtime/CMakeLists.txt#L31); `build-command`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L31-L31:sha256:c4fc0908cb6d65e094261876ea3903f45d1cd4ed91bfc66a1050a920edb44272
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Create the optional legacy C++ observer executable from the retained comparison source. |
| inputs / outputs | Adds \`crown_component_legacy_cpp\` using local \`legacy_cpp.cpp\`. |
| invariants | This target is separate from the four native component executables and exists only under the all-path gate. |
| ownership | The local build owns the observer binary; original libraries remain externally supplied. |
| failure | Missing source/compiler dependencies fail generation or build. |
| cost | Adds one optional executable; it is not automatically launched. |
| Design | [examples/component-runtime/legacy_cpp.cpp](../../../../../examples/component-runtime/legacy_cpp.cpp), [docs/legacy_baselines.md](../../../../legacy_baselines.md) |

## B0030

[Lines 32–32](../../../../../examples/component-runtime/CMakeLists.txt#L32); `build-command`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L32-L32:sha256:476d2aa18b938005669490905f6ea4f0b4120221cdb21c10ca5f0e0b4b05685f
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Disable compiler extensions on the optional legacy observer target. |
| inputs / outputs | Sets \`CXX_EXTENSIONS\` off for that executable. |
| invariants | The property is target-local. |
| ownership | CMake owns the target property. |
| failure | Unsupported compiler settings fail generation or compilation. |
| cost | One configure-time property assignment. |
| Design | [examples/component-runtime/legacy_cpp.cpp](../../../../../examples/component-runtime/legacy_cpp.cpp) |

## B0031

[Lines 33–36](../../../../../examples/component-runtime/CMakeLists.txt#L33); `build-command`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L33-L36:sha256:99eca9300261adac6f88bbfc6f1a24a6b0162e126dbb249e33fbed9664d8a249
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Supply the explicitly pinned external baseline and fmt headers as system includes while retaining strict diagnostics on the local observer. |
| inputs / outputs | The three supplied cache roots become target-local SYSTEM PRIVATE include paths; the wrapper keeps -Wall/-Wextra/-Wpedantic/-Wconversion/-Wsign-conversion/-Werror. |
| invariants | Only upstream headers receive system-header diagnostic treatment. Own wrapper warnings remain errors; no baseline source/archive, global warning policy, search path discovery or network input is changed. |
| ownership | The operator owns the checkouts; CMake passes their include paths to the compiler. |
| failure | Missing or incompatible external headers still fail compilation; external warning suppression is not output qualification. Exact baseline output checks remain separate. |
| cost | Configure-time include flag generation only; no runtime branch, allocation, shim, or engine update work. |
| Design | [docs/legacy_baselines.md](../../../../legacy_baselines.md), [examples/component-runtime/legacy_cpp.cpp](../../../../../examples/component-runtime/legacy_cpp.cpp), [docs/component_evaluation.md](../../../../component_evaluation.md) |

## B0032

[Lines 37–39](../../../../../examples/component-runtime/CMakeLists.txt#L37); `build-command`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L37-L39:sha256:b4f7d8bf4482f31f54785e8a462fe999ee20115604f748bfe915ea802483a2c9
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Link the optional observer with Crown core/JSON plus the explicitly supplied original static archives. |
| inputs / outputs | Uses installed \`CROWN::core\` and \`CROWN::json\`, and exact archive paths under the provided build/source roots. |
| invariants | No original archive is fetched, rebuilt, or substituted by this CMake file. |
| ownership | CROWN targets are imported; original archives are operator-owned files. |
| failure | Missing or ABI-incompatible archives fail link or execution; this target alone does not establish benchmark comparability. |
| cost | Adds five direct link inputs; runtime behavior is in the executable and remains outside CMake. |
| Design | [docs/legacy_baselines.md](../../../../legacy_baselines.md), [examples/component-runtime/legacy_cpp.cpp](../../../../../examples/component-runtime/legacy_cpp.cpp) |

## B0033

[Lines 40–40](../../../../../examples/component-runtime/CMakeLists.txt#L40); `build-command`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L40-L40:sha256:f17d9f9666ad7bc2eda3ff433790c46489bffa5ea99cacf1c56df64ae4ee2db6
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Apply the same strict warning policy to the optional observer source. |
| inputs / outputs | Uses warnings, pedantic, conversion, sign-conversion, and warnings-as-errors flags. |
| invariants | Options apply to the local observer target; upstream archives are not recompiled here. |
| ownership | The local target owns compile options; external libraries retain their own build settings. |
| failure | Unsupported flags or source warnings can fail compilation. |
| cost | Compile-time diagnostics only. |
| Design | [examples/component-runtime/legacy_cpp.cpp](../../../../../examples/component-runtime/legacy_cpp.cpp) |

## B0034

[Lines 41–41](../../../../../examples/component-runtime/CMakeLists.txt#L41); `build-command`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L41-L41:sha256:1580c623168ea6c0a789d3be000852a569df5198eeb3650cf5b2a75e863f2178
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Close the all-path condition for the optional observer target. |
| inputs / outputs | Ends the gate begun by the three cache-path condition. |
| invariants | If any input path is empty, none of the optional target declarations inside the branch apply. |
| ownership | CMake owns the optional target gate. |
| failure | Malformed conditional structure stops configuration. |
| cost | No runtime cost. |
| Design | [examples/component-runtime/CMakeLists.txt](../../../../../examples/component-runtime/CMakeLists.txt), [docs/legacy_baselines.md](../../../../legacy_baselines.md) |
