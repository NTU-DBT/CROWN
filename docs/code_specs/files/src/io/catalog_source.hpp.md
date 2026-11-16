# `src/io/catalog_source.hpp` — block usage map

[Source](../../../../../src/io/catalog_source.hpp) · [Source index](../../../README.md) · [Subsystem contracts](../../../subsystem_contracts.md) · [Reviewed primitives](../../../primitives.md)

Admit bounded external documents/records and serialize explicit public representations at the engine boundary.

Snapshot SHA-256: `677c14d73e729ce74be4a1da288b8a9cfa9391363ef270573a2b338f53282642`. 21 lines partitioned into 3 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [io](../../../subsystem_contracts.md#io). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/ingestion.md](../../../../ingestion.md), [docs/query_identity.md](../../../../query_identity.md), [docs/schema_evolution.md](../../../../schema_evolution.md), [docs/cli.md](../../../../cli.md), [docs/query_memory.md](../../../../query_memory.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–10](../../../../../src/io/catalog_source.hpp#L1) | Imports dependencies; guards repeated header inclusion; declares namespace scope. | source comment (unverified): // Dispatch preserves callback ownership: returned references still borrow source. · [reviewed contract](#b0001) |
| [B0002 · 11–20](../../../../../src/io/catalog_source.hpp#L11) | Callable definition: template&lt;class Function&gt; decltype(auto) read(const CatalogSource& source,Function&& function) | calls std::visit, constexpr, Error; returns std::visit(\[&\](const auto& value)-&gt;decltype(auto) {; std::forward&lt;Function&gt;(function)(value); source comment (unverified): // Dispatch preserves callback ownership: returned references still borrow source. · [reviewed contract](#b0002) |
| [B0003 · 21–21](../../../../../src/io/catalog_source.hpp#L21) | Closes surrounding scope/type. | source comment (unverified): // namespace crown::io::catalog_source_detail · [reviewed contract](#b0003) |

## B0001

[Lines 1–10](../../../../../src/io/catalog_source.hpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L1-L10:sha256:d6d62bed9d2d85e904e9ea66676948914989e1c04db6a58d47ad0d96a599a445
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Imports compile-time dependencies (crown/io/catalog_source.hpp, crown/ir/program_model.hpp, crown/api/error.hpp, type_traits, utility) and opens crown::io::catalog_source_detail scope for the declarations or definitions that follow. Embedded source note records intended usage: Dispatch preserves callback ownership: returned references still borrow source. Presence of a native owner alone does not validate catalog semantics. Treat that prose as guidance, not as independently verified executable behavior. |
| inputs / outputs | No runtime inputs/outputs are declared by the import/scope lines themselves. |
| invariants | The listed headers and namespace membership determine compile-time name availability; any API behavior belongs to the declarations/definitions that follow. |
| ownership | No object ownership is created by the imports or namespace tokens. |
| failure | No runtime failure path. Missing/incompatible dependencies or a violated compile-time constraint fail translation/linking. |
| cost | Compile/preprocessor work only; no new per-operation runtime overhead. |
| Design | [src/io/catalog_source.hpp](../../../../../src/io/catalog_source.hpp), [docs/code_specs/files/src/io/catalog_source.hpp.md](catalog_source.hpp.md), [docs/ingestion.md](../../../../ingestion.md), [docs/catalog.md](../../../../catalog.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0002

[Lines 11–20](../../../../../src/io/catalog_source.hpp#L11); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
template<class Function> decltype(auto) read(const CatalogSource& source,Function&& function) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Visit either an owned compiler catalog or retained native program catalog without copying it. |
| inputs / outputs | std::visit forwards the callback once, passing Catalog const& directly or dereferencing a nonempty shared_ptr&lt;const program::Catalog&gt;; decltype(auto) preserves callback result category. |
| invariants | Callback result type/category must agree for both alternatives. This dispatcher checks native owner presence only, not schema validity, proof, account compatibility or admission. Callers establish those boundaries. |
| ownership | CatalogSource owns ordinary Catalog or retains the aliasing immutable program owner. Callback references/views borrow that backing; the visitor creates no owner for returned borrows. |
| failure | Empty native owner throws invalid_catalog; callback errors propagate unchanged. There is no catch, ordinary-catalog export or fallback. |
| cost | Fixed variant dispatch and callback invocation; all callback scanning/formatting/allocation costs remain explicit, and no implicit schema copy occurs. |
| Design | [src/io/catalog_source.hpp](../../../../../src/io/catalog_source.hpp), [include/crown/io/catalog_source.hpp](../../../../../include/crown/io/catalog_source.hpp), [include/crown/ir/program.hpp](../../../../../include/crown/ir/program.hpp), [src/io/event_reader.cpp](../../../../../src/io/event_reader.cpp), [src/io/batch.cpp](../../../../../src/io/batch.cpp), [docs/ingestion.md](../../../../ingestion.md), [docs/code_review.md](../../../../code_review.md) |

## B0003

[Lines 21–21](../../../../../src/io/catalog_source.hpp#L21); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L21-L21:sha256:4608ebda2b377fe84aff995a75ad7623bc137f06cf33bc514b4ea486303eb425
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Closes the namespace crown::io::catalog_source_detail at this source boundary; this is a lexical delimiter, not an operation. |
| inputs / outputs | No runtime input or output. Declarations following the span leave the preceding C++ scope. |
| invariants | The delimiter ends the preceding scope's visibility/linkage region; it adds no validation, publication, ownership transfer, or runtime authority. |
| ownership | The delimiter adds no owner. If it ends a function/block with live automatic objects, their normal destructors release those objects; namespace and type-definition closes change no existing object's lifetime. |
| failure | No explicit failure translation or catch is added. If a function/block exit destroys automatic objects, exception behavior follows those destructors; namespace/type closes have no runtime failure path. |
| cost | The delimiter adds no algorithmic work. A function/block exit can run existing automatic-object destructors and cleanup; namespace/type closes have no runtime cost. |
| Design | [src/io/catalog_source.hpp](../../../../../src/io/catalog_source.hpp), [docs/code_specs/files/src/io/catalog_source.hpp.md](catalog_source.hpp.md), [docs/ingestion.md](../../../../ingestion.md), [docs/catalog.md](../../../../catalog.md), [docs/query_memory.md](../../../../query_memory.md) |
