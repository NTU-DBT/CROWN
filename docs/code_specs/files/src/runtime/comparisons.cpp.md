# `src/runtime/comparisons.cpp` — block usage map

[Source](../../../../../src/runtime/comparisons.cpp) · [Source index](../../../README.md) · [Subsystem contracts](../../../subsystem_contracts.md) · [Reviewed primitives](../../../primitives.md)

Reuse ordinary propagation and full hidden-variable assignments, filter before projection, deduplicate and publish prepaid source/result state.

Snapshot SHA-256: `2ce415ca56daea17f6c02a39da86dc910de3b523cf24d54e29c2873f764fbacd`. 302 lines partitioned into 47 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [comparisons](../../../subsystem_contracts.md#comparisons). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/comparisons.md](../../../../comparisons.md), [docs/query_memory.md](../../../../query_memory.md), [docs/code_review.md](../../../../code_review.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–12](../../../../../src/runtime/comparisons.cpp#L1) | Imports dependencies; declares namespace scope; declares aliases; declares types or opens a type body; declares values/defaults or compile-time conditions. |  · [reviewed contract](#b0001) |
| [B0002 · 13–16](../../../../../src/runtime/comparisons.cpp#L13) | Callable definition: template&lt;class T&gt; auto allocator(const resource::MemoryAccount& account, resource::MemoryPurpose purpose = resource::MemoryPurpos… | calls ; returns resource::MemoryAllocator&lt;T&gt;(account, purpose, memory) · [reviewed contract](#b0002) |
| [B0003 · 17–20](../../../../../src/runtime/comparisons.cpp#L17) | Callable definition: TupleVector output(const resource::MemoryAccount& account) | calls TupleVector; returns TupleVector(resource::OwnerAllocator&lt;storage::Tuple&gt;(account, · [reviewed contract](#b0003) |
| [B0004 · 21–23](../../../../../src/runtime/comparisons.cpp#L21) | Callable definition: void require(bool condition, const char* message) | calls Error; guard void require(bool condition, const char* message) { · [reviewed contract](#b0004) |
| [B0005 · 24–30](../../../../../src/runtime/comparisons.cpp#L24) | declares types or opens a type body. | source comment (unverified): // One selected wrapper balance covers the whole recompute/difference. Scalar · [reviewed contract](#b0005) |
| [B0006 · 31–35](../../../../../src/runtime/comparisons.cpp#L31) | Callable definition: void take(std::uint64_t amount = 1) | calls Error · [reviewed contract](#b0006) |
| [B0007 · 36–36](../../../../../src/runtime/comparisons.cpp#L36) | Callable definition: \[\[nodiscard\]\] std::uint64_t remaining() const noexcept | calls ; returns limit - metrics.work · [reviewed contract](#b0007) |
| [B0008 · 37–43](../../../../../src/runtime/comparisons.cpp#L37) | Callable definition: void scalar(const storage::ScalarView& value) | calls take, size, parts · [reviewed contract](#b0008) |
| [B0009 · 44–46](../../../../../src/runtime/comparisons.cpp#L44) | Callable definition: void payload(storage::RowView row) | calls cells, scalar; 1 loop sites · [reviewed contract](#b0009) |
| [B0010 · 47–50](../../../../../src/runtime/comparisons.cpp#L47) | Callable definition: std::strong_ordering compare(const storage::ScalarView& left, const storage::ScalarView& right) | calls scalar; returns left &lt;=&gt; right; source comment (unverified): // Admission and native schemas fix the exact same scalar kind. · [reviewed contract](#b0010) |
| [B0011 · 51–57](../../../../../src/runtime/comparisons.cpp#L51) | Callable definition: std::strong_ordering compare(storage::RowView left, storage::RowView right) | calls take, std::min, size; returns order; left.size() &lt;=&gt; right.size(); 1 loop sites · [reviewed contract](#b0011) |
| [B0012 · 58–62](../../../../../src/runtime/comparisons.cpp#L58) | Callable definition: std::strong_ordering compare(const storage::Tuple& left, const storage::Tuple& right) | calls values, native_view, require, has_value; guard require(a.has_value() && b.has_value(), "comparison state lost native payload ownership");; returns compare(*a, *b) · [reviewed contract](#b0012) |
| [B0013 · 63–66](../../../../../src/runtime/comparisons.cpp#L63) | Closes surrounding scope/type. | source comment (unverified): // This comparator exists ONLY in recomputation scratch. Its borrowed balance · [reviewed contract](#b0013) |
| [B0014 · 67–73](../../../../../src/runtime/comparisons.cpp#L67) | Type/record definition: struct RowLess | returns budget-&gt;compare(a.view(), b.view()) &lt; 0; budget-&gt;compare(a.view(), b) &lt; 0; source comment (unverified): // This comparator exists ONLY in recomputation scratch. Its borrowed balance · [reviewed contract](#b0014) |
| [B0015 · 74–78](../../../../../src/runtime/comparisons.cpp#L74) | Type/record definition: struct Writing |  · [reviewed contract](#b0015) |
| [B0016 · 79–79](../../../../../src/runtime/comparisons.cpp#L79) | Explanatory comments or spacing. |  |
| [B0017 · 80–83](../../../../../src/runtime/comparisons.cpp#L80) | Callable definition: storage::ScalarView operand(const Operand& input, storage::RowView assignment) | calls ; returns assignment\[variable-&gt;value\]; std::get&lt;storage::ScalarView&gt;(input) · [reviewed contract](#b0017) |
| [B0018 · 84–100](../../../../../src/runtime/comparisons.cpp#L84) | Callable definition: bool accepts(std::span&lt;const Predicate&gt; predicates, storage::RowView assignment, Budget& budget) | calls take, compare, operand; returns false; true; 1 loop sites · [reviewed contract](#b0018) |
| [B0019 · 101–106](../../../../../src/runtime/comparisons.cpp#L101) | Explanatory comments or spacing. | source comment (unverified): // Full survivor-factor witnesses retain hidden comparison variables. Native · [reviewed contract](#b0019) |
| [B0020 · 107–160](../../../../../src/runtime/comparisons.cpp#L107) | Callable definition: Vector&lt;storage::Tuple&gt; recompute(const CompiledProgram& program, const Binding& binding, SupportRuntime::EpochView view, Limits l… | calls account, metrics, take, witnesses; guard require(fields.size() == program.query().variables.size(), "whole-tree witness omitted a query vari…; returns result; growth copy_of, emplace, push_back, reserve; 4 loop sites; source comment (unverified): // Full survivor-factor witnesses retain hidden comparison variables. Native · [reviewed contract](#b0020) |
| [B0021 · 161–163](../../../../../src/runtime/comparisons.cpp#L161) | Explanatory comments or spacing. | source comment (unverified): // Sorted endpoint merge creates owning immutable row handles before source · [reviewed contract](#b0021) |
| [B0022 · 164–176](../../../../../src/runtime/comparisons.cpp#L164) | Callable definition: void difference(const Vector&lt;storage::Tuple&gt;& before, const Vector&lt;storage::Tuple&gt;& after, TupleVector& added, TupleVector& remov… | calls size, compare, take, push_back; growth push_back; 3 loop sites; source comment (unverified): // Sorted endpoint merge creates owning immutable row handles before source · [reviewed contract](#b0022) |
| [B0023 · 177–183](../../../../../src/runtime/comparisons.cpp#L177) | declares types or opens a type body. | source comment (unverified): // namespace · [reviewed contract](#b0023) |
| [B0024 · 184–206](../../../../../src/runtime/comparisons.cpp#L184) | Callable definition: Data(const CompiledProgram& source, std::span&lt;const planner::comparisons::Predicate&gt; input, Budget& budget) : account(source.acco… | calls account, program, constants, predicates; returns *variable; constants.back().view()\[0\]; growth copy_of, push_back, reserve; 1 loop sites · [reviewed contract](#b0024) |
| [B0025 · 207–207](../../../../../src/runtime/comparisons.cpp#L207) | Closes surrounding scope/type. |  · [reviewed contract](#b0025) |
| [B0026 · 208–211](../../../../../src/runtime/comparisons.cpp#L208) | Callable definition: const Binding::Data& Binding::data() const | calls Error; returns *data_ · [reviewed contract](#b0026) |
| [B0027 · 212–212](../../../../../src/runtime/comparisons.cpp#L212) | Callable definition: const CompiledProgram& Binding::program() const & | calls data; returns data().program · [reviewed contract](#b0027) |
| [B0028 · 213–213](../../../../../src/runtime/comparisons.cpp#L213) | Callable definition: std::span&lt;const Predicate&gt; Binding::predicates() const & | calls data; returns data().predicates · [reviewed contract](#b0028) |
| [B0029 · 214–214](../../../../../src/runtime/comparisons.cpp#L214) | Callable definition: const resource::MemoryAccount& Binding::account() const & | calls data; returns data().account · [reviewed contract](#b0029) |
| [B0030 · 215–215](../../../../../src/runtime/comparisons.cpp#L215) | Explanatory comments or spacing. |  |
| [B0031 · 216–231](../../../../../src/runtime/comparisons.cpp#L216) | Type/record definition: struct Runtime::Data | growth make_accounted_shared · [reviewed contract](#b0031) |
| [B0032 · 232–232](../../../../../src/runtime/comparisons.cpp#L232) | Explanatory comments or spacing. |  |
| [B0033 · 233–245](../../../../../src/runtime/comparisons.cpp#L233) | Callable definition: Runtime::Runtime(const planner::comparisons::Plan& plan, Options options) | calls take, sources, general, plan; growth make_accounted_unique; source comment (unverified): // Cold predicate freeze and initial answer construction share this ONE · [reviewed contract](#b0033) |
| [B0034 · 246–248](../../../../../src/runtime/comparisons.cpp#L246) | declares callable signatures; declares values/defaults or compile-time conditions. |  · [reviewed contract](#b0034) |
| [B0035 · 249–252](../../../../../src/runtime/comparisons.cpp#L249) | Callable definition: Runtime::Data& Runtime::data() const | calls Error; returns *data_ · [reviewed contract](#b0035) |
| [B0036 · 253–253](../../../../../src/runtime/comparisons.cpp#L253) | Callable definition: const CompiledProgram& Runtime::program() const & | calls data, program; returns data().binding.program() · [reviewed contract](#b0036) |
| [B0037 · 254–254](../../../../../src/runtime/comparisons.cpp#L254) | Callable definition: const Binding& Runtime::binding() const & | calls data; returns data().binding · [reviewed contract](#b0037) |
| [B0038 · 255–255](../../../../../src/runtime/comparisons.cpp#L255) | Callable definition: const resource::MemoryAccount& Runtime::account() const & | calls data; returns data().account · [reviewed contract](#b0038) |
| [B0039 · 256–256](../../../../../src/runtime/comparisons.cpp#L256) | Callable definition: bool Runtime::ready() const | calls data, ready; returns !d.busy && d.sources.ready() · [reviewed contract](#b0039) |
| [B0040 · 257–257](../../../../../src/runtime/comparisons.cpp#L257) | Callable definition: std::uint64_t Runtime::sequence() const | calls data, readable, sequence; returns d.sources.sequence() · [reviewed contract](#b0040) |
| [B0041 · 258–258](../../../../../src/runtime/comparisons.cpp#L258) | Callable definition: bool Runtime::has_answer() const | calls data, readable, empty; returns !d.rows.empty() · [reviewed contract](#b0041) |
| [B0042 · 259–259](../../../../../src/runtime/comparisons.cpp#L259) | Explanatory comments or spacing. |  |
| [B0043 · 260–284](../../../../../src/runtime/comparisons.cpp#L260) | Callable definition: Epoch Runtime::apply(const PhysicalSetUpdate& update) | calls data, readable, writing, take; returns change.native_changed; {std::move(input), d.binding, std::move(added), std::move(removed), metrics}; source comment (unverified): // Declare this before every temporary: it covers source/H-free publication, · [reviewed contract](#b0043) |
| [B0044 · 285–285](../../../../../src/runtime/comparisons.cpp#L285) | Explanatory comments or spacing. |  |
| [B0045 · 286–295](../../../../../src/runtime/comparisons.cpp#L286) | Callable definition: Snapshot Runtime::snapshot(Limits limits) const | calls data, readable, writing, take; returns {d.sources.sequence(), d.binding, std::move(rows), metrics}; growth push_back, reserve; 1 loop sites · [reviewed contract](#b0045) |
| [B0046 · 296–299](../../../../../src/runtime/comparisons.cpp#L296) | Callable definition: Database Runtime::source_snapshot() const | calls data, readable, writing, snapshot; returns d.sources.snapshot().physical · [reviewed contract](#b0046) |
| [B0047 · 300–302](../../../../../src/runtime/comparisons.cpp#L300) | declares callable signatures; declares values/defaults or compile-time conditions. | guard static_assert(std::is_nothrow_move_constructible_v&lt;Epoch&gt;);; source comment (unverified): // namespace crown::runtime::comparisons · [reviewed contract](#b0047) |

## B0001

[Lines 1–12](../../../../../src/runtime/comparisons.cpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L1-L12:sha256:aad8fbacb3f0ebdc13b75fcd62311b51c3620e6abc6b5f720270467cce0cecb9
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Set private original-account attribution and maintained-vector vocabulary. |
| inputs / outputs | Includes public runtime/error and standard ordered-container/arithmetic facilities; defines support-node attribution and Vector. |
| invariants | All internal vector arrays use nonpropagating MemoryAllocator; no hidden second account is declared. |
| ownership | Aliases own no payload; constructed containers borrow/share the supplied account. |
| failure | Inclusion and aliases do not catch or translate inherited failures. |
| cost | Compile-time setup only; actual array and node costs remain charged at their call sites. |
| Design | [Refactor.md](../../../../../Refactor.md), [docs/comparisons.md](../../../../comparisons.md), [src/runtime/comparisons.cpp](../../../../../src/runtime/comparisons.cpp) |

## B0002

[Lines 13–16](../../../../../src/runtime/comparisons.cpp#L13); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L13-L16:sha256:1397841814c21e90a3e38d5fe8863de615cb35416d00238072f90b8d7bba43c5
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Create a maintained or scratch allocator on the receiving query account. |
| inputs / outputs | MemoryAccount and optional MemoryPurpose in; typed MemoryAllocator out. |
| invariants | Attribution stays support_node/0 and allocator assignment cannot replace the retained budget. |
| ownership | Returned allocator retains the same account control; it allocates no container payload yet. |
| failure | Invalid account/purpose fails through the standard memory contract. |
| cost | Fixed allocator-handle construction, with later actual allocation/account bookkeeping. |
| Design | [Refactor.md](../../../../../Refactor.md), [docs/comparisons.md](../../../../comparisons.md), [src/runtime/comparisons.cpp](../../../../../src/runtime/comparisons.cpp), [include/crown/resource/allocator.hpp](../../../../../include/crown/resource/allocator.hpp) |

## B0003

[Lines 17–20](../../../../../src/runtime/comparisons.cpp#L17); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L17-L20:sha256:169c2c603c1964944f04bbbea63e15881249560653a8d0ee819f8e8a56769cd6
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Create an empty transferable comparison output array. |
| inputs / outputs | Original account in; empty TupleVector with output_buffer OwnerAllocator out. |
| invariants | No native payload or independent cap is created by the empty vector. |
| ownership | Capacity and copied native Tuple handles retain the same original account. |
| failure | Allocator contract refusal can occur before the empty array is returned. |
| cost | Fixed empty-container setup; subsequent capacity growth costs its real funded allocations. |
| Design | [Refactor.md](../../../../../Refactor.md), [docs/comparisons.md](../../../../comparisons.md), [src/runtime/comparisons.cpp](../../../../../src/runtime/comparisons.cpp) |

## B0004

[Lines 21–23](../../../../../src/runtime/comparisons.cpp#L21); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L21-L23:sha256:5e06bf1e741d2b376c5214f1623e1022e6270cc3c460409e0998342127a697a7
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Reject an impossible internal comparison state with a direct diagnostic. |
| inputs / outputs | Boolean condition and static message; returns on true or throws comparison_invariant. |
| invariants | This checks internal/API premises rather than providing a retry/recovery framework. |
| ownership | Inputs are borrowed and no success-state owner is changed. |
| failure | False throws crown::Error before the caller continues. |
| cost | Scalar branch on success; formatting/error allocation is exceptional work. |
| Design | [Refactor.md](../../../../../Refactor.md), [docs/comparisons.md](../../../../comparisons.md), [src/runtime/comparisons.cpp](../../../../../src/runtime/comparisons.cpp) |

## B0005

[Lines 24–30](../../../../../src/runtime/comparisons.cpp#L24); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L24-L30:sha256:f1b5ead17ea0bc25c89a1fa8a7fd584b2f34c0bdc7d59e2df80cbab30f7de23f
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Define the shared selected wrapper allowance and explain its scalar-byte metric. |
| inputs / outputs | Budget borrows Metrics and stores a uint64 limit for one composed operation. |
| invariants | metrics.work starts at zero and never exceeds limit; admitted extents are not measured wall time. |
| ownership | Budget never escapes the constructor/apply/snapshot scope; scratch comparators may borrow it only there. |
| failure | Exhaustion is handled by take(), with private operation state discarded by normal RAII. |
| cost | Fixed scalar state; all subsequent units consume this one balance. |
| Design | [Refactor.md](../../../../../Refactor.md), [docs/comparisons.md](../../../../comparisons.md), [src/runtime/comparisons.cpp](../../../../../src/runtime/comparisons.cpp) |

## B0006

[Lines 31–35](../../../../../src/runtime/comparisons.cpp#L31); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L31-L35:sha256:f64daee670a6b1445ec90903029c384fc2db343a7550b1e63fe67d8d9016e5be
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Consume selected units without overflowing the wrapper work counter. |
| inputs / outputs | Amount defaults to one; increases metrics.work after checking remaining capacity. |
| invariants | Prior work &lt;= limit is preserved, so limit-work subtraction cannot underflow. |
| ownership | Only the borrowed private Metrics counter changes; no payload is retained. |
| failure | Insufficient remaining work throws comparison_work_limit before increment. |
| cost | One bounded integer subtraction/comparison/addition, independent of requested amount. |
| Design | [Refactor.md](../../../../../Refactor.md), [docs/comparisons.md](../../../../comparisons.md), [src/runtime/comparisons.cpp](../../../../../src/runtime/comparisons.cpp) |

## B0007

[Lines 36–36](../../../../../src/runtime/comparisons.cpp#L36); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L36-L36:sha256:b03189754ae9512b96e66ce82e6f2711fece2488455bf96a0b1892f548d35e77
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Borrow the remaining wrapper allowance for bounded view construction. |
| inputs / outputs | Returns limit minus already consumed work, without consuming or creating a balance. |
| invariants | take() preserves work &lt;= limit; view work is subsequently consumed from this same wrapper budget. |
| ownership | Returns a scalar value, not an owning refill token. |
| failure | Noexcept under the maintained Budget invariant. |
| cost | One bounded subtraction. |
| Design | [Refactor.md](../../../../../Refactor.md), [docs/comparisons.md](../../../../comparisons.md), [src/runtime/comparisons.cpp](../../../../../src/runtime/comparisons.cpp) |

## B0008

[Lines 37–43](../../../../../src/runtime/comparisons.cpp#L37); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L37-L43:sha256:148a7d1c68c2d26380950f0256a6751a465ef987e666b78b908d09330b8138fe
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Admit a scalar read and its conservative string/decimal extent. |
| inputs / outputs | ScalarView in; increments field count, byte extent and total wrapper work. |
| invariants | String bytes and inline decimal digits are counted before comparison/copy; no floating conversion. |
| ownership | Views remain borrowed from live witness, literal or retained native payload owners. |
| failure | Field admission can succeed before byte refusal; those diagnostics remain private and are not refunded. |
| cost | Fixed tag inspection plus admitted extent units; later scalar comparison/copy performs actual byte work. |
| Design | [Refactor.md](../../../../../Refactor.md), [docs/comparisons.md](../../../../comparisons.md), [src/runtime/comparisons.cpp](../../../../../src/runtime/comparisons.cpp) |

## B0009

[Lines 44–46](../../../../../src/runtime/comparisons.cpp#L44); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L44-L46:sha256:2a845c41730640c40eb2f02f33a7f9c0c75e257dee94a247b46801fa04abb496
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Admit every field/extent of a row before a payload copy. |
| inputs / outputs | Borrowed RowView is traversed through scalar() using the existing shared Budget. |
| invariants | No new allowance is allocated per field or row. |
| ownership | The source owner must retain all cell/string data for this pass. |
| failure | Refusal stops the private copy path without publishing comparison state. |
| cost | O(row fields) metadata visits plus the sum of admitted scalar extents. |
| Design | [Refactor.md](../../../../../Refactor.md), [docs/comparisons.md](../../../../comparisons.md), [src/runtime/comparisons.cpp](../../../../../src/runtime/comparisons.cpp) |

## B0010

[Lines 47–50](../../../../../src/runtime/comparisons.cpp#L47); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L47-L50:sha256:1d2084c0fe7dba5fba56a710058c9e6001d3d676eaa803bb972d40bb2c2e663a
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Compare two exact same-type native scalar operands. |
| inputs / outputs | Admits both views, then returns their strong ordering. |
| invariants | Planner admission and native schemas establish equal ScalarType; variant tag ordering is not used as an implicit cast. |
| ownership | Both operands borrow live immutable owners for the comparison. |
| failure | Work/extent exhaustion occurs before the native ordering operation. |
| cost | Two field admissions plus actual string prefix or bounded decimal/date/integer comparison work. |
| Design | [Refactor.md](../../../../../Refactor.md), [docs/comparisons.md](../../../../comparisons.md), [src/runtime/comparisons.cpp](../../../../../src/runtime/comparisons.cpp) |

## B0011

[Lines 51–57](../../../../../src/runtime/comparisons.cpp#L51); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L51-L57:sha256:a82eaa4eac879f63f04442ab2fa1babc5038040af8ac7d2e4df3558762e61ca5
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Perform a budgeted lexicographic row comparison for dedup or endpoint merge. |
| inputs / outputs | Two RowViews in; strong ordering by first differing field, then arity. |
| invariants | Row-comparison count consumes structural work; only examined field prefixes consume scalar extents. |
| ownership | No descriptor/payload is copied or retained. |
| failure | Budget refusal may interrupt private set/merge work; committed rows remain untouched. |
| cost | O(examined fields and scalar bytes), not a constant-cost dictionary comparison. |
| Design | [Refactor.md](../../../../../Refactor.md), [docs/comparisons.md](../../../../comparisons.md), [src/runtime/comparisons.cpp](../../../../../src/runtime/comparisons.cpp) |

## B0012

[Lines 58–62](../../../../../src/runtime/comparisons.cpp#L58); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L58-L62:sha256:34c3eb2df98ce941474b717170137e4e30b3578b6f1fb0ec2cdd3e3d52352404
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Compare retained native Tuple payloads through their funded row views. |
| inputs / outputs | Two immutable Tuple handles in; validates native backing and delegates row ordering. |
| invariants | All comparison state tuples were built through the genuine result AccountedLayout. |
| ownership | Tuples retain payload ownership beyond temporary TupleValuesView adapters. |
| failure | Missing native backing throws comparison_invariant; delegated work can refuse. |
| cost | Fixed handle/view access followed by actual lexicographic scalar/byte cost. |
| Design | [Refactor.md](../../../../../Refactor.md), [docs/comparisons.md](../../../../comparisons.md), [src/runtime/comparisons.cpp](../../../../../src/runtime/comparisons.cpp) |

## B0013

[Lines 63–66](../../../../../src/runtime/comparisons.cpp#L63); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L63-L66:sha256:cbc83d3edef86fde0144c954fcd6319c889f23ccc0ff972e772d015087f44fc1
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Close Budget and specify why the following comparator cannot escape recomputation. |
| inputs / outputs | Documents the shared-balance lifetime required by scratch set operations. |
| invariants | The persistent result is a tuple vector, containing no Budget pointer. |
| ownership | Scratch comparator borrows an enclosing live Budget until set destruction. |
| failure | Comment and scope closure introduce no executable branch. |
| cost | No runtime operation; container operations carry their own costs. |
| Design | [Refactor.md](../../../../../Refactor.md), [docs/comparisons.md](../../../../comparisons.md), [src/runtime/comparisons.cpp](../../../../../src/runtime/comparisons.cpp) |

## B0014

[Lines 67–73](../../../../../src/runtime/comparisons.cpp#L67); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L67-L73:sha256:e5597056ebfc7e1459c61215509a059a6c8907974a18581aeea418316f9e39fc
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Adapt budgeted row comparison to transparent scratch-set probes. |
| inputs / outputs | AccountedRow/RowView combinations compare lexicographically through one borrowed Budget. |
| invariants | Comparator lives only in the recompute-local set and never in a returned Snapshot. |
| ownership | Set nodes/keys use the original account; comparator borrows rather than owns the balance. |
| failure | Comparison may throw on budget refusal; standard set exception guarantees and scratch destruction suffice. |
| cost | Each ordered lookup/insertion takes O(log distinct rows) scalar/byte comparisons in the usual set model. |
| Design | [Refactor.md](../../../../../Refactor.md), [docs/comparisons.md](../../../../comparisons.md), [src/runtime/comparisons.cpp](../../../../../src/runtime/comparisons.cpp) |

## B0015

[Lines 74–78](../../../../../src/runtime/comparisons.cpp#L74); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L74-L78:sha256:d28848b678dbf3f53e1ebaedce6131ea6e70001879e9afe87fa69246093fb7e1
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Hold the wrapper busy flag through success/refusal and temporary retirement. |
| inputs / outputs | Writing stores a bool reference, sets true on entry and clears it on destruction. |
| invariants | Caller checks readable before construction; guard is declared before every publication temporary. |
| ownership | Borrowed Data flag must outlive the guard; no new owner or mutex is created. |
| failure | Noexcept entry/exit; other RAII objects unwind while the flag remains set. |
| cost | Two scalar flag writes; this enforces serial visibility, not thread synchronization. |
| Design | [Refactor.md](../../../../../Refactor.md), [docs/comparisons.md](../../../../comparisons.md), [src/runtime/comparisons.cpp](../../../../../src/runtime/comparisons.cpp) |

## B0017

[Lines 80–83](../../../../../src/runtime/comparisons.cpp#L80); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L80-L83:sha256:4286f0ef0eab9700cdd61bacdc895457bd56882dce8fd113037dff73203bfcbf
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Read an admitted variable slot or frozen literal for predicate evaluation. |
| inputs / outputs | Runtime Operand and complete sorted assignment in; cheap ScalarView value out. |
| invariants | VariableId equals the verified whole-tree witness field position; constant-false emits no assignment to read. |
| ownership | Returned strings borrow the witness or immutable Binding literal block. |
| failure | Genuine admission and verified layout are preconditions; the helper adds no repeated range/type checks. |
| cost | Fixed variant dispatch/index access; scalar comparison work is admitted by the caller. |
| Design | [Refactor.md](../../../../../Refactor.md), [docs/comparisons.md](../../../../comparisons.md), [src/runtime/comparisons.cpp](../../../../../src/runtime/comparisons.cpp) |

## B0018

[Lines 84–100](../../../../../src/runtime/comparisons.cpp#L84); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L84-L100:sha256:f2360d75fa84a09d2d621229fdef481dc4ce56cc918c0cb69b7af23bbf08038c
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Evaluate the explicit conjunction before any head projection. |
| inputs / outputs | Frozen predicates plus complete assignment; returns false on the first failed relation. |
| invariants | All six exact operators use strong ordering; empty conjunction accepts; hidden operands stay available. |
| ownership | Reads only witness/Binding-owned cells; no projected answer is mutated here. |
| failure | Shared structural/scalar/byte budget may throw; private witness/result construction then unwinds. |
| cost | O(tested predicates plus their actual scalar/byte comparisons), with ordinary short circuiting. |
| Design | [Refactor.md](../../../../../Refactor.md), [docs/comparisons.md](../../../../comparisons.md), [src/runtime/comparisons.cpp](../../../../../src/runtime/comparisons.cpp) |

## B0019

[Lines 101–106](../../../../../src/runtime/comparisons.cpp#L101); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L101-L106:sha256:9672e631dfe5c99369da5afc79a42f78e2f982e3ea3e6f87aed832db6435e950
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Explain the whole-tree witness variable mapping and contradictory-operator exception. |
| inputs / outputs | Documents native complete-occurrence scopes and ascending VariableId output. |
| invariants | A canonical constant-false tree can retain declared variables yet produces no tuple or invalid operand read. |
| ownership | Witness metadata and payload are retained by the native cursor during use. |
| failure | This explanatory region executes no operation. |
| cost | No new paper algorithm or complexity claim is attached to the helper. |
| Design | [Refactor.md](../../../../../Refactor.md), [docs/comparisons.md](../../../../comparisons.md), [src/runtime/comparisons.cpp](../../../../../src/runtime/comparisons.cpp), [src/runtime/support.cpp](../../../../../src/runtime/support.cpp), [src/planner/verify.cpp](../../../../../src/planner/verify.cpp) |

## B0020

[Lines 107–160](../../../../../src/runtime/comparisons.cpp#L107); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L107-L160:sha256:89b9cc34befb99d03b5f892a6261dac112da9c534c872d8b3105b374f3f7b567
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Privately rebuild the exact comparison set from complete equality witnesses. |
| inputs / outputs | Genuine program, frozen Binding, owner-only EpochView, limits and shared Budget; returns sorted native Tuple state. |
| invariants | Verify all variable slots only for tree routes; filter first, project original ordered/repeated head, deduplicate; constant operators use native semantics. |
| ownership | One cumulative cursor and original-account scratch/vector/set/key/tuple allocations; projected borrows are frozen before witness retirement. |
| failure | Any view/cursor/work/row/account refusal discards private state; cursor/view close before source publication; no catch/journal framework. |
| cost | All native witness work plus predicate cost, O(log distinct) budgeted row comparisons and distinct payload copies; set/output bytes coexist temporarily; cleanup is real. |
| Design | [Refactor.md](../../../../../Refactor.md), [docs/comparisons.md](../../../../comparisons.md), [src/runtime/comparisons.cpp](../../../../../src/runtime/comparisons.cpp), [include/crown/runtime/support.hpp](../../../../../include/crown/runtime/support.hpp), [src/runtime/support.cpp](../../../../../src/runtime/support.cpp), [include/crown/storage/accounted_layout.hpp](../../../../../include/crown/storage/accounted_layout.hpp) |

## B0021

[Lines 161–163](../../../../../src/runtime/comparisons.cpp#L161); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L161-L163:sha256:4d91aeb1536f9f430313d8b21ccbafb0ea3e382d5ec3419cf4f953ed6d4f5d5c
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Distinguish exact endpoint answer changes from native local support events. |
| inputs / outputs | Describes the sorted before/after merge used by difference(). |
| invariants | Added/removed are sets in original head order, not signed local membership logs. |
| ownership | Merged delta handles retain payloads before any committed source row is retired. |
| failure | Comment performs no allocation or publication. |
| cost | The following merge bears its actual row comparison and output-array costs. |
| Design | [Refactor.md](../../../../../Refactor.md), [docs/comparisons.md](../../../../comparisons.md), [src/runtime/comparisons.cpp](../../../../../src/runtime/comparisons.cpp) |

## B0022

[Lines 164–176](../../../../../src/runtime/comparisons.cpp#L164); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L164-L176:sha256:37801650e4c40a14e191635113a5c77d9c5042e564e2679c37466cb2e17b9eef
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Materialize exact added/removed endpoint sets using a sorted merge. |
| inputs / outputs | Sorted distinct before/after state vectors; appends native Tuple handles to funded output vectors. |
| invariants | Equal rows emit neither delta; each unequal endpoint row emits once; one shared budget covers comparisons and copies. |
| ownership | Copies share immutable original-account payloads, preserving removed rows after deletion. |
| failure | Budget or output-array growth refusal leaves committed source/current state unchanged because commit has not occurred. |
| cost | O(before+after) row comparisons/handle visits, actual prefix bytes and O(delta) funded array capacity. |
| Design | [Refactor.md](../../../../../Refactor.md), [docs/comparisons.md](../../../../comparisons.md), [src/runtime/comparisons.cpp](../../../../../src/runtime/comparisons.cpp) |

## B0023

[Lines 177–183](../../../../../src/runtime/comparisons.cpp#L177); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L177-L183:sha256:63a4a39d8b918c70d94e2c4bad575a874f11918a49afabba80631921908a10aa
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Define the immutable comparison metadata owner’s account and storage members. |
| inputs / outputs | Binding::Data holds genuine CompiledProgram, literal AccountedRows and runtime Predicate arrays. |
| invariants | Predicate string views target owned constant blocks; program provenance remains equality-only. |
| ownership | All arrays/blocks/control use the receiving original account; destruction order retires predicates before constants. |
| failure | No constructor work is performed by these member declarations alone. |
| cost | Metadata space is O(predicate count plus literal payload bytes); final-owner cleanup visits it. |
| Design | [Refactor.md](../../../../../Refactor.md), [docs/comparisons.md](../../../../comparisons.md), [src/runtime/comparisons.cpp](../../../../../src/runtime/comparisons.cpp) |

## B0024

[Lines 184–206](../../../../../src/runtime/comparisons.cpp#L184); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L184-L206:sha256:f855d4097e2510a9b3d1624a1e90d8eb404ab187d6ac4dcce1317e513aa8cf70
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Freeze admitted predicates into native metadata using the constructor’s shared allowance. |
| inputs / outputs | Original-account CompiledProgram, planner predicate span and existing Budget&; builds immutable operands/constants. |
| invariants | No new allowance is created; operand count multiplication is checked; literal views never borrow caller Value storage. |
| ownership | CompiledProgram aliases genuine metadata; literals own one AccountedRow block each, arrays reserve funded capacity. |
| failure | Work/account/allocation refusal destroys incomplete private metadata and publishes no Runtime. |
| cost | O(predicates plus literal field/byte copies), reserved operand capacity and real account/control allocations. |
| Design | [Refactor.md](../../../../../Refactor.md), [docs/comparisons.md](../../../../comparisons.md), [src/runtime/comparisons.cpp](../../../../../src/runtime/comparisons.cpp) |

## B0025

[Lines 207–207](../../../../../src/runtime/comparisons.cpp#L207); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L207-L207:sha256:aa1d1a63390229c798347e83a0405441c9400035284ad168c1bf6cdf1d70a370
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Close the immutable Binding implementation type. |
| inputs / outputs | Completes the Data declaration after its freeze constructor. |
| invariants | Its arrays and native program obey their already specified ownership order. |
| ownership | No independent account or raw borrowed literal owner is introduced at closure. |
| failure | No executable action at the closing delimiter. |
| cost | No runtime work; Data destruction costs belong to its owned members. |
| Design | [Refactor.md](../../../../../Refactor.md), [docs/comparisons.md](../../../../comparisons.md), [src/runtime/comparisons.cpp](../../../../../src/runtime/comparisons.cpp) |

## B0026

[Lines 208–211](../../../../../src/runtime/comparisons.cpp#L208); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L208-L211:sha256:aecca346c2441c054e845bf1f1be228a83d9d07d34c85cc029daffa214731742
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Validate a live Binding before exposing private immutable Data. |
| inputs / outputs | Returns a const Data reference or rejects an empty handle. |
| invariants | Borrowed Data reference is valid only while a corresponding Binding owner survives. |
| ownership | No new shared control or metadata copy is created. |
| failure | Empty binding throws comparison_state directly. |
| cost | One owner-presence check/reference return on success. |
| Design | [Refactor.md](../../../../../Refactor.md), [docs/comparisons.md](../../../../comparisons.md), [src/runtime/comparisons.cpp](../../../../../src/runtime/comparisons.cpp) |

## B0027

[Lines 212–212](../../../../../src/runtime/comparisons.cpp#L212); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L212-L212:sha256:1c9c5021b3cd142893393016c080f75dcd9a8f11b6dede983b766634566de6b7
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Expose genuine original equality metadata from a live semantic Binding. |
| inputs / outputs | Returns const CompiledProgram& without exporting a DTO or comparison proof profile. |
| invariants | The actual comparison conjunction remains separately available in predicates(). |
| ownership | Reference borrows the Binding’s immutable shared owner. |
| failure | Empty binding delegates comparison_state rejection to data(). |
| cost | Fixed presence check and reference return; no payload copy. |
| Design | [Refactor.md](../../../../../Refactor.md), [docs/comparisons.md](../../../../comparisons.md), [src/runtime/comparisons.cpp](../../../../../src/runtime/comparisons.cpp) |

## B0028

[Lines 213–213](../../../../../src/runtime/comparisons.cpp#L213); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L213-L213:sha256:afb98666f1961b62a94e9f8b5bd21ac3c33e450e7ae3c43cf4c65fce3e4fee44
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Expose frozen native predicate operands under Binding lifetime. |
| inputs / outputs | Returns a const Predicate span in admitted conjunction order. |
| invariants | Literal ScalarViews borrow owned constant blocks, not original planner DTOs. |
| ownership | Caller keeps Binding alive for all span/string uses. |
| failure | Empty binding throws through data(); span construction itself allocates nothing. |
| cost | Fixed span construction; iterating/evaluating predicates has its separate actual cost. |
| Design | [Refactor.md](../../../../../Refactor.md), [docs/comparisons.md](../../../../comparisons.md), [src/runtime/comparisons.cpp](../../../../../src/runtime/comparisons.cpp) |

## B0029

[Lines 214–214](../../../../../src/runtime/comparisons.cpp#L214); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L214-L214:sha256:ed08cb0bb9d2c8102a2c3baa819d09c19c9a978a065c1ad41c77bb8d53f41d02
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Expose the Binding’s original allocation authority. |
| inputs / outputs | Returns const MemoryAccount& from immutable Data. |
| invariants | Getter does not mint, refill or switch the query budget. |
| ownership | Account reference borrows Binding ownership; copied account handles share the same control. |
| failure | Empty binding rejects through data(). |
| cost | Fixed reference access, without account-ledger scanning. |
| Design | [Refactor.md](../../../../../Refactor.md), [docs/comparisons.md](../../../../comparisons.md), [src/runtime/comparisons.cpp](../../../../../src/runtime/comparisons.cpp) |

## B0031

[Lines 216–231](../../../../../src/runtime/comparisons.cpp#L216); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L216-L231:sha256:eb3fcd5c9eb56488bd825e5236b52a3588f56b7a9e35695dd792d6bf63141b2f
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Own one physical coordinator, one semantic binding and one maintained comparison set. |
| inputs / outputs | Runtime::Data constructor receives a physical owner, admitted Plan, limits and shared constructor Budget&. |
| invariants | Account derives from source.plan(); state allocator is fixed to it; readable rejects both wrapper busy and native busy. |
| ownership | Data owns source, account-backed Binding and sorted native Tuple vector; busy is a serial visibility flag. |
| failure | Metadata construction can refuse privately; readable throws comparison_busy during publication/cursor pinning. |
| cost | One owner/control allocation plus explicit metadata setup; sorted state occupies O(result handles and payload bytes). |
| Design | [Refactor.md](../../../../../Refactor.md), [docs/comparisons.md](../../../../comparisons.md), [src/runtime/comparisons.cpp](../../../../../src/runtime/comparisons.cpp) |

## B0033

[Lines 233–245](../../../../../src/runtime/comparisons.cpp#L233); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L233-L245:sha256:91a32d273966a83b4623d3a11e940eb021c3d7f8b3bca96b361fd6ed4c7e7145
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Construct initially empty physical sources and their exact initial comparison answer. |
| inputs / outputs | Admitted Plan/Options; creates one physical owner, frozen Binding and initial sorted result. |
| invariants | Cold predicate freeze and initial recompute share exactly one wrapper Budget; native source import retains its separate original policy. |
| ownership | AccountedUnique funds Data; all view/cursor/scratch/result work uses its original account. |
| failure | Any constructor refusal destroys incomplete members; no facade becomes usable with a partial answer. |
| cost | Original physical admission plus predicate freeze and one complete initial witness computation, including constant true/false routes. |
| Design | [Refactor.md](../../../../../Refactor.md), [docs/comparisons.md](../../../../comparisons.md), [src/runtime/comparisons.cpp](../../../../../src/runtime/comparisons.cpp) |

## B0034

[Lines 246–248](../../../../../src/runtime/comparisons.cpp#L246); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L246-L248:sha256:d1c5047f2b9543cf3d82b13faa99266df419fa743ad54b0a7d9addc0e3f60d23
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Implement facade destruction and move-only transfer without copying native state. |
| inputs / outputs | Default destructor/move constructor/move assignment operate on the account-funded unique Data owner. |
| invariants | Moving leaves the old facade without executable Data and never substitutes another grant inside a live Data. |
| ownership | Destination takes source ownership; replacing a destination retires its prior Data. |
| failure | Moves are declared noexcept; later moved-from getters reject. |
| cost | Transfer is scalar ownership work; destruction/replacement pays actual retained state/control cleanup. |
| Design | [Refactor.md](../../../../../Refactor.md), [docs/comparisons.md](../../../../comparisons.md), [src/runtime/comparisons.cpp](../../../../../src/runtime/comparisons.cpp) |

## B0035

[Lines 249–252](../../../../../src/runtime/comparisons.cpp#L249); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L249-L252:sha256:2ddede69e4163ea25b61ed6722f0f60f375383ceb2de6fc3d2ced6177107823b
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Validate the facade’s unique Data handle. |
| inputs / outputs | Returns Data& for live owners, including const facade operations with a serial busy guard. |
| invariants | Const facade methods cannot be used concurrently with mutation; this helper supplies no synchronization. |
| ownership | Reference borrows the facade-owned AccountedUnique. |
| failure | Moved-from owner throws comparison_state. |
| cost | Fixed pointer test/reference return. |
| Design | [Refactor.md](../../../../../Refactor.md), [docs/comparisons.md](../../../../comparisons.md), [src/runtime/comparisons.cpp](../../../../../src/runtime/comparisons.cpp) |

## B0036

[Lines 253–253](../../../../../src/runtime/comparisons.cpp#L253); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L253-L253:sha256:1cf51007bfd9784bf39938e45c5e8c8f07fc65cd8d2e8863bc17fbc778f2d107
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Expose the genuine equality CompiledProgram associated with this comparison owner. |
| inputs / outputs | Returns const CompiledProgram& from the retained Binding. |
| invariants | Immutable provenance access remains safe during the wrapper busy window; comparison semantics require binding(). |
| ownership | Reference borrows the immutable Binding metadata owner. |
| failure | Moved-from facade rejects via data(); underlying live Binding is constructed once. |
| cost | Fixed handle/reference access; no source or result scan. |
| Design | [Refactor.md](../../../../../Refactor.md), [docs/comparisons.md](../../../../comparisons.md), [src/runtime/comparisons.cpp](../../../../../src/runtime/comparisons.cpp) |

## B0037

[Lines 254–254](../../../../../src/runtime/comparisons.cpp#L254); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L254-L254:sha256:e11944276c5c1d1a06faae08d0f1b90872be5309b6298d2bde61708440e03c81
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Expose the runtime’s actual comparison semantic binding. |
| inputs / outputs | Returns const Binding&; copying it retains immutable program/predicate/schema ownership. |
| invariants | Binding captures predicates rather than claiming a canonical identity or durability version. |
| ownership | Reference borrows facade; a copied Binding independently preserves constants. |
| failure | Moved-from facade rejects via data(). |
| cost | Reference return; copying a handle is shared-owner bookkeeping. |
| Design | [Refactor.md](../../../../../Refactor.md), [docs/comparisons.md](../../../../comparisons.md), [src/runtime/comparisons.cpp](../../../../../src/runtime/comparisons.cpp) |

## B0038

[Lines 255–255](../../../../../src/runtime/comparisons.cpp#L255); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L255-L255:sha256:37c4f8acd35c7d8ddcaa7d160f3861eaec3a86e914e16b0700d36317093af787
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Expose the physical owner’s original account to callers. |
| inputs / outputs | Returns const MemoryAccount& retained in Data. |
| invariants | No second account or per-operation memory refill is constructed. |
| ownership | Reference borrows Data; caller can retain a copy of the same account handle. |
| failure | Moved-from facade rejects via data(). |
| cost | Fixed metadata access. |
| Design | [Refactor.md](../../../../../Refactor.md), [docs/comparisons.md](../../../../comparisons.md), [src/runtime/comparisons.cpp](../../../../../src/runtime/comparisons.cpp) |

## B0039

[Lines 256–256](../../../../../src/runtime/comparisons.cpp#L256); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L256-L256:sha256:e8631935f49cb376508303223bc98ae80f2afa29b5a95725d45022e8566804a1
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Report whether both wrapper publication and native source owner are quiescent. |
| inputs / outputs | Returns !busy && sources.ready(). |
| invariants | False covers the gap after native commit and before result swap/retirement completes. |
| ownership | Reads only live Data/native flags; no reader lease is acquired. |
| failure | Moved-from facade rejects; live readiness query allocates nothing. |
| cost | Fixed flag/native-ready checks, without result enumeration. |
| Design | [Refactor.md](../../../../../Refactor.md), [docs/comparisons.md](../../../../comparisons.md), [src/runtime/comparisons.cpp](../../../../../src/runtime/comparisons.cpp) |

## B0040

[Lines 257–257](../../../../../src/runtime/comparisons.cpp#L257); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L257-L257:sha256:a62a92827b854bc9f3e97726737beb3898412feffdaf76d269e627338b4846ac
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Read the committed physical/comparison sequence when quiescent. |
| inputs / outputs | Checks Data readability, then returns sources.sequence(). |
| invariants | Source and comparison endpoints publish under the same wrapper barrier. |
| ownership | Scalar return retains no epoch or storage borrow. |
| failure | Busy owner throws comparison_busy; moved-from owner throws comparison_state. |
| cost | Fixed state checks and sequence access. |
| Design | [Refactor.md](../../../../../Refactor.md), [docs/comparisons.md](../../../../comparisons.md), [src/runtime/comparisons.cpp](../../../../../src/runtime/comparisons.cpp) |

## B0041

[Lines 258–258](../../../../../src/runtime/comparisons.cpp#L258); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L258-L258:sha256:db55a809358f6e2536ab1cd511ebd68c429de41f98162ff4150ba1a485cc9c36
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Read exact comparison nonemptiness from the committed set. |
| inputs / outputs | After readability check returns whether the maintained sorted vector is nonempty. |
| invariants | Uses comparison results, not the original equality query’s has_answer flag. |
| ownership | No row copy, cursor or lease is created. |
| failure | Busy/moved-from owners reject through existing direct guards. |
| cost | Fixed vector-size test; initial/update recomputation paid the actual answer work. |
| Design | [Refactor.md](../../../../../Refactor.md), [docs/comparisons.md](../../../../comparisons.md), [src/runtime/comparisons.cpp](../../../../../src/runtime/comparisons.cpp) |

## B0043

[Lines 260–284](../../../../../src/runtime/comparisons.cpp#L260); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L260-L284:sha256:005f030af91230256392b33349810129356e6d1fc21c1f457d80c65587dd1c64
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Atomically maintain source state, exact comparison results and owning endpoint deltas. |
| inputs / outputs | PhysicalSetUpdate in; PhysicalEpoch plus Binding, added/removed rows and actual Metrics out. |
| invariants | prepare drains all aliases; recompute only if any native_changed; full assignment filtering precedes projection; source commit follows all fallible work. |
| ownership | One source token owns rollback; scratch/deltas/current state use original account; equal-allocator swap publishes; guard outlives old-result/token retirement. |
| failure | Sequence/schema/constraint/native/view/cursor/work/row/account/allocation refusal unwinds privately, preserving committed source/current/sequence. |
| cost | Ordinary native propagation, optional all-witness recomputation, ordered dedup and endpoint merge; source constraints/allocator/cleanup costs remain explicit. |
| Design | [Refactor.md](../../../../../Refactor.md), [docs/comparisons.md](../../../../comparisons.md), [src/runtime/comparisons.cpp](../../../../../src/runtime/comparisons.cpp) |

## B0045

[Lines 286–295](../../../../../src/runtime/comparisons.cpp#L286); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L286-L295:sha256:7f5efcc434a12f1c3ff1b31887be8db0d01f556c13f0824df9a6b97a451dcfa4
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Create an owning eager snapshot of the committed comparison set. |
| inputs / outputs | Caller Limits bound copy work/rows; returns committed sequence, semantic Binding, sorted Tuple handles and copy metrics. |
| invariants | No witness traversal or query recomputation; rows share immutable native payloads and retain original repeated-head layout. |
| ownership | Funded OwnerAllocator vector and Binding survive runtime teardown without holding a source epoch lease. |
| failure | Busy/row/work/account/allocation refusal leaves committed state unchanged; incomplete copies destroy normally under the guard. |
| cost | O(result count) handle/array work and real capacity allocations; no repeated string payload copy. |
| Design | [Refactor.md](../../../../../Refactor.md), [docs/comparisons.md](../../../../comparisons.md), [src/runtime/comparisons.cpp](../../../../../src/runtime/comparisons.cpp) |

## B0046

[Lines 296–299](../../../../../src/runtime/comparisons.cpp#L296); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L296-L299:sha256:654a3200f587473d03948622be972e0ea9541eaec81af073df498bac8fb938c6
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Export the original physical-source database for external diagnostics. |
| inputs / outputs | Returns sources.snapshot().physical after serial readability/busy protection. |
| invariants | Includes original full source tables, not filtered comparison projections or a maintained source mirror. |
| ownership | Legacy Database/Row/string export belongs to the caller; internal native snapshot work still uses existing source rules. |
| failure | Inherited diagnostic allocation/account failures unwind without changing source/current state. |
| cost | Eager whole-source/support snapshot/export costs apply; this is not an update-path primitive. |
| Design | [Refactor.md](../../../../../Refactor.md), [docs/comparisons.md](../../../../comparisons.md), [src/runtime/comparisons.cpp](../../../../../src/runtime/comparisons.cpp) |

## B0047

[Lines 300–302](../../../../../src/runtime/comparisons.cpp#L300); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L300-L302:sha256:7d7cc230dd43ebd213d5c3fc186c375030113c6ba9cc485a1b9fbe9b1f02672b
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Require nonthrowing aggregate movement at the final publication return. |
| inputs / outputs | Compile-time checks that Epoch and Snapshot move constructors are noexcept. |
| invariants | After source commit and result swap, moving the prepared return value cannot allocate or throw. |
| ownership | Moves transfer already funded arrays, Binding and native epoch payload owners. |
| failure | Compilation fails if future member changes violate this barrier premise. |
| cost | Compile-time checks; runtime transfer/last-owner cleanup retains its actual costs. |
| Design | [Refactor.md](../../../../../Refactor.md), [docs/comparisons.md](../../../../comparisons.md), [src/runtime/comparisons.cpp](../../../../../src/runtime/comparisons.cpp) |
