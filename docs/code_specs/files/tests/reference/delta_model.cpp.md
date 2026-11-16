# `tests/reference/delta_model.cpp` — block usage map

[Source](../../../../../tests/reference/delta_model.cpp) · [Source index](../../../README.md) · [Subsystem contracts](../../../subsystem_contracts.md) · [Reviewed primitives](../../../primitives.md)

Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection.

Snapshot SHA-256: `57bf07b92bded65d87585e04f366ec2a6a27d54262a4b7f6fe905eeb72514e1a`. 209 lines partitioned into 18 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [tests](../../../subsystem_contracts.md#tests). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/code_review.md](../../../../code_review.md), [docs/reference_fuzz.md](../../../../reference_fuzz.md), [docs/task_ledger.md](../../../../task_ledger.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–13](../../../../../tests/reference/delta_model.cpp#L1) | Imports dependencies; declares namespace scope; declares aliases; declares values/defaults or compile-time conditions. |  · [reviewed contract](#b0001) |
| [B0002 · 14–16](../../../../../tests/reference/delta_model.cpp#L14) | Callable definition: void require(bool condition,std::string_view message) | calls Error, std::string; guard void require(bool condition,std::string_view message) { · [reviewed contract](#b0002) |
| [B0003 · 17–19](../../../../../tests/reference/delta_model.cpp#L17) | Callable definition: void transition_require(bool condition,std::string_view message) | calls Error, std::string · [reviewed contract](#b0003) |
| [B0004 · 20–24](../../../../../tests/reference/delta_model.cpp#L20) | Callable definition: std::vector&lt;VariableId&gt; intersection(const VariableSet& left,const VariableSet& right) | calls std::set_intersection, begin, end, std::back_inserter; returns result · [reviewed contract](#b0004) |
| [B0005 · 25–29](../../../../../tests/reference/delta_model.cpp#L25) | Callable definition: Assignment assignment(const Row& row,const std::vector&lt;VariableId&gt;& scope) | calls require, size, emplace; guard require(row.size()==scope.size(),"factor row width differs from its scope"); Assignment result;; returns result; growth emplace; 1 loop sites · [reviewed contract](#b0005) |
| [B0006 · 30–34](../../../../../tests/reference/delta_model.cpp#L30) | Callable definition: Row project(const Assignment& row,const std::vector&lt;VariableId&gt;& scope) | calls reserve, size, find, require; guard for (const auto variable : scope) { const auto found=row.find(variable); require(found!=row.end(),"…; returns result; growth push_back, reserve; 1 loop sites · [reviewed contract](#b0006) |
| [B0007 · 35–46](../../../../../tests/reference/delta_model.cpp#L35) | Callable definition: Assignments join(const Assignments& left,const Assignments& right) | calls emplace, insert, std::move; returns result; growth emplace, insert; 3 loop sites · [reviewed contract](#b0007) |
| [B0008 · 47–53](../../../../../tests/reference/delta_model.cpp#L47) | Callable definition: bool compatible(const Row& a,const Factor& left,const Row& b,const Factor& right) | calls assignment, size, find, end; returns false; true; 1 loop sites · [reviewed contract](#b0008) |
| [B0009 · 54–84](../../../../../tests/reference/delta_model.cpp#L54) | Callable definition: void validate_snapshot(const Snapshot& snapshot) | calls empty, require, head, begin; guard if (snapshot.factors.empty()) { require(!snapshot.constant_answer \|\| snapshot.head.empty(),"true co…; growth emplace, insert; 5 loop sites · [reviewed contract](#b0009) |
| [B0010 · 85–86](../../../../../tests/reference/delta_model.cpp#L85) | Closes surrounding scope/type. | source comment (unverified): // namespace · [reviewed contract](#b0010) |
| [B0011 · 87–133](../../../../../tests/reference/delta_model.cpp#L87) | Callable definition: Snapshot recompute(const Catalog& catalog,const Query& query,const FreeConnexTree& tree,const std::vector&lt;Relation&gt;& native_rows) | calls planner::validate_tree, require, size, push_back; guard require(checked.valid,"native model requires a verified free-connex tree");; returns result; result; growth emplace, insert, push_back; 9 loop sites; source comment (unverified): // Deliberately full subtree assignments: no maintained survivor/support · [reviewed contract](#b0011) |
| [B0012 · 134–134](../../../../../tests/reference/delta_model.cpp#L134) | Explanatory comments or spacing. |  |
| [B0013 · 135–149](../../../../../tests/reference/delta_model.cpp#L135) | Callable definition: std::vector&lt;Row&gt; enumerate(const Snapshot& snapshot,const FixedAssignment& fixed) | calls validate_snapshot, head, begin, end; guard for (const auto& \[variable,value\] : fixed) { static_cast&lt;void&gt;(value); require(head.contains(variab…; returns snapshot.constant_answer?std::vector&lt;Row&gt;{Row{}}:std::vector&lt;Row&gt;{}; result; growth insert, push_back; 4 loop sites · [reviewed contract](#b0013) |
| [B0014 · 150–150](../../../../../tests/reference/delta_model.cpp#L150) | Explanatory comments or spacing. |  |
| [B0015 · 151–166](../../../../../tests/reference/delta_model.cpp#L151) | Callable definition: std::vector&lt;Relation&gt; bootstrap_live(const Snapshot& snapshot) | calls validate_snapshot, result, size, require; guard require(std::any_of(child.rows.begin(),child.rows.end(),\[&\](const Row& value) { return compatible(r…; returns compatible(row,parent,value,child); compatible(value,parent,row,child); growth insert; 3 loop sites; source comment (unverified): // This precondition follows from the drained S/P/E invariant. An · [reviewed contract](#b0015) |
| [B0016 · 167–167](../../../../../tests/reference/delta_model.cpp#L167) | Explanatory comments or spacing. |  |
| [B0017 · 168–208](../../../../../tests/reference/delta_model.cpp#L168) | Callable definition: Transition partition(const Snapshot& before,const Snapshot& after,SetOperation operation) | calls transition_require, validate_snapshot, size, resize; guard require(!fragment.candidates.empty(),"live E witness has no whole-query completion");; returns result; growth emplace, insert, push_back, resize; 8 loop sites · [reviewed contract](#b0017) |
| [B0018 · 209–209](../../../../../tests/reference/delta_model.cpp#L209) | Closes surrounding scope/type. | source comment (unverified): // namespace crown::reference::delta · [reviewed contract](#b0018) |

## B0001

[Lines 1–13](../../../../../tests/reference/delta_model.cpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L1-L13:sha256:c97d7dfde76a3766c401a26f2d78c6c61518e97a7ca61312bcaa62344574b6f2
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Prepare delta_model.cpp: include "delta_model.hpp", "crown/api/error.hpp", "crown/planner/verify.hpp", &lt;algorithm&gt;, &lt;iterator&gt;, &lt;set&gt;, &lt;utility&gt;; bind local aliases/name imports. |
| inputs / outputs | Compiler-visible dependencies, names and the recorded declarations in; declarations available to the following fixture/CLI/example definitions out. |
| invariants | Declarations are scoped to this source/header and its selected ABI. Included code has its own effects; names and editable fixture values do not confer proof, admission or publication authority. |
| ownership | Aliases/includes do not create a query owner. Pointers/references/views are non-owning. Containers own their elements, which can themselves be borrowed pointers or numeric IDs. Only documented owning shared-control handles retain controls; IDs/slot-handle values do not independently keep an arena/runtime alive. |
| failure | Missing headers, ill-formed names/types, failed static assertions or active #error directives stop compilation. No runtime rejection/rollback mechanism is implemented by aliases or function prototypes. |
| cost | Preprocessing and type/constraint instantiation cost compilation. Alias/prototype syntax does not invoke the declared operation; any included definitions keep their own initialization effects. |
| Design | [tests/reference/delta_model.cpp](../../../../../tests/reference/delta_model.cpp), [docs/ordered_delta.md](../../../../ordered_delta.md), [docs/code_review.md](../../../../code_review.md) |

## B0002

[Lines 14–16](../../../../../tests/reference/delta_model.cpp#L14); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void require(bool condition,std::string_view message)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Reject an invalid materializing delta-model precondition with its distinct code. |
| inputs / outputs | If condition is false, constructs Error(invalid_delta_model, copied message); otherwise returns. |
| invariants | Used for snapshot shape, binding/projected-completion and reference invariant failures, not semantic production rejection. |
| ownership | Message view is borrowed on entry and copied only into the thrown Error. |
| failure | Error/message allocation may itself throw; there is no fixed/noexcept diagnostic guarantee. |
| cost | Fixed successful guard; failure copies message and constructs an exception. |
| Design | [tests/reference/delta_model.cpp](../../../../../tests/reference/delta_model.cpp), [include/crown/api/error.hpp](../../../../../include/crown/api/error.hpp) |

## B0003

[Lines 17–19](../../../../../tests/reference/delta_model.cpp#L17); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void transition_require(bool condition,std::string_view message)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Distinguish malformed before/after transition input from a malformed model snapshot. |
| inputs / outputs | Throws Error(invalid_delta_transition, copied message) for a false condition. |
| invariants | Covers polarity, query/factor compatibility and declared-direction monotonicity only; it does not authenticate physical history. |
| ownership | Copies a borrowed message into an ordinary owning exception on failure. |
| failure | Allocation/native standard failures propagate; no exception is translated to a success status. |
| cost | Fixed guard on success; message/exception work on failure. |
| Design | [tests/reference/delta_model.cpp](../../../../../tests/reference/delta_model.cpp), [include/crown/api/error.hpp](../../../../../include/crown/api/error.hpp) |

## B0004

[Lines 20–24](../../../../../tests/reference/delta_model.cpp#L20); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::vector<VariableId> intersection(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Produce sorted common variable IDs for visible scopes and separators. |
| inputs / outputs | Uses set_intersection on two VariableSets and appends to a new vector. |
| invariants | Input set ordering supplies sorted unique output; this is ID intersection, not join-row evaluation. |
| ownership | Borrows both sets and returns an owning ordinary vector. |
| failure | Container allocation failures propagate without mutating inputs. |
| cost | Linear ordered-set traversal in both input cardinalities plus output storage. |
| Design | [tests/reference/delta_model.cpp](../../../../../tests/reference/delta_model.cpp), [include/crown/ir/model.hpp](../../../../../include/crown/ir/model.hpp) |

## B0005

[Lines 25–29](../../../../../tests/reference/delta_model.cpp#L25); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Assignment assignment(const Row& row,
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Map one complete factor row to its scope variable IDs. |
| inputs / outputs | Requires equal row/scope width and inserts each scope/value pair into an owning ordered Assignment. |
| invariants | Repeated variable IDs reject even when values are equal. Exact Value kinds/payload are retained. |
| ownership | Copies each input Value into the returned map; input rows/scopes are borrowed. |
| failure | Shape/duplicate IDs raise invalid_delta_model; map/value allocation failures propagate. |
| cost | O(width log width) ordered insertions with scalar copying; used repeatedly by the slow reference joins. |
| Design | [tests/reference/delta_model.cpp](../../../../../tests/reference/delta_model.cpp), [tests/reference/delta_model.hpp](../../../../../tests/reference/delta_model.hpp) |

## B0006

[Lines 30–34](../../../../../tests/reference/delta_model.cpp#L30); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Row project(const Assignment& row,
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Project an assignment to an explicitly ordered scope/head, including repeated output positions. |
| inputs / outputs | Reserves requested width, requires every variable bound and copies its Value in scope order. |
| invariants | Output order follows the supplied vector; unlike factor scope validation, this helper permits repeated head fields. |
| ownership | Borrows the map and returns an owning Row with copied scalar payloads. |
| failure | Unbound variables raise invalid_delta_model; reserve/value-copy failures propagate. |
| cost | One map lookup per output position plus complete scalar-copy cost. |
| Design | [tests/reference/delta_model.cpp](../../../../../tests/reference/delta_model.cpp), [docs/semantics.md §Answers and Boolean queries](../../../../semantics.md) |

## B0007

[Lines 35–46](../../../../../tests/reference/delta_model.cpp#L35); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Assignments join(const Assignments& left,
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Compute a literal materialized natural join of two assignment sets. |
| inputs / outputs | Examines every pair, copies the left map, merges right bindings if equal on common variables and inserts compatible combinations into an exact set. |
| invariants | Conflicting shared bindings reject that pair; exact set insertion deduplicates full assignments. No maintained support/survivor counter is consulted. |
| ownership | Returned maps/Values own all payload. Per-pair combined maps are temporary and unwind independently of input sets. |
| failure | Ordinary allocation/comparison errors propagate; inputs remain unchanged. |
| cost | Cartesian pair traversal with map copy/merge and set insertion costs; can be exponential across repeated joins. It is an oracle, not a bounded-delay algorithm. |
| Design | [tests/reference/delta_model.cpp](../../../../../tests/reference/delta_model.cpp), [docs/semantics.md §Answers and Boolean queries](../../../../semantics.md) |

## B0008

[Lines 47–53](../../../../../tests/reference/delta_model.cpp#L47); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
bool compatible(const Row& a,
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Check equality on common visible variables for a parent/child row pair. |
| inputs / outputs | Builds an Assignment for left row/scope, then compares each right shared-variable value. |
| invariants | Callers first validate both factor widths; this private helper indexes the right row under that precondition. Nonshared variables do not constrain compatibility. |
| ownership | Borrows both Rows/Factors but allocates a temporary owning left map on each call. |
| failure | Left shape validation or allocation can throw; a value conflict returns false. |
| cost | Map construction plus one lookup per right variable; repeated semijoin scans incur this real temporary cost. |
| Design | [tests/reference/delta_model.cpp](../../../../../tests/reference/delta_model.cpp), [tests/reference/delta_model.hpp](../../../../../tests/reference/delta_model.hpp) |

## B0009

[Lines 54–84](../../../../../tests/reference/delta_model.cpp#L54); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void validate_snapshot(const Snapshot& snapshot)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Validate the public visible-factor data before enumeration/live/transition computation. |
| inputs / outputs | Checks constant shape or unique node IDs, root/parent order, scope ordering, row widths/types, head coverage and running intersection using occurrence/edge counts. |
| invariants | Only visible head variables appear in factor scopes. Scalar type consistency is inferred from present rows; this data check does not import an original query/native owner or prove downward totality. |
| ownership | Borrows the snapshot and owns temporary sets/maps for validation. |
| failure | Violations raise invalid_delta_model; ordinary container failures propagate. There is no independent resource grant here. |
| cost | Traverses all factors/scopes/row cells with ordered-set/map work; temporary metadata scales with variables and nodes. |
| Design | [tests/reference/delta_model.cpp](../../../../../tests/reference/delta_model.cpp), [tests/reference/delta_model.hpp](../../../../../tests/reference/delta_model.hpp) |

## B0010

[Lines 85–86](../../../../../tests/reference/delta_model.cpp#L85); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L85-L86:sha256:c2bd7638f09d52cb034ed574f539304035fc6fab162bf8d5fa20a35d8c7288a1
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Close the recorded declaration scopes in delta_model.cpp: namespace (anonymous). |
| inputs / outputs | Preceding namespace, type or initializer declarations in; completed lexical boundary out. |
| invariants | Brace-opening context is recorded in root-scope-context-v1.json. These are declaration/initializer boundaries, not an independent update, validation or recovery operation. |
| ownership | Enclosing objects and borrowed fields keep their declared ownership. This punctuation creates no new owner. |
| failure | Malformed scope syntax is a compile error. Any initializer/constructor failure belongs to the enclosing object declaration. |
| cost | No separate loop, guard or engine call is introduced by the delimiter; enclosing initialization and object lifetime still have their actual costs. |
| Design | [tests/reference/delta_model.cpp](../../../../../tests/reference/delta_model.cpp), [docs/ordered_delta.md](../../../../ordered_delta.md), [docs/code_review.md](../../../../code_review.md) |

## B0011

[Lines 87–133](../../../../../tests/reference/delta_model.cpp#L87); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Snapshot recompute(const Catalog& catalog,
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Reconstruct visible E factors by full subtree joins from admitted native rows. |
| inputs / outputs | Shares planner::validate_tree, checks native_rows size, builds parent-before-child order, joins complete native/generalized subtree assignments bottom-up and projects the root-connected visible region. |
| invariants | Native scopes use ascending variable IDs and exact query types; generalized nodes have no external rows. Root may contain hidden variables; visible factors use scope∩head. Relational recomputation is separate, while structural validation intentionally shares P02. |
| ownership | Copies native Values into ordinary materialized assignment sets and returned factors; retains no native runtime handle/counter/journal. |
| failure | Invalid tree/rows/type/generalized input raises invalid_delta_model; allocation may abort before an owning result escapes. |
| cost | Full subtree Cartesian joins and projections can use very large time/memory. This intentionally slow reference path does not inherit P1 runtime bounds. |
| Design | [tests/reference/delta_model.cpp](../../../../../tests/reference/delta_model.cpp), [docs/delta_runtime.md](../../../../delta_runtime.md), [docs/planner_proofs.md §Independent tree verification (P02)](../../../../planner_proofs.md) |

## B0013

[Lines 135–149](../../../../../tests/reference/delta_model.cpp#L135); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::vector<Row> enumerate(const Snapshot& snapshot,
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Materialize complete visible-head rows subject to optional visible fixed bindings. |
| inputs / outputs | Validates snapshot/fixed variable IDs, starts with the fixed Assignment, joins every factor and projects original ordered head; a true empty constant returns one empty row. |
| invariants | Fixed IDs must be in the visible head; this is not D02 hidden-variable binding. Full witnesses below projected E factors have already been eliminated. |
| ownership | Returns owning Row vector after temporary complete Assignment sets die; no cursor lease or input view survives. |
| failure | Malformed snapshot/fixed IDs raise invalid_delta_model; allocation/Value-copy failures propagate. |
| cost | Materializes full joins even when a lazy native cursor would be cheaper; output head width/repeated positions add copy work. |
| Design | [tests/reference/delta_model.cpp](../../../../../tests/reference/delta_model.cpp), [docs/result_cursors.md](../../../../result_cursors.md), [docs/semantics.md §Answers and Boolean queries](../../../../semantics.md) |

## B0015

[Lines 151–166](../../../../../tests/reference/delta_model.cpp#L151); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::vector<Relation> bootstrap_live(const Snapshot& snapshot)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Compute live factors by a top-down semijoin under the maintained E downward-totality precondition. |
| inputs / outputs | Validates snapshot, copies root rows, requires every parent E row to match some child row, then keeps child rows matching already-live parent rows. |
| invariants | Checks downward totality against all parent E rows, not only live parent rows. Arbitrary factor joins lacking this property reject; this is not projection of a global answer relation. |
| ownership | Owns returned live row sets; repeated compatibility checks own temporary Assignment maps. |
| failure | A non-total child separator raises invalid_delta_model; allocation failures propagate. |
| cost | Nested parent/child row scans per edge plus map-based compatibility; row-width and materialization costs are explicit. |
| Design | [tests/reference/delta_model.cpp](../../../../../tests/reference/delta_model.cpp), [docs/delta_runtime.md](../../../../delta_runtime.md) |

## B0017

[Lines 168–208](../../../../../tests/reference/delta_model.cpp#L168); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Transition partition(const Snapshot& before,
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Partition one same-sign logical factor-membership step by earliest changed factor ownership. |
| inputs / outputs | Validates compatible snapshots/polarity/monotonicity, computes changed/live sets, enumerates each live witness in after(insert) or before(erase), and accepts candidates absent from every earlier changed-factor key. |
| invariants | Snapshot head/node/parent/scope schemas must match. It validates no physical input history or mixed-batch semantics. Raw accepted rows are appended without final dedup so ownership mistakes remain visible. |
| ownership | Owns all changed/live/fragments/raw rows in a local Transition; reads only public materialized snapshots, never native state/cursors. |
| failure | Bad transition shape uses invalid_delta_transition; model/live/completion invariants use invalid_delta_model. Partial owning output unwinds on allocation failure. |
| cost | Repeated live bootstraps, full join enumeration per witness and earlier-factor probes can be expensive. Metrics count selected events with fixture-sized unchecked integers, not all CPU or a work allowance. |
| Design | [tests/reference/delta_model.cpp](../../../../../tests/reference/delta_model.cpp), [docs/delta_runtime.md §Views and prefix identity](../../../../delta_runtime.md), [tests/reference/delta_model.hpp](../../../../../tests/reference/delta_model.hpp) |

## B0018

[Lines 209–209](../../../../../tests/reference/delta_model.cpp#L209); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L209-L209:sha256:0a5a4838291cf26f99d4040c3ad41648b9b6306abcd99216e51033f7f2590389
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Close the recorded declaration scopes in delta_model.cpp: namespace crown::reference::delta. |
| inputs / outputs | Preceding namespace, type or initializer declarations in; completed lexical boundary out. |
| invariants | Brace-opening context is recorded in root-scope-context-v1.json. These are declaration/initializer boundaries, not an independent update, validation or recovery operation. |
| ownership | Enclosing objects and borrowed fields keep their declared ownership. This punctuation creates no new owner. |
| failure | Malformed scope syntax is a compile error. Any initializer/constructor failure belongs to the enclosing object declaration. |
| cost | No separate loop, guard or engine call is introduced by the delimiter; enclosing initialization and object lifetime still have their actual costs. |
| Design | [tests/reference/delta_model.cpp](../../../../../tests/reference/delta_model.cpp), [docs/ordered_delta.md](../../../../ordered_delta.md), [docs/code_review.md](../../../../code_review.md) |
