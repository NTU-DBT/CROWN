# `tests/unit/physical_backend_options_test.cpp` — block usage map

[Source](../../../../../tests/unit/physical_backend_options_test.cpp) · [Source index](../../../README.md) · [Subsystem contracts](../../../subsystem_contracts.md) · [Reviewed primitives](../../../primitives.md)

Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection.

Snapshot SHA-256: `c98d4596ec2f53cab43e0c32bd402e3aadf5e3e8cdee885cc8235a81c2bc64b2`. 335 lines partitioned into 30 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [tests](../../../subsystem_contracts.md#tests). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/code_review.md](../../../../code_review.md), [docs/reference_fuzz.md](../../../../reference_fuzz.md), [docs/task_ledger.md](../../../../task_ledger.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–18](../../../../../tests/unit/physical_backend_options_test.cpp#L1) | Imports dependencies; declares namespace scope; declares aliases. |  · [reviewed contract](#b0001) |
| [B0002 · 19–21](../../../../../tests/unit/physical_backend_options_test.cpp#L19) | Callable definition: void check(bool condition, const std::string& message) | calls std::runtime_error; guard void check(bool condition, const std::string& message) { · [reviewed contract](#b0002) |
| [B0003 · 22–22](../../../../../tests/unit/physical_backend_options_test.cpp#L22) | Explanatory comments or spacing. |  |
| [B0004 · 23–32](../../../../../tests/unit/physical_backend_options_test.cpp#L23) | Callable definition: void expect_error(std::string_view text, const std::string& message) | calls crown::io::read_physical_options, std::runtime_error, what · [reviewed contract](#b0004) |
| [B0005 · 33–33](../../../../../tests/unit/physical_backend_options_test.cpp#L33) | Explanatory comments or spacing. |  |
| [B0006 · 34–36](../../../../../tests/unit/physical_backend_options_test.cpp#L34) | Callable definition: void expect_error(const std::string& text, const std::string& message) | calls  · [reviewed contract](#b0006) |
| [B0007 · 37–37](../../../../../tests/unit/physical_backend_options_test.cpp#L37) | Explanatory comments or spacing. |  |
| [B0008 · 38–40](../../../../../tests/unit/physical_backend_options_test.cpp#L38) | Callable definition: void expect_error(const Json& value, const std::string& message) | calls dump · [reviewed contract](#b0008) |
| [B0009 · 41–41](../../../../../tests/unit/physical_backend_options_test.cpp#L41) | Explanatory comments or spacing. |  |
| [B0010 · 42–48](../../../../../tests/unit/physical_backend_options_test.cpp#L42) | Callable definition: void replace_once(std::string& text, const std::string& needle, const std::string& replacement) | calls find, check, size, replace; guard check(position != std::string::npos, "cannot find expected JSON fragment: " + needle); · [reviewed contract](#b0010) |
| [B0011 · 49–49](../../../../../tests/unit/physical_backend_options_test.cpp#L49) | Explanatory comments or spacing. |  |
| [B0012 · 50–57](../../../../../tests/unit/physical_backend_options_test.cpp#L50) | Callable definition: Json reference_v1_expected() | calls ; returns Json{{@ , 1}, · [reviewed contract](#b0012) |
| [B0013 · 58–58](../../../../../tests/unit/physical_backend_options_test.cpp#L58) | Explanatory comments or spacing. |  |
| [B0014 · 59–75](../../../../../tests/unit/physical_backend_options_test.cpp#L59) | Callable definition: void reference_options_keep_v1_bytes() | calls check, has_value, reference_v1_expected, crown::io::write_physical_options; guard check(!defaults.indexed_storage.has_value(), "default physical options select no indexed backend");; source comment (unverified): // This is the frozen compact v1 object, with its exact historical defaults. · [reviewed contract](#b0014) |
| [B0015 · 76–84](../../../../../tests/unit/physical_backend_options_test.cpp#L76) | declares callable signatures; declares values/defaults or compile-time conditions. | guard static_assert(sizeof(std::size_t) == sizeof(std::uint64_t), "this boundary test requires a 64-bit s… · [reviewed contract](#b0015) |
| [B0016 · 85–99](../../../../../tests/unit/physical_backend_options_test.cpp#L85) | Callable definition: crown::storage::IndexedBackendSpec indexed_spec() | calls ; returns spec · [reviewed contract](#b0016) |
| [B0017 · 100–100](../../../../../tests/unit/physical_backend_options_test.cpp#L100) | Explanatory comments or spacing. |  |
| [B0018 · 101–108](../../../../../tests/unit/physical_backend_options_test.cpp#L101) | Callable definition: PhysicalOptions indexed_options() | calls indexed_spec; returns options · [reviewed contract](#b0018) |
| [B0019 · 109–109](../../../../../tests/unit/physical_backend_options_test.cpp#L109) | Explanatory comments or spacing. |  |
| [B0020 · 110–138](../../../../../tests/unit/physical_backend_options_test.cpp#L110) | Callable definition: Json indexed_expected() | calls ; returns Json{; source comment (unverified): // Keep this oracle independent of write_physical_options and of the spec encoder. · [reviewed contract](#b0020) |
| [B0021 · 139–139](../../../../../tests/unit/physical_backend_options_test.cpp#L139) | Explanatory comments or spacing. |  |
| [B0022 · 140–165](../../../../../tests/unit/physical_backend_options_test.cpp#L140) | Callable definition: void indexed_options_round_trip_exactly() | calls indexed_options, indexed_expected, dump, crown::io::write_physical_options; guard check(encoded == expected, "indexed options have the full independently specified schema-v2 object"… · [reviewed contract](#b0022) |
| [B0023 · 166–166](../../../../../tests/unit/physical_backend_options_test.cpp#L166) | Explanatory comments or spacing. |  |
| [B0024 · 167–266](../../../../../tests/unit/physical_backend_options_test.cpp#L167) | Callable definition: void strict_schema_rejects_unknown_missing_and_wrong_fields() | calls indexed_expected, expect_error, erase, std::string; 7 loop sites · [reviewed contract](#b0024) |
| [B0025 · 267–267](../../../../../tests/unit/physical_backend_options_test.cpp#L267) | Explanatory comments or spacing. |  |
| [B0026 · 268–308](../../../../../tests/unit/physical_backend_options_test.cpp#L268) | Callable definition: void indexed_numbers_must_be_unsigned_integer_u64_values() | calls indexed_expected, Json, std::string, expect_error; 6 loop sites · [reviewed contract](#b0026) |
| [B0027 · 309–309](../../../../../tests/unit/physical_backend_options_test.cpp#L309) | Explanatory comments or spacing. |  |
| [B0028 · 310–319](../../../../../tests/unit/physical_backend_options_test.cpp#L310) | Callable definition: void duplicate_object_keys_are_rejected() | calls indexed_expected, dump, replace_once, expect_error · [reviewed contract](#b0028) |
| [B0029 · 320–322](../../../../../tests/unit/physical_backend_options_test.cpp#L320) | Closes surrounding scope/type. | source comment (unverified): // namespace · [reviewed contract](#b0029) |
| [B0030 · 323–335](../../../../../tests/unit/physical_backend_options_test.cpp#L323) | Callable definition: int main() | calls reference_options_keep_v1_bytes, indexed_options_round_trip_exactly, strict_schema_rejects_unknown_missing_and_wrong_fields, indexed_numbers_must_be_unsigned_integer_u64_values; returns 1 · [reviewed contract](#b0030) |

## B0001

[Lines 1–18](../../../../../tests/unit/physical_backend_options_test.cpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L1-L18:sha256:79de3bef4de279d7b485433a750928e251c4b5707821843287ef3aac73866227
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Prepare physical_backend_options_test.cpp: include "crown/api/error.hpp", "crown/io/physical.hpp", "crown/ir/physical.hpp", "crown/storage/backend.hpp", &lt;array&gt;, &lt;cstdint&gt;, &lt;functional&gt;, &lt;iostream&gt;, &lt;limits&gt;, &lt;stdexcept&gt;, &lt;string&gt;, &lt;string_view&gt;; bind local aliases/name imports. |
| inputs / outputs | Compiler-visible dependencies, names and the recorded declarations in; declarations available to the following fixture/CLI/example definitions out. |
| invariants | Declarations are scoped to this source/header and its selected ABI. Included code has its own effects; names and editable fixture values do not confer proof, admission or publication authority. |
| ownership | Aliases/includes do not create a query owner. Pointers/references/views are non-owning. Containers own their elements, which can themselves be borrowed pointers or numeric IDs. Only documented owning shared-control handles retain controls; IDs/slot-handle values do not independently keep an arena/runtime alive. |
| failure | Missing headers, ill-formed names/types, failed static assertions or active #error directives stop compilation. No runtime rejection/rollback mechanism is implemented by aliases or function prototypes. |
| cost | Preprocessing and type/constraint instantiation cost compilation. Alias/prototype syntax does not invoke the declared operation; any included definitions keep their own initialization effects. |
| Design | [tests/unit/physical_backend_options_test.cpp](../../../../../tests/unit/physical_backend_options_test.cpp), [docs/physical_runtime.md](../../../../physical_runtime.md), [docs/code_review.md](../../../../code_review.md) |

## B0002

[Lines 19–21](../../../../../tests/unit/physical_backend_options_test.cpp#L19); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void check(bool condition, const std::string& message) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Fail one physical-options codec assertion when false. |
| inputs / outputs | Takes Boolean and borrowed message; returns void. |
| invariants | Does not catch earlier exceptions. |
| ownership | Borrows message and retains no state. |
| failure | False throws std::runtime_error. |
| cost | One branch; exception construction on failure. |
| Design | tests/unit/physical_backend_options_test.cpp:19-21 |

## B0004

[Lines 23–32](../../../../../tests/unit/physical_backend_options_test.cpp#L23); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void expect_error(std::string_view text, const std::string& message) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Require physical-options JSON text to be rejected by read_physical_options. |
| inputs / outputs | Takes borrowed JSON text and label; invokes reader once. |
| invariants | Accepts any crown::Error; does not check CROWN error code. |
| ownership | Text/message are borrowed; no JSON state retained. |
| failure | Non-Crown std::exception is wrapped as runtime_error with what(); no crown::Error also throws runtime_error. |
| cost | One reader call and exception classification. |
| Design | tests/unit/physical_backend_options_test.cpp:23-32, [include/crown/io/physical.hpp](../../../../../include/crown/io/physical.hpp) |

## B0006

[Lines 34–36](../../../../../tests/unit/physical_backend_options_test.cpp#L34); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void expect_error(const std::string& text, const std::string& message) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Forward an owning string invalid-input fixture to the string_view helper. |
| inputs / outputs | Takes two const string references and delegates text as string_view. |
| invariants | Adds no reader call beyond delegated overload. |
| ownership | Strings are borrowed while forwarding. |
| failure | Failure behavior is that of the string_view overload. |
| cost | One forwarding call. |
| Design | tests/unit/physical_backend_options_test.cpp:34-36, [include/crown/io/physical.hpp](../../../../../include/crown/io/physical.hpp) |

## B0008

[Lines 38–40](../../../../../tests/unit/physical_backend_options_test.cpp#L38); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void expect_error(const Json& value, const std::string& message) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Serialize a Json invalid-input fixture before delegating to the text helper. |
| inputs / outputs | Takes borrowed Json/message; calls dump and then the reader through overload chain. |
| invariants | Requires rejection but does not inspect error code. |
| ownership | Json/message are borrowed; dumped string is a call-local temporary. |
| failure | Delegates error classification to string_view overload. |
| cost | One Json dump and one reader invocation. |
| Design | tests/unit/physical_backend_options_test.cpp:38-40, [include/crown/io/physical.hpp](../../../../../include/crown/io/physical.hpp) |

## B0010

[Lines 42–48](../../../../../tests/unit/physical_backend_options_test.cpp#L42); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void replace_once(std::string& text, const std::string& needle, const std::string& replacement) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Replace one unique JSON text fragment for duplicate-key and oversized-number fixtures. |
| inputs / outputs | Takes mutable text and borrowed needle/replacement; changes the sole match in place. |
| invariants | Requires one occurrence and rejects a second, avoiding ambiguous edits. |
| ownership | Mutates caller-owned text; needle/replacement are borrowed. |
| failure | Missing or repeated needle throws std::runtime_error through check. |
| cost | Two find calls and one in-place replace. |
| Design | tests/unit/physical_backend_options_test.cpp:42-48 |

## B0012

[Lines 50–57](../../../../../tests/unit/physical_backend_options_test.cpp#L50); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Json reference_v1_expected() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Construct an independent expected schema-v1 physical-options Json. |
| inputs / outputs | Returns version 1, four policy tags and work/identity_work limits 1,000,000. |
| invariants | Expected object is handwritten, not obtained from encoder under test. |
| ownership | Returns owning Json. |
| failure | No malformed value is constructed; Json failures propagate. |
| cost | One small fixed object construction. |
| Design | tests/unit/physical_backend_options_test.cpp:50-57, [include/crown/io/physical.hpp](../../../../../include/crown/io/physical.hpp), [include/crown/ir/physical.hpp](../../../../../include/crown/ir/physical.hpp) |

## B0014

[Lines 59–75](../../../../../tests/unit/physical_backend_options_test.cpp#L59); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void reference_options_keep_v1_bytes() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Check default schema-v1 options against independent object and frozen compact bytes. |
| inputs / outputs | Encodes defaults, compares with reference object and fixed serialized string, decodes that string, then re-encodes. |
| invariants | Default indexed_storage is absent; decode retains absence and round-trip dump matches exact expected bytes. |
| ownership | Options and Json values are local owning values. |
| failure | Mismatch fails via check; supplied frozen valid JSON is expected to decode. |
| cost | One encode, one decode and one re-encode. |
| Design | tests/unit/physical_backend_options_test.cpp:59-75, [include/crown/io/physical.hpp](../../../../../include/crown/io/physical.hpp), [src/io/physical.cpp](../../../../../src/io/physical.cpp), [include/crown/ir/physical.hpp](../../../../../include/crown/ir/physical.hpp) |

## B0015

[Lines 76–84](../../../../../tests/unit/physical_backend_options_test.cpp#L76); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L76-L84:sha256:0ad03bddb6cfa336f2f4908c9e46a86e64ed5e69786d01ffc9570d55be9294e3
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Prepare physical_backend_options_test.cpp: require 1 compile-time type/ABI conditions; declare constant fixture data. |
| inputs / outputs | Compiler-visible dependencies, names and the recorded declarations in; declarations available to the following fixture/CLI/example definitions out. The source span lists the exact member/global names, types and initial values; initializers run when the enclosing object/program/thread is initialized. |
| invariants | Declarations are scoped to this source/header and its selected ABI. Included code has its own effects; names and editable fixture values do not confer proof, admission or publication authority. Static assertions establish only their listed C++ type properties, not query/result/recovery correctness or test execution. |
| ownership | Aliases/includes do not create a query owner. Pointers/references/views are non-owning. Containers own their elements, which can themselves be borrowed pointers or numeric IDs. Only documented owning shared-control handles retain controls; IDs/slot-handle values do not independently keep an arena/runtime alive. |
| failure | Missing headers, ill-formed names/types, failed static assertions or active #error directives stop compilation. No runtime rejection/rollback mechanism is implemented by aliases or function prototypes. |
| cost | Preprocessing and type/constraint instantiation cost compilation. Alias/prototype syntax does not invoke the declared operation; any included definitions keep their own initialization effects. These constexpr data are fixed fixture constants; quota literals are grants, not reserved bytes or measured peaks. |
| Design | [tests/unit/physical_backend_options_test.cpp](../../../../../tests/unit/physical_backend_options_test.cpp), [docs/physical_runtime.md](../../../../physical_runtime.md), [docs/code_review.md](../../../../code_review.md) |

## B0016

[Lines 85–99](../../../../../tests/unit/physical_backend_options_test.cpp#L85); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
crown::storage::IndexedBackendSpec indexed_spec() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Build fixed indexed-backend configuration records for exact schema-v2 integers. |
| inputs / outputs | Returns nine IndexedLimits fields in declaration order {0, 9007199254740993, size_t max, 9007199254740995, 0, 17, size_t max, 1, 9007199254740999} and five IndexWork fields {u64 max, 9007199254740993, 0, 9007199254740995, u64 max}. |
| invariants | Adjacent source static_assert requires size_t and uint64_t equal size on host; this callable itself returns the fixture. |
| ownership | Returns an IndexedBackendSpec containing fixed IndexedLimits and IndexWork records by value; these fields are not dynamic vectors. |
| failure | No failure is asserted here; cast range relies on stated 64-bit host assertion. |
| cost | Assigns nine size_t limit fields and five uint64_t work fields; no limit/work container allocation is introduced. |
| Design | tests/unit/physical_backend_options_test.cpp:85-99, [include/crown/storage/backend.hpp](../../../../../include/crown/storage/backend.hpp), [include/crown/ir/physical.hpp](../../../../../include/crown/ir/physical.hpp), include/crown/storage/index_work.hpp:14-23 |

## B0018

[Lines 101–108](../../../../../tests/unit/physical_backend_options_test.cpp#L101); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
PhysicalOptions indexed_options() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Build options with indexed spec and non-default producer policy/limits. |
| inputs / outputs | Returns tags exact-nonnull-v1/crown-tree-v77/height-policy-v4/cost-model-v2; work 9007199254740997; identity work 29; indexed_spec(). |
| invariants | These are fixture values; this helper does not encode/validate them. |
| ownership | Returns owning options and nested spec. |
| failure | No failure is asserted by this factory. |
| cost | Assigns four tags, two limits and one spec. |
| Design | tests/unit/physical_backend_options_test.cpp:101-108, [include/crown/ir/physical.hpp](../../../../../include/crown/ir/physical.hpp), [include/crown/storage/backend.hpp](../../../../../include/crown/storage/backend.hpp) |

## B0020

[Lines 110–138](../../../../../tests/unit/physical_backend_options_test.cpp#L110); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Json indexed_expected() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Build independent full JSON oracle for indexed_options schema v2. |
| inputs / outputs | Includes exact policy tags, physical limits, four indexed tags, nine per-table limits and five work fields, including above-2^53 and max values. |
| invariants | Written independently of write_physical_options and spec encoder; exact field/value set is in source body. |
| ownership | Returns owning Json tree. |
| failure | No failure expected while constructing valid oracle. |
| cost | Constructs one fixed nested object with 4 policy fields, 2 physical limits, 4 indexed tags, 9 limits and 5 work counters. |
| Design | tests/unit/physical_backend_options_test.cpp:110-138, [include/crown/io/physical.hpp](../../../../../include/crown/io/physical.hpp), [include/crown/storage/backend.hpp](../../../../../include/crown/storage/backend.hpp), [include/crown/ir/physical.hpp](../../../../../include/crown/ir/physical.hpp) |

## B0022

[Lines 140–165](../../../../../tests/unit/physical_backend_options_test.cpp#L140); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void indexed_options_round_trip_exactly() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Check schema-v2 encoding/decoding against the independent indexed options oracle. |
| inputs / outputs | Compares Json object and canonical dump; decodes expected bytes; compares four policy tags, two physical limits and the two fixed indexed-configuration records; re-encodes. |
| invariants | Selected above-2^53 and maximum values survive; indexed_storage is present. |
| ownership | Local values own their data; actual borrows decoded indexed specification. |
| failure | Mismatch fails through check; valid oracle is expected to decode. |
| cost | One encode/decode/re-encode plus comparisons of four policy strings, two physical limits and the fixed nine-limit/five-work records. Json/string work remains dependent on serialized contents. |
| Design | tests/unit/physical_backend_options_test.cpp:140-165, [include/crown/io/physical.hpp](../../../../../include/crown/io/physical.hpp), [src/io/physical.cpp](../../../../../src/io/physical.cpp), [include/crown/ir/physical.hpp](../../../../../include/crown/ir/physical.hpp), [include/crown/storage/backend.hpp](../../../../../include/crown/storage/backend.hpp), include/crown/storage/index_work.hpp:14-23 |

## B0024

[Lines 167–266](../../../../../tests/unit/physical_backend_options_test.cpp#L167); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void strict_schema_rejects_unknown_missing_and_wrong_fields() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Check selected schema-v2 version, presence, unknown-field and tag rejection cases. |
| inputs / outputs | Mutates valid oracle for version 99, v1 with indexed_storage, missing/null indexed_storage; loops arrays of 4 root, 4 policy, 2 physical-limit, 6 indexed-object, 4 tag, 9 table-limit and 5 work fields; adds one unknown field at each object level. |
| invariants | Missing fields are removed individually. Unknown names and wrong-tag values are explicit in source; helper only requires crown::Error. |
| ownership | Every mutation is a local Json copy. |
| failure | Every listed document must reject; this body checks no exact CROWN error codes. |
| cost | Finite loop bounds are exactly array sizes 4,4,2,6,4,9,5 plus fixed version/null/unknown cases. |
| Design | tests/unit/physical_backend_options_test.cpp:167-266, [include/crown/io/physical.hpp](../../../../../include/crown/io/physical.hpp), [src/io/physical.cpp](../../../../../src/io/physical.cpp) |

## B0026

[Lines 268–308](../../../../../tests/unit/physical_backend_options_test.cpp#L268); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void indexed_numbers_must_be_unsigned_integer_u64_values() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Check selected non-u64 JSON types and numeric overflow for each indexed limit/work field. |
| inputs / outputs | For each of 9 table and 5 operation fields substitutes -1, 1.25, 1.0, false, null and string "1"; then emits decimal 18446744073709551616 for each field via replace_once. |
| invariants | Covers negative, fractional, integral floating representation, Boolean, null and string, plus one above-u64 text; helper requires crown::Error only. |
| ownership | Json/string mutations are local; replace_once changes only serialized overflow fixture. |
| failure | All selected invalid values reject; accepted upper-bound coverage is limited to values present in indexed_expected. |
| cost | Six typed cases and one serialized overflow for each of 14 fields. |
| Design | tests/unit/physical_backend_options_test.cpp:268-308, [include/crown/io/physical.hpp](../../../../../include/crown/io/physical.hpp), [src/io/physical.cpp](../../../../../src/io/physical.cpp) |

## B0028

[Lines 310–319](../../../../../tests/unit/physical_backend_options_test.cpp#L310); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void duplicate_object_keys_are_rejected() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Check rejection of duplicate root and nested indexed-limit keys in JSON text. |
| inputs / outputs | Starts with indexed_expected dump; duplicates schema_version at root and rows in nested indexed_storage.limits. |
| invariants | Only those two duplicate keys are exercised. |
| ownership | Each mutation is a local string, viewed during read. |
| failure | Both documents must throw crown::Error; code is not checked. |
| cost | Two replacements and two reader calls. |
| Design | tests/unit/physical_backend_options_test.cpp:310-319, [include/crown/io/physical.hpp](../../../../../include/crown/io/physical.hpp), [src/io/physical.cpp](../../../../../src/io/physical.cpp) |

## B0029

[Lines 320–322](../../../../../tests/unit/physical_backend_options_test.cpp#L320); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L320-L322:sha256:9e375a3cb3a2cbe2f9ded9c8296a6ab66848cc826fd71f919246acb17e0bd455
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Close the recorded declaration scopes in physical_backend_options_test.cpp: namespace (anonymous). |
| inputs / outputs | Preceding namespace, type or initializer declarations in; completed lexical boundary out. |
| invariants | Brace-opening context is recorded in root-scope-context-v1.json. These are declaration/initializer boundaries, not an independent update, validation or recovery operation. |
| ownership | Enclosing objects and borrowed fields keep their declared ownership. This punctuation creates no new owner. |
| failure | Malformed scope syntax is a compile error. Any initializer/constructor failure belongs to the enclosing object declaration. |
| cost | No separate loop, guard or engine call is introduced by the delimiter; enclosing initialization and object lifetime still have their actual costs. |
| Design | [tests/unit/physical_backend_options_test.cpp](../../../../../tests/unit/physical_backend_options_test.cpp), [docs/physical_runtime.md](../../../../physical_runtime.md), [docs/code_review.md](../../../../code_review.md) |

## B0030

[Lines 323–335](../../../../../tests/unit/physical_backend_options_test.cpp#L323); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
int main() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Provide the backend-options test executable's finite entry sequence. |
| inputs / outputs | Calls the five named codec tests in source order; catches std::exception; prints result and returns 0 or 1. |
| invariants | Accepts no arguments; finite rejection matrix is in called tests. |
| ownership | Fixture state is local to called functions. |
| failure | Escaping std::exception is printed and maps to 1. |
| cost | Five test-function calls; no benchmark. |
| Design | tests/unit/physical_backend_options_test.cpp:323-335, [include/crown/io/physical.hpp](../../../../../include/crown/io/physical.hpp) |
