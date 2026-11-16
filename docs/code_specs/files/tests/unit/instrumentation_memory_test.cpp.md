# `tests/unit/instrumentation_memory_test.cpp` — block usage map

[Source](../../../../../tests/unit/instrumentation_memory_test.cpp) · [Source index](../../../README.md) · [Subsystem contracts](../../../subsystem_contracts.md) · [Reviewed primitives](../../../primitives.md)

Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection.

Snapshot SHA-256: `158df8b95d2912426c4adeae41ed88ee4fdd9780cb51dda9ee5580901c4fe559`. 212 lines partitioned into 15 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [tests](../../../subsystem_contracts.md#tests). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/code_review.md](../../../../code_review.md), [docs/reference_fuzz.md](../../../../reference_fuzz.md), [docs/task_ledger.md](../../../../task_ledger.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–15](../../../../../tests/unit/instrumentation_memory_test.cpp#L1) | Imports dependencies; declares namespace scope; declares aliases; declares values/defaults or compile-time conditions. |  · [reviewed contract](#b0001) |
| [B0002 · 16–16](../../../../../tests/unit/instrumentation_memory_test.cpp#L16) | Callable definition: void check(bool ok,std::string_view message) | calls std::runtime_error, std::string; guard void check(bool ok,std::string_view message) {if(!ok)throw std::runtime_error(std::string(message))… · [reviewed contract](#b0002) |
| [B0003 · 17–20](../../../../../tests/unit/instrumentation_memory_test.cpp#L17) | Callable definition: void controller_only(const resource::MemoryAccount& account) | calls check_invariants, statistics, check, resource::MemoryAccount::control_bytes; guard check(state.allocations==1 && state.requested_bytes==resource::MemoryAccount::control_bytes(),"inst… · [reviewed contract](#b0003) |
| [B0004 · 21–31](../../../../../tests/unit/instrumentation_memory_test.cpp#L21) | Callable definition: PhysicalPlan plan(bool indexed) | calls std::to_string, push_back, planner::lower_tree, s04_runtime::options; returns planner::lower_tree(catalog,query,tree,indexed?s04_runtime::options():PhysicalOptions{}); growth push_back; 1 loop sites · [reviewed contract](#b0004) |
| [B0005 · 32–35](../../../../../tests/unit/instrumentation_memory_test.cpp#L32) | Callable definition: DeltaOptions options(std::uint64_t cap=64*1024*1024,ObservationMode mode=ObservationMode::counters) | calls ; returns result · [reviewed contract](#b0005) |
| [B0006 · 36–36](../../../../../tests/unit/instrumentation_memory_test.cpp#L36) | Callable definition: ws::Options enabled(std::uint64_t period=1) | calls ; returns value · [reviewed contract](#b0006) |
| [B0007 · 37–41](../../../../../tests/unit/instrumentation_memory_test.cpp#L37) | Callable definition: void accept(DeltaRuntime& runtime,std::uint64_t sequence) | calls begin, drain, none, commit; growth insert · [reviewed contract](#b0007) |
| [B0008 · 42–53](../../../../../tests/unit/instrumentation_memory_test.cpp#L42) | Callable definition: bool same(const ws::Snapshot& a,const ws::Snapshot& b) | calls options, modes, previous_modes, stamp; returns a.options()==b.options() && a.modes()==b.modes() && a.previous_modes()==b.previous_modes() && · [reviewed contract](#b0008) |
| [B0009 · 54–91](../../../../../tests/unit/instrumentation_memory_test.cpp#L54) | Callable definition: void observer_requests_limits_and_failures() | calls resource::MemoryAccount::create, statistics, crown::runtime::detail::ObservationState::create, statistics_for; guard check(calls==after.successful_allocations-before.successful_allocations && owned.requested_bytes==a…; 4 loop sites · [reviewed contract](#b0009) |
| [B0010 · 92–122](../../../../../tests/unit/instrumentation_memory_test.cpp#L92) | Callable definition: void actual_runtime_requests_and_lifetimes(bool indexed) | calls runtime, plan, options, account; guard check(account.statistics_for(observation_owner).current.allocations==2,"actual query observation ow…; growth emplace · [reviewed contract](#b0010) |
| [B0011 · 123–163](../../../../../tests/unit/instrumentation_memory_test.cpp#L123) | Callable definition: void cap_and_persistent_failures(bool indexed) | calls runtime, plan, options, configure_workload_statistics; guard peak=runtime.plan().account().statistics().peak_requested_bytes;check(peak&gt;before,"instrumentation …; growth emplace; 3 loop sites; source comment (unverified): // A second capture has the same byte frontier as with_pending. At the · [reviewed contract](#b0011) |
| [B0012 · 164–170](../../../../../tests/unit/instrumentation_memory_test.cpp#L164) | Callable definition: QuerySession::Owner pending_session(bool indexed,std::uint64_t cap=64*1024*1024) | calls options, QuerySession::create_typed, plan, configure_workload_statistics; guard check(session-&gt;enqueue(offered)==io::Admission::accepted,"pending workload session input was refuse…; returns session; growth insert · [reviewed contract](#b0012) |
| [B0013 · 171–206](../../../../../tests/unit/instrumentation_memory_test.cpp#L171) | Callable definition: void pending_session_capture(bool indexed) | calls pending_session, get_deleter, account, statistics; guard check(held && held-&gt;pending() && calls==8 && calls==account.statistics().successful_allocations-bef…; 2 loop sites · [reviewed contract](#b0013) |
| [B0014 · 207–207](../../../../../tests/unit/instrumentation_memory_test.cpp#L207) | Closes surrounding scope/type. | source comment (unverified): // namespace · [reviewed contract](#b0014) |
| [B0015 · 208–212](../../../../../tests/unit/instrumentation_memory_test.cpp#L208) | Callable definition: int main() | calls observer_requests_limits_and_failures, actual_runtime_requests_and_lifetimes, cap_and_persistent_failures, pending_session_capture; returns 1; 1 loop sites · [reviewed contract](#b0015) |

## B0001

[Lines 1–15](../../../../../tests/unit/instrumentation_memory_test.cpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L1-L15:sha256:76011137bfe19b4b3d2c079044ba08cbeb14dce5c83435d8826ef65dba9fb201
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Prepare instrumentation_memory_test.cpp: include "crown/runtime/session.hpp", "indexed_runtime_fixture.hpp", "index_allocation.hpp", &lt;algorithm&gt;, &lt;iostream&gt;, &lt;optional&gt;, &lt;stdexcept&gt;; bind local aliases/name imports; declare constant fixture data. |
| inputs / outputs | Compiler-visible dependencies, names and the recorded declarations in; declarations available to the following fixture/CLI/example definitions out. The source span lists the exact member/global names, types and initial values; initializers run when the enclosing object/program/thread is initialized. |
| invariants | Declarations are scoped to this source/header and its selected ABI. Included code has its own effects; names and editable fixture values do not confer proof, admission or publication authority. |
| ownership | Aliases/includes do not create a query owner. Pointers/references/views are non-owning. Containers own their elements, which can themselves be borrowed pointers or numeric IDs. Only documented owning shared-control handles retain controls; IDs/slot-handle values do not independently keep an arena/runtime alive. |
| failure | Missing headers, ill-formed names/types, failed static assertions or active #error directives stop compilation. No runtime rejection/rollback mechanism is implemented by aliases or function prototypes. |
| cost | Preprocessing and type/constraint instantiation cost compilation. Alias/prototype syntax does not invoke the declared operation; any included definitions keep their own initialization effects. These constexpr data are fixed fixture constants; quota literals are grants, not reserved bytes or measured peaks. |
| Design | [tests/unit/instrumentation_memory_test.cpp](../../../../../tests/unit/instrumentation_memory_test.cpp), [docs/query_memory.md](../../../../query_memory.md), [docs/code_review.md](../../../../code_review.md) |

## B0002

[Lines 16–16](../../../../../tests/unit/instrumentation_memory_test.cpp#L16); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void check(bool ok,std::string_view message) {if(!ok)throw std::runtime_error(std::string(message));}
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Provide a conditional-message assertion for instrumentation fixtures. |
| inputs / outputs | Input: bool and string_view. Output: normal return when true. |
| invariants | Converts the borrowed message into std::string only in the false branch before throwing runtime_error. |
| ownership | No message is retained on success. |
| failure | False throws runtime_error; ordinary string construction is conditional. |
| cost | One predicate branch; no allocation assertion is implied. |
| Design | [tests/unit/instrumentation_memory_test.cpp](../../../../../tests/unit/instrumentation_memory_test.cpp) |

## B0003

[Lines 17–20](../../../../../tests/unit/instrumentation_memory_test.cpp#L17); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void controller_only(const resource::MemoryAccount& account) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Assert final release leaves only an account controller. |
| inputs / outputs | Input: MemoryAccount reference; output: none. |
| invariants | Runs account invariant check and requires current allocation count 1 and requested bytes equal control_bytes(). |
| ownership | Borrowed handle keeps controller alive; the helper retains no owner. |
| failure | Mismatch throws runtime_error; it says nothing about allocations outside the account. |
| cost | Fixed counter reads and comparisons. |
| Design | [tests/unit/instrumentation_memory_test.cpp](../../../../../tests/unit/instrumentation_memory_test.cpp), [include/crown/resource/memory.hpp](../../../../../include/crown/resource/memory.hpp), [docs/query_memory.md](../../../../query_memory.md) |

## B0004

[Lines 21–31](../../../../../tests/unit/instrumentation_memory_test.cpp#L21); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
PhysicalPlan plan(bool indexed) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Lower the 12-native-node fixture for the selected reference or indexed backend. |
| inputs / outputs | Input: backend selector. Output: PhysicalPlan with 12 one-column tables and 12 native TreeNodes; node 0 is the root and has child edges to node ids 1..11. |
| invariants | Each node i binds variable x and occurrence i. Every TreeNode, including node 0, is NodeKind::native; node 0 is the root with children 1..11. Indexed mode supplies the test fixture index/work options. This lowers setup and does not execute a runtime query. |
| ownership | Catalog/query/tree are ordinary local values; returned plan owns the lowered metadata as defined by the plan API. |
| failure | Invalid lowering or ordinary allocation failure propagates. |
| cost | Constructs 12 table/name/atom/node entries and lowers once; no runtime-account metric is measured here. |
| Design | [tests/unit/instrumentation_memory_test.cpp](../../../../../tests/unit/instrumentation_memory_test.cpp), [tests/support/indexed_runtime_fixture.hpp](../../../../../tests/support/indexed_runtime_fixture.hpp), [include/crown/planner/lower.hpp](../../../../../include/crown/planner/lower.hpp) |

## B0005

[Lines 32–35](../../../../../tests/unit/instrumentation_memory_test.cpp#L32); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
DeltaOptions options(std::uint64_t cap=64*1024*1024,ObservationMode mode=ObservationMode::counters) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Build DeltaRuntime options and configure physical observation storage. |
| inputs / outputs | Inputs: support cap (default 64 MiB) and observation mode (default counters). Output: DeltaOptions. |
| invariants | Sets physical support byte limit, disables support transition capture, and configures observation with trace capacity 8,192, period 1, offset 0, non-clock mode. |
| ownership | Other DeltaOptions retain defaults; no runtime/account is created by this value helper. |
| failure | Invalid observation/options are rejected by the later runtime factory. |
| cost | Fixed options construction and assignments. |
| Design | [tests/unit/instrumentation_memory_test.cpp](../../../../../tests/unit/instrumentation_memory_test.cpp), [include/crown/runtime/delta.hpp](../../../../../include/crown/runtime/delta.hpp), [include/crown/runtime/observation.hpp](../../../../../include/crown/runtime/observation.hpp) |

## B0006

[Lines 36–36](../../../../../tests/unit/instrumentation_memory_test.cpp#L36); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
ws::Options enabled(std::uint64_t period=1) {ws::Options value;value.mode=ws::Mode::counters;value.period=period;return value;}
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Produce enabled workload-counter options for a selected sampling period. |
| inputs / outputs | Input: period, default 1. Output: workload::Options in counters mode. |
| invariants | Leaves other options at defaults, including cell cap and offset; caller must use a valid positive period/offset relation. |
| ownership | Returns a value object; not installed until configure_workload_statistics is called. |
| failure | This helper does not validate period; State::configure may throw invalid_argument later. |
| cost | Fixed options initialization. |
| Design | [tests/unit/instrumentation_memory_test.cpp](../../../../../tests/unit/instrumentation_memory_test.cpp), [include/crown/runtime/workload_statistics.hpp](../../../../../include/crown/runtime/workload_statistics.hpp), [src/runtime/workload_statistics.cpp](../../../../../src/runtime/workload_statistics.cpp) |

## B0007

[Lines 37–41](../../../../../tests/unit/instrumentation_memory_test.cpp#L37); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void accept(DeltaRuntime& runtime,std::uint64_t sequence) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Commit and discard one minimal physical input epoch in a DeltaRuntime. |
| inputs / outputs | Input: runtime and sequence; inserts that sequence as an int64 into source table 0. |
| invariants | Uses begin and drain, then runs commit and discard in Scope(0). This block reads neither s04_alloc::calls nor triggered, so it does not explicitly assert a zero intercepted-request count. |
| ownership | Input row is constructed as ordinary caller input; pending token owns private work until commit/discard. |
| failure | Queue/sequence/runtime errors propagate and fail the fixture. |
| cost | One insertion epoch plus its usual drain/commit work; the assertion covers only operator-new calls in the commit/discard scope. |
| Design | [tests/unit/instrumentation_memory_test.cpp](../../../../../tests/unit/instrumentation_memory_test.cpp), [include/crown/runtime/delta.hpp](../../../../../include/crown/runtime/delta.hpp), [tests/support/index_allocation.hpp](../../../../../tests/support/index_allocation.hpp) |

## B0008

[Lines 42–53](../../../../../tests/unit/instrumentation_memory_test.cpp#L42); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
bool same(const ws::Snapshot& a,const ws::Snapshot& b) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Compare the selected observable portions of two immutable workload snapshots. |
| inputs / outputs | Inputs: two Snapshot handles. Output: bool. |
| invariants | Compares options/modes, selected stamp and pending/history flags, selected metadata, and equality of descriptors/current/previous cells. It deliberately omits some stamp and metadata members, so true means this compared subset matches. |
| ownership | Snapshot copies share their immutable Data; spans/references are borrowed while a handle remains alive. |
| failure | Unequal compared fields return false; the test assumes matching descriptor/cell lengths. |
| cost | Linear in compared descriptor and cell arrays plus fixed metadata checks. |
| Design | [tests/unit/instrumentation_memory_test.cpp](../../../../../tests/unit/instrumentation_memory_test.cpp), [include/crown/runtime/workload_statistics.hpp](../../../../../include/crown/runtime/workload_statistics.hpp) |

## B0009

[Lines 54–91](../../../../../tests/unit/instrumentation_memory_test.cpp#L54); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void observer_requests_limits_and_failures() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Measure observation allocations, trace capacity, exact/under caps, and constructor fault cleanup. |
| inputs / outputs | No inputs. Exercises off/counters/timed/trace on fresh accounts, records owner requests, generates 9,000 trace events against capacity 8,192, and probes exact/one-under trace caps plus persistent-new fault positions. |
| invariants | For each mode, scoped global-new call delta equals account successful-allocation delta and observation-owner requested bytes equal account current delta; owner blocks are 0 off, 1 counters/timed, 2 trace. Trace records stop at 8,192 and mark truncated. Difference between trace and counter requested bytes equals the allocator’s real capacity request. Cap boundary compares measured construction peak and peak-1. Constructor sweep expects exactly 2 bad_alloc points. |
| ownership | Observation state and trace array are account-funded under observation owner id 0; report/snapshot values are local and state reset precedes controller-only check. The later capacity-16 control is attempted on each same cap account and reset; no allocation-count assertion applies to it. |
| failure | Only expected MemoryFailure(limit) is accepted for one-under; fault sweep catches bad_alloc. Diagnostics/assertions may allocate outside any accounting check. |
| cost | Event loop is 9,000 calls; allocation metrics count admitted requests/bytes, while the injected sweep counts operator-new attempts. Owner statistics_for checks scan outstanding allocations; no CPU/RSS or general mode cost is measured. |
| Design | [tests/unit/instrumentation_memory_test.cpp](../../../../../tests/unit/instrumentation_memory_test.cpp), [include/crown/runtime/observation.hpp](../../../../../include/crown/runtime/observation.hpp), [src/runtime/observation.cpp](../../../../../src/runtime/observation.cpp), [include/crown/resource/memory.hpp](../../../../../include/crown/resource/memory.hpp), [tests/support/index_allocation.hpp](../../../../../tests/support/index_allocation.hpp) |

## B0010

[Lines 92–122](../../../../../tests/unit/instrumentation_memory_test.cpp#L92); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void actual_runtime_requests_and_lifetimes(bool indexed) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Check workload-collector and immutable snapshot funding/lifetime on each Delta backend. |
| inputs / outputs | Input: backend selector. Configures counters, commits seq1, captures two snapshots, commits seq2, disables/reset collection, then closes runtime. |
| invariants | Configuration scope requires global-new calls equal account successful-allocation delta and workload owner 1 to hold 5 blocks. Each runtime snapshot capture has exactly 4 calls; the two committed captures both have pending=false and leave 8 capture-owner allocations. Selected retained-payload bytes equal workload owner payload bytes. Held first snapshot remains at committed count 1 after seq2; reset/off releases workload owner blocks. After runtime close handles retain values/account, and final release leaves only controller. |
| ownership | Runtime, collectors, and capture arrays use original plan account with distinct workload owner id 1 and capture owner id 1. Snapshot handles share immutable payload; they do not deep-copy merely when copied as handles. |
| failure | Any unfunded request, changed held data, wrong attribution/count, or retained capacity fails. Calls are scoped around configuration/capture, not every setup or assertion. |
| cost | Plan has 12 inputs. Workload configuration/capture arrays are charged account requests; retained_payload_bytes is collector payload metric, not total account bytes, CPU, or RSS. statistics_for attribution reads scan the outstanding-allocation list. |
| Design | [tests/unit/instrumentation_memory_test.cpp](../../../../../tests/unit/instrumentation_memory_test.cpp), [include/crown/runtime/workload_statistics.hpp](../../../../../include/crown/runtime/workload_statistics.hpp), [src/runtime/workload_statistics.cpp](../../../../../src/runtime/workload_statistics.cpp), [src/runtime/physical.cpp](../../../../../src/runtime/physical.cpp), [src/runtime/session.cpp](../../../../../src/runtime/session.cpp), [tests/support/index_allocation.hpp](../../../../../tests/support/index_allocation.hpp), [docs/query_memory.md](../../../../query_memory.md) |

## B0011

[Lines 123–163](../../../../../tests/unit/instrumentation_memory_test.cpp#L123); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void cap_and_persistent_failures(bool indexed) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Measure exact/one-under and persistent failures for workload reconfiguration and snapshot recapture. |
| inputs / outputs | Input: backend selector. Two operations: configure period 3 while retaining an old snapshot, or capture another snapshot while old capture is held. Measures each peak, then sweeps persistent bad_alloc positions until success. |
| invariants | One-under must preserve sequence 1 and held data/options; account current usage remains baseline. For reconfigure path it additionally compares a fresh snapshot to held; for copy path it checks old capture and documented state only at byte-cap boundary. Persistent sweeps require unchanged state/current bytes at every failure, retry, then exact failure counts 6 for reconfigure and 4 for capture. |
| ownership | Old snapshot intentionally pins account-owned capture arrays during peak and retry. Candidate copy/reconfiguration is tentative until operation succeeds. |
| failure | Byte denial accepts only MemoryFailure(limit); injected sweep catches bad_alloc and stops on first success. Exact counts are fixture-specific assertions, not a baseline calibration pass. |
| cost | For each backend × two operation types: one measured peak, exact/under cases, and up to 128 fault positions until success. Peaks are requested account bytes with retained snapshot overlap, not process heap/RSS or CPU. |
| Design | [tests/unit/instrumentation_memory_test.cpp](../../../../../tests/unit/instrumentation_memory_test.cpp), [include/crown/runtime/workload_statistics.hpp](../../../../../include/crown/runtime/workload_statistics.hpp), [src/runtime/workload_statistics.cpp](../../../../../src/runtime/workload_statistics.cpp), [src/runtime/physical.cpp](../../../../../src/runtime/physical.cpp), [tests/support/index_allocation.hpp](../../../../../tests/support/index_allocation.hpp) |

## B0012

[Lines 164–170](../../../../../tests/unit/instrumentation_memory_test.cpp#L164); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
QuerySession::Owner pending_session(bool indexed,std::uint64_t cap=64*1024*1024) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Create a session with one private pending input and workload counters enabled. |
| inputs / outputs | Inputs: backend selector and account cap. Output: QuerySession::Owner after configuration, event enqueue, start, and begin_next. |
| invariants | Requires one event be admitted and one pending operation begin; committed sequence remains before the in-flight event. Returns named session owner, eligible for implicit move under the project C++23 mode. |
| ownership | Owner/deleter retains original runtime account and owns session; offered batch/input row are caller values. |
| failure | Admission or begin failure throws runtime_error; factory/configuration errors propagate. |
| cost | Builds the 12-input plan/session, configures collector, admits one event and stages pending work. |
| Design | [tests/unit/instrumentation_memory_test.cpp](../../../../../tests/unit/instrumentation_memory_test.cpp), [include/crown/runtime/session.hpp](../../../../../include/crown/runtime/session.hpp), [src/runtime/session.cpp](../../../../../src/runtime/session.cpp), [CMakeLists.txt](../../../../../CMakeLists.txt), [tests/support/indexed_runtime_fixture.hpp](../../../../../tests/support/indexed_runtime_fixture.hpp) |

## B0013

[Lines 171–206](../../../../../tests/unit/instrumentation_memory_test.cpp#L171); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void pending_session_capture(bool indexed) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Capture workload counters while a session has uncommitted private work, checking ownership, caps, and persistent faults. |
| inputs / outputs | Input: backend selector. Returns no value. Captures pending snapshot for one queued/begun input; exercises measured peak exact/under caps and fault-after positions. |
| invariants | Uncapped capture has pending=true, 8 intercepted new calls equal account successful-allocation delta, and 4 capture-owner blocks. One-under failure leaves no output/current-byte delta and committed/progress sequence 0; exact capture survives session drop with pending marker and original owner. Persistent sweep requires 8 failed positions, each with no partial output/current change/progress, then a successful retry. |
| ownership | Session, runtime, snapshot control/arrays share original account; snapshot is retained after session drop until explicitly reset. Drop/reset cleanup is under fault-after-zero. Return optional is handle ownership, not a deep copy. |
| failure | Only MemoryFailure(limit) at byte boundary and bad_alloc in fault sweep count as expected failures; event refusal or changed progress fails. |
| cost | Pending capture includes the runtime snapshot and with_pending() copied numeric arrays. Counts cover intercepted C++ new; the account measures request bytes. No RSS/CPU statement. |
| Design | [tests/unit/instrumentation_memory_test.cpp](../../../../../tests/unit/instrumentation_memory_test.cpp), [include/crown/runtime/session.hpp](../../../../../include/crown/runtime/session.hpp), [src/runtime/session.cpp](../../../../../src/runtime/session.cpp), [include/crown/runtime/workload_statistics.hpp](../../../../../include/crown/runtime/workload_statistics.hpp), [src/runtime/workload_statistics.cpp](../../../../../src/runtime/workload_statistics.cpp), [tests/support/index_allocation.hpp](../../../../../tests/support/index_allocation.hpp) |

## B0014

[Lines 207–207](../../../../../tests/unit/instrumentation_memory_test.cpp#L207); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L207-L207:sha256:533f16bca7d58f44b3103b92e3485d22cfbb34bbad5ea3f3fa3b5a9dcb24ec89
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Close the recorded declaration scopes in instrumentation_memory_test.cpp: namespace (anonymous). |
| inputs / outputs | Preceding namespace, type or initializer declarations in; completed lexical boundary out. |
| invariants | Brace-opening context is recorded in root-scope-context-v1.json. These are declaration/initializer boundaries, not an independent update, validation or recovery operation. |
| ownership | Enclosing objects and borrowed fields keep their declared ownership. This punctuation creates no new owner. |
| failure | Malformed scope syntax is a compile error. Any initializer/constructor failure belongs to the enclosing object declaration. |
| cost | No separate loop, guard or engine call is introduced by the delimiter; enclosing initialization and object lifetime still have their actual costs. |
| Design | [tests/unit/instrumentation_memory_test.cpp](../../../../../tests/unit/instrumentation_memory_test.cpp), [docs/query_memory.md](../../../../query_memory.md), [docs/code_review.md](../../../../code_review.md) |

## B0015

[Lines 208–212](../../../../../tests/unit/instrumentation_memory_test.cpp#L208); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
int main() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Run observation, workload, and pending-session allocation fixtures for both backends. |
| inputs / outputs | No inputs. Runs the observation constructor case once and three fixture groups for reference/indexed backends. |
| invariants | Catches std::exception, writes failure and returns 1; otherwise prints completion and returns 0. Output is the source program’s behavior only. |
| ownership | All test runtime/snapshot/account lifetimes are bounded by helper scopes. |
| failure | Any assertion/exception fails the process. |
| cost | Delegates to fixed 12-input, 9,000-event and bounded allocation-fault fixtures. |
| Design | [tests/unit/instrumentation_memory_test.cpp](../../../../../tests/unit/instrumentation_memory_test.cpp) |
