# `src/storage/arena.cpp` — block usage map

[Source](../../../../../src/storage/arena.cpp) · [Source index](../../../README.md) · [Subsystem contracts](../../../subsystem_contracts.md) · [Reviewed primitives](../../../primitives.md)

Keep stable tuple handles and retained deleted payloads for live readers and inverse operations.

Snapshot SHA-256: `363980ce000990d43a7eb38cadc6d73b666eea2bcd366686c2955870a9f06006`. 236 lines partitioned into 46 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [arena](../../../subsystem_contracts.md#arena). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/tuple_arenas.md](../../../../tuple_arenas.md), [docs/storage_journal.md](../../../../storage_journal.md), [docs/query_memory.md](../../../../query_memory.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–11](../../../../../src/storage/arena.cpp#L1) | Imports dependencies; declares namespace scope; declares callable signatures; declares values/defaults or compile-time conditions. |  · [reviewed contract](#b0001) |
| [B0002 · 12–16](../../../../../src/storage/arena.cpp#L12) | Callable definition: ArenaOwnerId new_arena_owner() | calls detail::try_new_arena_owner, Error; returns *owner · [reviewed contract](#b0002) |
| [B0003 · 17–19](../../../../../src/storage/arena.cpp#L17) | Callable definition: void require(bool value, std::string_view message) | calls Error, std::string; guard void require(bool value, std::string_view message) { · [reviewed contract](#b0003) |
| [B0004 · 20–22](../../../../../src/storage/arena.cpp#L20) | declares types or opens a type body. | source comment (unverified): // namespace · [reviewed contract](#b0004) |
| [B0005 · 23–31](../../../../../src/storage/arena.cpp#L23) | Type/record definition: struct Slot |  · [reviewed contract](#b0005) |
| [B0006 · 32–38](../../../../../src/storage/arena.cpp#L32) | declares callable signatures; declares values/defaults or compile-time conditions. | source comment (unverified): // Individual slot allocation keeps payload addresses stable when the vector · [reviewed contract](#b0006) |
| [B0007 · 39–39](../../../../../src/storage/arena.cpp#L39) | Callable definition: explicit State(TupleLayout value) : layout(std::move(value)) | calls layout, std::move, id · [reviewed contract](#b0007) |
| [B0008 · 40–42](../../../../../src/storage/arena.cpp#L40) | declares callable signatures; declares values/defaults or compile-time conditions. |  · [reviewed contract](#b0008) |
| [B0009 · 43–45](../../../../../src/storage/arena.cpp#L43) | Callable definition: void owned(ArenaHandle handle) const | calls Error · [reviewed contract](#b0009) |
| [B0010 · 46–50](../../../../../src/storage/arena.cpp#L46) | Callable definition: bool contains(ArenaHandle handle) const | calls owned, size; returns handle.slot.value &lt; slots.size() && slots\[handle.slot.value\]-&gt;live && · [reviewed contract](#b0010) |
| [B0011 · 51–54](../../../../../src/storage/arena.cpp#L51) | Callable definition: Slot& live(ArenaHandle handle) const | calls contains, Error; returns *slots\[handle.slot.value\] · [reviewed contract](#b0011) |
| [B0012 · 55–62](../../../../../src/storage/arena.cpp#L55) | Callable definition: void link_live(std::size_t position, Slot& slot) noexcept | calls  · [reviewed contract](#b0012) |
| [B0013 · 63–72](../../../../../src/storage/arena.cpp#L63) | Callable definition: void reclaim(std::size_t position, Slot& slot) noexcept | calls reset · [reviewed contract](#b0013) |
| [B0014 · 73–82](../../../../../src/storage/arena.cpp#L73) | Callable definition: void erase(std::size_t position, Slot& slot) noexcept | calls reclaim · [reviewed contract](#b0014) |
| [B0015 · 83–85](../../../../../src/storage/arena.cpp#L83) | Callable definition: void clear() noexcept | calls erase; 1 loop sites · [reviewed contract](#b0015) |
| [B0016 · 86–94](../../../../../src/storage/arena.cpp#L86) | Callable definition: void unpin(ArenaHandle handle) noexcept | calls reclaim · [reviewed contract](#b0016) |
| [B0017 · 95–96](../../../../../src/storage/arena.cpp#L95) | Closes surrounding scope/type. |  · [reviewed contract](#b0017) |
| [B0018 · 97–97](../../../../../src/storage/arena.cpp#L97) | Callable definition: TupleArena::TupleArena(TupleLayout layout) : state_(std::make_shared&lt;State&gt;(std::move(layout))) | calls state_, std::move; growth make_shared · [reviewed contract](#b0018) |
| [B0019 · 98–98](../../../../../src/storage/arena.cpp#L98) | Callable definition: TupleArena::~TupleArena() | calls clear · [reviewed contract](#b0019) |
| [B0020 · 99–99](../../../../../src/storage/arena.cpp#L99) | declares callable signatures; declares values/defaults or compile-time conditions. |  · [reviewed contract](#b0020) |
| [B0021 · 100–106](../../../../../src/storage/arena.cpp#L100) | Callable definition: TupleArena& TupleArena::operator=(TupleArena&& other) noexcept | calls std::move; returns *this · [reviewed contract](#b0021) |
| [B0022 · 107–110](../../../../../src/storage/arena.cpp#L107) | Callable definition: TupleArena::State& TupleArena::state() const | calls Error; returns *state_ · [reviewed contract](#b0022) |
| [B0023 · 111–111](../../../../../src/storage/arena.cpp#L111) | Callable definition: ArenaOwnerId TupleArena::owner() const | calls state; returns state().owner · [reviewed contract](#b0023) |
| [B0024 · 112–112](../../../../../src/storage/arena.cpp#L112) | Callable definition: const TupleLayout& TupleArena::layout() const | calls state; returns state().layout · [reviewed contract](#b0024) |
| [B0025 · 113–113](../../../../../src/storage/arena.cpp#L113) | Callable definition: ArenaStatistics TupleArena::statistics() const | calls state; returns state().counts · [reviewed contract](#b0025) |
| [B0026 · 114–114](../../../../../src/storage/arena.cpp#L114) | Explanatory comments or spacing. |  |
| [B0027 · 115–142](../../../../../src/storage/arena.cpp#L115) | Callable definition: ArenaHandle TupleArena::insert(const Tuple& tuple) | calls state, same_token, layout, Error; returns {s.owner, TupleSlotId{position}, s.slots\[position\]-&gt;generation}; growth emplace, insert, make_unique, push_back; source comment (unverified): // Copy first. optional remains disengaged if a value/string allocation · [reviewed contract](#b0027) |
| [B0028 · 143–143](../../../../../src/storage/arena.cpp#L143) | Callable definition: bool TupleArena::contains(ArenaHandle handle) const | calls state, contains; returns state().contains(handle) · [reviewed contract](#b0028) |
| [B0029 · 144–144](../../../../../src/storage/arena.cpp#L144) | Callable definition: const Tuple& TupleArena::get(ArenaHandle handle) const | calls state, live; returns *state().live(handle).tuple · [reviewed contract](#b0029) |
| [B0030 · 145–152](../../../../../src/storage/arena.cpp#L145) | Callable definition: TupleArena::Pin TupleArena::pin(ArenaHandle handle) const | calls state, live, Error, Pin; returns Pin(state_, handle) · [reviewed contract](#b0030) |
| [B0031 · 153–158](../../../../../src/storage/arena.cpp#L153) | Callable definition: bool TupleArena::erase(ArenaHandle handle) | calls state, contains, erase; returns false; true · [reviewed contract](#b0031) |
| [B0032 · 159–159](../../../../../src/storage/arena.cpp#L159) | Callable definition: void TupleArena::clear() | calls state, clear · [reviewed contract](#b0032) |
| [B0033 · 160–166](../../../../../src/storage/arena.cpp#L160) | Callable definition: void TupleArena::revive(const Pin& pin) noexcept | calls size, std::terminate, link_live · [reviewed contract](#b0033) |
| [B0034 · 167–167](../../../../../src/storage/arena.cpp#L167) | Explanatory comments or spacing. |  |
| [B0035 · 168–169](../../../../../src/storage/arena.cpp#L168) | Callable definition: TupleArena::Pin::Pin(std::shared_ptr&lt;State&gt; state, ArenaHandle handle) noexcept : state_(std::move(state)), handle_(handle) | calls state_, std::move, handle_ · [reviewed contract](#b0035) |
| [B0036 · 170–170](../../../../../src/storage/arena.cpp#L170) | declares callable signatures; declares values/defaults or compile-time conditions. |  · [reviewed contract](#b0036) |
| [B0037 · 171–174](../../../../../src/storage/arena.cpp#L171) | Callable definition: TupleArena::Pin& TupleArena::Pin::operator=(Pin&& other) noexcept | calls std::move; returns *this · [reviewed contract](#b0037) |
| [B0038 · 175–175](../../../../../src/storage/arena.cpp#L175) | Callable definition: TupleArena::Pin::~Pin() | calls reset · [reviewed contract](#b0038) |
| [B0039 · 176–177](../../../../../src/storage/arena.cpp#L176) | Explanatory comments or spacing. | source comment (unverified): // Pin bookkeeping is constant; the final closed-State release can destroy · [reviewed contract](#b0039) |
| [B0040 · 178–180](../../../../../src/storage/arena.cpp#L178) | Callable definition: void TupleArena::Pin::reset() noexcept | calls unpin, reset; source comment (unverified): // Pin bookkeeping is constant; the final closed-State release can destroy · [reviewed contract](#b0040) |
| [B0041 · 181–184](../../../../../src/storage/arena.cpp#L181) | Callable definition: ArenaHandle TupleArena::Pin::handle() const | calls Error; returns handle_ · [reviewed contract](#b0041) |
| [B0042 · 185–188](../../../../../src/storage/arena.cpp#L185) | Callable definition: const Tuple& TupleArena::Pin::get() const | calls handle; returns *state_-&gt;slots\[handle_.slot.value\]-&gt;tuple · [reviewed contract](#b0042) |
| [B0043 · 189–192](../../../../../src/storage/arena.cpp#L189) | Callable definition: bool TupleArena::Pin::is_live() const | calls handle, contains; returns state_-&gt;contains(handle_) · [reviewed contract](#b0043) |
| [B0044 · 193–195](../../../../../src/storage/arena.cpp#L193) | Explanatory comments or spacing. | source comment (unverified): // Explicit diagnostic: scans all high-water slots and allocates two visited · [reviewed contract](#b0044) |
| [B0045 · 196–235](../../../../../src/storage/arena.cpp#L196) | Callable definition: void TupleArena::check_invariants() const | calls state, size, free, live; guard require(position &lt; s.slots.size() && !free\[position\], "invalid/cyclic arena free list");; 3 loop sites; source comment (unverified): // Explicit diagnostic: scans all high-water slots and allocates two visited · [reviewed contract](#b0045) |
| [B0046 · 236–236](../../../../../src/storage/arena.cpp#L236) | Closes surrounding scope/type. | source comment (unverified): // namespace crown::storage · [reviewed contract](#b0046) |

## B0001

[Lines 1–11](../../../../../src/storage/arena.cpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
#include "crown/storage/arena.hpp"
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Define the legacy arena implementation dependencies and reserved lifecycle sentinels. |
| inputs / outputs | Imports public arena/error/owner-allocation interfaces; none reserves size_t max and last_generation reserves uint64 max as the no-wrap terminal generation. |
| invariants | A reusable free slot must be below the terminal generation; ordinary live positions never use the none sentinel. |
| ownership | Includes/constants create no arena or pin allocation. |
| failure | No runtime rejection in these declarations; later constructors/mutators enforce the sentinel bounds. |
| cost | Compile-time/scalar setup only; no per-operation work is added. |
| Design | [docs/tuple_arenas.md](../../../../tuple_arenas.md), [docs/decisions/0012-generational-arena.md](../../../../decisions/0012-generational-arena.md), [Refactor.md §11.4 S03](../../../../../Refactor.md) |

## B0002

[Lines 12–16](../../../../../src/storage/arena.cpp#L12); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
ArenaOwnerId new_arena_owner()
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Acquire a process-wide unique identity for a newly constructed arena. |
| inputs / outputs | Calls the common legacy/accounted try_new_arena_owner authority; returns its nonzero owner ID. |
| invariants | Successful identities never wrap or get reused; later constructor failure may consume an unpublished identity. |
| ownership | Returns a scalar token, not a payload or byte allowance. |
| failure | Exhaustion throws storage_overflow; there is no fallback identity or mutation rollback of the global authority. |
| cost | An atomic compare/exchange loop in the common helper, potentially retried under contention; cold arena construction only. |
| Design | [docs/tuple_arenas.md](../../../../tuple_arenas.md), [docs/decisions/0012-generational-arena.md](../../../../decisions/0012-generational-arena.md), [Refactor.md §11.4 S03](../../../../../Refactor.md), [src/storage/arena_owner.cpp](../../../../../src/storage/arena_owner.cpp) |

## B0003

[Lines 17–19](../../../../../src/storage/arena.cpp#L17); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void require(bool value, std::string_view message)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Report a failed explicit arena invariant without burdening successful checks with owning messages. |
| inputs / outputs | Boolean condition and borrowed message in; normal return or arena_contract Error. |
| invariants | Does not repair state or change counters; used by the diagnostic scan. |
| ownership | Borrows static text on success; Error owns failure text. |
| failure | False throws and diagnostic allocation may also fail. |
| cost | Constant successful check; exception/string work only on rejection. |
| Design | [docs/tuple_arenas.md](../../../../tuple_arenas.md), [docs/decisions/0012-generational-arena.md](../../../../decisions/0012-generational-arena.md), [Refactor.md §11.4 S03](../../../../../Refactor.md) |

## B0004

[Lines 20–22](../../../../../src/storage/arena.cpp#L20); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L20-L22:sha256:f6238b89b760f09bc1de1825e55fb5e12411a0fd8b88e6a4c988201aa6bd4168
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Source usage for this declaration span in src/storage/arena.cpp: defines/starts \`struct TupleArena::State\` in this range; closes \`anonymous namespace\` Member/state declarations in this range include \`} struct TupleArena::State {\`. |
| inputs / outputs | This span declares/carries these members or local values: \`} struct TupleArena::State {\`. Constructor/function input and output shapes remain those written in this same source range. |
| invariants | Every closing brace in the span closes the paired lexical namespace/type/block shown in the source. The source note says: namespace Prose alone does not enforce the rule. |
| ownership | Imports, namespace aliases, forward declarations and compile guards create no object owner. Runtime ownership starts with declared object instances and their allocator/member types. |
| failure | No explicit throw/catch appears in this exact span. Includes, constructors, inline members, static initialization and callees can still fail; follow their enclosing API contracts. |
| cost | This span changes compile/link structure and type layout. Runtime initialization, allocation, exceptions and operation work follow the declared owner/callable code; no absence is inferred from declaration syntax. |
| Design | [docs/storage.md](../../../../storage.md), [docs/tuple_arenas.md](../../../../tuple_arenas.md), [docs/query_memory.md](../../../../query_memory.md), [docs/code_specs/subsystem_contracts.md](../../../subsystem_contracts.md) |

## B0005

[Lines 23–31](../../../../../src/storage/arena.cpp#L23); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct Slot {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Store one stable allocation generation and its live/free/retired lifecycle metadata. |
| inputs / outputs | A tuple is copied into optional payload; fields initialize generation 1, zero pins, no links and provisional live membership. |
| invariants | Publication into the arena lists/counters happens later. A reclaimed slot has no tuple; a retired pinned slot keeps its tuple and cannot be reused. |
| ownership | The separately allocated Slot owns a Tuple; copied native tuples share admitted payload while legacy copies own separate Row bytes. |
| failure | Tuple copy construction can fail before slot publication; no internal catch or partial membership is needed. |
| cost | Fixed slot metadata plus representation-specific tuple copy; separate allocation stabilizes addresses across pointer-vector growth. |
| Design | [docs/tuple_arenas.md](../../../../tuple_arenas.md), [docs/decisions/0012-generational-arena.md](../../../../decisions/0012-generational-arena.md), [Refactor.md §11.4 S03](../../../../../Refactor.md) |

## B0006

[Lines 32–38](../../../../../src/storage/arena.cpp#L32); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
ArenaOwnerId owner = new_arena_owner();
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Retain the shared arena owner, immutable layout, high-water slot directory and intrusive list/counter state. |
| inputs / outputs | Initializes fresh owner identity, slot vector, empty free/live heads and zero ArenaStatistics. |
| invariants | All slots belong to this one owner/layout; live/free membership is linked inside slots, so unlink/reclaim needs no separate allocating container. |
| ownership | State owns standard vector/unique_ptr metadata and layout handle; pins may retain the State after the facade closes. This legacy arena metadata is not query-accounted. |
| failure | Owner acquisition may throw during construction; vector metadata grows only through insert, not during reclamation. |
| cost | O(total slots) retained high-water metadata, with vector capacity possibly above size; counter reads do not measure allocator bytes. |
| Design | [docs/tuple_arenas.md](../../../../tuple_arenas.md), [docs/decisions/0012-generational-arena.md](../../../../decisions/0012-generational-arena.md), [Refactor.md §11.4 S03](../../../../../Refactor.md) |

## B0007

[Lines 39–39](../../../../../src/storage/arena.cpp#L39); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
explicit State(TupleLayout value)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Finish construction of a shared arena State only for a valid layout handle. |
| inputs / outputs | Moves an incoming layout and validates its presence by id(). |
| invariants | Owner member acquisition occurs before the body; a failed layout check does not recycle that unpublished owner ID. |
| ownership | The shared State retains the layout token for every stored slot and future pin. |
| failure | Moved-from layout rejects with invalid_layout; shared construction unwinds members without publishing an arena. |
| cost | Constant handle move/check after owner acquisition and surrounding shared allocation. |
| Design | [docs/tuple_arenas.md](../../../../tuple_arenas.md), [docs/decisions/0012-generational-arena.md](../../../../decisions/0012-generational-arena.md), [Refactor.md §11.4 S03](../../../../../Refactor.md) |

## B0008

[Lines 40–42](../../../../../src/storage/arena.cpp#L40); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
State(const State&) = delete;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Prevent accidental duplication of an arena ownership authority. |
| inputs / outputs | Deleted copy constructor/assignment force State use through the one shared owner rather than copying owner IDs/lists. |
| invariants | Sharing a State via pins differs from copying its mutable metadata; slots/list identity is unique. |
| ownership | Compile-time restriction; moves of public facades transfer a shared pointer instead. |
| failure | Attempts to copy State fail compilation, not at runtime. |
| cost | No runtime checks or allocation. |
| Design | [docs/tuple_arenas.md](../../../../tuple_arenas.md), [docs/decisions/0012-generational-arena.md](../../../../decisions/0012-generational-arena.md), [Refactor.md §11.4 S03](../../../../../Refactor.md) |

## B0009

[Lines 43–45](../../../../../src/storage/arena.cpp#L43); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void owned(ArenaHandle handle) const
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Check that an untrusted allocation handle names this arena owner before slot access. |
| inputs / outputs | ArenaHandle in; returns if its owner ID matches this State. |
| invariants | Foreign ownership is rejected even when slot/generation happen to be numerically plausible. |
| ownership | Borrows the handle and State; no pin or owner is acquired. |
| failure | Foreign owner throws foreign_handle before any slot dereference. |
| cost | Constant scalar identity comparison; owning diagnostic cost only on failure. |
| Design | [docs/tuple_arenas.md](../../../../tuple_arenas.md), [docs/decisions/0012-generational-arena.md](../../../../decisions/0012-generational-arena.md), [Refactor.md §11.4 S03](../../../../../Refactor.md) |

## B0010

[Lines 46–50](../../../../../src/storage/arena.cpp#L46); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
bool contains(ArenaHandle handle) const
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Test live allocation membership with exact owner, slot and generation identity. |
| inputs / outputs | First validates owner; then checks slot bounds, live flag and matching generation. |
| invariants | Retired/free/exhausted or wrong-generation handles are absent; the short-circuit bound check precedes slot access. |
| ownership | Reads one stable Slot without retaining its payload. |
| failure | Foreign owner throws foreign_handle; a stale same-owner handle returns false. |
| cost | Constant lookup and scalar tests, independent of high-water slot count; no success-path allocation. |
| Design | [docs/tuple_arenas.md](../../../../tuple_arenas.md), [docs/decisions/0012-generational-arena.md](../../../../decisions/0012-generational-arena.md), [Refactor.md §11.4 S03](../../../../../Refactor.md) |

## B0011

[Lines 51–54](../../../../../src/storage/arena.cpp#L51); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Slot& live(ArenaHandle handle) const
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Resolve a validated live handle for get/pin operations. |
| inputs / outputs | Uses contains() and returns the corresponding mutable Slot reference. |
| invariants | Only live current-generation handles pass; const facade access does not imply concurrent access safety. |
| ownership | Borrows internal slot metadata; callers must keep State alive and obey serialized access. |
| failure | Foreign_handle propagates from contains; stale same-owner handle throws stale_handle. |
| cost | Constant checked resolution; no allocation on success. |
| Design | [docs/tuple_arenas.md](../../../../tuple_arenas.md), [docs/decisions/0012-generational-arena.md](../../../../decisions/0012-generational-arena.md), [Refactor.md §11.4 S03](../../../../../Refactor.md) |

## B0012

[Lines 55–62](../../../../../src/storage/arena.cpp#L55); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void link_live(std::size_t position, Slot& slot) noexcept
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Publish a privately prepared or retained slot at the live-list head. |
| inputs / outputs | Valid position/Slot in; sets live links/head and increments live_records. |
| invariants | Caller has prepared payload and removed any free/retired classification; prior head back-link stays consistent. |
| ownership | Uses existing slot/directory storage only; it does not allocate or copy tuple data. |
| failure | Noexcept private operation; position/payload/list consistency are caller-established preconditions. |
| cost | Constant intrusive-link/counter work with no list scan. |
| Design | [docs/tuple_arenas.md](../../../../tuple_arenas.md), [docs/decisions/0012-generational-arena.md](../../../../decisions/0012-generational-arena.md), [Refactor.md §11.4 S03](../../../../../Refactor.md) |

## B0013

[Lines 63–72](../../../../../src/storage/arena.cpp#L63); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void reclaim(std::size_t position, Slot& slot) noexcept
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Destroy an unneeded erased payload and classify its retained metadata as free or exhausted. |
| inputs / outputs | An erased slot with no remaining pins in; clears optional tuple and links reusable metadata to free_head unless generation is terminal. |
| invariants | Terminal generations never enter the free list; other slots keep their generation until successful reuse. |
| ownership | Payload ownership releases here; Slot/directory metadata stays allocated until State teardown. |
| failure | Noexcept and no new allocation under valid owner/destructor contracts. |
| cost | Constant link/counter work plus representation/last-owner payload destruction; freeing payload is not evidence of shrinking high-water metadata. |
| Design | [docs/tuple_arenas.md](../../../../tuple_arenas.md), [docs/decisions/0012-generational-arena.md](../../../../decisions/0012-generational-arena.md), [Refactor.md §11.4 S03](../../../../../Refactor.md) |

## B0014

[Lines 73–82](../../../../../src/storage/arena.cpp#L73); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void erase(std::size_t position, Slot& slot) noexcept
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Remove one known live allocation from membership before retiring or reclaiming its payload. |
| inputs / outputs | Unlinks both neighboring live links, marks not live, decrements live_records, then retains pinned payload or reclaims unpinned payload. |
| invariants | An erased pinned allocation remains readable only through existing pins and cannot be reused; ordinary membership ends immediately. |
| ownership | Keeps retained payload for pins or releases it through reclaim; no new owner/container allocation. |
| failure | Noexcept private mutation requires a currently live slot and consistent lists. |
| cost | Constant bookkeeping plus possible payload-release cost; no scan of unrelated slots. |
| Design | [docs/tuple_arenas.md](../../../../tuple_arenas.md), [docs/decisions/0012-generational-arena.md](../../../../decisions/0012-generational-arena.md), [Refactor.md §11.4 S03](../../../../../Refactor.md) |

## B0015

[Lines 83–85](../../../../../src/storage/arena.cpp#L83); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void clear() noexcept
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Retire or reclaim every currently live allocation without visiting free high-water history. |
| inputs / outputs | Repeatedly erases live_head until the live list is empty. |
| invariants | All ordinary handles become stale; pins retain only their erased payloads, not membership. |
| ownership | Keeps slot-directory/Slot metadata; unpinned payloads release, pinned payloads survive. |
| failure | Noexcept and no new allocation; valid list/owner invariants are private preconditions. |
| cost | O(current live records) link work plus each released payload teardown, independent of unrelated free-slot history. |
| Design | [docs/tuple_arenas.md](../../../../tuple_arenas.md), [docs/decisions/0012-generational-arena.md](../../../../decisions/0012-generational-arena.md), [Refactor.md §11.4 S03](../../../../../Refactor.md) |

## B0016

[Lines 86–94](../../../../../src/storage/arena.cpp#L86); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void unpin(ArenaHandle handle) noexcept
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Release one existing pin and reclaim an erased allocation when its final pin leaves. |
| inputs / outputs | Private valid pin handle in; decrements per-slot/total pins and, if retired count reaches zero, decrements retained_records and reclaims. |
| invariants | Pins prevent slot reuse, so this internal handle still names its original generation/payload. A live final-unpin leaves membership unchanged. |
| ownership | Releases payload only on last retired pin; the caller later releases its separate shared State reference. |
| failure | Noexcept with factory-established pin/counter preconditions; no repeated public owner/generation error path. |
| cost | Constant bookkeeping plus possible one-payload release; later shared State destruction in Pin::reset has a separate high-water cost. |
| Design | [docs/tuple_arenas.md](../../../../tuple_arenas.md), [docs/decisions/0012-generational-arena.md](../../../../decisions/0012-generational-arena.md), [Refactor.md §11.4 S03](../../../../../Refactor.md) |

## B0017

[Lines 95–96](../../../../../src/storage/arena.cpp#L95); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L95-L96:sha256:cdbb10f75f6890449819c9d57e5ae7b786fb73c5111c5d829c37bc18f3e053e8
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Close the \`struct TupleArena::State\` scope at this exact source boundary. |
| inputs / outputs | This token introduces no callable inputs or outputs. Declarations inside \`struct TupleArena::State\` define the available names, members and operations. |
| invariants | The closing brace matches the opening \`struct TupleArena::State\` at its lexical source position in src/storage/arena.cpp; it preserves C++ namespace/type nesting. |
| ownership | The closing delimiter creates no owner. Types closed by \`struct TupleArena::State\` retain the lifetimes and allocator rules of their own fields and operations. |
| failure | No failure path executes at this closing delimiter. Failure and cleanup behavior belong to enclosed functions and owning types. |
| cost | The delimiter itself performs no runtime work; the enclosed initializers, methods and destructors carry their own costs. |
| Design | [docs/storage.md](../../../../storage.md), [docs/tuple_arenas.md](../../../../tuple_arenas.md), [docs/query_memory.md](../../../../query_memory.md), [docs/code_specs/subsystem_contracts.md](../../../subsystem_contracts.md) |

## B0018

[Lines 97–97](../../../../../src/storage/arena.cpp#L97); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
TupleArena::TupleArena(TupleLayout layout)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Create a noncopyable arena facade with one fresh shared State. |
| inputs / outputs | Valid layout handle in; make_shared constructs unique owner identity and empty lists/counters. |
| invariants | Every future payload must use the same exact layout token; this creates no SQL or byte-budget admission. |
| ownership | Facade owns State; future pins may share it. Standard metadata allocation is distinct from AccountedTupleArena. |
| failure | Shared allocation, owner exhaustion or invalid layout can throw before a completed facade exists. |
| cost | One standard shared allocation plus cold owner-ID acquisition and constant layout setup. |
| Design | [docs/tuple_arenas.md](../../../../tuple_arenas.md), [docs/decisions/0012-generational-arena.md](../../../../decisions/0012-generational-arena.md), [Refactor.md §11.4 S03](../../../../../Refactor.md) |

## B0019

[Lines 98–98](../../../../../src/storage/arena.cpp#L98); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
TupleArena::~TupleArena()
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Close a live arena facade by invalidating all of its remaining live memberships. |
| inputs / outputs | If state_ exists, clears its current live list before member shared ownership is released. |
| invariants | Moved-from destruction is harmless; surviving pins retain erased payloads but no live membership. |
| ownership | Last State release also destroys its high-water slot metadata and layout; otherwise pins defer that cost. |
| failure | No new allocation or throwing cleanup under valid invariants/destructors. |
| cost | O(live rows) retirement plus payload releases, and O(total slots) metadata teardown only when this is the final State owner. |
| Design | [docs/tuple_arenas.md](../../../../tuple_arenas.md), [docs/decisions/0012-generational-arena.md](../../../../decisions/0012-generational-arena.md), [Refactor.md §11.4 S03](../../../../../Refactor.md) |

## B0020

[Lines 99–99](../../../../../src/storage/arena.cpp#L99); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
TupleArena::TupleArena(TupleArena&&) noexcept = default;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Transfer an arena facade without rebuilding slots or changing owner identity. |
| inputs / outputs | Default move transfers state_ to the destination, leaving the source empty. |
| invariants | Existing handles, pins and slot addresses still name the transferred State. |
| ownership | Shared State ownership moves; no new State/owner ID is created. |
| failure | Noexcept; later ordinary use of the empty source reports invalid_arena. |
| cost | Constant pointer transfer with no allocation or tuple scan. |
| Design | [docs/tuple_arenas.md](../../../../tuple_arenas.md), [docs/decisions/0012-generational-arena.md](../../../../decisions/0012-generational-arena.md), [Refactor.md §11.4 S03](../../../../../Refactor.md) |

## B0021

[Lines 100–106](../../../../../src/storage/arena.cpp#L100); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
TupleArena& TupleArena::operator=(TupleArena&& other) noexcept
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Replace an arena facade while closing its previous memberships and preserving incoming identities. |
| inputs / outputs | Non-self assignment clears prior live rows then moves other.state_; self-move leaves the arena unchanged. |
| invariants | Old pins observe retired old rows; incoming handles retain their original owner/slot/generation. |
| ownership | Old State may survive through pins or be destroyed; incoming State ownership transfers without reallocation. |
| failure | Noexcept and no allocating rollback path under valid cleanup contracts. |
| cost | O(old live rows) clear plus possible O(old total slots) final metadata destruction; incoming pointer transfer is constant. |
| Design | [docs/tuple_arenas.md](../../../../tuple_arenas.md), [docs/decisions/0012-generational-arena.md](../../../../decisions/0012-generational-arena.md), [Refactor.md §11.4 S03](../../../../../Refactor.md) |

## B0022

[Lines 107–110](../../../../../src/storage/arena.cpp#L107); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
TupleArena::State& TupleArena::state() const
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Resolve the facade shared State and reject moved-from use. |
| inputs / outputs | Returns a State reference if state_ is nonempty. |
| invariants | The mutable reference behind const supports pin counters; all operations still require serialized external access. |
| ownership | Borrows the State without incrementing its shared count. |
| failure | Empty facade throws invalid_arena. |
| cost | Constant pointer test/reference return; no success-path allocation. |
| Design | [docs/tuple_arenas.md](../../../../tuple_arenas.md), [docs/decisions/0012-generational-arena.md](../../../../decisions/0012-generational-arena.md), [Refactor.md §11.4 S03](../../../../../Refactor.md) |

## B0023

[Lines 111–111](../../../../../src/storage/arena.cpp#L111); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
ArenaOwnerId TupleArena::owner() const
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Expose the arena allocation-owner identity. |
| inputs / outputs | Returns State owner through checked state(). |
| invariants | Owner ID is separate from logical table/storage IDs and never changes when the facade moves. |
| ownership | Scalar copy only; no extra State retention. |
| failure | Moved-from facade rejects with invalid_arena. |
| cost | Constant checked scalar read. |
| Design | [docs/tuple_arenas.md](../../../../tuple_arenas.md), [docs/decisions/0012-generational-arena.md](../../../../decisions/0012-generational-arena.md), [Refactor.md §11.4 S03](../../../../../Refactor.md) |

## B0024

[Lines 112–112](../../../../../src/storage/arena.cpp#L112); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
const TupleLayout& TupleArena::layout() const
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Borrow the one exact layout token required by all arena payloads. |
| inputs / outputs | Returns the State layout reference after state() validation. |
| invariants | Keep the arena State alive through an owner/pin while using this borrowed reference. |
| ownership | No layout copy or new token/control block is made. |
| failure | Moved-from facade rejects with invalid_arena. |
| cost | Constant checked reference access. |
| Design | [docs/tuple_arenas.md](../../../../tuple_arenas.md), [docs/decisions/0012-generational-arena.md](../../../../decisions/0012-generational-arena.md), [Refactor.md §11.4 S03](../../../../../Refactor.md) |

## B0025

[Lines 113–113](../../../../../src/storage/arena.cpp#L113); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
ArenaStatistics TupleArena::statistics() const
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Snapshot current slot/member/pin classification counts. |
| inputs / outputs | Returns State ArenaStatistics by value after presence validation. |
| invariants | Counts are logical records/slots/pins, not allocated bytes, vector capacity or historical allocator calls. |
| ownership | Fixed counter copy; no scan or new retained owner. |
| failure | Moved-from facade rejects with invalid_arena. |
| cost | Constant counter read, independent of slot count. |
| Design | [docs/tuple_arenas.md](../../../../tuple_arenas.md), [docs/decisions/0012-generational-arena.md](../../../../decisions/0012-generational-arena.md), [Refactor.md §11.4 S03](../../../../../Refactor.md) |

## B0027

[Lines 115–142](../../../../../src/storage/arena.cpp#L115); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
ArenaHandle TupleArena::insert(const Tuple& tuple)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Publish one owned allocation only after its tuple copy and any directory growth succeed. |
| inputs / outputs | Requires matching layout token. Reuses free_head by copying first then advancing generation, or allocates a new stable Slot before appending its unique_ptr. |
| invariants | No slot, generation, live/free counter or published handle changes on allocation failure; exhausted generations are never in the reusable list. |
| ownership | Arena retains a Tuple copy; legacy payloads deep-copy, native payloads share existing immutable owners. New Slot/directory metadata uses standard allocation. |
| failure | Layout mismatch/capacity exhaustion rejects before publication; tuple/Slot/vector allocation failures unwind private work with the old arena intact. |
| cost | Representation-specific tuple copy; free reuse has constant bookkeeping, fresh append has one Slot allocation and amortized pointer-vector growth, worst-case O(total slots) pointer moves. |
| Design | [docs/tuple_arenas.md](../../../../tuple_arenas.md), [docs/decisions/0012-generational-arena.md](../../../../decisions/0012-generational-arena.md), [Refactor.md §11.4 S03](../../../../../Refactor.md) |

## B0028

[Lines 143–143](../../../../../src/storage/arena.cpp#L143); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
bool TupleArena::contains(ArenaHandle handle) const
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Expose exact live arena allocation membership. |
| inputs / outputs | Resolves State then delegates owner/bounds/live/generation checks. |
| invariants | An existing pin does not make an erased row live; logical table identities are not accepted as arena handles. |
| ownership | No pin/payload retention is acquired. |
| failure | Moved-from facade or foreign owner throws; stale same-owner handle returns false. |
| cost | Constant checked membership read; no allocation on success. |
| Design | [docs/tuple_arenas.md](../../../../tuple_arenas.md), [docs/decisions/0012-generational-arena.md](../../../../decisions/0012-generational-arena.md), [Refactor.md §11.4 S03](../../../../../Refactor.md) |

## B0029

[Lines 144–144](../../../../../src/storage/arena.cpp#L144); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
const Tuple& TupleArena::get(ArenaHandle handle) const
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Borrow a live tuple by its current exact arena handle. |
| inputs / outputs | Resolves State/live Slot and dereferences its engaged payload. |
| invariants | Ordinary borrowed access ends on erase, clear, facade destruction/replacement unless the caller separately retains the payload through a pin. |
| ownership | Returns a reference to stable Slot storage without copying or pinning. |
| failure | Moved-from/foreign/stale handles reject through state()/live() before dereference. |
| cost | Constant checked lookup and reference access; no scalar export or allocation. |
| Design | [docs/tuple_arenas.md](../../../../tuple_arenas.md), [docs/decisions/0012-generational-arena.md](../../../../decisions/0012-generational-arena.md), [Refactor.md §11.4 S03](../../../../../Refactor.md) |

## B0030

[Lines 145–152](../../../../../src/storage/arena.cpp#L145); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
TupleArena::Pin TupleArena::pin(ArenaHandle handle) const
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Acquire explicit immutable payload retention for one currently live allocation. |
| inputs / outputs | Checks owner/generation/liveness, admits per-slot/total pin-count increments, then returns a private Pin sharing State. |
| invariants | Cannot newly pin an erased row; counter admission precedes the nonthrowing Pin construction. A pin does not preserve membership or cursor validity. |
| ownership | The Pin retains State/slot payload without copying Tuple fields or allocating its own control block. |
| failure | Bad handles reject; size_t pin-count exhaustion throws storage_overflow before any counter increment. |
| cost | Constant lookup/counter/shared-handle work; caller containers storing returned pins may allocate separately. |
| Design | [docs/tuple_arenas.md](../../../../tuple_arenas.md), [docs/decisions/0012-generational-arena.md](../../../../decisions/0012-generational-arena.md), [Refactor.md §11.4 S03](../../../../../Refactor.md) |

## B0031

[Lines 153–158](../../../../../src/storage/arena.cpp#L153); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
bool TupleArena::erase(ArenaHandle handle)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Erase live membership or treat an already stale same-owner handle as absent. |
| inputs / outputs | Checks State and owner; returns false if not live/current, otherwise retires/reclaims the known Slot and returns true. |
| invariants | Committed erase never makes a public handle reusable with the same generation; private journal revive is a separate undo-only operation. |
| ownership | Pinned payload survives; unpinned payload releases; all Slot metadata remains. |
| failure | Foreign/moved-from handles reject before mutation; successful erase has no new allocation. |
| cost | Constant membership/link work plus possible payload teardown; no unrelated-slot scan. |
| Design | [docs/tuple_arenas.md](../../../../tuple_arenas.md), [docs/decisions/0012-generational-arena.md](../../../../decisions/0012-generational-arena.md), [Refactor.md §11.4 S03](../../../../../Refactor.md) |

## B0032

[Lines 159–159](../../../../../src/storage/arena.cpp#L159); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void TupleArena::clear()
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Expose complete live-membership removal while retaining high-water metadata and pinned values. |
| inputs / outputs | Checked State in; delegates its intrusive live-list clear. |
| invariants | Every prior ordinary live handle becomes stale; free/exhausted history is not traversed or reset. |
| ownership | Pins keep only their own payloads and State alive after clear. |
| failure | Moved-from facade throws invalid_arena; valid cleanup allocates nothing. |
| cost | O(current live records) plus payload-release costs, not a scan of all historical slots. |
| Design | [docs/tuple_arenas.md](../../../../tuple_arenas.md), [docs/decisions/0012-generational-arena.md](../../../../decisions/0012-generational-arena.md), [Refactor.md §11.4 S03](../../../../../Refactor.md) |

## B0033

[Lines 160–166](../../../../../src/storage/arena.cpp#L160); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void TupleArena::revive(const Pin& pin) noexcept
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Restore an uncommitted erased allocation using its retained exact pin for table-journal undo. |
| inputs / outputs | Requires same State, valid slot, erased membership, positive pins, matching generation and retained payload; decrements retired count then links live. |
| invariants | Original address/generation/payload is restored without a new public allocation. This private friend API is not general stale-handle resurrection. |
| ownership | Uses the journal-held Pin retention and existing Slot/list storage. |
| failure | A violated private undo precondition terminates; valid rollback has no throwing or allocation path. |
| cost | Constant validation/link/counter work, no tuple copy or allocation. |
| Design | [docs/tuple_arenas.md](../../../../tuple_arenas.md), [docs/decisions/0012-generational-arena.md](../../../../decisions/0012-generational-arena.md), [Refactor.md §11.4 S03](../../../../../Refactor.md), [docs/storage_journal.md](../../../../storage_journal.md) |

## B0035

[Lines 168–169](../../../../../src/storage/arena.cpp#L168); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
TupleArena::Pin::Pin(std::shared_ptr<State> state, ArenaHandle handle) noexcept
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Adopt already-admitted pin ownership and exact allocation identity. |
| inputs / outputs | Private constructor receives retained State and handle after pin counts were incremented. |
| invariants | Caller has established a live original generation and balanced counters; construction itself does not increment them again. |
| ownership | Moves the existing shared State handle and copies scalar identity. |
| failure | Noexcept; only arena factories may establish this private invariant. |
| cost | Constant owner transfer, no allocation or payload copy. |
| Design | [docs/tuple_arenas.md](../../../../tuple_arenas.md), [docs/decisions/0012-generational-arena.md](../../../../decisions/0012-generational-arena.md), [Refactor.md §11.4 S03](../../../../../Refactor.md) |

## B0036

[Lines 170–170](../../../../../src/storage/arena.cpp#L170); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
TupleArena::Pin::Pin(Pin&&) noexcept = default;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Move one pin obligation without changing pin counters or allocation identity. |
| inputs / outputs | Default move transfers shared State and copies its scalar handle; the source shared owner becomes empty. |
| invariants | Only the destination will later unpin; a moved-from destructor must not decrement counters. |
| ownership | Transfers one retention obligation without constructing another control block. |
| failure | Noexcept and no runtime admission. |
| cost | Constant moves, no allocation or payload scan. |
| Design | [docs/tuple_arenas.md](../../../../tuple_arenas.md), [docs/decisions/0012-generational-arena.md](../../../../decisions/0012-generational-arena.md), [Refactor.md §11.4 S03](../../../../../Refactor.md) |

## B0037

[Lines 171–174](../../../../../src/storage/arena.cpp#L171); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
TupleArena::Pin& TupleArena::Pin::operator=(Pin&& other) noexcept
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Move-replace a pin after releasing any destination retention. |
| inputs / outputs | Non-self assignment resets this pin, moves other.state_ and copies its handle; self-move leaves retention unchanged. |
| invariants | Exactly one decrement for the old obligation and one surviving obligation for the incoming pin; source becomes empty. |
| ownership | Old last retention may release its payload and final State; incoming State transfers without copying payload. |
| failure | Noexcept under valid destructor/counter invariants. |
| cost | Constant transfer plus reset cost, potentially O(total old slots) if it releases the final closed State. |
| Design | [docs/tuple_arenas.md](../../../../tuple_arenas.md), [docs/decisions/0012-generational-arena.md](../../../../decisions/0012-generational-arena.md), [Refactor.md §11.4 S03](../../../../../Refactor.md) |

## B0038

[Lines 175–175](../../../../../src/storage/arena.cpp#L175); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
TupleArena::Pin::~Pin()
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Balance the pin obligation automatically at scope exit. |
| inputs / outputs | Delegates to reset(), harmless for empty or moved-from pins. |
| invariants | Live membership is not erased by pin destruction; last retired pin triggers reclaim. |
| ownership | May release the final payload and shared State, including all high-water metadata. |
| failure | No allocating or throwing cleanup under valid private invariants. |
| cost | Constant pin bookkeeping plus payload release and possible O(total slots) final State teardown. |
| Design | [docs/tuple_arenas.md](../../../../tuple_arenas.md), [docs/decisions/0012-generational-arena.md](../../../../decisions/0012-generational-arena.md), [Refactor.md §11.4 S03](../../../../../Refactor.md) |

## B0039

[Lines 176–177](../../../../../src/storage/arena.cpp#L176); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
// Pin bookkeeping is constant;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Separate pin counter work from the final closed-State destruction cost. |
| inputs / outputs | The note describes the reset boundary and its possible last shared State release. |
| invariants | Only slot bookkeeping is constant; high-water metadata can outlive the facade through pins. |
| ownership | No new retention is added; the existing State shared owner determines deferred teardown. |
| failure | No runtime check or throwing cleanup is introduced. |
| cost | No runtime work from the comment; final teardown may visit all retained slot metadata. |
| Design | [docs/tuple_arenas.md](../../../../tuple_arenas.md) |

## B0040

[Lines 178–180](../../../../../src/storage/arena.cpp#L178); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void TupleArena::Pin::reset() noexcept
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Release one retention obligation and make the pin empty. |
| inputs / outputs | For nonempty State, calls unpin(handle_) then releases state_; empty reset is a no-op. |
| invariants | The State stays alive through unpin. A retired final pin reclaims its payload before the last shared State reference can disappear. |
| ownership | Releases the owned retention and potentially final high-water metadata/layout backing. |
| failure | Noexcept; no new allocation or public error conversion. |
| cost | Constant counter/list work plus payload teardown; final closed-State release can destroy O(total slots) metadata. |
| Design | [docs/tuple_arenas.md](../../../../tuple_arenas.md), [docs/decisions/0012-generational-arena.md](../../../../decisions/0012-generational-arena.md), [Refactor.md §11.4 S03](../../../../../Refactor.md) |

## B0041

[Lines 181–184](../../../../../src/storage/arena.cpp#L181); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
ArenaHandle TupleArena::Pin::handle() const
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Read the exact allocation identity retained by a nonempty pin. |
| inputs / outputs | Returns stored owner/slot/generation after checking state_ presence. |
| invariants | A returned handle may already be erased; identity access does not assert current membership. |
| ownership | Returns scalar values only, without creating a second pin. |
| failure | Empty or moved-from pin throws invalid_pin. |
| cost | Constant checked scalar copy, no allocation on success. |
| Design | [docs/tuple_arenas.md](../../../../tuple_arenas.md), [docs/decisions/0012-generational-arena.md](../../../../decisions/0012-generational-arena.md), [Refactor.md §11.4 S03](../../../../../Refactor.md) |

## B0042

[Lines 185–188](../../../../../src/storage/arena.cpp#L185); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
const Tuple& TupleArena::Pin::get() const
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Borrow the retained immutable tuple even when its membership has ended. |
| inputs / outputs | Checks nonempty pin through handle(), then resolves its retained Slot payload. |
| invariants | Pins prevent reuse/reclaim of that allocation, so no repeated live/generation lookup is required; get remains usable after owner close/erase. |
| ownership | Returns a reference backed by this Pin State retention; it expires after the final relevant payload owner is released. |
| failure | Empty pin rejects with invalid_pin; private balanced-pin invariants guarantee payload presence. |
| cost | Constant direct slot/reference access without tuple copy or allocation. |
| Design | [docs/tuple_arenas.md](../../../../tuple_arenas.md), [docs/decisions/0012-generational-arena.md](../../../../decisions/0012-generational-arena.md), [Refactor.md §11.4 S03](../../../../../Refactor.md) |

## B0043

[Lines 189–192](../../../../../src/storage/arena.cpp#L189); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
bool TupleArena::Pin::is_live() const
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Distinguish retained payload access from current arena membership. |
| inputs / outputs | Checks a nonempty Pin, then asks State::contains for its stored handle. |
| invariants | Erased retained payload reports false; private tentative journal undo can restore membership with the same retained generation. |
| ownership | No new pin or ownership is acquired. |
| failure | Empty/moved-from Pin throws invalid_pin; valid private pins retain their correct owner. |
| cost | Constant owner/bounds/generation/live checks, no scan or allocation. |
| Design | [docs/tuple_arenas.md](../../../../tuple_arenas.md), [docs/decisions/0012-generational-arena.md](../../../../decisions/0012-generational-arena.md), [Refactor.md §11.4 S03](../../../../../Refactor.md) |

## B0044

[Lines 193–195](../../../../../src/storage/arena.cpp#L193); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
// Explicit diagnostic: scans all high-water slots
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Label full invariant recomputation as an explicit diagnostic cost. |
| inputs / outputs | The note identifies the two visited arrays, high-water scan and retained tuple checks below. |
| invariants | This is a description of the existing diagnostic, not extra mutation-path validation. |
| ownership | No new owner, journal or scratch is installed by this comment. |
| failure | No executable failure behavior changes. |
| cost | No runtime work from the comment; the called diagnostic has size-dependent allocation/scan/validation costs. |
| Design | [docs/tuple_arenas.md](../../../../tuple_arenas.md) |

## B0045

[Lines 196–235](../../../../../src/storage/arena.cpp#L196); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void TupleArena::check_invariants() const
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Explicitly recompute the arena slot partition, linked lists, counters and stored tuple validity. |
| inputs / outputs | Uses two high-water-size visited bit vectors, walks free/live lists, validates each Slot and compares reconstructed ArenaStatistics. |
| invariants | Checks no cycles/duplicates, exact back-links, nonzero generations, retained/free/exhausted payload rules, matching layout tokens and valid tuple values. Assumes valid C++ slot objects, not arbitrary memory-corruption safety. |
| ownership | Borrows State/payloads; temporary vectors are ordinary diagnostic storage and are released on return/failure. |
| failure | Bad facade/invariant/value/domain or temporary allocation rejects; no arena membership/counter mutation is performed. |
| cost | O(total slots plus all stored tuple/equality/value validation costs), two O(total slots) bit arrays; legacy decimal validation may render/allocate. This is not automatic insert/erase work. |
| Design | [docs/tuple_arenas.md](../../../../tuple_arenas.md), [docs/decisions/0012-generational-arena.md](../../../../decisions/0012-generational-arena.md), [Refactor.md §11.4 S03](../../../../../Refactor.md) |

## B0046

[Lines 236–236](../../../../../src/storage/arena.cpp#L236); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L236-L236:sha256:a925daf8c493848e231ff86cf03ec96eebbfe0f1e72bb404adf6ae3a25cd1b86
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Close the \`namespace crown::storage\` scope at this exact source boundary. |
| inputs / outputs | This token introduces no callable inputs or outputs. Declarations inside \`namespace crown::storage\` define the available names, members and operations. |
| invariants | The closing brace matches the opening \`namespace crown::storage\` at its lexical source position in src/storage/arena.cpp; it preserves C++ namespace/type nesting. |
| ownership | The closing delimiter creates no owner. Types closed by \`namespace crown::storage\` retain the lifetimes and allocator rules of their own fields and operations. |
| failure | No failure path executes at this closing delimiter. Failure and cleanup behavior belong to enclosed functions and owning types. |
| cost | The delimiter itself performs no runtime work; the enclosed initializers, methods and destructors carry their own costs. |
| Design | [docs/storage.md](../../../../storage.md), [docs/tuple_arenas.md](../../../../tuple_arenas.md), [docs/query_memory.md](../../../../query_memory.md), [docs/code_specs/subsystem_contracts.md](../../../subsystem_contracts.md) |
