# `src/resource/memory.cpp` — block usage map

[Source](../../../../../src/resource/memory.cpp) · [Source index](../../../README.md) · [Subsystem contracts](../../../subsystem_contracts.md) · [Reviewed primitives](../../../primitives.md)

Fund native owners and nested storage from one finite requested-byte account.

Snapshot SHA-256: `5f9932dea1b1ffc46cff9aac3e115b14992f4f39bb66b51202c6ff7ed98b0597`. 362 lines partitioned into 56 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [memory](../../../subsystem_contracts.md#memory). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/query_memory.md](../../../../query_memory.md), [docs/memory_accounts.md](../../../../memory_accounts.md), [docs/memory_reports.md](../../../../memory_reports.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–14](../../../../../src/resource/memory.cpp#L1) | Imports dependencies; declares namespace scope; declares callable signatures; declares values/defaults or compile-time conditions. | guard static_assert(sizeof(std::size_t) &lt;= sizeof(std::uint64_t));; growth new · [reviewed contract](#b0001) |
| [B0002 · 15–22](../../../../../src/resource/memory.cpp#L15) | Callable definition: std::uint64_t new_owner() | calls load, MemoryFailure, compare_exchange_weak; returns value + 1; 1 loop sites · [reviewed contract](#b0002) |
| [B0003 · 23–25](../../../../../src/resource/memory.cpp#L23) | Callable definition: void require(bool value, const char* /*source diagnostic*/) | calls MemoryFailure; guard void require(bool value, const char* /*source diagnostic*/) {; source comment (unverified): /*source diagnostic*/ · [reviewed contract](#b0003) |
| [B0004 · 26–30](../../../../../src/resource/memory.cpp#L26) | Callable definition: std::size_t purpose_index(MemoryPurpose purpose) | calls require; guard require(value &lt; memory_purpose_count, "unknown memory purpose");; returns value · [reviewed contract](#b0004) |
| [B0005 · 31–35](../../../../../src/resource/memory.cpp#L31) | Callable definition: std::size_t lifetime_index(AllocationLifetime lifetime) | calls require; guard require(value &lt; allocation_lifetime_count, "unknown allocation lifetime");; returns value · [reviewed contract](#b0005) |
| [B0006 · 36–41](../../../../../src/resource/memory.cpp#L36) | Callable definition: void add(MemoryUsage& total, const MemoryUsage& value) noexcept | calls ; source comment (unverified): // Every term is a disjoint subset of the already admitted account total. · [reviewed contract](#b0006) |
| [B0007 · 42–48](../../../../../src/resource/memory.cpp#L42) | Callable definition: void subtract(MemoryUsage& total, const MemoryUsage& value) noexcept | calls std::terminate · [reviewed contract](#b0007) |
| [B0008 · 49–50](../../../../../src/resource/memory.cpp#L49) | Closes surrounding scope/type. | source comment (unverified): // namespace · [reviewed contract](#b0008) |
| [B0009 · 51–65](../../../../../src/resource/memory.cpp#L51) | Type/record definition: struct MemoryAccount::Control |  · [reviewed contract](#b0009) |
| [B0010 · 66–80](../../../../../src/resource/memory.cpp#L66) | Type/record definition: struct MemoryAccount::BlockData | returns {1, static_cast&lt;std::uint64_t&gt;(raw_size), static_cast&lt;std::uint64_t&gt;(payload_size)} · [reviewed contract](#b0010) |
| [B0011 · 81–81](../../../../../src/resource/memory.cpp#L81) | Explanatory comments or spacing. |  |
| [B0012 · 82–82](../../../../../src/resource/memory.cpp#L82) | Callable definition: std::uint64_t MemoryAccount::control_bytes() noexcept | calls ; returns sizeof(Control) · [reviewed contract](#b0012) |
| [B0013 · 83–92](../../../../../src/resource/memory.cpp#L83) | Callable definition: std::uint64_t MemoryAccount::allocation_bytes(std::size_t bytes, std::size_t alignment) | calls require, std::max, max, MemoryFailure; guard require(alignment != 0 && (alignment & (alignment - 1)) == 0, "alignment must be a nonzero power of…; returns static_cast&lt;std::uint64_t&gt;(header + (effective - 1) + payload) · [reviewed contract](#b0013) |
| [B0014 · 93–93](../../../../../src/resource/memory.cpp#L93) | Explanatory comments or spacing. |  |
| [B0015 · 94–94](../../../../../src/resource/memory.cpp#L94) | Callable definition: MemoryAccount::MemoryAccount(Control* control) noexcept : control_(control) | calls control_ · [reviewed contract](#b0015) |
| [B0016 · 95–104](../../../../../src/resource/memory.cpp#L95) | Callable definition: MemoryAccount MemoryAccount::create(std::uint64_t limit) | calls control_bytes, MemoryFailure, new, MemoryAccount; returns MemoryAccount(std::construct_at(static_cast&lt;Control*&gt;(raw), limit, new_owner())); growth new · [reviewed contract](#b0016) |
| [B0017 · 105–112](../../../../../src/resource/memory.cpp#L105) | Callable definition: void MemoryAccount::retain(Control* control) noexcept | calls std::terminate; source comment (unverified): // Reference overflow is an invalid internal lifetime state. Supported RAII · [reviewed contract](#b0017) |
| [B0018 · 113–121](../../../../../src/resource/memory.cpp#L113) | Callable definition: void MemoryAccount::release(Control* control) noexcept | calls std::terminate, std::destroy_at, delete · [reviewed contract](#b0018) |
| [B0019 · 122–122](../../../../../src/resource/memory.cpp#L122) | Callable definition: MemoryAccount::MemoryAccount(const MemoryAccount& other) noexcept : control_(other.control_) | calls control_, retain · [reviewed contract](#b0019) |
| [B0020 · 123–126](../../../../../src/resource/memory.cpp#L123) | Callable definition: MemoryAccount& MemoryAccount::operator=(const MemoryAccount& other) noexcept | calls release; returns *this · [reviewed contract](#b0020) |
| [B0021 · 127–127](../../../../../src/resource/memory.cpp#L127) | Callable definition: MemoryAccount::MemoryAccount(MemoryAccount&& other) noexcept : control_(std::exchange(other.control_, nullptr)) | calls control_, std::exchange · [reviewed contract](#b0021) |
| [B0022 · 128–131](../../../../../src/resource/memory.cpp#L128) | Callable definition: MemoryAccount& MemoryAccount::operator=(MemoryAccount&& other) noexcept | calls std::exchange; returns *this · [reviewed contract](#b0022) |
| [B0023 · 132–132](../../../../../src/resource/memory.cpp#L132) | Callable definition: MemoryAccount::~MemoryAccount() | calls release · [reviewed contract](#b0023) |
| [B0024 · 133–136](../../../../../src/resource/memory.cpp#L133) | Callable definition: MemoryAccount::Control& MemoryAccount::required() const | calls require; guard require(control_ != nullptr, "empty memory account");; returns *control_ · [reviewed contract](#b0024) |
| [B0025 · 137–137](../../../../../src/resource/memory.cpp#L137) | Callable definition: MemoryStatistics MemoryAccount::statistics() const | calls required; returns required().statistics · [reviewed contract](#b0025) |
| [B0026 · 138–157](../../../../../src/resource/memory.cpp#L138) | Callable definition: AttributedMemoryStatistics MemoryAccount::statistics_for(MemoryAttribution attribution) const | calls require, valid, required, usage; guard require(attribution.valid(), "unknown memory attribution");; returns result; 1 loop sites · [reviewed contract](#b0026) |
| [B0027 · 158–159](../../../../../src/resource/memory.cpp#L158) | Explanatory comments or spacing. | source comment (unverified): // Caller-funded inventory, not a unique-owner registry: several allocations · [reviewed contract](#b0027) |
| [B0028 · 160–168](../../../../../src/resource/memory.cpp#L160) | Callable definition: std::size_t MemoryAccount::copy_attributions(std::span&lt;MemoryAttribution&gt; output) const | calls required, require, size; guard require(!control.allocating && output.size()&gt;=control.statistics.current.allocations,; returns used; 1 loop sites; source comment (unverified): // Caller-funded inventory, not a unique-owner registry: several allocations · [reviewed contract](#b0028) |
| [B0029 · 169–169](../../../../../src/resource/memory.cpp#L169) | Explanatory comments or spacing. |  |
| [B0030 · 170–190](../../../../../src/resource/memory.cpp#L170) | Callable definition: void MemoryAccount::set_lifetime_containing(const void* address, MemoryPurpose purpose, MemoryAttribution attribution, Allocation… | calls required, require, valid, purpose_index; guard require(!control.allocating && address != nullptr && attribution.valid(), "invalid containing alloc…; 1 loop sites · [reviewed contract](#b0030) |
| [B0031 · 191–191](../../../../../src/resource/memory.cpp#L191) | Explanatory comments or spacing. |  |
| [B0032 · 192–232](../../../../../src/resource/memory.cpp#L192) | Callable definition: MemoryBlock MemoryAccount::allocate(std::size_t bytes, std::size_t alignment, MemoryPurpose purpose, MemoryAttribution attributio… | calls required, keep_alive, AllocationGuard, control; guard require(purpose != MemoryPurpose::control, "controller purpose is reserved");; returns MemoryBlock(block); growth allocate, new; source comment (unverified): // Failure leaves every account counter unchanged. · [reviewed contract](#b0032) |
| [B0033 · 233–240](../../../../../src/resource/memory.cpp#L233) | Callable definition: void* MemoryAccount::allocate_raw(std::size_t bytes, std::size_t alignment, MemoryPurpose purpose, MemoryAttribution attribution)… | calls allocate, std::exchange; returns header-&gt;payload; growth allocate, allocate_raw; source comment (unverified): // Ownership transfers to the allocator's caller. The header retains the · [reviewed contract](#b0033) |
| [B0034 · 241–252](../../../../../src/resource/memory.cpp#L241) | Callable definition: MemoryUsage MemoryAccount::allocation_usage_raw(const void* pointer, std::size_t bytes, std::size_t alignment, MemoryPurpose purp… | calls required, require, usage; guard require(pointer != nullptr, "empty raw allocation lookup");; returns block-&gt;usage(); source comment (unverified): // As for allocator deallocation, pointer must name a still-live allocation · [reviewed contract](#b0034) |
| [B0035 · 253–263](../../../../../src/resource/memory.cpp#L253) | Callable definition: void MemoryAccount::set_lifetime_raw(void* pointer, std::size_t bytes, std::size_t alignment, MemoryPurpose purpose, MemoryAttrib… | calls lifetime_index, allocation_usage_raw, require, subtract; guard require(!block-&gt;owner-&gt;allocating, "allocation classification reentry"); · [reviewed contract](#b0035) |
| [B0036 · 264–272](../../../../../src/resource/memory.cpp#L264) | Callable definition: void MemoryAccount::deallocate_raw(void* pointer, std::size_t bytes, std::size_t alignment, MemoryPurpose purpose, MemoryAttribut… | calls std::terminate, free; source comment (unverified): // Standard allocator ownership/size mismatch is invalid. · [reviewed contract](#b0036) |
| [B0037 · 273–291](../../../../../src/resource/memory.cpp#L273) | Callable definition: void MemoryAccount::free(BlockData* block) noexcept | calls std::terminate, usage, subtract, std::destroy_at; source comment (unverified): // Invalid upstream deallocation reentry. · [reviewed contract](#b0037) |
| [B0038 · 292–292](../../../../../src/resource/memory.cpp#L292) | Explanatory comments or spacing. |  |
| [B0039 · 293–293](../../../../../src/resource/memory.cpp#L293) | Callable definition: MemoryBlock::MemoryBlock(MemoryAccount::BlockData* data) noexcept : data_(data) | calls data_ · [reviewed contract](#b0039) |
| [B0040 · 294–294](../../../../../src/resource/memory.cpp#L294) | Callable definition: MemoryBlock::MemoryBlock(MemoryBlock&& other) noexcept : data_(std::exchange(other.data_, nullptr)) | calls data_, std::exchange · [reviewed contract](#b0040) |
| [B0041 · 295–298](../../../../../src/resource/memory.cpp#L295) | Callable definition: MemoryBlock& MemoryBlock::operator=(MemoryBlock&& other) noexcept | calls std::exchange; returns *this · [reviewed contract](#b0041) |
| [B0042 · 299–299](../../../../../src/resource/memory.cpp#L299) | Callable definition: MemoryBlock::~MemoryBlock() | calls reset · [reviewed contract](#b0042) |
| [B0043 · 300–300](../../../../../src/resource/memory.cpp#L300) | Callable definition: void MemoryBlock::reset() noexcept | calls MemoryAccount::free, std::exchange · [reviewed contract](#b0043) |
| [B0044 · 301–301](../../../../../src/resource/memory.cpp#L301) | Callable definition: void* MemoryBlock::data() noexcept | calls ; returns data_ ? data_-&gt;payload : nullptr · [reviewed contract](#b0044) |
| [B0045 · 302–302](../../../../../src/resource/memory.cpp#L302) | Callable definition: const void* MemoryBlock::data() const noexcept | calls ; returns data_ ? data_-&gt;payload : nullptr · [reviewed contract](#b0045) |
| [B0046 · 303–303](../../../../../src/resource/memory.cpp#L303) | Callable definition: std::size_t MemoryBlock::size() const noexcept | calls ; returns data_ ? data_-&gt;payload_size : 0 · [reviewed contract](#b0046) |
| [B0047 · 304–304](../../../../../src/resource/memory.cpp#L304) | Callable definition: MemoryUsage MemoryBlock::usage() const noexcept | calls usage; returns data_ ? data_-&gt;usage() : MemoryUsage{} · [reviewed contract](#b0047) |
| [B0048 · 305–308](../../../../../src/resource/memory.cpp#L305) | Callable definition: MemoryAccount::BlockData& MemoryBlock::required() const | calls require; guard require(data_ != nullptr, "empty memory allocation");; returns *data_ · [reviewed contract](#b0048) |
| [B0049 · 309–309](../../../../../src/resource/memory.cpp#L309) | Callable definition: MemoryPurpose MemoryBlock::purpose() const | calls required; returns required().purpose · [reviewed contract](#b0049) |
| [B0050 · 310–310](../../../../../src/resource/memory.cpp#L310) | Callable definition: MemoryAttribution MemoryBlock::attribution() const | calls required; returns required().attribution · [reviewed contract](#b0050) |
| [B0051 · 311–311](../../../../../src/resource/memory.cpp#L311) | Callable definition: AllocationLifetime MemoryBlock::lifetime() const | calls required; returns required().lifetime · [reviewed contract](#b0051) |
| [B0052 · 312–312](../../../../../src/resource/memory.cpp#L312) | Callable definition: MemoryStatistics MemoryBlock::account_statistics() const | calls required; returns required().owner-&gt;statistics · [reviewed contract](#b0052) |
| [B0053 · 313–323](../../../../../src/resource/memory.cpp#L313) | Callable definition: void MemoryBlock::set_lifetime(AllocationLifetime lifetime) const | calls lifetime_index, required, usage, subtract · [reviewed contract](#b0053) |
| [B0054 · 324–324](../../../../../src/resource/memory.cpp#L324) | Explanatory comments or spacing. |  |
| [B0055 · 325–360](../../../../../src/resource/memory.cpp#L325) | Callable definition: void MemoryAccount::check_invariants() const | calls required, require, valid, purpose_index; guard require(slow != fast, "cyclic memory allocation list");; 2 loop sites · [reviewed contract](#b0055) |
| [B0056 · 361–362](../../../../../src/resource/memory.cpp#L361) | Closes surrounding scope/type. | source comment (unverified): // namespace crown::resource · [reviewed contract](#b0056) |

## B0001

[Lines 1–14](../../../../../src/resource/memory.cpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
constexpr auto maximum =
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Fix the representational domain for account identities and historical/reference counters. |
| inputs / outputs | maximum is uint64_t::max; the adjacent static assertion requires size_t values to fit uint64_t. |
| invariants | The platform bound justifies byte-size conversion. Unbounded churn/history still needs explicit overflow checks before publication. |
| ownership | Compile-time scalar metadata only; there is no counter registry or hidden account. |
| failure | An unsupported wider size_t platform fails at compile time; runtime exhaustion remains checked in the relevant primitive. |
| cost | No runtime allocation or scan; actual owner-ID creation is the separate atomic CAS helper. |
| Design | [docs/query_memory.md](../../../../query_memory.md), [docs/memory_accounts.md](../../../../memory_accounts.md) |

## B0002

[Lines 15–22](../../../../../src/resource/memory.cpp#L15); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::uint64_t new_owner()
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Allocate a process-unique nonzero account identity. |
| inputs / outputs | An atomic monotonic counter returns its next uint64 identity. |
| invariants | Only identity allocation is atomic; account mutation itself still requires one externally synchronized caller. IDs never wrap or get reused. |
| ownership | No heap storage or query account is created by this helper. |
| failure | Exhaustion raises fixed MemoryFailure(overflow) before a successful ID is returned. |
| cost | One CAS retry loop; contention can retry, with no per-account registry or retained history allocation. |
| Design | [docs/query_memory.md](../../../../query_memory.md), [docs/code_specs/primitives.md](../../../primitives.md), [docs/storage_journal.md](../../../../storage_journal.md) |

## B0003

[Lines 23–25](../../../../../src/resource/memory.cpp#L23); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void require(bool value,
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Enforce a resource-path contract with fixed diagnostics. |
| inputs / outputs | A Boolean contract predicate returns normally when true and throws MemoryFailure(contract) otherwise. |
| invariants | The source diagnostic parameter is intentionally not formatted or retained. |
| ownership | No owning diagnostic string; exception-runtime storage is outside operator-new accounting. |
| failure | Invalid resource use is surfaced by the fixed typed failure. |
| cost | O(1) predicate/branch; success allocates nothing. |
| Design | [docs/query_memory.md](../../../../query_memory.md), [docs/code_specs/primitives.md](../../../primitives.md), [docs/storage_journal.md](../../../../storage_journal.md) |

## B0004

[Lines 26–30](../../../../../src/resource/memory.cpp#L26); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::size_t purpose_index(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Validate a purpose before indexing fixed account statistics. |
| inputs / outputs | A MemoryPurpose yields its checked array index. |
| invariants | The count/sentinel and invalid enum values cannot index the arrays. |
| ownership | Borrows only an enum value. |
| failure | Invalid purpose raises MemoryFailure(contract). |
| cost | O(1), no allocation. |
| Design | [docs/query_memory.md](../../../../query_memory.md), [docs/code_specs/primitives.md](../../../primitives.md), [docs/storage_journal.md](../../../../storage_journal.md) |

## B0005

[Lines 31–35](../../../../../src/resource/memory.cpp#L31); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::size_t lifetime_index(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Validate an allocation lifetime before indexing its partition. |
| inputs / outputs | An AllocationLifetime yields its checked fixed-array index. |
| invariants | The count/sentinel is not a valid classification. |
| ownership | Borrows only an enum value. |
| failure | Invalid lifetime raises MemoryFailure(contract). |
| cost | O(1), no allocation. |
| Design | [docs/query_memory.md](../../../../query_memory.md), [docs/code_specs/primitives.md](../../../primitives.md), [docs/storage_journal.md](../../../../storage_journal.md) |

## B0006

[Lines 36–41](../../../../../src/resource/memory.cpp#L36); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void add(MemoryUsage& total,
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Combine disjoint already-admitted native allocation usage. |
| inputs / outputs | One MemoryUsage is added to three aggregate counters. |
| invariants | Inputs describe disjoint subsets of this admitted account, so their sums fit its checked total; this is not unchecked external arithmetic. |
| ownership | Inline accounting values only. |
| failure | Noexcept under the stated subset invariant. |
| cost | Three fixed additions; no independent budget or scan. |
| Design | [docs/query_memory.md](../../../../query_memory.md), [docs/code_specs/primitives.md](../../../primitives.md), [docs/storage_journal.md](../../../../storage_journal.md) |

## B0007

[Lines 42–48](../../../../../src/resource/memory.cpp#L42); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void subtract(MemoryUsage& total,
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Remove a known live allocation contribution from its accounting partitions. |
| inputs / outputs | One contained usage is subtracted from three aggregate counters. |
| invariants | Each term must be present in the total before subtraction. |
| ownership | Inline statistics only; it does not release the actual block. |
| failure | Counter underflow is an internal accounting defect and terminates rather than unwinding native deallocation. |
| cost | Three comparisons and subtractions; O(1), nonallocating. |
| Design | [docs/query_memory.md](../../../../query_memory.md), [docs/code_specs/primitives.md](../../../primitives.md), [docs/storage_journal.md](../../../../storage_journal.md) |

## B0008

[Lines 49–50](../../../../../src/resource/memory.cpp#L49); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L49-L50:sha256:c2bd7638f09d52cb034ed574f539304035fc6fab162bf8d5fa20a35d8c7288a1
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Close the \`anonymous namespace in src/resource/memory.cpp\` scope at this exact source boundary. |
| inputs / outputs | This token introduces no callable inputs or outputs. Declarations inside \`anonymous namespace in src/resource/memory.cpp\` define the available names, members and operations. |
| invariants | The closing brace matches the opening \`anonymous namespace in src/resource/memory.cpp\` at its lexical source position in src/resource/memory.cpp; it preserves C++ namespace/type nesting. |
| ownership | The closing delimiter creates no owner. Types closed by \`anonymous namespace in src/resource/memory.cpp\` retain the lifetimes and allocator rules of their own fields and operations. |
| failure | No failure path executes at this closing delimiter. Failure and cleanup behavior belong to enclosed functions and owning types. |
| cost | The delimiter itself performs no runtime work; the enclosed initializers, methods and destructors carry their own costs. |
| Design | [docs/query_memory.md](../../../../query_memory.md), [docs/memory_accounts.md](../../../../memory_accounts.md), [docs/code_specs/primitives.md](../../../primitives.md), [docs/code_specs/subsystem_contracts.md](../../../subsystem_contracts.md) |

## B0009

[Lines 51–65](../../../../../src/resource/memory.cpp#L51); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct MemoryAccount::Control {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Own the account lifetime, active allocation list and fixed statistics. |
| inputs / outputs | Limit and nonzero owner ID initialize a one-allocation controller-only account. |
| invariants | Controller bytes count toward requested-byte limit and query:0 attribution; all blocks retain this same controller. |
| ownership | Intrusive nonowning list points to blocks; reference count is single-caller, not an atomic synchronization mechanism. |
| failure | Controller is published only after allocation/construction succeeds. |
| cost | Fixed-size statistics arrays and one controller allocation; no per-attribution map or churn history. |
| Design | [docs/query_memory.md](../../../../query_memory.md), [docs/code_specs/primitives.md](../../../primitives.md), [docs/storage_journal.md](../../../../storage_journal.md) |

## B0010

[Lines 66–80](../../../../../src/resource/memory.cpp#L66); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct MemoryAccount::BlockData {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Record exact ownership, framing and intrusive membership for one upstream allocation. |
| inputs / outputs | Header stores owner, links, aligned payload pointer/size, original alignment, purpose, lifetime and attribution; usage() returns exact stored sizes. |
| invariants | Payload/header/back-pointer occupy one upstream request; attribution stays immutable while lifetime can change. |
| ownership | The block independently retains Control until free; list links do not own another block. |
| failure | Header-only methods assume the still-live allocation contract. |
| cost | Fixed header per allocation; usage() reads three scalars without recalculation. |
| Design | [docs/query_memory.md](../../../../query_memory.md), [docs/code_specs/primitives.md](../../../primitives.md), [docs/storage_journal.md](../../../../storage_journal.md) |

## B0012

[Lines 82–82](../../../../../src/resource/memory.cpp#L82); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::uint64_t MemoryAccount::control_bytes()
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Expose the actual account-controller requested bytes for admission. |
| inputs / outputs | Returns sizeof(Control) as uint64. |
| invariants | This is included in every created account before payload allocations. |
| ownership | No account instance is needed. |
| failure | Noexcept. |
| cost | O(1) compile-time size; no allocation. |
| Design | [docs/query_memory.md](../../../../query_memory.md), [docs/code_specs/primitives.md](../../../primitives.md), [docs/storage_journal.md](../../../../storage_journal.md) |

## B0013

[Lines 83–92](../../../../../src/resource/memory.cpp#L83); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::uint64_t MemoryAccount::allocation_bytes(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Calculate the exact checked upstream request for a payload and alignment. |
| inputs / outputs | Payload bytes and nonzero power-of-two alignment yield header+back-pointer+padding+at-least-one payload byte. |
| invariants | Requested bytes differ from logical payload bytes. A zero-byte payload still owns a real framed block. Arithmetic must fit size_t before conversion. |
| ownership | Pure preflight; it allocates nothing and consumes no account budget. |
| failure | Invalid alignment raises contract; size overflow raises overflow. |
| cost | Fixed arithmetic/checks; no allocator usable-size or RSS inspection. |
| Design | [docs/query_memory.md](../../../../query_memory.md), [docs/code_specs/primitives.md](../../../primitives.md), [docs/storage_journal.md](../../../../storage_journal.md) |

## B0015

[Lines 94–94](../../../../../src/resource/memory.cpp#L94); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
MemoryAccount::MemoryAccount(Control* control) noexcept
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Adopt the freshly constructed controller's initial handle reference. |
| inputs / outputs | Private construction stores Control* directly; create supplies its already initialized reference count. |
| invariants | The constructor does not increment the initial reference, allocate a controller, or inspect any block list. |
| ownership | The resulting handle owns the initial controller reference; only private construction can supply it. |
| failure | Noexcept under the factory's constructed-controller precondition. |
| cost | O(1) pointer assignment; no allocation. |
| Design | [docs/query_memory.md](../../../../query_memory.md), [docs/memory_accounts.md](../../../../memory_accounts.md) |

## B0016

[Lines 95–104](../../../../../src/resource/memory.cpp#L95); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
MemoryAccount MemoryAccount::create(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Create one finite allocation authority and its charged controller before native query admission. |
| inputs / outputs | Requested-byte limit in; owning MemoryAccount out. A limit below control_bytes is rejected. |
| invariants | The controller itself consumes the limit; creating this account is not permitted as a hidden per-operation refill. |
| ownership | The returned account retains the constructed Control; raw controller storage is freed if new_owner or construction fails. |
| failure | Limit failure precedes raw allocation. The catch deallocates raw storage on construction/owner-ID failure and must remain unless admission is reordered with equivalent semantics. |
| cost | One upstream allocation plus fixed controller/counter work and atomic owner-ID assignment; not an ordinary tuple-operation primitive. |
| Design | [docs/query_memory.md](../../../../query_memory.md), [docs/memory_accounts.md](../../../../memory_accounts.md) |

## B0017

[Lines 105–112](../../../../../src/resource/memory.cpp#L105); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void MemoryAccount::retain(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Retain a live account controller for a handle or raw block. |
| inputs / outputs | A nullable Control pointer increments its reference count if present. |
| invariants | References are externally synchronized and cannot wrap. |
| ownership | Shares the existing controller; it does not mint an allowance. |
| failure | Reference overflow is an invalid internal lifetime state and terminates. |
| cost | O(1), noexcept, no allocation. |
| Design | [docs/query_memory.md](../../../../query_memory.md), [docs/code_specs/primitives.md](../../../primitives.md), [docs/storage_journal.md](../../../../storage_journal.md) |

## B0018

[Lines 113–121](../../../../../src/resource/memory.cpp#L113); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void MemoryAccount::release(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Release one account/controller reference and delete the final empty controller. |
| inputs / outputs | Nullable Control is decremented; the final reference destroys controller storage. |
| invariants | Final release requires an empty block list and controller-only current usage. |
| ownership | Every still-live block retains its own reference, so a facade may disappear before its outputs. |
| failure | Underflow or inconsistent final state terminates; no throwing cleanup. |
| cost | O(1) reference operation; final controller destruction is fixed-size, without a ledger traversal. |
| Design | [docs/query_memory.md](../../../../query_memory.md), [docs/code_specs/primitives.md](../../../primitives.md), [docs/storage_journal.md](../../../../storage_journal.md) |

## B0019

[Lines 122–122](../../../../../src/resource/memory.cpp#L122); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
MemoryAccount::MemoryAccount(const MemoryAccount& other) noexcept
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Share an existing finite account when an owner or allocator is copied. |
| inputs / outputs | Copies the controller pointer and retain()s it if present. |
| invariants | An empty source stays empty. A nonempty copy has the same owner ID, statistics and limit; no new allowance appears. |
| ownership | Both handles independently retain the same controller. |
| failure | Noexcept; impossible reference overflow terminates in retain rather than permitting wrapped lifetime state. |
| cost | O(1) pointer/reference work; no allocation or ledger scan. |
| Design | [docs/query_memory.md](../../../../query_memory.md), [docs/memory_accounts.md](../../../../memory_accounts.md) |

## B0020

[Lines 123–126](../../../../../src/resource/memory.cpp#L123); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
MemoryAccount& MemoryAccount::operator=(const MemoryAccount& other) noexcept
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Replace one account handle by a retained copy of another. |
| inputs / outputs | Nonself assignment retains the source controller, releases the old controller and stores the source pointer; returns *this. |
| invariants | Retain precedes release, including when distinct handles share a controller, so the assignment cannot destroy the controller being adopted. |
| ownership | Only handle ownership changes; blocks independently retain their original account and are neither migrated nor freed. |
| failure | Noexcept with retain/release internal lifetime contracts; self assignment does no work. |
| cost | O(1) reference work, with fixed controller destruction only if the old final reference was empty of blocks. |
| Design | [docs/query_memory.md](../../../../query_memory.md), [docs/memory_accounts.md](../../../../memory_accounts.md) |

## B0021

[Lines 127–127](../../../../../src/resource/memory.cpp#L127); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
MemoryAccount::MemoryAccount(MemoryAccount&& other) noexcept
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Transfer an account handle without changing controller reference totals. |
| inputs / outputs | Exchanges the source pointer with null and stores its previous value. |
| invariants | The source becomes empty; the destination inherits the exact existing account authority. |
| ownership | One reference moves between handles; no controller/block is cloned. |
| failure | Noexcept. |
| cost | O(1) pointer exchange; no allocation, scan or retain/release pair. |
| Design | [docs/query_memory.md](../../../../query_memory.md), [docs/memory_accounts.md](../../../../memory_accounts.md) |

## B0022

[Lines 128–131](../../../../../src/resource/memory.cpp#L128); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
MemoryAccount& MemoryAccount::operator=(MemoryAccount&& other) noexcept
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Release a destination handle and transfer another account handle into it. |
| inputs / outputs | Nonself assignment releases its prior controller then exchanges the source pointer with null; returns *this. |
| invariants | A distinct source handle already retains any shared controller while the destination releases its reference. Self move leaves the handle unchanged. |
| ownership | The source reference moves once; live blocks remain attached to their original headers/accounts. |
| failure | Noexcept; invalid final-release lifetime state terminates. |
| cost | O(1) handle work and optional fixed final-controller delete, with no allocation or block traversal. |
| Design | [docs/query_memory.md](../../../../query_memory.md), [docs/memory_accounts.md](../../../../memory_accounts.md) |

## B0023

[Lines 132–132](../../../../../src/resource/memory.cpp#L132); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
MemoryAccount::~MemoryAccount()
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Release this facade's controller reference on scope exit. |
| inputs / outputs | Calls release(control_) for an empty or live account handle. |
| invariants | Outstanding blocks retain independent references, so this destructor does not walk/free them or invalidate their owners. |
| ownership | Only the final reference destroys an already block-empty controller. |
| failure | Destructor cleanup is nonthrowing; inconsistent reference/final-state invariants terminate. |
| cost | O(1) reference decrement and optional fixed controller delete; no ledger scan or allocation. |
| Design | [docs/query_memory.md](../../../../query_memory.md), [docs/memory_accounts.md](../../../../memory_accounts.md) |

## B0024

[Lines 133–136](../../../../../src/resource/memory.cpp#L133); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
MemoryAccount::Control& MemoryAccount::required()
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Validate a nonempty account handle and borrow its controller. |
| inputs / outputs | Returns Control& for an existing handle. |
| invariants | A moved-from/default account cannot silently allocate unbounded memory. |
| ownership | Borrowed reference valid under the account/controller retention contract. |
| failure | Empty handle raises MemoryFailure(contract). |
| cost | O(1); success allocates nothing. |
| Design | [docs/query_memory.md](../../../../query_memory.md), [docs/code_specs/primitives.md](../../../primitives.md), [docs/storage_journal.md](../../../../storage_journal.md) |

## B0025

[Lines 137–137](../../../../../src/resource/memory.cpp#L137); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
MemoryStatistics MemoryAccount::statistics()
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Copy account-wide maintained statistics without deriving them from blocks. |
| inputs / outputs | A valid account returns its fixed MemoryStatistics value. |
| invariants | These are requested-byte/current/history counters, not RSS or logical relation size. |
| ownership | Returned structure owns scalars and fixed arrays, not pointers to mutable blocks. |
| failure | Empty account raises contract; caller externally synchronizes with mutation. |
| cost | Fixed-size copy; does not walk the allocation ledger. |
| Design | [docs/query_memory.md](../../../../query_memory.md), [docs/code_specs/primitives.md](../../../primitives.md), [docs/storage_journal.md](../../../../storage_journal.md) |

## B0026

[Lines 138–157](../../../../../src/resource/memory.cpp#L138); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
AttributedMemoryStatistics MemoryAccount::statistics_for(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Sum current allocation usage for one immutable owner attribution. |
| inputs / outputs | Valid attribution in; allocation/request/payload counters partitioned by purpose/lifetime out. |
| invariants | query:0 includes the controller once; other owners do not. Each scanned live block contributes at most once, so accumulated partitions fit the admitted account total. Reclassification and owner reports do not mint another limit. |
| ownership | The result is scalar counter state; the scan borrows current ledger nodes for the duration of the call. |
| failure | Invalid account or attribution raises fixed MemoryFailure(contract). Accumulation uses noexcept add() under the admitted disjoint-subset invariant; it does not independently validate corrupted counters/list structure. No new payload allocation is needed on success. |
| cost | O(A) outstanding allocations; not O(1) merely because the output is fixed size. Avoid placing it in per-row update/probe paths. |
| Design | [docs/memory_reports.md](../../../../memory_reports.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0027

[Lines 158–159](../../../../../src/resource/memory.cpp#L158); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L158-L159:sha256:2e845cc4428ec924731b3a3533e71edf647fffbbc7fd6cf43534bb40f560de44
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Usage note immediately before \`std::size_t MemoryAccount::copy_attributions(std::span&lt;MemoryAttribution&gt; output) const\`: Caller-funded inventory, not a unique-owner registry: several allocations can carry the same attribution. No addresses or retained history are exported. |
| inputs / outputs | This comment introduces no parameter, field or return value. It documents the adjacent construct beginning at src/resource/memory.cpp:L160; use that declaration for the actual input/output shape. |
| invariants | The source note states: Caller-funded inventory, not a unique-owner registry: several allocations can carry the same attribution. No addresses or retained history are exported. It is prose guidance; the adjacent implementation is the place to check enforcement. |
| ownership | The comment itself retains nothing. It documents this neighboring ownership/account boundary: Caller-funded inventory, not a unique-owner registry: several allocations can carry the same attribution. No addresses or retained history are exported. Actual lifetime is determined by the declared members and owners. |
| failure | This comment adds no branch or handler. Any failure behavior remains in the adjacent callable implementation and its callers. |
| cost | The note states a local cost boundary: Caller-funded inventory, not a unique-owner registry: several allocations can carry the same attribution. No addresses or retained history are exported. Treat it as usage guidance; actual work follows the implementation and input. |
| Design | [docs/query_memory.md](../../../../query_memory.md), [docs/memory_accounts.md](../../../../memory_accounts.md), [docs/code_specs/primitives.md](../../../primitives.md), [docs/code_specs/subsystem_contracts.md](../../../subsystem_contracts.md) |

## B0028

[Lines 160–168](../../../../../src/resource/memory.cpp#L160); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::size_t MemoryAccount::copy_attributions(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Export one current attribution key per native allocation into caller capacity. |
| inputs / outputs | Caller span of at least current.allocations receives controller query:0 followed by every block attribution; returns used length. |
| invariants | Caller is quiescent; keys can repeat because this is one entry per allocation, not a distinct-owner registry. |
| ownership | Caller owns the buffer; no addresses or account-internal view escapes. |
| failure | Insufficient capacity, empty account or allocation reentry raises contract before/at invariant checks. |
| cost | O(outstanding allocations), no scratch allocation or retained owner-history growth. |
| Design | [docs/query_memory.md](../../../../query_memory.md), [docs/code_specs/primitives.md](../../../primitives.md), [docs/storage_journal.md](../../../../storage_journal.md) |

## B0030

[Lines 170–190](../../../../../src/resource/memory.cpp#L170); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void MemoryAccount::set_lifetime_containing(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Find the account allocation containing an interior standard-container address and reclassify its lifetime. |
| inputs / outputs | Live interior address plus expected purpose/attribution and target lifetime in; ledger counters/lifetime updated in place. |
| invariants | The caller must supply a current allocation from this account. Purpose/attribution must match; active/retained/free-pool labels never alter requested bytes. |
| ownership | No pointer is acquired or freed; the supplied address is compared numerically against ledger payload intervals. |
| failure | Quiescence/identity/category validation and a missing containing allocation are contract failures. No allocation is performed. |
| cost | O(A) scan of outstanding allocations. Native owned-node containers can use exact-allocation O(1) classification instead; ordered std::map undo currently pays this bridge cost. |
| Design | [docs/query_memory.md](../../../../query_memory.md), [docs/memory_reports.md](../../../../memory_reports.md) |

## B0032

[Lines 192–232](../../../../../src/resource/memory.cpp#L192); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
MemoryBlock MemoryAccount::allocate(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Admit and own one aligned allocation while keeping accounting correct across upstream allocator reentry/failure. |
| inputs / outputs | Payload bytes, alignment, purpose and attribution in; MemoryBlock with exact stored request out. |
| invariants | A reentrant allocation cannot overcommit an in-flight admission. Requested-byte and history counters are checked before publication; purpose/owner are immutable. |
| ownership | keep_alive retains Control across the upstream call; the returned block owns its ledger node/payload and retains the account. |
| failure | AllocationGuard clears the in-flight flag on every exit. Limit/overflow/contract failures occur before publishing a live allocation; failed upstream allocation does not enter the ledger. |
| cost | Fixed arithmetic/counter/intrusive-ledger work plus one upstream allocation. Alignment/header allowance is charged even for zero-payload requests. |
| Design | [docs/query_memory.md](../../../../query_memory.md), [docs/memory_accounts.md](../../../../memory_accounts.md) |

## B0033

[Lines 233–240](../../../../../src/resource/memory.cpp#L233); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void* MemoryAccount::allocate_raw(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Transfer an admitted MemoryBlock to the standard-allocator bridge. |
| inputs / outputs | Bytes/alignment/purpose/attribution return the aligned live payload pointer. |
| invariants | Exactly one later deallocate_raw call must use this live base pointer and original metadata. |
| ownership | Releases the temporary MemoryBlock handle without freeing its block; the header independently retains Control. |
| failure | Admission/upstream failures publish no raw pointer. |
| cost | One allocate() operation plus fixed ownership transfer; no second allocation or scan. |
| Design | [docs/query_memory.md](../../../../query_memory.md), [docs/code_specs/primitives.md](../../../primitives.md), [docs/storage_journal.md](../../../../storage_journal.md) |

## B0034

[Lines 241–252](../../../../../src/resource/memory.cpp#L241); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
MemoryUsage MemoryAccount::allocation_usage_raw(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Inspect the exact request represented by an allocator-owned live base pointer. |
| inputs / outputs | Pointer plus original size/alignment/purpose/attribution return stored MemoryUsage. |
| invariants | Pointer must already name a still-live allocation from this adapter. Reading its preceding header is not safe introspection of arbitrary/expired addresses. |
| ownership | Borrows block/header; no lifetime retention is added. |
| failure | After the live-pointer precondition, metadata mismatches raise contract. |
| cost | O(1) back-pointer access and fixed metadata comparisons; no ledger scan. |
| Design | [docs/query_memory.md](../../../../query_memory.md), [docs/code_specs/primitives.md](../../../primitives.md), [docs/storage_journal.md](../../../../storage_journal.md) |

## B0035

[Lines 253–263](../../../../../src/resource/memory.cpp#L253); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void MemoryAccount::set_lifetime_raw(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Reclassify a known live allocator block without changing its byte allowance. |
| inputs / outputs | Exact allocator pointer/metadata and destination lifetime move usage between lifetime partitions. |
| invariants | Immutable owner/purpose/attribution and current total remain unchanged; no reentry into active allocation. |
| ownership | Borrows the same live base pointer required by allocation_usage_raw. |
| failure | Invalid lifetime, mismatched metadata or reentry raises contract; no new allocation occurs. |
| cost | O(1) header access and fixed counters; unlike containing-pointer classification, no ledger search. |
| Design | [docs/query_memory.md](../../../../query_memory.md), [docs/code_specs/primitives.md](../../../primitives.md), [docs/storage_journal.md](../../../../storage_journal.md) |

## B0036

[Lines 264–272](../../../../../src/resource/memory.cpp#L264); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void MemoryAccount::deallocate_raw(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Free exactly one standard-allocator allocation through its original account. |
| inputs / outputs | Null is a no-op; otherwise pointer and exact original metadata identify the block to free. |
| invariants | The nonnull pointer must be a valid still-live allocation base; duplicate/foreign/arbitrary pointer calls violate the allocator contract. |
| ownership | Free releases the block-owned controller reference after unlinking accounting state. |
| failure | Metadata mismatch terminates; this noexcept cleanup path does not format or translate errors. |
| cost | O(1) header validation/unlink/counter work plus upstream deallocation. |
| Design | [docs/query_memory.md](../../../../query_memory.md), [docs/code_specs/primitives.md](../../../primitives.md), [docs/storage_journal.md](../../../../storage_journal.md) |

## B0037

[Lines 273–291](../../../../../src/resource/memory.cpp#L273); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void MemoryAccount::free(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Unlink one native block, debit its exact partitions and release upstream storage. |
| inputs / outputs | Nullable BlockData pointer is consumed; current/purpose/lifetime usage and freed history are updated. |
| invariants | No allocation/reclassification/deallocation reentry; the intrusive neighbors and statistics describe this block. |
| ownership | Destroys header/back-pointer, deletes the original raw pointer, then releases its independent Control reference. |
| failure | Corrupt counters/list/lifetime states terminate; supported deallocation is noexcept and nonallocating. |
| cost | O(1) intrusive unlink and fixed counters; no search for a block or attribution. |
| Design | [docs/query_memory.md](../../../../query_memory.md), [docs/code_specs/primitives.md](../../../primitives.md), [docs/storage_journal.md](../../../../storage_journal.md) |

## B0039

[Lines 293–293](../../../../../src/resource/memory.cpp#L293); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
MemoryBlock::MemoryBlock(MemoryAccount::BlockData* data) noexcept
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Adopt the sole RAII handle of one newly admitted block. |
| inputs / outputs | Private construction stores the allocation's live BlockData pointer. |
| invariants | The account admission path has already linked/counted the block and retained its controller before this handle is returned. |
| ownership | The block handle owns raw allocation release, with no extra controller retain or second owner. |
| failure | Noexcept under the private allocation factory precondition. |
| cost | O(1) pointer assignment; no extra allocation. |
| Design | [docs/query_memory.md](../../../../query_memory.md), [docs/memory_accounts.md](../../../../memory_accounts.md) |

## B0040

[Lines 294–294](../../../../../src/resource/memory.cpp#L294); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
MemoryBlock::MemoryBlock(MemoryBlock&& other) noexcept
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Transfer a raw-block owner and empty the previous handle. |
| inputs / outputs | Exchanges the source header pointer with null. |
| invariants | Account totals, allocation identity and classification do not change when ownership moves. |
| ownership | Exactly one MemoryBlock remains responsible for freeing the existing header/payload. |
| failure | Noexcept, including moves from empty handles. |
| cost | O(1) pointer exchange; no allocation, data copy or ledger scan. |
| Design | [docs/query_memory.md](../../../../query_memory.md), [docs/memory_accounts.md](../../../../memory_accounts.md) |

## B0041

[Lines 295–298](../../../../../src/resource/memory.cpp#L295); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
MemoryBlock& MemoryBlock::operator=(MemoryBlock&& other) noexcept
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Free a previous block and replace it with another sole owner. |
| inputs / outputs | Nonself assignment reset()s the destination and exchanges the source header with null; returns *this. |
| invariants | Self move is a no-op. Distinct allocations keep their own account metadata even if the handles belong to different accounts. |
| ownership | Consumes the old block once, adopts the new block once and leaves the source empty. |
| failure | Noexcept; free enforces internal deallocation contracts without throwing. |
| cost | O(1) transfer plus one direct unlink/upstream deallocation when the destination was nonempty. |
| Design | [docs/query_memory.md](../../../../query_memory.md), [docs/memory_accounts.md](../../../../memory_accounts.md) |

## B0042

[Lines 299–299](../../../../../src/resource/memory.cpp#L299); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
MemoryBlock::~MemoryBlock()
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Release this sole raw allocation automatically at owner destruction. |
| inputs / outputs | Calls reset(), which consumes its header pointer or safely handles an empty block. |
| invariants | No typed payload destructor is invoked here; owners of constructed T must destroy it before this raw block release. |
| ownership | The allocation's independent controller reference survives until free has finished. |
| failure | Nonthrowing destructor; internal corrupt accounting/deallocation state terminates. |
| cost | O(1) account unlink/counters plus upstream delete; no allocation or payload traversal. |
| Design | [docs/query_memory.md](../../../../query_memory.md), [docs/memory_accounts.md](../../../../memory_accounts.md) |

## B0043

[Lines 300–300](../../../../../src/resource/memory.cpp#L300); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void MemoryBlock::reset()
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Release sole block ownership, including on moved-from or empty handles. |
| inputs / outputs | Exchanges the held BlockData pointer with null and frees the former block. |
| invariants | Repeated reset is harmless and cannot double-free. |
| ownership | The original block controller reference covers cleanup even if all MemoryAccount facades disappeared. |
| failure | Noexcept; free enforces internal lifetime contracts. |
| cost | O(1) unlink/deallocation, no allocation. |
| Design | [docs/query_memory.md](../../../../query_memory.md), [docs/code_specs/primitives.md](../../../primitives.md), [docs/storage_journal.md](../../../../storage_journal.md) |

## B0044

[Lines 301–301](../../../../../src/resource/memory.cpp#L301); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void* MemoryBlock::data() noexcept
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Borrow writable raw payload from a still-owned block. |
| inputs / outputs | Returns its payload pointer or nullptr when empty. |
| invariants | A real zero-payload block may return a nonnull aligned pointer; size() still reports the requested zero length. |
| ownership | The pointer is borrowed and cannot outlive the block allocation; callers must not independently delete it. |
| failure | Noexcept, with no required-nonempty check. |
| cost | O(1) header access; no allocation or scan. |
| Design | [docs/query_memory.md](../../../../query_memory.md), [docs/memory_accounts.md](../../../../memory_accounts.md) |

## B0045

[Lines 302–302](../../../../../src/resource/memory.cpp#L302); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
const void* MemoryBlock::data() const noexcept
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Borrow a const raw payload address without extending ownership. |
| inputs / outputs | Returns the same live payload address as the writable overload, or nullptr for empty state. |
| invariants | Const access does not imply that separately held owners cannot mutate payload; external synchronization remains required. |
| ownership | The pointer expires when the owning allocation is reset or destroyed. |
| failure | Noexcept for live, empty and moved handles. |
| cost | O(1) header access; no allocation or content copy. |
| Design | [docs/query_memory.md](../../../../query_memory.md), [docs/memory_accounts.md](../../../../memory_accounts.md) |

## B0046

[Lines 303–303](../../../../../src/resource/memory.cpp#L303); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::size_t MemoryBlock::size() const noexcept
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Read the caller's exact requested payload size. |
| inputs / outputs | Returns stored payload_size or zero for an empty handle. |
| invariants | Size excludes account/header/alignment allowance and can be zero even for a real charged allocation. |
| ownership | Scalar result only; no pointer or account handle escapes. |
| failure | Noexcept. |
| cost | O(1) metadata read; no recomputation, scan or allocation. |
| Design | [docs/query_memory.md](../../../../query_memory.md), [docs/memory_accounts.md](../../../../memory_accounts.md) |

## B0047

[Lines 304–304](../../../../../src/resource/memory.cpp#L304); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
MemoryUsage MemoryBlock::usage() const noexcept
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Read exact stored request and payload counters for this one block. |
| inputs / outputs | A live header yields {1,raw_size,payload_size}; an empty handle yields zero MemoryUsage. |
| invariants | A real zero-payload block still reports one allocation and framed requested bytes; no controller usage is included. |
| ownership | Returned scalar value is independent of the block lifetime. |
| failure | Noexcept under the live-header ownership invariant. |
| cost | O(1) fixed field reads, without recomputing alignment or scanning account totals. |
| Design | [docs/query_memory.md](../../../../query_memory.md), [docs/memory_accounts.md](../../../../memory_accounts.md) |

## B0048

[Lines 305–308](../../../../../src/resource/memory.cpp#L305); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
MemoryAccount::BlockData& MemoryBlock::required()
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Borrow metadata only from a nonempty block handle. |
| inputs / outputs | Returns the live header used by purpose/attribution/lifetime accessors. |
| invariants | A real zero-byte payload still has a nonempty block; moved/default handles do not. |
| ownership | Borrowed reference must not survive block reset/move/destruction. |
| failure | Empty block raises MemoryFailure(contract). |
| cost | O(1), no success-path allocation. |
| Design | [docs/query_memory.md](../../../../query_memory.md), [docs/code_specs/primitives.md](../../../primitives.md), [docs/storage_journal.md](../../../../storage_journal.md) |

## B0049

[Lines 309–309](../../../../../src/resource/memory.cpp#L309); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
MemoryPurpose MemoryBlock::purpose() const
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Read the immutable category of a real allocation. |
| inputs / outputs | Uses required() and returns its stored MemoryPurpose. |
| invariants | Default/reset/moved handles do not fabricate a scratch purpose; a real zero-payload allocation has valid metadata. |
| ownership | Inline enum copy from a borrowed live header. |
| failure | Empty state raises fixed MemoryFailure(contract). |
| cost | O(1) validation and read; no allocation on success. |
| Design | [docs/query_memory.md](../../../../query_memory.md), [docs/memory_accounts.md](../../../../memory_accounts.md) |

## B0050

[Lines 310–310](../../../../../src/resource/memory.cpp#L310); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
MemoryAttribution MemoryBlock::attribution() const
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Read this allocation's original query-local operator owner. |
| inputs / outputs | Uses required() and copies its MemoryAttribution. |
| invariants | Attribution is immutable even when the lifetime label changes; it remains scoped to the owning account. |
| ownership | The result owns no controller or allocation reference. |
| failure | Empty handle raises fixed MemoryFailure(contract). |
| cost | O(1) header/value access; no owner registry or scan. |
| Design | [docs/query_memory.md](../../../../query_memory.md), [docs/memory_accounts.md](../../../../memory_accounts.md) |

## B0051

[Lines 311–311](../../../../../src/resource/memory.cpp#L311); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
AllocationLifetime MemoryBlock::lifetime() const
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Read the current accounting classification of one owned block. |
| inputs / outputs | Uses required() and returns active, retained or free_pool. |
| invariants | The value describes a whole allocation and can change only through classification APIs, without changing total charged bytes. |
| ownership | Returns a copied enum; block ownership is unchanged. |
| failure | Empty handle raises fixed MemoryFailure(contract). |
| cost | O(1) metadata read; no allocation or ledger search. |
| Design | [docs/query_memory.md](../../../../query_memory.md), [docs/memory_accounts.md](../../../../memory_accounts.md) |

## B0052

[Lines 312–312](../../../../../src/resource/memory.cpp#L312); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
MemoryStatistics MemoryBlock::account_statistics() const
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Inspect the account that remains alive through this block's own reference. |
| inputs / outputs | A required live block returns a fixed copy of its owner controller's statistics. |
| invariants | The result describes the entire account rather than just this block; other handles may already be closed. External synchronization is still required. |
| ownership | Returned arrays/scalars own no block pointer or account handle. |
| failure | Empty block raises fixed MemoryFailure(contract); success performs no allocation. |
| cost | Fixed-size statistics copy, independent of outstanding allocation count. |
| Design | [docs/query_memory.md](../../../../query_memory.md), [docs/memory_accounts.md](../../../../memory_accounts.md) |

## B0053

[Lines 313–323](../../../../../src/resource/memory.cpp#L313); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void MemoryBlock::set_lifetime(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Classify directly owned block storage without freeing or refilling its account. |
| inputs / outputs | A live block and valid destination lifetime move its exact usage between fixed lifetime totals. |
| invariants | Requested/payload bytes and immutable attribution remain unchanged; equal classification is a no-op. |
| ownership | The MemoryBlock continues to own the same allocation. |
| failure | Invalid/empty state raises fixed MemoryFailure; upstream allocation reentry raises bad_alloc. Internal noexcept callers must establish these preconditions. |
| cost | O(1), nonallocating, no ledger scan. |
| Design | [docs/query_memory.md](../../../../query_memory.md), [docs/code_specs/primitives.md](../../../primitives.md), [docs/storage_journal.md](../../../../storage_journal.md) |

## B0055

[Lines 325–360](../../../../../src/resource/memory.cpp#L325); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void MemoryAccount::check_invariants()
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Independently reconcile allocation links, exact byte framing and statistics. |
| inputs / outputs | Valid account either passes or reports a fixed contract failure. |
| invariants | Detects list cycles, owner/back-pointer/size/attribution errors, partition/history inconsistencies and controller retention loss. |
| ownership | Borrows the ledger under external synchronization; uses only fixed stack arrays. |
| failure | Contract errors raise MemoryFailure; this diagnostic does not repair corrupted state. |
| cost | O(outstanding allocations), no dynamic scratch; diagnostic only, separate from O(1) ordinary accounting. |
| Design | [docs/query_memory.md](../../../../query_memory.md), [docs/code_specs/primitives.md](../../../primitives.md), [docs/storage_journal.md](../../../../storage_journal.md) |

## B0056

[Lines 361–362](../../../../../src/resource/memory.cpp#L361); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L361-L362:sha256:dac88a67995b7afa420dbeca9b79a3d6aa0eeffa831dda093f93c62eb2b7b46f
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Close the \`namespace crown::resource\` scope at this exact source boundary. |
| inputs / outputs | This token introduces no callable inputs or outputs. Declarations inside \`namespace crown::resource\` define the available names, members and operations. |
| invariants | The closing brace matches the opening \`namespace crown::resource\` at its lexical source position in src/resource/memory.cpp; it preserves C++ namespace/type nesting. |
| ownership | The closing delimiter creates no owner. Types closed by \`namespace crown::resource\` retain the lifetimes and allocator rules of their own fields and operations. |
| failure | No failure path executes at this closing delimiter. Failure and cleanup behavior belong to enclosed functions and owning types. |
| cost | The delimiter itself performs no runtime work; the enclosed initializers, methods and destructors carry their own costs. |
| Design | [docs/query_memory.md](../../../../query_memory.md), [docs/memory_accounts.md](../../../../memory_accounts.md), [docs/code_specs/primitives.md](../../../primitives.md), [docs/code_specs/subsystem_contracts.md](../../../subsystem_contracts.md) |
