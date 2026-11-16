# Durable generation selection, rotation and retirement

`QuerySession::enable_generation` publishes an initial native checkpoint and
journal through a durable root file. `rotate_generation` selects a new pair at a
quiescent boundary. `restore_generation` follows that exact root and returns the
reconstructed owner paused. Include `crown/runtime/session_generation.hpp`.
The [journal writer](session-journal.md) and [native replay](native-replay.md)
contracts still apply.

O05's integrated generation protocol is verified within the
[O04–O06 acceptance scope](verification/o05-o06-native-acceptance-2026-11-10.md). Rotation
retains selected historical pairs until explicit [verified retirement](history-retirement.md). Consuming or
discarding replay output, reaching a checkpoint, and supplying a replay frontier
do not authorize deleting history. The [local epoch sink](local-sink.md) supplies
durable local prefix receipts and explicit verified session delivery. A
durable [history-retirement protocol](history-retirement.md) now binds actual
verified sink/checkpoint coverage. The dated integrated record preserves its
264-test source/configuration matrix; full release reviews remain open. A new root is authority for current native state, not an acknowledgment of
external output delivery.

Set `SessionGenerationOptions::journal.query_id` to the expected 32-byte lowercase
hex query identity. `journal.generation` is the positive first generation; its
default is1. Enable on a created/running/paused session with no attached journal,
private work, queued/cached input, unread output, failure or observed EOF. The
existing native checkpoint barrier enforces source/window quiescence. The new
root and pair are exclusive creations; an existing root or candidate is never
replaced by initial enable.

For root path `/trusted/data/query.root`, generation1 uses sibling paths
`query.root.g0000000000000001.ckpt` and
`query.root.g0000000000000001.wal`. The stable `query.root.lock` sentinel is
no-follow regular-file admitted, exclusively flocked and synced with its directory
before publication. Its descriptor and a directory descriptor stay owned for the
session lifetime, alongside the current journal lock. Never remove or replace the
sentinel. Keep the parent namespace/root name stable; relative paths also require
a stable working directory. Cooperating users of this namespace must use the
generation APIs to mutate managed pairs, including historical journals.

The existing parent must be trusted. Names are opaque non-NUL bytes; root names
are at most232 bytes, leaving room for the longest derived sibling under Linux's
255-byte component limit. Full derived paths obey the configured path limit.
Root/lock/checkpoint/journal symlinks are not followed by admission. The
[Linux local-filesystem assumptions](journal-files.md) remain unchanged.

Initial enable and rotation use this order:

1. Capture and encode a quiescent native checkpoint in the original query
   account. Preflight the copied checkpoint load-policy shape and limits.
2. Write a random exclusive sibling temporary, fsync it, checked-close it,
   install the checkpoint without replacement, remove the temporary and fsync
   the parent directory.
3. Exclusively create, lock and durably publish a fresh journal header bound to
   that checkpoint's exact SHA256, query/generation, program/catalog/policy and
   physical/command bases.
4. Write/fsync/checked-close a complete root temporary. Initial publication uses
   no-replace link; rotation atomically renames over the old root. Fsync the
   directory before switching the in-process active journal.

No input or decision is admitted to the new log before root durability. Completion
after the root link/rename is allocation-free. Rotation preserves current native
state/source/control and changes only the selected durable baseline/log. The old
journal closes after the new root is durable; both old files remain intact.
Checkpoint-file replacement through the direct API stays blocked while attached.

Rotation requires an enabled healthy generation owner and no pending journal
input or active partial watermark command. It retains the original first
generation and increments current generation without wrapping. The default
`retained_generations=32` includes every generation from first through current;
exceeding it rejects before publication. This bounds retained selected pairs
together with each checkpoint/journal's byte caps. It does not silently delete
an old pair. A later restart may explicitly use a different retention policy.

Before rotating, the owner rereads the current root under its stable lock and
requires its exact stored selection. It may unlink only the next unselected
candidate's three derived names (`.ckpt`, `.wal`, `.plan`), then fsync the directory. Such candidates can be
left by a prior failed/crashed attempt before root publication. Selected/older
generations are never cleaned by this path. A failed initial enable with no root
can leave unselected candidates; inspect the outcome and use an unused explicit
initial generation if creating again. A complete existing root should be reopened.
Random temporary files are never selected automatically and may remain after
process crashes.

`GenerationFailure` reports a fixed fault/stage/native error and root-selection
outcome. Candidate-file creation does not itself change selection. Once a root
link/rename is attempted, failure can mean `unknown`; it never authorizes blind
retry or history deletion. A generation/journal I/O failure marks the session
`recovery_required` and retains its root ownership until drop/destruction. Native
memory/codec categories remain intact. Prepublication allocation failures retain
the old selected owner and can retry after unselected-candidate cleanup. Stop
retains writer ownership; explicit drop releases the current journal, root lock,
directory and funded owner without allocation.

For recovery supply `SessionGenerationRecoveryOptions::replay.journal.query_id`
as an expected binding. The authoritative root supplies its generation; the
`replay.journal.generation` input is ignored by this API. The factory admits and
locks the root, checks complete fixed bytes/checksum/stable metadata/exact EOF and
syncs the root and directory. It validates the selected checkpoint's exact hash
and physical/command bases before opening, replaying or repairing its journal.
Existing native program/schema/source/window and journal header checks still
apply. Missing/corrupt roots reject; the factory does not guess from old pairs,
directory listings or temporary files.

The root lock stays private across native reconstruction. Its final generation
holder is funded in the receiving account before replay can repair durable
tails, then installed in the session by a nonthrowing move. A rejected receiving
allocation or heap cap leaves incomplete WAL/sink tails unchanged and releases
the owner and locks. The same admission ordering applies to legacy roots and
descriptor-aware selected-plan recovery; retirement cleanup is a later,
separately recoverable operation. Use the [native replay options](native-replay.md) for stream tail/origin
seek, complete pending input, partial windows and bounded identity-bearing output.
The selected generation is included in recovered identities. An attached local
sink retains previously accepted epochs across rotations.
`restore_generation_with_local_sink` validates the actual bound sink before
replay, compares accepted post-checkpoint physical epochs and retains only
missing output. It accepts an older sink origin whose complete coverage reaches
the selected checkpoint; it rejects coverage behind that checkpoint or ahead
of validated native replay. Both tails repair only after whole native/source
validation. Native replay does not reproduce output predating the selected
checkpoint; catch-up across older pairs remains separate work.
Explicit retirement is available after actual verified delivery; a pending intent
requires sink-aware recovery, which validates before tail repair and resumes
cleanup. Bare recovery rejects a pending intent.
See the [local sink contract](local-sink.md).

`generation_state()` returns fixed descriptive selection and current operation/
validation-work counters. On uncertain I/O its selection can be the previous
confirmed root; reopen after releasing the owner. Mutating that report cannot
change the owned selection or refill quotas. Root limits and generation policy
are copied, and root I/O/extra validation work are cumulative for that owner.
Default root limits are4095 path bytes,1MiB transfer chunks,1,000,000 operations,
128MiB checkpoint bytes and1GiB extra validation work. The extra-work accounting
charges checkpoint payload bytes once, the actual encoded root length per root
encoding, and twice that length per root inspection. Root variants use 212, 324,
276 or 388 bytes; these declared units are separate from I/O, hashing and native validation.
Root limits govern candidate publication; `journal.checkpoint` retains native
envelope/capture/load policy, and
the journal file retains its own scan/record/I/O limits. Recovery limits must be
sufficient for the saved image and selected log. Native execution/source limits
and the actual shared heap account remain independent finite bounds, not RSS or
wall-time claims.

The CROWNGR1/version1 root is exactly212 bytes. It contains magic8, version u16,
flags u16=0, payload length u64=128; query-id ASCII32, generation u64,
first-generation u64, checkpoint-SHA ASCII64, physical u64 and command u64; then
ASCII64 SHA256 of the preceding148 bytes. Integers are little-endian. Identities
and hashes use lowercase hexadecimal. Positive first<=current is mandatory;
trailing bytes, malformed metadata and checksum corruption reject. Checksums
detect corruption within the trusted namespace; they are not signatures.

See the [verification record](verification/o05-generation-native-2026-11-10.md)
for source/binary evidence and scoped acceptance. The
[handoff](handoff.md) records durable acknowledgment/retirement and the remaining
Refactor work.

Rotation with an authenticated local sink writes CROWNGR1/version2 (324 bytes),
which adds a checkpoint-bound delivery-prefix fingerprint. Roots without that
anchor keep v1/212 bytes. The same-generation retirement floor preserves the
anchor. See [retirement](history-retirement.md) for wire layouts, compatibility,
limits and every persistence/continuation boundary.

A plan-bound selection uses version 3: 276 bytes without delivery or 388 bytes
with delivery. It adds the exact selected plan descriptor hash; flags distinguish
the delivery-bearing variant. All admitted versions retain exact length/checksum
validation rather than treating one version's size as a universal work constant.

Integrated O04–O06 acceptance is verified: all 264 registered tests pass Debug,
Release, Clang18, ASan+UBSan/leaks and clean source-only Release with unchanged
predecessor definitions. See the [complete record](verification/o05-o06-native-acceptance-2026-11-10.md)
for requirement mapping, whole native pipeline/crash/resource evidence and limits.
