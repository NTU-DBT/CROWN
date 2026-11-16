# `tests/unit/public_tuple_memory_test.cpp` — block usage map

[Source](../../../../../tests/unit/public_tuple_memory_test.cpp) · [Source index](../../../README.md) · [Subsystem contracts](../../../subsystem_contracts.md) · [Reviewed primitives](../../../primitives.md)

Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection.

Snapshot SHA-256: `4804e374cbe0e2072bf2a32a1b1b11c27d10a5d14a7e4da0c798654f3397675d`. 226 lines partitioned into 20 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [tests](../../../subsystem_contracts.md#tests). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/code_review.md](../../../../code_review.md), [docs/reference_fuzz.md](../../../../reference_fuzz.md), [docs/task_ledger.md](../../../../task_ledger.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–17](../../../../../tests/unit/public_tuple_memory_test.cpp#L1) | Imports dependencies; declares namespace scope; declares aliases. |  · [reviewed contract](#b0001) |
| [B0002 · 18–20](../../../../../tests/unit/public_tuple_memory_test.cpp#L18) | Callable definition: void check(bool value,std::string_view message) | calls std::runtime_error, std::string; guard void check(bool value,std::string_view message) { · [reviewed contract](#b0002) |
| [B0003 · 21–21](../../../../../tests/unit/public_tuple_memory_test.cpp#L21) | Callable definition: resource::MemoryAccount unlimited() | calls resource::MemoryAccount::create; returns resource::MemoryAccount::create(UINT64_MAX) · [reviewed contract](#b0003) |
| [B0004 · 22–22](../../../../../tests/unit/public_tuple_memory_test.cpp#L22) | declares values/defaults or compile-time conditions. |  · [reviewed contract](#b0004) |
| [B0005 · 23–27](../../../../../tests/unit/public_tuple_memory_test.cpp#L23) | Callable definition: TupleLayout source_layout() | calls std::string; returns {LayoutId{3},{{ScalarType::int64},{ScalarType::string,{},VariableId{0}}, · [reviewed contract](#b0005) |
| [B0006 · 28–32](../../../../../tests/unit/public_tuple_memory_test.cpp#L28) | Callable definition: Row scalars(std::size_t length=4096) | calls std::string, Date::parse, Decimal::parse; returns {std::int64_t{-7},text,true,Date::parse(@ ), · [reviewed contract](#b0006) |
| [B0007 · 33–41](../../../../../tests/unit/public_tuple_memory_test.cpp#L33) | Callable definition: void reconcile(const resource::MemoryAccount& account) | calls check_invariants, statistics, add, check; guard check(purposes==state.current && lifetimes==state.current,"public tuple allocations do not reconcil…; 2 loop sites · [reviewed contract](#b0007) |
| [B0008 · 42–46](../../../../../tests/unit/public_tuple_memory_test.cpp#L42) | Callable definition: void controller_only(const resource::MemoryAccount& account) | calls reconcile, statistics, check, resource::MemoryAccount::control_bytes; guard check(state.current.allocations==1 && state.current.requested_bytes==resource::MemoryAccount::contr… · [reviewed contract](#b0008) |
| [B0009 · 47–52](../../../../../tests/unit/public_tuple_memory_test.cpp#L47) | Callable definition: template&lt;class F&gt;void denied(F&& operation) | calls operation, check, fault, std::runtime_error; guard check(failure.fault()==resource::MemoryFault::limit,"unexpected public tuple rejection");return; · [reviewed contract](#b0009) |
| [B0010 · 53–105](../../../../../tests/unit/public_tuple_memory_test.cpp#L53) | Callable definition: void native_views() | calls unlimited, scalars, row_hash, source_layout; guard check(tuple.is_accounted() && tuple.account_statistics().owner==account.statistics().owner,; 1 loop sites · [reviewed contract](#b0010) |
| [B0011 · 106–148](../../../../../tests/unit/public_tuple_memory_test.cpp#L106) | Callable definition: void limits_and_failures() | calls source_layout, scalars, unlimited, AccountedLayout::freeze; guard check(tuple.is_accounted(),"native descriptor payload was unaccounted");; 1 loop sites · [reviewed contract](#b0011) |
| [B0012 · 149–157](../../../../../tests/unit/public_tuple_memory_test.cpp#L149) | Callable definition: PhysicalPlan query(bool indexed) | calls planner::lower_tree, s04_runtime::options; returns planner::lower_tree(catalog,query,tree,indexed?s04_runtime::options():PhysicalOptions{}) · [reviewed contract](#b0012) |
| [B0013 · 158–158](../../../../../tests/unit/public_tuple_memory_test.cpp#L158) | Callable definition: Row parent() | calls std::string; returns {std::string(@ ,12)+std::string(16384,@ ),std::int64_t{42}} · [reviewed contract](#b0013) |
| [B0014 · 159–159](../../../../../tests/unit/public_tuple_memory_test.cpp#L159) | Callable definition: Row child() | calls ; returns {std::int64_t{42}} · [reviewed contract](#b0014) |
| [B0015 · 160–162](../../../../../tests/unit/public_tuple_memory_test.cpp#L160) | Callable definition: DeltaOptions options(std::uint64_t cap=UINT64_MAX) | calls ; returns options · [reviewed contract](#b0015) |
| [B0016 · 163–165](../../../../../tests/unit/public_tuple_memory_test.cpp#L163) | Callable definition: resource::MemoryAccount memory(DeltaRuntime& runtime) | calls RuntimeTestProbe::memory_account, RuntimeTestProbe::support, RuntimeTestProbe::physical; returns RuntimeTestProbe::memory_account(RuntimeTestProbe::support(RuntimeTestProbe::physical(runtime))) · [reviewed contract](#b0016) |
| [B0017 · 166–190](../../../../../tests/unit/public_tuple_memory_test.cpp#L166) | Callable definition: void output_transfer(bool indexed) | calls runtime, query, options, memory; guard check(record && record-&gt;tuple.is_accounted(),"committed public output has no native payload owner");; growth emplace, insert · [reviewed contract](#b0017) |
| [B0018 · 191–218](../../../../../tests/unit/public_tuple_memory_test.cpp#L191) | Callable definition: void retained_output_cap(bool indexed) | calls query, runtime, options, apply; guard check(bool(record),"retained output fixture produced no row");retained=record-&gt;tuple.values();}; growth insert · [reviewed contract](#b0018) |
| [B0019 · 219–219](../../../../../tests/unit/public_tuple_memory_test.cpp#L219) | Closes surrounding scope/type. | source comment (unverified): // namespace · [reviewed contract](#b0019) |
| [B0020 · 220–226](../../../../../tests/unit/public_tuple_memory_test.cpp#L220) | Callable definition: int main() | calls native_views, limits_and_failures, output_transfer, retained_output_cap; returns 1; 1 loop sites · [reviewed contract](#b0020) |

## B0001

[Lines 1–17](../../../../../tests/unit/public_tuple_memory_test.cpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L1-L17:sha256:8726dd13bd32c821716f2e3183e6d57b075f4ca7e14e3a89f491bbbce89faa24
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Prepare public_tuple_memory_test.cpp: include "crown/storage/accounted_layout.hpp", "crown/storage/accounted_projection.hpp", "crown/runtime/delta.hpp", "crown/io/document.hpp", "indexed_runtime_fixture.hpp", "runtime_probe.hpp", "index_allocation.hpp", &lt;array&gt;, &lt;iostream&gt;, &lt;optional&gt;, &lt;stdexcept&gt;; bind local aliases/name imports. |
| inputs / outputs | Compiler-visible dependencies, names and the recorded declarations in; declarations available to the following fixture/CLI/example definitions out. |
| invariants | Declarations are scoped to this source/header and its selected ABI. Included code has its own effects; names and editable fixture values do not confer proof, admission or publication authority. |
| ownership | Aliases/includes do not create a query owner. Pointers/references/views are non-owning. Containers own their elements, which can themselves be borrowed pointers or numeric IDs. Only documented owning shared-control handles retain controls; IDs/slot-handle values do not independently keep an arena/runtime alive. |
| failure | Missing headers, ill-formed names/types, failed static assertions or active #error directives stop compilation. No runtime rejection/rollback mechanism is implemented by aliases or function prototypes. |
| cost | Preprocessing and type/constraint instantiation cost compilation. Alias/prototype syntax does not invoke the declared operation; any included definitions keep their own initialization effects. |
| Design | [tests/unit/public_tuple_memory_test.cpp](../../../../../tests/unit/public_tuple_memory_test.cpp), [docs/storage.md](../../../../storage.md), [docs/code_review.md](../../../../code_review.md) |

## B0002

[Lines 18–20](../../../../../tests/unit/public_tuple_memory_test.cpp#L18); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void check(bool value,std::string_view message) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Provide the tuple test's fail-fast assertion boundary. |
| inputs / outputs | Boolean condition and diagnostic string_view in; throws std::runtime_error with copied message when false. |
| invariants | Checks the supplied condition only; callers determine the semantic scope. |
| ownership | Message is borrowed until exception construction; no other state retained. |
| failure | False condition throws std::runtime_error; allocation failure propagates. |
| cost | One branch and failure-only diagnostic construction. |
| Design | [tests/unit/public_tuple_memory_test.cpp](../../../../../tests/unit/public_tuple_memory_test.cpp) |

## B0003

[Lines 21–21](../../../../../tests/unit/public_tuple_memory_test.cpp#L21); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
resource::MemoryAccount unlimited(){return resource::MemoryAccount::create(UINT64_MAX);}
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Create the maximum representable uint64 byte grant for the ordinary finite tuple fixtures. |
| inputs / outputs | No input; returns MemoryAccount::create(UINT64_MAX). |
| invariants | The configured grant is UINT64_MAX. It keeps these small fixtures away from calibrated byte limits but does not disable admission, overflow or upstream allocation failures, and is not a measured maximum. |
| ownership | Returned handle owns/shared-retains its account control. |
| failure | Account construction failure propagates. |
| cost | One account-controller construction. |
| Design | [include/crown/resource/memory.hpp](../../../../../include/crown/resource/memory.hpp), [tests/support/index_allocation.hpp](../../../../../tests/support/index_allocation.hpp), [tests/unit/public_tuple_memory_test.cpp](../../../../../tests/unit/public_tuple_memory_test.cpp) |

## B0004

[Lines 22–22](../../../../../tests/unit/public_tuple_memory_test.cpp#L22); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L22-L22:sha256:86719a994ef4a1c3d778cddc165e5e4cbaf4bc8b99d7ca3331e245b29cae6669
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Prepare public_tuple_memory_test.cpp: declare constant fixture data. |
| inputs / outputs | Compiler-visible dependencies, names and the recorded declarations in; declarations available to the following fixture/CLI/example definitions out. The source span lists the exact member/global names, types and initial values; initializers run when the enclosing object/program/thread is initialized. |
| invariants | Declarations are scoped to this source/header and its selected ABI. Included code has its own effects; names and editable fixture values do not confer proof, admission or publication authority. |
| ownership | Aliases/includes do not create a query owner. Pointers/references/views are non-owning. Containers own their elements, which can themselves be borrowed pointers or numeric IDs. Only documented owning shared-control handles retain controls; IDs/slot-handle values do not independently keep an arena/runtime alive. |
| failure | Missing headers, ill-formed names/types, failed static assertions or active #error directives stop compilation. No runtime rejection/rollback mechanism is implemented by aliases or function prototypes. |
| cost | Preprocessing and type/constraint instantiation cost compilation. Alias/prototype syntax does not invoke the declared operation; any included definitions keep their own initialization effects. These constexpr data are fixed fixture constants; quota literals are grants, not reserved bytes or measured peaks. |
| Design | [tests/unit/public_tuple_memory_test.cpp](../../../../../tests/unit/public_tuple_memory_test.cpp), [docs/storage.md](../../../../storage.md), [docs/code_review.md](../../../../code_review.md) |

## B0005

[Lines 23–27](../../../../../tests/unit/public_tuple_memory_test.cpp#L23); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
TupleLayout source_layout() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Build the source TupleLayout descriptor used by public/native tuple conversion checks. |
| inputs / outputs | No input; returns LayoutId{3} with fields int64, string bound to VariableId{0}, boolean, date, decimal(38,0), and a second string bound to VariableId{0}; context version 7 and a 14-byte binary binding. |
| invariants | Field order, scalar kinds, decimal domain, repeated variable identity, layout ID, and context are fixed fixture data. |
| ownership | Returned TupleLayout owns its descriptor; temporary field vector and binding are moved/copied by its constructor. |
| failure | Descriptor/string allocation or validation failures propagate. |
| cost | Constructs one six-field descriptor and its short context string. |
| Design | [include/crown/resource/memory.hpp](../../../../../include/crown/resource/memory.hpp), [include/crown/storage/accounted_layout.hpp](../../../../../include/crown/storage/accounted_layout.hpp), [include/crown/storage/layout.hpp](../../../../../include/crown/storage/layout.hpp), [include/crown/storage/tuple_values.hpp](../../../../../include/crown/storage/tuple_values.hpp), [tests/support/index_allocation.hpp](../../../../../tests/support/index_allocation.hpp), [tests/unit/public_tuple_memory_test.cpp](../../../../../tests/unit/public_tuple_memory_test.cpp) |

## B0006

[Lines 28–32](../../../../../tests/unit/public_tuple_memory_test.cpp#L28); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Row scalars(std::size_t length=4096) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Create the selected mixed-scalar row with two equal binary string fields. |
| inputs / outputs | length defaults to 4096; returns Row{int64 -7, 'left\0right'+length 'v' bytes, true, Date 2026-11-09, Decimal -12345678901234567890123456789012345678, same text}. |
| invariants | Both string fields carry identical bytes including an embedded NUL; the default text length is 4106 bytes. Length is a fixture input, not a maximum. |
| ownership | Returns an owning Row with owning strings. |
| failure | String/scalar/decimal construction errors propagate. |
| cost | Builds one six-field row and two equal text strings of 10+length bytes. |
| Design | [tests/unit/public_tuple_memory_test.cpp](../../../../../tests/unit/public_tuple_memory_test.cpp) |

## B0007

[Lines 33–41](../../../../../tests/unit/public_tuple_memory_test.cpp#L33); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void reconcile(const resource::MemoryAccount& account) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Reconcile account current requested usage against purpose and lifetime partitions and its configured cap. |
| inputs / outputs | MemoryAccount reference in; calls check_invariants/statistics, sums allocations/requested_bytes/payload_bytes from by_purpose and by_lifetime, and checks both sums equal current. |
| invariants | Requires current.requested_bytes&lt;=limit_bytes and peak_requested_bytes&lt;=limit_bytes. MemoryUsage requested bytes are upstream requests including account framing/alignment, not RSS or allocator usable size. |
| ownership | Account is borrowed; statistics and sums are local. |
| failure | Invariant or check mismatch propagates/throws std::runtime_error. |
| cost | Scans fixed purpose and lifetime arrays and invokes explicit account diagnostics. |
| Design | [include/crown/resource/memory.hpp](../../../../../include/crown/resource/memory.hpp), [tests/support/index_allocation.hpp](../../../../../tests/support/index_allocation.hpp), [tests/unit/public_tuple_memory_test.cpp](../../../../../tests/unit/public_tuple_memory_test.cpp) |

## B0008

[Lines 42–46](../../../../../tests/unit/public_tuple_memory_test.cpp#L42); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void controller_only(const resource::MemoryAccount& account) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Require only the account controller to remain after all tuple/view owners are released. |
| inputs / outputs | MemoryAccount reference in; calls reconcile and requires current.allocations==1 and current.requested_bytes==MemoryAccount::control_bytes(). |
| invariants | This checks current account requests, not process memory or unrelated owners. |
| ownership | Account handle is borrowed and keeps the controller available for the check. |
| failure | Any mismatch throws; no attempt to release remaining allocations is made. |
| cost | One reconciliation plus one account statistics read. |
| Design | [include/crown/resource/memory.hpp](../../../../../include/crown/resource/memory.hpp), [tests/support/index_allocation.hpp](../../../../../tests/support/index_allocation.hpp), [tests/unit/public_tuple_memory_test.cpp](../../../../../tests/unit/public_tuple_memory_test.cpp) |

## B0009

[Lines 47–52](../../../../../tests/unit/public_tuple_memory_test.cpp#L47); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
template<class F>void denied(F&& operation) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Require an account MemoryFault::limit from a callable used by tuple cap tests. |
| inputs / outputs | Callable passed as F&&; invokes the named operation parameter as an lvalue and accepts only MemoryFailure with fault()==MemoryFault::limit. |
| invariants | The helper does not std::forward the named rvalue-reference parameter and does not treat std::bad_alloc or contract faults as byte-limit denial. |
| ownership | Callable is borrowed for the duration; caught exception is not retained. |
| failure | Unexpected MemoryFailure fails through check; other exceptions propagate; successful return without denial throws std::runtime_error. |
| cost | One operation call and catch/check path; no bound on operation-internal work. |
| Design | [include/crown/resource/memory.hpp](../../../../../include/crown/resource/memory.hpp), [tests/support/index_allocation.hpp](../../../../../tests/support/index_allocation.hpp), [tests/unit/public_tuple_memory_test.cpp](../../../../../tests/unit/public_tuple_memory_test.cpp) |

## B0010

[Lines 53–105](../../../../../tests/unit/public_tuple_memory_test.cpp#L53); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void native_views() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Check immutable public Tuple values and views preserve an AccountedLayout token/account through copy, descriptor, projection, and explicit scalar export. |
| inputs / outputs | Freezes source_layout in UINT64_MAX account; creates AccountedTuple from scalars; converts with Tuple::from_accounted, checks native_view cell pointer, row/hash/layout, usage delta, copy/view/comparison/hash under zero covered C++ new calls, descriptor tuple/view, AccountedProjection over fields {1,4,5}, and scalar JSON view parity. |
| invariants | Public Tuple stays accounted under the original owner and shares the original native cell array; values/hash/layout token agree. The copy/view/comparison/hash block asserts no account delta and zero covered-new calls. Target layout and projection metadata are created before projection.apply is counted; that apply must make covered-new calls equal to the receiving-account allocation delta and at least two calls. The retained value view outlives source/layout/tuple and final release returns to controller. Claims remain limited to these descriptors/values. |
| ownership | AccountedLayout owns frozen metadata, AccountedTuple owns row bytes, public Tuple transfers the accounted payload, and TupleValuesView retains immutable payload; locals/reset order is explicit. |
| failure | Freeze, validation, projection, or export failures propagate; failed assertions throw. Zero-call checks observe the included replacement C++ new hook only. |
| cost | Creates three six-field payloads (initial accounted input, descriptor.tuple and descriptor.tuple_view), transfers the initial payload into Tuple, and creates one three-field projected tuple. Also builds source/target/projection metadata, performs copy/view checks and six pairs of scalar JSON encodings (twelve encoding calls), plus account diagnostics. |
| Design | [include/crown/io/document.hpp](../../../../../include/crown/io/document.hpp), [include/crown/resource/memory.hpp](../../../../../include/crown/resource/memory.hpp), [include/crown/storage/accounted_layout.hpp](../../../../../include/crown/storage/accounted_layout.hpp), [include/crown/storage/accounted_projection.hpp](../../../../../include/crown/storage/accounted_projection.hpp), [include/crown/storage/layout.hpp](../../../../../include/crown/storage/layout.hpp), [include/crown/storage/tuple_values.hpp](../../../../../include/crown/storage/tuple_values.hpp), [tests/support/index_allocation.hpp](../../../../../tests/support/index_allocation.hpp), [tests/unit/public_tuple_memory_test.cpp](../../../../../tests/unit/public_tuple_memory_test.cpp) |

## B0011

[Lines 106–148](../../../../../tests/unit/public_tuple_memory_test.cpp#L106); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void limits_and_failures() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Measure a finite accounted tuple peak and test exact/one-under admission plus selected persistent allocation-failure retries. |
| inputs / outputs | Builds source layout and default scalar row; measures peak in UINT64_MAX account, admits at exactly peak, rejects tuple creation at peak-1 without changing current, retries scalars(1), then injects fail positions 0..31 around descriptor.tuple on fresh accounts. |
| invariants | Exact observed peak is admitted; one-under denial leaves pre-call current unchanged and the smaller row uses the same peak-1 limit. In the failure sweep, std::bad_alloc points leave current unchanged and same-input retry succeeds; loop requires a non-failing point and at least two failures. This is a finite tuple fixture and selected replacement-new positions, not a general max. |
| ownership | Each account/layout/tuple is scoped per route; account handle permits final controller-only checks. |
| failure | denied() accepts only MemoryFault::limit; injected bad_alloc is caught only in the sweep; other failures propagate. |
| cost | One peak calibration, exact and one-under cases, then at most 32 fresh accounts with one injected tuple and optional retry each. |
| Design | [include/crown/resource/memory.hpp](../../../../../include/crown/resource/memory.hpp), [include/crown/storage/accounted_layout.hpp](../../../../../include/crown/storage/accounted_layout.hpp), [include/crown/storage/layout.hpp](../../../../../include/crown/storage/layout.hpp), [include/crown/storage/tuple_values.hpp](../../../../../include/crown/storage/tuple_values.hpp), [tests/support/index_allocation.hpp](../../../../../tests/support/index_allocation.hpp), [tests/unit/public_tuple_memory_test.cpp](../../../../../tests/unit/public_tuple_memory_test.cpp) |

## B0012

[Lines 149–157](../../../../../tests/unit/public_tuple_memory_test.cpp#L149); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
PhysicalPlan query(bool indexed) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Construct the two-relation DeltaRuntime fixture plan for output transfer tests. |
| inputs / outputs | indexed flag in; returns plan for r(x:string,y:int64) joined to s(y:int64), projecting x and y, with r root and s child. |
| invariants | indexed=true selects s04_runtime::options(); plan construction does not create a runtime or execute an update. |
| ownership | Returned PhysicalPlan owns compiled data; source Catalog, Query, and FreeConnexTree are locals. |
| failure | Lowering errors propagate. |
| cost | Fixed two-table/two-node lowering. |
| Design | [include/crown/planner/lower.hpp](../../../../../include/crown/planner/lower.hpp), [include/crown/resource/memory.hpp](../../../../../include/crown/resource/memory.hpp), [include/crown/runtime/delta.hpp](../../../../../include/crown/runtime/delta.hpp), [include/crown/runtime/physical.hpp](../../../../../include/crown/runtime/physical.hpp), [include/crown/storage/accounted_layout.hpp](../../../../../include/crown/storage/accounted_layout.hpp), [include/crown/storage/layout.hpp](../../../../../include/crown/storage/layout.hpp), [include/crown/storage/tuple_values.hpp](../../../../../include/crown/storage/tuple_values.hpp), [tests/support/index_allocation.hpp](../../../../../tests/support/index_allocation.hpp), [tests/support/indexed_runtime_fixture.hpp](../../../../../tests/support/indexed_runtime_fixture.hpp), [tests/support/runtime_probe.hpp](../../../../../tests/support/runtime_probe.hpp), [tests/unit/public_tuple_memory_test.cpp](../../../../../tests/unit/public_tuple_memory_test.cpp) |

## B0013

[Lines 158–158](../../../../../tests/unit/public_tuple_memory_test.cpp#L158); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Row parent(){return {std::string("binary\0value",12)+std::string(16384,'r'),std::int64_t{42}};}
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Create a long binary parent row for spool/output retention checks. |
| inputs / outputs | No input; returns Row containing a 12-byte 'binary\0value' prefix plus 16384 'r' bytes and int64 42. |
| invariants | The string contains an embedded NUL and totals 16396 bytes; second field is the child join key. |
| ownership | Returns owning Row/string. |
| failure | String/row allocation failures propagate. |
| cost | Builds one fixed two-field row whose string field is 16396 bytes. |
| Design | [tests/unit/public_tuple_memory_test.cpp](../../../../../tests/unit/public_tuple_memory_test.cpp) |

## B0014

[Lines 159–159](../../../../../tests/unit/public_tuple_memory_test.cpp#L159); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Row child(){return {std::int64_t{42}};}
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Create the matching child row. |
| inputs / outputs | No input; returns one-field Row with int64 42. |
| invariants | The scalar matches parent()'s second field. |
| ownership | Returns owning one-scalar Row. |
| failure | No custom failure handling. |
| cost | Fixed one-field row construction. |
| Design | [tests/unit/public_tuple_memory_test.cpp](../../../../../tests/unit/public_tuple_memory_test.cpp) |

## B0015

[Lines 160–162](../../../../../tests/unit/public_tuple_memory_test.cpp#L160); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
DeltaOptions options(std::uint64_t cap=UINT64_MAX) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Create DeltaOptions with a caller-selected support memory cap. |
| inputs / outputs | cap defaults to UINT64_MAX; returns DeltaOptions with physical.support.memory_limit_bytes set to cap. |
| invariants | The default cap is the largest representable uint64 grant; admission/overflow/upstream failure rules remain active. The cap-specific routes instead pass their measured finite peak. Other DeltaOptions defaults are not changed here. |
| ownership | Returns options by value; nested configuration is copied with it. |
| failure | No custom failure handling; value construction errors propagate. |
| cost | Fixed option-object construction. |
| Design | [include/crown/runtime/delta.hpp](../../../../../include/crown/runtime/delta.hpp), [tests/unit/public_tuple_memory_test.cpp](../../../../../tests/unit/public_tuple_memory_test.cpp) |

## B0016

[Lines 163–165](../../../../../tests/unit/public_tuple_memory_test.cpp#L163); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
resource::MemoryAccount memory(DeltaRuntime& runtime) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Obtain the existing support MemoryAccount retained by a DeltaRuntime fixture through test probes. |
| inputs / outputs | DeltaRuntime reference in; RuntimeTestProbe::physical(runtime) then RuntimeTestProbe::support(...) then RuntimeTestProbe::memory_account(...) returns a shared MemoryAccount handle. |
| invariants | Returns the nested runtime's existing query account; no new account or allowance is created. |
| ownership | Runtime is borrowed; returned handle shares account control. |
| failure | Probe contract/runtime state errors propagate. |
| cost | Three test-probe calls (physical, support, memory_account), with the last returning a shared account handle; no new grant is created. |
| Design | [include/crown/resource/memory.hpp](../../../../../include/crown/resource/memory.hpp), [include/crown/runtime/delta.hpp](../../../../../include/crown/runtime/delta.hpp), [include/crown/runtime/physical.hpp](../../../../../include/crown/runtime/physical.hpp), [include/crown/storage/accounted_layout.hpp](../../../../../include/crown/storage/accounted_layout.hpp), [include/crown/storage/layout.hpp](../../../../../include/crown/storage/layout.hpp), [include/crown/storage/tuple_values.hpp](../../../../../include/crown/storage/tuple_values.hpp), [tests/support/index_allocation.hpp](../../../../../tests/support/index_allocation.hpp), [tests/support/indexed_runtime_fixture.hpp](../../../../../tests/support/indexed_runtime_fixture.hpp), [tests/support/runtime_probe.hpp](../../../../../tests/support/runtime_probe.hpp), [tests/unit/public_tuple_memory_test.cpp](../../../../../tests/unit/public_tuple_memory_test.cpp) |

## B0017

[Lines 166–190](../../../../../tests/unit/public_tuple_memory_test.cpp#L166); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void output_transfer(bool indexed) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Check no-allocation transfer of one committed SignedResult and its output view beyond DeltaRuntime lifetime. |
| inputs / outputs | indexed flag in; inserts parent, drains child update, commits under zero covered C++ new calls, calls Epoch::next, records account usage delta and retains TupleValuesView; then destroys record/epoch/runtime and later clears view. |
| invariants | Returned SignedResult::tuple must be accounted; before/after account allocation count changes by exactly one release, and DeltaMetrics::spool_bytes equals released node requested bytes plus tuple.memory_usage().requested_bytes. Commit/next/view observation makes zero covered new calls. Values remain equal to parent after epoch/facade destruction; final view release leaves only control allocation. These assertions cover one output record. |
| ownership | DeltaRuntime owns query state; Epoch and SignedResult own/retain output until reset; TupleValuesView retains immutable tuple payload after facade destruction. |
| failure | Update/capture failures propagate; assertion failures throw. The zero-call scope is the test's replacement-new hook, not a malloc or universal allocation proof. |
| cost | One parent insert, one child drain/commit, one next call and account snapshots around transfer/release. |
| Design | [include/crown/resource/memory.hpp](../../../../../include/crown/resource/memory.hpp), [include/crown/runtime/delta.hpp](../../../../../include/crown/runtime/delta.hpp), [include/crown/runtime/physical.hpp](../../../../../include/crown/runtime/physical.hpp), [include/crown/storage/accounted_layout.hpp](../../../../../include/crown/storage/accounted_layout.hpp), [include/crown/storage/layout.hpp](../../../../../include/crown/storage/layout.hpp), [include/crown/storage/tuple_values.hpp](../../../../../include/crown/storage/tuple_values.hpp), [tests/support/index_allocation.hpp](../../../../../tests/support/index_allocation.hpp), [tests/support/indexed_runtime_fixture.hpp](../../../../../tests/support/indexed_runtime_fixture.hpp), [tests/support/runtime_probe.hpp](../../../../../tests/support/runtime_probe.hpp), [tests/unit/public_tuple_memory_test.cpp](../../../../../tests/unit/public_tuple_memory_test.cpp) |

## B0018

[Lines 191–218](../../../../../tests/unit/public_tuple_memory_test.cpp#L191); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void retained_output_cap(bool indexed) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Measure a finite retained-output peak and verify a caller-held value can cause one update denial followed by same-sequence retry. |
| inputs / outputs | indexed flag in; measures a three-update DeltaRuntime peak with discarded epochs, rebuilds at that cap, retains the parent TupleValuesView from child insertion output, expects child erase at sequence 3 to be denied, clears view under zero covered C++ new calls, then retries sequence 3. |
| invariants | The denied erase must leave runtime ready and canonical_state unchanged and retained values readable. Retry must report one remaining output, commit sequence 3, and retain original account owner. Peak is one route's observed cap, not a universal maximum; the successful route is finite. |
| ownership | Runtime/account own query state; caller-held TupleValuesView extends the output bytes until explicit reset; epochs are discarded or scoped per operation. |
| failure | denied() accepts only MemoryFault::limit; retry/update errors propagate. Final controller-only assertion follows runtime destruction. |
| cost | Three calibration updates; two capped setup updates; one denied erase; one same-sequence retry; and explicit account/canonical-state diagnostics per backend. |
| Design | [include/crown/resource/memory.hpp](../../../../../include/crown/resource/memory.hpp), [include/crown/runtime/delta.hpp](../../../../../include/crown/runtime/delta.hpp), [include/crown/runtime/physical.hpp](../../../../../include/crown/runtime/physical.hpp), [include/crown/storage/accounted_layout.hpp](../../../../../include/crown/storage/accounted_layout.hpp), [include/crown/storage/layout.hpp](../../../../../include/crown/storage/layout.hpp), [include/crown/storage/tuple_values.hpp](../../../../../include/crown/storage/tuple_values.hpp), [tests/support/index_allocation.hpp](../../../../../tests/support/index_allocation.hpp), [tests/support/indexed_runtime_fixture.hpp](../../../../../tests/support/indexed_runtime_fixture.hpp), [tests/support/runtime_probe.hpp](../../../../../tests/support/runtime_probe.hpp), [tests/unit/public_tuple_memory_test.cpp](../../../../../tests/unit/public_tuple_memory_test.cpp) |

## B0019

[Lines 219–219](../../../../../tests/unit/public_tuple_memory_test.cpp#L219); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L219-L219:sha256:533f16bca7d58f44b3103b92e3485d22cfbb34bbad5ea3f3fa3b5a9dcb24ec89
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Close the recorded declaration scopes in public_tuple_memory_test.cpp: namespace (anonymous). |
| inputs / outputs | Preceding namespace, type or initializer declarations in; completed lexical boundary out. |
| invariants | Brace-opening context is recorded in root-scope-context-v1.json. These are declaration/initializer boundaries, not an independent update, validation or recovery operation. |
| ownership | Enclosing objects and borrowed fields keep their declared ownership. This punctuation creates no new owner. |
| failure | Malformed scope syntax is a compile error. Any initializer/constructor failure belongs to the enclosing object declaration. |
| cost | No separate loop, guard or engine call is introduced by the delimiter; enclosing initialization and object lifetime still have their actual costs. |
| Design | [tests/unit/public_tuple_memory_test.cpp](../../../../../tests/unit/public_tuple_memory_test.cpp), [docs/storage.md](../../../../storage.md), [docs/code_review.md](../../../../code_review.md) |

## B0020

[Lines 220–226](../../../../../tests/unit/public_tuple_memory_test.cpp#L220); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
int main() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Provide the public tuple memory test executable's no-argument entry point. |
| inputs / outputs | No arguments; runs native_views and limits_and_failures once, then output_transfer and retained_output_cap for indexed=false and true; prints status and returns 0 on success. |
| invariants | Catches std::exception, prints diagnostic to stderr, and returns 1 on failure. The source runs only the enumerated fixtures; documentation author did not execute this entry point. |
| ownership | Entry point owns helper-local runtime/account values through each call and returns no runtime result. |
| failure | Only std::exception is caught at the outer boundary; catch-path stream errors are not separately handled. |
| cost | Two shared public tuple routes plus two routes per backend; underlying peak/failure/account checks are finite to those fixtures. |
| Design | [include/crown/io/document.hpp](../../../../../include/crown/io/document.hpp), [include/crown/resource/memory.hpp](../../../../../include/crown/resource/memory.hpp), [include/crown/runtime/delta.hpp](../../../../../include/crown/runtime/delta.hpp), [include/crown/runtime/physical.hpp](../../../../../include/crown/runtime/physical.hpp), [include/crown/storage/accounted_layout.hpp](../../../../../include/crown/storage/accounted_layout.hpp), [include/crown/storage/accounted_projection.hpp](../../../../../include/crown/storage/accounted_projection.hpp), [include/crown/storage/layout.hpp](../../../../../include/crown/storage/layout.hpp), [include/crown/storage/tuple_values.hpp](../../../../../include/crown/storage/tuple_values.hpp), [tests/support/index_allocation.hpp](../../../../../tests/support/index_allocation.hpp), [tests/support/indexed_runtime_fixture.hpp](../../../../../tests/support/indexed_runtime_fixture.hpp), [tests/support/runtime_probe.hpp](../../../../../tests/support/runtime_probe.hpp), [tests/unit/public_tuple_memory_test.cpp](../../../../../tests/unit/public_tuple_memory_test.cpp) |
