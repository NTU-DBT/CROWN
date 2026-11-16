# `tests/unit/ranking_payload_time_test.cpp` — block usage map

[Source](../../../../../tests/unit/ranking_payload_time_test.cpp) · [Source index](../../../README.md) · [Subsystem contracts](../../../subsystem_contracts.md) · [Reviewed primitives](../../../primitives.md)

Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection.

Snapshot SHA-256: `bc239d8a19ba5b9818841e7f82fc271f12b9142014a2484f96fae6c1ab5ab0f3`. 82 lines partitioned into 6 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [tests](../../../subsystem_contracts.md#tests). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/code_review.md](../../../../code_review.md), [docs/reference_fuzz.md](../../../../reference_fuzz.md), [docs/task_ledger.md](../../../../task_ledger.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–11](../../../../../tests/unit/ranking_payload_time_test.cpp#L1) | Imports dependencies; declares namespace scope; declares aliases; declares values/defaults or compile-time conditions. |  · [reviewed contract](#b0001) |
| [B0002 · 12–16](../../../../../tests/unit/ranking_payload_time_test.cpp#L12) | Callable definition: pr::Result memory(const planner::CandidateSnapshot& set,const runtime::PhysicalRuntime& owner) | calls rr::rank_current, check, has_value; guard check(attempt.result.has_value(),"normalized payload baseline failed");return *attempt.result;; returns *attempt.result · [reviewed contract](#b0002) |
| [B0003 · 17–17](../../../../../tests/unit/ranking_payload_time_test.cpp#L17) | Type/record definition: struct NormalizedFixture |  · [reviewed contract](#b0003) |
| [B0004 · 18–36](../../../../../tests/unit/ranking_payload_time_test.cpp#L18) | Callable definition: NormalizedFixture sql(std::size_t padding) | calls fixture, std::string, frontend::bind_sql, check; guard auto binding=frontend::bind_sql(source,f.catalog);check(std::holds_alternative&lt;frontend::BoundSql&gt;(…; returns {std::move(set),runtime::PhysicalRuntime::initialize(plan,f.database)} · [reviewed contract](#b0004) |
| [B0005 · 37–37](../../../../../tests/unit/ranking_payload_time_test.cpp#L37) | Closes surrounding scope/type. |  · [reviewed contract](#b0005) |
| [B0006 · 38–82](../../../../../tests/unit/ranking_payload_time_test.cpp#L38) | Callable definition: int main() | calls sql, memory, check, scores; guard check(large.scores().size()==3 && large.usage().payload_bytes&gt;=small.usage().payload_bytes+3*16'384…; returns 1; 1 loop sites; source comment (unverified): // All three separately owned plans retain the long source text. Comments · [reviewed contract](#b0006) |

## B0001

[Lines 1–11](../../../../../tests/unit/ranking_payload_time_test.cpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L1-L11:sha256:e1788eecc9095789f2b7c20cfb24713047aa57bfc1f0ffd27f3684c07829614c
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Prepare ranking_payload_time_test.cpp: include "ranking_fixture.hpp", "ranking_detail.hpp", "compiled_source.hpp", "crown/io/normalization.hpp", "crown/runtime/ranking_evidence.hpp", &lt;iostream&gt;; bind local aliases/name imports. |
| inputs / outputs | Compiler-visible dependencies, names and the recorded declarations in; declarations available to the following fixture/CLI/example definitions out. |
| invariants | Declarations are scoped to this source/header and its selected ABI. Included code has its own effects; names and editable fixture values do not confer proof, admission or publication authority. |
| ownership | Aliases/includes do not create a query owner. Pointers/references/views are non-owning. Containers own their elements, which can themselves be borrowed pointers or numeric IDs. Only documented owning shared-control handles retain controls; IDs/slot-handle values do not independently keep an arena/runtime alive. |
| failure | Missing headers, ill-formed names/types, failed static assertions or active #error directives stop compilation. No runtime rejection/rollback mechanism is implemented by aliases or function prototypes. |
| cost | Preprocessing and type/constraint instantiation cost compilation. Alias/prototype syntax does not invoke the declared operation; any included definitions keep their own initialization effects. |
| Design | [tests/unit/ranking_payload_time_test.cpp](../../../../../tests/unit/ranking_payload_time_test.cpp), [docs/ranking.md](../../../../ranking.md), [docs/code_review.md](../../../../code_review.md) |

## B0002

[Lines 12–16](../../../../../tests/unit/ranking_payload_time_test.cpp#L12); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
pr::Result memory(const planner::CandidateSnapshot& set,const runtime::PhysicalRuntime& owner){
  pr::Request request;request.policy=pr::Policy::tuple_index_slots;
  const auto attempt=rr::rank_current(set,owner,request);
  check(attempt.result.has_value(),"normalized payload baseline failed");return *attempt.result;
}

```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Rank the owner’s current input slots and return its immutable Result. |
| inputs / outputs | Receives CandidateSnapshot and PhysicalRuntime, captures evidence, ranks tuple-index slots, and returns the completed Result by value. |
| invariants | The score uses source-slot cardinality; returned Result is tied to the captured as-of evidence, not a promise of continued owner freshness. |
| ownership | Snapshot and owner are borrowed for the call; returned Result owns/share-retains its result and evidence handles. |
| failure | A failed capture or rank does not return a partial Result; caller turns the stop into a test failure. |
| cost | One bounded capture and rank over retained candidates; source and candidate traversal work is charged under C02 limits. |
| Design | [tests/unit/ranking_payload_time_test.cpp](../../../../../tests/unit/ranking_payload_time_test.cpp), [include/crown/planner/ranking.hpp](../../../../../include/crown/planner/ranking.hpp), [docs/ranking.md](../../../../ranking.md), [docs/ranking_accounting.md](../../../../ranking_accounting.md), [include/crown/runtime/ranking_evidence.hpp](../../../../../include/crown/runtime/ranking_evidence.hpp), [src/runtime/ranking_evidence.cpp](../../../../../src/runtime/ranking_evidence.cpp) |

## B0003

[Lines 17–17](../../../../../tests/unit/ranking_payload_time_test.cpp#L17); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct NormalizedFixture {planner::CandidateSnapshot set;runtime::PhysicalRuntime owner;};

```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Bundle a normalized-core candidate family with a runtime lowered from its first candidate. |
| inputs / outputs | Stores the full CandidateSnapshot family and one PhysicalRuntime initialized from a lower of set.candidate(0), returning both handles by value. |
| invariants | Both values derive from the same normalized SQL program; the runtime plan is for candidate zero and is not a common physical plan for every candidate in the snapshot. |
| ownership | The fixture owns both handles, so returned fixture does not borrow its local compiler objects. |
| failure | Preparation failure is thrown by the helper before fixture return. |
| cost | Preparation/lowering work occurs per helper invocation; no timing is asserted here. |
| Design | [tests/unit/ranking_payload_time_test.cpp](../../../../../tests/unit/ranking_payload_time_test.cpp), [include/crown/planner/ranking.hpp](../../../../../include/crown/planner/ranking.hpp), [docs/ranking.md](../../../../ranking.md), [docs/ranking_accounting.md](../../../../ranking_accounting.md), [include/crown/runtime/ranking_evidence.hpp](../../../../../include/crown/runtime/ranking_evidence.hpp), [src/runtime/ranking_evidence.cpp](../../../../../src/runtime/ranking_evidence.cpp) |

## B0004

[Lines 18–36](../../../../../tests/unit/ranking_payload_time_test.cpp#L18); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
NormalizedFixture sql(std::size_t padding){
  const auto f=fixture();
  const auto source=std::string("/*")+std::string(padding,'p')+"*/ SELECT EXISTS (SELECT 1 FROM \"R\" JOIN \"S\" ON \"R\".x=\"S\".x JOIN \"T\" ON \"S\".y=\"T\".y)";
  auto binding=frontend::bind_sql(source,f.catalog);check(std::holds_alternative<frontend::BoundSql>(binding),"SQL payload binding failed");
  auto normalized=frontend::normalize_sql(std::get<frontend::BoundSql>(binding));check(std::holds_alternative<frontend::NormalizedSql>(normalized),"SQL payload normalization failed");
  const auto program=std::get<frontend::NormalizedSql>(std::move(normalized));
  Fixture logical{program.core_catalog,program.core,{}};auto set=candidates(logical);
  const auto plan=planner::lower_normalized(program,set.candidate(0)->tree());
  const auto native=CompiledProgram::standalone(plan);
  const auto copy=planner::compiler_source_detail::normalized(*native.normalized());
  check(io::write_sql_normalization(frontend::SqlNormalizeResult{copy})==
    io::write_sql_normalization(frontend::SqlNormalizeResult{program}),
    "native compiler inputs changed the full normalized SQL program");
  const auto replay=planner::lower_normalized(copy,set.candidate(0)->tree(),
    planner::compiler_source_detail::options(native.options()));
  check(replay.identity().canonical==plan.identity().canonical && replay.physical_sha256()==plan.physical_sha256(),
    "native compiler inputs changed physical/semantic identities");
  return {std::move(set),runtime::PhysicalRuntime::initialize(plan,f.database)};
}

```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Prepare a normalized SQL fixture with controllable source padding. |
| inputs / outputs | Builds SQL with a comment of the requested length, normalizes and lowers it, and returns its candidate snapshot plus initialized runtime. |
| invariants | Comment padding changes retained source bytes but not query semantics or selected score. |
| ownership | The returned fixture owns its snapshot/runtime; local SQL and normalized inputs may die after return. |
| failure | Parser, lowerer, or runtime construction failure propagates; no partial fixture is returned. |
| cost | Each call parses and prepares the full padded text and initializes one owner; padding controls bytes, not a CPU guarantee. |
| Design | [tests/unit/ranking_payload_time_test.cpp](../../../../../tests/unit/ranking_payload_time_test.cpp), [include/crown/planner/ranking.hpp](../../../../../include/crown/planner/ranking.hpp), [docs/ranking.md](../../../../ranking.md), [docs/ranking_accounting.md](../../../../ranking_accounting.md), [include/crown/runtime/ranking_evidence.hpp](../../../../../include/crown/runtime/ranking_evidence.hpp), [src/runtime/ranking_evidence.cpp](../../../../../src/runtime/ranking_evidence.cpp) |

## B0005

[Lines 37–37](../../../../../tests/unit/ranking_payload_time_test.cpp#L37); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L37-L37:sha256:412ca345ccf75bf9c0806bce695be8de808b79984251a7a54d202cf6101dd451
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Close the recorded declaration scopes in ranking_payload_time_test.cpp: namespace (anonymous). |
| inputs / outputs | Preceding namespace, type or initializer declarations in; completed lexical boundary out. |
| invariants | Brace-opening context is recorded in root-scope-context-v1.json. These are declaration/initializer boundaries, not an independent update, validation or recovery operation. |
| ownership | Enclosing objects and borrowed fields keep their declared ownership. This punctuation creates no new owner. |
| failure | Malformed scope syntax is a compile error. Any initializer/constructor failure belongs to the enclosing object declaration. |
| cost | No separate loop, guard or engine call is introduced by the delimiter; enclosing initialization and object lifetime still have their actual costs. |
| Design | [tests/unit/ranking_payload_time_test.cpp](../../../../../tests/unit/ranking_payload_time_test.cpp), [docs/ranking.md](../../../../ranking.md), [docs/code_review.md](../../../../code_review.md) |

## B0006

[Lines 38–82](../../../../../tests/unit/ranking_payload_time_test.cpp#L38); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
int main(){try{
  using namespace c02_test;namespace pr=planner::ranking;namespace rr=runtime::ranking;
  // All three separately owned plans retain the long source text. Comments
  // change that payload without changing the literal query or score terms.
  auto short_sql=sql(0);auto long_sql=sql(16'384);
  const auto small=memory(short_sql.set,short_sql.owner);const auto large=memory(long_sql.set,long_sql.owner);
  check(large.scores().size()==3 && large.usage().payload_bytes>=small.usage().payload_bytes+3*16'384,"source payload was charged once instead of per candidate");
  for(const auto& score:large.scores())check(score.slots==(shape(score.candidate.tree())==0?"24":"32"),"source padding changed unitless proxy");
  pr::Request request;request.policy=pr::Policy::tuple_index_slots;request.fallback=pr::Fallback::height_only;
  request.limits.payload_bytes=large.usage().payload_bytes;
  const auto exact=rr::rank_current(long_sql.set,long_sql.owner,request);check(exact.result && exact.usage.payload_bytes==request.limits.payload_bytes,"exact retained payload ceiling failed");
  --request.limits.payload_bytes;
  const auto short_cap=rr::rank_current(long_sql.set,long_sql.owner,request);check(!short_cap.result && short_cap.stop==pr::Stop::byte_limit,"retained plan payload limit invoked fallback or published");
  check(long_sql.owner.sequence()==0 && long_sql.owner.has_answer() && large.scores().size()==3,"payload failure changed prior artifact or owner");

  Fixture typed;typed.catalog.tables={{"typed",{{"x",ScalarType::int64},{"d",ScalarType::decimal}}}};
  const auto coefficient=Decimal::parse("-99999999999999999999999999999999999999");
  typed.query.variables={{"x",ScalarType::int64}};
  typed.query.atoms={{"typed",TableId{0},{Term{VariableId{0}},Term{Value{coefficient}}}}};
  typed.query.head={{VariableId{0},"first"},{VariableId{0},"second"},{VariableId{0},"third"}};
  typed.database.tables={Relation{Row{std::int64_t{1},coefficient},Row{std::int64_t{2},coefficient}}};
  const auto typed_set=candidates(typed,1,0);
  auto typed_owner=runtime::PhysicalRuntime::initialize(planner::lower_tree(typed.catalog,typed.query,typed_set.candidate(0)->tree()),typed.database);
  const auto typed_result=memory(typed_set,typed_owner);const auto& selected=typed_result.scores()[typed_result.selected_index()];
  check(selected.slots=="13" && selected.modeled_plan->result_layout().fields().size()==3,"repeated head/Decimal literal proxy mismatch");
  const auto caller_plan=crown::PhysicalPlan::from_compiled(*selected.modeled_plan);
  check(std::get<Decimal>(caller_plan.inputs()[0].constants[0].value)==coefficient,"retained 38-digit Decimal copy changed");
  request.limits.payload_bytes=typed_result.usage().payload_bytes;
  check(rr::rank_current(typed_set,typed_owner,request).result.has_value(),"typed exact payload cap failed");
  --request.limits.payload_bytes;const auto typed_short=rr::rank_current(typed_set,typed_owner,request);
  check(!typed_short.result && typed_short.stop==pr::Stop::byte_limit,"typed retained payload escaped cap");

  const auto f=fixture();const auto set=candidates(f);auto owner=runtime::PhysicalRuntime::initialize(planner::lower_tree(f.catalog,f.query,set.candidate(0)->tree()),f.database);
  rr::CaptureOptions options;options.processing.active_time=std::chrono::minutes{10};
  const auto captured=rr::capture(set,owner,options);check(captured.evidence.has_value(),"timed capture failed");
  check(captured.usage.active_nanoseconds==captured.evidence->inputs().preparation_usage().active_nanoseconds,"capture lost its measured active work");
  request.limits=options.processing;
  const auto ranked=pr::rank(set,request,captured.evidence->inputs());check(ranked.result && ranked.usage.active_nanoseconds>=captured.usage.active_nanoseconds,"split rank discarded captured active work");
  request.limits.active_time=std::chrono::nanoseconds{static_cast<std::chrono::nanoseconds::rep>(captured.usage.active_nanoseconds)};
  const auto time_stop=pr::rank(set,request,captured.evidence->inputs());check(!time_stop.result && time_stop.stop==pr::Stop::time_limit && time_stop.usage.active_nanoseconds==captured.usage.active_nanoseconds,"carried exact time ceiling did not stop before ranking");
  pr::Limits limits;limits.active_time=std::chrono::nanoseconds{11};pr::Usage past;past.active_nanoseconds=11;
  bool stopped=false;try{pr::detail::Budget budget(limits,past);static_cast<void>(budget);}catch(const pr::detail::Failure& e){stopped=e.stop==pr::Stop::time_limit;}
  check(stopped,"time carry boundary was not transactional");
  std::cout<<"C02 per-candidate owned payload and aggregate active-time boundaries passed\n";
}catch(const std::exception& e){std::cerr<<e.what()<<'\n';return 1;}}

```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Separate payload-size admission and timing carried from preparation. |
| inputs / outputs | Compares small and 16,384-byte-padded SQL fixtures, exact/one-under payload caps, repeated Decimal output, and current-vs-as-of preparation timing. |
| invariants | Padding increases modeled retained source payload by at least 3×16,384 bytes while preserving scores; exact/one-under denial checks the selected result fields; carried preparation time is included only when measured; time caps are soft resource ceilings, not C02 score inputs. |
| ownership | Each fixture owns its actual runtime and retained source; ranked Results keep the capture context. |
| failure | One-under payload and carried-time limits stop transactionally; budget construction at its exact active-time cap is rejected. |
| cost | Runs two padded normalized-SQL preparations, payload-cap and timing calls, a separate typed Decimal/repeated-output fixture, and a further untimed/current-capture fixture with ranking attempts. It inspects modeled payload and active-time counters, not allocator bytes or benchmark CPU. |
| Design | [tests/unit/ranking_payload_time_test.cpp](../../../../../tests/unit/ranking_payload_time_test.cpp), [include/crown/planner/ranking.hpp](../../../../../include/crown/planner/ranking.hpp), [docs/ranking.md](../../../../ranking.md), [docs/ranking_accounting.md](../../../../ranking_accounting.md), [include/crown/runtime/ranking_evidence.hpp](../../../../../include/crown/runtime/ranking_evidence.hpp), [src/runtime/ranking_evidence.cpp](../../../../../src/runtime/ranking_evidence.cpp) |
