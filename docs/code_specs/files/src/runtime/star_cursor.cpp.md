# `src/runtime/star_cursor.cpp` — block usage map

[Source](../../../../../src/runtime/star_cursor.cpp) · [Source index](../../../README.md) · [Subsystem contracts](../../../subsystem_contracts.md) · [Reviewed primitives](../../../primitives.md)

Pace live-group projection candidates, deduplicate borrowed keys and return original-account owning outputs under a read lease.

Snapshot SHA-256: `32817f5aba44654eabe5dc8169dd51fafec565e599c038c7c84e9eb863d03d49`. 139 lines partitioned into 22 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [star](../../../subsystem_contracts.md#star). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/star.md](../../../../star.md), [docs/query_memory.md](../../../../query_memory.md), [docs/code_review.md](../../../../code_review.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–8](../../../../../src/runtime/star_cursor.cpp#L1) | Imports dependencies; declares namespace scope; declares values/defaults or compile-time conditions. |  · [reviewed contract](#b0001) |
| [B0002 · 9–11](../../../../../src/runtime/star_cursor.cpp#L9) | Callable definition: template&lt;class T&gt; auto cursor_allocator(const resource::MemoryAccount& account) | calls ; returns resource::MemoryAllocator&lt;T&gt;(account, resource::MemoryPurpose::cursor, cursor_memory) · [reviewed contract](#b0002) |
| [B0003 · 12–25](../../../../../src/runtime/star_cursor.cpp#L12) | declares types or opens a type body; declares values/defaults or compile-time conditions. | source comment (unverified): // namespace · [reviewed contract](#b0003) |
| [B0004 · 26–52](../../../../../src/runtime/star_cursor.cpp#L26) | Callable definition: Data(std::shared_ptr&lt;Runtime::Data&gt; runtime, CursorOptions requested) : owner(std::move(runtime)), options(requested), seen(std::… | calls owner, std::move, options, seen; guard detail::require(projection != (*group)-&gt;projections.cend(), "live star group has no projection");; 1 loop sites; source comment (unverified): // The per-output duplicate bound is product_hidden(1 + heavy_keys_i). · [reviewed contract](#b0004) |
| [B0005 · 53–53](../../../../../src/runtime/star_cursor.cpp#L53) | Callable definition: ~Data() | calls close · [reviewed contract](#b0005) |
| [B0006 · 54–54](../../../../../src/runtime/star_cursor.cpp#L54) | Explanatory comments or spacing. |  |
| [B0007 · 55–59](../../../../../src/runtime/star_cursor.cpp#L55) | Callable definition: void take() | calls Error · [reviewed contract](#b0007) |
| [B0008 · 60–60](../../../../../src/runtime/star_cursor.cpp#L60) | Explanatory comments or spacing. |  |
| [B0009 · 61–70](../../../../../src/runtime/star_cursor.cpp#L61) | Callable definition: void close() noexcept | calls size, clear, reset; source comment (unverified): // Each seen key required two charged actions and queue.size() &lt;= seen.size(), · [reviewed contract](#b0009) |
| [B0010 · 71–71](../../../../../src/runtime/star_cursor.cpp#L71) | Explanatory comments or spacing. |  |
| [B0011 · 72–103](../../../../../src/runtime/star_cursor.cpp#L72) | Callable definition: std::optional&lt;storage::Tuple&gt; advance() | calls take, cend, view, insert; guard detail::require(projection != (*group)-&gt;projections.cend(), "live star group has no projection");; returns {}; std::optional&lt;storage::Tuple&gt;{std::move(tuple)}; growth insert, push_back; 1 loop sites; source comment (unverified): // Includes an empty-source or exhausted-queue termination attempt. · [reviewed contract](#b0011) |
| [B0012 · 104–105](../../../../../src/runtime/star_cursor.cpp#L104) | Closes surrounding scope/type. |  · [reviewed contract](#b0012) |
| [B0013 · 106–106](../../../../../src/runtime/star_cursor.cpp#L106) | Callable definition: Runtime::Cursor::Cursor(resource::AccountedUnique&lt;Data&gt; data) noexcept : data_(std::move(data)) | calls data_, std::move · [reviewed contract](#b0013) |
| [B0014 · 107–107](../../../../../src/runtime/star_cursor.cpp#L107) | Callable definition: Runtime::Cursor::~Cursor() | calls cancel · [reviewed contract](#b0014) |
| [B0015 · 108–108](../../../../../src/runtime/star_cursor.cpp#L108) | Callable definition: Runtime::Cursor::Cursor(Cursor&& other) noexcept : data_(std::move(other.data_)), closed_(other.closed_) | calls data_, std::move, closed_ · [reviewed contract](#b0015) |
| [B0016 · 109–114](../../../../../src/runtime/star_cursor.cpp#L109) | Callable definition: Runtime::Cursor& Runtime::Cursor::operator=(Cursor&& other) noexcept | calls std::move; returns *this · [reviewed contract](#b0016) |
| [B0017 · 115–118](../../../../../src/runtime/star_cursor.cpp#L115) | Callable definition: void Runtime::Cursor::cancel() noexcept | calls close, reset · [reviewed contract](#b0017) |
| [B0018 · 119–119](../../../../../src/runtime/star_cursor.cpp#L119) | Callable definition: CursorMetrics Runtime::Cursor::metrics() const noexcept | calls ; returns data_ ? data_-&gt;metrics : closed_ · [reviewed contract](#b0018) |
| [B0019 · 120–129](../../../../../src/runtime/star_cursor.cpp#L120) | Callable definition: std::optional&lt;storage::Tuple&gt; Runtime::Cursor::next() | calls advance, cancel; returns {}; result · [reviewed contract](#b0019) |
| [B0020 · 130–130](../../../../../src/runtime/star_cursor.cpp#L130) | Explanatory comments or spacing. |  |
| [B0021 · 131–138](../../../../../src/runtime/star_cursor.cpp#L131) | Callable definition: Runtime::Cursor Runtime::results(CursorOptions options) const | calls data, readable, detail::require, max; guard detail::require(owner.readers != std::numeric_limits&lt;std::uint64_t&gt;::max(), "star reader count over…; returns Cursor(std::move(prepared)); growth make_accounted_unique · [reviewed contract](#b0021) |
| [B0022 · 139–139](../../../../../src/runtime/star_cursor.cpp#L139) | Closes surrounding scope/type. | source comment (unverified): // namespace crown::runtime::star · [reviewed contract](#b0022) |

## B0001

[Lines 1–8](../../../../../src/runtime/star_cursor.cpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L1-L8:sha256:a852aab687164652f7ecf42b3feb22dfb105f939b79d3d9df594f04102051490
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Bind the projection cursor implementation to its native containers and attribution. |
| inputs / outputs | Includes and cursor_memory identify the original-account cursor allocation role. |
| invariants | This private producer operates on already maintained star groups; it performs no query admission or source update. |
| ownership | Later allocation helpers receive the retained Runtime::Data account explicitly. |
| failure | Compilation/include errors are separate from cursor construction refusal. |
| cost | Declaration/setup work only. |
| Design | [docs/star.md](../../../../star.md), [build/verification/v68-star-proof-v1/audit.txt §7](../../../../../build/verification/v68-star-proof-v1/audit.txt), [docs/result_cursors.md](../../../../result_cursors.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0002

[Lines 9–11](../../../../../src/runtime/star_cursor.cpp#L9); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L9-L11:sha256:bf182c6a3ec24ff9de7a1c3b5d69e65366e3b3e4ba007d39aab8b8ed3471d650
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Create a cursor-purpose allocator on the original query account. |
| inputs / outputs | cursor_allocator&lt;T&gt;(account) returns MemoryAllocator&lt;T&gt; with cursor:0 attribution. |
| invariants | Seen/queue/control memory is not given an unrelated account or per-next refill. |
| ownership | The allocator retains the original account for capacity lifetime. |
| failure | Invalid account/purpose refusal follows existing allocator contracts. |
| cost | Fixed construction; actual container allocations/account framing are additional. |
| Design | [docs/star.md](../../../../star.md), [build/verification/v68-star-proof-v1/audit.txt §7](../../../../../build/verification/v68-star-proof-v1/audit.txt), [docs/result_cursors.md](../../../../result_cursors.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0003

[Lines 12–25](../../../../../src/runtime/star_cursor.cpp#L12); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L12-L25:sha256:50ea18cedf8d50d19b3bfa6c172736e53d3e37ddea3b728035924e7bcd360b59
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Retain the view owner, borrowed projection streams and private distinct-output buffers. |
| inputs / outputs | Cursor::Data stores owner, options/metrics, seen set, queue, live-group/projection iterators and a lease flag. |
| invariants | Projection keys stay immutable while the lease pins the committed epoch. Queue/seen contain borrowed RowViews, not ordinary owning row mirrors. |
| ownership | The shared owner retains all borrowed payload; map/deque storage uses its original account. |
| failure | The factory acquires the reader lease only after successful construction. |
| cost | O(seen outputs+queued views) private scratch plus fixed stream state. |
| Design | [docs/star.md](../../../../star.md), [build/verification/v68-star-proof-v1/audit.txt §7](../../../../../build/verification/v68-star-proof-v1/audit.txt), [docs/result_cursors.md](../../../../result_cursors.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0004

[Lines 26–52](../../../../../src/runtime/star_cursor.cpp#L26); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L26-L52:sha256:1f8d919a17ac6606f23fdae0e6fc1e4f58e99ebdc39262ea8753680ba05dad9a
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Prepare the overflow-safe candidate quantum and first nonempty group stream. |
| inputs / outputs | Constructor creates accounted distinct/queue buffers, scans hidden coordinates and computes min(max(1,N), product(1+heavy keys)). |
| invariants | j is the distinct head-variable count through free flags. Every candidate has a center-row witness; full heads use quantum one. |
| ownership | Owner sharing pins map payload during construction, but no reader count is published until the factory finishes. |
| failure | Lifetime work, allocation or invalid live-group projection refusal destroys private members without leaking a lease. |
| cost | O(d) selected startup and real control/deque/set setup; this is not free whole-query preprocessing. |
| Design | [docs/star.md](../../../../star.md), [build/verification/v68-star-proof-v1/audit.txt §7](../../../../../build/verification/v68-star-proof-v1/audit.txt), [docs/result_cursors.md](../../../../result_cursors.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0005

[Lines 53–53](../../../../../src/runtime/star_cursor.cpp#L53); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L53-L53:sha256:7672bac2176dc3530a1595ca20c7bc4773ef31cd2c583ea0173185cf3789b56c
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Close the cursor lease and borrowed scratch during Data destruction. |
| inputs / outputs | The destructor delegates to idempotent close(). |
| invariants | Buffers are cleared before dropping the retained Runtime owner. |
| ownership | Original-account container storage is released by member destruction. |
| failure | Valid destruction is nonthrowing and never publishes a query update. |
| cost | Actual O(cursor scratch) closure and possible last-owner source/view destruction. |
| Design | [docs/star.md](../../../../star.md), [build/verification/v68-star-proof-v1/audit.txt §7](../../../../../build/verification/v68-star-proof-v1/audit.txt), [docs/result_cursors.md](../../../../result_cursors.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0007

[Lines 55–59](../../../../../src/runtime/star_cursor.cpp#L55); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L55-L59:sha256:18347ac027b2ed648c1fa95b68023e2608a4390b05689f612722f4b4f23222fc
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Spend the cursor lifetime work balance before another selected action. |
| inputs / outputs | take compares metrics.work with immutable options.work, then increments once. |
| invariants | Construction and every active next share this same balance, including empty/end attempts. |
| ownership | Only local metrics are changed; no source/query epoch is mutated. |
| failure | Exhaustion raises star_cursor_work_limit before the selected action; outer next closes the lease. |
| cost | Fixed comparison/increment, excluding scalar/container work. |
| Design | [docs/star.md](../../../../star.md), [build/verification/v68-star-proof-v1/audit.txt §7](../../../../../build/verification/v68-star-proof-v1/audit.txt), [docs/result_cursors.md](../../../../result_cursors.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0009

[Lines 61–70](../../../../../src/runtime/star_cursor.cpp#L61); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L61-L70:sha256:368995af5801d6c0e95b58f10f02ab462ac58d81317aebfc27a5eb314994855b
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Clear borrowed output scratch and release one reader lease exactly once. |
| inputs / outputs | close records seen+queue cleanup items, clears both containers, decrements readers if leased and resets owner. |
| invariants | Queue size cannot exceed seen size; the sum fits prior charged work. No projection payload is used after owner release. |
| ownership | Retained query ownership is dropped only after all borrowed RowViews are discarded. |
| failure | Noexcept/idempotent closure; it must complete even after work or allocation refusal. |
| cost | O(seen+queue) teardown and deallocation; a final owner reset can additionally destroy source/view state. |
| Design | [docs/star.md](../../../../star.md), [build/verification/v68-star-proof-v1/audit.txt §7](../../../../../build/verification/v68-star-proof-v1/audit.txt), [docs/result_cursors.md](../../../../result_cursors.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0011

[Lines 72–103](../../../../../src/runtime/star_cursor.cpp#L72); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L72-L103:sha256:a297563f216dcddf51c4a64483c47f05bb0a43b5405a83bb4e9cbcc2e85ee555
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Pace global projection deduplication with a bounded candidate quantum. |
| inputs / outputs | advance consumes up to K per-group distinct head entries, queues newly seen views, advances nonempty group streams and emits one separately owned tuple. |
| invariants | Multiplicity at most product_hidden(1+heavy keys) makes the queue productive until exhaustion; empty queue with candidates remaining is an invariant error. |
| ownership | Seen/queue views borrow leased group keys; output tuple/layout payload is funded and owned independently before queue removal. |
| failure | Selected-work, comparison/allocation or internal failure propagates to next(), which cancels the cursor and preserves the maintained view. |
| cost | O(K) selected candidate/group actions per active call plus ordered seen comparisons, tuple/scalar copies, allocation and explicit final cleanup; no P2 end-to-end delay claim. |
| Design | [docs/star.md](../../../../star.md), [build/verification/v68-star-proof-v1/audit.txt §7](../../../../../build/verification/v68-star-proof-v1/audit.txt), [docs/result_cursors.md](../../../../result_cursors.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0012

[Lines 104–105](../../../../../src/runtime/star_cursor.cpp#L104); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L104-L105:sha256:cdbb10f75f6890449819c9d57e5ae7b786fb73c5111c5d829c37bc18f3e053e8
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Close the private cursor producer type before public handle definitions. |
| inputs / outputs | Type closure separates internal stream state from Runtime::Cursor wrappers. |
| invariants | It adds no output or lease transition. |
| ownership | No new storage ownership. |
| failure | No runtime failure. |
| cost | No runtime work. |
| Design | [docs/star.md](../../../../star.md), [build/verification/v68-star-proof-v1/audit.txt §7](../../../../../build/verification/v68-star-proof-v1/audit.txt), [docs/result_cursors.md](../../../../result_cursors.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0013

[Lines 106–106](../../../../../src/runtime/star_cursor.cpp#L106); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L106-L106:sha256:efb628a37ff112db397a3f4073735535176718c86d9042c46fb52d3640d3a97f
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Wrap a fully prepared original-account cursor control. |
| inputs / outputs | Private Cursor constructor moves AccountedUnique&lt;Data&gt; into the public move-only handle. |
| invariants | The factory already published its valid lease after all fallible Data construction. |
| ownership | The unique owner retains the original allocator/deleter and its shared Runtime owner. |
| failure | Noexcept handle construction. |
| cost | Fixed ownership transfer. |
| Design | [docs/star.md](../../../../star.md), [build/verification/v68-star-proof-v1/audit.txt §7](../../../../../build/verification/v68-star-proof-v1/audit.txt), [docs/result_cursors.md](../../../../result_cursors.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0014

[Lines 107–107](../../../../../src/runtime/star_cursor.cpp#L107); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L107-L107:sha256:702361fb21ad53d695e73cda5003c462d125a19f5b521ebb42cddcdf4c2a7a2f
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Cancel any active cursor on public handle destruction. |
| inputs / outputs | Cursor destructor delegates to cancel(). |
| invariants | One live lease is released even if the consumer stops before terminal null. |
| ownership | Private buffers/control use original allocators; prior owning result tuples are independent. |
| failure | Noexcept cancellation/destruction under native allocator contracts. |
| cost | Actual cursor scratch and possible last-owner teardown costs. |
| Design | [docs/star.md](../../../../star.md), [build/verification/v68-star-proof-v1/audit.txt §7](../../../../../build/verification/v68-star-proof-v1/audit.txt), [docs/result_cursors.md](../../../../result_cursors.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0015

[Lines 108–108](../../../../../src/runtime/star_cursor.cpp#L108); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L108-L108:sha256:3a80f8c2bc4641140c7fbeb5d72d4ab34eac15f16d08fecc75761bde7f8057e2
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Move a cursor while transferring its active reader ownership. |
| inputs / outputs | Move construction transfers unique Data and copies closed scalar metrics. |
| invariants | The moved-from handle has no active control and cannot close the transferred lease. |
| ownership | Data ownership and its account/deleter are moved, not cloned. |
| failure | Noexcept move. |
| cost | Fixed handle/metric movement. |
| Design | [docs/star.md](../../../../star.md), [build/verification/v68-star-proof-v1/audit.txt §7](../../../../../build/verification/v68-star-proof-v1/audit.txt), [docs/result_cursors.md](../../../../result_cursors.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0016

[Lines 109–114](../../../../../src/runtime/star_cursor.cpp#L109); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L109-L114:sha256:c1cdc26af24318bb38df03a31069ca70c015ae5558a97f9d120037dc540547ce
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Replace a cursor after closing the destination lease. |
| inputs / outputs | Move assignment cancels old Data, transfers the source control and retains the source closed metrics. |
| invariants | Self-assignment is inert; the old reader cannot remain live after replacement. |
| ownership | Original allocator ownership follows each unique control; returned owning tuples remain valid. |
| failure | Noexcept replacement; old cleanup cannot allocate. |
| cost | Fixed movement plus actual cleanup of the replaced cursor/query owner. |
| Design | [docs/star.md](../../../../star.md), [build/verification/v68-star-proof-v1/audit.txt §7](../../../../../build/verification/v68-star-proof-v1/audit.txt), [docs/result_cursors.md](../../../../result_cursors.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0017

[Lines 115–118](../../../../../src/runtime/star_cursor.cpp#L115); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L115-L118:sha256:8cbaa19011178bcaf7f90022b94674310a009bce1c27dba8f79c679da26d4c30
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Explicitly close an active cursor and preserve its final metrics. |
| inputs / outputs | cancel calls Data::close, copies its metrics into closed_, and releases unique Data; a closed handle is inert. |
| invariants | Its lease is removed once and no borrowed views survive query-owner release. |
| ownership | Metric scalars survive without retaining account/state; cursor control is destroyed by its original deleter. |
| failure | Noexcept and idempotent, including after an active next failure. |
| cost | O(private scratch) and possible final owner cleanup, not constant cancellation. |
| Design | [docs/star.md](../../../../star.md), [build/verification/v68-star-proof-v1/audit.txt §7](../../../../../build/verification/v68-star-proof-v1/audit.txt), [docs/result_cursors.md](../../../../result_cursors.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0018

[Lines 119–119](../../../../../src/runtime/star_cursor.cpp#L119); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L119-L119:sha256:de7eed6c613b25df82c95b9a1b31fcaf5928e59bb85c1cd6854d5832169b9506
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Return active or final closed cursor counters. |
| inputs / outputs | metrics copies Data::metrics when live, otherwise closed_. |
| invariants | The returned counters distinguish selected production from cleanup_items. |
| ownership | Only scalar metric values are returned. |
| failure | Noexcept read; it does not advance or acquire another lease. |
| cost | Fixed-size copy. |
| Design | [docs/star.md](../../../../star.md), [build/verification/v68-star-proof-v1/audit.txt §7](../../../../../build/verification/v68-star-proof-v1/audit.txt), [docs/result_cursors.md](../../../../result_cursors.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0019

[Lines 120–129](../../../../../src/runtime/star_cursor.cpp#L120); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L120-L129:sha256:d5f271b54e9ee7a6555f9e845d4c81458960691003eca19896784e26179c7ee6
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Expose one owning result or terminal null with failure-safe lease release. |
| inputs / outputs | next returns null for closed Data, otherwise advances and cancels on terminal null; any exception cancels then rethrows. |
| invariants | This catch is a concrete cursor cleanup boundary, not retry/fallback or source mutation. |
| ownership | Earlier returned tuples own their rows/layouts after private cursor scratch is discarded. |
| failure | Work/OOM/invariant failure closes the cursor before escaping; caller may create another current-view cursor explicitly. |
| cost | Actual advance work plus terminal/failure O(scratch) cleanup; repeated closed next is constant. |
| Design | [docs/star.md](../../../../star.md), [build/verification/v68-star-proof-v1/audit.txt §7](../../../../../build/verification/v68-star-proof-v1/audit.txt), [docs/result_cursors.md](../../../../result_cursors.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0021

[Lines 131–138](../../../../../src/runtime/star_cursor.cpp#L131); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L131-L138:sha256:fd0b2064cc733f477710d60b0819615dcd7e132cf126f3c4f7ba27b17c8ffb1d
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Publish a committed-view reader only after complete cursor preparation. |
| inputs / outputs | Runtime::results checks readable state and reader headroom, funds/constructs Cursor::Data, then increments readers and marks the lease. |
| invariants | No constructor/allocation failure can leave an extra reader; subsequent updates reject while a lease is live. |
| ownership | The control and all nested buffers use owner.account; Data retains shared Runtime lifetime. |
| failure | Moved/busy state, reader overflow, cursor-work or memory refusal returns no partial cursor. |
| cost | O(d) quantum preparation and actual cursor/deque/control allocation; later outputs and cleanup have their own costs. |
| Design | [docs/star.md](../../../../star.md), [build/verification/v68-star-proof-v1/audit.txt §7](../../../../../build/verification/v68-star-proof-v1/audit.txt), [docs/result_cursors.md](../../../../result_cursors.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0022

[Lines 139–139](../../../../../src/runtime/star_cursor.cpp#L139); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L139-L139:sha256:e898273caf1be38528f5e43eb29805db329a1e942171a5ddef8c4d4c074bbfe3
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Close the star projection cursor implementation namespace. |
| inputs / outputs | Namespace closure finishes public cursor factory/wrapper definitions. |
| invariants | It adds no hidden output flush or query publication. |
| ownership | No storage ownership. |
| failure | No runtime failure. |
| cost | No runtime work. |
| Design | [docs/star.md](../../../../star.md), [build/verification/v68-star-proof-v1/audit.txt §7](../../../../../build/verification/v68-star-proof-v1/audit.txt), [docs/result_cursors.md](../../../../result_cursors.md), [docs/query_memory.md](../../../../query_memory.md) |
