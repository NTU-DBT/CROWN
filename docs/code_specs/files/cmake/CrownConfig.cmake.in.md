# `cmake/CrownConfig.cmake.in` — block usage map

[Source](../../../../cmake/CrownConfig.cmake.in) · [Source index](../../README.md) · [Subsystem contracts](../../subsystem_contracts.md) · [Reviewed primitives](../../primitives.md)

Define native target boundaries, pinned dependencies, compilation options, installation and test registration.

Snapshot SHA-256: `68be007cc31fc1c93135b48be53a965dfddd2d1015b91fc0b00a6bb97948d022`. 12 lines partitioned into 10 blocks using `cmake_commands`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [build](../../subsystem_contracts.md#build). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/native_build.md](../../../native_build.md), [docs/source_baselines.md](../../../source_baselines.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–1](../../../../cmake/CrownConfig.cmake.in#L1) | Member/declaration region. |  · [reviewed contract](#b0001) |
| [B0002 · 2–2](../../../../cmake/CrownConfig.cmake.in#L2) | CMake command: include(CMakeFindDependencyMacro) |  · [reviewed contract](#b0002) |
| [B0003 · 3–3](../../../../cmake/CrownConfig.cmake.in#L3) | CMake command: find_dependency(Threads) |  · [reviewed contract](#b0003) |
| [B0004 · 4–4](../../../../cmake/CrownConfig.cmake.in#L4) | CMake command: if(NOT TARGET CROWN::pg_query) |  · [reviewed contract](#b0004) |
| [B0005 · 5–5](../../../../cmake/CrownConfig.cmake.in#L5) | CMake command: add_library(CROWN::pg_query STATIC IMPORTED) |  · [reviewed contract](#b0005) |
| [B0006 · 6–6](../../../../cmake/CrownConfig.cmake.in#L6) | CMake command: set_and_check(_crown_pg_query_archive "@PACKAGE_CMAKE_INSTALL_LIBDIR@/crown/deps/libpg_query.a") |  · [reviewed contract](#b0006) |
| [B0007 · 7–9](../../../../cmake/CrownConfig.cmake.in#L7) | CMake command: set_target_properties(CROWN::pg_query PROPERTIES |  · [reviewed contract](#b0007) |
| [B0008 · 10–10](../../../../cmake/CrownConfig.cmake.in#L10) | CMake command: endif() |  · [reviewed contract](#b0008) |
| [B0009 · 11–11](../../../../cmake/CrownConfig.cmake.in#L11) | CMake command: include("${CMAKE_CURRENT_LIST_DIR}/CrownTargets.cmake") |  · [reviewed contract](#b0009) |
| [B0010 · 12–12](../../../../cmake/CrownConfig.cmake.in#L12) | CMake command: check_required_components(Crown) |  · [reviewed contract](#b0010) |

## B0001

[Lines 1–1](../../../../cmake/CrownConfig.cmake.in#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@PACKAGE_INIT@
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Expand relocatable package initialization and helper macros. |
| inputs / outputs | configure_package_config_file substitutes this token into installed CrownConfig.cmake. |
| invariants | This template is not directly executable CMake; generated helpers supply set_and_check and check_required_components. |
| ownership | Generated configuration owns prefix/path variables and macro definitions; template bytes remain source input. |
| failure | Template/configuration errors belong to configure/generation; generated helper failures occur when a consumer finds the package. |
| cost | One offline template substitution plus generated consumer configure metadata. |
| Design | [cmake/CrownConfig.cmake.in](../../../../cmake/CrownConfig.cmake.in), [cmake/CrownInstall.cmake](../../../../cmake/CrownInstall.cmake), [CMakeLists.txt](../../../../CMakeLists.txt), [tests/integration/installed_workflow.py](../../../../tests/integration/installed_workflow.py), [docs/cli.md](../../../cli.md), [docs/native_build.md](../../../native_build.md) |

## B0002

[Lines 2–2](../../../../cmake/CrownConfig.cmake.in#L2); `build-command`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
include(CMakeFindDependencyMacro)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Load the CMake dependency-forwarding macro. |
| inputs / outputs | Consumer CMake module search supplies find_dependency. |
| invariants | Runs when installed package config is included, not per query. |
| ownership | Consumer CMake scope retains macro definitions. |
| failure | Missing/invalid module fails package configuration. |
| cost | One configure-time module resolution/read. |
| Design | [cmake/CrownConfig.cmake.in](../../../../cmake/CrownConfig.cmake.in), [cmake/CrownInstall.cmake](../../../../cmake/CrownInstall.cmake), [CMakeLists.txt](../../../../CMakeLists.txt), [tests/integration/installed_workflow.py](../../../../tests/integration/installed_workflow.py), [docs/cli.md](../../../cli.md), [docs/native_build.md](../../../native_build.md) |

## B0003

[Lines 3–3](../../../../cmake/CrownConfig.cmake.in#L3); `build-command`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
find_dependency(Threads)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Require the installed consumer thread dependency. |
| inputs / outputs | Forwards package quiet/required behavior to Threads discovery. |
| invariants | A missing dependency prevents a successful Crown package result; this does not start native worker threads. |
| ownership | Consumer owns imported Threads target/cache metadata. |
| failure | Dependency discovery may mark package not found or stop required configuration. |
| cost | Configure probes/cache lookup; may perform platform compiler/link checks. |
| Design | [cmake/CrownConfig.cmake.in](../../../../cmake/CrownConfig.cmake.in), [cmake/CrownInstall.cmake](../../../../cmake/CrownInstall.cmake), [CMakeLists.txt](../../../../CMakeLists.txt), [tests/integration/installed_workflow.py](../../../../tests/integration/installed_workflow.py), [docs/cli.md](../../../cli.md), [docs/native_build.md](../../../native_build.md) |

## B0004

[Lines 4–4](../../../../cmake/CrownConfig.cmake.in#L4); `build-command`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
if(NOT TARGET CROWN::pg_query)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Create a parser import only if consumer has no target of that name. |
| inputs / outputs | Existing target graph to conditional import setup. |
| invariants | An existing target is reused without validating its archive or ABI here; public export include remains outside this condition. |
| ownership | No new native payload; examines consumer CMake target table. |
| failure | Malformed CMake context fails configure; false condition simply skips the block. |
| cost | Constant-size target lookup and configure branch. |
| Design | [cmake/CrownConfig.cmake.in](../../../../cmake/CrownConfig.cmake.in), [cmake/CrownInstall.cmake](../../../../cmake/CrownInstall.cmake), [CMakeLists.txt](../../../../CMakeLists.txt), [tests/integration/installed_workflow.py](../../../../tests/integration/installed_workflow.py), [docs/cli.md](../../../cli.md), [docs/native_build.md](../../../native_build.md) |

## B0005

[Lines 5–5](../../../../cmake/CrownConfig.cmake.in#L5); `build-command`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
add_library(CROWN::pg_query STATIC IMPORTED)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Declare a consumer-side imported static parser target. |
| inputs / outputs | Missing target name to a CMake imported library placeholder. |
| invariants | No parser source compilation is registered here; archive location and link interface are assigned below. Imported target lacks GLOBAL and follows normal directory scope. |
| ownership | Consumer CMake owns target metadata; installed archive remains an on-disk input. |
| failure | Target-name/context errors fail configure. |
| cost | Target declaration only; no query runtime work. |
| Design | [cmake/CrownConfig.cmake.in](../../../../cmake/CrownConfig.cmake.in), [cmake/CrownInstall.cmake](../../../../cmake/CrownInstall.cmake), [CMakeLists.txt](../../../../CMakeLists.txt), [tests/integration/installed_workflow.py](../../../../tests/integration/installed_workflow.py), [docs/cli.md](../../../cli.md), [docs/native_build.md](../../../native_build.md) |

## B0006

[Lines 6–6](../../../../cmake/CrownConfig.cmake.in#L6); `build-command`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
set_and_check(_crown_pg_query_archive
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Resolve and require the installed parser archive in the moved prefix. |
| inputs / outputs | Configured package libdir to checked archive-path variable. |
| invariants | Generated PACKAGE_INIT helper checks file existence; it does not checksum archive contents. |
| ownership | Consumer scope owns path text; archive bytes are borrowed package input. |
| failure | Missing installed archive causes generated helper fatal configuration error. |
| cost | Path substitution and one configure-time filesystem existence check. |
| Design | [cmake/CrownConfig.cmake.in](../../../../cmake/CrownConfig.cmake.in), [cmake/CrownInstall.cmake](../../../../cmake/CrownInstall.cmake), [CMakeLists.txt](../../../../CMakeLists.txt), [tests/integration/installed_workflow.py](../../../../tests/integration/installed_workflow.py), [docs/cli.md](../../../cli.md), [docs/native_build.md](../../../native_build.md) |

## B0007

[Lines 7–9](../../../../cmake/CrownConfig.cmake.in#L7); `build-command`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
set_target_properties(CROWN::pg_query PROPERTIES
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Bind imported parser archive and transitive Threads linkage. |
| inputs / outputs | Checked archive path and Threads::Threads to target properties. |
| invariants | IMPORTED_LOCATION points to installed archive; INTERFACE_LINK_LIBRARIES propagates thread dependency to consumers. |
| ownership | CMake target retains path/dependency strings, not loaded parser state. |
| failure | Missing target/property errors fail configure; unusable archive/link errors occur later during consumer build. |
| cost | Small configure metadata assignment; archive link work belongs to explicit build. |
| Design | [cmake/CrownConfig.cmake.in](../../../../cmake/CrownConfig.cmake.in), [cmake/CrownInstall.cmake](../../../../cmake/CrownInstall.cmake), [CMakeLists.txt](../../../../CMakeLists.txt), [tests/integration/installed_workflow.py](../../../../tests/integration/installed_workflow.py), [docs/cli.md](../../../cli.md), [docs/native_build.md](../../../native_build.md) |

## B0008

[Lines 10–10](../../../../cmake/CrownConfig.cmake.in#L10); `build-command`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
endif()
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Close optional parser-target setup. |
| inputs / outputs | if(NOT TARGET CROWN::pg_query) scope to unconditional export loading. |
| invariants | Existing and newly declared parser targets both proceed to the following CrownTargets include. |
| ownership | No payload or additional target ownership. |
| failure | CMake nesting/syntax errors fail configure. |
| cost | Configure control only. |
| Design | [cmake/CrownConfig.cmake.in](../../../../cmake/CrownConfig.cmake.in), [cmake/CrownInstall.cmake](../../../../cmake/CrownInstall.cmake), [CMakeLists.txt](../../../../CMakeLists.txt), [tests/integration/installed_workflow.py](../../../../tests/integration/installed_workflow.py), [docs/cli.md](../../../cli.md), [docs/native_build.md](../../../native_build.md) |

## B0009

[Lines 11–11](../../../../cmake/CrownConfig.cmake.in#L11); `build-command`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
include("${CMAKE_CURRENT_LIST_DIR}/CrownTargets.cmake")
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Load exported public CROWN target graph beside installed package config. |
| inputs / outputs | Current installed config directory to generated target definitions. |
| invariants | Uses package-local exported file after parser dependency setup, supporting relocation. Target graph is distinct from runtime checked program authority. |
| ownership | Consumer CMake owns imported public targets/properties; files remain in install prefix. |
| failure | Missing/inconsistent export graph fails configure or a later consumer link. |
| cost | Reads/evaluates exported target metadata; no query-time execution. |
| Design | [cmake/CrownConfig.cmake.in](../../../../cmake/CrownConfig.cmake.in), [cmake/CrownInstall.cmake](../../../../cmake/CrownInstall.cmake), [CMakeLists.txt](../../../../CMakeLists.txt), [tests/integration/installed_workflow.py](../../../../tests/integration/installed_workflow.py), [docs/cli.md](../../../cli.md), [docs/native_build.md](../../../native_build.md) |

## B0010

[Lines 12–12](../../../../cmake/CrownConfig.cmake.in#L12); `build-command`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
check_required_components(Crown)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Mark package unavailable when requested required components were not found. |
| inputs / outputs | Consumer requested component state to Crown_FOUND via generated macro. |
| invariants | Checks package component flags; it does not enable runtime operators or validate query plans. |
| ownership | Consumer package variables are updated in CMake scope. |
| failure | Unsatisfied required component makes package not found; outer required find_package controls fatal presentation. |
| cost | Loops over requested component names during package configuration. |
| Design | [cmake/CrownConfig.cmake.in](../../../../cmake/CrownConfig.cmake.in), [cmake/CrownInstall.cmake](../../../../cmake/CrownInstall.cmake), [CMakeLists.txt](../../../../CMakeLists.txt), [tests/integration/installed_workflow.py](../../../../tests/integration/installed_workflow.py), [docs/cli.md](../../../cli.md), [docs/native_build.md](../../../native_build.md) |
