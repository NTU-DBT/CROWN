# CROWN continuation handoff

The full Refactor.md goal remains active: **57 verified / 1 in progress (A02) /
20 not started**, 78 total. W06 stays verified within the documented bounded
SQL/native/local-sink profile. A02 still blocks C04/B01; R2 history retirement,
V04 packaging and full release gates remain open.

Latest [V35 inspection](verification/human-inspection-v35-2026-11-13.md):
`build/verification/human-inspection-v35-progress-v1.json`, frozen source
`build/verification/human-inspection-v35-source-v1`, main packet
`build/verification/inspection-selection-tests-v35-v1`.
The exact preceding handoff is [V34 history](handoff-history-v34-2026-11-13.md).

## Current source and usage boundary

The [source index](code_specs/README.md) has 15,778 contracts
in 13,362 blocks across 751 files / 172,040
lines / 19,412 blocks. V35 fills all 181 actual selected gaps in seven
selection/ranking/candidate/fast-path test files. All selected non-test regions
have scoped cards; **831 selected test regions remain**. Unreviewed scaffolding
has structural facts only. Every maintained line is mapped, which does not
certify all semantics or all comments.

All 1,196 native input paths, including all 355 production paths, tests/fixtures,
CMake/install definitions and offline tools, equal V34 exactly. No engine code,
handler, wrapper, allocation or work checkpoint changes. V35 executes no native
build/CTest/SDK/timing job. The six precise aggregate-role labels and 110 tool
cards from V34 retain their source binding to tools/code_specs_support.py SHA
`cc31de0ea2d2b3e667c07d834ac781e9925aac982f712b5fd11274b368d9254f`.

Three original author packets (72 selection/result, 46 ranking-oracle, 63 planner)
and their three independent reviewer packets remain immutable. Root reads all
seven sources and relevant callers, checks all recursive seals and actual
missing-region sets (including mains), replays before/after field amendments,
and adopts a single plain 181-card result. See adoption-final-v1,
review-seal-pins-final-v1, coverage-final-v1, code-specs-final-v1,
native-source-comparison-final-v1 and receiving-acceptance-v2 in the main packet.
Private receiver schema corrections and root's removed query-acyclicity wording
are recorded separately; no native failure follows. Root handles complex review;
three Luna Max agents do bounded authorship/cross-review. No Astra is used.

Key reviewed distinctions: publication uses <=11 sampled allocation positions
and no direct current-byte assertion; selection persistent calls 2N+2 on fresh
fixtures, ranking calls 2N+3 on one retained fixture; caps call D+2*pins+3 excluding
setup. The 288 lifetime cases do not expand fault/cap cache coverage; selection caps use
bypass. Allocator equality differs from equal current-byte totals. Six native
grant refusals are not successful initialization; one aggregate IndexWork grant
has five dimensions. Ranking height-only skips evidence capture, selection does
not. Candidate complete sets include original exact seed plus normal forms;
cached residual provenance survives new original-proof binding. Work deltas,
modeled slots and zero scan metrics do not bound all CPU/copy/heap/RSS work.

The integer oracle has 54 unique lexical decimal strings/2,916 ordered pairs and
155 maximum digits, independent expected arithmetic but production operand
construction. boundaries=16 labels 32-bit checkpoints. Three invocations establish
an exact work boundary. Diagnostic string arguments can allocate on passing
assertions. Tree fingerprints assume finite acyclic trees; query incidence may
be cyclic. Partial progress assertions and outer exception catches have exact
limited scope. These are source observations, not new test runs or paper proofs.

## Preserved native acceptance

V33 executed Debug and ASan/UBSan/leaks: each passed the preserved Session fault
test and new interrupted mixed nullable self-join matrix. New matrix per profile:
14 backend/action cases, 784 EIO cuts, 156 real process exits, 28 independently
decoded healthy/probe tapes; old matrix separately 504 EIO/118 exits/8,502 covered
new cuts. Survivors check source weights, exact typed output, W/I/C/D, progress,
sink bytes, a valid next update and another reopen. Process cuts surround actual
persistence syscalls; RAM-stage death equivalence is source-derived. No host
power-loss or kill-after-every-alias claim.

V33 OFF Release configure/build/install passed; Debug/SAN registered 348 tests,
OFF 0; prior 347 names/properties/resolved commands stayed intact. Moved SDK 229 files
match the actually tested V32 SDK, with no V33 SDK test rerun. V32 retains 21
affected names and four 123-case mature SQL modes: 3,952 snapshots/3,706 epochs per
mode, 14,824 actual Session reopens/3,952 checkpoints per profile. Keep their dated
receipts; none are V35 executions. No whole-current 348, fresh Clang, CPU or
release certification follows.

Preserve V32 immutable sorted original-column int32 guards and physical bigint
schema. Final expression type decides SUM policy; COUNT and narrow-then-widen
keep guards, NULL passes, filtered/unmatched/net-zero facts may not project.
Prior installed evidence accounts fixed Data+56 bytes and U guard checkpoints
per projected row/fact. Conditional/FILTER syntax needs fresh evaluation-scope
review.

## Continuation and evidence rules

The [R2 input guide](sql_aggregate_input.md) is operational authority: drain spool
first, resolve pending WAL Input before reading more, resume logged W/reader
position. Reject advances I/source/reader without C/D; report failure never
permits relogging. A consumed unterminated record remains terminal if LF is
later appended. Retained R2 history starts at generation one under its durable
finite cap; reopening cannot refill it. Retirement/V04 remains separate work.

Revalidate the latest sealed boundary on entry. Never rewrite completed packets,
private builds/SDKs or snapshots; use fresh amendments. V34 restored its rewritten
peer validator to exact seal 373454d9 and preserved changed 20e8 state under a fresh
amendment at cabd2243; V35 protects both. Do not rerun old live-source validators
after authorized registry edits and then modify their evidence to pass.

No native edits during recorder jobs; no overlapping build/CTest/enumeration in
one build directory. Archive terminal LastTest before another native action.
Main Debug/SAN/OFF builds are reusable. Finish map generation before checking;
read unused_manual_overrides directly. Never stage/reset/commit. exec_command
requires sandbox escalation in this environment. Continue individual review
without runtime instrumentation growth. Concurrent B01/B05 drafts remain
unaccepted. This continuation completes neither all comments nor the full goal.
