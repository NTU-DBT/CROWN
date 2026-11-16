# `tests/unit/storage_journal_exception_test.cpp` — block usage map

[Source](../../../../../tests/unit/storage_journal_exception_test.cpp) · [Source index](../../../README.md) · [Subsystem contracts](../../../subsystem_contracts.md) · [Reviewed primitives](../../../primitives.md)

Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection.

Snapshot SHA-256: `c3bd36e432ca88bf4834668e82cc79b5ae165a935ead3832e54c4ad7eff8a21c`. 425 lines partitioned into 50 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [tests](../../../subsystem_contracts.md#tests). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/code_review.md](../../../../code_review.md), [docs/reference_fuzz.md](../../../../reference_fuzz.md), [docs/task_ledger.md](../../../../task_ledger.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–18](../../../../../tests/unit/storage_journal_exception_test.cpp#L1) | Imports dependencies; declares namespace scope; declares values/defaults or compile-time conditions. | growth new; source comment (unverified): // This binary injects failures at ordinary global-new allocation attempts. · [reviewed contract](#b0001) |
| [B0002 · 19–23](../../../../../tests/unit/storage_journal_exception_test.cpp#L19) | Callable definition: \[\[gnu::noinline\]\] void* malloc_new(std::size_t bytes) | calls std::malloc; returns result; growth malloc · [reviewed contract](#b0002) |
| [B0003 · 24–26](../../../../../tests/unit/storage_journal_exception_test.cpp#L24) | Type/record definition: struct ResetFailure |  · [reviewed contract](#b0003) |
| [B0004 · 27–28](../../../../../tests/unit/storage_journal_exception_test.cpp#L27) | Closes surrounding scope/type. | source comment (unverified): // namespace · [reviewed contract](#b0004) |
| [B0005 · 29–29](../../../../../tests/unit/storage_journal_exception_test.cpp#L29) | Callable definition: void* operator new(std::size_t bytes) | calls malloc_new; returns malloc_new(bytes); growth new · [reviewed contract](#b0005) |
| [B0006 · 30–30](../../../../../tests/unit/storage_journal_exception_test.cpp#L30) | Callable definition: void* operator new\[\](std::size_t bytes) | calls ; returns malloc_new(bytes); growth new · [reviewed contract](#b0006) |
| [B0007 · 31–31](../../../../../tests/unit/storage_journal_exception_test.cpp#L31) | Callable definition: void operator delete(void* pointer) noexcept | calls std::free · [reviewed contract](#b0007) |
| [B0008 · 32–32](../../../../../tests/unit/storage_journal_exception_test.cpp#L32) | Callable definition: void operator delete\[\](void* pointer) noexcept | calls  · [reviewed contract](#b0008) |
| [B0009 · 33–33](../../../../../tests/unit/storage_journal_exception_test.cpp#L33) | Callable definition: void operator delete(void* pointer, std::size_t) noexcept | calls std::free · [reviewed contract](#b0009) |
| [B0010 · 34–34](../../../../../tests/unit/storage_journal_exception_test.cpp#L34) | Callable definition: void operator delete\[\](void* pointer, std::size_t) noexcept | calls  · [reviewed contract](#b0010) |
| [B0011 · 35–39](../../../../../tests/unit/storage_journal_exception_test.cpp#L35) | declares namespace scope; declares aliases. |  · [reviewed contract](#b0011) |
| [B0012 · 40–42](../../../../../tests/unit/storage_journal_exception_test.cpp#L40) | Callable definition: void check(bool condition, std::string_view message) | calls std::runtime_error, std::string; guard void check(bool condition, std::string_view message) { · [reviewed contract](#b0012) |
| [B0013 · 43–43](../../../../../tests/unit/storage_journal_exception_test.cpp#L43) | Explanatory comments or spacing. |  |
| [B0014 · 44–53](../../../../../tests/unit/storage_journal_exception_test.cpp#L44) | Callable definition: template &lt;class Action&gt; void expect_error(Action&& action, std::string_view code) | calls action, check, code, std::runtime_error; guard check(failure.code() == code, "unexpected storage error code"); · [reviewed contract](#b0014) |
| [B0015 · 54–54](../../../../../tests/unit/storage_journal_exception_test.cpp#L54) | Explanatory comments or spacing. |  |
| [B0016 · 55–59](../../../../../tests/unit/storage_journal_exception_test.cpp#L55) | Callable definition: TupleLayout source_layout() | calls ; returns TupleLayout{LayoutId{1}, · [reviewed contract](#b0016) |
| [B0017 · 60–60](../../../../../tests/unit/storage_journal_exception_test.cpp#L60) | Explanatory comments or spacing. |  |
| [B0018 · 61–65](../../../../../tests/unit/storage_journal_exception_test.cpp#L61) | Callable definition: std::string long_text(char fill, std::string_view suffix) | calls result, append; returns result · [reviewed contract](#b0018) |
| [B0019 · 66–66](../../../../../tests/unit/storage_journal_exception_test.cpp#L66) | Explanatory comments or spacing. |  |
| [B0020 · 67–70](../../../../../tests/unit/storage_journal_exception_test.cpp#L67) | Callable definition: Tuple make_row(const TupleLayout& layout, std::int64_t group, std::string value, std::string_view amount, std::int64_t ordinal) | calls tuple, std::move, Decimal::parse; returns layout.tuple(Row{Value{group}, Value{std::move(value)}, Value{Decimal::parse(amount)}, Value{ordina… · [reviewed contract](#b0020) |
| [B0021 · 71–80](../../../../../tests/unit/storage_journal_exception_test.cpp#L71) | declares types or opens a type body. |  · [reviewed contract](#b0021) |
| [B0022 · 81–111](../../../../../tests/unit/storage_journal_exception_test.cpp#L81) | Callable definition: Fixture() | calls push_back, make_row, long_text, reserve; guard check(result.inserted, "fixture row unexpectedly duplicated");; growth insert, push_back, reserve; 4 loop sites · [reviewed contract](#b0022) |
| [B0023 · 112–113](../../../../../tests/unit/storage_journal_exception_test.cpp#L112) | Closes surrounding scope/type. |  · [reviewed contract](#b0023) |
| [B0024 · 114–118](../../../../../tests/unit/storage_journal_exception_test.cpp#L114) | Type/record definition: struct IndexImage |  · [reviewed contract](#b0024) |
| [B0025 · 119–119](../../../../../tests/unit/storage_journal_exception_test.cpp#L119) | Explanatory comments or spacing. |  |
| [B0026 · 120–126](../../../../../tests/unit/storage_journal_exception_test.cpp#L120) | Type/record definition: struct TableImage |  · [reviewed contract](#b0026) |
| [B0027 · 127–127](../../../../../tests/unit/storage_journal_exception_test.cpp#L127) | Explanatory comments or spacing. |  |
| [B0028 · 128–149](../../../../../tests/unit/storage_journal_exception_test.cpp#L128) | Callable definition: TableImage capture(const ReferenceTable& table) | calls snapshot, reserve, size, find; guard check(handle.has_value(), "snapshot row has no handle");; returns result; growth push_back, reserve; 3 loop sites · [reviewed contract](#b0028) |
| [B0029 · 150–150](../../../../../tests/unit/storage_journal_exception_test.cpp#L150) | Explanatory comments or spacing. |  |
| [B0030 · 151–182](../../../../../tests/unit/storage_journal_exception_test.cpp#L151) | Callable definition: void expect_image(const ReferenceTable& table, const TableImage& before, const Fixture& fixture) | calls snapshot, check, size, indices; guard check(after_rows == before.rows, "journal rollback did not restore full rows");; 4 loop sites · [reviewed contract](#b0030) |
| [B0031 · 183–183](../../../../../tests/unit/storage_journal_exception_test.cpp#L183) | Explanatory comments or spacing. |  |
| [B0032 · 184–186](../../../../../tests/unit/storage_journal_exception_test.cpp#L184) | Callable definition: Tuple retry_row(const TupleLayout& layout) | calls make_row, long_text; returns make_row(layout, 8, long_text(@ , @ ), @ , 90) · [reviewed contract](#b0032) |
| [B0033 · 187–187](../../../../../tests/unit/storage_journal_exception_test.cpp#L187) | Explanatory comments or spacing. |  |
| [B0034 · 188–196](../../../../../tests/unit/storage_journal_exception_test.cpp#L188) | Type/record definition: struct TransactionRows |  · [reviewed contract](#b0034) |
| [B0035 · 197–197](../../../../../tests/unit/storage_journal_exception_test.cpp#L197) | Explanatory comments or spacing. |  |
| [B0036 · 198–216](../../../../../tests/unit/storage_journal_exception_test.cpp#L198) | Callable definition: void apply_mixed_transaction(ReferenceTable::Journal& journal, Fixture& fixture, const TransactionRows& rows) | calls insert, check, erase; guard check(first.inserted && first.handle.tuple.value == 7, "first journal insert consumed the wrong ID"…; growth insert · [reviewed contract](#b0036) |
| [B0037 · 217–217](../../../../../tests/unit/storage_journal_exception_test.cpp#L217) | Explanatory comments or spacing. |  |
| [B0038 · 218–275](../../../../../tests/unit/storage_journal_exception_test.cpp#L218) | Callable definition: std::size_t allocation_failures() | calls capture, revision, live, projection; guard check(live.next().has_value(), "journal begin failure invalidated a cursor without mutation");; returns failures; growth insert; 1 loop sites; source comment (unverified): // Keep failure injection active through no-throw destruction. · [reviewed contract](#b0038) |
| [B0039 · 276–276](../../../../../tests/unit/storage_journal_exception_test.cpp#L276) | Explanatory comments or spacing. |  |
| [B0040 · 277–311](../../../../../tests/unit/storage_journal_exception_test.cpp#L277) | Callable definition: void active_journal_guards() | calls capture, revision, make_row, long_text; guard check(journal.active(), "new journal is not active");; growth insert · [reviewed contract](#b0040) |
| [B0041 · 312–312](../../../../../tests/unit/storage_journal_exception_test.cpp#L312) | Explanatory comments or spacing. |  |
| [B0042 · 313–323](../../../../../tests/unit/storage_journal_exception_test.cpp#L313) | Callable definition: void exercise_mixed_operations(ReferenceTable::Journal& journal, Fixture& fixture, const TransactionRows& rows) | calls apply_mixed_transaction, check, size, change; guard check(journal.size() == 8, "journal change history omitted a real change or recorded a no-op"); · [reviewed contract](#b0042) |
| [B0043 · 324–324](../../../../../tests/unit/storage_journal_exception_test.cpp#L324) | Explanatory comments or spacing. |  |
| [B0044 · 325–349](../../../../../tests/unit/storage_journal_exception_test.cpp#L325) | Callable definition: void explicit_rollback_is_allocation_free() | calls capture, revision, live, bucket_cursor; guard check(fixture.table.revision() &gt; old_revision, "tentative journal mutations did not advance revisio…; growth insert · [reviewed contract](#b0044) |
| [B0045 · 350–350](../../../../../tests/unit/storage_journal_exception_test.cpp#L350) | Explanatory comments or spacing. |  |
| [B0046 · 351–365](../../../../../tests/unit/storage_journal_exception_test.cpp#L351) | Callable definition: void destructor_rollback_is_allocation_free() | calls capture, revision, rows, journal; guard check(fixture.table.revision() &gt; old_revision, "destructor rollback restored the old revision");; source comment (unverified): // Let the journal destructor roll back while ordinary global-new attempts fail. · [reviewed contract](#b0046) |
| [B0047 · 366–366](../../../../../tests/unit/storage_journal_exception_test.cpp#L366) | Explanatory comments or spacing. |  |
| [B0048 · 367–398](../../../../../tests/unit/storage_journal_exception_test.cpp#L367) | Callable definition: ReferenceTable::Journal committed_journal_after_owner_destruction() | calls make_row, long_text, journal, insert; guard check(new_row.inserted, "commit fixture insert was not inserted");; returns journal; retained; growth insert · [reviewed contract](#b0048) |
| [B0049 · 399–401](../../../../../tests/unit/storage_journal_exception_test.cpp#L399) | Closes surrounding scope/type. | source comment (unverified): // namespace · [reviewed contract](#b0049) |
| [B0050 · 402–425](../../../../../tests/unit/storage_journal_exception_test.cpp#L402) | Callable definition: int main() | calls allocation_failures, check, active_journal_guards, explicit_rollback_is_allocation_free; guard check(failures &gt; 0, "journal allocation sweep did not exercise allocation failures");; returns 1 · [reviewed contract](#b0050) |

## B0001

[Lines 1–18](../../../../../tests/unit/storage_journal_exception_test.cpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L1-L18:sha256:e99a2e0fbc719ec1d3e88110bb1540f5d7ba864a4434ae63ee28a2b321bd595a
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Prepare storage_journal_exception_test.cpp: include "crown/api/error.hpp", "crown/storage/reference.hpp", &lt;cstddef&gt;, &lt;cstdlib&gt;, &lt;cstdint&gt;, &lt;iostream&gt;, &lt;new&gt;, &lt;stdexcept&gt;, &lt;string&gt;, &lt;string_view&gt;, &lt;utility&gt;, &lt;vector&gt;; declare fixture state/default initializers. |
| inputs / outputs | Compiler-visible dependencies, names and the recorded declarations in; declarations available to the following fixture/CLI/example definitions out. The source span lists the exact member/global names, types and initial values; initializers run when the enclosing object/program/thread is initialized. |
| invariants | Declarations are scoped to this source/header and its selected ABI. Included code has its own effects; names and editable fixture values do not confer proof, admission or publication authority. |
| ownership | Aliases/includes do not create a query owner. Pointers/references/views are non-owning. Containers own their elements, which can themselves be borrowed pointers or numeric IDs. Only documented owning shared-control handles retain controls; IDs/slot-handle values do not independently keep an arena/runtime alive. Thread-local fault/countdown state belongs to this test executable and each thread; it is not a field added to a production owner. |
| failure | Missing headers, ill-formed names/types, failed static assertions or active #error directives stop compilation. No runtime rejection/rollback mechanism is implemented by aliases or function prototypes. |
| cost | Preprocessing and type/constraint instantiation cost compilation. Alias/prototype syntax does not invoke the declared operation; any included definitions keep their own initialization effects. This span initializes fixed scalar/atomic/TLS probe state. Storage and later probe accesses are test costs; no native factory or filesystem operation is implied by these scalar initializers. TLS storage and later injector accesses are test instrumentation costs. |
| Design | [tests/unit/storage_journal_exception_test.cpp](../../../../../tests/unit/storage_journal_exception_test.cpp), [docs/session-journal.md](../../../../session-journal.md), [docs/code_review.md](../../../../code_review.md) |

## B0002

[Lines 19–23](../../../../../tests/unit/storage_journal_exception_test.cpp#L19); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
[[gnu::noinline]] void* malloc_new(std::size_t bytes)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Implement the exception-journal test's ordinary global-new failure seam. |
| inputs / outputs | Callable: \[\[gnu::noinline\]\] void* malloc_new(std::size_t bytes). Input: requested byte count. Output: malloc-backed storage or std::bad_alloc when fail_after reaches zero. |
| invariants | Only ordinary new/new\[\] calls routed through local replacements are injected; direct allocator calls and aligned-new overloads are outside the seam. |
| ownership | ReferenceTable owns its current logical rows and indexes. Fixture fields and captured images are test-owned copies except stored tuple addresses, which borrow from the live table; committed journals own affected payload pins. |
| failure | A failed check throws std::runtime_error; expect_error accepts only the requested crown::Error. The allocation sweep catches std::bad_alloc from ordinary global-new injection and keeps it armed through undo. |
| cost | Uses the six-row fixture and five secondary indexes unless a bounded sweep is stated. This is rollback evidence for that fixture, not a general resource bound. |
| Design | [include/crown/storage/reference.hpp](../../../../../include/crown/storage/reference.hpp), [src/storage/reference.cpp](../../../../../src/storage/reference.cpp), [docs/storage_journal.md §Purpose and API](../../../../storage_journal.md), [docs/storage_journal.md §Undo records and identity restoration](../../../../storage_journal.md), [docs/tuple_arenas.md §Ownership and identity](../../../../tuple_arenas.md), [docs/tuple_arenas.md §Allocation failure and inspection](../../../../tuple_arenas.md) |

## B0003

[Lines 24–26](../../../../../tests/unit/storage_journal_exception_test.cpp#L24); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct ResetFailure
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Disable ordinary global-new failure injection when its guard is destroyed. |
| inputs / outputs | Type: struct ResetFailure. Input: none. Output: no value; destructor sets fail_after to -1. |
| invariants | The guard is noncopyable and does not restore a nested countdown. |
| ownership | ReferenceTable owns its current logical rows and indexes. Fixture fields and captured images are test-owned copies except stored tuple addresses, which borrow from the live table; committed journals own affected payload pins. |
| failure | A failed check throws std::runtime_error; expect_error accepts only the requested crown::Error. The allocation sweep catches std::bad_alloc from ordinary global-new injection and keeps it armed through undo. |
| cost | Uses the six-row fixture and five secondary indexes unless a bounded sweep is stated. This is rollback evidence for that fixture, not a general resource bound. |
| Design | [include/crown/storage/reference.hpp](../../../../../include/crown/storage/reference.hpp), [src/storage/reference.cpp](../../../../../src/storage/reference.cpp), [docs/storage_journal.md §Purpose and API](../../../../storage_journal.md), [docs/storage_journal.md §Undo records and identity restoration](../../../../storage_journal.md), [docs/tuple_arenas.md §Ownership and identity](../../../../tuple_arenas.md), [docs/tuple_arenas.md §Allocation failure and inspection](../../../../tuple_arenas.md) |

## B0004

[Lines 27–28](../../../../../tests/unit/storage_journal_exception_test.cpp#L27); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L27-L28:sha256:c2bd7638f09d52cb034ed574f539304035fc6fab162bf8d5fa20a35d8c7288a1
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Close the recorded declaration scopes in storage_journal_exception_test.cpp: namespace (anonymous). |
| inputs / outputs | Preceding namespace, type or initializer declarations in; completed lexical boundary out. |
| invariants | Brace-opening context is recorded in root-scope-context-v1.json. These are declaration/initializer boundaries, not an independent update, validation or recovery operation. |
| ownership | Enclosing objects and borrowed fields keep their declared ownership. This punctuation creates no new owner. |
| failure | Malformed scope syntax is a compile error. Any initializer/constructor failure belongs to the enclosing object declaration. |
| cost | No separate loop, guard or engine call is introduced by the delimiter; enclosing initialization and object lifetime still have their actual costs. |
| Design | [tests/unit/storage_journal_exception_test.cpp](../../../../../tests/unit/storage_journal_exception_test.cpp), [docs/session-journal.md](../../../../session-journal.md), [docs/code_review.md](../../../../code_review.md) |

## B0005

[Lines 29–29](../../../../../tests/unit/storage_journal_exception_test.cpp#L29); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void* operator new(std::size_t bytes)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Route scalar global-new requests through the exception test's malloc_new seam. |
| inputs / outputs | Callable: void* operator new(std::size_t bytes). Input: bytes. Output: allocated pointer or std::bad_alloc. |
| invariants | Only this standalone executable interposes the ordinary scalar overload. |
| ownership | ReferenceTable owns its current logical rows and indexes. Fixture fields and captured images are test-owned copies except stored tuple addresses, which borrow from the live table; committed journals own affected payload pins. |
| failure | A failed check throws std::runtime_error; expect_error accepts only the requested crown::Error. The allocation sweep catches std::bad_alloc from ordinary global-new injection and keeps it armed through undo. |
| cost | Uses the six-row fixture and five secondary indexes unless a bounded sweep is stated. This is rollback evidence for that fixture, not a general resource bound. |
| Design | [include/crown/storage/reference.hpp](../../../../../include/crown/storage/reference.hpp), [src/storage/reference.cpp](../../../../../src/storage/reference.cpp), [docs/storage_journal.md §Purpose and API](../../../../storage_journal.md), [docs/storage_journal.md §Undo records and identity restoration](../../../../storage_journal.md), [docs/tuple_arenas.md §Ownership and identity](../../../../tuple_arenas.md), [docs/tuple_arenas.md §Allocation failure and inspection](../../../../tuple_arenas.md) |

## B0006

[Lines 30–30](../../../../../tests/unit/storage_journal_exception_test.cpp#L30); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void* operator new[](std::size_t bytes)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Route array global-new requests through the exception test's malloc_new seam. |
| inputs / outputs | Callable: void* operator new\[\](std::size_t bytes). Input: bytes. Output: allocated pointer or std::bad_alloc. |
| invariants | Only this standalone executable interposes the ordinary array overload. |
| ownership | ReferenceTable owns its current logical rows and indexes. Fixture fields and captured images are test-owned copies except stored tuple addresses, which borrow from the live table; committed journals own affected payload pins. |
| failure | A failed check throws std::runtime_error; expect_error accepts only the requested crown::Error. The allocation sweep catches std::bad_alloc from ordinary global-new injection and keeps it armed through undo. |
| cost | Uses the six-row fixture and five secondary indexes unless a bounded sweep is stated. This is rollback evidence for that fixture, not a general resource bound. |
| Design | [include/crown/storage/reference.hpp](../../../../../include/crown/storage/reference.hpp), [src/storage/reference.cpp](../../../../../src/storage/reference.cpp), [docs/storage_journal.md §Purpose and API](../../../../storage_journal.md), [docs/storage_journal.md §Undo records and identity restoration](../../../../storage_journal.md), [docs/tuple_arenas.md §Ownership and identity](../../../../tuple_arenas.md), [docs/tuple_arenas.md §Allocation failure and inspection](../../../../tuple_arenas.md) |

## B0007

[Lines 31–31](../../../../../tests/unit/storage_journal_exception_test.cpp#L31); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void operator delete(void* pointer) noexcept
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Free storage from the local scalar global-new replacement. |
| inputs / outputs | Callable: void operator delete(void* pointer) noexcept. Input: possibly null pointer. Output: none. |
| invariants | The replacement calls std::free without consulting fail_after. |
| ownership | ReferenceTable owns its current logical rows and indexes. Fixture fields and captured images are test-owned copies except stored tuple addresses, which borrow from the live table; committed journals own affected payload pins. |
| failure | A failed check throws std::runtime_error; expect_error accepts only the requested crown::Error. The allocation sweep catches std::bad_alloc from ordinary global-new injection and keeps it armed through undo. |
| cost | Uses the six-row fixture and five secondary indexes unless a bounded sweep is stated. This is rollback evidence for that fixture, not a general resource bound. |
| Design | [include/crown/storage/reference.hpp](../../../../../include/crown/storage/reference.hpp), [src/storage/reference.cpp](../../../../../src/storage/reference.cpp), [docs/storage_journal.md §Purpose and API](../../../../storage_journal.md), [docs/storage_journal.md §Undo records and identity restoration](../../../../storage_journal.md), [docs/tuple_arenas.md §Ownership and identity](../../../../tuple_arenas.md), [docs/tuple_arenas.md §Allocation failure and inspection](../../../../tuple_arenas.md) |

## B0008

[Lines 32–32](../../../../../tests/unit/storage_journal_exception_test.cpp#L32); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void operator delete[](void* pointer) noexcept
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Free storage from the local array global-new replacement. |
| inputs / outputs | Callable: void operator delete\[\](void* pointer) noexcept. Input: possibly null pointer. Output: none. |
| invariants | The replacement calls std::free without consulting fail_after. |
| ownership | ReferenceTable owns its current logical rows and indexes. Fixture fields and captured images are test-owned copies except stored tuple addresses, which borrow from the live table; committed journals own affected payload pins. |
| failure | A failed check throws std::runtime_error; expect_error accepts only the requested crown::Error. The allocation sweep catches std::bad_alloc from ordinary global-new injection and keeps it armed through undo. |
| cost | Uses the six-row fixture and five secondary indexes unless a bounded sweep is stated. This is rollback evidence for that fixture, not a general resource bound. |
| Design | [include/crown/storage/reference.hpp](../../../../../include/crown/storage/reference.hpp), [src/storage/reference.cpp](../../../../../src/storage/reference.cpp), [docs/storage_journal.md §Purpose and API](../../../../storage_journal.md), [docs/storage_journal.md §Undo records and identity restoration](../../../../storage_journal.md), [docs/tuple_arenas.md §Ownership and identity](../../../../tuple_arenas.md), [docs/tuple_arenas.md §Allocation failure and inspection](../../../../tuple_arenas.md) |

## B0009

[Lines 33–33](../../../../../tests/unit/storage_journal_exception_test.cpp#L33); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void operator delete(void* pointer, std::size_t) noexcept
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Free sized scalar storage from the local global-new replacement. |
| inputs / outputs | Callable: void operator delete(void* pointer, std::size_t) noexcept. Inputs: pointer and ignored size. Output: none. |
| invariants | The matching delete calls std::free and does not inject failures. |
| ownership | ReferenceTable owns its current logical rows and indexes. Fixture fields and captured images are test-owned copies except stored tuple addresses, which borrow from the live table; committed journals own affected payload pins. |
| failure | A failed check throws std::runtime_error; expect_error accepts only the requested crown::Error. The allocation sweep catches std::bad_alloc from ordinary global-new injection and keeps it armed through undo. |
| cost | Uses the six-row fixture and five secondary indexes unless a bounded sweep is stated. This is rollback evidence for that fixture, not a general resource bound. |
| Design | [include/crown/storage/reference.hpp](../../../../../include/crown/storage/reference.hpp), [src/storage/reference.cpp](../../../../../src/storage/reference.cpp), [docs/storage_journal.md §Purpose and API](../../../../storage_journal.md), [docs/storage_journal.md §Undo records and identity restoration](../../../../storage_journal.md), [docs/tuple_arenas.md §Ownership and identity](../../../../tuple_arenas.md), [docs/tuple_arenas.md §Allocation failure and inspection](../../../../tuple_arenas.md) |

## B0010

[Lines 34–34](../../../../../tests/unit/storage_journal_exception_test.cpp#L34); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void operator delete[](void* pointer, std::size_t) noexcept
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Free sized array storage from the local global-new replacement. |
| inputs / outputs | Callable: void operator delete\[\](void* pointer, std::size_t) noexcept. Inputs: pointer and ignored size. Output: none. |
| invariants | The matching delete calls std::free and does not inject failures. |
| ownership | ReferenceTable owns its current logical rows and indexes. Fixture fields and captured images are test-owned copies except stored tuple addresses, which borrow from the live table; committed journals own affected payload pins. |
| failure | A failed check throws std::runtime_error; expect_error accepts only the requested crown::Error. The allocation sweep catches std::bad_alloc from ordinary global-new injection and keeps it armed through undo. |
| cost | Uses the six-row fixture and five secondary indexes unless a bounded sweep is stated. This is rollback evidence for that fixture, not a general resource bound. |
| Design | [include/crown/storage/reference.hpp](../../../../../include/crown/storage/reference.hpp), [src/storage/reference.cpp](../../../../../src/storage/reference.cpp), [docs/storage_journal.md §Purpose and API](../../../../storage_journal.md), [docs/storage_journal.md §Undo records and identity restoration](../../../../storage_journal.md), [docs/tuple_arenas.md §Ownership and identity](../../../../tuple_arenas.md), [docs/tuple_arenas.md §Allocation failure and inspection](../../../../tuple_arenas.md) |

## B0011

[Lines 35–39](../../../../../tests/unit/storage_journal_exception_test.cpp#L35); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L35-L39:sha256:f23c5a94ebfd83ca0850025ccb8c05140fdd3ce1eb2d5b84b654436fde82c70d
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Prepare storage_journal_exception_test.cpp: bind local aliases/name imports. |
| inputs / outputs | Compiler-visible dependencies, names and the recorded declarations in; declarations available to the following fixture/CLI/example definitions out. |
| invariants | Declarations are scoped to this source/header and its selected ABI. Included code has its own effects; names and editable fixture values do not confer proof, admission or publication authority. |
| ownership | Aliases/includes do not create a query owner. Pointers/references/views are non-owning. Containers own their elements, which can themselves be borrowed pointers or numeric IDs. Only documented owning shared-control handles retain controls; IDs/slot-handle values do not independently keep an arena/runtime alive. |
| failure | Missing headers, ill-formed names/types, failed static assertions or active #error directives stop compilation. No runtime rejection/rollback mechanism is implemented by aliases or function prototypes. |
| cost | Preprocessing and type/constraint instantiation cost compilation. Alias/prototype syntax does not invoke the declared operation; any included definitions keep their own initialization effects. |
| Design | [tests/unit/storage_journal_exception_test.cpp](../../../../../tests/unit/storage_journal_exception_test.cpp), [docs/session-journal.md](../../../../session-journal.md), [docs/code_review.md](../../../../code_review.md) |

## B0012

[Lines 40–42](../../../../../tests/unit/storage_journal_exception_test.cpp#L40); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void check(bool condition, std::string_view message)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Raise a storage-journal test failure with the supplied diagnostic. |
| inputs / outputs | Callable: void check(bool condition, std::string_view message). Inputs: Boolean condition and string_view message. Output: none for true; false throws std::runtime_error. |
| invariants | A failed check is not treated as an expected storage API error. |
| ownership | ReferenceTable owns its current logical rows and indexes. Fixture fields and captured images are test-owned copies except stored tuple addresses, which borrow from the live table; committed journals own affected payload pins. |
| failure | A failed check throws std::runtime_error; expect_error accepts only the requested crown::Error. The allocation sweep catches std::bad_alloc from ordinary global-new injection and keeps it armed through undo. |
| cost | Uses the six-row fixture and five secondary indexes unless a bounded sweep is stated. This is rollback evidence for that fixture, not a general resource bound. |
| Design | [include/crown/storage/reference.hpp](../../../../../include/crown/storage/reference.hpp), [src/storage/reference.cpp](../../../../../src/storage/reference.cpp), [docs/storage_journal.md §Purpose and API](../../../../storage_journal.md), [docs/storage_journal.md §Undo records and identity restoration](../../../../storage_journal.md), [docs/tuple_arenas.md §Ownership and identity](../../../../tuple_arenas.md), [docs/tuple_arenas.md §Allocation failure and inspection](../../../../tuple_arenas.md) |

## B0014

[Lines 44–53](../../../../../tests/unit/storage_journal_exception_test.cpp#L44); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
template <class Action>
void expect_error(Action&& action, std::string_view code)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Require a callable to throw the selected storage Error code. |
| inputs / outputs | Callable: template &lt;class Action&gt; void expect_error(Action&& action, std::string_view code). Inputs: action and expected string_view code. Output: none for a matching crown::Error. |
| invariants | A wrong error code or normal return throws std::runtime_error and fails the test. |
| ownership | ReferenceTable owns its current logical rows and indexes. Fixture fields and captured images are test-owned copies except stored tuple addresses, which borrow from the live table; committed journals own affected payload pins. |
| failure | A failed check throws std::runtime_error; expect_error accepts only the requested crown::Error. The allocation sweep catches std::bad_alloc from ordinary global-new injection and keeps it armed through undo. |
| cost | Uses the six-row fixture and five secondary indexes unless a bounded sweep is stated. This is rollback evidence for that fixture, not a general resource bound. |
| Design | [include/crown/storage/reference.hpp](../../../../../include/crown/storage/reference.hpp), [src/storage/reference.cpp](../../../../../src/storage/reference.cpp), [docs/storage_journal.md §Purpose and API](../../../../storage_journal.md), [docs/storage_journal.md §Undo records and identity restoration](../../../../storage_journal.md), [docs/tuple_arenas.md §Ownership and identity](../../../../tuple_arenas.md), [docs/tuple_arenas.md §Allocation failure and inspection](../../../../tuple_arenas.md) |

## B0016

[Lines 55–59](../../../../../tests/unit/storage_journal_exception_test.cpp#L55); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
TupleLayout source_layout()
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Create the four-field typed tuple layout used by exception journal fixtures. |
| inputs / outputs | Callable: TupleLayout source_layout(). Input: none. Output: int64 group, string value, decimal(18,2), and int64 ordinal fields. |
| invariants | The decimal precision and scale constrain all make_row decimal values. |
| ownership | ReferenceTable owns its current logical rows and indexes. Fixture fields and captured images are test-owned copies except stored tuple addresses, which borrow from the live table; committed journals own affected payload pins. |
| failure | A failed check throws std::runtime_error; expect_error accepts only the requested crown::Error. The allocation sweep catches std::bad_alloc from ordinary global-new injection and keeps it armed through undo. |
| cost | Uses the six-row fixture and five secondary indexes unless a bounded sweep is stated. This is rollback evidence for that fixture, not a general resource bound. |
| Design | [include/crown/storage/reference.hpp](../../../../../include/crown/storage/reference.hpp), [src/storage/reference.cpp](../../../../../src/storage/reference.cpp), [docs/storage_journal.md §Purpose and API](../../../../storage_journal.md), [docs/storage_journal.md §Undo records and identity restoration](../../../../storage_journal.md), [docs/tuple_arenas.md §Ownership and identity](../../../../tuple_arenas.md), [docs/tuple_arenas.md §Allocation failure and inspection](../../../../tuple_arenas.md) |

## B0018

[Lines 61–65](../../../../../tests/unit/storage_journal_exception_test.cpp#L61); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::string long_text(char fill, std::string_view suffix)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Build a 240-character payload and append the supplied fixture suffix. |
| inputs / outputs | Callable: std::string long_text(char fill, std::string_view suffix). Inputs: fill character and suffix view. Output: owning string. |
| invariants | The resulting value contains the complete suffix and is longer than the fixed fill prefix. |
| ownership | ReferenceTable owns its current logical rows and indexes. Fixture fields and captured images are test-owned copies except stored tuple addresses, which borrow from the live table; committed journals own affected payload pins. |
| failure | A failed check throws std::runtime_error; expect_error accepts only the requested crown::Error. The allocation sweep catches std::bad_alloc from ordinary global-new injection and keeps it armed through undo. |
| cost | Uses the six-row fixture and five secondary indexes unless a bounded sweep is stated. This is rollback evidence for that fixture, not a general resource bound. |
| Design | [include/crown/storage/reference.hpp](../../../../../include/crown/storage/reference.hpp), [src/storage/reference.cpp](../../../../../src/storage/reference.cpp), [docs/storage_journal.md §Purpose and API](../../../../storage_journal.md), [docs/storage_journal.md §Undo records and identity restoration](../../../../storage_journal.md), [docs/tuple_arenas.md §Ownership and identity](../../../../tuple_arenas.md), [docs/tuple_arenas.md §Allocation failure and inspection](../../../../tuple_arenas.md) |

## B0020

[Lines 67–70](../../../../../tests/unit/storage_journal_exception_test.cpp#L67); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Tuple make_row(const TupleLayout& layout, std::int64_t group, std::string value,
               std::string_view amount, std::int64_t ordinal)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Construct one typed four-field Tuple using fixture group/text/amount/ordinal values. |
| inputs / outputs | Callable: Tuple make_row(const TupleLayout& layout, std::int64_t group, std::string value, std::string_view amount, std::int64_t ordinal). Inputs: layout, group, owning text, decimal text, ordinal. Output: layout-owned tuple. |
| invariants | The amount is parsed as Decimal before tuple validation under decimal(18,2). |
| ownership | ReferenceTable owns its current logical rows and indexes. Fixture fields and captured images are test-owned copies except stored tuple addresses, which borrow from the live table; committed journals own affected payload pins. |
| failure | A failed check throws std::runtime_error; expect_error accepts only the requested crown::Error. The allocation sweep catches std::bad_alloc from ordinary global-new injection and keeps it armed through undo. |
| cost | Uses the six-row fixture and five secondary indexes unless a bounded sweep is stated. This is rollback evidence for that fixture, not a general resource bound. |
| Design | [include/crown/storage/reference.hpp](../../../../../include/crown/storage/reference.hpp), [src/storage/reference.cpp](../../../../../src/storage/reference.cpp), [docs/storage_journal.md §Purpose and API](../../../../storage_journal.md), [docs/storage_journal.md §Undo records and identity restoration](../../../../storage_journal.md), [docs/tuple_arenas.md §Ownership and identity](../../../../tuple_arenas.md), [docs/tuple_arenas.md §Allocation failure and inspection](../../../../tuple_arenas.md) |

## B0021

[Lines 71–80](../../../../../tests/unit/storage_journal_exception_test.cpp#L71); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L71-L80:sha256:d8a6764061be64c7c86fad7369520f1d783a587a62282111acc234fb9a4dd10b
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Prepare storage_journal_exception_test.cpp: declare fixture state/default initializers. |
| inputs / outputs | Compiler-visible dependencies, names and the recorded declarations in; declarations available to the following fixture/CLI/example definitions out. The source span lists the exact member/global names, types and initial values; initializers run when the enclosing object/program/thread is initialized. |
| invariants | Declarations are scoped to this source/header and its selected ABI. Included code has its own effects; names and editable fixture values do not confer proof, admission or publication authority. |
| ownership | Aliases/includes do not create a query owner. Pointers/references/views are non-owning. Containers own their elements, which can themselves be borrowed pointers or numeric IDs. Only documented owning shared-control handles retain controls; IDs/slot-handle values do not independently keep an arena/runtime alive. |
| failure | Missing headers, ill-formed names/types, failed static assertions or active #error directives stop compilation. No runtime rejection/rollback mechanism is implemented by aliases or function prototypes. Actual object construction and explicit initializers keep the failure contracts of their declared types/called helpers; this card supplies no extra rollback. |
| cost | Preprocessing and type/constraint instantiation cost compilation. Alias/prototype syntax does not invoke the declared operation; any included definitions keep their own initialization effects. Member/global initialization follows the shown C++ types and expressions when its enclosing object/program is constructed; owning containers can allocate. Default member declarations do not themselves instantiate a fixture. Copies and teardown follow the owning types. |
| Design | [tests/unit/storage_journal_exception_test.cpp](../../../../../tests/unit/storage_journal_exception_test.cpp), [docs/session-journal.md](../../../../session-journal.md), [docs/code_review.md](../../../../code_review.md) |

## B0022

[Lines 81–111](../../../../../tests/unit/storage_journal_exception_test.cpp#L81); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Fixture()
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Own the six-row indexed ReferenceTable, row handles, and explicit arena pins used by rollback checks. |
| inputs / outputs | Callable: Fixture(). Construction: six fixed typed rows, five projections over source slots, and one pin per inserted handle. |
| invariants | The fixture retains original tuple identities and source values while journal operations mutate table membership. |
| ownership | The fixture owns the reference table, six source Tuples, row handles, five index IDs, and six explicit TupleArena pins. |
| failure | A failed check throws std::runtime_error; expect_error accepts only the requested crown::Error. The allocation sweep catches std::bad_alloc from ordinary global-new injection and keeps it armed through undo. |
| cost | Uses the six-row fixture and five secondary indexes unless a bounded sweep is stated. This is rollback evidence for that fixture, not a general resource bound. |
| Design | [include/crown/storage/reference.hpp](../../../../../include/crown/storage/reference.hpp), [src/storage/reference.cpp](../../../../../src/storage/reference.cpp), [docs/storage_journal.md §Purpose and API](../../../../storage_journal.md), [docs/storage_journal.md §Undo records and identity restoration](../../../../storage_journal.md), [docs/tuple_arenas.md §Ownership and identity](../../../../tuple_arenas.md), [docs/tuple_arenas.md §Allocation failure and inspection](../../../../tuple_arenas.md) |

## B0023

[Lines 112–113](../../../../../tests/unit/storage_journal_exception_test.cpp#L112); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L112-L113:sha256:cdbb10f75f6890449819c9d57e5ae7b786fb73c5111c5d829c37bc18f3e053e8
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Close the recorded declaration scopes in storage_journal_exception_test.cpp: struct Fixture. |
| inputs / outputs | Preceding namespace, type or initializer declarations in; completed lexical boundary out. |
| invariants | Brace-opening context is recorded in root-scope-context-v1.json. These are declaration/initializer boundaries, not an independent update, validation or recovery operation. |
| ownership | Enclosing objects and borrowed fields keep their declared ownership. This punctuation creates no new owner. |
| failure | Malformed scope syntax is a compile error. Any initializer/constructor failure belongs to the enclosing object declaration. |
| cost | No separate loop, guard or engine call is introduced by the delimiter; enclosing initialization and object lifetime still have their actual costs. |
| Design | [tests/unit/storage_journal_exception_test.cpp](../../../../../tests/unit/storage_journal_exception_test.cpp), [docs/session-journal.md](../../../../session-journal.md), [docs/code_review.md](../../../../code_review.md) |

## B0024

[Lines 114–118](../../../../../tests/unit/storage_journal_exception_test.cpp#L114); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct IndexImage
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Capture one index's identity, owning key tuples, and bucket handle vectors. |
| inputs / outputs | Type: struct IndexImage. Fields: IndexId, key Tuple list, and one TupleHandle vector per key. |
| invariants | Key and bucket vectors are copied before the failure or rollback being examined. |
| ownership | Key tuples and bucket-handle vectors are copied into the image. |
| failure | A failed check throws std::runtime_error; expect_error accepts only the requested crown::Error. The allocation sweep catches std::bad_alloc from ordinary global-new injection and keeps it armed through undo. |
| cost | Uses the six-row fixture and five secondary indexes unless a bounded sweep is stated. This is rollback evidence for that fixture, not a general resource bound. |
| Design | [include/crown/storage/reference.hpp](../../../../../include/crown/storage/reference.hpp), [src/storage/reference.cpp](../../../../../src/storage/reference.cpp), [docs/storage_journal.md §Purpose and API](../../../../storage_journal.md), [docs/storage_journal.md §Undo records and identity restoration](../../../../storage_journal.md), [docs/tuple_arenas.md §Ownership and identity](../../../../tuple_arenas.md), [docs/tuple_arenas.md §Allocation failure and inspection](../../../../tuple_arenas.md) |

## B0026

[Lines 120–126](../../../../../tests/unit/storage_journal_exception_test.cpp#L120); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct TableImage
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Hold the logical table and arena observations used for exact rollback comparison. |
| inputs / outputs | Type: struct TableImage. Fields: row copies, logical handles, borrowed tuple addresses, index images, and ArenaStatistics. |
| invariants | Address entries refer into the still-live ReferenceTable; they are compared only while its owner exists. |
| ownership | Rows/handles/index images own copies; addresses borrow table tuples and are used only with the same live table. |
| failure | A failed check throws std::runtime_error; expect_error accepts only the requested crown::Error. The allocation sweep catches std::bad_alloc from ordinary global-new injection and keeps it armed through undo. |
| cost | Uses the six-row fixture and five secondary indexes unless a bounded sweep is stated. This is rollback evidence for that fixture, not a general resource bound. |
| Design | [include/crown/storage/reference.hpp](../../../../../include/crown/storage/reference.hpp), [src/storage/reference.cpp](../../../../../src/storage/reference.cpp), [docs/storage_journal.md §Purpose and API](../../../../storage_journal.md), [docs/storage_journal.md §Undo records and identity restoration](../../../../storage_journal.md), [docs/tuple_arenas.md §Ownership and identity](../../../../tuple_arenas.md), [docs/tuple_arenas.md §Allocation failure and inspection](../../../../tuple_arenas.md) |

## B0028

[Lines 128–149](../../../../../tests/unit/storage_journal_exception_test.cpp#L128); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
TableImage capture(const ReferenceTable& table)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Snapshot rows, handle/address identity, all secondary index buckets, and arena counters before mutation. |
| inputs / outputs | Callable: TableImage capture(const ReferenceTable& table). Input: const ReferenceTable. Output: owning TableImage plus addresses into the same live table. |
| invariants | Every snapshot row must resolve to a handle; every index key gets its actual bucket captured. |
| ownership | The returned image owns its copied snapshots and index vectors; it stores nonowning tuple addresses from the input table. |
| failure | A failed check throws std::runtime_error; expect_error accepts only the requested crown::Error. The allocation sweep catches std::bad_alloc from ordinary global-new injection and keeps it armed through undo. |
| cost | Copies the six-row snapshot, five index key/bucket images, handles, addresses, and arena counters. |
| Design | [include/crown/storage/reference.hpp](../../../../../include/crown/storage/reference.hpp), [src/storage/reference.cpp](../../../../../src/storage/reference.cpp), [docs/storage_journal.md §Purpose and API](../../../../storage_journal.md), [docs/storage_journal.md §Undo records and identity restoration](../../../../storage_journal.md), [docs/tuple_arenas.md §Ownership and identity](../../../../tuple_arenas.md), [docs/tuple_arenas.md §Allocation failure and inspection](../../../../tuple_arenas.md) |

## B0030

[Lines 151–182](../../../../../tests/unit/storage_journal_exception_test.cpp#L151); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void expect_image(const ReferenceTable& table, const TableImage& before,
                  const Fixture& fixture)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Verify rollback restored the captured table/index image and fixture pins. |
| inputs / outputs | Callable: void expect_image(const ReferenceTable& table, const TableImage& before, const Fixture& fixture). Inputs: table, before image, and Fixture. Output: none when rows, keys, buckets, handles, addresses, generations, and selected arena counts match. |
| invariants | It checks all explicit pin handles remain live and calls table.check_invariants after structural comparisons. |
| ownership | All references are borrowed only for the duration of comparison; Fixture pins and the caller-owned table must remain alive. |
| failure | A failed check throws std::runtime_error; expect_error accepts only the requested crown::Error. The allocation sweep catches std::bad_alloc from ordinary global-new injection and keeps it armed through undo. |
| cost | Compares six rows, all five index images and buckets, every pinned identity, arena counters, and a full table invariant check. |
| Design | [include/crown/storage/reference.hpp](../../../../../include/crown/storage/reference.hpp), [src/storage/reference.cpp](../../../../../src/storage/reference.cpp), [docs/storage_journal.md §Purpose and API](../../../../storage_journal.md), [docs/storage_journal.md §Undo records and identity restoration](../../../../storage_journal.md), [docs/tuple_arenas.md §Ownership and identity](../../../../tuple_arenas.md), [docs/tuple_arenas.md §Allocation failure and inspection](../../../../tuple_arenas.md) |

## B0032

[Lines 184–186](../../../../../tests/unit/storage_journal_exception_test.cpp#L184); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Tuple retry_row(const TupleLayout& layout)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Produce the fixed row used to detect logical tuple-ID consumption after aborted transactions. |
| inputs / outputs | Callable: Tuple retry_row(const TupleLayout& layout). Input: TupleLayout. Output: group 8, retry-suffixed text, decimal 9.99, ordinal 90 tuple. |
| invariants | The retry value is not part of the six-row fixture and is inserted only after the journal scope ends. |
| ownership | ReferenceTable owns its current logical rows and indexes. Fixture fields and captured images are test-owned copies except stored tuple addresses, which borrow from the live table; committed journals own affected payload pins. |
| failure | A failed check throws std::runtime_error; expect_error accepts only the requested crown::Error. The allocation sweep catches std::bad_alloc from ordinary global-new injection and keeps it armed through undo. |
| cost | Uses the six-row fixture and five secondary indexes unless a bounded sweep is stated. This is rollback evidence for that fixture, not a general resource bound. |
| Design | [include/crown/storage/reference.hpp](../../../../../include/crown/storage/reference.hpp), [src/storage/reference.cpp](../../../../../src/storage/reference.cpp), [docs/storage_journal.md §Purpose and API](../../../../storage_journal.md), [docs/storage_journal.md §Undo records and identity restoration](../../../../storage_journal.md), [docs/tuple_arenas.md §Ownership and identity](../../../../tuple_arenas.md), [docs/tuple_arenas.md §Allocation failure and inspection](../../../../tuple_arenas.md) |

## B0034

[Lines 188–196](../../../../../tests/unit/storage_journal_exception_test.cpp#L188); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct TransactionRows
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Own the two insert rows and one retry row used in the mixed journal transaction. |
| inputs / outputs | Type: struct TransactionRows. Input: TupleLayout. Output: three typed Tuples with distinct groups/text/ordinals. |
| invariants | All test values are constructed before the allocation failure is armed. |
| ownership | The three row values own their strings and typed scalars and are constructed before injection. |
| failure | A failed check throws std::runtime_error; expect_error accepts only the requested crown::Error. The allocation sweep catches std::bad_alloc from ordinary global-new injection and keeps it armed through undo. |
| cost | Uses the six-row fixture and five secondary indexes unless a bounded sweep is stated. This is rollback evidence for that fixture, not a general resource bound. |
| Design | [include/crown/storage/reference.hpp](../../../../../include/crown/storage/reference.hpp), [src/storage/reference.cpp](../../../../../src/storage/reference.cpp), [docs/storage_journal.md §Purpose and API](../../../../storage_journal.md), [docs/storage_journal.md §Undo records and identity restoration](../../../../storage_journal.md), [docs/tuple_arenas.md §Ownership and identity](../../../../tuple_arenas.md), [docs/tuple_arenas.md §Allocation failure and inspection](../../../../tuple_arenas.md) |

## B0036

[Lines 198–216](../../../../../tests/unit/storage_journal_exception_test.cpp#L198); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void apply_mixed_transaction(ReferenceTable::Journal& journal, Fixture& fixture,
                             const TransactionRows& rows)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Apply an ordered mixture of two inserts, erases, reinserts, and no-op repeats through one active journal. |
| inputs / outputs | Callable: void apply_mixed_transaction(ReferenceTable::Journal& journal, Fixture& fixture, const TransactionRows& rows). Inputs: journal, fixture, and prebuilt rows. Output: none; journal retains eight logical change entries. |
| invariants | Duplicate erases do not add entries; reinsertions of erased values receive fresh tentative IDs. |
| ownership | ReferenceTable owns its current logical rows and indexes. Fixture fields and captured images are test-owned copies except stored tuple addresses, which borrow from the live table; committed journals own affected payload pins. |
| failure | A failed check throws std::runtime_error; expect_error accepts only the requested crown::Error. The allocation sweep catches std::bad_alloc from ordinary global-new injection and keeps it armed through undo. |
| cost | Uses the six-row fixture and five secondary indexes unless a bounded sweep is stated. This is rollback evidence for that fixture, not a general resource bound. |
| Design | [include/crown/storage/reference.hpp](../../../../../include/crown/storage/reference.hpp), [src/storage/reference.cpp](../../../../../src/storage/reference.cpp), [docs/storage_journal.md §Purpose and API](../../../../storage_journal.md), [docs/storage_journal.md §Undo records and identity restoration](../../../../storage_journal.md), [docs/tuple_arenas.md §Ownership and identity](../../../../tuple_arenas.md), [docs/tuple_arenas.md §Allocation failure and inspection](../../../../tuple_arenas.md) |

## B0038

[Lines 218–275](../../../../../tests/unit/storage_journal_exception_test.cpp#L218); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::size_t allocation_failures()
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Sweep ordinary global-new failure points through journal creation and a mixed transaction, keeping failure armed through rollback. |
| inputs / outputs | Callable: std::size_t allocation_failures(). Input: none. Output: number of failed positions before first success, with at most 2048 positions. |
| invariants | Each failed attempt restores the captured table image; revision decides whether earlier live/bucket cursors remain valid, and the retry row receives logical ID 7. |
| ownership | ReferenceTable owns its current logical rows and indexes. Fixture fields and captured images are test-owned copies except stored tuple addresses, which borrow from the live table; committed journals own affected payload pins. |
| failure | Only std::bad_alloc from ordinary new/new\[\] during journal preparation/mutation/rollback is the expected injected path; other failures escape the sweep. |
| cost | At most 2048 newly built six-row/five-index fixtures; each point captures a table image, attempts one mixed journal transaction, validates rollback/cursor state, and retries the logical ID. |
| Design | [tests/unit/storage_journal_exception_test.cpp](../../../../../tests/unit/storage_journal_exception_test.cpp), [src/storage/reference.cpp](../../../../../src/storage/reference.cpp), [docs/storage_journal.md §Undo records and identity restoration](../../../../storage_journal.md) |

## B0040

[Lines 277–311](../../../../../tests/unit/storage_journal_exception_test.cpp#L277); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void active_journal_guards()
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Check writer/cursor exclusion and permitted reads while a ReferenceTable journal is active. |
| inputs / outputs | Callable: void active_journal_guards(). Input: none. Output: none after direct mutation, second journal, cursor, and foreign-handle cases match their expected errors. |
| invariants | Read lookup/snapshot/bucket access remains available; empty rollback preserves revision and preexisting cursor usability. |
| ownership | ReferenceTable owns its current logical rows and indexes. Fixture fields and captured images are test-owned copies except stored tuple addresses, which borrow from the live table; committed journals own affected payload pins. |
| failure | A failed check throws std::runtime_error; expect_error accepts only the requested crown::Error. The allocation sweep catches std::bad_alloc from ordinary global-new injection and keeps it armed through undo. |
| cost | Checks a fixed set of direct mutators/cursor methods and one small table image. |
| Design | [include/crown/storage/reference.hpp](../../../../../include/crown/storage/reference.hpp), [src/storage/reference.cpp](../../../../../src/storage/reference.cpp), [docs/storage_journal.md §Purpose and API](../../../../storage_journal.md), [docs/storage_journal.md §Undo records and identity restoration](../../../../storage_journal.md), [docs/tuple_arenas.md §Ownership and identity](../../../../tuple_arenas.md), [docs/tuple_arenas.md §Allocation failure and inspection](../../../../tuple_arenas.md) |

## B0042

[Lines 313–323](../../../../../tests/unit/storage_journal_exception_test.cpp#L313); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void exercise_mixed_operations(ReferenceTable::Journal& journal, Fixture& fixture,
                               const TransactionRows& rows)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Run the shared eight-change transaction and inspect selected ordered journal change views. |
| inputs / outputs | Callable: void exercise_mixed_operations(ReferenceTable::Journal& journal, Fixture& fixture, const TransactionRows& rows). Inputs: journal, fixture, and prepared rows. Output: none after first insertion and one erased-row view match. |
| invariants | The repeated no-op operations in apply_mixed_transaction do not contribute to journal size. |
| ownership | ReferenceTable owns its current logical rows and indexes. Fixture fields and captured images are test-owned copies except stored tuple addresses, which borrow from the live table; committed journals own affected payload pins. |
| failure | A failed check throws std::runtime_error; expect_error accepts only the requested crown::Error. The allocation sweep catches std::bad_alloc from ordinary global-new injection and keeps it armed through undo. |
| cost | Uses the six-row fixture and five secondary indexes unless a bounded sweep is stated. This is rollback evidence for that fixture, not a general resource bound. |
| Design | [include/crown/storage/reference.hpp](../../../../../include/crown/storage/reference.hpp), [src/storage/reference.cpp](../../../../../src/storage/reference.cpp), [docs/storage_journal.md §Purpose and API](../../../../storage_journal.md), [docs/storage_journal.md §Undo records and identity restoration](../../../../storage_journal.md), [docs/tuple_arenas.md §Ownership and identity](../../../../tuple_arenas.md), [docs/tuple_arenas.md §Allocation failure and inspection](../../../../tuple_arenas.md) |

## B0044

[Lines 325–349](../../../../../tests/unit/storage_journal_exception_test.cpp#L325); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void explicit_rollback_is_allocation_free()
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Run explicit rollback twice while ordinary global-new attempts are forced to fail, then compare the restored image. |
| inputs / outputs | Callable: void explicit_rollback_is_allocation_free(). Input: none. Output: none after row/index/pin restoration and stale-cursor/error checks. |
| invariants | The injected seam is ordinary global new/new\[\]; the test does not instrument direct malloc or every allocator API. |
| ownership | ReferenceTable owns its current logical rows and indexes. Fixture fields and captured images are test-owned copies except stored tuple addresses, which borrow from the live table; committed journals own affected payload pins. |
| failure | A failed check throws std::runtime_error; expect_error accepts only the requested crown::Error. The allocation sweep catches std::bad_alloc from ordinary global-new injection and keeps it armed through undo. |
| cost | Applies the fixed eight-entry mixed change list and compares one before/after table image while ordinary global-new attempts fail. |
| Design | [include/crown/storage/reference.hpp](../../../../../include/crown/storage/reference.hpp), [src/storage/reference.cpp](../../../../../src/storage/reference.cpp), [docs/storage_journal.md §Purpose and API](../../../../storage_journal.md), [docs/storage_journal.md §Undo records and identity restoration](../../../../storage_journal.md), [docs/tuple_arenas.md §Ownership and identity](../../../../tuple_arenas.md), [docs/tuple_arenas.md §Allocation failure and inspection](../../../../tuple_arenas.md) |

## B0046

[Lines 351–365](../../../../../tests/unit/storage_journal_exception_test.cpp#L351); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void destructor_rollback_is_allocation_free()
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Let active journal destruction roll back while ordinary global-new attempts are forced to fail. |
| inputs / outputs | Callable: void destructor_rollback_is_allocation_free(). Input: none. Output: none after the exact table image is restored and the revision remains advanced. |
| invariants | The failure countdown is disabled only after the journal destructor returns. |
| ownership | ReferenceTable owns its current logical rows and indexes. Fixture fields and captured images are test-owned copies except stored tuple addresses, which borrow from the live table; committed journals own affected payload pins. |
| failure | A failed check throws std::runtime_error; expect_error accepts only the requested crown::Error. The allocation sweep catches std::bad_alloc from ordinary global-new injection and keeps it armed through undo. |
| cost | Applies the same fixed eight-entry change list and compares one table image after scope exit. |
| Design | [include/crown/storage/reference.hpp](../../../../../include/crown/storage/reference.hpp), [src/storage/reference.cpp](../../../../../src/storage/reference.cpp), [docs/storage_journal.md §Purpose and API](../../../../storage_journal.md), [docs/storage_journal.md §Undo records and identity restoration](../../../../storage_journal.md), [docs/tuple_arenas.md §Ownership and identity](../../../../tuple_arenas.md), [docs/tuple_arenas.md §Allocation failure and inspection](../../../../tuple_arenas.md) |

## B0048

[Lines 367–398](../../../../../tests/unit/storage_journal_exception_test.cpp#L367); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
ReferenceTable::Journal committed_journal_after_owner_destruction()
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Return a committed journal whose insert/erase change tuples remain readable after clear and table destruction. |
| inputs / outputs | Callable: ReferenceTable::Journal committed_journal_after_owner_destruction(). Input: none. Output: moved ReferenceTable::Journal with two committed change views. |
| invariants | The journal retains affected payload pins, not the whole table; dropping a separate fixture pin does not invalidate its change values. |
| ownership | The returned inactive Journal owns the committed change pins after the local Fixture and table are destroyed. |
| failure | The commit operation runs under the injected ordinary global-new failure state; a matching journal Error or missing retained payload fails the test. |
| cost | Creates two journal entries, clears six table rows, then checks two retained values after the fixture/table lifetime. |
| Design | [tests/unit/storage_journal_exception_test.cpp](../../../../../tests/unit/storage_journal_exception_test.cpp), [docs/storage_journal.md §Purpose and API](../../../../storage_journal.md), [docs/storage_journal.md §Undo records and identity restoration](../../../../storage_journal.md) |

## B0049

[Lines 399–401](../../../../../tests/unit/storage_journal_exception_test.cpp#L399); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L399-L401:sha256:9e375a3cb3a2cbe2f9ded9c8296a6ab66848cc826fd71f919246acb17e0bd455
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Close the recorded declaration scopes in storage_journal_exception_test.cpp: namespace (anonymous). |
| inputs / outputs | Preceding namespace, type or initializer declarations in; completed lexical boundary out. |
| invariants | Brace-opening context is recorded in root-scope-context-v1.json. These are declaration/initializer boundaries, not an independent update, validation or recovery operation. |
| ownership | Enclosing objects and borrowed fields keep their declared ownership. This punctuation creates no new owner. |
| failure | Malformed scope syntax is a compile error. Any initializer/constructor failure belongs to the enclosing object declaration. |
| cost | No separate loop, guard or engine call is introduced by the delimiter; enclosing initialization and object lifetime still have their actual costs. |
| Design | [tests/unit/storage_journal_exception_test.cpp](../../../../../tests/unit/storage_journal_exception_test.cpp), [docs/session-journal.md](../../../../session-journal.md), [docs/code_review.md](../../../../code_review.md) |

## B0050

[Lines 402–425](../../../../../tests/unit/storage_journal_exception_test.cpp#L402); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
int main()
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Run exception-injected rollback, active guards, explicit/destructor rollback, and committed payload lifetime checks. |
| inputs / outputs | Callable: int main(). Input: none. Output: zero on success after printing the ordinary-new failure count, or one with the first exception. |
| invariants | The injected failure sweep is capped at 2048 positions and all data/index counts come from the fixed Fixture. |
| ownership | ReferenceTable owns its current logical rows and indexes. Fixture fields and captured images are test-owned copies except stored tuple addresses, which borrow from the live table; committed journals own affected payload pins. |
| failure | A failed check throws std::runtime_error; expect_error accepts only the requested crown::Error. The allocation sweep catches std::bad_alloc from ordinary global-new injection and keeps it armed through undo. |
| cost | Runs one at-most-2048 fault sweep plus four finite lifecycle/rollback scenarios over the fixed six-row/five-index fixture. |
| Design | [tests/unit/storage_journal_exception_test.cpp](../../../../../tests/unit/storage_journal_exception_test.cpp), [docs/storage_journal.md §Undo records and identity restoration](../../../../storage_journal.md), [docs/tuple_arenas.md §Allocation failure and inspection](../../../../tuple_arenas.md) |
