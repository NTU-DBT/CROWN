# C01 statistics guide — combined-header compile revision

Documentation-only, excluded preparation. **O07 is verified; C01 remains `not_started` and excluded from native sources, builds, and report/schema integration.** This new package revises the frozen guide proposal at `docs/verification/c01-statistics-guide-proposal/`; it does not edit that package. The frozen base package manifest digest is `f085d4b6035c468b5810264623819e27a402ded8f6ce7a34233073458828f904`; its original input pins are preserved verbatim here as historical evidence.

## Reconciliation

The guide is reconciled to the frozen combined proposal overlay, manifest digest `cb0ecb64935f80bf4915aa069de1bf01bcf1ea2f22a591f6f7408d405fcf4cfe`. It now describes the actual `CombinedCapture` and `capture_combined_statistics` API while keeping state-capture and workload-observation status, budgets, and intervals distinct. The combined overlay remains excluded preparation: native C01 methods, compatible EXPLAIN/report integration, schemas, and native engine overhead remain unfinished.

The active `input-pins.sha256` records current API headers, project headers used by the snippets, current O07 documentation, and root evidence. `historical-input-pins.sha256` is the old guide's original input manifest; its earlier O07 documentation hashes are historical and are not presented as current. The old guide's original files and `package.sha256` remain unchanged.

## Snippet compile results

Both exact guide snippets were extracted into distinct `/tmp/crown-c01-guide-revision-*` translation units. Each compiled in both production and `CROWN_RUNTIME_TESTING` preprocessing variants with C++23, the six project warning flags as errors, assertions enabled, and `-O3`. The combined proposal overlay include path precedes the native include path; `-isystem third_party` supplies the transitive JSON header that was missing from the previous frozen guide's compile attempt.

All four commands use `-c` only and succeeded with exit code 0. They produced object and dependency files only; no object was linked or run. `compile-evidence.md` records each exact command, empty compiler log hash, source hash, dependency-list hash, object hash, and the combined public-header pins. No test, checker, CMake, CTest, or `nm` command was run.

## Source and publication boundary

The candidate guide lives at `overlay/docs/statistics.md`. It uses the current C01 combined overlay API, but remains a review artifact. Root will reconcile it before any native documentation/API publication. Current O07 v2 EXPLAIN and schemas still do not contain C01 fields. The component benchmark figures remain scoped synthetic replay measurements, not engine throughput or query latency.
