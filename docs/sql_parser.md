# SQL syntax parser (F02)

`crown parse-sql INPUT.sql` runs the syntax-only SQL frontend. It wraps the
pinned `libpg_query` 18.1.0 parser, built from commit
`c1546e7e97edc93fe8474d7a59881e91fbf48cfc` (PostgreSQL 18.6 / parser version
180006). The output contract is [sql-syntax-v1.schema.json](../schemas/sql-syntax-v1.schema.json).

## Lifecycle

The CLI reads at most 1 MiB plus one byte, sufficient to detect an over-limit
file without buffering it in full, and passes those bytes to the parser
wrapper. The wrapper applies the 1 MiB source limit, rejects malformed
UTF-8 and embedded NUL bytes before calling the NUL-terminated upstream C API,
then parses the entire source. It copies the successful parse JSON into owned
memory and frees the upstream parse result on both success and failure. No
pointer owned by libpg_query escapes the wrapper.

Wrapper calls are serialized around upstream parsing and result conversion.
Upstream frees its per-call PostgreSQL memory context; its top context is
cached per calling thread until the upstream thread-exit destructor runs.
The wrapper does not call the upstream terminal `pg_query_exit` between
parses. Prior owned results remain valid across later calls and thread exit.

The JSON result always reports `parser: "libpg_query"`, `parser_version:
"18.1.0"`, `postgres_version: 180006`, and `admission_status:
"not_checked"`. A successful result contains the original UTF-8 `source`, a
`statement` byte range, and the complete upstream parse `ast`. The AST is
preserved as supplied by libpg_query, including the `RawStmt` envelope,
PostgreSQL version, and every upstream `location` field. The range starts at
`RawStmt.stmt_location` (zero when omitted) and ends at the start plus
`RawStmt.stmt_len`. When `stmt_len` is zero or omitted, the range ends at the
source length. The end offset is exclusive.

The parser accepts exactly one nonempty statement. Leading comments and empty
semicolons are allowed. A final semicolon is part of the upstream statement
range when libpg_query includes it. Semicolons in strings and comments do not
split statements. The whole input is parsed before the statement count is
checked, so malformed SQL in a later statement returns the parser's syntax
diagnostic; two valid statements return `multiple_statements` at the second
statement's start.

`syntax_valid: true` means only that the source parsed as one statement. It
does not resolve table or column names, check types, normalize a query, classify
its body, or authorize execution. `COUNT`, `GROUP BY`, plain bag `SELECT`,
`NULL`, and DDL are useful syntax fixtures, but their presence in the AST does
not mean CROWN supports those semantics. `admit-sql` reports frontend/structural admission only
(`execution_status:not_lowered`). A normalized SQL artifact can separately be
lowered with a verified tree through `lower-normalized`; lowering does not
start a maintained runtime.

## Locations and diagnostics

Source ranges and all AST locations are zero-based byte offsets into the
original UTF-8 file. They are not rewritten into character offsets. For a
valid-encoding diagnostic, `byte_offset` is zero-based, `character_position`
is one-based as in PostgreSQL, and `line` and `column` are one-based; column
counts Unicode code points. If the byte sequence is malformed UTF-8, only the
byte offset is populated because a character position is undefined. Resource
diagnostics that have no reliable failure location use null coordinates.

| Diagnostic code | Meaning |
| --- | --- |
| `sql_syntax_error` | The pinned PostgreSQL grammar rejected the source. |
| `empty_sql` | The input contains no nonempty statement (for example, only comments or semicolons). |
| `multiple_statements` | More than one nonempty, syntactically valid statement was parsed. |
| `invalid_encoding` | The source is malformed UTF-8 or contains an embedded NUL byte. |
| `resource_limit` | The source is over 1 MiB, the AST nesting is over 256, or the parser reports a resource exhaustion condition. |

The result JSON is written to stdout for both syntax success and parse
diagnostics. Exit status is 0 for one valid statement, 1 for a syntax,
statement-boundary, encoding, or resource diagnostic, and 2 for CLI usage or
input-file I/O errors.

## Work after syntax parsing

Parsing remains syntax-only: it does not bind names, check types, normalize a
query, classify its structure, or admit it. Current binding, normalization,
and frontend/structural admission behavior is documented in
[SQL binding](sql_binding.md), [SQL normalization](sql_normalization.md), and
[SQL admission](sql_admission.md); current implementation status is tracked in
[task_ledger.md](task_ledger.md). Parser success alone never admits a query.
Admission still reports `execution_status:not_lowered`; this parser contract
makes no SQL execution or allocator/runtime guarantee.

The integration fixtures under `tests/frontend/parser/` use AST snapshots
obtained directly from the pinned upstream C API, not from `crown parse-sql`.
They check complete AST preservation, source ranges, Unicode locations,
statement boundaries, and syntax that later frontend stages may reject.
