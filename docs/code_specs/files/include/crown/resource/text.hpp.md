# `include/crown/resource/text.hpp` — block usage map

[Source](../../../../../../include/crown/resource/text.hpp) · [Source index](../../../../README.md) · [Subsystem contracts](../../../../subsystem_contracts.md) · [Reviewed primitives](../../../../primitives.md)

Fund native owners and nested storage from one finite requested-byte account.

Snapshot SHA-256: `a5cf10422228d4e8579d1ce26ffeec042fc928ab711871594458cca4c6811f20`. 73 lines partitioned into 23 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [memory](../../../../subsystem_contracts.md#memory). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/query_memory.md](../../../../../query_memory.md), [docs/memory_accounts.md](../../../../../memory_accounts.md), [docs/memory_reports.md](../../../../../memory_reports.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–14](../../../../../../include/crown/resource/text.hpp#L1) | Imports dependencies; guards repeated header inclusion; declares namespace scope; declares types or opens a type body; declares callable signatures; declares values/defaults or compile-time conditions. | source comment (unverified): // Immutable native text. The real character request and terminator consume the · [reviewed contract](#b0001) |
| [B0002 · 15–20](../../../../../../include/crown/resource/text.hpp#L15) | Callable definition: \[\[nodiscard\]\] static MemoryUsage allocation_usage_for(std::string_view text) | calls empty, size, max, MemoryFailure; returns {}; {1,MemoryAccount::allocation_bytes(bytes,alignof(char)),bytes} · [reviewed contract](#b0002) |
| [B0003 · 21–31](../../../../../../include/crown/resource/text.hpp#L21) | Callable definition: \[\[nodiscard\]\] static AccountedText copy_of(const MemoryAccount& account,std::string_view text, MemoryAttribution owner={},MemoryP… | calls allocation_usage_for, allocate, std::memcpy, data; returns result; growth allocate, copy_of · [reviewed contract](#b0003) |
| [B0004 · 32–32](../../../../../../include/crown/resource/text.hpp#L32) | Callable definition: AccountedText(const AccountedText& source):AccountedText(copy_of(source.account_,source.view(),source.owner_,source.purpose_)) | calls copy_of, view; growth copy_of · [reviewed contract](#b0004) |
| [B0005 · 33–34](../../../../../../include/crown/resource/text.hpp#L33) | Explanatory comments or spacing. | source comment (unverified): // Nonempty copies prepare source-account bytes before replacing this value; · [reviewed contract](#b0005) |
| [B0006 · 35–38](../../../../../../include/crown/resource/text.hpp#L35) | Callable definition: AccountedText& operator=(const AccountedText& source) | calls view; returns *this; growth copy_of; source comment (unverified): // Nonempty copies prepare source-account bytes before replacing this value; · [reviewed contract](#b0006) |
| [B0007 · 39–40](../../../../../../include/crown/resource/text.hpp#L39) | Callable definition: AccountedText(AccountedText&& source) noexcept :account_(std::move(source.account_)),block_(std::move(source.block_)),size_(std::… | calls account_, std::move, block_, size_ · [reviewed contract](#b0007) |
| [B0008 · 41–47](../../../../../../include/crown/resource/text.hpp#L41) | Callable definition: AccountedText& operator=(AccountedText&& source) noexcept | calls std::exchange; returns *this · [reviewed contract](#b0008) |
| [B0009 · 48–48](../../../../../../include/crown/resource/text.hpp#L48) | Callable definition: \[\[nodiscard\]\] std::string_view view() const noexcept | calls data; returns {data(),size_} · [reviewed contract](#b0009) |
| [B0010 · 49–49](../../../../../../include/crown/resource/text.hpp#L49) | Callable definition: \[\[nodiscard\]\] operator std::string_view() const noexcept | calls view; returns view() · [reviewed contract](#b0010) |
| [B0011 · 50–50](../../../../../../include/crown/resource/text.hpp#L50) | Callable definition: \[\[nodiscard\]\] const char* data() const noexcept | calls ; returns block_?static_cast&lt;const char*&gt;(block_.data()):@ · [reviewed contract](#b0011) |
| [B0012 · 51–51](../../../../../../include/crown/resource/text.hpp#L51) | Callable definition: \[\[nodiscard\]\] const char* c_str() const noexcept | calls data; returns data() · [reviewed contract](#b0012) |
| [B0013 · 52–52](../../../../../../include/crown/resource/text.hpp#L52) | Callable definition: \[\[nodiscard\]\] std::size_t size() const noexcept | calls ; returns size_ · [reviewed contract](#b0013) |
| [B0014 · 53–53](../../../../../../include/crown/resource/text.hpp#L53) | Callable definition: \[\[nodiscard\]\] bool empty() const noexcept | calls ; returns size_==0 · [reviewed contract](#b0014) |
| [B0015 · 54–54](../../../../../../include/crown/resource/text.hpp#L54) | Explanatory comments or spacing. | source comment (unverified): // Character-block usage only; the shared controller is counted by the account. · [reviewed contract](#b0015) |
| [B0016 · 55–55](../../../../../../include/crown/resource/text.hpp#L55) | Callable definition: \[\[nodiscard\]\] MemoryUsage memory_usage() const noexcept | calls usage; returns block_.usage(); source comment (unverified): // Character-block usage only; the shared controller is counted by the account. · [reviewed contract](#b0016) |
| [B0017 · 56–56](../../../../../../include/crown/resource/text.hpp#L56) | Callable definition: \[\[nodiscard\]\] bool operator==(const AccountedText& other) const noexcept | calls ; returns view()==other.view() · [reviewed contract](#b0017) |
| [B0018 · 57–57](../../../../../../include/crown/resource/text.hpp#L57) | Callable definition: \[\[nodiscard\]\] std::strong_ordering operator&lt;=&gt;(const AccountedText& other) const noexcept | calls ; returns view()&lt;=&gt;other.view() · [reviewed contract](#b0018) |
| [B0019 · 58–58](../../../../../../include/crown/resource/text.hpp#L58) | Callable definition: \[\[nodiscard\]\] bool operator==(std::string_view other) const noexcept | calls ; returns view()==other · [reviewed contract](#b0019) |
| [B0020 · 59–59](../../../../../../include/crown/resource/text.hpp#L59) | Callable definition: \[\[nodiscard\]\] std::strong_ordering operator&lt;=&gt;(std::string_view other) const noexcept | calls ; returns view()&lt;=&gt;other · [reviewed contract](#b0020) |
| [B0021 · 60–66](../../../../../../include/crown/resource/text.hpp#L60) | declares values/defaults or compile-time conditions. |  · [reviewed contract](#b0021) |
| [B0022 · 67–72](../../../../../../include/crown/resource/text.hpp#L67) | Type/record definition: struct AccountedTextLess | returns a.view()&lt;b.view(); a.view()&lt;b · [reviewed contract](#b0022) |
| [B0023 · 73–73](../../../../../../include/crown/resource/text.hpp#L73) | Closes surrounding scope/type. | source comment (unverified): // namespace crown::resource · [reviewed contract](#b0023) |

## B0001

[Lines 1–14](../../../../../../include/crown/resource/text.hpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
class AccountedText {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Own immutable native text bytes under a retained memory account. |
| inputs / outputs | Default text is empty; copy_of/copy create owned bytes with a terminator; moves transfer ownership; read methods return borrowed immutable character access. |
| invariants | Copies use the source account/classification, while moves preserve them. Empty text uses no character block; nonempty text stores its explicit length and trailing NUL, preserving embedded NUL bytes. |
| ownership | The object retains both an account handle and a move-only block; nested arbitrary objects are absent. Borrowed text expires when its owner is replaced or destroyed. |
| failure | Copy/admission may throw before publication; default/read/move paths are noexcept under account lifetime invariants. |
| cost | Nonempty copies allocate and copy O(text bytes); views and ownership moves are O(1). No interning table, shared mutable buffer or per-read allocation. |
| Design | [docs/query_memory.md](../../../../../query_memory.md), [include/crown/resource/memory.hpp](../../../../../../include/crown/resource/memory.hpp) |

## B0002

[Lines 15–20](../../../../../../include/crown/resource/text.hpp#L15); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
[[nodiscard]] static MemoryUsage allocation_usage_for(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Preflight the exact request needed for an owned terminated character block. |
| inputs / outputs | An input string_view returns zero usage for empty text, otherwise one allocation with payload size text.size()+1 and exact account framing. |
| invariants | The extra byte is a terminator; explicit size still describes all source bytes. The result excludes the already existing account controller. |
| ownership | The input is borrowed for its size only; no account, character copy or allocation is acquired. |
| failure | Size+1 or account-framing overflow throws fixed MemoryFailure(overflow). No byte limit is consumed by the estimate. |
| cost | O(1) arithmetic and framing calculation, independent of character contents. |
| Design | [docs/query_memory.md](../../../../../query_memory.md), [include/crown/resource/memory.hpp](../../../../../../include/crown/resource/memory.hpp) |

## B0003

[Lines 21–31](../../../../../../include/crown/resource/text.hpp#L21); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
[[nodiscard]] static AccountedText copy_of(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Prepare an independently owned terminated copy of a borrowed text range. |
| inputs / outputs | Account, string_view and optional attribution/purpose produce AccountedText whose size equals the full source byte length. |
| invariants | Nonempty text uses one account allocation, memcpy of all bytes and a trailing zero. Empty text retains supplied handle/metadata without allocating or invoking category/account validation. |
| ownership | Returned text retains the caller's existing account. The source range must stay readable during copying, then may expire. |
| failure | Overflow, account admission or upstream allocation failure propagates while the local result releases its partial ownership; no prior caller object is mutated. |
| cost | O(text bytes) copy and one framed allocation when nonempty; O(1) handle work for empty text. Controller bytes are already charged to the shared account. |
| Design | [docs/query_memory.md](../../../../../query_memory.md), [include/crown/resource/memory.hpp](../../../../../../include/crown/resource/memory.hpp) |

## B0004

[Lines 32–32](../../../../../../include/crown/resource/text.hpp#L32); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
AccountedText(const AccountedText& source):
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Deep-copy native text under the source's original allocation authority. |
| inputs / outputs | Copy construction delegates to copy_of using source account, view, attribution and purpose. |
| invariants | Characters are independent when nonempty; the account/cap remains shared. Empty/default source text can be copied without a character allocation. |
| ownership | The new object owns its own block; no mutable source buffer is shared and the source remains unchanged. |
| failure | Preflight/admission/allocation failures prevent construction and release local temporary ownership. |
| cost | O(source bytes) and one character allocation for nonempty text; both source and copy remain charged while alive. |
| Design | [docs/query_memory.md](../../../../../query_memory.md), [include/crown/resource/text.hpp](../../../../../../include/crown/resource/text.hpp) |

## B0005

[Lines 33–34](../../../../../../include/crown/resource/text.hpp#L33); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L33-L34:sha256:e80ef4415d44632461afb69a5fe2e043f592ee012fcf04c57ad151e02cc9bad9
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Usage note immediately before \`AccountedText& operator=(const AccountedText& source)\`: Nonempty copies prepare source-account bytes before replacing this value; both old and new blocks remain charged while they overlap. |
| inputs / outputs | This comment introduces no parameter, field or return value. It documents the adjacent construct beginning at include/crown/resource/text.hpp:L35; use that declaration for the actual input/output shape. |
| invariants | The source note states: Nonempty copies prepare source-account bytes before replacing this value; both old and new blocks remain charged while they overlap. It is prose guidance; the adjacent implementation is the place to check enforcement. |
| ownership | The comment itself retains nothing. It documents this neighboring ownership/account boundary: Nonempty copies prepare source-account bytes before replacing this value; both old and new blocks remain charged while they overlap. Actual lifetime is determined by the declared members and owners. |
| failure | This comment adds no branch or handler. Any failure behavior remains in the adjacent callable implementation and its callers. |
| cost | The note states a local cost boundary: Nonempty copies prepare source-account bytes before replacing this value; both old and new blocks remain charged while they overlap. Treat it as usage guidance; actual work follows the implementation and input. |
| Design | [docs/query_memory.md](../../../../../query_memory.md), [docs/memory_accounts.md](../../../../../memory_accounts.md), [docs/code_specs/primitives.md](../../../../primitives.md), [docs/code_specs/subsystem_contracts.md](../../../../subsystem_contracts.md) |

## B0006

[Lines 35–38](../../../../../../include/crown/resource/text.hpp#L35); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
AccountedText& operator=(const AccountedText& source)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Replace text by a fully prepared copy that adopts the source account and classification. |
| inputs / outputs | Self assignment is a no-op; otherwise copy_of prepares a temporary and move assignment replaces the destination. |
| invariants | Preparation precedes releasing the old block. This preserves the old value if preparation fails, and permits old/new allocation overlap under their respective accounts. |
| ownership | Destination takes the new block and source account; assignment is transferable value ownership, not destination-budget enforcement. |
| failure | A throwing preparation leaves the destination unchanged. The final ownership move is noexcept. |
| cost | O(source bytes) plus one nonempty allocation and old block release; no whole-account scan. |
| Design | [docs/query_memory.md](../../../../../query_memory.md), [include/crown/resource/text.hpp](../../../../../../include/crown/resource/text.hpp) |

## B0007

[Lines 39–40](../../../../../../include/crown/resource/text.hpp#L39); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
AccountedText(AccountedText&& source) noexcept
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Transfer a text owner without copying its character range. |
| inputs / outputs | Moves account and block, transfers scalar metadata, and exchanges the source size to zero. |
| invariants | The source becomes a valid empty text; ownership of any old character pointer now belongs to the destination. |
| ownership | The same account-funded block moves once; no new budget or payload allocation is created. |
| failure | Noexcept; no source characters are read or reconstructed. |
| cost | O(1) handle/scalar operations and no allocation. |
| Design | [docs/query_memory.md](../../../../../query_memory.md), [include/crown/resource/text.hpp](../../../../../../include/crown/resource/text.hpp) |

## B0008

[Lines 41–47](../../../../../../include/crown/resource/text.hpp#L41); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
AccountedText& operator=(AccountedText&& source) noexcept
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Release the previous text block and adopt another text owner directly. |
| inputs / outputs | A nonself assignment moves block/account, transfers owner/purpose and resets source size; self move leaves the object unchanged. |
| invariants | The old block is released before its account handle is replaced. Moved source views no longer describe source-owned storage. |
| ownership | The destination owns the transferred block and retains its original source account; old storage is deallocated through its own header. |
| failure | Noexcept under valid account/deallocation contracts. |
| cost | O(1) transfer plus O(1) framed-block/upstream release; it does not scan or copy old/new character bytes. |
| Design | [docs/query_memory.md](../../../../../query_memory.md), [include/crown/resource/text.hpp](../../../../../../include/crown/resource/text.hpp) |

## B0009

[Lines 48–48](../../../../../../include/crown/resource/text.hpp#L48); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
[[nodiscard]] std::string_view view() const noexcept
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Read the complete immutable byte range without an owning conversion. |
| inputs / outputs | Returns string_view(data(),size_), including embedded NUL bytes and an empty range for moved/default text. |
| invariants | The view uses explicit length and excludes the extra terminator; it does not extend the owner lifetime. |
| ownership | Borrowed bytes remain valid until this block is released/replaced; a move transfers the owner that keeps them alive. |
| failure | Noexcept; empty text uses static empty-string data. |
| cost | O(1) pointer/length construction and no allocation. |
| Design | [docs/query_memory.md](../../../../../query_memory.md), [include/crown/resource/text.hpp](../../../../../../include/crown/resource/text.hpp) |

## B0010

[Lines 49–49](../../../../../../include/crown/resource/text.hpp#L49); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
[[nodiscard]] operator std::string_view() const noexcept
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Support borrowed text consumers through the same complete-range view. |
| inputs / outputs | Implicit conversion returns view() with identical pointer and length. |
| invariants | Conversion does not export owning text or prolong its lifetime. |
| ownership | The caller borrows the AccountedText character block or static empty storage. |
| failure | Noexcept, including default/moved objects. |
| cost | O(1), no character copy or allocation. |
| Design | [docs/query_memory.md](../../../../../query_memory.md), [include/crown/resource/text.hpp](../../../../../../include/crown/resource/text.hpp) |

## B0011

[Lines 50–50](../../../../../../include/crown/resource/text.hpp#L50); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
[[nodiscard]] const char* data() const noexcept
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Expose the immutable character address with a valid empty fallback. |
| inputs / outputs | Returns the live block payload as const char* or a static empty string when no block exists. |
| invariants | A nonempty block contains size_ bytes followed by a NUL. Explicit length is necessary to preserve embedded NUL content. |
| ownership | The pointer borrows owned storage; it must not be freed or retained beyond the owning block. |
| failure | Noexcept; it does not require a nonempty account or block. |
| cost | O(1) block-presence and pointer access; no allocation. |
| Design | [docs/query_memory.md](../../../../../query_memory.md), [include/crown/resource/text.hpp](../../../../../../include/crown/resource/text.hpp) |

## B0012

[Lines 51–51](../../../../../../include/crown/resource/text.hpp#L51); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
[[nodiscard]] const char* c_str() const noexcept
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Offer terminated access for consumers that need a C string address. |
| inputs / outputs | Returns data(), whose range has a trailing zero or is the static empty C string. |
| invariants | Embedded NUL bytes remain legal stored text, so a C-string consumer may observe a shorter prefix than size(). |
| ownership | Borrowed immutable pointer shares data()'s owner/lifetime rules. |
| failure | Noexcept; no temporary buffer is created. |
| cost | O(1) pointer forwarding with no allocation. |
| Design | [docs/query_memory.md](../../../../../query_memory.md), [include/crown/resource/text.hpp](../../../../../../include/crown/resource/text.hpp) |

## B0013

[Lines 52–52](../../../../../../include/crown/resource/text.hpp#L52); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
[[nodiscard]] std::size_t size() const noexcept
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Read the stored full byte length without inspecting character contents. |
| inputs / outputs | Returns size_, excluding the terminating byte. |
| invariants | Default and moved-from text have size zero; embedded NUL does not change the count. |
| ownership | Inline scalar value only; no borrowed pointer is returned. |
| failure | Noexcept. |
| cost | O(1) read; no strlen, traversal or allocation. |
| Design | [docs/query_memory.md](../../../../../query_memory.md), [include/crown/resource/text.hpp](../../../../../../include/crown/resource/text.hpp) |

## B0014

[Lines 53–53](../../../../../../include/crown/resource/text.hpp#L53); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
[[nodiscard]] bool empty() const noexcept
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Test text emptiness from its explicit byte count. |
| inputs / outputs | Returns whether size_ equals zero. |
| invariants | Emptiness does not imply an unbound account: an empty copied value can still retain an existing controller. |
| ownership | No ownership or reference-count change occurs. |
| failure | Noexcept for all valid/default/moved text values. |
| cost | O(1) comparison, no content read or allocation. |
| Design | [docs/query_memory.md](../../../../../query_memory.md), [include/crown/resource/text.hpp](../../../../../../include/crown/resource/text.hpp) |

## B0015

[Lines 54–54](../../../../../../include/crown/resource/text.hpp#L54); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L54-L54:sha256:57cba54449911170f4e730525bbafade88cdbe0ecdd500580754ecee5674d8ca
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Usage note immediately before \`\[\[nodiscard\]\] MemoryUsage memory_usage() const noexcept\`: Character-block usage only; the shared controller is counted by the account. |
| inputs / outputs | This comment introduces no parameter, field or return value. It documents the adjacent construct beginning at include/crown/resource/text.hpp:L55; use that declaration for the actual input/output shape. |
| invariants | The source note states: Character-block usage only; the shared controller is counted by the account. It is prose guidance; the adjacent implementation is the place to check enforcement. |
| ownership | The comment itself retains nothing. It documents this neighboring ownership/account boundary: Character-block usage only; the shared controller is counted by the account. Actual lifetime is determined by the declared members and owners. |
| failure | This comment adds no branch or handler. Any failure behavior remains in the adjacent callable implementation and its callers. |
| cost | The prose adds no executable work. Runtime cost belongs to the adjacent operation; the note does not establish a measured or global complexity bound. |
| Design | [docs/query_memory.md](../../../../../query_memory.md), [docs/memory_accounts.md](../../../../../memory_accounts.md), [docs/code_specs/primitives.md](../../../../primitives.md), [docs/code_specs/subsystem_contracts.md](../../../../subsystem_contracts.md) |

## B0016

[Lines 55–55](../../../../../../include/crown/resource/text.hpp#L55); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
[[nodiscard]] MemoryUsage memory_usage() const noexcept
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Report the owned character block's exact current requested/payload size. |
| inputs / outputs | Returns block_.usage(), with zero for empty/default/moved text. |
| invariants | Usage includes that block's framing/terminator but excludes the shared controller and any separate object/container allocation holding this value. |
| ownership | The result is fixed scalar data; no account ownership or live block pointer escapes. |
| failure | Noexcept direct block query. |
| cost | O(1) header read; no account scan or character-size estimate. |
| Design | [docs/query_memory.md](../../../../../query_memory.md), [include/crown/resource/memory.hpp](../../../../../../include/crown/resource/memory.hpp) |

## B0017

[Lines 56–56](../../../../../../include/crown/resource/text.hpp#L56); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
[[nodiscard]] bool operator==(const AccountedText& other) const noexcept
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Compare complete native text values without copying owned bytes. |
| inputs / outputs | Returns equality of this view and another AccountedText view. |
| invariants | Equality uses byte lengths and complete contents, including embedded NUL, independently of the owners' accounts. |
| ownership | Both ranges are borrowed only during the call. |
| failure | Noexcept; no allocation or diagnostic translation. |
| cost | Length check plus O(length) worst-case comparison for equal-length ranges; no owning conversion. |
| Design | [docs/query_memory.md](../../../../../query_memory.md), [include/crown/resource/text.hpp](../../../../../../include/crown/resource/text.hpp) |

## B0018

[Lines 57–57](../../../../../../include/crown/resource/text.hpp#L57); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
[[nodiscard]] std::strong_ordering operator<=>(const AccountedText& other) const noexcept
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Order native text by its complete lexicographic byte range. |
| inputs / outputs | Returns the strong ordering of two string_views. |
| invariants | Account, classification and trailing storage terminator do not affect value ordering. |
| ownership | Borrows both immutable ranges without retaining either owner. |
| failure | Noexcept. |
| cost | O(min(lengths)) worst-case character work plus length ordering; no allocation. |
| Design | [docs/query_memory.md](../../../../../query_memory.md), [include/crown/resource/text.hpp](../../../../../../include/crown/resource/text.hpp) |

## B0019

[Lines 58–58](../../../../../../include/crown/resource/text.hpp#L58); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
[[nodiscard]] bool operator==(std::string_view other) const noexcept
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Compare native text with caller-owned borrowed bytes. |
| inputs / outputs | Returns equality of view() and the provided string_view. |
| invariants | The caller range must be readable for its full length during comparison; no terminator is required. |
| ownership | Both ranges stay borrowed, and the caller need not construct an owning native value. |
| failure | Noexcept; no account admission is involved. |
| cost | Length check plus O(length) worst-case work for equal lengths; no allocation. |
| Design | [docs/query_memory.md](../../../../../query_memory.md), [include/crown/resource/text.hpp](../../../../../../include/crown/resource/text.hpp) |

## B0020

[Lines 59–59](../../../../../../include/crown/resource/text.hpp#L59); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
[[nodiscard]] std::strong_ordering operator<=>(std::string_view other) const noexcept
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Order native text beside caller bytes through borrowed explicit-length ranges. |
| inputs / outputs | Returns string_view strong ordering against the caller range. |
| invariants | Full byte contents and lengths determine ordering, including embedded NUL; a caller C-string terminator is irrelevant. |
| ownership | The caller owns its input and this object owns its block; neither ownership is copied. |
| failure | Noexcept under valid borrowed-range lifetimes. |
| cost | O(min(lengths)) worst-case character work and no allocation. |
| Design | [docs/query_memory.md](../../../../../query_memory.md), [include/crown/resource/text.hpp](../../../../../../include/crown/resource/text.hpp) |

## B0021

[Lines 60–66](../../../../../../include/crown/resource/text.hpp#L60); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
  MemoryAccount account_;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Keep immutable text ownership and classification in one small value. |
| inputs / outputs | Account, move-only block, size, attribution and purpose represent the current text; default scalar_payload purpose is stored. |
| invariants | Nonempty text has a block with size_+1 payload; empty text uses no character block. Block destruction precedes account-member destruction because members unwind in reverse order. |
| ownership | The explicit account handle supports same-account copies; the block independently keeps the controller alive through raw release. |
| failure | Implicit teardown needs no new allocation and follows MemoryBlock/account noexcept cleanup contracts. |
| cost | Fixed object metadata; destroying text releases one block in O(1) account work, independent of byte length. |
| Design | [docs/query_memory.md](../../../../../query_memory.md), [include/crown/resource/memory.hpp](../../../../../../include/crown/resource/memory.hpp) |

## B0022

[Lines 67–72](../../../../../../include/crown/resource/text.hpp#L67); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct AccountedTextLess {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Enable ordered-container lookup by native text or a caller string_view. |
| inputs / outputs | Transparent comparator supplies native/native, native/view and view/native overloads returning lexicographic less-than. |
| invariants | All overloads use complete explicit-length views and agree on one byte ordering, so heterogeneous probes need no temporary key owner. |
| ownership | Both ranges are borrowed for one comparison; no text or controller copy is made. |
| failure | All overloads are noexcept under valid input view lifetimes. |
| cost | Each comparison visits at most the common range length; map lookup adds its own O(log keys) comparisons. No per-probe allocation. |
| Design | [docs/query_memory.md](../../../../../query_memory.md), [include/crown/resource/text.hpp](../../../../../../include/crown/resource/text.hpp) |

## B0023

[Lines 73–73](../../../../../../include/crown/resource/text.hpp#L73); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L73-L73:sha256:7567672dab57c42722d3b39b4b45d2fe8c5a88eb6ef0a643a7b5488aa659ec31
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Close the \`namespace crown::resource\` scope at this exact source boundary. |
| inputs / outputs | This token introduces no callable inputs or outputs. Declarations inside \`namespace crown::resource\` define the available names, members and operations. |
| invariants | The closing brace matches the opening \`namespace crown::resource\` at its lexical source position in include/crown/resource/text.hpp; it preserves C++ namespace/type nesting. |
| ownership | The closing delimiter creates no owner. Types closed by \`namespace crown::resource\` retain the lifetimes and allocator rules of their own fields and operations. |
| failure | No failure path executes at this closing delimiter. Failure and cleanup behavior belong to enclosed functions and owning types. |
| cost | The delimiter itself performs no runtime work; the enclosed initializers, methods and destructors carry their own costs. |
| Design | [docs/query_memory.md](../../../../../query_memory.md), [docs/memory_accounts.md](../../../../../memory_accounts.md), [docs/code_specs/primitives.md](../../../../primitives.md), [docs/code_specs/subsystem_contracts.md](../../../../subsystem_contracts.md) |
