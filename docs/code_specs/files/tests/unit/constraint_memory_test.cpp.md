# `tests/unit/constraint_memory_test.cpp` — block usage map

[Source](../../../../../tests/unit/constraint_memory_test.cpp) · [Source index](../../../README.md) · [Subsystem contracts](../../../subsystem_contracts.md) · [Reviewed primitives](../../../primitives.md)

Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection.

Snapshot SHA-256: `956dbff6f13a99bddbc306f20be508f8ec1f8155b81a02a0a83b0bcda14fc798`. 221 lines partitioned into 16 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [tests](../../../subsystem_contracts.md#tests). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/code_review.md](../../../../code_review.md), [docs/reference_fuzz.md](../../../../reference_fuzz.md), [docs/task_ledger.md](../../../../task_ledger.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–14](../../../../../tests/unit/constraint_memory_test.cpp#L1) | Imports dependencies; declares namespace scope; declares aliases. |  · [reviewed contract](#b0001) |
| [B0002 · 15–17](../../../../../tests/unit/constraint_memory_test.cpp#L15) | Callable definition: void check(bool value,std::string_view message) | calls std::runtime_error, std::string; guard void check(bool value,std::string_view message) { · [reviewed contract](#b0002) |
| [B0003 · 18–20](../../../../../tests/unit/constraint_memory_test.cpp#L18) | Callable definition: PhysicalRuntimeOptions options(std::uint64_t cap=64*1024*1024) | calls ; returns value · [reviewed contract](#b0003) |
| [B0004 · 21–33](../../../../../tests/unit/constraint_memory_test.cpp#L21) | Callable definition: Catalog schema(bool trusted=true) | calls ; returns catalog · [reviewed contract](#b0004) |
| [B0005 · 34–36](../../../../../tests/unit/constraint_memory_test.cpp#L34) | Callable definition: PhysicalPlan plan(bool indexed,const Catalog& catalog) | calls planner::lower_tree, s04_runtime::options; returns planner::lower_tree(catalog,Query{{},{},{},false},FreeConnexTree{},indexed?s04_runtime::options():P… · [reviewed contract](#b0005) |
| [B0006 · 37–46](../../../../../tests/unit/constraint_memory_test.cpp#L37) | Callable definition: Database database(std::size_t rows=13) | calls resize, std::to_string, std::string, Date::parse; returns data; growth insert, resize; 1 loop sites · [reviewed contract](#b0006) |
| [B0007 · 47–49](../../../../../tests/unit/constraint_memory_test.cpp#L47) | Callable definition: resource::MemoryAccount memory(const PhysicalRuntime& runtime) | calls RuntimeTestProbe::memory_account, RuntimeTestProbe::support; returns RuntimeTestProbe::memory_account(RuntimeTestProbe::support(const_cast&lt;PhysicalRuntime&&gt;(runtime))) · [reviewed contract](#b0007) |
| [B0008 · 50–54](../../../../../tests/unit/constraint_memory_test.cpp#L50) | Callable definition: void controller_only(const resource::MemoryAccount& account) | calls check_invariants, statistics, check, resource::MemoryAccount::control_bytes; guard check(current.allocations==1 && current.requested_bytes==resource::MemoryAccount::control_bytes(), · [reviewed contract](#b0008) |
| [B0009 · 55–60](../../../../../tests/unit/constraint_memory_test.cpp#L55) | Callable definition: template&lt;class F&gt;void denied(F&& action) | calls action, check, fault, std::runtime_error; guard check(failure.fault()==resource::MemoryFault::limit,"unexpected native validation byte fault");retu… · [reviewed contract](#b0009) |
| [B0010 · 61–64](../../../../../tests/unit/constraint_memory_test.cpp#L61) | Callable definition: template&lt;class F&gt;auto diagnostic(F&& action) | calls action, code, std::string, what; returns std::pair&lt;std::string,std::string&gt;{}; std::pair{error.code(),std::string(error.what())} · [reviewed contract](#b0010) |
| [B0011 · 65–106](../../../../../tests/unit/constraint_memory_test.cpp#L65) | Callable definition: void semantic_and_allocation_parity(bool indexed) | calls schema, runtime, plan, options; guard check(actual==expected,"native validation changed reference error code/message/order or trust seman…; growth insert, resize; 3 loop sites · [reviewed contract](#b0011) |
| [B0012 · 107–130](../../../../../tests/unit/constraint_memory_test.cpp#L107) | Callable definition: void validator_limits(bool indexed) | calls schema, plan, database, runtime; guard check(peak&gt;setup,"constraint fixture did not exceed construction peak"); · [reviewed contract](#b0012) |
| [B0013 · 131–188](../../../../../tests/unit/constraint_memory_test.cpp#L131) | Callable definition: void update_and_rebuild(bool indexed) | calls plan, schema, database, std::string; guard check(calls==account.statistics().successful_allocations-before,; growth insert; 1 loop sites; source comment (unverified): // Caller input construction is outside the engine's allocation boundary. · [reviewed contract](#b0013) |
| [B0014 · 189–212](../../../../../tests/unit/constraint_memory_test.cpp#L189) | Callable definition: void persistent_failures(bool indexed) | calls plan, schema, database, std::string; guard ++failures;check(runtime.ready() && runtime.canonical_state()==before,"native scratch allocation fa…; growth insert; 2 loop sites · [reviewed contract](#b0014) |
| [B0015 · 213–213](../../../../../tests/unit/constraint_memory_test.cpp#L213) | Closes surrounding scope/type. | source comment (unverified): // namespace · [reviewed contract](#b0015) |
| [B0016 · 214–221](../../../../../tests/unit/constraint_memory_test.cpp#L214) | Callable definition: int main() | calls semantic_and_allocation_parity, validator_limits, update_and_rebuild, persistent_failures; returns 1; 1 loop sites · [reviewed contract](#b0016) |

## B0001

[Lines 1–14](../../../../../tests/unit/constraint_memory_test.cpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L1-L14:sha256:29d7eb64ad8539814059de8d4ad249e6e3cce87b61eb072f63faebf0277c63a4
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Prepare constraint_memory_test.cpp: include "constraint_validation.hpp", "crown/catalog/catalog.hpp", "crown/runtime/physical.hpp", "indexed_runtime_fixture.hpp", "runtime_probe.hpp", "index_allocation.hpp", &lt;iostream&gt;, &lt;optional&gt;, &lt;stdexcept&gt;; bind local aliases/name imports. |
| inputs / outputs | Compiler-visible dependencies, names and the recorded declarations in; declarations available to the following fixture/CLI/example definitions out. |
| invariants | Declarations are scoped to this source/header and its selected ABI. Included code has its own effects; names and editable fixture values do not confer proof, admission or publication authority. |
| ownership | Aliases/includes do not create a query owner. Pointers/references/views are non-owning. Containers own their elements, which can themselves be borrowed pointers or numeric IDs. Only documented owning shared-control handles retain controls; IDs/slot-handle values do not independently keep an arena/runtime alive. |
| failure | Missing headers, ill-formed names/types, failed static assertions or active #error directives stop compilation. No runtime rejection/rollback mechanism is implemented by aliases or function prototypes. |
| cost | Preprocessing and type/constraint instantiation cost compilation. Alias/prototype syntax does not invoke the declared operation; any included definitions keep their own initialization effects. |
| Design | [tests/unit/constraint_memory_test.cpp](../../../../../tests/unit/constraint_memory_test.cpp), [docs/query_memory.md](../../../../query_memory.md), [docs/code_review.md](../../../../code_review.md) |

## B0002

[Lines 15–17](../../../../../tests/unit/constraint_memory_test.cpp#L15); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void check(bool value,std::string_view message) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Provide the local assertion primitive used by this file. |
| inputs / outputs | Inputs: predicate and borrowed message view. Output: normal return for true; no value. |
| invariants | Only the false branch constructs an owning std::string and throws std::runtime_error. |
| ownership | The message view is borrowed for the call; no retained state. |
| failure | False throws runtime_error with a copied message; true does not convert the view. |
| cost | One branch check; string allocation is conditional on failure. |
| Design | [tests/unit/constraint_memory_test.cpp](../../../../../tests/unit/constraint_memory_test.cpp) |

## B0003

[Lines 18–20](../../../../../tests/unit/constraint_memory_test.cpp#L18); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
PhysicalRuntimeOptions options(std::uint64_t cap=64*1024*1024) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Build physical runtime options with a caller-selected support-account ceiling. |
| inputs / outputs | Input: requested byte cap, default 64 MiB. Output: PhysicalRuntimeOptions with support.memory_limit_bytes set. |
| invariants | Other fields retain PhysicalRuntimeOptions defaults; this helper does not create an account or reset a cap. |
| ownership | Returns an ordinary options value; caller owns it. |
| failure | No validation is performed here; runtime construction or a later accounted allocation may reject the cap. |
| cost | Fixed value construction and one assignment. |
| Design | [tests/unit/constraint_memory_test.cpp](../../../../../tests/unit/constraint_memory_test.cpp), [include/crown/runtime/physical.hpp](../../../../../include/crown/runtime/physical.hpp), [include/crown/runtime/support.hpp](../../../../../include/crown/runtime/support.hpp) |

## B0004

[Lines 21–33](../../../../../tests/unit/constraint_memory_test.cpp#L21); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Catalog schema(bool trusted=true) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Create the three-table catalog used to compare native and reference constraint validation. |
| inputs / outputs | Input: trusted flag. Output: catalog with source id/key/date/bool/decimal(38,2), target key/date, and unused id/payload tables. |
| invariants | The flag switches source primary/all-scalar/FK and target unique constraints between enforced and untrusted; unused.hint remains untrusted. |
| ownership | Catalog owns ordinary schema strings and constraint vectors as caller-side fixture data. |
| failure | Schema construction can fail through ordinary allocation; no MemoryAccount is involved. |
| cost | Fixed small schema construction; string/vector fixture allocations are outside runtime-account measurements. |
| Design | [tests/unit/constraint_memory_test.cpp](../../../../../tests/unit/constraint_memory_test.cpp), [src/runtime/constraint_validation.hpp](../../../../../src/runtime/constraint_validation.hpp) |

## B0005

[Lines 34–36](../../../../../tests/unit/constraint_memory_test.cpp#L34); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
PhysicalPlan plan(bool indexed,const Catalog& catalog) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Lower the empty query/tree against a supplied catalog for one storage backend. |
| inputs / outputs | Inputs: indexed selector and catalog reference. Output: PhysicalPlan from planner::lower_tree. |
| invariants | Indexed mode uses the test fixture options; reference mode uses default PhysicalOptions. The empty query/tree is deliberate for the validation fixtures. |
| ownership | The catalog is borrowed during lowering; returned plan owns its compiled representation according to lowering semantics. |
| failure | Lowering may reject an invalid catalog/plan or fail allocation; this helper adds no recovery. |
| cost | One lowering call; cost depends on catalog metadata, not fixture row count. |
| Design | [tests/unit/constraint_memory_test.cpp](../../../../../tests/unit/constraint_memory_test.cpp), [tests/support/indexed_runtime_fixture.hpp](../../../../../tests/support/indexed_runtime_fixture.hpp), [include/crown/planner/lower.hpp](../../../../../include/crown/planner/lower.hpp) |

## B0006

[Lines 37–46](../../../../../tests/unit/constraint_memory_test.cpp#L37); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Database database(std::size_t rows=13) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Build ordinary database input rows for constraint and memory-boundary cases. |
| inputs / outputs | Input: row count, default 13. Output: three-table Database; source and target share each generated long key/date, with scalar fields and a 38-digit decimal. |
| invariants | Each generated key contains an embedded NUL plus 8,192 k bytes; table 2 starts empty. This is caller input, not a native account export. |
| ownership | Database, Rows, strings, and decimal values are ordinary fixture-owned values. |
| failure | Parsing/allocation exceptions can escape; the helper has no native rollback boundary. |
| cost | Linear in requested rows, including ordinary long-string construction and set insertion, outside runtime account accounting. |
| Design | [tests/unit/constraint_memory_test.cpp](../../../../../tests/unit/constraint_memory_test.cpp), [include/crown/catalog/catalog.hpp](../../../../../include/crown/catalog/catalog.hpp), [include/crown/ir/model.hpp](../../../../../include/crown/ir/model.hpp), [docs/query_memory.md](../../../../query_memory.md) |

## B0007

[Lines 47–49](../../../../../tests/unit/constraint_memory_test.cpp#L47); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
resource::MemoryAccount memory(const PhysicalRuntime& runtime) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Expose the physical runtime’s support account to test-only assertions. |
| inputs / outputs | Input: const PhysicalRuntime reference. Output: a shared MemoryAccount handle obtained through RuntimeTestProbe. |
| invariants | The const_cast is limited to the friend test probe accessor; it does not mutate runtime state. |
| ownership | Returned account handle retains the shared account controller after facade lifetime. |
| failure | Invalid/moved-from runtime or probe access errors propagate. |
| cost | Constant-size handle access; not a runtime allocation measurement. |
| Design | [tests/unit/constraint_memory_test.cpp](../../../../../tests/unit/constraint_memory_test.cpp), [tests/support/runtime_probe.hpp](../../../../../tests/support/runtime_probe.hpp), [include/crown/runtime/physical.hpp](../../../../../include/crown/runtime/physical.hpp) |

## B0008

[Lines 50–54](../../../../../tests/unit/constraint_memory_test.cpp#L50); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void controller_only(const resource::MemoryAccount& account) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Assert that all accounted allocations except the account controller were released. |
| inputs / outputs | Input: MemoryAccount reference. Output: none when invariants hold. |
| invariants | Checks account invariants and exactly one live allocation whose requested bytes equal control_bytes(). |
| ownership | Borrowed account remains alive across the check; no allocation is retained. |
| failure | A mismatch throws runtime_error; this checks the account’s tracked requests, not process RSS. |
| cost | Reads account counters and compares fixed values. |
| Design | [tests/unit/constraint_memory_test.cpp](../../../../../tests/unit/constraint_memory_test.cpp), [include/crown/resource/memory.hpp](../../../../../include/crown/resource/memory.hpp), [docs/query_memory.md](../../../../query_memory.md) |

## B0009

[Lines 55–60](../../../../../tests/unit/constraint_memory_test.cpp#L55); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
template<class F>void denied(F&& action) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Require an action to fail specifically at the account byte limit. |
| inputs / outputs | Input: forwarding-reference callable; output: void on caught MemoryFailure with fault limit. |
| invariants | Calls the named parameter action() as an lvalue; it does not forward the original value category. Other MemoryFailure faults rethrow through the local assertion. |
| ownership | Callable is borrowed for this stack call; no action state is retained. |
| failure | A non-limit MemoryFailure is reported as runtime_error; a successful action throws runtime_error because denial was expected. |
| cost | One call and exception dispatch; diagnostics may allocate only on assertion failure. |
| Design | [tests/unit/constraint_memory_test.cpp](../../../../../tests/unit/constraint_memory_test.cpp), [include/crown/resource/memory.hpp](../../../../../include/crown/resource/memory.hpp) |

## B0010

[Lines 61–64](../../../../../tests/unit/constraint_memory_test.cpp#L61); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
template<class F>auto diagnostic(F&& action) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Normalize a successful validation result or crown::Error into a comparable pair. |
| inputs / outputs | Input: callable. Output: empty pair on success, otherwise copies error code and what() text. |
| invariants | Invokes named action() as an lvalue and catches only crown::Error; other exceptions propagate. |
| ownership | Returned pair owns its copied strings; exception is not retained. |
| failure | A non-crown exception escapes. Error presentation strings may allocate; no s04 allocation scope surrounds this helper’s parity checks. |
| cost | One call plus any exception formatting/string copies on the error path. |
| Design | [tests/unit/constraint_memory_test.cpp](../../../../../tests/unit/constraint_memory_test.cpp), [include/crown/api/error.hpp](../../../../../include/crown/api/error.hpp), [src/runtime/constraint_validation.hpp](../../../../../src/runtime/constraint_validation.hpp) |

## B0011

[Lines 65–106](../../../../../tests/unit/constraint_memory_test.cpp#L65); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void semantic_and_allocation_parity(bool indexed) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Compare reference and native constraint semantics, then check funded native scratch on a valid database. |
| inputs / outputs | Input: backend selector. For each trusted/untrusted schema, compares both validators on scenarios 0..6 (valid; table-count mismatch; wrong arity; wrong date type; decimal scale overflow; boolean-field flip while retaining the original row, triggering duplicate primary id; missing FK key). It also compares three zero-column unique/FK fixtures. |
| invariants | Error pair equality covers code, message, and order; current account usage must return to its pre-call value after each of 14 schema/scenario calls. Only the separate valid 3-row call checks global-new calls equal successful account allocation delta; trusted enforced-key case additionally requires calls&gt;0. Invalid-call diagnostics are not inside that allocation counter assertion. |
| ownership | Native key sets/cell views are temporary and should unwind; fixture databases and diagnostic strings are ordinary caller-side objects. |
| failure | Validator exceptions are caught only by diagnostic when they are crown::Error. Any leaked accounted scratch, parity change, or unfunded ordinary-new request fails an assertion. |
| cost | Two trust states × seven scenarios plus three empty-key comparisons per backend. It checks one valid allocation reconciliation per trust state, not CPU cost or allocations for every error case. |
| Design | [tests/unit/constraint_memory_test.cpp](../../../../../tests/unit/constraint_memory_test.cpp), [src/runtime/constraint_validation.hpp](../../../../../src/runtime/constraint_validation.hpp), [include/crown/resource/memory.hpp](../../../../../include/crown/resource/memory.hpp), [tests/support/index_allocation.hpp](../../../../../tests/support/index_allocation.hpp) |

## B0012

[Lines 107–130](../../../../../tests/unit/constraint_memory_test.cpp#L107); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void validator_limits(bool indexed) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Measure native validator peak requested bytes and verify exact-cap admission and one-byte-under cleanup/retry. |
| inputs / outputs | Input: backend selector. Output: prints the measured peak after validating the default 13-row fixture. |
| invariants | First measures above-construction peak; a fresh runtime with cap=peak must complete at the same peak and return current usage to baseline. At peak-1 the validator must throw MemoryFailure(limit), preserve current usage and sequence 0, then validate one row under the same unchanged cap. |
| ownership | The validator owns temporary compact keys/cell scratch in the runtime account; runtime/account handle stays alive through the retry. |
| failure | Only the account limit fault is accepted by denied(); semantic or unrelated failures fail the test. |
| cost | Full reference/native validation work over the 13-row fixture; measured value is maximum requested account bytes, not CPU time or total heap/RSS. |
| Design | [tests/unit/constraint_memory_test.cpp](../../../../../tests/unit/constraint_memory_test.cpp), [src/runtime/constraint_validation.hpp](../../../../../src/runtime/constraint_validation.hpp), [include/crown/resource/memory.hpp](../../../../../include/crown/resource/memory.hpp), [docs/query_memory.md](../../../../query_memory.md) |

## B0013

[Lines 131–188](../../../../../tests/unit/constraint_memory_test.cpp#L131); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void update_and_rebuild(bool indexed) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Exercise account-funded constraint validation during a physical update and two rebuild methods. |
| inputs / outputs | Input: backend selector. Inserts a caller-built 12,000-byte payload into unused table 2; separately inserts a five-scalar source row. Measures direct and insertion-replay rebuilds. |
| invariants | For update and scalar update, intercepted global-new calls equal successful account allocations during the scoped apply. A measured update cap admits; one-byte-under denial preserves ready/canonical state, and erasing the absent row at the same sequence succeeds as a no-op. Rebuilds retain rows, sequence, and account owner; exact measured cap succeeds and one-byte-under preserves old canonical state/current bytes. |
| ownership | The large extra Row and update object are constructed before the scoped engine operation. Rebuild creates a new runtime facade using the existing query account; old and new state overlap during measurement. Returned epoch/rebuilt runtime owns its normal results until scope exit. |
| failure | Denied paths require MemoryFault::limit; failed attempts must leave the old runtime ready and canonical. Each rebuild method has its own measured peak before boundary checks. |
| cost | Apply/rebuild scans and copies depend on the default 13 source/target pairs (26 physical rows), schema, route count, and source rows. Peak is requested account bytes including overlapping old/new funded state; global-new parity is asserted only for the two scoped update operations. |
| Design | [tests/unit/constraint_memory_test.cpp](../../../../../tests/unit/constraint_memory_test.cpp), [src/runtime/constraint_validation.hpp](../../../../../src/runtime/constraint_validation.hpp), [src/runtime/physical.cpp](../../../../../src/runtime/physical.cpp), [include/crown/runtime/physical.hpp](../../../../../include/crown/runtime/physical.hpp), [tests/support/index_allocation.hpp](../../../../../tests/support/index_allocation.hpp), [docs/query_memory.md](../../../../query_memory.md) |

## B0014

[Lines 189–212](../../../../../tests/unit/constraint_memory_test.cpp#L189); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void persistent_failures(bool indexed) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Sweep persistent global-new failure positions through constrained update and rebuild rollback paths. |
| inputs / outputs | Input: backend selector. For update and rebuild separately, constructs fresh runtimes initialized from two source/target pairs (four physical rows) and tests fail-after positions 0 through at most 2047, stopping on the first successful operation. |
| invariants | At every bad_alloc, prior canonical state and ready state must remain unchanged. Failed rebuild must restore current bytes and a same-state rebuild retry must work; update retry must accept the same input at sequence 1. Only failures&gt;0 and eventual completion are required; failure count is printed, not calibrated to an exact expected value. |
| ownership | The loop creates a fresh runtime/account for each fail-after position. After bad_alloc, it retries in that same iteration and on that same runtime after the hook scope ends: the same update row at sequence 1, or a same-state rebuild. Runtime scratch remains on the original account. |
| failure | Only std::bad_alloc marks an injected failure; other failures escape. Account invariants are checked at each point. |
| cost | At most 2 × 2,048 attempts per backend until first success, with fixture recreation, canonical export comparisons, and retries. Hook positions count covered operator-new requests, not bytes, CPU, or direct malloc. |
| Design | [tests/unit/constraint_memory_test.cpp](../../../../../tests/unit/constraint_memory_test.cpp), [tests/support/index_allocation.hpp](../../../../../tests/support/index_allocation.hpp), [src/runtime/physical.cpp](../../../../../src/runtime/physical.cpp), [src/runtime/constraint_validation.hpp](../../../../../src/runtime/constraint_validation.hpp) |

## B0015

[Lines 213–213](../../../../../tests/unit/constraint_memory_test.cpp#L213); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L213-L213:sha256:533f16bca7d58f44b3103b92e3485d22cfbb34bbad5ea3f3fa3b5a9dcb24ec89
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Close the recorded declaration scopes in constraint_memory_test.cpp: namespace (anonymous). |
| inputs / outputs | Preceding namespace, type or initializer declarations in; completed lexical boundary out. |
| invariants | Brace-opening context is recorded in root-scope-context-v1.json. These are declaration/initializer boundaries, not an independent update, validation or recovery operation. |
| ownership | Enclosing objects and borrowed fields keep their declared ownership. This punctuation creates no new owner. |
| failure | Malformed scope syntax is a compile error. Any initializer/constructor failure belongs to the enclosing object declaration. |
| cost | No separate loop, guard or engine call is introduced by the delimiter; enclosing initialization and object lifetime still have their actual costs. |
| Design | [tests/unit/constraint_memory_test.cpp](../../../../../tests/unit/constraint_memory_test.cpp), [docs/query_memory.md](../../../../query_memory.md), [docs/code_review.md](../../../../code_review.md) |

## B0016

[Lines 214–221](../../../../../tests/unit/constraint_memory_test.cpp#L214); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
int main() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Run the constraint validation, budget, rebuild, and persistence-fault fixture matrix. |
| inputs / outputs | Inputs: none. Output: status text and process status. |
| invariants | Runs four helpers for reference and indexed backends; catches std::exception, writes the failure and returns 1, otherwise prints completion and returns 0. |
| ownership | Local runtimes, accounts, databases, and result epochs release by helper scope. |
| failure | Any assertion/runtime exception is converted to exit status 1. |
| cost | Delegates to the helpers’ finite fixtures and bounded fault loops; this block itself makes no stronger performance claim and this packet did not execute it. |
| Design | [tests/unit/constraint_memory_test.cpp](../../../../../tests/unit/constraint_memory_test.cpp), [tests/support/indexed_runtime_fixture.hpp](../../../../../tests/support/indexed_runtime_fixture.hpp) |
