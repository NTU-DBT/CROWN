# `tests/support/indexed_runtime_fixture.hpp` — block usage map

[Source](../../../../../tests/support/indexed_runtime_fixture.hpp) · [Source index](../../../README.md) · [Subsystem contracts](../../../subsystem_contracts.md) · [Reviewed primitives](../../../primitives.md)

Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection.

Snapshot SHA-256: `24d8d23b638acd67355e01cd9f019f8080f1297388d6f3b9fe3d41dc74dc2bcb`. 21 lines partitioned into 5 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [tests](../../../subsystem_contracts.md#tests). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/code_review.md](../../../../code_review.md), [docs/reference_fuzz.md](../../../../reference_fuzz.md), [docs/task_ledger.md](../../../../task_ledger.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–7](../../../../../tests/support/indexed_runtime_fixture.hpp#L1) | Imports dependencies; guards repeated header inclusion; declares namespace scope. | source comment (unverified): // Backend selector only. Derived fixtures retain their existing independent · [reviewed contract](#b0001) |
| [B0002 · 8–14](../../../../../tests/support/indexed_runtime_fixture.hpp#L8) | Callable definition: inline PhysicalOptions options() | calls ; returns value; source comment (unverified): // Limits are component counts and one aggregate operation grant, not query bytes. · [reviewed contract](#b0002) |
| [B0003 · 15–17](../../../../../tests/support/indexed_runtime_fixture.hpp#L15) | Callable definition: inline PhysicalPlan lower_tree(const Catalog& catalog,const Query& query,const FreeConnexTree& tree) | calls planner::lower_tree, options; returns planner::lower_tree(catalog,query,tree,options()) · [reviewed contract](#b0003) |
| [B0004 · 18–20](../../../../../tests/support/indexed_runtime_fixture.hpp#L18) | Callable definition: inline PhysicalPlan lower_normalized(const frontend::NormalizedSql& program,const FreeConnexTree& tree) | calls planner::lower_normalized, options; returns planner::lower_normalized(program,tree,options()) · [reviewed contract](#b0004) |
| [B0005 · 21–21](../../../../../tests/support/indexed_runtime_fixture.hpp#L21) | Closes surrounding scope/type. | source comment (unverified): // namespace crown::s04_runtime · [reviewed contract](#b0005) |

## B0001

[Lines 1–7](../../../../../tests/support/indexed_runtime_fixture.hpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L1-L7:sha256:bb2288c099dc2c0fe4c8e0afa199089ef7971412565ae0f27beda76bead93a8c
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Prepare indexed_runtime_fixture.hpp: include "crown/planner/lower.hpp". |
| inputs / outputs | Compiler-visible dependencies, names and the recorded declarations in; declarations available to the following fixture/CLI/example definitions out. |
| invariants | Declarations are scoped to this source/header and its selected ABI. Included code has its own effects; names and editable fixture values do not confer proof, admission or publication authority. |
| ownership | Aliases/includes do not create a query owner. Pointers/references/views are non-owning. Containers own their elements, which can themselves be borrowed pointers or numeric IDs. Only documented owning shared-control handles retain controls; IDs/slot-handle values do not independently keep an arena/runtime alive. |
| failure | Missing headers, ill-formed names/types, failed static assertions or active #error directives stop compilation. No runtime rejection/rollback mechanism is implemented by aliases or function prototypes. |
| cost | Preprocessing and type/constraint instantiation cost compilation. Alias/prototype syntax does not invoke the declared operation; any included definitions keep their own initialization effects. |
| Design | [tests/support/indexed_runtime_fixture.hpp](../../../../../tests/support/indexed_runtime_fixture.hpp), [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/code_review.md](../../../../code_review.md) |

## B0002

[Lines 8–14](../../../../../tests/support/indexed_runtime_fixture.hpp#L8); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
inline PhysicalOptions options()
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Select finite indexed table components and one aggregate native operation allowance for derived fixtures. |
| inputs / outputs | Sets per-table limits rows4096,indices64,keys32768,memberships65536,nodes131072,directory_slots524288,arena_slots8192,arena_pins32768,journal_entries8192; each of five per-operation IndexWork domains is 1e9. |
| invariants | Backend selector only: these counts are neither query allocator-byte cap nor per-table refills. Original independent data/oracle/failure assertions remain consumer responsibilities. |
| ownership | Inline editable PhysicalOptions DTO; admitted immutable plan later binds values and runtime creates/reuses actual account/work owners. |
| failure | No admission/catch here; real lower/runtime construction validates/funds configured storage. |
| cost | Fixed scalar/optional setup; no indexed table directory, plan or work grant allocation yet. |
| Design | [tests/support/indexed_runtime_fixture.hpp](../../../../../tests/support/indexed_runtime_fixture.hpp), [include/crown/storage/backend.hpp](../../../../../include/crown/storage/backend.hpp), [include/crown/storage/index_work.hpp](../../../../../include/crown/storage/index_work.hpp), [src/planner/lower.cpp](../../../../../src/planner/lower.cpp), [tests/unit/indexed_physical_runtime_test.cpp](../../../../../tests/unit/indexed_physical_runtime_test.cpp), [tests/unit/indexed_owner_statistics_test.cpp](../../../../../tests/unit/indexed_owner_statistics_test.cpp), [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/query_memory.md](../../../../query_memory.md), [docs/code_review.md](../../../../code_review.md) |

## B0003

[Lines 15–17](../../../../../tests/support/indexed_runtime_fixture.hpp#L15); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
inline PhysicalPlan lower_tree(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Lower actual catalog/query/checked tree with the fixture's finite indexed backend options. |
| inputs / outputs | Delegates planner::lower_tree(catalog,query,tree,options()). |
| invariants | Public lowering still validates source/tree and computes immutable compiler plan; fixture does not bypass proof/source checks or replace row/oracle semantics. |
| ownership | Returns owning PhysicalPlan; actual copies share its immutable plan control, default moves can empty source. Ordinary input catalog/query/tree remain caller-owned. |
| failure | All lower/identity/metadata/limit/allocation failures propagate; no fallback backend or handler. |
| cost | Fixed wrapper plus full actual lowering/validation/source identity and plan allocations; runtime import/setup remains separate. |
| Design | [tests/support/indexed_runtime_fixture.hpp](../../../../../tests/support/indexed_runtime_fixture.hpp), [include/crown/storage/backend.hpp](../../../../../include/crown/storage/backend.hpp), [include/crown/storage/index_work.hpp](../../../../../include/crown/storage/index_work.hpp), [src/planner/lower.cpp](../../../../../src/planner/lower.cpp), [tests/unit/indexed_physical_runtime_test.cpp](../../../../../tests/unit/indexed_physical_runtime_test.cpp), [tests/unit/indexed_owner_statistics_test.cpp](../../../../../tests/unit/indexed_owner_statistics_test.cpp), [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/query_memory.md](../../../../query_memory.md), [docs/code_review.md](../../../../code_review.md) |

## B0004

[Lines 18–20](../../../../../tests/support/indexed_runtime_fixture.hpp#L18); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
inline PhysicalPlan lower_normalized(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Lower an actual normalized SQL source while retaining finite indexed options. |
| inputs / outputs | Delegates planner::lower_normalized(program,tree,options()). |
| invariants | Normalized source/core binding and selected tree gates remain in production lowering. An editable SQL/DTO flag alone is not executable/proof authority. |
| ownership | Compiler plan owns retained/copy metadata; caller NormalizedSql/tree are borrowed during the cold compiler boundary. |
| failure | Real source replay/binding/lowering/identity/account/allocation failures propagate unchanged. |
| cost | Full normalized-source lowering/admission/metadata copies in addition to fixed wrapper; no query rows are imported here. |
| Design | [tests/support/indexed_runtime_fixture.hpp](../../../../../tests/support/indexed_runtime_fixture.hpp), [include/crown/storage/backend.hpp](../../../../../include/crown/storage/backend.hpp), [include/crown/storage/index_work.hpp](../../../../../include/crown/storage/index_work.hpp), [src/planner/lower.cpp](../../../../../src/planner/lower.cpp), [tests/unit/indexed_physical_runtime_test.cpp](../../../../../tests/unit/indexed_physical_runtime_test.cpp), [tests/unit/indexed_owner_statistics_test.cpp](../../../../../tests/unit/indexed_owner_statistics_test.cpp), [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/query_memory.md](../../../../query_memory.md), [docs/code_review.md](../../../../code_review.md) |

## B0005

[Lines 21–21](../../../../../tests/support/indexed_runtime_fixture.hpp#L21); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L21-L21:sha256:3b3057ff95e3b33da30fae083e4431628786e1191905c4d6b6980e80527dbe61
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Close the recorded declaration scopes in indexed_runtime_fixture.hpp: namespace crown::s04_runtime. |
| inputs / outputs | Preceding namespace, type or initializer declarations in; completed lexical boundary out. |
| invariants | Brace-opening context is recorded in root-scope-context-v1.json. These are declaration/initializer boundaries, not an independent update, validation or recovery operation. |
| ownership | Enclosing objects and borrowed fields keep their declared ownership. This punctuation creates no new owner. |
| failure | Malformed scope syntax is a compile error. Any initializer/constructor failure belongs to the enclosing object declaration. |
| cost | No separate loop, guard or engine call is introduced by the delimiter; enclosing initialization and object lifetime still have their actual costs. |
| Design | [tests/support/indexed_runtime_fixture.hpp](../../../../../tests/support/indexed_runtime_fixture.hpp), [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/code_review.md](../../../../code_review.md) |
