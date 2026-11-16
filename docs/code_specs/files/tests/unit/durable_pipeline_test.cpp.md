# `tests/unit/durable_pipeline_test.cpp` — block usage map

[Source](../../../../../tests/unit/durable_pipeline_test.cpp) · [Source index](../../../README.md) · [Subsystem contracts](../../../subsystem_contracts.md) · [Reviewed primitives](../../../primitives.md)

Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection.

Snapshot SHA-256: `0e7f6f58795cabe6e43794c768b954e77f8bb2a772cbe29c758e7593b4ca8c38`. 148 lines partitioned into 27 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [tests](../../../subsystem_contracts.md#tests). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/code_review.md](../../../../code_review.md), [docs/reference_fuzz.md](../../../../reference_fuzz.md), [docs/task_ledger.md](../../../../task_ledger.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–17](../../../../../tests/unit/durable_pipeline_test.cpp#L1) | Imports dependencies; declares namespace scope; declares aliases; declares types or opens a type body. |  · [reviewed contract](#b0001) |
| [B0002 · 18–22](../../../../../tests/unit/durable_pipeline_test.cpp#L18) | Callable definition: explicit Pipeline(bool indexed):fixture(indexed,1),program(CompiledProgram::standalone(fixture.query.test.plan)) | calls fixture, program, CompiledProgram::standalone, resize; guard check(expected.size()==3,"loop-edge fixture did not exercise both aliases and new-new output");; growth resize; 1 loop sites · [reviewed contract](#b0002) |
| [B0003 · 23–23](../../../../../tests/unit/durable_pipeline_test.cpp#L23) | Callable definition: QuerySession& session() | calls ; returns *fixture.query.session · [reviewed contract](#b0003) |
| [B0004 · 24–24](../../../../../tests/unit/durable_pipeline_test.cpp#L24) | Callable definition: void offer() | calls typed::enqueue, session · [reviewed contract](#b0004) |
| [B0005 · 25–25](../../../../../tests/unit/durable_pipeline_test.cpp#L25) | Callable definition: void begin() | calls check, session, begin_next; guard void begin(){check(session().begin_next(),"durable loop-edge input missing");} · [reviewed contract](#b0005) |
| [B0006 · 26–26](../../../../../tests/unit/durable_pipeline_test.cpp#L26) | Callable definition: void restore() | calls reset, QuerySession::restore_generation_with_local_sink, generation_test::recovery_options, options · [reviewed contract](#b0006) |
| [B0007 · 27–30](../../../../../tests/unit/durable_pipeline_test.cpp#L27) | Callable definition: void unchanged() | calls check, session, status, progress; guard check(session().status().committed_sequence==2 && session().progress().sequence==2 && session().loc… · [reviewed contract](#b0007) |
| [B0008 · 31–40](../../../../../tests/unit/durable_pipeline_test.cpp#L31) | Callable definition: void recover(bool committed,bool pending) | calls restore, session, local_sink_state, check; guard restore();const auto stored=session().local_sink_state().persisted.sequence;check(stored&gt;=2 && stor… · [reviewed contract](#b0008) |
| [B0009 · 41–46](../../../../../tests/unit/durable_pipeline_test.cpp#L41) | Callable definition: void next_and_retire(bool queued) | calls apply, typed::oracle, begin, finish; guard static_cast&lt;void&gt;(session().deliver_local_epoch());check(typed::rows(session())==next && session().… · [reviewed contract](#b0009) |
| [B0010 · 47–47](../../../../../tests/unit/durable_pipeline_test.cpp#L47) | Callable definition: void retry(bool pending=true) | calls recover · [reviewed contract](#b0010) |
| [B0011 · 48–48](../../../../../tests/unit/durable_pipeline_test.cpp#L48) | Closes surrounding scope/type. |  · [reviewed contract](#b0011) |
| [B0012 · 49–52](../../../../../tests/unit/durable_pipeline_test.cpp#L49) | Callable definition: std::size_t steps(bool indexed) | calls f, offer, begin, session; returns count; 1 loop sites · [reviewed contract](#b0012) |
| [B0013 · 53–62](../../../../../tests/unit/durable_pipeline_test.cpp#L53) | Callable definition: void cancellations(bool indexed) | calls steps, f, offer, begin; guard bool hidden=false;try{static_cast&lt;void&gt;(f.session().deliver_local_epoch());}catch(const Error&){hid…; 2 loop sites · [reviewed contract](#b0013) |
| [B0014 · 63–74](../../../../../tests/unit/durable_pipeline_test.cpp#L63) | Callable definition: void allocations(bool indexed) | calls f, offer, begin, finish; guard check(failed,"durable fan-out allocation fault missed");f.unchanged();check(typed::rows(f.session()…; 1 loop sites · [reviewed contract](#b0014) |
| [B0015 · 75–84](../../../../../tests/unit/durable_pipeline_test.cpp#L75) | Callable definition: void crashes(bool indexed) | calls steps, f, reset, fork; guard Pipeline f(indexed);f.fixture.query.session.reset();const auto child=::fork();check(child&gt;=0,"durab…; 2 loop sites · [reviewed contract](#b0015) |
| [B0016 · 85–85](../../../../../tests/unit/durable_pipeline_test.cpp#L85) | Type/record definition: enum class WriterPhase |  · [reviewed contract](#b0016) |
| [B0017 · 86–92](../../../../../tests/unit/durable_pipeline_test.cpp#L86) | Type/record definition: struct Hook | returns value; h.decision&lt;recovery::journal::testing::FileDecision&gt;(event.after) · [reviewed contract](#b0017) |
| [B0018 · 93–96](../../../../../tests/unit/durable_pipeline_test.cpp#L93) | Type/record definition: struct Installed |  · [reviewed contract](#b0018) |
| [B0019 · 97–99](../../../../../tests/unit/durable_pipeline_test.cpp#L97) | Callable definition: void prepare(Pipeline& f,WriterPhase phase) | calls offer, begin, session, step; 1 loop sites · [reviewed contract](#b0019) |
| [B0020 · 100–100](../../../../../tests/unit/durable_pipeline_test.cpp#L100) | Callable definition: void perform(Pipeline& f,WriterPhase phase) | calls begin, session, commit, deliver_local_epoch · [reviewed contract](#b0020) |
| [B0021 · 101–101](../../../../../tests/unit/durable_pipeline_test.cpp#L101) | Callable definition: Hook trace(bool indexed,WriterPhase phase) | calls f, prepare, installed, perform; returns h · [reviewed contract](#b0021) |
| [B0022 · 102–104](../../../../../tests/unit/durable_pipeline_test.cpp#L102) | Callable definition: std::pair&lt;bool,bool&gt; persisted(const Pipeline& f) | calls generation_test::path, contents, recovery::journal::scan, check; guard const auto log=generation_test::path(f.fixture.query.name,2,".wal"),bytes=contents(log);const auto …; returns {state.physical_sequence==3,state.pending.has_value()} · [reviewed contract](#b0022) |
| [B0023 · 105–117](../../../../../tests/unit/durable_pipeline_test.cpp#L105) | Callable definition: void writer_failures(bool indexed) | calls trace, f, prepare, installed; guard check(failed && f.session().journal_state().recovery_required,"writer fault allowed uncertain conti…; 3 loop sites · [reviewed contract](#b0023) |
| [B0024 · 118–133](../../../../../tests/unit/durable_pipeline_test.cpp#L118) | Callable definition: void sink_reopen(bool indexed) | calls trace, f, prepare, installed; guard const auto state=f.session().local_sink_state();check(failed && state.recovery_required && state.ve…; 3 loop sites · [reviewed contract](#b0024) |
| [B0025 · 134–146](../../../../../tests/unit/durable_pipeline_test.cpp#L134) | Callable definition: void io_crashes(bool indexed) | calls trace, f, reset, fork; guard Pipeline f(indexed);f.fixture.query.session.reset();const auto child=::fork();check(child&gt;=0,"durab…; 3 loop sites · [reviewed contract](#b0025) |
| [B0026 · 147–147](../../../../../tests/unit/durable_pipeline_test.cpp#L147) | Closes surrounding scope/type. |  · [reviewed contract](#b0026) |
| [B0027 · 148–148](../../../../../tests/unit/durable_pipeline_test.cpp#L148) | Callable definition: int main(int argc,char** argv) | calls check, std::string_view, crashes, io_crashes; guard int main(int argc,char** argv){try{check(argc==2,"expected durable pipeline mode");for(const bool i…; returns 1; 1 loop sites · [reviewed contract](#b0027) |

## B0001

[Lines 1–17](../../../../../tests/unit/durable_pipeline_test.cpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L1-L17:sha256:5910796eee34d1394ef28e31d5ca820c1e129e03384ae92c1b853a0a6a9297f1
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Prepare durable_pipeline_test.cpp: include "local_sink_fixture.hpp", "crown/api/error.hpp", "journal_file_probe.hpp", "local_sink_probe.hpp", &lt;cerrno&gt;, &lt;sys/wait.h&gt;; bind local aliases/name imports; declare fixture state/default initializers. |
| inputs / outputs | Compiler-visible dependencies, names and the recorded declarations in; declarations available to the following fixture/CLI/example definitions out. The source span lists the exact member/global names, types and initial values; initializers run when the enclosing object/program/thread is initialized. |
| invariants | Declarations are scoped to this source/header and its selected ABI. Included code has its own effects; names and editable fixture values do not confer proof, admission or publication authority. |
| ownership | Aliases/includes do not create a query owner. Pointers/references/views are non-owning. Containers own their elements, which can themselves be borrowed pointers or numeric IDs. Only documented owning shared-control handles retain controls; IDs/slot-handle values do not independently keep an arena/runtime alive. |
| failure | Missing headers, ill-formed names/types, failed static assertions or active #error directives stop compilation. No runtime rejection/rollback mechanism is implemented by aliases or function prototypes. Actual object construction and explicit initializers keep the failure contracts of their declared types/called helpers; this card supplies no extra rollback. |
| cost | Preprocessing and type/constraint instantiation cost compilation. Alias/prototype syntax does not invoke the declared operation; any included definitions keep their own initialization effects. Member/global initialization follows the shown C++ types and expressions when its enclosing object/program is constructed; owning containers can allocate. Default member declarations do not themselves instantiate a fixture. Copies and teardown follow the owning types. |
| Design | [tests/unit/durable_pipeline_test.cpp](../../../../../tests/unit/durable_pipeline_test.cpp), [docs/session-journal.md](../../../../session-journal.md), [docs/code_review.md](../../../../code_review.md) |

## B0002

[Lines 18–22](../../../../../tests/unit/durable_pipeline_test.cpp#L18); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
explicit Pipeline(bool indexed):fixture(indexed,1),program(CompiledProgram::standalone(fixture.query.test.plan))
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Create a self-join pipeline fixture from two already committed epochs and rotate its selected durable generation. |
| inputs / outputs | The indexed flag selects the fixture backend; the constructor stores a compiled program, independent current database/oracle output, expected next fan-out, and pre-attempt sink prefix. |
| invariants | The next event is chosen to exercise two aliases and new-new output; the baseline committed/source/sink boundary is physical sequence 2, generation 2. |
| ownership | Fixture owns the QuerySession through its nested local-sink fixture; CompiledProgram and ordinary expected row sets are separate owners; the saved prefix is a test-side byte copy. |
| failure | Fixture setup assertions reject an unexpected fan-out shape or a failed commit/delivery before any case begins. |
| cost | Exactly two initial fixture updates plus one rotation; native index/query/storage allocations are charged to the session account, while database/oracle sets and prefix copies are test-side allocations. |
| Design | [tests/unit/durable_pipeline_test.cpp](../../../../../tests/unit/durable_pipeline_test.cpp), [docs/session-journal.md](../../../../session-journal.md), [docs/native-replay.md](../../../../native-replay.md), [docs/local-sink.md](../../../../local-sink.md), [docs/checkpoints.md § Atomic durable checkpoint files](../../../../checkpoints.md), [src/runtime/replay.cpp](../../../../../src/runtime/replay.cpp), [src/recovery/journal.cpp](../../../../../src/recovery/journal.cpp), [src/recovery/journal_file.cpp](../../../../../src/recovery/journal_file.cpp), [src/recovery/local_sink.cpp](../../../../../src/recovery/local_sink.cpp), [tests/support/local_sink_fixture.hpp](../../../../../tests/support/local_sink_fixture.hpp) |

## B0003

[Lines 23–23](../../../../../tests/unit/durable_pipeline_test.cpp#L23); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
QuerySession& session()
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Return the currently attached session from the pipeline fixture. |
| inputs / outputs | Returns QuerySession& borrowed from fixture.query.session. |
| invariants | The reference is valid only until the owning fixture resets or destroys that unique session owner. |
| ownership | The fixture retains descriptor, writer, sink, and account lifetimes; this accessor transfers none of them. |
| failure | A use after fixture restore/reset would be dangling; callers obtain it immediately before an operation. |
| cost | Constant-time reference access; no query or test allocation. |
| Design | [tests/unit/durable_pipeline_test.cpp](../../../../../tests/unit/durable_pipeline_test.cpp), [docs/session-journal.md](../../../../session-journal.md), [docs/native-replay.md](../../../../native-replay.md), [docs/local-sink.md](../../../../local-sink.md), [docs/checkpoints.md § Atomic durable checkpoint files](../../../../checkpoints.md), [src/runtime/replay.cpp](../../../../../src/runtime/replay.cpp), [src/recovery/journal.cpp](../../../../../src/recovery/journal.cpp), [src/recovery/journal_file.cpp](../../../../../src/recovery/journal_file.cpp), [src/recovery/local_sink.cpp](../../../../../src/recovery/local_sink.cpp), [tests/support/local_sink_fixture.hpp](../../../../../tests/support/local_sink_fixture.hpp) |

## B0004

[Lines 24–24](../../../../../tests/unit/durable_pipeline_test.cpp#L24); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void offer()
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Queue the third self-join input with its source position for the next pipeline attempt. |
| inputs / outputs | Offers the fixture's third PhysicalSetUpdate through the typed-input helper at sequence 3 and feed offset 30. |
| invariants | Admission alone does not prepare/commit the event; queue ownership moves only after accepted admission. |
| ownership | On acceptance the native queue owns the copied event; the fixture retains the source update used to construct it. |
| failure | The shared enqueue assertion fails if admission rejects or leaves the offered batch nonempty. |
| cost | One event crosses the DTO-to-native queue boundary under the query account; the one-item batch and source descriptor are bounded test inputs. |
| Design | [tests/unit/durable_pipeline_test.cpp](../../../../../tests/unit/durable_pipeline_test.cpp), [docs/session-journal.md](../../../../session-journal.md), [docs/native-replay.md](../../../../native-replay.md), [docs/local-sink.md](../../../../local-sink.md), [docs/checkpoints.md § Atomic durable checkpoint files](../../../../checkpoints.md), [src/runtime/replay.cpp](../../../../../src/runtime/replay.cpp), [src/recovery/journal.cpp](../../../../../src/recovery/journal.cpp), [src/recovery/journal_file.cpp](../../../../../src/recovery/journal_file.cpp), [src/recovery/local_sink.cpp](../../../../../src/recovery/local_sink.cpp), [tests/support/local_sink_fixture.hpp](../../../../../tests/support/local_sink_fixture.hpp) |

## B0005

[Lines 25–25](../../../../../tests/unit/durable_pipeline_test.cpp#L25); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void begin()
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Require that the queued third input is available for native processing. |
| inputs / outputs | Calls begin_next on the fixture's session and returns only when the session reports an input. |
| invariants | It proves head acquisition, not engine preparation, durable decision, commit, or sink delivery. |
| ownership | The session retains its private native pending input; this helper borrows the session. |
| failure | A missing event raises the test diagnostic before the caller proceeds. |
| cost | One session state transition over a single queued event; native preparation costs are charged to the query account in later step/commit calls. |
| Design | [tests/unit/durable_pipeline_test.cpp](../../../../../tests/unit/durable_pipeline_test.cpp), [docs/session-journal.md](../../../../session-journal.md), [docs/native-replay.md](../../../../native-replay.md), [docs/local-sink.md](../../../../local-sink.md), [docs/checkpoints.md § Atomic durable checkpoint files](../../../../checkpoints.md), [src/runtime/replay.cpp](../../../../../src/runtime/replay.cpp), [src/recovery/journal.cpp](../../../../../src/recovery/journal.cpp), [src/recovery/journal_file.cpp](../../../../../src/recovery/journal_file.cpp), [src/recovery/local_sink.cpp](../../../../../src/recovery/local_sink.cpp), [tests/support/local_sink_fixture.hpp](../../../../../tests/support/local_sink_fixture.hpp) |

## B0006

[Lines 26–26](../../../../../tests/unit/durable_pipeline_test.cpp#L26); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void restore()
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Replace the fixture session with root-selected generation recovery that validates the local sink. |
| inputs / outputs | Drops the current QuerySession and calls restore_generation_with_local_sink with the compiled binding, root name, recovery options, sink path, and sink options. |
| invariants | The old owner is destroyed before reopening; the restored owner is the actual native replay result, not a copied status/report. |
| ownership | The unique_ptr owns new descriptors, locks, receiving account, replay state, and sink attachment; the fixture continues to own its test paths and program. |
| failure | Factory rejection propagates; the fixture does not resume from the old session after failed restore. |
| cost | Destruction releases the old owner before native reconstruction; replay and sink validation allocate in the new query account, plus bounded test path/output copies. |
| Design | [tests/unit/durable_pipeline_test.cpp](../../../../../tests/unit/durable_pipeline_test.cpp), [docs/session-journal.md](../../../../session-journal.md), [docs/native-replay.md](../../../../native-replay.md), [docs/local-sink.md](../../../../local-sink.md), [docs/checkpoints.md § Atomic durable checkpoint files](../../../../checkpoints.md), [src/runtime/replay.cpp](../../../../../src/runtime/replay.cpp), [src/recovery/journal.cpp](../../../../../src/recovery/journal.cpp), [src/recovery/journal_file.cpp](../../../../../src/recovery/journal_file.cpp), [src/recovery/local_sink.cpp](../../../../../src/recovery/local_sink.cpp), [tests/support/local_sink_fixture.hpp](../../../../../tests/support/local_sink_fixture.hpp) |

## B0007

[Lines 27–30](../../../../../tests/unit/durable_pipeline_test.cpp#L27); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void unchanged()
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Check that a private fan-out attempt has not changed committed native/source state or durable sink bytes. |
| inputs / outputs | Reads session status/progress/sink state and compares them with the sequence-2 fixture baseline and copied prefix. |
| invariants | The check establishes no public progress or persisted file growth; it does not inspect every private allocator byte or prove process-crash durability. |
| ownership | Session owns live native/file state; the fixture owns the expected source offsets and prefix copy. |
| failure | Any changed physical/source sequence, sink sequence, or sink byte prefix fails the case. |
| cost | Reads bounded fixed reports and reads the small test file into an ordinary string; native state is not copied by this helper. |
| Design | [tests/unit/durable_pipeline_test.cpp](../../../../../tests/unit/durable_pipeline_test.cpp), [docs/session-journal.md](../../../../session-journal.md), [docs/native-replay.md](../../../../native-replay.md), [docs/local-sink.md](../../../../local-sink.md), [docs/checkpoints.md § Atomic durable checkpoint files](../../../../checkpoints.md), [src/runtime/replay.cpp](../../../../../src/runtime/replay.cpp), [src/recovery/journal.cpp](../../../../../src/recovery/journal.cpp), [src/recovery/journal_file.cpp](../../../../../src/recovery/journal_file.cpp), [src/recovery/local_sink.cpp](../../../../../src/recovery/local_sink.cpp), [tests/support/local_sink_fixture.hpp](../../../../../tests/support/local_sink_fixture.hpp) |

## B0008

[Lines 31–40](../../../../../tests/unit/durable_pipeline_test.cpp#L31); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void recover(bool committed,bool pending)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Recover and finish one self-join fan-out according to whether its native decision and input frame survived. |
| inputs / outputs | Accepts the expected committed/pending booleans; performs real sink-aware generation restore, checks rows/source/output, starts and retries missing work, then validates the next event and retirement restart. |
| invariants | Only complete native decisions advance physical/source state; a retained uncommitted input is reused rather than reoffered; output compares the complete canonical epoch. |
| ownership | Each recovered QuerySession owns one new receiving account and attached sink; typed::rows and expected output are ordinary export copies; path/file copies belong to the test fixture. |
| failure | Mismatched pending/commit boundary, source progress, rows, local output, retirement selection, or next event fails the assertion; unknown file outcomes must be resolved by actual factory recovery. |
| cost | At most the fixture's one pending event and two post-base physical events are replayed; native replay allocations use the receiving account, while full-row oracle/difference sets and file contents are test-side copies. |
| Design | [tests/unit/durable_pipeline_test.cpp](../../../../../tests/unit/durable_pipeline_test.cpp), [docs/session-journal.md](../../../../session-journal.md), [docs/native-replay.md](../../../../native-replay.md), [docs/local-sink.md](../../../../local-sink.md), [docs/checkpoints.md § Atomic durable checkpoint files](../../../../checkpoints.md), [src/runtime/replay.cpp](../../../../../src/runtime/replay.cpp), [src/recovery/journal.cpp](../../../../../src/recovery/journal.cpp), [src/recovery/journal_file.cpp](../../../../../src/recovery/journal_file.cpp), [src/recovery/local_sink.cpp](../../../../../src/recovery/local_sink.cpp), [tests/support/local_sink_fixture.hpp](../../../../../tests/support/local_sink_fixture.hpp) |

## B0009

[Lines 41–46](../../../../../tests/unit/durable_pipeline_test.cpp#L41); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void next_and_retire(bool queued)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Commit and deliver the next queued or direct fixture event, then retire and reopen selected history. |
| inputs / outputs | Applies update 3 to the independent database; either consumes a queued event or calls the fixture writer; delivers, compares physical sequence 4 and canonical output, retires history, and restores again. |
| invariants | The same previous sink receipt and source frontier must survive retirement/reopen; the two branches differ only in how the next input reaches the session. |
| ownership | Fixture/session retains the durable owners; database and difference rows are caller-owned oracle values; returned epoch rows are exported copies. |
| failure | Wrong next sequence, output, source position, selected first generation, receipt, or restored relation fails. |
| cost | One event and one epoch are processed. Native writer/recovery costs use the session account; the independent database, sets, receipt report, and file reads are bounded test copies. |
| Design | [tests/unit/durable_pipeline_test.cpp](../../../../../tests/unit/durable_pipeline_test.cpp), [docs/session-journal.md](../../../../session-journal.md), [docs/native-replay.md](../../../../native-replay.md), [docs/local-sink.md](../../../../local-sink.md), [docs/checkpoints.md § Atomic durable checkpoint files](../../../../checkpoints.md), [src/runtime/replay.cpp](../../../../../src/runtime/replay.cpp), [src/recovery/journal.cpp](../../../../../src/recovery/journal.cpp), [src/recovery/journal_file.cpp](../../../../../src/recovery/journal_file.cpp), [src/recovery/local_sink.cpp](../../../../../src/recovery/local_sink.cpp), [tests/support/local_sink_fixture.hpp](../../../../../tests/support/local_sink_fixture.hpp) |

## B0010

[Lines 47–47](../../../../../tests/unit/durable_pipeline_test.cpp#L47); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void retry(bool pending=true)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Run recovery after a simulated input/commit state by using the no-commit recovery branch. |
| inputs / outputs | Calls recover(false,pending), where the caller records whether the original input frame remains in the selected journal. |
| invariants | The pending flag selects reuse-versus-offer; this helper does not infer it from a caller-authored status report. |
| ownership | State ownership and failure behavior are inherited from recover; the boolean is a test expectation only. |
| failure | Any disagreement with the actual selected log or native reconstruction fails downstream checks. |
| cost | One bounded recovery scenario using the fixture's single outstanding event. |
| Design | [tests/unit/durable_pipeline_test.cpp](../../../../../tests/unit/durable_pipeline_test.cpp), [docs/session-journal.md](../../../../session-journal.md), [docs/native-replay.md](../../../../native-replay.md), [docs/local-sink.md](../../../../local-sink.md), [docs/checkpoints.md § Atomic durable checkpoint files](../../../../checkpoints.md), [src/runtime/replay.cpp](../../../../../src/runtime/replay.cpp), [src/recovery/journal.cpp](../../../../../src/recovery/journal.cpp), [src/recovery/journal_file.cpp](../../../../../src/recovery/journal_file.cpp), [src/recovery/local_sink.cpp](../../../../../src/recovery/local_sink.cpp), [tests/support/local_sink_fixture.hpp](../../../../../tests/support/local_sink_fixture.hpp) |

## B0011

[Lines 48–48](../../../../../tests/unit/durable_pipeline_test.cpp#L48); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L48-L48:sha256:aa1d1a63390229c798347e83a0405441c9400035284ad168c1bf6cdf1d70a370
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Close the recorded declaration scopes in durable_pipeline_test.cpp: struct Pipeline. |
| inputs / outputs | Preceding namespace, type or initializer declarations in; completed lexical boundary out. |
| invariants | Brace-opening context is recorded in root-scope-context-v1.json. These are declaration/initializer boundaries, not an independent update, validation or recovery operation. |
| ownership | Enclosing objects and borrowed fields keep their declared ownership. This punctuation creates no new owner. |
| failure | Malformed scope syntax is a compile error. Any initializer/constructor failure belongs to the enclosing object declaration. |
| cost | No separate loop, guard or engine call is introduced by the delimiter; enclosing initialization and object lifetime still have their actual costs. |
| Design | [tests/unit/durable_pipeline_test.cpp](../../../../../tests/unit/durable_pipeline_test.cpp), [docs/session-journal.md](../../../../session-journal.md), [docs/code_review.md](../../../../code_review.md) |

## B0012

[Lines 49–52](../../../../../tests/unit/durable_pipeline_test.cpp#L49); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::size_t steps(bool indexed)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Calibrate the finite count of private self-join steps needed before native preparation completes. |
| inputs / outputs | Creates the baseline pipeline, offers/begins its next event, and returns the first step count yielding DeltaStep::prepared. |
| invariants | The calibration stops at 10,000 calls and supplies loop bounds to the prefix sweep; it does not claim general query complexity. |
| ownership | Each temporary fixture owns its own session/file state and is destroyed on return. |
| failure | Exhausting the explicit step bound throws instead of allowing an unbounded calibration loop. |
| cost | At most 10,000 step attempts for a fixed fixture; actual native support/engine requests remain account-funded. |
| Design | [tests/unit/durable_pipeline_test.cpp](../../../../../tests/unit/durable_pipeline_test.cpp), [docs/session-journal.md](../../../../session-journal.md), [docs/native-replay.md](../../../../native-replay.md), [docs/local-sink.md](../../../../local-sink.md), [docs/checkpoints.md § Atomic durable checkpoint files](../../../../checkpoints.md), [src/runtime/replay.cpp](../../../../../src/runtime/replay.cpp), [src/recovery/journal.cpp](../../../../../src/recovery/journal.cpp), [src/recovery/journal_file.cpp](../../../../../src/recovery/journal_file.cpp), [src/recovery/local_sink.cpp](../../../../../src/recovery/local_sink.cpp), [tests/support/local_sink_fixture.hpp](../../../../../tests/support/local_sink_fixture.hpp) |

## B0013

[Lines 53–62](../../../../../tests/unit/durable_pipeline_test.cpp#L53); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void cancellations(bool indexed)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Check every private self-join prefix for invisibility, pause/stop rollback, and restart recovery. |
| inputs / outputs | For both backend choices, runs prefixes from zero through the calibrated prepared count, then tests sink/output rejection, stop rollback, and recovery. |
| invariants | Private alias fan-out must not reach output/sink before commit; cancellation preserves the prior logical rows and recovery later completes one whole epoch. |
| ownership | Each iteration constructs a fresh filesystem/query owner; source fixture and test oracle rows live independently. |
| failure | Unexpected output visibility, changed prefix, incomplete rollback, or wrong recovery result fails immediately. |
| cost | Prefix count is bounded by the calibrated step count plus one; each prefix performs actual native cancellation/replay and bounded oracle/file comparisons. |
| Design | [tests/unit/durable_pipeline_test.cpp](../../../../../tests/unit/durable_pipeline_test.cpp), [docs/session-journal.md](../../../../session-journal.md), [docs/native-replay.md](../../../../native-replay.md), [docs/local-sink.md](../../../../local-sink.md), [docs/checkpoints.md § Atomic durable checkpoint files](../../../../checkpoints.md), [src/runtime/replay.cpp](../../../../../src/runtime/replay.cpp), [src/recovery/journal.cpp](../../../../../src/recovery/journal.cpp), [src/recovery/journal_file.cpp](../../../../../src/recovery/journal_file.cpp), [src/recovery/local_sink.cpp](../../../../../src/recovery/local_sink.cpp), [tests/support/local_sink_fixture.hpp](../../../../../tests/support/local_sink_fixture.hpp) |

## B0014

[Lines 63–74](../../../../../tests/unit/durable_pipeline_test.cpp#L63); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void allocations(bool indexed)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Inject each measured C++ replacement-new failure in the private native fan-out attempt and recover the retained prefix. |
| inputs / outputs | Counts calls under the test replacement operators, then fails at each observed ordinal for fresh fixtures and checks unchanged state, pending frame, descriptor release, and recovery. |
| invariants | The test support defines scalar/array, aligned, and nothrow replacement forms; the seam does not inject direct malloc/realloc or MemoryAccount quota failures, and is not a complete OS allocation fault model. |
| ownership | The fresh session owns native journal/sink descriptors and charged state; each fault scope borrows its fixture; destroying the owner must release descriptors before recovery. |
| failure | Every counted throwing cut must produce bad_alloc without publishing partial aliases or durable sink output; pending input is recovered rather than duplicated. |
| cost | The loop is bounded by the measured replacement-new calls for this event. Actual native allocations use the query account; test strings/rows and descriptor enumeration are not query-account charges, and libc calls that bypass the replacements are outside this injected seam. |
| Design | [tests/unit/durable_pipeline_test.cpp](../../../../../tests/unit/durable_pipeline_test.cpp), [docs/session-journal.md](../../../../session-journal.md), [docs/native-replay.md](../../../../native-replay.md), [docs/local-sink.md](../../../../local-sink.md), [docs/checkpoints.md § Atomic durable checkpoint files](../../../../checkpoints.md), [src/runtime/replay.cpp](../../../../../src/runtime/replay.cpp), [src/recovery/journal.cpp](../../../../../src/recovery/journal.cpp), [src/recovery/journal_file.cpp](../../../../../src/recovery/journal_file.cpp), [src/recovery/local_sink.cpp](../../../../../src/recovery/local_sink.cpp), [tests/support/local_sink_fixture.hpp](../../../../../tests/support/local_sink_fixture.hpp), [tests/support/index_allocation.hpp](../../../../../tests/support/index_allocation.hpp) |

## B0015

[Lines 75–84](../../../../../tests/unit/durable_pipeline_test.cpp#L75); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void crashes(bool indexed)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Fork process exits at every public native preparation prefix and verify the prior durable sink boundary remains recoverable. |
| inputs / outputs | Uses the calibrated step count, a child restore/start/offer, and _exit(77) after selected step prefixes; parent retries actual factory recovery. |
| invariants | This is process termination at selected API prefixes, not power loss or hardware/filesystem fault simulation; no partial self-join epoch may be visible. |
| ownership | Fork duplicates the parent's file namespace state; child and parent have separate process memory, while files are shared; the parent fixture owns subsequent validation. |
| failure | Any child exit other than the configured code, changed sink prefix, or wrong recovery fails. |
| cost | A bounded prefix range through count+1 for each backend; process startup and actual native replay dominate, with no unbounded loop. |
| Design | [tests/unit/durable_pipeline_test.cpp](../../../../../tests/unit/durable_pipeline_test.cpp), [docs/session-journal.md](../../../../session-journal.md), [docs/native-replay.md](../../../../native-replay.md), [docs/local-sink.md](../../../../local-sink.md), [docs/checkpoints.md § Atomic durable checkpoint files](../../../../checkpoints.md), [src/runtime/replay.cpp](../../../../../src/runtime/replay.cpp), [src/recovery/journal.cpp](../../../../../src/recovery/journal.cpp), [src/recovery/journal_file.cpp](../../../../../src/recovery/journal_file.cpp), [src/recovery/local_sink.cpp](../../../../../src/recovery/local_sink.cpp), [tests/support/local_sink_fixture.hpp](../../../../../tests/support/local_sink_fixture.hpp) |

## B0016

[Lines 85–85](../../../../../tests/unit/durable_pipeline_test.cpp#L85); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
enum class WriterPhase
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Name the three writer fault seams exercised by the durable pipeline suite. |
| inputs / outputs | Enumerates input append, decision append, and sink publication phases; no callable behavior is attached to the enum. |
| invariants | The tests choose one file owner per phase and install the matching hook; the labels do not imply identical commit semantics. |
| ownership | The enum is a by-value test selector with no retained resource. |
| failure | An unhandled enum branch would leave the relevant test action unperformed and is caught by fixture assertions. |
| cost | Constant-size selector; no runtime allocation. |
| Design | [tests/unit/durable_pipeline_test.cpp](../../../../../tests/unit/durable_pipeline_test.cpp), [docs/session-journal.md](../../../../session-journal.md), [docs/native-replay.md](../../../../native-replay.md), [docs/local-sink.md](../../../../local-sink.md), [docs/checkpoints.md § Atomic durable checkpoint files](../../../../checkpoints.md), [src/runtime/replay.cpp](../../../../../src/runtime/replay.cpp), [src/recovery/journal.cpp](../../../../../src/recovery/journal.cpp), [src/recovery/journal_file.cpp](../../../../../src/recovery/journal_file.cpp), [src/recovery/local_sink.cpp](../../../../../src/recovery/local_sink.cpp), [tests/support/local_sink_fixture.hpp](../../../../../tests/support/local_sink_fixture.hpp) |

## B0017

[Lines 86–92](../../../../../tests/unit/durable_pipeline_test.cpp#L86); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct Hook
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Record before/after journal or sink syscall positions and inject error or process exit at a chosen ordinal. |
| inputs / outputs | The noexcept callbacks count actual hook events, may _exit(77), and return EIO before/after the selected journal/sink operation. |
| invariants | Callbacks use fixed scalar state; event memory and Hook context are borrowed; a post-effect error can leave a complete durable frame/epoch visible. |
| ownership | The caller owns Hook until the hook is cleared; static callback pointers do not own the context. |
| failure | A configured hook can terminate the child or inject one error; out-of-range event counts are caught by the caller's measured trace. |
| cost | Each callback performs constant bounded work and no dynamic allocation; the kernel operation is the real journal/sink I/O, not an emulation. |
| Design | [tests/unit/durable_pipeline_test.cpp](../../../../../tests/unit/durable_pipeline_test.cpp), [docs/session-journal.md](../../../../session-journal.md), [docs/native-replay.md](../../../../native-replay.md), [docs/local-sink.md](../../../../local-sink.md), [docs/checkpoints.md § Atomic durable checkpoint files](../../../../checkpoints.md), [src/runtime/replay.cpp](../../../../../src/runtime/replay.cpp), [src/recovery/journal.cpp](../../../../../src/recovery/journal.cpp), [src/recovery/journal_file.cpp](../../../../../src/recovery/journal_file.cpp), [src/recovery/local_sink.cpp](../../../../../src/recovery/local_sink.cpp), [tests/support/local_sink_fixture.hpp](../../../../../tests/support/local_sink_fixture.hpp) |

## B0018

[Lines 93–96](../../../../../tests/unit/durable_pipeline_test.cpp#L93); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct Installed
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Install the selected thread-local journal or sink hook for one lexical operation and clear both on scope exit. |
| inputs / outputs | Construction takes Hook& and phase; destruction clears journal and sink callbacks regardless of the selected phase. |
| invariants | The callback context is borrowed and must outlive Installed; install/clear do not transfer ownership or make hooks process-global. |
| ownership | Caller owns Hook, while Installed owns only the scoped registration lifetime. |
| failure | RAII cleanup runs on C++ exception exit; _exit bypasses destructors by design in crash cases. |
| cost | Two callback setter operations; no fixture or query allocation. |
| Design | [tests/unit/durable_pipeline_test.cpp](../../../../../tests/unit/durable_pipeline_test.cpp), [docs/session-journal.md](../../../../session-journal.md), [docs/native-replay.md](../../../../native-replay.md), [docs/local-sink.md](../../../../local-sink.md), [docs/checkpoints.md § Atomic durable checkpoint files](../../../../checkpoints.md), [src/runtime/replay.cpp](../../../../../src/runtime/replay.cpp), [src/recovery/journal.cpp](../../../../../src/recovery/journal.cpp), [src/recovery/journal_file.cpp](../../../../../src/recovery/journal_file.cpp), [src/recovery/local_sink.cpp](../../../../../src/recovery/local_sink.cpp), [tests/support/local_sink_fixture.hpp](../../../../../tests/support/local_sink_fixture.hpp) |

## B0019

[Lines 97–99](../../../../../tests/unit/durable_pipeline_test.cpp#L97); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void prepare(Pipeline& f,WriterPhase phase)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Place one input/decision/sink operation at its intended native transaction boundary before fault tracing. |
| inputs / outputs | Offers input for all phases; decision and sink phases additionally begin/step to prepared; sink phase commits the journal decision before delivery. |
| invariants | The helper distinguishes input persistence, physical decision, and sink acknowledgment ordering; it does not deliver the sink epoch itself. |
| ownership | Pipeline owns session and output spool; any Prepared engine state remains inside the session until perform/fixture teardown. |
| failure | An input/preparation failure propagates and invalidates the intended hook boundary rather than silently continuing. |
| cost | One bounded event plus finite preparation steps; native spool and journal work consume the query account. |
| Design | [tests/unit/durable_pipeline_test.cpp](../../../../../tests/unit/durable_pipeline_test.cpp), [docs/session-journal.md](../../../../session-journal.md), [docs/native-replay.md](../../../../native-replay.md), [docs/local-sink.md](../../../../local-sink.md), [docs/checkpoints.md § Atomic durable checkpoint files](../../../../checkpoints.md), [src/runtime/replay.cpp](../../../../../src/runtime/replay.cpp), [src/recovery/journal.cpp](../../../../../src/recovery/journal.cpp), [src/recovery/journal_file.cpp](../../../../../src/recovery/journal_file.cpp), [src/recovery/local_sink.cpp](../../../../../src/recovery/local_sink.cpp), [tests/support/local_sink_fixture.hpp](../../../../../tests/support/local_sink_fixture.hpp) |

## B0020

[Lines 100–100](../../../../../tests/unit/durable_pipeline_test.cpp#L100); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void perform(Pipeline& f,WriterPhase phase)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Execute exactly the selected input, decision, or sink action after preparation. |
| inputs / outputs | Calls begin_next, commit, or deliver_local_epoch according to WriterPhase. |
| invariants | No fallback phase is performed; the returned sink report is deliberately discarded by the test action. |
| ownership | The session owns the native pending/output state; this function borrows Pipeline and never moves its owner. |
| failure | Writer failures propagate to the phase-specific catcher. |
| cost | One public session operation; native/file allocation and I/O costs are charged by their actual owners. |
| Design | [tests/unit/durable_pipeline_test.cpp](../../../../../tests/unit/durable_pipeline_test.cpp), [docs/session-journal.md](../../../../session-journal.md), [docs/native-replay.md](../../../../native-replay.md), [docs/local-sink.md](../../../../local-sink.md), [docs/checkpoints.md § Atomic durable checkpoint files](../../../../checkpoints.md), [src/runtime/replay.cpp](../../../../../src/runtime/replay.cpp), [src/recovery/journal.cpp](../../../../../src/recovery/journal.cpp), [src/recovery/journal_file.cpp](../../../../../src/recovery/journal_file.cpp), [src/recovery/local_sink.cpp](../../../../../src/recovery/local_sink.cpp), [tests/support/local_sink_fixture.hpp](../../../../../tests/support/local_sink_fixture.hpp) |

## B0021

[Lines 101–101](../../../../../tests/unit/durable_pipeline_test.cpp#L101); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Hook trace(bool indexed,WriterPhase phase)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Measure a successful hook trace for one writer phase so later fault loops use actual syscall ordinals. |
| inputs / outputs | Builds a fresh fixture, prepares the selected phase, installs Hook, performs the operation, and returns its event count. |
| invariants | Only callbacks reached through the selected actual file API contribute; a zero trace is not fabricated into coverage. |
| ownership | Returned Hook is a plain fixed-size value; fixture/session/file owners die before return. |
| failure | Preparation or public writer errors abort calibration rather than being counted as a successful baseline. |
| cost | Bounded by actual syscall count for a single frame/epoch; no per-event heap allocation in Hook. |
| Design | [tests/unit/durable_pipeline_test.cpp](../../../../../tests/unit/durable_pipeline_test.cpp), [docs/session-journal.md](../../../../session-journal.md), [docs/native-replay.md](../../../../native-replay.md), [docs/local-sink.md](../../../../local-sink.md), [docs/checkpoints.md § Atomic durable checkpoint files](../../../../checkpoints.md), [src/runtime/replay.cpp](../../../../../src/runtime/replay.cpp), [src/recovery/journal.cpp](../../../../../src/recovery/journal.cpp), [src/recovery/journal_file.cpp](../../../../../src/recovery/journal_file.cpp), [src/recovery/local_sink.cpp](../../../../../src/recovery/local_sink.cpp), [tests/support/local_sink_fixture.hpp](../../../../../tests/support/local_sink_fixture.hpp) |

## B0022

[Lines 102–104](../../../../../tests/unit/durable_pipeline_test.cpp#L102); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::pair<bool,bool> persisted(const Pipeline& f)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Read the actual selected generation WAL and report whether physical epoch 3 committed and whether input remains pending. |
| inputs / outputs | Loads the journal bytes, scans them through the native journal parser, and returns the two observed booleans. |
| invariants | Only journal physical sequence 2 or 3 is accepted; pending state comes from the parsed prefix rather than the test's requested outcome. |
| ownership | The test-side contents string owns a copy; the parsed scan result is local; the journal file remains fixture-owned. |
| failure | Unexpected committed sequence fails before recovery can guess. |
| cost | Scans one bounded WAL copy; standard string/file buffering is test memory, not query-account replay storage. |
| Design | [tests/unit/durable_pipeline_test.cpp](../../../../../tests/unit/durable_pipeline_test.cpp), [docs/session-journal.md](../../../../session-journal.md), [docs/native-replay.md](../../../../native-replay.md), [docs/local-sink.md](../../../../local-sink.md), [docs/checkpoints.md § Atomic durable checkpoint files](../../../../checkpoints.md), [src/runtime/replay.cpp](../../../../../src/runtime/replay.cpp), [src/recovery/journal.cpp](../../../../../src/recovery/journal.cpp), [src/recovery/journal_file.cpp](../../../../../src/recovery/journal_file.cpp), [src/recovery/local_sink.cpp](../../../../../src/recovery/local_sink.cpp), [tests/support/local_sink_fixture.hpp](../../../../../tests/support/local_sink_fixture.hpp) |

## B0023

[Lines 105–117](../../../../../tests/unit/durable_pipeline_test.cpp#L105); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void writer_failures(bool indexed)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Fault every before/after input-frame and decision I/O callback and require native recovery after uncertain writer state. |
| inputs / outputs | Traces both journal phases, injects EIO at each syscall side, checks recovery_required/backpressure and old public boundary, then parses the actual WAL and sink-aware restores. |
| invariants | An error after an actual effect may mean the frame committed; only parsed native prefix decides. This suite does not claim durability across power failure. |
| ownership | Writer/file/session state is fixture-owned; fault Hook context is lexical; recovery creates an independent receiving session/account. |
| failure | Each fault must poison admission until the old owner is dropped and factory reconstruction succeeds with exactly one complete output. |
| cost | Loop bound is measured file callbacks times two sides and two phases. Native replay, query rows, output and sink buffers use their actual accounts; WAL strings and query oracle copies are outside. |
| Design | [tests/unit/durable_pipeline_test.cpp](../../../../../tests/unit/durable_pipeline_test.cpp), [docs/session-journal.md](../../../../session-journal.md), [docs/native-replay.md](../../../../native-replay.md), [docs/local-sink.md](../../../../local-sink.md), [docs/checkpoints.md § Atomic durable checkpoint files](../../../../checkpoints.md), [src/runtime/replay.cpp](../../../../../src/runtime/replay.cpp), [src/recovery/journal.cpp](../../../../../src/recovery/journal.cpp), [src/recovery/journal_file.cpp](../../../../../src/recovery/journal_file.cpp), [src/recovery/local_sink.cpp](../../../../../src/recovery/local_sink.cpp), [tests/support/local_sink_fixture.hpp](../../../../../tests/support/local_sink_fixture.hpp) |

## B0024

[Lines 118–133](../../../../../tests/unit/durable_pipeline_test.cpp#L118); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void sink_reopen(bool indexed)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Fault every sink syscall side and check poisoned backpressure, retained output/work, same-owner reopen, and exact retry. |
| inputs / outputs | For each measured sink event, injects EIO, queues one following input, makes repeated begin attempts, reopens the real sink file on the same session, then delivers/reads the epoch. |
| invariants | Failed delivery retains the whole committed native output and does not advance verified sequence; a visible complete epoch retries as duplicate, otherwise as published; queue admission remains blocked until acceptance. |
| ownership | QuerySession retains pending output, queue node, work counters and sink attachment; test Hook is scoped; read_local_epoch returns account-owned native rows copied to an ordinary output oracle. |
| failure | Unexpected acknowledgment, lost output, work refill, queue consumption, noncanonical duplicate, or wrong next update fails. |
| cost | Bounded by actual sink syscall count times two fault sides; actual sink buffers/decoded rows use the query account, while returned outputs/file bytes/oracle values are copies. |
| Design | [tests/unit/durable_pipeline_test.cpp](../../../../../tests/unit/durable_pipeline_test.cpp), [docs/session-journal.md](../../../../session-journal.md), [docs/native-replay.md](../../../../native-replay.md), [docs/local-sink.md](../../../../local-sink.md), [docs/checkpoints.md § Atomic durable checkpoint files](../../../../checkpoints.md), [src/runtime/replay.cpp](../../../../../src/runtime/replay.cpp), [src/recovery/journal.cpp](../../../../../src/recovery/journal.cpp), [src/recovery/journal_file.cpp](../../../../../src/recovery/journal_file.cpp), [src/recovery/local_sink.cpp](../../../../../src/recovery/local_sink.cpp), [tests/support/local_sink_fixture.hpp](../../../../../tests/support/local_sink_fixture.hpp) |

## B0025

[Lines 134–146](../../../../../tests/unit/durable_pipeline_test.cpp#L134); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void io_crashes(bool indexed)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Fork at every before/after journal-input, decision, and sink syscall callback and recover the actual shared files. |
| inputs / outputs | Measures one successful trace per phase, resets to the baseline, and child-exits at each real syscall boundary before/after the effect. |
| invariants | The parent distinguishes a complete persisted decision from a pending input by scanning the WAL and validates full native/output recovery; the run is a process-crash test, not a power-loss model. |
| ownership | Child callback holds a process-local Hook; files are shared with parent; parent fixture and later receiving session own subsequent checks. |
| failure | A missing callback, unexpected child exit, invalid file prefix, wrong result, or duplicate delivery fails. |
| cost | Finite event-count times two phases/sides across three file phases and two backend choices; actual native replay and ordinary test file copies are distinct costs. |
| Design | [tests/unit/durable_pipeline_test.cpp](../../../../../tests/unit/durable_pipeline_test.cpp), [docs/session-journal.md](../../../../session-journal.md), [docs/native-replay.md](../../../../native-replay.md), [docs/local-sink.md](../../../../local-sink.md), [docs/checkpoints.md § Atomic durable checkpoint files](../../../../checkpoints.md), [src/runtime/replay.cpp](../../../../../src/runtime/replay.cpp), [src/recovery/journal.cpp](../../../../../src/recovery/journal.cpp), [src/recovery/journal_file.cpp](../../../../../src/recovery/journal_file.cpp), [src/recovery/local_sink.cpp](../../../../../src/recovery/local_sink.cpp), [tests/support/local_sink_fixture.hpp](../../../../../tests/support/local_sink_fixture.hpp) |

## B0026

[Lines 147–147](../../../../../tests/unit/durable_pipeline_test.cpp#L147); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L147-L147:sha256:412ca345ccf75bf9c0806bce695be8de808b79984251a7a54d202cf6101dd451
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Close the recorded declaration scopes in durable_pipeline_test.cpp: namespace (anonymous). |
| inputs / outputs | Preceding namespace, type or initializer declarations in; completed lexical boundary out. |
| invariants | Brace-opening context is recorded in root-scope-context-v1.json. These are declaration/initializer boundaries, not an independent update, validation or recovery operation. |
| ownership | Enclosing objects and borrowed fields keep their declared ownership. This punctuation creates no new owner. |
| failure | Malformed scope syntax is a compile error. Any initializer/constructor failure belongs to the enclosing object declaration. |
| cost | No separate loop, guard or engine call is introduced by the delimiter; enclosing initialization and object lifetime still have their actual costs. |
| Design | [tests/unit/durable_pipeline_test.cpp](../../../../../tests/unit/durable_pipeline_test.cpp), [docs/session-journal.md](../../../../session-journal.md), [docs/code_review.md](../../../../code_review.md) |

## B0027

[Lines 148–148](../../../../../tests/unit/durable_pipeline_test.cpp#L148); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
int main(int argc,char** argv)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Select ordinary fault or process-crash durable-pipeline coverage for each storage backend. |
| inputs / outputs | Requires one mode argument, then runs indexed and reference modes; exactly \`crash\` selects fork cases, other strings select cancellation/allocation/writer/sink cases. |
| invariants | The local-sink integration fixture provides real generation and file-backed replay; this test does not exercise every QuerySession checkpoint file API overload. |
| ownership | Main owns all stack fixtures within called cases; process children are explicitly waited for in crash paths. |
| failure | Invalid argc or any failed invariant returns a failing process status with the diagnostic. |
| cost | Runs a finite selected matrix; each case's native and file work is separately bounded by its fixture/hook trace. |
| Design | [tests/unit/durable_pipeline_test.cpp](../../../../../tests/unit/durable_pipeline_test.cpp), [docs/session-journal.md](../../../../session-journal.md), [docs/native-replay.md](../../../../native-replay.md), [docs/local-sink.md](../../../../local-sink.md), [docs/checkpoints.md § Atomic durable checkpoint files](../../../../checkpoints.md), [src/runtime/replay.cpp](../../../../../src/runtime/replay.cpp), [src/recovery/journal.cpp](../../../../../src/recovery/journal.cpp), [src/recovery/journal_file.cpp](../../../../../src/recovery/journal_file.cpp), [src/recovery/local_sink.cpp](../../../../../src/recovery/local_sink.cpp), [tests/support/local_sink_fixture.hpp](../../../../../tests/support/local_sink_fixture.hpp) |
