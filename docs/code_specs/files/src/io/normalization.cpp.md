# `src/io/normalization.cpp` — block usage map

[Source](../../../../../src/io/normalization.cpp) · [Source index](../../../README.md) · [Subsystem contracts](../../../subsystem_contracts.md) · [Reviewed primitives](../../../primitives.md)

Admit bounded external documents/records and serialize explicit public representations at the engine boundary.

Snapshot SHA-256: `34e6f18c143bcab0683344d0487fdac60cbe4ae622ed54d99e08cc2ab84848aa`. 109 lines partitioned into 11 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [io](../../../subsystem_contracts.md#io). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/ingestion.md](../../../../ingestion.md), [docs/query_identity.md](../../../../query_identity.md), [docs/schema_evolution.md](../../../../schema_evolution.md), [docs/cli.md](../../../../cli.md), [docs/query_memory.md](../../../../query_memory.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–7](../../../../../src/io/normalization.cpp#L1) | Imports dependencies; declares namespace scope. |  · [reviewed contract](#b0001) |
| [B0002 · 8–12](../../../../../src/io/normalization.cpp#L8) | Callable definition: Json type_json(const frontend::SqlType& type) | calls frontend::sql_kind_name; returns result · [reviewed contract](#b0002) |
| [B0003 · 13–14](../../../../../src/io/normalization.cpp#L13) | Closes surrounding scope/type. | source comment (unverified): // namespace · [reviewed contract](#b0003) |
| [B0004 · 15–60](../../../../../src/io/normalization.cpp#L15) | Callable definition: Json write_sql_normalization(const frontend::SqlNormalizeResult& result) | calls write_sql_binding, erase, resize, size; returns output; output; growth push_back, resize; 12 loop sites · [reviewed contract](#b0004) |
| [B0005 · 61–61](../../../../../src/io/normalization.cpp#L61) | Explanatory comments or spacing. |  |
| [B0006 · 62–86](../../../../../src/io/normalization.cpp#L62) | Callable definition: frontend::NormalizedSql read_sql_normalization(std::string_view text, const ProgramReadLimits& limits) | calls detail::parse_json, detail::fields, detail::unsigned_integer, at; returns normalized; source comment (unverified): // Rebuild under host caps, restore stored policy, and compare every serialized field. · [reviewed contract](#b0006) |
| [B0007 · 87–87](../../../../../src/io/normalization.cpp#L87) | Explanatory comments or spacing. |  |
| [B0008 · 88–99](../../../../../src/io/normalization.cpp#L88) | Callable definition: frontend::NormalizedSql upgrade_sql_normalization(const frontend::NormalizedSql& program, std::uint64_t target_version, const Pro… | calls Error, read_sql_normalization, write_sql_normalization, dump; returns original; upgraded · [reviewed contract](#b0008) |
| [B0009 · 100–100](../../../../../src/io/normalization.cpp#L100) | Explanatory comments or spacing. |  |
| [B0010 · 101–108](../../../../../src/io/normalization.cpp#L101) | Callable definition: std::vector&lt;frontend::SqlValue&gt; read_parameter_values(std::string_view text) | calls detail::parse_json, detail::fields, detail::version, at; returns result; growth push_back; 1 loop sites · [reviewed contract](#b0010) |
| [B0011 · 109–109](../../../../../src/io/normalization.cpp#L109) | Closes surrounding scope/type. | source comment (unverified): // namespace crown::io · [reviewed contract](#b0011) |

## B0001

[Lines 1–7](../../../../../src/io/normalization.cpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
#include "crown/io/normalization.hpp"
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Serialize normalized SQL diagnostics and rebuild executable normalization by complete binding/normalization replay. |
| inputs / outputs | Imports the declarations used by this translation unit/header; no runtime input or result. |
| invariants | Namespace/includes do not perform admission, validation, publication or IO. |
| ownership | Declarations give no ownership of caller records, source bytes or runtime accounts. |
| failure | Compile/link dependencies only; there is no executable failure boundary in these includes. |
| cost | Compile-time dependencies; later functions account for their own runtime work and storage. |
| Design | [src/io/normalization.cpp](../../../../../src/io/normalization.cpp), [include/crown/io/normalization.hpp](../../../../../include/crown/io/normalization.hpp), [include/crown/frontend/normalize.hpp](../../../../../include/crown/frontend/normalize.hpp), [src/io/binding.cpp](../../../../../src/io/binding.cpp), [src/io/document.cpp](../../../../../src/io/document.cpp), [src/io/json.hpp](../../../../../src/io/json.hpp), [docs/sql_support.md](../../../../sql_support.md), [docs/code_review.md](../../../../code_review.md) |

## B0002

[Lines 8–12](../../../../../src/io/normalization.cpp#L8); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Json type_json(const frontend::SqlType& type) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Export one SQL type descriptor. |
| inputs / outputs | SqlType in; owning kind/nullable/optional precision-scale JSON out. |
| invariants | Encoding mirrors the supplied descriptor; does not independently prove SQL binding/admission. |
| ownership | Borrows type, DOM owns labels/nested fields. |
| failure | sql_kind_name invalid-type or DOM OOM errors propagate. |
| cost | Fixed fields and ordinary object/string allocations. |
| Design | [src/io/normalization.cpp](../../../../../src/io/normalization.cpp), [include/crown/io/normalization.hpp](../../../../../include/crown/io/normalization.hpp), [include/crown/frontend/normalize.hpp](../../../../../include/crown/frontend/normalize.hpp), [src/io/binding.cpp](../../../../../src/io/binding.cpp), [src/io/document.cpp](../../../../../src/io/document.cpp), [src/io/json.hpp](../../../../../src/io/json.hpp), [docs/sql_support.md](../../../../sql_support.md), [docs/code_review.md](../../../../code_review.md) |

## B0003

[Lines 13–14](../../../../../src/io/normalization.cpp#L13); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L13-L14:sha256:c2bd7638f09d52cb034ed574f539304035fc6fab162bf8d5fa20a35d8c7288a1
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Closes the anonymous namespace at this source boundary; this is a lexical delimiter, not an operation. |
| inputs / outputs | No runtime input or output. Declarations following the span leave the preceding C++ scope. |
| invariants | The delimiter ends the preceding scope's visibility/linkage region; it adds no validation, publication, ownership transfer, or runtime authority. |
| ownership | The delimiter adds no owner. If it ends a function/block with live automatic objects, their normal destructors release those objects; namespace and type-definition closes change no existing object's lifetime. |
| failure | No explicit failure translation or catch is added. If a function/block exit destroys automatic objects, exception behavior follows those destructors; namespace/type closes have no runtime failure path. |
| cost | The delimiter adds no algorithmic work. A function/block exit can run existing automatic-object destructors and cleanup; namespace/type closes have no runtime cost. |
| Design | [src/io/normalization.cpp](../../../../../src/io/normalization.cpp), [docs/code_specs/files/src/io/normalization.cpp.md](normalization.cpp.md), [docs/sql_binding.md](../../../../sql_binding.md), [docs/sql_normalization.md](../../../../sql_normalization.md) |

## B0004

[Lines 15–60](../../../../../src/io/normalization.cpp#L15); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Json write_sql_normalization(const frontend::SqlNormalizeResult& result) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Serialize a normalization result or its binding diagnostic. |
| inputs / outputs | SqlNormalizeResult in; owning format1/2 normalized artifact or normalization_valid=false diagnostic out. |
| invariants | Success labels admission_status=not_checked. Format1 rejects constant_columns; versions outside1/2 reject. Fields are serialized reports, not a native compiled-program authority. |
| ownership | Success explicitly deep-copies core catalog/query into ordinary Document, allocates empty initial relation array and DOM for binding/parameters/adapters/routes/outputs. Input remains owned by caller. |
| failure | Diagnostic is forwarded through write_sql_binding then relabeled; invalid version/constant guard/scalar/DOM/OOM error aborts local output. |
| cost | Full graph traversal/copy, binding/core serialization plus all adapter/program/route/output entries and scalar bytes. Initial Document+DOM coexist; ordinary allocations outside update quanta. |
| Design | [src/io/normalization.cpp](../../../../../src/io/normalization.cpp), [include/crown/io/normalization.hpp](../../../../../include/crown/io/normalization.hpp), [include/crown/frontend/normalize.hpp](../../../../../include/crown/frontend/normalize.hpp), [src/io/binding.cpp](../../../../../src/io/binding.cpp), [src/io/document.cpp](../../../../../src/io/document.cpp), [src/io/json.hpp](../../../../../src/io/json.hpp), [docs/sql_support.md](../../../../sql_support.md), [docs/code_review.md](../../../../code_review.md) |

```text
if (const auto* failure = std::get_if<frontend::BindingDiagnostic>(&result)) {
    auto output = write_sql_binding(*failure);
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Relabel a binding failure as a normalization diagnostic. |
| inputs / outputs | BindingDiagnostic alternative in; creates its binding DOM then erases binding_valid and sets normalization_valid=false. |
| invariants | Diagnostic envelope is rejected by read_sql_normalization as executable state. |
| ownership | New ordinary DOM owns copied diagnostic/phase strings. |
| failure | write_sql_binding/DOM allocation errors propagate; no successful normalized graph is constructed. |
| cost | Cost of diagnostic binding serialization plus small DOM key erase/insert. |
| Design | [src/io/normalization.cpp](../../../../../src/io/normalization.cpp), [include/crown/io/normalization.hpp](../../../../../include/crown/io/normalization.hpp), [include/crown/frontend/normalize.hpp](../../../../../include/crown/frontend/normalize.hpp), [src/io/binding.cpp](../../../../../src/io/binding.cpp), [src/io/document.cpp](../../../../../src/io/document.cpp), [src/io/json.hpp](../../../../../src/io/json.hpp), [docs/sql_support.md](../../../../sql_support.md), [docs/code_review.md](../../../../code_review.md) |

```text
{"binding",write_sql_binding(normalized.binding)},{"core",write_document(document)},
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Export the bound SQL and core CQ embedded in a successful normalization. |
| inputs / outputs | normalized.binding and local copied Document in; ordinary binding/core DOM fields out. |
| invariants | write_sql_binding accepts const SqlBindResult&, so a BoundSql argument constructs an owning variant copy before serialization. Document includes no runtime rows. |
| ownership | Binding variant deep-copies source text/catalog/resolved graph; BoundSql owns resolved expressions rather than a PostgreSQL AST. Core Document owns separate catalog/query; DOM copies serialized fields again. |
| failure | Binding/document validation/DOM or graph copy OOM errors propagate. |
| cost | Full binding graph copy plus binding/core serialization and their ordinary temporary memory peak; not charged normalization execution work. |
| Design | [src/io/normalization.cpp](../../../../../src/io/normalization.cpp), [include/crown/frontend/normalize.hpp](../../../../../include/crown/frontend/normalize.hpp), [src/io/binding.cpp](../../../../../src/io/binding.cpp), [src/io/document.cpp](../../../../../src/io/document.cpp), [docs/code_review.md](../../../../code_review.md) |

```text
for (const auto& adapter : normalized.adapters) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Export each normalized source adapter and its optional constant guards. |
| inputs / outputs | Borrowed adapters in; creates per-adapter arrays for predicates/classes/equalities/projection/program and permitted constants. |
| invariants | Version1 with any constant guard throws rather than hiding or dropping it; version2 preserves typed scalar values. |
| ownership | DOM owns arrays/scalar strings; adapter/source graph remains borrowed. |
| failure | Unsupported version1 guard or write_scalar/DOM errors abort enclosing writer. |
| cost | O(total adapter entries+constant payload bytes) traversal and ordinary array/object allocation. |
| Design | [src/io/normalization.cpp](../../../../../src/io/normalization.cpp), [include/crown/io/normalization.hpp](../../../../../include/crown/io/normalization.hpp), [include/crown/frontend/normalize.hpp](../../../../../include/crown/frontend/normalize.hpp), [src/io/binding.cpp](../../../../../src/io/binding.cpp), [src/io/document.cpp](../../../../../src/io/document.cpp), [src/io/json.hpp](../../../../../src/io/json.hpp), [docs/sql_support.md](../../../../sql_support.md), [docs/code_review.md](../../../../code_review.md) |

```text
for (const auto& field : normalized.outputs) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Preserve each output expression as either a core-column reference or typed constant. |
| inputs / outputs | Normalized output fields in; emits name/type/kind and column/value. |
| invariants | Column indices and expressions are output data; authority is reconstructed by normalization replay. |
| ownership | DOM copies names/types/constants into ordinary owned storage. |
| failure | Invalid variant/scalar/DOM failure propagates. |
| cost | O(output count+name/constant bytes), with per-field DOM allocations. |
| Design | [src/io/normalization.cpp](../../../../../src/io/normalization.cpp), [include/crown/io/normalization.hpp](../../../../../include/crown/io/normalization.hpp), [include/crown/frontend/normalize.hpp](../../../../../include/crown/frontend/normalize.hpp), [src/io/binding.cpp](../../../../../src/io/binding.cpp), [src/io/document.cpp](../../../../../src/io/document.cpp), [src/io/json.hpp](../../../../../src/io/json.hpp), [docs/sql_support.md](../../../../sql_support.md), [docs/code_review.md](../../../../code_review.md) |

## B0006

[Lines 62–86](../../../../../src/io/normalization.cpp#L62); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
frontend::NormalizedSql read_sql_normalization(std::string_view text, const ProgramReadLimits& limits) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Rebuild a normalized SQL program from serialized source binding and parameters, then compare the entire artifact. |
| inputs / outputs | Text and host ProgramReadLimits in; format1/2 NormalizedSql out after read_sql_binding and normalize_sql replay. |
| invariants | Requires successful Boolean flag but does not trust it: effective normalization work=min(stored,host) when capped, then stored work policy is restored for exact complete dump equality. All redundant core/adapters/routes/output/work/admission labels must match replay. |
| ownership | Ordinary input DOM and subtree dumps, rebuilt binding/parameters/normalization and expected DOM/text coexist. Returned object owns its ordinary graph; no native account claim. |
| failure | Parse/shape/version/binding/parameter failures propagate. Replay resource_limit diagnostic maps to resource_limit; other replay diagnostics to invalid_document. Mismatch/OOM publishes no program. |
| cost | Outer parse, binding dump+reparse/rebind, parameter envelope dump+reparse, full normalization, full serializer and two complete dump strings/comparison. Host normalization budget does not cap DOM/text allocation overhead. |
| Design | [src/io/normalization.cpp](../../../../../src/io/normalization.cpp), [include/crown/io/normalization.hpp](../../../../../include/crown/io/normalization.hpp), [include/crown/frontend/normalize.hpp](../../../../../include/crown/frontend/normalize.hpp), [src/io/binding.cpp](../../../../../src/io/binding.cpp), [src/io/document.cpp](../../../../../src/io/document.cpp), [src/io/json.hpp](../../../../../src/io/json.hpp), [docs/sql_support.md](../../../../sql_support.md), [docs/code_review.md](../../../../code_review.md) |

```text
const auto stored = encoded.is_null() ? std::optional<std::uint64_t>{} : detail::unsigned_integer(encoded,"$.limits.work_limit");
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Preserve stored producer policy while applying a stricter host work cap to actual replay. |
| inputs / outputs | Stored optional work limit and host limit in; options.limits.work_limit becomes their effective minimum. |
| invariants | Host may tighten replay only; normalized result later restores stored limit so canonical equality can still compare original policy. |
| ownership | Inline optionals/scalars; does not clone the normalization graph. |
| failure | Malformed stored numeric limit rejects before replay; no partial returned program. |
| cost | O(1) optional comparisons and assignments. |
| Design | [src/io/normalization.cpp](../../../../../src/io/normalization.cpp), [include/crown/io/normalization.hpp](../../../../../include/crown/io/normalization.hpp), [include/crown/frontend/normalize.hpp](../../../../../include/crown/frontend/normalize.hpp), [src/io/binding.cpp](../../../../../src/io/binding.cpp), [src/io/document.cpp](../../../../../src/io/document.cpp), [src/io/json.hpp](../../../../../src/io/json.hpp), [docs/sql_support.md](../../../../sql_support.md), [docs/code_review.md](../../../../code_review.md) |

```text
if (const auto* failure = std::get_if<frontend::BindingDiagnostic>(&result)) {
    if (failure->diagnostic.code == "resource_limit") throw Error("resource_limit","normalization replay: " + failure->diagnostic.message);
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Keep replay exhaustion distinct from a semantically nonreproducible normalization artifact. |
| inputs / outputs | BindingDiagnostic returned by normalize_sql in; throws resource_limit or invalid_document. |
| invariants | No false successful program on exhaustion; diagnostic code test preserves the public resource category. |
| ownership | Copies diagnostic message/code into ordinary Error text; partial replay graph unwinds. |
| failure | No catch of bad_alloc/native failures; replacement Error construction may fail separately. |
| cost | Exceptional diagnostic formatting O(message bytes) plus partial state release. |
| Design | [src/io/normalization.cpp](../../../../../src/io/normalization.cpp), [include/crown/io/normalization.hpp](../../../../../include/crown/io/normalization.hpp), [include/crown/frontend/normalize.hpp](../../../../../include/crown/frontend/normalize.hpp), [src/io/binding.cpp](../../../../../src/io/binding.cpp), [src/io/document.cpp](../../../../../src/io/document.cpp), [src/io/json.hpp](../../../../../src/io/json.hpp), [docs/sql_support.md](../../../../sql_support.md), [docs/code_review.md](../../../../code_review.md) |

```text
if (write_sql_normalization(normalized).dump() != input.dump()) detail::fail("$","normalized program differs from complete binding/normalization replay");
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Compare exact canonical serialized normalization including redundant fields and numeric DOM distinctions. |
| inputs / outputs | Rebuilt normalized value and original DOM in; exact dump-text inequality rejects. |
| invariants | Stored producer limit was restored before comparison; normalization_valid/admission/work/adapters are checked by replay, not trusted as evidence. |
| ownership | Passing NormalizedSql to const SqlNormalizeResult& implicitly constructs a variant that deep-copies its ordinary owning graph; then expected DOM and both dump strings are allocated. |
| failure | Any copy/serialize/dump/mismatch failure aborts before returning the rebuilt program. |
| cost | Full graph copy plus serialization and two encoded-text traversals/storage; explicit cold validation overhead outside normalization work counters. |
| Design | [src/io/normalization.cpp](../../../../../src/io/normalization.cpp), [include/crown/io/normalization.hpp](../../../../../include/crown/io/normalization.hpp), [include/crown/frontend/normalize.hpp](../../../../../include/crown/frontend/normalize.hpp), [src/io/binding.cpp](../../../../../src/io/binding.cpp), [src/io/document.cpp](../../../../../src/io/document.cpp), [src/io/json.hpp](../../../../../src/io/json.hpp), [docs/sql_support.md](../../../../sql_support.md), [docs/code_review.md](../../../../code_review.md) |

## B0008

[Lines 88–99](../../../../../src/io/normalization.cpp#L88); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
frontend::NormalizedSql upgrade_sql_normalization(const frontend::NormalizedSql& program, std::uint64_t target_version, const ProgramReadLimits& limits) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Validate a normalized program before performing an upward format1-to2 replay. |
| inputs / outputs | Owned program, target_version and host limits in; independently replayed current-format or upgraded NormalizedSql out. |
| invariants | Rejects downward/outside1..2 targets; same target still validates by writer+reader roundtrip. Upgrade reuses binding/parameters and stored policy with host effective cap, then restores original limits. |
| ownership | Fresh ordinary replay graph; original input untouched. Parameter copy and two normalization graphs can overlap during migration. |
| failure | Initial replay/target validation/OOM errors propagate; upgrade diagnostic throws its exact code with normalized-upgrade context. |
| cost | Full current artifact serialize/dump/reparse/replay/compare, then an additional normalize pass for an actual format upgrade; cold migration cost, not runtime update work. |
| Design | [src/io/normalization.cpp](../../../../../src/io/normalization.cpp), [include/crown/io/normalization.hpp](../../../../../include/crown/io/normalization.hpp), [include/crown/frontend/normalize.hpp](../../../../../include/crown/frontend/normalize.hpp), [src/io/binding.cpp](../../../../../src/io/binding.cpp), [src/io/document.cpp](../../../../../src/io/document.cpp), [src/io/json.hpp](../../../../../src/io/json.hpp), [docs/sql_support.md](../../../../sql_support.md), [docs/code_review.md](../../../../code_review.md) |

## B0010

[Lines 101–108](../../../../../src/io/normalization.cpp#L101); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::vector<frontend::SqlValue> read_parameter_values(std::string_view text) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Read an owning typed parameter list including explicit SQL NULL values. |
| inputs / outputs | Strict version1 values-array envelope text in; vector&lt;SqlValue&gt; out. |
| invariants | Only null becomes disengaged SqlValue; nonnull typed scalar parsing is delegated to read_scalar. No independent count/byte cap beyond parser depth. |
| ownership | DOM is temporary; result owns ordinary vector and scalar/string/decimal payload copies. |
| failure | Parse/shape/version/scalar/OOM errors unwind partial list; no program or parameter mutation is published. |
| cost | Full parse plus O(values+scalar bytes) extraction/deep-copy and vector growth. |
| Design | [src/io/normalization.cpp](../../../../../src/io/normalization.cpp), [include/crown/io/normalization.hpp](../../../../../include/crown/io/normalization.hpp), [include/crown/frontend/normalize.hpp](../../../../../include/crown/frontend/normalize.hpp), [src/io/binding.cpp](../../../../../src/io/binding.cpp), [src/io/document.cpp](../../../../../src/io/document.cpp), [src/io/json.hpp](../../../../../src/io/json.hpp), [docs/sql_support.md](../../../../sql_support.md), [docs/code_review.md](../../../../code_review.md) |

## B0011

[Lines 109–109](../../../../../src/io/normalization.cpp#L109); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L109-L109:sha256:a992a30ac7c9748c33994a213cb5eed12f62a6204d01f8b49f69db451a145039
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Closes the namespace crown::io at this source boundary; this is a lexical delimiter, not an operation. |
| inputs / outputs | No runtime input or output. Declarations following the span leave the preceding C++ scope. |
| invariants | The delimiter ends the preceding scope's visibility/linkage region; it adds no validation, publication, ownership transfer, or runtime authority. |
| ownership | The delimiter adds no owner. If it ends a function/block with live automatic objects, their normal destructors release those objects; namespace and type-definition closes change no existing object's lifetime. |
| failure | No explicit failure translation or catch is added. If a function/block exit destroys automatic objects, exception behavior follows those destructors; namespace/type closes have no runtime failure path. |
| cost | The delimiter adds no algorithmic work. A function/block exit can run existing automatic-object destructors and cleanup; namespace/type closes have no runtime cost. |
| Design | [src/io/normalization.cpp](../../../../../src/io/normalization.cpp), [docs/code_specs/files/src/io/normalization.cpp.md](normalization.cpp.md), [docs/sql_binding.md](../../../../sql_binding.md), [docs/sql_normalization.md](../../../../sql_normalization.md) |
