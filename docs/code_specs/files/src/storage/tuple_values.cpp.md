# `src/storage/tuple_values.cpp` — block usage map

[Source](../../../../../src/storage/tuple_values.cpp) · [Source index](../../../README.md) · [Subsystem contracts](../../../subsystem_contracts.md) · [Reviewed primitives](../../../primitives.md)

Represent exact typed scalars, rows, layouts and projections at compiler/public/native boundaries.

Snapshot SHA-256: `72b235106d379679860072c57e6a425a61bf996b56fba77e77d723b6f6e0163d`. 64 lines partitioned into 18 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [values](../../../subsystem_contracts.md#values). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/scalars.md](../../../../scalars.md), [docs/storage.md](../../../../storage.md), [docs/tuple_arenas.md](../../../../tuple_arenas.md), [docs/verification/s05-public-tuples-2026-11-09.md](../../../../verification/s05-public-tuples-2026-11-09.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–6](../../../../../src/storage/tuple_values.cpp#L1) | Imports dependencies; declares namespace scope. |  · [reviewed contract](#b0001) |
| [B0002 · 7–12](../../../../../src/storage/tuple_values.cpp#L7) | Callable definition: const Row* TupleValuesView::legacy_row() const noexcept | calls ; returns *row; *owner?(*owner)-&gt;legacy:nullptr · [reviewed contract](#b0002) |
| [B0003 · 13–18](../../../../../src/storage/tuple_values.cpp#L13) | Callable definition: std::optional&lt;RowView&gt; TupleValuesView::native_view() const noexcept | calls ; returns *row; (*owner)-&gt;native · [reviewed contract](#b0003) |
| [B0004 · 19–22](../../../../../src/storage/tuple_values.cpp#L19) | Callable definition: std::size_t TupleValuesView::size() const noexcept | calls legacy_row, size, native_view; returns row-&gt;size(); row?row-&gt;size():0 · [reviewed contract](#b0004) |
| [B0005 · 23–26](../../../../../src/storage/tuple_values.cpp#L23) | Callable definition: ScalarView TupleValuesView::operator\[\](std::size_t position) const | calls borrow_scalar, native_view; returns borrow_scalar((*row)\[position\]); (*native_view())\[position\] · [reviewed contract](#b0005) |
| [B0006 · 27–30](../../../../../src/storage/tuple_values.cpp#L27) | Callable definition: ScalarView TupleValuesView::at(std::size_t position) const | calls size, std::out_of_range; returns (*this)\[position\] · [reviewed contract](#b0006) |
| [B0007 · 31–34](../../../../../src/storage/tuple_values.cpp#L31) | Callable definition: const void* TupleValuesView::identity() const noexcept | calls legacy_row, native_view, cells, data; returns row; row?row-&gt;cells().data():nullptr · [reviewed contract](#b0007) |
| [B0008 · 35–35](../../../../../src/storage/tuple_values.cpp#L35) | Callable definition: TupleValuesView::const_iterator TupleValuesView::begin() const noexcept | calls const_iterator; returns const_iterator(*this,0) · [reviewed contract](#b0008) |
| [B0009 · 36–36](../../../../../src/storage/tuple_values.cpp#L36) | Callable definition: TupleValuesView::const_iterator TupleValuesView::end() const noexcept | calls const_iterator, size; returns const_iterator(*this,size()) · [reviewed contract](#b0009) |
| [B0010 · 37–40](../../../../../src/storage/tuple_values.cpp#L37) | Callable definition: std::uint64_t TupleValuesView::hash() const | calls legacy_row, crown::row_hash, native_view, hash; returns crown::row_hash(*row); row?row-&gt;hash():RowView{}.hash() · [reviewed contract](#b0010) |
| [B0011 · 41–46](../../../../../src/storage/tuple_values.cpp#L41) | Callable definition: std::strong_ordering TupleValuesView::operator&lt;=&gt;(const TupleValuesView& other) const | calls size; returns order; size()&lt;=&gt;other.size(); 1 loop sites · [reviewed contract](#b0011) |
| [B0012 · 47–53](../../../../../src/storage/tuple_values.cpp#L47) | Callable definition: bool TupleValuesView::operator==(const TupleValuesView& other) const | calls ; returns false; false; 1 loop sites · [reviewed contract](#b0012) |
| [B0013 · 54–54](../../../../../src/storage/tuple_values.cpp#L54) | Callable definition: std::strong_ordering TupleValuesView::operator&lt;=&gt;(const Row& other) const | calls ; returns *this&lt;=&gt;borrow(other) · [reviewed contract](#b0013) |
| [B0014 · 55–55](../../../../../src/storage/tuple_values.cpp#L55) | Callable definition: bool TupleValuesView::operator==(const Row& other) const | calls ; returns *this==borrow(other) · [reviewed contract](#b0014) |
| [B0015 · 56–56](../../../../../src/storage/tuple_values.cpp#L56) | Callable definition: std::strong_ordering TupleValuesView::operator&lt;=&gt;(RowView other) const | calls ; returns *this&lt;=&gt;borrow(other) · [reviewed contract](#b0015) |
| [B0016 · 57–57](../../../../../src/storage/tuple_values.cpp#L57) | Callable definition: bool TupleValuesView::operator==(RowView other) const | calls ; returns *this==borrow(other) · [reviewed contract](#b0016) |
| [B0017 · 58–63](../../../../../src/storage/tuple_values.cpp#L58) | Callable definition: Row export_row(TupleValuesView values) | calls legacy_row, reserve, size, push_back; returns *row; result; growth push_back, reserve; 1 loop sites · [reviewed contract](#b0017) |
| [B0018 · 64–64](../../../../../src/storage/tuple_values.cpp#L64) | Closes surrounding scope/type. | source comment (unverified): // namespace crown::storage · [reviewed contract](#b0018) |

## B0001

[Lines 1–6](../../../../../src/storage/tuple_values.cpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L1-L6:sha256:8d5890808dda0cd572943d686b38c677994bd02fb702316d6b44907fa3842abc
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Source usage for this declaration span in src/storage/tuple_values.cpp: imports \`"crown/storage/tuple_values.hpp"\`, \`"tuple_payload.hpp"\`, \`&lt;algorithm&gt;\`, \`&lt;stdexcept&gt;\` for compilation; opens namespace \`crown::storage\`. |
| inputs / outputs | Compile inputs are the listed headers and namespace/type names. This span adds no result value unless a helper/type definition listed above is instantiated or called. |
| invariants | The exact import, alias, namespace and member declarations determine the local compile/link surface; stronger behavior belongs to their constructors and operations. |
| ownership | Imports, namespace aliases, forward declarations and compile guards create no object owner. Runtime ownership starts with declared object instances and their allocator/member types. |
| failure | No explicit throw/catch appears in this exact span. Includes, constructors, inline members, static initialization and callees can still fail; follow their enclosing API contracts. |
| cost | The include directives affect compile dependencies. Any runtime initializer or cost in included definitions follows those definitions and is not inferred absent by this import block. |
| Design | [docs/storage.md](../../../../storage.md), [docs/scalars.md](../../../../scalars.md), [docs/query_memory.md](../../../../query_memory.md), [docs/code_specs/subsystem_contracts.md](../../../subsystem_contracts.md) |

## B0002

[Lines 7–12](../../../../../src/storage/tuple_values.cpp#L7); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
const Row* TupleValuesView::legacy_row()
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Expose a legacy-row adapter only when the selected representation supplies one. |
| inputs / outputs | Borrowed legacy pointer or legacy payload owner returns Row pointer; native/empty representations return null. |
| invariants | Pointer does not own storage and must not outlive the source row or retained owning view. |
| ownership | Tuple-derived view retains its concrete payload; explicit borrow(row) does not. |
| failure | Noexcept null result denotes another representation, not a failed validation. |
| cost | O(1), no allocation. |
| Design | [docs/query_memory.md](../../../../query_memory.md), [docs/tuple_arenas.md](../../../../tuple_arenas.md), [docs/scalars.md](../../../../scalars.md) |

## B0003

[Lines 13–18](../../../../../src/storage/tuple_values.cpp#L13); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::optional<RowView> TupleValuesView::native_view()
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Expose compact cells without exporting ordinary Values. |
| inputs / outputs | Borrowed RowView or nonlegacy owning payload returns optional RowView; legacy/empty owner yields no adapter. |
| invariants | Returned view remains borrowed; explicit borrowed-source variants receive no hidden ownership. |
| ownership | Retaining a tuple-derived TupleValuesView keeps payload alive; borrowing callers separately retain their row. |
| failure | Noexcept; missing representation is an empty optional. |
| cost | Fixed variant/pointer checks, no allocation. |
| Design | [docs/query_memory.md](../../../../query_memory.md), [docs/tuple_arenas.md](../../../../tuple_arenas.md), [docs/scalars.md](../../../../scalars.md) |

## B0004

[Lines 19–22](../../../../../src/storage/tuple_values.cpp#L19); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::size_t TupleValuesView::size()
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Read arity across legacy, compact and empty public views. |
| inputs / outputs | Legacy row size, compact view size or zero for no source. |
| invariants | No row export or scalar traversal. |
| ownership | Representation adapters borrow existing state. |
| failure | Noexcept. |
| cost | O(1). |
| Design | [docs/query_memory.md](../../../../query_memory.md), [docs/tuple_arenas.md](../../../../tuple_arenas.md), [docs/scalars.md](../../../../scalars.md) |

## B0005

[Lines 23–26](../../../../../src/storage/tuple_values.cpp#L23); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
ScalarView TupleValuesView::operator[](
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Read one public cell as a compact scalar without heap export. |
| inputs / outputs | Valid position yields inline ScalarView; legacy values adapt, native descriptors copy inline. |
| invariants | Unchecked position must be&lt;size and source alive; strings in returned ScalarView still borrow source bytes. |
| ownership | Returned scalar does not retain payload ownership; caller keeps an owning tuple/view or borrowed source alive. |
| failure | Out-of-range is outside the unchecked contract; invalid legacy alternatives can raise contract failure. |
| cost | Fixed dispatch/&lt;=38-digit inline copy; no owning std::string or Row. |
| Design | [docs/query_memory.md](../../../../query_memory.md), [docs/tuple_arenas.md](../../../../tuple_arenas.md), [docs/scalars.md](../../../../scalars.md) |

## B0006

[Lines 27–30](../../../../../src/storage/tuple_values.cpp#L27); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
ScalarView TupleValuesView::at(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Read a public cell with ordinary checked-container presentation. |
| inputs / outputs | Checks position against arity, then returns compact scalar value. |
| invariants | String result remains borrowed after checked access. |
| ownership | No payload ownership is transferred to ScalarView. |
| failure | Out-of-range raises std::out_of_range; source remains unchanged. |
| cost | Fixed arity check plus scalar adaptation; successful access allocates nothing. |
| Design | [docs/query_memory.md](../../../../query_memory.md), [docs/tuple_arenas.md](../../../../tuple_arenas.md), [docs/scalars.md](../../../../scalars.md) |

## B0007

[Lines 31–34](../../../../../src/storage/tuple_values.cpp#L31); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
const void* TupleValuesView::identity()
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Identify the source sequence for iterator equality without deep comparison. |
| inputs / outputs | Legacy Row address, compact descriptor address or null identify the underlying sequence. |
| invariants | Identity is storage-based, not structural value equality or a persistent tuple ID. |
| ownership | Borrowed pointer only; view/iterator ownership retains payload only when tuple-derived. |
| failure | Noexcept. |
| cost | O(1), no row hash or allocation. |
| Design | [docs/query_memory.md](../../../../query_memory.md), [docs/tuple_arenas.md](../../../../tuple_arenas.md), [docs/scalars.md](../../../../scalars.md) |

## B0008

[Lines 35–35](../../../../../src/storage/tuple_values.cpp#L35); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
TupleValuesView::const_iterator TupleValuesView::begin()
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Create a forward iterator that carries this view representation. |
| inputs / outputs | Returns iterator at position0. |
| invariants | Iterator equality combines position and source-storage identity. |
| ownership | Copying an owning view retains its shared payload without allocating; explicit borrowed views still need caller storage. |
| failure | Noexcept; dereferencing end remains outside the iterator contract. |
| cost | Fixed representation/owner copy, no scalar/deep-byte copy. |
| Design | [docs/query_memory.md](../../../../query_memory.md), [docs/tuple_arenas.md](../../../../tuple_arenas.md), [docs/scalars.md](../../../../scalars.md) |

## B0009

[Lines 36–36](../../../../../src/storage/tuple_values.cpp#L36); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
TupleValuesView::const_iterator TupleValuesView::end()
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Create a forward iterator that carries this view representation. |
| inputs / outputs | Returns iterator at position=size. |
| invariants | Iterator equality combines position and source-storage identity. |
| ownership | Copying an owning view retains its shared payload without allocating; explicit borrowed views still need caller storage. |
| failure | Noexcept; dereferencing end remains outside the iterator contract. |
| cost | Fixed representation/owner copy, no scalar/deep-byte copy. |
| Design | [docs/query_memory.md](../../../../query_memory.md), [docs/tuple_arenas.md](../../../../tuple_arenas.md), [docs/scalars.md](../../../../scalars.md) |

## B0010

[Lines 37–40](../../../../../src/storage/tuple_values.cpp#L37); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::uint64_t TupleValuesView::hash()
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Hash public values using the representation-appropriate exact row hash. |
| inputs / outputs | Legacy rows dispatch to crown::row_hash; compact rows use RowView::hash; no source hashes as an empty row. |
| invariants | Canonical value/type framing agrees across representations. |
| ownership | Borrows stored cells; legacy decimal hashing may create ordinary formatted text. |
| failure | Legacy formatting/allocation failures propagate; compact valid hash allocates nothing. |
| cost | O(cells + string bytes + decimal rendering), with legacy Decimal formatting costs separate from inline native hashing. |
| Design | [docs/query_memory.md](../../../../query_memory.md), [docs/tuple_arenas.md](../../../../tuple_arenas.md), [docs/scalars.md](../../../../scalars.md) |

## B0011

[Lines 41–46](../../../../../src/storage/tuple_values.cpp#L41); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::strong_ordering TupleValuesView::operator<=>(const TupleValuesView& other)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Lexicographically compare any two public value representations. |
| inputs / outputs | Compare shared prefix by compact scalar values, then arity. |
| invariants | Alternative tags and canonical decimal ordering preserve exact typed order. |
| ownership | Each element adaptation borrows strings; no owning Row is constructed. |
| failure | Requires live input storage; invalid legacy Value can raise adapter failure. |
| cost | O(common prefix/deep bytes), repeated fixed representation/size access and bounded decimal copies; no success allocation. |
| Design | [docs/query_memory.md](../../../../query_memory.md), [docs/tuple_arenas.md](../../../../tuple_arenas.md), [docs/scalars.md](../../../../scalars.md) |

## B0012

[Lines 47–53](../../../../../src/storage/tuple_values.cpp#L47); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
bool TupleValuesView::operator==(const TupleValuesView& other)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Test exact public row-value equality. |
| inputs / outputs | Read each arity once, reject a mismatch without element access, then compare corresponding scalar ordering values until a mismatch or the end. |
| invariants | For valid stable row values, unequal arity implies false and equal-arity results match lexicographic equality. This value comparison does not establish layout/token identity. |
| ownership | Both views keep their existing representation ownership only. |
| failure | Unequal arities return false without adapting elements. Equal-width operands retain existing scalar/lifetime preconditions and adaptation failures; this is not an input-validation API. |
| cost | Two fixed arity reads and O(1) mismatch rejection; equal-width inputs visit actual compared fields/deep bytes without repeated arity queries. No Row export, payload copy or allocation. |
| Design | [docs/query_memory.md](../../../../query_memory.md), [docs/tuple_arenas.md](../../../../tuple_arenas.md), [docs/scalars.md](../../../../scalars.md) |

## B0013

[Lines 54–54](../../../../../src/storage/tuple_values.cpp#L54); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::strong_ordering TupleValuesView::operator<=>(const Row& other)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Compare public values to ordinary Row without an owning conversion. |
| inputs / outputs | Construct a borrowed adapter and perform typed lexicographic ordering. |
| invariants | Adapter must not outlive other; canonical type/order rules are unchanged. |
| ownership | Borrows other, retaining neither ordinary row nor native block separately. |
| failure | Invalid source lifetime/unchecked cells violate the contract; legacy adaptation can raise its fixed contract failure. |
| cost | Actual common-prefix/deep-value comparisons; wrapper creates no allocation or Row mirror. |
| Design | [docs/query_memory.md](../../../../query_memory.md), [docs/tuple_arenas.md](../../../../tuple_arenas.md), [docs/scalars.md](../../../../scalars.md) |

## B0014

[Lines 55–55](../../../../../src/storage/tuple_values.cpp#L55); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
bool TupleValuesView::operator==(const Row& other)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Compare public values to ordinary Row without an owning conversion. |
| inputs / outputs | Borrow the supplied row for this call and forward to central TupleValuesView equality, including its arity rejection. |
| invariants | For valid stable row values, unequal arity implies false and equal-arity results match lexicographic equality. This value comparison does not establish layout/token identity. |
| ownership | Borrows other, retaining neither ordinary row nor native block separately. |
| failure | Unequal arities return false without adapting elements. Equal-width operands retain existing scalar/lifetime preconditions and adaptation failures; this is not an input-validation API. |
| cost | Two fixed arity reads and O(1) mismatch rejection; equal-width inputs visit actual compared fields/deep bytes without repeated arity queries. No Row export, payload copy or allocation. |
| Design | [docs/query_memory.md](../../../../query_memory.md), [docs/tuple_arenas.md](../../../../tuple_arenas.md), [docs/scalars.md](../../../../scalars.md) |

## B0015

[Lines 56–56](../../../../../src/storage/tuple_values.cpp#L56); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::strong_ordering TupleValuesView::operator<=>(RowView other)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Compare public values to compact RowView without an owning conversion. |
| inputs / outputs | Construct a borrowed adapter and perform typed lexicographic ordering. |
| invariants | Adapter must not outlive other; canonical type/order rules are unchanged. |
| ownership | Borrows other, retaining neither ordinary row nor native block separately. |
| failure | Invalid source lifetime/unchecked cells violate the contract; legacy adaptation can raise its fixed contract failure. |
| cost | Actual common-prefix/deep-value comparisons; wrapper creates no allocation or Row mirror. |
| Design | [docs/query_memory.md](../../../../query_memory.md), [docs/tuple_arenas.md](../../../../tuple_arenas.md), [docs/scalars.md](../../../../scalars.md) |

## B0016

[Lines 57–57](../../../../../src/storage/tuple_values.cpp#L57); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
bool TupleValuesView::operator==(RowView other)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Compare public values to compact RowView without an owning conversion. |
| inputs / outputs | Borrow the supplied row for this call and forward to central TupleValuesView equality, including its arity rejection. |
| invariants | For valid stable row values, unequal arity implies false and equal-arity results match lexicographic equality. This value comparison does not establish layout/token identity. |
| ownership | Borrows other, retaining neither ordinary row nor native block separately. |
| failure | Unequal arities return false without adapting elements. Equal-width operands retain existing scalar/lifetime preconditions and adaptation failures; this is not an input-validation API. |
| cost | Two fixed arity reads and O(1) mismatch rejection; equal-width inputs visit actual compared fields/deep bytes without repeated arity queries. No Row export, payload copy or allocation. |
| Design | [docs/query_memory.md](../../../../query_memory.md), [docs/tuple_arenas.md](../../../../tuple_arenas.md), [docs/scalars.md](../../../../scalars.md) |

## B0017

[Lines 58–63](../../../../../src/storage/tuple_values.cpp#L58); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Row export_row(TupleValuesView values)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Export an owning ordinary row from either public representation. |
| inputs / outputs | Legacy case copies its Row; native case reserves and exports each scalar. |
| invariants | Result strings/Decimal coefficients are owning; no borrowed ScalarView escapes as an owning DTO. |
| ownership | Ordinary vector/string allocations are explicit caller/tool output, outside native retained representation. |
| failure | Allocation failure destroys partial output and leaves source untouched. |
| cost | O(arity + copied strings + decimal conversion), potentially allocating; not a cheap native probe. |
| Design | [docs/query_memory.md](../../../../query_memory.md), [docs/tuple_arenas.md](../../../../tuple_arenas.md), [docs/scalars.md](../../../../scalars.md) |

## B0018

[Lines 64–64](../../../../../src/storage/tuple_values.cpp#L64); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L64-L64:sha256:4f2834e597d1f01238db1fb63d4fa196a9ce6aa15226d81387eb8f8d01efb52c
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Close the \`namespace crown::storage\` scope at this exact source boundary. |
| inputs / outputs | This token introduces no callable inputs or outputs. Declarations inside \`namespace crown::storage\` define the available names, members and operations. |
| invariants | The closing brace matches the opening \`namespace crown::storage\` at its lexical source position in src/storage/tuple_values.cpp; it preserves C++ namespace/type nesting. |
| ownership | The closing delimiter creates no owner. Types closed by \`namespace crown::storage\` retain the lifetimes and allocator rules of their own fields and operations. |
| failure | No failure path executes at this closing delimiter. Failure and cleanup behavior belong to enclosed functions and owning types. |
| cost | The delimiter itself performs no runtime work; the enclosed initializers, methods and destructors carry their own costs. |
| Design | [docs/storage.md](../../../../storage.md), [docs/scalars.md](../../../../scalars.md), [docs/query_memory.md](../../../../query_memory.md), [docs/code_specs/subsystem_contracts.md](../../../subsystem_contracts.md) |
