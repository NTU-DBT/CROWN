# `src/planner/selection_detail.hpp` — block usage map

[Source](../../../../../src/planner/selection_detail.hpp) · [Source index](../../../README.md) · [Subsystem contracts](../../../subsystem_contracts.md) · [Reviewed primitives](../../../primitives.md)

Rank or select within a checked candidate family using exact binding, explicit evidence and bounded local score policies.

Snapshot SHA-256: `f767d14d27fe3e50269a94ea72530ba44d5fe5eaa114f772a416c34ec765f160`. 229 lines partitioned into 39 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [ranking](../../../subsystem_contracts.md#ranking). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/ranking.md](../../../../ranking.md), [docs/selection.md](../../../../selection.md), [docs/selection_binding.md](../../../../selection_binding.md), [docs/ranking_accounting.md](../../../../ranking_accounting.md), [docs/selection_accounting.md](../../../../selection_accounting.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–13](../../../../../src/planner/selection_detail.hpp#L1) | Imports dependencies; guards repeated header inclusion; declares namespace scope; declares values/defaults or compile-time conditions. | source comment (unverified): // Attribute selection result, cache and scratch allocations to the selection capture owner. · [reviewed contract](#b0001) |
| [B0002 · 14–16](../../../../../src/planner/selection_detail.hpp#L14) | Callable definition: template&lt;class T&gt; resource::OwnerAllocator&lt;T&gt; selection_allocator(const resource::MemoryAccount& account) | calls ; returns resource::OwnerAllocator&lt;T&gt;(account,resource::MemoryPurpose::capture,selection_memory_owner); source comment (unverified): // Build a transferable selection allocator retaining the supplied account. See · [reviewed contract](#b0002) |
| [B0003 · 17–18](../../../../../src/planner/selection_detail.hpp#L17) | Explanatory comments or spacing. | source comment (unverified): // Carry fixed selection stop/resource/component diagnostics through unwinding. See · [reviewed contract](#b0003) |
| [B0004 · 19–24](../../../../../src/planner/selection_detail.hpp#L19) | Type/record definition: struct Failure | source comment (unverified): // Carry fixed selection stop/resource/component diagnostics through unwinding. See · [reviewed contract](#b0004) |
| [B0005 · 25–47](../../../../../src/planner/selection_detail.hpp#L25) | declares types or opens a type body; declares callable signatures; declares values/defaults or compile-time conditions. | guard void require(bool, Stop = Stop::internal_error);; source comment (unverified): // Own one aggregate logical-processing grant and optional active timer. See · [reviewed contract](#b0005) |
| [B0006 · 48–52](../../../../../src/planner/selection_detail.hpp#L48) | Callable definition: template&lt;class T&gt; void vector(std::size_t n) | calls cells, bytes; source comment (unverified): // Admit logical vector cells and element-storage bytes before allocation. See · [reviewed contract](#b0006) |
| [B0007 · 53–54](../../../../../src/planner/selection_detail.hpp#L53) | Explanatory comments or spacing. | source comment (unverified): // Run a synchronous borrowed C02 visitor under the same cumulative Usage. See · [reviewed contract](#b0007) |
| [B0008 · 55–64](../../../../../src/planner/selection_detail.hpp#L55) | Callable definition: template&lt;class Function&gt; void borrowed(Function&& function) | calls sample, reset, inner, function; source comment (unverified): // Run a synchronous borrowed C02 visitor under the same cumulative Usage. See · [reviewed contract](#b0008) |
| [B0009 · 65–71](../../../../../src/planner/selection_detail.hpp#L65) | declares values/defaults or compile-time conditions. | source comment (unverified): // The stopped outer timer measures the whole synchronous delegated phase. · [reviewed contract](#b0009) |
| [B0010 · 72–72](../../../../../src/planner/selection_detail.hpp#L72) | Type/record definition: enum class Origin | source comment (unverified): // Scope artifact evidence origin for cache-key reproduction. See docs/selection_binding.md. · [reviewed contract](#b0010) |
| [B0011 · 73–74](../../../../../src/planner/selection_detail.hpp#L73) | Explanatory comments or spacing. | source comment (unverified): // Own one FIFO key and complete native plan with logical retention charge. See · [reviewed contract](#b0011) |
| [B0012 · 75–82](../../../../../src/planner/selection_detail.hpp#L75) | Type/record definition: struct Entry | source comment (unverified): // Own one FIFO key and complete native plan with logical retention charge. See · [reviewed contract](#b0012) |
| [B0013 · 83–87](../../../../../src/planner/selection_detail.hpp#L83) | declares types or opens a type body. | source comment (unverified): // Each FIFO node keeps its allocating query account. Splicing never transfers a · [reviewed contract](#b0013) |
| [B0014 · 88–95](../../../../../src/planner/selection_detail.hpp#L88) | Type/record definition: public: struct Iterator | returns *value; value · [reviewed contract](#b0014) |
| [B0015 · 96–99](../../../../../src/planner/selection_detail.hpp#L96) | declares callable signatures; declares values/defaults or compile-time conditions. | source comment (unverified): // Transfer a chain while resetting source tail/count. See docs/selection_accounting.md. · [reviewed contract](#b0015) |
| [B0016 · 100–101](../../../../../src/planner/selection_detail.hpp#L100) | Callable definition: Entries(Entries&& other) noexcept :first_(std::move(other.first_)),last_(std::exchange(other.last_,nullptr)),size_(std::exchange(… | calls first_, std::move, last_, std::exchange; source comment (unverified): // Transfer a chain while resetting source tail/count. See docs/selection_accounting.md. · [reviewed contract](#b0016) |
| [B0017 · 102–102](../../../../../src/planner/selection_detail.hpp#L102) | Callable definition: ~Entries() | calls clear · [reviewed contract](#b0017) |
| [B0018 · 103–103](../../../../../src/planner/selection_detail.hpp#L103) | Callable definition: std::size_t size() const noexcept | calls ; returns size_ · [reviewed contract](#b0018) |
| [B0019 · 104–104](../../../../../src/planner/selection_detail.hpp#L104) | Callable definition: bool empty() const noexcept | calls ; returns !first_ · [reviewed contract](#b0019) |
| [B0020 · 105–105](../../../../../src/planner/selection_detail.hpp#L105) | Callable definition: Iterator begin() const noexcept | calls get; returns {first_.get()} · [reviewed contract](#b0020) |
| [B0021 · 106–106](../../../../../src/planner/selection_detail.hpp#L106) | Callable definition: Iterator end() const noexcept | calls ; returns {} · [reviewed contract](#b0021) |
| [B0022 · 107–107](../../../../../src/planner/selection_detail.hpp#L107) | Explanatory comments or spacing. | source comment (unverified): // Link one prepared detached node at the FIFO tail. See docs/selection_accounting.md. · [reviewed contract](#b0022) |
| [B0023 · 108–111](../../../../../src/planner/selection_detail.hpp#L108) | Callable definition: void push_back(resource::AccountedUnique&lt;Entry&gt; entry) noexcept | calls get, std::move; growth push_back; source comment (unverified): // Link one prepared detached node at the FIFO tail. See docs/selection_accounting.md. · [reviewed contract](#b0023) |
| [B0024 · 112–113](../../../../../src/planner/selection_detail.hpp#L112) | Explanatory comments or spacing. | source comment (unverified): // Retire a funded front node into another list without destruction. See · [reviewed contract](#b0024) |
| [B0025 · 114–117](../../../../../src/planner/selection_detail.hpp#L114) | Callable definition: void move_front_to(Entries& destination) noexcept | calls std::move, push_back; growth push_back; source comment (unverified): // Retire a funded front node into another list without destruction. See · [reviewed contract](#b0025) |
| [B0026 · 118–118](../../../../../src/planner/selection_detail.hpp#L118) | Explanatory comments or spacing. | source comment (unverified): // Splice a disjoint prepared list onto this FIFO. See docs/selection_accounting.md. · [reviewed contract](#b0026) |
| [B0027 · 119–123](../../../../../src/planner/selection_detail.hpp#L119) | Callable definition: void append(Entries& other) noexcept | calls empty, std::move, std::exchange; source comment (unverified): // Splice a disjoint prepared list onto this FIFO. See docs/selection_accounting.md. · [reviewed contract](#b0027) |
| [B0028 · 124–125](../../../../../src/planner/selection_detail.hpp#L124) | Explanatory comments or spacing. | source comment (unverified): // Destroy FIFO nodes iteratively while preserving no-allocation cleanup. See · [reviewed contract](#b0028) |
| [B0029 · 126–129](../../../../../src/planner/selection_detail.hpp#L126) | Callable definition: void clear() noexcept | calls std::move; 1 loop sites; source comment (unverified): // Destroy FIFO nodes iteratively while preserving no-allocation cleanup. See · [reviewed contract](#b0029) |
| [B0030 · 130–136](../../../../../src/planner/selection_detail.hpp#L130) | Member/declaration region. | source comment (unverified): // Own cache configuration, committed statistics and FIFO entries. See · [reviewed contract](#b0030) |
| [B0031 · 137–142](../../../../../src/planner/selection_detail.hpp#L137) | Type/record definition: struct CacheData | source comment (unverified): // Own cache configuration, committed statistics and FIFO entries. See · [reviewed contract](#b0031) |
| [B0032 · 143–144](../../../../../src/planner/selection_detail.hpp#L143) | Explanatory comments or spacing. | source comment (unverified): // Own all unpublished/published selection context in one account-backed backing object. See · [reviewed contract](#b0032) |
| [B0033 · 145–165](../../../../../src/planner/selection_detail.hpp#L145) | Type/record definition: struct SelectionData | source comment (unverified): // Own all unpublished/published selection context in one account-backed backing object. See · [reviewed contract](#b0033) |
| [B0034 · 166–169](../../../../../src/planner/selection_detail.hpp#L166) | Type/record definition: struct Factory | returns Selection(std::move(data)); value ? value-&gt;data_.get() : nullptr · [reviewed contract](#b0034) |
| [B0035 · 170–171](../../../../../src/planner/selection_detail.hpp#L170) | Explanatory comments or spacing. | source comment (unverified): // Keep speculative result/cache statistics and funded list changes private. See · [reviewed contract](#b0035) |
| [B0036 · 172–180](../../../../../src/planner/selection_detail.hpp#L172) | Type/record definition: struct Prepared | source comment (unverified): // Keep speculative result/cache statistics and funded list changes private. See · [reviewed contract](#b0036) |
| [B0037 · 181–207](../../../../../src/planner/selection_detail.hpp#L181) | declares callable signatures; declares values/defaults or compile-time conditions. | source comment (unverified): // Diagnostic record encoders used by private framing/mutation consumers. They · [reviewed contract](#b0037) |
| [B0038 · 208–228](../../../../../src/planner/selection_detail.hpp#L208) | Type/record definition: struct Operation | source comment (unverified): // Own one synchronous selection transaction over caller inputs. See docs/selection.md. · [reviewed contract](#b0038) |
| [B0039 · 229–229](../../../../../src/planner/selection_detail.hpp#L229) | Closes surrounding scope/type. | source comment (unverified): // namespace crown::planner::selection::detail · [reviewed contract](#b0039) |

## B0001

[Lines 1–13](../../../../../src/planner/selection_detail.hpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
inline constexpr resource::MemoryAttribution selection_memory_owner
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Attribute selection result, cache and scratch allocations to the selection capture owner. |
| inputs / outputs | Fixed capture-kind owner number 12. |
| invariants | Attribution labels allocation partition, not a new allowance. |
| ownership | Value metadata copied into allocators. |
| failure | Consumers require valid account/purpose. |
| cost | Fixed scalar metadata. |
| Design | [docs/query_memory.md §Boundaries](../../../../query_memory.md) |

## B0002

[Lines 14–16](../../../../../src/planner/selection_detail.hpp#L14); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
template<class T> resource::OwnerAllocator<T> selection_allocator(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Build a transferable selection allocator retaining the supplied account. |
| inputs / outputs | MemoryAccount to capture-purpose OwnerAllocator&lt;T&gt;. |
| invariants | Copies/assignments preserve original account and attribution; no refill is created. |
| ownership | Allocator retains account control. |
| failure | Invalid account/purpose contract throws MemoryFailure. |
| cost | Handle metadata setup; real allocation happens in containers. |
| Design | [docs/query_memory.md §Boundaries](../../../../query_memory.md) |

## B0003

[Lines 17–18](../../../../../src/planner/selection_detail.hpp#L17); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L17-L18:sha256:f94494b9dd607f69728f5727a64f7805f3f5747350031949c99b58baa3090329
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Use the adjacent note for Failure: Carry fixed selection stop/resource/component diagnostics through unwinding. Confirm behavior against the declaration and implementation; comment text alone does not enforce or prove it. |
| inputs / outputs | This comment has no inputs or outputs. It accompanies Failure; use the adjacent declaration and implementation for the actual values and result. |
| invariants | This is static guidance only. The comment cannot alter state or guarantee that its wording holds. |
| ownership | The note owns no storage and changes no lifetime; ownership and borrowing for Failure come from its actual types and implementation. |
| failure | Reading the comment has no runtime failure path. Compile or link errors, exceptions, and resource stops belong to the adjacent code. |
| cost | The comment adds no runtime instructions, allocation, clock read, counter debit, or engine hook; only source-text processing is added. |
| Design | [src/planner/selection_detail.hpp](../../../../../src/planner/selection_detail.hpp), [docs/selection.md](../../../../selection.md), [docs/selection_accounting.md](../../../../selection_accounting.md), [docs/selection_binding.md](../../../../selection_binding.md) |

## B0004

[Lines 19–24](../../../../../src/planner/selection_detail.hpp#L19); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct Failure {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Carry fixed selection stop/resource/component diagnostics through unwinding. |
| inputs / outputs | Stop, Resource, optional rank::Stop and reasons. |
| invariants | No owning message or partial Selection is attached. |
| ownership | Value-only exception payload. |
| failure | Caught by pure entry point without mutating cache. |
| cost | Fixed payload; C++ exception-runtime storage remains separate. |
| Design | [docs/selection.md](../../../../selection.md), [docs/selection_accounting.md §Atomic publication](../../../../selection_accounting.md) |

## B0005

[Lines 25–47](../../../../../src/planner/selection_detail.hpp#L25); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct Budget {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Own one aggregate logical-processing grant and optional active timer. |
| inputs / outputs | Limits, cumulative Usage, receiving MemoryAccount and timer state. |
| invariants | Logical counters are not requested-byte accounting; accepted prior debits are not rolled back on later failure. |
| ownership | Shares receiving account; owns scalar usage/time. |
| failure | Failure throws fixed dimension diagnostics before disallowed additions. |
| cost | Sampling is optional; actual allocator/container work stays separate. |
| Design | [docs/selection_accounting.md §Exact charge primitives](../../../../selection_accounting.md), [docs/selection_accounting.md §Delegated budget equation](../../../../selection_accounting.md), [docs/selection_accounting.md §Optional active time](../../../../selection_accounting.md) |

## B0006

[Lines 48–52](../../../../../src/planner/selection_detail.hpp#L48); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
template<class T> void vector(std::size_t n) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Admit logical vector cells and element-storage bytes before allocation. |
| inputs / outputs | Charges n cells then n*sizeof(T) payload after multiplication check. |
| invariants | Byte rejection may leave accepted cell debit; capacity/control-block overhead differs from modeled bytes. |
| ownership | Mutates Budget counters only. |
| failure | Overflow/cap throws Failure before container growth at callers. |
| cost | Fixed arithmetic charges; actual construction/growth is separate. |
| Design | [docs/selection_accounting.md §Exact charge primitives](../../../../selection_accounting.md) |

## B0007

[Lines 53–54](../../../../../src/planner/selection_detail.hpp#L53); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L53-L54:sha256:0e256bfc0dddfb989f923e493d568744533330acd9cfa3a099a1b7c0d910e811
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Use the adjacent note for sample: Run a synchronous borrowed C02 visitor under the same cumulative Usage. Confirm behavior against the declaration and implementation; comment text alone does not enforce or prove it. |
| inputs / outputs | This comment has no inputs or outputs. It accompanies sample; use the adjacent declaration and implementation for the actual values and result. |
| invariants | This is static guidance only. The comment cannot alter state or guarantee that its wording holds. |
| ownership | The note owns no storage and changes no lifetime; ownership and borrowing for sample come from its actual types and implementation. |
| failure | Reading the comment has no runtime failure path. Compile or link errors, exceptions, and resource stops belong to the adjacent code. |
| cost | The comment adds no runtime instructions, allocation, clock read, counter debit, or engine hook; only source-text processing is added. |
| Design | [src/planner/selection_detail.hpp](../../../../../src/planner/selection_detail.hpp), [docs/selection.md](../../../../selection.md), [docs/selection_accounting.md](../../../../selection_accounting.md), [docs/selection_binding.md](../../../../selection_binding.md) |

## B0008

[Lines 55–64](../../../../../src/planner/selection_detail.hpp#L55); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
template<class Function> void borrowed(Function&& function) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Run a synchronous borrowed C02 visitor under the same cumulative Usage. |
| inputs / outputs | Samples outer timer, disables inner timer, delegates callback, replaces Usage even on exception, then samples again on success. |
| invariants | No fresh grant or duplicated preparation charge; outer interval covers callback time. |
| ownership | Borrows callback for call; inner budget shares receiving account. |
| failure | Catch/rethrow preserves component counters and failure order; it is necessary, not a redundant conversion. |
| cost | Callback traversal/allocations plus optional outer samples; no independent clock loop. |
| Design | [docs/selection_accounting.md §Delegated budget equation](../../../../selection_accounting.md), [docs/selection_accounting.md §Optional active time](../../../../selection_accounting.md) |

## B0009

[Lines 65–71](../../../../../src/planner/selection_detail.hpp#L65); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
rank::Limits begin_delegate(const rank::Usage& preparation = {});
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Pair delegated remaining grants with one outer usage/time merge. |
| inputs / outputs | begin returns P+(L-U); end consumes returned Usage and the same preparation. |
| invariants | Caller uses the same Evidence P and merges once; no independent refill or overlapping elapsed addition. |
| ownership | Only value limits/usage cross the call; outer account remains retained. |
| failure | Throwing checks preserve partial diagnostic accounting; selection transaction remains uncommitted. |
| cost | Eight scalar dimensions and optional wall samples plus delegated work. |
| Design | [docs/selection_accounting.md §Delegated budget equation](../../../../selection_accounting.md), [docs/selection_accounting.md §Optional active time](../../../../selection_accounting.md) |

## B0010

[Lines 72–72](../../../../../src/planner/selection_detail.hpp#L72); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
enum class Origin {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Scope artifact evidence origin for cache-key reproduction. |
| inputs / outputs | Absent/as-of/physical/delta/session tag. |
| invariants | Origin is not owner freshness or deployment authority. |
| ownership | Scalar value. |
| failure | Unknown internal origins are not public input. |
| cost | Fixed tag encoding. |
| Design | [docs/selection_binding.md §Physical source and artifact frames](../../../../selection_binding.md) |

## B0011

[Lines 73–74](../../../../../src/planner/selection_detail.hpp#L73); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L73-L74:sha256:a36880c6c6f7068fbb6da3e360dd70fc79f60eaf165abea2cde541d89cef6791
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Use the adjacent note for Entry: Own one FIFO key and complete native plan with logical retention charge. Confirm behavior against the declaration and implementation; comment text alone does not enforce or prove it. |
| inputs / outputs | This comment has no inputs or outputs. It accompanies Entry; use the adjacent declaration and implementation for the actual values and result. |
| invariants | This is static guidance only. The comment cannot alter state or guarantee that its wording holds. |
| ownership | The note owns no storage and changes no lifetime; ownership and borrowing for Entry come from its actual types and implementation. |
| failure | Reading the comment has no runtime failure path. Compile or link errors, exceptions, and resource stops belong to the adjacent code. |
| cost | The comment adds no runtime instructions, allocation, clock read, counter debit, or engine hook; only source-text processing is added. |
| Design | [src/planner/selection_detail.hpp](../../../../../src/planner/selection_detail.hpp), [docs/selection.md](../../../../selection.md), [docs/selection_accounting.md](../../../../selection_accounting.md), [docs/selection_binding.md](../../../../selection_binding.md) |

## B0012

[Lines 75–82](../../../../../src/planner/selection_detail.hpp#L75); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct Entry {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Own one FIFO key and complete native plan with logical retention charge. |
| inputs / outputs | SelectionText key, CompiledProgram, payload and next AccountedUnique. |
| invariants | Key/plan are installed only after a fresh whole-set decision; next links retain their original account. |
| ownership | Key/node use allocating query account; plan shares its existing funded program. |
| failure | Unpublished construction failure leaves cache untouched. |
| cost | Key bytes plus shared program and node framing; final plan release may be large. |
| Design | [docs/selection_accounting.md §Atomic publication](../../../../selection_accounting.md), [docs/query_memory.md §Boundaries](../../../../query_memory.md) |

```text
Entry(const resource::MemoryAccount& account,std::string_view k,CompiledProgram p,std::uint64_t bytes)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Prepare a private account-backed cache node payload. |
| inputs / outputs | Copies key bytes, moves compiled handle, records modeled payload. |
| invariants | No cache list/statistic mutation occurs during construction. |
| ownership | Owns key under provided account and shares plan backing. |
| failure | Text/account allocation failure destroys unexposed partial state. |
| cost | Key copy/allocation plus handle transfer. |
| Design | [docs/selection_accounting.md §Atomic publication](../../../../selection_accounting.md), [docs/query_memory.md §Boundaries](../../../../query_memory.md) |

## B0013

[Lines 83–87](../../../../../src/planner/selection_detail.hpp#L83); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
class Entries {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Manage account-preserving FIFO links without recursive chain teardown. |
| inputs / outputs | Owns first/last/size and supports append, front transfer and iterative clear. |
| invariants | Lists/nodes must be valid, disjoint for append, and size additions representable. Tail next is empty. |
| ownership | Each AccountedUnique node retains its own allocator/account. |
| failure | Private no-throw link operations rely on prepared invariants. |
| cost | Link operations are fixed pointer work; clear releases all node/key/plan payloads. |
| Design | [docs/selection_accounting.md §Atomic publication](../../../../selection_accounting.md), [docs/query_memory.md §Boundaries](../../../../query_memory.md) |

## B0014

[Lines 88–95](../../../../../src/planner/selection_detail.hpp#L88); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct Iterator {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Borrow a FIFO node for exclusive synchronous traversal. |
| inputs / outputs | Raw const Entry pointer with dereference, arrow, next and equality. |
| invariants | Dereference/increment require non-end; mutation/clear/eviction invalidates removed-node borrows. |
| ownership | Owns no entry or plan. |
| failure | No bounds/lifetime checks. |
| cost | Fixed pointer navigation; payload access does not copy. |
| Design | [docs/selection_accounting.md §Atomic publication](../../../../selection_accounting.md) |

```text
const Entry& operator*() const noexcept {return *value;}
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Borrow the current live cache entry. |
| inputs / outputs | Returns const reference from non-null iterator. |
| invariants | Owner/list must retain this node. |
| ownership | No ownership transfer. |
| failure | Noexcept precondition; end dereference invalid. |
| cost | Reference return. |
| Design | [docs/selection_accounting.md §Atomic publication](../../../../selection_accounting.md) |

```text
const Entry* operator->() const noexcept {return value;}
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Expose the current borrowed node address. |
| inputs / outputs | Returns raw const pointer, possibly null at end. |
| invariants | Pointer does not extend node lifetime. |
| ownership | Borrow only. |
| failure | Noexcept; caller checks end before use. |
| cost | Pointer copy. |
| Design | [docs/selection_accounting.md §Atomic publication](../../../../selection_accounting.md) |

```text
Iterator& operator++() noexcept {value=value->next.get();return *this;}
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Advance through the current node next link. |
| inputs / outputs | Requires non-end and returns this iterator. |
| invariants | Removed nodes cannot be advanced safely. |
| ownership | Borrows list links. |
| failure | Noexcept with valid node precondition. |
| cost | One pointer load. |
| Design | [docs/selection_accounting.md §Atomic publication](../../../../selection_accounting.md) |

```text
bool operator==(const Iterator&) const=default;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Compare iterator positions by node address. |
| inputs / outputs | Memberwise raw-pointer equality. |
| invariants | Equal positions imply no content/key equality. |
| ownership | Borrows scalar values. |
| failure | No validation. |
| cost | Fixed pointer comparison. |
| Design | [docs/selection_accounting.md §Atomic publication](../../../../selection_accounting.md) |

## B0015

[Lines 96–99](../../../../../src/planner/selection_detail.hpp#L96); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Entries()=default;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Create an empty noncopyable FIFO owner. |
| inputs / outputs | Adjacent deleted copy operations prevent duplicate chain ownership. |
| invariants | first/last empty and size zero; no implicit move assignment is declared. |
| ownership | Owns no node initially. |
| failure | Copy misuse is a compile-time error. |
| cost | Empty header setup; no node allocation. |
| Design | [docs/selection_accounting.md §Atomic publication](../../../../selection_accounting.md) |

## B0016

[Lines 100–101](../../../../../src/planner/selection_detail.hpp#L100); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Entries(Entries&& other) noexcept
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Transfer a chain while resetting source tail/count. |
| inputs / outputs | Moves first_, exchanges last_/size_ to empty. |
| invariants | Node/control-block addresses and original accounts remain unchanged. |
| ownership | Transfers unique chain ownership. |
| failure | Noexcept; source becomes empty. |
| cost | Fixed pointer/count operations. |
| Design | [docs/selection_accounting.md §Atomic publication](../../../../selection_accounting.md) |

## B0017

[Lines 102–102](../../../../../src/planner/selection_detail.hpp#L102); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
~Entries() {clear();}
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Release the FIFO iteratively on owner destruction. |
| inputs / outputs | Calls clear on all retained nodes. |
| invariants | Each next owner is detached before current node destruction, avoiding recursive chain release. |
| ownership | Drops node/key/program ownership. |
| failure | Noexcept under contained destructors. |
| cost | Linear nodes plus actual key/native-program final teardown. |
| Design | [docs/selection_accounting.md §Atomic publication](../../../../selection_accounting.md) |

## B0018

[Lines 103–103](../../../../../src/planner/selection_detail.hpp#L103); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::size_t size() const noexcept {return size_;}
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Read committed list length. |
| inputs / outputs | Returns saved size. |
| invariants | List invariants are maintained by private commit/preparation code. |
| ownership | Scalar/iterator result owns no node. |
| failure | Noexcept; caller retains list lifetime. |
| cost | Fixed saved metadata access. |
| Design | [docs/selection_accounting.md §Atomic publication](../../../../selection_accounting.md) |

## B0019

[Lines 104–104](../../../../../src/planner/selection_detail.hpp#L104); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
bool empty() const noexcept {return !first_;}
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Read whether the list owns a first node. |
| inputs / outputs | Returns pointer emptiness. |
| invariants | List invariants are maintained by private commit/preparation code. |
| ownership | Scalar/iterator result owns no node. |
| failure | Noexcept; caller retains list lifetime. |
| cost | Fixed saved metadata access. |
| Design | [docs/selection_accounting.md §Atomic publication](../../../../selection_accounting.md) |

## B0020

[Lines 105–105](../../../../../src/planner/selection_detail.hpp#L105); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Iterator begin() const noexcept {return {first_.get()};}
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Borrow the first FIFO node position. |
| inputs / outputs | Returns raw-node iterator. |
| invariants | List invariants are maintained by private commit/preparation code. |
| ownership | Scalar/iterator result owns no node. |
| failure | Noexcept; caller retains list lifetime. |
| cost | Fixed saved metadata access. |
| Design | [docs/selection_accounting.md §Atomic publication](../../../../selection_accounting.md) |

## B0021

[Lines 106–106](../../../../../src/planner/selection_detail.hpp#L106); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Iterator end() const noexcept {return {};}
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Create the null sentinel for FIFO traversal. |
| inputs / outputs | Returns empty iterator. |
| invariants | List invariants are maintained by private commit/preparation code. |
| ownership | Scalar/iterator result owns no node. |
| failure | Noexcept; caller retains list lifetime. |
| cost | Fixed saved metadata access. |
| Design | [docs/selection_accounting.md §Atomic publication](../../../../selection_accounting.md) |

## B0022

[Lines 107–107](../../../../../src/planner/selection_detail.hpp#L107); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L107-L107:sha256:3d724f57922f79222227ac811ff30911febf55799177c9660b1e658a501dad8d
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Use the adjacent note for push_back: Link one prepared detached node at the FIFO tail. Confirm behavior against the declaration and implementation; comment text alone does not enforce or prove it. |
| inputs / outputs | This comment has no inputs or outputs. It accompanies push_back; use the adjacent declaration and implementation for the actual values and result. |
| invariants | This is static guidance only. The comment cannot alter state or guarantee that its wording holds. |
| ownership | The note owns no storage and changes no lifetime; ownership and borrowing for push_back come from its actual types and implementation. |
| failure | Reading the comment has no runtime failure path. Compile or link errors, exceptions, and resource stops belong to the adjacent code. |
| cost | The comment adds no runtime instructions, allocation, clock read, counter debit, or engine hook; only source-text processing is added. |
| Design | [src/planner/selection_detail.hpp](../../../../../src/planner/selection_detail.hpp), [docs/selection.md](../../../../selection.md), [docs/selection_accounting.md](../../../../selection_accounting.md), [docs/selection_binding.md](../../../../selection_binding.md) |

## B0023

[Lines 108–111](../../../../../src/planner/selection_detail.hpp#L108); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void push_back(resource::AccountedUnique<Entry> entry) noexcept {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Link one prepared detached node at the FIFO tail. |
| inputs / outputs | Requires non-null node with empty next and representable size increment. |
| invariants | No allocation or plan destruction occurs when valid tail/first destinations are empty. |
| ownership | Transfers AccountedUnique without changing account. |
| failure | Noexcept private invariant boundary. |
| cost | Fixed link/count updates. |
| Design | [docs/selection_accounting.md §Atomic publication](../../../../selection_accounting.md) |

## B0024

[Lines 112–113](../../../../../src/planner/selection_detail.hpp#L112); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L112-L113:sha256:c97dd881499026175a9c6e0b90ad564ddb7d7673f0b1060275c5e9bd7805a632
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Use the adjacent note for move_front_to: Retire a funded front node into another list without destruction. Confirm behavior against the declaration and implementation; comment text alone does not enforce or prove it. |
| inputs / outputs | This comment has no inputs or outputs. It accompanies move_front_to; use the adjacent declaration and implementation for the actual values and result. |
| invariants | This is static guidance only. The comment cannot alter state or guarantee that its wording holds. |
| ownership | The note owns no storage and changes no lifetime; ownership and borrowing for move_front_to come from its actual types and implementation. |
| failure | Reading the comment has no runtime failure path. Compile or link errors, exceptions, and resource stops belong to the adjacent code. |
| cost | The comment adds no runtime instructions, allocation, clock read, counter debit, or engine hook; only source-text processing is added. |
| Design | [src/planner/selection_detail.hpp](../../../../../src/planner/selection_detail.hpp), [docs/selection.md](../../../../selection.md), [docs/selection_accounting.md](../../../../selection_accounting.md), [docs/selection_binding.md](../../../../selection_binding.md) |

## B0025

[Lines 114–117](../../../../../src/planner/selection_detail.hpp#L114); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void move_front_to(Entries& destination) noexcept {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Retire a funded front node into another list without destruction. |
| inputs / outputs | Detaches first next link, updates size/tail and pushes detached node. |
| invariants | Source is nonempty; destination is a valid distinct retirement list. |
| ownership | Transfers original node/account ownership. |
| failure | Noexcept prepared-commit operation. |
| cost | Fixed pointer/count moves. |
| Design | [docs/selection_accounting.md §Atomic publication](../../../../selection_accounting.md) |

## B0026

[Lines 118–118](../../../../../src/planner/selection_detail.hpp#L118); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L118-L118:sha256:977371c112d7f909a6f807181edc66845a28bbb4a40d005523050e141ac99a77
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Use the adjacent note for append: Splice a disjoint prepared list onto this FIFO. Confirm behavior against the declaration and implementation; comment text alone does not enforce or prove it. |
| inputs / outputs | This comment has no inputs or outputs. It accompanies append; use the adjacent declaration and implementation for the actual values and result. |
| invariants | This is static guidance only. The comment cannot alter state or guarantee that its wording holds. |
| ownership | The note owns no storage and changes no lifetime; ownership and borrowing for append come from its actual types and implementation. |
| failure | Reading the comment has no runtime failure path. Compile or link errors, exceptions, and resource stops belong to the adjacent code. |
| cost | The comment adds no runtime instructions, allocation, clock read, counter debit, or engine hook; only source-text processing is added. |
| Design | [src/planner/selection_detail.hpp](../../../../../src/planner/selection_detail.hpp), [docs/selection.md](../../../../selection.md), [docs/selection_accounting.md](../../../../selection_accounting.md), [docs/selection_binding.md](../../../../selection_binding.md) |

## B0027

[Lines 119–123](../../../../../src/planner/selection_detail.hpp#L119); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void append(Entries& other) noexcept {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Splice a disjoint prepared list onto this FIFO. |
| inputs / outputs | Empty source returns; otherwise moves chain/tail/count and empties other. |
| invariants | Self-append is invalid; total size must fit. |
| ownership | Node accounts and payload addresses remain unchanged. |
| failure | Noexcept with valid disjoint lists. |
| cost | Fixed linking independent of chain length. |
| Design | [docs/selection_accounting.md §Atomic publication](../../../../selection_accounting.md) |

## B0028

[Lines 124–125](../../../../../src/planner/selection_detail.hpp#L124); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L124-L125:sha256:a318e466000898b7a68fb549a10393e84d982a0f4746b5059858d7e71ba87537
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Use the adjacent note for clear: Destroy FIFO nodes iteratively while preserving no-allocation cleanup. Confirm behavior against the declaration and implementation; comment text alone does not enforce or prove it. |
| inputs / outputs | This comment has no inputs or outputs. It accompanies clear; use the adjacent declaration and implementation for the actual values and result. |
| invariants | This is static guidance only. The comment cannot alter state or guarantee that its wording holds. |
| ownership | The note owns no storage and changes no lifetime; ownership and borrowing for clear come from its actual types and implementation. |
| failure | Reading the comment has no runtime failure path. Compile or link errors, exceptions, and resource stops belong to the adjacent code. |
| cost | The comment adds no runtime instructions, allocation, clock read, counter debit, or engine hook; only source-text processing is added. |
| Design | [src/planner/selection_detail.hpp](../../../../../src/planner/selection_detail.hpp), [docs/selection.md](../../../../selection.md), [docs/selection_accounting.md](../../../../selection_accounting.md), [docs/selection_binding.md](../../../../selection_binding.md) |

## B0029

[Lines 126–129](../../../../../src/planner/selection_detail.hpp#L126); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void clear() noexcept {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Destroy FIFO nodes iteratively while preserving no-allocation cleanup. |
| inputs / outputs | Detaches each next link before local node destruction, then resets tail/count. |
| invariants | No recursive AccountedUnique next chain remains during a node destructor. |
| ownership | Releases each node/key and any last-owned compiled graph/account. |
| failure | Noexcept under native ownership destructors. |
| cost | Linear nodes plus payload-dependent final release; no fresh allocation. |
| Design | [docs/selection_accounting.md §Atomic publication](../../../../selection_accounting.md), [docs/query_memory.md §Boundaries](../../../../query_memory.md) |

## B0030

[Lines 130–136](../../../../../src/planner/selection_detail.hpp#L130); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
resource::AccountedUnique<Entry> first_;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Keep unique FIFO ownership separate from its borrowed tail and length. |
| inputs / outputs | first owns chain; last_ borrows final node; size_ counts nodes. |
| invariants | Empty state has null first/tail and zero size; list operations preserve empty-tail-next invariant. |
| ownership | Only first/next AccountedUnique own nodes; tail extends no lifetime. |
| failure | No standalone validation; private link methods require consistent state. |
| cost | Fixed headers; chain release is iterative/payload-dependent. |
| Design | [docs/selection_accounting.md §Atomic publication](../../../../selection_accounting.md) |

## B0031

[Lines 137–142](../../../../../src/planner/selection_detail.hpp#L137); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct CacheData {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Own cache configuration, committed statistics and FIFO entries. |
| inputs / outputs | Fixed limits/statistics plus Entries. |
| invariants | Scalar totals must match list content at preparation boundaries. |
| ownership | Unique PlanCache owns Data; nodes retain independent query accounts. |
| failure | Creation validation occurs at public create. |
| cost | Header plus retained entries/graphs. |
| Design | [docs/selection_accounting.md §Atomic publication](../../../../selection_accounting.md) |

```text
explicit CacheData(CacheLimits value) : limits(value) {}
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Initialize empty cache state from validated retention caps. |
| inputs / outputs | Copies limits; statistics/list stay empty. |
| invariants | No entry or runtime account is allocated here. |
| ownership | Outer unique owner supplies storage. |
| failure | No semantic validation in this constructor. |
| cost | Fixed setup. |
| Design | [docs/selection_accounting.md §Atomic publication](../../../../selection_accounting.md) |

## B0032

[Lines 143–144](../../../../../src/planner/selection_detail.hpp#L143); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L143-L144:sha256:c34ddd179cdd52cf6afe3375893628c22402397835e3ae7ec9797ff2943fed27
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Use the adjacent note for SelectionData: Own all unpublished/published selection context in one account-backed backing object. Confirm behavior against the declaration and implementation; comment text alone does not enforce or prove it. |
| inputs / outputs | This comment has no inputs or outputs. It accompanies SelectionData; use the adjacent declaration and implementation for the actual values and result. |
| invariants | This is static guidance only. The comment cannot alter state or guarantee that its wording holds. |
| ownership | The note owns no storage and changes no lifetime; ownership and borrowing for SelectionData come from its actual types and implementation. |
| failure | Reading the comment has no runtime failure path. Compile or link errors, exceptions, and resource stops belong to the adjacent code. |
| cost | The comment adds no runtime instructions, allocation, clock read, counter debit, or engine hook; only source-text processing is added. |
| Design | [src/planner/selection_detail.hpp](../../../../../src/planner/selection_detail.hpp), [docs/selection.md](../../../../selection.md), [docs/selection_accounting.md](../../../../selection_accounting.md), [docs/selection_binding.md](../../../../selection_binding.md) |

## B0033

[Lines 145–165](../../../../../src/planner/selection_detail.hpp#L145); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct SelectionData {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Own all unpublished/published selection context in one account-backed backing object. |
| inputs / outputs | Snapshot, captured source/request, evidence, complete assessments/decisions, chosen/plan, usage/cache/key. Optional captured declaration plus per-retained-candidate conditional reports and native edge vectors. |
| invariants | Publication requires chosen and plan and complete decision context; captured handles do not create original proof authority. |
| ownership | Shares proof/family/evidence/program owners; new text/vectors/control use receiving account. Pattern reports retain genuine candidate and captured-declaration handles; no source/tree or rule deep copy per report. |
| failure | Partial Data remains private and RAII-safe on failure. |
| cost | Retained payload and final teardown scale with assessments, decisions, text and program graphs. Optional reports add O(N) fixed handles/fields and O(total native edges) backing cells. Default requests retain empty optional/vector fields with fixed storage only. |
| Design | [docs/selection.md](../../../../selection.md), [docs/query_memory.md §Boundaries](../../../../query_memory.md), [docs/selection_accounting.md §Atomic publication](../../../../selection_accounting.md), [docs/update_patterns.md](../../../../update_patterns.md) |

## B0034

[Lines 166–169](../../../../../src/planner/selection_detail.hpp#L166); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct Factory {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Restrict result construction and cache access to private selection code. |
| inputs / outputs | Wraps prepared Data or borrows PlanCache implementation. |
| invariants | Factory validates neither proof nor cache contents; caller stages establish invariants. |
| ownership | Moves shared result owner; cache pointer is nonowning. |
| failure | Noexcept wrappers. |
| cost | Fixed handle/pointer work. |
| Design | [docs/selection_accounting.md §Atomic publication](../../../../selection_accounting.md) |

```text
static Selection selection(std::shared_ptr<const SelectionData> data) noexcept
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Prepare a public immutable result handle before commit. |
| inputs / outputs | Moves trusted Data ownership into private Selection constructor. |
| invariants | No exposure through Attempt until finalization succeeds. |
| ownership | Shares backing/account without deep copy. |
| failure | Noexcept; constructor does no validation. |
| cost | One shared-handle move. |
| Design | [docs/selection_accounting.md §Atomic publication](../../../../selection_accounting.md) |

```text
static CacheData* cache(PlanCache* value) noexcept
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Borrow cache state for the exclusive synchronous transaction. |
| inputs / outputs | Returns null for absent/moved cache. |
| invariants | Raw pointer is valid only while caller preserves cache owner/access exclusivity. |
| ownership | No ownership retention. |
| failure | Noexcept; admission later rejects required null cache. |
| cost | Fixed pointer lookup. |
| Design | [docs/selection_accounting.md §Atomic publication](../../../../selection_accounting.md) |

## B0035

[Lines 170–171](../../../../../src/planner/selection_detail.hpp#L170); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L170-L171:sha256:69d4737e024e9f685fe7e997492df7fd99e7d90ad11a4aa03588000bef5ad215
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Use the adjacent note for Prepared: Keep speculative result/cache statistics and funded list changes private. Confirm behavior against the declaration and implementation; comment text alone does not enforce or prove it. |
| inputs / outputs | This comment has no inputs or outputs. It accompanies Prepared; use the adjacent declaration and implementation for the actual values and result. |
| invariants | This is static guidance only. The comment cannot alter state or guarantee that its wording holds. |
| ownership | The note owns no storage and changes no lifetime; ownership and borrowing for Prepared come from its actual types and implementation. |
| failure | Reading the comment has no runtime failure path. Compile or link errors, exceptions, and resource stops belong to the adjacent code. |
| cost | The comment adds no runtime instructions, allocation, clock read, counter debit, or engine hook; only source-text processing is added. |
| Design | [src/planner/selection_detail.hpp](../../../../../src/planner/selection_detail.hpp), [docs/selection.md](../../../../selection.md), [docs/selection_accounting.md](../../../../selection_accounting.md), [docs/selection_binding.md](../../../../selection_binding.md) |

## B0036

[Lines 172–180](../../../../../src/planner/selection_detail.hpp#L172); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct Prepared {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Keep speculative result/cache statistics and funded list changes private. |
| inputs / outputs | Data owner, raw cache borrow, next counters, insertion/retired lists and eviction count. |
| invariants | Before commit cache is untouched; retired entries release after publication. |
| ownership | Owns private staged lists/result; borrows live exclusive cache. |
| failure | Failure before commit destroys speculative ownership without cache mutation. |
| cost | Preparation may allocate; commit links only, later destruction can be large. |
| Design | [docs/selection_accounting.md §Atomic publication](../../../../selection_accounting.md) |

## B0037

[Lines 181–207](../../../../../src/planner/selection_detail.hpp#L181); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
PreparationTiming preparation_timing(const std::optional<rank::Evidence>&) noexcept;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Declare private synchronous binding, component, payload and cache-preparation protocols. |
| inputs / outputs | Helpers borrow immutable snapshot/source/candidate/program/model plus one Budget; diagnostic record functions return owning bytes. |
| invariants | Source/compiled byte equality is a validation gate after typed authority, never an import/proof constructor. Cache prepare/stage is separate from no-fail commit. |
| ownership | Borrows end with the call; returned text and Prepared own retained storage/account. |
| failure | Budget/component/allocation failures unwind private preparation before cache publication. |
| cost | Full variable-width visits/comparisons and actual allocation costs, as specified in individual definition cards. |
| Design | [docs/selection_binding.md §Physical source and artifact frames](../../../../selection_binding.md), [docs/selection_accounting.md §Delegated budget equation](../../../../selection_accounting.md), [docs/selection_accounting.md §Atomic publication](../../../../selection_accounting.md) |

## B0038

[Lines 208–228](../../../../../src/planner/selection_detail.hpp#L208); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct Operation {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Own one synchronous selection transaction over caller inputs. |
| inputs / outputs | Borrows snapshot/source/request/cache; retains evidence, diagnostics and Budget. |
| invariants | Inputs/cache stay stable and exclusive throughout; no saved resumable operation escapes. |
| ownership | New results allocate under selected receiving/evidence/native/standalone account. |
| failure | Exceptions become fixed Attempt outcomes at entry point; no whole-graph rollback machinery is needed. |
| cost | Complete retained-family/source/ranking/native/cache work with variable-width costs. |
| Design | [docs/selection.md](../../../../selection.md), [docs/selection_accounting.md §Atomic publication](../../../../selection_accounting.md), [docs/query_memory.md §Boundaries](../../../../query_memory.md) |

## B0039

[Lines 229–229](../../../../../src/planner/selection_detail.hpp#L229); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L229-L229:sha256:41848aefb30bbb259c959e13f974e1f553bad9051ef8e1ee6f1df63b5ac2ac7c
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | This block close namespace crown::planner::selection::detail. |
| inputs / outputs | A scope delimiter has no call inputs or outputs; it controls which following declarations belong to the C++ namespace, class, or helper scope. |
| invariants | The braces set lexical visibility and type boundaries only. Any attached note is documentation and does not enforce behavior. |
| ownership | The delimiter and note acquire, release, or transfer no runtime object. Member lifetimes come from the enclosed type definitions. |
| failure | An unmatched or misplaced brace fails compilation; this block adds no runtime exception or resource-stop path. |
| cost | No runtime work or allocation is added. The compiler parses the scope boundary and comment. |
| Design | [src/planner/selection_detail.hpp](../../../../../src/planner/selection_detail.hpp), [docs/selection.md](../../../../selection.md), [docs/selection_accounting.md](../../../../selection_accounting.md), [docs/selection_binding.md](../../../../selection_binding.md) |
