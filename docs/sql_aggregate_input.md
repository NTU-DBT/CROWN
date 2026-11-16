# SQL aggregate JSONL and CLI

The separate `crown aggregate` command family connects original SQL and nullable
physical rows to the [durable R2 Session](sql_aggregate_session.md). The original
set commands and their input formats keep their existing contracts.

The [public reader](../include/crown/io/sql_aggregate_input.hpp) supplies owning
commands to `Session::log()`. Its [implementation](../src/io/sql_aggregate_input.cpp)
validates transport, types and sequence; the [CLI](../apps/crown/aggregate.cpp)
owns file seeking and the log/decide/deliver loop. Neither input parsing nor a
successful JSON decode decides a native commit.

## Workflow

Create a session once, using a catalog in the existing catalog document format:

```sh
crown aggregate create query.sql catalog.json query.root groups.sink --average-scale 2
```

Creation binds the actual SQL/catalog and chooses a checked minimum tree for a
non-contradictory source; contradictory sources use the constant-empty route.
It writes the genuine descriptor and initial checkpoint through Session. Root,
generation candidate and sink paths must satisfy the existing new-session rules.
The report supplies `binding_sha256`, which each JSONL command must repeat.

```sh
crown aggregate run query.root groups.sink updates.jsonl --commands 100
crown aggregate status query.root groups.sink
crown aggregate snapshot query.root groups.sink
crown aggregate checkpoint query.root groups.sink
```

Each later command reconstructs the selected genuine descriptor and state.
`run` resumes from the original input-file origin; pass the same consumed prefix.
`--commands` counts decisions in that invocation, including a recovered pending
Input. Omit it to continue to EOF or an error. A previously committed spool is
delivered even with `--commands 0`; a pending Input stays pending at that limit.
Checkpoint requires no pending Input or output. Snapshot reports current C, which
can be ahead of delivered D; it does not acknowledge results.

Status, snapshot and checkpoint are recovery operations. By default, the Session
may repair admissible torn tails after its complete validation barrier. Use
`--repair-tail no` to refuse such repair. None of these commands can certify a
corrupt complete frame by truncating it.

Default identity labels are 32 zeroes for the query and 32 ones for the sink.
Use `--query-id HEX32` consistently for a custom query label and `--sink-id HEX32`
at creation for a custom sink label. These labels are not authentication secrets;
the actual descriptor, root and sink binding checks still apply. The containing
namespace and advisory-lock cooperation follow the [file contract](sql_aggregate_files.md).

`--physical-options FILE` uses the existing versioned physical-options format.
When recovering indexed storage, supply `--rebuild-indexed-work N`: N is a finite
cold allowance for each of the five indexed work domains. It does not change the
stored operational policy. Reference storage does not accept an indexed rebuild
grant. Other resource options are listed by `crown aggregate --help`.

## One atomic JSONL command

The [versioned JSON schema](../schemas/sql-aggregate-input-v1.schema.json)
describes structural shape. Genuine binding/type/domain checks, duplicate-key
rejection, lexical integer forms and operational resource/progress limits remain
decoder and Session obligations; schema validation alone does not authorize native state.

For `SELECT g,COUNT(*),SUM(x) FROM r GROUP BY g`, with nullable TEXT `g`, nullable
BIGINT `x` and physical source schema version 1, a command has this form. Replace
the example binding with the exact hash from creation:

```json
{"schema_version":1,"binding_sha256":"<64 lowercase hex characters from creation>","sequence":1,"replacements":[{"table":"r","source_schema_version":1,"values":["a",2],"before":0,"after":3}],"source_position":{"source":"updates","offset":1}}
```

The binding identifies the genuine original SQL, catalog, typed parameters,
source normalization and aggregate kernel. A replacement names an exact physical
table, supplies every physical column in catalog order, and states its complete
before/after weight. SQL aliases are not source names. Weights are unsigned
64-bit JSON integers. Multiple edits of the same row must form an exact chain;
the native batch validates final-state constraints and arithmetic atomically.
An empty replacement list is a successful empty epoch with its own C and output.

Only `source_position` is optional. Its nonempty UTF8 source name and unsigned
offset use the Session's strict per-source progress rules. The reader supplies
its own byte/record continuation; JSON cannot override that metadata.
Unknown, missing or duplicate fields are rejected, including nested fields.
The next sequence must be logged W+1, including after a semantic Reject.

Nullable cells use JSON `null`. Other admitted scalars are signed-bigint integers,
TEXT strings, booleans, `{"date":"2020-02-29"}` and
`{"decimal":"12.50"}`. The physical source type, nullability and decimal domain
must match; floats and implicit conversions are rejected. Strings are valid SQL
UTF8 without NUL. DATE/DECIMAL source decoding does not extend the aggregate
binder's separate expression/function admission rules. In particular, this input
path adds no new decimal SUM or varying-int32 admission.

LF, CRLF and a final unterminated JSON object are accepted. Blank lines are
errors. Byte counters include line terminators, while `record_bytes` excludes LF
and one trailing CR. An already consumed unterminated final record is terminal
for this CLI source: appending an LF afterward does not repair its saved offset.
Records must already be LF-terminated when logged if later appends are intended.
The CLI rejects a saved non-LF continuation inside a now-longer file.
A saved offset is not a content hash of the input file: preserve
the consumed prefix. Durable WAL commands remain the authority for their native
effects.

## Ownership, failure and cost

The reader freezes genuine immutable compiler metadata into the receiving
account; sharing is sufficient when it already has that owner. It borrows the
stream. Each decoded command owns flat cell, TEXT/source-name and replacement
buffers, with stable internal spans. Command views require a live, unmoved owner;
the command itself can outlive the reader, DOM and stream. No row/DOM mirror is
kept by Session after it owns its logged command.

Before reading, the reader latches `requires_reopen`. It clears that latch only
after complete framing, validation and command funding, or a clean EOF. A failure
requires a new reader from durable logged W/reader progress. If `log()` fails
during funding/validation before Input I/O, its caller can retry the same owning decoded command;
it must not advance to a later command. The CLI exits on failure and reconstructs
the correct boundary on its next invocation. An uncertain file I/O outcome uses
Session's reopen requirement; retaining the decoded command does not waive it.

The CLI first delivers any committed spool. It then resolves a WAL-owned pending
Input before constructing the next reader. Each new decoded command ends its
lifetime after `log()` and before `decide()`; the reader retains its largest raw
line capacity. Native preparation and canonical output continue to use Session's
single existing batch token and one spool. The six semantic Reject reasons
advance I and source/reader progress; resource or contract failures do not gain a
Reject tag. Report failure after a durable decision does not undo it or authorize
logging the same command again.

Default limits are 1 MiB per record and scalar string/tag, 4 KiB per source name,
65,536 replacements, 1,000,000 cells, 1 GiB cumulative bytes and 1,000,000 records.
Cumulative caps are measured from the original stream origin, including restored
counters. Limits admit logical extents; vector capacity and growth overlap are
charged as actual receiving-account requests. The retained raw line is bounded
by the record cap and geometric vector growth. The CLI's account has a default
256 MiB limit shared by its reader, Session and native state.

JSON DOM, duplicate-key sets, lexer tokens and ordinary stream/compiler workspace
remain outside that native account. Their input extent is bounded by the record
and document limits. Decoding makes two scalar passes and copies retained TEXT
once into the flat command buffer. Physical table lookup scans the genuine table
list per replacement per pass; total transport work depends on record bytes,
cells and replacements times table count. The Session then performs its separate
canonical encoding and genuine native validation. No single-tuple delay theorem
or CPU benchmark is claimed for this transport path.

Reports cap appended bytes before stdout starts. One scalar's JSON-escape
temporary is ordinary presentation work. Snapshot first funds its eager native
image, then encodes it with typed nullable cells and symbolic SQL kinds. The
binary sink's protected [group epochs](sql_aggregate_records.md) are the durable
before/after output; stdout is a report. The CLI's fixed-failure translations
occur only at the presentation boundary after RAII owners unwind.

The [reader tests](../tests/unit/sql_aggregate_input_test.cpp) cover owning borrows,
strict validation, exact limits, continuation, reached C++ allocation refusals and
receiving-account peak. JSON destruction can complete through its own allocation
fallback, so refusal may return a correct command rather than propagate.
The [CLI checks](../tests/integration/sql_aggregate_cli.py) use real subprocesses,
pending Input/Commit fixtures, both storage backends, independent DuckDB
snapshots, actual sink-frame decoding, count-limit and signed-bigint SUM overflow,
checkpoint/retry and tail/transport refusal. Deterministic boundary fixtures are
separate from the existing Session EIO/process-cut evidence.
