# `tests/unit/reoptimization_selection_test.cpp` — block usage map

[Source](../../../../../tests/unit/reoptimization_selection_test.cpp) · [Source index](../../../README.md) · [Subsystem contracts](../../../subsystem_contracts.md) · [Reviewed primitives](../../../primitives.md)

Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection.

Snapshot SHA-256: `55e3641c0d725b10822a61438533af31d3e7d09165b03f387e27889fb906d9c9`. 115 lines partitioned into 11 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [tests](../../../subsystem_contracts.md#tests). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/code_review.md](../../../../code_review.md), [docs/reference_fuzz.md](../../../../reference_fuzz.md), [docs/task_ledger.md](../../../../task_ledger.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–14](../../../../../tests/unit/reoptimization_selection_test.cpp#L1) | Imports dependencies; declares namespace scope; declares aliases; declares values/defaults or compile-time conditions. |  · [reviewed contract](#b0001) |
| [B0002 · 15–17](../../../../../tests/unit/reoptimization_selection_test.cpp#L15) | Callable definition: Relation rows(QuerySession& session) | calls snapshot, insert, storage::export_row, values; returns result; growth insert; 1 loop sites · [reviewed contract](#b0002) |
| [B0003 · 18–20](../../../../../tests/unit/reoptimization_selection_test.cpp#L18) | Callable definition: reoptimization::Options options() | calls ; returns value · [reviewed contract](#b0003) |
| [B0004 · 21–24](../../../../../tests/unit/reoptimization_selection_test.cpp#L21) | Callable definition: template&lt;class Function&gt; void rejected(Function&& function,std::string_view code) | calls function, check, code, std::runtime_error; guard try{function();}catch(const Error& failure){check(failure.code()==code,"C05 bridge rejected with wr… · [reviewed contract](#b0004) |
| [B0005 · 25–29](../../../../../tests/unit/reoptimization_selection_test.cpp#L25) | Callable definition: Output update(QuerySession& session,std::uint64_t sequence,TableId table,SetOperation operation,const Row& row) | calls batch, check, enqueue, begin_next; guard check(session.enqueue(batch)==io::Admission::accepted && session.begin_next(),"C05 bridge input mis…; returns result; growth emplace; 1 loop sites · [reviewed contract](#b0005) |
| [B0006 · 30–32](../../../../../tests/unit/reoptimization_selection_test.cpp#L30) | Callable definition: ps::Request request(ps::Policy policy) | calls ; returns value · [reviewed contract](#b0006) |
| [B0007 · 33–38](../../../../../tests/unit/reoptimization_selection_test.cpp#L33) | Callable definition: rs::CurrentSelection measured(QuerySession& session,const planner::CandidateSnapshot& family,ps::Policy policy=ps::Policy::height… | calls report_metadata, plan, rs::select_for_reoptimization, request; guard check(attempt.stop==ps::Stop::complete && attempt.selection && attempt.selection-&gt;preparation_nanos…; returns *attempt.selection · [reviewed contract](#b0007) |
| [B0008 · 39–65](../../../../../tests/unit/reoptimization_selection_test.cpp#L39) | Callable definition: void stale(const PhysicalPlan& plan,const planner::CandidateSnapshot& family,const Database& initial) | calls QuerySession::create_typed, start, report_metadata, owner; guard check(ordinary.selection && !ordinary.selection-&gt;preparation_nanoseconds(),"ordinary C05 selection …; growth insert; 1 loop sites · [reviewed contract](#b0008) |
| [B0009 · 66–98](../../../../../tests/unit/reoptimization_selection_test.cpp#L66) | Callable definition: template&lt;class Lower&gt; void install(const PhysicalPlan& plan,const planner::CandidateSnapshot& family,const Database& initial,Lowe… | calls file, QuerySession::create_typed, start, enable_generation; guard check(update(*session,sequence,TableId{0},SetOperation::insert,*initial.tables\[0\].begin())==; growth insert; 1 loop sites · [reviewed contract](#b0009) |
| [B0010 · 99–99](../../../../../tests/unit/reoptimization_selection_test.cpp#L99) | Closes surrounding scope/type. | source comment (unverified): // namespace · [reviewed contract](#b0010) |
| [B0011 · 100–115](../../../../../tests/unit/reoptimization_selection_test.cpp#L100) | Callable definition: int main(int argc,char** argv) | calls check, c05_independent::boolean_fixture, s04_runtime::options, c05_independent::lower; guard check(argc==2,"usage: reoptimization_selection SOURCE");const auto fixture=c05_independent::boolean…; returns planner::lower_tree(fixture.document.catalog,fixture.document.query,tree,physical); planner::lower_…; 1 loop sites · [reviewed contract](#b0011) |

## B0001

[Lines 1–14](../../../../../tests/unit/reoptimization_selection_test.cpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L1-L14:sha256:7e6e67a575c7e459e5176083a6cd86f84fb4fffba364bc8b886f7bccdeff992d
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Prepare reoptimization_selection_test.cpp: include "selection_independent_fixture.hpp", "indexed_runtime_fixture.hpp", "local_sink_fixture.hpp", "crown/frontend/admission.hpp", "crown/io/compiler_plan_artifact.hpp", &lt;iostream&gt;; bind local aliases/name imports. |
| inputs / outputs | Compiler-visible dependencies, names and the recorded declarations in; declarations available to the following fixture/CLI/example definitions out. |
| invariants | Declarations are scoped to this source/header and its selected ABI. Included code has its own effects; names and editable fixture values do not confer proof, admission or publication authority. |
| ownership | Aliases/includes do not create a query owner. Pointers/references/views are non-owning. Containers own their elements, which can themselves be borrowed pointers or numeric IDs. Only documented owning shared-control handles retain controls; IDs/slot-handle values do not independently keep an arena/runtime alive. |
| failure | Missing headers, ill-formed names/types, failed static assertions or active #error directives stop compilation. No runtime rejection/rollback mechanism is implemented by aliases or function prototypes. |
| cost | Preprocessing and type/constraint instantiation cost compilation. Alias/prototype syntax does not invoke the declared operation; any included definitions keep their own initialization effects. |
| Design | [tests/unit/reoptimization_selection_test.cpp](../../../../../tests/unit/reoptimization_selection_test.cpp), [docs/selection.md](../../../../selection.md), [docs/code_review.md](../../../../code_review.md) |

## B0002

[Lines 15–17](../../../../../tests/unit/reoptimization_selection_test.cpp#L15); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Relation rows(QuerySession& session) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Export committed QuerySession snapshot rows for comparison with the non-switching session. |
| inputs / outputs | Input mutable session reference; returns standard Relation of exported rows. |
| invariants | Reads the committed snapshot into a Relation. Duplicate rows would collapse because insertion success is not asserted; this is a distinct-row comparison, not a raw-output uniqueness check. |
| ownership | Result owns deep test copies. |
| failure | Snapshot/export failure propagates. |
| cost | Visits and copies every result row/field. |
| Design | [tests/unit/reoptimization_selection_test.cpp § Relation rows(QuerySession& session) (lines 15-17)](../../../../../tests/unit/reoptimization_selection_test.cpp), [include/crown/runtime/session.hpp § snapshot API](../../../../../include/crown/runtime/session.hpp) |

## B0003

[Lines 18–20](../../../../../tests/unit/reoptimization_selection_test.cpp#L18); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
reoptimization::Options options() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Set the explicit long forecast for selection-to-switch fixtures. |
| inputs / outputs | Returns Options with Forecast{1,000,000,000 ns, 1 ns, UINT64_MAX inputs}. |
| invariants | These caller values are predictions only. |
| ownership | Owns a value object. |
| failure | No failure path. |
| cost | Constant-time construction. |
| Design | [tests/unit/reoptimization_selection_test.cpp § reoptimization::Options options() (lines 18-20)](../../../../../tests/unit/reoptimization_selection_test.cpp), [include/crown/runtime/reoptimization.hpp § Forecast, Policy and Options (lines 11-61)](../../../../../include/crown/runtime/reoptimization.hpp), [docs/reoptimization.md § Policy units and boundaries (lines 42-57)](../../../../reoptimization.md) |

## B0004

[Lines 21–24](../../../../../tests/unit/reoptimization_selection_test.cpp#L21); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
template<class Function> void rejected(Function&& function,std::string_view code) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Require a selection bridge operation to reject with the exact error code. |
| inputs / outputs | Callable plus expected string code; invokes once and catches Error. |
| invariants | Only public Error codes are matched. |
| ownership | Borrows Function&&, invokes function() as a named lvalue and retains no result; code is a borrowed string_view. |
| failure | Throws if accepted or if code differs; other exceptions propagate. |
| cost | One invocation. |
| Design | [tests/unit/reoptimization_selection_test.cpp § template<class Function> void rejected(Function&& function,std::string_view code) (lines 21-24)](../../../../../tests/unit/reoptimization_selection_test.cpp) |

## B0005

[Lines 25–29](../../../../../tests/unit/reoptimization_selection_test.cpp#L25); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Output update(QuerySession& session,std::uint64_t sequence,TableId table,SetOperation operation,const Row& row) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Submit one exact wire-positioned update through QuerySession and drain its ordinary output into a signed set. |
| inputs / outputs | Inputs session, sequence, table, operation and borrowed row; builds one TransportBatch, begins, runs fixture finish, then reads all next_output rows. |
| invariants | Requires one accepted update and unique \`(operation,row)\` outputs; no local sink is involved in this helper. |
| ownership | TransportBatch is local; session retains committed data; returned set deep-copies output rows. |
| failure | Checks fail for missing admission/begin or repeated output; native exceptions propagate. |
| cost | One event, one epoch and complete output drain/copy. |
| Design | [tests/unit/reoptimization_selection_test.cpp § Output update(QuerySession& session,std::uint64_t sequence,TableId table,SetOperation operation,const Row& row) (lines 25-29)](../../../../../tests/unit/reoptimization_selection_test.cpp), [tests/support/local_sink_fixture.hpp § finish and output (lines 15-20)](../../../../../tests/support/local_sink_fixture.hpp) |

## B0006

[Lines 30–32](../../../../../tests/unit/reoptimization_selection_test.cpp#L30); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
ps::Request request(ps::Policy policy) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Construct a planner selection request with the chosen policy and required evidence fallback. |
| inputs / outputs | Input planner selection policy; output Request with fallback require_evidence. |
| invariants | Does not override request limits or turn evidence into a timed prediction. |
| ownership | Returns a value object. |
| failure | No failure path. |
| cost | Constant-time construction. |
| Design | [tests/unit/reoptimization_selection_test.cpp § ps::Request request(ps::Policy policy) (lines 30-32)](../../../../../tests/unit/reoptimization_selection_test.cpp), [include/crown/planner/selection.hpp § Request](../../../../../include/crown/planner/selection.hpp) |

## B0007

[Lines 33–38](../../../../../tests/unit/reoptimization_selection_test.cpp#L33); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
rs::CurrentSelection measured(QuerySession& session,const planner::CandidateSnapshot& family,ps::Policy policy=ps::Policy::height_only) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Use the explicit session-aware selection API and require a completed result with positive preparation wall time. |
| inputs / outputs | Inputs session, complete CandidateSnapshot and optional policy; selects from PhysicalBasis of current plan and returns CurrentSelection. |
| invariants | Requires \`Stop::complete\`, a selection, and measured nanoseconds &gt; 0; unlike ordinary \`select_current\`, this explicit API includes selection preparation timing. |
| ownership | Returned selection value is copied out of Attempt; the source plan and session are borrowed during selection. |
| failure | check fails when selection is incomplete or untimed; selection errors propagate. |
| cost | Runs one full selection attempt including whatever capture/ranking/lowering the API performs; no fixed work bound is asserted here. |
| Design | [tests/unit/reoptimization_selection_test.cpp § rs::CurrentSelection measured(QuerySession& session,const planner::CandidateSnapshot& family,ps::Policy policy=ps::Policy::height_only) (lines 33-38)](../../../../../tests/unit/reoptimization_selection_test.cpp), [src/runtime/selection.cpp § current, select_for_reoptimization and begin_reoptimization (lines 76-187)](../../../../../src/runtime/selection.cpp), [docs/reoptimization.md § Optional C05 integration (lines 246-271)](../../../../reoptimization.md) |

## B0008

[Lines 39–65](../../../../../tests/unit/reoptimization_selection_test.cpp#L39); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void stale(const PhysicalPlan& plan,const planner::CandidateSnapshot& family,const Database& initial) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Prove the bridge rejects unmeasured, stale, foreign, reset/configuration-changed, pending, and budget-denied selections without starting reoptimization. |
| inputs / outputs | Inputs plan, family and database. Compares ordinary unmeasured select, wrong expected owner, foreign owner, an intervening update, stats reset/configuration change, pending seq 2, then zero aggregate selection-work grant. |
| invariants | The assertions pin owner/epoch freshness and current committed/pending sequences; the failed budget attempt must leave current owner, epoch 2 and inactive reoptimization. |
| ownership | Source and foreign sessions own separate runtimes; choice handles retain selection data; update outputs are consumed normally. |
| failure | Each invalid selection must return the named error/stop; pending native epoch must remain sequence 2 and not be altered. |
| cost | Creates source and foreign sessions, one ordinary selection and five measured choices, processes sequence 1, then prepares and finishes sequence 2 around a stale rejection. Finally performs one zero-work selection attempt. |
| Design | [tests/unit/reoptimization_selection_test.cpp § void stale(const PhysicalPlan& plan,const planner::CandidateSnapshot& family,const Database& initial) (lines 39-65)](../../../../../tests/unit/reoptimization_selection_test.cpp), [src/runtime/selection.cpp § current, select_for_reoptimization and begin_reoptimization (lines 76-187)](../../../../../src/runtime/selection.cpp), [docs/reoptimization.md § Optional C05 integration (lines 246-271)](../../../../reoptimization.md) |

## B0009

[Lines 66–98](../../../../../tests/unit/reoptimization_selection_test.cpp#L66); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
template<class Lower> void install(const PhysicalPlan& plan,const planner::CandidateSnapshot& family,const Database& initial,Lower&& lower) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Compare measured C05 preparation, independent compiler artifact replay, native switch publication, and sequence-9 output against a non-switching reference. |
| inputs / outputs | Plan/family/database and lowering callback in. Two sessions process sequences 1..8; the switched session measures selection, pauses, begins candidate preparation and verifies barrier 8. It then prepares/replays a compiler artifact, publishes the target, rejects the now-stale choice and compares sequence 9 on both sessions. |
| invariants | Checks measured selection/freshness cost is positive and at least choice preparation time, and charged-and-reserved payback cost includes that field. At barrier 8 both epochs are verified; canonical lowered bytes and full compiler replay hash match the choice. Publication preserves pause and query-account owner while installing the selected physical hash. Forecast remains a caller prediction, not measured benefit. |
| ownership | Both sessions own separate runtime states; compiler artifact uses separate account; choice/target metadata are scoped values. |
| failure | Checks fail on selection timing/account, barrier epoch, artifact mismatch, publication state or next output/progress divergence; stale choice is rejected after publication. |
| cost | Eight prefix updates per session, one selection/candidate rebuild, artifact prepare+full replay, one switch and one next update; all outputs/rows are copied for comparison. |
| Design | [tests/unit/reoptimization_selection_test.cpp § template<class Lower> void install(const PhysicalPlan& plan,const planner::CandidateSnapshot& family,const Database& initial,Lower&& lower) (lines 66-98)](../../../../../tests/unit/reoptimization_selection_test.cpp), [src/runtime/selection.cpp § current, select_for_reoptimization and begin_reoptimization (lines 76-187)](../../../../../src/runtime/selection.cpp), [docs/reoptimization.md § Optional C05 integration (lines 246-271)](../../../../reoptimization.md), [src/io/compiler_plan_artifact.cpp § prepare and replay overloads (lines 23-54)](../../../../../src/io/compiler_plan_artifact.cpp), [src/runtime/session.cpp § publish_reoptimization (lines 1361-1413)](../../../../../src/runtime/session.cpp) |

## B0010

[Lines 99–99](../../../../../tests/unit/reoptimization_selection_test.cpp#L99); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L99-L99:sha256:533f16bca7d58f44b3103b92e3485d22cfbb34bbad5ea3f3fa3b5a9dcb24ec89
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Close the recorded declaration scopes in reoptimization_selection_test.cpp: namespace (anonymous). |
| inputs / outputs | Preceding namespace, type or initializer declarations in; completed lexical boundary out. |
| invariants | Brace-opening context is recorded in root-scope-context-v1.json. These are declaration/initializer boundaries, not an independent update, validation or recovery operation. |
| ownership | Enclosing objects and borrowed fields keep their declared ownership. This punctuation creates no new owner. |
| failure | Malformed scope syntax is a compile error. Any initializer/constructor failure belongs to the enclosing object declaration. |
| cost | No separate loop, guard or engine call is introduced by the delimiter; enclosing initialization and object lifetime still have their actual costs. |
| Design | [tests/unit/reoptimization_selection_test.cpp](../../../../../tests/unit/reoptimization_selection_test.cpp), [docs/selection.md](../../../../selection.md), [docs/code_review.md](../../../../code_review.md) |

## B0011

[Lines 100–115](../../../../../tests/unit/reoptimization_selection_test.cpp#L100); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
int main(int argc,char** argv) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Run CQ stale-selection rejection and CQ/SQL measured-plan installation on both physical backends. |
| inputs / outputs | Requires source root. Per backend, loads the CQ plan, calls stale and install for CQ, admits SQL EXISTS, creates its candidate family and calls install for SQL. |
| invariants | Only these fixture families and four backend/query combinations are selected; successful C05 selection does not claim global optimization beyond its provider snapshot. |
| ownership | Main owns fixture and families; helpers own sessions. |
| failure | Requires one path; exceptions print and return 1. |
| cost | Two CQ stale campaigns and four installation campaigns (CQ/SQL on each backend). Every installation processes eight prefix inputs plus one continuation on each of two sessions. |
| Design | [tests/unit/reoptimization_selection_test.cpp § int main(int argc,char** argv) (lines 100-115)](../../../../../tests/unit/reoptimization_selection_test.cpp), [tests/support/selection_independent_fixture.hpp § BooleanFixture and boolean_fixture (lines 111-157)](../../../../../tests/support/selection_independent_fixture.hpp), [CMakeLists.txt § reoptimization_selection registration (lines 684-689)](../../../../../CMakeLists.txt) |
