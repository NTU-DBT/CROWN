# `src/frontend/adapter.cpp` — block usage map

[Source](../../../../../src/frontend/adapter.cpp) · [Source index](../../../README.md) · [Subsystem contracts](../../../subsystem_contracts.md) · [Reviewed primitives](../../../primitives.md)

Apply occurrence-local constants/repeated-variable tests and positional projection.

Snapshot SHA-256: `20244fc45652973d1de5d2b95fe1078c8c52ac63e83723546e21ee9065b59552`. 70 lines partitioned into 7 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [frontend](../../../subsystem_contracts.md#frontend). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/sql_support.md](../../../../sql_support.md), [docs/sql_parser.md](../../../../sql_parser.md), [docs/sql_binding.md](../../../../sql_binding.md), [docs/sql_normalization.md](../../../../sql_normalization.md), [docs/sql_admission.md](../../../../sql_admission.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–8](../../../../../src/frontend/adapter.cpp#L1) | Imports dependencies; declares namespace scope. |  · [reviewed contract](#b0001) |
| [B0002 · 9–16](../../../../../src/frontend/adapter.cpp#L9) | Callable definition: void add_support(SupportCounts& supports, Relation& relation, const Row& tuple) | calls find, end, emplace, insert; growth emplace, insert · [reviewed contract](#b0002) |
| [B0003 · 17–18](../../../../../src/frontend/adapter.cpp#L17) | Closes surrounding scope/type. | source comment (unverified): // namespace · [reviewed contract](#b0003) |
| [B0004 · 19–31](../../../../../src/frontend/adapter.cpp#L19) | Callable definition: AdapterState::AdapterState(NormalizedSql query, Database physical) : query_(std::move(query)), physical_(std::move(physical)) | calls query_, std::move, physical_, validate; growth resize; 2 loop sites · [reviewed contract](#b0004) |
| [B0005 · 32–32](../../../../../src/frontend/adapter.cpp#L32) | Explanatory comments or spacing. |  |
| [B0006 · 33–69](../../../../../src/frontend/adapter.cpp#L33) | Callable definition: AdaptedEpoch AdapterState::apply(const PhysicalSetUpdate& update) | calls max, Error, validate_row, at; returns epoch; growth insert, push_back; 1 loop sites; source comment (unverified): // Prepare every affected alias in stable occurrence order. No alias state is · [reviewed contract](#b0006) |
| [B0007 · 70–70](../../../../../src/frontend/adapter.cpp#L70) | Closes surrounding scope/type. | source comment (unverified): // namespace crown::frontend · [reviewed contract](#b0007) |

## B0001

[Lines 1–8](../../../../../src/frontend/adapter.cpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L1-L8:sha256:b04ca6b8e817b941af48179d8c79f6ab7fc86e43ce1cd291319b06256f0a34f0
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Imports compile-time dependencies (crown/frontend/adapter.hpp, crown/api/error.hpp, limits, utility) and opens crown::frontend scope for the declarations or definitions that follow. |
| inputs / outputs | No runtime inputs/outputs are declared by the import/scope lines themselves. |
| invariants | The listed headers and namespace membership determine compile-time name availability; any API behavior belongs to the declarations/definitions that follow. |
| ownership | No object ownership is created by the imports or namespace tokens. |
| failure | No runtime failure path. Missing/incompatible dependencies or a violated compile-time constraint fail translation/linking. |
| cost | Compile/preprocessor work only; no new per-operation runtime overhead. |
| Design | [src/frontend/adapter.cpp](../../../../../src/frontend/adapter.cpp), [docs/code_specs/files/src/frontend/adapter.cpp.md](adapter.cpp.md), [docs/sql_normalization.md](../../../../sql_normalization.md), [docs/sql_admission.md](../../../../sql_admission.md) |

## B0002

[Lines 9–16](../../../../../src/frontend/adapter.cpp#L9); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void add_support(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Record one distinct physical row supporting a logical projected row. |
| inputs / outputs | Candidate support map/relation and tuple; creates count1 or increments. |
| invariants | Counts are positive; relation membership is present exactly when support is positive. |
| ownership | New map key and set row own separate tuple copies in candidate/constructing state. |
| failure | Checked support overflow throws; failed insertion is safe because callers discard all candidate or incompletely constructed state. |
| cost | Ordered map probe/insertion and possibly relation insertion, row comparisons/copies; counter increment is fixed after lookup. |
| Design | [docs/sql_normalization.md](../../../../sql_normalization.md), [docs/decisions/0006-sql-normalization.md](../../../../decisions/0006-sql-normalization.md), [docs/semantics.md](../../../../semantics.md) |

## B0003

[Lines 17–18](../../../../../src/frontend/adapter.cpp#L17); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L17-L18:sha256:c2bd7638f09d52cb034ed574f539304035fc6fab162bf8d5fa20a35d8c7288a1
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Closes the anonymous namespace at this source boundary; this is a lexical delimiter, not an operation. |
| inputs / outputs | No runtime input or output. Declarations following the span leave the preceding C++ scope. |
| invariants | The delimiter ends the preceding scope's visibility/linkage region; it adds no validation, publication, ownership transfer, or runtime authority. |
| ownership | The delimiter adds no owner. If it ends a function/block with live automatic objects, their normal destructors release those objects; namespace and type-definition closes change no existing object's lifetime. |
| failure | No explicit failure translation or catch is added. If a function/block exit destroys automatic objects, exception behavior follows those destructors; namespace/type closes have no runtime failure path. |
| cost | The delimiter adds no algorithmic work. A function/block exit can run existing automatic-object destructors and cleanup; namespace/type closes have no runtime cost. |
| Design | [src/frontend/adapter.cpp](../../../../../src/frontend/adapter.cpp), [docs/code_specs/files/src/frontend/adapter.cpp.md](adapter.cpp.md), [docs/sql_normalization.md](../../../../sql_normalization.md), [docs/sql_admission.md](../../../../sql_admission.md) |

## B0004

[Lines 19–31](../../../../../src/frontend/adapter.cpp#L19); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
AdapterState::AdapterState(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Construct a correctness-reference adapter snapshot from a coherent normalized program. |
| inputs / outputs | Moves query/physical database, validates both contracts, computes all occurrence supports/logical relations. |
| invariants | Projection collisions count distinct full physical rows; aliases remain independently routed. |
| ownership | Owns program, full physical state and logical/support copies; getters borrow this owner. |
| failure | Validation, adapt_row, overflow or allocation failure destroys the unexposed partially constructed owner. |
| cost | Full validation plus every occurrence/base row adaptation and ordered support/set insertion; repeated aliases can scan the same base population. |
| Design | [docs/sql_normalization.md](../../../../sql_normalization.md), [docs/decisions/0006-sql-normalization.md](../../../../decisions/0006-sql-normalization.md), [docs/semantics.md](../../../../semantics.md) |

## B0006

[Lines 33–69](../../../../../src/frontend/adapter.cpp#L33); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
AdaptedEpoch AdapterState::apply(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Commit one contiguous physical set event to every alias atomically. |
| inputs / outputs | Next sequence, physical table/op/full row to input_changed and stable-order occurrence deltas. |
| invariants | Valid duplicate insert/absent erase advances sequence; no member swaps or sequence update until all candidate state and epoch allocations succeed. |
| ownership | Copies full physical database, support maps and logical database before routing, even on a valid no-op. Returned epoch owns delta rows. |
| failure | Sequence/row/op/constraint/support/allocation errors leave original physical/logical/support/sequence unchanged; local RAII supplies cleanup. |
| cost | Full state copies and whole-database constraint validation plus affected-alias adaptation and set/map operations; this independent reference adapter has no native CROWN update bound. |
| Design | [docs/sql_normalization.md](../../../../sql_normalization.md), [docs/decisions/0006-sql-normalization.md](../../../../decisions/0006-sql-normalization.md), [docs/semantics.md](../../../../semantics.md) |

## B0007

[Lines 70–70](../../../../../src/frontend/adapter.cpp#L70); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L70-L70:sha256:2fc33ff8830b8cd06d6971e8e31b29a8803f152d87e09a3fc4092b3efecdac93
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Closes the namespace crown::frontend at this source boundary; this is a lexical delimiter, not an operation. |
| inputs / outputs | No runtime input or output. Declarations following the span leave the preceding C++ scope. |
| invariants | The delimiter ends the preceding scope's visibility/linkage region; it adds no validation, publication, ownership transfer, or runtime authority. |
| ownership | The delimiter adds no owner. If it ends a function/block with live automatic objects, their normal destructors release those objects; namespace and type-definition closes change no existing object's lifetime. |
| failure | No explicit failure translation or catch is added. If a function/block exit destroys automatic objects, exception behavior follows those destructors; namespace/type closes have no runtime failure path. |
| cost | The delimiter adds no algorithmic work. A function/block exit can run existing automatic-object destructors and cleanup; namespace/type closes have no runtime cost. |
| Design | [src/frontend/adapter.cpp](../../../../../src/frontend/adapter.cpp), [docs/code_specs/files/src/frontend/adapter.cpp.md](adapter.cpp.md), [docs/sql_normalization.md](../../../../sql_normalization.md), [docs/sql_admission.md](../../../../sql_admission.md) |
