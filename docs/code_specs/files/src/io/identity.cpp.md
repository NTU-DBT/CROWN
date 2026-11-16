# `src/io/identity.cpp` — block usage map

[Source](../../../../../src/io/identity.cpp) · [Source index](../../../README.md) · [Subsystem contracts](../../../subsystem_contracts.md) · [Reviewed primitives](../../../primitives.md)

Admit bounded external documents/records and serialize explicit public representations at the engine boundary.

Snapshot SHA-256: `76f741ea6dc2efb6d0ccec2ce3cb33f6d914fad31d1f945c507dd45a4c366a8c`. 248 lines partitioned into 20 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [io](../../../subsystem_contracts.md#io). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/ingestion.md](../../../../ingestion.md), [docs/query_identity.md](../../../../query_identity.md), [docs/schema_evolution.md](../../../../schema_evolution.md), [docs/cli.md](../../../../cli.md), [docs/query_memory.md](../../../../query_memory.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–14](../../../../../src/io/identity.cpp#L1) | Imports dependencies; declares namespace scope. | source comment (unverified): // Shared abstract operation counter, not a serialized-byte or CPU/memory meter. · [reviewed contract](#b0001) |
| [B0002 · 15–23](../../../../../src/io/identity.cpp#L15) | Type/record definition: struct Work | source comment (unverified): // Shared abstract operation counter, not a serialized-byte or CPU/memory meter. · [reviewed contract](#b0002) |
| [B0003 · 24–28](../../../../../src/io/identity.cpp#L24) | Callable definition: Json type_json(const frontend::SqlType& type) | calls frontend::sql_kind_name; returns result · [reviewed contract](#b0003) |
| [B0004 · 29–29](../../../../../src/io/identity.cpp#L29) | Callable definition: Json sql_value(const frontend::SqlValue& value) | calls write_scalar, Json; returns value ? write_scalar(*value) : Json(nullptr) · [reviewed contract](#b0004) |
| [B0005 · 30–32](../../../../../src/io/identity.cpp#L30) | Callable definition: std::string digest(std::string_view domain, const Json& value) | calls sha256, dump; returns sha256(Json{{@ ,domain},{@ ,1},{@ ,value}}.dump()) · [reviewed contract](#b0005) |
| [B0006 · 33–37](../../../../../src/io/identity.cpp#L33) | Callable definition: Json semantic_catalog(const Catalog& catalog) | calls write_catalog_payload, erase; returns result; 1 loop sites · [reviewed contract](#b0006) |
| [B0007 · 38–43](../../../../../src/io/identity.cpp#L38) | Callable definition: Json sorted(Json values, Work& work) | calls charge, emplace_back, dump, std::move; returns left.first &lt; right.first; result; growth emplace_back, push_back; 2 loop sites · [reviewed contract](#b0007) |
| [B0008 · 44–44](../../../../../src/io/identity.cpp#L44) | Explanatory comments or spacing. |  |
| [B0009 · 45–60](../../../../../src/io/identity.cpp#L45) | Type/record definition: class Canonicalizer |  · [reviewed contract](#b0009) |
| [B0010 · 61–63](../../../../../src/io/identity.cpp#L61) | Explanatory comments or spacing. | source comment (unverified): // Equal-color groups may require a product of factorial permutations. Every · [reviewed contract](#b0010) |
| [B0011 · 64–138](../../../../../src/io/identity.cpp#L64) | Callable definition: QueryIdentity Canonicalizer::run(const CachePolicy& policy) | calls charge, annotations::require_set_backend_policy, empty, Error; returns colors\[left\] == colors\[right\] ? left &lt; right : colors\[left\] &lt; colors\[right\]; *id; growth emplace_back, push_back; 11 loop sites; source comment (unverified): // Equal-color groups may require a product of factorial permutations. Every · [reviewed contract](#b0011) |
| [B0012 · 139–143](../../../../../src/io/identity.cpp#L139) | Explanatory comments or spacing. | source comment (unverified): // Compile an address/ID-independent description of one adapter's expressions. · [reviewed contract](#b0012) |
| [B0013 · 144–182](../../../../../src/io/identity.cpp#L144) | Callable definition: std::vector&lt;Json&gt; local_expressions(const frontend::NormalizedSql& query, const frontend::OccurrenceAdapter& adapter, Work& work) | calls expressions, size, charge, at; returns expressions\[id.value\]; {{@ ,sql_value(query.constants.at(id.value))},{@ ,type_json(query.binding.ex…; growth push_back; 4 loop sites; source comment (unverified): // Compile an address/ID-independent description of one adapter's expressions. · [reviewed contract](#b0013) |
| [B0014 · 183–184](../../../../../src/io/identity.cpp#L183) | Closes surrounding scope/type. | source comment (unverified): // namespace · [reviewed contract](#b0014) |
| [B0015 · 185–191](../../../../../src/io/identity.cpp#L185) | Callable definition: QueryIdentity query_identity(const Catalog& catalog, const Query& query, const CachePolicy& policy, IdentityLimits limits) | calls validate, charge, Json::array, push_back; returns Canonicalizer(catalog,query,std::move(labels),{},{{@ ,@ },{@ ,@ },{@ ,policy.arithmetic}},std::move…; growth push_back; 2 loop sites · [reviewed contract](#b0015) |
| [B0016 · 192–192](../../../../../src/io/identity.cpp#L192) | Explanatory comments or spacing. |  |
| [B0017 · 193–238](../../../../../src/io/identity.cpp#L193) | Callable definition: QueryIdentity query_identity(const frontend::NormalizedSql& query, const CachePolicy& policy, IdentityLimits limits) | calls validate, charge, size, Error; returns value==frontend::SqlSemantics::set ? @ : @; Canonicalizer(query.binding.catalog,query.core,std::mov…; growth push_back; 8 loop sites · [reviewed contract](#b0017) |
| [B0018 · 239–241](../../../../../src/io/identity.cpp#L239) | Explanatory comments or spacing. | source comment (unverified): // Caller supplies a complete initialized producer DTO. These labels do not · [reviewed contract](#b0018) |
| [B0019 · 242–247](../../../../../src/io/identity.cpp#L242) | Callable definition: Json write_identity(const QueryIdentity& identity) | calls ; returns {{@ ,1},{@ ,true},{@ ,@ },{@ ,@ },; source comment (unverified): // Caller supplies a complete initialized producer DTO. These labels do not · [reviewed contract](#b0019) |
| [B0020 · 248–248](../../../../../src/io/identity.cpp#L248) | Closes surrounding scope/type. | source comment (unverified): // namespace crown::io · [reviewed contract](#b0020) |

## B0001

[Lines 1–14](../../../../../src/io/identity.cpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L1-L14:sha256:9e7faaa742a55f618851837dddd430240f9bc69e48988109874433af3ba4d565
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Imports compile-time dependencies (crown/io/identity.hpp, crown/annotations/policy.hpp, crown/api/error.hpp, crown/io/catalog.hpp, crown/ir/digest.hpp, algorithm) and opens crown::io scope for the declarations or definitions that follow. Embedded source note records intended usage: Shared abstract operation counter, not a serialized-byte or CPU/memory meter. Treat that prose as guidance, not as independently verified executable behavior. |
| inputs / outputs | No runtime inputs/outputs are declared by the import/scope lines themselves. |
| invariants | The listed headers and namespace membership determine compile-time name availability; any API behavior belongs to the declarations/definitions that follow. |
| ownership | No object ownership is created by the imports or namespace tokens. |
| failure | No runtime failure path. Missing/incompatible dependencies or a violated compile-time constraint fail translation/linking. |
| cost | Compile/preprocessor work only; no new per-operation runtime overhead. |
| Design | [src/io/identity.cpp](../../../../../src/io/identity.cpp), [docs/code_specs/files/src/io/identity.cpp.md](identity.cpp.md), [docs/query_identity.md](../../../../query_identity.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0002

[Lines 15–23](../../../../../src/io/identity.cpp#L15); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct Work {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Share one checked operational identity counter across the entire canonicalization. |
| inputs / outputs | Work owns IdentityLimits and used=0; charge rejects uint64 wrap or reaching a present ceiling before incrementing. |
| invariants | Zero rejects the first charge, nullopt means no configured work ceiling, and no nested expression/permutation resets its balance. Failure returns no partial identity. |
| ownership | Two inline limit/counter values; callers and Canonicalizer borrow this same local Work. |
| failure | Exhaustion/overflow throws public resource_limit; no retry, saturation or best-so-far digest is returned. |
| cost | Fixed comparisons/increment per charge; abstract events do not meter every JSON byte, deep copy, string comparison, allocation or SHA pass. |
| Design | [src/io/identity.cpp](../../../../../src/io/identity.cpp), [include/crown/io/identity.hpp](../../../../../include/crown/io/identity.hpp), [src/ir/digest.cpp](../../../../../src/ir/digest.cpp), [src/io/catalog.cpp](../../../../../src/io/catalog.cpp), [src/io/normalization.cpp](../../../../../src/io/normalization.cpp), [docs/query_identity.md](../../../../query_identity.md), [docs/schema_evolution.md](../../../../schema_evolution.md), [docs/code_review.md](../../../../code_review.md) |

```text
  void charge() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Reject identity work exhaustion before counter mutation. |
| inputs / outputs | Checks uint64 maximum and present operational ceiling, then increments used exactly once. |
| invariants | It is the same counter used by expressions, sorting and permutations, not a separately reset phase allowance. |
| ownership | Mutates only the local shared Work scalar. |
| failure | Public resource_limit on exhaustion/overflow; already consumed events are not reported as a valid partial result. |
| cost | Fixed branch/increment; diagnostic construction may allocate only on failure. |
| Design | [src/io/identity.cpp](../../../../../src/io/identity.cpp), [include/crown/io/identity.hpp](../../../../../include/crown/io/identity.hpp), [src/ir/digest.cpp](../../../../../src/ir/digest.cpp), [src/io/catalog.cpp](../../../../../src/io/catalog.cpp), [src/io/normalization.cpp](../../../../../src/io/normalization.cpp), [docs/query_identity.md](../../../../query_identity.md), [docs/schema_evolution.md](../../../../schema_evolution.md), [docs/code_review.md](../../../../code_review.md) |

## B0003

[Lines 24–28](../../../../../src/io/identity.cpp#L24); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Json type_json(const frontend::SqlType& type) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Describe SQL type semantics inside canonical labels. |
| inputs / outputs | Returns kind/nullable plus optional decimal precision/scale JSON. |
| invariants | This helper assumes producer-validated SqlType; it does not prove arbitrary edited types valid. |
| ownership | The returned ordinary owning JSON tree copies its exposed strings/arrays/objects; it retains no live runtime, grant or typed proof capability. |
| failure | Shape/type/version, parser/serialization or ordinary allocation failures propagate; this boundary adds no catch, fallback or retry. |
| cost | Small DOM/string copies; no expression evaluation or row conversion. |
| Design | [src/io/identity.cpp](../../../../../src/io/identity.cpp), [include/crown/io/identity.hpp](../../../../../include/crown/io/identity.hpp), [src/ir/digest.cpp](../../../../../src/ir/digest.cpp), [src/io/catalog.cpp](../../../../../src/io/catalog.cpp), [src/io/normalization.cpp](../../../../../src/io/normalization.cpp), [docs/query_identity.md](../../../../query_identity.md), [docs/schema_evolution.md](../../../../schema_evolution.md), [docs/code_review.md](../../../../code_review.md) |

## B0004

[Lines 29–29](../../../../../src/io/identity.cpp#L29); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Json sql_value(const frontend::SqlValue& value) { return value ? write_scalar(*value) : Json(nullptr); }
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Preserve SQL NULL separately from exact typed scalar constants. |
| inputs / outputs | SqlValue absent becomes JSON null; present Value is emitted through write_scalar canonical date/decimal/value encoding. |
| invariants | NULL remains a SQL-boundary concept and is not invented as a crown::Value tag. |
| ownership | The returned ordinary owning JSON tree copies its exposed strings/arrays/objects; it retains no live runtime, grant or typed proof capability. |
| failure | Shape/type/version, parser/serialization or ordinary allocation failures propagate; this boundary adds no catch, fallback or retry. |
| cost | Scalar/date/decimal/string formatting and ordinary owned JSON allocation according to value size. |
| Design | [src/io/identity.cpp](../../../../../src/io/identity.cpp), [include/crown/io/identity.hpp](../../../../../include/crown/io/identity.hpp), [src/ir/digest.cpp](../../../../../src/ir/digest.cpp), [src/io/catalog.cpp](../../../../../src/io/catalog.cpp), [src/io/normalization.cpp](../../../../../src/io/normalization.cpp), [docs/query_identity.md](../../../../query_identity.md), [docs/schema_evolution.md](../../../../schema_evolution.md), [docs/code_review.md](../../../../code_review.md) |

## B0005

[Lines 30–32](../../../../../src/io/identity.cpp#L30); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::string digest(std::string_view domain, const Json& value) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Hash a versioned domain-separated complete JSON payload. |
| inputs / outputs | Creates {domain,version:1,value}, dumps compact sorted-object JSON and computes the independent SHA-256 helper result. |
| invariants | Digest construction is representation-versioned, not a typed certificate, authentication token or input/program admission. |
| ownership | Returns ordinary owned digest text; temporary envelope copies payload and serialized bytes. |
| failure | Invalid JSON serialization, SHA length-domain or allocation failure propagates; no truncated or fallback digest. |
| cost | Copies/serializes actual payload bytes and hashes them linearly. SHA core uses fixed stack blocks, but this helper's DOM/dump/64-byte std::string result are ordinary allocating boundaries. |
| Design | [src/io/identity.cpp](../../../../../src/io/identity.cpp), [include/crown/io/identity.hpp](../../../../../include/crown/io/identity.hpp), [src/ir/digest.cpp](../../../../../src/ir/digest.cpp), [src/io/catalog.cpp](../../../../../src/io/catalog.cpp), [src/io/normalization.cpp](../../../../../src/io/normalization.cpp), [docs/query_identity.md](../../../../query_identity.md), [docs/schema_evolution.md](../../../../schema_evolution.md), [docs/code_review.md](../../../../code_review.md) |

## B0006

[Lines 33–37](../../../../../src/io/identity.cpp#L33); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Json semantic_catalog(const Catalog& catalog) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Separate semantic schema metadata from cost-only catalog inputs. |
| inputs / outputs | Serializes/validates the complete Catalog, then erases statistics and key_hints from each table in the local JSON copy. |
| invariants | Table/column order/names, constraints/status, types/nullability and schema versions remain semantic identity. Later cost_inputs digest includes the full original catalog. |
| ownership | The returned ordinary owning JSON tree copies its exposed strings/arrays/objects; it retains no live runtime, grant or typed proof capability. |
| failure | Shape/type/version, parser/serialization or ordinary allocation failures propagate; this boundary adds no catch, fallback or retry. |
| cost | Full catalog validation/export (including initially copied stats/hints), then per-table erasures/destruction. It is not a free filtered view. |
| Design | [src/io/identity.cpp](../../../../../src/io/identity.cpp), [include/crown/io/identity.hpp](../../../../../include/crown/io/identity.hpp), [src/ir/digest.cpp](../../../../../src/ir/digest.cpp), [src/io/catalog.cpp](../../../../../src/io/catalog.cpp), [src/io/normalization.cpp](../../../../../src/io/normalization.cpp), [docs/query_identity.md](../../../../query_identity.md), [docs/schema_evolution.md](../../../../schema_evolution.md), [docs/code_review.md](../../../../code_review.md) |

## B0007

[Lines 38–43](../../../../../src/io/identity.cpp#L38); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Json sorted(Json values, Work& work) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Sort local semantic operands by their complete serialized representations. |
| inputs / outputs | Adopts values by value, charges each entry/comparison, materializes one dump key per JSON value, sorts key/value pairs and moves values into a new array. |
| invariants | Sort key is exact versioned JSON bytes; equal keys encode identical payload, independent of original expression ID. Throws discard private partial sort, not source state. |
| ownership | Owns input JSON, keyed strings and output array; no persistent/shared expression cache is created. |
| failure | Work exhaustion in sort comparator, serialization or allocation failure propagates without a partial canonical result. |
| cost | O(n log n) comparisons with actual key-byte comparison lengths, plus complete subtree dumps/copies and ordinary container growth. Work counts comparisons/entries, not their total bytes. |
| Design | [src/io/identity.cpp](../../../../../src/io/identity.cpp), [include/crown/io/identity.hpp](../../../../../include/crown/io/identity.hpp), [src/ir/digest.cpp](../../../../../src/ir/digest.cpp), [src/io/catalog.cpp](../../../../../src/io/catalog.cpp), [src/io/normalization.cpp](../../../../../src/io/normalization.cpp), [docs/query_identity.md](../../../../query_identity.md), [docs/schema_evolution.md](../../../../schema_evolution.md), [docs/code_review.md](../../../../code_review.md) |

## B0009

[Lines 45–60](../../../../../src/io/identity.cpp#L45); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
class Canonicalizer {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Own canonicalization scratch while borrowing validated source and one work counter. |
| inputs / outputs | Constructor borrows Catalog/Query/Work and adopts labels, column classes, semantics and ordered output-contract JSON. |
| invariants | Source/query/work must remain alive and stable throughout synchronous run. It neither validates arbitrary normalized adapters nor owns a runtime or persistent plan cache. |
| ownership | References borrow source/query/work; vectors/JSON members own ordinary scratch and can deep-copy payload when new candidates are built. |
| failure | By-value argument construction may allocate before entry; run propagates validation/work/allocation failures with local RAII cleanup. |
| cost | Constructor body moves scratch handles plus references. Full payload construction/copies and factorial labeling remain explicit run/caller costs. |
| Design | [src/io/identity.cpp](../../../../../src/io/identity.cpp), [include/crown/io/identity.hpp](../../../../../include/crown/io/identity.hpp), [src/ir/digest.cpp](../../../../../src/ir/digest.cpp), [src/io/catalog.cpp](../../../../../src/io/catalog.cpp), [src/io/normalization.cpp](../../../../../src/io/normalization.cpp), [docs/query_identity.md](../../../../query_identity.md), [docs/schema_evolution.md](../../../../schema_evolution.md), [docs/code_review.md](../../../../code_review.md) |

```text
  const Catalog& source_;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Borrow stable source/query metadata while owning canonical scratch. |
| inputs / outputs | source_ and query_ refer to caller-validated metadata; work_ refers to the caller's one Work. labels_/classes_/semantics_/output_ own their moved vectors/JSON. |
| invariants | Synchronous run must finish before borrowed arguments expire or mutate; returned identity contains owned copies, not these references. |
| ownership | Borrowed references add no owner; scratch JSON/vector members own ordinary storage. |
| failure | No validation/exception translation is performed by the fields themselves. |
| cost | Fixed reference/handle storage; subsequent candidate construction pays full owned payload copies. |
| Design | [src/io/identity.cpp](../../../../../src/io/identity.cpp), [include/crown/io/identity.hpp](../../../../../include/crown/io/identity.hpp), [src/ir/digest.cpp](../../../../../src/ir/digest.cpp), [src/io/catalog.cpp](../../../../../src/io/catalog.cpp), [src/io/normalization.cpp](../../../../../src/io/normalization.cpp), [docs/query_identity.md](../../../../query_identity.md), [docs/schema_evolution.md](../../../../schema_evolution.md), [docs/code_review.md](../../../../code_review.md) |

## B0010

[Lines 61–63](../../../../../src/io/identity.cpp#L61); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L61-L63:sha256:04fcfe2b3fab4f5b7d1db7c2477f82c094c25b14c9f87fdbe221de80960dc0af
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Design note for adjacent code: Equal-color groups may require a product of factorial permutations. Every complete candidate owns/copies serialized metadata; no best-so-far hash escapes. This is caller guidance recorded as prose, not an executable result. |
| inputs / outputs | No runtime interface is implemented by these comment-only lines. They sit at src/io/identity.cpp lines 59-65; the surrounding declaration/body defines its own inputs and outputs. |
| invariants | The words record the intended use boundary only. They do not add a guard, proof, capability, transaction, durability guarantee, or account charge; verify behavior in the referenced implementation. |
| ownership | Comment text owns no data. Object lifetimes, borrows, and account attribution remain those of the adjacent source objects and their constructors. |
| failure | No failure path is implemented here. Any mentioned failure or recovery rule belongs to the adjacent operation and its existing error carrier. |
| cost | No runtime work is performed by these lines; any cost/bound in the note is not certified by this comment-only card. |
| Design | [src/io/identity.cpp](../../../../../src/io/identity.cpp), [docs/code_specs/files/src/io/identity.cpp.md](identity.cpp.md), [docs/query_identity.md](../../../../query_identity.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0011

[Lines 64–138](../../../../../src/io/identity.cpp#L64); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
QueryIdentity Canonicalizer::run(const CachePolicy& policy) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Compute the least complete colored-occurrence labeling before emitting all four identities. |
| inputs / outputs | Checks arithmetic/nonempty version policy; builds invariant atom colors, sorts/group equal colors, enumerates all within-group permutations, relabels variables by first use, chooses least full JSON and hashes semantic/output/cost/cache domains. |
| invariants | Preserves every source atom, typed constant, ordered/repeated head position, source schema and contradiction. Only complete search returns canonical output; no minimum-height, algebraic SQL equivalence, data-row or runtime authority is proved. |
| ownership | Owns all candidate/best JSON/string/permutation vectors locally; returned QueryIdentity owns canonical JSON, maps and digest strings independently of borrowed source. |
| failure | Invalid policy, work exhaustion, malformed producer references or allocation/serialization failure discards private partial state. No best-so-far/fallback digest escapes. |
| cost | Product of factorial equal-color group permutations in worst case. Each builds/copies/dumps full candidate, catalog and semantics and compares text, followed by full catalog/digest serialization. Abstract work is not total CPU/bytes or a memory cap. |
| Design | [src/io/identity.cpp](../../../../../src/io/identity.cpp), [include/crown/io/identity.hpp](../../../../../include/crown/io/identity.hpp), [src/ir/digest.cpp](../../../../../src/ir/digest.cpp), [src/io/catalog.cpp](../../../../../src/io/catalog.cpp), [src/io/normalization.cpp](../../../../../src/io/normalization.cpp), [docs/query_identity.md](../../../../query_identity.md), [docs/schema_evolution.md](../../../../schema_evolution.md), [docs/code_review.md](../../../../code_review.md) |

```text
  std::vector<std::string> colors;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Partition occurrence permutations by complete invariant typed atom color. |
| inputs / outputs | Adds typed term-shapes to owned atom labels, dumps each color, sorts occurrence indices by color then original index, and groups equal color strings. |
| invariants | Color order is invariant for the supported equivalence profile; physical source IDs/catalog layout remain fixed. Equal-color permutations are still exhaustively visited. |
| ownership | Owns color strings/order/group vectors; source terms remain borrowed. |
| failure | Work limit, invalid producer term IDs, serialization or allocation failure discards scratch. |
| cost | Term/color serialization and O(atoms log atoms) comparisons of actual color bytes, plus group scans. Label dumps and string comparison bytes are not individually counted work units. |
| Design | [src/io/identity.cpp](../../../../../src/io/identity.cpp), [include/crown/io/identity.hpp](../../../../../include/crown/io/identity.hpp), [src/ir/digest.cpp](../../../../../src/ir/digest.cpp), [src/io/catalog.cpp](../../../../../src/io/catalog.cpp), [src/io/normalization.cpp](../../../../../src/io/normalization.cpp), [docs/query_identity.md](../../../../query_identity.md), [docs/schema_evolution.md](../../../../schema_evolution.md), [docs/code_review.md](../../../../code_review.md) |

```text
    const auto variable_id=[&](VariableId variable) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Relabel variables by first encounter in one candidate ordering. |
| inputs / outputs | Charges access, assigns next canonical index once, records original-ID inverse order and type, and returns the candidate-local ID. |
| invariants | Per-candidate map is reset for the next occurrence permutation; the operational Work is not reset. Original query/head/physical-class references use the same mapping. |
| ownership | Captures local vectors/type JSON by reference only for the enclosing candidate construction. |
| failure | Invalid ID, work exhaustion or vector/JSON allocation failure propagates; no partially labeled result escapes. |
| cost | Fixed indexed optional lookup plus first-use vector/type output growth; no variable-name string lookup or persistent registry. |
| Design | [src/io/identity.cpp](../../../../../src/io/identity.cpp), [include/crown/io/identity.hpp](../../../../../include/crown/io/identity.hpp), [src/ir/digest.cpp](../../../../../src/ir/digest.cpp), [src/io/catalog.cpp](../../../../../src/io/catalog.cpp), [src/io/normalization.cpp](../../../../../src/io/normalization.cpp), [docs/query_identity.md](../../../../query_identity.md), [docs/schema_evolution.md](../../../../schema_evolution.md), [docs/code_review.md](../../../../code_review.md) |

```text
  best.semantic_sha256=digest("crown.query.semantic",best.canonical);
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Separate semantic, output, cost-input and full plan-cache invalidation domains. |
| inputs / outputs | Hashes canonical semantics, ordered output names/types, full source catalog including statistics/hints, then those hashes plus arithmetic/planner/optimization/cost version strings. |
| invariants | Statistics/hints are absent from semantic_catalog but present in cost_inputs and plan-cache identity. Version strings are nonempty labels, not executable policy implementations. |
| ownership | Owns four digest strings and temporary envelope/full-catalog JSON. |
| failure | Serialization/SHA-domain/allocation failure returns no identity even after complete labeling. |
| cost | Four complete domain-envelope dumps/hashes plus another full catalog validation/export. Final digest/DTO byte work is not separately charged by Work::charge. |
| Design | [src/io/identity.cpp](../../../../../src/io/identity.cpp), [include/crown/io/identity.hpp](../../../../../include/crown/io/identity.hpp), [src/ir/digest.cpp](../../../../../src/ir/digest.cpp), [src/io/catalog.cpp](../../../../../src/io/catalog.cpp), [src/io/normalization.cpp](../../../../../src/io/normalization.cpp), [docs/query_identity.md](../../../../query_identity.md), [docs/schema_evolution.md](../../../../schema_evolution.md), [docs/code_review.md](../../../../code_review.md) |

## B0012

[Lines 139–143](../../../../../src/io/identity.cpp#L139); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L139-L143:sha256:04ec0d54a5608bfb3b0f57206735f2a80f389f8996ea13e795499f3788d88e43
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Design note for adjacent code: Compile an address/ID-independent description of one adapter's expressions. Producer-validated inner USING is the left value plus a separate equality. Ordinary JSON operands copy subtrees; slot capacity spans the full binding expression count for each adapter. This is a cold compiler boundary. This is caller guidance recorded as prose, not an executable result. |
| inputs / outputs | No runtime interface is implemented by these comment-only lines. They sit at src/io/identity.cpp lines 137-145; the surrounding declaration/body defines its own inputs and outputs. |
| invariants | The words record the intended use boundary only. They do not add a guard, proof, capability, transaction, durability guarantee, or account charge; verify behavior in the referenced implementation. |
| ownership | Comment text owns no data. Object lifetimes, borrows, and account attribution remain those of the adjacent source objects and their constructors. |
| failure | No failure path is implemented here. Any mentioned failure or recovery rule belongs to the adjacent operation and its existing error carrier. |
| cost | No runtime work is performed by these lines; any cost/bound in the note is not certified by this comment-only card. |
| Design | [src/io/identity.cpp](../../../../../src/io/identity.cpp), [docs/code_specs/files/src/io/identity.cpp.md](identity.cpp.md), [docs/query_identity.md](../../../../query_identity.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0013

[Lines 144–182](../../../../../src/io/identity.cpp#L144); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::vector<Json> local_expressions(const frontend::NormalizedSql& query, const frontend::OccurrenceAdapter& adapter, Work& work) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Remove parser IDs from one validated local expression adapter. |
| inputs / outputs | Allocates a full binding-expression slot vector for this adapter; resolves local columns/typed constants and operations, erases checked identity/literal/widening/USING casts, reverses greater comparisons and sorts/flattens supported commutative forms. |
| invariants | Requires producer/reader-validated NormalizedSql/adapters; foreign columns reject. Inner USING's left-value rewrite relies on a separate producer-validated equality. It does not prove equivalence of arbitrary edited expression graphs. |
| ownership | Returned ordinary JSON slots own serialized subtrees; operand access returns copies and can duplicate previously built subexpressions. Source bindings/constants remain borrowed. |
| failure | Foreign column, invalid IDs/operator assumptions, work exhaustion or ordinary allocation failure propagates before labeling completes. |
| cost | Full binding-expression slot capacity per adapter plus visited adapter operations, subtree copying/dumps and sorting comparisons. Deep expression expansion/string bytes can exceed the abstract operation count. |
| Design | [src/io/identity.cpp](../../../../../src/io/identity.cpp), [include/crown/io/identity.hpp](../../../../../include/crown/io/identity.hpp), [src/ir/digest.cpp](../../../../../src/ir/digest.cpp), [src/io/catalog.cpp](../../../../../src/io/catalog.cpp), [src/io/normalization.cpp](../../../../../src/io/normalization.cpp), [docs/query_identity.md](../../../../query_identity.md), [docs/schema_evolution.md](../../../../schema_evolution.md), [docs/code_review.md](../../../../code_review.md) |

## B0014

[Lines 183–184](../../../../../src/io/identity.cpp#L183); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L183-L184:sha256:c2bd7638f09d52cb034ed574f539304035fc6fab162bf8d5fa20a35d8c7288a1
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Closes the anonymous namespace at this source boundary; this is a lexical delimiter, not an operation. |
| inputs / outputs | No runtime input or output. Declarations following the span leave the preceding C++ scope. |
| invariants | The delimiter ends the preceding scope's visibility/linkage region; it adds no validation, publication, ownership transfer, or runtime authority. |
| ownership | The delimiter adds no owner. If it ends a function/block with live automatic objects, their normal destructors release those objects; namespace and type-definition closes change no existing object's lifetime. |
| failure | No explicit failure translation or catch is added. If a function/block exit destroys automatic objects, exception behavior follows those destructors; namespace/type closes have no runtime failure path. |
| cost | The delimiter adds no algorithmic work. A function/block exit can run existing automatic-object destructors and cleanup; namespace/type closes have no runtime cost. |
| Design | [src/io/identity.cpp](../../../../../src/io/identity.cpp), [docs/code_specs/files/src/io/identity.cpp.md](identity.cpp.md), [docs/query_identity.md](../../../../query_identity.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0015

[Lines 185–191](../../../../../src/io/identity.cpp#L185); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
QueryIdentity query_identity(const Catalog& catalog, const Query& query, const CachePolicy& policy, IdentityLimits limits) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Canonicalize a validated direct conjunctive query against its complete source schema. |
| inputs / outputs | Validates Catalog/Query, creates one Work, labels atoms by physical table IDs and output contract by names/types, then runs direct-cq-v1 set-semantics Canonicalizer. |
| invariants | Full source schema remains fixed; variable names/IDs and atom textual order can be relabeled, but output positions and all atoms remain. No planner classification, proof or runtime is produced. |
| ownership | Returned identity owns ordinary canonical payload/maps/digests; Catalog/Query are borrowed during synchronous work. |
| failure | Source/query validation, policy/work/resource or allocation errors propagate; no partial identity. |
| cost | Validation/schema/name/term work plus potentially factorial Canonicalizer, deep output JSON and four digest builds. No native account or data-population scan. |
| Design | [src/io/identity.cpp](../../../../../src/io/identity.cpp), [include/crown/io/identity.hpp](../../../../../include/crown/io/identity.hpp), [src/ir/digest.cpp](../../../../../src/ir/digest.cpp), [src/io/catalog.cpp](../../../../../src/io/catalog.cpp), [src/io/normalization.cpp](../../../../../src/io/normalization.cpp), [docs/query_identity.md](../../../../query_identity.md), [docs/schema_evolution.md](../../../../schema_evolution.md), [docs/code_review.md](../../../../code_review.md) |

## B0017

[Lines 193–238](../../../../../src/io/identity.cpp#L193); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
QueryIdentity query_identity(const frontend::NormalizedSql& query, const CachePolicy& policy, IdentityLimits limits) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Canonicalize producer-validated normalized SQL adapters and specialized output semantics. |
| inputs / outputs | Checks core and adapter count, builds ID-independent local filters/projections/column classes/guards, captures parameters and constant/core output positions, and invokes canonicalizer using the original source catalog. |
| invariants | Normalized binding/adapters must already be producer/reader validated; checking the core alone does not make arbitrary edits safe. SQL source/locations are excluded, but requested/inner row semantics, EXISTS, parameter values/types, outputs and source schema remain. |
| ownership | Owns temporary ordinary adapter/parameter/output JSON; result owns canonical maps/digests without retaining borrowed query. |
| failure | Invalid program/source/policy, work exhaustion, bad producer IDs or allocation/serialization failure propagates; no partial/fallback identity. |
| cost | Per-adapter full expression-slot scratch, deep expression/filter copies and sorting, parameters/output serialization, then factorial colored labeling and digests. These cold compiler costs are not per-row runtime work. |
| Design | [src/io/identity.cpp](../../../../../src/io/identity.cpp), [include/crown/io/identity.hpp](../../../../../include/crown/io/identity.hpp), [src/ir/digest.cpp](../../../../../src/ir/digest.cpp), [src/io/catalog.cpp](../../../../../src/io/catalog.cpp), [src/io/normalization.cpp](../../../../../src/io/normalization.cpp), [docs/query_identity.md](../../../../query_identity.md), [docs/schema_evolution.md](../../../../schema_evolution.md), [docs/code_review.md](../../../../code_review.md) |

## B0018

[Lines 239–241](../../../../../src/io/identity.cpp#L239); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L239-L241:sha256:98d6afccbc0be8a919a38ed5ab5df6ad8d94dc722330f6644fbdb22640a63cd2
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Design note for adjacent code: Caller supplies a complete initialized producer DTO. These labels do not recompute digests or validate fields edited after identity construction. This is caller guidance recorded as prose, not an executable result. |
| inputs / outputs | No runtime interface is implemented by these comment-only lines. They sit at src/io/identity.cpp lines 237-243; the surrounding declaration/body defines its own inputs and outputs. |
| invariants | The words record the intended use boundary only. They do not add a guard, proof, capability, transaction, durability guarantee, or account charge; verify behavior in the referenced implementation. |
| ownership | Comment text owns no data. Object lifetimes, borrows, and account attribution remain those of the adjacent source objects and their constructors. |
| failure | No failure path is implemented here. Any mentioned failure or recovery rule belongs to the adjacent operation and its existing error carrier. |
| cost | No runtime work is performed by these lines; any cost/bound in the note is not certified by this comment-only card. |
| Design | [src/io/identity.cpp](../../../../../src/io/identity.cpp), [docs/code_specs/files/src/io/identity.cpp.md](identity.cpp.md), [docs/query_identity.md](../../../../query_identity.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0019

[Lines 242–247](../../../../../src/io/identity.cpp#L242); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Json write_identity(const QueryIdentity& identity) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Serialize a complete initialized QueryIdentity DTO without revalidating its digests. |
| inputs / outputs | Copies four digest strings, canonical payload, original-ID maps and work with identity_valid=true/status=complete labels. |
| invariants | Caller supplies a fully initialized producer result; default/edited DTOs are not checked here. Labels do not authenticate hashes, replay source or mint query/plan/proof authority; consumers must validate/recompute as required. |
| ownership | The returned ordinary owning JSON tree copies its exposed strings/arrays/objects; it retains no live runtime, grant or typed proof capability. |
| failure | Shape/type/version, parser/serialization or ordinary allocation failures propagate; this boundary adds no catch, fallback or retry. |
| cost | Deep canonical JSON/map/string copies and ordinary DOM allocation. It performs no SHA recomputation or labeling search. |
| Design | [src/io/identity.cpp](../../../../../src/io/identity.cpp), [include/crown/io/identity.hpp](../../../../../include/crown/io/identity.hpp), [src/ir/digest.cpp](../../../../../src/ir/digest.cpp), [src/io/catalog.cpp](../../../../../src/io/catalog.cpp), [src/io/normalization.cpp](../../../../../src/io/normalization.cpp), [docs/query_identity.md](../../../../query_identity.md), [docs/schema_evolution.md](../../../../schema_evolution.md), [docs/code_review.md](../../../../code_review.md) |

## B0020

[Lines 248–248](../../../../../src/io/identity.cpp#L248); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L248-L248:sha256:a992a30ac7c9748c33994a213cb5eed12f62a6204d01f8b49f69db451a145039
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Closes the namespace crown::io at this source boundary; this is a lexical delimiter, not an operation. |
| inputs / outputs | No runtime input or output. Declarations following the span leave the preceding C++ scope. |
| invariants | The delimiter ends the preceding scope's visibility/linkage region; it adds no validation, publication, ownership transfer, or runtime authority. |
| ownership | The delimiter adds no owner. If it ends a function/block with live automatic objects, their normal destructors release those objects; namespace and type-definition closes change no existing object's lifetime. |
| failure | No explicit failure translation or catch is added. If a function/block exit destroys automatic objects, exception behavior follows those destructors; namespace/type closes have no runtime failure path. |
| cost | The delimiter adds no algorithmic work. A function/block exit can run existing automatic-object destructors and cleanup; namespace/type closes have no runtime cost. |
| Design | [src/io/identity.cpp](../../../../../src/io/identity.cpp), [docs/code_specs/files/src/io/identity.cpp.md](identity.cpp.md), [docs/query_identity.md](../../../../query_identity.md), [docs/query_memory.md](../../../../query_memory.md) |
