# O05 journal component — 10 November 2026

O05 remains in progress. This record verifies the maintained CROWNWAL/version1
codec, ordered-prefix validation and native borrowed-input adapter. Durable file
append, query commit/replay integration, crash-safe retirement/truncation and
output identity/deduplication remain required. The [contract](../journal.md) defines
this component; the [handoff](../handoff.md) records the full next scope.

Work is uncommitted at baseline
`e369a623517723b3be3ea3e9806779f3c591e7f9`. All1020 predecessor O04 source paths
were verified and preserved before changes. O04 remains verified on its frozen
[full acceptance](o04-native-acceptance-2026-11-10.md), not a claim about new WAL.

## Selected matrix

| Configuration | Tests | Seconds |
| --- | --- | ---: |
| GCC13 Debug | 54/54 | 23.33 |
| GCC13 Release | 54/54 | 3.87 |
| Clang18 Debug | 54/54 | 18.85 |
| ASan+UBSan/leaks | 54/54 | 93.24 |

All53 predecessor checkpoint/runtime/session/window/memory regressions remain.
The normal tree now registers241 tests; this component record covers the selected
54, not the full suite or fresh-source O05 acceptance. No predecessor assertion,
fixture, cap or timeout changed. All accepted builds have zero compiler
warnings/errors with actual C++23 strict warning flags and enabled test checks.
Sanitizer/leak settings were checked in generated test metadata.

Audit pins172 actual executables/four caches,12 changed translation-unit objects,
16 archives and376 compiler/link records. The journal test links production
`libcrown_runtime.a` without private runtime test macros. Both runtime variants
compile the implementation; the registered production test runs native API
capture/decode/prefix assertions. Every terminal CTest stdout is archived and all
37 current jobs are closed.

## Independent format and ownership evidence

Luna Max generated seven fixtures solely from the format specification, without
reading the C++ implementation. Frame lengths are624/284/255/237/201/177/177 bytes
(1955 total). Both body SHA and protected-prefix SHA are checked. Commit-bound
input-body SHA remains
`7dc08dba65898efde205ca8008e3b4b102e79c13f7fcdee0b52af9edfe3c9779`.
The generator, exact source hashes, format and fixture manifest are retained in
`tests/recovery/journal/`. The experimental CRWNWL00/version0 format is rejected.

Each mode checks1955 truncations and one-bit flip at every byte. Resealed malformed
kinds/scalars/booleans/source names/reader counters/CSV permutations and policy
fields reject without allocation. All seven encoder allocation positions and five
decoder positions are persistently denied; resident storage remains intact.
Exact/one-under record work/bytes and receiving memory limits pass. Retained
native rows, source names and CSV fields outlive destroyed encoded frames.
`Decoded::input_view()` borrows those native fields without allocation or ordinary
Row export; temporary owners cannot return this view or a source-name view.

A six-record1803-byte window prefix is checked at all1804 cuts, including empty
input and partial headers/bodies. It preserves separately committed physical and
accepted command sequences and retains pending command identity through partial
watermark commits. Whole and incremental processing have identical boundaries/
work; input SHA, ordinal and substep bind commits. Exact/one-under global bytes,
work and record caps pass, as do failure rollback and moved-cursor invalidation.
These are format/counter checks; actual query/domain admission and filesystem
persistence are separate obligations.

## Preserved public regressions

The first maintained source-work control supplies4096 malformed source bytes with
only512 admitted work bytes. Before the fix, UTF8 traversal reached corruption
before the quota check. The unchanged production-only control fails before and
passes after moving the validation charge ahead of visits on encode and decode;
NUL/UTF8 validation now shares one pass. A checksum-valid decoder case separately
exhausts work immediately before that validation visit. Fixed journal failures
carry their own diagnostic; real resource errors retain their original category.

A second public control copied a valid prefix report and reset its work counter.
The original stateless advance API accepted a frame that exceeded the real
cumulative ceiling. It is replaced by noncopyable Cursor with private copied
limits/expected binding and continuation state. Reports are detached values; no
constructor imports them. Snapshot tampering cannot reset the allowance, failed
feeds preserve private state, and moves invalidate the source. The old negative
ELF/source/log and the new passing public snapshot control are preserved. Both
fixes retain all previous tests. A separate control compilation caught two local
warning errors; the corrected control builds strictly and its raw failure log is
retained. No project warning flags were reduced.

## Receipts and remaining scope

Receipt prefix is `build/verification/o05-journal-native-`: jobs-v1, inputs-v1–v7,
preimages-v1, matrix-audit-v1, root-review-v1, both negative-input/control receipts,
positive-controls, final progress, seal and independent readback. Tested source6
pins1033 paths. Final source7 adds this record and the API contract, and changes
only documentation (1035 paths). The seal binds actual source, native code,
compiler/link metadata, raw stdout and public controls; independent readback
checks the final result. Root implemented the component; Luna Max supplied bounded
independent fixtures/read-only review. No Astra was used.

The ledger remains43 verified/3 in progress(A02/O05/O06)/32 not started,78 total.
The full Refactor.md goal is active. Next implement durable single-writer journal
I/O, initialization/append/sync/close/torn-tail repair and explicit indeterminate
failure states; integrate the prepared native query publication barrier and
reader/window replay; retire journal generations only after a durable compatible
checkpoint; prove replay output identity/deduplication; inject every persistence
boundary, then complete full/fresh O05 acceptance. O06 durable sinks remain separate.
