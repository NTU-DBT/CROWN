# `include/crown/io/query_explain.hpp` — block usage map

[Source](../../../../../../include/crown/io/query_explain.hpp) · [Source index](../../../../README.md) · [Subsystem contracts](../../../../subsystem_contracts.md) · [Reviewed primitives](../../../../primitives.md)

Admit bounded external documents/records and serialize explicit public representations at the engine boundary.

Snapshot SHA-256: `b21222a3b3c260aa1ab7b344aac9ba61458c980990c8557bc0c28dfc0829050a`. 11 lines partitioned into 3 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [io](../../../../subsystem_contracts.md#io). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/ingestion.md](../../../../../ingestion.md), [docs/query_identity.md](../../../../../query_identity.md), [docs/schema_evolution.md](../../../../../schema_evolution.md), [docs/cli.md](../../../../../cli.md), [docs/query_memory.md](../../../../../query_memory.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–3](../../../../../../include/crown/io/query_explain.hpp#L1) | Imports dependencies; guards repeated header inclusion; declares namespace scope. |  · [reviewed contract](#b0001) |
| [B0002 · 4–4](../../../../../../include/crown/io/query_explain.hpp#L4) | Type/record definition: struct QueryExplainTextLimits |  · [reviewed contract](#b0002) |
| [B0003 · 5–11](../../../../../../include/crown/io/query_explain.hpp#L5) | declares values/defaults or compile-time conditions. | source comment (unverified): // Separate allocating, bounded strict UTF-8 transport; never admission/unwind. · [reviewed contract](#b0003) |

## B0001

[Lines 1–3](../../../../../../include/crown/io/query_explain.hpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
#pragma once
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Declare the io query_explain public interface and its required types. |
| inputs / outputs | Header imports its explicit dependencies and declares the APIs/contracts below. |
| invariants | Inclusion does not construct a live query, source, report, proof or file owner. |
| ownership | Declarations retain no instance; object ownership and copies are specified at the individual APIs. |
| failure | Compile-time dependency/declaration boundary; runtime failures belong to instantiated objects/operations. |
| cost | No runtime action from inclusion itself; inline methods retain their stated actual costs. |
| Design | [include/crown/io/query_explain.hpp](../../../../../../include/crown/io/query_explain.hpp), [src/io/query_explain.cpp](../../../../../../src/io/query_explain.cpp), [src/observability/query_explain.cpp](../../../../../../src/observability/query_explain.cpp), [docs/observability.md](../../../../../observability.md) |

## B0002

[Lines 4–4](../../../../../../include/crown/io/query_explain.hpp#L4); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct QueryExplainTextLimits {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Bound one query/search EXPLAIN encoding. |
| inputs / outputs | Default16 MiB encoded-byte limit for the strict manual writer. |
| invariants | No bound on retained proof graph, allocator capacity or all preparation memory. |
| ownership | Inline fixed fields only; copying these values allocates no container or text. No source/native owner is retained. |
| failure | Declaration/field initialization performs no semantic validation. Consumers validate the actual values at their own boundary. |
| cost | Fixed-size initialization/copy/comparison; declaration itself performs no runtime scan or I/O. |
| Design | [include/crown/io/query_explain.hpp](../../../../../../include/crown/io/query_explain.hpp), [src/io/query_explain.cpp](../../../../../../src/io/query_explain.cpp), [src/observability/query_explain.cpp](../../../../../../src/observability/query_explain.cpp), [docs/observability.md](../../../../../observability.md) |

## B0003

[Lines 5–11](../../../../../../include/crown/io/query_explain.hpp#L5); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
write_query_explain_json(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Export typed query evidence as json text. |
| inputs / outputs | Returns complete owning text; tree/DOT require a published ValidatedIncumbent witness rather than a numeric owner upper alone. |
| invariants | Capture/export does not advance search/replay or create proof. UTF8 and encoded-byte validation is transport-only. |
| ownership | Borrows typed report/proof handles, creates ordinary output storage; tree/key/text references remain report-owned. |
| failure | Missing genuine witness, moved-from report, encoding/byte/allocation failures propagate without a returned partial string. |
| cost | Full chosen metadata/witness/certificate traversal and byte escaping within output cap; no JSON DOM, but string capacity is a separate allocator cost. |
| Design | [include/crown/io/query_explain.hpp](../../../../../../include/crown/io/query_explain.hpp), [src/io/query_explain.cpp](../../../../../../src/io/query_explain.cpp), [src/observability/query_explain.cpp](../../../../../../src/observability/query_explain.cpp), [docs/observability.md](../../../../../observability.md) |

```text
write_query_explain_text(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Export typed query evidence as text text. |
| inputs / outputs | Returns complete owning text; tree/DOT require a published ValidatedIncumbent witness rather than a numeric owner upper alone. |
| invariants | Capture/export does not advance search/replay or create proof. UTF8 and encoded-byte validation is transport-only. |
| ownership | Borrows typed report/proof handles, creates ordinary output storage; tree/key/text references remain report-owned. |
| failure | Missing genuine witness, moved-from report, encoding/byte/allocation failures propagate without a returned partial string. |
| cost | Full chosen metadata/witness/certificate traversal and byte escaping within output cap; no JSON DOM, but string capacity is a separate allocator cost. |
| Design | [include/crown/io/query_explain.hpp](../../../../../../include/crown/io/query_explain.hpp), [src/io/query_explain.cpp](../../../../../../src/io/query_explain.cpp), [src/observability/query_explain.cpp](../../../../../../src/observability/query_explain.cpp), [docs/observability.md](../../../../../observability.md) |

```text
write_query_explain_tree_json(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Export typed query evidence as tree json text. |
| inputs / outputs | Returns complete owning text; tree/DOT require a published ValidatedIncumbent witness rather than a numeric owner upper alone. |
| invariants | Capture/export does not advance search/replay or create proof. UTF8 and encoded-byte validation is transport-only. |
| ownership | Borrows typed report/proof handles, creates ordinary output storage; tree/key/text references remain report-owned. |
| failure | Missing genuine witness, moved-from report, encoding/byte/allocation failures propagate without a returned partial string. |
| cost | Full chosen metadata/witness/certificate traversal and byte escaping within output cap; no JSON DOM, but string capacity is a separate allocator cost. |
| Design | [include/crown/io/query_explain.hpp](../../../../../../include/crown/io/query_explain.hpp), [src/io/query_explain.cpp](../../../../../../src/io/query_explain.cpp), [src/observability/query_explain.cpp](../../../../../../src/observability/query_explain.cpp), [docs/observability.md](../../../../../observability.md) |

```text
write_query_explain_dot(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Export typed query evidence as dot text. |
| inputs / outputs | Returns complete owning text; tree/DOT require a published ValidatedIncumbent witness rather than a numeric owner upper alone. |
| invariants | Capture/export does not advance search/replay or create proof. UTF8 and encoded-byte validation is transport-only. |
| ownership | Borrows typed report/proof handles, creates ordinary output storage; tree/key/text references remain report-owned. |
| failure | Missing genuine witness, moved-from report, encoding/byte/allocation failures propagate without a returned partial string. |
| cost | Full chosen metadata/witness/certificate traversal and byte escaping within output cap; no JSON DOM, but string capacity is a separate allocator cost. |
| Design | [include/crown/io/query_explain.hpp](../../../../../../include/crown/io/query_explain.hpp), [src/io/query_explain.cpp](../../../../../../src/io/query_explain.cpp), [src/observability/query_explain.cpp](../../../../../../src/observability/query_explain.cpp), [docs/observability.md](../../../../../observability.md) |
