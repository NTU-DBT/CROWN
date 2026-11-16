# V33 — bounded W06 acceptance and human usage specifications

W06 is verified within the documented bounded SQL/native/local-sink contract.
The original requirement audit found an integrated interruption coverage gap,
which the new test-only mixed self-join matrix closes. All **355 production
paths are byte-identical to V32**. This continuation adds no production owner,
catch, journal, wire field, allocation, work checkpoint or runtime dependency.

The full Refactor goal remains active: **57 verified / 1 in progress (A02) /
20 not started**, 78 total. A02 still blocks C04/B01. R2 history retirement,
V04 packaging and release gates remain open.

The implementation/evidence packet is
[`w06-acceptance-audit-v1`](../../build/verification/w06-acceptance-audit-v1/README.md).
The immutable boundary is `build/verification/human-inspection-v33-progress-v1.json`
with source under `build/verification/human-inspection-v33-source-v1`.
The exact preceding handoff is [V32 history](../handoff-history-v32-2026-11-13.md).

## Acceptance decision and its limits

The independent lane inspected the original four W06 artifact obligations,
four acceptance obligations and three contextual checks. Its
[eleven-row final audit](../../build/verification/w06-acceptance-independent-review-v1/acceptance-final-v1.md)
and [machine-readable decisions](../../build/verification/w06-acceptance-independent-review-v1/requirements-final-v1.json)
bind the exact receiving evidence to the final 1,196 native-input hashes.
No unresolved literal W06 gap or production design defect was identified.

| W06 obligation | Inspected behavior and evidence |
| --- | --- |
| Atomic replacement | One genuine native prepared token publishes the complete net source batch; a repeated K→K−1→K chain consolidates. |
| Aggregate consolidation | Private final group proposals combine signed contributions before checking final SUM; the sink receives complete before/final changes. |
| Checkpoint format | Complete nullable original source weights, genuine descriptor, C/I, source/reader progress and delivery anchor reconstruct the real runtime. |
| Arithmetic rollback | Contributing invalid int32 and final SUM overflow reproduce semantic Rejects while both visible and unused-source edits roll back. |
| Interrupted update recovery | Every injected survivor checks all known physical weights, exact typed results, W/I/C/D, progress, sink bytes, a new update and a final reopen. |
| Mixed-batch recovery | Both backends execute nullable two-alias self-join batches at the exact bigint count boundary, preserving invisible source rows. |
| Ancestor integrity | Existing native pending-epoch rollback controls, current healthy live-owner Reject checks and valid follow-up updates expose partial ancestor/group state. |
| Unambiguous deltas | Physical before/after uint64 weights, signed-magnitude bag changes and typed full-key group before/final rows keep zero, NULL and absence distinct. |

Actual child exits occur before/after observed persistence syscalls. The source
argument for RAM-only native preparation/publication is separate: private
preparation performs no persistent writes or delivery callbacks; death there
leaves the logged Input. Publication follows durable Commit, so death during
publication leaves Commit for replay. The tests do **not** kill after every
alias or RAM instruction. Existing direct in-memory allocation/annotation
controls supply separate rollback evidence. Generalized-factor invariants remain
prior W02/W03 dependency work, not a new proof from this two-alias fixture.

All selected R2 history remains retained from generation one under a durable
finite cap. No retirement operation is claimed or invoked. Retirement is
separate V04 work and is not substituted for the literal W06 acceptance clause.
No host power-loss, remote-sink, whole-current-suite, fresh Clang or CPU result
is inferred from this audit.

## Test design and actual receiving results

The new [native matrix](../../tests/unit/sql_aggregate_transaction_crash_test.cpp)
binds genuine original SQL with `COUNT(*)`, `COUNT(x::integer)`,
`SUM(x::integer)`, raw numeric `SUM(x)` and `AVG(x::integer)` over a nullable
self-join. One true left anchor joins itself and same-id right rows. Opposite
INT32_MAX contributions each have weight K=(INT64_MAX−3)/2, giving initial
COUNT(*)=INT64_MAX without physical expansion. Their final sums cancel exactly.

The mixed command replaces the NULL group key, changes a NULL weight, cancels
a same-key chain and changes unmatched/unused sources. Two separate Rejects
attempt a contributing invalid cast and removal of the balancing negative row;
each also attempts an unused-table edit that must roll back. Checkpoints start
at C1/generation 2, then C2/I4/generation 3 after Rejects. Recovery includes a
later erase Commit C3/I5 with missing final delivery and torn WAL/sink suffixes.
A small valid update after every outcome tests retained sufficient statistics
and new-new self-join contributions after group disappearance.

The preserved fault test and new matrix share the exact extracted fixed
[test observer](../../tests/support/sql_aggregate_session_probe.hpp).
The remaining preserved test bodies are unchanged. Production targets have
no observer field or callback. Only the two expected file-failure types are
caught by the new EIO test loop; unexpected errors fail directly.

| Current receiving profile | Selected CTests | Wall time | New matrix | Preserved matrix |
| --- | ---: | ---: | --- | --- |
| Strict GCC Debug | 2/2 pass | 173.46 s | 14 cases, 784 EIO, 156 process exits, 28 decoded tapes | 504 EIO, 118 exits, 8,502 covered C++ new cuts |
| ASan/UBSan/leaks | 2/2 pass | 386.48 s | 14 cases, 784 EIO, 156 process exits, 28 decoded tapes | 504 EIO, 118 exits, 8,502 covered C++ new cuts |

Per backend, each of log, Commit, cast Reject, SUM Reject and delivery has
8 EIO/4 process cuts; checkpoint has 115/34 and recovery 237/24. These are the
observed calls of this finite fixture, not all possible system states.
The receiving [summary](../../build/verification/w06-acceptance-audit-v1/receiving-acceptance-v1.json)
links raw Debug/SAN logs, retained tapes, input cohorts and exact limits.

The independent [Python decoder](../../tests/integration/sql_aggregate_transaction_crash.py)
checks framing, both hashes, identities, epoch order, command/generation and
manual typed group payloads for 28 healthy/probe tapes per profile. Every fault
outcome is compared byte-for-byte with manually specified canonical frames in
C++, then probed and reopened. Exported tape fields contain the expected bytes
only after exact actual-file equality assertions; Python does not independently
decode each injected fault outcome. Both retained artifacts hash to
`6939c70ced4704f48cd34ae407157e7a1c9e78756f7831e3dc4ab1e0358c4236`.

Both new/preserved targets compile with C++23, strict conversion warnings,
`-Werror` and `-UNDEBUG`; actual SAN compile/link flags and per-test failure
environment are checked. Production testing-OFF Release configure/build/install
pass. Debug/SAN each register 348 tests, preserving all 347 prior names,
properties and resolved commands; only `sql_aggregate_transaction_crashes` is
added. OFF registers zero tests.

The newly moved SDK has all 229 files byte-identical to V32, including every
archive/header/configuration file; its original prefix is absent. V32's actual
8/8 installed tests carry forward only by that identity; no SDK test is rerun
here. Likewise V32's 21 affected test names and four 123-case mature-SQL modes,
including 3,952 snapshots and 14,824 actual Session reopens per profile, remain
explicitly attributed to unchanged production/corpus source and prior receipts.
They are not newly executed V33 tests.

Thirteen recorder jobs contain eleven zero exits and two retained failures:
the first Debug/SAN build requests used trees not yet reconfigured for the new
target. Configuration and strict builds subsequently pass. Two whole input
cohorts cover 1,196 paths with zero in-command drift. The later cohort changes
only the test's healthy live-owner probe. A separate retained root-checker
correction fixes an overly uniform expected status string; no native failure
or requirement was suppressed.

## Human inspection coverage

The [source index](../code_specs/README.md) now partitions **751 files / 172,034
lines / 19,412 blocks**. There are **15,437 scoped usage contracts in 13,026
blocks**, 99 more than V32. Every maintained line has a structural location;
structural coverage is not a complete semantic specification. Selected
non-test callable/type regions have cards; **1,164 selected test regions remain**.
Other uncovered scaffolding retains structural facts only.

The new 40 root cards describe the test matrix, shared-helper extraction and
six CMake commands. Independent source review corrects four semantic-precision
fields and three spacing fields in a separately preserved amendment. Seven
probe cards move with unchanged helper definitions; two sanitizer anchors are
rekeyed. Root inspects the build/extraction delta before updating 1,465 old-source
cards and normalizes 311 affected line references to real files. Those reference
edits do not claim a fresh semantic review of every unchanged caller.

Another 59 cards cover runtime-memory, operator-report and public-tuple tests.
Independent review replaces 23 imprecise descriptions, including report versus
live-account values, retained epoch versus facade lifetime, handle copies,
comparison/counter work and unchecked temporary-file writes. The original author
payload and correction packet stay immutable. Documentation lanes execute no
native tests and cannot establish performance or test execution by card presence.

Generation completes before checking. Hash/anchor checks pass with zero stale
or unused cards; **116,731 generated local links** pass. A separate current-guide
audit checks local destinations/fragments and skips external URLs. Paper
references remain mapped in [code_review.md](../code_review.md); native memory,
SQL, rollback and durability costs remain local engineering contracts.

Root implements and receives the tests. One independent inherited-model agent
audits acceptance and new cards; Luna Max handles bounded packaging and memory
authoring, with a separate memory-card reviewer. No Astra is invoked here.
Recursive packet membership and seal hashes are checked before adoption.

## Continuation

Continue individual test usage review without adding runtime instrumentation.
The full goal stays active and the ledger does not claim V01/V02 or a release.
Preserve the existing R2 reader/logged-W/pending-head/spool rules. Completed
packets, SDKs and frozen sources are immutable; use fresh amendments. Revalidate
the saved boundary on entry. Reusable Debug/SAN/OFF builds are separate from
immutable evidence, and no native edits may overlap recorder commands.
