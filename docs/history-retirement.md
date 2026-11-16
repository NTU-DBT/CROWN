# Durable history retirement

Include `crown/runtime/session_generation.hpp` and
`crown/runtime/session_local_sink.hpp`. Call
`QuerySession::retire_generation_history()` at a quiescent generation barrier
after all committed output is verified in the attached actual local sink.
The operation deletes only older generations' checkpoint, journal and optional plan-descriptor files. It preserves the selected generation and complete local
output, advances the root's retained first generation to current, and frees
capacity under the configured retained-generation count. Repeating it is safe.
Rotation continues to retain history until this explicit operation succeeds.

Private work, a still-pending native/WAL input, a partial window command,
unread/undelivered output, terminal state, an uncertain journal or an unavailable
sink rejects retirement. Merely queued input that has not begun does not prevent
this barrier. A sink receipt by itself proves local storage. The session additionally
requires private native verification of that prefix, selected checkpoint hash,
physical/command bases and program/source/catalog/policy/schema binding. Mutable
state reports, replay frontiers and output consumption cannot authorize deletion.
The selected checkpoint is read and validated in the original account before
mutation. Confirmation rehashes those bytes, reopens the selected name, checks
regular-file status and size, then syncs that file and directory. It does not
reread the reopened bytes or compare its inode with the earlier reader; the
trusted stable namespace and generation lock are required.

## Checkpoint delivery binding

When rotating with a verified local sink, the durable generation root uses
CROWNGR1/version2. Its324-byte record extends the v1 native selection with sink
identity, checkpoint physical sequence, complete prefix byte length and SHA256
chain fingerprint. This binds the output already delivered before that checkpoint,
which later native replay does not recompute. The root is synced before the new
pair admits input, and retirement preserves its delivery anchor while changing
only the retention floor.

The sink's existing CROWNSK1 wire format is unchanged. File validation builds a
prefix chain from complete, checksum-validated canonical frames. The initial
fingerprint is the header frame's protected-header checksum. Each next fingerprint
is SHA256(previous64 ASCII checksum bytes followed by the next frame's64 ASCII
protected-header checksum bytes). Frame checksums bind body length and body SHA,
and canonical bodies bind generation/physical sequence/sign/exact typed values.
Index entries retain each prefix fingerprint under the same query heap. Comparing
a root anchor therefore works even if the sink contains later complete epochs
or a compatible incomplete suffix. Hash integrity assumes SHA256 collision
resistance; these checksums are not signatures.

On restart, both sink-aware factories and two-step attachment check the actual
file's checkpoint prefix against the selected root before tail repair. A changed
but structurally valid old epoch cannot silently become verified. Native replay
still compares complete canonical bytes for subsequent acknowledged epochs.
The private verified fingerprint survives same-owner reopen and advances only
after durable append or exact native duplicate verification. Unknown append
completion requires reopen and native verification before it becomes acknowledged.

CROWNGR1/version1 remains the212-byte format for roots without a delivery anchor.
Plan-aware roots use version3 (276 bytes) or version4 (388 bytes with delivery);
their selected plan hash is preserved through retirement. See
[reoptimization](reoptimization.md#durable-selection-and-sink-lineage).
A sink starting at that exact checkpoint has no earlier output to authenticate.
A legacy sink whose base predates an unanchored checkpoint remains readable and
recoverable, but cannot authorize retirement or be promoted into a new anchored
generation by rotation. Starting a different sink cannot replace an already bound
root contract. `local_sink_state().retirement_verified` reports the current private
checkpoint-prefix basis. Current delivery, health and quiescence are checked
separately; editing the returned report changes no authority.

## Persistence and continuation

Under the existing lifetime generation lock:

1. Validate the selected native checkpoint and actual verified local delivery.
2. Exclusively publish and directory-sync a checksummed `root.retire` intent.
   It records the old retained range and immutable native checkpoint/root binding,
   sink header and acknowledged generation/physical sequence.
3. Atomically replace and directory-sync the same-generation root with first=current,
   preserving its delivery anchor. The intent retains the old range after this step.
4. Unlink only each recorded older `.ckpt`, `.wal` and `.plan` name. Directory-sync after
   each removal; an already absent name is an idempotent completed removal.
5. Remove the intent and directory-sync last, after every old name's removal is
   durable. In the call that publishes a new intent, its successful suffix performs
   no allocation after intent publication. Restart admission still constructs and
   validates funded state before continuing an existing intent.

The selected checkpoint/journal is never a deletion candidate. No directory scan,
temporary or future unselected generation chooses cleanup scope. A failure after
publication can be uncertain and forbids continued session publication; drop the
owner and use `restore_generation_with_local_sink` with the same sink contract.
It validates the root-bound intent, selected checkpoint, actual sink prefix and
whole native/source/EOF/stamp/sync/seek recovery before repairing either tail,
then resumes cleanup before exposing the owner. Each removal and cleanup of the
intent can be retried. Bare `restore_generation` rejects a pending intent because
it lacks the actual sink needed to validate continuation.

A crash before floor publication leaves old selection plus intent. A crash after
floor publication retains the old deletion range in that intent. If the intent
is absent after its final unlink, all older names have already been removed and
synced. A still-visible intent can safely repeat already completed removals.
Malformed, incompatible or mismatched intents reject without repair/deletion.
After the floor advances, a genuine intent is the retained authority for the old
range. Checksums detect integrity changes; they do not authenticate a replacement
intent written and resealed by a hostile namespace writer.

## Format and costs

The retirement intent CROWNRT1/version1 is724 bytes: magic8,version u16=1,
flags u16=0,body length u64=640; native root projection128 bytes; sink header496;
acknowledged generation/sequence u64 each; then ASCII64 SHA256(first660 bytes).
The native root projection is query32,current/first u64,checkpoint SHA64,
physical/command u64. The sink header is query32,sink32,physical/source SHA64 each,
catalog u64,26 policy u64 words,initial generation/base/fields u64,schema SHA64.
The delivery anchor remains in the selected root and is checked independently;
the intent binds the immutable native selection and old cleanup range. A
plan-aware intent uses version2, body704 and total788 bytes: it adds the selected
plan SHA64 before the trailing checksum. Legacy version1 remains724 bytes.

Root v2 has the same8-byte CROWNGR1 magic,version2,flags0,body length240,
the original128 native bytes,then sink ID32,sequence u64,prefix bytes u64,
content-chain SHA64,then ASCII64 SHA256(first260 bytes). V1 remains unchanged.
All integers are little-endian. Hashes/IDs are lowercase ASCII hexadecimal.

Checkpoint validation buffers, sink index/fingerprints, native replay and control
state share the original receiving account. Root I/O and extra validation work
remain copied and cumulative; checkpoint rehashing charges its bytes. Sink chain
construction charges64 initial byte copies and256 units per epoch for copying
and hashing the128-byte link. Canonical encoding/replay grants remain separate
and bounded. Limits must cover the chosen recovery/cleanup range; exhaustion
rejects without refilling a live owner's counters. This protocol has no unlimited
queue or hidden spill allowance. Removing native history does not compact the
retained local output file; its existing file/epoch/index limits still apply.

Filesystem assumptions remain trusted, stable Linux namespace, regular no-follow
files, cooperating exclusive locks and local fsync semantics. Process-crash tests
do not simulate power loss. Local file delivery proves no arbitrary external
callback side effects. See [verification](verification/o06-history-retirement-native-2026-11-10.md)
and [handoff](handoff.md). The integrated O04–O06 264-test acceptance is verified
within its frozen native/set-session scope. R2 aggregate history retirement and
release gates remain open. The [independent retirement argument](../build/verification/v02-retirement-proof-review-v1/report.txt)
records the actual deletion range, publication order and restart assumptions.
