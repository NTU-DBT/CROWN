# `tests/unit/arena_model_test.cpp` — block usage map

[Source](../../../../../tests/unit/arena_model_test.cpp) · [Source index](../../../README.md) · [Subsystem contracts](../../../subsystem_contracts.md) · [Reviewed primitives](../../../primitives.md)

Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection.

Snapshot SHA-256: `db5c45e1b30911a597164c3de4b517813d102022f2bad9b0df356053f15532df`. 514 lines partitioned into 51 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [tests](../../../subsystem_contracts.md#tests). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/code_review.md](../../../../code_review.md), [docs/reference_fuzz.md](../../../../reference_fuzz.md), [docs/task_ledger.md](../../../../task_ledger.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–22](../../../../../tests/unit/arena_model_test.cpp#L1) | Imports dependencies; declares namespace scope; declares aliases. |  · [reviewed contract](#b0001) |
| [B0002 · 23–25](../../../../../tests/unit/arena_model_test.cpp#L23) | Callable definition: void check(bool condition, const std::string& message) | calls std::runtime_error; guard void check(bool condition, const std::string& message) { · [reviewed contract](#b0002) |
| [B0003 · 26–26](../../../../../tests/unit/arena_model_test.cpp#L26) | Explanatory comments or spacing. |  |
| [B0004 · 27–36](../../../../../tests/unit/arena_model_test.cpp#L27) | Callable definition: template &lt;class Action&gt; void expect_error(Action&& action, std::string_view code) | calls action, check, code, std::runtime_error; guard check(failure.code() == code, "wrong arena error: " + failure.code()); · [reviewed contract](#b0004) |
| [B0005 · 37–37](../../../../../tests/unit/arena_model_test.cpp#L37) | Explanatory comments or spacing. |  |
| [B0006 · 38–43](../../../../../tests/unit/arena_model_test.cpp#L38) | Callable definition: TupleLayout arena_layout(LayoutId id = LayoutId{71}) | calls ; returns TupleLayout{id, · [reviewed contract](#b0006) |
| [B0007 · 44–44](../../../../../tests/unit/arena_model_test.cpp#L44) | Explanatory comments or spacing. |  |
| [B0008 · 45–50](../../../../../tests/unit/arena_model_test.cpp#L45) | Callable definition: Row make_row(std::int64_t integer, std::string text, bool flag, std::string_view day = "2024-02-29", std::string_view amount = "1… | calls std::move, Date::parse, Decimal::parse; returns Row{Value{integer}, Value{std::move(text)}, Value{flag}, · [reviewed contract](#b0008) |
| [B0009 · 51–51](../../../../../tests/unit/arena_model_test.cpp#L51) | Explanatory comments or spacing. |  |
| [B0010 · 52–54](../../../../../tests/unit/arena_model_test.cpp#L52) | Callable definition: std::size_t pick(std::mt19937_64& random, std::size_t bound) | calls random; returns static_cast&lt;std::size_t&gt;(random() % static_cast&lt;std::uint64_t&gt;(bound)) · [reviewed contract](#b0010) |
| [B0011 · 55–55](../../../../../tests/unit/arena_model_test.cpp#L55) | Explanatory comments or spacing. |  |
| [B0012 · 56–69](../../../../../tests/unit/arena_model_test.cpp#L56) | Callable definition: Row random_row(std::mt19937_64& random, std::uint64_t serial) | calls std::string, random, pick, size; returns make_row(integer, std::move(text), (random() & 1U) != 0U, · [reviewed contract](#b0012) |
| [B0013 · 70–70](../../../../../tests/unit/arena_model_test.cpp#L70) | Explanatory comments or spacing. |  |
| [B0014 · 71–116](../../../../../tests/unit/arena_model_test.cpp#L71) | Callable definition: void type_contract_and_stable_addresses() | calls static_assert, reset, arena_layout, check; guard static_assert(!std::is_copy_constructible_v&lt;TupleArena&gt;);; growth insert; 1 loop sites · [reviewed contract](#b0014) |
| [B0015 · 117–117](../../../../../tests/unit/arena_model_test.cpp#L117) | Explanatory comments or spacing. |  |
| [B0016 · 118–147](../../../../../tests/unit/arena_model_test.cpp#L118) | Callable definition: void handle_errors_and_immediate_invalidation() | calls arena_layout, arena, make_row, insert; guard check(!arena.contains(malformed), "malformed same-owner handle is not live");; growth insert; 1 loop sites · [reviewed contract](#b0016) |
| [B0017 · 148–148](../../../../../tests/unit/arena_model_test.cpp#L148) | Explanatory comments or spacing. |  |
| [B0018 · 149–216](../../../../../tests/unit/arena_model_test.cpp#L149) | Callable definition: void pins_retirement_and_clear_generation() | calls arena_layout, arena, make_row, insert; guard check(first_pin.handle() == handle && second_pin.handle() == handle,; growth insert · [reviewed contract](#b0018) |
| [B0019 · 217–217](../../../../../tests/unit/arena_model_test.cpp#L217) | Explanatory comments or spacing. |  |
| [B0020 · 218–290](../../../../../tests/unit/arena_model_test.cpp#L218) | Callable definition: void moves_and_owner_lifetimes() | calls arena_layout, source, insert, tuple; guard check(moved.owner() == source_owner && moved.get(source_handle).values() == source_pin.get().values…; growth emplace, insert · [reviewed contract](#b0020) |
| [B0021 · 291–291](../../../../../tests/unit/arena_model_test.cpp#L291) | Explanatory comments or spacing. |  |
| [B0022 · 292–298](../../../../../tests/unit/arena_model_test.cpp#L292) | Type/record definition: struct ModelSlot |  · [reviewed contract](#b0022) |
| [B0023 · 299–299](../../../../../tests/unit/arena_model_test.cpp#L299) | Explanatory comments or spacing. |  |
| [B0024 · 300–303](../../../../../tests/unit/arena_model_test.cpp#L300) | Type/record definition: struct ModelPin |  · [reviewed contract](#b0024) |
| [B0025 · 304–305](../../../../../tests/unit/arena_model_test.cpp#L304) | declares types or opens a type body. |  · [reviewed contract](#b0025) |
| [B0026 · 306–308](../../../../../tests/unit/arena_model_test.cpp#L306) | Callable definition: public: ArenaModel(const TupleLayout& layout, TupleArena& arena) : layout_(layout), arena_(arena), owner_(arena.owner()) | calls layout_, arena_, owner_, owner · [reviewed contract](#b0026) |
| [B0027 · 309–309](../../../../../tests/unit/arena_model_test.cpp#L309) | Explanatory comments or spacing. |  |
| [B0028 · 310–330](../../../../../tests/unit/arena_model_test.cpp#L310) | Callable definition: ArenaHandle insert(Row row) | calls tuple, check, size, push_back; guard check(handle.owner == owner_, "insert returns this model's owner ID");; returns handle; growth insert, push_back · [reviewed contract](#b0028) |
| [B0029 · 331–331](../../../../../tests/unit/arena_model_test.cpp#L331) | Explanatory comments or spacing. |  |
| [B0030 · 332–338](../../../../../tests/unit/arena_model_test.cpp#L332) | Callable definition: bool erase(ArenaHandle handle) | calls is_live, check; guard check(actual == expected, "erase result matches independent slot/generation model");; returns expected · [reviewed contract](#b0030) |
| [B0031 · 339–339](../../../../../tests/unit/arena_model_test.cpp#L339) | Explanatory comments or spacing. |  |
| [B0032 · 340–343](../../../../../tests/unit/arena_model_test.cpp#L340) | Callable definition: void clear() | calls ; 1 loop sites · [reviewed contract](#b0032) |
| [B0033 · 344–344](../../../../../tests/unit/arena_model_test.cpp#L344) | Explanatory comments or spacing. |  |
| [B0034 · 345–354](../../../../../tests/unit/arena_model_test.cpp#L345) | Callable definition: void add_pin(std::size_t id, ArenaHandle handle) | calls check, is_live, pin, handle; guard check(is_live(handle), "model only adds pins to live handles");; growth emplace · [reviewed contract](#b0034) |
| [B0035 · 355–355](../../../../../tests/unit/arena_model_test.cpp#L355) | Explanatory comments or spacing. |  |
| [B0036 · 356–363](../../../../../tests/unit/arena_model_test.cpp#L356) | Callable definition: void release_pin(std::size_t id) | calls find, check, end, erase; guard check(found != pins_.end(), "selected model pin exists"); · [reviewed contract](#b0036) |
| [B0037 · 364–364](../../../../../tests/unit/arena_model_test.cpp#L364) | Explanatory comments or spacing. |  |
| [B0038 · 365–367](../../../../../tests/unit/arena_model_test.cpp#L365) | Callable definition: \[\[nodiscard\]\] const std::vector&lt;ArenaHandle&gt;& seen_handles() const noexcept | calls ; returns seen_handles_ · [reviewed contract](#b0038) |
| [B0039 · 368–368](../../../../../tests/unit/arena_model_test.cpp#L368) | Callable definition: \[\[nodiscard\]\] const std::map&lt;std::size_t, ModelPin&gt;& pins() const noexcept | calls ; returns pins_ · [reviewed contract](#b0039) |
| [B0040 · 369–375](../../../../../tests/unit/arena_model_test.cpp#L369) | Callable definition: \[\[nodiscard\]\] std::vector&lt;ArenaHandle&gt; live_handles() const | calls is_live, push_back; returns result; growth push_back; 1 loop sites · [reviewed contract](#b0040) |
| [B0041 · 376–383](../../../../../tests/unit/arena_model_test.cpp#L376) | Callable definition: \[\[nodiscard\]\] std::vector&lt;std::size_t&gt; pin_ids() const | calls push_back; returns result; growth push_back; 1 loop sites · [reviewed contract](#b0041) |
| [B0042 · 384–388](../../../../../tests/unit/arena_model_test.cpp#L384) | Callable definition: \[\[nodiscard\]\] bool is_live(ArenaHandle handle) const | calls size; returns handle.owner == owner_ && handle.slot.value &lt; slots_.size() && · [reviewed contract](#b0042) |
| [B0043 · 389–391](../../../../../tests/unit/arena_model_test.cpp#L389) | Callable definition: \[\[nodiscard\]\] const Row& value(ArenaHandle handle) const | calls at; returns slots_.at(handle.slot.value).value · [reviewed contract](#b0043) |
| [B0044 · 392–392](../../../../../tests/unit/arena_model_test.cpp#L392) | Explanatory comments or spacing. |  |
| [B0045 · 393–431](../../../../../tests/unit/arena_model_test.cpp#L393) | Callable definition: void compare(std::string_view where) const | calls check_invariants, check, std::string, size; guard check(slot.known && slot.generation &gt; 0U, std::string(where) + ": model slot metadata exists");; 3 loop sites · [reviewed contract](#b0045) |
| [B0046 · 432–441](../../../../../tests/unit/arena_model_test.cpp#L432) | declares values/defaults or compile-time conditions. |  · [reviewed contract](#b0046) |
| [B0047 · 442–493](../../../../../tests/unit/arena_model_test.cpp#L442) | Callable definition: void churn_seed(std::uint64_t seed) | calls arena_layout, arena, model, random; guard check(!arena.contains(stale), "random stale probe remains absent");; growth insert; 1 loop sites · [reviewed contract](#b0047) |
| [B0048 · 494–494](../../../../../tests/unit/arena_model_test.cpp#L494) | Explanatory comments or spacing. |  |
| [B0049 · 495–499](../../../../../tests/unit/arena_model_test.cpp#L495) | Callable definition: void randomized_independent_model() | calls churn_seed · [reviewed contract](#b0049) |
| [B0050 · 500–501](../../../../../tests/unit/arena_model_test.cpp#L500) | Closes surrounding scope/type. | source comment (unverified): // namespace · [reviewed contract](#b0050) |
| [B0051 · 502–514](../../../../../tests/unit/arena_model_test.cpp#L502) | Callable definition: int main() | calls type_contract_and_stable_addresses, handle_errors_and_immediate_invalidation, pins_retirement_and_clear_generation, moves_and_owner_lifetimes; returns 1 · [reviewed contract](#b0051) |

## B0001

[Lines 1–22](../../../../../tests/unit/arena_model_test.cpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L1-L22:sha256:6f00486235a100a63d0e4e3a8d1aa3bc309dce824d081a51397b46c4f724b023
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Prepare arena_model_test.cpp: include "crown/api/error.hpp", "crown/storage/arena.hpp", &lt;algorithm&gt;, &lt;array&gt;, &lt;cstdint&gt;, &lt;iostream&gt;, &lt;limits&gt;, &lt;map&gt;, &lt;optional&gt;, &lt;random&gt;, &lt;stdexcept&gt;, &lt;string&gt;, &lt;string_view&gt;, &lt;type_traits&gt;, &lt;utility&gt;, &lt;vector&gt;; bind local aliases/name imports. |
| inputs / outputs | Compiler-visible dependencies, names and the recorded declarations in; declarations available to the following fixture/CLI/example definitions out. |
| invariants | Declarations are scoped to this source/header and its selected ABI. Included code has its own effects; names and editable fixture values do not confer proof, admission or publication authority. |
| ownership | Aliases/includes do not create a query owner. Pointers/references/views are non-owning. Containers own their elements, which can themselves be borrowed pointers or numeric IDs. Only documented owning shared-control handles retain controls; IDs/slot-handle values do not independently keep an arena/runtime alive. |
| failure | Missing headers, ill-formed names/types, failed static assertions or active #error directives stop compilation. No runtime rejection/rollback mechanism is implemented by aliases or function prototypes. |
| cost | Preprocessing and type/constraint instantiation cost compilation. Alias/prototype syntax does not invoke the declared operation; any included definitions keep their own initialization effects. |
| Design | [tests/unit/arena_model_test.cpp](../../../../../tests/unit/arena_model_test.cpp), [docs/storage.md](../../../../storage.md), [docs/code_review.md](../../../../code_review.md) |

## B0002

[Lines 23–25](../../../../../tests/unit/arena_model_test.cpp#L23); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void check(bool condition, const std::string& message) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Implement a test assertion with a detailed diagnostic. |
| inputs / outputs | Boolean/message in; returns on true, throws runtime_error on false. |
| invariants | False model comparisons fail the process. |
| ownership | Message borrowed until a failure constructs the exception. |
| failure | runtime_error is the harness carrier. |
| cost | One branch; failure text only on false. |
| Design | tests/unit/arena_model_test.cpp:23-25, docs/tuple_arenas.md:39-118, docs/storage.md:72-116, [Refactor.md §6.2](../../../../../Refactor.md), [Refactor.md §11.4 S03](../../../../../Refactor.md) |

## B0004

[Lines 27–36](../../../../../tests/unit/arena_model_test.cpp#L27); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
template <class Action>
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Require one arena Error code from an operation. |
| inputs / outputs | Action/code in; returns after catching crown::Error with that code. |
| invariants | Wrong or absent Error cannot pass. |
| ownership | Action forwarded; caught Error borrowed during inspection. |
| failure | Wrong/missing expected errors become runtime_error; unrelated exceptions propagate. |
| cost | One operation and exception comparison. |
| Design | tests/unit/arena_model_test.cpp:27-36, docs/tuple_arenas.md:39-118, docs/storage.md:72-116, [Refactor.md §6.2](../../../../../Refactor.md), [Refactor.md §11.4 S03](../../../../../Refactor.md) |

## B0006

[Lines 38–43](../../../../../tests/unit/arena_model_test.cpp#L38); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
TupleLayout arena_layout(LayoutId id = LayoutId{71}) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Create the typed five-field arena model layout. |
| inputs / outputs | Optional LayoutId in; int64/string/bool/date/fixed decimal layout with arena-model context out. |
| invariants | Rows share this descriptor; decimal domain is precision 38, scale 5. |
| ownership | Returned descriptor owns fields. |
| failure | Descriptor construction errors propagate. |
| cost | Fixed five-field fixture construction. |
| Design | tests/unit/arena_model_test.cpp:38-43, docs/tuple_arenas.md:39-118, docs/storage.md:72-116, [Refactor.md §6.2](../../../../../Refactor.md), [Refactor.md §11.4 S03](../../../../../Refactor.md) |

## B0008

[Lines 45–50](../../../../../tests/unit/arena_model_test.cpp#L45); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Row make_row(std::int64_t integer, std::string text, bool flag,
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Create a typed model row from scalar and literal inputs. |
| inputs / outputs | Integer/text/bool/day/decimal strings in; Row with parsed Date and Decimal out. |
| invariants | Native parsing is fixture construction, not the independent expected-value algorithm. |
| ownership | Row owns scalar and text values. |
| failure | Parse/allocation errors propagate. |
| cost | Constructs one five-cell row. |
| Design | tests/unit/arena_model_test.cpp:45-50, docs/tuple_arenas.md:39-118, docs/storage.md:72-116, [Refactor.md §6.2](../../../../../Refactor.md), [Refactor.md §11.4 S03](../../../../../Refactor.md) |

## B0010

[Lines 52–54](../../../../../tests/unit/arena_model_test.cpp#L52); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::size_t pick(std::mt19937_64& random, std::size_t bound) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Select one deterministic slot from the PRNG. |
| inputs / outputs | PRNG reference and nonzero bound in; modulo-selected slot out. |
| invariants | Callers provide a positive bound. |
| ownership | Borrows PRNG for one draw. |
| failure | No custom catch. |
| cost | One PRNG draw and modulo. |
| Design | tests/unit/arena_model_test.cpp:52-54, docs/tuple_arenas.md:39-118, docs/storage.md:72-116, [Refactor.md §6.2](../../../../../Refactor.md), [Refactor.md §11.4 S03](../../../../../Refactor.md) |

## B0012

[Lines 56–69](../../../../../tests/unit/arena_model_test.cpp#L56); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Row random_row(std::mt19937_64& random, std::uint64_t serial) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Generate a seeded mixed-scalar row. |
| inputs / outputs | PRNG/serial in; bounded integer, one of seven strings, four dates and five decimals out. |
| invariants | Includes empty, embedded-NUL and UTF-8 text, boundary dates, decimal aliases. |
| ownership | Returned Row owns text; literal tables are static. |
| failure | Parse/allocation errors propagate. |
| cost | One selection per domain and row construction. |
| Design | tests/unit/arena_model_test.cpp:56-69, docs/tuple_arenas.md:39-118, docs/storage.md:72-116, [Refactor.md §6.2](../../../../../Refactor.md), [Refactor.md §11.4 S03](../../../../../Refactor.md) |

## B0014

[Lines 71–116](../../../../../tests/unit/arena_model_test.cpp#L71); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void type_contract_and_stable_addresses() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Check move/copy traits, layout tokens, owned values and stable addresses. |
| inputs / outputs | No input; inserts a 128 KiB tuple, grows arena by 2048 rows, probes foreign equal descriptor. |
| invariants | Arena/Pin are move-only; layout copies share token, rebuilt descriptors do not; stored tuple address stays fixed. |
| ownership | Arena owns payloads; saved pointer borrows one live tuple. |
| failure | Foreign token must raise layout_mismatch without stats change. |
| cost | One long row, 2048 growth rows and full invariant scan. |
| Design | tests/unit/arena_model_test.cpp:71-116, docs/tuple_arenas.md:39-118, docs/storage.md:72-116, [Refactor.md §6.2](../../../../../Refactor.md), [Refactor.md §11.4 S03](../../../../../Refactor.md) |

## B0016

[Lines 118–147](../../../../../tests/unit/arena_model_test.cpp#L118); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void handle_errors_and_immediate_invalidation() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Check foreign, malformed, erased and repeated arena-handle behavior. |
| inputs / outputs | No input; probes foreign owner, zero generation, out-of-range and stale handles. |
| invariants | Foreign owner differs from same-owner stale identities; erase invalidates membership immediately. |
| ownership | Arena owns one live tuple; handles are nonowning. |
| failure | Requires foreign_handle/stale_handle carriers and harmless false contains/erase. |
| cost | Fixed handle probes and invariant scan. |
| Design | tests/unit/arena_model_test.cpp:118-147, docs/tuple_arenas.md:39-118, docs/storage.md:72-116, [Refactor.md §6.2](../../../../../Refactor.md), [Refactor.md §11.4 S03](../../../../../Refactor.md) |

## B0018

[Lines 149–216](../../../../../tests/unit/arena_model_test.cpp#L149); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void pins_retirement_and_clear_generation() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Check pins, retirement, clear and generation reuse. |
| inputs / outputs | No input; makes two pins, erases, inserts until released, then clears a second arena. |
| invariants | Pins retain values but not membership; last release permits reuse with incremented generation; clear keeps generation history. |
| ownership | Pins retain arena state; ordinary handles do not. |
| failure | Empty Pin access must raise invalid_pin; stale get raises stale_handle. |
| cost | Small row/pin fixture; clear cost follows current live rows. |
| Design | tests/unit/arena_model_test.cpp:149-216, docs/tuple_arenas.md:39-118, docs/storage.md:72-116, [Refactor.md §6.2](../../../../../Refactor.md), [Refactor.md §11.4 S03](../../../../../Refactor.md) |

## B0020

[Lines 218–290](../../../../../tests/unit/arena_model_test.cpp#L218); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void moves_and_owner_lifetimes() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Check arena moves, replacement, self-moves and pins after destruction. |
| inputs / outputs | No input; transfers state, displaces another owner, self-moves and destroys temporary owner. |
| invariants | Moves preserve transferred identity; moved-from state is invalid; pins retain displaced/destroyed payloads. |
| ownership | Pin owns shared state after facade lifetime; raw aliases are test-only. |
| failure | Moved-from operations require invalid_arena; cross-owner handle foreign_handle; empty pin invalid_pin. |
| cost | Fixed lifecycle cases plus final retained payload release. |
| Design | tests/unit/arena_model_test.cpp:218-290, docs/tuple_arenas.md:39-118, docs/storage.md:72-116, [Refactor.md §6.2](../../../../../Refactor.md), [Refactor.md §11.4 S03](../../../../../Refactor.md) |

## B0022

[Lines 292–298](../../../../../tests/unit/arena_model_test.cpp#L292); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct ModelSlot {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Model one arena slot's generation, membership, pin count and row. |
| inputs / outputs | Slot state in; independent record out. |
| invariants | Generation and live/pinned state are represented separately. |
| ownership | Model owns Row value. |
| failure | No custom failure carrier. |
| cost | Value record used only by test model. |
| Design | tests/unit/arena_model_test.cpp:292-298, docs/tuple_arenas.md:39-118, docs/storage.md:72-116, [Refactor.md §6.2](../../../../../Refactor.md), [Refactor.md §11.4 S03](../../../../../Refactor.md) |

## B0024

[Lines 300–303](../../../../../tests/unit/arena_model_test.cpp#L300); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct ModelPin {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Pair one real Pin with its expected ArenaHandle. |
| inputs / outputs | Move-only Pin/handle in; model record out. |
| invariants | Saved handle is the model's pin identity. |
| ownership | Pin owns retained arena state; handle is nonowning. |
| failure | Native Pin move contract applies. |
| cost | One Pin object. |
| Design | tests/unit/arena_model_test.cpp:300-303, docs/tuple_arenas.md:39-118, docs/storage.md:72-116, [Refactor.md §6.2](../../../../../Refactor.md), [Refactor.md §11.4 S03](../../../../../Refactor.md) |

## B0025

[Lines 304–305](../../../../../tests/unit/arena_model_test.cpp#L304); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L304-L305:sha256:4e789741e77d1813fe2315ecf1f9bb6b17af92d1cf2e0b254a92d107f9fda7d2
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Prepare arena_model_test.cpp: open the test/reference type declaration. |
| inputs / outputs | Compiler-visible dependencies, names and the recorded declarations in; declarations available to the following fixture/CLI/example definitions out. |
| invariants | Declarations are scoped to this source/header and its selected ABI. Included code has its own effects; names and editable fixture values do not confer proof, admission or publication authority. |
| ownership | Aliases/includes do not create a query owner. Pointers/references/views are non-owning. Containers own their elements, which can themselves be borrowed pointers or numeric IDs. Only documented owning shared-control handles retain controls; IDs/slot-handle values do not independently keep an arena/runtime alive. |
| failure | Missing headers, ill-formed names/types, failed static assertions or active #error directives stop compilation. No runtime rejection/rollback mechanism is implemented by aliases or function prototypes. |
| cost | Preprocessing and type/constraint instantiation cost compilation. Alias/prototype syntax does not invoke the declared operation; any included definitions keep their own initialization effects. |
| Design | [tests/unit/arena_model_test.cpp](../../../../../tests/unit/arena_model_test.cpp), [docs/storage.md](../../../../storage.md), [docs/code_review.md](../../../../code_review.md) |

## B0026

[Lines 306–308](../../../../../tests/unit/arena_model_test.cpp#L306); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
public:
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Bind an independent arena model to layout, arena and owner. |
| inputs / outputs | Layout/Arena references in; captures arena owner ID. |
| invariants | Model compares handles only against captured owner. |
| ownership | Model borrows caller-owned layout and arena. |
| failure | No custom constructor check. |
| cost | Stores two references and one ID. |
| Design | tests/unit/arena_model_test.cpp:306-308, docs/tuple_arenas.md:39-118, docs/storage.md:72-116, [Refactor.md §6.2](../../../../../Refactor.md), [Refactor.md §11.4 S03](../../../../../Refactor.md) |

## B0028

[Lines 310–330](../../../../../tests/unit/arena_model_test.cpp#L310); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
ArenaHandle insert(Row row) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Insert a row and update independent slot/generation history. |
| inputs / outputs | Row rvalue in; real ArenaHandle out; model slot and handle history updated. |
| invariants | Fresh slot starts at generation 1; reused slot is free/unpinned and generation advances exactly once. |
| ownership | Arena owns tuple; model owns row/history copies. |
| failure | Unexpected slot state becomes runtime_error; native insertion errors propagate. |
| cost | One arena insert plus model/history growth. |
| Design | tests/unit/arena_model_test.cpp:310-330, docs/tuple_arenas.md:39-118, docs/storage.md:72-116, [Refactor.md §6.2](../../../../../Refactor.md), [Refactor.md §11.4 S03](../../../../../Refactor.md) |

## B0030

[Lines 332–338](../../../../../tests/unit/arena_model_test.cpp#L332); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
bool erase(ArenaHandle handle) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Compare erase result with modeled liveness and retire the slot. |
| inputs / outputs | ArenaHandle in; bool out. |
| invariants | Only matching owner/slot/generation is live; stale erase remains false. |
| ownership | Arena retains payload only when pins require it. |
| failure | Model mismatch throws runtime_error. |
| cost | One handle check and model flag update. |
| Design | tests/unit/arena_model_test.cpp:332-338, docs/tuple_arenas.md:39-118, docs/storage.md:72-116, [Refactor.md §6.2](../../../../../Refactor.md), [Refactor.md §11.4 S03](../../../../../Refactor.md) |

## B0032

[Lines 340–343](../../../../../tests/unit/arena_model_test.cpp#L340); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void clear() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Clear arena membership and all modeled live flags. |
| inputs / outputs | No input; real arena clear plus slot loop. |
| invariants | Pin counts and retained values remain modeled after clear. |
| ownership | Arena owns state; model iterates slots. |
| failure | Native clear errors propagate. |
| cost | Linear in model slots plus arena live cleanup. |
| Design | tests/unit/arena_model_test.cpp:340-343, docs/tuple_arenas.md:39-118, docs/storage.md:72-116, [Refactor.md §6.2](../../../../../Refactor.md), [Refactor.md §11.4 S03](../../../../../Refactor.md) |

## B0034

[Lines 345–354](../../../../../tests/unit/arena_model_test.cpp#L345); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void add_pin(std::size_t id, ArenaHandle handle) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Add a unique modeled Pin to a live row. |
| inputs / outputs | Pin ID/live handle in; creates real Pin and updates slot/map model. |
| invariants | Only live rows are accepted; new pin value/handle matches row; IDs are unique. |
| ownership | Map owns moved Pin; arena pin retains payload. |
| failure | Bad model precondition/ID throws runtime_error; native pin errors propagate. |
| cost | One pin and map insertion. |
| Design | tests/unit/arena_model_test.cpp:345-354, docs/tuple_arenas.md:39-118, docs/storage.md:72-116, [Refactor.md §6.2](../../../../../Refactor.md), [Refactor.md §11.4 S03](../../../../../Refactor.md) |

## B0036

[Lines 356–363](../../../../../tests/unit/arena_model_test.cpp#L356); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void release_pin(std::size_t id) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Release a selected modeled Pin. |
| inputs / outputs | Existing pin ID in; decrements slot count and erases stored Pin. |
| invariants | Count cannot underflow; last retired pin release reclaims arena payload. |
| ownership | Destroying map's Pin releases retention. |
| failure | Missing ID/underflow throws runtime_error. |
| cost | One lookup/erase; possibly destroys final payload. |
| Design | tests/unit/arena_model_test.cpp:356-363, docs/tuple_arenas.md:39-118, docs/storage.md:72-116, [Refactor.md §6.2](../../../../../Refactor.md), [Refactor.md §11.4 S03](../../../../../Refactor.md) |

## B0038

[Lines 365–367](../../../../../tests/unit/arena_model_test.cpp#L365); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
[[nodiscard]] const std::vector<ArenaHandle>& seen_handles() const noexcept {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Expose historical handles to the comparison harness. |
| inputs / outputs | No input; const reference to seen_handles. |
| invariants | History includes stale handles and older generations. |
| ownership | Borrowed reference valid with ArenaModel. |
| failure | No failure path. |
| cost | No copy/allocation. |
| Design | tests/unit/arena_model_test.cpp:365-367, docs/tuple_arenas.md:39-118, docs/storage.md:72-116, [Refactor.md §6.2](../../../../../Refactor.md), [Refactor.md §11.4 S03](../../../../../Refactor.md) |

## B0039

[Lines 368–368](../../../../../tests/unit/arena_model_test.cpp#L368); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
[[nodiscard]] const std::map<std::size_t, ModelPin>& pins() const noexcept { return pins_; }
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Expose the current modeled pins. |
| inputs / outputs | No input; const reference to pin map. |
| invariants | Only retained Pin objects remain in map. |
| ownership | Borrowed reference; map owns Pins. |
| failure | No failure path. |
| cost | No copy/allocation. |
| Design | tests/unit/arena_model_test.cpp:368-368, docs/tuple_arenas.md:39-118, docs/storage.md:72-116, [Refactor.md §6.2](../../../../../Refactor.md), [Refactor.md §11.4 S03](../../../../../Refactor.md) |

## B0040

[Lines 369–375](../../../../../tests/unit/arena_model_test.cpp#L369); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
[[nodiscard]] std::vector<ArenaHandle> live_handles() const {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Derive current live handles from history. |
| inputs / outputs | No input; filtered vector of live handles out. |
| invariants | Uses owner, slot range, live flag and exact generation. |
| ownership | Returned vector is test-owned. |
| failure | Vector allocation propagates. |
| cost | Scans all historical handles. |
| Design | tests/unit/arena_model_test.cpp:369-375, docs/tuple_arenas.md:39-118, docs/storage.md:72-116, [Refactor.md §6.2](../../../../../Refactor.md), [Refactor.md §11.4 S03](../../../../../Refactor.md) |

## B0041

[Lines 376–383](../../../../../tests/unit/arena_model_test.cpp#L376); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
[[nodiscard]] std::vector<std::size_t> pin_ids() const {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | List current test pin IDs in map order. |
| inputs / outputs | No input; ordered vector of IDs out. |
| invariants | Every listed ID has one live Pin model record. |
| ownership | Returned vector is copied; Pins remain map-owned. |
| failure | Vector allocation propagates. |
| cost | Linear in current modeled pins. |
| Design | tests/unit/arena_model_test.cpp:376-383, docs/tuple_arenas.md:39-118, docs/storage.md:72-116, [Refactor.md §6.2](../../../../../Refactor.md), [Refactor.md §11.4 S03](../../../../../Refactor.md) |

## B0042

[Lines 384–388](../../../../../tests/unit/arena_model_test.cpp#L384); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
[[nodiscard]] bool is_live(ArenaHandle handle) const {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Answer whether a handle is live in the model. |
| inputs / outputs | ArenaHandle in; bool out. |
| invariants | Foreign, out-of-range, unknown, retired and wrong-generation handles are false. |
| ownership | Reads model metadata only. |
| failure | Malformed handle is harmless. |
| cost | Constant-time slot lookup. |
| Design | tests/unit/arena_model_test.cpp:384-388, docs/tuple_arenas.md:39-118, docs/storage.md:72-116, [Refactor.md §6.2](../../../../../Refactor.md), [Refactor.md §11.4 S03](../../../../../Refactor.md) |

## B0043

[Lines 389–391](../../../../../tests/unit/arena_model_test.cpp#L389); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
[[nodiscard]] const Row& value(ArenaHandle handle) const {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Read the model Row for a valid slot. |
| inputs / outputs | ArenaHandle in; const Row reference out. |
| invariants | Caller supplies an in-range modeled slot. |
| ownership | Borrowed reference into slot model. |
| failure | Out-of-range index propagates from vector::at. |
| cost | One checked lookup. |
| Design | tests/unit/arena_model_test.cpp:389-391, docs/tuple_arenas.md:39-118, docs/storage.md:72-116, [Refactor.md §6.2](../../../../../Refactor.md), [Refactor.md §11.4 S03](../../../../../Refactor.md) |

## B0045

[Lines 393–431](../../../../../tests/unit/arena_model_test.cpp#L393); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void compare(std::string_view where) const {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Reconcile every slot, historical handle, Pin and count. |
| inputs / outputs | Context string in; compares arena invariant, exact statistics, stale/live handles and Pin values. |
| invariants | Slots partition into live/retained/free/exhausted; generations prevent stale aliasing. |
| ownership | Arena/model own state; label borrowed except failure diagnostics. |
| failure | Expected stale_handle is checked; mismatch becomes runtime_error. |
| cost | Scans all slots, historical handles and Pins; diagnostic/test cost. |
| Design | tests/unit/arena_model_test.cpp:393-431, docs/tuple_arenas.md:39-118, docs/storage.md:72-116, [Refactor.md §6.2](../../../../../Refactor.md), [Refactor.md §11.4 S03](../../../../../Refactor.md) |

## B0046

[Lines 432–441](../../../../../tests/unit/arena_model_test.cpp#L432); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L432-L441:sha256:a0cd75dec76148437df653db19373eece77dec7996302c9a524e13eb55002316
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Prepare arena_model_test.cpp: declare fixture state/default initializers. |
| inputs / outputs | Compiler-visible dependencies, names and the recorded declarations in; declarations available to the following fixture/CLI/example definitions out. The source span lists the exact member/global names, types and initial values; initializers run when the enclosing object/program/thread is initialized. |
| invariants | Declarations are scoped to this source/header and its selected ABI. Included code has its own effects; names and editable fixture values do not confer proof, admission or publication authority. |
| ownership | Aliases/includes do not create a query owner. Pointers/references/views are non-owning. Containers own their elements, which can themselves be borrowed pointers or numeric IDs. Only documented owning shared-control handles retain controls; IDs/slot-handle values do not independently keep an arena/runtime alive. |
| failure | Missing headers, ill-formed names/types, failed static assertions or active #error directives stop compilation. No runtime rejection/rollback mechanism is implemented by aliases or function prototypes. Actual object construction and explicit initializers keep the failure contracts of their declared types/called helpers; this card supplies no extra rollback. |
| cost | Preprocessing and type/constraint instantiation cost compilation. Alias/prototype syntax does not invoke the declared operation; any included definitions keep their own initialization effects. Member/global initialization follows the shown C++ types and expressions when its enclosing object/program is constructed; owning containers can allocate. Default member declarations do not themselves instantiate a fixture. Copies and teardown follow the owning types. |
| Design | [tests/unit/arena_model_test.cpp](../../../../../tests/unit/arena_model_test.cpp), [docs/storage.md](../../../../storage.md), [docs/code_review.md](../../../../code_review.md) |

## B0047

[Lines 442–493](../../../../../tests/unit/arena_model_test.cpp#L442); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void churn_seed(std::uint64_t seed) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Run one seeded 650-step arena churn trace. |
| inputs / outputs | Seed in; performs insert/erase/clear/pin/release/stale/malformed probes. |
| invariants | Full model comparison follows every operation. |
| ownership | Owns arena, model, PRNG, histories and Pins for one seed. |
| failure | Expected stale probes check stale_handle; other mismatches fail. |
| cost | Exactly 650 operations with full reconciliation each step. |
| Design | tests/unit/arena_model_test.cpp:442-493, docs/tuple_arenas.md:39-118, docs/storage.md:72-116, [Refactor.md §6.2](../../../../../Refactor.md), [Refactor.md §11.4 S03](../../../../../Refactor.md) |

## B0049

[Lines 495–499](../../../../../tests/unit/arena_model_test.cpp#L495); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void randomized_independent_model() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Run the three fixed-seed arena model traces. |
| inputs / outputs | No input; invokes churn_seed for three literals. |
| invariants | Finite seeds are regression traces, not exhaustive operation schedules. |
| ownership | Each helper owns an independent arena/model. |
| failure | Failures propagate to main. |
| cost | 1950 operations plus full per-step model checks. |
| Design | tests/unit/arena_model_test.cpp:495-499, docs/tuple_arenas.md:39-118, docs/storage.md:72-116, [Refactor.md §6.2](../../../../../Refactor.md), [Refactor.md §11.4 S03](../../../../../Refactor.md) |

## B0050

[Lines 500–501](../../../../../tests/unit/arena_model_test.cpp#L500); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L500-L501:sha256:c2bd7638f09d52cb034ed574f539304035fc6fab162bf8d5fa20a35d8c7288a1
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Close the recorded declaration scopes in arena_model_test.cpp: namespace (anonymous). |
| inputs / outputs | Preceding namespace, type or initializer declarations in; completed lexical boundary out. |
| invariants | Brace-opening context is recorded in root-scope-context-v1.json. These are declaration/initializer boundaries, not an independent update, validation or recovery operation. |
| ownership | Enclosing objects and borrowed fields keep their declared ownership. This punctuation creates no new owner. |
| failure | Malformed scope syntax is a compile error. Any initializer/constructor failure belongs to the enclosing object declaration. |
| cost | No separate loop, guard or engine call is introduced by the delimiter; enclosing initialization and object lifetime still have their actual costs. |
| Design | [tests/unit/arena_model_test.cpp](../../../../../tests/unit/arena_model_test.cpp), [docs/storage.md](../../../../storage.md), [docs/code_review.md](../../../../code_review.md) |

## B0051

[Lines 502–514](../../../../../tests/unit/arena_model_test.cpp#L502); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
int main() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Run arena type, handle, pin, move and randomized-model cases. |
| inputs / outputs | No input; invokes four cases and prints success text. |
| invariants | Process succeeds only if source assertions hold. |
| ownership | main owns sequencing. |
| failure | std::exception prints and returns 1. |
| cost | Finite source-defined cases; no execution claimed. |
| Design | tests/unit/arena_model_test.cpp:502-514, docs/tuple_arenas.md:39-118, docs/storage.md:72-116, [Refactor.md §6.2](../../../../../Refactor.md), [Refactor.md §11.4 S03](../../../../../Refactor.md) |
