# `tests/unit/scalar_test.cpp` — block usage map

[Source](../../../../../tests/unit/scalar_test.cpp) · [Source index](../../../README.md) · [Subsystem contracts](../../../subsystem_contracts.md) · [Reviewed primitives](../../../primitives.md)

Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection.

Snapshot SHA-256: `1192091bcf50ed507a5ef5b5dfbf9617fcfe0b426877afd40981066e5d976556`. 172 lines partitioned into 9 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [tests](../../../subsystem_contracts.md#tests). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/code_review.md](../../../../code_review.md), [docs/reference_fuzz.md](../../../../reference_fuzz.md), [docs/task_ledger.md](../../../../task_ledger.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–20](../../../../../tests/unit/scalar_test.cpp#L1) | Imports dependencies; declares namespace scope; declares aliases. |  · [reviewed contract](#b0001) |
| [B0002 · 21–23](../../../../../tests/unit/scalar_test.cpp#L21) | Callable definition: void check(bool condition, const std::string& message) | calls std::runtime_error; guard void check(bool condition, const std::string& message) { · [reviewed contract](#b0002) |
| [B0003 · 24–28](../../../../../tests/unit/scalar_test.cpp#L24) | Callable definition: void rejects(const std::function&lt;void()&gt;& action, const std::string& code) | calls void, action, check, code; guard catch (const Error& error) { check(error.code() == code, "wrong rejection: " + error.code() + ", ex… · [reviewed contract](#b0003) |
| [B0004 · 29–93](../../../../../tests/unit/scalar_test.cpp#L29) | Callable definition: void exact_decimals() | calls Decimal::parse, std::move, check, to_string; guard check(original.to_string() == "-12.34" && original == transferred,; growth emplace, insert; 9 loop sites; source comment (unverified): // An independent bounded rational grid compares scaled int64 numerators, · [reviewed contract](#b0004) |
| [B0005 · 94–115](../../../../../tests/unit/scalar_test.cpp#L94) | Callable definition: void dates_and_hashes() | calls check, to_string, Date::parse, epoch_days; guard check(Date{}.to_string() == "1970-01-01" && Date::parse("1970-01-01").epoch_days() == 0, "date epoc…; 3 loop sites · [reviewed contract](#b0005) |
| [B0006 · 116–124](../../../../../tests/unit/scalar_test.cpp#L116) | Callable definition: Json document_json() | calls Json::parse; returns Json::parse(@ · [reviewed contract](#b0006) |
| [B0007 · 125–158](../../../../../tests/unit/scalar_test.cpp#L125) | Callable definition: void codecs_and_reference() | calls io::read_document, document_json, dump, io::write_document; guard check(io::read_document(canonical).schema_version == 2 && io::write_document(io::read_document(cano…; source comment (unverified): // Structural math is type-agnostic, but its exact certificate binding must · [reviewed contract](#b0007) |
| [B0008 · 159–160](../../../../../tests/unit/scalar_test.cpp#L159) | Closes surrounding scope/type. | source comment (unverified): // namespace · [reviewed contract](#b0008) |
| [B0009 · 161–172](../../../../../tests/unit/scalar_test.cpp#L161) | Callable definition: int main() | calls exact_decimals, dates_and_hashes, codecs_and_reference, what; returns 0; 1 · [reviewed contract](#b0009) |

## B0001

[Lines 1–20](../../../../../tests/unit/scalar_test.cpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L1-L20:sha256:f2e1cc7390f77b5f65f98eb9f792dad3a47147a8b080dfce838f75d2659d2372
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Prepare scalar_test.cpp: include "crown/api/error.hpp", "crown/io/document.hpp", "crown/io/oracle.hpp", "crown/planner/oracle.hpp", "evaluator.hpp", &lt;cstdint&gt;, &lt;functional&gt;, &lt;iostream&gt;, &lt;map&gt;, &lt;set&gt;, &lt;stdexcept&gt;, &lt;string&gt;, &lt;unordered_set&gt;, &lt;utility&gt;, &lt;vector&gt;; bind local aliases/name imports. |
| inputs / outputs | Compiler-visible dependencies, names and the recorded declarations in; declarations available to the following fixture/CLI/example definitions out. |
| invariants | Declarations are scoped to this source/header and its selected ABI. Included code has its own effects; names and editable fixture values do not confer proof, admission or publication authority. |
| ownership | Aliases/includes do not create a query owner. Pointers/references/views are non-owning. Containers own their elements, which can themselves be borrowed pointers or numeric IDs. Only documented owning shared-control handles retain controls; IDs/slot-handle values do not independently keep an arena/runtime alive. |
| failure | Missing headers, ill-formed names/types, failed static assertions or active #error directives stop compilation. No runtime rejection/rollback mechanism is implemented by aliases or function prototypes. |
| cost | Preprocessing and type/constraint instantiation cost compilation. Alias/prototype syntax does not invoke the declared operation; any included definitions keep their own initialization effects. |
| Design | [tests/unit/scalar_test.cpp](../../../../../tests/unit/scalar_test.cpp), [docs/scalars.md](../../../../scalars.md), [docs/code_review.md](../../../../code_review.md) |

## B0002

[Lines 21–23](../../../../../tests/unit/scalar_test.cpp#L21); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void check(bool condition, const std::string& message)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Fails scalar tests when a predicate is false. |
| inputs / outputs | Takes bool and const std::string message reference. |
| invariants | Condition alone controls success; caller can eagerly form message. |
| ownership | Does not retain message. |
| failure | False throws std::runtime_error. |
| cost | One predicate check, no allocation measurement. |
| Design | [tests/unit/scalar_test.cpp](../../../../../tests/unit/scalar_test.cpp) |

## B0003

[Lines 24–28](../../../../../tests/unit/scalar_test.cpp#L24); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void rejects(const std::function<void()>& action, const std::string& code)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Checks an operation rejects with a requested CROWN Error code. |
| inputs / outputs | Accepts a const std::function reference, invokes it, and checks Error.code(). |
| invariants | Other Error codes do not count; non-Crown exceptions are not caught. |
| ownership | Callable and expected code are borrowed. |
| failure | No exception or wrong code raises runtime_error. |
| cost | One invocation per use; no allocation-attempt accounting. |
| Design | [tests/unit/scalar_test.cpp](../../../../../tests/unit/scalar_test.cpp), [include/crown/api/error.hpp](../../../../../include/crown/api/error.hpp) |

## B0004

[Lines 29–93](../../../../../tests/unit/scalar_test.cpp#L29); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void exact_decimals()
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Exercises exact Decimal canonicalization, moves, ordering, hashing, and bounded oracle grids. |
| inputs / outputs | Checks moves/zero forms, 38-digit boundaries, 13 malformed and two overflow spellings, 225 pairwise order comparisons, then a coefficient/scale grid from −250..250 at four scales. |
| invariants | The generated grid has 501×4=2,004 exact rational cases; map/set/hash comparisons cover the local Decimal semantics and do not prove broader decimal arithmetic. |
| ownership | Decimal strings and containers are ordinary scalar/test-owned allocations. |
| failure | Invalid spellings and overflow must reject; any order/hash/oracle mismatch fails. |
| cost | 2,004 grid inputs plus fixed cases and 225 comparisons; no timing/allocator benchmark. |
| Design | [tests/unit/scalar_test.cpp](../../../../../tests/unit/scalar_test.cpp), [src/ir/scalar.cpp](../../../../../src/ir/scalar.cpp), [include/crown/ir/scalar.hpp](../../../../../include/crown/ir/scalar.hpp), [docs/scalars.md](../../../../scalars.md) |

## B0005

[Lines 94–115](../../../../../tests/unit/scalar_test.cpp#L94); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void dates_and_hashes()
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Checks date conversion, typed Value hashing, and row equality for scalar aliases. |
| inputs / outputs | Covers epoch and pre-epoch, six valid and thirteen invalid dates, chrono order, Value hashes/type names, and equal Decimal row aliases in unordered_set. |
| invariants | Hash/equality checks are for provided examples; invalid enum type name is rejected. |
| ownership | Date and scalar values are ordinary owned test objects; strings used for formatting are local. |
| failure | Invalid dates/types and mismatched expectations fail at their checked boundary. |
| cost | Finite date/scalar sample set and one set insertion comparison; no measured performance claim. |
| Design | [tests/unit/scalar_test.cpp](../../../../../tests/unit/scalar_test.cpp), [src/ir/scalar.cpp](../../../../../src/ir/scalar.cpp), [include/crown/ir/scalar.hpp](../../../../../include/crown/ir/scalar.hpp), [docs/scalars.md](../../../../scalars.md) |

## B0006

[Lines 116–124](../../../../../tests/unit/scalar_test.cpp#L116); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Json document_json()
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Builds the fixed document JSON fixture used for codec and reference tests. |
| inputs / outputs | Parses one v2 CROWN document with Decimal/date types, repeated outputs, two initial rows with decimal aliases, and update payloads. |
| invariants | This helper supplies data only; it does not execute or validate the session. |
| ownership | Returned Json owns all parsed nodes and scalar tokens. |
| failure | Malformed embedded fixture JSON would propagate parse failure. |
| cost | One fixed JSON parse and tree allocation. |
| Design | [tests/unit/scalar_test.cpp](../../../../../tests/unit/scalar_test.cpp), [src/io/document.cpp](../../../../../src/io/document.cpp), [docs/scalars.md](../../../../scalars.md) |

## B0007

[Lines 125–158](../../../../../tests/unit/scalar_test.cpp#L125); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void codecs_and_reference()
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Checks scalar document roundtrip and reference witness support. |
| inputs / outputs | Roundtrips the document deterministically, creates a Reference Session with two initial rows, deletes those witnesses in sequence, checks the held old result, rejects invalid version/scalar tokens, and verifies/replays a minimum-tree certificate. |
| invariants | One deletion retains the answer while another witness remains; the final deletion removes it; the held prior epoch remains readable; certificate is tied to typed schema version. |
| ownership | Document and session own rows; held Relation is an ordinary result copy; certificate and decoded program own their values. |
| failure | Codec/type/version errors and answer mismatches fail at the tested boundary. |
| cost | Two sequential delete events and a held-result check, plus document JSON roundtrip, invalid-token/version probes, and certificate verification/replay; reference reevaluation and certificate work are not runtime-account or timing measurements. |
| Design | [tests/unit/scalar_test.cpp](../../../../../tests/unit/scalar_test.cpp), [src/io/document.cpp](../../../../../src/io/document.cpp), [tests/reference/evaluator.hpp](../../../../../tests/reference/evaluator.hpp), [src/ir/scalar.cpp](../../../../../src/ir/scalar.cpp), [docs/scalars.md](../../../../scalars.md) |

## B0008

[Lines 159–160](../../../../../tests/unit/scalar_test.cpp#L159); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L159-L160:sha256:c2bd7638f09d52cb034ed574f539304035fc6fab162bf8d5fa20a35d8c7288a1
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Close the recorded declaration scopes in scalar_test.cpp: namespace (anonymous). |
| inputs / outputs | Preceding namespace, type or initializer declarations in; completed lexical boundary out. |
| invariants | Brace-opening context is recorded in root-scope-context-v1.json. These are declaration/initializer boundaries, not an independent update, validation or recovery operation. |
| ownership | Enclosing objects and borrowed fields keep their declared ownership. This punctuation creates no new owner. |
| failure | Malformed scope syntax is a compile error. Any initializer/constructor failure belongs to the enclosing object declaration. |
| cost | No separate loop, guard or engine call is introduced by the delimiter; enclosing initialization and object lifetime still have their actual costs. |
| Design | [tests/unit/scalar_test.cpp](../../../../../tests/unit/scalar_test.cpp), [docs/scalars.md](../../../../scalars.md), [docs/code_review.md](../../../../code_review.md) |

## B0009

[Lines 161–172](../../../../../tests/unit/scalar_test.cpp#L161); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
int main()
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Runs decimal, date/hash, and codec/reference scalar groups. |
| inputs / outputs | No arguments; invokes three helpers and catches std::exception. |
| invariants | Success output follows completion of all three groups. |
| ownership | Fixture JSON, sessions, and Decimal values die with their helper scopes. |
| failure | Caught exception is printed and returns nonzero. |
| cost | Three finite source-defined groups; no benchmark is reported. |
| Design | [tests/unit/scalar_test.cpp](../../../../../tests/unit/scalar_test.cpp), [docs/scalars.md](../../../../scalars.md) |
