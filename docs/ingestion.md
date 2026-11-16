# Physical input codecs and ordered replay (O01)

Status: O01 is implemented and verified. Independent Astra source review and
all 69 tests pass GCC Debug/Release, ASan/UBSan, Clang and a fresh source-only
build; see the [evidence packet](verification/physical-input-2026-11-06.md) and
[495-input manifest](verification/physical-input-sources.sha256). The
[D06 packet](verification/delta-lifecycle-2026-11-06.md) records the preceding
verified snapshot; its historical hashes do not describe these new files.

The API is [ingest.hpp](../include/crown/io/ingest.hpp), implemented in
[ingest.cpp](../src/io/ingest.cpp) and
[ingest_text.cpp](../src/io/ingest_text.cpp). Native retained decoding is in
[event_reader.cpp](../src/io/event_reader.cpp) and
[native_decode.cpp](../src/io/native_decode.cpp). Commit-coupled replay is
[replay.hpp](../include/crown/runtime/replay.hpp) /
[replay.cpp](../src/runtime/replay.cpp). Input names physical source tables
and retains every declared column. The physical runtime performs occurrence
adaptation, filtering, projection-support counting and atomic alias fan-out.
The codec never substitutes logical aliases or projected witness rows.

## Version-1 JSONL event

Each line is one JSON object with exactly these required fields:

| Field | Meaning |
| --- | --- |
| `schema_version` | Input codec version, currently integer 1; independent of CQ/plan document versions. |
| `catalog_version` | Exact supplied catalog version. |
| `source_schema_version` | Exact source table's version. |
| `catalog_sha256` | Lowercase SHA-256 of compact canonical `write_catalog(catalog)` JSON, including all metadata. `input_catalog_sha256` computes it. |
| `sequence` | Positive uint64 event sequence; streams continue contiguously after their accepted progress. |
| `table` | Exact physical catalog name, preserving case. |
| `operation` | Exactly `insert` or `delete`; replacement/UPDATE and net batches are separate unsupported operations. |
| `values` | Complete row in source column order, with exact F01 types and decimal specification. |

Optional `source_position` has exactly `source` and `offset`. Source is a
nonempty UTF-8 string without NUL; offset is uint64, including zero. Provided
offsets strictly increase independently for each source; gaps and interleaving
sources are allowed. There is no ordering comparison between different
sources. An absent position makes no source-offset claim.

Typed scalars use existing [F01 encodings](scalars.md): int64 JSON integer
tokens, UTF-8 strings, booleans, `{"date":"2024-02-29"}` and
`{"decimal":"1.25"}`. Dates/decimals are never implicitly read from raw
strings or binary floats. JSON `null`, floating integer tokens such as `1.0`,
out-of-range integers, unknown/duplicate fields, wrong arity/types, unsupported
versions and mismatched source/catalog bindings fail. String values preserve
embedded NUL through JSON escaping. Identifiers are not case-folded by input.

[physical-update-v1.schema.json](../schemas/physical-update-v1.schema.json)
describes structural JSON shape. Native validation additionally checks catalog
identity, exact numeric tokens, UTF-8, calendar/decimal domains, row layout,
resource limits and stream order. Schema validation alone is not admission.

`write_input_json` writes a compact object without a line terminator.
`read_input_json` accepts one complete JSON document. `EventReader` JSONL
accepts LF/CRLF and a final record without a terminator; blank records fail.
`record_bytes` bounds the encoded object, excluding its LF/CRLF framing.
`total_bytes` and `bytes_read()` include all raw framing bytes.

## Version-1 binary frame

Each record has independent framing; concatenation is a stream. Integers use
little endian, with signed int64 values encoded as their 64 two's-complement
bits. There is no native-pointer, host-endian or ABI struct serialization.

| Order | Encoding |
| --- | --- |
| Header | Eight ASCII bytes `CROWNUPD`, uint16 version 1, uint32 payload byte length. |
| Binding | uint64 catalog version, uint64 table source version, 64 ASCII catalog-hash bytes. |
| Event | uint64 sequence, uint32 table-name byte length + UTF-8 bytes, one-byte operation (1 insert / 2 delete). |
| Position | One-byte presence (0/1); if present, uint32 source byte length + UTF-8 bytes, then uint64 offset. |
| Row | uint32 number of values, followed by tagged scalar payloads below. |

| Tag | Payload |
| --- | --- |
| 0 | Eight int64 bits as above. |
| 1 | uint32 byte length + exact UTF-8 string bytes. |
| 2 | One Boolean byte, only 0 or 1. |
| 3 | Exactly ten ASCII bytes `YYYY-MM-DD`, with valid finite Gregorian date. |
| 4 | uint32 byte length + canonical exact decimal text. |

Binary decimals must already be canonical; JSON/CSV input may use any valid
F01 decimal spelling before canonicalization. Unknown tags/flags, trailing
bytes, wrong row count, truncation, impossible lengths, mismatched bindings and
unsupported versions fail. The frame size is checked before a declared large
payload allocation, and field counts are checked against schema and remaining
payload before row reservation. `record_bytes` includes the 14-byte header.
This framing is not an authenticated transport or a checkpoint/crash protocol.

## CSV and explicit legacy profiles

`InputOptions` selects a format. CSV needs a physical `table`, and emits a
fixed `csv_operation` (insertion by default). With `header=true`, the first
record must name every source column exactly once; permutation is allowed.
Without a header, the declared source column order is mandatory. Empty files
have no events. Nullary tables use an empty CSV record/header. No source
columns, including unused query columns, are dropped.

Delimiters are explicitly configured single ASCII bytes except quote, CR, LF
and NUL; comma is default, pipe/tab/semicolon are supported. The reader handles
doubled quotes, quoted delimiters and embedded newlines, LF/CRLF, and EOF final
records. It rejects unquoted quotes, trailing text after a closing quote,
unterminated quotes and bare CR outside quotes. Strings are exact UTF-8 with
no trimming. Integers allow an ASCII sign and digits only; booleans are exactly
`true`/`false`. Date/decimal use their strict F01 parsers and column policies.

There is no guessed NULL spelling. Empty or `\N`/`NULL` text remains literal
in string columns and fails unsupported scalar domains as appropriate.
An upstream SQL-NULL sentinel must be declared with `null_token`; matching
values then fail explicitly because the current engine has no NULL value.
Declare that policy for sources such as SNB rather than interpreting their
NULLs as joinable strings.

| Profile | Literal record / configuration |
| --- | --- |
| `legacy_signed` | `+,u,v` or `-,u,v`; one explicit physical table. |
| `legacy_relations` | `+,G,u,v` / `-,V1,u`; explicit token→physical-table mapping, no fallback for unknown tokens. |
| `legacy_insert_only` | `u,v`; explicitly unsigned insert-only input, never guessed from another profile. |
| `legacy_flags` | `1,u,v` insert / `0,u,v` delete; flag-first, explicit physical table. |
| `legacy_timestamp_flags` | `timestamp|1|u|v` / `timestamp|0|u|v`; explicit table and source ID, pipe delimiter selected explicitly. Timestamp is retained verbatim as source offset and must increase; it is not a row column or an engine sequence. |

Text profiles assign contiguous engine sequences after `InputProgress.sequence`.
CSV and ordinary legacy profiles can attach raw record-start byte offsets
using `source` plus `byte_offset`. Timestamp/flag input instead preserves its
unsigned uint64 timestamp; a byte offset option does not apply. Legacy profiles
are always headerless. Non-default options for unrelated formats are rejected,
including native-wire source/table overrides and mappings in nonrelation
profiles. `*` enumeration markers fail as `unsupported_input_control`; they
are not silently skipped or turned into physical no-ops. A control-aware
benchmark/session adapter needs a separate explicit operation contract.

These profiles cover the literal graph, TwoComb relation-token and explicitly
mapped full-row SNB shapes in the legacy experiments. SNB payload widths and
types must match the full physical catalog; query-dependent field selection
and predicates belong in the compiled input adapters. No legacy implementation
was copied. In particular, the
[TwoComb converter](../experiments/TwoComb/Convert2Comb.scala) writes flag 1
for some vertex deletions while correctly writing 0 for graph deletions.
That file cannot reveal its intended signs to a reader. The timestamp/flag
profile follows literal flags and does not repair corrupted data; use the
correctly signed Crown trace when comparing intended behavior.

## Reader acceptance and engine replay

`EventReader` borrows its `istream`, retains its catalog owner and one bounded native
event, and supports repeated `peek()` of that same event. `acknowledge()`
advances accepted sequence/source positions and releases it. With no cached
event, acknowledgement is an idempotent no-op. It cannot silently read/skip a
new event. `records_read()` counts decoded records, including an unacknowledged
one; `bytes_read()` can include lookahead or failed input. Neither diagnostic
counter is a commit/checkpoint position.

Source map insertion is prepared during peek, before engine work. A valid
acknowledgement only links that prepared node or changes an existing scalar,
assigns sequence and destroys the cached row; it does not allocate or throw.
Parse/order/reader-allocation errors make the reader sticky-failed without
accepted-progress changes. Further peeks report `input_failed`; correction
requires explicit recreation. Initial progress is a caller-supplied boundary,
not a verified checkpoint importer, and does not retain CSV header/decoder
state needed by a future persistence protocol.

`OrderedReplay` owns a reader and binds its first application to one runtime
owner/catalog. It checks runtime readiness and accepted sequence, peeks a
validated event, calls atomic native `PhysicalRuntime::apply_view` or `DeltaRuntime::apply_view`,
then acknowledges through nonthrowing bookkeeping. Engine failure preserves
the cached record and old input progress for retry; it does not poison the
reader. A no-op physical event still commits its sequence and source position.
Wrong owner/catalog/progress or active readers/pending/output owners reject.

With delta replay, consume/discard the returned D06 output before the next
input. A sink/serializer failure happens after input commitment; retry its
output row through D06 rather than reapplying input. This is ordered per-event
replay, not all-or-nothing file/transport batching, durable delivery or WAL.
[O02 sessions](session_lifecycle.md) pair a reader's prepared event with D06 pending input;
O04–O06 must supply verified checkpoint/source-position and delivery protocols.

## Budgets and diagnostic command

Default limits are 1 MiB per encoded record and text field, 4,096 source
columns, 1,024 source-name bytes, 1,024 retained sources and one million decoded
records. Total bytes are optional; an unbounded stream can still keep bounded
record/progress state. The field limit also caps the physical table name,
including names supplied through CSV/legacy configuration. Raw CSV limits
include syntax and line terminators;
fixed binary int/bool payloads have their intrinsic widths, while CSV textual
int/bool spellings use field limits. JSON string tokens may first occupy
`record_bytes` lexer scratch before the narrower `field_bytes` acceptance
check. Catalog/mapping/header descriptors, container capacity/allocator slack,
external stream buffering and caller-owned input/output are additional costs.

Working input state is one raw/decoded record plus bounded column/source
metadata; there is no history of accepted source events. Native schema parsing,
public SAX codecs and direct canonical encoding avoid JSON-container teardown during persistent
OOM. Catalog hashing/binding costs O(catalog/configuration bytes), separate
from each update's engine work. The reference arena can grow its high-water
metadata geometrically; no uniform no-allocation or constant-update claim is
inferred from an ingestion allocation fixture.

The diagnostic command validates a complete stream without updating an engine:

```sh
crown validate-input CATALOG.json jsonl EVENTS.jsonl
crown validate-input CATALOG.json binary EVENTS.bin
crown validate-input CATALOG.json csv TABLE.csv TABLE_NAME
crown validate-input CATALOG.json legacy-signed EVENTS.csv TABLE_NAME
```

It also supports `legacy-insert-only` and flag-first `legacy-flags`. This small
CLI uses default comma/header settings; custom delimiters, relation mapping,
timestamp flags, resume progress and limit configuration use the library API.
It reports one summary only after valid EOF: format, bound catalog hash,
decoded record/raw byte counts and validated sequence/source positions.
Catalog text is bounded to 16 MiB. Failure has no partial successful summary.
This diagnostic is separate from O08's future session/streaming CLI release.

## Native reader API and memory grant

Execution constructs EventReader from the admitted CompiledProgram so that
reader controls, native options/framing/lexer/parser/cells/cached rows/source
positions and accepted progress consume the original query account. QuerySession
shares AccountedInputOptions with its immutable run context. Standalone
CatalogSource construction is an explicit compiler/external adapter with its own
account; it does not replace an execution program's allowance.

peek() returns a stable const InputEventView pointer. Native physical/delta
admission borrows its values synchronously and imports pending ownership before
returning. progress() is a const AccountedInputProgress reference; close() moves
that native accepted value without allocation. export_value() is the explicit
external InputProgress DTO boundary. SessionRunContext.input is immutable
AccountedInputOptions; get() exposes read-only native fields and export_value()
creates caller-owned InputOptions when needed. Copies retain the funded option
owner without allocating. Catalog fingerprint access is a borrowed string_view.

The public read_input_json/read_input_binary and write_input_* functions remain
owning caller DTO codecs. The native reader uses a bounded schema JSON parser
with funded token/cell capacity, strict Unicode/JSON numbers and inline decimal
parsing. Malformed syntax reports stable invalid_document text; old third-party
parser exception wording is not exposed. Field/schema/row/source/binding/limit
checks keep their error codes and order. Reader OOM remains sticky, unlike a typed
queue's retryable peek allocation failure. Explicit recreation retains only the
accepted prefix and the original execution grant.

See the historical [native stream evidence](verification/s05-stream-input-2026-11-09.md).
The later S05 acceptance verifies native post-admission ownership and authentic
record/byte reconciliation, including retained instrumentation, captures, reports,
diagnostics and retained reader/queue owners in its recorded routes. This does not bound
compiler/caller DTOs or all process RSS; see the [current ledger](task_ledger.md)
and [query memory boundary](query_memory.md).
