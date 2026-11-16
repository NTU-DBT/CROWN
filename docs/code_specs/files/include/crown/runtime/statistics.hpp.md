# `include/crown/runtime/statistics.hpp` — block usage map

[Source](../../../../../../include/crown/runtime/statistics.hpp) · [Source index](../../../../README.md) · [Subsystem contracts](../../../../subsystem_contracts.md) · [Reviewed primitives](../../../../primitives.md)

Capture bounded distributions, workload counters, owner memory and explain observations without mislabeling partial information as exact.

Snapshot SHA-256: `8706a66240987e4284a4597e100a2b427a94821881b0dbd7f12ec5f3f2f8c357`. 133 lines partitioned into 22 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [statistics](../../../../subsystem_contracts.md#statistics). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/statistics.md](../../../../../statistics.md), [docs/observability.md](../../../../../observability.md), [docs/memory_reports.md](../../../../../memory_reports.md), [docs/ranking_evaluation.md](../../../../../ranking_evaluation.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–9](../../../../../../include/crown/runtime/statistics.hpp#L1) | Imports dependencies; guards repeated header inclusion; declares namespace scope; declares types or opens a type body. |  · [reviewed contract](#b0001) |
| [B0002 · 10–10](../../../../../../include/crown/runtime/statistics.hpp#L10) | Type/record definition: struct Exhausted |  · [reviewed contract](#b0002) |
| [B0003 · 11–11](../../../../../../include/crown/runtime/statistics.hpp#L11) | Explanatory comments or spacing. | source comment (unverified): // Storage-only scope: revision is an invalidation stamp, NOT a committed epoch. · [reviewed contract](#b0003) |
| [B0004 · 12–12](../../../../../../include/crown/runtime/statistics.hpp#L12) | Type/record definition: struct Stamp | source comment (unverified): // Storage-only scope: revision is an invalidation stamp, NOT a committed epoch. · [reviewed contract](#b0004) |
| [B0005 · 13–13](../../../../../../include/crown/runtime/statistics.hpp#L13) | Type/record definition: enum class Completion |  · [reviewed contract](#b0005) |
| [B0006 · 14–18](../../../../../../include/crown/runtime/statistics.hpp#L14) | Type/record definition: struct Limits |  · [reviewed contract](#b0006) |
| [B0007 · 19–22](../../../../../../include/crown/runtime/statistics.hpp#L19) | Type/record definition: struct Usage |  · [reviewed contract](#b0007) |
| [B0008 · 23–24](../../../../../../include/crown/runtime/statistics.hpp#L23) | Explanatory comments or spacing. | source comment (unverified): // One caller-owned budget composes sequential captures. Failed components consume · [reviewed contract](#b0008) |
| [B0009 · 25–37](../../../../../../include/crown/runtime/statistics.hpp#L25) | Type/record definition: class Budget | returns limits_; usage_; source comment (unverified): // One caller-owned budget composes sequential captures. Failed components consume · [reviewed contract](#b0009) |
| [B0010 · 38–38](../../../../../../include/crown/runtime/statistics.hpp#L38) | Type/record definition: struct HeavyKey |  · [reviewed contract](#b0010) |
| [B0011 · 39–46](../../../../../../include/crown/runtime/statistics.hpp#L39) | Type/record definition: struct Distribution | source comment (unverified): // Exact multiplicity -&gt; number of keys. Empty when incomplete. · [reviewed contract](#b0011) |
| [B0012 · 47–50](../../../../../../include/crown/runtime/statistics.hpp#L47) | declares namespace scope; declares values/defaults or compile-time conditions. | source comment (unverified): // Query-owned captures use compact native keys and original-account arrays. · [reviewed contract](#b0012) |
| [B0013 · 51–53](../../../../../../include/crown/runtime/statistics.hpp#L51) | Callable definition: template&lt;class T&gt; resource::OwnerAllocator&lt;T&gt; capture_allocator(const resource::MemoryAccount& account) | calls ; returns resource::OwnerAllocator&lt;T&gt;(account,resource::MemoryPurpose::capture,owner_capture_memory) · [reviewed contract](#b0013) |
| [B0014 · 54–55](../../../../../../include/crown/runtime/statistics.hpp#L54) | declares aliases; declares types or opens a type body; declares values/defaults or compile-time conditions. |  · [reviewed contract](#b0014) |
| [B0015 · 56–76](../../../../../../include/crown/runtime/statistics.hpp#L56) | Type/record definition: class CapturedKey | returns *this; row_.view() · [reviewed contract](#b0015) |
| [B0016 · 77–77](../../../../../../include/crown/runtime/statistics.hpp#L77) | Type/record definition: struct CapturedHeavyKey |  · [reviewed contract](#b0016) |
| [B0017 · 78–89](../../../../../../include/crown/runtime/statistics.hpp#L78) | Type/record definition: struct CapturedDistribution | source comment (unverified): // This owning value copies funded vectors/keys and may allocate on that account. · [reviewed contract](#b0017) |
| [B0018 · 90–99](../../../../../../include/crown/runtime/statistics.hpp#L90) | declares namespace scope; declares callable signatures; declares values/defaults or compile-time conditions. | source comment (unverified): // Internal ordered-field scan. The owning owner report keeps the source layout · [reviewed contract](#b0018) |
| [B0019 · 100–111](../../../../../../include/crown/runtime/statistics.hpp#L100) | Type/record definition: class WeightedBuilder |  · [reviewed contract](#b0019) |
| [B0020 · 112–112](../../../../../../include/crown/runtime/statistics.hpp#L112) | Closes surrounding scope/type. |  · [reviewed contract](#b0020) |
| [B0021 · 113–122](../../../../../../include/crown/runtime/statistics.hpp#L113) | Type/record definition: struct Capture | source comment (unverified): // Layout/projection handles share metadata; Distribution owns ordinary exports. · [reviewed contract](#b0021) |
| [B0022 · 123–133](../../../../../../include/crown/runtime/statistics.hpp#L123) | declares callable signatures; declares values/defaults or compile-time conditions. | source comment (unverified): // Explicit synchronous reads of quiescent tables; active journal is rejected. · [reviewed contract](#b0022) |

## B0001

[Lines 1–9](../../../../../../include/crown/runtime/statistics.hpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
#pragma once
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Expose bounded standalone and native population statistics. |
| inputs / outputs | Includes table/reference/native row and original-account owning allocators; forwards table/RowView. |
| invariants | Statistics capture is explicit quiescent read, not query answer estimation or index-registration side effect. |
| ownership | No runtime graph allocated by inclusion. |
| failure | Compile-time dependency boundary. |
| cost | No runtime action at inclusion. |
| Design | [include/crown/runtime/statistics.hpp](../../../../../../include/crown/runtime/statistics.hpp), [src/runtime/statistics.cpp](../../../../../../src/runtime/statistics.cpp), [src/runtime/native_statistics.cpp](../../../../../../src/runtime/native_statistics.cpp), [docs/statistics.md](../../../../../statistics.md), [docs/code_review.md](../../../../../code_review.md) |

## B0002

[Lines 10–10](../../../../../../include/crown/runtime/statistics.hpp#L10); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
namespace detail { struct Exhausted {}; }
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Signal only logical statistics budget exhaustion internally. |
| inputs / outputs | Empty detail::Exhausted exception tag. |
| invariants | Consumers convert only this admitted exhaustion to unknown/incomplete; OOM/corruption/ownership are not swallowed. |
| ownership | Caller owns inline numeric/tag fields; this record retains no backing runtime, rows, strings or allocation grant. |
| failure | The declaration does not validate public fields or translate failure. Actual factories/consumers perform the stated checks. |
| cost | Constant-size enum/tag, no allocation, scan or clock. Arbitrary enum casts are not admitted automatically. |
| Design | [include/crown/runtime/statistics.hpp](../../../../../../include/crown/runtime/statistics.hpp), [src/runtime/statistics.cpp](../../../../../../src/runtime/statistics.cpp), [src/runtime/native_statistics.cpp](../../../../../../src/runtime/native_statistics.cpp), [docs/statistics.md](../../../../../statistics.md), [docs/code_review.md](../../../../../code_review.md) |

## B0003

[Lines 11–11](../../../../../../include/crown/runtime/statistics.hpp#L11); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L11-L11:sha256:3108bad868515ceebdaddf639f8eb780f273510e0a21ca56919118bd197b0b36
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Usage note immediately before \`struct Stamp\`: Storage-only scope: revision is an invalidation stamp, NOT a committed epoch. |
| inputs / outputs | This comment introduces no parameter, field or return value. It documents the adjacent construct beginning at include/crown/runtime/statistics.hpp:L12; use that declaration for the actual input/output shape. |
| invariants | The source note states: Storage-only scope: revision is an invalidation stamp, NOT a committed epoch. It is prose guidance; the adjacent implementation is the place to check enforcement. |
| ownership | The note states no ownership relation and retains no value. The adjacent declaration or function controls the actual owner and borrowed-view lifetime. |
| failure | This comment adds no branch or handler. Any failure behavior remains in the adjacent callable implementation and its callers. |
| cost | The prose adds no executable work. Runtime cost belongs to the adjacent operation; the note does not establish a measured or global complexity bound. |
| Design | [docs/statistics.md](../../../../../statistics.md), [docs/memory_reports.md](../../../../../memory_reports.md), [docs/query_memory.md](../../../../../query_memory.md), [docs/code_specs/subsystem_contracts.md](../../../../subsystem_contracts.md) |

## B0004

[Lines 12–12](../../../../../../include/crown/runtime/statistics.hpp#L12); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct Stamp { StorageOwnerId owner; RelationId relation; std::uint64_t revision; };
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Identify storage invalidation scope. |
| inputs / outputs | StorageOwnerId/relation/revision. |
| invariants | Revision can change during rollback; it is not OwnerStamp committed sequence or durability/freshness proof. |
| ownership | Caller owns inline numeric/tag fields; this record retains no backing runtime, rows, strings or allocation grant. |
| failure | The declaration does not validate public fields or translate failure. Actual factories/consumers perform the stated checks. |
| cost | Fixed inline scalar/enum/optional/array storage and bounded copies; no dynamic payload, scan, clock or allocation. |
| Design | [include/crown/runtime/statistics.hpp](../../../../../../include/crown/runtime/statistics.hpp), [src/runtime/statistics.cpp](../../../../../../src/runtime/statistics.cpp), [src/runtime/native_statistics.cpp](../../../../../../src/runtime/native_statistics.cpp), [docs/statistics.md](../../../../../statistics.md), [docs/code_review.md](../../../../../code_review.md) |

## B0005

[Lines 13–13](../../../../../../include/crown/runtime/statistics.hpp#L13); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
enum class Completion { exact, budget_exhausted };
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Qualify distribution completeness. |
| inputs / outputs | exact versus budget_exhausted. |
| invariants | Incomplete distributions expose visited progress only; NDV/top-K unknown and histogram empty. |
| ownership | Caller owns inline numeric/tag fields; this record retains no backing runtime, rows, strings or allocation grant. |
| failure | The declaration does not validate public fields or translate failure. Actual factories/consumers perform the stated checks. |
| cost | Constant-size enum/tag, no allocation, scan or clock. Arbitrary enum casts are not admitted automatically. |
| Design | [include/crown/runtime/statistics.hpp](../../../../../../include/crown/runtime/statistics.hpp), [src/runtime/statistics.cpp](../../../../../../src/runtime/statistics.cpp), [src/runtime/native_statistics.cpp](../../../../../../src/runtime/native_statistics.cpp), [docs/statistics.md](../../../../../statistics.md), [docs/code_review.md](../../../../../code_review.md) |

## B0006

[Lines 14–18](../../../../../../include/crown/runtime/statistics.hpp#L14); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct Limits {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Bound shared diagnostic population work and payload model. |
| inputs / outputs | work1M, rows/distinct65536, modeled bytes8MiB, projection width256 and topK16. |
| invariants | Logical accounted_bytes excludes real framing/capacity/scratch/caller copies; actual native account is independent. Width/top-K apply to requested local population, not global query answer. |
| ownership | Caller owns inline numeric/tag fields; this record retains no backing runtime, rows, strings or allocation grant. |
| failure | The declaration does not validate public fields or translate failure. Actual factories/consumers perform the stated checks. |
| cost | Fixed inline scalar/enum/optional/array storage and bounded copies; no dynamic payload, scan, clock or allocation. |
| Design | [include/crown/runtime/statistics.hpp](../../../../../../include/crown/runtime/statistics.hpp), [src/runtime/statistics.cpp](../../../../../../src/runtime/statistics.cpp), [src/runtime/native_statistics.cpp](../../../../../../src/runtime/native_statistics.cpp), [docs/statistics.md](../../../../../statistics.md), [docs/code_review.md](../../../../../code_review.md) |

## B0007

[Lines 19–22](../../../../../../include/crown/runtime/statistics.hpp#L19); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct Usage {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Record logical statistics consumption and capacity high waters. |
| inputs / outputs | work/rows/distinct/model bytes and maximum row/histogram/heavy capacities. |
| invariants | Counters accumulate across captures/failure prefixes; capacities are observations, not grants or current actual allocator byte totals. |
| ownership | Caller owns inline numeric/tag fields; this record retains no backing runtime, rows, strings or allocation grant. |
| failure | The declaration does not validate public fields or translate failure. Actual factories/consumers perform the stated checks. |
| cost | Fixed inline scalar/enum/optional/array storage and bounded copies; no dynamic payload, scan, clock or allocation. |
| Design | [include/crown/runtime/statistics.hpp](../../../../../../include/crown/runtime/statistics.hpp), [src/runtime/statistics.cpp](../../../../../../src/runtime/statistics.cpp), [src/runtime/native_statistics.cpp](../../../../../../src/runtime/native_statistics.cpp), [docs/statistics.md](../../../../../statistics.md), [docs/code_review.md](../../../../../code_review.md) |

## B0008

[Lines 23–24](../../../../../../include/crown/runtime/statistics.hpp#L23); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L23-L24:sha256:ba9928dc32ac2d2ef6d195cd4acd380c0077a6ea32e81a74ba18f9dc60a54080
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Usage note immediately before \`class Budget\`: One caller-owned budget composes sequential captures. Failed components consume work already performed. No allocation or clocks in budget accounting. |
| inputs / outputs | This comment introduces no parameter, field or return value. It documents the adjacent construct beginning at include/crown/runtime/statistics.hpp:L25; use that declaration for the actual input/output shape. |
| invariants | The source note states: One caller-owned budget composes sequential captures. Failed components consume work already performed. No allocation or clocks in budget accounting. It is prose guidance; the adjacent implementation is the place to check enforcement. |
| ownership | The comment itself retains nothing. It documents this neighboring ownership/account boundary: One caller-owned budget composes sequential captures. Failed components consume work already performed. No allocation or clocks in budget accounting. Actual lifetime is determined by the declared members and owners. |
| failure | The note describes a failure or stop boundary: One caller-owned budget composes sequential captures. Failed components consume work already performed. No allocation or clocks in budget accounting. The comment adds no handler; the surrounding code determines the outcome. |
| cost | The note states a local cost boundary: One caller-owned budget composes sequential captures. Failed components consume work already performed. No allocation or clocks in budget accounting. Treat it as usage guidance; actual work follows the implementation and input. |
| Design | [docs/statistics.md](../../../../../statistics.md), [docs/memory_reports.md](../../../../../memory_reports.md), [docs/query_memory.md](../../../../../query_memory.md), [docs/code_specs/subsystem_contracts.md](../../../../subsystem_contracts.md) |

## B0009

[Lines 25–37](../../../../../../include/crown/runtime/statistics.hpp#L25); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
class Budget {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Compose one caller-owned diagnostic Budget across sequential captures. |
| inputs / outputs | Fixed Limits/Usage; work/row/key/bytes charge corresponding caps; observe_capacities takes maxima. |
| invariants | Budget is cumulative and nontransactional: a later failure does not refund earlier charges. No clock, allocation or automatic per-component reset. |
| ownership | Caller must outlive all internal scans/WeightedBuilder borrowing it; no heap/runtime retained. |
| failure | Exceeding cap throws detail::Exhausted before that counter increment. Consumer paths decide incomplete versus propagated failure. |
| cost | O(1) scalar accounting per charge, fixed storage; excludes actual scan/allocator/cleanup costs. |
| Design | [include/crown/runtime/statistics.hpp](../../../../../../include/crown/runtime/statistics.hpp), [src/runtime/statistics.cpp](../../../../../../src/runtime/statistics.cpp), [src/runtime/native_statistics.cpp](../../../../../../src/runtime/native_statistics.cpp), [docs/statistics.md](../../../../../statistics.md), [docs/code_review.md](../../../../../code_review.md) |

```text
explicit Budget(Limits limits={}):limits_(limits) {}
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Initialize empty cumulative statistics usage. |
| inputs / outputs | Copies Limits, leaves Usage zero. |
| invariants | Zero caps are valid and cause later positive charges to exhaust; no account created. |
| ownership | Owns fixed settings/counters. |
| failure | Signature not noexcept but current constructor only copies fixed members. |
| cost | O(1), no allocation/clock. |
| Design | [include/crown/runtime/statistics.hpp](../../../../../../include/crown/runtime/statistics.hpp), [src/runtime/statistics.cpp](../../../../../../src/runtime/statistics.cpp), [src/runtime/native_statistics.cpp](../../../../../../src/runtime/native_statistics.cpp), [docs/statistics.md](../../../../../statistics.md), [docs/code_review.md](../../../../../code_review.md) |

```text
const Limits& limits() const { return limits_; }
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Borrow statistics Budget limits. |
| inputs / outputs | Returns const Limits&. |
| invariants | Does not refresh/reset counters or provide runtime memory allowance. |
| ownership | Reference borrows caller Budget. |
| failure | Signature not noexcept; current member access cannot throw. |
| cost | O(1). |
| Design | [include/crown/runtime/statistics.hpp](../../../../../../include/crown/runtime/statistics.hpp), [src/runtime/statistics.cpp](../../../../../../src/runtime/statistics.cpp), [src/runtime/native_statistics.cpp](../../../../../../src/runtime/native_statistics.cpp), [docs/statistics.md](../../../../../statistics.md), [docs/code_review.md](../../../../../code_review.md) |

```text
const Usage& usage() const { return usage_; }
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Borrow statistics Budget spent usage. |
| inputs / outputs | Returns const Usage&. |
| invariants | Does not refresh/reset counters or provide runtime memory allowance. |
| ownership | Reference borrows caller Budget. |
| failure | Signature not noexcept; current member access cannot throw. |
| cost | O(1). |
| Design | [include/crown/runtime/statistics.hpp](../../../../../../include/crown/runtime/statistics.hpp), [src/runtime/statistics.cpp](../../../../../../src/runtime/statistics.cpp), [src/runtime/native_statistics.cpp](../../../../../../src/runtime/native_statistics.cpp), [docs/statistics.md](../../../../../statistics.md), [docs/code_review.md](../../../../../code_review.md) |

```text
void work(std::uint64_t n=1);
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Charge statistics work. |
| inputs / outputs | Increments work by supplied n/default1 only when n fits cap-used. |
| invariants | Private Usage starts0 and remains &lt;= matching Limits cap. Existing charges are not rolled back when another dimension later fails. |
| ownership | Mutates caller Budget scalar only. |
| failure | Throws detail::Exhausted before rejected increment; no catch or allocating diagnostic. |
| cost | O(1), no allocation/clock. |
| Design | [include/crown/runtime/statistics.hpp](../../../../../../include/crown/runtime/statistics.hpp), [src/runtime/statistics.cpp](../../../../../../src/runtime/statistics.cpp), [src/runtime/native_statistics.cpp](../../../../../../src/runtime/native_statistics.cpp), [docs/statistics.md](../../../../../statistics.md), [docs/code_review.md](../../../../../code_review.md) |

```text
void row();
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Charge statistics one visited row. |
| inputs / outputs | Increments rows by1 only when n fits cap-used. |
| invariants | Private Usage starts0 and remains &lt;= matching Limits cap. Existing charges are not rolled back when another dimension later fails. |
| ownership | Mutates caller Budget scalar only. |
| failure | Throws detail::Exhausted before rejected increment; no catch or allocating diagnostic. |
| cost | O(1), no allocation/clock. |
| Design | [include/crown/runtime/statistics.hpp](../../../../../../include/crown/runtime/statistics.hpp), [src/runtime/statistics.cpp](../../../../../../src/runtime/statistics.cpp), [src/runtime/native_statistics.cpp](../../../../../../src/runtime/native_statistics.cpp), [docs/statistics.md](../../../../../statistics.md), [docs/code_review.md](../../../../../code_review.md) |

```text
void key();
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Charge statistics one distinct key. |
| inputs / outputs | Increments distinct_keys by1 only when n fits cap-used. |
| invariants | Private Usage starts0 and remains &lt;= matching Limits cap. Existing charges are not rolled back when another dimension later fails. |
| ownership | Mutates caller Budget scalar only. |
| failure | Throws detail::Exhausted before rejected increment; no catch or allocating diagnostic. |
| cost | O(1), no allocation/clock. |
| Design | [include/crown/runtime/statistics.hpp](../../../../../../include/crown/runtime/statistics.hpp), [src/runtime/statistics.cpp](../../../../../../src/runtime/statistics.cpp), [src/runtime/native_statistics.cpp](../../../../../../src/runtime/native_statistics.cpp), [docs/statistics.md](../../../../../statistics.md), [docs/code_review.md](../../../../../code_review.md) |

```text
void bytes(std::uint64_t n);
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Charge statistics logical payload bytes. |
| inputs / outputs | Increments accounted_bytes by supplied n only when n fits cap-used. |
| invariants | Private Usage starts0 and remains &lt;= matching Limits cap. Existing charges are not rolled back when another dimension later fails. |
| ownership | Mutates caller Budget scalar only. |
| failure | Throws detail::Exhausted before rejected increment; no catch or allocating diagnostic. |
| cost | O(1), no allocation/clock. |
| Design | [include/crown/runtime/statistics.hpp](../../../../../../include/crown/runtime/statistics.hpp), [src/runtime/statistics.cpp](../../../../../../src/runtime/statistics.cpp), [src/runtime/native_statistics.cpp](../../../../../../src/runtime/native_statistics.cpp), [docs/statistics.md](../../../../../statistics.md), [docs/code_review.md](../../../../../code_review.md) |

```text
void observe_capacities(std::size_t row,std::size_t histogram,std::size_t heavy) noexcept;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Observe diagnostic container capacity high waters. |
| inputs / outputs | Updates three maxima from actual row/histogram/heavy capacities. |
| invariants | Does not charge their actual allocator bytes or reduce previous maxima. |
| ownership | Only inline Budget Usage mutates. |
| failure | noexcept for a live readable object; borrowing does not validate lifetime or extend it. |
| cost | O(1), no allocation/clock. |
| Design | [include/crown/runtime/statistics.hpp](../../../../../../include/crown/runtime/statistics.hpp), [src/runtime/statistics.cpp](../../../../../../src/runtime/statistics.cpp), [src/runtime/native_statistics.cpp](../../../../../../src/runtime/native_statistics.cpp), [docs/statistics.md](../../../../../statistics.md), [docs/code_review.md](../../../../../code_review.md) |

## B0010

[Lines 38–38](../../../../../../include/crown/runtime/statistics.hpp#L38); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct HeavyKey { Row key; std::uint64_t count; };
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Own one ordinary exported heavy key. |
| inputs / outputs | Row key plus positive multiplicity. |
| invariants | A local population key/count is not global query answer count. |
| ownership | Owns ordinary caller-allocator rows/strings/vectors/set nodes described above. Copies deep-copy those members; it is neither a cheap shared handle nor a native owner capability. |
| failure | Owning construction/copy can allocate and throw. Ordinary aggregate/memberwise assignment has no special whole-record publication guarantee; no catch/fallback is added. |
| cost | Copy O(row/scalar/string bytes), no native owner scan. Release ordinary Value/string vector storage. |
| Design | [include/crown/runtime/statistics.hpp](../../../../../../include/crown/runtime/statistics.hpp), [src/runtime/statistics.cpp](../../../../../../src/runtime/statistics.cpp), [src/runtime/native_statistics.cpp](../../../../../../src/runtime/native_statistics.cpp), [docs/statistics.md](../../../../../statistics.md), [docs/code_review.md](../../../../../code_review.md) |

## B0011

[Lines 39–46](../../../../../../include/crown/runtime/statistics.hpp#L39); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct Distribution {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Own a standalone distribution export. |
| inputs / outputs | Completion, visited count, optional NDV, histogram vector and optional vector&lt;HeavyKey&gt;. |
| invariants | Exact histogram maps positive multiplicity→number of keys; top-K orders count desc then native row. Incomplete has no prefix exact facts; exact empty engages empty heavy keys/NDV0. |
| ownership | Owns ordinary caller-allocator rows/strings/vectors/set nodes described above. Copies deep-copy those members; it is neither a cheap shared handle nor a native owner capability. |
| failure | Owning construction/copy can allocate and throw. Ordinary aggregate/memberwise assignment has no special whole-record publication guarantee; no catch/fallback is added. |
| cost | Copy O(histogram+topK key bytes); capture additionally scans/groups/sorts. Release histogram vector and each retained key/string owner. |
| Design | [include/crown/runtime/statistics.hpp](../../../../../../include/crown/runtime/statistics.hpp), [src/runtime/statistics.cpp](../../../../../../src/runtime/statistics.cpp), [src/runtime/native_statistics.cpp](../../../../../../src/runtime/native_statistics.cpp), [docs/statistics.md](../../../../../statistics.md), [docs/code_review.md](../../../../../code_review.md) |

## B0012

[Lines 47–50](../../../../../../include/crown/runtime/statistics.hpp#L47); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
inline constexpr resource::MemoryAttribution owner_capture_memory{resource::MemoryOwnerKind::capture,2};
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Attribute query-owned population captures. |
| inputs / outputs | owner_capture_memory={capture,2}. |
| invariants | This label classifies actual account allocations; it cannot create a fresh budget. |
| ownership | Caller owns inline numeric/tag fields; this record retains no backing runtime, rows, strings or allocation grant. |
| failure | The declaration does not validate public fields or translate failure. Actual factories/consumers perform the stated checks. |
| cost | Fixed inline scalar/enum/optional/array storage and bounded copies; no dynamic payload, scan, clock or allocation. |
| Design | [include/crown/runtime/statistics.hpp](../../../../../../include/crown/runtime/statistics.hpp), [src/runtime/statistics.cpp](../../../../../../src/runtime/statistics.cpp), [src/runtime/native_statistics.cpp](../../../../../../src/runtime/native_statistics.cpp), [docs/statistics.md](../../../../../statistics.md), [docs/code_review.md](../../../../../code_review.md) |

## B0013

[Lines 51–53](../../../../../../include/crown/runtime/statistics.hpp#L51); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
template<class T> resource::OwnerAllocator<T> capture_allocator(const resource::MemoryAccount& account) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Bind a transferable native capture allocator. |
| inputs / outputs | Returns OwnerAllocator&lt;T&gt;(account,capture,owner_capture_memory). |
| invariants | Assignment/move/swap preserve actual source account and attribution. |
| ownership | Allocator retains supplied MemoryAccount, without allocating T storage. |
| failure | No allocating operation here; signature not marked noexcept. |
| cost | O(1) account/allocator copy. |
| Design | [include/crown/runtime/statistics.hpp](../../../../../../include/crown/runtime/statistics.hpp), [src/runtime/statistics.cpp](../../../../../../src/runtime/statistics.cpp), [src/runtime/native_statistics.cpp](../../../../../../src/runtime/native_statistics.cpp), [docs/statistics.md](../../../../../statistics.md), [docs/code_review.md](../../../../../code_review.md), [include/crown/resource/owner_allocator.hpp](../../../../../../include/crown/resource/owner_allocator.hpp) |

## B0014

[Lines 54–55](../../../../../../include/crown/runtime/statistics.hpp#L54); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
template<class T> using CaptureVector=std::vector<T,resource::OwnerAllocator<T>>;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Define native transferable capture vectors. |
| inputs / outputs | CaptureVector&lt;T&gt; is vector&lt;T,OwnerAllocator&lt;T&gt;&gt;. |
| invariants | Vector copy can allocate/deep-copy; move/assignment ownership propagation is separate from element construction cost. |
| ownership | Owns funded capacity and actual account; no hidden separate allowance. |
| failure | Allocations may throw; current element types have their specific copy behavior. |
| cost | O(N) copies, fixed ownership transfer on allocator-propagating move, element-specific destruction. |
| Design | [include/crown/runtime/statistics.hpp](../../../../../../include/crown/runtime/statistics.hpp), [src/runtime/statistics.cpp](../../../../../../src/runtime/statistics.cpp), [src/runtime/native_statistics.cpp](../../../../../../src/runtime/native_statistics.cpp), [docs/statistics.md](../../../../../statistics.md), [docs/code_review.md](../../../../../code_review.md), [include/crown/resource/owner_allocator.hpp](../../../../../../include/crown/resource/owner_allocator.hpp) |

## B0015

[Lines 56–76](../../../../../../include/crown/runtime/statistics.hpp#L56); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
class CapturedKey {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Own a compact key with explicit funded deep-copy semantics. |
| inputs / outputs | MemoryAccount plus AccountedRow; copy clones on retained account; getters expose lvalue-only RowView and scalar borrows. |
| invariants | No mutable runtime pointer/pin; captured value remains detached after owner update. Constructor caller supplies matching account/row; this value alone does not authenticate a capture. |
| ownership | One compact native block and actual account. Copies allocate; moves transfer, assignment uses temporary for consistency. |
| failure | Native copy/account/overflow failures propagate; no generic recovery handler. |
| cost | Copy O(columns+string bytes), compare actual value bytes, release one row block/account. |
| Design | [include/crown/runtime/statistics.hpp](../../../../../../include/crown/runtime/statistics.hpp), [src/runtime/statistics.cpp](../../../../../../src/runtime/statistics.cpp), [src/runtime/native_statistics.cpp](../../../../../../src/runtime/native_statistics.cpp), [docs/statistics.md](../../../../../statistics.md), [docs/code_review.md](../../../../../code_review.md), [src/storage/accounted_row.cpp](../../../../../../src/storage/accounted_row.cpp) |

```text
CapturedKey(const resource::MemoryAccount&,storage::AccountedRow);
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Adopt an already owned native captured key. |
| inputs / outputs | Account and move-only AccountedRow by value construct account_ and move row_. |
| invariants | Internal factories pass row from the same original account; constructor does not independently validate provenance or create allowance. |
| ownership | Destination adopts row block/account; borrowed source not retained. |
| failure | Parameter creation may allocate before call; constructor body only handle/row moves. |
| cost | O(1) adoption; prior native row copy cost paid by caller. |
| Design | [include/crown/runtime/statistics.hpp](../../../../../../include/crown/runtime/statistics.hpp), [src/runtime/statistics.cpp](../../../../../../src/runtime/statistics.cpp), [src/runtime/native_statistics.cpp](../../../../../../src/runtime/native_statistics.cpp), [docs/statistics.md](../../../../../statistics.md), [docs/code_review.md](../../../../../code_review.md) |

```text
CapturedKey(const CapturedKey&);
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Deep-copy a captured key on its original account. |
| inputs / outputs | Retains other.account_; clones row when account nonempty, otherwise empty row. |
| invariants | Copy does not refill account or retain source row pointer. |
| ownership | New native block independent, same original account/attribution from row clone. |
| failure | Allocation failure cleans partial copy, source unchanged. |
| cost | O(row columns+string bytes), old/new blocks coexist. |
| Design | [include/crown/runtime/statistics.hpp](../../../../../../include/crown/runtime/statistics.hpp), [src/runtime/statistics.cpp](../../../../../../src/runtime/statistics.cpp), [src/runtime/native_statistics.cpp](../../../../../../src/runtime/native_statistics.cpp), [docs/statistics.md](../../../../../statistics.md), [docs/code_review.md](../../../../../code_review.md) |

```text
CapturedKey(CapturedKey&&) noexcept=default;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Move captured-key ownership by construction. |
| inputs / outputs | Default noexcept move of account and native row. |
| invariants | Moved-from value only has ordinary valid moved-from state. |
| ownership | Transfers block/account, releases old destination block on assignment. |
| failure | noexcept. |
| cost | Fixed transfer and old-block cleanup; no new allocation. |
| Design | [include/crown/runtime/statistics.hpp](../../../../../../include/crown/runtime/statistics.hpp), [src/runtime/statistics.cpp](../../../../../../src/runtime/statistics.cpp), [src/runtime/native_statistics.cpp](../../../../../../src/runtime/native_statistics.cpp), [docs/statistics.md](../../../../../statistics.md), [docs/code_review.md](../../../../../code_review.md) |

```text
CapturedKey& operator=(CapturedKey&&) noexcept=default;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Move captured-key ownership by assignment. |
| inputs / outputs | Default noexcept move of account and native row. |
| invariants | Moved-from value only has ordinary valid moved-from state. |
| ownership | Transfers block/account, releases old destination block on assignment. |
| failure | noexcept. |
| cost | Fixed transfer and old-block cleanup; no new allocation. |
| Design | [include/crown/runtime/statistics.hpp](../../../../../../include/crown/runtime/statistics.hpp), [src/runtime/statistics.cpp](../../../../../../src/runtime/statistics.cpp), [src/runtime/native_statistics.cpp](../../../../../../src/runtime/native_statistics.cpp), [docs/statistics.md](../../../../../statistics.md), [docs/code_review.md](../../../../../code_review.md) |

```text
CapturedKey& operator=(const CapturedKey& other) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Copy-assign a captured key with private preparation. |
| inputs / outputs | Self-check; deep-copy next then move into destination. |
| invariants | Prevents new account from being paired with stale old row if allocation fails. |
| ownership | Temporary owns independent original-account row; final move replaces old ownership. |
| failure | Throw during private copy leaves destination unchanged; move publication noexcept. |
| cost | O(key bytes) clone plus old-block release, extra peak row until publication. |
| Design | [include/crown/runtime/statistics.hpp](../../../../../../include/crown/runtime/statistics.hpp), [src/runtime/statistics.cpp](../../../../../../src/runtime/statistics.cpp), [src/runtime/native_statistics.cpp](../../../../../../src/runtime/native_statistics.cpp), [docs/statistics.md](../../../../../statistics.md), [docs/code_review.md](../../../../../code_review.md) |

```text
storage::RowView view() const & noexcept { return row_.view(); }
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Borrow captured key values. |
| inputs / outputs | Returns row_.view() from lvalue key. |
| invariants | No pin/owner attached to the view. |
| ownership | Keep CapturedKey alive and unchanged. |
| failure | noexcept for a live readable object; borrowing does not validate lifetime or extend it. |
| cost | O(1) fixed member/view lookup; no allocation or clock. |
| Design | [include/crown/runtime/statistics.hpp](../../../../../../include/crown/runtime/statistics.hpp), [src/runtime/statistics.cpp](../../../../../../src/runtime/statistics.cpp), [src/runtime/native_statistics.cpp](../../../../../../src/runtime/native_statistics.cpp), [docs/statistics.md](../../../../../statistics.md), [docs/code_review.md](../../../../../code_review.md) |

```text
storage::RowView view() const &&=delete;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Reject RowView from temporary captured key. |
| inputs / outputs | Rvalue view deleted. |
| invariants | Prevents immediate dangling temporary view. |
| ownership | No owner returned. |
| failure | Compile-time rejection. |
| cost | No runtime cost. |
| Design | [include/crown/runtime/statistics.hpp](../../../../../../include/crown/runtime/statistics.hpp), [src/runtime/statistics.cpp](../../../../../../src/runtime/statistics.cpp), [src/runtime/native_statistics.cpp](../../../../../../src/runtime/native_statistics.cpp), [docs/statistics.md](../../../../../statistics.md), [docs/code_review.md](../../../../../code_review.md) |

```text
std::size_t size() const noexcept { return row_.size(); }
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Read captured key size. |
| inputs / outputs | Returns row_.size() by value. |
| invariants | Number of native scalar columns, not byte payload. |
| ownership | Only numeric value returned; key retains block during call. |
| failure | noexcept for a live readable object; borrowing does not validate lifetime or extend it. |
| cost | O(1) fixed member/view lookup; no allocation or clock. |
| Design | [include/crown/runtime/statistics.hpp](../../../../../../include/crown/runtime/statistics.hpp), [src/runtime/statistics.cpp](../../../../../../src/runtime/statistics.cpp), [src/runtime/native_statistics.cpp](../../../../../../src/runtime/native_statistics.cpp), [docs/statistics.md](../../../../../statistics.md), [docs/code_review.md](../../../../../code_review.md) |

```text
bool empty() const noexcept { return row_.empty(); }
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Read captured key emptiness. |
| inputs / outputs | Returns row_.empty() by value. |
| invariants | Empty zero-column key is valid without row block. |
| ownership | Only numeric value returned; key retains block during call. |
| failure | noexcept for a live readable object; borrowing does not validate lifetime or extend it. |
| cost | O(1) fixed member/view lookup; no allocation or clock. |
| Design | [include/crown/runtime/statistics.hpp](../../../../../../include/crown/runtime/statistics.hpp), [src/runtime/statistics.cpp](../../../../../../src/runtime/statistics.cpp), [src/runtime/native_statistics.cpp](../../../../../../src/runtime/native_statistics.cpp), [docs/statistics.md](../../../../../statistics.md), [docs/code_review.md](../../../../../code_review.md) |

```text
resource::MemoryUsage memory_usage() const noexcept { return row_.memory_usage(); }
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Read captured key actual row allocation usage. |
| inputs / outputs | Returns row_.memory_usage() by value. |
| invariants | Includes row framing through actual account, not logical statistics byte model. |
| ownership | Only numeric value returned; key retains block during call. |
| failure | noexcept for a live readable object; borrowing does not validate lifetime or extend it. |
| cost | O(1) fixed member/view lookup; no allocation or clock. |
| Design | [include/crown/runtime/statistics.hpp](../../../../../../include/crown/runtime/statistics.hpp), [src/runtime/statistics.cpp](../../../../../../src/runtime/statistics.cpp), [src/runtime/native_statistics.cpp](../../../../../../src/runtime/native_statistics.cpp), [docs/statistics.md](../../../../../statistics.md), [docs/code_review.md](../../../../../code_review.md) |

```text
const storage::ScalarView& operator[](std::size_t i) const noexcept { return row_.view()[i]; }
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Borrow one captured native scalar. |
| inputs / outputs | Returns const ScalarView& at i through unchecked RowView indexing. |
| invariants | Requires i&lt;size; caller does not receive an owning string/scalar copy. |
| ownership | Reference and any string_view borrow this key block; retain key. |
| failure | noexcept for a live readable object; borrowing does not validate lifetime or extend it. |
| cost | O(1) fixed member/view lookup; no allocation or clock. |
| Design | [include/crown/runtime/statistics.hpp](../../../../../../include/crown/runtime/statistics.hpp), [src/runtime/statistics.cpp](../../../../../../src/runtime/statistics.cpp), [src/runtime/native_statistics.cpp](../../../../../../src/runtime/native_statistics.cpp), [docs/statistics.md](../../../../../statistics.md), [docs/code_review.md](../../../../../code_review.md) |

```text
bool operator==(const CapturedKey& other) const noexcept { return view()==other.view(); }
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Compare native captured key values. |
| inputs / outputs | RowView equality. |
| invariants | Different accounts can have equal values; equality is no source authority. |
| ownership | Reads both borrowed blocks; retains neither. |
| failure | noexcept for a live readable object; borrowing does not validate lifetime or extend it. |
| cost | O(columns+compared string bytes), no allocation/clock. |
| Design | [include/crown/runtime/statistics.hpp](../../../../../../include/crown/runtime/statistics.hpp), [src/runtime/statistics.cpp](../../../../../../src/runtime/statistics.cpp), [src/runtime/native_statistics.cpp](../../../../../../src/runtime/native_statistics.cpp), [docs/statistics.md](../../../../../statistics.md), [docs/code_review.md](../../../../../code_review.md) |

```text
bool operator==(const Row& other) const { return view()==other; }
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Compare a native key with an ordinary caller Row. |
| inputs / outputs | Native RowView equality borrows supported ordinary Value scalars. |
| invariants | No ordinary key export and no owner validation. |
| ownership | Reads both operands, retains neither. |
| failure | Signature may propagate scalar conversion/contract faults. |
| cost | O(columns+compared string bytes); no full Row allocation for comparison. |
| Design | [include/crown/runtime/statistics.hpp](../../../../../../include/crown/runtime/statistics.hpp), [src/runtime/statistics.cpp](../../../../../../src/runtime/statistics.cpp), [src/runtime/native_statistics.cpp](../../../../../../src/runtime/native_statistics.cpp), [docs/statistics.md](../../../../../statistics.md), [docs/code_review.md](../../../../../code_review.md), [src/storage/accounted_row.cpp](../../../../../../src/storage/accounted_row.cpp) |

## B0016

[Lines 77–77](../../../../../../include/crown/runtime/statistics.hpp#L77); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct CapturedHeavyKey { CapturedKey key; std::uint64_t count; };
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Own one funded heavy key and multiplicity. |
| inputs / outputs | CapturedKey plus U64 count. |
| invariants | Count is positive stored multiplicity supplied by native population scan, not global answer count. |
| ownership | Copies clone native key on original account; moves transfer it. |
| failure | Key copy allocation may throw. |
| cost | O(key bytes) copy; one row-block release. |
| Design | [include/crown/runtime/statistics.hpp](../../../../../../include/crown/runtime/statistics.hpp), [src/runtime/statistics.cpp](../../../../../../src/runtime/statistics.cpp), [src/runtime/native_statistics.cpp](../../../../../../src/runtime/native_statistics.cpp), [docs/statistics.md](../../../../../statistics.md), [docs/code_review.md](../../../../../code_review.md) |

## B0017

[Lines 78–89](../../../../../../include/crown/runtime/statistics.hpp#L78); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct CapturedDistribution {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Own an original-account native distribution. |
| inputs / outputs | Completion/visited/optional NDV, funded histogram and optional funded heavy-key vector. |
| invariants | Unknown defaults budget_exhausted; exact facts publish only after scan/sort/output allocation complete. No prefix NDV/top-K escapes exhaustion. |
| ownership | Owns vectors and cloned native heavy keys; copies allocate/deep-copy on source account. Default empty instance has no allowance; explicit account binds histogram. |
| failure | Owning copy can throw; no whole-record strong-copy assignment is promised by this aggregate. Actual native scan catches only admitted exhaustion/storage-work limits. |
| cost | Copy O(histogram+heavy key bytes); release visits heavy keys and deallocates vectors/row blocks; actual capture includes grouping/sorting. |
| Design | [include/crown/runtime/statistics.hpp](../../../../../../include/crown/runtime/statistics.hpp), [src/runtime/statistics.cpp](../../../../../../src/runtime/statistics.cpp), [src/runtime/native_statistics.cpp](../../../../../../src/runtime/native_statistics.cpp), [docs/statistics.md](../../../../../statistics.md), [docs/code_review.md](../../../../../code_review.md) |

```text
CapturedDistribution()=default; // Empty incomplete facts require no allocation.
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Construct an empty incomplete native distribution. |
| inputs / outputs | Default completion budget_exhausted, empty vector and disengaged NDV/heavy keys. |
| invariants | No allowance created; no exact zero fact fabricated. |
| ownership | Empty ordinary account-bound allocator state only. |
| failure | Default members do not allocate; signature not marked noexcept. |
| cost | O(1), no payload allocation. |
| Design | [include/crown/runtime/statistics.hpp](../../../../../../include/crown/runtime/statistics.hpp), [src/runtime/statistics.cpp](../../../../../../src/runtime/statistics.cpp), [src/runtime/native_statistics.cpp](../../../../../../src/runtime/native_statistics.cpp), [docs/statistics.md](../../../../../statistics.md), [docs/code_review.md](../../../../../code_review.md) |

```text
explicit CapturedDistribution(const resource::MemoryAccount& account)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Bind native distribution histogram to an actual account. |
| inputs / outputs | Initializes capture/2 histogram allocator, leaving facts incomplete/empty. |
| invariants | No scan or reserve yet; heavy keys are constructed by complete native finish. |
| ownership | Retains actual grant in allocator. |
| failure | Allocator binding itself does not allocate; signature not marked noexcept. |
| cost | O(1), no payload allocation. |
| Design | [include/crown/runtime/statistics.hpp](../../../../../../include/crown/runtime/statistics.hpp), [src/runtime/statistics.cpp](../../../../../../src/runtime/statistics.cpp), [src/runtime/native_statistics.cpp](../../../../../../src/runtime/native_statistics.cpp), [docs/statistics.md](../../../../../statistics.md), [docs/code_review.md](../../../../../code_review.md) |

## B0018

[Lines 90–99](../../../../../../include/crown/runtime/statistics.hpp#L90); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Distribution projected_fields(const storage::ReferenceTable&,std::span<const FieldId>,Budget&);
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Scan ordered fields into an ordinary distribution from ReferenceTable. |
| inputs / outputs | Quiescent table, stable span&lt;FieldId&gt;, shared Budget and optional native storage allowance for nonreference table. |
| invariants | Empty/repeated fields valid; field range validated against actual table layout, no temporary schema metadata built. Active journal rejected at cursor admission. |
| ownership | Returns ordinary owning key/histogram/top-K storage outside native account; field span borrowed only for call, existing table unchanged. |
| failure | Logical/storage-work exhaustion returns incomplete visited progress; invalid fields/layout/OOM/ownership faults propagate. Cursor startup can fail before result exists. |
| cost | Projection grouping linearly searches K distinct keys for N rows, O(NK*comparison width/bytes), exports projection each row; sorting O(K log K), histogram reserve can sum O(H²) payload/work. Standalone histogram lookup now adjacent after count sort. |
| Design | [include/crown/runtime/statistics.hpp](../../../../../../include/crown/runtime/statistics.hpp), [src/runtime/statistics.cpp](../../../../../../src/runtime/statistics.cpp), [src/runtime/native_statistics.cpp](../../../../../../src/runtime/native_statistics.cpp), [docs/statistics.md](../../../../../statistics.md), [docs/code_review.md](../../../../../code_review.md) |

```text
Distribution projected_fields(const storage::StorageTable&,std::span<const FieldId>,Budget&,storage::IndexWorkAllowance*);
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Scan ordered fields into an ordinary distribution from StorageTable. |
| inputs / outputs | Quiescent table, stable span&lt;FieldId&gt;, shared Budget and optional native storage allowance for nonreference table. |
| invariants | Empty/repeated fields valid; field range validated against actual table layout, no temporary schema metadata built. Active journal rejected at cursor admission. |
| ownership | Returns ordinary owning key/histogram/top-K storage outside native account; field span borrowed only for call, existing table unchanged. |
| failure | Logical/storage-work exhaustion returns incomplete visited progress; invalid fields/layout/OOM/ownership faults propagate. Cursor startup can fail before result exists. |
| cost | Projection grouping linearly searches K distinct keys for N rows, O(NK*comparison width/bytes), exports projection each row; sorting O(K log K), histogram reserve can sum O(H²) payload/work. Standalone histogram lookup now adjacent after count sort. |
| Design | [include/crown/runtime/statistics.hpp](../../../../../../include/crown/runtime/statistics.hpp), [src/runtime/statistics.cpp](../../../../../../src/runtime/statistics.cpp), [src/runtime/native_statistics.cpp](../../../../../../src/runtime/native_statistics.cpp), [docs/statistics.md](../../../../../statistics.md), [docs/code_review.md](../../../../../code_review.md) |

```text
Distribution projected_fields(const storage::AccountedStorageTable&,std::span<const FieldId>,Budget&,storage::IndexWorkAllowance*);
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Scan ordered fields into an ordinary distribution from AccountedStorageTable. |
| inputs / outputs | Quiescent table, stable span&lt;FieldId&gt;, shared Budget and optional native storage allowance for nonreference table. |
| invariants | Empty/repeated fields valid; field range validated against actual table layout, no temporary schema metadata built. Active journal rejected at cursor admission. |
| ownership | Returns ordinary owning key/histogram/top-K storage outside native account; field span borrowed only for call, existing table unchanged. |
| failure | Logical/storage-work exhaustion returns incomplete visited progress; invalid fields/layout/OOM/ownership faults propagate. Cursor startup can fail before result exists. |
| cost | Projection grouping linearly searches K distinct keys for N rows, O(NK*comparison width/bytes), exports projection each row; sorting O(K log K), histogram reserve can sum O(H²) payload/work. Standalone histogram lookup now adjacent after count sort. |
| Design | [include/crown/runtime/statistics.hpp](../../../../../../include/crown/runtime/statistics.hpp), [src/runtime/statistics.cpp](../../../../../../src/runtime/statistics.cpp), [src/runtime/native_statistics.cpp](../../../../../../src/runtime/native_statistics.cpp), [docs/statistics.md](../../../../../statistics.md), [docs/code_review.md](../../../../../code_review.md) |

```text
CapturedDistribution native_projected_fields(const storage::AccountedStorageTable&,std::span<const FieldId>,
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Scan actual native table projections into funded distribution. |
| inputs / outputs | Accounted table, stable ordered fields, shared Budget/storage grant and actual receiving account. |
| invariants | No new layout/projection token; invalid fields reject; empty/repeated projections valid. It is an explicit scan, not a hot hook. |
| ownership | Projected compact row blocks/group scratch/results all on supplied original account; no ordinary Row mirror. |
| failure | Only Exhausted/storage_work_limit becomes unknown; corruption/layout/owner/OOM propagate and private scratch unwinds. |
| cost | O(NK*key comparison bytes) linear grouping plus O(K log K) sorting; native histogram lookup O(KH), repeated reserve model O(H²); output/top-K allocations explicit. |
| Design | [include/crown/runtime/statistics.hpp](../../../../../../include/crown/runtime/statistics.hpp), [src/runtime/statistics.cpp](../../../../../../src/runtime/statistics.cpp), [src/runtime/native_statistics.cpp](../../../../../../src/runtime/native_statistics.cpp), [docs/statistics.md](../../../../../statistics.md), [docs/code_review.md](../../../../../code_review.md) |

```text
CapturedDistribution native_index(const storage::AccountedStorageTable&,IndexId,const storage::Projection&,
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Read admitted native index bucket degrees into funded distribution. |
| inputs / outputs | Accounted table/index, matching legacy Projection metadata, shared budgets and actual account. |
| invariants | Index must already exist; projection describes that actual index and is not revalidated by this helper. No new index registration. |
| ownership | Copies native keys/degree into funded scratch/results; source metadata borrowed for call. |
| failure | Cursor startup before local try can propagate; admitted Exhausted/storage-work-limit inside traversal returns incomplete. Other failures propagate. |
| cost | One pass over K admitted index keys plus native key-byte copy, sorting O(K log K), native histogram scan O(KH)/reserve model O(H²), native cursor startup/lookup additional. |
| Design | [include/crown/runtime/statistics.hpp](../../../../../../include/crown/runtime/statistics.hpp), [src/runtime/statistics.cpp](../../../../../../src/runtime/statistics.cpp), [src/runtime/native_statistics.cpp](../../../../../../src/runtime/native_statistics.cpp), [docs/statistics.md](../../../../../statistics.md), [docs/code_review.md](../../../../../code_review.md) |

## B0019

[Lines 100–111](../../../../../../include/crown/runtime/statistics.hpp#L100); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
class WeightedBuilder {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Build a native distribution from actual positive weighted keys. |
| inputs / outputs | Noncopyable private Data borrows one Budget, retains original account, linked key groups/output/exhaustion flag. |
| invariants | Internal callers supply one stored full-key population and call finish once; add preserves each provided key/count, not a global result aggregation API. |
| ownership | Owns funded scratch control/list/row keys and later output vectors; borrowed Budget must outlive builder. |
| failure | Construction/copy/finish allocations can throw; add catches only logical Exhausted and returns false. stop marks incomplete. |
| cost | Admit O(key bytes) per item; finish sorts K groups, native histogram O(KH) and reserve O(H²), top-K funded output; destruction walks remaining group nodes. |
| Design | [include/crown/runtime/statistics.hpp](../../../../../../include/crown/runtime/statistics.hpp), [src/runtime/statistics.cpp](../../../../../../src/runtime/statistics.cpp), [src/runtime/native_statistics.cpp](../../../../../../src/runtime/native_statistics.cpp), [docs/statistics.md](../../../../../statistics.md), [docs/code_review.md](../../../../../code_review.md) |

```text
WeightedBuilder(Budget&,const resource::MemoryAccount&);
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Admit native weighted-distribution scratch. |
| inputs / outputs | Budget/account charge work+sizeof(Data), then construct accounted unique Data and empty groups/output. |
| invariants | No new grant; Budget charges remain spent if later account allocation fails. |
| ownership | Owns scratch control, borrows Budget. |
| failure | Exhausted/OOM/account failure propagate before builder exists. |
| cost | Fixed logical charge/control allocation; no key scan. |
| Design | [include/crown/runtime/statistics.hpp](../../../../../../include/crown/runtime/statistics.hpp), [src/runtime/statistics.cpp](../../../../../../src/runtime/statistics.cpp), [src/runtime/native_statistics.cpp](../../../../../../src/runtime/native_statistics.cpp), [docs/statistics.md](../../../../../statistics.md), [docs/code_review.md](../../../../../code_review.md) |

```text
~WeightedBuilder();
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Release private weighted capture scratch. |
| inputs / outputs | Destroys unique Data and retained key-group nodes/output. |
| invariants | No runtime mutation or scratch survives final builder owner. |
| ownership | Frees each remaining native key/node/control and allocator account handles. |
| failure | Nonthrowing ordinary RAII; no allocating recovery. |
| cost | O(retained group/heavy-key owners) frees, no table rescan. |
| Design | [include/crown/runtime/statistics.hpp](../../../../../../include/crown/runtime/statistics.hpp), [src/runtime/statistics.cpp](../../../../../../src/runtime/statistics.cpp), [src/runtime/native_statistics.cpp](../../../../../../src/runtime/native_statistics.cpp), [docs/statistics.md](../../../../../statistics.md), [docs/code_review.md](../../../../../code_review.md) |

```text
WeightedBuilder(const WeightedBuilder&)=delete;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Reject weighted builder copy construction. |
| inputs / outputs | Copy operation deleted. |
| invariants | Avoids duplicating Budget-borrowing accumulation lifecycle. |
| ownership | Unique scratch ownership only. |
| failure | Compile-time rejection. |
| cost | No runtime cost. |
| Design | [include/crown/runtime/statistics.hpp](../../../../../../include/crown/runtime/statistics.hpp), [src/runtime/statistics.cpp](../../../../../../src/runtime/statistics.cpp), [src/runtime/native_statistics.cpp](../../../../../../src/runtime/native_statistics.cpp), [docs/statistics.md](../../../../../statistics.md), [docs/code_review.md](../../../../../code_review.md) |

```text
WeightedBuilder& operator=(const WeightedBuilder&)=delete;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Reject weighted builder copy assignment. |
| inputs / outputs | Copy operation deleted. |
| invariants | Avoids duplicating Budget-borrowing accumulation lifecycle. |
| ownership | Unique scratch ownership only. |
| failure | Compile-time rejection. |
| cost | No runtime cost. |
| Design | [include/crown/runtime/statistics.hpp](../../../../../../include/crown/runtime/statistics.hpp), [src/runtime/statistics.cpp](../../../../../../src/runtime/statistics.cpp), [src/runtime/native_statistics.cpp](../../../../../../src/runtime/native_statistics.cpp), [docs/statistics.md](../../../../../statistics.md), [docs/code_review.md](../../../../../code_review.md) |

```text
bool add(storage::RowView,std::uint64_t);
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Append one positive native key/count or stop on logical exhaustion. |
| inputs / outputs | RowView/count&gt;0; returns true after clone/admit/visited increment, false when exhausted. |
| invariants | Does not deduplicate inputs; caller enumerates unique stored keys. Count0 is statistics_contract error. |
| ownership | Copies row on retained original account; view not retained after call. |
| failure | Only Exhausted sets exhausted=true/false return; OOM/contract failures propagate, private partial graph remains RAII-owned. |
| cost | O(key columns/bytes) copy plus one funded list/row node; bounded accounting, no clock. |
| Design | [include/crown/runtime/statistics.hpp](../../../../../../include/crown/runtime/statistics.hpp), [src/runtime/statistics.cpp](../../../../../../src/runtime/statistics.cpp), [src/runtime/native_statistics.cpp](../../../../../../src/runtime/native_statistics.cpp), [docs/statistics.md](../../../../../statistics.md), [docs/code_review.md](../../../../../code_review.md) |

```text
void stop() noexcept;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Mark weighted builder output incomplete. |
| inputs / outputs | Sets data_-&gt;exhausted=true. |
| invariants | Previously visited keys remain progress only; no later exact finish. |
| ownership | Mutates private scalar, retains no new input. |
| failure | noexcept for a live readable object; borrowing does not validate lifetime or extend it. |
| cost | O(1), no allocation/clock. |
| Design | [include/crown/runtime/statistics.hpp](../../../../../../include/crown/runtime/statistics.hpp), [src/runtime/statistics.cpp](../../../../../../src/runtime/statistics.cpp), [src/runtime/native_statistics.cpp](../../../../../../src/runtime/native_statistics.cpp), [docs/statistics.md](../../../../../statistics.md), [docs/code_review.md](../../../../../code_review.md) |

```text
CapturedDistribution finish();
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Finalize weighted keys or return incomplete native output. |
| inputs / outputs | If not exhausted, sort/build full facts; Exhausted during finish leaves output unknown; then move output out. |
| invariants | Internal one-shot use; complete facts publish together only after finish succeeds. |
| ownership | Transfers funded histogram/heavy keys to caller; private groups remain until builder destruction. |
| failure | Logical Exhausted consumed as unknown; allocation/contract failures propagate. |
| cost | O(K log K*key comparison bytes+KH+H²) current native finish plus top-K allocation; no source runtime scan here. |
| Design | [include/crown/runtime/statistics.hpp](../../../../../../include/crown/runtime/statistics.hpp), [src/runtime/statistics.cpp](../../../../../../src/runtime/statistics.cpp), [src/runtime/native_statistics.cpp](../../../../../../src/runtime/native_statistics.cpp), [docs/statistics.md](../../../../../statistics.md), [docs/code_review.md](../../../../../code_review.md) |

## B0020

[Lines 112–112](../../../../../../include/crown/runtime/statistics.hpp#L112); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L112-L112:sha256:412ca345ccf75bf9c0806bce695be8de808b79984251a7a54d202cf6101dd451
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Close the \`namespace detail\` scope at this exact source boundary. |
| inputs / outputs | This token introduces no callable inputs or outputs. Declarations inside \`namespace detail\` define the available names, members and operations. |
| invariants | The closing brace matches the opening \`namespace detail\` at its lexical source position in include/crown/runtime/statistics.hpp; it preserves C++ namespace/type nesting. |
| ownership | The closing delimiter creates no owner. Types closed by \`namespace detail\` retain the lifetimes and allocator rules of their own fields and operations. |
| failure | No failure path executes at this closing delimiter. Failure and cleanup behavior belong to enclosed functions and owning types. |
| cost | The delimiter itself performs no runtime work; the enclosed initializers, methods and destructors carry their own costs. |
| Design | [docs/statistics.md](../../../../../statistics.md), [docs/memory_reports.md](../../../../../memory_reports.md), [docs/query_memory.md](../../../../../query_memory.md), [docs/code_specs/subsystem_contracts.md](../../../../subsystem_contracts.md) |

## B0021

[Lines 113–122](../../../../../../include/crown/runtime/statistics.hpp#L113); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct Capture {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Own a standalone stamped table capture. |
| inputs / outputs | Storage stamp, shared source layout/optional shared Projection token/index, exact table cardinality and ordinary Distribution. |
| invariants | Stamp is storage invalidation only; legacy metadata must describe actual selected population. Missing distribution facts are unknown, not zero. |
| ownership | Owns ordinary caller-allocator rows/strings/vectors/set nodes described above. Copies deep-copy those members; it is neither a cheap shared handle nor a native owner capability. |
| failure | Owning construction/copy can allocate and throw. Ordinary aggregate/memberwise assignment has no special whole-record publication guarantee; no catch/fallback is added. |
| cost | Layout/projection copies share immutable tokens; Distribution copies deep-copy ordinary histogram/keys. Release ordinary report keys/vectors and possibly last schema/projection metadata; no live table retained. |
| Design | [include/crown/runtime/statistics.hpp](../../../../../../include/crown/runtime/statistics.hpp), [src/runtime/statistics.cpp](../../../../../../src/runtime/statistics.cpp), [src/runtime/native_statistics.cpp](../../../../../../src/runtime/native_statistics.cpp), [docs/statistics.md](../../../../../statistics.md), [docs/code_review.md](../../../../../code_review.md) |

## B0022

[Lines 123–133](../../../../../../include/crown/runtime/statistics.hpp#L123); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Capture projection(const storage::ReferenceTable&, const storage::Projection&, Budget&);
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Capture standalone projection statistics from ReferenceTable. |
| inputs / outputs | Actual quiescent table, compiled matching projection or admitted IndexId, shared Budget; nonreference overloads also borrow native IndexWorkAllowance. Accounted index overload receives matching legacy Projection metadata. |
| invariants | Projection overload validates source layout token; index already admitted. Accounted index overload relies on caller matching legacy metadata, not a new token check. Never creates index/schema on scan. |
| ownership | Returns ordinary owning Distribution and shared immutable layout/projection handles; native source borrowed only synchronously. |
| failure | Logical/storage-work exhaustion returns unknown distribution/progress where caught; cursor admission, invalid identity/layout, corruption and allocation failures can propagate. |
| cost | Projection O(NK*key bytes) grouping or index K-key scan; standalone finish count-sort O(K log K), adjacent histogram lookup O(K), repeated new-bin reserve/model O(H²), top-K Row exports/allocations. No constant-time/clock claim. |
| Design | [include/crown/runtime/statistics.hpp](../../../../../../include/crown/runtime/statistics.hpp), [src/runtime/statistics.cpp](../../../../../../src/runtime/statistics.cpp), [src/runtime/native_statistics.cpp](../../../../../../src/runtime/native_statistics.cpp), [docs/statistics.md](../../../../../statistics.md), [docs/code_review.md](../../../../../code_review.md) |

```text
Capture index(const storage::ReferenceTable&, IndexId, Budget&);
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Capture standalone index statistics from ReferenceTable. |
| inputs / outputs | Actual quiescent table, compiled matching projection or admitted IndexId, shared Budget; nonreference overloads also borrow native IndexWorkAllowance. Accounted index overload receives matching legacy Projection metadata. |
| invariants | Projection overload validates source layout token; index already admitted. Accounted index overload relies on caller matching legacy metadata, not a new token check. Never creates index/schema on scan. |
| ownership | Returns ordinary owning Distribution and shared immutable layout/projection handles; native source borrowed only synchronously. |
| failure | Logical/storage-work exhaustion returns unknown distribution/progress where caught; cursor admission, invalid identity/layout, corruption and allocation failures can propagate. |
| cost | Projection O(NK*key bytes) grouping or index K-key scan; standalone finish count-sort O(K log K), adjacent histogram lookup O(K), repeated new-bin reserve/model O(H²), top-K Row exports/allocations. No constant-time/clock claim. |
| Design | [include/crown/runtime/statistics.hpp](../../../../../../include/crown/runtime/statistics.hpp), [src/runtime/statistics.cpp](../../../../../../src/runtime/statistics.cpp), [src/runtime/native_statistics.cpp](../../../../../../src/runtime/native_statistics.cpp), [docs/statistics.md](../../../../../statistics.md), [docs/code_review.md](../../../../../code_review.md) |

```text
Capture projection(const storage::StorageTable&,const storage::Projection&,Budget&,storage::IndexWorkAllowance*);
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Capture standalone projection statistics from StorageTable. |
| inputs / outputs | Actual quiescent table, compiled matching projection or admitted IndexId, shared Budget; nonreference overloads also borrow native IndexWorkAllowance. Accounted index overload receives matching legacy Projection metadata. |
| invariants | Projection overload validates source layout token; index already admitted. Accounted index overload relies on caller matching legacy metadata, not a new token check. Never creates index/schema on scan. |
| ownership | Returns ordinary owning Distribution and shared immutable layout/projection handles; native source borrowed only synchronously. |
| failure | Logical/storage-work exhaustion returns unknown distribution/progress where caught; cursor admission, invalid identity/layout, corruption and allocation failures can propagate. |
| cost | Projection O(NK*key bytes) grouping or index K-key scan; standalone finish count-sort O(K log K), adjacent histogram lookup O(K), repeated new-bin reserve/model O(H²), top-K Row exports/allocations. No constant-time/clock claim. |
| Design | [include/crown/runtime/statistics.hpp](../../../../../../include/crown/runtime/statistics.hpp), [src/runtime/statistics.cpp](../../../../../../src/runtime/statistics.cpp), [src/runtime/native_statistics.cpp](../../../../../../src/runtime/native_statistics.cpp), [docs/statistics.md](../../../../../statistics.md), [docs/code_review.md](../../../../../code_review.md) |

```text
Capture index(const storage::StorageTable&,IndexId,Budget&,storage::IndexWorkAllowance*);
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Capture standalone index statistics from StorageTable. |
| inputs / outputs | Actual quiescent table, compiled matching projection or admitted IndexId, shared Budget; nonreference overloads also borrow native IndexWorkAllowance. Accounted index overload receives matching legacy Projection metadata. |
| invariants | Projection overload validates source layout token; index already admitted. Accounted index overload relies on caller matching legacy metadata, not a new token check. Never creates index/schema on scan. |
| ownership | Returns ordinary owning Distribution and shared immutable layout/projection handles; native source borrowed only synchronously. |
| failure | Logical/storage-work exhaustion returns unknown distribution/progress where caught; cursor admission, invalid identity/layout, corruption and allocation failures can propagate. |
| cost | Projection O(NK*key bytes) grouping or index K-key scan; standalone finish count-sort O(K log K), adjacent histogram lookup O(K), repeated new-bin reserve/model O(H²), top-K Row exports/allocations. No constant-time/clock claim. |
| Design | [include/crown/runtime/statistics.hpp](../../../../../../include/crown/runtime/statistics.hpp), [src/runtime/statistics.cpp](../../../../../../src/runtime/statistics.cpp), [src/runtime/native_statistics.cpp](../../../../../../src/runtime/native_statistics.cpp), [docs/statistics.md](../../../../../statistics.md), [docs/code_review.md](../../../../../code_review.md) |

```text
Capture index(const storage::AccountedStorageTable&,IndexId,const storage::Projection&,Budget&,storage::IndexWorkAllowance*);
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Capture standalone index statistics from AccountedStorageTable. |
| inputs / outputs | Quiescent actual table/id, caller legacy Projection, shared statistics Budget and optional native IndexWorkAllowance; return ordinary Capture with authentic native index descriptors. |
| invariants | Exact capture requires matching complete source/target descriptors and ordered field IDs. Recreated equal tokens are accepted. An exhausted comparison can return incomplete authentic metadata; it never labels a prefix distribution exact. No index/schema is registered here. |
| ownership | Returns ordinary owning Distribution and shared immutable layout/projection handles; native source borrowed only synchronously. |
| failure | Completed mismatch validation throws invalid_statistics_request. Cursor/descriptor admission before the try can fail; caught logical/storage work exhaustion returns incomplete, while unrelated errors propagate. |
| cost | Projection O(NK*key bytes) grouping or index K-key scan; standalone finish count-sort O(K log K), adjacent histogram lookup O(K), repeated new-bin reserve/model O(H²), top-K Row exports/allocations. No constant-time/clock claim. Accounted metadata validation additionally charges field scans and both context binding lengths against the same statistics work budget. |
| Design | [include/crown/runtime/statistics.hpp](../../../../../../include/crown/runtime/statistics.hpp), [src/runtime/statistics.cpp](../../../../../../src/runtime/statistics.cpp), [src/runtime/native_statistics.cpp](../../../../../../src/runtime/native_statistics.cpp), [docs/statistics.md](../../../../../statistics.md), [docs/code_review.md](../../../../../code_review.md) |
