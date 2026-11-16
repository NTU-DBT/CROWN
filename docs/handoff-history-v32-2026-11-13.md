# CROWN continuation handoff

The full Refactor.md goal remains active: **56 verified / 2 in progress
(A02/W06) / 20 not started**, 78 total. A02 blocks C04/B01. Full W06 and release
acceptance remain open.

Latest [V32 inspection](verification/human-inspection-v32-2026-11-13.md):
`build/verification/human-inspection-v32-progress-v1.json`, source snapshot
`build/verification/human-inspection-v32-source-v1`, implementation packet
`build/verification/w06-varying-int32-implementation-v1`.
The exact previous handoff is [V31 history](handoff-history-v31-2026-11-13.md).

## Implemented varying integer arguments

`SUM(x::integer)`, nested narrow-then-widen casts, COUNT and AVG now bind through
actual original-SQL/source/kernel factories. Physical inputs and raw GROUP BY
remain bigint; only expression type/result policy changes. The prior handoff's
physical_type(int32) diagnosis was incomplete: composition projects raw leaves
and preserves casts in kernel SQL. AggregateCompiler::argument was the ordinary
narrowing admission boundary. Do not alter the native scalar enum or synthetic
physical schema to encode these expressions.

One immutable sorted distinct guard vector records original columns before
measure dedup/final type replacement. Shared projection checks non-NULL int32
range before group mutation, including COUNT and inner casts widened back to
bigint. NULL passes; filtered/unmatched/net-zero changes may produce no fact.
Existing private proposals/native token own rollback. SUM(integer) checks its
final bigint sum; raw/widened SUM stays numeric; AVG keeps a wide numerator.
Foreign freeze copies guards and genuine descriptor rebind derives them again.
Future conditional expressions/aggregate FILTER need a fresh evaluation review.

Only three of 355 production paths change (header/compiler/shared helper); both
mutable runtime owner files remain byte-identical. No new catch, per-row/group/
operator field, journal or wire-format field is introduced. Immutable Data adds
56 accounted payload/requested bytes in the installed Release legacy probe,
even without guards; nonempty backing costs extra. U guards spend U checkpoints
per projected row/fact, including NULL. Old programs retain an accessor/empty-loop
cost. No CPU, malloc/RSS or portable ABI claim follows.

## Executed scope

All 21 affected test names have passing evidence in Debug and ASan/UBSan/leaks.
The initial 21-test command passed 17 and rejected four oracle modes at a missing
join-separator fixture. Its Python-only correction then passed all four modes:
Debug 1,074.57s, SAN 1,768.39s. Initial commands were 129.13s/369.22s and remain
failed receipts; C++ is identical across these stages. The complete production
OFF Release build passes. A 229-file moved SDK passes 8/8 in 4.21s: current header,
six full public unit consumers and actual installed CLI; original prefix absent.
Nineteen of 21 archives (including recovery/parser) match V31; aggregate and
composed aggregate runtime change. Only aggregate.hpp changes among headers.

Each final DuckDB 1.5.4 mode covers 123 original-SQL cases on both backends:
246 native cases, 3,952 snapshots and 3,706 atomic epochs. Twenty-four new cases
cover varying integer arguments, including all 19 AVG scales. Direct, physical
rebuild, checkpoint and durable Session modes pass. Session additionally checks
14,824 actual cold reopens and 3,952 checkpoints per profile, with independent
actual sink-frame decoding. Exact local AVG scale uses SQL SUM/COUNT plus
Fraction rounding; metadata follows the documented local result-type policy.

New C++ controls include genuine signed compressed cancellation beyond individual
bigint contributions, final overflow rollback, COUNT/nesting, NULL and inclusive
bounds, filtered/join activation, exact/one-under guard work, freeze allocation
cuts, wide AVG-only numerator, pending Reject/source-reader progress, complete
source checkpoints and false-Reject barriers before torn-tail repair. Existing
Session fault, CLI, descriptor, checkpoint/record and input tests also pass.

Actual old/new installed Release controls preserve allocation counts, selected
work and exact legacy binding images over four profiles/sixteen updates, with
COUNT/SUM/empty snapshot checks. Program/Epoch/Metrics remain 16/160/72 bytes.
All 347 names/properties and previously resolved commands are preserved; OFF 0.
The early broader builds resolve 59/40 formerly unbuilt Debug/SAN commands; other
unbuilt tests remain. There are 25 strict flag records. No full 347, current Clang,
CPU benchmark, complete W06 or release claim.

There are 27 recorder jobs, 21 zero exits and six retained failures: two interrupted
broad builds, two test-only compile failures and two initial oracle commands.
The six interrupted target outputs were rebuilt. Three exact source cohorts
cover 1,193 native paths, nine changed versus V31; every recorded command has zero
in-command drift. Root documentation-checker corrections are retained separately.
Use receiving-acceptance-v1, input-cohorts-v1, registration-comparison-v2,
coverage-final-v3, code-specs-final-v2 and legacy-cost-comparison-v1 in the packet.

## Human inspection and next work

The [source map](code_specs/README.md) now has 15,338 contracts over 748 files,
171,588 lines and 19,357 blocks; 12,927 blocks carry scoped contracts. V32 adds 132
cards: eight root feature cards, 63 API-test cards and 61 cursor/initialization-test
cards. Separate sealed amendments replace six/ten imprecise author cards without
changing author evidence. Those documentation lanes execute no tests. Root
rechecks changed-source cards, two signatures and exact reference deltas. All
selected non-test regions have cards; **1,223 existing-test regions remain**.
Structural coverage/card presence is not a semantic proof or blanket comment
certification. Generated hash/anchor checks and 115,783 local links pass.

Root implemented/verified; Luna Max handled two bounded author tasks and one
inherited-model lane reviewed design and both card sets. No Astra invocation.
Next: the full original W06 requirement audit, then any missing acceptance case,
while continuing remaining test usage reviews. R2 history retirement stays a
separate protocol, currently bounded from generation one. See next-implementation.md.

The [R2 input guide](sql_aggregate_input.md) remains the operational authority:
drain existing spool first, dispose a WAL pending Input before reading more, use
logged W/reader continuation, and preserve consumed source prefixes. Reject moves
I/source/reader without C/D; report failure never authorizes relogging. CLI uses
one reader record per W. A consumed unterminated final record is terminal even
if an LF is later appended. Ordinary DOM/compiler/stream workspace is separate.

No maintained native edits during recorder jobs; no overlapping build/CTest/
enumeration in one build directory. Archive terminal LastTest first. Main
Debug/SAN/OFF builds are reusable; completed private builds/SDKs, packets and
snapshots are immutable. Fresh amendments only. Do not rerun old live-source
checkers after authorized edits. Finish generation before checking maps; read
unused_manual_overrides directly. Never stage/reset/commit Git. exec_command
requires sandbox escalation here. Revalidate the saved boundary on next entry.

Concurrent B01/B05 draft scripts/report/outputs retain prior provenance and known
output/report limitations; this cohort did not execute or accept them. A02 still
blocks B01/C04; the full 78-card implementation goal remains active.
