# `include/crown/io/support.hpp` — block usage map

[Source](../../../../../../include/crown/io/support.hpp) · [Source index](../../../../README.md) · [Subsystem contracts](../../../../subsystem_contracts.md) · [Reviewed primitives](../../../../primitives.md)

Declare logical-support diagnostic trace import and snapshot/epoch JSON export.

Snapshot SHA-256: `f691240da4e3627b157acaf45d051e0c9ed38e059900826277f905c5f23d8364`. 17 lines partitioned into 3 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [io](../../../../subsystem_contracts.md#io). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/ingestion.md](../../../../../ingestion.md), [docs/query_identity.md](../../../../../query_identity.md), [docs/schema_evolution.md](../../../../../schema_evolution.md), [docs/cli.md](../../../../../cli.md), [docs/query_memory.md](../../../../../query_memory.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–5](../../../../../../include/crown/io/support.hpp#L1) | Imports dependencies; guards repeated header inclusion; declares namespace scope. |  · [reviewed contract](#b0001) |
| [B0002 · 6–9](../../../../../../include/crown/io/support.hpp#L6) | Type/record definition: struct SupportTrace |  · [reviewed contract](#b0002) |
| [B0003 · 10–17](../../../../../../include/crown/io/support.hpp#L10) | declares callable signatures; declares values/defaults or compile-time conditions. | source comment (unverified): // Diagnostic logical-native trace, not physical ingestion/checkpoint replay. · [reviewed contract](#b0003) |

## B0001

[Lines 1–5](../../../../../../include/crown/io/support.hpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
#pragma once
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Declare the io support public interface and its required types. |
| inputs / outputs | Header imports its explicit dependencies and declares the APIs/contracts below. |
| invariants | Inclusion does not construct a live query, source, report, proof or file owner. |
| ownership | Declarations retain no instance; object ownership and copies are specified at the individual APIs. |
| failure | Compile-time dependency/declaration boundary; runtime failures belong to instantiated objects/operations. |
| cost | No runtime action from inclusion itself; inline methods retain their stated actual costs. |
| Design | [include/crown/io/support.hpp](../../../../../../include/crown/io/support.hpp), [src/io/support.cpp](../../../../../../src/io/support.cpp), [docs/runtime_support.md](../../../../../runtime_support.md) |

## B0002

[Lines 6–9](../../../../../../include/crown/io/support.hpp#L6); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct SupportTrace {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Own an explicit logical-native diagnostic update trace. |
| inputs / outputs | Fixed SupportOptions and ordinary vector of NativeSetUpdate rows in logical node scope. |
| invariants | Diagnostic trace is not physical ingestion, checkpoint replay or durable output authority. |
| ownership | Ordinary caller-owned value; Rows/strings/vectors/maps own their storage and can allocate when constructed or copied. No native account authority is created. |
| failure | Declaration/field initialization performs no semantic validation. Consumers validate the actual values at their own boundary. |
| cost | Explicit ordinary container/text ownership and deep-copy costs; field declarations add no execution or validation pass. |
| Design | [include/crown/io/support.hpp](../../../../../../include/crown/io/support.hpp), [src/io/support.cpp](../../../../../../src/io/support.cpp), [docs/runtime_support.md](../../../../../runtime_support.md) |

```text
runtime::SupportOptions options;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | The support/observation/work/memory configuration to test. |
| inputs / outputs | Stores/exposes the support/observation/work/memory configuration to test. |
| invariants | Diagnostic trace is not physical ingestion, checkpoint replay or durable output authority. |
| ownership | Ordinary caller-owned value; Rows/strings/vectors/maps own their storage and can allocate when constructed or copied. No native account authority is created. |
| failure | Assignment adds no validation; aggregate construction/copy has the ownership costs stated here. |
| cost | Explicit ordinary container/text ownership and deep-copy costs; field declarations add no execution or validation pass. |
| Design | [include/crown/io/support.hpp](../../../../../../include/crown/io/support.hpp), [src/io/support.cpp](../../../../../../src/io/support.cpp), [docs/runtime_support.md](../../../../../runtime_support.md) |

```text
std::vector<runtime::NativeSetUpdate> updates;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | The owning logical-native update sequence, distinct from physical table events. |
| inputs / outputs | Stores/exposes the owning logical-native update sequence, distinct from physical table events. |
| invariants | Diagnostic trace is not physical ingestion, checkpoint replay or durable output authority. |
| ownership | Ordinary caller-owned value; Rows/strings/vectors/maps own their storage and can allocate when constructed or copied. No native account authority is created. |
| failure | Assignment adds no validation; aggregate construction/copy has the ownership costs stated here. |
| cost | Explicit ordinary container/text ownership and deep-copy costs; field declarations add no execution or validation pass. |
| Design | [include/crown/io/support.hpp](../../../../../../include/crown/io/support.hpp), [src/io/support.cpp](../../../../../../src/io/support.cpp), [docs/runtime_support.md](../../../../../runtime_support.md) |

## B0003

[Lines 10–17](../../../../../../include/crown/io/support.hpp#L10); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
read_support_trace(std::string_view text, const PhysicalPlan& plan
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Read bounded logical-native support diagnostic input. |
| inputs / outputs | Parses a complete DOM and validates logical node/update rows against the supplied plan, enforcing max_updates. |
| invariants | Logical scope rows are not physical full source-table rows; no source positions, native apply or checkpoint admission here. |
| ownership | Ordinary caller-owned value; Rows/strings/vectors/maps own their storage and can allocate when constructed or copied. No native account authority is created. |
| failure | Diagnostic schema/node/op/row/count/scalar/allocation errors propagate. |
| cost | Full DOM parse before update-count rejection, then owned vector/Row/scalar copies; no encoded-byte budget in this API. |
| Design | [include/crown/io/support.hpp](../../../../../../include/crown/io/support.hpp), [src/io/support.cpp](../../../../../../src/io/support.cpp), [docs/runtime_support.md](../../../../../runtime_support.md) |

```text
write_support_snapshot(const runtime::SupportSnapshot& snapshot, const PhysicalPlan& plan
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Export a captured support snapshot as a diagnostic DOM. |
| inputs / outputs | Serializes node/state/layout and owning/retained tuple values using the supplied immutable plan. |
| invariants | Mutable data alone never authorizes source acceptance, native plan execution, proof, output acknowledgment or durable publication. |
| ownership | Borrows snapshot/plan; output owns ordinary arrays/scalars/strings and retains no live owner. |
| failure | Encoding/contract/allocation errors return no completed DOM. |
| cost | Visits every exported captured row/field and creates ordinary nested JSON; no final item/byte cap or implicit fresh runtime capture. |
| Design | [include/crown/io/support.hpp](../../../../../../include/crown/io/support.hpp), [src/io/support.cpp](../../../../../../src/io/support.cpp), [docs/runtime_support.md](../../../../../runtime_support.md) |

```text
read_support_trace(std::string_view text,const CompiledProgram& plan
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Read bounded logical-native support diagnostic input. |
| inputs / outputs | Parses a complete DOM and validates logical node/update rows against the supplied plan, enforcing max_updates. |
| invariants | Logical scope rows are not physical full source-table rows; no source positions, native apply or checkpoint admission here. |
| ownership | Ordinary caller-owned value; Rows/strings/vectors/maps own their storage and can allocate when constructed or copied. No native account authority is created. |
| failure | Diagnostic schema/node/op/row/count/scalar/allocation errors propagate. |
| cost | Full DOM parse before update-count rejection, then owned vector/Row/scalar copies; no encoded-byte budget in this API. |
| Design | [include/crown/io/support.hpp](../../../../../../include/crown/io/support.hpp), [src/io/support.cpp](../../../../../../src/io/support.cpp), [docs/runtime_support.md](../../../../../runtime_support.md) |

```text
write_support_snapshot(const runtime::SupportSnapshot& snapshot,const CompiledProgram& plan
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Export a captured support snapshot as a diagnostic DOM. |
| inputs / outputs | Serializes node/state/layout and owning/retained tuple values using the supplied immutable plan. |
| invariants | Mutable data alone never authorizes source acceptance, native plan execution, proof, output acknowledgment or durable publication. |
| ownership | Borrows snapshot/plan; output owns ordinary arrays/scalars/strings and retains no live owner. |
| failure | Encoding/contract/allocation errors return no completed DOM. |
| cost | Visits every exported captured row/field and creates ordinary nested JSON; no final item/byte cap or implicit fresh runtime capture. |
| Design | [include/crown/io/support.hpp](../../../../../../include/crown/io/support.hpp), [src/io/support.cpp](../../../../../../src/io/support.cpp), [docs/runtime_support.md](../../../../../runtime_support.md) |

```text
Json write_support_options(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Present support/observation limits as diagnostic data. |
| inputs / outputs | Copies support and observation configuration into a DOM. |
| invariants | Mutable data alone never authorizes source acceptance, native plan execution, proof, output acknowledgment or durable publication. |
| ownership | Borrows existing snapshot/options; output owns ordinary JSON storage. |
| failure | Contract/encoding/allocation errors propagate with no native mutation. |
| cost | Fixed field population plus ordinary policy/JSON storage. |
| Design | [include/crown/io/support.hpp](../../../../../../include/crown/io/support.hpp), [src/io/support.cpp](../../../../../../src/io/support.cpp), [docs/runtime_support.md](../../../../../runtime_support.md) |

```text
Json write_support_epoch(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Present one captured support epoch/journal. |
| inputs / outputs | Exports metrics/transitions/pinned tuple values/record and event metadata. |
| invariants | Mutable data alone never authorizes source acceptance, native plan execution, proof, output acknowledgment or durable publication. |
| ownership | Borrows existing snapshot/options; output owns ordinary JSON storage. |
| failure | Contract/encoding/allocation errors propagate with no native mutation. |
| cost | Full captured journal/transition/scalar traversal and ordinary DOM allocation; no native replay. |
| Design | [include/crown/io/support.hpp](../../../../../../include/crown/io/support.hpp), [src/io/support.cpp](../../../../../../src/io/support.cpp), [docs/runtime_support.md](../../../../../runtime_support.md) |
