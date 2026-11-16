# O04 complete binary session envelope — scoped verification

The CROWNSI1/version1 complete session format is implemented. Atomic durable
publication/loading, persistence-failure handling and complete full/fresh-source
acceptance remain open. O04 is in_progress; the full Refactor.md goal remains
active, with ledger42 verified/3 in progress/33 not started (78 total).

## Implementation

[SessionImage](../../include/crown/recovery/session_image.hpp) contains owning
pointer-free bytes plus fixed manifest/statistics. [QuerySession](../../src/runtime/session.cpp)
holds the writer guard throughout capture and encoding, and rebuilds one new
query in one receiving account. Binary validation precedes decoded allocation;
native source/options/window owners contain no ordinary internal DTO graph.
Runtime bytes borrow immutable input only during synchronous restore, avoiding
an additional64MiB copy. All retained rows/text/options own their receiving bytes.
One indexed grant covers native runtime/source/support/live/workload admission.

The [format contract](../checkpoints.md) lists every field and resource boundary.
Controls, source kind, flags, snapshot/input/queue/workload policies, positions,
reader original counters/CSV mapping and window labels/count IDs/progress survive.
The embedded CROWNRI1 component binds catalog/plan/arithmetic/policy and restores
all physical base rows, including unmanaged/unused tables. A matching immutable
CompiledProgram must be supplied; program artifact serialization is not implied.
Shared scalar/policy primitives preserve the previous runtime format byte-for-byte.

The decoder rejects unknown versions/flags/enums, noncanonical optionals, overflow,
trailing/truncated bytes, wrong checksums, invalid source text/order/counters,
CSV permutations, window IDs/deadlines/progress and metadata limits before decoded
growth. Program/schema/constraint/window membership semantics additionally pass
through native admission. Capture-work fields describe the captured operation;
they never authorize new work or allocations. All real limits are recomputed.

## Executed acceptance

| Configuration | Selected tests | Wall time |
| --- | --- | --- |
| GCC Debug | 50/50 | 22.95s |
| GCC Release | 50/50 | 3.10s |
| Clang18 Debug | 50/50 | 18.78s |
| ASan + UBSan + leak checking | 50/50 | 97.51s |

All modes execute source8 (1010 paths); final9 adds this record and changes only
documentation (1011 paths). The50-test scope retains all48 predecessor regressions
and adds production and actual indexed-grant binary targets. It is scoped evidence,
not complete O04 or fresh-source verification.

Each new target covers48 typed cases (two backends, six query kinds, four states),
16 stream profile/backend continuations and16 backend/FIFO/window states. Typed
state and signed delta sets use the independent A04 or explicit SQL definitions.
Repeated capture is deterministic. Every18/613 reference and20/622 indexed
self-join allocation position fails atomically; actual global requests match the
original/receiving accounts. Exact receiving restore peaks succeed; one byte less
rejects. Existing native/window/source/policy/fault regressions remain intact.

New checks cover source-destroyed image lifetime, allocation-free image release,
CSV column permutation and self-join continuation, all native scalar window rows
(including raw NUL/non-UTF8 strings, date extrema and wide exact decimal), later
expiration, failed stopped reader state, writer/private/prepared/partial-output
barriers, active and stopped watermark barriers, and public zero-indexed-work
presentation. Logical deltas are checked as exact signed sets; durable replay
ordering/identity remains O05/O06 work.

The independent Python struct/hashlib fixture is1067 bytes, SHA256
`03b891a90f0b0a96406d77361d19f431546656365e9cce69f601c476e58492b4`.
It embeds an independently generated531-byte runtime component. Its synthetic
binding is codec-only; actual Program admission is covered by the production
round trips. Every truncation and bit flip, checksum-valid malformed fields,
resealed wrong program binding, exact/one-under byte/work caps and canonical
optionals pass. Structural rejection checks allow no allocation.

## Review findings and retained failures

Luna Max supplied a field inventory, the independent generator and a read-only
review. Root implemented the codec/integration and resolved the review finding;
no Astra was used. A caller-mutated native checkpoint could initially be encoded
with accepted progress that its inspector rejected. The unchanged public-only
production-library control fails before and rejects before output after source8.
All22 pre-fix source paths, the negative ELF/log, and the repaired control remain.
Encoder preflight now agrees with inspector invariants for sequence/control,
input canonicalization/ceilings, CSV mapping and window structural state.

Raw failures are preserved. The first new test build had two unused fixed
inspection-result warnings, fixed without relaxing warning policy. A raw-scalar
window fixture initially entered the UTF-8 text-input adapter; it now enters the
native component admission API, preserving its original raw-byte assertions.
GDB confirms a41-byte allocation in the existing running session-busy Error
presentation. Only that new over-strict Scope(0) expectation was corrected;
stopped active-window rejection remains allocation-free. No predecessor assertion,
fixture, limit, timeout or public stop semantics were weakened.

## Native evidence and next work

The receipt prefix is `build/verification/o04-session-image-native-`. The audit
reads back160 actual executables/four caches,56 changed-unit objects,16 archives
and352 compiler/link records. All accepted builds have zero compiler diagnostics;
strict warnings/assertions and ASan/UBSan/leak settings are checked against actual
flags. All32 jobs and handles are closed; every terminal CTest stdout is archived.
The final seal/readback pins source/preimage/artifact bytes and documentation links.

Next implement bounded file loading and atomic durable publication of this
complete envelope, documenting outcomes for write/sync/rename/directory-sync
failures and preserving the prior complete artifact until publication. Then run
full/fresh-source O04 acceptance before changing its status. O05 WAL and O06
durable delivery/replay identity remain separate. Continue from the
[handoff](../handoff.md) and [ledger](../task_ledger.md).
