# `src/planner/selection_cache.cpp` — block usage map

[Source](../../../../../src/planner/selection_cache.cpp) · [Source index](../../../README.md) · [Subsystem contracts](../../../subsystem_contracts.md) · [Reviewed primitives](../../../primitives.md)

Manage bounded FIFO plan entries while retaining each entry's allocating account.

Snapshot SHA-256: `4167e549c5a258a662dfe4cb2a2930d6c1ff4b6708e1604b060db0b82d7df12f`. 96 lines partitioned into 18 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [ranking](../../../subsystem_contracts.md#ranking). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/ranking.md](../../../../ranking.md), [docs/selection.md](../../../../selection.md), [docs/selection_binding.md](../../../../selection_binding.md), [docs/ranking_accounting.md](../../../../ranking_accounting.md), [docs/selection_accounting.md](../../../../selection_accounting.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–4](../../../../../src/planner/selection_cache.cpp#L1) | Imports dependencies; declares namespace scope. |  · [reviewed contract](#b0001) |
| [B0002 · 5–5](../../../../../src/planner/selection_cache.cpp#L5) | Callable definition: PlanCache::PlanCache(std::unique_ptr&lt;detail::CacheData&gt; data) noexcept : data_(std::move(data)) | calls data_, std::move · [reviewed contract](#b0002) |
| [B0003 · 6–11](../../../../../src/planner/selection_cache.cpp#L6) | declares callable signatures; declares values/defaults or compile-time conditions. | source comment (unverified): // Replace cache ownership and release old destination entries. See · [reviewed contract](#b0003) |
| [B0004 · 12–16](../../../../../src/planner/selection_cache.cpp#L12) | Callable definition: PlanCache PlanCache::create(CacheLimits limits) | calls Error, PlanCache; returns PlanCache(std::make_unique&lt;detail::CacheData&gt;(limits)); growth make_unique; source comment (unverified): // Create an empty component-owned cache with coherent retention caps. See docs/selection.md. · [reviewed contract](#b0004) |
| [B0005 · 17–17](../../../../../src/planner/selection_cache.cpp#L17) | Callable definition: bool PlanCache::valid() const noexcept | calls ; returns static_cast&lt;bool&gt;(data_) · [reviewed contract](#b0005) |
| [B0006 · 18–18](../../../../../src/planner/selection_cache.cpp#L18) | Callable definition: CacheLimits PlanCache::limits() const noexcept | calls ; returns data_ ? data_-&gt;limits : CacheLimits{0, 0, 0} · [reviewed contract](#b0006) |
| [B0007 · 19–19](../../../../../src/planner/selection_cache.cpp#L19) | Callable definition: CacheStatistics PlanCache::statistics() const noexcept | calls ; returns data_ ? data_-&gt;statistics : CacheStatistics{} · [reviewed contract](#b0007) |
| [B0008 · 20–21](../../../../../src/planner/selection_cache.cpp#L20) | Explanatory comments or spacing. | source comment (unverified): // Release all cached entries and reset committed statistics. See · [reviewed contract](#b0008) |
| [B0009 · 22–22](../../../../../src/planner/selection_cache.cpp#L22) | Callable definition: void PlanCache::clear() noexcept | calls clear; source comment (unverified): // Release all cached entries and reset committed statistics. See · [reviewed contract](#b0009) |
| [B0010 · 23–24](../../../../../src/planner/selection_cache.cpp#L23) | declares namespace scope. |  · [reviewed contract](#b0010) |
| [B0011 · 25–25](../../../../../src/planner/selection_cache.cpp#L25) | Callable definition: void increment(std::uint64_t& n, std::uint64_t amount = 1) | calls Budget::add · [reviewed contract](#b0011) |
| [B0012 · 26–28](../../../../../src/planner/selection_cache.cpp#L26) | Closes surrounding scope/type. | source comment (unverified): // Commit prepared cache changes through funded link moves and scalar assignment. See · [reviewed contract](#b0012) |
| [B0013 · 29–37](../../../../../src/planner/selection_cache.cpp#L29) | Callable definition: void Prepared::commit() noexcept | calls move_front_to, append; 1 loop sites; source comment (unverified): // Commit prepared cache changes through funded link moves and scalar assignment. See · [reviewed contract](#b0013) |
| [B0014 · 38–41](../../../../../src/planner/selection_cache.cpp#L38) | Explanatory comments or spacing. | source comment (unverified): // Called only after the fresh whole-set decision. Lookup stages statistics and · [reviewed contract](#b0014) |
| [B0015 · 42–67](../../../../../src/planner/selection_cache.cpp#L42) | Callable definition: void prepare_cache(Prepared& prepared, CacheData* cache, CacheUse use, Budget& budget) | calls require, has_value, size, work; guard require(cache != nullptr, Stop::invalid_handle);; 1 loop sites; source comment (unverified): // Called only after the fresh whole-set decision. Lookup stages statistics and · [reviewed contract](#b0015) |
| [B0016 · 68–69](../../../../../src/planner/selection_cache.cpp#L68) | Explanatory comments or spacing. | source comment (unverified): // Fund one miss entry and plan FIFO evictions without touching live cache. See · [reviewed contract](#b0016) |
| [B0017 · 70–94](../../../../../src/planner/selection_cache.cpp#L70) | Callable definition: void stage_cache_entry(Prepared& prepared, Budget& budget) | calls require, size, cache_plan_payload, keys; guard require(prepared.cache && data.plan && data.chosen && data.key);; growth make_accounted_unique, push_back; 1 loop sites; source comment (unverified): // Fund one miss entry and plan FIFO evictions without touching live cache. See · [reviewed contract](#b0017) |
| [B0018 · 95–96](../../../../../src/planner/selection_cache.cpp#L95) | Closes surrounding scope/type. | source comment (unverified): // namespace detail · [reviewed contract](#b0018) |

## B0001

[Lines 1–4](../../../../../src/planner/selection_cache.cpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L1-L4:sha256:f519eef23443ea5702f19d57dd7637158bfb128baa9ff531ab7a90bb2d4507a2
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | make #include "selection_detail.hpp", #include "crown/api/error.hpp" available to src/planner/selection_cache.cpp; open crown::planner::selection. |
| inputs / outputs | Preprocessor directives resolve compile-time declarations. This block has no runtime call inputs or result. |
| invariants | Includes, namespace openings, aliases, and forward declarations determine C++ name visibility and type availability; they do not validate planner data or grant proof authority. |
| ownership | No runtime object is owned by the include or scope directives. Any state belongs to the types and functions declared after them. |
| failure | A missing header, incompatible declaration, or ill-formed type use fails during compilation; runtime failures remain in the called code. |
| cost | Adds preprocessing, parsing, and any later template-instantiation work in this translation unit. It adds no runtime timer, counter, branch, or allocation. |
| Design | [src/planner/selection_cache.cpp](../../../../../src/planner/selection_cache.cpp), [docs/selection.md](../../../../selection.md), [docs/selection_accounting.md](../../../../selection_accounting.md), [docs/selection_binding.md](../../../../selection_binding.md) |

## B0002

[Lines 5–5](../../../../../src/planner/selection_cache.cpp#L5); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
PlanCache::PlanCache(std::unique_ptr<detail::CacheData> data) noexcept
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Adopt the validated empty cache implementation. |
| inputs / outputs | Moves unique Data into facade. |
| invariants | No lookup/entry allocation occurs here. |
| ownership | Exclusive ownership. |
| failure | Noexcept adoption. |
| cost | Pointer move. |
| Design | [docs/selection_accounting.md §Atomic publication](../../../../selection_accounting.md) |

## B0003

[Lines 6–11](../../../../../src/planner/selection_cache.cpp#L6); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
PlanCache::~PlanCache() = default;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Release every retained cache entry and last-owned plan. |
| inputs / outputs | Destroys Data/Entries iteratively. |
| invariants | Prior Selection handles retain their own plans. |
| ownership | Drops exclusive cache and per-node account owners. |
| failure | Nonthrowing native teardown. |
| cost | Linear entry/key/plan release outside selection grants. |
| Design | [docs/selection_accounting.md §Atomic publication](../../../../selection_accounting.md), [docs/query_memory.md §Boundaries](../../../../query_memory.md) |

```text
PlanCache::PlanCache(PlanCache&&) noexcept = default;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Transfer cache ownership without moving node payloads. |
| inputs / outputs | Moves unique implementation pointer. |
| invariants | Distinct source becomes empty; entry accounts stay original. |
| ownership | Exclusive transfer. |
| failure | Noexcept; moved observers use defaults. |
| cost | Fixed pointer move. |
| Design | [docs/selection_accounting.md §Atomic publication](../../../../selection_accounting.md) |

```text
PlanCache& PlanCache::operator=(PlanCache&&) noexcept = default;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Replace cache ownership and release old destination entries. |
| inputs / outputs | Unique-pointer assignment transfers source after old teardown. |
| invariants | Published result owners remain independent. |
| ownership | Can release old final-owned account/program payload. |
| failure | Noexcept under contained destructors. |
| cost | Pointer move plus potentially full old cache teardown. |
| Design | [docs/selection_accounting.md §Atomic publication](../../../../selection_accounting.md), [docs/query_memory.md §Boundaries](../../../../query_memory.md) |

## B0004

[Lines 12–16](../../../../../src/planner/selection_cache.cpp#L12); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
PlanCache PlanCache::create(CacheLimits limits) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Create an empty component-owned cache with coherent retention caps. |
| inputs / outputs | Positive entry capacity requires positive key/payload caps; zero entries disables cache. |
| invariants | Caps are logical retention, not query allocator limits. |
| ownership | Allocates ordinary CacheData; inserted nodes later use query accounts. |
| failure | Bad limits throw selection_cache_limits; allocation propagates. |
| cost | One header allocation, no plan/row storage. |
| Design | [docs/selection.md](../../../../selection.md), [docs/selection_accounting.md §Atomic publication](../../../../selection_accounting.md) |

## B0005

[Lines 17–17](../../../../../src/planner/selection_cache.cpp#L17); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
bool PlanCache::valid() const noexcept
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Test whether the facade owns cache Data. |
| inputs / outputs | Returns pointer presence. |
| invariants | No lookup, mutation or account refill occurs. |
| ownership | Returns independent scalar values. |
| failure | Noexcept moved-from guard. |
| cost | One pointer test. |
| Design | [docs/selection.md](../../../../selection.md) |

## B0006

[Lines 18–18](../../../../../src/planner/selection_cache.cpp#L18); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
CacheLimits PlanCache::limits() const noexcept
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Copy accepted cache retention caps. |
| inputs / outputs | Moved-from returns {0,0,0}. |
| invariants | No lookup, mutation or account refill occurs. |
| ownership | Returns independent scalar values. |
| failure | Noexcept moved-from guard. |
| cost | Fixed scalar copy. |
| Design | [docs/selection.md](../../../../selection.md) |

## B0007

[Lines 19–19](../../../../../src/planner/selection_cache.cpp#L19); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
CacheStatistics PlanCache::statistics() const noexcept
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Copy committed cache counters. |
| inputs / outputs | Moved-from returns zeros. |
| invariants | No lookup, mutation or account refill occurs. |
| ownership | Returns independent scalar values. |
| failure | Noexcept moved-from guard. |
| cost | Fixed snapshot. |
| Design | [docs/selection.md](../../../../selection.md) |

## B0008

[Lines 20–21](../../../../../src/planner/selection_cache.cpp#L20); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L20-L21:sha256:3b3d11ca17fb19939a2c48af5aadf5eb1fa6a3fcf8bd06f676621ee32b451b90
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Use the adjacent note for clear: Release all cached entries and reset committed statistics. Confirm behavior against the declaration and implementation; comment text alone does not enforce or prove it. |
| inputs / outputs | This comment has no inputs or outputs. It accompanies clear; use the adjacent declaration and implementation for the actual values and result. |
| invariants | This is static guidance only. The comment cannot alter state or guarantee that its wording holds. |
| ownership | The note owns no storage and changes no lifetime; ownership and borrowing for clear come from its actual types and implementation. |
| failure | Reading the comment has no runtime failure path. Compile or link errors, exceptions, and resource stops belong to the adjacent code. |
| cost | The comment adds no runtime instructions, allocation, clock read, counter debit, or engine hook; only source-text processing is added. |
| Design | [src/planner/selection_cache.cpp](../../../../../src/planner/selection_cache.cpp), [docs/selection.md](../../../../selection.md), [docs/selection_accounting.md](../../../../selection_accounting.md), [docs/selection_binding.md](../../../../selection_binding.md) |

## B0009

[Lines 22–22](../../../../../src/planner/selection_cache.cpp#L22); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void PlanCache::clear() noexcept
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Release all cached entries and reset committed statistics. |
| inputs / outputs | No-op if moved; otherwise iterative list clear then zero stats. |
| invariants | Does not invalidate separately retained Selection/program owners. |
| ownership | Drops cache ownership only. |
| failure | Noexcept and no new allocation. |
| cost | Linear nodes plus last-owner native graph release; separate caller operation. |
| Design | [docs/selection_accounting.md §Atomic publication](../../../../selection_accounting.md), [docs/query_memory.md §Boundaries](../../../../query_memory.md) |

## B0010

[Lines 23–24](../../../../../src/planner/selection_cache.cpp#L23); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L23-L24:sha256:15942a1ef98533a5f8c95849cbc0497e0f8e16726f6d0ccecc350e4a6e610c01
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | open detail and anonymous helper namespace in src/planner/selection_cache.cpp. |
| inputs / outputs | This namespace, scope, or declaration boundary has no runtime call inputs or outputs. |
| invariants | It changes compile-time visibility or declaration identity only; attached comments do not enforce or prove the described behavior. |
| ownership | This span creates no runtime owner. Later object definitions and calls determine storage and lifetimes. |
| failure | An invalid declaration or scope boundary fails compilation; no runtime exception or resource stop comes from this span. |
| cost | Compile-time parsing and preprocessor bookkeeping only; no runtime branch, allocation, clock read, counter debit, or engine hook. |
| Design | [src/planner/selection_cache.cpp](../../../../../src/planner/selection_cache.cpp), [docs/selection.md](../../../../selection.md), [docs/selection_accounting.md](../../../../selection_accounting.md), [docs/selection_binding.md](../../../../selection_binding.md) |

## B0011

[Lines 25–25](../../../../../src/planner/selection_cache.cpp#L25); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void increment(std::uint64_t& n,
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Stage cache counter increments without wrapping. |
| inputs / outputs | Delegates Budget::add with UINT64_MAX and counter_overflow label. |
| invariants | Only local next counters are changed before commit. |
| ownership | Borrows scalar counter. |
| failure | Overflow throws resource Failure. |
| cost | Fixed arithmetic. |
| Design | [docs/selection_accounting.md §Atomic publication](../../../../selection_accounting.md) |

## B0012

[Lines 26–28](../../../../../src/planner/selection_cache.cpp#L26); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L26-L28:sha256:477fc4239be2fb8bc67450f8859ff8c0beff3f1781838a29f5b40bbb3b6577f1
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | This block close the lexical scope identified by the source span. Its attached note introduces nearby behavior: Commit prepared cache changes through funded link moves and scalar assignment. |
| inputs / outputs | A scope delimiter has no call inputs or outputs; it controls which following declarations belong to the C++ namespace, class, or helper scope. |
| invariants | The braces set lexical visibility and type boundaries only. Any attached note is documentation and does not enforce behavior. |
| ownership | The delimiter and note acquire, release, or transfer no runtime object. Member lifetimes come from the enclosed type definitions. |
| failure | An unmatched or misplaced brace fails compilation; this block adds no runtime exception or resource-stop path. |
| cost | No runtime work or allocation is added. The compiler parses the scope boundary and comment. |
| Design | [src/planner/selection_cache.cpp](../../../../../src/planner/selection_cache.cpp), [docs/selection.md](../../../../selection.md), [docs/selection_accounting.md](../../../../selection_accounting.md), [docs/selection_binding.md](../../../../selection_binding.md) |

## B0013

[Lines 29–37](../../../../../src/planner/selection_cache.cpp#L29); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void Prepared::commit() noexcept {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Commit prepared cache changes through funded link moves and scalar assignment. |
| inputs / outputs | Moves evicted fronts into retired, appends insertion, assigns next statistics. |
| invariants | No allocation or last-plan destruction crosses the no-fail barrier; wrapper/result ownership already exists. |
| ownership | Retired nodes stay privately owned until after publication. |
| failure | Noexcept relies on valid eviction/list/count preparation. |
| cost | O(evictions) link operations; later retired graph destruction is separate. |
| Design | [docs/selection_accounting.md §Atomic publication](../../../../selection_accounting.md) |

## B0014

[Lines 38–41](../../../../../src/planner/selection_cache.cpp#L38); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L38-L41:sha256:0c3022dc3820156b2afad658234a801b9e49ee45ea0cf16fdd14211c0e3511f7
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Use the adjacent note for prepare_cache: Called only after the fresh whole-set decision. Lookup stages statistics and may choose the existing complete plan; no cache-owned object is changed here. Prepare a cache observation and prospective counters after fresh whole-set ranking. Confirm behavior against the declaration and implementation; comment text alone does not enforce or prove it. |
| inputs / outputs | This comment has no inputs or outputs. It accompanies prepare_cache; use the adjacent declaration and implementation for the actual values and result. |
| invariants | This is static guidance only. The comment cannot alter state or guarantee that its wording holds. |
| ownership | The note owns no storage and changes no lifetime; ownership and borrowing for prepare_cache come from its actual types and implementation. |
| failure | Reading the comment has no runtime failure path. Compile or link errors, exceptions, and resource stops belong to the adjacent code. |
| cost | The comment adds no runtime instructions, allocation, clock read, counter debit, or engine hook; only source-text processing is added. |
| Design | [src/planner/selection_cache.cpp](../../../../../src/planner/selection_cache.cpp), [docs/selection.md](../../../../selection.md), [docs/selection_accounting.md](../../../../selection_accounting.md), [docs/selection_binding.md](../../../../selection_binding.md) |

## B0015

[Lines 42–67](../../../../../src/planner/selection_cache.cpp#L42); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void prepare_cache(Prepared& prepared,
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Prepare a cache observation and prospective counters after fresh whole-set ranking. |
| inputs / outputs | Handles bypass/disabled, copies caps/stats, compares full keys in FIFO order; hit shares plan, miss stages count/disposition. |
| invariants | No list/statistic mutation; hits do not reorder. read_only may update counters only at later successful commit. |
| ownership | Borrows exclusive cache; result retains hit program independently. |
| failure | Byte/work/counter stops discard prospective observation, preserving cache. |
| cost | O(entries plus examined key bytes); hit avoids only winner lower, not fresh assessments. |
| Design | [docs/selection.md](../../../../selection.md), [docs/selection_accounting.md §Atomic publication](../../../../selection_accounting.md), [docs/selection_binding.md §Physical source and artifact frames](../../../../selection_binding.md) |

## B0016

[Lines 68–69](../../../../../src/planner/selection_cache.cpp#L68); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L68-L69:sha256:02551766bafadb65f709a48dde42428c8f6709db8467d660641e92f0fc1484b6
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Use the adjacent note for stage_cache_entry: Fund one miss entry and plan FIFO evictions without touching live cache. Confirm behavior against the declaration and implementation; comment text alone does not enforce or prove it. |
| inputs / outputs | This comment has no inputs or outputs. It accompanies stage_cache_entry; use the adjacent declaration and implementation for the actual values and result. |
| invariants | This is static guidance only. The comment cannot alter state or guarantee that its wording holds. |
| ownership | The note owns no storage and changes no lifetime; ownership and borrowing for stage_cache_entry come from its actual types and implementation. |
| failure | Reading the comment has no runtime failure path. Compile or link errors, exceptions, and resource stops belong to the adjacent code. |
| cost | The comment adds no runtime instructions, allocation, clock read, counter debit, or engine hook; only source-text processing is added. |
| Design | [src/planner/selection_cache.cpp](../../../../../src/planner/selection_cache.cpp), [docs/selection.md](../../../../selection.md), [docs/selection_accounting.md](../../../../selection_accounting.md), [docs/selection_binding.md](../../../../selection_binding.md) |

## B0017

[Lines 70–94](../../../../../src/planner/selection_cache.cpp#L70); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void stage_cache_entry(Prepared& prepared,
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Fund one miss entry and plan FIFO evictions without touching live cache. |
| inputs / outputs | Checks per-entry key/payload caps, charges/writes native key/node, computes next sizes/counters and evictions. |
| invariants | Oversized entry fails rather than bypasses requested caching. Subtractions/next totals are checked before commit. |
| ownership | Private insertion owns query-funded node; raw oldest iterator borrows stable exclusive cache. |
| failure | Any cap/allocation/counter failure destroys private insertion, leaving cache unchanged. |
| cost | Traverses plan payload and evicted prefix, copies key bytes and funds node; no constant-size plan admission claim. |
| Design | [docs/selection_accounting.md §Exact charge primitives](../../../../selection_accounting.md), [docs/selection_accounting.md §Atomic publication](../../../../selection_accounting.md), [docs/query_memory.md §Boundaries](../../../../query_memory.md) |

## B0018

[Lines 95–96](../../../../../src/planner/selection_cache.cpp#L95); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L95-L96:sha256:042b0207769f05d2e9988fc71f197f98b78b936a6e7438fe537c712022e1dc0c
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | close namespace detail and namespace crown::planner::selection in src/planner/selection_cache.cpp. |
| inputs / outputs | This namespace, scope, or declaration boundary has no runtime call inputs or outputs. |
| invariants | It changes compile-time visibility or declaration identity only; attached comments do not enforce or prove the described behavior. |
| ownership | This span creates no runtime owner. Later object definitions and calls determine storage and lifetimes. |
| failure | An invalid declaration or scope boundary fails compilation; no runtime exception or resource stop comes from this span. |
| cost | Compile-time parsing and preprocessor bookkeeping only; no runtime branch, allocation, clock read, counter debit, or engine hook. |
| Design | [src/planner/selection_cache.cpp](../../../../../src/planner/selection_cache.cpp), [docs/selection.md](../../../../selection.md), [docs/selection_accounting.md](../../../../selection_accounting.md), [docs/selection_binding.md](../../../../selection_binding.md) |
