#include "weighted_bag_fixture.hpp"
#include "index_allocation.hpp"
#include "crown/api/error.hpp"
#include <array>
#include <cstdint>
#include <iostream>
#include <map>
#include <optional>
#include <random>
#include <set>
#include <span>
#include <string>
#include <string_view>
#include <stdexcept>

namespace {
using namespace crown;
using namespace crown::weighted_test;
namespace w = crown::runtime::weighted;

using Signed = std::pair<bool,std::uint64_t>; // negative, magnitude
using DeltaMap = std::map<Row,Signed>;

template<class Action> void error(Action action, std::string_view code) {
  try {action();}
  catch (const Error& failure) {
    check(failure.code()==code,"unexpected weighted error: "+failure.code());return;
  }
  throw std::runtime_error("expected "+std::string(code));
}

DeltaMap difference(const Counts& before, const Counts& after) {
  std::set<Row> keys;
  for (const auto& [row,count]:before) {static_cast<void>(count);keys.insert(row);}
  for (const auto& [row,count]:after) {static_cast<void>(count);keys.insert(row);}
  DeltaMap result;
  for (const auto& row:keys) {
    const auto old=before.contains(row)?before.at(row):0;
    const auto next=after.contains(row)?after.at(row):0;
    if (old==next) continue;
    result.emplace(row,Signed{old>next,old>next?old-next:next-old});
  }
  return result;
}

DeltaMap read_deltas(std::span<const w::BagDelta> entries) {
  DeltaMap result;
  for (const auto& entry:entries) {
    check(entry.change.magnitude.present(),"zero net delta was retained");
    const auto row=storage::export_row(entry.tuple.values());
    check(result.emplace(row,Signed{entry.change.negative,entry.change.magnitude.value}).second,
        "duplicate projected tuple in delta handle");
  }
  return result;
}

Counts reference_bag(const runtime::WeightedRuntime& runtime, const Inputs& inputs) {
  return bag_oracle(runtime.structural_program(),inputs);
}

void compare_delta(const w::Epoch& epoch, const Counts& before, const Counts& after,
    std::uint64_t owner) {
  check(bool(epoch.bag_deltas),"enabled commit did not publish an owning delta handle");
  const auto actual=read_deltas(epoch.bag_deltas.entries());
  check(actual==difference(before,after),"signed delta differs from independent before/after bag oracle");
  for (const auto& entry:epoch.bag_deltas.entries())
    check(entry.tuple.layout().account_statistics().owner==owner,
        "delta tuple escaped the original runtime account");
}

DeltaMap preview_deltas(const runtime::WeightedRuntime::PendingEpoch& pending) {
  const auto preview=pending.bag_delta_preview();
  check(preview.has_value(),"enabled pending epoch returned disabled preview");
  return read_deltas(*preview); // Copy while the borrowed view is valid.
}

void replace_input(Inputs& inputs, std::size_t node, const Row& row, std::uint64_t after) {
  auto& table=inputs.at(node);
  if (after) table[row]=after;
  else table.erase(row);
}

void stage_replace(runtime::WeightedRuntime::PendingEpoch& pending, Inputs& inputs,
    std::size_t node, const Row& row, std::uint64_t before, std::uint64_t after) {
  const auto found=inputs.at(node).find(row);
  const auto current=found==inputs.at(node).end()?0:found->second;
  check(current==before,"test input mirror has a stale replacement precondition");
  check(before!=after,"stage_replace expects an actual input change");
  check(pending.stage({NodeId{node},row,{before},{after}}),"native replacement was reported as a no-op");
  replace_input(inputs,node,row,after);
}

void compare_runtime_bag(runtime::WeightedRuntime& runtime, const Inputs& inputs) {
  auto cursor=runtime.results();
  check(drain(cursor)==reference_bag(runtime,inputs),
      "committed output cursor differs from independent full-join bag oracle");
}

std::uint64_t delta_state_bytes(const runtime::WeightedRuntime& runtime) {
  const auto statistics=runtime.accounted_memory_statistics();
  return statistics.by_purpose[static_cast<std::size_t>(resource::MemoryPurpose::delta_state)].requested_bytes;
}

PhysicalPlan shared_key_path(bool indexed, std::optional<std::uint64_t> structural_limit={}) {
  const Catalog catalog{1,{{"r",{{"x",ScalarType::int64}}},
      {"s",{{"x",ScalarType::int64}}}}};
  const Query query{{{"x",ScalarType::int64}},
      {{"r",TableId{0},{VariableId{0}}},{"s",TableId{1},{VariableId{0}}}},
      {{VariableId{0},"x"}},false};
  const FreeConnexTree tree{NodeId{0},{
      {"r",NodeKind::native,{VariableId{0}},{NodeId{1}},0,{}},
      {"s",NodeKind::native,{VariableId{0}},{},1,{}}},{},{}};
  auto configured=options(indexed);
  if (structural_limit) configured.indexed_storage->per_operation.structural_steps=*structural_limit;
  return planner::lower_tree(catalog,query,tree,configured);
}

void opt_out(bool indexed) {
  Model model(unary(indexed));
  const auto before=reference_bag(model.runtime,model.inputs);
  const auto delta_bytes=delta_state_bytes(model.runtime);
  auto pending=model.runtime.begin_epoch(1); // One-argument form remains disabled.
  check(!pending.bag_delta_preview().has_value(),"default begin_epoch enabled delta capture");
  check(!pending.preview().bag_deltas,"pending Epoch exposed an unpublished delta handle");
  check(delta_state_bytes(model.runtime)==delta_bytes,"disabled epoch allocated delta state");
  auto after_inputs=model.inputs;
  stage_replace(pending,after_inputs,0,{n(7)},0,3);
  check(delta_state_bytes(model.runtime)==delta_bytes,"disabled stage allocated delta state");
  const auto after=reference_bag(model.runtime,after_inputs);
  const auto committed=pending.commit();
  check(!committed.bag_deltas,"opt-out commit published a delta handle");
  check(delta_state_bytes(model.runtime)==delta_bytes,"disabled commit retained delta state");
  check(after==Counts{{Row{n(7)},3}} && before.empty(),"opt-out reference bag setup");
  compare_runtime_bag(model.runtime,after_inputs);
}

void insert_delete_and_swap_remove(bool indexed) {
  {
    Model model(unary(indexed));
    const auto before=reference_bag(model.runtime,model.inputs);
    auto next_inputs=model.inputs;
    auto pending=model.runtime.begin_epoch(1,w::DeltaCapture::enabled);
    stage_replace(pending,next_inputs,0,{n(7)},0,2);
    check(preview_deltas(pending)==DeltaMap{{Row{n(7)},Signed{false,2}}},
        "first insertion preview");
    stage_replace(pending,next_inputs,0,{n(7)},2,0);
    check(preview_deltas(pending).empty(),"0-to-2-to-0 retained a public zero net fact");
    check(!pending.preview().bag_deltas,"pending Epoch published before commit");
    const auto after=reference_bag(model.runtime,next_inputs);
    const auto committed=pending.commit();
    compare_delta(committed,before,after,model.runtime.owner());
    check(committed.bag_deltas.entries().empty(),"captured no-op commit was not an enabled empty handle");
    compare_runtime_bag(model.runtime,next_inputs);
  }
  {
    Model model(unary(indexed));
    const auto before=reference_bag(model.runtime,model.inputs);
    auto next_inputs=model.inputs;
    auto pending=model.runtime.begin_epoch(1,w::DeltaCapture::enabled);
    stage_replace(pending,next_inputs,0,{n(1)},0,1); // Slot 0.
    stage_replace(pending,next_inputs,0,{n(2)},0,2); // Last slot.
    stage_replace(pending,next_inputs,0,{n(1)},1,0); // Cancel slot 0; move slot 1 into it.
    const DeltaMap expected{{Row{n(2)},Signed{false,2}}};
    check(preview_deltas(pending)==expected,"cancellation failed to repair the moved lookup slot");
    const auto after=reference_bag(model.runtime,next_inputs);
    const auto committed=pending.commit();
    compare_delta(committed,before,after,model.runtime.owner());
    check(committed.bag_deltas.entries().size()==1,"swap removal left a canceled fact resident");
    compare_runtime_bag(model.runtime,next_inputs);
  }
}

void absent_anchor_and_cross_term(bool indexed) {
  {
    Model model(counted_path(indexed));
    const auto before=reference_bag(model.runtime,model.inputs);
    auto next_inputs=model.inputs;
    auto pending=model.runtime.begin_epoch(1,w::DeltaCapture::enabled);
    stage_replace(pending,next_inputs,0,{n(1),n(10),n(100)},0,2);
    check(preview_deltas(pending).empty(),"unsupported root row emitted output");
    check(pending.preview().after.value==0,"root summary changed before the child existed");
    stage_replace(pending,next_inputs,1,{n(10),n(20)},0,3);
    const DeltaMap expected{{Row{n(1),n(10)},Signed{false,6}}};
    check(preview_deltas(pending)==expected,
        "new answer was lost while its root summary was absent at earlier factor changes");
    const auto after=reference_bag(model.runtime,next_inputs);
    const auto committed=pending.commit();
    compare_delta(committed,before,after,model.runtime.owner());
    check(after==Counts{{Row{n(1),n(10)},6}},"empty-to-populated hand result");
    compare_runtime_bag(model.runtime,next_inputs);
  }
  {
    BagModel model(counted_path(indexed));
    model.set(0,{n(1),n(10),n(100)},2);
    model.set(1,{n(10),n(20)},3);
    const auto before_inputs=model.inputs;
    const auto before=reference_bag(model.runtime,before_inputs);
    auto next_inputs=before_inputs;
    auto pending=model.runtime.begin_epoch(model.runtime.sequence()+1,w::DeltaCapture::enabled);
    stage_replace(pending,next_inputs,0,{n(1),n(10),n(100)},2,4);
    check(preview_deltas(pending)==DeltaMap{{Row{n(1),n(10)},Signed{false,6}}},
        "first telescoping term did not use the old child factor");
    stage_replace(pending,next_inputs,1,{n(10),n(20)},3,5);
    const DeltaMap expected{{Row{n(1),n(10)},Signed{false,14}}};
    check(preview_deltas(pending)==expected,
        "staged join delta replayed final factors instead of telescoping cross terms");
    check(!pending.preview().bag_deltas,"cross-term pending handle escaped before commit");
    const auto after=reference_bag(model.runtime,next_inputs);
    const auto committed=pending.commit();
    compare_delta(committed,before,after,model.runtime.owner());
    check(before==Counts{{Row{n(1),n(10)},6}} && after==Counts{{Row{n(1),n(10)},20}},
        "cross-term hand result");
    compare_runtime_bag(model.runtime,next_inputs);
  }
}

void dead_prefix_is_pruned(bool indexed) {
  w::Options configured;configured.multiplicity_limit=100;
  Model model(shared_key_path(indexed),configured);
  model.set(0,{n(1)},40);model.set(0,{n(2)},1);model.set(1,{n(1)},1);
  check(model.runtime.root_weight().value==40,"dead-prefix initial root");
  const auto before_inputs=model.inputs;
  const auto before=reference_bag(model.runtime,before_inputs);
  auto next_inputs=before_inputs;
  auto pending=model.runtime.begin_epoch(model.runtime.sequence()+1,w::DeltaCapture::enabled);
  stage_replace(pending,next_inputs,1,{n(2)},0,50);
  check(pending.preview().before.value==40 && pending.preview().after.value==90,
      "dead-prefix root must move from 40 to 90 under limit 100");
  const DeltaMap expected{{Row{n(2)},Signed{false,50}}};
  check(preview_deltas(pending)==expected,
      "anchor mismatch did not prune R(a) before multiplying by S(b)=50");
  const auto after=reference_bag(model.runtime,next_inputs);
  const auto committed=pending.commit();
  compare_delta(committed,before,after,model.runtime.owner());
  check(before==Counts{{Row{n(1)},40}} && after==Counts{{Row{n(1)},40},{Row{n(2)},50}},
      "dead-prefix projected bag hand result");
  compare_runtime_bag(model.runtime,next_inputs);
}

void hidden_projection_and_repeated_head(bool indexed) {
  {
    Model model(path(indexed));
    model.set(0,{n(1),n(10)},2);model.set(0,{n(1),n(11)},3);
    model.set(1,{n(10),n(20)},7);model.set(1,{n(11),n(21)},11);
    model.set(2,{n(20)},13);model.set(2,{n(21)},17);
    const auto before_inputs=model.inputs;
    const auto before=reference_bag(model.runtime,before_inputs);
    auto next_inputs=before_inputs;
    auto pending=model.runtime.begin_epoch(model.runtime.sequence()+1,w::DeltaCapture::enabled);
    stage_replace(pending,next_inputs,1,{n(10),n(20)},7,8);
    const DeltaMap expected{{Row{n(1)},Signed{false,26}}};
    check(preview_deltas(pending)==expected,"hidden y/z contributions did not consolidate to x");
    const auto after=reference_bag(model.runtime,next_inputs);
    const auto committed=pending.commit();
    compare_delta(committed,before,after,model.runtime.owner());
    check(before==Counts{{Row{n(1)},743}} && after==Counts{{Row{n(1)},769}},
        "hidden assignment sum hand result");
    compare_runtime_bag(model.runtime,next_inputs);
  }
  {
    Model model(counted_path(indexed,false,true));
    model.set(0,{n(1),n(10),n(100)},2);
    model.set(0,{n(1),n(10),n(101)},3);
    model.set(1,{n(10),n(20)},3);
    const auto before_inputs=model.inputs;
    const auto before=reference_bag(model.runtime,before_inputs);
    auto next_inputs=before_inputs;
    auto pending=model.runtime.begin_epoch(model.runtime.sequence()+1,w::DeltaCapture::enabled);
    stage_replace(pending,next_inputs,0,{n(1),n(10),n(100)},2,4);
    const DeltaMap expected{{Row{n(10),n(1),n(10)},Signed{false,6}}};
    check(preview_deltas(pending)==expected,"repeated head positions changed delta tuple layout");
    const auto after=reference_bag(model.runtime,next_inputs);
    const auto committed=pending.commit();
    compare_delta(committed,before,after,model.runtime.owner());
    check(before==Counts{{Row{n(10),n(1),n(10)},15}} &&
        after==Counts{{Row{n(10),n(1),n(10)},21}},"repeated-head hidden-row hand result");
    compare_runtime_bag(model.runtime,next_inputs);
  }
}

void generalized_factor(bool indexed) {
  Model model(generalized(indexed));
  model.set(1,{n(1)},11);
  model.set(3,{n(1),n(10),n(100)},2);model.set(3,{n(1),n(20),n(200)},3);
  model.set(4,{n(1),n(10),n(300)},5);model.set(4,{n(1),n(20),n(400)},7);
  const auto before_inputs=model.inputs;
  const auto before=reference_bag(model.runtime,before_inputs);
  auto next_inputs=before_inputs;
  auto pending=model.runtime.begin_epoch(model.runtime.sequence()+1,w::DeltaCapture::enabled);
  stage_replace(pending,next_inputs,3,{n(1),n(10),n(100)},2,4);
  const DeltaMap expected{{Row{n(1)},Signed{false,110}}};
  check(preview_deltas(pending)==expected,"generalized hidden-scope factor did not sum exactly once");
  const auto after=reference_bag(model.runtime,next_inputs);
  const auto committed=pending.commit();
  compare_delta(committed,before,after,model.runtime.owner());
  check(before==Counts{{Row{n(1)},341}} && after==Counts{{Row{n(1)},451}},
      "generalized hidden-scope hand result");
  compare_runtime_bag(model.runtime,next_inputs);
}

void nullary_unsigned_magnitude(bool indexed) {
  Model model(unary(indexed,true,true));
  const auto before_inputs=model.inputs;
  const auto before=reference_bag(model.runtime,before_inputs);
  auto inserted_inputs=before_inputs;
  auto insert=model.runtime.begin_epoch(1,w::DeltaCapture::enabled);
  stage_replace(insert,inserted_inputs,0,Row{},0,UINT64_MAX);
  const auto full=reference_bag(model.runtime,inserted_inputs);
  const auto positive=insert.commit();
  compare_delta(positive,before,full,model.runtime.owner());
  check(full==Counts{{Row{},UINT64_MAX}},"nullary UINT64_MAX output bag");
  check(read_deltas(positive.bag_deltas.entries())==
      DeltaMap{{Row{},Signed{false,UINT64_MAX}}},"positive magnitude narrowed to signed int64");
  compare_runtime_bag(model.runtime,inserted_inputs);

  auto deleted_inputs=inserted_inputs;
  auto erase=model.runtime.begin_epoch(2,w::DeltaCapture::enabled);
  stage_replace(erase,deleted_inputs,0,Row{},UINT64_MAX,0);
  const auto empty=reference_bag(model.runtime,deleted_inputs);
  const auto negative=erase.commit();
  compare_delta(negative,full,empty,model.runtime.owner());
  check(empty.empty() && read_deltas(negative.bag_deltas.entries())==
      DeltaMap{{Row{},Signed{true,UINT64_MAX}}},"negative magnitude narrowed or retained zero");
  compare_runtime_bag(model.runtime,deleted_inputs);
}

void typed_string_ownership(bool indexed) {
  std::optional<w::Epoch> retained;
  resource::MemoryAccount account;
  std::uint64_t owner=0;
  DeltaMap expected;
  const std::string name=std::string(256,'x')+"0";
  {
    Model model(typed_bag(indexed));typed_inputs(model);
    owner=model.runtime.owner();account=model.runtime.structural_program().account();
    const auto before_inputs=model.inputs;
    const auto before=reference_bag(model.runtime,before_inputs);
    auto after_inputs=before_inputs;
    auto pending=model.runtime.begin_epoch(model.runtime.sequence()+1,w::DeltaCapture::enabled);
    stage_replace(pending,after_inputs,0,
        {Value{name},n(7),Value{Date::parse("2026-11-11")}},2,4);
    const auto after=reference_bag(model.runtime,after_inputs);
    expected=difference(before,after);
    check(expected.size()==2,"typed string fixture did not emit two flag rows");
    retained.emplace(pending.commit());
    compare_delta(*retained,before,after,owner);
    check(read_deltas(retained->bag_deltas.entries())==DeltaMap{
        {Row{Value{false},Value{name},Value{Date::parse("2026-11-11")},Value{name},n(7)},Signed{false,6}},
        {Row{Value{true},Value{name},Value{Date::parse("2026-11-11")},Value{name},n(7)},Signed{false,10}}},
        "typed/repeated string output delta");
  }
  check(read_deltas(retained->bag_deltas.entries())==expected,
      "committed delta facts failed after runtime destruction");
  for (const auto& entry:retained->bag_deltas.entries()) {
    const auto row=storage::export_row(entry.tuple.values());
    check(std::get<std::string>(row[1])==name && row[1]==row[3],
        "owned long string or repeated output field changed after runtime destruction");
    check(entry.tuple.layout().account_statistics().owner==owner,
        "retained delta tuple lost its original account owner");
  }
  retained.reset();
  check(account.statistics().current.requested_bytes==resource::MemoryAccount::control_bytes(),
      "dropping the last committed delta handle leaked original-account bytes");
}

std::pair<std::uint64_t,std::uint64_t> measured_cross_term_work(bool indexed) {
  Model model(counted_path(indexed));
  auto pending=model.runtime.begin_epoch(1,w::DeltaCapture::enabled);
  check(pending.stage({NodeId{0},{n(1),n(10),n(100)},{0},{2}}),"work probe root insertion");
  const auto first=pending.preview().metrics.work;
  check(pending.stage({NodeId{1},{n(10),n(20)},{0},{3}}),"work probe child insertion");
  const auto complete=pending.preview().metrics.work;
  pending.rollback();
  check(complete>1 && first<complete-1,"work probe lacks a stage boundary for failure/retry");
  return {first,complete};
}

void resource_failure_rollback_and_retry(bool indexed) {
  const auto [first_work,complete_work]=measured_cross_term_work(indexed);
  w::Options configured;configured.work_limit=complete_work-1;
  Model model(counted_path(indexed),configured);
  const auto original=reference_bag(model.runtime,model.inputs);
  const auto sequence=model.runtime.sequence()+1;
  {
    auto pending=model.runtime.begin_epoch(sequence,w::DeltaCapture::enabled);
    check(pending.stage({NodeId{0},{n(1),n(10),n(100)},{0},{2}}),
        "first stage should fit the measured cumulative work limit");
    check(pending.preview().metrics.work==first_work,"first-stage work changed from measurement");
    error([&]{static_cast<void>(pending.stage({NodeId{1},{n(10),n(20)},{0},{3}}));},"resource_limit");
    check(!pending.active(),"work exhaustion did not abort the complete pending token");
  }
  check(model.runtime.ready() && model.runtime.sequence()==sequence-1 &&
      model.runtime.root_weight().value==0,"work exhaustion published partial native state");
  const auto attempt=model.runtime.last_attempt();
  check(attempt && attempt->phase==w::Phase::aborted &&
      attempt->metrics.work<=*configured.work_limit && attempt->metrics.work>=first_work,
      "aborted work diagnostic did not retain the spent stage work");
  check(reference_bag(model.runtime,model.inputs)==original,"rollback changed the independent input mirror");
  compare_runtime_bag(model.runtime,model.inputs);

  auto retry_inputs=model.inputs;
  auto retry=model.runtime.begin_epoch(sequence,w::DeltaCapture::enabled);
  stage_replace(retry,retry_inputs,0,{n(1),n(10),n(100)},0,2);
  const auto after=reference_bag(model.runtime,retry_inputs);
  const auto committed=retry.commit();
  compare_delta(committed,original,after,model.runtime.owner());
  check(committed.bag_deltas.entries().empty(),"retry root-only insertion should remain unsupported");
  compare_runtime_bag(model.runtime,retry_inputs);
}

// Intermediate stages use private state. Compare their net after every edit,
// including cancellation, against full native joins in this test-only mirror.
void randomized_batches(bool indexed) {
  Model model(counted_path(indexed,true,true));
  std::mt19937_64 random(0x7064656c7461ULL);
  for (unsigned epoch=0;epoch<64;++epoch) {
    const auto before=reference_bag(model.runtime,model.inputs);
    auto next_inputs=model.inputs;
    auto pending=model.runtime.begin_epoch(model.runtime.sequence()+1,w::DeltaCapture::enabled);
    for (unsigned stage=0;stage<6;++stage) {
      const auto node=static_cast<std::size_t>(random()%3);
      Row row;
      if (node==0) row={n(static_cast<std::int64_t>(random()%3)),
          n(static_cast<std::int64_t>(random()%3)),n(static_cast<std::int64_t>(random()%2))};
      else if (node==1) row={n(static_cast<std::int64_t>(random()%3)),n(static_cast<std::int64_t>(random()%3))};
      else row={n(static_cast<std::int64_t>(random()%3))};
      const auto found=next_inputs[node].find(row);
      const auto old=found==next_inputs[node].end()?0:found->second;
      const auto next=random()%5;
      if (old!=next) stage_replace(pending,next_inputs,node,row,old,next);
      check(preview_deltas(pending)==difference(before,reference_bag(model.runtime,next_inputs)),
          "random staged net differs from full native joins");
    }
    const auto after=reference_bag(model.runtime,next_inputs);
    const auto committed=pending.commit();
    compare_delta(committed,before,after,model.runtime.owner());
    compare_runtime_bag(model.runtime,next_inputs);
    model.inputs=std::move(next_inputs);
  }
}

void arithmetic_failure_rollback(bool indexed) {
  w::Options configured;configured.multiplicity_limit=10;
  Model model(unary(indexed),configured);model.set(0,{n(1)},9);
  const auto original=reference_bag(model.runtime,model.inputs);
  auto pending=model.runtime.begin_epoch(2,w::DeltaCapture::enabled);
  static_cast<void>(pending.stage({NodeId{0},{n(1)},{9},{8}}));
  error([&]{static_cast<void>(pending.stage({NodeId{0},{n(2)},{0},{3}}));},"annotation_overflow");
  check(!pending.active() && model.runtime.ready() && model.runtime.sequence()==1 &&
      model.runtime.root_weight().value==9,"arithmetic failure published an earlier private stage");
  compare_runtime_bag(model.runtime,model.inputs);
  auto next_inputs=model.inputs;
  auto retry=model.runtime.begin_epoch(2,w::DeltaCapture::enabled);
  stage_replace(retry,next_inputs,0,{n(1)},9,7);
  const auto committed=retry.commit();
  compare_delta(committed,original,reference_bag(model.runtime,next_inputs),model.runtime.owner());
}

// Deny each covered C++ new attempt in the exact native scenario. Oracle/Row
// setup is outside the seam; this neither intercepts all malloc nor measures CPU.
void allocation_cuts(bool indexed) {
  const std::array<w::Replacement,4> edits{{
      {NodeId{0},{n(1),n(10),n(100)},{0},{2}},
      {NodeId{0},{n(2),n(10),n(100)},{0},{3}},
      {NodeId{1},{n(10),n(20)},{0},{5}},
      {NodeId{0},{n(1),n(10),n(100)},{2},{0}}}};
  const auto stage_all=[&](runtime::WeightedRuntime::PendingEpoch& pending) {
    for (const auto& edit:edits) static_cast<void>(pending.stage(edit));
  };
  std::size_t allocations=0;
  {
    Model measured(counted_path(indexed));
    s04_alloc::Scope count;
    auto pending=measured.runtime.begin_epoch(1,w::DeltaCapture::enabled);
    stage_all(pending);static_cast<void>(pending.commit());allocations=s04_alloc::calls;
  }
  check(allocations>0,"empty enabled allocation-cut scenario");
  for (std::size_t cut=0;cut<allocations;++cut) {
    resource::MemoryAccount account;
    {
      Model model(counted_path(indexed));account=model.runtime.structural_program().account();
      bool rejected=false;
      {
        s04_alloc::Scope fail(static_cast<std::ptrdiff_t>(cut));
        try {
          auto pending=model.runtime.begin_epoch(1,w::DeltaCapture::enabled);
          stage_all(pending);static_cast<void>(pending.commit());
        } catch (const std::bad_alloc&) {rejected=true;}
      }
      check(rejected && s04_alloc::triggered,"enabled allocation cut was not observed");
      check(model.runtime.ready() && model.runtime.sequence()==0 && model.runtime.root_weight().value==0,
          "allocation cut published private source/factor state");
      compare_runtime_bag(model.runtime,model.inputs);
      auto retry=model.runtime.begin_epoch(1,w::DeltaCapture::enabled);
      stage_all(retry);const auto committed=retry.commit();
      auto next_inputs=model.inputs;
      for (const auto& edit:edits) replace_input(next_inputs,edit.node.value,edit.values,edit.after.value);
      compare_delta(committed,{},reference_bag(model.runtime,next_inputs),model.runtime.owner());
      compare_runtime_bag(model.runtime,next_inputs);
    }
    check(account.statistics().current.requested_bytes==resource::MemoryAccount::control_bytes(),
        "failed/retried delta capture leaked the receiving account");
  }
  std::cout<<"enabled delta allocation cuts backend="<<(indexed?"indexed":"ordered")
      <<" positions="<<allocations<<'\n';
}

void publication_uses_prepared_storage(bool indexed) {
  for (const bool commit:{false,true}) {
    Model model(unary(indexed));
    auto pending=model.runtime.begin_epoch(1,w::DeltaCapture::enabled);
    static_cast<void>(pending.stage({NodeId{0},{n(1)},{0},{2}}));
    std::optional<w::Epoch> output;
    std::size_t calls=0;
    {
      s04_alloc::Scope fail(0);
      if (commit) output.emplace(pending.commit());else pending.rollback();
      calls=s04_alloc::calls;
    }
    check(calls==0 && !s04_alloc::triggered,"prepared delta publication or rollback used C++ new");
    if (commit) check(read_deltas(output->bag_deltas.entries())==DeltaMap{{Row{n(1)},Signed{false,2}}},
        "nonallocating publication lost its owning facts");
    else check(model.runtime.ready() && model.runtime.sequence()==0,"nonallocating rollback published state");
  }
}

// A caller owns the physical shares; this port edits their logical total.
// The private aggregate changes 5→7→5, so the captured projected net cancels.
void contribution_changes(bool indexed) {
  Model model(unary(indexed));const Row row{n(7)};model.set(0,row,5);
  const auto original=reference_bag(model.runtime,model.inputs);
  auto pending=model.runtime.begin_epoch(2,w::DeltaCapture::enabled);
  check(pending.stage_contribution(NodeId{0},storage::TupleValuesView::borrow(row),{2},{4}),
      "enabled first contribution was a no-op");
  check(preview_deltas(pending)==DeltaMap{{row,Signed{false,2}}},"enabled contribution missed its intermediate net");
  check(pending.stage_contribution(NodeId{0},storage::TupleValuesView::borrow(row),{3},{1}),
      "enabled opposite contribution was a no-op");
  check(preview_deltas(pending).empty(),"opposite logical shares did not cancel captured output");
  const auto canceled=pending.commit();
  compare_delta(canceled,original,original,model.runtime.owner());
  compare_runtime_bag(model.runtime,model.inputs);
  auto next_inputs=model.inputs;
  auto next=model.runtime.begin_epoch(3,w::DeltaCapture::enabled);
  static_cast<void>(next.stage_contribution(NodeId{0},storage::TupleValuesView::borrow(row),{1},{3}));
  replace_input(next_inputs,0,row,7);
  const auto changed=next.commit();
  compare_delta(changed,original,reference_bag(model.runtime,next_inputs),model.runtime.owner());
  compare_runtime_bag(model.runtime,next_inputs);
}

// Measure actual indexed work, then replay exact and one-below limits across
// 64 resumed stages. Capture cursor work must spend this same native allowance.
std::uint64_t enabled_native_grant_scenario(std::optional<std::uint64_t> limit,
    w::DeltaCapture capture, bool reject) {
  Model model(shared_key_path(true,limit));
  model.set(0,{n(1)},2);model.set(0,{n(2)},3);
  model.set(1,{n(1)},5);model.set(1,{n(2)},7);
  const auto original=reference_bag(model.runtime,model.inputs);
  auto pending=model.runtime.begin_epoch(5,capture);
  std::uint64_t previous=0;
  bool rejected=false;
  try {
    for (std::uint64_t weight=6;weight<70;++weight) {
      static_cast<void>(pending.stage({NodeId{1},{n(1)},{weight-1},{weight}}));
      const auto spent=pending.preview().metrics.native_grant_consumed.structural_steps;
      check(spent>previous,"enabled resumed stage refilled its native grant");previous=spent;
    }
  } catch (const storage::IndexFailure& failure) {
    check(failure.code()=="storage_work_limit","unexpected enabled native-grant error");rejected=true;
  }
  check(rejected==reject,"enabled native-grant threshold disagreed");
  if (rejected) {
    check(!pending.active() && model.runtime.ready() && model.runtime.sequence()==4,
        "native-grant exhaustion published a private stage");
    compare_runtime_bag(model.runtime,model.inputs);return 0;
  }
  auto next_inputs=model.inputs;replace_input(next_inputs,1,{n(1)},69);
  const auto committed=pending.commit();
  if (capture==w::DeltaCapture::enabled)
    compare_delta(committed,original,reference_bag(model.runtime,next_inputs),model.runtime.owner());
  compare_runtime_bag(model.runtime,next_inputs);
  return committed.metrics.native_grant_consumed.structural_steps;
}

void enabled_native_grant() {
  const auto disabled=enabled_native_grant_scenario({},w::DeltaCapture::disabled,false);
  const auto enabled=enabled_native_grant_scenario({},w::DeltaCapture::enabled,false);
  check(enabled>disabled,"private capture cursors did not debit native indexed work");
  check(enabled_native_grant_scenario(enabled,w::DeltaCapture::enabled,false)==enabled,
      "exact enabled native grant changed its consumed work");
  static_cast<void>(enabled_native_grant_scenario(enabled-1,w::DeltaCapture::enabled,true));
  std::cout<<"delta native structural grant disabled="<<disabled<<" enabled="<<enabled<<'\n';
}

} // namespace

int main() {
  try {
    for (const bool indexed:{false,true}) {
      opt_out(indexed);
      insert_delete_and_swap_remove(indexed);
      absent_anchor_and_cross_term(indexed);
      dead_prefix_is_pruned(indexed);
      hidden_projection_and_repeated_head(indexed);
      generalized_factor(indexed);
      nullary_unsigned_magnitude(indexed);
      typed_string_ownership(indexed);
      resource_failure_rollback_and_retry(indexed);
      randomized_batches(indexed);
      arithmetic_failure_rollback(indexed);
      allocation_cuts(indexed);
      publication_uses_prepared_storage(indexed);
      contribution_changes(indexed);
    }
    enabled_native_grant();
    std::cout<<"weighted projected-bag deltas match independent before/after joins\n";
  } catch (const std::exception& failure) {std::cerr<<failure.what()<<'\n';return 1;}
}
