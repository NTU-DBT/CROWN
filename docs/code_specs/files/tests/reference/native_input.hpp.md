# `tests/reference/native_input.hpp` — block usage map

[Source](../../../../../tests/reference/native_input.hpp) · [Source index](../../../README.md) · [Subsystem contracts](../../../subsystem_contracts.md) · [Reviewed primitives](../../../primitives.md)

Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection.

Snapshot SHA-256: `f7bdaf79a5de830f570ae0b6b5851bb95ce5668fd4988c900930876d9a9f8625`. 16 lines partitioned into 10 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [tests](../../../subsystem_contracts.md#tests). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/code_review.md](../../../../code_review.md), [docs/reference_fuzz.md](../../../../reference_fuzz.md), [docs/task_ledger.md](../../../../task_ledger.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–7](../../../../../tests/reference/native_input.hpp#L1) | Imports dependencies; guards repeated header inclusion; declares namespace scope. | source comment (unverified): // Legacy values are borrowed; native program/view values get owning exports · [reviewed contract](#b0001) |
| [B0002 · 8–8](../../../../../tests/reference/native_input.hpp#L8) | Callable definition: inline const Catalog& catalog(const Catalog& value) | calls ; returns value · [reviewed contract](#b0002) |
| [B0003 · 9–9](../../../../../tests/reference/native_input.hpp#L9) | Callable definition: inline Catalog catalog(const program::Catalog& value) | calls planner::compiler_source_detail::catalog; returns planner::compiler_source_detail::catalog(value) · [reviewed contract](#b0003) |
| [B0004 · 10–10](../../../../../tests/reference/native_input.hpp#L10) | Callable definition: inline const Query& query(const Query& value) | calls ; returns value · [reviewed contract](#b0004) |
| [B0005 · 11–11](../../../../../tests/reference/native_input.hpp#L11) | Callable definition: inline Query query(const program::Query& value) | calls planner::compiler_source_detail::query; returns planner::compiler_source_detail::query(value) · [reviewed contract](#b0005) |
| [B0006 · 12–12](../../../../../tests/reference/native_input.hpp#L12) | Callable definition: inline const frontend::NormalizedSql& normalized(const frontend::NormalizedSql& value) | calls ; returns value · [reviewed contract](#b0006) |
| [B0007 · 13–13](../../../../../tests/reference/native_input.hpp#L13) | Callable definition: inline frontend::NormalizedSql normalized(const program::NormalizedSql& value) | calls planner::compiler_source_detail::normalized; returns planner::compiler_source_detail::normalized(value) · [reviewed contract](#b0007) |
| [B0008 · 14–14](../../../../../tests/reference/native_input.hpp#L14) | Callable definition: inline const Value& scalar(const Value& value) | calls ; returns value · [reviewed contract](#b0008) |
| [B0009 · 15–15](../../../../../tests/reference/native_input.hpp#L15) | Callable definition: inline Value scalar(const storage::ScalarView& value) | calls storage::export_scalar; returns storage::export_scalar(value) · [reviewed contract](#b0009) |
| [B0010 · 16–16](../../../../../tests/reference/native_input.hpp#L16) | Closes surrounding scope/type. | source comment (unverified): // namespace crown::reference::input · [reviewed contract](#b0010) |

## B0001

[Lines 1–7](../../../../../tests/reference/native_input.hpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L1-L7:sha256:12a85fd37add5be959f08005015251d93e316a791989a9c57c57c436246aac43
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Prepare native_input.hpp: include "../../src/planner/compiled_source.hpp". |
| inputs / outputs | Compiler-visible dependencies, names and the recorded declarations in; declarations available to the following fixture/CLI/example definitions out. |
| invariants | Declarations are scoped to this source/header and its selected ABI. Included code has its own effects; names and editable fixture values do not confer proof, admission or publication authority. |
| ownership | Aliases/includes do not create a query owner. Pointers/references/views are non-owning. Containers own their elements, which can themselves be borrowed pointers or numeric IDs. Only documented owning shared-control handles retain controls; IDs/slot-handle values do not independently keep an arena/runtime alive. |
| failure | Missing headers, ill-formed names/types, failed static assertions or active #error directives stop compilation. No runtime rejection/rollback mechanism is implemented by aliases or function prototypes. |
| cost | Preprocessing and type/constraint instantiation cost compilation. Alias/prototype syntax does not invoke the declared operation; any included definitions keep their own initialization effects. |
| Design | [tests/reference/native_input.hpp](../../../../../tests/reference/native_input.hpp), [docs/ingestion.md](../../../../ingestion.md), [docs/code_review.md](../../../../code_review.md) |

## B0002

[Lines 8–8](../../../../../tests/reference/native_input.hpp#L8); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
inline const Catalog& catalog(const Catalog& value)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Pass an already legacy owning catalog to a reference algorithm without copying it. |
| inputs / outputs | Returns the same const Catalog reference supplied by the caller. |
| invariants | This overload borrows; it does not create an owning export or validate catalog semantics. |
| ownership | Caller keeps the Catalog alive. A temporary argument may be consumed within its full expression but cannot supply a retained reference afterward. |
| failure | No throwing work in the body; caller lifetime misuse is not checked. |
| cost | Constant reference forwarding; no container traversal. |
| Design | [tests/reference/native_input.hpp](../../../../../tests/reference/native_input.hpp), [include/crown/ir/model.hpp](../../../../../include/crown/ir/model.hpp) |

## B0003

[Lines 9–9](../../../../../tests/reference/native_input.hpp#L9); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
inline Catalog catalog(const program::Catalog& value)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Export native immutable catalog metadata as an owning legacy reference input. |
| inputs / outputs | Calls compiler_source_detail::catalog and returns its Catalog value. |
| invariants | Exports semantic metadata rather than importing native proof/account authority or caching compiler state in a runtime. |
| ownership | Returned ordinary DTO owns copied names/tables/column/constraint values; native program view is borrowed during the copy. |
| failure | Export/container allocation failures propagate; no validation/retry boundary is introduced. |
| cost | Traverses/copies admitted catalog metadata and scalar/text payload using the existing cold exporter. |
| Design | [tests/reference/native_input.hpp](../../../../../tests/reference/native_input.hpp), [src/planner/compiled_source.cpp](../../../../../src/planner/compiled_source.cpp), [src/planner/compiled_source.hpp](../../../../../src/planner/compiled_source.hpp) |

## B0004

[Lines 10–10](../../../../../tests/reference/native_input.hpp#L10); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
inline const Query& query(const Query& value)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Forward an existing legacy query by const reference to a reference algorithm. |
| inputs / outputs | Returns the identical Query reference with no shape conversion. |
| invariants | Does not clone, normalize or authenticate the query. |
| ownership | Borrow requires the input Query to outlive use; do not retain a reference returned from a temporary after its full expression. |
| failure | No failure handling or validation occurs in this body. |
| cost | Constant reference forwarding. |
| Design | [tests/reference/native_input.hpp](../../../../../tests/reference/native_input.hpp), [include/crown/ir/model.hpp](../../../../../include/crown/ir/model.hpp) |

## B0005

[Lines 11–11](../../../../../tests/reference/native_input.hpp#L11); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
inline Query query(const program::Query& value)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Make an owning legacy query from immutable native query metadata. |
| inputs / outputs | Delegates to compiler_source_detail::query and returns Query by value. |
| invariants | Retains declared occurrences/terms/head/contradiction data as copied input; it is not a minimum-height proof or a native-owner import. |
| ownership | Returned query owns ordinary containers/Value payload after the source program view is released. |
| failure | Copy/allocation failures propagate unchanged. |
| cost | Linear metadata/term/payload copying through the existing cold exporter. |
| Design | [tests/reference/native_input.hpp](../../../../../tests/reference/native_input.hpp), [src/planner/compiled_source.cpp](../../../../../src/planner/compiled_source.cpp) |

## B0006

[Lines 12–12](../../../../../tests/reference/native_input.hpp#L12); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
inline const frontend::NormalizedSql& normalized(const frontend::NormalizedSql& value)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Forward an already owning normalized-SQL artifact to reference tooling. |
| inputs / outputs | Returns the same const NormalizedSql reference. |
| invariants | Performs no normalization, identity check or ownership transfer. |
| ownership | The caller’s artifact must outlive the borrowed reference; a temporary is usable only within its full expression. |
| failure | No throwing work/translation in the forwarding body. |
| cost | Constant reference forwarding. |
| Design | [tests/reference/native_input.hpp](../../../../../tests/reference/native_input.hpp), [include/crown/frontend/normalize.hpp](../../../../../include/crown/frontend/normalize.hpp) |

## B0007

[Lines 13–13](../../../../../tests/reference/native_input.hpp#L13); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
inline frontend::NormalizedSql normalized(const program::NormalizedSql& value)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Copy immutable native normalized metadata into the owning legacy normalized-SQL DTO. |
| inputs / outputs | Uses compiler_source_detail::normalized and returns the exported value. |
| invariants | Copies representation for independent reference consumers; does not rerun SQL parsing/admission or grant runtime authority. |
| ownership | Returned ordinary artifact owns its copied metadata/payload; source view is borrowed for the export only. |
| failure | Exporter/allocation failures propagate, with no fallback normalization. |
| cost | Visits/copies complete admitted normalized metadata; costs are not charged as native update work. |
| Design | [tests/reference/native_input.hpp](../../../../../tests/reference/native_input.hpp), [src/planner/compiled_source.cpp](../../../../../src/planner/compiled_source.cpp), [include/crown/frontend/normalize.hpp](../../../../../include/crown/frontend/normalize.hpp) |

## B0008

[Lines 14–14](../../../../../tests/reference/native_input.hpp#L14); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
inline const Value& scalar(const Value& value)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Borrow an existing legacy scalar without copying its payload. |
| inputs / outputs | Returns the same const Value reference. |
| invariants | Preserves exact variant kind; no coercion or validation is attempted. |
| ownership | Caller retains Value storage, including strings; temporary arguments cannot back a retained post-expression reference. |
| failure | No throwing operation in this body. |
| cost | Constant reference forwarding. |
| Design | [tests/reference/native_input.hpp](../../../../../tests/reference/native_input.hpp), [include/crown/ir/model.hpp](../../../../../include/crown/ir/model.hpp) |

## B0009

[Lines 15–15](../../../../../tests/reference/native_input.hpp#L15); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
inline Value scalar(const storage::ScalarView& value)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Export a borrowed native ScalarView as an owning legacy Value. |
| inputs / outputs | Calls storage::export_scalar and returns the owning variant. |
| invariants | Exact scalar kind/value is retained; TEXT/decimal payload export is not a lossy numeric conversion. |
| ownership | Returned Value owns required payload after the source view expires; view backing must remain stable during copying. |
| failure | Export/domain/allocation failures propagate; no extra catch or allocator wrapper is added. |
| cost | Fixed scalar work or payload-length copy for owning representations. |
| Design | [tests/reference/native_input.hpp](../../../../../tests/reference/native_input.hpp), [include/crown/storage/tuple_values.hpp](../../../../../include/crown/storage/tuple_values.hpp) |

## B0010

[Lines 16–16](../../../../../tests/reference/native_input.hpp#L16); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L16-L16:sha256:3f97e287134f94bf7beb7d6b414b09dd3e54af19a1370e3ba66d486a16e05dd9
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Close the recorded declaration scopes in native_input.hpp: namespace crown::reference::input. |
| inputs / outputs | Preceding namespace, type or initializer declarations in; completed lexical boundary out. |
| invariants | Brace-opening context is recorded in root-scope-context-v1.json. These are declaration/initializer boundaries, not an independent update, validation or recovery operation. |
| ownership | Enclosing objects and borrowed fields keep their declared ownership. This punctuation creates no new owner. |
| failure | Malformed scope syntax is a compile error. Any initializer/constructor failure belongs to the enclosing object declaration. |
| cost | No separate loop, guard or engine call is introduced by the delimiter; enclosing initialization and object lifetime still have their actual costs. |
| Design | [tests/reference/native_input.hpp](../../../../../tests/reference/native_input.hpp), [docs/ingestion.md](../../../../ingestion.md), [docs/code_review.md](../../../../code_review.md) |
