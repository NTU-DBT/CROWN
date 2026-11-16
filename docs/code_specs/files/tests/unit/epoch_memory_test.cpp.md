# `tests/unit/epoch_memory_test.cpp` — block usage map

[Source](../../../../../tests/unit/epoch_memory_test.cpp) · [Source index](../../../README.md) · [Subsystem contracts](../../../subsystem_contracts.md) · [Reviewed primitives](../../../primitives.md)

Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection.

Snapshot SHA-256: `7abf5a9da5a868d1eb43acb4f5b1d08bfad56c978eb9816004ab18c3996df44b`. 212 lines partitioned into 15 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [tests](../../../subsystem_contracts.md#tests). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/code_review.md](../../../../code_review.md), [docs/reference_fuzz.md](../../../../reference_fuzz.md), [docs/task_ledger.md](../../../../task_ledger.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–15](../../../../../tests/unit/epoch_memory_test.cpp#L1) | Imports dependencies; declares namespace scope; declares aliases. |  · [reviewed contract](#b0001) |
| [B0002 · 16–18](../../../../../tests/unit/epoch_memory_test.cpp#L16) | Callable definition: void check(bool value,std::string_view message) | calls std::runtime_error, std::string; guard void check(bool value,std::string_view message) { · [reviewed contract](#b0002) |
| [B0003 · 19–23](../../../../../tests/unit/epoch_memory_test.cpp#L19) | Callable definition: void controller_only(const resource::MemoryAccount& account) | calls check_invariants, statistics, check, resource::MemoryAccount::control_bytes; guard check(current.allocations==1 && current.requested_bytes==resource::MemoryAccount::control_bytes(), · [reviewed contract](#b0003) |
| [B0004 · 24–29](../../../../../tests/unit/epoch_memory_test.cpp#L24) | Callable definition: template&lt;class F&gt;void denied(F&& action) | calls action, check, fault, std::runtime_error; guard check(failure.fault()==resource::MemoryFault::limit,"wrong epoch byte-limit failure");return; · [reviewed contract](#b0004) |
| [B0005 · 30–32](../../../../../tests/unit/epoch_memory_test.cpp#L30) | Callable definition: template&lt;class T&gt;resource::MemoryUsage buffer_usage(const std::vector&lt;T,resource::OwnerAllocator&lt;T&gt;&gt;& values) | calls get_allocator, allocation_usage, data, capacity; returns values.get_allocator().allocation_usage(values.data(),values.capacity()) · [reviewed contract](#b0005) |
| [B0006 · 33–71](../../../../../tests/unit/epoch_memory_test.cpp#L33) | Callable definition: void allocator_ownership() | calls static_assert, resource::MemoryAccount::create, source, Allocator; guard static_assert(!std::allocator_traits&lt;resource::MemoryAllocator&lt;int&gt;&gt;::propagate_on_container_move_a…; returns bit · [reviewed contract](#b0006) |
| [B0007 · 72–79](../../../../../tests/unit/epoch_memory_test.cpp#L72) | Callable definition: PhysicalPlan plan(bool indexed) | calls planner::lower_tree, s04_runtime::options; returns planner::lower_tree(catalog,query,tree,indexed?s04_runtime::options():PhysicalOptions{}) · [reviewed contract](#b0007) |
| [B0008 · 80–80](../../../../../tests/unit/epoch_memory_test.cpp#L80) | Callable definition: Row parent() | calls std::string; returns {std::string(@ ,11)+std::string(8192,@ ),std::int64_t{42}} · [reviewed contract](#b0008) |
| [B0009 · 81–81](../../../../../tests/unit/epoch_memory_test.cpp#L81) | Callable definition: Row child() | calls ; returns {std::int64_t{42}} · [reviewed contract](#b0009) |
| [B0010 · 82–84](../../../../../tests/unit/epoch_memory_test.cpp#L82) | Callable definition: SupportOptions options(bool trace,std::uint64_t cap=64*1024*1024) | calls ; returns value · [reviewed contract](#b0010) |
| [B0011 · 85–140](../../../../../tests/unit/epoch_memory_test.cpp#L85) | Callable definition: void journal_owners(bool indexed,bool trace) | calls runtime, plan, options, RuntimeTestProbe::memory_account; guard check(pending.stage(NodeId{1},child()),"journal fixture did not change its child");; growth emplace, insert; 3 loop sites · [reviewed contract](#b0011) |
| [B0012 · 141–158](../../../../../tests/unit/epoch_memory_test.cpp#L141) | Callable definition: void physical_owners(bool indexed) | calls options, runtime, plan, RuntimeTestProbe::memory_account; guard check(rows.size()==1 && rows.get_allocator().account().statistics().owner==account.statistics().own…; growth emplace, insert · [reviewed contract](#b0012) |
| [B0013 · 159–201](../../../../../tests/unit/epoch_memory_test.cpp#L159) | Callable definition: void limits_and_faults(bool indexed) | calls plan, runtime, options, apply; guard check(runtime.accounted_memory_statistics().peak_requested_bytes==peak,"exact retained epoch peak w…; growth emplace, insert; 2 loop sites · [reviewed contract](#b0013) |
| [B0014 · 202–202](../../../../../tests/unit/epoch_memory_test.cpp#L202) | Closes surrounding scope/type. | source comment (unverified): // namespace · [reviewed contract](#b0014) |
| [B0015 · 203–212](../../../../../tests/unit/epoch_memory_test.cpp#L203) | Callable definition: int main() | calls allocator_ownership, journal_owners, physical_owners, limits_and_faults; returns 1; 2 loop sites · [reviewed contract](#b0015) |

## B0001

[Lines 1–15](../../../../../tests/unit/epoch_memory_test.cpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L1-L15:sha256:937f4b0bee63b95ce86f34cfe81cb8bf72604ed6ac0c57b88a0622feb2c08693
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Prepare epoch_memory_test.cpp: include "crown/api/error.hpp", "crown/runtime/physical.hpp", "indexed_runtime_fixture.hpp", "runtime_probe.hpp", "index_allocation.hpp", &lt;algorithm&gt;, &lt;iostream&gt;, &lt;optional&gt;, &lt;stdexcept&gt;, &lt;type_traits&gt;; bind local aliases/name imports. |
| inputs / outputs | Compiler-visible dependencies, names and the recorded declarations in; declarations available to the following fixture/CLI/example definitions out. |
| invariants | Declarations are scoped to this source/header and its selected ABI. Included code has its own effects; names and editable fixture values do not confer proof, admission or publication authority. |
| ownership | Aliases/includes do not create a query owner. Pointers/references/views are non-owning. Containers own their elements, which can themselves be borrowed pointers or numeric IDs. Only documented owning shared-control handles retain controls; IDs/slot-handle values do not independently keep an arena/runtime alive. |
| failure | Missing headers, ill-formed names/types, failed static assertions or active #error directives stop compilation. No runtime rejection/rollback mechanism is implemented by aliases or function prototypes. |
| cost | Preprocessing and type/constraint instantiation cost compilation. Alias/prototype syntax does not invoke the declared operation; any included definitions keep their own initialization effects. |
| Design | [tests/unit/epoch_memory_test.cpp](../../../../../tests/unit/epoch_memory_test.cpp), [docs/query_memory.md](../../../../query_memory.md), [docs/code_review.md](../../../../code_review.md) |

## B0002

[Lines 16–18](../../../../../tests/unit/epoch_memory_test.cpp#L16); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void check(bool value,std::string_view message) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Provide a failure-only string conversion assertion for epoch tests. |
| inputs / outputs | Input: bool and borrowed string_view. Output: void. |
| invariants | The std::string and runtime_error are constructed only when false. |
| ownership | No retained storage. |
| failure | False throws runtime_error; true does not copy the message. |
| cost | One branch predicate; no allocation-call guarantee. |
| Design | [tests/unit/epoch_memory_test.cpp](../../../../../tests/unit/epoch_memory_test.cpp) |

## B0003

[Lines 19–23](../../../../../tests/unit/epoch_memory_test.cpp#L19); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void controller_only(const resource::MemoryAccount& account) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Require release of funded epoch arrays and flags to leave only the controller. |
| inputs / outputs | Input: MemoryAccount reference. |
| invariants | Checks invariants and current allocation count 1 plus requested bytes exactly control_bytes(). |
| ownership | Caller keeps account alive while the helper inspects current state. |
| failure | Mismatch throws; does not inspect process heap. |
| cost | Fixed statistics read. |
| Design | [tests/unit/epoch_memory_test.cpp](../../../../../tests/unit/epoch_memory_test.cpp), [include/crown/resource/memory.hpp](../../../../../include/crown/resource/memory.hpp) |

## B0004

[Lines 24–29](../../../../../tests/unit/epoch_memory_test.cpp#L24); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
template<class F>void denied(F&& action) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Assert that an epoch action is denied by the original account limit. |
| inputs / outputs | Input: forwarding-reference callable; void result. |
| invariants | Calls named action() as an lvalue, catches MemoryFailure only when its fault is limit, and returns; no forwarding occurs. |
| ownership | Callable is borrowed for the call and does not escape. |
| failure | Wrong fault fails through check; successful action triggers runtime_error; other exceptions propagate. |
| cost | One action and exception dispatch; error text only on exceptional assertion path. |
| Design | [tests/unit/epoch_memory_test.cpp](../../../../../tests/unit/epoch_memory_test.cpp), [include/crown/resource/memory.hpp](../../../../../include/crown/resource/memory.hpp) |

## B0005

[Lines 30–32](../../../../../tests/unit/epoch_memory_test.cpp#L30); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
template<class T>resource::MemoryUsage buffer_usage(const std::vector<T,resource::OwnerAllocator<T>>& values) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Read the exact accounted request for a live OwnerAllocator vector buffer. |
| inputs / outputs | Input: const vector with OwnerAllocator. Output: MemoryUsage from allocator.allocation_usage(data,capacity). |
| invariants | The reading describes the buffer allocation represented by the supplied pointer/capacity; it does not total nested tuple payloads or all account owners. |
| ownership | Vector retains buffer and allocator/account; helper returns scalar usage only. |
| failure | Allocator usage query behavior for an empty buffer is delegated to the allocator. |
| cost | Constant-time allocation lookup for the buffer, not a scan of all account allocations. |
| Design | [tests/unit/epoch_memory_test.cpp](../../../../../tests/unit/epoch_memory_test.cpp), [include/crown/resource/owner_allocator.hpp](../../../../../include/crown/resource/owner_allocator.hpp), [include/crown/resource/allocator.hpp](../../../../../include/crown/resource/allocator.hpp) |

## B0006

[Lines 33–71](../../../../../tests/unit/epoch_memory_test.cpp#L33); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void allocator_ownership() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Check OwnerAllocator propagation and transfer behavior across result, copy, swap, failure, and packed-bool buffers. |
| inputs / outputs | No inputs. Uses two 1 MiB accounts, source and target int vectors, a third vector, one failed copy, and a 65-bit vector&lt;bool&gt;. |
| invariants | Static assertions require MemoryAllocator move propagation false but OwnerAllocator copy/move/swap propagation true and vector nothrow move assignment. Cross-account move and swap with fail-after-zero make zero intercepted new calls and transfer the source buffer plus allocator/account/attribution. Copy assignment creates a distinct buffer under target’s allocator. Failed copy leaves current bytes/source values; bit-buffer move preserves 65 true bits and journal_undo attribution. |
| ownership | Buffers carry their allocator and account; move/swap transfer storage, copy allocates new storage; local objects release before both controller-only checks. |
| failure | Injected copy bad_alloc must occur and leave usage/source intact; all ownership mismatches fail assertions. |
| cost | Small fixed vectors; scope hooks only test selected move/swap/copy calls. No general allocation-free claim beyond those tested operations. |
| Design | [tests/unit/epoch_memory_test.cpp](../../../../../tests/unit/epoch_memory_test.cpp), [include/crown/resource/owner_allocator.hpp](../../../../../include/crown/resource/owner_allocator.hpp), [include/crown/resource/allocator.hpp](../../../../../include/crown/resource/allocator.hpp), [tests/support/index_allocation.hpp](../../../../../tests/support/index_allocation.hpp) |

## B0007

[Lines 72–79](../../../../../tests/unit/epoch_memory_test.cpp#L72); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
PhysicalPlan plan(bool indexed) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Lower a two-node native join plan for one backend. |
| inputs / outputs | Input: indexed selector. Output: PhysicalPlan for two tables joined on int64 y with string x projected. |
| invariants | Indexed path uses fixture options; reference path uses default physical options. |
| ownership | Catalog/query/tree are ordinary fixture values; resulting plan is returned by value. |
| failure | Lowering failures propagate. |
| cost | Fixed two-node plan setup and lowering. |
| Design | [tests/unit/epoch_memory_test.cpp](../../../../../tests/unit/epoch_memory_test.cpp), [tests/support/indexed_runtime_fixture.hpp](../../../../../tests/support/indexed_runtime_fixture.hpp), [include/crown/planner/lower.hpp](../../../../../include/crown/planner/lower.hpp) |

## B0008

[Lines 80–80](../../../../../tests/unit/epoch_memory_test.cpp#L80); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Row parent(){return {std::string("epoch\0bytes",11)+std::string(8192,'e'),std::int64_t{42}};}
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Build the long parent row used to keep a compact key payload alive. |
| inputs / outputs | Input: none. Output: two-cell Row whose string is std::string("epoch\0bytes",11) followed by std::string(8192,'e'), then int64 42. |
| invariants | The first 11 bytes are the sequence epoch, NUL, bytes; the suffix has exactly 8,192 lowercase e bytes, for an 8,203-byte string. This is an ordinary caller Row before native adaptation. |
| ownership | Returned Row owns its std::string. |
| failure | String allocation can throw; no runtime account applies yet. |
| cost | One long ordinary string construction. |
| Design | [tests/unit/epoch_memory_test.cpp](../../../../../tests/unit/epoch_memory_test.cpp), [include/crown/ir/model.hpp](../../../../../include/crown/ir/model.hpp), [docs/query_memory.md](../../../../query_memory.md) |

## B0009

[Lines 81–81](../../../../../tests/unit/epoch_memory_test.cpp#L81); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Row child(){return {std::int64_t{42}};}
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Build the child row matching the parent join key. |
| inputs / outputs | No input. Output: one-cell Row containing int64 42. |
| invariants | Value matches parent cell 2. |
| ownership | Returns ordinary row value. |
| failure | Construction failure propagates. |
| cost | Fixed scalar/row construction. |
| Design | [tests/unit/epoch_memory_test.cpp](../../../../../tests/unit/epoch_memory_test.cpp), [include/crown/ir/model.hpp](../../../../../include/crown/ir/model.hpp) |

## B0010

[Lines 82–84](../../../../../tests/unit/epoch_memory_test.cpp#L82); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
SupportOptions options(bool trace,std::uint64_t cap=64*1024*1024) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Create support runtime options for trace capture and byte-cap tests. |
| inputs / outputs | Inputs: trace bool and cap default 64 MiB. Output: SupportOptions. |
| invariants | Sets capture_transitions to trace and memory_limit_bytes to cap; leaves work/other options default. |
| ownership | Ordinary options value; no account or arrays are allocated here. |
| failure | Validation occurs later during runtime construction/use. |
| cost | Fixed assignments. |
| Design | [tests/unit/epoch_memory_test.cpp](../../../../../tests/unit/epoch_memory_test.cpp), [include/crown/runtime/support.hpp](../../../../../include/crown/runtime/support.hpp) |

## B0011

[Lines 85–140](../../../../../tests/unit/epoch_memory_test.cpp#L85); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void journal_owners(bool indexed,bool trace) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Verify journal/event/transition ownership, child-flag copies, retention, and cleanup for trace on/off. |
| inputs / outputs | Inputs: backend selector and trace flag. Inserts parent at seq1, stages child at seq2, commits while fault-after-zero is active. |
| invariants | Commit makes zero intercepted new calls. Journal records exist and event/transition arrays bind original account. Trace mode has one real allocation each for arrays; copied epoch adds exactly copied transition-buffer usage while sharing journal pointer. Trace-off arrays are empty and use zero buffer usage. Each populated child_present bit vector uses original account/journal_undo; its copy adds one allocation matching new-call delta and releases cleanly. Held epoch survives runtime destruction; trace tuples are accounted, event sequence is 2; final release under fault-after-zero has zero calls. |
| ownership | Epoch owns a shared journal handle and OwnerAllocator transition array; journal records/pins and optional events retain native tuples in the account. Copying epoch duplicates its transition array but shares journal; child-flag copy owns its new buffer. Account remains through handle copies. |
| failure | Bad allocation or wrong allocator/purpose/value fails. Only scoped commit/copy/release paths claim zero/known new calls. |
| cost | One parent and one child route, optionally recorded trace arrays; the test reads per-buffer exact request and account counters, not total process memory or CPU. |
| Design | [tests/unit/epoch_memory_test.cpp](../../../../../tests/unit/epoch_memory_test.cpp), [include/crown/runtime/support.hpp](../../../../../include/crown/runtime/support.hpp), [src/runtime/support.cpp](../../../../../src/runtime/support.cpp), [include/crown/resource/owner_allocator.hpp](../../../../../include/crown/resource/owner_allocator.hpp), [tests/support/runtime_probe.hpp](../../../../../tests/support/runtime_probe.hpp), [tests/support/index_allocation.hpp](../../../../../tests/support/index_allocation.hpp), [docs/invariant_memory.md](../../../../invariant_memory.md) |

## B0012

[Lines 141–158](../../../../../tests/unit/epoch_memory_test.cpp#L141); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void physical_owners(bool indexed) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Verify physical preview derivation array remains funded and readable after runtime destruction. |
| inputs / outputs | Input: backend selector. Applies parent, prepares child physical insert, retains preview’s one derivation, then commits. |
| invariants | Preview vector has one row, original account owner, and one buffer request. Commit under fault-after-zero makes zero intercepted new calls. Retained epoch reports occurrence 1, child row, after-count 1 after runtime facade closes. |
| ownership | PhysicalEpoch owns moved preview arrays and account-backed tuple; account handle remains for final cleanup. |
| failure | Mismatched preview/retained values or allocation behavior fails; preparation/commit errors propagate. |
| cost | One prepared source update and one output derivation in this plan; measured buffer usage is only vector storage. |
| Design | [tests/unit/epoch_memory_test.cpp](../../../../../tests/unit/epoch_memory_test.cpp), [include/crown/runtime/physical.hpp](../../../../../include/crown/runtime/physical.hpp), [src/runtime/physical.cpp](../../../../../src/runtime/physical.cpp), [include/crown/resource/owner_allocator.hpp](../../../../../include/crown/resource/owner_allocator.hpp), [tests/support/runtime_probe.hpp](../../../../../tests/support/runtime_probe.hpp), [tests/support/index_allocation.hpp](../../../../../tests/support/index_allocation.hpp) |

## B0013

[Lines 159–201](../../../../../tests/unit/epoch_memory_test.cpp#L159); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void limits_and_faults(bool indexed) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Measure retained support-epoch peak, test exact/one-under caps, and sweep transient allocation failures. |
| inputs / outputs | Input: backend selector. Sequence: parent insert, child insert, child erase; peak fixture retains two epoch results simultaneously before measurement. Runs exact and peak-1 caps, then fail-after sweep 0..1023 until first successful child insertion. |
| invariants | Exact cap preserves measured peak. One-under denial preserves ready state, canonical state and held child trace; after releasing held epoch, same seq3 erase succeeds and has no answer. Persistent sweep checks every bad_alloc leaves old canonical state and journal_undo/output_buffer purpose usage unchanged, then same input retry succeeds. Requires at least 10 failures and eventual success; not an exact calibrated count. |
| ownership | Held SupportEpoch pins journal/trace/flags and can consume the original account, causing the later update denial. Retry uses same cap after release. Canonical DTO comparison is caller export. |
| failure | Only MemoryFailure(limit) via denied and bad_alloc via hook count as expected; account invariants checked each fault position. |
| cost | At most 1,024 fault points per backend, stopping on first success. Peak is requested account bytes including retained output overlap; hook counts operator-new positions, not bytes or CPU. |
| Design | [tests/unit/epoch_memory_test.cpp](../../../../../tests/unit/epoch_memory_test.cpp), [include/crown/runtime/support.hpp](../../../../../include/crown/runtime/support.hpp), [src/runtime/support.cpp](../../../../../src/runtime/support.cpp), [tests/support/index_allocation.hpp](../../../../../tests/support/index_allocation.hpp), [docs/query_memory.md](../../../../query_memory.md) |

## B0014

[Lines 202–202](../../../../../tests/unit/epoch_memory_test.cpp#L202); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L202-L202:sha256:533f16bca7d58f44b3103b92e3485d22cfbb34bbad5ea3f3fa3b5a9dcb24ec89
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Close the recorded declaration scopes in epoch_memory_test.cpp: namespace (anonymous). |
| inputs / outputs | Preceding namespace, type or initializer declarations in; completed lexical boundary out. |
| invariants | Brace-opening context is recorded in root-scope-context-v1.json. These are declaration/initializer boundaries, not an independent update, validation or recovery operation. |
| ownership | Enclosing objects and borrowed fields keep their declared ownership. This punctuation creates no new owner. |
| failure | Malformed scope syntax is a compile error. Any initializer/constructor failure belongs to the enclosing object declaration. |
| cost | No separate loop, guard or engine call is introduced by the delimiter; enclosing initialization and object lifetime still have their actual costs. |
| Design | [tests/unit/epoch_memory_test.cpp](../../../../../tests/unit/epoch_memory_test.cpp), [docs/query_memory.md](../../../../query_memory.md), [docs/code_review.md](../../../../code_review.md) |

## B0015

[Lines 203–212](../../../../../tests/unit/epoch_memory_test.cpp#L203); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
int main() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Run allocator ownership and journal/physical epoch matrices for both storage backends. |
| inputs / outputs | No inputs. Runs allocator_ownership once; for reference and indexed backends, trace off/on journal cases, physical owner case and cap/fault case. |
| invariants | Catches std::exception, writes failure and returns 1; otherwise prints completion and returns 0. Output is the source program’s behavior only. |
| ownership | Each case releases local objects by scope and explicitly checks controller-only account cleanup. |
| failure | Any assertion or runtime failure produces nonzero status. |
| cost | Finite fixture rows and bounded 1,024-position sweeps per backend. |
| Design | [tests/unit/epoch_memory_test.cpp](../../../../../tests/unit/epoch_memory_test.cpp), [tests/support/indexed_runtime_fixture.hpp](../../../../../tests/support/indexed_runtime_fixture.hpp), [tests/support/index_allocation.hpp](../../../../../tests/support/index_allocation.hpp) |
