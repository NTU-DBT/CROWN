# `include/crown/frontend/parser.hpp` — block usage map

[Source](../../../../../../include/crown/frontend/parser.hpp) · [Source index](../../../../README.md) · [Subsystem contracts](../../../../subsystem_contracts.md) · [Reviewed primitives](../../../../primitives.md)

Own the libpg_query parse result and expose the admitted parser representation.

Snapshot SHA-256: `dc006247071641a727f278b8f078d706c7f914137fe0cc025c80f6b1ca6a21d9`. 41 lines partitioned into 6 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [frontend](../../../../subsystem_contracts.md#frontend). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/sql_support.md](../../../../../sql_support.md), [docs/sql_parser.md](../../../../../sql_parser.md), [docs/sql_binding.md](../../../../../sql_binding.md), [docs/sql_normalization.md](../../../../../sql_normalization.md), [docs/sql_admission.md](../../../../../sql_admission.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–13](../../../../../../include/crown/frontend/parser.hpp#L1) | Imports dependencies; guards repeated header inclusion; declares namespace scope. | source comment (unverified): // Offsets are bytes into the owned UTF-8 source, with an exclusive end. · [reviewed contract](#b0001) |
| [B0002 · 14–18](../../../../../../include/crown/frontend/parser.hpp#L14) | Type/record definition: struct SourceRange | source comment (unverified): // Offsets are bytes into the owned UTF-8 source, with an exclusive end. · [reviewed contract](#b0002) |
| [B0003 · 19–26](../../../../../../include/crown/frontend/parser.hpp#L19) | Type/record definition: struct SqlDiagnostic | source comment (unverified): // One based, as in PostgreSQL. · [reviewed contract](#b0003) |
| [B0004 · 27–31](../../../../../../include/crown/frontend/parser.hpp#L27) | Type/record definition: struct SqlSyntax |  · [reviewed contract](#b0004) |
| [B0005 · 32–35](../../../../../../include/crown/frontend/parser.hpp#L32) | Type/record definition: struct ParseLimits |  · [reviewed contract](#b0005) |
| [B0006 · 36–41](../../../../../../include/crown/frontend/parser.hpp#L36) | declares aliases; declares values/defaults or compile-time conditions. | source comment (unverified): // Exactly one nonempty statement; parsing grants no semantic admission. · [reviewed contract](#b0006) |

## B0001

[Lines 1–13](../../../../../../include/crown/frontend/parser.hpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L1-L13:sha256:73af2f89c0072e045fdde055ea608fad60e78d1b2affd70a1186d4a73521d7df
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Header guard, parser result/JSON dependencies, and crown::frontend namespace opening; the following SourceRange declaration stores byte offsets into SQL source. Embedded source note records intended usage: Offsets are bytes into the owned UTF-8 source, with an exclusive end. PostgreSQL node \`location\` fields remain byte offsets in the untouched AST. Treat that prose as guidance, not as independently verified executable behavior. |
| inputs / outputs | No runtime inputs/outputs are declared by the import/scope lines themselves. |
| invariants | The header guard prevents repeat inclusion in a translation unit; imported declarations determine compile-time names. The note/type comments in this span are guidance and do not add runtime validation or a capability. |
| ownership | No object ownership is created by the imports or namespace tokens. |
| failure | No runtime failure path is introduced by the guard/imports; incompatible or missing declarations fail during compilation or linking. |
| cost | Preprocessor/compiler work only for these lines; the guard adds no per-operation runtime work. |
| Design | [include/crown/frontend/parser.hpp](../../../../../../include/crown/frontend/parser.hpp), [docs/code_specs/files/include/crown/frontend/parser.hpp.md](parser.hpp.md), [docs/sql_parser.md](../../../../../sql_parser.md), [docs/sql_binding.md](../../../../../sql_binding.md) |

## B0002

[Lines 14–18](../../../../../../include/crown/frontend/parser.hpp#L14); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct SourceRange
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Represent a half-open byte interval in the owned UTF-8 SQL source. |
| inputs / outputs | Two \`size_t\` offsets, \`begin\` and \`end\`, defaulting to zero; comparable as a value. |
| invariants | Parser-produced ranges satisfy begin &lt;= end &lt;= source.size(); the aggregate type itself does not enforce that relation. PostgreSQL AST locations remain byte offsets. |
| ownership | Owns only scalar offsets; no source buffer is retained. |
| failure | No constructor validation or failure path. |
| cost | Fixed-size value, O(1) copy/compare. |
| Design | [docs/sql_parser.md](../../../../../sql_parser.md), [src/frontend/parser.cpp](../../../../../../src/frontend/parser.cpp) |

## B0003

[Lines 19–26](../../../../../../include/crown/frontend/parser.hpp#L19); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct SqlDiagnostic
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Carry an owned SQL diagnostic and optional source coordinates. |
| inputs / outputs | Code/message strings and optional byte, character, line, and column positions. |
| invariants | Coordinate conventions are documented: byte offset zero-based; PostgreSQL character position, line, and Unicode-code-point column one-based. Malformed UTF-8 may have only a byte offset. |
| ownership | Owns strings and scalar optionals; no parser-owned pointers. |
| failure | The record does not validate code or coordinate consistency; parser construction establishes it. |
| cost | Fixed scalar fields plus code/message string storage. |
| Design | [docs/sql_parser.md](../../../../../sql_parser.md), [src/frontend/parser.cpp](../../../../../../src/frontend/parser.cpp) |

## B0004

[Lines 27–31](../../../../../../include/crown/frontend/parser.hpp#L27); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct SqlSyntax
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Own a parsed source, complete AST JSON, and one statement’s range. |
| inputs / outputs | UTF-8 source string, \`nlohmann::json\` AST, and half-open \`SourceRange\`. |
| invariants | A successful parser result represents exactly one nonempty statement; retaining source and untouched AST preserves byte locations. This is syntax only, not binding or support. |
| ownership | Owns every field, so it survives later parser calls and upstream thread cleanup. |
| failure | The aggregate itself permits arbitrary values; \`parse_sql\` validates producer results before returning it. |
| cost | Source and AST sizes grow with the full input/parse tree; copying this record copies owned state. |
| Design | [docs/sql_parser.md](../../../../../sql_parser.md), [src/frontend/parser.cpp](../../../../../../src/frontend/parser.cpp) |

## B0005

[Lines 32–35](../../../../../../include/crown/frontend/parser.hpp#L32); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct ParseLimits
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Expose source-byte and AST-nesting bounds for the parser wrapper. |
| inputs / outputs | \`source_bytes\` defaults to 1 MiB and \`ast_depth\` to 256; callers may pass other limits. |
| invariants | The wrapper also enforces the upstream C API \`int\` size bound. These are operational caps, not a total memory or wall-time guarantee. |
| ownership | Plain scalar options copied by value into \`parse_sql\`. |
| failure | No construction failure. A request beyond a configured bound becomes a diagnostic in the parser. |
| cost | Fixed-size value; enforcing limits requires scans/AST decode work at call time. |
| Design | [docs/sql_parser.md](../../../../../sql_parser.md), [src/frontend/parser.cpp](../../../../../../src/frontend/parser.cpp) |

## B0006

[Lines 36–41](../../../../../../include/crown/frontend/parser.hpp#L36); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
using SqlParseResult = std::variant<SqlSyntax, SqlDiagnostic>;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Expose the syntax-success/diagnostic result type and parser entry point. |
| inputs / outputs | \`SqlParseResult\` owns either alternative; \`parse_sql\` takes a borrowed source view plus defaulted \`ParseLimits\`. |
| invariants | A successful alternative means one statement parsed syntactically; it grants no semantic admission. Both result alternatives are independent of libpg_query storage. |
| ownership | Variant owns its selected payload; the function returns by value. |
| failure | Diagnostics represent declared input/resource rejection; unexpected upstream-contract failures may throw \`Error\`. |
| cost | Returning success transfers/moves owned source and AST; JSON decode and copy costs are paid before return. |
| Design | [docs/sql_parser.md](../../../../../sql_parser.md), [src/frontend/parser.cpp](../../../../../../src/frontend/parser.cpp) |
