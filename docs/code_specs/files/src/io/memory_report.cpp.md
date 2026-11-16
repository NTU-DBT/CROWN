# `src/io/memory_report.cpp` — block usage map

[Source](../../../../../src/io/memory_report.cpp) · [Source index](../../../README.md) · [Subsystem contracts](../../../subsystem_contracts.md) · [Reviewed primitives](../../../primitives.md)

Serialize a retained native memory report into ordinary JSON without rescanning live accounts/tables.

Snapshot SHA-256: `8843a953171c9fa36459dbe561d417be4c28c79e517f6fa49dc6f9e6badc07dd`. 91 lines partitioned into 15 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [io](../../../subsystem_contracts.md#io). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/ingestion.md](../../../../ingestion.md), [docs/query_identity.md](../../../../query_identity.md), [docs/schema_evolution.md](../../../../schema_evolution.md), [docs/cli.md](../../../../cli.md), [docs/query_memory.md](../../../../query_memory.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–6](../../../../../src/io/memory_report.cpp#L1) | Imports dependencies; declares namespace scope; declares values/defaults or compile-time conditions. |  · [reviewed contract](#b0001) |
| [B0002 · 7–9](../../../../../src/io/memory_report.cpp#L7) | Callable definition: template&lt;class Enum,std::size_t N&gt; const char* name(Enum value,const std::array&lt;const char*,N&gt;& names) | calls Error; returns names\[i\] · [reviewed contract](#b0002) |
| [B0003 · 10–10](../../../../../src/io/memory_report.cpp#L10) | Callable definition: const char* layer(mm::Layer v) | calls name; returns name(v,std::array{@ ,@ ,@ ,@ }) · [reviewed contract](#b0003) |
| [B0004 · 11–11](../../../../../src/io/memory_report.cpp#L11) | Callable definition: Json usage(resource::MemoryUsage value) | calls ; returns {{@ ,value.allocations},{@ ,value.requested_bytes},{@ ,value.payload_bytes}} · [reviewed contract](#b0004) |
| [B0005 · 12–16](../../../../../src/io/memory_report.cpp#L12) | Callable definition: Json attribution(resource::MemoryAttribution value) | calls static_assert, size, name; guard static_assert(names.size()==static_cast&lt;std::size_t&gt;(resource::MemoryOwnerKind::count));; returns {{@ ,name(value.kind,names)},{@ ,value.id}} · [reviewed contract](#b0005) |
| [B0006 · 17–24](../../../../../src/io/memory_report.cpp#L17) | Callable definition: template&lt;class Statistics&gt; void categories(Json& out,const Statistics& value) | calls static_assert, size, Json::object, usage; guard static_assert(purposes.size()==resource::memory_purpose_count && lifetimes.size()==resource::alloca…; 2 loop sites · [reviewed contract](#b0006) |
| [B0007 · 25–27](../../../../../src/io/memory_report.cpp#L25) | Callable definition: Json owner(const resource::AttributedMemoryStatistics& value) | calls attribution, usage, categories; returns out · [reviewed contract](#b0007) |
| [B0008 · 28–32](../../../../../src/io/memory_report.cpp#L28) | Callable definition: Json account(const resource::MemoryStatistics& value) | calls usage, categories; returns out · [reviewed contract](#b0008) |
| [B0009 · 33–40](../../../../../src/io/memory_report.cpp#L33) | Callable definition: Json arena(const storage::ArenaMemoryStatistics& value) | calls owner, usage; returns {{@ ,{{@ ,r.slots},{@ ,r.live_records},{@ ,r.retained_records},{@ ,r.pins},{@ ,r.free_slots},{@ ,r.… · [reviewed contract](#b0009) |
| [B0010 · 41–41](../../../../../src/io/memory_report.cpp#L41) | Callable definition: template&lt;class Id&gt; Json optional_id(const std::optional&lt;Id&gt;& value) | calls Json; returns value?Json(value-&gt;value):Json(nullptr) · [reviewed contract](#b0010) |
| [B0011 · 42–60](../../../../../src/io/memory_report.cpp#L42) | Callable definition: Json table(const mm::Table& value) | calls name, optional_id, std::visit, owner; returns out · [reviewed contract](#b0011) |
| [B0012 · 61–74](../../../../../src/io/memory_report.cpp#L61) | Callable definition: Json operation(const mm::Operator& value) | calls std::visit, attribution, constexpr, update; returns std::visit(\[\](const auto& item) {; out · [reviewed contract](#b0012) |
| [B0013 · 75–75](../../../../../src/io/memory_report.cpp#L75) | Closes surrounding scope/type. |  · [reviewed contract](#b0013) |
| [B0014 · 76–90](../../../../../src/io/memory_report.cpp#L76) | Callable definition: Json write_memory_report(const runtime::memory::Report& report) | calls snapshot, usage, layer, name; returns out; growth push_back; 3 loop sites; source comment (unverified): // Export the retained sample into an ordinary DOM; this does not rescan the live account. · [reviewed contract](#b0014) |
| [B0015 · 91–91](../../../../../src/io/memory_report.cpp#L91) | Closes surrounding scope/type. | source comment (unverified): // namespace crown::io · [reviewed contract](#b0015) |

## B0001

[Lines 1–6](../../../../../src/io/memory_report.cpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
#include "crown/io/memory_report.hpp"
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Export an already captured native memory report into an ordinary owning diagnostic DOM. |
| inputs / outputs | Imports the declarations used by this translation unit/header; no runtime input or result. |
| invariants | Namespace/includes do not perform admission, validation, publication or IO. |
| ownership | Declarations give no ownership of caller records, source bytes or runtime accounts. |
| failure | Compile/link dependencies only; there is no executable failure boundary in these includes. |
| cost | Compile-time dependencies; later functions account for their own runtime work and storage. |
| Design | [src/io/memory_report.cpp](../../../../../src/io/memory_report.cpp), [include/crown/io/memory_report.hpp](../../../../../include/crown/io/memory_report.hpp), [include/crown/runtime/memory_report.hpp](../../../../../include/crown/runtime/memory_report.hpp), [src/runtime/memory_report.cpp](../../../../../src/runtime/memory_report.cpp), [include/crown/resource/memory.hpp](../../../../../include/crown/resource/memory.hpp), [docs/memory_reports.md](../../../../memory_reports.md), [docs/code_review.md](../../../../code_review.md) |

## B0002

[Lines 7–9](../../../../../src/io/memory_report.cpp#L7); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
template<class Enum,std::size_t N> const char* name(Enum value,const std::array<const char*,N>& names) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Check an enum index before reading its stable memory-report label. |
| inputs / outputs | Enum and fixed label array in; const char* of static spelling out. |
| invariants | Out-of-range casts reject before indexing; this helper does not validate the rest of a report. |
| ownership | Borrowed static literals; no copied string on successful lookup. |
| failure | Unknown enum throws memory_report_encoding Error; error construction/unwind may allocate. |
| cost | O(1) bounds/index, no allocation on successful lookup. |
| Design | [src/io/memory_report.cpp](../../../../../src/io/memory_report.cpp), [include/crown/io/memory_report.hpp](../../../../../include/crown/io/memory_report.hpp), [include/crown/runtime/memory_report.hpp](../../../../../include/crown/runtime/memory_report.hpp), [src/runtime/memory_report.cpp](../../../../../src/runtime/memory_report.cpp), [include/crown/resource/memory.hpp](../../../../../include/crown/resource/memory.hpp), [docs/memory_reports.md](../../../../memory_reports.md), [docs/code_review.md](../../../../code_review.md) |

## B0003

[Lines 10–10](../../../../../src/io/memory_report.cpp#L10); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
const char* layer(mm::Layer v){return name(v,std::array{"support","physical","delta","session"});}
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Name the layer captured by the report. |
| inputs / outputs | Layer in; support/physical/delta/session static spelling out. |
| invariants | Delegates enum-domain check to name(). |
| ownership | Returns borrowed static bytes, no runtime owner. |
| failure | Unknown Layer rejects through memory_report_encoding. |
| cost | O(1) fixed label-array setup/lookup. |
| Design | [src/io/memory_report.cpp](../../../../../src/io/memory_report.cpp), [include/crown/io/memory_report.hpp](../../../../../include/crown/io/memory_report.hpp), [include/crown/runtime/memory_report.hpp](../../../../../include/crown/runtime/memory_report.hpp), [src/runtime/memory_report.cpp](../../../../../src/runtime/memory_report.cpp), [include/crown/resource/memory.hpp](../../../../../include/crown/resource/memory.hpp), [docs/memory_reports.md](../../../../memory_reports.md), [docs/code_review.md](../../../../code_review.md) |

## B0004

[Lines 11–11](../../../../../src/io/memory_report.cpp#L11); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Json usage(resource::MemoryUsage value){return {{"allocations",value.allocations},{"requested_bytes",value.requested_bytes},{"payload_bytes",value.payload_bytes}};}
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Convert one fixed allocation usage snapshot to an owned DOM object. |
| inputs / outputs | MemoryUsage scalar value in; allocations/requested_bytes/payload_bytes object out. |
| invariants | Copies recorded counts; does not query the ledger or recompute upstream framing. |
| ownership | Result has ordinary DOM object/node ownership; MemoryUsage itself is inline. |
| failure | DOM allocation failure propagates. |
| cost | Fixed three-field object; O(1) fields but allocating ordinary DOM storage. |
| Design | [src/io/memory_report.cpp](../../../../../src/io/memory_report.cpp), [include/crown/io/memory_report.hpp](../../../../../include/crown/io/memory_report.hpp), [include/crown/runtime/memory_report.hpp](../../../../../include/crown/runtime/memory_report.hpp), [src/runtime/memory_report.cpp](../../../../../src/runtime/memory_report.cpp), [include/crown/resource/memory.hpp](../../../../../include/crown/resource/memory.hpp), [docs/memory_reports.md](../../../../memory_reports.md), [docs/code_review.md](../../../../code_review.md) |

## B0005

[Lines 12–16](../../../../../src/io/memory_report.cpp#L12); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Json attribution(resource::MemoryAttribution value) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Encode a recorded immutable attribution kind and id. |
| inputs / outputs | MemoryAttribution in; kind/id object out. |
| invariants | Compile-time label count matches MemoryOwnerKind::count; runtime kind is range-checked by name(). |
| ownership | Static labels borrowed then copied into owning ordinary DOM. |
| failure | Unknown kind or DOM allocation rejects; original report unaffected. |
| cost | Fixed fields/lookup with ordinary object/string allocation. |
| Design | [src/io/memory_report.cpp](../../../../../src/io/memory_report.cpp), [include/crown/io/memory_report.hpp](../../../../../include/crown/io/memory_report.hpp), [include/crown/runtime/memory_report.hpp](../../../../../include/crown/runtime/memory_report.hpp), [src/runtime/memory_report.cpp](../../../../../src/runtime/memory_report.cpp), [include/crown/resource/memory.hpp](../../../../../include/crown/resource/memory.hpp), [docs/memory_reports.md](../../../../memory_reports.md), [docs/code_review.md](../../../../code_review.md) |

## B0006

[Lines 17–24](../../../../../src/io/memory_report.cpp#L17); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
template<class Statistics> void categories(Json& out,const Statistics& value) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Attach each fixed purpose and lifetime partition to a DOM record. |
| inputs / outputs | Mutable local out and statistics with fixed by_purpose/by_lifetime arrays in; writes new partition objects. |
| invariants | Compile-time array extents agree with enum counts; partitions are already-recorded usage, not a fresh scan/reconciliation. |
| ownership | DOM owns all label keys and nested usage objects; input fixed arrays borrowed. |
| failure | Allocation can leave local out partially built; top-level output is returned only when complete. |
| cost | Exactly memory_purpose_count+allocation_lifetime_count usage conversions; fixed per report row, ordinary DOM allocations. |
| Design | [src/io/memory_report.cpp](../../../../../src/io/memory_report.cpp), [include/crown/io/memory_report.hpp](../../../../../include/crown/io/memory_report.hpp), [include/crown/runtime/memory_report.hpp](../../../../../include/crown/runtime/memory_report.hpp), [src/runtime/memory_report.cpp](../../../../../src/runtime/memory_report.cpp), [include/crown/resource/memory.hpp](../../../../../include/crown/resource/memory.hpp), [docs/memory_reports.md](../../../../memory_reports.md), [docs/code_review.md](../../../../code_review.md) |

## B0007

[Lines 25–27](../../../../../src/io/memory_report.cpp#L25); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Json owner(const resource::AttributedMemoryStatistics& value) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Serialize one attributed account-owner partition. |
| inputs / outputs | AttributedMemoryStatistics in; account/attribution/current plus category objects out. |
| invariants | Owner usage belongs to the recorded whole account; not a process/RSS or only-current-runtime measurement. |
| ownership | Borrows fixed statistics; owns ordinary DOM output. |
| failure | Attribution/DOM errors propagate without resampling or changing ledger state. |
| cost | Fixed category loop/object allocations, no ledger traversal here. |
| Design | [src/io/memory_report.cpp](../../../../../src/io/memory_report.cpp), [include/crown/io/memory_report.hpp](../../../../../include/crown/io/memory_report.hpp), [include/crown/runtime/memory_report.hpp](../../../../../include/crown/runtime/memory_report.hpp), [src/runtime/memory_report.cpp](../../../../../src/runtime/memory_report.cpp), [include/crown/resource/memory.hpp](../../../../../include/crown/resource/memory.hpp), [docs/memory_reports.md](../../../../memory_reports.md), [docs/code_review.md](../../../../code_review.md) |

## B0008

[Lines 28–32](../../../../../src/io/memory_report.cpp#L28); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Json account(const resource::MemoryStatistics& value) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Serialize a fixed account-level memory snapshot. |
| inputs / outputs | MemoryStatistics in; owner/grant/current/peak/cumulative allocations/free counts and partitions out. |
| invariants | Peak is the captured account peak, not a measured per-serialization/phase CPU/byte peak. |
| ownership | Ordinary DOM owns the copied record; account controller is not retained by numeric owner label. |
| failure | DOM allocation failures propagate; snapshot untouched. |
| cost | Fixed field/category work and allocations; no live account scan. |
| Design | [src/io/memory_report.cpp](../../../../../src/io/memory_report.cpp), [include/crown/io/memory_report.hpp](../../../../../include/crown/io/memory_report.hpp), [include/crown/runtime/memory_report.hpp](../../../../../include/crown/runtime/memory_report.hpp), [src/runtime/memory_report.cpp](../../../../../src/runtime/memory_report.cpp), [include/crown/resource/memory.hpp](../../../../../include/crown/resource/memory.hpp), [docs/memory_reports.md](../../../../memory_reports.md), [docs/code_review.md](../../../../code_review.md) |

## B0009

[Lines 33–40](../../../../../src/io/memory_report.cpp#L33); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Json arena(const storage::ArenaMemoryStatistics& value) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Encode one arena component snapshot with recorded slot/pin/value partitions. |
| inputs / outputs | ArenaMemoryStatistics in; record counts, owner, component usage and capacities out. |
| invariants | live/retained/free/exhausted counts and directory spare bytes are the given sampled values; encoder does not walk arena slots. |
| ownership | Borrowed fixed arena record; ordinary DOM owns nested owner/usage records. |
| failure | Nested enum/DOM errors propagate. |
| cost | Fixed number of fields/usage objects independent of arena slot population; DOM allocation is real. |
| Design | [src/io/memory_report.cpp](../../../../../src/io/memory_report.cpp), [include/crown/io/memory_report.hpp](../../../../../include/crown/io/memory_report.hpp), [include/crown/runtime/memory_report.hpp](../../../../../include/crown/runtime/memory_report.hpp), [src/runtime/memory_report.cpp](../../../../../src/runtime/memory_report.cpp), [include/crown/resource/memory.hpp](../../../../../include/crown/resource/memory.hpp), [docs/memory_reports.md](../../../../memory_reports.md), [docs/code_review.md](../../../../code_review.md) |

## B0010

[Lines 41–41](../../../../../src/io/memory_report.cpp#L41); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
template<class Id> Json optional_id(const std::optional<Id>& value){return value?Json(value->value):Json(nullptr);}
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Encode a present fixed ID or explicit null. |
| inputs / outputs | optional&lt;Id&gt; in; Json integer or null out. |
| invariants | Presence/value copied; no authority/ID-range check. |
| ownership | Inline Json scalar/null result, no referenced backing owner. |
| failure | No intentional failure or contextual translation. |
| cost | O(1), scalar/null construction has no owning container allocation. |
| Design | [src/io/memory_report.cpp](../../../../../src/io/memory_report.cpp), [include/crown/io/memory_report.hpp](../../../../../include/crown/io/memory_report.hpp), [include/crown/runtime/memory_report.hpp](../../../../../include/crown/runtime/memory_report.hpp), [src/runtime/memory_report.cpp](../../../../../src/runtime/memory_report.cpp), [include/crown/resource/memory.hpp](../../../../../include/crown/resource/memory.hpp), [docs/memory_reports.md](../../../../memory_reports.md), [docs/code_review.md](../../../../code_review.md) |

## B0011

[Lines 42–60](../../../../../src/io/memory_report.cpp#L42); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Json table(const mm::Table& value) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Serialize one recorded storage table and the actual backend statistics variant. |
| inputs / outputs | memory::Table in; scope/relation/role/context/backend label plus table_owner/arena/owned/index records out. |
| invariants | The visit selects actual reference/indexed statistics shape. scope/backend use existing two-way labels; role alone is explicitly range-checked. This is not a validator for arbitrary edited DTO enums. |
| ownership | Borrowed table/statistics; output owns ordinary nested DOM. storage_owner integer does not retain the table. |
| failure | Role/attribution/DOM/variant errors propagate; no native table scan or mutation. |
| cost | Fixed component fields/categories per table; O(1) wrt row count, with multiple nested DOM allocations. |
| Design | [src/io/memory_report.cpp](../../../../../src/io/memory_report.cpp), [include/crown/io/memory_report.hpp](../../../../../include/crown/io/memory_report.hpp), [include/crown/runtime/memory_report.hpp](../../../../../include/crown/runtime/memory_report.hpp), [src/runtime/memory_report.cpp](../../../../../src/runtime/memory_report.cpp), [include/crown/resource/memory.hpp](../../../../../include/crown/resource/memory.hpp), [docs/memory_reports.md](../../../../memory_reports.md), [docs/code_review.md](../../../../code_review.md) |

```text
std::visit([&](const auto& memory) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Choose backend-specific diagnostic fields by the held statistics alternative. |
| inputs / outputs | std::visit callback reads reference or indexed memory record; mutates local output only. |
| invariants | requires{memory.live_records;} selects reference shape; else indexed records/directories shape. Data variant determines this branch, not the serialized backend string. |
| ownership | Captures out by reference; copies only scalar/category values into DOM. |
| failure | Nested owner/arena/DOM failures unwind local serializer. |
| cost | One fixed variant dispatch plus fixed records/categories; no row/index membership traversal. |
| Design | [src/io/memory_report.cpp](../../../../../src/io/memory_report.cpp), [include/crown/io/memory_report.hpp](../../../../../include/crown/io/memory_report.hpp), [include/crown/runtime/memory_report.hpp](../../../../../include/crown/runtime/memory_report.hpp), [src/runtime/memory_report.cpp](../../../../../src/runtime/memory_report.cpp), [include/crown/resource/memory.hpp](../../../../../include/crown/resource/memory.hpp), [docs/memory_reports.md](../../../../memory_reports.md), [docs/code_review.md](../../../../code_review.md) |

## B0012

[Lines 61–74](../../../../../src/io/memory_report.cpp#L61); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Json operation(const mm::Operator& value) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Encode one operator record by its actual variant. |
| inputs / outputs | SupportNode/Derivations/DeltaFactor/Coordinator alternative in; kind-specific diagnostic object out. |
| invariants | Optional visible/materialized fields remain nullable; operator statistics are sampled counts, not active engine capability. |
| ownership | Input variant borrowed; ordinary DOM owns labels/scalars/nested materialized object. |
| failure | Attribution/layer enum/DOM allocation or valueless variant failures propagate. |
| cost | Fixed fields per alternative, O(1) wrt represented rows; DOM construction allocates. |
| Design | [src/io/memory_report.cpp](../../../../../src/io/memory_report.cpp), [include/crown/io/memory_report.hpp](../../../../../include/crown/io/memory_report.hpp), [include/crown/runtime/memory_report.hpp](../../../../../include/crown/runtime/memory_report.hpp), [src/runtime/memory_report.cpp](../../../../../src/runtime/memory_report.cpp), [include/crown/resource/memory.hpp](../../../../../include/crown/resource/memory.hpp), [docs/memory_reports.md](../../../../memory_reports.md), [docs/code_review.md](../../../../code_review.md) |

```text
return std::visit([](const auto& item) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Visit actual operator-memory alternative and produce its descriptive DOM record. |
| inputs / outputs | Synchronous std::visit callback receives item and constructs attribution plus kind-specific fields. |
| invariants | Compile-time alternative, not arbitrary kind label, chooses branch; optional DeltaFactor materialized facts preserved nullable. |
| ownership | Borrowed variant alternative; ordinary Json out owns its copied nested data. |
| failure | Enum/DOM/OOM errors propagate; no account/runtime mutation. |
| cost | Fixed fields for each alternative; no scan proportional to represented row counts. |
| Design | [src/io/memory_report.cpp](../../../../../src/io/memory_report.cpp), [include/crown/runtime/memory_report.hpp](../../../../../include/crown/runtime/memory_report.hpp), [src/runtime/memory_report.cpp](../../../../../src/runtime/memory_report.cpp), [docs/code_review.md](../../../../code_review.md) |

## B0013

[Lines 75–75](../../../../../src/io/memory_report.cpp#L75); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L75-L75:sha256:412ca345ccf75bf9c0806bce695be8de808b79984251a7a54d202cf6101dd451
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Closes the enclosing implementation scope at this source boundary; this is a lexical delimiter, not an operation. |
| inputs / outputs | No runtime input or output. Declarations following the span leave the preceding C++ scope. |
| invariants | The delimiter ends the preceding scope's visibility/linkage region; it adds no validation, publication, ownership transfer, or runtime authority. |
| ownership | The delimiter adds no owner. If it ends a function/block with live automatic objects, their normal destructors release those objects; namespace and type-definition closes change no existing object's lifetime. |
| failure | No explicit failure translation or catch is added. If a function/block exit destroys automatic objects, exception behavior follows those destructors; namespace/type closes have no runtime failure path. |
| cost | The delimiter adds no algorithmic work. A function/block exit can run existing automatic-object destructors and cleanup; namespace/type closes have no runtime cost. |
| Design | [src/io/memory_report.cpp](../../../../../src/io/memory_report.cpp), [docs/code_specs/files/src/io/memory_report.cpp.md](memory_report.cpp.md), [docs/memory_reports.md](../../../../memory_reports.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0014

[Lines 76–90](../../../../../src/io/memory_report.cpp#L76); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Json write_memory_report(const runtime::memory::Report& report) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Export the retained report exactly as a standalone memory diagnostic artifact. |
| inputs / outputs | Valid memory::Report in; complete ordinary Json DOM with captured snapshot, usage, owner/table/operator arrays out. |
| invariants | Allocation scope is whole_query_account_including_held_generations_and_report_storage; operator scope is recorded_committed_runtime_only. This does not rerun collection, enforce an encoded byte limit, or sample current process memory. |
| ownership | Report remains retained by caller; DOM independently copies hash/labels/nested arrays using ordinary allocation outside the original native report account. |
| failure | Report has factory-only valid state and copy-like moves that preserve source access; enum/DOM errors abort return without affecting report, with no catches or publication boundary. |
| cost | O(owners+tables+operators) fixed-shape record exports and ordinary DOM storage; later dump/UTF8/encoded-byte work is separate. |
| Design | [src/io/memory_report.cpp](../../../../../src/io/memory_report.cpp), [include/crown/io/memory_report.hpp](../../../../../include/crown/io/memory_report.hpp), [include/crown/runtime/memory_report.hpp](../../../../../include/crown/runtime/memory_report.hpp), [src/runtime/memory_report.cpp](../../../../../src/runtime/memory_report.cpp), [include/crown/resource/memory.hpp](../../../../../include/crown/resource/memory.hpp), [docs/memory_reports.md](../../../../memory_reports.md), [docs/code_review.md](../../../../code_review.md) |

```text
for(const auto& row:report.owners())out["owners"].push_back(owner(row));
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Export each already captured owner partition. |
| inputs / outputs | report.owners() const vector reference iterated; owner DOM appended to local out. |
| invariants | No ledger resampling/relabeling or grant extension during serialization. |
| ownership | Const vector reference borrows report; appended DOM owns ordinary copies. |
| failure | Allocation/enum error aborts local output. |
| cost | O(owner count) fixed category exports and DOM growth. |
| Design | [src/io/memory_report.cpp](../../../../../src/io/memory_report.cpp), [include/crown/runtime/memory_report.hpp](../../../../../include/crown/runtime/memory_report.hpp), [src/runtime/memory_report.cpp](../../../../../src/runtime/memory_report.cpp), [docs/code_review.md](../../../../code_review.md) |

```text
for(const auto& row:report.tables())out["tables"].push_back(table(row));
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Export each captured table component record without scanning native tables. |
| inputs / outputs | report.tables() const vector reference iterated into ordinary table DOM records. |
| invariants | Table snapshot is retained report data, not live TableState access. |
| ownership | Borrowed vector reference; ordinary result array owns copied objects. |
| failure | Nested enum/DOM/OOM failure aborts enclosing writer. |
| cost | O(table count) fixed component conversion, independent of underlying row count. |
| Design | [src/io/memory_report.cpp](../../../../../src/io/memory_report.cpp), [include/crown/runtime/memory_report.hpp](../../../../../include/crown/runtime/memory_report.hpp), [src/runtime/memory_report.cpp](../../../../../src/runtime/memory_report.cpp), [docs/code_review.md](../../../../code_review.md) |

```text
for(const auto& row:report.operators())out["operators"].push_back(operation(row));
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Export each captured logical operator record. |
| inputs / outputs | report.operators() const vector reference iterated and dispatched through operation(). |
| invariants | Fixed recorded committed-runtime facts; no active operator evaluation. |
| ownership | Borrowed vector reference with independent ordinary DOM output. |
| failure | Variant/enum/DOM errors propagate. |
| cost | O(operator count) fixed-shape conversion and array growth. |
| Design | [src/io/memory_report.cpp](../../../../../src/io/memory_report.cpp), [include/crown/runtime/memory_report.hpp](../../../../../include/crown/runtime/memory_report.hpp), [src/runtime/memory_report.cpp](../../../../../src/runtime/memory_report.cpp), [docs/code_review.md](../../../../code_review.md) |

## B0015

[Lines 91–91](../../../../../src/io/memory_report.cpp#L91); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L91-L91:sha256:39c2bd587239794e92def2b2ebc5cce8f0acd397d817bceec761a8f61bea3e66
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Closes the namespace crown::io at this source boundary; this is a lexical delimiter, not an operation. |
| inputs / outputs | No runtime input or output. Declarations following the span leave the preceding C++ scope. |
| invariants | The delimiter ends the preceding scope's visibility/linkage region; it adds no validation, publication, ownership transfer, or runtime authority. |
| ownership | The delimiter adds no owner. If it ends a function/block with live automatic objects, their normal destructors release those objects; namespace and type-definition closes change no existing object's lifetime. |
| failure | No explicit failure translation or catch is added. If a function/block exit destroys automatic objects, exception behavior follows those destructors; namespace/type closes have no runtime failure path. |
| cost | The delimiter adds no algorithmic work. A function/block exit can run existing automatic-object destructors and cleanup; namespace/type closes have no runtime cost. |
| Design | [src/io/memory_report.cpp](../../../../../src/io/memory_report.cpp), [docs/code_specs/files/src/io/memory_report.cpp.md](memory_report.cpp.md), [docs/memory_reports.md](../../../../memory_reports.md), [docs/query_memory.md](../../../../query_memory.md) |
