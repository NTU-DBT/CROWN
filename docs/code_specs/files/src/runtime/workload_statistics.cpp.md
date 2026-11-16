# `src/runtime/workload_statistics.cpp` — block usage map

[Source](../../../../../src/runtime/workload_statistics.cpp) · [Source index](../../../README.md) · [Subsystem contracts](../../../subsystem_contracts.md) · [Reviewed primitives](../../../primitives.md)

Capture bounded distributions, workload counters, owner memory and explain observations without mislabeling partial information as exact.

Snapshot SHA-256: `71eaa55ea250da06d07cedea2468c109a827f4bf25228768b684b2206cb35a89`. 288 lines partitioned into 48 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [statistics](../../../subsystem_contracts.md#statistics). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/statistics.md](../../../../statistics.md), [docs/observability.md](../../../../observability.md), [docs/memory_reports.md](../../../../memory_reports.md), [docs/ranking_evaluation.md](../../../../ranking_evaluation.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–9](../../../../../src/runtime/workload_statistics.cpp#L1) | Imports dependencies; declares namespace scope; declares callable signatures; declares values/defaults or compile-time conditions. |  · [reviewed contract](#b0001) |
| [B0002 · 10–13](../../../../../src/runtime/workload_statistics.cpp#L10) | Callable definition: std::size_t plus(std::size_t a,std::size_t b) | calls std::length_error; returns a+b · [reviewed contract](#b0002) |
| [B0003 · 14–17](../../../../../src/runtime/workload_statistics.cpp#L14) | Callable definition: std::size_t times(std::size_t a,std::size_t b) | calls std::length_error; returns a*b · [reviewed contract](#b0003) |
| [B0004 · 18–20](../../../../../src/runtime/workload_statistics.cpp#L18) | Callable definition: void increment(U64& value,bool& saturated) noexcept | calls  · [reviewed contract](#b0004) |
| [B0005 · 21–21](../../../../../src/runtime/workload_statistics.cpp#L21) | Callable definition: std::size_t operation(SetOperation op) noexcept | calls ; returns op==SetOperation::erase?1:0 · [reviewed contract](#b0005) |
| [B0006 · 22–22](../../../../../src/runtime/workload_statistics.cpp#L22) | Callable definition: bool degraded(const Metadata& m) noexcept | calls ; returns m.invalid_descriptor \|\| m.protocol_error \|\| m.ordinal_exhausted · [reviewed contract](#b0006) |
| [B0007 · 23–25](../../../../../src/runtime/workload_statistics.cpp#L23) | Callable definition: Availability fraction_status(Availability status) noexcept | calls ; returns status==Availability::lower_bound?Availability::unavailable:status · [reviewed contract](#b0007) |
| [B0008 · 26–26](../../../../../src/runtime/workload_statistics.cpp#L26) | Closes surrounding scope/type. |  · [reviewed contract](#b0008) |
| [B0009 · 27–44](../../../../../src/runtime/workload_statistics.cpp#L27) | Type/record definition: struct Snapshot::Data | source comment (unverified): // Detached numeric copies plus owning plan metadata; never runtime rows or · [reviewed contract](#b0009) |
| [B0010 · 45–45](../../../../../src/runtime/workload_statistics.cpp#L45) | Callable definition: const CompiledProgram& Snapshot::plan() const noexcept | calls ; returns data_-&gt;plan · [reviewed contract](#b0010) |
| [B0011 · 46–46](../../../../../src/runtime/workload_statistics.cpp#L46) | Callable definition: const Stamp& Snapshot::stamp() const noexcept | calls ; returns data_-&gt;stamp · [reviewed contract](#b0011) |
| [B0012 · 47–47](../../../../../src/runtime/workload_statistics.cpp#L47) | Callable definition: const Options& Snapshot::options() const noexcept | calls ; returns data_-&gt;options · [reviewed contract](#b0012) |
| [B0013 · 48–48](../../../../../src/runtime/workload_statistics.cpp#L48) | Callable definition: const ModeFacts& Snapshot::modes() const noexcept | calls ; returns data_-&gt;modes · [reviewed contract](#b0013) |
| [B0014 · 49–49](../../../../../src/runtime/workload_statistics.cpp#L49) | Callable definition: const ModeFacts& Snapshot::previous_modes() const noexcept | calls ; returns data_-&gt;previous_modes · [reviewed contract](#b0014) |
| [B0015 · 50–50](../../../../../src/runtime/workload_statistics.cpp#L50) | Callable definition: std::span&lt;const Descriptor&gt; Snapshot::descriptors() const noexcept | calls ; returns data_-&gt;descriptors · [reviewed contract](#b0015) |
| [B0016 · 51–51](../../../../../src/runtime/workload_statistics.cpp#L51) | Callable definition: std::span&lt;const Cell&gt; Snapshot::cells() const noexcept | calls ; returns data_-&gt;cells · [reviewed contract](#b0016) |
| [B0017 · 52–52](../../../../../src/runtime/workload_statistics.cpp#L52) | Callable definition: std::span&lt;const Cell&gt; Snapshot::previous_cells() const noexcept | calls ; returns data_-&gt;previous · [reviewed contract](#b0017) |
| [B0018 · 53–53](../../../../../src/runtime/workload_statistics.cpp#L53) | Callable definition: const Metadata& Snapshot::metadata() const noexcept | calls ; returns data_-&gt;metadata · [reviewed contract](#b0018) |
| [B0019 · 54–54](../../../../../src/runtime/workload_statistics.cpp#L54) | Callable definition: const Metadata& Snapshot::previous_metadata() const noexcept | calls ; returns data_-&gt;previous_metadata · [reviewed contract](#b0019) |
| [B0020 · 55–55](../../../../../src/runtime/workload_statistics.cpp#L55) | Callable definition: const Memory& Snapshot::memory() const noexcept | calls ; returns data_-&gt;memory · [reviewed contract](#b0020) |
| [B0021 · 56–56](../../../../../src/runtime/workload_statistics.cpp#L56) | Callable definition: bool Snapshot::pending() const noexcept | calls ; returns data_-&gt;pending · [reviewed contract](#b0021) |
| [B0022 · 57–57](../../../../../src/runtime/workload_statistics.cpp#L57) | Callable definition: bool Snapshot::has_previous() const noexcept | calls ; returns data_-&gt;has_previous · [reviewed contract](#b0022) |
| [B0023 · 58–58](../../../../../src/runtime/workload_statistics.cpp#L58) | Callable definition: bool Snapshot::replaced_history() const noexcept | calls ; returns data_-&gt;replaced · [reviewed contract](#b0023) |
| [B0024 · 59–59](../../../../../src/runtime/workload_statistics.cpp#L59) | Callable definition: U64 Snapshot::previous_interval_start_epoch() const noexcept | calls ; returns data_-&gt;previous_start · [reviewed contract](#b0024) |
| [B0025 · 60–60](../../../../../src/runtime/workload_statistics.cpp#L60) | Callable definition: U64 Snapshot::previous_interval_end_epoch() const noexcept | calls ; returns data_-&gt;previous_end · [reviewed contract](#b0025) |
| [B0026 · 61–66](../../../../../src/runtime/workload_statistics.cpp#L61) | Callable definition: Snapshot Snapshot::with_pending() const | calls account, Snapshot, std::move; returns Snapshot(std::move(copy)); growth make_accounted_shared; source comment (unverified): // This marker requires a deep copy of the report arrays on the same account; · [reviewed contract](#b0026) |
| [B0027 · 67–73](../../../../../src/runtime/workload_statistics.cpp#L67) | Callable definition: Availability Snapshot::detail_availability() const noexcept | calls options, metadata, cells, degraded; returns Availability::disabled; Availability::lower_bound; 1 loop sites · [reviewed contract](#b0027) |
| [B0028 · 74–84](../../../../../src/runtime/workload_statistics.cpp#L74) | Callable definition: Fraction Snapshot::input_share(std::size_t id) const noexcept | calls options, descriptors, size, cells; returns {0,0,Availability::disabled}; {}; 1 loop sites · [reviewed contract](#b0028) |
| [B0029 · 85–104](../../../../../src/runtime/workload_statistics.cpp#L85) | Callable definition: Fraction Snapshot::events_per_physical_input(std::size_t id) const noexcept | calls options, descriptors, size, cells; returns {0,0,Availability::disabled}; {}; 1 loop sites · [reviewed contract](#b0029) |
| [B0030 · 105–113](../../../../../src/runtime/workload_statistics.cpp#L105) | Callable definition: Fraction Snapshot::crossing_fraction(std::size_t id) const noexcept | calls options, descriptors, size, cells; returns {0,0,Availability::disabled}; {} · [reviewed contract](#b0030) |
| [B0031 · 114–120](../../../../../src/runtime/workload_statistics.cpp#L114) | Callable definition: Fraction Snapshot::adapter_selectivity(std::size_t id) const noexcept | calls options, descriptors, size, cells; returns {0,0,Availability::disabled}; {} · [reviewed contract](#b0031) |
| [B0032 · 121–121](../../../../../src/runtime/workload_statistics.cpp#L121) | Explanatory comments or spacing. |  |
| [B0033 · 122–208](../../../../../src/runtime/workload_statistics.cpp#L122) | Callable definition: template&lt;class Plan&gt; void detail::State::configure(const Plan& plan,bool physical,const Options& options,U64 sequence) | calls std::invalid_argument, inputs, size, nodes; growth insert, push_back, reserve; 10 loop sites; source comment (unverified): // Every route position has a validated dense native ID; allocation is confined · [reviewed contract](#b0033) |
| [B0034 · 209–212](../../../../../src/runtime/workload_statistics.cpp#L209) | Callable definition: void detail::State::reset(U64 sequence) noexcept | calls reset · [reviewed contract](#b0034) |
| [B0035 · 213–216](../../../../../src/runtime/workload_statistics.cpp#L213) | Callable definition: std::size_t detail::State::route(std::size_t local) const noexcept | calls size; returns absent; routes_\[active_group_*stride_+local\] · [reviewed contract](#b0035) |
| [B0036 · 217–223](../../../../../src/runtime/workload_statistics.cpp#L217) | Callable definition: detail::Ticket detail::State::enter(std::size_t group) noexcept | calls options, pending, nest, current_ticket; returns {}; collector_.nest(collector_.current_ticket()); source comment (unverified): // Nested admission is constant work; a root admit clears the full attempt · [reviewed contract](#b0036) |
| [B0037 · 224–227](../../../../../src/runtime/workload_statistics.cpp#L224) | Callable definition: detail::Ticket detail::State::physical(TableId table,SetOperation op) noexcept | calls enter, operation; returns enter(maximum); enter(table.value*2+operation(op)) · [reviewed contract](#b0037) |
| [B0038 · 228–228](../../../../../src/runtime/workload_statistics.cpp#L228) | Callable definition: detail::Ticket detail::State::logical(SetOperation op) noexcept | calls enter, operation; returns enter(operation(op)) · [reviewed contract](#b0038) |
| [B0039 · 229–231](../../../../../src/runtime/workload_statistics.cpp#L229) | Callable definition: void detail::State::physical_fact(bool changed) noexcept | calls pending, physical_fact · [reviewed contract](#b0039) |
| [B0040 · 232–234](../../../../../src/runtime/workload_statistics.cpp#L232) | Callable definition: void detail::State::logical_fact(Ticket ticket,bool changed) noexcept | calls logical_fact · [reviewed contract](#b0040) |
| [B0041 · 235–239](../../../../../src/runtime/workload_statistics.cpp#L235) | Callable definition: void detail::State::finish(Ticket ticket,bool commit) noexcept | calls finish; source comment (unverified): // Root completion merges eligible cells and clears the full scratch slab. · [reviewed contract](#b0041) |
| [B0042 · 240–243](../../../../../src/runtime/workload_statistics.cpp#L240) | Callable definition: void detail::State::occurrence(OccurrenceId occurrence,bool accepted) noexcept | calls options, occurrence, route · [reviewed contract](#b0042) |
| [B0043 · 244–247](../../../../../src/runtime/workload_statistics.cpp#L244) | Callable definition: void detail::State::derivation(OccurrenceId occurrence,U64 before,U64 after) noexcept | calls options, support, route · [reviewed contract](#b0043) |
| [B0044 · 248–253](../../../../../src/runtime/workload_statistics.cpp#L248) | Callable definition: void detail::State::support(NodeId node,SupportRole role,U64 before,U64 after) noexcept | calls options, support, route · [reviewed contract](#b0044) |
| [B0045 · 254–257](../../../../../src/runtime/workload_statistics.cpp#L254) | Callable definition: void detail::State::touched(std::size_t edge,bool appeared,U64 degree) noexcept | calls options, degree, route · [reviewed contract](#b0045) |
| [B0046 · 258–266](../../../../../src/runtime/workload_statistics.cpp#L258) | Callable definition: void detail::State::modes(ModeFacts next,U64 sequence,bool initial) noexcept | calls increment, rotate; source comment (unverified): // A saturated numeric segment label must not suppress a real boundary. · [reviewed contract](#b0046) |
| [B0047 · 267–285](../../../../../src/runtime/workload_statistics.cpp#L267) | Callable definition: Snapshot detail::State::snapshot(const CompiledProgram& plan,SupportOwnerId owner,U64 sequence,bool pending) const | calls account, generation, generation_saturated, options; returns Snapshot(std::move(data)); growth make_accounted_shared; source comment (unverified): // Explicit allocating capture of committed current/previous numbers. No · [reviewed contract](#b0047) |
| [B0048 · 286–288](../../../../../src/runtime/workload_statistics.cpp#L286) | declares callable signatures; declares values/defaults or compile-time conditions. | source comment (unverified): // namespace crown::runtime::workload · [reviewed contract](#b0048) |

## B0001

[Lines 1–9](../../../../../src/runtime/workload_statistics.cpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
#include "workload_statistics_detail.hpp"
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Assemble numeric workload snapshot/routing support and host-size arithmetic bound. |
| inputs / outputs | Private State/Collector, accounted shared ownership and standard arithmetic/exception helpers are included; maximum is size_t max. |
| invariants | C01 collection is local instrumentation. Paper support recurrence does not establish allocator, sampling or report lifetime guarantees. |
| ownership | Declarations retain no account, query row or runtime pointer. |
| failure | Includes/constants perform no dynamic admission or recovery. |
| cost | No dynamic runtime cost for these declarations. |
| Design | [docs/statistics.md](../../../../statistics.md), [include/crown/runtime/workload_statistics.hpp](../../../../../include/crown/runtime/workload_statistics.hpp), [docs/code_review.md](../../../../code_review.md) |

## B0002

[Lines 10–13](../../../../../src/runtime/workload_statistics.cpp#L10); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::size_t plus(std::size_t a,std::size_t b) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Add descriptor/routing sizes before cold allocation. |
| inputs / outputs | Two size_t counts return exact a+b if representable. |
| invariants | Overflow is rejected before computing/publishing wrapped descriptor sizes. |
| ownership | Inline scalar arithmetic only. |
| failure | Throws length_error("statistics descriptor arithmetic") on overflow; callers prepare privately. |
| cost | Constant comparison and addition. |
| Design | [docs/statistics.md](../../../../statistics.md), [include/crown/runtime/workload_statistics.hpp](../../../../../include/crown/runtime/workload_statistics.hpp) |

## B0003

[Lines 14–17](../../../../../src/runtime/workload_statistics.cpp#L14); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::size_t times(std::size_t a,std::size_t b) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Multiply dense route/cell capacity dimensions safely. |
| inputs / outputs | Two size_t values return a*b, allowing a zero multiplier. |
| invariants | All cold route/allocation dimensions must fit host size before allocation. |
| ownership | Inline operands/result only. |
| failure | Throws length_error("statistics route arithmetic") before overflowing product. |
| cost | Constant zero test, division-bound check and multiply. |
| Design | [docs/statistics.md](../../../../statistics.md), [include/crown/runtime/workload_statistics.hpp](../../../../../include/crown/runtime/workload_statistics.hpp) |

## B0004

[Lines 18–20](../../../../../src/runtime/workload_statistics.cpp#L18); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void increment(U64& value,bool& saturated) noexcept {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Saturate a generation/segment counter without losing the saturation fact. |
| inputs / outputs | Mutable U64 counter and sticky bool either increment the counter or set saturated at UINT64_MAX. |
| invariants | Never wraps. A saturated label cannot certify an exact interval identity. |
| ownership | Mutates two caller-owned scalar fields, retains nothing. |
| failure | noexcept; no allocation or error presentation. |
| cost | Constant branch/scalar write. |
| Design | [docs/statistics.md](../../../../statistics.md), [include/crown/runtime/workload_statistics.hpp](../../../../../include/crown/runtime/workload_statistics.hpp) |

## B0005

[Lines 21–21](../../../../../src/runtime/workload_statistics.cpp#L21); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::size_t operation(SetOperation op) noexcept { return op==SetOperation::erase?1:0; }
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Map an admitted set operation to the dense insert/erase group offset. |
| inputs / outputs | SetOperation returns one for erase, zero otherwise. |
| invariants | Private callers supply an admitted operation; this helper is not invalid-enum validation. |
| ownership | Inline enum/result only. |
| failure | noexcept with no allocation or diagnostic path. |
| cost | One equality test. |
| Design | [docs/statistics.md](../../../../statistics.md), [include/crown/runtime/workload_statistics.hpp](../../../../../include/crown/runtime/workload_statistics.hpp) |

## B0006

[Lines 22–22](../../../../../src/runtime/workload_statistics.cpp#L22); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
bool degraded(const Metadata& m) noexcept { return m.invalid_descriptor || m.protocol_error || m.ordinal_exhausted; }
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Detect metadata that makes complete workload interpretation unsafe. |
| inputs / outputs | Metadata returns invalid_descriptor \|\| protocol_error \|\| ordinal_exhausted. |
| invariants | Saturation and truncation are checked separately by each availability accessor. |
| ownership | Borrows Metadata for the call. |
| failure | noexcept and allocation-free. |
| cost | Three Boolean reads/tests. |
| Design | [docs/statistics.md](../../../../statistics.md), [include/crown/runtime/workload_statistics.hpp](../../../../../include/crown/runtime/workload_statistics.hpp) |

## B0007

[Lines 23–25](../../../../../src/runtime/workload_statistics.cpp#L23); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Availability fraction_status(Availability status) noexcept {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Prevent a ratio of saturated lower-bound counters from looking numerically meaningful. |
| inputs / outputs | Availability lower_bound maps to unavailable; every other status passes through. |
| invariants | Raw capped counters remain inspectable, but a ratio of lower bounds is not a valid estimate. |
| ownership | Inline enum only. |
| failure | noexcept with no allocation. |
| cost | Constant comparison/select. |
| Design | [docs/statistics.md](../../../../statistics.md), [include/crown/runtime/workload_statistics.hpp](../../../../../include/crown/runtime/workload_statistics.hpp) |

## B0008

[Lines 26–26](../../../../../src/runtime/workload_statistics.cpp#L26); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L26-L26:sha256:412ca345ccf75bf9c0806bce695be8de808b79984251a7a54d202cf6101dd451
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Close the \`anonymous namespace in src/runtime/workload_statistics.cpp\` scope at this exact source boundary. |
| inputs / outputs | This token introduces no callable inputs or outputs. Declarations inside \`anonymous namespace in src/runtime/workload_statistics.cpp\` define the available names, members and operations. |
| invariants | The closing brace matches the opening \`anonymous namespace in src/runtime/workload_statistics.cpp\` at its lexical source position in src/runtime/workload_statistics.cpp; it preserves C++ namespace/type nesting. |
| ownership | The closing delimiter creates no owner. Types closed by \`anonymous namespace in src/runtime/workload_statistics.cpp\` retain the lifetimes and allocator rules of their own fields and operations. |
| failure | No failure path executes at this closing delimiter. Failure and cleanup behavior belong to enclosed functions and owning types. |
| cost | The delimiter itself performs no runtime work; the enclosed initializers, methods and destructors carry their own costs. |
| Design | [docs/statistics.md](../../../../statistics.md), [docs/memory_reports.md](../../../../memory_reports.md), [docs/query_memory.md](../../../../query_memory.md), [docs/code_specs/subsystem_contracts.md](../../../subsystem_contracts.md) |

## B0009

[Lines 27–44](../../../../../src/runtime/workload_statistics.cpp#L27); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct Snapshot::Data {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Own an immutable copied workload report and its owning compiled metadata. |
| inputs / outputs | Data stores CompiledProgram, stamps/options/modes, descriptor/current/previous numeric vectors, metadata/memory summaries and lifecycle flags; constructor sets plan/account allocators. |
| invariants | No native rows, mutable runtime pointers or storage pins are retained. Vectors use plan.account with capture/1 attribution. |
| ownership | Shares immutable plan and owns account-funded copies of report arrays; public Snapshot exposes const views. |
| failure | Snapshot factories construct privately; allocation/copy failure releases partial vectors and preserves the collector. |
| cost | Fixed metadata plus O(descriptor_count + current_cell_count + previous_cell_count) report payload; Cell includes its fixed 65-bin histogram. |
| Design | [docs/statistics.md](../../../../statistics.md), [include/crown/runtime/workload_statistics.hpp](../../../../../include/crown/runtime/workload_statistics.hpp), [src/runtime/workload_statistics_detail.hpp](../../../../../src/runtime/workload_statistics_detail.hpp), [docs/query_memory.md](../../../../query_memory.md) |

## B0010

[Lines 45–45](../../../../../src/runtime/workload_statistics.cpp#L45); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
const CompiledProgram& Snapshot::plan() const noexcept { return data_->plan; }
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Read Snapshot compiled program. |
| inputs / outputs | A readable factory-produced Snapshot returns its copied compiled program as const CompiledProgram reference. |
| invariants | Shares immutable source/layout metadata; does not expose the mutable runtime. |
| ownership | Borrows immutable Data; retain a Snapshot sharing that Data for the whole returned reference/span lifetime. Copy-like moves keep Snapshot handles readable. |
| failure | noexcept; no allocation, clock, validation, counter update or runtime access. |
| cost | Constant member access; no array copy or scan. |
| Design | [docs/statistics.md](../../../../statistics.md), [include/crown/runtime/workload_statistics.hpp](../../../../../include/crown/runtime/workload_statistics.hpp) |

## B0011

[Lines 46–46](../../../../../src/runtime/workload_statistics.cpp#L46); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
const Stamp& Snapshot::stamp() const noexcept { return data_->stamp; }
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Read Snapshot capture stamp. |
| inputs / outputs | A readable factory-produced Snapshot returns its copied capture stamp as const Stamp reference. |
| invariants | Includes owner, committed epoch and interval/configuration/reset/segment identities and saturation flags. |
| ownership | Borrows immutable Data; retain a Snapshot sharing that Data for the whole returned reference/span lifetime. Copy-like moves keep Snapshot handles readable. |
| failure | noexcept; no allocation, clock, validation, counter update or runtime access. |
| cost | Constant member access; no array copy or scan. |
| Design | [docs/statistics.md](../../../../statistics.md), [include/crown/runtime/workload_statistics.hpp](../../../../../include/crown/runtime/workload_statistics.hpp) |

## B0012

[Lines 47–47](../../../../../src/runtime/workload_statistics.cpp#L47); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
const Options& Snapshot::options() const noexcept { return data_->options; }
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Read Snapshot collector options. |
| inputs / outputs | A readable factory-produced Snapshot returns its copied collector options as const Options reference. |
| invariants | Describes mode, sampling period/offset, cell limit and detail budget at capture. |
| ownership | Borrows immutable Data; retain a Snapshot sharing that Data for the whole returned reference/span lifetime. Copy-like moves keep Snapshot handles readable. |
| failure | noexcept; no allocation, clock, validation, counter update or runtime access. |
| cost | Constant member access; no array copy or scan. |
| Design | [docs/statistics.md](../../../../statistics.md), [include/crown/runtime/workload_statistics.hpp](../../../../../include/crown/runtime/workload_statistics.hpp) |

## B0013

[Lines 48–48](../../../../../src/runtime/workload_statistics.cpp#L48); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
const ModeFacts& Snapshot::modes() const noexcept { return data_->modes; }
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Read Snapshot current output/mode facts. |
| inputs / outputs | A readable factory-produced Snapshot returns its copied current output/mode facts as const ModeFacts reference. |
| invariants | Facts identify the captured segment, not later owner configuration. |
| ownership | Borrows immutable Data; retain a Snapshot sharing that Data for the whole returned reference/span lifetime. Copy-like moves keep Snapshot handles readable. |
| failure | noexcept; no allocation, clock, validation, counter update or runtime access. |
| cost | Constant member access; no array copy or scan. |
| Design | [docs/statistics.md](../../../../statistics.md), [include/crown/runtime/workload_statistics.hpp](../../../../../include/crown/runtime/workload_statistics.hpp) |

## B0014

[Lines 49–49](../../../../../src/runtime/workload_statistics.cpp#L49); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
const ModeFacts& Snapshot::previous_modes() const noexcept { return data_->previous_modes; }
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Read Snapshot previous segment mode facts. |
| inputs / outputs | A readable factory-produced Snapshot returns its copied previous segment mode facts as const ModeFacts reference. |
| invariants | Consult has_previous before interpreting previous segment data. |
| ownership | Borrows immutable Data; retain a Snapshot sharing that Data for the whole returned reference/span lifetime. Copy-like moves keep Snapshot handles readable. |
| failure | noexcept; no allocation, clock, validation, counter update or runtime access. |
| cost | Constant member access; no array copy or scan. |
| Design | [docs/statistics.md](../../../../statistics.md), [include/crown/runtime/workload_statistics.hpp](../../../../../include/crown/runtime/workload_statistics.hpp) |

## B0015

[Lines 50–50](../../../../../src/runtime/workload_statistics.cpp#L50); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::span<const Descriptor> Snapshot::descriptors() const noexcept { return data_->descriptors; }
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Read Snapshot descriptor definitions. |
| inputs / outputs | A readable factory-produced Snapshot returns its copied descriptor definitions as const span. |
| invariants | Descriptor positions index current and previous numeric cells. |
| ownership | Borrows immutable Data; retain a Snapshot sharing that Data for the whole returned reference/span lifetime. Copy-like moves keep Snapshot handles readable. |
| failure | noexcept; no allocation, clock, validation, counter update or runtime access. |
| cost | Constant member access; no array copy or scan. |
| Design | [docs/statistics.md](../../../../statistics.md), [include/crown/runtime/workload_statistics.hpp](../../../../../include/crown/runtime/workload_statistics.hpp) |

## B0016

[Lines 51–51](../../../../../src/runtime/workload_statistics.cpp#L51); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::span<const Cell> Snapshot::cells() const noexcept { return data_->cells; }
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Read Snapshot committed current cells. |
| inputs / outputs | A readable factory-produced Snapshot returns its copied committed current cells as const span. |
| invariants | Attempt-private cells are never exported here; pending is marked separately. |
| ownership | Borrows immutable Data; retain a Snapshot sharing that Data for the whole returned reference/span lifetime. Copy-like moves keep Snapshot handles readable. |
| failure | noexcept; no allocation, clock, validation, counter update or runtime access. |
| cost | Constant member access; no array copy or scan. |
| Design | [docs/statistics.md](../../../../statistics.md), [include/crown/runtime/workload_statistics.hpp](../../../../../include/crown/runtime/workload_statistics.hpp) |

## B0017

[Lines 52–52](../../../../../src/runtime/workload_statistics.cpp#L52); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::span<const Cell> Snapshot::previous_cells() const noexcept { return data_->previous; }
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Read Snapshot previous segment cells. |
| inputs / outputs | A readable factory-produced Snapshot returns its copied previous segment cells as const span. |
| invariants | Previous history is at most one segment; has_previous/replaced_history explain availability/loss. |
| ownership | Borrows immutable Data; retain a Snapshot sharing that Data for the whole returned reference/span lifetime. Copy-like moves keep Snapshot handles readable. |
| failure | noexcept; no allocation, clock, validation, counter update or runtime access. |
| cost | Constant member access; no array copy or scan. |
| Design | [docs/statistics.md](../../../../statistics.md), [include/crown/runtime/workload_statistics.hpp](../../../../../include/crown/runtime/workload_statistics.hpp) |

## B0018

[Lines 53–53](../../../../../src/runtime/workload_statistics.cpp#L53); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
const Metadata& Snapshot::metadata() const noexcept { return data_->metadata; }
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Read Snapshot current metadata. |
| inputs / outputs | A readable factory-produced Snapshot returns its copied current metadata as const Metadata reference. |
| invariants | Attempt/commit/abort/truncation/protocol counters remain raw numeric observations. |
| ownership | Borrows immutable Data; retain a Snapshot sharing that Data for the whole returned reference/span lifetime. Copy-like moves keep Snapshot handles readable. |
| failure | noexcept; no allocation, clock, validation, counter update or runtime access. |
| cost | Constant member access; no array copy or scan. |
| Design | [docs/statistics.md](../../../../statistics.md), [include/crown/runtime/workload_statistics.hpp](../../../../../include/crown/runtime/workload_statistics.hpp) |

## B0019

[Lines 54–54](../../../../../src/runtime/workload_statistics.cpp#L54); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
const Metadata& Snapshot::previous_metadata() const noexcept { return data_->previous_metadata; }
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Read Snapshot previous segment metadata. |
| inputs / outputs | A readable factory-produced Snapshot returns its copied previous segment metadata as const Metadata reference. |
| invariants | Consult has_previous; metadata is copied as-of capture. |
| ownership | Borrows immutable Data; retain a Snapshot sharing that Data for the whole returned reference/span lifetime. Copy-like moves keep Snapshot handles readable. |
| failure | noexcept; no allocation, clock, validation, counter update or runtime access. |
| cost | Constant member access; no array copy or scan. |
| Design | [docs/statistics.md](../../../../statistics.md), [include/crown/runtime/workload_statistics.hpp](../../../../../include/crown/runtime/workload_statistics.hpp) |

## B0020

[Lines 55–55](../../../../../src/runtime/workload_statistics.cpp#L55); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
const Memory& Snapshot::memory() const noexcept { return data_->memory; }
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Read Snapshot component memory capacities. |
| inputs / outputs | A readable factory-produced Snapshot returns its copied component memory capacities as const Memory reference. |
| invariants | Reports collector/route/slab payload summaries, not this snapshot allocation, total account peak or process RSS. |
| ownership | Borrows immutable Data; retain a Snapshot sharing that Data for the whole returned reference/span lifetime. Copy-like moves keep Snapshot handles readable. |
| failure | noexcept; no allocation, clock, validation, counter update or runtime access. |
| cost | Constant member access; no array copy or scan. |
| Design | [docs/statistics.md](../../../../statistics.md), [include/crown/runtime/workload_statistics.hpp](../../../../../include/crown/runtime/workload_statistics.hpp) |

## B0021

[Lines 56–56](../../../../../src/runtime/workload_statistics.cpp#L56); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
bool Snapshot::pending() const noexcept { return data_->pending; }
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Read Snapshot pending marker. |
| inputs / outputs | A readable factory-produced Snapshot returns its copied pending marker as bool value. |
| invariants | True means the owner or collector had private work; committed cell copies remain committed. |
| ownership | Returns inline scalar copy; Snapshot retains the immutable Data. |
| failure | noexcept; no allocation, clock, validation, counter update or runtime access. |
| cost | Constant member access; no array copy or scan. |
| Design | [docs/statistics.md](../../../../statistics.md), [include/crown/runtime/workload_statistics.hpp](../../../../../include/crown/runtime/workload_statistics.hpp) |

## B0022

[Lines 57–57](../../../../../src/runtime/workload_statistics.cpp#L57); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
bool Snapshot::has_previous() const noexcept { return data_->has_previous; }
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Read Snapshot previous-history marker. |
| inputs / outputs | A readable factory-produced Snapshot returns its copied previous-history marker as bool value. |
| invariants | True identifies one retained previous mode interval. |
| ownership | Returns inline scalar copy; Snapshot retains the immutable Data. |
| failure | noexcept; no allocation, clock, validation, counter update or runtime access. |
| cost | Constant member access; no array copy or scan. |
| Design | [docs/statistics.md](../../../../statistics.md), [include/crown/runtime/workload_statistics.hpp](../../../../../include/crown/runtime/workload_statistics.hpp) |

## B0023

[Lines 58–58](../../../../../src/runtime/workload_statistics.cpp#L58); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
bool Snapshot::replaced_history() const noexcept { return data_->replaced; }
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Read Snapshot older-history replacement marker. |
| inputs / outputs | A readable factory-produced Snapshot returns its copied older-history replacement marker as bool value. |
| invariants | Indicates a newer rotation replaced a previously retained history segment. |
| ownership | Returns inline scalar copy; Snapshot retains the immutable Data. |
| failure | noexcept; no allocation, clock, validation, counter update or runtime access. |
| cost | Constant member access; no array copy or scan. |
| Design | [docs/statistics.md](../../../../statistics.md), [include/crown/runtime/workload_statistics.hpp](../../../../../include/crown/runtime/workload_statistics.hpp) |

## B0024

[Lines 59–59](../../../../../src/runtime/workload_statistics.cpp#L59); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
U64 Snapshot::previous_interval_start_epoch() const noexcept { return data_->previous_start; }
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Read Snapshot previous interval start epoch. |
| inputs / outputs | A readable factory-produced Snapshot returns its copied previous interval start epoch as U64 value. |
| invariants | Meaningful with has_previous and the captured previous mode facts. |
| ownership | Returns inline scalar copy; Snapshot retains the immutable Data. |
| failure | noexcept; no allocation, clock, validation, counter update or runtime access. |
| cost | Constant member access; no array copy or scan. |
| Design | [docs/statistics.md](../../../../statistics.md), [include/crown/runtime/workload_statistics.hpp](../../../../../include/crown/runtime/workload_statistics.hpp) |

## B0025

[Lines 60–60](../../../../../src/runtime/workload_statistics.cpp#L60); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
U64 Snapshot::previous_interval_end_epoch() const noexcept { return data_->previous_end; }
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Read Snapshot previous interval end epoch. |
| inputs / outputs | A readable factory-produced Snapshot returns its copied previous interval end epoch as U64 value. |
| invariants | Meaningful with has_previous; this is an epoch marker, not elapsed wall-clock time. |
| ownership | Returns inline scalar copy; Snapshot retains the immutable Data. |
| failure | noexcept; no allocation, clock, validation, counter update or runtime access. |
| cost | Constant member access; no array copy or scan. |
| Design | [docs/statistics.md](../../../../statistics.md), [include/crown/runtime/workload_statistics.hpp](../../../../../include/crown/runtime/workload_statistics.hpp) |

## B0026

[Lines 61–66](../../../../../src/runtime/workload_statistics.cpp#L61); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Snapshot Snapshot::with_pending() const {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Add the session-private-work marker to a detached snapshot copy. |
| inputs / outputs | Readable Snapshot produces a new owning Snapshot with otherwise copied Data and pending=true. |
| invariants | Original snapshot and collector remain unchanged; this does not export session-private numeric attempts. |
| ownership | Deep-copies descriptor/current/previous vectors using copied plan-account allocators and shares immutable plan metadata. No runtime pointer is retained. |
| failure | Account/upstream allocation or vector copy can throw; RAII drops the private copy and preserves the original. |
| cost | One accounted shared holder plus up to three vector copies: O(D + current_cells + previous_cells), not a handle-only operation. |
| Design | [docs/statistics.md](../../../../statistics.md), [include/crown/runtime/workload_statistics.hpp](../../../../../include/crown/runtime/workload_statistics.hpp), [src/runtime/session.cpp](../../../../../src/runtime/session.cpp), [docs/query_memory.md](../../../../query_memory.md) |

## B0027

[Lines 67–73](../../../../../src/runtime/workload_statistics.cpp#L67); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Availability Snapshot::detail_availability() const noexcept {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Classify captured detail completeness without manufacturing an exact census. |
| inputs / outputs | Snapshot options/metadata/cells return disabled, lower_bound, incomplete, exact (period1) or sampled. |
| invariants | Metadata or cell saturation takes precedence over truncation/protocol degradation. Pending and stamp-saturation checks are separate responsibilities of feature/freshness consumers. |
| ownership | Reads immutable report only; no owner callbacks. |
| failure | noexcept; no allocation or mutation. |
| cost | O(cell_count) scan until first saturated cell; otherwise fixed metadata/option reads. |
| Design | [docs/statistics.md](../../../../statistics.md), [include/crown/runtime/workload_statistics.hpp](../../../../../include/crown/runtime/workload_statistics.hpp) |

## B0028

[Lines 74–84](../../../../../src/runtime/workload_statistics.cpp#L74); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Fraction Snapshot::input_share(std::size_t id) const noexcept {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Compute a physical root stratum share among all committed physical inputs. |
| inputs / outputs | Physical descriptor index produces numerator=cells\[id\].inputs and denominator=sum inputs across every physical descriptor. |
| invariants | Disabled mode reports disabled; invalid/nonphysical index returns unavailable. Zero/overflow/cell saturation makes ratio unavailable; degraded metadata makes an otherwise valid share incomplete. |
| ownership | Borrows immutable parallel descriptor/cell arrays; returns only inline Fraction fields. |
| failure | noexcept and saturating local sum avoids wrap; no diagnostic exception. |
| cost | O(descriptor_count) scan, no heap or query-row access. |
| Design | [docs/statistics.md](../../../../statistics.md), [include/crown/runtime/workload_statistics.hpp](../../../../../include/crown/runtime/workload_statistics.hpp) |

## B0029

[Lines 85–104](../../../../../src/runtime/workload_statistics.cpp#L85); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Fraction Snapshot::events_per_physical_input(std::size_t id) const noexcept {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Report events per initiating physical input with the correct census/sample denominator. |
| inputs / outputs | Physical-scoped descriptor index selects visited/support-change/degree-count/input numerator and matching physical table/op root denominator. |
| invariants | Physical roots use all committed stratum inputs; detail uses complete_detail_inputs including selected no-ops. Logical scopes reject; empty/capped denominators yield unavailable; detailed availability is preserved without random-sample/confidence claims. |
| ownership | Reads snapshot numeric copies; returned Fraction owns scalar counts/status/scope only. |
| failure | noexcept; invalid/missing binding returns unavailable rather than throwing. |
| cost | O(D) root search plus O(D) detail-availability scan for nonphysical descriptors; no allocations. |
| Design | [docs/statistics.md](../../../../statistics.md), [include/crown/runtime/workload_statistics.hpp](../../../../../include/crown/runtime/workload_statistics.hpp) |

## B0030

[Lines 105–113](../../../../../src/runtime/workload_statistics.cpp#L105); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Fraction Snapshot::crossing_fraction(std::size_t id) const noexcept {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Report observed zero crossings as a fraction of support-count changes. |
| inputs / outputs | Support descriptor returns (zero_to_positive + positive_to_zero) / changes with observed_support_count_changes scope. |
| invariants | Invalid kinds reject; zero denominator, cell saturation or local numerator overflow makes the fraction unavailable. This is an observed-event fraction, not a future probability. |
| ownership | Inline Fraction copied from immutable report. |
| failure | noexcept; local saturation avoids overflowing numerator. |
| cost | Fixed arithmetic plus up to O(D) detail-availability scan; no heap. |
| Design | [docs/statistics.md](../../../../statistics.md), [include/crown/runtime/workload_statistics.hpp](../../../../../include/crown/runtime/workload_statistics.hpp) |

## B0031

[Lines 114–120](../../../../../src/runtime/workload_statistics.cpp#L114); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Fraction Snapshot::adapter_selectivity(std::size_t id) const noexcept {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Report accepted adapter visits divided by all observed visits. |
| inputs / outputs | Occurrence descriptor returns accepted/visited with observed_visited_routes scope. |
| invariants | Invalid kind, zero visits or capped counts yield unavailable. Detailed sample/incomplete status is retained; no population selectivity guarantee follows. |
| ownership | Borrows immutable numeric report; returns inline Fraction. |
| failure | noexcept and allocation-free. |
| cost | Fixed reads plus up to O(D) detail-availability scan. |
| Design | [docs/statistics.md](../../../../statistics.md), [include/crown/runtime/workload_statistics.hpp](../../../../../include/crown/runtime/workload_statistics.hpp) |

## B0033

[Lines 122–208](../../../../../src/runtime/workload_statistics.cpp#L122); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
template<class Plan> void detail::State::configure(const Plan& plan,bool physical,const Options& options,U64 sequence) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Prepare and atomically install complete dense workload descriptor/routing strata at a quiescent barrier. |
| inputs / outputs | Immutable admitted PhysicalPlan/CompiledProgram, physical/logical owner flag, Options and current sequence configure State and Collector. |
| invariants | Valid dense native IDs/routes are required. Enabled mode covers every physical table/op or both logical ops, support nodes, signed edges and physical occurrences. max_cells rejects incomplete strata; host-size arithmetic/capacities are checked before publication. Off retains no descriptor/route/slab payload. |
| ownership | Privately prepares account-funded scratch descriptors/routes; Collector prepares its own three slabs and descriptor copy. After its successful configure, same-allocator route swap and scalar updates publish. Old/new arrays overlap transiently on the original account. |
| failure | Invalid options/topology, length overflow, pending Collector, cap or allocation failure propagates before live State routing publication; Collector has its own strong guarantee. No local catch is required. |
| cost | Explicit cold allocation: topology/route scans, O(groups*(nodes+edges)+inputs) descriptors and O(groups*stride) dense routes; std::count over each native alias bucket and delegated O(D^2) descriptor duplicate/root validation. Temporary and old capacities overlap. No native row/binding-hash scan. |
| Design | [docs/statistics.md](../../../../statistics.md), [include/crown/runtime/workload_statistics.hpp](../../../../../include/crown/runtime/workload_statistics.hpp), [src/runtime/statistics_collection.cpp](../../../../../src/runtime/statistics_collection.cpp), [src/runtime/workload_statistics_detail.hpp](../../../../../src/runtime/workload_statistics_detail.hpp), [tests/unit/workload_statistics_exception_test.cpp](../../../../../tests/unit/workload_statistics_exception_test.cpp) |

```text
const auto per_group=plus(plus(1,times(nn,2)),plus(visible_count,times(ne,2)));
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Admit all enabled workload strata and capacity arithmetic before allocation. |
| inputs / outputs | Counts roots, two support roles/node, visible nodes and two edge signs per initiating group, plus physical occurrence/derivation slots. |
| invariants | Rejects a cell cap too small for complete strata; does not truncate descriptor definitions or inspect runtime rows. |
| ownership | Private descriptor/route vectors use the original collector account. |
| failure | length_error/checked-size failures precede reserve/assign and live publication. |
| cost | Fixed arithmetic after topology validation; subsequent capacities scale with groups, nodes, edges and aliases. |
| Design | [docs/statistics.md](../../../../statistics.md), [include/crown/runtime/workload_statistics.hpp](../../../../../include/crown/runtime/workload_statistics.hpp) |

```text
const auto append=[&](std::size_t local,Kind kind,Role role,std::optional<NodeId> node={},
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Bind a dense local event route to its immutable descriptor definition. |
| inputs / outputs | During configure group loop, writes routes\[group*stride+local\] and appends table/op/scope/role/node/alias/edge/sign metadata. |
| invariants | Topology/required counts are validated; each route is compiled once at a cold barrier and later hooks perform direct index access. |
| ownership | Lambda is synchronous/private; arrays are funded/reserved before construction. |
| failure | Any unexpected append failure leaves candidate arrays private; Collector/State stay unchanged until publish. |
| cost | Constant append per descriptor; total O(D) construction, dense unused route positions retain absent sentinels. |
| Design | [docs/statistics.md](../../../../statistics.md), [include/crown/runtime/workload_statistics.hpp](../../../../../include/crown/runtime/workload_statistics.hpp) |

```text
collector_.configure(options,descriptors,plus(sizeof(State)-sizeof(statistics_collection::Collector),
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Publish collector slabs before the nonthrowing State route/metadata handoff. |
| inputs / outputs | Delegated Collector.configure validates descriptors, allocates candidate descriptor/current/attempt/previous arrays, then swaps; State follows with same-allocator route swap and scalar updates. |
| invariants | No throwing preparation remains after successful Collector publication. Existing same-account capacities and new candidates overlap during setup. |
| ownership | Both old and candidate arrays have scoped owners; after swap locals destroy the old route payload. |
| failure | Collector failure preserves prior configuration; no duplicate local catch/undo is required. |
| cost | Delegated O(D^2) descriptor validation plus O(D) slab setup and old-state destruction; no query-row copy. |
| Design | [docs/statistics.md](../../../../statistics.md), [include/crown/runtime/workload_statistics.hpp](../../../../../include/crown/runtime/workload_statistics.hpp), [src/runtime/statistics_collection.cpp](../../../../../src/runtime/statistics_collection.cpp) |

## B0034

[Lines 209–212](../../../../../src/runtime/workload_statistics.cpp#L209); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void detail::State::reset(U64 sequence) noexcept {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Reset numeric workload history only when the collector is quiescent. |
| inputs / outputs | Current sequence asks Collector.reset; on success resets interval/previous/segment metadata, otherwise leaves State metadata alone. |
| invariants | Reset is not an update rollback; committed query rows and configured route descriptors remain unchanged. Pending collector refuses reset. |
| ownership | Mutates existing preallocated collector slabs and State scalar history; retains route capacity. |
| failure | noexcept; false Collector reset returns immediately with no State metadata changes. |
| cost | Delegated O(D) zeroing of current/attempt/previous slabs plus fixed scalar writes; no allocations or clocks. |
| Design | [docs/statistics.md](../../../../statistics.md), [include/crown/runtime/workload_statistics.hpp](../../../../../include/crown/runtime/workload_statistics.hpp), [src/runtime/statistics_collection.cpp](../../../../../src/runtime/statistics_collection.cpp) |

## B0035

[Lines 213–216](../../../../../src/runtime/workload_statistics.cpp#L213); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::size_t detail::State::route(std::size_t local) const noexcept {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Translate a validated local hook position into the current stratum descriptor. |
| inputs / outputs | Local offset and active_group return routes\[active_group*stride+local\] or absent for out-of-bounds/unconfigured state. |
| invariants | Offsets are compiled from dense plan IDs. Missing routes reach Collector validation rather than arbitrary memory access. |
| ownership | Borrows preallocated routes_; returns an inline index. |
| failure | noexcept with checked stride/local/group boundaries, no diagnostic allocation. |
| cost | Constant arithmetic/bounds checks/array lookup. |
| Design | [docs/statistics.md](../../../../statistics.md), [include/crown/runtime/workload_statistics.hpp](../../../../../include/crown/runtime/workload_statistics.hpp) |

## B0036

[Lines 217–223](../../../../../src/runtime/workload_statistics.cpp#L217); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
detail::Ticket detail::State::enter(std::size_t group) noexcept {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Admit one root attempt or nest inside its currently active workload ticket. |
| inputs / outputs | Dense group offset returns empty when off, nested current ticket when pending, otherwise binds active_group and admits its root descriptor. |
| invariants | Nested logical/native stages preserve the initiating outer physical stratum. Collector owns ordinal, depth, poisoning and attempt lifecycle. |
| ownership | Mutates only State active_group and preallocated Collector state; returned Ticket is a scalar capability. |
| failure | noexcept; Collector records invalid descriptor/protocol/ordinal exhaustion numerically instead of throwing into query work. |
| cost | Off/nested paths are constant; root admit clears the entire attempt slab O(D), even for unsampled attempts. No allocation/clock in the collection path. |
| Design | [docs/statistics.md](../../../../statistics.md), [include/crown/runtime/workload_statistics.hpp](../../../../../include/crown/runtime/workload_statistics.hpp), [src/runtime/statistics_collection.cpp](../../../../../src/runtime/statistics_collection.cpp) |

## B0037

[Lines 224–227](../../../../../src/runtime/workload_statistics.cpp#L224); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
detail::Ticket detail::State::physical(TableId table,SetOperation op) noexcept {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Choose an initiating physical table/operation workload stratum safely. |
| inputs / outputs | TableId and admitted set operation map to table*2+op then enter; impossible host-size table product uses an invalid sentinel group. |
| invariants | Collector validates the resulting root rather than allowing multiplication overflow. This instrumentation does not validate/query-mutate the SQL source itself. |
| ownership | Returns a scalar Ticket and uses existing State/Collector storage. |
| failure | noexcept; oversized group becomes recorded invalid-descriptor/protocol state in the collector. |
| cost | Constant mapping plus enter cost: O(D) root scratch clear, or constant nested/off path. |
| Design | [docs/statistics.md](../../../../statistics.md), [include/crown/runtime/workload_statistics.hpp](../../../../../include/crown/runtime/workload_statistics.hpp), [src/runtime/statistics_collection.cpp](../../../../../src/runtime/statistics_collection.cpp) |

## B0038

[Lines 228–228](../../../../../src/runtime/workload_statistics.cpp#L228); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
detail::Ticket detail::State::logical(SetOperation op) noexcept { return enter(operation(op)); }
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Enter the logical insertion/deletion workload stratum. |
| inputs / outputs | Admitted SetOperation forwards its dense operation offset to enter. |
| invariants | When nested under a physical owner, enter preserves the physical initiating group; standalone support uses logical_epoch scope. |
| ownership | No retained row or new allocation; returns scalar Ticket. |
| failure | noexcept; Collector owns protocol/degradation handling. |
| cost | Constant forwarding plus enter root/nesting cost. |
| Design | [docs/statistics.md](../../../../statistics.md), [include/crown/runtime/workload_statistics.hpp](../../../../../include/crown/runtime/workload_statistics.hpp) |

## B0039

[Lines 229–231](../../../../../src/runtime/workload_statistics.cpp#L229); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void detail::State::physical_fact(bool changed) noexcept {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Record the independently known physical changed/no-op fact inside an admitted attempt. |
| inputs / outputs | Boolean changed reaches Collector.physical_fact only while a collector attempt is pending. |
| invariants | One admitted physical root must receive the fact once. Collector detects wrong root, duplicate fact or protocol misuse; detailed sampling does not replace this census fact. |
| ownership | Mutates one preallocated attempt root Cell/metadata; retains no tuple. |
| failure | noexcept; protocol problems are marked, not thrown. |
| cost | Constant checks/scalar writes; no scan, allocation or clock. |
| Design | [docs/statistics.md](../../../../statistics.md), [include/crown/runtime/workload_statistics.hpp](../../../../../include/crown/runtime/workload_statistics.hpp), [src/runtime/statistics_collection.cpp](../../../../../src/runtime/statistics_collection.cpp) |

## B0040

[Lines 232–234](../../../../../src/runtime/workload_statistics.cpp#L232); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void detail::State::logical_fact(Ticket ticket,bool changed) noexcept {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Record a logical changed/no-op fact only for the outer standalone logical owner. |
| inputs / outputs | Valid root Ticket (serial!=0, depth1), changed and physical_owner_ decide whether Collector.logical_fact is called. |
| invariants | Nested logical stages under physical owners must not double-count input census. Root fact belongs to its initiating scope. |
| ownership | Uses preallocated collector fields; stores no Ticket beyond the call. |
| failure | noexcept; Collector records protocol misuse without changing query exception behavior. |
| cost | Constant root/owner tests and at most one fixed root-cell update. |
| Design | [docs/statistics.md](../../../../statistics.md), [include/crown/runtime/workload_statistics.hpp](../../../../../include/crown/runtime/workload_statistics.hpp) |

## B0041

[Lines 235–239](../../../../../src/runtime/workload_statistics.cpp#L235); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void detail::State::finish(Ticket ticket,bool commit) noexcept {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Close one workload ticket with query commit or abort outcome. |
| inputs / outputs | Nonempty Ticket and commit flag forward to Collector.finish; this State wrapper discards its Boolean validity result. |
| invariants | Caller must finish exact tickets in LIFO order. Nested abort poisons outer attempt; only successful outer completion merges census/complete detail. Instrumentation does not grant semantic query commit authority. |
| ownership | Mutates only preallocated attempt/current cells and metadata; no row ownership or query undo. |
| failure | noexcept; protocol errors are recorded by Collector. No exception handler/retry is introduced. |
| cost | Nested finish is constant; root completion scans/merges eligible cells and clears full scratch O(D), including unsampled paths. No allocation or clock. |
| Design | [docs/statistics.md](../../../../statistics.md), [include/crown/runtime/workload_statistics.hpp](../../../../../include/crown/runtime/workload_statistics.hpp), [src/runtime/statistics_collection.cpp](../../../../../src/runtime/statistics_collection.cpp) |

## B0042

[Lines 240–243](../../../../../src/runtime/workload_statistics.cpp#L240); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void detail::State::occurrence(OccurrenceId occurrence,bool accepted) noexcept {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Record an adapter occurrence visit and acceptance in the active stratum. |
| inputs / outputs | Dense admitted OccurrenceId and accepted flag resolve occurrence_offset_+id then call Collector.occurrence when enabled. |
| invariants | Caller IDs come from the validated plan. Collector checks kind/stratum/pending status, sampling and detail budget; count measures actual visits including rejects. |
| ownership | No tuple contents retained; writes fixed numeric attempt Cell. |
| failure | noexcept; invalid detail/limit truncates or marks report status instead of throwing. |
| cost | Off returns immediately; enabled route and scalar counter work are constant per event, no allocation/clock. |
| Design | [docs/statistics.md](../../../../statistics.md), [include/crown/runtime/workload_statistics.hpp](../../../../../include/crown/runtime/workload_statistics.hpp) |

## B0043

[Lines 244–247](../../../../../src/runtime/workload_statistics.cpp#L244); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void detail::State::derivation(OccurrenceId occurrence,U64 before,U64 after) noexcept {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Record an occurrence derivation-count replacement as detailed numeric work. |
| inputs / outputs | Dense OccurrenceId plus before/after counts route to derivation support Cell when enabled. |
| invariants | Collector records only actual before!=after changes, crossings and after-value histogram; detail budget is still consumed according to Collector protocol. |
| ownership | Copies numeric counts only into preallocated attempt metrics; no derivation row is retained. |
| failure | noexcept with numeric degradation/truncation, not query rejection. |
| cost | Constant route/hook plus fixed-width histogram/counter work; no heap or clock. |
| Design | [docs/statistics.md](../../../../statistics.md), [include/crown/runtime/workload_statistics.hpp](../../../../../include/crown/runtime/workload_statistics.hpp), [src/runtime/statistics_collection.cpp](../../../../../src/runtime/statistics_collection.cpp) |

## B0044

[Lines 248–253](../../../../../src/runtime/workload_statistics.cpp#L248); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void detail::State::support(NodeId node,SupportRole role,U64 before,U64 after) noexcept {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Record survivor, parent-support or visible-support count replacement. |
| inputs / outputs | Dense NodeId, admitted SupportRole and before/after choose the corresponding compiled offset and Collector.support Cell. |
| invariants | Private caller supplies one of the supported roles; fallback routes other values as visible_support rather than validating an enum. Collector validates actual descriptor presence/kind/stratum. |
| ownership | Retains only numeric observations in preallocated cells. |
| failure | noexcept; missing/invalid route marks incomplete detail, without changing query result/state. |
| cost | Constant role dispatch/lookup plus fixed-width support/histogram accounting. |
| Design | [docs/statistics.md](../../../../statistics.md), [include/crown/runtime/workload_statistics.hpp](../../../../../include/crown/runtime/workload_statistics.hpp) |

## B0045

[Lines 254–257](../../../../../src/runtime/workload_statistics.cpp#L254); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void detail::State::touched(std::size_t edge,bool appeared,U64 degree) noexcept {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Record one signed child-edge event and its actually touched/probed degree. |
| inputs / outputs | Dense edge index, appeared sign and U64 degree choose edge_offset+2*edge+sign then call Collector.degree. |
| invariants | One hook is one event; repeated touches remain repeated, and zero degree is a real sample. It is not a static distribution over distinct keys. |
| ownership | Only numeric degree/histogram fields are retained; no bucket, key, cursor or pin. |
| failure | noexcept; invalid detail/budget/saturation is recorded numerically. |
| cost | Constant dense-route arithmetic and fixed 65-bin bit-width update; no bucket scan/allocation/clock here. Caller separately pays for the actual bucket operation. |
| Design | [docs/statistics.md](../../../../statistics.md), [include/crown/runtime/workload_statistics.hpp](../../../../../include/crown/runtime/workload_statistics.hpp), [src/runtime/statistics_collection.cpp](../../../../../src/runtime/statistics_collection.cpp) |

## B0046

[Lines 258–266](../../../../../src/runtime/workload_statistics.cpp#L258); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void detail::State::modes(ModeFacts next,U64 sequence,bool initial) noexcept {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Start a new numeric mode segment after a successful semantic mode switch. |
| inputs / outputs | Next ModeFacts, current sequence and optional initial flag bind initial facts or retain previous facts/epoch interval and force Collector rotation on change. |
| invariants | Call only at a quiescent successful mode barrier; initialization and equal facts do not rotate. Saturated segment labels still force a real boundary. Only one previous segment is retained. |
| ownership | Swaps/clears existing collector slabs and copies State facts; no query rows or new payload. |
| failure | noexcept; private caller must ensure Collector is not pending, because rotate failure is intentionally ignored after State updates. |
| cost | Initial/equal path constant; changed enabled mode clears current/attempt slabs O(D) and swaps prior storage without allocation or clocks. |
| Design | [docs/statistics.md](../../../../statistics.md), [include/crown/runtime/workload_statistics.hpp](../../../../../include/crown/runtime/workload_statistics.hpp), [src/runtime/statistics_collection.cpp](../../../../../src/runtime/statistics_collection.cpp), [src/runtime/delta.cpp](../../../../../src/runtime/delta.cpp), [tests/unit/workload_statistics_test.cpp](../../../../../tests/unit/workload_statistics_test.cpp) |

## B0047

[Lines 267–285](../../../../../src/runtime/workload_statistics.cpp#L267); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Snapshot detail::State::snapshot(const CompiledProgram& plan,SupportOwnerId owner,U64 sequence,bool pending) const {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Detach committed workload numbers and metadata from a runtime owner. |
| inputs / outputs | Owning CompiledProgram, owner ID, sequence and private-work flag produce immutable Snapshot with stamps, current/previous modes/cells, descriptors, metadata and payload memory summary. |
| invariants | Only committed slabs are copied. pending is caller-private OR Collector pending. Memory describes collector/route capacities; report holder/vector copies and shared plan storage are separate actual allocations. |
| ownership | One accounted shared Data and descriptor/current/previous vector copies use plan.account capture/1; shares plan metadata and never retains runtime rows/pointers/pins. |
| failure | Allocation/copy failure destroys only private Snapshot storage; live collector/current history remain unchanged. No local catch/rollback is needed. |
| cost | O(D + current_cells + previous_cells) copies and capacity-sized payload; snapshot capture is explicit allocating diagnostic work, distinct from fixed event hooks. |
| Design | [docs/statistics.md](../../../../statistics.md), [include/crown/runtime/workload_statistics.hpp](../../../../../include/crown/runtime/workload_statistics.hpp), [tests/unit/workload_statistics_exception_test.cpp](../../../../../tests/unit/workload_statistics_exception_test.cpp), [docs/query_memory.md](../../../../query_memory.md) |

## B0048

[Lines 286–288](../../../../../src/runtime/workload_statistics.cpp#L286); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
template void detail::State::configure<PhysicalPlan>(const PhysicalPlan&,bool,const Options&,U64);
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Instantiate the same validated dense-routing setup for both admitted plan handle forms. |
| inputs / outputs | Explicit template instantiations provide State::configure for PhysicalPlan and CompiledProgram. |
| invariants | Both use the single implementation and its same topology/options/admission rules; no fallback collector is added. |
| ownership | No per-instance object or account created by these declarations. |
| failure | Runtime failure semantics remain those of configure; this block adds no catch. |
| cost | Compile/link instantiation only; no additional per-call work. |
| Design | [docs/statistics.md](../../../../statistics.md), [include/crown/runtime/workload_statistics.hpp](../../../../../include/crown/runtime/workload_statistics.hpp) |
