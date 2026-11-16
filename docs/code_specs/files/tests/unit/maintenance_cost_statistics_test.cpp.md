# `tests/unit/maintenance_cost_statistics_test.cpp` — block usage map

[Source](../../../../../tests/unit/maintenance_cost_statistics_test.cpp) · [Source index](../../../README.md) · [Subsystem contracts](../../../subsystem_contracts.md) · [Reviewed primitives](../../../primitives.md)

Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection.

Snapshot SHA-256: `dd218184f730c0ca7f633f70bbf8a0abb23a4dc02f81f1560fa0a215a55727af`. 143 lines partitioned into 10 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [tests](../../../subsystem_contracts.md#tests). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/code_review.md](../../../../code_review.md), [docs/reference_fuzz.md](../../../../reference_fuzz.md), [docs/task_ledger.md](../../../../task_ledger.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–15](../../../../../tests/unit/maintenance_cost_statistics_test.cpp#L1) | Imports dependencies; controls preprocessing; declares namespace scope; declares aliases; declares values/defaults or compile-time conditions. |  · [reviewed contract](#b0001) |
| [B0002 · 16–20](../../../../../tests/unit/maintenance_cost_statistics_test.cpp#L16) | Callable definition: std::vector&lt;cost::CalibrationSample&gt; rates() | calls push_back; returns result; growth push_back; 1 loop sites · [reviewed contract](#b0002) |
| [B0003 · 21–24](../../../../../tests/unit/maintenance_cost_statistics_test.cpp#L21) | Callable definition: std::vector&lt;cost::InputDemand&gt; demand(std::uint64_t inserts,std::uint64_t erases=0) | calls ; returns {{{0},ws::Operation::insert,inserts},{{0},ws::Operation::erase,erases},; growth insert · [reviewed contract](#b0003) |
| [B0004 · 25–28](../../../../../tests/unit/maintenance_cost_statistics_test.cpp#L25) | Callable definition: std::size_t native_index(const planner::CandidateSnapshot& set) | calls candidate_count, shape, candidate, tree; returns i; 1 loop sites · [reviewed contract](#b0004) |
| [B0005 · 29–31](../../../../../tests/unit/maintenance_cost_statistics_test.cpp#L29) | Callable definition: void apply(runtime::PhysicalRuntime& owner,SetOperation operation,std::int64_t value) | calls sequence · [reviewed contract](#b0005) |
| [B0006 · 32–120](../../../../../tests/unit/maintenance_cost_statistics_test.cpp#L32) | Callable definition: void test_backend(bool indexed) | calls fixture, candidates, native_index, planner::lower_tree; guard const auto captured=cost::capture(set,index,owner);check(captured.profile.has_value(),"sampled nati…; returns *capture.profile; growth insert; 2 loop sites; source comment (unverified): // Global attempts1/3 are sampled and change R. Attempts2/4 are unsampled · [reviewed contract](#b0006) |
| [B0007 · 121–121](../../../../../tests/unit/maintenance_cost_statistics_test.cpp#L121) | controls preprocessing. |  · [reviewed contract](#b0007) |
| [B0008 · 122–136](../../../../../tests/unit/maintenance_cost_statistics_test.cpp#L122) | Callable definition: void saturation(bool indexed) | calls fixture, candidates, native_index, planner::lower_tree; guard const auto captured=cost::capture(set,index,owner);check(captured.profile.has_value(),"saturated ac…; growth insert · [reviewed contract](#b0008) |
| [B0009 · 137–138](../../../../../tests/unit/maintenance_cost_statistics_test.cpp#L137) | controls preprocessing. |  · [reviewed contract](#b0009) |
| [B0010 · 139–143](../../../../../tests/unit/maintenance_cost_statistics_test.cpp#L139) | Callable definition: int main() | calls test_backend, saturation, what; returns 1; 2 loop sites · [reviewed contract](#b0010) |

## B0001

[Lines 1–15](../../../../../tests/unit/maintenance_cost_statistics_test.cpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L1-L15:sha256:a242c4c56fc7824b379f0b2cc64986dbb4ad9b8fd93d818e5ae8b88a676abd22
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Prepare maintenance_cost_statistics_test.cpp: include "ranking_fixture.hpp", "indexed_runtime_fixture.hpp", "crown/runtime/maintenance_cost.hpp", "runtime_probe.hpp", &lt;array&gt;, &lt;iostream&gt;; bind local aliases/name imports; select the recorded test ABI/preprocessor branch. |
| inputs / outputs | Compiler-visible dependencies, names and the recorded declarations in; declarations available to the following fixture/CLI/example definitions out. |
| invariants | Declarations are scoped to this source/header and its selected ABI. Included code has its own effects; names and editable fixture values do not confer proof, admission or publication authority. |
| ownership | Aliases/includes do not create a query owner. Pointers/references/views are non-owning. Containers own their elements, which can themselves be borrowed pointers or numeric IDs. Only documented owning shared-control handles retain controls; IDs/slot-handle values do not independently keep an arena/runtime alive. |
| failure | Missing headers, ill-formed names/types, failed static assertions or active #error directives stop compilation. No runtime rejection/rollback mechanism is implemented by aliases or function prototypes. |
| cost | Preprocessing and type/constraint instantiation cost compilation. Alias/prototype syntax does not invoke the declared operation; any included definitions keep their own initialization effects. |
| Design | [tests/unit/maintenance_cost_statistics_test.cpp](../../../../../tests/unit/maintenance_cost_statistics_test.cpp), [docs/maintenance_cost.md](../../../../maintenance_cost.md), [docs/code_review.md](../../../../code_review.md) |

## B0002

[Lines 16–20](../../../../../tests/unit/maintenance_cost_statistics_test.cpp#L16); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::vector<cost::CalibrationSample> rates() {
  std::vector<cost::CalibrationSample> result;
  for(std::size_t i=0;i<cost::component_count;++i)result.push_back({static_cast<C>(i),1,1});
  return result;
}

```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Create one isolated unit-rate sample for every C03 component. |
| inputs / outputs | Returns a vector with each Component and units=1, elapsed_ns=1. |
| invariants | Every component receives the same synthetic ratio, regardless of actual runtime. |
| ownership | The returned vector owns its sample records. |
| failure | Vector allocation can fail; there is no recovery logic here. |
| cost | Appends component_count records; no runtime operation is measured. |
| Design | [tests/unit/maintenance_cost_statistics_test.cpp](../../../../../tests/unit/maintenance_cost_statistics_test.cpp), [include/crown/runtime/maintenance_cost.hpp](../../../../../include/crown/runtime/maintenance_cost.hpp), [src/runtime/maintenance_cost.cpp](../../../../../src/runtime/maintenance_cost.cpp), [docs/maintenance_cost.md](../../../../maintenance_cost.md), [tests/support/indexed_runtime_fixture.hpp](../../../../../tests/support/indexed_runtime_fixture.hpp), [tests/support/ranking_fixture.hpp](../../../../../tests/support/ranking_fixture.hpp) |

## B0003

[Lines 21–24](../../../../../tests/unit/maintenance_cost_statistics_test.cpp#L21); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::vector<cost::InputDemand> demand(std::uint64_t inserts,std::uint64_t erases=0) {
  return {{{0},ws::Operation::insert,inserts},{{0},ws::Operation::erase,erases},
    {{1},ws::Operation::insert,0},{{1},ws::Operation::erase,0},{{2},ws::Operation::insert,0},{{2},ws::Operation::erase,0}};
}

```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Declare inserts and erases for table 0 and explicit zero demand elsewhere. |
| inputs / outputs | Returns six InputDemand rows: two operations for each of tables 0, 1, and 2. |
| invariants | All table/operation strata are present exactly once; tables 1 and 2 have zero demand. |
| ownership | Caller owns the returned vector; estimate receives a span during the call. |
| failure | The helper has no domain failure path beyond allocation. |
| cost | Constructs six small records. |
| Design | [tests/unit/maintenance_cost_statistics_test.cpp](../../../../../tests/unit/maintenance_cost_statistics_test.cpp), [include/crown/runtime/maintenance_cost.hpp](../../../../../include/crown/runtime/maintenance_cost.hpp), [src/runtime/maintenance_cost.cpp](../../../../../src/runtime/maintenance_cost.cpp), [docs/maintenance_cost.md](../../../../maintenance_cost.md), [tests/support/indexed_runtime_fixture.hpp](../../../../../tests/support/indexed_runtime_fixture.hpp), [tests/support/ranking_fixture.hpp](../../../../../tests/support/ranking_fixture.hpp) |

## B0004

[Lines 25–28](../../../../../tests/unit/maintenance_cost_statistics_test.cpp#L25); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::size_t native_index(const planner::CandidateSnapshot& set) {
  for(std::size_t i=0;i<set.candidate_count();++i)if(shape(set.candidate(i)->tree())==0)return i;
  throw std::runtime_error("native candidate absent");
}

```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Find the fixture candidate whose tree has native shape 0. |
| inputs / outputs | Scans a CandidateSnapshot and returns its first matching index. |
| invariants | Absence is an error; it does not silently select candidate zero. |
| ownership | Snapshot is borrowed; only the index escapes. |
| failure | Throws runtime_error if no native candidate exists. |
| cost | Linear scan up to candidate_count; shape is checked per candidate. |
| Design | [tests/unit/maintenance_cost_statistics_test.cpp](../../../../../tests/unit/maintenance_cost_statistics_test.cpp), [include/crown/runtime/maintenance_cost.hpp](../../../../../include/crown/runtime/maintenance_cost.hpp), [src/runtime/maintenance_cost.cpp](../../../../../src/runtime/maintenance_cost.cpp), [docs/maintenance_cost.md](../../../../maintenance_cost.md), [tests/support/indexed_runtime_fixture.hpp](../../../../../tests/support/indexed_runtime_fixture.hpp), [tests/support/ranking_fixture.hpp](../../../../../tests/support/ranking_fixture.hpp) |

## B0005

[Lines 29–31](../../../../../tests/unit/maintenance_cost_statistics_test.cpp#L29); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void apply(runtime::PhysicalRuntime& owner,SetOperation operation,std::int64_t value) {
  static_cast<void>(owner.apply({owner.sequence()+1,{0},operation,Row{value}}));
}

```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Advance a physical owner by one update attempt on table 0. |
| inputs / outputs | Builds one event at owner.sequence()+1 with caller operation/value and invokes apply. |
| invariants | The sequence is read from this owner immediately before the event; the result is intentionally discarded. |
| ownership | Owner is borrowed mutably; Row and event are temporary. |
| failure | Runtime apply exceptions propagate to the enclosing test. |
| cost | One owner update and its storage/statistics work; not a calibrated timing sample. |
| Design | [tests/unit/maintenance_cost_statistics_test.cpp](../../../../../tests/unit/maintenance_cost_statistics_test.cpp), [include/crown/runtime/maintenance_cost.hpp](../../../../../include/crown/runtime/maintenance_cost.hpp), [src/runtime/maintenance_cost.cpp](../../../../../src/runtime/maintenance_cost.cpp), [docs/maintenance_cost.md](../../../../maintenance_cost.md), [tests/support/indexed_runtime_fixture.hpp](../../../../../tests/support/indexed_runtime_fixture.hpp), [tests/support/ranking_fixture.hpp](../../../../../tests/support/ranking_fixture.hpp) |

## B0006

[Lines 32–120](../../../../../tests/unit/maintenance_cost_statistics_test.cpp#L32); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void test_backend(bool indexed) {
  const auto f=fixture();const auto set=candidates(f);const auto index=native_index(set);
  const auto plan=planner::lower_tree(f.catalog,f.query,set.candidate(index)->tree(),indexed?s04_runtime::options():PhysicalOptions{});
  auto owner=runtime::PhysicalRuntime::initialize(plan,f.database);
  ws::Options options;options.mode=ws::Mode::counters;options.period=2;owner.configure_workload_statistics(options);
  // Global attempts1/3 are sampled and change R. Attempts2/4 are unsampled
  // duplicate no-ops. No S bucket has key2 or3. This is deliberately biased:
  // observed sample support work must not be labelled a population fact.
  apply(owner,SetOperation::insert,2);apply(owner,SetOperation::insert,2);
  apply(owner,SetOperation::insert,3);apply(owner,SetOperation::insert,3);
  const auto captured=cost::capture(set,index,owner);check(captured.profile.has_value(),"sampled native profile missing");
  const auto& snapshot=captured.profile->evidence().captured()->workload();
  check(snapshot.detail_availability()==ws::Availability::sampled,"sampling status lost");
  check(cost::features(snapshot).stop==planner::ranking::Stop::evidence_unavailable,"sampled profile admitted as exact timing features");
  auto account=resource::MemoryAccount::create(32U*1024U*1024U);
  const auto calibration=cost::calibrate(account,"literal unit rates; no performance claim",plan.guarantee().storage_backend,rates());
  check(calibration.calibration.has_value(),"backend calibration failed");
  auto inputs=demand(8);cost::Request request;request.input=inputs;
  const std::array<cost::Profile,1> profiles{*captured.profile};
  const auto attempt=cost::estimate(account,set,profiles,*calibration.calibration,request);
  check(attempt.result.has_value(),"sampled estimate failed");const auto& estimate=attempt.result->candidates()[index];
  // Future8 inputs: base dispatch8, full-census changes(2/4)*8=4,
  // sampled adapter/derivation/survivor/parent-change/parent-crossing/edge
  // work each(2/2)*8=8. Six detail groups48 + census12 =60.
  check(estimate.total_ns==Ratio{60,1} && estimate.maintenance_ns==Ratio{60,1} && estimate.issues==0,"sampled/no-op literal60 forecast differs");
  bool census=false,adapter=false;
  for(const auto& term:estimate.terms)if(term.descriptor) {
    const auto& descriptor=snapshot.descriptors()[*term.descriptor];
    if(descriptor.table!=0 || descriptor.operation!=ws::Operation::insert)continue;
    if(term.component==C::base_change) {
      check(term.units==Ratio{4,1} && term.confidence.basis==cost::Basis::observed_census &&
        term.confidence.availability==ws::Availability::exact && term.confidence.complete_inputs==4 && term.confidence.observed_events==2,"no-ops lost from exact census denominator");census=true;
    }
    if(term.component==C::adapter_visit) {
      check(term.units==Ratio{8,1} && term.confidence.basis==cost::Basis::observed_complete_detail &&
        term.confidence.availability==ws::Availability::sampled && term.confidence.complete_inputs==2 && term.confidence.observed_events==2,"sampled detail denominator/status is not explicit");adapter=true;
    }
  }
  check(census && adapter,"required decomposed confidence terms absent");
  const auto recorded=[&](std::uint64_t period,std::uint64_t offset) {
    auto other=runtime::PhysicalRuntime::initialize(plan,f.database);ws::Options collection;
    collection.mode=ws::Mode::counters;collection.period=period;collection.offset=offset;other.configure_workload_statistics(collection);
    apply(other,SetOperation::insert,2);apply(other,SetOperation::insert,2);
    apply(other,SetOperation::insert,3);apply(other,SetOperation::insert,3);
    const auto capture=cost::capture(set,index,other);check(capture.profile.has_value(),"comparison profile missing");return *capture.profile;
  };
  // Complete detail sees two changes across four inputs, so six detail groups
  // contribute4 each:24 + census12 =36. Sampling only the duplicate no-ops
  // sees zero detail across TWO eligible inputs:0 + census12 =12. Neither
  // sampled forecast is a confidence bound on the actual population.
  const auto full=recorded(1,0),noops=recorded(2,1);
  const std::array<cost::Profile,1> full_profile{full},noop_profile{noops};
  const auto exact=cost::estimate(account,set,full_profile,*calibration.calibration,request);
  const auto noop=cost::estimate(account,set,noop_profile,*calibration.calibration,request);
  check(exact.result && exact.result->candidates()[index].total_ns==Ratio{36,1},"complete no-op detail denominator differs from literal36");
  check(noop.result && noop.result->candidates()[index].total_ns==Ratio{12,1},"selected no-ops disappeared from detail denominator");
  bool selected_noops=false;
  for(const auto& term:noop.result->candidates()[index].terms)if(term.component==C::adapter_visit && term.descriptor) {
    const auto& descriptor=noops.evidence().captured()->workload().descriptors()[*term.descriptor];
    if(descriptor.table==0 && descriptor.operation==ws::Operation::insert) {
      check(term.units==Ratio{} && term.confidence.complete_inputs==2 && term.confidence.observed_events==0 &&
        term.confidence.availability==ws::Availability::sampled,"selected no-op sample presented as empty or exact");selected_noops=true;
    }
  }
  check(selected_noops,"selected no-op confidence term absent");
  inputs=demand(8,1);request.input=inputs;
  const auto unknown=cost::estimate(account,set,profiles,*calibration.calibration,request);
  check(unknown.result && !unknown.result->candidates()[index].total_ns &&
    (unknown.result->candidates()[index].issues&cost::issue(cost::Issue::stratum_unobserved)),"unobserved delete stratum got a fabricated cost");
  const auto foreign=cost::calibrate(account,"deliberately wrong backend",indexed?"reference_ordered_v1":"indexed_chained_v1",rates());
  inputs=demand(8);request.input=inputs;
  const auto mismatch=cost::estimate(account,set,profiles,*foreign.calibration,request);
  check(mismatch.result && !mismatch.result->candidates()[index].total_ns &&
    (mismatch.result->candidates()[index].issues&cost::issue(cost::Issue::calibration_backend)),"backend coefficients silently transferred");
  options.period=1;options.detail_budget=0;owner.configure_workload_statistics(options);apply(owner,SetOperation::insert,4);
  const auto truncated=cost::capture(set,index,owner);check(truncated.profile.has_value(),"truncated profile missing");
  const std::array<cost::Profile,1> incomplete{*truncated.profile};
  const auto rejected=cost::estimate(account,set,incomplete,*calibration.calibration,request);
  check(rejected.result && !rejected.result->candidates()[index].total_ns && rejected.result->candidates()[index].issues!=0,"truncated observations priced as complete");
  inputs=demand(0);request.input=inputs;
  const auto idle=cost::estimate(account,set,incomplete,*calibration.calibration,request);
  check(idle.result && idle.result->candidates()[index].total_ns==Ratio{},"zero declared work inferred from observations instead of demand");
  options.detail_budget=65536;owner.configure_workload_statistics(options);
  auto pending=owner.prepare({owner.sequence()+1,{0},SetOperation::insert,Row{std::int64_t{5}}});
  const auto hidden=cost::capture(set,index,owner);
  check(hidden.stop==planner::ranking::Stop::evidence_unavailable && !hidden.profile,"private owner state became a published cost profile");pending.rollback();
  check(owner.sequence()==5 && owner.has_answer(),"cost capture/estimate changed live state");owner.check_invariants();
  std::cout<<"C03 indexed="<<indexed<<" exact-census4/2 sampled-detail2/2 literal60/36/12 unknown/truncated/backend/pending/zero-demand passed\n";
}

```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Check sampled C03 forecasts against both physical storage backends. |
| inputs / outputs | Creates the three-candidate fixture, initializes reference or indexed owner, samples every second update, captures a profile, and estimates eight future inserts. |
| invariants | Only two changed operations are sampled among four attempts; feature extraction rejects sampled detail. Expected sampled estimate is 60 while complete detail is 36; truncated, mismatched, unknown, pending, and zero-demand cases stay explicit. |
| ownership | Profile retains immutable observations; the owner remains the mutable source; calibration and estimate use a separate 32 MiB account. |
| failure | Checks reject backend mismatch, missing strata, detail truncation, and pending capture; assertions throw on any unexpected result. |
| cost | Three owners receive four update attempts each: the sampled primary owner and the full-detail/no-op comparison owners. The primary owner then receives one further insert and one prepared-but-rolled-back insert attempt before final assertions. Capture and estimate work is repeated for both backends; no wall-clock timing is measured. |
| Design | [tests/unit/maintenance_cost_statistics_test.cpp](../../../../../tests/unit/maintenance_cost_statistics_test.cpp), [include/crown/runtime/maintenance_cost.hpp](../../../../../include/crown/runtime/maintenance_cost.hpp), [src/runtime/maintenance_cost.cpp](../../../../../src/runtime/maintenance_cost.cpp), [docs/maintenance_cost.md](../../../../maintenance_cost.md), [tests/support/indexed_runtime_fixture.hpp](../../../../../tests/support/indexed_runtime_fixture.hpp), [tests/support/ranking_fixture.hpp](../../../../../tests/support/ranking_fixture.hpp) |

## B0007

[Lines 121–121](../../../../../tests/unit/maintenance_cost_statistics_test.cpp#L121); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L121-L121:sha256:c4b9c3fab52d74ef772a80090ef4a35760b5a3b41ee88be876eed0db22a2fcbd
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Prepare maintenance_cost_statistics_test.cpp: select the recorded test ABI/preprocessor branch. |
| inputs / outputs | Compiler-visible dependencies, names and the recorded declarations in; declarations available to the following fixture/CLI/example definitions out. |
| invariants | Declarations are scoped to this source/header and its selected ABI. Included code has its own effects; names and editable fixture values do not confer proof, admission or publication authority. |
| ownership | Aliases/includes do not create a query owner. Pointers/references/views are non-owning. Containers own their elements, which can themselves be borrowed pointers or numeric IDs. Only documented owning shared-control handles retain controls; IDs/slot-handle values do not independently keep an arena/runtime alive. |
| failure | Missing headers, ill-formed names/types, failed static assertions or active #error directives stop compilation. No runtime rejection/rollback mechanism is implemented by aliases or function prototypes. |
| cost | Preprocessing and type/constraint instantiation cost compilation. Alias/prototype syntax does not invoke the declared operation; any included definitions keep their own initialization effects. |
| Design | [tests/unit/maintenance_cost_statistics_test.cpp](../../../../../tests/unit/maintenance_cost_statistics_test.cpp), [docs/maintenance_cost.md](../../../../maintenance_cost.md), [docs/code_review.md](../../../../code_review.md) |

## B0008

[Lines 122–136](../../../../../tests/unit/maintenance_cost_statistics_test.cpp#L122); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void saturation(bool indexed) {
  const auto f=fixture();const auto set=candidates(f);const auto index=native_index(set);
  const auto plan=planner::lower_tree(f.catalog,f.query,set.candidate(index)->tree(),indexed?s04_runtime::options():PhysicalOptions{});
  auto owner=runtime::DeltaRuntime::initialize(plan,f.database);ws::Options options;options.mode=ws::Mode::counters;owner.configure_workload_statistics(options);
  auto epoch=owner.apply({1,{0},SetOperation::insert,Row{std::int64_t{2}}});epoch.discard();
  runtime::RuntimeTestProbe::seed_c01_report_saturation(owner);
  const auto captured=cost::capture(set,index,owner);check(captured.profile.has_value(),"saturated actual-owner profile absent");
  const auto& snapshot=captured.profile->evidence().captured()->workload();check(snapshot.detail_availability()==ws::Availability::lower_bound,"saturated counters presented as exact");
  check(cost::features(snapshot).stop==planner::ranking::Stop::evidence_unavailable,"saturated counters became calibration measurements");
  auto account=resource::MemoryAccount::create(32U*1024U*1024U);const auto calibration=cost::calibrate(account,"saturation boundary, synthetic rates",plan.guarantee().storage_backend,rates());
  auto inputs=demand(8);cost::Request request;request.input=inputs;const std::array<cost::Profile,1> profiles{*captured.profile};
  const auto rejected=cost::estimate(account,set,profiles,*calibration.calibration,request);
  check(rejected.result && !rejected.result->candidates()[index].total_ns && rejected.result->candidates()[index].issues!=0,"saturated capped counters became a complete forecast");
  std::cout<<"C03 indexed="<<indexed<<" actual test-ABI saturation unavailable for fit/complete forecast passed\n";
}

```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Inject counter saturation and require incomplete timing features on each backend. |
| inputs / outputs | Under CROWN_RUNTIME_TESTING, seeds a test owner counter through the runtime probe, captures its workload snapshot, then checks lower-bound and feature/estimate stops. |
| invariants | The injected maximum is a boundary sample, not execution of a maximum number of updates; saturated evidence is not treated as an exact zero or timing feature. |
| ownership | Local Snapshot/Profile handles retain captured payloads charged to the original query account. The runtime probe mutates the local test owner. Calibration and estimate result payloads use the separate 32 MiB receiving account. |
| failure | Unexpected saturation classification or estimate availability fails the assertion. |
| cost | One probe, capture, and feature/estimate path per backend; no event sweep is performed. |
| Design | [tests/unit/maintenance_cost_statistics_test.cpp](../../../../../tests/unit/maintenance_cost_statistics_test.cpp), [include/crown/runtime/maintenance_cost.hpp](../../../../../include/crown/runtime/maintenance_cost.hpp), [src/runtime/maintenance_cost.cpp](../../../../../src/runtime/maintenance_cost.cpp), [docs/maintenance_cost.md](../../../../maintenance_cost.md), [tests/support/indexed_runtime_fixture.hpp](../../../../../tests/support/indexed_runtime_fixture.hpp), [tests/support/ranking_fixture.hpp](../../../../../tests/support/ranking_fixture.hpp) |

## B0009

[Lines 137–138](../../../../../tests/unit/maintenance_cost_statistics_test.cpp#L137); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L137-L138:sha256:65c85c9be6517efcd9391b644fa92a11bb261ef8f295d09fd49bd012633a4298
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Prepare maintenance_cost_statistics_test.cpp: declare the recorded helper API/type boundary. |
| inputs / outputs | Compiler-visible dependencies, names and the recorded declarations in; declarations available to the following fixture/CLI/example definitions out. |
| invariants | Declarations are scoped to this source/header and its selected ABI. Included code has its own effects; names and editable fixture values do not confer proof, admission or publication authority. |
| ownership | Aliases/includes do not create a query owner. Pointers/references/views are non-owning. Containers own their elements, which can themselves be borrowed pointers or numeric IDs. Only documented owning shared-control handles retain controls; IDs/slot-handle values do not independently keep an arena/runtime alive. |
| failure | Missing headers, ill-formed names/types, failed static assertions or active #error directives stop compilation. No runtime rejection/rollback mechanism is implemented by aliases or function prototypes. |
| cost | Preprocessing and type/constraint instantiation cost compilation. Alias/prototype syntax does not invoke the declared operation; any included definitions keep their own initialization effects. |
| Design | [tests/unit/maintenance_cost_statistics_test.cpp](../../../../../tests/unit/maintenance_cost_statistics_test.cpp), [docs/maintenance_cost.md](../../../../maintenance_cost.md), [docs/code_review.md](../../../../code_review.md) |

## B0010

[Lines 139–143](../../../../../tests/unit/maintenance_cost_statistics_test.cpp#L139); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
int main(){try{for(bool indexed:{false,true})test_backend(indexed);
#ifdef CROWN_RUNTIME_TESTING
  for(bool indexed:{false,true})saturation(indexed);
#endif
}catch(const std::exception& error){std::cerr<<error.what()<<'\n';return 1;}}

```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Run the reference and indexed sampled-statistics scenarios. |
| inputs / outputs | Calls test_backend(false) and test_backend(true); testing builds also call saturation(false/true). |
| invariants | Each backend path stays independently labeled and uses its own fixture owner. |
| ownership | All state is local to each scenario and released on return. |
| failure | Exceptions from assertion helpers leave main as a failed test. |
| cost | Two ordinary scenario runs, plus two saturation runs only in the testing configuration. |
| Design | [tests/unit/maintenance_cost_statistics_test.cpp](../../../../../tests/unit/maintenance_cost_statistics_test.cpp), [include/crown/runtime/maintenance_cost.hpp](../../../../../include/crown/runtime/maintenance_cost.hpp), [src/runtime/maintenance_cost.cpp](../../../../../src/runtime/maintenance_cost.cpp), [docs/maintenance_cost.md](../../../../maintenance_cost.md), [tests/support/indexed_runtime_fixture.hpp](../../../../../tests/support/indexed_runtime_fixture.hpp), [tests/support/ranking_fixture.hpp](../../../../../tests/support/ranking_fixture.hpp) |
