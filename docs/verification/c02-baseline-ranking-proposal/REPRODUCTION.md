# Root-owned reproduction and acceptance boundaries

Run from the repository root. The author may compile and link the excluded
proposal, but must not execute produced binaries, Python checkers, CMake, CTest,
symbol probes or benchmarks. The following execution commands are for root.

## Direct compile/link recipe

`compile-closure.sh` accepts a configuration, isolated output directory, optional
stage and optional repository root. It never runs an executable it produces.
Use a new output directory rather than overwriting a pinned prior attempt.

```sh
bash docs/verification/c02-baseline-ranking-proposal/compile-closure.sh strict /tmp/crown-c02-baseline-root-strict all
bash docs/verification/c02-baseline-ranking-proposal/compile-closure.sh sanitize /tmp/crown-c02-baseline-root-sanitize all
bash docs/verification/c02-baseline-ranking-proposal/compile-normalized-fault.sh strict /tmp/crown-c02-baseline-root-normalized-strict /tmp/crown-c02-baseline-root-strict
bash docs/verification/c02-baseline-ranking-proposal/compile-normalized-fault.sh sanitize /tmp/crown-c02-baseline-root-normalized-sanitize /tmp/crown-c02-baseline-root-sanitize
```

The optional independent stages are `core`, `sql_plan`, `ranking_reference`,
`runtime`, `runtime_testing`, `tests`, then dependent `link`. Compilation stages
can be scheduled separately; link only after all finish. No CMake configure or
network dependency fetch is involved. The required parser C archives/headers
must already exist at the matching pinned native build locations; this recipe
does not build or substitute them.

The strict command uses C++23, `-O2 -g -UNDEBUG`, all six warning/error flags,
and pthread. Sanitizer adds `-O1 -fsanitize=address,undefined
-fno-omit-frame-pointer` to every project TU and link, and uses the matching
sanitized parser C archive. Production and CROWN_RUNTIME_TESTING runtimes are
separate. The overlay public include root precedes native include; the sole
Json include root is overlay/third_party. No native third_party C++ fallback is
needed or accepted for this closure.

Each object has an exact `.command`, `.log`, `.exit`, full compiler dependency
`.d`, and source/definition/output `.input.tsv`. Completed final commands also
record source/header before/after hashes. Archives record their exact commands
and member lists. Links record their exact commands/logs. Manifest files use
repository-relative inputs or explicitly absolute isolated artifact paths, as
stated in `BUILD_RESULTS.md`.

## Execution gates

With `out` set to an isolated completed strict directory, root can run:

```sh
"$out/executables/ranking_binding_test"
"$out/executables/ranking_pure_link_test"
"$out/executables/ranking_contract_test"
"$out/executables/ranking_empty_test"
"$out/executables/ranking_payload_time_test"
"$out/executables/ranking_census_test"
"$out/executables/ranking_exception_test"
"$out/executables/candidates_test" /home/userroot/Codex/CROWN/tests/candidates
"$out/executables/candidates_exception_test"
python3 tools/verify_candidate_reports.py "$out/executables/candidates_io_test" /home/userroot/Codex/CROWN
```

The last existing checker launches the IO consumer with `--emit`, validates
native candidate reports and schema/authority mutations, and denies network
resolution. Merely running the producer does not replace that gate. The same
consumer set needs execution with the matching sanitized closure and the
root's established ASan/UBSan environment. Root should guard input identities
before and after execution and retain each command, exit, stdout/stderr and
elapsed time. Do not describe a launch/session as a terminal pass.

## Authored coverage

| Consumer | Material independent expectation |
| --- | --- |
| `ranking_binding_test` | Exact frozen-v2 bytes across scalar/name/constraint/statistic fields, NUL/high bytes; exact/one-under key/payload and residual prefix admission |
| `ranking_pure_link_test` | Real finite P06/P07 typed proof/family and height ranking with no runtime/report archive |
| `ranking_contract_test` | Literal R/S/T scores 195/105/190 over W=100, memory 24/32/32; all terms, sampling/detail truncation independence, current/as-of/reset/pending/foreign distinctions, explicit fallback/resource separation |
| `ranking_empty_test` | Nullary 4, unary Boolean 14, empty source 0, constant true/false height-zero 0; native source limits versus C02 processing limits |
| `ranking_payload_time_test` | Three separately retained normalized SQL source payloads, exact/one-under complete payload ceilings, 38-digit Decimal/repeated output data, capture-to-rank time carry |
| `ranking_census_test` | Eleven isolated collector health/saturation boundaries, exact maximum-root denominator and >64-bit depth score pipeline, actual Delta owner saturation/state separation |
| `ranking_exception_test` | Persistent allocation faults through capture and all three policies; complete actual owner/workload preservation, prior results/snapshot/proof/terms, retry, original P07 binding allocation profile |
| `ranking_normalized_exception_test` | Supplemental real normalized SQL binding/replay/identity path under persistent faults, literal slot/depth scores, complete owner/workload/result preservation and retry |

The census maximum-root score is an explicitly private standalone boundary
injection, not UINT64_MAX actual updates on a runtime. The separate actual-owner
saturation hook jointly saturates its report fields; isolated classifier cases
are the evidence distinguishing individual saturation reasons. JSON cleanup-only
allocation failures may recover; a recovered operation must still publish the
same complete result. A failed operation must publish nothing.

The three inherited P07 consumers are unmodified native sources, rebuilt with
the shared encoder and patched Json dependency. Their broad existing oracle,
serialization and persistent-fault sweeps remain required, rather than being
replaced by the small C02 fixtures.

Independent public/arithmetic tests and independent header-only JSON cleanup
probes are separate root-coordinated packets. This packet neither edits nor
executes them. A later native integration still needs clean registration,
cross-compiler/debug/sanitizer matrix and publication review. The scoped C01
engine benchmark is not a C02 ranking benchmark or an overhead guarantee for
the repaired exceptional JSON path.
