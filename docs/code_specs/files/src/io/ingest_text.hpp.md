# `src/io/ingest_text.hpp` — block usage map

[Source](../../../../../src/io/ingest_text.hpp) · [Source index](../../../README.md) · [Subsystem contracts](../../../subsystem_contracts.md) · [Reviewed primitives](../../../primitives.md)

Admit bounded external documents/records and serialize explicit public representations at the engine boundary.

Snapshot SHA-256: `d15957ed079ae4d332f51e379cbe415863f42214b76b7fac3b8bf4a163d7349b`. 8 lines partitioned into 1 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [io](../../../subsystem_contracts.md#io). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/ingestion.md](../../../../ingestion.md), [docs/query_identity.md](../../../../query_identity.md), [docs/schema_evolution.md](../../../../schema_evolution.md), [docs/cli.md](../../../../cli.md), [docs/query_memory.md](../../../../query_memory.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–8](../../../../../src/io/ingest_text.hpp#L1) | Imports dependencies; guards repeated header inclusion; declares namespace scope; declares callable signatures. | source comment (unverified): // Shared strict UTF-8 validation; callers enforce their own byte/domain limits. · [reviewed contract](#b0001) |

## B0001

[Lines 1–8](../../../../../src/io/ingest_text.hpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void require_utf8(std::string_view text);
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Declare the one shared strict UTF-8 validator retained by the native IO consumers. |
| inputs / outputs | Accepts borrowed string_view and either returns after complete scalar-encoding validation or propagates invalid_document. |
| invariants | This private interface does not impose byte/domain/source-name limits, normalize accepted text, acknowledge input or control retry/poison semantics. |
| ownership | Borrows stable text for the call and retains no owner or bytes. |
| failure | Malformed UTF-8 raises the existing public diagnostic through the unchanged implementation; no handler or fallback is introduced. |
| cost | Linear byte validation with bounded per-codepoint work and no successful heap allocation; callers retain their own separate limits and ownership checks. |
| Design | [src/io/ingest_text.hpp](../../../../../src/io/ingest_text.hpp), [src/io/ingest_text.cpp](../../../../../src/io/ingest_text.cpp), [src/io/native_decode.cpp](../../../../../src/io/native_decode.cpp), [src/io/event_reader.cpp](../../../../../src/io/event_reader.cpp), [src/io/input_view.cpp](../../../../../src/io/input_view.cpp), [src/io/inspection.cpp](../../../../../src/io/inspection.cpp), [src/io/checkpoint_detail.hpp](../../../../../src/io/checkpoint_detail.hpp), [docs/ingestion.md](../../../../ingestion.md) |
