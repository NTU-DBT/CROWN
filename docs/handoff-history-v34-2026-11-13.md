# CROWN continuation handoff

The full Refactor.md goal remains active: **57 verified / 1 in progress (A02) /
20 not started**, 78 total. W06 stays verified in its documented bounded
SQL/native/local-sink profile. A02 still blocks C04/B01; R2 history retirement,
V04 packaging and full release gates remain open.

Latest [V34 inspection](verification/human-inspection-v34-2026-11-13.md):
`build/verification/human-inspection-v34-progress-v1.json`, frozen source
`build/verification/human-inspection-v34-source-v1`, main packet
`build/verification/inspection-memory-tests-v34-v1`.
The exact previous handoff is [V33 history](handoff-history-v33-2026-11-13.md).

## Current documentation boundary

The [source index](code_specs/README.md) has 15,597 scoped contracts across
751 files, 172,040 lines and 19,412 blocks; 13,181 blocks carry cards. V34 adds
160: 154 test-block cards and six aggregate-role data cards. All selected
non-test regions have cards; **1,012 selected test regions remain**. Other
scaffolding retains structural facts only. Every maintained line has a mapped
location; this is not complete semantic review or blanket comment certification.

The three author packets contain 152 cards: memory 48, physical 54 and support 50.
Root keeps the two useful support aliases and adds two omitted main cards, so
154 test blocks are adopted and all 152 intended selected gaps in these six
files are filled. Root independently reviews memory cards (22 fields/16 cards);
peer physical/support reviews amend 51/58 fields, respectively. Root additionally
corrects the two support cost fields to one aggregate IndexWork grant with five
dimensions. Original authors, peer proposals and receiving fixes are preserved.

Only tools/code_specs_support.py changes among 1,196 native-input paths:
six exact aggregate labels replace misleading inherited descriptions. Existing
78 labels and all non-ROLES AST nodes stay identical. The generator performs
both exact-path and eager fallback-stem lookups. Its labels convey no proof or
runtime authority. All 110 tool cards bind final source SHA
`cc31de0ea2d2b3e667c07d834ac781e9925aac982f712b5fd11274b368d9254f`.
All 355 production paths, every test/fixture and build/install definition equal
V33. No new native build/CTest/SDK run or CPU measurement occurs in V34.

Reviewed costs include nine/eleven linked allocation-list scans for owner
statistics, one/two allocations for copied trace/gauge arrays versus shared
report/evidence handles, correct cap-calibration/setup counts and actual DTO
versus compiled binding coverage. Diagnostic string arguments can allocate even
on successful checks taking const std::string&. The fixed generator counts are
source-derived input simulations, not native test execution. copied_* and
native_record_visits are selected metrics; they do not count all affected-state
copies, bucket/handle work or process CPU/RSS. Snapshots can own fresh account-
backed tuples; journal tuple pins persist with the last epoch/journal owner.

One peer rewrote its sealed validator after handing it over. The
original is restored at seal `373454d93dbeac5db83d7757d6cb6df24513866ecfd8cdb8e643e439b206e2f6`;
all 13 payloads match. Its complete changed 20e8 state is retained inside
`inspection-support-contract-review-v34-amendment1/changed-state`, with amendment
seal `cabd2243bbee4683b8a38239353d85a33ae5191d0dcb7fa4750178cedde8ff0b`.
Both trees and nested seals are independently checked. Never rewrite a completed
packet to make a live-source validator tolerate later authorized edits.

Use adoption-final-v1, review-seal-pins-final-v1, native-source-comparison-final-v1,
coverage-final-v1, code-specs-final-v1 and receiving-acceptance-v1 in the main
packet. Root-checker/schema/geometry corrections remain separately recorded.
Root handles complex review; three Luna Max agents handle bounded author/peer
tasks. No Astra used here. The next 72-card selection/ranking author packet is sealed under
`inspection-selection-tests-human-contracts-v35-v1`, SHA
`b1ad14cd70318ffdddb2dfbdcc0b7680daed98c680e864d58d124595e90858ec`.
It is outside V34 adoption and needs independent receiving review before use.

## Preserved native acceptance

V33 executed Debug and ASan/UBSan/leaks: each passed the preserved Session fault
test and new interrupted mixed nullable self-join matrix. New matrix per profile:
14 backend/action cases, 784 EIO cuts, 156 real process exits and 28 independently
decoded healthy/probe tapes; old matrix separately 504 EIO/118 exits/8,502 covered
new cuts. Every new injected survivor checks source weights, exact typed output,
W/I/C/D, progress, sink bytes, a valid next update and another reopen. Actual
process cuts surround observed persistence syscalls; RAM-stage equivalence is
source-derived. No host power loss or exits after each alias instruction are claimed.

V33 production OFF Release configure/build/install passed; Debug/SAN registered
348 tests and OFF 0. Prior 347 names/properties/resolved commands were preserved.
The moved SDK's 229 files match the actually tested V32 SDK exactly; V33 did not
rerun SDK tests. V32 retains its 21 affected names and four 123-case mature-SQL
modes: 3,952 snapshots/3,706 epochs per mode, 14,824 actual Session reopens/3,952
checkpoints per profile. These are dated preserved receipts, not V34 executions.
No whole-current-348, fresh Clang, CPU or release claim follows.

Keep the V32 narrowing design: immutable sorted distinct original-column int32
guards; physical bigint schema stays unchanged; final expression type decides
SUM policy. COUNT and narrow-then-widen retain guards; NULL passes and filtered/
unmatched/net-zero facts may not project. Program fixed Data cost +56 accounted
bytes and U selected guard checkpoints per projected row/fact remain prior
installed evidence, not a new timing claim. Conditional/FILTER syntax needs a
fresh evaluation-scope review.

## Continuation rules

The [R2 input guide](sql_aggregate_input.md) is operational authority: drain
spool first, dispose an existing WAL Input before reading more, resume from
logged W/reader position. Reject advances I/source/reader without C/D; report
failure never authorizes relogging. A consumed unterminated record stays terminal
if LF is later appended. All selected R2 history remains from generation one
under its durable finite cap; reopening cannot refill it.

Continue individual usage review without runtime wrapper/instrumentation growth.
No native edits during recorder jobs; no overlapping build/CTest/enumeration
within a build directory. Archive terminal LastTest before another native action.
Main Debug/SAN/OFF builds are reusable; completed packets, private builds/SDKs
and snapshots are immutable. Use fresh amendments and revalidate the saved
boundary on entry. Do not rerun old live-source checkers after authorized edits.
Finish map generation before checking; read unused_manual_overrides directly.
Never stage/reset/commit Git. exec_command needs sandbox escalation here.

Concurrent B01/B05 drafts keep their prior unaccepted provenance and limitations.
A02 and the remaining extension/experiment/release work stay open. V34 does not
complete all comments, all tests or the full implementation goal.
