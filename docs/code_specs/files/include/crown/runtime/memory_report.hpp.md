# `include/crown/runtime/memory_report.hpp` — block usage map

[Source](../../../../../../include/crown/runtime/memory_report.hpp) · [Source index](../../../../README.md) · [Subsystem contracts](../../../../subsystem_contracts.md) · [Reviewed primitives](../../../../primitives.md)

Capture/reconcile account allocation partitions with logical runtime ownership.

Snapshot SHA-256: `80951d835f309995106221eb367ad67de9a3bfd4222eefd93c99c51d8581cd78`. 90 lines partitioned into 18 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [statistics](../../../../subsystem_contracts.md#statistics). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/statistics.md](../../../../../statistics.md), [docs/observability.md](../../../../../observability.md), [docs/memory_reports.md](../../../../../memory_reports.md), [docs/ranking_evaluation.md](../../../../../ranking_evaluation.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–12](../../../../../../include/crown/runtime/memory_report.hpp#L1) | Imports dependencies; guards repeated header inclusion; declares namespace scope; declares types or opens a type body. |  · [reviewed contract](#b0001) |
| [B0002 · 13–13](../../../../../../include/crown/runtime/memory_report.hpp#L13) | Type/record definition: enum class Layer |  · [reviewed contract](#b0002) |
| [B0003 · 14–14](../../../../../../include/crown/runtime/memory_report.hpp#L14) | Type/record definition: enum class Availability |  · [reviewed contract](#b0003) |
| [B0004 · 15–15](../../../../../../include/crown/runtime/memory_report.hpp#L15) | Type/record definition: enum class Stop |  · [reviewed contract](#b0004) |
| [B0005 · 16–19](../../../../../../include/crown/runtime/memory_report.hpp#L16) | Type/record definition: struct Limits |  · [reviewed contract](#b0005) |
| [B0006 · 20–20](../../../../../../include/crown/runtime/memory_report.hpp#L20) | Type/record definition: struct Usage |  · [reviewed contract](#b0006) |
| [B0007 · 21–27](../../../../../../include/crown/runtime/memory_report.hpp#L21) | Type/record definition: struct Snapshot |  · [reviewed contract](#b0007) |
| [B0008 · 28–28](../../../../../../include/crown/runtime/memory_report.hpp#L28) | Type/record definition: enum class TableScope |  · [reviewed contract](#b0008) |
| [B0009 · 29–39](../../../../../../include/crown/runtime/memory_report.hpp#L29) | Type/record definition: struct Table |  · [reviewed contract](#b0009) |
| [B0010 · 40–46](../../../../../../include/crown/runtime/memory_report.hpp#L40) | Type/record definition: struct SupportNode |  · [reviewed contract](#b0010) |
| [B0011 · 47–51](../../../../../../include/crown/runtime/memory_report.hpp#L47) | Type/record definition: struct Derivations |  · [reviewed contract](#b0011) |
| [B0012 · 52–52](../../../../../../include/crown/runtime/memory_report.hpp#L52) | Type/record definition: struct FactorCounts |  · [reviewed contract](#b0012) |
| [B0013 · 53–57](../../../../../../include/crown/runtime/memory_report.hpp#L53) | Type/record definition: struct DeltaFactor |  · [reviewed contract](#b0013) |
| [B0014 · 58–58](../../../../../../include/crown/runtime/memory_report.hpp#L58) | Type/record definition: struct Coordinator |  · [reviewed contract](#b0014) |
| [B0015 · 59–63](../../../../../../include/crown/runtime/memory_report.hpp#L59) | declares aliases; declares types or opens a type body; declares values/defaults or compile-time conditions. | source comment (unverified): // The allocation partition is account-wide, including held generations, reports, · [reviewed contract](#b0015) |
| [B0016 · 64–84](../../../../../../include/crown/runtime/memory_report.hpp#L64) | Type/record definition: class Report | returns *this; source comment (unverified): // The allocation partition is account-wide, including held generations, reports, · [reviewed contract](#b0016) |
| [B0017 · 85–85](../../../../../../include/crown/runtime/memory_report.hpp#L85) | Type/record definition: struct Attempt |  · [reviewed contract](#b0017) |
| [B0018 · 86–90](../../../../../../include/crown/runtime/memory_report.hpp#L86) | declares values/defaults or compile-time conditions. | source comment (unverified): // namespace crown::runtime::memory · [reviewed contract](#b0018) |

## B0001

[Lines 1–12](../../../../../../include/crown/runtime/memory_report.hpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
#pragma once
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Expose native account memory-capture types. |
| inputs / outputs | Forward runtime owners and private Builder/Access/Data; includes table statistics and original-account allocator. |
| invariants | Captures are explicit diagnostics, never hot update hooks or process RSS measurements. |
| ownership | No live report allocated at inclusion. |
| failure | Compile-time declarations only. |
| cost | No runtime action at inclusion. |
| Design | [include/crown/runtime/memory_report.hpp](../../../../../../include/crown/runtime/memory_report.hpp), [src/runtime/memory_report.cpp](../../../../../../src/runtime/memory_report.cpp), [src/runtime/memory_report_detail.hpp](../../../../../../src/runtime/memory_report_detail.hpp), [docs/memory_reports.md](../../../../../memory_reports.md), [docs/code_review.md](../../../../../code_review.md) |

## B0002

[Lines 13–13](../../../../../../include/crown/runtime/memory_report.hpp#L13); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
enum class Layer {support,physical,delta,session};
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Tag captured runtime layer. |
| inputs / outputs | support/physical/delta/session. |
| invariants | Layer qualifies recorded committed counts, separate from account-wide allocation partition. |
| ownership | Caller owns inline numeric/tag fields; this record retains no backing runtime, rows, strings or allocation grant. |
| failure | The declaration does not validate public fields or translate failure. Actual factories/consumers perform the stated checks. |
| cost | Constant-size enum/tag, no allocation, scan or clock. Arbitrary enum casts are not admitted automatically. |
| Design | [include/crown/runtime/memory_report.hpp](../../../../../../include/crown/runtime/memory_report.hpp), [src/runtime/memory_report.cpp](../../../../../../src/runtime/memory_report.cpp), [src/runtime/memory_report_detail.hpp](../../../../../../src/runtime/memory_report_detail.hpp), [docs/memory_reports.md](../../../../../memory_reports.md), [docs/code_review.md](../../../../../code_review.md) |

## B0003

[Lines 14–14](../../../../../../include/crown/runtime/memory_report.hpp#L14); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
enum class Availability {committed,pending,released};
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Tag memory snapshot availability. |
| inputs / outputs | committed/pending/released. |
| invariants | Pending/released reports retain account partition but no committed table/operator counts. |
| ownership | Caller owns inline numeric/tag fields; this record retains no backing runtime, rows, strings or allocation grant. |
| failure | The declaration does not validate public fields or translate failure. Actual factories/consumers perform the stated checks. |
| cost | Constant-size enum/tag, no allocation, scan or clock. Arbitrary enum casts are not admitted automatically. |
| Design | [include/crown/runtime/memory_report.hpp](../../../../../../include/crown/runtime/memory_report.hpp), [src/runtime/memory_report.cpp](../../../../../../src/runtime/memory_report.cpp), [src/runtime/memory_report_detail.hpp](../../../../../../src/runtime/memory_report_detail.hpp), [docs/memory_reports.md](../../../../../memory_reports.md), [docs/code_review.md](../../../../../code_review.md) |

## B0004

[Lines 15–15](../../../../../../include/crown/runtime/memory_report.hpp#L15); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
enum class Stop {complete,invalid_handle,work_limit,owner_limit,table_limit,operator_limit,allocation_failure,overflow,inconsistent};
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Tag memory capture stop outcome. |
| inputs / outputs | Complete/invalid handle/work/owner/table/operator/allocation/overflow/inconsistent. |
| invariants | Failure returns no partial Report; attempted Usage and historical allocation counters can remain spent. |
| ownership | Caller owns inline numeric/tag fields; this record retains no backing runtime, rows, strings or allocation grant. |
| failure | The declaration does not validate public fields or translate failure. Actual factories/consumers perform the stated checks. |
| cost | Constant-size enum/tag, no allocation, scan or clock. Arbitrary enum casts are not admitted automatically. |
| Design | [include/crown/runtime/memory_report.hpp](../../../../../../include/crown/runtime/memory_report.hpp), [src/runtime/memory_report.cpp](../../../../../../src/runtime/memory_report.cpp), [src/runtime/memory_report_detail.hpp](../../../../../../src/runtime/memory_report_detail.hpp), [docs/memory_reports.md](../../../../../memory_reports.md), [docs/code_review.md](../../../../../code_review.md) |

## B0005

[Lines 16–19](../../../../../../include/crown/runtime/memory_report.hpp#L16); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct Limits {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Bound explicit memory capture diagnostics. |
| inputs / outputs | work16M and owner/table/operator maximums65536. |
| invariants | These caps bound logical scan/sort/count work and report size; original account still admits actual control/arrays/scratch independently. |
| ownership | Caller owns inline numeric/tag fields; this record retains no backing runtime, rows, strings or allocation grant. |
| failure | The declaration does not validate public fields or translate failure. Actual factories/consumers perform the stated checks. |
| cost | Fixed inline scalar/enum/optional/array storage and bounded copies; no dynamic payload, scan, clock or allocation. |
| Design | [include/crown/runtime/memory_report.hpp](../../../../../../include/crown/runtime/memory_report.hpp), [src/runtime/memory_report.cpp](../../../../../../src/runtime/memory_report.cpp), [src/runtime/memory_report_detail.hpp](../../../../../../src/runtime/memory_report_detail.hpp), [docs/memory_reports.md](../../../../../memory_reports.md), [docs/code_review.md](../../../../../code_review.md) |

## B0006

[Lines 20–20](../../../../../../include/crown/runtime/memory_report.hpp#L20); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct Usage {std::uint64_t work=0;std::size_t owners=0,tables=0,operators=0;};
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Carry memory-capture processing progress. |
| inputs / outputs | work and observed owners/tables/operators counts. |
| invariants | Failed attempts can retain spent work; these are not byte/RSS totals or new allowances. |
| ownership | Caller owns inline numeric/tag fields; this record retains no backing runtime, rows, strings or allocation grant. |
| failure | The declaration does not validate public fields or translate failure. Actual factories/consumers perform the stated checks. |
| cost | Fixed inline scalar/enum/optional/array storage and bounded copies; no dynamic payload, scan, clock or allocation. |
| Design | [include/crown/runtime/memory_report.hpp](../../../../../../include/crown/runtime/memory_report.hpp), [src/runtime/memory_report.cpp](../../../../../../src/runtime/memory_report.cpp), [src/runtime/memory_report_detail.hpp](../../../../../../src/runtime/memory_report_detail.hpp), [docs/memory_reports.md](../../../../../memory_reports.md), [docs/code_review.md](../../../../../code_review.md) |

## B0007

[Lines 21–27](../../../../../../include/crown/runtime/memory_report.hpp#L21); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct Snapshot {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Store one detached account observation and runtime identity labels. |
| inputs / outputs | Layer/availability, runtime owner/sequence, fixed64 physical hash and MemoryStatistics counter arrays. |
| invariants | Includes report own resident allocations at captured instant, after scratch release. Numeric public fields do not retain/fund account or prove current state. Historical peaks are not extra resident bytes. |
| ownership | Caller owns inline numeric/tag fields; this record retains no backing runtime, rows, strings or allocation grant. |
| failure | The declaration does not validate public fields or translate failure. Actual factories/consumers perform the stated checks. |
| cost | Fixed hash/statistics arrays and scalars copied; no account control/heap retained by this Snapshot alone. |
| Design | [include/crown/runtime/memory_report.hpp](../../../../../../include/crown/runtime/memory_report.hpp), [src/runtime/memory_report.cpp](../../../../../../src/runtime/memory_report.cpp), [src/runtime/memory_report_detail.hpp](../../../../../../src/runtime/memory_report_detail.hpp), [docs/memory_reports.md](../../../../../memory_reports.md), [docs/code_review.md](../../../../../code_review.md) |

## B0008

[Lines 28–28](../../../../../../include/crown/runtime/memory_report.hpp#L28); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
enum class TableScope {support,physical_source};
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Qualify a recorded table relation. |
| inputs / outputs | support versus physical_source. |
| invariants | Relation IDs are scoped by table population/storage owner; equal IDs across scopes are not the same allocation. |
| ownership | Caller owns inline numeric/tag fields; this record retains no backing runtime, rows, strings or allocation grant. |
| failure | The declaration does not validate public fields or translate failure. Actual factories/consumers perform the stated checks. |
| cost | Constant-size enum/tag, no allocation, scan or clock. Arbitrary enum casts are not admitted automatically. |
| Design | [include/crown/runtime/memory_report.hpp](../../../../../../include/crown/runtime/memory_report.hpp), [src/runtime/memory_report.cpp](../../../../../../src/runtime/memory_report.cpp), [src/runtime/memory_report_detail.hpp](../../../../../../src/runtime/memory_report_detail.hpp), [docs/memory_reports.md](../../../../../memory_reports.md), [docs/code_review.md](../../../../../code_review.md) |

## B0009

[Lines 29–39](../../../../../../include/crown/runtime/memory_report.hpp#L29); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct Table {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Store fixed diagnostics for one actual native table. |
| inputs / outputs | Scope/relation/role, optional node/base, storage owner/backend/live records and fixed native memory-statistics variant. |
| invariants | Actual table and arena owners join owners() partition. Several bindings may share an owner; do not add joins again. |
| ownership | Caller owns inline numeric/tag fields; this record retains no backing runtime, rows, strings or allocation grant. |
| failure | The declaration does not validate public fields or translate failure. Actual factories/consumers perform the stated checks. |
| cost | Bounded fixed statistics/variant copy, not a table row snapshot or vector allocation. |
| Design | [include/crown/runtime/memory_report.hpp](../../../../../../include/crown/runtime/memory_report.hpp), [src/runtime/memory_report.cpp](../../../../../../src/runtime/memory_report.cpp), [src/runtime/memory_report_detail.hpp](../../../../../../src/runtime/memory_report_detail.hpp), [docs/memory_reports.md](../../../../../memory_reports.md), [docs/code_review.md](../../../../../code_review.md) |

## B0010

[Lines 40–46](../../../../../../include/crown/runtime/memory_report.hpp#L40); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct SupportNode {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Store support metadata population counts. |
| inputs / outputs | Node/actual attribution, records/S/P, optional E and child flags. |
| invariants | Absent E is unavailable/not applicable, not measured zero. Counts do not imply fixed bytes or allocate/own support state. |
| ownership | Caller owns inline numeric/tag fields; this record retains no backing runtime, rows, strings or allocation grant. |
| failure | The declaration does not validate public fields or translate failure. Actual factories/consumers perform the stated checks. |
| cost | Fixed inline scalar/enum/optional/array storage and bounded copies; no dynamic payload, scan, clock or allocation. |
| Design | [include/crown/runtime/memory_report.hpp](../../../../../../include/crown/runtime/memory_report.hpp), [src/runtime/memory_report.cpp](../../../../../../src/runtime/memory_report.cpp), [src/runtime/memory_report_detail.hpp](../../../../../../src/runtime/memory_report_detail.hpp), [docs/memory_reports.md](../../../../../memory_reports.md), [docs/code_review.md](../../../../../code_review.md) |

## B0011

[Lines 47–51](../../../../../../include/crown/runtime/memory_report.hpp#L47); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct Derivations {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Store one physical occurrence derivation count. |
| inputs / outputs | OccurrenceId/actual attribution/key count. |
| invariants | This describes current committed derivation metadata, distinct from account-wide retained allocations. |
| ownership | Caller owns inline numeric/tag fields; this record retains no backing runtime, rows, strings or allocation grant. |
| failure | The declaration does not validate public fields or translate failure. Actual factories/consumers perform the stated checks. |
| cost | Fixed inline scalar/enum/optional/array storage and bounded copies; no dynamic payload, scan, clock or allocation. |
| Design | [include/crown/runtime/memory_report.hpp](../../../../../../include/crown/runtime/memory_report.hpp), [src/runtime/memory_report.cpp](../../../../../../src/runtime/memory_report.cpp), [src/runtime/memory_report_detail.hpp](../../../../../../src/runtime/memory_report_detail.hpp), [docs/memory_reports.md](../../../../../memory_reports.md), [docs/code_review.md](../../../../../code_review.md) |

## B0012

[Lines 52–52](../../../../../../include/crown/runtime/memory_report.hpp#L52); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct FactorCounts {std::uint64_t rows,parent_keys,parent_rows,child_keys,child_rows;};
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Store materialized Delta factor counts. |
| inputs / outputs | Rows, parent keys/rows and child keys/rows. |
| invariants | Counts qualify a materialized factor only; unmaterialized image is unavailable, not zero. |
| ownership | Caller owns inline numeric/tag fields; this record retains no backing runtime, rows, strings or allocation grant. |
| failure | The declaration does not validate public fields or translate failure. Actual factories/consumers perform the stated checks. |
| cost | Fixed inline scalar/enum/optional/array storage and bounded copies; no dynamic payload, scan, clock or allocation. |
| Design | [include/crown/runtime/memory_report.hpp](../../../../../../include/crown/runtime/memory_report.hpp), [src/runtime/memory_report.cpp](../../../../../../src/runtime/memory_report.cpp), [src/runtime/memory_report_detail.hpp](../../../../../../src/runtime/memory_report_detail.hpp), [docs/memory_reports.md](../../../../../memory_reports.md), [docs/code_review.md](../../../../../code_review.md) |

## B0013

[Lines 53–57](../../../../../../include/crown/runtime/memory_report.hpp#L53); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct DeltaFactor {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Identify a Delta factor and optional materialization. |
| inputs / outputs | Node/actual attribution/optional FactorCounts. |
| invariants | Owner key may be present even without materialized counts; bytes partitioned once in owners(). |
| ownership | Caller owns inline numeric/tag fields; this record retains no backing runtime, rows, strings or allocation grant. |
| failure | The declaration does not validate public fields or translate failure. Actual factories/consumers perform the stated checks. |
| cost | Fixed inline scalar/enum/optional/array storage and bounded copies; no dynamic payload, scan, clock or allocation. |
| Design | [include/crown/runtime/memory_report.hpp](../../../../../../include/crown/runtime/memory_report.hpp), [src/runtime/memory_report.cpp](../../../../../../src/runtime/memory_report.cpp), [src/runtime/memory_report_detail.hpp](../../../../../../src/runtime/memory_report_detail.hpp), [docs/memory_reports.md](../../../../../memory_reports.md), [docs/code_review.md](../../../../../code_review.md) |

## B0014

[Lines 58–58](../../../../../../include/crown/runtime/memory_report.hpp#L58); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct Coordinator {Layer layer;resource::MemoryAttribution attribution;};
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Identify coordinator allocation attribution. |
| inputs / outputs | Layer and actual MemoryAttribution. |
| invariants | A diagnostic owner label neither retains coordinator nor creates a grant. |
| ownership | Caller owns inline numeric/tag fields; this record retains no backing runtime, rows, strings or allocation grant. |
| failure | The declaration does not validate public fields or translate failure. Actual factories/consumers perform the stated checks. |
| cost | Fixed inline scalar/enum/optional/array storage and bounded copies; no dynamic payload, scan, clock or allocation. |
| Design | [include/crown/runtime/memory_report.hpp](../../../../../../include/crown/runtime/memory_report.hpp), [src/runtime/memory_report.cpp](../../../../../../src/runtime/memory_report.cpp), [src/runtime/memory_report_detail.hpp](../../../../../../src/runtime/memory_report_detail.hpp), [docs/memory_reports.md](../../../../../memory_reports.md), [docs/code_review.md](../../../../../code_review.md) |

## B0015

[Lines 59–63](../../../../../../include/crown/runtime/memory_report.hpp#L59); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
using Operator=std::variant<SupportNode,Derivations,DeltaFactor,Coordinator>;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Represent a fixed operator memory-count row. |
| inputs / outputs | Operator variant is SupportNode/Derivations/DeltaFactor/Coordinator. |
| invariants | Every alternative is an inline numeric record; no runtime row/graph pointer retained. |
| ownership | Caller owns inline numeric/tag fields; this record retains no backing runtime, rows, strings or allocation grant. |
| failure | The declaration does not validate public fields or translate failure. Actual factories/consumers perform the stated checks. |
| cost | Fixed inline scalar/enum/optional/array storage and bounded copies; no dynamic payload, scan, clock or allocation. |
| Design | [include/crown/runtime/memory_report.hpp](../../../../../../include/crown/runtime/memory_report.hpp), [src/runtime/memory_report.cpp](../../../../../../src/runtime/memory_report.cpp), [src/runtime/memory_report_detail.hpp](../../../../../../src/runtime/memory_report_detail.hpp), [docs/memory_reports.md](../../../../../memory_reports.md), [docs/code_review.md](../../../../../code_review.md) |

```text
template<class T> using Vector=std::vector<T,resource::OwnerAllocator<T>>;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Define transferable funded report arrays. |
| inputs / outputs | Vector&lt;T&gt; uses OwnerAllocator&lt;T&gt;. |
| invariants | Assignment/move/swap propagate storage account/attribution; no new allowance. Element ownership costs depend on T, not the alias. |
| ownership | Vector owns original-account capacity. Current report arrays hold fixed numeric rows; copying a vector itself deep-copies elements. |
| failure | Allocations may fail; empty vector binding allocates no payload. |
| cost | O(element count) vector copy/allocation; moves transfer storage; trivial report rows release one buffer. |
| Design | [include/crown/runtime/memory_report.hpp](../../../../../../include/crown/runtime/memory_report.hpp), [src/runtime/memory_report.cpp](../../../../../../src/runtime/memory_report.cpp), [src/runtime/memory_report_detail.hpp](../../../../../../src/runtime/memory_report_detail.hpp), [docs/memory_reports.md](../../../../../memory_reports.md), [docs/code_review.md](../../../../../code_review.md), [include/crown/resource/owner_allocator.hpp](../../../../../../include/crown/resource/owner_allocator.hpp) |

## B0016

[Lines 64–84](../../../../../../include/crown/runtime/memory_report.hpp#L64); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
class Report {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Share an immutable actual-account memory report. |
| inputs / outputs | Factory Data stores account, fixed Snapshot, owner/table/operator arrays and Usage. |
| invariants | owners() partitions account-wide allocations, including held generations/reports/cursors/output; counts describe recorded committed runtime only. Keys may be shared; sum owner partition once. |
| ownership | Shared_ptr retains actual report arrays and account, not runtime/plan. Copies and explicit copy-like moves share Data; all returned views borrow it. |
| failure | Capture can fail before publication; handle reads/copies are noexcept. Final release frees actual Data/control and numeric arrays, no re-capture. |
| cost | O(1) handle copies/refcounts; capture scans/sorts account and storage; final release deallocates fixed number of trivial-row arrays plus control/account. |
| Design | [include/crown/runtime/memory_report.hpp](../../../../../../include/crown/runtime/memory_report.hpp), [src/runtime/memory_report.cpp](../../../../../../src/runtime/memory_report.cpp), [src/runtime/memory_report_detail.hpp](../../../../../../src/runtime/memory_report_detail.hpp), [docs/memory_reports.md](../../../../../memory_reports.md), [docs/code_review.md](../../../../../code_review.md), [src/resource/memory.cpp](../../../../../../src/resource/memory.cpp) |

```text
Report(const Report&) noexcept=default;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Provide Report copy construction. |
| inputs / outputs | Retains other shared Data; explicit move also copies pointer so both factory handles remain readable. |
| invariants | Old destination views survive only if another handle retains old Data. |
| ownership | Shares actual arrays/account; assignment may release last old Data. |
| failure | noexcept; no deep vector copy. |
| cost | O(1) refcount, plus old Data/array block cleanup on last destination release. |
| Design | [include/crown/runtime/memory_report.hpp](../../../../../../include/crown/runtime/memory_report.hpp), [src/runtime/memory_report.cpp](../../../../../../src/runtime/memory_report.cpp), [src/runtime/memory_report_detail.hpp](../../../../../../src/runtime/memory_report_detail.hpp), [docs/memory_reports.md](../../../../../memory_reports.md), [docs/code_review.md](../../../../../code_review.md) |

```text
Report& operator=(const Report&) noexcept=default;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Provide Report copy assignment. |
| inputs / outputs | Retains other shared Data; explicit move also copies pointer so both factory handles remain readable. |
| invariants | Old destination views survive only if another handle retains old Data. |
| ownership | Shares actual arrays/account; assignment may release last old Data. |
| failure | noexcept; no deep vector copy. |
| cost | O(1) refcount, plus old Data/array block cleanup on last destination release. |
| Design | [include/crown/runtime/memory_report.hpp](../../../../../../include/crown/runtime/memory_report.hpp), [src/runtime/memory_report.cpp](../../../../../../src/runtime/memory_report.cpp), [src/runtime/memory_report_detail.hpp](../../../../../../src/runtime/memory_report_detail.hpp), [docs/memory_reports.md](../../../../../memory_reports.md), [docs/code_review.md](../../../../../code_review.md) |

```text
Report(Report&& other) noexcept:data_(other.data_) {}
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Provide Report copy-like move construction. |
| inputs / outputs | Retains other shared Data; explicit move also copies pointer so both factory handles remain readable. |
| invariants | Old destination views survive only if another handle retains old Data. |
| ownership | Shares actual arrays/account; assignment may release last old Data. |
| failure | noexcept; no deep vector copy. |
| cost | O(1) refcount, plus old Data/array block cleanup on last destination release. |
| Design | [include/crown/runtime/memory_report.hpp](../../../../../../include/crown/runtime/memory_report.hpp), [src/runtime/memory_report.cpp](../../../../../../src/runtime/memory_report.cpp), [src/runtime/memory_report_detail.hpp](../../../../../../src/runtime/memory_report_detail.hpp), [docs/memory_reports.md](../../../../../memory_reports.md), [docs/code_review.md](../../../../../code_review.md) |

```text
Report& operator=(Report&& other) noexcept {data_=other.data_;return *this;}
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Provide Report copy-like move assignment. |
| inputs / outputs | Retains other shared Data; explicit move also copies pointer so both factory handles remain readable. |
| invariants | Old destination views survive only if another handle retains old Data. |
| ownership | Shares actual arrays/account; assignment may release last old Data. |
| failure | noexcept; no deep vector copy. |
| cost | O(1) refcount, plus old Data/array block cleanup on last destination release. |
| Design | [include/crown/runtime/memory_report.hpp](../../../../../../include/crown/runtime/memory_report.hpp), [src/runtime/memory_report.cpp](../../../../../../src/runtime/memory_report.cpp), [src/runtime/memory_report_detail.hpp](../../../../../../src/runtime/memory_report_detail.hpp), [docs/memory_reports.md](../../../../../memory_reports.md), [docs/code_review.md](../../../../../code_review.md) |

```text
const Snapshot& snapshot() const noexcept;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Borrow memory Report snapshot. |
| inputs / outputs | Returns const Snapshot& from immutable Data. |
| invariants | Snapshot counters include own report storage and all remaining account owners at that instant. |
| ownership | Retain a Report sharing Data while reference is used; getter itself does not retain Data. |
| failure | noexcept for a live readable object; borrowing does not validate lifetime or extend it. |
| cost | O(1) fixed member/view lookup; no allocation or clock. |
| Design | [include/crown/runtime/memory_report.hpp](../../../../../../include/crown/runtime/memory_report.hpp), [src/runtime/memory_report.cpp](../../../../../../src/runtime/memory_report.cpp), [src/runtime/memory_report_detail.hpp](../../../../../../src/runtime/memory_report_detail.hpp), [docs/memory_reports.md](../../../../../memory_reports.md), [docs/code_review.md](../../../../../code_review.md) |

```text
const Vector<resource::AttributedMemoryStatistics>& owners() const noexcept;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Borrow memory Report owner partition. |
| inputs / outputs | Returns const Vector&lt;AttributedMemoryStatistics&gt;& from immutable Data. |
| invariants | Sorted unique actual attributions; sum each row once. |
| ownership | Retain a Report sharing Data while reference is used; getter itself does not retain Data. |
| failure | noexcept for a live readable object; borrowing does not validate lifetime or extend it. |
| cost | O(1) fixed member/view lookup; no allocation or clock. |
| Design | [include/crown/runtime/memory_report.hpp](../../../../../../include/crown/runtime/memory_report.hpp), [src/runtime/memory_report.cpp](../../../../../../src/runtime/memory_report.cpp), [src/runtime/memory_report_detail.hpp](../../../../../../src/runtime/memory_report_detail.hpp), [docs/memory_reports.md](../../../../../memory_reports.md), [docs/code_review.md](../../../../../code_review.md) |

```text
const Vector<Table>& tables() const noexcept;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Borrow memory Report table diagnostics. |
| inputs / outputs | Returns const Vector&lt;Table&gt;& from immutable Data. |
| invariants | Current committed table joins can share owners. |
| ownership | Retain a Report sharing Data while reference is used; getter itself does not retain Data. |
| failure | noexcept for a live readable object; borrowing does not validate lifetime or extend it. |
| cost | O(1) fixed member/view lookup; no allocation or clock. |
| Design | [include/crown/runtime/memory_report.hpp](../../../../../../include/crown/runtime/memory_report.hpp), [src/runtime/memory_report.cpp](../../../../../../src/runtime/memory_report.cpp), [src/runtime/memory_report_detail.hpp](../../../../../../src/runtime/memory_report_detail.hpp), [docs/memory_reports.md](../../../../../memory_reports.md), [docs/code_review.md](../../../../../code_review.md) |

```text
const Vector<Operator>& operators() const noexcept;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Borrow memory Report operator counts. |
| inputs / outputs | Returns const Vector&lt;Operator&gt;& from immutable Data. |
| invariants | Counts describe recorded runtime, not all retained owner generations. |
| ownership | Retain a Report sharing Data while reference is used; getter itself does not retain Data. |
| failure | noexcept for a live readable object; borrowing does not validate lifetime or extend it. |
| cost | O(1) fixed member/view lookup; no allocation or clock. |
| Design | [include/crown/runtime/memory_report.hpp](../../../../../../include/crown/runtime/memory_report.hpp), [src/runtime/memory_report.cpp](../../../../../../src/runtime/memory_report.cpp), [src/runtime/memory_report_detail.hpp](../../../../../../src/runtime/memory_report_detail.hpp), [docs/memory_reports.md](../../../../../memory_reports.md), [docs/code_review.md](../../../../../code_review.md) |

```text
const Usage& usage() const noexcept;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Borrow memory Report processing usage. |
| inputs / outputs | Returns const Usage& from immutable Data. |
| invariants | Scan/sort diagnostic work is independent of runtime execution allowance. |
| ownership | Retain a Report sharing Data while reference is used; getter itself does not retain Data. |
| failure | noexcept for a live readable object; borrowing does not validate lifetime or extend it. |
| cost | O(1) fixed member/view lookup; no allocation or clock. |
| Design | [include/crown/runtime/memory_report.hpp](../../../../../../include/crown/runtime/memory_report.hpp), [src/runtime/memory_report.cpp](../../../../../../src/runtime/memory_report.cpp), [src/runtime/memory_report_detail.hpp](../../../../../../src/runtime/memory_report_detail.hpp), [docs/memory_reports.md](../../../../../memory_reports.md), [docs/code_review.md](../../../../../code_review.md) |

```text
const resource::MemoryAccount& account() const & noexcept;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Borrow memory Report actual retained account. |
| inputs / outputs | Returns const MemoryAccount& from immutable Data. |
| invariants | Explicit account handle copy retains same allowance; no refill. |
| ownership | Retain a Report sharing Data while reference is used; getter itself does not retain Data. |
| failure | noexcept for a live readable object; borrowing does not validate lifetime or extend it. |
| cost | O(1) fixed member/view lookup; no allocation or clock. |
| Design | [include/crown/runtime/memory_report.hpp](../../../../../../include/crown/runtime/memory_report.hpp), [src/runtime/memory_report.cpp](../../../../../../src/runtime/memory_report.cpp), [src/runtime/memory_report_detail.hpp](../../../../../../src/runtime/memory_report_detail.hpp), [docs/memory_reports.md](../../../../../memory_reports.md), [docs/code_review.md](../../../../../code_review.md) |

```text
const resource::MemoryAccount& account() const &&=delete;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Reject account reference from a temporary Report. |
| inputs / outputs | Rvalue account() deleted. |
| invariants | Other lvalue borrows still require caller-retained Data ownership. |
| ownership | No account returned. |
| failure | Compile-time rejection. |
| cost | No runtime cost. |
| Design | [include/crown/runtime/memory_report.hpp](../../../../../../include/crown/runtime/memory_report.hpp), [src/runtime/memory_report.cpp](../../../../../../src/runtime/memory_report.cpp), [src/runtime/memory_report_detail.hpp](../../../../../../src/runtime/memory_report_detail.hpp), [docs/memory_reports.md](../../../../../memory_reports.md), [docs/code_review.md](../../../../../code_review.md) |

```text
static constexpr unsigned format_version=1;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Version native memory report format. |
| inputs / outputs | format_version=1. |
| invariants | Version is representation metadata, not authenticated allocation/proof authority. |
| ownership | Caller owns inline numeric/tag fields; this record retains no backing runtime, rows, strings or allocation grant. |
| failure | The declaration does not validate public fields or translate failure. Actual factories/consumers perform the stated checks. |
| cost | Fixed inline scalar/enum/optional/array storage and bounded copies; no dynamic payload, scan, clock or allocation. |
| Design | [include/crown/runtime/memory_report.hpp](../../../../../../include/crown/runtime/memory_report.hpp), [src/runtime/memory_report.cpp](../../../../../../src/runtime/memory_report.cpp), [src/runtime/memory_report_detail.hpp](../../../../../../src/runtime/memory_report_detail.hpp), [docs/memory_reports.md](../../../../../memory_reports.md), [docs/code_review.md](../../../../../code_review.md) |

```text
explicit Report(std::shared_ptr<const detail::Data> data) noexcept:data_(std::move(data)) {}
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Adopt complete private memory Data. |
| inputs / outputs | Builder moves shared_ptr&lt;const Data&gt; into data_. |
| invariants | Builder reconciled owner/purpose/lifetime partitions and table joins before return. |
| ownership | Report adopts actual immutable account/arrays only. |
| failure | noexcept for a live readable object; borrowing does not validate lifetime or extend it. |
| cost | O(1) pointer move; capture preparation precedes it. |
| Design | [include/crown/runtime/memory_report.hpp](../../../../../../include/crown/runtime/memory_report.hpp), [src/runtime/memory_report.cpp](../../../../../../src/runtime/memory_report.cpp), [src/runtime/memory_report_detail.hpp](../../../../../../src/runtime/memory_report_detail.hpp), [docs/memory_reports.md](../../../../../memory_reports.md), [docs/code_review.md](../../../../../code_review.md) |

## B0017

[Lines 85–85](../../../../../../include/crown/runtime/memory_report.hpp#L85); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct Attempt {Stop stop=Stop::inconsistent;std::optional<Report> report;Usage usage;};
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Return memory capture outcome and spent diagnostic usage. |
| inputs / outputs | Stop default inconsistent, optional shared Report, Usage. |
| invariants | Report exists only on complete; no failed partial arrays escape. |
| ownership | Copy shares actual Data; last release deallocates its numeric arrays/account. |
| failure | No carrier catch; noexcept Access::attempt maps typed failures, account/OOM and unknown exceptions. |
| cost | Fixed/refcount value copy; final release performs actual buffer/control cleanup. |
| Design | [include/crown/runtime/memory_report.hpp](../../../../../../include/crown/runtime/memory_report.hpp), [src/runtime/memory_report.cpp](../../../../../../src/runtime/memory_report.cpp), [src/runtime/memory_report_detail.hpp](../../../../../../src/runtime/memory_report_detail.hpp), [docs/memory_reports.md](../../../../../memory_reports.md), [docs/code_review.md](../../../../../code_review.md) |

## B0018

[Lines 86–90](../../../../../../include/crown/runtime/memory_report.hpp#L86); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
[[nodiscard]] Attempt capture(const SupportRuntime&,Limits={}) noexcept;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Capture actual account memory from SupportRuntime. |
| inputs / outputs | Owner and finite Limits return Attempt. Pending owners produce account-only pending; released QuerySession produces account-only released; invalid native owner stops invalid_handle. |
| invariants | Does not advance/drain execution. Session capture respects creator-thread/reentrancy Guard, with failures translated by noexcept boundary. Public numeric labels do not substitute actual owner Access. |
| ownership | All control/output/scratch arrays charged to actual original account; returned Report independent of runtime. Scratch released before final account snapshot, report own storage remains. |
| failure | noexcept maps work/count/overflow/inconsistency and allocation failures to stops; failed report unwinds, old runtime/reports preserved; no new grant. |
| cost | Explicit table ledger/resident scans and account key sorting/dedup; A allocations,U attributions,T tables,O operators: key O((A+O)log(A+O)), per-owner scans O(UA), table joins O(T log U) plus actual arena/index scans. |
| Design | [include/crown/runtime/memory_report.hpp](../../../../../../include/crown/runtime/memory_report.hpp), [src/runtime/memory_report.cpp](../../../../../../src/runtime/memory_report.cpp), [src/runtime/memory_report_detail.hpp](../../../../../../src/runtime/memory_report_detail.hpp), [docs/memory_reports.md](../../../../../memory_reports.md), [docs/code_review.md](../../../../../code_review.md), [src/runtime/support.cpp](../../../../../../src/runtime/support.cpp), [src/runtime/physical.cpp](../../../../../../src/runtime/physical.cpp), [src/runtime/delta.cpp](../../../../../../src/runtime/delta.cpp), [src/runtime/session.cpp](../../../../../../src/runtime/session.cpp) |

```text
[[nodiscard]] Attempt capture(const PhysicalRuntime&,Limits={}) noexcept;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Capture actual account memory from PhysicalRuntime. |
| inputs / outputs | Owner and finite Limits return Attempt. Pending owners produce account-only pending; released QuerySession produces account-only released; invalid native owner stops invalid_handle. |
| invariants | Does not advance/drain execution. Session capture respects creator-thread/reentrancy Guard, with failures translated by noexcept boundary. Public numeric labels do not substitute actual owner Access. |
| ownership | All control/output/scratch arrays charged to actual original account; returned Report independent of runtime. Scratch released before final account snapshot, report own storage remains. |
| failure | noexcept maps work/count/overflow/inconsistency and allocation failures to stops; failed report unwinds, old runtime/reports preserved; no new grant. |
| cost | Explicit table ledger/resident scans and account key sorting/dedup; A allocations,U attributions,T tables,O operators: key O((A+O)log(A+O)), per-owner scans O(UA), table joins O(T log U) plus actual arena/index scans. |
| Design | [include/crown/runtime/memory_report.hpp](../../../../../../include/crown/runtime/memory_report.hpp), [src/runtime/memory_report.cpp](../../../../../../src/runtime/memory_report.cpp), [src/runtime/memory_report_detail.hpp](../../../../../../src/runtime/memory_report_detail.hpp), [docs/memory_reports.md](../../../../../memory_reports.md), [docs/code_review.md](../../../../../code_review.md), [src/runtime/support.cpp](../../../../../../src/runtime/support.cpp), [src/runtime/physical.cpp](../../../../../../src/runtime/physical.cpp), [src/runtime/delta.cpp](../../../../../../src/runtime/delta.cpp), [src/runtime/session.cpp](../../../../../../src/runtime/session.cpp) |

```text
[[nodiscard]] Attempt capture(const DeltaRuntime&,Limits={}) noexcept;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Capture actual account memory from DeltaRuntime. |
| inputs / outputs | Owner and finite Limits return Attempt. Pending owners produce account-only pending; released QuerySession produces account-only released; invalid native owner stops invalid_handle. |
| invariants | Does not advance/drain execution. Session capture respects creator-thread/reentrancy Guard, with failures translated by noexcept boundary. Public numeric labels do not substitute actual owner Access. |
| ownership | All control/output/scratch arrays charged to actual original account; returned Report independent of runtime. Scratch released before final account snapshot, report own storage remains. |
| failure | noexcept maps work/count/overflow/inconsistency and allocation failures to stops; failed report unwinds, old runtime/reports preserved; no new grant. |
| cost | Explicit table ledger/resident scans and account key sorting/dedup; A allocations,U attributions,T tables,O operators: key O((A+O)log(A+O)), per-owner scans O(UA), table joins O(T log U) plus actual arena/index scans. |
| Design | [include/crown/runtime/memory_report.hpp](../../../../../../include/crown/runtime/memory_report.hpp), [src/runtime/memory_report.cpp](../../../../../../src/runtime/memory_report.cpp), [src/runtime/memory_report_detail.hpp](../../../../../../src/runtime/memory_report_detail.hpp), [docs/memory_reports.md](../../../../../memory_reports.md), [docs/code_review.md](../../../../../code_review.md), [src/runtime/support.cpp](../../../../../../src/runtime/support.cpp), [src/runtime/physical.cpp](../../../../../../src/runtime/physical.cpp), [src/runtime/delta.cpp](../../../../../../src/runtime/delta.cpp), [src/runtime/session.cpp](../../../../../../src/runtime/session.cpp) |

```text
[[nodiscard]] Attempt capture(const QuerySession&,Limits={}) noexcept;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Capture actual account memory from QuerySession. |
| inputs / outputs | Owner and finite Limits return Attempt. Pending owners produce account-only pending; released QuerySession produces account-only released; invalid native owner stops invalid_handle. |
| invariants | Does not advance/drain execution. Session capture respects creator-thread/reentrancy Guard, with failures translated by noexcept boundary. Public numeric labels do not substitute actual owner Access. |
| ownership | All control/output/scratch arrays charged to actual original account; returned Report independent of runtime. Scratch released before final account snapshot, report own storage remains. |
| failure | noexcept maps work/count/overflow/inconsistency and allocation failures to stops; failed report unwinds, old runtime/reports preserved; no new grant. |
| cost | Explicit table ledger/resident scans and account key sorting/dedup; A allocations,U attributions,T tables,O operators: key O((A+O)log(A+O)), per-owner scans O(UA), table joins O(T log U) plus actual arena/index scans. |
| Design | [include/crown/runtime/memory_report.hpp](../../../../../../include/crown/runtime/memory_report.hpp), [src/runtime/memory_report.cpp](../../../../../../src/runtime/memory_report.cpp), [src/runtime/memory_report_detail.hpp](../../../../../../src/runtime/memory_report_detail.hpp), [docs/memory_reports.md](../../../../../memory_reports.md), [docs/code_review.md](../../../../../code_review.md), [src/runtime/support.cpp](../../../../../../src/runtime/support.cpp), [src/runtime/physical.cpp](../../../../../../src/runtime/physical.cpp), [src/runtime/delta.cpp](../../../../../../src/runtime/delta.cpp), [src/runtime/session.cpp](../../../../../../src/runtime/session.cpp) |
