# `tests/unit/typed_input_memory_test.cpp` — block usage map

[Source](../../../../../tests/unit/typed_input_memory_test.cpp) · [Source index](../../../README.md) · [Subsystem contracts](../../../subsystem_contracts.md) · [Reviewed primitives](../../../primitives.md)

Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection.

Snapshot SHA-256: `4b8d602989b04b97a7b2a1dd34f62620246bbac2b124d5281c4de0ab4173076a`. 189 lines partitioned into 17 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [tests](../../../subsystem_contracts.md#tests). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/code_review.md](../../../../code_review.md), [docs/reference_fuzz.md](../../../../reference_fuzz.md), [docs/task_ledger.md](../../../../task_ledger.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–11](../../../../../tests/unit/typed_input_memory_test.cpp#L1) | Imports dependencies; declares namespace scope; declares aliases. |  · [reviewed contract](#b0001) |
| [B0002 · 12–12](../../../../../tests/unit/typed_input_memory_test.cpp#L12) | Callable definition: void check(bool condition,std::string_view message) | calls std::runtime_error, std::string; guard void check(bool condition,std::string_view message) {if(!condition)throw std::runtime_error(std::st… · [reviewed contract](#b0002) |
| [B0003 · 13–16](../../../../../tests/unit/typed_input_memory_test.cpp#L13) | Callable definition: Catalog schema() | calls ; returns Catalog{1,{{@ ,{{@ ,ScalarType::int64},{@ ,ScalarType::string},{@ ,ScalarType::boolean}, · [reviewed contract](#b0003) |
| [B0004 · 17–19](../../../../../tests/unit/typed_input_memory_test.cpp#L17) | Callable definition: PhysicalPlan plan(bool indexed) | calls planner::lower_tree, schema, s04_runtime::options; returns planner::lower_tree(schema(),Query{{},{},{},false},FreeConnexTree{},indexed?s04_runtime::options():… · [reviewed contract](#b0004) |
| [B0005 · 20–20](../../../../../tests/unit/typed_input_memory_test.cpp#L20) | Callable definition: DeltaOptions options(std::uint64_t cap=64*1024*1024) | calls ; returns result · [reviewed contract](#b0005) |
| [B0006 · 21–24](../../../../../tests/unit/typed_input_memory_test.cpp#L21) | Callable definition: Row row(std::int64_t id,std::size_t bytes=8192) | calls std::string, Date::parse, Decimal::parse, reserve; returns result; growth reserve · [reviewed contract](#b0006) |
| [B0007 · 25–33](../../../../../tests/unit/typed_input_memory_test.cpp#L25) | Callable definition: io::TransportBatch batch(std::size_t count=13,std::size_t bytes=8192,std::uint64_t first=1) | calls emplace_back, row, std::string, io::TransportBatch; returns io::TransportBatch(std::move(input)); growth emplace_back, insert; 1 loop sites · [reviewed contract](#b0007) |
| [B0008 · 34–37](../../../../../tests/unit/typed_input_memory_test.cpp#L34) | Callable definition: void controller_only(const resource::MemoryAccount& account) | calls check_invariants, statistics, check, resource::MemoryAccount::control_bytes; guard check(usage.allocations==1 && usage.requested_bytes==resource::MemoryAccount::control_bytes(),"type… · [reviewed contract](#b0008) |
| [B0009 · 38–42](../../../../../tests/unit/typed_input_memory_test.cpp#L38) | Callable definition: void accept(io::TypedQueue& queue,DeltaRuntime& runtime) | calls peek, check, begin_view, drain; guard const auto* item=queue.peek();check(item,"typed queue lost its head");const auto* event=std::get_if… · [reviewed contract](#b0009) |
| [B0010 · 43–71](../../../../../tests/unit/typed_input_memory_test.cpp#L43) | Callable definition: void ownership_and_requests(bool indexed) | calls runtime, plan, options, account; guard check(calls==account.statistics().successful_allocations-before,"native queue constructor allocated…; growth emplace · [reviewed contract](#b0010) |
| [B0011 · 72–105](../../../../../tests/unit/typed_input_memory_test.cpp#L72) | Callable definition: void component_and_query_limits(bool indexed) | calls runtime, plan, options, queue; guard check(queue.enqueue(offered)==io::Admission::accepted,"native byte calibration failed");; 1 loop sites · [reviewed contract](#b0011) |
| [B0012 · 106–139](../../../../../tests/unit/typed_input_memory_test.cpp#L106) | Callable definition: void persistent_failures(bool indexed) | calls runtime, plan, options, account; guard if(scenario&gt;=1)check(queue.enqueue(offered)==io::Admission::accepted,"fault seed admission failed");; 2 loop sites; source comment (unverified): // Snapshot construction above is outside the injected operation. Keep its · [reviewed contract](#b0012) |
| [B0013 · 140–140](../../../../../tests/unit/typed_input_memory_test.cpp#L140) | Type/record definition: struct FailingDecimal |  · [reviewed contract](#b0013) |
| [B0014 · 141–143](../../../../../tests/unit/typed_input_memory_test.cpp#L141) | Callable definition: template&lt;class Action&gt; std::pair&lt;std::string,std::string&gt; diagnostic(Action&& action) | calls action, code, what; returns {}; {error.code(),error.what()} · [reviewed contract](#b0014) |
| [B0015 · 144–180](../../../../../tests/unit/typed_input_memory_test.cpp#L144) | Callable definition: void late_error_parity(bool indexed) | calls schema, row, std::string, pop_back; guard check(event.update.values\[0\].valueless_by_exception(),"invalid-scalar fixture did not become valuel…; growth emplace, insert; 1 loop sites; source comment (unverified): // This profile rejects even the first row by column count. Use a fresh · [reviewed contract](#b0015) |
| [B0016 · 181–181](../../../../../tests/unit/typed_input_memory_test.cpp#L181) | Closes surrounding scope/type. | source comment (unverified): // namespace · [reviewed contract](#b0016) |
| [B0017 · 182–189](../../../../../tests/unit/typed_input_memory_test.cpp#L182) | Callable definition: int main() | calls ownership_and_requests, component_and_query_limits, persistent_failures, late_error_parity; returns 1; 1 loop sites · [reviewed contract](#b0017) |

## B0001

[Lines 1–11](../../../../../tests/unit/typed_input_memory_test.cpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L1-L11:sha256:b5289152c656e405c6b77b9e2a3a922837255437b459aefe12b0515874ca7e54
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Prepare typed_input_memory_test.cpp: include "crown/runtime/session.hpp", "indexed_runtime_fixture.hpp", "index_allocation.hpp", &lt;iostream&gt;, &lt;optional&gt;, &lt;stdexcept&gt;; bind local aliases/name imports. |
| inputs / outputs | Compiler-visible dependencies, names and the recorded declarations in; declarations available to the following fixture/CLI/example definitions out. |
| invariants | Declarations are scoped to this source/header and its selected ABI. Included code has its own effects; names and editable fixture values do not confer proof, admission or publication authority. |
| ownership | Aliases/includes do not create a query owner. Pointers/references/views are non-owning. Containers own their elements, which can themselves be borrowed pointers or numeric IDs. Only documented owning shared-control handles retain controls; IDs/slot-handle values do not independently keep an arena/runtime alive. |
| failure | Missing headers, ill-formed names/types, failed static assertions or active #error directives stop compilation. No runtime rejection/rollback mechanism is implemented by aliases or function prototypes. |
| cost | Preprocessing and type/constraint instantiation cost compilation. Alias/prototype syntax does not invoke the declared operation; any included definitions keep their own initialization effects. |
| Design | [tests/unit/typed_input_memory_test.cpp](../../../../../tests/unit/typed_input_memory_test.cpp), [docs/ingestion.md](../../../../ingestion.md), [docs/code_review.md](../../../../code_review.md) |

## B0002

[Lines 12–12](../../../../../tests/unit/typed_input_memory_test.cpp#L12); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void check(bool condition,std::string_view message) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Raise a test diagnostic when a typed-input predicate is false. |
| inputs / outputs | Boolean and borrowed message in; no output. |
| invariants | True returns; false is the only translated condition. |
| ownership | Message borrowed until failure; exception owns diagnostic. |
| failure | False throws std::runtime_error; construction errors propagate. |
| cost | One predicate branch. |
| Design | [tests/unit/typed_input_memory_test.cpp § lines 12-12](../../../../../tests/unit/typed_input_memory_test.cpp) |

## B0003

[Lines 13–16](../../../../../tests/unit/typed_input_memory_test.cpp#L13); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Catalog schema() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Build the one-table five-scalar catalog used by typed events. |
| inputs / outputs | No input; Catalog input(id int64,text string,flag bool,day date,amount decimal(38,2)) out. |
| invariants | One nonnullable decimal amount with binary collation. |
| ownership | Returned catalog owns descriptors/names. |
| failure | Catalog allocation errors propagate. |
| cost | Fixed one table/five columns. |
| Design | [tests/unit/typed_input_memory_test.cpp § lines 13-16](../../../../../tests/unit/typed_input_memory_test.cpp) |

## B0004

[Lines 17–19](../../../../../tests/unit/typed_input_memory_test.cpp#L17); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
PhysicalPlan plan(bool indexed) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Lower the test catalog under reference or indexed fixture configuration. |
| inputs / outputs | Selector flag in; PhysicalPlan out. |
| invariants | Uses empty query/tree and chooses s04_runtime options only when indexed is true; the helper is a selector, not proof that a binary ran. |
| ownership | Plan owns lowered data; inputs are local. |
| failure | Lowering/allocation errors propagate. |
| cost | One fixed lowering over five columns. |
| Design | [tests/unit/typed_input_memory_test.cpp § lines 17-19](../../../../../tests/unit/typed_input_memory_test.cpp), [tests/support/indexed_runtime_fixture.hpp § lines 4-20](../../../../../tests/support/indexed_runtime_fixture.hpp), [include/crown/planner/lower.hpp § lines 1-16](../../../../../include/crown/planner/lower.hpp) |

## B0005

[Lines 20–20](../../../../../tests/unit/typed_input_memory_test.cpp#L20); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
DeltaOptions options(std::uint64_t cap=64*1024*1024) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Set the original query-account limit for typed queue fixtures. |
| inputs / outputs | Cap bytes in; DeltaOptions with support memory_limit_bytes set. |
| invariants | Other DeltaOptions fields retain defaults. |
| ownership | Returned settings are a value. |
| failure | No custom failure conversion. |
| cost | Scalar assignment. |
| Design | [tests/unit/typed_input_memory_test.cpp § lines 20-20](../../../../../tests/unit/typed_input_memory_test.cpp), [include/crown/runtime/delta.hpp § lines 1-80](../../../../../include/crown/runtime/delta.hpp) |

## B0006

[Lines 21–24](../../../../../tests/unit/typed_input_memory_test.cpp#L21); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Row row(std::int64_t id,std::size_t bytes=8192) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Create a full five-scalar typed-row fixture. |
| inputs / outputs | ID and text payload length in; owning Row out. |
| invariants | Text starts with a six-byte NUL-containing prefix followed by q bytes; date and decimal exercise native conversion; reserve(16) is caller-side spare capacity. |
| ownership | Returned ordinary Row owns its text; it is offered DTO data, not native retained queue ownership. |
| failure | String, Date/Decimal and row allocation errors propagate. |
| cost | Constructs five scalar values and text proportional to bytes. |
| Design | [tests/unit/typed_input_memory_test.cpp § lines 21-24](../../../../../tests/unit/typed_input_memory_test.cpp), [include/crown/io/batch.hpp § lines 47-64](../../../../../include/crown/io/batch.hpp) |

## B0007

[Lines 25–33](../../../../../tests/unit/typed_input_memory_test.cpp#L25); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
io::TransportBatch batch(std::size_t count=13,std::size_t bytes=8192,std::uint64_t first=1) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Build an external typed transport batch of contiguous insert events. |
| inputs / outputs | Count, row text bytes and starting sequence in; move-only TransportBatch out. |
| invariants | Each item has table 0, source name 120 s bytes, source offset equal sequence, and one row from row(); empty/count cases follow loop bounds. |
| ownership | Temporary vector and InputEvent Rows belong to caller-side batch DTO until enqueue success. |
| failure | Vector/string/TransportBatch quota or allocation failures propagate. |
| cost | O(count) row and source construction; defaults build 13 rows with 8192 q bytes each, not a native queue allocation. |
| Design | [tests/unit/typed_input_memory_test.cpp § lines 25-33](../../../../../tests/unit/typed_input_memory_test.cpp), [include/crown/io/batch.hpp § lines 27-64](../../../../../include/crown/io/batch.hpp), [src/io/batch.cpp § lines 1-85](../../../../../src/io/batch.cpp) |

## B0008

[Lines 34–37](../../../../../tests/unit/typed_input_memory_test.cpp#L34); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void controller_only(const resource::MemoryAccount& account) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Check queue/progress owners have released the original account to its control allocation. |
| inputs / outputs | Account handle in; no value out. |
| invariants | Checks invariant ledger and exact single-allocation/control_bytes remainder. |
| ownership | Account borrowed; no new account created. |
| failure | Mismatch throws test runtime_error; account checks propagate. |
| cost | One explicit account invariant scan and statistics read. |
| Design | [tests/unit/typed_input_memory_test.cpp § lines 34-37](../../../../../tests/unit/typed_input_memory_test.cpp), [include/crown/resource/memory.hpp § lines 80-142](../../../../../include/crown/resource/memory.hpp), [src/resource/memory.cpp § lines 82-104](../../../../../src/resource/memory.cpp), [docs/query_memory.md § Query memory contract, lines 19-33](../../../../query_memory.md) |

## B0009

[Lines 38–42](../../../../../tests/unit/typed_input_memory_test.cpp#L38); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void accept(io::TypedQueue& queue,DeltaRuntime& runtime) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Commit the current physical queue head and acknowledge it after engine commit. |
| inputs / outputs | TypedQueue and DeltaRuntime in; one event accepted and Epoch discarded. |
| invariants | Requires nonempty InputEventView head; drains pending Delta work, then commits and acknowledges with replacement new forbidden. |
| ownership | Queue/runtime borrowed; PendingEpoch and Epoch local. |
| failure | Missing/wrong-kind head fails through check; runtime exceptions propagate before acknowledgement. |
| cost | One head lookup, complete pending drain, commit and ack. |
| Design | [tests/unit/typed_input_memory_test.cpp § lines 38-42](../../../../../tests/unit/typed_input_memory_test.cpp), [include/crown/io/batch.hpp § lines 85-95](../../../../../include/crown/io/batch.hpp), [src/io/batch.cpp § lines 270-313](../../../../../src/io/batch.cpp), [src/runtime/delta.cpp § lines 1582-1594](../../../../../src/runtime/delta.cpp), [tests/support/index_allocation.hpp § lines 11-45](../../../../../tests/support/index_allocation.hpp) |

## B0010

[Lines 43–71](../../../../../tests/unit/typed_input_memory_test.cpp#L43); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void ownership_and_requests(bool indexed) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Check typed queue constructor/admission/head/progress allocations and retained ownership under the plan account. |
| inputs / outputs | Selector in; asserts initial queue, import, two accepted items, progress value copies, post-destruction lifetime and final release. |
| invariants | Queue constructor ordinary-new calls equal zero account-allocation delta. Admission of two rows consumes offered batch and its queue-account byte increase equals QueueStats.accounted_bytes. Peek is stable; each ack advances only one event. Progress copy makes charged allocations and stays sequence/source offset 1 after another ack; close returns seq2/offset2 and both survive runtime/queue destruction. |
| ownership | Runtime plan provides the one original account; caller TransportBatch is consumed only on accepted import. Progress values share that account and are released before controller_only. |
| failure | Any count/bytes/head/progress mismatch fails; MemoryFailure/bad_alloc and runtime errors propagate. |
| cost | One two-item enqueue, two head/commit cycles, two snapshot copies and final teardown. Account counters measure request counts/bytes, not wall-clock. |
| Design | [tests/unit/typed_input_memory_test.cpp § lines 43-71](../../../../../tests/unit/typed_input_memory_test.cpp), [tests/support/index_allocation.hpp § lines 11-45](../../../../../tests/support/index_allocation.hpp), [include/crown/io/batch.hpp § lines 67-95](../../../../../include/crown/io/batch.hpp), [src/io/batch.cpp § lines 87-184,216-248,270-325](../../../../../src/io/batch.cpp), [include/crown/io/input_progress.hpp § lines 14-80](../../../../../include/crown/io/input_progress.hpp), [src/io/input_progress.cpp § lines 45-88](../../../../../src/io/input_progress.cpp), [docs/batches_windows.md § Native typed queue admission, lines 72-91](../../../../batches_windows.md), [docs/query_memory.md § Account boundary, lines 19-55](../../../../query_memory.md) |

## B0011

[Lines 72–105](../../../../../tests/unit/typed_input_memory_test.cpp#L72); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void component_and_query_limits(bool indexed) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Test queue byte admission separately from the original query-account limit. |
| inputs / outputs | Selector in; measures one 13-item component request total and query peak, then checks exact, component one-under, query exact and query one-under cases. |
| invariants | QueueStats.accounted_bytes is calibrated from native batch/item/row/source requests; bytes-1 returns Admission::full with zero hooked new calls and caller batch/queue/account unchanged. Query peak-1 throws MemoryFailure(limit), also preserving offered batch and queue. A one-row retry is admitted/accepted at sequence 1 without replacing the original cap. |
| ownership | Each case gets a fresh DeltaRuntime and TypedQueue sharing its plan account; caller batches remain external on rejection and are emptied on accepted admission. |
| failure | Wrong Admission or MemoryFault, or any mutation on rejection, fails through check; other exceptions escape. |
| cost | Five fixed fixture cases with at most 13 input events each; exact/one-under sizes are measured from the same fixture rather than timing constants. |
| Design | [tests/unit/typed_input_memory_test.cpp § lines 72-105](../../../../../tests/unit/typed_input_memory_test.cpp), [src/io/batch.cpp § lines 216-248](../../../../../src/io/batch.cpp), [src/resource/memory.cpp § lines 82-104,192-231](../../../../../src/resource/memory.cpp), [tests/support/index_allocation.hpp § lines 11-45](../../../../../tests/support/index_allocation.hpp), [docs/batches_windows.md § Native typed queue admission, lines 72-91](../../../../batches_windows.md), [docs/query_memory.md § Query memory contract, lines 19-33](../../../../query_memory.md) |

## B0012

[Lines 106–139](../../../../../tests/unit/typed_input_memory_test.cpp#L106); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void persistent_failures(bool indexed) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Sweep replacement-new failure points for typed enqueue, head validation/progress staging, and progress value copy. |
| inputs / outputs | Selector in; for each of three scenarios requires at least one bad_alloc and a successful endpoint before 1024 positions. |
| invariants | Setup and comparison snapshots occur outside injected operation. Admission failure preserves offered count, QueueStats, accepted progress and account current; peek failure is not sticky and the same head retries; progress-copy failure leaves destination default, then copy succeeds. Account invariants hold after each point. |
| ownership | Fresh runtime/queue/batch per point. Same queue and, for enqueue, same unconsumed batch are reused for recovery; account is never replaced. |
| failure | Only std::bad_alloc is treated as injected failure; unexpected state, no failure, or no success in 1024 positions fails. |
| cost | At most 1024 new fixtures per scenario; point indexes only replacement-new attempts via test hook. This is not a global malloc or CPU bound. |
| Design | [tests/unit/typed_input_memory_test.cpp § lines 106-139](../../../../../tests/unit/typed_input_memory_test.cpp), [tests/support/index_allocation.hpp § lines 11-45](../../../../../tests/support/index_allocation.hpp), [src/io/batch.cpp § lines 216-248,270-298,315-325](../../../../../src/io/batch.cpp), [src/io/input_progress.cpp § lines 80-88](../../../../../src/io/input_progress.cpp), [docs/batches_windows.md § Native typed queue admission, lines 72-91](../../../../batches_windows.md) |

## B0013

[Lines 140–140](../../../../../tests/unit/typed_input_memory_test.cpp#L140); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct FailingDecimal {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Provide a conversion fixture that makes a variant emplacement become valueless. |
| inputs / outputs | No input; conversion operator to Decimal. |
| invariants | Conversion always throws std::bad_alloc so the enclosing variant records valueless_by_exception. |
| ownership | Stateless type; no resource ownership. |
| failure | Every conversion throws std::bad_alloc by design. |
| cost | One throwing conversion. |
| Design | [tests/unit/typed_input_memory_test.cpp § lines 140-140](../../../../../tests/unit/typed_input_memory_test.cpp) |

## B0014

[Lines 141–143](../../../../../tests/unit/typed_input_memory_test.cpp#L141); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
template<class Action> std::pair<std::string,std::string> diagnostic(Action&& action) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Capture a CROWN diagnostic as code and text for late-validation parity. |
| inputs / outputs | Action in; pair of owning strings out. |
| invariants | Catches only crown::Error; success returns empty pair; std::bad_alloc and other failures propagate. |
| ownership | Callable forwarded; result owns copied error fields. |
| failure | Only CROWN Error is normalized; other exception categories escape. |
| cost | One invocation; copies diagnostic only on error. |
| Design | [tests/unit/typed_input_memory_test.cpp § lines 141-143](../../../../../tests/unit/typed_input_memory_test.cpp), [include/crown/api/error.hpp § lines 1-16](../../../../../include/crown/api/error.hpp) |

## B0015

[Lines 144–180](../../../../../tests/unit/typed_input_memory_test.cpp#L144); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void late_error_parity(bool indexed) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Compare typed-queue head validation with public validation for eight malformed event profiles. |
| inputs / outputs | Selector in; each scenario compares exact Error code/message, queue sticky behavior and committed prefix. |
| invariants | Cases are unknown table, short row, wrong bool scalar, decimal scale, valueless variant, column limit, zero sequence, invalid operation enum. Except the column-limit precedence branch, a valid seq1 prefix is accepted before malformed seq2 is enqueued; enqueue accepts deferred malformed content, peek diagnoses it, accepted sequence stays 1, runtime canonical state stays committed and repeat peek returns input_failed. Column-limit case closes the unread prefix and tests malformed seq2 at a fresh queue head. |
| ownership | Reference event/canonical input values belong to the test; each native queue and DeltaRuntime use the plan account. The malformed offered event remains caller-owned until successful import. |
| failure | Every reference fixture must be invalid; diagnostic code/message mismatch, premature import rejection, changed accepted prefix or wrong sticky code fails. |
| cost | Eight directed scenarios per selector; each performs one reference validation and one or two queue head checks. No general mutation fuzzing/timing claim. |
| Design | [tests/unit/typed_input_memory_test.cpp § lines 144-180](../../../../../tests/unit/typed_input_memory_test.cpp), [include/crown/io/ingest.hpp § lines 75-78](../../../../../include/crown/io/ingest.hpp), [src/io/ingest.cpp § lines 392-403](../../../../../src/io/ingest.cpp), [src/io/batch.cpp § lines 216-248,270-298](../../../../../src/io/batch.cpp), [docs/batches_windows.md § Native typed queue admission, lines 82-91](../../../../batches_windows.md) |

## B0016

[Lines 181–181](../../../../../tests/unit/typed_input_memory_test.cpp#L181); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L181-L181:sha256:533f16bca7d58f44b3103b92e3485d22cfbb34bbad5ea3f3fa3b5a9dcb24ec89
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Close the recorded declaration scopes in typed_input_memory_test.cpp: namespace (anonymous). |
| inputs / outputs | Preceding namespace, type or initializer declarations in; completed lexical boundary out. |
| invariants | Brace-opening context is recorded in root-scope-context-v1.json. These are declaration/initializer boundaries, not an independent update, validation or recovery operation. |
| ownership | Enclosing objects and borrowed fields keep their declared ownership. This punctuation creates no new owner. |
| failure | Malformed scope syntax is a compile error. Any initializer/constructor failure belongs to the enclosing object declaration. |
| cost | No separate loop, guard or engine call is introduced by the delimiter; enclosing initialization and object lifetime still have their actual costs. |
| Design | [tests/unit/typed_input_memory_test.cpp](../../../../../tests/unit/typed_input_memory_test.cpp), [docs/ingestion.md](../../../../ingestion.md), [docs/code_review.md](../../../../code_review.md) |

## B0017

[Lines 182–189](../../../../../tests/unit/typed_input_memory_test.cpp#L182); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
int main() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Run typed request/limit/failure/late-diagnostic checks under both plan selectors. |
| inputs / outputs | No args; 0 on success, 1 for caught std::exception. |
| invariants | Calls four suites once for false and true. The packet records source review only and does not claim this main was executed. |
| ownership | Helper-owned runtimes/queues/batches die within each call. |
| failure | Catches std::exception, writes message and returns 1; success prints test summary. |
| cost | Two selectors; persistent sweep cap is 1024 per three scenarios, late parity has eight cases each. No CPU threshold. |
| Design | [tests/unit/typed_input_memory_test.cpp § lines 182-189](../../../../../tests/unit/typed_input_memory_test.cpp), [tests/support/indexed_runtime_fixture.hpp § lines 4-20](../../../../../tests/support/indexed_runtime_fixture.hpp) |
