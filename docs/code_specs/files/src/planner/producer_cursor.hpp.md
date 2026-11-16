# `src/planner/producer_cursor.hpp` — block usage map

[Source](../../../../../src/planner/producer_cursor.hpp) · [Source index](../../../README.md) · [Subsystem contracts](../../../subsystem_contracts.md) · [Reviewed primitives](../../../primitives.md)

Search the finite canonical tree space and retain resumable evidence for exact minimum-height claims.

Snapshot SHA-256: `2d741deba625517979e7acbd56b9cdeeaf965c5ced75d2c5b6b2bad7fe514a7f`. 110 lines partitioned into 20 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [search](../../../subsystem_contracts.md#search). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/planner_proofs.md](../../../../planner_proofs.md), [docs/tree_oracle.md](../../../../tree_oracle.md), [docs/planner_continuations.md](../../../../planner_continuations.md), [docs/candidate_alternatives.md](../../../../candidate_alternatives.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–19](../../../../../src/planner/producer_cursor.hpp#L1) | Imports dependencies; guards repeated header inclusion; declares namespace scope; declares aliases; declares types or opens a type body; declares callable signatures; declares values/defaults or compile-time conditions. | source comment (unverified): // Coroutines contain only nonthrowing control flow between suspension points. · [reviewed contract](#b0001) |
| [B0002 · 20–20](../../../../../src/planner/producer_cursor.hpp#L20) | Callable definition: explicit Task(Handle h) noexcept : handle(h) | calls handle · [reviewed contract](#b0002) |
| [B0003 · 21–21](../../../../../src/planner/producer_cursor.hpp#L21) | Callable definition: Task(Task&& t) noexcept : handle(std::exchange(t.handle, {})) | calls handle, std::exchange · [reviewed contract](#b0003) |
| [B0004 · 22–25](../../../../../src/planner/producer_cursor.hpp#L22) | Callable definition: Task& operator=(Task&& t) noexcept | calls std::exchange; returns *this · [reviewed contract](#b0004) |
| [B0005 · 26–26](../../../../../src/planner/producer_cursor.hpp#L26) | Callable definition: ~Task() | calls destroy · [reviewed contract](#b0005) |
| [B0006 · 27–27](../../../../../src/planner/producer_cursor.hpp#L27) | Callable definition: bool await_ready() const noexcept | calls ; returns false · [reviewed contract](#b0006) |
| [B0007 · 28–28](../../../../../src/planner/producer_cursor.hpp#L28) | declares callable signatures. |  · [reviewed contract](#b0007) |
| [B0008 · 29–29](../../../../../src/planner/producer_cursor.hpp#L29) | Callable definition: void await_resume() const noexcept | calls  · [reviewed contract](#b0008) |
| [B0009 · 30–49](../../../../../src/planner/producer_cursor.hpp#L30) | Type/record definition: struct promise_type | returns Task{Handle::from_promise(*this)}; {}; source comment (unverified): // Throwing work must stay in Engine::step; an exception from resumed · [reviewed contract](#b0009) |
| [B0010 · 50–54](../../../../../src/planner/producer_cursor.hpp#L50) | declares types or opens a type body; declares values/defaults or compile-time conditions. |  · [reviewed contract](#b0010) |
| [B0011 · 55–58](../../../../../src/planner/producer_cursor.hpp#L55) | Callable definition: void start(Task& task) noexcept | calls promise · [reviewed contract](#b0011) |
| [B0012 · 59–60](../../../../../src/planner/producer_cursor.hpp#L59) | Explanatory comments or spacing. | source comment (unverified): // Cancellation is outside advance accounting. Tear down live frames from the · [reviewed contract](#b0012) |
| [B0013 · 61–69](../../../../../src/planner/producer_cursor.hpp#L61) | Callable definition: void cancel() noexcept | calls promise, destroy; 1 loop sites; source comment (unverified): // Cancellation is outside advance accounting. Tear down live frames from the · [reviewed contract](#b0013) |
| [B0014 · 70–81](../../../../../src/planner/producer_cursor.hpp#L70) | Callable definition: UnitResult step(const UnitContext& context) | calls promise, permits, execute, resume; returns {}; {UnitEvent::depth_blocked, p.requested_depth}; source comment (unverified): // failure leaves operation and suspension intact · [reviewed contract](#b0014) |
| [B0015 · 82–82](../../../../../src/planner/producer_cursor.hpp#L82) | Closes surrounding scope/type. |  · [reviewed contract](#b0015) |
| [B0016 · 83–90](../../../../../src/planner/producer_cursor.hpp#L83) | Callable definition: inline void Task::await_suspend(Handle parent) noexcept | calls promise · [reviewed contract](#b0016) |
| [B0017 · 91–95](../../../../../src/planner/producer_cursor.hpp#L91) | Callable definition: inline void Task::promise_type::Finish::await_suspend(Handle h) const noexcept | calls promise · [reviewed contract](#b0017) |
| [B0018 · 96–106](../../../../../src/planner/producer_cursor.hpp#L96) | Type/record definition: template&lt;class F&gt; struct Operation | returns false · [reviewed contract](#b0018) |
| [B0019 · 107–109](../../../../../src/planner/producer_cursor.hpp#L107) | Callable definition: template&lt;class F&gt; auto operation(F f, std::size_t depth = 0) noexcept | calls std::move; returns Operation&lt;F&gt;{std::move(f), depth} · [reviewed contract](#b0019) |
| [B0020 · 110–110](../../../../../src/planner/producer_cursor.hpp#L110) | Closes surrounding scope/type. | source comment (unverified): // namespace crown::planner::continuation_detail::producer_private · [reviewed contract](#b0020) |

## B0001

[Lines 1–19](../../../../../src/planner/producer_cursor.hpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L1-L19:sha256:ff9f08685020410f0ad5b26f9e14328fb858fb7ffef4c252b2a4dca9592d05f3
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Guard/import the producer header, open producer_private, forward-declare Engine/promise_type, and begin Task with its Handle alias, empty handle member and noexcept default constructor. |
| inputs / outputs | The alias names std::coroutine_handle&lt;promise_type&gt;; default Task() takes no argument and creates an empty handle wrapper. The Handle-taking constructor is adjacent at line 20, outside this span; it stores the supplied handle, which may be empty, without validating it. |
| invariants | Task is the move-only RAII wrapper implemented by the adjacent move/destructor definitions. The Handle value alone does not own or destroy a frame. The attached coroutine note states a control-flow/accounting boundary, not proof from these declarations. |
| ownership | An empty default Task owns no frame. If the adjacent constructor receives a valid frame handle, Task manages that frame and destroys it on release; an empty supplied handle leaves no frame to own. Move operations transfer and clear the old handle. The raw Handle alias is a non-owning coroutine handle value. |
| failure | Header/type errors fail compilation. The default constructor is noexcept and initializes an empty handle; frame creation and saved allocating operations have their separate surrounding contracts. |
| cost | Header parsing and fixed empty-handle initialization here. Constructing the empty Task does not allocate a coroutine frame; actual coroutine creation, resume/step work and destruction occur through the adjacent implementation. |
| Design | [src/planner/producer_cursor.hpp](../../../../../src/planner/producer_cursor.hpp), [docs/planner_continuations.md](../../../../planner_continuations.md) |

## B0002

[Lines 20–20](../../../../../src/planner/producer_cursor.hpp#L20); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
explicit Task(Handle h) noexcept : handle(h) {}
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Adopt one coroutine handle into its move-only RAII Task. |
| inputs / outputs | Stores a promise-typed handle. |
| invariants | Caller supplies a live frame and establishes links before stepping. |
| ownership | Task owns frame until move/detach. |
| failure | No exception; validity is caller precondition. |
| cost | Constant handle copy. |
| Design | [src/planner/producer_cursor.hpp](../../../../../src/planner/producer_cursor.hpp), [docs/planner_continuations.md](../../../../planner_continuations.md), [src/planner/continuation_machine.hpp](../../../../../src/planner/continuation_machine.hpp), [src/planner/exact.cpp](../../../../../src/planner/exact.cpp), [src/planner/candidate_generator.cpp](../../../../../src/planner/candidate_generator.cpp), [src/planner/residual_trace.cpp](../../../../../src/planner/residual_trace.cpp) |

## B0003

[Lines 21–21](../../../../../src/planner/producer_cursor.hpp#L21); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Task(Task&& t) noexcept : handle(std::exchange(t.handle, {})) {}
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Transfer frame ownership without double destruction. |
| inputs / outputs | Moves handle and clears source. |
| invariants | Only destination owns after move. |
| ownership | Transfers handle, not coroutine locals. |
| failure | No exception. |
| cost | Constant exchange. |
| Design | [src/planner/producer_cursor.hpp](../../../../../src/planner/producer_cursor.hpp), [docs/planner_continuations.md](../../../../planner_continuations.md), [src/planner/continuation_machine.hpp](../../../../../src/planner/continuation_machine.hpp), [src/planner/exact.cpp](../../../../../src/planner/exact.cpp), [src/planner/candidate_generator.cpp](../../../../../src/planner/candidate_generator.cpp), [src/planner/residual_trace.cpp](../../../../../src/planner/residual_trace.cpp) |

## B0004

[Lines 22–25](../../../../../src/planner/producer_cursor.hpp#L22); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Task& operator=(Task&& t) noexcept {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Replace current owned frame with another Task's frame. |
| inputs / outputs | Ignores self-move; destroys current frame then exchanges source handle. |
| invariants | Old frame is destroyed first; Engine must not retain a stale active pointer. |
| ownership | Transfers ownership and empties source. |
| failure | No exception intended from frame cleanup. |
| cost | Handle work plus arbitrary destructor/deallocation cost. |
| Design | [src/planner/producer_cursor.hpp](../../../../../src/planner/producer_cursor.hpp), [docs/planner_continuations.md](../../../../planner_continuations.md), [src/planner/continuation_machine.hpp](../../../../../src/planner/continuation_machine.hpp), [src/planner/exact.cpp](../../../../../src/planner/exact.cpp), [src/planner/candidate_generator.cpp](../../../../../src/planner/candidate_generator.cpp), [src/planner/residual_trace.cpp](../../../../../src/planner/residual_trace.cpp) |

## B0005

[Lines 26–26](../../../../../src/planner/producer_cursor.hpp#L26); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
~Task() { if (handle) handle.destroy(); }
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Destroy a frame still owned by this Task. |
| inputs / outputs | Destroys nonempty handle. |
| invariants | Cancellation clears owner handle before destroying frame to avoid double destroy. |
| ownership | Owns frame through handle; backlinks do not own. |
| failure | Frame cleanup is intended not to throw. |
| cost | Depends on locals and allocator; not constant-time. |
| Design | [src/planner/producer_cursor.hpp](../../../../../src/planner/producer_cursor.hpp), [docs/planner_continuations.md](../../../../planner_continuations.md), [src/planner/continuation_machine.hpp](../../../../../src/planner/continuation_machine.hpp), [src/planner/exact.cpp](../../../../../src/planner/exact.cpp), [src/planner/candidate_generator.cpp](../../../../../src/planner/candidate_generator.cpp), [src/planner/residual_trace.cpp](../../../../../src/planner/residual_trace.cpp) |

## B0006

[Lines 27–27](../../../../../src/planner/producer_cursor.hpp#L27); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
  bool await_ready() const noexcept { return false; }
  void await_suspend(Handle parent) noexcept;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Force Task awaits to suspend so Engine can switch active cursors. |
| inputs / outputs | Always returns false. |
| invariants | await_suspend installs parent/owner links; readiness does not. |
| ownership | Reads no state. |
| failure | No exception. |
| cost | Constant return. |
| Design | [src/planner/producer_cursor.hpp](../../../../../src/planner/producer_cursor.hpp), [docs/planner_continuations.md](../../../../planner_continuations.md), [src/planner/continuation_machine.hpp](../../../../../src/planner/continuation_machine.hpp), [src/planner/exact.cpp](../../../../../src/planner/exact.cpp), [src/planner/candidate_generator.cpp](../../../../../src/planner/candidate_generator.cpp), [src/planner/residual_trace.cpp](../../../../../src/planner/residual_trace.cpp) |

## B0007

[Lines 28–28](../../../../../src/planner/producer_cursor.hpp#L28); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L28-L28:sha256:3ebab1e9b73c977dcedcf25ca33d11b431234afc30d19eff0739acf302d21812
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Declare await_suspend in src/planner/producer_cursor.hpp with the exact signatures shown in this span. |
| inputs / outputs | Signatures: void await_suspend(Handle parent) noexcept;. These declarations specify parameter and result types; definitions supply runtime work. |
| invariants | The declarations fix C++ call types only; they do not execute, validate arguments, or create proof authority. |
| ownership | the signatures establish no separate retained owner. |
| failure | Ill-formed or mismatched declarations fail compilation/linkage. Runtime exception and resource-stop behavior belongs to each definition. |
| cost | The compiler parses the signatures; there is no runtime work or allocation until a definition is called. |
| Design | [src/planner/producer_cursor.hpp](../../../../../src/planner/producer_cursor.hpp), [docs/planner_continuations.md](../../../../planner_continuations.md) |

## B0008

[Lines 29–29](../../../../../src/planner/producer_cursor.hpp#L29); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
  void await_resume() const noexcept {}
  struct promise_type {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Resume parent after child completion without a value. |
| inputs / outputs | Returns void; completion/candidate data is communicated through Engine/owner state. |
| invariants | Retains no result. |
| ownership | Owns nothing. |
| failure | No exception. |
| cost | No-op. |
| Design | [src/planner/producer_cursor.hpp](../../../../../src/planner/producer_cursor.hpp), [docs/planner_continuations.md](../../../../planner_continuations.md), [src/planner/continuation_machine.hpp](../../../../../src/planner/continuation_machine.hpp), [src/planner/exact.cpp](../../../../../src/planner/exact.cpp), [src/planner/candidate_generator.cpp](../../../../../src/planner/candidate_generator.cpp), [src/planner/residual_trace.cpp](../../../../../src/planner/residual_trace.cpp) |

## B0009

[Lines 30–49](../../../../../src/planner/producer_cursor.hpp#L30); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct promise_type {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Define promise backlinks, pending operation slot and Task suspension policy. |
| inputs / outputs | Stores nonowning Engine/parent/owner links, operation address/callback and requested depth; provides return object, initial/final suspend and void return. |
| invariants | Throwing operations run in Engine::step; resumed control must not throw. A throw reaching unhandled_exception terminates. |
| ownership | Promise and closure/locals live in coroutine frame; Engine and owner links are borrows. |
| failure | Unexpected exception during resume is fatal. |
| cost | Frame allocation/cleanup plus closure/local storage; pointer protocol itself is fixed size. |
| Design | [src/planner/producer_cursor.hpp](../../../../../src/planner/producer_cursor.hpp), [docs/planner_continuations.md](../../../../planner_continuations.md), [src/planner/continuation_machine.hpp](../../../../../src/planner/continuation_machine.hpp), [src/planner/exact.cpp](../../../../../src/planner/exact.cpp), [src/planner/candidate_generator.cpp](../../../../../src/planner/candidate_generator.cpp), [src/planner/residual_trace.cpp](../../../../../src/planner/residual_trace.cpp) |

## B0010

[Lines 50–54](../../../../../src/planner/producer_cursor.hpp#L50); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L50-L54:sha256:7262c31771b55edd5f98707595889ccbcde6c3323cf7afb66fa6f33da1093868
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Close the Task definition and begin Engine with its active coroutine handle, logical depth, and administrative-only flag. |
| inputs / outputs | This block establishes Engine state. start(Task&) sets the active handle, the task promise owner, and depth; cancel() later walks and destroys the active chain. |
| invariants | Engine::active refers to a coroutine owned by a Task. Cancellation detaches each Task handle before destroying its frame, so the same frame is not destroyed twice. |
| ownership | Task owns each coroutine frame; Engine::active is a non-owning handle. depth and administrative_only are stored by value. |
| failure | The fields do not throw. start and cancel are noexcept; malformed coroutine ownership would violate the producer protocol rather than create a handled status here. |
| cost | Fixed handle, depth, and flag storage. Cancellation cost is proportional to the live coroutine chain and belongs to cancel(), not these fields. |
| Design | [src/planner/producer_cursor.hpp](../../../../../src/planner/producer_cursor.hpp), [docs/planner_continuations.md](../../../../planner_continuations.md) |

## B0011

[Lines 55–58](../../../../../src/planner/producer_cursor.hpp#L55); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void start(Task& task) noexcept {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Install root Task as active and initialize logical depth. |
| inputs / outputs | Sets active handle, writes Engine/owner backlinks and depth=1. |
| invariants | Requires live task and idle/reset Engine; no defensive validation. |
| ownership | Borrows Task while it owns frame. |
| failure | No exception/status for invalid use. |
| cost | Constant pointer/scalar updates. |
| Design | [src/planner/producer_cursor.hpp](../../../../../src/planner/producer_cursor.hpp), [docs/planner_continuations.md](../../../../planner_continuations.md), [src/planner/continuation_machine.hpp](../../../../../src/planner/continuation_machine.hpp), [src/planner/exact.cpp](../../../../../src/planner/exact.cpp), [src/planner/candidate_generator.cpp](../../../../../src/planner/candidate_generator.cpp), [src/planner/residual_trace.cpp](../../../../../src/planner/residual_trace.cpp) |

## B0012

[Lines 59–60](../../../../../src/planner/producer_cursor.hpp#L59); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L59-L60:sha256:380c98265c38214f3aa11ea35a44bd4d119e78d70c8ecdb636544d572b78d7a7
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Use the adjacent note for cancel: Cancellation is outside advance accounting. Tear down live frames from the leaf upward and detach their owning Task first, avoiding recursive unwind. Confirm behavior against the declaration and implementation; comment text alone does not enforce or prove it. |
| inputs / outputs | This comment has no inputs or outputs. It accompanies cancel; use the adjacent declaration and implementation for the actual values and result. |
| invariants | This is static guidance only. The comment cannot alter state or guarantee that its wording holds. |
| ownership | The note owns no storage and changes no lifetime; ownership and borrowing for cancel come from its actual types and implementation. |
| failure | Reading the comment has no runtime failure path. Compile or link errors, exceptions, and resource stops belong to the adjacent code. |
| cost | The comment adds no runtime instructions, allocation, clock read, counter debit, or engine hook; only source-text processing is added. |
| Design | [src/planner/producer_cursor.hpp](../../../../../src/planner/producer_cursor.hpp), [docs/planner_continuations.md](../../../../planner_continuations.md) |

## B0013

[Lines 61–69](../../../../../src/planner/producer_cursor.hpp#L61); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void cancel() noexcept {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Destroy live coroutine chain leaf-first without recursive child unwind. |
| inputs / outputs | Follows parent handles, clears owner handle before destroy, then sets depth zero. |
| invariants | Outside advance accounting; published handles/non-frame payloads belong to facade. Deallocation is not constant-time. |
| ownership | Borrows owner Tasks and destroys active frames only. |
| failure | No exception intended; links must identify live objects. |
| cost | O(active frames) plus arbitrary destructor/deallocation work. |
| Design | [src/planner/producer_cursor.hpp](../../../../../src/planner/producer_cursor.hpp), [docs/planner_continuations.md](../../../../planner_continuations.md), [src/planner/continuation_machine.hpp](../../../../../src/planner/continuation_machine.hpp), [src/planner/exact.cpp](../../../../../src/planner/exact.cpp), [src/planner/candidate_generator.cpp](../../../../../src/planner/candidate_generator.cpp), [src/planner/residual_trace.cpp](../../../../../src/planner/residual_trace.cpp) |

## B0014

[Lines 70–81](../../../../../src/planner/producer_cursor.hpp#L70); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
UnitResult step(const UnitContext& context) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Execute a pending operation then resume active coroutine under logical-depth admission. |
| inputs / outputs | Inactive returns default; otherwise checks requested_depth, executes callback, clears it only on success, then resumes once. |
| invariants | Callback throw leaves slot and suspended frame intact; retry also relies on prepare-before-publication. Throw inside resume terminates; depth is not CPU time. |
| ownership | Borrows frame/context; closure is stored in frame. |
| failure | Callback exceptions propagate deliberately; no handler here. |
| cost | One callback plus nonallocating control; closure cost may include allocation. |
| Design | [src/planner/producer_cursor.hpp](../../../../../src/planner/producer_cursor.hpp), [docs/planner_continuations.md](../../../../planner_continuations.md), [src/planner/continuation_machine.hpp](../../../../../src/planner/continuation_machine.hpp), [src/planner/exact.cpp](../../../../../src/planner/exact.cpp), [src/planner/candidate_generator.cpp](../../../../../src/planner/candidate_generator.cpp), [src/planner/residual_trace.cpp](../../../../../src/planner/residual_trace.cpp) |

## B0015

[Lines 82–82](../../../../../src/planner/producer_cursor.hpp#L82); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L82-L82:sha256:aa1d1a63390229c798347e83a0405441c9400035284ad168c1bf6cdf1d70a370
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | This block close the current class or struct and its enclosing lexical scope. |
| inputs / outputs | A scope delimiter has no call inputs or outputs; it controls which following declarations belong to the C++ namespace, class, or helper scope. |
| invariants | The braces set lexical visibility and type boundaries only. Any attached note is documentation and does not enforce behavior. |
| ownership | The delimiter and note acquire, release, or transfer no runtime object. Member lifetimes come from the enclosed type definitions. |
| failure | An unmatched or misplaced brace fails compilation; this block adds no runtime exception or resource-stop path. |
| cost | No runtime work or allocation is added. The compiler parses the scope boundary and comment. |
| Design | [src/planner/producer_cursor.hpp](../../../../../src/planner/producer_cursor.hpp), [docs/planner_continuations.md](../../../../planner_continuations.md) |

## B0016

[Lines 83–90](../../../../../src/planner/producer_cursor.hpp#L83); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
inline void Task::await_suspend(Handle parent) noexcept {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Link awaited child to parent Engine and make child active. |
| inputs / outputs | Copies Engine link, stores parent/owner backlinks, switches active and increments depth. |
| invariants | Parent and child handles must be live; no checks. |
| ownership | Task owns child; links nonowning. |
| failure | No exception. |
| cost | Constant pointer/depth updates. |
| Design | [src/planner/producer_cursor.hpp](../../../../../src/planner/producer_cursor.hpp), [docs/planner_continuations.md](../../../../planner_continuations.md), [src/planner/continuation_machine.hpp](../../../../../src/planner/continuation_machine.hpp), [src/planner/exact.cpp](../../../../../src/planner/exact.cpp), [src/planner/candidate_generator.cpp](../../../../../src/planner/candidate_generator.cpp), [src/planner/residual_trace.cpp](../../../../../src/planner/residual_trace.cpp) |

## B0017

[Lines 91–95](../../../../../src/planner/producer_cursor.hpp#L91); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
inline void Task::promise_type::Finish::await_suspend(Handle h) const noexcept {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Restore control to parent at final suspension. |
| inputs / outputs | Sets active to parent and decrements depth. |
| invariants | Child remains suspended and owned until Task cleanup. |
| ownership | Borrows frame/Engine; ownership unchanged. |
| failure | No exception; parent/depth protocol is precondition. |
| cost | Constant update. |
| Design | [src/planner/producer_cursor.hpp](../../../../../src/planner/producer_cursor.hpp), [docs/planner_continuations.md](../../../../planner_continuations.md), [src/planner/continuation_machine.hpp](../../../../../src/planner/continuation_machine.hpp), [src/planner/exact.cpp](../../../../../src/planner/exact.cpp), [src/planner/candidate_generator.cpp](../../../../../src/planner/candidate_generator.cpp), [src/planner/residual_trace.cpp](../../../../../src/planner/residual_trace.cpp) |

## B0018

[Lines 96–106](../../../../../src/planner/producer_cursor.hpp#L96); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
template<class F> struct Operation {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Store one potentially throwing operation as an awaiter in a coroutine frame. |
| inputs / outputs | Owns F and requested depth; await_suspend registers address, type-erased executor and depth in promise. |
| invariants | Address remains valid while suspended; Engine executes before resume and clears only after success. |
| ownership | Closure is in frame; promise borrows address. |
| failure | Callback can throw from Engine::step; resumed-control exceptions terminate. |
| cost | Closure storage depends on F; registration itself constant-time. |
| Design | [src/planner/producer_cursor.hpp](../../../../../src/planner/producer_cursor.hpp), [docs/planner_continuations.md](../../../../planner_continuations.md), [src/planner/continuation_machine.hpp](../../../../../src/planner/continuation_machine.hpp), [src/planner/exact.cpp](../../../../../src/planner/exact.cpp), [src/planner/candidate_generator.cpp](../../../../../src/planner/candidate_generator.cpp), [src/planner/residual_trace.cpp](../../../../../src/planner/residual_trace.cpp) |

## B0019

[Lines 107–109](../../../../../src/planner/producer_cursor.hpp#L107); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
template<class F> auto operation(F f, std::size_t depth = 0) noexcept {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Wrap callable and requested logical depth as Operation awaiter. |
| inputs / outputs | Moves F into wrapper; depth defaults to zero. |
| invariants | Factory only packages work. Nonthrowing F move is required by noexcept. |
| ownership | Returned awaiter owns closure through frame lifetime. |
| failure | Throwing F move terminates due noexcept. |
| cost | Wrapper plus F move/capture cost. |
| Design | [src/planner/producer_cursor.hpp](../../../../../src/planner/producer_cursor.hpp), [docs/planner_continuations.md](../../../../planner_continuations.md), [src/planner/continuation_machine.hpp](../../../../../src/planner/continuation_machine.hpp), [src/planner/exact.cpp](../../../../../src/planner/exact.cpp), [src/planner/candidate_generator.cpp](../../../../../src/planner/candidate_generator.cpp), [src/planner/residual_trace.cpp](../../../../../src/planner/residual_trace.cpp) |

## B0020

[Lines 110–110](../../../../../src/planner/producer_cursor.hpp#L110); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L110-L110:sha256:f22e39447e3d557b5c945301f03d763be8fee3acb694de10d4f4cdfc0e7cb0c2
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | This block close namespace crown::planner::continuation_detail::producer_private. |
| inputs / outputs | A scope delimiter has no call inputs or outputs; it controls which following declarations belong to the C++ namespace, class, or helper scope. |
| invariants | The braces set lexical visibility and type boundaries only. Any attached note is documentation and does not enforce behavior. |
| ownership | The delimiter and note acquire, release, or transfer no runtime object. Member lifetimes come from the enclosed type definitions. |
| failure | An unmatched or misplaced brace fails compilation; this block adds no runtime exception or resource-stop path. |
| cost | No runtime work or allocation is added. The compiler parses the scope boundary and comment. |
| Design | [src/planner/producer_cursor.hpp](../../../../../src/planner/producer_cursor.hpp), [docs/planner_continuations.md](../../../../planner_continuations.md) |
