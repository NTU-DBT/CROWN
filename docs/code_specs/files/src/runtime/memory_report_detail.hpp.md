# `src/runtime/memory_report_detail.hpp` — block usage map

[Source](../../../../../src/runtime/memory_report_detail.hpp) · [Source index](../../../README.md) · [Subsystem contracts](../../../subsystem_contracts.md) · [Reviewed primitives](../../../primitives.md)

Capture bounded distributions, workload counters, owner memory and explain observations without mislabeling partial information as exact.

Snapshot SHA-256: `5d140e0fd4e72f625a322575aa2943745a1bf5e52f7fbfb8c5647a1d6f8677b4`. 63 lines partitioned into 11 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [statistics](../../../subsystem_contracts.md#statistics). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/statistics.md](../../../../statistics.md), [docs/observability.md](../../../../observability.md), [docs/memory_reports.md](../../../../memory_reports.md), [docs/ranking_evaluation.md](../../../../ranking_evaluation.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–7](../../../../../src/runtime/memory_report_detail.hpp#L1) | Imports dependencies; guards repeated header inclusion; declares namespace scope; declares values/defaults or compile-time conditions. |  · [reviewed contract](#b0001) |
| [B0002 · 8–10](../../../../../src/runtime/memory_report_detail.hpp#L8) | Callable definition: template&lt;class T&gt; resource::OwnerAllocator&lt;T&gt; allocator(const resource::MemoryAccount& account) | calls ; returns resource::OwnerAllocator&lt;T&gt;(account,resource::MemoryPurpose::capture,report_owner) · [reviewed contract](#b0002) |
| [B0003 · 11–11](../../../../../src/runtime/memory_report_detail.hpp#L11) | Type/record definition: struct Failure |  · [reviewed contract](#b0003) |
| [B0004 · 12–12](../../../../../src/runtime/memory_report_detail.hpp#L12) | Explanatory comments or spacing. | source comment (unverified): // Numeric report arrays retain the original account; no live table/owner pointer escapes. · [reviewed contract](#b0004) |
| [B0005 · 13–26](../../../../../src/runtime/memory_report_detail.hpp#L13) | Type/record definition: struct Data | source comment (unverified): // Numeric report arrays retain the original account; no live table/owner pointer escapes. · [reviewed contract](#b0005) |
| [B0006 · 27–28](../../../../../src/runtime/memory_report_detail.hpp#L27) | Explanatory comments or spacing. | source comment (unverified): // Usage is borrowed from the enclosing Attempt and must outlive this builder. · [reviewed contract](#b0006) |
| [B0007 · 29–42](../../../../../src/runtime/memory_report_detail.hpp#L29) | Type/record definition: class Builder | source comment (unverified): // Usage is borrowed from the enclosing Attempt and must outlive this builder. · [reviewed contract](#b0007) |
| [B0008 · 43–51](../../../../../src/runtime/memory_report_detail.hpp#L43) | Type/record definition: struct Access |  · [reviewed contract](#b0008) |
| [B0009 · 52–52](../../../../../src/runtime/memory_report_detail.hpp#L52) | Explanatory comments or spacing. | source comment (unverified): // One best-effort noexcept boundary: never publish a partial reconciled report. · [reviewed contract](#b0009) |
| [B0010 · 53–62](../../../../../src/runtime/memory_report_detail.hpp#L53) | Callable definition: template&lt;class Function&gt; Attempt attempt(Function function) noexcept | calls function, fault; returns out; source comment (unverified): // One best-effort noexcept boundary: never publish a partial reconciled report. · [reviewed contract](#b0010) |
| [B0011 · 63–63](../../../../../src/runtime/memory_report_detail.hpp#L63) | Closes surrounding scope/type. | source comment (unverified): // namespace crown::runtime::memory::detail · [reviewed contract](#b0011) |

## B0001

[Lines 1–7](../../../../../src/runtime/memory_report_detail.hpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
inline constexpr resource::MemoryAttribution report_owner
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Attribute native memory report controls, arrays and report scratch to capture:14. |
| inputs / outputs | Static attribution is used with the original query account by allocator() and Builder. |
| invariants | An attribution labels actual account requests; it does not create a separate byte grant or exclude report storage from the account instant. |
| ownership | Inline constant has program lifetime and owns no allocation. |
| failure | No runtime failure path. |
| cost | Compile-time fixed tag, no instrumentation or row traversal. |
| Design | [src/runtime/memory_report_detail.hpp](../../../../../src/runtime/memory_report_detail.hpp), [include/crown/runtime/memory_report.hpp](../../../../../include/crown/runtime/memory_report.hpp), [src/runtime/memory_report.cpp](../../../../../src/runtime/memory_report.cpp), [src/runtime/physical.cpp](../../../../../src/runtime/physical.cpp), [src/runtime/support.cpp](../../../../../src/runtime/support.cpp), [src/runtime/delta.cpp](../../../../../src/runtime/delta.cpp), [docs/memory_reports.md](../../../../memory_reports.md), [docs/query_memory.md](../../../../query_memory.md), [tests/unit/report_capture_memory_test.cpp](../../../../../tests/unit/report_capture_memory_test.cpp), [docs/code_review.md](../../../../code_review.md) |

## B0002

[Lines 8–10](../../../../../src/runtime/memory_report_detail.hpp#L8); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
template<class T> resource::OwnerAllocator<T> allocator(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Bind report vector requests to the existing account and capture attribution. |
| inputs / outputs | Returns OwnerAllocator&lt;T&gt;(account,capture,report_owner). |
| invariants | Allocator binding alone does not reserve capacity or admit the report limits. |
| ownership | Returned allocator retains account; actual arrays and allocator framing are charged when allocated. |
| failure | Later allocation/overflow/account failure propagates to attempt() through Builder. |
| cost | Fixed owner-handle setup; actual memory cost follows requested capacity and framing. |
| Design | [src/runtime/memory_report_detail.hpp](../../../../../src/runtime/memory_report_detail.hpp), [include/crown/runtime/memory_report.hpp](../../../../../include/crown/runtime/memory_report.hpp), [src/runtime/memory_report.cpp](../../../../../src/runtime/memory_report.cpp), [src/runtime/physical.cpp](../../../../../src/runtime/physical.cpp), [src/runtime/support.cpp](../../../../../src/runtime/support.cpp), [src/runtime/delta.cpp](../../../../../src/runtime/delta.cpp), [docs/memory_reports.md](../../../../memory_reports.md), [docs/query_memory.md](../../../../query_memory.md), [tests/unit/report_capture_memory_test.cpp](../../../../../tests/unit/report_capture_memory_test.cpp), [docs/code_review.md](../../../../code_review.md) |

## B0003

[Lines 11–11](../../../../../src/runtime/memory_report_detail.hpp#L11); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct Failure {Stop stop;};
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Carry one fixed private best-effort memory-report stop. |
| inputs / outputs | Builder/Access throw a Stop value for work/owner/table/operator/overflow/consistency or handle denial. |
| invariants | The sentinel is report-control flow, not a query mutation rollback or diagnostic string. |
| ownership | Only inline enum payload; no source row or owner pointer is retained. |
| failure | attempt() translates it without broadening another failure category. |
| cost | Fixed payload/exception propagation; unwinding releases funded partial report scratch. |
| Design | [src/runtime/memory_report_detail.hpp](../../../../../src/runtime/memory_report_detail.hpp), [include/crown/runtime/memory_report.hpp](../../../../../include/crown/runtime/memory_report.hpp), [src/runtime/memory_report.cpp](../../../../../src/runtime/memory_report.cpp), [src/runtime/physical.cpp](../../../../../src/runtime/physical.cpp), [src/runtime/support.cpp](../../../../../src/runtime/support.cpp), [src/runtime/delta.cpp](../../../../../src/runtime/delta.cpp), [docs/memory_reports.md](../../../../memory_reports.md), [docs/query_memory.md](../../../../query_memory.md), [tests/unit/report_capture_memory_test.cpp](../../../../../tests/unit/report_capture_memory_test.cpp), [docs/code_review.md](../../../../code_review.md) |

## B0004

[Lines 12–12](../../../../../src/runtime/memory_report_detail.hpp#L12); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L12-L12:sha256:f15cd6d7ef6e5f8892790d7a3bf819f2e46a9a0d19b71fae12b3187f58c346fe
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Usage note immediately before \`struct Data\`: Numeric report arrays retain the original account; no live table/owner pointer escapes. |
| inputs / outputs | This comment introduces no parameter, field or return value. It documents the adjacent construct beginning at src/runtime/memory_report_detail.hpp:L13; use that declaration for the actual input/output shape. |
| invariants | The source note states: Numeric report arrays retain the original account; no live table/owner pointer escapes. It is prose guidance; the adjacent implementation is the place to check enforcement. |
| ownership | The comment itself retains nothing. It documents this neighboring ownership/account boundary: Numeric report arrays retain the original account; no live table/owner pointer escapes. Actual lifetime is determined by the declared members and owners. |
| failure | This comment adds no branch or handler. Any failure behavior remains in the adjacent callable implementation and its callers. |
| cost | The prose adds no executable work. Runtime cost belongs to the adjacent operation; the note does not establish a measured or global complexity bound. |
| Design | [docs/memory_reports.md](../../../../memory_reports.md), [docs/query_memory.md](../../../../query_memory.md), [docs/memory_accounts.md](../../../../memory_accounts.md), [docs/code_specs/subsystem_contracts.md](../../../subsystem_contracts.md) |

## B0005

[Lines 13–26](../../../../../src/runtime/memory_report_detail.hpp#L13); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct Data {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Own the immutable account-wide native memory report after private construction. |
| inputs / outputs | Retains account, fixed Snapshot, funded owners/tables/operators arrays and final Usage; constructor validates/copies the exact 64-byte physical-plan hash. |
| invariants | Snapshot numbers describe one captured instant, including report storage itself; rows/tables/operators describe the committed or explicitly unavailable runtime layer. No live runtime pointers or row leases are retained. |
| ownership | Shared Data/control and nested arrays use original account capture:14. Returned Report handles share this graph and remain readable after runtime close. |
| failure | Wrong hash width throws Failure(inconsistent). Later array/admission failures unwind the private graph and publish no Report. |
| cost | Fixed initial metadata/hash copy and empty allocators; actual capture includes account-ledger scans, capacity/high-water table scans and array allocation. Report copies share, not rescan. |
| Design | [src/runtime/memory_report_detail.hpp](../../../../../src/runtime/memory_report_detail.hpp), [include/crown/runtime/memory_report.hpp](../../../../../include/crown/runtime/memory_report.hpp), [src/runtime/memory_report.cpp](../../../../../src/runtime/memory_report.cpp), [src/runtime/physical.cpp](../../../../../src/runtime/physical.cpp), [src/runtime/support.cpp](../../../../../src/runtime/support.cpp), [src/runtime/delta.cpp](../../../../../src/runtime/delta.cpp), [docs/memory_reports.md](../../../../memory_reports.md), [docs/query_memory.md](../../../../query_memory.md), [tests/unit/report_capture_memory_test.cpp](../../../../../tests/unit/report_capture_memory_test.cpp), [docs/code_review.md](../../../../code_review.md) |

```text
  Data(const resource::MemoryAccount& a,Layer layer,
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Initialize funded empty report arrays and exact plan-bound snapshot metadata. |
| inputs / outputs | Copies account, layer, availability, owner, sequence and exactly snapshot.physical_sha256.size() bytes from hash. |
| invariants | Hash length must be exactly 64; copying bytes does not recompute a physical hash or certify an edited DTO. |
| ownership | Arrays retain their account allocators; input hash is borrowed only during the fixed copy. |
| failure | Invalid hash width raises private Failure(inconsistent); enclosing make_accounted_shared admission can fail before construction. |
| cost | Fixed 64-byte copy plus metadata/empty allocator setup; this constructor performs no table/ledger scan. |
| Design | [src/runtime/memory_report_detail.hpp](../../../../../src/runtime/memory_report_detail.hpp), [include/crown/runtime/memory_report.hpp](../../../../../include/crown/runtime/memory_report.hpp), [src/runtime/memory_report.cpp](../../../../../src/runtime/memory_report.cpp), [src/runtime/physical.cpp](../../../../../src/runtime/physical.cpp), [src/runtime/support.cpp](../../../../../src/runtime/support.cpp), [src/runtime/delta.cpp](../../../../../src/runtime/delta.cpp), [docs/memory_reports.md](../../../../memory_reports.md), [docs/query_memory.md](../../../../query_memory.md), [tests/unit/report_capture_memory_test.cpp](../../../../../tests/unit/report_capture_memory_test.cpp), [docs/code_review.md](../../../../code_review.md) |

## B0006

[Lines 27–28](../../../../../src/runtime/memory_report_detail.hpp#L27); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L27-L28:sha256:6a7cc3091b06aebb5b9914e7af8e79804a7a24f5956815bec9f6ef649af2dc8d
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Usage note immediately before \`class Builder\`: Usage is borrowed from the enclosing Attempt and must outlive this builder. finish reconciles actual account ledgers after releasing diagnostic scratch. |
| inputs / outputs | This comment introduces no parameter, field or return value. It documents the adjacent construct beginning at src/runtime/memory_report_detail.hpp:L29; use that declaration for the actual input/output shape. |
| invariants | The source note states: Usage is borrowed from the enclosing Attempt and must outlive this builder. finish reconciles actual account ledgers after releasing diagnostic scratch. It is prose guidance; the adjacent implementation is the place to check enforcement. |
| ownership | The comment itself retains nothing. It documents this neighboring ownership/account boundary: Usage is borrowed from the enclosing Attempt and must outlive this builder. finish reconciles actual account ledgers after releasing diagnostic scratch. Actual lifetime is determined by the declared members and owners. |
| failure | This comment adds no branch or handler. Any failure behavior remains in the adjacent callable implementation and its callers. |
| cost | The prose adds no executable work. Runtime cost belongs to the adjacent operation; the note does not establish a measured or global complexity bound. |
| Design | [docs/memory_reports.md](../../../../memory_reports.md), [docs/query_memory.md](../../../../query_memory.md), [docs/memory_accounts.md](../../../../memory_accounts.md), [docs/code_specs/subsystem_contracts.md](../../../subsystem_contracts.md) |

## B0007

[Lines 29–42](../../../../../src/runtime/memory_report_detail.hpp#L29); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
class Builder {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Privately assemble a bounded native account report before publication. |
| inputs / outputs | Constructor retains funded Data, limits and borrowed Usage sink. work/operation/table/records collect facts; finish inventories actual account attributions, reconciles all totals and returns Report. |
| invariants | Callers hold exclusive synchronous runtime access. Limits admit diagnostic scans, not a hard total-CPU model. Only complete, reconciled Report escapes; private partial usage can survive failure in Attempt. |
| ownership | data_ owns report/control/arrays, limits_ is inline, usage_ borrows the caller Attempt and must outlive Builder. Table inputs are not retained as mutable pointers. |
| failure | Failure and MemoryFailure/bad_alloc leave no published partial report; attempt() performs the one best-effort translation. Source runtime remains read-only. |
| cost | Table work includes conservative 3*account allocations+arena slots precharge and actual ledger/high-water/index scans. finish sorts/dedups attribution keys and scans the allocation ledger once per owner, plus reconciliation/joins; report and scratch allocations are real. |
| Design | [src/runtime/memory_report_detail.hpp](../../../../../src/runtime/memory_report_detail.hpp), [include/crown/runtime/memory_report.hpp](../../../../../include/crown/runtime/memory_report.hpp), [src/runtime/memory_report.cpp](../../../../../src/runtime/memory_report.cpp), [src/runtime/physical.cpp](../../../../../src/runtime/physical.cpp), [src/runtime/support.cpp](../../../../../src/runtime/support.cpp), [src/runtime/delta.cpp](../../../../../src/runtime/delta.cpp), [docs/memory_reports.md](../../../../memory_reports.md), [docs/query_memory.md](../../../../query_memory.md), [tests/unit/report_capture_memory_test.cpp](../../../../../tests/unit/report_capture_memory_test.cpp), [docs/code_review.md](../../../../code_review.md) |

```text
  explicit Builder(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Start private account-report construction after its initial work admission. |
| inputs / outputs | Uses original account and metadata; stores a reference to Attempt.usage and funds shared Data/control. |
| invariants | Usage sink must outlive this builder; no report is published by construction. |
| ownership | Owns Data; borrows Usage and temporary hash bytes only. |
| failure | work denial or allocation/hash validation failure propagates to attempt(). |
| cost | One work debit and actual shared control/Data allocation; no table scan. |
| Design | [src/runtime/memory_report_detail.hpp](../../../../../src/runtime/memory_report_detail.hpp), [include/crown/runtime/memory_report.hpp](../../../../../include/crown/runtime/memory_report.hpp), [src/runtime/memory_report.cpp](../../../../../src/runtime/memory_report.cpp), [src/runtime/physical.cpp](../../../../../src/runtime/physical.cpp), [src/runtime/support.cpp](../../../../../src/runtime/support.cpp), [src/runtime/delta.cpp](../../../../../src/runtime/delta.cpp), [docs/memory_reports.md](../../../../memory_reports.md), [docs/query_memory.md](../../../../query_memory.md), [tests/unit/report_capture_memory_test.cpp](../../../../../tests/unit/report_capture_memory_test.cpp), [docs/code_review.md](../../../../code_review.md) |

```text
  void work(std::uint64_t=1);
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Admit finite report diagnostic work without unsigned subtraction wrap. |
| inputs / outputs | Checks used&lt;=limit and amount&lt;=limit-used then increments Usage.work. |
| invariants | Spent usage is never restored by a failed later scan; this is separate from storage operation work. |
| ownership | Mutates borrowed Attempt usage only. |
| failure | Throws Failure(work_limit) on denial. |
| cost | Fixed checked arithmetic; caller supplies conservative scan/sort units. |
| Design | [src/runtime/memory_report_detail.hpp](../../../../../src/runtime/memory_report_detail.hpp), [include/crown/runtime/memory_report.hpp](../../../../../include/crown/runtime/memory_report.hpp), [src/runtime/memory_report.cpp](../../../../../src/runtime/memory_report.cpp), [src/runtime/physical.cpp](../../../../../src/runtime/physical.cpp), [src/runtime/support.cpp](../../../../../src/runtime/support.cpp), [src/runtime/delta.cpp](../../../../../src/runtime/delta.cpp), [docs/memory_reports.md](../../../../memory_reports.md), [docs/query_memory.md](../../../../query_memory.md), [tests/unit/report_capture_memory_test.cpp](../../../../../tests/unit/report_capture_memory_test.cpp), [docs/code_review.md](../../../../code_review.md) |

```text
  void table(TableScope,
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Capture one current table/arena memory fact and check its ownership totals. |
| inputs / outputs | Checks table cap, precharges 3*current account allocations+arena slots, obtains memory_statistics and validates live/arena/table-owned totals before appending. |
| invariants | Source table must remain stable; table/arena record counts and actual owned requested-byte totals must agree. |
| ownership | Retains copied numeric variants in a funded report array, no live table pointer. |
| failure | Cap/work/arithmetic/inconsistency/funding failures propagate without a partial report. |
| cost | Actual ledger/index/high-water slot scans plus vector growth; logical live row count alone does not bound this cost. |
| Design | [src/runtime/memory_report_detail.hpp](../../../../../src/runtime/memory_report_detail.hpp), [include/crown/runtime/memory_report.hpp](../../../../../include/crown/runtime/memory_report.hpp), [src/runtime/memory_report.cpp](../../../../../src/runtime/memory_report.cpp), [src/runtime/physical.cpp](../../../../../src/runtime/physical.cpp), [src/runtime/support.cpp](../../../../../src/runtime/support.cpp), [src/runtime/delta.cpp](../../../../../src/runtime/delta.cpp), [docs/memory_reports.md](../../../../memory_reports.md), [docs/query_memory.md](../../../../query_memory.md), [tests/unit/report_capture_memory_test.cpp](../../../../../tests/unit/report_capture_memory_test.cpp), [docs/code_review.md](../../../../code_review.md) |

```text
  void operation(Operator);
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Append one numeric operator attribution/count fact within the report cap. |
| inputs / outputs | Debits one work unit, checks operator count, moves the variant into funded array and updates Usage.operators. |
| invariants | Operator facts do not own query tuples or independently prove reconciled account totals. |
| ownership | Report owns copied/moved numeric variant; input argument is by value. |
| failure | Work/operator cap and allocation failures propagate privately. |
| cost | One fixed variant move and possible funded vector capacity growth. |
| Design | [src/runtime/memory_report_detail.hpp](../../../../../src/runtime/memory_report_detail.hpp), [include/crown/runtime/memory_report.hpp](../../../../../include/crown/runtime/memory_report.hpp), [src/runtime/memory_report.cpp](../../../../../src/runtime/memory_report.cpp), [src/runtime/physical.cpp](../../../../../src/runtime/physical.cpp), [src/runtime/support.cpp](../../../../../src/runtime/support.cpp), [src/runtime/delta.cpp](../../../../../src/runtime/delta.cpp), [docs/memory_reports.md](../../../../memory_reports.md), [docs/query_memory.md](../../../../query_memory.md), [tests/unit/report_capture_memory_test.cpp](../../../../../tests/unit/report_capture_memory_test.cpp), [docs/code_review.md](../../../../code_review.md) |

```text
  std::uint64_t records(TableScope,RelationId);
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Join a previously recorded table scope/relation to its live-record count. |
| inputs / outputs | Linearly scans existing table facts, debiting one work per visited item, returns first matching count. |
| invariants | Caller must have appended that exact table before querying; no maintained lookup index exists. |
| ownership | Borrows private recorded facts; result is inline. |
| failure | Missing match throws Failure(inconsistent); limit exhaustion throws Failure(work_limit). |
| cost | O(recorded tables) actual comparisons, no successful allocation. |
| Design | [src/runtime/memory_report_detail.hpp](../../../../../src/runtime/memory_report_detail.hpp), [include/crown/runtime/memory_report.hpp](../../../../../include/crown/runtime/memory_report.hpp), [src/runtime/memory_report.cpp](../../../../../src/runtime/memory_report.cpp), [src/runtime/physical.cpp](../../../../../src/runtime/physical.cpp), [src/runtime/support.cpp](../../../../../src/runtime/support.cpp), [src/runtime/delta.cpp](../../../../../src/runtime/delta.cpp), [docs/memory_reports.md](../../../../memory_reports.md), [docs/query_memory.md](../../../../query_memory.md), [tests/unit/report_capture_memory_test.cpp](../../../../../tests/unit/report_capture_memory_test.cpp), [docs/code_review.md](../../../../code_review.md) |

```text
  static std::uint64_t add(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Checked-add report payload/work/count quantities. |
| inputs / outputs | Returns a+b only when b&lt;=UINT64_MAX-a. |
| invariants | Never wraps or saturates an exact report total. |
| ownership | Inline values only. |
| failure | Overflow throws Failure(overflow). |
| cost | Fixed arithmetic; this helper does not meter itself. |
| Design | [src/runtime/memory_report_detail.hpp](../../../../../src/runtime/memory_report_detail.hpp), [include/crown/runtime/memory_report.hpp](../../../../../include/crown/runtime/memory_report.hpp), [src/runtime/memory_report.cpp](../../../../../src/runtime/memory_report.cpp), [src/runtime/physical.cpp](../../../../../src/runtime/physical.cpp), [src/runtime/support.cpp](../../../../../src/runtime/support.cpp), [src/runtime/delta.cpp](../../../../../src/runtime/delta.cpp), [docs/memory_reports.md](../../../../memory_reports.md), [docs/query_memory.md](../../../../query_memory.md), [tests/unit/report_capture_memory_test.cpp](../../../../../tests/unit/report_capture_memory_test.cpp), [docs/code_review.md](../../../../code_review.md) |

```text
  Report finish();
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Publish only an account-wide fully reconciled memory report. |
| inputs / outputs | Builds/sorts/deduplicates actual allocation and operator attributions, funds owners array, releases scratch, samples account, gathers each owner totals, verifies purpose/lifetime/arena/table joins and returns Report. |
| invariants | Scratch is gone before sampling; report storage is included. Account-wide owners can include retained older reports/generations, beyond current runtime facts. |
| ownership | Result shares funded Data; no source runtime pointers/row pins survive. |
| failure | Any limit/overflow/inconsistency/allocation error returns no Report through attempt(). |
| cost | Sorting attribution keys, owner_count*allocation_count ledger scans, table joins and funded arrays; no timing or O(live rows)-only claim. |
| Design | [src/runtime/memory_report_detail.hpp](../../../../../src/runtime/memory_report_detail.hpp), [include/crown/runtime/memory_report.hpp](../../../../../include/crown/runtime/memory_report.hpp), [src/runtime/memory_report.cpp](../../../../../src/runtime/memory_report.cpp), [src/runtime/physical.cpp](../../../../../src/runtime/physical.cpp), [src/runtime/support.cpp](../../../../../src/runtime/support.cpp), [src/runtime/delta.cpp](../../../../../src/runtime/delta.cpp), [docs/memory_reports.md](../../../../memory_reports.md), [docs/query_memory.md](../../../../query_memory.md), [tests/unit/report_capture_memory_test.cpp](../../../../../tests/unit/report_capture_memory_test.cpp), [docs/code_review.md](../../../../code_review.md) |

## B0008

[Lines 43–51](../../../../../src/runtime/memory_report_detail.hpp#L43); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct Access {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Expose private friend capture seams for actual runtime and session owners. |
| inputs / outputs | append overloads read Support/Physical/Delta internals into Builder; capture overloads create one Attempt and select committed/pending/released metadata under actual owner/session guards. |
| invariants | Public numeric DTOs cannot manufacture these private owner reads. A stable exclusive synchronous owner is required; QuerySession supplies its own guarded composition. |
| ownership | Only borrowed actual owner references during capture; resulting Report owns copied numeric facts/account graph. |
| failure | Noexcept capture overloads use attempt(); append failures preserve precise limit/consistency categories and source remains unchanged. |
| cost | Walks actual operator/table structures and account ledgers; pending/released captures omit unavailable committed facts rather than scanning tentative rows. |
| Design | [src/runtime/memory_report_detail.hpp](../../../../../src/runtime/memory_report_detail.hpp), [include/crown/runtime/memory_report.hpp](../../../../../include/crown/runtime/memory_report.hpp), [src/runtime/memory_report.cpp](../../../../../src/runtime/memory_report.cpp), [src/runtime/physical.cpp](../../../../../src/runtime/physical.cpp), [src/runtime/support.cpp](../../../../../src/runtime/support.cpp), [src/runtime/delta.cpp](../../../../../src/runtime/delta.cpp), [docs/memory_reports.md](../../../../memory_reports.md), [docs/query_memory.md](../../../../query_memory.md), [tests/unit/report_capture_memory_test.cpp](../../../../../tests/unit/report_capture_memory_test.cpp), [docs/code_review.md](../../../../code_review.md) |

## B0009

[Lines 52–52](../../../../../src/runtime/memory_report_detail.hpp#L52); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L52-L52:sha256:2eaa77305ad68258cfd7df5e70e6c7a4c9e032538d2b88adf3935bf8b1b197e4
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Usage note immediately before \`template&lt;class Function&gt; Attempt attempt(Function function) noexcept\`: One best-effort noexcept boundary: never publish a partial reconciled report. |
| inputs / outputs | This comment introduces no parameter, field or return value. It documents the adjacent construct beginning at src/runtime/memory_report_detail.hpp:L53; use that declaration for the actual input/output shape. |
| invariants | The source note states: One best-effort noexcept boundary: never publish a partial reconciled report. It is prose guidance; the adjacent implementation is the place to check enforcement. |
| ownership | The note states no ownership relation and retains no value. The adjacent declaration or function controls the actual owner and borrowed-view lifetime. |
| failure | This comment adds no branch or handler. Any failure behavior remains in the adjacent callable implementation and its callers. |
| cost | The prose adds no executable work. Runtime cost belongs to the adjacent operation; the note does not establish a measured or global complexity bound. |
| Design | [docs/memory_reports.md](../../../../memory_reports.md), [docs/query_memory.md](../../../../query_memory.md), [docs/memory_accounts.md](../../../../memory_accounts.md), [docs/code_specs/subsystem_contracts.md](../../../subsystem_contracts.md) |

## B0010

[Lines 53–62](../../../../../src/runtime/memory_report_detail.hpp#L53); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
template<class Function> Attempt attempt(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Translate best-effort memory-report construction failures once at the noexcept result boundary. |
| inputs / outputs | Calls function(out.usage), installs report and complete only on success; catches private Failure, MemoryFailure, bad_alloc and unexpected exceptions into fixed Stops. |
| invariants | MemoryFault overflow maps overflow, contract maps inconsistent, other memory faults map allocation_failure. Unexpected exceptions map inconsistent. Failure never publishes a partial Report or fabricates zero facts. |
| ownership | Attempt owns optional report and inline Usage; private Builder temporaries unwind, while already-spent diagnostic usage remains visible. |
| failure | All catches are necessary to the public noexcept best-effort contract; no retry, swallowed query mutation or account refill is introduced. |
| cost | One boundary dispatch plus actual delegated capture/unwinding. Successful execution does not build exception messages; allocation and scan costs reside in Builder. |
| Design | [src/runtime/memory_report_detail.hpp](../../../../../src/runtime/memory_report_detail.hpp), [include/crown/runtime/memory_report.hpp](../../../../../include/crown/runtime/memory_report.hpp), [src/runtime/memory_report.cpp](../../../../../src/runtime/memory_report.cpp), [src/runtime/physical.cpp](../../../../../src/runtime/physical.cpp), [src/runtime/support.cpp](../../../../../src/runtime/support.cpp), [src/runtime/delta.cpp](../../../../../src/runtime/delta.cpp), [docs/memory_reports.md](../../../../memory_reports.md), [docs/query_memory.md](../../../../query_memory.md), [tests/unit/report_capture_memory_test.cpp](../../../../../tests/unit/report_capture_memory_test.cpp), [docs/code_review.md](../../../../code_review.md) |

## B0011

[Lines 63–63](../../../../../src/runtime/memory_report_detail.hpp#L63); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L63-L63:sha256:400eae0d288b1fcf183df92a2012eed25c70478e8d985cbe7d2da6a0e1cf7bd2
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Close the \`namespace crown::runtime::memory::detail\` scope at this exact source boundary. |
| inputs / outputs | This token introduces no callable inputs or outputs. Declarations inside \`namespace crown::runtime::memory::detail\` define the available names, members and operations. |
| invariants | The closing brace matches the opening \`namespace crown::runtime::memory::detail\` at its lexical source position in src/runtime/memory_report_detail.hpp; it preserves C++ namespace/type nesting. |
| ownership | The closing delimiter creates no owner. Types closed by \`namespace crown::runtime::memory::detail\` retain the lifetimes and allocator rules of their own fields and operations. |
| failure | No failure path executes at this closing delimiter. Failure and cleanup behavior belong to enclosed functions and owning types. |
| cost | The delimiter itself performs no runtime work; the enclosed initializers, methods and destructors carry their own costs. |
| Design | [docs/memory_reports.md](../../../../memory_reports.md), [docs/query_memory.md](../../../../query_memory.md), [docs/memory_accounts.md](../../../../memory_accounts.md), [docs/code_specs/subsystem_contracts.md](../../../subsystem_contracts.md) |
