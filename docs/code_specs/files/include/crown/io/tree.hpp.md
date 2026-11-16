# `include/crown/io/tree.hpp` — block usage map

[Source](../../../../../../include/crown/io/tree.hpp) · [Source index](../../../../README.md) · [Subsystem contracts](../../../../subsystem_contracts.md) · [Reviewed primitives](../../../../primitives.md)

Admit bounded external documents/records and serialize explicit public representations at the engine boundary.

Snapshot SHA-256: `a5d08b327fa4be8effb7efc38ab18ec1abd11d667809b4ed1cbe10d313fde982`. 10 lines partitioned into 1 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [io](../../../../subsystem_contracts.md#io). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/ingestion.md](../../../../../ingestion.md), [docs/query_identity.md](../../../../../query_identity.md), [docs/schema_evolution.md](../../../../../schema_evolution.md), [docs/cli.md](../../../../../cli.md), [docs/query_memory.md](../../../../../query_memory.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–10](../../../../../../include/crown/io/tree.hpp#L1) | Imports dependencies; guards repeated header inclusion; declares namespace scope; declares callable signatures; declares values/defaults or compile-time conditions. | source comment (unverified): // namespace crown::io · [reviewed contract](#b0001) |

## B0001

[Lines 1–10](../../../../../../include/crown/io/tree.hpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
[[nodiscard]] FreeConnexTree read_tree(std::string_view text, const Catalog& catalog, const Query& query);
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Declare tree DTO read/write and serialization of a supplied validation report. |
| inputs / outputs | \`read_tree\` binds JSON names to a provided catalog/query and returns a \`FreeConnexTree\`; writers serialize a tree or \`ValidationReport\`. |
| invariants | Reader checks envelope/version/catalog binding and addressable IDs but leaves graph structure, scopes, and height claims to \`validate_tree\`. \`write_validation\` formats the given aggregate and does not rerun verification. |
| ownership | The returned tree owns node IDs, scopes, children, and optional claims; output DOM owns names and report arrays. |
| failure | Malformed shape, duplicate/unknown IDs, unsupported versions/semantics, or catalog mismatch are rejected; incorrect but addressable structure is left for the verifier. |
| cost | Parsing maps names to dense IDs and builds vectors/sets; writers traverse nodes, scopes, and violations into ordinary DOM. |
| Design | [include/crown/io/tree.hpp §public declarations](../../../../../../include/crown/io/tree.hpp), [src/io/document.cpp §tree codecs and report formatter](../../../../../../src/io/document.cpp), [src/planner/verify.cpp §structural validation](../../../../../../src/planner/verify.cpp), [docs/tree_oracle.md §independent tree verification](../../../../../tree_oracle.md) |
