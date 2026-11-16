# `include/crown/io/identity.hpp` — block usage map

[Source](../../../../../../include/crown/io/identity.hpp) · [Source index](../../../../README.md) · [Subsystem contracts](../../../../subsystem_contracts.md) · [Reviewed primitives](../../../../primitives.md)

Admit bounded external documents/records and serialize explicit public representations at the engine boundary.

Snapshot SHA-256: `4872c6ffab7e32ca8377075d4f1607b7f0c7aeaa4b803efbf9765c05128e290a`. 35 lines partitioned into 6 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [io](../../../../subsystem_contracts.md#io). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/ingestion.md](../../../../../ingestion.md), [docs/query_identity.md](../../../../../query_identity.md), [docs/schema_evolution.md](../../../../../schema_evolution.md), [docs/cli.md](../../../../../cli.md), [docs/query_memory.md](../../../../../query_memory.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–6](../../../../../../include/crown/io/identity.hpp#L1) | Imports dependencies; guards repeated header inclusion; declares namespace scope. |  · [reviewed contract](#b0001) |
| [B0002 · 7–7](../../../../../../include/crown/io/identity.hpp#L7) | Type/record definition: struct IdentityLimits |  · [reviewed contract](#b0002) |
| [B0003 · 8–13](../../../../../../include/crown/io/identity.hpp#L8) | Type/record definition: struct CachePolicy |  · [reviewed contract](#b0003) |
| [B0004 · 14–15](../../../../../../include/crown/io/identity.hpp#L14) | Explanatory comments or spacing. | source comment (unverified): // Ordinary editable identity DTO. Digests/flags are not executable, proof or · [reviewed contract](#b0004) |
| [B0005 · 16–26](../../../../../../include/crown/io/identity.hpp#L16) | Type/record definition: struct QueryIdentity | source comment (unverified): // Ordinary editable identity DTO. Digests/flags are not executable, proof or · [reviewed contract](#b0005) |
| [B0006 · 27–35](../../../../../../include/crown/io/identity.hpp#L27) | declares callable signatures; declares values/defaults or compile-time conditions. | source comment (unverified): // Complete colored-occurrence labeling within an operational work budget. · [reviewed contract](#b0006) |

## B0001

[Lines 1–6](../../../../../../include/crown/io/identity.hpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
#pragma once
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Declare the io identity public interface and its required types. |
| inputs / outputs | Header imports its explicit dependencies and declares the APIs/contracts below. |
| invariants | Inclusion does not construct a live query, source, report, proof or file owner. |
| ownership | Declarations retain no instance; object ownership and copies are specified at the individual APIs. |
| failure | Compile-time dependency/declaration boundary; runtime failures belong to instantiated objects/operations. |
| cost | No runtime action from inclusion itself; inline methods retain their stated actual costs. |
| Design | [include/crown/io/identity.hpp](../../../../../../include/crown/io/identity.hpp), [src/io/identity.cpp](../../../../../../src/io/identity.cpp), [docs/query_identity.md](../../../../../query_identity.md) |

## B0002

[Lines 7–7](../../../../../../include/crown/io/identity.hpp#L7); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct IdentityLimits {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Bound complete identity canonicalization work. |
| inputs / outputs | Optional work limit; default one million selected units, nullopt permits unbounded modeled search. |
| invariants | Exhaustion returns no fallback/partial identity. This work model does not cap all ordinary JSON/string allocator memory. |
| ownership | Inline fixed fields only; copying these values allocates no container or text. No source/native owner is retained. |
| failure | Declaration/field initialization performs no semantic validation. Consumers validate the actual values at their own boundary. |
| cost | Fixed-size initialization/copy/comparison; declaration itself performs no runtime scan or I/O. |
| Design | [include/crown/io/identity.hpp](../../../../../../include/crown/io/identity.hpp), [src/io/identity.cpp](../../../../../../src/io/identity.cpp), [docs/query_identity.md](../../../../../query_identity.md) |

```text
std::optional<std::uint64_t> work_limit = 1000000;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | The optional operational colored-labeling work cap. |
| inputs / outputs | Stores/exposes the optional operational colored-labeling work cap. |
| invariants | Exhaustion returns no fallback/partial identity. This work model does not cap all ordinary JSON/string allocator memory. |
| ownership | Inline fixed fields only; copying these values allocates no container or text. No source/native owner is retained. |
| failure | Assignment adds no validation; aggregate construction/copy has the ownership costs stated here. |
| cost | Fixed-size initialization/copy/comparison; declaration itself performs no runtime scan or I/O. |
| Design | [include/crown/io/identity.hpp](../../../../../../include/crown/io/identity.hpp), [src/io/identity.cpp](../../../../../../src/io/identity.cpp), [docs/query_identity.md](../../../../../query_identity.md) |

## B0003

[Lines 8–13](../../../../../../include/crown/io/identity.hpp#L8); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct CachePolicy {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Own the four independent canonical cache-policy strings. |
| inputs / outputs | Arithmetic, planner, optimization and cost-model tags participate in different identity domains. |
| invariants | Public value/configuration only; changing fields does not perform admission, execute an input or create proof authority. |
| ownership | Ordinary caller-owned value; Rows/strings/vectors/maps own their storage and can allocate when constructed or copied. No native account authority is created. |
| failure | Declaration/field initialization performs no semantic validation. Consumers validate the actual values at their own boundary. |
| cost | Explicit ordinary container/text ownership and deep-copy costs; field declarations add no execution or validation pass. |
| Design | [include/crown/io/identity.hpp](../../../../../../include/crown/io/identity.hpp), [src/io/identity.cpp](../../../../../../src/io/identity.cpp), [docs/query_identity.md](../../../../../query_identity.md) |

```text
std::string arithmetic =
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | The arithmetic semantic-policy identifier. |
| inputs / outputs | Stores/exposes the arithmetic semantic-policy identifier. |
| invariants | This field is descriptive/configuration data, not an independent admission or publication capability. |
| ownership | Ordinary caller-owned value; Rows/strings/vectors/maps own their storage and can allocate when constructed or copied. No native account authority is created. |
| failure | Assignment adds no validation; aggregate construction/copy has the ownership costs stated here. |
| cost | Explicit ordinary container/text ownership and deep-copy costs; field declarations add no execution or validation pass. |
| Design | [include/crown/io/identity.hpp](../../../../../../include/crown/io/identity.hpp), [src/io/identity.cpp](../../../../../../src/io/identity.cpp), [docs/query_identity.md](../../../../../query_identity.md) |

```text
std::string planner =
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | The planner family identifier. |
| inputs / outputs | Stores/exposes the planner family identifier. |
| invariants | This field is descriptive/configuration data, not an independent admission or publication capability. |
| ownership | Ordinary caller-owned value; Rows/strings/vectors/maps own their storage and can allocate when constructed or copied. No native account authority is created. |
| failure | Assignment adds no validation; aggregate construction/copy has the ownership costs stated here. |
| cost | Explicit ordinary container/text ownership and deep-copy costs; field declarations add no execution or validation pass. |
| Design | [include/crown/io/identity.hpp](../../../../../../include/crown/io/identity.hpp), [src/io/identity.cpp](../../../../../../src/io/identity.cpp), [docs/query_identity.md](../../../../../query_identity.md) |

```text
std::string optimization =
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | The structural optimization-policy identifier. |
| inputs / outputs | Stores/exposes the structural optimization-policy identifier. |
| invariants | This field is descriptive/configuration data, not an independent admission or publication capability. |
| ownership | Ordinary caller-owned value; Rows/strings/vectors/maps own their storage and can allocate when constructed or copied. No native account authority is created. |
| failure | Assignment adds no validation; aggregate construction/copy has the ownership costs stated here. |
| cost | Explicit ordinary container/text ownership and deep-copy costs; field declarations add no execution or validation pass. |
| Design | [include/crown/io/identity.hpp](../../../../../../include/crown/io/identity.hpp), [src/io/identity.cpp](../../../../../../src/io/identity.cpp), [docs/query_identity.md](../../../../../query_identity.md) |

```text
std::string cost_model =
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | The cost model/version identifier. |
| inputs / outputs | Stores/exposes the cost model/version identifier. |
| invariants | This field is descriptive/configuration data, not an independent admission or publication capability. |
| ownership | Ordinary caller-owned value; Rows/strings/vectors/maps own their storage and can allocate when constructed or copied. No native account authority is created. |
| failure | Assignment adds no validation; aggregate construction/copy has the ownership costs stated here. |
| cost | Explicit ordinary container/text ownership and deep-copy costs; field declarations add no execution or validation pass. |
| Design | [include/crown/io/identity.hpp](../../../../../../include/crown/io/identity.hpp), [src/io/identity.cpp](../../../../../../src/io/identity.cpp), [docs/query_identity.md](../../../../../query_identity.md) |

## B0004

[Lines 14–15](../../../../../../include/crown/io/identity.hpp#L14); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L14-L15:sha256:b332d93299c5246201e9f41d6a0b36f47f3acdaef8b8c6e97b05a8e65e03a2f9
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Design note for adjacent code: Ordinary editable identity DTO. Digests/flags are not executable, proof or native source-admission authority. This is caller guidance recorded as prose, not an executable result. |
| inputs / outputs | No runtime interface is implemented by these comment-only lines. They sit at include/crown/io/identity.hpp lines 12-17; the surrounding declaration/body defines its own inputs and outputs. |
| invariants | The words record the intended use boundary only. They do not add a guard, proof, capability, transaction, durability guarantee, or account charge; verify behavior in the referenced implementation. |
| ownership | Comment text owns no data. Object lifetimes, borrows, and account attribution remain those of the adjacent source objects and their constructors. |
| failure | No failure path is implemented here. Any mentioned failure or recovery rule belongs to the adjacent operation and its existing error carrier. |
| cost | No runtime work is performed by these lines; any cost/bound in the note is not certified by this comment-only card. |
| Design | [include/crown/io/identity.hpp](../../../../../../include/crown/io/identity.hpp), [docs/code_specs/files/include/crown/io/identity.hpp.md](identity.hpp.md), [docs/query_identity.md](../../../../../query_identity.md), [docs/query_memory.md](../../../../../query_memory.md) |

## B0005

[Lines 16–26](../../../../../../include/crown/io/identity.hpp#L16); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct QueryIdentity {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Own a complete ordinary canonical identity DTO. |
| inputs / outputs | Canonical JSON, four SHA256 domain strings, canonical-to-original occurrence/variable orders and charged work. |
| invariants | Editable descriptive DTO. Canonical labels erase allowed renamings/order only; consumers must translate IDs and independently establish executable/proof/source authority. |
| ownership | Ordinary caller-owned value; Rows/strings/vectors/maps own their storage and can allocate when constructed or copied. No native account authority is created. |
| failure | Declaration/field initialization performs no semantic validation. Consumers validate the actual values at their own boundary. |
| cost | Explicit ordinary container/text ownership and deep-copy costs; field declarations add no execution or validation pass. |
| Design | [include/crown/io/identity.hpp](../../../../../../include/crown/io/identity.hpp), [src/io/identity.cpp](../../../../../../src/io/identity.cpp), [docs/query_identity.md](../../../../../query_identity.md) |

```text
Json canonical;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | The owning canonical JSON envelope. |
| inputs / outputs | Stores/exposes the owning canonical JSON envelope. |
| invariants | Editable descriptive DTO. Canonical labels erase allowed renamings/order only; consumers must translate IDs and independently establish executable/proof/source authority. |
| ownership | Ordinary caller-owned value; Rows/strings/vectors/maps own their storage and can allocate when constructed or copied. No native account authority is created. |
| failure | Assignment adds no validation; aggregate construction/copy has the ownership costs stated here. |
| cost | Explicit ordinary container/text ownership and deep-copy costs; field declarations add no execution or validation pass. |
| Design | [include/crown/io/identity.hpp](../../../../../../include/crown/io/identity.hpp), [src/io/identity.cpp](../../../../../../src/io/identity.cpp), [docs/query_identity.md](../../../../../query_identity.md) |

```text
std::string semantic_sha256;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | The semantic-domain digest string. |
| inputs / outputs | Stores/exposes the semantic-domain digest string. |
| invariants | Editable descriptive DTO. Canonical labels erase allowed renamings/order only; consumers must translate IDs and independently establish executable/proof/source authority. |
| ownership | Ordinary caller-owned value; Rows/strings/vectors/maps own their storage and can allocate when constructed or copied. No native account authority is created. |
| failure | Assignment adds no validation; aggregate construction/copy has the ownership costs stated here. |
| cost | Explicit ordinary container/text ownership and deep-copy costs; field declarations add no execution or validation pass. |
| Design | [include/crown/io/identity.hpp](../../../../../../include/crown/io/identity.hpp), [src/io/identity.cpp](../../../../../../src/io/identity.cpp), [docs/query_identity.md](../../../../../query_identity.md) |

```text
std::string output_contract_sha256;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | The ordered output names/types contract digest. |
| inputs / outputs | Stores/exposes the ordered output names/types contract digest. |
| invariants | Editable descriptive DTO. Canonical labels erase allowed renamings/order only; consumers must translate IDs and independently establish executable/proof/source authority. |
| ownership | Ordinary caller-owned value; Rows/strings/vectors/maps own their storage and can allocate when constructed or copied. No native account authority is created. |
| failure | Assignment adds no validation; aggregate construction/copy has the ownership costs stated here. |
| cost | Explicit ordinary container/text ownership and deep-copy costs; field declarations add no execution or validation pass. |
| Design | [include/crown/io/identity.hpp](../../../../../../include/crown/io/identity.hpp), [src/io/identity.cpp](../../../../../../src/io/identity.cpp), [docs/query_identity.md](../../../../../query_identity.md) |

```text
std::string cost_inputs_sha256;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | The cost-input domain digest. |
| inputs / outputs | Stores/exposes the cost-input domain digest. |
| invariants | Editable descriptive DTO. Canonical labels erase allowed renamings/order only; consumers must translate IDs and independently establish executable/proof/source authority. |
| ownership | Ordinary caller-owned value; Rows/strings/vectors/maps own their storage and can allocate when constructed or copied. No native account authority is created. |
| failure | Assignment adds no validation; aggregate construction/copy has the ownership costs stated here. |
| cost | Explicit ordinary container/text ownership and deep-copy costs; field declarations add no execution or validation pass. |
| Design | [include/crown/io/identity.hpp](../../../../../../include/crown/io/identity.hpp), [src/io/identity.cpp](../../../../../../src/io/identity.cpp), [docs/query_identity.md](../../../../../query_identity.md) |

```text
std::string plan_cache_sha256;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | The full plan-cache policy/binding digest. |
| inputs / outputs | Stores/exposes the full plan-cache policy/binding digest. |
| invariants | Editable descriptive DTO. Canonical labels erase allowed renamings/order only; consumers must translate IDs and independently establish executable/proof/source authority. |
| ownership | Ordinary caller-owned value; Rows/strings/vectors/maps own their storage and can allocate when constructed or copied. No native account authority is created. |
| failure | Assignment adds no validation; aggregate construction/copy has the ownership costs stated here. |
| cost | Explicit ordinary container/text ownership and deep-copy costs; field declarations add no execution or validation pass. |
| Design | [include/crown/io/identity.hpp](../../../../../../include/crown/io/identity.hpp), [src/io/identity.cpp](../../../../../../src/io/identity.cpp), [docs/query_identity.md](../../../../../query_identity.md) |

```text
std::vector<std::size_t> occurrence_order;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | The canonical occurrence position to original occurrence ID permutation. |
| inputs / outputs | Stores/exposes the canonical occurrence position to original occurrence ID permutation. |
| invariants | Editable descriptive DTO. Canonical labels erase allowed renamings/order only; consumers must translate IDs and independently establish executable/proof/source authority. |
| ownership | Ordinary caller-owned value; Rows/strings/vectors/maps own their storage and can allocate when constructed or copied. No native account authority is created. |
| failure | Assignment adds no validation; aggregate construction/copy has the ownership costs stated here. |
| cost | Explicit ordinary container/text ownership and deep-copy costs; field declarations add no execution or validation pass. |
| Design | [include/crown/io/identity.hpp](../../../../../../include/crown/io/identity.hpp), [src/io/identity.cpp](../../../../../../src/io/identity.cpp), [docs/query_identity.md](../../../../../query_identity.md) |

```text
std::vector<std::size_t> variable_order;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | The canonical variable position to original variable ID permutation. |
| inputs / outputs | Stores/exposes the canonical variable position to original variable ID permutation. |
| invariants | Editable descriptive DTO. Canonical labels erase allowed renamings/order only; consumers must translate IDs and independently establish executable/proof/source authority. |
| ownership | Ordinary caller-owned value; Rows/strings/vectors/maps own their storage and can allocate when constructed or copied. No native account authority is created. |
| failure | Assignment adds no validation; aggregate construction/copy has the ownership costs stated here. |
| cost | Explicit ordinary container/text ownership and deep-copy costs; field declarations add no execution or validation pass. |
| Design | [include/crown/io/identity.hpp](../../../../../../include/crown/io/identity.hpp), [src/io/identity.cpp](../../../../../../src/io/identity.cpp), [docs/query_identity.md](../../../../../query_identity.md) |

```text
std::uint64_t work;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | The selected canonicalization work spent. |
| inputs / outputs | Stores/exposes the selected canonicalization work spent. |
| invariants | Editable descriptive DTO. Canonical labels erase allowed renamings/order only; consumers must translate IDs and independently establish executable/proof/source authority. |
| ownership | Ordinary caller-owned value; Rows/strings/vectors/maps own their storage and can allocate when constructed or copied. No native account authority is created. |
| failure | Assignment adds no validation; aggregate construction/copy has the ownership costs stated here. |
| cost | Explicit ordinary container/text ownership and deep-copy costs; field declarations add no execution or validation pass. |
| Design | [include/crown/io/identity.hpp](../../../../../../include/crown/io/identity.hpp), [src/io/identity.cpp](../../../../../../src/io/identity.cpp), [docs/query_identity.md](../../../../../query_identity.md) |

## B0006

[Lines 27–35](../../../../../../include/crown/io/identity.hpp#L27); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
QueryIdentity query_identity(const Catalog& catalog,
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Compute complete canonical identity in its explicit work domain. |
| inputs / outputs | Validate direct CQ then canonicalize colored occurrences, variables, outputs, schemas and policy. |
| invariants | Preserves full atom/type/constant/source and ordered output semantics; alpha-renaming and conjunction/variable order are normalized. |
| ownership | Ordinary caller-owned value; Rows/strings/vectors/maps own their storage and can allocate when constructed or copied. No native account authority is created. |
| failure | Invalid CQ/program/scalar or work/allocation failure propagates; no partial/fallback digest. |
| cost | Potentially combinatorial full colored labeling within selected work, ordinary JSON/vector/string copying/sorting and digest encoding; not a constant hash call. |
| Design | [include/crown/io/identity.hpp](../../../../../../include/crown/io/identity.hpp), [src/io/identity.cpp](../../../../../../src/io/identity.cpp), [docs/query_identity.md](../../../../../query_identity.md) |

```text
QueryIdentity query_identity(const frontend::NormalizedSql& query,
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Compute complete canonical identity in its explicit work domain. |
| inputs / outputs | Canonicalize a producer/reader-validated normalized program, including adapters, parameters and output/wrapper semantics. |
| invariants | Requires the caller to supply genuine owned normalized state; the returned DTO does not certify that precondition or admit execution. |
| ownership | Ordinary caller-owned value; Rows/strings/vectors/maps own their storage and can allocate when constructed or copied. No native account authority is created. |
| failure | Invalid CQ/program/scalar or work/allocation failure propagates; no partial/fallback digest. |
| cost | Potentially combinatorial full colored labeling within selected work, ordinary JSON/vector/string copying/sorting and digest encoding; not a constant hash call. |
| Design | [include/crown/io/identity.hpp](../../../../../../include/crown/io/identity.hpp), [src/io/identity.cpp](../../../../../../src/io/identity.cpp), [docs/query_identity.md](../../../../../query_identity.md) |

```text
Json write_identity(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Serialize the caller identity DTO for diagnostics. |
| inputs / outputs | Copies its digests/JSON/permutations/work into an ordinary schema1 DOM with identity_valid/status labels. |
| invariants | Mutable data alone never authorizes source acceptance, native plan execution, proof, output acknowledgment or durable publication. |
| ownership | Ordinary caller-owned value; Rows/strings/vectors/maps own their storage and can allocate when constructed or copied. No native account authority is created. |
| failure | Ordinary DOM/string allocation or encoding errors propagate; writer does not independently recompute/verify the identity. |
| cost | Full nested canonical JSON and permutation copies; no final byte/item cap in this API. |
| Design | [include/crown/io/identity.hpp](../../../../../../include/crown/io/identity.hpp), [src/io/identity.cpp](../../../../../../src/io/identity.cpp), [docs/query_identity.md](../../../../../query_identity.md) |
