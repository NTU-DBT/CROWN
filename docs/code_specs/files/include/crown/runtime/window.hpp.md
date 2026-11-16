# `include/crown/runtime/window.hpp` — block usage map

[Source](../../../../../../include/crown/runtime/window.hpp) · [Source index](../../../../README.md) · [Subsystem contracts](../../../../subsystem_contracts.md) · [Reviewed primitives](../../../../primitives.md)

Maintain operational event-time/FIFO membership and prepared expiration transitions.

Snapshot SHA-256: `3eed48b01b907c94d66ba217a1d2ca6aef8a38628f5cb8389f72f01ef4d9f754`. 211 lines partitioned into 29 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [window](../../../../subsystem_contracts.md#window). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/batches_windows.md](../../../../../batches_windows.md), [docs/session_lifecycle.md](../../../../../session_lifecycle.md), [docs/query_memory.md](../../../../../query_memory.md), [docs/update_patterns.md](../../../../../update_patterns.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–18](../../../../../../include/crown/runtime/window.hpp#L1) | Imports dependencies; guards repeated header inclusion; declares namespace scope; declares types or opens a type body. | source comment (unverified): // The original modes order labels. Physical modes order live full-row lifetimes, · [reviewed contract](#b0001) |
| [B0002 · 19–19](../../../../../../include/crown/runtime/window.hpp#L19) | Type/record definition: enum class WindowFifoPolicy | source comment (unverified): // The original modes order labels. Physical modes order live full-row lifetimes, · [reviewed contract](#b0002) |
| [B0003 · 20–29](../../../../../../include/crown/runtime/window.hpp#L20) | Callable definition: \[\[nodiscard\]\] constexpr const char* window_fifo_name(WindowFifoPolicy value) noexcept | calls ; returns @; @ · [reviewed contract](#b0003) |
| [B0004 · 30–41](../../../../../../include/crown/runtime/window.hpp#L30) | Type/record definition: struct WindowOptions | source comment (unverified): // Native retained payload/index descriptors and active watermark storage. · [reviewed contract](#b0004) |
| [B0005 · 42–53](../../../../../../include/crown/runtime/window.hpp#L42) | declares aliases; declares types or opens a type body; declares callable signatures; declares values/defaults or compile-time conditions. | growth copy_of; source comment (unverified): // Immutable options collection. Copies share actual original-account control · [reviewed contract](#b0005) |
| [B0006 · 54–54](../../../../../../include/crown/runtime/window.hpp#L54) | Callable definition: \[\[nodiscard\]\] bool empty() const noexcept | calls size; returns size()==0 · [reviewed contract](#b0006) |
| [B0007 · 55–55](../../../../../../include/crown/runtime/window.hpp#L55) | Callable definition: \[\[nodiscard\]\] const TableId& operator\[\](std::size_t i) const noexcept | calls ; returns data()\[i\] · [reviewed contract](#b0007) |
| [B0008 · 56–56](../../../../../../include/crown/runtime/window.hpp#L56) | Callable definition: \[\[nodiscard\]\] const_iterator begin() const noexcept | calls data, size; returns std::span&lt;const TableId&gt;(data(),size()).begin() · [reviewed contract](#b0008) |
| [B0009 · 57–57](../../../../../../include/crown/runtime/window.hpp#L57) | Callable definition: \[\[nodiscard\]\] const_iterator end() const noexcept | calls data, size; returns std::span&lt;const TableId&gt;(data(),size()).end() · [reviewed contract](#b0009) |
| [B0010 · 58–60](../../../../../../include/crown/runtime/window.hpp#L58) | Callable definition: \[\[nodiscard\]\] bool operator==(const WindowTables& other) const noexcept | calls begin, end; returns std::equal(begin(),end(),other.begin(),other.end()) · [reviewed contract](#b0010) |
| [B0011 · 61–63](../../../../../../include/crown/runtime/window.hpp#L61) | Callable definition: template&lt;class Allocator&gt; \[\[nodiscard\]\] bool operator==(const std::vector&lt;TableId,Allocator&gt;& other) const noexcept | calls begin, end; returns std::equal(begin(),end(),other.begin(),other.end()) · [reviewed contract](#b0011) |
| [B0012 · 64–65](../../../../../../include/crown/runtime/window.hpp#L64) | Callable definition: private: explicit WindowTables(std::shared_ptr&lt;const Data&gt; data) noexcept:data_(std::move(data)) | calls data_, std::move · [reviewed contract](#b0012) |
| [B0013 · 66–67](../../../../../../include/crown/runtime/window.hpp#L66) | declares values/defaults or compile-time conditions. |  · [reviewed contract](#b0013) |
| [B0014 · 68–81](../../../../../../include/crown/runtime/window.hpp#L68) | Type/record definition: struct AccountedWindowOptions | source comment (unverified): // Ordinary copies share managed IDs; explicit account imports copy capacity. · [reviewed contract](#b0014) |
| [B0015 · 82–83](../../../../../../include/crown/runtime/window.hpp#L82) | Explanatory comments or spacing. | source comment (unverified): // Canonical state is an explicit external DTO. Operational state owns compact · [reviewed contract](#b0015) |
| [B0016 · 84–90](../../../../../../include/crown/runtime/window.hpp#L84) | Type/record definition: struct WindowLabel | source comment (unverified): // Canonical state is an explicit external DTO. Operational state owns compact · [reviewed contract](#b0016) |
| [B0017 · 91–97](../../../../../../include/crown/runtime/window.hpp#L91) | Type/record definition: struct WindowCount |  · [reviewed contract](#b0017) |
| [B0018 · 98–104](../../../../../../include/crown/runtime/window.hpp#L98) | Type/record definition: struct WindowActiveCommand |  · [reviewed contract](#b0018) |
| [B0019 · 105–109](../../../../../../include/crown/runtime/window.hpp#L105) | Type/record definition: struct WindowMetrics |  · [reviewed contract](#b0019) |
| [B0020 · 110–115](../../../../../../include/crown/runtime/window.hpp#L110) | Type/record definition: struct WindowProgress |  · [reviewed contract](#b0020) |
| [B0021 · 116–126](../../../../../../include/crown/runtime/window.hpp#L116) | Type/record definition: struct WindowCanonicalState |  · [reviewed contract](#b0021) |
| [B0022 · 127–130](../../../../../../include/crown/runtime/window.hpp#L127) | Type/record definition: struct WindowStateLimits |  · [reviewed contract](#b0022) |
| [B0023 · 131–136](../../../../../../include/crown/runtime/window.hpp#L131) | Type/record definition: struct WindowCheckpointLabel |  · [reviewed contract](#b0023) |
| [B0024 · 137–142](../../../../../../include/crown/runtime/window.hpp#L137) | Type/record definition: struct WindowCheckpointCount |  · [reviewed contract](#b0024) |
| [B0025 · 143–145](../../../../../../include/crown/runtime/window.hpp#L143) | Explanatory comments or spacing. | source comment (unverified): // Native quiescent window state for the session envelope. FIFO/expiration · [reviewed contract](#b0025) |
| [B0026 · 146–159](../../../../../../include/crown/runtime/window.hpp#L146) | Type/record definition: struct WindowCheckpoint | source comment (unverified): // Native quiescent window state for the session envelope. FIFO/expiration · [reviewed contract](#b0026) |
| [B0027 · 160–163](../../../../../../include/crown/runtime/window.hpp#L160) | declares types or opens a type body. | source comment (unverified): // Window policy selects label FIFO, full-row lifetime FIFO or unrestricted order. · [reviewed contract](#b0027) |
| [B0028 · 164–185](../../../../../../include/crown/runtime/window.hpp#L164) | Type/record definition: public: class Prepared | source comment (unverified): // Owns staged rows/nodes but borrows the controller through a raw pointer. · [reviewed contract](#b0028) |
| [B0029 · 186–211](../../../../../../include/crown/runtime/window.hpp#L186) | controls preprocessing; declares types or opens a type body; declares callable signatures; declares values/defaults or compile-time conditions. | source comment (unverified): // Terminal: release expansion storage but retain committed prefix scalars. · [reviewed contract](#b0029) |

## B0001

[Lines 1–18](../../../../../../include/crown/runtime/window.hpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
#pragma once
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Expose operational full-row set windows and explicit state views. |
| inputs / outputs | Includes typed input views, accounted ownership and native image vector support; forwards program Catalog and image access. |
| invariants | Label FIFO is an operational policy; duplicate row labels do not establish physical-row lifetime FIFO or new aggregate/W06 behavior. |
| ownership | No controller/storage allocated by inclusion. |
| failure | Compile-time dependency boundary only. |
| cost | No runtime action at inclusion. |
| Design | [include/crown/runtime/window.hpp](../../../../../../include/crown/runtime/window.hpp), [src/runtime/window.cpp](../../../../../../src/runtime/window.cpp), [docs/batches_windows.md](../../../../../batches_windows.md), [docs/code_review.md](../../../../../code_review.md) |

## B0002

[Lines 19–19](../../../../../../include/crown/runtime/window.hpp#L19); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L19-L19:sha256:ef9f1ca262e43898226867c19904f9d81b17b6a57043e4dfe9b26b5ee502910b
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Choose legacy label order, physical full-row lifetime order or unrestricted baseline window behavior. |
| inputs / outputs | Stable values 0/1 label global/per-relation, 2/3 physical global/per-relation, and appended 4 unrestricted. |
| invariants | Unrestricted removes baseline FIFO ordering only; a Session declaration can still enforce insertion-only and explicit joint scopes. Arbitrary enum casts require factory validation. |
| ownership | Caller owns inline numeric/tag fields; this record retains no backing runtime, rows, strings or allocation grant. |
| failure | The declaration does not validate public fields or translate failure. Actual factories/consumers perform the stated checks. |
| cost | Constant-size enum/tag, no allocation, scan or clock. Arbitrary enum casts are not admitted automatically. |
| Design | [include/crown/runtime/window.hpp](../../../../../../include/crown/runtime/window.hpp), [src/runtime/window.cpp](../../../../../../src/runtime/window.cpp), [docs/batches_windows.md](../../../../../batches_windows.md), [docs/code_review.md](../../../../../code_review.md), [docs/update_patterns.md](../../../../../update_patterns.md) |

## B0003

[Lines 20–29](../../../../../../include/crown/runtime/window.hpp#L20); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L20-L29:sha256:fe6ec2863c3afd61fc083787ecb24224b33e9075560efa5be01db0b65b944d5f
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Name the five admitted window policies for diagnostic export. |
| inputs / outputs | Return exact names for enum values 0 through 4, including unrestricted; invalid values return unknown. |
| invariants | Names distinguish label order from physical full-row lifetime order. This formatter grants no admission, monitored-history or theorem authority; controller/image consumers validate the actual enum. |
| ownership | Borrows one scalar and returns static-lifetime literal storage. Callers neither own nor free that text. |
| failure | The function is noexcept and does not reject an invalid DTO value; it returns unknown. Actual window factories and image codecs reject unsupported values. |
| cost | One fixed enum dispatch; no allocation, retained owner, scan, clock or native step. |
| Design | [include/crown/runtime/window.hpp](../../../../../../include/crown/runtime/window.hpp), [docs/update_patterns.md](../../../../../update_patterns.md), [docs/batches_windows.md](../../../../../batches_windows.md) |

## B0004

[Lines 30–41](../../../../../../include/crown/runtime/window.hpp#L30); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct WindowOptions {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Own caller window admission options. |
| inputs / outputs | ordinary managed_tables vector, positive width, FIFO tag, max labels, retained payload and abstract command-work limits. |
| invariants | Controller validates nonempty/distinct actual catalog managed IDs and positive settings. Retained byte model excludes actual links/framing/preparation; command work excludes tree/scalar-byte/allocation CPU costs. |
| ownership | Owns ordinary caller-allocator rows/strings/vectors/set nodes described above. Copies deep-copy those members; it is neither a cheap shared handle nor a native owner capability. |
| failure | Owning construction/copy can allocate and throw. Ordinary aggregate/memberwise assignment has no special whole-record publication guarantee; no catch/fallback is added. |
| cost | Copy O(managed table count) ordinary vector allocation; fixed scalar fields. Release one trivial-ID vector buffer, no controller retained. |
| Design | [include/crown/runtime/window.hpp](../../../../../../include/crown/runtime/window.hpp), [src/runtime/window.cpp](../../../../../../src/runtime/window.cpp), [docs/batches_windows.md](../../../../../batches_windows.md), [docs/code_review.md](../../../../../code_review.md) |

## B0005

[Lines 42–53](../../../../../../include/crown/runtime/window.hpp#L42); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
class WindowTables {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Share immutable native managed-table option storage. |
| inputs / outputs | Private shared Data owns actual-account TableId vector with retained capacity; copy_of overloads admit copies, scalar/span-like methods borrow. |
| invariants | Default is empty. Ordinary handle copy shares payload; standard implicit move may empty source, unlike explicit copy-like workload/Report handles. |
| ownership | Shared_ptr retains actual funded control/vector/account only, not controller/session; borrowed elements/iterators do not retain Data. |
| failure | copy_of can throw before publication; reads on default/moved empty return size/capacity0/data null, unchecked indexing still requires bounds. |
| cost | Copy handle O(1); explicit copy_of O(N) allocation/copy with requested capacity; final release frees trivial ID buffer/control/account. |
| Design | [include/crown/runtime/window.hpp](../../../../../../include/crown/runtime/window.hpp), [src/runtime/window.cpp](../../../../../../src/runtime/window.cpp), [docs/batches_windows.md](../../../../../batches_windows.md), [docs/code_review.md](../../../../../code_review.md) |

```text
WindowTables() noexcept=default;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Construct empty native managed-table options. |
| inputs / outputs | Default shared_ptr empty. |
| invariants | No allowance or native table identity admitted. |
| ownership | Owns empty handle only. |
| failure | noexcept for a live readable object; borrowing does not validate lifetime or extend it. |
| cost | O(1), no allocation. |
| Design | [include/crown/runtime/window.hpp](../../../../../../include/crown/runtime/window.hpp), [src/runtime/window.cpp](../../../../../../src/runtime/window.cpp), [docs/batches_windows.md](../../../../../batches_windows.md), [docs/code_review.md](../../../../../code_review.md) |

```text
[[nodiscard]] static WindowTables copy_of(const resource::MemoryAccount&,const std::vector<TableId>&);
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Copy managed-table IDs from ordinary vector, preserving source capacity. |
| inputs / outputs | Existing account and source IDs return WindowTables; nonempty explicit capacity must be &gt;=size. Empty source returns default empty before capacity check. |
| invariants | Copies exact order/capacity request; does not validate catalog membership or duplicates. Controller performs admission separately. |
| ownership | Funds actual control/vector on supplied account, session:1 immutable_metadata; source borrowed only during copy. |
| failure | Nonempty capacity&lt;size throws ImageFailure(corrupt); native allocation/account failure unwinds unpublished Data. |
| cost | O(N) ID initialization/copy and capacity allocation; empty O(1). Existing source and new capacity coexist. |
| Design | [include/crown/runtime/window.hpp](../../../../../../include/crown/runtime/window.hpp), [src/runtime/window.cpp](../../../../../../src/runtime/window.cpp), [docs/batches_windows.md](../../../../../batches_windows.md), [docs/code_review.md](../../../../../code_review.md) |

```text
[[nodiscard]] static WindowTables copy_of(const resource::MemoryAccount&,std::span<const TableId>,std::size_t capacity);
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Copy managed-table IDs from borrowed span plus explicit capacity. |
| inputs / outputs | Existing account and source IDs return WindowTables; nonempty explicit capacity must be &gt;=size. Empty source returns default empty before capacity check. |
| invariants | Copies exact order/capacity request; does not validate catalog membership or duplicates. Controller performs admission separately. |
| ownership | Funds actual control/vector on supplied account, session:1 immutable_metadata; source borrowed only during copy. |
| failure | Nonempty capacity&lt;size throws ImageFailure(corrupt); native allocation/account failure unwinds unpublished Data. |
| cost | O(N) ID initialization/copy and capacity allocation; empty O(1). Existing source and new capacity coexist. |
| Design | [include/crown/runtime/window.hpp](../../../../../../include/crown/runtime/window.hpp), [src/runtime/window.cpp](../../../../../../src/runtime/window.cpp), [docs/batches_windows.md](../../../../../batches_windows.md), [docs/code_review.md](../../../../../code_review.md) |

```text
[[nodiscard]] std::size_t size() const noexcept;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Read managed-table size. |
| inputs / outputs | Returns number of IDs. |
| invariants | No catalog validation performed. |
| ownership | Pointer, if returned, borrows Data; retain this or another sharing handle. |
| failure | noexcept for a live readable object; borrowing does not validate lifetime or extend it. |
| cost | O(1) fixed member/view lookup; no allocation or clock. |
| Design | [include/crown/runtime/window.hpp](../../../../../../include/crown/runtime/window.hpp), [src/runtime/window.cpp](../../../../../../src/runtime/window.cpp), [docs/batches_windows.md](../../../../../batches_windows.md), [docs/code_review.md](../../../../../code_review.md) |

```text
[[nodiscard]] std::size_t capacity() const noexcept;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Read managed-table capacity. |
| inputs / outputs | Returns retained actual vector capacity. |
| invariants | No catalog validation performed. |
| ownership | Pointer, if returned, borrows Data; retain this or another sharing handle. |
| failure | noexcept for a live readable object; borrowing does not validate lifetime or extend it. |
| cost | O(1) fixed member/view lookup; no allocation or clock. |
| Design | [include/crown/runtime/window.hpp](../../../../../../include/crown/runtime/window.hpp), [src/runtime/window.cpp](../../../../../../src/runtime/window.cpp), [docs/batches_windows.md](../../../../../batches_windows.md), [docs/code_review.md](../../../../../code_review.md) |

```text
[[nodiscard]] const TableId* data() const noexcept;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Read managed-table data pointer. |
| inputs / outputs | Returns const TableId* or nullptr for empty. |
| invariants | No catalog validation performed. |
| ownership | Pointer, if returned, borrows Data; retain this or another sharing handle. |
| failure | noexcept for a live readable object; borrowing does not validate lifetime or extend it. |
| cost | O(1) fixed member/view lookup; no allocation or clock. |
| Design | [include/crown/runtime/window.hpp](../../../../../../include/crown/runtime/window.hpp), [src/runtime/window.cpp](../../../../../../src/runtime/window.cpp), [docs/batches_windows.md](../../../../../batches_windows.md), [docs/code_review.md](../../../../../code_review.md) |

## B0006

[Lines 54–54](../../../../../../include/crown/runtime/window.hpp#L54); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
[[nodiscard]] bool empty() const noexcept {return size()==0;}
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Test managed-table list emptiness. |
| inputs / outputs | Returns size()==0. |
| invariants | Empty handle is valid for reading but invalid Controller options. |
| ownership | Returns independent boolean. |
| failure | noexcept for a live readable object; borrowing does not validate lifetime or extend it. |
| cost | O(1) fixed member/view lookup; no allocation or clock. |
| Design | [include/crown/runtime/window.hpp](../../../../../../include/crown/runtime/window.hpp), [src/runtime/window.cpp](../../../../../../src/runtime/window.cpp), [docs/batches_windows.md](../../../../../batches_windows.md), [docs/code_review.md](../../../../../code_review.md) |

## B0007

[Lines 55–55](../../../../../../include/crown/runtime/window.hpp#L55); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
[[nodiscard]] const TableId& operator[](std::size_t i) const noexcept {return data()[i];}
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Borrow one managed-table ID. |
| inputs / outputs | Returns data()\[i\]. |
| invariants | Requires i&lt;size; deliberately no extra bounds/error layer. |
| ownership | Reference borrows retained WindowTables Data. |
| failure | noexcept for a live readable object; borrowing does not validate lifetime or extend it. |
| cost | O(1) fixed member/view lookup; no allocation or clock. |
| Design | [include/crown/runtime/window.hpp](../../../../../../include/crown/runtime/window.hpp), [src/runtime/window.cpp](../../../../../../src/runtime/window.cpp), [docs/batches_windows.md](../../../../../batches_windows.md), [docs/code_review.md](../../../../../code_review.md) |

## B0008

[Lines 56–56](../../../../../../include/crown/runtime/window.hpp#L56); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
[[nodiscard]] const_iterator begin() const noexcept {return std::span<const TableId>(data(),size()).begin();}
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Borrow begin iterator over managed table IDs. |
| inputs / outputs | Returns const iterator from span(data(),size()). |
| invariants | Empty iteration valid; iterators do not own backing. |
| ownership | Retain a WindowTables handle until iterator use ends. |
| failure | noexcept for a live readable object; borrowing does not validate lifetime or extend it. |
| cost | O(1) fixed member/view lookup; no allocation or clock. |
| Design | [include/crown/runtime/window.hpp](../../../../../../include/crown/runtime/window.hpp), [src/runtime/window.cpp](../../../../../../src/runtime/window.cpp), [docs/batches_windows.md](../../../../../batches_windows.md), [docs/code_review.md](../../../../../code_review.md) |

## B0009

[Lines 57–57](../../../../../../include/crown/runtime/window.hpp#L57); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
[[nodiscard]] const_iterator end() const noexcept {return std::span<const TableId>(data(),size()).end();}
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Borrow end iterator over managed table IDs. |
| inputs / outputs | Returns const iterator from span(data(),size()). |
| invariants | Empty iteration valid; iterators do not own backing. |
| ownership | Retain a WindowTables handle until iterator use ends. |
| failure | noexcept for a live readable object; borrowing does not validate lifetime or extend it. |
| cost | O(1) fixed member/view lookup; no allocation or clock. |
| Design | [include/crown/runtime/window.hpp](../../../../../../include/crown/runtime/window.hpp), [src/runtime/window.cpp](../../../../../../src/runtime/window.cpp), [docs/batches_windows.md](../../../../../batches_windows.md), [docs/code_review.md](../../../../../code_review.md) |

## B0010

[Lines 58–60](../../../../../../include/crown/runtime/window.hpp#L58); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
[[nodiscard]] bool operator==(const WindowTables& other) const noexcept {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Compare managed table IDs against WindowTables. |
| inputs / outputs | std::equal on complete begin/end ranges. |
| invariants | Compares ordered values/length, not account/catalog/source authority or capacity. |
| ownership | Reads both ranges synchronously, retains neither. |
| failure | noexcept for a live readable object; borrowing does not validate lifetime or extend it. |
| cost | O(compared IDs), no allocation/clock. |
| Design | [include/crown/runtime/window.hpp](../../../../../../include/crown/runtime/window.hpp), [src/runtime/window.cpp](../../../../../../src/runtime/window.cpp), [docs/batches_windows.md](../../../../../batches_windows.md), [docs/code_review.md](../../../../../code_review.md) |

## B0011

[Lines 61–63](../../../../../../include/crown/runtime/window.hpp#L61); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
template<class Allocator> [[nodiscard]] bool operator==(const std::vector<TableId,Allocator>& other) const noexcept {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Compare managed table IDs against allocator-parameterized std::vector&lt;TableId&gt;. |
| inputs / outputs | std::equal on complete begin/end ranges. |
| invariants | Compares ordered values/length, not account/catalog/source authority or capacity. |
| ownership | Reads both ranges synchronously, retains neither. |
| failure | noexcept for a live readable object; borrowing does not validate lifetime or extend it. |
| cost | O(compared IDs), no allocation/clock. |
| Design | [include/crown/runtime/window.hpp](../../../../../../include/crown/runtime/window.hpp), [src/runtime/window.cpp](../../../../../../src/runtime/window.cpp), [docs/batches_windows.md](../../../../../batches_windows.md), [docs/code_review.md](../../../../../code_review.md) |

## B0012

[Lines 64–65](../../../../../../include/crown/runtime/window.hpp#L64); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
explicit WindowTables(std::shared_ptr<const Data> data) noexcept:data_(std::move(data)) {}
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Adopt complete immutable managed-table Data. |
| inputs / outputs | Private copy_of construction moves shared_ptr&lt;const Data&gt;. |
| invariants | Nonempty factories prepared full vector first. |
| ownership | Owns actual immutable control/vector only. |
| failure | noexcept for a live readable object; borrowing does not validate lifetime or extend it. |
| cost | O(1) pointer transfer. |
| Design | [include/crown/runtime/window.hpp](../../../../../../include/crown/runtime/window.hpp), [src/runtime/window.cpp](../../../../../../src/runtime/window.cpp), [docs/batches_windows.md](../../../../../batches_windows.md), [docs/code_review.md](../../../../../code_review.md) |

## B0013

[Lines 66–67](../../../../../../include/crown/runtime/window.hpp#L66); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::shared_ptr<const Data> data_;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Retain managed-table backing owner. |
| inputs / outputs | shared_ptr&lt;const Data&gt; backs WindowTables. |
| invariants | Views do not themselves retain owner; copies share it after controller closes. |
| ownership | Last release frees actual vector/control and allocator account. |
| failure | No rescue allocation or validation on destruction. |
| cost | Fixed refcount work; final trivial-ID buffer/control deallocation. |
| Design | [include/crown/runtime/window.hpp](../../../../../../include/crown/runtime/window.hpp), [src/runtime/window.cpp](../../../../../../src/runtime/window.cpp), [docs/batches_windows.md](../../../../../batches_windows.md), [docs/code_review.md](../../../../../code_review.md) |

## B0014

[Lines 68–81](../../../../../../include/crown/runtime/window.hpp#L68); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct AccountedWindowOptions {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Retain native window settings and immutable managed-table owner. |
| inputs / outputs | WindowTables and fixed width/FIFO/label/byte/work limits; two explicit account-aware import constructors. |
| invariants | Ordinary copies share actual table list. Explicit account imports clone retained ID capacity; options carrier does not independently validate controller policy. |
| ownership | Managed-table handle retains actual owner/account, other fields inline. No runtime or row storage retained. |
| failure | Explicit imports can allocate/throw. Ordinary handle copies are nonallocating; last list release frees its actual storage. |
| cost | Ordinary copy O(1) handle+scalars; explicit imports O(N) plus capacity allocation. |
| Design | [include/crown/runtime/window.hpp](../../../../../../include/crown/runtime/window.hpp), [src/runtime/window.cpp](../../../../../../src/runtime/window.cpp), [docs/batches_windows.md](../../../../../batches_windows.md), [docs/code_review.md](../../../../../code_review.md) |

```text
AccountedWindowOptions(const resource::MemoryAccount&,const WindowOptions&);
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Import native window options from caller WindowOptions. |
| inputs / outputs | Account plus settings clone managed IDs/capacity into that account; copy fixed limits. |
| invariants | Explicit receiving-account constructor differs from ordinary shared-handle copy; controller later validates values/catalog. |
| ownership | Owns new WindowTables control/capacity on receiver; input not retained except existing independent handles. |
| failure | Allocation/capacity failures unwind new options, old intact. |
| cost | O(N) ID copy plus actual retained capacity/control requests. |
| Design | [include/crown/runtime/window.hpp](../../../../../../include/crown/runtime/window.hpp), [src/runtime/window.cpp](../../../../../../src/runtime/window.cpp), [docs/batches_windows.md](../../../../../batches_windows.md), [docs/code_review.md](../../../../../code_review.md) |

```text
AccountedWindowOptions(const resource::MemoryAccount&,const AccountedWindowOptions&);
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Import native window options from another AccountedWindowOptions. |
| inputs / outputs | Account plus settings clone managed IDs/capacity into that account; copy fixed limits. |
| invariants | Explicit receiving-account constructor differs from ordinary shared-handle copy; controller later validates values/catalog. |
| ownership | Owns new WindowTables control/capacity on receiver; input not retained except existing independent handles. |
| failure | Allocation/capacity failures unwind new options, old intact. |
| cost | O(N) ID copy plus actual retained capacity/control requests. |
| Design | [include/crown/runtime/window.hpp](../../../../../../include/crown/runtime/window.hpp), [src/runtime/window.cpp](../../../../../../src/runtime/window.cpp), [docs/batches_windows.md](../../../../../batches_windows.md), [docs/code_review.md](../../../../../code_review.md) |

```text
AccountedWindowOptions()=default;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Allow private empty options only for image materialization. |
| inputs / outputs | Private default constructor, friend SessionImageAccess. |
| invariants | Not a public validated Controller configuration factory. |
| ownership | Empty table handle and inline fields await validated decoding. |
| failure | Default scalar initialization is not admission; materializer must fill fields before use. |
| cost | Fixed empty construction; no ID allocation. |
| Design | [include/crown/runtime/window.hpp](../../../../../../include/crown/runtime/window.hpp), [src/runtime/window.cpp](../../../../../../src/runtime/window.cpp), [docs/batches_windows.md](../../../../../batches_windows.md), [docs/code_review.md](../../../../../code_review.md) |

## B0015

[Lines 82–83](../../../../../../include/crown/runtime/window.hpp#L82); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L82-L83:sha256:54aae7ec919eea1013f10bb86e37968979a26b90049a6ebaf55373e1c57d7493
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Usage note immediately before \`struct WindowLabel\`: Canonical state is an explicit external DTO. Operational state owns compact native rows, accounted nodes and a separate native active command internally. |
| inputs / outputs | This comment introduces no parameter, field or return value. It documents the adjacent construct beginning at include/crown/runtime/window.hpp:L71; use that declaration for the actual input/output shape. |
| invariants | The source note states: Canonical state is an explicit external DTO. Operational state owns compact native rows, accounted nodes and a separate native active command internally. It is prose guidance; the adjacent implementation is the place to check enforcement. |
| ownership | The comment itself retains nothing. It documents this neighboring ownership/account boundary: Canonical state is an explicit external DTO. Operational state owns compact native rows, accounted nodes and a separate native active command internally. Actual lifetime is determined by the declared members and owners. |
| failure | This comment adds no branch or handler. Any failure behavior remains in the adjacent callable implementation and its callers. |
| cost | The prose adds no executable work. Runtime cost belongs to the adjacent operation; the note does not establish a measured or global complexity bound. |
| Design | [docs/batches_windows.md](../../../../../batches_windows.md), [docs/session_lifecycle.md](../../../../../session_lifecycle.md), [docs/query_memory.md](../../../../../query_memory.md), [docs/code_specs/subsystem_contracts.md](../../../../subsystem_contracts.md) |

## B0016

[Lines 84–90](../../../../../../include/crown/runtime/window.hpp#L84); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct WindowLabel {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Export WindowLabel for inspection. |
| inputs / outputs | Label/table, ordinary full Row, timestamp/deadline/count_id. |
| invariants | Full-row identity includes unused source columns; label ID distinct from duplicate-row count identity. |
| ownership | Owns ordinary caller-allocator rows/strings/vectors/set nodes described above. Copies deep-copy those members; it is neither a cheap shared handle nor a native owner capability. |
| failure | Owning construction/copy can allocate and throw. Ordinary aggregate/memberwise assignment has no special whole-record publication guarantee; no catch/fallback is added. |
| cost | Copy O(row bytes); equality compares all fields. Release row Values/string storage. |
| Design | [include/crown/runtime/window.hpp](../../../../../../include/crown/runtime/window.hpp), [src/runtime/window.cpp](../../../../../../src/runtime/window.cpp), [docs/batches_windows.md](../../../../../batches_windows.md), [docs/code_review.md](../../../../../code_review.md) |

```text
bool operator==(const WindowLabel&) const = default;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Compare window label by stored members. |
| inputs / outputs | Default equality compares all label/table/row/time/count-ID fields. |
| invariants | Equality of exported facts does not prove current native/source/durable identity, report authenticity or minimum-height authority. |
| ownership | Reads both operands synchronously and retains no backing. |
| failure | Uses member comparison; no handler or admission/validation is added by =default. |
| cost | O(compared nested rows/strings/directory IDs); fixed metrics/progress compare bounded scalar fields. |
| Design | [include/crown/runtime/window.hpp](../../../../../../include/crown/runtime/window.hpp), [src/runtime/window.cpp](../../../../../../src/runtime/window.cpp), [docs/batches_windows.md](../../../../../batches_windows.md), [docs/code_review.md](../../../../../code_review.md) |

## B0017

[Lines 91–97](../../../../../../include/crown/runtime/window.hpp#L91); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct WindowCount {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Export WindowCount for inspection. |
| inputs / outputs | id/table/ordinary full Row and positive duplicate-label count. |
| invariants | Count identity can outlive the original label after another duplicate remains. Only 0→1/1→0 distinct presence causes physical set transitions. |
| ownership | Owns ordinary caller-allocator rows/strings/vectors/set nodes described above. Copies deep-copy those members; it is neither a cheap shared handle nor a native owner capability. |
| failure | Owning construction/copy can allocate and throw. Ordinary aggregate/memberwise assignment has no special whole-record publication guarantee; no catch/fallback is added. |
| cost | Copy O(row bytes); equality compares all fields. Release ordinary row/string payload. |
| Design | [include/crown/runtime/window.hpp](../../../../../../include/crown/runtime/window.hpp), [src/runtime/window.cpp](../../../../../../src/runtime/window.cpp), [docs/batches_windows.md](../../../../../batches_windows.md), [docs/code_review.md](../../../../../code_review.md) |

```text
bool operator==(const WindowCount&) const = default;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Compare window count by stored members. |
| inputs / outputs | Default equality compares id/table/row/count. |
| invariants | Equality of exported facts does not prove current native/source/durable identity, report authenticity or minimum-height authority. |
| ownership | Reads both operands synchronously and retains no backing. |
| failure | Uses member comparison; no handler or admission/validation is added by =default. |
| cost | O(compared nested rows/strings/directory IDs); fixed metrics/progress compare bounded scalar fields. |
| Design | [include/crown/runtime/window.hpp](../../../../../../include/crown/runtime/window.hpp), [src/runtime/window.cpp](../../../../../../src/runtime/window.cpp), [docs/batches_windows.md](../../../../../batches_windows.md), [docs/code_review.md](../../../../../code_review.md) |

## B0018

[Lines 98–104](../../../../../../include/crown/runtime/window.hpp#L98); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct WindowActiveCommand {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Export WindowActiveCommand for inspection. |
| inputs / outputs | command sequence/watermark, ordinary expiration-label vector and completed/total/work. |
| invariants | A watermark can have committed prefix steps; final step alone acknowledges external command/completes watermark. Export does not authorize resume by itself. |
| ownership | Owns ordinary caller-allocator rows/strings/vectors/set nodes described above. Copies deep-copy those members; it is neither a cheap shared handle nor a native owner capability. |
| failure | Owning construction/copy can allocate and throw. Ordinary aggregate/memberwise assignment has no special whole-record publication guarantee; no catch/fallback is added. |
| cost | Copy O(expiration label count), no operational map clone. Release one trivial-label vector buffer. |
| Design | [include/crown/runtime/window.hpp](../../../../../../include/crown/runtime/window.hpp), [src/runtime/window.cpp](../../../../../../src/runtime/window.cpp), [docs/batches_windows.md](../../../../../batches_windows.md), [docs/code_review.md](../../../../../code_review.md) |

```text
bool operator==(const WindowActiveCommand&) const = default;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Compare active command by stored members. |
| inputs / outputs | Default equality compares sequence/watermark/expiration vector/step counters/work. |
| invariants | Equality of exported facts does not prove current native/source/durable identity, report authenticity or minimum-height authority. |
| ownership | Reads both operands synchronously and retains no backing. |
| failure | Uses member comparison; no handler or admission/validation is added by =default. |
| cost | O(compared nested rows/strings/directory IDs); fixed metrics/progress compare bounded scalar fields. |
| Design | [include/crown/runtime/window.hpp](../../../../../../include/crown/runtime/window.hpp), [src/runtime/window.cpp](../../../../../../src/runtime/window.cpp), [docs/batches_windows.md](../../../../../batches_windows.md), [docs/code_review.md](../../../../../code_review.md) |

## B0019

[Lines 105–109](../../../../../../include/crown/runtime/window.hpp#L105); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct WindowMetrics {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Report current window component payload and prospective command work. |
| inputs / outputs | live_labels/distinct_rows/accounted_bytes/last_command_work. |
| invariants | Bytes are retained descriptors/native row payload/active capacity, not whole-account requested bytes. Work precharge is per prepared/committed command state, not total CPU across aborted retries. |
| ownership | Caller owns inline numeric/tag fields; this record retains no backing runtime, rows, strings or allocation grant. |
| failure | The declaration does not validate public fields or translate failure. Actual factories/consumers perform the stated checks. |
| cost | Fixed inline scalar/enum/optional/array storage and bounded copies; no dynamic payload, scan, clock or allocation. |
| Design | [include/crown/runtime/window.hpp](../../../../../../include/crown/runtime/window.hpp), [src/runtime/window.cpp](../../../../../../src/runtime/window.cpp), [docs/batches_windows.md](../../../../../batches_windows.md), [docs/code_review.md](../../../../../code_review.md) |

```text
bool operator==(const WindowMetrics&) const = default;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Compare window metrics by stored members. |
| inputs / outputs | Default equality compares all sizes/last work. |
| invariants | Equality of exported facts does not prove current native/source/durable identity, report authenticity or minimum-height authority. |
| ownership | Reads both operands synchronously and retains no backing. |
| failure | Uses member comparison; no handler or admission/validation is added by =default. |
| cost | O(compared nested rows/strings/directory IDs); fixed metrics/progress compare bounded scalar fields. |
| Design | [include/crown/runtime/window.hpp](../../../../../../include/crown/runtime/window.hpp), [src/runtime/window.cpp](../../../../../../src/runtime/window.cpp), [docs/batches_windows.md](../../../../../batches_windows.md), [docs/code_review.md](../../../../../code_review.md) |

## B0020

[Lines 110–115](../../../../../../include/crown/runtime/window.hpp#L110); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct WindowProgress {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Report committed command/physical/window expansion progress. |
| inputs / outputs | Completed external command, physical sequence, watermark,last label; optional active command and step counters. |
| invariants | Physical epochs differ from command sequence; active means committed prefix expansion, not complete command acknowledgment or durable acceptance. |
| ownership | Caller owns inline numeric/tag fields; this record retains no backing runtime, rows, strings or allocation grant. |
| failure | The declaration does not validate public fields or translate failure. Actual factories/consumers perform the stated checks. |
| cost | Fixed inline scalar/enum/optional/array storage and bounded copies; no dynamic payload, scan, clock or allocation. |
| Design | [include/crown/runtime/window.hpp](../../../../../../include/crown/runtime/window.hpp), [src/runtime/window.cpp](../../../../../../src/runtime/window.cpp), [docs/batches_windows.md](../../../../../batches_windows.md), [docs/code_review.md](../../../../../code_review.md) |

```text
bool operator==(const WindowProgress&) const = default;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Compare window progress by stored members. |
| inputs / outputs | Default equality compares all sequences/watermark/label/active and step fields. |
| invariants | Equality of exported facts does not prove current native/source/durable identity, report authenticity or minimum-height authority. |
| ownership | Reads both operands synchronously and retains no backing. |
| failure | Uses member comparison; no handler or admission/validation is added by =default. |
| cost | O(compared nested rows/strings/directory IDs); fixed metrics/progress compare bounded scalar fields. |
| Design | [include/crown/runtime/window.hpp](../../../../../../include/crown/runtime/window.hpp), [src/runtime/window.cpp](../../../../../../src/runtime/window.cpp), [docs/batches_windows.md](../../../../../batches_windows.md), [docs/code_review.md](../../../../../code_review.md) |

## B0021

[Lines 116–126](../../../../../../include/crown/runtime/window.hpp#L116); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct WindowCanonicalState {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Export WindowCanonicalState for inspection. |
| inputs / outputs | ordinary label/count vectors, expiration/global/per-relation directories, progress, optional active command and metrics. |
| invariants | Explicit external DTO, not native restore or durable authority. Operational native graph remains separate; copied flags do not admit source/window binding. |
| ownership | Owns ordinary caller-allocator rows/strings/vectors/set nodes described above. Copies deep-copy those members; it is neither a cheap shared handle nor a native owner capability. |
| failure | Owning construction/copy can allocate and throw. Ordinary aggregate/memberwise assignment has no special whole-record publication guarantee; no catch/fallback is added. |
| cost | Full state/row copy O(all exported rows/labels/directories); equality walks nested state. Release nested row/string/vector owners; no runtime retained. |
| Design | [include/crown/runtime/window.hpp](../../../../../../include/crown/runtime/window.hpp), [src/runtime/window.cpp](../../../../../../src/runtime/window.cpp), [docs/batches_windows.md](../../../../../batches_windows.md), [docs/code_review.md](../../../../../code_review.md) |

```text
bool operator==(const WindowCanonicalState&) const = default;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Compare window export by stored members. |
| inputs / outputs | Default equality compares all label/count/directory/progress/active/metric fields. |
| invariants | Equality of exported facts does not prove current native/source/durable identity, report authenticity or minimum-height authority. |
| ownership | Reads both operands synchronously and retains no backing. |
| failure | Uses member comparison; no handler or admission/validation is added by =default. |
| cost | O(compared nested rows/strings/directory IDs); fixed metrics/progress compare bounded scalar fields. |
| Design | [include/crown/runtime/window.hpp](../../../../../../include/crown/runtime/window.hpp), [src/runtime/window.cpp](../../../../../../src/runtime/window.cpp), [docs/batches_windows.md](../../../../../batches_windows.md), [docs/code_review.md](../../../../../code_review.md) |

## B0022

[Lines 127–130](../../../../../../include/crown/runtime/window.hpp#L127); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct WindowStateLimits {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Bound native window checkpoint/restore validation. |
| inputs / outputs | Logical work16Mi actions, label/count maximum65536. |
| invariants | Separate from retained payload cap and original query account; scalar string-byte compare and tree/allocator costs additional. |
| ownership | Caller owns inline numeric/tag fields; this record retains no backing runtime, rows, strings or allocation grant. |
| failure | The declaration does not validate public fields or translate failure. Actual factories/consumers perform the stated checks. |
| cost | Fixed inline scalar/enum/optional/array storage and bounded copies; no dynamic payload, scan, clock or allocation. |
| Design | [include/crown/runtime/window.hpp](../../../../../../include/crown/runtime/window.hpp), [src/runtime/window.cpp](../../../../../../src/runtime/window.cpp), [docs/batches_windows.md](../../../../../batches_windows.md), [docs/code_review.md](../../../../../code_review.md) |

## B0023

[Lines 131–136](../../../../../../include/crown/runtime/window.hpp#L131); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct WindowCheckpointLabel {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Own one native WindowCheckpointLabel entry. |
| inputs / outputs | Fields: label/table/native AccountedRow/timestamp/deadline/count_id. |
| invariants | Native row is move-only; no ordinary owning Row export and no supported implicit deep-copy of the entry. Actual factory validates identity/layout/references. |
| ownership | AccountedRow owns one compact funded scalar/string block. Moves transfer that block; explicit clone chooses receiving original account. |
| failure | Explicit row clone may allocate/throw; move/release do not allocate. |
| cost | Copy factory O(columns+row bytes); move fixed; release one real block, no per-string heap graph. |
| Design | [include/crown/runtime/window.hpp](../../../../../../include/crown/runtime/window.hpp), [src/runtime/window.cpp](../../../../../../src/runtime/window.cpp), [docs/batches_windows.md](../../../../../batches_windows.md), [docs/code_review.md](../../../../../code_review.md), [include/crown/storage/accounted_row.hpp](../../../../../../include/crown/storage/accounted_row.hpp) |

## B0024

[Lines 137–142](../../../../../../include/crown/runtime/window.hpp#L137); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct WindowCheckpointCount {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Own one native WindowCheckpointCount entry. |
| inputs / outputs | Fields: id/table/native AccountedRow/positive multiplicity. |
| invariants | Native row is move-only; no ordinary owning Row export and no supported implicit deep-copy of the entry. Actual factory validates identity/layout/references. |
| ownership | AccountedRow owns one compact funded scalar/string block. Moves transfer that block; explicit clone chooses receiving original account. |
| failure | Explicit row clone may allocate/throw; move/release do not allocate. |
| cost | Copy factory O(columns+row bytes); move fixed; release one real block, no per-string heap graph. |
| Design | [include/crown/runtime/window.hpp](../../../../../../include/crown/runtime/window.hpp), [src/runtime/window.cpp](../../../../../../src/runtime/window.cpp), [docs/batches_windows.md](../../../../../batches_windows.md), [docs/code_review.md](../../../../../code_review.md), [include/crown/storage/accounted_row.hpp](../../../../../../include/crown/storage/accounted_row.hpp) |

## B0025

[Lines 143–145](../../../../../../include/crown/runtime/window.hpp#L143); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L143-L145:sha256:6b086f3931afe06fb11d5f9c714e500d3b8233374e1c09fba3aa039967403a47
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Usage note immediately before \`struct WindowCheckpoint\`: Native quiescent window state for the session envelope. FIFO/expiration directories are derived from validated labels on restore. Count identity, including IDs whose original label expired, and all progress are retained. |
| inputs / outputs | This comment introduces no parameter, field or return value. It documents the adjacent construct beginning at include/crown/runtime/window.hpp:L133; use that declaration for the actual input/output shape. |
| invariants | The source note states: Native quiescent window state for the session envelope. FIFO/expiration directories are derived from validated labels on restore. Count identity, including IDs whose original label expired, and all progress are retained. It is prose guidance; the adjacent implementation is the place to check enforcement. |
| ownership | The comment itself retains nothing. It documents this neighboring ownership/account boundary: Native quiescent window state for the session envelope. FIFO/expiration directories are derived from validated labels on restore. Count identity, including IDs whose original label expired, and all progress are retained. Actual lifetime is determined by the declared members and owners. |
| failure | This comment adds no branch or handler. Any failure behavior remains in the adjacent callable implementation and its callers. |
| cost | The prose adds no executable work. Runtime cost belongs to the adjacent operation; the note does not establish a measured or global complexity bound. |
| Design | [docs/batches_windows.md](../../../../../batches_windows.md), [docs/session_lifecycle.md](../../../../../session_lifecycle.md), [docs/query_memory.md](../../../../../query_memory.md), [docs/code_specs/subsystem_contracts.md](../../../../subsystem_contracts.md) |

## B0026

[Lines 146–159](../../../../../../include/crown/runtime/window.hpp#L146); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct WindowCheckpoint {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Own a native quiescent window checkpoint component. |
| inputs / outputs | Accounted options/progress, ImageVectors of move-only native label/count rows, fixed catalog digest/work/stopped flags. |
| invariants | No Prepared or active watermark, including stopped tombstone, may checkpoint. Count identities/progress retained; restore derives FIFO/expiration directories and validates count references. Public fields do not prove source/base equality or durability. |
| ownership | Owns funded row/vector payload and actual immutable options handle. Entries contain move-only AccountedRow; implicit copying is not a supported deep-clone operation. Factory checkpoint_state explicitly clones. |
| failure | Construction/capture/restore can allocate/throw before publication; partial native payload unwinds. |
| cost | O(labels+counts+row bytes) explicit capture clones; release visits entries and frees each row/vector block, plus last options owner. |
| Design | [include/crown/runtime/window.hpp](../../../../../../include/crown/runtime/window.hpp), [src/runtime/window.cpp](../../../../../../src/runtime/window.cpp), [docs/batches_windows.md](../../../../../batches_windows.md), [docs/code_review.md](../../../../../code_review.md), [include/crown/recovery/image.hpp](../../../../../../include/crown/recovery/image.hpp) |

```text
WindowCheckpoint(const resource::MemoryAccount& account,AccountedWindowOptions value)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Bind empty native checkpoint arrays to account and adopt options. |
| inputs / outputs | Moves by-value AccountedWindowOptions; binds label/count ImageVector allocators to supplied account. |
| invariants | Does not clone rows or validate options/identity; actual factories supply compatible account/options. |
| ownership | Options retain their actual given owner; vectors retain supplied account and start empty. |
| failure | By-value argument or earlier explicit import may allocate before constructor; body performs ownership/allocator setup. |
| cost | Fixed handle/allocator setup, no label/count allocation. |
| Design | [include/crown/runtime/window.hpp](../../../../../../include/crown/runtime/window.hpp), [src/runtime/window.cpp](../../../../../../src/runtime/window.cpp), [docs/batches_windows.md](../../../../../batches_windows.md), [docs/code_review.md](../../../../../code_review.md) |

## B0027

[Lines 160–163](../../../../../../include/crown/runtime/window.hpp#L160); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
class WindowController {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Own operational window state under the selected FIFO policy with one outstanding preparation. |
| inputs / outputs | Stable Impl has native rows/accounted ordered label/count/FIFO/expiration maps and optional active expansion; public facade noncopyable. |
| invariants | Managed tables initially empty are enforced by QuerySession. Labels for the same row share full-row set presence. The global/per_relation policies order labels; physical_global/physical_per_relation order live full-row lifetimes; unrestricted imposes no FIFO ordering. Caller serializes controller; no internal lock. |
| ownership | Controller owns shared Impl; Prepared deliberately borrows raw Impl and must die before controller/stop. Native allocations stay on original account. |
| failure | Admission/prepare/checkpoint/export can throw; publication is nonthrowing after required native commit/metadata barrier. |
| cost | Insert may linearly compare distinct full rows; ordered maps add log factors; watermark preflight scans all expiring order, clones/reserves before publication. |
| Design | [include/crown/runtime/window.hpp](../../../../../../include/crown/runtime/window.hpp), [src/runtime/window.cpp](../../../../../../src/runtime/window.cpp), [docs/batches_windows.md](../../../../../batches_windows.md), [docs/code_review.md](../../../../../code_review.md), [src/runtime/session.cpp](../../../../../../src/runtime/session.cpp), [docs/update_patterns.md](../../../../../update_patterns.md) |

## B0028

[Lines 164–185](../../../../../../include/crown/runtime/window.hpp#L164); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
class Prepared {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Own a prepared window step while borrowing its controller. |
| inputs / outputs | Move-only AccountedUnique&lt;Data&gt; owns frozen update row, extracted funded nodes and prospective active command/byte/work totals. |
| invariants | Only one Prepared per controller. Must follow engine commit or explicit metadata barrier before publish; destroy Prepared before stopping/destroying Controller. |
| ownership | Owns prepared row/nodes/control but raw owner pointer does not retain Impl. update view borrows its row; source command not retained. |
| failure | Failed preparation frees private nodes; uncommitted destruction resets prepared flag without effect. After publish destruction only frees residual private ownership. |
| cost | Prepare pays allocation/clone/search/preflight; moving fixed ownership; teardown frees remaining nodes/row/active capacity without allocation. |
| Design | [include/crown/runtime/window.hpp](../../../../../../include/crown/runtime/window.hpp), [src/runtime/window.cpp](../../../../../../src/runtime/window.cpp), [docs/batches_windows.md](../../../../../batches_windows.md), [docs/code_review.md](../../../../../code_review.md) |

```text
~Prepared();
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Destroy prepared step ownership. |
| inputs / outputs | Default unique Data destruction; if still linked to owner reset owner.prepared. |
| invariants | Controller must remain alive; before stop. Unpublished step never changes committed window maps. |
| ownership | Frees private control/row/nodes; no ownership of Controller. |
| failure | Ordinary RAII, nonthrowing; lifetime misuse is not repaired. |
| cost | Releases a fixed number of staged nodes/row/control and any trivial-ID vector block; no scan of live labels or expiration IDs, no allocation. |
| Design | [include/crown/runtime/window.hpp](../../../../../../include/crown/runtime/window.hpp), [src/runtime/window.cpp](../../../../../../src/runtime/window.cpp), [docs/batches_windows.md](../../../../../batches_windows.md), [docs/code_review.md](../../../../../code_review.md) |

```text
Prepared(Prepared&&) noexcept;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Move Prepared by construction. |
| inputs / outputs | Transfers unique native Data. |
| invariants | Moved-from publish can no-op; update/completes require live Data. Assignment destroys old preparation first. |
| ownership | Transfers all staged ownership and raw controller borrow. |
| failure | noexcept for a live readable object; borrowing does not validate lifetime or extend it. |
| cost | Fixed transfer plus old prepared cleanup; no allocation. |
| Design | [include/crown/runtime/window.hpp](../../../../../../include/crown/runtime/window.hpp), [src/runtime/window.cpp](../../../../../../src/runtime/window.cpp), [docs/batches_windows.md](../../../../../batches_windows.md), [docs/code_review.md](../../../../../code_review.md) |

```text
Prepared& operator=(Prepared&&) noexcept;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Move Prepared by assignment. |
| inputs / outputs | Transfers unique native Data. |
| invariants | Moved-from publish can no-op; update/completes require live Data. Assignment destroys old preparation first. |
| ownership | Transfers all staged ownership and raw controller borrow. |
| failure | noexcept for a live readable object; borrowing does not validate lifetime or extend it. |
| cost | Fixed transfer plus old prepared cleanup; no allocation. |
| Design | [include/crown/runtime/window.hpp](../../../../../../include/crown/runtime/window.hpp), [src/runtime/window.cpp](../../../../../../src/runtime/window.cpp), [docs/batches_windows.md](../../../../../batches_windows.md), [docs/code_review.md](../../../../../code_review.md) |

```text
Prepared(const Prepared&)=delete;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Reject Prepared copy construction. |
| inputs / outputs | Deleted operation. |
| invariants | A prospective publication cannot be duplicated. |
| ownership | Unique staged owner. |
| failure | Compile-time rejection. |
| cost | No runtime cost. |
| Design | [include/crown/runtime/window.hpp](../../../../../../include/crown/runtime/window.hpp), [src/runtime/window.cpp](../../../../../../src/runtime/window.cpp), [docs/batches_windows.md](../../../../../batches_windows.md), [docs/code_review.md](../../../../../code_review.md) |

```text
Prepared& operator=(const Prepared&)=delete;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Reject Prepared copy assignment. |
| inputs / outputs | Deleted operation. |
| invariants | A prospective publication cannot be duplicated. |
| ownership | Unique staged owner. |
| failure | Compile-time rejection. |
| cost | No runtime cost. |
| Design | [include/crown/runtime/window.hpp](../../../../../../include/crown/runtime/window.hpp), [src/runtime/window.cpp](../../../../../../src/runtime/window.cpp), [docs/batches_windows.md](../../../../../batches_windows.md), [docs/code_review.md](../../../../../code_review.md) |

```text
[[nodiscard]] const std::optional<PhysicalUpdateView>& update() const noexcept;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Borrow optional physical set update for prepared step. |
| inputs / outputs | Returns const optional&lt;PhysicalUpdateView&gt;&. |
| invariants | Metadata-only duplicate-label/empty watermark steps can have no physical update; do not invent a physical epoch. |
| ownership | Keep live Prepared/control alive; values borrow its frozen row, not caller command. |
| failure | noexcept for a live readable object; borrowing does not validate lifetime or extend it. |
| cost | O(1) fixed member/view lookup; no allocation or clock. |
| Design | [include/crown/runtime/window.hpp](../../../../../../include/crown/runtime/window.hpp), [src/runtime/window.cpp](../../../../../../src/runtime/window.cpp), [docs/batches_windows.md](../../../../../batches_windows.md), [docs/code_review.md](../../../../../code_review.md) |

```text
[[nodiscard]] bool completes_command() const noexcept;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Read whether the prepared step finishes its external command. |
| inputs / outputs | Returns Data.complete. |
| invariants | Final watermark substep alone acknowledges external queue head; earlier steps leave active command. |
| ownership | Returns independent boolean; live Prepared required. |
| failure | noexcept for a live readable object; borrowing does not validate lifetime or extend it. |
| cost | O(1) fixed member/view lookup; no allocation or clock. |
| Design | [include/crown/runtime/window.hpp](../../../../../../include/crown/runtime/window.hpp), [src/runtime/window.cpp](../../../../../../src/runtime/window.cpp), [docs/batches_windows.md](../../../../../batches_windows.md), [docs/code_review.md](../../../../../code_review.md) |

```text
void publish() noexcept;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Publish funded window metadata after successful native/barrier commit. |
| inputs / outputs | Adopts prepared tree nodes or removes committed label/count/index entries, advances active/completed/physical scalars and prospective bytes/work; null/already published no-op. |
| invariants | Never call before engine commit when update engaged. Caller ensures one Prepared and controller lifetime. All needed allocations precede publication. |
| ownership | Nodes transfer into owner maps on same allocator; deleted rows/nodes and completed active vector released. Data.owner cleared after publication. |
| failure | noexcept; no rollback catch/allocating fallback. Violation of commit ordering is caller error. |
| cost | No allocation; ordered insert/find/erase still O(log live sizes), row/node/active release real costs, not constant publication CPU. |
| Design | [include/crown/runtime/window.hpp](../../../../../../include/crown/runtime/window.hpp), [src/runtime/window.cpp](../../../../../../src/runtime/window.cpp), [docs/batches_windows.md](../../../../../batches_windows.md), [docs/code_review.md](../../../../../code_review.md) |

```text
explicit Prepared(resource::AccountedUnique<Data>) noexcept;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Adopt private prepared Data. |
| inputs / outputs | Constructor moves AccountedUnique&lt;Data&gt;. |
| invariants | Controller factory completed all allocating preparation and set prepared=true. |
| ownership | Unique staged data, raw owner borrowed. |
| failure | noexcept for a live readable object; borrowing does not validate lifetime or extend it. |
| cost | O(1) transfer. |
| Design | [include/crown/runtime/window.hpp](../../../../../../include/crown/runtime/window.hpp), [src/runtime/window.cpp](../../../../../../src/runtime/window.cpp), [docs/batches_windows.md](../../../../../batches_windows.md), [docs/code_review.md](../../../../../code_review.md) |

## B0029

[Lines 186–211](../../../../../../include/crown/runtime/window.hpp#L186); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
WindowController(Catalog catalog,WindowOptions options);
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Admit standalone window controller. |
| inputs / outputs | Catalog and WindowOptions by value create standalone finite uint64-max account. |
| invariants | Validate positive settings, supported FIFO, nonempty/distinct managed IDs/catalog membership and retained model; no row membership/initial-base scan here. Session enforces initial emptiness. Admission accepts precisely policies 0..4; unrestricted is an explicit baseline, not inferred fallback. |
| ownership | Owns private account/Impl/options/maps; by-value ordinary inputs may already copy/allocate. |
| failure | Validation/account/OOM failure destroys private graph before facade exists. |
| cost | Copies managed ID capacity, hashes complete catalog, builds per-relation tree nodes; no update work hidden. Standalone construction intentionally creates its own account. |
| Design | [include/crown/runtime/window.hpp](../../../../../../include/crown/runtime/window.hpp), [src/runtime/window.cpp](../../../../../../src/runtime/window.cpp), [docs/batches_windows.md](../../../../../batches_windows.md), [docs/code_review.md](../../../../../code_review.md), [docs/update_patterns.md](../../../../../update_patterns.md) |

```text
WindowController(const resource::MemoryAccount&,const program::Catalog&,const WindowOptions&);
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Admit query-funded window controller. |
| inputs / outputs | Existing account, actual program Catalog and options. |
| invariants | Validate positive settings, supported FIFO, nonempty/distinct managed IDs/catalog membership and retained model; no row membership/initial-base scan here. Session enforces initial emptiness. Admission accepts precisely policies 0..4; unrestricted is an explicit baseline, not inferred fallback. |
| ownership | Owns funded Impl/options/directories on supplied original account; catalog borrowed synchronously. |
| failure | Validation/account/OOM failure destroys private graph before facade exists. |
| cost | Copies managed ID capacity, hashes complete catalog, builds per-relation tree nodes; no update work hidden. Standalone construction intentionally creates its own account. |
| Design | [include/crown/runtime/window.hpp](../../../../../../include/crown/runtime/window.hpp), [src/runtime/window.cpp](../../../../../../src/runtime/window.cpp), [docs/batches_windows.md](../../../../../batches_windows.md), [docs/code_review.md](../../../../../code_review.md), [docs/update_patterns.md](../../../../../update_patterns.md) |

```text
WindowController(const resource::MemoryAccount&,const program::Catalog&,const WindowCheckpoint&,WindowStateLimits={});
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Restore native window component into private controller. |
| inputs / outputs | Original account/catalog, WindowCheckpoint and finite WindowStateLimits. |
| invariants | Reject active/invalid progress, catalog mismatch, duplicate full rows, malformed IDs/timestamps/deadlines, count references and resource excess. Base/source row equality belongs to session/runtime restore separately. |
| ownership | Clones native label/count rows into receiver and rebuilds ordered FIFO/expiration maps; scratch unique/reference maps released before publish. |
| failure | Image/row/account/allocation failures unwind entire private graph, existing source unchanged. |
| cost | O(labels+counts) row scans plus ordered map/key comparisons and O(total row bytes) clones; scratch/key/reference/real node allocations original-account, scalar byte costs additional. |
| Design | [include/crown/runtime/window.hpp](../../../../../../include/crown/runtime/window.hpp), [src/runtime/window.cpp](../../../../../../src/runtime/window.cpp), [docs/batches_windows.md](../../../../../batches_windows.md), [docs/code_review.md](../../../../../code_review.md) |

```text
[[nodiscard]] WindowCheckpoint checkpoint_state(WindowStateLimits={}) const;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Capture a native quiescent window component. |
| inputs / outputs | Finite state limits; requires no prepared or active command, even if stopped. |
| invariants | Checks label/count bounds and charges row-column scans before cloning; does not make durable file or certify managed base equality. |
| ownership | Clones compact label/count rows and arrays on same original account; options shared, not runtime retained. |
| failure | Failure frees partial new checkpoint; live state unchanged. |
| cost | O(labels+counts+all row bytes) clone plus native vector allocation; original and copied row graphs coexist. |
| Design | [include/crown/runtime/window.hpp](../../../../../../include/crown/runtime/window.hpp), [src/runtime/window.cpp](../../../../../../src/runtime/window.cpp), [docs/batches_windows.md](../../../../../batches_windows.md), [docs/code_review.md](../../../../../code_review.md) |

```text
~WindowController();
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Release operational window owner. |
| inputs / outputs | Destroy facade shared Impl. |
| invariants | Every Prepared raw borrow must already be destroyed. |
| ownership | Frees all label/count/expiration/FIFO/relation nodes/row blocks/active capacity and last options handle. |
| failure | Nonthrowing RAII; no new allowance or cleanup allocation. |
| cost | O(live nodes/row owners) deallocation; scalar/string bytes live in compact blocks, no ordinary export. |
| Design | [include/crown/runtime/window.hpp](../../../../../../include/crown/runtime/window.hpp), [src/runtime/window.cpp](../../../../../../src/runtime/window.cpp), [docs/batches_windows.md](../../../../../batches_windows.md), [docs/code_review.md](../../../../../code_review.md) |

```text
WindowController(const WindowController&)=delete;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Reject controller copy construction. |
| inputs / outputs | Deleted operation. |
| invariants | Stable controller lifecycle must not duplicate one outstanding Prepared owner relation. User-declared destructor also supplies no implicit move API. |
| ownership | Single facade ownership. |
| failure | Compile-time rejection. |
| cost | No runtime cost. |
| Design | [include/crown/runtime/window.hpp](../../../../../../include/crown/runtime/window.hpp), [src/runtime/window.cpp](../../../../../../src/runtime/window.cpp), [docs/batches_windows.md](../../../../../batches_windows.md), [docs/code_review.md](../../../../../code_review.md) |

```text
WindowController& operator=(const WindowController&)=delete;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Reject controller copy assignment. |
| inputs / outputs | Deleted operation. |
| invariants | Stable controller lifecycle must not duplicate one outstanding Prepared owner relation. User-declared destructor also supplies no implicit move API. |
| ownership | Single facade ownership. |
| failure | Compile-time rejection. |
| cost | No runtime cost. |
| Design | [include/crown/runtime/window.hpp](../../../../../../include/crown/runtime/window.hpp), [src/runtime/window.cpp](../../../../../../src/runtime/window.cpp), [docs/batches_windows.md](../../../../../batches_windows.md), [docs/code_review.md](../../../../../code_review.md) |

```text
[[nodiscard]] Prepared prepare(const io::WindowCommand&,std::uint64_t next_physical_sequence);
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Prepare one step from ordinary WindowCommand (borrowed view adapter). |
| inputs / outputs | Command and next physical sequence; stable values during call; returns move-only Prepared, optional physical update. |
| invariants | Require live/unprepared controller, contiguous external sequence/current active watermark, monotone label/time/watermark, managed table/FIFO and finite caps. Physical sequence checked only for distinct-presence transitions. Public standalone prepare delegates without a Session declaration; only QuerySession can use the private pattern-aware preparation path. |
| ownership | Copies/freeze needed row values, preallocates/extracts nodes and whole watermark expansion, retains no command view after return. Prepared borrows Controller. |
| failure | Validation/resource/OOM errors free private graph; d.prepared set only at success. Committed window state unchanged until publish. |
| cost | Insertion linearly scans distinct full rows incl unused columns/byte comparisons; ordered structures add log costs. First watermark preflights complete expiration order and reserves all substep work/capacity, using temporary per-relation cursors. |
| Design | [include/crown/runtime/window.hpp](../../../../../../include/crown/runtime/window.hpp), [src/runtime/window.cpp](../../../../../../src/runtime/window.cpp), [docs/batches_windows.md](../../../../../batches_windows.md), [docs/code_review.md](../../../../../code_review.md), [docs/update_patterns.md](../../../../../update_patterns.md) |

```text
[[nodiscard]] Prepared prepare_view(const io::WindowCommandView&,std::uint64_t next_physical_sequence);
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Prepare one step from native WindowCommandView. |
| inputs / outputs | Command and next physical sequence; stable values during call; returns move-only Prepared, optional physical update. |
| invariants | Require live/unprepared controller, contiguous external sequence/current active watermark, monotone label/time/watermark, managed table/FIFO and finite caps. Physical sequence checked only for distinct-presence transitions. Public standalone prepare delegates without a Session declaration; only QuerySession can use the private pattern-aware preparation path. |
| ownership | Copies/freeze needed row values, preallocates/extracts nodes and whole watermark expansion, retains no command view after return. Prepared borrows Controller. |
| failure | Validation/resource/OOM errors free private graph; d.prepared set only at success. Committed window state unchanged until publish. |
| cost | Insertion linearly scans distinct full rows incl unused columns/byte comparisons; ordered structures add log costs. First watermark preflights complete expiration order and reserves all substep work/capacity, using temporary per-relation cursors. |
| Design | [include/crown/runtime/window.hpp](../../../../../../include/crown/runtime/window.hpp), [src/runtime/window.cpp](../../../../../../src/runtime/window.cpp), [docs/batches_windows.md](../../../../../batches_windows.md), [docs/code_review.md](../../../../../code_review.md), [docs/update_patterns.md](../../../../../update_patterns.md) |

```text
[[nodiscard]] WindowCanonicalState canonical_state() const;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Export complete ordinary window diagnostics. |
| inputs / outputs | Returns WindowCanonicalState with all labels/counts/directories/scalars and optional active expansion. |
| invariants | Explicit caller DTO, no automatic checkpoint admission/durability or source equivalence. Direct controller caller serializes access; session wrapper adds committed-step guard. |
| ownership | Copies native rows to ordinary Row/string/vector storage outside query account; native controller unchanged. |
| failure | Ordinary export allocation may throw; partial DTO freed, live state unchanged. |
| cost | O(all rows/bytes+directory labels+active IDs) scan/copy/allocation; not hot hook or fixed getter. |
| Design | [include/crown/runtime/window.hpp](../../../../../../include/crown/runtime/window.hpp), [src/runtime/window.cpp](../../../../../../src/runtime/window.cpp), [docs/batches_windows.md](../../../../../batches_windows.md), [docs/code_review.md](../../../../../code_review.md) |

```text
[[nodiscard]] WindowMetrics metrics() const noexcept;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Read controller component metrics. |
| inputs / outputs | Returns WindowMetrics. |
| invariants | Retained payload model/work, not total allocator/RSS or total work across aborted retries. |
| ownership | Scalar output independent; options reference borrows Controller, copy its owning handle explicitly if needed. |
| failure | noexcept for a live readable object; borrowing does not validate lifetime or extend it. |
| cost | O(1) fixed member/view lookup; no allocation or clock. |
| Design | [include/crown/runtime/window.hpp](../../../../../../include/crown/runtime/window.hpp), [src/runtime/window.cpp](../../../../../../src/runtime/window.cpp), [docs/batches_windows.md](../../../../../batches_windows.md), [docs/code_review.md](../../../../../code_review.md) |

```text
[[nodiscard]] WindowProgress progress() const noexcept;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Read controller command/physical progress. |
| inputs / outputs | Returns WindowProgress. |
| invariants | Active expansion steps differ from completed external command and physical epoch. |
| ownership | Scalar output independent; options reference borrows Controller, copy its owning handle explicitly if needed. |
| failure | noexcept for a live readable object; borrowing does not validate lifetime or extend it. |
| cost | O(1) fixed member/view lookup; no allocation or clock. |
| Design | [include/crown/runtime/window.hpp](../../../../../../include/crown/runtime/window.hpp), [src/runtime/window.cpp](../../../../../../src/runtime/window.cpp), [docs/batches_windows.md](../../../../../batches_windows.md), [docs/code_review.md](../../../../../code_review.md) |

```text
[[nodiscard]] const AccountedWindowOptions& options() const noexcept;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Read controller native admitted options. |
| inputs / outputs | Returns const AccountedWindowOptions&. |
| invariants | Returned handle value can be copied to retain its actual list after controller closes. |
| ownership | Scalar output independent; options reference borrows Controller, copy its owning handle explicitly if needed. |
| failure | noexcept for a live readable object; borrowing does not validate lifetime or extend it. |
| cost | O(1) fixed member/view lookup; no allocation or clock. |
| Design | [include/crown/runtime/window.hpp](../../../../../../include/crown/runtime/window.hpp), [src/runtime/window.cpp](../../../../../../src/runtime/window.cpp), [docs/batches_windows.md](../../../../../batches_windows.md), [docs/code_review.md](../../../../../code_review.md) |

```text
void stop() noexcept;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Stop further expansion while retaining committed prefix diagnostics. |
| inputs / outputs | Marks stopped; if active, releases expiration vector capacity and adjusts bytes but retains active scalar tombstone. |
| invariants | Terminal. Destroy Prepared before stop. Active tombstone still prevents quiescent checkpoint and marks incomplete command; no false completion/acknowledgment. |
| ownership | Releases active buffer; committed label/count/maps and options remain until controller destruction. |
| failure | noexcept; no allocation. |
| cost | Fixed state update/vector-block free, no scan of all labels/counts. Future prepare rejects. |
| Design | [include/crown/runtime/window.hpp](../../../../../../include/crown/runtime/window.hpp), [src/runtime/window.cpp](../../../../../../src/runtime/window.cpp), [docs/batches_windows.md](../../../../../batches_windows.md), [docs/code_review.md](../../../../../code_review.md) |

```text
std::shared_ptr<Impl> data_;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Retain actual operational implementation and account. |
| inputs / outputs | Private shared_ptr&lt;Impl&gt; owns native graph, test friend only under CROWN_RUNTIME_TESTING. |
| invariants | Prepared raw pointer does not increment this owner. No public arbitrary state import through fields. |
| ownership | Final Impl teardown frees all actual map/row/vector owners. |
| failure | RAII release, no handler or new grant. |
| cost | Refcount release and final owned-graph cleanup, not constant full destruction. |
| Design | [include/crown/runtime/window.hpp](../../../../../../include/crown/runtime/window.hpp), [src/runtime/window.cpp](../../../../../../src/runtime/window.cpp), [docs/batches_windows.md](../../../../../batches_windows.md), [docs/code_review.md](../../../../../code_review.md) |
