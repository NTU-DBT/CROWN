# Combined proposal build evidence

2026-11-07. **Compile/link completed; combined execution is pending root. C01 remains `not_started`.** This is excluded preparation. No test binary, diagnostic, Python checker, CMake, CTest, `nm`, network or git operation was executed by the author.

## Completed strict builds

Compiler: GCC 13.3.0 (`Ubuntu 13.3.0-6ubuntu2~24.04.1`), recorded in [compiler-version.txt](build-evidence/compiler-version.txt). Flags include `-std=c++23 -O2 -g -UNDEBUG -Wall -Wextra -Wpedantic -Wconversion -Wsign-conversion -Werror -pthread`. No warning is suppressed. Overlay headers, private runtime headers and fixture headers precede their native counterparts; `third_party` is a system include.

| Variant | Linked implementation/consumer TUs | Additional report compatibility TUs | Test/diagnostic TUs | Linked executables | Result |
| --- | ---: | ---: | ---: | ---: | --- |
| Production | 15 | 4 | 7 | 7 | Every final compile/link command exited 0 |
| `CROWN_RUNTIME_TESTING` | 15 | 4 | 5 | 5 | Every final compile/link command exited 0 |

Production outputs are `/tmp/crown-c01-combined-production`; testing outputs are `/tmp/crown-c01-combined-testing`. All 15 runtime/consumer objects were separately compiled in each variant. No runtime object or test object is reused across macro variants. The four report compatibility objects are unlinked: they show existing consumers still compile with the merged public headers, not that serialization integrates C01.

The source closure consists of the overridden storage implementation; state collector, owner collector, numeric collector, workload collector, joint capture and four runtime owners; and unchanged IO support/inspection, replay, window and observation consumers. Five frozen Release archives supply the remaining unchanged dependencies. The storage override is ahead of the archive group so the old storage object is not selected. See [source-map.md](source-map.md) for exact paths.

[Production commands](build-evidence/production-commands.sh) and [testing commands](build-evidence/testing-commands.sh) preserve actual expanded invocations, including incremental test recompilation and subsequent report compatibility compilation. [Production artifact hashes](build-evidence/production-artifacts.sha256) pin 98 files; [testing artifact hashes](build-evidence/testing-artifacts.sha256) pin 86 files. They include objects, executables, dependency files, command logs and the original unsuccessful warning log. Output-directory artifacts are evidence, not package source inputs.

An initial testing compilation at `-O2` diagnosed GCC's `-Wmaybe-uninitialized` in the accepted fixture's temporary `std::variant` move at `terms.push_back(IgnoredColumn{})`. The combined-only fixture now constructs the same variant alternative in place with `emplace_back(std::in_place_type<IgnoredColumn>)`. [The exact one-line patch](build-evidence/fixture-construction.patch) changes no query, input row, expected value or assertion. Both affected online consumers and both new joint consumers were then recompiled and linked with the full flags. Final logs are empty. The original log remains at `/tmp/crown-c01-combined-testing/workload_statistics_test-initial-O2-warning.log`, pinned in the testing artifact manifest. The accepted online package was not modified.

| Joint executable | SHA-256 |
| --- | --- |
| Production `combined_statistics_test` | `97252b7d675cd880466645a5973ccce2e6057922e0407767992f04e0f63a9062` |
| Production `combined_statistics_exception_test` | `d10ca14784638f9e134a15c3ddcc94054b74ffe7796f3ac7ad59a8c454c96c2e` |
| Testing `combined_statistics_test` | `cb638b59ed5d96cd1e1335704f152a1bfc6be2f39213ba89d63a0d2eed44191a` |
| Testing `combined_statistics_exception_test` | `ac093708aa0012144d97356d88541324a813cb895882b448ee7118fd1168ef02` |

## Dependencies and accepted predecessors

Both variants link the identical archives in [production-dependencies.sha256](build-evidence/production-dependencies.sha256) and [testing-dependencies.sha256](build-evidence/testing-dependencies.sha256):

| Archive under `build/release` | SHA-256 |
| --- | --- |
| `libcrown_core.a` | `784b820ff9284ad75033552056fd2a81113f7eb54be5db56959f31ce778bcf9d` |
| `libcrown_sql.a` | `6ba92b30615a1b35c7b499d1067647be49be47757b8ee58cb1098c65d275d26e` |
| `libcrown_plan.a` | `92a96fd0f01ade3862fb4fbbabe316337719f71eb43361f5eb6b250cdfe04d6a` |
| `libcrown_reference.a` | `035a204d7e00355b7f14e94255f8d77688f43a5688aabba898f6cedfd43f39f5` |
| `_deps/libpg_query/libpg_query-18.1.0/libpg_query.a` | `c254ea2e05708d5cf5e8526bad19d69d314d05a9af4f7a8b0be4b08e069e2174` |

The accepted owner package manifest is `dc7276b9c6427784f67372a95efa0365de3859203a0c1706fe2fe494ef02869e`; the accepted online manifest is `61281d60312f371930a6ddcb4c2c51570eb6d5c70264432715a7da0a3d247281`. Their preserved root results are [owner attempt 2](../../../build/verification/c01-statistics-owner-root-attempt-2.json) and [online attempt 1](../../../build/verification/c01-statistics-online-root-attempt-1.json). Root accepted the owner/storage groups and fault sweeps, and the online collector/integration groups and fault sweeps, separately under strict and sanitizer builds. Those accepted results are prerequisites; they are not combined results.

O07 has since been sealed by root after five 99-test matrices. The current ordinary [source seal](../observability-sources.sha256) has 691 entries and SHA-256 `f4acf6ea043859d350aa0dd2d56c86afca24535d7288eb5774f94b26ab0ea21e`. The [completion checkpoint](../../../build/verification/observability-completion-checkpoint.json) is pinned at `3d757ad07c62cbbac7d2de9fa87d0d4e11ddc435143172adfc724e490947aee3`. No native file is changed by this proposal.

`INPUT_SHA256SUMS` pins 119 actual native/compiler-dependency, predecessor-overlay, design/report-contract and archive inputs. Its SHA-256 is `bf37819e3dbd98fc3bc456015df53b5294571b563d484dbbcbe03321dea8c286`. `source-files.sha256` pins all 35 overlay files and has SHA-256 `4bc21abf9b8833e6f624643bac370fc6efc638c9feba8d8e3476477e38886156`. System compiler/standard-library files are identified by compiler version rather than exhaustively hashed. `PACKAGE_SHA256SUMS` covers the new package except itself. Root should preserve independent whole-native seals as well.

## Pending execution and coverage

Production proposes the unchanged 18 owner groups, 14 storage groups and their five allocation sweeps, the unchanged generalized diagnostic, plus nine joint groups and one new joint allocation sweep. Testing proposes the unchanged collector regressions, unchanged 10 online integration groups and online allocation sweeps, plus the same nine joint groups and joint allocation sweep. No combined pass count or injected-failure count is yet observed.

[ROOT_REPRODUCTION.md](ROOT_REPRODUCTION.md) gives exact strict execution and complete two-variant ASan/UBSan/leak commands. Combined sanitizer builds and execution have not been attempted by the author. Full native policy/constraint/window/scalar matrices, report/schema/CLI integration, benchmark instrumentation identification, measured engine overhead and S05 accounting remain open. The [report inventory](explain-integration-inventory.md) preserves default v2 compatibility and proposes opt-in versioned integration without implementing it.
