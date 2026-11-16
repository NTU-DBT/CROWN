# `tests/unit/accounted_ordered_rows_test.cpp` — block usage map

[Source](../../../../../tests/unit/accounted_ordered_rows_test.cpp) · [Source index](../../../README.md) · [Subsystem contracts](../../../subsystem_contracts.md) · [Reviewed primitives](../../../primitives.md)

Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection.

Snapshot SHA-256: `4e32ac1e7f5242f6a2edae622e646d23c994d5db2d0c5f718de5133b612196c7`. 260 lines partitioned into 16 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [tests](../../../subsystem_contracts.md#tests). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/code_review.md](../../../../code_review.md), [docs/reference_fuzz.md](../../../../reference_fuzz.md), [docs/task_ledger.md](../../../../task_ledger.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–20](../../../../../tests/unit/accounted_ordered_rows_test.cpp#L1) | Imports dependencies; declares namespace scope; declares aliases; declares values/defaults or compile-time conditions. |  · [reviewed contract](#b0001) |
| [B0002 · 21–23](../../../../../tests/unit/accounted_ordered_rows_test.cpp#L21) | Callable definition: void check(bool value,std::string_view message) | calls std::runtime_error, std::string; guard void check(bool value,std::string_view message) { · [reviewed contract](#b0002) |
| [B0003 · 24–24](../../../../../tests/unit/accounted_ordered_rows_test.cpp#L24) | Callable definition: MemoryAccount account() | calls MemoryAccount::create, max; returns MemoryAccount::create(std::numeric_limits&lt;std::uint64_t&gt;::max()) · [reviewed contract](#b0003) |
| [B0004 · 25–25](../../../../../tests/unit/accounted_ordered_rows_test.cpp#L25) | Callable definition: Row key(std::int64_t value) | calls ; returns {value} · [reviewed contract](#b0004) |
| [B0005 · 26–36](../../../../../tests/unit/accounted_ordered_rows_test.cpp#L26) | Callable definition: void reconcile(const MemoryAccount& memory) | calls check_invariants, statistics, add, check; guard check(purposes==state.current && lifetimes==state.current,"actual ordered-row allocations do not re…; 2 loop sites · [reviewed contract](#b0005) |
| [B0006 · 37–42](../../../../../tests/unit/accounted_ordered_rows_test.cpp#L37) | Callable definition: void controller_only(const MemoryAccount& memory) | calls reconcile, statistics, check, MemoryAccount::control_bytes; guard check(state.current.allocations==1 && state.current.requested_bytes==MemoryAccount::control_bytes(), · [reviewed contract](#b0006) |
| [B0007 · 43–54](../../../../../tests/unit/accounted_ordered_rows_test.cpp#L43) | Callable definition: void equivalent(const AccountedRowSet& rows,const Relation& expected) | calls check_invariants, check, export_rows, empty; guard check(rows.export_rows()==expected,"native ordering/membership differs from independent std::set");; 1 loop sites · [reviewed contract](#b0007) |
| [B0008 · 55–81](../../../../../tests/unit/accounted_ordered_rows_test.cpp#L55) | Callable definition: void exhaustive_ordering() | calls account, rows, check, insert; guard check(rows.insert(key(value)).second==expected.insert(key(value)).second,"insertion result mismatch…; growth insert; 4 loop sites; source comment (unverified): // This reverses construction order for every permutation, exercising each · [reviewed contract](#b0008) |
| [B0009 · 82–98](../../../../../tests/unit/accounted_ordered_rows_test.cpp#L82) | Callable definition: void random_differential() | calls account, rows, random, key; guard if(random()%3==0)check(rows.erase(probe)==expected.erase(probe),"random erase result differs");; growth insert; 1 loop sites · [reviewed contract](#b0009) |
| [B0010 · 99–129](../../../../../tests/unit/accounted_ordered_rows_test.cpp#L99) | Callable definition: void stable_addresses() | calls account, rows, try_emplace, key; guard auto handle=rows.extract(key(value));check(bool(handle),"stable-address extraction failed");; growth emplace, insert; 3 loop sites · [reviewed contract](#b0010) |
| [B0011 · 130–162](../../../../../tests/unit/accounted_ordered_rows_test.cpp#L130) | Callable definition: void scalar_ownership_and_lifetimes() | calls account, rows, std::string, Date::parse; guard expected.insert(original);check(rows.insert(original).second,"mixed-scalar row insertion failed");; growth insert · [reviewed contract](#b0011) |
| [B0012 · 163–208](../../../../../tests/unit/accounted_ordered_rows_test.cpp#L163) | Callable definition: void exact_cap_and_faults() | calls std::string, account, rows, insert; guard check(memory.statistics().peak_requested_bytes==peak,"exact native node/payload cap was not admitte…; growth insert; 1 loop sites · [reviewed contract](#b0012) |
| [B0013 · 209–217](../../../../../tests/unit/accounted_ordered_rows_test.cpp#L209) | Type/record definition: struct Bucket | growth insert · [reviewed contract](#b0013) |
| [B0014 · 218–252](../../../../../tests/unit/accounted_ordered_rows_test.cpp#L218) | Callable definition: void nested_ownership() | calls account, rows, key, std::string; guard check(memory.statistics().current==before &&; growth insert; 1 loop sites · [reviewed contract](#b0014) |
| [B0015 · 253–253](../../../../../tests/unit/accounted_ordered_rows_test.cpp#L253) | Closes surrounding scope/type. | source comment (unverified): // namespace · [reviewed contract](#b0015) |
| [B0016 · 254–260](../../../../../tests/unit/accounted_ordered_rows_test.cpp#L254) | Callable definition: int main() | calls exhaustive_ordering, random_differential, stable_addresses, scalar_ownership_and_lifetimes; returns 1 · [reviewed contract](#b0016) |

## B0001

[Lines 1–20](../../../../../tests/unit/accounted_ordered_rows_test.cpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L1-L20:sha256:ac8ceff0835c446a136a8d898a9d44c34adc2c6c010d1af24eafd4d9a2ba7968
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Prepare accounted_ordered_rows_test.cpp: include "accounted_ordered_rows.hpp", "index_allocation.hpp", &lt;array&gt;, &lt;bit&gt;, &lt;iostream&gt;, &lt;map&gt;, &lt;numeric&gt;, &lt;random&gt;, &lt;ranges&gt;, &lt;stdexcept&gt;; bind local aliases/name imports; declare constant fixture data. |
| inputs / outputs | Compiler-visible dependencies, names and the recorded declarations in; declarations available to the following fixture/CLI/example definitions out. The source span lists the exact member/global names, types and initial values; initializers run when the enclosing object/program/thread is initialized. |
| invariants | Declarations are scoped to this source/header and its selected ABI. Included code has its own effects; names and editable fixture values do not confer proof, admission or publication authority. |
| ownership | Aliases/includes do not create a query owner. Pointers/references/views are non-owning. Containers own their elements, which can themselves be borrowed pointers or numeric IDs. Only documented owning shared-control handles retain controls; IDs/slot-handle values do not independently keep an arena/runtime alive. |
| failure | Missing headers, ill-formed names/types, failed static assertions or active #error directives stop compilation. No runtime rejection/rollback mechanism is implemented by aliases or function prototypes. |
| cost | Preprocessing and type/constraint instantiation cost compilation. Alias/prototype syntax does not invoke the declared operation; any included definitions keep their own initialization effects. These constexpr data are fixed fixture constants; quota literals are grants, not reserved bytes or measured peaks. |
| Design | [tests/unit/accounted_ordered_rows_test.cpp](../../../../../tests/unit/accounted_ordered_rows_test.cpp), [docs/query_memory.md](../../../../query_memory.md), [docs/code_review.md](../../../../code_review.md) |

## B0002

[Lines 21–23](../../../../../tests/unit/accounted_ordered_rows_test.cpp#L21); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void check(bool value,std::string_view message) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Fail native ordered-row assertions. |
| inputs / outputs | Bool/message in; runtime_error when false. |
| invariants | Every native/account model discrepancy fails. |
| ownership | Message borrowed unless formatted on failure. |
| failure | runtime_error is harness carrier. |
| cost | One branch. |
| Design | tests/unit/accounted_ordered_rows_test.cpp:21-23, docs/memory_accounts.md:52-82, docs/memory_accounts.md:342-377, [Refactor.md §6.2](../../../../../Refactor.md), [Refactor.md §11.4 S05](../../../../../Refactor.md) |

## B0003

[Lines 24–24](../../../../../tests/unit/accounted_ordered_rows_test.cpp#L24); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
MemoryAccount account() {return MemoryAccount::create(std::numeric_limits<std::uint64_t>::max());}
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Create a MemoryAccount with maximum uint64 limit. |
| inputs / outputs | No input; returns new native account. |
| invariants | Controller bytes still count against the account; this is not IndexWork. |
| ownership | Returned account retains controller. |
| failure | MemoryFailure or upstream allocation failure propagates. |
| cost | Creates the account controller through its native account path; this contract does not assert an allocator-call count. |
| Design | tests/unit/accounted_ordered_rows_test.cpp:24-24, docs/memory_accounts.md:52-82, docs/memory_accounts.md:342-377, [Refactor.md §6.2](../../../../../Refactor.md), [Refactor.md §11.4 S05](../../../../../Refactor.md) |

## B0004

[Lines 25–25](../../../../../tests/unit/accounted_ordered_rows_test.cpp#L25); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Row key(std::int64_t value) {return {value};}
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Create one integer Row key. |
| inputs / outputs | int64 in; one-cell Row out. |
| invariants | No coercion. |
| ownership | Row owns scalar value. |
| failure | No custom catch. |
| cost | Fixed one-cell construction. |
| Design | tests/unit/accounted_ordered_rows_test.cpp:25-25, docs/memory_accounts.md:52-82, docs/memory_accounts.md:342-377, [Refactor.md §6.2](../../../../../Refactor.md), [Refactor.md §11.4 S05](../../../../../Refactor.md) |

## B0005

[Lines 26–36](../../../../../tests/unit/accounted_ordered_rows_test.cpp#L26); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void reconcile(const MemoryAccount& memory) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Reconcile account invariant, purpose/lifetime totals and peak limit. |
| inputs / outputs | MemoryAccount in; scans stats and checks exact category sums. |
| invariants | Current allocations equal totals by purpose and lifetime; peak stays within limit. |
| ownership | Borrows account; outputs no retained registry. |
| failure | MemoryAccount diagnostic errors or runtime_error propagate. |
| cost | Explicit full account-ledger diagnostic, not an update primitive. |
| Design | tests/unit/accounted_ordered_rows_test.cpp:26-36, docs/memory_accounts.md:52-82, docs/memory_accounts.md:342-377, [Refactor.md §6.2](../../../../../Refactor.md), [Refactor.md §11.4 S05](../../../../../Refactor.md) |

## B0006

[Lines 37–42](../../../../../tests/unit/accounted_ordered_rows_test.cpp#L37); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void controller_only(const MemoryAccount& memory) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Require only controller allocation after row owners are gone. |
| inputs / outputs | MemoryAccount in; first reconciles, then checks one control allocation and control_bytes. |
| invariants | No ordered-row node/payload remains charged. |
| ownership | Account still owns its controller. |
| failure | Mismatch throws runtime_error. |
| cost | Stats reads and full reconciliation. |
| Design | tests/unit/accounted_ordered_rows_test.cpp:37-42, docs/memory_accounts.md:52-82, docs/memory_accounts.md:342-377, [Refactor.md §6.2](../../../../../Refactor.md), [Refactor.md §11.4 S05](../../../../../Refactor.md) |

## B0007

[Lines 43–54](../../../../../tests/unit/accounted_ordered_rows_test.cpp#L43); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void equivalent(const AccountedRowSet& rows,const Relation& expected) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Compare AccountedRowSet with std::set, lookup and upper_bound. |
| inputs / outputs | Native set/reference set in; checks ordered export, AVL height and probes -1 through 8. |
| invariants | Membership/order/search boundaries agree; height assertion is finite fixture check. |
| ownership | Native rows use supplied account; std::set is independent test state. |
| failure | Mismatch or invariant error propagates. |
| cost | Exports rows and performs fixed nine-probe lookup checks. |
| Design | tests/unit/accounted_ordered_rows_test.cpp:43-54, docs/memory_accounts.md:52-82, docs/memory_accounts.md:342-377, [Refactor.md §6.2](../../../../../Refactor.md), [Refactor.md §11.4 S05](../../../../../Refactor.md) |

## B0008

[Lines 55–81](../../../../../tests/unit/accounted_ordered_rows_test.cpp#L55); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void exhaustive_ordering() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Exercise every six-key insertion order and reverse deletion order. |
| inputs / outputs | No input; iterates all 720 permutations, compares after each change, then extract/reinsert/erase under global-new denial. |
| invariants | Each deletion order and immediate/deep successor cases are covered; account totals reconcile independently. |
| ownership | MemoryAccount owns native nodes/payloads; extracted node handle retains its allocation; std::set is oracle. |
| failure | A caught global-new bad_alloc would fail unexpected close assertion; account errors propagate. |
| cost | For each of 720 orders, inserts six keys, then performs six rounds of extract/reinsert/erase with repeated equivalence and invariant checks; cleanup can be linear. |
| Design | tests/unit/accounted_ordered_rows_test.cpp:55-81, docs/memory_accounts.md:52-82, docs/memory_accounts.md:342-377, [Refactor.md §6.2](../../../../../Refactor.md), [Refactor.md §11.4 S05](../../../../../Refactor.md) |

## B0009

[Lines 82–98](../../../../../tests/unit/accounted_ordered_rows_test.cpp#L82); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void random_differential() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Compare 6000 seeded insert/erase operations and clear behavior. |
| inputs / outputs | No input; bounded integer probes mutate AccountedRowSet and std::set. |
| invariants | Every 29th step and final membership match; repeated clear leaves only account controller. |
| ownership | Native set uses MemoryAccount; oracle is ordinary std::set. |
| failure | Mismatches throw runtime_error. |
| cost | 6000 updates and periodic full exports; clear teardown remains proportional to rows. |
| Design | tests/unit/accounted_ordered_rows_test.cpp:82-98, docs/memory_accounts.md:52-82, docs/memory_accounts.md:342-377, [Refactor.md §6.2](../../../../../Refactor.md), [Refactor.md §11.4 S05](../../../../../Refactor.md) |

## B0010

[Lines 99–129](../../../../../tests/unit/accounted_ordered_rows_test.cpp#L99); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void stable_addresses() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Check extracted AccountedRowMap node and successor addresses. |
| inputs / outputs | No input; inserts 12 mapped rows, extracts each in a fixed order, checks all remaining addresses and reinserts. |
| invariants | Node/key/mapped addresses survive extract, rotations and handle reinsertion. |
| ownership | Accounted map owns nodes; node handle temporarily owns extracted node in same account. |
| failure | s04_alloc Scope catches global-new attempts on reinsertion; map invariant errors propagate. |
| cost | 12 removals plus O(12) surviving-address checks after each. |
| Design | tests/unit/accounted_ordered_rows_test.cpp:99-129, docs/memory_accounts.md:52-82, docs/memory_accounts.md:342-377, [Refactor.md §6.2](../../../../../Refactor.md), [Refactor.md §11.4 S05](../../../../../Refactor.md) |

## B0011

[Lines 130–162](../../../../../tests/unit/accounted_ordered_rows_test.cpp#L130); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void scalar_ownership_and_lifetimes() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Check mixed-scalar byte ownership and retained-lifetime classification. |
| inputs / outputs | No input; inserts a binary 4 KiB string/date/decimal row, drops caller value, extracts/reinserts and relabels. |
| invariants | Extract preserves actual bytes while two allocations classify retained; reinsert clears retained classification. |
| ownership | MemoryAccount owns AccountedRow/node block; RowView/export is borrowed or explicit copy. |
| failure | Global-new denial probes reinsertion; accounting mismatch throws runtime_error. |
| cost | Full account reconciliations and row exports; classification costs differ from byte allocation. |
| Design | tests/unit/accounted_ordered_rows_test.cpp:130-162, docs/memory_accounts.md:52-82, docs/memory_accounts.md:342-377, [Refactor.md §6.2](../../../../../Refactor.md), [Refactor.md §11.4 S05](../../../../../Refactor.md) |

## B0012

[Lines 163–208](../../../../../tests/unit/accounted_ordered_rows_test.cpp#L163); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void exact_cap_and_faults() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Check exact MemoryAccount cap, one-byte denial and upstream allocation faults. |
| inputs / outputs | No input; derives peak, admits exact limit, rejects peak-1, then injects global-new bad_alloc at each reached position. |
| invariants | MemoryFailure::limit leaves current bytes/membership; upstream failure is retryable and leaves account ledger unchanged. |
| ownership | AccountedRowSet allocates node and scalar storage through its MemoryAccount; s04_alloc intercepts underlying global-new calls separately. |
| failure | Catches MemoryFailure for cap and bad_alloc for injected upstream faults; assertions verify carriers/state. |
| cost | At most 16 positions, exact account statistics/reconciliation; no native build/test executed. |
| Design | tests/unit/accounted_ordered_rows_test.cpp:163-208, docs/memory_accounts.md:52-82, docs/memory_accounts.md:342-377, [Refactor.md §6.2](../../../../../Refactor.md), [Refactor.md §11.4 S05](../../../../../Refactor.md) |

## B0013

[Lines 209–217](../../../../../tests/unit/accounted_ordered_rows_test.cpp#L209); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct Bucket {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Wrap AccountedRowSet with an integer value and preserve supplied accounting ownership. |
| inputs / outputs | Bucket constructor receives MemoryAccount, purpose, attribution, lifetime and optionally a Row; it creates the nested set and seeds one row/value=1 when given a row, while set_lifetime forwards reclassification. |
| invariants | The initial nested membership is one; a lifetime change alters the accounting category, not the allocation bytes; no replacement account or grant is made. |
| ownership | Bucket owns the AccountedRowSet; nested allocations use the supplied MemoryAccount and explicit categories. |
| failure | Constructor, seed insertion and reclassification failures propagate from account/set APIs. |
| cost | Stores metadata and possibly performs one nested insert; reclassification cost follows the nested set. |
| Design | tests/unit/accounted_ordered_rows_test.cpp:209-217, docs/memory_accounts.md:52-82, docs/memory_accounts.md:342-377, [Refactor.md §6.2](../../../../../Refactor.md), [Refactor.md §11.4 S05](../../../../../Refactor.md) |

## B0014

[Lines 218–252](../../../../../tests/unit/accounted_ordered_rows_test.cpp#L218); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void nested_ownership() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Check nested AccountedRowMap extraction, lifetime ownership and construction faults. |
| inputs / outputs | No input; builds outer key/mapped bucket/inner payload, extracts/reinserts, then injects allocation failures. |
| invariants | Extraction keeps outer/inner four blocks charged and retained; construction failure leaves empty map/account totals unchanged. |
| ownership | One account owns outer node/key and nested row node/payload; node handle preserves same account. |
| failure | s04_alloc faults underlying global-new calls; catches bad_alloc, separately reconciles MemoryAccount. |
| cost | Finite nested teardown/fault sweep; nested classification may visit child state. |
| Design | tests/unit/accounted_ordered_rows_test.cpp:218-252, docs/memory_accounts.md:52-82, docs/memory_accounts.md:342-377, [Refactor.md §6.2](../../../../../Refactor.md), [Refactor.md §11.4 S05](../../../../../Refactor.md) |

## B0015

[Lines 253–253](../../../../../tests/unit/accounted_ordered_rows_test.cpp#L253); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L253-L253:sha256:533f16bca7d58f44b3103b92e3485d22cfbb34bbad5ea3f3fa3b5a9dcb24ec89
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Close the recorded declaration scopes in accounted_ordered_rows_test.cpp: namespace (anonymous). |
| inputs / outputs | Preceding namespace, type or initializer declarations in; completed lexical boundary out. |
| invariants | Brace-opening context is recorded in root-scope-context-v1.json. These are declaration/initializer boundaries, not an independent update, validation or recovery operation. |
| ownership | Enclosing objects and borrowed fields keep their declared ownership. This punctuation creates no new owner. |
| failure | Malformed scope syntax is a compile error. Any initializer/constructor failure belongs to the enclosing object declaration. |
| cost | No separate loop, guard or engine call is introduced by the delimiter; enclosing initialization and object lifetime still have their actual costs. |
| Design | [tests/unit/accounted_ordered_rows_test.cpp](../../../../../tests/unit/accounted_ordered_rows_test.cpp), [docs/query_memory.md](../../../../query_memory.md), [docs/code_review.md](../../../../code_review.md) |

## B0016

[Lines 254–260](../../../../../tests/unit/accounted_ordered_rows_test.cpp#L254); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
int main() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Run native ordered-row differential, address, account and fault cases. |
| inputs / outputs | No input; invokes six suites and emits success/failure. |
| invariants | Controller-only state required after owners unwind. |
| ownership | main owns case sequence; each case owns its account. |
| failure | std::exception prints and returns 1. |
| cost | Exhaustive 720 orders, 6000 random operations and finite fault loops; not executed here. |
| Design | tests/unit/accounted_ordered_rows_test.cpp:254-260, docs/memory_accounts.md:52-82, docs/memory_accounts.md:342-377, [Refactor.md §6.2](../../../../../Refactor.md), [Refactor.md §11.4 S05](../../../../../Refactor.md) |
