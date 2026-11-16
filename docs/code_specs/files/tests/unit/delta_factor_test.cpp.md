# `tests/unit/delta_factor_test.cpp` — block usage map

[Source](../../../../../tests/unit/delta_factor_test.cpp) · [Source index](../../../README.md) · [Subsystem contracts](../../../subsystem_contracts.md) · [Reviewed primitives](../../../primitives.md)

Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection.

Snapshot SHA-256: `625d7172a4f80e0e2de27757e5086f88a23100b58671c01a465606432dd18228`. 181 lines partitioned into 13 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [tests](../../../subsystem_contracts.md#tests). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/code_review.md](../../../../code_review.md), [docs/reference_fuzz.md](../../../../reference_fuzz.md), [docs/task_ledger.md](../../../../task_ledger.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–10](../../../../../tests/unit/delta_factor_test.cpp#L1) | Imports dependencies; declares namespace scope; declares aliases. |  · [reviewed contract](#b0001) |
| [B0002 · 11–11](../../../../../tests/unit/delta_factor_test.cpp#L11) | Callable definition: void check(bool condition,const std::string& message) | calls std::runtime_error; guard void check(bool condition,const std::string& message) { if (!condition) throw std::runtime_error(me… · [reviewed contract](#b0002) |
| [B0003 · 12–16](../../../../../tests/unit/delta_factor_test.cpp#L12) | Callable definition: template&lt;class Action&gt; void error(Action&& action,std::string_view code) | calls action, check, code, std::runtime_error; guard catch (const Error& failure) { check(failure.code()==code,"unexpected error "+failure.code()); retu… · [reviewed contract](#b0003) |
| [B0004 · 17–17](../../../../../tests/unit/delta_factor_test.cpp#L17) | Callable definition: Row row(std::initializer_list&lt;std::int64_t&gt; values) | calls emplace_back; returns result; growth emplace_back; 1 loop sites · [reviewed contract](#b0004) |
| [B0005 · 18–25](../../../../../tests/unit/delta_factor_test.cpp#L18) | Callable definition: Relation drain(SupportRuntime::ResultCursor cursor) | calls next, check, layout, same_token; guard check(tuple-&gt;layout().same_token(cursor.layout()),"factor result layout token");; returns result; growth insert; 1 loop sites · [reviewed contract](#b0005) |
| [B0006 · 26–34](../../../../../tests/unit/delta_factor_test.cpp#L26) | Callable definition: PhysicalPlan plan() | calls planner::lower_tree; returns planner::lower_tree(catalog,query,tree) · [reviewed contract](#b0006) |
| [B0007 · 35–54](../../../../../tests/unit/delta_factor_test.cpp#L35) | Callable definition: void unlive_factor() | calls runtime, plan, apply, row; guard check(!view.has_answer(),"unlive child made global truth true");; growth insert · [reviewed contract](#b0007) |
| [B0008 · 55–88](../../../../../tests/unit/delta_factor_test.cpp#L55) | Callable definition: void whole_epoch_and_rollback() | calls runtime, plan, apply, row; guard check(pending.stage(NodeId{0},row({1})),"first erase stage");; growth insert · [reviewed contract](#b0008) |
| [B0009 · 89–107](../../../../../tests/unit/delta_factor_test.cpp#L89) | Callable definition: void nullary_and_outside() | calls runtime, planner::lower_tree, apply, row; guard check(drain(view.visible_keys(NodeId{0}))==Relation{Row{}},"nullary E was not projected to one key"…; growth insert · [reviewed contract](#b0009) |
| [B0010 · 108–145](../../../../../tests/unit/delta_factor_test.cpp#L108) | Callable definition: std::uint64_t eager_cost(std::size_t count) | calls runtime, plan, apply, row; guard check(!input.active(),"maintenance epoch produced output");; returns scanned; growth insert; 1 loop sites · [reviewed contract](#b0010) |
| [B0011 · 146–171](../../../../../tests/unit/delta_factor_test.cpp#L146) | Callable definition: void typed_projection() | calls runtime, planner::lower_tree, Date::parse, Decimal::parse; guard check(inserted.metrics().spool_bytes&gt;=80+64+expected.size()*sizeof(Value)+sizeof(SignedResult),"wid…; growth insert · [reviewed contract](#b0011) |
| [B0012 · 172–172](../../../../../tests/unit/delta_factor_test.cpp#L172) | Closes surrounding scope/type. | source comment (unverified): // namespace · [reviewed contract](#b0012) |
| [B0013 · 173–181](../../../../../tests/unit/delta_factor_test.cpp#L173) | Callable definition: int main() | calls unlive_factor, whole_epoch_and_rollback, nullary_and_outside, typed_projection; guard check(larger&gt;small,"eager no-delta scan cost did not grow with E");; returns 1 · [reviewed contract](#b0013) |

## B0001

[Lines 1–10](../../../../../tests/unit/delta_factor_test.cpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L1-L10:sha256:45551a60b662790819cc2fd2026fcf00eecb3ab5d34c54f7977d6fae7908a211
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Prepare delta_factor_test.cpp: include "crown/api/error.hpp", "crown/planner/lower.hpp", "crown/runtime/delta.hpp", &lt;iostream&gt;, &lt;stdexcept&gt;, &lt;string&gt;; bind local aliases/name imports. |
| inputs / outputs | Compiler-visible dependencies, names and the recorded declarations in; declarations available to the following fixture/CLI/example definitions out. |
| invariants | Declarations are scoped to this source/header and its selected ABI. Included code has its own effects; names and editable fixture values do not confer proof, admission or publication authority. |
| ownership | Aliases/includes do not create a query owner. Pointers/references/views are non-owning. Containers own their elements, which can themselves be borrowed pointers or numeric IDs. Only documented owning shared-control handles retain controls; IDs/slot-handle values do not independently keep an arena/runtime alive. |
| failure | Missing headers, ill-formed names/types, failed static assertions or active #error directives stop compilation. No runtime rejection/rollback mechanism is implemented by aliases or function prototypes. |
| cost | Preprocessing and type/constraint instantiation cost compilation. Alias/prototype syntax does not invoke the declared operation; any included definitions keep their own initialization effects. |
| Design | [tests/unit/delta_factor_test.cpp](../../../../../tests/unit/delta_factor_test.cpp), [docs/ordered_delta.md](../../../../ordered_delta.md), [docs/code_review.md](../../../../code_review.md) |

## B0002

[Lines 11–11](../../../../../tests/unit/delta_factor_test.cpp#L11); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void check(bool condition,const std::string& message) { if (!condition) throw std::runtime_error(message); }

```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Assertion helper for delta-factor checks. |
| inputs / outputs | Accepts a Boolean and const std::string reference; throws std::runtime_error with that text only when false. |
| invariants | Call-site concatenations and literal-to-string conversion occur before entry even when the condition passes. |
| ownership | Borrows the already constructed message; any thrown exception owns its diagnostic. |
| failure | False throws and no error is caught here. |
| cost | One branch in the helper. Passing call-site std::string construction is separate and can allocate. |
| Design | [tests/unit/delta_factor_test.cpp](../../../../../tests/unit/delta_factor_test.cpp), [include/crown/runtime/support.hpp](../../../../../include/crown/runtime/support.hpp), [include/crown/runtime/delta.hpp](../../../../../include/crown/runtime/delta.hpp), [src/runtime/support.cpp](../../../../../src/runtime/support.cpp), [docs/indexed_storage.md](../../../../indexed_storage.md) |

## B0003

[Lines 12–16](../../../../../tests/unit/delta_factor_test.cpp#L12); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
template<class Action> void error(Action&& action,std::string_view code) {
  try { action(); }
  catch (const Error& failure) { check(failure.code()==code,"unexpected error "+failure.code()); return; }
  throw std::runtime_error("expected error "+std::string(code));
}

```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Assert a specified CROWN Error code. |
| inputs / outputs | Binds Action&& but invokes the named action() lvalue; catches crown::Error and compares its code with a borrowed string_view. |
| invariants | A matching CROWN error returns; mismatch checks fail, and normal action return triggers the expected-error runtime_error. |
| ownership | Action captures and error-code view are caller-owned; no runtime/query object is retained by the wrapper. |
| failure | Only crown::Error is caught. Runtime_error from the checks and all other exception types propagate. |
| cost | At most one action invocation and one code comparison. Diagnostic string construction is on the failure path here; no cost counter is measured. |
| Design | [tests/unit/delta_factor_test.cpp](../../../../../tests/unit/delta_factor_test.cpp), [include/crown/runtime/support.hpp](../../../../../include/crown/runtime/support.hpp), [include/crown/runtime/delta.hpp](../../../../../include/crown/runtime/delta.hpp), [src/runtime/support.cpp](../../../../../src/runtime/support.cpp), [docs/indexed_storage.md](../../../../indexed_storage.md) |

## B0004

[Lines 17–17](../../../../../tests/unit/delta_factor_test.cpp#L17); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Row row(std::initializer_list<std::int64_t> values) { Row result; for (const auto value : values) result.emplace_back(value); return result; }

```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Build an integer Row from an initializer list. |
| inputs / outputs | Copies each int64_t in an initializer_list into a Row and returns the Row value. |
| invariants | Input order and multiplicity are preserved; the helper performs no tuple-layout or scalar-type validation. |
| ownership | Initializer-list elements are borrowed for the call; returned Row owns its scalar values. |
| failure | Allocation failure during vector growth propagates; no CROWN error is caught. |
| cost | One emplace_back per input value and storage proportional to row width; callers often use it for two-column literals. |
| Design | [tests/unit/delta_factor_test.cpp](../../../../../tests/unit/delta_factor_test.cpp), [include/crown/runtime/support.hpp](../../../../../include/crown/runtime/support.hpp), [include/crown/runtime/delta.hpp](../../../../../include/crown/runtime/delta.hpp), [src/runtime/support.cpp](../../../../../src/runtime/support.cpp), [docs/indexed_storage.md](../../../../indexed_storage.md) |

## B0005

[Lines 18–25](../../../../../tests/unit/delta_factor_test.cpp#L18); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Relation drain(SupportRuntime::ResultCursor cursor) {
  Relation result;
  while (auto tuple=cursor.next()) {
    check(tuple->layout().same_token(cursor.layout()),"factor result layout token");
    check(result.insert(crown::storage::export_row(tuple->values())).second,"duplicate factor key");
  }
  return result;
}

```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Consume a cursor into an owning Relation while checking layout token and uniqueness. |
| inputs / outputs | Takes a ResultCursor by value, loops next() until empty, checks each result layout token, exports Tuple values into a Relation, and rejects duplicates. |
| invariants | The local cursor is drained to completion. It does not expose the cursor or check a separate active-state flag after exhaustion. |
| ownership | Owns the cursor handle passed in; Relation owns exported Rows and is returned by value. |
| failure | Tuple/layout or check failures propagate; duplicate or changed layout throws std::runtime_error. |
| cost | One next/export/set insertion per result. Row conversion and Relation search/insertion work depend on output size and values; no universal bound is asserted. |
| Design | [tests/unit/delta_factor_test.cpp](../../../../../tests/unit/delta_factor_test.cpp), [include/crown/runtime/support.hpp](../../../../../include/crown/runtime/support.hpp), [include/crown/runtime/delta.hpp](../../../../../include/crown/runtime/delta.hpp), [src/runtime/support.cpp](../../../../../src/runtime/support.cpp), [docs/indexed_storage.md](../../../../indexed_storage.md) |

## B0006

[Lines 26–34](../../../../../tests/unit/delta_factor_test.cpp#L26); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
PhysicalPlan plan() {
  Catalog catalog{1,{{"r",{{"x",ScalarType::int64}}},{"s",{{"x",ScalarType::int64},{"y",ScalarType::int64}}}}};
  Query query{{{"x",ScalarType::int64},{"y",ScalarType::int64}},
      {{"r",TableId{0},{VariableId{0}}},{"s",TableId{1},{VariableId{0},VariableId{1}}}},
      {{VariableId{1},"y"},{VariableId{0},"x"}},false};
  FreeConnexTree tree{NodeId{0},{{"r",NodeKind::native,{VariableId{0}},{NodeId{1}},0,{}},
      {"s",NodeKind::native,{VariableId{0},VariableId{1}},{},1,{}}},{},{}};
  return planner::lower_tree(catalog,query,tree);
}

```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Lower the shared two-node physical plan used by support and delta fixtures. |
| inputs / outputs | Builds R(x), S(x,y), a Query whose head order is y then x, and a two-node native tree before calling lower_tree. |
| invariants | The lower plan’s visible child factor carries (x,y), while output order intentionally differs from the factor order. |
| ownership | Local catalog/query/tree feed the returned owning PhysicalPlan; no runtime or account is retained. |
| failure | Lowering/allocation errors propagate out of this fixture constructor. |
| cost | Constructs two schemas and one two-node plan; lowering/setup cost is separate from each later runtime operation. |
| Design | [tests/unit/delta_factor_test.cpp](../../../../../tests/unit/delta_factor_test.cpp), [include/crown/runtime/support.hpp](../../../../../include/crown/runtime/support.hpp), [include/crown/runtime/delta.hpp](../../../../../include/crown/runtime/delta.hpp), [src/runtime/support.cpp](../../../../../src/runtime/support.cpp), [src/runtime/delta.cpp](../../../../../src/runtime/delta.cpp), [docs/indexed_storage.md](../../../../indexed_storage.md) |

## B0007

[Lines 35–54](../../../../../tests/unit/delta_factor_test.cpp#L35); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void unlive_factor() {
  SupportRuntime runtime(plan());
  static_cast<void>(runtime.apply({1,NodeId{1},SetOperation::insert,row({3,11})}));
  auto view=runtime.current_view();
  check(!view.has_answer(),"unlive child made global truth true");
  check(drain(view.results()).empty(),"empty global query");
  check(drain(view.visible_keys(NodeId{0})).empty(),"root E should be empty");
  auto child=view.visible_keys(NodeId{1});
  check(child.layout().same_token(runtime.plan().relations()[runtime.plan().nodes()[1].visible_relation->value].layout),"factor must use its own E layout");
  check(child.layout().fields()[0].variable==VariableId{0} && child.layout().fields()[1].variable==VariableId{1},"full sorted E schema");
  view.close();
  check(!runtime.ready(),"factor cursor must retain the view lease");
  check(drain(std::move(child))==Relation{row({3,11})},"factor scan dropped a globally dead key");
  check(runtime.ready(),"factor scan leaked a reader");
  auto retry=runtime.current_view();
  error([&] { static_cast<void>(retry.visible_keys(NodeId{99})); },"invalid_fragment");
  error([&] { static_cast<void>(retry.visible_keys(NodeId{1},{{0}})); },"resource_limit");
  check(retry.valid(),"failed cursor construction invalidated view"); retry.close();
  error([&] { static_cast<void>(retry.has_answer()); },"invalid_snapshot");
}

```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Show a globally dead child key remains present in its own factor view. |
| inputs / outputs | Inserts child key (3,11) without a matching root, then checks false global truth, empty query/root output, and one child visible key. |
| invariants | The child key retains the child E layout token and sorted (x,y) schema despite the empty global answer; closing the view alone leaves its cursor lease active. |
| ownership | Runtime owns indexes; view and child cursor retain the reader lease. drain returns an owning Relation before readiness is checked. |
| failure | Invalid node and invalid cursor limit expect invalid_fragment and resource_limit; using the closed view expects invalid_snapshot. A failed cursor construction leaves the view valid. |
| cost | One child update and one-row cursor drain plus empty global/root cursors. The test does not scan all account storage or claim a query-time bound. |
| Design | [tests/unit/delta_factor_test.cpp](../../../../../tests/unit/delta_factor_test.cpp), [include/crown/runtime/support.hpp](../../../../../include/crown/runtime/support.hpp), [include/crown/runtime/delta.hpp](../../../../../include/crown/runtime/delta.hpp), [src/runtime/support.cpp](../../../../../src/runtime/support.cpp), [src/runtime/delta.cpp](../../../../../src/runtime/delta.cpp), [docs/indexed_storage.md](../../../../indexed_storage.md) |

## B0008

[Lines 55–88](../../../../../tests/unit/delta_factor_test.cpp#L55); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void whole_epoch_and_rollback() {
  SupportRuntime runtime(plan());
  static_cast<void>(runtime.apply({1,NodeId{1},SetOperation::insert,row({1,10})}));
  static_cast<void>(runtime.apply({2,NodeId{0},SetOperation::insert,row({1})}));
  auto pending=runtime.begin_epoch(3,SetOperation::erase);
  check(pending.stage(NodeId{0},row({1})),"first erase stage");
  auto before=pending.view(SnapshotSide::before);
  check(before.has_answer(),"old truth was not retained");
  auto held=before.visible_keys(NodeId{0}); before.close();
  error([&] { static_cast<void>(pending.stage(NodeId{1},row({1,10}))); },"runtime_busy");
  check(pending.active(),"prefix-busy rejection aborted epoch");
  check(drain(std::move(held))==Relation{row({1})},"deleted factor key was not pinned");
  check(pending.stage(NodeId{1},row({1,10})),"second erase stage");
  auto old=pending.view(SnapshotSide::before); auto after=pending.view(SnapshotSide::after);
  check(old.has_answer() && !after.has_answer(),"whole-epoch old/new truth");
  check(drain(old.visible_keys(NodeId{0}))==Relation{row({1})},"whole-epoch before lost first stage");
  check(drain(old.visible_keys(NodeId{1}))==Relation{row({1,10})},"whole-epoch before lost last stage");
  check(drain(old.results())==Relation{row({10,1})},"whole-epoch output order");
  check(drain(after.visible_keys(NodeId{1})).empty(),"after factor still contains erased key");
  auto retained=old.visible_keys(NodeId{1}); old.close(); after.close();
  const auto committed=pending.commit(); check(committed.sequence==3,"committed sequence");
  check(!runtime.ready(),"committed factor cursor lost its reader guard");
  check(drain(std::move(retained))==Relation{row({1,10})},"committed old factor view became unreadable");
  check(runtime.ready(),"committed factor reader leaked");
  static_cast<void>(runtime.apply({4,NodeId{1},SetOperation::insert,row({2,20})}));
  auto abort=runtime.begin_epoch(5,SetOperation::erase);
  check(abort.stage(NodeId{1},row({2,20})),"rollback erase stage");
  auto image=abort.view(SnapshotSide::before); auto cursor=image.visible_keys(NodeId{1});
  abort.rollback();
  check(!image.valid() && cursor.state()==ResultCursorState::failed,"rollback did not close factor cursor");
  error([&] { static_cast<void>(image.has_answer()); },"invalid_snapshot");
  check(runtime.ready() && runtime.sequence()==4,"rollback did not restore writer readiness");
  static_cast<void>(runtime.apply({5,NodeId{1},SetOperation::erase,row({2,20})}));
}

```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Exercise before/after factor views, commit-retained cursor lifetime, and rollback invalidation. |
| inputs / outputs | Stages root then child deletion across an epoch, compares before/after truth and visible factors, commits with a retained old cursor, then opens and rolls back a second epoch. |
| invariants | Before retains output (10,1) in reordered head order; after has no child E key. Commit keeps the old cursor readable and blocks readiness until drain; rollback invalidates its view/cursor and leaves sequence 4 before a later sequence-5 update. |
| ownership | Pending epochs own staged state; views/cursors retain read leases. A committed old cursor can read its retained prefix; rollback closes the active prefix. |
| failure | The second stage while the earlier cursor holds the prefix must raise runtime_busy without aborting the epoch. Rollback makes view invalid and next raises invalid_cursor; checks verify readiness/sequence. |
| cost | Two small epochs, repeated visible-key/result drains, and one committed retained cursor; all work is fixture-sized and no global CPU or allocation bound is asserted. |
| Design | [tests/unit/delta_factor_test.cpp](../../../../../tests/unit/delta_factor_test.cpp), [include/crown/runtime/support.hpp](../../../../../include/crown/runtime/support.hpp), [include/crown/runtime/delta.hpp](../../../../../include/crown/runtime/delta.hpp), [src/runtime/support.cpp](../../../../../src/runtime/support.cpp), [src/runtime/delta.cpp](../../../../../src/runtime/delta.cpp), [docs/indexed_storage.md](../../../../indexed_storage.md) |

## B0009

[Lines 89–107](../../../../../tests/unit/delta_factor_test.cpp#L89); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void nullary_and_outside() {
  Catalog catalog{1,{{"r",{{"x",ScalarType::int64}}}}};
  Query query{{{"x",ScalarType::int64}},{{"r",TableId{0},{VariableId{0}}}},{},false};
  FreeConnexTree tree{NodeId{0},{{"r",NodeKind::native,{VariableId{0}},{},0,{}}},{},{}};
  SupportRuntime runtime(planner::lower_tree(catalog,query,tree));
  static_cast<void>(runtime.apply({1,NodeId{0},SetOperation::insert,row({1})}));
  static_cast<void>(runtime.apply({2,NodeId{0},SetOperation::insert,row({2})}));
  auto view=runtime.current_view();
  check(drain(view.visible_keys(NodeId{0}))==Relation{Row{}},"nullary E was not projected to one key");
  view.close();
  Query hidden{{{"x",ScalarType::int64},{"z",ScalarType::int64},{"y",ScalarType::int64}},
      {{"r",TableId{0},{VariableId{0},VariableId{1}}},{"s",TableId{1},{VariableId{1},VariableId{2}}}},{{VariableId{0},"x"}},false};
  Catalog two{1,{{"r",{{"x",ScalarType::int64},{"z",ScalarType::int64}}},{"s",{{"z",ScalarType::int64},{"y",ScalarType::int64}}}}};
  FreeConnexTree child{NodeId{0},{{"r",NodeKind::native,{VariableId{0},VariableId{1}},{NodeId{1}},0,{}},
      {"s",NodeKind::native,{VariableId{1},VariableId{2}},{},1,{}}},{},{}};
  SupportRuntime local(planner::lower_tree(two,hidden,child)); auto context=local.current_view();
  check(!local.plan().nodes()[1].connex,"test needs an outside-C* factor");
  error([&] { static_cast<void>(context.visible_keys(NodeId{1})); },"invalid_fragment");
}

```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Cover nullary visible keys and reject a factor outside C-star. |
| inputs / outputs | Builds a one-column root query and confirms two native rows project to one nullary visible key; then builds a hidden-variable child outside C-star. |
| invariants | The first visible E relation contains exactly the empty Row. The second child is non-connex and its visible_keys request is rejected. |
| ownership | Each runtime/view owns its own lowered plan and result lease; returned Relation owns exported rows. |
| failure | The outside-C-star request must raise invalid_fragment; lowering/runtime construction errors otherwise propagate. |
| cost | Two row insertions plus one nullary projection and one rejected child request. This is a shape fixture, not an exhaustive plan property proof. |
| Design | [tests/unit/delta_factor_test.cpp](../../../../../tests/unit/delta_factor_test.cpp), [include/crown/runtime/support.hpp](../../../../../include/crown/runtime/support.hpp), [include/crown/runtime/delta.hpp](../../../../../include/crown/runtime/delta.hpp), [src/runtime/support.cpp](../../../../../src/runtime/support.cpp), [src/runtime/delta.cpp](../../../../../src/runtime/delta.cpp), [docs/indexed_storage.md](../../../../indexed_storage.md) |

## B0010

[Lines 108–145](../../../../../tests/unit/delta_factor_test.cpp#L108); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::uint64_t eager_cost(std::size_t count) {
  DeltaOptions options; options.mode=DeltaMode::maintenance; options.live_maintenance=LiveMaintenance::eager;
  options.completion=DeltaCompletion::root_first;
  DeltaRuntime runtime(plan(),options);
  std::uint64_t sequence=0;
  for (std::size_t i=0;i<count;++i) {
    auto input=runtime.apply({++sequence,TableId{1},SetOperation::insert,row({static_cast<std::int64_t>(i+1),10})});
    check(!input.active(),"maintenance epoch produced output");
  }
  const auto bootstrap=runtime.set_mode(DeltaMode::delta);
  check(bootstrap.e_rows_scanned==count && bootstrap.live_rows==0 && bootstrap.parent_live_rows==0,"dead-factor bootstrap scan accounting");
  check(bootstrap.candidates==0 && bootstrap.accepted==0 && bootstrap.spool_rows==0,"bootstrap enumerated query output");
  auto empty=runtime.apply({++sequence,TableId{0},SetOperation::insert,row({100})});
  const auto scanned=empty.metrics().work;
  check(!empty.active() && empty.metrics().stages==1 && empty.metrics().changed_keys==0,"empty delta stage completion");
  check(empty.metrics().e_rows_scanned==count && empty.metrics().live_rows==0,"empty delta concealed its E scan");
  check(runtime.live_snapshot()->sequence==sequence,"empty delta did not advance live tag");
  auto activated=runtime.apply({++sequence,TableId{1},SetOperation::insert,row({100,20})});
  const auto metrics=activated.metrics();
  check(metrics.changed_keys==2 && metrics.live_witnesses==2 && metrics.candidates==2 && metrics.accepted==1 && metrics.rejected==1,"ancestor/child ownership counters");
  check(metrics.earlier_probes==1 && metrics.e_rows_scanned==count+2 && metrics.parent_live_rows==1 && metrics.separator_fields==count+2,"eager semijoin scan/field accounting");
  check(metrics.live_rows_copied==2 && metrics.live_rows==2 && metrics.peak_live_rows==2,"first live image accounting");
  check(metrics.spool_rows==1 && metrics.spool_capacity_rows>=1 && metrics.spool_bytes<=options.spool_byte_limit,"bounded spool accounting");
  check(metrics.cursor_startup_work>0 && metrics.cursor_results_work>0 && metrics.cursor_termination_work>0,"cursor phase work was not charged");
  check(activated.stages().size()==1 && !activated.stages()[0].before_answer && activated.stages()[0].after_answer,"adjacent-prefix truth diagnostics");
  check(!runtime.ready(),"undelivered output did not gate input");
  auto output=activated.next();
  check(output && output->ordinal==1 && output->operation==SetOperation::insert && output->tuple.values()==row({20,100}),"accepted output/layout order");
  check(!activated.next() && runtime.ready(),"last output did not release barrier");
  auto shared=runtime.apply({++sequence,TableId{0},SetOperation::insert,row({1})});
  check(shared.metrics().changed_keys==1 && shared.metrics().accepted==1 && shared.metrics().live_rows==4 && shared.metrics().peak_live_rows==6,"retained committed/working live images");
  check(shared.next()->tuple.values()==row({10,1}),"unchanged child E did not become live");
  const auto before=runtime.live_snapshot()->factors;
  auto noop=runtime.apply({++sequence,TableId{0},SetOperation::insert,row({1})});
  check(!noop.active() && noop.metrics().stages==0 && noop.metrics().e_rows_scanned==0,"certified source no-op scanned E");
  check(runtime.live_snapshot()->factors==before && runtime.live_snapshot()->sequence==sequence,"no-op cache membership/tag");
  runtime.check_invariants(); return scanned;
}

```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Compare eager abstract work for empty delta over one versus eight child E rows. |
| inputs / outputs | For count in {1,8}, inserts that many child E rows into eager-maintenance mode, switches to delta, measures the empty root-update work, then activates a child and checks its counters/output. |
| invariants | Bootstrap and empty update each report count E rows scanned with no live/output rows. The later activation expects two candidate owners and one accepted result. main compares only the returned empty-update abstract work at these two counts. |
| ownership | DeltaRuntime owns its native state, live images and spool; returned update cursors own delivery state until drained. |
| failure | Every check guards the literal counter/output expectations; failed setup or runtime operations propagate to main. There is no test that all possible E sizes scale linearly or that abstract work equals time. |
| cost | Includes count setup inserts, bootstrap, one empty root update, one child activation, output drain, and a no-op. Metrics are logical maintenance-work counters, not elapsed CPU/delay; comparison is only count 1 versus 8. |
| Design | [tests/unit/delta_factor_test.cpp](../../../../../tests/unit/delta_factor_test.cpp), [include/crown/runtime/support.hpp](../../../../../include/crown/runtime/support.hpp), [include/crown/runtime/delta.hpp](../../../../../include/crown/runtime/delta.hpp), [src/runtime/support.cpp](../../../../../src/runtime/support.cpp), [src/runtime/delta.cpp](../../../../../src/runtime/delta.cpp), [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/maintenance_cost.md](../../../../maintenance_cost.md) |

## B0011

[Lines 146–171](../../../../../tests/unit/delta_factor_test.cpp#L146); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void typed_projection() {
  Catalog catalog{1,{{"r",{{"day",ScalarType::date},{"amount",ScalarType::decimal,false,Collation::binary,DecimalSpec{38,2}},
      {"name",ScalarType::string},{"flag",ScalarType::boolean},{"witness",ScalarType::int64}}}}};
  Query query{{{"day",ScalarType::date},{"amount",ScalarType::decimal},{"name",ScalarType::string},
      {"flag",ScalarType::boolean},{"witness",ScalarType::int64}},
      {{"r",TableId{0},{VariableId{0},VariableId{1},VariableId{2},VariableId{3},VariableId{4}}}},
      {{VariableId{2},"name"},{VariableId{0},"day"},{VariableId{1},"amount"},{VariableId{3},"flag"},{VariableId{1},"again"}},false};
  FreeConnexTree tree{NodeId{0},{{"r",NodeKind::native,{VariableId{0},VariableId{1},VariableId{2},VariableId{3},VariableId{4}},{},0,{}}},{},{}};
  DeltaRuntime runtime(planner::lower_tree(catalog,query,tree));
  const Value day=Date::parse("2026-11-06"), amount=Decimal::parse("12345678901234567890.12"), name=std::string(80,'x');
  Row first{day,amount,name,Value{true},Value{std::int64_t{10}}}, second=first; second.back()=std::int64_t{20};
  const Row expected{name,day,amount,Value{true},amount};
  auto inserted=runtime.apply({1,TableId{0},SetOperation::insert,first});
  check(inserted.metrics().spool_bytes>=80+64+expected.size()*sizeof(Value)+sizeof(SignedResult),"wide scalar spool accounting");
  auto plus=inserted.next();
  check(plus && plus->tuple.values()==expected && plus->operation==SetOperation::insert,"typed reordered/repeated delta");
  check(plus->tuple.layout().same_token(runtime.result_layout()),"typed result layout token");
  auto collision=runtime.apply({2,TableId{0},SetOperation::insert,second});
  check(collision.remaining()==0 && collision.metrics().changed_keys==0,"typed hidden collision emitted output");
  auto nonlast=runtime.apply({3,TableId{0},SetOperation::erase,first});
  check(nonlast.remaining()==0,"typed nonlast deletion emitted output");
  auto erased=runtime.apply({4,TableId{0},SetOperation::erase,second}); auto minus=erased.next();
  check(minus && minus->tuple.values()==expected && minus->operation==SetOperation::erase,"typed last deletion output");
  check(plus->tuple.values()==expected && runtime.ready(),"returned typed row lost ownership after later epochs");
  runtime.check_invariants();
}

```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Check typed reordered/repeated output projection, hidden collisions, and returned-row lifetime. |
| inputs / outputs | Runs four typed source values through reordered/repeated output projection, inserts a second row differing only in hidden witness, deletes first then last witness, and retains the first returned tuple across later epochs. |
| invariants | Head output is (name, day, amount, flag, amount); hidden-witness collision emits nothing, only final deletion emits minus, and the first Tuple still matches after later updates. spool_bytes assertion is a lower bound for one wide result. |
| ownership | Runtime owns delta state/spool; returned Tuple owns or retains its output payload beyond the delivery cursor as provided by the Tuple API. |
| failure | Any type/layout/output mismatch fails checks; runtime/type errors propagate. The fixture does not fault-sweep spool allocation. |
| cost | Four typed values include an 80-byte string; the assertion checks spool lower bound 80+fixed+Value slots+SignedResult. That is not total bytes, allocator calls, or an RSS measurement. |
| Design | [tests/unit/delta_factor_test.cpp](../../../../../tests/unit/delta_factor_test.cpp), [include/crown/runtime/support.hpp](../../../../../include/crown/runtime/support.hpp), [include/crown/runtime/delta.hpp](../../../../../include/crown/runtime/delta.hpp), [src/runtime/support.cpp](../../../../../src/runtime/support.cpp), [src/runtime/delta.cpp](../../../../../src/runtime/delta.cpp), [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/maintenance_cost.md](../../../../maintenance_cost.md) |

## B0012

[Lines 172–172](../../../../../tests/unit/delta_factor_test.cpp#L172); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L172-L172:sha256:c7bfe2f3de133d78a2bc8bb1c4a08450563986ee8254facee698e1dcc57e8162
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Close the recorded declaration scopes in delta_factor_test.cpp: namespace (anonymous). |
| inputs / outputs | Preceding namespace, type or initializer declarations in; completed lexical boundary out. |
| invariants | Brace-opening context is recorded in root-scope-context-v1.json. These are declaration/initializer boundaries, not an independent update, validation or recovery operation. |
| ownership | Enclosing objects and borrowed fields keep their declared ownership. This punctuation creates no new owner. |
| failure | Malformed scope syntax is a compile error. Any initializer/constructor failure belongs to the enclosing object declaration. |
| cost | No separate loop, guard or engine call is introduced by the delimiter; enclosing initialization and object lifetime still have their actual costs. |
| Design | [tests/unit/delta_factor_test.cpp](../../../../../tests/unit/delta_factor_test.cpp), [docs/ordered_delta.md](../../../../ordered_delta.md), [docs/code_review.md](../../../../code_review.md) |

## B0013

[Lines 173–181](../../../../../tests/unit/delta_factor_test.cpp#L173); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
int main() {
  try {
    unlive_factor(); whole_epoch_and_rollback(); nullary_and_outside(); typed_projection();
    const auto small=eager_cost(1), larger=eager_cost(8);
    check(larger>small,"eager no-delta scan cost did not grow with E");
    std::cout<<"E-factor context, lease, rollback and eager-cost checks passed; empty-delta work "<<small<<" -> "<<larger<<'\n';
  }
  catch (const std::exception& failure) { std::cerr<<failure.what()<<'\n'; return 1; }
}

```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Run support factor, epoch, nullary, projection, and finite eager-work scenarios. |
| inputs / outputs | Runs unlive-factor, epoch/rollback, nullary/outside, typed-projection, then eager_cost(1) and eager_cost(8) and requires the latter abstract work to be greater. |
| invariants | The output labels the comparison as empty-delta work; each helper establishes only its stated finite fixture assertions. |
| ownership | Main owns no long-lived runtime; helper-local runtimes/cursors are destroyed on return. |
| failure | std::exception is caught, printed, and returns 1; non-standard exceptions escape. Success falls through with return code 0. |
| cost | Orchestrates the selected scenarios and their internal finite loops. The two point comparison is not a CPU benchmark or complexity theorem. |
| Design | [tests/unit/delta_factor_test.cpp](../../../../../tests/unit/delta_factor_test.cpp), [include/crown/runtime/support.hpp](../../../../../include/crown/runtime/support.hpp), [include/crown/runtime/delta.hpp](../../../../../include/crown/runtime/delta.hpp), [src/runtime/support.cpp](../../../../../src/runtime/support.cpp), [src/runtime/delta.cpp](../../../../../src/runtime/delta.cpp), [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/maintenance_cost.md](../../../../maintenance_cost.md) |
