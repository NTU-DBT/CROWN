# `tests/unit/indexed_table_model_test.cpp` — block usage map

[Source](../../../../../tests/unit/indexed_table_model_test.cpp) · [Source index](../../../README.md) · [Subsystem contracts](../../../subsystem_contracts.md) · [Reviewed primitives](../../../primitives.md)

Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection.

Snapshot SHA-256: `09522737c24c4e9a52d021603509eb19d63300c04f437591613b70ff12c6beb1`. 756 lines partitioned into 50 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [tests](../../../subsystem_contracts.md#tests). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/code_review.md](../../../../code_review.md), [docs/reference_fuzz.md](../../../../reference_fuzz.md), [docs/task_ledger.md](../../../../task_ledger.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–35](../../../../../tests/unit/indexed_table_model_test.cpp#L1) | Imports dependencies; controls preprocessing; declares namespace scope; declares aliases; declares callable signatures. | source comment (unverified): // Exercise the common InsertResult and shared-owner interfaces. · [reviewed contract](#b0001) |
| [B0002 · 36–38](../../../../../tests/unit/indexed_table_model_test.cpp#L36) | Callable definition: void verify(bool value, std::string_view message) | calls std::runtime_error, std::string · [reviewed contract](#b0002) |
| [B0003 · 39–39](../../../../../tests/unit/indexed_table_model_test.cpp#L39) | Explanatory comments or spacing. |  |
| [B0004 · 40–44](../../../../../tests/unit/indexed_table_model_test.cpp#L40) | Callable definition: IndexWorkAllowance ample() | calls IndexWorkAllowance; returns IndexWorkAllowance(IndexWork{1'000'000'000, 1'000'000'000, · [reviewed contract](#b0004) |
| [B0005 · 45–45](../../../../../tests/unit/indexed_table_model_test.cpp#L45) | Explanatory comments or spacing. |  |
| [B0006 · 46–50](../../../../../tests/unit/indexed_table_model_test.cpp#L46) | Callable definition: template &lt;class Function&gt; decltype(auto) with_work(Function&& function) | calls ample; returns std::forward&lt;Function&gt;(function)(allowance) · [reviewed contract](#b0006) |
| [B0007 · 51–51](../../../../../tests/unit/indexed_table_model_test.cpp#L51) | Explanatory comments or spacing. |  |
| [B0008 · 52–52](../../../../../tests/unit/indexed_table_model_test.cpp#L52) | Type/record definition: enum class Kind : std::uint8_t |  · [reviewed contract](#b0008) |
| [B0009 · 53–53](../../../../../tests/unit/indexed_table_model_test.cpp#L53) | Explanatory comments or spacing. |  |
| [B0010 · 54–59](../../../../../tests/unit/indexed_table_model_test.cpp#L54) | Type/record definition: struct Cell |  · [reviewed contract](#b0010) |
| [B0011 · 60–66](../../../../../tests/unit/indexed_table_model_test.cpp#L60) | declares aliases; declares values/defaults or compile-time conditions. |  · [reviewed contract](#b0011) |
| [B0012 · 67–73](../../../../../tests/unit/indexed_table_model_test.cpp#L67) | Type/record definition: struct RawRow |  · [reviewed contract](#b0012) |
| [B0013 · 74–98](../../../../../tests/unit/indexed_table_model_test.cpp#L74) | declares values/defaults or compile-time conditions. |  · [reviewed contract](#b0013) |
| [B0014 · 99–125](../../../../../tests/unit/indexed_table_model_test.cpp#L99) | Callable definition: RawRow raw_row(std::size_t number) | calls std::string, assign, push_back, std::to_string; returns row; row; growth push_back; source comment (unverified): // Two independently generated pool entries have equal row values. The · [reviewed contract](#b0014) |
| [B0015 · 126–126](../../../../../tests/unit/indexed_table_model_test.cpp#L126) | Explanatory comments or spacing. |  |
| [B0016 · 127–131](../../../../../tests/unit/indexed_table_model_test.cpp#L127) | Callable definition: std::int32_t literal_epoch_days(std::string_view literal) | calls size, std::runtime_error; returns date_epoch_days\[i\]; 1 loop sites · [reviewed contract](#b0016) |
| [B0017 · 132–134](../../../../../tests/unit/indexed_table_model_test.cpp#L132) | Explanatory comments or spacing. | source comment (unverified): // This small decimal formatter is the model's own value canonicalizer. It · [reviewed contract](#b0017) |
| [B0018 · 135–174](../../../../../tests/unit/indexed_table_model_test.cpp#L135) | Callable definition: std::string canonical_decimal(std::string_view literal) | calls empty, front, size, push_back; returns @; negative ? @ + body : body; growth push_back; 2 loop sites; source comment (unverified): // This small decimal formatter is the model's own value canonicalizer. It · [reviewed contract](#b0018) |
| [B0019 · 175–177](../../../../../tests/unit/indexed_table_model_test.cpp#L175) | Explanatory comments or spacing. | source comment (unverified): // The expected cells are generated directly from the raw fixture literals. · [reviewed contract](#b0019) |
| [B0020 · 178–185](../../../../../tests/unit/indexed_table_model_test.cpp#L178) | Callable definition: ModelRow model_row(const RawRow& row) | calls std::to_string, literal_epoch_days, canonical_decimal; returns ModelRow{; source comment (unverified): // The expected cells are generated directly from the raw fixture literals. · [reviewed contract](#b0020) |
| [B0021 · 186–186](../../../../../tests/unit/indexed_table_model_test.cpp#L186) | Explanatory comments or spacing. |  |
| [B0022 · 187–195](../../../../../tests/unit/indexed_table_model_test.cpp#L187) | Callable definition: Tuple native_row(const TupleLayout& layout, const RawRow& raw) | calls emplace_back, Date::parse, Decimal::parse, tuple; returns layout.tuple(std::move(values)); growth emplace_back · [reviewed contract](#b0022) |
| [B0023 · 196–196](../../../../../tests/unit/indexed_table_model_test.cpp#L196) | Explanatory comments or spacing. |  |
| [B0024 · 197–212](../../../../../tests/unit/indexed_table_model_test.cpp#L197) | Callable definition: ModelCell decode_cell(const Value& value) | calls std::visit, constexpr, std::to_string, epoch_days; returns std::visit(\[\](const auto& scalar) -&gt; ModelCell {; {Kind::integer, std::to_string(scalar)} · [reviewed contract](#b0024) |
| [B0025 · 213–213](../../../../../tests/unit/indexed_table_model_test.cpp#L213) | Explanatory comments or spacing. |  |
| [B0026 · 214–219](../../../../../tests/unit/indexed_table_model_test.cpp#L214) | Callable definition: ModelRow decode_tuple(const Tuple& tuple) | calls reserve, values, size, crown::storage::export_row; returns result; growth push_back, reserve; 1 loop sites · [reviewed contract](#b0026) |
| [B0027 · 220–220](../../../../../tests/unit/indexed_table_model_test.cpp#L220) | Explanatory comments or spacing. |  |
| [B0028 · 221–226](../../../../../tests/unit/indexed_table_model_test.cpp#L221) | Callable definition: ModelKey project_model(const ModelRow& row, const std::vector&lt;std::size_t&gt;& fields) | calls reserve, size, push_back, at; returns key; growth push_back, reserve; 1 loop sites · [reviewed contract](#b0028) |
| [B0029 · 227–227](../../../../../tests/unit/indexed_table_model_test.cpp#L227) | Explanatory comments or spacing. |  |
| [B0030 · 228–236](../../../../../tests/unit/indexed_table_model_test.cpp#L228) | Callable definition: Tuple literal_probe(const TupleLayout& target, const Tuple& source, const std::vector&lt;std::size_t&gt;& fields) | calls reserve, size, push_back, crown::storage::export_row; returns target.tuple(std::move(values)); growth push_back, reserve; 1 loop sites; source comment (unverified): // Select the declared source slots directly; this intentionally does not · [reviewed contract](#b0030) |
| [B0031 · 237–237](../../../../../tests/unit/indexed_table_model_test.cpp#L237) | Explanatory comments or spacing. |  |
| [B0032 · 238–241](../../../../../tests/unit/indexed_table_model_test.cpp#L238) | Type/record definition: struct HandlePair |  · [reviewed contract](#b0032) |
| [B0033 · 242–242](../../../../../tests/unit/indexed_table_model_test.cpp#L242) | Explanatory comments or spacing. |  |
| [B0034 · 243–246](../../../../../tests/unit/indexed_table_model_test.cpp#L243) | Type/record definition: struct IndexModel |  · [reviewed contract](#b0034) |
| [B0035 · 247–247](../../../../../tests/unit/indexed_table_model_test.cpp#L247) | Explanatory comments or spacing. |  |
| [B0036 · 248–258](../../../../../tests/unit/indexed_table_model_test.cpp#L248) | Type/record definition: struct ModelState |  · [reviewed contract](#b0036) |
| [B0037 · 259–259](../../../../../tests/unit/indexed_table_model_test.cpp#L259) | Explanatory comments or spacing. |  |
| [B0038 · 260–269](../../../../../tests/unit/indexed_table_model_test.cpp#L260) | Callable definition: void erase_model_row(ModelState& model, TupleNumber id) | calls find, verify, end, erase; growth push_back · [reviewed contract](#b0038) |
| [B0039 · 270–270](../../../../../tests/unit/indexed_table_model_test.cpp#L270) | Explanatory comments or spacing. |  |
| [B0040 · 271–277](../../../../../tests/unit/indexed_table_model_test.cpp#L271) | Callable definition: std::map&lt;ModelKey, std::set&lt;TupleNumber&gt;&gt; model_buckets( const ModelState& model, const std::vector&lt;std::size_t&gt;& fields) | calls project_model, insert; returns result; growth insert; 1 loop sites · [reviewed contract](#b0040) |
| [B0041 · 278–278](../../../../../tests/unit/indexed_table_model_test.cpp#L278) | Explanatory comments or spacing. |  |
| [B0042 · 279–281](../../../../../tests/unit/indexed_table_model_test.cpp#L279) | Callable definition: std::vector&lt;TupleNumber&gt; ids_from_set(const std::set&lt;TupleNumber&gt;& ids) | calls begin, end; returns {ids.begin(), ids.end()} · [reviewed contract](#b0042) |
| [B0043 · 282–282](../../../../../tests/unit/indexed_table_model_test.cpp#L282) | Explanatory comments or spacing. |  |
| [B0044 · 283–295](../../../../../tests/unit/indexed_table_model_test.cpp#L283) | Callable definition: std::vector&lt;TupleNumber&gt; handle_ids(const std::vector&lt;TupleHandle&gt;& handles, StorageOwnerId owner, RelationId relation) | calls reserve, size, verify, push_back; returns result; growth push_back, reserve; 1 loop sites · [reviewed contract](#b0044) |
| [B0045 · 296–296](../../../../../tests/unit/indexed_table_model_test.cpp#L296) | Explanatory comments or spacing. |  |
| [B0046 · 297–307](../../../../../tests/unit/indexed_table_model_test.cpp#L297) | Type/record definition: class DeterministicBits | returns state_ · [reviewed contract](#b0046) |
| [B0047 · 308–308](../../../../../tests/unit/indexed_table_model_test.cpp#L308) | Explanatory comments or spacing. |  |
| [B0048 · 309–742](../../../../../tests/unit/indexed_table_model_test.cpp#L309) | Callable definition: void differential_model() | calls source, reserve, size, verify; guard static_assert(limits.directory_slots &lt;= 65536);; returns std::nullopt; found-&gt;second; growth emplace, emplace_back, insert, push_back, reserve; 19 loop sites; source comment (unverified): // Large scalar payloads deliberately occupy only a small actual node set; · [reviewed contract](#b0048) |
| [B0049 · 743–745](../../../../../tests/unit/indexed_table_model_test.cpp#L743) | Closes surrounding scope/type. | source comment (unverified): // namespace · [reviewed contract](#b0049) |
| [B0050 · 746–756](../../../../../tests/unit/indexed_table_model_test.cpp#L746) | Callable definition: int main() | calls differential_model, defined · [reviewed contract](#b0050) |

## B0001

[Lines 1–35](../../../../../tests/unit/indexed_table_model_test.cpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L1-L35:sha256:a2180b2c2bd40e8bc7db8213fd81ab157c6e4ba7da3f448c8ae3666beb3145f4
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Prepare indexed_table_model_test.cpp: include "crown/storage/indexed.hpp", "crown/storage/reference.hpp", "indexed_testing.hpp", &lt;algorithm&gt;, &lt;array&gt;, &lt;compare&gt;, &lt;cstddef&gt;, &lt;cstdint&gt;, &lt;iterator&gt;, &lt;iostream&gt;, &lt;limits&gt;, &lt;map&gt;, &lt;optional&gt;, &lt;set&gt;, &lt;stdexcept&gt;, &lt;string&gt;, &lt;string_view&gt;, &lt;type_traits&gt;, &lt;utility&gt;, &lt;variant&gt;, &lt;vector&gt;; bind local aliases/name imports; select the recorded test ABI/preprocessor branch. |
| inputs / outputs | Compiler-visible dependencies, names and the recorded declarations in; declarations available to the following fixture/CLI/example definitions out. |
| invariants | Declarations are scoped to this source/header and its selected ABI. Included code has its own effects; names and editable fixture values do not confer proof, admission or publication authority. |
| ownership | Aliases/includes do not create a query owner. Pointers/references/views are non-owning. Containers own their elements, which can themselves be borrowed pointers or numeric IDs. Only documented owning shared-control handles retain controls; IDs/slot-handle values do not independently keep an arena/runtime alive. |
| failure | Missing headers, ill-formed names/types, failed static assertions or active #error directives stop compilation. No runtime rejection/rollback mechanism is implemented by aliases or function prototypes. |
| cost | Preprocessing and type/constraint instantiation cost compilation. Alias/prototype syntax does not invoke the declared operation; any included definitions keep their own initialization effects. |
| Design | [tests/unit/indexed_table_model_test.cpp](../../../../../tests/unit/indexed_table_model_test.cpp), [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/code_review.md](../../../../code_review.md) |

## B0002

[Lines 36–38](../../../../../tests/unit/indexed_table_model_test.cpp#L36); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void verify(bool value, std::string_view message) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Fail a deterministic indexed/reference model assertion. |
| inputs / outputs | Bool/message in; runtime_error when false. |
| invariants | False differential assertion fails the run. |
| ownership | Message borrowed except failure formatting. |
| failure | runtime_error is the harness carrier. |
| cost | One branch. |
| Design | tests/unit/indexed_table_model_test.cpp:36-38, docs/storage.md:11-71, docs/indexed_storage.md:35-89, [Refactor.md §6.2](../../../../../Refactor.md), [Refactor.md §11.4 S04](../../../../../Refactor.md) |

## B0004

[Lines 40–44](../../../../../tests/unit/indexed_table_model_test.cpp#L40); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
IndexWorkAllowance ample() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Return a large five-domain work allowance. |
| inputs / outputs | No input; large fixed IndexWorkAllowance out. |
| invariants | Work grant is logical debit, not allocation/account bytes. |
| ownership | Caller owns returned allowance. |
| failure | Construction errors propagate. |
| cost | Fixed struct and allowance. |
| Design | tests/unit/indexed_table_model_test.cpp:40-44, docs/storage.md:11-71, docs/indexed_storage.md:35-89, [Refactor.md §6.2](../../../../../Refactor.md), [Refactor.md §11.4 S04](../../../../../Refactor.md) |

## B0006

[Lines 46–50](../../../../../tests/unit/indexed_table_model_test.cpp#L46); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
template <class Function>
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Run one function with a fresh ample work allowance. |
| inputs / outputs | Callable in; invokes it with local allowance and returns its exact result category. |
| invariants | Each indexed call gets a fresh explicit grant; this helper does not measure work use. |
| ownership | Allowance local to call; callable forwarded. |
| failure | Callable exceptions propagate. |
| cost | One grant construction and invocation. |
| Design | tests/unit/indexed_table_model_test.cpp:46-50, docs/storage.md:11-71, docs/indexed_storage.md:35-89, [Refactor.md §6.2](../../../../../Refactor.md), [Refactor.md §11.4 S04](../../../../../Refactor.md) |

## B0008

[Lines 52–52](../../../../../tests/unit/indexed_table_model_test.cpp#L52); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
enum class Kind : std::uint8_t { integer, text, boolean, date, decimal };
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Tag the five scalar kinds in independent model cells. |
| inputs / outputs | No input; enum values identify integer/text/bool/date/decimal model categories. |
| invariants | Tags prevent unlike scalar encodings from comparing as equal. |
| ownership | Value-free model metadata. |
| failure | No failure path. |
| cost | Fixed enum. |
| Design | tests/unit/indexed_table_model_test.cpp:52-52, docs/storage.md:11-71, docs/indexed_storage.md:35-89, [Refactor.md §6.2](../../../../../Refactor.md), [Refactor.md §11.4 S04](../../../../../Refactor.md) |

## B0010

[Lines 54–59](../../../../../tests/unit/indexed_table_model_test.cpp#L54); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct Cell {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Represent an independently decoded scalar cell. |
| inputs / outputs | Kind and canonical string payload in; equality and ordering by fields. |
| invariants | Expected cells do not use native Value/Tuple equality as oracle. |
| ownership | Owns payload string. |
| failure | String allocation errors propagate. |
| cost | String compare/copy as used by model. |
| Design | tests/unit/indexed_table_model_test.cpp:54-59, docs/storage.md:11-71, docs/indexed_storage.md:35-89, [Refactor.md §6.2](../../../../../Refactor.md), [Refactor.md §11.4 S04](../../../../../Refactor.md) |

## B0011

[Lines 60–66](../../../../../tests/unit/indexed_table_model_test.cpp#L60); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L60-L66:sha256:1a701a3c24b1ea475f699ae3ead13e64a05805e8a3e89f544483ab242293d746
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Prepare indexed_table_model_test.cpp: bind local aliases/name imports. |
| inputs / outputs | Compiler-visible dependencies, names and the recorded declarations in; declarations available to the following fixture/CLI/example definitions out. |
| invariants | Declarations are scoped to this source/header and its selected ABI. Included code has its own effects; names and editable fixture values do not confer proof, admission or publication authority. |
| ownership | Aliases/includes do not create a query owner. Pointers/references/views are non-owning. Containers own their elements, which can themselves be borrowed pointers or numeric IDs. Only documented owning shared-control handles retain controls; IDs/slot-handle values do not independently keep an arena/runtime alive. |
| failure | Missing headers, ill-formed names/types, failed static assertions or active #error directives stop compilation. No runtime rejection/rollback mechanism is implemented by aliases or function prototypes. |
| cost | Preprocessing and type/constraint instantiation cost compilation. Alias/prototype syntax does not invoke the declared operation; any included definitions keep their own initialization effects. |
| Design | [tests/unit/indexed_table_model_test.cpp](../../../../../tests/unit/indexed_table_model_test.cpp), [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/code_review.md](../../../../code_review.md) |

## B0012

[Lines 67–73](../../../../../tests/unit/indexed_table_model_test.cpp#L67); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct RawRow {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Store unparsed scalar fixture literals. |
| inputs / outputs | Integer, text, bool, date and decimal string fields in; RawRow value out. |
| invariants | Retains raw literals until independent model/native construction. |
| ownership | Owns text/date/decimal strings. |
| failure | String allocation propagates. |
| cost | Fixed five-field record. |
| Design | tests/unit/indexed_table_model_test.cpp:67-73, docs/storage.md:11-71, docs/indexed_storage.md:35-89, [Refactor.md §6.2](../../../../../Refactor.md), [Refactor.md §11.4 S04](../../../../../Refactor.md) |

## B0013

[Lines 74–98](../../../../../tests/unit/indexed_table_model_test.cpp#L74); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L74-L98:sha256:51493ee4b43afd9502b09d5853d566a8847e6b4db2fe59118144a1f6f8ebdc15
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Prepare indexed_table_model_test.cpp: declare constant fixture data. |
| inputs / outputs | Compiler-visible dependencies, names and the recorded declarations in; declarations available to the following fixture/CLI/example definitions out. The source span lists the exact member/global names, types and initial values; initializers run when the enclosing object/program/thread is initialized. |
| invariants | Declarations are scoped to this source/header and its selected ABI. Included code has its own effects; names and editable fixture values do not confer proof, admission or publication authority. |
| ownership | Aliases/includes do not create a query owner. Pointers/references/views are non-owning. Containers own their elements, which can themselves be borrowed pointers or numeric IDs. Only documented owning shared-control handles retain controls; IDs/slot-handle values do not independently keep an arena/runtime alive. |
| failure | Missing headers, ill-formed names/types, failed static assertions or active #error directives stop compilation. No runtime rejection/rollback mechanism is implemented by aliases or function prototypes. |
| cost | Preprocessing and type/constraint instantiation cost compilation. Alias/prototype syntax does not invoke the declared operation; any included definitions keep their own initialization effects. These constexpr data are fixed fixture constants; quota literals are grants, not reserved bytes or measured peaks. |
| Design | [tests/unit/indexed_table_model_test.cpp](../../../../../tests/unit/indexed_table_model_test.cpp), [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/code_review.md](../../../../code_review.md) |

## B0014

[Lines 99–125](../../../../../tests/unit/indexed_table_model_test.cpp#L99); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
RawRow raw_row(std::size_t number) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Generate raw rows including binary, long and duplicate canonical spellings. |
| inputs / outputs | Pool number in; RawRow out from scalar tables and special slots 0..3/30..31. |
| invariants | Special rows include embedded NUL/high bytes, a 1024-character prefix followed by embedded NUL and tail text, equal logical rows and decimal aliases. |
| ownership | Returned strings own fixture bytes. |
| failure | Vector/string allocation propagates; recursive special slots use fixed smaller source slots. |
| cost | One finite raw row; special rows copy one prior fixture. |
| Design | tests/unit/indexed_table_model_test.cpp:99-125, docs/storage.md:11-71, docs/indexed_storage.md:35-89, [Refactor.md §6.2](../../../../../Refactor.md), [Refactor.md §11.4 S04](../../../../../Refactor.md) |

## B0016

[Lines 127–131](../../../../../tests/unit/indexed_table_model_test.cpp#L127); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::int32_t literal_epoch_days(std::string_view literal) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Convert one known literal date through independent epoch-day constants. |
| inputs / outputs | Date string_view in; matching explicit int32 epoch-day value out. |
| invariants | Does not call Date parsing to compute expected value; an unlisted fixture date is an error. |
| ownership | Borrows literal and static constant tables. |
| failure | Throws runtime_error if fixture literal lacks a model constant. |
| cost | Linear scan of six dates. |
| Design | tests/unit/indexed_table_model_test.cpp:127-131, docs/storage.md:11-71, docs/indexed_storage.md:35-89, [Refactor.md §6.2](../../../../../Refactor.md), [Refactor.md §11.4 S04](../../../../../Refactor.md) |

## B0017

[Lines 132–134](../../../../../tests/unit/indexed_table_model_test.cpp#L132); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L132-L134:sha256:5ee315744c426c798a81bd1e62fc3b4df58ce82922ed46d31d468b6e0a928a8a
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Explain the adjacent source contract: This small decimal formatter is the model's own value canonicalizer. It handles the fixture's ordinary base-10 literals without native Decimal APIs. |
| inputs / outputs | Human-readable source note in; no executable output or checked receipt. |
| invariants | This comment states context or a limitation. It does not itself enforce or prove the described behavior; use the adjacent implementation and its scoped contract. |
| ownership | Source text only; no object or resource lifetime is created. |
| failure | No runtime failure path in this comment; source encoding/comment syntax still belongs to compilation. |
| cost | No runtime operations from the comment. Any work described in the note belongs to the adjacent operation. |
| Design | [tests/unit/indexed_table_model_test.cpp](../../../../../tests/unit/indexed_table_model_test.cpp), [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/code_review.md](../../../../code_review.md) |

## B0018

[Lines 135–174](../../../../../tests/unit/indexed_table_model_test.cpp#L135); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::string canonical_decimal(std::string_view literal) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Canonicalize the fixture's ordinary base-ten decimal spellings independently. |
| inputs / outputs | Literal string_view in; sign/digits/scale normalization to canonical string out. |
| invariants | Strips leading/trailing zeros and normalizes zero; this small model formatter is limited to fixture literals and does not call Decimal APIs. |
| ownership | Returns owned string; input borrowed. |
| failure | Allocation failures propagate; malformed unsupported input is not a general parser contract. |
| cost | Linear pass over literal plus output construction. |
| Design | tests/unit/indexed_table_model_test.cpp:135-174, docs/storage.md:11-71, docs/indexed_storage.md:35-89, [Refactor.md §6.2](../../../../../Refactor.md), [Refactor.md §11.4 S04](../../../../../Refactor.md) |

## B0019

[Lines 175–177](../../../../../tests/unit/indexed_table_model_test.cpp#L175); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L175-L177:sha256:33b6f4b64fd01bfdecb0b32fa5265305c746868c3145286abd7696b933c904d3
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Explain the adjacent source contract: The expected cells are generated directly from the raw fixture literals. They never pass through Value equality, hashing, Tuple, or Projection. |
| inputs / outputs | Human-readable source note in; no executable output or checked receipt. |
| invariants | This comment states context or a limitation. It does not itself enforce or prove the described behavior; use the adjacent implementation and its scoped contract. |
| ownership | Source text only; no object or resource lifetime is created. |
| failure | No runtime failure path in this comment; source encoding/comment syntax still belongs to compilation. |
| cost | No runtime operations from the comment. Any work described in the note belongs to the adjacent operation. |
| Design | [tests/unit/indexed_table_model_test.cpp](../../../../../tests/unit/indexed_table_model_test.cpp), [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/code_review.md](../../../../code_review.md) |

## B0020

[Lines 178–185](../../../../../tests/unit/indexed_table_model_test.cpp#L178); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
ModelRow model_row(const RawRow& row) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Build expected model cells directly from raw input. |
| inputs / outputs | RawRow in; ModelRow with integer decimal string, raw text, bool bit, literal epoch days and model-canonical decimal out. |
| invariants | Expected row is derived without native Value equality, Tuple or Projection. |
| ownership | Model owns cell strings. |
| failure | Literal/date-model/allocation failures propagate. |
| cost | Five cell conversions and Row construction; allocator calls are not measured. |
| Design | tests/unit/indexed_table_model_test.cpp:178-185, docs/storage.md:11-71, docs/indexed_storage.md:35-89, [Refactor.md §6.2](../../../../../Refactor.md), [Refactor.md §11.4 S04](../../../../../Refactor.md) |

## B0022

[Lines 187–195](../../../../../tests/unit/indexed_table_model_test.cpp#L187); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Tuple native_row(const TupleLayout& layout, const RawRow& raw) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Convert raw fixture values into a native Tuple. |
| inputs / outputs | TupleLayout and RawRow in; parsed Row/typed Tuple out. |
| invariants | This builds implementation inputs only; expected model path remains separate. |
| ownership | Tuple owns copied/moved scalar payloads. |
| failure | Native Date/Decimal/tuple construction errors propagate. |
| cost | Parses and constructs five cells. |
| Design | tests/unit/indexed_table_model_test.cpp:187-195, docs/storage.md:11-71, docs/indexed_storage.md:35-89, [Refactor.md §6.2](../../../../../Refactor.md), [Refactor.md §11.4 S04](../../../../../Refactor.md) |

## B0024

[Lines 197–212](../../../../../tests/unit/indexed_table_model_test.cpp#L197); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
ModelCell decode_cell(const Value& value) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Decode one native Value into a tagged model cell. |
| inputs / outputs | Value in; visits variant and renders scalar kind/payload out. |
| invariants | Date uses epoch_days and decimal passes through model canonicalizer. |
| ownership | Returned string cell owns contents; Value is borrowed. |
| failure | String/canonicalization failures propagate. |
| cost | One variant visit and possible string conversion. |
| Design | tests/unit/indexed_table_model_test.cpp:197-212, docs/storage.md:11-71, docs/indexed_storage.md:35-89, [Refactor.md §6.2](../../../../../Refactor.md), [Refactor.md §11.4 S04](../../../../../Refactor.md) |

## B0026

[Lines 214–219](../../../../../tests/unit/indexed_table_model_test.cpp#L214); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
ModelRow decode_tuple(const Tuple& tuple) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Decode a native Tuple into independent typed cells. |
| inputs / outputs | Tuple in; exports its row values and decodes every cell into ModelRow. |
| invariants | Used to compare observed values to raw-literal oracle representation. |
| ownership | Returned vector owns decoded cells. |
| failure | Export/copy/conversion failures propagate. |
| cost | Linear in tuple width. |
| Design | tests/unit/indexed_table_model_test.cpp:214-219, docs/storage.md:11-71, docs/indexed_storage.md:35-89, [Refactor.md §6.2](../../../../../Refactor.md), [Refactor.md §11.4 S04](../../../../../Refactor.md) |

## B0028

[Lines 221–226](../../../../../tests/unit/indexed_table_model_test.cpp#L221); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
ModelKey project_model(const ModelRow& row, const std::vector<std::size_t>& fields) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Project an expected model row by explicit source-slot indices. |
| inputs / outputs | ModelRow/field-index vector in; copied ModelKey out. |
| invariants | Uses bounds-checked model fields; no native Projection application. |
| ownership | Returned key owns copied Cells. |
| failure | Out-of-range field throws; allocation propagates. |
| cost | Copies selected fields. |
| Design | tests/unit/indexed_table_model_test.cpp:221-226, docs/storage.md:11-71, docs/indexed_storage.md:35-89, [Refactor.md §6.2](../../../../../Refactor.md), [Refactor.md §11.4 S04](../../../../../Refactor.md) |

## B0030

[Lines 228–236](../../../../../tests/unit/indexed_table_model_test.cpp#L228); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Tuple literal_probe(const TupleLayout& target, const Tuple& source,
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Build a native key probe by direct source-slot selection. |
| inputs / outputs | Target layout, source Tuple and field-index vector in; target Tuple out. |
| invariants | Reads declared slots directly; intentionally bypasses Projection::apply and expected-data derivation. |
| ownership | Returned tuple owns exported selected values. |
| failure | Out-of-range access and tuple construction failures propagate. |
| cost | Exports/copies selected scalar fields. |
| Design | tests/unit/indexed_table_model_test.cpp:228-236, docs/storage.md:11-71, docs/indexed_storage.md:35-89, [Refactor.md §6.2](../../../../../Refactor.md), [Refactor.md §11.4 S04](../../../../../Refactor.md) |

## B0032

[Lines 238–241](../../../../../tests/unit/indexed_table_model_test.cpp#L238); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct HandlePair {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Pair optimized and reference handles for one model ID. |
| inputs / outputs | Two TupleHandles in; HandlePair value out. |
| invariants | Each backend handle is kept separately because owner IDs differ. |
| ownership | Plain test metadata. |
| failure | No custom failure path. |
| cost | Fixed pair. |
| Design | tests/unit/indexed_table_model_test.cpp:238-241, docs/storage.md:11-71, docs/indexed_storage.md:35-89, [Refactor.md §6.2](../../../../../Refactor.md), [Refactor.md §11.4 S04](../../../../../Refactor.md) |

## B0034

[Lines 243–246](../../../../../tests/unit/indexed_table_model_test.cpp#L243); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct IndexModel {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Describe an index program and its literal field map. |
| inputs / outputs | Program index and source field vector in; IndexModel value out. |
| invariants | Field mapping is the model oracle for projection output. |
| ownership | Owns copied field vector. |
| failure | Copy errors propagate. |
| cost | Copies selected field indices. |
| Design | tests/unit/indexed_table_model_test.cpp:243-246, docs/storage.md:11-71, docs/indexed_storage.md:35-89, [Refactor.md §6.2](../../../../../Refactor.md), [Refactor.md §11.4 S04](../../../../../Refactor.md) |

## B0036

[Lines 248–258](../../../../../tests/unit/indexed_table_model_test.cpp#L248); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct ModelState {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Store model ID counters, membership, order, handles and active indexes. |
| inputs / outputs | Default construction; maps IDs to raw-derived rows/handles/index programs and ordered live/stale histories. |
| invariants | next_tuple/index are monotonic model values; value and ID maps/order/index maps are reconciled separately. |
| ownership | Owns all expected rows/maps/vectors; production tables remain separate. |
| failure | Container allocation failures propagate. |
| cost | Storage proportional to the bounded model state. |
| Design | tests/unit/indexed_table_model_test.cpp:248-258, docs/storage.md:11-71, docs/indexed_storage.md:35-89, [Refactor.md §6.2](../../../../../Refactor.md), [Refactor.md §11.4 S04](../../../../../Refactor.md) |

## B0038

[Lines 260–269](../../../../../tests/unit/indexed_table_model_test.cpp#L260); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void erase_model_row(ModelState& model, TupleNumber id) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Remove one model row from value/ID/order state and record stale ID. |
| inputs / outputs | Model and live tuple number in; erases matching maps/order and appends stale history. |
| invariants | Live row must exist in both maps and insertion order before removal. |
| ownership | Mutates only model-owned containers. |
| failure | Missing row/order throws runtime_error. |
| cost | Map operations plus linear search/removal in order vector. |
| Design | tests/unit/indexed_table_model_test.cpp:260-269, docs/storage.md:11-71, docs/indexed_storage.md:35-89, [Refactor.md §6.2](../../../../../Refactor.md), [Refactor.md §11.4 S04](../../../../../Refactor.md) |

## B0040

[Lines 271–277](../../../../../tests/unit/indexed_table_model_test.cpp#L271); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::map<ModelKey, std::set<TupleNumber>> model_buckets(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Derive expected key buckets from current model rows and field mappings. |
| inputs / outputs | Model and selected source fields in; ordered map from model key to set of tuple IDs out. |
| invariants | Key projection is computed by model field copy, not native index state. |
| ownership | Returned map/set structures are independent oracle copies. |
| failure | Container allocation and invalid field errors propagate. |
| cost | Scans every live model row and inserts its projected key/ID. |
| Design | tests/unit/indexed_table_model_test.cpp:271-277, docs/storage.md:11-71, docs/indexed_storage.md:35-89, [Refactor.md §6.2](../../../../../Refactor.md), [Refactor.md §11.4 S04](../../../../../Refactor.md) |

## B0042

[Lines 279–281](../../../../../tests/unit/indexed_table_model_test.cpp#L279); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::vector<TupleNumber> ids_from_set(const std::set<TupleNumber>& ids) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Copy sorted tuple numbers from a model set. |
| inputs / outputs | Set of tuple numbers in; vector out. |
| invariants | Set order gives ascending logical ID expectation. |
| ownership | Returned vector owns IDs; set borrowed. |
| failure | Allocation failure propagates. |
| cost | Copies all set members. |
| Design | tests/unit/indexed_table_model_test.cpp:279-281, docs/storage.md:11-71, docs/indexed_storage.md:35-89, [Refactor.md §6.2](../../../../../Refactor.md), [Refactor.md §11.4 S04](../../../../../Refactor.md) |

## B0044

[Lines 283–295](../../../../../tests/unit/indexed_table_model_test.cpp#L283); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::vector<TupleNumber> handle_ids(const std::vector<TupleHandle>& handles,
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Validate backend owner/relation and monotonic order for bucket handles. |
| inputs / outputs | Handle vector plus expected owner/relation in; ordered tuple-number vector out. |
| invariants | Rejects foreign handles and nonmonotonic logical ID order. |
| ownership | Returned vector copies IDs; handles are borrowed. |
| failure | Mismatch throws runtime_error. |
| cost | Linear scan and vector copy. |
| Design | tests/unit/indexed_table_model_test.cpp:283-295, docs/storage.md:11-71, docs/indexed_storage.md:35-89, [Refactor.md §6.2](../../../../../Refactor.md), [Refactor.md §11.4 S04](../../../../../Refactor.md) |

## B0046

[Lines 297–307](../../../../../tests/unit/indexed_table_model_test.cpp#L297); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
class DeterministicBits {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Generate repeatable operation choices from a fixed xorshift state. |
| inputs / outputs | No input; next() mutates private uint64 state and returns next bits. |
| invariants | Seed and shift sequence are fixed for reproducible tape; no external RNG state. |
| ownership | PRNG owns one scalar state. |
| failure | No custom failure path. |
| cost | Three shifts/xors per draw. |
| Design | tests/unit/indexed_table_model_test.cpp:297-307, docs/storage.md:11-71, docs/indexed_storage.md:35-89, [Refactor.md §6.2](../../../../../Refactor.md), [Refactor.md §11.4 S04](../../../../../Refactor.md) |

## B0048

[Lines 309–742](../../../../../tests/unit/indexed_table_model_test.cpp#L309); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void differential_model() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Run 2000 deterministic operations against ReferenceTable, IndexedTable and raw-literal model. |
| inputs / outputs | No input; builds 32 raw/native/model pool entries and nine projection programs, applies forced setup cases plus seeded inserts/erases/index lifecycle/key erase/clear/find, then compares full observations after every step. |
| invariants | Independent raw model drives expected row/index membership, IDs and order; programs 3/4 share layout tokens but have distinct program identity; checks both backend outputs and all pool probes under whichever collision profile this executable was compiled for, then checks invariants. |
| ownership | ReferenceTable, IndexedTable and model own separate state; native tables own their rows/indexes, the model owns expected vectors/maps, and native probe tuples/observer snapshots are test-owned; each indexed action receives a fresh work allowance. |
| failure | Mismatched model/backend result, owner/token, ID, projection, bucket, or invariant throws runtime_error; native storage/work failures propagate. |
| cost | 2000 operations over at most 32 pool entries/64 live rows, with full snapshot/find/get/index/key/bucket comparison per operation; intentionally substantial test-only oracle work. |
| Design | tests/unit/indexed_table_model_test.cpp:309-742, docs/storage.md:11-71, docs/indexed_storage.md:35-89, [Refactor.md §6.2](../../../../../Refactor.md), [Refactor.md §11.4 S04](../../../../../Refactor.md) |

## B0049

[Lines 743–745](../../../../../tests/unit/indexed_table_model_test.cpp#L743); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L743-L745:sha256:9e375a3cb3a2cbe2f9ded9c8296a6ab66848cc826fd71f919246acb17e0bd455
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Close the recorded declaration scopes in indexed_table_model_test.cpp: namespace (anonymous). |
| inputs / outputs | Preceding namespace, type or initializer declarations in; completed lexical boundary out. |
| invariants | Brace-opening context is recorded in root-scope-context-v1.json. These are declaration/initializer boundaries, not an independent update, validation or recovery operation. |
| ownership | Enclosing objects and borrowed fields keep their declared ownership. This punctuation creates no new owner. |
| failure | Malformed scope syntax is a compile error. Any initializer/constructor failure belongs to the enclosing object declaration. |
| cost | No separate loop, guard or engine call is introduced by the delimiter; enclosing initialization and object lifetime still have their actual costs. |
| Design | [tests/unit/indexed_table_model_test.cpp](../../../../../tests/unit/indexed_table_model_test.cpp), [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/code_review.md](../../../../code_review.md) |

## B0050

[Lines 746–756](../../../../../tests/unit/indexed_table_model_test.cpp#L746); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
int main() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Run the deterministic table model and report the compile-selected hash profile. |
| inputs / outputs | No input; invokes differential_model and prints native/same-bucket/same-full-hash label selected at compile time. |
| invariants | Output describes profile selection, not independently measured performance. |
| ownership | main owns one call sequence. |
| failure | Any fixture/model exception fails the process. |
| cost | One finite 2000-operation model run if executed; not run here. |
| Design | tests/unit/indexed_table_model_test.cpp:746-756, docs/storage.md:11-71, docs/indexed_storage.md:35-89, [Refactor.md §6.2](../../../../../Refactor.md), [Refactor.md §11.4 S04](../../../../../Refactor.md) |
