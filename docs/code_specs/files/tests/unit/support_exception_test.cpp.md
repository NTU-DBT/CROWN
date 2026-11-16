# `tests/unit/support_exception_test.cpp` — block usage map

[Source](../../../../../tests/unit/support_exception_test.cpp) · [Source index](../../../README.md) · [Subsystem contracts](../../../subsystem_contracts.md) · [Reviewed primitives](../../../primitives.md)

Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection.

Snapshot SHA-256: `010ff791a81db64eaf826af98ffd9aea3d5d65d46bf6170f4ad8a722a4d4e6cd`. 433 lines partitioned into 54 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [tests](../../../subsystem_contracts.md#tests). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/code_review.md](../../../../code_review.md), [docs/reference_fuzz.md](../../../../reference_fuzz.md), [docs/task_ledger.md](../../../../task_ledger.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–21](../../../../../tests/unit/support_exception_test.cpp#L1) | Imports dependencies; declares namespace scope; declares values/defaults or compile-time conditions. | growth new; source comment (unverified): // This fault injector lives in its own executable so allocations elsewhere in · [reviewed contract](#b0001) |
| [B0002 · 22–29](../../../../../tests/unit/support_exception_test.cpp#L22) | Callable definition: \[\[gnu::noinline\]\] void* allocate(std::size_t bytes) | calls std::malloc; returns result; growth allocate, malloc · [reviewed contract](#b0002) |
| [B0003 · 30–35](../../../../../tests/unit/support_exception_test.cpp#L30) | Type/record definition: struct FaultScope |  · [reviewed contract](#b0003) |
| [B0004 · 36–37](../../../../../tests/unit/support_exception_test.cpp#L36) | Closes surrounding scope/type. | source comment (unverified): // namespace · [reviewed contract](#b0004) |
| [B0005 · 38–38](../../../../../tests/unit/support_exception_test.cpp#L38) | Callable definition: void* operator new(std::size_t bytes) | calls allocate; returns allocate(bytes); growth allocate, new · [reviewed contract](#b0005) |
| [B0006 · 39–39](../../../../../tests/unit/support_exception_test.cpp#L39) | Callable definition: void* operator new\[\](std::size_t bytes) | calls ; returns allocate(bytes); growth allocate, new · [reviewed contract](#b0006) |
| [B0007 · 40–40](../../../../../tests/unit/support_exception_test.cpp#L40) | Callable definition: void operator delete(void* pointer) noexcept | calls std::free · [reviewed contract](#b0007) |
| [B0008 · 41–41](../../../../../tests/unit/support_exception_test.cpp#L41) | Callable definition: void operator delete\[\](void* pointer) noexcept | calls  · [reviewed contract](#b0008) |
| [B0009 · 42–42](../../../../../tests/unit/support_exception_test.cpp#L42) | Callable definition: void operator delete(void* pointer, std::size_t) noexcept | calls std::free · [reviewed contract](#b0009) |
| [B0010 · 43–43](../../../../../tests/unit/support_exception_test.cpp#L43) | Callable definition: void operator delete\[\](void* pointer, std::size_t) noexcept | calls  · [reviewed contract](#b0010) |
| [B0011 · 44–48](../../../../../tests/unit/support_exception_test.cpp#L44) | declares namespace scope; declares aliases. |  · [reviewed contract](#b0011) |
| [B0012 · 49–51](../../../../../tests/unit/support_exception_test.cpp#L49) | Callable definition: void check(bool value, const std::string& message) | calls std::runtime_error; guard void check(bool value, const std::string& message) { · [reviewed contract](#b0012) |
| [B0013 · 52–52](../../../../../tests/unit/support_exception_test.cpp#L52) | Callable definition: Value n(std::int64_t value) | calls ; returns value · [reviewed contract](#b0013) |
| [B0014 · 53–53](../../../../../tests/unit/support_exception_test.cpp#L53) | Callable definition: Value s(std::string value) | calls ; returns value · [reviewed contract](#b0014) |
| [B0015 · 54–54](../../../../../tests/unit/support_exception_test.cpp#L54) | Callable definition: std::string padded(char value) | calls std::string; returns std::string(180, value) · [reviewed contract](#b0015) |
| [B0016 · 55–55](../../../../../tests/unit/support_exception_test.cpp#L55) | Explanatory comments or spacing. |  |
| [B0017 · 56–70](../../../../../tests/unit/support_exception_test.cpp#L56) | Callable definition: PhysicalPlan make_plan() | calls planner::lower_tree; returns planner::lower_tree(catalog, query, tree) · [reviewed contract](#b0017) |
| [B0018 · 71–71](../../../../../tests/unit/support_exception_test.cpp#L71) | Explanatory comments or spacing. |  |
| [B0019 · 72–77](../../../../../tests/unit/support_exception_test.cpp#L72) | Type/record definition: enum class Case |  · [reviewed contract](#b0019) |
| [B0020 · 78–86](../../../../../tests/unit/support_exception_test.cpp#L78) | Callable definition: const char* case_name(Case value) | calls ; returns @; @ · [reviewed contract](#b0020) |
| [B0021 · 87–87](../../../../../tests/unit/support_exception_test.cpp#L87) | Explanatory comments or spacing. |  |
| [B0022 · 88–92](../../../../../tests/unit/support_exception_test.cpp#L88) | Callable definition: SupportOptions options() | calls ; returns result · [reviewed contract](#b0022) |
| [B0023 · 93–93](../../../../../tests/unit/support_exception_test.cpp#L93) | Explanatory comments or spacing. |  |
| [B0024 · 94–108](../../../../../tests/unit/support_exception_test.cpp#L94) | Callable definition: std::vector&lt;NativeSetUpdate&gt; setup_updates(Case which) | calls n, s, padded, push_back; returns {{1, NodeId{2}, SetOperation::insert, s_x}}; result; growth insert, push_back · [reviewed contract](#b0024) |
| [B0025 · 109–109](../../../../../tests/unit/support_exception_test.cpp#L109) | Explanatory comments or spacing. |  |
| [B0026 · 110–120](../../../../../tests/unit/support_exception_test.cpp#L110) | Callable definition: NativeSetUpdate target_update(Case which) | calls n, s, padded, std::runtime_error; returns {4, NodeId{2}, SetOperation::insert, s_x}; {5, NodeId{2}, SetOperation::erase, s_x}; growth insert · [reviewed contract](#b0026) |
| [B0027 · 121–121](../../../../../tests/unit/support_exception_test.cpp#L121) | Explanatory comments or spacing. |  |
| [B0028 · 122–133](../../../../../tests/unit/support_exception_test.cpp#L122) | Callable definition: std::shared_ptr&lt;const SupportJournal&gt; initialize(SupportRuntime& runtime, Case which) | calls setup_updates, apply, check, empty; guard check(epoch.native_changed, "setup update did not change a native set");; returns last_journal; 1 loop sites · [reviewed contract](#b0028) |
| [B0029 · 134–134](../../../../../tests/unit/support_exception_test.cpp#L134) | Explanatory comments or spacing. |  |
| [B0030 · 135–147](../../../../../tests/unit/support_exception_test.cpp#L135) | Callable definition: io::Json normalized_snapshot(const SupportRuntime& runtime, const PhysicalPlan& plan) | calls io::write_support_snapshot, snapshot, at, is_null; returns result; 3 loop sites · [reviewed contract](#b0030) |
| [B0031 · 148–148](../../../../../tests/unit/support_exception_test.cpp#L148) | Explanatory comments or spacing. |  |
| [B0032 · 149–163](../../../../../tests/unit/support_exception_test.cpp#L149) | Callable definition: io::Json normalized_epoch(const SupportEpoch& epoch) | calls io::write_support_epoch, is_object, contains, items; returns result; 2 loop sites; source comment (unverified): // This includes transition handles, journal record handles, and event · [reviewed contract](#b0032) |
| [B0033 · 164–164](../../../../../tests/unit/support_exception_test.cpp#L164) | Explanatory comments or spacing. |  |
| [B0034 · 165–171](../../../../../tests/unit/support_exception_test.cpp#L165) | Type/record definition: struct JournalValue | returns layout.same_token(other.layout) && values == other.values · [reviewed contract](#b0034) |
| [B0035 · 172–172](../../../../../tests/unit/support_exception_test.cpp#L172) | Explanatory comments or spacing. |  |
| [B0036 · 173–179](../../../../../tests/unit/support_exception_test.cpp#L173) | Callable definition: std::vector&lt;JournalValue&gt; retained_values(const std::shared_ptr&lt;const SupportJournal&gt;& journal) | calls check, reserve, size, push_back; guard check(journal != nullptr, "successful update has no retained support journal");; returns result; growth push_back, reserve; 1 loop sites · [reviewed contract](#b0036) |
| [B0037 · 180–180](../../../../../tests/unit/support_exception_test.cpp#L180) | Explanatory comments or spacing. |  |
| [B0038 · 181–187](../../../../../tests/unit/support_exception_test.cpp#L181) | Callable definition: void check_rollback_statistics(const storage::ArenaStatistics& before, const storage::ArenaStatistics& after, const std::string& … | calls check; guard check(before.pins == after.pins && before.live_records == after.live_records && · [reviewed contract](#b0038) |
| [B0039 · 188–188](../../../../../tests/unit/support_exception_test.cpp#L188) | Explanatory comments or spacing. |  |
| [B0040 · 189–193](../../../../../tests/unit/support_exception_test.cpp#L189) | Type/record definition: struct LiveHandle |  · [reviewed contract](#b0040) |
| [B0041 · 194–194](../../../../../tests/unit/support_exception_test.cpp#L194) | Explanatory comments or spacing. |  |
| [B0042 · 195–215](../../../../../tests/unit/support_exception_test.cpp#L195) | Callable definition: std::vector&lt;LiveHandle&gt; public_handles(const SupportRuntime& runtime) | calls snapshot, get, check, push_back; guard check(owned && *owned == tuple, "snapshot exposed an invalid public support handle");; returns result; growth push_back; 5 loop sites · [reviewed contract](#b0042) |
| [B0043 · 216–216](../../../../../tests/unit/support_exception_test.cpp#L216) | Explanatory comments or spacing. |  |
| [B0044 · 217–221](../../../../../tests/unit/support_exception_test.cpp#L217) | Type/record definition: struct ExpectedResult |  · [reviewed contract](#b0044) |
| [B0045 · 222–222](../../../../../tests/unit/support_exception_test.cpp#L222) | Explanatory comments or spacing. |  |
| [B0046 · 223–230](../../../../../tests/unit/support_exception_test.cpp#L223) | Callable definition: ExpectedResult clean_result(const PhysicalPlan& plan, Case which) | calls options, initialize, apply, target_update; returns {normalized_snapshot(runtime, plan), normalized_epoch(epoch), runtime.has_answer()} · [reviewed contract](#b0046) |
| [B0047 · 231–231](../../../../../tests/unit/support_exception_test.cpp#L231) | Explanatory comments or spacing. |  |
| [B0048 · 232–297](../../../../../tests/unit/support_exception_test.cpp#L232) | Callable definition: void check_expected_state(const SupportRuntime& runtime, Case which, const SupportEpoch& epoch) | calls n, find, snapshot, at; guard check(runtime.has_answer() && record && survivor && parent_key && visible_key,; returns value.tuple.values() == x; value.tuple.values() == x · [reviewed contract](#b0048) |
| [B0049 · 298–298](../../../../../tests/unit/support_exception_test.cpp#L298) | Explanatory comments or spacing. |  |
| [B0050 · 299–373](../../../../../tests/unit/support_exception_test.cpp#L299) | Callable definition: std::size_t sweep(const PhysicalPlan& plan, Case which) | calls clean_result, target_update, options, initialize; guard check(runtime.sequence() == sequence && runtime.has_answer() == answer && runtime.owner() == owner,; returns failures; 1 loop sites; source comment (unverified): // allocate() leaves fail_after at zero through runtime rollback. · [reviewed contract](#b0050) |
| [B0051 · 374–374](../../../../../tests/unit/support_exception_test.cpp#L374) | Explanatory comments or spacing. |  |
| [B0052 · 375–411](../../../../../tests/unit/support_exception_test.cpp#L375) | Callable definition: void check_journal_survives_runtime_destruction(const PhysicalPlan& plan) | calls n, s, padded, options; guard check(retained != nullptr && !retained-&gt;records.empty(),; returns record.handle.node == NodeId{2} && record.handle.role == SupportRole::records &&; record.handle.nod…; growth insert · [reviewed contract](#b0052) |
| [B0053 · 412–413](../../../../../tests/unit/support_exception_test.cpp#L412) | Closes surrounding scope/type. | source comment (unverified): // namespace · [reviewed contract](#b0053) |
| [B0054 · 414–433](../../../../../tests/unit/support_exception_test.cpp#L414) | Callable definition: int main() | calls make_plan, sweep, check, check_journal_survives_runtime_destruction; guard check(insert &gt; 0 && supported_erase &gt; 0 && redundant_support_erase &gt; 0 && reclaim &gt; 0,; returns 1; growth insert · [reviewed contract](#b0054) |

## B0001

[Lines 1–21](../../../../../tests/unit/support_exception_test.cpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L1-L21:sha256:def8c44a56c004cb9e9eb13bd25d19bcb5db3827a6be73df6d213f068372e70e
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Prepare support_exception_test.cpp: include "crown/io/document.hpp", "crown/io/support.hpp", "crown/planner/lower.hpp", "crown/runtime/support.hpp", &lt;algorithm&gt;, &lt;cstddef&gt;, &lt;cstdint&gt;, &lt;cstdlib&gt;, &lt;iostream&gt;, &lt;new&gt;, &lt;optional&gt;, &lt;stdexcept&gt;, &lt;string&gt;, &lt;utility&gt;, &lt;vector&gt;; declare fixture state/default initializers. |
| inputs / outputs | Compiler-visible dependencies, names and the recorded declarations in; declarations available to the following fixture/CLI/example definitions out. The source span lists the exact member/global names, types and initial values; initializers run when the enclosing object/program/thread is initialized. |
| invariants | Declarations are scoped to this source/header and its selected ABI. Included code has its own effects; names and editable fixture values do not confer proof, admission or publication authority. |
| ownership | Aliases/includes do not create a query owner. Pointers/references/views are non-owning. Containers own their elements, which can themselves be borrowed pointers or numeric IDs. Only documented owning shared-control handles retain controls; IDs/slot-handle values do not independently keep an arena/runtime alive. Thread-local fault/countdown state belongs to this test executable and each thread; it is not a field added to a production owner. |
| failure | Missing headers, ill-formed names/types, failed static assertions or active #error directives stop compilation. No runtime rejection/rollback mechanism is implemented by aliases or function prototypes. |
| cost | Preprocessing and type/constraint instantiation cost compilation. Alias/prototype syntax does not invoke the declared operation; any included definitions keep their own initialization effects. This span initializes fixed scalar/atomic/TLS probe state. Storage and later probe accesses are test costs; no native factory or filesystem operation is implied by these scalar initializers. TLS storage and later injector accesses are test instrumentation costs. |
| Design | [tests/unit/support_exception_test.cpp](../../../../../tests/unit/support_exception_test.cpp), [docs/prepared_epochs.md](../../../../prepared_epochs.md), [docs/code_review.md](../../../../code_review.md) |

## B0002

[Lines 22–29](../../../../../tests/unit/support_exception_test.cpp#L22); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
[[gnu::noinline]] void* allocate(std::size_t bytes)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Provide the support fault executable's ordinary global-new allocation seam. |
| inputs / outputs | Callable: \[\[gnu::noinline\]\] void* allocate(std::size_t bytes). Input: requested byte count. Output: malloc-backed storage or std::bad_alloc when the thread-local countdown reaches zero. |
| invariants | A zero-byte request asks malloc for one byte; this hook sees ordinary new/new\[\] calls routed through the local replacements, not direct allocator calls or aligned-new overloads. |
| ownership | malloc_new-style backing is returned to the ordinary operator-new caller and later released by matching replacement delete; this test path does not retain a separate allocator object. |
| failure | A failed check throws std::runtime_error. The sweep catches std::bad_alloc from ordinary global-new injection around the target apply; runtime/API failures outside that catch fail the executable. |
| cost | One requested-size malloc call for each ordinary global-new attempt; countdown checks are constant work. |
| Design | [include/crown/runtime/support.hpp](../../../../../include/crown/runtime/support.hpp), [src/runtime/support.cpp](../../../../../src/runtime/support.cpp), [docs/support_invariants.md](../../../../support_invariants.md), [docs/prepared_epochs.md §Staging, rollback, and publication](../../../../prepared_epochs.md), [docs/prepared_epochs.md §Batch event and resource accounting](../../../../prepared_epochs.md) |

## B0003

[Lines 30–35](../../../../../tests/unit/support_exception_test.cpp#L30); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct FaultScope
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Arm one support-runtime allocation-failure position and disable it when the scope ends. |
| inputs / outputs | Type: struct FaultScope. Input: selected ordinary global-new attempt index. Output: no value; construction sets fail_after and destruction restores the disabled sentinel. |
| invariants | The scope is noncopyable and resets to -1 rather than restoring a nested prior value. |
| ownership | Test plan, row, and JSON results are local owning values. Passed runtime/plan references are borrowed for the call; only an explicitly retained shared SupportJournal keeps its affected record pins beyond an epoch. |
| failure | A failed check throws std::runtime_error. The sweep catches std::bad_alloc from ordinary global-new injection around the target apply; runtime/API failures outside that catch fail the executable. |
| cost | Uses the fixed two-child plan and short fixture rows; it is a test helper, not a public work or allocation bound. |
| Design | [include/crown/runtime/support.hpp](../../../../../include/crown/runtime/support.hpp), [src/runtime/support.cpp](../../../../../src/runtime/support.cpp), [docs/support_invariants.md](../../../../support_invariants.md), [docs/prepared_epochs.md §Staging, rollback, and publication](../../../../prepared_epochs.md), [docs/prepared_epochs.md §Batch event and resource accounting](../../../../prepared_epochs.md) |

## B0004

[Lines 36–37](../../../../../tests/unit/support_exception_test.cpp#L36); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L36-L37:sha256:c2bd7638f09d52cb034ed574f539304035fc6fab162bf8d5fa20a35d8c7288a1
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Close the recorded declaration scopes in support_exception_test.cpp: namespace (anonymous). |
| inputs / outputs | Preceding namespace, type or initializer declarations in; completed lexical boundary out. |
| invariants | Brace-opening context is recorded in root-scope-context-v1.json. These are declaration/initializer boundaries, not an independent update, validation or recovery operation. |
| ownership | Enclosing objects and borrowed fields keep their declared ownership. This punctuation creates no new owner. |
| failure | Malformed scope syntax is a compile error. Any initializer/constructor failure belongs to the enclosing object declaration. |
| cost | No separate loop, guard or engine call is introduced by the delimiter; enclosing initialization and object lifetime still have their actual costs. |
| Design | [tests/unit/support_exception_test.cpp](../../../../../tests/unit/support_exception_test.cpp), [docs/prepared_epochs.md](../../../../prepared_epochs.md), [docs/code_review.md](../../../../code_review.md) |

## B0005

[Lines 38–38](../../../../../tests/unit/support_exception_test.cpp#L38); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void* operator new(std::size_t bytes)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Route scalar C++ allocation requests through the support test's failure countdown. |
| inputs / outputs | Callable: void* operator new(std::size_t bytes). Input: byte count. Output: pointer from allocate or std::bad_alloc. |
| invariants | Only this test executable interposes the ordinary scalar global-new overload. |
| ownership | Test plan, row, and JSON results are local owning values. Passed runtime/plan references are borrowed for the call; only an explicitly retained shared SupportJournal keeps its affected record pins beyond an epoch. |
| failure | A failed check throws std::runtime_error. The sweep catches std::bad_alloc from ordinary global-new injection around the target apply; runtime/API failures outside that catch fail the executable. |
| cost | Uses the fixed two-child plan and short fixture rows; it is a test helper, not a public work or allocation bound. |
| Design | [include/crown/runtime/support.hpp](../../../../../include/crown/runtime/support.hpp), [src/runtime/support.cpp](../../../../../src/runtime/support.cpp), [docs/support_invariants.md](../../../../support_invariants.md), [docs/prepared_epochs.md §Staging, rollback, and publication](../../../../prepared_epochs.md), [docs/prepared_epochs.md §Batch event and resource accounting](../../../../prepared_epochs.md) |

## B0006

[Lines 39–39](../../../../../tests/unit/support_exception_test.cpp#L39); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void* operator new[](std::size_t bytes)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Route array C++ allocation requests through the support test's failure countdown. |
| inputs / outputs | Callable: void* operator new\[\](std::size_t bytes). Input: byte count. Output: pointer from allocate or std::bad_alloc. |
| invariants | Only this test executable interposes the ordinary array global-new overload. |
| ownership | Test plan, row, and JSON results are local owning values. Passed runtime/plan references are borrowed for the call; only an explicitly retained shared SupportJournal keeps its affected record pins beyond an epoch. |
| failure | A failed check throws std::runtime_error. The sweep catches std::bad_alloc from ordinary global-new injection around the target apply; runtime/API failures outside that catch fail the executable. |
| cost | Uses the fixed two-child plan and short fixture rows; it is a test helper, not a public work or allocation bound. |
| Design | [include/crown/runtime/support.hpp](../../../../../include/crown/runtime/support.hpp), [src/runtime/support.cpp](../../../../../src/runtime/support.cpp), [docs/support_invariants.md](../../../../support_invariants.md), [docs/prepared_epochs.md §Staging, rollback, and publication](../../../../prepared_epochs.md), [docs/prepared_epochs.md §Batch event and resource accounting](../../../../prepared_epochs.md) |

## B0007

[Lines 40–40](../../../../../tests/unit/support_exception_test.cpp#L40); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void operator delete(void* pointer) noexcept
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Release storage allocated by the local scalar global-new replacement. |
| inputs / outputs | Callable: void operator delete(void* pointer) noexcept. Input: possibly null pointer. Output: none. |
| invariants | Deallocation calls std::free and does not consult or change fail_after. |
| ownership | Test plan, row, and JSON results are local owning values. Passed runtime/plan references are borrowed for the call; only an explicitly retained shared SupportJournal keeps its affected record pins beyond an epoch. |
| failure | A failed check throws std::runtime_error. The sweep catches std::bad_alloc from ordinary global-new injection around the target apply; runtime/API failures outside that catch fail the executable. |
| cost | Uses the fixed two-child plan and short fixture rows; it is a test helper, not a public work or allocation bound. |
| Design | [include/crown/runtime/support.hpp](../../../../../include/crown/runtime/support.hpp), [src/runtime/support.cpp](../../../../../src/runtime/support.cpp), [docs/support_invariants.md](../../../../support_invariants.md), [docs/prepared_epochs.md §Staging, rollback, and publication](../../../../prepared_epochs.md), [docs/prepared_epochs.md §Batch event and resource accounting](../../../../prepared_epochs.md) |

## B0008

[Lines 41–41](../../../../../tests/unit/support_exception_test.cpp#L41); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void operator delete[](void* pointer) noexcept
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Release storage allocated by the local array global-new replacement. |
| inputs / outputs | Callable: void operator delete\[\](void* pointer) noexcept. Input: possibly null pointer. Output: none. |
| invariants | Deallocation calls std::free and does not consult or change fail_after. |
| ownership | Test plan, row, and JSON results are local owning values. Passed runtime/plan references are borrowed for the call; only an explicitly retained shared SupportJournal keeps its affected record pins beyond an epoch. |
| failure | A failed check throws std::runtime_error. The sweep catches std::bad_alloc from ordinary global-new injection around the target apply; runtime/API failures outside that catch fail the executable. |
| cost | Uses the fixed two-child plan and short fixture rows; it is a test helper, not a public work or allocation bound. |
| Design | [include/crown/runtime/support.hpp](../../../../../include/crown/runtime/support.hpp), [src/runtime/support.cpp](../../../../../src/runtime/support.cpp), [docs/support_invariants.md](../../../../support_invariants.md), [docs/prepared_epochs.md §Staging, rollback, and publication](../../../../prepared_epochs.md), [docs/prepared_epochs.md §Batch event and resource accounting](../../../../prepared_epochs.md) |

## B0009

[Lines 42–42](../../../../../tests/unit/support_exception_test.cpp#L42); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void operator delete(void* pointer, std::size_t) noexcept
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Release sized scalar allocations from the local global-new replacement. |
| inputs / outputs | Callable: void operator delete(void* pointer, std::size_t) noexcept. Inputs: pointer and ignored object size. Output: none. |
| invariants | The sized form uses the same std::free backing and does not inspect the failure countdown. |
| ownership | Test plan, row, and JSON results are local owning values. Passed runtime/plan references are borrowed for the call; only an explicitly retained shared SupportJournal keeps its affected record pins beyond an epoch. |
| failure | A failed check throws std::runtime_error. The sweep catches std::bad_alloc from ordinary global-new injection around the target apply; runtime/API failures outside that catch fail the executable. |
| cost | Uses the fixed two-child plan and short fixture rows; it is a test helper, not a public work or allocation bound. |
| Design | [include/crown/runtime/support.hpp](../../../../../include/crown/runtime/support.hpp), [src/runtime/support.cpp](../../../../../src/runtime/support.cpp), [docs/support_invariants.md](../../../../support_invariants.md), [docs/prepared_epochs.md §Staging, rollback, and publication](../../../../prepared_epochs.md), [docs/prepared_epochs.md §Batch event and resource accounting](../../../../prepared_epochs.md) |

## B0010

[Lines 43–43](../../../../../tests/unit/support_exception_test.cpp#L43); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void operator delete[](void* pointer, std::size_t) noexcept
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Release sized array allocations from the local global-new replacement. |
| inputs / outputs | Callable: void operator delete\[\](void* pointer, std::size_t) noexcept. Inputs: pointer and ignored object size. Output: none. |
| invariants | The sized form uses the same std::free backing and does not inspect the failure countdown. |
| ownership | Test plan, row, and JSON results are local owning values. Passed runtime/plan references are borrowed for the call; only an explicitly retained shared SupportJournal keeps its affected record pins beyond an epoch. |
| failure | A failed check throws std::runtime_error. The sweep catches std::bad_alloc from ordinary global-new injection around the target apply; runtime/API failures outside that catch fail the executable. |
| cost | Uses the fixed two-child plan and short fixture rows; it is a test helper, not a public work or allocation bound. |
| Design | [include/crown/runtime/support.hpp](../../../../../include/crown/runtime/support.hpp), [src/runtime/support.cpp](../../../../../src/runtime/support.cpp), [docs/support_invariants.md](../../../../support_invariants.md), [docs/prepared_epochs.md §Staging, rollback, and publication](../../../../prepared_epochs.md), [docs/prepared_epochs.md §Batch event and resource accounting](../../../../prepared_epochs.md) |

## B0011

[Lines 44–48](../../../../../tests/unit/support_exception_test.cpp#L44); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L44-L48:sha256:8242ad734347dfc37e148e0d62e2395222d63e4c2cc8e1382655189ec4b9389d
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Prepare support_exception_test.cpp: bind local aliases/name imports. |
| inputs / outputs | Compiler-visible dependencies, names and the recorded declarations in; declarations available to the following fixture/CLI/example definitions out. |
| invariants | Declarations are scoped to this source/header and its selected ABI. Included code has its own effects; names and editable fixture values do not confer proof, admission or publication authority. |
| ownership | Aliases/includes do not create a query owner. Pointers/references/views are non-owning. Containers own their elements, which can themselves be borrowed pointers or numeric IDs. Only documented owning shared-control handles retain controls; IDs/slot-handle values do not independently keep an arena/runtime alive. |
| failure | Missing headers, ill-formed names/types, failed static assertions or active #error directives stop compilation. No runtime rejection/rollback mechanism is implemented by aliases or function prototypes. |
| cost | Preprocessing and type/constraint instantiation cost compilation. Alias/prototype syntax does not invoke the declared operation; any included definitions keep their own initialization effects. |
| Design | [tests/unit/support_exception_test.cpp](../../../../../tests/unit/support_exception_test.cpp), [docs/prepared_epochs.md](../../../../prepared_epochs.md), [docs/code_review.md](../../../../code_review.md) |

## B0012

[Lines 49–51](../../../../../tests/unit/support_exception_test.cpp#L49); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void check(bool value, const std::string& message)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Turn a failed support-test expectation into a labeled exception. |
| inputs / outputs | Callable: void check(bool value, const std::string& message). Inputs: Boolean condition and message. Output: none on success; false throws std::runtime_error. |
| invariants | The assertion remains active in all build modes because it is an ordinary conditional. |
| ownership | Test plan, row, and JSON results are local owning values. Passed runtime/plan references are borrowed for the call; only an explicitly retained shared SupportJournal keeps its affected record pins beyond an epoch. |
| failure | A failed check throws std::runtime_error. The sweep catches std::bad_alloc from ordinary global-new injection around the target apply; runtime/API failures outside that catch fail the executable. |
| cost | Uses the fixed two-child plan and short fixture rows; it is a test helper, not a public work or allocation bound. |
| Design | [include/crown/runtime/support.hpp](../../../../../include/crown/runtime/support.hpp), [src/runtime/support.cpp](../../../../../src/runtime/support.cpp), [docs/support_invariants.md](../../../../support_invariants.md), [docs/prepared_epochs.md §Staging, rollback, and publication](../../../../prepared_epochs.md), [docs/prepared_epochs.md §Batch event and resource accounting](../../../../prepared_epochs.md) |

## B0013

[Lines 52–52](../../../../../tests/unit/support_exception_test.cpp#L52); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Value n(std::int64_t value)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Build an int64 Value for the support plan and update fixtures. |
| inputs / outputs | Callable: Value n(std::int64_t value). Input: signed 64-bit integer. Output: Value containing that integer. |
| invariants | The helper performs no range conversion beyond the Value alternative. |
| ownership | Test plan, row, and JSON results are local owning values. Passed runtime/plan references are borrowed for the call; only an explicitly retained shared SupportJournal keeps its affected record pins beyond an epoch. |
| failure | A failed check throws std::runtime_error. The sweep catches std::bad_alloc from ordinary global-new injection around the target apply; runtime/API failures outside that catch fail the executable. |
| cost | Uses the fixed two-child plan and short fixture rows; it is a test helper, not a public work or allocation bound. |
| Design | [include/crown/runtime/support.hpp](../../../../../include/crown/runtime/support.hpp), [src/runtime/support.cpp](../../../../../src/runtime/support.cpp), [docs/support_invariants.md](../../../../support_invariants.md), [docs/prepared_epochs.md §Staging, rollback, and publication](../../../../prepared_epochs.md), [docs/prepared_epochs.md §Batch event and resource accounting](../../../../prepared_epochs.md) |

## B0014

[Lines 53–53](../../../../../tests/unit/support_exception_test.cpp#L53); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Value s(std::string value)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Build a string Value for the support plan and update fixtures. |
| inputs / outputs | Callable: Value s(std::string value). Input: owning string. Output: Value containing the moved string. |
| invariants | The returned Value owns the string bytes. |
| ownership | Test plan, row, and JSON results are local owning values. Passed runtime/plan references are borrowed for the call; only an explicitly retained shared SupportJournal keeps its affected record pins beyond an epoch. |
| failure | A failed check throws std::runtime_error. The sweep catches std::bad_alloc from ordinary global-new injection around the target apply; runtime/API failures outside that catch fail the executable. |
| cost | Uses the fixed two-child plan and short fixture rows; it is a test helper, not a public work or allocation bound. |
| Design | [include/crown/runtime/support.hpp](../../../../../include/crown/runtime/support.hpp), [src/runtime/support.cpp](../../../../../src/runtime/support.cpp), [docs/support_invariants.md](../../../../support_invariants.md), [docs/prepared_epochs.md §Staging, rollback, and publication](../../../../prepared_epochs.md), [docs/prepared_epochs.md §Batch event and resource accounting](../../../../prepared_epochs.md) |

## B0015

[Lines 54–54](../../../../../tests/unit/support_exception_test.cpp#L54); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::string padded(char value)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Create the fixed-width string payload used to make support journal rows nontrivial. |
| inputs / outputs | Callable: std::string padded(char value). Input: fill character. Output: a 180-character string. |
| invariants | Every call uses the same width; the helper adds no suffix or normalization. |
| ownership | Test plan, row, and JSON results are local owning values. Passed runtime/plan references are borrowed for the call; only an explicitly retained shared SupportJournal keeps its affected record pins beyond an epoch. |
| failure | A failed check throws std::runtime_error. The sweep catches std::bad_alloc from ordinary global-new injection around the target apply; runtime/API failures outside that catch fail the executable. |
| cost | Uses the fixed two-child plan and short fixture rows; it is a test helper, not a public work or allocation bound. |
| Design | [include/crown/runtime/support.hpp](../../../../../include/crown/runtime/support.hpp), [src/runtime/support.cpp](../../../../../src/runtime/support.cpp), [docs/support_invariants.md](../../../../support_invariants.md), [docs/prepared_epochs.md §Staging, rollback, and publication](../../../../prepared_epochs.md), [docs/prepared_epochs.md §Batch event and resource accounting](../../../../prepared_epochs.md) |

## B0017

[Lines 56–70](../../../../../tests/unit/support_exception_test.cpp#L56); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
PhysicalPlan make_plan()
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Lower one two-child generalized support tree for the allocation rollback scenarios. |
| inputs / outputs | Callable: PhysicalPlan make_plan(). Input: none. Output: a PhysicalPlan with R and S native children sharing x and a root projection of x. |
| invariants | Rows with x=10 can acquire support from both children; the unrelated x=99 row does not produce the root answer. |
| ownership | Test plan, row, and JSON results are local owning values. Passed runtime/plan references are borrowed for the call; only an explicitly retained shared SupportJournal keeps its affected record pins beyond an epoch. |
| failure | A failed check throws std::runtime_error. The sweep catches std::bad_alloc from ordinary global-new injection around the target apply; runtime/API failures outside that catch fail the executable. |
| cost | Uses the fixed two-child plan and short fixture rows; it is a test helper, not a public work or allocation bound. |
| Design | [include/crown/runtime/support.hpp](../../../../../include/crown/runtime/support.hpp), [src/runtime/support.cpp](../../../../../src/runtime/support.cpp), [docs/support_invariants.md](../../../../support_invariants.md), [docs/prepared_epochs.md §Staging, rollback, and publication](../../../../prepared_epochs.md), [docs/prepared_epochs.md §Batch event and resource accounting](../../../../prepared_epochs.md) |

## B0019

[Lines 72–77](../../../../../tests/unit/support_exception_test.cpp#L72); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
enum class Case
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Name the four support transitions whose allocation failures are swept. |
| inputs / outputs | Type: enum class Case. Values: last-child insertion, supported-child erase, redundant-child-support erase, and candidate reclaim. |
| invariants | The four enum values select the setup and single target update used by sweep. |
| ownership | Test plan, row, and JSON results are local owning values. Passed runtime/plan references are borrowed for the call; only an explicitly retained shared SupportJournal keeps its affected record pins beyond an epoch. |
| failure | A failed check throws std::runtime_error. The sweep catches std::bad_alloc from ordinary global-new injection around the target apply; runtime/API failures outside that catch fail the executable. |
| cost | Uses the fixed two-child plan and short fixture rows; it is a test helper, not a public work or allocation bound. |
| Design | [include/crown/runtime/support.hpp](../../../../../include/crown/runtime/support.hpp), [src/runtime/support.cpp](../../../../../src/runtime/support.cpp), [docs/support_invariants.md](../../../../support_invariants.md), [docs/prepared_epochs.md §Staging, rollback, and publication](../../../../prepared_epochs.md), [docs/prepared_epochs.md §Batch event and resource accounting](../../../../prepared_epochs.md) |

## B0020

[Lines 78–86](../../../../../tests/unit/support_exception_test.cpp#L78); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
const char* case_name(Case value)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Render one support fault-sweep case as its stable diagnostic label. |
| inputs / outputs | Callable: const char* case_name(Case value). Input: Case. Output: the matching lowercase case name, or unknown for an invalid enum value. |
| invariants | The returned string literals are static and do not own per-call storage. |
| ownership | Test plan, row, and JSON results are local owning values. Passed runtime/plan references are borrowed for the call; only an explicitly retained shared SupportJournal keeps its affected record pins beyond an epoch. |
| failure | A failed check throws std::runtime_error. The sweep catches std::bad_alloc from ordinary global-new injection around the target apply; runtime/API failures outside that catch fail the executable. |
| cost | Uses the fixed two-child plan and short fixture rows; it is a test helper, not a public work or allocation bound. |
| Design | [include/crown/runtime/support.hpp](../../../../../include/crown/runtime/support.hpp), [src/runtime/support.cpp](../../../../../src/runtime/support.cpp), [docs/support_invariants.md](../../../../support_invariants.md), [docs/prepared_epochs.md §Staging, rollback, and publication](../../../../prepared_epochs.md), [docs/prepared_epochs.md §Batch event and resource accounting](../../../../prepared_epochs.md) |

## B0022

[Lines 88–92](../../../../../tests/unit/support_exception_test.cpp#L88); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
SupportOptions options()
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Enable transition capture for the support rollback fixture. |
| inputs / outputs | Callable: SupportOptions options(). Input: none. Output: default SupportOptions with capture_transitions set true. |
| invariants | No additional work, row, or memory cap is installed by this helper. |
| ownership | Test plan, row, and JSON results are local owning values. Passed runtime/plan references are borrowed for the call; only an explicitly retained shared SupportJournal keeps its affected record pins beyond an epoch. |
| failure | A failed check throws std::runtime_error. The sweep catches std::bad_alloc from ordinary global-new injection around the target apply; runtime/API failures outside that catch fail the executable. |
| cost | Uses the fixed two-child plan and short fixture rows; it is a test helper, not a public work or allocation bound. |
| Design | [include/crown/runtime/support.hpp](../../../../../include/crown/runtime/support.hpp), [src/runtime/support.cpp](../../../../../src/runtime/support.cpp), [docs/support_invariants.md](../../../../support_invariants.md), [docs/prepared_epochs.md §Staging, rollback, and publication](../../../../prepared_epochs.md), [docs/prepared_epochs.md §Batch event and resource accounting](../../../../prepared_epochs.md) |

## B0024

[Lines 94–108](../../../../../tests/unit/support_exception_test.cpp#L94); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::vector<NativeSetUpdate> setup_updates(Case which)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Build the finite initial native update prefix for one rollback case. |
| inputs / outputs | Callable: std::vector&lt;NativeSetUpdate&gt; setup_updates(Case which). Input: selected Case. Output: one S insert for reclaim, otherwise three R inserts and optionally one S insert. |
| invariants | Sequences are fixed and contiguous within each returned setup list; the x=99 R row is unrelated to the root answer. |
| ownership | Test plan, row, and JSON results are local owning values. Passed runtime/plan references are borrowed for the call; only an explicitly retained shared SupportJournal keeps its affected record pins beyond an epoch. |
| failure | A failed check throws std::runtime_error. The sweep catches std::bad_alloc from ordinary global-new injection around the target apply; runtime/API failures outside that catch fail the executable. |
| cost | Uses the fixed two-child plan and short fixture rows; it is a test helper, not a public work or allocation bound. |
| Design | [include/crown/runtime/support.hpp](../../../../../include/crown/runtime/support.hpp), [src/runtime/support.cpp](../../../../../src/runtime/support.cpp), [docs/support_invariants.md](../../../../support_invariants.md), [docs/prepared_epochs.md §Staging, rollback, and publication](../../../../prepared_epochs.md), [docs/prepared_epochs.md §Batch event and resource accounting](../../../../prepared_epochs.md) |

## B0026

[Lines 110–120](../../../../../tests/unit/support_exception_test.cpp#L110); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
NativeSetUpdate target_update(Case which)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Choose the one allocation-swept native update for a support case. |
| inputs / outputs | Callable: NativeSetUpdate target_update(Case which). Input: Case. Output: the matching insert or erase at sequence 4, 5, or 2. |
| invariants | Supported-child deletion retains R support; redundant-support deletion leaves a second R row; reclaim erases the only S support. |
| ownership | Test plan, row, and JSON results are local owning values. Passed runtime/plan references are borrowed for the call; only an explicitly retained shared SupportJournal keeps its affected record pins beyond an epoch. |
| failure | An unsupported Case reaches the explicit unknown-case std::runtime_error; normal target sequences are fixed by the four enumerators. |
| cost | Uses the fixed two-child plan and short fixture rows; it is a test helper, not a public work or allocation bound. |
| Design | [include/crown/runtime/support.hpp](../../../../../include/crown/runtime/support.hpp), [src/runtime/support.cpp](../../../../../src/runtime/support.cpp), [docs/support_invariants.md](../../../../support_invariants.md), [docs/prepared_epochs.md §Staging, rollback, and publication](../../../../prepared_epochs.md), [docs/prepared_epochs.md §Batch event and resource accounting](../../../../prepared_epochs.md) |

## B0028

[Lines 122–133](../../../../../tests/unit/support_exception_test.cpp#L122); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::shared_ptr<const SupportJournal> initialize(SupportRuntime& runtime, Case which)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Apply the case's setup prefix and retain its last affected-record journal. |
| inputs / outputs | Callable: std::shared_ptr&lt;const SupportJournal&gt; initialize(SupportRuntime& runtime, Case which). Inputs: mutable SupportRuntime and Case. Output: shared immutable SupportJournal from the last setup epoch. |
| invariants | Every setup step must change a native set and expose a nonempty journal before the runtime invariant check passes. |
| ownership | Test plan, row, and JSON results are local owning values. Passed runtime/plan references are borrowed for the call; only an explicitly retained shared SupportJournal keeps its affected record pins beyond an epoch. |
| failure | A failed check throws std::runtime_error. The sweep catches std::bad_alloc from ordinary global-new injection around the target apply; runtime/API failures outside that catch fail the executable. |
| cost | Uses the fixed two-child plan and short fixture rows; it is a test helper, not a public work or allocation bound. |
| Design | [include/crown/runtime/support.hpp](../../../../../include/crown/runtime/support.hpp), [src/runtime/support.cpp](../../../../../src/runtime/support.cpp), [docs/support_invariants.md](../../../../support_invariants.md), [docs/prepared_epochs.md §Staging, rollback, and publication](../../../../prepared_epochs.md), [docs/prepared_epochs.md §Batch event and resource accounting](../../../../prepared_epochs.md) |

## B0030

[Lines 135–147](../../../../../tests/unit/support_exception_test.cpp#L135); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
io::Json normalized_snapshot(const SupportRuntime& runtime, const PhysicalPlan& plan)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Serialize a support snapshot while removing runtime-owner values from handle JSON for repeatable comparison. |
| inputs / outputs | Callable: io::Json normalized_snapshot(const SupportRuntime& runtime, const PhysicalPlan& plan). Inputs: runtime and plan. Output: owning JSON snapshot with handle owner fields set to zero. |
| invariants | Logical tuple IDs, values, support roles, counts, and record ordering remain part of the comparison. |
| ownership | The serializer creates an owning JSON snapshot from the runtime; the plan/runtime remain borrowed for the call. |
| failure | A failed check throws std::runtime_error. The sweep catches std::bad_alloc from ordinary global-new injection around the target apply; runtime/API failures outside that catch fail the executable. |
| cost | Visits and serializes the finite support snapshot, then walks its node records and support-key arrays to zero owner fields. |
| Design | [include/crown/runtime/support.hpp](../../../../../include/crown/runtime/support.hpp), [src/runtime/support.cpp](../../../../../src/runtime/support.cpp), [docs/support_invariants.md](../../../../support_invariants.md), [docs/prepared_epochs.md §Staging, rollback, and publication](../../../../prepared_epochs.md), [docs/prepared_epochs.md §Batch event and resource accounting](../../../../prepared_epochs.md) |

## B0032

[Lines 149–163](../../../../../tests/unit/support_exception_test.cpp#L149); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
io::Json normalized_epoch(const SupportEpoch& epoch)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Serialize a support epoch while normalizing owner identifiers in every nested handle. |
| inputs / outputs | Callable: io::Json normalized_epoch(const SupportEpoch& epoch). Input: SupportEpoch. Output: owning JSON epoch with owner fields recursively set to zero. |
| invariants | Transition and journal ordinals, event causes, and non-owner fields are preserved. |
| ownership | The writer creates an owning JSON value; the source SupportEpoch is borrowed and unchanged. |
| failure | A failed check throws std::runtime_error. The sweep catches std::bad_alloc from ordinary global-new injection around the target apply; runtime/API failures outside that catch fail the executable. |
| cost | Walks the serialized finite epoch JSON recursively once to normalize owner fields. |
| Design | [include/crown/runtime/support.hpp](../../../../../include/crown/runtime/support.hpp), [src/runtime/support.cpp](../../../../../src/runtime/support.cpp), [docs/support_invariants.md](../../../../support_invariants.md), [docs/prepared_epochs.md §Staging, rollback, and publication](../../../../prepared_epochs.md), [docs/prepared_epochs.md §Batch event and resource accounting](../../../../prepared_epochs.md) |

## B0034

[Lines 165–171](../../../../../tests/unit/support_exception_test.cpp#L165); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct JournalValue
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Keep a comparable copy of one retained support journal record's layout identity and row values. |
| inputs / outputs | Type: struct JournalValue. Fields: AccountedLayout token plus owning exported Row. Equality requires both the same layout token and equal values. |
| invariants | This projection compares payload lifetime without retaining the SupportJournal itself. |
| ownership | AccountedLayout retains the native layout token, while exported Row owns copied scalar/string values. |
| failure | A failed check throws std::runtime_error. The sweep catches std::bad_alloc from ordinary global-new injection around the target apply; runtime/API failures outside that catch fail the executable. |
| cost | Uses the fixed two-child plan and short fixture rows; it is a test helper, not a public work or allocation bound. |
| Design | [include/crown/runtime/support.hpp](../../../../../include/crown/runtime/support.hpp), [src/runtime/support.cpp](../../../../../src/runtime/support.cpp), [docs/support_invariants.md](../../../../support_invariants.md), [docs/prepared_epochs.md §Staging, rollback, and publication](../../../../prepared_epochs.md), [docs/prepared_epochs.md §Batch event and resource accounting](../../../../prepared_epochs.md) |

## B0036

[Lines 173–179](../../../../../tests/unit/support_exception_test.cpp#L173); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::vector<JournalValue> retained_values(const std::shared_ptr<const SupportJournal>& journal)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Copy all retained support journal payloads into test-owned layout/value pairs. |
| inputs / outputs | Callable: std::vector&lt;JournalValue&gt; retained_values(const std::shared_ptr&lt;const SupportJournal&gt;& journal). Input: shared immutable SupportJournal. Output: one JournalValue per journal record. |
| invariants | The helper rejects a null journal and compares full row values under the retained original layout token. |
| ownership | The returned vector owns copied row values and shared layout tokens; it does not own or extend the source SupportJournal. |
| failure | A failed check throws std::runtime_error. The sweep catches std::bad_alloc from ordinary global-new injection around the target apply; runtime/API failures outside that catch fail the executable. |
| cost | Reserves once for journal record count and copies one layout token plus row values per record. |
| Design | [include/crown/runtime/support.hpp](../../../../../include/crown/runtime/support.hpp), [src/runtime/support.cpp](../../../../../src/runtime/support.cpp), [docs/support_invariants.md](../../../../support_invariants.md), [docs/prepared_epochs.md §Staging, rollback, and publication](../../../../prepared_epochs.md), [docs/prepared_epochs.md §Batch event and resource accounting](../../../../prepared_epochs.md) |

## B0038

[Lines 181–187](../../../../../tests/unit/support_exception_test.cpp#L181); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void check_rollback_statistics(const storage::ArenaStatistics& before,
                               const storage::ArenaStatistics& after,
                               const std::string& context)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Compare the support arena counters that this failure test promises to restore. |
| inputs / outputs | Callable: void check_rollback_statistics(const storage::ArenaStatistics& before, const storage::ArenaStatistics& after, const std::string& context). Inputs: before/after ArenaStatistics and context label. Output: none when pins, live records, and retained records match. |
| invariants | Slot high-water or generation history is not part of this assertion. |
| ownership | Test plan, row, and JSON results are local owning values. Passed runtime/plan references are borrowed for the call; only an explicitly retained shared SupportJournal keeps its affected record pins beyond an epoch. |
| failure | A failed check throws std::runtime_error. The sweep catches std::bad_alloc from ordinary global-new injection around the target apply; runtime/API failures outside that catch fail the executable. |
| cost | Uses the fixed two-child plan and short fixture rows; it is a test helper, not a public work or allocation bound. |
| Design | [include/crown/runtime/support.hpp](../../../../../include/crown/runtime/support.hpp), [src/runtime/support.cpp](../../../../../src/runtime/support.cpp), [docs/support_invariants.md](../../../../support_invariants.md), [docs/prepared_epochs.md §Staging, rollback, and publication](../../../../prepared_epochs.md), [docs/prepared_epochs.md §Batch event and resource accounting](../../../../prepared_epochs.md) |

## B0040

[Lines 189–193](../../../../../tests/unit/support_exception_test.cpp#L189); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct LiveHandle
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Store one public support handle with its copied resolved tuple for rollback comparisons. |
| inputs / outputs | Type: struct LiveHandle. Fields: SupportHandle and storage::Tuple. Default equality compares both stored values. |
| invariants | The tuple is a test-owned value; handle identity remains owner/node/role/tuple-ID based. |
| ownership | The stored SupportHandle is an identity value; the storage::Tuple owns its copied native tuple payload. |
| failure | A failed check throws std::runtime_error. The sweep catches std::bad_alloc from ordinary global-new injection around the target apply; runtime/API failures outside that catch fail the executable. |
| cost | Uses the fixed two-child plan and short fixture rows; it is a test helper, not a public work or allocation bound. |
| Design | [include/crown/runtime/support.hpp](../../../../../include/crown/runtime/support.hpp), [src/runtime/support.cpp](../../../../../src/runtime/support.cpp), [docs/support_invariants.md](../../../../support_invariants.md), [docs/prepared_epochs.md §Staging, rollback, and publication](../../../../prepared_epochs.md), [docs/prepared_epochs.md §Batch event and resource accounting](../../../../prepared_epochs.md) |

## B0042

[Lines 195–215](../../../../../tests/unit/support_exception_test.cpp#L195); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::vector<LiveHandle> public_handles(const SupportRuntime& runtime)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Enumerate every public handle reachable from a support snapshot and copy its resolved tuple. |
| inputs / outputs | Callable: std::vector&lt;LiveHandle&gt; public_handles(const SupportRuntime& runtime). Input: const SupportRuntime. Output: record, survivor, parent-support, and optional visible handles with their owned tuple values. |
| invariants | Each candidate handle must resolve through runtime.get or runtime.find to the tuple represented by its snapshot row/key. |
| ownership | Test plan, row, and JSON results are local owning values. Passed runtime/plan references are borrowed for the call; only an explicitly retained shared SupportJournal keeps its affected record pins beyond an epoch. |
| failure | A failed check throws std::runtime_error. The sweep catches std::bad_alloc from ordinary global-new injection around the target apply; runtime/API failures outside that catch fail the executable. |
| cost | Walks all snapshot nodes, records, survivor rows, and parent/visible keys, resolving each exposed handle. |
| Design | [include/crown/runtime/support.hpp](../../../../../include/crown/runtime/support.hpp), [src/runtime/support.cpp](../../../../../src/runtime/support.cpp), [docs/support_invariants.md](../../../../support_invariants.md), [docs/prepared_epochs.md §Staging, rollback, and publication](../../../../prepared_epochs.md), [docs/prepared_epochs.md §Batch event and resource accounting](../../../../prepared_epochs.md) |

## B0044

[Lines 217–221](../../../../../tests/unit/support_exception_test.cpp#L217); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct ExpectedResult
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Hold the clean-run oracle values used to compare one fault-sweep retry. |
| inputs / outputs | Type: struct ExpectedResult. Fields: normalized snapshot JSON, normalized epoch JSON, and answer-presence Boolean. |
| invariants | The result owns its JSON data and contains only the selected finite case's output. |
| ownership | Both JSON values own their serialized data and do not retain the runtime. |
| failure | A failed check throws std::runtime_error. The sweep catches std::bad_alloc from ordinary global-new injection around the target apply; runtime/API failures outside that catch fail the executable. |
| cost | Uses the fixed two-child plan and short fixture rows; it is a test helper, not a public work or allocation bound. |
| Design | [include/crown/runtime/support.hpp](../../../../../include/crown/runtime/support.hpp), [src/runtime/support.cpp](../../../../../src/runtime/support.cpp), [docs/support_invariants.md](../../../../support_invariants.md), [docs/prepared_epochs.md §Staging, rollback, and publication](../../../../prepared_epochs.md), [docs/prepared_epochs.md §Batch event and resource accounting](../../../../prepared_epochs.md) |

## B0046

[Lines 223–230](../../../../../tests/unit/support_exception_test.cpp#L223); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
ExpectedResult clean_result(const PhysicalPlan& plan, Case which)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Run a case once without injection to build its expected snapshot, epoch, and answer state. |
| inputs / outputs | Callable: ExpectedResult clean_result(const PhysicalPlan& plan, Case which). Inputs: plan and Case. Output: owning ExpectedResult after setup, target apply, and invariant validation. |
| invariants | The reference is a clean execution of this same fixture path, not an independent general support oracle. |
| ownership | Test plan, row, and JSON results are local owning values. Passed runtime/plan references are borrowed for the call; only an explicitly retained shared SupportJournal keeps its affected record pins beyond an epoch. |
| failure | A failed check throws std::runtime_error. The sweep catches std::bad_alloc from ordinary global-new injection around the target apply; runtime/API failures outside that catch fail the executable. |
| cost | Uses the fixed two-child plan and short fixture rows; it is a test helper, not a public work or allocation bound. |
| Design | [include/crown/runtime/support.hpp](../../../../../include/crown/runtime/support.hpp), [src/runtime/support.cpp](../../../../../src/runtime/support.cpp), [docs/support_invariants.md](../../../../support_invariants.md), [docs/prepared_epochs.md §Staging, rollback, and publication](../../../../prepared_epochs.md), [docs/prepared_epochs.md §Batch event and resource accounting](../../../../prepared_epochs.md) |

## B0048

[Lines 232–297](../../../../../tests/unit/support_exception_test.cpp#L232); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void check_expected_state(const SupportRuntime& runtime, Case which, const SupportEpoch& epoch)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Assert the four hand-built support transitions and their affected-record metrics. |
| inputs / outputs | Callable: void check_expected_state(const SupportRuntime& runtime, Case which, const SupportEpoch& epoch). Inputs: runtime, Case, and resulting epoch. Output: none if each case's local support state matches. |
| invariants | Assertions distinguish last-child insertion, supported deletion, decrement from two supports to one, and zero-support candidate reclaim. |
| ownership | Test plan, row, and JSON results are local owning values. Passed runtime/plan references are borrowed for the call; only an explicitly retained shared SupportJournal keeps its affected record pins beyond an epoch. |
| failure | A failed check throws std::runtime_error. The sweep catches std::bad_alloc from ordinary global-new injection around the target apply; runtime/API failures outside that catch fail the executable. |
| cost | Inspects the selected node snapshots and exact transition counters for one of four fixed cases. |
| Design | [include/crown/runtime/support.hpp](../../../../../include/crown/runtime/support.hpp), [src/runtime/support.cpp](../../../../../src/runtime/support.cpp), [docs/support_invariants.md](../../../../support_invariants.md), [docs/prepared_epochs.md §Staging, rollback, and publication](../../../../prepared_epochs.md), [docs/prepared_epochs.md §Batch event and resource accounting](../../../../prepared_epochs.md) |

## B0050

[Lines 299–373](../../../../../tests/unit/support_exception_test.cpp#L299); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::size_t sweep(const PhysicalPlan& plan, Case which)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Inject ordinary global-new failures through one support apply, verify rollback, then retry the same sequence. |
| inputs / outputs | Callable: std::size_t sweep(const PhysicalPlan& plan, Case which). Inputs: plan and Case. Output: number of failed injection positions before the first successful apply. |
| invariants | Each failure must preserve sequence, answer, owner, snapshot IDs, public handles, selected arena counters, and an earlier journal's pinned values; retry must match the clean epoch and work metric. |
| ownership | Each iteration owns a fresh SupportRuntime and local rollback snapshot; previous_journal explicitly retains only its affected tuple pins during retry. |
| failure | Only std::bad_alloc from the target apply is classified as an injected failure; mismatch checks, invariant errors, and nonallocation failures abort the test rather than being retried. |
| cost | At most 2048 fresh runtime setup/apply attempts per Case, repeated for four Cases; every failed attempt performs snapshot, handle, statistics, journal-value, and invariant checks before a same-sequence retry. |
| Design | [tests/unit/support_exception_test.cpp](../../../../../tests/unit/support_exception_test.cpp), [src/runtime/support.cpp](../../../../../src/runtime/support.cpp), [docs/support_invariants.md](../../../../support_invariants.md) |

## B0052

[Lines 375–411](../../../../../tests/unit/support_exception_test.cpp#L375); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void check_journal_survives_runtime_destruction(const PhysicalPlan& plan)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Verify that an earlier support journal keeps its affected source tuple readable across a later erase and runtime destruction. |
| inputs / outputs | Callable: void check_journal_survives_runtime_destruction(const PhysicalPlan& plan). Input: plan. Output: none after source-row value checks before and after owner lifetime ends. |
| invariants | The retained shared journal owns its record pins; it does not freeze unrelated runtime state. |
| ownership | The shared immutable SupportJournal owns affected record pins across the later erase and the SupportRuntime's lifetime; the plan remains borrowed. |
| failure | A failed check throws std::runtime_error. The sweep catches std::bad_alloc from ordinary global-new injection around the target apply; runtime/API failures outside that catch fail the executable. |
| cost | Two native updates plus linear searches over the retained journal records before and after the runtime scope. |
| Design | [tests/unit/support_exception_test.cpp](../../../../../tests/unit/support_exception_test.cpp), [include/crown/runtime/support.hpp](../../../../../include/crown/runtime/support.hpp), [docs/support_invariants.md](../../../../support_invariants.md) |

## B0053

[Lines 412–413](../../../../../tests/unit/support_exception_test.cpp#L412); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L412-L413:sha256:c2bd7638f09d52cb034ed574f539304035fc6fab162bf8d5fa20a35d8c7288a1
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Close the recorded declaration scopes in support_exception_test.cpp: namespace (anonymous). |
| inputs / outputs | Preceding namespace, type or initializer declarations in; completed lexical boundary out. |
| invariants | Brace-opening context is recorded in root-scope-context-v1.json. These are declaration/initializer boundaries, not an independent update, validation or recovery operation. |
| ownership | Enclosing objects and borrowed fields keep their declared ownership. This punctuation creates no new owner. |
| failure | Malformed scope syntax is a compile error. Any initializer/constructor failure belongs to the enclosing object declaration. |
| cost | No separate loop, guard or engine call is introduced by the delimiter; enclosing initialization and object lifetime still have their actual costs. |
| Design | [tests/unit/support_exception_test.cpp](../../../../../tests/unit/support_exception_test.cpp), [docs/prepared_epochs.md](../../../../prepared_epochs.md), [docs/code_review.md](../../../../code_review.md) |

## B0054

[Lines 414–433](../../../../../tests/unit/support_exception_test.cpp#L414); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
int main()
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Run the four support allocation sweeps and retained-journal lifetime case. |
| inputs / outputs | Callable: int main(). Input: none. Output: zero after printing per-case failure counts, or one after reporting the first exception. |
| invariants | The exercised state space is exactly the four Case values and the fixed plan/data fixtures in this executable. |
| ownership | Test plan, row, and JSON results are local owning values. Passed runtime/plan references are borrowed for the call; only an explicitly retained shared SupportJournal keeps its affected record pins beyond an epoch. |
| failure | A failed check throws std::runtime_error. The sweep catches std::bad_alloc from ordinary global-new injection around the target apply; runtime/API failures outside that catch fail the executable. |
| cost | Runs four separately capped 2048-position sweeps and one journal-lifetime scenario; no timing is measured. |
| Design | [tests/unit/support_exception_test.cpp](../../../../../tests/unit/support_exception_test.cpp), [docs/support_invariants.md](../../../../support_invariants.md), [docs/prepared_epochs.md §Staging, rollback, and publication](../../../../prepared_epochs.md) |
