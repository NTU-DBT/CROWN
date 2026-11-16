# `include/crown/runtime/update_view.hpp` — block usage map

[Source](../../../../../../include/crown/runtime/update_view.hpp) · [Source index](../../../../README.md) · [Subsystem contracts](../../../../subsystem_contracts.md) · [Reviewed primitives](../../../../primitives.md)

Compose one full physical source update across all its aliases into one atomic logical support epoch.

Snapshot SHA-256: `bc10b4eabb13f1a6a35b6fab9b95309e69bfc62340227858d0c5a0098225ce6b`. 17 lines partitioned into 3 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [physical](../../../../subsystem_contracts.md#physical). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/physical_runtime.md](../../../../../physical_runtime.md), [docs/runtime_initialization.md](../../../../../runtime_initialization.md), [docs/support_invariants.md](../../../../../support_invariants.md), [docs/query_memory.md](../../../../../query_memory.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–7](../../../../../../include/crown/runtime/update_view.hpp#L1) | Imports dependencies; guards repeated header inclusion; declares namespace scope. | source comment (unverified): // Borrowed input for native adapters. Values must remain alive during admission; · [reviewed contract](#b0001) |
| [B0002 · 8–16](../../../../../../include/crown/runtime/update_view.hpp#L8) | Type/record definition: struct PhysicalUpdateView | returns {update.sequence,update.table,update.operation,storage::TupleValuesView::borrow(update.values)}; source comment (unverified): // Borrowed input for native adapters. Values must remain alive during admission; · [reviewed contract](#b0002) |
| [B0003 · 17–17](../../../../../../include/crown/runtime/update_view.hpp#L17) | Closes surrounding scope/type. | source comment (unverified): // namespace crown::runtime · [reviewed contract](#b0003) |

## B0001

[Lines 1–7](../../../../../../include/crown/runtime/update_view.hpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
#pragma once
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Declare the runtime update_view public interface and its required types. |
| inputs / outputs | Header imports its explicit dependencies and declares the APIs/contracts below. |
| invariants | Inclusion does not construct a live query, source, report, proof or file owner. |
| ownership | Declarations retain no instance; object ownership and copies are specified at the individual APIs. |
| failure | Compile-time dependency/declaration boundary; runtime failures belong to instantiated objects/operations. |
| cost | No runtime action from inclusion itself; inline methods retain their stated actual costs. |
| Design | [include/crown/runtime/update_view.hpp](../../../../../../include/crown/runtime/update_view.hpp), [src/runtime/physical.cpp](../../../../../../src/runtime/physical.cpp), [src/runtime/delta.cpp](../../../../../../src/runtime/delta.cpp), [docs/physical_runtime.md](../../../../../physical_runtime.md) |

## B0002

[Lines 8–16](../../../../../../include/crown/runtime/update_view.hpp#L8); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct PhysicalUpdateView {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Describe one physical set input through tuple views. |
| inputs / outputs | Sequence, table, set operation and TupleValuesView; borrow factory does not retain an ordinary input Row. |
| invariants | Values/source backing must stay valid during admission. Editable view fields are not accepted source state; physical/delta prepare copies native ownership before returning. |
| ownership | Inline fields plus TupleValuesView. A directly supplied tuple-derived view can share an existing immutable payload; borrow(update) is deliberately nonretaining. |
| failure | Declaration/field initialization performs no semantic validation. Consumers validate the actual values at their own boundary. |
| cost | Fixed descriptor copy/variant/reference work, no row payload clone; native pending state imports independent ownership. |
| Design | [include/crown/runtime/update_view.hpp](../../../../../../include/crown/runtime/update_view.hpp), [src/runtime/physical.cpp](../../../../../../src/runtime/physical.cpp), [src/runtime/delta.cpp](../../../../../../src/runtime/delta.cpp), [docs/physical_runtime.md](../../../../../physical_runtime.md) |

```text
std::uint64_t sequence;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | The requested positive contiguous source sequence, validated by caller/native boundary. |
| inputs / outputs | Stores/exposes the requested positive contiguous source sequence, validated by caller/native boundary. |
| invariants | Values/source backing must stay valid during admission. Editable view fields are not accepted source state; physical/delta prepare copies native ownership before returning. |
| ownership | Inline fields plus TupleValuesView. A directly supplied tuple-derived view can share an existing immutable payload; borrow(update) is deliberately nonretaining. |
| failure | Assignment adds no validation; aggregate construction/copy has the ownership costs stated here. |
| cost | Fixed descriptor copy/variant/reference work, no row payload clone; native pending state imports independent ownership. |
| Design | [include/crown/runtime/update_view.hpp](../../../../../../include/crown/runtime/update_view.hpp), [src/runtime/physical.cpp](../../../../../../src/runtime/physical.cpp), [src/runtime/delta.cpp](../../../../../../src/runtime/delta.cpp), [docs/physical_runtime.md](../../../../../physical_runtime.md) |

```text
TableId table;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | The physical source table ID to validate. |
| inputs / outputs | Stores/exposes the physical source table ID to validate. |
| invariants | Values/source backing must stay valid during admission. Editable view fields are not accepted source state; physical/delta prepare copies native ownership before returning. |
| ownership | Inline fields plus TupleValuesView. A directly supplied tuple-derived view can share an existing immutable payload; borrow(update) is deliberately nonretaining. |
| failure | Assignment adds no validation; aggregate construction/copy has the ownership costs stated here. |
| cost | Fixed descriptor copy/variant/reference work, no row payload clone; native pending state imports independent ownership. |
| Design | [include/crown/runtime/update_view.hpp](../../../../../../include/crown/runtime/update_view.hpp), [src/runtime/physical.cpp](../../../../../../src/runtime/physical.cpp), [src/runtime/delta.cpp](../../../../../../src/runtime/delta.cpp), [docs/physical_runtime.md](../../../../../physical_runtime.md) |

```text
SetOperation operation;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | The insert/delete operation to validate. |
| inputs / outputs | Stores/exposes the insert/delete operation to validate. |
| invariants | Values/source backing must stay valid during admission. Editable view fields are not accepted source state; physical/delta prepare copies native ownership before returning. |
| ownership | Inline fields plus TupleValuesView. A directly supplied tuple-derived view can share an existing immutable payload; borrow(update) is deliberately nonretaining. |
| failure | Assignment adds no validation; aggregate construction/copy has the ownership costs stated here. |
| cost | Fixed descriptor copy/variant/reference work, no row payload clone; native pending state imports independent ownership. |
| Design | [include/crown/runtime/update_view.hpp](../../../../../../include/crown/runtime/update_view.hpp), [src/runtime/physical.cpp](../../../../../../src/runtime/physical.cpp), [src/runtime/delta.cpp](../../../../../../src/runtime/delta.cpp), [docs/physical_runtime.md](../../../../../physical_runtime.md) |

```text
storage::TupleValuesView values;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | The full physical input row view with its actual borrowed/shared lifetime. |
| inputs / outputs | Stores/exposes the full physical input row view with its actual borrowed/shared lifetime. |
| invariants | Values/source backing must stay valid during admission. Editable view fields are not accepted source state; physical/delta prepare copies native ownership before returning. |
| ownership | Inline fields plus TupleValuesView. A directly supplied tuple-derived view can share an existing immutable payload; borrow(update) is deliberately nonretaining. |
| failure | Assignment adds no validation; aggregate construction/copy has the ownership costs stated here. |
| cost | Fixed descriptor copy/variant/reference work, no row payload clone; native pending state imports independent ownership. |
| Design | [include/crown/runtime/update_view.hpp](../../../../../../include/crown/runtime/update_view.hpp), [src/runtime/physical.cpp](../../../../../../src/runtime/physical.cpp), [src/runtime/delta.cpp](../../../../../../src/runtime/delta.cpp), [docs/physical_runtime.md](../../../../../physical_runtime.md) |

```text
static PhysicalUpdateView borrow(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Borrow an ordinary PhysicalSetUpdate without copying its row. |
| inputs / outputs | Copies fixed sequence/table/op and calls TupleValuesView::borrow(update.values). |
| invariants | No type/domain/sequence/source acceptance occurs; original Row must remain alive through admission. |
| ownership | Explicitly nonretaining Row view; caller owns all ordinary input payload. |
| failure | Declared noexcept; no allocation or validation exception. |
| cost | Fixed field/view construction, no payload scan/copy. |
| Design | [include/crown/runtime/update_view.hpp](../../../../../../include/crown/runtime/update_view.hpp), [src/runtime/physical.cpp](../../../../../../src/runtime/physical.cpp), [src/runtime/delta.cpp](../../../../../../src/runtime/delta.cpp), [docs/physical_runtime.md](../../../../../physical_runtime.md) |

## B0003

[Lines 17–17](../../../../../../include/crown/runtime/update_view.hpp#L17); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L17-L17:sha256:024a31d07f0690bcfeef2cd00cf111a56223bd48741eae7b548b6bc9143d9111
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Close the \`namespace crown::runtime\` scope at this exact source boundary. |
| inputs / outputs | This token introduces no callable inputs or outputs. Declarations inside \`namespace crown::runtime\` define the available names, members and operations. |
| invariants | The closing brace matches the opening \`namespace crown::runtime\` at its lexical source position in include/crown/runtime/update_view.hpp; it preserves C++ namespace/type nesting. |
| ownership | The closing delimiter creates no owner. Types closed by \`namespace crown::runtime\` retain the lifetimes and allocator rules of their own fields and operations. |
| failure | No failure path executes at this closing delimiter. Failure and cleanup behavior belong to enclosed functions and owning types. |
| cost | The delimiter itself performs no runtime work; the enclosed initializers, methods and destructors carry their own costs. |
| Design | [docs/runtime_support.md](../../../../../runtime_support.md), [docs/physical_runtime.md](../../../../../physical_runtime.md), [docs/query_memory.md](../../../../../query_memory.md), [docs/code_specs/subsystem_contracts.md](../../../../subsystem_contracts.md) |
