# `cmake/CrownInstall.cmake` — block usage map

[Source](../../../../cmake/CrownInstall.cmake) · [Source index](../../README.md) · [Subsystem contracts](../../subsystem_contracts.md) · [Reviewed primitives](../../primitives.md)

Define native target boundaries, pinned dependencies, compilation options, installation and test registration.

Snapshot SHA-256: `0bb2fd883aa2001ec6c23a452ba38662283d775ddf3d8debe53e9a12e837e2e5`. 51 lines partitioned into 40 blocks using `cmake_commands`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [build](../../subsystem_contracts.md#build). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/native_build.md](../../../native_build.md), [docs/source_baselines.md](../../../source_baselines.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–1](../../../../cmake/CrownInstall.cmake#L1) | CMake command: include(GNUInstallDirs) |  · [reviewed contract](#b0001) |
| [B0002 · 2–2](../../../../cmake/CrownInstall.cmake#L2) | CMake command: include(CMakePackageConfigHelpers) |  · [reviewed contract](#b0002) |
| [B0003 · 3–6](../../../../cmake/CrownInstall.cmake#L3) | CMake command: set(_crown_public_targets crown_options crown_json crown_core crown_sql crown_sql_rows crown_sql_aggregate crown_sql_aggregate_ru… |  · [reviewed contract](#b0003) |
| [B0004 · 7–7](../../../../cmake/CrownInstall.cmake#L7) | CMake command: foreach(_crown_target IN LISTS _crown_public_targets) |  · [reviewed contract](#b0004) |
| [B0005 · 8–8](../../../../cmake/CrownInstall.cmake#L8) | CMake command: string(REGEX REPLACE "^crown_" "" _crown_export_name "${_crown_target}") |  · [reviewed contract](#b0005) |
| [B0006 · 9–9](../../../../cmake/CrownInstall.cmake#L9) | CMake command: set_target_properties(${_crown_target} PROPERTIES EXPORT_NAME "${_crown_export_name}") |  · [reviewed contract](#b0006) |
| [B0007 · 10–10](../../../../cmake/CrownInstall.cmake#L10) | CMake command: if(NOT TARGET CROWN::${_crown_export_name}) |  · [reviewed contract](#b0007) |
| [B0008 · 11–11](../../../../cmake/CrownInstall.cmake#L11) | CMake command: add_library(CROWN::${_crown_export_name} ALIAS ${_crown_target}) |  · [reviewed contract](#b0008) |
| [B0009 · 12–12](../../../../cmake/CrownInstall.cmake#L12) | CMake command: endif() |  · [reviewed contract](#b0009) |
| [B0010 · 13–13](../../../../cmake/CrownInstall.cmake#L13) | CMake command: endforeach() |  · [reviewed contract](#b0010) |
| [B0011 · 14–14](../../../../cmake/CrownInstall.cmake#L14) | CMake command: target_compile_features(crown_core PUBLIC cxx_std_23) |  · [reviewed contract](#b0011) |
| [B0012 · 15–18](../../../../cmake/CrownInstall.cmake#L15) | CMake command: install(TARGETS ${_crown_public_targets} EXPORT CrownTargets |  · [reviewed contract](#b0012) |
| [B0013 · 19–19](../../../../cmake/CrownInstall.cmake#L19) | CMake command: install(TARGETS crown RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}) |  · [reviewed contract](#b0013) |
| [B0014 · 20–20](../../../../cmake/CrownInstall.cmake#L20) | CMake command: install(FILES "${_crown_pg_query_library}" DESTINATION "${CMAKE_INSTALL_LIBDIR}/crown/deps") |  · [reviewed contract](#b0014) |
| [B0015 · 21–21](../../../../cmake/CrownInstall.cmake#L21) | CMake command: install(DIRECTORY include/crown DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}) |  · [reviewed contract](#b0015) |
| [B0016 · 22–22](../../../../cmake/CrownInstall.cmake#L22) | CMake command: install(FILES third_party/nlohmann/json.hpp DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}/nlohmann") |  · [reviewed contract](#b0016) |
| [B0017 · 23–23](../../../../cmake/CrownInstall.cmake#L23) | CMake command: install(FILES third_party/nlohmann/LICENSE.MIT DESTINATION "${CMAKE_INSTALL_DATADIR}/crown/licenses/nlohmann") |  · [reviewed contract](#b0017) |
| [B0018 · 24–24](../../../../cmake/CrownInstall.cmake#L24) | CMake command: install(DIRECTORY third_party/nlohmann/patches/ DESTINATION "${CMAKE_INSTALL_DATADIR}/crown/patches/nlohmann") |  · [reviewed contract](#b0018) |
| [B0019 · 25–25](../../../../cmake/CrownInstall.cmake#L25) | CMake command: install(DIRECTORY third_party/libpg_query/notices/ DESTINATION "${CMAKE_INSTALL_DATADIR}/crown/licenses/libpg_query") |  · [reviewed contract](#b0019) |
| [B0020 · 26–28](../../../../cmake/CrownInstall.cmake#L26) | CMake command: configure_package_config_file(cmake/CrownConfig.cmake.in "${CMAKE_CURRENT_BINARY_DIR}/CrownConfig.cmake" |  · [reviewed contract](#b0020) |
| [B0021 · 29–30](../../../../cmake/CrownInstall.cmake#L29) | CMake command: write_basic_package_version_file("${CMAKE_CURRENT_BINARY_DIR}/CrownConfigVersion.cmake" |  · [reviewed contract](#b0021) |
| [B0022 · 31–31](../../../../cmake/CrownInstall.cmake#L31) | CMake command: install(EXPORT CrownTargets NAMESPACE CROWN:: DESTINATION "${CMAKE_INSTALL_LIBDIR}/cmake/Crown") |  · [reviewed contract](#b0022) |
| [B0023 · 32–34](../../../../cmake/CrownInstall.cmake#L32) | CMake command: install(FILES "${CMAKE_CURRENT_BINARY_DIR}/CrownConfig.cmake" |  · [reviewed contract](#b0023) |
| [B0024 · 35–35](../../../../cmake/CrownInstall.cmake#L35) | Explanatory comments or spacing. |  |
| [B0025 · 36–36](../../../../cmake/CrownInstall.cmake#L36) | CMake command: install(DIRECTORY schemas/ DESTINATION "${CMAKE_INSTALL_DATADIR}/crown/schemas" FILES_MATCHING PATTERN "*.json") |  · [reviewed contract](#b0025) |
| [B0026 · 37–37](../../../../cmake/CrownInstall.cmake#L37) | Explanatory comments or spacing. |  |
| [B0027 · 38–38](../../../../cmake/CrownInstall.cmake#L38) | CMake command: install(DIRECTORY examples/native-workflow/ DESTINATION "${CMAKE_INSTALL_DATADIR}/crown/examples/native-workflow") |  · [reviewed contract](#b0027) |
| [B0028 · 39–39](../../../../cmake/CrownInstall.cmake#L39) | CMake command: install(DIRECTORY examples/cost-calibration/ DESTINATION "${CMAKE_INSTALL_DATADIR}/crown/examples/cost-calibration") |  · [reviewed contract](#b0028) |
| [B0029 · 40–40](../../../../cmake/CrownInstall.cmake#L40) | CMake command: install(DIRECTORY examples/workload-measurement/ DESTINATION "${CMAKE_INSTALL_DATADIR}/crown/examples/workload-measurement") |  · [reviewed contract](#b0029) |
| [B0030 · 41–41](../../../../cmake/CrownInstall.cmake#L41) | CMake command: install(DIRECTORY examples/ranking-evaluation/ DESTINATION "${CMAKE_INSTALL_DATADIR}/crown/examples/ranking-evaluation") |  · [reviewed contract](#b0030) |
| [B0031 · 42–42](../../../../cmake/CrownInstall.cmake#L42) | CMake command: install(DIRECTORY examples/reoptimization/ DESTINATION "${CMAKE_INSTALL_DATADIR}/crown/examples/reoptimization") |  · [reviewed contract](#b0031) |
| [B0032 · 43–43](../../../../cmake/CrownInstall.cmake#L43) | CMake command: install(DIRECTORY examples/meta-candidates/ DESTINATION "${CMAKE_INSTALL_DATADIR}/crown/examples/meta-candidates") |  · [reviewed contract](#b0032) |
| [B0033 · 44–44](../../../../cmake/CrownInstall.cmake#L44) | CMake command: install(DIRECTORY examples/component-planning/ DESTINATION "${CMAKE_INSTALL_DATADIR}/crown/examples/component-planning") |  · [reviewed contract](#b0033) |
| [B0034 · 45–45](../../../../cmake/CrownInstall.cmake#L45) | CMake command: install(DIRECTORY examples/component-runtime/ DESTINATION "${CMAKE_INSTALL_DATADIR}/crown/examples/component-runtime") |  · [reviewed contract](#b0034) |
| [B0035 · 46–46](../../../../cmake/CrownInstall.cmake#L46) | CMake command: install(DIRECTORY examples/independent-queries/ DESTINATION "${CMAKE_INSTALL_DATADIR}/crown/examples/independent-queries") |  · [reviewed contract](#b0035) |
| [B0036 · 47–47](../../../../cmake/CrownInstall.cmake#L47) | CMake command: install(FILES tools/support/ComponentReplay.scala DESTINATION "${CMAKE_INSTALL_DATADIR}/crown/examples/component-runtime") |  · [reviewed contract](#b0036) |
| [B0037 · 48–48](../../../../cmake/CrownInstall.cmake#L48) | Explanatory comments or spacing. |  |
| [B0038 · 49–49](../../../../cmake/CrownInstall.cmake#L49) | CMake command: install(FILES tools/prepare_workflow_input.py DESTINATION "${CMAKE_INSTALL_DATADIR}/crown/examples/native-workflow") |  · [reviewed contract](#b0038) |
| [B0039 · 50–50](../../../../cmake/CrownInstall.cmake#L50) | Explanatory comments or spacing. |  |
| [B0040 · 51–51](../../../../cmake/CrownInstall.cmake#L51) | CMake command: install(FILES docs/cli.md docs/sql_aggregate_input.md DESTINATION "${CMAKE_INSTALL_DATADIR}/crown/docs") |  · [reviewed contract](#b0040) |

## B0001

[Lines 1–1](../../../../cmake/CrownInstall.cmake#L1); `build-command`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
include(GNUInstallDirs)

```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Load standard CMAKE_INSTALL_* destination variables. |
| inputs / outputs | Defines configurable bindir, libdir, includedir and datadir used by install rules. |
| invariants | These commands declare CMake build/package metadata; they do not execute CROWN application work. The optional CROWN::meta_candidates target links core only; no runtime or test/reference ABI is added to this adapter. |
| ownership | CMake target/package metadata only; no binary payload is owned here. |
| failure | Missing modules, invalid targets or unresolved export properties fail configuration/export generation. |
| cost | Configure/generate metadata over a finite list; no per-query CMake work. |
| Design | [cmake/CrownInstall.cmake](../../../../cmake/CrownInstall.cmake), [CMakeLists.txt](../../../../CMakeLists.txt), [cmake/CrownConfig.cmake.in](../../../../cmake/CrownConfig.cmake.in), [docs/native_build.md](../../../native_build.md), [docs/cli.md](../../../cli.md), [examples/native-workflow/CMakeLists.txt](../../../../examples/native-workflow/CMakeLists.txt), [examples/cost-calibration/CMakeLists.txt](../../../../examples/cost-calibration/CMakeLists.txt), [examples/reoptimization/CMakeLists.txt](../../../../examples/reoptimization/CMakeLists.txt), [examples/ranking-evaluation/CMakeLists.txt](../../../../examples/ranking-evaluation/CMakeLists.txt), [examples/workload-measurement/CMakeLists.txt](../../../../examples/workload-measurement/CMakeLists.txt), [tests/integration/installed_workflow.py](../../../../tests/integration/installed_workflow.py), [docs/meta_candidate_adapter.md](../../../meta_candidate_adapter.md) |

## B0002

[Lines 2–2](../../../../cmake/CrownInstall.cmake#L2); `build-command`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
include(CMakePackageConfigHelpers)

```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Load helpers for package config and version-file generation. |
| inputs / outputs | Makes the relocatable config/version commands available. |
| invariants | These commands declare CMake build/package metadata; they do not execute CROWN application work. The optional CROWN::meta_candidates target links core only; no runtime or test/reference ABI is added to this adapter. |
| ownership | CMake target/package metadata only; no binary payload is owned here. |
| failure | Missing modules, invalid targets or unresolved export properties fail configuration/export generation. |
| cost | Configure/generate metadata over a finite list; no per-query CMake work. |
| Design | [cmake/CrownInstall.cmake](../../../../cmake/CrownInstall.cmake), [CMakeLists.txt](../../../../CMakeLists.txt), [cmake/CrownConfig.cmake.in](../../../../cmake/CrownConfig.cmake.in), [docs/native_build.md](../../../native_build.md), [docs/cli.md](../../../cli.md), [examples/native-workflow/CMakeLists.txt](../../../../examples/native-workflow/CMakeLists.txt), [examples/cost-calibration/CMakeLists.txt](../../../../examples/cost-calibration/CMakeLists.txt), [examples/reoptimization/CMakeLists.txt](../../../../examples/reoptimization/CMakeLists.txt), [examples/ranking-evaluation/CMakeLists.txt](../../../../examples/ranking-evaluation/CMakeLists.txt), [examples/workload-measurement/CMakeLists.txt](../../../../examples/workload-measurement/CMakeLists.txt), [tests/integration/installed_workflow.py](../../../../tests/integration/installed_workflow.py), [docs/meta_candidate_adapter.md](../../../meta_candidate_adapter.md) |

## B0003

[Lines 3–6](../../../../cmake/CrownInstall.cmake#L3); `build-command`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L3-L6:sha256:8d9ac858ff73a3987dc3cd644a0df719f4ff619b394e791d198fa78911218bd1
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Export/install the optional independent-query directory library. |
| inputs / outputs | Add crown_queries to _crown_public_targets; existing alias/export loop derives CROWN::queries and the common install rule includes the target. |
| invariants | The optional directory API joins package public closure; other targets remain present. |
| ownership | Installed metadata carries the library; callers retain session/account ownership. |
| failure | Missing target or dependency fails generation/export instead of silently omitting the API. |
| cost | Adds one public target to package metadata; no runtime work. |
| Design | [docs/independent_queries.md](../../../independent_queries.md), [include/crown/runtime/queries.hpp](../../../../include/crown/runtime/queries.hpp), [src/runtime/queries.cpp](../../../../src/runtime/queries.cpp) |

## B0004

[Lines 7–7](../../../../cmake/CrownInstall.cmake#L7); `build-command`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
foreach(_crown_target IN LISTS _crown_public_targets)

```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Iterate the fixed public target list for exported names and build aliases. |
| inputs / outputs | Each target enters the rename/property/alias body exactly once. |
| invariants | These commands declare CMake build/package metadata; they do not execute CROWN application work. |
| ownership | CMake target/package metadata only; no binary payload is owned here. |
| failure | Missing modules, invalid targets or unresolved export properties fail configuration/export generation. |
| cost | Configure/generate metadata over a finite list; no per-query CMake work. |
| Design | [cmake/CrownInstall.cmake](../../../../cmake/CrownInstall.cmake), [CMakeLists.txt](../../../../CMakeLists.txt), [cmake/CrownConfig.cmake.in](../../../../cmake/CrownConfig.cmake.in), [docs/native_build.md](../../../native_build.md), [docs/cli.md](../../../cli.md), [examples/native-workflow/CMakeLists.txt](../../../../examples/native-workflow/CMakeLists.txt), [examples/cost-calibration/CMakeLists.txt](../../../../examples/cost-calibration/CMakeLists.txt), [examples/reoptimization/CMakeLists.txt](../../../../examples/reoptimization/CMakeLists.txt), [examples/ranking-evaluation/CMakeLists.txt](../../../../examples/ranking-evaluation/CMakeLists.txt), [examples/workload-measurement/CMakeLists.txt](../../../../examples/workload-measurement/CMakeLists.txt), [tests/integration/installed_workflow.py](../../../../tests/integration/installed_workflow.py) |

## B0005

[Lines 8–8](../../../../cmake/CrownInstall.cmake#L8); `build-command`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
  string(REGEX REPLACE "^crown_" "" _crown_export_name "${_crown_target}")

```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Derive public component names by removing the crown_ prefix. |
| inputs / outputs | For example crown_runtime yields runtime for the CROWN:: namespace. |
| invariants | These commands declare CMake build/package metadata; they do not execute CROWN application work. |
| ownership | CMake target/package metadata only; no binary payload is owned here. |
| failure | Missing modules, invalid targets or unresolved export properties fail configuration/export generation. |
| cost | Configure/generate metadata over a finite list; no per-query CMake work. |
| Design | [cmake/CrownInstall.cmake](../../../../cmake/CrownInstall.cmake), [CMakeLists.txt](../../../../CMakeLists.txt), [cmake/CrownConfig.cmake.in](../../../../cmake/CrownConfig.cmake.in), [docs/native_build.md](../../../native_build.md), [docs/cli.md](../../../cli.md), [examples/native-workflow/CMakeLists.txt](../../../../examples/native-workflow/CMakeLists.txt), [examples/cost-calibration/CMakeLists.txt](../../../../examples/cost-calibration/CMakeLists.txt), [examples/reoptimization/CMakeLists.txt](../../../../examples/reoptimization/CMakeLists.txt), [examples/ranking-evaluation/CMakeLists.txt](../../../../examples/ranking-evaluation/CMakeLists.txt), [examples/workload-measurement/CMakeLists.txt](../../../../examples/workload-measurement/CMakeLists.txt), [tests/integration/installed_workflow.py](../../../../tests/integration/installed_workflow.py) |

## B0006

[Lines 9–9](../../../../cmake/CrownInstall.cmake#L9); `build-command`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
  set_target_properties(${_crown_target} PROPERTIES EXPORT_NAME "${_crown_export_name}")

```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Set each target’s EXPORT_NAME to its public component spelling. |
| inputs / outputs | Install export metadata uses stable consumer-facing target names. |
| invariants | These commands declare CMake build/package metadata; they do not execute CROWN application work. |
| ownership | CMake target/package metadata only; no binary payload is owned here. |
| failure | Missing modules, invalid targets or unresolved export properties fail configuration/export generation. |
| cost | Configure/generate metadata over a finite list; no per-query CMake work. |
| Design | [cmake/CrownInstall.cmake](../../../../cmake/CrownInstall.cmake), [CMakeLists.txt](../../../../CMakeLists.txt), [cmake/CrownConfig.cmake.in](../../../../cmake/CrownConfig.cmake.in), [docs/native_build.md](../../../native_build.md), [docs/cli.md](../../../cli.md), [examples/native-workflow/CMakeLists.txt](../../../../examples/native-workflow/CMakeLists.txt), [examples/cost-calibration/CMakeLists.txt](../../../../examples/cost-calibration/CMakeLists.txt), [examples/reoptimization/CMakeLists.txt](../../../../examples/reoptimization/CMakeLists.txt), [examples/ranking-evaluation/CMakeLists.txt](../../../../examples/ranking-evaluation/CMakeLists.txt), [examples/workload-measurement/CMakeLists.txt](../../../../examples/workload-measurement/CMakeLists.txt), [tests/integration/installed_workflow.py](../../../../tests/integration/installed_workflow.py) |

## B0007

[Lines 10–10](../../../../cmake/CrownInstall.cmake#L10); `build-command`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
  if(NOT TARGET CROWN::${_crown_export_name})

```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Check whether the intended build-tree CROWN alias already exists. |
| inputs / outputs | Only an absent namespace name reaches add_library(ALIAS). |
| invariants | These commands declare CMake build/package metadata; they do not execute CROWN application work. |
| ownership | CMake target/package metadata only; no binary payload is owned here. |
| failure | The guard avoids duplicate alias creation; an invalid target/name fails configuration. |
| cost | Configure/generate metadata over a finite list; no per-query CMake work. |
| Design | [cmake/CrownInstall.cmake](../../../../cmake/CrownInstall.cmake), [CMakeLists.txt](../../../../CMakeLists.txt), [cmake/CrownConfig.cmake.in](../../../../cmake/CrownConfig.cmake.in), [docs/native_build.md](../../../native_build.md), [docs/cli.md](../../../cli.md), [examples/native-workflow/CMakeLists.txt](../../../../examples/native-workflow/CMakeLists.txt), [examples/cost-calibration/CMakeLists.txt](../../../../examples/cost-calibration/CMakeLists.txt), [examples/reoptimization/CMakeLists.txt](../../../../examples/reoptimization/CMakeLists.txt), [examples/ranking-evaluation/CMakeLists.txt](../../../../examples/ranking-evaluation/CMakeLists.txt), [examples/workload-measurement/CMakeLists.txt](../../../../examples/workload-measurement/CMakeLists.txt), [tests/integration/installed_workflow.py](../../../../tests/integration/installed_workflow.py) |

## B0008

[Lines 11–11](../../../../cmake/CrownInstall.cmake#L11); `build-command`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
    add_library(CROWN::${_crown_export_name} ALIAS ${_crown_target})

```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Create a build-tree CROWN:: alias for the internal target. |
| inputs / outputs | The alias points to the listed crown_ target and mirrors the installed name. |
| invariants | These commands declare CMake build/package metadata; they do not execute CROWN application work. |
| ownership | CMake target/package metadata only; no binary payload is owned here. |
| failure | The guard avoids duplicate alias creation; an invalid target/name fails configuration. |
| cost | Configure/generate metadata over a finite list; no per-query CMake work. |
| Design | [cmake/CrownInstall.cmake](../../../../cmake/CrownInstall.cmake), [CMakeLists.txt](../../../../CMakeLists.txt), [cmake/CrownConfig.cmake.in](../../../../cmake/CrownConfig.cmake.in), [docs/native_build.md](../../../native_build.md), [docs/cli.md](../../../cli.md), [examples/native-workflow/CMakeLists.txt](../../../../examples/native-workflow/CMakeLists.txt), [examples/cost-calibration/CMakeLists.txt](../../../../examples/cost-calibration/CMakeLists.txt), [examples/reoptimization/CMakeLists.txt](../../../../examples/reoptimization/CMakeLists.txt), [examples/ranking-evaluation/CMakeLists.txt](../../../../examples/ranking-evaluation/CMakeLists.txt), [examples/workload-measurement/CMakeLists.txt](../../../../examples/workload-measurement/CMakeLists.txt), [tests/integration/installed_workflow.py](../../../../tests/integration/installed_workflow.py) |

## B0009

[Lines 12–12](../../../../cmake/CrownInstall.cmake#L12); `build-command`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
  endif()

```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Close the alias-existence conditional. |
| inputs / outputs | No output; ends the guard around alias creation. |
| invariants | These commands declare CMake build/package metadata; they do not execute CROWN application work. |
| ownership | CMake target/package metadata only; no binary payload is owned here. |
| failure | Unbalanced loop/conditional syntax fails configuration. |
| cost | Configure/generate metadata over a finite list; no per-query CMake work. |
| Design | [cmake/CrownInstall.cmake](../../../../cmake/CrownInstall.cmake), [CMakeLists.txt](../../../../CMakeLists.txt), [cmake/CrownConfig.cmake.in](../../../../cmake/CrownConfig.cmake.in), [docs/native_build.md](../../../native_build.md), [docs/cli.md](../../../cli.md), [examples/native-workflow/CMakeLists.txt](../../../../examples/native-workflow/CMakeLists.txt), [examples/cost-calibration/CMakeLists.txt](../../../../examples/cost-calibration/CMakeLists.txt), [examples/reoptimization/CMakeLists.txt](../../../../examples/reoptimization/CMakeLists.txt), [examples/ranking-evaluation/CMakeLists.txt](../../../../examples/ranking-evaluation/CMakeLists.txt), [examples/workload-measurement/CMakeLists.txt](../../../../examples/workload-measurement/CMakeLists.txt), [tests/integration/installed_workflow.py](../../../../tests/integration/installed_workflow.py) |

## B0010

[Lines 13–13](../../../../cmake/CrownInstall.cmake#L13); `build-command`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
endforeach()

```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Close iteration over the public target list. |
| inputs / outputs | No output; terminates the foreach body. |
| invariants | These commands declare CMake build/package metadata; they do not execute CROWN application work. |
| ownership | CMake target/package metadata only; no binary payload is owned here. |
| failure | Unbalanced loop/conditional syntax fails configuration. |
| cost | Configure/generate metadata over a finite list; no per-query CMake work. |
| Design | [cmake/CrownInstall.cmake](../../../../cmake/CrownInstall.cmake), [CMakeLists.txt](../../../../CMakeLists.txt), [cmake/CrownConfig.cmake.in](../../../../cmake/CrownConfig.cmake.in), [docs/native_build.md](../../../native_build.md), [docs/cli.md](../../../cli.md), [examples/native-workflow/CMakeLists.txt](../../../../examples/native-workflow/CMakeLists.txt), [examples/cost-calibration/CMakeLists.txt](../../../../examples/cost-calibration/CMakeLists.txt), [examples/reoptimization/CMakeLists.txt](../../../../examples/reoptimization/CMakeLists.txt), [examples/ranking-evaluation/CMakeLists.txt](../../../../examples/ranking-evaluation/CMakeLists.txt), [examples/workload-measurement/CMakeLists.txt](../../../../examples/workload-measurement/CMakeLists.txt), [tests/integration/installed_workflow.py](../../../../tests/integration/installed_workflow.py) |

## B0011

[Lines 14–14](../../../../cmake/CrownInstall.cmake#L14); `build-command`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
target_compile_features(crown_core PUBLIC cxx_std_23)

```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Publish C++23 as a transitive requirement of crown_core. |
| inputs / outputs | Exported consumers inherit the language feature requirement. |
| invariants | These commands declare CMake build/package metadata; they do not execute CROWN application work. |
| ownership | CMake target/package metadata only; no binary payload is owned here. |
| failure | Missing modules, invalid targets or unresolved export properties fail configuration/export generation. |
| cost | Configure/generate metadata over a finite list; no per-query CMake work. |
| Design | [cmake/CrownInstall.cmake](../../../../cmake/CrownInstall.cmake), [CMakeLists.txt](../../../../CMakeLists.txt), [cmake/CrownConfig.cmake.in](../../../../cmake/CrownConfig.cmake.in), [docs/native_build.md](../../../native_build.md), [docs/cli.md](../../../cli.md), [examples/native-workflow/CMakeLists.txt](../../../../examples/native-workflow/CMakeLists.txt), [examples/cost-calibration/CMakeLists.txt](../../../../examples/cost-calibration/CMakeLists.txt), [examples/reoptimization/CMakeLists.txt](../../../../examples/reoptimization/CMakeLists.txt), [examples/ranking-evaluation/CMakeLists.txt](../../../../examples/ranking-evaluation/CMakeLists.txt), [examples/workload-measurement/CMakeLists.txt](../../../../examples/workload-measurement/CMakeLists.txt), [tests/integration/installed_workflow.py](../../../../tests/integration/installed_workflow.py) |

## B0012

[Lines 15–18](../../../../cmake/CrownInstall.cmake#L15); `build-command`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
install(TARGETS ${_crown_public_targets} EXPORT CrownTargets

```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Install public library targets and generate the CrownTargets export set. |
| inputs / outputs | Copies target artifacts to GNUInstallDirs locations and records their target graph. |
| invariants | These rules copy package inputs on explicit install; installed examples are configured later as external consumers. |
| ownership | The install prefix owns copied artifact/data; source and build inputs remain separate. |
| failure | Missing built/generated input, export dependency or unwritable destination fails installation. |
| cost | One target/artifact metadata generation or finite install copy. |
| Design | [cmake/CrownInstall.cmake](../../../../cmake/CrownInstall.cmake), [CMakeLists.txt](../../../../CMakeLists.txt), [cmake/CrownConfig.cmake.in](../../../../cmake/CrownConfig.cmake.in), [docs/native_build.md](../../../native_build.md), [docs/cli.md](../../../cli.md), [examples/native-workflow/CMakeLists.txt](../../../../examples/native-workflow/CMakeLists.txt), [examples/cost-calibration/CMakeLists.txt](../../../../examples/cost-calibration/CMakeLists.txt), [examples/reoptimization/CMakeLists.txt](../../../../examples/reoptimization/CMakeLists.txt), [examples/ranking-evaluation/CMakeLists.txt](../../../../examples/ranking-evaluation/CMakeLists.txt), [examples/workload-measurement/CMakeLists.txt](../../../../examples/workload-measurement/CMakeLists.txt), [tests/integration/installed_workflow.py](../../../../tests/integration/installed_workflow.py) |

## B0013

[Lines 19–19](../../../../cmake/CrownInstall.cmake#L19); `build-command`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
install(TARGETS crown RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR})

```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Install the crown command-line executable. |
| inputs / outputs | Copies the built runtime target to CMAKE_INSTALL_BINDIR. |
| invariants | These rules copy package inputs on explicit install; installed examples are configured later as external consumers. |
| ownership | The install prefix owns copied artifact/data; source and build inputs remain separate. |
| failure | Missing source input or unwritable destination fails installation; external consumer errors occur later. |
| cost | One finite file/directory copy at installation. |
| Design | [cmake/CrownInstall.cmake](../../../../cmake/CrownInstall.cmake), [CMakeLists.txt](../../../../CMakeLists.txt), [cmake/CrownConfig.cmake.in](../../../../cmake/CrownConfig.cmake.in), [docs/native_build.md](../../../native_build.md), [docs/cli.md](../../../cli.md), [examples/native-workflow/CMakeLists.txt](../../../../examples/native-workflow/CMakeLists.txt), [examples/cost-calibration/CMakeLists.txt](../../../../examples/cost-calibration/CMakeLists.txt), [examples/reoptimization/CMakeLists.txt](../../../../examples/reoptimization/CMakeLists.txt), [examples/ranking-evaluation/CMakeLists.txt](../../../../examples/ranking-evaluation/CMakeLists.txt), [examples/workload-measurement/CMakeLists.txt](../../../../examples/workload-measurement/CMakeLists.txt), [tests/integration/installed_workflow.py](../../../../tests/integration/installed_workflow.py) |

## B0014

[Lines 20–20](../../../../cmake/CrownInstall.cmake#L20); `build-command`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
install(FILES "${_crown_pg_query_library}" DESTINATION "${CMAKE_INSTALL_LIBDIR}/crown/deps")

```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Bundle the parser archive under the package dependency directory. |
| inputs / outputs | Copies libpg_query.a to CMAKE_INSTALL_LIBDIR/crown/deps. |
| invariants | These rules copy package inputs on explicit install; installed examples are configured later as external consumers. |
| ownership | The install prefix owns copied artifact/data; source and build inputs remain separate. |
| failure | Missing source input or unwritable destination fails installation; external consumer errors occur later. |
| cost | One finite file/directory copy at installation. |
| Design | [cmake/CrownInstall.cmake](../../../../cmake/CrownInstall.cmake), [CMakeLists.txt](../../../../CMakeLists.txt), [cmake/CrownConfig.cmake.in](../../../../cmake/CrownConfig.cmake.in), [docs/native_build.md](../../../native_build.md), [docs/cli.md](../../../cli.md), [examples/native-workflow/CMakeLists.txt](../../../../examples/native-workflow/CMakeLists.txt), [examples/cost-calibration/CMakeLists.txt](../../../../examples/cost-calibration/CMakeLists.txt), [examples/reoptimization/CMakeLists.txt](../../../../examples/reoptimization/CMakeLists.txt), [examples/ranking-evaluation/CMakeLists.txt](../../../../examples/ranking-evaluation/CMakeLists.txt), [examples/workload-measurement/CMakeLists.txt](../../../../examples/workload-measurement/CMakeLists.txt), [tests/integration/installed_workflow.py](../../../../tests/integration/installed_workflow.py) |

## B0015

[Lines 21–21](../../../../cmake/CrownInstall.cmake#L21); `build-command`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
install(DIRECTORY include/crown DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})

```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Install public CROWN headers. |
| inputs / outputs | Copies include/crown beneath CMAKE_INSTALL_INCLUDEDIR. |
| invariants | These rules copy package inputs on explicit install; installed examples are configured later as external consumers. |
| ownership | The install prefix owns copied artifact/data; source and build inputs remain separate. |
| failure | Missing source input or unwritable destination fails installation; external consumer errors occur later. |
| cost | One finite file/directory copy at installation. |
| Design | [cmake/CrownInstall.cmake](../../../../cmake/CrownInstall.cmake), [CMakeLists.txt](../../../../CMakeLists.txt), [cmake/CrownConfig.cmake.in](../../../../cmake/CrownConfig.cmake.in), [docs/native_build.md](../../../native_build.md), [docs/cli.md](../../../cli.md), [examples/native-workflow/CMakeLists.txt](../../../../examples/native-workflow/CMakeLists.txt), [examples/cost-calibration/CMakeLists.txt](../../../../examples/cost-calibration/CMakeLists.txt), [examples/reoptimization/CMakeLists.txt](../../../../examples/reoptimization/CMakeLists.txt), [examples/ranking-evaluation/CMakeLists.txt](../../../../examples/ranking-evaluation/CMakeLists.txt), [examples/workload-measurement/CMakeLists.txt](../../../../examples/workload-measurement/CMakeLists.txt), [tests/integration/installed_workflow.py](../../../../tests/integration/installed_workflow.py) |

## B0016

[Lines 22–22](../../../../cmake/CrownInstall.cmake#L22); `build-command`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
install(FILES third_party/nlohmann/json.hpp DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}/nlohmann")

```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Install the vendored JSON header at its public include spelling. |
| inputs / outputs | Copies json.hpp beneath CMAKE_INSTALL_INCLUDEDIR/nlohmann. |
| invariants | These rules copy package inputs on explicit install; installed examples are configured later as external consumers. |
| ownership | The install prefix owns copied artifact/data; source and build inputs remain separate. |
| failure | Missing source input or unwritable destination fails installation; external consumer errors occur later. |
| cost | One finite file/directory copy at installation. |
| Design | [cmake/CrownInstall.cmake](../../../../cmake/CrownInstall.cmake), [CMakeLists.txt](../../../../CMakeLists.txt), [cmake/CrownConfig.cmake.in](../../../../cmake/CrownConfig.cmake.in), [docs/native_build.md](../../../native_build.md), [docs/cli.md](../../../cli.md), [examples/native-workflow/CMakeLists.txt](../../../../examples/native-workflow/CMakeLists.txt), [examples/cost-calibration/CMakeLists.txt](../../../../examples/cost-calibration/CMakeLists.txt), [examples/reoptimization/CMakeLists.txt](../../../../examples/reoptimization/CMakeLists.txt), [examples/ranking-evaluation/CMakeLists.txt](../../../../examples/ranking-evaluation/CMakeLists.txt), [examples/workload-measurement/CMakeLists.txt](../../../../examples/workload-measurement/CMakeLists.txt), [tests/integration/installed_workflow.py](../../../../tests/integration/installed_workflow.py) |

## B0017

[Lines 23–23](../../../../cmake/CrownInstall.cmake#L23); `build-command`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
install(FILES third_party/nlohmann/LICENSE.MIT DESTINATION "${CMAKE_INSTALL_DATADIR}/crown/licenses/nlohmann")

```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Install the nlohmann MIT license beside package data. |
| inputs / outputs | Copies the license beneath share/crown/licenses/nlohmann. |
| invariants | These rules copy package inputs on explicit install; installed examples are configured later as external consumers. |
| ownership | The install prefix owns copied artifact/data; source and build inputs remain separate. |
| failure | Missing source input or unwritable destination fails installation; external consumer errors occur later. |
| cost | One finite file/directory copy at installation. |
| Design | [cmake/CrownInstall.cmake](../../../../cmake/CrownInstall.cmake), [CMakeLists.txt](../../../../CMakeLists.txt), [cmake/CrownConfig.cmake.in](../../../../cmake/CrownConfig.cmake.in), [docs/native_build.md](../../../native_build.md), [docs/cli.md](../../../cli.md), [examples/native-workflow/CMakeLists.txt](../../../../examples/native-workflow/CMakeLists.txt), [examples/cost-calibration/CMakeLists.txt](../../../../examples/cost-calibration/CMakeLists.txt), [examples/reoptimization/CMakeLists.txt](../../../../examples/reoptimization/CMakeLists.txt), [examples/ranking-evaluation/CMakeLists.txt](../../../../examples/ranking-evaluation/CMakeLists.txt), [examples/workload-measurement/CMakeLists.txt](../../../../examples/workload-measurement/CMakeLists.txt), [tests/integration/installed_workflow.py](../../../../tests/integration/installed_workflow.py) |

## B0018

[Lines 24–24](../../../../cmake/CrownInstall.cmake#L24); `build-command`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
install(DIRECTORY third_party/nlohmann/patches/ DESTINATION "${CMAKE_INSTALL_DATADIR}/crown/patches/nlohmann")

```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Install the local nlohmann patch provenance directory. |
| inputs / outputs | Copies patch files beneath share/crown/patches/nlohmann. |
| invariants | These rules copy package inputs on explicit install; installed examples are configured later as external consumers. |
| ownership | The install prefix owns copied artifact/data; source and build inputs remain separate. |
| failure | Missing source input or unwritable destination fails installation; external consumer errors occur later. |
| cost | One finite file/directory copy at installation. |
| Design | [cmake/CrownInstall.cmake](../../../../cmake/CrownInstall.cmake), [CMakeLists.txt](../../../../CMakeLists.txt), [cmake/CrownConfig.cmake.in](../../../../cmake/CrownConfig.cmake.in), [docs/native_build.md](../../../native_build.md), [docs/cli.md](../../../cli.md), [examples/native-workflow/CMakeLists.txt](../../../../examples/native-workflow/CMakeLists.txt), [examples/cost-calibration/CMakeLists.txt](../../../../examples/cost-calibration/CMakeLists.txt), [examples/reoptimization/CMakeLists.txt](../../../../examples/reoptimization/CMakeLists.txt), [examples/ranking-evaluation/CMakeLists.txt](../../../../examples/ranking-evaluation/CMakeLists.txt), [examples/workload-measurement/CMakeLists.txt](../../../../examples/workload-measurement/CMakeLists.txt), [tests/integration/installed_workflow.py](../../../../tests/integration/installed_workflow.py) |

## B0019

[Lines 25–25](../../../../cmake/CrownInstall.cmake#L25); `build-command`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
install(DIRECTORY third_party/libpg_query/notices/ DESTINATION "${CMAKE_INSTALL_DATADIR}/crown/licenses/libpg_query")

```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Install libpg_query component notices. |
| inputs / outputs | Copies every vendored notice beneath share/crown/licenses/libpg_query. |
| invariants | These rules copy package inputs on explicit install; installed examples are configured later as external consumers. |
| ownership | The install prefix owns copied artifact/data; source and build inputs remain separate. |
| failure | Missing source input or unwritable destination fails installation; external consumer errors occur later. |
| cost | One finite file/directory copy at installation. |
| Design | [cmake/CrownInstall.cmake](../../../../cmake/CrownInstall.cmake), [CMakeLists.txt](../../../../CMakeLists.txt), [cmake/CrownConfig.cmake.in](../../../../cmake/CrownConfig.cmake.in), [docs/native_build.md](../../../native_build.md), [docs/cli.md](../../../cli.md), [examples/native-workflow/CMakeLists.txt](../../../../examples/native-workflow/CMakeLists.txt), [examples/cost-calibration/CMakeLists.txt](../../../../examples/cost-calibration/CMakeLists.txt), [examples/reoptimization/CMakeLists.txt](../../../../examples/reoptimization/CMakeLists.txt), [examples/ranking-evaluation/CMakeLists.txt](../../../../examples/ranking-evaluation/CMakeLists.txt), [examples/workload-measurement/CMakeLists.txt](../../../../examples/workload-measurement/CMakeLists.txt), [tests/integration/installed_workflow.py](../../../../tests/integration/installed_workflow.py) |

## B0020

[Lines 26–28](../../../../cmake/CrownInstall.cmake#L26); `build-command`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
configure_package_config_file(cmake/CrownConfig.cmake.in "${CMAKE_CURRENT_BINARY_DIR}/CrownConfig.cmake"

```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Generate CrownConfig.cmake with an install-relative libdir. |
| inputs / outputs | Configures the template and passes CMAKE_INSTALL_LIBDIR as a package path variable. |
| invariants | These commands declare CMake build/package metadata; they do not execute CROWN application work. |
| ownership | CMake target/package metadata only; no binary payload is owned here. |
| failure | Missing modules, invalid targets or unresolved export properties fail configuration/export generation. |
| cost | Configure/generate metadata over a finite list; no per-query CMake work. |
| Design | [cmake/CrownInstall.cmake](../../../../cmake/CrownInstall.cmake), [CMakeLists.txt](../../../../CMakeLists.txt), [cmake/CrownConfig.cmake.in](../../../../cmake/CrownConfig.cmake.in), [docs/native_build.md](../../../native_build.md), [docs/cli.md](../../../cli.md), [examples/native-workflow/CMakeLists.txt](../../../../examples/native-workflow/CMakeLists.txt), [examples/cost-calibration/CMakeLists.txt](../../../../examples/cost-calibration/CMakeLists.txt), [examples/reoptimization/CMakeLists.txt](../../../../examples/reoptimization/CMakeLists.txt), [examples/ranking-evaluation/CMakeLists.txt](../../../../examples/ranking-evaluation/CMakeLists.txt), [examples/workload-measurement/CMakeLists.txt](../../../../examples/workload-measurement/CMakeLists.txt), [tests/integration/installed_workflow.py](../../../../tests/integration/installed_workflow.py) |

## B0021

[Lines 29–30](../../../../cmake/CrownInstall.cmake#L29); `build-command`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
write_basic_package_version_file("${CMAKE_CURRENT_BINARY_DIR}/CrownConfigVersion.cmake"

```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Generate package version compatibility metadata. |
| inputs / outputs | Writes CrownConfigVersion.cmake using the project version and SameMinorVersion policy. |
| invariants | These commands declare CMake build/package metadata; they do not execute CROWN application work. |
| ownership | CMake target/package metadata only; no binary payload is owned here. |
| failure | Missing modules, invalid targets or unresolved export properties fail configuration/export generation. |
| cost | Configure/generate metadata over a finite list; no per-query CMake work. |
| Design | [cmake/CrownInstall.cmake](../../../../cmake/CrownInstall.cmake), [CMakeLists.txt](../../../../CMakeLists.txt), [cmake/CrownConfig.cmake.in](../../../../cmake/CrownConfig.cmake.in), [docs/native_build.md](../../../native_build.md), [docs/cli.md](../../../cli.md), [examples/native-workflow/CMakeLists.txt](../../../../examples/native-workflow/CMakeLists.txt), [examples/cost-calibration/CMakeLists.txt](../../../../examples/cost-calibration/CMakeLists.txt), [examples/reoptimization/CMakeLists.txt](../../../../examples/reoptimization/CMakeLists.txt), [examples/ranking-evaluation/CMakeLists.txt](../../../../examples/ranking-evaluation/CMakeLists.txt), [examples/workload-measurement/CMakeLists.txt](../../../../examples/workload-measurement/CMakeLists.txt), [tests/integration/installed_workflow.py](../../../../tests/integration/installed_workflow.py) |

## B0022

[Lines 31–31](../../../../cmake/CrownInstall.cmake#L31); `build-command`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
install(EXPORT CrownTargets NAMESPACE CROWN:: DESTINATION "${CMAKE_INSTALL_LIBDIR}/cmake/Crown")

```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Generate the namespaced install target export. |
| inputs / outputs | Writes CrownTargets metadata beneath libdir/cmake/Crown with CROWN:: names. |
| invariants | These commands declare CMake build/package metadata; they do not execute CROWN application work. |
| ownership | CMake target/package metadata only; no binary payload is owned here. |
| failure | Missing modules, invalid targets or unresolved export properties fail configuration/export generation. |
| cost | Configure/generate metadata over a finite list; no per-query CMake work. |
| Design | [cmake/CrownInstall.cmake](../../../../cmake/CrownInstall.cmake), [CMakeLists.txt](../../../../CMakeLists.txt), [cmake/CrownConfig.cmake.in](../../../../cmake/CrownConfig.cmake.in), [docs/native_build.md](../../../native_build.md), [docs/cli.md](../../../cli.md), [examples/native-workflow/CMakeLists.txt](../../../../examples/native-workflow/CMakeLists.txt), [examples/cost-calibration/CMakeLists.txt](../../../../examples/cost-calibration/CMakeLists.txt), [examples/reoptimization/CMakeLists.txt](../../../../examples/reoptimization/CMakeLists.txt), [examples/ranking-evaluation/CMakeLists.txt](../../../../examples/ranking-evaluation/CMakeLists.txt), [examples/workload-measurement/CMakeLists.txt](../../../../examples/workload-measurement/CMakeLists.txt), [tests/integration/installed_workflow.py](../../../../tests/integration/installed_workflow.py) |

## B0023

[Lines 32–34](../../../../cmake/CrownInstall.cmake#L32); `build-command`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
install(FILES "${CMAKE_CURRENT_BINARY_DIR}/CrownConfig.cmake"

```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Install package config and version metadata. |
| inputs / outputs | Copies generated CrownConfig.cmake and CrownConfigVersion.cmake beside the export. |
| invariants | These rules copy package inputs on explicit install; installed examples are configured later as external consumers. |
| ownership | The install prefix owns copied artifact/data; source and build inputs remain separate. |
| failure | Missing built/generated input, export dependency or unwritable destination fails installation. |
| cost | One target/artifact metadata generation or finite install copy. |
| Design | [cmake/CrownInstall.cmake](../../../../cmake/CrownInstall.cmake), [CMakeLists.txt](../../../../CMakeLists.txt), [cmake/CrownConfig.cmake.in](../../../../cmake/CrownConfig.cmake.in), [docs/native_build.md](../../../native_build.md), [docs/cli.md](../../../cli.md), [examples/native-workflow/CMakeLists.txt](../../../../examples/native-workflow/CMakeLists.txt), [examples/cost-calibration/CMakeLists.txt](../../../../examples/cost-calibration/CMakeLists.txt), [examples/reoptimization/CMakeLists.txt](../../../../examples/reoptimization/CMakeLists.txt), [examples/ranking-evaluation/CMakeLists.txt](../../../../examples/ranking-evaluation/CMakeLists.txt), [examples/workload-measurement/CMakeLists.txt](../../../../examples/workload-measurement/CMakeLists.txt), [tests/integration/installed_workflow.py](../../../../tests/integration/installed_workflow.py) |

## B0025

[Lines 36–36](../../../../cmake/CrownInstall.cmake#L36); `build-command`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
install(DIRECTORY schemas/ DESTINATION "${CMAKE_INSTALL_DATADIR}/crown/schemas" FILES_MATCHING PATTERN "*.json")

```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Install only JSON schemas as package data. |
| inputs / outputs | Copies matching *.json files beneath share/crown/schemas. |
| invariants | These rules copy package inputs on explicit install; installed examples are configured later as external consumers. |
| ownership | The install prefix owns copied artifact/data; source and build inputs remain separate. |
| failure | Missing source input or unwritable destination fails installation; external consumer errors occur later. |
| cost | One finite file/directory copy at installation. |
| Design | [cmake/CrownInstall.cmake](../../../../cmake/CrownInstall.cmake), [CMakeLists.txt](../../../../CMakeLists.txt), [cmake/CrownConfig.cmake.in](../../../../cmake/CrownConfig.cmake.in), [docs/native_build.md](../../../native_build.md), [docs/cli.md](../../../cli.md), [examples/native-workflow/CMakeLists.txt](../../../../examples/native-workflow/CMakeLists.txt), [examples/cost-calibration/CMakeLists.txt](../../../../examples/cost-calibration/CMakeLists.txt), [examples/reoptimization/CMakeLists.txt](../../../../examples/reoptimization/CMakeLists.txt), [examples/ranking-evaluation/CMakeLists.txt](../../../../examples/ranking-evaluation/CMakeLists.txt), [examples/workload-measurement/CMakeLists.txt](../../../../examples/workload-measurement/CMakeLists.txt), [tests/integration/installed_workflow.py](../../../../tests/integration/installed_workflow.py) |

## B0027

[Lines 38–38](../../../../cmake/CrownInstall.cmake#L38); `build-command`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
install(DIRECTORY examples/native-workflow/ DESTINATION "${CMAKE_INSTALL_DATADIR}/crown/examples/native-workflow")

```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Install the native-workflow example project and sources. |
| inputs / outputs | Copies the directory containing a CROWN::explain consumer. |
| invariants | These rules copy package inputs on explicit install; installed examples are configured later as external consumers. |
| ownership | The install prefix owns copied artifact/data; source and build inputs remain separate. |
| failure | Missing source input or unwritable destination fails installation; external consumer errors occur later. |
| cost | One finite file/directory copy at installation. |
| Design | [cmake/CrownInstall.cmake](../../../../cmake/CrownInstall.cmake), [CMakeLists.txt](../../../../CMakeLists.txt), [cmake/CrownConfig.cmake.in](../../../../cmake/CrownConfig.cmake.in), [docs/native_build.md](../../../native_build.md), [docs/cli.md](../../../cli.md), [examples/native-workflow/CMakeLists.txt](../../../../examples/native-workflow/CMakeLists.txt), [examples/cost-calibration/CMakeLists.txt](../../../../examples/cost-calibration/CMakeLists.txt), [examples/reoptimization/CMakeLists.txt](../../../../examples/reoptimization/CMakeLists.txt), [examples/ranking-evaluation/CMakeLists.txt](../../../../examples/ranking-evaluation/CMakeLists.txt), [examples/workload-measurement/CMakeLists.txt](../../../../examples/workload-measurement/CMakeLists.txt), [tests/integration/installed_workflow.py](../../../../tests/integration/installed_workflow.py) |

## B0028

[Lines 39–39](../../../../cmake/CrownInstall.cmake#L39); `build-command`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
install(DIRECTORY examples/cost-calibration/ DESTINATION "${CMAKE_INSTALL_DATADIR}/crown/examples/cost-calibration")

```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Install the cost-calibration example project and sources. |
| inputs / outputs | Copies the directory containing a CROWN::ranking_runtime consumer. |
| invariants | These rules copy package inputs on explicit install; installed examples are configured later as external consumers. |
| ownership | The install prefix owns copied artifact/data; source and build inputs remain separate. |
| failure | Missing source input or unwritable destination fails installation; external consumer errors occur later. |
| cost | One finite file/directory copy at installation. |
| Design | [cmake/CrownInstall.cmake](../../../../cmake/CrownInstall.cmake), [CMakeLists.txt](../../../../CMakeLists.txt), [cmake/CrownConfig.cmake.in](../../../../cmake/CrownConfig.cmake.in), [docs/native_build.md](../../../native_build.md), [docs/cli.md](../../../cli.md), [examples/native-workflow/CMakeLists.txt](../../../../examples/native-workflow/CMakeLists.txt), [examples/cost-calibration/CMakeLists.txt](../../../../examples/cost-calibration/CMakeLists.txt), [examples/reoptimization/CMakeLists.txt](../../../../examples/reoptimization/CMakeLists.txt), [examples/ranking-evaluation/CMakeLists.txt](../../../../examples/ranking-evaluation/CMakeLists.txt), [examples/workload-measurement/CMakeLists.txt](../../../../examples/workload-measurement/CMakeLists.txt), [tests/integration/installed_workflow.py](../../../../tests/integration/installed_workflow.py) |

## B0029

[Lines 40–40](../../../../cmake/CrownInstall.cmake#L40); `build-command`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
install(DIRECTORY examples/workload-measurement/ DESTINATION "${CMAKE_INSTALL_DATADIR}/crown/examples/workload-measurement")

```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Install the workload-measurement example project and sources. |
| inputs / outputs | Copies the directory containing a CROWN::runtime consumer. |
| invariants | These rules copy package inputs on explicit install; installed examples are configured later as external consumers. |
| ownership | The install prefix owns copied artifact/data; source and build inputs remain separate. |
| failure | Missing source input or unwritable destination fails installation; external consumer errors occur later. |
| cost | One finite file/directory copy at installation. |
| Design | [cmake/CrownInstall.cmake](../../../../cmake/CrownInstall.cmake), [CMakeLists.txt](../../../../CMakeLists.txt), [cmake/CrownConfig.cmake.in](../../../../cmake/CrownConfig.cmake.in), [docs/native_build.md](../../../native_build.md), [docs/cli.md](../../../cli.md), [examples/native-workflow/CMakeLists.txt](../../../../examples/native-workflow/CMakeLists.txt), [examples/cost-calibration/CMakeLists.txt](../../../../examples/cost-calibration/CMakeLists.txt), [examples/reoptimization/CMakeLists.txt](../../../../examples/reoptimization/CMakeLists.txt), [examples/ranking-evaluation/CMakeLists.txt](../../../../examples/ranking-evaluation/CMakeLists.txt), [examples/workload-measurement/CMakeLists.txt](../../../../examples/workload-measurement/CMakeLists.txt), [tests/integration/installed_workflow.py](../../../../tests/integration/installed_workflow.py) |

## B0030

[Lines 41–41](../../../../cmake/CrownInstall.cmake#L41); `build-command`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
install(DIRECTORY examples/ranking-evaluation/ DESTINATION "${CMAKE_INSTALL_DATADIR}/crown/examples/ranking-evaluation")

```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Install the ranking-evaluation example project and sources. |
| inputs / outputs | Copies the directory containing a CROWN::selection_runtime consumer. |
| invariants | These rules copy package inputs on explicit install; installed examples are configured later as external consumers. |
| ownership | The install prefix owns copied artifact/data; source and build inputs remain separate. |
| failure | Missing source input or unwritable destination fails installation; external consumer errors occur later. |
| cost | One finite file/directory copy at installation. |
| Design | [cmake/CrownInstall.cmake](../../../../cmake/CrownInstall.cmake), [CMakeLists.txt](../../../../CMakeLists.txt), [cmake/CrownConfig.cmake.in](../../../../cmake/CrownConfig.cmake.in), [docs/native_build.md](../../../native_build.md), [docs/cli.md](../../../cli.md), [examples/native-workflow/CMakeLists.txt](../../../../examples/native-workflow/CMakeLists.txt), [examples/cost-calibration/CMakeLists.txt](../../../../examples/cost-calibration/CMakeLists.txt), [examples/reoptimization/CMakeLists.txt](../../../../examples/reoptimization/CMakeLists.txt), [examples/ranking-evaluation/CMakeLists.txt](../../../../examples/ranking-evaluation/CMakeLists.txt), [examples/workload-measurement/CMakeLists.txt](../../../../examples/workload-measurement/CMakeLists.txt), [tests/integration/installed_workflow.py](../../../../tests/integration/installed_workflow.py) |

## B0031

[Lines 42–42](../../../../cmake/CrownInstall.cmake#L42); `build-command`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
install(DIRECTORY examples/reoptimization/ DESTINATION "${CMAKE_INSTALL_DATADIR}/crown/examples/reoptimization")

```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Install the reoptimization example project and sources. |
| inputs / outputs | Copies the directory containing a CROWN::selection_runtime consumer. |
| invariants | These rules copy package inputs on explicit install; installed examples are configured later as external consumers. |
| ownership | The install prefix owns copied artifact/data; source and build inputs remain separate. |
| failure | Missing source input or unwritable destination fails installation; external consumer errors occur later. |
| cost | One finite file/directory copy at installation. |
| Design | [cmake/CrownInstall.cmake](../../../../cmake/CrownInstall.cmake), [CMakeLists.txt](../../../../CMakeLists.txt), [cmake/CrownConfig.cmake.in](../../../../cmake/CrownConfig.cmake.in), [docs/native_build.md](../../../native_build.md), [docs/cli.md](../../../cli.md), [examples/native-workflow/CMakeLists.txt](../../../../examples/native-workflow/CMakeLists.txt), [examples/cost-calibration/CMakeLists.txt](../../../../examples/cost-calibration/CMakeLists.txt), [examples/reoptimization/CMakeLists.txt](../../../../examples/reoptimization/CMakeLists.txt), [examples/ranking-evaluation/CMakeLists.txt](../../../../examples/ranking-evaluation/CMakeLists.txt), [examples/workload-measurement/CMakeLists.txt](../../../../examples/workload-measurement/CMakeLists.txt), [tests/integration/installed_workflow.py](../../../../tests/integration/installed_workflow.py) |

## B0032

[Lines 43–43](../../../../cmake/CrownInstall.cmake#L43); `build-command`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L43-L43:sha256:bb596baf16bdd0dd1497f4d769a757753e7ca91939713b26e726d7788acf3a07
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Install the independent public meta-candidate example sources. |
| inputs / outputs | The complete examples/meta-candidates directory is copied under share/crown/examples/meta-candidates. |
| invariants | The example finds CROWN::meta_candidates through package export; its build is not coupled to source-tree headers. |
| ownership | The configured build or installation owns these target/file definitions; no query row, runtime owner or mutable cursor is retained by CMake. |
| failure | Ordinary configure, compile, link, install or test-process errors remain explicit at their own boundary; no engine rollback framework is introduced. |
| cost | Configure/install metadata and explicit compilation/copy/test work only. This adds no per-update operation or retained runtime index. |
| Design | [docs/meta_candidate_adapter.md](../../../meta_candidate_adapter.md), [docs/meta_decompositions.md](../../../meta_decompositions.md) |

## B0033

[Lines 44–44](../../../../cmake/CrownInstall.cmake#L44); `build-command`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L44-L44:sha256:26144be26b6e6c91100071338cf8a617319de438116b398ff8f9e60d01018e4d
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Install the component-planning example sources under the Crown shared-data example tree. |
| inputs / outputs | Copies the source directory to \`${CMAKE_INSTALL_DATADIR}/crown/examples/component-planning\`. |
| invariants | This is example data installation, not an installed executable or library export. |
| ownership | The install rule copies maintained example files at install time. |
| failure | Missing source directory or install permission fails the install step. |
| cost | Copies the directory contents during installation; no runtime work. |
| Design | [examples/component-planning/CMakeLists.txt](../../../../examples/component-planning/CMakeLists.txt), [examples/component-planning/main.cpp](../../../../examples/component-planning/main.cpp) |

## B0034

[Lines 45–45](../../../../cmake/CrownInstall.cmake#L45); `build-command`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L45-L45:sha256:4bf618d000b4e7aca679b24cc1ddc96b1ba60fc5fabbc2217588d0aad10ee879
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Install the component-runtime example sources under the Crown shared-data example tree. |
| inputs / outputs | Copies the source directory to \`${CMAKE_INSTALL_DATADIR}/crown/examples/component-runtime\`. |
| invariants | This installs the self-contained consumer example sources; it does not install these executables as package targets. |
| ownership | The install rule copies maintained example files at install time. |
| failure | Missing source directory or install permission fails the install step. |
| cost | Copies the directory contents during installation; no runtime work. |
| Design | [examples/component-runtime/CMakeLists.txt](../../../../examples/component-runtime/CMakeLists.txt), [docs/legacy_baselines.md](../../../legacy_baselines.md) |

## B0035

[Lines 46–46](../../../../cmake/CrownInstall.cmake#L46); `build-command`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L46-L46:sha256:983e1969c92ca25ac192a55fd12d0fe33bc2479c463d59b295777a16b32ed564
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Install the independent-query example project as shared-data sources. |
| inputs / outputs | Copy examples/independent-queries/ contents to ${CMAKE_INSTALL_DATADIR}/crown/examples/independent-queries. |
| invariants | The rule installs project/source files, not the built executable. |
| ownership | Prefix owns installed copies; eventual client owns sessions. |
| failure | Missing source or unwritable destination fails installation. |
| cost | Copies directory contents; runs no query. |
| Design | [docs/independent_queries.md](../../../independent_queries.md), [include/crown/runtime/queries.hpp](../../../../include/crown/runtime/queries.hpp), [src/runtime/queries.cpp](../../../../src/runtime/queries.cpp), [examples/independent-queries/CMakeLists.txt](../../../../examples/independent-queries/CMakeLists.txt), [examples/independent-queries/main.cpp](../../../../examples/independent-queries/main.cpp) |

## B0036

[Lines 47–47](../../../../cmake/CrownInstall.cmake#L47); `build-command`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L47-L47:sha256:9355d35d4e9b2eff360fcd13ed15c4e9e266f5ce6c0390401dec122d149d4792
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Install the structural ComponentReplay helper alongside component-runtime example data. |
| inputs / outputs | Copies \`tools/support/ComponentReplay.scala\` into the component-runtime shared-data directory. |
| invariants | The helper is optional tooling input and is not an automatically launched runtime or fetched dependency. |
| ownership | The install rule copies the exact maintained helper file. |
| failure | Missing helper source or install permission fails the install step. |
| cost | Copies one file at install time; no Scala process is launched. |
| Design | [tools/support/ComponentReplay.scala](../../../../tools/support/ComponentReplay.scala), [docs/legacy_baselines.md](../../../legacy_baselines.md) |

## B0038

[Lines 49–49](../../../../cmake/CrownInstall.cmake#L49); `build-command`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
install(FILES tools/prepare_workflow_input.py DESTINATION "${CMAKE_INSTALL_DATADIR}/crown/examples/native-workflow")

```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Install the workflow-input preparation helper beside its example. |
| inputs / outputs | Copies tools/prepare_workflow_input.py to the native-workflow example directory. |
| invariants | These rules copy package inputs on explicit install; installed examples are configured later as external consumers. |
| ownership | The install prefix owns copied artifact/data; source and build inputs remain separate. |
| failure | Missing source input or unwritable destination fails installation; external consumer errors occur later. |
| cost | One finite file/directory copy at installation. |
| Design | [cmake/CrownInstall.cmake](../../../../cmake/CrownInstall.cmake), [CMakeLists.txt](../../../../CMakeLists.txt), [cmake/CrownConfig.cmake.in](../../../../cmake/CrownConfig.cmake.in), [docs/native_build.md](../../../native_build.md), [docs/cli.md](../../../cli.md), [examples/native-workflow/CMakeLists.txt](../../../../examples/native-workflow/CMakeLists.txt), [examples/cost-calibration/CMakeLists.txt](../../../../examples/cost-calibration/CMakeLists.txt), [examples/reoptimization/CMakeLists.txt](../../../../examples/reoptimization/CMakeLists.txt), [examples/ranking-evaluation/CMakeLists.txt](../../../../examples/ranking-evaluation/CMakeLists.txt), [examples/workload-measurement/CMakeLists.txt](../../../../examples/workload-measurement/CMakeLists.txt), [tests/integration/installed_workflow.py](../../../../tests/integration/installed_workflow.py) |

## B0040

[Lines 51–51](../../../../cmake/CrownInstall.cmake#L51); `build-command`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
install(FILES docs/cli.md docs/sql_aggregate_input.md DESTINATION "${CMAKE_INSTALL_DATADIR}/crown/docs")

```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Install the set and R2 input/CLI usage guides. |
| inputs / outputs | Copies docs/cli.md and docs/sql_aggregate_input.md into share/crown/docs. The existing schemas directory rule separately includes the new structural input schema. |
| invariants | This is an install-only change. Source/design cross-references use the repository layout; complete installed-document navigation is not certified. |
| ownership | The install prefix owns copied artifact/data; source and build inputs remain separate. |
| failure | Missing source input or unwritable destination fails installation; external consumer errors occur later. |
| cost | Two bounded documentation-file copies during explicit install; no native runtime cost. |
| Design | [cmake/CrownInstall.cmake](../../../../cmake/CrownInstall.cmake), [docs/cli.md](../../../cli.md), [docs/sql_aggregate_input.md](../../../sql_aggregate_input.md), [schemas/sql-aggregate-input-v1.schema.json](../../../../schemas/sql-aggregate-input-v1.schema.json) |
