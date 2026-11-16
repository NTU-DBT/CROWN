# O07 EXPLAIN, metrics and traces — verified

**O07 is verified.** All five native configurations pass all 99 tests on one
frozen revision. The full 78-card goal remains active: 37 verified, two in
progress (A02/O06), 39 not started. No public release gate is claimed.

| Configuration | Tests | CTest seconds |
| --- | --- | ---: |
| GCC Debug | 99/99 | 1441.06 |
| GCC Release | 99/99 | 257.73 |
| ASan + UBSan + leak checking (sanitizer) | 99/99 | 5913.44 |
| Clang Debug | 99/99 | 1181.39 |
| Fresh source-only Release | 99/99 | 255.35 |

Native integration includes immutable physical/runtime/session/query reports,
the metrics registry and sampled causal trace, human/JSON/DOT/tree JSON exports,
four closed versioned schemas, and the native `crown explain` dispatcher.
Height evidence remains distinct from cost-search status. Current modes,
requested/resolved options, initialization/context, trace sampling, cursor
work/timing, gauges and unavailable components are explicitly represented.

Six new test executables and seven CTest cases preserve all original 92 names
and commands. Standalone preparation includes all 437 query inputs under both
policies against the independent literal oracle and genuine replay, 2,192 report
artifacts, 1,133 cursor checks, 74 composed artifacts, owner/clock/fault/lifetime
coverage, and the final CLI fixture corpus. These are supplemental to the full
native matrix, whose exact per-test results and raw logs are independently audited.

The final native 585 fingerprint is
`9ca9005001bda9e56faa0951077e53fc106450d7350bf185cd62556a7af25d0a`.
The complete execution 635 fingerprint is
`8ae45108daed5530d67372c93b46bb198bf694a5c8bf429cb6905d4b367bbf12`.
All five before/after maps match. The fresh source-only snapshot matches both
inventories, passes all tests and is removed after retained evidence collection.
Freeze: `build/verification/observability-execution-freeze.json`.

The independent [matrix review](observability-matrix-review-2026-11-07.md)
accepts exact 99-name results, all five terminal summaries, 178 structured
numeric rows in each in-place configuration, 157 raw CMake compile commands,
96 vendored parser C units, strict project warnings and separate production/
testing runtime closures. Thirteen historical allocation-only rows have explicit
metadata-layout deltas; the other 152 retain exact values. These inventories
have different meanings. Hidden Make recipes are not expanded executed argv.
The clean build retains the same GNUmake jobserver note and two upstream upb
maybe-uninitialized diagnostics as P07, matched by exact identities/counts and
pinned vendor inputs. They are not claimed fixed or harmless; unexpected or
project warnings still fail. Production archives exclude testing probes;
testing variants expose the expected hooks. Parser sanitizer references include
both ASan and UBSan. Raw evidence: `build/verification/observability-*`.

The [691-source current seal](observability-sources.sha256) has SHA-256
`f4acf6ea043859d350aa0dd2d56c86afca24535d7288eb5774f94b26ab0ea21e`. It contains the previous 592 path inventory plus 99 new paths,
with no removals. All nine historical manifest FILE identities and original
Refactor.md are preserved. Older entry checksums describe older source snapshots
and are not revalidated against current files. The independent final source
audit checks this seal, current links/schema references, integration boundaries,
all 78 ledger cards and accepted matrix artifact identities.

See [observability guide](../observability.md), [native build guide](../native_build.md)
and [AntiGravity handoff](../handoff.md). S05 total allocator bytes, O04/O05
recovery, O06 durable delivery, C01/C02 statistics/cost work, benchmarks and O08
public workflow/release remain open. DOT acceptance is lexical; Graphviz was
not installed or run. Source-position acknowledgement does not imply durability.

The [independent final source audit](../../build/verification/observability-source-evidence-audit.json)
accepts the current 691-source seal and metadata with zero errors and zero
pending checks. The final documented state is rechecked before the completion
checkpoint is recorded.
