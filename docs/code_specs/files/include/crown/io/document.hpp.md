# `include/crown/io/document.hpp` — block usage map

[Source](../../../../../../include/crown/io/document.hpp) · [Source index](../../../../README.md) · [Subsystem contracts](../../../../subsystem_contracts.md) · [Reviewed primitives](../../../../primitives.md)

Admit bounded external documents/records and serialize explicit public representations at the engine boundary.

Snapshot SHA-256: `ac7b1fba2bb4fcc3b76a27666cfc06725ccd8f56a84671feba7bf637a5b3aa3b`. 22 lines partitioned into 1 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [io](../../../../subsystem_contracts.md#io). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/ingestion.md](../../../../../ingestion.md), [docs/query_identity.md](../../../../../query_identity.md), [docs/schema_evolution.md](../../../../../schema_evolution.md), [docs/cli.md](../../../../../cli.md), [docs/query_memory.md](../../../../../query_memory.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–22](../../../../../../include/crown/io/document.hpp#L1) | Imports dependencies; guards repeated header inclusion; declares namespace scope; declares aliases; declares callable signatures; declares values/defaults or compile-time conditions. | source comment (unverified): // Strict external JSON boundary: reject duplicate keys and nesting beyond256 · [reviewed contract](#b0001) |

## B0001

[Lines 1–22](../../../../../../include/crown/io/document.hpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
using Json = nlohmann::json;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Name the JSON DOM and expose strict CQ document, scalar, relation, and reference-epoch codecs. |
| inputs / outputs | Readers parse JSON/scalars/documents; writers encode a \`Document\`, scalar/view, relation, or committed epoch; \`upgrade_document\` validates and converts upward among formats 1–3. |
| invariants | Parsing rejects duplicate keys and nesting over 256. Typed scalar and document versions remain strict; document serialization/upgrade does not admit or execute a native program. |
| ownership | Returned \`Json\`, \`Document\`, values, rows, and relations own ordinary storage; scalar-view writing copies its borrowed scalar into the DOM. |
| failure | Unknown fields, bad versions, duplicate keys, invalid sequences/references, unsupported types, and type/domain errors throw documented \`Error\`s. DOM/key-set allocation may fail separately. |
| cost | Read builds a DOM plus duplicate-key sets and owning model; write/upgrade traverse and build full ordinary DOMs, including rows/updates. Nesting is capped, but total input/output bytes and all heap use are not capped here. |
| Design | [include/crown/io/document.hpp §public declarations](../../../../../../include/crown/io/document.hpp), [src/io/json.hpp §strict parser](../../../../../../src/io/json.hpp), [src/io/document.cpp §document/scalar codecs](../../../../../../src/io/document.cpp), [docs/semantics.md §document boundary](../../../../../semantics.md), [docs/scalars.md §typed JSON](../../../../../scalars.md), [docs/schema_evolution.md §migration](../../../../../schema_evolution.md) |
