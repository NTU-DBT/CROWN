# `tests/unit/semantics_test.cpp` — block usage map

[Source](../../../../../tests/unit/semantics_test.cpp) · [Source index](../../../README.md) · [Subsystem contracts](../../../subsystem_contracts.md) · [Reviewed primitives](../../../primitives.md)

Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection.

Snapshot SHA-256: `5babed56ad0d9fdace89ec8fd44de259d6f8c8f032b5053e28f409ea86807a41`. 148 lines partitioned into 11 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [tests](../../../subsystem_contracts.md#tests). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/code_review.md](../../../../code_review.md), [docs/reference_fuzz.md](../../../../reference_fuzz.md), [docs/task_ledger.md](../../../../task_ledger.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–15](../../../../../tests/unit/semantics_test.cpp#L1) | Imports dependencies; declares namespace scope; declares aliases. |  · [reviewed contract](#b0001) |
| [B0002 · 16–18](../../../../../tests/unit/semantics_test.cpp#L16) | Callable definition: void check(bool condition, const std::string& message) | calls std::runtime_error; guard void check(bool condition, const std::string& message) { · [reviewed contract](#b0002) |
| [B0003 · 19–23](../../../../../tests/unit/semantics_test.cpp#L19) | Callable definition: void rejects(const std::function&lt;void()&gt;& action, const std::string& code) | calls void, action, check, code; guard catch (const Error& error) { check(error.code() == code, "wrong rejection: " + error.code() + " exp… · [reviewed contract](#b0003) |
| [B0004 · 24–24](../../../../../tests/unit/semantics_test.cpp#L24) | Callable definition: Value integer(std::int64_t value) | calls ; returns Value{value} · [reviewed contract](#b0004) |
| [B0005 · 25–32](../../../../../tests/unit/semantics_test.cpp#L25) | Callable definition: Json input() | calls Json::parse; returns Json::parse(@ · [reviewed contract](#b0005) |
| [B0006 · 33–53](../../../../../tests/unit/semantics_test.cpp#L33) | Callable definition: void atomicity_and_ownership() | calls io::read_document, input, dump, session; guard check(first.current == answer && first.delta.added == answer && first.delta.removed.empty(), "first…; growth insert · [reviewed contract](#b0006) |
| [B0007 · 54–84](../../../../../tests/unit/semantics_test.cpp#L54) | Callable definition: void exact_values_and_roundtrip() | calls input, Json::array, max, min; guard check(io::write_document(copy).dump() == canonical, "canonicalization is idempotent");; growth insert, push_back · [reviewed contract](#b0007) |
| [B0008 · 85–109](../../../../../tests/unit/semantics_test.cpp#L85) | Callable definition: void empty_and_wide_queries() | calls check, reference::evaluate, empty, std::to_string; guard check(reference::evaluate(catalog, query, database) == Relation{Row{}}, "empty body is one nullary …; growth emplace_back, push_back; 1 loop sites · [reviewed contract](#b0008) |
| [B0009 · 110–133](../../../../../tests/unit/semantics_test.cpp#L110) | Callable definition: void schema_rejections() | calls input, rejects, io::read_document, dump; growth push_back · [reviewed contract](#b0009) |
| [B0010 · 134–135](../../../../../tests/unit/semantics_test.cpp#L134) | Closes surrounding scope/type. | source comment (unverified): // namespace · [reviewed contract](#b0010) |
| [B0011 · 136–148](../../../../../tests/unit/semantics_test.cpp#L136) | Callable definition: int main() | calls atomicity_and_ownership, exact_values_and_roundtrip, empty_and_wide_queries, schema_rejections; returns 0; 1 · [reviewed contract](#b0011) |

## B0001

[Lines 1–15](../../../../../tests/unit/semantics_test.cpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L1-L15:sha256:b1c2ee3ba829a0e113097dcb77a6391bd3767e8669311b3aabde7dea8b305b10
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Prepare semantics_test.cpp: include "crown/api/error.hpp", "crown/io/document.hpp", "evaluator.hpp", &lt;cstdint&gt;, &lt;functional&gt;, &lt;iostream&gt;, &lt;limits&gt;, &lt;stdexcept&gt;, &lt;string&gt;, &lt;utility&gt;; bind local aliases/name imports. |
| inputs / outputs | Compiler-visible dependencies, names and the recorded declarations in; declarations available to the following fixture/CLI/example definitions out. |
| invariants | Declarations are scoped to this source/header and its selected ABI. Included code has its own effects; names and editable fixture values do not confer proof, admission or publication authority. |
| ownership | Aliases/includes do not create a query owner. Pointers/references/views are non-owning. Containers own their elements, which can themselves be borrowed pointers or numeric IDs. Only documented owning shared-control handles retain controls; IDs/slot-handle values do not independently keep an arena/runtime alive. |
| failure | Missing headers, ill-formed names/types, failed static assertions or active #error directives stop compilation. No runtime rejection/rollback mechanism is implemented by aliases or function prototypes. |
| cost | Preprocessing and type/constraint instantiation cost compilation. Alias/prototype syntax does not invoke the declared operation; any included definitions keep their own initialization effects. |
| Design | [tests/unit/semantics_test.cpp](../../../../../tests/unit/semantics_test.cpp), [docs/schema_evolution.md](../../../../schema_evolution.md), [docs/code_review.md](../../../../code_review.md) |

## B0002

[Lines 16–18](../../../../../tests/unit/semantics_test.cpp#L16); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void check(bool condition, const std::string& message)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Raises a semantic-test exception when a predicate is false. |
| inputs / outputs | Accepts bool and const message reference. |
| invariants | Message expressions may already be constructed before entry. |
| ownership | No message retention. |
| failure | False throws std::runtime_error. |
| cost | One branch only. |
| Design | [tests/unit/semantics_test.cpp](../../../../../tests/unit/semantics_test.cpp) |

## B0003

[Lines 19–23](../../../../../tests/unit/semantics_test.cpp#L19); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void rejects(const std::function<void()>& action, const std::string& code)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Asserts that a callable rejects with a particular CROWN Error code. |
| inputs / outputs | Receives a const std::function reference, invokes it, and compares Error.code(). |
| invariants | Matching code is required; other Error codes and success fail the helper. |
| ownership | Callable/code are borrowed for the invocation. |
| failure | No expected Error or mismatch throws runtime_error; other exception types propagate. |
| cost | One call per probe; no allocation attempt count. |
| Design | [tests/unit/semantics_test.cpp](../../../../../tests/unit/semantics_test.cpp), [include/crown/api/error.hpp](../../../../../include/crown/api/error.hpp) |

## B0004

[Lines 24–24](../../../../../tests/unit/semantics_test.cpp#L24); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Value integer(std::int64_t value)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Builds an integer Value for document and row fixtures. |
| inputs / outputs | Accepts int64 and returns Value. |
| invariants | Preserves the exact signed integer value. |
| ownership | Caller owns returned scalar. |
| failure | Construction errors propagate. |
| cost | One scalar creation. |
| Design | [tests/unit/semantics_test.cpp](../../../../../tests/unit/semantics_test.cpp), [include/crown/ir/scalar.hpp](../../../../../include/crown/ir/scalar.hpp) |

## B0005

[Lines 25–32](../../../../../tests/unit/semantics_test.cpp#L25); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Json input()
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Parses the one-row input document fixture. |
| inputs / outputs | Returns Json for a schema-v1 CROWN document with catalog, query, and initial row. |
| invariants | The fixture is valid before each test mutates it. |
| ownership | Json owns the parsed document tree. |
| failure | Invalid embedded JSON would propagate parse failure. |
| cost | One fixed JSON parse. |
| Design | [tests/unit/semantics_test.cpp](../../../../../tests/unit/semantics_test.cpp), [src/io/document.cpp](../../../../../src/io/document.cpp) |

## B0006

[Lines 33–53](../../../../../tests/unit/semantics_test.cpp#L33); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void atomicity_and_ownership()
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Checks reference-session atomicity, duplicate events, and retained old results. |
| inputs / outputs | Inserts two witnesses, tests rejected sequence/type/op updates, repeats an insert, deletes one then the last witness, and commits an absent erase. |
| invariants | Rejected update leaves sequence/database/snapshot at the prior committed state; duplicate insertion and absent erase are no-op events; one remaining witness preserves the answer and final removal retracts it. |
| ownership | Reference Session owns mutable database/current state; previously returned Relation is an independent held snapshot. |
| failure | Expected update diagnostics are checked; post-error current state and earlier result readability are asserted. |
| cost | Six committed sequence positions include the duplicate insert and absent-delete no-ops; three rejected update attempts are also checked. The tiny reference query is reevaluated and materializes Relation snapshots; no runtime account or CPU measurement is present. |
| Design | [tests/unit/semantics_test.cpp](../../../../../tests/unit/semantics_test.cpp), [tests/reference/evaluator.hpp](../../../../../tests/reference/evaluator.hpp), [src/io/document.cpp](../../../../../src/io/document.cpp) |

## B0007

[Lines 54–84](../../../../../tests/unit/semantics_test.cpp#L54); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void exact_values_and_roundtrip()
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Checks exact integer and duplicate-output preservation through document codecs. |
| inputs / outputs | Roundtrips min/max int64 and 2^53+1 with repeated outputs, validates update encoding errors, and checks NUL/Unicode strings and booleans. |
| invariants | Exact integer values and duplicate output positions survive; malformed sequence/op payloads reject. |
| ownership | Json and decoded Document own scalar strings and rows. |
| failure | Writer/reader errors and any changed value/position fail assertions. |
| cost | Finite scalar/document fixtures and one codec roundtrip; ordinary JSON allocations are not measured. |
| Design | [tests/unit/semantics_test.cpp](../../../../../tests/unit/semantics_test.cpp), [src/io/document.cpp](../../../../../src/io/document.cpp), [src/ir/scalar.cpp](../../../../../src/ir/scalar.cpp) |

## B0008

[Lines 85–109](../../../../../tests/unit/semantics_test.cpp#L85); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void empty_and_wide_queries()
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Checks nullary query results, contradiction, and a dynamically wide row. |
| inputs / outputs | Evaluates empty-body query to one nullary tuple, contradiction to empty, and a 70-variable row/query against the same reference database. |
| invariants | Empty conjunction and contradictory atom cases differ; dynamic width has no assumed 64-variable bound in this test. |
| ownership | Reference result Relation and generated wide row are owning test values. |
| failure | Unexpected row count/value fails. |
| cost | One small query pair plus one 70-field fixture evaluation; no width-scaling claim. |
| Design | [tests/unit/semantics_test.cpp](../../../../../tests/unit/semantics_test.cpp), [tests/reference/evaluator.cpp](../../../../../tests/reference/evaluator.cpp), [src/io/document.cpp](../../../../../src/io/document.cpp) |

## B0009

[Lines 110–133](../../../../../tests/unit/semantics_test.cpp#L110); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void schema_rejections()
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Checks document/schema reader rejection cases across versions and scalar/update syntax. |
| inputs / outputs | Mutates a valid input into a fixed list of malformed versions, fields, schema/term/value/update forms, duplicate keys, malformed JSON, and non-object root. |
| invariants | Each case is expected to reject at document decode; cases include type/domain and update sequence checks but do not prove exhaustive invalid-input coverage. |
| ownership | Each mutated Json is a local owning copy; malformed raw JSON is a string fixture. |
| failure | The error helper requires the specified code for every listed rejection; unexpected acceptance or wrong code fails. |
| cost | Eighteen explicit rejected documents/text inputs covering version, schema, scalar, update, duplicate-key, JSON-shape, and parse errors; each rebuilds/decodes ordinary Json/string values, with no CPU or allocation metric. |
| Design | [tests/unit/semantics_test.cpp](../../../../../tests/unit/semantics_test.cpp), [src/io/document.cpp](../../../../../src/io/document.cpp), [docs/schema_evolution.md](../../../../schema_evolution.md) |

## B0010

[Lines 134–135](../../../../../tests/unit/semantics_test.cpp#L134); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L134-L135:sha256:c2bd7638f09d52cb034ed574f539304035fc6fab162bf8d5fa20a35d8c7288a1
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Close the recorded declaration scopes in semantics_test.cpp: namespace (anonymous). |
| inputs / outputs | Preceding namespace, type or initializer declarations in; completed lexical boundary out. |
| invariants | Brace-opening context is recorded in root-scope-context-v1.json. These are declaration/initializer boundaries, not an independent update, validation or recovery operation. |
| ownership | Enclosing objects and borrowed fields keep their declared ownership. This punctuation creates no new owner. |
| failure | Malformed scope syntax is a compile error. Any initializer/constructor failure belongs to the enclosing object declaration. |
| cost | No separate loop, guard or engine call is introduced by the delimiter; enclosing initialization and object lifetime still have their actual costs. |
| Design | [tests/unit/semantics_test.cpp](../../../../../tests/unit/semantics_test.cpp), [docs/schema_evolution.md](../../../../schema_evolution.md), [docs/code_review.md](../../../../code_review.md) |

## B0011

[Lines 136–148](../../../../../tests/unit/semantics_test.cpp#L136); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
int main()
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Runs the four document-semantics groups from main. |
| inputs / outputs | No arguments; invokes atomicity/ownership, exact values/roundtrip, empty/wide queries, and schema rejections. |
| invariants | Success output follows all four helpers; std::exception is caught. |
| ownership | Each helper scopes its document/session/result values locally. |
| failure | Caught exception is printed and returns nonzero. |
| cost | Four finite test groups; entry point reports no performance measure. |
| Design | [tests/unit/semantics_test.cpp](../../../../../tests/unit/semantics_test.cpp), [src/io/document.cpp](../../../../../src/io/document.cpp) |
