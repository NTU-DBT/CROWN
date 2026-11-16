# Recovery interfaces, storage internals and IR primitives

This comment/specification continuation adds 409 contracts after
[v12](human-inspection-v12-2026-11-12.md), reaching 7,080 contracts in 5,842
mapped blocks across 692 maintained files / 159,363 lines / 17,819 blocks.
Another 517 selected production blocks need cards (90 include, 427 src, zero
apps); test/tool/example gaps remain separate. Structural coverage locates
code; it does not establish runtime correctness.

Use the [source index](../code_specs/README.md) and
[primitive contracts](../code_specs/primitives.md) to inspect each region's
usage, inputs/outputs, ownership, invariants, failure phase and actual cost.

## Integrated scopes

The [recovery/session header review](../../build/verification/recovery-session-headers-human-review-v1/report.md)
adds 265 contracts across twelve headers, covering all 119 substantive regions
and 91 selected scopes. Encoded/decoded buffers and native rows own actual
storage; artifact and pending-frame views borrow it. Receipt values do not
retain a File descriptor or account. HeaderMatch checks its defined identity
fields; a match is distinct from full record validation or durable authority.
Copied inspection/Scanned reports do not authorize Cursor continuation.

Failed Cursor work can be spent without publishing accepted prefix progress.
WAL versus sink File poison/state rules remain distinct. Typed File, receipt
and root-lock APIs retain their actual identities and publication boundaries;
plain DTO flags do not replace them. Fixed-message exception construction
avoids ordinary message strings, but throwing/unwinding still has C++ runtime
cost. No blanket allocation-free failure claim is made.

The [storage internals review](../../build/verification/storage-internals-human-review-v1/report.md)
adds 80 contracts, covers all 137 selected blocks and qualifies 15 earlier
cards among 77 existing scoped records. Numeric ID collision probes differ
from tuple/key hashing and payload comparisons. Actual visited nodes, scalar
work, conservative retirement and capacity reservations remain explicit.
Capacity work may be debited even when vector capacity already fits; no
allocation then occurs. Pointer-array growth overlaps old/new blocks until
initialization completes; releasing its trivial slot block does not traverse
capacity. Moving block/vector ownership preserves addresses; replacement or
release invalidates borrows into that storage.

The [root IR review](../../build/verification/ir-primitives-human-review-v1/report.md)
adds 64 contracts for Span/Set/JsonView, digest and model validation, covering
all 33 selected blocks. Bare views retain no owner. Unchecked range access
requires valid indices; at() adds the explicit bounds check. Set requires
sorted backing and does not enforce uniqueness. JsonView scalar getters
require exact kinds rather than coercing integers and doubles.

Public Decimal hashing can allocate text; successful fixed-array digesting
uses fixed scratch, while its owning string export allocates separately.
Digest cards cite the algorithm's constants, padding and rounds in
[FIPS 180-4, August 2015](https://nvlpubs.nist.gov/nistpubs/FIPS/NIST.FIPS.180-4.pdf#page=27).
This identifies the algorithm reference, not FIPS validation of this software.
CQ/catalog validation, row shape/type/decimal checks and collection constraints
remain separate. The narrow invalid_catalog translation and possible
valueless-Value rejection remain necessary. CROWN paper provenance stays in
[the review guide](../code_review.md); C++ ownership/account/codec contracts
are local engineering rules.

## Validation and preservation

Thirty-five concise comment edits add 53 source lines across the 26-file
scope. Root checks every primary/context pin and immutable manifest, complete
code-bearing block equality and whole-file C++/literal equality. The 15 old
prose updates are compared against their exact current baseline; unrelated
canonical work stays intact. No executable token, guard, handler, runtime
owner, allocation scheme or hot-path operation changes.

The [current reconciliation](../../build/verification/inspection-gap-inventory-v7/README.md)
matches all source hashes/line counts, resolves every canonical card in its
attached block and rejects duplicate/orphaned attachments. Generated-map and
current-guide links are checked separately.

Native execution remains preserved v11: 26/26 Debug and 26/26 ASan/UBSan/leak
checks, plus actual-entry allocation and process-I/O probes. No native tests
or builds are repeated for these token-identical comments, and no new native
build against current source bytes is claimed. Current native input keys and
all v11 artifacts are preserved. No timing or full-release claim is added.

Root proofs/recipes: `build/verification/inspection-recovery-storage-ir-v1`.
Corrected seal: `build/verification/human-inspection-v13-progress-v2.json`;
frozen source: `build/verification/human-inspection-v13-source-v2`.
The initial v1 preservation recipe omitted the three new review packets after
an incorrect path substitution. V2 preserves v1 and explicitly validates and
includes all three packet directories/manifests. The correction recipe and
audit are in `build/verification/inspection-recovery-storage-ir-evidence-v1`.
Source contracts and native execution scope are unchanged. Earlier seals remain
immutable. Input admission/binding, remaining report/input IO and remaining
public-interface drafts stay outside these counts. A separate unused-parser
removal proposal remains unapplied pending source review and native checks.
Full repository human review, W06 work and release acceptance remain open.
