# Runtime and storage header usage contracts

This comment/specification continuation adds 518 contracts after
[v11](human-inspection-v11-2026-11-12.md), reaching 6,671 contracts in 5,621
mapped blocks across 692 maintained files / 159,310 lines / 17,816 blocks.
Another 702 selected production blocks need individual contracts (198 include,
504 src, zero apps). Test/tool/example structural gaps remain separate.

The [block index](../code_specs/README.md) and
[primitive cards](../code_specs/primitives.md) give usage, inputs/outputs,
invariants, ownership/lifetime, failure and actual cost for each reviewed
region. Structural coverage alone is not a semantic or runtime proof.

## Two integrated reviews

The [runtime header review](../../build/verification/runtime-session-window-inspection-headers-human-review-v1/report.md)
adds 365 individual contracts for inspection, memory reports, statistics,
session and window APIs. It covers all 124 substantive regions and 91 selected
scopes. Ordinary owning DTOs differ from native funded rows and shared immutable
graphs. SessionSnapshot shares funded result rows but can allocate copying its
ordinary exported progress map/text. Native window checkpoint rows are move-only;
explicit checkpoint cloning pays for new row storage. Returned references and
spans borrow their backing. A shared owner's last release can destroy its graph.

Creator-thread and nonreentrant guards, quiescent snapshot/checkpoint barriers,
accepted source/window sequence domains and actual file/receipt/root-lock
authority are explicit. Mutable status or checkpoint flags grant no authority.
WAL decisions and uncertain durable publication retain their actual recovery
rules. Sink epoch index lookup is constant; subsequent frame read, hashing,
validation, decoding and native allocation scale with the frame.

The [storage header review](../../build/verification/storage-primitives-human-review-v1/report.md)
adds 153 contracts and preserves all 22 existing scoped cards. It covers all
102 selected blocks, including 89 previously uncovered blocks. Accounted
layout/projection/tuple owners differ from ordinary standalone containers,
borrowed cursor entries and explicit payload pins. Native cursors check facade
liveness; standalone journals can keep State alive after the facade disappears.
Pins preserve immutable payload, not index membership or cursor validity. The
last pin of a closed arena can release its high-water metadata.

Root directly checks the work grant and tuple-view boundaries. All five budget
comparisons must precede subtraction; default aggregate ordering is lexicographic
and cannot replace componentwise admission. Optional grant access and required
dereference have different empty-owner behavior. Tuple-derived views/iterators
retain their payload; explicit borrow views and exported native/legacy adapters
do not gain ownership. Iterator copying can perform shared reference operations
without materializing a row. Legacy Decimal hashing may allocate its text form.

The headers contain no catches. Existing fixed/legacy diagnostics, canonical
grant rules and public/native validation boundaries remain. No new data
structure, query state, observer, cache, allocation, retry or runtime check is
introduced. The comments explain the existing costs without claiming they are
total CPU, RSS or whole-runtime bounds. Paper links remain scoped through
[the review guide](../code_review.md); these ownership/API rules are local
engineering contracts.

## Source and documentation validation

Twenty-eight concise comment edits add 48 lines across the 23-header scope.
Root verifies every primary base pin, both immutable review manifests,
whole-file C++/literal token streams and every complete code-bearing mapped
block. Comment-only structural ranges may differ. All prior unrelated cards
remain; the 22 old storage cards change only their reviewed source hashes.
No executable token changes.

The separate D1 correction updates [session lifecycle](../session_lifecycle.md):
its historical O04-future sentence now points to implemented checkpoint,
session-journal and generation recovery guides. Exact current method evidence
supports the correction; it is separate from the C++ token comparison.

The [current reconciliation](../../build/verification/inspection-gap-inventory-v6/README.md)
checks every current source hash/line count, resolves all 6,671 canonical cards
inside their attached blocks and detects duplicate/orphaned attachments.
Generated-map links and current-guide links have separate offline checks.

Native execution remains the preserved v11 scope: 26/26 Debug and 26/26
ASan/UBSan/leak checks, plus actual-entry persistent-C++-OOM and process-I/O
probes. V12 does not rerun native tests for token-identical comment changes and
does not claim a new native build against these different source bytes. Current
native input keys are unchanged; every changed native input is a reviewed header
with equal C++/literal tokens. V11 native artifacts and archived logs remain
preserved observations. No new timing or full-release claim is made.

Root recipes/proofs: `build/verification/inspection-header-contracts-v1`.
Seal: `build/verification/human-inspection-v12-progress-v1.json`; frozen source:
`build/verification/human-inspection-v12-source-v1`. Earlier seals stay immutable.
Recovery/session public header and storage implementation drafts remain outside
these counts. Repository-wide human review, W06 work and release acceptance
remain open.
