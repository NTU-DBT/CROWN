# `include/crown/storage/accounted_projection.hpp` — block usage map

[Source](../../../../../../include/crown/storage/accounted_projection.hpp) · [Source index](../../../../README.md) · [Subsystem contracts](../../../../subsystem_contracts.md) · [Reviewed primitives](../../../../primitives.md)

Represent exact typed scalars, rows, layouts and projections at compiler/public/native boundaries.

Snapshot SHA-256: `7e5d617cca6936eb5e19619382625bfc9cebd40bf68a835d9472e4fd1fc35901`. 60 lines partitioned into 10 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [values](../../../../subsystem_contracts.md#values). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/scalars.md](../../../../../scalars.md), [docs/storage.md](../../../../../storage.md), [docs/tuple_arenas.md](../../../../../tuple_arenas.md), [docs/verification/s05-public-tuples-2026-11-09.md](../../../../../verification/s05-public-tuples-2026-11-09.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–11](../../../../../../include/crown/storage/accounted_projection.hpp#L1) | Imports dependencies; guards repeated header inclusion; declares namespace scope. |  · [reviewed contract](#b0001) |
| [B0002 · 12–15](../../../../../../include/crown/storage/accounted_projection.hpp#L12) | Type/record definition: enum class ProjectionProblem |  · [reviewed contract](#b0002) |
| [B0003 · 16–24](../../../../../../include/crown/storage/accounted_projection.hpp#L16) | Type/record definition: class ProjectionValidationFailure final : public std::exception | returns issue_ · [reviewed contract](#b0003) |
| [B0004 · 25–35](../../../../../../include/crown/storage/accounted_projection.hpp#L25) | declares types or opens a type body; declares callable signatures; declares values/defaults or compile-time conditions. | source comment (unverified): // Construction proves the mapping against two frozen layouts sharing one · [reviewed contract](#b0004) |
| [B0005 · 36–36](../../../../../../include/crown/storage/accounted_projection.hpp#L36) | Callable definition: \[\[nodiscard\]\] explicit operator bool() const noexcept | calls ; returns bool(data_) · [reviewed contract](#b0005) |
| [B0006 · 37–43](../../../../../../include/crown/storage/accounted_projection.hpp#L37) | declares callable signatures; declares values/defaults or compile-time conditions. | source comment (unverified): // Exact shared program identity; equal field lists do not share a token. · [reviewed contract](#b0006) |
| [B0007 · 44–46](../../../../../../include/crown/storage/accounted_projection.hpp#L44) | Callable definition: \[\[nodiscard\]\] bool same_token(const AccountedProjection& other) const noexcept | calls ; returns data_ && data_ == other.data_; source comment (unverified): // Exact shared program identity; equal field lists do not share a token. · [reviewed contract](#b0007) |
| [B0008 · 47–52](../../../../../../include/crown/storage/accounted_projection.hpp#L47) | declares callable signatures; declares values/defaults or compile-time conditions. | source comment (unverified): // External/adapter row view: validation proves the source descriptor; the · [reviewed contract](#b0008) |
| [B0009 · 53–54](../../../../../../include/crown/storage/accounted_projection.hpp#L53) | Callable definition: private: explicit AccountedProjection(std::shared_ptr&lt;const Data&gt; data) noexcept : data_(std::move(data)) | calls data_, std::move · [reviewed contract](#b0009) |
| [B0010 · 55–60](../../../../../../include/crown/storage/accounted_projection.hpp#L55) | declares callable signatures; declares values/defaults or compile-time conditions. | source comment (unverified): // namespace crown::storage · [reviewed contract](#b0010) |

## B0001

[Lines 1–11](../../../../../../include/crown/storage/accounted_projection.hpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L1-L11:sha256:8843b4afcec90e15d4bff46c66ed0a1d3e814e2fcf9a7ad377863f9f9cfdfefe
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Source usage for this declaration span in include/crown/storage/accounted_projection.hpp: \`#pragma once\` makes this header idempotent within a translation unit; imports \`"crown/storage/accounted_layout.hpp"\`, \`&lt;exception&gt;\`, \`&lt;memory&gt;\`, \`&lt;span&gt;\`, \`&lt;string_view&gt;\`, \`&lt;utility&gt;\` for compilation; opens namespace \`crown::storage\`. |
| inputs / outputs | Compile inputs are the listed headers and namespace/type names. This span adds no result value unless a helper/type definition listed above is instantiated or called. |
| invariants | The exact import, alias, namespace and member declarations determine the local compile/link surface; stronger behavior belongs to their constructors and operations. |
| ownership | Imports, namespace aliases, forward declarations and compile guards create no object owner. Runtime ownership starts with declared object instances and their allocator/member types. |
| failure | No explicit throw/catch appears in this exact span. Includes, constructors, inline members, static initialization and callees can still fail; follow their enclosing API contracts. |
| cost | The include directives affect compile dependencies. Any runtime initializer or cost in included definitions follows those definitions and is not inferred absent by this import block. |
| Design | [docs/storage.md](../../../../../storage.md), [docs/scalars.md](../../../../../scalars.md), [docs/query_memory.md](../../../../../query_memory.md), [docs/code_specs/subsystem_contracts.md](../../../../subsystem_contracts.md) |

## B0002

[Lines 12–15](../../../../../../include/crown/storage/accounted_projection.hpp#L12); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
enum class ProjectionProblem {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Name projection admission and token-mismatch rejections. |
| inputs / outputs | Tags distinguish layout/account/context/arity/field/domain/variable/equality/token failures. |
| invariants | These are native fixed diagnostics, not proof that any unchecked mapping is valid. |
| ownership | The scalar/metadata result retains no row, account or runtime ownership; plain record declarations here own only their shown inline fields. |
| failure | The declaration does not throw or recover. |
| cost | Fixed-size metadata copy/read/comparison; no dynamic allocation or population traversal. |
| Design | [include/crown/storage/accounted_projection.hpp](../../../../../../include/crown/storage/accounted_projection.hpp), [src/storage/accounted_projection.cpp](../../../../../../src/storage/accounted_projection.cpp), [tests/unit/layout_test.cpp](../../../../../../tests/unit/layout_test.cpp), [docs/query_memory.md](../../../../../query_memory.md), [docs/storage.md](../../../../../storage.md), [docs/code_review.md](../../../../../code_review.md) |

## B0003

[Lines 16–24](../../../../../../include/crown/storage/accounted_projection.hpp#L16); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
class ProjectionValidationFailure final
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Carry a fixed native projection rejection without formatted strings. |
| inputs / outputs | Inline ProjectionProblem exposes issue/code/static what. |
| invariants | layout_mismatch is distinguished from invalid projection admission. |
| ownership | Owns enum only; static diagnostic views do not retain layout/data. |
| failure | Noexcept construction/access; throwing still uses normal exception runtime. |
| cost | Fixed-size status/presentation. |
| Design | [docs/storage.md](../../../../../storage.md), [docs/tuple_arenas.md](../../../../../tuple_arenas.md), [docs/query_memory.md](../../../../../query_memory.md), [docs/scalars.md](../../../../../scalars.md) |

## B0004

[Lines 25–35](../../../../../../include/crown/storage/accounted_projection.hpp#L25); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
class AccountedProjection {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Own a checked exact field mapping between two same-query native layouts. |
| inputs / outputs | freeze proves mapping; apply accepts either prevalidated token-bound tuple or fully validated external RowView; descriptor shares public mapping. |
| invariants | Numeric fields are immutable and target variable/domain equalities are proved once. Direct native tuple and public RowView routes have different validation costs. |
| ownership | Original account retains field block/shared Data and source/target tokens; output owns selected copied bytes. |
| failure | Fixed native projection/tuple failures are separately translated by public callback; funding failure publishes no projection/tuple. |
| cost | Admission uses accounted scratch; direct tuple apply has constant token checks then selected-field gather; RowView/public path also validates full source. |
| Design | [docs/storage.md](../../../../../storage.md), [docs/tuple_arenas.md](../../../../../tuple_arenas.md), [docs/query_memory.md](../../../../../query_memory.md), [docs/scalars.md](../../../../../scalars.md) |

```text
[[nodiscard]] static AccountedProjection freeze(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Prove and fund a native field-selection program once. |
| inputs / outputs | freeze accepts two existing AccountedLayouts, ordered FieldIds and attribution, returning an immutable AccountedProjection. |
| invariants | Requires valid same-account layouts with identical context, target arity, valid source positions, nonnarrowing domains, compatible variable identity and justified target equalities. |
| ownership | Copies FieldIds into funded metadata, funds shared Data/control, and retains both layout tokens. Caller field spans are not retained. |
| failure | ProjectionValidationFailure identifies mapping rejection; size/account/allocator failures propagate with no partial result. |
| cost | Visits selected fields plus context bytes; repeated-target-variable map admission is O(fields log fields) with accounted scratch, followed by field-array copy and funded shared allocation. |
| Design | [include/crown/storage/accounted_projection.hpp](../../../../../../include/crown/storage/accounted_projection.hpp), [src/storage/accounted_projection.cpp](../../../../../../src/storage/accounted_projection.cpp), [tests/unit/layout_test.cpp](../../../../../../tests/unit/layout_test.cpp), [docs/query_memory.md](../../../../../query_memory.md), [docs/storage.md](../../../../../storage.md), [docs/code_review.md](../../../../../code_review.md) |

## B0005

[Lines 36–36](../../../../../../include/crown/storage/accounted_projection.hpp#L36); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
[[nodiscard]] explicit operator bool() const noexcept { return bool(data_); }
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Test whether a frozen projection token is present. |
| inputs / outputs | Returns bool(data_), false for default/moved-from projection handles. |
| invariants | Presence is not descriptor equivalence or source tuple validation. |
| ownership | The scalar/metadata result retains no row, account or runtime ownership; plain record declarations here own only their shown inline fields. |
| failure | The shown inline operation is noexcept and has no throwing body or exception translation. |
| cost | Fixed-size metadata copy/read/comparison; no dynamic allocation or population traversal. |
| Design | [include/crown/storage/accounted_projection.hpp](../../../../../../include/crown/storage/accounted_projection.hpp), [src/storage/accounted_projection.cpp](../../../../../../src/storage/accounted_projection.cpp), [tests/unit/layout_test.cpp](../../../../../../tests/unit/layout_test.cpp), [docs/query_memory.md](../../../../../query_memory.md), [docs/storage.md](../../../../../storage.md), [docs/code_review.md](../../../../../code_review.md) |

## B0006

[Lines 37–43](../../../../../../include/crown/storage/accounted_projection.hpp#L37); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
[[nodiscard]] const AccountedLayout& source() const &;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Expose borrowed source/target layouts and ordered projected FieldIds from a frozen projection. |
| inputs / outputs | source(), target(), and fields() return const references/spans into the projection's Data. |
| invariants | freeze validates the mapping; the returned views remain valid only while a live projection owner retains Data. |
| ownership | Call these accessors on a retained lvalue AccountedProjection; rvalue overloads are deleted. |
| failure | An empty handle makes required() throw ProjectionValidationFailure(invalid_layout); rvalue use is a compile-time error. |
| cost | Accessors return borrowed metadata and allocate no field copy. |
| Design | [include/crown/storage/accounted_projection.hpp §AccountedProjection](../../../../../../include/crown/storage/accounted_projection.hpp), [src/storage/accounted_projection.cpp §required and getters](../../../../../../src/storage/accounted_projection.cpp), [docs/storage.md §Compiled projections](../../../../../storage.md) |

## B0007

[Lines 44–46](../../../../../../include/crown/storage/accounted_projection.hpp#L44); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
[[nodiscard]] bool same_token(const AccountedProjection& other) const noexcept {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Compare exact immutable projection identity. |
| inputs / outputs | Requires this token to be nonnull and identical to the other Data shared pointer. |
| invariants | An equal field list or independently frozen equivalent projection does not acquire this token. |
| ownership | Only compares existing shared ownership addresses; no owner is copied into the result. |
| failure | The shown inline operation is noexcept and has no throwing body or exception translation. |
| cost | Fixed-size metadata copy/read/comparison; no dynamic allocation or population traversal. |
| Design | [include/crown/storage/accounted_projection.hpp](../../../../../../include/crown/storage/accounted_projection.hpp), [src/storage/accounted_projection.cpp](../../../../../../src/storage/accounted_projection.cpp), [tests/unit/layout_test.cpp](../../../../../../tests/unit/layout_test.cpp), [docs/query_memory.md](../../../../../query_memory.md), [docs/storage.md](../../../../../storage.md), [docs/code_review.md](../../../../../code_review.md) |

## B0008

[Lines 47–52](../../../../../../include/crown/storage/accounted_projection.hpp#L47); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
[[nodiscard]] AccountedTuple apply(const AccountedTuple&) const;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Gather selected fields from an exactly token-matched native tuple. |
| inputs / outputs | The two AccountedTuple overloads require the exact source token, preserve or override attribution, and return target-layout native output. |
| invariants | freeze already proved target domains/equalities. The direct native path does not revalidate the entire source row or build an intermediate owning Row. |
| ownership | Input tuple is borrowed during copying; result shares target metadata and owns selected bytes under the projection's existing account. |
| failure | Empty projection, token mismatch, payload-size overflow or account/allocation denial propagates before result return. |
| cost | Fixed token checks (the preserving overload repeats the check) plus selected-field sizing/copy/deep-string bytes and one funded row allocation. |
| Design | [include/crown/storage/accounted_projection.hpp](../../../../../../include/crown/storage/accounted_projection.hpp), [src/storage/accounted_projection.cpp](../../../../../../src/storage/accounted_projection.cpp), [tests/unit/layout_test.cpp](../../../../../../tests/unit/layout_test.cpp), [docs/query_memory.md](../../../../../query_memory.md), [docs/storage.md](../../../../../storage.md), [docs/code_review.md](../../../../../code_review.md) |

```text
[[nodiscard]] AccountedTuple apply(RowView,resource::MemoryAttribution = {}) const;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Validate an external compact row before using the compiled selection. |
| inputs / outputs | apply(RowView,attribution) validates full source descriptor then gathers selected fields into target-layout native output. |
| invariants | A bare RowView carries no source token authority; it must not use the direct AccountedTuple shortcut. |
| ownership | Caller descriptors/string bytes remain borrowed until copy completes; output owns copied bytes in the original projection account. |
| failure | Source TupleValidationFailure and projection/account/allocation failures propagate; no borrowed output escapes on failure. |
| cost | Full source field/equality validation plus selected descriptor/string copying and one funded row allocation; this adapter can do more work than direct native apply. |
| Design | [include/crown/storage/accounted_projection.hpp](../../../../../../include/crown/storage/accounted_projection.hpp), [src/storage/accounted_projection.cpp](../../../../../../src/storage/accounted_projection.cpp), [tests/unit/layout_test.cpp](../../../../../../tests/unit/layout_test.cpp), [docs/query_memory.md](../../../../../query_memory.md), [docs/storage.md](../../../../../storage.md), [docs/code_review.md](../../../../../code_review.md) |

```text
[[nodiscard]] Projection descriptor() const;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Expose a retaining public projection descriptor without rebuilding its map. |
| inputs / outputs | descriptor returns Projection(data_), preserving both layout tokens, selected fields and native callback. |
| invariants | Sharing this handle creates neither a fresh field-selection program nor a new account. |
| ownership | Returned Projection retains funded Data/source/target metadata and can outlive this wrapper; its fields span still borrows that shared backing. |
| failure | Empty projections reject with fixed invalid_projection; no owning legacy metadata fallback is allocated. |
| cost | Fixed shared-handle copy. Later public apply additionally checks token and validates full source, unlike direct native AccountedTuple apply. |
| Design | [include/crown/storage/accounted_projection.hpp](../../../../../../include/crown/storage/accounted_projection.hpp), [src/storage/accounted_projection.cpp](../../../../../../src/storage/accounted_projection.cpp), [tests/unit/layout_test.cpp](../../../../../../tests/unit/layout_test.cpp), [docs/query_memory.md](../../../../../query_memory.md), [docs/storage.md](../../../../../storage.md), [docs/code_review.md](../../../../../code_review.md) |

## B0009

[Lines 53–54](../../../../../../include/crown/storage/accounted_projection.hpp#L53); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
explicit AccountedProjection(std::shared_ptr<const Data> data) noexcept : data_(std::move(data)) {}
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Adopt an already checked funded projection owner. |
| inputs / outputs | Private constructor moves shared_ptr&lt;const Data&gt;. |
| invariants | Mapping proof, source/target account match and metadata admission belong to freeze, not this move. |
| ownership | Retains the same funded field map and source/target layout tokens. |
| failure | The shown inline operation is noexcept and has no throwing body or exception translation. |
| cost | Fixed-size metadata copy/read/comparison; no dynamic allocation or population traversal. |
| Design | [include/crown/storage/accounted_projection.hpp](../../../../../../include/crown/storage/accounted_projection.hpp), [src/storage/accounted_projection.cpp](../../../../../../src/storage/accounted_projection.cpp), [tests/unit/layout_test.cpp](../../../../../../tests/unit/layout_test.cpp), [docs/query_memory.md](../../../../../query_memory.md), [docs/storage.md](../../../../../storage.md), [docs/code_review.md](../../../../../code_review.md) |

## B0010

[Lines 55–60](../../../../../../include/crown/storage/accounted_projection.hpp#L55); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::shared_ptr<const Data> data_;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Retain the immutable validated projection mapping and its source/target layouts. |
| inputs / outputs | freeze supplies the Data; getters, token comparison, and apply read it. |
| invariants | Data holds the account, layouts, and funded FieldId storage; the mapping is const after publication. |
| ownership | Copies share Data and keep its layouts/field block alive until the last handle releases it. |
| failure | The field itself has no failure path; accessing an empty projection throws invalid_layout. |
| cost | The declaration allocates nothing; final release can free the field allocation and shared control. |
| Design | [src/storage/accounted_projection.cpp §AccountedProjection::Data](../../../../../../src/storage/accounted_projection.cpp), [src/storage/accounted_projection.cpp §AccountedProjection::freeze](../../../../../../src/storage/accounted_projection.cpp), [docs/storage.md §Compiled projections](../../../../../storage.md), [docs/query_memory.md](../../../../../query_memory.md) |
