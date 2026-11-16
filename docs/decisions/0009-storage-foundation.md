# Decision 0009: typed layouts and the reference storage contract

Status: S01/S02 verified, 2026-11-05. This records the storage foundation;
the wider refactor and release gates remain open.

Use immutable ordered tuple layouts with typed field metadata and shared
runtime tokens. Tuples own and validate their scalar values. Compiled
projections select numeric slots and produce keys under an explicit target
layout token. Permit composite, reordered, repeated, and nullary projections.
Projection source and target contexts must agree; scalar kinds must match,
decimal domains may widen exactly, and repeated target variables require an
equality proof from the source layout. Different source layouts can interoperate
through one shared target token. Descriptor equality alone does not establish
runtime token identity.

Keep storage identity exact and typed. Runtime tuple/index IDs are nonzero,
monotonic within their table owner, and not reused after erase or clear.
Handles include owner and relation identity. The initial backend is a standard
map/set reference table with primary full-row lookup and secondary key
buckets; empty buckets are removed. Duplicate/absent no-ops leave the revision
unchanged. Row changes, nonempty clear, and index add/drop advance it and
invalidate live cursors. Live and bucket cursors hold a weak owner and fail
fast; `snapshot()` returns owning tuple copies. Storage operations are
single-threaded, require external synchronization for concurrent use, and
provide per-table strong exception rollback.

The v1 wire descriptors contain no runtime token. Layout reads create a fresh
token; projection reads require caller-supplied source and target layouts and
bind to those tokens after checking complete descriptors. The exact wire
contracts are [tuple-layout v1](../../schemas/tuple-layout-v1.schema.json) and
[key-projection v1](../../schemas/key-projection-v1.schema.json).

See [storage.md](../storage.md) for the API and limits, and the
[storage verification packet](../verification/storage-2026-11-05.md) for the
acceptance audit and final build matrix. Arenas, generational handles,
pinning/reclamation, optimized indexes, quotas/accounting, and maintained
query/join runtime work remain S03–S05/R work.
