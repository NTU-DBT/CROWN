# Independent O08 workflow fixtures

These five fixtures pair one SQL statement, one standalone catalog, and an ordered physical-event JSONL template with separately generated expected current sets and raw signed set differences. `generate_fixtures.py` uses only Python's standard library; every expected query is a direct finite set comprehension over the current physical table sets.

`events.template.jsonl` contains the logical physical event plus explicit contiguous sequence, catalog/source-schema versions, and strictly increasing source positions. It intentionally omits `catalog_sha256`; a future native runner must compute that binding from the native canonical catalog output and add it to each input record. No native executable was run to derive expected rows or deltas.

The scalar fixture uses JSON strings containing both an escaped NUL and literal UTF-8, JSON booleans, and the native tagged `date` and `decimal` forms. Decimal equality in the independent oracle uses `decimal.Decimal`; output spellings are canonicalized as fixed decimal text.

## Limits

The fixtures and their independent oracles are not a CLI acceptance result. The query admissions, native SQL types, runtime snapshots, local-sink epochs, and recovery behavior have not been built or executed here. Event records need the runner-filled catalog hash before `EventReader` accepts them. Source offsets are logical strictly increasing markers, not byte offsets into the JSONL template. The oracles model finite set semantics and do not prove performance, resource bounds, or durability.
