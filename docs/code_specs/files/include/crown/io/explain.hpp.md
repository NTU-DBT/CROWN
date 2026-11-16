# `include/crown/io/explain.hpp` — block usage map

[Source](../../../../../../include/crown/io/explain.hpp) · [Source index](../../../../README.md) · [Subsystem contracts](../../../../subsystem_contracts.md) · [Reviewed primitives](../../../../primitives.md)

Admit bounded external documents/records and serialize explicit public representations at the engine boundary.

Snapshot SHA-256: `f3d46de431b1d2bfad28d01c47c1d81cdf5ef413e4ec93b7a566aed16f0d7f6c`. 19 lines partitioned into 3 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [io](../../../../subsystem_contracts.md#io). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/ingestion.md](../../../../../ingestion.md), [docs/query_identity.md](../../../../../query_identity.md), [docs/schema_evolution.md](../../../../../schema_evolution.md), [docs/cli.md](../../../../../cli.md), [docs/query_memory.md](../../../../../query_memory.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–5](../../../../../../include/crown/io/explain.hpp#L1) | Imports dependencies; guards repeated header inclusion; declares namespace scope. |  · [reviewed contract](#b0001) |
| [B0002 · 6–6](../../../../../../include/crown/io/explain.hpp#L6) | Type/record definition: struct ExplainTextLimits |  · [reviewed contract](#b0002) |
| [B0003 · 7–19](../../../../../../include/crown/io/explain.hpp#L7) | declares values/defaults or compile-time conditions. | source comment (unverified): // Strict UTF-8 text transport. Native admission remains arbitrary-byte safe. · [reviewed contract](#b0003) |

## B0001

[Lines 1–5](../../../../../../include/crown/io/explain.hpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
#pragma once
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Declare the io explain public interface and its required types. |
| inputs / outputs | Header imports its explicit dependencies and declares the APIs/contracts below. |
| invariants | Inclusion does not construct a live query, source, report, proof or file owner. |
| ownership | Declarations retain no instance; object ownership and copies are specified at the individual APIs. |
| failure | Compile-time dependency/declaration boundary; runtime failures belong to instantiated objects/operations. |
| cost | No runtime action from inclusion itself; inline methods retain their stated actual costs. |
| Design | [include/crown/io/explain.hpp](../../../../../../include/crown/io/explain.hpp), [src/io/explain.cpp](../../../../../../src/io/explain.cpp), [src/io/query_explain.cpp](../../../../../../src/io/query_explain.cpp), [docs/observability.md](../../../../../observability.md) |

## B0002

[Lines 6–6](../../../../../../include/crown/io/explain.hpp#L6); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct ExplainTextLimits {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Bound one final encoded EXPLAIN artifact. |
| inputs / outputs | Default16 MiB encoded-byte allowance passed to the manual strict-UTF8 writers. |
| invariants | Encoded length is not string capacity, retained report memory or total process memory. |
| ownership | Inline fixed fields only; copying these values allocates no container or text. No source/native owner is retained. |
| failure | Declaration/field initialization performs no semantic validation. Consumers validate the actual values at their own boundary. |
| cost | Fixed-size initialization/copy/comparison; declaration itself performs no runtime scan or I/O. |
| Design | [include/crown/io/explain.hpp](../../../../../../include/crown/io/explain.hpp), [src/io/explain.cpp](../../../../../../src/io/explain.cpp), [src/io/query_explain.cpp](../../../../../../src/io/query_explain.cpp), [docs/observability.md](../../../../../observability.md) |

## B0003

[Lines 7–19](../../../../../../include/crown/io/explain.hpp#L7); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
write_explain_json(const observability::PlanExplanation&
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Export PlanExplanation as complete json text. |
| inputs / outputs | Serializes the already admitted selected physical plan and captured metadata; tree form is its checked selected tree, not automatically an original minimum proof. |
| invariants | Strict UTF8/encoded-byte admission affects only this export. No search advance, source acceptance, native mutation or JSON DOM construction. |
| ownership | Borrows immutable report; returns an ordinary owning string outside native report/account storage. Nested query wrappers can overlap inner and outer strings. |
| failure | Encoding, byte-limit, absent-witness, moved-from report or ordinary allocation failure returns no complete artifact and leaves producer/native state unchanged. |
| cost | Visits rendered metadata/tree/trace/scalars and emits escaped bytes. Wrappers may construct/copy an inner result before outer append; no total peak-memory cap. |
| Design | [include/crown/io/explain.hpp](../../../../../../include/crown/io/explain.hpp), [src/io/explain.cpp](../../../../../../src/io/explain.cpp), [src/io/query_explain.cpp](../../../../../../src/io/query_explain.cpp), [docs/observability.md](../../../../../observability.md) |

```text
write_explain_text(const observability::PlanExplanation&
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Export PlanExplanation as complete text text. |
| inputs / outputs | Serializes the already admitted selected physical plan and captured metadata; tree form is its checked selected tree, not automatically an original minimum proof. |
| invariants | Strict UTF8/encoded-byte admission affects only this export. No search advance, source acceptance, native mutation or JSON DOM construction. |
| ownership | Borrows immutable report; returns an ordinary owning string outside native report/account storage. Nested query wrappers can overlap inner and outer strings. |
| failure | Encoding, byte-limit, absent-witness, moved-from report or ordinary allocation failure returns no complete artifact and leaves producer/native state unchanged. |
| cost | Visits rendered metadata/tree/trace/scalars and emits escaped bytes. Wrappers may construct/copy an inner result before outer append; no total peak-memory cap. |
| Design | [include/crown/io/explain.hpp](../../../../../../include/crown/io/explain.hpp), [src/io/explain.cpp](../../../../../../src/io/explain.cpp), [src/io/query_explain.cpp](../../../../../../src/io/query_explain.cpp), [docs/observability.md](../../../../../observability.md) |

```text
write_explain_dot(const observability::PlanExplanation&
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Export PlanExplanation as complete dot text. |
| inputs / outputs | Serializes the already admitted selected physical plan and captured metadata; tree form is its checked selected tree, not automatically an original minimum proof. |
| invariants | Strict UTF8/encoded-byte admission affects only this export. No search advance, source acceptance, native mutation or JSON DOM construction. |
| ownership | Borrows immutable report; returns an ordinary owning string outside native report/account storage. Nested query wrappers can overlap inner and outer strings. |
| failure | Encoding, byte-limit, absent-witness, moved-from report or ordinary allocation failure returns no complete artifact and leaves producer/native state unchanged. |
| cost | Visits rendered metadata/tree/trace/scalars and emits escaped bytes. Wrappers may construct/copy an inner result before outer append; no total peak-memory cap. |
| Design | [include/crown/io/explain.hpp](../../../../../../include/crown/io/explain.hpp), [src/io/explain.cpp](../../../../../../src/io/explain.cpp), [src/io/query_explain.cpp](../../../../../../src/io/query_explain.cpp), [docs/observability.md](../../../../../observability.md) |

```text
write_explain_tree_json(const observability::PlanExplanation&
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Export PlanExplanation as complete tree json text. |
| inputs / outputs | Serializes the already admitted selected physical plan and captured metadata; tree form is its checked selected tree, not automatically an original minimum proof. |
| invariants | Strict UTF8/encoded-byte admission affects only this export. No search advance, source acceptance, native mutation or JSON DOM construction. |
| ownership | Borrows immutable report; returns an ordinary owning string outside native report/account storage. Nested query wrappers can overlap inner and outer strings. |
| failure | Encoding, byte-limit, absent-witness, moved-from report or ordinary allocation failure returns no complete artifact and leaves producer/native state unchanged. |
| cost | Visits rendered metadata/tree/trace/scalars and emits escaped bytes. Wrappers may construct/copy an inner result before outer append; no total peak-memory cap. |
| Design | [include/crown/io/explain.hpp](../../../../../../include/crown/io/explain.hpp), [src/io/explain.cpp](../../../../../../src/io/explain.cpp), [src/io/query_explain.cpp](../../../../../../src/io/query_explain.cpp), [docs/observability.md](../../../../../observability.md) |

```text
write_explain_json(const observability::QueryExplanation&
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Export QueryExplanation as complete json text. |
| inputs / outputs | Wraps/delegates the typed query writer; tree/DOT needs an actual published checked witness. |
| invariants | Strict UTF8/encoded-byte admission affects only this export. No search advance, source acceptance, native mutation or JSON DOM construction. |
| ownership | Borrows immutable report; returns an ordinary owning string outside native report/account storage. Nested query wrappers can overlap inner and outer strings. |
| failure | Encoding, byte-limit, absent-witness, moved-from report or ordinary allocation failure returns no complete artifact and leaves producer/native state unchanged. |
| cost | Visits rendered metadata/tree/trace/scalars and emits escaped bytes. Wrappers may construct/copy an inner result before outer append; no total peak-memory cap. |
| Design | [include/crown/io/explain.hpp](../../../../../../include/crown/io/explain.hpp), [src/io/explain.cpp](../../../../../../src/io/explain.cpp), [src/io/query_explain.cpp](../../../../../../src/io/query_explain.cpp), [docs/observability.md](../../../../../observability.md) |

```text
write_explain_text(const observability::QueryExplanation&
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Export QueryExplanation as complete text text. |
| inputs / outputs | Wraps/delegates the typed query writer; tree/DOT needs an actual published checked witness. |
| invariants | Strict UTF8/encoded-byte admission affects only this export. No search advance, source acceptance, native mutation or JSON DOM construction. |
| ownership | Borrows immutable report; returns an ordinary owning string outside native report/account storage. Nested query wrappers can overlap inner and outer strings. |
| failure | Encoding, byte-limit, absent-witness, moved-from report or ordinary allocation failure returns no complete artifact and leaves producer/native state unchanged. |
| cost | Visits rendered metadata/tree/trace/scalars and emits escaped bytes. Wrappers may construct/copy an inner result before outer append; no total peak-memory cap. |
| Design | [include/crown/io/explain.hpp](../../../../../../include/crown/io/explain.hpp), [src/io/explain.cpp](../../../../../../src/io/explain.cpp), [src/io/query_explain.cpp](../../../../../../src/io/query_explain.cpp), [docs/observability.md](../../../../../observability.md) |

```text
write_explain_dot(const observability::QueryExplanation&
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Export QueryExplanation as complete dot text. |
| inputs / outputs | Wraps/delegates the typed query writer; tree/DOT needs an actual published checked witness. |
| invariants | Strict UTF8/encoded-byte admission affects only this export. No search advance, source acceptance, native mutation or JSON DOM construction. |
| ownership | Borrows immutable report; returns an ordinary owning string outside native report/account storage. Nested query wrappers can overlap inner and outer strings. |
| failure | Encoding, byte-limit, absent-witness, moved-from report or ordinary allocation failure returns no complete artifact and leaves producer/native state unchanged. |
| cost | Visits rendered metadata/tree/trace/scalars and emits escaped bytes. Wrappers may construct/copy an inner result before outer append; no total peak-memory cap. |
| Design | [include/crown/io/explain.hpp](../../../../../../include/crown/io/explain.hpp), [src/io/explain.cpp](../../../../../../src/io/explain.cpp), [src/io/query_explain.cpp](../../../../../../src/io/query_explain.cpp), [docs/observability.md](../../../../../observability.md) |

```text
write_explain_tree_json(const observability::QueryExplanation&
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Export QueryExplanation as complete tree json text. |
| inputs / outputs | Wraps/delegates the typed query writer; tree/DOT needs an actual published checked witness. |
| invariants | Strict UTF8/encoded-byte admission affects only this export. No search advance, source acceptance, native mutation or JSON DOM construction. |
| ownership | Borrows immutable report; returns an ordinary owning string outside native report/account storage. Nested query wrappers can overlap inner and outer strings. |
| failure | Encoding, byte-limit, absent-witness, moved-from report or ordinary allocation failure returns no complete artifact and leaves producer/native state unchanged. |
| cost | Visits rendered metadata/tree/trace/scalars and emits escaped bytes. Wrappers may construct/copy an inner result before outer append; no total peak-memory cap. |
| Design | [include/crown/io/explain.hpp](../../../../../../include/crown/io/explain.hpp), [src/io/explain.cpp](../../../../../../src/io/explain.cpp), [src/io/query_explain.cpp](../../../../../../src/io/query_explain.cpp), [docs/observability.md](../../../../../observability.md) |
