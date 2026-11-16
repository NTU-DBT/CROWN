# `tests/unit/indexed_runtime_budget_test.cpp` — block usage map

[Source](../../../../../tests/unit/indexed_runtime_budget_test.cpp) · [Source index](../../../README.md) · [Subsystem contracts](../../../subsystem_contracts.md) · [Reviewed primitives](../../../primitives.md)

Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection.

Snapshot SHA-256: `809f9cf7bb121a7b536b9533a367dab5f9936531d1d06d71ff3a8b54b3dc4f75`. 248 lines partitioned into 20 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [tests](../../../subsystem_contracts.md#tests). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/code_review.md](../../../../code_review.md), [docs/reference_fuzz.md](../../../../reference_fuzz.md), [docs/task_ledger.md](../../../../task_ledger.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–18](../../../../../tests/unit/indexed_runtime_budget_test.cpp#L1) | Imports dependencies; declares namespace scope; declares aliases; declares values/defaults or compile-time conditions. | source comment (unverified): // Native program metadata must fit before each exact update-boundary test. · [reviewed contract](#b0001) |
| [B0002 · 19–19](../../../../../tests/unit/indexed_runtime_budget_test.cpp#L19) | Callable definition: void check(bool value,std::string_view message) | calls std::runtime_error, std::string; guard void check(bool value,std::string_view message) { if (!value) throw std::runtime_error(std::string(… · [reviewed contract](#b0002) |
| [B0003 · 20–24](../../../../../tests/unit/indexed_runtime_budget_test.cpp#L20) | Callable definition: template&lt;class F&gt; void error(std::string_view code,F operation) | calls operation, check, code, std::runtime_error; guard catch (const Error& failure) { check(failure.code()==code,"wrong runtime rejection code");return; } · [reviewed contract](#b0003) |
| [B0004 · 25–27](../../../../../tests/unit/indexed_runtime_budget_test.cpp#L25) | Callable definition: RuntimeStorageWork observed(const auto& runtime) | calls RuntimeTestProbe::index_work, check, has_value; guard const auto value=RuntimeTestProbe::index_work(runtime);check(value.has_value(),"actual runtime has …; returns *value · [reviewed contract](#b0004) |
| [B0005 · 28–30](../../../../../tests/unit/indexed_runtime_budget_test.cpp#L28) | declares values/defaults or compile-time conditions. |  · [reviewed contract](#b0005) |
| [B0006 · 31–31](../../../../../tests/unit/indexed_runtime_budget_test.cpp#L31) | Callable definition: storage::IndexWork generous() | calls s04_runtime::options; returns s04_runtime::options().indexed_storage-&gt;per_operation · [reviewed contract](#b0006) |
| [B0007 · 32–41](../../../../../tests/unit/indexed_runtime_budget_test.cpp#L32) | Callable definition: PhysicalPlan plan(storage::IndexWork limit=generous()) | calls generous, s04_runtime::options, planner::lower_tree; returns planner::lower_tree(catalog,query,tree,options) · [reviewed contract](#b0007) |
| [B0008 · 42–45](../../../../../tests/unit/indexed_runtime_budget_test.cpp#L42) | Callable definition: Row parent_row(std::size_t value) | calls std::string, std::to_string, append, std::move; returns {std::move(key),std::int64_t{42}} · [reviewed contract](#b0008) |
| [B0009 · 46–46](../../../../../tests/unit/indexed_runtime_budget_test.cpp#L46) | Callable definition: PhysicalSetUpdate crossing() | calls ; returns {population+1,TableId{1},SetOperation::insert,{std::int64_t{42}}}; growth insert · [reviewed contract](#b0009) |
| [B0010 · 47–58](../../../../../tests/unit/indexed_runtime_budget_test.cpp#L47) | Callable definition: storage::IndexWork populate(auto& runtime) | calls observed, apply, parent_row, check; guard check(work.fresh_operations==before+1,"one physical input minted more than one storage allowance");; returns largest; growth insert; 2 loop sites · [reviewed contract](#b0010) |
| [B0011 · 59–59](../../../../../tests/unit/indexed_runtime_budget_test.cpp#L59) | Type/record definition: struct SavedHandles |  · [reviewed contract](#b0011) |
| [B0012 · 60–69](../../../../../tests/unit/indexed_runtime_budget_test.cpp#L60) | Callable definition: SavedHandles save_handles(const PhysicalRuntime& runtime) | calls parent_row, find_source, find_support, check; guard check(source && support,"literal pre-update source/support record is absent");; returns saved; growth push_back; 1 loop sites · [reviewed contract](#b0012) |
| [B0013 · 70–95](../../../../../tests/unit/indexed_runtime_budget_test.cpp#L70) | Callable definition: void unchanged(PhysicalRuntime& runtime,const SavedHandles& before,PhysicalStorageStatistics arenas) | calls check, ready, sequence, committed_state_gauges; guard check(runtime.ready() && runtime.sequence()==population,"failed aggregate work changed publication …; 1 loop sites; source comment (unverified): // A bulk diagnostic snapshot has its own aggregate cost and can exceed a · [reviewed contract](#b0013) |
| [B0014 · 96–122](../../../../../tests/unit/indexed_runtime_budget_test.cpp#L96) | Callable definition: void physical_exact_and_one_under() | calls reference, plan, check, observed; guard PhysicalRuntime reference(plan());check(observed(reference).fresh_operations==1,"constructor minted…; 2 loop sites · [reviewed contract](#b0014) |
| [B0015 · 123–151](../../../../../tests/unit/indexed_runtime_budget_test.cpp#L123) | Callable definition: void delta_and_cursor_retention() | calls runtime, plan, check, observed; guard DeltaRuntime runtime(plan(),options);check(observed(runtime).fresh_operations==1,"delta bootstrap r…; growth emplace; 2 loop sites · [reviewed contract](#b0015) |
| [B0016 · 152–169](../../../../../tests/unit/indexed_runtime_budget_test.cpp#L152) | Callable definition: void actual_source_capacity() | calls s04_runtime::options, planner::lower_tree, runtime, apply; guard check(runtime.sequence()==1 && state.physical.tables\[0\]==Relation{Row{std::int64_t{1},std::string("…; growth insert · [reviewed contract](#b0016) |
| [B0017 · 170–195](../../../../../tests/unit/indexed_runtime_budget_test.cpp#L170) | Callable definition: void capture_and_large_exact_annotation() | calls runtime, plan, populate, apply; guard check(observed(runtime).fresh_operations==before+1 && captured.availability()==stats::Availability:…; growth insert · [reviewed contract](#b0017) |
| [B0018 · 196–241](../../../../../tests/unit/indexed_runtime_budget_test.cpp#L196) | Callable definition: void persistent_allocation_rollback() | calls apply, parent_row, baseline, plan; guard check(allocations&gt;20 && allocations&lt;2000,"persistent runtime fault coverage changed unexpectedly");; growth insert; 4 loop sites; source comment (unverified): // These metadata reads allocate nothing while denial remains active. · [reviewed contract](#b0018) |
| [B0019 · 242–242](../../../../../tests/unit/indexed_runtime_budget_test.cpp#L242) | Closes surrounding scope/type. | source comment (unverified): // namespace · [reviewed contract](#b0019) |
| [B0020 · 243–248](../../../../../tests/unit/indexed_runtime_budget_test.cpp#L243) | Callable definition: int main() | calls physical_exact_and_one_under, delta_and_cursor_retention, actual_source_capacity, capture_and_large_exact_annotation · [reviewed contract](#b0020) |

## B0001

[Lines 1–18](../../../../../tests/unit/indexed_runtime_budget_test.cpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L1-L18:sha256:99382200064815f26ec827aa253ba9b598924a47869845d92cc6f760143d20bb
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Prepare indexed_runtime_budget_test.cpp: include "indexed_runtime_fixture.hpp", "runtime_probe.hpp", "index_allocation.hpp", "crown/runtime/owner_statistics.hpp", &lt;algorithm&gt;, &lt;array&gt;, &lt;iostream&gt;, &lt;stdexcept&gt;, &lt;string_view&gt;; bind local aliases/name imports; declare constant fixture data. |
| inputs / outputs | Compiler-visible dependencies, names and the recorded declarations in; declarations available to the following fixture/CLI/example definitions out. The source span lists the exact member/global names, types and initial values; initializers run when the enclosing object/program/thread is initialized. |
| invariants | Declarations are scoped to this source/header and its selected ABI. Included code has its own effects; names and editable fixture values do not confer proof, admission or publication authority. |
| ownership | Aliases/includes do not create a query owner. Pointers/references/views are non-owning. Containers own their elements, which can themselves be borrowed pointers or numeric IDs. Only documented owning shared-control handles retain controls; IDs/slot-handle values do not independently keep an arena/runtime alive. |
| failure | Missing headers, ill-formed names/types, failed static assertions or active #error directives stop compilation. No runtime rejection/rollback mechanism is implemented by aliases or function prototypes. |
| cost | Preprocessing and type/constraint instantiation cost compilation. Alias/prototype syntax does not invoke the declared operation; any included definitions keep their own initialization effects. These constexpr data are fixed fixture constants; quota literals are grants, not reserved bytes or measured peaks. |
| Design | [tests/unit/indexed_runtime_budget_test.cpp](../../../../../tests/unit/indexed_runtime_budget_test.cpp), [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/code_review.md](../../../../code_review.md) |

## B0002

[Lines 19–19](../../../../../tests/unit/indexed_runtime_budget_test.cpp#L19); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void check(bool value,std::string_view message) { if (!value) throw std::runtime_error(std::string(message)); }
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Provide assertion handling for the actual runtime work-budget test. |
| inputs / outputs | Checks a boolean and throws runtime_error with copied message only when false. |
| invariants | Successful checks do not construct failure diagnostics; message is not query-account storage. |
| ownership | Owns no runtime state. |
| failure | Assertion failure throws; diagnostic allocation may itself fail. |
| cost | One conditional branch; failure-only text/exception work. |
| Design | [tests/unit/indexed_runtime_budget_test.cpp](../../../../../tests/unit/indexed_runtime_budget_test.cpp) |

## B0003

[Lines 20–24](../../../../../tests/unit/indexed_runtime_budget_test.cpp#L20); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
template<class F> void error(std::string_view code,F operation) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Require one exact public Error code. |
| inputs / outputs | Invokes the named callable as an lvalue and accepts Error only if code()==requested code. |
| invariants | Does not accept IndexFailure directly or other Error categories. |
| ownership | F is passed by value into the helper parameter (copying or moving the callable as the call requires) and invoked synchronously from that local parameter. |
| failure | Wrong Error or success throws runtime_error; unrelated exceptions propagate. |
| cost | One operation plus catch/check; delegated work dominates. |
| Design | [tests/unit/indexed_runtime_budget_test.cpp](../../../../../tests/unit/indexed_runtime_budget_test.cpp), [docs/indexed_storage.md](../../../../indexed_storage.md) |

## B0004

[Lines 25–27](../../../../../tests/unit/indexed_runtime_budget_test.cpp#L25); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
RuntimeStorageWork observed(const auto& runtime) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Read the active runtime’s test-only indexed work limit, consumption and fresh-operation counter. |
| inputs / outputs | Calls RuntimeTestProbe::index_work and returns its RuntimeStorageWork value after requiring it exists. |
| invariants | The result is a five-domain work diagnostic, not bytes, allocation count or CPU time; a reference runtime returns no indexed context. |
| ownership | Copies scalar diagnostics; runtime owns the actual work lease. |
| failure | Missing context throws through check. |
| cost | One private-state probe and small struct copy. |
| Design | [tests/unit/indexed_runtime_budget_test.cpp](../../../../../tests/unit/indexed_runtime_budget_test.cpp), [tests/support/runtime_probe.hpp](../../../../../tests/support/runtime_probe.hpp), [include/crown/runtime/physical.hpp](../../../../../include/crown/runtime/physical.hpp), [src/runtime/physical.cpp](../../../../../src/runtime/physical.cpp), [include/crown/runtime/support.hpp](../../../../../include/crown/runtime/support.hpp), [src/runtime/support.cpp](../../../../../src/runtime/support.cpp), [include/crown/runtime/delta.hpp](../../../../../include/crown/runtime/delta.hpp), [src/runtime/delta.cpp](../../../../../src/runtime/delta.cpp), [include/crown/storage/index_work.hpp](../../../../../include/crown/storage/index_work.hpp), [src/runtime/storage_work.hpp](../../../../../src/runtime/storage_work.hpp), [docs/indexed_storage.md](../../../../indexed_storage.md) |

## B0005

[Lines 28–30](../../../../../tests/unit/indexed_runtime_budget_test.cpp#L28); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L28-L30:sha256:3403a2c30f68341435d75575309684305759f35f58bff58afdbfd36fa73a1cdc
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Prepare indexed_runtime_budget_test.cpp: declare constant fixture data. |
| inputs / outputs | Compiler-visible dependencies, names and the recorded declarations in; declarations available to the following fixture/CLI/example definitions out. The source span lists the exact member/global names, types and initial values; initializers run when the enclosing object/program/thread is initialized. |
| invariants | Declarations are scoped to this source/header and its selected ABI. Included code has its own effects; names and editable fixture values do not confer proof, admission or publication authority. |
| ownership | Aliases/includes do not create a query owner. Pointers/references/views are non-owning. Containers own their elements, which can themselves be borrowed pointers or numeric IDs. Only documented owning shared-control handles retain controls; IDs/slot-handle values do not independently keep an arena/runtime alive. |
| failure | Missing headers, ill-formed names/types, failed static assertions or active #error directives stop compilation. No runtime rejection/rollback mechanism is implemented by aliases or function prototypes. |
| cost | Preprocessing and type/constraint instantiation cost compilation. Alias/prototype syntax does not invoke the declared operation; any included definitions keep their own initialization effects. These constexpr data are fixed fixture constants; quota literals are grants, not reserved bytes or measured peaks. |
| Design | [tests/unit/indexed_runtime_budget_test.cpp](../../../../../tests/unit/indexed_runtime_budget_test.cpp), [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/code_review.md](../../../../code_review.md) |

## B0006

[Lines 31–31](../../../../../tests/unit/indexed_runtime_budget_test.cpp#L31); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
storage::IndexWork generous() { return s04_runtime::options().indexed_storage->per_operation; }
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Read the generous per-operation grant from the indexed runtime fixture. |
| inputs / outputs | Returns s04_runtime options indexed_storage.per_operation. |
| invariants | Fields are structural_steps, scalar_fields, scalar_bytes, pointer_slots and link_actions; these component counts are neither query bytes nor elapsed time. |
| ownership | Returns a value IndexWork vector. |
| failure | Fixture assumes indexed_storage exists. |
| cost | Copies five scalar dimensions. |
| Design | [tests/unit/indexed_runtime_budget_test.cpp](../../../../../tests/unit/indexed_runtime_budget_test.cpp), [tests/support/indexed_runtime_fixture.hpp](../../../../../tests/support/indexed_runtime_fixture.hpp), [include/crown/storage/index_work.hpp](../../../../../include/crown/storage/index_work.hpp), [docs/indexed_storage.md](../../../../indexed_storage.md) |

## B0007

[Lines 32–41](../../../../../tests/unit/indexed_runtime_budget_test.cpp#L32); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
PhysicalPlan plan(storage::IndexWork limit=generous()) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Compile the R/S indexed test plan with one caller-supplied aggregate operation grant. |
| inputs / outputs | Defines R(x:string,y:int64), S(y:int64), joins on y and projects x; writes limit into per_operation before lowering. |
| invariants | The five-dimensional IndexWork vector is a single budget consumed by one outer operation and shared through nested/resumed work; per-table capacities and query-account bytes are separate. |
| ownership | Returns PhysicalPlan; local catalog/query/tree are inputs. |
| failure | Planner lowering/allocation errors propagate. |
| cost | One fixed plan lowering; runtime work later consumes the configured vector. |
| Design | [tests/unit/indexed_runtime_budget_test.cpp](../../../../../tests/unit/indexed_runtime_budget_test.cpp), [tests/support/indexed_runtime_fixture.hpp](../../../../../tests/support/indexed_runtime_fixture.hpp), [include/crown/planner/lower.hpp](../../../../../include/crown/planner/lower.hpp), [include/crown/storage/index_work.hpp](../../../../../include/crown/storage/index_work.hpp), [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0008

[Lines 42–45](../../../../../tests/unit/indexed_runtime_budget_test.cpp#L42); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Row parent_row(std::size_t value) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Create a wide binary parent row for source/support rollback checks. |
| inputs / outputs | Returns row key "row-"+decimal value+96 x bytes+0x00,0xff and int64 42. |
| invariants | append length 2 retains both trailing bytes. |
| ownership | Ordinary Row/string input; runtime takes its funded copy. |
| failure | String allocation failures propagate. |
| cost | O(96+digits(value)) content construction outside query-account reporting. |
| Design | [tests/unit/indexed_runtime_budget_test.cpp](../../../../../tests/unit/indexed_runtime_budget_test.cpp) |

## B0009

[Lines 46–46](../../../../../tests/unit/indexed_runtime_budget_test.cpp#L46); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
PhysicalSetUpdate crossing() { return {population+1,TableId{1},SetOperation::insert,{std::int64_t{42}}}; }
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Create child insert at the first sequence after 48 parent rows. |
| inputs / outputs | Returns table-1 insert, sequence population+1 (=49), tuple {42}. |
| invariants | Its separator matches all populated parent rows. |
| ownership | Ordinary update value held by caller until runtime admission. |
| failure | Runtime error is checked by caller. |
| cost | Small scalar/update construction; resulting fanout drives runtime work. |
| Design | [tests/unit/indexed_runtime_budget_test.cpp](../../../../../tests/unit/indexed_runtime_budget_test.cpp) |

## B0010

[Lines 47–58](../../../../../tests/unit/indexed_runtime_budget_test.cpp#L47); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
storage::IndexWork populate(auto& runtime) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Populate 48 parent rows and record the componentwise maximum consumed work. |
| inputs / outputs | Applies inserts to table 0 at sequences 1..48, checks fresh_operations rises exactly once per input, and takes maxima across the five consumed fields (including initial consumption). |
| invariants | There is one fresh outer operation per input; each field is tracked separately. Delta Epoch outputs are discarded if the return type supports discard(). |
| ownership | Runtime owns inserted rows; return IndexWork is diagnostic scalar state. |
| failure | Wrong operation count or update failure throws. |
| cost | 48 fresh update operations and counter reads; each input includes a wide row. No bytes/CPU are measured. |
| Design | [tests/unit/indexed_runtime_budget_test.cpp](../../../../../tests/unit/indexed_runtime_budget_test.cpp), [tests/support/indexed_runtime_fixture.hpp](../../../../../tests/support/indexed_runtime_fixture.hpp), [tests/support/runtime_probe.hpp](../../../../../tests/support/runtime_probe.hpp), [include/crown/runtime/physical.hpp](../../../../../include/crown/runtime/physical.hpp), [src/runtime/physical.cpp](../../../../../src/runtime/physical.cpp), [include/crown/runtime/delta.hpp](../../../../../include/crown/runtime/delta.hpp), [src/runtime/delta.cpp](../../../../../src/runtime/delta.cpp), [include/crown/storage/index_work.hpp](../../../../../include/crown/storage/index_work.hpp), [src/runtime/storage_work.hpp](../../../../../src/runtime/storage_work.hpp), [docs/indexed_storage.md](../../../../indexed_storage.md) |

## B0011

[Lines 59–59](../../../../../tests/unit/indexed_runtime_budget_test.cpp#L59); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct SavedHandles { std::vector<TupleHandle> source;std::vector<SupportHandle> support; };
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Define the test’s saved source/support handles. |
| inputs / outputs | Two ordinary std::vector fields hold TupleHandle and SupportHandle values. |
| invariants | Vectors hold IDs, not tuple payload copies or MemoryAccount pins. |
| ownership | SavedHandles owns test-side vector allocations; runtime owns referenced records. |
| failure | No custom failure path. |
| cost | Plain record declaration; vector costs occur when populated. |
| Design | [tests/unit/indexed_runtime_budget_test.cpp](../../../../../tests/unit/indexed_runtime_budget_test.cpp), [tests/support/runtime_probe.hpp](../../../../../tests/support/runtime_probe.hpp), [include/crown/runtime/physical.hpp](../../../../../include/crown/runtime/physical.hpp), [src/runtime/physical.cpp](../../../../../src/runtime/physical.cpp), [include/crown/runtime/support.hpp](../../../../../include/crown/runtime/support.hpp), [src/runtime/support.cpp](../../../../../src/runtime/support.cpp) |

## B0012

[Lines 60–69](../../../../../tests/unit/indexed_runtime_budget_test.cpp#L60); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
SavedHandles save_handles(const PhysicalRuntime& runtime) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Capture handles for all pre-update source and support rows. |
| inputs / outputs | Looks up each of the 48 parent rows in table 0 and node 0 records and stores both handles. |
| invariants | Every lookup must find a valid stable handle before the crossing attempt. |
| ownership | Runtime retains tuple/support payloads; SavedHandles retains only handles in ordinary test vectors. |
| failure | Absent source/support row fails check. |
| cost | 48 source and 48 support lookups plus two test-side vector growth sequences. |
| Design | [tests/unit/indexed_runtime_budget_test.cpp](../../../../../tests/unit/indexed_runtime_budget_test.cpp), [tests/support/runtime_probe.hpp](../../../../../tests/support/runtime_probe.hpp), [include/crown/runtime/physical.hpp](../../../../../include/crown/runtime/physical.hpp), [src/runtime/physical.cpp](../../../../../src/runtime/physical.cpp), [include/crown/runtime/support.hpp](../../../../../include/crown/runtime/support.hpp), [src/runtime/support.cpp](../../../../../src/runtime/support.cpp) |

## B0013

[Lines 70–95](../../../../../tests/unit/indexed_runtime_budget_test.cpp#L70); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void unchanged(PhysicalRuntime& runtime,const SavedHandles& before,PhysicalStorageStatistics arenas) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Verify a denied crossing preserved prior rows, support metadata and storage counts. |
| inputs / outputs | Checks ready/sequence 48, committed cardinality gauges, then reads every saved source/support handle and compares row values, member/satisfied/child flags, live-record/pin/retained counts. |
| invariants | Does not bulk-snapshot the runtime because that diagnostic can exceed a grant. It does not compare whole query-account current bytes; checked storage fields are the enumerated source/support arena counts. Point reads/metadata probes are separate calls with their own outer operation grants. |
| ownership | Runtime owns source/support records; SavedHandles retains only IDs and PhysicalStorageStatistics is a scalar diagnostic snapshot. This helper avoids bulk PhysicalRuntime::snapshot materialization; \`unchanged\` checks prior rows through bounded point reads. |
| failure | Any changed cardinality, values, metadata or enumerated storage counter throws. |
| cost | One gauge read plus 48 source/support point pairs and metadata reads; constructs 48 expected wide rows. Point reads are separate funded operations. |
| Design | [tests/unit/indexed_runtime_budget_test.cpp](../../../../../tests/unit/indexed_runtime_budget_test.cpp), [tests/support/runtime_probe.hpp](../../../../../tests/support/runtime_probe.hpp), [include/crown/runtime/physical.hpp](../../../../../include/crown/runtime/physical.hpp), [src/runtime/physical.cpp](../../../../../src/runtime/physical.cpp), [include/crown/runtime/support.hpp](../../../../../include/crown/runtime/support.hpp), [src/runtime/support.cpp](../../../../../src/runtime/support.cpp), [include/crown/storage/index_work.hpp](../../../../../include/crown/storage/index_work.hpp), [src/runtime/storage_work.hpp](../../../../../src/runtime/storage_work.hpp), [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0014

[Lines 96–122](../../../../../tests/unit/indexed_runtime_budget_test.cpp#L96); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void physical_exact_and_one_under() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Measure the exact five-domain PhysicalRuntime crossing grant and five one-domain-under failures. |
| inputs / outputs | A generous indexed runtime is populated, then child insert measures exact consumed IndexWork. The exact vector is replayed; five more runtimes decrement one vector field each and expect storage_work_limit. |
| invariants | The local variable named reference is still indexed (\`plan()\` default). The same five-dimensional vector is the grant; each one-under changes one field only. Denial preserves state/handles and mints only the failed outer operation. Repair is not retrying the identical update: it does a no-op child erase at 49, deletes one parent at 50, then retries child insert at 51 (47-way fanout). |
| ownership | Each runtime owns its query account and source/support records. SavedHandles stores test-side IDs; PhysicalStorageStatistics stores scalar arena diagnostics. The rollback check deliberately uses point reads instead of a bulk runtime snapshot. |
| failure | Only public storage_work_limit is accepted; changed state or grant refill fails. |
| cost | Seven PhysicalRuntime instances: measurement, exact replay, five under-grant cases. Each populates 48 rows; under cases also fail once, run repair operations and perform separately funded point diagnostics. |
| Design | [tests/unit/indexed_runtime_budget_test.cpp](../../../../../tests/unit/indexed_runtime_budget_test.cpp), [tests/support/indexed_runtime_fixture.hpp](../../../../../tests/support/indexed_runtime_fixture.hpp), [tests/support/runtime_probe.hpp](../../../../../tests/support/runtime_probe.hpp), [include/crown/runtime/physical.hpp](../../../../../include/crown/runtime/physical.hpp), [src/runtime/physical.cpp](../../../../../src/runtime/physical.cpp), [include/crown/runtime/support.hpp](../../../../../include/crown/runtime/support.hpp), [src/runtime/support.cpp](../../../../../src/runtime/support.cpp), [include/crown/runtime/delta.hpp](../../../../../include/crown/runtime/delta.hpp), [src/runtime/delta.cpp](../../../../../src/runtime/delta.cpp), [include/crown/storage/index_work.hpp](../../../../../include/crown/storage/index_work.hpp), [src/runtime/storage_work.hpp](../../../../../src/runtime/storage_work.hpp), [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0015

[Lines 123–151](../../../../../tests/unit/indexed_runtime_budget_test.cpp#L123); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void delta_and_cursor_retention() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Verify one grant spans Delta begin/resumed steps/commit, one whole cursor and rebuild. |
| inputs / outputs | Populates indexed DeltaRuntime with 48 parents, begins a crossing update, steps until prepared, commits under the zero-covered-new scope, discards the returned Epoch without asserting its record count, traverses core_results, then rebuilds. |
| invariants | One outer Delta operation creates the five-domain grant; repeated step and commit reuse it without refill. Cursor traversal has one separate grant for next/EOF; rebuild consumes one source-capture grant and rebuilt target has its own initialization/bootstrap grant. Zero-new scope observes replacement-new only. |
| ownership | PendingEpoch and cursor retain the active lease over their respective lifetimes; rebuilt runtime owns target state/context. |
| failure | Wrong fresh-operation count, step termination or row count fails; runtime errors propagate. |
| cost | Per invocation: 48 setup updates, one crossing/resume sequence, one prepared commit and output discard (returned Epoch cardinality is not asserted), one 48-row-plus-EOF core cursor, an invariant check and one rebuild. Diagnostic setup grants are separate from these long operations. |
| Design | [tests/unit/indexed_runtime_budget_test.cpp](../../../../../tests/unit/indexed_runtime_budget_test.cpp), [tests/support/indexed_runtime_fixture.hpp](../../../../../tests/support/indexed_runtime_fixture.hpp), [tests/support/runtime_probe.hpp](../../../../../tests/support/runtime_probe.hpp), [tests/support/index_allocation.hpp](../../../../../tests/support/index_allocation.hpp), [include/crown/runtime/delta.hpp](../../../../../include/crown/runtime/delta.hpp), [src/runtime/delta.cpp](../../../../../src/runtime/delta.cpp), [include/crown/runtime/physical.hpp](../../../../../include/crown/runtime/physical.hpp), [src/runtime/physical.cpp](../../../../../src/runtime/physical.cpp), [include/crown/runtime/support.hpp](../../../../../include/crown/runtime/support.hpp), [src/runtime/support.cpp](../../../../../src/runtime/support.cpp), [include/crown/storage/index_work.hpp](../../../../../include/crown/storage/index_work.hpp), [src/runtime/storage_work.hpp](../../../../../src/runtime/storage_work.hpp), [include/crown/resource/memory.hpp](../../../../../include/crown/resource/memory.hpp), [src/resource/memory.cpp](../../../../../src/resource/memory.cpp), [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/delta_runtime.md](../../../../delta_runtime.md) |

## B0016

[Lines 152–169](../../../../../tests/unit/indexed_runtime_budget_test.cpp#L152); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void actual_source_capacity() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Distinguish table row capacity from IndexWork and query-account bytes. |
| inputs / outputs | Sets per-table row limit=1; first distinct full source row succeeds, second fails storage_capacity; repeats for SupportRuntime and checks an ordinary reference PhysicalRuntime has no indexed work context. |
| invariants | Per-table rows is an object capacity, separate from the five work domains and MemoryAccount byte limit. The physical case checks sequence, the exact prior source table and derivation count after rejection; the logical SupportRuntime case checks sequence and that one record remains, not a full row-image comparison. |
| ownership | Each runtime owns account-backed tables; exported snapshots/relations are temporary. |
| failure | Only exact storage_capacity error is accepted for the second insert. |
| cost | Three runtimes: indexed PhysicalRuntime, indexed SupportRuntime and reference PhysicalRuntime; two attempted inserts each for the indexed owners, one PhysicalRuntime snapshot and one SupportRuntime snapshot. The reference instance checks that no indexed work context exists. |
| Design | [tests/unit/indexed_runtime_budget_test.cpp](../../../../../tests/unit/indexed_runtime_budget_test.cpp), [tests/support/indexed_runtime_fixture.hpp](../../../../../tests/support/indexed_runtime_fixture.hpp), [tests/support/runtime_probe.hpp](../../../../../tests/support/runtime_probe.hpp), [include/crown/runtime/physical.hpp](../../../../../include/crown/runtime/physical.hpp), [src/runtime/physical.cpp](../../../../../src/runtime/physical.cpp), [include/crown/runtime/support.hpp](../../../../../include/crown/runtime/support.hpp), [src/runtime/support.cpp](../../../../../src/runtime/support.cpp), [include/crown/storage/index_work.hpp](../../../../../include/crown/storage/index_work.hpp), [src/runtime/storage_work.hpp](../../../../../src/runtime/storage_work.hpp), [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0017

[Lines 170–195](../../../../../tests/unit/indexed_runtime_budget_test.cpp#L170); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void capture_and_large_exact_annotation() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Check an eight-component statistics capture and exact annotation increment above 2^53. |
| inputs / outputs | After 48 parents and child crossing, captures source/occurrence/node/index scopes under one fresh operation; then test-probe seeds support count to 2^53+1, performs one real parent insert, captures updated count and restores to population+1. |
| invariants | The test requires eight returned components; component 0 is checked for source-scope ndv==1 and a first heavy-key count of 48, while component 7 is checked for a first reverse-index heavy-key count of 48. It does not assert cardinality for every component. RuntimeTestProbe directly seeds support metadata to 2^53+1 without normal propagation, one real parent update increments it exactly, and the probe restores the value to 49 before invariant checking; no huge row population is constructed. The probe setter opens a test-build StorageOperation. The initial eight-component capture is directly asserted to add exactly one fresh operation; no separate fresh-operation counts are asserted around the probe writes, real increment update or later single-scope capture. |
| ownership | Runtime owns source/support state; capture result is temporary; RuntimeTestProbe directly mutates private support metadata for this test only. |
| failure | Unavailable capture, wrong count or failed restoration throws. |
| cost | Builds 48 parents and performs one crossing, one eight-scope capture, two direct test-probe metadata writes, one parent update and one single-scope capture. The initial eight-scope capture is checked to consume exactly one fresh operation. The probe implementation opens StorageOperation, while this helper does not separately assert fresh-operation counts for the probe writes, increment update or later capture. |
| Design | [tests/unit/indexed_runtime_budget_test.cpp](../../../../../tests/unit/indexed_runtime_budget_test.cpp), [tests/support/indexed_runtime_fixture.hpp](../../../../../tests/support/indexed_runtime_fixture.hpp), [tests/support/runtime_probe.hpp](../../../../../tests/support/runtime_probe.hpp), [include/crown/runtime/physical.hpp](../../../../../include/crown/runtime/physical.hpp), [src/runtime/physical.cpp](../../../../../src/runtime/physical.cpp), [include/crown/runtime/support.hpp](../../../../../include/crown/runtime/support.hpp), [src/runtime/support.cpp](../../../../../src/runtime/support.cpp), [include/crown/storage/index_work.hpp](../../../../../include/crown/storage/index_work.hpp), [src/runtime/storage_work.hpp](../../../../../src/runtime/storage_work.hpp), [docs/indexed_storage.md](../../../../indexed_storage.md) |

## B0018

[Lines 196–241](../../../../../tests/unit/indexed_runtime_budget_test.cpp#L196); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void persistent_allocation_rollback() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Inject each calibrated C++ new failure in a physical crossing and verify rollback then retry. |
| inputs / outputs | Measures successful covered replacement-new count N for a crossing after three parent rows; for every point 0..N-1 reconstructs runtime/setup, injects bad_alloc during apply and retries unscoped. |
| invariants | N must satisfy 20&lt;N&lt;2000. Every point fails after exactly point+1 covered attempts; complete previous rows/handles, source/support arena live/pin/retained counts remain unchanged. It does not compare total query-account requested bytes. |
| ownership | Runtime owns query-funded rows; saved IDs/snapshots/test vectors are outside runtime storage. Shim counts covered operator-new attempts, not direct malloc/all allocation bytes/RSS/CPU. |
| failure | Every injected attempt must throw bad_alloc; same update retry commits sequence 4 and expected answer/support survivors. |
| cost | One successful calibration update plus N fresh runtimes with three setup rows, one faulted update, diagnostics, one retry and invariant scan per point; N dynamic. |
| Design | [tests/unit/indexed_runtime_budget_test.cpp](../../../../../tests/unit/indexed_runtime_budget_test.cpp), [tests/support/indexed_runtime_fixture.hpp](../../../../../tests/support/indexed_runtime_fixture.hpp), [tests/support/runtime_probe.hpp](../../../../../tests/support/runtime_probe.hpp), [tests/support/index_allocation.hpp](../../../../../tests/support/index_allocation.hpp), [include/crown/runtime/physical.hpp](../../../../../include/crown/runtime/physical.hpp), [src/runtime/physical.cpp](../../../../../src/runtime/physical.cpp), [include/crown/runtime/support.hpp](../../../../../include/crown/runtime/support.hpp), [src/runtime/support.cpp](../../../../../src/runtime/support.cpp), [include/crown/storage/index_work.hpp](../../../../../include/crown/storage/index_work.hpp), [src/runtime/storage_work.hpp](../../../../../src/runtime/storage_work.hpp), [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0019

[Lines 242–242](../../../../../tests/unit/indexed_runtime_budget_test.cpp#L242); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L242-L242:sha256:c7bfe2f3de133d78a2bc8bb1c4a08450563986ee8254facee698e1dcc57e8162
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Close the recorded declaration scopes in indexed_runtime_budget_test.cpp: namespace (anonymous). |
| inputs / outputs | Preceding namespace, type or initializer declarations in; completed lexical boundary out. |
| invariants | Brace-opening context is recorded in root-scope-context-v1.json. These are declaration/initializer boundaries, not an independent update, validation or recovery operation. |
| ownership | Enclosing objects and borrowed fields keep their declared ownership. This punctuation creates no new owner. |
| failure | Malformed scope syntax is a compile error. Any initializer/constructor failure belongs to the enclosing object declaration. |
| cost | No separate loop, guard or engine call is introduced by the delimiter; enclosing initialization and object lifetime still have their actual costs. |
| Design | [tests/unit/indexed_runtime_budget_test.cpp](../../../../../tests/unit/indexed_runtime_budget_test.cpp), [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/code_review.md](../../../../code_review.md) |

## B0020

[Lines 243–248](../../../../../tests/unit/indexed_runtime_budget_test.cpp#L243); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
int main() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Run the indexed runtime budget, rollback and capture scenarios. |
| inputs / outputs | Calls physical exact/under grants, Delta/cursor retention, source capacity, statistics/large annotation and persistent rollback once each. |
| invariants | Most helpers construct indexed plans; only actual_source_capacity additionally checks one default reference plan. Main has no outer try/catch: normal fallthrough returns 0; uncaught exceptions terminate/nonzero. Completion print is not execution evidence. |
| ownership | Each helper creates/releases its own runtimes; no runtime state crosses calls. |
| failure | Exceptions are uncaught in this main. |
| cost | Five helper calls; physical helper constructs seven runtimes, source-capacity three, and fault helper repeats dynamic fresh setup. No native test/build run is claimed. |
| Design | [tests/unit/indexed_runtime_budget_test.cpp](../../../../../tests/unit/indexed_runtime_budget_test.cpp), [tests/support/indexed_runtime_fixture.hpp](../../../../../tests/support/indexed_runtime_fixture.hpp), [tests/support/runtime_probe.hpp](../../../../../tests/support/runtime_probe.hpp), [tests/support/index_allocation.hpp](../../../../../tests/support/index_allocation.hpp), [include/crown/runtime/physical.hpp](../../../../../include/crown/runtime/physical.hpp), [src/runtime/physical.cpp](../../../../../src/runtime/physical.cpp), [include/crown/runtime/delta.hpp](../../../../../include/crown/runtime/delta.hpp), [src/runtime/delta.cpp](../../../../../src/runtime/delta.cpp), [include/crown/runtime/support.hpp](../../../../../include/crown/runtime/support.hpp), [src/runtime/support.cpp](../../../../../src/runtime/support.cpp), [include/crown/storage/index_work.hpp](../../../../../include/crown/storage/index_work.hpp), [src/runtime/storage_work.hpp](../../../../../src/runtime/storage_work.hpp), [include/crown/resource/memory.hpp](../../../../../include/crown/resource/memory.hpp), [src/resource/memory.cpp](../../../../../src/resource/memory.cpp), [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/query_memory.md](../../../../query_memory.md), [docs/delta_runtime.md](../../../../delta_runtime.md) |
