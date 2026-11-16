# `tests/unit/maintenance_cost_fit_test.cpp` — block usage map

[Source](../../../../../tests/unit/maintenance_cost_fit_test.cpp) · [Source index](../../../README.md) · [Subsystem contracts](../../../subsystem_contracts.md) · [Reviewed primitives](../../../primitives.md)

Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection.

Snapshot SHA-256: `f5648c00ae925ca1828f7df3169fa6b37e1823d2b6c071e41783f9343cf491b8`. 82 lines partitioned into 5 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [tests](../../../subsystem_contracts.md#tests). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/code_review.md](../../../../code_review.md), [docs/reference_fuzz.md](../../../../reference_fuzz.md), [docs/task_ledger.md](../../../../task_ledger.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–12](../../../../../tests/unit/maintenance_cost_fit_test.cpp#L1) | Imports dependencies; declares namespace scope; declares aliases; declares values/defaults or compile-time conditions. |  · [reviewed contract](#b0001) |
| [B0002 · 13–13](../../../../../tests/unit/maintenance_cost_fit_test.cpp#L13) | Callable definition: void check(bool x,const char* message) | calls std::runtime_error; guard void check(bool x,const char* message){if(!x)throw std::runtime_error(message);} · [reviewed contract](#b0002) |
| [B0003 · 14–80](../../../../../tests/unit/maintenance_cost_fit_test.cpp#L14) | Callable definition: void run(const char* fixture) | calls source, check, bool, io::Json::parse; guard std::ifstream source(fixture);check(bool(source),"missing independent fixture");const auto input=io…; growth push_back; 7 loop sites · [reviewed contract](#b0003) |
| [B0004 · 81–81](../../../../../tests/unit/maintenance_cost_fit_test.cpp#L81) | Closes surrounding scope/type. |  · [reviewed contract](#b0004) |
| [B0005 · 82–82](../../../../../tests/unit/maintenance_cost_fit_test.cpp#L82) | Callable definition: int main(int argc,char** argv) | calls check, run, what; guard int main(int argc,char** argv){try{check(argc==2,"usage: FIT_FIXTURE.json");run(argv\[1\]);}catch(con…; returns 1 · [reviewed contract](#b0005) |

## B0001

[Lines 1–12](../../../../../tests/unit/maintenance_cost_fit_test.cpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L1-L12:sha256:3f1a9b5988fe53a0886d565c481dc4c18b8f774bdf14a93dbbe923aea19536d4
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Prepare maintenance_cost_fit_test.cpp: include "crown/runtime/maintenance_cost.hpp", "crown/io/document.hpp", &lt;cmath&gt;, &lt;fstream&gt;, &lt;iostream&gt;, &lt;limits&gt;, &lt;stdexcept&gt;; bind local aliases/name imports. |
| inputs / outputs | Compiler-visible dependencies, names and the recorded declarations in; declarations available to the following fixture/CLI/example definitions out. |
| invariants | Declarations are scoped to this source/header and its selected ABI. Included code has its own effects; names and editable fixture values do not confer proof, admission or publication authority. |
| ownership | Aliases/includes do not create a query owner. Pointers/references/views are non-owning. Containers own their elements, which can themselves be borrowed pointers or numeric IDs. Only documented owning shared-control handles retain controls; IDs/slot-handle values do not independently keep an arena/runtime alive. |
| failure | Missing headers, ill-formed names/types, failed static assertions or active #error directives stop compilation. No runtime rejection/rollback mechanism is implemented by aliases or function prototypes. |
| cost | Preprocessing and type/constraint instantiation cost compilation. Alias/prototype syntax does not invoke the declared operation; any included definitions keep their own initialization effects. |
| Design | [tests/unit/maintenance_cost_fit_test.cpp](../../../../../tests/unit/maintenance_cost_fit_test.cpp), [docs/maintenance_cost.md](../../../../maintenance_cost.md), [docs/code_review.md](../../../../code_review.md) |

## B0002

[Lines 13–13](../../../../../tests/unit/maintenance_cost_fit_test.cpp#L13); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void check(bool x,const char* message){if(!x)throw std::runtime_error(message);}

```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Turn a false fixture assertion into a named test exception. |
| inputs / outputs | Receives one Boolean and a static message; returns no value. |
| invariants | Only the supplied condition decides whether the assertion is accepted. |
| ownership | The message is borrowed for the duration of the throw; no result is retained. |
| failure | False raises std::runtime_error with the message. |
| cost | One branch; exception text is constructed only on failure. |
| Design | [tests/unit/maintenance_cost_fit_test.cpp](../../../../../tests/unit/maintenance_cost_fit_test.cpp), [include/crown/runtime/maintenance_cost.hpp](../../../../../include/crown/runtime/maintenance_cost.hpp), [src/runtime/maintenance_cost.cpp](../../../../../src/runtime/maintenance_cost.cpp), [docs/maintenance_cost.md](../../../../maintenance_cost.md) |

## B0003

[Lines 14–80](../../../../../tests/unit/maintenance_cost_fit_test.cpp#L14); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void run(const char* fixture) {
  std::ifstream source(fixture);check(bool(source),"missing independent fixture");const auto input=io::Json::parse(source);
  check(input.at("component_order").size()==model::component_count,"independent component order changed");
  for(std::size_t i=0;i<model::component_count;++i)check(input.at("component_order")[i]==model::component_name(static_cast<C>(i)),"independent component name/order mismatch");
  auto account=resource::MemoryAccount::create(16U*1024U*1024U);const auto baseline=account.statistics().current;
  for(const auto& fixture_case:input.at("fixtures")) {
    std::vector<model::FitObservation> observations;
    for(const auto& sample:fixture_case.at("samples")) {
      model::FitObservation observation;observation.elapsed_ns=sample.at("elapsed_ns").get<model::U64>();
      for(std::size_t j=0;j<fixture_case.at("feature_indices").size();++j)
        observation.units.at(fixture_case.at("feature_indices")[j].get<std::size_t>())=sample.at("units")[j].get<model::U64>();
      observations.push_back(observation);
    }
    model::FitOptions options;options.relative_tolerance=1e-12;
    const auto fitted=model::fit(account,"independent synthetic exact linear arithmetic","reference_ordered_v1",observations,options);
    check(fitted.stop==planner::ranking::Stop::complete && fitted.calibration.has_value(),"fit did not complete");
    const auto& calibration=*fitted.calibration;const auto& summary=*calibration.fit_summary();
    check(calibration.origin()==model::CalibrationOrigin::fitted_linear_assumption && summary.observations==observations.size(),"fit origin/sample count missing");
    check(summary.numerical_rank==fixture_case.at("expected").at("design_rank").get<std::size_t>(),"numerical rank differs from independent integer rank");
    check(summary.root_mean_square_error_ns==0 && summary.maximum_absolute_error_ns==0,"exact literal prediction differs after quantization");
    const auto name=fixture_case.at("name").get<std::string>();
    if(name=="identifiable_three_features") {
      check(!summary.underdetermined && summary.observed_features==3,"identifiable fixture reported ambiguous");
      const std::array<model::U64,3> expected{5,2,7};
      for(std::size_t j=0;j<3;++j) {
        const auto index=fixture_case.at("feature_indices")[j].get<std::size_t>();
        check(calibration.coefficients()[index] && calibration.coefficients()[index]->nanoseconds_per_unit==model::Ratio{expected[j],1},"independent coefficient differs");
        check(calibration.coefficients()[index]->elapsed_ns==0,"joint timing attributed as independent feature measurement");
      }
    }else if(name=="collinear_two_features") {
      check(summary.underdetermined && summary.observed_features==2,"collinear rates reported individually identifiable");
      for(const auto& observation:observations) {
        long double predicted=0;
        for(std::size_t j=0;j<model::component_count;++j)if(calibration.coefficients()[j]){
          const auto rate=calibration.coefficients()[j]->nanoseconds_per_unit;
          predicted+=static_cast<long double>(observation.units[j])*rate.numerator/rate.denominator;
        }
        check(predicted==observation.elapsed_ns,"collinear identified combination differs");
      }
    }else {
      const auto annotation=static_cast<std::size_t>(C::annotation_change),unused=static_cast<std::size_t>(C::checkpoint_byte);
      check(calibration.coefficients()[annotation] && calibration.coefficients()[annotation]->nanoseconds_per_unit==model::Ratio{},"measured zero became missing");
      check(!calibration.coefficients()[unused],"unused column got a fabricated zero coefficient");
    }
    const auto elapsed=calibration.fit_observations()[0].elapsed_ns;observations[0].elapsed_ns=9999;
    check(calibration.fit_observations()[0].elapsed_ns==elapsed,"raw fitting observations borrow caller memory");
    std::cout<<"C03 independent fit "<<name<<" rank="<<summary.numerical_rank<<" observed="<<summary.observed_features<<" passed\n";
  }
  check(account.statistics().current==baseline,"fit results/scratch did not return to receiving account baseline");
  std::array<model::FitObservation,1> one{};one[0].units[0]=1;one[0].elapsed_ns=10;
  model::FitOptions invalid;invalid.relative_tolerance=std::numeric_limits<double>::quiet_NaN();
  check(model::fit(account,"invalid","reference_ordered_v1",one,invalid).stop==planner::ranking::Stop::invalid_limits,"NaN fit option accepted");
  invalid={};invalid.quantization_denominator=0;
  check(model::fit(account,"invalid","reference_ordered_v1",one,invalid).stop==planner::ranking::Stop::invalid_limits,"zero quantization accepted");
  auto zero=one;zero[0].units[0]=0;
  check(model::fit(account,"invalid","reference_ordered_v1",zero).stop==planner::ranking::Stop::invalid_limits,"empty feature observation accepted");
  planner::ranking::Limits tiny;tiny.work=0;
  const auto stopped=model::fit(account,"work limit","reference_ordered_v1",one,{},tiny);
  check(stopped.stop==planner::ranking::Stop::work_limit && !stopped.calibration,"fit resource limit published partial calibration");
  const auto no_storage=resource::MemoryAccount::create(resource::MemoryAccount::control_bytes());
  const auto denied=model::fit(no_storage,"account exhaustion","reference_ordered_v1",one);
  check(denied.stop==planner::ranking::Stop::allocation_failure && !denied.calibration,"fit escaped receiving account");
  one[0].elapsed_ns=UINT64_MAX;
  check(model::fit(account,"quantization overflow","reference_ordered_v1",one).stop==planner::ranking::Stop::bit_limit,"quantized conversion overflow was not checked");
  check(account.statistics().current==baseline,"failed fit leaked account allocations");
  std::cout<<"C03 fit ownership/unknown/rank/NaN/quantization/work/account failure checks passed\n";
}

```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Compare independent synthetic fit fixtures with C03 whole-phase fitting. |
| inputs / outputs | Reads the JSON fixture, maps sparse feature indices into FitObservation vectors, calls fit, and checks rank, quantized rates, residuals, and failure cases. |
| invariants | The identifiable case expects rates 5,2,7; the collinear case checks only an identified combination and marks ambiguity; zero and unused coefficients remain distinct. |
| ownership | The 16 MiB account owns fit outputs; observations are local copies of fixture numbers, not measured runtime captures. |
| failure | Assertion failures throw; fit cases for NaN, zero denominator, empty feature, zero work, tiny account, and quantization overflow must stop without retained account growth. |
| cost | Iterates all fixture cases and each sample/feature index; fit performs bounded iterative work. Predicted exact residuals validate synthetic arithmetic, not elapsed CPU or prediction quality. |
| Design | [tests/unit/maintenance_cost_fit_test.cpp](../../../../../tests/unit/maintenance_cost_fit_test.cpp), [include/crown/runtime/maintenance_cost.hpp](../../../../../include/crown/runtime/maintenance_cost.hpp), [src/runtime/maintenance_cost.cpp](../../../../../src/runtime/maintenance_cost.cpp), [docs/maintenance_cost.md](../../../../maintenance_cost.md) |

## B0004

[Lines 81–81](../../../../../tests/unit/maintenance_cost_fit_test.cpp#L81); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L81-L81:sha256:412ca345ccf75bf9c0806bce695be8de808b79984251a7a54d202cf6101dd451
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Close the recorded declaration scopes in maintenance_cost_fit_test.cpp: namespace (anonymous). |
| inputs / outputs | Preceding namespace, type or initializer declarations in; completed lexical boundary out. |
| invariants | Brace-opening context is recorded in root-scope-context-v1.json. These are declaration/initializer boundaries, not an independent update, validation or recovery operation. |
| ownership | Enclosing objects and borrowed fields keep their declared ownership. This punctuation creates no new owner. |
| failure | Malformed scope syntax is a compile error. Any initializer/constructor failure belongs to the enclosing object declaration. |
| cost | No separate loop, guard or engine call is introduced by the delimiter; enclosing initialization and object lifetime still have their actual costs. |
| Design | [tests/unit/maintenance_cost_fit_test.cpp](../../../../../tests/unit/maintenance_cost_fit_test.cpp), [docs/maintenance_cost.md](../../../../maintenance_cost.md), [docs/code_review.md](../../../../code_review.md) |

## B0005

[Lines 82–82](../../../../../tests/unit/maintenance_cost_fit_test.cpp#L82); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
int main(int argc,char** argv){try{check(argc==2,"usage: FIT_FIXTURE.json");run(argv[1]);}catch(const std::exception& error){std::cerr<<error.what()<<'\n';return 1;}}

```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Load a caller-supplied fixture and report fit assertion failures. |
| inputs / outputs | Uses argv\[1\] as fixture path, invokes run, returns process status. |
| invariants | It does not manufacture fixture data or time a query. |
| ownership | The local account and JSON data die when main returns. |
| failure | Missing arguments or a thrown std::exception produce a nonzero exit. |
| cost | One fixture run; fit-loop cost depends on fixture sample sizes and options. |
| Design | [tests/unit/maintenance_cost_fit_test.cpp](../../../../../tests/unit/maintenance_cost_fit_test.cpp), [include/crown/runtime/maintenance_cost.hpp](../../../../../include/crown/runtime/maintenance_cost.hpp), [src/runtime/maintenance_cost.cpp](../../../../../src/runtime/maintenance_cost.cpp), [docs/maintenance_cost.md](../../../../maintenance_cost.md) |
