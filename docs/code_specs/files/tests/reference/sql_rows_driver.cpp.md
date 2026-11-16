# `tests/reference/sql_rows_driver.cpp` — block usage map

[Source](../../../../../tests/reference/sql_rows_driver.cpp) · [Source index](../../../README.md) · [Subsystem contracts](../../../subsystem_contracts.md) · [Reviewed primitives](../../../primitives.md)

Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection.

Snapshot SHA-256: `44b185da37a79529fa5bb9199e2cacd57a73bf68ccfefb73cd31089a2aba914d`. 71 lines partitioned into 5 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [tests](../../../subsystem_contracts.md#tests). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/code_review.md](../../../../code_review.md), [docs/reference_fuzz.md](../../../../reference_fuzz.md), [docs/task_ledger.md](../../../../task_ledger.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–10](../../../../../tests/reference/sql_rows_driver.cpp#L1) | Imports dependencies; declares namespace scope; declares aliases. |  · [reviewed contract](#b0001) |
| [B0002 · 11–19](../../../../../tests/reference/sql_rows_driver.cpp#L11) | Callable definition: Json snapshot(const runtime::SqlRowsRuntime& runtime) | calls Json::array, results, next, view; returns {{@ , runtime.sequence()}, {@ , std::move(rows)}}; growth push_back; 2 loop sites · [reviewed contract](#b0002) |
| [B0003 · 20–64](../../../../../tests/reference/sql_rows_driver.cpp#L20) | Callable definition: Json evaluate(const Json& request) | calls io::read_catalog_payload, at, contains, Json::array; returns {{@ , request.at(@ )}, {@ , std::move(types)}, {@ , std::move(trace)}}; growth emplace_back, push_back; 5 loop sites · [reviewed contract](#b0003) |
| [B0004 · 65–66](../../../../../tests/reference/sql_rows_driver.cpp#L65) | Closes surrounding scope/type. | source comment (unverified): // namespace · [reviewed contract](#b0004) |
| [B0005 · 67–71](../../../../../tests/reference/sql_rows_driver.cpp#L67) | Callable definition: int main() | calls std::getline, evaluate, Json::parse, dump; returns 1; 1 loop sites · [reviewed contract](#b0005) |

## B0001

[Lines 1–10](../../../../../tests/reference/sql_rows_driver.cpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L1-L10:sha256:6e6f8db1617ece57b203423669c1f6420e3864be7789195f3bce9757bf435cb5
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Prepare sql_rows_driver.cpp: include "crown/runtime/sql_rows.hpp", "crown/api/error.hpp", "crown/io/catalog.hpp", "crown/planner/oracle.hpp", "indexed_runtime_fixture.hpp", &lt;iostream&gt;; bind local aliases/name imports. |
| inputs / outputs | Compiler-visible dependencies, names and the recorded declarations in; declarations available to the following fixture/CLI/example definitions out. |
| invariants | Declarations are scoped to this source/header and its selected ABI. Included code has its own effects; names and editable fixture values do not confer proof, admission or publication authority. |
| ownership | Aliases/includes do not create a query owner. Pointers/references/views are non-owning. Containers own their elements, which can themselves be borrowed pointers or numeric IDs. Only documented owning shared-control handles retain controls; IDs/slot-handle values do not independently keep an arena/runtime alive. |
| failure | Missing headers, ill-formed names/types, failed static assertions or active #error directives stop compilation. No runtime rejection/rollback mechanism is implemented by aliases or function prototypes. |
| cost | Preprocessing and type/constraint instantiation cost compilation. Alias/prototype syntax does not invoke the declared operation; any included definitions keep their own initialization effects. |
| Design | [tests/reference/sql_rows_driver.cpp](../../../../../tests/reference/sql_rows_driver.cpp), [docs/sql_rows_batches.md](../../../../sql_rows_batches.md), [docs/code_review.md](../../../../code_review.md) |

## B0002

[Lines 11–19](../../../../../tests/reference/sql_rows_driver.cpp#L11); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Json snapshot(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Observe the actual compressed SQL cursor. |
| inputs / outputs | Runtime to sequence and owning typed JSON rows. |
| invariants | Completely drains native output; result schema remains owned; weight is emitted as uint64 JSON, and scalar tags preserve date/numeric identity. |
| ownership | Exported JSON is ordinary test memory; returned tuples own native payload until serialization ends. |
| failure | Traversal/export failure fails the executable. |
| cost | Explicit full result traversal/copy after each update, outside production apply. |
| Design | [docs/sql_rows_runtime.md](../../../../sql_rows_runtime.md), [Refactor.md §W05](../../../../../Refactor.md), [build/verification/w05-rows-oracle-human-review-v1/README.md](../../../../../build/verification/w05-rows-oracle-human-review-v1/README.md), [build/verification/w05-rows-oracle-human-review-v1/CORRECTION-1.md](../../../../../build/verification/w05-rows-oracle-human-review-v1/CORRECTION-1.md) |

## B0003

[Lines 20–64](../../../../../tests/reference/sql_rows_driver.cpp#L20); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Json evaluate(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Exercise real SQL binding, checked tree choice and physical replacements. |
| inputs / outputs | One JSON scenario to output metadata and all snapshots. |
| invariants | Fresh immutable compiler program and actual core feed checked search/lowering. Typed parameters are bound once; before/after are supplied, not inferred from runtime. NULL parameter/source values directly emplace disengaged optionals; present values directly emplace the same typed scalar through std::in_place. Borrowed Cells directly emplace the same ScalarViews or NULL after the complete owned row is built. Alternative tags, value order and before/after weights are unchanged; no temporary optional construction remains in these three loops. |
| ownership | Cold ordinary DTOs feed the receiver-owned runtime. Parameters own decoded Values until binding freezes them. Each complete owned source row is built before borrowed Cell/string views; both owned and borrowed vectors remain alive and unmodified through synchronous apply and snapshot. The runtime retains its genuine account-funded copy, not these views. |
| failure | Unexpected rejection/incomplete proof/failed update aborts the driver; no alternate evaluator. Scalar decode/allocation errors propagate through the same process boundary; direct emplace avoids the GCC13 O3 optional/variant temporary warning without suppressing warnings or adding catches. |
| cost | Cold compilation plus the same scalar/field parsing, vector construction, actual updates and explicit snapshots. Direct optional emplacement removes temporary wrappers without introducing a runtime hook or changing asymptotic work; no mature engine is linked. |
| Design | [docs/sql_rows_runtime.md](../../../../sql_rows_runtime.md), [Refactor.md §W05](../../../../../Refactor.md), [build/verification/w05-rows-oracle-human-review-v1/README.md](../../../../../build/verification/w05-rows-oracle-human-review-v1/README.md), [build/verification/w05-rows-oracle-human-review-v1/CORRECTION-1.md](../../../../../build/verification/w05-rows-oracle-human-review-v1/CORRECTION-1.md) |

## B0004

[Lines 65–66](../../../../../tests/reference/sql_rows_driver.cpp#L65); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L65-L66:sha256:c2bd7638f09d52cb034ed574f539304035fc6fab162bf8d5fa20a35d8c7288a1
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Close the recorded declaration scopes in sql_rows_driver.cpp: namespace (anonymous). |
| inputs / outputs | Preceding namespace, type or initializer declarations in; completed lexical boundary out. |
| invariants | Brace-opening context is recorded in root-scope-context-v1.json. These are declaration/initializer boundaries, not an independent update, validation or recovery operation. |
| ownership | Enclosing objects and borrowed fields keep their declared ownership. This punctuation creates no new owner. |
| failure | Malformed scope syntax is a compile error. Any initializer/constructor failure belongs to the enclosing object declaration. |
| cost | No separate loop, guard or engine call is introduced by the delimiter; enclosing initialization and object lifetime still have their actual costs. |
| Design | [tests/reference/sql_rows_driver.cpp](../../../../../tests/reference/sql_rows_driver.cpp), [docs/sql_rows_batches.md](../../../../sql_rows_batches.md), [docs/code_review.md](../../../../code_review.md) |

## B0005

[Lines 67–71](../../../../../tests/reference/sql_rows_driver.cpp#L67); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
int main()
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Serve deterministic line-oriented oracle requests. |
| inputs / outputs | One request line to one response line. |
| invariants | No per-case failure is silently skipped or relabelled success. |
| ownership | Executable owns I/O and per-request state. |
| failure | One top-level reporting catch exits nonzero. |
| cost | Linear protocol bytes plus evaluate work; test harness only. |
| Design | [docs/sql_rows_runtime.md](../../../../sql_rows_runtime.md), [Refactor.md §W05](../../../../../Refactor.md), [build/verification/w05-rows-oracle-human-review-v1/README.md](../../../../../build/verification/w05-rows-oracle-human-review-v1/README.md), [build/verification/w05-rows-oracle-human-review-v1/CORRECTION-1.md](../../../../../build/verification/w05-rows-oracle-human-review-v1/CORRECTION-1.md) |
