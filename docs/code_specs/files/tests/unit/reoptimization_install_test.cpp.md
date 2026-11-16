# `tests/unit/reoptimization_install_test.cpp` — block usage map

[Source](../../../../../tests/unit/reoptimization_install_test.cpp) · [Source index](../../../README.md) · [Subsystem contracts](../../../subsystem_contracts.md) · [Reviewed primitives](../../../primitives.md)

Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection.

Snapshot SHA-256: `eee6ec9dd579545c11acf5c3697a78526eff9ce7a6b74d881834014b6415b461`. 247 lines partitioned into 19 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [tests](../../../subsystem_contracts.md#tests). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/code_review.md](../../../../code_review.md), [docs/reference_fuzz.md](../../../../reference_fuzz.md), [docs/task_ledger.md](../../../../task_ledger.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–14](../../../../../tests/unit/reoptimization_install_test.cpp#L1) | Imports dependencies; declares namespace scope; declares aliases; declares values/defaults or compile-time conditions. |  · [reviewed contract](#b0001) |
| [B0002 · 15–17](../../../../../tests/unit/reoptimization_install_test.cpp#L15) | Callable definition: reoptimization::Options migration_options() | calls ; returns value · [reviewed contract](#b0002) |
| [B0003 · 18–20](../../../../../tests/unit/reoptimization_install_test.cpp#L18) | Callable definition: SessionOptions session_options(DeltaMode mode) | calls ; returns value · [reviewed contract](#b0003) |
| [B0004 · 21–24](../../../../../tests/unit/reoptimization_install_test.cpp#L21) | Callable definition: void enqueue(QuerySession& session,io::InputItem item) | calls push_back, std::move, batch, check; guard check(session.enqueue(batch)==io::Admission::accepted && batch.empty(),"install input admission fai…; growth push_back · [reviewed contract](#b0004) |
| [B0005 · 25–35](../../../../../tests/unit/reoptimization_install_test.cpp#L25) | Callable definition: void collect(QuerySession& session,Outputs& outputs,bool sink) | calls status, local_sink_state, deliver_local_epoch, read_local_epoch; guard check(outputs.emplace(delivery.sequence,local_sink_test::output(epoch)).second,"install repeated a …; growth emplace; 1 loop sites · [reviewed contract](#b0005) |
| [B0006 · 36–38](../../../../../tests/unit/reoptimization_install_test.cpp#L36) | Callable definition: void finish(QuerySession& session,Outputs& outputs,bool sink=false) | calls step, commit, collect; 1 loop sites · [reviewed contract](#b0006) |
| [B0007 · 39–42](../../../../../tests/unit/reoptimization_install_test.cpp#L39) | Callable definition: void apply(QuerySession& session,const PhysicalSetUpdate& update,Outputs& outputs,bool sink=false) | calls enqueue, check, begin_next, finish; guard check(session.begin_next(),"install event missing");finish(session,outputs,sink); · [reviewed contract](#b0007) |
| [B0008 · 43–45](../../../../../tests/unit/reoptimization_install_test.cpp#L43) | Callable definition: Relation results(QuerySession& session) | calls snapshot, insert, storage::export_row, values; returns value; growth insert; 1 loop sites · [reviewed contract](#b0008) |
| [B0009 · 46–53](../../../../../tests/unit/reoptimization_install_test.cpp#L46) | Callable definition: reoptimization::Status verify(QuerySession& session,Outputs& outputs,bool sink=false) | calls request_reoptimization_barrier, advance_reoptimization, collect, std::runtime_error; returns value; 1 loop sites · [reviewed contract](#b0009) |
| [B0010 · 54–57](../../../../../tests/unit/reoptimization_install_test.cpp#L54) | Callable definition: template&lt;class Function&gt; void binding_rejected(Function&& function) | calls function, std::runtime_error · [reviewed contract](#b0010) |
| [B0011 · 58–70](../../../../../tests/unit/reoptimization_install_test.cpp#L58) | Callable definition: QuerySession::Owner recover(const PhysicalPlan& original,const std::string& root,const std::string& sink={}) | calls QuerySession::lock_generation_recovery, CompiledProgram::standalone, generation_test::recovery_options, check; guard check(locked-&gt;has_plan() && !locked-&gt;compiler_artifact().empty(),"selected descriptor/compiler inpu…; returns session; source comment (unverified): // Full compiler decode happens explicitly while the actual root lock remains owned. · [reviewed contract](#b0011) |
| [B0012 · 71–137](../../../../../tests/unit/reoptimization_install_test.cpp#L71) | Callable definition: void ordinary(const PhysicalPlan& original,const PhysicalPlan& target,const planner::CandidateSnapshot& family, std::size_t membe… | calls file, QuerySession::create_typed, session_options, start; guard session-&gt;pause();check(verify(*session,actual,sink).phase==reoptimization::Phase::verified,"install…; growth insert; 1 loop sites; source comment (unverified): // The original compiler artifact is independently admitted, rather than exported from execution state. · [reviewed contract](#b0012) |
| [B0013 · 138–155](../../../../../tests/unit/reoptimization_install_test.cpp#L138) | Callable definition: void promotion(const PhysicalPlan& original,const PhysicalPlan& target,const planner::CandidateSnapshot& family,std::size_t membe… | calls file, QuerySession::create_typed, session_options, start; guard check(session-&gt;generation_state().selected.generation==2 && session-&gt;generation_state().selected.fi…; growth insert · [reviewed contract](#b0013) |
| [B0014 · 156–162](../../../../../tests/unit/reoptimization_install_test.cpp#L156) | Callable definition: void window_command(QuerySession& session,io::WindowCommand command,Outputs& output) | calls enqueue, std::move, progress, check; guard check(session.begin_next(),"install window command missing");finish(session,output);; 1 loop sites · [reviewed contract](#b0014) |
| [B0015 · 163–189](../../../../../tests/unit/reoptimization_install_test.cpp#L163) | Callable definition: void window(const PhysicalPlan& original,const PhysicalPlan& target,const planner::CandidateSnapshot& family,WindowFifoPolicy fif… | calls file, QuerySession::create_windowed, session_options, start; guard check(session-&gt;begin_next(),"install watermark missing");session-&gt;pause();; 1 loop sites · [reviewed contract](#b0015) |
| [B0016 · 190–204](../../../../../tests/unit/reoptimization_install_test.cpp#L190) | Callable definition: void late_sink(const PhysicalPlan& original,const PhysicalPlan& target,const planner::CandidateSnapshot& family,const Database& i… | calls file, QuerySession::create_typed, session_options, start; guard check(verify(*session,output).phase==reoptimization::Phase::verified,"late-sink candidate failed");; source comment (unverified): // Recover once before any metadata selection persists the new sink origin. · [reviewed contract](#b0016) |
| [B0017 · 205–216](../../../../../tests/unit/reoptimization_install_test.cpp#L205) | Callable definition: void ended_input(const PhysicalPlan& original,const PhysicalPlan& target,const planner::CandidateSnapshot& family,const Database&… | calls file, QuerySession::create, session_options, QuerySession::create_typed; guard check(session-&gt;begin_next_result()==SessionBegin::end,"EOF fixture did not reach input end");; growth make_unique · [reviewed contract](#b0017) |
| [B0018 · 217–217](../../../../../tests/unit/reoptimization_install_test.cpp#L217) | Closes surrounding scope/type. | source comment (unverified): // namespace · [reviewed contract](#b0018) |
| [B0019 · 218–247](../../../../../tests/unit/reoptimization_install_test.cpp#L218) | Callable definition: int main(int argc,char** argv) | calls check, c05_independent::boolean_fixture, s04_runtime::options, c05_independent::lower; guard check(argc==2,"usage: reoptimization_install SOURCE");const auto fixture=c05_independent::boolean_f…; returns 0; 1; 8 loop sites · [reviewed contract](#b0019) |

## B0001

[Lines 1–14](../../../../../tests/unit/reoptimization_install_test.cpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L1-L14:sha256:7083082d1f3b1af88d8fe296410be8a885496fef7d9aaef1ba25482cd0618563
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Prepare reoptimization_install_test.cpp: include "selection_independent_fixture.hpp", "indexed_runtime_fixture.hpp", "local_sink_fixture.hpp", "crown/frontend/admission.hpp", "crown/io/compiler_plan_artifact.hpp", "crown/runtime/session_reoptimization.hpp", &lt;iostream&gt;; bind local aliases/name imports. |
| inputs / outputs | Compiler-visible dependencies, names and the recorded declarations in; declarations available to the following fixture/CLI/example definitions out. |
| invariants | Declarations are scoped to this source/header and its selected ABI. Included code has its own effects; names and editable fixture values do not confer proof, admission or publication authority. |
| ownership | Aliases/includes do not create a query owner. Pointers/references/views are non-owning. Containers own their elements, which can themselves be borrowed pointers or numeric IDs. Only documented owning shared-control handles retain controls; IDs/slot-handle values do not independently keep an arena/runtime alive. |
| failure | Missing headers, ill-formed names/types, failed static assertions or active #error directives stop compilation. No runtime rejection/rollback mechanism is implemented by aliases or function prototypes. |
| cost | Preprocessing and type/constraint instantiation cost compilation. Alias/prototype syntax does not invoke the declared operation; any included definitions keep their own initialization effects. |
| Design | [tests/unit/reoptimization_install_test.cpp](../../../../../tests/unit/reoptimization_install_test.cpp), [docs/reoptimization.md](../../../../reoptimization.md), [docs/code_review.md](../../../../code_review.md) |

## B0002

[Lines 15–17](../../../../../tests/unit/reoptimization_install_test.cpp#L15); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
reoptimization::Options migration_options() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Supply the migration forecast used by installation scenarios. |
| inputs / outputs | Returns Options with caller forecast 1,000,000,000 ns/input versus 1 ns/input over UINT64_MAX future inputs. |
| invariants | The values are deliberately optimistic fixture inputs, not measured runtime speed. |
| ownership | Returns a value object; no owner/account retained. |
| failure | No helper-level failure branch. |
| cost | Fixed option assignments only; it does not time any native code. |
| Design | [tests/unit/reoptimization_install_test.cpp](../../../../../tests/unit/reoptimization_install_test.cpp), [tests/support/selection_independent_fixture.hpp](../../../../../tests/support/selection_independent_fixture.hpp), [tests/support/indexed_runtime_fixture.hpp](../../../../../tests/support/indexed_runtime_fixture.hpp), [tests/support/local_sink_fixture.hpp](../../../../../tests/support/local_sink_fixture.hpp), [tests/support/session_file_fixture.hpp](../../../../../tests/support/session_file_fixture.hpp), [include/crown/runtime/session.hpp](../../../../../include/crown/runtime/session.hpp), [include/crown/runtime/reoptimization.hpp](../../../../../include/crown/runtime/reoptimization.hpp), [src/runtime/session.cpp](../../../../../src/runtime/session.cpp), [src/runtime/reoptimization.cpp](../../../../../src/runtime/reoptimization.cpp), [src/recovery/generation.cpp](../../../../../src/recovery/generation.cpp), [src/io/compiler_plan_artifact.cpp](../../../../../src/io/compiler_plan_artifact.cpp), [docs/reoptimization.md](../../../../reoptimization.md), [docs/generations.md](../../../../generations.md), [docs/history-retirement.md](../../../../history-retirement.md), [docs/local-sink.md](../../../../local-sink.md) |

## B0003

[Lines 18–20](../../../../../tests/unit/reoptimization_install_test.cpp#L18); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
SessionOptions session_options(DeltaMode mode) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Set the installation session mode and 64 MiB support memory limit. |
| inputs / outputs | Returns SessionOptions for the supplied delta mode and support memory grant. |
| invariants | This is an account limit for test sessions, not a process-wide heap/RSS or CPU limit. |
| ownership | Returned by value for session construction. |
| failure | No helper-level failure path. |
| cost | Fixed assignments; actual session allocations happen later. |
| Design | [tests/unit/reoptimization_install_test.cpp](../../../../../tests/unit/reoptimization_install_test.cpp), [tests/support/selection_independent_fixture.hpp](../../../../../tests/support/selection_independent_fixture.hpp), [tests/support/indexed_runtime_fixture.hpp](../../../../../tests/support/indexed_runtime_fixture.hpp), [tests/support/local_sink_fixture.hpp](../../../../../tests/support/local_sink_fixture.hpp), [tests/support/session_file_fixture.hpp](../../../../../tests/support/session_file_fixture.hpp), [include/crown/runtime/session.hpp](../../../../../include/crown/runtime/session.hpp), [include/crown/runtime/reoptimization.hpp](../../../../../include/crown/runtime/reoptimization.hpp), [src/runtime/session.cpp](../../../../../src/runtime/session.cpp), [src/runtime/reoptimization.cpp](../../../../../src/runtime/reoptimization.cpp), [src/recovery/generation.cpp](../../../../../src/recovery/generation.cpp), [src/io/compiler_plan_artifact.cpp](../../../../../src/io/compiler_plan_artifact.cpp), [docs/reoptimization.md](../../../../reoptimization.md), [docs/generations.md](../../../../generations.md), [docs/history-retirement.md](../../../../history-retirement.md), [docs/local-sink.md](../../../../local-sink.md) |

## B0004

[Lines 21–24](../../../../../tests/unit/reoptimization_install_test.cpp#L21); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void enqueue(QuerySession& session,io::InputItem item) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Transfer one test input item into a typed session queue. |
| inputs / outputs | Moves one InputItem through a local vector and TransportBatch and asserts accepted admission plus an emptied batch. |
| invariants | The fixture assumes typed admission succeeds; rejected input fails the test. |
| ownership | Queue owns accepted input after transfer; local vector/batch are short-lived. |
| failure | Admission or assertion failure propagates. |
| cost | One item/vector/batch construction and one enqueue; queue storage work depends on input shape. |
| Design | [tests/unit/reoptimization_install_test.cpp](../../../../../tests/unit/reoptimization_install_test.cpp), [tests/support/selection_independent_fixture.hpp](../../../../../tests/support/selection_independent_fixture.hpp), [tests/support/indexed_runtime_fixture.hpp](../../../../../tests/support/indexed_runtime_fixture.hpp), [tests/support/local_sink_fixture.hpp](../../../../../tests/support/local_sink_fixture.hpp), [tests/support/session_file_fixture.hpp](../../../../../tests/support/session_file_fixture.hpp), [include/crown/runtime/session.hpp](../../../../../include/crown/runtime/session.hpp), [include/crown/runtime/reoptimization.hpp](../../../../../include/crown/runtime/reoptimization.hpp), [src/runtime/session.cpp](../../../../../src/runtime/session.cpp), [src/runtime/reoptimization.cpp](../../../../../src/runtime/reoptimization.cpp), [src/recovery/generation.cpp](../../../../../src/recovery/generation.cpp), [src/io/compiler_plan_artifact.cpp](../../../../../src/io/compiler_plan_artifact.cpp), [docs/reoptimization.md](../../../../reoptimization.md), [docs/generations.md](../../../../generations.md), [docs/history-retirement.md](../../../../history-retirement.md), [docs/local-sink.md](../../../../local-sink.md) |

## B0005

[Lines 25–35](../../../../../tests/unit/reoptimization_install_test.cpp#L25); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void collect(QuerySession& session,Outputs& outputs,bool sink) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Collect pending test output either from the local sink or the session cursor. |
| inputs / outputs | Skips pending sequences/commands; in sink mode skips already verified sequence or delivers and reads one epoch; otherwise drains next_output into an Outputs map. |
| invariants | Checks that each delivery/output operation-row pair is unique. Local sink delivery and result cursor are distinct paths. |
| ownership | Session owns sink/cursor; test map/set owns copied output rows. |
| failure | Duplicate output or API/delivery failure propagates. |
| cost | Status checks plus per-row set/map insertions; sink mode additionally performs one durable delivery/read when needed. |
| Design | [tests/unit/reoptimization_install_test.cpp](../../../../../tests/unit/reoptimization_install_test.cpp), [tests/support/selection_independent_fixture.hpp](../../../../../tests/support/selection_independent_fixture.hpp), [tests/support/indexed_runtime_fixture.hpp](../../../../../tests/support/indexed_runtime_fixture.hpp), [tests/support/local_sink_fixture.hpp](../../../../../tests/support/local_sink_fixture.hpp), [tests/support/session_file_fixture.hpp](../../../../../tests/support/session_file_fixture.hpp), [include/crown/runtime/session.hpp](../../../../../include/crown/runtime/session.hpp), [include/crown/runtime/reoptimization.hpp](../../../../../include/crown/runtime/reoptimization.hpp), [src/runtime/session.cpp](../../../../../src/runtime/session.cpp), [src/runtime/reoptimization.cpp](../../../../../src/runtime/reoptimization.cpp), [src/recovery/generation.cpp](../../../../../src/recovery/generation.cpp), [src/io/compiler_plan_artifact.cpp](../../../../../src/io/compiler_plan_artifact.cpp), [docs/reoptimization.md](../../../../reoptimization.md), [docs/generations.md](../../../../generations.md), [docs/history-retirement.md](../../../../history-retirement.md), [docs/local-sink.md](../../../../local-sink.md) |

## B0006

[Lines 36–38](../../../../../tests/unit/reoptimization_install_test.cpp#L36); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void finish(QuerySession& session,Outputs& outputs,bool sink=false) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Complete a pending epoch and collect it using the selected delivery mode. |
| inputs / outputs | Steps until prepared, commits, then calls collect with sink default false. |
| invariants | Caller must have a valid pending event; the step loop has no finite iteration guard here. |
| ownership | Session owns runtime state; Outputs owns copies of observable rows. |
| failure | Step/commit/output failures propagate. |
| cost | As many delta steps as the epoch needs, one commit, and output collection; not a CPU bound. |
| Design | [tests/unit/reoptimization_install_test.cpp](../../../../../tests/unit/reoptimization_install_test.cpp), [tests/support/selection_independent_fixture.hpp](../../../../../tests/support/selection_independent_fixture.hpp), [tests/support/indexed_runtime_fixture.hpp](../../../../../tests/support/indexed_runtime_fixture.hpp), [tests/support/local_sink_fixture.hpp](../../../../../tests/support/local_sink_fixture.hpp), [tests/support/session_file_fixture.hpp](../../../../../tests/support/session_file_fixture.hpp), [include/crown/runtime/session.hpp](../../../../../include/crown/runtime/session.hpp), [include/crown/runtime/reoptimization.hpp](../../../../../include/crown/runtime/reoptimization.hpp), [src/runtime/session.cpp](../../../../../src/runtime/session.cpp), [src/runtime/reoptimization.cpp](../../../../../src/runtime/reoptimization.cpp), [src/recovery/generation.cpp](../../../../../src/recovery/generation.cpp), [src/io/compiler_plan_artifact.cpp](../../../../../src/io/compiler_plan_artifact.cpp), [docs/reoptimization.md](../../../../reoptimization.md), [docs/generations.md](../../../../generations.md), [docs/history-retirement.md](../../../../history-retirement.md), [docs/local-sink.md](../../../../local-sink.md) |

## B0007

[Lines 39–42](../../../../../tests/unit/reoptimization_install_test.cpp#L39); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void apply(QuerySession& session,const PhysicalSetUpdate& update,Outputs& outputs,bool sink=false) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Apply an update with a feed source position to the session and collect its output. |
| inputs / outputs | Enqueues sequence at feed offset sequence*10, requires begin_next, then calls finish. |
| invariants | This helper expects accepted input and a startable event; it does not test admission failure. |
| ownership | Input is moved into the session queue; output is copied into Outputs. |
| failure | Admission, begin, finish, or collection failure propagates. |
| cost | One queue admission plus one unbounded per-epoch step loop and output work. |
| Design | [tests/unit/reoptimization_install_test.cpp](../../../../../tests/unit/reoptimization_install_test.cpp), [tests/support/selection_independent_fixture.hpp](../../../../../tests/support/selection_independent_fixture.hpp), [tests/support/indexed_runtime_fixture.hpp](../../../../../tests/support/indexed_runtime_fixture.hpp), [tests/support/local_sink_fixture.hpp](../../../../../tests/support/local_sink_fixture.hpp), [tests/support/session_file_fixture.hpp](../../../../../tests/support/session_file_fixture.hpp), [include/crown/runtime/session.hpp](../../../../../include/crown/runtime/session.hpp), [include/crown/runtime/reoptimization.hpp](../../../../../include/crown/runtime/reoptimization.hpp), [src/runtime/session.cpp](../../../../../src/runtime/session.cpp), [src/runtime/reoptimization.cpp](../../../../../src/runtime/reoptimization.cpp), [src/recovery/generation.cpp](../../../../../src/recovery/generation.cpp), [src/io/compiler_plan_artifact.cpp](../../../../../src/io/compiler_plan_artifact.cpp), [docs/reoptimization.md](../../../../reoptimization.md), [docs/generations.md](../../../../generations.md), [docs/history-retirement.md](../../../../history-retirement.md), [docs/local-sink.md](../../../../local-sink.md) |

## B0008

[Lines 43–45](../../../../../tests/unit/reoptimization_install_test.cpp#L43); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Relation results(QuerySession& session) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Copy current snapshot rows into a Relation for reference comparison. |
| inputs / outputs | Calls session.snapshot and exports/inserts each row. |
| invariants | Used as a copied test oracle, not a retained session cursor. |
| ownership | The returned Relation owns copied row values. |
| failure | Snapshot/export/allocation errors propagate. |
| cost | Visits and copies all rows in the snapshot; container growth follows observed result size. |
| Design | [tests/unit/reoptimization_install_test.cpp](../../../../../tests/unit/reoptimization_install_test.cpp), [tests/support/selection_independent_fixture.hpp](../../../../../tests/support/selection_independent_fixture.hpp), [tests/support/indexed_runtime_fixture.hpp](../../../../../tests/support/indexed_runtime_fixture.hpp), [tests/support/local_sink_fixture.hpp](../../../../../tests/support/local_sink_fixture.hpp), [tests/support/session_file_fixture.hpp](../../../../../tests/support/session_file_fixture.hpp), [include/crown/runtime/session.hpp](../../../../../include/crown/runtime/session.hpp), [include/crown/runtime/reoptimization.hpp](../../../../../include/crown/runtime/reoptimization.hpp), [src/runtime/session.cpp](../../../../../src/runtime/session.cpp), [src/runtime/reoptimization.cpp](../../../../../src/runtime/reoptimization.cpp), [src/recovery/generation.cpp](../../../../../src/recovery/generation.cpp), [src/io/compiler_plan_artifact.cpp](../../../../../src/io/compiler_plan_artifact.cpp), [docs/reoptimization.md](../../../../reoptimization.md), [docs/generations.md](../../../../generations.md), [docs/history-retirement.md](../../../../history-retirement.md), [docs/local-sink.md](../../../../local-sink.md) |

## B0009

[Lines 46–53](../../../../../tests/unit/reoptimization_install_test.cpp#L46); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
reoptimization::Status verify(QuerySession& session,Outputs& outputs,bool sink=false) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Request and drive the installation barrier until it is verified or terminally rejected/failed. |
| inputs / outputs | Requests barrier, then calls advance_reoptimization(1) and collect up to 10,000 times. |
| invariants | Returns only verified, rejected, or failed; exhausting the loop throws. Unit quantum limits migration progress per call, not CPU duration. |
| ownership | Session retains candidate and target until publication/cancel; Outputs is test-owned. |
| failure | Nonterminal status after 10,000 iterations throws runtime_error; API/delivery failures propagate. |
| cost | At most 10,000 advancement/collection iterations; each can perform source drain, replay, compare, and sink work. |
| Design | [tests/unit/reoptimization_install_test.cpp](../../../../../tests/unit/reoptimization_install_test.cpp), [tests/support/selection_independent_fixture.hpp](../../../../../tests/support/selection_independent_fixture.hpp), [tests/support/indexed_runtime_fixture.hpp](../../../../../tests/support/indexed_runtime_fixture.hpp), [tests/support/local_sink_fixture.hpp](../../../../../tests/support/local_sink_fixture.hpp), [tests/support/session_file_fixture.hpp](../../../../../tests/support/session_file_fixture.hpp), [include/crown/runtime/session.hpp](../../../../../include/crown/runtime/session.hpp), [include/crown/runtime/reoptimization.hpp](../../../../../include/crown/runtime/reoptimization.hpp), [src/runtime/session.cpp](../../../../../src/runtime/session.cpp), [src/runtime/reoptimization.cpp](../../../../../src/runtime/reoptimization.cpp), [src/recovery/generation.cpp](../../../../../src/recovery/generation.cpp), [src/io/compiler_plan_artifact.cpp](../../../../../src/io/compiler_plan_artifact.cpp), [docs/reoptimization.md](../../../../reoptimization.md), [docs/generations.md](../../../../generations.md), [docs/history-retirement.md](../../../../history-retirement.md), [docs/local-sink.md](../../../../local-sink.md) |

## B0010

[Lines 54–57](../../../../../tests/unit/reoptimization_install_test.cpp#L54); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
template<class Function> void binding_rejected(Function&& function) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Require a generation binding failure for an intentionally wrong recovery/compiler call. |
| inputs / outputs | Invokes the forwarded callable and returns only when it throws recovery::GenerationFailure. |
| invariants | Only GenerationFailure is accepted; other exceptions propagate and success is treated as test failure. |
| ownership | Borrows the callable; no recovery owner is retained by the helper. |
| failure | Unexpected success throws runtime_error. |
| cost | One invocation and catch path; no runtime cost assertion. |
| Design | [tests/unit/reoptimization_install_test.cpp](../../../../../tests/unit/reoptimization_install_test.cpp), [tests/support/selection_independent_fixture.hpp](../../../../../tests/support/selection_independent_fixture.hpp), [tests/support/indexed_runtime_fixture.hpp](../../../../../tests/support/indexed_runtime_fixture.hpp), [tests/support/local_sink_fixture.hpp](../../../../../tests/support/local_sink_fixture.hpp), [tests/support/session_file_fixture.hpp](../../../../../tests/support/session_file_fixture.hpp), [include/crown/runtime/session.hpp](../../../../../include/crown/runtime/session.hpp), [include/crown/runtime/reoptimization.hpp](../../../../../include/crown/runtime/reoptimization.hpp), [src/runtime/session.cpp](../../../../../src/runtime/session.cpp), [src/runtime/reoptimization.cpp](../../../../../src/runtime/reoptimization.cpp), [src/recovery/generation.cpp](../../../../../src/recovery/generation.cpp), [src/io/compiler_plan_artifact.cpp](../../../../../src/io/compiler_plan_artifact.cpp), [docs/reoptimization.md](../../../../reoptimization.md), [docs/generations.md](../../../../generations.md), [docs/history-retirement.md](../../../../history-retirement.md), [docs/local-sink.md](../../../../local-sink.md) |

## B0011

[Lines 58–70](../../../../../tests/unit/reoptimization_install_test.cpp#L58); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
QuerySession::Owner recover(const PhysicalPlan& original,const std::string& root,const std::string& sink={}) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Recover a selected generation while preserving the original receiving account and root lock through compiler decode. |
| inputs / outputs | Locks with expected original compiled plan; requires selected descriptor/compiler bytes; replays bytes into a separate 32 MiB compiler account; consumes the locked object through selected-generation restore, optionally with local sink. |
| invariants | Asserts restored account owner equals the lock’s receiving account and differs from compiler account. Descriptor-aware recovery is required; caller-selected legacy restore is not used. |
| ownership | Move-only locked recovery owns the root lock and borrowed compiler bytes until restore consumes it; returned session owns the moved managed generation. |
| failure | Missing plan/artifact, decode, binding, or restore failure propagates. |
| cost | Reads/validates descriptor and compiler bytes, decodes in a separate account, then reconstructs/replays native state; file, hash, decode, and account work depend on artifact size. |
| Design | [tests/unit/reoptimization_install_test.cpp](../../../../../tests/unit/reoptimization_install_test.cpp), [tests/support/selection_independent_fixture.hpp](../../../../../tests/support/selection_independent_fixture.hpp), [tests/support/indexed_runtime_fixture.hpp](../../../../../tests/support/indexed_runtime_fixture.hpp), [tests/support/local_sink_fixture.hpp](../../../../../tests/support/local_sink_fixture.hpp), [tests/support/session_file_fixture.hpp](../../../../../tests/support/session_file_fixture.hpp), [include/crown/runtime/session.hpp](../../../../../include/crown/runtime/session.hpp), [include/crown/runtime/reoptimization.hpp](../../../../../include/crown/runtime/reoptimization.hpp), [src/runtime/session.cpp](../../../../../src/runtime/session.cpp), [src/runtime/reoptimization.cpp](../../../../../src/runtime/reoptimization.cpp), [src/recovery/generation.cpp](../../../../../src/recovery/generation.cpp), [src/io/compiler_plan_artifact.cpp](../../../../../src/io/compiler_plan_artifact.cpp), [docs/reoptimization.md](../../../../reoptimization.md), [docs/generations.md](../../../../generations.md), [docs/history-retirement.md](../../../../history-retirement.md), [docs/local-sink.md](../../../../local-sink.md), [include/crown/io/compiler_plan_artifact.hpp](../../../../../include/crown/io/compiler_plan_artifact.hpp) |

## B0012

[Lines 71–137](../../../../../tests/unit/reoptimization_install_test.cpp#L71); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void ordinary(const PhysicalPlan& original,const PhysicalPlan& target,const planner::CandidateSnapshot& family,
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Exercise real plan publication, owner replacement, recovery, rotation, hysteresis, and a repeated switch against a reference session. |
| inputs / outputs | For each backend/mode/sink: applies sequence 1 no-op, queues 2–4, pauses, verifies, publishes prepared artifact, checks results/output/progress and owner/account, continues at 5, rotates to 3, recovers selected plan, continues at 6, then tests hysteresis and a second switch. |
| invariants | Checks immutable generation-1 rollback pair; selection generation 2 at physical sequence 4; switch epoch 4 remains through generation-3 rotation at sequence 5. Completion reports compiler preparation cost equal to the artifact statistic, positive native preparation/publication/cleanup durations, and complete timing fields. Sink origin/empty epoch and workload configuration are preserved when enabled. Hysteresis rejects a too-early switch, then zero minimum gap permits retry. |
| ownership | The current QuerySession facade stays at same original account while its native runtime owner changes; compiler artifact lives in separate account. Old runtime remains until durable selection/install in implementation. Recovery consumes the root lock. |
| failure | Wrong artifact/source or legacy recovery binding must reject; any changed output/result, frontiers, owner, historical file, or unrecoverable selected plan fails. |
| cost | Commits/queues four updates, barrier drains and compares, prepares artifact, writes descriptor/checkpoint/WAL/root, replaces runtime, rotates, optionally retires, recovers, and performs a second migration. These are fixture operations, not timing guarantees. |
| Design | [tests/unit/reoptimization_install_test.cpp](../../../../../tests/unit/reoptimization_install_test.cpp), [tests/support/selection_independent_fixture.hpp](../../../../../tests/support/selection_independent_fixture.hpp), [tests/support/indexed_runtime_fixture.hpp](../../../../../tests/support/indexed_runtime_fixture.hpp), [tests/support/local_sink_fixture.hpp](../../../../../tests/support/local_sink_fixture.hpp), [tests/support/session_file_fixture.hpp](../../../../../tests/support/session_file_fixture.hpp), [include/crown/runtime/session.hpp](../../../../../include/crown/runtime/session.hpp), [include/crown/runtime/reoptimization.hpp](../../../../../include/crown/runtime/reoptimization.hpp), [src/runtime/session.cpp](../../../../../src/runtime/session.cpp), [src/runtime/reoptimization.cpp](../../../../../src/runtime/reoptimization.cpp), [src/recovery/generation.cpp](../../../../../src/recovery/generation.cpp), [src/io/compiler_plan_artifact.cpp](../../../../../src/io/compiler_plan_artifact.cpp), [docs/reoptimization.md](../../../../reoptimization.md), [docs/generations.md](../../../../generations.md), [docs/history-retirement.md](../../../../history-retirement.md), [docs/local-sink.md](../../../../local-sink.md), [include/crown/io/compiler_plan_artifact.hpp](../../../../../include/crown/io/compiler_plan_artifact.hpp), [docs/session-journal.md](../../../../session-journal.md) |

## B0013

[Lines 138–155](../../../../../tests/unit/reoptimization_install_test.cpp#L138); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void promotion(const PhysicalPlan& original,const PhysicalPlan& target,const planner::CandidateSnapshot& family,std::size_t member,const Database& initial) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Promote an existing journal into a managed generation root, then switch and recover a new plan. |
| inputs / outputs | Creates checkpoint/journal/local sink, commits one duplicate insert/no-op, saves unmanaged checkpoint/WAL and sink header, promotes, migrates, publishes and restores. |
| invariants | Promotion starts generation and retention floor at 2; original unmanaged files and sink identity remain unchanged; selected-plan recovery returns sequence 1 results. |
| ownership | Session takes generation ownership after promotion; old files remain external snapshots; artifact uses separate compiler account. |
| failure | Any changed old byte/header, wrong generation floor, failed verification/publication, or recovered result mismatch fails. |
| cost | Creates/checkpoints/journals one session, executes one update, promotion I/O, migration, artifact preparation, publication, and recovery. |
| Design | [tests/unit/reoptimization_install_test.cpp](../../../../../tests/unit/reoptimization_install_test.cpp), [tests/support/selection_independent_fixture.hpp](../../../../../tests/support/selection_independent_fixture.hpp), [tests/support/indexed_runtime_fixture.hpp](../../../../../tests/support/indexed_runtime_fixture.hpp), [tests/support/local_sink_fixture.hpp](../../../../../tests/support/local_sink_fixture.hpp), [tests/support/session_file_fixture.hpp](../../../../../tests/support/session_file_fixture.hpp), [include/crown/runtime/session.hpp](../../../../../include/crown/runtime/session.hpp), [include/crown/runtime/reoptimization.hpp](../../../../../include/crown/runtime/reoptimization.hpp), [src/runtime/session.cpp](../../../../../src/runtime/session.cpp), [src/runtime/reoptimization.cpp](../../../../../src/runtime/reoptimization.cpp), [src/recovery/generation.cpp](../../../../../src/recovery/generation.cpp), [src/io/compiler_plan_artifact.cpp](../../../../../src/io/compiler_plan_artifact.cpp), [docs/reoptimization.md](../../../../reoptimization.md), [docs/generations.md](../../../../generations.md), [docs/history-retirement.md](../../../../history-retirement.md), [docs/local-sink.md](../../../../local-sink.md), [include/crown/io/compiler_plan_artifact.hpp](../../../../../include/crown/io/compiler_plan_artifact.hpp), [docs/session-journal.md](../../../../session-journal.md) |

## B0014

[Lines 156–162](../../../../../tests/unit/reoptimization_install_test.cpp#L156); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void window_command(QuerySession& session,io::WindowCommand command,Outputs& output) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Process a window command up to the accepted sequence. |
| inputs / outputs | Moves command into queue and loops at most 100 begin_next/finish calls while progress is behind. |
| invariants | The iteration guard is 100; work inside each finish call is not time-bounded. |
| ownership | Command transfers to session; output is copied into caller map. |
| failure | Missing command or failure to reach sequence fails. |
| cost | At most 100 command starts and complete epoch work, plus output collection. |
| Design | [tests/unit/reoptimization_install_test.cpp](../../../../../tests/unit/reoptimization_install_test.cpp), [tests/support/selection_independent_fixture.hpp](../../../../../tests/support/selection_independent_fixture.hpp), [tests/support/indexed_runtime_fixture.hpp](../../../../../tests/support/indexed_runtime_fixture.hpp), [tests/support/local_sink_fixture.hpp](../../../../../tests/support/local_sink_fixture.hpp), [tests/support/session_file_fixture.hpp](../../../../../tests/support/session_file_fixture.hpp), [include/crown/runtime/session.hpp](../../../../../include/crown/runtime/session.hpp), [include/crown/runtime/reoptimization.hpp](../../../../../include/crown/runtime/reoptimization.hpp), [src/runtime/session.cpp](../../../../../src/runtime/session.cpp), [src/runtime/reoptimization.cpp](../../../../../src/runtime/reoptimization.cpp), [src/recovery/generation.cpp](../../../../../src/recovery/generation.cpp), [src/io/compiler_plan_artifact.cpp](../../../../../src/io/compiler_plan_artifact.cpp), [docs/reoptimization.md](../../../../reoptimization.md), [docs/generations.md](../../../../generations.md), [docs/history-retirement.md](../../../../history-retirement.md), [docs/local-sink.md](../../../../local-sink.md) |

## B0015

[Lines 163–189](../../../../../tests/unit/reoptimization_install_test.cpp#L163); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void window(const PhysicalPlan& original,const PhysicalPlan& target,const planner::CandidateSnapshot& family,WindowFifoPolicy fifo) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Install/recover across a queued watermark while preserving pause, window state, and exact output. |
| inputs / outputs | Applies four window inserts to session/reference; enqueues watermark 5, begins it, pauses, verifies, publishes, restores and processes command 6. Loops over global/per-relation FIFO. |
| invariants | After switch progress command sequence is 5 and physical committed sequence 6; watermark is complete, session paused, controller/output/results equal reference before and after restore. |
| ownership | Each session owns its controller; managed generation/descriptor owns checkpoint and selected plan. |
| failure | Partial watermark, changed pause/controller/output, or failed recovery/next command fails. |
| cost | Runs command loops (max 100 per command), drains watermark substeps, publishes and restores; work is driven by the window/controller implementation. |
| Design | [tests/unit/reoptimization_install_test.cpp](../../../../../tests/unit/reoptimization_install_test.cpp), [tests/support/selection_independent_fixture.hpp](../../../../../tests/support/selection_independent_fixture.hpp), [tests/support/indexed_runtime_fixture.hpp](../../../../../tests/support/indexed_runtime_fixture.hpp), [tests/support/local_sink_fixture.hpp](../../../../../tests/support/local_sink_fixture.hpp), [tests/support/session_file_fixture.hpp](../../../../../tests/support/session_file_fixture.hpp), [include/crown/runtime/session.hpp](../../../../../include/crown/runtime/session.hpp), [include/crown/runtime/reoptimization.hpp](../../../../../include/crown/runtime/reoptimization.hpp), [src/runtime/session.cpp](../../../../../src/runtime/session.cpp), [src/runtime/reoptimization.cpp](../../../../../src/runtime/reoptimization.cpp), [src/recovery/generation.cpp](../../../../../src/recovery/generation.cpp), [src/io/compiler_plan_artifact.cpp](../../../../../src/io/compiler_plan_artifact.cpp), [docs/reoptimization.md](../../../../reoptimization.md), [docs/generations.md](../../../../generations.md), [docs/history-retirement.md](../../../../history-retirement.md), [docs/local-sink.md](../../../../local-sink.md), [include/crown/io/compiler_plan_artifact.hpp](../../../../../include/crown/io/compiler_plan_artifact.hpp) |

## B0016

[Lines 190–204](../../../../../tests/unit/reoptimization_install_test.cpp#L190); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void late_sink(const PhysicalPlan& original,const PhysicalPlan& target,const planner::CandidateSnapshot& family,const Database& initial) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Persist a local-sink origin after a sink is attached following a plan switch. |
| inputs / outputs | Switches once at epoch 0 with no sink, attaches sink, recovers through it, rotates generation, checks descriptor sink origin and switch epoch, retires history, and recovers again. |
| invariants | This fixture has no committed data before attach; descriptor for generation 3 binds the new sink header and last_switch_epoch 0; retirement floor becomes 3. |
| ownership | Session/root owner and sink file are separate owned handles; origin is immutable descriptor metadata after selection. |
| failure | Failure to persist/recover exact origin/floor or mismatch to descriptor fails. |
| cost | Performs one empty-state verification/publication, recovery, sink creation, rotation, retirement, and another recovery; filesystem/hash work is fixture-local. |
| Design | [tests/unit/reoptimization_install_test.cpp](../../../../../tests/unit/reoptimization_install_test.cpp), [tests/support/selection_independent_fixture.hpp](../../../../../tests/support/selection_independent_fixture.hpp), [tests/support/indexed_runtime_fixture.hpp](../../../../../tests/support/indexed_runtime_fixture.hpp), [tests/support/local_sink_fixture.hpp](../../../../../tests/support/local_sink_fixture.hpp), [tests/support/session_file_fixture.hpp](../../../../../tests/support/session_file_fixture.hpp), [include/crown/runtime/session.hpp](../../../../../include/crown/runtime/session.hpp), [include/crown/runtime/reoptimization.hpp](../../../../../include/crown/runtime/reoptimization.hpp), [src/runtime/session.cpp](../../../../../src/runtime/session.cpp), [src/runtime/reoptimization.cpp](../../../../../src/runtime/reoptimization.cpp), [src/recovery/generation.cpp](../../../../../src/recovery/generation.cpp), [src/io/compiler_plan_artifact.cpp](../../../../../src/io/compiler_plan_artifact.cpp), [docs/reoptimization.md](../../../../reoptimization.md), [docs/generations.md](../../../../generations.md), [docs/history-retirement.md](../../../../history-retirement.md), [docs/local-sink.md](../../../../local-sink.md), [include/crown/io/compiler_plan_artifact.hpp](../../../../../include/crown/io/compiler_plan_artifact.hpp) |

## B0017

[Lines 205–216](../../../../../tests/unit/reoptimization_install_test.cpp#L205); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void ended_input(const PhysicalPlan& original,const PhysicalPlan& target,const planner::CandidateSnapshot& family,const Database& initial,bool stream) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Reject durable plan publication after stream EOF or typed input closure without changing the selected root. |
| inputs / outputs | For stream and typed variants, reaches end, snapshots root bytes, verifies candidate, prepares artifact, then attempts publication. |
| invariants | The test expects Error code reoptimization_input_state and byte-identical root; verification at EOF is not publication authority. |
| ownership | Session owns stream/queue and root lock; saved root bytes belong to test. |
| failure | If publication succeeds or reports another error, the test fails. |
| cost | Two variants each do bounded barrier work, artifact preparation, one rejected publication and root read; no durability or CPU theorem beyond this fixture. |
| Design | [tests/unit/reoptimization_install_test.cpp](../../../../../tests/unit/reoptimization_install_test.cpp), [tests/support/selection_independent_fixture.hpp](../../../../../tests/support/selection_independent_fixture.hpp), [tests/support/indexed_runtime_fixture.hpp](../../../../../tests/support/indexed_runtime_fixture.hpp), [tests/support/local_sink_fixture.hpp](../../../../../tests/support/local_sink_fixture.hpp), [tests/support/session_file_fixture.hpp](../../../../../tests/support/session_file_fixture.hpp), [include/crown/runtime/session.hpp](../../../../../include/crown/runtime/session.hpp), [include/crown/runtime/reoptimization.hpp](../../../../../include/crown/runtime/reoptimization.hpp), [src/runtime/session.cpp](../../../../../src/runtime/session.cpp), [src/runtime/reoptimization.cpp](../../../../../src/runtime/reoptimization.cpp), [src/recovery/generation.cpp](../../../../../src/recovery/generation.cpp), [src/io/compiler_plan_artifact.cpp](../../../../../src/io/compiler_plan_artifact.cpp), [docs/reoptimization.md](../../../../reoptimization.md), [docs/generations.md](../../../../generations.md), [docs/history-retirement.md](../../../../history-retirement.md), [docs/local-sink.md](../../../../local-sink.md), [include/crown/io/compiler_plan_artifact.hpp](../../../../../include/crown/io/compiler_plan_artifact.hpp) |

## B0018

[Lines 217–217](../../../../../tests/unit/reoptimization_install_test.cpp#L217); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L217-L217:sha256:533f16bca7d58f44b3103b92e3485d22cfbb34bbad5ea3f3fa3b5a9dcb24ec89
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Close the recorded declaration scopes in reoptimization_install_test.cpp: namespace (anonymous). |
| inputs / outputs | Preceding namespace, type or initializer declarations in; completed lexical boundary out. |
| invariants | Brace-opening context is recorded in root-scope-context-v1.json. These are declaration/initializer boundaries, not an independent update, validation or recovery operation. |
| ownership | Enclosing objects and borrowed fields keep their declared ownership. This punctuation creates no new owner. |
| failure | Malformed scope syntax is a compile error. Any initializer/constructor failure belongs to the enclosing object declaration. |
| cost | No separate loop, guard or engine call is introduced by the delimiter; enclosing initialization and object lifetime still have their actual costs. |
| Design | [tests/unit/reoptimization_install_test.cpp](../../../../../tests/unit/reoptimization_install_test.cpp), [docs/reoptimization.md](../../../../reoptimization.md), [docs/code_review.md](../../../../code_review.md) |

## B0019

[Lines 218–247](../../../../../tests/unit/reoptimization_install_test.cpp#L218); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
int main(int argc,char** argv) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Run the installation scenarios and report the source-derived ordinary-case count. |
| inputs / outputs | Requires SOURCE, creates Boolean fixture, loops two backends, CQ plus two SQL forms, two modes and two sink settings; ordinary increments cases for each. Also calls promotion, late-sink, typed/stream EOF, both window FIFOs. |
| invariants | The printed ordinary count is 24 = 2 backends × 3 query forms × 2 modes × 2 sink settings. Twelve other helper invocations are not included in that counter. |
| ownership | Fixture and each session/artifact/root/sink have scoped owners; helper return handles are consumed or destroyed. |
| failure | std::exception is printed and yields 1; successful source path returns 0. |
| cost | 24 is a source-loop derivation, not native execution evidence. Extra 12 helper calls, SQL admission/lowering, artifacts, barriers, file publication/recovery and output work are not included in the counter. |
| Design | [tests/unit/reoptimization_install_test.cpp](../../../../../tests/unit/reoptimization_install_test.cpp), [tests/support/selection_independent_fixture.hpp](../../../../../tests/support/selection_independent_fixture.hpp), [tests/support/indexed_runtime_fixture.hpp](../../../../../tests/support/indexed_runtime_fixture.hpp), [tests/support/local_sink_fixture.hpp](../../../../../tests/support/local_sink_fixture.hpp), [tests/support/session_file_fixture.hpp](../../../../../tests/support/session_file_fixture.hpp), [include/crown/runtime/session.hpp](../../../../../include/crown/runtime/session.hpp), [include/crown/runtime/reoptimization.hpp](../../../../../include/crown/runtime/reoptimization.hpp), [src/runtime/session.cpp](../../../../../src/runtime/session.cpp), [src/runtime/reoptimization.cpp](../../../../../src/runtime/reoptimization.cpp), [src/recovery/generation.cpp](../../../../../src/recovery/generation.cpp), [src/io/compiler_plan_artifact.cpp](../../../../../src/io/compiler_plan_artifact.cpp), [docs/reoptimization.md](../../../../reoptimization.md), [docs/generations.md](../../../../generations.md), [docs/history-retirement.md](../../../../history-retirement.md), [docs/local-sink.md](../../../../local-sink.md), [tests/candidates/queries/boolean_rst.cq.json](../../../../../tests/candidates/queries/boolean_rst.cq.json), [tests/candidates/trees/boolean_rst_native_s_root.tree.json](../../../../../tests/candidates/trees/boolean_rst_native_s_root.tree.json), [tests/candidates/trees/boolean_rst_generalized_x_root.tree.json](../../../../../tests/candidates/trees/boolean_rst_generalized_x_root.tree.json), [tests/candidates/trees/boolean_rst_generalized_y_root.tree.json](../../../../../tests/candidates/trees/boolean_rst_generalized_y_root.tree.json), [include/crown/frontend/admission.hpp](../../../../../include/crown/frontend/admission.hpp), [include/crown/io/compiler_plan_artifact.hpp](../../../../../include/crown/io/compiler_plan_artifact.hpp), [docs/session-journal.md](../../../../session-journal.md), [CMakeLists.txt](../../../../../CMakeLists.txt) |
