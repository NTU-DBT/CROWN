# `src/runtime/queries.cpp` — block usage map

[Source](../../../../../src/runtime/queries.cpp) · [Source index](../../../README.md) · [Subsystem contracts](../../../subsystem_contracts.md) · [Reviewed primitives](../../../primitives.md)

Maintain Boolean CROWN record/survivor/projected-support state and enumerate current answers from factorized visible relations.

Snapshot SHA-256: `515ba5678f5a54e38b777d1c677242f72ec87fae27435df0becd19c870af4b5a`. 60 lines partitioned into 14 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [support](../../../subsystem_contracts.md#support). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/support_invariants.md](../../../../support_invariants.md), [docs/runtime_support.md](../../../../runtime_support.md), [docs/prepared_epochs.md](../../../../prepared_epochs.md), [docs/result_cursors.md](../../../../result_cursors.md), [docs/epoch_views.md](../../../../epoch_views.md), [docs/code_review.md](../../../../code_review.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–9](../../../../../src/runtime/queries.cpp#L1) | Imports dependencies; declares namespace scope; declares callable signatures; declares values/defaults or compile-time conditions. | guard static_assert(std::is_nothrow_move_assignable_v&lt;QuerySession::Owner::deleter_type&gt;);; source comment (unverified): // Both const inspection and mutable dispatch perform one ordered lookup. · [reviewed contract](#b0001) |
| [B0002 · 10–17](../../../../../src/runtime/queries.cpp#L10) | Callable definition: auto find_entry(auto& entries,std::uint64_t directory,QueryId id) | calls Error, find, end; returns position; source comment (unverified): // Both const inspection and mutable dispatch perform one ordered lookup. · [reviewed contract](#b0002) |
| [B0003 · 18–19](../../../../../src/runtime/queries.cpp#L18) | Closes surrounding scope/type. | source comment (unverified): // namespace · [reviewed contract](#b0003) |
| [B0004 · 20–24](../../../../../src/runtime/queries.cpp#L20) | Callable definition: IndependentQueries::IndependentQueries(QueryDirectoryLimits limits) : account_(resource::MemoryAccount::create(limits.memory_byte… | calls account_, resource::MemoryAccount::create, entries_, limits_ · [reviewed contract](#b0004) |
| [B0005 · 25–25](../../../../../src/runtime/queries.cpp#L25) | Explanatory comments or spacing. |  |
| [B0006 · 26–37](../../../../../src/runtime/queries.cpp#L26) | Callable definition: QueryId IndependentQueries::admit(QuerySession::Owner& session) & | calls Error, size, max, try_emplace; returns {directory_,next_++}; source comment (unverified): // Only this node allocation can fail. Numeric comparison and the subsequent · [reviewed contract](#b0006) |
| [B0007 · 38–38](../../../../../src/runtime/queries.cpp#L38) | Explanatory comments or spacing. |  |
| [B0008 · 39–41](../../../../../src/runtime/queries.cpp#L39) | Callable definition: bool IndependentQueries::contains(QueryId id) const noexcept | calls find, end; returns id.directory == directory_ && entries_.find(id.value) != entries_.end() · [reviewed contract](#b0008) |
| [B0009 · 42–44](../../../../../src/runtime/queries.cpp#L42) | Callable definition: resource::MemoryStatistics IndependentQueries::directory_memory() const | calls statistics; returns account_.statistics() · [reviewed contract](#b0009) |
| [B0010 · 45–47](../../../../../src/runtime/queries.cpp#L45) | Callable definition: QuerySession& IndependentQueries::at(QueryId id) & | calls find_entry; returns *find_entry(entries_,directory_,id)-&gt;second · [reviewed contract](#b0010) |
| [B0011 · 48–50](../../../../../src/runtime/queries.cpp#L48) | Callable definition: const QuerySession& IndependentQueries::at(QueryId id) const & | calls find_entry; returns *find_entry(entries_,directory_,id)-&gt;second · [reviewed contract](#b0011) |
| [B0012 · 51–56](../../../../../src/runtime/queries.cpp#L51) | Callable definition: QuerySession::Owner IndependentQueries::release(QueryId id) & | calls find_entry, std::move, erase; returns result · [reviewed contract](#b0012) |
| [B0013 · 57–59](../../../../../src/runtime/queries.cpp#L57) | Callable definition: void IndependentQueries::erase(QueryId id) & | calls erase, find_entry · [reviewed contract](#b0013) |
| [B0014 · 60–60](../../../../../src/runtime/queries.cpp#L60) | Closes surrounding scope/type. | source comment (unverified): // namespace crown::runtime · [reviewed contract](#b0014) |

## B0001

[Lines 1–9](../../../../../src/runtime/queries.cpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L1-L9:sha256:ea0035afc4ff39e10c9cece23aadfbda49edc1db0c7a6d9ca53dceea2d1cbce1
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Bind the public directory implementation and prove its deleter transfer cannot throw. |
| inputs / outputs | Public declarations, typed Error and numeric/type traits; compile-time nothrow assertion. |
| invariants | Successful node allocation is followed only by a nonthrowing unique-owner transfer. |
| ownership | No owner created by this scope. |
| failure | Build fails if the deleter loses nothrow move assignment. |
| cost | No runtime work for includes/assertion. |
| Design | [docs/independent_queries.md](../../../../independent_queries.md), [Refactor.md §X10](../../../../../Refactor.md), [include/crown/runtime/session.hpp](../../../../../include/crown/runtime/session.hpp), [docs/query_memory.md](../../../../query_memory.md) |

## B0002

[Lines 10–17](../../../../../src/runtime/queries.cpp#L10); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L10-L17:sha256:b9c50785445cd623e39845a58dd8b473ce9b9a0832461fd3f4fae15c76774c1c
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Resolve an ID once for both const and mutable operations. |
| inputs / outputs | Map, expected directory identity and QueryId; returns matching iterator. |
| invariants | Foreign IDs reject before map access; missing/removed ordinal rejects before dereference. |
| ownership | Iterator borrows the map and never retains a query. |
| failure | query_id on foreign/absent identity; no allocation on success. |
| cost | O(logQ), one ordered lookup. |
| Design | [docs/independent_queries.md](../../../../independent_queries.md), [Refactor.md §X10](../../../../../Refactor.md), [include/crown/runtime/session.hpp](../../../../../include/crown/runtime/session.hpp), [docs/query_memory.md](../../../../query_memory.md) |

## B0003

[Lines 18–19](../../../../../src/runtime/queries.cpp#L18); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L18-L19:sha256:c929980d95efc152dc886ac42af0f045075441dd18a8f886364828ead327bbd3
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | End the private lookup-helper scope. |
| inputs / outputs | Namespace delimiter only. |
| invariants | Helper remains translation-unit private. |
| ownership | No ownership operation. |
| failure | No runtime failure. |
| cost | No runtime cost. |
| Design | [docs/independent_queries.md](../../../../independent_queries.md), [Refactor.md §X10](../../../../../Refactor.md), [include/crown/runtime/session.hpp](../../../../../include/crown/runtime/session.hpp), [docs/query_memory.md](../../../../query_memory.md) |

## B0004

[Lines 20–24](../../../../../src/runtime/queries.cpp#L20); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L20-L24:sha256:a469744e347b2c3f12f868fa2d2637dd3c96cead417dd1d12aeeacc53fca6fcb
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Create a fresh independently funded bookkeeping controller and empty ordered directory. |
| inputs / outputs | QueryDirectoryLimits in; empty directory with process-unique account identity out. |
| invariants | Account is constructed before its allocator/map; sessions are never charged to this account. |
| ownership | Directory members retain the metadata account; facade is caller storage. |
| failure | Controller allocation/limit/owner-ID failure aborts construction with no admitted query. |
| cost | One account-controller allocation; empty map has no node allocations. |
| Design | [docs/independent_queries.md](../../../../independent_queries.md), [Refactor.md §X10](../../../../../Refactor.md), [include/crown/runtime/session.hpp](../../../../../include/crown/runtime/session.hpp), [docs/query_memory.md](../../../../query_memory.md) |

## B0006

[Lines 26–37](../../../../../src/runtime/queries.cpp#L26); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L26-L37:sha256:991f7811e41a54c54bd531809ec0ac6ba1ca7c270e36747a055dfb97547c309d
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Admit exactly one already constructed independent session with strong ownership transfer. |
| inputs / outputs | Nonempty caller owner in; fresh QueryId out; caller owner becomes empty only on success. |
| invariants | Check null/count/ordinal exhaustion, allocate empty map node, then nonthrowing move; monotonically increasing ordinal excludes stale-ID reuse. |
| ownership | Original session/account is moved, never cloned; failed allocation leaves it with caller. |
| failure | Typed admission errors or MemoryFailure before transfer. No catch/rollback framework is needed after successful allocation. |
| cost | One map-node allocation and O(logQ) insertion; no session work or new query budget. |
| Design | [docs/independent_queries.md](../../../../independent_queries.md), [Refactor.md §X10](../../../../../Refactor.md), [include/crown/runtime/session.hpp](../../../../../include/crown/runtime/session.hpp), [docs/query_memory.md](../../../../query_memory.md) |

## B0008

[Lines 39–41](../../../../../src/runtime/queries.cpp#L39); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L39-L41:sha256:02539f8df5212c8cfdc6a337cc2c2860113cb49b93851020e6b84c0f4ada2e3a
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Inspect live membership without throwing. |
| inputs / outputs | QueryId in; true only for this directory and a current ordinal. |
| invariants | Foreign identity short-circuits and cannot alias same ordinal. |
| ownership | No ownership change. |
| failure | No failure under numeric comparator/map contracts. |
| cost | O(logQ), no allocation. |
| Design | [docs/independent_queries.md](../../../../independent_queries.md), [Refactor.md §X10](../../../../../Refactor.md), [include/crown/runtime/session.hpp](../../../../../include/crown/runtime/session.hpp), [docs/query_memory.md](../../../../query_memory.md) |

## B0009

[Lines 42–44](../../../../../src/runtime/queries.cpp#L42); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L42-L44:sha256:de203b4033d49cb134ee5dbc9fc9d16f618ada72d0c82b504158ed1053460b5a
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Return actual directory account counters. |
| inputs / outputs | No input; fixed-size MemoryStatistics copy out. |
| invariants | Reports directory metadata only, not combined session memory or RSS. |
| ownership | Copied scalar counters do not retain query owners. |
| failure | Valid constructed account statistics propagate their established contract. |
| cost | O(1) fixed counter copy; no allocation scan. |
| Design | [docs/independent_queries.md](../../../../independent_queries.md), [Refactor.md §X10](../../../../../Refactor.md), [include/crown/runtime/session.hpp](../../../../../include/crown/runtime/session.hpp), [docs/query_memory.md](../../../../query_memory.md) |

## B0010

[Lines 45–47](../../../../../src/runtime/queries.cpp#L45); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L45-L47:sha256:2ae518d0b0756091a645e1c77083abc1b2ae2846f25ed6d0657916e2169c2fe2
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Borrow mutable access to one admitted session. |
| inputs / outputs | QueryId in; QuerySession lvalue reference out. |
| invariants | One checked lookup; reference survives operations on other entries only. |
| ownership | Borrow ends on own removal/release/directory destruction. |
| failure | query_id on foreign/stale/absent ID. |
| cost | O(logQ); callers can keep a valid borrow to avoid lookup per update. |
| Design | [docs/independent_queries.md](../../../../independent_queries.md), [Refactor.md §X10](../../../../../Refactor.md), [include/crown/runtime/session.hpp](../../../../../include/crown/runtime/session.hpp), [docs/query_memory.md](../../../../query_memory.md) |

## B0011

[Lines 48–50](../../../../../src/runtime/queries.cpp#L48); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L48-L50:sha256:feb254377d511a591576862acca6e18a52533261bfba98d663caa791267ac9c0
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Borrow read-only access to one admitted session. |
| inputs / outputs | QueryId in; const QuerySession lvalue reference out. |
| invariants | Const inspection follows exactly the same identity/lifetime validation as mutable lookup. |
| ownership | No owner copied or acquired. |
| failure | query_id on foreign/stale/absent ID. |
| cost | O(logQ), no allocation. |
| Design | [docs/independent_queries.md](../../../../independent_queries.md), [Refactor.md §X10](../../../../../Refactor.md), [include/crown/runtime/session.hpp](../../../../../include/crown/runtime/session.hpp), [docs/query_memory.md](../../../../query_memory.md) |

## B0012

[Lines 51–56](../../../../../src/runtime/queries.cpp#L51); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L51-L56:sha256:f28e34872a54c609a487cb2dae66c2f3fdacf4ca91f0d60dd24240a710252366
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Transfer a current session back to its caller and remove its local name. |
| inputs / outputs | QueryId in; the exact QuerySession::Owner out. |
| invariants | Lookup precedes mutation; move is nonthrowing; removed ID stays invalid permanently. |
| ownership | Returned owner preserves original query account/progress; node memory returns to directory account. |
| failure | Invalid ID fails without transfer; no expected throwing work after owner move. |
| cost | O(logQ) lookup and node removal; session remains alive. |
| Design | [docs/independent_queries.md](../../../../independent_queries.md), [Refactor.md §X10](../../../../../Refactor.md), [include/crown/runtime/session.hpp](../../../../../include/crown/runtime/session.hpp), [docs/query_memory.md](../../../../query_memory.md) |

## B0013

[Lines 57–59](../../../../../src/runtime/queries.cpp#L57); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L57-L59:sha256:57831a4d3e3d96f680b8870de470ad2728b2456c788a2cdcf5ae4275f70695d1
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Destroy only one admitted query owner. |
| inputs / outputs | QueryId in; matched owner and node removed. |
| invariants | No other entry or per-query publication boundary is touched. |
| ownership | Session destructor runs before node/account storage release; held owning snapshots retain normal lifetime. |
| failure | Invalid ID fails before mutation; session destructor is nothrow by owner contract. |
| cost | O(logQ) lookup/removal plus the selected session existing teardown cost. |
| Design | [docs/independent_queries.md](../../../../independent_queries.md), [Refactor.md §X10](../../../../../Refactor.md), [include/crown/runtime/session.hpp](../../../../../include/crown/runtime/session.hpp), [docs/query_memory.md](../../../../query_memory.md) |

## B0014

[Lines 60–60](../../../../../src/runtime/queries.cpp#L60); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L60-L60:sha256:024a31d07f0690bcfeef2cd00cf111a56223bd48741eae7b548b6bc9143d9111
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | End the implementation namespace. |
| inputs / outputs | Namespace delimiter only. |
| invariants | Directory symbols remain in crown::runtime. |
| ownership | No ownership operation. |
| failure | No runtime failure. |
| cost | No runtime cost. |
| Design | [docs/independent_queries.md](../../../../independent_queries.md), [Refactor.md §X10](../../../../../Refactor.md), [include/crown/runtime/session.hpp](../../../../../include/crown/runtime/session.hpp), [docs/query_memory.md](../../../../query_memory.md) |
