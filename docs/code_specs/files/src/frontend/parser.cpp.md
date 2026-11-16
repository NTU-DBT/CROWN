# `src/frontend/parser.cpp` — block usage map

[Source](../../../../../src/frontend/parser.cpp) · [Source index](../../../README.md) · [Subsystem contracts](../../../subsystem_contracts.md) · [Reviewed primitives](../../../primitives.md)

Own the libpg_query parse result and expose the admitted parser representation.

Snapshot SHA-256: `45f92cbb543a049e226a97cf4b396d57f6f263d19ebe866b48274c6d50b86e71`. 150 lines partitioned into 14 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [frontend](../../../subsystem_contracts.md#frontend). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/sql_support.md](../../../../sql_support.md), [docs/sql_parser.md](../../../../sql_parser.md), [docs/sql_binding.md](../../../../sql_binding.md), [docs/sql_normalization.md](../../../../sql_normalization.md), [docs/sql_admission.md](../../../../sql_admission.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–10](../../../../../src/frontend/parser.cpp#L1) | Imports dependencies; declares namespace scope. |  · [reviewed contract](#b0001) |
| [B0002 · 11–11](../../../../../src/frontend/parser.cpp#L11) | Callable definition: std::mutex& parser_detail::mutex() | calls ; returns value · [reviewed contract](#b0002) |
| [B0003 · 12–14](../../../../../src/frontend/parser.cpp#L12) | declares namespace scope; declares callable signatures; declares values/defaults or compile-time conditions. | guard static_assert(PG_VERSION_NUM == 180006, "SQL AST contract requires PostgreSQL 18.6"); · [reviewed contract](#b0003) |
| [B0004 · 15–24](../../../../../src/frontend/parser.cpp#L15) | Type/record definition: class ParseOwner | returns result_ · [reviewed contract](#b0004) |
| [B0005 · 25–25](../../../../../src/frontend/parser.cpp#L25) | Explanatory comments or spacing. |  |
| [B0006 · 26–26](../../../../../src/frontend/parser.cpp#L26) | Callable definition: bool continuation(unsigned char byte) | calls ; returns byte &gt;= 0x80 && byte &lt;= 0xbf · [reviewed contract](#b0006) |
| [B0007 · 27–29](../../../../../src/frontend/parser.cpp#L27) | Explanatory comments or spacing. | source comment (unverified): // A strict UTF-8 boundary is required before the NUL-terminated C parser and · [reviewed contract](#b0007) |
| [B0008 · 30–49](../../../../../src/frontend/parser.cpp#L30) | Callable definition: std::optional&lt;std::size_t&gt; invalid_utf8(std::string_view source) | calls size, continuation; returns i; i; 2 loop sites; source comment (unverified): // A strict UTF-8 boundary is required before the NUL-terminated C parser and · [reviewed contract](#b0008) |
| [B0009 · 50–63](../../../../../src/frontend/parser.cpp#L50) | Callable definition: SqlDiagnostic diagnostic_at(std::string code, std::string message, std::string_view source, std::optional&lt;std::size_t&gt; offset = s… | calls std::move, continuation; returns result; result; 1 loop sites · [reviewed contract](#b0009) |
| [B0010 · 64–76](../../../../../src/frontend/parser.cpp#L64) | Callable definition: std::optional&lt;std::size_t&gt; byte_position(std::string_view source, int character_position) | calls size, continuation; returns std::nullopt; i; 1 loop sites; source comment (unverified): // Error at end of input. · [reviewed contract](#b0010) |
| [B0011 · 77–84](../../../../../src/frontend/parser.cpp#L77) | Callable definition: std::size_t statement_offset(const nlohmann::json& statement, const char* field) | calls contains, at, is_number_integer, Error; returns 0; value.get&lt;std::size_t&gt;(); source comment (unverified): // Upstream omits zero fields. · [reviewed contract](#b0011) |
| [B0012 · 85–86](../../../../../src/frontend/parser.cpp#L85) | Closes surrounding scope/type. | source comment (unverified): // namespace · [reviewed contract](#b0012) |
| [B0013 · 87–149](../../../../../src/frontend/parser.cpp#L87) | Callable definition: SqlParseResult parse_sql(std::string_view source, ParseLimits limits) | calls size, max, diagnostic_at, invalid_utf8; returns diagnostic_at(@ , @ , source); SqlDiagnostic{@ , @ , offset, {}, {}, {}}; source comment (unverified): // Coordinates on malformed UTF-8 would imply a nonexistent character map. · [reviewed contract](#b0013) |
| [B0014 · 150–150](../../../../../src/frontend/parser.cpp#L150) | Closes surrounding scope/type. | source comment (unverified): // namespace crown::frontend · [reviewed contract](#b0014) |

## B0001

[Lines 1–10](../../../../../src/frontend/parser.cpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
#include "crown/frontend/parser.hpp"
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Include the shared private parser-gate declaration while preserving existing JSON parser dependencies. |
| inputs / outputs | Imports, declarations, comments, closure or spacing in the exact stated block. |
| invariants | No SQL admission, plan authority, output publication or execution claim from this scaffolding. |
| ownership | No new executable ownership beyond declarations explicitly described in surrounding cards. |
| failure | No runtime failure is handled by these lines. |
| cost | No runtime work from comments/spacing/declarations. |
| Design | [build/verification/w06-sql-aggregate-compiler-repair-v2/design.md](../../../../../build/verification/w06-sql-aggregate-compiler-repair-v2/design.md), [build/verification/w06-sql-aggregate-compiler-repair-v2/private-contribution-port.md](../../../../../build/verification/w06-sql-aggregate-compiler-repair-v2/private-contribution-port.md), [build/verification/w06-contract-assessment-v1/assessment.md](../../../../../build/verification/w06-contract-assessment-v1/assessment.md), Refactor.md:1317-1327, Refactor.md:1325-1333, [docs/sql_parser.md §Lifecycle](../../../../sql_parser.md), [src/frontend/parser.cpp](../../../../../src/frontend/parser.cpp), [src/frontend/parser_detail.hpp](../../../../../src/frontend/parser_detail.hpp), [src/frontend/sql_aggregate.cpp](../../../../../src/frontend/sql_aggregate.cpp) |

## B0002

[Lines 11–11](../../../../../src/frontend/parser.cpp#L11); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::mutex& parser_detail::mutex() { static std::mutex value; return value; }
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Return the one process wrapper gate used by JSON/protobuf/deparse paths. |
| inputs / outputs | Function-local static std::mutex returns by reference. |
| invariants | Every wrapper shares this gate; no recursive lock is held when composition invokes child factories. |
| ownership | Static mutex lasts for process lifetime; no query/account owner is created. |
| failure | Ordinary mutex construction/lock contract applies; function allocates no query state. |
| cost | Constant reference access. |
| Design | [build/verification/w06-sql-aggregate-compiler-repair-v2/design.md](../../../../../build/verification/w06-sql-aggregate-compiler-repair-v2/design.md), [build/verification/w06-sql-aggregate-compiler-repair-v2/private-contribution-port.md](../../../../../build/verification/w06-sql-aggregate-compiler-repair-v2/private-contribution-port.md), [build/verification/w06-contract-assessment-v1/assessment.md](../../../../../build/verification/w06-contract-assessment-v1/assessment.md), Refactor.md:1317-1327, [build/verification/w06-sql-aggregate-compiler-repair-v2/source/pinned-libpg-query/pg_query.h](../../../../../build/verification/w06-sql-aggregate-compiler-repair-v2/source/pinned-libpg-query/pg_query.h), [build/verification/w06-sql-aggregate-compiler-repair-v2/source/pinned-libpg-query/protobuf/pg_query.upb.h](../../../../../build/verification/w06-sql-aggregate-compiler-repair-v2/source/pinned-libpg-query/protobuf/pg_query.upb.h), [build/verification/w06-sql-aggregate-compiler-repair-v2/source/pinned-libpg-query/vendor/upb/upb/generated_code_support.h](../../../../../build/verification/w06-sql-aggregate-compiler-repair-v2/source/pinned-libpg-query/vendor/upb/upb/generated_code_support.h), [build/verification/w06-sql-aggregate-compiler-repair-v2/source/pinned-libpg-query/vendor/upb/upb.c](../../../../../build/verification/w06-sql-aggregate-compiler-repair-v2/source/pinned-libpg-query/vendor/upb/upb.c), [build/verification/w06-sql-aggregate-compiler-repair-v2/source/pinned-libpg-query/Makefile](../../../../../build/verification/w06-sql-aggregate-compiler-repair-v2/source/pinned-libpg-query/Makefile), Refactor.md:1325-1333, [docs/sql_parser.md §Lifecycle](../../../../sql_parser.md), [src/frontend/parser.cpp](../../../../../src/frontend/parser.cpp), [src/frontend/parser_detail.hpp](../../../../../src/frontend/parser_detail.hpp), [src/frontend/sql_aggregate.cpp](../../../../../src/frontend/sql_aggregate.cpp) |

## B0003

[Lines 12–14](../../../../../src/frontend/parser.cpp#L12); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L12-L14:sha256:a4f49bca7b7e55b62ec4757b1ffce30b2cb7459b281565ad9bab539bc227688a
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Adds a compile-time assertion for the declared representation/configuration: static_assert(PG_VERSION_NUM == 180006, "SQL AST contract requires PostgreSQL 18.6"); |
| inputs / outputs | No runtime values are exchanged; the compiler evaluates the assertion during translation and rejects the build if it is false. |
| invariants | The stated type/layout condition must remain true for this translation unit to compile. |
| ownership | Compile-time only; no object owner is created. |
| failure | A false condition is a compile-time diagnostic, not a runtime exception. |
| cost | Compile-time checking only; no runtime cost. |
| Design | [src/frontend/parser.cpp](../../../../../src/frontend/parser.cpp), [docs/code_specs/files/src/frontend/parser.cpp.md](parser.cpp.md), [docs/sql_parser.md](../../../../sql_parser.md), [docs/sql_binding.md](../../../../sql_binding.md) |

## B0004

[Lines 15–24](../../../../../src/frontend/parser.cpp#L15); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
class ParseOwner {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Own one libpg_query parse result for the wrapper call. |
| inputs / outputs | A NUL-terminated source pointer in; \`PgQueryParseResult\` held privately, with a const borrowed view from \`get()\`. |
| invariants | The wrapper does not copy, assign, or expose the C result beyond this owner’s lifetime. |
| ownership | \`ParseOwner\` frees \`result_\` in its destructor, including returns and exceptions after construction; \`get()\` is borrowed. |
| failure | C++ scope cleanup invokes \`pg_query_free_parse_result\`; upstream parser errors remain represented in the owned result. |
| cost | One upstream parse-result owner; cleanup cost follows upstream result size. No CROWN allocation-accounting object is used. |
| Design | [docs/sql_parser.md](../../../../sql_parser.md), [include/crown/frontend/parser.hpp](../../../../../include/crown/frontend/parser.hpp) |

## B0006

[Lines 26–26](../../../../../src/frontend/parser.cpp#L26); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
bool continuation(unsigned char byte)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Recognize one UTF-8 continuation byte for the strict source and diagnostic scans. |
| inputs / outputs | One unsigned byte in; true exactly for 0x80 through 0xBF. |
| invariants | This local predicate alone does not establish valid UTF-8; \`invalid_utf8\` checks sequence length and scalar boundaries. |
| ownership | No retained state or ownership. |
| failure | No failure path. |
| cost | Constant comparisons, O(1), no allocation. |
| Design | [docs/sql_parser.md](../../../../sql_parser.md) |

## B0007

[Lines 27–29](../../../../../src/frontend/parser.cpp#L27); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L27-L29:sha256:a7134668627b5a629af135dbca519abad880c6e12f1c79e4dea8953ac80e528f
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Design note for adjacent code: A strict UTF-8 boundary is required before the NUL-terminated C parser and before interpreting PostgreSQL character positions. Reject overlong forms, surrogate code points and values above U+10FFFF as well as truncated input. This is caller guidance recorded as prose, not an executable result. |
| inputs / outputs | No runtime interface is implemented by these comment-only lines. They sit at src/frontend/parser.cpp lines 25-31; the surrounding declaration/body defines its own inputs and outputs. |
| invariants | The words record the intended use boundary only. They do not add a guard, proof, capability, transaction, durability guarantee, or account charge; verify behavior in the referenced implementation. |
| ownership | Comment text owns no data. Object lifetimes, borrows, and account attribution remain those of the adjacent source objects and their constructors. |
| failure | No failure path is implemented here. Any mentioned failure or recovery rule belongs to the adjacent operation and its existing error carrier. |
| cost | No runtime work is performed by these lines; any cost/bound in the note is not certified by this comment-only card. |
| Design | [src/frontend/parser.cpp](../../../../../src/frontend/parser.cpp), [docs/code_specs/files/src/frontend/parser.cpp.md](parser.cpp.md), [docs/sql_parser.md](../../../../sql_parser.md), [docs/sql_binding.md](../../../../sql_binding.md) |

## B0008

[Lines 30–49](../../../../../src/frontend/parser.cpp#L30); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::optional<std::size_t> invalid_utf8(std::string_view source)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Find the first malformed UTF-8 byte before passing bytes to the NUL-terminated parser. |
| inputs / outputs | A borrowed byte view in; first bad byte index or \`nullopt\` out. |
| invariants | Rejects invalid lead bytes, truncation, bad continuation bytes, overlong encodings, surrogates, and values above U+10FFFF. |
| ownership | Borrows the caller’s view only for the scan; returns a scalar offset. |
| failure | Malformed input returns its byte offset; it does not construct Unicode character coordinates or throw for ordinary malformed encodings. |
| cost | One forward scan, O(source bytes), O(1) auxiliary storage, no allocation. |
| Design | [docs/sql_parser.md](../../../../sql_parser.md) |

## B0009

[Lines 50–63](../../../../../src/frontend/parser.cpp#L50); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
SqlDiagnostic diagnostic_at(std::string code, std::string message, std::string_view source,
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Create an owned SQL diagnostic and derive PostgreSQL-style source coordinates when an offset exists. |
| inputs / outputs | Owned code/message, borrowed valid UTF-8 source, and optional byte offset in; owned \`SqlDiagnostic\` out. |
| invariants | With an offset, coordinates are one-based; line advances at LF, column counts Unicode code points, and character position counts decoded code points. Without an offset, all coordinates stay absent. |
| ownership | Moves code/message into the result; source is borrowed only during coordinate calculation. |
| failure | Internal callers must supply an in-range offset into valid UTF-8; malformed UTF-8 uses a separate diagnostic path because character coordinates are undefined. |
| cost | O(offset) byte scan when located; O(1) coordinate work otherwise. No heap growth beyond owned strings/result. |
| Design | [docs/sql_parser.md](../../../../sql_parser.md), [include/crown/frontend/parser.hpp](../../../../../include/crown/frontend/parser.hpp) |

## B0010

[Lines 64–76](../../../../../src/frontend/parser.cpp#L64); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::optional<std::size_t> byte_position(std::string_view source, int character_position)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Map libpg_query’s one-based character cursor position back to a source byte offset. |
| inputs / outputs | Valid UTF-8 source and signed PostgreSQL character position in; byte offset or \`nullopt\` out. |
| invariants | Positions &lt;= 0 and positions beyond the end are absent; the position immediately after the last code point maps to \`source.size()\`. |
| ownership | Borrows source and returns a scalar offset; it does not retain a pointer. |
| failure | No exception is created for an unusable upstream position; callers retain a diagnostic with null offset. |
| cost | O(source bytes) scan, O(1) auxiliary state, no allocation. |
| Design | [docs/sql_parser.md](../../../../sql_parser.md) |

## B0011

[Lines 77–84](../../../../../src/frontend/parser.cpp#L77); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::size_t statement_offset(const nlohmann::json& statement, const char* field)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Read an upstream RawStmt offset field while accommodating omitted zero-valued fields. |
| inputs / outputs | Borrowed statement JSON and field name in; nonnegative \`size_t\` offset out. |
| invariants | Missing field means zero. Present fields must be nonnegative integer JSON values; range checks against source are performed by \`parse_sql\`. |
| ownership | Borrows the AST node and field name; returns a scalar. |
| failure | Wrong type or negative value throws \`parser_contract\`, treating malformed upstream JSON as an invariant failure. |
| cost | One JSON object field lookup and scalar conversion; no traversal or output allocation on success. |
| Design | [docs/sql_parser.md](../../../../sql_parser.md) |

## B0012

[Lines 85–86](../../../../../src/frontend/parser.cpp#L85); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L85-L86:sha256:c2bd7638f09d52cb034ed574f539304035fc6fab162bf8d5fa20a35d8c7288a1
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Closes the anonymous namespace at this source boundary; this is a lexical delimiter, not an operation. |
| inputs / outputs | No runtime input or output. Declarations following the span leave the preceding C++ scope. |
| invariants | The delimiter ends the preceding scope's visibility/linkage region; it adds no validation, publication, ownership transfer, or runtime authority. |
| ownership | The delimiter adds no owner. If it ends a function/block with live automatic objects, their normal destructors release those objects; namespace and type-definition closes change no existing object's lifetime. |
| failure | No explicit failure translation or catch is added. If a function/block exit destroys automatic objects, exception behavior follows those destructors; namespace/type closes have no runtime failure path. |
| cost | The delimiter adds no algorithmic work. A function/block exit can run existing automatic-object destructors and cleanup; namespace/type closes have no runtime cost. |
| Design | [src/frontend/parser.cpp](../../../../../src/frontend/parser.cpp), [docs/code_specs/files/src/frontend/parser.cpp.md](parser.cpp.md), [docs/sql_parser.md](../../../../sql_parser.md), [docs/sql_binding.md](../../../../sql_binding.md) |

## B0013

[Lines 87–149](../../../../../src/frontend/parser.cpp#L87); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
SqlParseResult parse_sql(std::string_view source, ParseLimits limits)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Parse one SQL statement under the shared native parser/deparser gate while preserving the existing JSON result contract. |
| inputs / outputs | Original SQL bytes and ParseLimits produce owning SqlSyntax or an original-source SqlDiagnostic. |
| invariants | Existing UTF-8, NUL, byte/depth, PostgreSQL-version, single-statement, and range checks remain. JSON, protobuf parse, and protobuf deparse wrappers use parser_detail::mutex(); child factories are entered only after a prior parse wrapper returns. |
| ownership | The lock guard and ParseOwner span parse_sql including JSON conversion; ParseOwner frees its C result before the lock leaves scope. No libpg_query pointer escapes; returned SQL source/JSON use ordinary cold workspace. |
| failure | Existing syntax/resource/contract diagnostics remain. ParseOwner cleanup and lock release occur on return or exception; parser_contract and allocation/lock failures are not converted into aggregate diagnostics here. |
| cost | One shared std::mutex acquisition per parse, replacing the former local mutex with the common gate; upstream parser and JSON work remain cold serialized work. |
| Design | [docs/sql_parser.md §Lifecycle](../../../../sql_parser.md), [src/frontend/parser_detail.hpp](../../../../../src/frontend/parser_detail.hpp), [src/frontend/parser.cpp](../../../../../src/frontend/parser.cpp), [src/frontend/sql_aggregate.cpp](../../../../../src/frontend/sql_aggregate.cpp), [build/verification/w06-sql-aggregate-compiler-repair-v2/source/pinned-libpg-query/pg_query.h](../../../../../build/verification/w06-sql-aggregate-compiler-repair-v2/source/pinned-libpg-query/pg_query.h) |

## B0014

[Lines 150–150](../../../../../src/frontend/parser.cpp#L150); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L150-L150:sha256:2fc33ff8830b8cd06d6971e8e31b29a8803f152d87e09a3fc4092b3efecdac93
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Closes the namespace crown::frontend at this source boundary; this is a lexical delimiter, not an operation. |
| inputs / outputs | No runtime input or output. Declarations following the span leave the preceding C++ scope. |
| invariants | The delimiter ends the preceding scope's visibility/linkage region; it adds no validation, publication, ownership transfer, or runtime authority. |
| ownership | The delimiter adds no owner. If it ends a function/block with live automatic objects, their normal destructors release those objects; namespace and type-definition closes change no existing object's lifetime. |
| failure | No explicit failure translation or catch is added. If a function/block exit destroys automatic objects, exception behavior follows those destructors; namespace/type closes have no runtime failure path. |
| cost | The delimiter adds no algorithmic work. A function/block exit can run existing automatic-object destructors and cleanup; namespace/type closes have no runtime cost. |
| Design | [src/frontend/parser.cpp](../../../../../src/frontend/parser.cpp), [docs/code_specs/files/src/frontend/parser.cpp.md](parser.cpp.md), [docs/sql_parser.md](../../../../sql_parser.md), [docs/sql_binding.md](../../../../sql_binding.md) |
