# `include/crown/io/normalization.hpp` — block usage map

[Source](../../../../../../include/crown/io/normalization.hpp) · [Source index](../../../../README.md) · [Subsystem contracts](../../../../subsystem_contracts.md) · [Reviewed primitives](../../../../primitives.md)

Admit bounded external documents/records and serialize explicit public representations at the engine boundary.

Snapshot SHA-256: `177a23f69c516a0a9a1dc532bfa8782f2588b8975090b148b542b1fa8660ca9a`. 18 lines partitioned into 3 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [io](../../../../subsystem_contracts.md#io). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/ingestion.md](../../../../../ingestion.md), [docs/query_identity.md](../../../../../query_identity.md), [docs/schema_evolution.md](../../../../../schema_evolution.md), [docs/cli.md](../../../../../cli.md), [docs/query_memory.md](../../../../../query_memory.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–7](../../../../../../include/crown/io/normalization.hpp#L1) | Imports dependencies; guards repeated header inclusion; declares namespace scope; declares callable signatures; declares values/defaults or compile-time conditions. |  · [reviewed contract](#b0001) |
| [B0002 · 8–11](../../../../../../include/crown/io/normalization.hpp#L8) | Type/record definition: struct ProgramReadLimits |  · [reviewed contract](#b0002) |
| [B0003 · 12–18](../../../../../../include/crown/io/normalization.hpp#L12) | declares callable signatures; declares values/defaults or compile-time conditions. | source comment (unverified): // Reconstruct owned executable state by replay; diagnostic envelopes are not · [reviewed contract](#b0003) |

## B0001

[Lines 1–7](../../../../../../include/crown/io/normalization.hpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
#pragma once
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Declare the io normalization public interface and its required types. |
| inputs / outputs | Header imports its explicit dependencies and declares the APIs/contracts below. |
| invariants | Inclusion does not construct a live query, source, report, proof or file owner. |
| ownership | Declarations retain no instance; object ownership and copies are specified at the individual APIs. |
| failure | Compile-time dependency/declaration boundary; runtime failures belong to instantiated objects/operations. |
| cost | No runtime action from inclusion itself; inline methods retain their stated actual costs. |
| Design | [include/crown/io/normalization.hpp](../../../../../../include/crown/io/normalization.hpp), [src/io/normalization.cpp](../../../../../../src/io/normalization.cpp), [docs/sql_normalization.md](../../../../../sql_normalization.md) |

```text
Json write_sql_normalization(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Serialize normalized-program success or binding-diagnostic data. |
| inputs / outputs | Produces a complete ordinary DOM, including owned source/binding/core/parameters/adapters/outputs/work. |
| invariants | A serialized success flag is descriptive; reader authority comes from complete replay, not this writer. |
| ownership | Ordinary caller-owned value; Rows/strings/vectors/maps own their storage and can allocate when constructed or copied. No native account authority is created. |
| failure | Version/schema/scalar/binding/normalization/resource/allocation errors propagate; no partial result is returned. |
| cost | Full ordinary Document/core/JSON/vector/scalar copies; no final output byte/item cap in this API. |
| Design | [include/crown/io/normalization.hpp](../../../../../../include/crown/io/normalization.hpp), [src/io/normalization.cpp](../../../../../../src/io/normalization.cpp), [docs/sql_normalization.md](../../../../../sql_normalization.md) |

## B0002

[Lines 8–11](../../../../../../include/crown/io/normalization.hpp#L8); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct ProgramReadLimits {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Supply independent host binding/normalization replay limits. |
| inputs / outputs | BindLimits and NormalizeLimits cap reconstruction while stored producer policies remain represented exactly. |
| invariants | These are work-domain limits, not a total input/DOM byte limit or editable execution-authority flags. |
| ownership | Inline fixed fields only; copying these values allocates no container or text. No source/native owner is retained. |
| failure | Declaration/field initialization performs no semantic validation. Consumers validate the actual values at their own boundary. |
| cost | Fixed-size initialization/copy/comparison; declaration itself performs no runtime scan or I/O. |
| Design | [include/crown/io/normalization.hpp](../../../../../../include/crown/io/normalization.hpp), [src/io/normalization.cpp](../../../../../../src/io/normalization.cpp), [docs/sql_normalization.md](../../../../../sql_normalization.md) |

```text
frontend::BindLimits binding;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | The independent host SQL binding reconstruction cap. |
| inputs / outputs | Stores/exposes the independent host SQL binding reconstruction cap. |
| invariants | These are work-domain limits, not a total input/DOM byte limit or editable execution-authority flags. |
| ownership | Inline fixed fields only; copying these values allocates no container or text. No source/native owner is retained. |
| failure | Assignment adds no validation; aggregate construction/copy has the ownership costs stated here. |
| cost | Fixed-size initialization/copy/comparison; declaration itself performs no runtime scan or I/O. |
| Design | [include/crown/io/normalization.hpp](../../../../../../include/crown/io/normalization.hpp), [src/io/normalization.cpp](../../../../../../src/io/normalization.cpp), [docs/sql_normalization.md](../../../../../sql_normalization.md) |

```text
frontend::NormalizeLimits normalization;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | The host normalized-program reconstruction cap. |
| inputs / outputs | Stores/exposes the host normalized-program reconstruction cap. |
| invariants | These are work-domain limits, not a total input/DOM byte limit or editable execution-authority flags. |
| ownership | Inline fixed fields only; copying these values allocates no container or text. No source/native owner is retained. |
| failure | Assignment adds no validation; aggregate construction/copy has the ownership costs stated here. |
| cost | Fixed-size initialization/copy/comparison; declaration itself performs no runtime scan or I/O. |
| Design | [include/crown/io/normalization.hpp](../../../../../../include/crown/io/normalization.hpp), [src/io/normalization.cpp](../../../../../../src/io/normalization.cpp), [docs/sql_normalization.md](../../../../../sql_normalization.md) |

## B0003

[Lines 12–18](../../../../../../include/crown/io/normalization.hpp#L12); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
frontend::NormalizedSql read_sql_normalization(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Reconstruct normalized owned state through complete binding/normalization replay. |
| inputs / outputs | Parses strict version1/2 envelope, replays binding and parameters under host caps, normalizes, restores stored policy and compares complete serialized result. |
| invariants | Rejects diagnostic/edited/inconsistent envelopes; host caps limit replay without silently replacing stored producer policy. |
| ownership | Ordinary caller-owned value; Rows/strings/vectors/maps own their storage and can allocate when constructed or copied. No native account authority is created. |
| failure | Version/schema/scalar/binding/normalization/resource/allocation errors propagate; no partial result is returned. |
| cost | Full DOM parse, nested dump/reparse, binding/normalization work, ordinary source/parameter copies and full dump comparison. |
| Design | [include/crown/io/normalization.hpp](../../../../../../include/crown/io/normalization.hpp), [src/io/normalization.cpp](../../../../../../src/io/normalization.cpp), [docs/sql_normalization.md](../../../../../sql_normalization.md) |

```text
frontend::NormalizedSql upgrade_sql_normalization(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Validate/replay then upgrade normalized format upward. |
| inputs / outputs | Supports versions1 through2; first reconstructs original, then normalizes at target version under independent host caps. |
| invariants | Rejects downward/unknown versions; no source/runtime mutation or proof of original minimum. |
| ownership | Ordinary caller-owned value; Rows/strings/vectors/maps own their storage and can allocate when constructed or copied. No native account authority is created. |
| failure | Version/schema/scalar/binding/normalization/resource/allocation errors propagate; no partial result is returned. |
| cost | Complete serialize/read replay even for same-version validation; changed version adds another normalization pass and owned compiler DTO storage. |
| Design | [include/crown/io/normalization.hpp](../../../../../../include/crown/io/normalization.hpp), [src/io/normalization.cpp](../../../../../../src/io/normalization.cpp), [docs/sql_normalization.md](../../../../../sql_normalization.md) |

```text
std::vector<frontend::SqlValue> read_parameter_values(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Decode the strict version1 typed parameter envelope. |
| inputs / outputs | Parses values as typed ordinary scalars or SQL NULL into an owning vector. |
| invariants | Parameter values alone are not bound/admitted executable state; this API has no separate count/byte grant. |
| ownership | Ordinary caller-owned value; Rows/strings/vectors/maps own their storage and can allocate when constructed or copied. No native account authority is created. |
| failure | Version/schema/scalar/binding/normalization/resource/allocation errors propagate; no partial result is returned. |
| cost | Full ordinary DOM parse and scalar/string/Decimal/vector allocation; NULL occupies an empty optional. |
| Design | [include/crown/io/normalization.hpp](../../../../../../include/crown/io/normalization.hpp), [src/io/normalization.cpp](../../../../../../src/io/normalization.cpp), [docs/sql_normalization.md](../../../../../sql_normalization.md) |
