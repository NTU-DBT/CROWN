# `include/crown/io/statistics_explain.hpp` — block usage map

[Source](../../../../../../include/crown/io/statistics_explain.hpp) · [Source index](../../../../README.md) · [Subsystem contracts](../../../../subsystem_contracts.md) · [Reviewed primitives](../../../../primitives.md)

Admit bounded external documents/records and serialize explicit public representations at the engine boundary.

Snapshot SHA-256: `1d18b097073dbb50fb47cced99d37e8d05485d50c0d60b32419d2d52454818a9`. 14 lines partitioned into 5 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [io](../../../../subsystem_contracts.md#io). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/ingestion.md](../../../../../ingestion.md), [docs/query_identity.md](../../../../../query_identity.md), [docs/schema_evolution.md](../../../../../schema_evolution.md), [docs/cli.md](../../../../../cli.md), [docs/query_memory.md](../../../../../query_memory.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–4](../../../../../../include/crown/io/statistics_explain.hpp#L1) | Imports dependencies; guards repeated header inclusion; declares namespace scope. |  · [reviewed contract](#b0001) |
| [B0002 · 5–5](../../../../../../include/crown/io/statistics_explain.hpp#L5) | Type/record definition: struct StatisticsTextLimits |  · [reviewed contract](#b0002) |
| [B0003 · 6–10](../../../../../../include/crown/io/statistics_explain.hpp#L6) | Explanatory comments or spacing. | source comment (unverified): // Items count each JSON value (object, array, scalar/null), excluding field · [reviewed contract](#b0003) |
| [B0004 · 11–11](../../../../../../include/crown/io/statistics_explain.hpp#L11) | Type/record definition: struct StatisticsText | source comment (unverified): // Items count each JSON value (object, array, scalar/null), excluding field · [reviewed contract](#b0004) |
| [B0005 · 12–14](../../../../../../include/crown/io/statistics_explain.hpp#L12) | declares values/defaults or compile-time conditions. |  · [reviewed contract](#b0005) |

## B0001

[Lines 1–4](../../../../../../include/crown/io/statistics_explain.hpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
#pragma once
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Declare the io statistics_explain public interface and its required types. |
| inputs / outputs | Header imports its explicit dependencies and declares the APIs/contracts below. |
| invariants | Inclusion does not construct a live query, source, report, proof or file owner. |
| ownership | Declarations retain no instance; object ownership and copies are specified at the individual APIs. |
| failure | Compile-time dependency/declaration boundary; runtime failures belong to instantiated objects/operations. |
| cost | No runtime action from inclusion itself; inline methods retain their stated actual costs. |
| Design | [include/crown/io/statistics_explain.hpp](../../../../../../include/crown/io/statistics_explain.hpp), [src/io/statistics_explain.cpp](../../../../../../src/io/statistics_explain.cpp), [docs/statistics.md](../../../../../statistics.md) |

## B0002

[Lines 5–5](../../../../../../include/crown/io/statistics_explain.hpp#L5); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct StatisticsTextLimits {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Bound statistics encoded bytes and JSON value count. |
| inputs / outputs | Defaults16 MiB and one million values; containers/null/scalars count, member names do not. |
| invariants | Bounds final encoded work domain, not report ownership, allocator capacity or total process memory. |
| ownership | Inline fixed fields only; copying these values allocates no container or text. No source/native owner is retained. |
| failure | Declaration/field initialization performs no semantic validation. Consumers validate the actual values at their own boundary. |
| cost | Fixed-size initialization/copy/comparison; declaration itself performs no runtime scan or I/O. |
| Design | [include/crown/io/statistics_explain.hpp](../../../../../../include/crown/io/statistics_explain.hpp), [src/io/statistics_explain.cpp](../../../../../../src/io/statistics_explain.cpp), [docs/statistics.md](../../../../../statistics.md) |

## B0003

[Lines 6–10](../../../../../../include/crown/io/statistics_explain.hpp#L6); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L6-L10:sha256:39aeb89f1dc13dc9d65d8afa4e3729136ae97b229cd339a7fc84e2adcb1096cd
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Design note for adjacent code: Items count each JSON value (object, array, scalar/null), excluding field names. Human output adds a fixed introduction to the same complete JSON. Both limits are checked before publication; failure returns no partial text. Native byte payloads use hex; internal labels are ASCII. Report storage and string capacity are separate from final encoded length. This is caller guidance recorded as prose, not an executable result. |
| inputs / outputs | No runtime interface is implemented by these comment-only lines. They sit at include/crown/io/statistics_explain.hpp lines 4-12; the surrounding declaration/body defines its own inputs and outputs. |
| invariants | The words record the intended use boundary only. They do not add a guard, proof, capability, transaction, durability guarantee, or account charge; verify behavior in the referenced implementation. |
| ownership | Comment text owns no data. Object lifetimes, borrows, and account attribution remain those of the adjacent source objects and their constructors. |
| failure | No failure path is implemented here. Any mentioned failure or recovery rule belongs to the adjacent operation and its existing error carrier. |
| cost | No runtime work is performed by these lines; any cost/bound in the note is not certified by this comment-only card. |
| Design | [include/crown/io/statistics_explain.hpp](../../../../../../include/crown/io/statistics_explain.hpp), [docs/code_specs/files/include/crown/io/statistics_explain.hpp.md](statistics_explain.hpp.md), [docs/observability.md](../../../../../observability.md), [docs/statistics.md](../../../../../statistics.md) |

## B0004

[Lines 11–11](../../../../../../include/crown/io/statistics_explain.hpp#L11); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct StatisticsText {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Own one complete rendered statistics artifact and value count. |
| inputs / outputs | Ordinary string plus counted JSON items; text form prepends a fixed human introduction. |
| invariants | Native arbitrary bytes are hex-encoded and internal control labels are ASCII. No admission/proof authority from rendered flags. |
| ownership | Ordinary caller-owned value; Rows/strings/vectors/maps own their storage and can allocate when constructed or copied. No native account authority is created. |
| failure | Declaration/field initialization performs no semantic validation. Consumers validate the actual values at their own boundary. |
| cost | Explicit ordinary container/text ownership and deep-copy costs; field declarations add no execution or validation pass. |
| Design | [include/crown/io/statistics_explain.hpp](../../../../../../include/crown/io/statistics_explain.hpp), [src/io/statistics_explain.cpp](../../../../../../src/io/statistics_explain.cpp), [docs/statistics.md](../../../../../statistics.md) |

## B0005

[Lines 12–14](../../../../../../include/crown/io/statistics_explain.hpp#L12); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
write_statistics_json(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Render complete statistics json with explicit byte/item caps. |
| inputs / outputs | Returns StatisticsText with final owning string and value count; text adds a fixed introduction before the same JSON payload. |
| invariants | Every JSON value is charged; field names are excluded. Native byte payloads use hex, preserving arbitrary bytes without requiring them to be UTF8. |
| ownership | Borrows immutable report, owns ordinary encoded text; no query/account shadow or live owner pointer is stored. |
| failure | Byte/item limits, invalid internal ASCII or allocation failure returns no complete artifact; reports/native state are unchanged. |
| cost | Full captured descriptor/component/key/trace traversal and encoding; hex doubles source byte characters, and capacity/report memory stay outside length caps. |
| Design | [include/crown/io/statistics_explain.hpp](../../../../../../include/crown/io/statistics_explain.hpp), [src/io/statistics_explain.cpp](../../../../../../src/io/statistics_explain.cpp), [docs/statistics.md](../../../../../statistics.md) |

```text
write_statistics_text(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Render complete statistics text with explicit byte/item caps. |
| inputs / outputs | Returns StatisticsText with final owning string and value count; text adds a fixed introduction before the same JSON payload. |
| invariants | Every JSON value is charged; field names are excluded. Native byte payloads use hex, preserving arbitrary bytes without requiring them to be UTF8. |
| ownership | Borrows immutable report, owns ordinary encoded text; no query/account shadow or live owner pointer is stored. |
| failure | Byte/item limits, invalid internal ASCII or allocation failure returns no complete artifact; reports/native state are unchanged. |
| cost | Full captured descriptor/component/key/trace traversal and encoding; hex doubles source byte characters, and capacity/report memory stay outside length caps. |
| Design | [include/crown/io/statistics_explain.hpp](../../../../../../include/crown/io/statistics_explain.hpp), [src/io/statistics_explain.cpp](../../../../../../src/io/statistics_explain.cpp), [docs/statistics.md](../../../../../statistics.md) |
