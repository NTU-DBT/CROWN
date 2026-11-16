# Independent native O07 integration review — 2026-11-07

Disposition: **no blocking source-integration finding in the reviewed native
snapshot**. This is acceptance of the applied source map and wiring, not a
claim that the native verification matrix passed or O07 is complete. O07 is
in progress; the recorded ledger state is 36 verified / 3 in progress / 39 not
started. The reviewer performed source reads and metadata/hash analysis only:
no executable, Python checker, CMake or CTest execution and no root-process
polling. Root separately reported its initial all-target Release build passed.
That build alone does not establish the final multi-configuration acceptance.

## Applied snapshot and preservation

`build/verification/o07-native-integration-applied.json` records 108 copied
native paths. All 108 current destination hashes equal both their recorded
`after_sha256` and the corresponding accepted proposal source bytes. All ten
replaced files have backups matching their recorded `before_sha256`. New files
have no invented preexisting backup. The map hash is
`c8498024948326954d1408e7b6c7a3b691306fba20f40745495313802a4f7356`.
The native CMake file is
`81dbe6daffe09a4a769b4d02a2c3276bb9e13009ae381bb2ddc20a7851339b63`.

All nine historical manifest **files** match the preapplication checkpoint:
P05, P06, P04, O03, R06, O02, O01, D06 and P07. Their internal entries were not
revalidated against the changed native tree. They remain historical snapshots,
not a current O07 source seal. `Refactor.md` still has its original SHA-256
`bb90e4a4e97e2817a0869ad86c5c8b00e571bb241f153fb44641c71f86fcd5ce`.

The application map has no existing Core/planner/Reference or legacy-test
source destination: its test CPP additions are the six new acceptance files;
its intended runtime changes are the reviewed support/physical/delta/session
sources and public runtime headers, with observation.cpp added. Forty-five
unaffected paths additionally match available O07-specific preintegration
baseline pins. This is the extent of the independently checked unchanged-file
claim. The available preapplication full-source records contain aggregate
fingerprints, not a separate per-path map; this review does not invent a full
unchanged-header/Core/legacy-file proof or reuse old seal entries as a current
check. The detailed 45-path list is in the audit metadata below.

## Production and testing closure

`CMakeLists.txt:43–77` gives the production direction:
query-explain → Core; SQL → Core/libpg_query; Plan → SQL/Core;
Runtime → Plan; Explain → Runtime/query-explain; CLI → Explain/Reference.
Reference stays on Core. libpg_query is an imported static target with a
Threads dependency (`cmake/LibPgQuery.cmake`), not a back edge to Runtime.
Native runtime sources do not include the report factories. This graph is
acyclic.

The single nine-source `CROWN_RUNTIME_SOURCES` list at CMake lines 55–56 is
used in full by both `crown_runtime` and `crown_runtime_testing`. The testing
variant propagates `CROWN_RUNTIME_TESTING` publicly (lines 153–156).
`crown_explain_testing` uses only `crown_runtime_testing`; production Explain
uses only production Runtime. The five new runtime-consuming acceptance
executables use Explain-testing. The sixth, query-explain, links only the
query/Core/Reference closure (lines 162–177). No target's transitive graph
contains both runtime variants.

After root reported its terminal Release build, the reviewer read its generated
link.txt and compile_commands.json **as metadata**, without executing them.
All seven inspected final link commands (CLI plus six new tests) agree with
that source graph. Both runtime variants have all nine native-source compile
commands; the macro is absent in production and present in every testing
runtime command. No command uses an excluded overlay include directory. This
addresses the nontrivial ObservationSnapshot/Summary ABI risk: there is no
old-runtime archive or mixed-runtime variant in these generated closures.

## Native acceptance packaging checklist

| Native surface | Checked integration |
| --- | --- |
| `tests/unit/runtime_observation_test.cpp`, `observation_mode_binding_test.cpp`, `observation_run_context_test.cpp` | Byte-identical accepted final-layer adaptations; test-only hooks are linked to the complete testing runtime. |
| `tests/unit/cursor_observation_test.cpp` | Byte-identical accepted fixture revision; uses native headers and existing Reference helpers. |
| `tests/unit/query_explain_test.cpp`, `tests/support/query_families.hpp` | Accepted depth revision plus local family header; query test has no Runtime dependency or included test CPP. |
| `tests/unit/composed_explain_test.cpp` | Accepted detached-owner revision `3b1fdd7…`; native sidecar capture remains before owner teardown. |
| `tools/support/check_query_reports.py` | The sole difference from accepted checker is `PACKAGE = Path(__file__).resolve().parents[2]`; no schema/semantic/oracle gate changed. |
| Cursor/composed checkers and `tools/verify_observability_reports.py` | Native paths only in execution. Wrapper creates a fresh corpus, runs `all`, requires complete checking, preserves failures and removes successful temporary output. Composed schema/root arguments are explicit (wrapper lines 25–35). |
| `tests/observability/cli/` | Whole accepted 475a package copied, including readiness and all 66 hashed package files; its four schemas match native schemas exactly. All 63 fixture/schema payload files retain accepted hashes. |
| `schemas/` | Final V2 report/tree and standalone V1 query/witness schemas are present; no superseded physical V1 schema is used by the new native registrations. |
| `apps/crown/main.cpp:79–80`, `apps/crown/explain.cpp` | Existing main dispatches to the separate EXPLAIN implementation; the accepted production CLI source is copied exactly. |

The CLI package SHA is
`475a36a1a275ac4d1f0d066f1ce637d7d7e97fd2f7d49599104c185e02f8d80a`;
its runner SHA is
`ceff2d13e45f07a7ee0cd6b6ae90c1ea6e8f7d9bcaebd522d78b655f72a409da`.
Its readiness self-pins verify in the native location. An explicit optional
`--expected-crown-sha256` is enforced; otherwise the actual selected build's
binary identity is recorded. CMake therefore correctly runs each native
configuration's `$<TARGET_FILE:crown>` without pinning every build to one
preparatory production executable. The default `/tmp` output parent and fresh
child per run make the omitted output argument intentional and portable.
Proposal paths in the copied README/source-map are provenance, not executable
runtime dependencies. JSON schemas and fixtures remain mandatory byte pins.

Static comparison with the backed-up CMake gives exactly **92 → 99** distinct
registrations. Every original test name and COMMAND is preserved. The seven
new names are `runtime_observation`, `observation_mode_binding`,
`observation_run_context`, `cursor_observation`, `query_explain`,
`composed_explain` and `explain_cli` (CMake lines 164–170 and 362–367).
Root also independently reported the generated graph has those 99 cases.

## Authority and compatibility boundaries

The copied factories preserve exact native Catalog/Query equality, candidate
policy context and selected-tree binding (`src/observability/explain.cpp:26–70,
142–161`). A selected alternative can carry the original minimum proof;
JSON and caller flags cannot create that proof. The constant-false executable
operator remains separate from original structural height/infeasibility
(lines 167–169). Actual-owner runtime/session capture keeps private-state
gauges unavailable and distinguishes a dropped session (lines 175–197).
These factories and the accepted bounded manual codecs match the reviewed
source bytes; no new admission JSON or report-authority constructor appeared
in native application.

`ObservationOptions` still defaults to **timed**
(`include/crown/runtime/observation.hpp:19`). Legacy capture/timing fixtures
were not rewritten to counters or stripped of their capture requests. Only
explicit off plus allocating legacy transition capture remains rejected.
Current versus begin configuration, actual output lifecycle, owned numeric
trace, source work inclusions and unavailable accounting fields retain the
accepted implementation. Removal of the stale native-integration gate is the
intentional native report/schema adaptation, not evidence of broader cost,
durability, recovery or benchmark guarantees.

## Remaining acceptance boundary and evidence

No source blocker is unresolved in this snapshot. The full native matrix,
sanitizer/fault results, final public-doc reconciliation, exact current source
inventory and new O07 seal remain root-owned acceptance work. Preparatory
accepted CLI (root reports 2,750 checks / 175 calls) and owner/report runs
support provenance; they do not replace fresh native tests after application.
Later ordinary documentation changes must be included in the final inventory;
this review does not preapprove unknown later source edits.

Metadata-only audit artifacts:

- `/tmp/o07-native-integration-independent-audit.json`, SHA `727889483dff3a0dae68356a25a329cb30cc424b1614cf205461a7cb43457f34`: 108 destinations/source copies, ten backups, nine historical FILE hashes, Refactor, 45 unaffected O07 pins, registrations and static graph.
- `/tmp/o07-native-integration-generated-graph-audit.json`, SHA `79079640de0d32e91bddb45b8b081692bfa1b12ff9aeafe8704aabc50594fbb3`: seven generated link closures and both nine-TU compile variants, read only after root reported build termination.
