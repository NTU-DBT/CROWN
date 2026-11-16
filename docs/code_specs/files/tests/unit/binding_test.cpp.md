# `tests/unit/binding_test.cpp` — block usage map

[Source](../../../../../tests/unit/binding_test.cpp) · [Source index](../../../README.md) · [Subsystem contracts](../../../subsystem_contracts.md) · [Reviewed primitives](../../../primitives.md)

Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection.

Snapshot SHA-256: `02ddfcd26f886f1dd5a466696c3916c63d4bf08550a2a59b0da5cae99cd598aa`. 166 lines partitioned into 11 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [tests](../../../subsystem_contracts.md#tests). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/code_review.md](../../../../code_review.md), [docs/reference_fuzz.md](../../../../reference_fuzz.md), [docs/task_ledger.md](../../../../task_ledger.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–13](../../../../../tests/unit/binding_test.cpp#L1) | Imports dependencies; declares namespace scope; declares aliases. |  · [reviewed contract](#b0001) |
| [B0002 · 14–16](../../../../../tests/unit/binding_test.cpp#L14) | Callable definition: void check(bool condition, const std::string& message) | calls std::runtime_error; guard void check(bool condition, const std::string& message) { · [reviewed contract](#b0002) |
| [B0003 · 17–21](../../../../../tests/unit/binding_test.cpp#L17) | Callable definition: const BoundSql& bound(const SqlBindResult& result) | calls std::runtime_error; returns *value · [reviewed contract](#b0003) |
| [B0004 · 22–27](../../../../../tests/unit/binding_test.cpp#L22) | Callable definition: const BindingDiagnostic& rejected(const SqlBindResult& result, std::string_view code) | calls check, std::string; guard check(std::holds_alternative&lt;BindingDiagnostic&gt;(result), "expected binding rejection " + std::strin…; returns error · [reviewed contract](#b0004) |
| [B0005 · 28–35](../../../../../tests/unit/binding_test.cpp#L28) | Callable definition: Catalog catalog() | calls ; returns {1,{ · [reviewed contract](#b0005) |
| [B0006 · 36–40](../../../../../tests/unit/binding_test.cpp#L36) | Callable definition: std::vector&lt;std::string&gt; names(const BoundSql& query) | calls push_back; returns result; growth push_back; 1 loop sites · [reviewed contract](#b0006) |
| [B0007 · 41–86](../../../../../tests/unit/binding_test.cpp#L41) | Callable definition: void join_scopes_and_outputs() | calls catalog, bind_sql, bound, check; guard check(names(query) == std::vector&lt;std::string&gt;{"key","a","b","c","a","b","key","key","c","a","again… · [reviewed contract](#b0007) |
| [B0008 · 87–122](../../../../../tests/unit/binding_test.cpp#L87) | Callable definition: void types_parameters_and_wrappers() | calls catalog, bind_sql, check, bound; guard check(bound(ordinary).semantics == SqlSemantics::bag, "plain SELECT does not become DISTINCT");; returns operation && operation-&gt;operation == SqlOperator::widen_integer; 1 loop sites · [reviewed contract](#b0008) |
| [B0009 · 123–153](../../../../../tests/unit/binding_test.cpp#L123) | Callable definition: void locations_ownership_and_limits() | calls bind_sql, rejected, find, check; guard check(error.byte_offset == offset && error.character_position == offset - 1 && error.line == 2 && e…; growth push_back; 1 loop sites · [reviewed contract](#b0009) |
| [B0010 · 154–154](../../../../../tests/unit/binding_test.cpp#L154) | Closes surrounding scope/type. | source comment (unverified): // namespace · [reviewed contract](#b0010) |
| [B0011 · 155–166](../../../../../tests/unit/binding_test.cpp#L155) | Callable definition: int main() | calls join_scopes_and_outputs, types_parameters_and_wrappers, locations_ownership_and_limits, what; returns 0; 1 · [reviewed contract](#b0011) |

## B0001

[Lines 1–13](../../../../../tests/unit/binding_test.cpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L1-L13:sha256:a6d1038906d699c211a3af8727dffb4e381e7a16ec0a1345662f4b22faa62fab
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Prepare binding_test.cpp: include "crown/frontend/bind.hpp", "crown/api/error.hpp", "crown/io/binding.hpp", "crown/io/catalog.hpp", &lt;algorithm&gt;, &lt;iostream&gt;, &lt;stdexcept&gt;, &lt;string_view&gt;; bind local aliases/name imports. |
| inputs / outputs | Compiler-visible dependencies, names and the recorded declarations in; declarations available to the following fixture/CLI/example definitions out. |
| invariants | Declarations are scoped to this source/header and its selected ABI. Included code has its own effects; names and editable fixture values do not confer proof, admission or publication authority. |
| ownership | Aliases/includes do not create a query owner. Pointers/references/views are non-owning. Containers own their elements, which can themselves be borrowed pointers or numeric IDs. Only documented owning shared-control handles retain controls; IDs/slot-handle values do not independently keep an arena/runtime alive. |
| failure | Missing headers, ill-formed names/types, failed static assertions or active #error directives stop compilation. No runtime rejection/rollback mechanism is implemented by aliases or function prototypes. |
| cost | Preprocessing and type/constraint instantiation cost compilation. Alias/prototype syntax does not invoke the declared operation; any included definitions keep their own initialization effects. |
| Design | [tests/unit/binding_test.cpp](../../../../../tests/unit/binding_test.cpp), [docs/sql_binding.md](../../../../sql_binding.md), [docs/code_review.md](../../../../code_review.md) |

## B0002

[Lines 14–16](../../../../../tests/unit/binding_test.cpp#L14); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void check(bool condition, const std::string& message)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Converts a false binder-test predicate into a test exception. |
| inputs / outputs | Accepts a bool and const message reference; no return value. |
| invariants | True predicates do not inspect or copy the message in this function; argument expressions may already have allocated. |
| ownership | Message is borrowed only for the call. |
| failure | False throws std::runtime_error. |
| cost | One branch; no allocation measurement. |
| Design | [tests/unit/binding_test.cpp](../../../../../tests/unit/binding_test.cpp) |

## B0003

[Lines 17–21](../../../../../tests/unit/binding_test.cpp#L17); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
const BoundSql& bound(const SqlBindResult& result)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Extracts a successful BoundSql from a binding result variant. |
| inputs / outputs | Returns a const reference to the BoundSql alternative when present. |
| invariants | A diagnostic alternative is a test failure, not an empty successful query. |
| ownership | Returned reference is borrowed from the input SqlBindResult; that result must outlive every use. |
| failure | Wrong alternative throws runtime_error with diagnostic code/message. |
| cost | Variant inspection only; diagnostic message copy occurs only on failure path in this helper. |
| Design | [tests/unit/binding_test.cpp](../../../../../tests/unit/binding_test.cpp), [include/crown/frontend/bind.hpp](../../../../../include/crown/frontend/bind.hpp) |

## B0004

[Lines 22–27](../../../../../tests/unit/binding_test.cpp#L22); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
const BindingDiagnostic& rejected(const SqlBindResult& result, std::string_view code)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Extracts and checks a binding diagnostic from a result variant. |
| inputs / outputs | Requires a BindingDiagnostic with the requested code and returns it by const reference. |
| invariants | The diagnostic alternative and exact code are both asserted. |
| ownership | Returned diagnostic reference remains tied to the caller-owned result variant. |
| failure | Wrong alternative or code throws runtime_error; returned ref is invalid after result destruction. |
| cost | Variant and code comparison only, with failure-message construction on failure. |
| Design | [tests/unit/binding_test.cpp](../../../../../tests/unit/binding_test.cpp), [include/crown/frontend/bind.hpp](../../../../../include/crown/frontend/bind.hpp) |

## B0005

[Lines 28–35](../../../../../tests/unit/binding_test.cpp#L28); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Catalog catalog()
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Builds a compact catalog for binder scope, type, and wildcard cases. |
| inputs / outputs | Returns fixed r/s/flags/zero tables and their columns. |
| invariants | Column and table order are test inputs to output-order and scope checks. |
| ownership | Returned Catalog owns its schema vectors and names. |
| failure | Construction/allocation failures propagate to main. |
| cost | Small fixed catalog setup; no account or CPU measurement. |
| Design | [tests/unit/binding_test.cpp](../../../../../tests/unit/binding_test.cpp), [include/crown/frontend/bind.hpp](../../../../../include/crown/frontend/bind.hpp) |

## B0006

[Lines 36–40](../../../../../tests/unit/binding_test.cpp#L36); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::vector<std::string> names(const BoundSql& query)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Copies ordered output labels from a bound query. |
| inputs / outputs | Accepts BoundSql by const reference and returns a vector of output names in output order. |
| invariants | Repeated output positions remain positions in the result vector. |
| ownership | Returned strings own their copied labels and do not borrow query storage. |
| failure | Allocation failures propagate. |
| cost | Copies one string per output position; fixture-scale only. |
| Design | [tests/unit/binding_test.cpp](../../../../../tests/unit/binding_test.cpp), [include/crown/frontend/bind.hpp](../../../../../include/crown/frontend/bind.hpp), [docs/sql_binding.md](../../../../sql_binding.md) |

## B0007

[Lines 41–86](../../../../../tests/unit/binding_test.cpp#L41); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void join_scopes_and_outputs()
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Checks binder join-scope rules and visible output ordering. |
| inputs / outputs | Binds a finite set of joins, aliases, wildcards, malformed joins, and bare SELECT statements over the fixed catalog. |
| invariants | Checks USING/NATURAL merged-column order, alias qualifiers, self-join occurrence separation, default versus ONLY flags, lack of flat inheritance, ambiguity and duplicate-name rejection, and zero-source/wildcard behavior. |
| ownership | Each BoundSql is owned by its result; helper accessors borrow while those result variants remain in scope. |
| failure | Expected bind errors are checked as diagnostics or caught errors depending on call site; accidental acceptance/rejection fails. |
| cost | Finite enumerated SQL statements; each performs ordinary binding and output-name construction, with no timing assertion. |
| Design | [tests/unit/binding_test.cpp](../../../../../tests/unit/binding_test.cpp), [src/frontend/bind.cpp](../../../../../src/frontend/bind.cpp), [src/io/binding.cpp](../../../../../src/io/binding.cpp), [docs/sql_binding.md](../../../../sql_binding.md) |

## B0008

[Lines 87–122](../../../../../tests/unit/binding_test.cpp#L87); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void types_parameters_and_wrappers()
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Checks type inference, parameters, casts, and EXISTS wrapper behavior. |
| inputs / outputs | Binds typed/untyped parameters, typed literals, casts, NULL checks, invalid values, and a fixed unsupported-statement list. |
| invariants | Plain SELECT remains bag-marked; explicit width casts and DATE/NULL/CAST cases are distinguished from unsupported implicit/cross-domain conversions; outer EXISTS result semantics are tested separately from inner DISTINCT. |
| ownership | BoundSql is an owning value; output wrapper metadata is part of the returned binding, not admission certification. |
| failure | BindingDiagnostic codes are checked for missing/unbound parameter and invalid forms; unexpected acceptance fails. |
| cost | Finite statement matrix including seven unsupported forms; no runtime execution or timing. |
| Design | [tests/unit/binding_test.cpp](../../../../../tests/unit/binding_test.cpp), [src/frontend/bind.cpp](../../../../../src/frontend/bind.cpp), [src/frontend/parser.cpp](../../../../../src/frontend/parser.cpp), [docs/sql_binding.md](../../../../sql_binding.md) |

## B0009

[Lines 123–153](../../../../../tests/unit/binding_test.cpp#L123); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void locations_ownership_and_limits()
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Checks source-coordinate diagnostics, owned binder inputs, copy/move, and three limits. |
| inputs / outputs | Binds Unicode SQL with an ambiguous reference, clears caller SQL/catalog after binding, copies/moves successful results, and probes work/expression/recursion limits plus syntax and 70-column inputs. |
| invariants | Diagnostic byte offset and character/line/column fields are distinguished; bound source and schema survive caller cleanup; work, expression, and recursion limits are separate options. |
| ownership | Result owns retained source/catalog data; bound/rejected helper references are borrowed from the live result variant. |
| failure | Expected phases/codes are asserted; a mismatched source location or prematurely borrowed reference fails. |
| cost | Three explicit zero-limit probes plus fixed Unicode and 70-column fixtures; no allocation count or CPU benchmark. |
| Design | [tests/unit/binding_test.cpp](../../../../../tests/unit/binding_test.cpp), [src/frontend/bind.cpp](../../../../../src/frontend/bind.cpp), [src/frontend/parser.cpp](../../../../../src/frontend/parser.cpp), [docs/sql_binding.md](../../../../sql_binding.md), [docs/sql_parser.md](../../../../sql_parser.md) |

## B0010

[Lines 154–154](../../../../../tests/unit/binding_test.cpp#L154); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L154-L154:sha256:c7bfe2f3de133d78a2bc8bb1c4a08450563986ee8254facee698e1dcc57e8162
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Close the recorded declaration scopes in binding_test.cpp: namespace (anonymous). |
| inputs / outputs | Preceding namespace, type or initializer declarations in; completed lexical boundary out. |
| invariants | Brace-opening context is recorded in root-scope-context-v1.json. These are declaration/initializer boundaries, not an independent update, validation or recovery operation. |
| ownership | Enclosing objects and borrowed fields keep their declared ownership. This punctuation creates no new owner. |
| failure | Malformed scope syntax is a compile error. Any initializer/constructor failure belongs to the enclosing object declaration. |
| cost | No separate loop, guard or engine call is introduced by the delimiter; enclosing initialization and object lifetime still have their actual costs. |
| Design | [tests/unit/binding_test.cpp](../../../../../tests/unit/binding_test.cpp), [docs/sql_binding.md](../../../../sql_binding.md), [docs/code_review.md](../../../../code_review.md) |

## B0011

[Lines 155–166](../../../../../tests/unit/binding_test.cpp#L155); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
int main()
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Runs all three binder test groups in the standalone entry point. |
| inputs / outputs | No arguments; calls join scopes/outputs, types/parameters/wrappers, and locations/ownership/limits. |
| invariants | The success line follows all helpers; only std::exception is caught. |
| ownership | Called helpers own their catalogs and result variants locally. |
| failure | Caught std::exception is printed and returns nonzero. |
| cost | Three finite groups, with costs dominated by binding fixtures; no measurement is reported. |
| Design | [tests/unit/binding_test.cpp](../../../../../tests/unit/binding_test.cpp), [docs/sql_binding.md](../../../../sql_binding.md) |
