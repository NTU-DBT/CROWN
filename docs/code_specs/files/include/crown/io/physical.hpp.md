# `include/crown/io/physical.hpp` — block usage map

[Source](../../../../../../include/crown/io/physical.hpp) · [Source index](../../../../README.md) · [Subsystem contracts](../../../../subsystem_contracts.md) · [Reviewed primitives](../../../../primitives.md)

Admit bounded external documents/records and serialize explicit public representations at the engine boundary.

Snapshot SHA-256: `69b8da51b816966c391c275fb13de7a760c0291165661509d11acd3e94178630`. 22 lines partitioned into 3 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [io](../../../../subsystem_contracts.md#io). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/ingestion.md](../../../../../ingestion.md), [docs/query_identity.md](../../../../../query_identity.md), [docs/schema_evolution.md](../../../../../schema_evolution.md), [docs/cli.md](../../../../../cli.md), [docs/query_memory.md](../../../../../query_memory.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–13](../../../../../../include/crown/io/physical.hpp#L1) | Imports dependencies; guards repeated header inclusion; declares namespace scope; declares callable signatures; declares values/defaults or compile-time conditions. | source comment (unverified): // Canonical owned compile input, excluding initial rows and update streams. · [reviewed contract](#b0001) |
| [B0002 · 14–17](../../../../../../include/crown/io/physical.hpp#L14) | Type/record definition: struct PhysicalReadLimits |  · [reviewed contract](#b0002) |
| [B0003 · 18–22](../../../../../../include/crown/io/physical.hpp#L18) | declares values/defaults or compile-time conditions. | source comment (unverified): // Rebuilds every program from owned source/query/tree and compares the complete · [reviewed contract](#b0003) |

## B0001

[Lines 1–13](../../../../../../include/crown/io/physical.hpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
#pragma once
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Declare the io physical public interface and its required types. |
| inputs / outputs | Header imports its explicit dependencies and declares the APIs/contracts below. |
| invariants | Inclusion does not construct a live query, source, report, proof or file owner. |
| ownership | Declarations retain no instance; object ownership and copies are specified at the individual APIs. |
| failure | Compile-time dependency/declaration boundary; runtime failures belong to instantiated objects/operations. |
| cost | No runtime action from inclusion itself; inline methods retain their stated actual costs. |
| Design | [include/crown/io/physical.hpp](../../../../../../include/crown/io/physical.hpp), [src/io/physical.cpp](../../../../../../src/io/physical.cpp), [docs/physical_plans.md](../../../../../physical_plans.md) |

```text
Json write_physical_options(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Serialize physical planner/storage configuration. |
| inputs / outputs | Returns ordinary options DOM. |
| invariants | Mutable data alone never authorizes source acceptance, native plan execution, proof, output acknowledgment or durable publication. |
| ownership | Ordinary caller-owned value; Rows/strings/vectors/maps own their storage and can allocate when constructed or copied. No native account authority is created. |
| failure | Schema/version/binding/tree/lowering/resource/encoding/allocation errors propagate before a completed result; producers/native state are not mutated. |
| cost | Fixed options fields plus owning JSON/policy text storage. |
| Design | [include/crown/io/physical.hpp](../../../../../../include/crown/io/physical.hpp), [src/io/physical.cpp](../../../../../../src/io/physical.cpp), [docs/physical_plans.md](../../../../../physical_plans.md) |

```text
PhysicalOptions read_physical_options(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Decode strict physical configuration. |
| inputs / outputs | Parses option/policy/storage contract fields. |
| invariants | Mutable data alone never authorizes source acceptance, native plan execution, proof, output acknowledgment or durable publication. |
| ownership | Ordinary caller-owned value; Rows/strings/vectors/maps own their storage and can allocate when constructed or copied. No native account authority is created. |
| failure | Schema/version/binding/tree/lowering/resource/encoding/allocation errors propagate before a completed result; producers/native state are not mutated. |
| cost | Ordinary DOM parse and option/policy text construction; no total byte cap. |
| Design | [include/crown/io/physical.hpp](../../../../../../include/crown/io/physical.hpp), [src/io/physical.cpp](../../../../../../src/io/physical.cpp), [docs/physical_plans.md](../../../../../physical_plans.md) |

```text
Json write_physical_source(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Export canonical owned compile input. |
| inputs / outputs | Serializes source catalog/query or normalized program while excluding initial rows/update streams. |
| invariants | Source description remains distinct from lowered plan, native source acceptance and original minimum proof. |
| ownership | Ordinary caller-owned value; Rows/strings/vectors/maps own their storage and can allocate when constructed or copied. No native account authority is created. |
| failure | Schema/version/binding/tree/lowering/resource/encoding/allocation errors propagate before a completed result; producers/native state are not mutated. |
| cost | Full ordinary source/normalization JSON copies and nested serialization. |
| Design | [include/crown/io/physical.hpp](../../../../../../include/crown/io/physical.hpp), [src/io/physical.cpp](../../../../../../src/io/physical.cpp), [docs/physical_plans.md](../../../../../physical_plans.md) |

```text
Json write_physical(const PhysicalPlan& plan);
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Serialize the actual admitted physical compiler DTO. |
| inputs / outputs | Writes complete source/tree/options/verification/layout/relation/index/input/enumeration/guarantee/work fields. |
| invariants | Writer presents existing typed state; flags/slots in a copied DOM do not authorize execution. |
| ownership | Ordinary caller-owned value; Rows/strings/vectors/maps own their storage and can allocate when constructed or copied. No native account authority is created. |
| failure | Schema/version/binding/tree/lowering/resource/encoding/allocation errors propagate before a completed result; producers/native state are not mutated. |
| cost | Full plan/source/scalar/array DOM construction with no final byte/item cap. |
| Design | [include/crown/io/physical.hpp](../../../../../../include/crown/io/physical.hpp), [src/io/physical.cpp](../../../../../../src/io/physical.cpp), [docs/physical_plans.md](../../../../../physical_plans.md) |

```text
Json write_physical(const CompiledProgram& plan);
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Explicitly export native metadata through the compiler DTO boundary. |
| inputs / outputs | PhysicalPlan::from_compiled makes an ordinary owned export, then delegates unchanged serializer. |
| invariants | This allocation boundary is separate from native mutation/publication; no native-to-DTO mirror retained afterward. |
| ownership | Ordinary caller-owned value; Rows/strings/vectors/maps own their storage and can allocate when constructed or copied. No native account authority is created. |
| failure | Schema/version/binding/tree/lowering/resource/encoding/allocation errors propagate before a completed result; producers/native state are not mutated. |
| cost | Complete native metadata export followed by full ordinary serializer; exported DTO and DOM overlap. |
| Design | [include/crown/io/physical.hpp](../../../../../../include/crown/io/physical.hpp), [src/io/physical.cpp](../../../../../../src/io/physical.cpp), [docs/physical_plans.md](../../../../../physical_plans.md) |

## B0002

[Lines 14–17](../../../../../../include/crown/io/physical.hpp#L14); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct PhysicalReadLimits {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Supply independent physical/compiler reconstruction caps. |
| inputs / outputs | Lowering and nested program read limits. |
| invariants | Stored producer limits and host reconstruction caps are separate; neither DTO admits a native runtime by itself. |
| ownership | Inline fixed fields only; copying these values allocates no container or text. No source/native owner is retained. |
| failure | Declaration/field initialization performs no semantic validation. Consumers validate the actual values at their own boundary. |
| cost | Fixed-size initialization/copy/comparison; declaration itself performs no runtime scan or I/O. |
| Design | [include/crown/io/physical.hpp](../../../../../../include/crown/io/physical.hpp), [src/io/physical.cpp](../../../../../../src/io/physical.cpp), [docs/physical_plans.md](../../../../../physical_plans.md) |

```text
PhysicalLimits lowering;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | The independent host lowering/identity operational limits. |
| inputs / outputs | Stores/exposes the independent host lowering/identity operational limits. |
| invariants | Stored producer limits and host reconstruction caps are separate; neither DTO admits a native runtime by itself. |
| ownership | Inline fixed fields only; copying these values allocates no container or text. No source/native owner is retained. |
| failure | Assignment adds no validation; aggregate construction/copy has the ownership costs stated here. |
| cost | Fixed-size initialization/copy/comparison; declaration itself performs no runtime scan or I/O. |
| Design | [include/crown/io/physical.hpp](../../../../../../include/crown/io/physical.hpp), [src/io/physical.cpp](../../../../../../src/io/physical.cpp), [docs/physical_plans.md](../../../../../physical_plans.md) |

```text
ProgramReadLimits program;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | The nested binding/normalization host replay limits. |
| inputs / outputs | Stores/exposes the nested binding/normalization host replay limits. |
| invariants | Stored producer limits and host reconstruction caps are separate; neither DTO admits a native runtime by itself. |
| ownership | Inline fixed fields only; copying these values allocates no container or text. No source/native owner is retained. |
| failure | Assignment adds no validation; aggregate construction/copy has the ownership costs stated here. |
| cost | Fixed-size initialization/copy/comparison; declaration itself performs no runtime scan or I/O. |
| Design | [include/crown/io/physical.hpp](../../../../../../include/crown/io/physical.hpp), [src/io/physical.cpp](../../../../../../src/io/physical.cpp), [docs/physical_plans.md](../../../../../physical_plans.md) |

## B0003

[Lines 18–22](../../../../../../include/crown/io/physical.hpp#L18); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
PhysicalPlan read_physical(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Rebuild and compare the complete physical artifact. |
| inputs / outputs | Checks version/lowerer/storage/source tag, reconstructs source and checked tree, lowers under host caps then compares complete serialization. |
| invariants | No imported tree_valid/height/guarantee/slot flag is trusted. Tree validity/lowering is not automatically original minimum-height evidence. |
| ownership | Ordinary caller-owned value; Rows/strings/vectors/maps own their storage and can allocate when constructed or copied. No native account authority is created. |
| failure | Schema/version/binding/tree/lowering/resource/encoding/allocation errors propagate before a completed result; producers/native state are not mutated. |
| cost | Full DOM parse, nested source/tree/program dump/replay, lowering/identity work and complete output comparison; no total input DOM byte cap. |
| Design | [include/crown/io/physical.hpp](../../../../../../include/crown/io/physical.hpp), [src/io/physical.cpp](../../../../../../src/io/physical.cpp), [docs/physical_plans.md](../../../../../physical_plans.md) |
