# `cmake/LibPgQuery.cmake` — block usage map

[Source](../../../../cmake/LibPgQuery.cmake) · [Source index](../../README.md) · [Subsystem contracts](../../subsystem_contracts.md) · [Reviewed primitives](../../primitives.md)

Define native target boundaries, pinned dependencies, compilation options, installation and test registration.

Snapshot SHA-256: `0d9c5d00986a553d6145791e90310c39c58579ef956979132c3292530494c4ef`. 114 lines partitioned into 62 blocks using `cmake_commands`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [build](../../subsystem_contracts.md#build). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/native_build.md](../../../native_build.md), [docs/source_baselines.md](../../../source_baselines.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–3](../../../../cmake/LibPgQuery.cmake#L1) | Member/declaration region. | 1 loop sites; source comment (unverified): # Build the pinned libpg_query source archive locally. Keep this as an · [reviewed contract](#b0001) |
| [B0002 · 4–5](../../../../cmake/LibPgQuery.cmake#L4) | CMake command: set(_crown_pg_query_archive |  · [reviewed contract](#b0002) |
| [B0003 · 6–7](../../../../cmake/LibPgQuery.cmake#L6) | CMake command: set(_crown_pg_query_sha256 |  · [reviewed contract](#b0003) |
| [B0004 · 8–8](../../../../cmake/LibPgQuery.cmake#L8) | CMake command: file(SHA256 "${_crown_pg_query_archive}" _crown_pg_query_actual_sha256) |  · [reviewed contract](#b0004) |
| [B0005 · 9–9](../../../../cmake/LibPgQuery.cmake#L9) | CMake command: if(NOT _crown_pg_query_actual_sha256 STREQUAL _crown_pg_query_sha256) |  · [reviewed contract](#b0005) |
| [B0006 · 10–11](../../../../cmake/LibPgQuery.cmake#L10) | CMake command: message(FATAL_ERROR |  · [reviewed contract](#b0006) |
| [B0007 · 12–12](../../../../cmake/LibPgQuery.cmake#L12) | CMake command: endif() |  · [reviewed contract](#b0007) |
| [B0008 · 13–13](../../../../cmake/LibPgQuery.cmake#L13) | Explanatory comments or spacing. |  |
| [B0009 · 14–14](../../../../cmake/LibPgQuery.cmake#L14) | CMake command: find_program(CROWN_MAKE_EXECUTABLE NAMES gmake make REQUIRED) |  · [reviewed contract](#b0009) |
| [B0010 · 15–19](../../../../cmake/LibPgQuery.cmake#L15) | CMake command: execute_process( |  · [reviewed contract](#b0010) |
| [B0011 · 20–20](../../../../cmake/LibPgQuery.cmake#L20) | CMake command: if(NOT _crown_make_result EQUAL 0 OR NOT _crown_make_version MATCHES "GNU Make") |  · [reviewed contract](#b0011) |
| [B0012 · 21–22](../../../../cmake/LibPgQuery.cmake#L21) | CMake command: message(FATAL_ERROR |  · [reviewed contract](#b0012) |
| [B0013 · 23–23](../../../../cmake/LibPgQuery.cmake#L23) | CMake command: endif() |  · [reviewed contract](#b0013) |
| [B0014 · 24–24](../../../../cmake/LibPgQuery.cmake#L24) | Explanatory comments or spacing. |  |
| [B0015 · 25–25](../../../../cmake/LibPgQuery.cmake#L25) | CMake command: find_package(Threads REQUIRED) |  · [reviewed contract](#b0015) |
| [B0016 · 26–26](../../../../cmake/LibPgQuery.cmake#L26) | Explanatory comments or spacing. |  |
| [B0017 · 27–27](../../../../cmake/LibPgQuery.cmake#L27) | CMake command: set(_crown_pg_query_extract_root "${CMAKE_CURRENT_BINARY_DIR}/_deps/libpg_query") |  · [reviewed contract](#b0017) |
| [B0018 · 28–28](../../../../cmake/LibPgQuery.cmake#L28) | CMake command: set(_crown_pg_query_source_dir "${_crown_pg_query_extract_root}/libpg_query-18.1.0") |  · [reviewed contract](#b0018) |
| [B0019 · 29–29](../../../../cmake/LibPgQuery.cmake#L29) | CMake command: set(_crown_pg_query_library "${_crown_pg_query_source_dir}/libpg_query.a") |  · [reviewed contract](#b0019) |
| [B0020 · 30–30](../../../../cmake/LibPgQuery.cmake#L30) | CMake command: set(_crown_pg_query_header "${_crown_pg_query_source_dir}/pg_query.h") |  · [reviewed contract](#b0020) |
| [B0021 · 31–33](../../../../cmake/LibPgQuery.cmake#L31) | Member/declaration region. | source comment (unverified): # CMake validates INTERFACE include directories during generation. Create the · [reviewed contract](#b0021) |
| [B0022 · 34–34](../../../../cmake/LibPgQuery.cmake#L34) | CMake command: file(MAKE_DIRECTORY "${_crown_pg_query_source_dir}") |  · [reviewed contract](#b0022) |
| [B0023 · 35–38](../../../../cmake/LibPgQuery.cmake#L35) | Member/declaration region. | source comment (unverified): # Make reconfiguration invalidate the static library when compiler or flags · [reviewed contract](#b0023) |
| [B0024 · 39–39](../../../../cmake/LibPgQuery.cmake#L39) | CMake command: set(_crown_pg_query_build_config "${CMAKE_CURRENT_BINARY_DIR}/_deps/libpg_query-build-config.txt") |  · [reviewed contract](#b0024) |
| [B0025 · 40–49](../../../../cmake/LibPgQuery.cmake#L40) | CMake command: string(CONCAT _crown_pg_query_build_config_content |  · [reviewed contract](#b0025) |
| [B0026 · 50–50](../../../../cmake/LibPgQuery.cmake#L50) | CMake command: file(GENERATE OUTPUT "${_crown_pg_query_build_config}" CONTENT "${_crown_pg_query_build_config_content}") |  · [reviewed contract](#b0026) |
| [B0027 · 51–54](../../../../cmake/LibPgQuery.cmake#L51) | Member/declaration region. | source comment (unverified): # Recheck the vendored archive at build time as well as configure time, so a · [reviewed contract](#b0027) |
| [B0028 · 55–55](../../../../cmake/LibPgQuery.cmake#L55) | CMake command: set(_crown_pg_query_verify_script "${CMAKE_CURRENT_BINARY_DIR}/_deps/verify-libpg-query.cmake") |  · [reviewed contract](#b0028) |
| [B0029 · 56–60](../../../../cmake/LibPgQuery.cmake#L56) | CMake command: string(CONCAT _crown_pg_query_verify_contents |  · [reviewed contract](#b0029) |
| [B0030 · 61–61](../../../../cmake/LibPgQuery.cmake#L61) | CMake command: file(GENERATE OUTPUT "${_crown_pg_query_verify_script}" CONTENT "${_crown_pg_query_verify_contents}") |  · [reviewed contract](#b0030) |
| [B0031 · 62–64](../../../../cmake/LibPgQuery.cmake#L62) | Member/declaration region. | source comment (unverified): # Pass through CMake's C flags and instrument the dependency itself when · [reviewed contract](#b0031) |
| [B0032 · 65–65](../../../../cmake/LibPgQuery.cmake#L65) | CMake command: set(_crown_pg_query_cflags "${CMAKE_C_FLAGS}") |  · [reviewed contract](#b0032) |
| [B0033 · 66–66](../../../../cmake/LibPgQuery.cmake#L66) | CMake command: if(CMAKE_SYSROOT) |  · [reviewed contract](#b0033) |
| [B0034 · 67–67](../../../../cmake/LibPgQuery.cmake#L67) | CMake command: string(APPEND _crown_pg_query_cflags " --sysroot=${CMAKE_SYSROOT}") |  · [reviewed contract](#b0034) |
| [B0035 · 68–68](../../../../cmake/LibPgQuery.cmake#L68) | CMake command: endif() |  · [reviewed contract](#b0035) |
| [B0036 · 69–69](../../../../cmake/LibPgQuery.cmake#L69) | CMake command: set(_crown_pg_query_cc "${CMAKE_C_COMPILER}") |  · [reviewed contract](#b0036) |
| [B0037 · 70–70](../../../../cmake/LibPgQuery.cmake#L70) | CMake command: if(CMAKE_C_COMPILER_ARG1) |  · [reviewed contract](#b0037) |
| [B0038 · 71–71](../../../../cmake/LibPgQuery.cmake#L71) | CMake command: string(APPEND _crown_pg_query_cc " ${CMAKE_C_COMPILER_ARG1}") |  · [reviewed contract](#b0038) |
| [B0039 · 72–72](../../../../cmake/LibPgQuery.cmake#L72) | CMake command: endif() |  · [reviewed contract](#b0039) |
| [B0040 · 73–73](../../../../cmake/LibPgQuery.cmake#L73) | CMake command: if(CMAKE_C_COMPILER_TARGET) |  · [reviewed contract](#b0040) |
| [B0041 · 74–74](../../../../cmake/LibPgQuery.cmake#L74) | CMake command: string(APPEND _crown_pg_query_cc " --target=${CMAKE_C_COMPILER_TARGET}") |  · [reviewed contract](#b0041) |
| [B0042 · 75–75](../../../../cmake/LibPgQuery.cmake#L75) | CMake command: endif() |  · [reviewed contract](#b0042) |
| [B0043 · 76–76](../../../../cmake/LibPgQuery.cmake#L76) | CMake command: if(CROWN_SANITIZERS) |  · [reviewed contract](#b0043) |
| [B0044 · 77–77](../../../../cmake/LibPgQuery.cmake#L77) | CMake command: string(APPEND _crown_pg_query_cflags " -fsanitize=address,undefined -fno-omit-frame-pointer") |  · [reviewed contract](#b0044) |
| [B0045 · 78–78](../../../../cmake/LibPgQuery.cmake#L78) | CMake command: endif() |  · [reviewed contract](#b0045) |
| [B0046 · 79–81](../../../../cmake/LibPgQuery.cmake#L79) | CMake command: set(_crown_pg_query_make_args |  · [reviewed contract](#b0046) |
| [B0047 · 82–82](../../../../cmake/LibPgQuery.cmake#L82) | CMake command: if(NOT _crown_pg_query_cflags STREQUAL "") |  · [reviewed contract](#b0047) |
| [B0048 · 83–83](../../../../cmake/LibPgQuery.cmake#L83) | CMake command: list(APPEND _crown_pg_query_make_args "CFLAGS=${_crown_pg_query_cflags}") |  · [reviewed contract](#b0048) |
| [B0049 · 84–84](../../../../cmake/LibPgQuery.cmake#L84) | CMake command: endif() |  · [reviewed contract](#b0049) |
| [B0050 · 85–85](../../../../cmake/LibPgQuery.cmake#L85) | Explanatory comments or spacing. |  |
| [B0051 · 86–101](../../../../cmake/LibPgQuery.cmake#L86) | CMake command: add_custom_command( | source comment (unverified): # The tarball preserves upstream source timestamps, so refresh the public · [reviewed contract](#b0051) |
| [B0052 · 102–102](../../../../cmake/LibPgQuery.cmake#L102) | Explanatory comments or spacing. |  |
| [B0053 · 103–104](../../../../cmake/LibPgQuery.cmake#L103) | CMake command: add_custom_target(_crown_pg_query_build |  · [reviewed contract](#b0053) |
| [B0054 · 105–105](../../../../cmake/LibPgQuery.cmake#L105) | Explanatory comments or spacing. |  |
| [B0055 · 106–106](../../../../cmake/LibPgQuery.cmake#L106) | CMake command: add_library(crown_pg_query STATIC IMPORTED GLOBAL) |  · [reviewed contract](#b0055) |
| [B0056 · 107–108](../../../../cmake/LibPgQuery.cmake#L107) | CMake command: set_target_properties(crown_pg_query PROPERTIES |  · [reviewed contract](#b0056) |
| [B0057 · 109–109](../../../../cmake/LibPgQuery.cmake#L109) | CMake command: target_include_directories(crown_pg_query SYSTEM INTERFACE "${_crown_pg_query_source_dir}") |  · [reviewed contract](#b0057) |
| [B0058 · 110–110](../../../../cmake/LibPgQuery.cmake#L110) | CMake command: target_link_libraries(crown_pg_query INTERFACE Threads::Threads) |  · [reviewed contract](#b0058) |
| [B0059 · 111–111](../../../../cmake/LibPgQuery.cmake#L111) | CMake command: if(CROWN_SANITIZERS) |  · [reviewed contract](#b0059) |
| [B0060 · 112–112](../../../../cmake/LibPgQuery.cmake#L112) | CMake command: target_link_options(crown_pg_query INTERFACE -fsanitize=address,undefined) |  · [reviewed contract](#b0060) |
| [B0061 · 113–113](../../../../cmake/LibPgQuery.cmake#L113) | CMake command: endif() |  · [reviewed contract](#b0061) |
| [B0062 · 114–114](../../../../cmake/LibPgQuery.cmake#L114) | CMake command: add_dependencies(crown_pg_query _crown_pg_query_build) |  · [reviewed contract](#b0062) |

## B0001

[Lines 1–3](../../../../cmake/LibPgQuery.cmake#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L1-L3:sha256:9dc6f5a7bbeaceadcb2f97b893cf0a1e458727ea513fe06dad76fb678bc1cbd6
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Explain the neighboring build/test boundary: Build the pinned libpg_query source archive locally. Keep this as an imported target so upstream's own Makefile remains responsible for compiling its generated PostgreSQL source set. |
| inputs / outputs | CMake comment text only; neighboring commands define actual targets/properties. |
| invariants | The note is not a link-graph proof, command execution result, timing bound or test pass. Historical measurements/counts apply only to their named cohort. |
| ownership | No build artifact, process, query state or resource owner is created by comment text. |
| failure | The comment does not implement error handling; actual configure/build/test failures belong to neighboring commands. |
| cost | No runtime/build command from this note; neighboring target configuration, compilation and selected test execution keep their actual costs. |
| Design | [cmake/LibPgQuery.cmake](../../../../cmake/LibPgQuery.cmake), [docs/native_build.md](../../../native_build.md), [docs/code_review.md](../../../code_review.md) |

## B0002

[Lines 4–5](../../../../cmake/LibPgQuery.cmake#L4); `build-command`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
set(_crown_pg_query_archive

```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Select the vendored libpg_query archive relative to this module. |
| inputs / outputs | The module path resolves to the checked-in 18.1.0 tarball used by hashing and the build rule. |
| invariants | The archive version/hash and generated outputs stay tied to this configured build; this has no per-query CMake role. |
| ownership | Configure-time CMake variables only; generated files remain under CMAKE_CURRENT_BINARY_DIR. |
| failure | Invalid input, generated path or compiler option fails at configure/generation or the later dependency build. |
| cost | Small configure-time variable/control work; no runtime cost. |
| Design | [cmake/LibPgQuery.cmake](../../../../cmake/LibPgQuery.cmake), [CMakeLists.txt](../../../../CMakeLists.txt), [dependencies.lock.json](../../../../dependencies.lock.json), [third_party/libpg_query/README.md](../../../../third_party/libpg_query/README.md), [docs/native_build.md](../../../native_build.md), [cmake/CrownConfig.cmake.in](../../../../cmake/CrownConfig.cmake.in) |

## B0003

[Lines 6–7](../../../../cmake/LibPgQuery.cmake#L6); `build-command`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
set(_crown_pg_query_sha256

```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Set the expected SHA-256 for the selected parser archive. |
| inputs / outputs | A fixed digest is the comparison value for the archive bytes and matches the lock entry. |
| invariants | The archive version/hash and generated outputs stay tied to this configured build; this has no per-query CMake role. |
| ownership | Configure-time CMake variables only; generated files remain under CMAKE_CURRENT_BINARY_DIR. |
| failure | Invalid input, generated path or compiler option fails at configure/generation or the later dependency build. |
| cost | Small configure-time variable/control work; no runtime cost. |
| Design | [cmake/LibPgQuery.cmake](../../../../cmake/LibPgQuery.cmake), [CMakeLists.txt](../../../../CMakeLists.txt), [dependencies.lock.json](../../../../dependencies.lock.json), [third_party/libpg_query/README.md](../../../../third_party/libpg_query/README.md), [docs/native_build.md](../../../native_build.md), [cmake/CrownConfig.cmake.in](../../../../cmake/CrownConfig.cmake.in) |

## B0004

[Lines 8–8](../../../../cmake/LibPgQuery.cmake#L8); `build-command`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
file(SHA256 "${_crown_pg_query_archive}" _crown_pg_query_actual_sha256)

```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Hash the source archive during configuration. |
| inputs / outputs | Archive bytes produce the actual digest variable before extraction is registered. |
| invariants | The archive version/hash and generated outputs stay tied to this configured build; this has no per-query CMake role. |
| ownership | Configure-time CMake variables only; generated files remain under CMAKE_CURRENT_BINARY_DIR. |
| failure | Invalid input, generated path or compiler option fails at configure/generation or the later dependency build. |
| cost | One sequential read and SHA-256 of the compressed archive during configure. |
| Design | [cmake/LibPgQuery.cmake](../../../../cmake/LibPgQuery.cmake), [CMakeLists.txt](../../../../CMakeLists.txt), [dependencies.lock.json](../../../../dependencies.lock.json), [third_party/libpg_query/README.md](../../../../third_party/libpg_query/README.md), [docs/native_build.md](../../../native_build.md), [cmake/CrownConfig.cmake.in](../../../../cmake/CrownConfig.cmake.in) |

## B0005

[Lines 9–9](../../../../cmake/LibPgQuery.cmake#L9); `build-command`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
if(NOT _crown_pg_query_actual_sha256 STREQUAL _crown_pg_query_sha256)

```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Branch on a mismatch between actual and pinned archive digests. |
| inputs / outputs | The two digest variables select either fatal configure failure or continued generation. |
| invariants | The archive version/hash and generated outputs stay tied to this configured build; this has no per-query CMake role. |
| ownership | CMake configure condition only; no target, file or runtime object is owned by the guard. |
| failure | Invalid input, generated path or compiler option fails at configure/generation or the later dependency build. |
| cost | Small configure-time variable/control work; no runtime cost. |
| Design | [cmake/LibPgQuery.cmake](../../../../cmake/LibPgQuery.cmake), [CMakeLists.txt](../../../../CMakeLists.txt), [dependencies.lock.json](../../../../dependencies.lock.json), [third_party/libpg_query/README.md](../../../../third_party/libpg_query/README.md), [docs/native_build.md](../../../native_build.md), [cmake/CrownConfig.cmake.in](../../../../cmake/CrownConfig.cmake.in) |

## B0006

[Lines 10–11](../../../../cmake/LibPgQuery.cmake#L10); `build-command`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
  message(FATAL_ERROR
    "Vendored libpg_query 18.1.0 archive checksum mismatch: ${_crown_pg_query_actual_sha256}")

```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Stop configuration and report the observed digest on a pin mismatch. |
| inputs / outputs | The diagnostic includes the computed digest; no target is emitted on this branch. |
| invariants | The archive version/hash and generated outputs stay tied to this configured build; this has no per-query CMake role. |
| ownership | Configure-time CMake variables only; generated files remain under CMAKE_CURRENT_BINARY_DIR. |
| failure | FATAL_ERROR stops configuration before dependency extraction/build. |
| cost | Small configure-time variable/control work; no runtime cost. |
| Design | [cmake/LibPgQuery.cmake](../../../../cmake/LibPgQuery.cmake), [CMakeLists.txt](../../../../CMakeLists.txt), [dependencies.lock.json](../../../../dependencies.lock.json), [third_party/libpg_query/README.md](../../../../third_party/libpg_query/README.md), [docs/native_build.md](../../../native_build.md), [cmake/CrownConfig.cmake.in](../../../../cmake/CrownConfig.cmake.in) |

## B0007

[Lines 12–12](../../../../cmake/LibPgQuery.cmake#L12); `build-command`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
endif()

find_program(CROWN_MAKE_EXECUTABLE NAMES gmake make REQUIRED)

```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Close the archive checksum conditional. |
| inputs / outputs | No output; closes the mismatch guard from B0005. |
| invariants | This is a CMake control closure only; it adds no runtime condition. |
| ownership | CMake control closure only; it owns no target, file or runtime object. |
| failure | Unbalanced CMake syntax fails configuration; the guarded command’s failure remains at its own phase. |
| cost | Small configure-time variable/control work; no runtime cost. |
| Design | [cmake/LibPgQuery.cmake](../../../../cmake/LibPgQuery.cmake), [CMakeLists.txt](../../../../CMakeLists.txt), [dependencies.lock.json](../../../../dependencies.lock.json), [third_party/libpg_query/README.md](../../../../third_party/libpg_query/README.md), [docs/native_build.md](../../../native_build.md), [cmake/CrownConfig.cmake.in](../../../../cmake/CrownConfig.cmake.in) |

## B0009

[Lines 14–14](../../../../cmake/LibPgQuery.cmake#L14); `build-command`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
find_program(CROWN_MAKE_EXECUTABLE NAMES gmake make REQUIRED)

```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Find gmake or make as a required host build tool. |
| inputs / outputs | Stores the executable path for the following version probe and later build command. |
| invariants | The archive version/hash and generated outputs stay tied to this configured build; this has no per-query CMake role. |
| ownership | Configure-time CMake variables only; generated files remain under CMAKE_CURRENT_BINARY_DIR. |
| failure | Missing required make/thread package support stops configuration. |
| cost | Small configure-time variable/control work; no runtime cost. |
| Design | [cmake/LibPgQuery.cmake](../../../../cmake/LibPgQuery.cmake), [CMakeLists.txt](../../../../CMakeLists.txt), [dependencies.lock.json](../../../../dependencies.lock.json), [third_party/libpg_query/README.md](../../../../third_party/libpg_query/README.md), [docs/native_build.md](../../../native_build.md), [cmake/CrownConfig.cmake.in](../../../../cmake/CrownConfig.cmake.in) |

## B0010

[Lines 15–19](../../../../cmake/LibPgQuery.cmake#L15); `build-command`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
execute_process(

```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Probe the selected make executable and capture status and version text. |
| inputs / outputs | The process fills result, stdout and stderr variables; it does not build the parser. |
| invariants | The archive version/hash and generated outputs stay tied to this configured build; this has no per-query CMake role. |
| ownership | Configure-time CMake variables only; generated files remain under CMAKE_CURRENT_BINARY_DIR. |
| failure | Invalid input, generated path or compiler option fails at configure/generation or the later dependency build. |
| cost | One short external GNU Make version process during configure. |
| Design | [cmake/LibPgQuery.cmake](../../../../cmake/LibPgQuery.cmake), [CMakeLists.txt](../../../../CMakeLists.txt), [dependencies.lock.json](../../../../dependencies.lock.json), [third_party/libpg_query/README.md](../../../../third_party/libpg_query/README.md), [docs/native_build.md](../../../native_build.md), [cmake/CrownConfig.cmake.in](../../../../cmake/CrownConfig.cmake.in) |

## B0011

[Lines 20–20](../../../../cmake/LibPgQuery.cmake#L20); `build-command`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
if(NOT _crown_make_result EQUAL 0 OR NOT _crown_make_version MATCHES "GNU Make")

```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Require a successful probe whose output identifies GNU Make. |
| inputs / outputs | The status and captured version determine whether dependency setup can continue. |
| invariants | The archive version/hash and generated outputs stay tied to this configured build; this has no per-query CMake role. |
| ownership | CMake configure condition only; no target, file or runtime object is owned by the guard. |
| failure | Invalid input, generated path or compiler option fails at configure/generation or the later dependency build. |
| cost | Small configure-time variable/control work; no runtime cost. |
| Design | [cmake/LibPgQuery.cmake](../../../../cmake/LibPgQuery.cmake), [CMakeLists.txt](../../../../CMakeLists.txt), [dependencies.lock.json](../../../../dependencies.lock.json), [third_party/libpg_query/README.md](../../../../third_party/libpg_query/README.md), [docs/native_build.md](../../../native_build.md), [cmake/CrownConfig.cmake.in](../../../../cmake/CrownConfig.cmake.in) |

## B0012

[Lines 21–22](../../../../cmake/LibPgQuery.cmake#L21); `build-command`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
  message(FATAL_ERROR
    "libpg_query requires GNU Make; found '${CROWN_MAKE_EXECUTABLE}'. ${_crown_make_error}")

```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Stop and explain when GNU Make is missing or incompatible. |
| inputs / outputs | The diagnostic reports the selected executable and captured stderr. |
| invariants | The archive version/hash and generated outputs stay tied to this configured build; this has no per-query CMake role. |
| ownership | Configure-time CMake variables only; generated files remain under CMAKE_CURRENT_BINARY_DIR. |
| failure | FATAL_ERROR stops configuration before dependency extraction/build. |
| cost | Small configure-time variable/control work; no runtime cost. |
| Design | [cmake/LibPgQuery.cmake](../../../../cmake/LibPgQuery.cmake), [CMakeLists.txt](../../../../CMakeLists.txt), [dependencies.lock.json](../../../../dependencies.lock.json), [third_party/libpg_query/README.md](../../../../third_party/libpg_query/README.md), [docs/native_build.md](../../../native_build.md), [cmake/CrownConfig.cmake.in](../../../../cmake/CrownConfig.cmake.in) |

## B0013

[Lines 23–23](../../../../cmake/LibPgQuery.cmake#L23); `build-command`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
endif()

find_package(Threads REQUIRED)

```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Close the GNU Make validation conditional. |
| inputs / outputs | No output; closes the tool check from B0011. |
| invariants | This is a CMake control closure only; it adds no runtime condition. |
| ownership | CMake control closure only; it owns no target, file or runtime object. |
| failure | Unbalanced CMake syntax fails configuration; the guarded command’s failure remains at its own phase. |
| cost | Small configure-time variable/control work; no runtime cost. |
| Design | [cmake/LibPgQuery.cmake](../../../../cmake/LibPgQuery.cmake), [CMakeLists.txt](../../../../CMakeLists.txt), [dependencies.lock.json](../../../../dependencies.lock.json), [third_party/libpg_query/README.md](../../../../third_party/libpg_query/README.md), [docs/native_build.md](../../../native_build.md), [cmake/CrownConfig.cmake.in](../../../../cmake/CrownConfig.cmake.in) |

## B0015

[Lines 25–25](../../../../cmake/LibPgQuery.cmake#L25); `build-command`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
find_package(Threads REQUIRED)

```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Resolve CMake’s Threads target for the parser link interface. |
| inputs / outputs | Provides Threads::Threads for the imported parser target. |
| invariants | The archive version/hash and generated outputs stay tied to this configured build; this has no per-query CMake role. |
| ownership | Configure-time CMake variables only; generated files remain under CMAKE_CURRENT_BINARY_DIR. |
| failure | Missing required make/thread package support stops configuration. |
| cost | Small configure-time variable/control work; no runtime cost. |
| Design | [cmake/LibPgQuery.cmake](../../../../cmake/LibPgQuery.cmake), [CMakeLists.txt](../../../../CMakeLists.txt), [dependencies.lock.json](../../../../dependencies.lock.json), [third_party/libpg_query/README.md](../../../../third_party/libpg_query/README.md), [docs/native_build.md](../../../native_build.md), [cmake/CrownConfig.cmake.in](../../../../cmake/CrownConfig.cmake.in) |

## B0017

[Lines 27–27](../../../../cmake/LibPgQuery.cmake#L27); `build-command`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
set(_crown_pg_query_extract_root "${CMAKE_CURRENT_BINARY_DIR}/_deps/libpg_query")

```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Choose a binary-tree root for parser extraction. |
| inputs / outputs | CMAKE_CURRENT_BINARY_DIR supplies the local _deps/libpg_query path. |
| invariants | The archive version/hash and generated outputs stay tied to this configured build; this has no per-query CMake role. |
| ownership | Configure-time CMake variables only; generated files remain under CMAKE_CURRENT_BINARY_DIR. |
| failure | Invalid input, generated path or compiler option fails at configure/generation or the later dependency build. |
| cost | Small configure-time variable/control work; no runtime cost. |
| Design | [cmake/LibPgQuery.cmake](../../../../cmake/LibPgQuery.cmake), [CMakeLists.txt](../../../../CMakeLists.txt), [dependencies.lock.json](../../../../dependencies.lock.json), [third_party/libpg_query/README.md](../../../../third_party/libpg_query/README.md), [docs/native_build.md](../../../native_build.md), [cmake/CrownConfig.cmake.in](../../../../cmake/CrownConfig.cmake.in) |

## B0018

[Lines 28–28](../../../../cmake/LibPgQuery.cmake#L28); `build-command`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
set(_crown_pg_query_source_dir "${_crown_pg_query_extract_root}/libpg_query-18.1.0")

```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Select the versioned extracted parser source directory. |
| inputs / outputs | The path under the dependency root names libpg_query-18.1.0. |
| invariants | The archive version/hash and generated outputs stay tied to this configured build; this has no per-query CMake role. |
| ownership | Configure-time CMake variables only; generated files remain under CMAKE_CURRENT_BINARY_DIR. |
| failure | Invalid input, generated path or compiler option fails at configure/generation or the later dependency build. |
| cost | Small configure-time variable/control work; no runtime cost. |
| Design | [cmake/LibPgQuery.cmake](../../../../cmake/LibPgQuery.cmake), [CMakeLists.txt](../../../../CMakeLists.txt), [dependencies.lock.json](../../../../dependencies.lock.json), [third_party/libpg_query/README.md](../../../../third_party/libpg_query/README.md), [docs/native_build.md](../../../native_build.md), [cmake/CrownConfig.cmake.in](../../../../cmake/CrownConfig.cmake.in) |

## B0019

[Lines 29–29](../../../../cmake/LibPgQuery.cmake#L29); `build-command`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
set(_crown_pg_query_library "${_crown_pg_query_source_dir}/libpg_query.a")

```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Name the static archive output expected from upstream Make. |
| inputs / outputs | The output path is libpg_query.a inside the extracted source directory. |
| invariants | The archive version/hash and generated outputs stay tied to this configured build; this has no per-query CMake role. |
| ownership | Configure-time CMake variables only; generated files remain under CMAKE_CURRENT_BINARY_DIR. |
| failure | Invalid input, generated path or compiler option fails at configure/generation or the later dependency build. |
| cost | Small configure-time variable/control work; no runtime cost. |
| Design | [cmake/LibPgQuery.cmake](../../../../cmake/LibPgQuery.cmake), [CMakeLists.txt](../../../../CMakeLists.txt), [dependencies.lock.json](../../../../dependencies.lock.json), [third_party/libpg_query/README.md](../../../../third_party/libpg_query/README.md), [docs/native_build.md](../../../native_build.md), [cmake/CrownConfig.cmake.in](../../../../cmake/CrownConfig.cmake.in) |

## B0020

[Lines 30–30](../../../../cmake/LibPgQuery.cmake#L30); `build-command`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
set(_crown_pg_query_header "${_crown_pg_query_source_dir}/pg_query.h")

```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Name pg_query.h as a declared dependency build output. |
| inputs / outputs | The header path is exposed through the parser target include directory. |
| invariants | The archive version/hash and generated outputs stay tied to this configured build; this has no per-query CMake role. |
| ownership | Configure-time CMake variables only; generated files remain under CMAKE_CURRENT_BINARY_DIR. |
| failure | Invalid input, generated path or compiler option fails at configure/generation or the later dependency build. |
| cost | Small configure-time variable/control work; no runtime cost. |
| Design | [cmake/LibPgQuery.cmake](../../../../cmake/LibPgQuery.cmake), [CMakeLists.txt](../../../../CMakeLists.txt), [dependencies.lock.json](../../../../dependencies.lock.json), [third_party/libpg_query/README.md](../../../../third_party/libpg_query/README.md), [docs/native_build.md](../../../native_build.md), [cmake/CrownConfig.cmake.in](../../../../cmake/CrownConfig.cmake.in) |

## B0021

[Lines 31–33](../../../../cmake/LibPgQuery.cmake#L31); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L31-L33:sha256:6457714173b712835614451f9601d59a998b3624d7e17e38f58ff21733f442b5
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Explain the neighboring build/test boundary: CMake validates INTERFACE include directories during generation. Create the empty build-tree directory now; the build command replaces it with the verified archive contents before a consumer compiles. |
| inputs / outputs | CMake comment text only; neighboring commands define actual targets/properties. |
| invariants | The note is not a link-graph proof, command execution result, timing bound or test pass. Historical measurements/counts apply only to their named cohort. |
| ownership | No build artifact, process, query state or resource owner is created by comment text. |
| failure | The comment does not implement error handling; actual configure/build/test failures belong to neighboring commands. |
| cost | No runtime/build command from this note; neighboring target configuration, compilation and selected test execution keep their actual costs. |
| Design | [cmake/LibPgQuery.cmake](../../../../cmake/LibPgQuery.cmake), [docs/native_build.md](../../../native_build.md), [docs/code_review.md](../../../code_review.md) |

## B0022

[Lines 34–34](../../../../cmake/LibPgQuery.cmake#L34); `build-command`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
file(MAKE_DIRECTORY "${_crown_pg_query_source_dir}")

```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Create the empty include directory before CMake validates that path at generation. |
| inputs / outputs | The build later replaces this placeholder with verified archive contents. |
| invariants | The archive version/hash and generated outputs stay tied to this configured build; this has no per-query CMake role. |
| ownership | Configure-time CMake variables only; generated files remain under CMAKE_CURRENT_BINARY_DIR. |
| failure | Invalid input, generated path or compiler option fails at configure/generation or the later dependency build. |
| cost | Small configure-time variable/control work; no runtime cost. |
| Design | [cmake/LibPgQuery.cmake](../../../../cmake/LibPgQuery.cmake), [CMakeLists.txt](../../../../CMakeLists.txt), [dependencies.lock.json](../../../../dependencies.lock.json), [third_party/libpg_query/README.md](../../../../third_party/libpg_query/README.md), [docs/native_build.md](../../../native_build.md), [cmake/CrownConfig.cmake.in](../../../../cmake/CrownConfig.cmake.in) |

## B0023

[Lines 35–38](../../../../cmake/LibPgQuery.cmake#L35); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L35-L38:sha256:721ac80e31fac6281eff89b5c447295d87d8d751b9d26e76682522e77ef330ec
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Explain the neighboring build/test boundary: Make reconfiguration invalidate the static library when compiler or flags change, without causing a rebuild when the generated configuration is unchanged. |
| inputs / outputs | CMake comment text only; neighboring commands define actual targets/properties. |
| invariants | The note is not a link-graph proof, command execution result, timing bound or test pass. Historical measurements/counts apply only to their named cohort. |
| ownership | No build artifact, process, query state or resource owner is created by comment text. |
| failure | The comment does not implement error handling; actual configure/build/test failures belong to neighboring commands. |
| cost | No runtime/build command from this note; neighboring target configuration, compilation and selected test execution keep their actual costs. |
| Design | [cmake/LibPgQuery.cmake](../../../../cmake/LibPgQuery.cmake), [docs/native_build.md](../../../native_build.md), [docs/code_review.md](../../../code_review.md) |

## B0024

[Lines 39–39](../../../../cmake/LibPgQuery.cmake#L39); `build-command`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
set(_crown_pg_query_build_config "${CMAKE_CURRENT_BINARY_DIR}/_deps/libpg_query-build-config.txt")

```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Name the generated parser build-configuration stamp. |
| inputs / outputs | The binary-tree stamp is a custom-command dependency for compiler-input changes. |
| invariants | The archive version/hash and generated outputs stay tied to this configured build; this has no per-query CMake role. |
| ownership | Configure-time CMake variables only; generated files remain under CMAKE_CURRENT_BINARY_DIR. |
| failure | Invalid input, generated path or compiler option fails at configure/generation or the later dependency build. |
| cost | Small configure-time variable/control work; no runtime cost. |
| Design | [cmake/LibPgQuery.cmake](../../../../cmake/LibPgQuery.cmake), [CMakeLists.txt](../../../../CMakeLists.txt), [dependencies.lock.json](../../../../dependencies.lock.json), [third_party/libpg_query/README.md](../../../../third_party/libpg_query/README.md), [docs/native_build.md](../../../native_build.md), [cmake/CrownConfig.cmake.in](../../../../cmake/CrownConfig.cmake.in) |

## B0025

[Lines 40–49](../../../../cmake/LibPgQuery.cmake#L40); `build-command`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
string(CONCAT _crown_pg_query_build_config_content

```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Serialize compiler and parser build inputs into stamp content. |
| inputs / outputs | Records compiler path/arg/id/version/target, sysroot, base C flags, sanitizer option and make path. |
| invariants | The archive version/hash and generated outputs stay tied to this configured build; this has no per-query CMake role. |
| ownership | Configure-time CMake variables only; generated files remain under CMAKE_CURRENT_BINARY_DIR. |
| failure | Invalid input, generated path or compiler option fails at configure/generation or the later dependency build. |
| cost | Small configure-time variable/control work; no runtime cost. |
| Design | [cmake/LibPgQuery.cmake](../../../../cmake/LibPgQuery.cmake), [CMakeLists.txt](../../../../CMakeLists.txt), [dependencies.lock.json](../../../../dependencies.lock.json), [third_party/libpg_query/README.md](../../../../third_party/libpg_query/README.md), [docs/native_build.md](../../../native_build.md), [cmake/CrownConfig.cmake.in](../../../../cmake/CrownConfig.cmake.in) |

## B0026

[Lines 50–50](../../../../cmake/LibPgQuery.cmake#L50); `build-command`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
file(GENERATE OUTPUT "${_crown_pg_query_build_config}" CONTENT "${_crown_pg_query_build_config_content}")

```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Generate the parser build-configuration stamp. |
| inputs / outputs | Writes assembled settings under the binary tree so changed content invalidates the build rule. |
| invariants | The archive version/hash and generated outputs stay tied to this configured build; this has no per-query CMake role. |
| ownership | Configure-time CMake variables only; generated files remain under CMAKE_CURRENT_BINARY_DIR. |
| failure | Invalid input, generated path or compiler option fails at configure/generation or the later dependency build. |
| cost | Small configure-time variable/control work; no runtime cost. |
| Design | [cmake/LibPgQuery.cmake](../../../../cmake/LibPgQuery.cmake), [CMakeLists.txt](../../../../CMakeLists.txt), [dependencies.lock.json](../../../../dependencies.lock.json), [third_party/libpg_query/README.md](../../../../third_party/libpg_query/README.md), [docs/native_build.md](../../../native_build.md), [cmake/CrownConfig.cmake.in](../../../../cmake/CrownConfig.cmake.in) |

## B0027

[Lines 51–54](../../../../cmake/LibPgQuery.cmake#L51); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L51-L54:sha256:aea8c5016f4e1c26095042ac65bf887a1521bee379fe93c903b02436a409cab9
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Explain the neighboring build/test boundary: Recheck the vendored archive at build time as well as configure time, so a changed file cannot be silently extracted after this build directory was configured. |
| inputs / outputs | CMake comment text only; neighboring commands define actual targets/properties. |
| invariants | The note is not a link-graph proof, command execution result, timing bound or test pass. Historical measurements/counts apply only to their named cohort. |
| ownership | No build artifact, process, query state or resource owner is created by comment text. |
| failure | The comment does not implement error handling; actual configure/build/test failures belong to neighboring commands. |
| cost | No runtime/build command from this note; neighboring target configuration, compilation and selected test execution keep their actual costs. |
| Design | [cmake/LibPgQuery.cmake](../../../../cmake/LibPgQuery.cmake), [docs/native_build.md](../../../native_build.md), [docs/code_review.md](../../../code_review.md) |

## B0028

[Lines 55–55](../../../../cmake/LibPgQuery.cmake#L55); `build-command`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
set(_crown_pg_query_verify_script "${CMAKE_CURRENT_BINARY_DIR}/_deps/verify-libpg-query.cmake")

```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Name the generated build-time archive verifier. |
| inputs / outputs | The binary-tree script runs immediately before extraction. |
| invariants | The archive version/hash and generated outputs stay tied to this configured build; this has no per-query CMake role. |
| ownership | Configure-time CMake variables only; generated files remain under CMAKE_CURRENT_BINARY_DIR. |
| failure | Invalid input, generated path or compiler option fails at configure/generation or the later dependency build. |
| cost | Small configure-time variable/control work; no runtime cost. |
| Design | [cmake/LibPgQuery.cmake](../../../../cmake/LibPgQuery.cmake), [CMakeLists.txt](../../../../CMakeLists.txt), [dependencies.lock.json](../../../../dependencies.lock.json), [third_party/libpg_query/README.md](../../../../third_party/libpg_query/README.md), [docs/native_build.md](../../../native_build.md), [cmake/CrownConfig.cmake.in](../../../../cmake/CrownConfig.cmake.in) |

## B0029

[Lines 56–60](../../../../cmake/LibPgQuery.cmake#L56); `build-command`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
string(CONCAT _crown_pg_query_verify_contents

```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Construct a build-time script that rehashes and rejects archive drift. |
| inputs / outputs | The generated script compares archive bytes with the same pinned digest. |
| invariants | The archive version/hash and generated outputs stay tied to this configured build; this has no per-query CMake role. |
| ownership | Configure-time CMake variables only; generated files remain under CMAKE_CURRENT_BINARY_DIR. |
| failure | Invalid input, generated path or compiler option fails at configure/generation or the later dependency build. |
| cost | Small script generation; archive hashing occurs only when the build rule runs. |
| Design | [cmake/LibPgQuery.cmake](../../../../cmake/LibPgQuery.cmake), [CMakeLists.txt](../../../../CMakeLists.txt), [dependencies.lock.json](../../../../dependencies.lock.json), [third_party/libpg_query/README.md](../../../../third_party/libpg_query/README.md), [docs/native_build.md](../../../native_build.md), [cmake/CrownConfig.cmake.in](../../../../cmake/CrownConfig.cmake.in) |

## B0030

[Lines 61–61](../../../../cmake/LibPgQuery.cmake#L61); `build-command`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
file(GENERATE OUTPUT "${_crown_pg_query_verify_script}" CONTENT "${_crown_pg_query_verify_contents}")

```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Generate the build-time archive verifier script. |
| inputs / outputs | Writes the checker text to the path consumed by the custom command. |
| invariants | The archive version/hash and generated outputs stay tied to this configured build; this has no per-query CMake role. |
| ownership | Configure-time CMake variables only; generated files remain under CMAKE_CURRENT_BINARY_DIR. |
| failure | Invalid input, generated path or compiler option fails at configure/generation or the later dependency build. |
| cost | Small configure-time variable/control work; no runtime cost. |
| Design | [cmake/LibPgQuery.cmake](../../../../cmake/LibPgQuery.cmake), [CMakeLists.txt](../../../../CMakeLists.txt), [dependencies.lock.json](../../../../dependencies.lock.json), [third_party/libpg_query/README.md](../../../../third_party/libpg_query/README.md), [docs/native_build.md](../../../native_build.md), [cmake/CrownConfig.cmake.in](../../../../cmake/CrownConfig.cmake.in) |

## B0031

[Lines 62–64](../../../../cmake/LibPgQuery.cmake#L62); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L62-L64:sha256:5ef673c4994f98dfb9daf1e8bc8ab8020d8c795cef3274981f36a656bba9173a
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Explain the neighboring build/test boundary: Pass through CMake's C flags and instrument the dependency itself when sanitizers are enabled. The upstream Makefile appends its own required flags. |
| inputs / outputs | CMake comment text only; neighboring commands define actual targets/properties. |
| invariants | The note is not a link-graph proof, command execution result, timing bound or test pass. Historical measurements/counts apply only to their named cohort. |
| ownership | No build artifact, process, query state or resource owner is created by comment text. |
| failure | The comment does not implement error handling; actual configure/build/test failures belong to neighboring commands. |
| cost | No runtime/build command from this note; neighboring target configuration, compilation and selected test execution keep their actual costs. |
| Design | [cmake/LibPgQuery.cmake](../../../../cmake/LibPgQuery.cmake), [docs/native_build.md](../../../native_build.md), [docs/code_review.md](../../../code_review.md) |

## B0032

[Lines 65–65](../../../../cmake/LibPgQuery.cmake#L65); `build-command`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
set(_crown_pg_query_cflags "${CMAKE_C_FLAGS}")

```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Initialize parser CFLAGS from CMAKE_C_FLAGS. |
| inputs / outputs | The base C flags start the external Make flag string; configuration-specific C flags are not copied. |
| invariants | The archive version/hash and generated outputs stay tied to this configured build; this has no per-query CMake role. |
| ownership | Configure-time CMake variables only; generated files remain under CMAKE_CURRENT_BINARY_DIR. |
| failure | Invalid input, generated path or compiler option fails at configure/generation or the later dependency build. |
| cost | Small configure-time variable/control work; no runtime cost. |
| Design | [cmake/LibPgQuery.cmake](../../../../cmake/LibPgQuery.cmake), [CMakeLists.txt](../../../../CMakeLists.txt), [dependencies.lock.json](../../../../dependencies.lock.json), [third_party/libpg_query/README.md](../../../../third_party/libpg_query/README.md), [docs/native_build.md](../../../native_build.md), [cmake/CrownConfig.cmake.in](../../../../cmake/CrownConfig.cmake.in) |

## B0033

[Lines 66–66](../../../../cmake/LibPgQuery.cmake#L66); `build-command`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
if(CMAKE_SYSROOT)

```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Guard optional sysroot forwarding. |
| inputs / outputs | A nonempty CMAKE_SYSROOT enables the following append. |
| invariants | The archive version/hash and generated outputs stay tied to this configured build; this has no per-query CMake role. |
| ownership | CMake configure condition only; no target, file or runtime object is owned by the guard. |
| failure | Invalid input, generated path or compiler option fails at configure/generation or the later dependency build. |
| cost | Small configure-time variable/control work; no runtime cost. |
| Design | [cmake/LibPgQuery.cmake](../../../../cmake/LibPgQuery.cmake), [CMakeLists.txt](../../../../CMakeLists.txt), [dependencies.lock.json](../../../../dependencies.lock.json), [third_party/libpg_query/README.md](../../../../third_party/libpg_query/README.md), [docs/native_build.md](../../../native_build.md), [cmake/CrownConfig.cmake.in](../../../../cmake/CrownConfig.cmake.in) |

## B0034

[Lines 67–67](../../../../cmake/LibPgQuery.cmake#L67); `build-command`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
  string(APPEND _crown_pg_query_cflags " --sysroot=${CMAKE_SYSROOT}")

```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Append CMAKE_SYSROOT to parser CFLAGS. |
| inputs / outputs | Adds a --sysroot argument without changing global CMake flags. |
| invariants | The archive version/hash and generated outputs stay tied to this configured build; this has no per-query CMake role. |
| ownership | Configure-time CMake variables only; generated files remain under CMAKE_CURRENT_BINARY_DIR. |
| failure | Invalid input, generated path or compiler option fails at configure/generation or the later dependency build. |
| cost | Small configure-time variable/control work; no runtime cost. |
| Design | [cmake/LibPgQuery.cmake](../../../../cmake/LibPgQuery.cmake), [CMakeLists.txt](../../../../CMakeLists.txt), [dependencies.lock.json](../../../../dependencies.lock.json), [third_party/libpg_query/README.md](../../../../third_party/libpg_query/README.md), [docs/native_build.md](../../../native_build.md), [cmake/CrownConfig.cmake.in](../../../../cmake/CrownConfig.cmake.in) |

## B0035

[Lines 68–68](../../../../cmake/LibPgQuery.cmake#L68); `build-command`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
endif()
set(_crown_pg_query_cc "${CMAKE_C_COMPILER}")

```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Close the optional sysroot branch. |
| inputs / outputs | No output; terminates the CMAKE_SYSROOT condition. |
| invariants | This is a CMake control closure only; it adds no runtime condition. |
| ownership | CMake control closure only; it owns no target, file or runtime object. |
| failure | Unbalanced CMake syntax fails configuration; the guarded command’s failure remains at its own phase. |
| cost | Small configure-time variable/control work; no runtime cost. |
| Design | [cmake/LibPgQuery.cmake](../../../../cmake/LibPgQuery.cmake), [CMakeLists.txt](../../../../CMakeLists.txt), [dependencies.lock.json](../../../../dependencies.lock.json), [third_party/libpg_query/README.md](../../../../third_party/libpg_query/README.md), [docs/native_build.md](../../../native_build.md), [cmake/CrownConfig.cmake.in](../../../../cmake/CrownConfig.cmake.in) |

## B0036

[Lines 69–69](../../../../cmake/LibPgQuery.cmake#L69); `build-command`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
set(_crown_pg_query_cc "${CMAKE_C_COMPILER}")

```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Initialize external Make CC from CMAKE_C_COMPILER. |
| inputs / outputs | The selected C executable begins the compiler command string. |
| invariants | The archive version/hash and generated outputs stay tied to this configured build; this has no per-query CMake role. |
| ownership | Configure-time CMake variables only; generated files remain under CMAKE_CURRENT_BINARY_DIR. |
| failure | Invalid input, generated path or compiler option fails at configure/generation or the later dependency build. |
| cost | Small configure-time variable/control work; no runtime cost. |
| Design | [cmake/LibPgQuery.cmake](../../../../cmake/LibPgQuery.cmake), [CMakeLists.txt](../../../../CMakeLists.txt), [dependencies.lock.json](../../../../dependencies.lock.json), [third_party/libpg_query/README.md](../../../../third_party/libpg_query/README.md), [docs/native_build.md](../../../native_build.md), [cmake/CrownConfig.cmake.in](../../../../cmake/CrownConfig.cmake.in) |

## B0037

[Lines 70–70](../../../../cmake/LibPgQuery.cmake#L70); `build-command`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
if(CMAKE_C_COMPILER_ARG1)

```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Guard optional CMAKE_C_COMPILER_ARG1 forwarding. |
| inputs / outputs | A nonempty initial compiler argument enables the following append. |
| invariants | The archive version/hash and generated outputs stay tied to this configured build; this has no per-query CMake role. |
| ownership | CMake configure condition only; no target, file or runtime object is owned by the guard. |
| failure | Invalid input, generated path or compiler option fails at configure/generation or the later dependency build. |
| cost | Small configure-time variable/control work; no runtime cost. |
| Design | [cmake/LibPgQuery.cmake](../../../../cmake/LibPgQuery.cmake), [CMakeLists.txt](../../../../CMakeLists.txt), [dependencies.lock.json](../../../../dependencies.lock.json), [third_party/libpg_query/README.md](../../../../third_party/libpg_query/README.md), [docs/native_build.md](../../../native_build.md), [cmake/CrownConfig.cmake.in](../../../../cmake/CrownConfig.cmake.in) |

## B0038

[Lines 71–71](../../../../cmake/LibPgQuery.cmake#L71); `build-command`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
  string(APPEND _crown_pg_query_cc " ${CMAKE_C_COMPILER_ARG1}")

```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Append CMAKE_C_COMPILER_ARG1 to the external CC command. |
| inputs / outputs | The configured initial argument follows the selected compiler executable. |
| invariants | The archive version/hash and generated outputs stay tied to this configured build; this has no per-query CMake role. |
| ownership | Configure-time CMake variables only; generated files remain under CMAKE_CURRENT_BINARY_DIR. |
| failure | Invalid input, generated path or compiler option fails at configure/generation or the later dependency build. |
| cost | Small configure-time variable/control work; no runtime cost. |
| Design | [cmake/LibPgQuery.cmake](../../../../cmake/LibPgQuery.cmake), [CMakeLists.txt](../../../../CMakeLists.txt), [dependencies.lock.json](../../../../dependencies.lock.json), [third_party/libpg_query/README.md](../../../../third_party/libpg_query/README.md), [docs/native_build.md](../../../native_build.md), [cmake/CrownConfig.cmake.in](../../../../cmake/CrownConfig.cmake.in) |

## B0039

[Lines 72–72](../../../../cmake/LibPgQuery.cmake#L72); `build-command`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
endif()
if(CMAKE_C_COMPILER_TARGET)

```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Close the optional compiler-argument branch. |
| inputs / outputs | No output; terminates the ARG1 condition. |
| invariants | This is a CMake control closure only; it adds no runtime condition. |
| ownership | CMake control closure only; it owns no target, file or runtime object. |
| failure | Unbalanced CMake syntax fails configuration; the guarded command’s failure remains at its own phase. |
| cost | Small configure-time variable/control work; no runtime cost. |
| Design | [cmake/LibPgQuery.cmake](../../../../cmake/LibPgQuery.cmake), [CMakeLists.txt](../../../../CMakeLists.txt), [dependencies.lock.json](../../../../dependencies.lock.json), [third_party/libpg_query/README.md](../../../../third_party/libpg_query/README.md), [docs/native_build.md](../../../native_build.md), [cmake/CrownConfig.cmake.in](../../../../cmake/CrownConfig.cmake.in) |

## B0040

[Lines 73–73](../../../../cmake/LibPgQuery.cmake#L73); `build-command`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
if(CMAKE_C_COMPILER_TARGET)

```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Guard optional C compiler target forwarding. |
| inputs / outputs | A nonempty CMAKE_C_COMPILER_TARGET enables a target option. |
| invariants | The archive version/hash and generated outputs stay tied to this configured build; this has no per-query CMake role. |
| ownership | CMake configure condition only; no target, file or runtime object is owned by the guard. |
| failure | Invalid input, generated path or compiler option fails at configure/generation or the later dependency build. |
| cost | Small configure-time variable/control work; no runtime cost. |
| Design | [cmake/LibPgQuery.cmake](../../../../cmake/LibPgQuery.cmake), [CMakeLists.txt](../../../../CMakeLists.txt), [dependencies.lock.json](../../../../dependencies.lock.json), [third_party/libpg_query/README.md](../../../../third_party/libpg_query/README.md), [docs/native_build.md](../../../native_build.md), [cmake/CrownConfig.cmake.in](../../../../cmake/CrownConfig.cmake.in) |

## B0041

[Lines 74–74](../../../../cmake/LibPgQuery.cmake#L74); `build-command`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
  string(APPEND _crown_pg_query_cc " --target=${CMAKE_C_COMPILER_TARGET}")

```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Append the compiler target triple to external CC. |
| inputs / outputs | Adds --target using the CMake-selected target triple. |
| invariants | The archive version/hash and generated outputs stay tied to this configured build; this has no per-query CMake role. |
| ownership | Configure-time CMake variables only; generated files remain under CMAKE_CURRENT_BINARY_DIR. |
| failure | Invalid input, generated path or compiler option fails at configure/generation or the later dependency build. |
| cost | Small configure-time variable/control work; no runtime cost. |
| Design | [cmake/LibPgQuery.cmake](../../../../cmake/LibPgQuery.cmake), [CMakeLists.txt](../../../../CMakeLists.txt), [dependencies.lock.json](../../../../dependencies.lock.json), [third_party/libpg_query/README.md](../../../../third_party/libpg_query/README.md), [docs/native_build.md](../../../native_build.md), [cmake/CrownConfig.cmake.in](../../../../cmake/CrownConfig.cmake.in) |

## B0042

[Lines 75–75](../../../../cmake/LibPgQuery.cmake#L75); `build-command`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
endif()
if(CROWN_SANITIZERS)

```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Close the optional compiler-target branch. |
| inputs / outputs | No output; terminates the target condition. |
| invariants | This is a CMake control closure only; it adds no runtime condition. |
| ownership | CMake control closure only; it owns no target, file or runtime object. |
| failure | Unbalanced CMake syntax fails configuration; the guarded command’s failure remains at its own phase. |
| cost | Small configure-time variable/control work; no runtime cost. |
| Design | [cmake/LibPgQuery.cmake](../../../../cmake/LibPgQuery.cmake), [CMakeLists.txt](../../../../CMakeLists.txt), [dependencies.lock.json](../../../../dependencies.lock.json), [third_party/libpg_query/README.md](../../../../third_party/libpg_query/README.md), [docs/native_build.md](../../../native_build.md), [cmake/CrownConfig.cmake.in](../../../../cmake/CrownConfig.cmake.in) |

## B0043

[Lines 76–76](../../../../cmake/LibPgQuery.cmake#L76); `build-command`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
if(CROWN_SANITIZERS)
  string(APPEND _crown_pg_query_cflags " -fsanitize=address,undefined -fno-omit-frame-pointer")

```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Guard sanitizer instrumentation for parser C sources. |
| inputs / outputs | CROWN_SANITIZERS decides whether parser CFLAGS gain sanitizer options. |
| invariants | The archive version/hash and generated outputs stay tied to this configured build; this has no per-query CMake role. |
| ownership | CMake configure condition only; its body changes the external parser build flags, not runtime state. |
| failure | Invalid input, generated path or compiler option fails at configure/generation or the later dependency build. |
| cost | Small configure-time variable/control work; no runtime cost. |
| Design | [cmake/LibPgQuery.cmake](../../../../cmake/LibPgQuery.cmake), [CMakeLists.txt](../../../../CMakeLists.txt), [dependencies.lock.json](../../../../dependencies.lock.json), [third_party/libpg_query/README.md](../../../../third_party/libpg_query/README.md), [docs/native_build.md](../../../native_build.md), [cmake/CrownConfig.cmake.in](../../../../cmake/CrownConfig.cmake.in) |

## B0044

[Lines 77–77](../../../../cmake/LibPgQuery.cmake#L77); `build-command`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
  string(APPEND _crown_pg_query_cflags " -fsanitize=address,undefined -fno-omit-frame-pointer")

```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Append ASan, UBSan and frame-pointer flags to parser CFLAGS. |
| inputs / outputs | External Make receives matching instrumentation when sanitizers are enabled. |
| invariants | The archive version/hash and generated outputs stay tied to this configured build; this has no per-query CMake role. |
| ownership | Configure-time CMake variables only; generated files remain under CMAKE_CURRENT_BINARY_DIR. |
| failure | Invalid input, generated path or compiler option fails at configure/generation or the later dependency build. |
| cost | Small configure-time variable/control work; no runtime cost. |
| Design | [cmake/LibPgQuery.cmake](../../../../cmake/LibPgQuery.cmake), [CMakeLists.txt](../../../../CMakeLists.txt), [dependencies.lock.json](../../../../dependencies.lock.json), [third_party/libpg_query/README.md](../../../../third_party/libpg_query/README.md), [docs/native_build.md](../../../native_build.md), [cmake/CrownConfig.cmake.in](../../../../cmake/CrownConfig.cmake.in) |

## B0045

[Lines 78–78](../../../../cmake/LibPgQuery.cmake#L78); `build-command`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
endif()
set(_crown_pg_query_make_args

```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Close the parser sanitizer flag branch. |
| inputs / outputs | No output; terminates the CROWN_SANITIZERS condition. |
| invariants | This is a CMake control closure only; it adds no runtime condition. |
| ownership | CMake control closure only; it owns no target, file or runtime object. |
| failure | Unbalanced CMake syntax fails configuration; the guarded command’s failure remains at its own phase. |
| cost | Small configure-time variable/control work; no runtime cost. |
| Design | [cmake/LibPgQuery.cmake](../../../../cmake/LibPgQuery.cmake), [CMakeLists.txt](../../../../CMakeLists.txt), [dependencies.lock.json](../../../../dependencies.lock.json), [third_party/libpg_query/README.md](../../../../third_party/libpg_query/README.md), [docs/native_build.md](../../../native_build.md), [cmake/CrownConfig.cmake.in](../../../../cmake/CrownConfig.cmake.in) |

## B0046

[Lines 79–81](../../../../cmake/LibPgQuery.cmake#L79); `build-command`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
set(_crown_pg_query_make_args

```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Assemble the GNU Make command and compiler assignment. |
| inputs / outputs | The argument list names make, source directory, build target and CC value. |
| invariants | The archive version/hash and generated outputs stay tied to this configured build; this has no per-query CMake role. |
| ownership | Configure-time CMake variables only; generated files remain under CMAKE_CURRENT_BINARY_DIR. |
| failure | Invalid input, generated path or compiler option fails at configure/generation or the later dependency build. |
| cost | Small configure-time variable/control work; no runtime cost. |
| Design | [cmake/LibPgQuery.cmake](../../../../cmake/LibPgQuery.cmake), [CMakeLists.txt](../../../../CMakeLists.txt), [dependencies.lock.json](../../../../dependencies.lock.json), [third_party/libpg_query/README.md](../../../../third_party/libpg_query/README.md), [docs/native_build.md](../../../native_build.md), [cmake/CrownConfig.cmake.in](../../../../cmake/CrownConfig.cmake.in) |

## B0047

[Lines 82–82](../../../../cmake/LibPgQuery.cmake#L82); `build-command`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
if(NOT _crown_pg_query_cflags STREQUAL "")

```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Guard adding a CFLAGS assignment when composed flags exist. |
| inputs / outputs | An empty base flag string is valid; sysroot or sanitizer flags can make it nonempty. |
| invariants | The archive version/hash and generated outputs stay tied to this configured build; this has no per-query CMake role. |
| ownership | CMake configure condition only; no target, file or runtime object is owned by the guard. |
| failure | Invalid input, generated path or compiler option fails at configure/generation or the later dependency build. |
| cost | Small configure-time variable/control work; no runtime cost. |
| Design | [cmake/LibPgQuery.cmake](../../../../cmake/LibPgQuery.cmake), [CMakeLists.txt](../../../../CMakeLists.txt), [dependencies.lock.json](../../../../dependencies.lock.json), [third_party/libpg_query/README.md](../../../../third_party/libpg_query/README.md), [docs/native_build.md](../../../native_build.md), [cmake/CrownConfig.cmake.in](../../../../cmake/CrownConfig.cmake.in) |

## B0048

[Lines 83–83](../../../../cmake/LibPgQuery.cmake#L83); `build-command`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
  list(APPEND _crown_pg_query_make_args "CFLAGS=${_crown_pg_query_cflags}")

```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Append the composed CFLAGS value to the Make argument list. |
| inputs / outputs | The external command receives selected base/sysroot/sanitizer flags. |
| invariants | The archive version/hash and generated outputs stay tied to this configured build; this has no per-query CMake role. |
| ownership | Configure-time CMake variables only; generated files remain under CMAKE_CURRENT_BINARY_DIR. |
| failure | Invalid input, generated path or compiler option fails at configure/generation or the later dependency build. |
| cost | Small configure-time variable/control work; no runtime cost. |
| Design | [cmake/LibPgQuery.cmake](../../../../cmake/LibPgQuery.cmake), [CMakeLists.txt](../../../../CMakeLists.txt), [dependencies.lock.json](../../../../dependencies.lock.json), [third_party/libpg_query/README.md](../../../../third_party/libpg_query/README.md), [docs/native_build.md](../../../native_build.md), [cmake/CrownConfig.cmake.in](../../../../cmake/CrownConfig.cmake.in) |

## B0049

[Lines 84–84](../../../../cmake/LibPgQuery.cmake#L84); `build-command`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
endif()

add_custom_command(

```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Close the optional Make CFLAGS branch. |
| inputs / outputs | No output; ends the nonempty-flags condition. |
| invariants | This is a CMake control closure only; it adds no runtime condition. |
| ownership | CMake control closure only; it owns no target, file or runtime object. |
| failure | Unbalanced CMake syntax fails configuration; the guarded command’s failure remains at its own phase. |
| cost | Small configure-time variable/control work; no runtime cost. |
| Design | [cmake/LibPgQuery.cmake](../../../../cmake/LibPgQuery.cmake), [CMakeLists.txt](../../../../CMakeLists.txt), [dependencies.lock.json](../../../../dependencies.lock.json), [third_party/libpg_query/README.md](../../../../third_party/libpg_query/README.md), [docs/native_build.md](../../../native_build.md), [cmake/CrownConfig.cmake.in](../../../../cmake/CrownConfig.cmake.in) |

## B0051

[Lines 86–101](../../../../cmake/LibPgQuery.cmake#L86); `build-command`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
add_custom_command(

```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Register verified extraction and upstream static-library compilation as one output rule. |
| inputs / outputs | Declares archive and header outputs; checks hash, replaces extraction tree, unpacks, runs Make, touches header and depends on pinned inputs/stamps. |
| invariants | The producer runs only for stale declared outputs; extracted files stay in the binary tree. |
| ownership | The binary tree owns extracted source, archive and header outputs; the checked-in tarball remains source input. |
| failure | The checksum runs before removal; hash, extraction, Make or output errors fail this build rule and its dependents. |
| cost | A stale build hashes and extracts the archive and compiles upstream C sources; no per-query work. |
| Design | [cmake/LibPgQuery.cmake](../../../../cmake/LibPgQuery.cmake), [CMakeLists.txt](../../../../CMakeLists.txt), [dependencies.lock.json](../../../../dependencies.lock.json), [third_party/libpg_query/README.md](../../../../third_party/libpg_query/README.md), [docs/native_build.md](../../../native_build.md), [cmake/CrownConfig.cmake.in](../../../../cmake/CrownConfig.cmake.in) |

## B0053

[Lines 103–104](../../../../cmake/LibPgQuery.cmake#L103); `build-command`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
add_custom_target(_crown_pg_query_build

```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Group archive and header outputs behind a named custom target. |
| inputs / outputs | The build-graph node orders consumers after both files exist. |
| invariants | Target usage describes the build-tree archive and applies only to targets that consume it. |
| ownership | CMake target metadata refers to generated build-tree files; no separate runtime object is owned. |
| failure | Invalid target metadata fails configure/export; missing generated files fail dependent build/link. |
| cost | CMake metadata and incremental build ordering; compile/link effects only for consuming targets. |
| Design | [cmake/LibPgQuery.cmake](../../../../cmake/LibPgQuery.cmake), [CMakeLists.txt](../../../../CMakeLists.txt), [dependencies.lock.json](../../../../dependencies.lock.json), [third_party/libpg_query/README.md](../../../../third_party/libpg_query/README.md), [docs/native_build.md](../../../native_build.md), [cmake/CrownConfig.cmake.in](../../../../cmake/CrownConfig.cmake.in) |

## B0055

[Lines 106–106](../../../../cmake/LibPgQuery.cmake#L106); `build-command`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
add_library(crown_pg_query STATIC IMPORTED GLOBAL)

```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Declare crown_pg_query as a globally visible imported static target. |
| inputs / outputs | CMake target metadata represents the archive produced by the custom command. |
| invariants | Target usage describes the build-tree archive and applies only to targets that consume it. |
| ownership | CMake target metadata refers to generated build-tree files; no separate runtime object is owned. |
| failure | Invalid target metadata fails configure/export; missing generated files fail dependent build/link. |
| cost | CMake metadata and incremental build ordering; compile/link effects only for consuming targets. |
| Design | [cmake/LibPgQuery.cmake](../../../../cmake/LibPgQuery.cmake), [CMakeLists.txt](../../../../CMakeLists.txt), [dependencies.lock.json](../../../../dependencies.lock.json), [third_party/libpg_query/README.md](../../../../third_party/libpg_query/README.md), [docs/native_build.md](../../../native_build.md), [cmake/CrownConfig.cmake.in](../../../../cmake/CrownConfig.cmake.in) |

## B0056

[Lines 107–108](../../../../cmake/LibPgQuery.cmake#L107); `build-command`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
set_target_properties(crown_pg_query PROPERTIES

```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Set the imported target location to generated libpg_query.a. |
| inputs / outputs | The target location must equal the declared custom-command output. |
| invariants | Target usage describes the build-tree archive and applies only to targets that consume it. |
| ownership | CMake target metadata refers to generated build-tree files; no separate runtime object is owned. |
| failure | Invalid target metadata fails configure/export; missing generated files fail dependent build/link. |
| cost | CMake metadata and incremental build ordering; compile/link effects only for consuming targets. |
| Design | [cmake/LibPgQuery.cmake](../../../../cmake/LibPgQuery.cmake), [CMakeLists.txt](../../../../CMakeLists.txt), [dependencies.lock.json](../../../../dependencies.lock.json), [third_party/libpg_query/README.md](../../../../third_party/libpg_query/README.md), [docs/native_build.md](../../../native_build.md), [cmake/CrownConfig.cmake.in](../../../../cmake/CrownConfig.cmake.in) |

## B0057

[Lines 109–109](../../../../cmake/LibPgQuery.cmake#L109); `build-command`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
target_include_directories(crown_pg_query SYSTEM INTERFACE "${_crown_pg_query_source_dir}")

```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Expose extracted parser headers as a system include directory. |
| inputs / outputs | Consumers receive the versioned build-tree source directory on their include path. |
| invariants | Target usage describes the build-tree archive and applies only to targets that consume it. |
| ownership | CMake target metadata refers to generated build-tree files; no separate runtime object is owned. |
| failure | Invalid target metadata fails configure/export; missing generated files fail dependent build/link. |
| cost | CMake metadata and incremental build ordering; compile/link effects only for consuming targets. |
| Design | [cmake/LibPgQuery.cmake](../../../../cmake/LibPgQuery.cmake), [CMakeLists.txt](../../../../CMakeLists.txt), [dependencies.lock.json](../../../../dependencies.lock.json), [third_party/libpg_query/README.md](../../../../third_party/libpg_query/README.md), [docs/native_build.md](../../../native_build.md), [cmake/CrownConfig.cmake.in](../../../../cmake/CrownConfig.cmake.in) |

## B0058

[Lines 110–110](../../../../cmake/LibPgQuery.cmake#L110); `build-command`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
target_link_libraries(crown_pg_query INTERFACE Threads::Threads)

```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Propagate Threads::Threads through the parser target. |
| inputs / outputs | The platform thread dependency becomes a downstream link requirement. |
| invariants | Target usage describes the build-tree archive and applies only to targets that consume it. |
| ownership | CMake target metadata refers to generated build-tree files; no separate runtime object is owned. |
| failure | Invalid target metadata fails configure/export; missing generated files fail dependent build/link. |
| cost | CMake metadata and incremental build ordering; compile/link effects only for consuming targets. |
| Design | [cmake/LibPgQuery.cmake](../../../../cmake/LibPgQuery.cmake), [CMakeLists.txt](../../../../CMakeLists.txt), [dependencies.lock.json](../../../../dependencies.lock.json), [third_party/libpg_query/README.md](../../../../third_party/libpg_query/README.md), [docs/native_build.md](../../../native_build.md), [cmake/CrownConfig.cmake.in](../../../../cmake/CrownConfig.cmake.in) |

## B0059

[Lines 111–111](../../../../cmake/LibPgQuery.cmake#L111); `build-command`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
if(CROWN_SANITIZERS)
  target_link_options(crown_pg_query INTERFACE -fsanitize=address,undefined)

```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Guard sanitizer link requirements for the parser target. |
| inputs / outputs | CROWN_SANITIZERS enables the following target link option. |
| invariants | The archive version/hash and generated outputs stay tied to this configured build; this has no per-query CMake role. |
| ownership | The condition creates no runtime state; its body conditionally adds CMake target link metadata. |
| failure | Invalid input, generated path or compiler option fails at configure/generation or the later dependency build. |
| cost | Small configure-time variable/control work; no runtime cost. |
| Design | [cmake/LibPgQuery.cmake](../../../../cmake/LibPgQuery.cmake), [CMakeLists.txt](../../../../CMakeLists.txt), [dependencies.lock.json](../../../../dependencies.lock.json), [third_party/libpg_query/README.md](../../../../third_party/libpg_query/README.md), [docs/native_build.md](../../../native_build.md), [cmake/CrownConfig.cmake.in](../../../../cmake/CrownConfig.cmake.in) |

## B0060

[Lines 112–112](../../../../cmake/LibPgQuery.cmake#L112); `build-command`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
  target_link_options(crown_pg_query INTERFACE -fsanitize=address,undefined)

```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Propagate sanitizer link options for instrumented parser objects. |
| inputs / outputs | Consumers receive matching ASan/UBSan final-link flags. |
| invariants | Target usage describes the build-tree archive and applies only to targets that consume it. |
| ownership | CMake target metadata refers to generated build-tree files; no separate runtime object is owned. |
| failure | Invalid target metadata fails configure/export; missing generated files fail dependent build/link. |
| cost | CMake metadata and incremental build ordering; compile/link effects only for consuming targets. |
| Design | [cmake/LibPgQuery.cmake](../../../../cmake/LibPgQuery.cmake), [CMakeLists.txt](../../../../CMakeLists.txt), [dependencies.lock.json](../../../../dependencies.lock.json), [third_party/libpg_query/README.md](../../../../third_party/libpg_query/README.md), [docs/native_build.md](../../../native_build.md), [cmake/CrownConfig.cmake.in](../../../../cmake/CrownConfig.cmake.in) |

## B0061

[Lines 113–113](../../../../cmake/LibPgQuery.cmake#L113); `build-command`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
endif()
add_dependencies(crown_pg_query _crown_pg_query_build)

```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Close the sanitizer link-option condition. |
| inputs / outputs | No output; ends the target link-options branch. |
| invariants | This is a CMake control closure only; it adds no runtime condition. |
| ownership | CMake control closure only; it owns no target, file or runtime object. |
| failure | Unbalanced CMake syntax fails configuration; the guarded command’s failure remains at its own phase. |
| cost | Small configure-time variable/control work; no runtime cost. |
| Design | [cmake/LibPgQuery.cmake](../../../../cmake/LibPgQuery.cmake), [CMakeLists.txt](../../../../CMakeLists.txt), [dependencies.lock.json](../../../../dependencies.lock.json), [third_party/libpg_query/README.md](../../../../third_party/libpg_query/README.md), [docs/native_build.md](../../../native_build.md), [cmake/CrownConfig.cmake.in](../../../../cmake/CrownConfig.cmake.in) |

## B0062

[Lines 114–114](../../../../cmake/LibPgQuery.cmake#L114); `build-command`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
add_dependencies(crown_pg_query _crown_pg_query_build)

```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Order parser consumers after the target that produces its files. |
| inputs / outputs | The imported target depends on _crown_pg_query_build. |
| invariants | Target usage describes the build-tree archive and applies only to targets that consume it. |
| ownership | CMake target metadata refers to generated build-tree files; no separate runtime object is owned. |
| failure | Invalid target metadata fails configure/export; missing generated files fail dependent build/link. |
| cost | CMake metadata and incremental build ordering; compile/link effects only for consuming targets. |
| Design | [cmake/LibPgQuery.cmake](../../../../cmake/LibPgQuery.cmake), [CMakeLists.txt](../../../../CMakeLists.txt), [dependencies.lock.json](../../../../dependencies.lock.json), [third_party/libpg_query/README.md](../../../../third_party/libpg_query/README.md), [docs/native_build.md](../../../native_build.md), [cmake/CrownConfig.cmake.in](../../../../cmake/CrownConfig.cmake.in) |
