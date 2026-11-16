# `tests/unit/residual_io_test.cpp` — block usage map

[Source](../../../../../tests/unit/residual_io_test.cpp) · [Source index](../../../README.md) · [Subsystem contracts](../../../subsystem_contracts.md) · [Reviewed primitives](../../../primitives.md)

Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection.

Snapshot SHA-256: `b961fb49a975f9d2210613cecc9096e3df65d7abf80d23688e433dae7c632c11`. 374 lines partitioned into 22 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [tests](../../../subsystem_contracts.md#tests). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/code_review.md](../../../../code_review.md), [docs/reference_fuzz.md](../../../../reference_fuzz.md), [docs/task_ledger.md](../../../../task_ledger.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–17](../../../../../tests/unit/residual_io_test.cpp#L1) | Imports dependencies; declares namespace scope; declares aliases; declares values/defaults or compile-time conditions. |  · [reviewed contract](#b0001) |
| [B0002 · 18–20](../../../../../tests/unit/residual_io_test.cpp#L18) | Callable definition: void check(bool condition, const std::string& message) | calls std::runtime_error; guard void check(bool condition, const std::string& message) { · [reviewed contract](#b0002) |
| [B0003 · 21–21](../../../../../tests/unit/residual_io_test.cpp#L21) | Explanatory comments or spacing. |  |
| [B0004 · 22–25](../../../../../tests/unit/residual_io_test.cpp#L22) | Type/record definition: struct Fixture |  · [reviewed contract](#b0004) |
| [B0005 · 26–26](../../../../../tests/unit/residual_io_test.cpp#L26) | Explanatory comments or spacing. |  |
| [B0006 · 27–60](../../../../../tests/unit/residual_io_test.cpp#L27) | Callable definition: Fixture residual_fixture() | calls Date::parse, std::string, Decimal::parse; returns fixture · [reviewed contract](#b0006) |
| [B0007 · 61–61](../../../../../tests/unit/residual_io_test.cpp#L61) | Explanatory comments or spacing. |  |
| [B0008 · 62–75](../../../../../tests/unit/residual_io_test.cpp#L62) | Callable definition: Fixture optimum_fixture() | calls ; returns fixture · [reviewed contract](#b0008) |
| [B0009 · 76–76](../../../../../tests/unit/residual_io_test.cpp#L76) | Explanatory comments or spacing. |  |
| [B0010 · 77–91](../../../../../tests/unit/residual_io_test.cpp#L77) | Callable definition: Fixture infeasible_fixture() | calls push_back, std::to_string; returns fixture; growth push_back; 1 loop sites · [reviewed contract](#b0010) |
| [B0011 · 92–92](../../../../../tests/unit/residual_io_test.cpp#L92) | Explanatory comments or spacing. |  |
| [B0012 · 93–107](../../../../../tests/unit/residual_io_test.cpp#L93) | Callable definition: planner::ResidualOptions options(planner::ResidualMode mode) | calls reset; returns value · [reviewed contract](#b0012) |
| [B0013 · 108–108](../../../../../tests/unit/residual_io_test.cpp#L108) | Explanatory comments or spacing. |  |
| [B0014 · 109–120](../../../../../tests/unit/residual_io_test.cpp#L109) | Callable definition: void advance_to_trace(planner::ResidualSearch& owner, const std::string& label) | calls advance, check, trace, std::runtime_error; guard check(update.progress.result != planner::ResidualResult::failed,; 1 loop sites · [reviewed contract](#b0014) |
| [B0015 · 121–121](../../../../../tests/unit/residual_io_test.cpp#L121) | Explanatory comments or spacing. |  |
| [B0016 · 122–137](../../../../../tests/unit/residual_io_test.cpp#L122) | Callable definition: void finish(planner::ResidualSearch& owner, const std::string& label) | calls advance, check, std::runtime_error; guard check(update.progress.result != planner::ResidualResult::failed,; 1 loop sites · [reviewed contract](#b0016) |
| [B0017 · 138–140](../../../../../tests/unit/residual_io_test.cpp#L138) | declares aliases; declares values/defaults or compile-time conditions. |  · [reviewed contract](#b0017) |
| [B0018 · 141–144](../../../../../tests/unit/residual_io_test.cpp#L141) | Callable definition: void add_record(Records& records, std::string name, std::string schema, io::Json document) | calls push_back, std::move; growth push_back · [reviewed contract](#b0018) |
| [B0019 · 145–145](../../../../../tests/unit/residual_io_test.cpp#L145) | Explanatory comments or spacing. |  |
| [B0020 · 146–356](../../../../../tests/unit/residual_io_test.cpp#L146) | Callable definition: Records build_records() | calls static_assert, residual_fixture, planner::ResidualSearch::create, options; guard static_assert(!std::is_default_constructible_v&lt;planner::ResidualTrace&gt;);; returns records · [reviewed contract](#b0020) |
| [B0021 · 357–358](../../../../../tests/unit/residual_io_test.cpp#L357) | Closes surrounding scope/type. | source comment (unverified): // namespace · [reviewed contract](#b0021) |
| [B0022 · 359–374](../../../../../tests/unit/residual_io_test.cpp#L359) | Callable definition: int main(int argc, char** argv) | calls build_records, std::string_view, io::Json, dump; guard check(argc == 1, "usage: crown_residual_io_test \[--emit\]");; returns 0; 0 · [reviewed contract](#b0022) |

## B0001

[Lines 1–17](../../../../../tests/unit/residual_io_test.cpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L1-L17:sha256:66180227b7246a81ca03cc758defce8b1fcc3c4ca638b5a4650bb458ee8ce2c3
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Prepare residual_io_test.cpp: include "crown/api/error.hpp", "crown/io/residual.hpp", &lt;cstddef&gt;, &lt;iostream&gt;, &lt;stdexcept&gt;, &lt;string&gt;, &lt;string_view&gt;, &lt;type_traits&gt;, &lt;utility&gt;, &lt;vector&gt;; bind local aliases/name imports. |
| inputs / outputs | Compiler-visible dependencies, names and the recorded declarations in; declarations available to the following fixture/CLI/example definitions out. |
| invariants | Declarations are scoped to this source/header and its selected ABI. Included code has its own effects; names and editable fixture values do not confer proof, admission or publication authority. |
| ownership | Aliases/includes do not create a query owner. Pointers/references/views are non-owning. Containers own their elements, which can themselves be borrowed pointers or numeric IDs. Only documented owning shared-control handles retain controls; IDs/slot-handle values do not independently keep an arena/runtime alive. |
| failure | Missing headers, ill-formed names/types, failed static assertions or active #error directives stop compilation. No runtime rejection/rollback mechanism is implemented by aliases or function prototypes. |
| cost | Preprocessing and type/constraint instantiation cost compilation. Alias/prototype syntax does not invoke the declared operation; any included definitions keep their own initialization effects. |
| Design | [tests/unit/residual_io_test.cpp](../../../../../tests/unit/residual_io_test.cpp), [docs/residual_candidates.md](../../../../residual_candidates.md), [docs/code_review.md](../../../../code_review.md) |

## B0002

[Lines 18–20](../../../../../tests/unit/residual_io_test.cpp#L18); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void check(bool condition, const std::string& message)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Fail a residual IO assertion with a message. |
| inputs / outputs | Accepts condition and borrowed string. |
| invariants | False is the only failure condition. |
| ownership | Message is borrowed. |
| failure | Throws std::runtime_error on false. |
| cost | One condition branch; caller-built std::string messages are formed before entry, and failure copies text into std::runtime_error. |
| Design | [tests/unit/residual_io_test.cpp](../../../../../tests/unit/residual_io_test.cpp), [include/crown/planner/residual.hpp](../../../../../include/crown/planner/residual.hpp), [include/crown/io/residual.hpp](../../../../../include/crown/io/residual.hpp), [src/io/residual.cpp](../../../../../src/io/residual.cpp), [docs/residual_candidates.md](../../../../residual_candidates.md), [tests/unit/residual_io_test.cpp](../../../../../tests/unit/residual_io_test.cpp) |

## B0004

[Lines 22–25](../../../../../tests/unit/residual_io_test.cpp#L22); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct Fixture
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Bundle a Query fixture with its Catalog. |
| inputs / outputs | Owns one Catalog and Query used by residual artifact records. |
| invariants | The test chooses fixture identity; this type does not itself establish proof or publication state. |
| ownership | Both members are owned values. |
| failure | Aggregate construction can fail through allocation. |
| cost | Storage follows fixture size. |
| Design | [tests/unit/residual_io_test.cpp](../../../../../tests/unit/residual_io_test.cpp), [include/crown/planner/residual.hpp](../../../../../include/crown/planner/residual.hpp), [include/crown/io/residual.hpp](../../../../../include/crown/io/residual.hpp), [src/io/residual.cpp](../../../../../src/io/residual.cpp), [docs/residual_candidates.md](../../../../residual_candidates.md), [include/crown/io/residual.hpp](../../../../../include/crown/io/residual.hpp) |

## B0006

[Lines 27–60](../../../../../tests/unit/residual_io_test.cpp#L27); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Fixture residual_fixture()
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Create the mixed-value query used to inspect a frozen residual trace. |
| inputs / outputs | Returns catalog/query containing seven atoms, constants, an ignored column, contradiction metadata, and repeated aliased outputs. |
| invariants | This function only builds Catalog and Query data. The caller later admits it to ResidualSearch, whose creation validates input before metered search; no reference trace helper is called here. |
| ownership | Returns owned values; no external storage is retained. |
| failure | Value construction may fail through allocation; the helper reports no status. |
| cost | Builds a fixed seven-atom fixture. |
| Design | [tests/unit/residual_io_test.cpp](../../../../../tests/unit/residual_io_test.cpp), [include/crown/planner/residual.hpp](../../../../../include/crown/planner/residual.hpp), [include/crown/io/residual.hpp](../../../../../include/crown/io/residual.hpp), [src/io/residual.cpp](../../../../../src/io/residual.cpp), [docs/residual_candidates.md](../../../../residual_candidates.md), [tests/reference/residual_oracle.cpp](../../../../../tests/reference/residual_oracle.cpp) |

## B0008

[Lines 62–75](../../../../../tests/unit/residual_io_test.cpp#L62); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Fixture optimum_fixture()
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Create a small query with a known exact optimum for artifact-stage checks. |
| inputs / outputs | Returns a Catalog and Query used by residual search/serialization scenarios. |
| invariants | The fixture separates residual diagnostics from the original-query proof. |
| ownership | Returned Catalog and Query are owned values. |
| failure | Construction may allocate; no search occurs here. |
| cost | Fixed small fixture. |
| Design | [tests/unit/residual_io_test.cpp](../../../../../tests/unit/residual_io_test.cpp), [include/crown/planner/residual.hpp](../../../../../include/crown/planner/residual.hpp), [include/crown/io/residual.hpp](../../../../../include/crown/io/residual.hpp), [src/io/residual.cpp](../../../../../src/io/residual.cpp), [docs/residual_candidates.md](../../../../residual_candidates.md), [include/crown/planner/residual.hpp](../../../../../include/crown/planner/residual.hpp) |

## B0010

[Lines 77–91](../../../../../tests/unit/residual_io_test.cpp#L77); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Fixture infeasible_fixture()
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Create an infeasible triangle query for exact-certificate records. |
| inputs / outputs | Returns a three-atom cyclic query whose exact result is checked as infeasible. |
| invariants | The residual trace is diagnostic; infeasibility authority comes from the original exact proof/certificate record. |
| ownership | Returned fixture owns Catalog and Query. |
| failure | Construction may allocate; no proof is generated here. |
| cost | Fixed three-atom fixture. |
| Design | [tests/unit/residual_io_test.cpp](../../../../../tests/unit/residual_io_test.cpp), [include/crown/planner/residual.hpp](../../../../../include/crown/planner/residual.hpp), [include/crown/io/residual.hpp](../../../../../include/crown/io/residual.hpp), [src/io/residual.cpp](../../../../../src/io/residual.cpp), [docs/residual_candidates.md](../../../../residual_candidates.md), [docs/residual_candidates.md](../../../../residual_candidates.md) |

## B0012

[Lines 93–107](../../../../../tests/unit/residual_io_test.cpp#L93); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
planner::ResidualOptions options(planner::ResidualMode mode)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Set reproducible residual search limits for the IO test. |
| inputs / outputs | Returns ResidualOptions for the selected ResidualMode. |
| invariants | The fixture uses explicit finite work/depth/record/cell and exact producer/replay ceilings; these are not elapsed-time guarantees. |
| ownership | Options are returned by value. |
| failure | This helper only assigns the mode and numeric ceilings; it performs no validation or allocation. Search admission happens later. |
| cost | Constant setup; ceilings bound configured logical work. |
| Design | [tests/unit/residual_io_test.cpp](../../../../../tests/unit/residual_io_test.cpp), [include/crown/planner/residual.hpp](../../../../../include/crown/planner/residual.hpp), [include/crown/io/residual.hpp](../../../../../include/crown/io/residual.hpp), [src/io/residual.cpp](../../../../../src/io/residual.cpp), [docs/residual_candidates.md](../../../../residual_candidates.md), [include/crown/planner/residual.hpp](../../../../../include/crown/planner/residual.hpp) |

## B0014

[Lines 109–120](../../../../../tests/unit/residual_io_test.cpp#L109); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void advance_to_trace(planner::ResidualSearch& owner, const std::string& label)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Advance a residual owner until it exposes a trace. |
| inputs / outputs | Calls advance with one-million work units per request, at most one million times. |
| invariants | Only the expected quantum-work/time wait outcomes are tolerated before a trace is available. |
| ownership | Owner is borrowed; each returned progress value is temporary. |
| failure | Unexpected stops or a missing trace fail via check. |
| cost | At most one million advance calls; configured work quantum is 1,000,000 per call. |
| Design | [tests/unit/residual_io_test.cpp](../../../../../tests/unit/residual_io_test.cpp), [include/crown/planner/residual.hpp](../../../../../include/crown/planner/residual.hpp), [include/crown/io/residual.hpp](../../../../../include/crown/io/residual.hpp), [src/io/residual.cpp](../../../../../src/io/residual.cpp), [docs/residual_candidates.md](../../../../residual_candidates.md), [include/crown/planner/residual.hpp](../../../../../include/crown/planner/residual.hpp) |

## B0016

[Lines 122–137](../../../../../tests/unit/residual_io_test.cpp#L122); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void finish(planner::ResidualSearch& owner, const std::string& label)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Finish a residual owner with small progress quanta. |
| inputs / outputs | Calls advance with quantum 4096 until the operation reaches its completed state. |
| invariants | The five-million-call guard only bounds the test loop; no general CPU/time guard is proven. |
| ownership | Owner is borrowed; progress results are temporary. |
| failure | Unexpected stop or exhausting the call guard fails through check. |
| cost | At most five million calls of 4096 logical work each; actual completion may occur earlier. |
| Design | [tests/unit/residual_io_test.cpp](../../../../../tests/unit/residual_io_test.cpp), [include/crown/planner/residual.hpp](../../../../../include/crown/planner/residual.hpp), [include/crown/io/residual.hpp](../../../../../include/crown/io/residual.hpp), [src/io/residual.cpp](../../../../../src/io/residual.cpp), [docs/residual_candidates.md](../../../../residual_candidates.md), [include/crown/planner/residual.hpp](../../../../../include/crown/planner/residual.hpp) |

## B0017

[Lines 138–140](../../../../../tests/unit/residual_io_test.cpp#L138); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L138-L140:sha256:8f553b590a0a813f7ae3c535add6d4ad2eec0385c30105b12ddaf9a8a1249e02
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Prepare residual_io_test.cpp: bind local aliases/name imports. |
| inputs / outputs | Compiler-visible dependencies, names and the recorded declarations in; declarations available to the following fixture/CLI/example definitions out. |
| invariants | Declarations are scoped to this source/header and its selected ABI. Included code has its own effects; names and editable fixture values do not confer proof, admission or publication authority. |
| ownership | Aliases/includes do not create a query owner. Pointers/references/views are non-owning. Containers own their elements, which can themselves be borrowed pointers or numeric IDs. Only documented owning shared-control handles retain controls; IDs/slot-handle values do not independently keep an arena/runtime alive. |
| failure | Missing headers, ill-formed names/types, failed static assertions or active #error directives stop compilation. No runtime rejection/rollback mechanism is implemented by aliases or function prototypes. |
| cost | Preprocessing and type/constraint instantiation cost compilation. Alias/prototype syntax does not invoke the declared operation; any included definitions keep their own initialization effects. |
| Design | [tests/unit/residual_io_test.cpp](../../../../../tests/unit/residual_io_test.cpp), [docs/residual_candidates.md](../../../../residual_candidates.md), [docs/code_review.md](../../../../code_review.md) |

## B0018

[Lines 141–144](../../../../../tests/unit/residual_io_test.cpp#L141); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void add_record(Records& records, std::string name, std::string schema, io::Json document)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Insert a named residual JSON record into the output vector. |
| inputs / outputs | Takes Records by reference, name/schema strings by value, and a Json document; appends one object. |
| invariants | Vector order is insertion order; caller chooses schema label. |
| ownership | Records and Json are moved/copied into the vector; input name/schema are owned parameters. |
| failure | Allocation or JSON construction can throw. |
| cost | One append; storage follows document size. |
| Design | [tests/unit/residual_io_test.cpp](../../../../../tests/unit/residual_io_test.cpp), [include/crown/planner/residual.hpp](../../../../../include/crown/planner/residual.hpp), [include/crown/io/residual.hpp](../../../../../include/crown/io/residual.hpp), [src/io/residual.cpp](../../../../../src/io/residual.cpp), [docs/residual_candidates.md](../../../../residual_candidates.md), [include/crown/io/residual.hpp](../../../../../include/crown/io/residual.hpp) |

## B0020

[Lines 146–356](../../../../../tests/unit/residual_io_test.cpp#L146); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Records build_records()
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Build all residual IO fixture records and stage-transition examples. |
| inputs / outputs | Returns a Records vector for frozen trace, candidate/progress, exact pending/optimum/infeasible, metadata, move, and cancellation cases. |
| invariants | Candidate upper bounds and frozen traces do not certify original minimum; exact certificates do. Admitted progress and pending exact records use null proof fields. |
| ownership | All fixtures, owners, copied views, writers, and JSON are local; returned Records owns serialized documents. |
| failure | Assertions fail through check; state/API errors are caught or asserted at their call sites. |
| cost | Builds a fixed record set while advancing in-process ResidualSearch owners through trace publication and exact producer/replay work. advance_to_trace and finish have call ceilings, not CPU-time guarantees; JSON construction is additional ordinary work. |
| Design | [tests/unit/residual_io_test.cpp](../../../../../tests/unit/residual_io_test.cpp), [include/crown/planner/residual.hpp](../../../../../include/crown/planner/residual.hpp), [include/crown/io/residual.hpp](../../../../../include/crown/io/residual.hpp), [src/io/residual.cpp](../../../../../src/io/residual.cpp), [docs/residual_candidates.md](../../../../residual_candidates.md), [docs/residual_candidates.md](../../../../residual_candidates.md) |

## B0021

[Lines 357–358](../../../../../tests/unit/residual_io_test.cpp#L357); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L357-L358:sha256:c2bd7638f09d52cb034ed574f539304035fc6fab162bf8d5fa20a35d8c7288a1
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Close the recorded declaration scopes in residual_io_test.cpp: namespace (anonymous). |
| inputs / outputs | Preceding namespace, type or initializer declarations in; completed lexical boundary out. |
| invariants | Brace-opening context is recorded in root-scope-context-v1.json. These are declaration/initializer boundaries, not an independent update, validation or recovery operation. |
| ownership | Enclosing objects and borrowed fields keep their declared ownership. This punctuation creates no new owner. |
| failure | Malformed scope syntax is a compile error. Any initializer/constructor failure belongs to the enclosing object declaration. |
| cost | No separate loop, guard or engine call is introduced by the delimiter; enclosing initialization and object lifetime still have their actual costs. |
| Design | [tests/unit/residual_io_test.cpp](../../../../../tests/unit/residual_io_test.cpp), [docs/residual_candidates.md](../../../../residual_candidates.md), [docs/code_review.md](../../../../code_review.md) |

## B0022

[Lines 359–374](../../../../../tests/unit/residual_io_test.cpp#L359); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
int main(int argc, char** argv)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Emit residual records on request or run the IO assertion path. |
| inputs / outputs | Calls build_records before argument handling; --emit writes its JSON, no args prints success, and other args fail the argc check. |
| invariants | Execution advances in-process ResidualSearch producers and replay while building records; --emit only selects output mode and does not launch an external producer. |
| ownership | Owns argv-derived strings, records, and output JSON until writing. |
| failure | The catch handles std::exception only and returns 1; unknown arguments fail check after build_records and are caught the same way. |
| cost | One build_records call includes in-process trace/exact producer and replay work plus ordinary record/JSON construction; output has a fixed fixture collection. The call guards do not bound CPU time. |
| Design | [tests/unit/residual_io_test.cpp](../../../../../tests/unit/residual_io_test.cpp), [include/crown/planner/residual.hpp](../../../../../include/crown/planner/residual.hpp), [include/crown/io/residual.hpp](../../../../../include/crown/io/residual.hpp), [src/io/residual.cpp](../../../../../src/io/residual.cpp), [docs/residual_candidates.md](../../../../residual_candidates.md), [tests/integration/tree_oracle.py](../../../../../tests/integration/tree_oracle.py) |
