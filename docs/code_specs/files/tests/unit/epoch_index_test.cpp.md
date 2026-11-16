# `tests/unit/epoch_index_test.cpp` — block usage map

[Source](../../../../../tests/unit/epoch_index_test.cpp) · [Source index](../../../README.md) · [Subsystem contracts](../../../subsystem_contracts.md) · [Reviewed primitives](../../../primitives.md)

Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection.

Snapshot SHA-256: `7f22b6014e1aa6c31daa75a7cfaa259ff68437def9f0cb727dc8ed3b1666f519`. 221 lines partitioned into 24 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [tests](../../../subsystem_contracts.md#tests). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/code_review.md](../../../../code_review.md), [docs/reference_fuzz.md](../../../../reference_fuzz.md), [docs/task_ledger.md](../../../../task_ledger.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–16](../../../../../tests/unit/epoch_index_test.cpp#L1) | Imports dependencies; declares namespace scope; declares aliases. |  · [reviewed contract](#b0001) |
| [B0002 · 17–19](../../../../../tests/unit/epoch_index_test.cpp#L17) | Callable definition: void check(bool condition,const std::string& message) | calls std::runtime_error; guard void check(bool condition,const std::string& message) { · [reviewed contract](#b0002) |
| [B0003 · 20–20](../../../../../tests/unit/epoch_index_test.cpp#L20) | Explanatory comments or spacing. |  |
| [B0004 · 21–29](../../../../../tests/unit/epoch_index_test.cpp#L21) | Callable definition: template&lt;class Action&gt; void expect_error(Action&& action,std::string_view code) | calls action, check, code, std::string; guard check(failure.code()==code,"expected "+std::string(code)+", got "+failure.code()); · [reviewed contract](#b0004) |
| [B0005 · 30–30](../../../../../tests/unit/epoch_index_test.cpp#L30) | Explanatory comments or spacing. |  |
| [B0006 · 31–31](../../../../../tests/unit/epoch_index_test.cpp#L31) | Callable definition: Value n(std::int64_t value) | calls ; returns value · [reviewed contract](#b0006) |
| [B0007 · 32–32](../../../../../tests/unit/epoch_index_test.cpp#L32) | Explanatory comments or spacing. |  |
| [B0008 · 33–44](../../../../../tests/unit/epoch_index_test.cpp#L33) | Callable definition: PhysicalPlan bucket_plan() | calls planner::lower_tree; returns planner::lower_tree(catalog,query,tree) · [reviewed contract](#b0008) |
| [B0009 · 45–45](../../../../../tests/unit/epoch_index_test.cpp#L45) | Explanatory comments or spacing. |  |
| [B0010 · 46–57](../../../../../tests/unit/epoch_index_test.cpp#L46) | Callable definition: PhysicalPlan nullary_separator_plan() | calls planner::lower_tree; returns planner::lower_tree(catalog,query,tree) · [reviewed contract](#b0010) |
| [B0011 · 58–58](../../../../../tests/unit/epoch_index_test.cpp#L58) | Explanatory comments or spacing. |  |
| [B0012 · 59–61](../../../../../tests/unit/epoch_index_test.cpp#L59) | Callable definition: std::optional&lt;storage::Tuple&gt; next(SupportRuntime::ResultCursor& cursor) | calls ; returns cursor.next() · [reviewed contract](#b0012) |
| [B0013 · 62–62](../../../../../tests/unit/epoch_index_test.cpp#L62) | Explanatory comments or spacing. |  |
| [B0014 · 63–72](../../../../../tests/unit/epoch_index_test.cpp#L63) | Callable definition: Relation drain(SupportRuntime::ResultCursor& cursor) | calls next, check, layout, same_token; guard check(row-&gt;layout().same_token(cursor.layout()),"cursor changed its compiled output layout");; returns rows; growth insert; 1 loop sites · [reviewed contract](#b0014) |
| [B0015 · 73–73](../../../../../tests/unit/epoch_index_test.cpp#L73) | Explanatory comments or spacing. |  |
| [B0016 · 74–77](../../../../../tests/unit/epoch_index_test.cpp#L74) | Callable definition: void apply(SupportRuntime& runtime,std::uint64_t& sequence,NodeId node,SetOperation operation,Row row) | calls std::move, check; guard check(epoch.sequence==sequence,"support update advanced to the wrong sequence"); · [reviewed contract](#b0016) |
| [B0017 · 78–78](../../../../../tests/unit/epoch_index_test.cpp#L78) | Explanatory comments or spacing. |  |
| [B0018 · 79–161](../../../../../tests/unit/epoch_index_test.cpp#L79) | Callable definition: void restored_full_and_bucket_lookups_are_selective() | calls runtime, bucket_plan, apply, n; guard check(pending.stage(NodeId{1},{n(1),n(y)}),"fixture deletion did not change membership");; growth insert; 6 loop sites; source comment (unverified): // A local visible fragment isolates the child E full-key lookup. Whole-query · [reviewed contract](#b0018) |
| [B0019 · 162–162](../../../../../tests/unit/epoch_index_test.cpp#L162) | Explanatory comments or spacing. |  |
| [B0020 · 163–189](../../../../../tests/unit/epoch_index_test.cpp#L163) | Callable definition: void visible_bucket_supports_nullary_separator_and_leases() | calls runtime, nullary_separator_plan, apply, n; guard check(runtime.plan().enumeration().steps.size()==2 &&; growth insert · [reviewed contract](#b0020) |
| [B0021 · 190–190](../../../../../tests/unit/epoch_index_test.cpp#L190) | Explanatory comments or spacing. |  |
| [B0022 · 191–207](../../../../../tests/unit/epoch_index_test.cpp#L191) | Callable definition: void rollback_aborts_open_bucket_cursor() | calls runtime, bucket_plan, apply, n; guard check(pending.stage(NodeId{1},{n(1),n(7)}),"rollback fixture did not erase its E key");; growth insert · [reviewed contract](#b0022) |
| [B0023 · 208–210](../../../../../tests/unit/epoch_index_test.cpp#L208) | Closes surrounding scope/type. | source comment (unverified): // namespace · [reviewed contract](#b0023) |
| [B0024 · 211–221](../../../../../tests/unit/epoch_index_test.cpp#L211) | Callable definition: int main() | calls restored_full_and_bucket_lookups_are_selective, visible_bucket_supports_nullary_separator_and_leases, rollback_aborts_open_bucket_cursor, what; returns 1; 0 · [reviewed contract](#b0024) |

## B0001

[Lines 1–16](../../../../../tests/unit/epoch_index_test.cpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L1-L16:sha256:1237c42e1b7f08a03644983816127f9d820e812eda1c0642a63cabdb466db4a7
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Prepare epoch_index_test.cpp: include "crown/api/error.hpp", "crown/planner/lower.hpp", "crown/runtime/support.hpp", &lt;cstdint&gt;, &lt;iostream&gt;, &lt;optional&gt;, &lt;stdexcept&gt;, &lt;string&gt;, &lt;string_view&gt;, &lt;utility&gt;; bind local aliases/name imports. |
| inputs / outputs | Compiler-visible dependencies, names and the recorded declarations in; declarations available to the following fixture/CLI/example definitions out. |
| invariants | Declarations are scoped to this source/header and its selected ABI. Included code has its own effects; names and editable fixture values do not confer proof, admission or publication authority. |
| ownership | Aliases/includes do not create a query owner. Pointers/references/views are non-owning. Containers own their elements, which can themselves be borrowed pointers or numeric IDs. Only documented owning shared-control handles retain controls; IDs/slot-handle values do not independently keep an arena/runtime alive. |
| failure | Missing headers, ill-formed names/types, failed static assertions or active #error directives stop compilation. No runtime rejection/rollback mechanism is implemented by aliases or function prototypes. |
| cost | Preprocessing and type/constraint instantiation cost compilation. Alias/prototype syntax does not invoke the declared operation; any included definitions keep their own initialization effects. |
| Design | [tests/unit/epoch_index_test.cpp](../../../../../tests/unit/epoch_index_test.cpp), [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/code_review.md](../../../../code_review.md) |

## B0002

[Lines 17–19](../../../../../tests/unit/epoch_index_test.cpp#L17); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void check(bool condition,const std::string& message) {
  if (!condition) throw std::runtime_error(message);
}

```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Assertion helper for support runtime expectations. |
| inputs / outputs | Accepts a Boolean and const std::string reference; returns when true and throws std::runtime_error(message) when false. |
| invariants | The helper only branches on the value. Call-site string expressions, including concatenations, are evaluated before the call even on passing checks. |
| ownership | Borrows the already constructed std::string; an exception owns its diagnostic. |
| failure | False throws; exception construction can fail; no CROWN Error is caught here. |
| cost | One condition branch. Passing calls may already have incurred caller-side string creation, while this body only builds an exception on failure. |
| Design | [tests/unit/epoch_index_test.cpp](../../../../../tests/unit/epoch_index_test.cpp) |

## B0004

[Lines 21–29](../../../../../tests/unit/epoch_index_test.cpp#L21); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
template<class Action>
void expect_error(Action&& action,std::string_view code) {
  try { action(); }
  catch (const Error& failure) {
    check(failure.code()==code,"expected "+std::string(code)+", got "+failure.code());
    return;
  }
  throw std::runtime_error("expected error "+std::string(code));
}

```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Assert a specific CROWN Error code from an action. |
| inputs / outputs | Binds Action&& and a borrowed error-code string_view, invokes the named action as action() (an lvalue call), and compares a caught crown::Error::code(). |
| invariants | A matching CROWN error returns. A mismatch is reported by check; normal return falls through to the missing-error runtime_error. |
| ownership | The helper does not own action captures or code storage beyond the call; the caller owns runtime/view/cursor objects used by the action. |
| failure | Catches crown::Error only. Mismatch and missing errors throw std::runtime_error; non-CROWN exceptions propagate unchanged. |
| cost | At most one action invocation plus one code comparison. Caller-provided std::string expressions in check may be formed before entry; no allocation or timing counter is asserted. |
| Design | [tests/unit/epoch_index_test.cpp](../../../../../tests/unit/epoch_index_test.cpp), [include/crown/runtime/support.hpp](../../../../../include/crown/runtime/support.hpp), [docs/indexed_storage.md](../../../../indexed_storage.md) |

## B0006

[Lines 31–31](../../../../../tests/unit/epoch_index_test.cpp#L31); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Value n(std::int64_t value) { return value; }

```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Convert an integer fixture value to Value. |
| inputs / outputs | Converts one int64_t scalar to the corresponding Value alternative and returns it by value. |
| invariants | The fixture uses this helper only for integer columns and literals; it does not look up a runtime layout or validate a row. |
| ownership | The returned Value owns/carries the scalar alternative; there is no borrowed view or runtime handle. |
| failure | No explicit error path exists for this scalar conversion in the source. |
| cost | One scalar-to-variant construction; no relation scan, index lookup, or account allocation is performed by the helper. |
| Design | [tests/unit/epoch_index_test.cpp](../../../../../tests/unit/epoch_index_test.cpp) |

## B0008

[Lines 33–44](../../../../../tests/unit/epoch_index_test.cpp#L33); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
PhysicalPlan bucket_plan() {
  const Catalog catalog{1,{{"r",{{"x",ScalarType::int64}}},
                           {"s",{{"x",ScalarType::int64},{"y",ScalarType::int64}}}}};
  const Query query{{{"x",ScalarType::int64},{"y",ScalarType::int64}},
                    {{"r",TableId{0},{VariableId{0}}},
                     {"s",TableId{1},{VariableId{0},VariableId{1}}}},
                    {{VariableId{0},"x"},{VariableId{1},"y"}},false};
  const FreeConnexTree tree{NodeId{0},
      {{"r",NodeKind::native,{VariableId{0}},{NodeId{1}},0,{}},
       {"s",NodeKind::native,{VariableId{0},VariableId{1}},{},1,{}}}, {}, {}};
  return planner::lower_tree(catalog,query,tree);
}

```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Lower the two-relation R(x), S(x,y) bucket plan. |
| inputs / outputs | Builds Catalog R(x), S(x,y), a Query with x as join variable and x/y outputs, and a two-node FreeConnexTree, then returns lower_tree output. |
| invariants | The child S separator is x and its visible E key is (x,y); the root is R(x). These declarations define the finite bucket fixtures. |
| ownership | Catalog/query/tree are local value owners; the returned PhysicalPlan owns lowered descriptors. No runtime instance is created here. |
| failure | Planner lowering or allocation failures propagate; check is not involved in this helper. |
| cost | Creates two relation descriptors and a two-node tree before lowering; setup allocations/lowering are not the runtime cursor costs measured by the scenarios. |
| Design | [tests/unit/epoch_index_test.cpp](../../../../../tests/unit/epoch_index_test.cpp), [include/crown/runtime/support.hpp](../../../../../include/crown/runtime/support.hpp), [src/runtime/support.cpp](../../../../../src/runtime/support.cpp), [docs/indexed_storage.md](../../../../indexed_storage.md) |

## B0010

[Lines 46–57](../../../../../tests/unit/epoch_index_test.cpp#L46); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
PhysicalPlan nullary_separator_plan() {
  const Catalog catalog{1,{{"r",{{"x",ScalarType::int64}}},
                           {"flags",{{"tag",ScalarType::int64}}}}};
  const Query query{{{"x",ScalarType::int64}},
                    {{"r",TableId{0},{VariableId{0}}},
                     {"flags",TableId{1},{IgnoredColumn{}}}},
                    {{VariableId{0},"x"}},false};
  const FreeConnexTree tree{NodeId{0},
      {{"r",NodeKind::native,{VariableId{0}},{NodeId{1}},0,{}},
       {"flags",NodeKind::native,{}, {},1,{}}}, {}, {}};
  return planner::lower_tree(catalog,query,tree);
}

```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Lower a child plan with an ignored column and empty visible separator. |
| inputs / outputs | Builds R(x) and flags(tag), but maps the child column as IgnoredColumn and gives its tree node an empty variable set before lower_tree. |
| invariants | The flags catalog table has one physical tag column, ignored by its query atom. The compiled native child key and child bucket separator have zero fields; the SupportRuntime fixture supplies an empty Row for that native key. |
| ownership | Borrows local catalog/query/tree during lowering and returns an owning PhysicalPlan; no runtime instance or view is retained. |
| failure | Lowering and allocation errors propagate; no test-specific catch exists in the helper. |
| cost | Fixed two-relation plan construction and lowering. It establishes an empty-index key shape; it does not scan or mutate runtime data. |
| Design | [tests/unit/epoch_index_test.cpp](../../../../../tests/unit/epoch_index_test.cpp), [include/crown/runtime/support.hpp](../../../../../include/crown/runtime/support.hpp), [src/runtime/support.cpp](../../../../../src/runtime/support.cpp), [docs/indexed_storage.md](../../../../indexed_storage.md) |

## B0012

[Lines 59–61](../../../../../tests/unit/epoch_index_test.cpp#L59); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::optional<storage::Tuple> next(SupportRuntime::ResultCursor& cursor) {
  return cursor.next();
}

```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Advance a borrowed ResultCursor once. |
| inputs / outputs | Calls next() once on a borrowed ResultCursor and returns its optional storage::Tuple result. |
| invariants | The wrapper adds no exhaustion loop, layout conversion, or active-state change beyond the cursor API call. |
| ownership | The cursor stays owned by the caller; the returned Tuple is a value and its layout/payload follows the support Tuple API. |
| failure | Cursor errors propagate from next(); the wrapper catches nothing. |
| cost | One cursor advancement. Any tuple materialization and cursor metric work belong to ResultCursor::next(), not this forwarding helper. |
| Design | [tests/unit/epoch_index_test.cpp](../../../../../tests/unit/epoch_index_test.cpp), [include/crown/runtime/support.hpp](../../../../../include/crown/runtime/support.hpp), [src/runtime/support.cpp](../../../../../src/runtime/support.cpp), [docs/indexed_storage.md](../../../../indexed_storage.md) |

## B0014

[Lines 63–72](../../../../../tests/unit/epoch_index_test.cpp#L63); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Relation drain(SupportRuntime::ResultCursor& cursor) {
  Relation rows;
  while (auto row=next(cursor)) {
    check(row->layout().same_token(cursor.layout()),"cursor changed its compiled output layout");
    check(rows.insert(crown::storage::export_row(row->values())).second,"cursor emitted a duplicate row");
  }
  check(cursor.state()==ResultCursorState::exhausted && !cursor.active(),
      "cursor did not release its reader after exhaustion");
  return rows;
}

```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Drain a cursor into an owning Relation and check token, uniqueness, and exhaustion. |
| inputs / outputs | Repeatedly calls next(cursor), checks each Tuple layout token against cursor.layout(), exports values into an owning Relation, and rejects duplicate rows. |
| invariants | At end it additionally requires exhausted state and inactive cursor before returning the Relation by value. |
| ownership | Borrows cursor for the full drain; Relation owns exported Row values, so output rows outlive the cursor. |
| failure | Layout mismatch, duplicate output, or non-exhausted lease throws std::runtime_error; next() failures propagate. |
| cost | One cursor call and row export/ordered-set insertion per returned tuple, plus a final state check. Copying, row comparisons and container growth scale with result size and scalar payloads; no fixed CPU bound is measured. |
| Design | [tests/unit/epoch_index_test.cpp](../../../../../tests/unit/epoch_index_test.cpp), [include/crown/runtime/support.hpp](../../../../../include/crown/runtime/support.hpp), [src/runtime/support.cpp](../../../../../src/runtime/support.cpp), [docs/indexed_storage.md](../../../../indexed_storage.md) |

## B0016

[Lines 74–77](../../../../../tests/unit/epoch_index_test.cpp#L74); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void apply(SupportRuntime& runtime,std::uint64_t& sequence,NodeId node,SetOperation operation,Row row) {
  const auto epoch=runtime.apply({++sequence,node,operation,std::move(row)});
  check(epoch.sequence==sequence,"support update advanced to the wrong sequence");
}

```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Apply one support update and advance its sequence. |
| inputs / outputs | Pre-increments the caller sequence, moves one Row into SupportRuntime::apply with node and SetOperation, then checks the returned epoch sequence. |
| invariants | The expected sequence is the incremented value. If apply throws, this helper has already changed the caller sequence. |
| ownership | Runtime and sequence are borrowed; Row is passed by value and moved into the update request. |
| failure | Runtime errors propagate; a returned sequence mismatch throws std::runtime_error. No rollback of the sequence reference is attempted. |
| cost | One update submission and one sequence comparison. Runtime admission/index work is not counted by this wrapper. |
| Design | [tests/unit/epoch_index_test.cpp](../../../../../tests/unit/epoch_index_test.cpp), [include/crown/runtime/support.hpp](../../../../../include/crown/runtime/support.hpp), [src/runtime/support.cpp](../../../../../src/runtime/support.cpp), [docs/indexed_storage.md](../../../../indexed_storage.md) |

## B0018

[Lines 79–161](../../../../../tests/unit/epoch_index_test.cpp#L79); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void restored_full_and_bucket_lookups_are_selective() {
  SupportRuntime runtime(bucket_plan());
  std::uint64_t sequence=0;
  apply(runtime,sequence,NodeId{0},SetOperation::insert,{n(1)});
  apply(runtime,sequence,NodeId{0},SetOperation::insert,{n(2)});
  constexpr std::int64_t removed_count=7;
  constexpr std::int64_t unrelated_count=41;
  for (std::int64_t y=0;y<removed_count;++y)
    apply(runtime,sequence,NodeId{1},SetOperation::insert,{n(1),n(y)});
  for (std::int64_t y=100;y<100+unrelated_count;++y)
    apply(runtime,sequence,NodeId{1},SetOperation::insert,{n(2),n(y)});

  auto pending=runtime.begin_epoch(sequence+1,SetOperation::erase);
  for (std::int64_t y=0;y<removed_count;++y)
    check(pending.stage(NodeId{1},{n(1),n(y)}),"fixture deletion did not change membership");
  for (std::int64_t y=100;y<100+unrelated_count;++y)
    check(pending.stage(NodeId{1},{n(2),n(y)}),"unrelated fixture deletion did not change membership");
  auto before=pending.view(SnapshotSide::before);
  auto after=pending.view(SnapshotSide::after);
  check(before.metrics().restored_key_entries>0 && before.metrics().restored_bucket_entries>0 &&
            before.metrics().key_fields>0,
        "before view did not account for restored full and compiled-index keys");

  auto old_bucket=before.visible_bucket(NodeId{1},{n(1)});
  Relation expected_bucket;
  for (std::int64_t y=0;y<removed_count;++y) expected_bucket.insert({n(1),n(y)});
  check(drain(old_bucket)==expected_bucket,"before-side separator bucket lost erased E keys");
  const auto bucket_work=old_bucket.metrics().results.overlay_rows+
      old_bucket.metrics().termination.overlay_rows;
  check(bucket_work==static_cast<std::uint64_t>(removed_count),
      "separator lookup visited restored rows outside its matching bucket");

  auto new_bucket=after.visible_bucket(NodeId{1},{n(1)});
  check(drain(new_bucket).empty(),"after-side separator bucket returned erased E keys");
  check(new_bucket.metrics().results.overlay_rows+new_bucket.metrics().termination.overlay_rows==0,
      "after-side cursor unexpectedly visited before-only restored rows");

  const FixedAssignment exact{{VariableId{0},n(1)},{VariableId{1},n(3)}};
  // A local visible fragment isolates the child E full-key lookup. Whole-query
  // completions also restore the erased root factor, so their overlay count
  // necessarily includes that independent factor lookup.
  auto old_whole=before.completions(exact);
  check(drain(old_whole)==Relation{{n(1),n(3)}},"before-side whole completion lost its restored path");
  auto old_exact=before.completions(exact,VisibleFragment{NodeId{1}});
  check(drain(old_exact)==Relation{{n(1),n(3)}},"before-side direct completion missed its restored full key");
  check(old_exact.metrics().results.overlay_rows+old_exact.metrics().termination.overlay_rows==1,
      "direct full-key lookup inspected rows other than its exact restored key");
  auto old_miss=before.completions({{VariableId{0},n(1)},{VariableId{1},n(99)}},VisibleFragment{NodeId{1}});
  check(drain(old_miss).empty(),"before-side direct miss returned an unrelated restored key");
  check(old_miss.metrics().results.overlay_rows+old_miss.metrics().termination.overlay_rows==0,
      "direct full-key miss scanned unrelated restored keys");
  auto bucket_miss=before.visible_bucket(NodeId{1},{n(3)});
  check(drain(bucket_miss).empty(),"before-side separator miss returned an unrelated bucket");
  check(bucket_miss.metrics().results.overlay_rows+bucket_miss.metrics().termination.overlay_rows==0,
      "separator miss scanned restored rows from unrelated buckets");
  auto new_exact=after.completions(exact,VisibleFragment{NodeId{1}});
  check(drain(new_exact).empty(),"after-side direct completion returned a deleted full key");
  check(new_exact.metrics().results.overlay_rows+new_exact.metrics().termination.overlay_rows==0,
      "after-side direct lookup visited before-only restored rows");

  expect_error([&] { static_cast<void>(before.visible_bucket(NodeId{0},{})); },"invalid_fragment");
  expect_error([&] { static_cast<void>(before.visible_bucket(NodeId{99},{n(1)})); },"invalid_fragment");
  expect_error([&] { static_cast<void>(before.visible_bucket(NodeId{1},{})); },"invalid_tuple");
  expect_error([&] { static_cast<void>(before.visible_bucket(NodeId{1},{Value{std::string("wrong type")}})); },"invalid_tuple");

  // An opened E bucket cursor keeps its journal reader through commit. The
  // group still holds the ordinary view lease after the cursor is exhausted.
  auto commit_cursor=before.visible_bucket(NodeId{1},{n(1)});
  auto first_committed=commit_cursor.next();
  check(first_committed.has_value(),"visible bucket cursor did not open before commit");
  static_cast<void>(pending.commit());
  ++sequence;
  Relation committed_rows{crown::storage::export_row(first_committed->values())};
  while (auto row=commit_cursor.next())
    check(committed_rows.insert(crown::storage::export_row(row->values())).second,"committed visible bucket cursor repeated a row");
  check(committed_rows==expected_bucket && commit_cursor.state()==ResultCursorState::exhausted,
      "visible bucket cursor did not survive commit");
  expect_error([&] {
    static_cast<void>(runtime.apply({sequence+1,NodeId{1},SetOperation::insert,{n(1),n(500)}}));
  },"runtime_busy");
  before.close(); after.close();
  apply(runtime,sequence,NodeId{1},SetOperation::insert,{n(1),n(500)});
}

```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Check selective before/after restored full-key and bucket lookup for a finite deletion epoch. |
| inputs / outputs | Seeds 2 roots and 48 child keys (7 under x=1 and 41 under x=2), stages all 48 deletions, and tests before/after bucket and completion cursors including misses. |
| invariants | The before x=1 bucket returns 7 rows and overlay_rows=7; after bucket and direct after hit report zero. A child VisibleFragment exact hit reports one restored key and its miss zero. Whole-query completion also probes the restored root factor, so its overlay total is not a child-only measure. |
| ownership | Pending epoch owns staged changes; before/after views and cursors retain their reader leases. A commit-surviving bucket cursor remains readable until drained; view leases are explicitly closed before the next write. |
| failure | Checks invalid node/kind and separator shape errors, then runtime_busy while the committed view lease remains. Rollback/error branches are not substituted for the commit path in this fixture. |
| cost | Loops over 48 staged child rows, drains seven-row and empty results, and performs exact hit/miss cursor work. overlay_rows is a support metric, not CPU time, all allocation, or a bound on unrelated query work. |
| Design | [tests/unit/epoch_index_test.cpp](../../../../../tests/unit/epoch_index_test.cpp), [include/crown/runtime/support.hpp](../../../../../include/crown/runtime/support.hpp), [src/runtime/support.cpp](../../../../../src/runtime/support.cpp), [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/storage_journal.md](../../../../storage_journal.md) |

## B0020

[Lines 163–189](../../../../../tests/unit/epoch_index_test.cpp#L163); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void visible_bucket_supports_nullary_separator_and_leases() {
  SupportRuntime runtime(nullary_separator_plan());
  std::uint64_t sequence=0;
  apply(runtime,sequence,NodeId{0},SetOperation::insert,{n(1)});
  apply(runtime,sequence,NodeId{1},SetOperation::insert,{});
  check(runtime.plan().enumeration().steps.size()==2 &&
            runtime.plan().enumeration().steps[1].bucket_index.has_value() &&
            runtime.plan().indexes()[runtime.plan().enumeration().steps[1].bucket_index->value].projection.target().fields().empty(),
        "fixture did not compile an empty-separator child index");

  auto view=runtime.current_view();
  auto cursor=view.visible_bucket(NodeId{1},{});
  check(drain(cursor)==Relation{Row{}},"empty separator did not select the nullary E key");
  auto pinned=view.visible_bucket(NodeId{1},{});
  check(pinned.next().has_value(),"nullary bucket cursor could not open");
  expect_error([&] {
    static_cast<void>(runtime.apply({sequence+1,NodeId{1},SetOperation::erase,{}}));
  },"runtime_busy");
  pinned.cancel();
  expect_error([&] {
    static_cast<void>(runtime.apply({sequence+1,NodeId{1},SetOperation::erase,{}}));
  },"runtime_busy");
  view.close();
  const auto accepted=runtime.apply({sequence+1,NodeId{1},SetOperation::erase,{}});
  check(accepted.native_changed && accepted.sequence==sequence+1,
      "closing the view did not release the visible-bucket reader lease");
}

```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Test nullary separator lookup and show cancellation does not release a retained view lease. |
| inputs / outputs | Creates one root and one nullary child key, confirms the compiled empty-separator index, drains a nullary bucket, then keeps a second bucket cursor open across attempted erases. |
| invariants | Canceling the second cursor alone does not release the EpochView lease; writes remain runtime_busy until view.close(), after which erase advances sequence and succeeds. |
| ownership | Runtime owns indexed rows; view/cursors retain reader authority. The returned empty Row is exported into the helper Relation. |
| failure | The two erase attempts expect runtime_busy before view close; the final erase must report native_changed and the next sequence. |
| cost | One-row fixture plus two cursor constructions/drain and three update attempts. Lease checks are asserted directly; no allocator or zero-attempt denial counter is used. |
| Design | [tests/unit/epoch_index_test.cpp](../../../../../tests/unit/epoch_index_test.cpp), [include/crown/runtime/support.hpp](../../../../../include/crown/runtime/support.hpp), [src/runtime/support.cpp](../../../../../src/runtime/support.cpp), [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/storage_journal.md](../../../../storage_journal.md) |

## B0022

[Lines 191–207](../../../../../tests/unit/epoch_index_test.cpp#L191); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void rollback_aborts_open_bucket_cursor() {
  SupportRuntime runtime(bucket_plan());
  std::uint64_t sequence=0;
  apply(runtime,sequence,NodeId{0},SetOperation::insert,{n(1)});
  apply(runtime,sequence,NodeId{1},SetOperation::insert,{n(1),n(7)});
  auto pending=runtime.begin_epoch(sequence+1,SetOperation::erase);
  check(pending.stage(NodeId{1},{n(1),n(7)}),"rollback fixture did not erase its E key");
  auto before=pending.view(SnapshotSide::before);
  auto cursor=before.visible_bucket(NodeId{1},{n(1)});
  check(cursor.next().has_value(),"rollback fixture bucket cursor did not open");
  pending.rollback();
  check(!before.valid() && cursor.state()==ResultCursorState::failed && !cursor.active(),
      "rollback did not abort the visible-bucket cursor and prefix view");
  expect_error([&] { static_cast<void>(cursor.next()); },"invalid_cursor");
  before.close();
  apply(runtime,sequence,NodeId{1},SetOperation::insert,{n(1),n(8)});
}

```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Test rollback invalidates an open bucket cursor and restores writer readiness. |
| inputs / outputs | Seeds a root/child pair, stages child deletion, opens a before-view bucket cursor, rolls back, and checks that the view/cursor become invalid. |
| invariants | After rollback the cursor reports failed/inactive and next() raises invalid_cursor; closing the view releases the reader and a later child insert succeeds. |
| ownership | Pending owns the epoch; view and cursor retain its prefix reader until rollback invalidates them, while runtime remains caller-owned. |
| failure | The invalid cursor call must report invalid_cursor. Any other failed check or runtime error propagates to main. |
| cost | One staged delete, one cursor read, one rollback, one rejected next, and one subsequent insert; no large row sweep or allocator measurement. |
| Design | [tests/unit/epoch_index_test.cpp](../../../../../tests/unit/epoch_index_test.cpp), [include/crown/runtime/support.hpp](../../../../../include/crown/runtime/support.hpp), [src/runtime/support.cpp](../../../../../src/runtime/support.cpp), [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/storage_journal.md](../../../../storage_journal.md) |

## B0023

[Lines 208–210](../../../../../tests/unit/epoch_index_test.cpp#L208); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L208-L210:sha256:9e375a3cb3a2cbe2f9ded9c8296a6ab66848cc826fd71f919246acb17e0bd455
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Close the recorded declaration scopes in epoch_index_test.cpp: namespace (anonymous). |
| inputs / outputs | Preceding namespace, type or initializer declarations in; completed lexical boundary out. |
| invariants | Brace-opening context is recorded in root-scope-context-v1.json. These are declaration/initializer boundaries, not an independent update, validation or recovery operation. |
| ownership | Enclosing objects and borrowed fields keep their declared ownership. This punctuation creates no new owner. |
| failure | Malformed scope syntax is a compile error. Any initializer/constructor failure belongs to the enclosing object declaration. |
| cost | No separate loop, guard or engine call is introduced by the delimiter; enclosing initialization and object lifetime still have their actual costs. |
| Design | [tests/unit/epoch_index_test.cpp](../../../../../tests/unit/epoch_index_test.cpp), [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/code_review.md](../../../../code_review.md) |

## B0024

[Lines 211–221](../../../../../tests/unit/epoch_index_test.cpp#L211); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
int main() {
  try {
    restored_full_and_bucket_lookups_are_selective();
    visible_bucket_supports_nullary_separator_and_leases();
    rollback_aborts_open_bucket_cursor();
  } catch (const std::exception& failure) {
    std::cerr << failure.what() << '\n';
    return 1;
  }
  return 0;
}

```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Run the visible bucket, nullary separator, and rollback scenarios. |
| inputs / outputs | Runs the restored-key/bucket, nullary-separator/lease, and rollback/cursor-invalidity fixtures under an outer std::exception catch. |
| invariants | The three helpers independently own their runtimes and fixtures; success returns 0 and the first exception prints one diagnostic and returns 1. |
| ownership | Main retains no runtime after each helper returns; each helper scopes its own runtime, views, and cursors. |
| failure | Only std::exception is caught; non-standard exceptions escape. There is no error-code translation at this level. |
| cost | Runs the finite setup/update/query sequences of the three scenarios, including 48 staged deletions in the first. No native test execution or benchmark is claimed. |
| Design | [tests/unit/epoch_index_test.cpp](../../../../../tests/unit/epoch_index_test.cpp), [include/crown/runtime/support.hpp](../../../../../include/crown/runtime/support.hpp), [src/runtime/support.cpp](../../../../../src/runtime/support.cpp), [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/storage_journal.md](../../../../storage_journal.md) |
