# `src/runtime/memory_report.cpp` — block usage map

[Source](../../../../../src/runtime/memory_report.cpp) · [Source index](../../../README.md) · [Subsystem contracts](../../../subsystem_contracts.md) · [Reviewed primitives](../../../primitives.md)

Capture/reconcile account allocation partitions with logical runtime ownership.

Snapshot SHA-256: `f030124c7d47909bcc405a1a0220122d01c7574a91d386a43443e7d807ba00ec`. 118 lines partitioned into 26 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [statistics](../../../subsystem_contracts.md#statistics). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/statistics.md](../../../../statistics.md), [docs/observability.md](../../../../observability.md), [docs/memory_reports.md](../../../../memory_reports.md), [docs/ranking_evaluation.md](../../../../ranking_evaluation.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–4](../../../../../src/runtime/memory_report.cpp#L1) | Imports dependencies; declares namespace scope. |  · [reviewed contract](#b0001) |
| [B0002 · 5–5](../../../../../src/runtime/memory_report.cpp#L5) | Callable definition: const Snapshot& Report::snapshot() const noexcept | calls ; returns data_-&gt;snapshot · [reviewed contract](#b0002) |
| [B0003 · 6–6](../../../../../src/runtime/memory_report.cpp#L6) | Callable definition: const Vector&lt;resource::AttributedMemoryStatistics&gt;& Report::owners() const noexcept | calls ; returns data_-&gt;owners · [reviewed contract](#b0003) |
| [B0004 · 7–7](../../../../../src/runtime/memory_report.cpp#L7) | Callable definition: const Vector&lt;Table&gt;& Report::tables() const noexcept | calls ; returns data_-&gt;tables · [reviewed contract](#b0004) |
| [B0005 · 8–8](../../../../../src/runtime/memory_report.cpp#L8) | Callable definition: const Vector&lt;Operator&gt;& Report::operators() const noexcept | calls ; returns data_-&gt;operators · [reviewed contract](#b0005) |
| [B0006 · 9–9](../../../../../src/runtime/memory_report.cpp#L9) | Callable definition: const Usage& Report::usage() const noexcept | calls ; returns data_-&gt;usage · [reviewed contract](#b0006) |
| [B0007 · 10–10](../../../../../src/runtime/memory_report.cpp#L10) | Callable definition: const resource::MemoryAccount& Report::account() const & noexcept | calls ; returns data_-&gt;account · [reviewed contract](#b0007) |
| [B0008 · 11–12](../../../../../src/runtime/memory_report.cpp#L11) | declares namespace scope. |  · [reviewed contract](#b0008) |
| [B0009 · 13–13](../../../../../src/runtime/memory_report.cpp#L13) | Callable definition: void require(bool value) | calls ; guard void require(bool value){if(!value)throw Failure{Stop::inconsistent};} · [reviewed contract](#b0009) |
| [B0010 · 14–18](../../../../../src/runtime/memory_report.cpp#L14) | Callable definition: void sum(resource::MemoryUsage& to,const resource::MemoryUsage& value) | calls Builder::add · [reviewed contract](#b0010) |
| [B0011 · 19–21](../../../../../src/runtime/memory_report.cpp#L19) | Callable definition: resource::MemoryAttribution attribution(const Operator& value) | calls std::visit; returns std::visit(\[\](const auto& v){return v.attribution · [reviewed contract](#b0011) |
| [B0012 · 22–30](../../../../../src/runtime/memory_report.cpp#L22) | Callable definition: void arena(const storage::ArenaMemoryStatistics& value) | calls sum, require; guard require(total==value.owner.current && value.live_slots.allocations==value.records.live_records &&; 1 loop sites · [reviewed contract](#b0012) |
| [B0013 · 31–31](../../../../../src/runtime/memory_report.cpp#L31) | Closes surrounding scope/type. |  · [reviewed contract](#b0013) |
| [B0014 · 32–35](../../../../../src/runtime/memory_report.cpp#L32) | Callable definition: std::uint64_t Builder::add(std::uint64_t a,std::uint64_t b) | calls ; returns a+b · [reviewed contract](#b0014) |
| [B0015 · 36–40](../../../../../src/runtime/memory_report.cpp#L36) | Callable definition: Builder::Builder(const resource::MemoryAccount& account,Layer layer,Availability availability,std::uint64_t owner, std::uint64_t … | calls limits_, usage_, work; growth make_accounted_shared · [reviewed contract](#b0015) |
| [B0016 · 41–44](../../../../../src/runtime/memory_report.cpp#L41) | Callable definition: void Builder::work(std::uint64_t amount) | calls  · [reviewed contract](#b0016) |
| [B0017 · 45–48](../../../../../src/runtime/memory_report.cpp#L45) | Callable definition: void Builder::operation(Operator value) | calls work, size, push_back, std::move; growth push_back · [reviewed contract](#b0017) |
| [B0018 · 49–53](../../../../../src/runtime/memory_report.cpp#L49) | Callable definition: std::uint64_t Builder::records(TableScope scope,RelationId relation) | calls work; returns row.live_records; 1 loop sites; source comment (unverified): // A recorded-table join is a metered linear scan, not a maintained index. · [reviewed contract](#b0018) |
| [B0019 · 54–74](../../../../../src/runtime/memory_report.cpp#L54) | Callable definition: void Builder::table(TableScope scope,const storage::AccountedStorageTable& table,RelationRole role, std::optional&lt;NodeId&gt; node,st… | calls size, statistics, arena_statistics, work; guard require(live==table.size() && memory.arena.records==records && records.live_records==live);; returns memory.live_records; memory.records.rows; growth push_back; source comment (unverified): // Explicit diagnostics scan owner ledgers and resident arena/index storage. · [reviewed contract](#b0019) |
| [B0020 · 75–112](../../../../../src/runtime/memory_report.cpp#L75) | Callable definition: Report Builder::finish() | calls keys, statistics, add, size; guard require(total==data_-&gt;snapshot.account.current && purposes==data_-&gt;snapshot.account.by_purpose &&; returns a&lt;b; row.attribution&lt;key; growth push_back, reserve, resize; 6 loop sites; source comment (unverified): // Build the account-wide owner inventory privately, then release scratch · [reviewed contract](#b0020) |
| [B0021 · 113–113](../../../../../src/runtime/memory_report.cpp#L113) | Closes surrounding scope/type. | source comment (unverified): // namespace detail · [reviewed contract](#b0021) |
| [B0022 · 114–114](../../../../../src/runtime/memory_report.cpp#L114) | Callable definition: Attempt capture(const SupportRuntime& owner,Limits limits) noexcept | calls detail::Access::capture; returns detail::Access::capture(owner,limits) · [reviewed contract](#b0022) |
| [B0023 · 115–115](../../../../../src/runtime/memory_report.cpp#L115) | Callable definition: Attempt capture(const PhysicalRuntime& owner,Limits limits) noexcept | calls detail::Access::capture; returns detail::Access::capture(owner,limits) · [reviewed contract](#b0023) |
| [B0024 · 116–116](../../../../../src/runtime/memory_report.cpp#L116) | Callable definition: Attempt capture(const DeltaRuntime& owner,Limits limits) noexcept | calls detail::Access::capture; returns detail::Access::capture(owner,limits) · [reviewed contract](#b0024) |
| [B0025 · 117–117](../../../../../src/runtime/memory_report.cpp#L117) | Callable definition: Attempt capture(const QuerySession& owner,Limits limits) noexcept | calls detail::Access::capture; returns detail::Access::capture(owner,limits) · [reviewed contract](#b0025) |
| [B0026 · 118–118](../../../../../src/runtime/memory_report.cpp#L118) | Closes surrounding scope/type. | source comment (unverified): // namespace crown::runtime::memory · [reviewed contract](#b0026) |

## B0001

[Lines 1–4](../../../../../src/runtime/memory_report.cpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
#include "memory_report_detail.hpp"
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Assemble actual-account operator/table memory capture builder. |
| inputs / outputs | Private memory report types/ownership/sorting helpers and limits. |
| invariants | Account-wide ownership partition includes held generations/reports/cursors/output; table/operator joins describe recorded runtime only. No query-proof or process RSS authority. |
| ownership | Declarations own no runtime/account. |
| failure | No admission/handler in includes. |
| cost | Compile-time setup only. |
| Design | [docs/memory_reports.md](../../../../memory_reports.md), [include/crown/runtime/memory_report.hpp](../../../../../include/crown/runtime/memory_report.hpp), [src/runtime/memory_report_detail.hpp](../../../../../src/runtime/memory_report_detail.hpp), [docs/code_review.md](../../../../code_review.md) |

## B0002

[Lines 5–5](../../../../../src/runtime/memory_report.cpp#L5); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
const Snapshot& Report::snapshot() const noexcept{return data_->snapshot;}
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Borrow immutable Report snapshot instant. |
| inputs / outputs | Readable factory-produced Report returns const reference to snapshot instant; account() is lvalue-only and rvalue overload deleted. |
| invariants | Snapshot numbers are as-of capture,not automatically refreshed. Table/operator owner references can repeat; sum owners once. |
| ownership | Reference requires any sharing Report handle. Copy-like moves leave both handles readable; retained Report keeps its original account/data alive. |
| failure | noexcept,no allocation/live owner access. |
| cost | Constant handle/member lookup,no ledger scan on accessor. |
| Design | [docs/memory_reports.md](../../../../memory_reports.md), [include/crown/runtime/memory_report.hpp](../../../../../include/crown/runtime/memory_report.hpp), [src/runtime/memory_report_detail.hpp](../../../../../src/runtime/memory_report_detail.hpp) |

## B0003

[Lines 6–6](../../../../../src/runtime/memory_report.cpp#L6); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
const Vector<resource::AttributedMemoryStatistics>& Report::owners() const noexcept{return data_->owners;}
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Borrow immutable Report attributed owner partition. |
| inputs / outputs | Readable factory-produced Report returns const reference to attributed owner partition; account() is lvalue-only and rvalue overload deleted. |
| invariants | Snapshot numbers are as-of capture,not automatically refreshed. Table/operator owner references can repeat; sum owners once. |
| ownership | Reference requires any sharing Report handle. Copy-like moves leave both handles readable; retained Report keeps its original account/data alive. |
| failure | noexcept,no allocation/live owner access. |
| cost | Constant handle/member lookup,no ledger scan on accessor. |
| Design | [docs/memory_reports.md](../../../../memory_reports.md), [include/crown/runtime/memory_report.hpp](../../../../../include/crown/runtime/memory_report.hpp), [src/runtime/memory_report_detail.hpp](../../../../../src/runtime/memory_report_detail.hpp) |

## B0004

[Lines 7–7](../../../../../src/runtime/memory_report.cpp#L7); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
const Vector<Table>& Report::tables() const noexcept{return data_->tables;}
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Borrow immutable Report table diagnostics. |
| inputs / outputs | Readable factory-produced Report returns const reference to table diagnostics; account() is lvalue-only and rvalue overload deleted. |
| invariants | Snapshot numbers are as-of capture,not automatically refreshed. Table/operator owner references can repeat; sum owners once. |
| ownership | Reference requires any sharing Report handle. Copy-like moves leave both handles readable; retained Report keeps its original account/data alive. |
| failure | noexcept,no allocation/live owner access. |
| cost | Constant handle/member lookup,no ledger scan on accessor. |
| Design | [docs/memory_reports.md](../../../../memory_reports.md), [include/crown/runtime/memory_report.hpp](../../../../../include/crown/runtime/memory_report.hpp), [src/runtime/memory_report_detail.hpp](../../../../../src/runtime/memory_report_detail.hpp) |

## B0005

[Lines 8–8](../../../../../src/runtime/memory_report.cpp#L8); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
const Vector<Operator>& Report::operators() const noexcept{return data_->operators;}
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Borrow immutable Report operator counts. |
| inputs / outputs | Readable factory-produced Report returns const reference to operator counts; account() is lvalue-only and rvalue overload deleted. |
| invariants | Snapshot numbers are as-of capture,not automatically refreshed. Table/operator owner references can repeat; sum owners once. |
| ownership | Reference requires any sharing Report handle. Copy-like moves leave both handles readable; retained Report keeps its original account/data alive. |
| failure | noexcept,no allocation/live owner access. |
| cost | Constant handle/member lookup,no ledger scan on accessor. |
| Design | [docs/memory_reports.md](../../../../memory_reports.md), [include/crown/runtime/memory_report.hpp](../../../../../include/crown/runtime/memory_report.hpp), [src/runtime/memory_report_detail.hpp](../../../../../src/runtime/memory_report_detail.hpp) |

## B0006

[Lines 9–9](../../../../../src/runtime/memory_report.cpp#L9); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
const Usage& Report::usage() const noexcept{return data_->usage;}
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Borrow immutable Report capture usage. |
| inputs / outputs | Readable factory-produced Report returns const reference to capture usage; account() is lvalue-only and rvalue overload deleted. |
| invariants | Snapshot numbers are as-of capture,not automatically refreshed. Table/operator owner references can repeat; sum owners once. |
| ownership | Reference requires any sharing Report handle. Copy-like moves leave both handles readable; retained Report keeps its original account/data alive. |
| failure | noexcept,no allocation/live owner access. |
| cost | Constant handle/member lookup,no ledger scan on accessor. |
| Design | [docs/memory_reports.md](../../../../memory_reports.md), [include/crown/runtime/memory_report.hpp](../../../../../include/crown/runtime/memory_report.hpp), [src/runtime/memory_report_detail.hpp](../../../../../src/runtime/memory_report_detail.hpp) |

## B0007

[Lines 10–10](../../../../../src/runtime/memory_report.cpp#L10); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
const resource::MemoryAccount& Report::account() const & noexcept{return data_->account;}
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Borrow immutable Report original MemoryAccount. |
| inputs / outputs | Readable factory-produced Report returns const reference to original MemoryAccount; account() is lvalue-only and rvalue overload deleted. |
| invariants | Snapshot numbers are as-of capture,not automatically refreshed. Table/operator owner references can repeat; sum owners once. |
| ownership | Reference requires any sharing Report handle. Copy-like moves leave both handles readable; retained Report keeps its original account/data alive. |
| failure | noexcept,no allocation/live owner access. |
| cost | Constant handle/member lookup,no ledger scan on accessor. |
| Design | [docs/memory_reports.md](../../../../memory_reports.md), [include/crown/runtime/memory_report.hpp](../../../../../include/crown/runtime/memory_report.hpp), [src/runtime/memory_report_detail.hpp](../../../../../src/runtime/memory_report_detail.hpp) |

## B0008

[Lines 11–12](../../../../../src/runtime/memory_report.cpp#L11); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L11-L12:sha256:15942a1ef98533a5f8c95849cbc0497e0f8e16726f6d0ccecc350e4a6e610c01
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Source usage for this declaration span in src/runtime/memory_report.cpp: opens namespace \`detail\`; opens anonymous namespace with translation-unit-local linkage. |
| inputs / outputs | Compile inputs are the listed headers and namespace/type names. This span adds no result value unless a helper/type definition listed above is instantiated or called. |
| invariants | The exact import, alias, namespace and member declarations determine the local compile/link surface; stronger behavior belongs to their constructors and operations. |
| ownership | Imports, namespace aliases, forward declarations and compile guards create no object owner. Runtime ownership starts with declared object instances and their allocator/member types. |
| failure | No explicit throw/catch appears in this exact span. Includes, constructors, inline members, static initialization and callees can still fail; follow their enclosing API contracts. |
| cost | This span changes compile/link structure and type layout. Runtime initialization, allocation, exceptions and operation work follow the declared owner/callable code; no absence is inferred from declaration syntax. |
| Design | [docs/memory_reports.md](../../../../memory_reports.md), [docs/query_memory.md](../../../../query_memory.md), [docs/memory_accounts.md](../../../../memory_accounts.md), [docs/code_specs/subsystem_contracts.md](../../../subsystem_contracts.md) |

## B0009

[Lines 13–13](../../../../../src/runtime/memory_report.cpp#L13); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void require(bool value){if(!value)throw Failure{Stop::inconsistent};}
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Reject inconsistent memory partitions through fixed private stop. |
| inputs / outputs | False Boolean throws Failure{Stop::inconsistent}; true returns. |
| invariants | Caller publication boundary maps failure to Attempt; no query rollback or diagnostic string allocation here. |
| ownership | Enum-only exception,private report owns intermediate storage. |
| failure | Fixed Failure propagates; not swallowed into a partial report. |
| cost | One success branch. |
| Design | [docs/memory_reports.md](../../../../memory_reports.md), [include/crown/runtime/memory_report.hpp](../../../../../include/crown/runtime/memory_report.hpp), [src/runtime/memory_report_detail.hpp](../../../../../src/runtime/memory_report_detail.hpp) |

## B0010

[Lines 14–18](../../../../../src/runtime/memory_report.cpp#L14); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void sum(resource::MemoryUsage& to,const resource::MemoryUsage& value) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Add allocation/request/payload counters with exact overflow checks. |
| inputs / outputs | MemoryUsage value contributes all3fields to target through Builder::add. |
| invariants | No saturation/rounding; sums must reconcile exact resident partitions. |
| ownership | Copies inline counters only. |
| failure | Overflow can leave local accumulator partially changed; private builder aborts whole report,so no inverse needed. |
| cost | Three checked additions. |
| Design | [docs/memory_reports.md](../../../../memory_reports.md), [include/crown/runtime/memory_report.hpp](../../../../../include/crown/runtime/memory_report.hpp), [src/runtime/memory_report_detail.hpp](../../../../../src/runtime/memory_report_detail.hpp) |

## B0011

[Lines 19–21](../../../../../src/runtime/memory_report.cpp#L19); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
resource::MemoryAttribution attribution(const Operator& value) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Extract the memory attribution key from any operator carrier. |
| inputs / outputs | Operator variant visitor returns its attribution. |
| invariants | Logical operators may share a key or have zero resident allocation; keys must still appear in partition. |
| ownership | Inline enum/id copy,borrows variant only during call. |
| failure | Valid variant only; no allocation. |
| cost | Constant bounded variant dispatch. |
| Design | [docs/memory_reports.md](../../../../memory_reports.md), [include/crown/runtime/memory_report.hpp](../../../../../include/crown/runtime/memory_report.hpp), [src/runtime/memory_report_detail.hpp](../../../../../src/runtime/memory_report_detail.hpp) |

## B0012

[Lines 22–30](../../../../../src/runtime/memory_report.cpp#L22); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void arena(const storage::ArenaMemoryStatistics& value) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Check arena usage/count partition before accepting table memory diagnostics. |
| inputs / outputs | Sum state-control,directory,live/retained/free/exhausted slots and live/retained values; require owner.current equality and allocation counts matching record categories. |
| invariants | Arena owner is actual allocation attribution,not a row-size estimate. Categories partition resident usage; retained/free capacity stays visible. |
| ownership | Fixed local sums of already captured numeric data, no arena pointers retained. |
| failure | Overflow/inconsistent throws private fixed Failure and aborts report. |
| cost | Fixed category additions/checks; actual slot/ledger scans occurred in delegated memory_statistics. |
| Design | [docs/memory_reports.md](../../../../memory_reports.md), [include/crown/runtime/memory_report.hpp](../../../../../include/crown/runtime/memory_report.hpp), [src/runtime/memory_report_detail.hpp](../../../../../src/runtime/memory_report_detail.hpp) |

## B0013

[Lines 31–31](../../../../../src/runtime/memory_report.cpp#L31); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L31-L31:sha256:412ca345ccf75bf9c0806bce695be8de808b79984251a7a54d202cf6101dd451
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Close the \`anonymous namespace in src/runtime/memory_report.cpp\` scope at this exact source boundary. |
| inputs / outputs | This token introduces no callable inputs or outputs. Declarations inside \`anonymous namespace in src/runtime/memory_report.cpp\` define the available names, members and operations. |
| invariants | The closing brace matches the opening \`anonymous namespace in src/runtime/memory_report.cpp\` at its lexical source position in src/runtime/memory_report.cpp; it preserves C++ namespace/type nesting. |
| ownership | The closing delimiter creates no owner. Types closed by \`anonymous namespace in src/runtime/memory_report.cpp\` retain the lifetimes and allocator rules of their own fields and operations. |
| failure | No failure path executes at this closing delimiter. Failure and cleanup behavior belong to enclosed functions and owning types. |
| cost | The delimiter itself performs no runtime work; the enclosed initializers, methods and destructors carry their own costs. |
| Design | [docs/memory_reports.md](../../../../memory_reports.md), [docs/query_memory.md](../../../../query_memory.md), [docs/memory_accounts.md](../../../../memory_accounts.md), [docs/code_specs/subsystem_contracts.md](../../../subsystem_contracts.md) |

## B0014

[Lines 32–35](../../../../../src/runtime/memory_report.cpp#L32); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::uint64_t Builder::add(std::uint64_t a,std::uint64_t b) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Add memory/report work dimensions without U64 wrap. |
| inputs / outputs | a,b return exact sum iff b&lt;=MAX-a. |
| invariants | No partial/saturated resident totals allowed; cap admission separate. |
| ownership | Inline operands/result only. |
| failure | Failure(overflow) before overflowing result. |
| cost | Constant checked arithmetic. |
| Design | [docs/memory_reports.md](../../../../memory_reports.md), [include/crown/runtime/memory_report.hpp](../../../../../include/crown/runtime/memory_report.hpp), [src/runtime/memory_report_detail.hpp](../../../../../src/runtime/memory_report_detail.hpp) |

## B0015

[Lines 36–40](../../../../../src/runtime/memory_report.cpp#L36); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Builder::Builder(const resource::MemoryAccount& account,Layer layer,Availability availability,std::uint64_t owner,
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Create a private memory report on the actual original account. |
| inputs / outputs | Account,layer,committed/pending/released availability,owner,sequence,physical SHA,Limits and external Usage reference charge initial work then allocate Data. |
| invariants | Hash width checked by Data. Source/runtime metadata is descriptive; account totals will include this report itself once finalized. |
| ownership | Original account capture/14 funds Data/arrays; Builder borrows Usage/limits for synchronous capture lifetime. |
| failure | Work/hash/account/allocation failure leaves no public Report; caller attempt wrapper unwinds. |
| cost | One account-backed holder and fixed metadata copy; no ledger scan yet. |
| Design | [docs/memory_reports.md](../../../../memory_reports.md), [include/crown/runtime/memory_report.hpp](../../../../../include/crown/runtime/memory_report.hpp), [src/runtime/memory_report_detail.hpp](../../../../../src/runtime/memory_report_detail.hpp) |

## B0016

[Lines 41–44](../../../../../src/runtime/memory_report.cpp#L41); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void Builder::work(std::uint64_t amount) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Debit explicit diagnostic work without resetting the supplied capture allowance. |
| inputs / outputs | Usage.work and amount checked against fixed Limits.work before add. |
| invariants | Cumulative within this capture; work units reserve scans/sorts,not elapsed time/native maintenance grant. |
| ownership | Borrowed Usage counter only. |
| failure | Failure(work_limit) before overflow/over-cap increment. |
| cost | Constant arithmetic. |
| Design | [docs/memory_reports.md](../../../../memory_reports.md), [include/crown/runtime/memory_report.hpp](../../../../../include/crown/runtime/memory_report.hpp), [src/runtime/memory_report_detail.hpp](../../../../../src/runtime/memory_report_detail.hpp) |

## B0017

[Lines 45–48](../../../../../src/runtime/memory_report.cpp#L45); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void Builder::operation(Operator value) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Append one recorded current-runtime operator under cap. |
| inputs / outputs | Charge work,require operators.size&lt;limit then push variant and update usage.operators. |
| invariants | Operator counts/attribution describe current committed runtime; no owner bytes added twice or hidden factor availability as0. |
| ownership | Private account-owned operator vector moves fixed variant. |
| failure | Cap/account allocation failure aborts private report; no runtime mutation. |
| cost | Amortized vector append,possible capacity growth/copy of prior fixed carriers. |
| Design | [docs/memory_reports.md](../../../../memory_reports.md), [include/crown/runtime/memory_report.hpp](../../../../../include/crown/runtime/memory_report.hpp), [src/runtime/memory_report_detail.hpp](../../../../../src/runtime/memory_report_detail.hpp) |

## B0018

[Lines 49–53](../../../../../src/runtime/memory_report.cpp#L49); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::uint64_t Builder::records(TableScope scope,RelationId relation) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Resolve recorded live table count for a matching scope and relation. |
| inputs / outputs | Linear table vector scan charges each visit,returns live_records at first exact key. |
| invariants | Scope distinguishes support and physical-source relation IDs. Missing join is inconsistency,not zero. |
| ownership | Borrow private report array only. |
| failure | Failure(work_limit/inconsistent) before publication. |
| cost | O(recorded tables) per lookup,not a constant index. |
| Design | [docs/memory_reports.md](../../../../memory_reports.md), [include/crown/runtime/memory_report.hpp](../../../../../include/crown/runtime/memory_report.hpp), [src/runtime/memory_report_detail.hpp](../../../../../src/runtime/memory_report_detail.hpp) |

## B0019

[Lines 54–74](../../../../../src/runtime/memory_report.cpp#L54); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void Builder::table(TableScope scope,const storage::AccountedStorageTable& table,RelationRole role,
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Capture actual native table/arena memory after reserving delegated diagnostic scans. |
| inputs / outputs | Under table cap read account allocation count A and O(1) arena record/slot counters,charge3A+slots,invoke memory_statistics,check live/table/arena/owned reconciliation and append Table metadata. |
| invariants | Reservation covers actual account-ledger,arena slot high-water and index/node scans before traversal. No tuple payload byte scan or execution budget hidden as constant getter; private tables omitted by caller pending mode. |
| ownership | Stores copied numeric backend variant and IDs,not table/arena pointer. Report vector allocates on same account after scan; actual table/arena state unchanged. |
| failure | Work/cap/account/storage/inconsistent error aborts report; old runtime and previous reports remain resident. Counter history can still reflect attempted report allocation. |
| cost | O(account allocations+arena high-water slots+resident index/key/member metadata) delegated scans per table,plus account-owned vector append. |
| Design | [docs/memory_reports.md](../../../../memory_reports.md), [include/crown/runtime/memory_report.hpp](../../../../../include/crown/runtime/memory_report.hpp), [src/runtime/memory_report_detail.hpp](../../../../../src/runtime/memory_report_detail.hpp), [src/storage/accounted_arena.cpp](../../../../../src/storage/accounted_arena.cpp), [src/storage/accounted_reference.cpp](../../../../../src/storage/accounted_reference.cpp), [src/storage/accounted_indexed.cpp](../../../../../src/storage/accounted_indexed.cpp), [src/resource/memory.cpp](../../../../../src/resource/memory.cpp) |

```text
const auto allocations=data_->account.statistics().current.allocations;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Reserve delegated table diagnostic traversal before owner/arena/index scans begin. |
| inputs / outputs | Actual account allocation count and fixed arena slots determine conservative3A+slots work admission. |
| invariants | Each table/index/member node backed by allocation; actual owner and arena diagnostics scan ledgers/slot high-water/resident metadata,not O(1) getters. |
| ownership | Fixed counters borrowed; no new table state or row mirror. |
| failure | Work exhaustion precedes expensive delegated scan; source remains unchanged. |
| cost | O(1) counters/preflight followed by separately bounded scans. |
| Design | [docs/memory_reports.md](../../../../memory_reports.md), [include/crown/runtime/memory_report.hpp](../../../../../include/crown/runtime/memory_report.hpp), [src/runtime/memory_report_detail.hpp](../../../../../src/runtime/memory_report_detail.hpp), [src/storage/accounted_table.cpp](../../../../../src/storage/accounted_table.cpp), [src/storage/accounted_arena.cpp](../../../../../src/storage/accounted_arena.cpp) |

## B0020

[Lines 75–112](../../../../../src/runtime/memory_report.cpp#L75); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Report Builder::finish() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Finalize an account-wide exact ownership partition at a scratch-free captured instant. |
| inputs / outputs | Inventory all current attribution keys plus operator keys in funded scratch,sort/deduplicate under work cap,reserve owner rows,release scratch,sample account,scan ledger per owner and reconcile total/purpose/lifetime plus table/arena owner joins. |
| invariants | Snapshot includes its own retained Data/arrays but not released key scratch. All report/member allocations complete before sampled instant; no later successful scan allocates. Multiple table/operator joins do not multiply actual owner bytes. Query access serialized so captured ledger stays stable. |
| ownership | Scratch keys and report owner arrays use same original account; immutable Report shares const Data after success. Retained account may include older generations/reports/cursors/output. |
| failure | Work/owner/cap/overflow/allocation/inconsistent failure leaves no partial Report and releases private storage. Runtime logical state unchanged; historical account peaks/attempts may rise. |
| cost | For A allocations,U owner keys,O operators,T table reports: O((A+O)log(A+O)) sort plus O(U*A) ledger attribution scans and O(T log U) joins,account-funded scratch/array growth. Not a maintenance hot path. |
| Design | [docs/memory_reports.md](../../../../memory_reports.md), [include/crown/runtime/memory_report.hpp](../../../../../include/crown/runtime/memory_report.hpp), [src/runtime/memory_report_detail.hpp](../../../../../src/runtime/memory_report_detail.hpp), [src/resource/memory.cpp](../../../../../src/resource/memory.cpp), [tests/unit/operator_memory_report_test.cpp](../../../../../tests/unit/operator_memory_report_test.cpp) |

```text
const auto n=account.statistics().current.allocations;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Fund a sufficient live allocation-key inventory including scratch itself and zero-byte operator owners. |
| inputs / outputs | Reserve n+operator_count+1 keys,resize n+1 to include new scratch allocation,copy account attributions,append operators,sort/deduplicate and admit owner limit. |
| invariants | Inventory is per allocation,not a unique-owner registry. Appended operator keys ensure logical operators with no current allocation still have0owner rows. Actual account handles/framing apply. |
| ownership | Scratch MemoryAllocator uses capture/14; private owner vector separately funded before scratch release. |
| failure | Overflow/work/owner/account failure aborts private report; no partial partition. |
| cost | O(A+O) inventory and O((A+O)log(A+O)) metered sorting,temporary capacity under original account. |
| Design | [docs/memory_reports.md](../../../../memory_reports.md), [include/crown/runtime/memory_report.hpp](../../../../../include/crown/runtime/memory_report.hpp), [src/runtime/memory_report_detail.hpp](../../../../../src/runtime/memory_report_detail.hpp), [src/resource/memory.cpp](../../../../../src/resource/memory.cpp) |

```text
data_->snapshot.account=account.statistics();
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Record the account instant after diagnostic key scratch has been destroyed. |
| inputs / outputs | All final Report arrays already allocated; captured current/purpose/lifetime/history/peak include this report's resident storage and any other held account owners. |
| invariants | No future activity mutates this stored snapshot. Historical peaks may include earlier scratch,as cumulative account facts. |
| ownership | Fixed stats copy; Account retained by Report. |
| failure | Subsequent successful reconciliation performs no allocation,under serialized owner access. Failure discards private report. |
| cost | Constant account statistics copy; later per-owner scans explicit. |
| Design | [docs/memory_reports.md](../../../../memory_reports.md), [include/crown/runtime/memory_report.hpp](../../../../../include/crown/runtime/memory_report.hpp), [src/runtime/memory_report_detail.hpp](../../../../../src/runtime/memory_report_detail.hpp) |

```text
work(data_->snapshot.account.current.allocations);row=account.statistics_for(row.attribution);sum(total,row.current);
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Reconcile every owner by actual ledger scan and sum exact category partitions. |
| inputs / outputs | One A-work reservation per attribution precedes statistics_for; totals,purpose and lifetime arrays must equal sampled account instant. |
| invariants | Shared attribution keys counted once. Table/arena joins later check exact same owner rows,not separate additional bytes. |
| ownership | Writes only preallocated numeric owner records/local sums. |
| failure | Work/overflow/inconsistent failure stops report,not a partial success. |
| cost | O(U*A) ledger visits plus fixed category additions; no row payload scan. |
| Design | [docs/memory_reports.md](../../../../memory_reports.md), [include/crown/runtime/memory_report.hpp](../../../../../include/crown/runtime/memory_report.hpp), [src/runtime/memory_report_detail.hpp](../../../../../src/runtime/memory_report_detail.hpp), [src/resource/memory.cpp](../../../../../src/resource/memory.cpp) |

## B0021

[Lines 113–113](../../../../../src/runtime/memory_report.cpp#L113); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L113-L113:sha256:9b13ff9c39c1549372d6da49ddeb62b23042ce320c72e1a0dbe6e3bb292a34bd
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Close the \`namespace detail\` scope at this exact source boundary. |
| inputs / outputs | This token introduces no callable inputs or outputs. Declarations inside \`namespace detail\` define the available names, members and operations. |
| invariants | The closing brace matches the opening \`namespace detail\` at its lexical source position in src/runtime/memory_report.cpp; it preserves C++ namespace/type nesting. |
| ownership | The closing delimiter creates no owner. Types closed by \`namespace detail\` retain the lifetimes and allocator rules of their own fields and operations. |
| failure | No failure path executes at this closing delimiter. Failure and cleanup behavior belong to enclosed functions and owning types. |
| cost | The delimiter itself performs no runtime work; the enclosed initializers, methods and destructors carry their own costs. |
| Design | [docs/memory_reports.md](../../../../memory_reports.md), [docs/query_memory.md](../../../../query_memory.md), [docs/memory_accounts.md](../../../../memory_accounts.md), [docs/code_specs/subsystem_contracts.md](../../../subsystem_contracts.md) |

## B0022

[Lines 114–114](../../../../../src/runtime/memory_report.cpp#L114); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Attempt capture(const SupportRuntime& owner,Limits limits) noexcept{return detail::Access::capture(owner,limits);}
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Expose bounded actual-account memory capture for SupportRuntime. |
| inputs / outputs | Actual owner+Limits forward to private Access::capture and return Attempt with fixed stop/report/usage. |
| invariants | Delegated native access selects committed/pending. Pending report has account partition without committed table/operator counts; absent native owner returns invalid_handle rather than a fabricated released state. |
| ownership | Successful immutable Report owns original-account arrays/metadata independently of runtime lifetime. |
| failure | noexcept uses existing private attempt mapping for limit,MemoryFailure,bad_alloc,inconsistent errors; no partial report or extra handler here. |
| cost | Constant forwarding plus full table/ledger/sort/capture work; no execution advance. |
| Design | [docs/memory_reports.md](../../../../memory_reports.md), [include/crown/runtime/memory_report.hpp](../../../../../include/crown/runtime/memory_report.hpp), [src/runtime/memory_report_detail.hpp](../../../../../src/runtime/memory_report_detail.hpp), [src/runtime/support.cpp](../../../../../src/runtime/support.cpp), [src/runtime/physical.cpp](../../../../../src/runtime/physical.cpp), [src/runtime/delta.cpp](../../../../../src/runtime/delta.cpp), [src/runtime/session.cpp](../../../../../src/runtime/session.cpp) |

## B0023

[Lines 115–115](../../../../../src/runtime/memory_report.cpp#L115); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Attempt capture(const PhysicalRuntime& owner,Limits limits) noexcept{return detail::Access::capture(owner,limits);}
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Expose bounded actual-account memory capture for PhysicalRuntime. |
| inputs / outputs | Actual owner+Limits forward to private Access::capture and return Attempt with fixed stop/report/usage. |
| invariants | Delegated native access selects committed/pending. Pending report has account partition without committed table/operator counts; absent native owner returns invalid_handle rather than a fabricated released state. |
| ownership | Successful immutable Report owns original-account arrays/metadata independently of runtime lifetime. |
| failure | noexcept uses existing private attempt mapping for limit,MemoryFailure,bad_alloc,inconsistent errors; no partial report or extra handler here. |
| cost | Constant forwarding plus full table/ledger/sort/capture work; no execution advance. |
| Design | [docs/memory_reports.md](../../../../memory_reports.md), [include/crown/runtime/memory_report.hpp](../../../../../include/crown/runtime/memory_report.hpp), [src/runtime/memory_report_detail.hpp](../../../../../src/runtime/memory_report_detail.hpp), [src/runtime/support.cpp](../../../../../src/runtime/support.cpp), [src/runtime/physical.cpp](../../../../../src/runtime/physical.cpp), [src/runtime/delta.cpp](../../../../../src/runtime/delta.cpp), [src/runtime/session.cpp](../../../../../src/runtime/session.cpp) |

## B0024

[Lines 116–116](../../../../../src/runtime/memory_report.cpp#L116); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Attempt capture(const DeltaRuntime& owner,Limits limits) noexcept{return detail::Access::capture(owner,limits);}
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Expose bounded actual-account memory capture for DeltaRuntime. |
| inputs / outputs | Actual owner+Limits forward to private Access::capture and return Attempt with fixed stop/report/usage. |
| invariants | Delegated native access selects committed/pending. Pending report has account partition without committed table/operator counts; absent native owner returns invalid_handle rather than a fabricated released state. |
| ownership | Successful immutable Report owns original-account arrays/metadata independently of runtime lifetime. |
| failure | noexcept uses existing private attempt mapping for limit,MemoryFailure,bad_alloc,inconsistent errors; no partial report or extra handler here. |
| cost | Constant forwarding plus full table/ledger/sort/capture work; no execution advance. |
| Design | [docs/memory_reports.md](../../../../memory_reports.md), [include/crown/runtime/memory_report.hpp](../../../../../include/crown/runtime/memory_report.hpp), [src/runtime/memory_report_detail.hpp](../../../../../src/runtime/memory_report_detail.hpp), [src/runtime/support.cpp](../../../../../src/runtime/support.cpp), [src/runtime/physical.cpp](../../../../../src/runtime/physical.cpp), [src/runtime/delta.cpp](../../../../../src/runtime/delta.cpp), [src/runtime/session.cpp](../../../../../src/runtime/session.cpp) |

## B0025

[Lines 117–117](../../../../../src/runtime/memory_report.cpp#L117); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Attempt capture(const QuerySession& owner,Limits limits) noexcept{return detail::Access::capture(owner,limits);}
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Expose bounded actual-account memory capture for QuerySession. |
| inputs / outputs | Actual owner+Limits forward to private Access::capture and return Attempt with fixed stop/report/usage. |
| invariants | Delegated session guard enforces thread/reentry and selects committed,pending or released. Pending/released reports have account partition without fabricated committed table/operator counts. |
| ownership | Successful immutable Report owns original-account arrays/metadata independently of runtime lifetime. |
| failure | noexcept uses existing private attempt mapping for limit,MemoryFailure,bad_alloc,inconsistent errors; no partial report or extra handler here. |
| cost | Constant forwarding plus full table/ledger/sort/capture work; no execution advance. |
| Design | [docs/memory_reports.md](../../../../memory_reports.md), [include/crown/runtime/memory_report.hpp](../../../../../include/crown/runtime/memory_report.hpp), [src/runtime/memory_report_detail.hpp](../../../../../src/runtime/memory_report_detail.hpp), [src/runtime/support.cpp](../../../../../src/runtime/support.cpp), [src/runtime/physical.cpp](../../../../../src/runtime/physical.cpp), [src/runtime/delta.cpp](../../../../../src/runtime/delta.cpp), [src/runtime/session.cpp](../../../../../src/runtime/session.cpp) |

## B0026

[Lines 118–118](../../../../../src/runtime/memory_report.cpp#L118); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L118-L118:sha256:cc9f9f9d572a149929a625b44b3ffa79c1d2209276bdd6d1cac1ea537361b653
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Close the \`namespace crown::runtime::memory\` scope at this exact source boundary. |
| inputs / outputs | This token introduces no callable inputs or outputs. Declarations inside \`namespace crown::runtime::memory\` define the available names, members and operations. |
| invariants | The closing brace matches the opening \`namespace crown::runtime::memory\` at its lexical source position in src/runtime/memory_report.cpp; it preserves C++ namespace/type nesting. |
| ownership | The closing delimiter creates no owner. Types closed by \`namespace crown::runtime::memory\` retain the lifetimes and allocator rules of their own fields and operations. |
| failure | No failure path executes at this closing delimiter. Failure and cleanup behavior belong to enclosed functions and owning types. |
| cost | The delimiter itself performs no runtime work; the enclosed initializers, methods and destructors carry their own costs. |
| Design | [docs/memory_reports.md](../../../../memory_reports.md), [docs/query_memory.md](../../../../query_memory.md), [docs/memory_accounts.md](../../../../memory_accounts.md), [docs/code_specs/subsystem_contracts.md](../../../subsystem_contracts.md) |
