# `include/crown/io/sql.hpp` — block usage map

[Source](../../../../../../include/crown/io/sql.hpp) · [Source index](../../../../README.md) · [Subsystem contracts](../../../../subsystem_contracts.md) · [Reviewed primitives](../../../../primitives.md)

Admit bounded external documents/records and serialize explicit public representations at the engine boundary.

Snapshot SHA-256: `dbf8aedbc42a10f27d84e571bff6eaf66105030d617c85d93ea1c6a9e8c3eb37`. 7 lines partitioned into 1 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [io](../../../../subsystem_contracts.md#io). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/ingestion.md](../../../../../ingestion.md), [docs/query_identity.md](../../../../../query_identity.md), [docs/schema_evolution.md](../../../../../schema_evolution.md), [docs/cli.md](../../../../../cli.md), [docs/query_memory.md](../../../../../query_memory.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–7](../../../../../../include/crown/io/sql.hpp#L1) | Imports dependencies; guards repeated header inclusion; declares namespace scope; declares callable signatures; declares values/defaults or compile-time conditions. | source comment (unverified): // namespace crown::io · [reviewed contract](#b0001) |

## B0001

[Lines 1–7](../../../../../../include/crown/io/sql.hpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
[[nodiscard]] nlohmann::json write_sql_parse(const frontend::SqlParseResult& result);
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Serialize the result of SQL parsing at the syntax boundary. |
| inputs / outputs | The writer accepts \`SqlParseResult\` and returns syntax/source/AST or diagnostic JSON with parser labels. |
| invariants | Success reports \`admission_status:not_checked\`; an AST is not a bound SQL program or execution plan. Parser-version strings are output metadata, not semantic admission. |
| ownership | The DOM copies source and the ordinary AST, or diagnostic fields, independent of parse result lifetime. |
| failure | JSON DOM allocation can fail; parser rejection is represented by the diagnostic alternative rather than converted into a binding claim. |
| cost | Copies the complete parser AST/source into an ordinary DOM; no work, output-byte, or memory cap is part of this declaration. |
| Design | [include/crown/io/sql.hpp §writer declaration](../../../../../../include/crown/io/sql.hpp), [src/io/sql.cpp §syntax export](../../../../../../src/io/sql.cpp), [include/crown/frontend/parser.hpp §SqlParseResult](../../../../../../include/crown/frontend/parser.hpp), [docs/sql_parser.md §parser boundary](../../../../../sql_parser.md) |
