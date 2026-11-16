# `include/crown/ir/ids.hpp` — block usage map

[Source](../../../../../../include/crown/ir/ids.hpp) · [Source index](../../../../README.md) · [Subsystem contracts](../../../../subsystem_contracts.md) · [Reviewed primitives](../../../../primitives.md)

Give numeric IDs distinct types so owner/component domains are not interchanged accidentally.

Snapshot SHA-256: `5122223dc584233588dce881a3376b66f310fda3ab0e99820684afd43eef6cf0`. 39 lines partitioned into 20 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [ir](../../../../subsystem_contracts.md#ir). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/semantics.md](../../../../../semantics.md), [docs/physical_plans.md](../../../../../physical_plans.md), [docs/physical_runtime.md](../../../../../physical_runtime.md), [docs/query_identity.md](../../../../../query_identity.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–9](../../../../../../include/crown/ir/ids.hpp#L1) | Imports dependencies; guards repeated header inclusion; declares namespace scope. | source comment (unverified): // Plan/catalog ID wrappers carry scalar values scoped to a compiled document; · [reviewed contract](#b0001) |
| [B0002 · 10–10](../../../../../../include/crown/ir/ids.hpp#L10) | Type/record definition: struct TableId | source comment (unverified): // Plan/catalog ID wrappers carry scalar values scoped to a compiled document; · [reviewed contract](#b0002) |
| [B0003 · 11–11](../../../../../../include/crown/ir/ids.hpp#L11) | Type/record definition: struct ColumnId |  · [reviewed contract](#b0003) |
| [B0004 · 12–12](../../../../../../include/crown/ir/ids.hpp#L12) | Type/record definition: struct VariableId |  · [reviewed contract](#b0004) |
| [B0005 · 13–13](../../../../../../include/crown/ir/ids.hpp#L13) | Type/record definition: struct OccurrenceId |  · [reviewed contract](#b0005) |
| [B0006 · 14–14](../../../../../../include/crown/ir/ids.hpp#L14) | Type/record definition: struct NodeId |  · [reviewed contract](#b0006) |
| [B0007 · 15–15](../../../../../../include/crown/ir/ids.hpp#L15) | Type/record definition: struct RelationId |  · [reviewed contract](#b0007) |
| [B0008 · 16–16](../../../../../../include/crown/ir/ids.hpp#L16) | Type/record definition: struct LayoutId |  · [reviewed contract](#b0008) |
| [B0009 · 17–17](../../../../../../include/crown/ir/ids.hpp#L17) | Type/record definition: struct FieldId |  · [reviewed contract](#b0009) |
| [B0010 · 18–18](../../../../../../include/crown/ir/ids.hpp#L18) | Type/record definition: struct IndexRequirementId |  · [reviewed contract](#b0010) |
| [B0011 · 19–19](../../../../../../include/crown/ir/ids.hpp#L19) | Explanatory comments or spacing. | source comment (unverified): // Runtime IDs are monotonic within one storage owner; zero is not allocated. · [reviewed contract](#b0011) |
| [B0012 · 20–20](../../../../../../include/crown/ir/ids.hpp#L20) | Type/record definition: struct TupleId | source comment (unverified): // Runtime IDs are monotonic within one storage owner; zero is not allocated. · [reviewed contract](#b0012) |
| [B0013 · 21–21](../../../../../../include/crown/ir/ids.hpp#L21) | Type/record definition: struct IndexId |  · [reviewed contract](#b0013) |
| [B0014 · 22–22](../../../../../../include/crown/ir/ids.hpp#L22) | Type/record definition: struct StorageOwnerId |  · [reviewed contract](#b0014) |
| [B0015 · 23–24](../../../../../../include/crown/ir/ids.hpp#L23) | Explanatory comments or spacing. | source comment (unverified): // Arena slots may be reused. Their allocation identity includes a generation; · [reviewed contract](#b0015) |
| [B0016 · 25–25](../../../../../../include/crown/ir/ids.hpp#L25) | Type/record definition: struct ArenaOwnerId | source comment (unverified): // Arena slots may be reused. Their allocation identity includes a generation; · [reviewed contract](#b0016) |
| [B0017 · 26–26](../../../../../../include/crown/ir/ids.hpp#L26) | Type/record definition: struct TupleSlotId |  · [reviewed contract](#b0017) |
| [B0018 · 27–32](../../../../../../include/crown/ir/ids.hpp#L27) | Type/record definition: struct ArenaHandle |  · [reviewed contract](#b0018) |
| [B0019 · 33–38](../../../../../../include/crown/ir/ids.hpp#L33) | Type/record definition: struct TupleHandle |  · [reviewed contract](#b0019) |
| [B0020 · 39–39](../../../../../../include/crown/ir/ids.hpp#L39) | Closes surrounding scope/type. | source comment (unverified): // namespace crown · [reviewed contract](#b0020) |

## B0001

[Lines 1–9](../../../../../../include/crown/ir/ids.hpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L1-L9:sha256:6cf405c807459ffdd24288b97d28d79dc2646cd96aa2766bd31781e9fb526cd9
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Header guard, comparison and integer dependencies, then crown namespace opening for scalar ID wrappers and arena handles. Embedded source note records intended usage: Plan/catalog ID wrappers carry scalar values scoped to a compiled document; they do not check range or establish that a value belongs to that document. Treat that prose as guidance, not as independently verified executable behavior. |
| inputs / outputs | No runtime inputs/outputs are declared by the import/scope lines themselves. |
| invariants | The header guard prevents repeat inclusion in a translation unit; imported declarations determine compile-time names. The note/type comments in this span are guidance and do not add runtime validation or a capability. |
| ownership | No object ownership is created by the imports or namespace tokens. |
| failure | No runtime failure path is introduced by the guard/imports; incompatible or missing declarations fail during compilation or linking. |
| cost | Preprocessor/compiler work only for these lines; the guard adds no per-operation runtime work. |
| Design | [include/crown/ir/ids.hpp](../../../../../../include/crown/ir/ids.hpp), [docs/code_specs/files/include/crown/ir/ids.hpp.md](ids.hpp.md), [docs/semantics.md](../../../../../semantics.md), [docs/physical_plans.md](../../../../../physical_plans.md) |

## B0002

[Lines 10–10](../../../../../../include/crown/ir/ids.hpp#L10); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct TableId {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Identifies a table in the catalog bound to one compiled document. |
| inputs / outputs | Carries a public size_t value used wherever a catalog table reference is required. |
| invariants | The number is meaningful only in its catalog/document scope; this aggregate neither checks range nor establishes catalog membership. |
| ownership | Inline scalar wrapper with defaulted lexicographic comparison; it owns no catalog or table. |
| failure | Any size_t, including an out-of-range value, can be stored. Catalog/query admission and consuming lookup report invalid references. |
| cost | Constant-size storage, copy, and comparison; no allocation. |
| Design | [include/crown/ir/ids.hpp](../../../../../../include/crown/ir/ids.hpp), [docs/storage.md](../../../../../storage.md), [docs/tuple_arenas.md](../../../../../tuple_arenas.md), [include/crown/ir/model.hpp](../../../../../../include/crown/ir/model.hpp), [src/planner/lower.cpp](../../../../../../src/planner/lower.cpp), [src/planner/verify.cpp](../../../../../../src/planner/verify.cpp) |

## B0003

[Lines 11–11](../../../../../../include/crown/ir/ids.hpp#L11); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct ColumnId {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Identifies a column position within a catalog table. |
| inputs / outputs | Carries a size_t field used by table schema references and constraints. |
| invariants | The wrapper does not bind a column to a table; consumers must interpret it against the relevant table. |
| ownership | Inline scalar wrapper; no catalog ownership. |
| failure | Any value is representable; schema/query validation or consumer checks detect invalid positions. |
| cost | Constant-size storage, copy, and comparison; no allocation. |
| Design | [include/crown/ir/ids.hpp](../../../../../../include/crown/ir/ids.hpp), [docs/storage.md](../../../../../storage.md), [docs/tuple_arenas.md](../../../../../tuple_arenas.md), [include/crown/ir/model.hpp](../../../../../../include/crown/ir/model.hpp), [src/planner/lower.cpp](../../../../../../src/planner/lower.cpp), [src/planner/verify.cpp](../../../../../../src/planner/verify.cpp) |

## B0004

[Lines 12–12](../../../../../../include/crown/ir/ids.hpp#L12); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct VariableId {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Identifies a query variable position in a compiled document. |
| inputs / outputs | Carries the numeric variable reference used in terms, scopes, heads, and projections. |
| invariants | The value is document-scoped and is not checked against Query::variables by construction. |
| ownership | Inline scalar wrapper with value comparison; no Query ownership. |
| failure | Out-of-range values can be formed; validate(catalog, query), validate_tree, or typed consumers establish validity. |
| cost | Constant-size storage and comparison. |
| Design | [include/crown/ir/ids.hpp](../../../../../../include/crown/ir/ids.hpp), [docs/storage.md](../../../../../storage.md), [docs/tuple_arenas.md](../../../../../tuple_arenas.md), [include/crown/ir/model.hpp](../../../../../../include/crown/ir/model.hpp), [src/planner/lower.cpp](../../../../../../src/planner/lower.cpp), [src/planner/verify.cpp](../../../../../../src/planner/verify.cpp) |

## B0005

[Lines 13–13](../../../../../../include/crown/ir/ids.hpp#L13); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct OccurrenceId {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Identifies an atom occurrence position in a compiled query. |
| inputs / outputs | Carries a numeric occurrence reference used by adapters and physical inputs. |
| invariants | The value is scoped to the query/program; the wrapper does not prove an atom exists or appears exactly once in a tree. |
| ownership | Inline scalar wrapper; no atom ownership. |
| failure | Invalid position is representable; physical adapter access reports invalid_input_port and tree validation checks occurrence coverage. |
| cost | Constant-size storage and comparison. |
| Design | [include/crown/ir/ids.hpp](../../../../../../include/crown/ir/ids.hpp), [docs/storage.md](../../../../../storage.md), [docs/tuple_arenas.md](../../../../../tuple_arenas.md), [include/crown/ir/model.hpp](../../../../../../include/crown/ir/model.hpp), [src/planner/lower.cpp](../../../../../../src/planner/lower.cpp), [src/planner/verify.cpp](../../../../../../src/planner/verify.cpp) |

## B0006

[Lines 14–14](../../../../../../include/crown/ir/ids.hpp#L14); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct NodeId {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | References a node in a supplied or lowered tree. |
| inputs / outputs | Carries the numeric node reference used for roots, children, parents, and plan mappings. |
| invariants | Meaning depends on the owning FreeConnexTree/PhysicalPlan; it is not validated or dereferenced by the wrapper. |
| ownership | Inline scalar wrapper; no tree ownership. |
| failure | Invalid references are representable; validate_tree checks topology and references before a tree is accepted. |
| cost | Constant-size storage and comparison. |
| Design | [include/crown/ir/ids.hpp](../../../../../../include/crown/ir/ids.hpp), [docs/storage.md](../../../../../storage.md), [docs/tuple_arenas.md](../../../../../tuple_arenas.md), [include/crown/ir/model.hpp](../../../../../../include/crown/ir/model.hpp), [src/planner/lower.cpp](../../../../../../src/planner/lower.cpp), [src/planner/verify.cpp](../../../../../../src/planner/verify.cpp) |

## B0007

[Lines 15–15](../../../../../../include/crown/ir/ids.hpp#L15); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct RelationId {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Identifies a relation descriptor in a physical plan and corresponding storage table. |
| inputs / outputs | Carries a numeric relation reference between nodes, edges, requirements, and storage. |
| invariants | The value is plan-local; this wrapper does not establish relation existence, role, or layout compatibility. |
| ownership | Inline scalar wrapper; no relation/storage ownership. |
| failure | Invalid references are representable; validated lowering creates in-range IDs and consuming storage checks binding/layout. |
| cost | Constant-size storage and comparison. |
| Design | [include/crown/ir/ids.hpp](../../../../../../include/crown/ir/ids.hpp), [docs/storage.md](../../../../../storage.md), [docs/tuple_arenas.md](../../../../../tuple_arenas.md), [include/crown/ir/model.hpp](../../../../../../include/crown/ir/model.hpp), [src/planner/lower.cpp](../../../../../../src/planner/lower.cpp), [src/planner/verify.cpp](../../../../../../src/planner/verify.cpp) |

## B0008

[Lines 16–16](../../../../../../include/crown/ir/ids.hpp#L16); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct LayoutId {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Names a layout descriptor within a compiled plan/catalog context. |
| inputs / outputs | Carries a numeric descriptor label alongside a TupleLayout. |
| invariants | A label is not the immutable runtime layout token; equal IDs do not by themselves prove token compatibility. |
| ownership | Inline scalar wrapper; no layout ownership. |
| failure | Any value can be stored; TupleLayout token checks establish interoperability. |
| cost | Constant-size storage and comparison. |
| Design | [include/crown/ir/ids.hpp](../../../../../../include/crown/ir/ids.hpp), [docs/storage.md](../../../../../storage.md), [docs/tuple_arenas.md](../../../../../tuple_arenas.md), [include/crown/ir/model.hpp](../../../../../../include/crown/ir/model.hpp), [src/planner/lower.cpp](../../../../../../src/planner/lower.cpp), [src/planner/verify.cpp](../../../../../../src/planner/verify.cpp) |

## B0009

[Lines 17–17](../../../../../../include/crown/ir/ids.hpp#L17); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct FieldId {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Selects a numeric field position in a layout or projection. |
| inputs / outputs | Carries a slot index used by projections, guards, and result assembly instructions. |
| invariants | Its meaning is relative to a particular layout/program; construction does not check field bounds. |
| ownership | Inline scalar wrapper; no layout ownership. |
| failure | Out-of-range values are representable; projection construction or consumer validation/checking establishes valid use. |
| cost | Constant-size storage and comparison. |
| Design | [include/crown/ir/ids.hpp](../../../../../../include/crown/ir/ids.hpp), [docs/storage.md](../../../../../storage.md), [docs/tuple_arenas.md](../../../../../tuple_arenas.md), [include/crown/ir/model.hpp](../../../../../../include/crown/ir/model.hpp), [src/planner/lower.cpp](../../../../../../src/planner/lower.cpp), [src/planner/verify.cpp](../../../../../../src/planner/verify.cpp) |

## B0010

[Lines 18–18](../../../../../../include/crown/ir/ids.hpp#L18); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct IndexRequirementId {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | References a compiled index requirement in a PhysicalPlan. |
| inputs / outputs | Carries an index-descriptor position used by edges and enumeration steps. |
| invariants | It identifies a plan requirement, not a backend-assigned runtime IndexId; scope is one plan. |
| ownership | Inline scalar wrapper; no requirement or runtime index ownership. |
| failure | Any value is representable; lowerer constructs valid references and consumers check requirement binding. |
| cost | Constant-size storage and comparison. |
| Design | [include/crown/ir/ids.hpp](../../../../../../include/crown/ir/ids.hpp), [docs/storage.md](../../../../../storage.md), [docs/tuple_arenas.md](../../../../../tuple_arenas.md), [include/crown/ir/model.hpp](../../../../../../include/crown/ir/model.hpp), [src/planner/lower.cpp](../../../../../../src/planner/lower.cpp), [src/planner/verify.cpp](../../../../../../src/planner/verify.cpp) |

## B0011

[Lines 19–19](../../../../../../include/crown/ir/ids.hpp#L19); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L19-L19:sha256:c4e0d2225f7bd16acfc4335954c316c10c30ffdec3eda1c8be342ac1290399d5
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Design note for adjacent code: Runtime IDs are monotonic within one storage owner; zero is not allocated. This is caller guidance recorded as prose, not an executable result. |
| inputs / outputs | No runtime interface is implemented by these comment-only lines. They sit at include/crown/ir/ids.hpp lines 17-21; the surrounding declaration/body defines its own inputs and outputs. |
| invariants | The words record the intended use boundary only. They do not add a guard, proof, capability, transaction, durability guarantee, or account charge; verify behavior in the referenced implementation. |
| ownership | Comment text owns no data. Object lifetimes, borrows, and account attribution remain those of the adjacent source objects and their constructors. |
| failure | No failure path is implemented here. Any mentioned failure or recovery rule belongs to the adjacent operation and its existing error carrier. |
| cost | No runtime work is performed by these lines; any cost/bound in the note is not certified by this comment-only card. |
| Design | [include/crown/ir/ids.hpp](../../../../../../include/crown/ir/ids.hpp), [docs/code_specs/files/include/crown/ir/ids.hpp.md](ids.hpp.md), [docs/semantics.md](../../../../../semantics.md), [docs/physical_plans.md](../../../../../physical_plans.md) |

## B0012

[Lines 20–20](../../../../../../include/crown/ir/ids.hpp#L20); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct TupleId {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Names a logical tuple record within one storage owner. |
| inputs / outputs | Carries the monotonically assigned uint64 logical row ID used inside a TupleHandle and table ID maps. |
| invariants | Nonzero, monotonically allocated per table owner and not reused after erase/clear; exhaustion is handled by the allocator, not this value type. |
| ownership | Inline scalar wrapper; the ID does not retain the tuple payload or arena slot. |
| failure | The aggregate accepts zero and arbitrary values. Table allocation detects exhaustion; lookups distinguish foreign ownership from absent records. |
| cost | Constant-size value and comparison. |
| Design | [include/crown/ir/ids.hpp](../../../../../../include/crown/ir/ids.hpp), [docs/storage.md](../../../../../storage.md), [docs/tuple_arenas.md](../../../../../tuple_arenas.md), [include/crown/storage/reference.hpp](../../../../../../include/crown/storage/reference.hpp), [src/storage/reference.cpp](../../../../../../src/storage/reference.cpp) |

## B0013

[Lines 21–21](../../../../../../include/crown/ir/ids.hpp#L21); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct IndexId {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Names a runtime storage index within one table owner. |
| inputs / outputs | Carries the uint64 ID returned by runtime index registration and passed to index operations. |
| invariants | Nonzero, monotonic, and not reused within its owning table; distinct from an IndexRequirementId in the compile-time plan. |
| ownership | Inline scalar wrapper; no projection/index ownership. |
| failure | Arbitrary values can be formed; runtime lookup reports unknown_index and allocation reports overflow at exhaustion. |
| cost | Constant-size value and comparison. |
| Design | [include/crown/ir/ids.hpp](../../../../../../include/crown/ir/ids.hpp), [docs/storage.md](../../../../../storage.md), [include/crown/storage/reference.hpp](../../../../../../include/crown/storage/reference.hpp), [src/storage/reference.cpp](../../../../../../src/storage/reference.cpp), [include/crown/storage/accounted_reference.hpp](../../../../../../include/crown/storage/accounted_reference.hpp) |

## B0014

[Lines 22–22](../../../../../../include/crown/ir/ids.hpp#L22); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct StorageOwnerId {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Tags one logical storage-table owner for runtime IDs and handles. |
| inputs / outputs | Carries the uint64 owner component compared by TupleHandle consumers. |
| invariants | Owner identity must be paired with relation and tuple ID; the scalar wrapper neither creates nor verifies an owner. |
| ownership | Inline scalar value; it does not own storage state or extend table lifetime. |
| failure | Any value can be constructed; a consumer rejects a foreign owner when validating a handle. |
| cost | Constant-size value and comparison. |
| Design | [include/crown/ir/ids.hpp](../../../../../../include/crown/ir/ids.hpp), [docs/storage.md](../../../../../storage.md), [include/crown/storage/reference.hpp](../../../../../../include/crown/storage/reference.hpp), [src/storage/reference.cpp](../../../../../../src/storage/reference.cpp), [src/storage/accounted_plan.cpp](../../../../../../src/storage/accounted_plan.cpp) |

## B0015

[Lines 23–24](../../../../../../include/crown/ir/ids.hpp#L23); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L23-L24:sha256:5b763cf866a4f424693c5ca2f821141180ecfde74bc6e708a8a4641730611f97
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Design note for adjacent code: Arena slots may be reused. Their allocation identity includes a generation; logical TupleId values above remain independent and monotonic. This is caller guidance recorded as prose, not an executable result. |
| inputs / outputs | No runtime interface is implemented by these comment-only lines. They sit at include/crown/ir/ids.hpp lines 21-26; the surrounding declaration/body defines its own inputs and outputs. |
| invariants | The words record the intended use boundary only. They do not add a guard, proof, capability, transaction, durability guarantee, or account charge; verify behavior in the referenced implementation. |
| ownership | Comment text owns no data. Object lifetimes, borrows, and account attribution remain those of the adjacent source objects and their constructors. |
| failure | No failure path is implemented here. Any mentioned failure or recovery rule belongs to the adjacent operation and its existing error carrier. |
| cost | No runtime work is performed by these lines; any cost/bound in the note is not certified by this comment-only card. |
| Design | [include/crown/ir/ids.hpp](../../../../../../include/crown/ir/ids.hpp), [docs/code_specs/files/include/crown/ir/ids.hpp.md](ids.hpp.md), [docs/semantics.md](../../../../../semantics.md), [docs/physical_plans.md](../../../../../physical_plans.md) |

## B0016

[Lines 25–25](../../../../../../include/crown/ir/ids.hpp#L25); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct ArenaOwnerId {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Tags one tuple-arena allocation owner in ArenaHandle values. |
| inputs / outputs | Carries the owner component checked before an arena slot is resolved. |
| invariants | Arena allocation identity is separate from logical StorageOwnerId/ TupleId identity; equality alone does not prove the arena remains alive. |
| ownership | Inline scalar wrapper; holds no arena state or tuple payload. |
| failure | Any value is storable; arena operations throw foreign_handle when it differs from the live arena owner. |
| cost | Constant-size value and comparison. |
| Design | [include/crown/ir/ids.hpp](../../../../../../include/crown/ir/ids.hpp), [docs/tuple_arenas.md](../../../../../tuple_arenas.md), [include/crown/storage/arena.hpp](../../../../../../include/crown/storage/arena.hpp), [src/storage/arena.cpp](../../../../../../src/storage/arena.cpp), [include/crown/storage/accounted_arena.hpp](../../../../../../include/crown/storage/accounted_arena.hpp) |

## B0017

[Lines 26–26](../../../../../../include/crown/ir/ids.hpp#L26); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct TupleSlotId {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Names a position in a tuple arena's slot directory. |
| inputs / outputs | Carries the size_t slot index in an ArenaHandle. |
| invariants | Slot positions may be reused and are only unique together with arena owner and generation. |
| ownership | Inline scalar wrapper; no slot or payload ownership. |
| failure | Any value is representable; arena checks bounds, live state, and generation. |
| cost | Constant-size value and comparison. |
| Design | [include/crown/ir/ids.hpp](../../../../../../include/crown/ir/ids.hpp), [docs/tuple_arenas.md](../../../../../tuple_arenas.md), [include/crown/storage/arena.hpp](../../../../../../include/crown/storage/arena.hpp), [src/storage/arena.cpp](../../../../../../src/storage/arena.cpp) |

## B0018

[Lines 27–32](../../../../../../include/crown/ir/ids.hpp#L27); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct ArenaHandle {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Identifies one arena allocation by owner, slot, and generation. |
| inputs / outputs | Packages ArenaOwnerId, TupleSlotId, and generation for TupleArena contains/get/pin/erase operations. |
| invariants | The full triple distinguishes reused slots; aggregate construction performs no owner, bounds, liveness, or generation check. |
| ownership | Inline value handle; it does not retain the arena, row, or pin. A separate Pin retains payload lifetime. |
| failure | Foreign owners are rejected; same-owner out-of-range, erased, or wrong-generation handles are stale. contains/erase report false for stale handles while get/pin throw, as documented. |
| cost | Fixed-size copy/comparison; arena checks are constant-time against owner and slot metadata. |
| Design | [include/crown/ir/ids.hpp](../../../../../../include/crown/ir/ids.hpp), [docs/tuple_arenas.md](../../../../../tuple_arenas.md), [include/crown/storage/arena.hpp](../../../../../../include/crown/storage/arena.hpp), [src/storage/arena.cpp](../../../../../../src/storage/arena.cpp), [src/storage/accounted_arena.cpp](../../../../../../src/storage/accounted_arena.cpp) |

## B0019

[Lines 33–38](../../../../../../include/crown/ir/ids.hpp#L33); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct TupleHandle {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Identifies a logical row by storage owner, relation, and monotonic tuple ID. |
| inputs / outputs | Packages StorageOwnerId, RelationId, and TupleId for public reference-table row APIs. |
| invariants | All three components participate in identity. It differs from ArenaHandle, which names a physical slot generation. |
| ownership | Inline value handle; it neither owns nor pins a row. get returns a borrow with a documented mutation/destruction fence; pin is separate. |
| failure | A foreign owner or relation is rejected; a same-owner ID no longer present is absent/stale according to the operation. The handle itself cannot detect that state. |
| cost | Fixed-size copy/comparison; reference lookup adds map work. No allocation for the handle. |
| Design | [include/crown/ir/ids.hpp](../../../../../../include/crown/ir/ids.hpp), [docs/storage.md](../../../../../storage.md), [docs/tuple_arenas.md](../../../../../tuple_arenas.md), [include/crown/storage/reference.hpp](../../../../../../include/crown/storage/reference.hpp), [src/storage/reference.cpp](../../../../../../src/storage/reference.cpp) |

## B0020

[Lines 39–39](../../../../../../include/crown/ir/ids.hpp#L39); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L39-L39:sha256:250c3e1595f7269cedf50435b03d999ca6184ec33c6daa9baf0e4bd97c55f07a
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Closes the namespace crown at this source boundary; this is a lexical delimiter, not an operation. |
| inputs / outputs | No runtime input or output. Declarations following the span leave the preceding C++ scope. |
| invariants | The delimiter ends the preceding scope's visibility/linkage region; it adds no validation, publication, ownership transfer, or runtime authority. |
| ownership | The delimiter adds no owner. If it ends a function/block with live automatic objects, their normal destructors release those objects; namespace and type-definition closes change no existing object's lifetime. |
| failure | No explicit failure translation or catch is added. If a function/block exit destroys automatic objects, exception behavior follows those destructors; namespace/type closes have no runtime failure path. |
| cost | The delimiter adds no algorithmic work. A function/block exit can run existing automatic-object destructors and cleanup; namespace/type closes have no runtime cost. |
| Design | [include/crown/ir/ids.hpp](../../../../../../include/crown/ir/ids.hpp), [docs/code_specs/files/include/crown/ir/ids.hpp.md](ids.hpp.md), [docs/semantics.md](../../../../../semantics.md), [docs/physical_plans.md](../../../../../physical_plans.md) |
