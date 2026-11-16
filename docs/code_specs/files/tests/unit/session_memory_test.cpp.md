# `tests/unit/session_memory_test.cpp` — block usage map

[Source](../../../../../tests/unit/session_memory_test.cpp) · [Source index](../../../README.md) · [Subsystem contracts](../../../subsystem_contracts.md) · [Reviewed primitives](../../../primitives.md)

Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection.

Snapshot SHA-256: `ba9ec8596560d66f22de2d1c637fb6f384b00ce0bbb9bfe4ca15be8367f1b8f3`. 203 lines partitioned into 19 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [tests](../../../subsystem_contracts.md#tests). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/code_review.md](../../../../code_review.md), [docs/reference_fuzz.md](../../../../reference_fuzz.md), [docs/task_ledger.md](../../../../task_ledger.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–13](../../../../../tests/unit/session_memory_test.cpp#L1) | Imports dependencies; declares namespace scope; declares aliases; declares values/defaults or compile-time conditions. |  · [reviewed contract](#b0001) |
| [B0002 · 14–16](../../../../../tests/unit/session_memory_test.cpp#L14) | Callable definition: void check(bool value,std::string_view message) | calls std::runtime_error, std::string; guard void check(bool value,std::string_view message) { · [reviewed contract](#b0002) |
| [B0003 · 17–20](../../../../../tests/unit/session_memory_test.cpp#L17) | Callable definition: resource::MemoryUsage plus(resource::MemoryUsage left,const resource::MemoryUsage& right) | calls ; returns left · [reviewed contract](#b0003) |
| [B0004 · 21–23](../../../../../tests/unit/session_memory_test.cpp#L21) | Callable definition: resource::MemoryUsage difference(const resource::MemoryUsage& left,const resource::MemoryUsage& right) | calls ; returns {left.allocations-right.allocations,left.requested_bytes-right.requested_bytes,left.payload_bytes-r… · [reviewed contract](#b0004) |
| [B0005 · 24–31](../../../../../tests/unit/session_memory_test.cpp#L24) | Callable definition: void reconcile(const resource::MemoryAccount& account) | calls check_invariants, statistics, plus, check; guard check(purposes==state.current && lifetimes==state.current,"session account partitions do not reconc…; 2 loop sites · [reviewed contract](#b0005) |
| [B0006 · 32–36](../../../../../tests/unit/session_memory_test.cpp#L32) | Callable definition: void controller_only(const resource::MemoryAccount& account) | calls reconcile, statistics, check, resource::MemoryAccount::control_bytes; guard check(usage.allocations==1 && usage.requested_bytes==resource::MemoryAccount::control_bytes(), · [reviewed contract](#b0006) |
| [B0007 · 37–44](../../../../../tests/unit/session_memory_test.cpp#L37) | Callable definition: PhysicalPlan plan(bool indexed,bool boolean=false) | calls clear, planner::lower_tree, s04_runtime::options; returns planner::lower_tree(catalog,query,tree,indexed?s04_runtime::options():PhysicalOptions{}) · [reviewed contract](#b0007) |
| [B0008 · 45–50](../../../../../tests/unit/session_memory_test.cpp#L45) | Callable definition: Database database(std::size_t count=13) | calls resize, insert, std::string; returns db; growth insert, resize; 1 loop sites · [reviewed contract](#b0008) |
| [B0009 · 51–53](../../../../../tests/unit/session_memory_test.cpp#L51) | Callable definition: SessionOptions options(std::uint64_t cap=64*1024*1024) | calls ; returns value · [reviewed contract](#b0009) |
| [B0010 · 54–61](../../../../../tests/unit/session_memory_test.cpp#L54) | Callable definition: void same_rows(const SessionSnapshot& snapshot,const Relation& expected) | calls check, layout, same_token, insert; guard check(tuple.layout().same_token(snapshot.layout),"snapshot tuple lost its advertised layout token");; growth insert; 1 loop sites · [reviewed contract](#b0010) |
| [B0011 · 62–65](../../../../../tests/unit/session_memory_test.cpp#L62) | Callable definition: template&lt;class F&gt;void resource_denied(F&& action) | calls action, check, code, std::runtime_error; guard try{action();}catch(const Error& failure){check(failure.code()=="resource_limit","wrong snapshot su… · [reviewed contract](#b0011) |
| [B0012 · 66–69](../../../../../tests/unit/session_memory_test.cpp#L66) | Callable definition: template&lt;class F&gt;void account_denied(F&& action) | calls action, check, fault, std::runtime_error; guard try{action();}catch(const resource::MemoryFailure& failure){check(failure.fault()==resource::Memory… · [reviewed contract](#b0012) |
| [B0013 · 70–121](../../../../../tests/unit/session_memory_test.cpp#L70) | Callable definition: void ownership_and_bytes(bool indexed) | calls database, QuerySession::create_typed, plan, options; guard check(session-&gt;accounted_memory_statistics()-&gt;owner==account.statistics().owner,; growth emplace; 1 loop sites; source comment (unverified): // Preserve the measured growth schedule; a smaller row cap legitimately shrinks final capacity. · [reviewed contract](#b0013) |
| [B0014 · 122–134](../../../../../tests/unit/session_memory_test.cpp#L122) | Callable definition: void empty_and_boolean(bool indexed) | calls QuerySession::create_typed, plan, options, get_deleter; guard check(empty.rows.empty() && empty.rows.memory_usage()==resource::MemoryUsage{} && · [reviewed contract](#b0014) |
| [B0015 · 135–166](../../../../../tests/unit/session_memory_test.cpp#L135) | Callable definition: void retained_cap_and_move(bool indexed) | calls plan, database, QuerySession::create_typed, options; guard check(session-&gt;accounted_memory_statistics()-&gt;peak_requested_bytes==peak,"exact original session/sn… · [reviewed contract](#b0015) |
| [B0016 · 167–182](../../../../../tests/unit/session_memory_test.cpp#L167) | Callable definition: void snapshot_faults(bool indexed) | calls plan, database, QuerySession::create_typed, options; guard check(account.statistics().current==before && session-&gt;status().committed_sequence==0,; 1 loop sites · [reviewed contract](#b0016) |
| [B0017 · 183–193](../../../../../tests/unit/session_memory_test.cpp#L183) | Callable definition: void window_controls(bool indexed) | calls QuerySession::create_windowed, plan, options, get_deleter; guard check(account.statistics_for(session_owner).current.allocations==5, · [reviewed contract](#b0017) |
| [B0018 · 194–194](../../../../../tests/unit/session_memory_test.cpp#L194) | Closes surrounding scope/type. | source comment (unverified): // namespace · [reviewed contract](#b0018) |
| [B0019 · 195–203](../../../../../tests/unit/session_memory_test.cpp#L195) | Callable definition: int main() | calls ownership_and_bytes, empty_and_boolean, retained_cap_and_move, snapshot_faults; returns 1; 1 loop sites · [reviewed contract](#b0019) |

## B0001

[Lines 1–13](../../../../../tests/unit/session_memory_test.cpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L1-L13:sha256:27a6c53beb55c99ce810fd92d33530225a9b3bdb68c81dc3532f08ab5a6830d9
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Prepare session_memory_test.cpp: include "crown/api/error.hpp", "crown/runtime/session.hpp", "indexed_runtime_fixture.hpp", "index_allocation.hpp", &lt;iostream&gt;, &lt;optional&gt;, &lt;stdexcept&gt;; bind local aliases/name imports; declare constant fixture data. |
| inputs / outputs | Compiler-visible dependencies, names and the recorded declarations in; declarations available to the following fixture/CLI/example definitions out. The source span lists the exact member/global names, types and initial values; initializers run when the enclosing object/program/thread is initialized. |
| invariants | Declarations are scoped to this source/header and its selected ABI. Included code has its own effects; names and editable fixture values do not confer proof, admission or publication authority. |
| ownership | Aliases/includes do not create a query owner. Pointers/references/views are non-owning. Containers own their elements, which can themselves be borrowed pointers or numeric IDs. Only documented owning shared-control handles retain controls; IDs/slot-handle values do not independently keep an arena/runtime alive. |
| failure | Missing headers, ill-formed names/types, failed static assertions or active #error directives stop compilation. No runtime rejection/rollback mechanism is implemented by aliases or function prototypes. |
| cost | Preprocessing and type/constraint instantiation cost compilation. Alias/prototype syntax does not invoke the declared operation; any included definitions keep their own initialization effects. These constexpr data are fixed fixture constants; quota literals are grants, not reserved bytes or measured peaks. |
| Design | [tests/unit/session_memory_test.cpp](../../../../../tests/unit/session_memory_test.cpp), [docs/session_lifecycle.md](../../../../session_lifecycle.md), [docs/code_review.md](../../../../code_review.md) |

## B0002

[Lines 14–16](../../../../../tests/unit/session_memory_test.cpp#L14); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void check(bool value,std::string_view message) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Provide assertions for session snapshot/account helpers. |
| inputs / outputs | Checks a boolean; false copies the string_view message to std::string and throws runtime_error. |
| invariants | Message is borrowed during the call; successful checks do not build failure text. |
| ownership | No persistent or query-account state. |
| failure | False check throws; error-text allocation failure can propagate. |
| cost | One branch; failure-only string/exception work. |
| Design | [tests/unit/session_memory_test.cpp](../../../../../tests/unit/session_memory_test.cpp) |

## B0003

[Lines 17–20](../../../../../tests/unit/session_memory_test.cpp#L17); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
resource::MemoryUsage plus(resource::MemoryUsage left,const resource::MemoryUsage& right) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Add two resource::MemoryUsage triples. |
| inputs / outputs | Adds allocations, requested_bytes and payload_bytes componentwise and returns the new value. |
| invariants | No overflow checks; fixture totals are small. |
| ownership | Scalar values only; no account ownership. |
| failure | Unsigned overflow would wrap outside fixture assumptions. |
| cost | Three scalar additions. |
| Design | [tests/unit/session_memory_test.cpp](../../../../../tests/unit/session_memory_test.cpp), [include/crown/resource/memory.hpp](../../../../../include/crown/resource/memory.hpp) |

## B0004

[Lines 21–23](../../../../../tests/unit/session_memory_test.cpp#L21); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
resource::MemoryUsage difference(const resource::MemoryUsage& left,const resource::MemoryUsage& right) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Subtract one MemoryUsage triple from another. |
| inputs / outputs | Returns left minus right for allocations/requested_bytes/payload_bytes. |
| invariants | Caller must ensure left&gt;=right per field; no underflow guard. |
| ownership | Scalar values only. |
| failure | Underflow wraps unsigned fields; callers use before/after monotone allocations. |
| cost | Three subtractions. |
| Design | [tests/unit/session_memory_test.cpp](../../../../../tests/unit/session_memory_test.cpp), [include/crown/resource/memory.hpp](../../../../../include/crown/resource/memory.hpp) |

## B0005

[Lines 24–31](../../../../../tests/unit/session_memory_test.cpp#L24); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void reconcile(const resource::MemoryAccount& account) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Check complete session account partitioning and requested-byte limits. |
| inputs / outputs | Calls account.check_invariants, sums all by-purpose/by-lifetime MemoryUsage and checks both equal current; current and peak requested bytes must be &lt;= limit. |
| invariants | Whole account includes controller and framing. Requested bytes are not process RSS or allocator usable size. |
| ownership | Borrows existing MemoryAccount. |
| failure | Ledger/partition/cap mismatch throws. |
| cost | check_invariants traverses live blocks; then fixed-size arrays are summed. |
| Design | [tests/unit/session_memory_test.cpp](../../../../../tests/unit/session_memory_test.cpp), [include/crown/resource/memory.hpp](../../../../../include/crown/resource/memory.hpp), [src/resource/memory.cpp](../../../../../src/resource/memory.cpp), [docs/memory_accounts.md](../../../../memory_accounts.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0006

[Lines 32–36](../../../../../tests/unit/session_memory_test.cpp#L32); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void controller_only(const resource::MemoryAccount& account) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Verify session/snapshot data was released and only the controller remains. |
| inputs / outputs | Calls reconcile and checks current allocations=1 and requested_bytes=control_bytes(). |
| invariants | Requires all snapshots, contexts and session facades to have been released; passed account keeps controller alive. |
| ownership | Borrows final account handle; retains no data block. |
| failure | Any remaining account allocation fails assertion. |
| cost | Full account invariant scan plus purpose/lifetime reconciliation. |
| Design | [tests/unit/session_memory_test.cpp](../../../../../tests/unit/session_memory_test.cpp), [include/crown/resource/memory.hpp](../../../../../include/crown/resource/memory.hpp), [src/resource/memory.cpp](../../../../../src/resource/memory.cpp), [docs/memory_accounts.md](../../../../memory_accounts.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0007

[Lines 37–44](../../../../../tests/unit/session_memory_test.cpp#L37); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
PhysicalPlan plan(bool indexed,bool boolean=false) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Build the single-relation session plan for tuple or Boolean snapshots. |
| inputs / outputs | Defines R(x:int64,text:string), one native node; boolean=true clears head; indexed selects s04_runtime options. |
| invariants | Same relation/tree for both head variants; backend flag changes storage options only. |
| ownership | Returns PhysicalPlan from local catalog/query/tree. |
| failure | Lowering/allocation errors propagate. |
| cost | One fixed one-node plan lowering. |
| Design | [tests/unit/session_memory_test.cpp](../../../../../tests/unit/session_memory_test.cpp), [tests/support/indexed_runtime_fixture.hpp](../../../../../tests/support/indexed_runtime_fixture.hpp), [include/crown/planner/lower.hpp](../../../../../include/crown/planner/lower.hpp), [docs/session_lifecycle.md](../../../../session_lifecycle.md) |

## B0008

[Lines 45–50](../../../../../tests/unit/session_memory_test.cpp#L45); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Database database(std::size_t count=13) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Create a deterministic database with wide text payloads. |
| inputs / outputs | Creates one relation with count rows (default 13), int key i and 14-byte "snapshot\0bytes" prefix plus 8192 chars cycling a..t. |
| invariants | Explicit string length preserves embedded NUL; fixture Database uses ordinary containers, not SessionRows. |
| ownership | Returns normal allocator-owned Database/Relation/Rows. |
| failure | String/container allocation failure propagates. |
| cost | O(count×8192) payload construction plus table insert work outside the query-account measurement. |
| Design | [tests/unit/session_memory_test.cpp](../../../../../tests/unit/session_memory_test.cpp) |

## B0009

[Lines 51–53](../../../../../tests/unit/session_memory_test.cpp#L51); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
SessionOptions options(std::uint64_t cap=64*1024*1024) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Set the original query-account byte limit for session constructors. |
| inputs / outputs | Returns SessionOptions with delta.physical.support.memory_limit_bytes=cap, default 64 MiB. |
| invariants | Does not alter SnapshotLimits rows/bytes; they retain independent defaults. |
| ownership | Value object only. |
| failure | Runtime constructor may reject incompatible option values. |
| cost | Scalar assignments. |
| Design | [tests/unit/session_memory_test.cpp](../../../../../tests/unit/session_memory_test.cpp), [include/crown/runtime/session.hpp](../../../../../include/crown/runtime/session.hpp), [include/crown/runtime/delta.hpp](../../../../../include/crown/runtime/delta.hpp), [docs/session_lifecycle.md](../../../../session_lifecycle.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0010

[Lines 54–61](../../../../../tests/unit/session_memory_test.cpp#L54); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void same_rows(const SessionSnapshot& snapshot,const Relation& expected) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Compare exported SessionSnapshot tuples with independent ordinary rows. |
| inputs / outputs | Copies snapshot row values to an ordinary Relation; checks each tuple layout token matches snapshot.layout, then compares relations. |
| invariants | This output Relation is test-side ordinary storage, distinct from SessionRows and its measured account bytes. |
| ownership | Borrows snapshot and expected Relation; owns local Relation. |
| failure | Layout/value mismatch throws; export/allocation failures propagate. |
| cost | O(rows and widths) traversal/copy using test allocator. |
| Design | [tests/unit/session_memory_test.cpp](../../../../../tests/unit/session_memory_test.cpp), [include/crown/runtime/session.hpp](../../../../../include/crown/runtime/session.hpp), [include/crown/storage/layout.hpp](../../../../../include/crown/storage/layout.hpp), [docs/session_lifecycle.md](../../../../session_lifecycle.md), [docs/memory_accounts.md](../../../../memory_accounts.md) |

## B0011

[Lines 62–65](../../../../../tests/unit/session_memory_test.cpp#L62); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
template<class F>void resource_denied(F&& action) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Require a SessionSnapshot sublimit ResourceLimit. |
| inputs / outputs | Invokes named action as an lvalue; accepts only Error with code resource_limit. |
| invariants | Does not accept MemoryFailure::limit, which is the original query-account cap. |
| ownership | Borrows callable synchronously. |
| failure | Wrong Error or success throws; unrelated exceptions propagate. |
| cost | One snapshot attempt plus exception check. |
| Design | [tests/unit/session_memory_test.cpp](../../../../../tests/unit/session_memory_test.cpp), [include/crown/runtime/session.hpp](../../../../../include/crown/runtime/session.hpp), [src/runtime/session.cpp](../../../../../src/runtime/session.cpp), [docs/session_lifecycle.md](../../../../session_lifecycle.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0012

[Lines 66–69](../../../../../tests/unit/session_memory_test.cpp#L66); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
template<class F>void account_denied(F&& action) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Require rejection by the original session query-account byte cap. |
| inputs / outputs | Invokes named action as an lvalue; accepts only MemoryFailure with MemoryFault::limit. |
| invariants | Does not classify snapshot row/byte ResourceLimit as a query-cap denial. |
| ownership | Borrows callable and existing owner/account. |
| failure | Wrong MemoryFailure or success throws; unrelated exceptions propagate. |
| cost | One snapshot attempt plus catch/check. |
| Design | [tests/unit/session_memory_test.cpp](../../../../../tests/unit/session_memory_test.cpp), [include/crown/resource/memory.hpp](../../../../../include/crown/resource/memory.hpp), [include/crown/runtime/session.hpp](../../../../../include/crown/runtime/session.hpp), [src/runtime/session.cpp](../../../../../src/runtime/session.cpp), [docs/session_lifecycle.md](../../../../session_lifecycle.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0013

[Lines 70–121](../../../../../tests/unit/session_memory_test.cpp#L70); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void ownership_and_bytes(bool indexed) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Measure snapshot collection plus tuple requests and retain account-backed handles past drop. |
| inputs / outputs | Creates a typed 13-row session; checks facade account owner and 3 session control allocations (2 support_metadata, 1 immutable_metadata); snapshots and sums SessionRows collection and tuple MemoryUsage, tests copy sharing, exact/one-byte-under snapshot byte sublimits, captures statistics context, drops session, then releases retained handles. |
| invariants | Account growth equals the measured SessionRows collection/control requests plus native tuple requests. Collection uses two charged allocations in this fixture. The exact SnapshotLimits row ceiling is the measured rows.capacity() value (not the input row count of 13), paired with measured accounted bytes; one-byte-under returns resource_limit without changing current account bytes or sequence. Facade and capture-plan owner IDs match the original account. The no-new copy assertion covers this typed fixture; arbitrary progress-map copies can allocate. |
| ownership | SessionRows shared Data and AccountedTuple values remain charged to the original query account; SessionRunContext and SessionStatisticsContext may outlive session. All are released before controller_only. |
| failure | Unexpected limit class, owner, row bytes or copy behavior fails; scoped shim covers replacement-new only. |
| cost | One session, one measured snapshot, one exact retry, one one-byte-under attempt and one capture context; statistics_for/check_invariants walk live blocks. |
| Design | [tests/unit/session_memory_test.cpp](../../../../../tests/unit/session_memory_test.cpp), [tests/support/indexed_runtime_fixture.hpp](../../../../../tests/support/indexed_runtime_fixture.hpp), [tests/support/index_allocation.hpp](../../../../../tests/support/index_allocation.hpp), [include/crown/runtime/session.hpp](../../../../../include/crown/runtime/session.hpp), [src/runtime/session.cpp](../../../../../src/runtime/session.cpp), [include/crown/runtime/delta.hpp](../../../../../include/crown/runtime/delta.hpp), [src/runtime/delta.cpp](../../../../../src/runtime/delta.cpp), [include/crown/resource/memory.hpp](../../../../../include/crown/resource/memory.hpp), [src/resource/memory.cpp](../../../../../src/resource/memory.cpp), [include/crown/storage/layout.hpp](../../../../../include/crown/storage/layout.hpp), [docs/session_lifecycle.md](../../../../session_lifecycle.md), [docs/memory_accounts.md](../../../../memory_accounts.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0014

[Lines 122–134](../../../../../tests/unit/session_memory_test.cpp#L122); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void empty_and_boolean(bool indexed) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Check empty and one-row nullary Boolean snapshots. |
| inputs / outputs | Empty session snapshots with rows=0 and bytes=0; then Boolean plan with one input row snapshots one empty tuple. |
| invariants | Empty collection has zero memory_usage/accounted bytes and no account growth. Nullary result still has a tuple and collection/control requests. |
| ownership | Both snapshots use their session’s original account. |
| failure | Unexpected growth or shape fails assertion. |
| cost | Two session constructions and two small snapshots. |
| Design | [tests/unit/session_memory_test.cpp](../../../../../tests/unit/session_memory_test.cpp), [tests/support/indexed_runtime_fixture.hpp](../../../../../tests/support/indexed_runtime_fixture.hpp), [include/crown/runtime/session.hpp](../../../../../include/crown/runtime/session.hpp), [src/runtime/session.cpp](../../../../../src/runtime/session.cpp), [include/crown/resource/memory.hpp](../../../../../include/crown/resource/memory.hpp), [src/resource/memory.cpp](../../../../../src/resource/memory.cpp), [docs/session_lifecycle.md](../../../../session_lifecycle.md), [docs/memory_accounts.md](../../../../memory_accounts.md) |

## B0015

[Lines 135–166](../../../../../tests/unit/session_memory_test.cpp#L135); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void retained_cap_and_move(bool indexed) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Find retained snapshot byte peak and test cross-account SessionRows assignment. |
| inputs / outputs | Discovers account peak while retaining two snapshots; replays at exact cap; then peak-1 account cap admits first snapshot but rejects second. Assigns another session’s SessionRows from first.rows and retries after dropping aliases. |
| invariants | Exact account cap reproduces peak. Under-cap failure preserves current account bytes/sequence. Assignment shares the same row-buffer pointer, changes attributed account owner to first account and makes no covered new call; this is query-account assignment, not cloning. |
| ownership | Each session has independent account; SessionRows copy/assignment shares immutable Data and its account handle. |
| failure | Expected second-snapshot denial is MemoryFault::limit; failed retry/account-owner checks throw. |
| cost | Per backend: discovery with two snapshots, exact-cap with two, one-under with held first and denied second, plus one foreign-account session and final retry. |
| Design | [tests/unit/session_memory_test.cpp](../../../../../tests/unit/session_memory_test.cpp), [tests/support/indexed_runtime_fixture.hpp](../../../../../tests/support/indexed_runtime_fixture.hpp), [tests/support/index_allocation.hpp](../../../../../tests/support/index_allocation.hpp), [include/crown/runtime/session.hpp](../../../../../include/crown/runtime/session.hpp), [src/runtime/session.cpp](../../../../../src/runtime/session.cpp), [include/crown/resource/memory.hpp](../../../../../include/crown/resource/memory.hpp), [src/resource/memory.cpp](../../../../../src/resource/memory.cpp), [docs/session_lifecycle.md](../../../../session_lifecycle.md), [docs/memory_accounts.md](../../../../memory_accounts.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0016

[Lines 167–182](../../../../../tests/unit/session_memory_test.cpp#L167); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void snapshot_faults(bool indexed) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Fault-inject SessionSnapshot creation and retry at increasing replacement-new positions. |
| inputs / outputs | For points 0..511 creates fresh typed session/account, attempts five-row snapshot under s04_alloc, catches bad_alloc, checks current account bytes and committed sequence, retries failed points and stops at first success. |
| invariants | Requires &gt;=10 failure points and one nonthrowing point before 512. It does not assert C++ shim calls equal the selected point; account reconciliation and controller-only follow each iteration. |
| ownership | Owner/snapshot local to each point; retry result is released before session destruction. |
| failure | Only bad_alloc is treated as injected; other errors propagate; loop bounds are test guards. |
| cost | Data-dependent setups/snapshot attempts up to 512, retry per failure and full account scan per point. Shim counts covered operator-new attempts only. |
| Design | [tests/unit/session_memory_test.cpp](../../../../../tests/unit/session_memory_test.cpp), [tests/support/indexed_runtime_fixture.hpp](../../../../../tests/support/indexed_runtime_fixture.hpp), [tests/support/index_allocation.hpp](../../../../../tests/support/index_allocation.hpp), [include/crown/runtime/session.hpp](../../../../../include/crown/runtime/session.hpp), [src/runtime/session.cpp](../../../../../src/runtime/session.cpp), [include/crown/resource/memory.hpp](../../../../../include/crown/resource/memory.hpp), [src/resource/memory.cpp](../../../../../src/resource/memory.cpp), [docs/session_lifecycle.md](../../../../session_lifecycle.md), [docs/memory_accounts.md](../../../../memory_accounts.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0017

[Lines 183–193](../../../../../tests/unit/session_memory_test.cpp#L183); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void window_controls(bool indexed) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Check account attribution and release for the configured windowed session. |
| inputs / outputs | Creates a windowed session managing table 0 and asserts five current allocations under session owner attribution; destroys it in zero-new scope and checks controller_only. |
| invariants | Five allocations are specific to this constructor/options path, not a general count for all sessions. |
| ownership | Facade/account share original query controller; account handle outlives session. |
| failure | Unexpected five-allocation attribution or account state after destruction fails the assertions. The no-allocation scope arms fail-after on the first covered new call during reset, but this helper does not inspect s04_alloc::calls or triggered and so does not assert a measured zero-call result. |
| cost | One window session setup and final full account reconciliation. |
| Design | [tests/unit/session_memory_test.cpp](../../../../../tests/unit/session_memory_test.cpp), [tests/support/indexed_runtime_fixture.hpp](../../../../../tests/support/indexed_runtime_fixture.hpp), [tests/support/index_allocation.hpp](../../../../../tests/support/index_allocation.hpp), [include/crown/runtime/session.hpp](../../../../../include/crown/runtime/session.hpp), [src/runtime/session.cpp](../../../../../src/runtime/session.cpp), [include/crown/resource/memory.hpp](../../../../../include/crown/resource/memory.hpp), [src/resource/memory.cpp](../../../../../src/resource/memory.cpp), [docs/session_lifecycle.md](../../../../session_lifecycle.md), [docs/memory_accounts.md](../../../../memory_accounts.md) |

## B0018

[Lines 194–194](../../../../../tests/unit/session_memory_test.cpp#L194); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L194-L194:sha256:533f16bca7d58f44b3103b92e3485d22cfbb34bbad5ea3f3fa3b5a9dcb24ec89
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Close the recorded declaration scopes in session_memory_test.cpp: namespace (anonymous). |
| inputs / outputs | Preceding namespace, type or initializer declarations in; completed lexical boundary out. |
| invariants | Brace-opening context is recorded in root-scope-context-v1.json. These are declaration/initializer boundaries, not an independent update, validation or recovery operation. |
| ownership | Enclosing objects and borrowed fields keep their declared ownership. This punctuation creates no new owner. |
| failure | Malformed scope syntax is a compile error. Any initializer/constructor failure belongs to the enclosing object declaration. |
| cost | No separate loop, guard or engine call is introduced by the delimiter; enclosing initialization and object lifetime still have their actual costs. |
| Design | [tests/unit/session_memory_test.cpp](../../../../../tests/unit/session_memory_test.cpp), [docs/session_lifecycle.md](../../../../session_lifecycle.md), [docs/code_review.md](../../../../code_review.md) |

## B0019

[Lines 195–203](../../../../../tests/unit/session_memory_test.cpp#L195); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
int main() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Run the session snapshot ownership, cap and fault scenarios on both backend plans. |
| inputs / outputs | For each indexed=false/true calls ownership_and_bytes, empty_and_boolean, retained_cap_and_move, snapshot_faults and window_controls. |
| invariants | Completion message is not execution evidence; fault counts/peak are dynamic. |
| ownership | No runtime crosses helper boundary; only explicitly retained handles survive within each helper. |
| failure | Outer std::exception catch prints and returns status 1. |
| cost | Ten helper calls total (five/backend); snapshot loops repeat setup, account scans and row export work. |
| Design | [tests/unit/session_memory_test.cpp](../../../../../tests/unit/session_memory_test.cpp), [tests/support/indexed_runtime_fixture.hpp](../../../../../tests/support/indexed_runtime_fixture.hpp), [tests/support/index_allocation.hpp](../../../../../tests/support/index_allocation.hpp), [include/crown/runtime/session.hpp](../../../../../include/crown/runtime/session.hpp), [src/runtime/session.cpp](../../../../../src/runtime/session.cpp), [include/crown/runtime/delta.hpp](../../../../../include/crown/runtime/delta.hpp), [src/runtime/delta.cpp](../../../../../src/runtime/delta.cpp), [include/crown/resource/memory.hpp](../../../../../include/crown/resource/memory.hpp), [src/resource/memory.cpp](../../../../../src/resource/memory.cpp), [docs/session_lifecycle.md](../../../../session_lifecycle.md), [docs/memory_accounts.md](../../../../memory_accounts.md), [docs/query_memory.md](../../../../query_memory.md) |
