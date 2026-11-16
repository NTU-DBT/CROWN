# `tests/reference/candidate_set.hpp` — block usage map

[Source](../../../../../tests/reference/candidate_set.hpp) · [Source index](../../../README.md) · [Subsystem contracts](../../../subsystem_contracts.md) · [Reviewed primitives](../../../primitives.md)

Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection.

Snapshot SHA-256: `7dfd92b695cbd2cfc17473559c14acd8a43bbbc48d0ef8ef416f76a24f840c9d`. 63 lines partitioned into 9 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [tests](../../../subsystem_contracts.md#tests). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/code_review.md](../../../../code_review.md), [docs/reference_fuzz.md](../../../../reference_fuzz.md), [docs/task_ledger.md](../../../../task_ledger.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–16](../../../../../tests/reference/candidate_set.hpp#L1) | Imports dependencies; guards repeated header inclusion; declares namespace scope; declares values/defaults or compile-time conditions. | source comment (unverified): // Deliberately small operational limits for this blocking reference routine. · [reviewed contract](#b0001) |
| [B0002 · 17–21](../../../../../tests/reference/candidate_set.hpp#L17) | Type/record definition: struct NormalFormCollectionLimits | source comment (unverified): // Counts reference-level transitions. validate_tree is a bounded blocking · [reviewed contract](#b0002) |
| [B0003 · 22–22](../../../../../tests/reference/candidate_set.hpp#L22) | Explanatory comments or spacing. |  |
| [B0004 · 23–31](../../../../../tests/reference/candidate_set.hpp#L23) | Type/record definition: enum class NormalFormCollectionStop |  · [reviewed contract](#b0004) |
| [B0005 · 32–32](../../../../../tests/reference/candidate_set.hpp#L32) | Explanatory comments or spacing. |  |
| [B0006 · 33–38](../../../../../tests/reference/candidate_set.hpp#L33) | Type/record definition: struct NormalFormReferencePlan | source comment (unverified): // Equality evidence local to the supplied Catalog/Query and requested · [reviewed contract](#b0006) |
| [B0007 · 39–39](../../../../../tests/reference/candidate_set.hpp#L39) | Explanatory comments or spacing. |  |
| [B0008 · 40–48](../../../../../tests/reference/candidate_set.hpp#L40) | Type/record definition: struct NormalFormCollectionResult | source comment (unverified): // True only after every member of the finite requested-height family was · [reviewed contract](#b0008) |
| [B0009 · 49–63](../../../../../tests/reference/candidate_set.hpp#L49) | declares callable signatures; declares values/defaults or compile-time conditions. | source comment (unverified): // Collect the P02-valid, literal normal-form family for exactly the supplied · [reviewed contract](#b0009) |

## B0001

[Lines 1–16](../../../../../tests/reference/candidate_set.hpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L1-L16:sha256:461baf620cd08a0086f0cfcdfb51f769bda43ec4e139fd9d3df028a55958e33d
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Prepare candidate_set.hpp: include "crown/ir/tree.hpp", &lt;cstddef&gt;, &lt;cstdint&gt;, &lt;string&gt;, &lt;vector&gt;; declare constant fixture data. |
| inputs / outputs | Compiler-visible dependencies, names and the recorded declarations in; declarations available to the following fixture/CLI/example definitions out. The source span lists the exact member/global names, types and initial values; initializers run when the enclosing object/program/thread is initialized. |
| invariants | Declarations are scoped to this source/header and its selected ABI. Included code has its own effects; names and editable fixture values do not confer proof, admission or publication authority. |
| ownership | Aliases/includes do not create a query owner. Pointers/references/views are non-owning. Containers own their elements, which can themselves be borrowed pointers or numeric IDs. Only documented owning shared-control handles retain controls; IDs/slot-handle values do not independently keep an arena/runtime alive. |
| failure | Missing headers, ill-formed names/types, failed static assertions or active #error directives stop compilation. No runtime rejection/rollback mechanism is implemented by aliases or function prototypes. |
| cost | Preprocessing and type/constraint instantiation cost compilation. Alias/prototype syntax does not invoke the declared operation; any included definitions keep their own initialization effects. These constexpr data are fixed fixture constants; quota literals are grants, not reserved bytes or measured peaks. |
| Design | [tests/reference/candidate_set.hpp](../../../../../tests/reference/candidate_set.hpp), [docs/candidate_alternatives.md](../../../../candidate_alternatives.md), [docs/code_review.md](../../../../code_review.md), [tests/reference/candidate_set.cpp](../../../../../tests/reference/candidate_set.cpp) |

## B0002

[Lines 17–21](../../../../../tests/reference/candidate_set.hpp#L17); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct NormalFormCollectionLimits
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Set an upper bound for the bounded literal-family collector. |
| inputs / outputs | The caller supplies max_work_units; the default is 5,000,000 charged transitions. |
| invariants | This struct stores only max_work_units. The collector separately enforces fixed caps of three native occurrences and three active variables, and reports cap hits as resource stops. |
| ownership | No dynamic ownership; the value is a scalar limit copied into the collector call. |
| failure | A zero or small budget limits enumeration; it does not mean the family is unsupported. |
| cost | Reading the limits is constant work; the downstream charged transition count is independently reported. |
| Design | [tests/reference/candidate_set.hpp](../../../../../tests/reference/candidate_set.hpp), [tests/reference/candidate_set.cpp](../../../../../tests/reference/candidate_set.cpp), [tests/unit/candidates_test.cpp](../../../../../tests/unit/candidates_test.cpp), [Refactor.md §5.1](../../../../../Refactor.md), [docs/code_review.md](../../../../code_review.md), [tests/reference/candidate_set.cpp](../../../../../tests/reference/candidate_set.cpp) |

## B0004

[Lines 23–31](../../../../../tests/reference/candidate_set.hpp#L23); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
enum class NormalFormCollectionStop
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Name the collector’s stop reasons. |
| inputs / outputs | The result stores one enum value: none, work_limit, native_occurrence_cap, active_variable_cap, work_counter_overflow, allocation_failure, or container_limit. |
| invariants | Stop reason records bounded enumeration failure, never a semantic unsupported result. |
| ownership | The enum carries no owned resources. |
| failure | No exception behavior is defined by the enum itself; the collector maps caught failures to these values. |
| cost | Constant-size status value. |
| Design | [tests/reference/candidate_set.hpp](../../../../../tests/reference/candidate_set.hpp), [tests/reference/candidate_set.cpp](../../../../../tests/reference/candidate_set.cpp), [tests/unit/candidates_test.cpp](../../../../../tests/unit/candidates_test.cpp), [Refactor.md §5.1](../../../../../Refactor.md), [docs/code_review.md](../../../../code_review.md), [tests/reference/candidate_set.cpp](../../../../../tests/reference/candidate_set.cpp) |

## B0006

[Lines 33–38](../../../../../tests/reference/candidate_set.hpp#L33); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct NormalFormReferencePlan
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Pair one locally checked normal-form tree with its structural signature. |
| inputs / outputs | The result contains a signature string and a representative FreeConnexTree. |
| invariants | The signature is structural equality evidence local to the supplied Catalog/Query and requested height, not a global key or proof. The collector stores representatives only after successful P02 validation. |
| ownership | The string and tree are owned values in the result. |
| failure | This aggregate has no validating constructor. The collector validates drafts before creating entries; a caller using normal_form_reference_signature directly must establish P02 validity first. |
| cost | Copy/move cost follows the signature and tree size. |
| Design | [tests/reference/candidate_set.hpp](../../../../../tests/reference/candidate_set.hpp), [tests/reference/candidate_set.cpp](../../../../../tests/reference/candidate_set.cpp), [tests/unit/candidates_test.cpp](../../../../../tests/unit/candidates_test.cpp), [Refactor.md §5.1](../../../../../Refactor.md), [docs/code_review.md](../../../../code_review.md), [tests/reference/candidate_set.cpp](../../../../../tests/reference/candidate_set.cpp) |

## B0008

[Lines 40–48](../../../../../tests/reference/candidate_set.hpp#L40); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct NormalFormCollectionResult
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Return the collector’s unique representatives and stop accounting. |
| inputs / outputs | The result owns plans, charged work_units, exhausted/resource_limited flags, and stop reason. |
| invariants | exhausted is true only after visiting the entire requested-height family; a resource-limited prefix leaves it false. |
| ownership | The plan vector and each representative tree are owned by the result. |
| failure | Allocation/container/work limits may return a prefix with resource_limited=true. |
| cost | Storage scales with retained distinct signatures and trees; work_units counts reference transitions, not CPU. |
| Design | [tests/reference/candidate_set.hpp](../../../../../tests/reference/candidate_set.hpp), [tests/reference/candidate_set.cpp](../../../../../tests/reference/candidate_set.cpp), [tests/unit/candidates_test.cpp](../../../../../tests/unit/candidates_test.cpp), [Refactor.md §5.1](../../../../../Refactor.md), [docs/code_review.md](../../../../code_review.md), [tests/reference/candidate_set.cpp](../../../../../tests/reference/candidate_set.cpp) |

## B0009

[Lines 49–63](../../../../../tests/reference/candidate_set.hpp#L49); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L49-L63:sha256:0f133e8a696ab07ff26c7c8d827cb51d53ee5662bf6d24759d69f6817f6aa23a
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Prepare candidate_set.hpp: declare helper function signatures without invoking them. |
| inputs / outputs | Compiler-visible dependencies, names and the recorded declarations in; declarations available to the following fixture/CLI/example definitions out. Function prototypes declare the shown reference/helper API; invocation and any default-argument evaluation occur at the caller. |
| invariants | Declarations are scoped to this source/header and its selected ABI. Included code has its own effects; names and editable fixture values do not confer proof, admission or publication authority. |
| ownership | Aliases/includes do not create a query owner. Pointers/references/views are non-owning. Containers own their elements, which can themselves be borrowed pointers or numeric IDs. Only documented owning shared-control handles retain controls; IDs/slot-handle values do not independently keep an arena/runtime alive. |
| failure | Missing headers, ill-formed names/types, failed static assertions or active #error directives stop compilation. No runtime rejection/rollback mechanism is implemented by aliases or function prototypes. |
| cost | Preprocessing and type/constraint instantiation cost compilation. Alias/prototype syntax does not invoke the declared operation; any included definitions keep their own initialization effects. |
| Design | [tests/reference/candidate_set.hpp](../../../../../tests/reference/candidate_set.hpp), [docs/candidate_alternatives.md](../../../../candidate_alternatives.md), [docs/code_review.md](../../../../code_review.md), [tests/reference/candidate_set.cpp](../../../../../tests/reference/candidate_set.cpp) |
