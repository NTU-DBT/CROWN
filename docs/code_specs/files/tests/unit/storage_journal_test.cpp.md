# `tests/unit/storage_journal_test.cpp` — block usage map

[Source](../../../../../tests/unit/storage_journal_test.cpp) · [Source index](../../../README.md) · [Subsystem contracts](../../../subsystem_contracts.md) · [Reviewed primitives](../../../primitives.md)

Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection.

Snapshot SHA-256: `b5c71035598bcc3a79d229df24a3fd83288db970f4c6605d2450e413e0e05740`. 775 lines partitioned into 55 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [tests](../../../subsystem_contracts.md#tests). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/code_review.md](../../../../code_review.md), [docs/reference_fuzz.md](../../../../reference_fuzz.md), [docs/task_ledger.md](../../../../task_ledger.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–25](../../../../../tests/unit/storage_journal_test.cpp#L1) | Imports dependencies; declares namespace scope; declares values/defaults or compile-time conditions. | growth new; source comment (unverified): // This test is its own binary so allocation tracking cannot affect other tests. · [reviewed contract](#b0001) |
| [B0002 · 26–32](../../../../../tests/unit/storage_journal_test.cpp#L26) | Callable definition: \[\[gnu::noinline\]\] void* allocate(std::size_t bytes) | calls std::malloc; returns result; growth allocate, malloc · [reviewed contract](#b0002) |
| [B0003 · 33–34](../../../../../tests/unit/storage_journal_test.cpp#L33) | Closes surrounding scope/type. | source comment (unverified): // namespace · [reviewed contract](#b0003) |
| [B0004 · 35–35](../../../../../tests/unit/storage_journal_test.cpp#L35) | Callable definition: void* operator new(std::size_t bytes) | calls allocate; returns allocate(bytes); growth allocate, new · [reviewed contract](#b0004) |
| [B0005 · 36–36](../../../../../tests/unit/storage_journal_test.cpp#L36) | Callable definition: void* operator new\[\](std::size_t bytes) | calls ; returns allocate(bytes); growth allocate, new · [reviewed contract](#b0005) |
| [B0006 · 37–37](../../../../../tests/unit/storage_journal_test.cpp#L37) | Callable definition: void operator delete(void* pointer) noexcept | calls std::free · [reviewed contract](#b0006) |
| [B0007 · 38–38](../../../../../tests/unit/storage_journal_test.cpp#L38) | Callable definition: void operator delete\[\](void* pointer) noexcept | calls  · [reviewed contract](#b0007) |
| [B0008 · 39–39](../../../../../tests/unit/storage_journal_test.cpp#L39) | Callable definition: void operator delete(void* pointer, std::size_t) noexcept | calls std::free · [reviewed contract](#b0008) |
| [B0009 · 40–40](../../../../../tests/unit/storage_journal_test.cpp#L40) | Callable definition: void operator delete\[\](void* pointer, std::size_t) noexcept | calls  · [reviewed contract](#b0009) |
| [B0010 · 41–47](../../../../../tests/unit/storage_journal_test.cpp#L41) | declares namespace scope; declares aliases; declares values/defaults or compile-time conditions. |  · [reviewed contract](#b0010) |
| [B0011 · 48–50](../../../../../tests/unit/storage_journal_test.cpp#L48) | Callable definition: void check(bool condition, const std::string& message) | calls std::runtime_error; guard void check(bool condition, const std::string& message) { · [reviewed contract](#b0011) |
| [B0012 · 51–51](../../../../../tests/unit/storage_journal_test.cpp#L51) | Explanatory comments or spacing. |  |
| [B0013 · 52–61](../../../../../tests/unit/storage_journal_test.cpp#L52) | Callable definition: template &lt;class Action&gt; void expect_error(Action&& action, std::string_view code) | calls check, code, std::runtime_error, std::string; guard check(failure.code() == code, "wrong storage error: " + failure.code()); · [reviewed contract](#b0013) |
| [B0014 · 62–62](../../../../../tests/unit/storage_journal_test.cpp#L62) | Explanatory comments or spacing. |  |
| [B0015 · 63–78](../../../../../tests/unit/storage_journal_test.cpp#L63) | Callable definition: template &lt;class Action&gt; std::size_t count_allocations(Action&& action) | calls ; returns tracked_allocations · [reviewed contract](#b0015) |
| [B0016 · 79–79](../../../../../tests/unit/storage_journal_test.cpp#L79) | Explanatory comments or spacing. |  |
| [B0017 · 80–86](../../../../../tests/unit/storage_journal_test.cpp#L80) | Type/record definition: class AllocationFailureScope |  · [reviewed contract](#b0017) |
| [B0018 · 87–87](../../../../../tests/unit/storage_journal_test.cpp#L87) | Explanatory comments or spacing. |  |
| [B0019 · 88–93](../../../../../tests/unit/storage_journal_test.cpp#L88) | Callable definition: TupleLayout source_layout() | calls ; returns TupleLayout{LayoutId{1}, · [reviewed contract](#b0019) |
| [B0020 · 94–94](../../../../../tests/unit/storage_journal_test.cpp#L94) | Explanatory comments or spacing. |  |
| [B0021 · 95–99](../../../../../tests/unit/storage_journal_test.cpp#L95) | Callable definition: Row sample_row(std::int64_t integer, std::string text, bool flag, std::string_view day, std::string_view amount) | calls std::move, Date::parse, Decimal::parse; returns Row{Value{integer}, Value{std::move(text)}, Value{flag}, · [reviewed contract](#b0021) |
| [B0022 · 100–100](../../../../../tests/unit/storage_journal_test.cpp#L100) | Explanatory comments or spacing. |  |
| [B0023 · 101–106](../../../../../tests/unit/storage_journal_test.cpp#L101) | Callable definition: std::vector&lt;FieldId&gt; fields_for(const std::vector&lt;std::size_t&gt;& slots) | calls reserve, size, push_back; returns fields; growth push_back, reserve; 1 loop sites · [reviewed contract](#b0023) |
| [B0024 · 107–107](../../../../../tests/unit/storage_journal_test.cpp#L107) | Explanatory comments or spacing. |  |
| [B0025 · 108–113](../../../../../tests/unit/storage_journal_test.cpp#L108) | Callable definition: IndexId add_index(ReferenceTable& table, const TupleLayout& source, const std::vector&lt;std::size_t&gt;& slots, LayoutId target_id) | calls fields_for, projected_layout; returns table.add_index(Projection{source, target, fields}) · [reviewed contract](#b0025) |
| [B0026 · 114–114](../../../../../tests/unit/storage_journal_test.cpp#L114) | Explanatory comments or spacing. |  |
| [B0027 · 115–120](../../../../../tests/unit/storage_journal_test.cpp#L115) | Callable definition: Row raw_key(const Row& row, const std::vector&lt;std::size_t&gt;& slots) | calls reserve, size, push_back, at; returns result; growth push_back, reserve; 1 loop sites · [reviewed contract](#b0027) |
| [B0028 · 121–121](../../../../../tests/unit/storage_journal_test.cpp#L121) | Explanatory comments or spacing. |  |
| [B0029 · 122–183](../../../../../tests/unit/storage_journal_test.cpp#L122) | Callable definition: void compare_model(ReferenceTable& table, const TupleLayout& source, const RowsByValue& rows, const IndexSlots& indexes, const st… | calls check_invariants, check, size, insert; guard check(table.size() == rows.size(), where + ": row count differs from model");; growth insert; 9 loop sites · [reviewed contract](#b0029) |
| [B0030 · 184–184](../../../../../tests/unit/storage_journal_test.cpp#L184) | Explanatory comments or spacing. |  |
| [B0031 · 185–258](../../../../../tests/unit/storage_journal_test.cpp#L185) | Callable definition: void lock_and_noop_contract() | calls source_layout, sample_row, insert, tuple; guard check(journal.active() && journal.size() == 0U, "new journal is not empty and active");; growth insert · [reviewed contract](#b0031) |
| [B0032 · 259–259](../../../../../tests/unit/storage_journal_test.cpp#L259) | Explanatory comments or spacing. |  |
| [B0033 · 260–266](../../../../../tests/unit/storage_journal_test.cpp#L260) | Type/record definition: struct PinnedIdentity |  · [reviewed contract](#b0033) |
| [B0034 · 267–267](../../../../../tests/unit/storage_journal_test.cpp#L267) | Explanatory comments or spacing. |  |
| [B0035 · 268–362](../../../../../tests/unit/storage_journal_test.cpp#L268) | Callable definition: void rollback_restores_rows_indexes_and_generations() | calls source_layout, add_index, sample_row, reserve; guard check(original_model.emplace(row, handle).second, "duplicate rollback fixture row");; growth emplace, insert, push_back, reserve; 4 loop sites · [reviewed contract](#b0035) |
| [B0036 · 363–363](../../../../../tests/unit/storage_journal_test.cpp#L363) | Explanatory comments or spacing. |  |
| [B0037 · 364–435](../../../../../tests/unit/storage_journal_test.cpp#L364) | Callable definition: void committed_changes_keep_payloads_after_clear_and_destruction() | calls source_layout, sample_row, insert, tuple; guard check(journal.erase(first), "commit fixture could not erase first row");; growth emplace, insert, push_back; 3 loop sites; source comment (unverified): // The committed journal releases the table's write lock. The ordinary · [reviewed contract](#b0037) |
| [B0038 · 436–436](../../../../../tests/unit/storage_journal_test.cpp#L436) | Explanatory comments or spacing. |  |
| [B0039 · 437–472](../../../../../tests/unit/storage_journal_test.cpp#L437) | Callable definition: void move_assignment_and_destructor_rollback() | calls source_layout, sample_row, insert, tuple; guard check(destination.erase(left_handle), "move-assignment fixture left erase failed");; growth insert · [reviewed contract](#b0039) |
| [B0040 · 473–473](../../../../../tests/unit/storage_journal_test.cpp#L473) | Explanatory comments or spacing. |  |
| [B0041 · 474–504](../../../../../tests/unit/storage_journal_test.cpp#L474) | Callable definition: void rollback_and_commit_do_not_allocate() | calls static_assert, rollback, commit, source_layout; guard static_assert(noexcept(std::declval&lt;ReferenceTable::Journal&&gt;().rollback()));; growth emplace, insert · [reviewed contract](#b0041) |
| [B0042 · 505–505](../../../../../tests/unit/storage_journal_test.cpp#L505) | Explanatory comments or spacing. |  |
| [B0043 · 506–527](../../../../../tests/unit/storage_journal_test.cpp#L506) | Type/record definition: struct AllocationFixture | guard check(inserted.inserted, "allocation fixture unexpectedly duplicated a row");; growth emplace, insert; 1 loop sites · [reviewed contract](#b0043) |
| [B0044 · 528–528](../../../../../tests/unit/storage_journal_test.cpp#L528) | Explanatory comments or spacing. |  |
| [B0045 · 529–581](../../../../../tests/unit/storage_journal_test.cpp#L529) | Callable definition: std::size_t journal_insert_allocation_failures() | calls sample_row, tuple, std::max, journal; guard check(journal.active() && journal.size() == 0U,; returns failures; growth insert; 2 loop sites · [reviewed contract](#b0045) |
| [B0046 · 582–582](../../../../../tests/unit/storage_journal_test.cpp#L582) | Explanatory comments or spacing. |  |
| [B0047 · 583–632](../../../../../tests/unit/storage_journal_test.cpp#L583) | Callable definition: std::size_t journal_erase_allocation_failures() | calls begin, journal, revision, erase; guard check(journal.active() && journal.size() == 0U,; returns failures; 1 loop sites · [reviewed contract](#b0047) |
| [B0048 · 633–633](../../../../../tests/unit/storage_journal_test.cpp#L633) | Explanatory comments or spacing. |  |
| [B0049 · 634–636](../../../../../tests/unit/storage_journal_test.cpp#L634) | Callable definition: std::size_t pick(std::mt19937_64& random, std::size_t bound) | calls random; returns static_cast&lt;std::size_t&gt;(random() % static_cast&lt;std::uint64_t&gt;(bound)) · [reviewed contract](#b0049) |
| [B0050 · 637–637](../../../../../tests/unit/storage_journal_test.cpp#L637) | Explanatory comments or spacing. |  |
| [B0051 · 638–650](../../../../../tests/unit/storage_journal_test.cpp#L638) | Callable definition: Row random_row(std::mt19937_64& random) | calls std::string, Date::parse, Decimal::parse, random; returns Row{Value{integer}, Value{texts\[pick(random, texts.size())\]}, · [reviewed contract](#b0051) |
| [B0052 · 651–651](../../../../../tests/unit/storage_journal_test.cpp#L651) | Explanatory comments or spacing. |  |
| [B0053 · 652–754](../../../../../tests/unit/storage_journal_test.cpp#L652) | Callable definition: void randomized_journal_model() | calls source_layout, add_index, random_row, insert; guard check(result.inserted == (prior == rows.end()),; growth emplace, insert, push_back; 6 loop sites; source comment (unverified): // Remove all rows represented by a selected secondary key. The · [reviewed contract](#b0053) |
| [B0054 · 755–756](../../../../../tests/unit/storage_journal_test.cpp#L755) | Closes surrounding scope/type. | source comment (unverified): // namespace · [reviewed contract](#b0054) |
| [B0055 · 757–775](../../../../../tests/unit/storage_journal_test.cpp#L757) | Callable definition: int main() | calls lock_and_noop_contract, rollback_restores_rows_indexes_and_generations, committed_changes_keep_payloads_after_clear_and_destruction, move_assignment_and_destructor_rollback; returns 0; 1 · [reviewed contract](#b0055) |

## B0001

[Lines 1–25](../../../../../tests/unit/storage_journal_test.cpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L1-L25:sha256:2ecff22b498ae9a1ad0d421515c504c150eb8c6cd34447ea26497ee61bfb8b1c
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Prepare storage_journal_test.cpp: include "crown/api/error.hpp", "crown/storage/reference.hpp", &lt;algorithm&gt;, &lt;cstddef&gt;, &lt;cstdint&gt;, &lt;cstdlib&gt;, &lt;iostream&gt;, &lt;map&gt;, &lt;new&gt;, &lt;optional&gt;, &lt;random&gt;, &lt;set&gt;, &lt;stdexcept&gt;, &lt;string&gt;, &lt;string_view&gt;, &lt;utility&gt;, &lt;vector&gt;; declare fixture state/default initializers. |
| inputs / outputs | Compiler-visible dependencies, names and the recorded declarations in; declarations available to the following fixture/CLI/example definitions out. The source span lists the exact member/global names, types and initial values; initializers run when the enclosing object/program/thread is initialized. |
| invariants | Declarations are scoped to this source/header and its selected ABI. Included code has its own effects; names and editable fixture values do not confer proof, admission or publication authority. |
| ownership | Aliases/includes do not create a query owner. Pointers/references/views are non-owning. Containers own their elements, which can themselves be borrowed pointers or numeric IDs. Only documented owning shared-control handles retain controls; IDs/slot-handle values do not independently keep an arena/runtime alive. Thread-local fault/countdown state belongs to this test executable and each thread; it is not a field added to a production owner. |
| failure | Missing headers, ill-formed names/types, failed static assertions or active #error directives stop compilation. No runtime rejection/rollback mechanism is implemented by aliases or function prototypes. |
| cost | Preprocessing and type/constraint instantiation cost compilation. Alias/prototype syntax does not invoke the declared operation; any included definitions keep their own initialization effects. This span initializes fixed scalar/atomic/TLS probe state. Storage and later probe accesses are test costs; no native factory or filesystem operation is implied by these scalar initializers. TLS storage and later injector accesses are test instrumentation costs. |
| Design | [tests/unit/storage_journal_test.cpp](../../../../../tests/unit/storage_journal_test.cpp), [docs/session-journal.md](../../../../session-journal.md), [docs/code_review.md](../../../../code_review.md) |

## B0002

[Lines 26–32](../../../../../tests/unit/storage_journal_test.cpp#L26); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
[[gnu::noinline]] void* allocate(std::size_t bytes)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Implement the storage journal test's ordinary global-new fault and allocation-count seam. |
| inputs / outputs | Callable: \[\[gnu::noinline\]\] void* allocate(std::size_t bytes). Input: byte count. Output: malloc-backed bytes or std::bad_alloc; tracked attempts increment tracked_allocations. |
| invariants | Fault injection and counting observe ordinary new/new\[\] routed through the local replacement, not arbitrary allocator calls or aligned-new overloads. |
| ownership | ReferenceTable owns the live rows and indexes. Passed table/model references are borrowed; active Journal objects own their undo/change payload state and Pins own their referenced arena allocations. |
| failure | A failed check throws std::runtime_error; expect_error accepts only the requested crown::Error. Fault sweeps catch std::bad_alloc from the local ordinary global-new seam. |
| cost | One malloc request per intercepted attempt; optional counter increment and countdown checks are constant work. |
| Design | [include/crown/storage/reference.hpp](../../../../../include/crown/storage/reference.hpp), [src/storage/reference.cpp](../../../../../src/storage/reference.cpp), [docs/storage_journal.md §Purpose and API](../../../../storage_journal.md), [docs/storage_journal.md §Exclusive mutation and tentative reads](../../../../storage_journal.md), [docs/storage_journal.md §Undo records and identity restoration](../../../../storage_journal.md), [docs/storage_journal.md §Revisions and allocation metadata](../../../../storage_journal.md) |

## B0003

[Lines 33–34](../../../../../tests/unit/storage_journal_test.cpp#L33); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L33-L34:sha256:c2bd7638f09d52cb034ed574f539304035fc6fab162bf8d5fa20a35d8c7288a1
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Close the recorded declaration scopes in storage_journal_test.cpp: namespace (anonymous). |
| inputs / outputs | Preceding namespace, type or initializer declarations in; completed lexical boundary out. |
| invariants | Brace-opening context is recorded in root-scope-context-v1.json. These are declaration/initializer boundaries, not an independent update, validation or recovery operation. |
| ownership | Enclosing objects and borrowed fields keep their declared ownership. This punctuation creates no new owner. |
| failure | Malformed scope syntax is a compile error. Any initializer/constructor failure belongs to the enclosing object declaration. |
| cost | No separate loop, guard or engine call is introduced by the delimiter; enclosing initialization and object lifetime still have their actual costs. |
| Design | [tests/unit/storage_journal_test.cpp](../../../../../tests/unit/storage_journal_test.cpp), [docs/session-journal.md](../../../../session-journal.md), [docs/code_review.md](../../../../code_review.md) |

## B0004

[Lines 35–35](../../../../../tests/unit/storage_journal_test.cpp#L35); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void* operator new(std::size_t bytes)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Route scalar global-new requests through storage journal allocation tracking. |
| inputs / outputs | Callable: void* operator new(std::size_t bytes). Input: requested bytes. Output: pointer from allocate or std::bad_alloc. |
| invariants | The interposition is local to this standalone executable. |
| ownership | ReferenceTable owns the live rows and indexes. Passed table/model references are borrowed; active Journal objects own their undo/change payload state and Pins own their referenced arena allocations. |
| failure | A failed check throws std::runtime_error; expect_error accepts only the requested crown::Error. Fault sweeps catch std::bad_alloc from the local ordinary global-new seam. |
| cost | Uses one finite typed row or supplied index/key set. Test-side containers may allocate; this helper makes no elapsed-time claim. |
| Design | [include/crown/storage/reference.hpp](../../../../../include/crown/storage/reference.hpp), [src/storage/reference.cpp](../../../../../src/storage/reference.cpp), [docs/storage_journal.md §Purpose and API](../../../../storage_journal.md), [docs/storage_journal.md §Exclusive mutation and tentative reads](../../../../storage_journal.md), [docs/storage_journal.md §Undo records and identity restoration](../../../../storage_journal.md), [docs/storage_journal.md §Revisions and allocation metadata](../../../../storage_journal.md) |

## B0005

[Lines 36–36](../../../../../tests/unit/storage_journal_test.cpp#L36); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void* operator new[](std::size_t bytes)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Route array global-new requests through storage journal allocation tracking. |
| inputs / outputs | Callable: void* operator new\[\](std::size_t bytes). Input: requested bytes. Output: pointer from allocate or std::bad_alloc. |
| invariants | The interposition is local to this standalone executable. |
| ownership | ReferenceTable owns the live rows and indexes. Passed table/model references are borrowed; active Journal objects own their undo/change payload state and Pins own their referenced arena allocations. |
| failure | A failed check throws std::runtime_error; expect_error accepts only the requested crown::Error. Fault sweeps catch std::bad_alloc from the local ordinary global-new seam. |
| cost | Uses one finite typed row or supplied index/key set. Test-side containers may allocate; this helper makes no elapsed-time claim. |
| Design | [include/crown/storage/reference.hpp](../../../../../include/crown/storage/reference.hpp), [src/storage/reference.cpp](../../../../../src/storage/reference.cpp), [docs/storage_journal.md §Purpose and API](../../../../storage_journal.md), [docs/storage_journal.md §Exclusive mutation and tentative reads](../../../../storage_journal.md), [docs/storage_journal.md §Undo records and identity restoration](../../../../storage_journal.md), [docs/storage_journal.md §Revisions and allocation metadata](../../../../storage_journal.md) |

## B0006

[Lines 37–37](../../../../../tests/unit/storage_journal_test.cpp#L37); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void operator delete(void* pointer) noexcept
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Free storage obtained through the local scalar global-new replacement. |
| inputs / outputs | Callable: void operator delete(void* pointer) noexcept. Input: possibly null pointer. Output: none. |
| invariants | The replacement delegates to std::free and does not update the attempt counter. |
| ownership | ReferenceTable owns the live rows and indexes. Passed table/model references are borrowed; active Journal objects own their undo/change payload state and Pins own their referenced arena allocations. |
| failure | A failed check throws std::runtime_error; expect_error accepts only the requested crown::Error. Fault sweeps catch std::bad_alloc from the local ordinary global-new seam. |
| cost | Uses one finite typed row or supplied index/key set. Test-side containers may allocate; this helper makes no elapsed-time claim. |
| Design | [include/crown/storage/reference.hpp](../../../../../include/crown/storage/reference.hpp), [src/storage/reference.cpp](../../../../../src/storage/reference.cpp), [docs/storage_journal.md §Purpose and API](../../../../storage_journal.md), [docs/storage_journal.md §Exclusive mutation and tentative reads](../../../../storage_journal.md), [docs/storage_journal.md §Undo records and identity restoration](../../../../storage_journal.md), [docs/storage_journal.md §Revisions and allocation metadata](../../../../storage_journal.md) |

## B0007

[Lines 38–38](../../../../../tests/unit/storage_journal_test.cpp#L38); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void operator delete[](void* pointer) noexcept
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Free storage obtained through the local array global-new replacement. |
| inputs / outputs | Callable: void operator delete\[\](void* pointer) noexcept. Input: possibly null pointer. Output: none. |
| invariants | The replacement delegates to std::free and does not update the attempt counter. |
| ownership | ReferenceTable owns the live rows and indexes. Passed table/model references are borrowed; active Journal objects own their undo/change payload state and Pins own their referenced arena allocations. |
| failure | A failed check throws std::runtime_error; expect_error accepts only the requested crown::Error. Fault sweeps catch std::bad_alloc from the local ordinary global-new seam. |
| cost | Uses one finite typed row or supplied index/key set. Test-side containers may allocate; this helper makes no elapsed-time claim. |
| Design | [include/crown/storage/reference.hpp](../../../../../include/crown/storage/reference.hpp), [src/storage/reference.cpp](../../../../../src/storage/reference.cpp), [docs/storage_journal.md §Purpose and API](../../../../storage_journal.md), [docs/storage_journal.md §Exclusive mutation and tentative reads](../../../../storage_journal.md), [docs/storage_journal.md §Undo records and identity restoration](../../../../storage_journal.md), [docs/storage_journal.md §Revisions and allocation metadata](../../../../storage_journal.md) |

## B0008

[Lines 39–39](../../../../../tests/unit/storage_journal_test.cpp#L39); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void operator delete(void* pointer, std::size_t) noexcept
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Free a sized scalar allocation from the local global-new replacement. |
| inputs / outputs | Callable: void operator delete(void* pointer, std::size_t) noexcept. Inputs: pointer and ignored byte size. Output: none. |
| invariants | The sized delete uses std::free and has no injected allocation path. |
| ownership | ReferenceTable owns the live rows and indexes. Passed table/model references are borrowed; active Journal objects own their undo/change payload state and Pins own their referenced arena allocations. |
| failure | A failed check throws std::runtime_error; expect_error accepts only the requested crown::Error. Fault sweeps catch std::bad_alloc from the local ordinary global-new seam. |
| cost | Uses one finite typed row or supplied index/key set. Test-side containers may allocate; this helper makes no elapsed-time claim. |
| Design | [include/crown/storage/reference.hpp](../../../../../include/crown/storage/reference.hpp), [src/storage/reference.cpp](../../../../../src/storage/reference.cpp), [docs/storage_journal.md §Purpose and API](../../../../storage_journal.md), [docs/storage_journal.md §Exclusive mutation and tentative reads](../../../../storage_journal.md), [docs/storage_journal.md §Undo records and identity restoration](../../../../storage_journal.md), [docs/storage_journal.md §Revisions and allocation metadata](../../../../storage_journal.md) |

## B0009

[Lines 40–40](../../../../../tests/unit/storage_journal_test.cpp#L40); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void operator delete[](void* pointer, std::size_t) noexcept
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Free a sized array allocation from the local global-new replacement. |
| inputs / outputs | Callable: void operator delete\[\](void* pointer, std::size_t) noexcept. Inputs: pointer and ignored byte size. Output: none. |
| invariants | The sized delete uses std::free and has no injected allocation path. |
| ownership | ReferenceTable owns the live rows and indexes. Passed table/model references are borrowed; active Journal objects own their undo/change payload state and Pins own their referenced arena allocations. |
| failure | A failed check throws std::runtime_error; expect_error accepts only the requested crown::Error. Fault sweeps catch std::bad_alloc from the local ordinary global-new seam. |
| cost | Uses one finite typed row or supplied index/key set. Test-side containers may allocate; this helper makes no elapsed-time claim. |
| Design | [include/crown/storage/reference.hpp](../../../../../include/crown/storage/reference.hpp), [src/storage/reference.cpp](../../../../../src/storage/reference.cpp), [docs/storage_journal.md §Purpose and API](../../../../storage_journal.md), [docs/storage_journal.md §Exclusive mutation and tentative reads](../../../../storage_journal.md), [docs/storage_journal.md §Undo records and identity restoration](../../../../storage_journal.md), [docs/storage_journal.md §Revisions and allocation metadata](../../../../storage_journal.md) |

## B0010

[Lines 41–47](../../../../../tests/unit/storage_journal_test.cpp#L41); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L41-L47:sha256:8a559962de1a8fc6931cc8c63c32d4481ead87d9d9052c3585184aa2c532a580
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Prepare storage_journal_test.cpp: bind local aliases/name imports. |
| inputs / outputs | Compiler-visible dependencies, names and the recorded declarations in; declarations available to the following fixture/CLI/example definitions out. |
| invariants | Declarations are scoped to this source/header and its selected ABI. Included code has its own effects; names and editable fixture values do not confer proof, admission or publication authority. |
| ownership | Aliases/includes do not create a query owner. Pointers/references/views are non-owning. Containers own their elements, which can themselves be borrowed pointers or numeric IDs. Only documented owning shared-control handles retain controls; IDs/slot-handle values do not independently keep an arena/runtime alive. |
| failure | Missing headers, ill-formed names/types, failed static assertions or active #error directives stop compilation. No runtime rejection/rollback mechanism is implemented by aliases or function prototypes. |
| cost | Preprocessing and type/constraint instantiation cost compilation. Alias/prototype syntax does not invoke the declared operation; any included definitions keep their own initialization effects. |
| Design | [tests/unit/storage_journal_test.cpp](../../../../../tests/unit/storage_journal_test.cpp), [docs/session-journal.md](../../../../session-journal.md), [docs/code_review.md](../../../../code_review.md) |

## B0011

[Lines 48–50](../../../../../tests/unit/storage_journal_test.cpp#L48); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void check(bool condition, const std::string& message)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Raise a labeled test failure when a storage-journal expectation is false. |
| inputs / outputs | Callable: void check(bool condition, const std::string& message). Inputs: Boolean condition and message. Output: none on success; failure throws std::runtime_error. |
| invariants | The check is active independently of NDEBUG. |
| ownership | ReferenceTable owns the live rows and indexes. Passed table/model references are borrowed; active Journal objects own their undo/change payload state and Pins own their referenced arena allocations. |
| failure | A failed check throws std::runtime_error; expect_error accepts only the requested crown::Error. Fault sweeps catch std::bad_alloc from the local ordinary global-new seam. |
| cost | Uses one finite typed row or supplied index/key set. Test-side containers may allocate; this helper makes no elapsed-time claim. |
| Design | [include/crown/storage/reference.hpp](../../../../../include/crown/storage/reference.hpp), [src/storage/reference.cpp](../../../../../src/storage/reference.cpp), [docs/storage_journal.md §Purpose and API](../../../../storage_journal.md), [docs/storage_journal.md §Exclusive mutation and tentative reads](../../../../storage_journal.md), [docs/storage_journal.md §Undo records and identity restoration](../../../../storage_journal.md), [docs/storage_journal.md §Revisions and allocation metadata](../../../../storage_journal.md) |

## B0013

[Lines 52–61](../../../../../tests/unit/storage_journal_test.cpp#L52); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
template <class Action>
void expect_error(Action&& action, std::string_view code)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Require one action to throw the selected CROWN Error code. |
| inputs / outputs | Callable: template &lt;class Action&gt; void expect_error(Action&& action, std::string_view code). Inputs: callable action and expected code. Output: none for the matching Error; other/no errors fail the test. |
| invariants | Only crown::Error is treated as the expected storage diagnostic. |
| ownership | ReferenceTable owns the live rows and indexes. Passed table/model references are borrowed; active Journal objects own their undo/change payload state and Pins own their referenced arena allocations. |
| failure | A failed check throws std::runtime_error; expect_error accepts only the requested crown::Error. Fault sweeps catch std::bad_alloc from the local ordinary global-new seam. |
| cost | Uses one finite typed row or supplied index/key set. Test-side containers may allocate; this helper makes no elapsed-time claim. |
| Design | [include/crown/storage/reference.hpp](../../../../../include/crown/storage/reference.hpp), [src/storage/reference.cpp](../../../../../src/storage/reference.cpp), [docs/storage_journal.md §Purpose and API](../../../../storage_journal.md), [docs/storage_journal.md §Exclusive mutation and tentative reads](../../../../storage_journal.md), [docs/storage_journal.md §Undo records and identity restoration](../../../../storage_journal.md), [docs/storage_journal.md §Revisions and allocation metadata](../../../../storage_journal.md) |

## B0015

[Lines 63–78](../../../../../tests/unit/storage_journal_test.cpp#L63); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
template <class Action>
std::size_t count_allocations(Action&& action)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Count ordinary global-new attempts made by one action while rejecting any such attempt. |
| inputs / outputs | Callable: template &lt;class Action&gt; std::size_t count_allocations(Action&& action). Input: callable action. Output: intercepted allocation-attempt count when it completes. |
| invariants | Tracking sets fail_after to zero and is reset after success or exception; direct malloc and non-interposed allocation paths are not counted. |
| ownership | The action is borrowed for the call; the helper owns only thread-local tracking state and does not retain the action's table or result. |
| failure | If the action attempts an intercepted ordinary global-new allocation, fail_after=0 throws std::bad_alloc and the helper resets tracking before propagating. |
| cost | Runs the supplied action once and counts only ordinary global-new calls routed through allocate. |
| Design | [include/crown/storage/reference.hpp](../../../../../include/crown/storage/reference.hpp), [src/storage/reference.cpp](../../../../../src/storage/reference.cpp), [docs/storage_journal.md §Purpose and API](../../../../storage_journal.md), [docs/storage_journal.md §Exclusive mutation and tentative reads](../../../../storage_journal.md), [docs/storage_journal.md §Undo records and identity restoration](../../../../storage_journal.md), [docs/storage_journal.md §Revisions and allocation metadata](../../../../storage_journal.md) |

## B0017

[Lines 80–86](../../../../../tests/unit/storage_journal_test.cpp#L80); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
class AllocationFailureScope
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Arm one ordinary global-new failure position for a storage journal mutation. |
| inputs / outputs | Type: class AllocationFailureScope. Input: selected attempt index. Output: none; destructor disables injection. |
| invariants | It is noncopyable and owns only the thread-local test countdown. |
| ownership | ReferenceTable owns the live rows and indexes. Passed table/model references are borrowed; active Journal objects own their undo/change payload state and Pins own their referenced arena allocations. |
| failure | A failed check throws std::runtime_error; expect_error accepts only the requested crown::Error. Fault sweeps catch std::bad_alloc from the local ordinary global-new seam. |
| cost | Uses one finite typed row or supplied index/key set. Test-side containers may allocate; this helper makes no elapsed-time claim. |
| Design | [include/crown/storage/reference.hpp](../../../../../include/crown/storage/reference.hpp), [src/storage/reference.cpp](../../../../../src/storage/reference.cpp), [docs/storage_journal.md §Purpose and API](../../../../storage_journal.md), [docs/storage_journal.md §Exclusive mutation and tentative reads](../../../../storage_journal.md), [docs/storage_journal.md §Undo records and identity restoration](../../../../storage_journal.md), [docs/storage_journal.md §Revisions and allocation metadata](../../../../storage_journal.md) |

## B0019

[Lines 88–93](../../../../../tests/unit/storage_journal_test.cpp#L88); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
TupleLayout source_layout()
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Create the five-field typed layout used by storage journal fixtures. |
| inputs / outputs | Callable: TupleLayout source_layout(). Input: none. Output: int64, string, Boolean, date, and decimal fields under LayoutId 1 and the fixture context. |
| invariants | The returned layout fixes field order and scalar types for every model row and projection. |
| ownership | ReferenceTable owns the live rows and indexes. Passed table/model references are borrowed; active Journal objects own their undo/change payload state and Pins own their referenced arena allocations. |
| failure | A failed check throws std::runtime_error; expect_error accepts only the requested crown::Error. Fault sweeps catch std::bad_alloc from the local ordinary global-new seam. |
| cost | Uses one finite typed row or supplied index/key set. Test-side containers may allocate; this helper makes no elapsed-time claim. |
| Design | [include/crown/storage/reference.hpp](../../../../../include/crown/storage/reference.hpp), [src/storage/reference.cpp](../../../../../src/storage/reference.cpp), [docs/storage_journal.md §Purpose and API](../../../../storage_journal.md), [docs/storage_journal.md §Exclusive mutation and tentative reads](../../../../storage_journal.md), [docs/storage_journal.md §Undo records and identity restoration](../../../../storage_journal.md), [docs/storage_journal.md §Revisions and allocation metadata](../../../../storage_journal.md) |

## B0021

[Lines 95–99](../../../../../tests/unit/storage_journal_test.cpp#L95); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Row sample_row(std::int64_t integer, std::string text, bool flag,
               std::string_view day, std::string_view amount)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Build one fully typed storage model row from fixture scalar inputs. |
| inputs / outputs | Callable: Row sample_row(std::int64_t integer, std::string text, bool flag, std::string_view day, std::string_view amount). Inputs: integer, owning text, Boolean, ISO date text, and decimal text. Output: five-value Row. |
| invariants | Date and decimal text are parsed into their typed scalar alternatives before insertion. |
| ownership | ReferenceTable owns the live rows and indexes. Passed table/model references are borrowed; active Journal objects own their undo/change payload state and Pins own their referenced arena allocations. |
| failure | A failed check throws std::runtime_error; expect_error accepts only the requested crown::Error. Fault sweeps catch std::bad_alloc from the local ordinary global-new seam. |
| cost | Uses one finite typed row or supplied index/key set. Test-side containers may allocate; this helper makes no elapsed-time claim. |
| Design | [include/crown/storage/reference.hpp](../../../../../include/crown/storage/reference.hpp), [src/storage/reference.cpp](../../../../../src/storage/reference.cpp), [docs/storage_journal.md §Purpose and API](../../../../storage_journal.md), [docs/storage_journal.md §Exclusive mutation and tentative reads](../../../../storage_journal.md), [docs/storage_journal.md §Undo records and identity restoration](../../../../storage_journal.md), [docs/storage_journal.md §Revisions and allocation metadata](../../../../storage_journal.md) |

## B0023

[Lines 101–106](../../../../../tests/unit/storage_journal_test.cpp#L101); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::vector<FieldId> fields_for(const std::vector<std::size_t>& slots)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Convert source slot numbers into a positional FieldId vector. |
| inputs / outputs | Callable: std::vector&lt;FieldId&gt; fields_for(const std::vector&lt;std::size_t&gt;& slots). Input: slot vector. Output: same-order FieldId values. |
| invariants | The helper preserves supplied slot order and delegates range validation to downstream projection construction. |
| ownership | ReferenceTable owns the live rows and indexes. Passed table/model references are borrowed; active Journal objects own their undo/change payload state and Pins own their referenced arena allocations. |
| failure | A failed check throws std::runtime_error; expect_error accepts only the requested crown::Error. Fault sweeps catch std::bad_alloc from the local ordinary global-new seam. |
| cost | Uses one finite typed row or supplied index/key set. Test-side containers may allocate; this helper makes no elapsed-time claim. |
| Design | [include/crown/storage/reference.hpp](../../../../../include/crown/storage/reference.hpp), [src/storage/reference.cpp](../../../../../src/storage/reference.cpp), [docs/storage_journal.md §Purpose and API](../../../../storage_journal.md), [docs/storage_journal.md §Exclusive mutation and tentative reads](../../../../storage_journal.md), [docs/storage_journal.md §Undo records and identity restoration](../../../../storage_journal.md), [docs/storage_journal.md §Revisions and allocation metadata](../../../../storage_journal.md) |

## B0025

[Lines 108–113](../../../../../tests/unit/storage_journal_test.cpp#L108); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
IndexId add_index(ReferenceTable& table, const TupleLayout& source,
                  const std::vector<std::size_t>& slots, LayoutId target_id)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Build a projected target layout and register one ReferenceTable secondary index. |
| inputs / outputs | Callable: IndexId add_index(ReferenceTable& table, const TupleLayout& source, const std::vector&lt;std::size_t&gt;& slots, LayoutId target_id). Inputs: table, source layout, source slots, and target LayoutId. Output: registered IndexId. |
| invariants | Projection fields are exactly the ordered source slots supplied by the fixture. |
| ownership | ReferenceTable owns the live rows and indexes. Passed table/model references are borrowed; active Journal objects own their undo/change payload state and Pins own their referenced arena allocations. |
| failure | A failed check throws std::runtime_error; expect_error accepts only the requested crown::Error. Fault sweeps catch std::bad_alloc from the local ordinary global-new seam. |
| cost | Uses one finite typed row or supplied index/key set. Test-side containers may allocate; this helper makes no elapsed-time claim. |
| Design | [include/crown/storage/reference.hpp](../../../../../include/crown/storage/reference.hpp), [src/storage/reference.cpp](../../../../../src/storage/reference.cpp), [docs/storage_journal.md §Purpose and API](../../../../storage_journal.md), [docs/storage_journal.md §Exclusive mutation and tentative reads](../../../../storage_journal.md), [docs/storage_journal.md §Undo records and identity restoration](../../../../storage_journal.md), [docs/storage_journal.md §Revisions and allocation metadata](../../../../storage_journal.md) |

## B0027

[Lines 115–120](../../../../../tests/unit/storage_journal_test.cpp#L115); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Row raw_key(const Row& row, const std::vector<std::size_t>& slots)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Compute a reference secondary key by directly copying selected source row slots. |
| inputs / outputs | Callable: Row raw_key(const Row& row, const std::vector&lt;std::size_t&gt;& slots). Inputs: owning Row and source slots. Output: Row containing those values in slot order. |
| invariants | The oracle does not call Projection::apply, so it provides an independent key derivation for model comparisons. |
| ownership | ReferenceTable owns the live rows and indexes. Passed table/model references are borrowed; active Journal objects own their undo/change payload state and Pins own their referenced arena allocations. |
| failure | A failed check throws std::runtime_error; expect_error accepts only the requested crown::Error. Fault sweeps catch std::bad_alloc from the local ordinary global-new seam. |
| cost | Uses one finite typed row or supplied index/key set. Test-side containers may allocate; this helper makes no elapsed-time claim. |
| Design | [include/crown/storage/reference.hpp](../../../../../include/crown/storage/reference.hpp), [src/storage/reference.cpp](../../../../../src/storage/reference.cpp), [docs/storage_journal.md §Purpose and API](../../../../storage_journal.md), [docs/storage_journal.md §Exclusive mutation and tentative reads](../../../../storage_journal.md), [docs/storage_journal.md §Undo records and identity restoration](../../../../storage_journal.md), [docs/storage_journal.md §Revisions and allocation metadata](../../../../storage_journal.md) |

## B0029

[Lines 122–183](../../../../../tests/unit/storage_journal_test.cpp#L122); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void compare_model(ReferenceTable& table, const TupleLayout& source,
                   const RowsByValue& rows, const IndexSlots& indexes,
                   const std::string& where)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Compare ReferenceTable rows, handles, snapshots, index keys, and bucket members with a value-based oracle. |
| inputs / outputs | Callable: void compare_model(ReferenceTable& table, const TupleLayout& source, const RowsByValue& rows, const IndexSlots& indexes, const std::string& where). Inputs: table/layout, row-to-handle model, index-to-slot model, and diagnostic context. Output: none when all sets agree. |
| invariants | Expected buckets are derived from raw_key over model rows; table invariants are checked after the explicit comparisons. |
| ownership | ReferenceTable owns the live rows and indexes. Passed table/model references are borrowed; active Journal objects own their undo/change payload state and Pins own their referenced arena allocations. |
| failure | A failed check throws std::runtime_error; expect_error accepts only the requested crown::Error. Fault sweeps catch std::bad_alloc from the local ordinary global-new seam. |
| cost | Scans model rows and index keys/buckets; expected keys are built from supplied raw slots, so work grows with this finite fixture and its index memberships. |
| Design | [include/crown/storage/reference.hpp](../../../../../include/crown/storage/reference.hpp), [src/storage/reference.cpp](../../../../../src/storage/reference.cpp), [docs/storage_journal.md §Purpose and API](../../../../storage_journal.md), [docs/storage_journal.md §Exclusive mutation and tentative reads](../../../../storage_journal.md), [docs/storage_journal.md §Undo records and identity restoration](../../../../storage_journal.md), [docs/storage_journal.md §Revisions and allocation metadata](../../../../storage_journal.md) |

## B0031

[Lines 185–258](../../../../../tests/unit/storage_journal_test.cpp#L185); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void lock_and_noop_contract()
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Check active-journal writer exclusion, allowed reads, no-op recording, change views, and empty rollback behavior. |
| inputs / outputs | Callable: void lock_and_noop_contract(). Input: none. Output: none after a one-row table and one index fixture passes its guards. |
| invariants | Duplicate insert and missing-handle erase add no change; a real erase/reinsert records two entries, rollback restores the original handle, and the revision remains advanced so the preexisting cursor stays invalid. |
| ownership | ReferenceTable owns the live rows and indexes. Passed table/model references are borrowed; active Journal objects own their undo/change payload state and Pins own their referenced arena allocations. |
| failure | A failed check throws std::runtime_error; expect_error accepts only the requested crown::Error. Fault sweeps catch std::bad_alloc from the local ordinary global-new seam. |
| cost | Uses one finite typed row or supplied index/key set. Test-side containers may allocate; this helper makes no elapsed-time claim. |
| Design | [include/crown/storage/reference.hpp](../../../../../include/crown/storage/reference.hpp), [src/storage/reference.cpp](../../../../../src/storage/reference.cpp), [docs/storage_journal.md §Purpose and API](../../../../storage_journal.md), [docs/storage_journal.md §Exclusive mutation and tentative reads](../../../../storage_journal.md), [docs/storage_journal.md §Undo records and identity restoration](../../../../storage_journal.md), [docs/storage_journal.md §Revisions and allocation metadata](../../../../storage_journal.md) |

## B0033

[Lines 260–266](../../../../../tests/unit/storage_journal_test.cpp#L260); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct PinnedIdentity
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Keep one original row's logical handle, arena handle, tuple address, and explicit pin together. |
| inputs / outputs | Type: struct PinnedIdentity. Fields: copied Row, TupleHandle, ArenaHandle, borrowed tuple address, and owning TupleArena::Pin. |
| invariants | The pin keeps the original arena allocation available for identity comparison during rollback. |
| ownership | TupleArena::Pin owns the original arena allocation; the saved tuple pointer is borrowed from that pinned allocation. |
| failure | A failed check throws std::runtime_error; expect_error accepts only the requested crown::Error. Fault sweeps catch std::bad_alloc from the local ordinary global-new seam. |
| cost | Uses one finite typed row or supplied index/key set. Test-side containers may allocate; this helper makes no elapsed-time claim. |
| Design | [include/crown/storage/reference.hpp](../../../../../include/crown/storage/reference.hpp), [src/storage/reference.cpp](../../../../../src/storage/reference.cpp), [docs/storage_journal.md §Purpose and API](../../../../storage_journal.md), [docs/storage_journal.md §Exclusive mutation and tentative reads](../../../../storage_journal.md), [docs/storage_journal.md §Undo records and identity restoration](../../../../storage_journal.md), [docs/storage_journal.md §Revisions and allocation metadata](../../../../storage_journal.md) |

## B0035

[Lines 268–362](../../../../../tests/unit/storage_journal_test.cpp#L268); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void rollback_restores_rows_indexes_and_generations()
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Exercise erase/insert/reinsert history and verify rollback restores rows, secondary indexes, handles, generations, and addresses. |
| inputs / outputs | Callable: void rollback_restores_rows_indexes_and_generations(). Input: none. Output: none after five rows and integer/text/nullary indexes pass rollback assertions. |
| invariants | Rollback must restore logical identity and original payload addresses while dropping temporary records after journal destruction; the private revision stays advanced. |
| ownership | Local pins outlive the active journal and keep original payloads address-stable while table membership is undone. |
| failure | A failed check throws std::runtime_error; expect_error accepts only the requested crown::Error. Fault sweeps catch std::bad_alloc from the local ordinary global-new seam. |
| cost | Mutates five rows across three indexes, compares each erase state, then checks ordered changes and exact rollback identities. |
| Design | [include/crown/storage/reference.hpp](../../../../../include/crown/storage/reference.hpp), [src/storage/reference.cpp](../../../../../src/storage/reference.cpp), [docs/storage_journal.md §Purpose and API](../../../../storage_journal.md), [docs/storage_journal.md §Exclusive mutation and tentative reads](../../../../storage_journal.md), [docs/storage_journal.md §Undo records and identity restoration](../../../../storage_journal.md), [docs/storage_journal.md §Revisions and allocation metadata](../../../../storage_journal.md) |

## B0037

[Lines 364–435](../../../../../tests/unit/storage_journal_test.cpp#L364); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void committed_changes_keep_payloads_after_clear_and_destruction()
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Verify committed journal change views survive table clear, table destruction, journal moves, and repeated close calls. |
| inputs / outputs | Callable: void committed_changes_keep_payloads_after_clear_and_destruction(). Input: none. Output: none after four ordered changes remain readable through the retained committed journal. |
| invariants | Commit ends the table writer scope but the journal's affected tuple pins preserve its change payloads; it does not retain the whole table. |
| ownership | A committed Journal retains pins for its changes but releases the table's exclusive scope; the test moves that Journal outside table lifetime. |
| failure | A failed check throws std::runtime_error; expect_error accepts only the requested crown::Error. Fault sweeps catch std::bad_alloc from the local ordinary global-new seam. |
| cost | Creates four journal entries and compares those entries before and after clear, move, and table destruction. |
| Design | [include/crown/storage/reference.hpp](../../../../../include/crown/storage/reference.hpp), [src/storage/reference.cpp](../../../../../src/storage/reference.cpp), [docs/storage_journal.md §Purpose and API](../../../../storage_journal.md), [docs/storage_journal.md §Exclusive mutation and tentative reads](../../../../storage_journal.md), [docs/storage_journal.md §Undo records and identity restoration](../../../../storage_journal.md), [docs/storage_journal.md §Revisions and allocation metadata](../../../../storage_journal.md) |

## B0039

[Lines 437–472](../../../../../tests/unit/storage_journal_test.cpp#L437); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void move_assignment_and_destructor_rollback()
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Check that move assignment first rolls back its active destination and that the moved source journal rolls back against its original table. |
| inputs / outputs | Callable: void move_assignment_and_destructor_rollback(). Input: none. Output: none after two tables and explicit/destructor rollback checks. |
| invariants | The destination's former owner is restored during move assignment; the transferred journal still owns the right table state. |
| ownership | ReferenceTable owns the live rows and indexes. Passed table/model references are borrowed; active Journal objects own their undo/change payload state and Pins own their referenced arena allocations. |
| failure | A failed check throws std::runtime_error; expect_error accepts only the requested crown::Error. Fault sweeps catch std::bad_alloc from the local ordinary global-new seam. |
| cost | Uses one finite typed row or supplied index/key set. Test-side containers may allocate; this helper makes no elapsed-time claim. |
| Design | [include/crown/storage/reference.hpp](../../../../../include/crown/storage/reference.hpp), [src/storage/reference.cpp](../../../../../src/storage/reference.cpp), [docs/storage_journal.md §Purpose and API](../../../../storage_journal.md), [docs/storage_journal.md §Exclusive mutation and tentative reads](../../../../storage_journal.md), [docs/storage_journal.md §Undo records and identity restoration](../../../../storage_journal.md), [docs/storage_journal.md §Revisions and allocation metadata](../../../../storage_journal.md) |

## B0041

[Lines 474–504](../../../../../tests/unit/storage_journal_test.cpp#L474); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void rollback_and_commit_do_not_allocate()
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Check noexcept declarations and absence of intercepted ordinary global-new attempts in rollback, active destruction, and commit. |
| inputs / outputs | Callable: void rollback_and_commit_do_not_allocate(). Input: none. Output: none when the three operations complete with count_allocations equal to zero. |
| invariants | This test's allocation observation is the local global-new counter; it does not measure direct malloc or every possible allocator API. |
| ownership | ReferenceTable owns the live rows and indexes. Passed table/model references are borrowed; active Journal objects own their undo/change payload state and Pins own their referenced arena allocations. |
| failure | A failed check throws std::runtime_error; expect_error accepts only the requested crown::Error. Fault sweeps catch std::bad_alloc from the local ordinary global-new seam. |
| cost | Uses one finite typed row or supplied index/key set. Test-side containers may allocate; this helper makes no elapsed-time claim. |
| Design | [tests/unit/storage_journal_test.cpp](../../../../../tests/unit/storage_journal_test.cpp), [src/storage/reference.cpp](../../../../../src/storage/reference.cpp), [docs/storage_journal.md §Undo records and identity restoration](../../../../storage_journal.md) |

## B0043

[Lines 506–527](../../../../../tests/unit/storage_journal_test.cpp#L506); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct AllocationFixture
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Own the nine-row ReferenceTable model and three indexes reused by insert/erase fault sweeps. |
| inputs / outputs | Type: struct AllocationFixture. Construction: source layout, table, integer/text/nullary index projections, and row-to-handle map. Output: complete fixture. |
| invariants | Rows are synthesized from fixed formulas; candidate insert values are outside the fixture set. |
| ownership | The fixture owns its ReferenceTable, layout, row map, and index descriptions for each fault-sweep iteration. |
| failure | A failed check throws std::runtime_error; expect_error accepts only the requested crown::Error. Fault sweeps catch std::bad_alloc from the local ordinary global-new seam. |
| cost | Uses one finite typed row or supplied index/key set. Test-side containers may allocate; this helper makes no elapsed-time claim. |
| Design | [include/crown/storage/reference.hpp](../../../../../include/crown/storage/reference.hpp), [src/storage/reference.cpp](../../../../../src/storage/reference.cpp), [docs/storage_journal.md §Purpose and API](../../../../storage_journal.md), [docs/storage_journal.md §Exclusive mutation and tentative reads](../../../../storage_journal.md), [docs/storage_journal.md §Undo records and identity restoration](../../../../storage_journal.md), [docs/storage_journal.md §Revisions and allocation metadata](../../../../storage_journal.md) |

## B0045

[Lines 529–581](../../../../../tests/unit/storage_journal_test.cpp#L529); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::size_t journal_insert_allocation_failures()
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Sweep ordinary global-new failures through one journal insert and verify retry and rollback identity. |
| inputs / outputs | Callable: std::size_t journal_insert_allocation_failures(). Input: none. Output: number of injected failures before the first successful insert. |
| invariants | Failed inserts leave the active journal empty and revision unchanged; retries use largest existing logical tuple ID plus one, and rollback restores the model. |
| ownership | ReferenceTable owns the live rows and indexes. Passed table/model references are borrowed; active Journal objects own their undo/change payload state and Pins own their referenced arena allocations. |
| failure | Only std::bad_alloc from journal.insert is classified as a fault point; failed preparation must leave the journal active and empty. |
| cost | At most 512 fresh nine-row/three-index fixtures and one insert attempt each, with full model comparisons on failure/retry/rollback. |
| Design | [include/crown/storage/reference.hpp](../../../../../include/crown/storage/reference.hpp), [src/storage/reference.cpp](../../../../../src/storage/reference.cpp), [docs/storage_journal.md §Purpose and API](../../../../storage_journal.md), [docs/storage_journal.md §Exclusive mutation and tentative reads](../../../../storage_journal.md), [docs/storage_journal.md §Undo records and identity restoration](../../../../storage_journal.md), [docs/storage_journal.md §Revisions and allocation metadata](../../../../storage_journal.md) |

## B0047

[Lines 583–632](../../../../../tests/unit/storage_journal_test.cpp#L583); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::size_t journal_erase_allocation_failures()
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Sweep ordinary global-new failures through one journal erase and verify retry and rollback state. |
| inputs / outputs | Callable: std::size_t journal_erase_allocation_failures(). Input: none. Output: number of injected failures before the first successful erase. |
| invariants | Failed erases leave journal size and revision unchanged; success removes exactly the selected row tentatively and rollback restores its original handle. |
| ownership | ReferenceTable owns the live rows and indexes. Passed table/model references are borrowed; active Journal objects own their undo/change payload state and Pins own their referenced arena allocations. |
| failure | Only std::bad_alloc from journal.erase is classified as a fault point; all other mismatches fail the test immediately. |
| cost | At most 512 fresh nine-row/three-index fixtures and one erase attempt each, with full model comparisons on failure/retry/rollback. |
| Design | [include/crown/storage/reference.hpp](../../../../../include/crown/storage/reference.hpp), [src/storage/reference.cpp](../../../../../src/storage/reference.cpp), [docs/storage_journal.md §Purpose and API](../../../../storage_journal.md), [docs/storage_journal.md §Exclusive mutation and tentative reads](../../../../storage_journal.md), [docs/storage_journal.md §Undo records and identity restoration](../../../../storage_journal.md), [docs/storage_journal.md §Revisions and allocation metadata](../../../../storage_journal.md) |

## B0049

[Lines 634–636](../../../../../tests/unit/storage_journal_test.cpp#L634); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::size_t pick(std::mt19937_64& random, std::size_t bound)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Map one seeded random value into a nonempty finite fixture domain. |
| inputs / outputs | Callable: std::size_t pick(std::mt19937_64& random, std::size_t bound). Inputs: mt19937_64 state and bound. Output: random() modulo bound as a size_t. |
| invariants | The caller supplies a positive bound from a fixed nonempty values list. |
| ownership | ReferenceTable owns the live rows and indexes. Passed table/model references are borrowed; active Journal objects own their undo/change payload state and Pins own their referenced arena allocations. |
| failure | A failed check throws std::runtime_error; expect_error accepts only the requested crown::Error. Fault sweeps catch std::bad_alloc from the local ordinary global-new seam. |
| cost | Uses one finite typed row or supplied index/key set. Test-side containers may allocate; this helper makes no elapsed-time claim. |
| Design | [include/crown/storage/reference.hpp](../../../../../include/crown/storage/reference.hpp), [src/storage/reference.cpp](../../../../../src/storage/reference.cpp), [docs/storage_journal.md §Purpose and API](../../../../storage_journal.md), [docs/storage_journal.md §Exclusive mutation and tentative reads](../../../../storage_journal.md), [docs/storage_journal.md §Undo records and identity restoration](../../../../storage_journal.md), [docs/storage_journal.md §Revisions and allocation metadata](../../../../storage_journal.md) |

## B0051

[Lines 638–650](../../../../../tests/unit/storage_journal_test.cpp#L638); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Row random_row(std::mt19937_64& random)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Generate one typed row from the journal model's bounded scalar domains. |
| inputs / outputs | Callable: Row random_row(std::mt19937_64& random). Input: seeded mt19937_64. Output: int64 in \[-3,3\], one of five fixed strings, a Boolean, one of three dates, and one of four decimals. |
| invariants | The string set includes empty, embedded NUL, and UTF-8 examples; all scalar choices remain inside the declared layout. |
| ownership | ReferenceTable owns the live rows and indexes. Passed table/model references are borrowed; active Journal objects own their undo/change payload state and Pins own their referenced arena allocations. |
| failure | A failed check throws std::runtime_error; expect_error accepts only the requested crown::Error. Fault sweeps catch std::bad_alloc from the local ordinary global-new seam. |
| cost | Uses one finite typed row or supplied index/key set. Test-side containers may allocate; this helper makes no elapsed-time claim. |
| Design | [include/crown/storage/reference.hpp](../../../../../include/crown/storage/reference.hpp), [src/storage/reference.cpp](../../../../../src/storage/reference.cpp), [docs/storage_journal.md §Purpose and API](../../../../storage_journal.md), [docs/storage_journal.md §Exclusive mutation and tentative reads](../../../../storage_journal.md), [docs/storage_journal.md §Undo records and identity restoration](../../../../storage_journal.md), [docs/storage_journal.md §Revisions and allocation metadata](../../../../storage_journal.md) |

## B0053

[Lines 652–754](../../../../../tests/unit/storage_journal_test.cpp#L652); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void randomized_journal_model()
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Compare committed and rolled-back journal transactions with an independent map model across deterministic seeds. |
| inputs / outputs | Callable: void randomized_journal_model(). Input: none. Output: count of attempted tentative operations after 12 seeds, 90 transactions per seed, and 12 operations per transaction. |
| invariants | Every tentative step compares table/index state; commit or rollback then checks exact model state, revision movement, and preexisting cursor validity. |
| ownership | The model map and before_rows are owning copies; the active journal separately owns its undo entries until commit or rollback. |
| failure | A failed check throws std::runtime_error; expect_error accepts only the requested crown::Error. Fault sweeps catch std::bad_alloc from the local ordinary global-new seam. |
| cost | Exactly 12 seeds x 90 transactions x 12 tentative actions = 12,960 model-comparison steps, plus setup and end-state checks. |
| Design | [tests/unit/storage_journal_test.cpp](../../../../../tests/unit/storage_journal_test.cpp), [docs/storage_journal.md §Purpose and API](../../../../storage_journal.md), [docs/storage_journal.md §Revisions and allocation metadata](../../../../storage_journal.md) |

## B0054

[Lines 755–756](../../../../../tests/unit/storage_journal_test.cpp#L755); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L755-L756:sha256:c2bd7638f09d52cb034ed574f539304035fc6fab162bf8d5fa20a35d8c7288a1
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Close the recorded declaration scopes in storage_journal_test.cpp: namespace (anonymous). |
| inputs / outputs | Preceding namespace, type or initializer declarations in; completed lexical boundary out. |
| invariants | Brace-opening context is recorded in root-scope-context-v1.json. These are declaration/initializer boundaries, not an independent update, validation or recovery operation. |
| ownership | Enclosing objects and borrowed fields keep their declared ownership. This punctuation creates no new owner. |
| failure | Malformed scope syntax is a compile error. Any initializer/constructor failure belongs to the enclosing object declaration. |
| cost | No separate loop, guard or engine call is introduced by the delimiter; enclosing initialization and object lifetime still have their actual costs. |
| Design | [tests/unit/storage_journal_test.cpp](../../../../../tests/unit/storage_journal_test.cpp), [docs/session-journal.md](../../../../session-journal.md), [docs/code_review.md](../../../../code_review.md) |

## B0055

[Lines 757–775](../../../../../tests/unit/storage_journal_test.cpp#L757); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
int main()
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Run the fixed journal guard, rollback, retention, move, allocation, and randomized-model checks. |
| inputs / outputs | Callable: int main(). Input: none. Output: zero on success after reporting failure counts and operation count; one on the first exception. |
| invariants | The randomized loop is bounded to 12 seeds times 90 transactions times 12 operations, in addition to the finite fault sweeps. |
| ownership | ReferenceTable owns the live rows and indexes. Passed table/model references are borrowed; active Journal objects own their undo/change payload state and Pins own their referenced arena allocations. |
| failure | A failed check throws std::runtime_error; expect_error accepts only the requested crown::Error. Fault sweeps catch std::bad_alloc from the local ordinary global-new seam. |
| cost | Runs two at-most-512 fault sweeps and the fixed 12,960-step randomized model in addition to the five named journal cases. |
| Design | [tests/unit/storage_journal_test.cpp](../../../../../tests/unit/storage_journal_test.cpp), [include/crown/storage/reference.hpp](../../../../../include/crown/storage/reference.hpp), [docs/storage_journal.md §Scope boundary](../../../../storage_journal.md) |
