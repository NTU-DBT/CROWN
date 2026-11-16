# `src/runtime/fallback.cpp` — block usage map

[Source](../../../../../src/runtime/fallback.cpp) · [Source index](../../../README.md) · [Subsystem contracts](../../../subsystem_contracts.md) · [Reviewed primitives](../../../primitives.md)

Capture funded physical source images, enumerate complete assignments iteratively, project and deduplicate privately, then publish prepaid source/result state.

Snapshot SHA-256: `31d1ff977cbae09f6fce6f64b5db01648f1cf400dd3909f97bcaeeaea250a8e9`. 251 lines partitioned into 44 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [fallback](../../../subsystem_contracts.md#fallback). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/fallback.md](../../../../fallback.md), [docs/source_images.md](../../../../source_images.md), [docs/query_memory.md](../../../../query_memory.md), [Refactor.md](../../../../../Refactor.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–14](../../../../../src/runtime/fallback.cpp#L1) | Imports dependencies; declares namespace scope; declares aliases; declares types or opens a type body; declares values/defaults or compile-time conditions. |  · [reviewed contract](#b0001) |
| [B0002 · 15–18](../../../../../src/runtime/fallback.cpp#L15) | Callable definition: template&lt;class T&gt; auto allocator(const resource::MemoryAccount& account, resource::MemoryPurpose purpose = resource::MemoryPurpos… | calls ; returns resource::MemoryAllocator&lt;T&gt;(account, purpose, memory) · [reviewed contract](#b0002) |
| [B0003 · 19–21](../../../../../src/runtime/fallback.cpp#L19) | Callable definition: TupleVector output(const resource::MemoryAccount& account) | calls TupleVector; returns TupleVector(resource::OwnerAllocator&lt;storage::Tuple&gt;(account, resource::MemoryPurpose::output_buffe… · [reviewed contract](#b0003) |
| [B0004 · 22–24](../../../../../src/runtime/fallback.cpp#L22) | Callable definition: void require(bool condition, const char* message) | calls Error; guard void require(bool condition, const char* message) { · [reviewed contract](#b0004) |
| [B0005 · 25–31](../../../../../src/runtime/fallback.cpp#L25) | declares types or opens a type body. | source comment (unverified): // One balance covers a constructor's metadata/initial answer, or one update's · [reviewed contract](#b0005) |
| [B0006 · 32–35](../../../../../src/runtime/fallback.cpp#L32) | Callable definition: void take(std::uint64_t amount = 1) | calls Error · [reviewed contract](#b0006) |
| [B0007 · 36–36](../../../../../src/runtime/fallback.cpp#L36) | Callable definition: \[\[nodiscard\]\] std::uint64_t remaining() const noexcept | calls ; returns limit - metrics.work · [reviewed contract](#b0007) |
| [B0008 · 37–43](../../../../../src/runtime/fallback.cpp#L37) | Callable definition: void scalar(const storage::ScalarView& value) | calls take, size, parts · [reviewed contract](#b0008) |
| [B0009 · 44–44](../../../../../src/runtime/fallback.cpp#L44) | Callable definition: void payload(storage::RowView row) | calls cells, scalar; 1 loop sites · [reviewed contract](#b0009) |
| [B0010 · 45–47](../../../../../src/runtime/fallback.cpp#L45) | Callable definition: std::strong_ordering compare(const storage::ScalarView& a, const storage::ScalarView& b) | calls scalar; returns a &lt;=&gt; b · [reviewed contract](#b0010) |
| [B0011 · 48–53](../../../../../src/runtime/fallback.cpp#L48) | Callable definition: std::strong_ordering compare(storage::RowView a, storage::RowView b) | calls take, std::min, size; returns order; a.size() &lt;=&gt; b.size(); 1 loop sites · [reviewed contract](#b0011) |
| [B0012 · 54–58](../../../../../src/runtime/fallback.cpp#L54) | Callable definition: std::strong_ordering compare(const storage::Tuple& a, const storage::Tuple& b) | calls values, native_view, require, has_value; guard require(left.has_value() && right.has_value(), "fallback result lost native payload ownership");; returns compare(*left, *right) · [reviewed contract](#b0012) |
| [B0013 · 59–61](../../../../../src/runtime/fallback.cpp#L59) | Closes surrounding scope/type. | source comment (unverified): // Only private evaluation scratch retains this borrowed balance. Persistent · [reviewed contract](#b0013) |
| [B0014 · 62–68](../../../../../src/runtime/fallback.cpp#L62) | Type/record definition: struct RowLess | returns budget-&gt;compare(a.view(), b.view()) &lt; 0; budget-&gt;compare(a.view(), b) &lt; 0; source comment (unverified): // Only private evaluation scratch retains this borrowed balance. Persistent · [reviewed contract](#b0014) |
| [B0015 · 69–73](../../../../../src/runtime/fallback.cpp#L69) | Type/record definition: struct Writing |  · [reviewed contract](#b0015) |
| [B0016 · 74–78](../../../../../src/runtime/fallback.cpp#L74) | Explanatory comments or spacing. | source comment (unverified): // Iterative occurrence-by-occurrence nested loops, including cyclic joins. · [reviewed contract](#b0016) |
| [B0017 · 79–102](../../../../../src/runtime/fallback.cpp#L79) | Callable definition: Vector&lt;storage::Tuple&gt; evaluate(const Binding& binding, const physical::SourceImage& image, Limits limits, Budget& budget) | calls query, account, result, distinct; returns result; !query.head.empty(); growth copy_of, emplace, push_back, reserve; 1 loop sites; source comment (unverified): // Iterative occurrence-by-occurrence nested loops, including cyclic joins. · [reviewed contract](#b0017) |
| [B0018 · 103–115](../../../../../src/runtime/fallback.cpp#L103) | Callable definition: void difference(const Vector&lt;storage::Tuple&gt;& before, const Vector&lt;storage::Tuple&gt;& after, TupleVector& added, TupleVector& remov… | calls size, compare, take, push_back; growth push_back; 3 loop sites · [reviewed contract](#b0018) |
| [B0019 · 116–117](../../../../../src/runtime/fallback.cpp#L116) | Closes surrounding scope/type. | source comment (unverified): // namespace · [reviewed contract](#b0019) |
| [B0020 · 118–127](../../../../../src/runtime/fallback.cpp#L118) | Type/record definition: struct Binding::Data |  · [reviewed contract](#b0020) |
| [B0021 · 128–131](../../../../../src/runtime/fallback.cpp#L128) | Callable definition: const Binding::Data& Binding::data() const | calls Error; returns *data_ · [reviewed contract](#b0021) |
| [B0022 · 132–132](../../../../../src/runtime/fallback.cpp#L132) | Callable definition: const program::Query& Binding::query() const & | calls data; returns data().frozen.query · [reviewed contract](#b0022) |
| [B0023 · 133–133](../../../../../src/runtime/fallback.cpp#L133) | Callable definition: const Profile& Binding::profile() const & | calls data; returns data().profile · [reviewed contract](#b0023) |
| [B0024 · 134–134](../../../../../src/runtime/fallback.cpp#L134) | Callable definition: const CompiledProgram& Binding::sources() const & | calls data; returns data().sources · [reviewed contract](#b0024) |
| [B0025 · 135–135](../../../../../src/runtime/fallback.cpp#L135) | Callable definition: const storage::AccountedLayout& Binding::result_layout() const & | calls data; returns data().frozen.layout · [reviewed contract](#b0025) |
| [B0026 · 136–136](../../../../../src/runtime/fallback.cpp#L136) | Callable definition: const resource::MemoryAccount& Binding::account() const & | calls data; returns data().account · [reviewed contract](#b0026) |
| [B0027 · 137–146](../../../../../src/runtime/fallback.cpp#L137) | declares types or opens a type body; declares values/defaults or compile-time conditions. |  · [reviewed contract](#b0027) |
| [B0028 · 147–158](../../../../../src/runtime/fallback.cpp#L147) | Callable definition: Data(PhysicalRuntime source, const planner::fallback::Plan& plan, Limits selected, Budget& budget) : account(source.plan().accoun… | calls account, plan, sources, std::move; growth make_accounted_shared; 1 loop sites · [reviewed contract](#b0028) |
| [B0029 · 159–161](../../../../../src/runtime/fallback.cpp#L159) | Callable definition: void readable() const | calls ready, Error · [reviewed contract](#b0029) |
| [B0030 · 162–163](../../../../../src/runtime/fallback.cpp#L162) | Closes surrounding scope/type. |  · [reviewed contract](#b0030) |
| [B0031 · 164–176](../../../../../src/runtime/fallback.cpp#L164) | Callable definition: Runtime::Runtime(const planner::fallback::Plan& plan, Options options) | calls take, sources, source_only, plan; growth make_accounted_unique, push_back; source comment (unverified): // All original physical relations start empty. A nonempty body has no · [reviewed contract](#b0031) |
| [B0032 · 177–179](../../../../../src/runtime/fallback.cpp#L177) | declares callable signatures; declares values/defaults or compile-time conditions. |  · [reviewed contract](#b0032) |
| [B0033 · 180–183](../../../../../src/runtime/fallback.cpp#L180) | Callable definition: Runtime::Data& Runtime::data() const | calls Error; returns *data_ · [reviewed contract](#b0033) |
| [B0034 · 184–184](../../../../../src/runtime/fallback.cpp#L184) | Callable definition: const Binding& Runtime::binding() const & | calls data; returns data().binding · [reviewed contract](#b0034) |
| [B0035 · 185–185](../../../../../src/runtime/fallback.cpp#L185) | Callable definition: const resource::MemoryAccount& Runtime::account() const & | calls data; returns data().account · [reviewed contract](#b0035) |
| [B0036 · 186–186](../../../../../src/runtime/fallback.cpp#L186) | Callable definition: bool Runtime::ready() const | calls data, ready; returns !d.busy && d.sources.ready() · [reviewed contract](#b0036) |
| [B0037 · 187–187](../../../../../src/runtime/fallback.cpp#L187) | Callable definition: std::uint64_t Runtime::sequence() const | calls data, readable, sequence; returns d.sources.sequence() · [reviewed contract](#b0037) |
| [B0038 · 188–188](../../../../../src/runtime/fallback.cpp#L188) | Callable definition: bool Runtime::has_answer() const | calls data, readable, empty; returns !d.rows.empty() · [reviewed contract](#b0038) |
| [B0039 · 189–189](../../../../../src/runtime/fallback.cpp#L189) | Explanatory comments or spacing. |  |
| [B0040 · 190–219](../../../../../src/runtime/fallback.cpp#L190) | Callable definition: Epoch Runtime::apply(const PhysicalSetUpdate& update) | calls data, readable, writing, take; guard } else { require(count != 0, "fallback table cardinality underflow"); --count; }; returns {std::move(input), d.binding, std::move(added), std::move(removed), metrics}; growth insert; 1 loop sites; source comment (unverified): // A source-only program has no derivation routes: physical change plus the · [reviewed contract](#b0040) |
| [B0041 · 220–227](../../../../../src/runtime/fallback.cpp#L220) | Callable definition: Snapshot Runtime::snapshot(Limits limits) const | calls data, readable, writing, take; returns {d.sources.sequence(), d.binding, std::move(rows), metrics}; growth push_back, reserve; 1 loop sites · [reviewed contract](#b0041) |
| [B0042 · 228–245](../../../../../src/runtime/fallback.cpp#L228) | Callable definition: Explain Runtime::explain() const | calls data, readable, writing, tables; returns {d.binding.profile(), std::move(tables), product, prefix,; 1 loop sites; source comment (unverified): // A later zero makes the full product exactly zero even after overflow. · [reviewed contract](#b0042) |
| [B0043 · 246–248](../../../../../src/runtime/fallback.cpp#L246) | Callable definition: Database Runtime::source_snapshot() const | calls data, readable, writing, snapshot; returns d.sources.snapshot().physical · [reviewed contract](#b0043) |
| [B0044 · 249–251](../../../../../src/runtime/fallback.cpp#L249) | declares callable signatures; declares values/defaults or compile-time conditions. | guard static_assert(std::is_nothrow_move_constructible_v&lt;Epoch&gt;);; source comment (unverified): // namespace crown::runtime::fallback · [reviewed contract](#b0044) |

## B0001

[Lines 1–14](../../../../../src/runtime/fallback.cpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L1-L14:sha256:566bb583a6fc46fd415b12cccf6f3a93a9b2ea62dde085125607bba2f8740a36
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Set up the fallback caller of the common conservative CQ evaluator. |
| inputs / outputs | Imports the unchanged public fallback facade and private cq_recompute helper; defines original-account vector attribution. |
| invariants | The helper supplies query freezing and complete-witness traversal, while this caller retains SET DISTINCT and set deltas. |
| ownership | Aliases create no new source owner or ordinary Query/Database mirror. |
| failure | Declarations introduce no retry, catch framework or native execution. |
| cost | Compile-time setup; concrete vector/set allocations and destruction retain their real costs. |
| Design | [Refactor.md](../../../../../Refactor.md), [docs/query_memory.md](../../../../query_memory.md), [src/runtime/fallback.cpp](../../../../../src/runtime/fallback.cpp), [src/runtime/cq_recompute.hpp](../../../../../src/runtime/cq_recompute.hpp) |

## B0002

[Lines 15–18](../../../../../src/runtime/fallback.cpp#L15); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L15-L18:sha256:1397841814c21e90a3e38d5fe8863de615cb35416d00238072f90b8d7bba43c5
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Construct a scratch or retained allocator bound to the original account. |
| inputs / outputs | MemoryAccount and MemoryPurpose in; typed MemoryAllocator out. |
| invariants | Support-node attribution and nonpropagating query budget remain fixed. |
| ownership | Allocator shares the supplied account control and allocates no array yet. |
| failure | Invalid account/purpose fails through the memory contract. |
| cost | Fixed allocator-handle bookkeeping; future node/array allocations carry their actual costs. |
| Design | [Refactor.md](../../../../../Refactor.md), [docs/query_memory.md](../../../../query_memory.md), [src/runtime/fallback.cpp](../../../../../src/runtime/fallback.cpp) |

## B0003

[Lines 19–21](../../../../../src/runtime/fallback.cpp#L19); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L19-L21:sha256:b809fb00d5e7377b01538390bf7cb23d6b9f0efeabc0a1fc8b00e7d2e3eba328
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Create an empty transferable native answer/delta array. |
| inputs / outputs | Original account in; TupleVector with output_buffer OwnerAllocator out. |
| invariants | No tuple data or extra allowance is minted by creating the empty vector. |
| ownership | Capacity and native immutable row handles retain the same original account. |
| failure | Allocator construction can reject an invalid account. |
| cost | Fixed empty-container setup; capacity growth is separately funded. |
| Design | [Refactor.md](../../../../../Refactor.md), [docs/query_memory.md](../../../../query_memory.md), [src/runtime/fallback.cpp](../../../../../src/runtime/fallback.cpp) |

## B0004

[Lines 22–24](../../../../../src/runtime/fallback.cpp#L22); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L22-L24:sha256:0cbf6d7579d23fd522d791fd258ee4b200c50d231d616882547b3600e8338833
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Stop an impossible internal evaluator state with a direct error. |
| inputs / outputs | Condition/static message returns normally or throws fallback_invariant. |
| invariants | Used for native ownership/cardinality premises, not a recovery framework. |
| ownership | Inputs borrow caller state; no success owner changes. |
| failure | False throws before the caller continues. |
| cost | One branch on success; exceptional diagnostic work remains actual cost. |
| Design | [Refactor.md](../../../../../Refactor.md), [docs/query_memory.md](../../../../query_memory.md), [src/runtime/fallback.cpp](../../../../../src/runtime/fallback.cpp) |

## B0005

[Lines 25–31](../../../../../src/runtime/fallback.cpp#L25); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L25-L31:sha256:ede2241529231edd65c09d4b6d3706d59e1e4363962172098900ed250970fdcd
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Define the single shared wrapper budget and its metric meaning. |
| inputs / outputs | Budget borrows Metrics and holds a uint64 limit for one composed constructor/update/snapshot. |
| invariants | metrics.work starts at zero and never exceeds limit; source work is consumed once from this balance. |
| ownership | Budget stays in the caller scope; only recompute-local comparators borrow it. |
| failure | Exhaustion unwinds private scratch and source token through existing RAII. |
| cost | Fixed scalar state; admitted byte extents do not imply exact instruction/wall-time accounting. |
| Design | [Refactor.md](../../../../../Refactor.md), [docs/query_memory.md](../../../../query_memory.md), [src/runtime/fallback.cpp](../../../../../src/runtime/fallback.cpp) |

## B0006

[Lines 32–35](../../../../../src/runtime/fallback.cpp#L32); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L32-L35:sha256:7061d29b369646d6eb1fb6f29e74b89c490a5819524cddbd9af3f60ed0da5256
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Consume selected units with a checked remaining-balance test. |
| inputs / outputs | Amount defaults to one; increases metrics.work after successful capacity check. |
| invariants | The maintained work&lt;=limit invariant prevents subtraction or counter wraparound. |
| ownership | Only borrowed private diagnostics change, never a retained result. |
| failure | Insufficient remaining work throws fallback_work_limit before increment. |
| cost | Fixed bounded integer operations independent of the requested amount. |
| Design | [Refactor.md](../../../../../Refactor.md), [docs/query_memory.md](../../../../query_memory.md), [src/runtime/fallback.cpp](../../../../../src/runtime/fallback.cpp) |

## B0007

[Lines 36–36](../../../../../src/runtime/fallback.cpp#L36); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L36-L36:sha256:b03189754ae9512b96e66ce82e6f2711fece2488455bf96a0b1892f548d35e77
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Borrow the unconsumed wrapper ceiling for source-image construction. |
| inputs / outputs | Returns limit-work without allocating or consuming another allowance. |
| invariants | The successful image actual work is subsequently charged exactly once to the same budget. |
| ownership | Scalar return retains no account/grant owner. |
| failure | Noexcept under Budget invariants. |
| cost | One bounded subtraction. |
| Design | [Refactor.md](../../../../../Refactor.md), [docs/query_memory.md](../../../../query_memory.md), [src/runtime/fallback.cpp](../../../../../src/runtime/fallback.cpp) |

## B0008

[Lines 37–43](../../../../../src/runtime/fallback.cpp#L37); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L37-L43:sha256:148a7d1c68c2d26380950f0256a6751a465ef987e666b78b908d09330b8138fe
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Admit a scalar read and conservative string/decimal bytes. |
| inputs / outputs | ScalarView updates field/byte counters and total selected work. |
| invariants | Extent admission precedes native equality/copy; exact scalar values never convert through floating point. |
| ownership | Scalar/string views borrow live source-image, literal or retained-row ownership. |
| failure | Byte refusal can follow field admission; private counters are consumed rather than refunded. |
| cost | Fixed tag/length inspection plus admitted extents; actual comparison/copy still examines its real bytes. |
| Design | [Refactor.md](../../../../../Refactor.md), [docs/query_memory.md](../../../../query_memory.md), [src/runtime/fallback.cpp](../../../../../src/runtime/fallback.cpp) |

## B0009

[Lines 44–44](../../../../../src/runtime/fallback.cpp#L44); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L44-L44:sha256:980e3b7a6d22104439239ad410c3da3356191861dddb917e49aa6a334c6e6fca
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Admit every row field before deep native payload retention. |
| inputs / outputs | Borrowed RowView traverses scalar() under the same operation balance. |
| invariants | No per-field/per-row allowance is created. |
| ownership | The underlying image/key owner remains alive through this pass. |
| failure | Work refusal stops private retention before publication. |
| cost | O(row fields plus admitted scalar extents). |
| Design | [Refactor.md](../../../../../Refactor.md), [docs/query_memory.md](../../../../query_memory.md), [src/runtime/fallback.cpp](../../../../../src/runtime/fallback.cpp) |

## B0010

[Lines 45–47](../../../../../src/runtime/fallback.cpp#L45); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L45-L47:sha256:6ca20360bec320fc77bff3189a1b18f9276033f8dd90ed7f17afc6cf02febcd6
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Compare two exact same-domain native scalar values. |
| inputs / outputs | Admits both scalars, then returns strong ordering. |
| invariants | Typed query/source admission establishes same ScalarType; variant tags do not implement implicit coercion. |
| ownership | Both operands retain their original live owners through the comparison. |
| failure | Field/byte exhaustion precedes actual native ordering. |
| cost | Two field admissions plus actual string-prefix or bounded native scalar comparison. |
| Design | [Refactor.md](../../../../../Refactor.md), [docs/query_memory.md](../../../../query_memory.md), [src/runtime/fallback.cpp](../../../../../src/runtime/fallback.cpp) |

## B0011

[Lines 48–53](../../../../../src/runtime/fallback.cpp#L48); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L48-L53:sha256:19b65f5371b2d3f66539a26034dce0bca25de3fffe647c50058e1f6880ba3d27
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Perform budgeted lexicographic row ordering for DISTINCT and endpoint merge. |
| inputs / outputs | Returns first differing scalar order or arity order. |
| invariants | One structural comparison unit and examined scalar prefixes are charged; row widths are not constant. |
| ownership | No payload or schema is copied/retained by the comparison. |
| failure | Refusal may interrupt private set/merge work without changing committed state. |
| cost | O(examined fields/bytes) per comparison, in addition to ordered-container comparison counts. |
| Design | [Refactor.md](../../../../../Refactor.md), [docs/query_memory.md](../../../../query_memory.md), [src/runtime/fallback.cpp](../../../../../src/runtime/fallback.cpp) |

## B0012

[Lines 54–58](../../../../../src/runtime/fallback.cpp#L54); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L54-L58:sha256:23bce3a33e05561d4c8452e0f0be571dd8bcb73909f3dedcb35efe4dfd35b504
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Compare retained native Tuple values without legacy export. |
| inputs / outputs | Obtains owning-handle-backed native views and delegates lexicographic row ordering. |
| invariants | Every retained fallback tuple originated from its original-head AccountedLayout. |
| ownership | Tuple ownership keeps values valid beyond temporary adapter objects. |
| failure | Missing native backing throws fallback_invariant; delegated selected work can refuse. |
| cost | Fixed view extraction followed by actual prefix scalar/byte costs. |
| Design | [Refactor.md](../../../../../Refactor.md), [docs/query_memory.md](../../../../query_memory.md), [src/runtime/fallback.cpp](../../../../../src/runtime/fallback.cpp) |

## B0013

[Lines 59–61](../../../../../src/runtime/fallback.cpp#L59); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L59-L61:sha256:7577a634a4abb38cebdbbd01a4a1a8017d7ef1951226653f6d2ea46f37893fa5
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Close Budget and document the scratch-only comparator borrow. |
| inputs / outputs | Explains why no borrowed balance is stored in persistent sorted state. |
| invariants | The maintained state is a native Tuple vector; comparator lifetime ends during evaluation. |
| ownership | Only the enclosing active Budget can be borrowed by following scratch set operations. |
| failure | Comment/scope closure performs no executable work. |
| cost | No new runtime primitive or theorem is declared. |
| Design | [Refactor.md](../../../../../Refactor.md), [docs/query_memory.md](../../../../query_memory.md), [src/runtime/fallback.cpp](../../../../../src/runtime/fallback.cpp) |

## B0014

[Lines 62–68](../../../../../src/runtime/fallback.cpp#L62); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L62-L68:sha256:e5597056ebfc7e1459c61215509a059a6c8907974a18581aeea418316f9e39fc
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Provide transparent budgeted ordering for owned keys and borrowed row probes. |
| inputs / outputs | RowLess handles AccountedRow/RowView combinations via one Budget pointer. |
| invariants | This comparator exists only in the local DISTINCT set and cannot escape into Snapshot/current state. |
| ownership | Set nodes/keys use the original account; its borrowed budget outlives destruction. |
| failure | Comparison work refusal is handled by standard set exception safety and private scratch teardown. |
| cost | Usual O(log distinct outputs) comparisons per ordered probe/insertion, each with field/byte-dependent cost. |
| Design | [Refactor.md](../../../../../Refactor.md), [docs/query_memory.md](../../../../query_memory.md), [src/runtime/fallback.cpp](../../../../../src/runtime/fallback.cpp) |

## B0015

[Lines 69–73](../../../../../src/runtime/fallback.cpp#L69); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L69-L73:sha256:d28848b678dbf3f53e1ebaedce6131ea6e70001879e9afe87fa69246093fb7e1
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Keep wrapper readers busy through publication/refusal and temporary retirement. |
| inputs / outputs | Sets the borrowed Data flag on construction and clears it on destruction. |
| invariants | Caller checks quiescence first; guard is declared before source/image/result temporaries. |
| ownership | Data flag outlives the scope; no mutex, second owner or recovery object is created. |
| failure | Noexcept flag entry/exit; all later-created temporaries unwind while still guarded. |
| cost | Two flag writes; caller serialization remains required. |
| Design | [Refactor.md](../../../../../Refactor.md), [docs/query_memory.md](../../../../query_memory.md), [src/runtime/fallback.cpp](../../../../../src/runtime/fallback.cpp) |

## B0016

[Lines 74–78](../../../../../src/runtime/fallback.cpp#L74); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L74-L78:sha256:42bf0fa048ca2cd52353273d1adb0ac646dcc145878d8639d269dbaee8330135
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Describe the iterative binding-frame algorithm and its scratch bound. |
| inputs / outputs | One position/mark per atom and a trail of newly bound VariableIds implement depth-first nested loops. |
| invariants | Trail contains at most V simultaneously bound variables; rollback is local evaluation, not source publication undo. |
| ownership | Frames hold indices only; source rows remain owned by the immutable private SourceImage. |
| failure | Comment performs no executable step. |
| cost | O(atom count plus variables) binding scratch; actual prefix work can be huge even for no final output. |
| Design | [Refactor.md](../../../../../Refactor.md), [docs/query_memory.md](../../../../query_memory.md), [src/runtime/fallback.cpp](../../../../../src/runtime/fallback.cpp) |

## B0017

[Lines 79–102](../../../../../src/runtime/fallback.cpp#L79); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L79-L102:sha256:ebc794660fb658b12b7b2e48816b4e813d68acb93e36dbd7b8a4440662587e6c
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Evaluate the original CQ as a sorted DISTINCT set through the common full-witness visitor. |
| inputs / outputs | Binding, one charged source image, limits and shared Budget yield native original-head Tuple state. |
| invariants | Only complete physical witnesses project; repeats/constants/hidden variables are matched first; Boolean SET support stops at its first match. |
| ownership | The local set owns accounted keys; visitor views borrow image/frozen literals only during the callback; final tuples use the original layout/account. |
| failure | Contradiction returns empty; row/work/account/allocation refusal discards private state before source publication. |
| cost | Visited join prefixes/terms/equality bytes plus O(log distinct keys) ordered comparisons, two funded payload forms and actual cleanup; visitor scratch retires before final tuple materialization. |
| Design | [Refactor.md](../../../../../Refactor.md), [docs/query_memory.md](../../../../query_memory.md), [src/runtime/fallback.cpp](../../../../../src/runtime/fallback.cpp), [src/runtime/cq_recompute.hpp](../../../../../src/runtime/cq_recompute.hpp), [include/crown/runtime/source_image.hpp](../../../../../include/crown/runtime/source_image.hpp), [docs/fallback.md](../../../../fallback.md) |

## B0018

[Lines 103–115](../../../../../src/runtime/fallback.cpp#L103); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L103-L115:sha256:37801650e4c40a14e191635113a5c77d9c5042e564e2679c37466cb2e17b9eef
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Build exact endpoint set differences by merging sorted unique answer vectors. |
| inputs / outputs | Before/after native state vectors append owning added/removed Tuple handles. |
| invariants | Equal rows emit no delta; each endpoint-only row appears exactly once in its respective array. |
| ownership | Delta handles share original-account immutable payloads, including deleted/old answers. |
| failure | Budget or array allocation refusal occurs before source publication and preserves committed endpoints. |
| cost | O(before+after) row comparisons/visits, their actual scalar prefix bytes, and O(delta) funded capacity. |
| Design | [Refactor.md](../../../../../Refactor.md), [docs/query_memory.md](../../../../query_memory.md), [src/runtime/fallback.cpp](../../../../../src/runtime/fallback.cpp) |

## B0019

[Lines 116–117](../../../../../src/runtime/fallback.cpp#L116); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L116-L117:sha256:c929980d95efc152dc886ac42af0f045075441dd18a8f886364828ead327bbd3
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | End the private fallback evaluator/helper scope. |
| inputs / outputs | Closes the anonymous namespace before immutable public Binding storage. |
| invariants | No private comparator, Budget borrow or temporary container becomes public state. |
| ownership | Scope delimiter retains no owner. |
| failure | No executable failure path. |
| cost | No runtime work. |
| Design | [Refactor.md](../../../../../Refactor.md), [docs/query_memory.md](../../../../query_memory.md), [src/runtime/fallback.cpp](../../../../../src/runtime/fallback.cpp) |

## B0020

[Lines 118–127](../../../../../src/runtime/fallback.cpp#L118); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L118-L127:sha256:d134bf8810748c306d30cb04cf8691f6cd52ef39b20e2fdad386fd79199a135a
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Own the original arbitrary CQ through shared native frozen metadata. |
| inputs / outputs | Data retains the source-only CompiledProgram, actual Profile, account and one FrozenQuery with original-head output layout. |
| invariants | FrozenQuery keeps all query terms/text/literals stable; source-only Query{} provenance is not an arbitrary-CQ certificate. |
| ownership | Shared Data and all metadata/layout allocations remain on the source program original account; no second retained catalog/query DTO. |
| failure | Shared constructor Budget, metadata size/layout ID overflow or original allocation authority can refuse before Runtime construction completes. |
| cost | One common metadata import over names/terms/literal fields/bytes plus layout construction and allocator/retirement costs. |
| Design | [Refactor.md](../../../../../Refactor.md), [docs/query_memory.md](../../../../query_memory.md), [src/runtime/fallback.cpp](../../../../../src/runtime/fallback.cpp), [src/runtime/cq_recompute.hpp](../../../../../src/runtime/cq_recompute.hpp), [include/crown/runtime/fallback.hpp](../../../../../include/crown/runtime/fallback.hpp) |

## B0021

[Lines 128–131](../../../../../src/runtime/fallback.cpp#L128); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L128-L131:sha256:fca64acb6cf1dca890e4a1b1cff13af40c5e0d1d7afa541f4f4ef33fb37d5934
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Validate a live immutable Binding before exposing its Data. |
| inputs / outputs | Returns const Data& or rejects the default empty handle. |
| invariants | The reference remains valid only under a retained Binding owner. |
| ownership | No metadata copy or new control/grant is created. |
| failure | Empty binding throws fallback_state. |
| cost | One shared-owner presence check/reference return. |
| Design | [Refactor.md](../../../../../Refactor.md), [docs/query_memory.md](../../../../query_memory.md), [src/runtime/fallback.cpp](../../../../../src/runtime/fallback.cpp) |

## B0022

[Lines 132–132](../../../../../src/runtime/fallback.cpp#L132); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L132-L132:sha256:36b6628df32fc4e1c57724d5c8c1a11edf0a6a2fa1d19aa5c581f219f54b2b0d
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Borrow the actual original-query native views from frozen storage. |
| inputs / outputs | Returns const program::Query& from Binding Data. |
| invariants | Views describe original arbitrary atoms/head/contradiction rather than the empty source-only query. |
| ownership | Lvalue Binding retains funded arrays/text/literals; callers must keep the handle alive while borrowing. |
| failure | Empty Binding rejects with fallback_state. |
| cost | Fixed handle check/reference return; no query copying. |
| Design | [Refactor.md](../../../../../Refactor.md), [docs/query_memory.md](../../../../query_memory.md), [src/runtime/fallback.cpp](../../../../../src/runtime/fallback.cpp), [src/runtime/cq_recompute.hpp](../../../../../src/runtime/cq_recompute.hpp) |

## B0023

[Lines 133–133](../../../../../src/runtime/fallback.cpp#L133); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L133-L133:sha256:3822eaceed3298d5156ac03943e71ef0d4b7a3a9e2c5e430f2cfc1a24a442524
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Expose explicit conservative fallback classification and guarantees. |
| inputs / outputs | Returns const planner Profile& with static labels and structural/reason enums. |
| invariants | No source-only constant profile or unavailable CROWN/GHD theorem is substituted. |
| ownership | Reference borrows immutable Binding; label data is static, not uncharged dynamic strings. |
| failure | Empty binding rejects via data(). |
| cost | Fixed metadata access; classification was paid during cold genuine admission. |
| Design | [Refactor.md](../../../../../Refactor.md), [docs/query_memory.md](../../../../query_memory.md), [src/runtime/fallback.cpp](../../../../../src/runtime/fallback.cpp) |

## B0024

[Lines 134–134](../../../../../src/runtime/fallback.cpp#L134); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L134-L134:sha256:7ab5c4ea903771eef27ee26b2c217a9dbda88c2f3c29cbff5387a43bb05e0536
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Expose genuine original-catalog source-coordination provenance. |
| inputs / outputs | Returns the retained source-only CompiledProgram. |
| invariants | Its schemas/constraints/backend are genuine, but its empty query identity/guarantee does not describe the original arbitrary CQ. |
| ownership | Reference borrows Binding’s shared native program owner. |
| failure | Empty binding rejects through data(). |
| cost | Fixed handle/reference access without source inspection. |
| Design | [Refactor.md](../../../../../Refactor.md), [docs/query_memory.md](../../../../query_memory.md), [src/runtime/fallback.cpp](../../../../../src/runtime/fallback.cpp) |

## B0025

[Lines 135–135](../../../../../src/runtime/fallback.cpp#L135); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L135-L135:sha256:b6495c7d42a6f45208355b764c2dbb90e9a91a430dd4be8d717c1393db8472d1
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Borrow the genuine original-head layout generated by FrozenQuery. |
| inputs / outputs | Returns AccountedLayout from frozen metadata. |
| invariants | Ordered/repeated head fields and first-occurrence DecimalSpec remain those of the original fallback query. |
| ownership | Layout and frozen Data retain the same original account. |
| failure | Empty Binding rejects with fallback_state. |
| cost | Fixed reference lookup; tuple materialization costs occur at evaluation. |
| Design | [Refactor.md](../../../../../Refactor.md), [docs/query_memory.md](../../../../query_memory.md), [src/runtime/fallback.cpp](../../../../../src/runtime/fallback.cpp), [src/runtime/cq_recompute.hpp](../../../../../src/runtime/cq_recompute.hpp) |

## B0026

[Lines 136–136](../../../../../src/runtime/fallback.cpp#L136); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L136-L136:sha256:ed08cb0bb9d2c8102a2c3baa819d09c19c9a978a065c1ad41c77bb8d53f41d02
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Expose the immutable binding’s original memory authority. |
| inputs / outputs | Returns const MemoryAccount& from native Data. |
| invariants | No allowance or new account is created by metadata access. |
| ownership | Reference borrows Binding; copied handles share the same original control. |
| failure | Empty binding rejects through data(). |
| cost | Fixed reference return, without a ledger scan. |
| Design | [Refactor.md](../../../../../Refactor.md), [docs/query_memory.md](../../../../query_memory.md), [src/runtime/fallback.cpp](../../../../../src/runtime/fallback.cpp) |

## B0027

[Lines 137–146](../../../../../src/runtime/fallback.cpp#L137); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L137-L146:sha256:729a81dca090e8cdb548acca3457336529f8d5efd87d822f6657b8f01b1fee4e
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Declare one source owner and fixed funded query/result/count state. |
| inputs / outputs | Runtime::Data stores account, PhysicalRuntime, Binding, limits, sorted Tuple state, cardinalities, used-table mask and busy flag. |
| invariants | Cardinalities count full physical rows once per table; self-join factors repeat only in evaluation/estimates. |
| ownership | All maintained arrays use nonpropagating allocators; query metadata has independent immutable Binding ownership. |
| failure | Declarations introduce no source publication or speculative row mutation. |
| cost | O(source state plus distinct answers plus catalog table slots and original-query metadata). |
| Design | [Refactor.md](../../../../../Refactor.md), [docs/query_memory.md](../../../../query_memory.md), [src/runtime/fallback.cpp](../../../../../src/runtime/fallback.cpp) |

## B0028

[Lines 147–158](../../../../../src/runtime/fallback.cpp#L147); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L147-L158:sha256:572c971382beb621c86727660f7ad4bb976e2f32b8af6883bbc4178679f1a794
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Initialize the original-account metadata/count/use-mask state. |
| inputs / outputs | One physical owner, admitted Plan, limits and existing constructor Budget& build native Data. |
| invariants | Account comes from sources.plan(); actual original atom tables set used bits; both fixed table arrays start at zero. |
| ownership | Accounted shared Binding/unique Data and every array use the one original memory authority. |
| failure | Cold import/vector admission/allocation refusal leaves no published facade or partial source answer. |
| cost | Original-query freeze plus O(catalog tables+atoms) selected initialization and actual funded allocations. |
| Design | [Refactor.md](../../../../../Refactor.md), [docs/query_memory.md](../../../../query_memory.md), [src/runtime/fallback.cpp](../../../../../src/runtime/fallback.cpp) |

## B0029

[Lines 159–161](../../../../../src/runtime/fallback.cpp#L159); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L159-L161:sha256:602bddbe85a4203fac92904c4f70e0e22094f3c4b4422968f380f41db0e6d5e9
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Reject observation of an in-progress wrapper/native publication. |
| inputs / outputs | readable() checks busy and sources.ready(). |
| invariants | Both native staging and the gap through result/count swap/retirement remain unreadable. |
| ownership | Reads existing owner flags and acquires no lease. |
| failure | Busy owner throws fallback_busy. |
| cost | Fixed flag/native readiness checks. |
| Design | [Refactor.md](../../../../../Refactor.md), [docs/query_memory.md](../../../../query_memory.md), [src/runtime/fallback.cpp](../../../../../src/runtime/fallback.cpp) |

## B0030

[Lines 162–163](../../../../../src/runtime/fallback.cpp#L162); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L162-L163:sha256:cdbb10f75f6890449819c9d57e5ae7b786fb73c5111c5d829c37bc18f3e053e8
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Close Runtime::Data after its quiescence guard. |
| inputs / outputs | Completes the native unique-owner implementation type. |
| invariants | Binding/rows/counts/source ownership remain exactly the preceding member graph. |
| ownership | No additional database mirror or undo container is added. |
| failure | Closure performs no executable operation. |
| cost | No runtime work beyond eventual actual member teardown. |
| Design | [Refactor.md](../../../../../Refactor.md), [docs/query_memory.md](../../../../query_memory.md), [src/runtime/fallback.cpp](../../../../../src/runtime/fallback.cpp) |

## B0031

[Lines 164–176](../../../../../src/runtime/fallback.cpp#L164); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L164-L176:sha256:bf71c708924c15c5d371d5c7cd9bf3480d7a2421262443722cc075abe62dca88
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Construct the fallback over initially empty original physical relations. |
| inputs / outputs | Admitted Plan/Options create one source-only owner, original Binding, zero counts and exact initial result. |
| invariants | One Budget covers metadata and initial answer; a nonempty body has no witness on empty sources, while a noncontradictory empty body yields one nullary row. |
| ownership | All Data/layout/answer payloads are original-account native owners; no source image is needed to prove empty initial relations. |
| failure | Any source/metadata/work/row/account/allocation refusal destroys incomplete construction. |
| cost | Genuine physical admission plus linear metadata import and at most one initial native result allocation. |
| Design | [Refactor.md](../../../../../Refactor.md), [docs/query_memory.md](../../../../query_memory.md), [src/runtime/fallback.cpp](../../../../../src/runtime/fallback.cpp) |

## B0032

[Lines 177–179](../../../../../src/runtime/fallback.cpp#L177); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L177-L179:sha256:d1c5047f2b9543cf3d82b13faa99266df419fa743ad54b0a7d9addc0e3f60d23
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Destroy or transfer the facade’s account-funded unique implementation owner. |
| inputs / outputs | Default destructor/move constructor/move assignment avoid copying maintained source/result state. |
| invariants | Moved-from facade has no executable Data; moves never mint or replace a budget inside an existing Data. |
| ownership | Destination adopts source ownership; replacement retires the old destination Data. |
| failure | Moves are noexcept; later moved-from getters reject. |
| cost | Ownership transfer is scalar; actual Data/source/output last-owner cleanup may traverse substantial state. |
| Design | [Refactor.md](../../../../../Refactor.md), [docs/query_memory.md](../../../../query_memory.md), [src/runtime/fallback.cpp](../../../../../src/runtime/fallback.cpp) |

## B0033

[Lines 180–183](../../../../../src/runtime/fallback.cpp#L180); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L180-L183:sha256:edf6c02bb0e5fce705a6acac0fa77c532672ac080e144be5e85ffd2d34d9f0e8
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Validate the facade’s private live Data handle. |
| inputs / outputs | Returns Data&, including for serial const diagnostics that set a busy scope. |
| invariants | Const facade use supplies no thread-safety or arbitrary concurrent mutation guarantee. |
| ownership | Reference borrows AccountedUnique ownership. |
| failure | Moved-from owner throws fallback_state. |
| cost | Fixed pointer test/reference access. |
| Design | [Refactor.md](../../../../../Refactor.md), [docs/query_memory.md](../../../../query_memory.md), [src/runtime/fallback.cpp](../../../../../src/runtime/fallback.cpp) |

## B0034

[Lines 184–184](../../../../../src/runtime/fallback.cpp#L184); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L184-L184:sha256:e11944276c5c1d1a06faae08d0f1b90872be5309b6298d2bde61708440e03c81
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Expose actual-query Binding from the live facade. |
| inputs / outputs | Returns const Binding&; a caller copy retains original query/schema/constants/profile independently. |
| invariants | Immutable metadata access does not pretend source-only program identity is original-query identity. |
| ownership | Borrowed reference requires facade; copied Binding owns the shared native metadata. |
| failure | Moved-from facade rejects through data(). |
| cost | Fixed reference access; handle copies are shared-owner bookkeeping. |
| Design | [Refactor.md](../../../../../Refactor.md), [docs/query_memory.md](../../../../query_memory.md), [src/runtime/fallback.cpp](../../../../../src/runtime/fallback.cpp) |

## B0035

[Lines 185–185](../../../../../src/runtime/fallback.cpp#L185); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L185-L185:sha256:37c4f8acd35c7d8ddcaa7d160f3861eaec3a86e914e16b0700d36317093af787
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Expose the runtime’s original allocation authority. |
| inputs / outputs | Returns const MemoryAccount& retained in Data. |
| invariants | No new cap/refill/source owner is created. |
| ownership | Reference borrows Data; copied account handles retain its existing control. |
| failure | Moved-from facade rejects via data(). |
| cost | Fixed metadata access. |
| Design | [Refactor.md](../../../../../Refactor.md), [docs/query_memory.md](../../../../query_memory.md), [src/runtime/fallback.cpp](../../../../../src/runtime/fallback.cpp) |

## B0036

[Lines 186–186](../../../../../src/runtime/fallback.cpp#L186); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L186-L186:sha256:e8631935f49cb376508303223bc98ae80f2afa29b5a95725d45022e8566804a1
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Report combined wrapper/native quiescence. |
| inputs / outputs | Returns !busy && sources.ready(). |
| invariants | False persists through native commit, count/result publication and old temporary retirement. |
| ownership | No source/image/result read lease is acquired. |
| failure | Moved-from facade rejects; live check allocates nothing. |
| cost | Fixed flag/native ready checks. |
| Design | [Refactor.md](../../../../../Refactor.md), [docs/query_memory.md](../../../../query_memory.md), [src/runtime/fallback.cpp](../../../../../src/runtime/fallback.cpp) |

## B0037

[Lines 187–187](../../../../../src/runtime/fallback.cpp#L187); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L187-L187:sha256:a62a92827b854bc9f3e97726737beb3898412feffdaf76d269e627338b4846ac
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Expose a committed sequence only when both owners are readable. |
| inputs / outputs | After readable(), returns sources.sequence(). |
| invariants | Original physical source and exact fallback answer endpoints share the publication barrier. |
| ownership | Scalar return retains no row or epoch borrow. |
| failure | Busy or moved-from owner rejects through direct guards. |
| cost | Fixed state checks and sequence read. |
| Design | [Refactor.md](../../../../../Refactor.md), [docs/query_memory.md](../../../../query_memory.md), [src/runtime/fallback.cpp](../../../../../src/runtime/fallback.cpp) |

## B0038

[Lines 188–188](../../../../../src/runtime/fallback.cpp#L188); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L188-L188:sha256:db55a809358f6e2536ab1cd511ebd68c429de41f98162ff4150ba1a485cc9c36
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Read exact original-query nonemptiness from committed result state. |
| inputs / outputs | Returns !rows.empty() after the readability guard. |
| invariants | Does not use the source-only empty query’s always-true support answer. |
| ownership | No tuple copy, image or cursor is created. |
| failure | Busy/moved-from owner rejects via existing guards. |
| cost | Fixed vector-size test; full answer construction was charged earlier. |
| Design | [Refactor.md](../../../../../Refactor.md), [docs/query_memory.md](../../../../query_memory.md), [src/runtime/fallback.cpp](../../../../../src/runtime/fallback.cpp) |

## B0040

[Lines 190–219](../../../../../src/runtime/fallback.cpp#L190); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L190-L219:sha256:8489313319351ad3697b15a1bc51b4f78363727a6fda2e7bbb0ab31135fb7f7e
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Publish one full-source input and exact fallback endpoint changes atomically. |
| inputs / outputs | PhysicalSetUpdate returns original source epoch, actual Binding, sorted added/removed rows and Metrics. |
| invariants | Recompute trigger is physical_changed plus ORIGINAL table-use and noncontradiction; source-only derivations are never used as a trigger. |
| ownership | Private image/evaluator/delta arrays use original account; source token owns rollback; count/result changes publish only after valid commit under the guard. |
| failure | Every source/constraint/capture/work/row/account/allocation failure retires private work and preserves committed sequence/sources/counts/answers. |
| cost | Full source validation/copy, all visited assignment prefixes/bytes, ordered DISTINCT, payload materialization, endpoint merge and actual retirement; no specialized bound. |
| Design | [Refactor.md](../../../../../Refactor.md), [docs/query_memory.md](../../../../query_memory.md), [src/runtime/fallback.cpp](../../../../../src/runtime/fallback.cpp), [include/crown/runtime/source_image.hpp](../../../../../include/crown/runtime/source_image.hpp), [src/runtime/physical.cpp](../../../../../src/runtime/physical.cpp) |

## B0041

[Lines 220–227](../../../../../src/runtime/fallback.cpp#L220); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L220-L227:sha256:b2197f2380e2fb2a262a48056c4a10a5194ad2d21ec94c7c70ad1a51d3d51c8e
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Copy the committed exact result into a transferable owning snapshot. |
| inputs / outputs | Caller limits bound copy work/distinct rows; returns sequence, Binding, native Tuple handles and Metrics. |
| invariants | No source capture or evaluator run occurs; ordered/repeated output schema remains unchanged. |
| ownership | Funded output vector and shared immutable payload/metadata owners survive Runtime teardown without source leases. |
| failure | Busy/work/row/account/allocation refusal leaves committed state intact and discards incomplete copies. |
| cost | O(result count) handle/capacity operations; no repeated scalar string payload copy. |
| Design | [Refactor.md](../../../../../Refactor.md), [docs/query_memory.md](../../../../query_memory.md), [src/runtime/fallback.cpp](../../../../../src/runtime/fallback.cpp) |

## B0042

[Lines 228–245](../../../../../src/runtime/fallback.cpp#L228); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L228-L245:sha256:787d3d11279f29f1304bace80ff4089dcb47a785ae7d5bd2f31bf759ce943f51
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Build owning cold diagnostics with actual cardinalities and safe advisory product estimates. |
| inputs / outputs | Returns Profile, funded table_rows, optional witness/prefix products, actual result_rows and account statistics. |
| invariants | Each atom repeats its physical table factor; multiplication/addition overflow gives nullopt; later zero recovers final zero but not an overflowed earlier prefix sum. |
| ownership | Cardinality output uses original-account OwnerAllocator; metadata/profile are immutable values. |
| failure | Diagnostic account/allocation refusal cannot alter committed rows/counts; busy guard covers allocation callbacks. |
| cost | O(catalog tables+original atoms); estimates ignore equality/constant selectivity and field/byte costs, so are not claimed execution bounds. |
| Design | [Refactor.md](../../../../../Refactor.md), [docs/query_memory.md](../../../../query_memory.md), [src/runtime/fallback.cpp](../../../../../src/runtime/fallback.cpp) |

## B0043

[Lines 246–248](../../../../../src/runtime/fallback.cpp#L246); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L246-L248:sha256:cf54f2f57ecbb937042a444cbc96fa5f8b49ff5cdd987187fab01087b2de6938
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Export complete original physical source state at an explicit external boundary. |
| inputs / outputs | Returns the genuine physical snapshot’s Database after readability/busy protection. |
| invariants | No fallback-filtered rows or maintained ordinary database mirror are substituted. |
| ownership | Ordinary exported Database/Row/string DTO allocation belongs to the caller; internal source work retains existing original-account rules. |
| failure | Inherited diagnostic export failures unwind without changing committed state. |
| cost | Eager source/support snapshot and export costs apply; not an internal update-path primitive. |
| Design | [Refactor.md](../../../../../Refactor.md), [docs/query_memory.md](../../../../query_memory.md), [src/runtime/fallback.cpp](../../../../../src/runtime/fallback.cpp) |

## B0044

[Lines 249–251](../../../../../src/runtime/fallback.cpp#L249); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L249-L251:sha256:ffc51968f29cc78bceb0c7356178e732de8454a0b35734872cead5d100e0a8f3
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Preserve the nonthrowing final return-movement premise. |
| inputs / outputs | Static assertions require Epoch and Snapshot noexcept move construction. |
| invariants | Moving already prepared aggregate results after source publication cannot allocate or throw. |
| ownership | Moves transfer existing funded row arrays, Binding and source epoch owners. |
| failure | Compilation rejects future member changes that violate the premise. |
| cost | Compile-time checks; runtime handle moves and eventual cleanup retain actual costs. |
| Design | [Refactor.md](../../../../../Refactor.md), [docs/query_memory.md](../../../../query_memory.md), [src/runtime/fallback.cpp](../../../../../src/runtime/fallback.cpp) |
