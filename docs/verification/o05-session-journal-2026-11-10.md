# O05 prepared session journal writer — 10 November 2026

O05 remains in progress. Root implemented the writer integration. Luna Max
provided a bounded interface inventory, an eight-format stream fixture helper,
a bounded writer review and an independent partial-metadata fixture. No Astra
was used. All 1043 predecessor file-component paths were verified/preserved before
edits; full interim source1 has 1048 paths. Final tested source2 has 1051 paths.
See the [writer contract](../session-journal.md), [files](../journal-files.md) and
[records](../journal.md). Production native restore/replay remains unimplemented.

Final source2 selected 60/60 PASS in all four modes:
Debug 26.83s, Release 10.14s, Clang18 22.05s, ASan+UBSan/leaks 95.75s.
The current inventory has 247 names and retains all 244 predecessor names. These
60 are the predecessor 57 and three session writer tests, not whole247/fresh-source
acceptance. Strict flags/assertions/sanitizer/leak settings remain enabled;
accepted builds have no compiler diagnostics. Every terminal CTest stdout was
archived before later enumeration/builds.

The writer binds a new exclusive log to an exactly matching current durable
checkpoint. It captures logical input and full stream decoder continuation,
syncs before physical begin, records prepared physical/metadata decisions before
native publication/source acknowledgment/output, and covers the drain path.
File failures force recovery; predecision allocation failure can retry the same
cached input. Checkpoint-file replacement is blocked while attached; explicit
drop releases the lock and funded owner. Data uses the original native query
account; no ordinary Row graph or second allowance was introduced.

Native validation covers 12 query/backend combinations and 32 stream cases
(eight formats × two backends × baseline before/after first input), exact bytes/
records/header/permutation/source positions, both window FIFO policies and
partial metadata/physical watermark progress. Self-join fan-out/new-new values,
projection/Boolean/nullary results, maintenance/delta paths, metadata-only steps,
created/paused/stopped admission, invalid window semantic rejection before log,
paused drain and predecision allocation rollback/retry pass. Allocation is denied
immediately after successful decision fsync for physical, window metadata/first/
final physical and drain publication; all subsequent native publication passes.
Actual before/after syscall failures cover 16 physical input/decision cases and 32
window input/metadata/first/final watermark cases, retaining native/source/window
progress with output blocked and recovery required. Sixteen actual process exits
at input/decision calls check durable prefix and writer lock release. These exit
cases do not implement or prove a production native replay factory.

Two real integration failures were independently reproduced through unchanged
public control source linked only to production libraries. Both initially exit1:
explicit drop retained the journal lock; a non-final duplicate-label watermark
step was rejected because the codec required metadata completion. The negative
ELF, source1 snapshot, relevant native objects, exact compiler/link commands and
logs are preserved. After reset-on-drop and a contextual watermark metadata rule,
the same controls exit0. Native tests now keep duplicate labels through complete
expiration in both backends/FIFO policies, verifying two partial metadata steps
followed by the single physical deletion/source completion.

The codec correction preserves version1 wire bytes and all seven original golden
records. The previous bare-encoder metadata-incomplete negative becomes a strict
physical/stream prefix rejection; unknown kind remains a separate negative.
Incomplete insertion/withdrawal, changed physical/command/substep counters,
corruption and quotas still reject. A new independent 1311-byte four-frame stream
matches native encoding and all 1312 byte cut, incremental parity and exact/
one-under quotas pass. Its generator's first draft incorrectly used 16 decoded
query-id bytes instead of 32 ASCII hex; root's length check caught it. The v1 draft
is preserved; the corrected v2 checks its 624-byte header against the old golden
header. Maintained generation only normalizes paths/provenance; stream SHA is
3527114535de80780a7217545dbf44a8822f53c555116a772fc68d17af8cef6b.
The original fixture manifest's format-spec digest changes, not its seven frames.
Every other previous test/fixture/cap/timeout remains unchanged.

An initial helper indentation error was caught by strict compilation and fixed
without changing flags. Interim source1 selected 60/60 passes all four modes;
public controls exposed the two uncovered defects, so final source2 supersedes
it. The maintained tests now include those regressions. An all-green scoped
matrix alone was not treated as proof of complete recovery.

Audit binds 188 native executables,32 changed-unit objects,16 archives/four caches
and408 compiler/link records, plus the production-only negative/positive controls.
Root and Luna reviews, complete frozen sources/negative objects, independent
fixture provenance, actual commands, logs, all terminal jobs and final readback
are under build/verification/o05-session-journal-. Final docs-only source3 adds
two guides and updates ledger/handoff/contracts. O04 and the earlier file component
remain historical acceptance on their respective frozen source snapshots.

Next implement production single-account reconstruction/replay from the exact
checkpoint through committed physical/window substeps. Stage pending native
input, advance source positions/decoder bytes/records/CSV mapping before attaching
post-replay continuation, validate actual native transitions against decisions,
and expose no tentative recovery output. Preserve partial watermark commands.
Select a durable compatible checkpoint/generation pair before retiring history;
add audited stable output identity/O06 delivery and every integrated persistence
boundary, then whole/fresh acceptance. Full goal stays active: 43 verified,
3 in progress(A02/O05/O06),32 not started,78 total.
