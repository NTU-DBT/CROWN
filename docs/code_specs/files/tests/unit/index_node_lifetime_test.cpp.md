# `tests/unit/index_node_lifetime_test.cpp` — block usage map

[Source](../../../../../tests/unit/index_node_lifetime_test.cpp) · [Source index](../../../README.md) · [Subsystem contracts](../../../subsystem_contracts.md) · [Reviewed primitives](../../../primitives.md)

Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection.

Snapshot SHA-256: `761167241e1d0bb3ebaeef58c84465e220d4df96a318336b6e741ae5e19860d4`. 127 lines partitioned into 16 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [tests](../../../subsystem_contracts.md#tests). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/code_review.md](../../../../code_review.md), [docs/reference_fuzz.md](../../../../reference_fuzz.md), [docs/task_ledger.md](../../../../task_ledger.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–17](../../../../../tests/unit/index_node_lifetime_test.cpp#L1) | Imports dependencies; declares namespace scope; declares aliases; declares values/defaults or compile-time conditions. |  · [reviewed contract](#b0001) |
| [B0002 · 18–20](../../../../../tests/unit/index_node_lifetime_test.cpp#L18) | Callable definition: void verify(bool value, std::string_view message) | calls std::runtime_error, std::string · [reviewed contract](#b0002) |
| [B0003 · 21–23](../../../../../tests/unit/index_node_lifetime_test.cpp#L21) | Callable definition: IndexWorkAllowance ample() | calls IndexWorkAllowance; returns IndexWorkAllowance(IndexWork{1'000'000, 1'000'000, 1'000'000, 1'000'000, 1'000'000}) · [reviewed contract](#b0003) |
| [B0004 · 24–39](../../../../../tests/unit/index_node_lifetime_test.cpp#L24) | declares types or opens a type body; declares callable signatures; declares values/defaults or compile-time conditions. | guard static_assert(!std::is_copy_constructible_v&lt;detail::IndexedRow&gt; && !std::is_move_constructible_v&lt;de… · [reviewed contract](#b0004) |
| [B0005 · 40–45](../../../../../tests/unit/index_node_lifetime_test.cpp#L40) | Callable definition: std::unique_ptr&lt;detail::IndexedIndex&gt; make_index() | calls prepare_growth, publish_growth, std::move, admit; returns index; growth make_unique · [reviewed contract](#b0005) |
| [B0006 · 46–53](../../../../../tests/unit/index_node_lifetime_test.cpp#L46) | Callable definition: std::unique_ptr&lt;detail::IndexedRow&gt; make_row(std::uint64_t id) | calls prepare_growth, size, admit, publish_growth; returns row; growth make_unique · [reviewed contract](#b0006) |
| [B0007 · 54–61](../../../../../tests/unit/index_node_lifetime_test.cpp#L54) | Callable definition: detail::IndexedKey* add_key(detail::IndexedIndex& index, std::int64_t value) | calls tuple, prepare_growth, size, prepare_insert; returns key.release(); growth make_unique · [reviewed contract](#b0007) |
| [B0008 · 62–67](../../../../../tests/unit/index_node_lifetime_test.cpp#L62) | Callable definition: void add_member(detail::IndexedRow& row, detail::IndexedIndex& index, detail::IndexedKey& key) | calls prepare_insert, append_prepaid, release; growth make_unique; source comment (unverified): // One actual owning row, one borrowed bucket. · [reviewed contract](#b0008) |
| [B0009 · 68–69](../../../../../tests/unit/index_node_lifetime_test.cpp#L68) | Closes surrounding scope/type. |  · [reviewed contract](#b0009) |
| [B0010 · 70–87](../../../../../tests/unit/index_node_lifetime_test.cpp#L70) | Callable definition: void row_and_index_destruction() | calls make_index, make_row, add_key, add_member; source comment (unverified): // Automatic detachment must use current directory links after a rehash. · [reviewed contract](#b0010) |
| [B0011 · 88–88](../../../../../tests/unit/index_node_lifetime_test.cpp#L88) | Explanatory comments or spacing. |  |
| [B0012 · 89–107](../../../../../tests/unit/index_node_lifetime_test.cpp#L89) | Callable definition: void prepared_member_ownership() | calls make_index, make_row, add_key, prepare_insert; growth make_unique; source comment (unverified): // Its key/index pointers are expired; detached hooks avoid dereferencing them. · [reviewed contract](#b0012) |
| [B0013 · 108–108](../../../../../tests/unit/index_node_lifetime_test.cpp#L108) | Explanatory comments or spacing. |  |
| [B0014 · 109–121](../../../../../tests/unit/index_node_lifetime_test.cpp#L109) | Callable definition: void iterative_large_bucket() | calls make_index, add_key, reserve, make_row; growth push_back, reserve; 2 loop sites · [reviewed contract](#b0014) |
| [B0015 · 122–123](../../../../../tests/unit/index_node_lifetime_test.cpp#L122) | Closes surrounding scope/type. | source comment (unverified): // namespace · [reviewed contract](#b0015) |
| [B0016 · 124–127](../../../../../tests/unit/index_node_lifetime_test.cpp#L124) | Callable definition: int main() | calls row_and_index_destruction, prepared_member_ownership, iterative_large_bucket · [reviewed contract](#b0016) |

## B0001

[Lines 1–17](../../../../../tests/unit/index_node_lifetime_test.cpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L1-L17:sha256:b78bad74e76b5a6cdac61b0edc718982d71f86164b8da803219e9b8f36194bf9
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Prepare index_node_lifetime_test.cpp: include "indexed_nodes.hpp", &lt;cstddef&gt;, &lt;cstdint&gt;, &lt;iostream&gt;, &lt;memory&gt;, &lt;stdexcept&gt;, &lt;string&gt;, &lt;string_view&gt;, &lt;type_traits&gt;, &lt;vector&gt;; bind local aliases/name imports. |
| inputs / outputs | Compiler-visible dependencies, names and the recorded declarations in; declarations available to the following fixture/CLI/example definitions out. |
| invariants | Declarations are scoped to this source/header and its selected ABI. Included code has its own effects; names and editable fixture values do not confer proof, admission or publication authority. |
| ownership | Aliases/includes do not create a query owner. Pointers/references/views are non-owning. Containers own their elements, which can themselves be borrowed pointers or numeric IDs. Only documented owning shared-control handles retain controls; IDs/slot-handle values do not independently keep an arena/runtime alive. |
| failure | Missing headers, ill-formed names/types, failed static assertions or active #error directives stop compilation. No runtime rejection/rollback mechanism is implemented by aliases or function prototypes. |
| cost | Preprocessing and type/constraint instantiation cost compilation. Alias/prototype syntax does not invoke the declared operation; any included definitions keep their own initialization effects. |
| Design | [tests/unit/index_node_lifetime_test.cpp](../../../../../tests/unit/index_node_lifetime_test.cpp), [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/code_review.md](../../../../code_review.md) |

## B0002

[Lines 18–20](../../../../../tests/unit/index_node_lifetime_test.cpp#L18); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void verify(bool value, std::string_view message) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Fail an indexed-node lifetime assertion. |
| inputs / outputs | Bool/message in; runtime_error when false. |
| invariants | Bad ownership/link state fails. |
| ownership | Message borrowed except diagnostic. |
| failure | runtime_error carrier. |
| cost | One branch. |
| Design | tests/unit/index_node_lifetime_test.cpp:18-20, docs/indexed_storage.md:35-89, docs/storage_journal.md:133-163, [Refactor.md §6.2](../../../../../Refactor.md), [Refactor.md §11.4 S03](../../../../../Refactor.md), [Refactor.md §11.4 S04](../../../../../Refactor.md) |

## B0003

[Lines 21–23](../../../../../tests/unit/index_node_lifetime_test.cpp#L21); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
IndexWorkAllowance ample() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Return node-test work for structural/link operations. |
| inputs / outputs | No input; fixed IndexWork with structural and link domains. |
| invariants | No scalar/byte charge is supplied. |
| ownership | Caller owns allowance. |
| failure | No custom catch. |
| cost | Fixed value. |
| Design | tests/unit/index_node_lifetime_test.cpp:21-23, docs/indexed_storage.md:35-89, docs/storage_journal.md:133-163, [Refactor.md §6.2](../../../../../Refactor.md), [Refactor.md §11.4 S03](../../../../../Refactor.md), [Refactor.md §11.4 S04](../../../../../Refactor.md) |

## B0004

[Lines 24–39](../../../../../tests/unit/index_node_lifetime_test.cpp#L24); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
IndexWorkAllowance work = ample();
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Define the node-lifetime test Fixture’s empty directories, layouts, projection, capacities and pre-funded work allowance. |
| inputs / outputs | Compile-time assertions require four indexed node types to be noncopyable, nonmovable and nothrow-destructible. Fixture construction creates layouts/projection, three initially empty directories with maximum slot limits 4096/4096/64 and work=ample(); later helpers add nodes. |
| invariants | These are test-only type traits and fixture values; the empty initial directories and structural/link-only allowance do not set CROWN runtime defaults or assert scalar/byte work. |
| ownership | Fixture owns directory containers/projection/work value; test helpers’ unique_ptrs own nodes until the reviewed link/adoption steps transfer ownership. |
| failure | Layout/directory construction failures propagate to the test; this block has no catch or rollback. |
| cost | Layout/projection metadata plus empty directories carrying fixed slot ceilings; actual directory arrays grow later. No exact allocator-byte amount is claimed. |
| Design | [tests/unit/index_node_lifetime_test.cpp](../../../../../tests/unit/index_node_lifetime_test.cpp), tests/unit/index_node_lifetime_test.cpp:40-68, tests/unit/index_node_lifetime_test.cpp:70-121, CMakeLists.txt:1324-1326, tests/unit/index_node_lifetime_test.cpp:24-39 |

## B0005

[Lines 40–45](../../../../../tests/unit/index_node_lifetime_test.cpp#L40); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::unique_ptr<detail::IndexedIndex> make_index() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Build an empty private IndexedIndex with a projection and limits. |
| inputs / outputs | Fixture in; owning unique_ptr to index out. |
| invariants | Index identity/hook registration uses fixture's real ID directory. |
| ownership | Unique_ptr owns index; directory borrows link. |
| failure | Work/capacity failures propagate. |
| cost | Constructs index and possibly directory capacity. |
| Design | tests/unit/index_node_lifetime_test.cpp:40-45, docs/indexed_storage.md:35-89, docs/storage_journal.md:133-163, [Refactor.md §6.2](../../../../../Refactor.md), [Refactor.md §11.4 S03](../../../../../Refactor.md), [Refactor.md §11.4 S04](../../../../../Refactor.md) |

## B0006

[Lines 46–53](../../../../../tests/unit/index_node_lifetime_test.cpp#L46); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::unique_ptr<detail::IndexedRow> make_row(std::uint64_t id) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Allocate a private IndexedRow with ID and member-list capacity. |
| inputs / outputs | ID in; unique_ptr row out. |
| invariants | Primary and ID directories both link the same stable node. |
| ownership | Unique_ptr owns row; directories borrow hooks. |
| failure | Capacity/work failures propagate before links. |
| cost | One row and two directory growth/link steps. |
| Design | tests/unit/index_node_lifetime_test.cpp:46-53, docs/indexed_storage.md:35-89, docs/storage_journal.md:133-163, [Refactor.md §6.2](../../../../../Refactor.md), [Refactor.md §11.4 S03](../../../../../Refactor.md), [Refactor.md §11.4 S04](../../../../../Refactor.md) |

## B0007

[Lines 54–61](../../../../../tests/unit/index_node_lifetime_test.cpp#L54); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
detail::IndexedKey* add_key(detail::IndexedIndex& index, std::int64_t value) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Allocate a key object and link it in index hash directory/live-key list. |
| inputs / outputs | Index/key value in; raw pointer to the key out. |
| invariants | One stable key has both directory and live-list membership. |
| ownership | The index adopts the key only after both links publish; the returned raw pointer borrows that index-owned node. |
| failure | Admission/capacity errors propagate before publication. |
| cost | Key tuple/hash construction and two intrusive-structure updates; exact allocator requests are not measured. |
| Design | tests/unit/index_node_lifetime_test.cpp:54-61, docs/indexed_storage.md:35-89, docs/storage_journal.md:133-163, [Refactor.md §6.2](../../../../../Refactor.md), [Refactor.md §11.4 S03](../../../../../Refactor.md), [Refactor.md §11.4 S04](../../../../../Refactor.md) |

## B0008

[Lines 62–67](../../../../../tests/unit/index_node_lifetime_test.cpp#L62); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void add_member(detail::IndexedRow& row, detail::IndexedIndex& index, detail::IndexedKey& key) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Attach one IndexedMember to row and key hook lists. |
| inputs / outputs | Row/index/key in; creates and links one shared member. |
| invariants | Member has independent row/bucket links; row owns the member. |
| ownership | Releases unique_ptr only after both links are installed. |
| failure | Preparation errors leave no linked member. |
| cost | Two list preparations and two links. |
| Design | tests/unit/index_node_lifetime_test.cpp:62-67, docs/indexed_storage.md:35-89, docs/storage_journal.md:133-163, [Refactor.md §6.2](../../../../../Refactor.md), [Refactor.md §11.4 S03](../../../../../Refactor.md), [Refactor.md §11.4 S04](../../../../../Refactor.md) |

## B0009

[Lines 68–69](../../../../../tests/unit/index_node_lifetime_test.cpp#L68); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L68-L69:sha256:cdbb10f75f6890449819c9d57e5ae7b786fb73c5111c5d829c37bc18f3e053e8
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Close the recorded declaration scopes in index_node_lifetime_test.cpp: struct Fixture. |
| inputs / outputs | Preceding namespace, type or initializer declarations in; completed lexical boundary out. |
| invariants | Brace-opening context is recorded in root-scope-context-v1.json. These are declaration/initializer boundaries, not an independent update, validation or recovery operation. |
| ownership | Enclosing objects and borrowed fields keep their declared ownership. This punctuation creates no new owner. |
| failure | Malformed scope syntax is a compile error. Any initializer/constructor failure belongs to the enclosing object declaration. |
| cost | No separate loop, guard or engine call is introduced by the delimiter; enclosing initialization and object lifetime still have their actual costs. |
| Design | [tests/unit/index_node_lifetime_test.cpp](../../../../../tests/unit/index_node_lifetime_test.cpp), [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/code_review.md](../../../../code_review.md) |

## B0010

[Lines 70–87](../../../../../tests/unit/index_node_lifetime_test.cpp#L70); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void row_and_index_destruction() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Check row/index destruction detaches current links after rehash. |
| inputs / outputs | No input; builds two rows/two members, grows primary/ID directories, destroys owners. |
| invariants | Current arrays are used for unlink; row/index teardown removes all borrowed links. |
| ownership | Rows own members; key/index own keys; directories borrow. |
| failure | Assertions fail on dangling resident nodes. |
| cost | Two rows, one key and explicit rehash before teardown. |
| Design | tests/unit/index_node_lifetime_test.cpp:70-87, docs/indexed_storage.md:35-89, docs/storage_journal.md:133-163, [Refactor.md §6.2](../../../../../Refactor.md), [Refactor.md §11.4 S03](../../../../../Refactor.md), [Refactor.md §11.4 S04](../../../../../Refactor.md) |

## B0012

[Lines 89–107](../../../../../tests/unit/index_node_lifetime_test.cpp#L89); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void prepared_member_ownership() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Check private prepared-member ownership when index tears down. |
| inputs / outputs | No input; links only bucket hook, destroys index, then destroys private member. |
| invariants | Index teardown detaches both hooks and does not adopt/delete privately owned member. |
| ownership | unique_ptr remains member owner; member destructor tolerates detached hooks. |
| failure | Assertions catch dangling hook dereference/leak. |
| cost | One prepared member then second cleanup scenario. |
| Design | tests/unit/index_node_lifetime_test.cpp:89-107, docs/indexed_storage.md:35-89, docs/storage_journal.md:133-163, [Refactor.md §6.2](../../../../../Refactor.md), [Refactor.md §11.4 S03](../../../../../Refactor.md), [Refactor.md §11.4 S04](../../../../../Refactor.md) |

## B0014

[Lines 109–121](../../../../../tests/unit/index_node_lifetime_test.cpp#L109); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void iterative_large_bucket() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Destroy an index with 1024 live bucket members. |
| inputs / outputs | No input; allocates 1024 rows/members, destroys index and row vector. |
| invariants | Index teardown removes each row-owned member before rows disappear. |
| ownership | Rows own members; key/index own bucket structures. |
| failure | Assertions require empty primary/ID/index structures. |
| cost | Linear cleanup across 1024 linked members. |
| Design | tests/unit/index_node_lifetime_test.cpp:109-121, docs/indexed_storage.md:35-89, docs/storage_journal.md:133-163, [Refactor.md §6.2](../../../../../Refactor.md), [Refactor.md §11.4 S03](../../../../../Refactor.md), [Refactor.md §11.4 S04](../../../../../Refactor.md) |

## B0015

[Lines 122–123](../../../../../tests/unit/index_node_lifetime_test.cpp#L122); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L122-L123:sha256:c2bd7638f09d52cb034ed574f539304035fc6fab162bf8d5fa20a35d8c7288a1
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Close the recorded declaration scopes in index_node_lifetime_test.cpp: namespace (anonymous). |
| inputs / outputs | Preceding namespace, type or initializer declarations in; completed lexical boundary out. |
| invariants | Brace-opening context is recorded in root-scope-context-v1.json. These are declaration/initializer boundaries, not an independent update, validation or recovery operation. |
| ownership | Enclosing objects and borrowed fields keep their declared ownership. This punctuation creates no new owner. |
| failure | Malformed scope syntax is a compile error. Any initializer/constructor failure belongs to the enclosing object declaration. |
| cost | No separate loop, guard or engine call is introduced by the delimiter; enclosing initialization and object lifetime still have their actual costs. |
| Design | [tests/unit/index_node_lifetime_test.cpp](../../../../../tests/unit/index_node_lifetime_test.cpp), [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/code_review.md](../../../../code_review.md) |

## B0016

[Lines 124–127](../../../../../tests/unit/index_node_lifetime_test.cpp#L124); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
int main() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Run indexed row/index teardown lifetime cases. |
| inputs / outputs | No input; invokes three cases and prints summary. |
| invariants | No node/hook survives its owner incorrectly. |
| ownership | main owns sequencing. |
| failure | Unexpected exception fails process. |
| cost | Finite fixtures including 1024-member bucket; no execution claim. |
| Design | tests/unit/index_node_lifetime_test.cpp:124-127, docs/indexed_storage.md:35-89, docs/storage_journal.md:133-163, [Refactor.md §6.2](../../../../../Refactor.md), [Refactor.md §11.4 S03](../../../../../Refactor.md), [Refactor.md §11.4 S04](../../../../../Refactor.md) |
