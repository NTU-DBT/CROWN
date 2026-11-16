# CROWN continuation handoff

The full Refactor.md goal remains active: **57 verified / 1 in progress (A02) /
20 not started**, 78 total. **W06 is verified within the documented bounded
SQL/native/local-sink profile.** A02 still blocks C04/B01. R2 history retirement,
V04 packaging and full release gates remain open.

Latest [V33 inspection](verification/human-inspection-v33-2026-11-13.md):
`build/verification/human-inspection-v33-progress-v1.json`, source snapshot
`build/verification/human-inspection-v33-source-v1`, main packet
`build/verification/w06-acceptance-audit-v1`.
The exact previous handoff is [V32 history](handoff-history-v32-2026-11-13.md).

## Current result and acceptance

The original W06 audit found missing integrated interrupted mixed/self-join
coverage. The new test-only matrix closes that gap on both existing backends
with nullable COUNT/SUM/AVG, checked varying integer arguments, compressed
COUNT exactly INT64_MAX and opposite signed contributions that cancel only in
the final batch. Mixed commands replace the group key, chain one physical row
net-zero and retain unmatched/unused sources. Distinct cast/final-SUM Rejects
also attempt unused-source edits, which must roll back.

All 355 production source/header paths are byte-identical to V32. No production
owner, catch, journal, hook field, work checkpoint or allocation is added. The
old test observer is extracted exactly into tests/support; remaining preserved
fault-test bodies are unchanged. New observer use is confined to testing
libraries. Expected EIO loop catches two concrete file-failure types only.

The independent eleven-row audit is in
`build/verification/w06-acceptance-independent-review-v1/acceptance-final-v1.md`
and requirements-final-v1.json. Its seal-v1.json SHA is
`9a557ad253810cd151b1a51ef64db2d92c6306d82cfc0a372ce8e288052a321d`.
Actual child exits surround observed persistence syscalls. Recovery equivalence
during RAM-only private preparation/publication is a separately inspected
source-order argument, not a kill after each alias instruction. Existing
in-memory alias/ancestor rollback controls provide separate evidence.

No R2 history is retired: selected history starts at generation one under a
durable finite history_generations cap that reopening cannot refill. Retirement
is a separate V04 operation, not an unfulfilled literal W06 clause.

## Actual receiving scope

Debug and ASan/UBSan/leaks each pass two selected CTests:
sql_aggregate_session_faults and sql_aggregate_transaction_crashes. Debug wall
time is 173.46s; SAN 386.48s. Each new matrix covers 14 backend/action cases,
784 EIO cuts, 156 real process exits and 28 independently decoded healthy/probe
tapes. The preserved matrix separately covers 504 EIO, 118 process and 8,502
covered C++ new cuts. Every new injected survivor checks all known original
source weights, exact typed group state, W/I/C/D, source/reader progress, sink
bytes, a valid next update and another cold reopen. Healthy controls probe
live owners before their first reopen so recovery cannot hide a Reject defect.

The Python decoder checks the healthy/probe tapes. Every injected repaired
outcome is compared byte-for-byte against manual canonical frames in C++,
then probed/reopened; Python does not decode every injected outcome separately.
Exported expected tape bytes follow exact equality assertions with the real
sink. Debug/SAN tape SHA is
`6939c70ced4704f48cd34ae407157e7a1c9e78756f7831e3dc4ab1e0358c4236`.

Production testing-OFF strict Release configure/build/install pass; OFF has
zero tests. Debug/SAN have 348 registrations, retaining all 347 previous names,
properties and resolved commands, with only the new crash test added. Actual
C++23 strict conversion warnings, Werror, assertions and SAN compile/link/test
environment are checked. No whole-current-348, fresh Clang, CPU or power-loss
claim is made.

The newly moved SDK's 229 files are byte-identical to V32, original prefix
absent. Prior V32 installed 8/8 tests carry forward only by identity; no new SDK
test execution. Likewise V32's 21 affected names and four 123-case mature-SQL
modes retain their exact prior attribution: 3,952 snapshots/3,706 epochs per
mode and 14,824 Session reopens/3,952 checkpoints per profile. These are not
fresh V33 executions.

The packaging packet is
`build/verification/w06-acceptance-packaging-v1`; packet-manifest-v1.json SHA
`bb0bb2485739cd04e40e41305f73603dbbc19c02a044ee4d970717640e8ed6e9`.
All recursive payloads and exact SDK identity are checked by root.

Thirteen recorder jobs have eleven zero exits and two retained failures: initial
Debug/SAN target builds preceded reconfiguration and had no rule for the new
target. Reconfiguration and strict builds pass. Two exact source cohorts cover
1,196 native inputs with zero in-command drift; the later cohort strengthens
only the healthy live-owner test. Native delta versus V32: new C++ test, Python
wrapper and shared test helper, plus CMake wiring and old-helper extraction.
A retained root-checker amendment corrects an assumed uniform status string.
Use receiving-acceptance-v1, input-cohorts-v1, review-seal-pins-final-v1,
coverage-final-v2 and code-specs-final-v2 in the main packet.

## Human inspection and remaining work

The [source map](code_specs/README.md) has 15,437 contracts across 751 files,
172,034 lines and 19,412 blocks; 13,026 blocks carry scoped cards. V33 adds 99:
40 root test/build cards and 59 runtime-memory/operator-report/public-tuple test
cards. Independent review corrects four root semantic-precision fields and
three spacing fields; a separate memory amendment replaces 23 descriptions.
Original author evidence remains. Root rechecks changed-source cards, moves
seven helper anchors and rekeys two sanitizer anchors. Hash/anchor checks and
116,731 generated local links pass with zero stale/unused cards.

All selected non-test regions have cards; **1,164 selected existing-test regions
remain**, and other scaffolding retains structural facts only. Card presence is
not complete semantic proof or test execution. Continue this inspection with
purpose, inputs/outputs, invariants, ownership, failure and cost kept explicit;
avoid adding instrumentation or wrapper frameworks to production primitives.
Root handles complex work, Luna Max handles bounded author/packaging tasks,
and independent inherited-model agents review evidence/cards. No Astra used.

V32's narrowing design remains: immutable sorted distinct original-column
int32 guards, physical bigint schema unchanged, final expression type decides
SUM policy. Inner narrow-then-widen guards and COUNT survive dedup. NULL passes;
filtered/unmatched/net-zero facts may never project. No new mutable runtime state.
Installed Release legacy evidence reports fixed Data +56 accounted/requested
bytes, same covered allocation counts/selected work/binding bytes; U guards add
U selected checkpoints per projected row/fact. This is not a CPU/RSS/ABI claim.
Future conditional/FILTER syntax needs a fresh evaluation-scope review.

The [R2 input guide](sql_aggregate_input.md) remains operational authority:
drain existing spool, dispose the WAL pending Input before reading more, and
resume from logged W/reader continuation. Reject advances I/source/reader,
not C/D. Report failure never authorizes relogging. A consumed unterminated
record remains terminal even if LF is appended later. Compiler/DOM/stream
workspace has separate host scope.

## Workspace discipline

No maintained native edits during recorder jobs and no overlapping build/CTest/
enumeration in one build directory. Archive terminal LastTest before the next
native action. Main Debug/SAN/OFF builds are reusable; completed private builds,
SDKs, packets and snapshots are immutable. Use fresh amendments and never rerun
old live-source checkers after authorized changes. Finish generation before
checking maps; read unused_manual_overrides directly. Never stage/reset/commit
Git. exec_command needs sandbox escalation in this environment. Revalidate the
saved boundary on entry before edits.

Concurrent B01/B05 drafts retain their prior unaccepted provenance and known
output/report limitations. A02 licensing/distribution, remaining extensions,
experiments and release gates remain open. The full implementation goal remains
active; V33 does not complete all comments, all tests or the release.
