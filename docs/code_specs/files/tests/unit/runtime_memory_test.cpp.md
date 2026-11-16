# `tests/unit/runtime_memory_test.cpp` — block usage map

[Source](../../../../../tests/unit/runtime_memory_test.cpp) · [Source index](../../../README.md) · [Subsystem contracts](../../../subsystem_contracts.md) · [Reviewed primitives](../../../primitives.md)

Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection.

Snapshot SHA-256: `614ef2f5353b268b9a290804f1f5c85a27b90452071fbee30b4f309af931228a`. 451 lines partitioned into 25 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [tests](../../../subsystem_contracts.md#tests). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/code_review.md](../../../../code_review.md), [docs/reference_fuzz.md](../../../../reference_fuzz.md), [docs/task_ledger.md](../../../../task_ledger.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–14](../../../../../tests/unit/runtime_memory_test.cpp#L1) | Imports dependencies; declares namespace scope; declares aliases. |  · [reviewed contract](#b0001) |
| [B0002 · 15–17](../../../../../tests/unit/runtime_memory_test.cpp#L15) | Callable definition: void check(bool value,std::string_view message) | calls std::runtime_error, std::string; guard void check(bool value,std::string_view message) { · [reviewed contract](#b0002) |
| [B0003 · 18–24](../../../../../tests/unit/runtime_memory_test.cpp#L18) | Callable definition: template&lt;class F&gt; void denied(F&& operation) | calls operation, check, fault, std::runtime_error; guard check(failure.fault()==resource::MemoryFault::limit,"unexpected memory rejection");return; · [reviewed contract](#b0003) |
| [B0004 · 25–33](../../../../../tests/unit/runtime_memory_test.cpp#L25) | Callable definition: PhysicalPlan plan(bool indexed) | calls planner::lower_tree, s04_runtime::options; returns planner::lower_tree(catalog,query,tree,indexed?s04_runtime::options():PhysicalOptions{}) · [reviewed contract](#b0004) |
| [B0005 · 34–34](../../../../../tests/unit/runtime_memory_test.cpp#L34) | Callable definition: Row parent(std::size_t i) | calls std::string, std::to_string; returns {std::string(100,@ )+std::to_string(i),std::int64_t{42}} · [reviewed contract](#b0005) |
| [B0006 · 35–35](../../../../../tests/unit/runtime_memory_test.cpp#L35) | Callable definition: Row child() | calls ; returns {std::int64_t{42}} · [reviewed contract](#b0006) |
| [B0007 · 36–39](../../../../../tests/unit/runtime_memory_test.cpp#L36) | Callable definition: void populate(SupportRuntime& runtime) | calls apply, parent; growth insert · [reviewed contract](#b0007) |
| [B0008 · 40–43](../../../../../tests/unit/runtime_memory_test.cpp#L40) | Callable definition: void populate(PhysicalRuntime& runtime) | calls apply, parent; growth insert · [reviewed contract](#b0008) |
| [B0009 · 44–55](../../../../../tests/unit/runtime_memory_test.cpp#L44) | Callable definition: void reconcile(const resource::MemoryAccount& account) | calls check_invariants, statistics, add, check; guard check(purposes==stats.current && lifetimes==stats.current,"routed bytes do not reconcile");; 2 loop sites · [reviewed contract](#b0009) |
| [B0010 · 56–91](../../../../../tests/unit/runtime_memory_test.cpp#L56) | Callable definition: void exact_epoch(bool indexed) | calls plan, golden, populate, accounted_memory_statistics; guard check(peak&gt;setup_peak,"crossing must exceed the setup peak");; growth insert; source comment (unverified): // Native tables may keep admitted arena/directory capacity after rollback. · [reviewed contract](#b0010) |
| [B0011 · 92–125](../../../../../tests/unit/runtime_memory_test.cpp#L92) | Callable definition: void undo_and_churn(bool indexed) | calls runtime, plan, accounted_memory_statistics, populate; guard check(pending.stage(NodeId{1},child()),"deletion fixture did not change state");; growth insert; 1 loop sites; source comment (unverified): // A closed pending token may retain its original lease until destruction. · [reviewed contract](#b0011) |
| [B0012 · 126–142](../../../../../tests/unit/runtime_memory_test.cpp#L126) | Callable definition: void retained_owners(bool indexed) | calls runtime, plan, RuntimeTestProbe::memory_account, populate; guard check(account.statistics().current.allocations&gt;1,"retained cursor lost query ownership");; growth emplace, insert · [reviewed contract](#b0012) |
| [B0013 · 143–173](../../../../../tests/unit/runtime_memory_test.cpp#L143) | Callable definition: void cursor_limits(bool indexed) | calls plan, golden, accounted_memory_statistics, reserve; guard check(peak&gt;startup,"concurrent cursors must exceed the constructor peak");; growth push_back, reserve; 4 loop sites · [reviewed contract](#b0013) |
| [B0014 · 174–174](../../../../../tests/unit/runtime_memory_test.cpp#L174) | Callable definition: std::string binary_binding() | calls std::string, append; returns value · [reviewed contract](#b0014) |
| [B0015 · 175–216](../../../../../tests/unit/runtime_memory_test.cpp#L175) | Callable definition: void binding_limits(bool indexed) | calls plan, binary_binding, golden, accounted_memory_statistics; guard check(peak&gt;before.peak_requested_bytes,"binary binding must exceed the empty runtime peak");; growth emplace, insert · [reviewed contract](#b0015) |
| [B0016 · 217–224](../../../../../tests/unit/runtime_memory_test.cpp#L217) | Callable definition: PhysicalPlan overlay_plan(bool indexed) | calls planner::lower_tree, s04_runtime::options; returns planner::lower_tree(catalog,query,tree,indexed?s04_runtime::options():PhysicalOptions{}) · [reviewed contract](#b0016) |
| [B0017 · 225–282](../../../../../tests/unit/runtime_memory_test.cpp#L225) | Callable definition: void overlay_limits(bool indexed) | calls overlay_plan, binary_binding, apply, golden; guard check(pending.stage(NodeId{0},input),"overlay fixture did not erase the root");; growth emplace, insert · [reviewed contract](#b0017) |
| [B0018 · 283–305](../../../../../tests/unit/runtime_memory_test.cpp#L283) | Callable definition: void persistent_faults(bool indexed) | calls plan, runtime, populate, canonical_state; guard if (!triggered) { check(!failed && runtime.sequence()==3,"fault sweep ended without a committed epo…; growth insert; 1 loop sites · [reviewed contract](#b0018) |
| [B0019 · 306–339](../../../../../tests/unit/runtime_memory_test.cpp#L306) | Callable definition: void rebuild_and_composition(bool indexed) | calls physical, plan, populate, accounted_memory_statistics; guard check(RuntimeTestProbe::support(physical).accounted_memory_statistics().owner==owner,"physical/supp… · [reviewed contract](#b0019) |
| [B0020 · 340–345](../../../../../tests/unit/runtime_memory_test.cpp#L340) | Callable definition: PhysicalPlan payload_plan(bool indexed) | calls planner::lower_tree, s04_runtime::options; returns planner::lower_tree(catalog,query,tree,indexed?s04_runtime::options():PhysicalOptions{}) · [reviewed contract](#b0020) |
| [B0021 · 346–396](../../../../../tests/unit/runtime_memory_test.cpp#L346) | Callable definition: void compact_source_epoch(bool indexed) | calls payload_plan, std::string, append, golden; guard static_assert(std::is_same_v&lt;decltype(epoch.input.source-&gt;tuple()),const storage::AccountedTuple&&gt;);; growth emplace, insert · [reviewed contract](#b0021) |
| [B0022 · 397–408](../../../../../tests/unit/runtime_memory_test.cpp#L397) | Callable definition: void scalar_compatibility() | calls std::string, Date::parse, Decimal::parse, resource::MemoryAccount::create; guard check(owned.view()==values && values==owned.view() && (owned.view()&lt;=&gt;values)==0,; growth copy_of · [reviewed contract](#b0022) |
| [B0023 · 409–437](../../../../../tests/unit/runtime_memory_test.cpp#L409) | Callable definition: void physical_persistent_faults(bool indexed) | calls plan, child, runtime, populate; guard if(!triggered){check(!failed && runtime.sequence()==3,"physical fault sweep ended without commit");…; growth insert; 1 loop sites · [reviewed contract](#b0023) |
| [B0024 · 438–438](../../../../../tests/unit/runtime_memory_test.cpp#L438) | Closes surrounding scope/type. | source comment (unverified): // namespace · [reviewed contract](#b0024) |
| [B0025 · 439–451](../../../../../tests/unit/runtime_memory_test.cpp#L439) | Callable definition: int main() | calls scalar_compatibility, exact_epoch, undo_and_churn, retained_owners; returns 0; 1; 1 loop sites · [reviewed contract](#b0025) |

## B0001

[Lines 1–14](../../../../../tests/unit/runtime_memory_test.cpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L1-L14:sha256:8858e906c2a35738ae764c2a2276b22f2cb13f5c6ff13783bee94fb6ebcbbc03
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Prepare runtime_memory_test.cpp: include "indexed_runtime_fixture.hpp", "runtime_probe.hpp", "index_allocation.hpp", "crown/runtime/session.hpp", "crown/io/support.hpp", &lt;iostream&gt;, &lt;optional&gt;, &lt;stdexcept&gt;, &lt;type_traits&gt;; bind local aliases/name imports. |
| inputs / outputs | Compiler-visible dependencies, names and the recorded declarations in; declarations available to the following fixture/CLI/example definitions out. |
| invariants | Declarations are scoped to this source/header and its selected ABI. Included code has its own effects; names and editable fixture values do not confer proof, admission or publication authority. |
| ownership | Aliases/includes do not create a query owner. Pointers/references/views are non-owning. Containers own their elements, which can themselves be borrowed pointers or numeric IDs. Only documented owning shared-control handles retain controls; IDs/slot-handle values do not independently keep an arena/runtime alive. |
| failure | Missing headers, ill-formed names/types, failed static assertions or active #error directives stop compilation. No runtime rejection/rollback mechanism is implemented by aliases or function prototypes. |
| cost | Preprocessing and type/constraint instantiation cost compilation. Alias/prototype syntax does not invoke the declared operation; any included definitions keep their own initialization effects. |
| Design | [tests/unit/runtime_memory_test.cpp](../../../../../tests/unit/runtime_memory_test.cpp), [docs/query_memory.md](../../../../query_memory.md), [docs/code_review.md](../../../../code_review.md) |

## B0002

[Lines 15–17](../../../../../tests/unit/runtime_memory_test.cpp#L15); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void check(bool value,std::string_view message) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Provide the test file's fail-fast assertion boundary. |
| inputs / outputs | Boolean condition and diagnostic string_view in; returns normally when true, otherwise throws std::runtime_error with an owning string. |
| invariants | The helper checks only the supplied condition and does not collect multiple failures or establish runtime semantics by itself. |
| ownership | The message is borrowed until it is copied into the exception; no state beyond the temporary diagnostic is retained. |
| failure | False condition throws std::runtime_error; string construction failure propagates. |
| cost | One branch and, on failure, diagnostic string construction; assertion counts belong to the caller. |
| Design | [tests/unit/runtime_memory_test.cpp](../../../../../tests/unit/runtime_memory_test.cpp) |

## B0003

[Lines 18–24](../../../../../tests/unit/runtime_memory_test.cpp#L18); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
template<class F> void denied(F&& operation) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Require an operation to fail with an actual account byte-limit MemoryFailure. |
| inputs / outputs | Callable passed as F&&; invokes the named parameter operation() and returns after catching MemoryFailure whose fault() is MemoryFault::limit. |
| invariants | A different MemoryFailure triggers check failure; a different exception propagates. This helper does not use std::forward on the named rvalue-reference parameter. |
| ownership | The operation is borrowed for the call; caught exception state is not retained. |
| failure | Throws std::runtime_error if no limit failure occurs or the fault code differs; other operation exceptions propagate. |
| cost | One operation invocation and one catch/check path; it makes no bound claim about allocations performed by the operation. |
| Design | [include/crown/resource/memory.hpp](../../../../../include/crown/resource/memory.hpp), [include/crown/runtime/support.hpp](../../../../../include/crown/runtime/support.hpp), [tests/support/indexed_runtime_fixture.hpp](../../../../../tests/support/indexed_runtime_fixture.hpp), [tests/support/runtime_probe.hpp](../../../../../tests/support/runtime_probe.hpp), [tests/unit/runtime_memory_test.cpp](../../../../../tests/unit/runtime_memory_test.cpp) |

## B0004

[Lines 25–33](../../../../../tests/unit/runtime_memory_test.cpp#L25); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
PhysicalPlan plan(bool indexed) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Construct the two-node support/physical fixture plan, optionally selecting indexed storage. |
| inputs / outputs | indexed flag in; PhysicalPlan for relations r(x:string,y:int64) and s(y:int64), with x projected, out. |
| invariants | The tree has native root r with child s joined on y; indexed=true selects s04_runtime::options(), otherwise PhysicalOptions{}. |
| ownership | Returns an owning plan; fixture Catalog, Query, and FreeConnexTree are local construction inputs. |
| failure | Planner validation/allocation failures propagate; this helper adds no exception translation. |
| cost | Fixed two-relation/two-node fixture construction and lowering; it does not execute the plan. |
| Design | [include/crown/planner/lower.hpp](../../../../../include/crown/planner/lower.hpp), [tests/support/indexed_runtime_fixture.hpp](../../../../../tests/support/indexed_runtime_fixture.hpp), [tests/support/runtime_probe.hpp](../../../../../tests/support/runtime_probe.hpp), [tests/unit/runtime_memory_test.cpp](../../../../../tests/unit/runtime_memory_test.cpp) |

## B0005

[Lines 34–34](../../../../../tests/unit/runtime_memory_test.cpp#L34); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Row parent(std::size_t i) { return {std::string(100,'x')+std::to_string(i),std::int64_t{42}}; }
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Create one deterministic parent row for the memory fixtures. |
| inputs / outputs | Index i in; Row containing a 100-character 'x' prefix plus decimal i and int64 42 out. |
| invariants | The parent key bytes vary with i while the joined y value remains 42. |
| ownership | Returns an owning Row and its string payload. |
| failure | Standard string/row allocation failures propagate. |
| cost | Builds one finite row; payload length is 100 plus the decimal spelling of i. |
| Design | [tests/unit/runtime_memory_test.cpp](../../../../../tests/unit/runtime_memory_test.cpp) |

## B0006

[Lines 35–35](../../../../../tests/unit/runtime_memory_test.cpp#L35); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Row child() { return {std::int64_t{42}}; }
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Create the joined child fixture row. |
| inputs / outputs | No inputs; one-field Row containing int64 42 out. |
| invariants | Its y value matches parent(i)'s second field. |
| ownership | Returns an owning Row with no dynamic string payload. |
| failure | No custom failure handling; any library failure propagates. |
| cost | Fixed one-scalar row construction. |
| Design | [tests/unit/runtime_memory_test.cpp](../../../../../tests/unit/runtime_memory_test.cpp) |

## B0007

[Lines 36–39](../../../../../tests/unit/runtime_memory_test.cpp#L36); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void populate(SupportRuntime& runtime) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Seed two parent rows into a SupportRuntime fixture. |
| inputs / outputs | SupportRuntime reference in; applies insert events at sequence 1 and 2 to NodeId{0} using parent(1) and parent(2); no result out. |
| invariants | The helper ignores both returned epoch values and is used to prepare the root state for later test operations. |
| ownership | Runtime retains inserted state; each input Row is a temporary owned by the call expression. |
| failure | Apply failures propagate; the helper does not restore a partially seeded runtime. |
| cost | Exactly two apply calls and two parent-row constructions. |
| Design | [include/crown/resource/memory.hpp](../../../../../include/crown/resource/memory.hpp), [include/crown/runtime/support.hpp](../../../../../include/crown/runtime/support.hpp), [tests/support/indexed_runtime_fixture.hpp](../../../../../tests/support/indexed_runtime_fixture.hpp), [tests/support/runtime_probe.hpp](../../../../../tests/support/runtime_probe.hpp), [tests/unit/runtime_memory_test.cpp](../../../../../tests/unit/runtime_memory_test.cpp) |

## B0008

[Lines 40–43](../../../../../tests/unit/runtime_memory_test.cpp#L40); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void populate(PhysicalRuntime& runtime) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Seed two parent rows into a PhysicalRuntime fixture. |
| inputs / outputs | PhysicalRuntime reference in; applies insert events at sequence 1 and 2 to TableId{0} using parent(1) and parent(2); no result out. |
| invariants | This helper seeds physical source rows and does not assert support propagation or query output. |
| ownership | Runtime retains inserted source state; each input Row is temporary. |
| failure | Apply failures propagate; no rollback wrapper is provided. |
| cost | Exactly two apply calls and two parent-row constructions. |
| Design | [include/crown/resource/memory.hpp](../../../../../include/crown/resource/memory.hpp), [include/crown/runtime/physical.hpp](../../../../../include/crown/runtime/physical.hpp), [tests/support/indexed_runtime_fixture.hpp](../../../../../tests/support/indexed_runtime_fixture.hpp), [tests/support/runtime_probe.hpp](../../../../../tests/support/runtime_probe.hpp), [tests/unit/runtime_memory_test.cpp](../../../../../tests/unit/runtime_memory_test.cpp) |

## B0009

[Lines 44–55](../../../../../tests/unit/runtime_memory_test.cpp#L44); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void reconcile(const resource::MemoryAccount& account) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Check account ledger invariants and reconcile current requested usage partitions. |
| inputs / outputs | MemoryAccount reference in; calls check_invariants/statistics and sums allocations, requested_bytes, and payload_bytes across by_purpose and by_lifetime; no value out. |
| invariants | Both summed partitions must equal statistics().current, and current.requested_bytes plus peak_requested_bytes must each be at most limit_bytes. These account-request counters are not RSS or allocator usable size. |
| ownership | The account handle is borrowed; statistics and totals are local values. |
| failure | check_invariants or check failure propagates; mismatch throws std::runtime_error. |
| cost | Scans both fixed-size purpose/lifetime arrays and performs an explicit account diagnostic; no whole-process memory claim is made. |
| Design | [include/crown/resource/memory.hpp](../../../../../include/crown/resource/memory.hpp), [tests/unit/runtime_memory_test.cpp](../../../../../tests/unit/runtime_memory_test.cpp) |

## B0010

[Lines 56–91](../../../../../tests/unit/runtime_memory_test.cpp#L56); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void exact_epoch(bool indexed) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Measure one real child-insert peak, then check exact-cap admission and one-byte-under denial for a support epoch. |
| inputs / outputs | indexed flag in; builds a golden plan/runtime, records peak_requested_bytes before/after inserting child at sequence 3, reruns at that exact cap, then at cap minus one; no structured value out. |
| invariants | The fixture asserts the observed peak exceeds setup; exact observed peak is admitted. One byte under must report MemoryFault::limit, preserve ready() and canonical_state(), restore tuple_values requested bytes, retain no records or pins, and permit an erase retry at sequence 3. This is one finite fixture peak, not a universal bound. |
| ownership | Each runtime owns its account and committed state; RuntimeTestProbe returns a shared account handle for reconciliation. |
| failure | Unexpected memory fault or any failed condition throws; apply/planner errors propagate. The denied insert's prior epoch is checked, not generalized rollback for all failures. |
| cost | Three routes per backend: one golden peak calibration, one exact-cap run and one one-under run with its retry. Statistics and canonical-state snapshots add explicit diagnostic work. |
| Design | [include/crown/resource/memory.hpp](../../../../../include/crown/resource/memory.hpp), [include/crown/runtime/support.hpp](../../../../../include/crown/runtime/support.hpp), [tests/support/index_allocation.hpp](../../../../../tests/support/index_allocation.hpp), [tests/support/indexed_runtime_fixture.hpp](../../../../../tests/support/indexed_runtime_fixture.hpp), [tests/support/runtime_probe.hpp](../../../../../tests/support/runtime_probe.hpp), [tests/unit/runtime_memory_test.cpp](../../../../../tests/unit/runtime_memory_test.cpp) |

## B0011

[Lines 92–125](../../../../../tests/unit/runtime_memory_test.cpp#L92); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void undo_and_churn(bool indexed) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Check staged erase rollback, retained undo classification, and bounded repeated insert/erase churn. |
| inputs / outputs | indexed flag in; seeds and commits support state, stages erase of child, explicitly rolls back under s04_alloc::Scope(0), then performs deletes and 40 insert/duplicate-insert/erase cycles; no value out. |
| invariants | Before/after canonical_state must match on rollback; retained requested bytes must be positive while the erase token is pending; covered C++ new calls during rollback must be zero. Duplicate insert preserves account.statistics().current; each churn erase returns it to the warm-empty usage. This is 40 fixture iterations, not an unbounded leak proof. |
| ownership | Runtime/account own state; pending token is scoped and destroyed after rollback. Native capacity may remain charged and is intentionally compared at its warm level. |
| failure | Failed assertions throw; runtime errors propagate. The injected zero-call observation covers this test replacement-new hook, not libc malloc or every byte-account path. |
| cost | Three setup applies, one staged erase/rollback, three teardown applies, then forty cycles of three applies (120 churn applies), with account and canonical-state diagnostics. |
| Design | [include/crown/resource/memory.hpp](../../../../../include/crown/resource/memory.hpp), [tests/support/index_allocation.hpp](../../../../../tests/support/index_allocation.hpp), [tests/support/indexed_runtime_fixture.hpp](../../../../../tests/support/indexed_runtime_fixture.hpp), [tests/support/runtime_probe.hpp](../../../../../tests/support/runtime_probe.hpp), [tests/unit/runtime_memory_test.cpp](../../../../../tests/unit/runtime_memory_test.cpp) |

## B0012

[Lines 126–142](../../../../../tests/unit/runtime_memory_test.cpp#L126); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void retained_owners(bool indexed) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Check that a result cursor and public journal retain query ownership after SupportRuntime destruction. |
| inputs / outputs | indexed flag in; creates runtime, retains its MemoryAccount, applies a child epoch and keeps its journal plus ResultCursor across facade scope; calls next(), then releases cursor and journal; no result count out. |
| invariants | Cursor next() must produce a value after facade destruction; after cursor reset journal_undo still has requested bytes while journal lives; after journal reset the ledger reconciles to one control allocation. |
| ownership | Cursor, journal, and copied MemoryAccount independently extend their owners according to their public handles; locals are reset explicitly. |
| failure | Failed assertions or cursor/account operations propagate; no alternate cleanup path is asserted. |
| cost | One small finite fixture, one cursor read, and explicit account diagnostics. |
| Design | [include/crown/resource/memory.hpp](../../../../../include/crown/resource/memory.hpp), [include/crown/runtime/support.hpp](../../../../../include/crown/runtime/support.hpp), [tests/support/indexed_runtime_fixture.hpp](../../../../../tests/support/indexed_runtime_fixture.hpp), [tests/support/runtime_probe.hpp](../../../../../tests/support/runtime_probe.hpp), [tests/unit/runtime_memory_test.cpp](../../../../../tests/unit/runtime_memory_test.cpp) |

## B0013

[Lines 143–173](../../../../../tests/unit/runtime_memory_test.cpp#L143); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void cursor_limits(bool indexed) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Measure four concurrent result-cursor startup peak and test exact/one-under admission with lease preservation. |
| inputs / outputs | indexed flag in; observes startup and peak for four cursors, admits four at exact peak, then creates three under a one-byte-smaller cap and checks a fourth results() call is denied; no cursor rows are consumed. |
| invariants | Golden peak must exceed startup; exact peak is admitted. One-under failure leaves current usage unchanged and the three existing cursors active; after their scope runtime remains ready with unchanged canonical_state, a smaller one-cursor retry is active, then releases its lease. The peak is fixture-specific. |
| ownership | Runtime owns the account; cursor vector owns live read leases and is scoped before retry. |
| failure | Only MemoryFault::limit is accepted by denied(); other failures propagate. The check covers constructor/startup failure and the visible leases in this setup. |
| cost | At most four live cursors in the measured route, with account/canonical diagnostics before and after. |
| Design | [include/crown/resource/memory.hpp](../../../../../include/crown/resource/memory.hpp), [include/crown/runtime/support.hpp](../../../../../include/crown/runtime/support.hpp), [tests/support/indexed_runtime_fixture.hpp](../../../../../tests/support/indexed_runtime_fixture.hpp), [tests/support/runtime_probe.hpp](../../../../../tests/support/runtime_probe.hpp), [tests/unit/runtime_memory_test.cpp](../../../../../tests/unit/runtime_memory_test.cpp) |

## B0014

[Lines 174–174](../../../../../tests/unit/runtime_memory_test.cpp#L174); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::string binary_binding() { auto value=std::string(8192,'b');value.append("\0\xff",2);return value; }
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Build the binary binding fixture used by completion tests. |
| inputs / outputs | No inputs; string of 8192 'b' bytes followed by two bytes 0x00 and 0xff out. |
| invariants | The appended bytes are preserved as binary string content; total size is 8194 bytes. |
| ownership | Returns an owning std::string. |
| failure | String allocation failure propagates. |
| cost | Creates one finite string of 8194 bytes. |
| Design | [tests/unit/runtime_memory_test.cpp](../../../../../tests/unit/runtime_memory_test.cpp) |

## B0015

[Lines 175–216](../../../../../tests/unit/runtime_memory_test.cpp#L175); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void binding_limits(bool indexed) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Check completion binding payload charging, limit retry, and retained result ownership for an 8194-byte binary key. |
| inputs / outputs | indexed flag in; builds FixedAssignment for VariableId{0}, measures completions(fixed) peak and tuple_values delta, tests exact/one-under limits with a shorter retry, then keeps a binary completion cursor/result across facade lifetime; no structured value out. |
| invariants | Tuple_values requested bytes increase by at least binary.size(); exact observed peak is admitted; one-under denial leaves ready(), canonical_state(), and current bytes unchanged and allows the short binding retry. A returned result equals the binary key and retains a one-field layout/account until result reset. Fixture observations do not bound all bindings. |
| ownership | Runtime account is copied outside facade scope; cursor and returned Result retain the native payload/view until reset. |
| failure | denied() accepts only MemoryFault::limit. Other planner/cursor failures propagate; explicit result reset precedes final control-only check. |
| cost | Three binding cap routes (golden, exact, one-under with short retry), then one retained-cursor/result route per backend; equality, statistics and reconciliation inspect the selected values. |
| Design | [include/crown/resource/memory.hpp](../../../../../include/crown/resource/memory.hpp), [include/crown/runtime/support.hpp](../../../../../include/crown/runtime/support.hpp), [include/crown/storage/accounted_layout.hpp](../../../../../include/crown/storage/accounted_layout.hpp), [include/crown/storage/tuple_values.hpp](../../../../../include/crown/storage/tuple_values.hpp), [tests/support/indexed_runtime_fixture.hpp](../../../../../tests/support/indexed_runtime_fixture.hpp), [tests/support/runtime_probe.hpp](../../../../../tests/support/runtime_probe.hpp), [tests/unit/runtime_memory_test.cpp](../../../../../tests/unit/runtime_memory_test.cpp) |

## B0016

[Lines 217–224](../../../../../tests/unit/runtime_memory_test.cpp#L217); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
PhysicalPlan overlay_plan(bool indexed) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Construct the shared-key overlay fixture plan used by before-snapshot view tests. |
| inputs / outputs | indexed flag in; returns a PhysicalPlan for r(x:string,y:int64) joined to s(x:string), projecting y, with r as root and s child. |
| invariants | The join key is x, and indexed=true selects s04_runtime::options(); this function only lowers a fixed plan. |
| ownership | The plan owns the compiled fixture; local Catalog, Query, and FreeConnexTree are temporary inputs. |
| failure | Planner validation/allocation failures propagate. |
| cost | Fixed two-relation/two-node construction and lowering. |
| Design | [include/crown/planner/lower.hpp](../../../../../include/crown/planner/lower.hpp), [tests/support/indexed_runtime_fixture.hpp](../../../../../tests/support/indexed_runtime_fixture.hpp), [tests/support/runtime_probe.hpp](../../../../../tests/support/runtime_probe.hpp), [tests/unit/runtime_memory_test.cpp](../../../../../tests/unit/runtime_memory_test.cpp) |

## B0017

[Lines 225–282](../../../../../tests/unit/runtime_memory_test.cpp#L225); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void overlay_limits(bool indexed) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Measure before-delete overlay construction for a binary x key and check exact/one-under admission, rollback, and retained lookups. |
| inputs / outputs | indexed flag in; seeds r/s with an 8194-byte binary x, stages root erase, builds SnapshotSide::before view, measures peak and tuple_values bytes, then checks exact and one-under caps plus committed retained witness/completion cursors; no aggregate result out. |
| invariants | Selected view must restore at least one bucket entry, add at least three binary-size charges, and preserve the before-delete answer. Exact observed peak is admitted. One-under view failure leaves pending active, preview without answer, and current usage unchanged; injected rollback observes zero covered C++ new calls. Committed retained view is valid/non-tentative, witness returns (x,y), completion returns y, and owning results have two-/one-field layouts. These are selected fixture checks only. |
| ownership | Pending epoch owns staged mutation; view/cursors/results and copied account are retained explicitly across commit and facade destruction, then reset in order. |
| failure | Only MemoryFault::limit is accepted for the view denial. Rollback and reset failures are not hidden; no guarantee beyond this injected path is stated. |
| cost | Each route stages one erase; exact/one-under capture and retained witness/completion cursors add bounded fixture scans and account snapshots. |
| Design | [include/crown/resource/memory.hpp](../../../../../include/crown/resource/memory.hpp), [include/crown/runtime/support.hpp](../../../../../include/crown/runtime/support.hpp), [include/crown/storage/accounted_layout.hpp](../../../../../include/crown/storage/accounted_layout.hpp), [include/crown/storage/tuple_values.hpp](../../../../../include/crown/storage/tuple_values.hpp), [tests/support/index_allocation.hpp](../../../../../tests/support/index_allocation.hpp), [tests/support/indexed_runtime_fixture.hpp](../../../../../tests/support/indexed_runtime_fixture.hpp), [tests/support/runtime_probe.hpp](../../../../../tests/support/runtime_probe.hpp), [tests/unit/runtime_memory_test.cpp](../../../../../tests/unit/runtime_memory_test.cpp) |

## B0018

[Lines 283–305](../../../../../tests/unit/runtime_memory_test.cpp#L283); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void persistent_faults(bool indexed) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Sweep persistent allocation-failure positions for one support child-insert route and verify same-sequence retry. |
| inputs / outputs | For fail positions 0 through 1999, constructs/seeds a fresh SupportRuntime and injects persistent covered-new denial around sequence-3 child insertion. Triggered failures retry the same sequence after the denial scope. Returns void and prints the observed triggered-position count. |
| invariants | At each triggered position apply must throw std::bad_alloc, keep tuple_values usage and canonical_state, leave runtime ready, and preserve at least prior requested bytes; retry must commit sequence 3 with an answer. The loop stops at the first untriggered position and requires more than 20 triggered positions. This covers replacement C++ new attempts in this route, not libc malloc or all allocators. |
| ownership | Every loop iteration creates an independent runtime/account; failure scope is destroyed before state checks and retry. |
| failure | Unexpected exception types propagate. If no successful commit ends the sweep by fail==1999, or too few positions trigger, std::runtime_error is thrown. |
| cost | At most 2000 fresh fixture runtimes per indexed setting, each with seed, one injected apply, possible retry, and accounting/canonical diagnostics. |
| Design | [include/crown/resource/memory.hpp](../../../../../include/crown/resource/memory.hpp), [tests/support/index_allocation.hpp](../../../../../tests/support/index_allocation.hpp), [tests/support/indexed_runtime_fixture.hpp](../../../../../tests/support/indexed_runtime_fixture.hpp), [tests/support/runtime_probe.hpp](../../../../../tests/support/runtime_probe.hpp), [tests/unit/runtime_memory_test.cpp](../../../../../tests/unit/runtime_memory_test.cpp) |

## B0019

[Lines 306–339](../../../../../tests/unit/runtime_memory_test.cpp#L306); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void rebuild_and_composition(bool indexed) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Check shared account identity and retained-byte behavior through physical rebuild, DeltaRuntime options/trace, and QuerySession stop/drop. |
| inputs / outputs | indexed flag in; builds physical, delta, and typed session owners; compares account owner IDs, rebuild state/usage, 1 MiB support cap in observation and trace roundtrip, then session statistics across stop/drop; no value out. |
| invariants | Physical/support share an owner ID; the scoped physical rebuild charges overlapping old/new state to that account, matches canonical state and releases back to prior usage. The requested 1 MiB support-memory cap survives the Delta observation and support-trace roundtrip; the Delta rebuild retains its original owner. Session reports a nonzero owner and 1 MiB cap, keeps that owner after stop and exposes no account after drop. Other DeltaOptions fields are not round-tripped by these checks. |
| ownership | Physical, Delta and Session values own their respective runtimes. The physical rebuilt value has an inner scope; the Delta rebuilt value lives to function exit. Trace JSON and copied statistics are ordinary test locals. |
| failure | Planner, trace encoding/decoding, and session construction errors propagate; failed assertion throws std::runtime_error. |
| cost | One rebuild each for physical and delta plus one typed session lifecycle and a trace serialization roundtrip. |
| Design | [include/crown/io/support.hpp](../../../../../include/crown/io/support.hpp), [include/crown/resource/memory.hpp](../../../../../include/crown/resource/memory.hpp), [include/crown/runtime/delta.hpp](../../../../../include/crown/runtime/delta.hpp), [include/crown/runtime/physical.hpp](../../../../../include/crown/runtime/physical.hpp), [include/crown/runtime/session.hpp](../../../../../include/crown/runtime/session.hpp), [tests/support/indexed_runtime_fixture.hpp](../../../../../tests/support/indexed_runtime_fixture.hpp), [tests/support/runtime_probe.hpp](../../../../../tests/support/runtime_probe.hpp), [tests/unit/runtime_memory_test.cpp](../../../../../tests/unit/runtime_memory_test.cpp) |

## B0020

[Lines 340–345](../../../../../tests/unit/runtime_memory_test.cpp#L340); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
PhysicalPlan payload_plan(bool indexed) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Construct a one-relation physical plan whose query ignores a string source column. |
| inputs / outputs | indexed flag in; returns PhysicalPlan over r(x:int64,payload:string) projecting x while the physical occurrence includes IgnoredColumn{} for payload. |
| invariants | The fixture deliberately retains a full physical source row although the selected query output is only x; indexed=true selects the indexed fixture options. |
| ownership | Plan owns compiled metadata; the local catalog/query/tree are construction inputs. |
| failure | Lowering failures propagate. |
| cost | Fixed one-relation fixture lowering. |
| Design | [include/crown/planner/lower.hpp](../../../../../include/crown/planner/lower.hpp), [tests/support/indexed_runtime_fixture.hpp](../../../../../tests/support/indexed_runtime_fixture.hpp), [tests/support/runtime_probe.hpp](../../../../../tests/support/runtime_probe.hpp), [tests/unit/runtime_memory_test.cpp](../../../../../tests/unit/runtime_memory_test.cpp) |

## B0021

[Lines 346–396](../../../../../tests/unit/runtime_memory_test.cpp#L346); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void compact_source_epoch(bool indexed) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Check exact and one-under memory peaks for compact physical source epochs, retained source pins, and owning get_source exports. |
| inputs / outputs | Inserts one row with int64 7 and an 8194-byte ignored payload, calibrates its retained epoch peak, checks exact and one-under caps with a smaller retry, then retains a PhysicalEpoch input pin across facade destruction. A get_source export is checked only while its runtime is alive. |
| invariants | The input pin exposes const storage::AccountedTuple& with the complete ignored payload. Exact observed peak succeeds; one-under denial leaves sequence, gauges and derivation count empty and permits smaller retry. During the live scope, get_source returns optional&lt;AccountedTuple&gt; with original account/output attribution, and another runtime rejects its handle with foreign_handle. After facade destruction, the held epoch input pin still has the large row; resetting it returns the account to its controller. The exported get_source local is not tested after facade destruction. |
| ownership | The live runtime source arena owns the inserted row. Its exported AccountedTuple local is destroyed before that runtime; the optional PhysicalEpoch retains its input source pin and journal beyond the facade and is reset before the final account check. |
| failure | denied() accepts MemoryFault::limit; foreign source must surface Error code foreign_handle. Other failures propagate. |
| cost | Four finite routes per backend: golden calibration, exact cap, one-under cap with smaller retry, and retained epoch pin/export/foreign-handle checks. Diagnostics inspect the selected one-row fixture. |
| Design | [include/crown/resource/memory.hpp](../../../../../include/crown/resource/memory.hpp), [include/crown/runtime/physical.hpp](../../../../../include/crown/runtime/physical.hpp), [include/crown/storage/accounted_layout.hpp](../../../../../include/crown/storage/accounted_layout.hpp), [tests/support/indexed_runtime_fixture.hpp](../../../../../tests/support/indexed_runtime_fixture.hpp), [tests/support/runtime_probe.hpp](../../../../../tests/support/runtime_probe.hpp), [tests/unit/runtime_memory_test.cpp](../../../../../tests/unit/runtime_memory_test.cpp) |

## B0022

[Lines 397–408](../../../../../tests/unit/runtime_memory_test.cpp#L397); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void scalar_compatibility() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Check borrowed AccountedRow comparisons and explicit scalar export on a selected mixed scalar row. |
| inputs / outputs | Creates an AccountedRow from int64, binary string, bool, Date, and Decimal values; compares borrowed view both directions and exports a Row. |
| invariants | The selected value set must compare equal and spaceship-equal under zero covered C++ new calls; export_row must reproduce exact/binary values. This does not test all scalar domains or string lengths. |
| ownership | MemoryAccount and AccountedRow own native values; input Row is local and export_row returns an owning Row. |
| failure | Account/row construction and explicit export failures propagate; failed equality/no-allocation assertions throw. |
| cost | One five-field fixture undergoes three borrowed comparisons (two equality directions and one spaceship) under deny-new, followed by an explicit owning export and equality check. |
| Design | [include/crown/resource/memory.hpp](../../../../../include/crown/resource/memory.hpp), [include/crown/storage/accounted_row.hpp](../../../../../include/crown/storage/accounted_row.hpp), [include/crown/storage/tuple_values.hpp](../../../../../include/crown/storage/tuple_values.hpp), [tests/support/index_allocation.hpp](../../../../../tests/support/index_allocation.hpp), [tests/unit/runtime_memory_test.cpp](../../../../../tests/unit/runtime_memory_test.cpp) |

## B0023

[Lines 409–437](../../../../../tests/unit/runtime_memory_test.cpp#L409); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void physical_persistent_faults(bool indexed) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Sweep persistent allocation-failure positions for one composed physical child insert while checking stable source handles and retry. |
| inputs / outputs | indexed flag in; for fail positions 0 through 2999 creates/seeds PhysicalRuntime, saves two source handles, injects failure around insert into TableId{1} at sequence 3, then probes handles and retries triggered failures. |
| invariants | Each triggered failure must preserve ready() and canonical_state(), keep both prior source handles readable with exact parent rows, reconcile the query account, and permit retry to sequence 3 with an answer and source tuple handle value 1. At least 41 positions must trigger; the first untriggered point ends the sweep. This is limited to covered C++ new attempts observed on this route. |
| ownership | Each position uses a fresh runtime and copied account handle; saved handles are borrowed identifiers, and returned AccountedTuple values are temporary probes. |
| failure | The injected std::bad_alloc is the expected failure; other exceptions propagate. Missing termination by 3000 positions or an insufficient sweep throws std::runtime_error. |
| cost | At most 3000 fresh physical fixtures per backend, each with two seeds, two source lookups, one faulted apply, reconciliation, and possible retry. |
| Design | [include/crown/resource/memory.hpp](../../../../../include/crown/resource/memory.hpp), [include/crown/runtime/physical.hpp](../../../../../include/crown/runtime/physical.hpp), [tests/support/index_allocation.hpp](../../../../../tests/support/index_allocation.hpp), [tests/support/indexed_runtime_fixture.hpp](../../../../../tests/support/indexed_runtime_fixture.hpp), [tests/support/runtime_probe.hpp](../../../../../tests/support/runtime_probe.hpp), [tests/unit/runtime_memory_test.cpp](../../../../../tests/unit/runtime_memory_test.cpp) |

## B0024

[Lines 438–438](../../../../../tests/unit/runtime_memory_test.cpp#L438); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L438-L438:sha256:533f16bca7d58f44b3103b92e3485d22cfbb34bbad5ea3f3fa3b5a9dcb24ec89
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Close the recorded declaration scopes in runtime_memory_test.cpp: namespace (anonymous). |
| inputs / outputs | Preceding namespace, type or initializer declarations in; completed lexical boundary out. |
| invariants | Brace-opening context is recorded in root-scope-context-v1.json. These are declaration/initializer boundaries, not an independent update, validation or recovery operation. |
| ownership | Enclosing objects and borrowed fields keep their declared ownership. This punctuation creates no new owner. |
| failure | Malformed scope syntax is a compile error. Any initializer/constructor failure belongs to the enclosing object declaration. |
| cost | No separate loop, guard or engine call is introduced by the delimiter; enclosing initialization and object lifetime still have their actual costs. |
| Design | [tests/unit/runtime_memory_test.cpp](../../../../../tests/unit/runtime_memory_test.cpp), [docs/query_memory.md](../../../../query_memory.md), [docs/code_review.md](../../../../code_review.md) |

## B0025

[Lines 439–451](../../../../../tests/unit/runtime_memory_test.cpp#L439); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
int main() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Provide the runtime memory test executable's no-argument entry point and explicit remaining-coverage note. |
| inputs / outputs | No argument parameters are inspected. Runs scalar_compatibility once and ten named helpers for each indexed=false/true setting, prints progress/final coverage text, and returns 0 on success. |
| invariants | Any std::exception is printed to stderr and returns 1. The final text explicitly leaves legacy plan, exported outputs/captures, delta, and session coverage open; helper coverage is bounded to the listed fixtures. |
| ownership | The entry point owns all called fixture/runtime locals through their helper scopes; no report or result is returned to a caller. |
| failure | Catches std::exception only at this outer boundary; returns nonzero on that path. |
| cost | Runs the finite helper matrix in source order; internal fault loops and cursor/account diagnostics dominate cost. This packet documents source and does not claim the executable was run. |
| Design | [tests/support/index_allocation.hpp](../../../../../tests/support/index_allocation.hpp), [tests/support/indexed_runtime_fixture.hpp](../../../../../tests/support/indexed_runtime_fixture.hpp), [tests/support/runtime_probe.hpp](../../../../../tests/support/runtime_probe.hpp), [tests/unit/runtime_memory_test.cpp](../../../../../tests/unit/runtime_memory_test.cpp) |
