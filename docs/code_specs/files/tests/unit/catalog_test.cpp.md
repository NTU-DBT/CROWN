# `tests/unit/catalog_test.cpp` — block usage map

[Source](../../../../../tests/unit/catalog_test.cpp) · [Source index](../../../README.md) · [Subsystem contracts](../../../subsystem_contracts.md) · [Reviewed primitives](../../../primitives.md)

Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection.

Snapshot SHA-256: `c38cc198678c340fc0a9c8c6d93fed2e48f04b12fa1fe9d9aa063af4f6d7ba1d`. 210 lines partitioned into 11 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [tests](../../../subsystem_contracts.md#tests). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/code_review.md](../../../../code_review.md), [docs/reference_fuzz.md](../../../../reference_fuzz.md), [docs/task_ledger.md](../../../../task_ledger.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–17](../../../../../tests/unit/catalog_test.cpp#L1) | Imports dependencies; declares namespace scope; declares aliases. |  · [reviewed contract](#b0001) |
| [B0002 · 18–20](../../../../../tests/unit/catalog_test.cpp#L18) | Callable definition: void check(bool condition, const std::string& message) | calls std::runtime_error; guard void check(bool condition, const std::string& message) { · [reviewed contract](#b0002) |
| [B0003 · 21–29](../../../../../tests/unit/catalog_test.cpp#L21) | Callable definition: void rejects(const std::function&lt;void()&gt;& action, const std::string& code, const std::string& detail = "") | calls void, action, check, code; guard check(error.code() == code, "wrong rejection: " + error.code() + ", expected " + code + ": " + erro… · [reviewed contract](#b0003) |
| [B0004 · 30–30](../../../../../tests/unit/catalog_test.cpp#L30) | Callable definition: Value integer(std::int64_t value) | calls ; returns Value{value} · [reviewed contract](#b0004) |
| [B0005 · 31–43](../../../../../tests/unit/catalog_test.cpp#L31) | Callable definition: Json input() | calls Json::parse; returns Json::parse(@ · [reviewed contract](#b0005) |
| [B0006 · 44–82](../../../../../tests/unit/catalog_test.cpp#L44) | Callable definition: void constraints_and_atomicity() | calls io::read_document, input, dump, session; guard check(session.sequence() == 0 && session.database().tables == before && session.snapshot() == befor…; growth insert, push_back; 2 loop sites · [reviewed contract](#b0006) |
| [B0007 · 83–106](../../../../../tests/unit/catalog_test.cpp#L83) | Callable definition: void self_reference_and_empty_keys() | calls emplace_back, push_back, session, apply; guard check(insertion.current == Relation{{integer(1)}}, "self-referencing row is checked against one ato…; growth emplace_back, insert, push_back · [reviewed contract](#b0007) |
| [B0008 · 107–169](../../../../../tests/unit/catalog_test.cpp#L107) | Callable definition: void types_names_and_metadata() | calls catalog::require_identity_cast, rejects, check, catalog::decimal_fits; guard check(catalog::decimal_fits(Decimal::parse("99.99"), *fixed.decimal), "fixed-scale precision bounda…; growth insert; 6 loop sites · [reviewed contract](#b0008) |
| [B0009 · 170–196](../../../../../tests/unit/catalog_test.cpp#L170) | Callable definition: void codecs_and_binding() | calls io::read_document, input, dump, io::write_document; guard check(encoded.at("schema_version") == 3 && io::write_document(io::read_document(encoded.dump())).du… · [reviewed contract](#b0009) |
| [B0010 · 197–197](../../../../../tests/unit/catalog_test.cpp#L197) | Closes surrounding scope/type. | source comment (unverified): // namespace · [reviewed contract](#b0010) |
| [B0011 · 198–210](../../../../../tests/unit/catalog_test.cpp#L198) | Callable definition: int main() | calls constraints_and_atomicity, self_reference_and_empty_keys, types_names_and_metadata, codecs_and_binding; returns 0; 1 · [reviewed contract](#b0011) |

## B0001

[Lines 1–17](../../../../../tests/unit/catalog_test.cpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L1-L17:sha256:4eda9a7b78f8e2644952d0b221df6a1617ee0a20d3042f12f609627e591f5f68
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Prepare catalog_test.cpp: include "crown/catalog/catalog.hpp", "crown/api/error.hpp", "crown/io/catalog.hpp", "crown/io/oracle.hpp", "crown/planner/oracle.hpp", "evaluator.hpp", &lt;functional&gt;, &lt;array&gt;, &lt;iostream&gt;, &lt;limits&gt;, &lt;stdexcept&gt;, &lt;string&gt;; bind local aliases/name imports. |
| inputs / outputs | Compiler-visible dependencies, names and the recorded declarations in; declarations available to the following fixture/CLI/example definitions out. |
| invariants | Declarations are scoped to this source/header and its selected ABI. Included code has its own effects; names and editable fixture values do not confer proof, admission or publication authority. |
| ownership | Aliases/includes do not create a query owner. Pointers/references/views are non-owning. Containers own their elements, which can themselves be borrowed pointers or numeric IDs. Only documented owning shared-control handles retain controls; IDs/slot-handle values do not independently keep an arena/runtime alive. |
| failure | Missing headers, ill-formed names/types, failed static assertions or active #error directives stop compilation. No runtime rejection/rollback mechanism is implemented by aliases or function prototypes. |
| cost | Preprocessing and type/constraint instantiation cost compilation. Alias/prototype syntax does not invoke the declared operation; any included definitions keep their own initialization effects. |
| Design | [tests/unit/catalog_test.cpp](../../../../../tests/unit/catalog_test.cpp), [docs/catalog.md](../../../../catalog.md), [docs/code_review.md](../../../../code_review.md) |

## B0002

[Lines 18–20](../../../../../tests/unit/catalog_test.cpp#L18); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void check(bool condition, const std::string& message)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Raises a catalog-test failure when a predicate is false. |
| inputs / outputs | Takes condition and message by reference; returns void on success. |
| invariants | Assertion messages passed as expressions may be built before the call. |
| ownership | Does not retain the message. |
| failure | False throws std::runtime_error. |
| cost | Branch-only helper with no attempt counter. |
| Design | [tests/unit/catalog_test.cpp](../../../../../tests/unit/catalog_test.cpp) |

## B0003

[Lines 21–29](../../../../../tests/unit/catalog_test.cpp#L21); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void rejects(const std::function<void()>& action, const std::string& code, const std::string& detail = "")
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Asserts a callable throws the requested CROWN Error code and optional detail substring. |
| inputs / outputs | Receives const std::function reference, code, and optional detail; invokes the referred action. |
| invariants | It accepts any exception with matching Error code and, when nonempty, matching detail substring. |
| ownership | The callable and strings are borrowed for the call; the function does not store them. |
| failure | No throw or mismatch raises std::runtime_error; non-Crown exceptions propagate. |
| cost | One action invocation and diagnostic substring check; no allocation count is taken. |
| Design | [tests/unit/catalog_test.cpp](../../../../../tests/unit/catalog_test.cpp), [include/crown/api/error.hpp](../../../../../include/crown/api/error.hpp) |

## B0004

[Lines 30–30](../../../../../tests/unit/catalog_test.cpp#L30); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Value integer(std::int64_t value)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Constructs integer Values for catalog rows and constants. |
| inputs / outputs | Accepts int64 and returns Value. |
| invariants | Integer values remain exact at the Value representation boundary. |
| ownership | Returned scalar owns its value; no catalog is retained. |
| failure | Value construction failures propagate. |
| cost | One scalar construction. |
| Design | [tests/unit/catalog_test.cpp](../../../../../tests/unit/catalog_test.cpp), [include/crown/ir/scalar.hpp](../../../../../include/crown/ir/scalar.hpp) |

## B0005

[Lines 31–43](../../../../../tests/unit/catalog_test.cpp#L31); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Json input()
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Parses the initial catalog/document JSON fixture used by catalog mutation checks. |
| inputs / outputs | Returns a Json object for a v3 document with catalog version 9, enforced unique and FK constraints, a parent row, and two child rows. |
| invariants | The input is intentionally valid before each mutation case. |
| ownership | Json owns its parsed tree and row values. |
| failure | JSON parsing errors propagate rather than becoming expected constraint errors. |
| cost | One fixed JSON parse and owning tree; fixture storage is ordinary. |
| Design | [tests/unit/catalog_test.cpp](../../../../../tests/unit/catalog_test.cpp), [src/io/document.cpp](../../../../../src/io/document.cpp), [docs/catalog.md](../../../../catalog.md) |

## B0006

[Lines 44–82](../../../../../tests/unit/catalog_test.cpp#L44); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void constraints_and_atomicity()
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Exercises constrained updates, atomic failure, and witness-sensitive reference answers. |
| inputs / outputs | Reads the fixture, applies illegal parent-delete/duplicate-key/missing-FK cases, then valid no-op and child/parent deletions; also relaxes trust metadata before inserting rows. |
| invariants | Rejected operations preserve sequence/database/snapshot; exact duplicate insert is no-op; one of two child witnesses preserves the projection and the last removes it; untrusted hints do not remove mutable atoms from reference evaluation. |
| ownership | Session owns its database and current snapshot; saved result rows are copied relation values. |
| failure | Expected update failures are checked by code; post-failure sequence/database/snapshot equality is asserted. |
| cost | Three rejected update attempts and four committed events (duplicate insert, two child deletes, parent delete), plus two invalid-document reads and one untrusted-metadata snapshot; reference reevaluation and snapshot copies are not CPU or query-account measurements. |
| Design | [tests/unit/catalog_test.cpp](../../../../../tests/unit/catalog_test.cpp), [tests/reference/evaluator.hpp](../../../../../tests/reference/evaluator.hpp), [src/catalog/catalog.cpp](../../../../../src/catalog/catalog.cpp), [src/io/document.cpp](../../../../../src/io/document.cpp), [docs/catalog.md](../../../../catalog.md) |

## B0007

[Lines 83–106](../../../../../tests/unit/catalog_test.cpp#L83); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void self_reference_and_empty_keys()
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Covers self-referencing foreign keys and empty-column constraint edge cases. |
| inputs / outputs | Applies self-reference inserts/deletes, then checks zero-column unique and foreign-key cases against reference sessions. |
| invariants | Constraint validation is against the proposed after-state; an empty unique key permits at most one row, while an empty FK requires a target only when a source row exists. |
| ownership | reference::Session owns its Catalog, Query, and Database values. This helper has no Json fixture; the returned epoch and Relation values own their row data. |
| failure | Each invalid after-state must throw the expected code; wrong acceptance or rejection fails. |
| cost | Small explicit event and constraint cases; no generalized database scale claim. |
| Design | [tests/unit/catalog_test.cpp](../../../../../tests/unit/catalog_test.cpp), [src/catalog/catalog.cpp](../../../../../src/catalog/catalog.cpp), [src/io/document.cpp](../../../../../src/io/document.cpp), [docs/catalog.md](../../../../catalog.md) |

## B0008

[Lines 107–169](../../../../../tests/unit/catalog_test.cpp#L107); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void types_names_and_metadata()
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Checks scalar compatibility, decimal fit, row validation, and catalog name resolution. |
| inputs / outputs | Runs a 5×5 scalar identity-cast matrix, fixed decimal boundary cases, a bounded coefficient/scale/precision grid, and finite schema/name/nullability probes. |
| invariants | Independent formula comparison covers coefficients −200..200, input scales 0..3, precision 1..6 and scale 0..precision; nullable source and unsupported collation/type cases are tested separately. |
| ownership | Catalogs, Rows, Decimals, and Values are ordinary owning test fixtures. |
| failure | Expected type/decimal/name errors are asserted; grid mismatches throw test failures. |
| cost | 43,308 generated fit comparisons (401 coefficients × 4 input scales × 27 precision/scale pairs), plus 25 source/target type-pair checks and explicit cases; not a timing or allocator measurement. |
| Design | [tests/unit/catalog_test.cpp](../../../../../tests/unit/catalog_test.cpp), [src/catalog/catalog.cpp](../../../../../src/catalog/catalog.cpp), [src/ir/scalar.cpp](../../../../../src/ir/scalar.cpp), [docs/catalog.md](../../../../catalog.md), [docs/scalars.md](../../../../scalars.md) |

## B0009

[Lines 170–196](../../../../../tests/unit/catalog_test.cpp#L170); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void codecs_and_binding()
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Checks catalog/document codecs and certificate binding to schema version. |
| inputs / outputs | Roundtrips v3 documents and standalone catalogs, rejects old writes/duplicate or malformed fields, and verifies/read-replays a minimum-tree certificate. |
| invariants | Deterministic encoding and decimal precision are preserved; enforced FK targets are validated; changing source_schema_version invalidates certificate binding. |
| ownership | Json, Catalog, and certificate values own their decoded contents. |
| failure | Malformed/version/constraint errors are expected at the asserted reader/writer boundary; certificate mismatches are rejected. |
| cost | Finite codec and replay cases with JSON serialization/parsing; no runtime storage constructed. |
| Design | [tests/unit/catalog_test.cpp](../../../../../tests/unit/catalog_test.cpp), [src/io/catalog.cpp](../../../../../src/io/catalog.cpp), [src/io/document.cpp](../../../../../src/io/document.cpp), [include/crown/io/tree.hpp](../../../../../include/crown/io/tree.hpp), [docs/catalog.md](../../../../catalog.md) |

## B0010

[Lines 197–197](../../../../../tests/unit/catalog_test.cpp#L197); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L197-L197:sha256:c7bfe2f3de133d78a2bc8bb1c4a08450563986ee8254facee698e1dcc57e8162
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Close the recorded declaration scopes in catalog_test.cpp: namespace (anonymous). |
| inputs / outputs | Preceding namespace, type or initializer declarations in; completed lexical boundary out. |
| invariants | Brace-opening context is recorded in root-scope-context-v1.json. These are declaration/initializer boundaries, not an independent update, validation or recovery operation. |
| ownership | Enclosing objects and borrowed fields keep their declared ownership. This punctuation creates no new owner. |
| failure | Malformed scope syntax is a compile error. Any initializer/constructor failure belongs to the enclosing object declaration. |
| cost | No separate loop, guard or engine call is introduced by the delimiter; enclosing initialization and object lifetime still have their actual costs. |
| Design | [tests/unit/catalog_test.cpp](../../../../../tests/unit/catalog_test.cpp), [docs/catalog.md](../../../../catalog.md), [docs/code_review.md](../../../../code_review.md) |

## B0011

[Lines 198–210](../../../../../tests/unit/catalog_test.cpp#L198); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
int main()
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Runs the four catalog groups from main. |
| inputs / outputs | No arguments; invokes constraint/atomicity, self-reference/empty keys, types/names/metadata, and codec/binding groups. |
| invariants | Success is printed only after all four return; std::exception is caught. |
| ownership | Each helper releases its local Json, catalog, and sessions at return. |
| failure | Caught exception prints a diagnostic and returns nonzero. |
| cost | Four finite fixture groups; this entry point makes no performance claim. |
| Design | [tests/unit/catalog_test.cpp](../../../../../tests/unit/catalog_test.cpp), [docs/catalog.md](../../../../catalog.md) |
