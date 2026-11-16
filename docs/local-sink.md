# Durable local epoch delivery

Include `crown/runtime/session_local_sink.hpp`. A journaled `QuerySession` can
attach a durable local sink that accepts complete committed physical epochs,
including epochs with no output. The native producer still prepares its bounded
atomic spool before commitment. Delivery persists that whole epoch and releases
its output only after successful file synchronization. Old selected recovery
pairs remain retained until explicit [verified history retirement](history-retirement.md).
O04–O06 integrated acceptance is verified within its
[dated 264-test matrix](verification/o05-o06-native-acceptance-2026-11-10.md).
This scope does not complete repository-wide release review.

Call `create_local_sink(path, options)` at the journal's checkpoint boundary,
before advancing beyond that physical base. Supply a32-byte lowercase hexadecimal
`sink_id`. The session provides query identity, exact native program/source/
catalog/arithmetic policy and output scalar schema. A sink declares an initial
snapshot boundary: its change stream starts after that physical sequence. Supply
the baseline snapshot through the existing snapshot/checkpoint APIs when a client
needs it; the sink does not insert a synthetic epoch-zero snapshot.

After `commit()`, call `deliver_local_epoch()` until it returns `idle`. A
`published` result means one new complete epoch is durable; `duplicate` means an
identical previously durable epoch was verified without appending it again. The
result reports generation, physical sequence and row count. After acceptance,
`local_sink_receipt()` supplies an immutable, private-constructor receipt for the
bound local file's complete durable prefix. Its fields are nontrivial immutable
values; a returned report or detached byte representation cannot mint coverage.
Receipt metadata does not authorize retiring history by itself. Receipts also
carry the actual complete-prefix byte length and chain fingerprint. Rotation
binds verified checkpoint delivery into root v2; retirement requires the private
native verification state and selected durable checkpoint, rather than a report.

The session retains committed output until acceptance. While delivery is pending,
`begin_next_result()` returns `would_block` before peeking at another source
record; `begin_next()` reports `input_would_block`. Typed admission may fill only
the configured bounded input queue; `full` retains caller batch ownership. Normal
`next_output`, recovered-output transfer/discard, `start_drain` and discard-drain
reject while a sink is attached. They cannot silently remove required delivery.
Empty-output epochs also hold admission until their closure is persisted.

Pause preserves the pending epoch. Stop is terminal cancellation: it aborts
unpublished work and releases in-memory output without advancing the sink's
acknowledgment. Its journal remains the source of committed work on restart.
Drop/destruction also releases sink descriptors/buffers and writer locks. An
uncommitted complete input remains available through native recovery; do not
reoffer a cached retained input. Self-join occurrence fan-out remains private
until the existing atomic commit barrier, and local delivery rejects private work.

For restart use `restore_generation_with_local_sink(program, root, recovery,
sink_path, sink_options, continuation)` or the direct checkpoint/journal variant
`restore_journal_with_local_sink(program, checkpoint, journal, recovery, sink_path,
sink_options, continuation)`. Both return paused with the sink attached. The
factory opens and validates the actual durable sink in the same receiving query
account before native replay. Every already persisted post-checkpoint physical
epoch, including an empty closure, must match the complete canonical native
output. Verification cannot append a missing epoch. Metadata window substeps do
not create output epochs. A mismatched prefix or a sink ahead of the fully
validated native journal rejects without exposing an owner or output.

Acknowledged replay uses the normal bounded native atomic spool, borrowed row
views and canonical comparison buffers; it is released after comparison instead
of entering the recovered-output backlog. Only missing epochs consume recovery
`output_rows`/`output_bytes`. Fully acknowledged replay therefore accepts zero for
both limits. Missing output still obeys those limits, and all simultaneous native,
source, file, index and comparison allocations obey the same query heap cap.
Copied replay/source/file grants remain cumulative. Comparison charges the sink's
existing `delivery_work` grant once per epoch and row, retaining that spent work
for subsequent delivery/reopen; it does not mint a separate recovery grant.

The sink's query/program/schema identity must match; its stored initial base and
generation may predate the selected checkpoint. Complete durable coverage must
reach that checkpoint. The factory verifies subsequent accepted epochs against
native replay and retains missing output in order. It performs whole WAL/native,
pending-input, source/CSV/window, EOF/stamp/sync and optional continuation-seek
checks before repairing either incomplete tail. Complete corruption never
repairs. Caller `outputs_after_physical_sequence` is rejected by these factories:
an option is not durable delivery authority. Call `deliver_local_epoch()` after
restore to persist only missing epochs, then `start()` to resume admission.

The original two-step path remains available: `restore_journal` or
`restore_generation` with complete replay output, then `open_local_sink`.
It retains all replay output before attachment, so configure replay caps for the
selected journal. Partial transfer/discard or caller-frontier suppression cannot
authorize sink attachment. `open_local_sink` also reopens a poisoned attached
sink after I/O failure. Opening a sink whose coverage is behind the selected
checkpoint rejects; catch-up across older retained pairs is not inferred.

On this two-step path, `open_local_sink` can repair an explicitly allowed
incomplete suffix after identity, coverage and checkpoint-prefix checks.
`deliver_local_epoch` subsequently compares complete post-checkpoint epochs
against retained native output. Use a combined restore factory when these
semantic comparisons must precede either tail repair. The combined factory
repairs the WAL first and the sink second; a successful WAL repair remains if
the later sink repair fails.

Local delivery uses sign and exact native typed values, bound to query/sink/
generation/physical epoch. Serialization sorts complete typed row bytes into a
canonical order and rejects duplicate same-sign tuples. Ordinal, container
iteration order and layout addresses are excluded. A retry compares the entire
canonical frame against the stored frame, rather than trusting a digest alone.
Different contents or generation at an existing physical epoch reject before
mutation; gaps and decreasing generations reject. Window metadata steps create
no additional physical output epochs. A generation rotation preserves sink
identity/base and requires verified delivery through the committed boundary.

`read_local_epoch(sequence)` returns one complete persisted epoch with native
account-owned rows, usable after session destruction. The standalone
`crown::recovery::sink::File` API supplies the same create/open/append/read/receipt
contract for explicit producers and consumers. Its caller supplies expected
binding/schema and immutable input views during each call. `HeaderMatch::identity`
discovers the stored starting boundary while still checking the identity/schema;
the session additionally validates it against its actual checkpoint/journal.
`File::verify_epoch` compares only an existing complete epoch, even through a
valid incomplete suffix, and cannot append. Receipt and append remain blocked
until explicit tail repair. Generic file receipts prove local storage, not that
an arbitrary producer ran a query correctly.

Creation uses a random0600 exclusive no-follow sibling temporary, complete write,
file fsync, no-replace link, temporary unlink and parent fsync. Existing entries
are never replaced. Open admits a no-follow regular file, takes an exclusive
nonblocking advisory lock, validates the complete prefix and exact EOF/stable
metadata, then syncs the inode and parent before returning. The cooperating
writer owns the inode lock for its lifetime. Keep the trusted parent/name stable.
These are the established Linux local-filesystem/fsync assumptions; process-crash
tests do not simulate power loss.

A complete epoch frame is the local visibility/acknowledgment unit. Consumers use
the validated API/format and ignore incomplete tails. A file write/sync can fail
after a complete visible frame exists; the sink becomes poisoned and requires
reopen/validation. Reopening adopts and syncs a complete valid prefix, so a retry
deduplicates that epoch. Native session output remains available on the failed
attempt. An incomplete later tail can be explicitly repaired; session options
default to repair. A complete corrupt frame, impossible available checksum prefix,
schema/ordering error or binding mismatch rejects without repair. The initial
header must always be complete. Checked Linux close is never retried.

Buffers, native row views, row-offset sorting, decoded rows, schema and epoch
index use the original query account. No ordinary Row/string mirror is created
inside delivery. Default file limits are1GiB total bytes,1,000,000 epochs and I/O
operations,4GiB cumulative codec/validation-work units,1MiB transfers,4095 path
bytes; each record allows64MiB,512MiB work,65536 rows,1024 fields and1MiB scalar
bytes. Limits are copied and counters remain private. Reopening admits a fresh
file-validation owner; session `delivery_work` already spent is retained. Its
default512MiB grant charges one unit per epoch attempt and collected row view.

Canonical encoding temporarily retains row bytes, offsets and a final frame;
retries/readers also need a bounded frame buffer. The epoch index grows with the
retained file prefix. All actual simultaneous allocations still obey the shared
heap cap, including transient vector growth. Limits reject cleanly and keep
committed output for retry; this implementation has no unbounded queue or spill
fallback. `local_sink_state()` reports durable/verified boundaries, file bytes,
accounted buffer bytes, codec/I/O work, delivery work and blocked admission calls.
These counters describe costs; they are not wall-time or RSS guarantees. Legacy
D06 callback timing/report contracts remain separate from this session file API.

CROWNSK1/version1 frames have a148-byte protected header: magic8, version u16=1,
flags u16=0, body length u64, ASCII64 SHA256(body), ASCII64 SHA256(first84 header
bytes), then body. Integers are little-endian and hashes/identities lowercase
hex. Header body kind0/ordinal0 stores query/sink IDs, native ImageBinding/policy
version, initial generation/base, field count, schema SHA and scalar type tags.
Schema SHA hashes the one-byte type-tag list. Epoch body kind1 stores ordinal,
generation, physical sequence, row count and canonical rows; ordinal is physical
sequence minus initial base. Each row is operation-u8, arity-u64 and exact tagged
scalars: int64 bits, length-prefixed UTF8 string, bool, Date epoch-day bits, or
canonical inline decimal text. Strings may contain NUL; paths/IDs may not.
Checksums detect corruption within the trusted namespace and are not signatures.

The [verification record](verification/o06-local-sink-native-2026-11-10.md) pins
the accepted source and scoped matrix. This API demonstrates transactional local
committed-file delivery. Arbitrary external callbacks can still accept then fail
and need their own idempotency protocol. See [handoff](handoff.md) for durable history retirement and the remaining
Refactor work. The [sink-aware verification record](verification/o06-sink-restore-native-2026-11-10.md)
pins this factory integration separately from the initial sink component.

Checkpoint-root v2 anchors authenticate the pre-checkpoint sink prefix on both
restart paths before either tail is repaired. A private verified prefix advances
only after actual native append/duplicate verification, and same-owner reopen
checks it. A legacy v1 root with an older sink base cannot authenticate that
history for retirement or rotation. `local_sink_state().retirement_verified` is
descriptive. Per-entry chain fingerprints remain account-funded; initial copying
charges64 work units and each128-byte chain copy/hash charges256 units. See the
[retirement protocol](history-retirement.md) for compatibility and guarantees.

Integrated O04–O06 acceptance is verified: all 264 registered tests pass Debug,
Release, Clang18, ASan+UBSan/leaks and clean source-only Release with unchanged
predecessor definitions. See the [complete record](verification/o05-o06-native-acceptance-2026-11-10.md)
for requirement mapping, whole native pipeline/crash/resource evidence and limits.
