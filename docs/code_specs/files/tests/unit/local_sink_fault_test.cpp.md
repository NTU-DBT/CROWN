# `tests/unit/local_sink_fault_test.cpp` — block usage map

[Source](../../../../../tests/unit/local_sink_fault_test.cpp) · [Source index](../../../README.md) · [Subsystem contracts](../../../subsystem_contracts.md) · [Reviewed primitives](../../../primitives.md)

Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection.

Snapshot SHA-256: `dc2852b2bd70b783f0bd2e480dc7b9fc79b59d3418def0b3d980621afbcd51da`. 114 lines partitioned into 17 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [tests](../../../subsystem_contracts.md#tests). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/code_review.md](../../../../code_review.md), [docs/reference_fuzz.md](../../../../reference_fuzz.md), [docs/task_ledger.md](../../../../task_ledger.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–8](../../../../../tests/unit/local_sink_fault_test.cpp#L1) | Imports dependencies; declares namespace scope; declares aliases. |  · [reviewed contract](#b0001) |
| [B0002 · 9–9](../../../../../tests/unit/local_sink_fault_test.cpp#L9) | Type/record definition: enum class Action |  · [reviewed contract](#b0002) |
| [B0003 · 10–22](../../../../../tests/unit/local_sink_fault_test.cpp#L10) | Type/record definition: struct Hook | returns result · [reviewed contract](#b0003) |
| [B0004 · 23–23](../../../../../tests/unit/local_sink_fault_test.cpp#L23) | Type/record definition: struct Installed |  · [reviewed contract](#b0004) |
| [B0005 · 24–28](../../../../../tests/unit/local_sink_fault_test.cpp#L24) | declares types or opens a type body. |  · [reviewed contract](#b0005) |
| [B0006 · 29–39](../../../../../tests/unit/local_sink_fault_test.cpp#L29) | Callable definition: explicit Saved(Action action):f(false,1),program(CompiledProgram::standalone(f.test.plan)),path(f.directory.file("output.sink")) | calls f, program, CompiledProgram::standalone, path · [reviewed contract](#b0006) |
| [B0007 · 40–40](../../../../../tests/unit/local_sink_fault_test.cpp#L40) | Callable definition: void commit(std::size_t index) | calls typed::enqueue, check, begin_next, finish; guard void commit(std::size_t index) {typed::enqueue(*f.session,io::InputEvent{f.test.updates\[index\],io::… · [reviewed contract](#b0007) |
| [B0008 · 41–47](../../../../../tests/unit/local_sink_fault_test.cpp#L41) | Callable definition: QuerySession::Owner owner(Action action) | calls QuerySession::restore_generation, generation_test::recovery_options, open_local_sink, options; returns value · [reviewed contract](#b0008) |
| [B0009 · 48–53](../../../../../tests/unit/local_sink_fault_test.cpp#L48) | Callable definition: void perform(Action action,QuerySession& value) | calls create_local_sink, options, deliver_local_epoch, read_local_epoch · [reviewed contract](#b0009) |
| [B0010 · 54–65](../../../../../tests/unit/local_sink_fault_test.cpp#L54) | Callable definition: void verify(Action action) | calls QuerySession::restore_generation, generation_test::recovery_options, std::filesystem::exists, open_local_sink; guard check(value-&gt;local_sink_receipt().sequence()==0 && value-&gt;status().committed_sequence==0,"sink crea…; growth insert, resize; 2 loop sites · [reviewed contract](#b0010) |
| [B0011 · 66–66](../../../../../tests/unit/local_sink_fault_test.cpp#L66) | Closes surrounding scope/type. |  · [reviewed contract](#b0011) |
| [B0012 · 67–67](../../../../../tests/unit/local_sink_fault_test.cpp#L67) | Callable definition: Hook trace(Action action) | calls saved, owner, installed, perform; returns hook · [reviewed contract](#b0012) |
| [B0013 · 68–86](../../../../../tests/unit/local_sink_fault_test.cpp#L68) | Callable definition: void failures() | calls trace, saved, descriptors, owner; guard check(failed,"sink syscall error ignored");; 3 loop sites · [reviewed contract](#b0013) |
| [B0014 · 87–98](../../../../../tests/unit/local_sink_fault_test.cpp#L87) | Callable definition: void crashes() | calls trace, saved, fork, check; guard Saved saved(action);const auto child=::fork();check(child&gt;=0,"sink crash fork failed");; 3 loop sites · [reviewed contract](#b0014) |
| [B0015 · 99–112](../../../../../tests/unit/local_sink_fault_test.cpp#L99) | Callable definition: void allocations() | calls saved, owner, deliver_local_epoch, reset; guard check(failed && contents(item.path)==old && owner-&gt;status().output_remaining==1 && owner-&gt;local_sin…; 1 loop sites · [reviewed contract](#b0015) |
| [B0016 · 113–113](../../../../../tests/unit/local_sink_fault_test.cpp#L113) | Closes surrounding scope/type. |  · [reviewed contract](#b0016) |
| [B0017 · 114–114](../../../../../tests/unit/local_sink_fault_test.cpp#L114) | Callable definition: int main(int argc,char** argv) | calls check, std::string_view, crashes, allocations; guard int main(int argc,char** argv){try{check(argc==2,"expected sink fault mode");if(std::string_view(ar…; returns 1 · [reviewed contract](#b0017) |

## B0001

[Lines 1–8](../../../../../tests/unit/local_sink_fault_test.cpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L1-L8:sha256:51cab330e1873ac7630f0b4b936e145f01a2be7ac2c87808fb2346495dd53e5e
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Prepare local_sink_fault_test.cpp: include "local_sink_fixture.hpp", "local_sink_probe.hpp", &lt;cerrno&gt;, &lt;sys/wait.h&gt;; bind local aliases/name imports. |
| inputs / outputs | Compiler-visible dependencies, names and the recorded declarations in; declarations available to the following fixture/CLI/example definitions out. |
| invariants | Declarations are scoped to this source/header and its selected ABI. Included code has its own effects; names and editable fixture values do not confer proof, admission or publication authority. |
| ownership | Aliases/includes do not create a query owner. Pointers/references/views are non-owning. Containers own their elements, which can themselves be borrowed pointers or numeric IDs. Only documented owning shared-control handles retain controls; IDs/slot-handle values do not independently keep an arena/runtime alive. |
| failure | Missing headers, ill-formed names/types, failed static assertions or active #error directives stop compilation. No runtime rejection/rollback mechanism is implemented by aliases or function prototypes. |
| cost | Preprocessing and type/constraint instantiation cost compilation. Alias/prototype syntax does not invoke the declared operation; any included definitions keep their own initialization effects. |
| Design | [tests/unit/local_sink_fault_test.cpp](../../../../../tests/unit/local_sink_fault_test.cpp), [docs/local-sink.md](../../../../local-sink.md), [docs/code_review.md](../../../../code_review.md) |

## B0002

[Lines 9–9](../../../../../tests/unit/local_sink_fault_test.cpp#L9); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
enum class Action {create,deliver,open,read,repair};
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Name the sink operation being traced or faulted. |
| inputs / outputs | Enum selects create, deliver, open, read or repair setup and verification behavior. |
| invariants | The five actions use intentionally different saved sink prefixes; create starts without a file, repair starts with an incomplete suffix. |
| ownership | The enum is a tag only; Saved owns the file bytes and fixture directory. |
| failure | No invalid action is supplied by the test matrices. |
| cost | Five finite action values are traversed. |
| Design | tests/unit/local_sink_fault_test.cpp:9-9, docs/local-sink.md:110-145, docs/local-sink.md:119-127, src/runtime/session.cpp:864-927, src/recovery/local_sink.cpp:69-139, src/recovery/local_sink.cpp:269-317, tests/support/local_sink_fixture.hpp:12-29, tests/support/local_sink_probe.hpp:1-11, tests/support/index_allocation.hpp:11-70, docs/journal-files.md:57-66 |

## B0003

[Lines 10–22](../../../../../tests/unit/local_sink_fault_test.cpp#L10); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct Hook {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Count sink hook calls, cap transfers, inject syscall errors, or arm post-sync allocation denial. |
| inputs / outputs | Sink Event and Hook context in; Decision out; selected boundary may exit child with 77. |
| invariants | Only before events inject errors/caps; after sync records the S04 call count then sets the one-shot new hook to fail; after-event result reports native syscall observation. |
| ownership | Hook context is borrowed until Installed destruction; thread-local callbacks are reset before Hook lifetime ends. |
| failure | Callback is noexcept; syscall failure is surfaced by sink File/QuerySession, while crash is a process exit rather than an exception. |
| cost | Constant work and scalar writes per event; no event vector or byte counter is allocated. |
| Design | tests/unit/local_sink_fault_test.cpp:10-22, docs/local-sink.md:110-145, docs/local-sink.md:119-127, src/runtime/session.cpp:864-927, src/recovery/local_sink.cpp:69-139, src/recovery/local_sink.cpp:269-317, tests/support/local_sink_fixture.hpp:12-29, tests/support/local_sink_probe.hpp:1-11, tests/support/index_allocation.hpp:11-70, docs/journal-files.md:57-66 |

## B0004

[Lines 23–23](../../../../../tests/unit/local_sink_fault_test.cpp#L23); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct Installed {explicit Installed(Hook& hook){sk::testing::set_hook(Hook::call,&hook);}~Installed(){sk::testing::set_hook(nullptr,nullptr);}};
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Install one sink syscall callback for a scoped attempt and clear it on exit. |
| inputs / outputs | Hook reference in; installs sk::testing callback; destructor nulls the slot. |
| invariants | The callback context must remain alive through the installed scope; this wrapper does not stack or restore a prior hook. |
| ownership | Installed borrows Hook; the calling function owns both and scopes teardown before checking state. |
| failure | No custom error translation; sink APIs carry operation failures. |
| cost | One install and one clear call. |
| Design | tests/unit/local_sink_fault_test.cpp:23-23, docs/local-sink.md:110-145, docs/local-sink.md:119-127, src/runtime/session.cpp:864-927, src/recovery/local_sink.cpp:69-139, src/recovery/local_sink.cpp:269-317, tests/support/local_sink_fixture.hpp:12-29, tests/support/local_sink_probe.hpp:1-11, tests/support/index_allocation.hpp:11-70, docs/journal-files.md:57-66 |

## B0005

[Lines 24–28](../../../../../tests/unit/local_sink_fault_test.cpp#L24); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L24-L28:sha256:e1c996e074c287fdff216a0f208bd7f33798cd82e54e02547c83f3a19809833e
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Prepare local_sink_fault_test.cpp: declare fixture state/default initializers. |
| inputs / outputs | Compiler-visible dependencies, names and the recorded declarations in; declarations available to the following fixture/CLI/example definitions out. The source span lists the exact member/global names, types and initial values; initializers run when the enclosing object/program/thread is initialized. |
| invariants | Declarations are scoped to this source/header and its selected ABI. Included code has its own effects; names and editable fixture values do not confer proof, admission or publication authority. |
| ownership | Aliases/includes do not create a query owner. Pointers/references/views are non-owning. Containers own their elements, which can themselves be borrowed pointers or numeric IDs. Only documented owning shared-control handles retain controls; IDs/slot-handle values do not independently keep an arena/runtime alive. |
| failure | Missing headers, ill-formed names/types, failed static assertions or active #error directives stop compilation. No runtime rejection/rollback mechanism is implemented by aliases or function prototypes. Actual object construction and explicit initializers keep the failure contracts of their declared types/called helpers; this card supplies no extra rollback. |
| cost | Preprocessing and type/constraint instantiation cost compilation. Alias/prototype syntax does not invoke the declared operation; any included definitions keep their own initialization effects. Member/global initialization follows the shown C++ types and expressions when its enclosing object/program is constructed; owning containers can allocate. Default member declarations do not themselves instantiate a fixture. Copies and teardown follow the owning types. |
| Design | [tests/unit/local_sink_fault_test.cpp](../../../../../tests/unit/local_sink_fault_test.cpp), [docs/local-sink.md](../../../../local-sink.md), [docs/code_review.md](../../../../code_review.md) |

## B0006

[Lines 29–39](../../../../../tests/unit/local_sink_fault_test.cpp#L29); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
explicit Saved(Action action):f(false,1),program(CompiledProgram::standalone(f.test.plan)),path(f.directory.file("output.sink")) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Capture a durable two-epoch native/sink fixture for one sink fault action. |
| inputs / outputs | Action drives setup; Saved stores program, path, expected header and file bytes, then exposes restore/perform/verify helpers. |
| invariants | create captures no existing sink; deliver captures one durable epoch; open/read/repair capture two epochs, with repair truncating one byte after closing; verification replays two epochs and checks one next update. |
| ownership | Fixture owns directory/session until reset; saved strings own byte copies; returned restore owner has its own account-backed session. |
| failure | Setup helpers check native update creation; invalid file/setup conditions abort rather than being interpreted as the injected operation result. |
| cost | At most two source commits, two sink epochs, one restore and one byte-copy per saved file. |
| Design | tests/unit/local_sink_fault_test.cpp:29-39, docs/local-sink.md:110-145, docs/local-sink.md:119-127, src/runtime/session.cpp:864-927, src/recovery/local_sink.cpp:69-139, src/recovery/local_sink.cpp:269-317, tests/support/local_sink_fixture.hpp:12-29, tests/support/local_sink_probe.hpp:1-11, tests/support/index_allocation.hpp:11-70, docs/journal-files.md:57-66 |

## B0007

[Lines 40–40](../../../../../tests/unit/local_sink_fault_test.cpp#L40); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void commit(std::size_t index) {typed::enqueue(*f.session,io::InputEvent{f.test.updates[index],io::SourcePosition{"feed",f.test.updates[index].sequence*10}});check(f.session->begin_next(),"sink fault source missing");finish(*f.session);}
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Commit one selected typed fixture update without draining its output. |
| inputs / outputs | An update index selects a test event; enqueues it, begins input and calls finish to commit. |
| invariants | The sink fixture intentionally leaves committed output for deliver_local_epoch; source position is sequence times ten. |
| ownership | QuerySession owns native committed output; typed fixture supplies update values. |
| failure | Missing input or commit errors propagate to the fault setup. |
| cost | One input admission and native query commit. |
| Design | tests/unit/local_sink_fault_test.cpp:40-40, docs/local-sink.md:110-145, docs/local-sink.md:119-127, src/runtime/session.cpp:864-927, src/recovery/local_sink.cpp:69-139, src/recovery/local_sink.cpp:269-317, tests/support/local_sink_fixture.hpp:12-29, tests/support/local_sink_probe.hpp:1-11, tests/support/index_allocation.hpp:11-70, docs/journal-files.md:57-66 |

## B0008

[Lines 41–47](../../../../../tests/unit/local_sink_fault_test.cpp#L41); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
QuerySession::Owner owner(Action action) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Restore the native generation and attach/advance the sink to the state required by an action. |
| inputs / outputs | Action in; paused owner out, with sink attached for deliver/read and verified sequence advanced one or two times. |
| invariants | The prepared action's next operation is positioned at the same replay boundary for every measured hook trace. |
| ownership | Returned Owner retains the receiving query account, generation lock, journal and sink file lock; fixture program is borrowed/copied into restore. |
| failure | Native restore, sink open, or dedup delivery failure aborts setup before injection. |
| cost | One generation replay plus up to two sink open/duplicate operations. |
| Design | tests/unit/local_sink_fault_test.cpp:41-47, docs/local-sink.md:110-145, docs/local-sink.md:119-127, src/runtime/session.cpp:864-927, src/recovery/local_sink.cpp:69-139, src/recovery/local_sink.cpp:269-317, tests/support/local_sink_fixture.hpp:12-29, tests/support/local_sink_probe.hpp:1-11, tests/support/index_allocation.hpp:11-70, docs/journal-files.md:57-66 |

## B0009

[Lines 48–53](../../../../../tests/unit/local_sink_fault_test.cpp#L48); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void perform(Action action,QuerySession& value) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Dispatch the selected sink operation against a live restored owner. |
| inputs / outputs | Action and QuerySession in; create or opens the fixture file, delivers one epoch, reads epoch 2, or reopens the file. |
| invariants | The method called matches the hook trace and its action's saved prefix; read is an existing complete epoch observation. |
| ownership | The caller retains QuerySession; sink path/options are borrowed only during the call. |
| failure | Operation's \`sk::Failure\`, ImageFailure, or standard error propagates to the action-specific test. |
| cost | One API call; underlying I/O and row decoding scale with the small one/two-epoch fixture. |
| Design | tests/unit/local_sink_fault_test.cpp:48-53, docs/local-sink.md:110-145, docs/local-sink.md:119-127, src/runtime/session.cpp:864-927, src/recovery/local_sink.cpp:69-139, src/recovery/local_sink.cpp:269-317, tests/support/local_sink_fixture.hpp:12-29, tests/support/local_sink_probe.hpp:1-11, tests/support/index_allocation.hpp:11-70, docs/journal-files.md:57-66 |

## B0010

[Lines 54–65](../../../../../tests/unit/local_sink_fault_test.cpp#L54); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void verify(Action action) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Reopen and verify sink/native state after an injected failure or process exit, then commit a next update. |
| inputs / outputs | Action selects create-state checks or replay of epochs 1-2; verifies relation/output and then epoch 3 against an independent database oracle. |
| invariants | No failed create invents an output epoch; existing actions preserve commit/progress at 2, next delivery reaches 3, and output rows match signed set semantics. |
| ownership | A fresh generation owner opens the same path; returned epochs own account-funded rows; database is an independent test oracle. |
| failure | Any unopenable damaged prefix, changed output, source frontier or failed next update trips an assertion. |
| cost | One fresh replay, up to two dedup deliveries, one read, one next query commit/delivery, and oracle insertion of three fixture rows. |
| Design | tests/unit/local_sink_fault_test.cpp:54-65, docs/local-sink.md:110-145, docs/local-sink.md:119-127, src/runtime/session.cpp:864-927, src/recovery/local_sink.cpp:69-139, src/recovery/local_sink.cpp:269-317, tests/support/local_sink_fixture.hpp:12-29, tests/support/local_sink_probe.hpp:1-11, tests/support/index_allocation.hpp:11-70, docs/journal-files.md:57-66 |

## B0011

[Lines 66–66](../../../../../tests/unit/local_sink_fault_test.cpp#L66); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L66-L66:sha256:aa1d1a63390229c798347e83a0405441c9400035284ad168c1bf6cdf1d70a370
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Close the recorded declaration scopes in local_sink_fault_test.cpp: struct Saved. |
| inputs / outputs | Preceding namespace, type or initializer declarations in; completed lexical boundary out. |
| invariants | Brace-opening context is recorded in root-scope-context-v1.json. These are declaration/initializer boundaries, not an independent update, validation or recovery operation. |
| ownership | Enclosing objects and borrowed fields keep their declared ownership. This punctuation creates no new owner. |
| failure | Malformed scope syntax is a compile error. Any initializer/constructor failure belongs to the enclosing object declaration. |
| cost | No separate loop, guard or engine call is introduced by the delimiter; enclosing initialization and object lifetime still have their actual costs. |
| Design | [tests/unit/local_sink_fault_test.cpp](../../../../../tests/unit/local_sink_fault_test.cpp), [docs/local-sink.md](../../../../local-sink.md), [docs/code_review.md](../../../../code_review.md) |

## B0012

[Lines 67–67](../../../../../tests/unit/local_sink_fault_test.cpp#L67); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Hook trace(Action action) {Saved saved(action);auto value=saved.owner(action);Hook hook;{Installed installed(hook);saved.perform(action,*value);}return hook;}
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Measure a baseline hook trace for the selected action. |
| inputs / outputs | Action in; Saved plus restored owner run once under Hook; Hook returned with observed count. |
| invariants | The trace configures no error/crash; it establishes actual syscall ordinals for that action only. |
| ownership | Saved owner and Installed hook are destroyed in scope order; \`trace\` returns scalar Hook observations. |
| failure | Any API/setup failure aborts before a sweep can claim coverage. |
| cost | One complete action against a maximum two-epoch sink fixture. |
| Design | tests/unit/local_sink_fault_test.cpp:67-67, docs/local-sink.md:110-145, docs/local-sink.md:119-127, src/runtime/session.cpp:864-927, src/recovery/local_sink.cpp:69-139, src/recovery/local_sink.cpp:269-317, tests/support/local_sink_fixture.hpp:12-29, tests/support/local_sink_probe.hpp:1-11, tests/support/index_allocation.hpp:11-70, docs/journal-files.md:57-66 |

## B0013

[Lines 68–86](../../../../../tests/unit/local_sink_fault_test.cpp#L68); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void failures() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Fail every measured sink syscall before and after, then retry; also check short transfers and bounded EINTR. |
| inputs / outputs | For each action and baseline ordinal/side, operation must throw; checks committed state, recovery_required, descriptor count, reopened output and next update. |
| invariants | The sink is considered uncertain after syscall errors; 3-byte transfers must remain valid; repeated read EINTR is bounded by copied 30-operation limit. |
| ownership | Each case builds a fresh Saved and QuerySession owner; resets/reads happen after hook removal so verification I/O is not injected. |
| failure | Only sk::Failure satisfies the expected failed operation; generic errors or missed poisoning fail. Restart verification must recover accepted state. |
| cost | Five actions times two sides per observed syscall, plus five short-I/O runs and one repeated-interrupt quota case; the per-action baseline count is runtime-derived. |
| Design | tests/unit/local_sink_fault_test.cpp:68-86, docs/local-sink.md:110-145, docs/local-sink.md:119-127, src/runtime/session.cpp:864-927, src/recovery/local_sink.cpp:69-139, src/recovery/local_sink.cpp:269-317, tests/support/local_sink_fixture.hpp:12-29, tests/support/local_sink_probe.hpp:1-11, tests/support/index_allocation.hpp:11-70, docs/journal-files.md:57-66 |

## B0014

[Lines 87–98](../../../../../tests/unit/local_sink_fault_test.cpp#L87); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void crashes() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Exit child processes at each real sink syscall edge and validate recovery in the parent. |
| inputs / outputs | Five actions, each observed baseline boundary and before/after side; parent waits for exit 77 then runs Saved.verify. |
| invariants | The asserted failure model is process termination around syscall hooks, not power loss; parent restart must recover original native output and the next update. |
| ownership | Child's restored owner/file locks die on process exit; parent owns the original Saved fixture and reopens only after waitpid. |
| failure | Fork/wait/status mismatches or recovery of a corrupt/partial committed epoch fail the test. |
| cost | Five action traces times two sides per measured boundary; each case does one parent reopen and bounded next-update check. |
| Design | tests/unit/local_sink_fault_test.cpp:87-98, docs/local-sink.md:110-145, docs/local-sink.md:119-127, src/runtime/session.cpp:864-927, src/recovery/local_sink.cpp:69-139, src/recovery/local_sink.cpp:269-317, tests/support/local_sink_fixture.hpp:12-29, tests/support/local_sink_probe.hpp:1-11, tests/support/index_allocation.hpp:11-70, docs/journal-files.md:57-66 |

## B0015

[Lines 99–112](../../../../../tests/unit/local_sink_fault_test.cpp#L99); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void allocations() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Inject bad_alloc at each intercepted C++ allocation in local delivery and assert retained output/retry. |
| inputs / outputs | One successful delivery measures S04 calls; each position faults a fresh delivery; a separate hook denies new after successful file sync. |
| invariants | S04 counts replacement scalar/array/aligned/nothrow new calls, not allocation bytes or direct libc calls; fault must leave file unchanged, output remaining=1 and verified prefix=1; acknowledgement after sync must not allocate through the seam. |
| ownership | Scope is thread-local and nonnested; owner is reset before descriptor comparison; MemoryAccount statistics are not compared here. |
| failure | Only bad_alloc is expected at selected position; after each failed delivery, retry and Saved.verify must complete. |
| cost | One baseline delivery plus one complete fixture rebuild/delivery per covered new position and a post-sync denial case; actual count is observed. |
| Design | tests/unit/local_sink_fault_test.cpp:99-112, docs/local-sink.md:110-145, docs/local-sink.md:119-127, src/runtime/session.cpp:864-927, src/recovery/local_sink.cpp:69-139, src/recovery/local_sink.cpp:269-317, tests/support/local_sink_fixture.hpp:12-29, tests/support/local_sink_probe.hpp:1-11, tests/support/index_allocation.hpp:11-70, docs/journal-files.md:57-66 |

## B0016

[Lines 113–113](../../../../../tests/unit/local_sink_fault_test.cpp#L113); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L113-L113:sha256:412ca345ccf75bf9c0806bce695be8de808b79984251a7a54d202cf6101dd451
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Close the recorded declaration scopes in local_sink_fault_test.cpp: namespace (anonymous). |
| inputs / outputs | Preceding namespace, type or initializer declarations in; completed lexical boundary out. |
| invariants | Brace-opening context is recorded in root-scope-context-v1.json. These are declaration/initializer boundaries, not an independent update, validation or recovery operation. |
| ownership | Enclosing objects and borrowed fields keep their declared ownership. This punctuation creates no new owner. |
| failure | Malformed scope syntax is a compile error. Any initializer/constructor failure belongs to the enclosing object declaration. |
| cost | No separate loop, guard or engine call is introduced by the delimiter; enclosing initialization and object lifetime still have their actual costs. |
| Design | [tests/unit/local_sink_fault_test.cpp](../../../../../tests/unit/local_sink_fault_test.cpp), [docs/local-sink.md](../../../../local-sink.md), [docs/code_review.md](../../../../code_review.md) |

## B0017

[Lines 114–114](../../../../../tests/unit/local_sink_fault_test.cpp#L114); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
int main(int argc,char** argv){try{check(argc==2,"expected sink fault mode");if(std::string_view(argv[1])=="crash")crashes();else{allocations();failures();}}catch(const std::exception& e){std::cerr<<e.what()<<'\n';return 1;}}
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Select crash mode or combined allocation/error mode for the fault executable. |
| inputs / outputs | One mode argument: \`crash\` runs process exits; other supplied string runs allocations/failures. |
| invariants | The wrapper's checks are all delegated to bounded suites. |
| ownership | main has no fixture state; callees own hooks and sessions. |
| failure | Wrong argument count or any standard exception returns 1 after diagnostic. |
| cost | One selected fault suite. |
| Design | tests/unit/local_sink_fault_test.cpp:114-114, docs/local-sink.md:110-145, docs/local-sink.md:119-127, src/runtime/session.cpp:864-927, src/recovery/local_sink.cpp:69-139, src/recovery/local_sink.cpp:269-317, tests/support/local_sink_fixture.hpp:12-29, tests/support/local_sink_probe.hpp:1-11, tests/support/index_allocation.hpp:11-70, docs/journal-files.md:57-66 |
