# `tests/unit/reoptimization_session_test.cpp` — block usage map

[Source](../../../../../tests/unit/reoptimization_session_test.cpp) · [Source index](../../../README.md) · [Subsystem contracts](../../../subsystem_contracts.md) · [Reviewed primitives](../../../primitives.md)

Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection.

Snapshot SHA-256: `9d8910ab38181396b0c4d4b66598c9f7361a214038e87e54c1812002c888d62e`. 253 lines partitioned into 20 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [tests](../../../subsystem_contracts.md#tests). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/code_review.md](../../../../code_review.md), [docs/reference_fuzz.md](../../../../reference_fuzz.md), [docs/task_ledger.md](../../../../task_ledger.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–14](../../../../../tests/unit/reoptimization_session_test.cpp#L1) | Imports dependencies; declares namespace scope; declares aliases; declares values/defaults or compile-time conditions. |  · [reviewed contract](#b0001) |
| [B0002 · 15–18](../../../../../tests/unit/reoptimization_session_test.cpp#L15) | Callable definition: template&lt;class Action&gt; void code(Action&& action,std::string_view expected) | calls action, check, std::runtime_error; guard try{action();}catch(const Error& failure){check(failure.code()==expected,"session candidate rejecte… · [reviewed contract](#b0002) |
| [B0003 · 19–21](../../../../../tests/unit/reoptimization_session_test.cpp#L19) | Callable definition: reoptimization::Options options() | calls ; returns result · [reviewed contract](#b0003) |
| [B0004 · 22–24](../../../../../tests/unit/reoptimization_session_test.cpp#L22) | Callable definition: SessionOptions session_options(DeltaMode mode) | calls ; returns result · [reviewed contract](#b0004) |
| [B0005 · 25–28](../../../../../tests/unit/reoptimization_session_test.cpp#L25) | Callable definition: void enqueue(QuerySession& session,io::InputItem item) | calls push_back, std::move, batch, check; guard check(session.enqueue(batch)==io::Admission::accepted && batch.empty(),"session candidate input was…; growth push_back · [reviewed contract](#b0005) |
| [B0006 · 29–33](../../../../../tests/unit/reoptimization_session_test.cpp#L29) | Callable definition: void collect(QuerySession& session,Outputs& outputs) | calls status, next_output, check, emplace; guard while(auto row=session.next_output())check(outputs\[sequence\].emplace(row-&gt;operation,storage::export…; growth emplace; 1 loop sites · [reviewed contract](#b0006) |
| [B0007 · 34–36](../../../../../tests/unit/reoptimization_session_test.cpp#L34) | Callable definition: void finish(QuerySession& session,Outputs& outputs) | calls step, commit, collect; 1 loop sites · [reviewed contract](#b0007) |
| [B0008 · 37–40](../../../../../tests/unit/reoptimization_session_test.cpp#L37) | Callable definition: void apply(QuerySession& session,const PhysicalSetUpdate& update,Outputs& outputs) | calls enqueue, check, begin_next, finish; guard check(session.begin_next(),"session input missing");finish(session,outputs); · [reviewed contract](#b0008) |
| [B0009 · 41–43](../../../../../tests/unit/reoptimization_session_test.cpp#L41) | Callable definition: Relation results(QuerySession& session) | calls snapshot, insert, storage::export_row, values; returns result; growth insert; 1 loop sites · [reviewed contract](#b0009) |
| [B0010 · 44–50](../../../../../tests/unit/reoptimization_session_test.cpp#L44) | Callable definition: reoptimization::Status barrier(QuerySession& session,Outputs& outputs) | calls advance_reoptimization, collect, std::runtime_error; returns status; 1 loop sites · [reviewed contract](#b0010) |
| [B0011 · 51–89](../../../../../tests/unit/reoptimization_session_test.cpp#L51) | Callable definition: void ordinary(const PhysicalPlan& plan,const planner::CandidateSnapshot& family,const Database& initial,DeltaMode mode,BuildMetho… | calls QuerySession::create_typed, session_options, start, options; guard check(prepared.phase==reoptimization::Phase::catching_up && prepared.source_owner==owner.value && p…; growth insert; 2 loop sites · [reviewed contract](#b0011) |
| [B0012 · 90–124](../../../../../tests/unit/reoptimization_session_test.cpp#L90) | Callable definition: void failures(const PhysicalPlan& plan,const planner::CandidateSnapshot& family,const Database& initial) | calls QuerySession::create_typed, session_options, start, options; guard check(session-&gt;begin_next(),"funded queue head missing after staging failure");finish(*session,outp…; growth allocate, insert, reserve; 1 loop sites; source comment (unverified): // Freeing the candidate supplies the original writer's ordinary grant. · [reviewed contract](#b0012) |
| [B0013 · 125–142](../../../../../tests/unit/reoptimization_session_test.cpp#L125) | Callable definition: void ledger_bytes(const PhysicalPlan& plan,const planner::CandidateSnapshot& family,const Database& initial) | calls QuerySession::create_typed, session_options, start, report_metadata; guard check(bytes&gt;0 && account.statistics_for(owner).current.requested_bytes-before==bytes,"ledger bytes …; growth insert · [reviewed contract](#b0013) |
| [B0014 · 143–169](../../../../../tests/unit/reoptimization_session_test.cpp#L143) | Callable definition: void projected(const Catalog& catalog,PhysicalOptions physical,DeltaMode mode) | calls frontend::admit_sql, check, c05_independent::candidates, planner::lower_normalized; guard check(admitted.status==frontend::AdmissionStatus::admitted,"projected/repeated/constant SQL candida…; growth insert, resize; 1 loop sites · [reviewed contract](#b0014) |
| [B0015 · 170–176](../../../../../tests/unit/reoptimization_session_test.cpp#L170) | Callable definition: void stream(const PhysicalPlan& plan,const planner::CandidateSnapshot& family,const Database& initial) | calls get, QuerySession::create, std::move, session_options; guard check(barrier(*session,output).phase==reoptimization::Phase::verified && borrowed-&gt;tellg()==std::st…; growth make_unique; source comment (unverified): // Barrier must not decode it, irrespective of its codec. · [reviewed contract](#b0015) |
| [B0016 · 177–183](../../../../../tests/unit/reoptimization_session_test.cpp#L177) | Callable definition: void command(QuerySession& session,io::WindowCommand item,Outputs& output) | calls enqueue, std::move, progress, check; guard check(session.begin_next(),"window candidate command missing");finish(session,output);; 1 loop sites · [reviewed contract](#b0016) |
| [B0017 · 184–204](../../../../../tests/unit/reoptimization_session_test.cpp#L184) | Callable definition: void window(const PhysicalPlan& plan,const planner::CandidateSnapshot& family,WindowFifoPolicy fifo) | calls QuerySession::create_windowed, session_options, start, std::string; guard check(session-&gt;status().committed_sequence==3 && session-&gt;progress().sequence==4,"duplicate label c…; 1 loop sites · [reviewed contract](#b0017) |
| [B0018 · 205–230](../../../../../tests/unit/reoptimization_session_test.cpp#L205) | Callable definition: void durable(const PhysicalPlan& plan,const planner::CandidateSnapshot& family,const Database& initial) | calls file, QuerySession::create_typed, session_options, start; guard const auto result=session-&gt;deliver_local_epoch();check(result.kind==LocalDeliveryKind::published &&…; growth insert; 1 loop sites · [reviewed contract](#b0018) |
| [B0019 · 231–231](../../../../../tests/unit/reoptimization_session_test.cpp#L231) | Closes surrounding scope/type. | source comment (unverified): // namespace · [reviewed contract](#b0019) |
| [B0020 · 232–253](../../../../../tests/unit/reoptimization_session_test.cpp#L232) | Callable definition: int main(int argc,char** argv) | calls check, c05_independent::boolean_fixture, s04_runtime::options, c05_independent::lower; guard check(argc==2,"usage: reoptimization_session SOURCE");const auto fixture=c05_independent::boolean_f…; returns 0; 1; 5 loop sites · [reviewed contract](#b0020) |

## B0001

[Lines 1–14](../../../../../tests/unit/reoptimization_session_test.cpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L1-L14:sha256:522c652739d74beac325df4f50aec5196b0b5d1f25a77221b9f0f81749539af5
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Prepare reoptimization_session_test.cpp: include "selection_independent_fixture.hpp", "indexed_runtime_fixture.hpp", "local_sink_fixture.hpp", "crown/frontend/admission.hpp", &lt;map&gt;, &lt;set&gt;, &lt;sstream&gt;; bind local aliases/name imports. |
| inputs / outputs | Compiler-visible dependencies, names and the recorded declarations in; declarations available to the following fixture/CLI/example definitions out. |
| invariants | Declarations are scoped to this source/header and its selected ABI. Included code has its own effects; names and editable fixture values do not confer proof, admission or publication authority. |
| ownership | Aliases/includes do not create a query owner. Pointers/references/views are non-owning. Containers own their elements, which can themselves be borrowed pointers or numeric IDs. Only documented owning shared-control handles retain controls; IDs/slot-handle values do not independently keep an arena/runtime alive. |
| failure | Missing headers, ill-formed names/types, failed static assertions or active #error directives stop compilation. No runtime rejection/rollback mechanism is implemented by aliases or function prototypes. |
| cost | Preprocessing and type/constraint instantiation cost compilation. Alias/prototype syntax does not invoke the declared operation; any included definitions keep their own initialization effects. |
| Design | [tests/unit/reoptimization_session_test.cpp](../../../../../tests/unit/reoptimization_session_test.cpp), [docs/reoptimization.md](../../../../reoptimization.md), [docs/code_review.md](../../../../code_review.md) |

## B0002

[Lines 15–18](../../../../../tests/unit/reoptimization_session_test.cpp#L15); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
template<class Action> void code(Action&& action,std::string_view expected) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Assert that a supplied session action fails with the requested CROWN error code. |
| inputs / outputs | Invokes the forwarded action; returns on a caught crown::Error whose code equals expected. |
| invariants | Only crown::Error is caught. A wrong code fails the check inside the catch; no caught CROWN error produces a runtime_error. |
| ownership | Borrows the callable and expected string_view for the call; it owns no session state. |
| failure | Wrong code or no CROWN error throws a test exception; other exception types propagate unchanged. |
| cost | One action invocation and catch/compare path, with no loop or runtime work claim. |
| Design | [tests/unit/reoptimization_session_test.cpp](../../../../../tests/unit/reoptimization_session_test.cpp), [tests/support/selection_independent_fixture.hpp](../../../../../tests/support/selection_independent_fixture.hpp), [include/crown/runtime/session.hpp](../../../../../include/crown/runtime/session.hpp), [include/crown/runtime/reoptimization.hpp](../../../../../include/crown/runtime/reoptimization.hpp), [src/runtime/session.cpp](../../../../../src/runtime/session.cpp), [src/runtime/reoptimization.cpp](../../../../../src/runtime/reoptimization.cpp), [docs/reoptimization.md](../../../../reoptimization.md) |

## B0003

[Lines 19–21](../../../../../tests/unit/reoptimization_session_test.cpp#L19); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
reoptimization::Options options() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Supply the test forecast that makes ordinary migration policy eligible. |
| inputs / outputs | Returns Options with forecast current=1,000,000,000 ns/input, target=1 ns/input, horizon=UINT64_MAX. |
| invariants | This is a caller prediction used by the test; it is not measured session performance. |
| ownership | Returns a small value object; no session or account is retained. |
| failure | No explicit failure branch in the helper. |
| cost | Constructs and returns a fixed-size options value; no heap or timing claim. |
| Design | [tests/unit/reoptimization_session_test.cpp](../../../../../tests/unit/reoptimization_session_test.cpp), [tests/support/selection_independent_fixture.hpp](../../../../../tests/support/selection_independent_fixture.hpp), [include/crown/runtime/session.hpp](../../../../../include/crown/runtime/session.hpp), [include/crown/runtime/reoptimization.hpp](../../../../../include/crown/runtime/reoptimization.hpp), [src/runtime/session.cpp](../../../../../src/runtime/session.cpp), [src/runtime/reoptimization.cpp](../../../../../src/runtime/reoptimization.cpp), [docs/reoptimization.md](../../../../reoptimization.md) |

## B0004

[Lines 22–24](../../../../../tests/unit/reoptimization_session_test.cpp#L22); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
SessionOptions session_options(DeltaMode mode) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Configure a typed test session for the chosen delta mode and support-account cap. |
| inputs / outputs | Returns SessionOptions with the supplied DeltaMode and physical support memory limit 32 MiB. |
| invariants | The cap is scoped to the configured support memory limit; this helper does not cap CPU or total process memory. |
| ownership | Returns options by value; session creation later consumes them. |
| failure | No helper-level failure path. |
| cost | Fixed option assignments; actual allocations happen during session creation/use. |
| Design | [tests/unit/reoptimization_session_test.cpp](../../../../../tests/unit/reoptimization_session_test.cpp), [tests/support/selection_independent_fixture.hpp](../../../../../tests/support/selection_independent_fixture.hpp), [include/crown/runtime/session.hpp](../../../../../include/crown/runtime/session.hpp), [include/crown/runtime/reoptimization.hpp](../../../../../include/crown/runtime/reoptimization.hpp), [src/runtime/session.cpp](../../../../../src/runtime/session.cpp), [src/runtime/reoptimization.cpp](../../../../../src/runtime/reoptimization.cpp), [docs/reoptimization.md](../../../../reoptimization.md) |

## B0005

[Lines 25–28](../../../../../tests/unit/reoptimization_session_test.cpp#L25); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void enqueue(QuerySession& session,io::InputItem item) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Admit one test item through the typed transport queue. |
| inputs / outputs | Moves one InputItem into a vector and TransportBatch, then requires accepted admission and an empty batch. |
| invariants | The one-item accepted batch is asserted at this call site; queue admission policy remains the session implementation contract. |
| ownership | The vector and batch are local; accepted data is transferred into session-owned queue state. |
| failure | A failed admission or unconsumed batch throws through check. |
| cost | Builds one vector element/batch and performs one enqueue; queue/account work is implementation-dependent. |
| Design | [tests/unit/reoptimization_session_test.cpp](../../../../../tests/unit/reoptimization_session_test.cpp), [tests/support/selection_independent_fixture.hpp](../../../../../tests/support/selection_independent_fixture.hpp), [include/crown/runtime/session.hpp](../../../../../include/crown/runtime/session.hpp), [include/crown/runtime/reoptimization.hpp](../../../../../include/crown/runtime/reoptimization.hpp), [src/runtime/session.cpp](../../../../../src/runtime/session.cpp), [src/runtime/reoptimization.cpp](../../../../../src/runtime/reoptimization.cpp), [docs/reoptimization.md](../../../../reoptimization.md) |

## B0006

[Lines 29–33](../../../../../tests/unit/reoptimization_session_test.cpp#L29); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void collect(QuerySession& session,Outputs& outputs) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Collect committed outputs into the test-owned sequence/output map. |
| inputs / outputs | Returns early while a physical sequence or command is pending; otherwise drains output rows and inserts operation/row pairs under committed sequence. |
| invariants | Duplicate output pairs fail the assertion. This helper is an oracle collector, not a delivery or migration API. |
| ownership | The map, sets, and exported rows belong to the test; output tuple access is consumed during each iteration. |
| failure | Duplicate output or session API errors propagate as test failures. |
| cost | Checks session status and inserts each observed output row; map/set allocation and row copying depend on output size. |
| Design | [tests/unit/reoptimization_session_test.cpp](../../../../../tests/unit/reoptimization_session_test.cpp), [tests/support/selection_independent_fixture.hpp](../../../../../tests/support/selection_independent_fixture.hpp), [include/crown/runtime/session.hpp](../../../../../include/crown/runtime/session.hpp), [include/crown/runtime/reoptimization.hpp](../../../../../include/crown/runtime/reoptimization.hpp), [src/runtime/session.cpp](../../../../../src/runtime/session.cpp), [src/runtime/reoptimization.cpp](../../../../../src/runtime/reoptimization.cpp), [docs/reoptimization.md](../../../../reoptimization.md) |

## B0007

[Lines 34–36](../../../../../tests/unit/reoptimization_session_test.cpp#L34); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void finish(QuerySession& session,Outputs& outputs) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Finish a pending delta epoch and immediately collect its output. |
| inputs / outputs | Steps until DeltaStep::prepared, commits, then calls collect. |
| invariants | Callers must have begun a valid epoch; there is no loop-count guard in this helper. |
| ownership | The session retains runtime state; collected outputs are copied into the caller-owned map. |
| failure | Session errors or a failed duplicate-output assertion propagate. |
| cost | Performs as many step calls as the pending epoch requires, one commit, and output collection; not CPU-bounded by this test helper. |
| Design | [tests/unit/reoptimization_session_test.cpp](../../../../../tests/unit/reoptimization_session_test.cpp), [tests/support/selection_independent_fixture.hpp](../../../../../tests/support/selection_independent_fixture.hpp), [include/crown/runtime/session.hpp](../../../../../include/crown/runtime/session.hpp), [include/crown/runtime/reoptimization.hpp](../../../../../include/crown/runtime/reoptimization.hpp), [src/runtime/session.cpp](../../../../../src/runtime/session.cpp), [src/runtime/reoptimization.cpp](../../../../../src/runtime/reoptimization.cpp), [docs/reoptimization.md](../../../../reoptimization.md) |

## B0008

[Lines 37–40](../../../../../tests/unit/reoptimization_session_test.cpp#L37); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void apply(QuerySession& session,const PhysicalSetUpdate& update,Outputs& outputs) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Apply one physical update to a typed session with a deterministic source position. |
| inputs / outputs | Enqueues the update as InputEvent at feed offset sequence*10, requires begin_next, then finishes and collects. |
| invariants | The helper expects the event to be available and begin_next to succeed; it does not model input rejection. |
| ownership | Input item is moved through a local batch into the session; expected output is copied to the caller map. |
| failure | Admission/begin/step/commit or check failures propagate. |
| cost | One queue admission and one epoch step loop plus output work; cost depends on the physical plan and emitted rows. |
| Design | [tests/unit/reoptimization_session_test.cpp](../../../../../tests/unit/reoptimization_session_test.cpp), [tests/support/selection_independent_fixture.hpp](../../../../../tests/support/selection_independent_fixture.hpp), [include/crown/runtime/session.hpp](../../../../../include/crown/runtime/session.hpp), [include/crown/runtime/reoptimization.hpp](../../../../../include/crown/runtime/reoptimization.hpp), [src/runtime/session.cpp](../../../../../src/runtime/session.cpp), [src/runtime/reoptimization.cpp](../../../../../src/runtime/reoptimization.cpp), [docs/reoptimization.md](../../../../reoptimization.md) |

## B0009

[Lines 41–43](../../../../../tests/unit/reoptimization_session_test.cpp#L41); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Relation results(QuerySession& session) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Copy the session snapshot rows into a comparison Relation. |
| inputs / outputs | Calls snapshot, exports each row, and inserts the copied values into a set-like Relation. |
| invariants | Used only as a test oracle for equality against the reference session. |
| ownership | Snapshot/result rows are copied into the local Relation; no cursor or snapshot ownership is returned. |
| failure | Snapshot/export/allocation failures propagate. |
| cost | Visits and copies every snapshot row; result container work and allocations scale with observed rows. |
| Design | [tests/unit/reoptimization_session_test.cpp](../../../../../tests/unit/reoptimization_session_test.cpp), [tests/support/selection_independent_fixture.hpp](../../../../../tests/support/selection_independent_fixture.hpp), [include/crown/runtime/session.hpp](../../../../../include/crown/runtime/session.hpp), [include/crown/runtime/reoptimization.hpp](../../../../../include/crown/runtime/reoptimization.hpp), [src/runtime/session.cpp](../../../../../src/runtime/session.cpp), [src/runtime/reoptimization.cpp](../../../../../src/runtime/reoptimization.cpp), [docs/reoptimization.md](../../../../reoptimization.md) |

## B0010

[Lines 44–50](../../../../../tests/unit/reoptimization_session_test.cpp#L44); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
reoptimization::Status barrier(QuerySession& session,Outputs& outputs) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Drive a requested migration barrier to a terminal verification, failure, or rejection state. |
| inputs / outputs | Calls advance_reoptimization(1) at most 10,000 times and collects output after each call; returns on verified, failed, or rejected. |
| invariants | A nonterminal status after the finite call guard is an error. Quantum one limits requested migration progress per call, not elapsed CPU time. |
| ownership | The session owns the candidate and its target/ledger; Outputs remains test-owned. |
| failure | Throws runtime_error if no terminal status is observed; API and collector exceptions propagate. |
| cost | Up to 10,000 status/advance/collect iterations, with per-call draining, replay, comparison, and output work as driven by the implementation; not a wall-clock bound. |
| Design | [tests/unit/reoptimization_session_test.cpp](../../../../../tests/unit/reoptimization_session_test.cpp), [tests/support/selection_independent_fixture.hpp](../../../../../tests/support/selection_independent_fixture.hpp), [include/crown/runtime/session.hpp](../../../../../include/crown/runtime/session.hpp), [include/crown/runtime/reoptimization.hpp](../../../../../include/crown/runtime/reoptimization.hpp), [src/runtime/session.cpp](../../../../../src/runtime/session.cpp), [src/runtime/reoptimization.cpp](../../../../../src/runtime/reoptimization.cpp), [docs/reoptimization.md](../../../../reoptimization.md) |

## B0011

[Lines 51–89](../../../../../tests/unit/reoptimization_session_test.cpp#L51); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void ordinary(const PhysicalPlan& plan,const planner::CandidateSnapshot& family,const Database& initial,DeltaMode mode,BuildMethod method) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Compare an ordinary candidate migration with a continuously running reference session through a paused input barrier. |
| inputs / outputs | Builds the candidate under the selected mode/build method; commits four ordered updates to both sessions, queues two more only on the migrating session, pauses and drains them, checks verification/status/output/result equality, then cancels and applies sequence 7. |
| invariants | Bootstrap asserts a distinct target owner in the same query account and greater current requested bytes; the barrier checks source/target epoch 6, six staged/replayed records, backlog zero, eight source-row and two result-row visits, positive logical work and clock-read counters, eligible policy, and preserved pause/progress/output. Cancel lowers current requested bytes, unfreezes admission, and leaves the original owner runnable. Candidate verification is separate from publication; cancellation unfreezes the original plan. |
| ownership | Each session owns a runtime/account; the migration session owns a private target and staged ledger until cancel. Reference output/results are copied into test containers. |
| failure | Any failed admission, mismatched oracle/status, rejected policy, or nonterminal bounded barrier fails the test. |
| cost | Processes six physical updates across two sessions, catches up in one-step grants, drains queued input, and compares rows/results. The fixed work counters are logical runtime counters; no CPU bound is asserted. |
| Design | [tests/unit/reoptimization_session_test.cpp](../../../../../tests/unit/reoptimization_session_test.cpp), [tests/support/selection_independent_fixture.hpp](../../../../../tests/support/selection_independent_fixture.hpp), [include/crown/runtime/session.hpp](../../../../../include/crown/runtime/session.hpp), [include/crown/runtime/reoptimization.hpp](../../../../../include/crown/runtime/reoptimization.hpp), [src/runtime/session.cpp](../../../../../src/runtime/session.cpp), [src/runtime/reoptimization.cpp](../../../../../src/runtime/reoptimization.cpp), [docs/reoptimization.md](../../../../reoptimization.md) |

## B0012

[Lines 90–124](../../../../../tests/unit/reoptimization_session_test.cpp#L90); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void failures(const PhysicalPlan& plan,const planner::CandidateSnapshot& family,const Database& initial) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Exercise bounded candidate failure classes and prove the original writer can continue and a fresh candidate can retry. |
| inputs / outputs | Eight cases set backlog-record, staging-work, catch-up-step, equivalence-work, equivalence-row, forecast, allocation, or cursor-work limits; each commits an original update, checks failed/rejected status and retries. A separate expected-boundary case supplies epoch 1 while the source is at epoch 0. |
| invariants | The seven candidate stop cases distinguish backlog_limit, staging_limit, catch_up_limit, equivalence_limit, allocation_failure, and forecast_unavailable rejection; the stale source is rejected before an active target remains. The original committed sequence remains 1 and later updates/retry still succeed. |
| ownership | A temporary account reservation forces candidate-side allocation pressure; candidate state is cancelled/released so the original writer can use its grant. |
| failure | Unexpected phase/stop, rollback of the committed original event, failed retry, or acceptance of stale owner/epoch fails. |
| cost | Runs eight fresh session cases plus a stale-boundary case; failure positions are deliberately limited to the listed configured grants. The reservation is requested-byte account work, not a CPU/RSS measurement. |
| Design | [tests/unit/reoptimization_session_test.cpp](../../../../../tests/unit/reoptimization_session_test.cpp), [tests/support/selection_independent_fixture.hpp](../../../../../tests/support/selection_independent_fixture.hpp), [include/crown/runtime/session.hpp](../../../../../include/crown/runtime/session.hpp), [include/crown/runtime/reoptimization.hpp](../../../../../include/crown/runtime/reoptimization.hpp), [src/runtime/session.cpp](../../../../../src/runtime/session.cpp), [src/runtime/reoptimization.cpp](../../../../../src/runtime/reoptimization.cpp), [docs/reoptimization.md](../../../../reoptimization.md) |

## B0013

[Lines 125–142](../../../../../tests/unit/reoptimization_session_test.cpp#L125); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void ledger_bytes(const PhysicalPlan& plan,const planner::CandidateSnapshot& family,const Database& initial) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Check the ledger byte counter against actual requested allocations and exact/one-byte-short record limits. |
| inputs / outputs | Measures session-owner requested bytes around one staged record, then tests cap bytes-1, exact bytes, and an additional duplicate insert; finally drops the session. |
| invariants | The assertion equates backlog_bytes with the observed session-attribution requested-byte delta for this fixture record, not with all heap/process usage. The later no-op commit remains sequence 4 despite candidate backlog overflow. |
| ownership | The ledger and record are charged to the original account with session owner attribution 1; drop must release that attribution. |
| failure | Wrong byte delta/cap status, blocked original no-op commit, or retained attributed allocations fails. |
| cost | Creates several sessions and records, reads account statistics, and exercises allocator framing for the concrete row; no general byte formula or CPU bound is inferred. |
| Design | [tests/unit/reoptimization_session_test.cpp](../../../../../tests/unit/reoptimization_session_test.cpp), [tests/support/selection_independent_fixture.hpp](../../../../../tests/support/selection_independent_fixture.hpp), [include/crown/runtime/session.hpp](../../../../../include/crown/runtime/session.hpp), [include/crown/runtime/reoptimization.hpp](../../../../../include/crown/runtime/reoptimization.hpp), [src/runtime/session.cpp](../../../../../src/runtime/session.cpp), [src/runtime/reoptimization.cpp](../../../../../src/runtime/reoptimization.cpp), [docs/reoptimization.md](../../../../reoptimization.md) |

## B0014

[Lines 143–169](../../../../../tests/unit/reoptimization_session_test.cpp#L143); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void projected(const Catalog& catalog,PhysicalOptions physical,DeltaMode mode) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Verify migration equivalence for a DISTINCT SQL result with repeated and constant projected columns. |
| inputs / outputs | Admits the literal R/S/T SQL, builds a normalized plan and reference, starts with 2/4/2 rows, applies six updates to both sessions with migration advance(2), then checks a one-row literal result and exact output deltas. |
| invariants | The literal row is (x,y,x,7); barrier target epoch is 6 with two result-row visits. For maintenance mode the test does not require two emitted deletes; delta mode requires the expected two deletions. |
| ownership | The admitted program, sessions, and snapshots own their plan/runtime state; Relations and output maps are test-owned copies. |
| failure | Admission, exact result/delta, phase, epoch, or visit-count mismatch fails. |
| cost | Performs SQL admission/lowering, two sessions, six updates and two-step migration advances; visits/copies are fixture-dependent and the assertions do not claim a universal scan bound. |
| Design | [tests/unit/reoptimization_session_test.cpp](../../../../../tests/unit/reoptimization_session_test.cpp), [tests/support/selection_independent_fixture.hpp](../../../../../tests/support/selection_independent_fixture.hpp), [include/crown/runtime/session.hpp](../../../../../include/crown/runtime/session.hpp), [include/crown/runtime/reoptimization.hpp](../../../../../include/crown/runtime/reoptimization.hpp), [src/runtime/session.cpp](../../../../../src/runtime/session.cpp), [src/runtime/reoptimization.cpp](../../../../../src/runtime/reoptimization.cpp), [docs/reoptimization.md](../../../../reoptimization.md), [include/crown/frontend/admission.hpp](../../../../../include/crown/frontend/admission.hpp) |

## B0015

[Lines 170–176](../../../../../tests/unit/reoptimization_session_test.cpp#L170); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void stream(const PhysicalPlan& plan,const planner::CandidateSnapshot& family,const Database& initial) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Prove that requesting a barrier on an owned stream does not decode an unadmitted byte. |
| inputs / outputs | Creates an istringstream containing “+ R x\\n”, retains a borrowed raw pointer for observation, prepares and verifies at sequence zero, then cancels. |
| invariants | The observed stream position remains zero and session progress stays at zero; this fixture has no admitted stream row. |
| ownership | The session owns the moved istringstream; the raw pointer is borrowed only while the session remains alive. |
| failure | Barrier failure or changed stream position/progress fails. |
| cost | One bounded barrier loop plus a stream-position check; no decoder input is consumed by this scenario. |
| Design | [tests/unit/reoptimization_session_test.cpp](../../../../../tests/unit/reoptimization_session_test.cpp), [tests/support/selection_independent_fixture.hpp](../../../../../tests/support/selection_independent_fixture.hpp), [include/crown/runtime/session.hpp](../../../../../include/crown/runtime/session.hpp), [include/crown/runtime/reoptimization.hpp](../../../../../include/crown/runtime/reoptimization.hpp), [src/runtime/session.cpp](../../../../../src/runtime/session.cpp), [src/runtime/reoptimization.cpp](../../../../../src/runtime/reoptimization.cpp), [docs/reoptimization.md](../../../../reoptimization.md) |

## B0016

[Lines 177–183](../../../../../tests/unit/reoptimization_session_test.cpp#L177); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void command(QuerySession& session,io::WindowCommand item,Outputs& output) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Process a window command until its accepted sequence reaches the requested command sequence. |
| inputs / outputs | Moves the command into the queue; performs up to 100 begin_next/finish iterations while progress is behind; requires exact final sequence. |
| invariants | The helper bounds command-loop iterations, not time spent in each command/epoch. |
| ownership | Command is moved into session queue; output is collected into the caller map. |
| failure | Missing command, unsuccessful begin, or incomplete sequence after 100 attempts fails. |
| cost | At most 100 command starts/finishes and their per-command epoch/output work. |
| Design | [tests/unit/reoptimization_session_test.cpp](../../../../../tests/unit/reoptimization_session_test.cpp), [tests/support/selection_independent_fixture.hpp](../../../../../tests/support/selection_independent_fixture.hpp), [include/crown/runtime/session.hpp](../../../../../include/crown/runtime/session.hpp), [include/crown/runtime/reoptimization.hpp](../../../../../include/crown/runtime/reoptimization.hpp), [src/runtime/session.cpp](../../../../../src/runtime/session.cpp), [src/runtime/reoptimization.cpp](../../../../../src/runtime/reoptimization.cpp), [docs/reoptimization.md](../../../../reoptimization.md) |

## B0017

[Lines 184–204](../../../../../tests/unit/reoptimization_session_test.cpp#L184); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void window(const PhysicalPlan& plan,const planner::CandidateSnapshot& family,WindowFifoPolicy fifo) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Verify catch-up across duplicate window labels and a queued multi-substep watermark. |
| inputs / outputs | Creates width-10 windows on tables 0–2; applies command labels 1–4 to candidate/reference, confirms duplicate label creates no physical epoch, queues watermark sequence 5 to candidate and fully applies it to reference, then pauses and verifies. |
| invariants | At the boundary snapshot epoch is 3, both epochs are 6, three physical records are staged/replayed, command sequence is 5, queue and active command are empty, and output/controller/results match. Exercises global and per-relation FIFO policies. |
| ownership | Each session owns its window controller and queue; outputs and result Relations are test-owned copies. |
| failure | Partial watermark, fabricated metadata epoch, differing FIFO state, or mismatch with reference fails. |
| cost | Processes four labeled commands, a watermark expanded to physical work, one barrier and up to 100-step command helpers; counts describe this fixture only and do not bound CPU time. |
| Design | [tests/unit/reoptimization_session_test.cpp](../../../../../tests/unit/reoptimization_session_test.cpp), [tests/support/selection_independent_fixture.hpp](../../../../../tests/support/selection_independent_fixture.hpp), [include/crown/runtime/session.hpp](../../../../../include/crown/runtime/session.hpp), [include/crown/runtime/reoptimization.hpp](../../../../../include/crown/runtime/reoptimization.hpp), [src/runtime/session.cpp](../../../../../src/runtime/session.cpp), [src/runtime/reoptimization.cpp](../../../../../src/runtime/reoptimization.cpp), [docs/reoptimization.md](../../../../reoptimization.md) |

## B0018

[Lines 205–230](../../../../../tests/unit/reoptimization_session_test.cpp#L205); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void durable(const PhysicalPlan& plan,const planner::CandidateSnapshot& family,const Database& initial) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Prove candidate preparation drains every old-owner epoch through an attached durable sink without selecting a new generation. |
| inputs / outputs | Enables a generation root and local sink; queues a no-op insert at sequence 1 and a delete at 2; repeatedly advances by one and delivers output epochs through the sink; cancels and restores. |
| invariants | Requires empty epoch 1 and both deliveries at generation 1, verified sink/journal sequence 2, no pending journal input, unchanged root bytes/header, and recovered committed/progress/sink sequence 2. Candidate preparation alone leaves durable selection unchanged. |
| ownership | The session owns generation and local-sink handles; the restored session is produced by sink-aware generation recovery. Header/root byte strings are test snapshots. |
| failure | Skipped/duplicate delivery, selected-root/header change, failed verification, or failed recovery fails. |
| cost | Up to 10,000 one-quantum advances, two durable deliveries, file reads, then recovery; filesystem and sink work is explicit, not a latency/CPU guarantee. |
| Design | [tests/unit/reoptimization_session_test.cpp](../../../../../tests/unit/reoptimization_session_test.cpp), [tests/support/selection_independent_fixture.hpp](../../../../../tests/support/selection_independent_fixture.hpp), [include/crown/runtime/session.hpp](../../../../../include/crown/runtime/session.hpp), [include/crown/runtime/reoptimization.hpp](../../../../../include/crown/runtime/reoptimization.hpp), [src/runtime/session.cpp](../../../../../src/runtime/session.cpp), [src/runtime/reoptimization.cpp](../../../../../src/runtime/reoptimization.cpp), [docs/reoptimization.md](../../../../reoptimization.md), [docs/session-journal.md](../../../../session-journal.md) |

## B0019

[Lines 231–231](../../../../../tests/unit/reoptimization_session_test.cpp#L231); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L231-L231:sha256:533f16bca7d58f44b3103b92e3485d22cfbb34bbad5ea3f3fa3b5a9dcb24ec89
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Close the recorded declaration scopes in reoptimization_session_test.cpp: namespace (anonymous). |
| inputs / outputs | Preceding namespace, type or initializer declarations in; completed lexical boundary out. |
| invariants | Brace-opening context is recorded in root-scope-context-v1.json. These are declaration/initializer boundaries, not an independent update, validation or recovery operation. |
| ownership | Enclosing objects and borrowed fields keep their declared ownership. This punctuation creates no new owner. |
| failure | Malformed scope syntax is a compile error. Any initializer/constructor failure belongs to the enclosing object declaration. |
| cost | No separate loop, guard or engine call is introduced by the delimiter; enclosing initialization and object lifetime still have their actual costs. |
| Design | [tests/unit/reoptimization_session_test.cpp](../../../../../tests/unit/reoptimization_session_test.cpp), [docs/reoptimization.md](../../../../reoptimization.md), [docs/code_review.md](../../../../code_review.md) |

## B0020

[Lines 232–253](../../../../../tests/unit/reoptimization_session_test.cpp#L232); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
int main(int argc,char** argv) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Run the candidate-preparation fixtures for the two backends and report the source-derived ordinary-case count. |
| inputs / outputs | Requires one SOURCE argument, constructs the Boolean fixture, and loops over indexed/plain backend, maintenance/delta, and direct/insertion-replay build; each combination runs CQ and SQL ordinary cases. Also invokes failures, ledger, stream, projected, two FIFO windows, and durable cases. |
| invariants | The printed ordinary counter is 16 = 2 backends × 2 modes × 2 build methods × 2 query forms. Extra helpers are not included in that counter. This file verifies/cancels candidates but does not publish a replacement plan. |
| ownership | Fixture, sessions, plans, and temporary input are scoped to each invocation; all handles are destroyed through normal RAII or explicit cancel. |
| failure | Argument/fixture/check failures are caught as std::exception, printed, and return 1; otherwise return 0. |
| cost | The count is derived from source loops, not a native execution result. Each case does substantial fixture setup with bounded barrier-call loops; helper epoch-finish loops have no iteration guard and logical migration work; barrier limits are call counts, not CPU limits. |
| Design | [tests/unit/reoptimization_session_test.cpp](../../../../../tests/unit/reoptimization_session_test.cpp), [tests/support/selection_independent_fixture.hpp](../../../../../tests/support/selection_independent_fixture.hpp), [include/crown/runtime/session.hpp](../../../../../include/crown/runtime/session.hpp), [include/crown/runtime/reoptimization.hpp](../../../../../include/crown/runtime/reoptimization.hpp), [src/runtime/session.cpp](../../../../../src/runtime/session.cpp), [src/runtime/reoptimization.cpp](../../../../../src/runtime/reoptimization.cpp), [docs/reoptimization.md](../../../../reoptimization.md), [tests/candidates/queries/boolean_rst.cq.json](../../../../../tests/candidates/queries/boolean_rst.cq.json), [tests/candidates/trees/boolean_rst_native_s_root.tree.json](../../../../../tests/candidates/trees/boolean_rst_native_s_root.tree.json), [tests/candidates/trees/boolean_rst_generalized_x_root.tree.json](../../../../../tests/candidates/trees/boolean_rst_generalized_x_root.tree.json), [tests/candidates/trees/boolean_rst_generalized_y_root.tree.json](../../../../../tests/candidates/trees/boolean_rst_generalized_y_root.tree.json), [include/crown/frontend/admission.hpp](../../../../../include/crown/frontend/admission.hpp), [docs/session-journal.md](../../../../session-journal.md), [CMakeLists.txt](../../../../../CMakeLists.txt) |
