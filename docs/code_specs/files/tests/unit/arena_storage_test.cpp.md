# `tests/unit/arena_storage_test.cpp` — block usage map

[Source](../../../../../tests/unit/arena_storage_test.cpp) · [Source index](../../../README.md) · [Subsystem contracts](../../../subsystem_contracts.md) · [Reviewed primitives](../../../primitives.md)

Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection.

Snapshot SHA-256: `a6e2f7b0918a0f127f291d8fcd19f735029b3551cdbbd759482d7f525fbac395`. 203 lines partitioned into 15 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [tests](../../../subsystem_contracts.md#tests). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/code_review.md](../../../../code_review.md), [docs/reference_fuzz.md](../../../../reference_fuzz.md), [docs/task_ledger.md](../../../../task_ledger.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–19](../../../../../tests/unit/arena_storage_test.cpp#L1) | Imports dependencies; declares namespace scope; declares aliases. |  · [reviewed contract](#b0001) |
| [B0002 · 20–22](../../../../../tests/unit/arena_storage_test.cpp#L20) | Callable definition: void check(bool value, std::string_view message) | calls std::runtime_error, std::string; guard void check(bool value, std::string_view message) { · [reviewed contract](#b0002) |
| [B0003 · 23–27](../../../../../tests/unit/arena_storage_test.cpp#L23) | Callable definition: template&lt;class Action&gt; void error(Action&& action, std::string_view code) | calls action, check, code, std::runtime_error; guard catch (const Error& failure) { check(failure.code()==code,"wrong storage error"); return; } · [reviewed contract](#b0003) |
| [B0004 · 28–28](../../../../../tests/unit/arena_storage_test.cpp#L28) | Callable definition: TupleLayout layout() | calls ; returns {LayoutId{1},{{ScalarType::int64},{ScalarType::string}}} · [reviewed contract](#b0004) |
| [B0005 · 29–31](../../../../../tests/unit/arena_storage_test.cpp#L29) | Callable definition: Tuple value(const TupleLayout& source, std::int64_t number) | calls tuple, std::string; returns source.tuple({Value{number}, Value{std::string(240,static_cast&lt;char&gt;(@ +number%20))}}) · [reviewed contract](#b0005) |
| [B0006 · 32–34](../../../../../tests/unit/arena_storage_test.cpp#L32) | Callable definition: Projection key(const TupleLayout& source) | calls projected_layout; returns {source,projected_layout(LayoutId{2},source,std::vector&lt;FieldId&gt;{{0}}),{{0}}} · [reviewed contract](#b0006) |
| [B0007 · 35–69](../../../../../tests/unit/arena_storage_test.cpp#L35) | Callable definition: void boundaries() | calls layout, add_index, key, value; guard check(&one.get()==address && &two.get()==address,"table pins copy payload instead of retaining it");; growth insert · [reviewed contract](#b0007) |
| [B0008 · 70–70](../../../../../tests/unit/arena_storage_test.cpp#L70) | Explanatory comments or spacing. |  |
| [B0009 · 71–100](../../../../../tests/unit/arena_storage_test.cpp#L71) | Callable definition: void destruction_and_bulk() | calls layout, add_index, projected_layout, insert; guard check(table.erase_key(nullary,table.projection(nullary).target().tuple({}))==24,"bulk key erase mis…; growth emplace, insert; 1 loop sites · [reviewed contract](#b0009) |
| [B0010 · 101–101](../../../../../tests/unit/arena_storage_test.cpp#L101) | Explanatory comments or spacing. |  |
| [B0011 · 102–129](../../../../../tests/unit/arena_storage_test.cpp#L102) | Callable definition: void snapshot_copy() | calls planner::lower_tree, nodes, table, layout; guard auto retired=table.pin(first); check(table.erase(first),"snapshot fixture erase");; growth insert · [reviewed contract](#b0011) |
| [B0012 · 130–130](../../../../../tests/unit/arena_storage_test.cpp#L130) | Explanatory comments or spacing. |  |
| [B0013 · 131–198](../../../../../tests/unit/arena_storage_test.cpp#L131) | Callable definition: void model() | calls layout, add_index, key, projected_layout; guard check(result.inserted==(previous==rows.end()),"model duplicate mismatch");; growth emplace, insert, push_back; 5 loop sites · [reviewed contract](#b0013) |
| [B0014 · 199–199](../../../../../tests/unit/arena_storage_test.cpp#L199) | Closes surrounding scope/type. | source comment (unverified): // namespace · [reviewed contract](#b0014) |
| [B0015 · 200–203](../../../../../tests/unit/arena_storage_test.cpp#L200) | Callable definition: int main() | calls boundaries, destruction_and_bulk, snapshot_copy, model; returns 1 · [reviewed contract](#b0015) |

## B0001

[Lines 1–19](../../../../../tests/unit/arena_storage_test.cpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L1-L19:sha256:b718548e57c1adaf8b4d36b634dc6013d3e0a9389d1ed807f2fe01c137e7da04
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Prepare arena_storage_test.cpp: include "crown/api/error.hpp", "crown/planner/lower.hpp", "crown/storage/physical.hpp", &lt;algorithm&gt;, &lt;iostream&gt;, &lt;iterator&gt;, &lt;map&gt;, &lt;optional&gt;, &lt;random&gt;, &lt;set&gt;, &lt;stdexcept&gt;, &lt;string_view&gt;, &lt;utility&gt;, &lt;vector&gt;; bind local aliases/name imports. |
| inputs / outputs | Compiler-visible dependencies, names and the recorded declarations in; declarations available to the following fixture/CLI/example definitions out. |
| invariants | Declarations are scoped to this source/header and its selected ABI. Included code has its own effects; names and editable fixture values do not confer proof, admission or publication authority. |
| ownership | Aliases/includes do not create a query owner. Pointers/references/views are non-owning. Containers own their elements, which can themselves be borrowed pointers or numeric IDs. Only documented owning shared-control handles retain controls; IDs/slot-handle values do not independently keep an arena/runtime alive. |
| failure | Missing headers, ill-formed names/types, failed static assertions or active #error directives stop compilation. No runtime rejection/rollback mechanism is implemented by aliases or function prototypes. |
| cost | Preprocessing and type/constraint instantiation cost compilation. Alias/prototype syntax does not invoke the declared operation; any included definitions keep their own initialization effects. |
| Design | [tests/unit/arena_storage_test.cpp](../../../../../tests/unit/arena_storage_test.cpp), [docs/storage.md](../../../../storage.md), [docs/code_review.md](../../../../code_review.md) |

## B0002

[Lines 20–22](../../../../../tests/unit/arena_storage_test.cpp#L20); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void check(bool value, std::string_view message) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Fail a small arena/storage assertion. |
| inputs / outputs | Bool/message in; runtime_error on false. |
| invariants | False condition fails the case. |
| ownership | Message borrowed during call. |
| failure | runtime_error is harness carrier. |
| cost | One branch; failure-only diagnostic. |
| Design | tests/unit/arena_storage_test.cpp:20-22, docs/tuple_arenas.md:39-117, docs/storage.md:72-116, [Refactor.md §6.2](../../../../../Refactor.md), [Refactor.md §11.4 S02](../../../../../Refactor.md), [Refactor.md §11.4 S03](../../../../../Refactor.md) |

## B0003

[Lines 23–27](../../../../../tests/unit/arena_storage_test.cpp#L23); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
template<class Action> void error(Action&& action, std::string_view code) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Require one typed storage Error code. |
| inputs / outputs | Action/code in; returns after matching crown::Error. |
| invariants | Wrong or missing Error fails. |
| ownership | Action forwarded; Error borrowed. |
| failure | Mismatch becomes runtime_error; unrelated exceptions propagate. |
| cost | One action and comparison. |
| Design | tests/unit/arena_storage_test.cpp:23-27, docs/tuple_arenas.md:39-117, docs/storage.md:72-116, [Refactor.md §6.2](../../../../../Refactor.md), [Refactor.md §11.4 S02](../../../../../Refactor.md), [Refactor.md §11.4 S03](../../../../../Refactor.md) |

## B0004

[Lines 28–28](../../../../../tests/unit/arena_storage_test.cpp#L28); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
TupleLayout layout() { return {LayoutId{1},{{ScalarType::int64},{ScalarType::string}}}; }
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Build the two-field storage layout. |
| inputs / outputs | No input; ID 1 int64/string layout out. |
| invariants | Fixture rows share layout token. |
| ownership | Returned descriptor owns fields. |
| failure | Construction errors propagate. |
| cost | Fixed descriptor. |
| Design | tests/unit/arena_storage_test.cpp:28-28, docs/tuple_arenas.md:39-117, docs/storage.md:72-116, [Refactor.md §6.2](../../../../../Refactor.md), [Refactor.md §11.4 S02](../../../../../Refactor.md), [Refactor.md §11.4 S03](../../../../../Refactor.md) |

## B0005

[Lines 29–31](../../../../../tests/unit/arena_storage_test.cpp#L29); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Tuple value(const TupleLayout& source, std::int64_t number) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Build a row with deterministic 240-byte text. |
| inputs / outputs | Layout/int64 in; tuple with integer and generated string out. |
| invariants | Text fill is chosen from a finite alphabet. |
| ownership | Tuple owns values. |
| failure | Allocation errors propagate. |
| cost | One fixture string. |
| Design | tests/unit/arena_storage_test.cpp:29-31, docs/tuple_arenas.md:39-117, docs/storage.md:72-116, [Refactor.md §6.2](../../../../../Refactor.md), [Refactor.md §11.4 S02](../../../../../Refactor.md), [Refactor.md §11.4 S03](../../../../../Refactor.md) |

## B0006

[Lines 32–34](../../../../../tests/unit/arena_storage_test.cpp#L32); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Projection key(const TupleLayout& source) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Compile the integer key projection. |
| inputs / outputs | Source layout in; slot-0 projection and target ID 2 out. |
| invariants | Projection source is the supplied layout token. |
| ownership | Projection owns program/descriptor. |
| failure | Projection validation errors propagate. |
| cost | One-field projection. |
| Design | tests/unit/arena_storage_test.cpp:32-34, docs/tuple_arenas.md:39-117, docs/storage.md:72-116, [Refactor.md §6.2](../../../../../Refactor.md), [Refactor.md §11.4 S02](../../../../../Refactor.md), [Refactor.md §11.4 S03](../../../../../Refactor.md) |

## B0007

[Lines 35–69](../../../../../tests/unit/arena_storage_test.cpp#L35); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void boundaries() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Check pinning, erase, clear and generational reuse boundaries. |
| inputs / outputs | No input; duplicate, two pins, erase/reinsert, clear, release and foreign-owner cases. |
| invariants | Pins preserve payload/address but not membership; logical IDs increase; slot generations prevent stale aliasing. |
| ownership | ReferenceTable owns rows/indexes; Pins retain payloads; cursor is fail-fast. |
| failure | Checks stale_handle, invalid_cursor and foreign_handle. |
| cost | Few rows, stats comparisons and invariant checks. |
| Design | tests/unit/arena_storage_test.cpp:35-69, docs/tuple_arenas.md:39-117, docs/storage.md:72-116, [Refactor.md §6.2](../../../../../Refactor.md), [Refactor.md §11.4 S02](../../../../../Refactor.md), [Refactor.md §11.4 S03](../../../../../Refactor.md) |

## B0009

[Lines 71–100](../../../../../tests/unit/arena_storage_test.cpp#L71); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void destruction_and_bulk() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Check bulk nullary erase, destruction and table move ownership. |
| inputs / outputs | No input; 24-row nullary erase with pin, cursor expiry, move replacement and self-move. |
| invariants | Bulk erase removes membership while Pin retains value; moved incoming owner keeps its handle. |
| ownership | Table owns membership; Pin outlives table; cursors borrow weak ownership. |
| failure | Expired cursor/moved-from table use exact Error codes. |
| cost | Nullary deletion touches 24 rows; finite move cases. |
| Design | tests/unit/arena_storage_test.cpp:71-100, docs/tuple_arenas.md:39-117, docs/storage.md:72-116, [Refactor.md §6.2](../../../../../Refactor.md), [Refactor.md §11.4 S02](../../../../../Refactor.md), [Refactor.md §11.4 S03](../../../../../Refactor.md) |

## B0011

[Lines 102–129](../../../../../tests/unit/arena_storage_test.cpp#L102); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void snapshot_copy() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Compare snapshot_copy as a separate live-only PlanStorage owner. |
| inputs / outputs | No input; builds one plan table, retires a pinned row, copies, mutates and moves storage. |
| invariants | Copy preserves live tuple/index ID high-water but has new owner/payloads and excludes retired rows/Pins. |
| ownership | Original and copy own separate arenas; old Pins preserve originals. |
| failure | Copied owner rejects foreign handle; assertion/error helpers retain carriers. |
| cost | Copies only fixture live state; explicit copy utility cost. |
| Design | tests/unit/arena_storage_test.cpp:102-129, docs/tuple_arenas.md:39-117, docs/storage.md:72-116, [Refactor.md §6.2](../../../../../Refactor.md), [Refactor.md §11.4 S02](../../../../../Refactor.md), [Refactor.md §11.4 S03](../../../../../Refactor.md) |

## B0013

[Lines 131–198](../../../../../tests/unit/arena_storage_test.cpp#L131); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void model() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Run eight seeded reference-table arena/model traces. |
| inputs / outputs | No input; 700 steps per seed choose insert/erase/pin/key erase/nullary erase/clear. |
| invariants | After every step counts, values, indexes, pin liveness/address and slot partition match model. |
| ownership | ReferenceTable owns values; Held entries own Pins; model owns expected rows. |
| failure | Mismatches throw runtime_error; storage errors propagate. |
| cost | 5600 updates with snapshots/model scans/invariant checks. |
| Design | tests/unit/arena_storage_test.cpp:131-198, docs/tuple_arenas.md:39-117, docs/storage.md:72-116, [Refactor.md §6.2](../../../../../Refactor.md), [Refactor.md §11.4 S02](../../../../../Refactor.md), [Refactor.md §11.4 S03](../../../../../Refactor.md) |

## B0014

[Lines 199–199](../../../../../tests/unit/arena_storage_test.cpp#L199); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L199-L199:sha256:c7bfe2f3de133d78a2bc8bb1c4a08450563986ee8254facee698e1dcc57e8162
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Close the recorded declaration scopes in arena_storage_test.cpp: namespace (anonymous). |
| inputs / outputs | Preceding namespace, type or initializer declarations in; completed lexical boundary out. |
| invariants | Brace-opening context is recorded in root-scope-context-v1.json. These are declaration/initializer boundaries, not an independent update, validation or recovery operation. |
| ownership | Enclosing objects and borrowed fields keep their declared ownership. This punctuation creates no new owner. |
| failure | Malformed scope syntax is a compile error. Any initializer/constructor failure belongs to the enclosing object declaration. |
| cost | No separate loop, guard or engine call is introduced by the delimiter; enclosing initialization and object lifetime still have their actual costs. |
| Design | [tests/unit/arena_storage_test.cpp](../../../../../tests/unit/arena_storage_test.cpp), [docs/storage.md](../../../../storage.md), [docs/code_review.md](../../../../code_review.md) |

## B0015

[Lines 200–203](../../../../../tests/unit/arena_storage_test.cpp#L200); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
int main() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Run reference arena boundary, destruction, copy and model cases. |
| inputs / outputs | No input; invokes four cases and reports success. |
| invariants | Every finite assertion must pass. |
| ownership | main owns orchestration. |
| failure | std::exception prints and returns 1. |
| cost | No test execution is claimed. |
| Design | tests/unit/arena_storage_test.cpp:200-203, docs/tuple_arenas.md:39-117, docs/storage.md:72-116, [Refactor.md §6.2](../../../../../Refactor.md), [Refactor.md §11.4 S02](../../../../../Refactor.md), [Refactor.md §11.4 S03](../../../../../Refactor.md) |
