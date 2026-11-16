# `include/crown/storage/accounted_row.hpp` — block usage map

[Source](../../../../../../include/crown/storage/accounted_row.hpp) · [Source index](../../../../README.md) · [Subsystem contracts](../../../../subsystem_contracts.md) · [Reviewed primitives](../../../../primitives.md)

Represent exact typed scalars, rows, layouts and projections at compiler/public/native boundaries.

Snapshot SHA-256: `95ea07a9b4a61acc28493915a1149755f551563edd8e4fa5d8232e0d498067aa`. 129 lines partitioned into 20 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [values](../../../../subsystem_contracts.md#values). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/scalars.md](../../../../../scalars.md), [docs/storage.md](../../../../../storage.md), [docs/tuple_arenas.md](../../../../../tuple_arenas.md), [docs/verification/s05-public-tuples-2026-11-09.md](../../../../../verification/s05-public-tuples-2026-11-09.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–17](../../../../../../include/crown/storage/accounted_row.hpp#L1) | Imports dependencies; guards repeated header inclusion; declares namespace scope. | source comment (unverified): // Compact S05 payload. The public Row is a borrowed input here. · [reviewed contract](#b0001) |
| [B0002 · 18–38](../../../../../../include/crown/storage/accounted_row.hpp#L18) | Type/record definition: class InlineDecimal | returns {std::string_view(digits_.data(), digits_size_), scale_, negative_}; growth copy_of; source comment (unverified): // Decimal's entire bounded coefficient fits inline, including values too · [reviewed contract](#b0002) |
| [B0003 · 39–46](../../../../../../include/crown/storage/accounted_row.hpp#L39) | declares aliases; declares types or opens a type body; declares values/defaults or compile-time conditions. | source comment (unverified): // The alternative order deliberately matches crown::Value and ScalarType. · [reviewed contract](#b0003) |
| [B0004 · 47–65](../../../../../../include/crown/storage/accounted_row.hpp#L47) | Type/record definition: class RowView | returns {cells.data(),cells.size()}; size_; source comment (unverified): // Cells and any referenced string bytes must outlive every use of the view. · [reviewed contract](#b0004) |
| [B0005 · 66–78](../../../../../../include/crown/storage/accounted_row.hpp#L66) | declares callable signatures; declares values/defaults or compile-time conditions. | source comment (unverified): // Borrowed compatibility comparisons do not create an owning Row. · [reviewed contract](#b0005) |
| [B0006 · 79–104](../../../../../../include/crown/storage/accounted_row.hpp#L79) | declares types or opens a type body; declares callable signatures; declares values/defaults or compile-time conditions. | growth copy_of; source comment (unverified): // One real MemoryBlock contains the scalar descriptor array and every string · [reviewed contract](#b0006) |
| [B0007 · 105–107](../../../../../../include/crown/storage/accounted_row.hpp#L105) | Callable definition: \[\[nodiscard\]\] AccountedRow clone(const resource::MemoryAccount& account) const | calls copy_of, view, attribution; returns copy_of(account, view(), block_ ? block_.attribution() : resource::MemoryAttribution{}); growth clone, copy_of · [reviewed contract](#b0007) |
| [B0008 · 108–110](../../../../../../include/crown/storage/accounted_row.hpp#L108) | Callable definition: \[\[nodiscard\]\] AccountedRow clone(const resource::MemoryAccount& account, resource::MemoryAttribution attribution) const | calls copy_of, view; returns copy_of(account, view(), attribution); growth clone, copy_of · [reviewed contract](#b0008) |
| [B0009 · 111–112](../../../../../../include/crown/storage/accounted_row.hpp#L111) | declares callable signatures; declares values/defaults or compile-time conditions. |  · [reviewed contract](#b0009) |
| [B0010 · 113–113](../../../../../../include/crown/storage/accounted_row.hpp#L113) | Callable definition: \[\[nodiscard\]\] std::size_t size() const noexcept | calls ; returns size_ · [reviewed contract](#b0010) |
| [B0011 · 114–114](../../../../../../include/crown/storage/accounted_row.hpp#L114) | Callable definition: \[\[nodiscard\]\] bool empty() const noexcept | calls ; returns size_ == 0 · [reviewed contract](#b0011) |
| [B0012 · 115–115](../../../../../../include/crown/storage/accounted_row.hpp#L115) | Callable definition: \[\[nodiscard\]\] std::size_t stored_payload_bytes() const noexcept | calls size; returns block_.size() · [reviewed contract](#b0012) |
| [B0013 · 116–116](../../../../../../include/crown/storage/accounted_row.hpp#L116) | Callable definition: \[\[nodiscard\]\] resource::MemoryUsage memory_usage() const noexcept | calls usage; returns block_.usage() · [reviewed contract](#b0013) |
| [B0014 · 117–117](../../../../../../include/crown/storage/accounted_row.hpp#L117) | Callable definition: \[\[nodiscard\]\] resource::MemoryStatistics account_statistics() const | calls ; returns block_.account_statistics() · [reviewed contract](#b0014) |
| [B0015 · 118–118](../../../../../../include/crown/storage/accounted_row.hpp#L118) | Callable definition: \[\[nodiscard\]\] resource::AllocationLifetime lifetime() const | calls ; returns block_.lifetime() · [reviewed contract](#b0015) |
| [B0016 · 119–119](../../../../../../include/crown/storage/accounted_row.hpp#L119) | Callable definition: \[\[nodiscard\]\] resource::MemoryAttribution attribution() const | calls ; returns block_.attribution() · [reviewed contract](#b0016) |
| [B0017 · 120–120](../../../../../../include/crown/storage/accounted_row.hpp#L120) | Callable definition: void set_lifetime(resource::AllocationLifetime lifetime) const | calls  · [reviewed contract](#b0017) |
| [B0018 · 121–122](../../../../../../include/crown/storage/accounted_row.hpp#L121) | declares types or opens a type body. |  · [reviewed contract](#b0018) |
| [B0019 · 123–124](../../../../../../include/crown/storage/accounted_row.hpp#L123) | Callable definition: AccountedRow(resource::MemoryBlock block, std::size_t size) noexcept : block_(std::move(block)), size_(size) | calls block_, std::move, size_ · [reviewed contract](#b0019) |
| [B0020 · 125–129](../../../../../../include/crown/storage/accounted_row.hpp#L125) | declares values/defaults or compile-time conditions. | source comment (unverified): // namespace crown::storage · [reviewed contract](#b0020) |

## B0001

[Lines 1–17](../../../../../../include/crown/storage/accounted_row.hpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L1-L17:sha256:2aa6555147801a40ad90a74814003f3f221c83364154b5967e86cb1c0f040e0d
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Source usage for this declaration span in include/crown/storage/accounted_row.hpp: \`#pragma once\` makes this header idempotent within a translation unit; imports \`"crown/ir/model.hpp"\`, \`"crown/resource/memory.hpp"\`, \`&lt;array&gt;\`, \`&lt;span&gt;\`, \`&lt;string_view&gt;\`, \`&lt;utility&gt;\`, \`&lt;variant&gt;\` for compilation; opens namespace \`crown::storage\`. Source comment: Compact S05 payload. The public Row is a borrowed input here. Internal retention must own AccountedRow and keep its allocation alive for every RowView/string view that escapes. Decimal's entire bounded coefficient fits inline, including values too long for std::string's small-string buffer. No owning std::string is stored. |
| inputs / outputs | Compile inputs are the listed headers and namespace/type names. This span adds no result value unless a helper/type definition listed above is instantiated or called. |
| invariants | The source note says: Compact S05 payload. The public Row is a borrowed input here. Internal retention must own AccountedRow and keep its allocation alive for every RowView/string view that escapes. Decimal's entire bounded coefficient fits inline, including values too long for std::string's small-string buffer. No owning std::string is stored. Prose alone does not enforce the rule. |
| ownership | The source comment describes this adjacent lifetime/account boundary: Compact S05 payload. The public Row is a borrowed input here. Internal retention must own AccountedRow and keep its allocation alive for every RowView/string view that escapes. Decimal's entire bounded coefficient fits inline, including values too long for std::string's small-string buffer. No owning std::string is stored. The comment creates no owner; member types and callers determine actual retention. |
| failure | No explicit throw/catch appears in this exact span. Includes, constructors, inline members, static initialization and callees can still fail; follow their enclosing API contracts. |
| cost | The include directives affect compile dependencies. Any runtime initializer or cost in included definitions follows those definitions and is not inferred absent by this import block. |
| Design | [docs/storage.md](../../../../../storage.md), [docs/scalars.md](../../../../../scalars.md), [docs/query_memory.md](../../../../../query_memory.md), [docs/code_specs/subsystem_contracts.md](../../../../subsystem_contracts.md) |

## B0002

[Lines 18–38](../../../../../../include/crown/storage/accounted_row.hpp#L18); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
class InlineDecimal {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Store the entire admitted decimal coefficient inline for native rows. |
| inputs / outputs | parse/copy_of construct canonical data; parts borrows characters; render uses caller scratch. |
| invariants | Coefficient&lt;=38digits,scale&lt;=38, canonical positive zero. text_capacity41 includes sign/leading zero/point but no terminator. |
| ownership | Object owns38-byte inline array, not std::string; parts must not outlive this object. |
| failure | Parse/render have documented public-input/contract failures; ordinary move/copy/comparison do not allocate. |
| cost | Fixed-size value; bounded copies/render/comparison and O(input bytes) parsing. |
| Design | [docs/query_memory.md](../../../../../query_memory.md), [docs/tuple_arenas.md](../../../../../tuple_arenas.md), [docs/scalars.md](../../../../../scalars.md) |

```text
[[nodiscard]] static InlineDecimal copy_of(const Decimal&) noexcept;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Copy a valid bounded Decimal into a fully inline native scalar. |
| inputs / outputs | copy_of copies existing canonical coefficient parts; parse validates input text; parts borrows digits and render writes canonical bytes into a caller span. |
| invariants | Coefficient capacity is 38 digits and scale at most 38. parse scans arbitrary input length; text_capacity=41 accommodates every canonical admitted value. |
| ownership | InlineDecimal owns coefficient bytes, sign and scale. parts().digits borrows this object; neither string_view nor caller output span is retained. |
| failure | copy_of/parts/comparisons are noexcept for admitted values. parse throws public invalid_scalar/scalar_overflow on invalid text; render rejects too-small output with memory_contract before writing. |
| cost | Bounded inline copy/render/comparison, O(input text length) parse; successful inline operations own no std::string. Public parse errors and exception runtime may allocate. |
| Design | [include/crown/storage/accounted_row.hpp](../../../../../../include/crown/storage/accounted_row.hpp), [src/storage/accounted_row.cpp](../../../../../../src/storage/accounted_row.cpp), [src/resource/memory.cpp](../../../../../../src/resource/memory.cpp), [docs/query_memory.md](../../../../../query_memory.md), [docs/code_review.md](../../../../../code_review.md) |

## B0003

[Lines 39–46](../../../../../../include/crown/storage/accounted_row.hpp#L39); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
using ScalarView =
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Keep compact scalar tags aligned with public Value kinds. |
| inputs / outputs | Variant alternatives are int64, string_view, bool, Date and InlineDecimal in the same tag order as Value/ScalarType. |
| invariants | Only string_view borrows deep data; numeric/bool/date/decimal alternatives own inline values. Alternative order is part of typed comparison/hash adaptation. |
| ownership | A copied ScalarView owns inline alternatives but does not retain string bytes or a row owner. |
| failure | Construction/copy of these alternatives is nonthrowing; type adapters separately reject valueless/invalid public inputs. |
| cost | Fixed bounded descriptor copy; string content is not copied until an explicit row/scalar export or funded payload copy. |
| Design | [include/crown/storage/accounted_row.hpp](../../../../../../include/crown/storage/accounted_row.hpp), [src/storage/accounted_row.cpp](../../../../../../src/storage/accounted_row.cpp), [src/resource/memory.cpp](../../../../../../src/resource/memory.cpp), [docs/query_memory.md](../../../../../query_memory.md), [docs/code_review.md](../../../../../code_review.md) |

## B0004

[Lines 47–65](../../../../../../include/crown/storage/accounted_row.hpp#L47); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
class RowView {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Expose a borrowed range of compact typed descriptors. |
| inputs / outputs | borrow(span) or AccountedRow::view produce pointer/size with checked at and unchecked indexing. |
| invariants | Cells and referenced string bytes stay valid for every use; unchecked indexing requires index&lt;size. Default is empty. |
| ownership | No ownership extension; retaining RowView alone cannot retain AccountedRow. |
| failure | at uses MemoryFailure(contract); hash/noexcept comparisons require valid native invariants. |
| cost | Fixed view construction/access; hashing/comparison visit actual cells/deep bytes. |
| Design | [docs/query_memory.md](../../../../../query_memory.md), [docs/tuple_arenas.md](../../../../../tuple_arenas.md), [docs/scalars.md](../../../../../scalars.md) |

```text
[[nodiscard]] static RowView borrow(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Expose stable caller-owned compact descriptors without retention. |
| inputs / outputs | RowView::borrow(span) records pointer/count; operator\[\] is unchecked, at checks bounds, cells returns a borrowed span. |
| invariants | Caller ensures index validity for \[\] and keeps cells/string bytes alive and stable. Default RowView is empty, not a published ownership token. |
| ownership | RowView retains no owner. Copies/moves do not extend the AccountedRow or caller descriptor lifetime. |
| failure | Unchecked indexing outside the range violates its precondition; at throws fixed memory_contract. Borrow/size/cells are noexcept. |
| cost | Fixed view construction and access. Row hash/order/equality separately traverse actual fields/deep bytes with inline decimal work. |
| Design | [include/crown/storage/accounted_row.hpp](../../../../../../include/crown/storage/accounted_row.hpp), [src/storage/accounted_row.cpp](../../../../../../src/storage/accounted_row.cpp), [src/resource/memory.cpp](../../../../../../src/resource/memory.cpp), [docs/query_memory.md](../../../../../query_memory.md), [docs/code_review.md](../../../../../code_review.md) |

## B0005

[Lines 66–78](../../../../../../include/crown/storage/accounted_row.hpp#L66); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
[[nodiscard]] ScalarView borrow_scalar(const Value&);
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Adapt one public Value into the compact scalar representation. |
| inputs / outputs | borrow_scalar copies int64/bool/Date/Decimal parts inline and borrows string bytes; type_of reads the compact tag and compatibility comparisons use these descriptors. |
| invariants | No implicit owning Value/string conversion is performed; valid tag order matches Value and ScalarType. |
| ownership | Only string alternatives need the original Value/string owner to remain alive; InlineDecimal owns its bounded copied coefficient. |
| failure | Invalid/valueless public or compact values reject through the existing contract adapters; comparisons do not catch or coerce them. |
| cost | Fixed variant selection and bounded decimal copy; comparisons can scan deep string bytes. Successful borrowing creates no owning heap scalar. |
| Design | [include/crown/storage/accounted_row.hpp](../../../../../../include/crown/storage/accounted_row.hpp), [src/storage/accounted_row.cpp](../../../../../../src/storage/accounted_row.cpp), [src/resource/memory.cpp](../../../../../../src/resource/memory.cpp), [docs/query_memory.md](../../../../../query_memory.md), [docs/code_review.md](../../../../../code_review.md) |

```text
[[nodiscard]] Value export_scalar(const ScalarView&);
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Cross the explicit ordinary owning scalar/row export boundary. |
| inputs / outputs | export_scalar copies strings and renders/reparses InlineDecimal into public Decimal; export_row(RowView) reserves and appends exported Value cells. |
| invariants | Exports do not become internally retained native state or silently inherit a query-account grant. |
| ownership | Returned Value/Row owns standard-library storage independent of source compact views; caller must retain source backing until export finishes. |
| failure | Public scalar/Decimal validation or ordinary allocation failure propagates; no automatic migration/account reservation is attempted. |
| cost | Visits every exported descriptor and copied string/decimal bytes; row vector and scalar owning strings may allocate outside the native account. |
| Design | [include/crown/storage/accounted_row.hpp](../../../../../../include/crown/storage/accounted_row.hpp), [src/storage/accounted_row.cpp](../../../../../../src/storage/accounted_row.cpp), [src/resource/memory.cpp](../../../../../../src/resource/memory.cpp), [docs/query_memory.md](../../../../../query_memory.md), [docs/code_review.md](../../../../../code_review.md) |

## B0006

[Lines 79–104](../../../../../../include/crown/storage/accounted_row.hpp#L79); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
class AccountedRow {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Own one move-only native row allocation with inline decimal descriptors and deep strings. |
| inputs / outputs | Explicit copy/project/clone operations import into a chosen account; view borrows the owned descriptor range. |
| invariants | Zero cells and no block are different states: a copied empty row has a real framed block; default/moved row has none. Native retention must preserve the block for all views. |
| ownership | MemoryBlock owns descriptors and all string bytes; no implicit deep copy or unaccounted standard-row mirror. |
| failure | Construction/preflight may fail before publication; block-only attribution/lifetime/account access requires an owned block. |
| cost | One accounted row allocation per copy/project, actual deep bytes; moves/access are fixed and views add no allocation. |
| Design | [docs/query_memory.md](../../../../../query_memory.md), [docs/tuple_arenas.md](../../../../../tuple_arenas.md), [docs/scalars.md](../../../../../scalars.md) |

```text
[[nodiscard]] static AccountedRow copy_of(const resource::MemoryAccount&, const Row&,
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Copy borrowed row values into one real funded compact allocation. |
| inputs / outputs | copy_of(Row/RowView) and copy_view(TupleValuesView) compute descriptor+string sizes and build one block with rewritten internal string views. |
| invariants | Input cells/string bytes must stay unchanged through sizing and copying. No implicit native copy, standard Row mirror or auxiliary descriptor vector is retained. |
| ownership | MemoryBlock owns the ScalarView array and all copied strings; explicit account and attribution choose funding/classification. |
| failure | Checked arithmetic/account/allocator failures propagate. ScalarView trivial destruction/nothrow construction makes post-admission placement cleanup direct. |
| cost | Two descriptor passes plus deep string-byte copying and one account allocation with real header/alignment framing; logical string lengths are not charged as a second allocation. |
| Design | [include/crown/storage/accounted_row.hpp](../../../../../../include/crown/storage/accounted_row.hpp), [src/storage/accounted_row.cpp](../../../../../../src/storage/accounted_row.cpp), [src/resource/memory.cpp](../../../../../../src/resource/memory.cpp), [docs/query_memory.md](../../../../../query_memory.md), [docs/code_review.md](../../../../../code_review.md) |

```text
[[nodiscard]] static AccountedRow project(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Gather selected native fields directly into the funded output block. |
| inputs / outputs | project(account,RowView,FieldIds,attribution) sizes and copies the ordered/repeated/nullary field selection. |
| invariants | Field bounds are checked by the helper; duplicates deliberately copy selected bytes again. It does not validate source layout/domain semantics. |
| ownership | Input view and FieldIds are borrowed synchronously; returned row independently owns its descriptors/strings. |
| failure | Out-of-range selection, overflow or account/allocation failure rejects before a result escapes; no intermediate owning Row. |
| cost | Visits selected descriptors during sizing/copy and copies their actual selected string bytes, using one funded payload block. |
| Design | [include/crown/storage/accounted_row.hpp](../../../../../../include/crown/storage/accounted_row.hpp), [src/storage/accounted_row.cpp](../../../../../../src/storage/accounted_row.cpp), [src/resource/memory.cpp](../../../../../../src/resource/memory.cpp), [docs/query_memory.md](../../../../../query_memory.md), [docs/code_review.md](../../../../../code_review.md) |

```text
[[nodiscard]] static resource::MemoryUsage allocation_usage_for(const Row&);
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Preflight the exact real row allocation request without reserving memory. |
| inputs / outputs | allocation_usage_for(Row/TupleValuesView) uses the same descriptor/string payload sizing as copying and accounts for allocator framing/alignment. |
| invariants | Caller row/cells/string lengths must remain stable through subsequent copying. A returned usage value is not an allocated block or guarantee that later admission succeeds. |
| ownership | Reads caller data only; returned fixed usage metadata owns no bytes/account. |
| failure | Size/domain arithmetic failures propagate; no allocation, reservation, retry or budget change occurs in preflight. |
| cost | Linear descriptor sizing (string sizes are read rather than copied) plus fixed allocation-request arithmetic; no heap allocation. |
| Design | [include/crown/storage/accounted_row.hpp](../../../../../../include/crown/storage/accounted_row.hpp), [src/storage/accounted_row.cpp](../../../../../../src/storage/accounted_row.cpp), [src/resource/memory.cpp](../../../../../../src/resource/memory.cpp), [docs/query_memory.md](../../../../../query_memory.md), [docs/code_review.md](../../../../../code_review.md) |

## B0007

[Lines 105–107](../../../../../../include/crown/storage/accounted_row.hpp#L105); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
[[nodiscard]] AccountedRow clone(const resource::MemoryAccount& account) const {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Explicitly clone compact cells into a caller-selected account. |
| inputs / outputs | clone(account) copies view() and preserves attribution when the source block exists, otherwise uses default attribution. |
| invariants | Callers in native maintenance/rebuild/undo must select their existing query account rather than minting a replacement budget. |
| ownership | Source bytes are borrowed during the call; result owns a distinct block with copied descriptors and strings. |
| failure | Size overflow, invalid account, admission or allocator failures propagate without modifying the source. |
| cost | Preflight/copy scan all fields and string bytes and perform one funded block allocation, even when invoked through this small inline wrapper. |
| Design | [include/crown/storage/accounted_row.hpp](../../../../../../include/crown/storage/accounted_row.hpp), [src/storage/accounted_row.cpp](../../../../../../src/storage/accounted_row.cpp), [src/resource/memory.cpp](../../../../../../src/resource/memory.cpp), [docs/query_memory.md](../../../../../query_memory.md), [docs/code_review.md](../../../../../code_review.md) |

## B0008

[Lines 108–110](../../../../../../include/crown/storage/accounted_row.hpp#L108); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
[[nodiscard]] AccountedRow clone(const resource::MemoryAccount& account, resource::MemoryAttribution attribution) const {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Clone compact cells with an explicit destination allocation classification. |
| inputs / outputs | clone(account, attribution) forwards the source view and specified attribution to copy_of. |
| invariants | Classification changes which owner is reported, not which account funds the allocation or how much copying costs. |
| ownership | The returned row independently owns copied payload; it retains neither source row nor borrowed views. |
| failure | Overflow, account-cap or allocator failure propagates; source is unchanged. |
| cost | Linear descriptor sizing/copy and deep-string-byte copying plus one real accounted allocation. |
| Design | [include/crown/storage/accounted_row.hpp](../../../../../../include/crown/storage/accounted_row.hpp), [src/storage/accounted_row.cpp](../../../../../../src/storage/accounted_row.cpp), [src/resource/memory.cpp](../../../../../../src/resource/memory.cpp), [docs/query_memory.md](../../../../../query_memory.md), [docs/code_review.md](../../../../../code_review.md) |

## B0009

[Lines 111–112](../../../../../../include/crown/storage/accounted_row.hpp#L111); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
RowView view() const && = delete;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Prevent a RowView borrow from escaping an AccountedRow temporary. |
| inputs / outputs | The lvalue view() returns a RowView over the block; rvalue use is rejected. |
| invariants | The returned descriptor/string views borrow the owning AccountedRow block. |
| ownership | Keep the AccountedRow lvalue alive for the complete view use. |
| failure | Rvalue use is a compile-time error; the lvalue accessor is noexcept. |
| cost | Constructing the view allocates nothing; subsequent scans depend on cells and string bytes. |
| Design | [include/crown/storage/accounted_row.hpp §AccountedRow::view](../../../../../../include/crown/storage/accounted_row.hpp), [src/storage/accounted_row.cpp §AccountedRow::view](../../../../../../src/storage/accounted_row.cpp), [docs/query_memory.md](../../../../../query_memory.md) |

## B0010

[Lines 113–113](../../../../../../include/crown/storage/accounted_row.hpp#L113); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
[[nodiscard]] std::size_t size() const noexcept { return size_; }
  [[nodiscard]] bool empty() const noexcept { return size_ == 0; }
  [[nodiscard]] std::size_t stored_payload_bytes() const noexcept { return block_.size(); }
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Returns the stored scalar descriptor count size_. |
| inputs / outputs | Returns the stored scalar descriptor count size_. |
| invariants | Moved-from/default rows have the count maintained by their constructors/moves; size is not a byte charge. |
| ownership | The scalar/metadata result retains no row, account or runtime ownership; plain record declarations here own only their shown inline fields. |
| failure | The shown inline operation is noexcept and has no throwing body or exception translation. |
| cost | Fixed-size metadata copy/read/comparison; no dynamic allocation or population traversal. |
| Design | [include/crown/storage/accounted_row.hpp](../../../../../../include/crown/storage/accounted_row.hpp), [src/storage/accounted_row.cpp](../../../../../../src/storage/accounted_row.cpp), [src/resource/memory.cpp](../../../../../../src/resource/memory.cpp), [docs/query_memory.md](../../../../../query_memory.md), [docs/code_review.md](../../../../../code_review.md) |

## B0011

[Lines 114–114](../../../../../../include/crown/storage/accounted_row.hpp#L114); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
[[nodiscard]] bool empty() const noexcept { return size_ == 0; }
  [[nodiscard]] std::size_t stored_payload_bytes() const noexcept { return block_.size(); }
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Returns whether size_ equals zero. |
| inputs / outputs | Returns whether size_ equals zero. |
| invariants | An empty row can still own a framed zero-payload allocation; emptiness is not allocation absence. |
| ownership | The scalar/metadata result retains no row, account or runtime ownership; plain record declarations here own only their shown inline fields. |
| failure | The shown inline operation is noexcept and has no throwing body or exception translation. |
| cost | Fixed-size metadata copy/read/comparison; no dynamic allocation or population traversal. |
| Design | [include/crown/storage/accounted_row.hpp](../../../../../../include/crown/storage/accounted_row.hpp), [src/storage/accounted_row.cpp](../../../../../../src/storage/accounted_row.cpp), [src/resource/memory.cpp](../../../../../../src/resource/memory.cpp), [docs/query_memory.md](../../../../../query_memory.md), [docs/code_review.md](../../../../../code_review.md) |

## B0012

[Lines 115–115](../../../../../../include/crown/storage/accounted_row.hpp#L115); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
[[nodiscard]] std::size_t stored_payload_bytes() const noexcept { return block_.size(); }
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Returns block_.size(), the stored payload request before account framing. |
| inputs / outputs | Returns block_.size(), the stored payload request before account framing. |
| invariants | Descriptor and copied string bytes share this payload; real requested charge is reported by memory_usage(). |
| ownership | The scalar/metadata result retains no row, account or runtime ownership; plain record declarations here own only their shown inline fields. |
| failure | The shown inline operation is noexcept and has no throwing body or exception translation. |
| cost | Fixed-size metadata copy/read/comparison; no dynamic allocation or population traversal. |
| Design | [include/crown/storage/accounted_row.hpp](../../../../../../include/crown/storage/accounted_row.hpp), [src/storage/accounted_row.cpp](../../../../../../src/storage/accounted_row.cpp), [src/resource/memory.cpp](../../../../../../src/resource/memory.cpp), [docs/query_memory.md](../../../../../query_memory.md), [docs/code_review.md](../../../../../code_review.md) |

## B0013

[Lines 116–116](../../../../../../include/crown/storage/accounted_row.hpp#L116); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
[[nodiscard]] resource::MemoryUsage memory_usage() const noexcept { return block_.usage(); }
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Returns block_.usage(), zero for an empty block. |
| inputs / outputs | Returns block_.usage(), zero for an empty block. |
| invariants | This is the actual block request/framing, not whole-account usage, metadata or logical cell count. |
| ownership | The scalar/metadata result retains no row, account or runtime ownership; plain record declarations here own only their shown inline fields. |
| failure | The shown inline operation is noexcept and has no throwing body or exception translation. |
| cost | Fixed-size metadata copy/read/comparison; no dynamic allocation or population traversal. |
| Design | [include/crown/storage/accounted_row.hpp](../../../../../../include/crown/storage/accounted_row.hpp), [src/storage/accounted_row.cpp](../../../../../../src/storage/accounted_row.cpp), [src/resource/memory.cpp](../../../../../../src/resource/memory.cpp), [docs/query_memory.md](../../../../../query_memory.md), [docs/code_review.md](../../../../../code_review.md) |

## B0014

[Lines 117–117](../../../../../../include/crown/storage/accounted_row.hpp#L117); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
[[nodiscard]] resource::MemoryStatistics account_statistics() const { return block_.account_statistics(); }
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Read whole-account counters through an allocated row block. |
| inputs / outputs | Returns the owning account's MemoryStatistics, not only this row's charge. |
| invariants | No new owner, budget or row payload is created by this read. |
| ownership | The scalar/metadata result retains no row, account or runtime ownership; plain record declarations here own only their shown inline fields. |
| failure | An empty/default/moved-from MemoryBlock rejects with memory_contract; the wrapper does not catch or substitute zero. |
| cost | Fixed-size metadata copy/read/comparison; no dynamic allocation or population traversal. |
| Design | [include/crown/storage/accounted_row.hpp](../../../../../../include/crown/storage/accounted_row.hpp), [src/storage/accounted_row.cpp](../../../../../../src/storage/accounted_row.cpp), [src/resource/memory.cpp](../../../../../../src/resource/memory.cpp), [docs/query_memory.md](../../../../../query_memory.md), [docs/code_review.md](../../../../../code_review.md) |

## B0015

[Lines 118–118](../../../../../../include/crown/storage/accounted_row.hpp#L118); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
[[nodiscard]] resource::AllocationLifetime lifetime() const { return block_.lifetime(); }
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Read this allocation's lifetime classification. |
| inputs / outputs | Returns the existing MemoryBlock lifetime value. |
| invariants | No new owner, budget or row payload is created by this read. |
| ownership | The scalar/metadata result retains no row, account or runtime ownership; plain record declarations here own only their shown inline fields. |
| failure | An empty/default/moved-from MemoryBlock rejects with memory_contract; the wrapper does not catch or substitute zero. |
| cost | Fixed-size metadata copy/read/comparison; no dynamic allocation or population traversal. |
| Design | [include/crown/storage/accounted_row.hpp](../../../../../../include/crown/storage/accounted_row.hpp), [src/storage/accounted_row.cpp](../../../../../../src/storage/accounted_row.cpp), [src/resource/memory.cpp](../../../../../../src/resource/memory.cpp), [docs/query_memory.md](../../../../../query_memory.md), [docs/code_review.md](../../../../../code_review.md) |

## B0016

[Lines 119–119](../../../../../../include/crown/storage/accounted_row.hpp#L119); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
[[nodiscard]] resource::MemoryAttribution attribution() const { return block_.attribution(); }
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Read this allocation's owner attribution. |
| inputs / outputs | Returns the existing MemoryBlock attribution value. |
| invariants | No new owner, budget or row payload is created by this read. |
| ownership | The scalar/metadata result retains no row, account or runtime ownership; plain record declarations here own only their shown inline fields. |
| failure | An empty/default/moved-from MemoryBlock rejects with memory_contract; the wrapper does not catch or substitute zero. |
| cost | Fixed-size metadata copy/read/comparison; no dynamic allocation or population traversal. |
| Design | [include/crown/storage/accounted_row.hpp](../../../../../../include/crown/storage/accounted_row.hpp), [src/storage/accounted_row.cpp](../../../../../../src/storage/accounted_row.cpp), [src/resource/memory.cpp](../../../../../../src/resource/memory.cpp), [docs/query_memory.md](../../../../../query_memory.md), [docs/code_review.md](../../../../../code_review.md) |

## B0017

[Lines 120–120](../../../../../../include/crown/storage/accounted_row.hpp#L120); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void set_lifetime(resource::AllocationLifetime lifetime) const { block_.set_lifetime(lifetime); }
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Reclassify a live row allocation without moving its bytes. |
| inputs / outputs | Forwards AllocationLifetime into MemoryBlock::set_lifetime, despite const qualification of the row wrapper. |
| invariants | Account purpose/owner totals and account cap remain unchanged; lifetime subtotals move by this block's existing real usage. |
| ownership | The same row still owns the same allocation; outstanding stable views are not invalidated by classification alone. |
| failure | Invalid lifetime/empty block is a contract failure; account allocation reentrancy rejects with bad_alloc. No catch or retry is added. |
| cost | Fixed counter updates and a block-header read; no scan, allocation or grant refill. |
| Design | [include/crown/storage/accounted_row.hpp](../../../../../../include/crown/storage/accounted_row.hpp), [src/storage/accounted_row.cpp](../../../../../../src/storage/accounted_row.cpp), [src/resource/memory.cpp](../../../../../../src/resource/memory.cpp), [docs/query_memory.md](../../../../../query_memory.md), [docs/code_review.md](../../../../../code_review.md) |

## B0018

[Lines 121–122](../../../../../../include/crown/storage/accounted_row.hpp#L121); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
friend class AccountedProjection;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Allow AccountedProjection to construct the private projected AccountedRow. |
| inputs / outputs | Compile-time access is granted to one named class. |
| invariants | Friendship does not bypass the projection's runtime layout/domain validation. |
| ownership | No owner or row is created by the friend declaration. |
| failure | The declaration has no runtime failure path. |
| cost | Compile-time access only; projection allocation happens in the callable implementation. |
| Design | [include/crown/storage/accounted_row.hpp §AccountedRow](../../../../../../include/crown/storage/accounted_row.hpp), [src/storage/accounted_projection.cpp §AccountedProjection::apply](../../../../../../src/storage/accounted_projection.cpp), [src/storage/accounted_row.cpp §AccountedRow::project](../../../../../../src/storage/accounted_row.cpp) |

## B0019

[Lines 123–124](../../../../../../include/crown/storage/accounted_row.hpp#L123); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
AccountedRow(resource::MemoryBlock block, std::size_t size) noexcept
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Adopt a fully built compact row allocation. |
| inputs / outputs | Private constructor moves MemoryBlock and stores the scalar count. |
| invariants | Factory preflight/copy has already established descriptor placement, deep-byte ownership and matching count. |
| ownership | Transfers the single allocation into this move-only row; caller cells are not retained. |
| failure | The shown inline operation is noexcept and has no throwing body or exception translation. |
| cost | Fixed-size metadata copy/read/comparison; no dynamic allocation or population traversal. |
| Design | [include/crown/storage/accounted_row.hpp](../../../../../../include/crown/storage/accounted_row.hpp), [src/storage/accounted_row.cpp](../../../../../../src/storage/accounted_row.cpp), [src/resource/memory.cpp](../../../../../../src/resource/memory.cpp), [docs/query_memory.md](../../../../../query_memory.md), [docs/code_review.md](../../../../../code_review.md) |

## B0020

[Lines 125–129](../../../../../../include/crown/storage/accounted_row.hpp#L125); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
resource::MemoryBlock block_;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Store cell descriptors and copied string bytes in one funded row block. |
| inputs / outputs | copy_of/copy_view/project supply values and an account; AccountedRow stores the block and cell count. |
| invariants | Cell string_views point into the same block; no owning std::string is retained per cell. |
| ownership | MemoryBlock owns the allocation and AccountedRow releases it on move assignment/destruction. |
| failure | Copy/project sizing overflow or account admission failure rejects before a row is returned; project also rejects an out-of-range field before allocation. |
| cost | copy_of/copy_view/project allocate one account block and copy descriptors/string bytes, including the charged zero-width request; default and move construction allocate no row payload. Block release frees that allocation. |
| Design | [src/storage/accounted_row.cpp §copy_cells](../../../../../../src/storage/accounted_row.cpp), [src/storage/accounted_row.cpp §AccountedRow::copy_of](../../../../../../src/storage/accounted_row.cpp), [docs/query_memory.md](../../../../../query_memory.md), [docs/storage.md §Typed layouts and owned tuples](../../../../../storage.md) |
