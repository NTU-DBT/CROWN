# O05/O06 native history retirement — 10 November 2026

This goal turn is progress. Root implemented and reviewed production changes.
Luna Max supplied bounded inventory/review and independent wire fixtures; no
Astra was used. Full Refactor.md goal remains active and work uncommitted on
baseline `e369a623517723b3be3ea3e9806779f3c591e7f9`. Ledger:43 verified,
3 in progress(A02/O05/O06),32 not started,78 total.

## Accepted component

The [retirement API](../history-retirement.md) requires a healthy quiescent
generation, actual privately verified local delivery and validated selected
checkpoint/root binding. Intent is durable before floor advancement; floor
preserves delivery binding; every recorded older unlink directory-syncs before
intent cleanup. The current pair is never a candidate. Unknown failures require
reopen. Sink-aware recovery validates all native/source/sink/intent checks before
tail repair and resumes cleanup before exposing an owner. Bare recovery rejects
pending cleanup. Successful completion after intent publication allocates nothing.

Review found an actual pre-checkpoint prefix gap after the initial6/6 focused
tests passed: a validly checksummed old output could change under a checkpoint
with no remaining WAL replay, then be treated as verified for deletion. Root's
unchanged public production control reproduces deletion (negative ELF exit1).
The fixed-source same control rejects it and preserves old history (positive0).
All1099 interim paths (1095 sources plus4 generated test caches), five relevant
objects and the negative ELF remain preserved.

The fix adds rootv2's324-byte durable sink-prefix anchor and private native
verified-prefix tracking. File frames stay unchanged; complete prefix chains
bind actual canonical body/header checksums. Creation/header baselines or a
matched root anchor establish verification, actual native append/duplicate
comparison advances it, and same-owner reopen checks it. Legacy unanchored roots
remain recoverable but older unauthenticated sink output cannot authorize
retirement or rotation. Current-root floor changes preserve the anchor. These
hashes assume SHA256 collision resistance in the trusted namespace.

## Native evidence

Frozen source1 has1098 paths: all1088 predecessor paths plus10 new production,
support/test/fixture paths. Ten existing headers/build/production paths change;
all predecessor test sources/fixtures/caps/timeouts and accepted flag records
are unchanged. First compile corrections are retained (indentation warning and
an ambiguous new helper name). After the fix, focused12/12 passed.

Final selected75/75 pass four modes: Debug 202.14s, Release 288.92s, Clang18 290.96s, ASan+UBSan/leaks 221.05s.
262 registered names retain all259 predecessors. This is scoped75 acceptance,
not whole262/fresh integrated O04–O06 acceptance. Historical acceptance remains
bound to its original source. O05/O06 stay in progress until integrated audit.

Each mode checks12 typed cases across two backends and six query kinds,32
eight-format/backend/pending stream cases and16 partial-window/backend/FIFO
cases. Independent semantics verify native state/source/output and next updates.
Tests cover finite retention reuse, no-sink/report/undelivered/private/pending
gates, selected checkpoint corruption, exact old-range deletion, repeated no-op
retirement, root-floor/partial-absent continuation, both-tail validation ordering,
every724 intent cut/flip and324 v2-root cut/flip, checksum-valid bindings, legacy
fail-closed behavior and checkpoint-prefix mismatch through both restart paths.

Independent stdlib Python fixtures match native bytes/fields:724-byte CROWNRT1
intent SHA256 `54e9f4216cb183cc3f55dc84d218586dfc25c87a12d6b69591d9afec775d4ace`;
324-byte rootv2 SHA256 `86e8d4ea2d5df4d1a60935790146d34751a475801e89f14f908866d972d6dee5`.
Actual file prefix chains are also checked against an independent construction
from the complete frame checksums before comparing root binding.

All1 live and860 receiving allocation faults preserve durable files/release
locks; receiving counts equal the original account and exact/one-under heap
checks pass. Allocation denial from intent link proves nonallocating completion.
Live retirement has48 actual syscall boundaries; interrupted-cleanup restore has
108 across real root/checkpoint/journal/sink paths. All312 before/after errors
and312 process exits verify native state/source/accepted output/dedup and the
next update after actual reopen. Short3-byte I/O and repeated EINTR obey copied
finite quotas. Process exits are not power-loss simulation. The predecessor
generation matrix now dynamically covers226 errors/228 process exits (two
already-absent candidate after-boundaries are recorded separately).

Audit pins228 executables,48 relevant unit objects,16 archives/four caches and488
compiler/link records plus the production control builds. All19 final matrix/
control receipt jobs are terminal with stdout archived. Strict C++23 warnings as
errors, assertions and sanitizer/leak settings hold; accepted builds have zero
diagnostics. No build overlaps CTest in its directory. Root owns acceptance;
Luna's follow-up review found no concrete prefix-promotion or ordering issue.

## Handoff

Prefix `build/verification/o06-history-retirement-native-` holds preimages-v1,
interim-v1,negative-objects-v1,independent-v1,controls,inputs-v1,final jobs,
matrix-audit-v1,root-review-v1,progress-v1,jobs-v1,checkpoint-seal-v1 and independent
post-seal-audit-v1. Final docs-only source2 adds this record and the API guide
(1100 paths). Verify seal/readback before edits.

Next run whole262+ and clean source-only integrated O04–O06 acceptance, including
invariants, crash/replay/native state/source/output/resource checks, then audit
the actual O05/O06 card requirements before verifying them. The legacy v1
unproven-prefix limitation and retained sink-file caps are explicit. O08 CLI,
A02 licensing, other Refactor cards and release gates remain open.
