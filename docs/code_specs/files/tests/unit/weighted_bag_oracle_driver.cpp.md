# `tests/unit/weighted_bag_oracle_driver.cpp` — block usage map

[Source](../../../../../tests/unit/weighted_bag_oracle_driver.cpp) · [Source index](../../../README.md) · [Subsystem contracts](../../../subsystem_contracts.md) · [Reviewed primitives](../../../primitives.md)

Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection.

Snapshot SHA-256: `d438fc3725d1839adcd785f06031189112e2162962a2f1abfc4289a979ca742f`. 72 lines partitioned into 7 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [tests](../../../subsystem_contracts.md#tests). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/code_review.md](../../../../code_review.md), [docs/reference_fuzz.md](../../../../reference_fuzz.md), [docs/task_ledger.md](../../../../task_ledger.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–9](../../../../../tests/unit/weighted_bag_oracle_driver.cpp#L1) | Imports dependencies; declares namespace scope; declares aliases. |  · [reviewed contract](#b0001) |
| [B0002 · 10–25](../../../../../tests/unit/weighted_bag_oracle_driver.cpp#L10) | Callable definition: PhysicalPlan shape(const std::string& fixture, bool indexed) | calls counted_path, generalized, disconnected_bag, path; returns counted_path(indexed); counted_path(indexed,true) · [reviewed contract](#b0002) |
| [B0003 · 26–30](../../../../../tests/unit/weighted_bag_oracle_driver.cpp#L26) | Callable definition: Json row_json(const auto& values) | calls Json::array, size, push_back, io::write_scalar_view; returns result; growth push_back; 1 loop sites · [reviewed contract](#b0003) |
| [B0004 · 31–38](../../../../../tests/unit/weighted_bag_oracle_driver.cpp#L31) | Callable definition: Json state(runtime::WeightedRuntime& runtime) | calls Json::array, results, next, push_back; returns {{@ ,runtime.sequence()},{@ ,std::move(rows)},; growth push_back; 1 loop sites · [reviewed contract](#b0004) |
| [B0005 · 39–66](../../../../../tests/unit/weighted_bag_oracle_driver.cpp#L39) | Callable definition: void execute(const Json& request) | calls std::stoull, value, std::string, runtime; growth push_back; 6 loop sites · [reviewed contract](#b0005) |
| [B0006 · 67–67](../../../../../tests/unit/weighted_bag_oracle_driver.cpp#L67) | Closes surrounding scope/type. | source comment (unverified): // namespace · [reviewed contract](#b0006) |
| [B0007 · 68–72](../../../../../tests/unit/weighted_bag_oracle_driver.cpp#L68) | Callable definition: int main() | calls std::getline, execute, io::read_json, what; returns 1; 1 loop sites · [reviewed contract](#b0007) |

## B0001

[Lines 1–9](../../../../../tests/unit/weighted_bag_oracle_driver.cpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L1-L9:sha256:6c68ff40bbb5ac1c421a7fff678d0aa9acba0509c7c508c9739a6c6434b347a0
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Prepare weighted_bag_oracle_driver.cpp: include "weighted_bag_fixture.hpp", "crown/io/document.hpp", &lt;iostream&gt;; bind local aliases/name imports. |
| inputs / outputs | Compiler-visible dependencies, names and the recorded declarations in; declarations available to the following fixture/CLI/example definitions out. |
| invariants | Declarations are scoped to this source/header and its selected ABI. Included code has its own effects; names and editable fixture values do not confer proof, admission or publication authority. |
| ownership | Aliases/includes do not create a query owner. Pointers/references/views are non-owning. Containers own their elements, which can themselves be borrowed pointers or numeric IDs. Only documented owning shared-control handles retain controls; IDs/slot-handle values do not independently keep an arena/runtime alive. |
| failure | Missing headers, ill-formed names/types, failed static assertions or active #error directives stop compilation. No runtime rejection/rollback mechanism is implemented by aliases or function prototypes. |
| cost | Preprocessing and type/constraint instantiation cost compilation. Alias/prototype syntax does not invoke the declared operation; any included definitions keep their own initialization effects. |
| Design | [tests/unit/weighted_bag_oracle_driver.cpp](../../../../../tests/unit/weighted_bag_oracle_driver.cpp), [docs/weighted_enumeration.md](../../../../weighted_enumeration.md), [docs/code_review.md](../../../../code_review.md) |

## B0002

[Lines 10–25](../../../../../tests/unit/weighted_bag_oracle_driver.cpp#L10); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
PhysicalPlan shape(const std::string& fixture, bool indexed)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Select a compiled weighted bag fixture by name and backend. |
| inputs / outputs | Reads fixture string and indexed flag; returns a PhysicalPlan. |
| invariants | Recognized names select counted/tail/repeated/generalized/disconnected/path/deep-hidden/nullary/boolean/true/false; every other name falls through to unary. |
| ownership | Returns an owned plan; arguments are borrowed. |
| failure | Plan construction errors propagate to main. |
| cost | Constructs one fixed fixture plan. |
| Design | [tests/unit/weighted_bag_oracle_driver.cpp](../../../../../tests/unit/weighted_bag_oracle_driver.cpp), [tests/support/weighted_bag_fixture.hpp](../../../../../tests/support/weighted_bag_fixture.hpp), [tests/reference/weighted_bag_oracle.py](../../../../../tests/reference/weighted_bag_oracle.py), [tests/integration/weighted_bag.py](../../../../../tests/integration/weighted_bag.py), [docs/weighted_enumeration.md](../../../../weighted_enumeration.md), [tests/support/weighted_bag_fixture.hpp](../../../../../tests/support/weighted_bag_fixture.hpp) |

## B0003

[Lines 26–30](../../../../../tests/unit/weighted_bag_oracle_driver.cpp#L26); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Json row_json(const auto& values)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Encode one storage row view as JSON scalar values. |
| inputs / outputs | Reads a row-like range and returns a JSON array. |
| invariants | Each scalar is encoded in order with the shared scalar writer. |
| ownership | JSON array owns its encoded values; source view is borrowed during the loop. |
| failure | Scalar encoding/allocation errors propagate. |
| cost | One pass over row width. |
| Design | [tests/unit/weighted_bag_oracle_driver.cpp](../../../../../tests/unit/weighted_bag_oracle_driver.cpp), [tests/support/weighted_bag_fixture.hpp](../../../../../tests/support/weighted_bag_fixture.hpp), [tests/reference/weighted_bag_oracle.py](../../../../../tests/reference/weighted_bag_oracle.py), [tests/integration/weighted_bag.py](../../../../../tests/integration/weighted_bag.py), [docs/weighted_enumeration.md](../../../../weighted_enumeration.md), [include/crown/io/document.hpp](../../../../../include/crown/io/document.hpp) |

## B0004

[Lines 31–38](../../../../../tests/unit/weighted_bag_oracle_driver.cpp#L31); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Json state(runtime::WeightedRuntime& runtime)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Export the weighted runtime cursor state for the bag oracle. |
| inputs / outputs | Consumes a runtime result cursor and returns sequence, rows, total_count, and records_emitted. |
| invariants | Multiplicity and total_count are decimal strings; row scalars are JSON values. Cursor rows are drained to exhaustion. |
| ownership | Returned JSON owns row data; runtime is borrowed and cursor is local. |
| failure | Cursor/storage errors propagate to execute/main. |
| cost | Starts and drains a result cursor, traverses each emitted row field, and builds ordinary JSON rows/count strings; this output work is separate from runtime maintenance. |
| Design | [tests/unit/weighted_bag_oracle_driver.cpp](../../../../../tests/unit/weighted_bag_oracle_driver.cpp), [tests/support/weighted_bag_fixture.hpp](../../../../../tests/support/weighted_bag_fixture.hpp), [tests/reference/weighted_bag_oracle.py](../../../../../tests/reference/weighted_bag_oracle.py), [tests/integration/weighted_bag.py](../../../../../tests/integration/weighted_bag.py), [docs/weighted_enumeration.md](../../../../weighted_enumeration.md), [tests/integration/weighted_bag.py](../../../../../tests/integration/weighted_bag.py) |

## B0005

[Lines 39–66](../../../../../tests/unit/weighted_bag_oracle_driver.cpp#L39); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void execute(const Json& request)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Run one weighted bag request and print fixture shape plus state after each update. |
| inputs / outputs | Parses fixture/backend/limit, exports shape, initial state, then applies each update and emits state/error JSON. |
| invariants | Unknown fixture names become unary. Row parsing is inside the per-update Error catch; counts are decimal strings, while node IDs and records_emitted are JSON numbers. |
| ownership | Request is borrowed; runtime and per-line JSON values are local; stdout receives serialized snapshots. |
| failure | Per-update crown::Error from scalar decoding or apply becomes an error field; std::stoull and outer JSON/request exceptions reach main’s std::exception catch. |
| cost | One fixture setup plus one complete cursor drain for the initial state and after every requested update. |
| Design | [tests/unit/weighted_bag_oracle_driver.cpp](../../../../../tests/unit/weighted_bag_oracle_driver.cpp), [tests/support/weighted_bag_fixture.hpp](../../../../../tests/support/weighted_bag_fixture.hpp), [tests/reference/weighted_bag_oracle.py](../../../../../tests/reference/weighted_bag_oracle.py), [tests/integration/weighted_bag.py](../../../../../tests/integration/weighted_bag.py), [docs/weighted_enumeration.md](../../../../weighted_enumeration.md), [tests/integration/weighted_bag.py](../../../../../tests/integration/weighted_bag.py) |

## B0006

[Lines 67–67](../../../../../tests/unit/weighted_bag_oracle_driver.cpp#L67); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L67-L67:sha256:533f16bca7d58f44b3103b92e3485d22cfbb34bbad5ea3f3fa3b5a9dcb24ec89
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Close the recorded declaration scopes in weighted_bag_oracle_driver.cpp: namespace (anonymous). |
| inputs / outputs | Preceding namespace, type or initializer declarations in; completed lexical boundary out. |
| invariants | Brace-opening context is recorded in root-scope-context-v1.json. These are declaration/initializer boundaries, not an independent update, validation or recovery operation. |
| ownership | Enclosing objects and borrowed fields keep their declared ownership. This punctuation creates no new owner. |
| failure | Malformed scope syntax is a compile error. Any initializer/constructor failure belongs to the enclosing object declaration. |
| cost | No separate loop, guard or engine call is introduced by the delimiter; enclosing initialization and object lifetime still have their actual costs. |
| Design | [tests/unit/weighted_bag_oracle_driver.cpp](../../../../../tests/unit/weighted_bag_oracle_driver.cpp), [docs/weighted_enumeration.md](../../../../weighted_enumeration.md), [docs/code_review.md](../../../../code_review.md) |

## B0007

[Lines 68–72](../../../../../tests/unit/weighted_bag_oracle_driver.cpp#L68); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
int main()
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Process weighted bag JSONL requests. |
| inputs / outputs | Reads each input line and calls execute; writes diagnostics and returns 1 on exception. |
| invariants | Crown Error from per-update row decoding or apply is emitted in that update record; JSON/request errors and other std::exception failures reach the outer process catch. |
| ownership | Line strings and parsed requests are local. |
| failure | Catches std::exception and returns 1. |
| cost | One execute per input line; no request-count or time cap. |
| Design | [tests/unit/weighted_bag_oracle_driver.cpp](../../../../../tests/unit/weighted_bag_oracle_driver.cpp), [tests/support/weighted_bag_fixture.hpp](../../../../../tests/support/weighted_bag_fixture.hpp), [tests/reference/weighted_bag_oracle.py](../../../../../tests/reference/weighted_bag_oracle.py), [tests/integration/weighted_bag.py](../../../../../tests/integration/weighted_bag.py), [docs/weighted_enumeration.md](../../../../weighted_enumeration.md), [tests/integration/weighted_bag.py](../../../../../tests/integration/weighted_bag.py) |
