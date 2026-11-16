# O06 native local epoch sink — 10 November 2026

This goal turn is progress. Root implemented and reviewed production changes;
Luna Max supplied a bounded helper inventory/read-only review and independent
wire bytes. No Astra was used. The full Refactor.md goal stays active. The ledger
remains43 verified/3 in progress(A02/O05/O06)/32 not started,78 total. Work remains
uncommitted on baseline `e369a623517723b3be3ea3e9806779f3c591e7f9`.

## Accepted component

The [native local sink](../local-sink.md) persists complete canonical signed
physical epochs, including empty closures, under query/sink/native/schema/
generation identity. Native output stays owned until file sync; immutable opaque
receipts come only from a validated synced prefix. Whole-byte canonical retries
exclude ordinal/iteration/layout address. Prefix validation, no-follow regular
files, exclusive flock, bounded original-account storage and explicit torn repair
extend the maintained file pattern.

QuerySession attachment blocks further source peeking while delivery is pending;
typed queues remain bounded. Direct transfer/discard cannot bypass delivery.
Recovery compares earlier persisted epochs before deduplication, then publishes
missing output. Stop/drop leave WAL/native output reconstructible. Completion
after successful sink sync is allocation-free. A local file receipt is not an
arbitrary external side-effect acknowledgment or automatic retirement authority.

The current two-step recovery retains the native replay buffer before opening
the sink. Configured replay row/byte/work/heap caps must cover the selected log.
Caller output frontiers or partial consumption cannot substitute for real sink
coverage. A sink-aware restore path that avoids retaining acknowledged history,
durable old-pair retirement and full/fresh integrated acceptance remain open.

## Native evidence

Frozen source1 contains1082 paths: all1070 predecessor paths retained plus12 new
implementation/header/support/test/fixture paths. Existing changes are limited
to CMakeLists.txt,delta.hpp,session.hpp,delta.cpp,session.cpp. All predecessor tests,
fixtures,caps,timeouts and accepted flag records are unchanged. The convenience
would-block diagnostic now also describes pending durable delivery.

Final selected69/69 tests pass in all four modes: Debug 73.51s, Release 51.92s, Clang18 89.3s, ASan+UBSan/leaks 143.23s. All253 predecessor
names remain among256 registered names. This is component regression acceptance,
not whole256/fresh O04–O06 acceptance. Historical predecessor acceptance remains
bound to its original source snapshot.

Each mode verifies24 typed query/backend/restart cases,32 eight-format stream/
backend/pending cases and16 partial-window/backend/FIFO prefixes. Persisted rows
match the independent definition, including self-join fan-out, SQL predicates/
EXISTS, nullary and maintenance/empty output. Tests check native state/source,
retained input, decoder seek/next input, semantic replay identity, exact duplicate
and generation rotation. All five scalar kinds, embedded NUL/UTF8/date/decimal,
owning reader lifetime and independent265-byte epoch serialization pass.

The independent Python struct/hashlib/datetime frame has SHA256
`6c89a8446a9accaa0530cd9967b49676d1aa744b341dcd24becdfcdf5352b235`.
Its148-byte protected header/117-byte body match the actual production epoch
frame byte-for-byte; maintained copies match all independent artifact bytes.

All381 epoch-tail cuts,656 initial-header cuts,1036 byte flips, checksum-valid
semantic/schema/sequence corruption and63 available checksum-prefix negatives
pass. Compatible incomplete tails repair to the exact complete prefix; complete
or detectable corruption never repairs. Exact/one-under cumulative file bytes,
codec work and copied session delivery work pass, including work retained across
reopen. Symlinks/exclusive ownership, slow bounded queues/caller ownership,
private fan-out barriers and pause/cancel/stop/drop recovery pass.

Five delivery allocation faults preserve complete native output and the old file
for retry; global allocation denial after sync proves acknowledgment does not
allocate. Actual create/deliver/open/read/repair have11/4/16/3/20 syscall boundaries.
All108 injected before/after errors and108 process exits reopen through the
actual native session/sink, verify state/source/output/dedup and the next update.
Short3-byte transfers and repeated EINTR respect finite I/O caps. Process exits
are not power-loss simulation.

Expanded focused tests initially passed, but Luna's bounded review identified an
uncovered detectable-corruption case. A partial header checksum changed to
another valid hex byte was accepted/truncated as torn. The unchanged production
public negative ELF reproduces it (exit1). The fixed final-source positive ELF
rejects it before repair and preserves bytes (exit0). Full1082-path interim source,
four relevant Debug objects/negative ELF, failed/positive controls and compiler
corrections are preserved. Available checksum bytes are now compared with the
actual prefix checksum before torn classification, with added work reserved.

Audit pins212 actual executables,40 changed-unit objects,16 archives/four caches
and456 compiler/link records plus four public-control builds. All18 final matrix/
control receipt jobs are CLOSED, every terminal stdout archived and all strict
C++23/warnings-as-errors/new-test assertions/sanitizer/leak settings checked.
Accepted builds have no diagnostics; no build overlaps CTest in its directory.

## Handoff

Receipt prefix is `build/verification/o06-local-sink-native-`: preimages-v1,
interim-v1,negative-objects-v1,independent-v1,control source/commands/ELFs/logs,
inputs-v1,all final-v1 jobs,matrix-audit-v1,root-review-v1,progress-v1,jobs-v1,
checkpoint-seal-v1 and post-seal-audit-v1. Final docs-only source2 adds this record
and the API guide (1084 paths). Verify seal/readback before new edits.

Next add sink-aware native reconstruction using validated durable-prefix
authority, preserving complete native/whole-file admission and original-account
limits. Then implement crash-safe history-retirement intent/continuation under
the generation lock, only after durable checkpoint/root and verified local sink
coverage. Full/fresh integrated O04–O06 acceptance, O08 workflow, A02 licensing
and other Refactor cards/release gates remain open. See [handoff](../handoff.md).
