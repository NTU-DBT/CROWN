# `src/io/physical.cpp` — block usage map

[Source](../../../../../src/io/physical.cpp) · [Source index](../../../README.md) · [Subsystem contracts](../../../subsystem_contracts.md) · [Reviewed primitives](../../../primitives.md)

Admit bounded external documents/records and serialize explicit public representations at the engine boundary.

Snapshot SHA-256: `7cb7ed679c3060bcc1a9b6d70413b7e84b7c202465be7cb108e5bf20c2252655`. 219 lines partitioned into 23 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [io](../../../subsystem_contracts.md#io). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/ingestion.md](../../../../ingestion.md), [docs/query_identity.md](../../../../query_identity.md), [docs/schema_evolution.md](../../../../schema_evolution.md), [docs/cli.md](../../../../cli.md), [docs/query_memory.md](../../../../query_memory.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–10](../../../../../src/io/physical.cpp#L1) | Imports dependencies; declares namespace scope. |  · [reviewed contract](#b0001) |
| [B0002 · 11–13](../../../../../src/io/physical.cpp#L11) | Callable definition: template &lt;class Range&gt; Json ids(const Range& values) | calls Json::array, push_back; returns result; growth push_back; 1 loop sites · [reviewed contract](#b0002) |
| [B0003 · 14–14](../../../../../src/io/physical.cpp#L14) | Callable definition: template &lt;class Id&gt; Json optional_id(const std::optional&lt;Id&gt;& value) | calls Json; returns value ? Json(value-&gt;value) : Json(nullptr) · [reviewed contract](#b0003) |
| [B0004 · 15–17](../../../../../src/io/physical.cpp#L15) | Callable definition: Json projection(const storage::Projection& value) | calls source, id, target, ids; returns {{@ ,value.source().id().value},{@ ,value.target().id().value},{@ ,ids(value.fields())}} · [reviewed contract](#b0004) |
| [B0005 · 18–18](../../../../../src/io/physical.cpp#L18) | Callable definition: Json slot(AssignmentSlot value) | calls ; returns {{@ ,value.step},{@ ,value.field.value}} · [reviewed contract](#b0005) |
| [B0006 · 19–22](../../../../../src/io/physical.cpp#L19) | Callable definition: std::string route_name(PhysicalRoute route) | calls Error; returns @; @ · [reviewed contract](#b0006) |
| [B0007 · 23–33](../../../../../src/io/physical.cpp#L23) | Callable definition: std::string role_name(RelationRole role) | calls Error; returns @; @ · [reviewed contract](#b0007) |
| [B0008 · 34–36](../../../../../src/io/physical.cpp#L34) | Callable definition: std::optional&lt;std::uint64_t&gt; limit(const Json& value,const std::string& path) | calls is_null, detail::unsigned_integer; returns value.is_null() ? std::nullopt : std::optional&lt;std::uint64_t&gt;{detail::unsigned_integer(value,path)} · [reviewed contract](#b0008) |
| [B0009 · 37–37](../../../../../src/io/physical.cpp#L37) | Callable definition: Json limit(std::optional&lt;std::uint64_t&gt; value) | calls Json; returns value ? Json(*value) : Json(nullptr) · [reviewed contract](#b0009) |
| [B0010 · 38–47](../../../../../src/io/physical.cpp#L38) | Callable definition: Json indexed_backend(const storage::IndexedBackendSpec& spec) | calls ; returns {{@ ,@ },{@ ,@ }, · [reviewed contract](#b0010) |
| [B0011 · 48–54](../../../../../src/io/physical.cpp#L48) | Callable definition: std::size_t component_count(const Json& value,const std::string& path) | calls detail::unsigned_integer, constexpr, max, detail::fail; returns static_cast&lt;std::size_t&gt;(count) · [reviewed contract](#b0011) |
| [B0012 · 55–78](../../../../../src/io/physical.cpp#L55) | Callable definition: storage::IndexedBackendSpec read_indexed_backend(const Json& value) | calls detail::fields, detail::string, at, Error; returns spec; 1 loop sites · [reviewed contract](#b0012) |
| [B0013 · 79–86](../../../../../src/io/physical.cpp#L79) | Callable definition: Json guarantee(const GuaranteeProfile& profile) | calls ; returns {{@ ,profile.semantics},{@ ,profile.query_class},{@ ,profile.update_contract}, · [reviewed contract](#b0013) |
| [B0014 · 87–88](../../../../../src/io/physical.cpp#L87) | Closes surrounding scope/type. | source comment (unverified): // namespace · [reviewed contract](#b0014) |
| [B0015 · 89–95](../../../../../src/io/physical.cpp#L89) | Callable definition: Json write_physical_options(const PhysicalOptions& options) | calls limit, indexed_backend; returns result · [reviewed contract](#b0015) |
| [B0016 · 96–120](../../../../../src/io/physical.cpp#L96) | Callable definition: PhysicalOptions read_physical_options(std::string_view text) | calls detail::parse_json, detail::fields, detail::unsigned_integer, at; returns options; source comment (unverified): // Version2 is specifically the indexed contract. A relabeled legacy · [reviewed contract](#b0016) |
| [B0017 · 121–121](../../../../../src/io/physical.cpp#L121) | Explanatory comments or spacing. |  |
| [B0018 · 122–129](../../../../../src/io/physical.cpp#L122) | Callable definition: Json write_physical_source(const Catalog& catalog,const Query& query,const std::optional&lt;frontend::NormalizedSql&gt;& normalized) | calls write_sql_normalization, resize, size, write_document; returns {{@ ,@ },{@ ,write_sql_normalization(*normalized)}}; {{@ ,@ },{@ ,write_document(document)}}; growth resize · [reviewed contract](#b0018) |
| [B0019 · 130–179](../../../../../src/io/physical.cpp#L130) | Callable definition: Json write_physical(const PhysicalPlan& plan) | calls write_physical_source, catalog, query, normalized; returns {{@ ,plan.options().indexed_storage ? 2 : 1},; growth push_back; 13 loop sites · [reviewed contract](#b0019) |
| [B0020 · 180–183](../../../../../src/io/physical.cpp#L180) | Callable definition: Json write_physical(const CompiledProgram& plan) | calls PhysicalPlan::from_compiled; returns write_physical(exported) · [reviewed contract](#b0020) |
| [B0021 · 184–184](../../../../../src/io/physical.cpp#L184) | Explanatory comments or spacing. |  |
| [B0022 · 185–218](../../../../../src/io/physical.cpp#L185) | Callable definition: PhysicalPlan read_physical(std::string_view text,const PhysicalReadLimits& limits) | calls detail::parse_json, detail::fields, detail::unsigned_integer, at; returns planner::lower_tree(document.catalog,document.query,tree,options,limits.lowering); planner::lower_n…; source comment (unverified): // Source replay and verified lowering establish the result; imported flags/slots do not. · [reviewed contract](#b0022) |
| [B0023 · 219–219](../../../../../src/io/physical.cpp#L219) | Closes surrounding scope/type. | source comment (unverified): // namespace crown::io · [reviewed contract](#b0023) |

## B0001

[Lines 1–10](../../../../../src/io/physical.cpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
#include "crown/io/physical.hpp"
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Serialize physical compile artifacts and rebuild their complete verified lowering instead of trusting imported slots/flags. |
| inputs / outputs | Imports the declarations used by this translation unit/header; no runtime input or result. |
| invariants | Namespace/includes do not perform admission, validation, publication or IO. |
| ownership | Declarations give no ownership of caller records, source bytes or runtime accounts. |
| failure | Compile/link dependencies only; there is no executable failure boundary in these includes. |
| cost | Compile-time dependencies; later functions account for their own runtime work and storage. |
| Design | [src/io/physical.cpp](../../../../../src/io/physical.cpp), [include/crown/io/physical.hpp](../../../../../include/crown/io/physical.hpp), [src/io/json.hpp](../../../../../src/io/json.hpp), [src/io/document.cpp](../../../../../src/io/document.cpp), [src/io/layout.cpp](../../../../../src/io/layout.cpp), [src/io/normalization.cpp](../../../../../src/io/normalization.cpp), [src/planner/lower.cpp](../../../../../src/planner/lower.cpp), [src/planner/compiled_source.cpp](../../../../../src/planner/compiled_source.cpp), [docs/tree_plans.md](../../../../tree_plans.md), [docs/code_review.md](../../../../code_review.md) |

## B0002

[Lines 11–13](../../../../../src/io/physical.cpp#L11); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
template <class Range> Json ids(const Range& values) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Export a range of typed IDs as numeric JSON values. |
| inputs / outputs | Borrowed typed-ID range in; owning ordinary array out in supplied order. |
| invariants | No range/identity/admission validation is implied by numeric IDs. |
| ownership | DOM owns its array; typed source IDs are copied inline. |
| failure | Array allocation failure propagates. |
| cost | O(ID count) traversal/array growth; O(count) ordinary DOM storage. |
| Design | [src/io/physical.cpp](../../../../../src/io/physical.cpp), [include/crown/io/physical.hpp](../../../../../include/crown/io/physical.hpp), [src/io/json.hpp](../../../../../src/io/json.hpp), [src/io/document.cpp](../../../../../src/io/document.cpp), [src/io/layout.cpp](../../../../../src/io/layout.cpp), [src/io/normalization.cpp](../../../../../src/io/normalization.cpp), [src/planner/lower.cpp](../../../../../src/planner/lower.cpp), [src/planner/compiled_source.cpp](../../../../../src/planner/compiled_source.cpp), [docs/tree_plans.md](../../../../tree_plans.md), [docs/code_review.md](../../../../code_review.md) |

## B0003

[Lines 14–14](../../../../../src/io/physical.cpp#L14); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
template <class Id> Json optional_id(const std::optional<Id>& value) { return value ? Json(value->value) : Json(nullptr); }
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Encode a present physical ID or null. |
| inputs / outputs | optional&lt;Id&gt; in; numeric/null Json out. |
| invariants | Presence does not establish graph-reference validity. |
| ownership | Inline scalar/null result, no retained backing. |
| failure | No intentional failure branch. |
| cost | O(1), no container allocation for scalar/null. |
| Design | [src/io/physical.cpp](../../../../../src/io/physical.cpp), [include/crown/io/physical.hpp](../../../../../include/crown/io/physical.hpp), [src/io/json.hpp](../../../../../src/io/json.hpp), [src/io/document.cpp](../../../../../src/io/document.cpp), [src/io/layout.cpp](../../../../../src/io/layout.cpp), [src/io/normalization.cpp](../../../../../src/io/normalization.cpp), [src/planner/lower.cpp](../../../../../src/planner/lower.cpp), [src/planner/compiled_source.cpp](../../../../../src/planner/compiled_source.cpp), [docs/tree_plans.md](../../../../tree_plans.md), [docs/code_review.md](../../../../code_review.md) |

## B0004

[Lines 15–17](../../../../../src/io/physical.cpp#L15); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Json projection(const storage::Projection& value) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Export the layout IDs and selected fields of a projection. |
| inputs / outputs | Valid Projection in; source_layout/target_layout/fields DOM out. |
| invariants | Uses actual descriptor accessors; labels are not a reconstructed native projection. |
| ownership | Projection is borrowed; array/object DOM owns copied scalar data. |
| failure | Moved-from projection/layout accessor or DOM allocation failure propagates. |
| cost | O(projection width) array construction plus fixed object overhead. |
| Design | [src/io/physical.cpp](../../../../../src/io/physical.cpp), [include/crown/io/physical.hpp](../../../../../include/crown/io/physical.hpp), [src/io/json.hpp](../../../../../src/io/json.hpp), [src/io/document.cpp](../../../../../src/io/document.cpp), [src/io/layout.cpp](../../../../../src/io/layout.cpp), [src/io/normalization.cpp](../../../../../src/io/normalization.cpp), [src/planner/lower.cpp](../../../../../src/planner/lower.cpp), [src/planner/compiled_source.cpp](../../../../../src/planner/compiled_source.cpp), [docs/tree_plans.md](../../../../tree_plans.md), [docs/code_review.md](../../../../code_review.md) |

## B0005

[Lines 18–18](../../../../../src/io/physical.cpp#L18); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Json slot(AssignmentSlot value) { return {{"step",value.step},{"field",value.field.value}}; }
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Encode an enumeration assignment location. |
| inputs / outputs | AssignmentSlot in; step/field object out. |
| invariants | No step/field range check here; complete re-lowering verifies imported artifact. |
| ownership | Inline source data copied into ordinary DOM object. |
| failure | DOM allocation failure propagates. |
| cost | Fixed two-field object allocation. |
| Design | [src/io/physical.cpp](../../../../../src/io/physical.cpp), [include/crown/io/physical.hpp](../../../../../include/crown/io/physical.hpp), [src/io/json.hpp](../../../../../src/io/json.hpp), [src/io/document.cpp](../../../../../src/io/document.cpp), [src/io/layout.cpp](../../../../../src/io/layout.cpp), [src/io/normalization.cpp](../../../../../src/io/normalization.cpp), [src/planner/lower.cpp](../../../../../src/planner/lower.cpp), [src/planner/compiled_source.cpp](../../../../../src/planner/compiled_source.cpp), [docs/tree_plans.md](../../../../tree_plans.md), [docs/code_review.md](../../../../code_review.md) |

## B0006

[Lines 19–22](../../../../../src/io/physical.cpp#L19); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::string route_name(PhysicalRoute route) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Name a known physical route without an unknown fallback. |
| inputs / outputs | Enum in; ordinary std::string of stable route/role spelling out. |
| invariants | Only declared alternatives accepted; string labels alone cannot instantiate a plan. |
| ownership | Returned string owns its bytes; short-string optimization is implementation dependent. |
| failure | Unknown enum throws lowering_contract; string/Error allocation may fail. |
| cost | Fixed switch and O(label bytes) owning string construction. |
| Design | [src/io/physical.cpp](../../../../../src/io/physical.cpp), [include/crown/io/physical.hpp](../../../../../include/crown/io/physical.hpp), [src/io/json.hpp](../../../../../src/io/json.hpp), [src/io/document.cpp](../../../../../src/io/document.cpp), [src/io/layout.cpp](../../../../../src/io/layout.cpp), [src/io/normalization.cpp](../../../../../src/io/normalization.cpp), [src/planner/lower.cpp](../../../../../src/planner/lower.cpp), [src/planner/compiled_source.cpp](../../../../../src/planner/compiled_source.cpp), [docs/tree_plans.md](../../../../tree_plans.md), [docs/code_review.md](../../../../code_review.md) |

## B0007

[Lines 23–33](../../../../../src/io/physical.cpp#L23); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::string role_name(RelationRole role) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Name a known physical relation role without an unknown fallback. |
| inputs / outputs | Enum in; ordinary std::string of stable route/role spelling out. |
| invariants | Only declared alternatives accepted; string labels alone cannot instantiate a plan. |
| ownership | Returned string owns its bytes; short-string optimization is implementation dependent. |
| failure | Unknown enum throws lowering_contract; string/Error allocation may fail. |
| cost | Fixed switch and O(label bytes) owning string construction. |
| Design | [src/io/physical.cpp](../../../../../src/io/physical.cpp), [include/crown/io/physical.hpp](../../../../../include/crown/io/physical.hpp), [src/io/json.hpp](../../../../../src/io/json.hpp), [src/io/document.cpp](../../../../../src/io/document.cpp), [src/io/layout.cpp](../../../../../src/io/layout.cpp), [src/io/normalization.cpp](../../../../../src/io/normalization.cpp), [src/planner/lower.cpp](../../../../../src/planner/lower.cpp), [src/planner/compiled_source.cpp](../../../../../src/planner/compiled_source.cpp), [docs/tree_plans.md](../../../../tree_plans.md), [docs/code_review.md](../../../../code_review.md) |

## B0008

[Lines 34–36](../../../../../src/io/physical.cpp#L34); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::optional<std::uint64_t> limit(const Json& value,const std::string& path) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Read an optional producer work limit from a nullable numeric DOM value. |
| inputs / outputs | Json/path in; disengaged optional for null or strict uint64_t out. |
| invariants | No negative/float/bool coercion; host effective cap is applied in lowering separately. |
| ownership | Inline optional result; DOM/path borrowed. |
| failure | Invalid numeric form rejects through shared helper. |
| cost | O(1) scalar work, caller path construction may allocate. |
| Design | [src/io/physical.cpp](../../../../../src/io/physical.cpp), [include/crown/io/physical.hpp](../../../../../include/crown/io/physical.hpp), [src/io/json.hpp](../../../../../src/io/json.hpp), [src/io/document.cpp](../../../../../src/io/document.cpp), [src/io/layout.cpp](../../../../../src/io/layout.cpp), [src/io/normalization.cpp](../../../../../src/io/normalization.cpp), [src/planner/lower.cpp](../../../../../src/planner/lower.cpp), [src/planner/compiled_source.cpp](../../../../../src/planner/compiled_source.cpp), [docs/tree_plans.md](../../../../tree_plans.md), [docs/code_review.md](../../../../code_review.md) |

## B0009

[Lines 37–37](../../../../../src/io/physical.cpp#L37); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Json limit(std::optional<std::uint64_t> value) { return value ? Json(*value) : Json(nullptr); }
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Serialize an optional work limit as integer or explicit null. |
| inputs / outputs | optional&lt;uint64_t&gt; in; scalar/null Json out. |
| invariants | Null retains unbounded producer-policy meaning; not an allocation grant. |
| ownership | Inline result, no shared backing. |
| failure | No intentional failure branch. |
| cost | O(1), no container allocation. |
| Design | [src/io/physical.cpp](../../../../../src/io/physical.cpp), [include/crown/io/physical.hpp](../../../../../include/crown/io/physical.hpp), [src/io/json.hpp](../../../../../src/io/json.hpp), [src/io/document.cpp](../../../../../src/io/document.cpp), [src/io/layout.cpp](../../../../../src/io/layout.cpp), [src/io/normalization.cpp](../../../../../src/io/normalization.cpp), [src/planner/lower.cpp](../../../../../src/planner/lower.cpp), [src/planner/compiled_source.cpp](../../../../../src/planner/compiled_source.cpp), [docs/tree_plans.md](../../../../tree_plans.md), [docs/code_review.md](../../../../code_review.md) |

## B0010

[Lines 38–47](../../../../../src/io/physical.cpp#L38); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Json indexed_backend(const storage::IndexedBackendSpec& spec) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Serialize the exact indexed storage algorithm/traversal/component/work contract. |
| inputs / outputs | IndexedBackendSpec in; owning algorithm/scope labels and per_table/per_operation limits DOM out. |
| invariants | Component scope includes undo; work scope is operation aggregate. Serialization only copies spec values, it does not allocate tables or prove performance. |
| ownership | Input spec is fixed scalar record; nested DOM owns copied labels/fields. |
| failure | DOM allocation failure propagates. |
| cost | Fixed9 component ceilings and5 operation work fields plus contract labels; ordinary DOM allocations. |
| Design | [src/io/physical.cpp](../../../../../src/io/physical.cpp), [include/crown/io/physical.hpp](../../../../../include/crown/io/physical.hpp), [src/io/json.hpp](../../../../../src/io/json.hpp), [src/io/document.cpp](../../../../../src/io/document.cpp), [src/io/layout.cpp](../../../../../src/io/layout.cpp), [src/io/normalization.cpp](../../../../../src/io/normalization.cpp), [src/planner/lower.cpp](../../../../../src/planner/lower.cpp), [src/planner/compiled_source.cpp](../../../../../src/planner/compiled_source.cpp), [docs/tree_plans.md](../../../../tree_plans.md), [docs/code_review.md](../../../../code_review.md) |

## B0011

[Lines 48–54](../../../../../src/io/physical.cpp#L48); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::size_t component_count(const Json& value,const std::string& path) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Read a storage component count without host narrowing overflow. |
| inputs / outputs | Json/path in; strict nonnegative size_t out. |
| invariants | On hosts with fewer than64 size_t bits explicitly rejects excessive count; no table allocation performed. |
| ownership | Inline result; input DOM/path borrowed. |
| failure | Type/sign/host-range failures reject through invalid_document. |
| cost | O(1) scalar work plus any caller-built path text. |
| Design | [src/io/physical.cpp](../../../../../src/io/physical.cpp), [include/crown/io/physical.hpp](../../../../../include/crown/io/physical.hpp), [src/io/json.hpp](../../../../../src/io/json.hpp), [src/io/document.cpp](../../../../../src/io/document.cpp), [src/io/layout.cpp](../../../../../src/io/layout.cpp), [src/io/normalization.cpp](../../../../../src/io/normalization.cpp), [src/planner/lower.cpp](../../../../../src/planner/lower.cpp), [src/planner/compiled_source.cpp](../../../../../src/planner/compiled_source.cpp), [docs/tree_plans.md](../../../../tree_plans.md), [docs/code_review.md](../../../../code_review.md) |

## B0012

[Lines 55–78](../../../../../src/io/physical.cpp#L55); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
storage::IndexedBackendSpec read_indexed_backend(const Json& value) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Read an explicit indexed backend spec only for the supported storage contract. |
| inputs / outputs | DOM object in; exact algorithm/traversal/scopes,9 component counts and5 work limits out. |
| invariants | Rejects unknown/missing fields, unsupported labels and host-size component overflow; spec values are ceilings, not evidence that a native table exists. |
| ownership | Returns inline spec; shape checks use borrowed DOM, label/path helpers create ordinary temporary strings. |
| failure | Unsupported semantics/numeric/shape/OOM failures propagate; no storage-table mutation. |
| cost | Fixed-size object field checks and copied label/path bytes; no native allocations/tables, but ordinary temporary strings can allocate. |
| Design | [src/io/physical.cpp](../../../../../src/io/physical.cpp), [include/crown/io/physical.hpp](../../../../../include/crown/io/physical.hpp), [src/io/json.hpp](../../../../../src/io/json.hpp), [src/io/document.cpp](../../../../../src/io/document.cpp), [src/io/layout.cpp](../../../../../src/io/layout.cpp), [src/io/normalization.cpp](../../../../../src/io/normalization.cpp), [src/planner/lower.cpp](../../../../../src/planner/lower.cpp), [src/planner/compiled_source.cpp](../../../../../src/planner/compiled_source.cpp), [docs/tree_plans.md](../../../../tree_plans.md), [docs/code_review.md](../../../../code_review.md) |

## B0013

[Lines 79–86](../../../../../src/io/physical.cpp#L79); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Json guarantee(const GuaranteeProfile& profile) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Export the guarantee profile reported by an already constructed plan. |
| inputs / outputs | GuaranteeProfile strings/lists in; owning semantics/query/update/arithmetic/backend/bounds/assumptions DOM out. |
| invariants | Does not infer theorem applicability or cost optimality from labels; read_physical later compares these fields against real lowering. |
| ownership | Deep-copies ordinary string/list fields into DOM; original profile borrowed. |
| failure | DOM/text allocation failure propagates. |
| cost | O(total profile labels/list entries/bytes) copy and ordinary DOM storage. |
| Design | [src/io/physical.cpp](../../../../../src/io/physical.cpp), [include/crown/io/physical.hpp](../../../../../include/crown/io/physical.hpp), [src/io/json.hpp](../../../../../src/io/json.hpp), [src/io/document.cpp](../../../../../src/io/document.cpp), [src/io/layout.cpp](../../../../../src/io/layout.cpp), [src/io/normalization.cpp](../../../../../src/io/normalization.cpp), [src/planner/lower.cpp](../../../../../src/planner/lower.cpp), [src/planner/compiled_source.cpp](../../../../../src/planner/compiled_source.cpp), [docs/tree_plans.md](../../../../tree_plans.md), [docs/code_review.md](../../../../code_review.md) |

## B0014

[Lines 87–88](../../../../../src/io/physical.cpp#L87); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L87-L88:sha256:c2bd7638f09d52cb034ed574f539304035fc6fab162bf8d5fa20a35d8c7288a1
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Closes the anonymous namespace at this source boundary; this is a lexical delimiter, not an operation. |
| inputs / outputs | No runtime input or output. Declarations following the span leave the preceding C++ scope. |
| invariants | The delimiter ends the preceding scope's visibility/linkage region; it adds no validation, publication, ownership transfer, or runtime authority. |
| ownership | The delimiter adds no owner. If it ends a function/block with live automatic objects, their normal destructors release those objects; namespace and type-definition closes change no existing object's lifetime. |
| failure | No explicit failure translation or catch is added. If a function/block exit destroys automatic objects, exception behavior follows those destructors; namespace/type closes have no runtime failure path. |
| cost | The delimiter adds no algorithmic work. A function/block exit can run existing automatic-object destructors and cleanup; namespace/type closes have no runtime cost. |
| Design | [src/io/physical.cpp](../../../../../src/io/physical.cpp), [docs/code_specs/files/src/io/physical.cpp.md](physical.cpp.md), [docs/physical_plans.md](../../../../physical_plans.md), [docs/semantics.md](../../../../semantics.md) |

## B0015

[Lines 89–95](../../../../../src/io/physical.cpp#L89); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Json write_physical_options(const PhysicalOptions& options) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Export the stored physical policy and limits in the backend-specific schema version. |
| inputs / outputs | PhysicalOptions in; version1 for reference or2 with explicit indexed_storage out. |
| invariants | Version selection follows actual indexed_storage presence; no new account/backend/runtime state. |
| ownership | Copies policy strings/limit labels into ordinary DOM; optional indexed spec is serialized inline/nested. |
| failure | DOM allocation failure propagates; this writer does not independently validate arbitrary policy strings. |
| cost | Fixed options fields plus policy bytes and indexed fixed fields; ordinary DOM allocations. |
| Design | [src/io/physical.cpp](../../../../../src/io/physical.cpp), [include/crown/io/physical.hpp](../../../../../include/crown/io/physical.hpp), [src/io/json.hpp](../../../../../src/io/json.hpp), [src/io/document.cpp](../../../../../src/io/document.cpp), [src/io/layout.cpp](../../../../../src/io/layout.cpp), [src/io/normalization.cpp](../../../../../src/io/normalization.cpp), [src/planner/lower.cpp](../../../../../src/planner/lower.cpp), [src/planner/compiled_source.cpp](../../../../../src/planner/compiled_source.cpp), [docs/tree_plans.md](../../../../tree_plans.md), [docs/code_review.md](../../../../code_review.md) |

## B0016

[Lines 96–120](../../../../../src/io/physical.cpp#L96); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
PhysicalOptions read_physical_options(std::string_view text) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Parse exact reference/indexed options and validate arithmetic/versioned policy labels. |
| inputs / outputs | Text in; PhysicalOptions with owning policy strings and optional fixed indexed spec out. |
| invariants | Version1 forbids indexed_storage; version2 requires it. Arithmetic must pass require_set_backend_policy; planner/optimization/cost_model must be nonempty but are not independently looked up as installed algorithms here. |
| ownership | DOM temporary; policy strings deep-copy ordinary bytes. No native query account/backend is instantiated. |
| failure | Version/shape/policy/indexed numeric/DOM/OOM failures abort before return; no catch or state mutation. |
| cost | Full input parse plus fixed field checks and policy-label copies; parse has only depth/duplicate-key operational guards, no options byte cap here. |
| Design | [src/io/physical.cpp](../../../../../src/io/physical.cpp), [include/crown/io/physical.hpp](../../../../../include/crown/io/physical.hpp), [src/io/json.hpp](../../../../../src/io/json.hpp), [src/io/document.cpp](../../../../../src/io/document.cpp), [src/io/layout.cpp](../../../../../src/io/layout.cpp), [src/io/normalization.cpp](../../../../../src/io/normalization.cpp), [src/planner/lower.cpp](../../../../../src/planner/lower.cpp), [src/planner/compiled_source.cpp](../../../../../src/planner/compiled_source.cpp), [docs/tree_plans.md](../../../../tree_plans.md), [docs/code_review.md](../../../../code_review.md) |

```text
else if (version==2) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Require indexed contract presence for a version2 options envelope. |
| inputs / outputs | Parsed version2 object in; validates presence and exact top-level fields. |
| invariants | Changing only schema_version of a legacy object is unsupported_version, not implicit backend migration. |
| ownership | Borrows DOM; no output state published. |
| failure | Missing explicit contract rejects before spec parsing. |
| cost | Fixed membership/field checks; no native allocation. |
| Design | [src/io/physical.cpp](../../../../../src/io/physical.cpp), [include/crown/io/physical.hpp](../../../../../include/crown/io/physical.hpp), [src/io/json.hpp](../../../../../src/io/json.hpp), [src/io/document.cpp](../../../../../src/io/document.cpp), [src/io/layout.cpp](../../../../../src/io/layout.cpp), [src/io/normalization.cpp](../../../../../src/io/normalization.cpp), [src/planner/lower.cpp](../../../../../src/planner/lower.cpp), [src/planner/compiled_source.cpp](../../../../../src/planner/compiled_source.cpp), [docs/tree_plans.md](../../../../tree_plans.md), [docs/code_review.md](../../../../code_review.md) |

## B0018

[Lines 122–129](../../../../../src/io/physical.cpp#L122); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Json write_physical_source(const Catalog& catalog,const Query& query,const std::optional<frontend::NormalizedSql>& normalized) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Export the exact compile source without input data/streams. |
| inputs / outputs | Catalog/query/optional normalized program in; tagged normalized_sql or direct_cq source DOM out. |
| invariants | Normalized branch uses actual normalized artifact; direct branch forces document format3 with empty initial tables. Initial rows/update streams are deliberately absent from physical source identity. |
| ownership | Direct branch deep-copies catalog/query into ordinary Document; normalized call implicitly copies its owning NormalizedSql into SqlNormalizeResult variant before serialization. Result DOM independently owns text/arrays. |
| failure | Source/normalization/document/DOM/allocation errors propagate before return. |
| cost | Full source graph copying and DOM serialization, plus empty table array; cold export with original graph, temporary DTO/variant and DOM simultaneously retained. |
| Design | [src/io/physical.cpp](../../../../../src/io/physical.cpp), [include/crown/io/physical.hpp](../../../../../include/crown/io/physical.hpp), [src/io/json.hpp](../../../../../src/io/json.hpp), [src/io/document.cpp](../../../../../src/io/document.cpp), [src/io/layout.cpp](../../../../../src/io/layout.cpp), [src/io/normalization.cpp](../../../../../src/io/normalization.cpp), [src/planner/lower.cpp](../../../../../src/planner/lower.cpp), [src/planner/compiled_source.cpp](../../../../../src/planner/compiled_source.cpp), [docs/tree_plans.md](../../../../tree_plans.md), [docs/code_review.md](../../../../code_review.md) |

## B0019

[Lines 130–179](../../../../../src/io/physical.cpp#L130); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Json write_physical(const PhysicalPlan& plan) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Serialize every physical plan component, checked lowering result and stored guarantee into its canonical artifact. |
| inputs / outputs | Valid factory-produced PhysicalPlan in; full ordinary Json DOM out. |
| invariants | Plan factories supply engaged validation heights; writer dereferences them and does not create validity by filling flags. Graph rows/slots/layouts/policies/identity and work are descriptive output. |
| ownership | Plan handle/descriptor data borrowed; source/document, layouts, nodes, constants, identity JSON and guarantee strings are copied into owning ordinary DOM. |
| failure | Moved-from/accessor/scalar/tree/addressability/DOM/OOM failures propagate; no live runtime state is installed or changed. |
| cost | Full source/layout/relation/index/input/route/node/edge/enumeration graph traversal plus tree/catalog validation in write_tree; DOM/temporary copies allocate. No update/quanta-time claim. |
| Design | [src/io/physical.cpp](../../../../../src/io/physical.cpp), [include/crown/io/physical.hpp](../../../../../include/crown/io/physical.hpp), [src/io/json.hpp](../../../../../src/io/json.hpp), [src/io/document.cpp](../../../../../src/io/document.cpp), [src/io/layout.cpp](../../../../../src/io/layout.cpp), [src/io/normalization.cpp](../../../../../src/io/normalization.cpp), [src/planner/lower.cpp](../../../../../src/planner/lower.cpp), [src/planner/compiled_source.cpp](../../../../../src/planner/compiled_source.cpp), [docs/tree_plans.md](../../../../tree_plans.md), [docs/code_review.md](../../../../code_review.md) |

```text
for (const auto& index : plan.indexes()) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Export physical secondary-index projections and use labels. |
| inputs / outputs | IndexRequirement range in; per-index IDs/relation/projection/use array out. |
| invariants | Known reverse_child_support maps explicitly; existing other branch maps visible_enumeration, so this writer is not a general unknown-enum validator. |
| ownership | DOM owns array/object records, projection IDs copied from shared metadata. |
| failure | Projection/accessor/DOM errors abort enclosing serialization. |
| cost | O(index count+projection widths+use count) traversal/DOM allocations. |
| Design | [src/io/physical.cpp](../../../../../src/io/physical.cpp), [include/crown/io/physical.hpp](../../../../../include/crown/io/physical.hpp), [src/io/json.hpp](../../../../../src/io/json.hpp), [src/io/document.cpp](../../../../../src/io/document.cpp), [src/io/layout.cpp](../../../../../src/io/layout.cpp), [src/io/normalization.cpp](../../../../../src/io/normalization.cpp), [src/planner/lower.cpp](../../../../../src/planner/lower.cpp), [src/planner/compiled_source.cpp](../../../../../src/planner/compiled_source.cpp), [docs/tree_plans.md](../../../../tree_plans.md), [docs/code_review.md](../../../../code_review.md) |

```text
for (const auto& input : plan.inputs()) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Export physical input adapters including equality and typed constant predicates. |
| inputs / outputs | PhysicalInput range in; occurrence/node/base/logical/layout/projection/equalities/constants out. |
| invariants | Fields and constants are emitted exactly as lowering produced; no new row/program validation here. |
| ownership | DOM owns typed constant/text copies and arrays; input layouts remain borrowed handles. |
| failure | write_scalar/projection/DOM failures propagate. |
| cost | O(inputs+projection fields+equalities+constant payload bytes) and ordinary DOM storage. |
| Design | [src/io/physical.cpp](../../../../../src/io/physical.cpp), [include/crown/io/physical.hpp](../../../../../include/crown/io/physical.hpp), [src/io/json.hpp](../../../../../src/io/json.hpp), [src/io/document.cpp](../../../../../src/io/document.cpp), [src/io/layout.cpp](../../../../../src/io/layout.cpp), [src/io/normalization.cpp](../../../../../src/io/normalization.cpp), [src/planner/lower.cpp](../../../../../src/planner/lower.cpp), [src/planner/compiled_source.cpp](../../../../../src/planner/compiled_source.cpp), [docs/tree_plans.md](../../../../tree_plans.md), [docs/code_review.md](../../../../code_review.md) |

```text
for (const auto& node : plan.nodes()) nodes.push_back({{"id",node.id.value},{"kind",node.kind==NodeKind::native ? "native" : "generalized"},
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Export compiled node relations and separator/enumeration projections. |
| inputs / outputs | PhysicalNode range in; IDs/kind/parent/children/scopes/relations/projections out. |
| invariants | native vs generalized two-way label follows actual factory graph; full artifact reconstruction checks external edits later. |
| ownership | Borrowed graph; DOM copies numeric arrays/projection maps. |
| failure | Moved metadata/accessor/DOM failures propagate. |
| cost | O(nodes+children+scope widths+projection widths) traversal/DOM allocations. |
| Design | [src/io/physical.cpp](../../../../../src/io/physical.cpp), [include/crown/io/physical.hpp](../../../../../include/crown/io/physical.hpp), [src/io/json.hpp](../../../../../src/io/json.hpp), [src/io/document.cpp](../../../../../src/io/document.cpp), [src/io/layout.cpp](../../../../../src/io/layout.cpp), [src/io/normalization.cpp](../../../../../src/io/normalization.cpp), [src/planner/lower.cpp](../../../../../src/planner/lower.cpp), [src/planner/compiled_source.cpp](../../../../../src/planner/compiled_source.cpp), [docs/tree_plans.md](../../../../tree_plans.md), [docs/code_review.md](../../../../code_review.md) |

```text
auto steps=Json::array(), outputs=Json::array(), equalities=Json::array();
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Build the n-ary visible assignment program description. |
| inputs / outputs | Enumeration steps/output/equalities in; three owning JSON arrays out. |
| invariants | Depth/result-layout and assignment slots are descriptive; full replay re-lowers and compares exact data. |
| ownership | DOM owns arrays; source layouts/projections borrowed. |
| failure | Projection/accessor/DOM failure propagates before completed artifact. |
| cost | O(steps+step projection widths+outputs+equalities) allocations/traversal. |
| Design | [src/io/physical.cpp](../../../../../src/io/physical.cpp), [include/crown/io/physical.hpp](../../../../../include/crown/io/physical.hpp), [src/io/json.hpp](../../../../../src/io/json.hpp), [src/io/document.cpp](../../../../../src/io/document.cpp), [src/io/layout.cpp](../../../../../src/io/layout.cpp), [src/io/normalization.cpp](../../../../../src/io/normalization.cpp), [src/planner/lower.cpp](../../../../../src/planner/lower.cpp), [src/planner/compiled_source.cpp](../../../../../src/planner/compiled_source.cpp), [docs/tree_plans.md](../../../../tree_plans.md), [docs/code_review.md](../../../../code_review.md) |

## B0020

[Lines 180–183](../../../../../src/io/physical.cpp#L180); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Json write_physical(const CompiledProgram& plan) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Explicitly export immutable native compiler state through the legacy serializer. |
| inputs / outputs | CompiledProgram in; PhysicalPlan::from_compiled creates a caller DTO then write_physical returns owning DOM. |
| invariants | This is a cold compatibility/export boundary; no native internal replanning or update-hot-path operation. |
| ownership | export_program deep-copies ordinary source/query/tree/normalized/identity/policy graphs while descriptor handles can share their actual native owners; temporary plan and DOM overlap. |
| failure | Export/shared Data/identity-cleanup inventory/serialization/OOM failure propagates before return; original program unchanged. |
| cost | Full export graph copies plus complete legacy serializer and prepared identity cleanup traversal; original native account remains charged for any retained descriptor handles. |
| Design | [src/io/physical.cpp](../../../../../src/io/physical.cpp), [include/crown/io/physical.hpp](../../../../../include/crown/io/physical.hpp), [src/io/json.hpp](../../../../../src/io/json.hpp), [src/io/document.cpp](../../../../../src/io/document.cpp), [src/io/layout.cpp](../../../../../src/io/layout.cpp), [src/io/normalization.cpp](../../../../../src/io/normalization.cpp), [src/planner/lower.cpp](../../../../../src/planner/lower.cpp), [src/planner/compiled_source.cpp](../../../../../src/planner/compiled_source.cpp), [docs/tree_plans.md](../../../../tree_plans.md), [docs/code_review.md](../../../../code_review.md) |

## B0022

[Lines 185–218](../../../../../src/io/physical.cpp#L185); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
PhysicalPlan read_physical(std::string_view text,const PhysicalReadLimits& limits) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Rebuild a physical artifact from actual source/tree/options and require exact full canonical serialization. |
| inputs / outputs | Text plus independent host lowering/program limits in; factory-produced PhysicalPlan out. |
| invariants | Only format/lowerer pairs1/v1 and2/v2 accepted; indexed option presence must agree. Re-lower direct CQ or replay normalized SQL(upgrade1to2), independently verify tree/lowering, then compare every encoded field including hash/guarantee/slots/work. |
| ownership | Input DOM, subtree dump/reparse temporaries, rebuilt owning legacy plan, expected DOM and complete dump strings coexist; no native engine/account installed. |
| failure | Parse/version/source/tree/policy/replay/lowering limit/OOM errors propagate; mismatch physical_binding rejects before returned plan. No flag/hash-only shortcut. |
| cost | Full DOM parse, repeated options/source/tree subtree dumps and parses, binding/normalization/lowering work, whole expected serialization plus two complete dump strings. Host lowering limits do not bound all IO allocation/scan work. |
| Design | [src/io/physical.cpp](../../../../../src/io/physical.cpp), [include/crown/io/physical.hpp](../../../../../include/crown/io/physical.hpp), [src/io/json.hpp](../../../../../src/io/json.hpp), [src/io/document.cpp](../../../../../src/io/document.cpp), [src/io/layout.cpp](../../../../../src/io/layout.cpp), [src/io/normalization.cpp](../../../../../src/io/normalization.cpp), [src/planner/lower.cpp](../../../../../src/planner/lower.cpp), [src/planner/compiled_source.cpp](../../../../../src/planner/compiled_source.cpp), [docs/tree_plans.md](../../../../tree_plans.md), [docs/code_review.md](../../../../code_review.md) |

```text
auto rebuilt=[&]() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Select the admitted compile-source reconstruction path. |
| inputs / outputs | Tagged source and serialized tree/options in; local lambda returns newly lowered plan. |
| invariants | direct_cq reads document/tree then lower_tree; normalized_sql reads normalization, optionally upgrades1to2, reads its core tree then lower_normalized; unknown kind rejects. |
| ownership | Source DOM borrowed; each branch owns its local document/program/tree and resulting plan until transferred. |
| failure | Any branch parse/replay/verify/lowering failure aborts enclosing reconstruction; no shared runtime mutation. |
| cost | Actual branch performs cold parsing/validation/normalization/lowering, not a constant metadata dispatch or proof from kind string. |
| Design | [src/io/physical.cpp](../../../../../src/io/physical.cpp), [include/crown/io/physical.hpp](../../../../../include/crown/io/physical.hpp), [src/io/json.hpp](../../../../../src/io/json.hpp), [src/io/document.cpp](../../../../../src/io/document.cpp), [src/io/layout.cpp](../../../../../src/io/layout.cpp), [src/io/normalization.cpp](../../../../../src/io/normalization.cpp), [src/planner/lower.cpp](../../../../../src/planner/lower.cpp), [src/planner/compiled_source.cpp](../../../../../src/planner/compiled_source.cpp), [docs/tree_plans.md](../../../../tree_plans.md), [docs/code_review.md](../../../../code_review.md) |

```text
if (write_physical(rebuilt).dump()!=input.dump()) throw Error("physical_binding","physical artifact differs from complete verified lowering; source, slots, bindings and guarantees must all replay exactly");
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Require exact complete lowering reproduction before publishing the rebuilt plan. |
| inputs / outputs | Factory-produced rebuilt plan and original DOM in; dump-text equality required. |
| invariants | Text comparison preserves JSON numeric-type/spelling distinctions and checks all redundant fields, not merely advertised digest/validity/height labels. |
| ownership | Expected full DOM plus its dump and original DOM dump are ordinary temporary owning graphs/strings; returned plan remains independent. |
| failure | Serialization/dump/OOM/mismatch errors abort before result return. |
| cost | Full expected serializer and two encoded-byte scans/storage plus exact string comparison; this validation is not included in reported lowering work counter. |
| Design | [src/io/physical.cpp](../../../../../src/io/physical.cpp), [include/crown/io/physical.hpp](../../../../../include/crown/io/physical.hpp), [src/io/json.hpp](../../../../../src/io/json.hpp), [src/io/document.cpp](../../../../../src/io/document.cpp), [src/io/layout.cpp](../../../../../src/io/layout.cpp), [src/io/normalization.cpp](../../../../../src/io/normalization.cpp), [src/planner/lower.cpp](../../../../../src/planner/lower.cpp), [src/planner/compiled_source.cpp](../../../../../src/planner/compiled_source.cpp), [docs/tree_plans.md](../../../../tree_plans.md), [docs/code_review.md](../../../../code_review.md) |

## B0023

[Lines 219–219](../../../../../src/io/physical.cpp#L219); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L219-L219:sha256:a992a30ac7c9748c33994a213cb5eed12f62a6204d01f8b49f69db451a145039
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Closes the namespace crown::io at this source boundary; this is a lexical delimiter, not an operation. |
| inputs / outputs | No runtime input or output. Declarations following the span leave the preceding C++ scope. |
| invariants | The delimiter ends the preceding scope's visibility/linkage region; it adds no validation, publication, ownership transfer, or runtime authority. |
| ownership | The delimiter adds no owner. If it ends a function/block with live automatic objects, their normal destructors release those objects; namespace and type-definition closes change no existing object's lifetime. |
| failure | No explicit failure translation or catch is added. If a function/block exit destroys automatic objects, exception behavior follows those destructors; namespace/type closes have no runtime failure path. |
| cost | The delimiter adds no algorithmic work. A function/block exit can run existing automatic-object destructors and cleanup; namespace/type closes have no runtime cost. |
| Design | [src/io/physical.cpp](../../../../../src/io/physical.cpp), [docs/code_specs/files/src/io/physical.cpp.md](physical.cpp.md), [docs/physical_plans.md](../../../../physical_plans.md), [docs/semantics.md](../../../../semantics.md) |
