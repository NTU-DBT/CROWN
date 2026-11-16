# `tests/unit/delta_memory_test.cpp` — block usage map

[Source](../../../../../tests/unit/delta_memory_test.cpp) · [Source index](../../../README.md) · [Subsystem contracts](../../../subsystem_contracts.md) · [Reviewed primitives](../../../primitives.md)

Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection.

Snapshot SHA-256: `6a53cd762d77d4b1ef384261b8e3891b9d1ad5da0a755e88d0c19bd63e3c2b6e`. 266 lines partitioned into 20 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [tests](../../../subsystem_contracts.md#tests). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/code_review.md](../../../../code_review.md), [docs/reference_fuzz.md](../../../../reference_fuzz.md), [docs/task_ledger.md](../../../../task_ledger.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–14](../../../../../tests/unit/delta_memory_test.cpp#L1) | Imports dependencies; declares namespace scope; declares aliases. |  · [reviewed contract](#b0001) |
| [B0002 · 15–17](../../../../../tests/unit/delta_memory_test.cpp#L15) | Callable definition: void check(bool value,std::string_view message) | calls std::runtime_error, std::string; guard void check(bool value,std::string_view message) { · [reviewed contract](#b0002) |
| [B0003 · 18–27](../../../../../tests/unit/delta_memory_test.cpp#L18) | Callable definition: PhysicalPlan plan(bool indexed) | calls planner::lower_tree, s04_runtime::options; returns planner::lower_tree(catalog,query,tree,indexed?s04_runtime::options():PhysicalOptions{}) · [reviewed contract](#b0003) |
| [B0004 · 28–28](../../../../../tests/unit/delta_memory_test.cpp#L28) | Callable definition: Row parent(std::size_t i) | calls std::string, std::to_string; returns {std::string(@ ,10)+std::string(8192,@ )+std::to_string(i),std::int64_t{42}} · [reviewed contract](#b0004) |
| [B0005 · 29–29](../../../../../tests/unit/delta_memory_test.cpp#L29) | Callable definition: Row child() | calls ; returns {std::int64_t{42}} · [reviewed contract](#b0005) |
| [B0006 · 30–34](../../../../../tests/unit/delta_memory_test.cpp#L30) | Callable definition: DeltaOptions options(LiveMaintenance maintenance,DeltaCompletion completion,DeltaMode mode=DeltaMode::delta, std::uint64_t cap=st… | calls max; returns result · [reviewed contract](#b0006) |
| [B0007 · 35–37](../../../../../tests/unit/delta_memory_test.cpp#L35) | Callable definition: resource::MemoryAccount memory(DeltaRuntime& runtime) | calls RuntimeTestProbe::memory_account, RuntimeTestProbe::support, RuntimeTestProbe::physical; returns RuntimeTestProbe::memory_account(RuntimeTestProbe::support(RuntimeTestProbe::physical(runtime))) · [reviewed contract](#b0007) |
| [B0008 · 38–42](../../../../../tests/unit/delta_memory_test.cpp#L38) | Callable definition: void populate(DeltaRuntime& runtime,bool complete=false) | calls apply, parent, discard, child; growth insert · [reviewed contract](#b0008) |
| [B0009 · 43–51](../../../../../tests/unit/delta_memory_test.cpp#L43) | Callable definition: void reconcile(const resource::MemoryAccount& account) | calls check_invariants, statistics, add, check; guard check(purposes==state.current && lifetimes==state.current,"actual Delta memory does not reconcile");; 2 loop sites · [reviewed contract](#b0009) |
| [B0010 · 52–59](../../../../../tests/unit/delta_memory_test.cpp#L52) | Callable definition: resource::MemoryUsage delta_usage(const resource::MemoryAccount& account) | calls statistics_for; returns result; 1 loop sites · [reviewed contract](#b0010) |
| [B0011 · 60–65](../../../../../tests/unit/delta_memory_test.cpp#L60) | Callable definition: std::uint64_t delta_retained(const resource::MemoryAccount& account) | calls statistics_for; returns bytes; 1 loop sites · [reviewed contract](#b0011) |
| [B0012 · 66–70](../../../../../tests/unit/delta_memory_test.cpp#L66) | Callable definition: void controller_only(const resource::MemoryAccount& account) | calls reconcile, statistics, check, resource::MemoryAccount::control_bytes; guard check(state.current.allocations==1 && state.current.requested_bytes==resource::MemoryAccount::contr… · [reviewed contract](#b0012) |
| [B0013 · 71–76](../../../../../tests/unit/delta_memory_test.cpp#L71) | Callable definition: template&lt;class Operation&gt; void denied(Operation&& operation) | calls operation, check, fault, std::runtime_error; guard check(failure.fault()==resource::MemoryFault::limit,"unexpected actual Delta memory failure");retur… · [reviewed contract](#b0013) |
| [B0014 · 77–108](../../../../../tests/unit/delta_memory_test.cpp#L77) | Callable definition: void bootstrap_caps(bool indexed) | calls plan, apply, parent, discard; guard check(peak&gt;setup,"native live/index bootstrap did not charge actual bytes");; growth insert; 1 loop sites · [reviewed contract](#b0014) |
| [B0015 · 109–132](../../../../../tests/unit/delta_memory_test.cpp#L109) | Callable definition: void epoch_caps(bool indexed,LiveMaintenance maintenance,DeltaCompletion completion) | calls plan, child, runtime, options; guard auto epoch=runtime.apply(update);check(epoch.remaining()==2,"native memory fixture emitted a differ…; growth insert · [reviewed contract](#b0015) |
| [B0016 · 133–161](../../../../../tests/unit/delta_memory_test.cpp#L133) | Callable definition: void undo_and_transfer(bool indexed,LiveMaintenance maintenance,DeltaCompletion completion) | calls plan, runtime, options, memory; guard check(payload&gt;=4*1024,"retained native live/parent-index string bytes were not actually attributed"…; growth emplace; 1 loop sites · [reviewed contract](#b0016) |
| [B0017 · 162–186](../../../../../tests/unit/delta_memory_test.cpp#L162) | Callable definition: void persistent_faults(bool indexed) | calls plan, child, runtime, options; guard ++failures;check(runtime.ready() && runtime.canonical_state()==before && delta_usage(account)==usag…; growth insert; 1 loop sites · [reviewed contract](#b0017) |
| [B0018 · 187–247](../../../../../tests/unit/delta_memory_test.cpp#L187) | Callable definition: void native_cursor_boundaries(bool indexed) | calls plan, runtime, RuntimeTestProbe::memory_account, apply; guard check(bool(old)==bool(row),"native/public cursor termination differs");; growth copy_of, emplace, insert; 1 loop sites · [reviewed contract](#b0018) |
| [B0019 · 248–248](../../../../../tests/unit/delta_memory_test.cpp#L248) | Closes surrounding scope/type. | source comment (unverified): // namespace · [reviewed contract](#b0019) |
| [B0020 · 249–266](../../../../../tests/unit/delta_memory_test.cpp#L249) | Callable definition: int main() | calls native_cursor_boundaries, bootstrap_caps, epoch_caps, undo_and_transfer; returns 1; 2 loop sites · [reviewed contract](#b0020) |

## B0001

[Lines 1–14](../../../../../tests/unit/delta_memory_test.cpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L1-L14:sha256:4a7582811726dc2a84d4a2f23d875c0c2c581ce25e97997418084bf93b56863c
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Prepare delta_memory_test.cpp: include "indexed_runtime_fixture.hpp", "runtime_probe.hpp", "index_allocation.hpp", "crown/runtime/delta.hpp", "crown/api/error.hpp", &lt;array&gt;, &lt;iostream&gt;, &lt;optional&gt;, &lt;stdexcept&gt;; bind local aliases/name imports. |
| inputs / outputs | Compiler-visible dependencies, names and the recorded declarations in; declarations available to the following fixture/CLI/example definitions out. |
| invariants | Declarations are scoped to this source/header and its selected ABI. Included code has its own effects; names and editable fixture values do not confer proof, admission or publication authority. |
| ownership | Aliases/includes do not create a query owner. Pointers/references/views are non-owning. Containers own their elements, which can themselves be borrowed pointers or numeric IDs. Only documented owning shared-control handles retain controls; IDs/slot-handle values do not independently keep an arena/runtime alive. |
| failure | Missing headers, ill-formed names/types, failed static assertions or active #error directives stop compilation. No runtime rejection/rollback mechanism is implemented by aliases or function prototypes. |
| cost | Preprocessing and type/constraint instantiation cost compilation. Alias/prototype syntax does not invoke the declared operation; any included definitions keep their own initialization effects. |
| Design | [tests/unit/delta_memory_test.cpp](../../../../../tests/unit/delta_memory_test.cpp), [docs/ordered_delta.md](../../../../ordered_delta.md), [docs/code_review.md](../../../../code_review.md) |

## B0002

[Lines 15–17](../../../../../tests/unit/delta_memory_test.cpp#L15); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void check(bool value,std::string_view message) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Provide the test assertion boundary for the Delta memory helpers. |
| inputs / outputs | Evaluates a boolean; on false, copies the supplied string_view into std::string and throws std::runtime_error. |
| invariants | The message is borrowed for the call; successful checks do not construct failure text. |
| ownership | Owns no persistent state or query-account storage. |
| failure | Only a false assertion throws; allocation failure while constructing the exception can propagate. |
| cost | One branch per check; error-string and exception work occurs only on failure. |
| Design | [tests/unit/delta_memory_test.cpp](../../../../../tests/unit/delta_memory_test.cpp) |

## B0003

[Lines 18–27](../../../../../tests/unit/delta_memory_test.cpp#L18); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
PhysicalPlan plan(bool indexed) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Build the small two-table physical plan used by Delta account tests. |
| inputs / outputs | Defines R(x:string,y:int64), S(y:int64), an R-parent/S-child tree joined on y, and a query head containing both x and y; indexed selects s04_runtime options, otherwise default reference options. |
| invariants | Both modes retain the same query/tree; only backend options differ. |
| ownership | Returns an owning PhysicalPlan; local catalog/query/tree are construction inputs. |
| failure | Lowering or allocation errors propagate from planner::lower_tree. |
| cost | Builds/validates one fixed two-node plan; cost is ordinary plan lowering, not one runtime update. |
| Design | [tests/unit/delta_memory_test.cpp](../../../../../tests/unit/delta_memory_test.cpp), [tests/support/indexed_runtime_fixture.hpp](../../../../../tests/support/indexed_runtime_fixture.hpp), [include/crown/planner/lower.hpp](../../../../../include/crown/planner/lower.hpp) |

## B0004

[Lines 28–28](../../../../../tests/unit/delta_memory_test.cpp#L28); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Row parent(std::size_t i) {return {std::string("left\0right",10)+std::string(8192,'q')+std::to_string(i),std::int64_t{42}};}
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Create a large distinct parent row for retained live-index payload checks. |
| inputs / outputs | Returns a 10-byte "left\0right" prefix, 8192 q bytes, decimal i, and int64 42. |
| invariants | The explicit prefix length retains the embedded NUL; i changes the key. |
| ownership | Ordinary Row/string storage, outside a runtime MemoryAccount until passed to an API. |
| failure | String allocation failures propagate. |
| cost | Constructs O(8192+digits(i)) payload with the ordinary allocator. |
| Design | [tests/unit/delta_memory_test.cpp](../../../../../tests/unit/delta_memory_test.cpp) |

## B0005

[Lines 29–29](../../../../../tests/unit/delta_memory_test.cpp#L29); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Row child() {return {std::int64_t{42}};}
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Create the separator child row used by joins and crossing events. |
| inputs / outputs | Returns the one-cell row containing int64 42. |
| invariants | Its value matches parent field y. |
| ownership | Ordinary Row value owned by caller. |
| failure | Allocation failures propagate. |
| cost | One scalar cell. |
| Design | [tests/unit/delta_memory_test.cpp](../../../../../tests/unit/delta_memory_test.cpp) |

## B0006

[Lines 30–34](../../../../../tests/unit/delta_memory_test.cpp#L30); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
DeltaOptions options(LiveMaintenance maintenance,DeltaCompletion completion,DeltaMode mode=DeltaMode::delta,
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Construct DeltaRuntime mode, maintenance, completion and account-cap options. |
| inputs / outputs | Copies enum arguments into DeltaOptions and sets physical.support.memory_limit_bytes; defaults mode=delta and cap=UINT64_MAX. |
| invariants | Does not change the compiled plan’s indexed work grant or component capacities. |
| ownership | Returns a value object; creates no account. |
| failure | Invalid option combinations are rejected downstream by runtime construction/use. |
| cost | Scalar assignments; runtime initialization/event work dominates. |
| Design | [tests/unit/delta_memory_test.cpp](../../../../../tests/unit/delta_memory_test.cpp), [include/crown/runtime/delta.hpp](../../../../../include/crown/runtime/delta.hpp), [docs/delta_runtime.md](../../../../delta_runtime.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0007

[Lines 35–37](../../../../../tests/unit/delta_memory_test.cpp#L35); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
resource::MemoryAccount memory(DeltaRuntime& runtime) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Recover the existing account shared by DeltaRuntime and its embedded physical/support owner. |
| inputs / outputs | Uses RuntimeTestProbe to reach DeltaRuntime physical owner, SupportRuntime, then its MemoryAccount. |
| invariants | Returns the existing account handle; creates no replacement allowance/account. |
| ownership | Copied MemoryAccount retains the controller after runtime facade destruction. |
| failure | Moved-from runtime/probe access can fail; no fallback account. |
| cost | Probe accesses and shared handle copy; no attribution-list scan. |
| Design | [tests/unit/delta_memory_test.cpp](../../../../../tests/unit/delta_memory_test.cpp), [tests/support/runtime_probe.hpp](../../../../../tests/support/runtime_probe.hpp), [include/crown/runtime/delta.hpp](../../../../../include/crown/runtime/delta.hpp), [src/runtime/delta.cpp](../../../../../src/runtime/delta.cpp), [docs/memory_accounts.md](../../../../memory_accounts.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0008

[Lines 38–42](../../../../../tests/unit/delta_memory_test.cpp#L38); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void populate(DeltaRuntime& runtime,bool complete=false) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Populate an initially empty Delta runtime with two parents and optionally the child. |
| inputs / outputs | Applies/discards R inserts at sequence 1 and 2; if complete, also S insert at sequence 3. |
| invariants | Requires a ready empty owner and unique rows; discard closes each output Epoch while committed state advances. |
| ownership | Runtime owns accepted source/live state; input rows and returned Epochs are local. |
| failure | Runtime, limit and allocation errors propagate. |
| cost | Two or three outer updates; indexed mode uses one shared five-domain grant per update. |
| Design | [tests/unit/delta_memory_test.cpp](../../../../../tests/unit/delta_memory_test.cpp), [include/crown/runtime/delta.hpp](../../../../../include/crown/runtime/delta.hpp), [src/runtime/delta.cpp](../../../../../src/runtime/delta.cpp), [include/crown/storage/index_work.hpp](../../../../../include/crown/storage/index_work.hpp), [src/runtime/storage_work.hpp](../../../../../src/runtime/storage_work.hpp), [docs/delta_runtime.md](../../../../delta_runtime.md), [docs/indexed_storage.md](../../../../indexed_storage.md) |

## B0009

[Lines 43–51](../../../../../tests/unit/delta_memory_test.cpp#L43); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void reconcile(const resource::MemoryAccount& account) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Reconcile the complete query-account allocation ledger for a Delta runtime. |
| inputs / outputs | Calls check_invariants, sums current MemoryUsage by all purposes and lifetimes, and checks current/peak requested bytes &lt;= account limit. |
| invariants | Both partition sums must equal whole-account current; requested bytes include account framing and are not RSS/allocator usable size. |
| ownership | Borrows the caller’s MemoryAccount handle. It exposes the shared controller/accounting state but does not itself retain runtime payload blocks; account-aware allocation owners govern those blocks’ lifetimes. |
| failure | Ledger, partition or cap mismatch throws through check. |
| cost | check_invariants walks live blocks; fixed purpose/lifetime arrays are summed separately. |
| Design | [tests/unit/delta_memory_test.cpp](../../../../../tests/unit/delta_memory_test.cpp), [include/crown/resource/memory.hpp](../../../../../include/crown/resource/memory.hpp), [src/resource/memory.cpp](../../../../../src/resource/memory.cpp), [docs/memory_accounts.md](../../../../memory_accounts.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0010

[Lines 52–59](../../../../../tests/unit/delta_memory_test.cpp#L52); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
resource::MemoryUsage delta_usage(const resource::MemoryAccount& account) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Measure current usage at the two Delta factor nodes plus Delta metadata attribution. |
| inputs / outputs | Sums statistics_for(delta_node,id).current for IDs 0, 1 and UINT64_MAX. |
| invariants | This selected attribution total is not whole-query current bytes; reconcile separately checks the whole account. Each statistics_for traverses live blocks. |
| ownership | Returns scalar MemoryUsage only. |
| failure | Account errors propagate; fixture totals are assumed below uint64 overflow. |
| cost | Three O(A) scans for A outstanding account blocks, plus scalar additions; not constant-time lookup. |
| Design | [tests/unit/delta_memory_test.cpp](../../../../../tests/unit/delta_memory_test.cpp), [include/crown/resource/memory.hpp](../../../../../include/crown/resource/memory.hpp), [src/resource/memory.cpp](../../../../../src/resource/memory.cpp), [src/runtime/delta.cpp](../../../../../src/runtime/delta.cpp), [docs/memory_accounts.md](../../../../memory_accounts.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0011

[Lines 60–65](../../../../../tests/unit/delta_memory_test.cpp#L60); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::uint64_t delta_retained(const resource::MemoryAccount& account) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Measure retained requested bytes under the same three Delta attribution IDs. |
| inputs / outputs | Sums retained-lifetime requested_bytes from delta_node IDs 0, 1 and UINT64_MAX. |
| invariants | Only those fixture-scoped attributions are included; it is neither total query usage nor all heap. |
| ownership | Returns scalar bytes; changes no lifetime. |
| failure | Account errors propagate; no overflow guard for the fixture sum. |
| cost | Three O(A) statistics_for scans and additions. |
| Design | [tests/unit/delta_memory_test.cpp](../../../../../tests/unit/delta_memory_test.cpp), [include/crown/resource/memory.hpp](../../../../../include/crown/resource/memory.hpp), [src/resource/memory.cpp](../../../../../src/resource/memory.cpp), [src/runtime/delta.cpp](../../../../../src/runtime/delta.cpp), [docs/memory_accounts.md](../../../../memory_accounts.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0012

[Lines 66–70](../../../../../tests/unit/delta_memory_test.cpp#L66); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void controller_only(const resource::MemoryAccount& account) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Verify only the MemoryAccount controller remains after Delta storage is released. |
| inputs / outputs | Reconciles the account then requires one current allocation and requested bytes equal control_bytes(). |
| invariants | Call after runtime/retained handles are destroyed; the passed account intentionally keeps its controller alive. |
| ownership | Borrows final account handle; no data block should remain. |
| failure | Any remaining allocation or mismatch throws. |
| cost | Full invariant-list walk and partition sums; not a process-heap check. |
| Design | [tests/unit/delta_memory_test.cpp](../../../../../tests/unit/delta_memory_test.cpp), [include/crown/resource/memory.hpp](../../../../../include/crown/resource/memory.hpp), [src/resource/memory.cpp](../../../../../src/resource/memory.cpp), [docs/memory_accounts.md](../../../../memory_accounts.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0013

[Lines 71–76](../../../../../tests/unit/delta_memory_test.cpp#L71); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
template<class Operation> void denied(Operation&& operation) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Require an actual query-account byte-limit denial from a Delta operation. |
| inputs / outputs | Invokes the named callable as an lvalue; accepts only MemoryFailure with MemoryFault::limit. |
| invariants | Does not accept storage-work, table-capacity, bad_alloc or other errors as byte denial. |
| ownership | Borrows callable during synchronous invocation. |
| failure | Wrong MemoryFailure or success throws; other exceptions propagate. |
| cost | One attempted operation and catch/check work; Delta work dominates. |
| Design | [tests/unit/delta_memory_test.cpp](../../../../../tests/unit/delta_memory_test.cpp), [include/crown/resource/memory.hpp](../../../../../include/crown/resource/memory.hpp), [docs/query_memory.md](../../../../query_memory.md) |

## B0014

[Lines 77–108](../../../../../tests/unit/delta_memory_test.cpp#L77); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void bootstrap_caps(bool indexed) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Measure and replay the bytes to bootstrap Delta live/index structures from maintenance state. |
| inputs / outputs | Per backend, bootstraps 32 R rows plus one S row in maintenance mode, records account peak before/after set_mode(delta), then repeats at exact and peak-1 caps. |
| invariants | Exported live factors must contain 32 and 1 rows. Exact cap reaches measured peak; one-under must be MemoryFault::limit and preserve ready/canonical/whole current-account state. This is byte capacity, separate from IndexWork. |
| ownership | Baseline/exact/limited runtimes each own an independent account; plan is shared immutable input; exported LiveSnapshot is temporary. |
| failure | Only actual account limit fault is accepted; changed state/bytes fails. |
| cost | Three runtimes/backend; each bootstraps 33 updates and calls set_mode once. Exact/under repeat setup; live_snapshot exports rows. |
| Design | [tests/unit/delta_memory_test.cpp](../../../../../tests/unit/delta_memory_test.cpp), [tests/support/indexed_runtime_fixture.hpp](../../../../../tests/support/indexed_runtime_fixture.hpp), [include/crown/runtime/delta.hpp](../../../../../include/crown/runtime/delta.hpp), [src/runtime/delta.cpp](../../../../../src/runtime/delta.cpp), [include/crown/runtime/physical.hpp](../../../../../include/crown/runtime/physical.hpp), [src/runtime/physical.cpp](../../../../../src/runtime/physical.cpp), [include/crown/storage/index_work.hpp](../../../../../include/crown/storage/index_work.hpp), [src/runtime/storage_work.hpp](../../../../../src/runtime/storage_work.hpp), [include/crown/resource/memory.hpp](../../../../../include/crown/resource/memory.hpp), [src/resource/memory.cpp](../../../../../src/resource/memory.cpp), [docs/delta_runtime.md](../../../../delta_runtime.md), [docs/memory_accounts.md](../../../../memory_accounts.md), [docs/query_memory.md](../../../../query_memory.md), [docs/indexed_storage.md](../../../../indexed_storage.md) |

## B0015

[Lines 109–132](../../../../../tests/unit/delta_memory_test.cpp#L109); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void epoch_caps(bool indexed,LiveMaintenance maintenance,DeltaCompletion completion) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Find the byte peak for a live Delta crossing and test one-byte-under rollback. |
| inputs / outputs | For a backend/maintenance/completion profile, populate two R rows and insert S at sequence 3, requiring two results; replay at exact peak and peak-1 caps. |
| invariants | One-under failure leaves ready/canonical state and selected Delta-owner current usage unchanged. The compared delta_usage is only node IDs 0/1/MAX; reconcile separately validates whole account and cap. |
| ownership | Each baseline/exact/limited run has separate runtime/account; input rows are ordinary values. |
| failure | Under-cap must be MemoryFailure::limit; any other stop/state change fails. |
| cost | Three runtime setups/profile, each with two setup updates and one crossing. Main runs five profiles/backend; attribution queries scan live blocks. |
| Design | [tests/unit/delta_memory_test.cpp](../../../../../tests/unit/delta_memory_test.cpp), [tests/support/indexed_runtime_fixture.hpp](../../../../../tests/support/indexed_runtime_fixture.hpp), [include/crown/runtime/delta.hpp](../../../../../include/crown/runtime/delta.hpp), [src/runtime/delta.cpp](../../../../../src/runtime/delta.cpp), [include/crown/storage/index_work.hpp](../../../../../include/crown/storage/index_work.hpp), [src/runtime/storage_work.hpp](../../../../../src/runtime/storage_work.hpp), [include/crown/resource/memory.hpp](../../../../../include/crown/resource/memory.hpp), [src/resource/memory.cpp](../../../../../src/resource/memory.cpp), [docs/delta_runtime.md](../../../../delta_runtime.md), [docs/memory_accounts.md](../../../../memory_accounts.md), [docs/query_memory.md](../../../../query_memory.md), [docs/indexed_storage.md](../../../../indexed_storage.md) |

## B0016

[Lines 133–161](../../../../../tests/unit/delta_memory_test.cpp#L133); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void undo_and_transfer(bool indexed,LiveMaintenance maintenance,DeltaCompletion completion) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Check rollback of a pending Delta erase, commit transfer, and release. |
| inputs / outputs | From two parents plus child, begins/drains sequence-4 child erase, rolls back, then repeats and commits while counting returned Epoch records. |
| invariants | Rollback restores canonical state, delta_usage and retained bytes to zero; non-eager modes first observe extracted nodes as retained. Prepared commit/iteration/cleanup make zero covered operator-new calls; commit yields two records and sequence 4. |
| ownership | Runtime owns live/index state; PendingEpoch/Epoch and account handles are scoped. Account tracks native rows; s04_alloc only observes C++ replacement-new attempts. |
| failure | Unexpected state/account/work changes throw; no-allocation scope does not observe direct malloc/RSS. |
| cost | One runtime/profile: three setup events, rollback cycle and commit/transfer cycle. Five profiles/backend; each attribution scan traverses account blocks. |
| Design | [tests/unit/delta_memory_test.cpp](../../../../../tests/unit/delta_memory_test.cpp), [tests/support/indexed_runtime_fixture.hpp](../../../../../tests/support/indexed_runtime_fixture.hpp), [tests/support/index_allocation.hpp](../../../../../tests/support/index_allocation.hpp), [tests/support/runtime_probe.hpp](../../../../../tests/support/runtime_probe.hpp), [include/crown/runtime/delta.hpp](../../../../../include/crown/runtime/delta.hpp), [src/runtime/delta.cpp](../../../../../src/runtime/delta.cpp), [include/crown/runtime/physical.hpp](../../../../../include/crown/runtime/physical.hpp), [src/runtime/physical.cpp](../../../../../src/runtime/physical.cpp), [include/crown/runtime/support.hpp](../../../../../include/crown/runtime/support.hpp), [src/runtime/support.cpp](../../../../../src/runtime/support.cpp), [include/crown/storage/index_work.hpp](../../../../../include/crown/storage/index_work.hpp), [src/runtime/storage_work.hpp](../../../../../src/runtime/storage_work.hpp), [include/crown/resource/memory.hpp](../../../../../include/crown/resource/memory.hpp), [src/resource/memory.cpp](../../../../../src/resource/memory.cpp), [include/crown/storage/accounted_table.hpp](../../../../../include/crown/storage/accounted_table.hpp), [include/crown/storage/accounted_arena.hpp](../../../../../include/crown/storage/accounted_arena.hpp), [docs/delta_lifecycle.md](../../../../delta_lifecycle.md), [docs/delta_runtime.md](../../../../delta_runtime.md), [docs/memory_accounts.md](../../../../memory_accounts.md), [docs/query_memory.md](../../../../query_memory.md), [docs/indexed_storage.md](../../../../indexed_storage.md) |

## B0017

[Lines 162–186](../../../../../tests/unit/delta_memory_test.cpp#L162); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void persistent_faults(bool indexed) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Inject increasing replacement-new failures into a Delta crossing and verify retry. |
| inputs / outputs | For fail_after values 0..2047, creates a fresh on_output/ordered_replay runtime, populates two parents, attempts child sequence 3 under s04_alloc and retries unscoped after bad_alloc. |
| invariants | Every failure preserves ready/canonical state and selected Delta attributions; each iteration reconciles the full account and checks controller-only after runtime destruction. It stops at the first nonthrowing completion; no separate calibration N or exact trigger/call-count assertion is made. |
| ownership | Runtime/account are new per point; setup and retry occur outside the fault scope. Shim covers executable C++ operator-new attempts only. |
| failure | Only bad_alloc is treated as injected; other errors propagate. Requires &gt;20 failures and one nonthrowing completion below 2048. |
| cost | Data-dependent fresh runtime/setup/update attempts up to 2048, retry for each failure and whole-account live-block scan each point; no fixed allocation or CPU count. |
| Design | [tests/unit/delta_memory_test.cpp](../../../../../tests/unit/delta_memory_test.cpp), [tests/support/indexed_runtime_fixture.hpp](../../../../../tests/support/indexed_runtime_fixture.hpp), [tests/support/index_allocation.hpp](../../../../../tests/support/index_allocation.hpp), [include/crown/runtime/delta.hpp](../../../../../include/crown/runtime/delta.hpp), [src/runtime/delta.cpp](../../../../../src/runtime/delta.cpp), [include/crown/storage/index_work.hpp](../../../../../include/crown/storage/index_work.hpp), [src/runtime/storage_work.hpp](../../../../../src/runtime/storage_work.hpp), [include/crown/resource/memory.hpp](../../../../../include/crown/resource/memory.hpp), [src/resource/memory.cpp](../../../../../src/resource/memory.cpp), [docs/delta_runtime.md](../../../../delta_runtime.md), [docs/memory_accounts.md](../../../../memory_accounts.md), [docs/query_memory.md](../../../../query_memory.md), [docs/indexed_storage.md](../../../../indexed_storage.md) |

## B0018

[Lines 187–247](../../../../../tests/unit/delta_memory_test.cpp#L187); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void native_cursor_boundaries(bool indexed) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Compare public/native support cursors and verify borrowed input and retained output lifetimes. |
| inputs / outputs | Per backend, applies two parent and one child row; compares visible-key cursor termination, values, layout token and last-work readings; compares one separator bucket; checks invalid native input codes; runs completions_native from a short-lived AccountedRow binding. |
| invariants | Native/public outputs match on the exercised rows. The emitted AccountedTuple survives borrowed-input and runtime destruction, remains charged above controller bytes, then releases under zero covered operator-new calls. Cursor work equality is a diagnostic, not CPU time. |
| ownership | The constructed SupportRuntime owns logical support state; no PhysicalRuntime source-table owner is constructed in this helper. The retained AccountedTuple pin and copied MemoryAccount handle outlive the SupportRuntime. |
| failure | Invalid native inputs must report exact Error codes; changed values/layout/account owner or failed retention throws. |
| cost | Each invocation creates one SupportRuntime for its indexed/reference option, applies three updates, performs finite visible-key, bucket and completion cursor reads plus invalid-input probes, then checks one row after runtime destruction and reconciles the account once. Main invokes it separately for each backend. |
| Design | [tests/unit/delta_memory_test.cpp](../../../../../tests/unit/delta_memory_test.cpp), [tests/support/indexed_runtime_fixture.hpp](../../../../../tests/support/indexed_runtime_fixture.hpp), [tests/support/index_allocation.hpp](../../../../../tests/support/index_allocation.hpp), [tests/support/runtime_probe.hpp](../../../../../tests/support/runtime_probe.hpp), [include/crown/runtime/delta.hpp](../../../../../include/crown/runtime/delta.hpp), [src/runtime/delta.cpp](../../../../../src/runtime/delta.cpp), [include/crown/runtime/physical.hpp](../../../../../include/crown/runtime/physical.hpp), [src/runtime/physical.cpp](../../../../../src/runtime/physical.cpp), [include/crown/runtime/support.hpp](../../../../../include/crown/runtime/support.hpp), [src/runtime/support.cpp](../../../../../src/runtime/support.cpp), [include/crown/storage/index_work.hpp](../../../../../include/crown/storage/index_work.hpp), [src/runtime/storage_work.hpp](../../../../../src/runtime/storage_work.hpp), [include/crown/resource/memory.hpp](../../../../../include/crown/resource/memory.hpp), [src/resource/memory.cpp](../../../../../src/resource/memory.cpp), [include/crown/storage/accounted_table.hpp](../../../../../include/crown/storage/accounted_table.hpp), [include/crown/storage/accounted_arena.hpp](../../../../../include/crown/storage/accounted_arena.hpp), [include/crown/storage/layout.hpp](../../../../../include/crown/storage/layout.hpp), [docs/memory_accounts.md](../../../../memory_accounts.md), [docs/query_memory.md](../../../../query_memory.md), [docs/indexed_storage.md](../../../../indexed_storage.md) |

## B0019

[Lines 248–248](../../../../../tests/unit/delta_memory_test.cpp#L248); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L248-L248:sha256:533f16bca7d58f44b3103b92e3485d22cfbb34bbad5ea3f3fa3b5a9dcb24ec89
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Close the recorded declaration scopes in delta_memory_test.cpp: namespace (anonymous). |
| inputs / outputs | Preceding namespace, type or initializer declarations in; completed lexical boundary out. |
| invariants | Brace-opening context is recorded in root-scope-context-v1.json. These are declaration/initializer boundaries, not an independent update, validation or recovery operation. |
| ownership | Enclosing objects and borrowed fields keep their declared ownership. This punctuation creates no new owner. |
| failure | Malformed scope syntax is a compile error. Any initializer/constructor failure belongs to the enclosing object declaration. |
| cost | No separate loop, guard or engine call is introduced by the delimiter; enclosing initialization and object lifetime still have their actual costs. |
| Design | [tests/unit/delta_memory_test.cpp](../../../../../tests/unit/delta_memory_test.cpp), [docs/ordered_delta.md](../../../../ordered_delta.md), [docs/code_review.md](../../../../code_review.md) |

## B0020

[Lines 249–266](../../../../../tests/unit/delta_memory_test.cpp#L249); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
int main() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Run Delta memory and runtime-boundary helpers over indexed and reference backend settings. |
| inputs / outputs | For each backend setting, runs cursor boundaries, bootstrap caps, five epoch-cap and five undo/transfer profiles, and persistent faults. |
| invariants | The completion print is source text, not execution evidence; exact byte peaks and first-success fault positions are runtime observations. |
| ownership | Every helper constructs and releases its own runtime/account. |
| failure | Catches std::exception, prints the diagnostic and returns status 1; non-standard exceptions are not caught by this handler. |
| cost | 26 helper calls: per backend 1 cursor + 1 bootstrap + 5 cap + 5 rollback/transfer + 1 persistent-fault; inner update counts vary by profile. |
| Design | [tests/unit/delta_memory_test.cpp](../../../../../tests/unit/delta_memory_test.cpp), [tests/support/indexed_runtime_fixture.hpp](../../../../../tests/support/indexed_runtime_fixture.hpp), [tests/support/runtime_probe.hpp](../../../../../tests/support/runtime_probe.hpp), [tests/support/index_allocation.hpp](../../../../../tests/support/index_allocation.hpp), [include/crown/runtime/delta.hpp](../../../../../include/crown/runtime/delta.hpp), [src/runtime/delta.cpp](../../../../../src/runtime/delta.cpp), [include/crown/runtime/physical.hpp](../../../../../include/crown/runtime/physical.hpp), [src/runtime/physical.cpp](../../../../../src/runtime/physical.cpp), [include/crown/runtime/support.hpp](../../../../../include/crown/runtime/support.hpp), [src/runtime/support.cpp](../../../../../src/runtime/support.cpp), [include/crown/storage/index_work.hpp](../../../../../include/crown/storage/index_work.hpp), [src/runtime/storage_work.hpp](../../../../../src/runtime/storage_work.hpp), [include/crown/resource/memory.hpp](../../../../../include/crown/resource/memory.hpp), [src/resource/memory.cpp](../../../../../src/resource/memory.cpp), [docs/delta_runtime.md](../../../../delta_runtime.md), [docs/memory_accounts.md](../../../../memory_accounts.md), [docs/indexed_storage.md](../../../../indexed_storage.md) |
