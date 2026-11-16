# `tests/unit/storage_model_test.cpp` — block usage map

[Source](../../../../../tests/unit/storage_model_test.cpp) · [Source index](../../../README.md) · [Subsystem contracts](../../../subsystem_contracts.md) · [Reviewed primitives](../../../primitives.md)

Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection.

Snapshot SHA-256: `110066ee59ca2d70e339037c003e74d98375db32dec6715104d8ac5ad4946e31`. 574 lines partitioned into 37 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [tests](../../../subsystem_contracts.md#tests). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/code_review.md](../../../../code_review.md), [docs/reference_fuzz.md](../../../../reference_fuzz.md), [docs/task_ledger.md](../../../../task_ledger.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–23](../../../../../tests/unit/storage_model_test.cpp#L1) | Imports dependencies; declares namespace scope; declares aliases; declares values/defaults or compile-time conditions. |  · [reviewed contract](#b0001) |
| [B0002 · 24–26](../../../../../tests/unit/storage_model_test.cpp#L24) | Callable definition: void check(bool condition, const std::string& message) | calls std::runtime_error; guard void check(bool condition, const std::string& message) { · [reviewed contract](#b0002) |
| [B0003 · 27–35](../../../../../tests/unit/storage_model_test.cpp#L27) | Callable definition: template &lt;class Action&gt; void expect_error(Action&& action, std::string_view code) | calls action, check, code, std::runtime_error; guard check(failure.code() == code, "wrong storage error: " + failure.code()); · [reviewed contract](#b0003) |
| [B0004 · 36–36](../../../../../tests/unit/storage_model_test.cpp#L36) | Explanatory comments or spacing. |  |
| [B0005 · 37–42](../../../../../tests/unit/storage_model_test.cpp#L37) | Callable definition: TupleLayout source_layout(LayoutId id = LayoutId{1}, LayoutContext context = {17, "storage-model"}) | calls std::move; returns TupleLayout{id, · [reviewed contract](#b0005) |
| [B0006 · 43–43](../../../../../tests/unit/storage_model_test.cpp#L43) | Explanatory comments or spacing. |  |
| [B0007 · 44–48](../../../../../tests/unit/storage_model_test.cpp#L44) | Callable definition: Row sample_row(std::int64_t integer, std::string text, bool flag, std::string_view day, std::string_view amount) | calls std::move, Date::parse, Decimal::parse; returns Row{Value{integer}, Value{std::move(text)}, Value{flag}, · [reviewed contract](#b0007) |
| [B0008 · 49–49](../../../../../tests/unit/storage_model_test.cpp#L49) | Explanatory comments or spacing. |  |
| [B0009 · 50–55](../../../../../tests/unit/storage_model_test.cpp#L50) | Callable definition: std::vector&lt;FieldId&gt; fields_for(const Slots& slots) | calls reserve, size, push_back; returns fields; growth push_back, reserve; 1 loop sites · [reviewed contract](#b0009) |
| [B0010 · 56–58](../../../../../tests/unit/storage_model_test.cpp#L56) | Explanatory comments or spacing. | source comment (unverified): // The model's key extraction is deliberately a raw positional loop. It never · [reviewed contract](#b0010) |
| [B0011 · 59–64](../../../../../tests/unit/storage_model_test.cpp#L59) | Callable definition: Row raw_key(const Row& row, const Slots& slots) | calls reserve, size, push_back, at; returns result; growth push_back, reserve; 1 loop sites; source comment (unverified): // The model's key extraction is deliberately a raw positional loop. It never · [reviewed contract](#b0011) |
| [B0012 · 65–65](../../../../../tests/unit/storage_model_test.cpp#L65) | Explanatory comments or spacing. |  |
| [B0013 · 66–68](../../../../../tests/unit/storage_model_test.cpp#L66) | Callable definition: std::vector&lt;Slots&gt; projection_shapes() | calls ; returns {{}, {0}, {1, 0}, {4, 1, 4}, {2, 3, 1}, {3, 2, 0, 4}} · [reviewed contract](#b0013) |
| [B0014 · 69–69](../../../../../tests/unit/storage_model_test.cpp#L69) | Explanatory comments or spacing. |  |
| [B0015 · 70–72](../../../../../tests/unit/storage_model_test.cpp#L70) | Callable definition: std::size_t pick(std::mt19937_64& random, std::size_t bound) | calls random; returns static_cast&lt;std::size_t&gt;(random() % static_cast&lt;std::uint64_t&gt;(bound)) · [reviewed contract](#b0015) |
| [B0016 · 73–73](../../../../../tests/unit/storage_model_test.cpp#L73) | Explanatory comments or spacing. |  |
| [B0017 · 74–87](../../../../../tests/unit/storage_model_test.cpp#L74) | Callable definition: Row random_row(std::mt19937_64& random) | calls std::string, Date::parse, Decimal::parse, random; returns Row{Value{integer}, Value{texts\[pick(random, texts.size())\]}, · [reviewed contract](#b0017) |
| [B0018 · 88–88](../../../../../tests/unit/storage_model_test.cpp#L88) | Explanatory comments or spacing. |  |
| [B0019 · 89–92](../../../../../tests/unit/storage_model_test.cpp#L89) | Type/record definition: struct ModelIndex |  · [reviewed contract](#b0019) |
| [B0020 · 93–98](../../../../../tests/unit/storage_model_test.cpp#L93) | declares aliases; declares values/defaults or compile-time conditions. |  · [reviewed contract](#b0020) |
| [B0021 · 99–103](../../../../../tests/unit/storage_model_test.cpp#L99) | Callable definition: ExpectedBuckets expected_buckets(const Rows& rows, const Slots& slots) | calls raw_key, insert; returns result; growth insert; 1 loop sites · [reviewed contract](#b0021) |
| [B0022 · 104–104](../../../../../tests/unit/storage_model_test.cpp#L104) | Explanatory comments or spacing. |  |
| [B0023 · 105–192](../../../../../tests/unit/storage_model_test.cpp#L105) | Callable definition: void compare_table(ReferenceTable& table, const TupleLayout& source, const Rows& rows, const HandlesByRow& handles, const Indexes… | calls check_invariants, check, size, snapshot; guard check(table.size() == rows.size(), where + ": primary row count");; growth insert; 12 loop sites · [reviewed contract](#b0023) |
| [B0024 · 193–193](../../../../../tests/unit/storage_model_test.cpp#L193) | Explanatory comments or spacing. |  |
| [B0025 · 194–208](../../../../../tests/unit/storage_model_test.cpp#L194) | Callable definition: void add_model_index(ReferenceTable& table, const TupleLayout& source, const Slots& slots, LayoutId target_id, Indexes& indexes, … | calls fields_for, projected_layout, program, add_index; guard check(inserted, "fresh projection registration unexpectedly reused an active index ID");; growth emplace, insert · [reviewed contract](#b0025) |
| [B0026 · 209–209](../../../../../tests/unit/storage_model_test.cpp#L209) | Explanatory comments or spacing. |  |
| [B0027 · 210–249](../../../../../tests/unit/storage_model_test.cpp#L210) | Callable definition: void no_op_and_cursor_contract() | calls source_layout, table, sample_row, insert; guard check(inserted.inserted, "initial row was not inserted");; growth insert · [reviewed contract](#b0027) |
| [B0028 · 250–250](../../../../../tests/unit/storage_model_test.cpp#L250) | Explanatory comments or spacing. |  |
| [B0029 · 251–309](../../../../../tests/unit/storage_model_test.cpp#L251) | Callable definition: void shared_target_layout_interoperability() | calls source_layout, right_layout, TupleLayout, left_projection; guard check(!left_projection.source().same_token(right_projection.source()),; growth insert; 2 loop sites; source comment (unverified): // Production projection is used only to form the actual lookup key here. · [reviewed contract](#b0029) |
| [B0030 · 310–310](../../../../../tests/unit/storage_model_test.cpp#L310) | Explanatory comments or spacing. |  |
| [B0031 · 311–335](../../../../../tests/unit/storage_model_test.cpp#L311) | Callable definition: void ids_survive_clear_and_reinsertion() | calls source_layout, table, sample_row, insert; guard check(first.inserted && first.handle.tuple.value != 0, "first tuple ID was not allocated");; growth insert · [reviewed contract](#b0031) |
| [B0032 · 336–336](../../../../../tests/unit/storage_model_test.cpp#L336) | Explanatory comments or spacing. |  |
| [B0033 · 337–421](../../../../../tests/unit/storage_model_test.cpp#L337) | Callable definition: void cursor_ownership_and_moves() | calls source_layout, projected_layout, sample_row, tuple; guard check(!table.erase(layout.tuple(row)) && table.erase_key(index, absent_key) == 0,; returns tuple.values() == row; growth emplace, insert · [reviewed contract](#b0033) |
| [B0034 · 422–422](../../../../../tests/unit/storage_model_test.cpp#L422) | Explanatory comments or spacing. |  |
| [B0035 · 423–557](../../../../../tests/unit/storage_model_test.cpp#L423) | Callable definition: void randomized_model() | calls projection_shapes, source_layout, random, table; guard check(result.inserted, "new row insertion was reported as duplicate");; growth emplace, insert; 5 loop sites; source comment (unverified): // Check that duplicate/absent row operations leave an already-created · [reviewed contract](#b0035) |
| [B0036 · 558–560](../../../../../tests/unit/storage_model_test.cpp#L558) | Closes surrounding scope/type. | source comment (unverified): // namespace · [reviewed contract](#b0036) |
| [B0037 · 561–574](../../../../../tests/unit/storage_model_test.cpp#L561) | Callable definition: int main() | calls no_op_and_cursor_contract, shared_target_layout_interoperability, ids_survive_clear_and_reinsertion, cursor_ownership_and_moves; returns 0; 1 · [reviewed contract](#b0037) |

## B0001

[Lines 1–23](../../../../../tests/unit/storage_model_test.cpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L1-L23:sha256:f54cd5031af0eed8653d4fe0d5cfc073b8c575a1fcdb3da74dbf993e27ed3da8
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Prepare storage_model_test.cpp: include "crown/api/error.hpp", "crown/storage/reference.hpp", &lt;algorithm&gt;, &lt;array&gt;, &lt;cstdint&gt;, &lt;iostream&gt;, &lt;iterator&gt;, &lt;map&gt;, &lt;optional&gt;, &lt;random&gt;, &lt;set&gt;, &lt;stdexcept&gt;, &lt;string&gt;, &lt;string_view&gt;, &lt;utility&gt;, &lt;vector&gt;; bind local aliases/name imports. |
| inputs / outputs | Compiler-visible dependencies, names and the recorded declarations in; declarations available to the following fixture/CLI/example definitions out. |
| invariants | Declarations are scoped to this source/header and its selected ABI. Included code has its own effects; names and editable fixture values do not confer proof, admission or publication authority. |
| ownership | Aliases/includes do not create a query owner. Pointers/references/views are non-owning. Containers own their elements, which can themselves be borrowed pointers or numeric IDs. Only documented owning shared-control handles retain controls; IDs/slot-handle values do not independently keep an arena/runtime alive. |
| failure | Missing headers, ill-formed names/types, failed static assertions or active #error directives stop compilation. No runtime rejection/rollback mechanism is implemented by aliases or function prototypes. |
| cost | Preprocessing and type/constraint instantiation cost compilation. Alias/prototype syntax does not invoke the declared operation; any included definitions keep their own initialization effects. |
| Design | [tests/unit/storage_model_test.cpp](../../../../../tests/unit/storage_model_test.cpp), [docs/storage.md](../../../../storage.md), [docs/code_review.md](../../../../code_review.md) |

## B0002

[Lines 24–26](../../../../../tests/unit/storage_model_test.cpp#L24); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void check(bool condition, const std::string& message) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Fail one storage-model assertion. |
| inputs / outputs | Bool/message in; runtime_error on false. |
| invariants | False model comparison cannot pass. |
| ownership | Message is borrowed except failure construction. |
| failure | runtime_error is harness carrier. |
| cost | One branch; error text on failure. |
| Design | tests/unit/storage_model_test.cpp:24-26, docs/storage.md:11-116, docs/tuple_arenas.md:39-139, [Refactor.md §6.2](../../../../../Refactor.md), [Refactor.md §11.4 S02](../../../../../Refactor.md) |

## B0003

[Lines 27–35](../../../../../tests/unit/storage_model_test.cpp#L27); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
template <class Action>
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Require one crown::Error code from a reference-storage action. |
| inputs / outputs | Action/code in; returns after exact code match. |
| invariants | Wrong or absent Error fails. |
| ownership | Action is forwarded; caught Error borrowed. |
| failure | Mismatch becomes runtime_error; unrelated errors propagate. |
| cost | One action and comparison. |
| Design | tests/unit/storage_model_test.cpp:27-35, docs/storage.md:11-116, docs/tuple_arenas.md:39-139, [Refactor.md §6.2](../../../../../Refactor.md), [Refactor.md §11.4 S02](../../../../../Refactor.md) |

## B0005

[Lines 37–42](../../../../../tests/unit/storage_model_test.cpp#L37); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
TupleLayout source_layout(LayoutId id = LayoutId{1}, LayoutContext context = {17, "storage-model"}) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Create the five-scalar reference-model layout. |
| inputs / outputs | Optional ID/context in; int64/string/bool/date/decimal layout out. |
| invariants | Each test table uses its own explicit layout token/context. |
| ownership | Returned layout owns descriptors/context. |
| failure | Construction errors propagate. |
| cost | Fixed five-field descriptor. |
| Design | tests/unit/storage_model_test.cpp:37-42, docs/storage.md:11-116, docs/tuple_arenas.md:39-139, [Refactor.md §6.2](../../../../../Refactor.md), [Refactor.md §11.4 S02](../../../../../Refactor.md) |

## B0007

[Lines 44–48](../../../../../tests/unit/storage_model_test.cpp#L44); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Row sample_row(std::int64_t integer, std::string text, bool flag, std::string_view day,
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Create one mixed-scalar expected Row from literals. |
| inputs / outputs | Integer/text/bool/day/amount in; parsed Date and Decimal Row out. |
| invariants | Inputs supply all five scalar types. |
| ownership | Returned Row owns string. |
| failure | Parsing/allocation failures propagate. |
| cost | One row construction. |
| Design | tests/unit/storage_model_test.cpp:44-48, docs/storage.md:11-116, docs/tuple_arenas.md:39-139, [Refactor.md §6.2](../../../../../Refactor.md), [Refactor.md §11.4 S02](../../../../../Refactor.md) |

## B0009

[Lines 50–55](../../../../../tests/unit/storage_model_test.cpp#L50); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::vector<FieldId> fields_for(const Slots& slots) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Translate raw positional slots into FieldIds. |
| inputs / outputs | Vector of size_t positions in; same ordered FieldId vector out. |
| invariants | Repeated/reordered positions are retained. |
| ownership | Returns a new vector. |
| failure | Allocation failure propagates. |
| cost | Linear in projected field count. |
| Design | tests/unit/storage_model_test.cpp:50-55, docs/storage.md:11-116, docs/tuple_arenas.md:39-139, [Refactor.md §6.2](../../../../../Refactor.md), [Refactor.md §11.4 S02](../../../../../Refactor.md) |

## B0010

[Lines 56–58](../../../../../tests/unit/storage_model_test.cpp#L56); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L56-L58:sha256:076ddcc108df6c6d38e3173eee0d460e1fb59cd271f9a3e5bc628de33d83cb99
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Explain the adjacent source contract: The model's key extraction is deliberately a raw positional loop. It never calls Projection::apply or uses a key returned by the production index. |
| inputs / outputs | Human-readable source note in; no executable output or checked receipt. |
| invariants | This comment states context or a limitation. It does not itself enforce or prove the described behavior; use the adjacent implementation and its scoped contract. |
| ownership | Source text only; no object or resource lifetime is created. |
| failure | No runtime failure path in this comment; source encoding/comment syntax still belongs to compilation. |
| cost | No runtime operations from the comment. Any work described in the note belongs to the adjacent operation. |
| Design | [tests/unit/storage_model_test.cpp](../../../../../tests/unit/storage_model_test.cpp), [docs/storage.md](../../../../storage.md), [docs/code_review.md](../../../../code_review.md) |

## B0011

[Lines 59–64](../../../../../tests/unit/storage_model_test.cpp#L59); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Row raw_key(const Row& row, const Slots& slots) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Extract an independent expected key by raw positions. |
| inputs / outputs | Row/slot list in; copied Row of selected positions out. |
| invariants | Does not call Projection::apply or read production index output. |
| ownership | Returned Row owns copied Values. |
| failure | Out-of-range slot propagates from at. |
| cost | Copies key fields; test-oracle work. |
| Design | tests/unit/storage_model_test.cpp:59-64, docs/storage.md:11-116, docs/tuple_arenas.md:39-139, [Refactor.md §6.2](../../../../../Refactor.md), [Refactor.md §11.4 S02](../../../../../Refactor.md) |

## B0013

[Lines 66–68](../../../../../tests/unit/storage_model_test.cpp#L66); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::vector<Slots> projection_shapes() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Return six empty/single/composite/reordered/repeated projection shapes. |
| inputs / outputs | No input; fixed vector of slot vectors out. |
| invariants | Includes nullary, reordered and repeated positions. |
| ownership | Returns test-owned vector. |
| failure | Allocation failure propagates. |
| cost | Fixed six-shape construction. |
| Design | tests/unit/storage_model_test.cpp:66-68, docs/storage.md:11-116, docs/tuple_arenas.md:39-139, [Refactor.md §6.2](../../../../../Refactor.md), [Refactor.md §11.4 S02](../../../../../Refactor.md) |

## B0015

[Lines 70–72](../../../../../tests/unit/storage_model_test.cpp#L70); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::size_t pick(std::mt19937_64& random, std::size_t bound) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Choose a bounded position for seeded reference-model data. |
| inputs / outputs | PRNG reference/bound in; modulo-selected size_t out. |
| invariants | Callers provide nonzero bound. |
| ownership | Borrows PRNG. |
| failure | No custom catch. |
| cost | One draw and modulo. |
| Design | tests/unit/storage_model_test.cpp:70-72, docs/storage.md:11-116, docs/tuple_arenas.md:39-139, [Refactor.md §6.2](../../../../../Refactor.md), [Refactor.md §11.4 S02](../../../../../Refactor.md) |

## B0017

[Lines 74–87](../../../../../tests/unit/storage_model_test.cpp#L74); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Row random_row(std::mt19937_64& random) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Generate mixed-scalar randomized model rows. |
| inputs / outputs | PRNG in; bounded int, text including embedded NUL, bool, date and decimal out. |
| invariants | Domain is fixed and finite; decimal aliases may normalize to same Value. |
| ownership | Returned Row owns text. |
| failure | Normal value construction errors propagate. |
| cost | One selection per scalar domain. |
| Design | tests/unit/storage_model_test.cpp:74-87, docs/storage.md:11-116, docs/tuple_arenas.md:39-139, [Refactor.md §6.2](../../../../../Refactor.md), [Refactor.md §11.4 S02](../../../../../Refactor.md) |

## B0019

[Lines 89–92](../../../../../tests/unit/storage_model_test.cpp#L89); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct ModelIndex {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Pair an immutable Projection with its raw source-slot model. |
| inputs / outputs | Projection and slot vector in; ModelIndex out. |
| invariants | Raw slot list remains the expected key definition. |
| ownership | Model owns copied slots and Projection value. |
| failure | No custom failure path. |
| cost | Stores projection plus vector. |
| Design | tests/unit/storage_model_test.cpp:89-92, docs/storage.md:11-116, docs/tuple_arenas.md:39-139, [Refactor.md §6.2](../../../../../Refactor.md), [Refactor.md §11.4 S02](../../../../../Refactor.md) |

## B0020

[Lines 93–98](../../../../../tests/unit/storage_model_test.cpp#L93); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L93-L98:sha256:f6f8544403d6aa7fd18c8116732829d6cb8ad1e3c5ae9322ec5e5b5a8f139832
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Prepare storage_model_test.cpp: bind local aliases/name imports. |
| inputs / outputs | Compiler-visible dependencies, names and the recorded declarations in; declarations available to the following fixture/CLI/example definitions out. |
| invariants | Declarations are scoped to this source/header and its selected ABI. Included code has its own effects; names and editable fixture values do not confer proof, admission or publication authority. |
| ownership | Aliases/includes do not create a query owner. Pointers/references/views are non-owning. Containers own their elements, which can themselves be borrowed pointers or numeric IDs. Only documented owning shared-control handles retain controls; IDs/slot-handle values do not independently keep an arena/runtime alive. |
| failure | Missing headers, ill-formed names/types, failed static assertions or active #error directives stop compilation. No runtime rejection/rollback mechanism is implemented by aliases or function prototypes. |
| cost | Preprocessing and type/constraint instantiation cost compilation. Alias/prototype syntax does not invoke the declared operation; any included definitions keep their own initialization effects. |
| Design | [tests/unit/storage_model_test.cpp](../../../../../tests/unit/storage_model_test.cpp), [docs/storage.md](../../../../storage.md), [docs/code_review.md](../../../../code_review.md) |

## B0021

[Lines 99–103](../../../../../tests/unit/storage_model_test.cpp#L99); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
ExpectedBuckets expected_buckets(const Rows& rows, const Slots& slots) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Build expected key-to-row buckets using raw_key. |
| inputs / outputs | Rows/slot positions in; ordered map from key to matching Rows out. |
| invariants | Expected membership does not use a production bucket result. |
| ownership | All maps/rows are independent test-owned copies. |
| failure | Allocation failure propagates. |
| cost | Scans each expected row and copies its key. |
| Design | tests/unit/storage_model_test.cpp:99-103, docs/storage.md:11-116, docs/tuple_arenas.md:39-139, [Refactor.md §6.2](../../../../../Refactor.md), [Refactor.md §11.4 S02](../../../../../Refactor.md) |

## B0023

[Lines 105–192](../../../../../tests/unit/storage_model_test.cpp#L105); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void compare_table(ReferenceTable& table, const TupleLayout& source, const Rows& rows,
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Reconcile primary rows, handles, cursors and all index buckets. |
| inputs / outputs | Table/layout/model rows/handles/indexes/context in; throws on any differing snapshot, lookup, key, bucket or cursor. |
| invariants | Projection keys come from raw positional extraction; token identity and bucket membership are checked independently. |
| ownership | Table owns native tuples; snapshots and model maps are observer/test-owned. |
| failure | Unexpected storage errors propagate; mismatches throw runtime_error. |
| cost | Scans rows and every key/member/cursor; diagnostic model cost. |
| Design | tests/unit/storage_model_test.cpp:105-192, docs/storage.md:11-116, docs/tuple_arenas.md:39-139, [Refactor.md §6.2](../../../../../Refactor.md), [Refactor.md §11.4 S02](../../../../../Refactor.md) |

## B0025

[Lines 194–208](../../../../../tests/unit/storage_model_test.cpp#L194); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void add_model_index(ReferenceTable& table, const TupleLayout& source, const Slots& slots,
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Register one projection and update ID/index model. |
| inputs / outputs | Table/layout/slot shape/target ID/model in; adds projection and records monotonic ID. |
| invariants | Same program token is idempotent; a fresh ID is not reused after drop/clear. |
| ownership | Table and model independently retain programs. |
| failure | Unexpected ID/order/idempotence throws runtime_error. |
| cost | Builds key/projection and may scan existing rows in production index construction. |
| Design | tests/unit/storage_model_test.cpp:194-208, docs/storage.md:11-116, docs/tuple_arenas.md:39-139, [Refactor.md §6.2](../../../../../Refactor.md), [Refactor.md §11.4 S02](../../../../../Refactor.md) |

## B0027

[Lines 210–249](../../../../../tests/unit/storage_model_test.cpp#L210); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void no_op_and_cursor_contract() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Check no-op revision and cursor behavior plus indexed key erase. |
| inputs / outputs | No input; duplicate/absent operations keep cursor, then real insert/index/erase_key changes membership. |
| invariants | No-ops preserve revision; real mutation invalidates cursor; deleting last bucket member removes key. |
| ownership | Table owns rows; cursor is borrowed/fail-fast. |
| failure | Unexpected Error is observed as invalidation; failed assertions throw runtime_error. |
| cost | Two rows, one index and cursor/key probes. |
| Design | tests/unit/storage_model_test.cpp:210-249, docs/storage.md:11-116, docs/tuple_arenas.md:39-139, [Refactor.md §6.2](../../../../../Refactor.md), [Refactor.md §11.4 S02](../../../../../Refactor.md) |

## B0029

[Lines 251–309](../../../../../tests/unit/storage_model_test.cpp#L251); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void shared_target_layout_interoperability() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Check shared target token interoperability across distinct source layouts. |
| inputs / outputs | No input; makes left/right projections with one target token and probes shared key. |
| invariants | Different source tokens can address same key token; foreign table handles cannot read/delete local rows. |
| ownership | Two tables own independent rows; projected key is owning tuple. |
| failure | Foreign get/erase may reject or return absent, never mutate other table. |
| cost | Two small table/index builds and invariant scans. |
| Design | tests/unit/storage_model_test.cpp:251-309, docs/storage.md:11-116, docs/tuple_arenas.md:39-139, [Refactor.md §6.2](../../../../../Refactor.md), [Refactor.md §11.4 S02](../../../../../Refactor.md) |

## B0031

[Lines 311–335](../../../../../tests/unit/storage_model_test.cpp#L311); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void ids_survive_clear_and_reinsertion() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Check tuple and index IDs survive clear, drop and reinsertion. |
| inputs / outputs | No input; inserts row/index, clears/drops and creates replacements. |
| invariants | Both logical ID counters remain monotonic within table owner. |
| ownership | ReferenceTable owns IDs/state. |
| failure | Any reused/zero ID assertion fails. |
| cost | Two inserts and two index registrations. |
| Design | tests/unit/storage_model_test.cpp:311-335, docs/storage.md:11-116, docs/tuple_arenas.md:39-139, [Refactor.md §6.2](../../../../../Refactor.md), [Refactor.md §11.4 S02](../../../../../Refactor.md) |

## B0033

[Lines 337–421](../../../../../tests/unit/storage_model_test.cpp#L337); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void cursor_ownership_and_moves() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Check cursor invalidation, table moves and owning snapshot lifetime. |
| inputs / outputs | No input; tests live/bucket cursors through no-ops, mutations, moves, drop/clear and owner destruction. |
| invariants | Only real mutations invalidate revisions; moved state carries handles/cursors; snapshots keep copied values. |
| ownership | Cursors borrow weak table state; snapshot owns Tuples. |
| failure | Requires invalid_cursor/invalid_storage/foreign_handle in expected places. |
| cost | Three rows, several cursors, one snapshot and invariant scan. |
| Design | tests/unit/storage_model_test.cpp:337-421, docs/storage.md:11-116, docs/tuple_arenas.md:39-139, [Refactor.md §6.2](../../../../../Refactor.md), [Refactor.md §11.4 S02](../../../../../Refactor.md) |

## B0035

[Lines 423–557](../../../../../tests/unit/storage_model_test.cpp#L423); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void randomized_model() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Run a twelve-seed, hundred-step reference-table differential model. |
| inputs / outputs | No input; random insert/erase/key erase/clear/index operations update raw-slot model. |
| invariants | Every step compares rows, handles, index IDs, projections, key sets and buckets; no-op cursor probe stays usable. |
| ownership | Table owns rows; independent maps/sets hold expected values and handles. |
| failure | Mismatch/expected storage errors retain exact carriers. |
| cost | 1200 operations with full snapshot/index/bucket checks per step. |
| Design | tests/unit/storage_model_test.cpp:423-557, docs/storage.md:11-116, docs/tuple_arenas.md:39-139, [Refactor.md §6.2](../../../../../Refactor.md), [Refactor.md §11.4 S02](../../../../../Refactor.md) |

## B0036

[Lines 558–560](../../../../../tests/unit/storage_model_test.cpp#L558); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L558-L560:sha256:9e375a3cb3a2cbe2f9ded9c8296a6ab66848cc826fd71f919246acb17e0bd455
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Close the recorded declaration scopes in storage_model_test.cpp: namespace (anonymous). |
| inputs / outputs | Preceding namespace, type or initializer declarations in; completed lexical boundary out. |
| invariants | Brace-opening context is recorded in root-scope-context-v1.json. These are declaration/initializer boundaries, not an independent update, validation or recovery operation. |
| ownership | Enclosing objects and borrowed fields keep their declared ownership. This punctuation creates no new owner. |
| failure | Malformed scope syntax is a compile error. Any initializer/constructor failure belongs to the enclosing object declaration. |
| cost | No separate loop, guard or engine call is introduced by the delimiter; enclosing initialization and object lifetime still have their actual costs. |
| Design | [tests/unit/storage_model_test.cpp](../../../../../tests/unit/storage_model_test.cpp), [docs/storage.md](../../../../storage.md), [docs/code_review.md](../../../../code_review.md) |

## B0037

[Lines 561–574](../../../../../tests/unit/storage_model_test.cpp#L561); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
int main() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Run reference no-op, layout-token, ID, cursor and randomized checks. |
| inputs / outputs | No input; invokes five finite cases and reports result. |
| invariants | Process requires every direct and randomized assertion. |
| ownership | main owns case sequence. |
| failure | std::exception prints and returns 1. |
| cost | Finite source-defined model only; not executed here. |
| Design | tests/unit/storage_model_test.cpp:561-574, docs/storage.md:11-116, docs/tuple_arenas.md:39-139, [Refactor.md §6.2](../../../../../Refactor.md), [Refactor.md §11.4 S02](../../../../../Refactor.md) |
