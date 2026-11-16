# R2 physical-command and group-output records

The [public codec](../include/crown/recovery/sql_aggregate_records.hpp) encodes
nullable physical net commands, Commit/Reject decisions, and complete-key group
changes. It is a transport component. The [genuine descriptor factory](sql_aggregate_descriptor.md),
[complete physical checkpoint](sql_aggregate_checkpoint.md), and
[locked WAL/sink files](sql_aggregate_files.md) supply separate components. The
upper [Session](sql_aggregate_session.md) supplies selected-root ownership and
genuine recovery replay; The separate [R2 JSONL/CLI path](sql_aggregate_input.md) now connects these primitives through Session. R1 formats retain their meaning.

The code is split into [record validation/encoding](../src/recovery/sql_aggregate_records.cpp)
and a [small WAL state machine](../src/recovery/sql_aggregate_wal.cpp). The codec
uses the real immutable SQL aggregate program for physical column types, complete
group-key types, and projected output types. A descriptor hash identifies a
separately admitted descriptor; it cannot authorize an editable program DTO.

The weighted aggregation context is P1 §7.3, equations (10)–(14), in the
[corrected paper/source map](code_review.md). NULL representation, byte formats,
budgets, ownership, WAL ordering and recovery are local engineering contracts.
They are not paper theorems. See the [aggregate runtime](sql_aggregate_runtime.md)
and [whole-image cold factory](sql_source_images.md) for native semantics.

## Wire contract

Every integer is unsigned little endian unless its scalar tag specifies a signed
bit representation. Every hash/ID is fixed-width lowercase ASCII hex. Frames are
exact: appended bytes are rejected. The length-bearing prefix has its own hash.

| Offset | Width | Meaning |
| --- | --- | --- |
| 0 | 8 | `CROWNAG2` |
| 8 | 2 | Family format version 1 |
| 10 | 2 | Reserved zero |
| 12 | 8 | Body byte length |
| 20 | 64 | SHA256 of complete body |
| 84 | 64 | SHA256 of bytes 0–83 |
| 148 | 1+8 | Kind tag, record ordinal, then kind-specific payload |

| Tag | Payload, in wire order |
| --- | --- |
| 0 WalHeader | query ID32, descriptor hash64, generation8, checkpoint hash64, C8, I8 |
| 1 Input | I8, replacement count8, replacements, source flag1 and optional name length8/name/offset8, reader flag1 and optional bytes8/records8 |
| 2 Commit | input ordinal8, input body hash64, I8, C8, complete output frame length8, complete output frame hash64 |
| 3 Reject | input ordinal8, input body hash64, I8, C8, reason1 |
| 4 SinkHeader | query ID32, descriptor hash64, sink ID32, base C8 |
| 5 GroupEpoch | generation8, input I8, C8, input body hash64, changed1, group_changed1, change count8, changes |

A replacement contains table ID8, one complete nullable row, before weight8 and
after weight8. Preserve input order: duplicate physical row replacements may form
an exact chain. Weight/domain/UNIQUE/FK/arithmetic decisions remain the genuine
runtime's job; the codec does not silently turn them into transport rejection.

A row is field count8 followed by cells. A cell starts with presence1. Zero is SQL
NULL; one is followed by the existing scalar encoding: tag0 signed int64 bits8,
tag1 UTF8 byte length8/data, tag2 Boolean1, tag3 signed epoch-day bits4, or tag4
canonical decimal text length1/data. Every presence/Boolean flag is exactly 0/1.
Values must fit the declared SQL type, nullability and decimal specification.
TEXT excludes U+0000 and malformed UTF8. Scalar tags alone do not describe SQL
types.

A group change contains its complete key row, before-presence1 and optional value
row, then after-presence1 and optional value row. An absent tuple differs from a
present tuple with NULL cells. At least one value row must exist; a present
before/after pair must differ. Changes are strictly ordered by complete encoded
key bytes, including nullable presence, type tags and lengths. Duplicate keys
are rejected. Distinct keys may have identical projected values. An empty epoch
still has a complete 255-byte frame and closes its transport epoch when the actual
sink owner confirms it. The ordering is a canonical byte order, not SQL collation order.

Reject reasons 0–5 are weight mismatch, source overflow, UNIQUE violation, FK
violation, aggregate overflow and annotation overflow. There is no resource or
contract-failure tag. The upper Session maps only the supported genuine semantic
errors and reproduces them during recovery.

## Ownership, failure and cost

`inspect` borrows unchanged bytes for its call and allocates no retained or
ordinary C++ storage. It validates both hashes, exact structure, complete nullable
schemas and canonical group ordering before returning fixed metadata. Fixed
`ImageFailure` carries malformed/version/binding/scalar/limit/work rejection;
allocation failures propagate from owning factories. The codec installs no
catch, retry loop, rollback journal or mutable runtime field.

`encode_input` funds one immutable frame plus two flat arrays: cells and
replacement descriptors. Cell TEXT and source names borrow the owned frame.
Moves preserve the backing allocation addresses. Borrowed views require a live,
unmoved owner; rvalue views and copying are forbidden. External-byte
`decode_input` first validates the entire record, then copies the frame and
materializes those flat arrays. All retained storage uses the receiving account.
The command can directly supply `prepare_batch({C+1, owned.view().replacements})`;
the coordinator must validate sequencing and log/sync before calling prepare.

Encoding uses one count/validation pass and one funded write pass. Group encoding
also builds one packed key buffer and one index vector, sorts the indexes, rejects
duplicates, then writes the canonical frame. It adds no per-group owning key
allocation. Normal runtime updates do not call this upper target. Input encode
and inspect take O(B+F) byte/field work; group sorting additionally takes
O(K log K) key comparisons with compared byte extents charged. Temporary storage
is O(key bytes+K); retained output is one O(B) frame. These are algorithmic costs,
not CPU measurements or a claim about an entire durable session.

Finite per-record limits cover bytes, cumulative work, tables, rows, fields and
scalar/source text. Work counts serialized byte visits in every parse/write/hash
pass, UTF8 validation visits and charged comparisons. Multiple passes share the
same allowance. Row counts are per structural pass; work is never reset between
passes. Native source/group/indexed/build grants remain separate.

## WAL state machine

`WalCursor` accepts complete frames and owns fixed-size validation state only.
The first record must be WalHeader at ordinal0; later ordinals are contiguous.
It checks input body identity and separate W/I/C frontiers. Feed validates into a
fixed local candidate and publishes it only after success. A failed feed leaves
the previous validated state intact; callers may not treat this as an I/O
uncertainty or tail-repair decision.

| Record | Required state | Result |
| --- | --- | --- |
| Input | No pending head; I and C have successors; input I=old I+1 | W=I+1; remember one pending identity; sink floor=old C |
| Commit | Exact pending identity; I=pending I; C=old C+1 | I advances, C advances, pending clears |
| Reject | Exact pending identity; I=pending I; C=old C | I advances, C stays, pending clears |

C≤I≤W and W−I≤1 hold. The header starts W=I at checkpoint C/I. The cursor derives
the sink floor because a correct writer admits each new Input only at actual
D=C. Recovery must check that the actual sink satisfies floor≤D≤final C and
reproduce every decision/output through the genuine runtime. This codec cannot
observe D or prove the writer performed fsync. A final pending Input requires
D=final C; otherwise at most the last committed epoch may be missing. All scan
bytes, work and record admissions are cumulative. UINT64_MAX frontiers are
terminal without wrapping arithmetic.

## Inspection and verification

[The fixture generator](../tools/generate_sql_aggregate_record_fixtures.py) uses
only Python struct/integer/hash/date operations. Its seven full-byte goldens are
checked by [the native test](../tests/unit/sql_aggregate_records_test.cpp), alongside
ownership/native-use, NULL/full-key ordering, truncation/bit corruption,
checksum-valid malformed records, allocation-site cuts, exact budgets, and
Reject-induced I/C divergence. Execution evidence is recorded separately; test
existence alone does not establish execution or durable acceptance.
