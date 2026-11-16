# `src/runtime/statistics_collection.cpp` — block usage map

[Source](../../../../../src/runtime/statistics_collection.cpp) · [Source index](../../../README.md) · [Subsystem contracts](../../../subsystem_contracts.md) · [Reviewed primitives](../../../primitives.md)

Capture bounded distributions, workload counters, owner memory and explain observations without mislabeling partial information as exact.

Snapshot SHA-256: `04fc4f91c4353c2a4b57c8b769025ff659c62ebf2e8b6533dfcde3274e6bd3c0`. 228 lines partitioned into 30 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [statistics](../../../subsystem_contracts.md#statistics). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/statistics.md](../../../../statistics.md), [docs/observability.md](../../../../observability.md), [docs/memory_reports.md](../../../../memory_reports.md), [docs/ranking_evaluation.md](../../../../ranking_evaluation.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–9](../../../../../src/runtime/statistics_collection.cpp#L1) | Imports dependencies; declares namespace scope; declares callable signatures; declares values/defaults or compile-time conditions. |  · [reviewed contract](#b0001) |
| [B0002 · 10–13](../../../../../src/runtime/statistics_collection.cpp#L10) | Callable definition: void add(U64& dst, U64 n, bool& saturated) noexcept | calls  · [reviewed contract](#b0002) |
| [B0003 · 14–14](../../../../../src/runtime/statistics_collection.cpp#L14) | Callable definition: void inc(U64& dst, bool& saturated) noexcept | calls add · [reviewed contract](#b0003) |
| [B0004 · 15–15](../../../../../src/runtime/statistics_collection.cpp#L15) | Closes surrounding scope/type. |  · [reviewed contract](#b0004) |
| [B0005 · 16–21](../../../../../src/runtime/statistics_collection.cpp#L16) | Callable definition: void Cell::observe(U64 v) noexcept | calls std::min, std::max, inc, add · [reviewed contract](#b0005) |
| [B0006 · 22–34](../../../../../src/runtime/statistics_collection.cpp#L22) | Callable definition: void Cell::merge(const Cell& c) noexcept | calls std::min, std::max, ADD, add; 1 loop sites · [reviewed contract](#b0006) |
| [B0007 · 35–38](../../../../../src/runtime/statistics_collection.cpp#L35) | declares namespace scope; declares callable signatures; declares values/defaults or compile-time conditions. | source comment (unverified): // namespace crown::runtime::workload · [reviewed contract](#b0007) |
| [B0008 · 39–41](../../../../../src/runtime/statistics_collection.cpp#L39) | Callable definition: void inc(U64& value, bool& saturated) noexcept | calls  · [reviewed contract](#b0008) |
| [B0009 · 42–42](../../../../../src/runtime/statistics_collection.cpp#L42) | Callable definition: bool valid(Kind k) | calls ; returns k == Kind::physical \|\| k == Kind::logical \|\| k == Kind::occurrence \|\| k == Kind::support \|\| k == Ki… · [reviewed contract](#b0009) |
| [B0010 · 43–43](../../../../../src/runtime/statistics_collection.cpp#L43) | Callable definition: bool valid(Operation o) | calls ; returns o == Operation::insert \|\| o == Operation::erase; growth insert · [reviewed contract](#b0010) |
| [B0011 · 44–44](../../../../../src/runtime/statistics_collection.cpp#L44) | Callable definition: bool root(Kind k) noexcept | calls ; returns k==Kind::physical \|\| k==Kind::logical · [reviewed contract](#b0011) |
| [B0012 · 45–45](../../../../../src/runtime/statistics_collection.cpp#L45) | Closes surrounding scope/type. |  · [reviewed contract](#b0012) |
| [B0013 · 46–46](../../../../../src/runtime/statistics_collection.cpp#L46) | Callable definition: Collector::Collector():Collector(resource::MemoryAccount::create(std::numeric_limits&lt;U64&gt;::max())) | calls Collector, resource::MemoryAccount::create, max · [reviewed contract](#b0013) |
| [B0014 · 47–50](../../../../../src/runtime/statistics_collection.cpp#L47) | Callable definition: Collector::Collector(const resource::MemoryAccount& account) :descriptors_(resource::MemoryAllocator&lt;Descriptor&gt;(account,resource… | calls descriptors_, committed_, attempt_, get_allocator · [reviewed contract](#b0014) |
| [B0015 · 51–88](../../../../../src/runtime/statistics_collection.cpp#L51) | Callable definition: void Collector::configure(Options o, std::span&lt;const Descriptor&gt; ds, std::size_t external_bytes) | calls pending, std::logic_error, std::invalid_argument, empty; 3 loop sites; source comment (unverified): // All possible throwing operations precede publication. · [reviewed contract](#b0015) |
| [B0016 · 89–91](../../../../../src/runtime/statistics_collection.cpp#L89) | Callable definition: void Collector::clear(MemoryVector&lt;Cell&gt;& slab) noexcept | calls inc; 1 loop sites · [reviewed contract](#b0016) |
| [B0017 · 92–109](../../../../../src/runtime/statistics_collection.cpp#L92) | Callable definition: Ticket Collector::admit(std::size_t physical) noexcept | calls pending, inc, clear, size; returns {}; {}; source comment (unverified): // Root attempts clear the whole scratch slab, including unsampled inputs. · [reviewed contract](#b0017) |
| [B0018 · 110–116](../../../../../src/runtime/statistics_collection.cpp#L110) | Callable definition: void Collector::physical_fact(bool changed) noexcept | calls pending, size · [reviewed contract](#b0018) |
| [B0019 · 117–123](../../../../../src/runtime/statistics_collection.cpp#L117) | Callable definition: void Collector::logical_fact(bool changed) noexcept | calls pending, size · [reviewed contract](#b0019) |
| [B0020 · 124–128](../../../../../src/runtime/statistics_collection.cpp#L124) | Callable definition: Ticket Collector::begin(std::size_t physical, bool changed) noexcept | calls admit, physical_fact; returns ticket · [reviewed contract](#b0020) |
| [B0021 · 129–137](../../../../../src/runtime/statistics_collection.cpp#L129) | Callable definition: Ticket Collector::nest(Ticket t) noexcept | calls pending; returns {}; {} · [reviewed contract](#b0021) |
| [B0022 · 138–167](../../../../../src/runtime/statistics_collection.cpp#L138) | Callable definition: bool Collector::finish(Ticket t, bool commit) noexcept | calls pending, inc, size, root; returns true; false; 1 loop sites; source comment (unverified): // Only complete selected detail merges; committed root facts stay separate. · [reviewed contract](#b0022) |
| [B0023 · 168–184](../../../../../src/runtime/statistics_collection.cpp#L168) | Callable definition: Cell* Collector::detail(std::size_t i, Kind kind) noexcept | calls inc, pending, size; returns nullptr; nullptr; source comment (unverified): // A physical no-op has no alias/support activity. Erroneous hooks invalidate · [reviewed contract](#b0023) |
| [B0024 · 185–189](../../../../../src/runtime/statistics_collection.cpp#L185) | Callable definition: void Collector::occurrence(std::size_t i, bool accepted) noexcept | calls detail, inc · [reviewed contract](#b0024) |
| [B0025 · 190–198](../../../../../src/runtime/statistics_collection.cpp#L190) | Callable definition: void Collector::support(std::size_t i, U64 before, U64 after) noexcept | calls detail, inc, observe · [reviewed contract](#b0025) |
| [B0026 · 199–201](../../../../../src/runtime/statistics_collection.cpp#L199) | Callable definition: void Collector::degree(std::size_t i, U64 value) noexcept | calls detail, observe · [reviewed contract](#b0026) |
| [B0027 · 202–209](../../../../../src/runtime/statistics_collection.cpp#L202) | Callable definition: bool Collector::reset() noexcept | calls pending, clear, inc; returns false; true · [reviewed contract](#b0027) |
| [B0028 · 210–219](../../../../../src/runtime/statistics_collection.cpp#L210) | Callable definition: bool Collector::rotate(U64 configuration, bool force) noexcept | calls pending, swap, clear; returns false; true · [reviewed contract](#b0028) |
| [B0029 · 220–227](../../../../../src/runtime/statistics_collection.cpp#L220) | Callable definition: Memory Collector::memory() const noexcept | calls capacity; returns m; source comment (unverified): // Component payload capacity only: account framing, producer route storage · [reviewed contract](#b0029) |
| [B0030 · 228–228](../../../../../src/runtime/statistics_collection.cpp#L228) | Closes surrounding scope/type. | source comment (unverified): // namespace crown::runtime::statistics_collection · [reviewed contract](#b0030) |

## B0001

[Lines 1–9](../../../../../src/runtime/statistics_collection.cpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
#include "statistics_collection.hpp"
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Assemble fixed numeric workload cells with saturating U64 arithmetic. |
| inputs / outputs | Collector header,algorithm/bit/limits/errors; private maximum=U64 max in workload namespace. |
| invariants | C01 observations never wrap or affect query answers; no C01 clock/timed mode implemented here. |
| ownership | Declarations hold no rows/account/state. |
| failure | No runtime handler/admission in includes/constants. |
| cost | Compile-time setup only. |
| Design | [docs/statistics.md](../../../../statistics.md), [include/crown/runtime/workload_statistics.hpp](../../../../../include/crown/runtime/workload_statistics.hpp), [src/runtime/statistics_collection.hpp](../../../../../src/runtime/statistics_collection.hpp), [docs/code_review.md](../../../../code_review.md) |

## B0002

[Lines 10–13](../../../../../src/runtime/statistics_collection.cpp#L10); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void add(U64& dst, U64 n, bool& saturated) noexcept {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Saturate one observation count/sum while recording loss of exactness. |
| inputs / outputs | Destination U64,n,sticky bool add or set dst=MAX and saturated=true. |
| invariants | No wrap; raw capped counts remain visible as lower bounds. Ratios/exact-feature consumers must reject saturation separately. |
| ownership | Mutates caller numeric fields only. |
| failure | noexcept; no allocation/query rejection. |
| cost | Constant checked arithmetic. |
| Design | [docs/statistics.md](../../../../statistics.md), [include/crown/runtime/workload_statistics.hpp](../../../../../include/crown/runtime/workload_statistics.hpp), [src/runtime/statistics_collection.hpp](../../../../../src/runtime/statistics_collection.hpp) |

## B0003

[Lines 14–14](../../../../../src/runtime/statistics_collection.cpp#L14); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void inc(U64& dst, bool& saturated) noexcept { add(dst, 1, saturated); }
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Increment one workload-cell field with the same saturation rule. |
| inputs / outputs | Counter and sticky flag forward add(...,1,...). |
| invariants | No independently inconsistent overflow policy. |
| ownership | Two borrowed mutable scalars. |
| failure | noexcept and allocation-free. |
| cost | Constant forwarding/check. |
| Design | [docs/statistics.md](../../../../statistics.md), [include/crown/runtime/workload_statistics.hpp](../../../../../include/crown/runtime/workload_statistics.hpp), [src/runtime/statistics_collection.hpp](../../../../../src/runtime/statistics_collection.hpp) |

## B0004

[Lines 15–15](../../../../../src/runtime/statistics_collection.cpp#L15); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L15-L15:sha256:412ca345ccf75bf9c0806bce695be8de808b79984251a7a54d202cf6101dd451
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Close the \`anonymous namespace in src/runtime/statistics_collection.cpp\` scope at this exact source boundary. |
| inputs / outputs | This token introduces no callable inputs or outputs. Declarations inside \`anonymous namespace in src/runtime/statistics_collection.cpp\` define the available names, members and operations. |
| invariants | The closing brace matches the opening \`anonymous namespace in src/runtime/statistics_collection.cpp\` at its lexical source position in src/runtime/statistics_collection.cpp; it preserves C++ namespace/type nesting. |
| ownership | The closing delimiter creates no owner. Types closed by \`anonymous namespace in src/runtime/statistics_collection.cpp\` retain the lifetimes and allocator rules of their own fields and operations. |
| failure | No failure path executes at this closing delimiter. Failure and cleanup behavior belong to enclosed functions and owning types. |
| cost | The delimiter itself performs no runtime work; the enclosed initializers, methods and destructors carry their own costs. |
| Design | [docs/statistics.md](../../../../statistics.md), [docs/memory_reports.md](../../../../memory_reports.md), [docs/query_memory.md](../../../../query_memory.md), [docs/code_specs/subsystem_contracts.md](../../../subsystem_contracts.md) |

## B0005

[Lines 16–21](../../../../../src/runtime/statistics_collection.cpp#L16); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void Cell::observe(U64 v) noexcept {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Observe an actual numeric event after-value, including zero. |
| inputs / outputs | U64 value initializes/updates min/max and saturating count/sum; increments bin bit_width(value) in fixed65-bin histogram. |
| invariants | Min/max meaningful only when count&gt;0. Bin0 is zero; repeated events are repeated observations, not distinct-key census. |
| ownership | Mutates fixed Cell fields; no values/rows retained. |
| failure | noexcept; saturation flags numerical lower-bound status instead of throwing. |
| cost | Constant fixed-word min/max/bit width/counter work, no scan or heap. |
| Design | [docs/statistics.md](../../../../statistics.md), [include/crown/runtime/workload_statistics.hpp](../../../../../include/crown/runtime/workload_statistics.hpp), [src/runtime/statistics_collection.hpp](../../../../../src/runtime/statistics_collection.hpp) |

## B0006

[Lines 22–34](../../../../../src/runtime/statistics_collection.cpp#L22); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void Cell::merge(const Cell& c) noexcept {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Merge one completed numeric attempt cell into committed observations. |
| inputs / outputs | Cell c contributes extrema when populated, sticky saturation, all census/detail/crossing/count/sum fields and65histogram bins. |
| invariants | No averaging/deduplication. Complete-input sample denominator is merged separately from all physical inputs; capped data remains marked. |
| ownership | Copies inline numeric fields only; no row/owner/cursor retained. |
| failure | noexcept; every addition saturates and propagates lower-bound status. |
| cost | Fixed scalar fields+65bin additions per merged cell; no allocation. |
| Design | [docs/statistics.md](../../../../statistics.md), [include/crown/runtime/workload_statistics.hpp](../../../../../include/crown/runtime/workload_statistics.hpp), [src/runtime/statistics_collection.hpp](../../../../../src/runtime/statistics_collection.hpp) |

## B0007

[Lines 35–38](../../../../../src/runtime/statistics_collection.cpp#L35); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
} // namespace crown::runtime::workload
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Enter the collector implementation namespace and its counter bound. |
| inputs / outputs | Namespace closures/opening and private maximum=U64 max for protocol/metadata counters. |
| invariants | Distinct workload-cell and collector helper scopes avoid exposing a new public numeric policy. |
| ownership | No runtime/account ownership in declaration. |
| failure | No action/failure. |
| cost | Compile-time constant only. |
| Design | [docs/statistics.md](../../../../statistics.md), [include/crown/runtime/workload_statistics.hpp](../../../../../include/crown/runtime/workload_statistics.hpp), [src/runtime/statistics_collection.hpp](../../../../../src/runtime/statistics_collection.hpp) |

## B0008

[Lines 39–41](../../../../../src/runtime/statistics_collection.cpp#L39); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void inc(U64& value, bool& saturated) noexcept {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Increment collector metadata/ordinal-generation diagnostics without wrap. |
| inputs / outputs | Mutable U64 and sticky flag increment or mark saturation at maximum. |
| invariants | Protocols separately stop ordinal/serial exhaustion rather than wrap capability IDs. |
| ownership | Numeric fields only. |
| failure | noexcept, no allocation. |
| cost | Constant branch/write. |
| Design | [docs/statistics.md](../../../../statistics.md), [include/crown/runtime/workload_statistics.hpp](../../../../../include/crown/runtime/workload_statistics.hpp), [src/runtime/statistics_collection.hpp](../../../../../src/runtime/statistics_collection.hpp) |

## B0009

[Lines 42–42](../../../../../src/runtime/statistics_collection.cpp#L42); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
bool valid(Kind k) { return k == Kind::physical || k == Kind::logical || k == Kind::occurrence || k == Kind::support || k == Kind::degree; }
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Admit only declared workload descriptor kinds. |
| inputs / outputs | Kind must be physical,logical,occurrence,support or degree. |
| invariants | Other descriptor role/scope/node relationships are validated by producing State and later consumers; this helper validates kind only. |
| ownership | Scalar enum,Boolean result. |
| failure | No throw/allocation. |
| cost | Five bounded enum comparisons. |
| Design | [docs/statistics.md](../../../../statistics.md), [include/crown/runtime/workload_statistics.hpp](../../../../../include/crown/runtime/workload_statistics.hpp), [src/runtime/statistics_collection.hpp](../../../../../src/runtime/statistics_collection.hpp) |

## B0010

[Lines 43–43](../../../../../src/runtime/statistics_collection.cpp#L43); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
bool valid(Operation o) { return o == Operation::insert || o == Operation::erase; }
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Admit only insert/erase initiating operations. |
| inputs / outputs | Operation returns true for insert/erase. |
| invariants | No semantic input operation is executed here. |
| ownership | Inline enum/Boolean only. |
| failure | No throw/allocation. |
| cost | Two comparisons. |
| Design | [docs/statistics.md](../../../../statistics.md), [include/crown/runtime/workload_statistics.hpp](../../../../../include/crown/runtime/workload_statistics.hpp), [src/runtime/statistics_collection.hpp](../../../../../src/runtime/statistics_collection.hpp) |

## B0011

[Lines 44–44](../../../../../src/runtime/statistics_collection.cpp#L44); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
bool root(Kind k) noexcept { return k==Kind::physical || k==Kind::logical; }
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Identify census root kinds for protocol admission/merge. |
| inputs / outputs | Kind physical or logical returns true. |
| invariants | Physical and lower-only logical scopes remain distinct even though both are roots. |
| ownership | Inline enum only. |
| failure | noexcept no allocation. |
| cost | Two comparisons. |
| Design | [docs/statistics.md](../../../../statistics.md), [include/crown/runtime/workload_statistics.hpp](../../../../../include/crown/runtime/workload_statistics.hpp), [src/runtime/statistics_collection.hpp](../../../../../src/runtime/statistics_collection.hpp) |

## B0012

[Lines 45–45](../../../../../src/runtime/statistics_collection.cpp#L45); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L45-L45:sha256:412ca345ccf75bf9c0806bce695be8de808b79984251a7a54d202cf6101dd451
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Close the \`anonymous namespace in src/runtime/statistics_collection.cpp\` scope at this exact source boundary. |
| inputs / outputs | This token introduces no callable inputs or outputs. Declarations inside \`anonymous namespace in src/runtime/statistics_collection.cpp\` define the available names, members and operations. |
| invariants | The closing brace matches the opening \`anonymous namespace in src/runtime/statistics_collection.cpp\` at its lexical source position in src/runtime/statistics_collection.cpp; it preserves C++ namespace/type nesting. |
| ownership | The closing delimiter creates no owner. Types closed by \`anonymous namespace in src/runtime/statistics_collection.cpp\` retain the lifetimes and allocator rules of their own fields and operations. |
| failure | No failure path executes at this closing delimiter. Failure and cleanup behavior belong to enclosed functions and owning types. |
| cost | The delimiter itself performs no runtime work; the enclosed initializers, methods and destructors carry their own costs. |
| Design | [docs/statistics.md](../../../../statistics.md), [docs/memory_reports.md](../../../../memory_reports.md), [docs/query_memory.md](../../../../query_memory.md), [docs/code_specs/subsystem_contracts.md](../../../subsystem_contracts.md) |

## B0013

[Lines 46–46](../../../../../src/runtime/statistics_collection.cpp#L46); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Collector::Collector():Collector(resource::MemoryAccount::create(std::numeric_limits<U64>::max())) {}
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Create an explicit standalone collector account at construction. |
| inputs / outputs | Default constructor delegates using new MemoryAccount with finite U64-max cap. |
| invariants | Native runtimes pass their existing original account instead; no per-event account refill. |
| ownership | Allocator members retain standalone controller; no descriptor/slab payload until configure. |
| failure | Account creation can fail before collector publication. |
| cost | One account admission and fixed vector allocator setup. |
| Design | [docs/statistics.md](../../../../statistics.md), [include/crown/runtime/workload_statistics.hpp](../../../../../include/crown/runtime/workload_statistics.hpp), [src/runtime/statistics_collection.hpp](../../../../../src/runtime/statistics_collection.hpp) |

## B0014

[Lines 47–50](../../../../../src/runtime/statistics_collection.cpp#L47); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Collector::Collector(const resource::MemoryAccount& account)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Bind all collector storage to one existing memory account. |
| inputs / outputs | Descriptor/current/attempt/previous vectors use same account,observation purpose and attribution. |
| invariants | Empty vectors initially allocate no slab; copying options later cannot replace allocation authority. |
| ownership | Each nonpropagating allocator retains original account. |
| failure | Invalid allocator/account contract can throw on construction; partial owners unwind. |
| cost | Fixed account handles/empty vector controls. |
| Design | [docs/statistics.md](../../../../statistics.md), [include/crown/runtime/workload_statistics.hpp](../../../../../include/crown/runtime/workload_statistics.hpp), [src/runtime/statistics_collection.hpp](../../../../../src/runtime/statistics_collection.hpp) |

## B0015

[Lines 51–88](../../../../../src/runtime/statistics_collection.cpp#L51); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void Collector::configure(Options o, std::span<const Descriptor> ds, std::size_t external_bytes) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Prepare complete collector configuration before nonthrowing publication. |
| inputs / outputs | Quiescent collector validates mode/sampling/cell dimensions,descriptor kinds/root scope/duplicates/root binding; allocates private descriptor/current/attempt/previous arrays and checks actual capacities+external bytes, then swaps/options/reset. |
| invariants | Off requires empty descriptors and no retained vector payload. Never publishes partial strata. external_bytes covers producer routing component payload, not actual total account framing. No queries/rows/clocks are read. |
| ownership | Old/new same-account arrays overlap temporarily; private locals release old storage after publication. All allocations precede swaps/reset. |
| failure | Pending/invalid/duplicate/overflow/cap/allocation error preserves prior live configuration. No local catch/inverse needed for private vectors. |
| cost | O(D^2) duplicate/root searches, O(D*CellSize) zeroing/copy plus4vector allocations as nonempty; original account enforces peak overlap. |
| Design | [docs/statistics.md](../../../../statistics.md), [include/crown/runtime/workload_statistics.hpp](../../../../../include/crown/runtime/workload_statistics.hpp), [src/runtime/statistics_collection.hpp](../../../../../src/runtime/statistics_collection.hpp), [src/runtime/workload_statistics.cpp](../../../../../src/runtime/workload_statistics.cpp) |

```text
MemoryVector<Descriptor> descriptors(ds.begin(),ds.end(),descriptors_.get_allocator());
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Fund a full replacement collector before committing configuration. |
| inputs / outputs | Private descriptor/current/attempt/previous arrays and actual-capacity arithmetic all complete before live swaps/options/reset. |
| invariants | Strong guarantee needs transient old/new overlap; no catch/restoration graph required for local vector owners. |
| ownership | Original account and matching nonpropagating allocators retained throughout. |
| failure | Any allocation/capacity failure frees candidates and preserves previous collector. |
| cost | 4nonempty vector allocations/copies/zeroing and capacity-sized memory overlap. |
| Design | [docs/statistics.md](../../../../statistics.md), [include/crown/runtime/workload_statistics.hpp](../../../../../include/crown/runtime/workload_statistics.hpp), [src/runtime/statistics_collection.hpp](../../../../../src/runtime/statistics_collection.hpp) |

## B0016

[Lines 89–91](../../../../../src/runtime/statistics_collection.cpp#L89); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void Collector::clear(MemoryVector<Cell>& slab) noexcept {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Zero one dense numeric slab and record actual clearing work. |
| inputs / outputs | Each existing Cell resets and increments meta.cleared_cells with saturation. |
| invariants | No capacity changes; clearing costs remain even for unsampled attempts. |
| ownership | Mutates existing preallocated vector cells/metadata. |
| failure | noexcept, no allocation. |
| cost | O(slab size*fixed Cell size), including65bins per cell. |
| Design | [docs/statistics.md](../../../../statistics.md), [include/crown/runtime/workload_statistics.hpp](../../../../../include/crown/runtime/workload_statistics.hpp), [src/runtime/statistics_collection.hpp](../../../../../src/runtime/statistics_collection.hpp) |

## B0017

[Lines 92–109](../../../../../src/runtime/statistics_collection.cpp#L92); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Ticket Collector::admit(std::size_t physical) noexcept {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Admit a root collection attempt and choose deterministic detail sampling. |
| inputs / outputs | Enabled idle collector allocates serial/depth,binds root,selects zero-based ordinal%period==offset,advances ordinal,counts attempt/selection and clears entire scratch slab. |
| invariants | Every admitted attempt including abort/noop consumes ordinal; no random sampling/confidence guarantee. Serial/ordinal exhaustion records unusability; invalid root poisons. Nested root misuse marks protocol error. |
| ownership | Scalar Ticket and existing slabs only; no allocation/row capture. |
| failure | noexcept, report degradation rather than query throw. Caller must finish returned valid ticket exactly. |
| cost | O(D) scratch clear+fixed protocol; off path constant. |
| Design | [docs/statistics.md](../../../../statistics.md), [include/crown/runtime/workload_statistics.hpp](../../../../../include/crown/runtime/workload_statistics.hpp), [src/runtime/statistics_collection.hpp](../../../../../src/runtime/statistics_collection.hpp) |

## B0018

[Lines 110–116](../../../../../src/runtime/statistics_collection.cpp#L110); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void Collector::physical_fact(bool changed) noexcept {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Record one actual physical changed/no-op input fact independently of sampled detail. |
| inputs / outputs | Pending root of Kind::physical with no prior staged fact stores inputs1,changed0/1,noop complementary. |
| invariants | Duplicate/wrong/no pending root marks protocol error and poisons current attempt. No-op still enters committed census and eligible complete-sample denominator. |
| ownership | Mutates one preallocated attempt Cell and flags, retains no input row. |
| failure | noexcept with numeric protocol status; no query rollback. |
| cost | Constant checks/scalar stores. |
| Design | [docs/statistics.md](../../../../statistics.md), [include/crown/runtime/workload_statistics.hpp](../../../../../include/crown/runtime/workload_statistics.hpp), [src/runtime/statistics_collection.hpp](../../../../../src/runtime/statistics_collection.hpp) |

## B0019

[Lines 117–123](../../../../../src/runtime/statistics_collection.cpp#L117); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void Collector::logical_fact(bool changed) noexcept {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Record one actual logical changed/no-op input fact independently of sampled detail. |
| inputs / outputs | Pending root of Kind::logical with no prior staged fact stores inputs1,changed0/1,noop complementary. |
| invariants | Duplicate/wrong/no pending root marks protocol error and poisons current attempt. No-op still enters committed census and eligible complete-sample denominator. |
| ownership | Mutates one preallocated attempt Cell and flags, retains no input row. |
| failure | noexcept with numeric protocol status; no query rollback. |
| cost | Constant checks/scalar stores. |
| Design | [docs/statistics.md](../../../../statistics.md), [include/crown/runtime/workload_statistics.hpp](../../../../../include/crown/runtime/workload_statistics.hpp), [src/runtime/statistics_collection.hpp](../../../../../src/runtime/statistics_collection.hpp) |

## B0020

[Lines 124–128](../../../../../src/runtime/statistics_collection.cpp#L124); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Ticket Collector::begin(std::size_t physical, bool changed) noexcept {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Combine standalone physical admission and known fact staging. |
| inputs / outputs | admit(root), then physical_fact(changed) only for nonempty ticket. |
| invariants | Uses same ordinal/clear/protocol mechanism, not another attempt or fact. |
| ownership | Returns scalar Ticket; no new owner. |
| failure | noexcept numeric protocol handling. |
| cost | Root O(D) admission clear plus constant fact work. |
| Design | [docs/statistics.md](../../../../statistics.md), [include/crown/runtime/workload_statistics.hpp](../../../../../include/crown/runtime/workload_statistics.hpp), [src/runtime/statistics_collection.hpp](../../../../../src/runtime/statistics_collection.hpp) |

## B0021

[Lines 129–137](../../../../../src/runtime/statistics_collection.cpp#L129); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Ticket Collector::nest(Ticket t) noexcept {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Nest a linear capability ticket under the current root attempt. |
| inputs / outputs | Exact current serial/depth with room increments serial/depth, returns child ticket carrying parent serial. |
| invariants | Only LIFO matching closes are valid. Invalid ticket/depth/serial exhaustion poisons pending attempt and returns empty. |
| ownership | Fixed scalar capability, no dynamic stack or row owner. |
| failure | noexcept protocol_error rather than query throw. |
| cost | Constant counters/checks. |
| Design | [docs/statistics.md](../../../../statistics.md), [include/crown/runtime/workload_statistics.hpp](../../../../../include/crown/runtime/workload_statistics.hpp), [src/runtime/statistics_collection.hpp](../../../../../src/runtime/statistics_collection.hpp) |

## B0022

[Lines 138–167](../../../../../src/runtime/statistics_collection.cpp#L138); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
bool Collector::finish(Ticket t, bool commit) noexcept {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Commit or discard numeric observations only when the exact outer ticket completes. |
| inputs / outputs | Matching ticket optionally poisons on abort, restores parent serial,returns for nested depth; root requires one fact, merges all root census plus only selected/untruncated detail, updates complete-input denominator/metadata and clears scratch. |
| invariants | Any nested abort poisons whole root attempt; root facts survive detail truncation but no partial detail is merged. Selected noops count complete. Mismatched ticket cannot publish. |
| ownership | Existing numeric slabs/flags only; no query-state commit or undo authority. |
| failure | noexcept numeric protocol handling. False means instrumentation failed/aborted, not permission to alter native commit. |
| cost | Nested constant; root O(D*fixed Cell size) eligibility scan/merges+scratch clear, even when unsampled; no allocations/clocks. |
| Design | [docs/statistics.md](../../../../statistics.md), [include/crown/runtime/workload_statistics.hpp](../../../../../include/crown/runtime/workload_statistics.hpp), [src/runtime/statistics_collection.hpp](../../../../../src/runtime/statistics_collection.hpp) |

```text
if (selected_ && !truncated_) attempt_[physical_].complete_detail_inputs=1;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Publish the exact eligible detailed-input denominator independently of all committed census facts. |
| inputs / outputs | Selected,untruncated outer committed attempt adds one complete_detail_input including noop; detailed cells merge only for that complete sample. |
| invariants | Aborted/truncated sample detail never biases a denominator by partially merging. All root inputs still merge independently when semantic commit succeeds. |
| ownership | Preallocated numeric slabs only. |
| failure | noexcept; counter saturation remains explicit and disqualifies exact ratio consumers. |
| cost | One root field plus existing O(D) merge loop,not a new scan. |
| Design | [docs/statistics.md](../../../../statistics.md), [include/crown/runtime/workload_statistics.hpp](../../../../../include/crown/runtime/workload_statistics.hpp), [src/runtime/statistics_collection.hpp](../../../../../src/runtime/statistics_collection.hpp) |

## B0023

[Lines 168–184](../../../../../src/runtime/statistics_collection.cpp#L168); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Cell* Collector::detail(std::size_t i, Kind kind) noexcept {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Admit one bounded detail hook without throwing into maintenance. |
| inputs / outputs | Enabled mode increments guard count,requires pending matching kind/root table/op/scope,then sampling/nonpoison/notruncation/noop/detail-budget checks return Cell* or null. |
| invariants | Invalid hook truncates/marks protocol; complete physical census remains independent. Hook budget consumed before support checks equal before/after, so admitted no-change hook can cost work without event count. |
| ownership | Pointer borrows current attempt Cell for immediate synchronous update; cannot escape next reset/finish/configure. |
| failure | noexcept; no pending marks protocol, invalid descriptor/noop/detail exhaustion disables detail rather than rejecting query. |
| cost | Constant checks/counters, no scan/allocation/clock. |
| Design | [docs/statistics.md](../../../../statistics.md), [include/crown/runtime/workload_statistics.hpp](../../../../../include/crown/runtime/workload_statistics.hpp), [src/runtime/statistics_collection.hpp](../../../../../src/runtime/statistics_collection.hpp) |

## B0024

[Lines 185–189](../../../../../src/runtime/statistics_collection.cpp#L185); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void Collector::occurrence(std::size_t i, bool accepted) noexcept {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Count one visited/accepted-or-rejected adapter occurrence. |
| inputs / outputs | detail(kind occurrence) gates increment of visited and accepted/rejected. |
| invariants | Observed actual hook multiset retains rejection; no row/value contents captured. |
| ownership | Fixed attempt Cell only. |
| failure | noexcept; detail availability and saturation flags preserve loss. |
| cost | Constant hook gate and2saturating increments. |
| Design | [docs/statistics.md](../../../../statistics.md), [include/crown/runtime/workload_statistics.hpp](../../../../../include/crown/runtime/workload_statistics.hpp), [src/runtime/statistics_collection.hpp](../../../../../src/runtime/statistics_collection.hpp) |

## B0025

[Lines 190–198](../../../../../src/runtime/statistics_collection.cpp#L190); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void Collector::support(std::size_t i, U64 before, U64 after) noexcept {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Observe an actual support-count change and zero crossings. |
| inputs / outputs | Admitted support Cell ignores before==after after hook admission; otherwise increments changes,crossings and observes after value. |
| invariants | Numeric count changes differ from presence crossings; a nonzero-to-nonzero change is still observed. Histograms are event after-values. |
| ownership | Retains scalar counts only, no support tuple. |
| failure | noexcept saturating counters; query arithmetic/state unchanged. |
| cost | Constant detail gate,counters and fixed histogram update. |
| Design | [docs/statistics.md](../../../../statistics.md), [include/crown/runtime/workload_statistics.hpp](../../../../../include/crown/runtime/workload_statistics.hpp), [src/runtime/statistics_collection.hpp](../../../../../src/runtime/statistics_collection.hpp) |

## B0026

[Lines 199–201](../../../../../src/runtime/statistics_collection.cpp#L199); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void Collector::degree(std::size_t i, U64 value) noexcept {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Observe one actual child-event bucket degree/probe size. |
| inputs / outputs | Admitted degree Cell observes U64 size,including0 and repeated events. |
| invariants | Event-multiset population is not uniform distinct keys or static average degree. |
| ownership | Only numeric histogram/counters. |
| failure | noexcept, detail loss/saturation explicit. |
| cost | Constant hook/Cell observation; actual bucket search/scan is caller work. |
| Design | [docs/statistics.md](../../../../statistics.md), [include/crown/runtime/workload_statistics.hpp](../../../../../include/crown/runtime/workload_statistics.hpp), [src/runtime/statistics_collection.hpp](../../../../../src/runtime/statistics_collection.hpp) |

## B0027

[Lines 202–209](../../../../../src/runtime/statistics_collection.cpp#L202); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
bool Collector::reset() noexcept {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Reset numeric interval/history only at a quiescent barrier. |
| inputs / outputs | Pending returns false; otherwise clears metadata and3slabs,sampling/detail/history/configuration state,then increments sticky reset generation. |
| invariants | Configuration descriptor capacities remain; reset does not reset monotone serial capability counter or query state. Cleared-cell metadata records reset work rather than all counters being literally zero. |
| ownership | Existing slabs only, no capacity growth. |
| failure | noexcept; pending refusal leaves state unchanged. |
| cost | O(3D*CellSize) clearing plus fixed flags, no allocation. |
| Design | [docs/statistics.md](../../../../statistics.md), [include/crown/runtime/workload_statistics.hpp](../../../../../include/crown/runtime/workload_statistics.hpp), [src/runtime/statistics_collection.hpp](../../../../../src/runtime/statistics_collection.hpp) |

## B0028

[Lines 210–219](../../../../../src/runtime/statistics_collection.cpp#L210); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
bool Collector::rotate(U64 configuration, bool force) noexcept {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Retain one prior semantic-mode interval using funded slab swap. |
| inputs / outputs | Quiescent enabled changed/forced configuration saves old metadata,swaps committed-&gt;previous,clears new committed/attempt,updates history/config labels and resets sampling ordinal. |
| invariants | Only one previous segment; replaced_history marks older history loss. Off/equal-unforced returns without rotation. Caller invokes after successful semantic switch; saturation label may force a boundary. |
| ownership | Swaps existing numeric buffers, retains no runtime rows/new payload. |
| failure | noexcept; pending false leaves state unchanged, no allocation. |
| cost | O(D*CellSize) clearing+constant swaps/metadata, no clocks. |
| Design | [docs/statistics.md](../../../../statistics.md), [include/crown/runtime/workload_statistics.hpp](../../../../../include/crown/runtime/workload_statistics.hpp), [src/runtime/statistics_collection.hpp](../../../../../src/runtime/statistics_collection.hpp) |

## B0029

[Lines 220–227](../../../../../src/runtime/statistics_collection.cpp#L220); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Memory Collector::memory() const noexcept {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Report collector component payload capacities. |
| inputs / outputs | Returns sizeof Collector,descriptor and3slab capacity*sizeof values plus their retained_payload sum. |
| invariants | Capacity arithmetic was prevalidated in configure. Excludes account framing/controls,producer routing external bytes and detached snapshot allocations; State adds its own routes separately. |
| ownership | Fixed scalar Memory report, no buffer view. |
| failure | noexcept no allocation/row access. |
| cost | Constant capacity arithmetic. |
| Design | [docs/statistics.md](../../../../statistics.md), [include/crown/runtime/workload_statistics.hpp](../../../../../include/crown/runtime/workload_statistics.hpp), [src/runtime/statistics_collection.hpp](../../../../../src/runtime/statistics_collection.hpp) |

## B0030

[Lines 228–228](../../../../../src/runtime/statistics_collection.cpp#L228); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L228-L228:sha256:a4c1a5daa522ee499a01316a62dcf6453c13535b8b9a8ad341534f4c3044c745
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Close the \`namespace crown::runtime::statistics_collection\` scope at this exact source boundary. |
| inputs / outputs | This token introduces no callable inputs or outputs. Declarations inside \`namespace crown::runtime::statistics_collection\` define the available names, members and operations. |
| invariants | The closing brace matches the opening \`namespace crown::runtime::statistics_collection\` at its lexical source position in src/runtime/statistics_collection.cpp; it preserves C++ namespace/type nesting. |
| ownership | The closing delimiter creates no owner. Types closed by \`namespace crown::runtime::statistics_collection\` retain the lifetimes and allocator rules of their own fields and operations. |
| failure | No failure path executes at this closing delimiter. Failure and cleanup behavior belong to enclosed functions and owning types. |
| cost | The delimiter itself performs no runtime work; the enclosed initializers, methods and destructors carry their own costs. |
| Design | [docs/statistics.md](../../../../statistics.md), [docs/memory_reports.md](../../../../memory_reports.md), [docs/query_memory.md](../../../../query_memory.md), [docs/code_specs/subsystem_contracts.md](../../../subsystem_contracts.md) |
