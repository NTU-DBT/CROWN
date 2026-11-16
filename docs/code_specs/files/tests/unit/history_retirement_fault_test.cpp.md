# `tests/unit/history_retirement_fault_test.cpp` — block usage map

[Source](../../../../../tests/unit/history_retirement_fault_test.cpp) · [Source index](../../../README.md) · [Subsystem contracts](../../../subsystem_contracts.md) · [Reviewed primitives](../../../primitives.md)

Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection.

Snapshot SHA-256: `7c07afed25f036a8eb61a149bfd864f1ccf722fda007a8f2a83a0f002fb0c03e`. 108 lines partitioned into 18 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [tests](../../../subsystem_contracts.md#tests). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/code_review.md](../../../../code_review.md), [docs/reference_fuzz.md](../../../../reference_fuzz.md), [docs/task_ledger.md](../../../../task_ledger.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–12](../../../../../tests/unit/history_retirement_fault_test.cpp#L1) | Imports dependencies; declares namespace scope; declares aliases; declares values/defaults or compile-time conditions. |  · [reviewed contract](#b0001) |
| [B0002 · 13–13](../../../../../tests/unit/history_retirement_fault_test.cpp#L13) | Type/record definition: enum class Action |  · [reviewed contract](#b0002) |
| [B0003 · 14–17](../../../../../tests/unit/history_retirement_fault_test.cpp#L14) | declares types or opens a type body; declares values/defaults or compile-time conditions. |  · [reviewed contract](#b0003) |
| [B0004 · 18–18](../../../../../tests/unit/history_retirement_fault_test.cpp#L18) | Callable definition: void visit(bool done) noexcept | calls _exit · [reviewed contract](#b0004) |
| [B0005 · 19–19](../../../../../tests/unit/history_retirement_fault_test.cpp#L19) | Callable definition: template&lt;class D&gt; D decision(bool done) const noexcept | calls ; returns result · [reviewed contract](#b0005) |
| [B0006 · 20–34](../../../../../tests/unit/history_retirement_fault_test.cpp#L20) | Callable definition: static recovery::testing::GenerationDecision generation(const recovery::testing::GenerationEvent& event,void* context) noexcept | calls visit; returns result · [reviewed contract](#b0006) |
| [B0007 · 35–35](../../../../../tests/unit/history_retirement_fault_test.cpp#L35) | Callable definition: static recovery::testing::FileDecision checkpoint(const recovery::testing::FileEvent& event,void* context) noexcept | calls visit; returns h.decision&lt;recovery::testing::FileDecision&gt;(event.after) · [reviewed contract](#b0007) |
| [B0008 · 36–36](../../../../../tests/unit/history_retirement_fault_test.cpp#L36) | Callable definition: static jp::testing::FileDecision journal(const jp::testing::FileEvent& event,void* context) noexcept | calls visit; returns h.decision&lt;jp::testing::FileDecision&gt;(event.after) · [reviewed contract](#b0008) |
| [B0009 · 37–37](../../../../../tests/unit/history_retirement_fault_test.cpp#L37) | Callable definition: static sk::testing::Decision sink(const sk::testing::Event& event,void* context) noexcept | calls visit; returns h.decision&lt;sk::testing::Decision&gt;(event.after) · [reviewed contract](#b0009) |
| [B0010 · 38–38](../../../../../tests/unit/history_retirement_fault_test.cpp#L38) | Closes surrounding scope/type. |  · [reviewed contract](#b0010) |
| [B0011 · 39–42](../../../../../tests/unit/history_retirement_fault_test.cpp#L39) | Type/record definition: struct Installed |  · [reviewed contract](#b0011) |
| [B0012 · 43–60](../../../../../tests/unit/history_retirement_fault_test.cpp#L43) | Type/record definition: struct Saved | guard if(pending){Hook h;h.pause_cleanup=true;bool failed=false;{Installed installed(h);try{f.session-&gt;re…; returns f.restore(); {}; growth emplace_back; 4 loop sites · [reviewed contract](#b0012) |
| [B0013 · 61–61](../../../../../tests/unit/history_retirement_fault_test.cpp#L61) | Callable definition: Hook trace(Action action) | calls saved, owner, installed, perform; guard Hook trace(Action action){Saved saved(action);auto value=saved.owner(action);Hook h;{Installed inst…; returns h · [reviewed contract](#b0013) |
| [B0014 · 62–78](../../../../../tests/unit/history_retirement_fault_test.cpp#L62) | Callable definition: void failures() | calls saved, trace, reset, descriptors; guard check(failed \|\| h.already_absent,"retirement syscall error ignored");if(failed)++cases;else ++absen…; 3 loop sites · [reviewed contract](#b0014) |
| [B0015 · 79–90](../../../../../tests/unit/history_retirement_fault_test.cpp#L79) | Callable definition: void crashes() | calls saved, trace, reset, fork; guard saved.reset();const auto child=::fork();check(child&gt;=0,"retirement crash fork failed");; 3 loop sites · [reviewed contract](#b0015) |
| [B0016 · 91–106](../../../../../tests/unit/history_retirement_fault_test.cpp#L91) | Callable definition: void allocations() | calls saved, owner, perform, get_deleter; guard {auto value=saved.owner(action);{s04_alloc::Scope scope;saved.perform(action,value);count=s04_alloc…; 3 loop sites · [reviewed contract](#b0016) |
| [B0017 · 107–107](../../../../../tests/unit/history_retirement_fault_test.cpp#L107) | Closes surrounding scope/type. |  · [reviewed contract](#b0017) |
| [B0018 · 108–108](../../../../../tests/unit/history_retirement_fault_test.cpp#L108) | Callable definition: int main(int argc,char** argv) | calls check, std::string_view, crashes, allocations; guard int main(int argc,char** argv){try{check(argc==2,"expected retirement mode");if(std::string_view(ar…; returns 1 · [reviewed contract](#b0018) |

## B0001

[Lines 1–12](../../../../../tests/unit/history_retirement_fault_test.cpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L1-L12:sha256:e253bd0374b8b78f7e31a607166fa4e82f42ddaa1fda7ffdf51eb50952dfd58c
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Prepare history_retirement_fault_test.cpp: include "history_retirement_fixture.hpp", "generation_file_probe.hpp", "checkpoint_file_probe.hpp", "journal_file_probe.hpp", "local_sink_probe.hpp", &lt;cerrno&gt;, &lt;sys/wait.h&gt;; bind local aliases/name imports. |
| inputs / outputs | Compiler-visible dependencies, names and the recorded declarations in; declarations available to the following fixture/CLI/example definitions out. |
| invariants | Declarations are scoped to this source/header and its selected ABI. Included code has its own effects; names and editable fixture values do not confer proof, admission or publication authority. |
| ownership | Aliases/includes do not create a query owner. Pointers/references/views are non-owning. Containers own their elements, which can themselves be borrowed pointers or numeric IDs. Only documented owning shared-control handles retain controls; IDs/slot-handle values do not independently keep an arena/runtime alive. |
| failure | Missing headers, ill-formed names/types, failed static assertions or active #error directives stop compilation. No runtime rejection/rollback mechanism is implemented by aliases or function prototypes. |
| cost | Preprocessing and type/constraint instantiation cost compilation. Alias/prototype syntax does not invoke the declared operation; any included definitions keep their own initialization effects. |
| Design | [tests/unit/history_retirement_fault_test.cpp](../../../../../tests/unit/history_retirement_fault_test.cpp), [docs/history-retirement.md](../../../../history-retirement.md), [docs/code_review.md](../../../../code_review.md) |

## B0002

[Lines 13–13](../../../../../tests/unit/history_retirement_fault_test.cpp#L13); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
enum class Action {retire,resume};
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Select whether the saved generation owner is retired or resumes an existing retirement intent. |
| inputs / outputs | The enum value selects the fixture path used by trace, failures, crashes, and allocations. |
| invariants | retire starts from a normal selected generation; resume starts with a durable pending intent created by Saved. |
| ownership | The enum carries no state; Saved owns the root, sink, journal files, and intent bytes. |
| failure | An unknown enum value has no explicit recovery path and is outside the test cases. |
| cost | Two action values are visited by each top-level fault sweep. |
| Design | tests/unit/history_retirement_fault_test.cpp:13-13, docs/history-retirement.md:13-21, docs/history-retirement.md:60-115, docs/generations.md:65-123, src/runtime/session.cpp:1024-1046, src/recovery/generation_retirement.cpp:111-135, tests/support/history_retirement_fixture.hpp:6-41, tests/support/generation_file_probe.hpp:1-18, tests/support/checkpoint_file_probe.hpp:1-28, tests/support/journal_file_probe.hpp:1-18, tests/support/local_sink_probe.hpp:1-11, tests/support/index_allocation.hpp:11-70 |

## B0003

[Lines 14–17](../../../../../tests/unit/history_retirement_fault_test.cpp#L14); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L14-L17:sha256:410b7b194b680c96da61e6906eaa341b064a2b23fb285b3bdec0a64fe8fe9612
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Prepare history_retirement_fault_test.cpp: declare fixture state/default initializers. |
| inputs / outputs | Compiler-visible dependencies, names and the recorded declarations in; declarations available to the following fixture/CLI/example definitions out. The source span lists the exact member/global names, types and initial values; initializers run when the enclosing object/program/thread is initialized. |
| invariants | Declarations are scoped to this source/header and its selected ABI. Included code has its own effects; names and editable fixture values do not confer proof, admission or publication authority. |
| ownership | Aliases/includes do not create a query owner. Pointers/references/views are non-owning. Containers own their elements, which can themselves be borrowed pointers or numeric IDs. Only documented owning shared-control handles retain controls; IDs/slot-handle values do not independently keep an arena/runtime alive. |
| failure | Missing headers, ill-formed names/types, failed static assertions or active #error directives stop compilation. No runtime rejection/rollback mechanism is implemented by aliases or function prototypes. Actual object construction and explicit initializers keep the failure contracts of their declared types/called helpers; this card supplies no extra rollback. |
| cost | Preprocessing and type/constraint instantiation cost compilation. Alias/prototype syntax does not invoke the declared operation; any included definitions keep their own initialization effects. Member/global initialization follows the shown C++ types and expressions when its enclosing object/program is constructed; owning containers can allocate. Default member declarations do not themselves instantiate a fixture. Copies and teardown follow the owning types. |
| Design | [tests/unit/history_retirement_fault_test.cpp](../../../../../tests/unit/history_retirement_fault_test.cpp), [docs/history-retirement.md](../../../../history-retirement.md), [docs/code_review.md](../../../../code_review.md) |

## B0004

[Lines 18–18](../../../../../tests/unit/history_retirement_fault_test.cpp#L18); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void visit(bool done) noexcept {if(!done)++count;if(count==crash && done==after)::_exit(77);}
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Count generation-hook calls and terminate at one configured before/after syscall observation. |
| inputs / outputs | A GenerationEvent's after flag and Hook counters in; updates count/order flags or exits the child with status 77. |
| invariants | Only before events increment count; crash matching uses the same ordinal and selected side of the syscall. |
| ownership | The callback context is a borrowed Hook installed only inside Installed's scope; it retains no event memory. |
| failure | The hook is noexcept and does not translate failures; _exit prevents child cleanup at the selected boundary. |
| cost | Constant work per observed generation event; it does not count syscalls from the other installed file hooks separately. |
| Design | tests/unit/history_retirement_fault_test.cpp:18-18, docs/history-retirement.md:13-21, docs/history-retirement.md:60-115, docs/generations.md:65-123, src/runtime/session.cpp:1024-1046, src/recovery/generation_retirement.cpp:111-135, tests/support/history_retirement_fixture.hpp:6-41, tests/support/generation_file_probe.hpp:1-18, tests/support/checkpoint_file_probe.hpp:1-28, tests/support/journal_file_probe.hpp:1-18, tests/support/local_sink_probe.hpp:1-11, tests/support/index_allocation.hpp:11-70 |

## B0005

[Lines 19–19](../../../../../tests/unit/history_retirement_fault_test.cpp#L19); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
template<class D> D decision(bool done) const noexcept {D result;if(!done){result.maximum_transfer=maximum;if(count==fail){if(after)result.error_after=EIO;else result.error_before=EIO;}}return result;}
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Return a per-channel decision that caps transfer size or injects one before/after EIO. |
| inputs / outputs | A callback event's done flag and Hook settings in; a typed test decision out. |
| invariants | The transfer cap and fail point apply only before events; the after flag chooses the error side for the selected ordinal. |
| ownership | The value is a stack result consumed by the probe immediately; Hook state remains externally owned. |
| failure | A synthetic after error models an operation that took effect before error reporting; the hook itself never throws. |
| cost | One small decision value per event, with no event history allocation. |
| Design | tests/unit/history_retirement_fault_test.cpp:19-19, docs/history-retirement.md:13-21, docs/history-retirement.md:60-115, docs/generations.md:65-123, src/runtime/session.cpp:1024-1046, src/recovery/generation_retirement.cpp:111-135, tests/support/history_retirement_fixture.hpp:6-41, tests/support/generation_file_probe.hpp:1-18, tests/support/checkpoint_file_probe.hpp:1-28, tests/support/journal_file_probe.hpp:1-18, tests/support/local_sink_probe.hpp:1-11, tests/support/index_allocation.hpp:11-70 |

## B0006

[Lines 20–34](../../../../../tests/unit/history_retirement_fault_test.cpp#L20); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
static recovery::testing::GenerationDecision generation(const recovery::testing::GenerationEvent& event,void* context) noexcept {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Observe generation persistence stages and record intent/root/deletion ordering. |
| inputs / outputs | GenerationEvent plus borrowed Hook context in; returns GenerationDecision and updates intent/root flags. |
| invariants | Success flags require an after event with nonnegative result and no native error; root rename requires synced intent; old-file unlink requires synced new root. |
| ownership | The Hook context outlives the callback installation; event path/name views are read only during the callback. |
| failure | Configured EIO/EINTR can be returned at the chosen stage; a missed ordering assertion fails trace or the calling fault case. |
| cost | Constant field checks per generation event; the callback writes only scalar flags and counters. |
| Design | tests/unit/history_retirement_fault_test.cpp:20-34, docs/history-retirement.md:13-21, docs/history-retirement.md:60-115, docs/generations.md:65-123, src/runtime/session.cpp:1024-1046, src/recovery/generation_retirement.cpp:111-135, tests/support/history_retirement_fixture.hpp:6-41, tests/support/generation_file_probe.hpp:1-18, tests/support/checkpoint_file_probe.hpp:1-28, tests/support/journal_file_probe.hpp:1-18, tests/support/local_sink_probe.hpp:1-11, tests/support/index_allocation.hpp:11-70 |

## B0007

[Lines 35–35](../../../../../tests/unit/history_retirement_fault_test.cpp#L35); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
static recovery::testing::FileDecision checkpoint(const recovery::testing::FileEvent& event,void* context) noexcept {auto& h=*static_cast<Hook*>(context);h.visit(event.after);return h.decision<recovery::testing::FileDecision>(event.after);}
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Feed checkpoint-file events into the shared retirement fault counter and decision policy. |
| inputs / outputs | FileEvent and Hook context in; FileDecision out after visit updates the common ordinal. |
| invariants | This adapter does not maintain a separate checkpoint-only count; ordinal is shared with generation, journal, and sink events. |
| ownership | The probe lends the Hook context during Installed; event storage is not retained. |
| failure | Injected errors are returned through the file probe, whose production path maps them to FileFailure. |
| cost | Constant adapter work per checkpoint-file event. |
| Design | tests/unit/history_retirement_fault_test.cpp:35-35, docs/history-retirement.md:13-21, docs/history-retirement.md:60-115, docs/generations.md:65-123, src/runtime/session.cpp:1024-1046, src/recovery/generation_retirement.cpp:111-135, tests/support/history_retirement_fixture.hpp:6-41, tests/support/generation_file_probe.hpp:1-18, tests/support/checkpoint_file_probe.hpp:1-28, tests/support/journal_file_probe.hpp:1-18, tests/support/local_sink_probe.hpp:1-11, tests/support/index_allocation.hpp:11-70 |

## B0008

[Lines 36–36](../../../../../tests/unit/history_retirement_fault_test.cpp#L36); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
static jp::testing::FileDecision journal(const jp::testing::FileEvent& event,void* context) noexcept {auto& h=*static_cast<Hook*>(context);h.visit(event.after);return h.decision<jp::testing::FileDecision>(event.after);}
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Feed journal-file events into the retirement fault counter and decision policy. |
| inputs / outputs | Journal FileEvent and Hook context in; matching FileDecision out. |
| invariants | Journal events share the single cross-channel ordinal used by generation, checkpoint and sink observations. |
| ownership | Callback context is borrowed for the Installed lifetime; no journal bytes are copied here. |
| failure | Journal file failures propagate through the journal component and are caught by the outer retirement sweep. |
| cost | Constant callback work; the event itself may represent a read, append, sync, or close. |
| Design | tests/unit/history_retirement_fault_test.cpp:36-36, docs/history-retirement.md:13-21, docs/history-retirement.md:60-115, docs/generations.md:65-123, src/runtime/session.cpp:1024-1046, src/recovery/generation_retirement.cpp:111-135, tests/support/history_retirement_fixture.hpp:6-41, tests/support/generation_file_probe.hpp:1-18, tests/support/checkpoint_file_probe.hpp:1-28, tests/support/journal_file_probe.hpp:1-18, tests/support/local_sink_probe.hpp:1-11, tests/support/index_allocation.hpp:11-70 |

## B0009

[Lines 37–37](../../../../../tests/unit/history_retirement_fault_test.cpp#L37); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
static sk::testing::Decision sink(const sk::testing::Event& event,void* context) noexcept {auto& h=*static_cast<Hook*>(context);h.visit(event.after);return h.decision<sk::testing::Decision>(event.after);}
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Feed local-sink events into the retirement fault counter and decision policy. |
| inputs / outputs | Sink Event and Hook context in; sink Decision out. |
| invariants | Sink syscall boundaries participate in the same ordering/failure count as the retirement and native file channels. |
| ownership | Hook is borrowed only while Installed exists; no sink epoch or path is owned by this adapter. |
| failure | Sink Failure remains the caller-visible carrier unless the test deliberately exits at the hook. |
| cost | Constant callback work per sink event; epoch serialization and sink I/O costs belong to File/QuerySession. |
| Design | tests/unit/history_retirement_fault_test.cpp:37-37, docs/history-retirement.md:13-21, docs/history-retirement.md:60-115, docs/generations.md:65-123, src/runtime/session.cpp:1024-1046, src/recovery/generation_retirement.cpp:111-135, tests/support/history_retirement_fixture.hpp:6-41, tests/support/generation_file_probe.hpp:1-18, tests/support/checkpoint_file_probe.hpp:1-28, tests/support/journal_file_probe.hpp:1-18, tests/support/local_sink_probe.hpp:1-11, tests/support/index_allocation.hpp:11-70 |

## B0010

[Lines 38–38](../../../../../tests/unit/history_retirement_fault_test.cpp#L38); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L38-L38:sha256:aa1d1a63390229c798347e83a0405441c9400035284ad168c1bf6cdf1d70a370
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Close the recorded declaration scopes in history_retirement_fault_test.cpp: struct Hook. |
| inputs / outputs | Preceding namespace, type or initializer declarations in; completed lexical boundary out. |
| invariants | Brace-opening context is recorded in root-scope-context-v1.json. These are declaration/initializer boundaries, not an independent update, validation or recovery operation. |
| ownership | Enclosing objects and borrowed fields keep their declared ownership. This punctuation creates no new owner. |
| failure | Malformed scope syntax is a compile error. Any initializer/constructor failure belongs to the enclosing object declaration. |
| cost | No separate loop, guard or engine call is introduced by the delimiter; enclosing initialization and object lifetime still have their actual costs. |
| Design | [tests/unit/history_retirement_fault_test.cpp](../../../../../tests/unit/history_retirement_fault_test.cpp), [docs/history-retirement.md](../../../../history-retirement.md), [docs/code_review.md](../../../../code_review.md) |

## B0011

[Lines 39–42](../../../../../tests/unit/history_retirement_fault_test.cpp#L39); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct Installed {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Install all four retirement syscall hooks and clear them together with RAII. |
| inputs / outputs | A Hook reference in; no output; setters install callbacks for generation, checkpoint, journal and sink probes. |
| invariants | Each probe uses the same Hook counter/context, so the sweep addresses the observed cross-file order. |
| ownership | The callback context is borrowed; Installed must be destroyed before its Hook, and the destructor clears every thread-local slot. |
| failure | Construction/destruction are test scaffolding; hook installation is not nested or thread-safe coordination beyond the probes' thread-local contract. |
| cost | Four setter calls on entry and four nulling calls on scope exit. |
| Design | tests/unit/history_retirement_fault_test.cpp:39-42, docs/history-retirement.md:13-21, docs/history-retirement.md:60-115, docs/generations.md:65-123, src/runtime/session.cpp:1024-1046, src/recovery/generation_retirement.cpp:111-135, tests/support/history_retirement_fixture.hpp:6-41, tests/support/generation_file_probe.hpp:1-18, tests/support/checkpoint_file_probe.hpp:1-28, tests/support/journal_file_probe.hpp:1-18, tests/support/local_sink_probe.hpp:1-11, tests/support/index_allocation.hpp:11-70 |

## B0012

[Lines 43–60](../../../../../tests/unit/history_retirement_fault_test.cpp#L43); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct Saved {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Build an ordinary or intent-pending retirement snapshot and preserve the exact relevant file bytes. |
| inputs / outputs | Action selects a RetirementFixture; the object records root, sink, generations 1-3 pairs and optional .retire content. |
| invariants | resume first forces unlink failure, then requires selected first_generation=3 and an existing durable intent; retire captures the pre-intent state. |
| ownership | RetirementFixture owns its directory and session; saved byte strings own copies independent of file descriptors; reset rewrites only those recorded paths. |
| failure | A failed setup assertion aborts the case; file rewrites use the fixture helper and do not prove power-loss persistence. |
| cost | Copies the root, sink and six old/selected checkpoint/WAL files, plus one intent for resume; bounded by this three-generation fixture. |
| Design | tests/unit/history_retirement_fault_test.cpp:43-60, docs/history-retirement.md:13-21, docs/history-retirement.md:60-115, docs/generations.md:65-123, src/runtime/session.cpp:1024-1046, src/recovery/generation_retirement.cpp:111-135, tests/support/history_retirement_fixture.hpp:6-41, tests/support/generation_file_probe.hpp:1-18, tests/support/checkpoint_file_probe.hpp:1-28, tests/support/journal_file_probe.hpp:1-18, tests/support/local_sink_probe.hpp:1-11, tests/support/index_allocation.hpp:11-70 |

## B0013

[Lines 61–61](../../../../../tests/unit/history_retirement_fault_test.cpp#L61); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Hook trace(Action action){Saved saved(action);auto value=saved.owner(action);Hook h;{Installed installed(h);saved.perform(action,value);}check(!h.order_violation,"intent/root/deletion persistence order violated");return h;}
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Produce the baseline event ordinal and check that normal retirement/resume preserves the selected native anchor. |
| inputs / outputs | Action selects Saved setup; Hook counters observed around perform; Hook returned after scope. |
| invariants | A trace with an ordering violation cannot be used as the fault baseline. |
| ownership | Saved owns the restored QuerySession while tracing; Installed is destroyed before the Hook is returned. |
| failure | Fixture setup, operation, or ordering assertion propagates to main as an exception. |
| cost | One complete retire or resume operation establishes a finite, source-derived syscall count. |
| Design | tests/unit/history_retirement_fault_test.cpp:61-61, docs/history-retirement.md:13-21, docs/history-retirement.md:60-115, docs/generations.md:65-123, src/runtime/session.cpp:1024-1046, src/recovery/generation_retirement.cpp:111-135, tests/support/history_retirement_fixture.hpp:6-41, tests/support/generation_file_probe.hpp:1-18, tests/support/checkpoint_file_probe.hpp:1-28, tests/support/journal_file_probe.hpp:1-18, tests/support/local_sink_probe.hpp:1-11, tests/support/index_allocation.hpp:11-70 |

## B0014

[Lines 62–78](../../../../../tests/unit/history_retirement_fault_test.cpp#L62); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void failures() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Inject before/after failures at every observed retirement syscall and exercise short I/O and retry limits. |
| inputs / outputs | Retire/resume fixture plus each baseline ordinal/side; checks selected state, descriptor count and a subsequent sink-aware restore. |
| invariants | Only ENOENT reported after an unlink can be accepted as already absent; short transfers must preserve ordering; repeated read EINTR ends at the configured root-operation cap. |
| ownership | Each iteration restores the file snapshot, owns a temporary session, releases it before descriptor checks, and uses a fresh Hook scope. |
| failure | Expected carriers are GenerationFailure, checkpoint FileFailure, journal FileFailure or sink Failure; the fixture separately verifies selected state/output after each case. |
| cost | Two actions times two sides for each measured syscall, plus one three-byte short-I/O case per action and one 30-operation recovery quota case; baseline size is observed, not hard-coded. |
| Design | tests/unit/history_retirement_fault_test.cpp:62-78, docs/history-retirement.md:13-21, docs/history-retirement.md:60-115, docs/generations.md:65-123, src/runtime/session.cpp:1024-1046, src/recovery/generation_retirement.cpp:111-135, tests/support/history_retirement_fixture.hpp:6-41, tests/support/generation_file_probe.hpp:1-18, tests/support/checkpoint_file_probe.hpp:1-28, tests/support/journal_file_probe.hpp:1-18, tests/support/local_sink_probe.hpp:1-11, tests/support/index_allocation.hpp:11-70 |

## B0015

[Lines 79–90](../../../../../tests/unit/history_retirement_fault_test.cpp#L79); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void crashes() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Exit a child before or after each measured retirement syscall and verify restart from the recorded files. |
| inputs / outputs | Action, syscall ordinal and side in; parent waits for exit 77, then checks selected native pair/output and sink-aware recovery. |
| invariants | Every tested point is an actual syscall boundary seen in the corresponding baseline trace; test scope is process exit, not power loss. |
| ownership | Child inherits the fixture state and performs the operation; parent retains its own fixture and explicitly validates it after waitpid. |
| failure | Fork/wait/status mismatches fail the test; child exceptions exit with a distinct status rather than being mistaken for the hook exit. |
| cost | Two actions times two sides for each baseline event; each parent verification reopens the bounded generation fixture. |
| Design | tests/unit/history_retirement_fault_test.cpp:79-90, docs/history-retirement.md:13-21, docs/history-retirement.md:60-115, docs/generations.md:65-123, src/runtime/session.cpp:1024-1046, src/recovery/generation_retirement.cpp:111-135, tests/support/history_retirement_fixture.hpp:6-41, tests/support/generation_file_probe.hpp:1-18, tests/support/checkpoint_file_probe.hpp:1-28, tests/support/journal_file_probe.hpp:1-18, tests/support/local_sink_probe.hpp:1-11, tests/support/index_allocation.hpp:11-70 |

## B0016

[Lines 91–106](../../../../../tests/unit/history_retirement_fault_test.cpp#L91); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void allocations() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Fault each intercepted C++ allocation during retirement and prove no allocation after intent publication. |
| inputs / outputs | A successful retire/resume yields a count; each position is failed in a fresh attempt and compared with saved file bytes and descriptor count. |
| invariants | The S04 seam counts replaced scalar/array, aligned and nothrow C++ new calls, not bytes or direct libc calls; resume count must match receiving-account successful allocation statistics. |
| ownership | Scope is nonnested and thread-local; each failed QuerySession owner is reset before lock checks; MemoryAccount lifetime follows the accounted owner. |
| failure | Each selected position must throw bad_alloc before mutating saved durable files; a one-byte-under replay heap cap must produce MemoryFailure. |
| cost | One measured operation per action plus one failure attempt per intercepted new position; heap peak and allocation-call count are separate quantities; successful retire is then denied further new calls at the intent link. |
| Design | tests/unit/history_retirement_fault_test.cpp:91-106, docs/history-retirement.md:13-21, docs/history-retirement.md:60-115, docs/generations.md:65-123, src/runtime/session.cpp:1024-1046, src/recovery/generation_retirement.cpp:111-135, tests/support/history_retirement_fixture.hpp:6-41, tests/support/generation_file_probe.hpp:1-18, tests/support/checkpoint_file_probe.hpp:1-28, tests/support/journal_file_probe.hpp:1-18, tests/support/local_sink_probe.hpp:1-11, tests/support/index_allocation.hpp:11-70 |

## B0017

[Lines 107–107](../../../../../tests/unit/history_retirement_fault_test.cpp#L107); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L107-L107:sha256:412ca345ccf75bf9c0806bce695be8de808b79984251a7a54d202cf6101dd451
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Close the recorded declaration scopes in history_retirement_fault_test.cpp: namespace (anonymous). |
| inputs / outputs | Preceding namespace, type or initializer declarations in; completed lexical boundary out. |
| invariants | Brace-opening context is recorded in root-scope-context-v1.json. These are declaration/initializer boundaries, not an independent update, validation or recovery operation. |
| ownership | Enclosing objects and borrowed fields keep their declared ownership. This punctuation creates no new owner. |
| failure | Malformed scope syntax is a compile error. Any initializer/constructor failure belongs to the enclosing object declaration. |
| cost | No separate loop, guard or engine call is introduced by the delimiter; enclosing initialization and object lifetime still have their actual costs. |
| Design | [tests/unit/history_retirement_fault_test.cpp](../../../../../tests/unit/history_retirement_fault_test.cpp), [docs/history-retirement.md](../../../../history-retirement.md), [docs/code_review.md](../../../../code_review.md) |

## B0018

[Lines 108–108](../../../../../tests/unit/history_retirement_fault_test.cpp#L108); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
int main(int argc,char** argv){try{check(argc==2,"expected retirement mode");if(std::string_view(argv[1])=="crash")crashes();else{allocations();failures();}}catch(const std::exception& e){std::cerr<<e.what()<<'\n';return 1;}}
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Run either the child-process crash matrix or the allocation and syscall-error matrices. |
| inputs / outputs | Exactly one mode argument selects crashes; other values run allocations and failures; returns zero or reports an exception. |
| invariants | All inner assertions are required; this wrapper does not run an additional recovery mode. |
| ownership | main owns only argument dispatch and call order; local fixtures own resources inside each suite. |
| failure | Wrong argument count or any standard exception prints a diagnostic and returns 1. |
| cost | One bounded suite invocation; matrix sizes derive from fixture event/allocation counts. |
| Design | tests/unit/history_retirement_fault_test.cpp:108-108, docs/history-retirement.md:13-21, docs/history-retirement.md:60-115, docs/generations.md:65-123, src/runtime/session.cpp:1024-1046, src/recovery/generation_retirement.cpp:111-135, tests/support/history_retirement_fixture.hpp:6-41, tests/support/generation_file_probe.hpp:1-18, tests/support/checkpoint_file_probe.hpp:1-28, tests/support/journal_file_probe.hpp:1-18, tests/support/local_sink_probe.hpp:1-11, tests/support/index_allocation.hpp:11-70 |
