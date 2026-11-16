# `src/runtime/reoptimization_detail.hpp` — block usage map

[Source](../../../../../src/runtime/reoptimization_detail.hpp) · [Source index](../../../README.md) · [Subsystem contracts](../../../subsystem_contracts.md) · [Reviewed primitives](../../../primitives.md)

Coordinate input, window control, native epoch preparation, output delivery and durable recovery at one session lifecycle boundary.

Snapshot SHA-256: `e13ac49f2909c0da343e227cfc29cec30c2dbd65e6bb463d7591225d9ae664bc`. 116 lines partitioned into 22 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [session](../../../subsystem_contracts.md#session). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/session_lifecycle.md](../../../../session_lifecycle.md), [docs/session-journal.md](../../../../session-journal.md), [docs/generations.md](../../../../generations.md), [docs/local-sink.md](../../../../local-sink.md), [docs/reoptimization.md](../../../../reoptimization.md), [docs/native-replay.md](../../../../native-replay.md), [docs/update_patterns.md](../../../../update_patterns.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–12](../../../../../src/runtime/reoptimization_detail.hpp#L1) | Imports dependencies; guards repeated header inclusion; declares namespace scope; declares values/defaults or compile-time conditions. | source comment (unverified): // Exceptions carry only an enum: exhausting a migration grant must not need · [reviewed contract](#b0001) |
| [B0002 · 13–13](../../../../../src/runtime/reoptimization_detail.hpp#L13) | Type/record definition: struct Failure | source comment (unverified): // Exceptions carry only an enum: exhausting a migration grant must not need · [reviewed contract](#b0002) |
| [B0003 · 14–14](../../../../../src/runtime/reoptimization_detail.hpp#L14) | declares types or opens a type body. |  · [reviewed contract](#b0003) |
| [B0004 · 15–16](../../../../../src/runtime/reoptimization_detail.hpp#L15) | Callable definition: public: Budget(Status& status,const Limits& limits):status_(status),limits_(limits) | calls status_, limits_ · [reviewed contract](#b0004) |
| [B0005 · 17–21](../../../../../src/runtime/reoptimization_detail.hpp#L17) | Callable definition: void charge(std::uint64_t amount=1) | calls  · [reviewed contract](#b0005) |
| [B0006 · 22–25](../../../../../src/runtime/reoptimization_detail.hpp#L22) | Callable definition: void values(storage::RowView row) | calls charge, size, cells; 1 loop sites · [reviewed contract](#b0006) |
| [B0007 · 26–31](../../../../../src/runtime/reoptimization_detail.hpp#L26) | Callable definition: void values(storage::TupleValuesView row) | calls charge, size; 1 loop sites · [reviewed contract](#b0007) |
| [B0008 · 32–36](../../../../../src/runtime/reoptimization_detail.hpp#L32) | Callable definition: void row(storage::RowView value,bool source) | calls values · [reviewed contract](#b0008) |
| [B0009 · 37–41](../../../../../src/runtime/reoptimization_detail.hpp#L37) | Callable definition: void row(storage::TupleValuesView value,bool source) | calls values · [reviewed contract](#b0009) |
| [B0010 · 42–46](../../../../../src/runtime/reoptimization_detail.hpp#L42) | declares values/defaults or compile-time conditions. |  · [reviewed contract](#b0010) |
| [B0011 · 47–52](../../../../../src/runtime/reoptimization_detail.hpp#L47) | Type/record definition: struct RowLess | returns a.view()&lt;b.view() · [reviewed contract](#b0011) |
| [B0012 · 53–53](../../../../../src/runtime/reoptimization_detail.hpp#L53) | declares aliases; declares values/defaults or compile-time conditions. |  · [reviewed contract](#b0012) |
| [B0013 · 54–56](../../../../../src/runtime/reoptimization_detail.hpp#L54) | Callable definition: inline Rows rows(const resource::MemoryAccount& account,Budget& budget) | calls Rows; returns Rows(RowLess{&budget},resource::MemoryAllocator&lt;storage::AccountedRow&gt;(account,resource::MemoryPurp… · [reviewed contract](#b0013) |
| [B0014 · 57–59](../../../../../src/runtime/reoptimization_detail.hpp#L57) | Type/record definition: struct Access |  · [reviewed contract](#b0014) |
| [B0015 · 60–70](../../../../../src/runtime/reoptimization_detail.hpp#L60) | controls preprocessing; declares aliases; declares types or opens a type body; declares callable signatures; declares values/defaults or compile-time conditions. |  · [reviewed contract](#b0015) |
| [B0016 · 71–71](../../../../../src/runtime/reoptimization_detail.hpp#L71) | Callable definition: \[\[nodiscard\]\] bool active() const noexcept | calls has_value; returns target_.has_value() · [reviewed contract](#b0016) |
| [B0017 · 72–72](../../../../../src/runtime/reoptimization_detail.hpp#L72) | Callable definition: \[\[nodiscard\]\] bool frozen() const noexcept | calls ; returns status_.admission_frozen · [reviewed contract](#b0017) |
| [B0018 · 73–73](../../../../../src/runtime/reoptimization_detail.hpp#L73) | Callable definition: \[\[nodiscard\]\] bool verified() const noexcept | calls ; returns status_.phase==Phase::verified · [reviewed contract](#b0018) |
| [B0019 · 74–74](../../../../../src/runtime/reoptimization_detail.hpp#L74) | Callable definition: \[\[nodiscard\]\] bool caught_up() const noexcept | calls ; returns !head_ && !pending_ && !staged_ · [reviewed contract](#b0019) |
| [B0020 · 75–91](../../../../../src/runtime/reoptimization_detail.hpp#L75) | declares callable signatures; declares values/defaults or compile-time conditions. |  · [reviewed contract](#b0020) |
| [B0021 · 92–101](../../../../../src/runtime/reoptimization_detail.hpp#L92) | Type/record definition: private: struct Entry |  · [reviewed contract](#b0021) |
| [B0022 · 102–116](../../../../../src/runtime/reoptimization_detail.hpp#L102) | declares callable signatures; declares values/defaults or compile-time conditions. | source comment (unverified): // namespace crown::runtime::reoptimization::detail · [reviewed contract](#b0022) |

## B0001

[Lines 1–12](../../../../../src/runtime/reoptimization_detail.hpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L1-L12:sha256:afdc2ee19a6b4cfb89cf57de39785315211d6af834d5f95351520f60796fb38c
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Source usage for this declaration span in src/runtime/reoptimization_detail.hpp: \`#pragma once\` makes this header idempotent within a translation unit; imports \`"crown/runtime/reoptimization.hpp"\`, \`"crown/runtime/delta.hpp"\`, \`&lt;chrono&gt;\`, \`&lt;set&gt;\` for compilation; opens namespace \`crown::runtime::reoptimization::detail\`; declares constant-initialized constexpr/static metadata \`attribution\`; closes \`block opened at line 9\`. Source comment: Exceptions carry only an enum: exhausting a migration grant must not need another allocation from the already exhausted query account. |
| inputs / outputs | This span stores or passes the listed fields \`attribution\`; constructor/function parameters and any outputs are exactly those declared here. |
| invariants | Every closing brace in the span closes the paired lexical namespace/type/block shown in the source. The constexpr/static metadata is initialized as a constant expression and has no per-instance owner. The source note says: Exceptions carry only an enum: exhausting a migration grant must not need another allocation from the already exhausted query account. Prose alone does not enforce the rule. |
| ownership | The source comment describes this adjacent lifetime/account boundary: Exceptions carry only an enum: exhausting a migration grant must not need another allocation from the already exhausted query account. The comment creates no owner; member types and callers determine actual retention. |
| failure | No explicit throw/catch appears in this exact span. Includes, constructors, inline members, static initialization and callees can still fail; follow their enclosing API contracts. |
| cost | Includes/aliases/forwards affect compilation; constexpr/static metadata is constant-initialized. Runtime operation cost belongs to the helper/type that consumes it. |
| Design | [docs/selection.md](../../../../selection.md), [docs/selection_binding.md](../../../../selection_binding.md), [docs/selection_accounting.md](../../../../selection_accounting.md), [docs/reoptimization.md](../../../../reoptimization.md), [docs/code_specs/subsystem_contracts.md](../../../subsystem_contracts.md) |

## B0002

[Lines 13–13](../../../../../src/runtime/reoptimization_detail.hpp#L13); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct Failure {Stop stop;};
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Carry a private fixed migration stop without diagnostic allocation. |
| inputs / outputs | One Stop enum propagates to the candidate status boundary. |
| invariants | Failure cancels candidate work; it is not a committed-source undo or public durable outcome. |
| ownership | Inline enum only. |
| failure | Throwing uses exception-runtime storage, not a formatted string or query-account allocation. |
| cost | Fixed tag; normal exception unwinding is separate. |
| Design | [docs/reoptimization.md](../../../../reoptimization.md), [src/runtime/reoptimization.cpp](../../../../../src/runtime/reoptimization.cpp), [docs/query_memory.md](../../../../query_memory.md) |

## B0003

[Lines 14–14](../../../../../src/runtime/reoptimization_detail.hpp#L14); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L14-L14:sha256:94bfac13d5359274a362df542d1f56e7a5a16e4d78827a51c8b5d9b6fb320ab5
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Source usage for this declaration span in src/runtime/reoptimization_detail.hpp: defines/starts \`class Budget\` in this range. |
| inputs / outputs | The span supplies the listed source-level type/member/alias surface to its consumers; exact fields and parameters are the declarations shown here. |
| invariants | The exact import, alias, namespace and member declarations determine the local compile/link surface; stronger behavior belongs to their constructors and operations. |
| ownership | Imports, namespace aliases, forward declarations and compile guards create no object owner. Runtime ownership starts with declared object instances and their allocator/member types. |
| failure | No explicit throw/catch appears in this exact span. Includes, constructors, inline members, static initialization and callees can still fail; follow their enclosing API contracts. |
| cost | This span changes compile/link structure and type layout. Runtime initialization, allocation, exceptions and operation work follow the declared owner/callable code; no absence is inferred from declaration syntax. |
| Design | [docs/selection.md](../../../../selection.md), [docs/selection_binding.md](../../../../selection_binding.md), [docs/selection_accounting.md](../../../../selection_accounting.md), [docs/reoptimization.md](../../../../reoptimization.md), [docs/code_specs/subsystem_contracts.md](../../../subsystem_contracts.md) |

## B0004

[Lines 15–16](../../../../../src/runtime/reoptimization_detail.hpp#L15); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Budget(Status& status,const Limits& limits)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Borrow the one cumulative equivalence grant. |
| inputs / outputs | Mutable candidate Status and immutable Limits initialize a stack Budget with zero local rows. |
| invariants | Does not reset cumulative equivalence_work; row counters are local to the one verification attempt. |
| ownership | References must outlive the Budget and every RowLess/Rows that borrows it. |
| failure | Nonallocating initialization; later charges can throw fixed Failure. |
| cost | Fixed references/counter, no fresh account/grant. |
| Design | [docs/reoptimization.md](../../../../reoptimization.md), [src/runtime/reoptimization.cpp](../../../../../src/runtime/reoptimization.cpp), [docs/query_memory.md](../../../../query_memory.md) |

## B0005

[Lines 17–21](../../../../../src/runtime/reoptimization_detail.hpp#L17); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void charge(std::uint64_t amount=1)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Admit equivalence work before its operation. |
| inputs / outputs | Amount increments the cumulative status counter only if it fits Limits. |
| invariants | Subtraction-based check avoids overflow; rejected work does not refill earlier debits. |
| ownership | Mutates borrowed status only. |
| failure | Exhaustion raises Failure(equivalence_limit) before increment. |
| cost | Fixed arithmetic/branch; no allocation. |
| Design | [docs/reoptimization.md](../../../../reoptimization.md), [src/runtime/reoptimization.cpp](../../../../../src/runtime/reoptimization.cpp), [docs/query_memory.md](../../../../query_memory.md) |

## B0006

[Lines 22–25](../../../../../src/runtime/reoptimization_detail.hpp#L22); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void values(storage::RowView row)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Charge selected fields and string bytes of a contiguous native row. |
| inputs / outputs | One row visit, field count and present text byte widths debit the existing Budget. |
| invariants | A later rejection keeps previous debits; inline scalar widths are fixed-domain work, not an all-CPU meter. |
| ownership | Borrows row and its text only for this call; retains no payload. |
| failure | Fixed work failure precedes further charged visits; no partial committed source mutation. |
| cost | O(fields+visited string-byte sizing); no owning row copy or allocation. |
| Design | [docs/reoptimization.md](../../../../reoptimization.md), [src/runtime/reoptimization.cpp](../../../../../src/runtime/reoptimization.cpp), [docs/query_memory.md](../../../../query_memory.md) |

## B0007

[Lines 26–31](../../../../../src/runtime/reoptimization_detail.hpp#L26); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void values(storage::TupleValuesView row)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Charge selected fields and string bytes of a native-or-legacy tuple view. |
| inputs / outputs | One row visit, field count and present text byte widths debit the existing Budget. |
| invariants | A later rejection keeps previous debits; inline scalar widths are fixed-domain work, not an all-CPU meter. |
| ownership | Borrows row and its text only for this call; retains no payload. |
| failure | Fixed work failure precedes further charged visits; no partial committed source mutation. |
| cost | O(fields+visited string-byte sizing); no owning row copy or allocation. |
| Design | [docs/reoptimization.md](../../../../reoptimization.md), [src/runtime/reoptimization.cpp](../../../../../src/runtime/reoptimization.cpp), [docs/query_memory.md](../../../../query_memory.md) |

## B0008

[Lines 32–36](../../../../../src/runtime/reoptimization_detail.hpp#L32); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void row(storage::RowView value,bool source)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Admit one source/result census row and record its category. |
| inputs / outputs | Shared row quota and value work precede local row/category increments. |
| invariants | Source/result counters partition successful admitted rows; verification is a single attempt, so their sums fit the same uint64 quota. |
| ownership | Borrows Status/row, stores no row. |
| failure | Row/work exhaustion throws fixed Failure; no rollback of earlier admitted work. |
| cost | Value visits plus fixed quota/category arithmetic; no independent redundant counter overflow framework. |
| Design | [docs/reoptimization.md](../../../../reoptimization.md), [src/runtime/reoptimization.cpp](../../../../../src/runtime/reoptimization.cpp), [docs/query_memory.md](../../../../query_memory.md) |

## B0009

[Lines 37–41](../../../../../src/runtime/reoptimization_detail.hpp#L37); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void row(storage::TupleValuesView value,bool source)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Admit one source/result census row and record its category. |
| inputs / outputs | Shared row quota and value work precede local row/category increments. |
| invariants | Source/result counters partition successful admitted rows; verification is a single attempt, so their sums fit the same uint64 quota. |
| ownership | Borrows Status/row, stores no row. |
| failure | Row/work exhaustion throws fixed Failure; no rollback of earlier admitted work. |
| cost | Value visits plus fixed quota/category arithmetic; no independent redundant counter overflow framework. |
| Design | [docs/reoptimization.md](../../../../reoptimization.md), [src/runtime/reoptimization.cpp](../../../../../src/runtime/reoptimization.cpp), [docs/query_memory.md](../../../../query_memory.md) |

## B0010

[Lines 42–46](../../../../../src/runtime/reoptimization_detail.hpp#L42); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L42-L46:sha256:3894260164f60cb6d3aeed2fe109ac99a8bb6964c816615aecefdda9720aa1ed
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Source usage for this declaration span in src/runtime/reoptimization_detail.hpp: closes \`class Budget\` Member/state declarations in this range include \`std::uint64_t rows_=0\`. |
| inputs / outputs | This span declares/carries these members or local values: \`std::uint64_t rows_=0\`. Constructor/function input and output shapes remain those written in this same source range. |
| invariants | Every closing brace in the span closes the paired lexical namespace/type/block shown in the source. |
| ownership | Imports, namespace aliases, forward declarations and compile guards create no object owner. Runtime ownership starts with declared object instances and their allocator/member types. |
| failure | No explicit throw/catch appears in this exact span. Includes, constructors, inline members, static initialization and callees can still fail; follow their enclosing API contracts. |
| cost | This span changes compile/link structure and type layout. Runtime initialization, allocation, exceptions and operation work follow the declared owner/callable code; no absence is inferred from declaration syntax. |
| Design | [docs/selection.md](../../../../selection.md), [docs/selection_binding.md](../../../../selection_binding.md), [docs/selection_accounting.md](../../../../selection_accounting.md), [docs/reoptimization.md](../../../../reoptimization.md), [docs/code_specs/subsystem_contracts.md](../../../subsystem_contracts.md) |

## B0011

[Lines 47–52](../../../../../src/runtime/reoptimization_detail.hpp#L47); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct RowLess {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Order retained equivalence rows under the same Budget. |
| inputs / outputs | Comparator charges both complete row views, then performs exact typed lexicographic comparison. |
| invariants | Budget must remain live; comparisons can exhaust it. Ordering is exact, not a hash/model estimate. |
| ownership | Borrowed Budget pointer; compared AccountedRows retain payload independently. |
| failure | Throwing comparison affects private set construction only; source owners are unchanged. |
| cost | Both row field/text-width debits plus actual scalar comparisons; no projection or owning copy. |
| Design | [docs/reoptimization.md](../../../../reoptimization.md), [src/runtime/reoptimization.cpp](../../../../../src/runtime/reoptimization.cpp), [docs/query_memory.md](../../../../query_memory.md) |

## B0012

[Lines 53–53](../../../../../src/runtime/reoptimization_detail.hpp#L53); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L53-L53:sha256:16a5e10d87c6792a4b4c7570e0aee3131533026e711356eb9b97a95e06cf770a
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Source usage for this declaration span in src/runtime/reoptimization_detail.hpp: imports or aliases \`Rows=std::set&lt;storage::AccountedRow,RowLess,resource::MemoryAllocator&lt;storage::AccountedRow&gt;&gt;\`. |
| inputs / outputs | The span supplies the listed source-level type/member/alias surface to its consumers; exact fields and parameters are the declarations shown here. |
| invariants | The exact import, alias, namespace and member declarations determine the local compile/link surface; stronger behavior belongs to their constructors and operations. |
| ownership | Allocator-backed storage uses the explicit account/purpose/attribution shown in the declaration or constructor. Accounted row/tuple values own compact payload under their associated account. |
| failure | No explicit throw/catch appears in this exact span. Includes, constructors, inline members, static initialization and callees can still fail; follow their enclosing API contracts. |
| cost | Visible container/member storage can allocate on construction or growth according to its allocator and account binding; method traversal cost occurs where callers use it. |
| Design | [docs/selection.md](../../../../selection.md), [docs/selection_binding.md](../../../../selection_binding.md), [docs/selection_accounting.md](../../../../selection_accounting.md), [docs/reoptimization.md](../../../../reoptimization.md), [docs/code_specs/subsystem_contracts.md](../../../subsystem_contracts.md) |

## B0013

[Lines 54–56](../../../../../src/runtime/reoptimization_detail.hpp#L54); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
inline Rows rows(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Create an empty accounted ordered set for private result equivalence. |
| inputs / outputs | Account and live Budget produce Rows with RowLess and scratch-attributed allocator. |
| invariants | The set must not outlive its Budget; it is private verification state, not a native answer cache. |
| ownership | Future nodes/AccountedRows use the original account; comparator borrows the stack Budget. |
| failure | Later inserts/compares may allocate or throw; RAII destroys scratch on failure. |
| cost | Empty owner construction then O(log R) comparisons and funded nodes per insertion; full result retention is explicit. |
| Design | [docs/reoptimization.md](../../../../reoptimization.md), [src/runtime/reoptimization.cpp](../../../../../src/runtime/reoptimization.cpp), [docs/query_memory.md](../../../../query_memory.md) |

## B0014

[Lines 57–59](../../../../../src/runtime/reoptimization_detail.hpp#L57); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct Access {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Bridge typed runtime source comparison to private verification. |
| inputs / outputs | Two immutable/current Delta owners and one equivalence Budget yield exact same-source result. |
| invariants | Does not infer equivalence from physical SHA or candidate score alone. |
| ownership | Borrows both owners/Budget; retains no alternate source. |
| failure | Underlying work/native errors propagate to State verification boundary. |
| cost | Explicit full source comparison and scalar widths, not a constant metadata check. |
| Design | [docs/reoptimization.md](../../../../reoptimization.md), [src/runtime/reoptimization.cpp](../../../../../src/runtime/reoptimization.cpp), [docs/query_memory.md](../../../../query_memory.md) |

## B0015

[Lines 60–70](../../../../../src/runtime/reoptimization_detail.hpp#L60); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
class State {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Own a private checked candidate while the old source stays authoritative. |
| inputs / outputs | Bootstrap, stage/commit catch-up, barrier/equivalence, preparation and target transfer share original account/status. |
| invariants | Only prepared/verified publication transfers ownership. time can cancel; stage/verify recheck before work. Old source is not rolled back by candidate cancellation. |
| ownership | Retains target/pending/ledger/options under one controller; no production field is added for the test-only friend. |
| failure | Failures record stop and release private resources; old owner follows its existing protocol. |
| cost | Snapshot/build, affected ledger replay, full equivalence and dual-state peak are explicit; not ordinary constant update overhead. |
| Design | [docs/reoptimization.md](../../../../reoptimization.md), [src/runtime/reoptimization.cpp](../../../../../src/runtime/reoptimization.cpp), [docs/query_memory.md](../../../../query_memory.md) |

```text
friend struct ClockCounterTestAccess;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Allow only the internal test build to seed the counter edge. |
| inputs / outputs | Friend declaration exists under CROWN_RUNTIME_TESTING. |
| invariants | Adds no production member, public API or field; normal source validation/factory paths remain real. |
| ownership | Test access borrows a live State and changes only diagnostic clock_reads. |
| failure | Declaration has no runtime failure; tests retain their normal process boundary. |
| cost | Zero production data/instruction overhead. |
| Design | [docs/reoptimization.md](../../../../reoptimization.md), [src/runtime/reoptimization.cpp](../../../../../src/runtime/reoptimization.cpp), [docs/query_memory.md](../../../../query_memory.md) |

## B0016

[Lines 71–71](../../../../../src/runtime/reoptimization_detail.hpp#L71); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
[[nodiscard]] bool active() const noexcept
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Read whether a target owner is still engaged. |
| inputs / outputs | Returns one scalar lifecycle predicate without changing it. |
| invariants | Clock/counter cancellation can invalidate this flag within another call; callers recheck before later target work. |
| ownership | Borrows this State; no owner is returned. |
| failure | Noexcept and nonallocating for a live State. |
| cost | Fixed optional/flag checks. |
| Design | [docs/reoptimization.md](../../../../reoptimization.md), [src/runtime/reoptimization.cpp](../../../../../src/runtime/reoptimization.cpp), [docs/query_memory.md](../../../../query_memory.md) |

## B0017

[Lines 72–72](../../../../../src/runtime/reoptimization_detail.hpp#L72); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
[[nodiscard]] bool frozen() const noexcept
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Read whether new source admission is frozen. |
| inputs / outputs | Returns one scalar lifecycle predicate without changing it. |
| invariants | This flag alone does not establish target engagement, caught-up state or equivalence. |
| ownership | Borrows this State; no owner is returned. |
| failure | Noexcept and nonallocating for a live State. |
| cost | Fixed optional/flag checks. |
| Design | [docs/reoptimization.md](../../../../reoptimization.md), [src/runtime/reoptimization.cpp](../../../../../src/runtime/reoptimization.cpp), [docs/query_memory.md](../../../../query_memory.md) |

## B0018

[Lines 73–73](../../../../../src/runtime/reoptimization_detail.hpp#L73); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
[[nodiscard]] bool verified() const noexcept
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Read the private verified publication phase. |
| inputs / outputs | Returns one scalar lifecycle predicate without changing it. |
| invariants | Actual publication still requires barrier, target and durable/source conditions; metadata is not a proof handle. |
| ownership | Borrows this State; no owner is returned. |
| failure | Noexcept and nonallocating for a live State. |
| cost | Fixed optional/flag checks. |
| Design | [docs/reoptimization.md](../../../../reoptimization.md), [src/runtime/reoptimization.cpp](../../../../../src/runtime/reoptimization.cpp), [docs/query_memory.md](../../../../query_memory.md) |

## B0019

[Lines 74–74](../../../../../src/runtime/reoptimization_detail.hpp#L74); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
[[nodiscard]] bool caught_up() const noexcept
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Read whether backlog, pending replay and staged entry are empty. |
| inputs / outputs | Returns one scalar lifecycle predicate without changing it. |
| invariants | Empty queues alone do not imply active or verified state; use the full caller preconditions. |
| ownership | Borrows this State; no owner is returned. |
| failure | Noexcept and nonallocating for a live State. |
| cost | Fixed optional/flag checks. |
| Design | [docs/reoptimization.md](../../../../reoptimization.md), [src/runtime/reoptimization.cpp](../../../../../src/runtime/reoptimization.cpp), [docs/query_memory.md](../../../../query_memory.md) |

## B0020

[Lines 75–91](../../../../../src/runtime/reoptimization_detail.hpp#L75); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L75-L91:sha256:ee23b25551d6a9b179c090af933fd414992aa05225ba5d7219756d1c20f81d48
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Source usage for this declaration span in src/runtime/reoptimization_detail.hpp; the range contains the state/helper statements shown at its exact source span. |
| inputs / outputs | Compile inputs are the listed headers and namespace/type names. This span adds no result value unless a helper/type definition listed above is instantiated or called. |
| invariants | The exact import, alias, namespace and member declarations determine the local compile/link surface; stronger behavior belongs to their constructors and operations. |
| ownership | Imports, namespace aliases, forward declarations and compile guards create no object owner. Runtime ownership starts with declared object instances and their allocator/member types. |
| failure | No explicit throw/catch appears in this exact span. Includes, constructors, inline members, static initialization and callees can still fail; follow their enclosing API contracts. |
| cost | This span changes compile/link structure and type layout. Runtime initialization, allocation, exceptions and operation work follow the declared owner/callable code; no absence is inferred from declaration syntax. |
| Design | [docs/selection.md](../../../../selection.md), [docs/selection_binding.md](../../../../selection_binding.md), [docs/selection_accounting.md](../../../../selection_accounting.md), [docs/reoptimization.md](../../../../reoptimization.md), [docs/code_specs/subsystem_contracts.md](../../../subsystem_contracts.md) |

## B0021

[Lines 92–101](../../../../../src/runtime/reoptimization_detail.hpp#L92); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Entry(const PhysicalUpdateView& update,std::uint64_t size,storage::AccountedRow row)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Adopt a funded row into one ordered catch-up ledger entry. |
| inputs / outputs | Copies sequence/table/sign/charged-byte metadata and moves its AccountedRow. |
| invariants | Rows are full physical set events; sequence/no-op barriers remain distinct, with no weighted consolidation. |
| ownership | Entry owns row and next unique node; clear/pop detach the chain iteratively before destruction. |
| failure | Construction after funded row allocation uses nonthrowing member moves; outer stage owns cancellation on later failure. |
| cost | Fixed descriptor/handle moves; row copy and Entry allocation were explicit stage costs. |
| Design | [docs/reoptimization.md](../../../../reoptimization.md), [src/runtime/reoptimization.cpp](../../../../../src/runtime/reoptimization.cpp), [docs/query_memory.md](../../../../query_memory.md) |

```text
struct Entry {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Retain one private full-row catch-up record. |
| inputs / outputs | Sequence, modeled bytes, table/sign, owning native row and next node. |
| invariants | Source order is exact; unlink before destroying a long chain. |
| ownership | AccountedRow and AccountedUnique keep original memory authority. |
| failure | Unpublished allocations unwind; entry does not authorize session acknowledgement. |
| cost | One row payload plus one Entry request including account framing. |
| Design | [docs/reoptimization.md](../../../../reoptimization.md), [src/runtime/reoptimization.cpp](../../../../../src/runtime/reoptimization.cpp), [docs/query_memory.md](../../../../query_memory.md) |

## B0022

[Lines 102–116](../../../../../src/runtime/reoptimization_detail.hpp#L102); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L102-L116:sha256:661c9a02edf22bf13acbeac3666ecef7d8b5c044138436347cd49c9dd9f6603c
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Declare four noexcept State helpers and retain account/options/switch/status/artifact identity, optional target/pending epoch, head_/staged_ queue owners and borrowed tail_; close State and its named detail namespace. |
| inputs / outputs | clear_entries, pop, elapsed and increment are helper declarations. The following members hold the complete shown reoptimization state; line 110 initializes the artifact array and is not a scope opener. |
| invariants | The final braces close State and crown::runtime::reoptimization::detail. Numeric/hash/status metadata does not confer publication authority. The helper declarations promise noexcept, not zero work or absence of internal failure handling. |
| ownership | account_ shares its account; target_ and pending_ retain their optional native owner/epoch values. head_ and staged_ are two distinct AccountedUnique&lt;Entry&gt; owners; Entry::next owns the following entry. tail_ is a non-owning pointer into the retained queue, not a third owner. |
| failure | An exception escaping any declared noexcept helper terminates instead of propagating. The declarations themselves do not run cleanup; constructor and other method failures follow their own factory/state contracts. |
| cost | Fixed State members and optional/unique-owner handles here; queue allocation, traversal/destruction, native rebuild/catch-up and time accounting occur when their defined operations run. noexcept does not make those operations constant time or allocation-free. |
| Design | [docs/selection.md](../../../../selection.md), [docs/selection_binding.md](../../../../selection_binding.md), [docs/selection_accounting.md](../../../../selection_accounting.md), [docs/reoptimization.md](../../../../reoptimization.md), [docs/code_specs/subsystem_contracts.md](../../../subsystem_contracts.md) |
