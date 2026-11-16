# `tests/unit/admission_test.cpp` — block usage map

[Source](../../../../../tests/unit/admission_test.cpp) · [Source index](../../../README.md) · [Subsystem contracts](../../../subsystem_contracts.md) · [Reviewed primitives](../../../primitives.md)

Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection.

Snapshot SHA-256: `048944bd045d8b13102a14d007e317d99889065a85acc72b0c1213ce0fb8599e`. 134 lines partitioned into 13 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [tests](../../../subsystem_contracts.md#tests). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/code_review.md](../../../../code_review.md), [docs/reference_fuzz.md](../../../../reference_fuzz.md), [docs/task_ledger.md](../../../../task_ledger.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–14](../../../../../tests/unit/admission_test.cpp#L1) | Imports dependencies; declares namespace scope; declares aliases. |  · [reviewed contract](#b0001) |
| [B0002 · 15–15](../../../../../tests/unit/admission_test.cpp#L15) | Callable definition: Value n(std::int64_t value) | calls ; returns value · [reviewed contract](#b0002) |
| [B0003 · 16–16](../../../../../tests/unit/admission_test.cpp#L16) | Callable definition: Value s(std::string value) | calls ; returns value · [reviewed contract](#b0003) |
| [B0004 · 17–17](../../../../../tests/unit/admission_test.cpp#L17) | Callable definition: void check(bool value,const std::string& message) | calls std::runtime_error; guard void check(bool value,const std::string& message) { if (!value) throw std::runtime_error(message); } · [reviewed contract](#b0004) |
| [B0005 · 18–19](../../../../../tests/unit/admission_test.cpp#L18) | Callable definition: Catalog catalog() | calls ; returns {5,{{@ ,{{@ ,ScalarType::int64},{@ ,ScalarType::int64},{@ ,ScalarType::string}}}, · [reviewed contract](#b0005) |
| [B0006 · 20–20](../../../../../tests/unit/admission_test.cpp#L20) | Callable definition: Database empty(const Catalog& schema) | calls size; returns {std::vector&lt;Relation&gt;(schema.tables.size())} · [reviewed contract](#b0006) |
| [B0007 · 21–21](../../../../../tests/unit/admission_test.cpp#L21) | Callable definition: Relation snapshot(const AdapterState& state) | calls map_sql_result, query, reference::evaluate, logical; returns map_sql_result(state.query(),reference::evaluate(state.query().core_catalog,state.query().core,stat… · [reviewed contract](#b0007) |
| [B0008 · 22–30](../../../../../tests/unit/admission_test.cpp#L22) | Callable definition: AdmissionResult status(std::string_view sql,AdmissionStatus expected,const AdmissionOptions& options={}) | calls admit_sql, catalog, check, admission_status_name; guard check(result.status==expected,"unexpected admission: "+admission_status_name(result.status)+" for "…; returns result · [reviewed contract](#b0008) |
| [B0009 · 31–60](../../../../../tests/unit/admission_test.cpp#L31) | Callable definition: void categories_and_structure() | calls status, check, empty, size; guard check(full.route==AdmissionRoute::free_connex && full.structure-&gt;query_class==planner::QueryClass::…; 1 loop sites · [reviewed contract](#b0009) |
| [B0010 · 61–95](../../../../../tests/unit/admission_test.cpp#L61) | Callable definition: void grounding_and_legacy() | calls catalog, status, check, size; guard check(admitted.program-&gt;core.head.size()==1 && std::holds_alternative&lt;ConstantOutput&gt;(admitted.prog…; 1 loop sites · [reviewed contract](#b0010) |
| [B0011 · 96–127](../../../../../tests/unit/admission_test.cpp#L96) | Callable definition: void limits_parameters_and_ownership() | calls check, status, planner::analyze_bounded, io::write_structural_analysis; guard check(status(sql,AdmissionStatus::resource_limit,options).phase=="binding","binding limit phase");; growth push_back; 1 loop sites · [reviewed contract](#b0011) |
| [B0012 · 128–128](../../../../../tests/unit/admission_test.cpp#L128) | Closes surrounding scope/type. | source comment (unverified): // namespace · [reviewed contract](#b0012) |
| [B0013 · 129–134](../../../../../tests/unit/admission_test.cpp#L129) | Callable definition: int main() | calls categories_and_structure, grounding_and_legacy, limits_parameters_and_ownership, what; returns 1 · [reviewed contract](#b0013) |

## B0001

[Lines 1–14](../../../../../tests/unit/admission_test.cpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L1-L14:sha256:6b574e73343c144912a86eff6ef724d13573342773b34aa838690a79e03f8bcf
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Prepare admission_test.cpp: include "crown/frontend/admission.hpp", "crown/frontend/adapter.hpp", "crown/io/admission.hpp", "crown/io/normalization.hpp", "crown/io/recognition.hpp", "crown/api/error.hpp", "evaluator.hpp", &lt;iostream&gt;, &lt;stdexcept&gt;; bind local aliases/name imports. |
| inputs / outputs | Compiler-visible dependencies, names and the recorded declarations in; declarations available to the following fixture/CLI/example definitions out. |
| invariants | Declarations are scoped to this source/header and its selected ABI. Included code has its own effects; names and editable fixture values do not confer proof, admission or publication authority. |
| ownership | Aliases/includes do not create a query owner. Pointers/references/views are non-owning. Containers own their elements, which can themselves be borrowed pointers or numeric IDs. Only documented owning shared-control handles retain controls; IDs/slot-handle values do not independently keep an arena/runtime alive. |
| failure | Missing headers, ill-formed names/types, failed static assertions or active #error directives stop compilation. No runtime rejection/rollback mechanism is implemented by aliases or function prototypes. |
| cost | Preprocessing and type/constraint instantiation cost compilation. Alias/prototype syntax does not invoke the declared operation; any included definitions keep their own initialization effects. |
| Design | [tests/unit/admission_test.cpp](../../../../../tests/unit/admission_test.cpp), [docs/sql_admission.md](../../../../sql_admission.md), [docs/code_review.md](../../../../code_review.md) |

## B0002

[Lines 15–15](../../../../../tests/unit/admission_test.cpp#L15); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Value n(std::int64_t value)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Builds an integer Value for the admission fixtures. |
| inputs / outputs | Accepts int64 and returns the corresponding scalar Value. |
| invariants | The helper does no range conversion beyond the Value constructor. |
| ownership | The returned Value owns only its scalar payload; the argument remains a local copy. |
| failure | Any constructor exception propagates to the enclosing test. |
| cost | One scalar construction; no query or database work. |
| Design | [tests/unit/admission_test.cpp](../../../../../tests/unit/admission_test.cpp), [include/crown/ir/scalar.hpp](../../../../../include/crown/ir/scalar.hpp) |

## B0003

[Lines 16–16](../../../../../tests/unit/admission_test.cpp#L16); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Value s(std::string value)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Builds a string Value for tags and SQL-related fixture fields. |
| inputs / outputs | Moves the by-value string into a string-valued Value and returns it. |
| invariants | The helper preserves the supplied bytes, including embedded NUL when present. |
| ownership | The Value owns its string after the local parameter is moved. |
| failure | Allocation or scalar-construction exceptions propagate. |
| cost | One fixture scalar construction plus any string storage; not charged to a query account. |
| Design | [tests/unit/admission_test.cpp](../../../../../tests/unit/admission_test.cpp), [include/crown/ir/scalar.hpp](../../../../../include/crown/ir/scalar.hpp) |

## B0004

[Lines 17–17](../../../../../tests/unit/admission_test.cpp#L17); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void check(bool value,const std::string& message)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Turns a false test predicate into a local test failure. |
| inputs / outputs | Takes a bool and a const message reference; returns normally on true. |
| invariants | Only false predicates throw; message construction at the call site can already have happened. |
| ownership | Does not retain the referenced message. |
| failure | False raises std::runtime_error with the supplied text. |
| cost | Predicate check only; no allocation is asserted for successful call sites. |
| Design | [tests/unit/admission_test.cpp](../../../../../tests/unit/admission_test.cpp) |

## B0005

[Lines 18–19](../../../../../tests/unit/admission_test.cpp#L18); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Catalog catalog()
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Creates the fixed catalog used by admission and reference-result cases. |
| inputs / outputs | Returns catalog version 5 with r(x,y,tag), s(y,z), t(x,z), and zero(empty). |
| invariants | Column order, scalar types, and the empty relation are fixed test inputs. |
| ownership | Catalog and nested names are returned by value with ordinary container ownership. |
| failure | Catalog construction failures propagate to main. |
| cost | Allocates fixture containers proportional to these four schemas; no measured resource counter. |
| Design | [tests/unit/admission_test.cpp](../../../../../tests/unit/admission_test.cpp), [include/crown/frontend/admission.hpp](../../../../../include/crown/frontend/admission.hpp) |

## B0006

[Lines 20–20](../../../../../tests/unit/admission_test.cpp#L20); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Database empty(const Catalog& schema)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Creates an empty database shaped like the supplied catalog. |
| inputs / outputs | Accepts a catalog reference and returns one empty Relation per schema table. |
| invariants | The relation vector follows catalog table order and begins with no rows. |
| ownership | Returned database owns its relation container; it does not borrow the catalog. |
| failure | A schema/table mismatch is not separately tested here; allocation failures propagate. |
| cost | One empty relation/container setup per catalog table. |
| Design | [tests/unit/admission_test.cpp](../../../../../tests/unit/admission_test.cpp), [tests/reference/evaluator.hpp](../../../../../tests/reference/evaluator.hpp) |

## B0007

[Lines 21–21](../../../../../tests/unit/admission_test.cpp#L21); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Relation snapshot(const AdapterState& state)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Evaluates a reference AdapterState to an owning query-result relation. |
| inputs / outputs | Passes the state catalog, core query, and logical database to the reference evaluator, then maps its result. |
| invariants | This is the test oracle path; it does not create or inspect a physical runtime. |
| ownership | Returned Relation owns result rows after the state or evaluator temporaries end. |
| failure | Reference evaluation and mapping errors propagate. |
| cost | Work follows the finite fixture evaluation and result mapping; no benchmark or query-account measurement. |
| Design | [tests/unit/admission_test.cpp](../../../../../tests/unit/admission_test.cpp), [tests/reference/evaluator.cpp](../../../../../tests/reference/evaluator.cpp) |

## B0008

[Lines 22–30](../../../../../tests/unit/admission_test.cpp#L22); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
AdmissionResult status(std::string_view sql,AdmissionStatus expected,const AdmissionOptions& options={})
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Checks one SQL admission outcome and its stable result envelope. |
| inputs / outputs | Takes SQL, expected status, and optional options; returns the AdmissionResult after checking status, diagnostic/route/structure/program relationships and serialized status labels. |
| invariants | Rejected results require diagnostics and no route; admitted results require no diagnostic, a route, structure, and schema-2 normalized program; envelope labels remain frontend_and_structure/not_lowered. |
| ownership | The returned result owns normalized/source data; SQL is a view used only during admission. |
| failure | Any mismatched status or envelope condition throws through check; admission diagnostics are asserted as data, not converted to exceptions here. |
| cost | One admission, serialization, and assertion set per call; call-site diagnostic text may be built eagerly. |
| Design | [tests/unit/admission_test.cpp](../../../../../tests/unit/admission_test.cpp), [src/frontend/admission.cpp](../../../../../src/frontend/admission.cpp), [include/crown/frontend/admission.hpp](../../../../../include/crown/frontend/admission.hpp), [docs/sql_admission.md](../../../../sql_admission.md) |

## B0009

[Lines 31–60](../../../../../tests/unit/admission_test.cpp#L31); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void categories_and_structure()
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Exercises a fixed matrix of SQL shape, syntax, semantic, and unsupported-feature classifications. |
| inputs / outputs | Invokes status across 22 cases: 14 explicit shape/status cases plus 8 unsupported forms; then directly checks nullable-column and invalid-catalog rejection. |
| invariants | Expected outcomes distinguish admitted free-connex/constant-empty queries, structural rejection, semantic failure, and unsupported SQL; assertions cover these inputs only. |
| ownership | Each AdmissionResult and fixture string is ordinary test-owned storage; no result is retained as runtime state. |
| failure | A wrong classification or envelope assertion throws; parser/admission diagnostic contents are inspected only where stated. |
| cost | 24 admission paths total including the two direct final calls; the 8-form loop is finite. Fixture/query serialization allocations are not account measurements. |
| Design | [tests/unit/admission_test.cpp](../../../../../tests/unit/admission_test.cpp), [src/frontend/admission.cpp](../../../../../src/frontend/admission.cpp), [src/frontend/parser.cpp](../../../../../src/frontend/parser.cpp), [docs/sql_admission.md](../../../../sql_admission.md) |

## B0010

[Lines 61–95](../../../../../tests/unit/admission_test.cpp#L61); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void grounding_and_legacy()
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Compares legacy CQ upgrading and admitted SQL against the reference semantics. |
| inputs / outputs | Builds v1/v2 normalized forms, admits grounded queries, snapshots reference states, and applies witness insert/delete sequences. |
| invariants | It checks a legacy non-free-connex label, v1 roundtrip, v2 upgrade, equal projections for duplicate logical answers, constant grounding, unmatched predicates, and self-join support across two witnesses. |
| ownership | Normalized programs and snapshots own their contents; reference sessions own mutable database state and held result rows remain values. |
| failure | Unexpected normalization, admission, evaluation, or delta behavior fails via test exceptions. |
| cost | Finite small relation fixtures and explicit event sequences; no physical lowering or runtime account counter is measured. |
| Design | [tests/unit/admission_test.cpp](../../../../../tests/unit/admission_test.cpp), [src/frontend/normalize.cpp](../../../../../src/frontend/normalize.cpp), [src/frontend/admission.cpp](../../../../../src/frontend/admission.cpp), [tests/reference/evaluator.cpp](../../../../../tests/reference/evaluator.cpp), [docs/sql_admission.md](../../../../sql_admission.md) |

## B0011

[Lines 96–127](../../../../../tests/unit/admission_test.cpp#L96); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void limits_parameters_and_ownership()
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Checks admission limits, parameter grounding, and result lifetime behavior. |
| inputs / outputs | Sets bind/normalize/recognition limits, compares bounded analysis work, binds typed parameters, tests NULL EXISTS and missing-parameter diagnostics, parses options JSON, and copies/moves an owned result. |
| invariants | Zero limits stop at their respective phases; recognition failure may retain the program while leaving structure absent; bounded analysis is compared with the unlimited witness; a 70-column SELECT* and nullary EXISTS avoid an assumed 64-column cutoff. |
| ownership | AdmissionResult remains usable after caller SQL/catalog clear; copy and move results are checked as owning values. |
| failure | Expected parameter, parse, and resource outcomes are checked by their result fields; an unexpected diagnostic or ownership difference fails. |
| cost | Finite phase probes and one measured-work boundary pair; 70-column fixture construction and JSON parsing are ordinary allocations, not account measurements. |
| Design | [tests/unit/admission_test.cpp](../../../../../tests/unit/admission_test.cpp), [src/frontend/admission.cpp](../../../../../src/frontend/admission.cpp), [src/frontend/bind.cpp](../../../../../src/frontend/bind.cpp), [src/frontend/normalize.cpp](../../../../../src/frontend/normalize.cpp), [docs/sql_admission.md](../../../../sql_admission.md) |

## B0012

[Lines 128–128](../../../../../tests/unit/admission_test.cpp#L128); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L128-L128:sha256:c7bfe2f3de133d78a2bc8bb1c4a08450563986ee8254facee698e1dcc57e8162
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Close the recorded declaration scopes in admission_test.cpp: namespace (anonymous). |
| inputs / outputs | Preceding namespace, type or initializer declarations in; completed lexical boundary out. |
| invariants | Brace-opening context is recorded in root-scope-context-v1.json. These are declaration/initializer boundaries, not an independent update, validation or recovery operation. |
| ownership | Enclosing objects and borrowed fields keep their declared ownership. This punctuation creates no new owner. |
| failure | Malformed scope syntax is a compile error. Any initializer/constructor failure belongs to the enclosing object declaration. |
| cost | No separate loop, guard or engine call is introduced by the delimiter; enclosing initialization and object lifetime still have their actual costs. |
| Design | [tests/unit/admission_test.cpp](../../../../../tests/unit/admission_test.cpp), [docs/sql_admission.md](../../../../sql_admission.md), [docs/code_review.md](../../../../code_review.md) |

## B0013

[Lines 129–134](../../../../../tests/unit/admission_test.cpp#L129); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
int main()
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Provides the executable entry point for the three admission test groups. |
| inputs / outputs | Takes no arguments; runs category/structure, grounding/legacy, and limit/parameter/ownership groups, then prints the success line. |
| invariants | Success output is reached only after all three groups return; the catch handles std::exception. |
| ownership | All fixture state is scoped to called functions; the main retains no result after return. |
| failure | The outer catch reports failure and returns nonzero for std::exception. |
| cost | Runs exactly three finite source-defined groups; execution cost is not reported as a measurement here. |
| Design | [tests/unit/admission_test.cpp](../../../../../tests/unit/admission_test.cpp), [docs/sql_admission.md](../../../../sql_admission.md) |
