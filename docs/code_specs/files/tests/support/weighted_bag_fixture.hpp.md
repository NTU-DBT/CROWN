# `tests/support/weighted_bag_fixture.hpp` — block usage map

[Source](../../../../../tests/support/weighted_bag_fixture.hpp) · [Source index](../../../README.md) · [Subsystem contracts](../../../subsystem_contracts.md) · [Reviewed primitives](../../../primitives.md)

Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection.

Snapshot SHA-256: `dcfe87641d230985091043ddd824dbee37ec881cecb2fc1499e472b9ab886e2b`. 185 lines partitioned into 23 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [tests](../../../subsystem_contracts.md#tests). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/code_review.md](../../../../code_review.md), [docs/reference_fuzz.md](../../../../reference_fuzz.md), [docs/task_ledger.md](../../../../task_ledger.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–10](../../../../../tests/support/weighted_bag_fixture.hpp#L1) | Imports dependencies; guards repeated header inclusion; declares namespace scope. | source comment (unverified): // W03 test reference: enumerate native assignment joins, independently of · [reviewed contract](#b0001) |
| [B0002 · 11–29](../../../../../tests/support/weighted_bag_fixture.hpp#L11) | Callable definition: inline PhysicalPlan counted_path(bool indexed, bool hidden_tail=false, bool repeated_head=false) | calls push_back, planner::lower_tree, options; returns planner::lower_tree(catalog,query,tree,options(indexed)); growth push_back; source comment (unverified): // Both nodes are in C*: hidden u and z must be summed locally, while S's · [reviewed contract](#b0002) |
| [B0003 · 30–30](../../../../../tests/support/weighted_bag_fixture.hpp#L30) | Explanatory comments or spacing. |  |
| [B0004 · 31–43](../../../../../tests/support/weighted_bag_fixture.hpp#L31) | Callable definition: inline PhysicalPlan typed_bag(bool indexed) | calls planner::lower_tree, options; returns planner::lower_tree(catalog,query,tree,options(indexed)) · [reviewed contract](#b0004) |
| [B0005 · 44–44](../../../../../tests/support/weighted_bag_fixture.hpp#L44) | Explanatory comments or spacing. |  |
| [B0006 · 45–49](../../../../../tests/support/weighted_bag_fixture.hpp#L45) | Callable definition: inline void typed_inputs(Model& model, std::size_t rows=3) | calls set, std::string, std::to_string, n; 1 loop sites · [reviewed contract](#b0006) |
| [B0007 · 50–50](../../../../../tests/support/weighted_bag_fixture.hpp#L50) | Explanatory comments or spacing. |  |
| [B0008 · 51–63](../../../../../tests/support/weighted_bag_fixture.hpp#L51) | Callable definition: inline PhysicalPlan disconnected_bag(bool indexed, std::optional&lt;std::uint64_t&gt; structural_limit={}) | calls options, planner::lower_tree; returns planner::lower_tree(catalog,query,tree,configured) · [reviewed contract](#b0008) |
| [B0009 · 64–64](../../../../../tests/support/weighted_bag_fixture.hpp#L64) | Explanatory comments or spacing. |  |
| [B0010 · 65–84](../../../../../tests/support/weighted_bag_fixture.hpp#L65) | Callable definition: inline PhysicalPlan deep_bag(std::size_t length, bool hidden, bool indexed) | calls push_back, std::to_string, emplace_back, std::move; returns planner::lower_tree(catalog,query,tree,options(indexed)); growth emplace_back, push_back; 2 loop sites · [reviewed contract](#b0010) |
| [B0011 · 85–85](../../../../../tests/support/weighted_bag_fixture.hpp#L85) | Explanatory comments or spacing. |  |
| [B0012 · 86–97](../../../../../tests/support/weighted_bag_fixture.hpp#L86) | Callable definition: inline Assignments native_assignments(const CompiledProgram& plan, const Inputs& inputs, const std::vector&lt;NodeId&gt;& nodes, Assign… | calls std::move, nodes, emplace, assignment; returns result; growth emplace; 2 loop sites · [reviewed contract](#b0012) |
| [B0013 · 98–102](../../../../../tests/support/weighted_bag_fixture.hpp#L98) | Callable definition: inline std::vector&lt;NodeId&gt; all_nodes(const CompiledProgram& plan) | calls nodes, push_back; returns result; growth push_back; 1 loop sites · [reviewed contract](#b0013) |
| [B0014 · 103–113](../../../../../tests/support/weighted_bag_fixture.hpp#L103) | Callable definition: inline Counts bag_oracle(const CompiledProgram& plan, const Inputs& inputs) | calls route, native_assignments, all_nodes, query; returns {}; {{Row{},1}}; growth push_back; 2 loop sites · [reviewed contract](#b0014) |
| [B0015 · 114–116](../../../../../tests/support/weighted_bag_fixture.hpp#L114) | Explanatory comments or spacing. | source comment (unverified): // Delete C* edges, then join each resulting component's actual native atoms. · [reviewed contract](#b0015) |
| [B0016 · 117–123](../../../../../tests/support/weighted_bag_fixture.hpp#L117) | Callable definition: inline std::vector&lt;NodeId&gt; component(const CompiledProgram& plan, NodeId root) | calls size, nodes, push_back; returns result; growth push_back; 2 loop sites; source comment (unverified): // Delete C* edges, then join each resulting component's actual native atoms. · [reviewed contract](#b0016) |
| [B0017 · 124–131](../../../../../tests/support/weighted_bag_fixture.hpp#L124) | Callable definition: inline std::uint64_t component_count(const CompiledProgram& plan, const Inputs& inputs, const std::vector&lt;NodeId&gt;& nodes, Assignm… | calls native_assignments, std::move, add; returns count; 1 loop sites · [reviewed contract](#b0017) |
| [B0018 · 132–152](../../../../../tests/support/weighted_bag_fixture.hpp#L132) | Callable definition: inline void compare_factors(const w::Snapshot& actual, const Inputs& inputs) | calls recompute, nodes, component, storage::export_row; guard check(row.value-&gt;factor.value==count,"cached local contribution differs from native component join"…; growth emplace; 4 loop sites · [reviewed contract](#b0018) |
| [B0019 · 153–153](../../../../../tests/support/weighted_bag_fixture.hpp#L153) | Explanatory comments or spacing. | source comment (unverified): // Account assertions cover actual emitted tuples; ordinary exported maps remain separate. · [reviewed contract](#b0019) |
| [B0020 · 154–166](../../../../../tests/support/weighted_bag_fixture.hpp#L154) | Callable definition: inline Counts drain(runtime::WeightedRuntime::ResultCursor& cursor) | calls next, check, layout, same_token; guard check(record-&gt;tuple.layout().same_token(cursor.layout()),"weighted cursor output layout changed");; returns result; growth emplace; 1 loop sites; source comment (unverified): // Account assertions cover actual emitted tuples; ordinary exported maps remain separate. · [reviewed contract](#b0020) |
| [B0021 · 167–177](../../../../../tests/support/weighted_bag_fixture.hpp#L167) | Callable definition: inline void compare_bag(runtime::WeightedRuntime& runtime, const Inputs& inputs) | calls bag_oracle, structural_program, snapshot, compare_factors; guard check(cursor.binding()==runtime.binding(),"cursor weighted binding differs");; 1 loop sites · [reviewed contract](#b0021) |
| [B0022 · 178–184](../../../../../tests/support/weighted_bag_fixture.hpp#L178) | Type/record definition: struct BagModel:Model | returns result · [reviewed contract](#b0022) |
| [B0023 · 185–185](../../../../../tests/support/weighted_bag_fixture.hpp#L185) | Closes surrounding scope/type. | source comment (unverified): // namespace crown::weighted_test · [reviewed contract](#b0023) |

## B0001

[Lines 1–10](../../../../../tests/support/weighted_bag_fixture.hpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L1-L10:sha256:3a51d2b675674c83ddc63915c44b8c5520e776ccf2c268c30fb3df81423d2e44
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Prepare weighted_bag_fixture.hpp: include "weighted_fixture.hpp". |
| inputs / outputs | Compiler-visible dependencies, names and the recorded declarations in; declarations available to the following fixture/CLI/example definitions out. |
| invariants | Declarations are scoped to this source/header and its selected ABI. Included code has its own effects; names and editable fixture values do not confer proof, admission or publication authority. |
| ownership | Aliases/includes do not create a query owner. Pointers/references/views are non-owning. Containers own their elements, which can themselves be borrowed pointers or numeric IDs. Only documented owning shared-control handles retain controls; IDs/slot-handle values do not independently keep an arena/runtime alive. |
| failure | Missing headers, ill-formed names/types, failed static assertions or active #error directives stop compilation. No runtime rejection/rollback mechanism is implemented by aliases or function prototypes. |
| cost | Preprocessing and type/constraint instantiation cost compilation. Alias/prototype syntax does not invoke the declared operation; any included definitions keep their own initialization effects. |
| Design | [tests/support/weighted_bag_fixture.hpp](../../../../../tests/support/weighted_bag_fixture.hpp), [docs/weighted_enumeration.md](../../../../weighted_enumeration.md), [docs/code_review.md](../../../../code_review.md) |

## B0002

[Lines 11–29](../../../../../tests/support/weighted_bag_fixture.hpp#L11); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
inline PhysicalPlan counted_path(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Build a bag path that separates local hidden-witness factors from child weights. |
| inputs / outputs | R(x,y,u)→S(y,z), head x,y; optional hidden T(z) tail, optional repeated/reordered head y,x,y. |
| invariants | R/S are in C*; hidden-tail T is outside. S weight must not be double-counted in R's local factor. |
| ownership | Local ordinary source DTOs are owned; returned PhysicalPlan shares its actual immutable compiler control on copy. |
| failure | Ordinary allocation/compiler rejection propagates; no fake optimum/source/proof handles. |
| cost | Bounded DTO construction, optional one-node extension and real lowering. |
| Design | [tests/support/weighted_bag_fixture.hpp](../../../../../tests/support/weighted_bag_fixture.hpp), [tests/unit/weighted_bag_test.cpp](../../../../../tests/unit/weighted_bag_test.cpp), [tests/unit/weighted_cursor_limits_test.cpp](../../../../../tests/unit/weighted_cursor_limits_test.cpp), [tests/unit/weighted_bag_oracle_driver.cpp](../../../../../tests/unit/weighted_bag_oracle_driver.cpp), [tests/reference/weighted_bag_oracle.py](../../../../../tests/reference/weighted_bag_oracle.py), [include/crown/runtime/weighted.hpp](../../../../../include/crown/runtime/weighted.hpp), [docs/weighted_enumeration.md](../../../../weighted_enumeration.md), [Refactor.md](../../../../../Refactor.md), [docs/code_review.md](../../../../code_review.md) |

## B0004

[Lines 31–43](../../../../../tests/support/weighted_bag_fixture.hpp#L31); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
inline PhysicalPlan typed_bag(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Build mixed-scalar bag output with a repeated projected field. |
| inputs / outputs | R(name,y,day)→S(y,flag), head flag,name,day,name,y. |
| invariants | String/date/Boolean/int64 distinctions and duplicate output variable positions must survive layout/export. |
| ownership | Local ordinary source DTOs are owned; returned PhysicalPlan shares its actual immutable compiler control on copy. |
| failure | Ordinary allocation/compiler rejection propagates; no fake optimum/source/proof handles. |
| cost | Small typed catalog/query/tree setup and actual lowering. |
| Design | [tests/support/weighted_bag_fixture.hpp](../../../../../tests/support/weighted_bag_fixture.hpp), [tests/unit/weighted_bag_test.cpp](../../../../../tests/unit/weighted_bag_test.cpp), [tests/unit/weighted_cursor_limits_test.cpp](../../../../../tests/unit/weighted_cursor_limits_test.cpp), [tests/unit/weighted_bag_oracle_driver.cpp](../../../../../tests/unit/weighted_bag_oracle_driver.cpp), [tests/reference/weighted_bag_oracle.py](../../../../../tests/reference/weighted_bag_oracle.py), [include/crown/runtime/weighted.hpp](../../../../../include/crown/runtime/weighted.hpp), [docs/weighted_enumeration.md](../../../../weighted_enumeration.md), [Refactor.md](../../../../../Refactor.md), [docs/code_review.md](../../../../code_review.md) |

## B0006

[Lines 45–49](../../../../../tests/support/weighted_bag_fixture.hpp#L45); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
inline void typed_inputs(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Populate mixed-scalar weighted rows through actual Model updates. |
| inputs / outputs | Creates rows long 256-x name+index,y7,Date2026-11-11 with weights i+2; S(y7,false)=3,true=5. |
| invariants | Trusted small rows count avoids size_t/uint64 sequence/weight wrap. Calls Model::set, so every step performs full node-state comparison, not BagModel virtual dispatch. |
| ownership | Each generated string/Row is independently owned then separately stored by runtime/model. |
| failure | Date parse, allocations/native update/oracle assertions can fail after prior updates remain committed. |
| cost | rows+2 full native/model updates and exhaustive comparisons, plus O(256*rows) string generation/copies. |
| Design | [tests/support/weighted_bag_fixture.hpp](../../../../../tests/support/weighted_bag_fixture.hpp), [tests/unit/weighted_bag_test.cpp](../../../../../tests/unit/weighted_bag_test.cpp), [tests/unit/weighted_cursor_limits_test.cpp](../../../../../tests/unit/weighted_cursor_limits_test.cpp), [tests/unit/weighted_bag_oracle_driver.cpp](../../../../../tests/unit/weighted_bag_oracle_driver.cpp), [tests/reference/weighted_bag_oracle.py](../../../../../tests/reference/weighted_bag_oracle.py), [include/crown/runtime/weighted.hpp](../../../../../include/crown/runtime/weighted.hpp), [docs/weighted_enumeration.md](../../../../weighted_enumeration.md), [Refactor.md](../../../../../Refactor.md), [docs/code_review.md](../../../../code_review.md) |

## B0008

[Lines 51–63](../../../../../tests/support/weighted_bag_fixture.hpp#L51); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
inline PhysicalPlan disconnected_bag(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Build a nullary generalized root with a full Cartesian bag head. |
| inputs / outputs | G() children a(x),b(y), head x,y; optional structural_steps override. |
| invariants | Override requires indexed=true, as actual cursor-limit callers supply; no false+limit optional safety is promised. |
| ownership | Local ordinary source DTOs are owned; returned PhysicalPlan shares its actual immutable compiler control on copy. |
| failure | Ordinary allocation/compiler rejection propagates; no fake optimum/source/proof handles. |
| cost | Fixed plan DTO setup and lowering; Cartesian outputs arise at runtime/oracle enumeration. |
| Design | [tests/support/weighted_bag_fixture.hpp](../../../../../tests/support/weighted_bag_fixture.hpp), [tests/unit/weighted_bag_test.cpp](../../../../../tests/unit/weighted_bag_test.cpp), [tests/unit/weighted_cursor_limits_test.cpp](../../../../../tests/unit/weighted_cursor_limits_test.cpp), [tests/unit/weighted_bag_oracle_driver.cpp](../../../../../tests/unit/weighted_bag_oracle_driver.cpp), [tests/reference/weighted_bag_oracle.py](../../../../../tests/reference/weighted_bag_oracle.py), [include/crown/runtime/weighted.hpp](../../../../../include/crown/runtime/weighted.hpp), [docs/weighted_enumeration.md](../../../../weighted_enumeration.md), [Refactor.md](../../../../../Refactor.md), [docs/code_review.md](../../../../code_review.md) |

## B0010

[Lines 65–84](../../../../../tests/support/weighted_bag_fixture.hpp#L65); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
inline PhysicalPlan deep_bag(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Build a variable-length native chain for iterative cursor depth tests. |
| inputs / outputs | length&gt;=1; nonhidden nodes all x, hidden root x,y and descendants y; head x. |
| invariants | Trusted bounded positive length is used by callers. length0 produces an invalid rooted tree rejected by actual lowering, not an accepted empty case. |
| ownership | Local ordinary source DTOs are owned; returned PhysicalPlan shares its actual immutable compiler control on copy. |
| failure | Ordinary allocation/compiler rejection propagates; no fake optimum/source/proof handles. |
| cost | O(length) source/tree allocations and actual compiler validation/lowering; runtime traversal tested separately. |
| Design | [tests/support/weighted_bag_fixture.hpp](../../../../../tests/support/weighted_bag_fixture.hpp), [tests/unit/weighted_bag_test.cpp](../../../../../tests/unit/weighted_bag_test.cpp), [tests/unit/weighted_cursor_limits_test.cpp](../../../../../tests/unit/weighted_cursor_limits_test.cpp), [tests/unit/weighted_bag_oracle_driver.cpp](../../../../../tests/unit/weighted_bag_oracle_driver.cpp), [tests/reference/weighted_bag_oracle.py](../../../../../tests/reference/weighted_bag_oracle.py), [include/crown/runtime/weighted.hpp](../../../../../include/crown/runtime/weighted.hpp), [docs/weighted_enumeration.md](../../../../weighted_enumeration.md), [Refactor.md](../../../../../Refactor.md), [docs/code_review.md](../../../../code_review.md) |

## B0012

[Lines 86–97](../../../../../tests/support/weighted_bag_fixture.hpp#L86); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
inline Assignments native_assignments(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Independently join native input atoms in a selected component with optional fixed visible bindings. |
| inputs / outputs | Starts unit assignment weight1, skips generalized nodes, maps each native input row to scope and calls exhaustive join. |
| invariants | Uses admitted node IDs/input layout and bounded uint64 weights; no incremental cache/factor is read to derive expected multiplicities. |
| ownership | fixed is an owning by-value Assignment moved into private result; all intermediate maps/Values are ordinary owners. |
| failure | Invalid IDs/width, checked weight overflow or allocation failures propagate; native state is not changed. |
| cost | Potential Cartesian/exponential joins plus deep assignment/scalar copies; full local input scan per selected atom. |
| Design | [tests/support/weighted_bag_fixture.hpp](../../../../../tests/support/weighted_bag_fixture.hpp), [tests/unit/weighted_bag_test.cpp](../../../../../tests/unit/weighted_bag_test.cpp), [tests/unit/weighted_cursor_limits_test.cpp](../../../../../tests/unit/weighted_cursor_limits_test.cpp), [tests/unit/weighted_bag_oracle_driver.cpp](../../../../../tests/unit/weighted_bag_oracle_driver.cpp), [tests/reference/weighted_bag_oracle.py](../../../../../tests/reference/weighted_bag_oracle.py), [include/crown/runtime/weighted.hpp](../../../../../include/crown/runtime/weighted.hpp), [docs/weighted_enumeration.md](../../../../weighted_enumeration.md), [Refactor.md](../../../../../Refactor.md), [docs/code_review.md](../../../../code_review.md) |

## B0013

[Lines 98–102](../../../../../tests/support/weighted_bag_fixture.hpp#L98); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
inline std::vector<NodeId> all_nodes(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Copy compiled node IDs for the exhaustive whole-query oracle. |
| inputs / outputs | Iterates plan.nodes in its stored order and pushes each id. |
| invariants | Only actual admitted compiled IDs are returned, not guessed table IDs. |
| ownership | Return owns vector of scalar IDs; plan borrow ends with call. |
| failure | Vector allocation failures propagate. |
| cost | O(nodes) traversal and vector growth. |
| Design | [tests/support/weighted_bag_fixture.hpp](../../../../../tests/support/weighted_bag_fixture.hpp), [tests/unit/weighted_bag_test.cpp](../../../../../tests/unit/weighted_bag_test.cpp), [tests/unit/weighted_cursor_limits_test.cpp](../../../../../tests/unit/weighted_cursor_limits_test.cpp), [tests/unit/weighted_bag_oracle_driver.cpp](../../../../../tests/unit/weighted_bag_oracle_driver.cpp), [tests/reference/weighted_bag_oracle.py](../../../../../tests/reference/weighted_bag_oracle.py), [include/crown/runtime/weighted.hpp](../../../../../include/crown/runtime/weighted.hpp), [docs/weighted_enumeration.md](../../../../weighted_enumeration.md), [Refactor.md](../../../../../Refactor.md), [docs/code_review.md](../../../../code_review.md) |

## B0014

[Lines 103–113](../../../../../tests/support/weighted_bag_fixture.hpp#L103); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
inline Counts bag_oracle(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Compute projected bag multiplicities from a full independent native assignment join. |
| inputs / outputs | Constant routes yield empty or {empty:1}; tree joins all native atoms then copies ordered query.head fields and checked-sums equal output rows. |
| invariants | Preserves repeated/reordered fields and witness multiplicity, even for empty head. It does not collapse positive weights to Boolean truth. |
| ownership | Returned ordinary map deeply owns rows; intermediate assignments own independent values. |
| failure | Missing binding, numeric overflow/assertion and ordinary allocation failures propagate. |
| cost | Potential exponential full join plus projection/map aggregation and scalar copies; not a cursor implementation. |
| Design | [tests/support/weighted_bag_fixture.hpp](../../../../../tests/support/weighted_bag_fixture.hpp), [tests/unit/weighted_bag_test.cpp](../../../../../tests/unit/weighted_bag_test.cpp), [tests/unit/weighted_cursor_limits_test.cpp](../../../../../tests/unit/weighted_cursor_limits_test.cpp), [tests/unit/weighted_bag_oracle_driver.cpp](../../../../../tests/unit/weighted_bag_oracle_driver.cpp), [tests/reference/weighted_bag_oracle.py](../../../../../tests/reference/weighted_bag_oracle.py), [include/crown/runtime/weighted.hpp](../../../../../include/crown/runtime/weighted.hpp), [docs/weighted_enumeration.md](../../../../weighted_enumeration.md), [Refactor.md](../../../../../Refactor.md), [docs/code_review.md](../../../../code_review.md) |

## B0015

[Lines 114–116](../../../../../tests/support/weighted_bag_fixture.hpp#L114); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L114-L116:sha256:e87249013e16beae11902568e567719ac317d6bcbaee0e8854900d42a2fbd3fd
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Explain the adjacent source contract: Delete C* edges, then join each resulting component's actual native atoms. Seeding the visible assignment also handles a generalized unit-only component. |
| inputs / outputs | Human-readable source note in; no executable output or checked receipt. |
| invariants | This comment states context or a limitation. It does not itself enforce or prove the described behavior; use the adjacent implementation and its scoped contract. |
| ownership | Source text only; no object or resource lifetime is created. |
| failure | No runtime failure path in this comment; source encoding/comment syntax still belongs to compilation. |
| cost | No runtime operations from the comment. Any work described in the note belongs to the adjacent operation. |
| Design | [tests/support/weighted_bag_fixture.hpp](../../../../../tests/support/weighted_bag_fixture.hpp), [docs/weighted_enumeration.md](../../../../weighted_enumeration.md), [docs/code_review.md](../../../../code_review.md) |

## B0016

[Lines 117–123](../../../../../tests/support/weighted_bag_fixture.hpp#L117); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
inline std::vector<NodeId> component(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Find one local-factor component after deleting edges into C* nodes. |
| inputs / outputs | Starts root and appends descendants only while child.connex is false. |
| invariants | Valid admitted tree/C* flags are prerequisites; root itself remains included whether connex or not. |
| ownership | Return owns only scalar IDs; plan is borrowed. |
| failure | Invalid graph/index misuse is outside fixture contract; vector allocation failures propagate. |
| cost | O(component nodes+child edges) traversal and ordinary vector growth. |
| Design | [tests/support/weighted_bag_fixture.hpp](../../../../../tests/support/weighted_bag_fixture.hpp), [tests/unit/weighted_bag_test.cpp](../../../../../tests/unit/weighted_bag_test.cpp), [tests/unit/weighted_cursor_limits_test.cpp](../../../../../tests/unit/weighted_cursor_limits_test.cpp), [tests/unit/weighted_bag_oracle_driver.cpp](../../../../../tests/unit/weighted_bag_oracle_driver.cpp), [tests/reference/weighted_bag_oracle.py](../../../../../tests/reference/weighted_bag_oracle.py), [include/crown/runtime/weighted.hpp](../../../../../include/crown/runtime/weighted.hpp), [docs/weighted_enumeration.md](../../../../weighted_enumeration.md), [Refactor.md](../../../../../Refactor.md), [docs/code_review.md](../../../../code_review.md) |

## B0017

[Lines 124–131](../../../../../tests/support/weighted_bag_fixture.hpp#L124); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
inline std::uint64_t component_count(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Sum full native witness weights conditioned on fixed component bindings. |
| inputs / outputs | Calls native_assignments(plan,inputs,nodes,fixed) and checked-sums all resulting weights. |
| invariants | A generalized component with no native atoms returns unit1 if fixed binding stands; no cached factor supplies expected count. |
| ownership | fixed is owned by-value/moved; intermediate maps own ordinary data; scalar result has no lifetime borrow. |
| failure | Checked oracle overflow or allocation failures propagate. |
| cost | Whole component join and aggregation; potentially exponential, plus deep scalar copies. |
| Design | [tests/support/weighted_bag_fixture.hpp](../../../../../tests/support/weighted_bag_fixture.hpp), [tests/unit/weighted_bag_test.cpp](../../../../../tests/unit/weighted_bag_test.cpp), [tests/unit/weighted_cursor_limits_test.cpp](../../../../../tests/unit/weighted_cursor_limits_test.cpp), [tests/unit/weighted_bag_oracle_driver.cpp](../../../../../tests/unit/weighted_bag_oracle_driver.cpp), [tests/reference/weighted_bag_oracle.py](../../../../../tests/reference/weighted_bag_oracle.py), [include/crown/runtime/weighted.hpp](../../../../../include/crown/runtime/weighted.hpp), [docs/weighted_enumeration.md](../../../../weighted_enumeration.md), [Refactor.md](../../../../../Refactor.md), [docs/code_review.md](../../../../code_review.md) |

## B0018

[Lines 132–152](../../../../../tests/support/weighted_bag_fixture.hpp#L132); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
inline void compare_factors(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Compare cached local/visible factors with independent component joins. |
| inputs / outputs | Recomputes full subtree support; for actual records derives supported C* component count, groups visible keys and recomputes expected visible weights, then compares actual factor map. |
| invariants | Record membership is separately validated by Model::compare; actual record keys select checks but actual factor weights never determine expected weight. Hidden component atoms and unit-only cases are covered. |
| ownership | Actual Snapshot owns native views; ordinary exported rows/maps and recomputed Expected own independent copies. |
| failure | Lookup/precondition/overflow/allocation/assertion failures propagate; no repair. |
| cost | Full exhaustive recomputation plus repeated component joins per record/visible key and map exports; deliberately high oracle cost. |
| Design | [tests/support/weighted_bag_fixture.hpp](../../../../../tests/support/weighted_bag_fixture.hpp), [tests/unit/weighted_bag_test.cpp](../../../../../tests/unit/weighted_bag_test.cpp), [tests/unit/weighted_cursor_limits_test.cpp](../../../../../tests/unit/weighted_cursor_limits_test.cpp), [tests/unit/weighted_bag_oracle_driver.cpp](../../../../../tests/unit/weighted_bag_oracle_driver.cpp), [tests/reference/weighted_bag_oracle.py](../../../../../tests/reference/weighted_bag_oracle.py), [include/crown/runtime/weighted.hpp](../../../../../include/crown/runtime/weighted.hpp), [docs/weighted_enumeration.md](../../../../weighted_enumeration.md), [Refactor.md](../../../../../Refactor.md), [docs/code_review.md](../../../../code_review.md) |

## B0019

[Lines 153–153](../../../../../tests/support/weighted_bag_fixture.hpp#L153); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L153-L153:sha256:2343868178b294603c465daceec8c5b8c74e4eb6e104fcd09bdace72d858ecd4
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Explain the adjacent source contract: Account assertions cover actual emitted tuples; ordinary exported maps remain separate. |
| inputs / outputs | Human-readable source note in; no executable output or checked receipt. |
| invariants | This comment states context or a limitation. It does not itself enforce or prove the described behavior; use the adjacent implementation and its scoped contract. |
| ownership | Source text only; no object or resource lifetime is created. |
| failure | No runtime failure path in this comment; source encoding/comment syntax still belongs to compilation. |
| cost | No runtime operations from the comment. Any work described in the note belongs to the adjacent operation. |
| Design | [tests/support/weighted_bag_fixture.hpp](../../../../../tests/support/weighted_bag_fixture.hpp), [docs/weighted_enumeration.md](../../../../weighted_enumeration.md), [docs/code_review.md](../../../../code_review.md) |

## B0020

[Lines 154–166](../../../../../tests/support/weighted_bag_fixture.hpp#L154); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
inline Counts drain(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Consume a real weighted result cursor while checking emitted ownership/layout and multiplicity. |
| inputs / outputs | For every record checks same layout token, accounted tuple owner==cursor.owner, positive weight and unique ordinary projected key; finally exhausted&&!active. |
| invariants | Native tuple account assertion covers emitted output only. Ordinary exported result map is not funded/countable by the native account; duplicate tuples must already be aggregated by cursor. |
| ownership | Caller owns cursor/reader lease; each returned tuple remains valid through immediate export; map return owns deep ordinary copies. |
| failure | Cursor grants/native failures, ordinary export/map allocations or assertions propagate; cursor RAII is still responsible for lease cleanup on early failure. |
| cost | Full native cursor traversal plus O(log outputs) ordinary map insertions and scalar copies; no time/whole-account coverage claim. |
| Design | [tests/support/weighted_bag_fixture.hpp](../../../../../tests/support/weighted_bag_fixture.hpp), [tests/unit/weighted_bag_test.cpp](../../../../../tests/unit/weighted_bag_test.cpp), [tests/unit/weighted_cursor_limits_test.cpp](../../../../../tests/unit/weighted_cursor_limits_test.cpp), [tests/unit/weighted_bag_oracle_driver.cpp](../../../../../tests/unit/weighted_bag_oracle_driver.cpp), [tests/reference/weighted_bag_oracle.py](../../../../../tests/reference/weighted_bag_oracle.py), [include/crown/runtime/weighted.hpp](../../../../../include/crown/runtime/weighted.hpp), [docs/weighted_enumeration.md](../../../../weighted_enumeration.md), [Refactor.md](../../../../../Refactor.md), [docs/code_review.md](../../../../code_review.md) |

## B0021

[Lines 167–177](../../../../../tests/support/weighted_bag_fixture.hpp#L167); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
inline void compare_bag(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Check real bag cursor output, cached factors and release of the reader lease. |
| inputs / outputs | Computes whole-query bag oracle; snapshots/checks factors; obtains cursor, checks binding, drains/compares, requires runtime.ready and root_weight==checked expected sum. |
| invariants | Expected bag derives from independent model inputs; root/factor/native cursor are actual observations, not expected-weight inputs. |
| ownership | Local snapshot/cursor retain native owners; ordinary expected maps own copies; exhaustion releases actual reader lease. |
| failure | Native admission/traversal/ordinary allocation/oracle/assertion failure propagates; a prior committed update is not undone. |
| cost | Potential exponential oracle and repeated factor recomputations, snapshot capture and full real result traversal. |
| Design | [tests/support/weighted_bag_fixture.hpp](../../../../../tests/support/weighted_bag_fixture.hpp), [tests/unit/weighted_bag_test.cpp](../../../../../tests/unit/weighted_bag_test.cpp), [tests/unit/weighted_cursor_limits_test.cpp](../../../../../tests/unit/weighted_cursor_limits_test.cpp), [tests/unit/weighted_bag_oracle_driver.cpp](../../../../../tests/unit/weighted_bag_oracle_driver.cpp), [tests/reference/weighted_bag_oracle.py](../../../../../tests/reference/weighted_bag_oracle.py), [include/crown/runtime/weighted.hpp](../../../../../include/crown/runtime/weighted.hpp), [docs/weighted_enumeration.md](../../../../weighted_enumeration.md), [Refactor.md](../../../../../Refactor.md), [docs/code_review.md](../../../../code_review.md) |

## B0022

[Lines 178–184](../../../../../tests/support/weighted_bag_fixture.hpp#L178); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct BagModel:Model
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Extend independent node-state verification with complete bag-output verification. |
| inputs / outputs | Inherits Model construction; set calls base update/compare then compare_bag. |
| invariants | Native runtime remains move-only and ordinary model independent; no new runtime state/container is added to the engine. |
| ownership | Composite inherits actual Runtime ownership; ordinary Inputs remain deep-copy model data. |
| failure | Bag check can fail after base apply/model publication; no joint rollback guarantee. |
| cost | Base real update/exhaustive node verification plus full bag/factor/cursor verification. |
| Design | [tests/support/weighted_bag_fixture.hpp](../../../../../tests/support/weighted_bag_fixture.hpp), [tests/unit/weighted_bag_test.cpp](../../../../../tests/unit/weighted_bag_test.cpp), [tests/unit/weighted_cursor_limits_test.cpp](../../../../../tests/unit/weighted_cursor_limits_test.cpp), [tests/unit/weighted_bag_oracle_driver.cpp](../../../../../tests/unit/weighted_bag_oracle_driver.cpp), [tests/reference/weighted_bag_oracle.py](../../../../../tests/reference/weighted_bag_oracle.py), [include/crown/runtime/weighted.hpp](../../../../../include/crown/runtime/weighted.hpp), [docs/weighted_enumeration.md](../../../../weighted_enumeration.md), [Refactor.md](../../../../../Refactor.md), [docs/code_review.md](../../../../code_review.md) |

```text
using Model::Model;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Reuse actual Model admission for BagModel construction. |
| inputs / outputs | Inherited constructors accept admitted plan and weighted options. |
| invariants | Does not wrap/replace native admission or add fake owner grants. |
| ownership | Base stores real move-only runtime and independent ordinary Inputs. |
| failure | Same native/vector construction errors as base propagate. |
| cost | Exactly base constructor setup, no additional bag-state container. |
| Design | [tests/support/weighted_bag_fixture.hpp](../../../../../tests/support/weighted_bag_fixture.hpp), [tests/unit/weighted_bag_test.cpp](../../../../../tests/unit/weighted_bag_test.cpp), [tests/unit/weighted_cursor_limits_test.cpp](../../../../../tests/unit/weighted_cursor_limits_test.cpp), [tests/unit/weighted_bag_oracle_driver.cpp](../../../../../tests/unit/weighted_bag_oracle_driver.cpp), [tests/reference/weighted_bag_oracle.py](../../../../../tests/reference/weighted_bag_oracle.py), [include/crown/runtime/weighted.hpp](../../../../../include/crown/runtime/weighted.hpp), [docs/weighted_enumeration.md](../../../../weighted_enumeration.md), [Refactor.md](../../../../../Refactor.md), [docs/code_review.md](../../../../code_review.md) |

```text
w::Epoch set(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Verify bag semantics after the base weighted update. |
| inputs / outputs | Moves Row to Model::set, retains returned epoch, calls compare_bag and returns epoch. |
| invariants | Base update is already committed and node-verified before bag checks; failed later assertions cannot undo it. |
| ownership | Epoch local/return owns its real value members; native runtime and ordinary model live in base. |
| failure | Any base/native/oracle/cursor/assertion failure propagates without broad catch. |
| cost | One base full update check plus exhaustive bag/factor/cursor work; no per-primitive runtime overhead is introduced. |
| Design | [tests/support/weighted_bag_fixture.hpp](../../../../../tests/support/weighted_bag_fixture.hpp), [tests/unit/weighted_bag_test.cpp](../../../../../tests/unit/weighted_bag_test.cpp), [tests/unit/weighted_cursor_limits_test.cpp](../../../../../tests/unit/weighted_cursor_limits_test.cpp), [tests/unit/weighted_bag_oracle_driver.cpp](../../../../../tests/unit/weighted_bag_oracle_driver.cpp), [tests/reference/weighted_bag_oracle.py](../../../../../tests/reference/weighted_bag_oracle.py), [include/crown/runtime/weighted.hpp](../../../../../include/crown/runtime/weighted.hpp), [docs/weighted_enumeration.md](../../../../weighted_enumeration.md), [Refactor.md](../../../../../Refactor.md), [docs/code_review.md](../../../../code_review.md) |

## B0023

[Lines 185–185](../../../../../tests/support/weighted_bag_fixture.hpp#L185); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L185-L185:sha256:e3e0d6ed285ee7d6b125a50e4e786e09eff84b033609cd7064be9e446b1450b2
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Close the recorded declaration scopes in weighted_bag_fixture.hpp: namespace crown::weighted_test. |
| inputs / outputs | Preceding namespace, type or initializer declarations in; completed lexical boundary out. |
| invariants | Brace-opening context is recorded in root-scope-context-v1.json. These are declaration/initializer boundaries, not an independent update, validation or recovery operation. |
| ownership | Enclosing objects and borrowed fields keep their declared ownership. This punctuation creates no new owner. |
| failure | Malformed scope syntax is a compile error. Any initializer/constructor failure belongs to the enclosing object declaration. |
| cost | No separate loop, guard or engine call is introduced by the delimiter; enclosing initialization and object lifetime still have their actual costs. |
| Design | [tests/support/weighted_bag_fixture.hpp](../../../../../tests/support/weighted_bag_fixture.hpp), [docs/weighted_enumeration.md](../../../../weighted_enumeration.md), [docs/code_review.md](../../../../code_review.md) |
