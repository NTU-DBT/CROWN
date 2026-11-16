# `src/io/binding.cpp` — block usage map

[Source](../../../../../src/io/binding.cpp) · [Source index](../../../README.md) · [Subsystem contracts](../../../subsystem_contracts.md) · [Reviewed primitives](../../../primitives.md)

Admit bounded external documents/records and serialize explicit public representations at the engine boundary.

Snapshot SHA-256: `ef15e0ec4e59d93550e8e1ed0773b5254f2cfd12636f3a6ea739101d13e593ec`. 138 lines partitioned into 11 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [io](../../../subsystem_contracts.md#io). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/ingestion.md](../../../../ingestion.md), [docs/query_identity.md](../../../../query_identity.md), [docs/schema_evolution.md](../../../../schema_evolution.md), [docs/cli.md](../../../../cli.md), [docs/query_memory.md](../../../../query_memory.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–9](../../../../../src/io/binding.cpp#L1) | Imports dependencies; declares namespace scope. |  · [reviewed contract](#b0001) |
| [B0002 · 10–14](../../../../../src/io/binding.cpp#L10) | Callable definition: Json type_json(const frontend::SqlType& type) | calls frontend::sql_kind_name; returns output · [reviewed contract](#b0002) |
| [B0003 · 15–15](../../../../../src/io/binding.cpp#L15) | Callable definition: Json optional_offset(std::optional&lt;std::size_t&gt; offset) | calls Json; returns offset ? Json(*offset) : Json(nullptr) · [reviewed contract](#b0003) |
| [B0004 · 16–16](../../../../../src/io/binding.cpp#L16) | Callable definition: std::string semantics(frontend::SqlSemantics mode) | calls ; returns mode == frontend::SqlSemantics::set ? @ : @ · [reviewed contract](#b0004) |
| [B0005 · 17–18](../../../../../src/io/binding.cpp#L17) | Closes surrounding scope/type. | source comment (unverified): // namespace · [reviewed contract](#b0005) |
| [B0006 · 19–75](../../../../../src/io/binding.cpp#L19) | Callable definition: Json write_sql_binding(const frontend::SqlBindResult& result) | calls optional_offset, write_catalog, semantics, Json; returns output; output; growth push_back; 6 loop sites · [reviewed contract](#b0006) |
| [B0007 · 76–78](../../../../../src/io/binding.cpp#L76) | Explanatory comments or spacing. | source comment (unverified): // Every encoded binding field is an assertion checked by complete source/catalog · [reviewed contract](#b0007) |
| [B0008 · 79–119](../../../../../src/io/binding.cpp#L79) | Callable definition: frontend::BoundSql read_sql_binding(std::string_view text, frontend::BindLimits replay_limits) | calls detail::parse_json, detail::fields, detail::version, at; returns static_cast&lt;std::size_t&gt;(number); bound; growth push_back; 1 loop sites; source comment (unverified): // Every encoded binding field is an assertion checked by complete source/catalog · [reviewed contract](#b0008) |
| [B0009 · 120–120](../../../../../src/io/binding.cpp#L120) | Explanatory comments or spacing. |  |
| [B0010 · 121–137](../../../../../src/io/binding.cpp#L121) | Callable definition: frontend::BindOptions read_bind_options(std::string_view text) | calls detail::parse_json, detail::fields, detail::version, at; returns options; growth push_back; 1 loop sites · [reviewed contract](#b0010) |
| [B0011 · 138–138](../../../../../src/io/binding.cpp#L138) | Closes surrounding scope/type. | source comment (unverified): // namespace crown::io · [reviewed contract](#b0011) |

## B0001

[Lines 1–9](../../../../../src/io/binding.cpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L1-L9:sha256:ca57034cbc718c699cbe2e57d136c03d307e48eaeaee8fe9c0969e2dde91eda4
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Imports compile-time dependencies (crown/io/binding.hpp, crown/io/catalog.hpp, json.hpp, limits, type_traits) and opens crown::io scope for the declarations or definitions that follow. |
| inputs / outputs | No runtime inputs/outputs are declared by the import/scope lines themselves. |
| invariants | The listed headers and namespace membership determine compile-time name availability; any API behavior belongs to the declarations/definitions that follow. |
| ownership | No object ownership is created by the imports or namespace tokens. |
| failure | No runtime failure path. Missing/incompatible dependencies or a violated compile-time constraint fail translation/linking. |
| cost | Compile/preprocessor work only; no new per-operation runtime overhead. |
| Design | [src/io/binding.cpp](../../../../../src/io/binding.cpp), [docs/code_specs/files/src/io/binding.cpp.md](binding.cpp.md), [docs/sql_binding.md](../../../../sql_binding.md), [docs/sql_normalization.md](../../../../sql_normalization.md) |

## B0002

[Lines 10–14](../../../../../src/io/binding.cpp#L10); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Json type_json(const frontend::SqlType& type) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Describe one SQL expression/parameter type in binding JSON. |
| inputs / outputs | Writes SqlKind name, nullable flag and optional exact decimal precision/scale. |
| invariants | The serializer does not validate an edited SqlType or turn unknown/int32 expression kinds into legal catalog parameter signatures. |
| ownership | The returned ordinary owning JSON tree copies its exposed strings/arrays/objects; it retains no live runtime, grant or typed proof capability. |
| failure | Shape/type/version, parser/serialization or ordinary allocation failures propagate; this boundary adds no catch, fallback or retry. |
| cost | Small DOM/string construction and optional scalar fields; no binding or decimal-value conversion. |
| Design | [src/io/binding.cpp](../../../../../src/io/binding.cpp), [include/crown/frontend/bind.hpp](../../../../../include/crown/frontend/bind.hpp), [src/frontend/bind.cpp](../../../../../src/frontend/bind.cpp), [src/io/catalog.cpp](../../../../../src/io/catalog.cpp), [tests/unit/binding_test.cpp](../../../../../tests/unit/binding_test.cpp), [tests/integration/binding.py](../../../../../tests/integration/binding.py), [docs/sql_binding.md](../../../../sql_binding.md), [docs/schema_evolution.md](../../../../schema_evolution.md), [docs/code_review.md](../../../../code_review.md) |

## B0003

[Lines 15–15](../../../../../src/io/binding.cpp#L15); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Json optional_offset(std::optional<std::size_t> offset) { return offset ? Json(*offset) : Json(nullptr); }
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Preserve optional parser-source coordinates without changing their domain. |
| inputs / outputs | Returns size_t JSON integer or null for missing byte/character/line/column metadata. |
| invariants | Coordinates keep the parser/binder convention; this helper performs no UTF-8 indexing or offset repair. |
| ownership | Owns a JSON scalar only. |
| failure | Shape/type/version, parser/serialization or ordinary allocation failures propagate; this boundary adds no catch, fallback or retry. |
| cost | Fixed scalar/null creation; no source scan. |
| Design | [src/io/binding.cpp](../../../../../src/io/binding.cpp), [include/crown/frontend/bind.hpp](../../../../../include/crown/frontend/bind.hpp), [src/frontend/bind.cpp](../../../../../src/frontend/bind.cpp), [src/io/catalog.cpp](../../../../../src/io/catalog.cpp), [tests/unit/binding_test.cpp](../../../../../tests/unit/binding_test.cpp), [tests/integration/binding.py](../../../../../tests/integration/binding.py), [docs/sql_binding.md](../../../../sql_binding.md), [docs/schema_evolution.md](../../../../schema_evolution.md), [docs/code_review.md](../../../../code_review.md) |

## B0004

[Lines 16–16](../../../../../src/io/binding.cpp#L16); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::string semantics(frontend::SqlSemantics mode) { return mode == frontend::SqlSemantics::set ? "set" : "bag"; }
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Name the requested producer SQL set/bag mode. |
| inputs / outputs | Returns owning text set for SqlSemantics::set, otherwise bag under the valid-producer enum precondition. |
| invariants | This is serialization, not enum validation, semantic normalization or runtime mode selection. |
| ownership | Returned std::string owns the short label. |
| failure | No exception translation; ordinary string construction may fail. |
| cost | Bounded label construction; no query traversal. |
| Design | [src/io/binding.cpp](../../../../../src/io/binding.cpp), [include/crown/frontend/bind.hpp](../../../../../include/crown/frontend/bind.hpp), [src/frontend/bind.cpp](../../../../../src/frontend/bind.cpp), [src/io/catalog.cpp](../../../../../src/io/catalog.cpp), [tests/unit/binding_test.cpp](../../../../../tests/unit/binding_test.cpp), [tests/integration/binding.py](../../../../../tests/integration/binding.py), [docs/sql_binding.md](../../../../sql_binding.md), [docs/schema_evolution.md](../../../../schema_evolution.md), [docs/code_review.md](../../../../code_review.md) |

## B0005

[Lines 17–18](../../../../../src/io/binding.cpp#L17); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L17-L18:sha256:c2bd7638f09d52cb034ed574f539304035fc6fab162bf8d5fa20a35d8c7288a1
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Closes the anonymous namespace at this source boundary; this is a lexical delimiter, not an operation. |
| inputs / outputs | No runtime input or output. Declarations following the span leave the preceding C++ scope. |
| invariants | The delimiter ends the preceding scope's visibility/linkage region; it adds no validation, publication, ownership transfer, or runtime authority. |
| ownership | The delimiter adds no owner. If it ends a function/block with live automatic objects, their normal destructors release those objects; namespace and type-definition closes change no existing object's lifetime. |
| failure | No explicit failure translation or catch is added. If a function/block exit destroys automatic objects, exception behavior follows those destructors; namespace/type closes have no runtime failure path. |
| cost | The delimiter adds no algorithmic work. A function/block exit can run existing automatic-object destructors and cleanup; namespace/type closes have no runtime cost. |
| Design | [src/io/binding.cpp](../../../../../src/io/binding.cpp), [docs/code_specs/files/src/io/binding.cpp.md](binding.cpp.md), [docs/sql_binding.md](../../../../sql_binding.md), [docs/sql_normalization.md](../../../../sql_normalization.md) |

## B0006

[Lines 19–75](../../../../../src/io/binding.cpp#L19); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Json write_sql_binding(const frontend::SqlBindResult& result) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Serialize an owned binding or diagnostic without claiming admission. |
| inputs / outputs | Diagnostic alternatives expose phase/code/message/locations. Successful BoundSql exports source/catalog, parameters, occurrences, typed expression DAG IDs, predicates, ordered outputs, stored limits and work. |
| invariants | admission_status stays not_checked. Table IDs bind to the owned flat catalog; include_descendants records SQL intent but catalogs have no inheritance edges. Writer assumes valid initialized producer DTOs. |
| ownership | The returned ordinary owning JSON tree copies its exposed strings/arrays/objects; it retains no live runtime, grant or typed proof capability. |
| failure | Shape/type/version, parser/serialization or ordinary allocation failures propagate; this boundary adds no catch, fallback or retry. |
| cost | Deep ordinary JSON/catalog/source/array copies over all binding records and literal bytes, including scalar/date/decimal formatting. It neither parses nor rebinds SQL. |
| Design | [src/io/binding.cpp](../../../../../src/io/binding.cpp), [include/crown/frontend/bind.hpp](../../../../../include/crown/frontend/bind.hpp), [src/frontend/bind.cpp](../../../../../src/frontend/bind.cpp), [src/io/catalog.cpp](../../../../../src/io/catalog.cpp), [tests/unit/binding_test.cpp](../../../../../tests/unit/binding_test.cpp), [tests/integration/binding.py](../../../../../tests/integration/binding.py), [docs/sql_binding.md](../../../../sql_binding.md), [docs/schema_evolution.md](../../../../schema_evolution.md), [docs/code_review.md](../../../../code_review.md) |

```text
      if constexpr (std::is_same_v<T,frontend::BoundColumn>) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Encode each expression node with its exact kind-specific references and values. |
| inputs / outputs | Column records use occurrence/column IDs; literals preserve typed values or SQL NULL; parameters preserve one-based number; operations preserve ordered child expression IDs and operator name. |
| invariants | Expression source locations and SQL types are emitted separately. Rendering these editable references does not validate an arbitrary expression graph or mint a compiled executable. |
| ownership | The returned ordinary owning JSON tree copies its exposed strings/arrays/objects; it retains no live runtime, grant or typed proof capability. |
| failure | Shape/type/version, parser/serialization or ordinary allocation failures propagate; this boundary adds no catch, fallback or retry. |
| cost | Visits all expression records/argument IDs and copies literal/string/decimal payload as needed. No expression evaluation or native row allocation occurs. |
| Design | [src/io/binding.cpp](../../../../../src/io/binding.cpp), [include/crown/frontend/bind.hpp](../../../../../include/crown/frontend/bind.hpp), [src/frontend/bind.cpp](../../../../../src/frontend/bind.cpp), [src/io/catalog.cpp](../../../../../src/io/catalog.cpp), [tests/unit/binding_test.cpp](../../../../../tests/unit/binding_test.cpp), [tests/integration/binding.py](../../../../../tests/integration/binding.py), [docs/sql_binding.md](../../../../sql_binding.md), [docs/schema_evolution.md](../../../../schema_evolution.md), [docs/code_review.md](../../../../code_review.md) |

## B0007

[Lines 76–78](../../../../../src/io/binding.cpp#L76); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L76-L78:sha256:697601d945909cc43d590f0c3c6002048913c87077d3468de5a9eabf7cc08baf
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Design note for adjacent code: Every encoded binding field is an assertion checked by complete source/catalog replay. Parsed flags and expression IDs are not admission authority. This is caller guidance recorded as prose, not an executable result. |
| inputs / outputs | No runtime interface is implemented by these comment-only lines. They sit at src/io/binding.cpp lines 74-80; the surrounding declaration/body defines its own inputs and outputs. |
| invariants | The words record the intended use boundary only. They do not add a guard, proof, capability, transaction, durability guarantee, or account charge; verify behavior in the referenced implementation. |
| ownership | Comment text owns no data. Object lifetimes, borrows, and account attribution remain those of the adjacent source objects and their constructors. |
| failure | No failure path is implemented here. Any mentioned failure or recovery rule belongs to the adjacent operation and its existing error carrier. |
| cost | No runtime work is performed by these lines; any cost/bound in the note is not certified by this comment-only card. |
| Design | [src/io/binding.cpp](../../../../../src/io/binding.cpp), [docs/code_specs/files/src/io/binding.cpp.md](binding.cpp.md), [docs/sql_binding.md](../../../../sql_binding.md), [docs/sql_normalization.md](../../../../sql_normalization.md) |

## B0008

[Lines 79–119](../../../../../src/io/binding.cpp#L79); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
frontend::BoundSql read_sql_binding(std::string_view text, frontend::BindLimits replay_limits) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Regain a successful binding only by complete bounded source/catalog replay. |
| inputs / outputs | Parses strict artifact, rebuilds parameter signatures/catalog/stored limits, clamps operational replay limits, rebinds source, restores stored-limit metadata and compares complete serialized output with parsed input. |
| invariants | No editable expression/node/work/flag field is trusted as authority. Object-key/whitespace spelling is normalized by parsed JSON, while complete field/type/value content must match replay. Successful return remains a mutable BoundSql DTO requiring producer invariants if later edited. |
| ownership | Owns replayed source/catalog/expressions/outputs independently of the input string. Simultaneous input DOM, replay DTO and two dump strings are temporary ordinary allocations. |
| failure | Resource-limit BindingDiagnostic is preserved as Error(resource_limit); other replay rejection/mismatch becomes invalid_document. Parser-contract/allocator failures can escape; no broad handler is added. |
| cost | Full JSON/catalog/signature dump/reparse plus real parser/binder replay and complete DOM serialization/comparison. Replay work/depth/expression caps do not meter every DTO allocation or copied byte. |
| Design | [src/io/binding.cpp](../../../../../src/io/binding.cpp), [include/crown/frontend/bind.hpp](../../../../../include/crown/frontend/bind.hpp), [src/frontend/bind.cpp](../../../../../src/frontend/bind.cpp), [src/io/catalog.cpp](../../../../../src/io/catalog.cpp), [tests/unit/binding_test.cpp](../../../../../tests/unit/binding_test.cpp), [tests/integration/binding.py](../../../../../tests/integration/binding.py), [docs/sql_binding.md](../../../../sql_binding.md), [docs/schema_evolution.md](../../../../schema_evolution.md), [docs/code_review.md](../../../../code_review.md) |

```text
  options.limits = stored;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Apply host replay ceilings while preserving artifact limit metadata for exact comparison. |
| inputs / outputs | Copies stored limits, then takes the smaller present work cap and minimum expression/recursion ceilings; after successful bind, stored metadata is restored before writing the comparison artifact. |
| invariants | A tighter host cap can reject replay but does not rewrite the artifact into a different accepted contract. Unlimited stored work is still constrained by a finite host ceiling. |
| ownership | Only local BindOptions/returned BoundSql limit fields are changed. |
| failure | Exhausted replay reports resource_limit; no fallback partial binding is returned. |
| cost | Fixed optional/scalar comparisons; parser/binder work is paid by the later replay call. |
| Design | [src/io/binding.cpp](../../../../../src/io/binding.cpp), [include/crown/frontend/bind.hpp](../../../../../include/crown/frontend/bind.hpp), [src/frontend/bind.cpp](../../../../../src/frontend/bind.cpp), [src/io/catalog.cpp](../../../../../src/io/catalog.cpp), [tests/unit/binding_test.cpp](../../../../../tests/unit/binding_test.cpp), [tests/integration/binding.py](../../../../../tests/integration/binding.py), [docs/sql_binding.md](../../../../sql_binding.md), [docs/schema_evolution.md](../../../../schema_evolution.md), [docs/code_review.md](../../../../code_review.md) |

## B0010

[Lines 121–137](../../../../../src/io/binding.cpp#L121); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
frontend::BindOptions read_bind_options(std::string_view text) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Build binding parameter metadata through the catalog column validation boundary. |
| inputs / outputs | Reads strict schema-v1 parameter type objects, assigns synthetic names $1...$n, wraps them as one table and uses read_catalog_payload, returning its validated columns. |
| invariants | Catalog scalar types/nullability/binary collation/exact decimal domains apply. This does not bind parameter values, parse SQL or normalize expressions. |
| ownership | Returns ordinary owned Column/vector/string metadata; caller JSON is copied into temporary synthetic catalog nodes. |
| failure | Shape/type/version, parser/serialization or ordinary allocation failures propagate; this boundary adds no catch, fallback or retry. |
| cost | Parameter iteration/string naming plus ordinary DOM copies and complete synthetic catalog validation; map/name/domain checks retain their real costs. |
| Design | [src/io/binding.cpp](../../../../../src/io/binding.cpp), [include/crown/frontend/bind.hpp](../../../../../include/crown/frontend/bind.hpp), [src/frontend/bind.cpp](../../../../../src/frontend/bind.cpp), [src/io/catalog.cpp](../../../../../src/io/catalog.cpp), [tests/unit/binding_test.cpp](../../../../../tests/unit/binding_test.cpp), [tests/integration/binding.py](../../../../../tests/integration/binding.py), [docs/sql_binding.md](../../../../sql_binding.md), [docs/schema_evolution.md](../../../../schema_evolution.md), [docs/code_review.md](../../../../code_review.md) |

## B0011

[Lines 138–138](../../../../../src/io/binding.cpp#L138); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L138-L138:sha256:a992a30ac7c9748c33994a213cb5eed12f62a6204d01f8b49f69db451a145039
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Closes the namespace crown::io at this source boundary; this is a lexical delimiter, not an operation. |
| inputs / outputs | No runtime input or output. Declarations following the span leave the preceding C++ scope. |
| invariants | The delimiter ends the preceding scope's visibility/linkage region; it adds no validation, publication, ownership transfer, or runtime authority. |
| ownership | The delimiter adds no owner. If it ends a function/block with live automatic objects, their normal destructors release those objects; namespace and type-definition closes change no existing object's lifetime. |
| failure | No explicit failure translation or catch is added. If a function/block exit destroys automatic objects, exception behavior follows those destructors; namespace/type closes have no runtime failure path. |
| cost | The delimiter adds no algorithmic work. A function/block exit can run existing automatic-object destructors and cleanup; namespace/type closes have no runtime cost. |
| Design | [src/io/binding.cpp](../../../../../src/io/binding.cpp), [docs/code_specs/files/src/io/binding.cpp.md](binding.cpp.md), [docs/sql_binding.md](../../../../sql_binding.md), [docs/sql_normalization.md](../../../../sql_normalization.md) |
