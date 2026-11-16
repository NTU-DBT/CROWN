# `tests/unit/reoptimization_install_fault_test.cpp` — block usage map

[Source](../../../../../tests/unit/reoptimization_install_fault_test.cpp) · [Source index](../../../README.md) · [Subsystem contracts](../../../subsystem_contracts.md) · [Reviewed primitives](../../../primitives.md)

Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection.

Snapshot SHA-256: `da0f42c47237668de09cdc00f13ec882028cea8dc14ab9188df45a9b06c88c4b`. 163 lines partitioned into 21 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [tests](../../../subsystem_contracts.md#tests). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/code_review.md](../../../../code_review.md), [docs/reference_fuzz.md](../../../../reference_fuzz.md), [docs/task_ledger.md](../../../../task_ledger.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–15](../../../../../tests/unit/reoptimization_install_fault_test.cpp#L1) | Imports dependencies; declares namespace scope; declares aliases. |  · [reviewed contract](#b0001) |
| [B0002 · 16–18](../../../../../tests/unit/reoptimization_install_fault_test.cpp#L16) | Callable definition: reoptimization::Options options() | calls ; returns value · [reviewed contract](#b0002) |
| [B0003 · 19–21](../../../../../tests/unit/reoptimization_install_fault_test.cpp#L19) | Callable definition: Relation rows(QuerySession& session) | calls snapshot, insert, storage::export_row, values; returns result; growth insert; 1 loop sites · [reviewed contract](#b0003) |
| [B0004 · 22–27](../../../../../tests/unit/reoptimization_install_fault_test.cpp#L22) | declares types or opens a type body; declares callable signatures; declares values/defaults or compile-time conditions. |  · [reviewed contract](#b0004) |
| [B0005 · 28–41](../../../../../tests/unit/reoptimization_install_fault_test.cpp#L28) | Callable definition: Fixture(const PhysicalPlan& plan,const planner::MinimumHeightCandidate& candidate,const Database& initial) :session(QuerySession:… | calls session, QuerySession::create_typed, start, enable_generation; guard check(session-&gt;read_local_epoch(1).rows.empty(),"install fault fixture lost its physical no-op epoc…; growth insert · [reviewed contract](#b0005) |
| [B0006 · 42–46](../../../../../tests/unit/reoptimization_install_fault_test.cpp#L42) | Callable definition: void commit(std::uint64_t sequence,TableId table,SetOperation operation,const Row& row) | calls batch, check, enqueue, begin_next; guard check(session-&gt;enqueue(batch)==io::Admission::accepted && session-&gt;begin_next(),"install fault pref… · [reviewed contract](#b0006) |
| [B0007 · 47–51](../../../../../tests/unit/reoptimization_install_fault_test.cpp#L47) | Callable definition: void historical() const | calls check, session_file_test::contents, generation_test::path; guard check(session_file_test::contents(generation_test::path(root,1,".ckpt"))==checkpoint && · [reviewed contract](#b0007) |
| [B0008 · 52–66](../../../../../tests/unit/reoptimization_install_fault_test.cpp#L52) | Callable definition: void recover(const PhysicalPlan& original,const Database& initial) | calls reset, QuerySession::lock_generation_recovery, CompiledProgram::standalone, generation_test::recovery_options; guard check((selected.generation==1 \|\| selected.generation==2) && session-&gt;status().committed_sequence==3… · [reviewed contract](#b0008) |
| [B0009 · 67–70](../../../../../tests/unit/reoptimization_install_fault_test.cpp#L67) | declares types or opens a type body; declares values/defaults or compile-time conditions. |  · [reviewed contract](#b0009) |
| [B0010 · 71–71](../../../../../tests/unit/reoptimization_install_fault_test.cpp#L71) | Callable definition: void visit(bool done) noexcept | calls _exit · [reviewed contract](#b0010) |
| [B0011 · 72–74](../../../../../tests/unit/reoptimization_install_fault_test.cpp#L72) | Callable definition: template&lt;class Decision&gt; Decision decision(bool done) const noexcept | calls ; returns result · [reviewed contract](#b0011) |
| [B0012 · 75–87](../../../../../tests/unit/reoptimization_install_fault_test.cpp#L75) | Callable definition: static recovery::testing::GenerationDecision generation(const recovery::testing::GenerationEvent& event,void* context) noexcept | calls visit; returns self.decision&lt;recovery::testing::GenerationDecision&gt;(event.after) · [reviewed contract](#b0012) |
| [B0013 · 88–92](../../../../../tests/unit/reoptimization_install_fault_test.cpp#L88) | Callable definition: static recovery::journal::testing::FileDecision journal(const recovery::journal::testing::FileEvent& event,void* context) noexcept | calls visit; returns self.decision&lt;recovery::journal::testing::FileDecision&gt;(event.after) · [reviewed contract](#b0013) |
| [B0014 · 93–93](../../../../../tests/unit/reoptimization_install_fault_test.cpp#L93) | Closes surrounding scope/type. |  · [reviewed contract](#b0014) |
| [B0015 · 94–97](../../../../../tests/unit/reoptimization_install_fault_test.cpp#L94) | Type/record definition: struct Installed |  · [reviewed contract](#b0015) |
| [B0016 · 98–102](../../../../../tests/unit/reoptimization_install_fault_test.cpp#L98) | Callable definition: std::uint64_t trace(const PhysicalPlan& original,const planner::MinimumHeightCandidate& candidate,const Database& initial,const i… | calls fixture, installed, check, publish_reoptimization; guard {s04_alloc::Scope count;Installed installed(hook);check(fixture.session-&gt;publish_reoptimization(art…; returns hook.count · [reviewed contract](#b0016) |
| [B0017 · 103–118](../../../../../tests/unit/reoptimization_install_fault_test.cpp#L103) | Callable definition: std::size_t io_cuts(const PhysicalPlan& original,const planner::MinimumHeightCandidate& candidate,const Database& initial,const i… | calls fixture, installed, publish_reoptimization, check; guard check(failed \|\| hook.absent,"native installation ignored a syscall failure");fixture.historical();; returns cuts; 2 loop sites · [reviewed contract](#b0017) |
| [B0018 · 119–128](../../../../../tests/unit/reoptimization_install_fault_test.cpp#L119) | Callable definition: std::size_t crash_cuts(const PhysicalPlan& original,const planner::MinimumHeightCandidate& candidate,const Database& initial,cons… | calls fixture, fork, check, installed; guard Fixture fixture(original,candidate,initial);const auto child=::fork();check(child&gt;=0,"native instal…; returns cuts; 2 loop sites · [reviewed contract](#b0018) |
| [B0019 · 129–147](../../../../../tests/unit/reoptimization_install_fault_test.cpp#L129) | Callable definition: std::size_t allocations(const PhysicalPlan& original,const planner::MinimumHeightCandidate& candidate,const Database& initial,con… | calls fixture, report_metadata, plan, account; guard check(count==account.statistics().successful_allocations-before,"native publication allocated outsi…; returns count; 1 loop sites · [reviewed contract](#b0019) |
| [B0020 · 148–148](../../../../../tests/unit/reoptimization_install_fault_test.cpp#L148) | Closes surrounding scope/type. | source comment (unverified): // namespace · [reviewed contract](#b0020) |
| [B0021 · 149–163](../../../../../tests/unit/reoptimization_install_fault_test.cpp#L149) | Callable definition: int main(int argc,char** argv) | calls check, c05_independent::boolean_fixture, s04_runtime::options, c05_independent::lower; guard check(argc==3,"usage: reoptimization_install_fault SOURCE io\|crash\|allocation");const auto fixture=…; returns 0; 1; 1 loop sites · [reviewed contract](#b0021) |

## B0001

[Lines 1–15](../../../../../tests/unit/reoptimization_install_fault_test.cpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L1-L15:sha256:3dfa5398322c7d76b52072b749081873417c64fef67d45a00021cd53bf12b6ca
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Prepare reoptimization_install_fault_test.cpp: include "selection_independent_fixture.hpp", "indexed_runtime_fixture.hpp", "local_sink_fixture.hpp", "generation_file_probe.hpp", "journal_file_probe.hpp", "crown/io/compiler_plan_artifact.hpp", "crown/runtime/session_reoptimization.hpp", &lt;cerrno&gt;, &lt;iostream&gt;, &lt;sys/wait.h&gt;; bind local aliases/name imports. |
| inputs / outputs | Compiler-visible dependencies, names and the recorded declarations in; declarations available to the following fixture/CLI/example definitions out. |
| invariants | Declarations are scoped to this source/header and its selected ABI. Included code has its own effects; names and editable fixture values do not confer proof, admission or publication authority. |
| ownership | Aliases/includes do not create a query owner. Pointers/references/views are non-owning. Containers own their elements, which can themselves be borrowed pointers or numeric IDs. Only documented owning shared-control handles retain controls; IDs/slot-handle values do not independently keep an arena/runtime alive. |
| failure | Missing headers, ill-formed names/types, failed static assertions or active #error directives stop compilation. No runtime rejection/rollback mechanism is implemented by aliases or function prototypes. |
| cost | Preprocessing and type/constraint instantiation cost compilation. Alias/prototype syntax does not invoke the declared operation; any included definitions keep their own initialization effects. |
| Design | [tests/unit/reoptimization_install_fault_test.cpp](../../../../../tests/unit/reoptimization_install_fault_test.cpp), [docs/reoptimization.md](../../../../reoptimization.md), [docs/code_review.md](../../../../code_review.md) |

## B0002

[Lines 16–18](../../../../../tests/unit/reoptimization_install_fault_test.cpp#L16); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
reoptimization::Options options() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Supply the forecast used to permit test publication payback. |
| inputs / outputs | Returns reoptimization options with forecast 1,000,000,000 ns/input, target 1 ns/input, and UINT64_MAX horizon. |
| invariants | Forecast values are caller-provided policy inputs, not measured speed. |
| ownership | Returns value options; no account or session retained. |
| failure | No helper failure branch. |
| cost | Fixed assignments; no native timing. |
| Design | [tests/unit/reoptimization_install_fault_test.cpp](../../../../../tests/unit/reoptimization_install_fault_test.cpp), [tests/support/selection_independent_fixture.hpp](../../../../../tests/support/selection_independent_fixture.hpp), [tests/support/indexed_runtime_fixture.hpp](../../../../../tests/support/indexed_runtime_fixture.hpp), [tests/support/local_sink_fixture.hpp](../../../../../tests/support/local_sink_fixture.hpp), [tests/support/generation_file_probe.hpp](../../../../../tests/support/generation_file_probe.hpp), [tests/support/session_file_fixture.hpp](../../../../../tests/support/session_file_fixture.hpp), [include/crown/runtime/session.hpp](../../../../../include/crown/runtime/session.hpp), [include/crown/runtime/reoptimization.hpp](../../../../../include/crown/runtime/reoptimization.hpp), [include/crown/recovery/generation.hpp](../../../../../include/crown/recovery/generation.hpp), [src/runtime/session.cpp](../../../../../src/runtime/session.cpp), [src/runtime/reoptimization.cpp](../../../../../src/runtime/reoptimization.cpp), [src/recovery/generation.cpp](../../../../../src/recovery/generation.cpp), [src/io/compiler_plan_artifact.cpp](../../../../../src/io/compiler_plan_artifact.cpp), [docs/reoptimization.md](../../../../reoptimization.md), [docs/generations.md](../../../../generations.md), [docs/local-sink.md](../../../../local-sink.md) |

## B0003

[Lines 19–21](../../../../../tests/unit/reoptimization_install_fault_test.cpp#L19); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Relation rows(QuerySession& session) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Copy current session snapshot rows for recovery-state comparison. |
| inputs / outputs | Snapshots session rows, exports them, and inserts them into a Relation. |
| invariants | This is a result-set oracle; it does not return a live cursor. |
| ownership | The Relation owns copied row values. |
| failure | Snapshot/export/allocation failures propagate. |
| cost | Visits/copies every snapshot row and grows a test container. |
| Design | [tests/unit/reoptimization_install_fault_test.cpp](../../../../../tests/unit/reoptimization_install_fault_test.cpp), [tests/support/selection_independent_fixture.hpp](../../../../../tests/support/selection_independent_fixture.hpp), [tests/support/indexed_runtime_fixture.hpp](../../../../../tests/support/indexed_runtime_fixture.hpp), [tests/support/local_sink_fixture.hpp](../../../../../tests/support/local_sink_fixture.hpp), [tests/support/generation_file_probe.hpp](../../../../../tests/support/generation_file_probe.hpp), [tests/support/session_file_fixture.hpp](../../../../../tests/support/session_file_fixture.hpp), [include/crown/runtime/session.hpp](../../../../../include/crown/runtime/session.hpp), [include/crown/runtime/reoptimization.hpp](../../../../../include/crown/runtime/reoptimization.hpp), [include/crown/recovery/generation.hpp](../../../../../include/crown/recovery/generation.hpp), [src/runtime/session.cpp](../../../../../src/runtime/session.cpp), [src/runtime/reoptimization.cpp](../../../../../src/runtime/reoptimization.cpp), [src/recovery/generation.cpp](../../../../../src/recovery/generation.cpp), [src/io/compiler_plan_artifact.cpp](../../../../../src/io/compiler_plan_artifact.cpp), [docs/reoptimization.md](../../../../reoptimization.md), [docs/generations.md](../../../../generations.md), [docs/local-sink.md](../../../../local-sink.md) |

## B0004

[Lines 22–27](../../../../../tests/unit/reoptimization_install_fault_test.cpp#L22); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L22-L27:sha256:ee0a8bae183870410637dbddfb0cffbac16fd0f6575536b87161d4a12aff73c5
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Prepare reoptimization_install_fault_test.cpp: declare fixture state/default initializers. |
| inputs / outputs | Compiler-visible dependencies, names and the recorded declarations in; declarations available to the following fixture/CLI/example definitions out. The source span lists the exact member/global names, types and initial values; initializers run when the enclosing object/program/thread is initialized. |
| invariants | Declarations are scoped to this source/header and its selected ABI. Included code has its own effects; names and editable fixture values do not confer proof, admission or publication authority. |
| ownership | Aliases/includes do not create a query owner. Pointers/references/views are non-owning. Containers own their elements, which can themselves be borrowed pointers or numeric IDs. Only documented owning shared-control handles retain controls; IDs/slot-handle values do not independently keep an arena/runtime alive. This filesystem Directory member owns the fixture namespace; its constructor/cleanup follows the documented filesystem effects of its helper type. |
| failure | Missing headers, ill-formed names/types, failed static assertions or active #error directives stop compilation. No runtime rejection/rollback mechanism is implemented by aliases or function prototypes. Actual object construction and explicit initializers keep the failure contracts of their declared types/called helpers; this card supplies no extra rollback. |
| cost | Preprocessing and type/constraint instantiation cost compilation. Alias/prototype syntax does not invoke the declared operation; any included definitions keep their own initialization effects. Member/global initialization follows the shown C++ types and expressions when its enclosing object/program is constructed; owning containers can allocate. Default member declarations do not themselves instantiate a fixture. Copies and teardown follow the owning types. This span declares a filesystem Directory member; its fixture construction/cleanup can perform filesystem I/O outside the native query account. |
| Design | [tests/unit/reoptimization_install_fault_test.cpp](../../../../../tests/unit/reoptimization_install_fault_test.cpp), [docs/reoptimization.md](../../../../reoptimization.md), [docs/code_review.md](../../../../code_review.md) |

## B0005

[Lines 28–41](../../../../../tests/unit/reoptimization_install_fault_test.cpp#L28); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
  Fixture(const PhysicalPlan& plan,const planner::MinimumHeightCandidate& candidate,const Database& initial)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Create the real installation-fault fixture at a nonzero durable delivery frontier. |
| inputs / outputs | Creates/starts typed session with generation and local sink; commits sequence 1 as a physical no-op, begins candidate, then commits updates 2 and 3; barrier verifies snapshot 1, target 3, two replayed records and sink verified sequence 3. Saves root, generation-1 checkpoint/WAL, sink bytes, and old owner. |
| invariants | Fixture has three durable output epochs; old owner/root snapshots are captured only after the verified barrier. Candidate target comes from the Boolean candidate family; session remains at its original owner before publication. |
| ownership | Session owns generation/sink and candidate; saved file contents and owner ID are test values; temporary directory owns paths. |
| failure | Any failed commit/delivery, nonempty no-op epoch, wrong barrier frontier/count or file read fails. |
| cost | Creates files and session, delivers three epochs, performs catch-up/barrier and copies four file snapshots; work is real fixture setup, not a measurement result. |
| Design | [tests/unit/reoptimization_install_fault_test.cpp](../../../../../tests/unit/reoptimization_install_fault_test.cpp), [tests/support/selection_independent_fixture.hpp](../../../../../tests/support/selection_independent_fixture.hpp), [tests/support/indexed_runtime_fixture.hpp](../../../../../tests/support/indexed_runtime_fixture.hpp), [tests/support/local_sink_fixture.hpp](../../../../../tests/support/local_sink_fixture.hpp), [tests/support/generation_file_probe.hpp](../../../../../tests/support/generation_file_probe.hpp), [tests/support/session_file_fixture.hpp](../../../../../tests/support/session_file_fixture.hpp), [include/crown/runtime/session.hpp](../../../../../include/crown/runtime/session.hpp), [include/crown/runtime/reoptimization.hpp](../../../../../include/crown/runtime/reoptimization.hpp), [include/crown/recovery/generation.hpp](../../../../../include/crown/recovery/generation.hpp), [src/runtime/session.cpp](../../../../../src/runtime/session.cpp), [src/runtime/reoptimization.cpp](../../../../../src/runtime/reoptimization.cpp), [src/recovery/generation.cpp](../../../../../src/recovery/generation.cpp), [src/io/compiler_plan_artifact.cpp](../../../../../src/io/compiler_plan_artifact.cpp), [docs/reoptimization.md](../../../../reoptimization.md), [docs/generations.md](../../../../generations.md), [docs/local-sink.md](../../../../local-sink.md) |

## B0006

[Lines 42–46](../../../../../tests/unit/reoptimization_install_fault_test.cpp#L42); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
  void commit(std::uint64_t sequence,TableId table,SetOperation operation,const Row& row) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Commit one update and durably deliver that epoch during fixture setup. |
| inputs / outputs | Enqueues sequence with feed offset sequence*10, requires begin_next, finishes the delta, and requires local sink delivery at the same sequence. |
| invariants | The test always uses the attached local sink; each call contributes one delivered epoch. |
| ownership | Input moves into session; sink/session own accepted/persisted state. |
| failure | Missing input or mismatched delivery sequence fails. |
| cost | One queue admission, unbounded epoch stepping, commit and durable sink write. |
| Design | [tests/unit/reoptimization_install_fault_test.cpp](../../../../../tests/unit/reoptimization_install_fault_test.cpp), [tests/support/selection_independent_fixture.hpp](../../../../../tests/support/selection_independent_fixture.hpp), [tests/support/indexed_runtime_fixture.hpp](../../../../../tests/support/indexed_runtime_fixture.hpp), [tests/support/local_sink_fixture.hpp](../../../../../tests/support/local_sink_fixture.hpp), [tests/support/generation_file_probe.hpp](../../../../../tests/support/generation_file_probe.hpp), [tests/support/session_file_fixture.hpp](../../../../../tests/support/session_file_fixture.hpp), [include/crown/runtime/session.hpp](../../../../../include/crown/runtime/session.hpp), [include/crown/runtime/reoptimization.hpp](../../../../../include/crown/runtime/reoptimization.hpp), [include/crown/recovery/generation.hpp](../../../../../include/crown/recovery/generation.hpp), [src/runtime/session.cpp](../../../../../src/runtime/session.cpp), [src/runtime/reoptimization.cpp](../../../../../src/runtime/reoptimization.cpp), [src/recovery/generation.cpp](../../../../../src/recovery/generation.cpp), [src/io/compiler_plan_artifact.cpp](../../../../../src/io/compiler_plan_artifact.cpp), [docs/reoptimization.md](../../../../reoptimization.md), [docs/generations.md](../../../../generations.md), [docs/local-sink.md](../../../../local-sink.md) |

## B0007

[Lines 47–51](../../../../../tests/unit/reoptimization_install_fault_test.cpp#L47); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
  void historical() const {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Assert that publication-fault trials preserve the original checkpoint, WAL and sink prefix. |
| inputs / outputs | Reads generation-1 checkpoint/WAL and sink bytes and compares them with Fixture snapshots. |
| invariants | This helper does not check root bytes or all generation files; callers perform those assertions separately. |
| ownership | Expected bytes are fixture-owned strings; file reads return temporary strings. |
| failure | Any changed byte fails. |
| cost | Reads and compares three files; I/O and memory scale with saved file lengths. |
| Design | [tests/unit/reoptimization_install_fault_test.cpp](../../../../../tests/unit/reoptimization_install_fault_test.cpp), [tests/support/selection_independent_fixture.hpp](../../../../../tests/support/selection_independent_fixture.hpp), [tests/support/indexed_runtime_fixture.hpp](../../../../../tests/support/indexed_runtime_fixture.hpp), [tests/support/local_sink_fixture.hpp](../../../../../tests/support/local_sink_fixture.hpp), [tests/support/generation_file_probe.hpp](../../../../../tests/support/generation_file_probe.hpp), [tests/support/session_file_fixture.hpp](../../../../../tests/support/session_file_fixture.hpp), [include/crown/runtime/session.hpp](../../../../../include/crown/runtime/session.hpp), [include/crown/runtime/reoptimization.hpp](../../../../../include/crown/runtime/reoptimization.hpp), [include/crown/recovery/generation.hpp](../../../../../include/crown/recovery/generation.hpp), [src/runtime/session.cpp](../../../../../src/runtime/session.cpp), [src/runtime/reoptimization.cpp](../../../../../src/runtime/reoptimization.cpp), [src/recovery/generation.cpp](../../../../../src/recovery/generation.cpp), [src/io/compiler_plan_artifact.cpp](../../../../../src/io/compiler_plan_artifact.cpp), [docs/reoptimization.md](../../../../reoptimization.md), [docs/generations.md](../../../../generations.md), [docs/local-sink.md](../../../../local-sink.md) |

## B0008

[Lines 52–66](../../../../../tests/unit/reoptimization_install_fault_test.cpp#L52); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
  void recover(const PhysicalPlan& original,const Database& initial) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Recover whichever generation root survived a publication cut and apply one next update. |
| inputs / outputs | Drops session, locks root using original plan, replays selected artifact into 16 MiB compiler account or prepares original if no plan; restores with local sink; checks selected gen 1/2, sequence 3, true empty-tuple result, then starts and commits delete sequence 4. |
| invariants | Recovery must select a complete old/new plan and exact sequence/source/result; local sink is restored; next update emits one row and leaves no result. |
| ownership | Compiler artifact uses a separate account; locked root owner is consumed by restore; returned session owns recovered runtime/generation/sink. |
| failure | Partial plan/epoch, wrong selected generation, changed row/output/frontier or any recovery/update error fails. |
| cost | May decode compiler descriptor, replay journal/sink, restore runtime, and execute/deliver one update; file and native work vary by recovered generation. |
| Design | [tests/unit/reoptimization_install_fault_test.cpp](../../../../../tests/unit/reoptimization_install_fault_test.cpp), [tests/support/selection_independent_fixture.hpp](../../../../../tests/support/selection_independent_fixture.hpp), [tests/support/indexed_runtime_fixture.hpp](../../../../../tests/support/indexed_runtime_fixture.hpp), [tests/support/local_sink_fixture.hpp](../../../../../tests/support/local_sink_fixture.hpp), [tests/support/generation_file_probe.hpp](../../../../../tests/support/generation_file_probe.hpp), [tests/support/session_file_fixture.hpp](../../../../../tests/support/session_file_fixture.hpp), [include/crown/runtime/session.hpp](../../../../../include/crown/runtime/session.hpp), [include/crown/runtime/reoptimization.hpp](../../../../../include/crown/runtime/reoptimization.hpp), [include/crown/recovery/generation.hpp](../../../../../include/crown/recovery/generation.hpp), [src/runtime/session.cpp](../../../../../src/runtime/session.cpp), [src/runtime/reoptimization.cpp](../../../../../src/runtime/reoptimization.cpp), [src/recovery/generation.cpp](../../../../../src/recovery/generation.cpp), [src/io/compiler_plan_artifact.cpp](../../../../../src/io/compiler_plan_artifact.cpp), [docs/reoptimization.md](../../../../reoptimization.md), [docs/generations.md](../../../../generations.md), [docs/local-sink.md](../../../../local-sink.md), [include/crown/io/compiler_plan_artifact.hpp](../../../../../include/crown/io/compiler_plan_artifact.hpp) |

## B0009

[Lines 67–70](../../../../../tests/unit/reoptimization_install_fault_test.cpp#L67); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L67-L70:sha256:27b3e8da9e8d8b886a1def10f022a535803ceacec8c4c42406958fad950d6216
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Prepare reoptimization_install_fault_test.cpp: declare fixture state/default initializers. |
| inputs / outputs | Compiler-visible dependencies, names and the recorded declarations in; declarations available to the following fixture/CLI/example definitions out. The source span lists the exact member/global names, types and initial values; initializers run when the enclosing object/program/thread is initialized. |
| invariants | Declarations are scoped to this source/header and its selected ABI. Included code has its own effects; names and editable fixture values do not confer proof, admission or publication authority. |
| ownership | Aliases/includes do not create a query owner. Pointers/references/views are non-owning. Containers own their elements, which can themselves be borrowed pointers or numeric IDs. Only documented owning shared-control handles retain controls; IDs/slot-handle values do not independently keep an arena/runtime alive. |
| failure | Missing headers, ill-formed names/types, failed static assertions or active #error directives stop compilation. No runtime rejection/rollback mechanism is implemented by aliases or function prototypes. Actual object construction and explicit initializers keep the failure contracts of their declared types/called helpers; this card supplies no extra rollback. |
| cost | Preprocessing and type/constraint instantiation cost compilation. Alias/prototype syntax does not invoke the declared operation; any included definitions keep their own initialization effects. Member/global initialization follows the shown C++ types and expressions when its enclosing object/program is constructed; owning containers can allocate. Default member declarations do not themselves instantiate a fixture. Copies and teardown follow the owning types. |
| Design | [tests/unit/reoptimization_install_fault_test.cpp](../../../../../tests/unit/reoptimization_install_fault_test.cpp), [docs/reoptimization.md](../../../../reoptimization.md), [docs/code_review.md](../../../../code_review.md) |

## B0010

[Lines 71–71](../../../../../tests/unit/reoptimization_install_fault_test.cpp#L71); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
  void visit(bool done) noexcept {if(!done)++count;if(count==crash && done==after)::_exit(77);}
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Advance a shared hook ordinal and terminate at a selected process-crash event. |
| inputs / outputs | Increments count only for before callbacks; calls _exit(77) when ordinal and before/after side match crash target. |
| invariants | After events reuse the current ordinal; crash ordinal is chosen by the parent sweep. |
| ownership | No heap or test fixture ownership; callback context is borrowed. |
| failure | Process exits immediately at requested cut; no cleanup or exception recovery runs in child. |
| cost | One counter comparison per callback; process termination is immediate at selected event. |
| Design | [tests/unit/reoptimization_install_fault_test.cpp](../../../../../tests/unit/reoptimization_install_fault_test.cpp), [tests/support/selection_independent_fixture.hpp](../../../../../tests/support/selection_independent_fixture.hpp), [tests/support/indexed_runtime_fixture.hpp](../../../../../tests/support/indexed_runtime_fixture.hpp), [tests/support/local_sink_fixture.hpp](../../../../../tests/support/local_sink_fixture.hpp), [tests/support/generation_file_probe.hpp](../../../../../tests/support/generation_file_probe.hpp), [tests/support/session_file_fixture.hpp](../../../../../tests/support/session_file_fixture.hpp), [include/crown/runtime/session.hpp](../../../../../include/crown/runtime/session.hpp), [include/crown/runtime/reoptimization.hpp](../../../../../include/crown/runtime/reoptimization.hpp), [include/crown/recovery/generation.hpp](../../../../../include/crown/recovery/generation.hpp), [src/runtime/session.cpp](../../../../../src/runtime/session.cpp), [src/runtime/reoptimization.cpp](../../../../../src/runtime/reoptimization.cpp), [src/recovery/generation.cpp](../../../../../src/recovery/generation.cpp), [src/io/compiler_plan_artifact.cpp](../../../../../src/io/compiler_plan_artifact.cpp), [docs/reoptimization.md](../../../../reoptimization.md), [docs/generations.md](../../../../generations.md), [docs/local-sink.md](../../../../local-sink.md) |

## B0011

[Lines 72–74](../../../../../tests/unit/reoptimization_install_fault_test.cpp#L72); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
  template<class Decision> Decision decision(bool done) const noexcept {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Build a before/after I/O error decision for the current hook ordinal. |
| inputs / outputs | Returns Decision with error_after or error_before set to EIO only for the matching before ordinal. |
| invariants | No error is injected on unrelated events or when callback is after and after mode is false. |
| ownership | Returns fixed decision value; does not retain event/context. |
| failure | The target operation observes the injected native error through its file wrapper. |
| cost | Fixed comparisons and decision construction. |
| Design | [tests/unit/reoptimization_install_fault_test.cpp](../../../../../tests/unit/reoptimization_install_fault_test.cpp), [tests/support/selection_independent_fixture.hpp](../../../../../tests/support/selection_independent_fixture.hpp), [tests/support/indexed_runtime_fixture.hpp](../../../../../tests/support/indexed_runtime_fixture.hpp), [tests/support/local_sink_fixture.hpp](../../../../../tests/support/local_sink_fixture.hpp), [tests/support/generation_file_probe.hpp](../../../../../tests/support/generation_file_probe.hpp), [tests/support/session_file_fixture.hpp](../../../../../tests/support/session_file_fixture.hpp), [include/crown/runtime/session.hpp](../../../../../include/crown/runtime/session.hpp), [include/crown/runtime/reoptimization.hpp](../../../../../include/crown/runtime/reoptimization.hpp), [include/crown/recovery/generation.hpp](../../../../../include/crown/recovery/generation.hpp), [src/runtime/session.cpp](../../../../../src/runtime/session.cpp), [src/runtime/reoptimization.cpp](../../../../../src/runtime/reoptimization.cpp), [src/recovery/generation.cpp](../../../../../src/recovery/generation.cpp), [src/io/compiler_plan_artifact.cpp](../../../../../src/io/compiler_plan_artifact.cpp), [docs/reoptimization.md](../../../../reoptimization.md), [docs/generations.md](../../../../generations.md), [docs/local-sink.md](../../../../local-sink.md), [tests/support/journal_file_probe.hpp](../../../../../tests/support/journal_file_probe.hpp) |

## B0012

[Lines 75–87](../../../../../tests/unit/reoptimization_install_fault_test.cpp#L75); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
  static recovery::testing::GenerationDecision generation(const recovery::testing::GenerationEvent& event,void* context) noexcept {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Observe generation-file events, verify sync order before root rename, and optionally deny the C++ new probe at that seam. |
| inputs / outputs | Routes event through visit; tracks successful plan/checkpoint directory syncs; at root rename requires plan/checkpoint/WAL sync flags, marks reached and optionally sets s04_alloc remaining to zero; returns injected decision. |
| invariants | The asserted order is the test’s observed hook order before root rename. The deny seam tests configured C++ new allocation instrumentation, not libcmalloc or host power-loss behavior. |
| ownership | Hook context is borrowed until Installed resets callbacks. |
| failure | Injected EIO or process exit follows configured Hook state; callback itself is noexcept. |
| cost | One event update plus a few stage/result comparisons; no file operation occurs in the callback itself. |
| Design | [tests/unit/reoptimization_install_fault_test.cpp](../../../../../tests/unit/reoptimization_install_fault_test.cpp), [tests/support/selection_independent_fixture.hpp](../../../../../tests/support/selection_independent_fixture.hpp), [tests/support/indexed_runtime_fixture.hpp](../../../../../tests/support/indexed_runtime_fixture.hpp), [tests/support/local_sink_fixture.hpp](../../../../../tests/support/local_sink_fixture.hpp), [tests/support/generation_file_probe.hpp](../../../../../tests/support/generation_file_probe.hpp), [tests/support/session_file_fixture.hpp](../../../../../tests/support/session_file_fixture.hpp), [include/crown/runtime/session.hpp](../../../../../include/crown/runtime/session.hpp), [include/crown/runtime/reoptimization.hpp](../../../../../include/crown/runtime/reoptimization.hpp), [include/crown/recovery/generation.hpp](../../../../../include/crown/recovery/generation.hpp), [src/runtime/session.cpp](../../../../../src/runtime/session.cpp), [src/runtime/reoptimization.cpp](../../../../../src/runtime/reoptimization.cpp), [src/recovery/generation.cpp](../../../../../src/recovery/generation.cpp), [src/io/compiler_plan_artifact.cpp](../../../../../src/io/compiler_plan_artifact.cpp), [docs/reoptimization.md](../../../../reoptimization.md), [docs/generations.md](../../../../generations.md), [docs/local-sink.md](../../../../local-sink.md) |

## B0013

[Lines 88–92](../../../../../tests/unit/reoptimization_install_fault_test.cpp#L88); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
  static recovery::journal::testing::FileDecision journal(const recovery::journal::testing::FileEvent& event,void* context) noexcept {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Track the WAL directory-sync event and apply injected journal-file failures. |
| inputs / outputs | Routes journal event through visit, marks wal_synced for successful directory sync, and returns the configured decision. |
| invariants | The test requires WAL durable sync to be observed before root rename in trace. |
| ownership | Hook context is borrowed; file callback does not retain the event. |
| failure | Configured EIO/crash is consumed by the journal file operation. |
| cost | One callback, counter update and fixed stage/result checks. |
| Design | [tests/unit/reoptimization_install_fault_test.cpp](../../../../../tests/unit/reoptimization_install_fault_test.cpp), [tests/support/selection_independent_fixture.hpp](../../../../../tests/support/selection_independent_fixture.hpp), [tests/support/indexed_runtime_fixture.hpp](../../../../../tests/support/indexed_runtime_fixture.hpp), [tests/support/local_sink_fixture.hpp](../../../../../tests/support/local_sink_fixture.hpp), [tests/support/generation_file_probe.hpp](../../../../../tests/support/generation_file_probe.hpp), [tests/support/session_file_fixture.hpp](../../../../../tests/support/session_file_fixture.hpp), [include/crown/runtime/session.hpp](../../../../../include/crown/runtime/session.hpp), [include/crown/runtime/reoptimization.hpp](../../../../../include/crown/runtime/reoptimization.hpp), [include/crown/recovery/generation.hpp](../../../../../include/crown/recovery/generation.hpp), [src/runtime/session.cpp](../../../../../src/runtime/session.cpp), [src/runtime/reoptimization.cpp](../../../../../src/runtime/reoptimization.cpp), [src/recovery/generation.cpp](../../../../../src/recovery/generation.cpp), [src/io/compiler_plan_artifact.cpp](../../../../../src/io/compiler_plan_artifact.cpp), [docs/reoptimization.md](../../../../reoptimization.md), [docs/generations.md](../../../../generations.md), [docs/local-sink.md](../../../../local-sink.md), [tests/support/journal_file_probe.hpp](../../../../../tests/support/journal_file_probe.hpp) |

## B0014

[Lines 93–93](../../../../../tests/unit/reoptimization_install_fault_test.cpp#L93); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L93-L93:sha256:aa1d1a63390229c798347e83a0405441c9400035284ad168c1bf6cdf1d70a370
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Close the recorded declaration scopes in reoptimization_install_fault_test.cpp: struct Hook. |
| inputs / outputs | Preceding namespace, type or initializer declarations in; completed lexical boundary out. |
| invariants | Brace-opening context is recorded in root-scope-context-v1.json. These are declaration/initializer boundaries, not an independent update, validation or recovery operation. |
| ownership | Enclosing objects and borrowed fields keep their declared ownership. This punctuation creates no new owner. |
| failure | Malformed scope syntax is a compile error. Any initializer/constructor failure belongs to the enclosing object declaration. |
| cost | No separate loop, guard or engine call is introduced by the delimiter; enclosing initialization and object lifetime still have their actual costs. |
| Design | [tests/unit/reoptimization_install_fault_test.cpp](../../../../../tests/unit/reoptimization_install_fault_test.cpp), [docs/reoptimization.md](../../../../reoptimization.md), [docs/code_review.md](../../../../code_review.md) |

## B0015

[Lines 94–97](../../../../../tests/unit/reoptimization_install_fault_test.cpp#L94); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct Installed {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Install generation and journal callbacks for one fault trial and clear them on scope exit. |
| inputs / outputs | Registers both static callbacks with Hook context; destructor clears both registrations. |
| invariants | Hook must outlive the installed scope. Both registrations are thread-local; destruction sets them to null instead of restoring prior callbacks, so nested installations through this helper are unsupported. |
| ownership | The Hook context pointer is borrowed by both callbacks. Installed does not own Hook or preserve previous thread-local registration state. |
| failure | Registration or the target operation failure propagates; destructor only resets hooks. |
| cost | Two global hook updates at entry and two at exit. |
| Design | [tests/unit/reoptimization_install_fault_test.cpp](../../../../../tests/unit/reoptimization_install_fault_test.cpp), [tests/support/selection_independent_fixture.hpp](../../../../../tests/support/selection_independent_fixture.hpp), [tests/support/indexed_runtime_fixture.hpp](../../../../../tests/support/indexed_runtime_fixture.hpp), [tests/support/local_sink_fixture.hpp](../../../../../tests/support/local_sink_fixture.hpp), [tests/support/generation_file_probe.hpp](../../../../../tests/support/generation_file_probe.hpp), [tests/support/session_file_fixture.hpp](../../../../../tests/support/session_file_fixture.hpp), [include/crown/runtime/session.hpp](../../../../../include/crown/runtime/session.hpp), [include/crown/runtime/reoptimization.hpp](../../../../../include/crown/runtime/reoptimization.hpp), [include/crown/recovery/generation.hpp](../../../../../include/crown/recovery/generation.hpp), [src/runtime/session.cpp](../../../../../src/runtime/session.cpp), [src/runtime/reoptimization.cpp](../../../../../src/runtime/reoptimization.cpp), [src/recovery/generation.cpp](../../../../../src/recovery/generation.cpp), [src/io/compiler_plan_artifact.cpp](../../../../../src/io/compiler_plan_artifact.cpp), [docs/reoptimization.md](../../../../reoptimization.md), [docs/generations.md](../../../../generations.md), [docs/local-sink.md](../../../../local-sink.md), [tests/support/journal_file_probe.hpp](../../../../../tests/support/journal_file_probe.hpp) |

## B0016

[Lines 98–102](../../../../../tests/unit/reoptimization_install_fault_test.cpp#L98); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::uint64_t trace(const PhysicalPlan& original,const planner::MinimumHeightCandidate& candidate,const Database& initial,const io::CompilerPlanArtifact& artifact) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Trace real publication callbacks while denying configured C++ new at root rename. |
| inputs / outputs | Builds fresh Fixture, runs publish_reoptimization with Hook.deny under s04_alloc scope, then requires rename reached, all syncs ordered, and no allocator trigger; returns observed callback count. |
| invariants | The trace proves the hook order and absence of the configured allocator trigger on this path after the seam; it is not a general allocation-free, libcmalloc, or power-loss proof. Returned count is the observed ordinal boundary count for this profile. |
| ownership | Session retains old owner until publication selection/install; artifact is external compiler input. Hook is cleared before return. |
| failure | Publication/order/allocation assertion failures fail the trace. |
| cost | Performs one full session publication, callback visits and account/allocator checks; trace is run once per backend in main. |
| Design | [tests/unit/reoptimization_install_fault_test.cpp](../../../../../tests/unit/reoptimization_install_fault_test.cpp), [tests/support/selection_independent_fixture.hpp](../../../../../tests/support/selection_independent_fixture.hpp), [tests/support/indexed_runtime_fixture.hpp](../../../../../tests/support/indexed_runtime_fixture.hpp), [tests/support/local_sink_fixture.hpp](../../../../../tests/support/local_sink_fixture.hpp), [tests/support/generation_file_probe.hpp](../../../../../tests/support/generation_file_probe.hpp), [tests/support/session_file_fixture.hpp](../../../../../tests/support/session_file_fixture.hpp), [include/crown/runtime/session.hpp](../../../../../include/crown/runtime/session.hpp), [include/crown/runtime/reoptimization.hpp](../../../../../include/crown/runtime/reoptimization.hpp), [include/crown/recovery/generation.hpp](../../../../../include/crown/recovery/generation.hpp), [src/runtime/session.cpp](../../../../../src/runtime/session.cpp), [src/runtime/reoptimization.cpp](../../../../../src/runtime/reoptimization.cpp), [src/recovery/generation.cpp](../../../../../src/recovery/generation.cpp), [src/io/compiler_plan_artifact.cpp](../../../../../src/io/compiler_plan_artifact.cpp), [docs/reoptimization.md](../../../../reoptimization.md), [docs/generations.md](../../../../generations.md), [docs/local-sink.md](../../../../local-sink.md), [include/crown/io/compiler_plan_artifact.hpp](../../../../../include/crown/io/compiler_plan_artifact.hpp), [tests/support/journal_file_probe.hpp](../../../../../tests/support/journal_file_probe.hpp), [docs/session-journal.md](../../../../session-journal.md) |

## B0017

[Lines 103–118](../../../../../tests/unit/reoptimization_install_fault_test.cpp#L103); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::size_t io_cuts(const PhysicalPlan& original,const planner::MinimumHeightCandidate& candidate,const Database& initial,const io::CompilerPlanArtifact& artifact,std::uint64_t boundaries) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Inject every observed before/after file I/O cut and verify recovery, retry, or uncertainty behavior. |
| inputs / outputs | For each boundary and side, builds a fresh Fixture and calls publish; accepts GenerationFailure/FileFailure or the explicit absent-candidate cleanup case, checks historical files, then either recovery_required latch or unchanged old owner/root plus successful retry; finally recovers and counts cut. |
| invariants | Only preselection failures with unchanged root/owner are retried; ambiguous root selection must latch recovery_required. The hook.absent allowance covers injected unlink_candidate/ENOENT cleanup. |
| ownership | Fresh session/root/sink per cut; recovery consumes root lock and replaces fixture session. |
| failure | Missed injection (except absent cleanup), changed rollback files, wrong phase, old-root change, failed retry or bad recovered update fails. |
| cost | For each of 2×B observed boundaries, creates fixture, publishes once under hooks, reads historical files, may retry, and fully recovers/applies next input. B is measured by trace per backend; no fixed count or CPU guarantee. |
| Design | [tests/unit/reoptimization_install_fault_test.cpp](../../../../../tests/unit/reoptimization_install_fault_test.cpp), [tests/support/selection_independent_fixture.hpp](../../../../../tests/support/selection_independent_fixture.hpp), [tests/support/indexed_runtime_fixture.hpp](../../../../../tests/support/indexed_runtime_fixture.hpp), [tests/support/local_sink_fixture.hpp](../../../../../tests/support/local_sink_fixture.hpp), [tests/support/generation_file_probe.hpp](../../../../../tests/support/generation_file_probe.hpp), [tests/support/session_file_fixture.hpp](../../../../../tests/support/session_file_fixture.hpp), [include/crown/runtime/session.hpp](../../../../../include/crown/runtime/session.hpp), [include/crown/runtime/reoptimization.hpp](../../../../../include/crown/runtime/reoptimization.hpp), [include/crown/recovery/generation.hpp](../../../../../include/crown/recovery/generation.hpp), [src/runtime/session.cpp](../../../../../src/runtime/session.cpp), [src/runtime/reoptimization.cpp](../../../../../src/runtime/reoptimization.cpp), [src/recovery/generation.cpp](../../../../../src/recovery/generation.cpp), [src/io/compiler_plan_artifact.cpp](../../../../../src/io/compiler_plan_artifact.cpp), [docs/reoptimization.md](../../../../reoptimization.md), [docs/generations.md](../../../../generations.md), [docs/local-sink.md](../../../../local-sink.md), [include/crown/io/compiler_plan_artifact.hpp](../../../../../include/crown/io/compiler_plan_artifact.hpp), [tests/support/journal_file_probe.hpp](../../../../../tests/support/journal_file_probe.hpp), [docs/session-journal.md](../../../../session-journal.md) |

## B0018

[Lines 119–128](../../../../../tests/unit/reoptimization_install_fault_test.cpp#L119); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::size_t crash_cuts(const PhysicalPlan& original,const planner::MinimumHeightCandidate& candidate,const Database& initial,const io::CompilerPlanArtifact& artifact,std::uint64_t boundaries) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Crash a child at every observed before/after publication I/O boundary, then recover in the parent. |
| inputs / outputs | For each boundary/side creates Fixture, forks; child publishes with Hook crash and must exit 77; parent checks historical bytes and calls recover. |
| invariants | Expected recovery is old or fully selected new generation; each trial checks next update after recovery. Parent does not assert a fixed boundary count. |
| ownership | Child inherits fixture process state after fork; filesystem changes are shared; parent retains its descriptors/session and destroys normally after recovery. |
| failure | Fork/wait mismatch, missed exit 77, changed historical file, or failed recovery/update fails. |
| cost | Two trials per observed boundary, each with fixture creation, fork/wait and recovery. This is process-exit injection, not a physical power-loss test. |
| Design | [tests/unit/reoptimization_install_fault_test.cpp](../../../../../tests/unit/reoptimization_install_fault_test.cpp), [tests/support/selection_independent_fixture.hpp](../../../../../tests/support/selection_independent_fixture.hpp), [tests/support/indexed_runtime_fixture.hpp](../../../../../tests/support/indexed_runtime_fixture.hpp), [tests/support/local_sink_fixture.hpp](../../../../../tests/support/local_sink_fixture.hpp), [tests/support/generation_file_probe.hpp](../../../../../tests/support/generation_file_probe.hpp), [tests/support/session_file_fixture.hpp](../../../../../tests/support/session_file_fixture.hpp), [include/crown/runtime/session.hpp](../../../../../include/crown/runtime/session.hpp), [include/crown/runtime/reoptimization.hpp](../../../../../include/crown/runtime/reoptimization.hpp), [include/crown/recovery/generation.hpp](../../../../../include/crown/recovery/generation.hpp), [src/runtime/session.cpp](../../../../../src/runtime/session.cpp), [src/runtime/reoptimization.cpp](../../../../../src/runtime/reoptimization.cpp), [src/recovery/generation.cpp](../../../../../src/recovery/generation.cpp), [src/io/compiler_plan_artifact.cpp](../../../../../src/io/compiler_plan_artifact.cpp), [docs/reoptimization.md](../../../../reoptimization.md), [docs/generations.md](../../../../generations.md), [docs/local-sink.md](../../../../local-sink.md), [include/crown/io/compiler_plan_artifact.hpp](../../../../../include/crown/io/compiler_plan_artifact.hpp), [tests/support/journal_file_probe.hpp](../../../../../tests/support/journal_file_probe.hpp), [docs/session-journal.md](../../../../session-journal.md) |

## B0019

[Lines 129–147](../../../../../tests/unit/reoptimization_install_fault_test.cpp#L129); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::size_t allocations(const PhysicalPlan& original,const planner::MinimumHeightCandidate& candidate,const Database& initial,const io::CompilerPlanArtifact& artifact) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Count observed publication allocator calls and fail each nonterminal allocation ordinal. |
| inputs / outputs | Measures one baseline publish; asserts s04_alloc calls equal the original account successful-allocation delta and count is 1..9999; for points 0 through N-1, forces bad_alloc, checks no recovery-required and unchanged old owner/root/history, retries publish, then recovers. |
| invariants | Sweep has N failure trials, not an extra terminal-N failure trial. Per backend the helper makes one baseline publication plus two publications per ordinal (failed attempt and retry). Account allocation count is specific to the original query account; no CPU or total-heap statement follows. |
| ownership | Compiler artifact is held in separate account; native publication allocations are asserted against original runtime account; each fixture has its own owner and files. |
| failure | Every injected point must trigger and throw bad_alloc before selection; failure must leave original state retryable. |
| cost | N is measured separately per backend; the loop covers 0≤point&lt;N and each point constructs a new fixture, fails one publication, retries once, then recovers. File/setup work is outside the allocation-count assertion. |
| Design | [tests/unit/reoptimization_install_fault_test.cpp](../../../../../tests/unit/reoptimization_install_fault_test.cpp), [tests/support/selection_independent_fixture.hpp](../../../../../tests/support/selection_independent_fixture.hpp), [tests/support/indexed_runtime_fixture.hpp](../../../../../tests/support/indexed_runtime_fixture.hpp), [tests/support/local_sink_fixture.hpp](../../../../../tests/support/local_sink_fixture.hpp), [tests/support/generation_file_probe.hpp](../../../../../tests/support/generation_file_probe.hpp), [tests/support/session_file_fixture.hpp](../../../../../tests/support/session_file_fixture.hpp), [include/crown/runtime/session.hpp](../../../../../include/crown/runtime/session.hpp), [include/crown/runtime/reoptimization.hpp](../../../../../include/crown/runtime/reoptimization.hpp), [include/crown/recovery/generation.hpp](../../../../../include/crown/recovery/generation.hpp), [src/runtime/session.cpp](../../../../../src/runtime/session.cpp), [src/runtime/reoptimization.cpp](../../../../../src/runtime/reoptimization.cpp), [src/recovery/generation.cpp](../../../../../src/recovery/generation.cpp), [src/io/compiler_plan_artifact.cpp](../../../../../src/io/compiler_plan_artifact.cpp), [docs/reoptimization.md](../../../../reoptimization.md), [docs/generations.md](../../../../generations.md), [docs/local-sink.md](../../../../local-sink.md), [include/crown/io/compiler_plan_artifact.hpp](../../../../../include/crown/io/compiler_plan_artifact.hpp) |

## B0020

[Lines 148–148](../../../../../tests/unit/reoptimization_install_fault_test.cpp#L148); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L148-L148:sha256:533f16bca7d58f44b3103b92e3485d22cfbb34bbad5ea3f3fa3b5a9dcb24ec89
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Close the recorded declaration scopes in reoptimization_install_fault_test.cpp: namespace (anonymous). |
| inputs / outputs | Preceding namespace, type or initializer declarations in; completed lexical boundary out. |
| invariants | Brace-opening context is recorded in root-scope-context-v1.json. These are declaration/initializer boundaries, not an independent update, validation or recovery operation. |
| ownership | Enclosing objects and borrowed fields keep their declared ownership. This punctuation creates no new owner. |
| failure | Malformed scope syntax is a compile error. Any initializer/constructor failure belongs to the enclosing object declaration. |
| cost | No separate loop, guard or engine call is introduced by the delimiter; enclosing initialization and object lifetime still have their actual costs. |
| Design | [tests/unit/reoptimization_install_fault_test.cpp](../../../../../tests/unit/reoptimization_install_fault_test.cpp), [docs/reoptimization.md](../../../../reoptimization.md), [docs/code_review.md](../../../../code_review.md) |

## B0021

[Lines 149–163](../../../../../tests/unit/reoptimization_install_fault_test.cpp#L149); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
int main(int argc,char** argv) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Run publication I/O, crash, or allocation fault sweeps for both physical backends. |
| inputs / outputs | Requires SOURCE and mode; constructs literal Boolean family, lowers candidates 0/1 for plain/indexed backends, prepares target artifact in 16 MiB compiler account, measures trace boundary count, then exact io/crash dispatch or allocation for every other mode string. |
| invariants | Fixture frontier is snapshot epoch 1, target/barrier epoch 3, two replayed records, and three delivered output epochs. Unknown mode text falls through to allocation; it is not rejected. Streamed printed cuts depend on actual hook/allocation counts and are source behavior, not a run result. |
| ownership | Each iteration owns original/target plan values and compiler artifact; fixture scopes own root/session/sink state. |
| failure | std::exception prints and returns 1; otherwise 0 after both backends. Invalid second argument is not itself an error. |
| cost | One trace per backend plus mode-specific dynamic sweeps; allocation count uses N trials 0..N-1 and baseline+2N publish attempts per backend. This source-derived structure does not claim execution or host CPU cost. |
| Design | [tests/unit/reoptimization_install_fault_test.cpp](../../../../../tests/unit/reoptimization_install_fault_test.cpp), [tests/support/selection_independent_fixture.hpp](../../../../../tests/support/selection_independent_fixture.hpp), [tests/support/indexed_runtime_fixture.hpp](../../../../../tests/support/indexed_runtime_fixture.hpp), [tests/support/local_sink_fixture.hpp](../../../../../tests/support/local_sink_fixture.hpp), [tests/support/generation_file_probe.hpp](../../../../../tests/support/generation_file_probe.hpp), [tests/support/session_file_fixture.hpp](../../../../../tests/support/session_file_fixture.hpp), [include/crown/runtime/session.hpp](../../../../../include/crown/runtime/session.hpp), [include/crown/runtime/reoptimization.hpp](../../../../../include/crown/runtime/reoptimization.hpp), [include/crown/recovery/generation.hpp](../../../../../include/crown/recovery/generation.hpp), [src/runtime/session.cpp](../../../../../src/runtime/session.cpp), [src/runtime/reoptimization.cpp](../../../../../src/runtime/reoptimization.cpp), [src/recovery/generation.cpp](../../../../../src/recovery/generation.cpp), [src/io/compiler_plan_artifact.cpp](../../../../../src/io/compiler_plan_artifact.cpp), [docs/reoptimization.md](../../../../reoptimization.md), [docs/generations.md](../../../../generations.md), [docs/local-sink.md](../../../../local-sink.md), [tests/candidates/queries/boolean_rst.cq.json](../../../../../tests/candidates/queries/boolean_rst.cq.json), [tests/candidates/trees/boolean_rst_native_s_root.tree.json](../../../../../tests/candidates/trees/boolean_rst_native_s_root.tree.json), [tests/candidates/trees/boolean_rst_generalized_x_root.tree.json](../../../../../tests/candidates/trees/boolean_rst_generalized_x_root.tree.json), [tests/candidates/trees/boolean_rst_generalized_y_root.tree.json](../../../../../tests/candidates/trees/boolean_rst_generalized_y_root.tree.json), [include/crown/io/compiler_plan_artifact.hpp](../../../../../include/crown/io/compiler_plan_artifact.hpp), [tests/support/journal_file_probe.hpp](../../../../../tests/support/journal_file_probe.hpp), [docs/session-journal.md](../../../../session-journal.md), [CMakeLists.txt](../../../../../CMakeLists.txt) |
