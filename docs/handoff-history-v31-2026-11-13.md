# CROWN continuation handoff

The full Refactor.md goal remains active. The [ledger](task_ledger.md) remains
**56 verified / 2 in progress (A02/W06) / 20 not started**, 78 total. A02 blocks
C04/B01. Full W06 and release acceptance remain open.

Latest [V31 inspection](verification/human-inspection-v31-2026-11-13.md):
`build/verification/human-inspection-v31-progress-v1.json`, source snapshot
`build/verification/human-inspection-v31-source-v1`, implementation packet
`build/verification/w06-r2-jsonl-cli-implementation-v1`.
The exact previous handoff is [V30 history](handoff-history-v30-2026-11-13.md).

## New operational path

The separate [R2 JSONL/CLI guide](sql_aggregate_input.md) documents
`crown aggregate {create|run|status|snapshot|checkpoint}`. Creation uses actual
original SQL/catalog admission and a checked minimum source tree, or the
contradiction shortcut's existing constant-empty route. Later commands recover
the genuine selected descriptor/Session. Input records bind the actual SQL
identity and physical table schema version; full nullable rows use explicit
unsigned before/after weights. The structural schema supplements runtime checks.

Run delivers an existing spool even at zero decisions, resolves a WAL-owned
pending Input before reading the next line, then resumes from logged W and its
reader continuation. Reject advances I/reader while C/D stay. A report failure
after delivery does not authorize relogging the command. CLI JSONL requires one
saved reader record per W. The caller preserves the consumed input prefix;
offset checks do not rehash it. A consumed unterminated final record is terminal
for later CLI appends, including an LF added afterward.

The reader owns accounted flat TEXT/cell/edit buffers and freezes genuine
metadata into the receiving account. Its failure latch needs no catch/retry
wrapper. The decoded command ends before native preparation; the reader retains
bounded raw-line capacity. Ordinary DOM/lexer/compiler/stream/report workspace
stays separate. Six short fixed-failure translations live only at the CLI
presentation boundary. Existing Session's three catch boundaries are unchanged.

All 350 existing production paths other than main.cpp remain byte-identical to
V30 (351 predecessor production paths total). main adds only the aggregate
include/help/dispatch lines. All 20 non-recovery archives, including the pinned
parser, and all previous public headers match the prior SDK exactly. No ordinary
source/native/group field or handler is introduced. Transport still has DOM,
two-pass scalar, table-lookup, canonical encode and native costs; no CPU timing
or single-tuple delay claim is made.

## Executed scope

Affected Debug 15/15 passed in 120.36s and full selected ASan/UBSan/leaks 15/15 in
394.93s, including the existing set CLI workflow, process boundary, EXPLAIN and
Session fault sweep. The final Python-only unterminated-continuation extension
and packaging/schema additions passed current Debug 2/2 in 3.66s and SAN 2/2 in
30.36s. Production C++ is identical across these gates.

The current 229-file relocated Release SDK passes 4/4 in 3.19s: full existing
public Session unit, reader unit, standalone header and actual installed CLI.
The original prefix is absent. A separate installed-CLI gate checks five source
shapes on both backends (10 cases/20 commands): no-FROM, typed NULL/no-FROM,
contradiction, self-join and two-table join. It verifies independent DuckDB
snapshots, actual sink frames and checkpoints after every command. This extra
shape gate is Release evidence, not a Debug/SAN execution claim.

Each main CLI profile covers 11 ordered commands per backend plus two distinct
signed-bigint SUM-overflow/retry commands. It verifies native Rejects, pending
Input/Commit resume, actual sink bytes, report-failure resume, tail barriers and
strict transport refusal. DuckDB 1.5.4 is required. The allocation fixture reaches
144 covered C++ new refusals: 141 propagate, three complete via existing JSON
DOM-destruction fallback; all restore the receiving account. Exact peak 13,151
bytes passes and one below refuses. This is not malloc/DOM/RSS accounting.

All 345 previous registrations/properties are preserved; 347 registered, OFF zero.
Actual strict flags are checked in 14 records. There are 40 recorder jobs, 35 zero
exits including four diagnostic GDB commands; all five initial build/test failures
are retained. GDB zero exits are not receiving-test passes. Current native inputs
1,193 = seven additions / three changes versus V30. Original recorded keys have
no in-command mutation; no global no-additions claim is inferred from that check.
No full 347-test, current Clang, CPU benchmark, whole W06 or release claim.

## Human inspection and remaining work

The [source map](code_specs/README.md) has 15,206 contracts over 748 maintained
files, 171,238 lines and 19,341 blocks; 12,795 blocks carry scoped contracts.
V31 adds 152 cards, including 72 existing epoch/view/transport test cards and
38 reader/test cards. Root supplies 42 CLI/build/declaration cards and exact
source-delta updates; a fresh cost amendment preserves the original author
packet. All selected non-test regions have cards; **1,347 selected existing-test
regions remain**. Structural maps/card presence do not prove semantics.

Root implemented and verified. Luna Max handled two bounded usage-card tasks;
a normal-model lane independently reviewed lifecycle/ownership/limits and found
seven corrected code/documentation issues. No Astra invocation was needed.
Review packets/private builds are immutable after completion.

Next: exact varying-int32 aggregate admission and the complete W06 acceptance
audit. Preserve logical int32 arithmetic and genuine kernel binding; do not
silently widen SUM or alter the native scalar enum just to pass tests. Current
composition rejects varying int32 at its synthetic-kernel type boundary.
R2 history retirement remains separate, with history currently bounded from one.
Continue the 1,347 existing-test usage reviews. See root next-implementation.md.

Concurrent B01/B05 draft scripts/report/outputs retain V30's separate provenance
capture and known overwrite/missing-result/fixed-conclusion limitations. This
Session/CLI cohort did not execute or accept them. A02 still blocks B01/C04.

No maintained native edits during recorder jobs. No overlapping build/CTest/
enumeration in one build directory; archive terminal LastTest before the next
native action. Main Debug/SAN/OFF builds are reusable. Completed packets, SDKs,
private builds and snapshots are immutable; use fresh amendments for corrections.
Do not rerun old live-source postchecks after authorized edits. Generate maps to
completion before checking. Never stage/reset/commit Git. Exec commands require
sandbox escalation here. Revalidate the saved state at the next entry.
