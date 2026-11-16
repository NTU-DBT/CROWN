# O07 native integration wiring proposal — unapplied

This new excluded package prepares concrete native build and CLI wiring on top of the frozen composed EXPLAIN package. It does **not** apply native changes, run CMake, register unaccepted tests, execute binaries, run Python tests, or advance O07 status. O07 remains NS until root integration. Prior runtime/report/query proposals and native sources remain pinned and unchanged.

## Dispatcher and narrow corrections

The authored overlay moves the standalone command implementation into `apps/crown/explain.cpp`, with private `apps/crown/explain.hpp` declaring `crown::cli::explain_main(int,char**)`. It has no `main` function. Native `apps/crown/main.cpp` includes that private header and dispatches `crown explain ...` using `argc-1, argv+1`. The native `main` remains the sole program entry point. Existing command branches, results and error handlers remain byte-identical; only the include, new help branch and new dispatcher branch are added. EXPLAIN keeps its bounded/sanitized diagnostics and 0/1/2/3/4 exit convention. Other commands continue using their existing JSON error handlers and exit conventions.

`crown --help` lists existing commands plus `explain`; `crown explain --help` gives the physical/runtime/session/query/progress/replay command forms and supported options. The full implementation and authority/lifecycle rules remain those documented in the frozen composed proposal. Search and replay work is explicit CLI work before read-only capture, not hidden in export.

The frozen standalone `evidence()` did consume `--proof-work` before checking for `--certificate`, silently ignoring an otherwise inapplicable option. The adapted function takes both options, rejects a supplied proof quantum without its certificate with `usage`, and only then parses the applicable quantum. This is a narrow CLI correction in this new overlay; the frozen standalone package is not changed. Root should independently check an otherwise valid physical plan with orphan `--proof-work` fails, valid paired options retain the existing proof route, and missing/invalid/duplicate options preserve expected diagnostics.

The native report IO mirror removes the transient `native_integration_and_acceptance` entry from `open_gates` and removes that transient phrase from human output. The matching native v2 schema no longer admits that entry. This avoids a permanently stale development-state assertion after actual integration; it does not certify this proposal as integrated or verified. Genuine unavailable S05 allocator accounting, checkpoint/recovery/delivery, C01/C02 statistics/ranking and benchmark/release gates remain. Frozen query-report/witness v1 schemas are included byte-for-byte in the source map alongside both final v2 schemas, so standalone query IO retains its documented contract.

## Concrete target ownership

The mirrored CMake file contains only the required source and target changes:

- `crown_query_explain`: `src/observability/query_explain.cpp`, `src/io/query_explain.cpp`; PUBLIC dependency on `crown_core`, PRIVATE warnings/options. No runtime dependency.
- `CROWN_RUNTIME_SOURCES` appends `src/runtime/observation.cpp`, so both existing runtime variants compile it. The final composed nine-unit runtime source/header layer remains required.
- `CROWN_EXPLAIN_SOURCES`: `src/observability/explain.cpp`, `src/io/explain.cpp`, `src/io/run_context.cpp`, `src/io/cursor_observation.cpp`.
- `crown_explain`: these four sources, PUBLIC `crown_runtime` and `crown_query_explain`, PRIVATE options. Runtime never depends back on report IO.
- `crown`: existing `apps/crown/main.cpp` plus `apps/crown/explain.cpp`; links `crown_explain`, `crown_reference`, options. Its runtime dependency is production runtime through the report target, even with BUILD_TESTING enabled.
- Within BUILD_TESTING, `crown_explain_testing` recompiles the same four report sources and links PUBLIC **only** `crown_runtime_testing` plus the runtime-free `crown_query_explain`. `CROWN_RUNTIME_TESTING` propagates from runtime_testing. Future observation tests must link this report variant without additionally linking `crown_explain` or `crown_runtime`; mixing those archives would violate the matched-header/ODR requirement.

No new test targets, test files or registrations are included. Root will supply the final independently accepted source list. Existing test registrations and sanitizer policies are unchanged. No configure/generate/CTest result is claimed; the CMake edit is a source proposal awaiting root validation.

## Patches, source map and compiler evidence

`native-integration-incremental.patch` is applied after the frozen composed native-source patch. It adds the native dispatcher/build edits, supersedes final IO/v2 schema, adds the two frozen v1 schemas, and deletes the previously proposed `apps/crown-explain/main.cpp` standalone entry point from that composed staging tree. This deletion is patch text only; no prior proposal file was removed.

`native-integration-complete.patch` consolidates all required highest-layer runtime/report sources and this adaptation directly against pinned native files. It omits both obsolete standalone prototype CLI paths. `source-map.json` contains 30 resolved native destinations, exact source hashes and existing native baseline hashes. All four schema destinations are explicit:

- `schemas/explain-report-v2.schema.json`
- `schemas/explain-tree-v2.schema.json`
- `schemas/query-explain-v1.schema.json`
- `schemas/query-witness-v1.schema.json`

`baseline-sha256.json` pins the native CMake/main/reference library, all frozen composed package files and its transitive prior/native baselines. Compiler evidence is generated by direct C++ invocation into `/tmp`, not a native build. `build_cli.py OUTPUT --configuration testing|production` validates those pins, compiles the two new application units and changed report IO with strict C++23 warnings-as-errors, then links against the matching complete final nine-unit runtime archive and five unchanged matched report objects. The old standalone main and superseded report IO objects are excluded. Production uses O3 without `CROWN_RUNTIME_TESTING`; the isolated testing build uses O0 with that definition across all adapted consumers and the matched runtime/report closure. The unchanged core/plan/sql/reference/libpg_query libraries are pinned, with the prior composed ABI include audit showing no runtime-layout consumption in their source closure. Header search precedence is this adaptation → Composed → Cursor → RunContext → Mode → Runtime → original physical report → query report → native.

The resulting `/tmp/.../crown` binaries have been linked but never run here. Reused object/library hashes and compiler-generated dependencies are recorded. This validates C++ interfaces and linkage, not CMake correctness or command behavior. Root should run both old-command regressions and new EXPLAIN cases after reviewing/applying the concrete patch, including `--help`, `explain --help`, every dispatcher form, orphan proof work, schema closure and absence of the stale integration gate. Full native matrices/sanitizers and O07 acceptance remain required.
