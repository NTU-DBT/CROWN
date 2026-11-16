# `include/crown/io/catalog_source.hpp` — block usage map

[Source](../../../../../../include/crown/io/catalog_source.hpp) · [Source index](../../../../README.md) · [Subsystem contracts](../../../../subsystem_contracts.md) · [Reviewed primitives](../../../../primitives.md)

Admit bounded external documents/records and serialize explicit public representations at the engine boundary.

Snapshot SHA-256: `367297ff55e7fb9f938dea32e5885035edde9110d5c1b8c04d7060be8430b282`. 10 lines partitioned into 1 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [io](../../../../subsystem_contracts.md#io). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/ingestion.md](../../../../../ingestion.md), [docs/query_identity.md](../../../../../query_identity.md), [docs/schema_evolution.md](../../../../../schema_evolution.md), [docs/cli.md](../../../../../cli.md), [docs/query_memory.md](../../../../../query_memory.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–10](../../../../../../include/crown/io/catalog_source.hpp#L1) | Imports dependencies; guards repeated header inclusion; declares namespace scope; declares aliases; declares values/defaults or compile-time conditions. | source comment (unverified): // Compiler callers may supply an owned catalog. Runtime readers share the · [reviewed contract](#b0001) |

## B0001

[Lines 1–10](../../../../../../include/crown/io/catalog_source.hpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
using CatalogSource=std::variant<Catalog,std::shared_ptr<const program::Catalog>>;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Let input owners use either an ordinary catalog copy or an immutable catalog view retained by a compiled program. |
| inputs / outputs | \`CatalogSource\` is a variant of \`Catalog\` and \`shared_ptr&lt;const program::Catalog&gt;\`; ingestion and typed queues read the selected schema through a visitor. |
| invariants | The native shared pointer must be nonempty at the dispatch boundary. Choosing a variant alternative does not validate catalog semantics or transfer catalog payload into a new catalog copy. |
| ownership | The ordinary alternative owns its catalog. \`CompiledProgram::source_catalog_owner()\` creates an aliasing shared pointer that keeps the original program control and catalog alive. |
| failure | The visitor rejects a null native shared pointer. Input constructors validate ordinary catalog input while computing its fingerprint; the admitted \`CompiledProgram\` bridge skips that redundant catalog validation and relies on program provenance. The alias itself checks no catalog semantics. |
| cost | Variant dispatch is fixed; native access retains shared control rather than copying the full catalog. Fingerprinting and per-input validation traverse catalog/data separately. |
| Design | [include/crown/io/catalog_source.hpp §CatalogSource alias](../../../../../../include/crown/io/catalog_source.hpp), [src/io/catalog_source.hpp §visitor and null-owner check](../../../../../../src/io/catalog_source.hpp), [src/io/event_reader.cpp §reader construction](../../../../../../src/io/event_reader.cpp), [src/io/ingest.cpp §non-admitted catalog fingerprint validation](../../../../../../src/io/ingest.cpp), [src/ir/program.cpp §source_catalog_owner](../../../../../../src/ir/program.cpp), [src/io/batch_program.cpp §typed queue bridge](../../../../../../src/io/batch_program.cpp), [src/io/ingest_program.cpp §event reader bridge](../../../../../../src/io/ingest_program.cpp) |
