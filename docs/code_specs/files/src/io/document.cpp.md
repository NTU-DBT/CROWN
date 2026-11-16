# `src/io/document.cpp` — block usage map

[Source](../../../../../src/io/document.cpp) · [Source index](../../../README.md) · [Subsystem contracts](../../../subsystem_contracts.md) · [Reviewed primitives](../../../primitives.md)

Admit bounded external documents/records and serialize explicit public representations at the engine boundary.

Snapshot SHA-256: `a444da894dda0372a08a878469c869ed400888134fc598df0ba58b353f124d02`. 465 lines partitioned into 37 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [io](../../../subsystem_contracts.md#io). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/ingestion.md](../../../../ingestion.md), [docs/query_identity.md](../../../../query_identity.md), [docs/schema_evolution.md](../../../../schema_evolution.md), [docs/cli.md](../../../../cli.md), [docs/query_memory.md](../../../../query_memory.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–19](../../../../../src/io/document.cpp#L1) | Imports dependencies; declares namespace scope. |  · [reviewed contract](#b0001) |
| [B0002 · 20–20](../../../../../src/io/document.cpp#L20) | Callable definition: Json read_json(std::string_view text) | calls detail::parse_json; returns detail::parse_json(text) · [reviewed contract](#b0002) |
| [B0003 · 21–28](../../../../../src/io/document.cpp#L21) | declares namespace scope; declares aliases. |  · [reviewed contract](#b0003) |
| [B0004 · 29–37](../../../../../src/io/document.cpp#L29) | Callable definition: ScalarType read_type(const Json& value, const std::string& path, std::uint64_t format) | calls string, Error; returns ScalarType::int64; ScalarType::string · [reviewed contract](#b0004) |
| [B0005 · 38–56](../../../../../src/io/document.cpp#L38) | Callable definition: Value read_value(const Json& value, const std::string& path, std::uint64_t format) | calls is_boolean, is_string, is_number_unsigned, max; returns value.get&lt;bool&gt;(); value.get&lt;std::string&gt;() · [reviewed contract](#b0005) |
| [B0006 · 57–61](../../../../../src/io/document.cpp#L57) | Callable definition: Row read_row(const Json& value, const std::string& path, std::uint64_t format) | calls array, push_back, read_value; returns result; growth push_back; 1 loop sites · [reviewed contract](#b0006) |
| [B0007 · 62–69](../../../../../src/io/document.cpp#L62) | Callable definition: Json write_value(const Value& value) | calls std::visit, constexpr, to_string, Json; returns std::visit(\[\](const auto& cell) -&gt; Json {; {{@ , cell.to_string()}} · [reviewed contract](#b0007) |
| [B0008 · 70–74](../../../../../src/io/document.cpp#L70) | Callable definition: Json write_row(const Row& row) | calls Json::array, push_back, write_value; returns result; growth push_back; 1 loop sites · [reviewed contract](#b0008) |
| [B0009 · 75–81](../../../../../src/io/document.cpp#L75) | Callable definition: template&lt;class Id&gt; Id lookup(const std::map&lt;std::string, Id&gt;& names, const Json& value, const std::string& path) | calls string, find, end, fail; returns it-&gt;second · [reviewed contract](#b0009) |
| [B0010 · 82–84](../../../../../src/io/document.cpp#L82) | Closes surrounding scope/type. | source comment (unverified): // namespace · [reviewed contract](#b0010) |
| [B0011 · 85–172](../../../../../src/io/document.cpp#L85) | Callable definition: Document read_document(std::string_view text) | calls parse_json, fields, unsigned_integer, at; returns document; growth emplace, emplace_back, insert, push_back, resize; 10 loop sites; source comment (unverified): // Ordinary owning DOM/model boundary; native admission and update execution follow later. · [reviewed contract](#b0011) |
| [B0012 · 173–173](../../../../../src/io/document.cpp#L173) | Explanatory comments or spacing. |  |
| [B0013 · 174–181](../../../../../src/io/document.cpp#L174) | Callable definition: Document upgrade_document(const Document& document, std::uint64_t target_version) | calls Error, write_document; returns result · [reviewed contract](#b0013) |
| [B0014 · 182–182](../../../../../src/io/document.cpp#L182) | Explanatory comments or spacing. |  |
| [B0015 · 183–187](../../../../../src/io/document.cpp#L183) | Callable definition: Json write_relation(const Relation& relation) | calls Json::array, push_back, write_row; returns result; growth push_back; 1 loop sites · [reviewed contract](#b0015) |
| [B0016 · 188–188](../../../../../src/io/document.cpp#L188) | Callable definition: Json write_scalar(const Value& value) | calls write_value; returns write_value(value) · [reviewed contract](#b0016) |
| [B0017 · 189–189](../../../../../src/io/document.cpp#L189) | Explanatory comments or spacing. | source comment (unverified): // JSON copies borrowed/stack scalar text; the returned DOM owns its bytes. · [reviewed contract](#b0017) |
| [B0018 · 190–199](../../../../../src/io/document.cpp#L190) | Callable definition: Json write_scalar_view(const storage::ScalarView& value) | calls std::visit, constexpr, to_string, render; returns std::visit(\[\](const auto& cell)-&gt;Json {; {{@ ,cell.to_string()}}; source comment (unverified): // JSON copies borrowed/stack scalar text; the returned DOM owns its bytes. · [reviewed contract](#b0018) |
| [B0019 · 200–200](../../../../../src/io/document.cpp#L200) | Callable definition: Value read_scalar(const Json& value) | calls read_value; returns read_value(value,@ ,3) · [reviewed contract](#b0019) |
| [B0020 · 201–204](../../../../../src/io/document.cpp#L201) | Callable definition: Json write_epoch(const CommittedReferenceEpoch& epoch) | calls write_relation; returns {{@ , epoch.sequence}, {@ , epoch.input_changed}, {@ , write_relation(epoch.current)}, · [reviewed contract](#b0020) |
| [B0021 · 205–205](../../../../../src/io/document.cpp#L205) | Explanatory comments or spacing. |  |
| [B0022 · 206–252](../../../../../src/io/document.cpp#L206) | Callable definition: Json write_document(const Document& document) | calls Error, catalog::requires_format3, validate, validate_database; returns {{@ , document.schema_version}, {@ , @ }, {@ , std::move(catalog_payload)},; growth insert, push_back; 8 loop sites; source comment (unverified): // Format 3 builds a separate rich DOM while the legacy table DOM remains local. · [reviewed contract](#b0022) |
| [B0023 · 253–254](../../../../../src/io/document.cpp#L253) | Explanatory comments or spacing. | source comment (unverified): // Decode names and claims only; independent tree verification grants an upper bound. · [reviewed contract](#b0023) |
| [B0024 · 255–307](../../../../../src/io/document.cpp#L255) | Callable definition: FreeConnexTree read_tree(std::string_view text, const Catalog& catalog, const Query& query) | calls validate, parse_json, fields, version; returns scope; tree; growth emplace, insert, push_back; 7 loop sites; source comment (unverified): // Decode names and claims only; independent tree verification grants an upper bound. · [reviewed contract](#b0024) |
| [B0025 · 308–309](../../../../../src/io/document.cpp#L308) | Explanatory comments or spacing. | source comment (unverified): // Addressability checks do not verify graph structure or claimed height. · [reviewed contract](#b0025) |
| [B0026 · 310–351](../../../../../src/io/document.cpp#L310) | Callable definition: Json write_tree(const FreeConnexTree& tree, const Catalog& catalog, const Query& query) | calls validate, empty, insert, fail; returns tree.nodes\[id.value\].id; value; growth insert, push_back; 5 loop sites; source comment (unverified): // Addressability checks do not verify graph structure or claimed height. · [reviewed contract](#b0026) |
| [B0027 · 352–353](../../../../../src/io/document.cpp#L352) | Explanatory comments or spacing. | source comment (unverified): // Report formatting trusts the supplied aggregate; it does not rerun the verifier. · [reviewed contract](#b0027) |
| [B0028 · 354–379](../../../../../src/io/document.cpp#L354) | Callable definition: Json write_validation(const planner::ValidationReport& report, const FreeConnexTree& tree, const Query& query) | calls size, std::to_string, Json::array, push_back; returns id.value &lt; tree.nodes.size() ? tree.nodes\[id.value\].id : @ + std::to_string(id.value) + @; id.value…; growth push_back; 4 loop sites; source comment (unverified): // Report formatting trusts the supplied aggregate; it does not rerun the verifier. · [reviewed contract](#b0028) |
| [B0029 · 380–382](../../../../../src/io/document.cpp#L380) | declares namespace scope; declares aliases. |  · [reviewed contract](#b0029) |
| [B0030 · 383–387](../../../../../src/io/document.cpp#L383) | Callable definition: std::size_t index_value(const Json& value, const std::string& path) | calls unsigned_integer, max, fail; returns static_cast&lt;std::size_t&gt;(number) · [reviewed contract](#b0030) |
| [B0031 · 388–390](../../../../../src/io/document.cpp#L388) | Closes surrounding scope/type. | source comment (unverified): // namespace · [reviewed contract](#b0031) |
| [B0032 · 391–429](../../../../../src/io/document.cpp#L391) | Callable definition: Json write_oracle(const planner::OracleResult& result, const Catalog& catalog, const Query& query) | calls Error, write_tree, Json, Json::array; returns {{@ , 1}, {@ , result.tree.has_value()}, {@ , height},; growth push_back; 1 loop sites; source comment (unverified): // Legacy flag gate: this serializer does not independently replay the proof. · [reviewed contract](#b0032) |
| [B0033 · 430–431](../../../../../src/io/document.cpp#L430) | Explanatory comments or spacing. | source comment (unverified): // Binding/type checks produce an unverified claim; whole independent replay is separate. · [reviewed contract](#b0033) |
| [B0034 · 432–459](../../../../../src/io/document.cpp#L432) | Callable definition: planner::HeightCertificate read_height_certificate(std::string_view text, const Catalog& catalog, const Query& query) | calls parse_json, fields, unsigned_integer, at; returns certificate; growth push_back; 2 loop sites; source comment (unverified): // Binding/type checks produce an unverified claim; whole independent replay is separate. · [reviewed contract](#b0034) |
| [B0035 · 460–460](../../../../../src/io/document.cpp#L460) | Explanatory comments or spacing. |  |
| [B0036 · 461–464](../../../../../src/io/document.cpp#L461) | Callable definition: Json write_certificate_report(const planner::CertificateReport& report) | calls ; returns {{@ , 1}, {@ , report.valid}, {@ , report.resource_limit}, · [reviewed contract](#b0036) |
| [B0037 · 465–465](../../../../../src/io/document.cpp#L465) | Closes surrounding scope/type. | source comment (unverified): // namespace crown::io · [reviewed contract](#b0037) |

## B0001

[Lines 1–19](../../../../../src/io/document.cpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L1-L19:sha256:34128c25e48fd4fa7ee3072129363ca056f9f366d081dd5d7917be0b7a35d6cc
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Imports compile-time dependencies (crown/io/document.hpp, crown/io/tree.hpp, crown/io/oracle.hpp, crown/io/catalog.hpp, crown/catalog/catalog.hpp, json.hpp) and opens crown::io scope for the declarations or definitions that follow. |
| inputs / outputs | No runtime inputs/outputs are declared by the import/scope lines themselves. |
| invariants | The listed headers and namespace membership determine compile-time name availability; any API behavior belongs to the declarations/definitions that follow. |
| ownership | No object ownership is created by the imports or namespace tokens. |
| failure | No runtime failure path. Missing/incompatible dependencies or a violated compile-time constraint fail translation/linking. |
| cost | Compile/preprocessor work only; no new per-operation runtime overhead. |
| Design | [src/io/document.cpp](../../../../../src/io/document.cpp), [docs/code_specs/files/src/io/document.cpp.md](document.cpp.md), [docs/semantics.md](../../../../semantics.md), [docs/tree_plans.md](../../../../tree_plans.md), [docs/planner_proofs.md](../../../../planner_proofs.md) |

## B0002

[Lines 20–20](../../../../../src/io/document.cpp#L20); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Json read_json(std::string_view text)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Expose the strict external JSON parser before artifact-specific checks. |
| inputs / outputs | Immutable text returns owning Json through detail::parse_json. |
| invariants | Callback rejects duplicate keys and nesting deeper than 256 before DOM ambiguity is lost. Does not validate a CQ/tree/certificate schema, enforce a byte/item/account cap or establish proof authority. |
| ownership | Borrows immutable caller values synchronously; returns owning ordinary JSON/native DTO data and changes no native producer, source or durable state. |
| failure | JSON exceptions become Error(invalid_document) in shared parser; duplicate/depth Errors and allocation failures propagate unchanged. Vendored DOM already has the pinned allocation-failure cleanup repair. |
| cost | O(input parsing plus ordered-set key insert/comparison costs), full ordinary DOM and temporary key-set/string ownership; not allocation-free. |
| Design | [src/io/json.hpp](../../../../../src/io/json.hpp), [third_party/nlohmann/json.hpp](../../../../../third_party/nlohmann/json.hpp), [include/crown/io/document.hpp](../../../../../include/crown/io/document.hpp) |

## B0003

[Lines 21–28](../../../../../src/io/document.cpp#L21); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L21-L28:sha256:72d3978674f8ff329c2d89ee127592ef859c52c5e9c9565787fc86b8ec281bcb
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Opens the private document-codec namespace and imports the shared JSON validators/reader helpers for the typed document decoders that follow. |
| inputs / outputs | No runtime inputs/outputs are declared by the import/scope lines themselves. |
| invariants | The listed headers and namespace membership determine compile-time name availability; any API behavior belongs to the declarations/definitions that follow. |
| ownership | No object ownership is created by the imports or namespace tokens. |
| failure | No runtime failure path. Missing/incompatible dependencies or a violated compile-time constraint fail translation/linking. |
| cost | Compile/preprocessor work only; no new per-operation runtime overhead. |
| Design | [src/io/document.cpp](../../../../../src/io/document.cpp), [docs/code_specs/files/src/io/document.cpp.md](document.cpp.md), [docs/semantics.md](../../../../semantics.md), [docs/tree_plans.md](../../../../tree_plans.md), [docs/planner_proofs.md](../../../../planner_proofs.md) |

## B0004

[Lines 29–37](../../../../../src/io/document.cpp#L29); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
ScalarType read_type(const Json& value, const std::string& path, std::uint64_t format)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Decode a version-supported scalar type name. |
| inputs / outputs | Requires JSON string; maps int64/string/bool in all document formats, date/decimal only for format&gt;=2. |
| invariants | No implicit type aliases, float/NULL type or runtime casting. Caller supplies already-admitted document version. |
| ownership | Borrows immutable caller values synchronously; returns owning ordinary JSON/native DTO data and changes no native producer, source or durable state. |
| failure | Error(unsupported_type) for unknown/version-incompatible type; invalid JSON kind and allocation failures propagate. |
| cost | Copies type-name string then fixed comparisons; string/path/diagnostic work may allocate. |
| Design | [include/crown/io/document.hpp](../../../../../include/crown/io/document.hpp), [docs/semantics.md §Tables, occurrences and values](../../../../semantics.md), [docs/scalars.md §Typed JSON values](../../../../scalars.md) |

## B0005

[Lines 38–56](../../../../../src/io/document.cpp#L38); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Value read_value(const Json& value, const std::string& path, std::uint64_t format)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Decode one exact nonnull external scalar with contextual errors. |
| inputs / outputs | Accepts bool, owning string, int64-range integers, and format&gt;=2 one-key date/decimal string objects parsed by their exact scalar parsers. |
| invariants | Unsigned values above INT64_MAX reject; NULL/float/implicit casts reject. Only Date/Decimal Error is caught to prepend path while preserving code; this is an external DTO codec, not native row/schema admission. |
| ownership | Borrows immutable caller values synchronously; returns owning ordinary JSON/native DTO data and changes no native producer, source or durable state. |
| failure | Narrow Error catch annotates typed date/decimal rejection; MemoryFailure/bad_alloc and non-Error exceptions bypass it. Other malformed scalars use invalid_document. |
| cost | O(string/scalar text bytes), ordinary owning string/Decimal storage and scalar parsing; error path builds contextual diagnostic strings. |
| Design | [include/crown/io/document.hpp](../../../../../include/crown/io/document.hpp), [docs/semantics.md §Tables, occurrences and values](../../../../semantics.md), [docs/scalars.md §Typed JSON values](../../../../scalars.md), [src/ir/scalar.cpp](../../../../../src/ir/scalar.cpp) |

## B0006

[Lines 57–61](../../../../../src/io/document.cpp#L57); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Row read_row(const Json& value, const std::string& path, std::uint64_t format)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Decode an owning row from a JSON array. |
| inputs / outputs | Appends each read_value result into ordinary Row vector using supplied document version/path. |
| invariants | No row arity/table-type/constraint check here; read_document validates the completed row against its catalog. Order is preserved, no NULL/coercion added. |
| ownership | Borrows immutable caller values synchronously; returns owning ordinary JSON/native DTO data and changes no native producer, source or durable state. |
| failure | Validation/encoding Error, JSON/library and allocation failures propagate; private ordinary strings/vectors/DOMs unwind. No partial public result or producer progress is published. |
| cost | O(fields plus scalar payload parsing/copies), vector growth and owning text/Decimal allocations; no reserve or explicit field/byte quota. |
| Design | [include/crown/io/document.hpp](../../../../../include/crown/io/document.hpp), [docs/semantics.md §Tables, occurrences and values](../../../../semantics.md), [docs/scalars.md §Typed JSON values](../../../../scalars.md) |

## B0007

[Lines 62–69](../../../../../src/io/document.cpp#L62); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Json write_value(const Value& value)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Create an owning JSON scalar node from an ordinary Value. |
| inputs / outputs | Visits int/string/bool directly; Date/Decimal produce one-key typed objects with formatted text. |
| invariants | Typed output retains exact Date/Decimal representation rather than float conversion. Strings are copied, not borrowed; strict dump encoding can still fail later for invalid native UTF8. |
| ownership | Borrows immutable caller values synchronously; returns owning ordinary JSON/native DTO data and changes no native producer, source or durable state. |
| failure | Validation/encoding Error, JSON/library and allocation failures propagate; private ordinary strings/vectors/DOMs unwind. No partial public result or producer progress is published. |
| cost | O(text/scalar-format bytes), ordinary Json string/object allocations and Date/Decimal formatting; not allocation-free. |
| Design | [include/crown/io/document.hpp](../../../../../include/crown/io/document.hpp), [docs/semantics.md §Tables, occurrences and values](../../../../semantics.md), [docs/scalars.md §Typed JSON values](../../../../scalars.md), [src/io/json.hpp](../../../../../src/io/json.hpp), [third_party/nlohmann/json.hpp](../../../../../third_party/nlohmann/json.hpp) |

## B0008

[Lines 70–74](../../../../../src/io/document.cpp#L70); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Json write_row(const Row& row)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Build an owning JSON array for one ordinary row. |
| inputs / outputs | Calls write_value per cell and appends into Json array in field order. |
| invariants | No table schema check, row deduplication, source advance or output-stream I/O. DOM construction alone is separate from final text encoding. |
| ownership | Borrows immutable caller values synchronously; returns owning ordinary JSON/native DTO data and changes no native producer, source or durable state. |
| failure | Validation/encoding Error, JSON/library and allocation failures propagate; private ordinary strings/vectors/DOMs unwind. No partial public result or producer progress is published. |
| cost | O(fields plus payload/format bytes), dynamic Json array growth and nested string/object ownership; no export cap. |
| Design | [include/crown/io/document.hpp](../../../../../include/crown/io/document.hpp), [docs/semantics.md §Tables, occurrences and values](../../../../semantics.md), [docs/scalars.md §Typed JSON values](../../../../scalars.md), [src/io/json.hpp](../../../../../src/io/json.hpp), [third_party/nlohmann/json.hpp](../../../../../third_party/nlohmann/json.hpp) |

## B0009

[Lines 75–81](../../../../../src/io/document.cpp#L75); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
template<class Id> Id lookup(const std::map<std::string, Id>& names, const Json& value, const std::string& path)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Resolve one named external identifier against a prepared ordered map. |
| inputs / outputs | Requires JSON string, copies name, finds it in map and returns typed ID; missing name yields contextual invalid_document. |
| invariants | Map was built by the containing document/tree parser; this helper does not create IDs, validate uniqueness or accept numeric aliases. |
| ownership | Input map/DOM borrowed synchronously; only copied typed ID escapes. |
| failure | Validation/encoding Error, JSON/library and allocation failures propagate; private ordinary strings/vectors/DOMs unwind. No partial public result or producer progress is published. |
| cost | O(name bytes plus log(map size) string comparisons), copied string/path/error may allocate; returned ID is fixed. |
| Design | [include/crown/io/document.hpp](../../../../../include/crown/io/document.hpp), [docs/semantics.md §Tables, occurrences and values](../../../../semantics.md), [docs/scalars.md §Typed JSON values](../../../../scalars.md), [src/io/json.hpp](../../../../../src/io/json.hpp), [third_party/nlohmann/json.hpp](../../../../../third_party/nlohmann/json.hpp) |

## B0010

[Lines 82–84](../../../../../src/io/document.cpp#L82); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L82-L84:sha256:9e91c6c9c15f2da016079421e26dab73ab13b9415757af3d191b5e490950f8b3
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Closes the anonymous namespace at this source boundary; this is a lexical delimiter, not an operation. Trailing source note states: Ordinary owning DOM/model boundary; native admission and update execution follow later. It remains prose guidance, not a certified executable claim. |
| inputs / outputs | No runtime input or output. Declarations following the span leave the preceding C++ scope. |
| invariants | The delimiter ends the preceding scope's visibility/linkage region; it adds no validation, publication, ownership transfer, or runtime authority. Any trailing comment in this block is guidance only and adds no runtime invariant. |
| ownership | The delimiter adds no owner. If it ends a function/block with live automatic objects, their normal destructors release those objects; namespace and type-definition closes change no existing object's lifetime. |
| failure | No explicit failure translation or catch is added. If a function/block exit destroys automatic objects, exception behavior follows those destructors; namespace/type closes have no runtime failure path. |
| cost | The delimiter adds no algorithmic work. A function/block exit can run existing automatic-object destructors and cleanup; namespace/type closes have no runtime cost. |
| Design | [src/io/document.cpp](../../../../../src/io/document.cpp), [docs/code_specs/files/src/io/document.cpp.md](document.cpp.md), [docs/semantics.md](../../../../semantics.md), [docs/tree_plans.md](../../../../tree_plans.md), [docs/planner_proofs.md](../../../../planner_proofs.md) |

## B0011

[Lines 85–172](../../../../../src/io/document.cpp#L85); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Document read_document(std::string_view text)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Parse and validate an owning direct-CQ set document in formats 1 through 3. |
| inputs / outputs | Strict DOM requires exact fields, version/set semantics; decodes legacy/rich catalog, named query variables/occurrences/terms/head/contradiction, optional initial sets and contiguous updates from sequence 1. |
| invariants | Core validate rejects nullable catalog columns, duplicate/unbound identifiers, arity/types and invalid native query. Initial table blocks are unique; duplicate rows collapse in Relation sets. Row validation and initial enforced key/FK checks run, but updates are not executed and do not prove future constraint-preserving native transitions. |
| ownership | Returned Document deep-owns ordinary metadata, values, sets and updates; retains no input text/DOM view. Private parse/model/key containers release on rejection. |
| failure | Validation/encoding Error, JSON/library and allocation failures propagate; private ordinary strings/vectors/DOMs unwind. No partial public result or producer progress is published. |
| cost | Full input DOM plus owning Catalog/Query/Database/update vector coexist; name maps/sets and relation inserts allocate/copy with log comparisons. Final validate_database rescans rows and builds projected key sets for each enforced unique/FK constraint. No parser byte/row/field/work/account cap beyond shared nesting limit. |
| Design | [include/crown/io/document.hpp](../../../../../include/crown/io/document.hpp), [docs/semantics.md §Tables, occurrences and values](../../../../semantics.md), [docs/scalars.md §Typed JSON values](../../../../scalars.md), [src/io/json.hpp](../../../../../src/io/json.hpp), [third_party/nlohmann/json.hpp](../../../../../third_party/nlohmann/json.hpp), [src/ir/model.cpp](../../../../../src/ir/model.cpp), [src/catalog/catalog.cpp](../../../../../src/catalog/catalog.cpp), [docs/catalog.md §Validation and canonical writing](../../../../catalog.md), [src/io/catalog.cpp](../../../../../src/io/catalog.cpp) |

## B0013

[Lines 174–181](../../../../../src/io/document.cpp#L174); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Document upgrade_document(const Document& document, std::uint64_t target_version)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Produce a validated explicit upward or same-version document copy. |
| inputs / outputs | Target must be &gt;=source version and within 1..3. Builds/discards source write_document DOM, deep-copies Document, changes root version, builds/discards target DOM and returns copy. |
| invariants | No downgrade or inferred metadata/scalar/NULL/constraint change. Embedded update version is generated from the chosen root on later export; logical rows/query/update order stay unchanged. |
| ownership | Borrows immutable caller values synchronously; returns owning ordinary JSON/native DTO data and changes no native producer, source or durable state. |
| failure | Validation/encoding Error, JSON/library and allocation failures propagate; private ordinary strings/vectors/DOMs unwind. No partial public result or producer progress is published. |
| cost | Two complete write_document validation/DOM builds plus a full model/initial/update deep copy. Ordinary temporary DOMs and result overlap source; no native account or migration work quota. |
| Design | [include/crown/io/document.hpp](../../../../../include/crown/io/document.hpp), [docs/semantics.md §Tables, occurrences and values](../../../../semantics.md), [docs/scalars.md §Typed JSON values](../../../../scalars.md), [docs/schema_evolution.md §Explicit direct-CQ migration](../../../../schema_evolution.md) |

## B0015

[Lines 183–187](../../../../../src/io/document.cpp#L183); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Json write_relation(const Relation& relation)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Export an ordinary set Relation as a JSON row array. |
| inputs / outputs | Visits relation ordered iteration, writing each row to an owning Json array. |
| invariants | Only supplied rows are read; this is neither a native runtime snapshot operation nor incremental/durable output acknowledgement. |
| ownership | Borrows immutable caller values synchronously; returns owning ordinary JSON/native DTO data and changes no native producer, source or durable state. |
| failure | Validation/encoding Error, JSON/library and allocation failures propagate; private ordinary strings/vectors/DOMs unwind. No partial public result or producer progress is published. |
| cost | O(all row/cell/payload bytes) traversal and nested DOM allocations; output has no byte/item quota. |
| Design | [include/crown/io/document.hpp](../../../../../include/crown/io/document.hpp), [docs/semantics.md §Tables, occurrences and values](../../../../semantics.md), [docs/scalars.md §Typed JSON values](../../../../scalars.md), [src/io/json.hpp](../../../../../src/io/json.hpp), [third_party/nlohmann/json.hpp](../../../../../third_party/nlohmann/json.hpp) |

## B0016

[Lines 188–188](../../../../../src/io/document.cpp#L188); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Json write_scalar(const Value& value)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Expose owning ordinary Value-to-JSON scalar conversion. |
| inputs / outputs | Delegates to write_value for exact scalar/typed object representation. |
| invariants | No native schema check, implicit cast or output-text write; the DOM owns all strings. |
| ownership | Borrows immutable caller values synchronously; returns owning ordinary JSON/native DTO data and changes no native producer, source or durable state. |
| failure | Validation/encoding Error, JSON/library and allocation failures propagate; private ordinary strings/vectors/DOMs unwind. No partial public result or producer progress is published. |
| cost | Same scalar formatting/copy/object allocation as write_value, fixed forwarding overhead. |
| Design | [include/crown/io/document.hpp](../../../../../include/crown/io/document.hpp), [docs/semantics.md §Tables, occurrences and values](../../../../semantics.md), [docs/scalars.md §Typed JSON values](../../../../scalars.md), [src/io/json.hpp](../../../../../src/io/json.hpp), [third_party/nlohmann/json.hpp](../../../../../third_party/nlohmann/json.hpp) |

## B0017

[Lines 189–189](../../../../../src/io/document.cpp#L189); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L189-L189:sha256:7928a0c4969421399984ffef375e816bdd437bed9734a00a6c221b5b1794f013
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Design note for adjacent code: JSON copies borrowed/stack scalar text; the returned DOM owns its bytes. This is caller guidance recorded as prose, not an executable result. |
| inputs / outputs | No runtime interface is implemented by these comment-only lines. They sit at src/io/document.cpp lines 187-191; the surrounding declaration/body defines its own inputs and outputs. |
| invariants | The words record the intended use boundary only. They do not add a guard, proof, capability, transaction, durability guarantee, or account charge; verify behavior in the referenced implementation. |
| ownership | Comment text owns no data. Object lifetimes, borrows, and account attribution remain those of the adjacent source objects and their constructors. |
| failure | No failure path is implemented here. Any mentioned failure or recovery rule belongs to the adjacent operation and its existing error carrier. |
| cost | No runtime work is performed by these lines; any cost/bound in the note is not certified by this comment-only card. |
| Design | [src/io/document.cpp](../../../../../src/io/document.cpp), [docs/code_specs/files/src/io/document.cpp.md](document.cpp.md), [docs/semantics.md](../../../../semantics.md), [docs/tree_plans.md](../../../../tree_plans.md), [docs/planner_proofs.md](../../../../planner_proofs.md) |

## B0018

[Lines 190–199](../../../../../src/io/document.cpp#L190); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Json write_scalar_view(const storage::ScalarView& value)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Export a borrowed native ScalarView into an owning Json value. |
| inputs / outputs | Visits exact scalar type; Date formats text, InlineDecimal renders into fixed stack buffer then Json copies the view, other values construct owning Json. |
| invariants | Stack decimal bytes and native string views do not escape. Stack rendering avoids an ordinary Decimal conversion but JSON string/object ownership still allocates; final UTF8 dump is a separate boundary. |
| ownership | Native ScalarView borrowed synchronously; returned DOM deep-owns text and survives source/stack destruction. |
| failure | Validation/encoding Error, JSON/library and allocation failures propagate; private ordinary strings/vectors/DOMs unwind. No partial public result or producer progress is published. |
| cost | O(string/formatted scalar bytes), fixed decimal stack scratch plus ordinary Json string/object allocations; not allocation-free. |
| Design | [include/crown/io/document.hpp](../../../../../include/crown/io/document.hpp), [docs/semantics.md §Tables, occurrences and values](../../../../semantics.md), [docs/scalars.md §Typed JSON values](../../../../scalars.md), [src/io/json.hpp](../../../../../src/io/json.hpp), [third_party/nlohmann/json.hpp](../../../../../third_party/nlohmann/json.hpp), [include/crown/storage/accounted_row.hpp](../../../../../include/crown/storage/accounted_row.hpp) |

## B0019

[Lines 200–200](../../../../../src/io/document.cpp#L200); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Value read_scalar(const Json& value)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Decode one scalar using current direct-CQ scalar rules. |
| inputs / outputs | Delegates to read_value with path $ and format 3, returning owning Value. |
| invariants | Allows exact date/decimal typed objects, rejects NULL/float/implicit coercion; no table schema or SQL nullable-row admission. |
| ownership | Borrows immutable caller values synchronously; returns owning ordinary JSON/native DTO data and changes no native producer, source or durable state. |
| failure | Validation/encoding Error, JSON/library and allocation failures propagate; private ordinary strings/vectors/DOMs unwind. No partial public result or producer progress is published. |
| cost | Scalar parse/string/Decimal ownership cost from read_value; no independent byte/work quota. |
| Design | [include/crown/io/document.hpp](../../../../../include/crown/io/document.hpp), [docs/semantics.md §Tables, occurrences and values](../../../../semantics.md), [docs/scalars.md §Typed JSON values](../../../../scalars.md) |

## B0020

[Lines 201–204](../../../../../src/io/document.cpp#L201); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Json write_epoch(const CommittedReferenceEpoch& epoch)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Export a completed reference epoch DTO including its full sets. |
| inputs / outputs | Writes sequence/input_changed, complete current relation, added set and removed set. |
| invariants | Does not validate epoch correctness, derive the delta, commit a native epoch or persist/acknowledge output; caller supplies the reference aggregate. |
| ownership | Borrows immutable caller values synchronously; returns owning ordinary JSON/native DTO data and changes no native producer, source or durable state. |
| failure | Validation/encoding Error, JSON/library and allocation failures propagate; private ordinary strings/vectors/DOMs unwind. No partial public result or producer progress is published. |
| cost | Traverses and allocates owning DOMs for current plus both delta relations; duplicated values are copied independently and can overlap nested initializer temporaries. |
| Design | [include/crown/io/document.hpp](../../../../../include/crown/io/document.hpp), [docs/semantics.md §Tables, occurrences and values](../../../../semantics.md), [docs/scalars.md §Typed JSON values](../../../../scalars.md), [src/io/json.hpp](../../../../../src/io/json.hpp), [third_party/nlohmann/json.hpp](../../../../../third_party/nlohmann/json.hpp) |

## B0022

[Lines 206–252](../../../../../src/io/document.cpp#L206); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Json write_document(const Document& document)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Validate and export a version-preserving direct-CQ document DOM. |
| inputs / outputs | Admits schema 1..3 and compatible catalog metadata, validates query and whole initial database, serializes catalog/query/initial sets and checks contiguous typed update envelopes/rows. |
| invariants | Version 1 rejects date/decimal catalog columns; formats&lt;3 reject rich catalog metadata. This emits mutable descriptive data, not a compiled/native/proof artifact, and it does not execute updates or prove post-update constraints. |
| ownership | Borrows Document and deep-copies all exported strings/values into ordinary DOM. Source remains unchanged, including schema_version. |
| failure | Validation/encoding Error, JSON/library and allocation failures propagate; private ordinary strings/vectors/DOMs unwind. No partial public result or producer progress is published. |
| cost | Whole metadata/initial/update scan and owning nested DOM; validate_database also builds enforced unique/FK projected key sets. Format 3 first builds the legacy table/column DOM then separately builds rich catalog payload, retaining the unused legacy temporary until return. No export byte/item/work/account quota. |
| Design | [include/crown/io/document.hpp](../../../../../include/crown/io/document.hpp), [docs/semantics.md §Tables, occurrences and values](../../../../semantics.md), [docs/scalars.md §Typed JSON values](../../../../scalars.md), [src/ir/model.cpp](../../../../../src/ir/model.cpp), [src/catalog/catalog.cpp](../../../../../src/catalog/catalog.cpp), [docs/catalog.md §Validation and canonical writing](../../../../catalog.md), [src/io/catalog.cpp](../../../../../src/io/catalog.cpp), [docs/schema_evolution.md §Explicit direct-CQ migration](../../../../schema_evolution.md) |

## B0023

[Lines 253–254](../../../../../src/io/document.cpp#L253); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L253-L254:sha256:c10b814ea23aa76c178d2e62e3340143896df488591053d937346028f9d909e4
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Design note for adjacent code: Decode names and claims only; independent tree verification grants an upper bound. This is caller guidance recorded as prose, not an executable result. |
| inputs / outputs | No runtime interface is implemented by these comment-only lines. They sit at src/io/document.cpp lines 251-256; the surrounding declaration/body defines its own inputs and outputs. |
| invariants | The words record the intended use boundary only. They do not add a guard, proof, capability, transaction, durability guarantee, or account charge; verify behavior in the referenced implementation. |
| ownership | Comment text owns no data. Object lifetimes, borrows, and account attribution remain those of the adjacent source objects and their constructors. |
| failure | No failure path is implemented here. Any mentioned failure or recovery rule belongs to the adjacent operation and its existing error carrier. |
| cost | No runtime work is performed by these lines; any cost/bound in the note is not certified by this comment-only card. |
| Design | [src/io/document.cpp](../../../../../src/io/document.cpp), [docs/code_specs/files/src/io/document.cpp.md](document.cpp.md), [docs/semantics.md](../../../../semantics.md), [docs/tree_plans.md](../../../../tree_plans.md), [docs/planner_proofs.md](../../../../planner_proofs.md) |

## B0024

[Lines 255–307](../../../../../src/io/document.cpp#L255); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
FreeConnexTree read_tree(std::string_view text, const Catalog& catalog, const Query& query)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Decode a named structural-tree claim without verifying it. |
| inputs / outputs | Validates supplied Catalog/Query, strict version-1 set-plan DOM/catalog version and node IDs; resolves named variables/occurrences/children/root, scopes and optional separator/connex/native-height claims. |
| invariants | Native/generalized fields are exact; node IDs nonempty/unique, scope variables unique and references known. Graph connectedness/acyclicity/coverage/running-intersection/connex/claimed-height truth require the independent verifier. A parsed FreeConnexTree is not a ValidatedIncumbent. |
| ownership | Returned tree owns IDs/containers and retains no DOM/text borrow; supplied query/catalog only read. |
| failure | Validation/encoding Error, JSON/library and allocation failures propagate; private ordinary strings/vectors/DOMs unwind. No partial public result or producer progress is published. |
| cost | Full DOM, ordinary name maps and owning node/child/set/claim vectors; ordered lookups and scope inserts add log comparisons and name copies. No node/byte/work cap beyond shared JSON nesting. |
| Design | [include/crown/io/tree.hpp](../../../../../include/crown/io/tree.hpp), [docs/tree_plans.md §Plan document](../../../../tree_plans.md), [docs/tree_plans.md §What is checked](../../../../tree_plans.md), [src/io/json.hpp](../../../../../src/io/json.hpp), [third_party/nlohmann/json.hpp](../../../../../third_party/nlohmann/json.hpp), [src/ir/model.cpp](../../../../../src/ir/model.cpp), [src/catalog/catalog.cpp](../../../../../src/catalog/catalog.cpp), [docs/catalog.md §Validation and canonical writing](../../../../catalog.md), [include/crown/planner/verify.hpp](../../../../../include/crown/planner/verify.hpp) |

## B0025

[Lines 308–309](../../../../../src/io/document.cpp#L308); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L308-L309:sha256:583270c82ae448896bbb30980e0f50e54d74016aff946cf11f86f02e75082339
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Design note for adjacent code: Addressability checks do not verify graph structure or claimed height. This is caller guidance recorded as prose, not an executable result. |
| inputs / outputs | No runtime interface is implemented by these comment-only lines. They sit at src/io/document.cpp lines 306-311; the surrounding declaration/body defines its own inputs and outputs. |
| invariants | The words record the intended use boundary only. They do not add a guard, proof, capability, transaction, durability guarantee, or account charge; verify behavior in the referenced implementation. |
| ownership | Comment text owns no data. Object lifetimes, borrows, and account attribution remain those of the adjacent source objects and their constructors. |
| failure | No failure path is implemented here. Any mentioned failure or recovery rule belongs to the adjacent operation and its existing error carrier. |
| cost | No runtime work is performed by these lines; any cost/bound in the note is not certified by this comment-only card. |
| Design | [src/io/document.cpp](../../../../../src/io/document.cpp), [docs/code_specs/files/src/io/document.cpp.md](document.cpp.md), [docs/semantics.md](../../../../semantics.md), [docs/tree_plans.md](../../../../tree_plans.md), [docs/planner_proofs.md](../../../../planner_proofs.md) |

## B0026

[Lines 310–351](../../../../../src/io/document.cpp#L310); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Json write_tree(const FreeConnexTree& tree, const Catalog& catalog, const Query& query)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Export a named structural-tree DTO with addressability checks. |
| inputs / outputs | Validates supplied Catalog/Query and checks node-ID uniqueness, referenced node/variable/occurrence bounds and native/generalized occurrence shape; writes root/nodes and optional supplied claims. |
| invariants | No structural checker runs. Cycles, duplicate children, invalid coverage/connex/height claims can still serialize; tree validity/minimum authority is not established by successful writing. |
| ownership | Borrows immutable caller values synchronously; returns owning ordinary JSON/native DTO data and changes no native producer, source or durable state. |
| failure | Validation/encoding Error, JSON/library and allocation failures propagate; private ordinary strings/vectors/DOMs unwind. No partial public result or producer progress is published. |
| cost | O(nodes plus edge/scope/claim entries and copied name bytes), name uniqueness set and owning nested DOM. node_name returns owning string copies per reference; no output byte/node/work cap. |
| Design | [include/crown/io/tree.hpp](../../../../../include/crown/io/tree.hpp), [docs/tree_plans.md §Plan document](../../../../tree_plans.md), [docs/tree_plans.md §What is checked](../../../../tree_plans.md), [src/io/json.hpp](../../../../../src/io/json.hpp), [third_party/nlohmann/json.hpp](../../../../../third_party/nlohmann/json.hpp), [src/ir/model.cpp](../../../../../src/ir/model.cpp), [src/catalog/catalog.cpp](../../../../../src/catalog/catalog.cpp), [docs/catalog.md §Validation and canonical writing](../../../../catalog.md) |

## B0027

[Lines 352–353](../../../../../src/io/document.cpp#L352); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L352-L353:sha256:f265feb1a3ec57cb69ebf33eecb25448b92f63b50e75faa6300f69752a138b94
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Design note for adjacent code: Report formatting trusts the supplied aggregate; it does not rerun the verifier. This is caller guidance recorded as prose, not an executable result. |
| inputs / outputs | No runtime interface is implemented by these comment-only lines. They sit at src/io/document.cpp lines 350-355; the surrounding declaration/body defines its own inputs and outputs. |
| invariants | The words record the intended use boundary only. They do not add a guard, proof, capability, transaction, durability guarantee, or account charge; verify behavior in the referenced implementation. |
| ownership | Comment text owns no data. Object lifetimes, borrows, and account attribution remain those of the adjacent source objects and their constructors. |
| failure | No failure path is implemented here. Any mentioned failure or recovery rule belongs to the adjacent operation and its existing error carrier. |
| cost | No runtime work is performed by these lines; any cost/bound in the note is not certified by this comment-only card. |
| Design | [src/io/document.cpp](../../../../../src/io/document.cpp), [docs/code_specs/files/src/io/document.cpp.md](document.cpp.md), [docs/semantics.md](../../../../semantics.md), [docs/tree_plans.md](../../../../tree_plans.md), [docs/planner_proofs.md](../../../../planner_proofs.md) |

## B0028

[Lines 354–379](../../../../../src/io/document.cpp#L354); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Json write_validation(const planner::ValidationReport& report, const FreeConnexTree& tree, const Query& query)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Format a supplied independent-validator report without rerunning validation. |
| inputs / outputs | Exports report.valid, optional native height/edge depth, supplied maximal connex/separators and violations; references use names or #node/#variable/#occurrence diagnostic fallbacks. |
| invariants | height_status valid_upper_bound follows the supplied report flag. Mutable ValidationReport is not authenticated here and supplies no minimum/cost/durability authority. |
| ownership | Borrows immutable caller values synchronously; returns owning ordinary JSON/native DTO data and changes no native producer, source or durable state. |
| failure | Validation/encoding Error, JSON/library and allocation failures propagate; private ordinary strings/vectors/DOMs unwind. No partial public result or producer progress is published. |
| cost | O(report connex/separator/violation entries and copied strings), fallback to_string/name copies and ordinary nested DOM; no graph traversal beyond referenced names. |
| Design | [include/crown/io/tree.hpp](../../../../../include/crown/io/tree.hpp), [docs/tree_plans.md §Plan document](../../../../tree_plans.md), [docs/tree_plans.md §What is checked](../../../../tree_plans.md), [include/crown/planner/verify.hpp](../../../../../include/crown/planner/verify.hpp), [src/io/json.hpp](../../../../../src/io/json.hpp), [third_party/nlohmann/json.hpp](../../../../../third_party/nlohmann/json.hpp) |

## B0029

[Lines 380–382](../../../../../src/io/document.cpp#L380); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L380-L382:sha256:7c68bc0475f2c9f8e2c573f7c18684d9f24a2d3a690f000612d05ecac83ba063
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Reopens a private document-codec namespace and imports query_binding for the later oracle/certificate JSON serialization and replay helpers. |
| inputs / outputs | No runtime inputs/outputs are declared by the import/scope lines themselves. |
| invariants | The listed headers and namespace membership determine compile-time name availability; any API behavior belongs to the declarations/definitions that follow. |
| ownership | No object ownership is created by the imports or namespace tokens. |
| failure | No runtime failure path. Missing/incompatible dependencies or a violated compile-time constraint fail translation/linking. |
| cost | Compile/preprocessor work only; no new per-operation runtime overhead. |
| Design | [src/io/document.cpp](../../../../../src/io/document.cpp), [docs/code_specs/files/src/io/document.cpp.md](document.cpp.md), [docs/semantics.md](../../../../semantics.md), [docs/tree_plans.md](../../../../tree_plans.md), [docs/planner_proofs.md](../../../../planner_proofs.md) |

## B0030

[Lines 383–387](../../../../../src/io/document.cpp#L383); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::size_t index_value(const Json& value, const std::string& path)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Decode one host-representable certificate index/height. |
| inputs / outputs | Uses strict unsigned_integer then rejects values above platform SIZE_MAX before casting. |
| invariants | No float/Boolean/negative coercion or validation against a particular atom/node count; index domain and claim truth belong to containing parse/replay. |
| ownership | Returns copied size_t; no input borrow escapes. |
| failure | Validation/encoding Error, JSON/library and allocation failures propagate; private ordinary strings/vectors/DOMs unwind. No partial public result or producer progress is published. |
| cost | Fixed numeric checks and copy; error/path strings can allocate. |
| Design | [include/crown/io/oracle.hpp](../../../../../include/crown/io/oracle.hpp), [include/crown/planner/oracle.hpp](../../../../../include/crown/planner/oracle.hpp), [docs/tree_oracle.md §Height certificate](../../../../tree_oracle.md), [src/io/json.hpp](../../../../../src/io/json.hpp), [third_party/nlohmann/json.hpp](../../../../../third_party/nlohmann/json.hpp) |

## B0031

[Lines 388–390](../../../../../src/io/document.cpp#L388); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L388-L390:sha256:e02b25a94fcd17f6fea12e131ff0b7b135a6d1326d77b41e9f0b303723e112e3
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Closes the anonymous namespace at this source boundary; this is a lexical delimiter, not an operation. Trailing source note states: Legacy flag gate: this serializer does not independently replay the proof. It remains prose guidance, not a certified executable claim. |
| inputs / outputs | No runtime input or output. Declarations following the span leave the preceding C++ scope. |
| invariants | The delimiter ends the preceding scope's visibility/linkage region; it adds no validation, publication, ownership transfer, or runtime authority. Any trailing comment in this block is guidance only and adds no runtime invariant. |
| ownership | The delimiter adds no owner. If it ends a function/block with live automatic objects, their normal destructors release those objects; namespace and type-definition closes change no existing object's lifetime. |
| failure | No explicit failure translation or catch is added. If a function/block exit destroys automatic objects, exception behavior follows those destructors; namespace/type closes have no runtime failure path. |
| cost | The delimiter adds no algorithmic work. A function/block exit can run existing automatic-object destructors and cleanup; namespace/type closes have no runtime cost. |
| Design | [src/io/document.cpp](../../../../../src/io/document.cpp), [docs/code_specs/files/src/io/document.cpp.md](document.cpp.md), [docs/semantics.md](../../../../semantics.md), [docs/tree_plans.md](../../../../tree_plans.md), [docs/planner_proofs.md](../../../../planner_proofs.md) |

## B0032

[Lines 391–429](../../../../../src/io/document.cpp#L391); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Json write_oracle(const planner::OracleResult& result, const Catalog& catalog, const Query& query)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Export the legacy exact-oracle result envelope and optional certificate DTO. |
| inputs / outputs | Non-resource result requires certificate_verified and known v1/v2 algorithm, then emits versioned certificate with query binding/tree/lower bounds; outer result includes supplied status/height/stats/limits/reason and fixed no-cost/no-runtime claims. |
| invariants | Compatibility adapter trusts an editable OracleResult flag; it performs no replay and cannot mint typed proof handles. tree_valid means supplied tree present, not verifier result. Resource-limit route emits null certificate but does not sanitize arbitrary caller-supplied partial tree/height fields; trusted minimum_tree normally supplies none. |
| ownership | Borrows mutable compatibility aggregate only for this call; returns ordinary deep-owned envelope/certificate/binding/tree values. |
| failure | Error(invalid_search_certificate) for missing non-resource flag/unsupported non-resource algorithm; tree/document validation, JSON and allocation errors propagate. No result or authority is published on failure. |
| cost | Whole tree/lower-bound/occurrence/stats serialization and full query_binding Document copy/validation/DOM. Certificate and outer envelope each retain tree DOM copies; nested initializers may add temporary copies. No output/work cap, no runtime/native scan. |
| Design | [include/crown/io/oracle.hpp](../../../../../include/crown/io/oracle.hpp), [include/crown/planner/oracle.hpp](../../../../../include/crown/planner/oracle.hpp), [docs/tree_oracle.md §Height certificate](../../../../tree_oracle.md), [docs/planner_proofs.md §Independent lower-bound evidence and strict limits](../../../../planner_proofs.md), [docs/planner_continuations.md §Authority and policies](../../../../planner_continuations.md), [src/io/json.hpp](../../../../../src/io/json.hpp), [third_party/nlohmann/json.hpp](../../../../../third_party/nlohmann/json.hpp), [src/io/query_binding.hpp](../../../../../src/io/query_binding.hpp), [src/planner/search_session.cpp](../../../../../src/planner/search_session.cpp) |

## B0033

[Lines 430–431](../../../../../src/io/document.cpp#L430); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L430-L431:sha256:f7bc911c7811031b73b19e29d6eaf02a9146d81d9409fe99aa58ead3d77121b0
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Design note for adjacent code: Binding/type checks produce an unverified claim; whole independent replay is separate. This is caller guidance recorded as prose, not an executable result. |
| inputs / outputs | No runtime interface is implemented by these comment-only lines. They sit at src/io/document.cpp lines 428-433; the surrounding declaration/body defines its own inputs and outputs. |
| invariants | The words record the intended use boundary only. They do not add a guard, proof, capability, transaction, durability guarantee, or account charge; verify behavior in the referenced implementation. |
| ownership | Comment text owns no data. Object lifetimes, borrows, and account attribution remain those of the adjacent source objects and their constructors. |
| failure | No failure path is implemented here. Any mentioned failure or recovery rule belongs to the adjacent operation and its existing error carrier. |
| cost | No runtime work is performed by these lines; any cost/bound in the note is not certified by this comment-only card. |
| Design | [src/io/document.cpp](../../../../../src/io/document.cpp), [docs/code_specs/files/src/io/document.cpp.md](document.cpp.md), [docs/semantics.md](../../../../semantics.md), [docs/tree_plans.md](../../../../tree_plans.md), [docs/planner_proofs.md](../../../../planner_proofs.md) |

## B0034

[Lines 432–459](../../../../../src/io/document.cpp#L432); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
planner::HeightCertificate read_height_certificate(std::string_view text, const Catalog& catalog, const Query& query)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Parse a versioned bound certificate claim while leaving proof verification separate. |
| inputs / outputs | Strict root fields accept formats1/2 with algorithm/version compatibility; dumps binding, validates it as Document, compares exact canonical dump to generated Catalog/Query binding, then parses optional height/tree and lower-bound state DTOs. |
| invariants | Canonical text preserves bool/int/float distinctions. Format1 deliberately accepts unknown algorithms except the v2-name mismatch; independent replay rejects unsupported claims. Integer ranges/Boolean flags parse, but occurrence order/uniqueness/domain and lower-bound/root/upper correctness require replay. No checked handle or minimum is created. |
| ownership | Returned HeightCertificate deep-owns algorithm/tree/claim vectors. Temporary canonical strings/DOMs/models release after call; no caller text or Catalog/Query borrow survives. |
| failure | Error on unsupported format/version-algorithm mismatch, binding inequality or malformed fields; nested document/tree/scalar/JSON/allocation errors propagate. Parsing success is not a verification result. |
| cost | Full input DOM plus binding dump, nested read_document DOM/model, generated query_binding model copy/DOM/dump and exact string compare; optional tree dump/reparse plus owning claim vectors. No certificate-entry/byte/work/account cap beyond shared nesting. |
| Design | [include/crown/io/oracle.hpp](../../../../../include/crown/io/oracle.hpp), [include/crown/planner/oracle.hpp](../../../../../include/crown/planner/oracle.hpp), [docs/tree_oracle.md §Height certificate](../../../../tree_oracle.md), [docs/planner_proofs.md §Independent lower-bound evidence and strict limits](../../../../planner_proofs.md), [docs/planner_continuations.md §Authority and policies](../../../../planner_continuations.md), [src/io/json.hpp](../../../../../src/io/json.hpp), [third_party/nlohmann/json.hpp](../../../../../third_party/nlohmann/json.hpp), [src/io/query_binding.hpp](../../../../../src/io/query_binding.hpp), [tests/unit/planner_certificate_codec_test.cpp](../../../../../tests/unit/planner_certificate_codec_test.cpp) |

## B0036

[Lines 461–464](../../../../../src/io/document.cpp#L461); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Json write_certificate_report(const planner::CertificateReport& report)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Export a certificate-check report DTO as diagnostic JSON. |
| inputs / outputs | Writes supplied valid/resource_limit/message/work values with outer schema_version1. |
| invariants | Does not rerun checker, reconcile inconsistent caller flags or manufacture CheckedCertificate/VerifiedOptimum. The report is a summary of a trusted checker when actually produced by one. |
| ownership | Borrows immutable caller values synchronously; returns owning ordinary JSON/native DTO data and changes no native producer, source or durable state. |
| failure | Validation/encoding Error, JSON/library and allocation failures propagate; private ordinary strings/vectors/DOMs unwind. No partial public result or producer progress is published. |
| cost | Fixed fields plus owning message string/DOM allocation and copy; no proof/tree scan. |
| Design | [include/crown/io/oracle.hpp](../../../../../include/crown/io/oracle.hpp), [include/crown/planner/oracle.hpp](../../../../../include/crown/planner/oracle.hpp), [docs/tree_oracle.md §Height certificate](../../../../tree_oracle.md), [docs/planner_proofs.md §Independent lower-bound evidence and strict limits](../../../../planner_proofs.md), [docs/planner_continuations.md §Authority and policies](../../../../planner_continuations.md), [src/io/json.hpp](../../../../../src/io/json.hpp), [third_party/nlohmann/json.hpp](../../../../../third_party/nlohmann/json.hpp) |

## B0037

[Lines 465–465](../../../../../src/io/document.cpp#L465); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L465-L465:sha256:a992a30ac7c9748c33994a213cb5eed12f62a6204d01f8b49f69db451a145039
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Closes the namespace crown::io at this source boundary; this is a lexical delimiter, not an operation. |
| inputs / outputs | No runtime input or output. Declarations following the span leave the preceding C++ scope. |
| invariants | The delimiter ends the preceding scope's visibility/linkage region; it adds no validation, publication, ownership transfer, or runtime authority. |
| ownership | The delimiter adds no owner. If it ends a function/block with live automatic objects, their normal destructors release those objects; namespace and type-definition closes change no existing object's lifetime. |
| failure | No explicit failure translation or catch is added. If a function/block exit destroys automatic objects, exception behavior follows those destructors; namespace/type closes have no runtime failure path. |
| cost | The delimiter adds no algorithmic work. A function/block exit can run existing automatic-object destructors and cleanup; namespace/type closes have no runtime cost. |
| Design | [src/io/document.cpp](../../../../../src/io/document.cpp), [docs/code_specs/files/src/io/document.cpp.md](document.cpp.md), [docs/semantics.md](../../../../semantics.md), [docs/tree_plans.md](../../../../tree_plans.md), [docs/planner_proofs.md](../../../../planner_proofs.md) |
