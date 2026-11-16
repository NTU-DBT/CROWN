# `include/crown/runtime/inspection.hpp` — block usage map

[Source](../../../../../../include/crown/runtime/inspection.hpp) · [Source index](../../../../README.md) · [Subsystem contracts](../../../../subsystem_contracts.md) · [Reviewed primitives](../../../../primitives.md)

Capture bounded distributions, workload counters, owner memory and explain observations without mislabeling partial information as exact.

Snapshot SHA-256: `d8d5418ab1de4d6286cd82c58d9ea868b181e8c2b5627f6a6c8eff08c5abcc5f`. 143 lines partitioned into 29 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [statistics](../../../../subsystem_contracts.md#statistics). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/statistics.md](../../../../../statistics.md), [docs/observability.md](../../../../../observability.md), [docs/memory_reports.md](../../../../../memory_reports.md), [docs/ranking_evaluation.md](../../../../../ranking_evaluation.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–8](../../../../../../include/crown/runtime/inspection.hpp#L1) | Imports dependencies; guards repeated header inclusion; declares namespace scope. |  · [reviewed contract](#b0001) |
| [B0002 · 9–12](../../../../../../include/crown/runtime/inspection.hpp#L9) | Type/record definition: enum class InvariantComponent |  · [reviewed contract](#b0002) |
| [B0003 · 13–17](../../../../../../include/crown/runtime/inspection.hpp#L13) | Type/record definition: enum class InvariantCode |  · [reviewed contract](#b0003) |
| [B0004 · 18–24](../../../../../../include/crown/runtime/inspection.hpp#L18) | declares types or opens a type body; declares callable signatures; declares values/defaults or compile-time conditions. | source comment (unverified): // Localized diagnostic keys retain compact values under their original query · [reviewed contract](#b0004) |
| [B0005 · 25–27](../../../../../../include/crown/runtime/inspection.hpp#L25) | Callable definition: InvariantKey(const InvariantKey& other):account_(other.account_) | calls account_, empty, clone; growth clone · [reviewed contract](#b0005) |
| [B0006 · 28–30](../../../../../../include/crown/runtime/inspection.hpp#L28) | Callable definition: InvariantKey& operator=(const InvariantKey& other) | calls std::move; returns *this · [reviewed contract](#b0006) |
| [B0007 · 31–32](../../../../../../include/crown/runtime/inspection.hpp#L31) | declares callable signatures; declares values/defaults or compile-time conditions. |  · [reviewed contract](#b0007) |
| [B0008 · 33–37](../../../../../../include/crown/runtime/inspection.hpp#L33) | Callable definition: \[\[nodiscard\]\] static InvariantKey copy_of(const resource::MemoryAccount& account,storage::RowView values) | calls empty, storage::AccountedRow::copy_of; returns out; growth copy_of · [reviewed contract](#b0008) |
| [B0009 · 38–38](../../../../../../include/crown/runtime/inspection.hpp#L38) | Callable definition: \[\[nodiscard\]\] storage::RowView view() const & noexcept | calls ; returns row_.view() · [reviewed contract](#b0009) |
| [B0010 · 39–39](../../../../../../include/crown/runtime/inspection.hpp#L39) | declares callable signatures; declares values/defaults or compile-time conditions. |  · [reviewed contract](#b0010) |
| [B0011 · 40–40](../../../../../../include/crown/runtime/inspection.hpp#L40) | Callable definition: \[\[nodiscard\]\] const resource::MemoryAccount& account() const & noexcept | calls ; returns account_ · [reviewed contract](#b0011) |
| [B0012 · 41–41](../../../../../../include/crown/runtime/inspection.hpp#L41) | declares callable signatures; declares values/defaults or compile-time conditions. |  · [reviewed contract](#b0012) |
| [B0013 · 42–42](../../../../../../include/crown/runtime/inspection.hpp#L42) | Callable definition: \[\[nodiscard\]\] bool operator==(const Row& other) const | calls ; returns row_.view()==other · [reviewed contract](#b0013) |
| [B0014 · 43–43](../../../../../../include/crown/runtime/inspection.hpp#L43) | Callable definition: \[\[nodiscard\]\] bool operator==(const InvariantKey& other) const noexcept | calls ; returns row_.view()==other.row_.view() · [reviewed contract](#b0014) |
| [B0015 · 44–47](../../../../../../include/crown/runtime/inspection.hpp#L44) | Member/declaration region. |  · [reviewed contract](#b0015) |
| [B0016 · 48–57](../../../../../../include/crown/runtime/inspection.hpp#L48) | Type/record definition: struct InvariantIssue |  · [reviewed contract](#b0016) |
| [B0017 · 58–61](../../../../../../include/crown/runtime/inspection.hpp#L58) | Type/record definition: struct InspectionOptions |  · [reviewed contract](#b0017) |
| [B0018 · 62–68](../../../../../../include/crown/runtime/inspection.hpp#L62) | Type/record definition: struct RuntimeStateStatistics |  · [reviewed contract](#b0018) |
| [B0019 · 69–80](../../../../../../include/crown/runtime/inspection.hpp#L69) | Type/record definition: struct InvariantReport | returns complete && issues.empty(); source comment (unverified): // Copies duplicate funded issue/key payload; moves transfer its actual owner. · [reviewed contract](#b0019) |
| [B0020 · 81–85](../../../../../../include/crown/runtime/inspection.hpp#L81) | Type/record definition: struct CanonicalCount |  · [reviewed contract](#b0020) |
| [B0021 · 86–92](../../../../../../include/crown/runtime/inspection.hpp#L86) | Type/record definition: struct CanonicalRecord |  · [reviewed contract](#b0021) |
| [B0022 · 93–101](../../../../../../include/crown/runtime/inspection.hpp#L93) | Type/record definition: struct CanonicalNode |  · [reviewed contract](#b0022) |
| [B0023 · 102–111](../../../../../../include/crown/runtime/inspection.hpp#L102) | Type/record definition: struct CanonicalSupportState | source comment (unverified): // Explicit ordinary DTO: copying nested rows/strings/containers may allocate. · [reviewed contract](#b0023) |
| [B0024 · 112–118](../../../../../../include/crown/runtime/inspection.hpp#L112) | Type/record definition: struct CanonicalPhysicalState |  · [reviewed contract](#b0024) |
| [B0025 · 119–124](../../../../../../include/crown/runtime/inspection.hpp#L119) | Type/record definition: struct CanonicalBucket |  · [reviewed contract](#b0025) |
| [B0026 · 125–130](../../../../../../include/crown/runtime/inspection.hpp#L125) | Type/record definition: struct CanonicalLiveFactor |  · [reviewed contract](#b0026) |
| [B0027 · 131–136](../../../../../../include/crown/runtime/inspection.hpp#L131) | Type/record definition: struct CanonicalLiveState |  · [reviewed contract](#b0027) |
| [B0028 · 137–142](../../../../../../include/crown/runtime/inspection.hpp#L137) | Type/record definition: struct CanonicalDeltaState |  · [reviewed contract](#b0028) |
| [B0029 · 143–143](../../../../../../include/crown/runtime/inspection.hpp#L143) | Closes surrounding scope/type. | source comment (unverified): // namespace crown::runtime · [reviewed contract](#b0029) |

## B0001

[Lines 1–8](../../../../../../include/crown/runtime/inspection.hpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
#pragma once
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Expose inspection value types without running invariant checks. |
| inputs / outputs | Includes model/tree, compact AccountedRow and transferable owner allocator. |
| invariants | Independent inspections run only through actual runtime barriers; these public carriers are not proof or durable admission APIs. |
| ownership | No graph allocated by inclusion; concrete owning types below retain their own payload. |
| failure | Compile-time dependency boundary only. |
| cost | No runtime action at inclusion. |
| Design | [include/crown/runtime/inspection.hpp](../../../../../../include/crown/runtime/inspection.hpp), [src/runtime/inspection_detail.hpp](../../../../../../src/runtime/inspection_detail.hpp), [src/runtime/support.cpp](../../../../../../src/runtime/support.cpp), [src/runtime/physical.cpp](../../../../../../src/runtime/physical.cpp), [src/runtime/delta.cpp](../../../../../../src/runtime/delta.cpp), [docs/invariant_memory.md](../../../../../invariant_memory.md), [docs/code_review.md](../../../../../code_review.md) |

## B0002

[Lines 9–12](../../../../../../include/crown/runtime/inspection.hpp#L9); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
enum class InvariantComponent {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Identify the runtime component of a localized issue. |
| inputs / outputs | Source/derivation/records/S/P/E/sequence/storage/live factors/parent/child/totals tags. |
| invariants | Tags locate an observed mismatch, not current-owner authority. |
| ownership | Caller owns inline numeric/tag fields; this record retains no backing runtime, rows, strings or allocation grant. |
| failure | The declaration does not validate public fields or translate failure. Actual factories/consumers perform the stated checks. |
| cost | Constant-size enum/tag, no allocation, scan or clock. Arbitrary enum casts are not admitted automatically. |
| Design | [include/crown/runtime/inspection.hpp](../../../../../../include/crown/runtime/inspection.hpp), [src/runtime/inspection_detail.hpp](../../../../../../src/runtime/inspection_detail.hpp), [src/runtime/support.cpp](../../../../../../src/runtime/support.cpp), [src/runtime/physical.cpp](../../../../../../src/runtime/physical.cpp), [src/runtime/delta.cpp](../../../../../../src/runtime/delta.cpp), [docs/invariant_memory.md](../../../../../invariant_memory.md), [docs/code_review.md](../../../../../code_review.md) |

## B0003

[Lines 13–17](../../../../../../include/crown/runtime/inspection.hpp#L13); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
enum class InvariantCode {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Identify the kind of invariant mismatch. |
| inputs / outputs | Missing/unexpected records, metadata, child/support/derivation/membership/sequence/storage/source/aggregate codes. |
| invariants | Expected/actual values remain optional; absence does not mean zero. |
| ownership | Caller owns inline numeric/tag fields; this record retains no backing runtime, rows, strings or allocation grant. |
| failure | The declaration does not validate public fields or translate failure. Actual factories/consumers perform the stated checks. |
| cost | Constant-size enum/tag, no allocation, scan or clock. Arbitrary enum casts are not admitted automatically. |
| Design | [include/crown/runtime/inspection.hpp](../../../../../../include/crown/runtime/inspection.hpp), [src/runtime/inspection_detail.hpp](../../../../../../src/runtime/inspection_detail.hpp), [src/runtime/support.cpp](../../../../../../src/runtime/support.cpp), [src/runtime/physical.cpp](../../../../../../src/runtime/physical.cpp), [src/runtime/delta.cpp](../../../../../../src/runtime/delta.cpp), [docs/invariant_memory.md](../../../../../invariant_memory.md), [docs/code_review.md](../../../../../code_review.md) |

## B0004

[Lines 18–24](../../../../../../include/crown/runtime/inspection.hpp#L18); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
inline constexpr resource::MemoryAttribution invariant_attribution{resource::MemoryOwnerKind::capture,15};
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Attribute native invariant diagnostic ownership. |
| inputs / outputs | invariant_attribution is capture:15. |
| invariants | It labels actual original-account allocations; a numeric attribution alone does not provide an allowance. |
| ownership | Caller owns inline numeric/tag fields; this record retains no backing runtime, rows, strings or allocation grant. |
| failure | The declaration does not validate public fields or translate failure. Actual factories/consumers perform the stated checks. |
| cost | Fixed inline scalar/enum/optional/array storage and bounded copies; no dynamic payload, scan, clock or allocation. |
| Design | [include/crown/runtime/inspection.hpp](../../../../../../include/crown/runtime/inspection.hpp), [src/runtime/inspection_detail.hpp](../../../../../../src/runtime/inspection_detail.hpp), [src/runtime/support.cpp](../../../../../../src/runtime/support.cpp), [src/runtime/physical.cpp](../../../../../../src/runtime/physical.cpp), [src/runtime/delta.cpp](../../../../../../src/runtime/delta.cpp), [docs/invariant_memory.md](../../../../../invariant_memory.md), [docs/code_review.md](../../../../../code_review.md) |

```text
class InvariantKey {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Own a compact detached invariant key on its actual account. |
| inputs / outputs | MemoryAccount plus move-only AccountedRow; explicit copy_of/copy constructor clone scalar/string bytes while getters borrow. |
| invariants | Empty keys require no row block. Owning copies allocate on the same account; reports keep keys valid after runtime changes without retaining runtime rows/pins. |
| ownership | Account handle retains original grant; compact row owns one native block including string bytes. Moves transfer ownership; release frees block without allocation. |
| failure | Copy/clone can throw under original cap; copy assignment privately prepares complete replacement. Default empty key creates no account. |
| cost | Copy O(columns+string bytes), one row block when nonempty; move fixed transfer, release fixed per block/account, comparison scans values. |
| Design | [include/crown/runtime/inspection.hpp](../../../../../../include/crown/runtime/inspection.hpp), [src/runtime/inspection_detail.hpp](../../../../../../src/runtime/inspection_detail.hpp), [src/runtime/support.cpp](../../../../../../src/runtime/support.cpp), [src/runtime/physical.cpp](../../../../../../src/runtime/physical.cpp), [src/runtime/delta.cpp](../../../../../../src/runtime/delta.cpp), [docs/invariant_memory.md](../../../../../invariant_memory.md), [docs/code_review.md](../../../../../code_review.md), [include/crown/storage/accounted_row.hpp](../../../../../../include/crown/storage/accounted_row.hpp), [src/storage/accounted_row.cpp](../../../../../../src/storage/accounted_row.cpp) |

```text
InvariantKey() noexcept=default;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Construct an empty invariant key. |
| inputs / outputs | Default account and empty native row. |
| invariants | Empty RowView is a valid zero-field diagnostic key; no allowance is created. |
| ownership | Owns empty value only. |
| failure | noexcept for a live readable object; borrowing does not validate lifetime or extend it. |
| cost | O(1), no allocation. |
| Design | [include/crown/runtime/inspection.hpp](../../../../../../include/crown/runtime/inspection.hpp), [src/runtime/inspection_detail.hpp](../../../../../../src/runtime/inspection_detail.hpp), [src/runtime/support.cpp](../../../../../../src/runtime/support.cpp), [src/runtime/physical.cpp](../../../../../../src/runtime/physical.cpp), [src/runtime/delta.cpp](../../../../../../src/runtime/delta.cpp), [docs/invariant_memory.md](../../../../../invariant_memory.md), [docs/code_review.md](../../../../../code_review.md) |

## B0005

[Lines 25–27](../../../../../../include/crown/runtime/inspection.hpp#L25); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
InvariantKey(const InvariantKey& other):account_(other.account_) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Deep-copy an invariant key on its retained account. |
| inputs / outputs | Copy account; clone nonempty row with invariant attribution. |
| invariants | Preserves exact typed bytes and source account; empty row bypasses allocation. |
| ownership | New row block owned independently, original preserved. |
| failure | Clone allocation failure destroys partial new key and leaves source intact. |
| cost | O(columns+string bytes) allocation/copy; old/new row blocks coexist. |
| Design | [include/crown/runtime/inspection.hpp](../../../../../../include/crown/runtime/inspection.hpp), [src/runtime/inspection_detail.hpp](../../../../../../src/runtime/inspection_detail.hpp), [src/runtime/support.cpp](../../../../../../src/runtime/support.cpp), [src/runtime/physical.cpp](../../../../../../src/runtime/physical.cpp), [src/runtime/delta.cpp](../../../../../../src/runtime/delta.cpp), [docs/invariant_memory.md](../../../../../invariant_memory.md), [docs/code_review.md](../../../../../code_review.md) |

## B0006

[Lines 28–30](../../../../../../include/crown/runtime/inspection.hpp#L28); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
InvariantKey& operator=(const InvariantKey& other) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Copy-assign invariant key with complete replacement publication. |
| inputs / outputs | Self-check; construct copy(other), then noexcept move-assign. |
| invariants | Failure cannot leave new account paired with old row bytes. |
| ownership | Temporary binds source account; publication releases destination old row/account and transfers new payload. |
| failure | Only temporary clone may throw; old destination unchanged until complete. |
| cost | O(key bytes) clone plus one old-row deallocation; self assignment O(1). |
| Design | [include/crown/runtime/inspection.hpp](../../../../../../include/crown/runtime/inspection.hpp), [src/runtime/inspection_detail.hpp](../../../../../../src/runtime/inspection_detail.hpp), [src/runtime/support.cpp](../../../../../../src/runtime/support.cpp), [src/runtime/physical.cpp](../../../../../../src/runtime/physical.cpp), [src/runtime/delta.cpp](../../../../../../src/runtime/delta.cpp), [docs/invariant_memory.md](../../../../../invariant_memory.md), [docs/code_review.md](../../../../../code_review.md) |

## B0007

[Lines 31–32](../../../../../../include/crown/runtime/inspection.hpp#L31); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
InvariantKey(InvariantKey&&) noexcept=default;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Move-construct an invariant key. |
| inputs / outputs | Default noexcept move transfers MemoryAccount and AccountedRow. |
| invariants | Moved-from key is destructible/assignable and has ordinary empty/moved fields, not a fresh grant. |
| ownership | Destination adopts existing row block; assignment releases prior row/account. |
| failure | noexcept; no copy fallback. |
| cost | Fixed ownership transfer plus old-block release on assignment, no allocation. |
| Design | [include/crown/runtime/inspection.hpp](../../../../../../include/crown/runtime/inspection.hpp), [src/runtime/inspection_detail.hpp](../../../../../../src/runtime/inspection_detail.hpp), [src/runtime/support.cpp](../../../../../../src/runtime/support.cpp), [src/runtime/physical.cpp](../../../../../../src/runtime/physical.cpp), [src/runtime/delta.cpp](../../../../../../src/runtime/delta.cpp), [docs/invariant_memory.md](../../../../../invariant_memory.md), [docs/code_review.md](../../../../../code_review.md) |

```text
InvariantKey& operator=(InvariantKey&&) noexcept=default;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Move-assign an invariant key. |
| inputs / outputs | Default noexcept move transfers MemoryAccount and AccountedRow. |
| invariants | Moved-from key is destructible/assignable and has ordinary empty/moved fields, not a fresh grant. |
| ownership | Destination adopts existing row block; assignment releases prior row/account. |
| failure | noexcept; no copy fallback. |
| cost | Fixed ownership transfer plus old-block release on assignment, no allocation. |
| Design | [include/crown/runtime/inspection.hpp](../../../../../../include/crown/runtime/inspection.hpp), [src/runtime/inspection_detail.hpp](../../../../../../src/runtime/inspection_detail.hpp), [src/runtime/support.cpp](../../../../../../src/runtime/support.cpp), [src/runtime/physical.cpp](../../../../../../src/runtime/physical.cpp), [src/runtime/delta.cpp](../../../../../../src/runtime/delta.cpp), [docs/invariant_memory.md](../../../../../invariant_memory.md), [docs/code_review.md](../../../../../code_review.md) |

## B0008

[Lines 33–37](../../../../../../include/crown/runtime/inspection.hpp#L33); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
[[nodiscard]] static InvariantKey copy_of(const resource::MemoryAccount& account,storage::RowView values) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Copy borrowed values into a detached native invariant key. |
| inputs / outputs | Account and RowView yield owned compact row only when values nonempty. |
| invariants | Borrow must remain stable during copy; no export to ordinary Row is needed. |
| ownership | Retains account and newly copied block; source view not retained. |
| failure | Allocation/size/account failures propagate; partial result unwinds. |
| cost | O(columns+string bytes) one-block allocation/copy, empty O(1). |
| Design | [include/crown/runtime/inspection.hpp](../../../../../../include/crown/runtime/inspection.hpp), [src/runtime/inspection_detail.hpp](../../../../../../src/runtime/inspection_detail.hpp), [src/runtime/support.cpp](../../../../../../src/runtime/support.cpp), [src/runtime/physical.cpp](../../../../../../src/runtime/physical.cpp), [src/runtime/delta.cpp](../../../../../../src/runtime/delta.cpp), [docs/invariant_memory.md](../../../../../invariant_memory.md), [docs/code_review.md](../../../../../code_review.md) |

## B0009

[Lines 38–38](../../../../../../include/crown/runtime/inspection.hpp#L38); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
[[nodiscard]] storage::RowView view() const & noexcept{return row_.view();}
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Borrow native invariant key values. |
| inputs / outputs | Returns row_.view() for an lvalue key. |
| invariants | View carries scalar/string borrows, no pin or row owner. |
| ownership | Keep key alive and unchanged; view does not retain block. |
| failure | noexcept for a live readable object; borrowing does not validate lifetime or extend it. |
| cost | O(1) fixed member/view lookup; no allocation or clock. |
| Design | [include/crown/runtime/inspection.hpp](../../../../../../include/crown/runtime/inspection.hpp), [src/runtime/inspection_detail.hpp](../../../../../../src/runtime/inspection_detail.hpp), [src/runtime/support.cpp](../../../../../../src/runtime/support.cpp), [src/runtime/physical.cpp](../../../../../../src/runtime/physical.cpp), [src/runtime/delta.cpp](../../../../../../src/runtime/delta.cpp), [docs/invariant_memory.md](../../../../../invariant_memory.md), [docs/code_review.md](../../../../../code_review.md) |

## B0010

[Lines 39–39](../../../../../../include/crown/runtime/inspection.hpp#L39); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
storage::RowView view() const &&=delete;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Reject a borrowed key view from a temporary. |
| inputs / outputs | Rvalue view() is deleted. |
| invariants | Compiler rejects a common immediate dangling-view path; lvalue lifetime still caller-owned. |
| ownership | No owner returned. |
| failure | Compile-time rejection, not runtime catch. |
| cost | No runtime cost. |
| Design | [include/crown/runtime/inspection.hpp](../../../../../../include/crown/runtime/inspection.hpp), [src/runtime/inspection_detail.hpp](../../../../../../src/runtime/inspection_detail.hpp), [src/runtime/support.cpp](../../../../../../src/runtime/support.cpp), [src/runtime/physical.cpp](../../../../../../src/runtime/physical.cpp), [src/runtime/delta.cpp](../../../../../../src/runtime/delta.cpp), [docs/invariant_memory.md](../../../../../invariant_memory.md), [docs/code_review.md](../../../../../code_review.md) |

## B0011

[Lines 40–40](../../../../../../include/crown/runtime/inspection.hpp#L40); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
[[nodiscard]] const resource::MemoryAccount& account() const & noexcept{return account_;}
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Borrow invariant key account binding. |
| inputs / outputs | Returns const MemoryAccount& for lvalue key. |
| invariants | This is actual retained allocation authority, distinct from numeric diagnostic labels. |
| ownership | Reference borrows key; explicitly copying MemoryAccount retains the same grant. |
| failure | noexcept for a live readable object; borrowing does not validate lifetime or extend it. |
| cost | O(1) fixed member/view lookup; no allocation or clock. |
| Design | [include/crown/runtime/inspection.hpp](../../../../../../include/crown/runtime/inspection.hpp), [src/runtime/inspection_detail.hpp](../../../../../../src/runtime/inspection_detail.hpp), [src/runtime/support.cpp](../../../../../../src/runtime/support.cpp), [src/runtime/physical.cpp](../../../../../../src/runtime/physical.cpp), [src/runtime/delta.cpp](../../../../../../src/runtime/delta.cpp), [docs/invariant_memory.md](../../../../../invariant_memory.md), [docs/code_review.md](../../../../../code_review.md) |

## B0012

[Lines 41–41](../../../../../../include/crown/runtime/inspection.hpp#L41); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
const resource::MemoryAccount& account() const &&=delete;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Reject an account reference from a temporary invariant key. |
| inputs / outputs | Rvalue account() deleted. |
| invariants | Prevents reference escaping an immediately destroyed key. |
| ownership | No ownership transfer. |
| failure | Compile-time rejection. |
| cost | No runtime cost. |
| Design | [include/crown/runtime/inspection.hpp](../../../../../../include/crown/runtime/inspection.hpp), [src/runtime/inspection_detail.hpp](../../../../../../src/runtime/inspection_detail.hpp), [src/runtime/support.cpp](../../../../../../src/runtime/support.cpp), [src/runtime/physical.cpp](../../../../../../src/runtime/physical.cpp), [src/runtime/delta.cpp](../../../../../../src/runtime/delta.cpp), [docs/invariant_memory.md](../../../../../invariant_memory.md), [docs/code_review.md](../../../../../code_review.md) |

## B0013

[Lines 42–42](../../../../../../include/crown/runtime/inspection.hpp#L42); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
[[nodiscard]] bool operator==(const Row& other) const{return row_.view()==other;}
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Compare a native key with an ordinary caller row without export. |
| inputs / outputs | RowView compares types/values against borrowed ordinary Value cells. |
| invariants | Caller row must contain supported native scalar values; no key mutation or factory authority follows. |
| ownership | Reads both operands; retains neither. |
| failure | Signature may propagate scalar-borrow/conversion contract failures; no handler. |
| cost | O(columns+compared string bytes), no ordinary key export. |
| Design | [include/crown/runtime/inspection.hpp](../../../../../../include/crown/runtime/inspection.hpp), [src/runtime/inspection_detail.hpp](../../../../../../src/runtime/inspection_detail.hpp), [src/runtime/support.cpp](../../../../../../src/runtime/support.cpp), [src/runtime/physical.cpp](../../../../../../src/runtime/physical.cpp), [src/runtime/delta.cpp](../../../../../../src/runtime/delta.cpp), [docs/invariant_memory.md](../../../../../invariant_memory.md), [docs/code_review.md](../../../../../code_review.md), [src/storage/accounted_row.cpp](../../../../../../src/storage/accounted_row.cpp) |

## B0014

[Lines 43–43](../../../../../../include/crown/runtime/inspection.hpp#L43); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
[[nodiscard]] bool operator==(const InvariantKey& other) const noexcept{return row_.view()==other.row_.view();}
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Compare two native invariant keys. |
| inputs / outputs | RowView equality compares exact typed values. |
| invariants | Different account/owner identity does not affect value equality. |
| ownership | Reads key blocks synchronously; no retention. |
| failure | noexcept for a live readable object; borrowing does not validate lifetime or extend it. |
| cost | O(columns+compared string bytes); no allocation or clock. |
| Design | [include/crown/runtime/inspection.hpp](../../../../../../include/crown/runtime/inspection.hpp), [src/runtime/inspection_detail.hpp](../../../../../../src/runtime/inspection_detail.hpp), [src/runtime/support.cpp](../../../../../../src/runtime/support.cpp), [src/runtime/physical.cpp](../../../../../../src/runtime/physical.cpp), [src/runtime/delta.cpp](../../../../../../src/runtime/delta.cpp), [docs/invariant_memory.md](../../../../../invariant_memory.md), [docs/code_review.md](../../../../../code_review.md) |

## B0015

[Lines 44–47](../../../../../../include/crown/runtime/inspection.hpp#L44); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
resource::MemoryAccount account_;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Retain invariant key account and compact row ownership. |
| inputs / outputs | Private account_ and row_ back the native value. |
| invariants | Row clone and allocation ownership stay paired; no mutable runtime pointer. |
| ownership | Final block/account release uses original allocator accounting; row has inline scalar descriptors/string bytes in one block. |
| failure | Nonthrowing release; invalid allocator contract is not recoverable via a new grant. |
| cost | One block free and account release; no per-string allocation cleanup. |
| Design | [include/crown/runtime/inspection.hpp](../../../../../../include/crown/runtime/inspection.hpp), [src/runtime/inspection_detail.hpp](../../../../../../src/runtime/inspection_detail.hpp), [src/runtime/support.cpp](../../../../../../src/runtime/support.cpp), [src/runtime/physical.cpp](../../../../../../src/runtime/physical.cpp), [src/runtime/delta.cpp](../../../../../../src/runtime/delta.cpp), [docs/invariant_memory.md](../../../../../invariant_memory.md), [docs/code_review.md](../../../../../code_review.md), [src/resource/memory.cpp](../../../../../../src/resource/memory.cpp) |

## B0016

[Lines 48–57](../../../../../../include/crown/runtime/inspection.hpp#L48); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct InvariantIssue {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Own a localized invariant issue and optional expected/actual facts. |
| inputs / outputs | Code/component plus optional table/occurrence/node/child-slot, native InvariantKey and optional counters. |
| invariants | Keys/facts are copied diagnostics; flags and numeric IDs do not admit runtime state. Incomplete reports cannot be treated as valid. |
| ownership | Key owns its compact native block/account; other fields inline. Copies deep-copy the key; moves transfer. |
| failure | Key-copy allocation failure propagates; no hidden catch. |
| cost | O(key bytes) owning copy, fixed numeric operations and one key-block release. |
| Design | [include/crown/runtime/inspection.hpp](../../../../../../include/crown/runtime/inspection.hpp), [src/runtime/inspection_detail.hpp](../../../../../../src/runtime/inspection_detail.hpp), [src/runtime/support.cpp](../../../../../../src/runtime/support.cpp), [src/runtime/physical.cpp](../../../../../../src/runtime/physical.cpp), [src/runtime/delta.cpp](../../../../../../src/runtime/delta.cpp), [docs/invariant_memory.md](../../../../../invariant_memory.md), [docs/code_review.md](../../../../../code_review.md) |

## B0017

[Lines 58–61](../../../../../../include/crown/runtime/inspection.hpp#L58); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct InspectionOptions {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Bound explicit invariant-inspection work and retained issue count. |
| inputs / outputs | Optional logical work_limit default1M and issue_limit128. |
| invariants | These are coarse diagnostic action limits, not CPU/allocator-byte limits. Exhaustion marks complete=false; actual account independently caps diagnostic scratch. |
| ownership | Caller owns inline numeric/tag fields; this record retains no backing runtime, rows, strings or allocation grant. |
| failure | The declaration does not validate public fields or translate failure. Actual factories/consumers perform the stated checks. |
| cost | Fixed inline scalar/enum/optional/array storage and bounded copies; no dynamic payload, scan, clock or allocation. |
| Design | [include/crown/runtime/inspection.hpp](../../../../../../include/crown/runtime/inspection.hpp), [src/runtime/inspection_detail.hpp](../../../../../../src/runtime/inspection_detail.hpp), [src/runtime/support.cpp](../../../../../../src/runtime/support.cpp), [src/runtime/physical.cpp](../../../../../../src/runtime/physical.cpp), [src/runtime/delta.cpp](../../../../../../src/runtime/delta.cpp), [docs/invariant_memory.md](../../../../../invariant_memory.md), [docs/code_review.md](../../../../../code_review.md) |

## B0018

[Lines 62–68](../../../../../../include/crown/runtime/inspection.hpp#L62); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct RuntimeStateStatistics {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Carry observed native population totals from inspection. |
| inputs / outputs | Fixed source/derivation/native/generalized/S/P/E/flags/storage/index/live factor and bucket counts. |
| invariants | Counts describe local populations and may be partial when report.complete=false; neither answer cardinality nor memory bytes follow from their sum. |
| ownership | Caller owns inline numeric/tag fields; this record retains no backing runtime, rows, strings or allocation grant. |
| failure | The declaration does not validate public fields or translate failure. Actual factories/consumers perform the stated checks. |
| cost | Fixed inline scalar/enum/optional/array storage and bounded copies; no dynamic payload, scan, clock or allocation. |
| Design | [include/crown/runtime/inspection.hpp](../../../../../../include/crown/runtime/inspection.hpp), [src/runtime/inspection_detail.hpp](../../../../../../src/runtime/inspection_detail.hpp), [src/runtime/support.cpp](../../../../../../src/runtime/support.cpp), [src/runtime/physical.cpp](../../../../../../src/runtime/physical.cpp), [src/runtime/delta.cpp](../../../../../../src/runtime/delta.cpp), [docs/invariant_memory.md](../../../../../invariant_memory.md), [docs/code_review.md](../../../../../code_review.md) |

## B0019

[Lines 69–80](../../../../../../include/crown/runtime/inspection.hpp#L69); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct InvariantReport {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Own an invariant report and its funded localized keys. |
| inputs / outputs | complete/work/statistics plus OwnerAllocator&lt;InvariantIssue&gt; vector; account constructor binds capture:15; valid checks only complete&&issues.empty. |
| invariants | Public flags/default empty reports do not prove a native inspection ran. Actual runtime inspection controls completeness; exhaustion returns incomplete, OOM propagates. |
| ownership | Issues/key blocks own original-account payload. Copying vector deep-copies issue keys; moves transfer vector/account; scratch expected-state maps are released before factory return. |
| failure | Copy/append can allocate/throw; no blanket noexcept/constant-copy claim. Default construction binds no allowance. |
| cost | O(issue count+key bytes) copies/allocations, teardown visits issues and frees key/vector blocks; actual independent recomputation scans/allocates separately. |
| Design | [include/crown/runtime/inspection.hpp](../../../../../../include/crown/runtime/inspection.hpp), [src/runtime/inspection_detail.hpp](../../../../../../src/runtime/inspection_detail.hpp), [src/runtime/support.cpp](../../../../../../src/runtime/support.cpp), [src/runtime/physical.cpp](../../../../../../src/runtime/physical.cpp), [src/runtime/delta.cpp](../../../../../../src/runtime/delta.cpp), [docs/invariant_memory.md](../../../../../invariant_memory.md), [docs/code_review.md](../../../../../code_review.md) |

```text
InvariantReport()=default;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Construct an empty unbound report carrier. |
| inputs / outputs | Defaults complete=true, work0, empty issues vector with default allocator. |
| invariants | valid() on this value means its flags agree, not that a live native owner was inspected. |
| ownership | Owns no payload/grant. |
| failure | No issue allocation until caller tries to populate; native inspectors use explicit account constructor. |
| cost | Fixed empty initialization. |
| Design | [include/crown/runtime/inspection.hpp](../../../../../../include/crown/runtime/inspection.hpp), [src/runtime/inspection_detail.hpp](../../../../../../src/runtime/inspection_detail.hpp), [src/runtime/support.cpp](../../../../../../src/runtime/support.cpp), [src/runtime/physical.cpp](../../../../../../src/runtime/physical.cpp), [src/runtime/delta.cpp](../../../../../../src/runtime/delta.cpp), [docs/invariant_memory.md](../../../../../invariant_memory.md), [docs/code_review.md](../../../../../code_review.md) |

```text
explicit InvariantReport(const resource::MemoryAccount& account)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Bind an empty report to an actual account. |
| inputs / outputs | Initializes issues allocator capture purpose/capture:15. |
| invariants | Does not reserve issues or run inspection. |
| ownership | Vector allocator retains supplied grant; no payload allocation here. |
| failure | Allocator binding itself no allocation; later additions may fail. |
| cost | Fixed handle setup. |
| Design | [include/crown/runtime/inspection.hpp](../../../../../../include/crown/runtime/inspection.hpp), [src/runtime/inspection_detail.hpp](../../../../../../src/runtime/inspection_detail.hpp), [src/runtime/support.cpp](../../../../../../src/runtime/support.cpp), [src/runtime/physical.cpp](../../../../../../src/runtime/physical.cpp), [src/runtime/delta.cpp](../../../../../../src/runtime/delta.cpp), [docs/invariant_memory.md](../../../../../invariant_memory.md), [docs/code_review.md](../../../../../code_review.md) |

```text
[[nodiscard]] bool valid() const noexcept { return complete && issues.empty(); }
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Test report completeness and absence of issues. |
| inputs / outputs | Returns complete && issues.empty(). |
| invariants | This checks public report fields only; true is not proof, durability or authenticated native-source authority. |
| ownership | Reads report only, returns scalar. |
| failure | noexcept for a live readable object; borrowing does not validate lifetime or extend it. |
| cost | O(1) fixed member/view lookup; no allocation or clock. |
| Design | [include/crown/runtime/inspection.hpp](../../../../../../include/crown/runtime/inspection.hpp), [src/runtime/inspection_detail.hpp](../../../../../../src/runtime/inspection_detail.hpp), [src/runtime/support.cpp](../../../../../../src/runtime/support.cpp), [src/runtime/physical.cpp](../../../../../../src/runtime/physical.cpp), [src/runtime/delta.cpp](../../../../../../src/runtime/delta.cpp), [docs/invariant_memory.md](../../../../../invariant_memory.md), [docs/code_review.md](../../../../../code_review.md) |

## B0020

[Lines 81–85](../../../../../../include/crown/runtime/inspection.hpp#L81); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct CanonicalCount {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Export CanonicalCount for human comparison. |
| inputs / outputs | ordinary Row key and U64 count. |
| invariants | Count is a local key multiplicity, not global query answer count. |
| ownership | Owns ordinary caller-allocator rows/strings/vectors/set nodes described above. Copies deep-copy those members; it is neither a cheap shared handle nor a native owner capability. |
| failure | Owning construction/copy can allocate and throw. Ordinary aggregate/memberwise assignment has no special whole-record publication guarantee; no catch/fallback is added. |
| cost | Copy O(key bytes), comparison scans row/count. Release row Values/string owners. |
| Design | [include/crown/runtime/inspection.hpp](../../../../../../include/crown/runtime/inspection.hpp), [src/runtime/inspection_detail.hpp](../../../../../../src/runtime/inspection_detail.hpp), [src/runtime/support.cpp](../../../../../../src/runtime/support.cpp), [src/runtime/physical.cpp](../../../../../../src/runtime/physical.cpp), [src/runtime/delta.cpp](../../../../../../src/runtime/delta.cpp), [docs/invariant_memory.md](../../../../../invariant_memory.md), [docs/code_review.md](../../../../../code_review.md) |

```text
bool operator==(const CanonicalCount&) const=default;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Compare canonical count by stored members. |
| inputs / outputs | Default equality compares key/count. |
| invariants | Equality of exported facts does not prove current native/source/durable identity, report authenticity or minimum-height authority. |
| ownership | Reads both operands synchronously and retains no backing. |
| failure | Uses member comparison; no handler or admission/validation is added by =default. |
| cost | O(compared nested values/string bytes/container elements), with early exit; no native owner scan. |
| Design | [include/crown/runtime/inspection.hpp](../../../../../../include/crown/runtime/inspection.hpp), [src/runtime/inspection_detail.hpp](../../../../../../src/runtime/inspection_detail.hpp), [src/runtime/support.cpp](../../../../../../src/runtime/support.cpp), [src/runtime/physical.cpp](../../../../../../src/runtime/physical.cpp), [src/runtime/delta.cpp](../../../../../../src/runtime/delta.cpp), [docs/invariant_memory.md](../../../../../invariant_memory.md), [docs/code_review.md](../../../../../code_review.md) |

## B0021

[Lines 86–92](../../../../../../include/crown/runtime/inspection.hpp#L86); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct CanonicalRecord {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Export CanonicalRecord for human comparison. |
| inputs / outputs | ordinary Row values, satisfied count, vector&lt;bool&gt; child flags and survives flag. |
| invariants | Child flags are explicit copied diagnostics, not support-table ownership. |
| ownership | Owns ordinary caller-allocator rows/strings/vectors/set nodes described above. Copies deep-copy those members; it is neither a cheap shared handle nor a native owner capability. |
| failure | Owning construction/copy can allocate and throw. Ordinary aggregate/memberwise assignment has no special whole-record publication guarantee; no catch/fallback is added. |
| cost | Copy O(row bytes+child flags), equality scans both. Release row/string and flag-vector storage. |
| Design | [include/crown/runtime/inspection.hpp](../../../../../../include/crown/runtime/inspection.hpp), [src/runtime/inspection_detail.hpp](../../../../../../src/runtime/inspection_detail.hpp), [src/runtime/support.cpp](../../../../../../src/runtime/support.cpp), [src/runtime/physical.cpp](../../../../../../src/runtime/physical.cpp), [src/runtime/delta.cpp](../../../../../../src/runtime/delta.cpp), [docs/invariant_memory.md](../../../../../invariant_memory.md), [docs/code_review.md](../../../../../code_review.md) |

```text
bool operator==(const CanonicalRecord&) const=default;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Compare canonical record by stored members. |
| inputs / outputs | Default equality compares values/satisfied/child_present/survives. |
| invariants | Equality of exported facts does not prove current native/source/durable identity, report authenticity or minimum-height authority. |
| ownership | Reads both operands synchronously and retains no backing. |
| failure | Uses member comparison; no handler or admission/validation is added by =default. |
| cost | O(compared nested values/string bytes/container elements), with early exit; no native owner scan. |
| Design | [include/crown/runtime/inspection.hpp](../../../../../../include/crown/runtime/inspection.hpp), [src/runtime/inspection_detail.hpp](../../../../../../src/runtime/inspection_detail.hpp), [src/runtime/support.cpp](../../../../../../src/runtime/support.cpp), [src/runtime/physical.cpp](../../../../../../src/runtime/physical.cpp), [src/runtime/delta.cpp](../../../../../../src/runtime/delta.cpp), [docs/invariant_memory.md](../../../../../invariant_memory.md), [docs/code_review.md](../../../../../code_review.md) |

## B0022

[Lines 93–101](../../../../../../include/crown/runtime/inspection.hpp#L93); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct CanonicalNode {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Export CanonicalNode for human comparison. |
| inputs / outputs | node/kind, record vector, survivors Relation, parent count vector and optional visible counts. |
| invariants | Absent visible population differs from an empty existing visible population. Node state is an exported diagnostic DTO. |
| ownership | Owns ordinary caller-allocator rows/strings/vectors/set nodes described above. Copies deep-copy those members; it is neither a cheap shared handle nor a native owner capability. |
| failure | Owning construction/copy can allocate and throw. Ordinary aggregate/memberwise assignment has no special whole-record publication guarantee; no catch/fallback is added. |
| cost | Copy O(all nested rows/flags/counts); Relation copies allocate tree nodes, equality traverses contents. Teardown visits nested rows/Relation nodes/count entries and frees their buffers. |
| Design | [include/crown/runtime/inspection.hpp](../../../../../../include/crown/runtime/inspection.hpp), [src/runtime/inspection_detail.hpp](../../../../../../src/runtime/inspection_detail.hpp), [src/runtime/support.cpp](../../../../../../src/runtime/support.cpp), [src/runtime/physical.cpp](../../../../../../src/runtime/physical.cpp), [src/runtime/delta.cpp](../../../../../../src/runtime/delta.cpp), [docs/invariant_memory.md](../../../../../invariant_memory.md), [docs/code_review.md](../../../../../code_review.md) |

```text
bool operator==(const CanonicalNode&) const=default;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Compare canonical node by stored members. |
| inputs / outputs | Default equality compares all node/record/S/P/E fields. |
| invariants | Equality of exported facts does not prove current native/source/durable identity, report authenticity or minimum-height authority. |
| ownership | Reads both operands synchronously and retains no backing. |
| failure | Uses member comparison; no handler or admission/validation is added by =default. |
| cost | O(compared nested values/string bytes/container elements), with early exit; no native owner scan. |
| Design | [include/crown/runtime/inspection.hpp](../../../../../../include/crown/runtime/inspection.hpp), [src/runtime/inspection_detail.hpp](../../../../../../src/runtime/inspection_detail.hpp), [src/runtime/support.cpp](../../../../../../src/runtime/support.cpp), [src/runtime/physical.cpp](../../../../../../src/runtime/physical.cpp), [src/runtime/delta.cpp](../../../../../../src/runtime/delta.cpp), [docs/invariant_memory.md](../../../../../invariant_memory.md), [docs/code_review.md](../../../../../code_review.md) |

## B0023

[Lines 102–111](../../../../../../include/crown/runtime/inspection.hpp#L102); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct CanonicalSupportState {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Export CanonicalSupportState for human comparison. |
| inputs / outputs | physical hash/arithmetic strings, catalog version/sequence/answer and vector&lt;CanonicalNode&gt;. |
| invariants | Arithmetic/hash labels and has_answer are copied facts, not native admission/proof credentials. |
| ownership | Owns ordinary caller-allocator rows/strings/vectors/set nodes described above. Copies deep-copy those members; it is neither a cheap shared handle nor a native owner capability. |
| failure | Owning construction/copy can allocate and throw. Ordinary aggregate/memberwise assignment has no special whole-record publication guarantee; no catch/fallback is added. |
| cost | Copy O(strings+full nested support DTO); actual factory scans and sorts per-node records/counts. Release all nested node/row/tree/vector owners. |
| Design | [include/crown/runtime/inspection.hpp](../../../../../../include/crown/runtime/inspection.hpp), [src/runtime/inspection_detail.hpp](../../../../../../src/runtime/inspection_detail.hpp), [src/runtime/support.cpp](../../../../../../src/runtime/support.cpp), [src/runtime/physical.cpp](../../../../../../src/runtime/physical.cpp), [src/runtime/delta.cpp](../../../../../../src/runtime/delta.cpp), [docs/invariant_memory.md](../../../../../invariant_memory.md), [docs/code_review.md](../../../../../code_review.md) |

```text
bool operator==(const CanonicalSupportState&) const=default;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Compare support export by stored members. |
| inputs / outputs | Default equality compares hash/version/sequence/answer/nodes/arithmetic. |
| invariants | Equality of exported facts does not prove current native/source/durable identity, report authenticity or minimum-height authority. |
| ownership | Reads both operands synchronously and retains no backing. |
| failure | Uses member comparison; no handler or admission/validation is added by =default. |
| cost | O(compared nested values/string bytes/container elements), with early exit; no native owner scan. |
| Design | [include/crown/runtime/inspection.hpp](../../../../../../include/crown/runtime/inspection.hpp), [src/runtime/inspection_detail.hpp](../../../../../../src/runtime/inspection_detail.hpp), [src/runtime/support.cpp](../../../../../../src/runtime/support.cpp), [src/runtime/physical.cpp](../../../../../../src/runtime/physical.cpp), [src/runtime/delta.cpp](../../../../../../src/runtime/delta.cpp), [docs/invariant_memory.md](../../../../../invariant_memory.md), [docs/code_review.md](../../../../../code_review.md) |

## B0024

[Lines 112–118](../../../../../../include/crown/runtime/inspection.hpp#L112); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct CanonicalPhysicalState {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Export CanonicalPhysicalState for human comparison. |
| inputs / outputs | CanonicalSupportState, committed sequence, vector&lt;Relation&gt; sources and per-occurrence count vectors. |
| invariants | Sources and derivations are distinct full-row and projected populations. |
| ownership | Owns ordinary caller-allocator rows/strings/vectors/set nodes described above. Copies deep-copy those members; it is neither a cheap shared handle nor a native owner capability. |
| failure | Owning construction/copy can allocate and throw. Ordinary aggregate/memberwise assignment has no special whole-record publication guarantee; no catch/fallback is added. |
| cost | Copy O(exported source/support/derivation bytes); factory exports actual source snapshot and occurrence counts. Teardown traverses copied relations/rows and nested support graph. |
| Design | [include/crown/runtime/inspection.hpp](../../../../../../include/crown/runtime/inspection.hpp), [src/runtime/inspection_detail.hpp](../../../../../../src/runtime/inspection_detail.hpp), [src/runtime/support.cpp](../../../../../../src/runtime/support.cpp), [src/runtime/physical.cpp](../../../../../../src/runtime/physical.cpp), [src/runtime/delta.cpp](../../../../../../src/runtime/delta.cpp), [docs/invariant_memory.md](../../../../../invariant_memory.md), [docs/code_review.md](../../../../../code_review.md) |

```text
bool operator==(const CanonicalPhysicalState&) const=default;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Compare physical export by stored members. |
| inputs / outputs | Default equality compares support/sequence/sources/derivations. |
| invariants | Equality of exported facts does not prove current native/source/durable identity, report authenticity or minimum-height authority. |
| ownership | Reads both operands synchronously and retains no backing. |
| failure | Uses member comparison; no handler or admission/validation is added by =default. |
| cost | O(compared nested values/string bytes/container elements), with early exit; no native owner scan. |
| Design | [include/crown/runtime/inspection.hpp](../../../../../../include/crown/runtime/inspection.hpp), [src/runtime/inspection_detail.hpp](../../../../../../src/runtime/inspection_detail.hpp), [src/runtime/support.cpp](../../../../../../src/runtime/support.cpp), [src/runtime/physical.cpp](../../../../../../src/runtime/physical.cpp), [src/runtime/delta.cpp](../../../../../../src/runtime/delta.cpp), [docs/invariant_memory.md](../../../../../invariant_memory.md), [docs/code_review.md](../../../../../code_review.md) |

## B0025

[Lines 119–124](../../../../../../include/crown/runtime/inspection.hpp#L119); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct CanonicalBucket {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Export CanonicalBucket for human comparison. |
| inputs / outputs | ordinary key Row, numeric count and rows Relation. |
| invariants | Bucket count and member-row population are separate diagnostics. |
| ownership | Owns ordinary caller-allocator rows/strings/vectors/set nodes described above. Copies deep-copy those members; it is neither a cheap shared handle nor a native owner capability. |
| failure | Owning construction/copy can allocate and throw. Ordinary aggregate/memberwise assignment has no special whole-record publication guarantee; no catch/fallback is added. |
| cost | Copy O(key/member bytes+tree nodes); equality compares key/count/Relation. Release key strings and member Relation nodes. |
| Design | [include/crown/runtime/inspection.hpp](../../../../../../include/crown/runtime/inspection.hpp), [src/runtime/inspection_detail.hpp](../../../../../../src/runtime/inspection_detail.hpp), [src/runtime/support.cpp](../../../../../../src/runtime/support.cpp), [src/runtime/physical.cpp](../../../../../../src/runtime/physical.cpp), [src/runtime/delta.cpp](../../../../../../src/runtime/delta.cpp), [docs/invariant_memory.md](../../../../../invariant_memory.md), [docs/code_review.md](../../../../../code_review.md) |

```text
bool operator==(const CanonicalBucket&) const=default;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Compare bucket export by stored members. |
| inputs / outputs | Default equality compares key/count/rows. |
| invariants | Equality of exported facts does not prove current native/source/durable identity, report authenticity or minimum-height authority. |
| ownership | Reads both operands synchronously and retains no backing. |
| failure | Uses member comparison; no handler or admission/validation is added by =default. |
| cost | O(compared nested values/string bytes/container elements), with early exit; no native owner scan. |
| Design | [include/crown/runtime/inspection.hpp](../../../../../../include/crown/runtime/inspection.hpp), [src/runtime/inspection_detail.hpp](../../../../../../src/runtime/inspection_detail.hpp), [src/runtime/support.cpp](../../../../../../src/runtime/support.cpp), [src/runtime/physical.cpp](../../../../../../src/runtime/physical.cpp), [src/runtime/delta.cpp](../../../../../../src/runtime/delta.cpp), [docs/invariant_memory.md](../../../../../invariant_memory.md), [docs/code_review.md](../../../../../code_review.md) |

## B0026

[Lines 125–130](../../../../../../include/crown/runtime/inspection.hpp#L125); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct CanonicalLiveFactor {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Export CanonicalLiveFactor for human comparison. |
| inputs / outputs | node, rows Relation and parent/child CanonicalBucket vectors. |
| invariants | Copied live factor graph has no cursor pin or mutable owner reference. |
| ownership | Owns ordinary caller-allocator rows/strings/vectors/set nodes described above. Copies deep-copy those members; it is neither a cheap shared handle nor a native owner capability. |
| failure | Owning construction/copy can allocate and throw. Ordinary aggregate/memberwise assignment has no special whole-record publication guarantee; no catch/fallback is added. |
| cost | Copy O(factor/bucket/member bytes); equality walks nested containers. Release all copied relation/bucket owners. |
| Design | [include/crown/runtime/inspection.hpp](../../../../../../include/crown/runtime/inspection.hpp), [src/runtime/inspection_detail.hpp](../../../../../../src/runtime/inspection_detail.hpp), [src/runtime/support.cpp](../../../../../../src/runtime/support.cpp), [src/runtime/physical.cpp](../../../../../../src/runtime/physical.cpp), [src/runtime/delta.cpp](../../../../../../src/runtime/delta.cpp), [docs/invariant_memory.md](../../../../../invariant_memory.md), [docs/code_review.md](../../../../../code_review.md) |

```text
bool operator==(const CanonicalLiveFactor&) const=default;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Compare live factor by stored members. |
| inputs / outputs | Default equality compares node/rows/parents/children. |
| invariants | Equality of exported facts does not prove current native/source/durable identity, report authenticity or minimum-height authority. |
| ownership | Reads both operands synchronously and retains no backing. |
| failure | Uses member comparison; no handler or admission/validation is added by =default. |
| cost | O(compared nested values/string bytes/container elements), with early exit; no native owner scan. |
| Design | [include/crown/runtime/inspection.hpp](../../../../../../include/crown/runtime/inspection.hpp), [src/runtime/inspection_detail.hpp](../../../../../../src/runtime/inspection_detail.hpp), [src/runtime/support.cpp](../../../../../../src/runtime/support.cpp), [src/runtime/physical.cpp](../../../../../../src/runtime/physical.cpp), [src/runtime/delta.cpp](../../../../../../src/runtime/delta.cpp), [docs/invariant_memory.md](../../../../../invariant_memory.md), [docs/code_review.md](../../../../../code_review.md) |

## B0027

[Lines 131–136](../../../../../../include/crown/runtime/inspection.hpp#L131); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct CanonicalLiveState {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Export CanonicalLiveState for human comparison. |
| inputs / outputs | sequence, live-factor vector and row/parent/child totals. |
| invariants | Totals describe exported live image, not current source authority. |
| ownership | Owns ordinary caller-allocator rows/strings/vectors/set nodes described above. Copies deep-copy those members; it is neither a cheap shared handle nor a native owner capability. |
| failure | Owning construction/copy can allocate and throw. Ordinary aggregate/memberwise assignment has no special whole-record publication guarantee; no catch/fallback is added. |
| cost | Copy O(all factor/bucket rows); actual factory enumerates native live image. Teardown visits factor graph and frees ordinary nodes/arrays. |
| Design | [include/crown/runtime/inspection.hpp](../../../../../../include/crown/runtime/inspection.hpp), [src/runtime/inspection_detail.hpp](../../../../../../src/runtime/inspection_detail.hpp), [src/runtime/support.cpp](../../../../../../src/runtime/support.cpp), [src/runtime/physical.cpp](../../../../../../src/runtime/physical.cpp), [src/runtime/delta.cpp](../../../../../../src/runtime/delta.cpp), [docs/invariant_memory.md](../../../../../invariant_memory.md), [docs/code_review.md](../../../../../code_review.md) |

```text
bool operator==(const CanonicalLiveState&) const=default;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Compare live export by stored members. |
| inputs / outputs | Default equality compares sequence/factors/row totals. |
| invariants | Equality of exported facts does not prove current native/source/durable identity, report authenticity or minimum-height authority. |
| ownership | Reads both operands synchronously and retains no backing. |
| failure | Uses member comparison; no handler or admission/validation is added by =default. |
| cost | O(compared nested values/string bytes/container elements), with early exit; no native owner scan. |
| Design | [include/crown/runtime/inspection.hpp](../../../../../../include/crown/runtime/inspection.hpp), [src/runtime/inspection_detail.hpp](../../../../../../src/runtime/inspection_detail.hpp), [src/runtime/support.cpp](../../../../../../src/runtime/support.cpp), [src/runtime/physical.cpp](../../../../../../src/runtime/physical.cpp), [src/runtime/delta.cpp](../../../../../../src/runtime/delta.cpp), [docs/invariant_memory.md](../../../../../invariant_memory.md), [docs/code_review.md](../../../../../code_review.md) |

## B0028

[Lines 137–142](../../../../../../include/crown/runtime/inspection.hpp#L137); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct CanonicalDeltaState {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Export CanonicalDeltaState for human comparison. |
| inputs / outputs | CanonicalPhysicalState, delta/sql-view flags and optional CanonicalLiveState. |
| invariants | Optional live image presence and public flags do not configure DeltaRuntime or prove equivalence. |
| ownership | Owns ordinary caller-allocator rows/strings/vectors/set nodes described above. Copies deep-copy those members; it is neither a cheap shared handle nor a native owner capability. |
| failure | Owning construction/copy can allocate and throw. Ordinary aggregate/memberwise assignment has no special whole-record publication guarantee; no catch/fallback is added. |
| cost | Copy O(full physical+optional live DTO); equality walks both. Release nested ordinary physical/live graph. |
| Design | [include/crown/runtime/inspection.hpp](../../../../../../include/crown/runtime/inspection.hpp), [src/runtime/inspection_detail.hpp](../../../../../../src/runtime/inspection_detail.hpp), [src/runtime/support.cpp](../../../../../../src/runtime/support.cpp), [src/runtime/physical.cpp](../../../../../../src/runtime/physical.cpp), [src/runtime/delta.cpp](../../../../../../src/runtime/delta.cpp), [docs/invariant_memory.md](../../../../../invariant_memory.md), [docs/code_review.md](../../../../../code_review.md) |

```text
bool operator==(const CanonicalDeltaState&) const=default;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Compare delta export by stored members. |
| inputs / outputs | Default equality compares physical/flags/optional live. |
| invariants | Equality of exported facts does not prove current native/source/durable identity, report authenticity or minimum-height authority. |
| ownership | Reads both operands synchronously and retains no backing. |
| failure | Uses member comparison; no handler or admission/validation is added by =default. |
| cost | O(compared nested values/string bytes/container elements), with early exit; no native owner scan. |
| Design | [include/crown/runtime/inspection.hpp](../../../../../../include/crown/runtime/inspection.hpp), [src/runtime/inspection_detail.hpp](../../../../../../src/runtime/inspection_detail.hpp), [src/runtime/support.cpp](../../../../../../src/runtime/support.cpp), [src/runtime/physical.cpp](../../../../../../src/runtime/physical.cpp), [src/runtime/delta.cpp](../../../../../../src/runtime/delta.cpp), [docs/invariant_memory.md](../../../../../invariant_memory.md), [docs/code_review.md](../../../../../code_review.md) |

## B0029

[Lines 143–143](../../../../../../include/crown/runtime/inspection.hpp#L143); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L143-L143:sha256:97734ee3ed73fbf0bd112ff8fee5fae528737ea20327081d48b1efcf3f9b9a5a
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Close the \`namespace crown::runtime\` scope at this exact source boundary. |
| inputs / outputs | This token introduces no callable inputs or outputs. Declarations inside \`namespace crown::runtime\` define the available names, members and operations. |
| invariants | The closing brace matches the opening \`namespace crown::runtime\` at its lexical source position in include/crown/runtime/inspection.hpp; it preserves C++ namespace/type nesting. |
| ownership | The closing delimiter creates no owner. Types closed by \`namespace crown::runtime\` retain the lifetimes and allocator rules of their own fields and operations. |
| failure | No failure path executes at this closing delimiter. Failure and cleanup behavior belong to enclosed functions and owning types. |
| cost | The delimiter itself performs no runtime work; the enclosed initializers, methods and destructors carry their own costs. |
| Design | [docs/runtime_support.md](../../../../../runtime_support.md), [docs/support_invariants.md](../../../../../support_invariants.md), [docs/result_cursors.md](../../../../../result_cursors.md), [docs/query_memory.md](../../../../../query_memory.md), [docs/code_specs/subsystem_contracts.md](../../../../subsystem_contracts.md) |
