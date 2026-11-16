# Complete physical R2 checkpoints

The [checkpoint API](../include/crown/recovery/sql_aggregate_checkpoint.hpp)
serializes the complete original physical bags and restores them through the
existing genuine cold factory. It stores no group/join/native-state mirror.
Filtered and unused rows, SQL NULL cells, empty original tables, source positions
and separate command/runtime frontiers survive reconstruction. This is the
checkpoint component of W06. [Actual WAL/sink files](sql_aggregate_files.md) supply
the lower durable transport owners; the upper [Session](sql_aggregate_session.md)
coordinates root publication and genuine replay. The separate [R2 JSONL/CLI path](sql_aggregate_input.md) now connects these primitives through Session.

The [implementation](../src/recovery/sql_aggregate_checkpoint.cpp) is an upper
recovery component. Ordinary update source/native/group code acquires no field,
handler or checkpoint maintenance work. Weighted aggregation context is P1 §7.3
in the [corrected paper/source map](code_review.md). Serialization, ownership,
budgets, rollback and file-authority rules are local engineering contracts.

## State and authority

The genuine [descriptor](sql_aggregate_descriptor.md) supplies original nullable
schemas, the actual source/native program and weighted binding, plus original
normal policies. Encode checks the source carrier's complete original binding,
source key, physical/source hashes, weighted binding, C and progress I. Public
SourceSnapshot fields remain editable data. Well-typed rows can still violate a
source constraint or aggregate arithmetic; the actual cold factory rejects such
images before exposing a restored runtime.

CheckpointMetadata binds query ID, descriptor hash, generation, physical C,
command I and a delivery-anchor DTO. It requires C≤I and the described anchor
sequence=C, nonzero byte extent and valid sink/hash fields. Progress.sequence is
I; it need not equal C after semantic Rejects. The optional reader position is
independent stream bytes/records: records≤I, and nonzero records require nonzero
bytes. Zero records may accompany consumed header/whitespace bytes.

The delivery DTO is not an actual sink Receipt. The codec cannot observe W or D.
The upper Session captures only at W=I,D=C, obtains the anchor from its
actual healthy R2 sink, and matches selected query/generation/descriptor/C/I/delivery
metadata against actual root/WAL/sink owners. `restore_checkpoint_into` matches
the caller's expected complete metadata before any receiving allocation, but a
caller-supplied expected DTO does not itself provide file-selection authority.

## Wire contract

The CROWNAC2 version1 frame uses the
[148-byte protected envelope](sql_aggregate_records.md#wire-contract) with magic
`CROWNAC2`, version1 and reserved zero. Length and body are protected by separate
SHA256 digests. The complete-frame SHA256 is the checkpoint's selected identity.
Frames are exact: trailing bytes, malformed complete data and unsupported versions
are rejected. No R1 checkpoint or signed-set row is reinterpreted.

| Body field, in order | Width / representation |
| --- | --- |
| Query ID, descriptor identity | 32, 64 lowercase ASCII hex bytes |
| Generation, C, I | Three unsigned little-endian 8-byte words |
| Delivery sink ID, sequence, extent, content identity | 32 bytes, two words, 64 bytes |
| Reader present, optional position | Flag1; if present bytes8 and records8 |
| Original source positions | Count8; each name length8/UTF8 bytes/offset8 |
| Original table count, physical row count | Two words |
| Physical entries | Table ID8, complete nullable row, positive weight8 |

A nullable row has field count8 and one presence byte per cell. Present values
use the existing exact scalar tags/representations for signed int64, UTF8 TEXT,
Boolean, canonical date and canonical fixed decimal. Every row must match its
actual original SqlTypes/nullability/domain and the configured field/string caps.
Physical weights are nonzero and within the original multiplicity domain. C0
requires zero physical rows; authentic static/global-empty state is reconstructed
from the descriptor once. UINT64_MAX is accepted as a terminal C without wrapping.

All original tables are identified by the genuine descriptor; the stored table
count must match, including tables with no rows. Entries are strictly ordered by
numeric TableId, then complete typed nullable row-wire bytes. Weight is excluded
from the key. Duplicate complete physical identities are rejected even with
different weights. This byte ordering is canonical transport order, not SQL sort
order. Original source names are nonempty UTF8 without U+0000, strictly ordered
and unique; source positions themselves are absolute uint64 data. Operational
monotonicity must be checked by the actual ingress owner before Input fsync.

## Lifecycle and ownership

Encoding validates and measures full row keys, then uses one packed accounted
key buffer plus one index vector to sort and reject duplicates. The packed key
buffer dies before final-frame allocation; the index vector remains through
writing. The count/write/hash passes share one codec
work grant. The writer records fixed metadata/statistics directly; no redundant
decode/rehash pass follows encoding. `Checkpoint` owns the receiving frame bytes;
moves preserve backing ownership and copying/rvalue borrowed views are forbidden.

Inspection validates the complete checksums, metadata, canonical source positions,
table count, exact nullable schemas, canonical row order and weights with only
fixed/transient borrowed values. No retained or covered C++ allocation occurs.
Input bytes must remain unchanged for the whole inspect/restore call. Fixed
ImageFailure carries wire/version/schema/work rejection; native source/constraint/
arithmetic/account errors retain their existing carriers. No new catch, retry or
undo framework is added.

Restore uses that full inspection and expected-metadata match first. It then owns
source names in AccountedInputProgress and materializes physical rows using one
reused reserved Cell scratch vector and one accounted owning Tuple per row.
Those temporary decoded tuples overlap the new live rows copied by the genuine
whole-image factory; this is bounded cold peak memory, not a retained row mirror.
All temporary decode rows die before return. Returned runtime/program/source
state and source-position names use the receiving account and survive wire/input
owner destruction.

The genuine cold factory re-lowers and checks source/native binding, validates
all final UNIQUE/FK constraints and arithmetic, and seeds one unpublished owner
at C−1 with one complete batch at C. C0 and static0/1 initialize once. It restores
the original normal policy/context after closing cold journals/grants/cursors.
The codec neither replays dummy epochs nor introduces a public sequence setter.

## Limits and cost

CheckpointLimits bound complete bytes, cumulative codec work, tables, rows,
fields, scalar extents, source count and name bytes. Work counts serialized byte
visits, charged comparison extents, TEXT validation and selected copy charges:
one unit per materialized cell plus each retained TEXT byte. It is not a count of
sizeof(Cell) memory-copy bytes, every CPU instruction or elapsed time. Row caps
apply to each structural pass; used work never resets between passes. Cold
source/native/indexed/group/lowering grants remain separate and cumulative as
specified by the existing build factory.

Encoding costs linear row/key-byte work plus O(R log R) complete-key comparisons;
scratch is O(key bytes+R). Inspection and decode are linear in admitted wire data
and selected comparisons/copies. Actual rebuild costs and peak decoded/live row
overlap are additional. There is no per-row allowance refill or normal update
overhead, and no constant-admission/public-delay theorem is claimed.

## Verification boundaries

[The native test](../tests/unit/sql_aggregate_checkpoint_test.cpp) covers complete
nullable joins, hidden grouping keys with equal rendered values, filtered/unused
bags, C/I divergence, progress/read positions, next exact output, both backends,
caps, corruption, C0/static/terminal state and genuine UNIQUE/FK/count-overflow
rejection of editable but well-typed images. [The wire verifier](../tests/integration/sql_aggregate_checkpoint_wire.py)
uses Python struct/date/hash rules to rebuild an entire emitted fixture independently.

The [SQL oracle](../tests/integration/sql_aggregate_runtime_oracle.py) now offers
`--checkpoint-every-epoch`, mutually exclusive with direct in-memory rebuild mode.
It reconstructs each native frontier from serialized physical rows before the
mature SQL comparison checks that state and the following atomic diff. Its
delivery anchors are explicit fixture DTOs, not claims of an actual sink/fsync.
Execution receipts and independent review are maintained separately from these
test descriptions; full durable recovery acceptance remains open.
