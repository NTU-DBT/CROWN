# `include/crown/io/cursor_observation.hpp` — block usage map

[Source](../../../../../../include/crown/io/cursor_observation.hpp) · [Source index](../../../../README.md) · [Subsystem contracts](../../../../subsystem_contracts.md) · [Reviewed primitives](../../../../primitives.md)

Admit bounded external documents/records and serialize explicit public representations at the engine boundary.

Snapshot SHA-256: `7f0fd6e6abf951ebac847762c69fb6e79b10b1638b2a262cf6f733c9323b8397`. 7 lines partitioned into 1 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [io](../../../../subsystem_contracts.md#io). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/ingestion.md](../../../../../ingestion.md), [docs/query_identity.md](../../../../../query_identity.md), [docs/schema_evolution.md](../../../../../schema_evolution.md), [docs/cli.md](../../../../../cli.md), [docs/query_memory.md](../../../../../query_memory.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–7](../../../../../../include/crown/io/cursor_observation.hpp#L1) | Imports dependencies; guards repeated header inclusion; declares namespace scope; declares callable signatures; declares values/defaults or compile-time conditions. | source comment (unverified): // namespace crown::io · [reviewed contract](#b0001) |

## B0001

[Lines 1–7](../../../../../../include/crown/io/cursor_observation.hpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
[[nodiscard]] std::string write_cursor_observation_json(const runtime::CursorObservation&,std::size_t max_bytes=16*1024*1024);
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Declare JSON string exporters for one cursor observation and committed-state gauges. |
| inputs / outputs | The cursor overload accepts its observation; two gauge overloads accept live committed or previously captured gauges. Each takes a default 16 MiB encoded-byte limit. |
| invariants | Formatting reads supplied values without advancing a cursor. Availability flags preserve unavailable/disabled values as null; captured gauge export does not rescan the engine or prove total memory. |
| ownership | Each result is an ordinary owning string; DTO input remains caller-owned. |
| failure | Invalid UTF-8 in serialized text or exceeding the appended-byte limit throws. The cap does not bound string capacity or temporary allocation. |
| cost | Work follows serialized metric/configuration/base/node entries and text length; constructing the JSON string uses ordinary allocation outside cursor work. |
| Design | [include/crown/io/cursor_observation.hpp §overloads and defaults](../../../../../../include/crown/io/cursor_observation.hpp), [src/io/cursor_observation.cpp §writer and gauge serialization](../../../../../../src/io/cursor_observation.cpp), [src/io/explain.cpp §diagnostic callers](../../../../../../src/io/explain.cpp), [docs/measurement.md §cursor observation](../../../../../measurement.md) |
