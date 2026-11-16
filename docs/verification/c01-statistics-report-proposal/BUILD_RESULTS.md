# Report proposal compile evidence

2026-11-07. **Final strict compilation/linking completed; all execution and schema/checker validation remain pending root. C01 remains `not_started`.** No native source/header/test/tool/schema/CMake file or frozen proposal was modified.

| Final variant | Implementation/report TUs | Consumer TUs / executables | Status |
| --- | ---: | ---: | --- |
| Production | 23 | 5 | Every final compile/link exited 0 |
| `CROWN_RUNTIME_TESTING` | 23 | 6 | Every final compile/link exited 0 |
| Frozen combined legacy control | 19 pinned existing objects + 2 original query report TUs | 1 | Compile/link exited 0 |

Both final variants use `-std=c++23 -O2 -g -UNDEBUG -Wall -Wextra -Wpedantic -Wconversion -Wsign-conversion -Werror -pthread`. [Compiler identity](build-evidence/compiler-version.txt) is GCC 13.3.0 (`Ubuntu 13.3.0-6ubuntu2~24.04.1`). No warning is disabled. Every runtime and consumer object is compiled with the matching macro variant; the testing-only numeric seed is absent from production.

Final outputs are `/tmp/crown-c01-report-production-final` and `/tmp/crown-c01-report-testing-final`. Expanded [production commands](build-evidence/production-commands.sh) and [testing commands](build-evidence/testing-commands.sh) record all compilations and links. [Production artifacts](build-evidence/production-artifacts.sha256) pin 96 files; [testing artifacts](build-evidence/testing-artifacts.sha256) pin 101 files, including all objects, executables, dependency files and logs. The final logs are empty. Earlier `/tmp/crown-c01-report-api`, `production` and `testing` outputs precede the runtime-context architecture correction and are not the final evidence.

The runtime-only consumer links exactly the first 15 runtime/IO-support objects and five frozen foundation archives. It links no `src/observability` or report IO object. Native [CMakeLists.txt](../../../CMakeLists.txt) keeps those foundation archives independent of observability. This successful link addresses the runtime/report dependency boundary that an all-object standalone report link alone could hide.

The independent control is `/tmp/crown-c01-report-legacy-control/statistics_legacy_control`. Its [commands](build-evidence/legacy-control-commands.sh), [19 frozen object identities](build-evidence/legacy-control-frozen-objects.sha256), and [14 artifact identities](build-evidence/legacy-control-artifacts.sha256) are preserved. It uses frozen combined runtime/header bytes and original native report code; none of the new v3 implementation is linked. Its future output is the reference for two byte-exact C01-off v2 comparisons. No comparison has been executed yet.

| Final executable | SHA-256 |
| --- | --- |
| Production report producer | `f4ba9114409c71275cfd82699b832e3b565ab788983dce21aac9e82990c33cde` |
| Testing report producer | `399a9ed0f12e9408cdd4700587d3a395e1073519a06fcb4c7d85b1efb2d27758` |
| Production runtime-only consumer | `fec619d5da8db45b5a1d3c9b65f58348450fed6bf8966ae84ef00ed4494ff7d4` |
| Testing runtime-only consumer | `4d58ca02d45158e853f40f673e7b6f733a7032e5a2405d0fe293fe8d8941a0b3` |
| Frozen combined legacy control | `b042e8c80a99bcea6e6242235ae913046107664d3fd6d333662dfbf20d67258f` |

[Production](build-evidence/production-dependencies.sha256), [testing](build-evidence/testing-dependencies.sha256), and [control](build-evidence/legacy-control-dependencies.sha256) archive manifests pin the actual five Release archives. They retain the root-supplied core/SQL/plan/reference/parser hashes. No cached library was rebuilt. The overridden storage object precedes the archive group.

`INPUT_SHA256SUMS` has 154 entries and SHA-256 `35f8ccd336d48f9b7c0258531f76097820af9072f7dd66a540afac444b0d9e50`. It includes actual compiler dependencies outside this overlay, all 28 existing native schemas, native comparison inputs, frozen combined sources/manifests, the 19 control objects, five linked archives and O07 seal/checkpoint. Compiler/standard-library implementation files are identified by compiler version rather than exhaustively hashed. `source-files.sha256` pins all 48 overlay files at `c8b5c3f43eb513e3fab9163bf4d3f8fb62662f73cd6cc0bd01667878a535216c`. `PACKAGE_SHA256SUMS` covers every package file except itself.

The frozen combined package manifest remains `cb0ecb64935f80bf4915aa069de1bf01bcf1ea2f22a591f6f7408d405fcf4cfe`; its accepted owner and online ancestors remain unchanged. Root reported that the combined strict suites passed. Those successes are not report results. O07 remains independently verified under ordinary source seal `f4acf6ea043859d350aa0dd2d56c86afca24535d7288eb5774f94b26ab0ea21e` (691 entries).

The new producer proposes 31 ordinary v3 artifacts, with an additional actual-owner saturation artifact in testing. It also checks literal owner facts, event-versus-state distinctions, generalized 0/1 pre-probe presence, immutable history, explicit v2 rejection, and exact/one-under/zero export caps. The new exception consumer proposes four same-owner sweeps: runtime report capture, JSON export, human export and guarded private-session capture. The checker proposes 15 ordinary schema/semantic mutations plus two saturation mutations in testing. Actual produced counts, failures injected, schema validation and sanitizer outcomes must come from root execution.

[ROOT_REPRODUCTION.md](ROOT_REPRODUCTION.md) contains exact execution and full two-variant ASan/UBSan/leak commands. Native source registration, default/opt-in CLI behavior, full legacy and C01 policy matrices, measured engine overhead and total allocator accounting remain open. The preparation-only `c01_project_gate=open` report/schema constant must be reconciled with repository acceptance before the final native C01 matrix; this packet does not permanently prescribe an open gate for a verified build.
