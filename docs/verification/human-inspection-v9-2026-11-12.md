# Input, recovery, windows, reports and IR inspection

This continuation adds 492 contracts after v8, reaching 5,300 contracts in 4,702
mapped blocks across 690 maintained files / 158,973 lines / 17,746 blocks.
Another 1,465 selected production blocks need individual cards (482 include,
926 src, 57 apps). Test/tool/example structural gaps remain separate. The full
Refactor goal and release reviews stay active.

The [block index](../code_specs/README.md) and [primitive cards](../code_specs/primitives.md)
give concrete usage, ownership, failure phases, costs and source references.
Integrated scopes are input/reader/native decoding, recovery files, windows and
session images, typed EXPLAIN capture/query serialization, and two IR headers.
Every substantive assigned scope has a card; this is not full repository review.

## The direct code cleanup

The JSON integer parser already rejects EOF/nondigits, then consumes either one
zero or a nonempty run of digits. No later operation rewinds its position. Its
final empty-span guard could never fire. Root removes that guard and its unused
begin capture; grammar, range, float/exponent and enclosing delimiter checks
remain. The [input review](../../build/verification/ingest-reader-human-review-v1/report.md)
and root proof retain the exact preimage, branch/caller argument and proposal.

Every other native edit is a comment correction/explanation with complete C++
and literal tokens equal. This batch adds or removes no handler, runtime field,
cache, wrapper, instrumentation or allocation layer. No timing improvement is
claimed. All three reader catches remain: consumed bytes can make decode/order/
allocation failure sticky, whereas engine rejection retains the cached event for
retry. Prepared acknowledgement advances after engine publication.

## Important boundaries

| Boundary | Usage, ownership and actual cost |
| --- | --- |
| Input | Public DTO decoding and funded native input have different allocation/error-presentation paths. Native retained data is prepared before acknowledgement. This is v1 full non-null set-event transport, not a W05 nullable/bag log or W06 protocol. |
| Recovery files | Prefix scans, checksum/copy work, locks, writes and synchronization are explicit. Pure comparison after successful read differs from uncertain I/O poisoning. Durable fsync can precede a failed stat; root-selection outcome does not describe every leftover file. |
| Windows | Duplicate labels maintain set presence with counts; full-row lookup is linear. Whole-watermark work/FIFO preparation precedes publication; active partial commands retain precharged work. Prepared nodes and acknowledgement follow native commit. |
| Session image | Structural inspection and receiver-owned materialization are separate. ValidatedSessionImage borrows unchanged bytes; public manifests do not replace later program/base/window admission. Metadata names require UTF-8; scalar row strings keep their raw-byte contract. |
| Typed reports | Original-query minimum-height context differs from selected incumbent/candidate tree matching and descriptive JSON. Legacy gauges read maintained sizes across node descriptors/source tables, allocate arrays and copy trace before final node-limit admission; they do not enumerate every resident row. Private v3 context omits that legacy traversal. |

See the [recovery review](../../build/verification/recovery-files-human-review-v1/report.md),
[window/image review](../../build/verification/window-image-human-review-v1/report.md)
and [capture/query review](../../build/verification/explain-capture-query-human-review-v1/report.md).
These allocator/codec/durability rules are local engineering contracts. Exact
paper provenance remains in [the review guide](../code_review.md); descriptive
records do not establish paper hypotheses or typed proof authority.

Root keeps the original [Luna IR draft](../../build/verification/ir-model-human-review-v1/README.md)
and corrects 59 cards before integrating all 65. Owning strings/vectors/sets and
deep scalar payload can allocate/copy proportionally to contents; public DTOs do
not automatically use a native query account. Public Decimal hashing can allocate
for canonical rendering. Borrowed program views do not retain backing; embedded
accounted layout/projection handles independently retain only their own metadata.
The contradiction flag defines an empty source query, not a proof about another
unmarked body. These specs change no native header bytes.

## Executed checks and checkpoint

Strict Debug passes 18/18 selected tests in 61.64 s; ASan/UBSan/leaks passes the
same 18 in 133.35 s. Both 18-target builds pass and all final receipts share the
same 1,127 maintained input pins with no drift. Controls cover ingestion normal/
failure/CLI fixtures, stream memory, generation/WAL/sink, windows/batch failure/
sequence/memory/checkpoint, session image/limits and query/composed EXPLAIN.
No new test mirrors the removed unreachable branch. Existing format, domain,
resource and integration cases verify admitted behavior.

Receipts: `build/verification/inspection-io-{build,test}-{debug,sanitizer}-v1.json`.
Raw terminal LastTest logs are archived. Source hashes, anchors, attachments and
references pass the standalone documentation checker. No full 323-test, release/
compiler matrix, W06 recovery or performance experiment is claimed.

Final seal: `build/verification/human-inspection-v9-progress-v1.json`; frozen
source: `build/verification/human-inspection-v9-source-v1`. Recipes, per-block
token proofs, corrected IR cards and native inventory are in
`build/verification/inspection-io-recovery-v1`. Earlier seals remain immutable;
main build paths remain active/reusable after preservation.

Ranking/reoptimization, batch/residual/cursor IO and runtime observation/memory
drafts remain unintegrated. The ranking draft's counter-overflow cancellation edge
needs its own controlled reproduction and changed-scope verification. They are
excluded from these counts and gates; complete human inspection remains open.
