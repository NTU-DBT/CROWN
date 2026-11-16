# `src/storage/accounted_arena.cpp` — block usage map

[Source](../../../../../src/storage/accounted_arena.cpp) · [Source index](../../../README.md) · [Subsystem contracts](../../../subsystem_contracts.md) · [Reviewed primitives](../../../primitives.md)

Keep stable tuple handles and retained deleted payloads for live readers and inverse operations.

Snapshot SHA-256: `8004f85fd013e2be50bb458e6c23e9cf08408680eb06730e212520185ae2975b`. 296 lines partitioned into 54 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [arena](../../../subsystem_contracts.md#arena). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/tuple_arenas.md](../../../../tuple_arenas.md), [docs/storage_journal.md](../../../../storage_journal.md), [docs/query_memory.md](../../../../query_memory.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–14](../../../../../src/storage/accounted_arena.cpp#L1) | Imports dependencies; declares namespace scope; declares callable signatures; declares values/defaults or compile-time conditions. |  · [reviewed contract](#b0001) |
| [B0002 · 15–17](../../../../../src/storage/accounted_arena.cpp#L15) | Callable definition: void require(bool value, ArenaProblem issue = ArenaProblem::invariant) | calls ArenaValidationFailure; guard void require(bool value, ArenaProblem issue = ArenaProblem::invariant) { · [reviewed contract](#b0002) |
| [B0003 · 18–23](../../../../../src/storage/accounted_arena.cpp#L18) | Callable definition: void add(resource::MemoryUsage& to, resource::MemoryUsage value) noexcept | calls ; source comment (unverified): // Disjoint actual blocks of this account; their sum is already admitted. · [reviewed contract](#b0003) |
| [B0004 · 24–25](../../../../../src/storage/accounted_arena.cpp#L24) | Closes surrounding scope/type. |  · [reviewed contract](#b0004) |
| [B0005 · 26–36](../../../../../src/storage/accounted_arena.cpp#L26) | Callable definition: std::string_view ArenaValidationFailure::code() const noexcept | calls ; returns @; @ · [reviewed contract](#b0005) |
| [B0006 · 37–47](../../../../../src/storage/accounted_arena.cpp#L37) | Callable definition: const char* ArenaValidationFailure::what() const noexcept | calls ; returns @; @ · [reviewed contract](#b0006) |
| [B0007 · 48–49](../../../../../src/storage/accounted_arena.cpp#L48) | declares types or opens a type body. |  · [reviewed contract](#b0007) |
| [B0008 · 50–57](../../../../../src/storage/accounted_arena.cpp#L50) | Type/record definition: struct Slot |  · [reviewed contract](#b0008) |
| [B0009 · 58–59](../../../../../src/storage/accounted_arena.cpp#L58) | Explanatory comments or spacing. | source comment (unverified): // A slot's address never moves. Only this block handle moves during directory · [reviewed contract](#b0009) |
| [B0010 · 60–78](../../../../../src/storage/accounted_arena.cpp#L60) | Type/record definition: struct SlotOwner | returns *this; static_cast&lt;Slot*&gt;(block.data()); source comment (unverified): // A slot's address never moves. Only this block handle moves during directory · [reviewed contract](#b0010) |
| [B0011 · 79–86](../../../../../src/storage/accounted_arena.cpp#L79) | declares callable signatures; declares values/defaults or compile-time conditions. | guard static_assert(std::is_nothrow_move_constructible_v&lt;SlotOwner&gt;); · [reviewed contract](#b0011) |
| [B0012 · 87–90](../../../../../src/storage/accounted_arena.cpp#L87) | Callable definition: State(resource::MemoryAccount value, AccountedLayout descriptor, ArenaOwnerId id) noexcept : account(std::move(value)), layout(st… | calls account, std::move, layout, owner · [reviewed contract](#b0012) |
| [B0013 · 91–92](../../../../../src/storage/accounted_arena.cpp#L91) | declares callable signatures; declares values/defaults or compile-time conditions. |  · [reviewed contract](#b0013) |
| [B0014 · 93–95](../../../../../src/storage/accounted_arena.cpp#L93) | Callable definition: void owned(ArenaHandle handle) const | calls require; guard require(handle.owner == owner, ArenaProblem::foreign_handle); · [reviewed contract](#b0014) |
| [B0015 · 96–100](../../../../../src/storage/accounted_arena.cpp#L96) | Callable definition: \[\[nodiscard\]\] bool contains(ArenaHandle handle) const | calls owned, size; returns handle.slot.value &lt; slots.size() && slots\[handle.slot.value\]-&gt;live && · [reviewed contract](#b0015) |
| [B0016 · 101–104](../../../../../src/storage/accounted_arena.cpp#L101) | Callable definition: \[\[nodiscard\]\] Slot& live(ArenaHandle handle) | calls require, contains; guard require(contains(handle), ArenaProblem::stale_handle);; returns *slots\[handle.slot.value\] · [reviewed contract](#b0016) |
| [B0017 · 105–108](../../../../../src/storage/accounted_arena.cpp#L105) | Callable definition: void classify_slot(std::size_t position, resource::AllocationLifetime lifetime) noexcept | calls set_lifetime, AccountedTupleArena::classify · [reviewed contract](#b0017) |
| [B0018 · 109–114](../../../../../src/storage/accounted_arena.cpp#L109) | Callable definition: void link_live(std::size_t position, Slot& slot) noexcept | calls classify_slot · [reviewed contract](#b0018) |
| [B0019 · 115–125](../../../../../src/storage/accounted_arena.cpp#L115) | Callable definition: void reclaim(std::size_t position, Slot& slot) noexcept | calls reset, set_lifetime; source comment (unverified): // Exhausted metadata is reserved but cannot rejoin the reusable pool. · [reviewed contract](#b0019) |
| [B0020 · 126–134](../../../../../src/storage/accounted_arena.cpp#L126) | Callable definition: void erase(std::size_t position, Slot& slot) noexcept | calls classify_slot, reclaim · [reviewed contract](#b0020) |
| [B0021 · 135–137](../../../../../src/storage/accounted_arena.cpp#L135) | Callable definition: void clear() noexcept | calls erase; 1 loop sites · [reviewed contract](#b0021) |
| [B0022 · 138–141](../../../../../src/storage/accounted_arena.cpp#L138) | Callable definition: void unpin(ArenaHandle handle) noexcept | calls reclaim · [reviewed contract](#b0022) |
| [B0023 · 142–143](../../../../../src/storage/accounted_arena.cpp#L142) | Closes surrounding scope/type. |  · [reviewed contract](#b0023) |
| [B0024 · 144–152](../../../../../src/storage/accounted_arena.cpp#L144) | Callable definition: AccountedTupleArena::AccountedTupleArena(AccountedLayout layout) | calls require, bool, query_account, detail::try_new_arena_owner; guard require(bool(layout), ArenaProblem::layout_mismatch);; growth make_accounted_shared · [reviewed contract](#b0024) |
| [B0025 · 153–153](../../../../../src/storage/accounted_arena.cpp#L153) | Callable definition: AccountedTupleArena::~AccountedTupleArena() | calls clear · [reviewed contract](#b0025) |
| [B0026 · 154–154](../../../../../src/storage/accounted_arena.cpp#L154) | declares callable signatures; declares values/defaults or compile-time conditions. |  · [reviewed contract](#b0026) |
| [B0027 · 155–158](../../../../../src/storage/accounted_arena.cpp#L155) | Callable definition: AccountedTupleArena& AccountedTupleArena::operator=(AccountedTupleArena&& other) noexcept | calls std::move; returns *this · [reviewed contract](#b0027) |
| [B0028 · 159–161](../../../../../src/storage/accounted_arena.cpp#L159) | Callable definition: AccountedTupleArena::State& AccountedTupleArena::state() const | calls require, bool; guard require(bool(state_), ArenaProblem::invalid_arena);return *state_;; returns *state_ · [reviewed contract](#b0028) |
| [B0029 · 162–164](../../../../../src/storage/accounted_arena.cpp#L162) | Callable definition: void AccountedTupleArena::classify(AccountedTuple& tuple, resource::AllocationLifetime lifetime) noexcept | calls set_lifetime · [reviewed contract](#b0029) |
| [B0030 · 165–165](../../../../../src/storage/accounted_arena.cpp#L165) | Callable definition: ArenaOwnerId AccountedTupleArena::owner() const | calls state; returns state().owner · [reviewed contract](#b0030) |
| [B0031 · 166–166](../../../../../src/storage/accounted_arena.cpp#L166) | Callable definition: resource::MemoryAttribution AccountedTupleArena::attribution() const | calls state; returns state().attribution · [reviewed contract](#b0031) |
| [B0032 · 167–167](../../../../../src/storage/accounted_arena.cpp#L167) | Callable definition: const AccountedLayout& AccountedTupleArena::layout() const & | calls state; returns state().layout · [reviewed contract](#b0032) |
| [B0033 · 168–168](../../../../../src/storage/accounted_arena.cpp#L168) | Callable definition: ArenaStatistics AccountedTupleArena::statistics() const | calls state; returns state().counts · [reviewed contract](#b0033) |
| [B0034 · 169–169](../../../../../src/storage/accounted_arena.cpp#L169) | Callable definition: resource::MemoryStatistics AccountedTupleArena::account_statistics() const | calls state, statistics; returns state().account.statistics() · [reviewed contract](#b0034) |
| [B0035 · 170–171](../../../../../src/storage/accounted_arena.cpp#L170) | Explanatory comments or spacing. | source comment (unverified): // Explicit diagnostic: the attribution query scans the whole account ledger, · [reviewed contract](#b0035) |
| [B0036 · 172–191](../../../../../src/storage/accounted_arena.cpp#L172) | Callable definition: ArenaMemoryStatistics AccountedTupleArena::memory_statistics() const | calls state, statistics_for, get_allocator, allocation_usage; returns result; 1 loop sites; source comment (unverified): // Explicit diagnostic: the attribution query scans the whole account ledger, · [reviewed contract](#b0036) |
| [B0037 · 192–212](../../../../../src/storage/accounted_arena.cpp#L192) | Callable definition: ArenaHandle AccountedTupleArena::insert(const AccountedTuple& tuple) | calls state, require, same_token, layout; guard auto& s = state();require(s.layout.same_token(tuple.layout()), ArenaProblem::layout_mismatch);; returns {s.owner, TupleSlotId{position}, s.slots\[position\]-&gt;generation}; growth allocate, emplace, insert, push_back · [reviewed contract](#b0037) |
| [B0038 · 213–213](../../../../../src/storage/accounted_arena.cpp#L213) | Callable definition: bool AccountedTupleArena::contains(ArenaHandle handle) const | calls state, contains; returns state().contains(handle) · [reviewed contract](#b0038) |
| [B0039 · 214–214](../../../../../src/storage/accounted_arena.cpp#L214) | Callable definition: const AccountedTuple& AccountedTupleArena::get(ArenaHandle handle) const & | calls state, live; returns *state().live(handle).tuple · [reviewed contract](#b0039) |
| [B0040 · 215–219](../../../../../src/storage/accounted_arena.cpp#L215) | Callable definition: AccountedTupleArena::Pin AccountedTupleArena::pin(ArenaHandle handle) const | calls state, live, resource::MemoryFailure, Pin; returns Pin(state_, handle) · [reviewed contract](#b0040) |
| [B0041 · 220–223](../../../../../src/storage/accounted_arena.cpp#L220) | Callable definition: bool AccountedTupleArena::erase(ArenaHandle handle) | calls state, contains, erase; returns false; true · [reviewed contract](#b0041) |
| [B0042 · 224–224](../../../../../src/storage/accounted_arena.cpp#L224) | Callable definition: void AccountedTupleArena::clear() | calls state, clear · [reviewed contract](#b0042) |
| [B0043 · 225–230](../../../../../src/storage/accounted_arena.cpp#L225) | Callable definition: void AccountedTupleArena::revive(const Pin& pin) noexcept | calls size, std::terminate, link_live · [reviewed contract](#b0043) |
| [B0044 · 231–232](../../../../../src/storage/accounted_arena.cpp#L231) | Callable definition: AccountedTupleArena::Pin::Pin(std::shared_ptr&lt;State&gt; state, ArenaHandle handle) noexcept : state_(std::move(state)), handle_(hand… | calls state_, std::move, handle_ · [reviewed contract](#b0044) |
| [B0045 · 233–233](../../../../../src/storage/accounted_arena.cpp#L233) | declares callable signatures; declares values/defaults or compile-time conditions. |  · [reviewed contract](#b0045) |
| [B0046 · 234–237](../../../../../src/storage/accounted_arena.cpp#L234) | Callable definition: AccountedTupleArena::Pin& AccountedTupleArena::Pin::operator=(Pin&& other) noexcept | calls std::move; returns *this · [reviewed contract](#b0046) |
| [B0047 · 238–238](../../../../../src/storage/accounted_arena.cpp#L238) | Callable definition: AccountedTupleArena::Pin::~Pin() | calls reset · [reviewed contract](#b0047) |
| [B0048 · 239–241](../../../../../src/storage/accounted_arena.cpp#L239) | Callable definition: void AccountedTupleArena::Pin::reset() noexcept | calls unpin, reset · [reviewed contract](#b0048) |
| [B0049 · 242–244](../../../../../src/storage/accounted_arena.cpp#L242) | Callable definition: ArenaHandle AccountedTupleArena::Pin::handle() const | calls require, bool; guard require(bool(state_), ArenaProblem::invalid_pin);return handle_;; returns handle_ · [reviewed contract](#b0049) |
| [B0050 · 245–247](../../../../../src/storage/accounted_arena.cpp#L245) | Callable definition: const AccountedTuple& AccountedTupleArena::Pin::get() const & | calls handle; returns *state_-&gt;slots\[handle_.slot.value\]-&gt;tuple · [reviewed contract](#b0050) |
| [B0051 · 248–248](../../../../../src/storage/accounted_arena.cpp#L248) | Callable definition: bool AccountedTupleArena::Pin::is_live() const | calls handle, contains; returns state_-&gt;contains(handle_) · [reviewed contract](#b0051) |
| [B0052 · 249–249](../../../../../src/storage/accounted_arena.cpp#L249) | Explanatory comments or spacing. |  |
| [B0053 · 250–295](../../../../../src/storage/accounted_arena.cpp#L250) | Callable definition: void AccountedTupleArena::check_invariants() const | calls state, size, require, has_value; guard require(position &lt; s.slots.size() && expected.free_slots &lt; s.slots.size());; 5 loop sites · [reviewed contract](#b0053) |
| [B0054 · 296–296](../../../../../src/storage/accounted_arena.cpp#L296) | Closes surrounding scope/type. |  · [reviewed contract](#b0054) |

## B0001

[Lines 1–14](../../../../../src/storage/accounted_arena.cpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L1-L14:sha256:e49857c953b73ad89f93643d76d4279902c6e023d1b968d40e0862b189e4478e
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Source usage for this declaration span in src/storage/accounted_arena.cpp: imports \`"crown/storage/accounted_arena.hpp"\`, \`"arena_owner.hpp"\`, \`"crown/resource/ownership.hpp"\`, \`&lt;limits&gt;\`, \`&lt;memory&gt;\`, \`&lt;type_traits&gt;\`, \`&lt;utility&gt;\`, \`&lt;vector&gt;\` for compilation; opens namespace \`crown::storage\`; opens anonymous namespace with translation-unit-local linkage; declares constant-initialized constexpr/static metadata \`none\`, \`last_generation\`. |
| inputs / outputs | Compile inputs are the listed headers and namespace/type names. This span adds no result value unless a helper/type definition listed above is instantiated or called. |
| invariants | The constexpr/static metadata is initialized as a constant expression and has no per-instance owner. |
| ownership | Imports, namespace aliases, forward declarations and compile guards create no object owner. Runtime ownership starts with declared object instances and their allocator/member types. |
| failure | No explicit throw/catch appears in this exact span. Includes, constructors, inline members, static initialization and callees can still fail; follow their enclosing API contracts. |
| cost | Includes/aliases/forwards affect compilation; constexpr/static metadata is constant-initialized. Runtime operation cost belongs to the helper/type that consumes it. |
| Design | [docs/storage.md](../../../../storage.md), [docs/tuple_arenas.md](../../../../tuple_arenas.md), [docs/query_memory.md](../../../../query_memory.md), [docs/code_specs/subsystem_contracts.md](../../../subsystem_contracts.md) |

## B0002

[Lines 15–17](../../../../../src/storage/accounted_arena.cpp#L15); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void require(bool value, ArenaProblem issue
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Raise a fixed arena validation category at a failed invariant. |
| inputs / outputs | Boolean and ArenaProblem in; normal return or ArenaValidationFailure. |
| invariants | No Error string formatting or account creation occurs here. |
| ownership | Exception stores only the enum; descriptions use static text. |
| failure | False throws the supplied fixed issue; caller decides whether failure is recoverable or forbidden by noexcept. |
| cost | One branch on success; exception runtime costs on failure, no diagnostic-string allocation. |
| Design | [docs/tuple_arenas.md](../../../../tuple_arenas.md), [docs/query_memory.md](../../../../query_memory.md), [docs/memory_reports.md](../../../../memory_reports.md), [include/crown/storage/accounted_arena.hpp](../../../../../include/crown/storage/accounted_arena.hpp) |

## B0003

[Lines 18–23](../../../../../src/storage/accounted_arena.cpp#L18); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void add(resource::MemoryUsage& to
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Accumulate disjoint admitted memory-usage partitions. |
| inputs / outputs | Two allocation/request/payload counter triples; destination increases. |
| invariants | Inputs partition actual blocks of one admitted account, so component sums fit its already checked total. |
| ownership | Inline scalar counters only. |
| failure | Noexcept relies on the disjoint-subset invariant; it is not an arbitrary unchecked public accumulator. |
| cost | Three additions; no scan, allocation or redundant per-component overflow guard. |
| Design | [docs/tuple_arenas.md](../../../../tuple_arenas.md), [docs/query_memory.md](../../../../query_memory.md), [docs/memory_reports.md](../../../../memory_reports.md), [include/crown/storage/accounted_arena.hpp](../../../../../include/crown/storage/accounted_arena.hpp) |

## B0004

[Lines 24–25](../../../../../src/storage/accounted_arena.cpp#L24); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L24-L25:sha256:938de74be97bf3aba7872a61ba0e42084008c81e8a202a612134c755aaf7fa06
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Close the \`anonymous namespace in src/storage/accounted_arena.cpp\` scope at this exact source boundary. |
| inputs / outputs | This token introduces no callable inputs or outputs. Declarations inside \`anonymous namespace in src/storage/accounted_arena.cpp\` define the available names, members and operations. |
| invariants | The closing brace matches the opening \`anonymous namespace in src/storage/accounted_arena.cpp\` at its lexical source position in src/storage/accounted_arena.cpp; it preserves C++ namespace/type nesting. |
| ownership | The closing delimiter creates no owner. Types closed by \`anonymous namespace in src/storage/accounted_arena.cpp\` retain the lifetimes and allocator rules of their own fields and operations. |
| failure | No failure path executes at this closing delimiter. Failure and cleanup behavior belong to enclosed functions and owning types. |
| cost | The delimiter itself performs no runtime work; the enclosed initializers, methods and destructors carry their own costs. |
| Design | [docs/storage.md](../../../../storage.md), [docs/tuple_arenas.md](../../../../tuple_arenas.md), [docs/query_memory.md](../../../../query_memory.md), [docs/code_specs/subsystem_contracts.md](../../../subsystem_contracts.md) |

## B0005

[Lines 26–36](../../../../../src/storage/accounted_arena.cpp#L26); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::string_view ArenaValidationFailure::code()
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Map a fixed arena issue to a stable code. |
| inputs / outputs | Stored issue yields a static string_view, with arena_contract fallback. |
| invariants | Mapping changes no arena state and does not validate a handle. |
| ownership | View refers to static literal storage. |
| failure | Noexcept; unknown enum values use the invariant fallback. |
| cost | Fixed switch, no allocation. |
| Design | [docs/tuple_arenas.md](../../../../tuple_arenas.md), [docs/query_memory.md](../../../../query_memory.md), [docs/memory_reports.md](../../../../memory_reports.md), [include/crown/storage/accounted_arena.hpp](../../../../../include/crown/storage/accounted_arena.hpp) |

## B0006

[Lines 37–47](../../../../../src/storage/accounted_arena.cpp#L37); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
const char* ArenaValidationFailure::what()
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Present a fixed arena failure description. |
| inputs / outputs | Stored issue yields static null-terminated text. |
| invariants | Message identifies validation category without formatting dynamic row data. |
| ownership | Returned pointer refers to static storage. |
| failure | Noexcept; unknown issue has a fixed fallback. |
| cost | Fixed switch, no owning string allocation. |
| Design | [docs/tuple_arenas.md](../../../../tuple_arenas.md), [docs/query_memory.md](../../../../query_memory.md), [docs/memory_reports.md](../../../../memory_reports.md), [include/crown/storage/accounted_arena.hpp](../../../../../include/crown/storage/accounted_arena.hpp) |

## B0007

[Lines 48–49](../../../../../src/storage/accounted_arena.cpp#L48); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct AccountedTupleArena::State {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Own stable arena slots, live/free links and generational pin state in one account. |
| inputs / outputs | Admitted layout/account and unique arena owner produce empty slot directory and counters. |
| invariants | Slot storage never moves; directory growth moves only SlotOwner handles. Live/retained/free/exhausted states partition slots; exhausted generations never wrap. |
| ownership | Shared state owns slot blocks and tuple payloads; pins retain state after facade destruction. |
| failure | State construction publishes nothing until the accounted shared owner succeeds. |
| cost | O(slot high-water capacity) metadata over lifetime; no unbounded history beyond visible reusable/exhausted storage. |
| Design | [docs/tuple_arenas.md](../../../../tuple_arenas.md), [docs/query_memory.md](../../../../query_memory.md), [docs/storage_journal.md](../../../../storage_journal.md) |

## B0008

[Lines 50–57](../../../../../src/storage/accounted_arena.cpp#L50); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct Slot {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Retain one stable generation and optional funded tuple. |
| inputs / outputs | Tuple is moved into a new slot; membership, pin and list metadata start inactive. |
| invariants | Generation starts at one; pinned deleted payload is retained; exhausted generations never rejoin the reusable pool. |
| ownership | Slot lives in its own account block; optional AccountedTuple retains its payload. |
| failure | Noexcept construction relies on nonthrowing tuple move; allocation/copy happens before construction. |
| cost | Fixed metadata plus a tuple handle move, no row copy in Slot construction. |
| Design | [docs/tuple_arenas.md](../../../../tuple_arenas.md), [docs/query_memory.md](../../../../query_memory.md), [docs/memory_reports.md](../../../../memory_reports.md), [include/crown/storage/accounted_arena.hpp](../../../../../include/crown/storage/accounted_arena.hpp) |

## B0009

[Lines 58–59](../../../../../src/storage/accounted_arena.cpp#L58); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L58-L59:sha256:aadd891f17693de381dba24f9dd8962ab882bda0ade83b344a8f0ccb82716e1d
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Usage note immediately before \`struct SlotOwner\`: A slot's address never moves. Only this block handle moves during directory growth, and every constructed Slot is destroyed before its block is freed. |
| inputs / outputs | This comment introduces no parameter, field or return value. It documents the adjacent construct beginning at src/storage/accounted_arena.cpp:L60; use that declaration for the actual input/output shape. |
| invariants | The source note states: A slot's address never moves. Only this block handle moves during directory growth, and every constructed Slot is destroyed before its block is freed. It is prose guidance; the adjacent implementation is the place to check enforcement. |
| ownership | The comment creates or retains no runtime owner. Its prose documents moving the slot block handle while preserving Slot addresses and destroying Slot before releasing its block; that lifetime rule must be checked in the adjacent implementation, not inferred from the comment alone. |
| failure | This comment adds no branch or handler. Any failure behavior remains in the adjacent callable implementation and its callers. |
| cost | The prose adds no executable work. Runtime cost belongs to the adjacent operation; the note does not establish a measured or global complexity bound. |
| Design | [docs/storage.md](../../../../storage.md), [docs/tuple_arenas.md](../../../../tuple_arenas.md), [docs/query_memory.md](../../../../query_memory.md), [docs/code_specs/subsystem_contracts.md](../../../subsystem_contracts.md) |

## B0010

[Lines 60–78](../../../../../src/storage/accounted_arena.cpp#L60); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct SlotOwner {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Own stable slot storage while the directory relocates handles. |
| inputs / outputs | Move-only MemoryBlock wrapper destroys the constructed Slot before releasing its block. |
| invariants | Only complete Slot objects are adopted. Vector growth moves block handles, never slot addresses. |
| ownership | Exactly one SlotOwner owns each slot block; moved-from owner is empty. |
| failure | Move/reset/destruction are noexcept; cleanup never allocates. |
| cost | Fixed handle moves; reset may destroy a deep tuple and free its funded block. Directory growth can move all H handles. |
| Design | [docs/tuple_arenas.md](../../../../tuple_arenas.md), [docs/query_memory.md](../../../../query_memory.md), [docs/memory_reports.md](../../../../memory_reports.md), [include/crown/storage/accounted_arena.hpp](../../../../../include/crown/storage/accounted_arena.hpp) |

## B0011

[Lines 79–86](../../../../../src/storage/accounted_arena.cpp#L79); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L79-L86:sha256:95c090b0e8c416e808dcaf80163ebccbbc41159a902c119a4f997c9a2f84a057
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Declare AccountedTupleArena::State account/layout, numeric owner ID, attribution, SlotOwner directory, free/live heads and ArenaStatistics; require SlotOwner nothrow movement. |
| inputs / outputs | The listed State members retain allocation context, layout/identity, stable slot blocks and population/free-list metadata. The static assertion checks one C++ move property at compile time. |
| invariants | ArenaOwnerId owner identifies the arena for handle validation; it is not a resource-owning object. Vector growth moves SlotOwner handles, while each allocated Slot stays at its block address. Handle validity/pin rules remain separate API contracts. |
| ownership | account retains account control; layout retains its descriptor control. The allocator-backed slots vector owns SlotOwner elements, each of which owns a MemoryBlock. SlotOwner::reset destroys the constructed Slot before freeing its block; numeric owner/head fields and counts are values. |
| failure | An incompatible SlotOwner move property fails compilation. Construction/slot-directory growth and slot allocation keep the constructor/arena-operation resource and allocation failure contracts. |
| cost | State has fixed metadata and an accounted SlotOwner vector; growth allocates directory capacity and later slot creation allocates separate blocks under their explicit purpose/attribution. Moving owners does not relocate Slot payloads; teardown destroys each Slot before its block is released. |
| Design | [docs/storage.md](../../../../storage.md), [docs/tuple_arenas.md](../../../../tuple_arenas.md), [docs/query_memory.md](../../../../query_memory.md), [docs/code_specs/subsystem_contracts.md](../../../subsystem_contracts.md) |

## B0012

[Lines 87–90](../../../../../src/storage/accounted_arena.cpp#L87); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
State(resource::MemoryAccount value
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Initialize one empty native arena state under its existing authority. |
| inputs / outputs | Account, immutable layout and unique arena ID produce empty directory/free/live lists and counters. |
| invariants | State attribution is tuple_arena:id; directory uses that same account and ownership category. |
| ownership | State retains account/layout; its vector allocator borrows that retained authority. |
| failure | Noexcept metadata construction; make_accounted_shared funds State/control before adoption. |
| cost | Fixed empty-state construction; slot and directory allocations are deferred. |
| Design | [docs/tuple_arenas.md](../../../../tuple_arenas.md), [docs/query_memory.md](../../../../query_memory.md), [docs/memory_reports.md](../../../../memory_reports.md), [include/crown/storage/accounted_arena.hpp](../../../../../include/crown/storage/accounted_arena.hpp) |

## B0013

[Lines 91–92](../../../../../src/storage/accounted_arena.cpp#L91); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L91-L92:sha256:36f20f0d57663b6b4e810443a43ddffefc3b20a4e37675ed2946b6d076815b07
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Source usage for this declaration span in src/storage/accounted_arena.cpp; the range contains the state/helper statements shown at its exact source span. |
| inputs / outputs | Compile inputs are the listed headers and namespace/type names. This span adds no result value unless a helper/type definition listed above is instantiated or called. |
| invariants | The exact import, alias, namespace and member declarations determine the local compile/link surface; stronger behavior belongs to their constructors and operations. |
| ownership | Imports, namespace aliases, forward declarations and compile guards create no object owner. Runtime ownership starts with declared object instances and their allocator/member types. |
| failure | No explicit throw/catch appears in this exact span. Includes, constructors, inline members, static initialization and callees can still fail; follow their enclosing API contracts. |
| cost | This span changes compile/link structure and type layout. Runtime initialization, allocation, exceptions and operation work follow the declared owner/callable code; no absence is inferred from declaration syntax. |
| Design | [docs/storage.md](../../../../storage.md), [docs/tuple_arenas.md](../../../../tuple_arenas.md), [docs/query_memory.md](../../../../query_memory.md), [docs/code_specs/subsystem_contracts.md](../../../subsystem_contracts.md) |

## B0014

[Lines 93–95](../../../../../src/storage/accounted_arena.cpp#L93); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void owned(ArenaHandle handle)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Authenticate the immutable owner part of a handle. |
| inputs / outputs | Handle in; success only when its arena owner matches. |
| invariants | Owner mismatch is distinct from stale/out-of-range generation. |
| ownership | Borrows State; stores nothing. |
| failure | Foreign owner throws fixed foreign_handle without mutation. |
| cost | One owner comparison; no lookup or allocation. |
| Design | [docs/tuple_arenas.md](../../../../tuple_arenas.md), [docs/query_memory.md](../../../../query_memory.md), [docs/memory_reports.md](../../../../memory_reports.md), [include/crown/storage/accounted_arena.hpp](../../../../../include/crown/storage/accounted_arena.hpp) |

## B0015

[Lines 96–100](../../../../../src/storage/accounted_arena.cpp#L96); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
[[nodiscard]] bool contains(ArenaHandle handle) const
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Check current live membership at one slot generation. |
| inputs / outputs | Authenticated handle yields true only for an in-range live slot with the same generation. |
| invariants | Foreign owners throw; stale generation or absent slot returns false. Deleted pinned tuples are not live members. |
| ownership | Borrows the directory/slot without retaining a pin. |
| failure | Owner failure changes nothing; short-circuit bounds check precedes slot access. |
| cost | Direct slot addressing plus fixed comparisons; no directory scan or allocation. |
| Design | [docs/tuple_arenas.md](../../../../tuple_arenas.md), [docs/query_memory.md](../../../../query_memory.md), [docs/memory_reports.md](../../../../memory_reports.md), [include/crown/storage/accounted_arena.hpp](../../../../../include/crown/storage/accounted_arena.hpp) |

## B0016

[Lines 101–104](../../../../../src/storage/accounted_arena.cpp#L101); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
[[nodiscard]] Slot& live(ArenaHandle handle)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Borrow a current live slot after full handle authentication. |
| inputs / outputs | Handle in; mutable Slot reference out. |
| invariants | Requires owned, in-range, live, current-generation membership; retained dead pins are not accepted here. |
| ownership | Reference is bounded by enclosing state/operation; no pin is created. |
| failure | Foreign owner or stale membership throws before returning a reference. |
| cost | Fixed owner/slot/generation checks and direct addressing. |
| Design | [docs/tuple_arenas.md](../../../../tuple_arenas.md), [docs/query_memory.md](../../../../query_memory.md), [docs/memory_reports.md](../../../../memory_reports.md), [include/crown/storage/accounted_arena.hpp](../../../../../include/crown/storage/accounted_arena.hpp) |

## B0017

[Lines 105–108](../../../../../src/storage/accounted_arena.cpp#L105); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void classify_slot(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Classify the slot block and present tuple payload as one lifetime state. |
| inputs / outputs | Known slot position and active/retained/free classification update actual account partitions. |
| invariants | Slot and optional tuple belong to the arena account/attribution; caller avoids allocation reentry. |
| ownership | No transfer/free of either block; immutable layout metadata is shared separately. |
| failure | Noexcept internal operation relies on valid lifetime/ownership metadata; a broken precondition terminates through fixed checks. |
| cost | O(1) direct block classifications, no allocation-ledger scan. |
| Design | [docs/tuple_arenas.md](../../../../tuple_arenas.md), [docs/query_memory.md](../../../../query_memory.md), [docs/storage_journal.md](../../../../storage_journal.md) |

## B0018

[Lines 109–114](../../../../../src/storage/accounted_arena.cpp#L109); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void link_live(std::size_t position, Slot& slot)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Publish a prepared slot into the live linked list. |
| inputs / outputs | Funded existing slot/position enters the head and increments live count. |
| invariants | Caller supplies a nonlive admissible slot and already established tuple; lists/counters remain consistent. |
| ownership | Reclassifies slot/tuple blocks active without transferring account ownership. |
| failure | Noexcept internal publication; invalid ownership/lifetime metadata terminates through fixed lower checks. |
| cost | Fixed link/counter/direct lifetime edits; no tuple copy or account-ledger scan. |
| Design | [docs/tuple_arenas.md](../../../../tuple_arenas.md), [docs/query_memory.md](../../../../query_memory.md), [docs/memory_reports.md](../../../../memory_reports.md), [include/crown/storage/accounted_arena.hpp](../../../../../include/crown/storage/accounted_arena.hpp) |

## B0019

[Lines 115–125](../../../../../src/storage/accounted_arena.cpp#L115); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void reclaim(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Release an unpinned retired tuple and classify its stable slot as reusable or exhausted. |
| inputs / outputs | Nonlive zero-pin Slot loses tuple storage; nonmax generation joins free list, max generation stays unreusable. |
| invariants | Only a last-pin release or unpinned erase may reclaim; generation never decreases or wraps. |
| ownership | Retains the slot metadata block/high-water directory while releasing tuple payload. |
| failure | Noexcept under arena ownership/lifetime invariants. |
| cost | O(1) free-list/counter work plus actual tuple payload release; no allocation or directory shrink. |
| Design | [docs/tuple_arenas.md](../../../../tuple_arenas.md), [docs/query_memory.md](../../../../query_memory.md), [docs/storage_journal.md](../../../../storage_journal.md) |

## B0020

[Lines 126–134](../../../../../src/storage/accounted_arena.cpp#L126); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void erase(std::size_t position, Slot& slot)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Remove one live membership while respecting retained pins. |
| inputs / outputs | Known live slot is unlinked; pinned payload becomes retained, otherwise it is reclaimed. |
| invariants | Membership disappears immediately; pin count controls payload retention and generation reuse. |
| ownership | Keeps payload/storage for live pins; unpinned payload is destroyed under its account. |
| failure | Noexcept internal mutation relies on valid list/slot invariants. |
| cost | Fixed live-list edits plus actual tuple destruction or direct retained classification; no scan. |
| Design | [docs/tuple_arenas.md](../../../../tuple_arenas.md), [docs/query_memory.md](../../../../query_memory.md), [docs/memory_reports.md](../../../../memory_reports.md), [include/crown/storage/accounted_arena.hpp](../../../../../include/crown/storage/accounted_arena.hpp) |

## B0021

[Lines 135–137](../../../../../src/storage/accounted_arena.cpp#L135); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void clear() noexcept
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Retire every currently live arena row when clearing or closing the facade. |
| inputs / outputs | Repeatedly erase live_head until no live rows remain. |
| invariants | Pinned tuples become retained; unpinned tuples reclaim; high-water slot metadata remains visible. |
| ownership | Pins keep state/retired payload alive after the facade releases its shared owner. |
| failure | Noexcept and nonallocating for valid arena state. |
| cost | O(current live rows) pointer/classification/release work; does not scan free/exhausted slots. |
| Design | [docs/tuple_arenas.md](../../../../tuple_arenas.md), [docs/query_memory.md](../../../../query_memory.md), [docs/storage_journal.md](../../../../storage_journal.md) |

## B0022

[Lines 138–141](../../../../../src/storage/accounted_arena.cpp#L138); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void unpin(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Release one established pin and reclaim a retired row after its last pin. |
| inputs / outputs | Pin handle decrements slot and total pin counts; last nonlive pin triggers reclaim. |
| invariants | The Pin already proves matching owner/slot/generation and retains its payload; no fresh external handle validation is required. |
| ownership | Called before releasing the pin shared state reference. |
| failure | Noexcept internal cleanup; invalid duplicated pin release violates the owning Pin contract. |
| cost | O(1) pin/free-list bookkeeping plus possible targeted tuple-payload destruction. This function does not release the State owner; its caller Pin::reset may subsequently perform O(slot high-water) final-State destruction. |
| Design | [docs/tuple_arenas.md](../../../../tuple_arenas.md), [docs/query_memory.md](../../../../query_memory.md), [docs/storage_journal.md](../../../../storage_journal.md) |

## B0023

[Lines 142–143](../../../../../src/storage/accounted_arena.cpp#L142); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L142-L143:sha256:cdbb10f75f6890449819c9d57e5ae7b786fb73c5111c5d829c37bc18f3e053e8
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Close the \`struct AccountedTupleArena::State\` scope at this exact source boundary. |
| inputs / outputs | This token introduces no callable inputs or outputs. Declarations inside \`struct AccountedTupleArena::State\` define the available names, members and operations. |
| invariants | The closing brace matches the opening \`struct AccountedTupleArena::State\` at its lexical source position in src/storage/accounted_arena.cpp; it preserves C++ namespace/type nesting. |
| ownership | The closing delimiter creates no owner. Types closed by \`struct AccountedTupleArena::State\` retain the lifetimes and allocator rules of their own fields and operations. |
| failure | No failure path executes at this closing delimiter. Failure and cleanup behavior belong to enclosed functions and owning types. |
| cost | The delimiter itself performs no runtime work; the enclosed initializers, methods and destructors carry their own costs. |
| Design | [docs/storage.md](../../../../storage.md), [docs/tuple_arenas.md](../../../../tuple_arenas.md), [docs/query_memory.md](../../../../query_memory.md), [docs/code_specs/subsystem_contracts.md](../../../subsystem_contracts.md) |

## B0024

[Lines 144–152](../../../../../src/storage/accounted_arena.cpp#L144); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
AccountedTupleArena::AccountedTupleArena(AccountedLayout layout)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Create a native arena in the supplied immutable layout account. |
| inputs / outputs | Valid AccountedLayout produces an empty unique-identity arena with accounted shared State. |
| invariants | Owner IDs are never reused; an unpublished construction failure may consume one identity. |
| ownership | Account copied from the layout, not minted as another query cap. |
| failure | Invalid layout, owner-ID exhaustion or allocation failure publishes no arena. |
| cost | Fixed owner-ID CAS/empty state construction; slot payload/storage is deferred until insertion. |
| Design | [docs/tuple_arenas.md](../../../../tuple_arenas.md), [docs/query_memory.md](../../../../query_memory.md), [docs/storage_journal.md](../../../../storage_journal.md) |

## B0025

[Lines 153–153](../../../../../src/storage/accounted_arena.cpp#L153); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
AccountedTupleArena::~AccountedTupleArena()
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Close live membership when the arena facade dies. |
| inputs / outputs | Clears the current live list before dropping its shared State. |
| invariants | Pins can keep deleted payloads alive after facade destruction. |
| ownership | Facade releases its shared state; final state owner destroys all high-water slots/directory. |
| failure | Noexcept cleanup; no replacement allocation or catch layer. |
| cost | O(L) live erases and payload releases; final State destruction additionally visits H slots. |
| Design | [docs/tuple_arenas.md](../../../../tuple_arenas.md), [docs/query_memory.md](../../../../query_memory.md), [docs/memory_reports.md](../../../../memory_reports.md), [include/crown/storage/accounted_arena.hpp](../../../../../include/crown/storage/accounted_arena.hpp) |

## B0026

[Lines 154–154](../../../../../src/storage/accounted_arena.cpp#L154); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L154-L154:sha256:dac59247bb588071c45e09c4f9fe207248d132e3a16a70aac26c52b63b0cfa89
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Source usage for this declaration span in src/storage/accounted_arena.cpp; the range contains the state/helper statements shown at its exact source span. |
| inputs / outputs | Compile inputs are the listed headers and namespace/type names. This span adds no result value unless a helper/type definition listed above is instantiated or called. |
| invariants | The exact import, alias, namespace and member declarations determine the local compile/link surface; stronger behavior belongs to their constructors and operations. |
| ownership | Imports, namespace aliases, forward declarations and compile guards create no object owner. Runtime ownership starts with declared object instances and their allocator/member types. |
| failure | No explicit throw/catch appears in this exact span. Includes, constructors, inline members, static initialization and callees can still fail; follow their enclosing API contracts. |
| cost | This span changes compile/link structure and type layout. Runtime initialization, allocation, exceptions and operation work follow the declared owner/callable code; no absence is inferred from declaration syntax. |
| Design | [docs/storage.md](../../../../storage.md), [docs/tuple_arenas.md](../../../../tuple_arenas.md), [docs/query_memory.md](../../../../query_memory.md), [docs/code_specs/subsystem_contracts.md](../../../subsystem_contracts.md) |

## B0027

[Lines 155–158](../../../../../src/storage/accounted_arena.cpp#L155); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
AccountedTupleArena& AccountedTupleArena::operator=
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Replace an arena facade without abandoning its old live membership. |
| inputs / outputs | Move source into destination; self-move is ignored. |
| invariants | Old arena is cleared before adopting new state; pins retain old deleted payload independently. |
| ownership | Transfers shared State handle; source becomes empty. |
| failure | Noexcept; old State/payload cleanup cannot allocate. |
| cost | Handle move plus old live-list cleanup and possible O(H) final-state destruction. |
| Design | [docs/tuple_arenas.md](../../../../tuple_arenas.md), [docs/query_memory.md](../../../../query_memory.md), [docs/memory_reports.md](../../../../memory_reports.md), [include/crown/storage/accounted_arena.hpp](../../../../../include/crown/storage/accounted_arena.hpp) |

## B0028

[Lines 159–161](../../../../../src/storage/accounted_arena.cpp#L159); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
AccountedTupleArena::State& AccountedTupleArena::state()
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Borrow the retained mutable state behind a valid facade. |
| inputs / outputs | Valid facade gives State reference even for const diagnostic wrappers. |
| invariants | All access remains single-mutating-thread/external-serialization; const is not concurrency permission. |
| ownership | Reference borrows state_; it does not add an owner. |
| failure | Empty/moved-from facade throws invalid_arena. |
| cost | Fixed owner check, no allocation or traversal. |
| Design | [docs/tuple_arenas.md](../../../../tuple_arenas.md), [docs/query_memory.md](../../../../query_memory.md), [docs/memory_reports.md](../../../../memory_reports.md), [include/crown/storage/accounted_arena.hpp](../../../../../include/crown/storage/accounted_arena.hpp) |

## B0029

[Lines 162–164](../../../../../src/storage/accounted_arena.cpp#L162); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void AccountedTupleArena::classify(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Reclassify the exact tuple payload allocation. |
| inputs / outputs | Tuple and lifetime tag update its accounted block classification. |
| invariants | Account, attribution and requested bytes do not change; classification never refunds a limit. |
| ownership | Tuple keeps its MemoryBlock. |
| failure | Noexcept internal wrapper relies on valid block/lifetime; invalid metadata is a contract fault. |
| cost | One direct block-classification operation; no account-ledger search. |
| Design | [docs/tuple_arenas.md](../../../../tuple_arenas.md), [docs/query_memory.md](../../../../query_memory.md), [docs/memory_reports.md](../../../../memory_reports.md), [include/crown/storage/accounted_arena.hpp](../../../../../include/crown/storage/accounted_arena.hpp) |

## B0030

[Lines 165–165](../../../../../src/storage/accounted_arena.cpp#L165); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
ArenaOwnerId AccountedTupleArena::owner()
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Read the immutable arena owner ID. |
| inputs / outputs | Returns State.owner. |
| invariants | This accessor does not validate all arena invariants or scan slots. |
| ownership | Value ID does not keep an arena or handle alive. |
| failure | Moved/empty arena rejects through state(); otherwise no allocation. |
| cost | Fixed owner access and value/reference return; attribution/full arena memory scans are separate. |
| Design | [docs/tuple_arenas.md](../../../../tuple_arenas.md), [docs/query_memory.md](../../../../query_memory.md), [docs/memory_reports.md](../../../../memory_reports.md), [include/crown/storage/accounted_arena.hpp](../../../../../include/crown/storage/accounted_arena.hpp) |

## B0031

[Lines 166–166](../../../../../src/storage/accounted_arena.cpp#L166); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
resource::MemoryAttribution AccountedTupleArena::attribution()
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Read this arena allocation attribution. |
| inputs / outputs | Returns tuple_arena:id used for its funded state/slots/payload. |
| invariants | This accessor does not validate all arena invariants or scan slots. |
| ownership | Inline value does not transfer memory ownership. |
| failure | Moved/empty arena rejects through state(); otherwise no allocation. |
| cost | Fixed owner access and value/reference return; attribution/full arena memory scans are separate. |
| Design | [docs/tuple_arenas.md](../../../../tuple_arenas.md), [docs/query_memory.md](../../../../query_memory.md), [docs/memory_reports.md](../../../../memory_reports.md), [include/crown/storage/accounted_arena.hpp](../../../../../include/crown/storage/accounted_arena.hpp) |

## B0032

[Lines 167–167](../../../../../src/storage/accounted_arena.cpp#L167); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
const AccountedLayout& AccountedTupleArena::layout() const &
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Borrow the exact immutable layout token. |
| inputs / outputs | Returns State.layout by lvalue-only const reference. |
| invariants | This accessor does not validate all arena invariants or scan slots. |
| ownership | Reference must not outlive the retained arena state; rvalue borrow is deleted. |
| failure | Moved/empty arena rejects through state(); otherwise no allocation. |
| cost | Fixed owner access and value/reference return; attribution/full arena memory scans are separate. |
| Design | [docs/tuple_arenas.md](../../../../tuple_arenas.md), [docs/query_memory.md](../../../../query_memory.md), [docs/memory_reports.md](../../../../memory_reports.md), [include/crown/storage/accounted_arena.hpp](../../../../../include/crown/storage/accounted_arena.hpp) |

## B0033

[Lines 168–168](../../../../../src/storage/accounted_arena.cpp#L168); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
ArenaStatistics AccountedTupleArena::statistics()
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Read maintained live/free/retained/exhausted/pin counts. |
| inputs / outputs | Returns State.counts without recomputation. |
| invariants | This accessor does not validate all arena invariants or scan slots. |
| ownership | Inline counter snapshot. |
| failure | Moved/empty arena rejects through state(); otherwise no allocation. |
| cost | Fixed owner access and value/reference return; attribution/full arena memory scans are separate. |
| Design | [docs/tuple_arenas.md](../../../../tuple_arenas.md), [docs/query_memory.md](../../../../query_memory.md), [docs/memory_reports.md](../../../../memory_reports.md), [include/crown/storage/accounted_arena.hpp](../../../../../include/crown/storage/accounted_arena.hpp) |

## B0034

[Lines 169–169](../../../../../src/storage/accounted_arena.cpp#L169); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
resource::MemoryStatistics AccountedTupleArena::account_statistics()
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Read account-wide native allocation counters. |
| inputs / outputs | Returns shared account statistics, including other owners in the same account. |
| invariants | This accessor does not validate all arena invariants or scan slots. |
| ownership | Inline snapshot; no transfer/refill of authority. |
| failure | Moved/empty arena rejects through state(); otherwise no allocation. |
| cost | Fixed owner access and value/reference return; attribution/full arena memory scans are separate. |
| Design | [docs/tuple_arenas.md](../../../../tuple_arenas.md), [docs/query_memory.md](../../../../query_memory.md), [docs/memory_reports.md](../../../../memory_reports.md), [include/crown/storage/accounted_arena.hpp](../../../../../include/crown/storage/accounted_arena.hpp) |

## B0035

[Lines 170–171](../../../../../src/storage/accounted_arena.cpp#L170); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L170-L171:sha256:becb7d586c3f1402868fc1712daa02f2025cbfee3d199aeaf6e6d405e4608ff0
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Usage note immediately before \`ArenaMemoryStatistics AccountedTupleArena::memory_statistics() const\`: Explicit diagnostic: the attribution query scans the whole account ledger, then this report visits all high-water slots, including retained/free slots. |
| inputs / outputs | This comment introduces no parameter, field or return value. It documents the adjacent construct beginning at src/storage/accounted_arena.cpp:L172; use that declaration for the actual input/output shape. |
| invariants | The source note states: Explicit diagnostic: the attribution query scans the whole account ledger, then this report visits all high-water slots, including retained/free slots. It is prose guidance; the adjacent implementation is the place to check enforcement. |
| ownership | The comment itself retains nothing. It documents this neighboring ownership/account boundary: Explicit diagnostic: the attribution query scans the whole account ledger, then this report visits all high-water slots, including retained/free slots. Actual lifetime is determined by the declared members and owners. |
| failure | This comment adds no branch or handler. Any failure behavior remains in the adjacent callable implementation and its callers. |
| cost | The note states a local cost boundary: Explicit diagnostic: the attribution query scans the whole account ledger, then this report visits all high-water slots, including retained/free slots. Treat it as usage guidance; actual work follows the implementation and input. |
| Design | [docs/storage.md](../../../../storage.md), [docs/tuple_arenas.md](../../../../tuple_arenas.md), [docs/query_memory.md](../../../../query_memory.md), [docs/code_specs/subsystem_contracts.md](../../../subsystem_contracts.md) |

## B0036

[Lines 172–191](../../../../../src/storage/accounted_arena.cpp#L172); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
ArenaMemoryStatistics AccountedTupleArena::memory_statistics()
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Reconcile exact native arena allocations with logical slot states. |
| inputs / outputs | Returns state/control/directory/spare/live/retained/free/exhausted byte and record breakdowns. |
| invariants | Current account attribution must match actual arena-owned blocks; spare vector capacity is charged. |
| ownership | Returned diagnostic owns only fixed counters; no payload/address collection escapes. |
| failure | Invalid arena/account metadata raises the existing fixed contract failure. |
| cost | O(all account allocations + arena slot high-water): attributed ledger scan followed by slot traversal; no dynamic scratch. |
| Design | [docs/tuple_arenas.md](../../../../tuple_arenas.md), [docs/query_memory.md](../../../../query_memory.md), [docs/storage_journal.md](../../../../storage_journal.md) |

## B0037

[Lines 192–212](../../../../../src/storage/accounted_arena.cpp#L192); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
ArenaHandle AccountedTupleArena::insert(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Publish one accounted tuple in a stable new or safely reused generational slot. |
| inputs / outputs | Same-token input is deeply copied into the arena account; returns owner/slot/current generation handle. |
| invariants | For reuse, tuple construction succeeds before removing free membership or advancing generation. For new slots, payload and directory growth succeed before live publication. |
| ownership | Arena owns a new payload independent of input; slot address survives directory reallocation. |
| failure | Layout mismatch, size/history limit or allocation failure leaves previously published arena rows/generations/counters unchanged. |
| cost | Actual row fields/deep-byte copy; O(1) reuse bookkeeping, amortized directory growth that can move O(slot high-water) handles. |
| Design | [docs/tuple_arenas.md](../../../../tuple_arenas.md), [docs/query_memory.md](../../../../query_memory.md), [docs/storage_journal.md](../../../../storage_journal.md) |

## B0038

[Lines 213–213](../../../../../src/storage/accounted_arena.cpp#L213); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
bool AccountedTupleArena::contains(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Expose authenticated current-membership lookup. |
| inputs / outputs | Handle yields State.contains result. |
| invariants | Foreign owner throws; stale/out-of-range/deleted returns false. |
| ownership | No pin or retaining row is returned. |
| failure | Invalid facade/foreign owner rejects without mutation. |
| cost | Fixed direct slot lookup, no row copy. |
| Design | [docs/tuple_arenas.md](../../../../tuple_arenas.md), [docs/query_memory.md](../../../../query_memory.md), [docs/memory_reports.md](../../../../memory_reports.md), [include/crown/storage/accounted_arena.hpp](../../../../../include/crown/storage/accounted_arena.hpp) |

## B0039

[Lines 214–214](../../../../../src/storage/accounted_arena.cpp#L214); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
const AccountedTuple& AccountedTupleArena::get(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Borrow the live tuple of an authenticated current handle. |
| inputs / outputs | Handle returns a lvalue-only const tuple reference. |
| invariants | Must be live at the same generation. A handle alone does not pin storage across erase/clear. |
| ownership | Borrow is bounded by current membership and retained state; caller uses Pin for retained lifetime. |
| failure | Invalid facade/foreign/stale handle throws before reference return. |
| cost | Fixed direct checks; no deep copy or allocation. |
| Design | [docs/tuple_arenas.md](../../../../tuple_arenas.md), [docs/query_memory.md](../../../../query_memory.md), [docs/memory_reports.md](../../../../memory_reports.md), [include/crown/storage/accounted_arena.hpp](../../../../../include/crown/storage/accounted_arena.hpp) |

## B0040

[Lines 215–219](../../../../../src/storage/accounted_arena.cpp#L215); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
AccountedTupleArena::Pin AccountedTupleArena::pin(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Retain a currently live immutable arena tuple across erase/closure. |
| inputs / outputs | Valid live handle produces a move-only pin and increments slot/total counts. |
| invariants | Foreign owner errors are distinct from same-owner stale handles; pin-count overflow is checked before increments. |
| ownership | Pin shares the same State/account, not a payload copy or table-membership lease. |
| failure | Invalid/stale/foreign handle or counter exhaustion changes no pin count. |
| cost | O(1) owner/slot/generation checks and shared-owner retention, no allocation. |
| Design | [docs/tuple_arenas.md](../../../../tuple_arenas.md), [docs/query_memory.md](../../../../query_memory.md), [docs/storage_journal.md](../../../../storage_journal.md) |

## B0041

[Lines 220–223](../../../../../src/storage/accounted_arena.cpp#L220); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
bool AccountedTupleArena::erase(ArenaHandle handle)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Erase current membership for an authenticated handle. |
| inputs / outputs | Returns false for absent/stale slot; true after one actual live removal. |
| invariants | Foreign owner is an error, not a miss; pinned deleted payload remains readable by its Pin. |
| ownership | State keeps slot storage; unpinned tuple payload is reclaimed. |
| failure | Invalid facade/owner throws before mutation; actual internal erase is nonthrowing. |
| cost | Fixed checks/list edits plus possible actual tuple release; no whole-directory scan. |
| Design | [docs/tuple_arenas.md](../../../../tuple_arenas.md), [docs/query_memory.md](../../../../query_memory.md), [docs/memory_reports.md](../../../../memory_reports.md), [include/crown/storage/accounted_arena.hpp](../../../../../include/crown/storage/accounted_arena.hpp) |

## B0042

[Lines 224–224](../../../../../src/storage/accounted_arena.cpp#L224); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void AccountedTupleArena::clear()
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Erase every current live membership. |
| inputs / outputs | Valid facade becomes empty of live rows, preserving reusable/exhausted metadata and retained pins. |
| invariants | Does not scan or shrink every high-water slot; live list drives removal. |
| ownership | Pin owners retain deleted tuples/state; facade retains directory/slot capacity. |
| failure | Invalid facade throws before mutation; State.clear cleanup is noexcept. |
| cost | O(L) live-list erases plus released payload costs; no new allocation. |
| Design | [docs/tuple_arenas.md](../../../../tuple_arenas.md), [docs/query_memory.md](../../../../query_memory.md), [docs/memory_reports.md](../../../../memory_reports.md), [include/crown/storage/accounted_arena.hpp](../../../../../include/crown/storage/accounted_arena.hpp) |

## B0043

[Lines 225–230](../../../../../src/storage/accounted_arena.cpp#L225); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void AccountedTupleArena::revive(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Restore a journal-retained tuple to arena live membership without allocating. |
| inputs / outputs | An owner-matching retained Pin revives its unchanged slot/generation/payload. |
| invariants | Same State, nonlive slot, positive pin count, matching generation and payload are prepaid inverse preconditions. |
| ownership | Retained payload already exists; pin ownership and generation remain unchanged. |
| failure | Noexcept; invalid inverse state terminates, rather than trying a new insertion. |
| cost | O(1) classification/live-link/counter work; no payload copy, hash or generation increment. |
| Design | [docs/tuple_arenas.md](../../../../tuple_arenas.md), [docs/query_memory.md](../../../../query_memory.md), [docs/storage_journal.md](../../../../storage_journal.md) |

## B0044

[Lines 231–232](../../../../../src/storage/accounted_arena.cpp#L231); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
AccountedTupleArena::Pin::Pin(std::shared_ptr<State> state
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Adopt a pin whose counters were already admitted and incremented. |
| inputs / outputs | State handle and current ArenaHandle initialize one move-only Pin. |
| invariants | Private constructor is called after checked State.pin counters; it does not increment them twice. |
| ownership | Shared state keeps slot/tuple backing alive across arena erase/destruction. |
| failure | Noexcept shared-handle move; no new allocation. |
| cost | Fixed owner/handle move. |
| Design | [docs/tuple_arenas.md](../../../../tuple_arenas.md), [docs/query_memory.md](../../../../query_memory.md), [docs/memory_reports.md](../../../../memory_reports.md), [include/crown/storage/accounted_arena.hpp](../../../../../include/crown/storage/accounted_arena.hpp) |

## B0045

[Lines 233–233](../../../../../src/storage/accounted_arena.cpp#L233); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L233-L233:sha256:18ab092441fb5c51b07f698aa739d5663bcb371f14ff0fd64f724729be1e4271
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Source usage for this declaration span in src/storage/accounted_arena.cpp; the range contains the state/helper statements shown at its exact source span. |
| inputs / outputs | Compile inputs are the listed headers and namespace/type names. This span adds no result value unless a helper/type definition listed above is instantiated or called. |
| invariants | The exact import, alias, namespace and member declarations determine the local compile/link surface; stronger behavior belongs to their constructors and operations. |
| ownership | Imports, namespace aliases, forward declarations and compile guards create no object owner. Runtime ownership starts with declared object instances and their allocator/member types. |
| failure | No explicit throw/catch appears in this exact span. Includes, constructors, inline members, static initialization and callees can still fail; follow their enclosing API contracts. |
| cost | This span changes compile/link structure and type layout. Runtime initialization, allocation, exceptions and operation work follow the declared owner/callable code; no absence is inferred from declaration syntax. |
| Design | [docs/storage.md](../../../../storage.md), [docs/tuple_arenas.md](../../../../tuple_arenas.md), [docs/query_memory.md](../../../../query_memory.md), [docs/code_specs/subsystem_contracts.md](../../../subsystem_contracts.md) |

## B0046

[Lines 234–237](../../../../../src/storage/accounted_arena.cpp#L234); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
AccountedTupleArena::Pin& AccountedTupleArena::Pin::operator=
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Transfer a pin while releasing any previous retained pin. |
| inputs / outputs | Move assignment resets old pin then adopts source state/handle; self-move leaves it unchanged. |
| invariants | Exactly one eventual unpin per successful retained Pin ownership. |
| ownership | Transfers shared State; source becomes empty. |
| failure | Noexcept cleanup and handle moves. |
| cost | Fixed bookkeeping plus old tuple release and possible O(H) final-state cleanup. |
| Design | [docs/tuple_arenas.md](../../../../tuple_arenas.md), [docs/query_memory.md](../../../../query_memory.md), [docs/memory_reports.md](../../../../memory_reports.md), [include/crown/storage/accounted_arena.hpp](../../../../../include/crown/storage/accounted_arena.hpp) |

## B0047

[Lines 238–238](../../../../../src/storage/accounted_arena.cpp#L238); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
AccountedTupleArena::Pin::~Pin()
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Release the retained tuple-generation pin. |
| inputs / outputs | Destructor delegates to reset. |
| invariants | Deletion/reclaim occurs only when last pin and live-membership rules permit. |
| ownership | Drops shared State after unpinning. |
| failure | Noexcept and nonallocating; duplicate/fabricated pins violate private ownership invariants. |
| cost | Fixed bookkeeping plus targeted payload release and possible final State/directory destruction. |
| Design | [docs/tuple_arenas.md](../../../../tuple_arenas.md), [docs/query_memory.md](../../../../query_memory.md), [docs/memory_reports.md](../../../../memory_reports.md), [include/crown/storage/accounted_arena.hpp](../../../../../include/crown/storage/accounted_arena.hpp) |

## B0048

[Lines 239–241](../../../../../src/storage/accounted_arena.cpp#L239); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void AccountedTupleArena::Pin::reset()
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Release pin retention exactly once and make the token empty. |
| inputs / outputs | A nonempty Pin unpins its handle then resets its shared State; empty is a no-op. |
| invariants | A retired last-pin row reclaims; live rows keep membership; moved-from pins are safe to reset. |
| ownership | Tuple may outlive the arena facade, while final pin release may also delete the whole State. |
| failure | Noexcept cleanup and no new allocation. |
| cost | O(1) pin bookkeeping plus possible tuple release and O(slot high-water) final-state destruction. |
| Design | [docs/tuple_arenas.md](../../../../tuple_arenas.md), [docs/query_memory.md](../../../../query_memory.md), [docs/storage_journal.md](../../../../storage_journal.md) |

## B0049

[Lines 242–244](../../../../../src/storage/accounted_arena.cpp#L242); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
ArenaHandle AccountedTupleArena::Pin::handle()
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Read the retained slot identity independent of current live membership. |
| inputs / outputs | Valid Pin returns its original owner/slot/generation. |
| invariants | Handle remains the same after erase; returned handle does not itself retain the tuple. |
| ownership | Inline identity value; Pin is the retaining owner. |
| failure | Empty/moved-from/reset Pin throws invalid_pin. |
| cost | Fixed retained-owner check/copy. |
| Design | [docs/tuple_arenas.md](../../../../tuple_arenas.md), [docs/query_memory.md](../../../../query_memory.md), [docs/memory_reports.md](../../../../memory_reports.md), [include/crown/storage/accounted_arena.hpp](../../../../../include/crown/storage/accounted_arena.hpp) |

## B0050

[Lines 245–247](../../../../../src/storage/accounted_arena.cpp#L245); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
const AccountedTuple& AccountedTupleArena::Pin::get() const &
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Borrow a retained tuple even after membership deletion. |
| inputs / outputs | Valid lvalue Pin returns the tuple in its retained slot. |
| invariants | Pin ownership proves the generation/payload cannot be reused; this getter deliberately does not require live membership. |
| ownership | Borrow survives arena erase/destruction but ends when the Pin is reset/destroyed and no other retention remains. |
| failure | Invalid Pin throws; valid retained slot access requires no redundant contains/live check. |
| cost | Fixed slot addressing, no scalar copy, allocation or directory scan. |
| Design | [docs/tuple_arenas.md](../../../../tuple_arenas.md), [docs/query_memory.md](../../../../query_memory.md), [docs/memory_reports.md](../../../../memory_reports.md), [include/crown/storage/accounted_arena.hpp](../../../../../include/crown/storage/accounted_arena.hpp) |

## B0051

[Lines 248–248](../../../../../src/storage/accounted_arena.cpp#L248); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
bool AccountedTupleArena::Pin::is_live()
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Distinguish retained payload from current live membership. |
| inputs / outputs | Valid Pin returns State.contains for its original handle. |
| invariants | A valid Pin may return false after erase/clear; retained payload still exists. |
| ownership | Borrows retained state; does not create another pin. |
| failure | Empty Pin throws invalid_pin. |
| cost | Fixed owner/slot/generation checks. |
| Design | [docs/tuple_arenas.md](../../../../tuple_arenas.md), [docs/query_memory.md](../../../../query_memory.md), [docs/memory_reports.md](../../../../memory_reports.md), [include/crown/storage/accounted_arena.hpp](../../../../../include/crown/storage/accounted_arena.hpp) |

## B0053

[Lines 250–295](../../../../../src/storage/accounted_arena.cpp#L250); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void AccountedTupleArena::check_invariants()
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Reconcile arena links, generations, pin counts, tuple validity and actual allocation partitions. |
| inputs / outputs | Valid arena passes a diagnostic over free/live lists, every slot, memory report and account ledger. |
| invariants | Bounded list walks detect cycles; counted slot categories/pins must agree with maintained statistics and lifetime partitions. |
| ownership | Borrows existing slot/account state, fixed scratch only. |
| failure | Reports fixed arena/resource contract failures; does not repair or publish memberships. |
| cost | O(slot high-water + all account allocations + tuple field/deep equality validation), including the explicit memory-statistics and account diagnostic scans. |
| Design | [docs/tuple_arenas.md](../../../../tuple_arenas.md), [docs/query_memory.md](../../../../query_memory.md), [docs/storage_journal.md](../../../../storage_journal.md) |

## B0054

[Lines 296–296](../../../../../src/storage/accounted_arena.cpp#L296); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L296-L296:sha256:412ca345ccf75bf9c0806bce695be8de808b79984251a7a54d202cf6101dd451
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Close the \`namespace crown::storage\` scope at this exact source boundary. |
| inputs / outputs | This token introduces no callable inputs or outputs. Declarations inside \`namespace crown::storage\` define the available names, members and operations. |
| invariants | The closing brace matches the opening \`namespace crown::storage\` at its lexical source position in src/storage/accounted_arena.cpp; it preserves C++ namespace/type nesting. |
| ownership | The closing delimiter creates no owner. Types closed by \`namespace crown::storage\` retain the lifetimes and allocator rules of their own fields and operations. |
| failure | No failure path executes at this closing delimiter. Failure and cleanup behavior belong to enclosed functions and owning types. |
| cost | The delimiter itself performs no runtime work; the enclosed initializers, methods and destructors carry their own costs. |
| Design | [docs/storage.md](../../../../storage.md), [docs/tuple_arenas.md](../../../../tuple_arenas.md), [docs/query_memory.md](../../../../query_memory.md), [docs/code_specs/subsystem_contracts.md](../../../subsystem_contracts.md) |
