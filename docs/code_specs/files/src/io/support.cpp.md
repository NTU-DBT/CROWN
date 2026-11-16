# `src/io/support.cpp` — block usage map

[Source](../../../../../src/io/support.cpp) · [Source index](../../../README.md) · [Subsystem contracts](../../../subsystem_contracts.md) · [Reviewed primitives](../../../primitives.md)

Parse logical-support diagnostic Rows and serialize retained support state/journals without applying updates.

Snapshot SHA-256: `7a55a71d3c0a4031ac18dc802da5d2d4a3bf5eab48fb7fd0afa7f49e6e60e7f8`. 148 lines partitioned into 24 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [io](../../../subsystem_contracts.md#io). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/ingestion.md](../../../../ingestion.md), [docs/query_identity.md](../../../../query_identity.md), [docs/schema_evolution.md](../../../../schema_evolution.md), [docs/cli.md](../../../../cli.md), [docs/query_memory.md](../../../../query_memory.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–7](../../../../../src/io/support.cpp#L1) | Imports dependencies; declares namespace scope. |  · [reviewed contract](#b0001) |
| [B0002 · 8–8](../../../../../src/io/support.cpp#L8) | Callable definition: const storage::TupleLayout& readable(const storage::TupleLayout& layout) | calls ; returns layout · [reviewed contract](#b0002) |
| [B0003 · 9–9](../../../../../src/io/support.cpp#L9) | Callable definition: storage::TupleLayout readable(const storage::AccountedLayout& layout) | calls descriptor; returns layout.descriptor() · [reviewed contract](#b0003) |
| [B0004 · 10–10](../../../../../src/io/support.cpp#L10) | Callable definition: Json row(storage::RowView values) | calls Json::array, cells, push_back, write_scalar_view; returns output; growth push_back; 1 loop sites · [reviewed contract](#b0004) |
| [B0005 · 11–11](../../../../../src/io/support.cpp#L11) | Callable definition: Json row(storage::TupleValuesView values) | calls Json::array, push_back, write_scalar_view; returns output; growth push_back; 1 loop sites · [reviewed contract](#b0005) |
| [B0006 · 12–20](../../../../../src/io/support.cpp#L12) | Callable definition: std::string role(runtime::SupportRole role) | calls Error; returns @; @ · [reviewed contract](#b0006) |
| [B0007 · 21–23](../../../../../src/io/support.cpp#L21) | Callable definition: Json handle(runtime::SupportHandle value) | calls role; returns {{@ ,value.owner.value},{@ ,value.node.value},{@ ,role(value.role)},{@ ,value.tuple.value}} · [reviewed contract](#b0007) |
| [B0008 · 24–30](../../../../../src/io/support.cpp#L24) | Callable definition: std::string operation(SetOperation operation) | calls Error; returns @; @; growth insert · [reviewed contract](#b0008) |
| [B0009 · 31–37](../../../../../src/io/support.cpp#L31) | Callable definition: std::string event_kind(runtime::SupportEventKind kind) | calls Error; returns @; @ · [reviewed contract](#b0009) |
| [B0010 · 38–43](../../../../../src/io/support.cpp#L38) | Callable definition: Json value_state(const runtime::SupportValueState& value) | calls Json; returns {{@ ,value.member}, · [reviewed contract](#b0010) |
| [B0011 · 44–56](../../../../../src/io/support.cpp#L44) | Callable definition: Json journal(const runtime::SupportJournal& value) | calls Json::array, push_back, handle, row; returns {{@ ,value.sequence},{@ ,std::move(records)},{@ ,std::move(events)}}; growth push_back; 2 loop sites · [reviewed contract](#b0011) |
| [B0012 · 57–61](../../../../../src/io/support.cpp#L57) | Callable definition: Json keys(const std::vector&lt;runtime::ProjectionKeySnapshot&gt;& values) | calls Json::array, push_back, row, values; returns output; growth push_back; 1 loop sites · [reviewed contract](#b0012) |
| [B0013 · 62–62](../../../../../src/io/support.cpp#L62) | Closes surrounding scope/type. | source comment (unverified): // namespace · [reviewed contract](#b0013) |
| [B0014 · 63–103](../../../../../src/io/support.cpp#L63) | Callable definition: template&lt;class Plan&gt; SupportTrace read_support_trace_impl(std::string_view text,const Plan& plan,std::size_t max_updates) | calls detail::parse_json, detail::fields, detail::version, at; returns trace; growth emplace, insert, push_back; 3 loop sites; source comment (unverified): // Diagnostic Rows/DOM own ordinary storage; native descriptors only supply validation. · [reviewed contract](#b0014) |
| [B0015 · 104–104](../../../../../src/io/support.cpp#L104) | Callable definition: SupportTrace read_support_trace(std::string_view text,const PhysicalPlan& plan,std::size_t max_updates) | calls read_support_trace_impl; returns read_support_trace_impl(text,plan,max_updates) · [reviewed contract](#b0015) |
| [B0016 · 105–105](../../../../../src/io/support.cpp#L105) | Callable definition: SupportTrace read_support_trace(std::string_view text,const CompiledProgram& plan,std::size_t max_updates) | calls read_support_trace_impl; returns read_support_trace_impl(text,plan,max_updates) · [reviewed contract](#b0016) |
| [B0017 · 106–106](../../../../../src/io/support.cpp#L106) | Explanatory comments or spacing. |  |
| [B0018 · 107–113](../../../../../src/io/support.cpp#L107) | Callable definition: Json write_support_options(const runtime::SupportOptions& options) | calls Json; returns result · [reviewed contract](#b0018) |
| [B0019 · 114–126](../../../../../src/io/support.cpp#L114) | Callable definition: template&lt;class Plan&gt; Json write_support_snapshot_impl(const runtime::SupportSnapshot& snapshot,const Plan& plan) | calls Json::array, push_back, row, values; returns {{@ ,snapshot.sequence},{@ ,snapshot.has_answer},{@ ,std::move(nodes)}}; growth push_back; 3 loop sites · [reviewed contract](#b0019) |
| [B0020 · 127–127](../../../../../src/io/support.cpp#L127) | Callable definition: Json write_support_snapshot(const runtime::SupportSnapshot& snapshot,const PhysicalPlan& plan) | calls write_support_snapshot_impl; returns write_support_snapshot_impl(snapshot,plan) · [reviewed contract](#b0020) |
| [B0021 · 128–128](../../../../../src/io/support.cpp#L128) | Callable definition: Json write_support_snapshot(const runtime::SupportSnapshot& snapshot,const CompiledProgram& plan) | calls write_support_snapshot_impl; returns write_support_snapshot_impl(snapshot,plan) · [reviewed contract](#b0021) |
| [B0022 · 129–129](../../../../../src/io/support.cpp#L129) | Explanatory comments or spacing. |  |
| [B0023 · 130–147](../../../../../src/io/support.cpp#L130) | Callable definition: Json write_support_epoch(const runtime::SupportEpoch& epoch) | calls Json::array, push_back, handle, operation; returns {{@ ,epoch.sequence},{@ ,epoch.native_changed},{@ ,epoch.has_answer},; growth push_back; 1 loop sites · [reviewed contract](#b0023) |
| [B0024 · 148–148](../../../../../src/io/support.cpp#L148) | Closes surrounding scope/type. | source comment (unverified): // namespace crown::io · [reviewed contract](#b0024) |

## B0001

[Lines 1–7](../../../../../src/io/support.cpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
#include "crown/io/support.hpp"
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Implement explicit logical-native support diagnostic trace import and state/journal export. |
| inputs / outputs | Imports the declarations used by this translation unit/header; no runtime input or result. |
| invariants | Namespace/includes do not perform admission, validation, publication or IO. |
| ownership | Declarations give no ownership of caller records, source bytes or runtime accounts. |
| failure | Compile/link dependencies only; there is no executable failure boundary in these includes. |
| cost | Compile-time dependencies; later functions account for their own runtime work and storage. |
| Design | [src/io/support.cpp](../../../../../src/io/support.cpp), [include/crown/io/support.hpp](../../../../../include/crown/io/support.hpp), [include/crown/runtime/support.hpp](../../../../../include/crown/runtime/support.hpp), [src/io/json.hpp](../../../../../src/io/json.hpp), [src/io/document.cpp](../../../../../src/io/document.cpp), [src/storage/layout.cpp](../../../../../src/storage/layout.cpp), [src/storage/accounted_layout.cpp](../../../../../src/storage/accounted_layout.cpp), [src/catalog/catalog.cpp](../../../../../src/catalog/catalog.cpp), [include/crown/storage/tuple_values.hpp](../../../../../include/crown/storage/tuple_values.hpp), [docs/support_invariants.md](../../../../support_invariants.md), [docs/code_review.md](../../../../code_review.md) |

## B0002

[Lines 8–8](../../../../../src/io/support.cpp#L8); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
const storage::TupleLayout& readable(const storage::TupleLayout& layout){return layout;}
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Borrow an ordinary plan layout descriptor for diagnostic row validation. |
| inputs / outputs | TupleLayout reference in; same const reference out. |
| invariants | No descriptor clone or tuple factory invocation. |
| ownership | Borrowed layout; no new retained shared handle. |
| failure | No intentional failure; caller keeps source layout alive. |
| cost | O(1), no allocation. |
| Design | [src/io/support.cpp](../../../../../src/io/support.cpp), [include/crown/io/support.hpp](../../../../../include/crown/io/support.hpp), [include/crown/runtime/support.hpp](../../../../../include/crown/runtime/support.hpp), [src/io/json.hpp](../../../../../src/io/json.hpp), [src/io/document.cpp](../../../../../src/io/document.cpp), [src/storage/layout.cpp](../../../../../src/storage/layout.cpp), [src/storage/accounted_layout.cpp](../../../../../src/storage/accounted_layout.cpp), [src/catalog/catalog.cpp](../../../../../src/catalog/catalog.cpp), [include/crown/storage/tuple_values.hpp](../../../../../include/crown/storage/tuple_values.hpp), [docs/support_invariants.md](../../../../support_invariants.md), [docs/code_review.md](../../../../code_review.md) |

## B0003

[Lines 9–9](../../../../../src/io/support.cpp#L9); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
storage::TupleLayout readable(const storage::AccountedLayout& layout){return layout.descriptor();}
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Retain the actual native descriptor behind an AccountedLayout for readable validation. |
| inputs / outputs | Valid AccountedLayout in; TupleLayout handle returned by descriptor(). |
| invariants | Returned descriptor shares the actual immutable native Data/factory; no independent recompiled token or deep metadata copy. |
| ownership | Shared owner retention; releasing this local handle decrements refcount, last-owner teardown follows actual descriptor graph. |
| failure | Moved-from/native required() can reject; successful descriptor handle creation requests no payload allocation. |
| cost | O(1) shared handle creation/release; no fields/binding copy. |
| Design | [src/io/support.cpp](../../../../../src/io/support.cpp), [include/crown/io/support.hpp](../../../../../include/crown/io/support.hpp), [include/crown/runtime/support.hpp](../../../../../include/crown/runtime/support.hpp), [src/io/json.hpp](../../../../../src/io/json.hpp), [src/io/document.cpp](../../../../../src/io/document.cpp), [src/storage/layout.cpp](../../../../../src/storage/layout.cpp), [src/storage/accounted_layout.cpp](../../../../../src/storage/accounted_layout.cpp), [src/catalog/catalog.cpp](../../../../../src/catalog/catalog.cpp), [include/crown/storage/tuple_values.hpp](../../../../../include/crown/storage/tuple_values.hpp), [docs/support_invariants.md](../../../../support_invariants.md), [docs/code_review.md](../../../../code_review.md) |

## B0004

[Lines 10–10](../../../../../src/io/support.cpp#L10); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Json row(storage::RowView values) { auto output=Json::array(); for (const auto& value : values.cells()) output.push_back(write_scalar_view(value)); return output; }
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Export RowView scalar values into an ordinary owning array. |
| inputs / outputs | Read-only row view in; each cell converted with write_scalar_view, returns Json array. |
| invariants | No layout/sequence/native authority check; typed scalar accessor/serializer supplies value representation. |
| ownership | RowView borrows backing; TupleValuesView may retain its tuple payload or borrow explicit source. Output DOM deep-copies scalar strings and tagged text. |
| failure | Invalid scalar/view/DOM/OOM failure propagates without changing input. |
| cost | O(fields+scalar bytes) traversal/copy and array growth; date/decimal formatting adds text work/storage. |
| Design | [src/io/support.cpp](../../../../../src/io/support.cpp), [include/crown/io/support.hpp](../../../../../include/crown/io/support.hpp), [include/crown/runtime/support.hpp](../../../../../include/crown/runtime/support.hpp), [src/io/json.hpp](../../../../../src/io/json.hpp), [src/io/document.cpp](../../../../../src/io/document.cpp), [src/storage/layout.cpp](../../../../../src/storage/layout.cpp), [src/storage/accounted_layout.cpp](../../../../../src/storage/accounted_layout.cpp), [src/catalog/catalog.cpp](../../../../../src/catalog/catalog.cpp), [include/crown/storage/tuple_values.hpp](../../../../../include/crown/storage/tuple_values.hpp), [docs/support_invariants.md](../../../../support_invariants.md), [docs/code_review.md](../../../../code_review.md) |

## B0005

[Lines 11–11](../../../../../src/io/support.cpp#L11); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Json row(storage::TupleValuesView values) { auto output=Json::array(); for (const auto& value : values) output.push_back(write_scalar_view(value)); return output; }
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Export TupleValuesView scalar values into an ordinary owning array. |
| inputs / outputs | Read-only row view in; each cell converted with write_scalar_view, returns Json array. |
| invariants | No layout/sequence/native authority check; typed scalar accessor/serializer supplies value representation. |
| ownership | RowView borrows backing; TupleValuesView may retain its tuple payload or borrow explicit source. Output DOM deep-copies scalar strings and tagged text. |
| failure | Invalid scalar/view/DOM/OOM failure propagates without changing input. |
| cost | O(fields+scalar bytes) traversal/copy and array growth; date/decimal formatting adds text work/storage. |
| Design | [src/io/support.cpp](../../../../../src/io/support.cpp), [include/crown/io/support.hpp](../../../../../include/crown/io/support.hpp), [include/crown/runtime/support.hpp](../../../../../include/crown/runtime/support.hpp), [src/io/json.hpp](../../../../../src/io/json.hpp), [src/io/document.cpp](../../../../../src/io/document.cpp), [src/storage/layout.cpp](../../../../../src/storage/layout.cpp), [src/storage/accounted_layout.cpp](../../../../../src/storage/accounted_layout.cpp), [src/catalog/catalog.cpp](../../../../../src/catalog/catalog.cpp), [include/crown/storage/tuple_values.hpp](../../../../../include/crown/storage/tuple_values.hpp), [docs/support_invariants.md](../../../../support_invariants.md), [docs/code_review.md](../../../../code_review.md) |

## B0006

[Lines 12–20](../../../../../src/io/support.cpp#L12); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::string role(runtime::SupportRole role) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Name SupportRole for a logical-support diagnostic. |
| inputs / outputs | Enum in; owning ordinary std::string with records/survivors/parent_support/visible label out. |
| invariants | Unknown alternative rejects rather than assigning a valid fallback. |
| ownership | String owns bytes; short-string optimization is not a semantic allocation guarantee. |
| failure | Unknown enum throws runtime_contract; string/Error allocation can fail. |
| cost | Fixed switch plus O(label bytes) string construction. |
| Design | [src/io/support.cpp](../../../../../src/io/support.cpp), [include/crown/io/support.hpp](../../../../../include/crown/io/support.hpp), [include/crown/runtime/support.hpp](../../../../../include/crown/runtime/support.hpp), [src/io/json.hpp](../../../../../src/io/json.hpp), [src/io/document.cpp](../../../../../src/io/document.cpp), [src/storage/layout.cpp](../../../../../src/storage/layout.cpp), [src/storage/accounted_layout.cpp](../../../../../src/storage/accounted_layout.cpp), [src/catalog/catalog.cpp](../../../../../src/catalog/catalog.cpp), [include/crown/storage/tuple_values.hpp](../../../../../include/crown/storage/tuple_values.hpp), [docs/support_invariants.md](../../../../support_invariants.md), [docs/code_review.md](../../../../code_review.md) |

## B0007

[Lines 21–23](../../../../../src/io/support.cpp#L21); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Json handle(runtime::SupportHandle value) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Export the descriptive coordinates of one support handle. |
| inputs / outputs | SupportHandle value in; owner/node/role/tuple DOM out. |
| invariants | Numeric owner/tuple labels do not retain backing or prove that a handle is live/current; actual runtime accessor gates remain separate. |
| ownership | Fixed source coordinates copied into owning ordinary object; role string is temporary. |
| failure | Unknown role/DOM allocation failure propagates. |
| cost | Fixed fields/label cost; ordinary DOM object can allocate. |
| Design | [src/io/support.cpp](../../../../../src/io/support.cpp), [include/crown/io/support.hpp](../../../../../include/crown/io/support.hpp), [include/crown/runtime/support.hpp](../../../../../include/crown/runtime/support.hpp), [src/io/json.hpp](../../../../../src/io/json.hpp), [src/io/document.cpp](../../../../../src/io/document.cpp), [src/storage/layout.cpp](../../../../../src/storage/layout.cpp), [src/storage/accounted_layout.cpp](../../../../../src/storage/accounted_layout.cpp), [src/catalog/catalog.cpp](../../../../../src/catalog/catalog.cpp), [include/crown/storage/tuple_values.hpp](../../../../../include/crown/storage/tuple_values.hpp), [docs/support_invariants.md](../../../../support_invariants.md), [docs/code_review.md](../../../../code_review.md) |

## B0008

[Lines 24–30](../../../../../src/io/support.cpp#L24); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::string operation(SetOperation operation) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Name SetOperation for a logical-support diagnostic. |
| inputs / outputs | Enum in; owning ordinary std::string with insert/erase label out. |
| invariants | Unknown alternative rejects rather than assigning a valid fallback. |
| ownership | String owns bytes; short-string optimization is not a semantic allocation guarantee. |
| failure | Unknown enum throws runtime_contract; string/Error allocation can fail. |
| cost | Fixed switch plus O(label bytes) string construction. |
| Design | [src/io/support.cpp](../../../../../src/io/support.cpp), [include/crown/io/support.hpp](../../../../../include/crown/io/support.hpp), [include/crown/runtime/support.hpp](../../../../../include/crown/runtime/support.hpp), [src/io/json.hpp](../../../../../src/io/json.hpp), [src/io/document.cpp](../../../../../src/io/document.cpp), [src/storage/layout.cpp](../../../../../src/storage/layout.cpp), [src/storage/accounted_layout.cpp](../../../../../src/storage/accounted_layout.cpp), [src/catalog/catalog.cpp](../../../../../src/catalog/catalog.cpp), [include/crown/storage/tuple_values.hpp](../../../../../include/crown/storage/tuple_values.hpp), [docs/support_invariants.md](../../../../support_invariants.md), [docs/code_review.md](../../../../code_review.md) |

## B0009

[Lines 31–37](../../../../../src/io/support.cpp#L31); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::string event_kind(runtime::SupportEventKind kind) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Name SupportEventKind for a logical-support diagnostic. |
| inputs / outputs | Enum in; owning ordinary std::string with native_update/child_key label out. |
| invariants | Unknown alternative rejects rather than assigning a valid fallback. |
| ownership | String owns bytes; short-string optimization is not a semantic allocation guarantee. |
| failure | Unknown enum throws runtime_contract; string/Error allocation can fail. |
| cost | Fixed switch plus O(label bytes) string construction. |
| Design | [src/io/support.cpp](../../../../../src/io/support.cpp), [include/crown/io/support.hpp](../../../../../include/crown/io/support.hpp), [include/crown/runtime/support.hpp](../../../../../include/crown/runtime/support.hpp), [src/io/json.hpp](../../../../../src/io/json.hpp), [src/io/document.cpp](../../../../../src/io/document.cpp), [src/storage/layout.cpp](../../../../../src/storage/layout.cpp), [src/storage/accounted_layout.cpp](../../../../../src/storage/accounted_layout.cpp), [src/catalog/catalog.cpp](../../../../../src/catalog/catalog.cpp), [include/crown/storage/tuple_values.hpp](../../../../../include/crown/storage/tuple_values.hpp), [docs/support_invariants.md](../../../../support_invariants.md), [docs/code_review.md](../../../../code_review.md) |

## B0010

[Lines 38–43](../../../../../src/io/support.cpp#L38); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Json value_state(const runtime::SupportValueState& value) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Encode recorded before/after membership and optional support facts. |
| inputs / outputs | SupportValueState in; member/satisfied_children/child_present/support DOM out. |
| invariants | Reports snapshot fields, without recomputing support counts or child satisfaction. |
| ownership | child_present Boolean vector is deep-copied into ordinary DOM array; optional counters copied inline. |
| failure | DOM allocation failure propagates. |
| cost | O(child flag count) copy plus fixed scalar fields; not universally fixed-size or allocation-free. |
| Design | [src/io/support.cpp](../../../../../src/io/support.cpp), [include/crown/io/support.hpp](../../../../../include/crown/io/support.hpp), [include/crown/runtime/support.hpp](../../../../../include/crown/runtime/support.hpp), [src/io/json.hpp](../../../../../src/io/json.hpp), [src/io/document.cpp](../../../../../src/io/document.cpp), [src/storage/layout.cpp](../../../../../src/storage/layout.cpp), [src/storage/accounted_layout.cpp](../../../../../src/storage/accounted_layout.cpp), [src/catalog/catalog.cpp](../../../../../src/catalog/catalog.cpp), [include/crown/storage/tuple_values.hpp](../../../../../include/crown/storage/tuple_values.hpp), [docs/support_invariants.md](../../../../support_invariants.md), [docs/code_review.md](../../../../code_review.md) |

## B0011

[Lines 44–56](../../../../../src/io/support.cpp#L44); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Json journal(const runtime::SupportJournal& value) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Export complete retained support undo records and causal events. |
| inputs / outputs | SupportJournal in; sequence/records/events DOM out. |
| invariants | Uses each recorded tuple/key and before/after facts; numeric cause/handle labels do not restore a journal or grant rollback authority. |
| ownership | Journal borrowed; DOM independently owns row/string/flag copies. record.tuple() and event.key.values() may retain existing immutable tuple backing while exporting. |
| failure | Tuple/enum/scalar/DOM errors propagate; journal/runtime unchanged. |
| cost | O(records+events+all tuple/key cells/text+before/after child flags) DOM copies; repeated values encoded repeatedly. |
| Design | [src/io/support.cpp](../../../../../src/io/support.cpp), [include/crown/io/support.hpp](../../../../../include/crown/io/support.hpp), [include/crown/runtime/support.hpp](../../../../../include/crown/runtime/support.hpp), [src/io/json.hpp](../../../../../src/io/json.hpp), [src/io/document.cpp](../../../../../src/io/document.cpp), [src/storage/layout.cpp](../../../../../src/storage/layout.cpp), [src/storage/accounted_layout.cpp](../../../../../src/storage/accounted_layout.cpp), [src/catalog/catalog.cpp](../../../../../src/catalog/catalog.cpp), [include/crown/storage/tuple_values.hpp](../../../../../include/crown/storage/tuple_values.hpp), [docs/support_invariants.md](../../../../support_invariants.md), [docs/code_review.md](../../../../code_review.md) |

```text
for (const auto& record : value.records) records.push_back({{"ordinal",record.ordinal},{"cause",record.cause},
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Export each recorded support journal mutation with its retained tuple and before/after state. |
| inputs / outputs | Journal records iterated into records DOM array. |
| invariants | record.tuple() accessor supplies actual retained values; serialized handle/ordinal/cause does not itself grant rollback authority. |
| ownership | Borrowed journal/tuple view; ordinary DOM deep-copies rows/strings/child flags. |
| failure | Tuple/accessor/role/scalar/DOM errors propagate; journal unchanged. |
| cost | O(records+all record row fields/text+before/after flag counts), allocating result. |
| Design | [src/io/support.cpp](../../../../../src/io/support.cpp), [include/crown/runtime/support.hpp](../../../../../include/crown/runtime/support.hpp), [src/io/document.cpp](../../../../../src/io/document.cpp), [docs/code_review.md](../../../../code_review.md) |

```text
for (const auto& event : value.events) events.push_back({{"id",event.id},{"cause",event.cause},
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Export each causal support event in existing journal order. |
| inputs / outputs | Journal events iterated; IDs/source/operation/target/key/before/after copied into DOM. |
| invariants | No event application/reordering or verification occurs here. |
| ownership | Borrowed event key/handle; DOM owns row/scalar copies. |
| failure | Enum/scalar/DOM failures propagate. |
| cost | O(events+event key fields/bytes), ordinary DOM growth. |
| Design | [src/io/support.cpp](../../../../../src/io/support.cpp), [include/crown/runtime/support.hpp](../../../../../include/crown/runtime/support.hpp), [src/io/document.cpp](../../../../../src/io/document.cpp), [docs/code_review.md](../../../../code_review.md) |

## B0012

[Lines 57–61](../../../../../src/io/support.cpp#L57); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Json keys(const std::vector<runtime::ProjectionKeySnapshot>& values) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Export projection-key support/count/handle snapshots. |
| inputs / outputs | ProjectionKeySnapshot vector in; owning array of key/support/handle objects out. |
| invariants | No re-probe/recomputation of support membership or handle validity. |
| ownership | Snapshot tuples retained by caller; DOM owns fresh scalar/string copies. |
| failure | Tuple/scalar/role/DOM failure propagates. |
| cost | O(keys+key cell/text bytes) array/object/scalar allocation. |
| Design | [src/io/support.cpp](../../../../../src/io/support.cpp), [include/crown/io/support.hpp](../../../../../include/crown/io/support.hpp), [include/crown/runtime/support.hpp](../../../../../include/crown/runtime/support.hpp), [src/io/json.hpp](../../../../../src/io/json.hpp), [src/io/document.cpp](../../../../../src/io/document.cpp), [src/storage/layout.cpp](../../../../../src/storage/layout.cpp), [src/storage/accounted_layout.cpp](../../../../../src/storage/accounted_layout.cpp), [src/catalog/catalog.cpp](../../../../../src/catalog/catalog.cpp), [include/crown/storage/tuple_values.hpp](../../../../../include/crown/storage/tuple_values.hpp), [docs/support_invariants.md](../../../../support_invariants.md), [docs/code_review.md](../../../../code_review.md) |

## B0013

[Lines 62–62](../../../../../src/io/support.cpp#L62); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L62-L62:sha256:c7bfe2f3de133d78a2bc8bb1c4a08450563986ee8254facee698e1dcc57e8162
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Closes the anonymous namespace at this source boundary; this is a lexical delimiter, not an operation. |
| inputs / outputs | No runtime input or output. Declarations following the span leave the preceding C++ scope. |
| invariants | The delimiter ends the preceding scope's visibility/linkage region; it adds no validation, publication, ownership transfer, or runtime authority. |
| ownership | The delimiter adds no owner. If it ends a function/block with live automatic objects, their normal destructors release those objects; namespace and type-definition closes change no existing object's lifetime. |
| failure | No explicit failure translation or catch is added. If a function/block exit destroys automatic objects, exception behavior follows those destructors; namespace/type closes have no runtime failure path. |
| cost | The delimiter adds no algorithmic work. A function/block exit can run existing automatic-object destructors and cleanup; namespace/type closes have no runtime cost. |
| Design | [src/io/support.cpp](../../../../../src/io/support.cpp), [docs/code_specs/files/src/io/support.cpp.md](support.cpp.md), [docs/support_invariants.md](../../../../support_invariants.md), [docs/runtime_support.md](../../../../runtime_support.md) |

## B0014

[Lines 63–103](../../../../../src/io/support.cpp#L63); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
template<class Plan> SupportTrace read_support_trace_impl(std::string_view text,const Plan& plan,std::size_t max_updates) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Read a bounded diagnostic logical-native update trace against the supplied plan layouts. |
| inputs / outputs | Text/PhysicalPlan or CompiledProgram/max_updates in; owning SupportTrace with options/NativeSetUpdate vector out. |
| invariants | DOM is fully parsed before update-count check. Optional work/support/order/capture/memory values are exact-shaped; support_limit must be positive; updates contiguous from1 and target an actual native node; layout.validate checks types/domains/equalities. This is not physical source/checkpoint replay. |
| ownership | Owns ordinary DOM, copied tree-name map and Row/Value update vector. Native plan descriptor adapter shares metadata only; it calls validate(values), NOT tuple(), so trace rows remain ordinary DTO ownership. |
| failure | Parse/shape/options/sequence/node/row/OOM errors abort private trace. No runtime update, progress acceptance or native row ownership is published. |
| cost | Full DOM parse; O(nodes log nodes+name bytes) ordinary map; each update O(log nodes name comparison+row parsing+layout fields/repeated-value bytes), vector/row/string allocations outside support work_limit. Decimal domain checks additionally format ordinary temporary canonical text. |
| Design | [src/io/support.cpp](../../../../../src/io/support.cpp), [include/crown/io/support.hpp](../../../../../include/crown/io/support.hpp), [include/crown/runtime/support.hpp](../../../../../include/crown/runtime/support.hpp), [src/io/json.hpp](../../../../../src/io/json.hpp), [src/io/document.cpp](../../../../../src/io/document.cpp), [src/storage/layout.cpp](../../../../../src/storage/layout.cpp), [src/storage/accounted_layout.cpp](../../../../../src/storage/accounted_layout.cpp), [src/catalog/catalog.cpp](../../../../../src/catalog/catalog.cpp), [include/crown/storage/tuple_values.hpp](../../../../../include/crown/storage/tuple_values.hpp), [docs/support_invariants.md](../../../../support_invariants.md), [docs/code_review.md](../../../../code_review.md) |

```text
if (input.contains("options")) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Read only explicit optional support diagnostic options. |
| inputs / outputs | options object in; mutates local SupportTrace options defaults for present supported keys. |
| invariants | work_limit may be null; support_limit&gt;0; order exactly fifo/lifo; capture_transitions Boolean; memory_limit uint64. These values do not retroactively fund/bound this ordinary DOM/trace import. |
| ownership | Local options own fixed fields; temporary order string is ordinary allocation. |
| failure | Invalid type/shape/range/order rejects before updates are returned. |
| cost | Fixed field checks/string copy; no native runtime creation. |
| Design | [src/io/support.cpp](../../../../../src/io/support.cpp), [include/crown/io/support.hpp](../../../../../include/crown/io/support.hpp), [include/crown/runtime/support.hpp](../../../../../include/crown/runtime/support.hpp), [src/io/json.hpp](../../../../../src/io/json.hpp), [src/io/document.cpp](../../../../../src/io/document.cpp), [src/storage/layout.cpp](../../../../../src/storage/layout.cpp), [src/storage/accounted_layout.cpp](../../../../../src/storage/accounted_layout.cpp), [src/catalog/catalog.cpp](../../../../../src/catalog/catalog.cpp), [include/crown/storage/tuple_values.hpp](../../../../../include/crown/storage/tuple_values.hpp), [docs/support_invariants.md](../../../../support_invariants.md), [docs/code_review.md](../../../../code_review.md) |

```text
std::map<std::string,NodeId> nodes;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Index plan node names for diagnostic update resolution. |
| inputs / outputs | Borrowed plan tree in; local std::map&lt;string,NodeId&gt; built in node order. |
| invariants | Plan factory supplies unique consistent node IDs; name map does not itself prove tree validity. |
| ownership | Ordinary map deep-copies node names; independent of native descriptor account. |
| failure | Map/name allocation failure aborts private trace; original plan unchanged. |
| cost | O(N log N) comparisons plus name-byte copies and N ordinary nodes. |
| Design | [src/io/support.cpp](../../../../../src/io/support.cpp), [include/crown/io/support.hpp](../../../../../include/crown/io/support.hpp), [include/crown/runtime/support.hpp](../../../../../include/crown/runtime/support.hpp), [src/io/json.hpp](../../../../../src/io/json.hpp), [src/io/document.cpp](../../../../../src/io/document.cpp), [src/storage/layout.cpp](../../../../../src/storage/layout.cpp), [src/storage/accounted_layout.cpp](../../../../../src/storage/accounted_layout.cpp), [src/catalog/catalog.cpp](../../../../../src/catalog/catalog.cpp), [include/crown/storage/tuple_values.hpp](../../../../../include/crown/storage/tuple_values.hpp), [docs/support_invariants.md](../../../../support_invariants.md), [docs/code_review.md](../../../../code_review.md) |

```text
for (const auto& update : updates) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Parse, order-check and validate each logical diagnostic row before retaining it. |
| inputs / outputs | DOM updates in; sequence/native name/insert-or-erase/typed Row reconstructed and moved into trace. |
| invariants | Sequence must equal current trace size+1; native node check precedes layout.validate; validation includes repeated-variable equality, not a runtime set transition. |
| ownership | Ordinary Row owns scalar/string payload; readable native descriptor only shares actual layout metadata for synchronous validation. |
| failure | Any row/type/domain/OOM failure discards partial local trace; does not fail or mutate a live SupportRuntime. |
| cost | Name lookup O(log N) with byte comparisons, parse O(fields+payload bytes), validate O(fields+equality value bytes), ordinary vector growth. |
| Design | [src/io/support.cpp](../../../../../src/io/support.cpp), [include/crown/io/support.hpp](../../../../../include/crown/io/support.hpp), [include/crown/runtime/support.hpp](../../../../../include/crown/runtime/support.hpp), [src/io/json.hpp](../../../../../src/io/json.hpp), [src/io/document.cpp](../../../../../src/io/document.cpp), [src/storage/layout.cpp](../../../../../src/storage/layout.cpp), [src/storage/accounted_layout.cpp](../../../../../src/storage/accounted_layout.cpp), [src/catalog/catalog.cpp](../../../../../src/catalog/catalog.cpp), [include/crown/storage/tuple_values.hpp](../../../../../include/crown/storage/tuple_values.hpp), [docs/support_invariants.md](../../../../support_invariants.md), [docs/code_review.md](../../../../code_review.md) |

## B0015

[Lines 104–104](../../../../../src/io/support.cpp#L104); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
SupportTrace read_support_trace(std::string_view text,const PhysicalPlan& plan,std::size_t max_updates){return read_support_trace_impl(text,plan,max_updates);}
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Import the logical diagnostic trace for PhysicalPlan through the shared validation path. |
| inputs / outputs | Borrowed text/plan and max_updates in; owning SupportTrace out. |
| invariants | No implicit physical ingestion, runtime factory or durable acceptance; target node/layout must match actual supplied plan. |
| ownership | Trace owns ordinary Rows/options/vector; PhysicalPlan remains borrowed, native descriptors can be shared by the readable adapter during validation only. |
| failure | Callee parsing/validation/OOM failures propagate unchanged; no catch. |
| cost | Full shared import cost: DOM, node-name map, per-update scalar and layout scans, ordinary row/string allocations. |
| Design | [src/io/support.cpp](../../../../../src/io/support.cpp), [include/crown/io/support.hpp](../../../../../include/crown/io/support.hpp), [include/crown/runtime/support.hpp](../../../../../include/crown/runtime/support.hpp), [src/io/json.hpp](../../../../../src/io/json.hpp), [src/io/document.cpp](../../../../../src/io/document.cpp), [src/storage/layout.cpp](../../../../../src/storage/layout.cpp), [src/storage/accounted_layout.cpp](../../../../../src/storage/accounted_layout.cpp), [src/catalog/catalog.cpp](../../../../../src/catalog/catalog.cpp), [include/crown/storage/tuple_values.hpp](../../../../../include/crown/storage/tuple_values.hpp), [docs/support_invariants.md](../../../../support_invariants.md), [docs/code_review.md](../../../../code_review.md) |

## B0016

[Lines 105–105](../../../../../src/io/support.cpp#L105); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
SupportTrace read_support_trace(std::string_view text,const CompiledProgram& plan,std::size_t max_updates){return read_support_trace_impl(text,plan,max_updates);}
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Import the logical diagnostic trace for CompiledProgram through the shared validation path. |
| inputs / outputs | Borrowed text/plan and max_updates in; owning SupportTrace out. |
| invariants | No implicit physical ingestion, runtime factory or durable acceptance; target node/layout must match actual supplied plan. |
| ownership | Trace owns ordinary Rows/options/vector; CompiledProgram remains borrowed, native descriptors can be shared by the readable adapter during validation only. |
| failure | Callee parsing/validation/OOM failures propagate unchanged; no catch. |
| cost | Full shared import cost: DOM, node-name map, per-update scalar and layout scans, ordinary row/string allocations. |
| Design | [src/io/support.cpp](../../../../../src/io/support.cpp), [include/crown/io/support.hpp](../../../../../include/crown/io/support.hpp), [include/crown/runtime/support.hpp](../../../../../include/crown/runtime/support.hpp), [src/io/json.hpp](../../../../../src/io/json.hpp), [src/io/document.cpp](../../../../../src/io/document.cpp), [src/storage/layout.cpp](../../../../../src/storage/layout.cpp), [src/storage/accounted_layout.cpp](../../../../../src/storage/accounted_layout.cpp), [src/catalog/catalog.cpp](../../../../../src/catalog/catalog.cpp), [include/crown/storage/tuple_values.hpp](../../../../../include/crown/storage/tuple_values.hpp), [docs/support_invariants.md](../../../../support_invariants.md), [docs/code_review.md](../../../../code_review.md) |

## B0018

[Lines 107–113](../../../../../src/io/support.cpp#L107); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Json write_support_options(const runtime::SupportOptions& options) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Export recorded support policy with an optional nondefault memory ceiling. |
| inputs / outputs | SupportOptions in; owning work/support/order/capture and optionally memory_limit_bytes DOM out. |
| invariants | Existing order mapping is fifo versus else-lifo; writer does not independently validate arbitrary enum edits. Default memory ceiling omitted canonically. |
| ownership | Borrowed fixed options; owning ordinary DOM result. |
| failure | DOM allocation failure propagates. |
| cost | Fixed fields and nullable numeric values, ordinary object allocation. |
| Design | [src/io/support.cpp](../../../../../src/io/support.cpp), [include/crown/io/support.hpp](../../../../../include/crown/io/support.hpp), [include/crown/runtime/support.hpp](../../../../../include/crown/runtime/support.hpp), [src/io/json.hpp](../../../../../src/io/json.hpp), [src/io/document.cpp](../../../../../src/io/document.cpp), [src/storage/layout.cpp](../../../../../src/storage/layout.cpp), [src/storage/accounted_layout.cpp](../../../../../src/storage/accounted_layout.cpp), [src/catalog/catalog.cpp](../../../../../src/catalog/catalog.cpp), [include/crown/storage/tuple_values.hpp](../../../../../include/crown/storage/tuple_values.hpp), [docs/support_invariants.md](../../../../support_invariants.md), [docs/code_review.md](../../../../code_review.md) |

## B0019

[Lines 114–126](../../../../../src/io/support.cpp#L114); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
template<class Plan> Json write_support_snapshot_impl(const runtime::SupportSnapshot& snapshot,const Plan& plan) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Export a support snapshot using matching plan node names. |
| inputs / outputs | SupportSnapshot and plan in; sequence/has_answer/nodes with records/survivors/keys DOM out. |
| invariants | plan.tree().nodes.at checks node index; supplied snapshot must belong to matching plan. Names/kinds/counters/handles are serialized diagnostics, not authority or a new invariant check. |
| ownership | Snapshot/plan borrowed; DOM deep-copies tuple/key/string/child-flag values; shared tuple views only retain existing backing during export. |
| failure | Node-range/tuple/role/scalar/DOM/OOM errors propagate; snapshot/runtime unchanged. |
| cost | Full nodes/records/survivors/parent and optional visible keys traversal, all scalar/flag bytes copied; no live runtime scan or sort here. |
| Design | [src/io/support.cpp](../../../../../src/io/support.cpp), [include/crown/io/support.hpp](../../../../../include/crown/io/support.hpp), [include/crown/runtime/support.hpp](../../../../../include/crown/runtime/support.hpp), [src/io/json.hpp](../../../../../src/io/json.hpp), [src/io/document.cpp](../../../../../src/io/document.cpp), [src/storage/layout.cpp](../../../../../src/storage/layout.cpp), [src/storage/accounted_layout.cpp](../../../../../src/storage/accounted_layout.cpp), [src/catalog/catalog.cpp](../../../../../src/catalog/catalog.cpp), [include/crown/storage/tuple_values.hpp](../../../../../include/crown/storage/tuple_values.hpp), [docs/support_invariants.md](../../../../support_invariants.md), [docs/code_review.md](../../../../code_review.md) |

```text
for (const auto& node : snapshot.nodes) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Encode each snapshot node using the supplied plan label and retained tuples. |
| inputs / outputs | Node snapshot in; record/survivor/key arrays built and appended to local nodes. |
| invariants | .at enforces addressability only; caller must pair snapshot with matching actual plan. |
| ownership | Node/plan/tuples borrowed; DOM owns copied values/flags/names. |
| failure | Node index/tuple/scalar/DOM errors abort enclosing writer. |
| cost | O(records+survivors+keys+all value/flag bytes) per node. |
| Design | [src/io/support.cpp](../../../../../src/io/support.cpp), [include/crown/runtime/support.hpp](../../../../../include/crown/runtime/support.hpp), [src/io/document.cpp](../../../../../src/io/document.cpp), [docs/code_review.md](../../../../code_review.md) |

## B0020

[Lines 127–127](../../../../../src/io/support.cpp#L127); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Json write_support_snapshot(const runtime::SupportSnapshot& snapshot,const PhysicalPlan& plan){return write_support_snapshot_impl(snapshot,plan);}
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Export matching support snapshot names/values for PhysicalPlan. |
| inputs / outputs | Snapshot/plan in; ordinary owning Json out through write_support_snapshot_impl. |
| invariants | Must provide matching plan; labels/IDs are diagnostic coordinates, not native proof or durable receipt. |
| ownership | Inputs borrowed; DOM owns copied row/text/flag graph. |
| failure | Shared serializer indexing/enum/scalar/OOM errors propagate. |
| cost | O(total snapshot records/keys/cells/bytes) serialization and ordinary allocation, not a constant shared-handle export. |
| Design | [src/io/support.cpp](../../../../../src/io/support.cpp), [include/crown/io/support.hpp](../../../../../include/crown/io/support.hpp), [include/crown/runtime/support.hpp](../../../../../include/crown/runtime/support.hpp), [src/io/json.hpp](../../../../../src/io/json.hpp), [src/io/document.cpp](../../../../../src/io/document.cpp), [src/storage/layout.cpp](../../../../../src/storage/layout.cpp), [src/storage/accounted_layout.cpp](../../../../../src/storage/accounted_layout.cpp), [src/catalog/catalog.cpp](../../../../../src/catalog/catalog.cpp), [include/crown/storage/tuple_values.hpp](../../../../../include/crown/storage/tuple_values.hpp), [docs/support_invariants.md](../../../../support_invariants.md), [docs/code_review.md](../../../../code_review.md) |

## B0021

[Lines 128–128](../../../../../src/io/support.cpp#L128); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Json write_support_snapshot(const runtime::SupportSnapshot& snapshot,const CompiledProgram& plan){return write_support_snapshot_impl(snapshot,plan);}
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Export matching support snapshot names/values for CompiledProgram. |
| inputs / outputs | Snapshot/plan in; ordinary owning Json out through write_support_snapshot_impl. |
| invariants | Must provide matching plan; labels/IDs are diagnostic coordinates, not native proof or durable receipt. |
| ownership | Inputs borrowed; DOM owns copied row/text/flag graph. |
| failure | Shared serializer indexing/enum/scalar/OOM errors propagate. |
| cost | O(total snapshot records/keys/cells/bytes) serialization and ordinary allocation, not a constant shared-handle export. |
| Design | [src/io/support.cpp](../../../../../src/io/support.cpp), [include/crown/io/support.hpp](../../../../../include/crown/io/support.hpp), [include/crown/runtime/support.hpp](../../../../../include/crown/runtime/support.hpp), [src/io/json.hpp](../../../../../src/io/json.hpp), [src/io/document.cpp](../../../../../src/io/document.cpp), [src/storage/layout.cpp](../../../../../src/storage/layout.cpp), [src/storage/accounted_layout.cpp](../../../../../src/storage/accounted_layout.cpp), [src/catalog/catalog.cpp](../../../../../src/catalog/catalog.cpp), [include/crown/storage/tuple_values.hpp](../../../../../include/crown/storage/tuple_values.hpp), [docs/support_invariants.md](../../../../support_invariants.md), [docs/code_review.md](../../../../code_review.md) |

## B0023

[Lines 130–147](../../../../../src/io/support.cpp#L130); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Json write_support_epoch(const runtime::SupportEpoch& epoch) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Export the recorded support epoch transitions, optional journal and fixed metrics. |
| inputs / outputs | SupportEpoch in; complete ordinary transition/journal/metrics DOM out. |
| invariants | native_changed/has_answer/metrics are already-recorded epoch facts; serializer does not apply the epoch or validate/replay rollback. Empty journal becomes null. |
| ownership | Input epoch/tuples borrowed; transitions DOM owns scalar/text copies. const retained_journal owns its full DOM, then initializer-list result copies it into final journal field; both coexist temporarily. |
| failure | Tuple/enum/scalar/DOM/allocation failure aborts return without changing epoch/runtime. |
| cost | O(transitions+all transition tuple bytes+journal records/events/flags/payload)+fixed metrics. Additional full journal DOM copy/peak is actual current code cost. |
| Design | [src/io/support.cpp](../../../../../src/io/support.cpp), [include/crown/io/support.hpp](../../../../../include/crown/io/support.hpp), [include/crown/runtime/support.hpp](../../../../../include/crown/runtime/support.hpp), [src/io/json.hpp](../../../../../src/io/json.hpp), [src/io/document.cpp](../../../../../src/io/document.cpp), [src/storage/layout.cpp](../../../../../src/storage/layout.cpp), [src/storage/accounted_layout.cpp](../../../../../src/storage/accounted_layout.cpp), [src/catalog/catalog.cpp](../../../../../src/catalog/catalog.cpp), [include/crown/storage/tuple_values.hpp](../../../../../include/crown/storage/tuple_values.hpp), [docs/support_invariants.md](../../../../support_invariants.md), [docs/code_review.md](../../../../code_review.md) |

```text
for (const auto& transition : epoch.transitions) transitions.push_back({{"cause",transition.cause},
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Encode recorded epoch transitions without applying them. |
| inputs / outputs | Transition vector iterated in existing order; cause/handle/operation/values copied into DOM. |
| invariants | Output transition list is a diagnostic artifact, not a live support journal or accepted source event. |
| ownership | Borrowed tuple view; ordinary DOM owns scalar/string array. |
| failure | Enum/scalar/DOM allocation failure propagates. |
| cost | O(transitions+tuple fields/bytes), with ordinary array/object allocation. |
| Design | [src/io/support.cpp](../../../../../src/io/support.cpp), [include/crown/runtime/support.hpp](../../../../../include/crown/runtime/support.hpp), [src/io/document.cpp](../../../../../src/io/document.cpp), [docs/code_review.md](../../../../code_review.md) |

```text
const Json retained_journal=epoch.journal ? journal(*epoch.journal) : Json(nullptr);
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Build an optional full journal DOM before inserting it into the final epoch artifact. |
| inputs / outputs | epoch.journal presence selects journal export or Json null; const local is later included by value in final initializer-list DOM. |
| invariants | Both encoded journal copies represent the same retained epoch state; no native rollback/receipt is produced. |
| ownership | Local const Json owns the full nested journal; final DOM copies it, causing a real transient duplicate graph. |
| failure | Initial encode or later copy OOM aborts epoch serialization; native journal unchanged. |
| cost | Full journal serialization plus another O(journal DOM size) deep copy; possible cleanup/copy allocation and peak explicitly excluded from update metrics. |
| Design | [src/io/support.cpp](../../../../../src/io/support.cpp), [include/crown/runtime/support.hpp](../../../../../include/crown/runtime/support.hpp), [src/io/document.cpp](../../../../../src/io/document.cpp), [docs/code_review.md](../../../../code_review.md) |

## B0024

[Lines 148–148](../../../../../src/io/support.cpp#L148); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L148-L148:sha256:a992a30ac7c9748c33994a213cb5eed12f62a6204d01f8b49f69db451a145039
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Closes the namespace crown::io at this source boundary; this is a lexical delimiter, not an operation. |
| inputs / outputs | No runtime input or output. Declarations following the span leave the preceding C++ scope. |
| invariants | The delimiter ends the preceding scope's visibility/linkage region; it adds no validation, publication, ownership transfer, or runtime authority. |
| ownership | The delimiter adds no owner. If it ends a function/block with live automatic objects, their normal destructors release those objects; namespace and type-definition closes change no existing object's lifetime. |
| failure | No explicit failure translation or catch is added. If a function/block exit destroys automatic objects, exception behavior follows those destructors; namespace/type closes have no runtime failure path. |
| cost | The delimiter adds no algorithmic work. A function/block exit can run existing automatic-object destructors and cleanup; namespace/type closes have no runtime cost. |
| Design | [src/io/support.cpp](../../../../../src/io/support.cpp), [docs/code_specs/files/src/io/support.cpp.md](support.cpp.md), [docs/support_invariants.md](../../../../support_invariants.md), [docs/runtime_support.md](../../../../runtime_support.md) |
