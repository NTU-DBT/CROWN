# `tests/unit/owner_capture_memory_test.cpp` — block usage map

[Source](../../../../../tests/unit/owner_capture_memory_test.cpp) · [Source index](../../../README.md) · [Subsystem contracts](../../../subsystem_contracts.md) · [Reviewed primitives](../../../primitives.md)

Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection.

Snapshot SHA-256: `87a115144f2367503097226ba114b194ee4b2afd65c4268e33bf0bb5a4175377`. 190 lines partitioned into 18 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [tests](../../../subsystem_contracts.md#tests). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/code_review.md](../../../../code_review.md), [docs/reference_fuzz.md](../../../../reference_fuzz.md), [docs/task_ledger.md](../../../../task_ledger.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–12](../../../../../tests/unit/owner_capture_memory_test.cpp#L1) | Imports dependencies; declares namespace scope; declares aliases; declares values/defaults or compile-time conditions. |  · [reviewed contract](#b0001) |
| [B0002 · 13–13](../../../../../tests/unit/owner_capture_memory_test.cpp#L13) | Callable definition: void check(bool ok,std::string_view message) | calls std::runtime_error, std::string; guard void check(bool ok,std::string_view message) {if(!ok)throw std::runtime_error(std::string(message))… · [reviewed contract](#b0002) |
| [B0003 · 14–17](../../../../../tests/unit/owner_capture_memory_test.cpp#L14) | Callable definition: void controller_only(const resource::MemoryAccount& account) | calls check_invariants, statistics, check, resource::MemoryAccount::control_bytes; guard check(current.allocations==1 && current.requested_bytes==resource::MemoryAccount::control_bytes(),"… · [reviewed contract](#b0003) |
| [B0004 · 18–28](../../../../../tests/unit/owner_capture_memory_test.cpp#L18) | Callable definition: PhysicalPlan plan(bool indexed) | calls planner::lower_tree, s04_runtime::options; returns planner::lower_tree(catalog,query,tree,indexed?s04_runtime::options():PhysicalOptions{}) · [reviewed contract](#b0004) |
| [B0005 · 29–31](../../../../../tests/unit/owner_capture_memory_test.cpp#L29) | Callable definition: std::string text(std::size_t i,std::size_t width) | calls result, back; returns result · [reviewed contract](#b0005) |
| [B0006 · 32–41](../../../../../tests/unit/owner_capture_memory_test.cpp#L32) | Callable definition: Database database(std::size_t rows,std::size_t width) | calls text, insert, Date::parse, Decimal::parse; returns result; growth insert; 2 loop sites · [reviewed contract](#b0006) |
| [B0007 · 42–45](../../../../../tests/unit/owner_capture_memory_test.cpp#L42) | Callable definition: PhysicalRuntime runtime(bool indexed,std::uint64_t cap=allowance,std::size_t rows=4,std::size_t width=96) | calls PhysicalRuntime::initialize, plan, database; returns PhysicalRuntime::initialize(plan(indexed),database(rows,width),options) · [reviewed contract](#b0007) |
| [B0008 · 46–46](../../../../../tests/unit/owner_capture_memory_test.cpp#L46) | Callable definition: st::Limits limits() | calls ; returns result · [reviewed contract](#b0008) |
| [B0009 · 47–47](../../../../../tests/unit/owner_capture_memory_test.cpp#L47) | Callable definition: std::vector&lt;FieldId&gt; fields() | calls ; returns {{1},{4},{2},{3},{0},{1}} · [reviewed contract](#b0009) |
| [B0010 · 48–58](../../../../../tests/unit/owner_capture_memory_test.cpp#L48) | Callable definition: st::OwnerRequest request(const CompiledProgram& program,std::size_t repeats=1) | calls push_back, fields, indexes; returns result; growth push_back; 2 loop sites · [reviewed contract](#b0010) |
| [B0011 · 59–61](../../../../../tests/unit/owner_capture_memory_test.cpp#L59) | Callable definition: Row first_key(std::size_t width) | calls text, Decimal::parse, Date::parse; returns {s,Decimal::parse(@ ),true,Date::parse(@ ),std::int64_t{0},s} · [reviewed contract](#b0011) |
| [B0012 · 62–68](../../../../../tests/unit/owner_capture_memory_test.cpp#L62) | Callable definition: void facts(const st::OwnerCapture& value,std::size_t rows,std::size_t width) | calls check, availability, components, empty; guard check(value.availability()==st::Availability::available && !value.components().empty(),"native owne… · [reviewed contract](#b0012) |
| [B0013 · 69–82](../../../../../tests/unit/owner_capture_memory_test.cpp#L69) | Callable definition: std::uint64_t retained_blocks(const st::OwnerCapture& value) | calls components, capacity, memory_usage; returns result; 2 loop sites · [reviewed contract](#b0013) |
| [B0014 · 83–123](../../../../../tests/unit/owner_capture_memory_test.cpp#L83) | Callable definition: void requests_lifetimes_and_pending(bool indexed) | calls runtime, plan, account, request; guard check(calls&gt;0 && calls==after.successful_allocations-before.successful_allocations &&; growth emplace, insert; 1 loop sites; source comment (unverified): // Indexed reads retain no component graph, but their existing StorageOperation · [reviewed contract](#b0014) |
| [B0015 · 124–149](../../../../../tests/unit/owner_capture_memory_test.cpp#L124) | Callable definition: void caps(bool indexed,bool copying) | calls runtime, plan, account, request; guard peak=account.statistics().peak_requested_bytes;check(peak&gt;before,"owner capture cap fixture did not…; 1 loop sites · [reviewed contract](#b0015) |
| [B0016 · 150–184](../../../../../tests/unit/owner_capture_memory_test.cpp#L150) | Callable definition: void persistent_capture_and_cross_account_assignment(bool indexed) | calls runtime, plan, account, request; guard check(capture_calls&gt;0 && copy_calls&gt;0 && capture_calls&lt;4096 && copy_calls&lt;4096,"native owner failur…; 2 loop sites · [reviewed contract](#b0016) |
| [B0017 · 185–185](../../../../../tests/unit/owner_capture_memory_test.cpp#L185) | Closes surrounding scope/type. |  · [reviewed contract](#b0017) |
| [B0018 · 186–190](../../../../../tests/unit/owner_capture_memory_test.cpp#L186) | Callable definition: int main() | calls requests_lifetimes_and_pending, caps, persistent_capture_and_cross_account_assignment, what; returns 1; 1 loop sites · [reviewed contract](#b0018) |

## B0001

[Lines 1–12](../../../../../tests/unit/owner_capture_memory_test.cpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L1-L12:sha256:fbdba9cf1e3baa6cd3a480c5b6919166fdd88d1ae82c969ade60e1490eb35d29
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Prepare owner_capture_memory_test.cpp: include "owner_statistics_fixture.hpp", "indexed_runtime_fixture.hpp", "index_allocation.hpp", &lt;iostream&gt;, &lt;optional&gt;; bind local aliases/name imports; declare constant fixture data. |
| inputs / outputs | Compiler-visible dependencies, names and the recorded declarations in; declarations available to the following fixture/CLI/example definitions out. The source span lists the exact member/global names, types and initial values; initializers run when the enclosing object/program/thread is initialized. |
| invariants | Declarations are scoped to this source/header and its selected ABI. Included code has its own effects; names and editable fixture values do not confer proof, admission or publication authority. |
| ownership | Aliases/includes do not create a query owner. Pointers/references/views are non-owning. Containers own their elements, which can themselves be borrowed pointers or numeric IDs. Only documented owning shared-control handles retain controls; IDs/slot-handle values do not independently keep an arena/runtime alive. |
| failure | Missing headers, ill-formed names/types, failed static assertions or active #error directives stop compilation. No runtime rejection/rollback mechanism is implemented by aliases or function prototypes. |
| cost | Preprocessing and type/constraint instantiation cost compilation. Alias/prototype syntax does not invoke the declared operation; any included definitions keep their own initialization effects. These constexpr data are fixed fixture constants; quota literals are grants, not reserved bytes or measured peaks. |
| Design | [tests/unit/owner_capture_memory_test.cpp](../../../../../tests/unit/owner_capture_memory_test.cpp), [docs/query_memory.md](../../../../query_memory.md), [docs/code_review.md](../../../../code_review.md) |

## B0002

[Lines 13–13](../../../../../tests/unit/owner_capture_memory_test.cpp#L13); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void check(bool ok,std::string_view message) {if(!ok)throw std::runtime_error(std::string(message));}
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Throw a source-specific assertion message for a failed memory/account fixture check. |
| inputs / outputs | Boolean and message view enter; normal return or std::runtime_error exits. |
| invariants | Message bytes are copied only on the false path; successful checks do not build a diagnostic string. |
| ownership | Message is borrowed for the call; exception owns its copied what() string. |
| failure | False throws std::runtime_error; no native MemoryFailure is synthesized. |
| cost | One branch on success; failure constructs an owning diagnostic string. |
| Design | [docs/statistics.md](../../../../statistics.md), [Refactor.md](../../../../../Refactor.md) |

## B0003

[Lines 14–17](../../../../../tests/unit/owner_capture_memory_test.cpp#L14); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void controller_only(const resource::MemoryAccount& account) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Verify the query MemoryAccount is back to its charged controller only. |
| inputs / outputs | Borrowed MemoryAccount enters; invariant check and current-allocation count comparison exit. |
| invariants | Requires account invariants, exactly one live allocation, and requested bytes equal control_bytes after all capture copies are released. |
| ownership | Account is borrowed and remains owned by the plan/runtime or copied account handle; no allocation handle escapes. |
| failure | MemoryAccount invariant failures or the fixture check propagate; this is post-cleanup validation, not an allocation-time fault. |
| cost | Scans account counters and invokes its invariant checker; cost depends on current allocation history/list length. |
| Design | [docs/statistics.md](../../../../statistics.md), [Refactor.md](../../../../../Refactor.md) |

## B0004

[Lines 18–28](../../../../../tests/unit/owner_capture_memory_test.cpp#L18); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
PhysicalPlan plan(bool indexed) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Lower the typed R(x,string,bool,date,decimal) join plan with an ignored witness column and optional indexed support. |
| inputs / outputs | Indexed flag enters; owned PhysicalPlan exits. |
| invariants | Plan fields order is x,string,bool,date,decimal; witness is ignored and S contains x. Indexed mode requests S04 index options; ordinary mode uses PhysicalOptions. |
| ownership | Returned plan owns descriptors; local catalog/query/tree die after lower_tree. |
| failure | Planner/resource errors propagate before account fixture checks. |
| cost | Constructs and lowers a fixed two-node plan; no rows or capture distributions are processed. |
| Design | [docs/statistics.md](../../../../statistics.md), [Refactor.md](../../../../../Refactor.md) |

## B0005

[Lines 29–31](../../../../../tests/unit/owner_capture_memory_test.cpp#L29); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::string text(std::size_t i,std::size_t width) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Generate a native string key containing NUL and 0xff at a deterministic position. |
| inputs / outputs | Index and width enter; owning byte string exits. |
| invariants | First byte derives from index, middle byte is NUL, final byte is 0xff; contents are length-delimited and not text-normalized. |
| ownership | Returns an owning std::string; no relation row aliases its storage. |
| failure | String allocation failure propagates. |
| cost | Allocates and fills exactly width bytes. |
| Design | [docs/statistics.md](../../../../statistics.md), [Refactor.md](../../../../../Refactor.md) |

## B0006

[Lines 32–41](../../../../../tests/unit/owner_capture_memory_test.cpp#L32); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Database database(std::size_t rows,std::size_t width) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Build two typed R witnesses and a matching S key for each x. |
| inputs / outputs | Row count and string width enter; owning two-table Database exits. |
| invariants | Each x has exactly two full R rows with the same projected typed fields but distinct ignored witnesses; S has one x row; strings contain NUL/high bytes and decimal is a large exact value. |
| ownership | Database owns all rows and strings; no runtime storage or report key is borrowed. |
| failure | Value construction/allocation failure propagates. |
| cost | Constructs 3*rows rows with one width-sized string per x and repeated scalar conversions. |
| Design | [docs/statistics.md](../../../../statistics.md), [Refactor.md](../../../../../Refactor.md) |

## B0007

[Lines 42–45](../../../../../tests/unit/owner_capture_memory_test.cpp#L42); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
PhysicalRuntime runtime(bool indexed,std::uint64_t cap=allowance,std::size_t rows=4,std::size_t width=96) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Initialize physical owner runtime with selectable indexed storage, finite native cap, and observation disabled. |
| inputs / outputs | Indexed flag, account byte cap, row count, and string width enter; owning PhysicalRuntime exits. |
| invariants | Capture-transition observation is off; runtime fixture matches plan/database settings; this helper's cap applies to the query MemoryAccount. |
| ownership | Runtime owns its plan, account, and native state; returned runtime controls their lifetime. |
| failure | MemoryFailure or planner/allocator exceptions propagate from initialize. |
| cost | Builds the requested relation rows and engine state; runtime setup cost varies with rows, width, and indexed option. |
| Design | [docs/statistics.md](../../../../statistics.md), [Refactor.md](../../../../../Refactor.md) |

## B0008

[Lines 46–46](../../../../../tests/unit/owner_capture_memory_test.cpp#L46); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
st::Limits limits() {st::Limits result;result.work=8000000;result.heavy_keys=64;return result;}
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Set a large statistics work allowance and top-K cap for the memory fixture. |
| inputs / outputs | No arguments; Limits exits with work=8,000,000 and heavy_keys=64, other Limits defaults unchanged. |
| invariants | These are logical statistics scan limits, separate from the runtime's native MemoryAccount cap. |
| ownership | Returns a small value object; no runtime or account is retained. |
| failure | No expected failure path. |
| cost | Constant-size Limits construction. |
| Design | [docs/statistics.md](../../../../statistics.md), [Refactor.md](../../../../../Refactor.md) |

## B0009

[Lines 47–47](../../../../../tests/unit/owner_capture_memory_test.cpp#L47); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::vector<FieldId> fields() {return {{1},{4},{2},{3},{0},{1}};}
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Return an ordered, repeated projection used to prove the captured request is copied. |
| inputs / outputs | No arguments; fields \[1,4,2,3,0,1\] exit. |
| invariants | Field 1 repeats at the end, so field order and duplicate identity must be retained. |
| ownership | Vector owns its FieldIds and is copied into each request/component. |
| failure | Vector allocation failure propagates. |
| cost | Constructs six field IDs. |
| Design | [docs/statistics.md](../../../../statistics.md), [Refactor.md](../../../../../Refactor.md) |

## B0010

[Lines 48–58](../../../../../tests/unit/owner_capture_memory_test.cpp#L48); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
st::OwnerRequest request(const CompiledProgram& program,std::size_t repeats=1) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Build a request containing repeated source projections, occurrence, R records/S, parent-support, visible, and every admitted index. |
| inputs / outputs | Borrowed compiled program and repeat count enter; owning OwnerRequest exits. |
| invariants | Requested fields are copied; index IDs come from program.indexes(); all scopes correspond to the same actual compiled plan. |
| ownership | Request owns its vectors; program is borrowed during enumeration. |
| failure | Invalid plan index metadata would fail later validation; request vector allocation can throw. |
| cost | Adds repeat source selections, four fixed owner selections, then scans/serializes all admitted index requirements. |
| Design | [docs/statistics.md](../../../../statistics.md), [Refactor.md](../../../../../Refactor.md) |

## B0011

[Lines 59–61](../../../../../tests/unit/owner_capture_memory_test.cpp#L59); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Row first_key(std::size_t width) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Construct the expected first projected typed key, including binary string and large decimal values. |
| inputs / outputs | String width enters; owning ordered Row exits with string, Decimal, bool, date, int64, repeated string. |
| invariants | Expected key uses projection field order \[1,4,2,3,0,1\]; the same binary string occupies both positions. |
| ownership | Returned Row and strings own their values. |
| failure | Scalar/string allocation failure propagates. |
| cost | Constructs one key and two width-sized string values. |
| Design | [docs/statistics.md](../../../../statistics.md), [Refactor.md](../../../../../Refactor.md) |

## B0012

[Lines 62–68](../../../../../tests/unit/owner_capture_memory_test.cpp#L62); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void facts(const st::OwnerCapture& value,std::size_t rows,std::size_t width) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Check that the first captured source projection has exact full-row visitation and expected typed heavy key. |
| inputs / outputs | Borrowed OwnerCapture plus row count and width enter; assertion-only result exits. |
| invariants | Requires available/exact distribution, visited=2*rows, NDV=rows, exactly rows heavy keys, and first heavy key/count matching first_key/2. |
| ownership | Capture owns its report keys; helper borrows report and constructs a temporary expected key. |
| failure | Failed assertion throws; capture budget or native MemoryFailure is not caught here. |
| cost | Checks report vectors and materializes one expected typed key; no new engine scan. |
| Design | [docs/statistics.md](../../../../statistics.md), [Refactor.md](../../../../../Refactor.md) |

## B0013

[Lines 69–82](../../../../../tests/unit/owner_capture_memory_test.cpp#L69); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::uint64_t retained_blocks(const st::OwnerCapture& value) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Count native allocation blocks retained by the returned capture's component and distribution vectors/keys. |
| inputs / outputs | Borrowed OwnerCapture enters; uint64 allocation-block estimate exits. |
| invariants | Counts nonempty component/field/histogram/heavy-key capacities and each heavy Row's memory_usage().allocations; intentionally reports logical blocks, not allocator headers or spare-capacity bytes. |
| ownership | Capture remains owner of all counted buffers; helper borrows them and returns only a scalar. |
| failure | No injected failure expected; calls to memory_usage and counters are read-only. |
| cost | Linear in component, histogram, heavy-key, and key-field counts; does not allocate a report copy. |
| Design | [docs/statistics.md](../../../../statistics.md), [Refactor.md](../../../../../Refactor.md) |

## B0014

[Lines 83–123](../../../../../tests/unit/owner_capture_memory_test.cpp#L83); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void requests_lifetimes_and_pending(bool indexed) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Measure query-account allocation attribution, deep copy, private pending behavior, and release lifetime for reference and indexed owners. |
| inputs / outputs | Runs request/copy under s04_alloc::Scope count; prepares one private S insert; repeats indexed pending fail positions 0 and 1, then releases captures under fail_after=0. |
| invariants | Capture/copy request deltas match successful global-new attempts and retained_blocks; request field mutation cannot rewrite copied descriptors; pending has no components/current-byte delta; indexed pending grants use exactly two temporary new requests, reference uses zero; held capture survives runtime destruction and final release leaves controller only. |
| ownership | Held/copy captures own plan, request fields, distributions and heavy keys after runtime destruction; account handle keeps original query control alive until those values are dropped. |
| failure | s04_alloc fails covered global C++ new/new\[\] attempts; thrown bad_alloc must leave current account bytes and accepted sequence unchanged. It does not fault direct malloc/syscalls, and the successful Scope counts only covered C++ new requests. |
| cost | Runs complete captures and deep copies for both storage modes; separates native requested-byte/account statistics from the interposer's C++ new-call count; zero-new cleanup is only for those guarded release paths. |
| Design | [docs/statistics.md](../../../../statistics.md), [docs/query_memory.md](../../../../query_memory.md), [tests/support/index_allocation.hpp](../../../../../tests/support/index_allocation.hpp), [Refactor.md](../../../../../Refactor.md) |

## B0015

[Lines 124–149](../../../../../tests/unit/owner_capture_memory_test.cpp#L124); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void caps(bool indexed,bool copying) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Find exact versus one-byte-under native query cap for capture and owning copy, then retry after dropping a pin. |
| inputs / outputs | For each indexed/reference and capture/copy phase, calibrates peak requested bytes on 48 rows of 1536-byte keys, then repeats at limit=peak and peak-1. |
| invariants | Exact cap succeeds; peak-1 raises MemoryFailure(limit) with sequence/current bytes unchanged; existing report remains exact; after releasing the pin, retry succeeds without changing limit_bytes. |
| ownership | Held and pin captures own their allocations under the query account; account and runtime remain alive until each phase ends. |
| failure | Catches only native MemoryFailure with fault=limit for the one-under run; other failures propagate. This path is account-cap evidence, distinct from a global-new failure sweep. |
| cost | Builds and retains large typed projections/reports to expose peak requested bytes; byte cap is the account's requested-byte total, not process RSS or allocator overhead. |
| Design | [docs/statistics.md](../../../../statistics.md), [docs/query_memory.md](../../../../query_memory.md), [Refactor.md](../../../../../Refactor.md) |

## B0016

[Lines 150–184](../../../../../tests/unit/owner_capture_memory_test.cpp#L150); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void persistent_capture_and_cross_account_assignment(bool indexed) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Sweep persistent C++ allocation failure for source captures and cross-account copy assignment. |
| inputs / outputs | Two runtimes/accounts and a source request/capture are created; calibration counts C++ new calls; each failpoint assigns into an existing destination or captures anew. |
| invariants | Every failed point leaves both current account totals unchanged; failed assignment preserves destination facts/stamp/plan account; success allocates all capture/copy requests against source account only; no epoch changes; every cleanup succeeds with fail_after=0. |
| ownership | Source and destination report values own their payloads and account handles; after copy assignment destination retains old account on failure and source account on success. |
| failure | s04_alloc interposes global C++ new/new\[\] attempts and throws bad_alloc; direct malloc/syscalls are not counted. Failure occurs before or during a captured allocation request and strong destination guarantee is asserted. |
| cost | Per phase performs one complete calibration and a fail-after sweep through each C++ new position for both storage modes; counts are bounded below 4096 but are not byte totals or process allocation claims. |
| Design | [docs/statistics.md](../../../../statistics.md), [docs/query_memory.md](../../../../query_memory.md), [tests/support/index_allocation.hpp](../../../../../tests/support/index_allocation.hpp), [Refactor.md](../../../../../Refactor.md) |

## B0017

[Lines 185–185](../../../../../tests/unit/owner_capture_memory_test.cpp#L185); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L185-L185:sha256:412ca345ccf75bf9c0806bce695be8de808b79984251a7a54d202cf6101dd451
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Close the recorded declaration scopes in owner_capture_memory_test.cpp: namespace (anonymous). |
| inputs / outputs | Preceding namespace, type or initializer declarations in; completed lexical boundary out. |
| invariants | Brace-opening context is recorded in root-scope-context-v1.json. These are declaration/initializer boundaries, not an independent update, validation or recovery operation. |
| ownership | Enclosing objects and borrowed fields keep their declared ownership. This punctuation creates no new owner. |
| failure | Malformed scope syntax is a compile error. Any initializer/constructor failure belongs to the enclosing object declaration. |
| cost | No separate loop, guard or engine call is introduced by the delimiter; enclosing initialization and object lifetime still have their actual costs. |
| Design | [tests/unit/owner_capture_memory_test.cpp](../../../../../tests/unit/owner_capture_memory_test.cpp), [docs/query_memory.md](../../../../query_memory.md), [docs/code_review.md](../../../../code_review.md) |

## B0018

[Lines 186–190](../../../../../tests/unit/owner_capture_memory_test.cpp#L186); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
int main() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Run all capture lifetime and failure-account checks for reference and indexed storage. |
| inputs / outputs | For each storage mode, calls the request/lifetime/pending check, exact/one-under capture and copy phases, then persistent capture and cross-account assignment sweep. |
| invariants | The main is an orchestration layer; guarantees are those asserted by the four called helpers, including exact versus one-under account cap and cleanup. Compile-time assertions require a non-default, read-only OwnerCapture API. |
| ownership | All runtimes, accounts and optionals are local; captures deliberately outlive individual runtime scopes inside request/lifetime helper. |
| failure | Returns 1 after printing a caught std::exception; unexpected failure is not suppressed. |
| cost | Executes both storage configurations and all defined fault positions; no wall-clock cost or universal allocator guarantee is claimed. |
| Design | [docs/statistics.md](../../../../statistics.md), [docs/query_memory.md](../../../../query_memory.md), [tests/support/index_allocation.hpp](../../../../../tests/support/index_allocation.hpp), [Refactor.md](../../../../../Refactor.md) |
