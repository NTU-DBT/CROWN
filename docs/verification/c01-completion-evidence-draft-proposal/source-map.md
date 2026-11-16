# Source map for the C01 evidence draft

Exact input hashes are in `input-pins.sha256`. Earlier isolated root packets
often say C01 is `not_started`; those statements describe the pre-integration
slice named by each packet. The four terminal rows come from immutable
configuration summaries; pending SAN status comes from the byte-for-byte
`matrix-status-as-read-2026-11-07.json` snapshot. Root authority and matrix audit
attempt 2 define the separate partial evidence-audit status.

| Evidence area | Inputs | Use in draft and limits |
| --- | --- | --- |
| Requirement/contract | `Refactor.md` §11.8 C01–C03; `docs/statistics.md` | C01 acceptance requires exact small-data agreement, measured collection overhead/memory, and explicit unknown/stale facts. Current guide states local populations, collection modes, report semantics, and component exclusions. |
| Pre-integration registration | `c01-statistics-native-registration-independent-review-2026-11-07.md`, native registration `PACKAGE_SHA256SUMS`, `source-files.sha256`, `c01-native-integration-preflight-2026-11-07.md` | Independent source review found no blocker but reserved actual build/test acceptance to root. These files describe the reviewed application candidate, not completion. |
| Native application record | `build/verification/c01-native-integration-start.json`, `build/verification/c01-statistics-native-publication-root-attempt-1.json` | Guarded application records the historical O07 baseline and source map. Publication staging passed before application; that scope does not replace the final native matrix. |
| Current frozen matrix | `build/verification/statistics-execution-freeze.json`; `build/verification/statistics-debug-summary.json`, `build/verification/statistics-release-summary.json`, `build/verification/statistics-clang-summary.json`, `build/verification/statistics-clean-source-summary.json`; in-package `matrix-status-as-read-2026-11-07.json` | Freeze binds 623 native and 676 execution inputs, 131 expected tests, and 195 compile-command entries. Four summaries show terminal passes. The byte-for-byte jobs snapshot records the sanitizer active at draft time; root must refresh that mutable status before publication. |
| Current preliminary source audit | `build/verification/statistics-source-preliminary-audit-attempt-3.json` | Reports zero errors, but remains preliminary; full matrix acceptance and final metadata transition are pending. It is not the final source audit. |
| Independent matrix evidence audit | `build/verification/statistics-matrix-evidence-audit-attempt-1.json`, `build/verification/statistics-matrix-audit-launch-preflight-attempt-1.json`, `build/verification/statistics-matrix-evidence-audit-attempt-2.json`, `build/verification/statistics-matrix-audit-authority.json`, `docs/verification/c01-matrix-audit-trace-revision-proposal/PACKAGE_SHA256SUMS` | Attempt 1 and its launch preflight remain historical failures. Root accepts the revised auditor for this evidence; attempt 2 audited the four completed configurations with 1,047 observed numeric rows each, 195 compile entries, all six archive roles, cross-configuration checks, zero errors, and zero allocation differences. Attempt 2 still has `accepted_matrix_evidence: false` because sanitizer and semantic-symbol gates are pending. |
| Owner capture and fixture geometry | `c01-statistics-capture-root-results-2026-11-07.md`, `c01-statistics-owner-root-results-2026-11-07.md`, `c01-statistics-owner-generalized-revision-proposal/PACKAGE_SHA256SUMS`, `c01-statistics-owner-root-attempt-2.json` | Records exact selected source/native/S/P/E/index populations, shared limits, owner-versus-storage freshness, and the generalized C* geometry correction. These are predecessor slice results, not the full native matrix. |
| Collector and independent literal oracle | `c01-statistics-collection-root-results-2026-11-07.md`, `c01-statistics-literal-reference-root-results-2026-11-07.md`, their root JSON attempts | Records census/event sampling, truncation/abort/no-op semantics, saturation, fixed collector warning correction, 25 literal scopes and 18 replayed inputs. |
| Online/combined C01 review | `c01-statistics-online-root-results-2026-11-07.md`, `c01-statistics-combined-root-results-2026-11-07.md`, `c01-combined-independent-review-2026-11-07.md` | Records transactional publication and combined owner/workload checks. Independent review is a no-blocker source review with explicit fixture/sweep coverage limits, not matrix acceptance. |
| Policy/scalar/report evidence | `c01-statistics-policy-root-results-2026-11-07.md`, `c01-statistics-scalar-root-results-2026-11-07.md`, `c01-statistics-report-root-results-2026-11-07.md`, `c01-statistics-report-independent-review-2026-11-07.md` | Records selected FIFO/LIFO/window cases, typed scalar/constraint cases, v3 report/schema and targeted legacy-v2 checks. Reviews do not replace root execution and list transport, lifecycle, and saturation coverage limits. |
| Component and native engine measurements | `c01-statistics-benchmark-root-results-2026-11-07.md`, `c01-statistics-native-benchmark-root-results-2026-11-07.md`, component/native benchmark package manifests, `c01-statistics-native-benchmark-oracle-revision-proposal/package.sha256`, `c01-statistics-native-benchmark-metadata-revision-proposal/package.sha256`, preserved root attempts and raw JSON | Supplies scoped synthetic timings, substantial collection costs, component-capacity accounting, raw/run evidence, and preserved oracle/preflight failures. Neither is full workload/production prediction or S05 evidence. |
| Mutable publication context | `docs/native_build.md`, `docs/handoff.md` | Read-only context at authoring time, not pinned as a timeless input. `native_build.md` retains preparation-era wording; root must re-read and reconcile both during the final metadata transition. This packet edits neither file. |

Every root-results document is linked from `completion-evidence-draft.md` or
summarized here. Historical package claims remain scoped to their own test
variant, fixture, and root attempt. Four matrix rows come from the immutable
configuration summaries; test/input inventory comes from the freeze; SAN's
as-of state comes only from the preserved jobs snapshot. Isolated proposal
execution tables do not supply native matrix rows.

Before moving the evidence body to `docs/verification/statistics-2026-11-07.md`,
root must change its repository-link prefix from `../../../` to `../../`.
