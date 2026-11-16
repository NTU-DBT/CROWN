# `include/crown/storage/tuple_values.hpp` — block usage map

[Source](../../../../../../include/crown/storage/tuple_values.hpp) · [Source index](../../../../README.md) · [Subsystem contracts](../../../../subsystem_contracts.md) · [Reviewed primitives](../../../../primitives.md)

Represent exact typed scalars, rows, layouts and projections at compiler/public/native boundaries.

Snapshot SHA-256: `4884cf7ff09ee90ef0ed9eaa6c8731f6887fc8c95355575f39b7c8ec1ce3a58a`. 77 lines partitioned into 17 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [values](../../../../subsystem_contracts.md#values). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/scalars.md](../../../../../scalars.md), [docs/storage.md](../../../../../storage.md), [docs/tuple_arenas.md](../../../../../tuple_arenas.md), [docs/verification/s05-public-tuples-2026-11-09.md](../../../../../verification/s05-public-tuples-2026-11-09.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–21](../../../../../../include/crown/storage/tuple_values.hpp#L1) | Imports dependencies; guards repeated header inclusion; declares namespace scope; declares types or opens a type body; declares callable signatures; declares values/defaults or compile-time conditions. | source comment (unverified): // Read-only public values. A tuple's view retains its immutable payload without · [reviewed contract](#b0001) |
| [B0002 · 22–22](../../../../../../include/crown/storage/tuple_values.hpp#L22) | Callable definition: \[\[nodiscard\]\] static TupleValuesView borrow(const Row& row) noexcept | calls TupleValuesView; returns TupleValuesView(&row) · [reviewed contract](#b0002) |
| [B0003 · 23–23](../../../../../../include/crown/storage/tuple_values.hpp#L23) | Callable definition: \[\[nodiscard\]\] static TupleValuesView borrow(RowView row) noexcept | calls TupleValuesView; returns TupleValuesView(row) · [reviewed contract](#b0003) |
| [B0004 · 24–24](../../../../../../include/crown/storage/tuple_values.hpp#L24) | declares callable signatures; declares values/defaults or compile-time conditions. |  · [reviewed contract](#b0004) |
| [B0005 · 25–25](../../../../../../include/crown/storage/tuple_values.hpp#L25) | Callable definition: \[\[nodiscard\]\] bool empty() const noexcept | calls size; returns size()==0 · [reviewed contract](#b0005) |
| [B0006 · 26–30](../../../../../../include/crown/storage/tuple_values.hpp#L26) | declares callable signatures; declares values/defaults or compile-time conditions. | source comment (unverified): // Element access returns an inline scalar, not an owning string. Keep an · [reviewed contract](#b0006) |
| [B0007 · 31–31](../../../../../../include/crown/storage/tuple_values.hpp#L31) | Callable definition: \[\[nodiscard\]\] ScalarView front() const | calls at; returns at(0); source comment (unverified): // front/back use at(): empty views reject before a cell is dereferenced. · [reviewed contract](#b0007) |
| [B0008 · 32–32](../../../../../../include/crown/storage/tuple_values.hpp#L32) | Callable definition: \[\[nodiscard\]\] ScalarView back() const | calls at, size; returns at(size()-1) · [reviewed contract](#b0008) |
| [B0009 · 33–47](../../../../../../include/crown/storage/tuple_values.hpp#L33) | declares types or opens a type body; declares callable signatures; declares values/defaults or compile-time conditions. | source comment (unverified): // Borrowed adapters transfer no ownership. Tuple-derived views retain their · [reviewed contract](#b0009) |
| [B0010 · 48–48](../../../../../../include/crown/storage/tuple_values.hpp#L48) | Callable definition: explicit TupleValuesView(const Row* row) noexcept:source_(row) | calls source_ · [reviewed contract](#b0010) |
| [B0011 · 49–49](../../../../../../include/crown/storage/tuple_values.hpp#L49) | Callable definition: explicit TupleValuesView(RowView row) noexcept:source_(row) | calls source_ · [reviewed contract](#b0011) |
| [B0012 · 50–50](../../../../../../include/crown/storage/tuple_values.hpp#L50) | Callable definition: explicit TupleValuesView(std::shared_ptr&lt;const detail::TuplePayload&gt; owner) noexcept:source_(std::move(owner)) | calls source_, std::move · [reviewed contract](#b0012) |
| [B0013 · 51–54](../../../../../../include/crown/storage/tuple_values.hpp#L51) | declares callable signatures; declares values/defaults or compile-time conditions. |  · [reviewed contract](#b0013) |
| [B0014 · 55–73](../../../../../../include/crown/storage/tuple_values.hpp#L55) | Type/record definition: class TupleValuesView::const_iterator | returns values_\[position_\]; *this · [reviewed contract](#b0014) |
| [B0015 · 74–75](../../../../../../include/crown/storage/tuple_values.hpp#L74) | declares callable signatures. |  · [reviewed contract](#b0015) |
| [B0016 · 76–76](../../../../../../include/crown/storage/tuple_values.hpp#L76) | Callable definition: \[\[nodiscard\]\] inline std::uint64_t row_hash(TupleValuesView values) | calls hash; returns values.hash() · [reviewed contract](#b0016) |
| [B0017 · 77–77](../../../../../../include/crown/storage/tuple_values.hpp#L77) | Closes surrounding scope/type. | source comment (unverified): // namespace crown::storage · [reviewed contract](#b0017) |

## B0001

[Lines 1–21](../../../../../../include/crown/storage/tuple_values.hpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
class TupleValuesView {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Unify read-only legacy/compact values while preserving explicit ownership. |
| inputs / outputs | Tuple::values retains immutable payload; borrow(Row/RowView) creates a nonowning adapter; indexing returns compact scalar values. |
| invariants | Strings in extracted ScalarView do not retain any owner. Tuple-derived view ownership lasts only while a tuple/view/iterator retaining it survives; explicit borrow still requires caller storage. |
| ownership | Representation is pointer, RowView or shared immutable payload. No owning standard-row mirror or implicit Row export. |
| failure | at presents std::out_of_range; unchecked access requires valid index/storage. |
| cost | Fixed view copies/refcounts; actual hashing/comparison/export costs are representation-specific. |
| Design | [docs/query_memory.md](../../../../../query_memory.md), [docs/tuple_arenas.md](../../../../../tuple_arenas.md), [docs/scalars.md](../../../../../scalars.md) |

## B0002

[Lines 22–22](../../../../../../include/crown/storage/tuple_values.hpp#L22); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
[[nodiscard]] static TupleValuesView borrow(const Row& row) noexcept{return TupleValuesView(&row);}
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Borrow a caller-owned legacy Row without copying cells. |
| inputs / outputs | borrow(const Row&) records its address in the view representation. |
| invariants | The view/iterator does not retain an explicit borrowed Row; moving or destroying the Row can invalidate it. |
| ownership | Caller owns the Row vector, Value objects and any strings; keep them alive and stable. |
| failure | The shown inline operation is noexcept and has no throwing body or exception translation. |
| cost | Fixed-size metadata copy/read/comparison; no dynamic allocation or population traversal. |
| Design | [include/crown/storage/tuple_values.hpp](../../../../../../include/crown/storage/tuple_values.hpp), [src/storage/tuple_values.cpp](../../../../../../src/storage/tuple_values.cpp), [src/storage/layout.cpp](../../../../../../src/storage/layout.cpp), [src/storage/accounted_row.cpp](../../../../../../src/storage/accounted_row.cpp), [docs/storage.md](../../../../../storage.md), [docs/code_review.md](../../../../../code_review.md) |

## B0003

[Lines 23–23](../../../../../../include/crown/storage/tuple_values.hpp#L23); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
[[nodiscard]] static TupleValuesView borrow(RowView row) noexcept{return TupleValuesView(row);}
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Borrow compact descriptors through an existing nonowning RowView. |
| inputs / outputs | borrow(RowView) stores that view directly. |
| invariants | No ownership is acquired for the descriptor array or strings by wrapping it. |
| ownership | The original AccountedRow/caller cells and referenced string bytes must outlive every view/iterator access. |
| failure | The shown inline operation is noexcept and has no throwing body or exception translation. |
| cost | Fixed-size metadata copy/read/comparison; no dynamic allocation or population traversal. |
| Design | [include/crown/storage/tuple_values.hpp](../../../../../../include/crown/storage/tuple_values.hpp), [src/storage/tuple_values.cpp](../../../../../../src/storage/tuple_values.cpp), [src/storage/layout.cpp](../../../../../../src/storage/layout.cpp), [src/storage/accounted_row.cpp](../../../../../../src/storage/accounted_row.cpp), [docs/storage.md](../../../../../storage.md), [docs/code_review.md](../../../../../code_review.md) |

## B0004

[Lines 24–24](../../../../../../include/crown/storage/tuple_values.hpp#L24); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L24-L24:sha256:2cfe5354f5705b040c88d7bddf5c2475885e5dfab11f2dc043f629cfbed4ab69
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Source usage for this declaration span in include/crown/storage/tuple_values.hpp; the range contains the state/helper statements shown at its exact source span. |
| inputs / outputs | Compile inputs are the listed headers and namespace/type names. This span adds no result value unless a helper/type definition listed above is instantiated or called. |
| invariants | The exact import, alias, namespace and member declarations determine the local compile/link surface; stronger behavior belongs to their constructors and operations. |
| ownership | Imports, namespace aliases, forward declarations and compile guards create no object owner. Runtime ownership starts with declared object instances and their allocator/member types. |
| failure | No explicit throw/catch appears in this exact span. Includes, constructors, inline members, static initialization and callees can still fail; follow their enclosing API contracts. |
| cost | This span changes compile/link structure and type layout. Runtime initialization, allocation, exceptions and operation work follow the declared owner/callable code; no absence is inferred from declaration syntax. |
| Design | [docs/storage.md](../../../../../storage.md), [docs/scalars.md](../../../../../scalars.md), [docs/query_memory.md](../../../../../query_memory.md), [docs/code_specs/subsystem_contracts.md](../../../../subsystem_contracts.md) |

## B0005

[Lines 25–25](../../../../../../include/crown/storage/tuple_values.hpp#L25); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
[[nodiscard]] bool empty() const noexcept{return size()==0;}
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Check whether the active values representation has zero cells. |
| inputs / outputs | Returns size()==0 for default, borrowed or retaining views. |
| invariants | An empty view need not be an absent retained payload or absent allocation. |
| ownership | Reads its existing representation; ownership is unchanged. |
| failure | The shown inline operation is noexcept and has no throwing body or exception translation. |
| cost | Fixed-size metadata copy/read/comparison; no dynamic allocation or population traversal. |
| Design | [include/crown/storage/tuple_values.hpp](../../../../../../include/crown/storage/tuple_values.hpp), [src/storage/tuple_values.cpp](../../../../../../src/storage/tuple_values.cpp), [src/storage/layout.cpp](../../../../../../src/storage/layout.cpp), [src/storage/accounted_row.cpp](../../../../../../src/storage/accounted_row.cpp), [docs/storage.md](../../../../../storage.md), [docs/code_review.md](../../../../../code_review.md) |

## B0006

[Lines 26–30](../../../../../../include/crown/storage/tuple_values.hpp#L26); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
[[nodiscard]] ScalarView at(std::size_t) const;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Select public-view scalar access with explicit bounds semantics. |
| inputs / outputs | at checks position&lt;size and returns an inline ScalarView; operator\[\] omits bounds checks and needs a valid index. |
| invariants | Reading a legacy Decimal copies its bounded parts into InlineDecimal; reading a string returns a borrowed string_view. An empty/default view must never be indexed with \[\]. |
| ownership | A tuple-derived retaining view must remain alive for returned string bytes, unless another tuple/payload owner remains. Explicit borrow views still need the caller source. |
| failure | at throws std::out_of_range for invalid positions; legacy value adaptation may reject an invalid Value. Unchecked out-of-range access violates the caller precondition. |
| cost | Fixed representation dispatch and bounded scalar descriptor copy; no successful deep string copy. Failure diagnostics may allocate. |
| Design | [include/crown/storage/tuple_values.hpp](../../../../../../include/crown/storage/tuple_values.hpp), [src/storage/tuple_values.cpp](../../../../../../src/storage/tuple_values.cpp), [src/storage/layout.cpp](../../../../../../src/storage/layout.cpp), [src/storage/accounted_row.cpp](../../../../../../src/storage/accounted_row.cpp), [docs/storage.md](../../../../../storage.md), [docs/code_review.md](../../../../../code_review.md) |

## B0007

[Lines 31–31](../../../../../../include/crown/storage/tuple_values.hpp#L31); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
[[nodiscard]] ScalarView front() const{return at(0);}
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Read the first scalar through checked public-view access. |
| inputs / outputs | Calls at(0) and returns ScalarView by value. |
| invariants | Empty views reject: back's unsigned size()-1 still reaches the at() bounds check before dereference. ScalarView strings remain borrowed. |
| ownership | Returned nonstring alternatives are inline; string_view requires the active payload/borrowed-source owner to remain alive. |
| failure | at() throws std::out_of_range for empty/out-of-range input; exception diagnostics may allocate. This wrapper adds no catch. |
| cost | Fixed representation selection and cell copy, with bounded inline decimal copying; no successful deep string allocation. |
| Design | [include/crown/storage/tuple_values.hpp](../../../../../../include/crown/storage/tuple_values.hpp), [src/storage/tuple_values.cpp](../../../../../../src/storage/tuple_values.cpp), [src/storage/layout.cpp](../../../../../../src/storage/layout.cpp), [src/storage/accounted_row.cpp](../../../../../../src/storage/accounted_row.cpp), [docs/storage.md](../../../../../storage.md), [docs/code_review.md](../../../../../code_review.md) |

## B0008

[Lines 32–32](../../../../../../include/crown/storage/tuple_values.hpp#L32); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
[[nodiscard]] ScalarView back() const{return at(size()-1);}
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Read the last scalar through checked public-view access. |
| inputs / outputs | Calls at(size()-1) and returns ScalarView by value. |
| invariants | Empty views reject: back's unsigned size()-1 still reaches the at() bounds check before dereference. ScalarView strings remain borrowed. |
| ownership | Returned nonstring alternatives are inline; string_view requires the active payload/borrowed-source owner to remain alive. |
| failure | at() throws std::out_of_range for empty/out-of-range input; exception diagnostics may allocate. This wrapper adds no catch. |
| cost | Fixed representation selection and cell copy, with bounded inline decimal copying; no successful deep string allocation. |
| Design | [include/crown/storage/tuple_values.hpp](../../../../../../include/crown/storage/tuple_values.hpp), [src/storage/tuple_values.cpp](../../../../../../src/storage/tuple_values.cpp), [src/storage/layout.cpp](../../../../../../src/storage/layout.cpp), [src/storage/accounted_row.cpp](../../../../../../src/storage/accounted_row.cpp), [docs/storage.md](../../../../../storage.md), [docs/code_review.md](../../../../../code_review.md) |

## B0009

[Lines 33–47](../../../../../../include/crown/storage/tuple_values.hpp#L33); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
[[nodiscard]] std::uint64_t hash() const;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Hash the active public-values representation with its actual scalar costs. |
| inputs / outputs | Legacy rows use crown::row_hash(Row); native rows use RowView::hash; default empty views use the empty native row hash. |
| invariants | Typed tags/framing preserve value semantics; no immutable layout token is included and collisions still require equality. |
| ownership | Reads stable active backing; retaining the view preserves only tuple-derived payload ownership. |
| failure | Legacy scalar/hash failures propagate; no account or error translation is introduced. |
| cost | Visits actual row fields/string bytes. Legacy Decimal hashing formats an owning to_string result and can allocate; native InlineDecimal rendering uses fixed stack capacity. |
| Design | [include/crown/storage/tuple_values.hpp](../../../../../../include/crown/storage/tuple_values.hpp), [src/storage/tuple_values.cpp](../../../../../../src/storage/tuple_values.cpp), [src/storage/layout.cpp](../../../../../../src/storage/layout.cpp), [src/storage/accounted_row.cpp](../../../../../../src/storage/accounted_row.cpp), [docs/storage.md](../../../../../storage.md), [docs/code_review.md](../../../../../code_review.md) |

```text
[[nodiscard]] const Row* legacy_row() const noexcept;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Expose explicit borrowed representation adapters. |
| inputs / outputs | legacy_row returns a legacy Row pointer if active; native_view returns optional RowView for compact backing. Neither converts the other representation. |
| invariants | An absent adapter is not permission to treat a nonempty row as empty without checking its active representation. |
| ownership | Adapters return borrows; they do not transfer the view's payload owner. Keep a retaining tuple/view or borrowed source alive. |
| failure | The shown inline operation is noexcept and has no throwing body or exception translation. |
| cost | Fixed variant checks and pointer/view copies; no owning Row export, descriptor scan or heap allocation. |
| Design | [include/crown/storage/tuple_values.hpp](../../../../../../include/crown/storage/tuple_values.hpp), [src/storage/tuple_values.cpp](../../../../../../src/storage/tuple_values.cpp), [src/storage/layout.cpp](../../../../../../src/storage/layout.cpp), [src/storage/accounted_row.cpp](../../../../../../src/storage/accounted_row.cpp), [docs/storage.md](../../../../../storage.md), [docs/code_review.md](../../../../../code_review.md) |

## B0010

[Lines 48–48](../../../../../../include/crown/storage/tuple_values.hpp#L48); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
explicit TupleValuesView(const Row* row) noexcept:source_(row) {}
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Store a borrowed legacy row representation. |
| inputs / outputs | Private constructor puts const Row* into source_; default construction uses a null pointer. |
| invariants | Nonempty operator\[\] use requires a live pointed-to Row and a valid index; default/null means empty for checked/size operations. |
| ownership | Pointer storage retains no Row, vector or strings. |
| failure | The shown inline operation is noexcept and has no throwing body or exception translation. |
| cost | Fixed-size metadata copy/read/comparison; no dynamic allocation or population traversal. |
| Design | [include/crown/storage/tuple_values.hpp](../../../../../../include/crown/storage/tuple_values.hpp), [src/storage/tuple_values.cpp](../../../../../../src/storage/tuple_values.cpp), [src/storage/layout.cpp](../../../../../../src/storage/layout.cpp), [src/storage/accounted_row.cpp](../../../../../../src/storage/accounted_row.cpp), [docs/storage.md](../../../../../storage.md), [docs/code_review.md](../../../../../code_review.md) |

## B0011

[Lines 49–49](../../../../../../include/crown/storage/tuple_values.hpp#L49); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
explicit TupleValuesView(RowView row) noexcept:source_(row) {}
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Store a borrowed compact row representation. |
| inputs / outputs | Private constructor puts RowView into source_. |
| invariants | The RowView remains borrowed; a variant wrapper does not extend backing lifetime. |
| ownership | The original descriptor/string owner must remain stable and alive. |
| failure | The shown inline operation is noexcept and has no throwing body or exception translation. |
| cost | Fixed-size metadata copy/read/comparison; no dynamic allocation or population traversal. |
| Design | [include/crown/storage/tuple_values.hpp](../../../../../../include/crown/storage/tuple_values.hpp), [src/storage/tuple_values.cpp](../../../../../../src/storage/tuple_values.cpp), [src/storage/layout.cpp](../../../../../../src/storage/layout.cpp), [src/storage/accounted_row.cpp](../../../../../../src/storage/accounted_row.cpp), [docs/storage.md](../../../../../storage.md), [docs/code_review.md](../../../../../code_review.md) |

## B0012

[Lines 50–50](../../../../../../include/crown/storage/tuple_values.hpp#L50); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
explicit TupleValuesView(std::shared_ptr<const detail::TuplePayload> owner) noexcept:source_(std::move(owner)) {}
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Retain an immutable tuple payload for public read access. |
| inputs / outputs | Private constructor moves shared_ptr&lt;const TuplePayload&gt; into source_. |
| invariants | This is the retaining tuple-derived variant; explicit borrow() variants remain nonowning. |
| ownership | The view shares existing payload and its ordinary/native ownership; it copies no deep row or strings. |
| failure | The shown inline operation is noexcept and has no throwing body or exception translation. |
| cost | Fixed shared-handle move; final owner release can destroy the actual row payload and its owned bytes. |
| Design | [include/crown/storage/tuple_values.hpp](../../../../../../include/crown/storage/tuple_values.hpp), [src/storage/tuple_values.cpp](../../../../../../src/storage/tuple_values.cpp), [src/storage/layout.cpp](../../../../../../src/storage/layout.cpp), [src/storage/accounted_row.cpp](../../../../../../src/storage/accounted_row.cpp), [docs/storage.md](../../../../../storage.md), [docs/code_review.md](../../../../../code_review.md) |

## B0013

[Lines 51–54](../../../../../../include/crown/storage/tuple_values.hpp#L51); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L51-L54:sha256:a9cbe0a23235595affb6fdf7de34957aa3a21c5f1204e8a36f2b977c3e3c0cfe
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Source usage for this declaration span in include/crown/storage/tuple_values.hpp: closes \`block opened at line 52\`, \`class TupleValuesView\`. |
| inputs / outputs | Compile inputs are the listed headers and namespace/type names. This span adds no result value unless a helper/type definition listed above is instantiated or called. |
| invariants | Every closing brace in the span closes the paired lexical namespace/type/block shown in the source. |
| ownership | shared_ptr members retain shared state for the handle lifetime. Span/view members borrow their source; retain the source owner for the full use window. |
| failure | No explicit throw/catch appears in this exact span. Includes, constructors, inline members, static initialization and callees can still fail; follow their enclosing API contracts. |
| cost | This span changes compile/link structure and type layout. Runtime initialization, allocation, exceptions and operation work follow the declared owner/callable code; no absence is inferred from declaration syntax. |
| Design | [docs/storage.md](../../../../../storage.md), [docs/scalars.md](../../../../../scalars.md), [docs/query_memory.md](../../../../../query_memory.md), [docs/code_specs/subsystem_contracts.md](../../../../subsystem_contracts.md) |

## B0014

[Lines 55–73](../../../../../../include/crown/storage/tuple_values.hpp#L55); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
class TupleValuesView::const_iterator {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Carry a public values representation through forward iteration. |
| inputs / outputs | Dereference returns ScalarView by value; increments position; equality uses position and storage identity. |
| invariants | Only dereference within range. Extracted string_view still needs surviving source/view ownership after iterator destruction. |
| ownership | Iterator owns a copy of TupleValuesView, retaining tuple payload when present but not borrowed caller rows. |
| failure | Increment/equality are noexcept; invalid dereference is outside contract. |
| cost | Fixed iterator/view/refcount work; no per-step scalar heap or deep string copy. |
| Design | [docs/query_memory.md](../../../../../query_memory.md), [docs/tuple_arenas.md](../../../../../tuple_arenas.md), [docs/scalars.md](../../../../../scalars.md) |

## B0015

[Lines 74–75](../../../../../../include/crown/storage/tuple_values.hpp#L74); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
[[nodiscard]] Row export_row(TupleValuesView);
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Explicitly export a public values view into an owning standard Row. |
| inputs / outputs | Legacy representation deep-copies its Row directly; compact representation reserves a vector and exports each ScalarView. |
| invariants | This named export is the owning DTO boundary; no iterator/accessor implicitly materializes a Row. |
| ownership | Output vector/strings/Decimal objects own ordinary storage; the source view retains only the ownership its representation already had. |
| failure | Ordinary allocation/scalar export failures propagate before a completed Row is returned. |
| cost | O(fields + copied string/decimal bytes) with ordinary vector/scalar allocation; separate from any native operation work or requested-byte cap. |
| Design | [include/crown/storage/tuple_values.hpp](../../../../../../include/crown/storage/tuple_values.hpp), [src/storage/tuple_values.cpp](../../../../../../src/storage/tuple_values.cpp), [src/storage/layout.cpp](../../../../../../src/storage/layout.cpp), [src/storage/accounted_row.cpp](../../../../../../src/storage/accounted_row.cpp), [docs/storage.md](../../../../../storage.md), [docs/code_review.md](../../../../../code_review.md) |

## B0016

[Lines 76–76](../../../../../../include/crown/storage/tuple_values.hpp#L76); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
[[nodiscard]] inline std::uint64_t row_hash(TupleValuesView values){return values.hash();}
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Use the public values representation's exact typed row hash. |
| inputs / outputs | row_hash(TupleValuesView) calls values.hash() on the active legacy or compact representation. |
| invariants | A hash collision does not imply tuple equality; this wrapper adds no token validation. |
| ownership | The by-value view retains an existing tuple payload only when its representation already owns one; borrowed inputs remain borrowed. |
| failure | Representation-specific validation/hash failures propagate; no catch or native budget is installed. |
| cost | Visits actual fields/bytes. Native RowView hash uses inline decimal rendering; the legacy Row hash can allocate Decimal::to_string text. The inline wrapper is not a no-allocation guarantee. |
| Design | [include/crown/storage/tuple_values.hpp](../../../../../../include/crown/storage/tuple_values.hpp), [src/storage/tuple_values.cpp](../../../../../../src/storage/tuple_values.cpp), [src/storage/layout.cpp](../../../../../../src/storage/layout.cpp), [src/storage/accounted_row.cpp](../../../../../../src/storage/accounted_row.cpp), [docs/storage.md](../../../../../storage.md), [docs/code_review.md](../../../../../code_review.md) |

## B0017

[Lines 77–77](../../../../../../include/crown/storage/tuple_values.hpp#L77); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L77-L77:sha256:4f2834e597d1f01238db1fb63d4fa196a9ce6aa15226d81387eb8f8d01efb52c
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Close the \`namespace crown::storage\` scope at this exact source boundary. |
| inputs / outputs | This token introduces no callable inputs or outputs. Declarations inside \`namespace crown::storage\` define the available names, members and operations. |
| invariants | The closing brace matches the opening \`namespace crown::storage\` at its lexical source position in include/crown/storage/tuple_values.hpp; it preserves C++ namespace/type nesting. |
| ownership | The closing delimiter creates no owner. Types closed by \`namespace crown::storage\` retain the lifetimes and allocator rules of their own fields and operations. |
| failure | No failure path executes at this closing delimiter. Failure and cleanup behavior belong to enclosed functions and owning types. |
| cost | The delimiter itself performs no runtime work; the enclosed initializers, methods and destructors carry their own costs. |
| Design | [docs/storage.md](../../../../../storage.md), [docs/scalars.md](../../../../../scalars.md), [docs/query_memory.md](../../../../../query_memory.md), [docs/code_specs/subsystem_contracts.md](../../../../subsystem_contracts.md) |
