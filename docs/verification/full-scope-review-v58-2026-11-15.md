# Full-scope correctness review — V58

The current implementation review is complete within the scope below. All 362
existing checks pass in both Debug and ASan/UBSan. Review and independent oracle
comparisons found two defects in the new experimental aggregate adapter; both
are corrected. The complete Refactor implementation goal remains active, and
B04 controlled experiments and release acceptance remain open.

The [receiving packet](../../build/verification/full-scope-review-v58-v1/README.md)
retains source bindings, raw commands/logs, JUnit results, failed preimages and
terminal receipts. The [handoff](../handoff.md) identifies the remaining work.

## Source coverage

The review closes all **433 primary paths**: 431 production, tool, example and
CMake code paths, plus two build/provenance JSON inputs. These include all 370
production files. Another 363 test-code files are inventoried, documented and
exercised through the registered checks; this is not a claim that every test
body received a new manual read. Fixtures and schemas have separate bindings.

| Area | Complete source review |
| --- | --- |
| SQL, catalog, IR and planner | Workhorse read of all 97 files / 18,388 lines. [Coverage and report](../../build/verification/v58-frontend-planner-source-review-v1/REVIEW.md). |
| Runtime and observability | Workhorse read of all 82 files / 18,965 lines. [Review](../../build/verification/v58-runtime-source-review-v1/review.md). |
| Resource, storage and version | Root read of 54 files / 8,492 lines and independent read of the remaining 15 public headers / 1,388 lines: 69 complete files. [Root argument](../../build/verification/v58-root-storage-resource-review-v1/review.md), [header review](../../build/verification/v58-storage-header-review-v1/README.md). |
| Input and recovery | Workhorse read of all 113 files / 13,298 lines, including commit, WAL, replay, retirement and public boundaries. [Review](../../build/verification/v58-io-recovery-source-review-v1/review.md). |
| Tools, CLI and packaging | 72 files / 12,793 lines: 66 freshly read and six received from exact independent complete reads. Nine application paths overlap the production inventory. [Review](../../build/verification/v58-tooling-source-review-v1/REVIEW.md). |
| Independent successor monitor | One Astra Max review read all eleven production successors since V54 and six new B04 files: 17 files / 4,239 lines. [Report](../../build/verification/v58-independent-correctness-monitor-v1/review.md). |

The [predecessor closure](../../build/verification/v58-full-source-closure-v1/manifest-v1.json)
joins these exact source spans with no missing or unread primary path. Subsequent
receiving covers exactly five source successors: two offline inventory tools,
two comment-only storage headers and the corrected aggregate adapter. The
earlier monitor's COUNT-source reasoning was insufficient: complete input
grouping alone does not identify external column positions. The counterexample
and compiler-mapping argument below supersede that specific claim; the old
packet is preserved.

The [code and exact-paper map](../code_review.md),
[independent arguments](../independent_review.md) and each block's seven-field
usage card remain the route from implementation to paper or local design.
The maintained maps now contain **794 files / 180,992 lines / 20,190 regions**,
with **19,670 authored cards covering all 17,226 nonblank regions**. The remaining
2,964 regions are blank spacing. Final checking resolves 143,145 local links
with no error. Scala helpers have structural source cards, not a claimed Scala
method parser. Exact bindings establish inspectability, not correctness alone.

## Confirmed corrections

The new aggregate adapter passed its empty default physical-options object to
a strict versioned DTO reader. Its advertised default request consequently
failed with `missing field schema_version` before runtime construction. Exactly
an omitted or empty object now selects `PhysicalOptions{}`; nonempty objects and
other JSON types retain strict validation. Actual omitted/default equivalence
and malformed-options controls pass. The failed run and preimage are retained.

The optional compressed COUNT-source path also assumed source-output positions
matched aggregate-kernel positions. For
`SELECT src,dst,COUNT(*) FROM graph GROUP BY src,src,dst`, inserting `(1,2)`
produced the wrong key and values: the ordinary result is key `[1,2]`, values
`[1,2,1]`; the old adapter returned key `[1,1,2,1,2]`, values `[1,1,1]`.
SQL grouping deduplicates repeated columns, so the coordinate spaces differ.

Verification now builds the canonical group key through
`SqlAggregateInput::source_output` and `kernel.group_columns()`, then obtains
projected group fields through the compiled field mapping. The existing
complete-input-grouping and COUNT(*) guards remain. This is a verification-only
mapping change; the measurement branch is unchanged. It adds no retained row
ledger, production hook or exception framework. The
[mapping argument](../../build/verification/v58-b04-adapter-spec-proposal-v3/mapping-argument-v1.md)
records the compiler premises and handling of repeated, reordered and
constraint-collapsed columns.

Two public indexed-cursor comments now state exact work-grant identity and
invalidation on every rollback, including an empty rollback. Removing comment
lines yields exactly the predecessor code bytes. Both offline specification
tools explicitly include `tools/support/ComponentReplay.scala`; a regression
also confirms unrelated Scala remains excluded and a missing helper map rejects.

## Executed validation

All 1,239 pre-existing native/test/schema/build inputs matched V57 while the
full suites ran. Each profile passed its 361-check main suite and separately
passed `clean_source_snapshot`, covering all 362 registrations. Terminal
[Debug](../../build/verification/full-scope-review-v58-v1/debug-tests-v1.json)
and [sanitizer](../../build/verification/full-scope-review-v58-v1/sanitizer-tests-v1.json)
records report exit zero and no changed baseline input. The later two header
comment edits and two offline tool successors are received separately. Existing
Release libraries and isolated new adapter/exporter builds also pass.

- The final COUNT-source correction passes **48 actual native commands / 336
  prefix comparisons**, including 24 ASan/UBSan commands. Independent SQLite
  comparisons check canonical keys and values for duplicate grouping, reordered
  grouping, repeated outputs, COUNT-only output, equality collapse and constant
  collapse across both backends and ordinary/compressed sources.
- Scaled receiving covers six cohorts, **32 configurations / 1,952 passing
  prefix comparisons**, plus a 30-prefix duplicate-group regression. Its
  [final report](../../build/verification/v58-b04-scaled-preflight-v1/FINAL-REPORT.md)
  preserves the initial receiver mistakes, genuine defect and corrected reruns.
- Ten initial native/legacy wrapper cases compare 199 prefixes with SQLite.
  Legacy C++ cardinality and absolute group replacements retain their actual
  semantics; Scala performs a real full iterator drain after every input.
  The final correction checks above supersede the early source-only key gap.
- All nine exported minimum candidates replay their bound training trace through
  the existing independent delta/full-snapshot collector. Taller ordinary
  controls are produced, but their new V3 consumer is not implemented yet.
- Ten negative adapter controls and three provenance controls reject malformed
  requests, unsupported modes, exhausted limits and changed calibration
  context/phase/digest. Eight verify/measure controls repeat three fresh logical
  passes with matching results/counts and discarded measurement payloads.
- The actual planner/calibration/statistics pipeline and six initial native
  aggregate oracle cases pass ASan/UBSan. Frozen observations reproduce fitted
  coefficients and C02 choices across four statistics variants. The smoke fit
  has rank six over eleven features and establishes no predictive accuracy.
- All 91 new cards are adopted. Ninety-four existing cards are rebound to exact
  successor hashes, with six semantic amendments. Generation and the actual
  specification/link checker pass.

The unmodified legacy C++ archives and Scala runtime are outside the native
sanitizer claim. Concurrent smoke clocks are ineligible for controlled
performance comparisons. JVM/JIT/allocator state persists across logical passes;
framework parsing and formatting costs remain included where actually charged.
Memory, account bytes, setup, service/output/release and teardown have distinct
scopes. Small exact-integer cohorts imply no general floating-point guarantee.

## Remaining scope

No further concrete defect was found in the reviewed current core. This is
finite execution evidence and conditional source reasoning, not an exhaustive
formal proof. External parser/JSON/ABI, owner lifetime and filesystem assumptions
remain stated in the existing contracts.

B04 still requires the complete [ten-axis matrix](../../build/verification/v58-b04-design-review-v1/README.md),
V3 upper-only artifact consumption, offline selection receiving, set/session
adapters and matched batch/output/recovery experiments. C05 event-cost
installation remains unsupported; C03 forecasts here are offline data.
Approximation, shared-query algorithms and parallel/distributed engine execution
remain deferred. Queries remain independent. The ledger stays at 63 verified,
two in progress and 13 not started, with the implementation and release gates
open. Licensing review remains deferred while rights/notices are preserved.
