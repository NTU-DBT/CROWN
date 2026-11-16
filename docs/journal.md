# Journal records and ordered-prefix validation

O05 is verified within its bounded native/set-session acceptance. This component
encodes and validates journal records. The
[session writer](session-journal.md) connects durable input/decision ordering
to prepared native publication. The [native recovery factory](native-replay.md)
reconstructs the exact checkpoint/prefix through actual native transitions,
retaining source continuation and bounded output with semantic identity. The
[durable file component](journal-files.md) supplies single-writer creation,
append/sync, reopening and explicit incomplete-tail repair. [Generation
selection/rotation](generations.md) durably selects complete pairs under a root
lock. [Local epoch delivery](local-sink.md) supplies canonical durable local
output/receipts. Sink-aware restore and [verified history retirement](history-retirement.md)
are implemented and covered by the integrated O04–O06 acceptance.
A prefix report alone does not establish durable persistence or native admission.

Include `crown/recovery/journal.hpp` and use `crown::recovery::journal`.
`encode(account, ordinal, payload, limits)` preflights the complete record before
allocating one final account-funded buffer. `inspect(bytes, limits)` validates
both checksums and complete structure without allocation. `decode(account, bytes,
limits)` owns native row/source/CSV storage in the receiving account. It retains
no view into the input frame. The byte view must remain immutable during each
synchronous call.

`Decoded::input_view()` borrows the decoded owner's native tuple, source name and
reader permutation, avoiding an ordinary owning Row conversion. Keep that owner
alive until the view is consumed. Temporary owners cannot produce this view or
a source-name view. The downstream query still validates catalog, row/domain,
source and window policies; codec metadata is descriptive.

`scan(bytes, limits, expected_header)` reports the validated complete prefix and
last committed physical/accepted command boundaries. The first header must be
complete. A later compatible incomplete header/body reports a torn tail; a
complete header has its checksum checked before its length can classify a body
as incomplete. Complete malformed or checksum-invalid records reject. The report
retains a pending input view for an unfinished window command; those frame bytes
borrow immutable caller input.

`Cursor(limits, expected_header)` validates the same stream incrementally through
`feed(full_frame)` and `finish_tail(incomplete_tail)`. Limits, expected binding and
continuation state are privately owned. Reports returned by `state()` or feed are
copies and cannot reset quota or sequence state. No constructor imports a report.
The cursor is noncopyable; moves transfer continuation and invalidate the source.
Each feed validates exactly one complete record, without rereading earlier file
contents. Failed feed/tail validation leaves the prior cursor state unchanged.
The pending frame retains its borrowed lifetime. Filesystem repair/flush remains
the file owner's responsibility; validating a replacement does not repair a file.

Failures carry `journal::Fault` (the shared image fault categories) with a fixed
`journal::Failure` diagnostic. Native `MemoryFailure` categories and allocation
failures propagate unchanged. Error paths do not build owning error strings.

## Format 1

Magic is eight bytes `CROWNWAL`, followed by little-endian u16 version1, u16
flags0, u64 body length and64 lowercase ASCII SHA256 bytes over the body. Those
84 prefix bytes are followed by64 lowercase ASCII SHA256 bytes over the prefix,
then the body, for148 bytes of fixed header. Both checksums are required; the
protected length prevents corrupt complete records from looking like torn tails.
The experimental `CRWNWL00`/version0 prototype is not a supported wire format.
There is no implicit migration, forward skipping or checksum authentication.

Every body starts with kind u8 and ordinal u64. Kind0 is the first header record,
ordinal0; subsequent record ordinals are positive and contiguous. Header payload:
query ID32 hex, generation u64>0, physical/source SHA64 each, catalog u64>0,
arithmetic u16(1),26 runtime policy u64 words, checkpoint SHA64, base physical/
command sequence u64 and input kind u8(stream0/physical1/window2). A nonwindow
header has equal physical and command sequences. An expected header matches all
fields, including query/generation identity and checkpoint digest.

Kind1 input has an item tag u8 and sequence u64>0. Physical tag0 adds table u64,
operation u8(insert0/erase1) and a row. Window tag1 adds command u8(insert0/
withdraw1/watermark2): insertion carries label>0/table/row/timestamp; withdrawal
carries label>0; watermark carries its value. Every item then has an optional
source tag and, when present, u64 UTF8 name length/nonempty nonNUL bytes plus u64
offset. An optional reader advance follows: bytes/records u64, header-read bool
and u64 CSV permutation count/list. It applies only to physical stream records;
records equal the input sequence, and absent header state has no permutation.

Rows use a u64 field count and the CROWNRI1 native scalar tags: int64 bits, raw
byte strings with u64 length, canonical bool0/1, signed32 epoch-day bits, and exact
canonical decimal text with a one-byte length. Row strings are not normalized.
Source names retain strict UTF8/nonNUL validation. Source-validation byte work is
admitted before visiting the name, on both encode and decode paths.

Kind2 commit carries input ordinal u64, its body SHA64, commit kind u8(physical0/
metadata1), physical sequence/completed command sequence/substep u64 and canonical
completes-input bool. Markers bind to the active input and next substep. Physical
markers increment physical sequence exactly once. Incomplete window substeps keep
command progress fixed; completion advances it to the input command sequence.
Metadata commits leave physical sequence unchanged and are forbidden for
physical/stream input. Window watermark steps can be incomplete metadata commits
when expiring a duplicate row label: completed-command sequence stays fixed and
substep advances. Incomplete physical/metadata steps are watermark-only; completion
advances the command sequence. The pre-release version1 wire layout is unchanged. A new input cannot replace a pending one.

Kind3 checkpoint carries physical/command sequence u64 and checkpoint SHA64. It
requires no pending input and matches the current committed boundaries. The
marker alone is not authority to truncate a journal. The generation protocol
publishes a durable checkpoint/pair/root while retaining prior history; durable
local sink coverage now authorizes explicit [history retirement](history-retirement.md)
through a checkpoint-bound root anchor and durable cleanup intent. The marker
alone still supplies no retirement authority.

## Resources and evidence

Record byte/work/row/field/scalar bounds and source-name bytes are independent of
global prefix byte/work/record limits and actual account ceilings. Record rows
bound input row payloads, including empty rows; a record contains at most one.
The common ImageLimits table-count field has no table-list payload here; table
IDs receive actual catalog validation at native query admission. Serialized work
reserves checksum visits, validation/materialization passes and CSV-permutation
comparisons. The private cursor retains cumulative work across feeds. Fixed
metadata copies and runtime admission have their own costs; these abstract units
do not claim a CPU-time or RSS bound.

Seven independent Python fixtures cover624/284/255/237/201/177/177-byte frames,
all native scalar kinds, source/reader metadata and all window command kinds.
Tests reject every truncation and one-bit flip at every byte, checksum-valid
malformed fields, and incompatible ordinal/input-digest/substep bindings. They
cover1804 cuts of a six-record window prefix, partial physical versus command
progress, whole/incremental parity, no-allocation validation, persistent faults,
exact/one-under limits, retained decoded lifetime and diagnostic quota-tamper
rejection. Native file/query recovery is verified within the separate integrated
O04–O06 packet; these codec fixtures alone do not establish that result.

The [component verification record](verification/o05-journal-native-2026-11-10.md)
records54 selected tests in four native configurations and both preserved public
regressions. The [current ledger](task_ledger.md) records the later integrated
264-test O04–O06 acceptance; release gates remain open.
