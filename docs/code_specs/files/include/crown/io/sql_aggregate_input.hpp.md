# `include/crown/io/sql_aggregate_input.hpp` — block usage map

[Source](../../../../../../include/crown/io/sql_aggregate_input.hpp) · [Source index](../../../../README.md) · [Subsystem contracts](../../../../subsystem_contracts.md) · [Reviewed primitives](../../../../primitives.md)

Admit bounded external documents/records and serialize explicit public representations at the engine boundary.

Snapshot SHA-256: `9a4ea634f8d11ec879ac4c47c5503f4f0fb4489dabebf72e183ecc954d670935`. 55 lines partitioned into 7 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [io](../../../../subsystem_contracts.md#io). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/ingestion.md](../../../../../ingestion.md), [docs/query_identity.md](../../../../../query_identity.md), [docs/schema_evolution.md](../../../../../schema_evolution.md), [docs/cli.md](../../../../../cli.md), [docs/query_memory.md](../../../../../query_memory.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–8](../../../../../../include/crown/io/sql_aggregate_input.hpp#L1) | Imports dependencies; guards repeated header inclusion; declares namespace scope. | source comment (unverified): // Transport admissions from the original stream origin. JSON parsing workspace · [reviewed contract](#b0001) |
| [B0002 · 9–13](../../../../../../include/crown/io/sql_aggregate_input.hpp#L9) | Type/record definition: struct SqlAggregateJsonlLimits | source comment (unverified): // Transport admissions from the original stream origin. JSON parsing workspace · [reviewed contract](#b0002) |
| [B0003 · 14–16](../../../../../../include/crown/io/sql_aggregate_input.hpp#L14) | Explanatory comments or spacing. | source comment (unverified): // One validated physical command. Flat cell/text/edit buffers own every borrow; · [reviewed contract](#b0003) |
| [B0004 · 17–31](../../../../../../include/crown/io/sql_aggregate_input.hpp#L17) | Type/record definition: class SqlAggregateJsonCommand | source comment (unverified): // One validated physical command. Flat cell/text/edit buffers own every borrow; · [reviewed contract](#b0004) |
| [B0005 · 32–37](../../../../../../include/crown/io/sql_aggregate_input.hpp#L32) | Explanatory comments or spacing. | source comment (unverified): // The stream must already point at origin.bytes. The schema is a genuine frozen · [reviewed contract](#b0005) |
| [B0006 · 38–54](../../../../../../include/crown/io/sql_aggregate_input.hpp#L38) | Type/record definition: class SqlAggregateJsonlReader | source comment (unverified): // The stream must already point at origin.bytes. The schema is a genuine frozen · [reviewed contract](#b0006) |
| [B0007 · 55–55](../../../../../../include/crown/io/sql_aggregate_input.hpp#L55) | Closes surrounding scope/type. | source comment (unverified): // namespace crown::io · [reviewed contract](#b0007) |

## B0001

[Lines 1–8](../../../../../../include/crown/io/sql_aggregate_input.hpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L1-L8:sha256:1395cc756213d63fa5fc3f1f2eab9afa37f5ca6017d1578abaa16ad79c09d3ef
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Header guard and aggregate-record/istream dependencies, followed by crown::io namespace opening for the JSONL transport command and reader. Embedded source note records intended usage: Transport admissions from the original stream origin. JSON parsing workspace is separate; retained line/command storage uses the supplied receiving account. Treat that prose as guidance, not as independently verified executable behavior. |
| inputs / outputs | No runtime inputs/outputs are declared by the import/scope lines themselves. |
| invariants | The header guard prevents repeat inclusion in a translation unit; imported declarations determine compile-time names. The note/type comments in this span are guidance and do not add runtime validation or a capability. |
| ownership | No object ownership is created by the imports or namespace tokens. |
| failure | No runtime failure path is introduced by the guard/imports; incompatible or missing declarations fail during compilation or linking. |
| cost | Preprocessor/compiler work only for these lines; the guard adds no per-operation runtime work. |
| Design | [include/crown/io/sql_aggregate_input.hpp](../../../../../../include/crown/io/sql_aggregate_input.hpp), [docs/code_specs/files/include/crown/io/sql_aggregate_input.hpp.md](sql_aggregate_input.hpp.md), [docs/sql_aggregate_input.md](../../../../../sql_aggregate_input.md), [docs/sql_aggregate_records.md](../../../../../sql_aggregate_records.md) |

## B0002

[Lines 9–13](../../../../../../include/crown/io/sql_aggregate_input.hpp#L9); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct SqlAggregateJsonlLimits {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Declare the finite admission limits used by the JSONL reader. |
| inputs / outputs | The caller supplies per-record and per-field byte limits, optional source-name bytes, replacement count, total cell count, cumulative input bytes and record count. Defaults are 1 MiB record/field, 4 KiB source, 65,536 replacements, 1,000,000 cells, 1 GiB bytes and 1,000,000 records. |
| invariants | Counters start at the supplied ReaderPosition origin. Framing counts LF/CRLF in cumulative bytes; record_bytes excludes LF and one trailing CR. Limits bound logical extents, not vector capacity, growth overlap or JSON parser workspace. |
| ownership | This value object owns no input or buffer. The reader copies the limits; accounted line and command allocations use the supplied receiving MemoryAccount. JSON DOM, duplicate-key sets and lexer/parser workspace remain ordinary allocations outside that account. |
| failure | A record_bytes value of SIZE_MAX is rejected at reader construction; exceeded caps fail during next() and poison that reader. Invalid origin progress is rejected separately. This struct itself performs no validation. |
| cost | The struct adds no runtime work. Enforcing caps is proportional to consumed bytes, parsed fields/cells and replacements; retained capacity is charged by actual account requests. No RSS or parser-workspace total follows from these fields. |
| Design | [docs/sql_aggregate_input.md §One atomic JSONL command](../../../../../sql_aggregate_input.md), [docs/sql_aggregate_input.md §Ownership, failure and cost](../../../../../sql_aggregate_input.md), [apps/crown/aggregate.cpp §help limits and resume text, lines 71–85](../../../../../../apps/crown/aggregate.cpp), [docs/query_memory.md §Boundaries](../../../../../query_memory.md) |

## B0003

[Lines 14–16](../../../../../../include/crown/io/sql_aggregate_input.hpp#L14); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L14-L16:sha256:859d9abad791fe7ddf052f87d06238de33f7d63a9bf38b58c3aea5381689cc76
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Design note for adjacent code: One validated physical command. Flat cell/text/edit buffers own every borrow; moving the owner preserves their heap addresses. No native decision is made. This is caller guidance recorded as prose, not an executable result. |
| inputs / outputs | No runtime interface is implemented by these comment-only lines. They sit at include/crown/io/sql_aggregate_input.hpp lines 12-18; the surrounding declaration/body defines its own inputs and outputs. |
| invariants | The words record the intended use boundary only. They do not add a guard, proof, capability, transaction, durability guarantee, or account charge; verify behavior in the referenced implementation. |
| ownership | Comment text owns no data. Object lifetimes, borrows, and account attribution remain those of the adjacent source objects and their constructors. |
| failure | No failure path is implemented here. Any mentioned failure or recovery rule belongs to the adjacent operation and its existing error carrier. |
| cost | No runtime work is performed by these lines; any cost/bound in the note is not certified by this comment-only card. |
| Design | [include/crown/io/sql_aggregate_input.hpp](../../../../../../include/crown/io/sql_aggregate_input.hpp), [docs/code_specs/files/include/crown/io/sql_aggregate_input.hpp.md](sql_aggregate_input.hpp.md), [docs/sql_aggregate_input.md](../../../../../sql_aggregate_input.md), [docs/sql_aggregate_records.md](../../../../../sql_aggregate_records.md) |

## B0004

[Lines 17–31](../../../../../../include/crown/io/sql_aggregate_input.hpp#L17); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
class SqlAggregateJsonCommand {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Own one validated physical command whose InputView can be borrowed synchronously by Session::log(). |
| inputs / outputs | A successful reader decode returns sequence, replacements, optional source position and reader continuation through view() on an lvalue command. |
| invariants | The command is move-only, its view() is lvalue-qualified, and no native commit or semantic decision is made by decoding. Cell/source string views and replacement spans point into the command owner’s flat buffers. |
| ownership | The private accounted Data owns flat TEXT, cells and replacement descriptors under the receiving account. A command may outlive the reader, stream and temporary JSON DOM; moving the owner preserves its allocated backing addresses. |
| failure | view() on a moved-from owner raises invalid_input_state; the diagnostic is constructed on this failure path. Copying and rvalue view are disallowed at compile time. |
| cost | Moving transfers ownership without copying payloads. Constructing InputView is constant-size borrowing; retaining/copying it beyond the command lifetime is invalid. Command destruction releases its account-backed buffers. |
| Design | [docs/sql_aggregate_input.md §One atomic JSONL command](../../../../../sql_aggregate_input.md), [docs/sql_aggregate_input.md §Ownership, failure and cost](../../../../../sql_aggregate_input.md), [docs/sql_aggregate_records.md §Wire contract](../../../../../sql_aggregate_records.md), [docs/sql_aggregate_records.md §Ownership, failure and cost](../../../../../sql_aggregate_records.md), [docs/sql_aggregate_session.md §State and command usage](../../../../../sql_aggregate_session.md), [include/crown/recovery/sql_aggregate_session.hpp §Session log/decide/deliver declarations, lines 81–85](../../../../../../include/crown/recovery/sql_aggregate_session.hpp) |

## B0005

[Lines 32–37](../../../../../../include/crown/io/sql_aggregate_input.hpp#L32); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L32-L37:sha256:bbf6b0307324bd4eecc6c56cc2f41c1b3bd10c4d377943aae1db4ffb8fd40329
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Design note for adjacent code: The stream must already point at origin.bytes. The schema is a genuine frozen program; JSON must bind its complete identity and each physical table version. next() owns one command, checks W+1, and records the next unread logical byte. Failure latches requires_reopen before consuming input, without catch/retry wrappers. Reopen from durable logged W/reader progress, not disposed I alone. This is caller guidance recorded as prose, not an executable result. |
| inputs / outputs | No runtime interface is implemented by these comment-only lines. They sit at include/crown/io/sql_aggregate_input.hpp lines 30-39; the surrounding declaration/body defines its own inputs and outputs. |
| invariants | The words record the intended use boundary only. They do not add a guard, proof, capability, transaction, durability guarantee, or account charge; verify behavior in the referenced implementation. |
| ownership | Comment text owns no data. Object lifetimes, borrows, and account attribution remain those of the adjacent source objects and their constructors. |
| failure | No failure path is implemented here. Any mentioned failure or recovery rule belongs to the adjacent operation and its existing error carrier. |
| cost | No runtime work is performed by these lines; any cost/bound in the note is not certified by this comment-only card. |
| Design | [include/crown/io/sql_aggregate_input.hpp](../../../../../../include/crown/io/sql_aggregate_input.hpp), [docs/code_specs/files/include/crown/io/sql_aggregate_input.hpp.md](sql_aggregate_input.hpp.md), [docs/sql_aggregate_input.md](../../../../../sql_aggregate_input.md), [docs/sql_aggregate_records.md](../../../../../sql_aggregate_records.md) |

## B0006

[Lines 38–54](../../../../../../include/crown/io/sql_aggregate_input.hpp#L38); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
class SqlAggregateJsonlReader {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Read one bounded JSONL command at a time against a genuine frozen SQL aggregate program and durable input progress. |
| inputs / outputs | Construction borrows an already positioned stream and receives the account, genuine program, logged W, byte/record origin and limits. next() yields an owning command or clean EOF; position() returns successful reader progress; requires_reopen() exposes the poison state. |
| invariants | The record binding must equal the genuine program identity, physical source/schema and complete row types must match, and each decoded sequence must equal logged W+1. The reader validates transport only; Session remains the authority for logging, native preparation, Reject/Commit and delivery. |
| ownership | Reader state retains a stream reference, account, frozen program and accounted raw-line buffer. The caller must keep the stream alive and positioned at origin.bytes. It is move-only and holds no decoded command after next() returns. |
| failure | Any framing, JSON, binding, row, limit, I/O or allocation failure after next() begins leaves the reader requiring reopen. Reopen from durable logged W and reader progress; do not retry the partially consumed stream in place. Clean EOF is repeatable. |
| cost | Framing reads through a single LF or EOF without relying on stream read-ahead; retained line capacity and returned command buffers use the account. JSON DOM and parser workspace are outside it. Decode scans bytes/cells/replacements and physical-source lists; no delay theorem is claimed. |
| Design | [docs/sql_aggregate_input.md §One atomic JSONL command](../../../../../sql_aggregate_input.md), [docs/sql_aggregate_input.md §Ownership, failure and cost](../../../../../sql_aggregate_input.md), [docs/sql_aggregate_input.md §Workflow](../../../../../sql_aggregate_input.md), [docs/sql_aggregate_session.md §State and command usage](../../../../../sql_aggregate_session.md), [apps/crown/aggregate.cpp §run reader/session loop, lines 167–190](../../../../../../apps/crown/aggregate.cpp), [docs/query_memory.md §Boundaries](../../../../../query_memory.md), [schemas/sql-aggregate-input-v1.schema.json](../../../../../../schemas/sql-aggregate-input-v1.schema.json), [apps/crown/aggregate.cpp §seek continuation line-boundary guard, lines 141–155](../../../../../../apps/crown/aggregate.cpp) |

## B0007

[Lines 55–55](../../../../../../include/crown/io/sql_aggregate_input.hpp#L55); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L55-L55:sha256:39c2bd587239794e92def2b2ebc5cce8f0acd397d817bceec761a8f61bea3e66
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Closes the namespace crown::io at this source boundary; this is a lexical delimiter, not an operation. |
| inputs / outputs | No runtime input or output. Declarations following the span leave the preceding C++ scope. |
| invariants | The delimiter ends the preceding scope's visibility/linkage region; it adds no validation, publication, ownership transfer, or runtime authority. |
| ownership | The delimiter adds no owner. If it ends a function/block with live automatic objects, their normal destructors release those objects; namespace and type-definition closes change no existing object's lifetime. |
| failure | No explicit failure translation or catch is added. If a function/block exit destroys automatic objects, exception behavior follows those destructors; namespace/type closes have no runtime failure path. |
| cost | The delimiter adds no algorithmic work. A function/block exit can run existing automatic-object destructors and cleanup; namespace/type closes have no runtime cost. |
| Design | [include/crown/io/sql_aggregate_input.hpp](../../../../../../include/crown/io/sql_aggregate_input.hpp), [docs/code_specs/files/include/crown/io/sql_aggregate_input.hpp.md](sql_aggregate_input.hpp.md), [docs/sql_aggregate_input.md](../../../../../sql_aggregate_input.md), [docs/sql_aggregate_records.md](../../../../../sql_aggregate_records.md) |
