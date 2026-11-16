# `tests/unit/selection_resources_independent_test.cpp` — block usage map

[Source](../../../../../tests/unit/selection_resources_independent_test.cpp) · [Source index](../../../README.md) · [Subsystem contracts](../../../subsystem_contracts.md) · [Reviewed primitives](../../../primitives.md)

Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection.

Snapshot SHA-256: `719f23c6909f9dbe8a4c97f4e9c71981391bd9b1c4dcb3ade1714d1023783478`. 166 lines partitioned into 8 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [tests](../../../subsystem_contracts.md#tests). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/code_review.md](../../../../code_review.md), [docs/reference_fuzz.md](../../../../reference_fuzz.md), [docs/task_ledger.md](../../../../task_ledger.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–18](../../../../../tests/unit/selection_resources_independent_test.cpp#L1) | Imports dependencies; declares namespace scope; declares aliases; declares values/defaults or compile-time conditions. |  · [reviewed contract](#b0001) |
| [B0002 · 19–51](../../../../../tests/unit/selection_resources_independent_test.cpp#L19) | Callable definition: void fixed_preparation_algebra() | calls size, budget, begin_delegate, check; guard for (auto field:limits_by_field) check(first.*field==97,"first delegated limit did not add back exa…; 8 loop sites; source comment (unverified): // Resource numbers are deliberately synthetic. They create no semantic · [reviewed contract](#b0002) |
| [B0003 · 52–52](../../../../../tests/unit/selection_resources_independent_test.cpp#L52) | Explanatory comments or spacing. |  |
| [B0004 · 53–102](../../../../../tests/unit/selection_resources_independent_test.cpp#L53) | Callable definition: void complete_dual_usage_and_boundaries(const BooleanFixture& f) | calls r::PhysicalRuntime::initialize, lower, at, hot; guard check(result.assessments().size()==2 && result.assessments()\[0\].purpose==s::AssessmentPurpose::slot…; 3 loop sites · [reviewed contract](#b0004) |
| [B0005 · 103–103](../../../../../tests/unit/selection_resources_independent_test.cpp#L103) | Explanatory comments or spacing. |  |
| [B0006 · 104–154](../../../../../tests/unit/selection_resources_independent_test.cpp#L104) | Callable definition: void current_capture_and_time(const BooleanFixture& f) | calls r::PhysicalRuntime::initialize, lower, at, hot; guard check(captured.memory_reasons()==0 && captured.capture_accounting().state_rows==0 &&; 1 loop sites · [reviewed contract](#b0006) |
| [B0007 · 155–156](../../../../../tests/unit/selection_resources_independent_test.cpp#L155) | Closes surrounding scope/type. | source comment (unverified): // namespace · [reviewed contract](#b0007) |
| [B0008 · 157–166](../../../../../tests/unit/selection_resources_independent_test.cpp#L157) | Callable definition: int main(int argc,char** argv) | calls check, boolean_fixture, fixed_preparation_algebra, complete_dual_usage_and_boundaries; guard check(argc==2,"usage: selection_resources_independent_test REPOSITORY_ROOT");; returns 1 · [reviewed contract](#b0008) |

## B0001

[Lines 1–18](../../../../../tests/unit/selection_resources_independent_test.cpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L1-L18:sha256:eaf788a6c8292a7dbd99ee95d28ba2cae5e153ed465c957ea409f3484cc09791
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Prepare selection_resources_independent_test.cpp: include "selection_independent_fixture.hpp", "selection_detail.hpp", &lt;iostream&gt;, &lt;limits&gt;; bind local aliases/name imports; declare constant fixture data. |
| inputs / outputs | Compiler-visible dependencies, names and the recorded declarations in; declarations available to the following fixture/CLI/example definitions out. The source span lists the exact member/global names, types and initial values; initializers run when the enclosing object/program/thread is initialized. |
| invariants | Declarations are scoped to this source/header and its selected ABI. Included code has its own effects; names and editable fixture values do not confer proof, admission or publication authority. |
| ownership | Aliases/includes do not create a query owner. Pointers/references/views are non-owning. Containers own their elements, which can themselves be borrowed pointers or numeric IDs. Only documented owning shared-control handles retain controls; IDs/slot-handle values do not independently keep an arena/runtime alive. |
| failure | Missing headers, ill-formed names/types, failed static assertions or active #error directives stop compilation. No runtime rejection/rollback mechanism is implemented by aliases or function prototypes. |
| cost | Preprocessing and type/constraint instantiation cost compilation. Alias/prototype syntax does not invoke the declared operation; any included definitions keep their own initialization effects. These constexpr data are fixed fixture constants; quota literals are grants, not reserved bytes or measured peaks. |
| Design | [tests/unit/selection_resources_independent_test.cpp](../../../../../tests/unit/selection_resources_independent_test.cpp), [docs/selection.md](../../../../selection.md), [docs/code_review.md](../../../../code_review.md) |

## B0002

[Lines 19–51](../../../../../tests/unit/selection_resources_independent_test.cpp#L19); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void fixed_preparation_algebra() {
  // Resource numbers are deliberately synthetic. They create no semantic
  // Evidence, Selection, proof or private cache entry. The independent oracle
  // is plain integer arithmetic: P=7, own=3, V1=17, V2=27 => U=40, not47/54.
  rank::Limits limits;
  rank::Usage preparation;
  for (std::size_t i=0;i<counters_by_field.size();++i) {
    limits.*limits_by_field[i]=100;
    preparation.*counters_by_field[i]=7;
  }
  budget_detail::Budget budget(limits,preparation);
  for (auto field:counters_by_field) budget.usage.*field+=3;
  const auto first=budget.begin_delegate(preparation);
  for (auto field:limits_by_field) check(first.*field==97,"first delegated limit did not add back exactly one P");
  auto returned=preparation;
  for (auto field:counters_by_field) returned.*field=17;
  budget.end_delegate(returned,preparation);
  for (auto field:counters_by_field) check(budget.usage.*field==20,"first complete assessment counted preparation twice");
  const auto second=budget.begin_delegate(preparation);
  for (auto field:limits_by_field) check(second.*field==87,"second assessment received a fresh full grant");
  for (auto field:counters_by_field) returned.*field=27;
  budget.end_delegate(returned,preparation);
  budget.finish();
  for (auto field:counters_by_field) check(budget.usage.*field==40,"two-assessment aggregate is not P+3+(17-P)+(27-P)");
  check(budget.usage.active_nanoseconds==0,"timing-off neutral accounting invented elapsed time");
  std::uint64_t used=std::numeric_limits<std::uint64_t>::max()-1;
  budget_detail::Budget::add(used,1,std::numeric_limits<std::uint64_t>::max(),s::Resource::work);
  check(used==std::numeric_limits<std::uint64_t>::max(),"exact U64 boundary failed");
  bool stopped=false;
  try {budget_detail::Budget::add(used,1,std::numeric_limits<std::uint64_t>::max(),s::Resource::work);}
  catch (const budget_detail::Failure& error) {stopped=error.stop==s::Stop::resource_limit && error.resource==s::Resource::work;}
  check(stopped && used==std::numeric_limits<std::uint64_t>::max(),"U64 charge wrapped or mutated on overflow");
}

```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Check delegated Budget arithmetic against exact aggregate boundaries. |
| inputs / outputs | Computes a fixed preparation Usage and two assessment requests, then checks exact combined usage and overflow rejection. |
| invariants | The synthetic preparation equation checks all eight numeric resource fields with nonzero P/own/V1/V2 values; active_nanoseconds is separately asserted to remain zero. These values create no proof, Evidence or native work grant. |
| ownership | Only local value records are retained. |
| failure | Over-limit addition produces the expected resource stop without wrapped usage. |
| cost | Fixed eight-dimension arithmetic on stack values; no ranking/lowering call. |
| Design | [tests/unit/selection_resources_independent_test.cpp](../../../../../tests/unit/selection_resources_independent_test.cpp), [include/crown/planner/selection.hpp](../../../../../include/crown/planner/selection.hpp), [src/planner/selection.cpp](../../../../../src/planner/selection.cpp), [docs/selection.md](../../../../selection.md), [docs/selection_accounting.md](../../../../selection_accounting.md), [include/crown/runtime/selection.hpp](../../../../../include/crown/runtime/selection.hpp), [src/runtime/selection.cpp](../../../../../src/runtime/selection.cpp), [tests/support/selection_independent_fixture.hpp](../../../../../tests/support/selection_independent_fixture.hpp) |

## B0004

[Lines 53–102](../../../../../tests/unit/selection_resources_independent_test.cpp#L53); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void complete_dual_usage_and_boundaries(const BooleanFixture& f) {
  auto owner=r::PhysicalRuntime::initialize(lower(f.by_label.at("native_s")),f.initial);
  hot(owner,f);
  const auto facts=capture_checked(f.all,owner);
  const s::Source source{s::DirectCQ{}};
  auto request=depth();request.constraint=s::TupleIndexSlotLimit{"24"};
  const auto full=s::select(f.all,source,request,facts.inputs());
  const auto& result=complete(full);
  check(result.assessments().size()==2 && result.assessments()[0].purpose==s::AssessmentPurpose::slot_constraint &&
        result.assessments()[1].purpose==s::AssessmentPurpose::primary,
        "dual assessment order differs from constraint then complete primary");
  const auto& first=result.assessments()[0].result;
  const auto& second=result.assessments()[1].result;
  literal_slots(f,first);literal_depth(f,second);
  const auto& prepared=facts.inputs().preparation_usage();
  for (std::size_t i=0;i<counters_by_field.size();++i) {
    const auto field=counters_by_field[i];const auto limit=limits_by_field[i];
    const auto p=prepared.*field,v1=first.usage().*field,v2=second.usage().*field,u=result.usage().*field;
    check(v1>=p && v2>=p,"complete component usage omitted carried preparation");
    check(u>=p && u-p>=v1-p && u-p-(v1-p)>=v2-p,"aggregate omitted complete assessment cost");
    check(first.request().limits.*limit<=request.limits.aggregate.*limit &&
          second.request().limits.*limit<=first.request().limits.*limit &&
          first.request().limits.*limit-second.request().limits.*limit>=v1-p,
          "second delegated grant did not reflect first complete cost");
  }
  check(result.usage().active_nanoseconds==0 && result.preparation_timing()==s::PreparationTiming::unmeasured,
        "untimed as-of preparation was represented as measured zero");
  for (std::size_t i=0;i<counters_by_field.size();++i) {
    const auto consumed=result.usage().*counters_by_field[i];
    if (consumed==0) continue;
    auto exact=request;exact.limits.aggregate.*limits_by_field[i]=consumed;
    const auto fitted=s::select(f.all,source,exact,facts.inputs());
    check(fitted.stop==s::Stop::complete && fitted.selection && label(f,*fitted.selection)=="native_s",
          "exact aggregate resource boundary failed or changed the literal constrained choice");
    --(exact.limits.aggregate.*limits_by_field[i]);
    exact.fallback=rank::Fallback::height_only;
    const auto shortfall=s::select(f.all,source,exact,facts.inputs());
    check(shortfall.stop==s::Stop::resource_limit && !shortfall.selection,
          "one-under aggregate resource boundary published partial choice or used fallback");
  }
  for (const auto score_bits:{0U,513U}) {
    auto invalid=request;invalid.limits.aggregate.score_bits=score_bits;
    const auto stopped=s::select(f.all,source,invalid,facts.inputs());
    check(stopped.stop==s::Stop::invalid_request && !stopped.selection,"invalid score width reached ranking");
  }
  auto too_few=request;too_few.limits.aggregate.candidates=2;
  const auto candidate_stop=s::select(f.all,source,too_few,facts.inputs());
  check(candidate_stop.stop==s::Stop::resource_limit && !candidate_stop.selection,
        "candidate cap used a convenient prefix as a complete constrained winner");
}

```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Verify dual assessment shares capture preparation and respects exact work ceilings. |
| inputs / outputs | Uses complete Boolean evidence, runs dual-policy selection at cap 24, then exact/one-under cases for measured nonzero dimensions, score-bit and candidate-count limits. A fallback is configured for a one-under case; no cache is created. |
| invariants | Both complete assessments receive the remaining aggregate budget; one-under stops do not publish partial results or fallback; unmeasured preparation is not invented. |
| ownership | Selection retains Evidence and both assessment records; fixture runtime and values are local. This helper does not create or inspect a PlanCache. |
| failure | One-under usage ceilings and a candidate-count shortfall return resource_limit; score_bits 0 or 513 return invalid_request. A configured fallback does not publish a partial constrained result. |
| cost | Three retained candidates and bounded dual ranking/lowering; exact/one-under checks apply to exercised nonzero usage components, not necessarily every request dimension. Caps are logical accounting, not CPU time. |
| Design | [tests/unit/selection_resources_independent_test.cpp](../../../../../tests/unit/selection_resources_independent_test.cpp), [include/crown/planner/selection.hpp](../../../../../include/crown/planner/selection.hpp), [src/planner/selection.cpp](../../../../../src/planner/selection.cpp), [docs/selection.md](../../../../selection.md), [docs/selection_accounting.md](../../../../selection_accounting.md), [include/crown/runtime/selection.hpp](../../../../../include/crown/runtime/selection.hpp), [src/runtime/selection.cpp](../../../../../src/runtime/selection.cpp), [tests/support/selection_independent_fixture.hpp](../../../../../tests/support/selection_independent_fixture.hpp) |

## B0006

[Lines 104–154](../../../../../tests/unit/selection_resources_independent_test.cpp#L104); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void current_capture_and_time(const BooleanFixture& f) {
  auto owner=r::PhysicalRuntime::initialize(lower(f.by_label.at("native_s")),f.initial);
  hot(owner,f);
  const s::Source source{s::DirectCQ{}};
  const auto state=owner.canonical_state();
  const auto workload=owner.workload_statistics();
  auto request=depth();request.constraint=s::TupleIndexSlotLimit{"24"};
  r::statistics::Limits no_rows;no_rows.rows=0;no_rows.distinct_keys=0;
  const auto cardinality=current::select_current(f.all,source,owner,request,no_rows);
  const auto& captured=complete(cardinality).capture().inputs();
  check(captured.memory_reasons()==0 && captured.capture_accounting().state_rows==0 &&
        captured.capture_accounting().state_keys==0 && captured.sources().size()==3,
        "cardinality-only selection scanned rows/keys or lost exact source counts");
  for (const bool byte_limit:{false,true}) {
    auto limits=no_rows;
    if (byte_limit) limits.accounted_bytes=0;else limits.work=0;
    const auto unavailable=current::select_current(f.all,source,owner,request,limits);
    check(unavailable.stop==s::Stop::evidence_unavailable && !unavailable.selection &&
          has(unavailable.reasons,rank::Reason::source_budget_exhausted),
          "source-capture exhaustion was confused with an ordinary processing stop");
  }
  auto no_work=request;no_work.limits.aggregate.work=0;no_work.fallback=rank::Fallback::height_only;
  const auto processing=current::select_current(f.all,source,owner,no_work);
  check(processing.stop==s::Stop::resource_limit && !processing.selection && processing.resource==s::Resource::work,
        "zero C05 processing work became statistical fallback");
  const auto untimed=capture_checked(f.all,owner);
  check(untimed.inputs().preparation_usage().active_nanoseconds==0 &&
        !untimed.inputs().capture_accounting().processing_limits.active_time,"untimed preparation fixture is not untimed");
  auto timed=depth();timed.limits.aggregate.active_time=std::chrono::seconds{60};
  const auto historical=s::select(f.all,source,timed,untimed.inputs());
  check(complete(historical).preparation_timing()==s::PreparationTiming::unmeasured &&
        historical.selection->usage().active_nanoseconds>0,
        "timed as-of call fabricated measurement of prior untimed capture");
  const auto now=current::select_current(f.all,source,owner,timed);
  check(complete(now).selection().preparation_timing()==s::PreparationTiming::measured &&
        now.selection->capture().inputs().capture_accounting().processing_limits.active_time.has_value() &&
        now.selection->selection().usage().active_nanoseconds>=now.selection->capture().inputs().preparation_usage().active_nanoseconds,
        "current timed selection failed to time/carry its fresh preparation");
  capture::CaptureOptions measured;measured.processing.active_time=std::chrono::seconds{60};
  const auto saved=capture_checked(f.all,owner,measured);
  timed.limits.aggregate.active_time=std::chrono::nanoseconds{
      static_cast<std::chrono::nanoseconds::rep>(saved.inputs().preparation_usage().active_nanoseconds)};
  const auto carried=s::select(f.all,source,timed,saved.inputs());
  check(carried.stop==s::Stop::resource_limit && !carried.selection && carried.resource==s::Resource::active_time,
        "already-consumed carried time allowed fresh selection work");
  timed.limits.aggregate.active_time=std::chrono::nanoseconds{-1};
  const auto negative=s::select(f.all,source,timed,untimed.inputs());
  check(negative.stop==s::Stop::invalid_request && !negative.selection,"negative duration was admitted");
  check(owner.canonical_state()==state && same_workload(workload,owner.workload_statistics()),
        "resource/timing experiments changed complete owner or workload state");
}

```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Separate current capture, carried preparation timing, and rank-time limits. |
| inputs / outputs | Uses a nonempty three-source fixture with state row/key scan limits set to zero, then tests capture work/byte exhaustion, zero selection work, untimed as-of evidence, timed current capture and negative duration. |
| invariants | C01 capture work/byte limits can make current source facts unavailable; row/key scan limits of zero still permit cardinality-only facts for the nonempty sources. A zero aggregate selection-work cap returns resource_limit, but this test does not assert zero reported usage. Preparation timing remains separately measured or unmeasured. |
| ownership | Runtime owner supplies actual account; CurrentSelection retains fresh RuntimeEvidence; old Evidence remains as-of. |
| failure | Source and processing stops remain distinct; negative duration is invalid and no partial selection is returned. |
| cost | Several fresh captures and rank attempts; timing fields are observations, not a hard preemption or CPU guarantee. |
| Design | [tests/unit/selection_resources_independent_test.cpp](../../../../../tests/unit/selection_resources_independent_test.cpp), [include/crown/planner/selection.hpp](../../../../../include/crown/planner/selection.hpp), [src/planner/selection.cpp](../../../../../src/planner/selection.cpp), [docs/selection.md](../../../../selection.md), [docs/selection_accounting.md](../../../../selection_accounting.md), [include/crown/runtime/selection.hpp](../../../../../include/crown/runtime/selection.hpp), [src/runtime/selection.cpp](../../../../../src/runtime/selection.cpp), [tests/support/selection_independent_fixture.hpp](../../../../../tests/support/selection_independent_fixture.hpp) |

## B0007

[Lines 155–156](../../../../../tests/unit/selection_resources_independent_test.cpp#L155); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L155-L156:sha256:c929980d95efc152dc886ac42af0f045075441dd18a8f886364828ead327bbd3
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Close the recorded declaration scopes in selection_resources_independent_test.cpp: namespace (anonymous). |
| inputs / outputs | Preceding namespace, type or initializer declarations in; completed lexical boundary out. |
| invariants | Brace-opening context is recorded in root-scope-context-v1.json. These are declaration/initializer boundaries, not an independent update, validation or recovery operation. |
| ownership | Enclosing objects and borrowed fields keep their declared ownership. This punctuation creates no new owner. |
| failure | Malformed scope syntax is a compile error. Any initializer/constructor failure belongs to the enclosing object declaration. |
| cost | No separate loop, guard or engine call is introduced by the delimiter; enclosing initialization and object lifetime still have their actual costs. |
| Design | [tests/unit/selection_resources_independent_test.cpp](../../../../../tests/unit/selection_resources_independent_test.cpp), [docs/selection.md](../../../../selection.md), [docs/code_review.md](../../../../code_review.md) |

## B0008

[Lines 157–166](../../../../../tests/unit/selection_resources_independent_test.cpp#L157); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
int main(int argc,char** argv) {
  try {
    check(argc==2,"usage: selection_resources_independent_test REPOSITORY_ROOT");
    const auto fixture=boolean_fixture(argv[1]);
    fixed_preparation_algebra();
    complete_dual_usage_and_boundaries(fixture);
    current_capture_and_time(fixture);
    std::cout<<"C05 independent resources groups=3 additive_dimensions=8 literal_aggregate=40 cap=24 source_rows=0\n";
  } catch(const std::exception& error){std::cerr<<error.what()<<'\n';return 1;}
}

```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Run independent resource algebra and usage scenarios. |
| inputs / outputs | Loads fixture and runs fixed algebra, dual usage, and capture/time groups. |
| invariants | The helper groups assert separate account, C01 capture, and C02 ranking dimensions. |
| ownership | All fixture owners/results are local to helpers. |
| failure | Unexpected usage or stop fails the executable. |
| cost | Three groups with finite candidate and cap matrices. |
| Design | [tests/unit/selection_resources_independent_test.cpp](../../../../../tests/unit/selection_resources_independent_test.cpp), [include/crown/planner/selection.hpp](../../../../../include/crown/planner/selection.hpp), [src/planner/selection.cpp](../../../../../src/planner/selection.cpp), [docs/selection.md](../../../../selection.md), [docs/selection_accounting.md](../../../../selection_accounting.md), [include/crown/runtime/selection.hpp](../../../../../include/crown/runtime/selection.hpp), [src/runtime/selection.cpp](../../../../../src/runtime/selection.cpp), [tests/support/selection_independent_fixture.hpp](../../../../../tests/support/selection_independent_fixture.hpp) |
