# `tests/unit/weighted_oracle_driver.cpp` — block usage map

[Source](../../../../../tests/unit/weighted_oracle_driver.cpp) · [Source index](../../../README.md) · [Subsystem contracts](../../../subsystem_contracts.md) · [Reviewed primitives](../../../primitives.md)

Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection.

Snapshot SHA-256: `7f2b439820b4a21636f633b0d41e4f59529a4c4f74efe4b763965e59c72068c9`. 65 lines partitioned into 6 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [tests](../../../subsystem_contracts.md#tests). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/code_review.md](../../../../code_review.md), [docs/reference_fuzz.md](../../../../reference_fuzz.md), [docs/task_ledger.md](../../../../task_ledger.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–10](../../../../../tests/unit/weighted_oracle_driver.cpp#L1) | Imports dependencies; declares namespace scope; declares aliases. | source comment (unverified): // Test transport only. All numeric counts are decimal strings so the Python · [reviewed contract](#b0001) |
| [B0002 · 11–15](../../../../../tests/unit/weighted_oracle_driver.cpp#L11) | Callable definition: Json row_json(storage::RowView row) | calls Json::array, size, push_back, io::write_scalar_view; returns result; growth push_back; 1 loop sites · [reviewed contract](#b0002) |
| [B0003 · 16–33](../../../../../tests/unit/weighted_oracle_driver.cpp#L16) | Callable definition: Json state(runtime::WeightedRuntime& runtime) | calls snapshot, Json::array, push_back, std::to_string; returns {{@ ,runtime.sequence()},{@ ,std::to_string(snapshot.root.value)},; growth push_back; 4 loop sites · [reviewed contract](#b0003) |
| [B0004 · 34–59](../../../../../tests/unit/weighted_oracle_driver.cpp#L34) | Callable definition: void execute(const Json& request) | calls at, path, generalized, fanout; growth push_back; 5 loop sites · [reviewed contract](#b0004) |
| [B0005 · 60–60](../../../../../tests/unit/weighted_oracle_driver.cpp#L60) | Closes surrounding scope/type. | source comment (unverified): // namespace · [reviewed contract](#b0005) |
| [B0006 · 61–65](../../../../../tests/unit/weighted_oracle_driver.cpp#L61) | Callable definition: int main() | calls std::getline, execute, io::read_json, what; returns 1; 1 loop sites · [reviewed contract](#b0006) |

## B0001

[Lines 1–10](../../../../../tests/unit/weighted_oracle_driver.cpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L1-L10:sha256:bf694c61d962ac1afc2e46007ff1137d5aee41b153289f269453cc47c1b18088
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Prepare weighted_oracle_driver.cpp: include "weighted_fixture.hpp", "crown/io/document.hpp", &lt;iostream&gt;; bind local aliases/name imports. |
| inputs / outputs | Compiler-visible dependencies, names and the recorded declarations in; declarations available to the following fixture/CLI/example definitions out. |
| invariants | Declarations are scoped to this source/header and its selected ABI. Included code has its own effects; names and editable fixture values do not confer proof, admission or publication authority. |
| ownership | Aliases/includes do not create a query owner. Pointers/references/views are non-owning. Containers own their elements, which can themselves be borrowed pointers or numeric IDs. Only documented owning shared-control handles retain controls; IDs/slot-handle values do not independently keep an arena/runtime alive. |
| failure | Missing headers, ill-formed names/types, failed static assertions or active #error directives stop compilation. No runtime rejection/rollback mechanism is implemented by aliases or function prototypes. |
| cost | Preprocessing and type/constraint instantiation cost compilation. Alias/prototype syntax does not invoke the declared operation; any included definitions keep their own initialization effects. |
| Design | [tests/unit/weighted_oracle_driver.cpp](../../../../../tests/unit/weighted_oracle_driver.cpp), [docs/weighted_messages.md](../../../../weighted_messages.md), [docs/code_review.md](../../../../code_review.md) |

## B0002

[Lines 11–15](../../../../../tests/unit/weighted_oracle_driver.cpp#L11); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Json row_json(storage::RowView row)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Encode a borrowed row view as an ordered JSON array. |
| inputs / outputs | Reads storage::RowView and returns encoded scalar values. |
| invariants | The row order and scalar types are preserved. |
| ownership | The returned JSON owns values; RowView is borrowed. |
| failure | Scalar writer/allocation errors propagate. |
| cost | One pass over row width. |
| Design | [tests/unit/weighted_oracle_driver.cpp](../../../../../tests/unit/weighted_oracle_driver.cpp), [tests/support/weighted_fixture.hpp](../../../../../tests/support/weighted_fixture.hpp), [tests/reference/weighted_oracle.py](../../../../../tests/reference/weighted_oracle.py), [tests/integration/weighted_messages.py](../../../../../tests/integration/weighted_messages.py), [docs/weighted_messages.md](../../../../weighted_messages.md), [include/crown/io/document.hpp](../../../../../include/crown/io/document.hpp) |

## B0003

[Lines 16–33](../../../../../tests/unit/weighted_oracle_driver.cpp#L16); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Json state(runtime::WeightedRuntime& runtime)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Export a weighted runtime snapshot as JSON. |
| inputs / outputs | Reads runtime.snapshot and returns sequence, root count, per-node records, and messages. |
| invariants | Local/subtree/message counts are decimal strings; node IDs and supported-child counts are JSON numbers. RecordValue::children are cached child multiplicities, also decimal strings, not child node IDs. |
| ownership | Snapshot and returned JSON own copies; runtime is borrowed. |
| failure | Snapshot/export allocation errors propagate. |
| cost | Captures an owning runtime snapshot in the query account, then traverses every record tuple, cached child multiplicity, and message key/value while building ordinary JSON. Cost follows retained state and scalar widths, not just emitted row count. |
| Design | [tests/unit/weighted_oracle_driver.cpp](../../../../../tests/unit/weighted_oracle_driver.cpp), [tests/support/weighted_fixture.hpp](../../../../../tests/support/weighted_fixture.hpp), [tests/reference/weighted_oracle.py](../../../../../tests/reference/weighted_oracle.py), [tests/integration/weighted_messages.py](../../../../../tests/integration/weighted_messages.py), [docs/weighted_messages.md](../../../../weighted_messages.md), [tests/integration/weighted_messages.py](../../../../../tests/integration/weighted_messages.py) |

## B0004

[Lines 34–59](../../../../../tests/unit/weighted_oracle_driver.cpp#L34); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void execute(const Json& request)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Parse one weighted message request, apply updates, and emit state. |
| inputs / outputs | Selects path/generalized/fanout or unary shape, sets multiplicity limit, prints shape and one state per update. |
| invariants | Unknown fixture names fall through to the default unary shape. Row/scalar parsing happens before the per-update Error catch; malformed scalar input can escape to main. Count fields use decimal strings but structural IDs are JSON numbers. |
| ownership | Request is borrowed; runtime, rows, JSON descriptions, and snapshots are local. |
| failure | Only apply Errors become per-update error codes; outer std::exception is caught by main. |
| cost | One snapshot per update; fixture work is bounded by supplied update count and runtime state size. |
| Design | [tests/unit/weighted_oracle_driver.cpp](../../../../../tests/unit/weighted_oracle_driver.cpp), [tests/support/weighted_fixture.hpp](../../../../../tests/support/weighted_fixture.hpp), [tests/reference/weighted_oracle.py](../../../../../tests/reference/weighted_oracle.py), [tests/integration/weighted_messages.py](../../../../../tests/integration/weighted_messages.py), [docs/weighted_messages.md](../../../../weighted_messages.md), [tests/integration/weighted_messages.py](../../../../../tests/integration/weighted_messages.py) |

## B0005

[Lines 60–60](../../../../../tests/unit/weighted_oracle_driver.cpp#L60); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L60-L60:sha256:533f16bca7d58f44b3103b92e3485d22cfbb34bbad5ea3f3fa3b5a9dcb24ec89
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Close the recorded declaration scopes in weighted_oracle_driver.cpp: namespace (anonymous). |
| inputs / outputs | Preceding namespace, type or initializer declarations in; completed lexical boundary out. |
| invariants | Brace-opening context is recorded in root-scope-context-v1.json. These are declaration/initializer boundaries, not an independent update, validation or recovery operation. |
| ownership | Enclosing objects and borrowed fields keep their declared ownership. This punctuation creates no new owner. |
| failure | Malformed scope syntax is a compile error. Any initializer/constructor failure belongs to the enclosing object declaration. |
| cost | No separate loop, guard or engine call is introduced by the delimiter; enclosing initialization and object lifetime still have their actual costs. |
| Design | [tests/unit/weighted_oracle_driver.cpp](../../../../../tests/unit/weighted_oracle_driver.cpp), [docs/weighted_messages.md](../../../../weighted_messages.md), [docs/code_review.md](../../../../code_review.md) |

## B0006

[Lines 61–65](../../../../../tests/unit/weighted_oracle_driver.cpp#L61); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
int main()
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Process weighted message JSONL requests. |
| inputs / outputs | Reads each line, executes it, writes diagnostics on exception, and returns 1 when caught. |
| invariants | Malformed request/scalar errors are process-level failures; no per-line continuation is promised after an exception. |
| ownership | Line and parsed request are local. |
| failure | Catches std::exception and returns 1. |
| cost | One execute per input line; no request-count or time cap. |
| Design | [tests/unit/weighted_oracle_driver.cpp](../../../../../tests/unit/weighted_oracle_driver.cpp), [tests/support/weighted_fixture.hpp](../../../../../tests/support/weighted_fixture.hpp), [tests/reference/weighted_oracle.py](../../../../../tests/reference/weighted_oracle.py), [tests/integration/weighted_messages.py](../../../../../tests/integration/weighted_messages.py), [docs/weighted_messages.md](../../../../weighted_messages.md), [tests/integration/weighted_messages.py](../../../../../tests/integration/weighted_messages.py) |
