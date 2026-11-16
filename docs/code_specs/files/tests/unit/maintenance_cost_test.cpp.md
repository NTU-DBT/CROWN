# `tests/unit/maintenance_cost_test.cpp` — block usage map

[Source](../../../../../tests/unit/maintenance_cost_test.cpp) · [Source index](../../../README.md) · [Subsystem contracts](../../../subsystem_contracts.md) · [Reviewed primitives](../../../primitives.md)

Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection.

Snapshot SHA-256: `248ef73c19124f736d3c5a4e3ed4273e85630463e380a92b1a1c46bc9a2dd33e`. 146 lines partitioned into 7 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [tests](../../../subsystem_contracts.md#tests). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/code_review.md](../../../../code_review.md), [docs/reference_fuzz.md](../../../../reference_fuzz.md), [docs/task_ledger.md](../../../../task_ledger.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–11](../../../../../tests/unit/maintenance_cost_test.cpp#L1) | Imports dependencies; declares namespace scope; declares aliases; declares values/defaults or compile-time conditions. |  · [reviewed contract](#b0001) |
| [B0002 · 12–19](../../../../../tests/unit/maintenance_cost_test.cpp#L12) | Callable definition: std::vector&lt;model::CalibrationSample&gt; samples() | calls push_back; returns out; growth push_back; 1 loop sites · [reviewed contract](#b0002) |
| [B0003 · 20–22](../../../../../tests/unit/maintenance_cost_test.cpp#L20) | Callable definition: std::vector&lt;model::InputDemand&gt; demand() | calls ; returns {{{0},O::insert,4},{{0},O::erase,3},{{1},O::insert,0},{{1},O::erase,0},{{2},O::insert,0},{{2},O::er…; growth insert · [reviewed contract](#b0003) |
| [B0004 · 23–26](../../../../../tests/unit/maintenance_cost_test.cpp#L23) | Callable definition: void apply(runtime::DeltaRuntime& owner,SetOperation operation,std::int64_t key) | calls sequence, next; 1 loop sites · [reviewed contract](#b0004) |
| [B0005 · 27–144](../../../../../tests/unit/maintenance_cost_test.cpp#L27) | Callable definition: void run() | calls static_assert, fixture, c02_test::candidates, candidate_count; guard static_assert(!std::is_default_constructible_v&lt;model::Profile&gt; && !std::is_default_constructible_v&lt;…; growth insert, push_back; 6 loop sites; source comment (unverified): // R(7) toggles six times and touches one S row each time; R(8) touches three. · [reviewed contract](#b0005) |
| [B0006 · 145–145](../../../../../tests/unit/maintenance_cost_test.cpp#L145) | Closes surrounding scope/type. |  · [reviewed contract](#b0006) |
| [B0007 · 146–146](../../../../../tests/unit/maintenance_cost_test.cpp#L146) | Callable definition: int main() | calls run, what; returns 1 · [reviewed contract](#b0007) |

## B0001

[Lines 1–11](../../../../../tests/unit/maintenance_cost_test.cpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L1-L11:sha256:25d7ca6cb2e7bde5fe70903646d0e351e749f1d3b05e9495a55450b6a942e003
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Prepare maintenance_cost_test.cpp: include "ranking_fixture.hpp", "crown/runtime/maintenance_cost.hpp", &lt;array&gt;, &lt;iostream&gt;; bind local aliases/name imports. |
| inputs / outputs | Compiler-visible dependencies, names and the recorded declarations in; declarations available to the following fixture/CLI/example definitions out. |
| invariants | Declarations are scoped to this source/header and its selected ABI. Included code has its own effects; names and editable fixture values do not confer proof, admission or publication authority. |
| ownership | Aliases/includes do not create a query owner. Pointers/references/views are non-owning. Containers own their elements, which can themselves be borrowed pointers or numeric IDs. Only documented owning shared-control handles retain controls; IDs/slot-handle values do not independently keep an arena/runtime alive. |
| failure | Missing headers, ill-formed names/types, failed static assertions or active #error directives stop compilation. No runtime rejection/rollback mechanism is implemented by aliases or function prototypes. |
| cost | Preprocessing and type/constraint instantiation cost compilation. Alias/prototype syntax does not invoke the declared operation; any included definitions keep their own initialization effects. |
| Design | [tests/unit/maintenance_cost_test.cpp](../../../../../tests/unit/maintenance_cost_test.cpp), [docs/maintenance_cost.md](../../../../maintenance_cost.md), [docs/code_review.md](../../../../code_review.md) |

## B0002

[Lines 12–19](../../../../../tests/unit/maintenance_cost_test.cpp#L12); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::vector<model::CalibrationSample> samples() {
  std::vector<model::CalibrationSample> out;
  for(std::size_t i=0;i<model::component_count;++i)out.push_back({static_cast<C>(i),1,1});
  out[static_cast<std::size_t>(C::edge_lookup)].elapsed_ns=2;
  out[static_cast<std::size_t>(C::native_bucket_touch)].elapsed_ns=3;
  out[static_cast<std::size_t>(C::annotation_change)].elapsed_ns=11;
  return out;
}

```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Build distinct synthetic per-component unit rates. |
| inputs / outputs | Returns one CalibrationSample per component; edge lookup is 2 ns/unit, native bucket touch 3, annotation change 11, others 1. |
| invariants | Rates are explicitly synthetic arithmetic inputs; they are not inferred from runtime measurements. |
| ownership | Returned vector owns records; calibrate copies its accepted model data. |
| failure | Only sample-vector construction can fail in this helper; it does not call calibration. Calibration is invoked later by run(). |
| cost | Appends component_count samples. |
| Design | [tests/unit/maintenance_cost_test.cpp](../../../../../tests/unit/maintenance_cost_test.cpp), [include/crown/runtime/maintenance_cost.hpp](../../../../../include/crown/runtime/maintenance_cost.hpp), [src/runtime/maintenance_cost.cpp](../../../../../src/runtime/maintenance_cost.cpp), [docs/maintenance_cost.md](../../../../maintenance_cost.md) |

## B0003

[Lines 20–22](../../../../../tests/unit/maintenance_cost_test.cpp#L20); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::vector<model::InputDemand> demand() {
  return {{{0},O::insert,4},{{0},O::erase,3},{{1},O::insert,0},{{1},O::erase,0},{{2},O::insert,0},{{2},O::erase,0}};
}

```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Declare seven input operations on table 0 and zero elsewhere. |
| inputs / outputs | Returns six rows covering insert/erase for three tables, with counts 4 and 3 on table 0. |
| invariants | Every table/op stratum appears once, including zeros. |
| ownership | Caller owns the vector; Request borrows it only during estimate. |
| failure | No domain error; allocation failure propagates. |
| cost | Constructs six demand records. |
| Design | [tests/unit/maintenance_cost_test.cpp](../../../../../tests/unit/maintenance_cost_test.cpp), [include/crown/runtime/maintenance_cost.hpp](../../../../../include/crown/runtime/maintenance_cost.hpp), [src/runtime/maintenance_cost.cpp](../../../../../src/runtime/maintenance_cost.cpp), [docs/maintenance_cost.md](../../../../maintenance_cost.md) |

## B0004

[Lines 23–26](../../../../../tests/unit/maintenance_cost_test.cpp#L23); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void apply(runtime::DeltaRuntime& owner,SetOperation operation,std::int64_t key) {
  auto epoch=owner.apply({owner.sequence()+1,{0},operation,Row{key}});
  while(epoch.next()){}
}

```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Apply and fully consume one DeltaRuntime epoch. |
| inputs / outputs | Uses owner.sequence()+1 and a table-0 operation/key; drains epoch.next() until exhausted. |
| invariants | The helper publishes the whole epoch before returning; it does not count rows itself. |
| ownership | Owner is mutably borrowed; returned cursor is local and released after drain. |
| failure | Runtime update errors propagate; no partial forecast is asserted. |
| cost | One delta operation and cursor drain; row count depends on the update. |
| Design | [tests/unit/maintenance_cost_test.cpp](../../../../../tests/unit/maintenance_cost_test.cpp), [include/crown/runtime/maintenance_cost.hpp](../../../../../include/crown/runtime/maintenance_cost.hpp), [src/runtime/maintenance_cost.cpp](../../../../../src/runtime/maintenance_cost.cpp), [docs/maintenance_cost.md](../../../../maintenance_cost.md) |

## B0005

[Lines 27–144](../../../../../tests/unit/maintenance_cost_test.cpp#L27); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void run() {
  static_assert(!std::is_default_constructible_v<model::Profile> && !std::is_default_constructible_v<model::Calibration>);
  const auto f=fixture();const auto candidates=c02_test::candidates(f);
  Database state;state.tables={Relation{},Relation{{std::int64_t{7},std::int64_t{10}},
    {std::int64_t{8},std::int64_t{20}},{std::int64_t{8},std::int64_t{30}},{std::int64_t{8},std::int64_t{40}}},
    Relation{{std::int64_t{10}},{std::int64_t{20}},{std::int64_t{30}},{std::int64_t{40}}}};
  std::vector<model::Profile> profiles;std::vector<runtime::DeltaRuntime> owners;std::size_t native=SIZE_MAX;
  for(std::size_t i=0;i<candidates.candidate_count();++i) {
    const auto candidate=*candidates.candidate(i);if(shape(candidate.tree())==0)native=i;
    const auto plan=planner::lower_tree(f.catalog,f.query,candidate.tree());runtime::DeltaOptions options;
    options.mode=runtime::DeltaMode::delta;options.physical.support.observation.mode=runtime::ObservationMode::off;
    auto owner=runtime::DeltaRuntime::initialize(plan,state,options);
    runtime::workload::Options collection;collection.mode=runtime::workload::Mode::counters;
    owner.configure_workload_statistics(collection);
    for(unsigned n=0;n<3;++n){apply(owner,SetOperation::insert,7);apply(owner,SetOperation::erase,7);}
    apply(owner,SetOperation::insert,8);
    const auto captured=model::capture(candidates,i,owner);
    check(captured.stop==planner::ranking::Stop::complete && captured.profile.has_value(),"actual candidate capture failed");
    check(captured.profile->memory_at_capture().current.requested_bytes>0,"missing actual account memory");
    profiles.push_back(*captured.profile);owners.push_back(std::move(owner));
  }
  check(native!=SIZE_MAX,"missing native candidate");
  auto account=resource::MemoryAccount::create(64U*1024U*1024U);
  auto calibrated=model::calibrate(account,"synthetic arithmetic fixture; disjoint operation units", "reference_ordered_v1",samples());
  check(calibrated.calibration.has_value(),"calibration failed");
  auto forecast=demand();model::Request request;request.input=forecast;
  auto estimate=model::estimate(account,candidates,profiles,*calibrated.calibration,request);
  check(estimate.result && estimate.result->candidates().size()==3,"not every candidate estimated");
  for(const auto& value:estimate.result->candidates())check(value.total_ns.has_value() && value.issues==0,"complete observed candidate unavailable");
  const auto& chosen=estimate.result->candidates()[native];
  const auto features=model::features(chosen.observations->evidence().captured()->workload());
  check(features.census && features.census->units[static_cast<std::size_t>(C::native_bucket_touch)]==9 &&
    features.census->units[static_cast<std::size_t>(C::edge_lookup)]==7 && features.census->units[0]==7,"native feature census differs from hand trace");
  // R(7) toggles six times and touches one S row each time; R(8) touches three.
  // Seven incoming events touch nine records. Uniform mean degree2 gives14,
  // which is wrong for this event multiset.
  R touches,lookups;
  for(const auto& term:chosen.terms) {
    if(term.component==C::native_bucket_touch && term.units){check(term.units->denominator==1,"unexpected fractional horizon touch count");touches.numerator+=term.units->numerator;}
    if(term.component==C::edge_lookup && term.units){check(term.units->denominator==1,"unexpected fractional horizon event count");lookups.numerator+=term.units->numerator;}
  }
  check(touches==R{9,1} && lookups==R{7,1},"conditional event weighting replaced by uniform static degree");
  // Four input/adapter/derivation groups each7; survivors16; parent counts16;
  // parent crossings14; root visible updates9/crossings7; lookup14; touch27.
  if(chosen.maintenance_ns!=R{131,1}) {
    std::cerr<<"native maintenance "<<(chosen.maintenance_ns?chosen.maintenance_ns->numerator:0)<<'/'<<(chosen.maintenance_ns?chosen.maintenance_ns->denominator:0)<<'\n';
    for(const auto& t:chosen.terms)if(t.units && t.units->numerator)std::cerr<<model::component_name(t.component)<<' '<<t.units->numerator<<'/'<<t.units->denominator<<'\n';
  }
  check(chosen.maintenance_ns==R{131,1},"literal native maintenance decomposition differs");
  request.output={2,1,7,7,64,1,128,5};
  const auto output=model::estimate(account,candidates,profiles,*calibrated.calibration,request);
  check(output.result.has_value(),"output demand estimate failed");const auto& priced=output.result->candidates()[native];
  check(priced.maintenance_ns==chosen.maintenance_ns,"annotation/output demand charged as support work");
  check(priced.snapshot_ns==R{6,1} && priced.delta_ns==R{21,1} && priced.encoding_ns==R{64,1} &&
    priced.checkpoint_ns==R{129,1} && priced.annotation_ns==R{55,1} && priced.total_ns==R{406,1},"literal output/checkpoint/annotation decomposition differs");
  request.output.snapshot_rows_total=3;
  const auto varied=model::estimate(account,candidates,profiles,*calibrated.calibration,request);
  check(varied.result && varied.result->candidates()[native].snapshot_ns==R{7,1} && varied.result->candidates()[native].total_ns==R{407,1},"aggregate varying snapshot demand ignored");
  request.output.snapshot_rows_total.reset();
  auto partial=profiles;partial.erase(partial.begin()+static_cast<std::ptrdiff_t>(native));
  const auto missing=model::estimate(account,candidates,partial,*calibrated.calibration,request);
  check(missing.result && missing.result->candidates().size()==3 && !missing.result->candidates()[native].total_ns &&
    missing.result->candidates()[native].issues==model::issue(model::Issue::profile_missing),"missing candidate got fabricated costs");
  request.memory_budget_bytes=1;const auto memory=model::estimate(account,candidates,profiles,*calibrated.calibration,request);
  check(memory.result && !memory.result->candidates()[native].total_ns && (memory.result->candidates()[native].issues&model::issue(model::Issue::memory_budget)),"memory bytes used as latency or budget ignored");
  request.memory_budget_bytes=64U*1024U*1024U;request.limits.work=0;
  const auto stopped=model::estimate(account,candidates,profiles,*calibrated.calibration,request);
  check(stopped.stop==planner::ranking::Stop::work_limit && !stopped.result,"partial result published after work limit");
  const auto before=profiles[native].evidence().inputs().identity().epoch;apply(owners[native],SetOperation::erase,8);
  const auto stale=model::revalidate(profiles[native],owners[native]);
  check(stale.depth!=0 && profiles[native].evidence().inputs().identity().epoch==before,"stale profile presented as current or mutated");
  // As-of evidence remains immutable and reproducible after owner advancement.
  request.limits={};request.output={};const auto again=model::estimate(account,candidates,profiles,*calibrated.calibration,request);
  check(again.result && again.result->candidates()[native].maintenance_ns==chosen.maintenance_ns,"as-of estimate changed after update");
  auto duplicates=profiles;duplicates.push_back(profiles.front());
  const auto duplicate=model::estimate(account,candidates,duplicates,*calibrated.calibration,request);
  check(duplicate.stop==planner::ranking::Stop::binding_mismatch && !duplicate.result,"duplicate profile accepted");
  const auto wrong=model::capture(candidates,(native+1)%3,owners[native]);
  check(wrong.stop==planner::ranking::Stop::binding_mismatch && !wrong.profile,"profile borrowed another candidate's bucket statistics");
  runtime::workload::Options off;owners[native].configure_workload_statistics(off);
  const auto disabled=model::capture(candidates,native,owners[native]);check(disabled.profile.has_value(),"disabled profile not representable");
  check(model::features(disabled.profile->evidence().captured()->workload()).stop==planner::ranking::Stop::evidence_unavailable,"disabled counters became fit observations");
  auto without=profiles;without[native]=*disabled.profile;
  const auto unavailable=model::estimate(account,candidates,without,*calibrated.calibration,request);
  check(unavailable.result && !unavailable.result->candidates()[native].total_ns &&
    (unavailable.result->candidates()[native].issues&model::issue(model::Issue::detail_unavailable)),"disabled collection fabricated zero maintenance");
  std::array<model::CalibrationSample,2> rational_samples{{{C::base_input,2,3},{C::base_input,4,8}}};
  const auto fitted=model::calibrate(account,"literal measured-input arithmetic","reference_ordered_v1",rational_samples);
  check(fitted.calibration && fitted.calibration->coefficients()[0]->nanoseconds_per_unit==R{11,6} &&
    fitted.calibration->coefficients()[0]->samples==2,"calibration is not summed time per summed unit");
  std::array<model::CalibrationSample,1> invalid{{{C::base_input,0,1}}};
  check(model::calibrate(account,"invalid","reference_ordered_v1",invalid).stop==planner::ranking::Stop::invalid_limits,"zero-unit calibration accepted");
  rational_samples={{{C::base_input,UINT64_MAX,1},{C::base_input,1,1}}};
  check(model::calibrate(account,"overflow","reference_ordered_v1",rational_samples).stop==planner::ranking::Stop::bit_limit,"calibration overflow wrapped");
  auto tiny=resource::MemoryAccount::create(resource::MemoryAccount::control_bytes());
  const auto denied=model::calibrate(tiny,"tiny","reference_ordered_v1",samples());
  check(denied.stop==planner::ranking::Stop::allocation_failure && !denied.calibration,"calibration escaped the receiving account");
  forecast[0].inputs=999;check(estimate.result->input_demand()[0].inputs==4,"published demand borrows caller memory");
  runtime::workload::Options sampled;sampled.mode=runtime::workload::Mode::counters;sampled.period=2;
  owners[native].configure_workload_statistics(sampled);apply(owners[native],SetOperation::insert,9);
  check(model::features(owners[native].workload_statistics()).stop==planner::ranking::Stop::evidence_unavailable,"sampled counts priced as full timing features");
  sampled.period=1;sampled.detail_budget=0;owners[native].configure_workload_statistics(sampled);apply(owners[native],SetOperation::insert,10);
  check(model::features(owners[native].workload_statistics()).stop==planner::ranking::Stop::evidence_unavailable,"truncated detail became timing features");
  const auto physical_plan=planner::lower_tree(f.catalog,f.query,candidates.candidate(native)->tree());
  auto physical=runtime::PhysicalRuntime::initialize(physical_plan,state);sampled.detail_budget=65536;physical.configure_workload_statistics(sampled);
  const auto physical_apply=[&](SetOperation operation,std::int64_t key){static_cast<void>(physical.apply({physical.sequence()+1,{0},operation,Row{key}}));};
  for(unsigned i=0;i<3;++i){physical_apply(SetOperation::insert,7);physical_apply(SetOperation::erase,7);}physical_apply(SetOperation::insert,8);
  const auto physical_profile=model::capture(candidates,native,physical);check(physical_profile.profile.has_value(),"physical owner profile capture failed");
  const std::array<model::Profile,1> physical_profiles{*physical_profile.profile};forecast=demand();request.input=forecast;
  const auto physical_price=model::estimate(account,candidates,physical_profiles,*calibrated.calibration,request);
  check(physical_price.result && physical_price.result->candidates()[native].maintenance_ns==R{131,1},"physical owner changed observed support costing");
  model::FitOptions bound;bound.modes=chosen.observed_modes;std::array<model::FitObservation,1> measured{};measured[0].units[0]=1;measured[0].elapsed_ns=1;
  const auto bound_fit=model::fit(account,"mode-bound synthetic fixture","reference_ordered_v1",measured,bound);check(bound_fit.calibration.has_value(),"mode-bound calibration failed");
  const auto different_mode=model::estimate(account,candidates,physical_profiles,*bound_fit.calibration,request);
  check(different_mode.result && !different_mode.result->candidates()[native].total_ns &&
    (different_mode.result->candidates()[native].issues&model::issue(model::Issue::calibration_mode)),"fitted delta mode coefficients silently used for physical maintenance owner");
  std::cout<<"C03 actual candidate profiles, skewed event-multiset9/7, literal131/406 costs, separate annotation/output/memory, missing/stale/caps passed\n";
}

```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Capture every candidate and compare synthetic decomposition and rejection cases. |
| inputs / outputs | For each of three candidate owners, applies three insert/erase cycles on key 7 starting from empty R, then inserts key 8; captures each profile, calibrates synthetic rates, and estimates the declared demand. |
| invariants | Capture is candidate-bound and uses actual account evidence. The three key-7 cycles each change membership. After the owner advances, revalidation reports stale currentness while saved as-of evidence still supports the same estimate. |
| ownership | Each Profile retains evidence, not a live mutable owner; estimate copies profiles and demand into the receiving account. |
| failure | Missing/incompatible profiles, invalid calibration, work or memory limits, and arithmetic overflow produce the asserted stops/issues. After owner advancement, revalidate reports stale depth, but the immutable as-of profile still estimates the same maintenance cost. |
| cost | Three candidates each receive update/capture work; three toggle cycles plus one insert per owner. Estimate builds terms per candidate and requested component; no wall-clock measurement occurs. |
| Design | [tests/unit/maintenance_cost_test.cpp](../../../../../tests/unit/maintenance_cost_test.cpp), [include/crown/runtime/maintenance_cost.hpp](../../../../../include/crown/runtime/maintenance_cost.hpp), [src/runtime/maintenance_cost.cpp](../../../../../src/runtime/maintenance_cost.cpp), [docs/maintenance_cost.md](../../../../maintenance_cost.md) |

## B0006

[Lines 145–145](../../../../../tests/unit/maintenance_cost_test.cpp#L145); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L145-L145:sha256:412ca345ccf75bf9c0806bce695be8de808b79984251a7a54d202cf6101dd451
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Close the recorded declaration scopes in maintenance_cost_test.cpp: namespace (anonymous). |
| inputs / outputs | Preceding namespace, type or initializer declarations in; completed lexical boundary out. |
| invariants | Brace-opening context is recorded in root-scope-context-v1.json. These are declaration/initializer boundaries, not an independent update, validation or recovery operation. |
| ownership | Enclosing objects and borrowed fields keep their declared ownership. This punctuation creates no new owner. |
| failure | Malformed scope syntax is a compile error. Any initializer/constructor failure belongs to the enclosing object declaration. |
| cost | No separate loop, guard or engine call is introduced by the delimiter; enclosing initialization and object lifetime still have their actual costs. |
| Design | [tests/unit/maintenance_cost_test.cpp](../../../../../tests/unit/maintenance_cost_test.cpp), [docs/maintenance_cost.md](../../../../maintenance_cost.md), [docs/code_review.md](../../../../code_review.md) |

## B0007

[Lines 146–146](../../../../../tests/unit/maintenance_cost_test.cpp#L146); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
int main(){try{run();}catch(const std::exception& e){std::cerr<<e.what()<<'\n';return 1;}}

```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Execute the single Delta C03 estimate fixture. |
| inputs / outputs | Invokes run and returns process status. |
| invariants | The scenario is a synthetic estimate validation, not an automatic selection policy. |
| ownership | All owners and model values are confined to run. |
| failure | A thrown assertion or C03 failure exits unsuccessfully. |
| cost | One run over three candidates. |
| Design | [tests/unit/maintenance_cost_test.cpp](../../../../../tests/unit/maintenance_cost_test.cpp), [include/crown/runtime/maintenance_cost.hpp](../../../../../include/crown/runtime/maintenance_cost.hpp), [src/runtime/maintenance_cost.cpp](../../../../../src/runtime/maintenance_cost.cpp), [docs/maintenance_cost.md](../../../../maintenance_cost.md) |
