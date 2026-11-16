# `tests/unit/index_directory_test.cpp` — block usage map

[Source](../../../../../tests/unit/index_directory_test.cpp) · [Source index](../../../README.md) · [Subsystem contracts](../../../subsystem_contracts.md) · [Reviewed primitives](../../../primitives.md)

Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection.

Snapshot SHA-256: `7bda8c3f83dd1b3b8c3fdaa448f436942a9282e6d188acd2fc21bf7e6e7678bf`. 238 lines partitioned into 23 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [tests](../../../subsystem_contracts.md#tests). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/code_review.md](../../../../code_review.md), [docs/reference_fuzz.md](../../../../reference_fuzz.md), [docs/task_ledger.md](../../../../task_ledger.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–22](../../../../../tests/unit/index_directory_test.cpp#L1) | Imports dependencies; declares namespace scope; declares aliases. |  · [reviewed contract](#b0001) |
| [B0002 · 23–25](../../../../../tests/unit/index_directory_test.cpp#L23) | Callable definition: void verify(bool value, std::string_view message) | calls std::runtime_error, std::string · [reviewed contract](#b0002) |
| [B0003 · 26–32](../../../../../tests/unit/index_directory_test.cpp#L26) | Callable definition: template &lt;class Function&gt; void rejects(std::string_view code, Function&& function) | calls function, verify, code · [reviewed contract](#b0003) |
| [B0004 · 33–35](../../../../../tests/unit/index_directory_test.cpp#L33) | Callable definition: IndexWorkAllowance ample() | calls IndexWorkAllowance; returns IndexWorkAllowance(IndexWork{1'000'000, 1'000'000, 1'000'000, 1'000'000, 1'000'000}) · [reviewed contract](#b0004) |
| [B0005 · 36–41](../../../../../tests/unit/index_directory_test.cpp#L36) | Type/record definition: struct Node |  · [reviewed contract](#b0005) |
| [B0006 · 42–46](../../../../../tests/unit/index_directory_test.cpp#L42) | declares aliases; declares callable signatures; declares values/defaults or compile-time conditions. | guard static_assert(!std::is_copy_constructible_v&lt;Node&gt; && !std::is_move_constructible_v&lt;Node&gt;); · [reviewed contract](#b0006) |
| [B0007 · 47–54](../../../../../tests/unit/index_directory_test.cpp#L47) | Callable definition: Node* find(Directory& directory, std::uint64_t hash, std::uint64_t key, IndexWorkAllowance& allowance, std::size_t* comparisons =… | calls admit; returns directory.find(hash, \[&\](const Node& node, IndexWorkAllowance& grant) {; node.key == key · [reviewed contract](#b0007) |
| [B0008 · 55–61](../../../../../tests/unit/index_directory_test.cpp#L55) | Callable definition: void insert(Directory& directory, Node& node, std::uint64_t hash, IndexWorkAllowance& allowance) | calls prepare_growth, size, admit, publish_growth; growth insert · [reviewed contract](#b0008) |
| [B0009 · 62–72](../../../../../tests/unit/index_directory_test.cpp#L62) | Callable definition: std::vector&lt;std::uint64_t&gt; live_order(const Directory& directory) | calls first_resident, Directory::next_resident, verify, size; returns result; growth push_back; 1 loop sites · [reviewed contract](#b0009) |
| [B0010 · 73–73](../../../../../tests/unit/index_directory_test.cpp#L73) | Explanatory comments or spacing. |  |
| [B0011 · 74–82](../../../../../tests/unit/index_directory_test.cpp#L74) | Callable definition: void allowances() | calls grant, remaining, rejects, admit · [reviewed contract](#b0011) |
| [B0012 · 83–83](../../../../../tests/unit/index_directory_test.cpp#L83) | Explanatory comments or spacing. |  |
| [B0013 · 84–115](../../../../../tests/unit/index_directory_test.cpp#L84) | Callable definition: void empty_and_capacity() | calls empty, zero, rejects, find; returns true; true; growth insert, make_unique; 2 loop sites; source comment (unverified): // Eight is allowed; the required sixteen is not. · [reviewed contract](#b0013) |
| [B0014 · 116–116](../../../../../tests/unit/index_directory_test.cpp#L116) | Explanatory comments or spacing. |  |
| [B0015 · 117–168](../../../../../tests/unit/index_directory_test.cpp#L117) | Callable definition: void collisions_and_growth() | calls directory, ample, insert, verify; growth insert, make_unique; 2 loop sites; source comment (unverified): // Distinct keys, identical full hashes. · [reviewed contract](#b0015) |
| [B0016 · 169–169](../../../../../tests/unit/index_directory_test.cpp#L169) | Explanatory comments or spacing. |  |
| [B0017 · 170–180](../../../../../tests/unit/index_directory_test.cpp#L170) | Callable definition: void independent_hooks() | calls primary, identity, node, ample; returns row.key == 23; growth insert · [reviewed contract](#b0017) |
| [B0018 · 181–181](../../../../../tests/unit/index_directory_test.cpp#L181) | Explanatory comments or spacing. |  |
| [B0019 · 182–199](../../../../../tests/unit/index_directory_test.cpp#L182) | Callable definition: void restored_neighbors() | calls directory, ample, first, middle; growth insert; source comment (unverified): // One aggregate allowance reserves both forward removals and their inverse · [reviewed contract](#b0019) |
| [B0020 · 200–200](../../../../../tests/unit/index_directory_test.cpp#L200) | Explanatory comments or spacing. |  |
| [B0021 · 201–232](../../../../../tests/unit/index_directory_test.cpp#L201) | Callable definition: void generated_tape() | calls directory, ample, contains, insert; growth emplace, insert, make_unique, push_back; 3 loop sites · [reviewed contract](#b0021) |
| [B0022 · 233–234](../../../../../tests/unit/index_directory_test.cpp#L233) | Closes surrounding scope/type. | source comment (unverified): // namespace · [reviewed contract](#b0022) |
| [B0023 · 235–238](../../../../../tests/unit/index_directory_test.cpp#L235) | Callable definition: int main() | calls allowances, empty_and_capacity, collisions_and_growth, independent_hooks · [reviewed contract](#b0023) |

## B0001

[Lines 1–22](../../../../../tests/unit/index_directory_test.cpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L1-L22:sha256:be0ebc9d28b69fbd9abb5160e61571cef0a3752d96d6bfd3d5d727462f65479d
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Prepare index_directory_test.cpp: include "hash_directory.hpp", &lt;algorithm&gt;, &lt;array&gt;, &lt;cstdint&gt;, &lt;iostream&gt;, &lt;limits&gt;, &lt;map&gt;, &lt;memory&gt;, &lt;stdexcept&gt;, &lt;string&gt;, &lt;string_view&gt;, &lt;type_traits&gt;, &lt;vector&gt;; bind local aliases/name imports. |
| inputs / outputs | Compiler-visible dependencies, names and the recorded declarations in; declarations available to the following fixture/CLI/example definitions out. |
| invariants | Declarations are scoped to this source/header and its selected ABI. Included code has its own effects; names and editable fixture values do not confer proof, admission or publication authority. |
| ownership | Aliases/includes do not create a query owner. Pointers/references/views are non-owning. Containers own their elements, which can themselves be borrowed pointers or numeric IDs. Only documented owning shared-control handles retain controls; IDs/slot-handle values do not independently keep an arena/runtime alive. Directory here aliases an in-memory HashDirectory; it does not name or own a filesystem directory. |
| failure | Missing headers, ill-formed names/types, failed static assertions or active #error directives stop compilation. No runtime rejection/rollback mechanism is implemented by aliases or function prototypes. |
| cost | Preprocessing and type/constraint instantiation cost compilation. Alias/prototype syntax does not invoke the declared operation; any included definitions keep their own initialization effects. |
| Design | [tests/unit/index_directory_test.cpp](../../../../../tests/unit/index_directory_test.cpp), [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/code_review.md](../../../../code_review.md), [src/storage/hash_directory.hpp](../../../../../src/storage/hash_directory.hpp) |

## B0002

[Lines 23–25](../../../../../tests/unit/index_directory_test.cpp#L23); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void verify(bool value, std::string_view message) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Fail one indexed-directory test assertion. |
| inputs / outputs | Bool/message in; runtime_error when false. |
| invariants | False directory behavior cannot pass. |
| ownership | Message borrowed except failure formatting. |
| failure | runtime_error is harness carrier. |
| cost | One branch. |
| Design | tests/unit/index_directory_test.cpp:23-25, docs/indexed_storage.md:35-89, docs/memory_accounts.md:378-409, [Refactor.md §6.2](../../../../../Refactor.md), [Refactor.md §11.4 S04](../../../../../Refactor.md) |

## B0003

[Lines 26–32](../../../../../tests/unit/index_directory_test.cpp#L26); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
template <class Function>
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Require one storage Error code. |
| inputs / outputs | Code/action in; returns after crown::Error matches. |
| invariants | Wrong or missing Error fails. |
| ownership | Action forwarded; caught Error borrowed. |
| failure | Mismatch becomes runtime_error. |
| cost | One action/check. |
| Design | tests/unit/index_directory_test.cpp:26-32, docs/indexed_storage.md:35-89, docs/memory_accounts.md:378-409, [Refactor.md §6.2](../../../../../Refactor.md), [Refactor.md §11.4 S04](../../../../../Refactor.md) |

## B0004

[Lines 33–35](../../../../../tests/unit/index_directory_test.cpp#L33); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
IndexWorkAllowance ample() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Return a large standalone IndexWork allowance. |
| inputs / outputs | No input; all five domains receive fixed large values. |
| invariants | This is native work accounting, not allocator bytes. |
| ownership | Returned grant owned by caller. |
| failure | No custom catch. |
| cost | Fixed struct construction. |
| Design | tests/unit/index_directory_test.cpp:33-35, docs/indexed_storage.md:35-89, docs/memory_accounts.md:378-409, [Refactor.md §6.2](../../../../../Refactor.md), [Refactor.md §11.4 S04](../../../../../Refactor.md) |

## B0005

[Lines 36–41](../../../../../tests/unit/index_directory_test.cpp#L36); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct Node {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Define a nonmovable directory node with independent primary/ID hooks. |
| inputs / outputs | Key in; stores exact key and two intrusive hooks. |
| invariants | Node cannot copy/move while linked. |
| ownership | Fixture unique_ptr owns node. |
| failure | No custom failure path. |
| cost | Fixed node record. |
| Design | tests/unit/index_directory_test.cpp:36-41, docs/indexed_storage.md:35-89, docs/memory_accounts.md:378-409, [Refactor.md §6.2](../../../../../Refactor.md), [Refactor.md §11.4 S04](../../../../../Refactor.md) |

## B0006

[Lines 42–46](../../../../../tests/unit/index_directory_test.cpp#L42); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L42-L46:sha256:b6f8a7dada3e7f5501cdc2d3121d03e83dd7d0098e6b3b4364ee056813bd3415
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Prepare index_directory_test.cpp: bind local aliases/name imports; require 2 compile-time type/ABI conditions. |
| inputs / outputs | Compiler-visible dependencies, names and the recorded declarations in; declarations available to the following fixture/CLI/example definitions out. |
| invariants | Declarations are scoped to this source/header and its selected ABI. Included code has its own effects; names and editable fixture values do not confer proof, admission or publication authority. Static assertions establish only their listed C++ type properties, not query/result/recovery correctness or test execution. |
| ownership | Aliases/includes do not create a query owner. Pointers/references/views are non-owning. Containers own their elements, which can themselves be borrowed pointers or numeric IDs. Only documented owning shared-control handles retain controls; IDs/slot-handle values do not independently keep an arena/runtime alive. Directory here aliases an in-memory HashDirectory; it does not name or own a filesystem directory. |
| failure | Missing headers, ill-formed names/types, failed static assertions or active #error directives stop compilation. No runtime rejection/rollback mechanism is implemented by aliases or function prototypes. |
| cost | Preprocessing and type/constraint instantiation cost compilation. Alias/prototype syntax does not invoke the declared operation; any included definitions keep their own initialization effects. |
| Design | [tests/unit/index_directory_test.cpp](../../../../../tests/unit/index_directory_test.cpp), [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/code_review.md](../../../../code_review.md), [src/storage/hash_directory.hpp](../../../../../src/storage/hash_directory.hpp) |

## B0007

[Lines 47–54](../../../../../tests/unit/index_directory_test.cpp#L47); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Node* find(Directory& directory, std::uint64_t hash, std::uint64_t key,
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Adapt exact key equality to HashDirectory::find and count comparisons. |
| inputs / outputs | Directory/hash/key/grant/optional counter in; Node pointer or null out. |
| invariants | Debits one scalar field per equality body; full-hash filter is directory-owned. |
| ownership | Borrows node directory and grant. |
| failure | Work denial propagates storage_work_limit. |
| cost | Visits real collision chain and optional comparison counter. |
| Design | tests/unit/index_directory_test.cpp:47-54, docs/indexed_storage.md:35-89, docs/memory_accounts.md:378-409, [Refactor.md §6.2](../../../../../Refactor.md), [Refactor.md §11.4 S04](../../../../../Refactor.md) |

## B0008

[Lines 55–61](../../../../../tests/unit/index_directory_test.cpp#L55); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void insert(Directory& directory, Node& node, std::uint64_t hash,
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Prepare growth, admit link work and publish a directory node. |
| inputs / outputs | Directory/Node/hash/grant in; links node after growth publication. |
| invariants | No link occurs before both growth and link-work admission. |
| ownership | Node storage remains caller-owned; directory stores intrusive link. |
| failure | Capacity/work errors happen before link. |
| cost | Growth preparation plus fixed link actions. |
| Design | tests/unit/index_directory_test.cpp:55-61, docs/indexed_storage.md:35-89, docs/memory_accounts.md:378-409, [Refactor.md §6.2](../../../../../Refactor.md), [Refactor.md §11.4 S04](../../../../../Refactor.md) |

## B0009

[Lines 62–72](../../../../../tests/unit/index_directory_test.cpp#L62); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::vector<std::uint64_t> live_order(const Directory& directory) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Materialize insertion-order resident list for assertions. |
| inputs / outputs | Directory in; ordered vector of keys out. |
| invariants | Detects cycle/cardinality and verifies tail. |
| ownership | Returned vector is test-owned; Nodes remain caller-owned. |
| failure | Invariant mismatch throws runtime_error. |
| cost | Traverses all resident nodes. |
| Design | tests/unit/index_directory_test.cpp:62-72, docs/indexed_storage.md:35-89, docs/memory_accounts.md:378-409, [Refactor.md §6.2](../../../../../Refactor.md), [Refactor.md §11.4 S04](../../../../../Refactor.md) |

## B0011

[Lines 74–82](../../../../../tests/unit/index_directory_test.cpp#L74); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void allowances() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Check five-domain allowance is atomic on failed admission. |
| inputs / outputs | No input; tests one short dimension, exact exhaustion and subsequent denial. |
| invariants | Failed aggregate check consumes none of earlier domains. |
| ownership | Allowance owned by test. |
| failure | Expected storage_work_limit required. |
| cost | Three literal grant checks. |
| Design | tests/unit/index_directory_test.cpp:74-82, docs/indexed_storage.md:35-89, docs/memory_accounts.md:378-409, [Refactor.md §6.2](../../../../../Refactor.md), [Refactor.md §11.4 S04](../../../../../Refactor.md) |

## B0013

[Lines 84–115](../../../../../tests/unit/index_directory_test.cpp#L84); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void empty_and_capacity() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Check empty/capped directory startup and capacity behavior. |
| inputs / outputs | No input; probes empty find/growth token, capped 8-slot directory and over-cap requests. |
| invariants | Empty lookup costs startup; abandoned growth is unpublished; over-cap rejection preserves list. |
| ownership | Directories own arrays; fixture Nodes owned separately. |
| failure | Requires storage_work_limit/storage_capacity. |
| cost | Few fixed lookups and capacity probes. |
| Design | tests/unit/index_directory_test.cpp:84-115, docs/indexed_storage.md:35-89, docs/memory_accounts.md:378-409, [Refactor.md §6.2](../../../../../Refactor.md), [Refactor.md §11.4 S04](../../../../../Refactor.md) |

## B0015

[Lines 117–168](../../../../../tests/unit/index_directory_test.cpp#L117); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void collisions_and_growth() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Check full-hash collisions, masked-bucket collisions and growth publication. |
| inputs / outputs | No input; uses real Nodes with forced hashes, private growth tokens and exact work grants. |
| invariants | Full hashes compare exact chain; bucket-only mismatch skips equality; growth preserves resident order. |
| ownership | Directory borrows nodes; prepared growth token owns private array until publish/destruction. |
| failure | Work/capacity failures leave grant/membership atomic. |
| cost | Six-node collision chain, rehash and bounded lookup probes. |
| Design | tests/unit/index_directory_test.cpp:117-168, docs/indexed_storage.md:35-89, docs/memory_accounts.md:378-409, [Refactor.md §6.2](../../../../../Refactor.md), [Refactor.md §11.4 S04](../../../../../Refactor.md) |

## B0017

[Lines 170–180](../../../../../tests/unit/index_directory_test.cpp#L170); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void independent_hooks() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Keep two intrusive hooks independently indexed. |
| inputs / outputs | No input; links same Node in primary and identity directories, then unlinks only primary. |
| invariants | Removing one hook does not disturb the second directory membership. |
| ownership | Node is shared caller-owned fixture; both directories borrow it. |
| failure | Work failure propagates before publication. |
| cost | Two directory inserts and lookups. |
| Design | tests/unit/index_directory_test.cpp:170-180, docs/indexed_storage.md:35-89, docs/memory_accounts.md:378-409, [Refactor.md §6.2](../../../../../Refactor.md), [Refactor.md §11.4 S04](../../../../../Refactor.md) |

## B0019

[Lines 182–199](../../../../../tests/unit/index_directory_test.cpp#L182); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void restored_neighbors() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Reserve unlink and inverse link work, grow, then restore exact neighbors. |
| inputs / outputs | No input; removes two nodes, grows to 16 and relinks between saved neighbors. |
| invariants | One aggregate IndexWork grant prepays forward/inverse actions; original traversal order returns. |
| ownership | Directory and Nodes are fixture-owned; prepared growth remains private until publish. |
| failure | Any over-budget/cap failure aborts before publication. |
| cost | Three nodes, two removals, one growth and two restoration links. |
| Design | tests/unit/index_directory_test.cpp:182-199, docs/indexed_storage.md:35-89, docs/memory_accounts.md:378-409, [Refactor.md §6.2](../../../../../Refactor.md), [Refactor.md §11.4 S04](../../../../../Refactor.md) |

## B0021

[Lines 201–232](../../../../../tests/unit/index_directory_test.cpp#L201); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void generated_tape() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Run 5000 deterministic directory insert/erase/probe steps. |
| inputs / outputs | No input; xorshift tape updates directory and independent map/order model. |
| invariants | Every step compares live order and exact find results for keys 0..32. |
| ownership | Model owns unique_ptr Nodes; directory borrows resident links. |
| failure | Assertion/work/capacity failures surface. |
| cost | 5000 steps with 33 probes per step; finite model overhead. |
| Design | tests/unit/index_directory_test.cpp:201-232, docs/indexed_storage.md:35-89, docs/memory_accounts.md:378-409, [Refactor.md §6.2](../../../../../Refactor.md), [Refactor.md §11.4 S04](../../../../../Refactor.md) |

## B0022

[Lines 233–234](../../../../../tests/unit/index_directory_test.cpp#L233); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L233-L234:sha256:c2bd7638f09d52cb034ed574f539304035fc6fab162bf8d5fa20a35d8c7288a1
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Close the recorded declaration scopes in index_directory_test.cpp: namespace (anonymous). |
| inputs / outputs | Preceding namespace, type or initializer declarations in; completed lexical boundary out. |
| invariants | Brace-opening context is recorded in root-scope-context-v1.json. These are declaration/initializer boundaries, not an independent update, validation or recovery operation. |
| ownership | Enclosing objects and borrowed fields keep their declared ownership. This punctuation creates no new owner. |
| failure | Malformed scope syntax is a compile error. Any initializer/constructor failure belongs to the enclosing object declaration. |
| cost | No separate loop, guard or engine call is introduced by the delimiter; enclosing initialization and object lifetime still have their actual costs. |
| Design | [tests/unit/index_directory_test.cpp](../../../../../tests/unit/index_directory_test.cpp), [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/code_review.md](../../../../code_review.md), [src/storage/hash_directory.hpp](../../../../../src/storage/hash_directory.hpp) |

## B0023

[Lines 235–238](../../../../../tests/unit/index_directory_test.cpp#L235); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
int main() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Run directory allowance, capacity, collision, hook, undo and tape cases. |
| inputs / outputs | No input; calls six scenarios and prints summary. |
| invariants | Every literal invariant/assertion must hold. |
| ownership | main owns only call order. |
| failure | Unexpected error fails process. |
| cost | Finite cases including 5000 tape steps; not run here. |
| Design | tests/unit/index_directory_test.cpp:235-238, docs/indexed_storage.md:35-89, docs/memory_accounts.md:378-409, [Refactor.md §6.2](../../../../../Refactor.md), [Refactor.md §11.4 S04](../../../../../Refactor.md) |
