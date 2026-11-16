# C01 native registration and publication independent review

2026-11-07. Independent Astra Max review, finalized against the frozen package below. **No unresolved blocking defect established in the registration/publication candidate.** The inspected build wiring, source mapping, baseline provenance, wrapper, publication change, and final documentation are coherent. This conclusion is source-review evidence; the expected 131-test registration and native compiler/sanitizer/clean-source results still require root execution. C01 remains `not_started` at this pre-application boundary.

Only this review document was written. No candidate, native file, frozen predecessor, historical manifest, or acceptance record was edited. The reviewer executed no CMake, CTest, Python checker, project binary, benchmark, or symbol inspector, and compiled no additional diagnostic. Root retains the immediate pre-application check of the old 691 source entries; this review did not repeat that full audit.

## Frozen inputs

Package-relative paths below refer to `docs/verification/c01-statistics-native-registration-proposal/`.

| Input | SHA-256 |
| --- | --- |
| `PACKAGE_SHA256SUMS`, 93 entries | `3a8ad914fabffc307f21f645c099f657cb6ad4484a42e93c5de0c52fbc6d2c18` |
| `INPUT_SHA256SUMS`, 344 entries | `daa335e88947592038632bc4edd19c9a31f9471d8f88b7ff3f91dd1d34aac56d` |
| `source-files.sha256`, 62 destinations | `9b46c92287ac1ba58e96108095305e89a0f03b8d56ea1954503c75627e75cf99` |
| `PREEDIT_DESTINATIONS_SHA256SUMS`, 20 entries | `b6b39267aa6d402a843400c1875834b58b7d057943ef3fd42b5c36ce7a0ef6b9` |
| `NEW_DESTINATIONS.txt`, 42 entries | `aa5b67ed18ad04ce98e27d2b7594f4896bcdb0d713018052674040ab980e913a` |
| `source-map.tsv` | `0e10f026f6f6044ac0c6cbac10d3c431081d458d6757a2b039683deac3b067ff` |
| `expected-ctests.txt`, 131 unique names | `697887db2b28bcd53287d0fa1e449342e2c3faa822fc41dd5019476706b0766d` |
| `overlay/CMakeLists.txt` | `85c4b77a82ed29238e822b2f98d5e530ada593ddb46e4d1b10f275356d36143e` |
| `overlay/tools/verify_statistics_reports.py` | `e0fa12df16ff73b49d20481d2e1c60fed5def6b382bc0e4ba2e757fabb349713` |
| Copied `overlay/tools/support/check_statistics_reports.py` | `3c7a12c18c3e9b1eb1ff09e56ad620f966d02f6de41435aa3aa6d207fe9a426b` |
| `overlay/schemas/statistics-explain-v3.schema.json` | `160316d4f705dcb5a314ee090578a93e96310e424d04aeb7dee884d2dc0ced10` |
| `overlay/docs/statistics.md` | `37cad58989031ffbcf0c2573dfc3dc4a1d98a29fcd4f0ff46c6c9e181bd4c0dd` |
| Frozen report predecessor manifest | `730a7488e53a749b024b307dab27c09d58a324ae7603bccc8831364af289f947` |
| Root report strict attempt 1 JSON | `0c8b2051866d751dd632a5d036ac1d042e110e32386a0a75026699ee6ce17d1c` |
| Root report complete-sanitizer attempt 2 JSON | `e00845f8f553181ed1658e018dc5e44a550d9b96e90ea960cf6d890aa91aedb7` |
| Root actual-engine benchmark attempt 3 JSON | `b7447586fe1cd442cb51d0c0d0b78e813a0ad496a42fd7d9ad1895c060080b7e` |

`sha256sum --quiet -c` exited 0 for the package, input, source, pre-edit destination, production-artifact, and testing-artifact manifests: 93/344/62/20/12/12 entries respectively, with overlap. Every listed new destination was absent. The 20 existing and 42 new destinations exactly partition the source map. The map exactly covers all overlay files, and each `exact_copy` entry compared equal to its recorded origin. These checks establish identity and mapping, not successful native execution.

## Review results

**Build and dependency direction.** The five statistics runtime units are added to `CROWN_RUNTIME_SOURCES`, used by both production and testing runtime libraries. The two report units are added only to `CROWN_EXPLAIN_SOURCES`. Storage remains in `crown_core`; its changed reference implementation includes storage/core facilities and does not introduce a runtime/report dependency. The runtime libraries still depend downward on plan/core, and the report libraries depend on the corresponding runtime. No inspected target links both runtime variants. The existing public `CROWN_RUNTIME_TESTING` definition flows from the testing runtime into its matching report library and consumers; it is not a global definition.

The new internal collector/workload tests receive `src/runtime`, probe consumers receive `tests/support`, and owner/policy tests requiring the independent evaluator link `crown_reference`. Quote-included runtime implementation headers reside alongside their source files. The two runtime-only Session consumers link only their matching runtime and options, without reference/query/report libraries. New consumers receive `-UNDEBUG`; sanitizer flags and the final sanitizer environment assignment cover the additions. No missing source, include directory, compile definition, or link dependency was established by inspection. The narrow direct writer compiles/relinks do not substitute for a fresh native build or prove static-archive extraction behavior; root's actual native links remain required evidence.

**Test retention and expected count.** The native CMake diff leaves every original `add_test` command intact. Independently extracted original literal names match the 99-name legacy inventory. The expected inventory and registration TSV match, and the expected names are unique. The added arithmetic is 8 individual capture/owner/collector/workload/scalar tests, 10 matched production/testing combined/report/runtime-only tests, and 14 FIFO/LIFO policy/replay/window executions: 32 additions, hence 131 expected total. Every new registration receives label `C01` and timeout 900.

The three altered legacy fixture sources preserve their original branches when `CROWN_STATISTICS_ACCEPTANCE` is absent. Their old targets keep that macro absent. Six additional production executables supply the enabled FIFO/LIFO selections; only the LIFO copies define `CROWN_STATISTICS_LIFO`. The original independent result/prefix/window oracles remain in place. Five delta selections plus replay/window per order are selected coverage, not the full policy Cartesian product. The historical generalized diagnostic and baseline generator are deliberately omitted from publication; their frozen evidence is preserved and the registered tests/baselines cover their intended facts.

**Portable source inputs and v2 provenance.** Native CMake and both checker paths contain no historical workspace or `/tmp` dependency. The existing clean-build copier includes `include`, `src`, `tests`, `tools`, and `schemas`; its `legacy` name exclusion does not exclude `tests/statistics/legacy-v2`. The two expected v2 JSON files are checked-in inputs, with these verified hashes:

| Baseline | SHA-256 |
| --- | --- |
| `legacy-runtime.json` | `24589b38bbf86a10b9c37cb6c166b387df1db5e671807f620b0e5569e628b25f` |
| `legacy-session.json` | `9c6ff1a4de6b04c5fc95a862465508445a959ff30938618cd2614dded1fc6eb2` |

Both match the original root output directory `/tmp/crown-c01-report-root-attempt-1-legacy-baseline/`. Root attempt 1 records the frozen control executable `b042e8c80a99bcea6e6242235ae913046107664d3fd6d333662dfbf20d67258f`, exit 0, and matching production/testing byte comparisons. The control used frozen combined runtime and original v2 report objects, rather than the v3 writer. Native tests consume the copied bytes, not that old binary. The publication-only author script's temporary borrowed objects are explicitly compilation evidence, not native build inputs.

**Wrapper and publication semantics.** The wrapper requires exactly the two permitted checksum entries, rejects duplicates/missing entries/hash mismatches, creates a fresh corpus, invokes the actual selected producer and unchanged checker with `check=True`, and forwards the testing variant explicitly. Failures inside production/checking propagate and retain that fresh corpus; successful completion deletes only that corpus. Baselines are neither rewritten nor regenerated. CTest supplies the matching target path and source root, and subprocesses use argument arrays.

The writer/schema diff removes only `c01_project_gate`; the schema remains closed, and the wrapper adds a negative check for reintroducing that field. The copied checker is byte-identical to the accepted predecessor checker. Typed byte/Decimal encoding, null/unknown and lower-bound handling, scalar tags, budget semantics, and legacy-v2 guards remain unchanged. Removing repository acceptance from runtime capabilities does not assert C01 completion. The new wrapper/publication bytes still need their root execution; predecessor report successes alone do not establish those results.

**Public claims and evidence.** The final guide distinguishes local state populations from transactional event counts; exact/sample/incomplete/lower-bound states; independent O07/C01 modes; interval identity; released/private/unread states; and state, workload-capacity, and export budgets. Runtime/report copying and allocator/peak-memory exclusions remain explicit. README/native-build text scopes O07's 99-test/five-configuration result to its already verified historical 691-entry seal. C01 native acceptance remains explicitly pending.

The guide's benchmark medians and component payloads agree with the accepted root record: six profiles, 5,000 prebuilt events, two warmups/nine measured repetitions, O07 off, and substantial observed collection costs. It states that the timer excludes initialization/configuration/export/output delivery and that the disabled candidate is not an engine built without C01. It makes no zero-overhead, production-performance, arrival-rate, total/peak-memory, S05, or cost-ranking claim. The accepted report strict and complete-sanitizer results are separately identified; the later publication and native matrix are not presented as already passed.

## Resolved draft observations and remaining limits

One concrete documentation defect was corrected before freeze: the lifecycle bullet had said dropped-session capture/snapshot methods uniformly return disengaged optionals. Final `overlay/docs/statistics.md:80` now names only `capture_statistics`, `capture_combined_statistics`, and `workload_statistics`; it correctly states that `snapshot()` throws `session_dropped`, while context/report capture returns retained metadata or a released report. An additional evidence-wording correction scopes inherited O07 seal language to its historical checkpoint. Both corrections are in the pinned final package; neither remains an open finding.

This review did not configure CMake or observe generated target commands, inspect symbols, run the new wrapper, or exercise cleanup failures. Actual generated test count/commands, production/testing symbols, archive boundaries, sanitizer execution, and source-only reconstruction remain root checks. The wrapper assumes the documented Python/jsonschema environment; its semantic checker uses Python assertions and was inspected under the ordinary, non-optimized interpreter contract. The two byte baselines are targeted compatibility evidence, not a replacement for the full legacy matrix. The prior report review's typed-transport, saturation-combination, and lifecycle coverage limits remain relevant; registration does not expand those assertions automatically.

The source map excludes ledger/handoff/acceptance edits and historical manifests. Root's immediate old-seal validation, pre-edit backup, native application, new freeze, complete matrix, and new source seal remain distinct steps. Their disclosed pending status is not a defect in this excluded registration package, and the no-blocker conclusion does not advance the C01 ledger state.
