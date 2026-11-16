# `tests/unit/ingest_test.cpp` — block usage map

[Source](../../../../../tests/unit/ingest_test.cpp) · [Source index](../../../README.md) · [Subsystem contracts](../../../subsystem_contracts.md) · [Reviewed primitives](../../../primitives.md)

Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection.

Snapshot SHA-256: `04bcae7652192350620dec8bb5384c8e8bbd2a473d70c54e7414fffd151aeb2c`. 1257 lines partitioned into 70 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [tests](../../../subsystem_contracts.md#tests). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/code_review.md](../../../../code_review.md), [docs/reference_fuzz.md](../../../../reference_fuzz.md), [docs/task_ledger.md](../../../../task_ledger.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–31](../../../../../tests/unit/ingest_test.cpp#L1) | Imports dependencies; declares namespace scope; declares aliases; declares values/defaults or compile-time conditions. |  · [reviewed contract](#b0001) |
| [B0002 · 32–34](../../../../../tests/unit/ingest_test.cpp#L32) | Callable definition: void check(bool condition, const std::string& message) | calls std::runtime_error; guard void check(bool condition, const std::string& message) { · [reviewed contract](#b0002) |
| [B0003 · 35–35](../../../../../tests/unit/ingest_test.cpp#L35) | Explanatory comments or spacing. |  |
| [B0004 · 36–44](../../../../../tests/unit/ingest_test.cpp#L36) | Callable definition: template &lt;class Action&gt; void rejects(Action&& action, std::string_view label) | calls action, std::runtime_error, std::string · [reviewed contract](#b0004) |
| [B0005 · 45–45](../../../../../tests/unit/ingest_test.cpp#L45) | Explanatory comments or spacing. |  |
| [B0006 · 46–56](../../../../../tests/unit/ingest_test.cpp#L46) | Callable definition: template &lt;class Action&gt; void rejects_code(Action&& action, std::string_view code) | calls action, check, code, std::string; guard check(failure.code() == code, · [reviewed contract](#b0006) |
| [B0007 · 57–57](../../../../../tests/unit/ingest_test.cpp#L57) | Explanatory comments or spacing. |  |
| [B0008 · 58–65](../../../../../tests/unit/ingest_test.cpp#L58) | Callable definition: Catalog typed_catalog() | calls ; returns {41, {{@ , {{@ , ScalarType::int64}, · [reviewed contract](#b0008) |
| [B0009 · 66–66](../../../../../tests/unit/ingest_test.cpp#L66) | Explanatory comments or spacing. |  |
| [B0010 · 67–97](../../../../../tests/unit/ingest_test.cpp#L67) | Callable definition: Catalog fingerprint_catalog() | calls emplace_back, push_back, std::move; returns {73, {std::move(parent), std::move(child)}}; growth emplace_back, push_back · [reviewed contract](#b0010) |
| [B0011 · 98–98](../../../../../tests/unit/ingest_test.cpp#L98) | Explanatory comments or spacing. |  |
| [B0012 · 99–102](../../../../../tests/unit/ingest_test.cpp#L99) | Callable definition: Row typed_row(std::int64_t id, std::string text, bool enabled, Date day, Decimal amount) | calls std::move; returns {id, std::move(text), enabled, day, amount} · [reviewed contract](#b0012) |
| [B0013 · 103–103](../../../../../tests/unit/ingest_test.cpp#L103) | Explanatory comments or spacing. |  |
| [B0014 · 104–110](../../../../../tests/unit/ingest_test.cpp#L104) | Callable definition: InputEvent event(std::uint64_t sequence, Row values, SetOperation operation = SetOperation::insert, std::optional&lt;io::SourcePosit… | calls std::move; returns {PhysicalSetUpdate{sequence, TableId{0}, operation, std::move(values)},; growth insert · [reviewed contract](#b0014) |
| [B0015 · 111–111](../../../../../tests/unit/ingest_test.cpp#L111) | Explanatory comments or spacing. |  |
| [B0016 · 112–118](../../../../../tests/unit/ingest_test.cpp#L112) | Callable definition: std::string json_line(const Catalog& catalog, std::uint64_t sequence, Row values, SetOperation operation = SetOperation::insert, … | calls io::write_input_json, event, std::move; returns io::write_input_json(event(sequence, std::move(values),; growth insert · [reviewed contract](#b0016) |
| [B0017 · 119–119](../../../../../tests/unit/ingest_test.cpp#L119) | Explanatory comments or spacing. |  |
| [B0018 · 120–125](../../../../../tests/unit/ingest_test.cpp#L120) | Callable definition: void append_le(std::string& out, std::uint64_t value, std::size_t bytes) | calls push_back; growth push_back; 1 loop sites · [reviewed contract](#b0018) |
| [B0019 · 126–126](../../../../../tests/unit/ingest_test.cpp#L126) | Explanatory comments or spacing. |  |
| [B0020 · 127–129](../../../../../tests/unit/ingest_test.cpp#L127) | Callable definition: void append_bytes(std::string& out, std::string_view value) | calls append, data, size · [reviewed contract](#b0020) |
| [B0021 · 130–130](../../../../../tests/unit/ingest_test.cpp#L130) | Explanatory comments or spacing. |  |
| [B0022 · 131–136](../../../../../tests/unit/ingest_test.cpp#L131) | Callable definition: void append_string(std::string& out, std::string_view value) | calls check, size, max, append_le; guard check(value.size() &lt;= std::numeric_limits&lt;std::uint32_t&gt;::max(), · [reviewed contract](#b0022) |
| [B0023 · 137–137](../../../../../tests/unit/ingest_test.cpp#L137) | Explanatory comments or spacing. |  |
| [B0024 · 138–155](../../../../../tests/unit/ingest_test.cpp#L138) | Callable definition: void append_binary_value(std::string& out, const Value& value) | calls push_back, append_le, append_string, append_bytes; growth push_back · [reviewed contract](#b0024) |
| [B0025 · 156–156](../../../../../tests/unit/ingest_test.cpp#L156) | Explanatory comments or spacing. |  |
| [B0026 · 157–179](../../../../../tests/unit/ingest_test.cpp#L157) | Callable definition: std::string golden_binary(const InputEvent& input, const Catalog& catalog) | calls append_le, at, append_bytes, io::input_catalog_sha256; returns frame; growth insert, push_back; 1 loop sites · [reviewed contract](#b0026) |
| [B0027 · 180–180](../../../../../tests/unit/ingest_test.cpp#L180) | Explanatory comments or spacing. |  |
| [B0028 · 181–187](../../../../../tests/unit/ingest_test.cpp#L181) | Callable definition: bool same_event(const auto& left, const InputEvent& right) | calls ; returns left.update.sequence == right.update.sequence && · [reviewed contract](#b0028) |
| [B0029 · 188–188](../../../../../tests/unit/ingest_test.cpp#L188) | Explanatory comments or spacing. |  |
| [B0030 · 189–307](../../../../../tests/unit/ingest_test.cpp#L189) | Callable definition: void json_contract_and_typed_scalars() | calls typed_catalog, io::input_catalog_sha256, check, size; guard check(hash.size() == 64 &&; growth insert; 1 loop sites; source comment (unverified): // This is a hand-authored JSONL record. It checks the public spelling and · [reviewed contract](#b0030) |
| [B0031 · 308–308](../../../../../tests/unit/ingest_test.cpp#L308) | Explanatory comments or spacing. |  |
| [B0032 · 309–324](../../../../../tests/unit/ingest_test.cpp#L309) | Callable definition: void catalog_fingerprint_matches_existing_serializer() | calls fingerprint_catalog, io::write_catalog, dump, sha256; guard check(io::input_catalog_sha256(catalog) == expected, · [reviewed contract](#b0032) |
| [B0033 · 325–325](../../../../../tests/unit/ingest_test.cpp#L325) | Explanatory comments or spacing. |  |
| [B0034 · 326–408](../../../../../tests/unit/ingest_test.cpp#L326) | Callable definition: void binary_golden_and_frames() | calls typed_catalog, event, typed_row, min; guard check(encoded == golden,; growth insert · [reviewed contract](#b0034) |
| [B0035 · 409–409](../../../../../tests/unit/ingest_test.cpp#L409) | Explanatory comments or spacing. |  |
| [B0036 · 410–557](../../../../../tests/unit/ingest_test.cpp#L410) | Callable definition: void jsonl_progress_failures_and_limits() | calls typed_catalog, typed_row, Date::parse, Decimal::parse; guard check(first && first == reader.peek() && first-&gt;update.sequence == 41 &&; growth emplace, insert · [reviewed contract](#b0036) |
| [B0037 · 558–558](../../../../../tests/unit/ingest_test.cpp#L558) | Explanatory comments or spacing. |  |
| [B0038 · 559–609](../../../../../tests/unit/ingest_test.cpp#L559) | Callable definition: void jsonl_object_budget_excludes_framing() | calls typed_catalog, typed_row, Date::parse, Decimal::parse; guard check(io::write_input_json(input_event, catalog, exact.limits) == object &&; 1 loop sites · [reviewed contract](#b0038) |
| [B0039 · 610–610](../../../../../tests/unit/ingest_test.cpp#L610) | Explanatory comments or spacing. |  |
| [B0040 · 611–689](../../../../../tests/unit/ingest_test.cpp#L611) | Callable definition: void nondefault_options_are_format_scoped() | calls typed_catalog, void, emplace, configure; guard check(relations_accept_map.peek() == nullptr,; returns options; growth emplace; 4 loop sites · [reviewed contract](#b0040) |
| [B0041 · 690–690](../../../../../tests/unit/ingest_test.cpp#L690) | Explanatory comments or spacing. |  |
| [B0042 · 691–752](../../../../../tests/unit/ingest_test.cpp#L691) | Callable definition: void timestamp_flag_legacy_profile() | calls typed_catalog, typed_row, Date::parse, Decimal::parse; guard check(first && first-&gt;update.sequence == 1 &&; growth insert; 1 loop sites · [reviewed contract](#b0042) |
| [B0043 · 753–753](../../../../../tests/unit/ingest_test.cpp#L753) | Explanatory comments or spacing. |  |
| [B0044 · 754–925](../../../../../tests/unit/ingest_test.cpp#L754) | Callable definition: void csv_and_legacy_profiles() | calls typed_catalog, csv_stream, csv_reader, peek; guard check(csv_first && csv_first-&gt;update.sequence == 21 &&; growth emplace, insert; 1 loop sites · [reviewed contract](#b0044) |
| [B0045 · 926–926](../../../../../tests/unit/ingest_test.cpp#L926) | Explanatory comments or spacing. |  |
| [B0046 · 927–945](../../../../../tests/unit/ingest_test.cpp#L927) | Callable definition: PhysicalPlan edge_self_join_plan() | calls planner::lower_tree; returns planner::lower_tree(catalog, query, tree) · [reviewed contract](#b0046) |
| [B0047 · 946–946](../../../../../tests/unit/ingest_test.cpp#L946) | Explanatory comments or spacing. |  |
| [B0048 · 947–949](../../../../../tests/unit/ingest_test.cpp#L947) | Callable definition: Row edge(std::int64_t x, std::int64_t y, std::string payload) | calls std::move; returns {x, y, std::move(payload)} · [reviewed contract](#b0048) |
| [B0049 · 950–950](../../../../../tests/unit/ingest_test.cpp#L950) | Explanatory comments or spacing. |  |
| [B0050 · 951–956](../../../../../tests/unit/ingest_test.cpp#L951) | Callable definition: std::string edge_json_line(const Catalog& catalog, std::uint64_t sequence, SetOperation operation, Row values) | calls io::write_input_json, std::move; returns io::write_input_json( · [reviewed contract](#b0050) |
| [B0051 · 957–957](../../../../../tests/unit/ingest_test.cpp#L957) | Explanatory comments or spacing. |  |
| [B0052 · 958–963](../../../../../tests/unit/ingest_test.cpp#L958) | Callable definition: std::vector&lt;Row&gt; replay_rows() | calls edge; returns {edge(1, 2, @ ), edge(2, 3, @ ), · [reviewed contract](#b0052) |
| [B0053 · 964–964](../../../../../tests/unit/ingest_test.cpp#L964) | Explanatory comments or spacing. |  |
| [B0054 · 965–969](../../../../../tests/unit/ingest_test.cpp#L965) | Callable definition: std::vector&lt;SetOperation&gt; replay_operations() | calls ; returns {SetOperation::insert, SetOperation::insert, SetOperation::insert,; growth insert · [reviewed contract](#b0054) |
| [B0055 · 970–970](../../../../../tests/unit/ingest_test.cpp#L970) | Explanatory comments or spacing. |  |
| [B0056 · 971–980](../../../../../tests/unit/ingest_test.cpp#L971) | Callable definition: std::string replay_stream(const Catalog& catalog) | calls replay_rows, replay_operations, size, edge_json_line; returns contents; growth push_back; 1 loop sites · [reviewed contract](#b0056) |
| [B0057 · 981–981](../../../../../tests/unit/ingest_test.cpp#L981) | Explanatory comments or spacing. |  |
| [B0058 · 982–1054](../../../../../tests/unit/ingest_test.cpp#L982) | Callable definition: void physical_replay_preserves_source_rows_and_counts() | calls edge_self_join_plan, catalog, replay_rows, replay_operations; guard check(next && next-&gt;update.sequence == i + 1 &&; growth insert, resize; 1 loop sites · [reviewed contract](#b0058) |
| [B0059 · 1055–1055](../../../../../tests/unit/ingest_test.cpp#L1055) | Explanatory comments or spacing. |  |
| [B0060 · 1056–1064](../../../../../tests/unit/ingest_test.cpp#L1056) | Callable definition: std::set&lt;SignedRow&gt; expected_delta(const Relation& before, const Relation& after) | calls contains, emplace; returns result; growth emplace, insert; 2 loop sites · [reviewed contract](#b0060) |
| [B0061 · 1065–1065](../../../../../tests/unit/ingest_test.cpp#L1065) | Explanatory comments or spacing. |  |
| [B0062 · 1066–1075](../../../../../tests/unit/ingest_test.cpp#L1066) | Callable definition: std::set&lt;SignedRow&gt; drain_delta(DeltaRuntime::Epoch& epoch) | calls next, check, emplace, crown::storage::export_row; guard check(result.emplace(record-&gt;operation, crown::storage::export_row(record-&gt;tuple.values())).second,; returns result; growth emplace; 1 loop sites · [reviewed contract](#b0062) |
| [B0063 · 1076–1076](../../../../../tests/unit/ingest_test.cpp#L1076) | Explanatory comments or spacing. |  |
| [B0064 · 1077–1083](../../../../../tests/unit/ingest_test.cpp#L1077) | Callable definition: DeltaOptions ordered_delta_options() | calls ; returns options · [reviewed contract](#b0064) |
| [B0065 · 1084–1084](../../../../../tests/unit/ingest_test.cpp#L1084) | Explanatory comments or spacing. |  |
| [B0066 · 1085–1121](../../../../../tests/unit/ingest_test.cpp#L1085) | Callable definition: void ordered_delta_replay_matches_a04() | calls edge_self_join_plan, catalog, replay_rows, replay_operations; guard check(epoch && epoch-&gt;sequence() == i + 1 &&; growth insert, resize; 1 loop sites · [reviewed contract](#b0066) |
| [B0067 · 1122–1122](../../../../../tests/unit/ingest_test.cpp#L1122) | Explanatory comments or spacing. |  |
| [B0068 · 1123–1234](../../../../../tests/unit/ingest_test.cpp#L1123) | Callable definition: void replay_retry_busy_owner_and_later_malformed_record() | calls edge_self_join_plan, catalog, edge, retry_stream; guard check(cached != nullptr, "retry fixture has one pending source record");; growth insert; source comment (unverified): // A prepared physical epoch holds the target runtime busy. The exact cached · [reviewed contract](#b0068) |
| [B0069 · 1235–1237](../../../../../tests/unit/ingest_test.cpp#L1235) | Closes surrounding scope/type. | source comment (unverified): // namespace · [reviewed contract](#b0069) |
| [B0070 · 1238–1257](../../../../../tests/unit/ingest_test.cpp#L1238) | Callable definition: int main() | calls json_contract_and_typed_scalars, catalog_fingerprint_matches_existing_serializer, binary_golden_and_frames, jsonl_progress_failures_and_limits; returns 0; 1 · [reviewed contract](#b0070) |

## B0001

[Lines 1–31](../../../../../tests/unit/ingest_test.cpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L1-L31:sha256:7af83341eb906b7907f8f2455778255fe6bb926b6879dd5a957bfe264b5d673d
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Prepare ingest_test.cpp: include "crown/api/error.hpp", "crown/io/catalog.hpp", "crown/io/ingest.hpp", "crown/ir/digest.hpp", "crown/planner/lower.hpp", "crown/runtime/delta.hpp", "crown/runtime/replay.hpp", "evaluator.hpp", &lt;cstdint&gt;, &lt;functional&gt;, &lt;iostream&gt;, &lt;limits&gt;, &lt;set&gt;, &lt;sstream&gt;, &lt;stdexcept&gt;, &lt;string&gt;, &lt;string_view&gt;, &lt;utility&gt;, &lt;vector&gt;; bind local aliases/name imports. |
| inputs / outputs | Compiler-visible dependencies, names and the recorded declarations in; declarations available to the following fixture/CLI/example definitions out. |
| invariants | Declarations are scoped to this source/header and its selected ABI. Included code has its own effects; names and editable fixture values do not confer proof, admission or publication authority. |
| ownership | Aliases/includes do not create a query owner. Pointers/references/views are non-owning. Containers own their elements, which can themselves be borrowed pointers or numeric IDs. Only documented owning shared-control handles retain controls; IDs/slot-handle values do not independently keep an arena/runtime alive. |
| failure | Missing headers, ill-formed names/types, failed static assertions or active #error directives stop compilation. No runtime rejection/rollback mechanism is implemented by aliases or function prototypes. |
| cost | Preprocessing and type/constraint instantiation cost compilation. Alias/prototype syntax does not invoke the declared operation; any included definitions keep their own initialization effects. |
| Design | [tests/unit/ingest_test.cpp](../../../../../tests/unit/ingest_test.cpp), [docs/ingestion.md](../../../../ingestion.md), [docs/code_review.md](../../../../code_review.md) |

## B0002

[Lines 32–34](../../../../../tests/unit/ingest_test.cpp#L32); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void check(bool condition, const std::string& message)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Turn one unit-test predicate into a descriptive assertion failure. |
| inputs / outputs | Callable: void check(bool condition, const std::string& message). Inputs: Boolean condition and message. Output: None on success. |
| invariants | A false condition throws std::runtime_error. |
| ownership | Fixture values and runtime objects are local to this call unless returned by value; borrowed references and views remain subject to their declared owners. No test result survives the function. |
| failure | A failed check throws std::runtime_error; expected API rejection is caught only where rejects or rejects_code is called. Other exceptions propagate to main's std::exception handler. |
| cost | Work is the finite encoding, decoding, row replay or assertion work in this fixture. It is not a benchmark and does not establish an asymptotic or CPU-time bound for production. |
| Design | [include/crown/io/ingest.hpp](../../../../../include/crown/io/ingest.hpp), [src/io/ingest.cpp](../../../../../src/io/ingest.cpp), [src/io/event_reader.cpp](../../../../../src/io/event_reader.cpp), [docs/ingestion.md § Version-1 binary frame](../../../../ingestion.md) |

## B0004

[Lines 36–44](../../../../../tests/unit/ingest_test.cpp#L36); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
template <class Action>
void rejects(Action&& action, std::string_view label)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Require an action to throw a CROWN Error, without checking its code. |
| inputs / outputs | Callable: template &lt;class Action&gt; void rejects(Action&& action, std::string_view label). Inputs: forwarded action and case label. Output: None when crown::Error is caught. |
| invariants | Other exception types propagate; no error means the helper throws std::runtime_error. |
| ownership | Fixture values and runtime objects are local to this call unless returned by value; borrowed references and views remain subject to their declared owners. No test result survives the function. |
| failure | Catches only crown::Error; std::runtime_error from the action or any other exception type propagates. |
| cost | Work is the finite encoding, decoding, row replay or assertion work in this fixture. It is not a benchmark and does not establish an asymptotic or CPU-time bound for production. |
| Design | [include/crown/io/ingest.hpp](../../../../../include/crown/io/ingest.hpp), [src/io/ingest.cpp](../../../../../src/io/ingest.cpp), [src/io/event_reader.cpp](../../../../../src/io/event_reader.cpp), [docs/ingestion.md § Version-1 binary frame](../../../../ingestion.md) |

## B0006

[Lines 46–56](../../../../../tests/unit/ingest_test.cpp#L46); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
template <class Action>
void rejects_code(Action&& action, std::string_view code)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Require a CROWN Error carrying one exact error code. |
| inputs / outputs | Callable: template &lt;class Action&gt; void rejects_code(Action&& action, std::string_view code). Inputs: forwarded action and expected code. Output: None on exact match. |
| invariants | A wrong code or no CROWN Error becomes std::runtime_error. |
| ownership | Fixture values and runtime objects are local to this call unless returned by value; borrowed references and views remain subject to their declared owners. No test result survives the function. |
| failure | Catches crown::Error and checks its exact code; other exceptions propagate and an absent expected error throws std::runtime_error. |
| cost | Work is the finite encoding, decoding, row replay or assertion work in this fixture. It is not a benchmark and does not establish an asymptotic or CPU-time bound for production. |
| Design | [include/crown/io/ingest.hpp](../../../../../include/crown/io/ingest.hpp), [src/io/ingest.cpp](../../../../../src/io/ingest.cpp), [src/io/event_reader.cpp](../../../../../src/io/event_reader.cpp), [docs/ingestion.md § Version-1 binary frame](../../../../ingestion.md) |

## B0008

[Lines 58–65](../../../../../tests/unit/ingest_test.cpp#L58); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Catalog typed_catalog()
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Build a one-table catalog containing int64, string, bool, date and decimal columns. |
| inputs / outputs | Callable: Catalog typed_catalog(). Input: none. Output: catalog version 41 with source schema version 7. |
| invariants | Catalog version is 41, table source schema version is 7, and row order follows id/text/enabled/day/amount. |
| ownership | Returns a catalog value; nested table and column metadata are owned by that value. |
| failure | A failed check throws std::runtime_error; expected API rejection is caught only where rejects or rejects_code is called. Other exceptions propagate to main's std::exception handler. |
| cost | Work is the finite encoding, decoding, row replay or assertion work in this fixture. It is not a benchmark and does not establish an asymptotic or CPU-time bound for production. |
| Design | [include/crown/io/ingest.hpp](../../../../../include/crown/io/ingest.hpp), [src/io/ingest.cpp](../../../../../src/io/ingest.cpp), [docs/ingestion.md § Version-1 JSONL event](../../../../ingestion.md), [docs/catalog.md § Validation and canonical writing](../../../../catalog.md) |

## B0010

[Lines 67–97](../../../../../tests/unit/ingest_test.cpp#L67); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Catalog fingerprint_catalog()
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Build a two-table catalog covering escaped Unicode metadata and catalog features. |
| inputs / outputs | Callable: Catalog fingerprint_catalog(). Input: none. Output: catalog with nullable columns, fixed decimal, keys, FK, stats and hints. |
| invariants | The fixture includes escaped quotes, backslashes, newlines, Unicode, nullability, decimal bounds, key constraints, stats and hints. |
| ownership | Builds catalog/table/constraint vectors by value and transfers the parent/child tables into the returned catalog. |
| failure | A failed check throws std::runtime_error; expected API rejection is caught only where rejects or rejects_code is called. Other exceptions propagate to main's std::exception handler. |
| cost | Work is the finite encoding, decoding, row replay or assertion work in this fixture. It is not a benchmark and does not establish an asymptotic or CPU-time bound for production. |
| Design | [include/crown/io/ingest.hpp](../../../../../include/crown/io/ingest.hpp), [src/io/ingest.cpp](../../../../../src/io/ingest.cpp), [src/io/event_reader.cpp](../../../../../src/io/event_reader.cpp), [docs/ingestion.md § Version-1 binary frame](../../../../ingestion.md) |

## B0012

[Lines 99–102](../../../../../tests/unit/ingest_test.cpp#L99); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Row typed_row(std::int64_t id, std::string text, bool enabled, Date day,
              Decimal amount)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Assemble a physical row in the typed catalog's column order. |
| inputs / outputs | Callable: Row typed_row(std::int64_t id, std::string text, bool enabled, Date day, Decimal amount). Inputs: id, owned text, Boolean, Date and Decimal. Output: Row. |
| invariants | The returned cells stay in typed_catalog column order; text ownership is transferred with std::move. |
| ownership | Returns a Row; the string parameter is moved into that row. |
| failure | A failed check throws std::runtime_error; expected API rejection is caught only where rejects or rejects_code is called. Other exceptions propagate to main's std::exception handler. |
| cost | Work is the finite encoding, decoding, row replay or assertion work in this fixture. It is not a benchmark and does not establish an asymptotic or CPU-time bound for production. |
| Design | [include/crown/io/ingest.hpp](../../../../../include/crown/io/ingest.hpp), [src/io/ingest.cpp](../../../../../src/io/ingest.cpp), [docs/ingestion.md § Version-1 JSONL event](../../../../ingestion.md), [docs/catalog.md § Validation and canonical writing](../../../../catalog.md) |

## B0014

[Lines 104–110](../../../../../tests/unit/ingest_test.cpp#L104); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
InputEvent event(std::uint64_t sequence,
                 Row values,
                 SetOperation operation = SetOperation::insert,
                 std::optional<io::SourcePosition> position = std::nullopt)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Build a physical insert/delete event for table zero with optional source position. |
| inputs / outputs | Callable: InputEvent event(std::uint64_t sequence, Row values, SetOperation operation = SetOperation::insert, std::optional&lt;io::SourcePosition&gt; position = std::nullopt). Inputs: sequence, row, operation and optional position. Output: InputEvent. |
| invariants | Every event targets TableId{0}; sequence, operation, full values and optional source position are retained. |
| ownership | Moves the supplied row and optional source position into the returned InputEvent. |
| failure | A failed check throws std::runtime_error; expected API rejection is caught only where rejects or rejects_code is called. Other exceptions propagate to main's std::exception handler. |
| cost | Work is the finite encoding, decoding, row replay or assertion work in this fixture. It is not a benchmark and does not establish an asymptotic or CPU-time bound for production. |
| Design | [include/crown/io/ingest.hpp](../../../../../include/crown/io/ingest.hpp), [src/io/ingest.cpp](../../../../../src/io/ingest.cpp), [docs/ingestion.md § Version-1 JSONL event](../../../../ingestion.md), [docs/catalog.md § Validation and canonical writing](../../../../catalog.md) |

## B0016

[Lines 112–118](../../../../../tests/unit/ingest_test.cpp#L112); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::string json_line(const Catalog& catalog, std::uint64_t sequence,
                      Row values,
                      SetOperation operation = SetOperation::insert,
                      std::optional<io::SourcePosition> position = std::nullopt)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Serialize one event through the production input JSON writer. |
| inputs / outputs | Callable: std::string json_line(const Catalog& catalog, std::uint64_t sequence, Row values, SetOperation operation = SetOperation::insert, std::optional&lt;io::SourcePosition&gt; position = std::…. Inputs: catalog, sequence, row, operation and optional position. Output: JSON text. |
| invariants | Production JSON writer receives the same table-zero event assembled by event; no custom JSON serialization is used here. |
| ownership | Returns the string produced by the public writer; the temporary event and its values expire after the call. |
| failure | A failed check throws std::runtime_error; expected API rejection is caught only where rejects or rejects_code is called. Other exceptions propagate to main's std::exception handler. |
| cost | Work is the finite encoding, decoding, row replay or assertion work in this fixture. It is not a benchmark and does not establish an asymptotic or CPU-time bound for production. |
| Design | [include/crown/io/ingest.hpp](../../../../../include/crown/io/ingest.hpp), [src/io/ingest.cpp](../../../../../src/io/ingest.cpp), [docs/ingestion.md § Version-1 JSONL event](../../../../ingestion.md), [docs/catalog.md § Validation and canonical writing](../../../../catalog.md) |

## B0018

[Lines 120–125](../../../../../tests/unit/ingest_test.cpp#L120); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void append_le(std::string& out, std::uint64_t value, std::size_t bytes)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Append the low requested bytes of an integer in little-endian order. |
| inputs / outputs | Callable: void append_le(std::string& out, std::uint64_t value, std::size_t bytes). Inputs: destination string, integer and byte count. Output: destination mutated in place. |
| invariants | Exactly bytes low-order bytes are appended little-endian; callers supply a width appropriate to the field. |
| ownership | Mutates caller-owned destination bytes; it retains no reference to the integer. |
| failure | A failed check throws std::runtime_error; expected API rejection is caught only where rejects or rejects_code is called. Other exceptions propagate to main's std::exception handler. |
| cost | Work is the finite encoding, decoding, row replay or assertion work in this fixture. It is not a benchmark and does not establish an asymptotic or CPU-time bound for production. |
| Design | [include/crown/io/ingest.hpp](../../../../../include/crown/io/ingest.hpp), [src/io/ingest.cpp](../../../../../src/io/ingest.cpp), [src/io/event_reader.cpp](../../../../../src/io/event_reader.cpp), [docs/ingestion.md § Version-1 binary frame](../../../../ingestion.md) |

## B0020

[Lines 127–129](../../../../../tests/unit/ingest_test.cpp#L127); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void append_bytes(std::string& out, std::string_view value)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Append an exact byte span to the test frame builder. |
| inputs / outputs | Callable: void append_bytes(std::string& out, std::string_view value). Inputs: destination and borrowed bytes. Output: destination mutated in place. |
| invariants | The appended bytes equal the string_view byte sequence, including embedded NUL. |
| ownership | Copies the supplied byte view into caller-owned destination; source lifetime is needed only during the call. |
| failure | A failed check throws std::runtime_error; expected API rejection is caught only where rejects or rejects_code is called. Other exceptions propagate to main's std::exception handler. |
| cost | Work is the finite encoding, decoding, row replay or assertion work in this fixture. It is not a benchmark and does not establish an asymptotic or CPU-time bound for production. |
| Design | [include/crown/io/ingest.hpp](../../../../../include/crown/io/ingest.hpp), [src/io/ingest.cpp](../../../../../src/io/ingest.cpp), [src/io/event_reader.cpp](../../../../../src/io/event_reader.cpp), [docs/ingestion.md § Version-1 binary frame](../../../../ingestion.md) |

## B0022

[Lines 131–136](../../../../../tests/unit/ingest_test.cpp#L131); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void append_string(std::string& out, std::string_view value)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Append a uint32 byte length followed by one string payload. |
| inputs / outputs | Callable: void append_string(std::string& out, std::string_view value). Inputs: destination and string view. Output: destination mutated in place. |
| invariants | The fixture helper rejects lengths above the uint32 wire field. |
| ownership | Mutates the destination with length and bytes; string_view remains borrowed only for the call. |
| failure | A failed check throws std::runtime_error; expected API rejection is caught only where rejects or rejects_code is called. Other exceptions propagate to main's std::exception handler. |
| cost | Work is the finite encoding, decoding, row replay or assertion work in this fixture. It is not a benchmark and does not establish an asymptotic or CPU-time bound for production. |
| Design | [include/crown/io/ingest.hpp](../../../../../include/crown/io/ingest.hpp), [src/io/ingest.cpp](../../../../../src/io/ingest.cpp), [src/io/event_reader.cpp](../../../../../src/io/event_reader.cpp), [docs/ingestion.md § Version-1 binary frame](../../../../ingestion.md) |

## B0024

[Lines 138–155](../../../../../tests/unit/ingest_test.cpp#L138); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void append_binary_value(std::string& out, const Value& value)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Append one typed scalar using the test's version-one binary tags and payloads. |
| inputs / outputs | Callable: void append_binary_value(std::string& out, const Value& value). Inputs: destination and Value variant. Output: encoded bytes appended. |
| invariants | Tag values are int64=0, text=1, bool=2, date=3 and decimal=4; scalar payloads follow the test frame recipe. |
| ownership | Mutates caller-owned destination; scalar variants are read without retaining references. |
| failure | A failed check throws std::runtime_error; expected API rejection is caught only where rejects or rejects_code is called. Other exceptions propagate to main's std::exception handler. |
| cost | Work is the finite encoding, decoding, row replay or assertion work in this fixture. It is not a benchmark and does not establish an asymptotic or CPU-time bound for production. |
| Design | [include/crown/io/ingest.hpp](../../../../../include/crown/io/ingest.hpp), [src/io/ingest.cpp](../../../../../src/io/ingest.cpp), [src/io/event_reader.cpp](../../../../../src/io/event_reader.cpp), [docs/ingestion.md § Version-1 binary frame](../../../../ingestion.md) |

## B0026

[Lines 157–179](../../../../../tests/unit/ingest_test.cpp#L157); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::string golden_binary(const InputEvent& input, const Catalog& catalog)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Independently assemble one complete CROWNUPD version-one input frame. |
| inputs / outputs | Callable: std::string golden_binary(const InputEvent& input, const Catalog& catalog). Inputs: event and catalog. Output: raw frame string. |
| invariants | The payload field order is catalog/source versions, catalog digest, sequence, table, operation, optional position, arity and typed cells; the frame prefix is CROWNUPD/version 1/uint32 payload size. |
| ownership | Builds a local payload and frame string, then returns the owned frame. |
| failure | A failed check throws std::runtime_error; expected API rejection is caught only where rejects or rejects_code is called. Other exceptions propagate to main's std::exception handler. |
| cost | Serializes the fixed catalog/event fields into one hand-assembled frame. |
| Design | [include/crown/io/ingest.hpp](../../../../../include/crown/io/ingest.hpp), [src/io/ingest.cpp](../../../../../src/io/ingest.cpp), [src/io/event_reader.cpp](../../../../../src/io/event_reader.cpp), [docs/ingestion.md § Version-1 binary frame](../../../../ingestion.md) |

## B0028

[Lines 181–187](../../../../../tests/unit/ingest_test.cpp#L181); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
bool same_event(const auto& left, const InputEvent& right)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Compare sequence, table, operation, full row and optional source position. |
| inputs / outputs | Callable: bool same_event(const auto& left, const InputEvent& right). Inputs: left-like value and expected InputEvent. Output: Boolean equality result. |
| invariants | Equality covers only the physical event's sequence/table/operation/values and optional source position. |
| ownership | Fixture values and runtime objects are local to this call unless returned by value; borrowed references and views remain subject to their declared owners. No test result survives the function. |
| failure | A failed check throws std::runtime_error; expected API rejection is caught only where rejects or rejects_code is called. Other exceptions propagate to main's std::exception handler. |
| cost | Work is the finite encoding, decoding, row replay or assertion work in this fixture. It is not a benchmark and does not establish an asymptotic or CPU-time bound for production. |
| Design | [include/crown/io/ingest.hpp](../../../../../include/crown/io/ingest.hpp), [src/io/ingest.cpp](../../../../../src/io/ingest.cpp), [src/io/event_reader.cpp](../../../../../src/io/event_reader.cpp), [docs/ingestion.md § Version-1 binary frame](../../../../ingestion.md) |

## B0030

[Lines 189–307](../../../../../tests/unit/ingest_test.cpp#L189); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void json_contract_and_typed_scalars()
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Check raw JSON read/write, catalog binding, exact scalar forms, field rejection and source-position validation. |
| inputs / outputs | Callable: void json_contract_and_typed_scalars(). Input: none. Output: None after typed JSON API assertions. |
| invariants | The raw record is hand-authored before the production writer round-trip; the fixture covers int64 and uint64 maxima. |
| ownership | Fixture values and runtime objects are local to this call unless returned by value; borrowed references and views remain subject to their declared owners. No test result survives the function. |
| failure | Each malformed case must raise crown::Error; the unsupported operation additionally requires unsupported_input_operation. |
| cost | Exercises one raw JSON event, a bounded list of mutated JSON objects, and fixed scalar/digest boundaries. |
| Design | [include/crown/io/ingest.hpp](../../../../../include/crown/io/ingest.hpp), [src/io/ingest.cpp](../../../../../src/io/ingest.cpp), [docs/ingestion.md § Version-1 JSONL event](../../../../ingestion.md), [docs/catalog.md § Validation and canonical writing](../../../../catalog.md) |

## B0032

[Lines 309–324](../../../../../tests/unit/ingest_test.cpp#L309); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void catalog_fingerprint_matches_existing_serializer()
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Compare the input catalog hash with SHA256 of the canonical catalog serializer. |
| inputs / outputs | Callable: void catalog_fingerprint_matches_existing_serializer(). Input: none. Output: None after digest and feature-spelling checks. |
| invariants | The compared expected digest is computed from write_catalog(catalog).dump(); this checks agreement with that serializer, not an independently hard-coded digest. |
| ownership | Fixture values and runtime objects are local to this call unless returned by value; borrowed references and views remain subject to their declared owners. No test result survives the function. |
| failure | A failed check throws std::runtime_error; expected API rejection is caught only where rejects or rejects_code is called. Other exceptions propagate to main's std::exception handler. |
| cost | Work is the finite encoding, decoding, row replay or assertion work in this fixture. It is not a benchmark and does not establish an asymptotic or CPU-time bound for production. |
| Design | [include/crown/io/ingest.hpp](../../../../../include/crown/io/ingest.hpp), [src/io/ingest.cpp](../../../../../src/io/ingest.cpp), [docs/ingestion.md § Version-1 JSONL event](../../../../ingestion.md), [docs/catalog.md § Validation and canonical writing](../../../../catalog.md) |

## B0034

[Lines 326–408](../../../../../tests/unit/ingest_test.cpp#L326); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void binary_golden_and_frames()
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Check exact binary writer bytes, decoding, malformed frames and concatenated-reader acknowledgement. |
| inputs / outputs | Callable: void binary_golden_and_frames(). Input: none. Output: None after frame and progress assertions. |
| invariants | The manual frame has no checksum; malformed probes target magic/version/length/tags, and reader progress advances only on acknowledge. |
| ownership | Fixture values and runtime objects are local to this call unless returned by value; borrowed references and views remain subject to their declared owners. No test result survives the function. |
| failure | Malformed frame probes must raise crown::Error; exact byte/progress assertions use check and throw std::runtime_error. |
| cost | Builds one golden and two concatenated records, then checks fixed malformed mutations and reader transitions. |
| Design | [include/crown/io/ingest.hpp](../../../../../include/crown/io/ingest.hpp), [src/io/ingest.cpp](../../../../../src/io/ingest.cpp), [src/io/event_reader.cpp](../../../../../src/io/event_reader.cpp), [docs/ingestion.md § Version-1 binary frame](../../../../ingestion.md) |

## B0036

[Lines 410–557](../../../../../tests/unit/ingest_test.cpp#L410); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void jsonl_progress_failures_and_limits()
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Check JSONL peek/ack progress, source offsets, sticky failures, all configured caps and sequence overflow. |
| inputs / outputs | Callable: void jsonl_progress_failures_and_limits(). Input: none. Output: None after finite reader cases. |
| invariants | Peek may consume/count bytes but does not accept sequence/source progress; acknowledge alone commits the cached record and failures are sticky. |
| ownership | Fixture values and runtime objects are local to this call unless returned by value; borrowed references and views remain subject to their declared owners. No test result survives the function. |
| failure | Expected limit/sequence failures must throw crown::Error; sticky-state and no-advance assertions are separate check calls. |
| cost | Uses a finite set of streams to exercise progress, each configured limit and maximum sequence behavior. |
| Design | [include/crown/io/ingest.hpp](../../../../../include/crown/io/ingest.hpp), [src/io/ingest.cpp](../../../../../src/io/ingest.cpp), [src/io/event_reader.cpp](../../../../../src/io/event_reader.cpp), [docs/ingestion.md § Version-1 binary frame](../../../../ingestion.md) |

## B0038

[Lines 559–609](../../../../../tests/unit/ingest_test.cpp#L559); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void jsonl_object_budget_excludes_framing()
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Check object-byte versus raw-stream-byte accounting for LF and CRLF JSONL framing. |
| inputs / outputs | Callable: void jsonl_object_budget_excludes_framing(). Input: none. Output: None after exact-limit and one-under cases. |
| invariants | record_bytes limits the JSON object without LF/CRLF, whereas total_bytes counts the raw terminator too. |
| ownership | Fixture values and runtime objects are local to this call unless returned by value; borrowed references and views remain subject to their declared owners. No test result survives the function. |
| failure | One-under and total-byte cases require resource_limit; any acceptance or progress mismatch throws. |
| cost | Work is the finite encoding, decoding, row replay or assertion work in this fixture. It is not a benchmark and does not establish an asymptotic or CPU-time bound for production. |
| Design | [include/crown/io/ingest.hpp](../../../../../include/crown/io/ingest.hpp), [src/io/ingest.cpp](../../../../../src/io/ingest.cpp), [src/io/event_reader.cpp](../../../../../src/io/event_reader.cpp), [docs/ingestion.md § Version-1 binary frame](../../../../ingestion.md) |

## B0040

[Lines 611–689](../../../../../tests/unit/ingest_test.cpp#L611); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void nondefault_options_are_format_scoped()
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Check that options unrelated to JSONL/binary or each legacy profile are rejected. |
| inputs / outputs | Callable: void nondefault_options_are_format_scoped(). Input: none. Output: None after constructor/profile assertions. |
| invariants | The relation-token mapping is accepted only in the explicit legacy-relations case shown. |
| ownership | Fixture values and runtime objects are local to this call unless returned by value; borrowed references and views remain subject to their declared owners. No test result survives the function. |
| failure | Rejected profiles require invalid_input_options; the explicit legacy-relations positive control must reach EOF. |
| cost | Work is the finite encoding, decoding, row replay or assertion work in this fixture. It is not a benchmark and does not establish an asymptotic or CPU-time bound for production. |
| Design | [include/crown/io/ingest.hpp](../../../../../include/crown/io/ingest.hpp), [src/io/event_reader.cpp](../../../../../src/io/event_reader.cpp), [docs/ingestion.md § CSV and explicit legacy profiles](../../../../ingestion.md), [docs/ingestion.md § Reader acceptance and engine replay](../../../../ingestion.md) |

## B0042

[Lines 691–752](../../../../../tests/unit/ingest_test.cpp#L691); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void timestamp_flag_legacy_profile()
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Check legacy timestamp/flag conversion, source position progression, monotonicity and required options. |
| inputs / outputs | Callable: void timestamp_flag_legacy_profile(). Input: none. Output: None after two accepted rows and rejection cases. |
| invariants | The timestamp field becomes source offset, the flag selects insert/delete, and reader sequence is assigned contiguously. |
| ownership | Fixture values and runtime objects are local to this call unless returned by value; borrowed references and views remain subject to their declared owners. No test result survives the function. |
| failure | Repeated/backward offsets require invalid_source_position and subsequent peeks require input_failed. |
| cost | Work is the finite encoding, decoding, row replay or assertion work in this fixture. It is not a benchmark and does not establish an asymptotic or CPU-time bound for production. |
| Design | [include/crown/io/ingest.hpp](../../../../../include/crown/io/ingest.hpp), [src/io/event_reader.cpp](../../../../../src/io/event_reader.cpp), [docs/ingestion.md § CSV and explicit legacy profiles](../../../../ingestion.md), [docs/ingestion.md § Reader acceptance and engine replay](../../../../ingestion.md) |

## B0044

[Lines 754–925](../../../../../tests/unit/ingest_test.cpp#L754); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void csv_and_legacy_profiles()
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Check typed CSV and explicit legacy row formats, header/quote handling, operations and option rejection. |
| inputs / outputs | Callable: void csv_and_legacy_profiles(). Input: none. Output: None after the finite format fixtures. |
| invariants | CSV header permutation is mapped to full physical column order; legacy profiles remain explicit, headerless formats. |
| ownership | Fixture values and runtime objects are local to this call unless returned by value; borrowed references and views remain subject to their declared owners. No test result survives the function. |
| failure | Specified format/option violations must raise crown::Error; value or count mismatches throw std::runtime_error. |
| cost | Parses the fixed header, two CSV rows and one example for each explicit legacy profile, plus invalid controls. |
| Design | [include/crown/io/ingest.hpp](../../../../../include/crown/io/ingest.hpp), [src/io/event_reader.cpp](../../../../../src/io/event_reader.cpp), [docs/ingestion.md § CSV and explicit legacy profiles](../../../../ingestion.md), [docs/ingestion.md § Reader acceptance and engine replay](../../../../ingestion.md) |

## B0046

[Lines 927–945](../../../../../tests/unit/ingest_test.cpp#L927); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
PhysicalPlan edge_self_join_plan()
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Lower a two-occurrence self-join plan over an Edge table with an ignored payload column. |
| inputs / outputs | Callable: PhysicalPlan edge_self_join_plan(). Input: none. Output: PhysicalPlan produced by planner::lower_tree. |
| invariants | Both occurrences use the same physical table; payload is ignored by the query and both aliases share y. |
| ownership | Returns a lowered PhysicalPlan owning its catalog/query/tree-derived state; fixture temporaries are copied or moved into lowering. |
| failure | A failed check throws std::runtime_error; expected API rejection is caught only where rejects or rejects_code is called. Other exceptions propagate to main's std::exception handler. |
| cost | Work is the finite encoding, decoding, row replay or assertion work in this fixture. It is not a benchmark and does not establish an asymptotic or CPU-time bound for production. |
| Design | [include/crown/runtime/replay.hpp](../../../../../include/crown/runtime/replay.hpp), [src/runtime/replay.cpp](../../../../../src/runtime/replay.cpp), [include/crown/runtime/delta.hpp](../../../../../include/crown/runtime/delta.hpp), [docs/physical_runtime.md § Input and source-row identity](../../../../physical_runtime.md), [docs/physical_runtime.md § Prepare, busy reads, and commit](../../../../physical_runtime.md) |

## B0048

[Lines 947–949](../../../../../tests/unit/ingest_test.cpp#L947); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Row edge(std::int64_t x, std::int64_t y, std::string payload)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Build one full Edge physical row. |
| inputs / outputs | Callable: Row edge(std::int64_t x, std::int64_t y, std::string payload). Inputs: x, y and payload string. Output: Row. |
| invariants | Row layout is x/y/payload and payload is not omitted from physical identity. |
| ownership | Returns a Row that owns the moved payload string. |
| failure | A failed check throws std::runtime_error; expected API rejection is caught only where rejects or rejects_code is called. Other exceptions propagate to main's std::exception handler. |
| cost | Work is the finite encoding, decoding, row replay or assertion work in this fixture. It is not a benchmark and does not establish an asymptotic or CPU-time bound for production. |
| Design | [include/crown/io/ingest.hpp](../../../../../include/crown/io/ingest.hpp), [src/io/ingest.cpp](../../../../../src/io/ingest.cpp), [src/io/event_reader.cpp](../../../../../src/io/event_reader.cpp), [docs/ingestion.md § Version-1 binary frame](../../../../ingestion.md) |

## B0050

[Lines 951–956](../../../../../tests/unit/ingest_test.cpp#L951); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::string edge_json_line(const Catalog& catalog, std::uint64_t sequence,
                           SetOperation operation, Row values)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Serialize one Edge set update with source offset derived from sequence. |
| inputs / outputs | Callable: std::string edge_json_line(const Catalog& catalog, std::uint64_t sequence, SetOperation operation, Row values). Inputs: catalog, sequence, operation and row. Output: JSON event text. |
| invariants | Source name is edge-feed and the offset is sequence multiplied by eleven; the operation and row are supplied directly. |
| ownership | Returns writer-owned JSON text; the temporary event and source position expire after the call. |
| failure | A failed check throws std::runtime_error; expected API rejection is caught only where rejects or rejects_code is called. Other exceptions propagate to main's std::exception handler. |
| cost | Work is the finite encoding, decoding, row replay or assertion work in this fixture. It is not a benchmark and does not establish an asymptotic or CPU-time bound for production. |
| Design | [include/crown/io/ingest.hpp](../../../../../include/crown/io/ingest.hpp), [src/io/ingest.cpp](../../../../../src/io/ingest.cpp), [src/io/event_reader.cpp](../../../../../src/io/event_reader.cpp), [docs/ingestion.md § Version-1 binary frame](../../../../ingestion.md) |

## B0052

[Lines 958–963](../../../../../tests/unit/ingest_test.cpp#L958); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::vector<Row> replay_rows()
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Return the fixed ordered set of eight Edge rows, including duplicate and missing-row cases. |
| inputs / outputs | Callable: std::vector&lt;Row&gt; replay_rows(). Input: none. Output: vector&lt;Row&gt; in replay order. |
| invariants | The vector contains eight source events, including a duplicate full row, distinct payload witnesses and one final absent-row delete. |
| ownership | Returns a fresh vector of rows with owned payload strings. |
| failure | A failed check throws std::runtime_error; expected API rejection is caught only where rejects or rejects_code is called. Other exceptions propagate to main's std::exception handler. |
| cost | Work is the finite encoding, decoding, row replay or assertion work in this fixture. It is not a benchmark and does not establish an asymptotic or CPU-time bound for production. |
| Design | [include/crown/io/ingest.hpp](../../../../../include/crown/io/ingest.hpp), [src/io/ingest.cpp](../../../../../src/io/ingest.cpp), [src/io/event_reader.cpp](../../../../../src/io/event_reader.cpp), [docs/ingestion.md § Version-1 binary frame](../../../../ingestion.md) |

## B0054

[Lines 965–969](../../../../../tests/unit/ingest_test.cpp#L965); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::vector<SetOperation> replay_operations()
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Return the eight insert/erase operations aligned by index with replay_rows. |
| inputs / outputs | Callable: std::vector&lt;SetOperation&gt; replay_operations(). Input: none. Output: vector&lt;SetOperation&gt; of matching length. |
| invariants | Operation index i corresponds to row index i; both vectors have eight elements. |
| ownership | Returns a fresh operation vector. |
| failure | A failed check throws std::runtime_error; expected API rejection is caught only where rejects or rejects_code is called. Other exceptions propagate to main's std::exception handler. |
| cost | Work is the finite encoding, decoding, row replay or assertion work in this fixture. It is not a benchmark and does not establish an asymptotic or CPU-time bound for production. |
| Design | [include/crown/io/ingest.hpp](../../../../../include/crown/io/ingest.hpp), [src/io/ingest.cpp](../../../../../src/io/ingest.cpp), [src/io/event_reader.cpp](../../../../../src/io/event_reader.cpp), [docs/ingestion.md § Version-1 binary frame](../../../../ingestion.md) |

## B0056

[Lines 971–980](../../../../../tests/unit/ingest_test.cpp#L971); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::string replay_stream(const Catalog& catalog)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Serialize the fixed row and operation vectors as newline-delimited ordered input. |
| inputs / outputs | Callable: std::string replay_stream(const Catalog& catalog). Input: catalog. Output: owned JSONL string with one-based sequence IDs. |
| invariants | The output has one line per paired row/operation and sequence is vector index plus one. |
| ownership | Returns an owned string assembled from local rows and serialized event strings. |
| failure | A failed check throws std::runtime_error; expected API rejection is caught only where rejects or rejects_code is called. Other exceptions propagate to main's std::exception handler. |
| cost | Work is the finite encoding, decoding, row replay or assertion work in this fixture. It is not a benchmark and does not establish an asymptotic or CPU-time bound for production. |
| Design | [include/crown/io/ingest.hpp](../../../../../include/crown/io/ingest.hpp), [src/io/ingest.cpp](../../../../../src/io/ingest.cpp), [src/io/event_reader.cpp](../../../../../src/io/event_reader.cpp), [docs/ingestion.md § Version-1 binary frame](../../../../ingestion.md) |

## B0058

[Lines 982–1054](../../../../../tests/unit/ingest_test.cpp#L982); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void physical_replay_preserves_source_rows_and_counts()
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Apply the fixture stream to OrderedReplay and PhysicalRuntime while checking source-row identity and self-join counts. |
| inputs / outputs | Callable: void physical_replay_preserves_source_rows_and_counts(). Input: none. Output: None after runtime snapshots, counters and invariants are checked. |
| invariants | The physical set stores full rows including payload; each accepted ordered event advances sequence even when the last deletion is a set no-op. |
| ownership | Fixture values and runtime objects are local to this call unless returned by value; borrowed references and views remain subject to their declared owners. No test result survives the function. |
| failure | CROWN runtime, reader and invariant errors propagate; failed checks throw std::runtime_error. |
| cost | Applies eight events and checks one runtime snapshot/invariant set per event. |
| Design | [include/crown/runtime/replay.hpp](../../../../../include/crown/runtime/replay.hpp), [src/runtime/replay.cpp](../../../../../src/runtime/replay.cpp), [include/crown/runtime/delta.hpp](../../../../../include/crown/runtime/delta.hpp), [docs/physical_runtime.md § Input and source-row identity](../../../../physical_runtime.md), [docs/physical_runtime.md § Prepare, busy reads, and commit](../../../../physical_runtime.md) |

## B0060

[Lines 1056–1064](../../../../../tests/unit/ingest_test.cpp#L1056); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::set<SignedRow> expected_delta(const Relation& before,
                                   const Relation& after)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Compute signed set differences between two reference relations. |
| inputs / outputs | Callable: std::set&lt;SignedRow&gt; expected_delta(const Relation& before, const Relation& after). Inputs: before and after Relation. Output: set of insert/erase row pairs. |
| invariants | Only rows present in after but not before become inserts; only rows present in before but not after become erases. |
| ownership | Fixture values and runtime objects are local to this call unless returned by value; borrowed references and views remain subject to their declared owners. No test result survives the function. |
| failure | A failed check throws std::runtime_error; expected API rejection is caught only where rejects or rejects_code is called. Other exceptions propagate to main's std::exception handler. |
| cost | Work is the finite encoding, decoding, row replay or assertion work in this fixture. It is not a benchmark and does not establish an asymptotic or CPU-time bound for production. |
| Design | [include/crown/runtime/replay.hpp](../../../../../include/crown/runtime/replay.hpp), [src/runtime/replay.cpp](../../../../../src/runtime/replay.cpp), [include/crown/runtime/delta.hpp](../../../../../include/crown/runtime/delta.hpp), [docs/physical_runtime.md § Input and source-row identity](../../../../physical_runtime.md), [docs/physical_runtime.md § Prepare, busy reads, and commit](../../../../physical_runtime.md) |

## B0062

[Lines 1066–1075](../../../../../tests/unit/ingest_test.cpp#L1066); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::set<SignedRow> drain_delta(DeltaRuntime::Epoch& epoch)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Consume one DeltaRuntime epoch into signed exported rows and require closure. |
| inputs / outputs | Callable: std::set&lt;SignedRow&gt; drain_delta(DeltaRuntime::Epoch& epoch). Input: live epoch reference. Output: set of signed rows. |
| invariants | Every yielded operation/row pair must be unique in the drained set and the epoch must be inactive with zero remaining records. |
| ownership | Consumes the borrowed live Epoch and copies exported rows into a local set before returning. |
| failure | A failed check throws std::runtime_error; expected API rejection is caught only where rejects or rejects_code is called. Other exceptions propagate to main's std::exception handler. |
| cost | Work is the finite encoding, decoding, row replay or assertion work in this fixture. It is not a benchmark and does not establish an asymptotic or CPU-time bound for production. |
| Design | [include/crown/runtime/replay.hpp](../../../../../include/crown/runtime/replay.hpp), [src/runtime/replay.cpp](../../../../../src/runtime/replay.cpp), [include/crown/runtime/delta.hpp](../../../../../include/crown/runtime/delta.hpp), [docs/physical_runtime.md § Input and source-row identity](../../../../physical_runtime.md), [docs/physical_runtime.md § Prepare, busy reads, and commit](../../../../physical_runtime.md) |

## B0064

[Lines 1077–1083](../../../../../tests/unit/ingest_test.cpp#L1077); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
DeltaOptions ordered_delta_options()
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Build maintenance-mode options with live output and ordered-replay completion. |
| inputs / outputs | Callable: DeltaOptions ordered_delta_options(). Input: none. Output: DeltaOptions. |
| invariants | The returned options select maintenance mode, live-on-output maintenance and ordered-replay completion. |
| ownership | Returns options by value with no retained aliases. |
| failure | A failed check throws std::runtime_error; expected API rejection is caught only where rejects or rejects_code is called. Other exceptions propagate to main's std::exception handler. |
| cost | Work is the finite encoding, decoding, row replay or assertion work in this fixture. It is not a benchmark and does not establish an asymptotic or CPU-time bound for production. |
| Design | [include/crown/runtime/replay.hpp](../../../../../include/crown/runtime/replay.hpp), [src/runtime/replay.cpp](../../../../../src/runtime/replay.cpp), [include/crown/runtime/delta.hpp](../../../../../include/crown/runtime/delta.hpp), [docs/physical_runtime.md § Input and source-row identity](../../../../physical_runtime.md), [docs/physical_runtime.md § Prepare, busy reads, and commit](../../../../physical_runtime.md) |

## B0066

[Lines 1085–1121](../../../../../tests/unit/ingest_test.cpp#L1085); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void ordered_delta_replay_matches_a04()
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Compare each ordered native delta epoch with an independent before/after evaluator. |
| inputs / outputs | Callable: void ordered_delta_replay_matches_a04(). Input: none. Output: None after applying and draining all eight events. |
| invariants | Each input is checked against the exact before/after relation difference; output is fully drained before the next replay input. |
| ownership | Fixture values and runtime objects are local to this call unless returned by value; borrowed references and views remain subject to their declared owners. No test result survives the function. |
| failure | CROWN errors propagate; any epoch, relation, or closure mismatch throws std::runtime_error. |
| cost | Runs eight updates, recomputes before/after reference relations, and drains each output epoch. |
| Design | [include/crown/runtime/replay.hpp](../../../../../include/crown/runtime/replay.hpp), [src/runtime/replay.cpp](../../../../../src/runtime/replay.cpp), [include/crown/runtime/delta.hpp](../../../../../include/crown/runtime/delta.hpp), [docs/physical_runtime.md § Input and source-row identity](../../../../physical_runtime.md), [docs/physical_runtime.md § Prepare, busy reads, and commit](../../../../physical_runtime.md) |

## B0068

[Lines 1123–1234](../../../../../tests/unit/ingest_test.cpp#L1123); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void replay_retry_busy_owner_and_later_malformed_record()
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Check busy-owner retry, reader/runtime binding, catalog mismatch, malformed later input and the delta output barrier. |
| inputs / outputs | Callable: void replay_retry_busy_owner_and_later_malformed_record(). Input: none. Output: None after five finite replay scenarios. |
| invariants | The same cached event is retried only after the blocking prepared epoch/output lease is released. |
| ownership | Fixture values and runtime objects are local to this call unless returned by value; borrowed references and views remain subject to their declared owners. No test result survives the function. |
| failure | The named busy/catalog/input failures must carry exact codes where asserted; any state mismatch throws std::runtime_error. |
| cost | Exercises four finite stream scenarios: busy retry, owner binding, catalog/malformed input, and output barrier. |
| Design | [include/crown/runtime/replay.hpp](../../../../../include/crown/runtime/replay.hpp), [src/runtime/replay.cpp](../../../../../src/runtime/replay.cpp), [include/crown/runtime/delta.hpp](../../../../../include/crown/runtime/delta.hpp), [docs/physical_runtime.md § Input and source-row identity](../../../../physical_runtime.md), [docs/physical_runtime.md § Prepare, busy reads, and commit](../../../../physical_runtime.md) |

## B0069

[Lines 1235–1237](../../../../../tests/unit/ingest_test.cpp#L1235); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L1235-L1237:sha256:9e375a3cb3a2cbe2f9ded9c8296a6ab66848cc826fd71f919246acb17e0bd455
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Close the recorded declaration scopes in ingest_test.cpp: namespace (anonymous). |
| inputs / outputs | Preceding namespace, type or initializer declarations in; completed lexical boundary out. |
| invariants | Brace-opening context is recorded in root-scope-context-v1.json. These are declaration/initializer boundaries, not an independent update, validation or recovery operation. |
| ownership | Enclosing objects and borrowed fields keep their declared ownership. This punctuation creates no new owner. |
| failure | Malformed scope syntax is a compile error. Any initializer/constructor failure belongs to the enclosing object declaration. |
| cost | No separate loop, guard or engine call is introduced by the delimiter; enclosing initialization and object lifetime still have their actual costs. |
| Design | [tests/unit/ingest_test.cpp](../../../../../tests/unit/ingest_test.cpp), [docs/ingestion.md](../../../../ingestion.md), [docs/code_review.md](../../../../code_review.md) |

## B0070

[Lines 1238–1257](../../../../../tests/unit/ingest_test.cpp#L1238); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
int main()
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Run the ingest codec, progress, format and physical/delta replay unit cases. |
| inputs / outputs | Callable: int main(). Input: none. Output: zero on success; catches std::exception, writes its message and returns one on failure. |
| invariants | The function runs each listed helper/test once in source order and treats any standard exception as one test-process failure. |
| ownership | All test state is local to invoked cases; main owns only exception text during its catch path. |
| failure | Catches std::exception, prints what() and returns 1; otherwise writes the success line and returns 0. |
| cost | Work is the finite encoding, decoding, row replay or assertion work in this fixture. It is not a benchmark and does not establish an asymptotic or CPU-time bound for production. |
| Design | [include/crown/io/ingest.hpp](../../../../../include/crown/io/ingest.hpp), [src/io/ingest.cpp](../../../../../src/io/ingest.cpp), [src/io/event_reader.cpp](../../../../../src/io/event_reader.cpp), [docs/ingestion.md § Version-1 binary frame](../../../../ingestion.md) |
