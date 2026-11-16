# Full-scope source review and component experiments — V60

The current implemented source has a complete review lineage across all **446
primary paths**: 444 production/tool/example/build-code files and two configuration
inputs. All **370 production files** match the reviewed V59 bytes. This round
reviews three changed code paths and ten new code paths, corrects experiment
receiver defects, and completes three controlled studies. The full Refactor
implementation goal remains active; B04 and release acceptance remain open.

Use the [inspection index](../code_specs/README.md), [paper/code guide](../code_review.md)
and [experiment guide](../component_evaluation.md) for human examination. The
[handoff](../handoff.md) records continuation state.

## Exact source and review scope

The [inventory](../../build/verification/v60-full-source-closure-v1/source-inventory.json)
contains **817 code/configuration paths**: 446 primary paths and 371 test-code
paths. Relative to V59, 804 are unchanged, three changed, ten are new, and none
are missing. Test code has source-bound usage cards and execution evidence;
this does not claim a fresh complete manual read of every old test body.

The [V58 full-source review](full-scope-review-v58-2026-11-15.md) supplies the
complete production arguments and both 362-check Debug/ASan+UBSan runs. Its two
later comment successors are already received in
[V59](component-evaluation-v59-2026-11-15.md). V60 retains those production bytes;
repeating the full unchanged engine suite supplies no new source coverage.

| Current successor | Review and independent evidence |
| --- | --- |
| Main CMake, Session client and SQL-row client | Root exact-diff read and [adopted source-bound contracts](../../build/verification/v60-root-usage-v1/adoption-v2.json). The changes add a private search diagnostic, four test registrations, explicit experimental wait/memory observations and actual selected-tree reporting. |
| Operational runner and regression | Complete workhorse source read; [21 usage cards and terminal evidence](../../build/verification/v60-operational-evaluation-v1/manifest-v1.json). |
| Literal-search client, runner and regression | Complete workhorse read of 741 lines; [34 cards, closed protocol proposals and actual reference controls](../../build/verification/v60-literal-search-evaluation-v1/manifest-v1.json). |
| Exact cohort/oracle helper and regression | Independent Luna read, eight pure tests and [28 current source-bound cards](../../build/verification/v60-cohort-oracle-review-v2/manifest.json). |
| Matched runner, SQLite control and regression | Root implementation and independent workhorse read of all 494 lines; [13 cards and resolved findings](../../build/verification/v60-baseline-review-v1/manifest-v1.json). |

All **19,932 adopted usage contracts** cover every **17,485 nonblank region**
across **815 code files /185,544 lines /20,540 regions**. The 3,055 blank regions
retain structural descriptions. Receiving adds 108 cards, rebinds 1,550 old cards
after exact inspection, amends six runtime scopes and moves 19 numeric references
with their unchanged source text. The canonical checker passes **145,117 local
links** with zero errors. Bindings establish inspectability; correctness also
depends on the source arguments and actual independent checks above.

## Findings and corrections

The original aggregate experiment requested `SUM(r1.c1)` grouped by `r0.c0` over
`r0(a,b) JOIN r1(b,c)`. Its required source head contains the disconnected
endpoints `{a,c}` and has no admitted free-connex tree. Both native profiles
correctly rejected it before timing. The retained failed attempts are evidence
of that rejection. The current experiment uses `SUM/AVG(r0.c1)`; its source head
is r0's native scope, and changing hidden r1 multiplicity still changes exact
COUNT/SUM/AVG while projected set membership survives.

The Scala result receiver initially extracted four named fields while ignoring
other text. It now matches the entire published four-pair payload and rejects
extra fields, duplicate names and trailing garbage. Fixed-query admission also
locks physical column order and requires one transaction and observation per
physical input. Expected Scala class/JAR/Java bytes join to 477 parent-sealed
paths. Native DISTINCT cardinality uses genuine signed changes folded into one
scalar, matching the requested count-only demand.

An attempted cold-oracle memory reduction passed horizon-only records to a
checker that also needed output counts. Independent review caught that contract
mismatch before any accepted run of the attempted version. The final receiver
performs full independent native verification, freezes actual identity/count
obligations, releases the large oracle graph and validates measured passes
against those obligations. The matched parent receiver retains identity/count
metadata during timing after releasing its independent oracle rows.

The direct SQLite control now rejects Boolean/floating pass counters. The exact
full-head peak is **2w³+w**, including the transient zero-valued insert; its
fully loaded cardinality is 2w³. Empty/repeated width strata reject before arm
construction. These are tool/client corrections; production algorithms are
unchanged.

## Executed correctness checks

- Four new regressions pass in Release and ASan/UBSan configurations: exact
  cohort/oracle checks, operational evaluation, independent search evaluation,
  and matched evaluation. Native sanitizer runs use leak detection and halt on
  address/undefined-behavior errors; Python itself is outside that claim.
- Operational regressions check 32 arms and 24 contrasts per profile, plus 16
  supplemental signed-service controls: 580 primary and 320 supplemental prefix
  observations. All 48 gates precede the 32 diagnostic measured invocations.
  Corrupted observations, undeclared factors, a real late native budget failure
  and reuse of completed output paths reject as intended.
- Each search profile checks 43 genuine method/budget/reference controls and
  four serialized proof replays. Tiny normalized-family coverage, exact C02
  arithmetic, infeasibility, zero-work stops and request/CPU/output negatives pass.
- Final matched tests check nine native/SQLite arms, published text decoders,
  integer counters, physical column order, observation schedules, a real native
  budget failure and output exclusivity. An optional 12-arm preflight also
  qualifies the original Scala/C++ observers against the current scalar-fold
  and full-output contracts.
- Existing runtime regression passes **57 commands /280 SQLite prefix or common
  endpoint comparisons** in each main profile and each newly built standalone
  profile. Standalone clients compile under strict warnings against the frozen
  relocated SDKs; those SDKs remain unchanged.
- [Actual new-field receiving](../../build/verification/component-evaluation-v60-v1/runtime-fields-receiving-v1.json)
  checks 120 Session reports, 780 batch memory observations, 12 reconstructions,
  80 delayed measured epochs and 24 actual SQL-row tree reports across the two
  operational profiles.

Operational regression v2 executed helper preimage `5f614992…`; its operational
functions are unchanged in current helper `06b5f4b4…`. The successor changes
only the baseline DISTINCT-count mode and its comment. Current helper tests and
final matched checks pass, and the full controlled Release operational study
executes the current helper bytes. The retained receipts preserve this distinction.

## Controlled studies

All drivers run sequentially with other workers held and children pinned to
CPU0. Build, request, harness and launcher closures are checked. Correctness gates
precede timing; all three drivers terminate with exit zero and unchanged inputs.

| Study | Correctness gates | Retained timing invocations | Scope |
| --- | --- | --- | --- |
| [Operational](../../build/verification/component-evaluation-v60-v1/controlled-operational-v1/experiment.json) | 96 primary +48 signed-service | 288, each with one excluded fresh-owner warmup and one measured pass | Widths2/4/8; both storage backends; output, batching, recovery and exact annotation protocols; 72 declared contrasts. |
| [Matched implementations](../../build/verification/component-evaluation-v60-v1/controlled-matched-v1/experiment.json) | 36 | 108, each with one excluded fresh-owner warmup and one measured pass | Native backends, exact SQLite recomputation and qualified C++/Scala local observers on the same physical inputs and output demands; 36 contrasts. |
| [Independent search](../../build/verification/component-evaluation-v60-v1/controlled-search-v1/experiment.json) | 345 variants +8 tiny reference controls, plus23 serialized proof replays | 1,380 processes:345 warmups +1,035 measured | 23 queries, five methods and three work grants; 345 summaries retain actual stops and family/scoring availability. |

The operational study checks 17,632 primary and 9,728 supplemental prefix
observations across its verify passes; matched verification checks 14,304.
The runtime receiving also confirms 57 paired backend controls, including 15
equal exported-tree pairs. Set/Session reports bind their physical program
identity; their tree itself is not exported by those clients.

Search results preserve incomplete outcomes: five literal cases still stop at
one million work units, four optimized cases lack the original proof at 10,000,
and four meta families remain prefixes at one million. On the complete tiny C02
reference, a residual choice retains a **1/2 structural-score gap**; available
optimized/meta choices select the reference optimum. This is a finite depth
proxy comparison, with actual runtime census weights and separately charged
proof/admission/scoring phases.

Whole-implementation timings include plan/factorization, layout, scalar width,
parsing, formatting, allocation and JVM/JIT costs. SQLite includes Python and
full query recomputation. Synthetic consumer wait measures a retained service
boundary; recovery reconstructs a clean owner from real WAL/checkpoints. Requested
account samples and whole-child RSS have distinct scopes. V59's richer C03 study
retains its underdetermined fit and explicit fallbacks; C05 `maintenance_cost`
remains unsupported. Full ten-axis B04 attribution and release acceptance remain
open.

## Preserved measured bytes and continuation

The [archive receiving](../../build/verification/v60-controlled-build-archive-v1/receiving-v1.json)
preserves 789 mutable workspace inputs, seven native executables, 21 archives and
151 recorded C++ units in a 798-file frozen closure. Twenty project archives
match their 140 recorded member objects exactly; 11 direct units and 96 parser
C members remain distinguishable. It verifies 1,070 already immutable workspace
pins and 430 system pins separately. Dynamic-library and parser C compilation
provenance limits are explicit in that record.

The continuation authority is `build/verification/human-inspection-v60-progress-v1.json`
with its terminal post-seal check. Preserve old packets, frozen source copies,
SDKs and private prefixes. Main producer builds remain reusable. The ledger stays
**63 verified /2 in progress /13 not started**; approximation and parallel or
distributed execution remain deferred, with independent query maintenance as the
multi-query requirement. The [handoff](../handoff.md) identifies the next work.
