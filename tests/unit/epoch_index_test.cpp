#include "crown/api/error.hpp"
#include "crown/planner/lower.hpp"
#include "crown/runtime/support.hpp"

#include <cstdint>
#include <iostream>
#include <optional>
#include <stdexcept>
#include <string>
#include <string_view>
#include <utility>

namespace {
using namespace crown;
using namespace crown::runtime;

void check(bool condition,const std::string& message) {
  if (!condition) throw std::runtime_error(message);
}

template<class Action>
void expect_error(Action&& action,std::string_view code) {
  try { action(); }
  catch (const Error& failure) {
    check(failure.code()==code,"expected "+std::string(code)+", got "+failure.code());
    return;
  }
  throw std::runtime_error("expected error "+std::string(code));
}

Value n(std::int64_t value) { return value; }

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

std::optional<storage::Tuple> next(SupportRuntime::ResultCursor& cursor) {
  return cursor.next();
}

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

void apply(SupportRuntime& runtime,std::uint64_t& sequence,NodeId node,SetOperation operation,Row row) {
  const auto epoch=runtime.apply({++sequence,node,operation,std::move(row)});
  check(epoch.sequence==sequence,"support update advanced to the wrong sequence");
}

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

}  // namespace

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
