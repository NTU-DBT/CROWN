# `src/runtime/selection.cpp` — block usage map

[Source](../../../../../src/runtime/selection.cpp) · [Source index](../../../README.md) · [Subsystem contracts](../../../subsystem_contracts.md) · [Reviewed primitives](../../../primitives.md)

Rank or select within a checked candidate family using exact binding, explicit evidence and bounded local score policies.

Snapshot SHA-256: `0d0ef11e19de93a9b75b34231e255be4e7b9bc7f3eb74a45b69dedab3a7963e7`. 226 lines partitioned into 29 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [ranking](../../../subsystem_contracts.md#ranking). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/ranking.md](../../../../ranking.md), [docs/selection.md](../../../../selection.md), [docs/selection_binding.md](../../../../selection_binding.md), [docs/ranking_accounting.md](../../../../ranking_accounting.md), [docs/selection_accounting.md](../../../../selection_accounting.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–10](../../../../../src/runtime/selection.cpp#L1) | Imports dependencies; declares namespace scope; declares values/defaults or compile-time conditions. | growth new · [reviewed contract](#b0001) |
| [B0002 · 11–11](../../../../../src/runtime/selection.cpp#L11) | Type/record definition: struct Data |  · [reviewed contract](#b0002) |
| [B0003 · 12–14](../../../../../src/runtime/selection.cpp#L12) | Type/record definition: struct Factory | returns CurrentSelection(std::move(data)) · [reviewed contract](#b0003) |
| [B0004 · 15–15](../../../../../src/runtime/selection.cpp#L15) | Closes surrounding scope/type. |  · [reviewed contract](#b0004) |
| [B0005 · 16–16](../../../../../src/runtime/selection.cpp#L16) | Callable definition: const ps::Selection& CurrentSelection::selection() const noexcept | calls ; returns data_-&gt;selection · [reviewed contract](#b0005) |
| [B0006 · 17–17](../../../../../src/runtime/selection.cpp#L17) | Callable definition: const ranking::RuntimeEvidence& CurrentSelection::capture() const noexcept | calls ; returns data_-&gt;capture · [reviewed contract](#b0006) |
| [B0007 · 18–18](../../../../../src/runtime/selection.cpp#L18) | Callable definition: std::optional&lt;std::uint64_t&gt; CurrentSelection::preparation_nanoseconds() const noexcept | calls ; returns data_-&gt;preparation_ns · [reviewed contract](#b0007) |
| [B0008 · 19–24](../../../../../src/runtime/selection.cpp#L19) | Callable definition: std::optional&lt;PatternGuarantee&gt; CurrentSelection::pattern_guarantee() const noexcept | calls session_context, pattern_guarantee, status, PatternGuarantee; returns {}; PatternGuarantee(data_) · [reviewed contract](#b0008) |
| [B0009 · 25–25](../../../../../src/runtime/selection.cpp#L25) | Callable definition: ps::PatternGuarantee PatternGuarantee::selected() const noexcept | calls pattern_guarantee; returns *data_-&gt;selection.pattern_guarantee() · [reviewed contract](#b0009) |
| [B0010 · 26–28](../../../../../src/runtime/selection.cpp#L26) | Callable definition: const UpdatePatternStatus& PatternGuarantee::enforcement() const & noexcept | calls session_context, status; returns *data_-&gt;capture.session_context()-&gt;status().update_patterns · [reviewed contract](#b0010) |
| [B0011 · 29–29](../../../../../src/runtime/selection.cpp#L29) | Callable definition: statistics::OwnerStamp PatternGuarantee::stamp() const noexcept | calls captured, state, stamp; returns data_-&gt;capture.captured()-&gt;state().stamp() · [reviewed contract](#b0011) |
| [B0012 · 30–33](../../../../../src/runtime/selection.cpp#L30) | Callable definition: bool PatternGuarantee::selected_plan_matches_capture() const noexcept | calls enforcement, plan, physical_sha256, std::string_view; returns data_-&gt;selection.plan().physical_sha256() == std::string_view(actual.data(), actual.size()) · [reviewed contract](#b0012) |
| [B0013 · 34–34](../../../../../src/runtime/selection.cpp#L34) | declares namespace scope. |  · [reviewed contract](#b0013) |
| [B0014 · 35–37](../../../../../src/runtime/selection.cpp#L35) | Callable definition: std::optional&lt;statistics::Freshness&gt; freshness(const PhysicalRuntime& owner, const statistics::OwnerCapture& captured) | calls statistics_freshness; returns owner.statistics_freshness(captured, 0) · [reviewed contract](#b0014) |
| [B0015 · 38–40](../../../../../src/runtime/selection.cpp#L38) | Callable definition: std::optional&lt;statistics::Freshness&gt; freshness(const DeltaRuntime& owner, const statistics::OwnerCapture& captured) | calls statistics_freshness; returns owner.statistics_freshness(captured, 0) · [reviewed contract](#b0015) |
| [B0016 · 41–43](../../../../../src/runtime/selection.cpp#L41) | Callable definition: std::optional&lt;statistics::Freshness&gt; freshness(const QuerySession& owner, const statistics::OwnerCapture& captured) | calls statistics_freshness; returns owner.statistics_freshness(captured, 0) · [reviewed contract](#b0016) |
| [B0017 · 44–55](../../../../../src/runtime/selection.cpp#L44) | Callable definition: pr::Reasons reason(std::optional&lt;statistics::Freshness&gt; value) | calls pr::reason; returns pr::reason(pr::Reason::released); 0 · [reviewed contract](#b0017) |
| [B0018 · 56–57](../../../../../src/runtime/selection.cpp#L56) | Explanatory comments or spacing. | source comment (unverified): // Caller retains exclusive synchronous owner access through capture and publication. · [reviewed contract](#b0018) |
| [B0019 · 58–102](../../../../../src/runtime/selection.cpp#L58) | Callable definition: template&lt;class Owner&gt; void boundary(const ranking::RuntimeEvidence& facts, const Owner& owner, sd::Budget& budget, const std::opt… | calls captured, pr::reason, state, workload; guard sd::require(profile.has_value() && !profile-&gt;violation,ps::Stop::boundary_unavailable);; 1 loop sites; source comment (unverified): // Caller retains exclusive synchronous owner access through capture and publication. · [reviewed contract](#b0019) |
| [B0020 · 103–104](../../../../../src/runtime/selection.cpp#L103) | Explanatory comments or spacing. | source comment (unverified): // Keep the public noexcept diagnostic mapper around the one prepublication · [reviewed contract](#b0020) |
| [B0021 · 105–179](../../../../../src/runtime/selection.cpp#L105) | Callable definition: template&lt;class Owner&gt; Attempt current(const planner::CandidateSnapshot& snapshot, const ps::Source& source, const Owner& owner, c… | calls Clock::now, constexpr, report_metadata, plan; guard sd::require(!request.update_patterns,ps::Stop::unsupported_model);; returns owner.report_metadata().plan(); owner.plan(); growth emplace, make_accounted_shared; source comment (unverified): // Keep the public noexcept diagnostic mapper around the one prepublication · [reviewed contract](#b0021) |
| [B0022 · 180–180](../../../../../src/runtime/selection.cpp#L180) | Closes surrounding scope/type. |  · [reviewed contract](#b0022) |
| [B0023 · 181–184](../../../../../src/runtime/selection.cpp#L181) | Callable definition: Attempt select_current(const planner::CandidateSnapshot& s, const ps::Source& source, const PhysicalRuntime& owner, const ps::Req… | calls current; returns current(s, source, owner, request, limits, cache, use) · [reviewed contract](#b0023) |
| [B0024 · 185–188](../../../../../src/runtime/selection.cpp#L185) | Callable definition: Attempt select_current(const planner::CandidateSnapshot& s, const ps::Source& source, const DeltaRuntime& owner, const ps::Reques… | calls current; returns current(s, source, owner, request, limits, cache, use) · [reviewed contract](#b0024) |
| [B0025 · 189–192](../../../../../src/runtime/selection.cpp#L189) | Callable definition: Attempt select_current(const planner::CandidateSnapshot& s, const ps::Source& source, const QuerySession& owner, const ps::Reques… | calls current; returns current(s, source, owner, request, limits, cache, use) · [reviewed contract](#b0025) |
| [B0026 · 193–196](../../../../../src/runtime/selection.cpp#L193) | Callable definition: Attempt select_for_reoptimization(const planner::CandidateSnapshot& snapshot,const ps::Source& source,const QuerySession& session… | calls current; returns current(snapshot,source,session,request,limits,cache,use,true) · [reviewed contract](#b0026) |
| [B0027 · 197–197](../../../../../src/runtime/selection.cpp#L197) | Explanatory comments or spacing. | source comment (unverified): // Historical choices require fresh owner/interval/producer binding and real timing. · [reviewed contract](#b0027) |
| [B0028 · 198–225](../../../../../src/runtime/selection.cpp#L198) | Callable definition: void begin_reoptimization(QuerySession& session,const CurrentSelection& choice,reoptimization::Options options) | calls Clock::now, preparation_nanoseconds, Error, selection; source comment (unverified): // Historical choices require fresh owner/interval/producer binding and real timing. · [reviewed contract](#b0028) |
| [B0029 · 226–226](../../../../../src/runtime/selection.cpp#L226) | Closes surrounding scope/type. | source comment (unverified): // namespace crown::runtime::selection · [reviewed contract](#b0029) |

## B0001

[Lines 1–10](../../../../../src/runtime/selection.cpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L1-L10:sha256:ebe9d71ce2177f54eafcc616800a62e51dac97ef6893aeff5df81e818e85a026
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Source usage for this declaration span in src/runtime/selection.cpp: imports \`"crown/runtime/selection.hpp"\`, \`"../planner/selection_detail.hpp"\`, \`"crown/api/error.hpp"\`, \`&lt;new&gt;\`, \`&lt;type_traits&gt;\` for compilation; creates namespace alias \`sd = ::crown::planner::selection::detail\`; creates namespace alias \`pr = ::crown::planner::ranking\`; opens namespace \`crown::runtime::selection\`; opens namespace \`detail\`. |
| inputs / outputs | Compile inputs are the listed headers and namespace/type names. This span adds no result value unless a helper/type definition listed above is instantiated or called. |
| invariants | The exact import, alias, namespace and member declarations determine the local compile/link surface; stronger behavior belongs to their constructors and operations. |
| ownership | Imports, namespace aliases, forward declarations and compile guards create no object owner. Runtime ownership starts with declared object instances and their allocator/member types. |
| failure | No explicit throw/catch appears in this exact span. Includes, constructors, inline members, static initialization and callees can still fail; follow their enclosing API contracts. |
| cost | The include directives affect compile dependencies. Any runtime initializer or cost in included definitions follows those definitions and is not inferred absent by this import block. |
| Design | [docs/selection.md](../../../../selection.md), [docs/selection_binding.md](../../../../selection_binding.md), [docs/selection_accounting.md](../../../../selection_accounting.md), [docs/reoptimization.md](../../../../reoptimization.md), [docs/code_specs/subsystem_contracts.md](../../../subsystem_contracts.md) |

## B0002

[Lines 11–11](../../../../../src/runtime/selection.cpp#L11); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct Data { ps::Selection selection;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Retain a checked pure selection together with its actual-owner capture and optional measured preparation cost. |
| inputs / outputs | selection owns the chosen checked candidate/plan/report graph; capture owns RuntimeEvidence/CombinedCapture/session context; preparation_ns is absent until a measured successful bridge fills it before returning. |
| invariants | No caller-editable numeric evidence can create this private wrapper. After return, a CurrentSelection is an immutable historical value, not a promise the runtime stays unchanged. |
| ownership | Shared Data/control uses original query account capture:13; members share their already funded immutable graphs. No live owner pointer is stored. |
| failure | Construction/account admission occurs before any cache statistic/eviction/insertion; failure publishes no CurrentSelection or cache action. |
| cost | One actual funded wrapper/control allocation plus shared handles. Referenced evidence/selection graphs already paid real capture/preparation costs; ordinary wrapper copies share rather than rescan. |
| Design | [src/runtime/selection.cpp](../../../../../src/runtime/selection.cpp), [include/crown/runtime/selection.hpp](../../../../../include/crown/runtime/selection.hpp), [src/planner/selection.cpp](../../../../../src/planner/selection.cpp), [src/planner/selection_detail.hpp](../../../../../src/planner/selection_detail.hpp), [src/runtime/ranking_evidence.cpp](../../../../../src/runtime/ranking_evidence.cpp), [src/runtime/reoptimization.cpp](../../../../../src/runtime/reoptimization.cpp), [docs/selection.md](../../../../selection.md), [docs/selection_accounting.md](../../../../selection_accounting.md), [docs/reoptimization.md](../../../../reoptimization.md), [tests/unit/selection_current_test.cpp](../../../../../tests/unit/selection_current_test.cpp), [tests/unit/selection_publication_fault_independent_test.cpp](../../../../../tests/unit/selection_publication_fault_independent_test.cpp), [tests/unit/reoptimization_selection_test.cpp](../../../../../tests/unit/reoptimization_selection_test.cpp), [docs/code_review.md](../../../../code_review.md) |

## B0003

[Lines 12–14](../../../../../src/runtime/selection.cpp#L12); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct Factory {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Privately adopt prepared shared selection data without another allocation. |
| inputs / outputs | Factory::make moves shared_ptr&lt;const Data&gt; into CurrentSelection using its friend constructor. |
| invariants | Only private checked producer code invokes this seam; it does not validate editable report DTOs or perform owner capture by itself. |
| ownership | Result shares immutable selection/evidence/account owners; no deep row/array clone. |
| failure | Declared noexcept; the actual wrapper allocation was admitted before this call. |
| cost | Fixed shared owner transfer with no source scan or new control block. |
| Design | [src/runtime/selection.cpp](../../../../../src/runtime/selection.cpp), [include/crown/runtime/selection.hpp](../../../../../include/crown/runtime/selection.hpp), [src/planner/selection.cpp](../../../../../src/planner/selection.cpp), [src/planner/selection_detail.hpp](../../../../../src/planner/selection_detail.hpp), [src/runtime/ranking_evidence.cpp](../../../../../src/runtime/ranking_evidence.cpp), [src/runtime/reoptimization.cpp](../../../../../src/runtime/reoptimization.cpp), [docs/selection.md](../../../../selection.md), [docs/selection_accounting.md](../../../../selection_accounting.md), [docs/reoptimization.md](../../../../reoptimization.md), [tests/unit/selection_current_test.cpp](../../../../../tests/unit/selection_current_test.cpp), [tests/unit/selection_publication_fault_independent_test.cpp](../../../../../tests/unit/selection_publication_fault_independent_test.cpp), [tests/unit/reoptimization_selection_test.cpp](../../../../../tests/unit/reoptimization_selection_test.cpp), [docs/code_review.md](../../../../code_review.md) |

## B0004

[Lines 15–15](../../../../../src/runtime/selection.cpp#L15); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L15-L15:sha256:412ca345ccf75bf9c0806bce695be8de808b79984251a7a54d202cf6101dd451
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Close the \`namespace detail\` scope at this exact source boundary. |
| inputs / outputs | This token introduces no callable inputs or outputs. Declarations inside \`namespace detail\` define the available names, members and operations. |
| invariants | The closing brace matches the opening \`namespace detail\` at its lexical source position in src/runtime/selection.cpp; it preserves C++ namespace/type nesting. |
| ownership | The closing delimiter creates no owner. Types closed by \`namespace detail\` retain the lifetimes and allocator rules of their own fields and operations. |
| failure | No failure path executes at this closing delimiter. Failure and cleanup behavior belong to enclosed functions and owning types. |
| cost | The delimiter itself performs no runtime work; the enclosed initializers, methods and destructors carry their own costs. |
| Design | [docs/selection.md](../../../../selection.md), [docs/selection_binding.md](../../../../selection_binding.md), [docs/selection_accounting.md](../../../../selection_accounting.md), [docs/reoptimization.md](../../../../reoptimization.md), [docs/code_specs/subsystem_contracts.md](../../../subsystem_contracts.md) |

## B0005

[Lines 16–16](../../../../../src/runtime/selection.cpp#L16); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
const ps::Selection& CurrentSelection::selection()
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Borrow the prepared pure choice and its checked plan/candidate facts. |
| inputs / outputs | Returns data_-&gt;selection by const reference. |
| invariants | Public CurrentSelection has private construction and copy-like shared-handle moves; this accessor does not recapture/revalidate freshness or mutate selection. |
| ownership | Reference borrows the retained Data graph; keep a CurrentSelection owner alive. |
| failure | Noexcept under valid factory-produced handle invariant; no fallback empty Data allocation. |
| cost | Fixed reference return, no key/array copy or row scan. |
| Design | [src/runtime/selection.cpp](../../../../../src/runtime/selection.cpp), [include/crown/runtime/selection.hpp](../../../../../include/crown/runtime/selection.hpp), [src/planner/selection.cpp](../../../../../src/planner/selection.cpp), [src/planner/selection_detail.hpp](../../../../../src/planner/selection_detail.hpp), [src/runtime/ranking_evidence.cpp](../../../../../src/runtime/ranking_evidence.cpp), [src/runtime/reoptimization.cpp](../../../../../src/runtime/reoptimization.cpp), [docs/selection.md](../../../../selection.md), [docs/selection_accounting.md](../../../../selection_accounting.md), [docs/reoptimization.md](../../../../reoptimization.md), [tests/unit/selection_current_test.cpp](../../../../../tests/unit/selection_current_test.cpp), [tests/unit/selection_publication_fault_independent_test.cpp](../../../../../tests/unit/selection_publication_fault_independent_test.cpp), [tests/unit/reoptimization_selection_test.cpp](../../../../../tests/unit/reoptimization_selection_test.cpp), [docs/code_review.md](../../../../code_review.md) |

## B0006

[Lines 17–17](../../../../../src/runtime/selection.cpp#L17); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
const ranking::RuntimeEvidence& CurrentSelection::capture()
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Borrow the exact actual-owner evidence retained with this choice. |
| inputs / outputs | Returns data_-&gt;capture by const reference. |
| invariants | Public CurrentSelection has private construction and copy-like shared-handle moves; this accessor does not recapture/revalidate freshness or mutate selection. |
| ownership | Reference borrows the retained Data graph; keep a CurrentSelection owner alive. |
| failure | Noexcept under valid factory-produced handle invariant; no fallback empty Data allocation. |
| cost | Fixed reference return, no key/array copy or row scan. |
| Design | [src/runtime/selection.cpp](../../../../../src/runtime/selection.cpp), [include/crown/runtime/selection.hpp](../../../../../include/crown/runtime/selection.hpp), [src/planner/selection.cpp](../../../../../src/planner/selection.cpp), [src/planner/selection_detail.hpp](../../../../../src/planner/selection_detail.hpp), [src/runtime/ranking_evidence.cpp](../../../../../src/runtime/ranking_evidence.cpp), [src/runtime/reoptimization.cpp](../../../../../src/runtime/reoptimization.cpp), [docs/selection.md](../../../../selection.md), [docs/selection_accounting.md](../../../../selection_accounting.md), [docs/reoptimization.md](../../../../reoptimization.md), [tests/unit/selection_current_test.cpp](../../../../../tests/unit/selection_current_test.cpp), [tests/unit/selection_publication_fault_independent_test.cpp](../../../../../tests/unit/selection_publication_fault_independent_test.cpp), [tests/unit/reoptimization_selection_test.cpp](../../../../../tests/unit/reoptimization_selection_test.cpp), [docs/code_review.md](../../../../code_review.md) |

## B0007

[Lines 18–18](../../../../../src/runtime/selection.cpp#L18); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::optional<std::uint64_t> CurrentSelection::preparation_nanoseconds()
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Expose whether actual bridge preparation was measured for reoptimization cost attribution. |
| inputs / outputs | Returns the optional stored uint64 nanoseconds by value. |
| invariants | Unmeasured or regressed-clock preparation stays absent. Zero is a real measured duration, not substituted missing time; C02 modeled cost is not converted to nanoseconds. |
| ownership | Only inline optional copy; no source/evidence graph is copied. |
| failure | Declared noexcept; measurement and overflow/binding acceptance occur elsewhere. |
| cost | Fixed optional load, no clock read or runtime capture. |
| Design | [src/runtime/selection.cpp](../../../../../src/runtime/selection.cpp), [include/crown/runtime/selection.hpp](../../../../../include/crown/runtime/selection.hpp), [src/planner/selection.cpp](../../../../../src/planner/selection.cpp), [src/planner/selection_detail.hpp](../../../../../src/planner/selection_detail.hpp), [src/runtime/ranking_evidence.cpp](../../../../../src/runtime/ranking_evidence.cpp), [src/runtime/reoptimization.cpp](../../../../../src/runtime/reoptimization.cpp), [docs/selection.md](../../../../selection.md), [docs/selection_accounting.md](../../../../selection_accounting.md), [docs/reoptimization.md](../../../../reoptimization.md), [tests/unit/selection_current_test.cpp](../../../../../tests/unit/selection_current_test.cpp), [tests/unit/selection_publication_fault_independent_test.cpp](../../../../../tests/unit/selection_publication_fault_independent_test.cpp), [tests/unit/reoptimization_selection_test.cpp](../../../../../tests/unit/reoptimization_selection_test.cpp), [docs/code_review.md](../../../../code_review.md) |

## B0008

[Lines 19–24](../../../../../src/runtime/selection.cpp#L19); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L19-L24:sha256:69ab744a84567c71f9d6c27760427959a46b86626cbd6fe10cad571d44495e08
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Publish an as-of profile only with selected proof and actual Session premises. |
| inputs / outputs | Read retained pure profile and Session context; absent context/monitor, absent proof or a captured violation returns none. Otherwise share existing CurrentSelectionData. |
| invariants | CurrentSelection admission already checked the real capture/source/rules/prefix. This accessor does not reread the owner or refresh historical facts, and does not claim selected/installed identity equality. |
| ownership | Shared existing selection/capture graph; temporary pure-profile handles only change reference counts. |
| failure | Noexcept, no allocation or new catch; unsuccessful conditions return an empty optional. |
| cost | O(1) fields/refcounts, no rule comparison, row scan or update-path work. |
| Design | docs/update_patterns.md#support-action-guarantee-profile, [docs/selection.md](../../../../selection.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0009

[Lines 25–25](../../../../../src/runtime/selection.cpp#L25); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L25-L25:sha256:4809316dd1cdf40d4b2d43adcfacf34ede23ae71e7cd6aae55622d9e1077a236
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Return the selected conditional profile from a qualified capture. |
| inputs / outputs | Read the already-proved pure selection and return its owning profile handle. |
| invariants | Runtime profile construction requires this optional to be present; selected-plan identity can differ from the observed plan. |
| ownership | Share the existing pure Data owner, without cloning report or plan. |
| failure | Noexcept on valid privately constructed runtime profile. |
| cost | O(1) reference work; no allocation. |
| Design | docs/update_patterns.md#support-action-guarantee-profile, [docs/selection.md](../../../../selection.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0010

[Lines 26–28](../../../../../src/runtime/selection.cpp#L26); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L26-L28:sha256:34058333a32aab564bf0e19b241f164f965b08c1f203e630928e96e2cb21a458
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Borrow the actual captured Session monitor status. |
| inputs / outputs | Return the immutable SessionStatisticsContext update-pattern status, including declaration, origins, through-counters, actual physical hash and trust/violation fields. |
| invariants | Private profile construction requires an available unrejected monitor. This is a historical capture after owner advancement, not an authentication of restored past. |
| ownership | Borrow pinned by shared runtime-profile Data; no live Session handle or row owner escapes. |
| failure | Noexcept on a valid profile; no fresh capture or translation. |
| cost | O(1), no allocation or rule clone. |
| Design | docs/update_patterns.md#support-action-guarantee-profile, [docs/selection.md](../../../../selection.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0011

[Lines 29–29](../../../../../src/runtime/selection.cpp#L29); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L29-L29:sha256:bae48498e39bf6dfeb6dfcb8ce935185cdc3f3c2601fbfe3c2ff1c6120c0b57f
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Copy the actual captured physical owner stamp. |
| inputs / outputs | Return the retained combined state stamp with owner, committed physical sequence and layer. |
| invariants | Current-selection boundary admission established capture availability and monitor physical-sequence equality. Command progress remains separate. |
| ownership | Fixed scalar copy; no borrowed owner lifetime is required after return. |
| failure | Noexcept on a valid profile; no fresh runtime read. |
| cost | O(1), no allocation. |
| Design | docs/update_patterns.md#support-action-guarantee-profile, [docs/selection.md](../../../../selection.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0012

[Lines 30–33](../../../../../src/runtime/selection.cpp#L30); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L30-L33:sha256:7fbd10225092f0189077fd14c15e108fec87ab4e14a18a98115d7c2c8ec599a8
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Distinguish a proposed selected plan from the plan observed in the capture. |
| inputs / outputs | Compare selected compiled physical SHA with all64 bytes of the captured monitor physical SHA. |
| invariants | Compares complete physical identity, not just query, height or shape. Equality is as-of capture; it neither refreshes a live owner nor measures work across replacement. |
| ownership | Read two existing immutable hashes; temporary view borrows within the call. |
| failure | Noexcept, no allocation or hashing/recompilation. |
| cost | At most64 fixed character comparisons, constant storage. |
| Design | docs/update_patterns.md#support-action-guarantee-profile, [docs/selection.md](../../../../selection.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0013

[Lines 34–34](../../../../../src/runtime/selection.cpp#L34); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L34-L34:sha256:cf04d99c0f5d3521f67f7c587d20dd3592a5024b903529e1e468844f7fae8135
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Source usage for this declaration span in src/runtime/selection.cpp: opens anonymous namespace with translation-unit-local linkage. |
| inputs / outputs | Compile inputs are the listed headers and namespace/type names. This span adds no result value unless a helper/type definition listed above is instantiated or called. |
| invariants | The exact import, alias, namespace and member declarations determine the local compile/link surface; stronger behavior belongs to their constructors and operations. |
| ownership | Imports, namespace aliases, forward declarations and compile guards create no object owner. Runtime ownership starts with declared object instances and their allocator/member types. |
| failure | No explicit throw/catch appears in this exact span. Includes, constructors, inline members, static initialization and callees can still fail; follow their enclosing API contracts. |
| cost | This span changes compile/link structure and type layout. Runtime initialization, allocation, exceptions and operation work follow the declared owner/callable code; no absence is inferred from declaration syntax. |
| Design | [docs/selection.md](../../../../selection.md), [docs/selection_binding.md](../../../../selection_binding.md), [docs/selection_accounting.md](../../../../selection_accounting.md), [docs/reoptimization.md](../../../../reoptimization.md), [docs/code_specs/subsystem_contracts.md](../../../subsystem_contracts.md) |

## B0014

[Lines 35–37](../../../../../src/runtime/selection.cpp#L35); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::optional<statistics::Freshness> freshness(const PhysicalRuntime& owner,
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Read exact current committed-stamp freshness from the actual PhysicalRuntime. |
| inputs / outputs | Calls owner.statistics_freshness(captured,0), returning optional freshness (session release can be disengaged). |
| invariants | Zero lag requires current owner/layer/sequence; full source/mode/interval/pending checks remain in boundary/revalidation. It does not itself make stale facts current. |
| ownership | Borrows actual owner and owning capture synchronously; returned enum/optional owns no runtime pointer. |
| failure | Any owner access failure propagates to current()'s noexcept mapper; no local generic handler. |
| cost | Fixed stamp access/comparison plus actual owner/session guard cost, with no table-row capture. |
| Design | [src/runtime/selection.cpp](../../../../../src/runtime/selection.cpp), [include/crown/runtime/selection.hpp](../../../../../include/crown/runtime/selection.hpp), [src/planner/selection.cpp](../../../../../src/planner/selection.cpp), [src/planner/selection_detail.hpp](../../../../../src/planner/selection_detail.hpp), [src/runtime/ranking_evidence.cpp](../../../../../src/runtime/ranking_evidence.cpp), [src/runtime/reoptimization.cpp](../../../../../src/runtime/reoptimization.cpp), [docs/selection.md](../../../../selection.md), [docs/selection_accounting.md](../../../../selection_accounting.md), [docs/reoptimization.md](../../../../reoptimization.md), [tests/unit/selection_current_test.cpp](../../../../../tests/unit/selection_current_test.cpp), [tests/unit/selection_publication_fault_independent_test.cpp](../../../../../tests/unit/selection_publication_fault_independent_test.cpp), [tests/unit/reoptimization_selection_test.cpp](../../../../../tests/unit/reoptimization_selection_test.cpp), [docs/code_review.md](../../../../code_review.md) |

## B0015

[Lines 38–40](../../../../../src/runtime/selection.cpp#L38); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::optional<statistics::Freshness> freshness(const DeltaRuntime& owner,
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Read exact current committed-stamp freshness from the actual DeltaRuntime. |
| inputs / outputs | Calls owner.statistics_freshness(captured,0), returning optional freshness (session release can be disengaged). |
| invariants | Zero lag requires current owner/layer/sequence; full source/mode/interval/pending checks remain in boundary/revalidation. It does not itself make stale facts current. |
| ownership | Borrows actual owner and owning capture synchronously; returned enum/optional owns no runtime pointer. |
| failure | Any owner access failure propagates to current()'s noexcept mapper; no local generic handler. |
| cost | Fixed stamp access/comparison plus actual owner/session guard cost, with no table-row capture. |
| Design | [src/runtime/selection.cpp](../../../../../src/runtime/selection.cpp), [include/crown/runtime/selection.hpp](../../../../../include/crown/runtime/selection.hpp), [src/planner/selection.cpp](../../../../../src/planner/selection.cpp), [src/planner/selection_detail.hpp](../../../../../src/planner/selection_detail.hpp), [src/runtime/ranking_evidence.cpp](../../../../../src/runtime/ranking_evidence.cpp), [src/runtime/reoptimization.cpp](../../../../../src/runtime/reoptimization.cpp), [docs/selection.md](../../../../selection.md), [docs/selection_accounting.md](../../../../selection_accounting.md), [docs/reoptimization.md](../../../../reoptimization.md), [tests/unit/selection_current_test.cpp](../../../../../tests/unit/selection_current_test.cpp), [tests/unit/selection_publication_fault_independent_test.cpp](../../../../../tests/unit/selection_publication_fault_independent_test.cpp), [tests/unit/reoptimization_selection_test.cpp](../../../../../tests/unit/reoptimization_selection_test.cpp), [docs/code_review.md](../../../../code_review.md) |

## B0016

[Lines 41–43](../../../../../src/runtime/selection.cpp#L41); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::optional<statistics::Freshness> freshness(const QuerySession& owner,
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Read exact current committed-stamp freshness from the actual QuerySession. |
| inputs / outputs | Calls owner.statistics_freshness(captured,0), returning optional freshness (session release can be disengaged). |
| invariants | Zero lag requires current owner/layer/sequence; full source/mode/interval/pending checks remain in boundary/revalidation. It does not itself make stale facts current. |
| ownership | Borrows actual owner and owning capture synchronously; returned enum/optional owns no runtime pointer. |
| failure | Any owner access failure propagates to current()'s noexcept mapper; no local generic handler. |
| cost | Fixed stamp access/comparison plus actual owner/session guard cost, with no table-row capture. |
| Design | [src/runtime/selection.cpp](../../../../../src/runtime/selection.cpp), [include/crown/runtime/selection.hpp](../../../../../include/crown/runtime/selection.hpp), [src/planner/selection.cpp](../../../../../src/planner/selection.cpp), [src/planner/selection_detail.hpp](../../../../../src/planner/selection_detail.hpp), [src/runtime/ranking_evidence.cpp](../../../../../src/runtime/ranking_evidence.cpp), [src/runtime/reoptimization.cpp](../../../../../src/runtime/reoptimization.cpp), [docs/selection.md](../../../../selection.md), [docs/selection_accounting.md](../../../../selection_accounting.md), [docs/reoptimization.md](../../../../reoptimization.md), [tests/unit/selection_current_test.cpp](../../../../../tests/unit/selection_current_test.cpp), [tests/unit/selection_publication_fault_independent_test.cpp](../../../../../tests/unit/selection_publication_fault_independent_test.cpp), [tests/unit/reoptimization_selection_test.cpp](../../../../../tests/unit/reoptimization_selection_test.cpp), [docs/code_review.md](../../../../code_review.md) |

## B0017

[Lines 44–55](../../../../../src/runtime/selection.cpp#L44); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
pr::Reasons reason(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Translate freshness classification into explicit current-selection boundary reasons. |
| inputs / outputs | Disengaged means released; current maps to zero; within_lag/stale to stale; other named cases map foreign/future/layer; invalid cast falls back read_failed. |
| invariants | Within-lag history is rejected for this zero-lag publication boundary. No numeric reason upgrades capture completeness, proof or source authority. |
| ownership | Only inline optional/bitset values and static enum tags. |
| failure | No throwing operation; this is a diagnostic mapping, not an error catch. |
| cost | Bounded enum switch with no allocation or owner traversal. |
| Design | [src/runtime/selection.cpp](../../../../../src/runtime/selection.cpp), [include/crown/runtime/selection.hpp](../../../../../include/crown/runtime/selection.hpp), [src/planner/selection.cpp](../../../../../src/planner/selection.cpp), [src/planner/selection_detail.hpp](../../../../../src/planner/selection_detail.hpp), [src/runtime/ranking_evidence.cpp](../../../../../src/runtime/ranking_evidence.cpp), [src/runtime/reoptimization.cpp](../../../../../src/runtime/reoptimization.cpp), [docs/selection.md](../../../../selection.md), [docs/selection_accounting.md](../../../../selection_accounting.md), [docs/reoptimization.md](../../../../reoptimization.md), [tests/unit/selection_current_test.cpp](../../../../../tests/unit/selection_current_test.cpp), [tests/unit/selection_publication_fault_independent_test.cpp](../../../../../tests/unit/selection_publication_fault_independent_test.cpp), [tests/unit/reoptimization_selection_test.cpp](../../../../../tests/unit/reoptimization_selection_test.cpp), [docs/code_review.md](../../../../code_review.md) |

## B0018

[Lines 56–57](../../../../../src/runtime/selection.cpp#L56); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L56-L57:sha256:5536267c2079578290350b1a7ca7e3c16196fcf5c12ae3b127bb29cb97265406
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Usage note immediately before \`template&lt;class Owner&gt; void boundary(const ranking::RuntimeEvidence& facts, const Owner& owner, sd::Budget& budget)\`: Caller retains exclusive synchronous owner access through capture and publication. Current stamps alone do not establish pending, source-layer or mode agreement. |
| inputs / outputs | This comment introduces no parameter, field or return value. It documents the adjacent construct beginning at src/runtime/selection.cpp:L43; use that declaration for the actual input/output shape. |
| invariants | The source note states: Caller retains exclusive synchronous owner access through capture and publication. Current stamps alone do not establish pending, source-layer or mode agreement. It is prose guidance; the adjacent implementation is the place to check enforcement. |
| ownership | The comment itself retains nothing. It documents this neighboring ownership/account boundary: Caller retains exclusive synchronous owner access through capture and publication. Current stamps alone do not establish pending, source-layer or mode agreement. Actual lifetime is determined by the declared members and owners. |
| failure | This comment adds no branch or handler. Any failure behavior remains in the adjacent callable implementation and its callers. |
| cost | The prose adds no executable work. Runtime cost belongs to the adjacent operation; the note does not establish a measured or global complexity bound. |
| Design | [docs/selection.md](../../../../selection.md), [docs/selection_binding.md](../../../../selection_binding.md), [docs/selection_accounting.md](../../../../selection_accounting.md), [docs/reoptimization.md](../../../../reoptimization.md), [docs/code_specs/subsystem_contracts.md](../../../subsystem_contracts.md) |

## B0019

[Lines 58–102](../../../../../src/runtime/selection.cpp#L58); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
template<class Owner> void boundary(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Verify actual captured owner, source, pending and mode facts before preparing or publishing a current choice. |
| inputs / outputs | Requires CombinedCapture, charges one freshness plus 12 fixed consistency work (and 12 for sessions), checks zero-lag freshness, physical source layer, consistent state/workload/input owner/sequence, pending flags and actual owner type. A requested pattern additionally requires an actual Session monitor with no violation, matching physical sequence/source/count and exactly equal sorted rules. |
| invariants | Session additionally requires retained non-dropped metadata/context and agreement of requested/resolved mode/completion/live/view/workload options. Caller holds exclusive synchronous owner access throughout capture/selection/publication; this function adds no synchronization. An imported declaration alone cannot authorize an unmonitored live owner; restored sessions retain their explicit trusted-history premise. |
| ownership | Borrows immutable captured facts and actual owner, retaining no new runtime pointer/key. Session context was captured with native guard earlier. |
| failure | Any accumulated reason throws Failure(boundary_unavailable) before prepare/cache publication. Missing capture means released; logical work exhaustion propagates precisely. |
| cost | Existing fixed binding/freshness checks plus opt-in 64-byte source binding and O(R) canonical rule comparison under the aggregate grant. No new row scan or binding allocation; prior evidence capture retains its own costs. |
| Design | [src/runtime/selection.cpp](../../../../../src/runtime/selection.cpp), [include/crown/runtime/selection.hpp](../../../../../include/crown/runtime/selection.hpp), [src/planner/selection.cpp](../../../../../src/planner/selection.cpp), [src/planner/selection_detail.hpp](../../../../../src/planner/selection_detail.hpp), [src/runtime/ranking_evidence.cpp](../../../../../src/runtime/ranking_evidence.cpp), [src/runtime/reoptimization.cpp](../../../../../src/runtime/reoptimization.cpp), [docs/selection.md](../../../../selection.md), [docs/selection_accounting.md](../../../../selection_accounting.md), [docs/reoptimization.md](../../../../reoptimization.md), [tests/unit/selection_current_test.cpp](../../../../../tests/unit/selection_current_test.cpp), [tests/unit/selection_publication_fault_independent_test.cpp](../../../../../tests/unit/selection_publication_fault_independent_test.cpp), [tests/unit/reoptimization_selection_test.cpp](../../../../../tests/unit/reoptimization_selection_test.cpp), [docs/code_review.md](../../../../code_review.md), [docs/update_patterns.md](../../../../update_patterns.md) |

## B0020

[Lines 103–104](../../../../../src/runtime/selection.cpp#L103); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L103-L104:sha256:24da398871674d96742c7aef0573e9c895b7c3f46846ad682b5d6b7b51cb9e16
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Usage note immediately before \`template&lt;class Owner&gt; Attempt current(const planner::CandidateSnapshot& snapshot, const ps::Source& source, const Owner& owner, const ps::Request& request, statistics::Limits state\`: Keep the public noexcept diagnostic mapper around the one prepublication capture/prepare/cache transaction; source/row ownership is in retained native graphs. |
| inputs / outputs | This comment introduces no parameter, field or return value. It documents the adjacent construct beginning at src/runtime/selection.cpp:L76; use that declaration for the actual input/output shape. |
| invariants | The source note states: Keep the public noexcept diagnostic mapper around the one prepublication capture/prepare/cache transaction; source/row ownership is in retained native graphs. It is prose guidance; the adjacent implementation is the place to check enforcement. |
| ownership | The comment itself retains nothing. It documents this neighboring ownership/account boundary: Keep the public noexcept diagnostic mapper around the one prepublication capture/prepare/cache transaction; source/row ownership is in retained native graphs. Actual lifetime is determined by the declared members and owners. |
| failure | This comment adds no branch or handler. Any failure behavior remains in the adjacent callable implementation and its callers. |
| cost | The prose adds no executable work. Runtime cost belongs to the adjacent operation; the note does not establish a measured or global complexity bound. |
| Design | [docs/selection.md](../../../../selection.md), [docs/selection_binding.md](../../../../selection_binding.md), [docs/selection_accounting.md](../../../../selection_accounting.md), [docs/reoptimization.md](../../../../reoptimization.md), [docs/code_specs/subsystem_contracts.md](../../../subsystem_contracts.md) |

## B0021

[Lines 105–179](../../../../../src/runtime/selection.cpp#L105); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
template<class Owner> Attempt current(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Capture, validate, prepare and atomically publish one current actual-owner selection with fixed noexcept diagnostics. |
| inputs / outputs | Builds Operation on actual plan account, admits request, delegates one bounded ranking capture, attaches evidence, checks boundary, prepares pure choice/cache action, admits/funds native wrapper, finalizes, then returns Attempt. |
| invariants | Wrapper allocation precedes every cache statistic/eviction/insertion. prepare stays private; finalize performs final deadline sample then nonthrowing commit. Failure publishes no choice/cache mutation. Caller preserves exclusive synchronous owner access throughout; no locks or concurrent snapshot guarantee is supplied. Pattern-conditioned current capture is supported only for QuerySession; bare PhysicalRuntime/DeltaRuntime refuses unsupported_model before evidence capture. The single existing noexcept mapper remains the failure boundary. |
| ownership | Operation borrows source/request/cache through the call; published wrapper retains funded pure selection/evidence graphs, not live owner. Private scratch releases on failure; operation is torn down before measured completion sampling. |
| failure | Necessary public noexcept boundary maps selection/ranking failures, bad_alloc (including native MemoryFailure), exact native storage cap/overflow/work categories, public Error and unexpected exceptions into fixed Attempt fields. It does not retry, refill grants or swallow source mutations. Before Operation exists, unmatched failures retain default internal_error. |
| cost | Real capture/normalization/assessment/lowering/cache-key work and funded scratch/results, with logical delegated limits distinct from total CPU/memory. Unmeasured bridge adds no outer clock; measured success reads outer start/end around preparation and Operation teardown, storing duration only without clock regression. |
| Design | [src/runtime/selection.cpp](../../../../../src/runtime/selection.cpp), [include/crown/runtime/selection.hpp](../../../../../include/crown/runtime/selection.hpp), [src/planner/selection.cpp](../../../../../src/planner/selection.cpp), [src/planner/selection_detail.hpp](../../../../../src/planner/selection_detail.hpp), [src/runtime/ranking_evidence.cpp](../../../../../src/runtime/ranking_evidence.cpp), [src/runtime/reoptimization.cpp](../../../../../src/runtime/reoptimization.cpp), [docs/selection.md](../../../../selection.md), [docs/selection_accounting.md](../../../../selection_accounting.md), [docs/reoptimization.md](../../../../reoptimization.md), [tests/unit/selection_current_test.cpp](../../../../../tests/unit/selection_current_test.cpp), [tests/unit/selection_publication_fault_independent_test.cpp](../../../../../tests/unit/selection_publication_fault_independent_test.cpp), [tests/unit/reoptimization_selection_test.cpp](../../../../../tests/unit/reoptimization_selection_test.cpp), [docs/code_review.md](../../../../code_review.md), [docs/update_patterns.md](../../../../update_patterns.md) |

```text
    const auto plan=[&] {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Select the actual owner's immutable plan/account before composing native selection. |
| inputs / outputs | For QuerySession obtains report_metadata().plan(); for Physical/Delta obtains owner.plan(). |
| invariants | No compiler DTO or caller-chosen substitute account is accepted for native capture/selection ownership. |
| ownership | Local CompiledProgram/plan handle shares immutable metadata and original account; it does not clone live source rows. |
| failure | Released/invalid owner access or account faults propagate to the outer fixed noexcept diagnostic boundary. |
| cost | Fixed plan/session metadata access and shared ownership; no population traversal. |
| Design | [src/runtime/selection.cpp](../../../../../src/runtime/selection.cpp), [include/crown/runtime/selection.hpp](../../../../../include/crown/runtime/selection.hpp), [src/planner/selection.cpp](../../../../../src/planner/selection.cpp), [src/planner/selection_detail.hpp](../../../../../src/planner/selection_detail.hpp), [src/runtime/ranking_evidence.cpp](../../../../../src/runtime/ranking_evidence.cpp), [src/runtime/reoptimization.cpp](../../../../../src/runtime/reoptimization.cpp), [docs/selection.md](../../../../selection.md), [docs/selection_accounting.md](../../../../selection_accounting.md), [docs/reoptimization.md](../../../../reoptimization.md), [tests/unit/selection_current_test.cpp](../../../../../tests/unit/selection_current_test.cpp), [tests/unit/selection_publication_fault_independent_test.cpp](../../../../../tests/unit/selection_publication_fault_independent_test.cpp), [tests/unit/reoptimization_selection_test.cpp](../../../../../tests/unit/reoptimization_selection_test.cpp), [docs/code_review.md](../../../../code_review.md) |

## B0022

[Lines 180–180](../../../../../src/runtime/selection.cpp#L180); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L180-L180:sha256:412ca345ccf75bf9c0806bce695be8de808b79984251a7a54d202cf6101dd451
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Close the \`anonymous namespace in src/runtime/selection.cpp\` scope at this exact source boundary. |
| inputs / outputs | This token introduces no callable inputs or outputs. Declarations inside \`anonymous namespace in src/runtime/selection.cpp\` define the available names, members and operations. |
| invariants | The closing brace matches the opening \`anonymous namespace in src/runtime/selection.cpp\` at its lexical source position in src/runtime/selection.cpp; it preserves C++ namespace/type nesting. |
| ownership | The closing delimiter creates no owner. Types closed by \`anonymous namespace in src/runtime/selection.cpp\` retain the lifetimes and allocator rules of their own fields and operations. |
| failure | No failure path executes at this closing delimiter. Failure and cleanup behavior belong to enclosed functions and owning types. |
| cost | The delimiter itself performs no runtime work; the enclosed initializers, methods and destructors carry their own costs. |
| Design | [docs/selection.md](../../../../selection.md), [docs/selection_binding.md](../../../../selection_binding.md), [docs/selection_accounting.md](../../../../selection_accounting.md), [docs/reoptimization.md](../../../../reoptimization.md), [docs/code_specs/subsystem_contracts.md](../../../subsystem_contracts.md) |

## B0023

[Lines 181–184](../../../../../src/runtime/selection.cpp#L181); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Attempt select_current(const planner::CandidateSnapshot& s, const ps::Source& source, const PhysicalRuntime& owner,
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Run synchronous current-selection composition for an actual PhysicalRuntime. |
| inputs / outputs | Forwards snapshot/source/owner/request/state_limits/cache/use to current() with measured=false. |
| invariants | Each call takes a fresh bounded actual-owner capture, including height-only policy; caller holds exclusive access until return. Result history must be revalidated before later execution. |
| ownership | Only borrowed call inputs; success owns shared checked selection/evidence; mutable cache is affected only by successful atomic publication. |
| failure | Noexcept current() returns fixed diagnostic Attempt; no wrapper-local exception or retry path. |
| cost | Fixed forwarding plus the full capture/assessment/lowering/cache/native allocation costs of current(); outer preparation clock is not sampled. |
| Design | [src/runtime/selection.cpp](../../../../../src/runtime/selection.cpp), [include/crown/runtime/selection.hpp](../../../../../include/crown/runtime/selection.hpp), [src/planner/selection.cpp](../../../../../src/planner/selection.cpp), [src/planner/selection_detail.hpp](../../../../../src/planner/selection_detail.hpp), [src/runtime/ranking_evidence.cpp](../../../../../src/runtime/ranking_evidence.cpp), [src/runtime/reoptimization.cpp](../../../../../src/runtime/reoptimization.cpp), [docs/selection.md](../../../../selection.md), [docs/selection_accounting.md](../../../../selection_accounting.md), [docs/reoptimization.md](../../../../reoptimization.md), [tests/unit/selection_current_test.cpp](../../../../../tests/unit/selection_current_test.cpp), [tests/unit/selection_publication_fault_independent_test.cpp](../../../../../tests/unit/selection_publication_fault_independent_test.cpp), [tests/unit/reoptimization_selection_test.cpp](../../../../../tests/unit/reoptimization_selection_test.cpp), [docs/code_review.md](../../../../code_review.md) |

## B0024

[Lines 185–188](../../../../../src/runtime/selection.cpp#L185); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Attempt select_current(const planner::CandidateSnapshot& s, const ps::Source& source, const DeltaRuntime& owner,
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Run synchronous current-selection composition for an actual DeltaRuntime. |
| inputs / outputs | Forwards snapshot/source/owner/request/state_limits/cache/use to current() with measured=false. |
| invariants | Each call takes a fresh bounded actual-owner capture, including height-only policy; caller holds exclusive access until return. Result history must be revalidated before later execution. |
| ownership | Only borrowed call inputs; success owns shared checked selection/evidence; mutable cache is affected only by successful atomic publication. |
| failure | Noexcept current() returns fixed diagnostic Attempt; no wrapper-local exception or retry path. |
| cost | Fixed forwarding plus the full capture/assessment/lowering/cache/native allocation costs of current(); outer preparation clock is not sampled. |
| Design | [src/runtime/selection.cpp](../../../../../src/runtime/selection.cpp), [include/crown/runtime/selection.hpp](../../../../../include/crown/runtime/selection.hpp), [src/planner/selection.cpp](../../../../../src/planner/selection.cpp), [src/planner/selection_detail.hpp](../../../../../src/planner/selection_detail.hpp), [src/runtime/ranking_evidence.cpp](../../../../../src/runtime/ranking_evidence.cpp), [src/runtime/reoptimization.cpp](../../../../../src/runtime/reoptimization.cpp), [docs/selection.md](../../../../selection.md), [docs/selection_accounting.md](../../../../selection_accounting.md), [docs/reoptimization.md](../../../../reoptimization.md), [tests/unit/selection_current_test.cpp](../../../../../tests/unit/selection_current_test.cpp), [tests/unit/selection_publication_fault_independent_test.cpp](../../../../../tests/unit/selection_publication_fault_independent_test.cpp), [tests/unit/reoptimization_selection_test.cpp](../../../../../tests/unit/reoptimization_selection_test.cpp), [docs/code_review.md](../../../../code_review.md) |

## B0025

[Lines 189–192](../../../../../src/runtime/selection.cpp#L189); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Attempt select_current(const planner::CandidateSnapshot& s, const ps::Source& source, const QuerySession& owner,
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Run synchronous current-selection composition for an actual QuerySession. |
| inputs / outputs | Forwards snapshot/source/owner/request/state_limits/cache/use to current() with measured=false. |
| invariants | Each call takes a fresh bounded actual-owner capture, including height-only policy; caller holds exclusive access until return. Result history must be revalidated before later execution. |
| ownership | Only borrowed call inputs; success owns shared checked selection/evidence; mutable cache is affected only by successful atomic publication. |
| failure | Noexcept current() returns fixed diagnostic Attempt; no wrapper-local exception or retry path. |
| cost | Fixed forwarding plus the full capture/assessment/lowering/cache/native allocation costs of current(); outer preparation clock is not sampled. |
| Design | [src/runtime/selection.cpp](../../../../../src/runtime/selection.cpp), [include/crown/runtime/selection.hpp](../../../../../include/crown/runtime/selection.hpp), [src/planner/selection.cpp](../../../../../src/planner/selection.cpp), [src/planner/selection_detail.hpp](../../../../../src/planner/selection_detail.hpp), [src/runtime/ranking_evidence.cpp](../../../../../src/runtime/ranking_evidence.cpp), [src/runtime/reoptimization.cpp](../../../../../src/runtime/reoptimization.cpp), [docs/selection.md](../../../../selection.md), [docs/selection_accounting.md](../../../../selection_accounting.md), [docs/reoptimization.md](../../../../reoptimization.md), [tests/unit/selection_current_test.cpp](../../../../../tests/unit/selection_current_test.cpp), [tests/unit/selection_publication_fault_independent_test.cpp](../../../../../tests/unit/selection_publication_fault_independent_test.cpp), [tests/unit/reoptimization_selection_test.cpp](../../../../../tests/unit/reoptimization_selection_test.cpp), [docs/code_review.md](../../../../code_review.md) |

## B0026

[Lines 193–196](../../../../../src/runtime/selection.cpp#L193); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Attempt select_for_reoptimization(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Prepare an actual session selection with measured end-to-end bridge time for later cost accounting. |
| inputs / outputs | Forwards to current(...,true), returning measured preparation only on successful monotonic clock observation. |
| invariants | Measured time includes native capture, selection and Operation teardown; it is separate from modeled ranking scores and cooperative budget elapsed. Absent timing cannot be fabricated later. |
| ownership | Success owns immutable funded selection/capture graph; input session/request/cache remain caller-owned. |
| failure | Noexcept diagnostic behavior is identical to current; failed capture/prepare/cache publication yields no usable CurrentSelection. |
| cost | Full current costs plus explicit steady_clock reads; measurement introduces no per-row timing hooks. |
| Design | [src/runtime/selection.cpp](../../../../../src/runtime/selection.cpp), [include/crown/runtime/selection.hpp](../../../../../include/crown/runtime/selection.hpp), [src/planner/selection.cpp](../../../../../src/planner/selection.cpp), [src/planner/selection_detail.hpp](../../../../../src/planner/selection_detail.hpp), [src/runtime/ranking_evidence.cpp](../../../../../src/runtime/ranking_evidence.cpp), [src/runtime/reoptimization.cpp](../../../../../src/runtime/reoptimization.cpp), [docs/selection.md](../../../../selection.md), [docs/selection_accounting.md](../../../../selection_accounting.md), [docs/reoptimization.md](../../../../reoptimization.md), [tests/unit/selection_current_test.cpp](../../../../../tests/unit/selection_current_test.cpp), [tests/unit/selection_publication_fault_independent_test.cpp](../../../../../tests/unit/selection_publication_fault_independent_test.cpp), [tests/unit/reoptimization_selection_test.cpp](../../../../../tests/unit/reoptimization_selection_test.cpp), [docs/code_review.md](../../../../code_review.md) |

## B0027

[Lines 197–197](../../../../../src/runtime/selection.cpp#L197); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L197-L197:sha256:008a4210a5fecb2ab1c8111d90f4ebb74f89e22ee62c0b3054fc9d0e5421b96c
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Usage note immediately before \`void begin_reoptimization(QuerySession& session,const CurrentSelection& choice,reoptimization::Options options)\`: Historical choices require fresh owner/interval/producer binding and real timing. |
| inputs / outputs | This comment introduces no parameter, field or return value. It documents the adjacent construct beginning at src/runtime/selection.cpp:L166; use that declaration for the actual input/output shape. |
| invariants | The source note states: Historical choices require fresh owner/interval/producer binding and real timing. It is prose guidance; the adjacent implementation is the place to check enforcement. |
| ownership | The note states no ownership relation and retains no value. The adjacent declaration or function controls the actual owner and borrowed-view lifetime. |
| failure | This comment adds no branch or handler. Any failure behavior remains in the adjacent callable implementation and its callers. |
| cost | The prose adds no executable work. Runtime cost belongs to the adjacent operation; the note does not establish a measured or global complexity bound. |
| Design | [docs/selection.md](../../../../selection.md), [docs/selection_binding.md](../../../../selection_binding.md), [docs/selection_accounting.md](../../../../selection_accounting.md), [docs/reoptimization.md](../../../../reoptimization.md), [docs/code_specs/subsystem_contracts.md](../../../subsystem_contracts.md) |

## B0028

[Lines 198–225](../../../../../src/runtime/selection.cpp#L198); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void begin_reoptimization(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Revalidate a measured historical choice and charge actual preparation plus validation before starting session reoptimization. |
| inputs / outputs | Requires preparation_ns, revalidates owner/epoch/interval/modes/policy evidence, checks exact source SHA and relevant indexed/arithmetic/planner/optimization/cost/producer limits, reconciles optional expected boundary, then calls begin_reoptimization_with_cost. |
| invariants | Checked choice supplies selected candidate; edited DTO scores are not execution authority. Caller must preserve exclusive session access. Unmeasured, stale or differently bound plans cannot initiate the transition. Pattern-conditioned choices also require the current Session monitor to remain available and unrejected before existing freshness/source revalidation. |
| ownership | Borrows choice/session and moves only local options into session start; retained evidence/plan handles remain owned by choice. No source row view escapes. |
| failure | Specific Error codes reject unmeasured/stale/binding/expected/clock-regression/cost-overflow cases before start. Session's start method owns its atomic transition/failure semantics; no extra catch or retry. |
| cost | Ranking revalidation explicitly captures a new combined snapshot with empty state request, cloning funded descriptor/current/previous numeric arrays and rerunning a bounded census (including roots*descriptors scans and scratch allocations). Binding comparisons and two steady_clock samples add fixed work; measured validation is checked-added to preparation. Source row distributions are not requested by that revalidation; subsequent rebuild costs belong to session reoptimization. The additional monitor-status copy retains a shared declaration handle without cloning rules. |
| Design | [src/runtime/selection.cpp](../../../../../src/runtime/selection.cpp), [include/crown/runtime/selection.hpp](../../../../../include/crown/runtime/selection.hpp), [src/planner/selection.cpp](../../../../../src/planner/selection.cpp), [src/planner/selection_detail.hpp](../../../../../src/planner/selection_detail.hpp), [src/runtime/ranking_evidence.cpp](../../../../../src/runtime/ranking_evidence.cpp), [src/runtime/reoptimization.cpp](../../../../../src/runtime/reoptimization.cpp), [docs/selection.md](../../../../selection.md), [docs/selection_accounting.md](../../../../selection_accounting.md), [docs/reoptimization.md](../../../../reoptimization.md), [tests/unit/selection_current_test.cpp](../../../../../tests/unit/selection_current_test.cpp), [tests/unit/selection_publication_fault_independent_test.cpp](../../../../../tests/unit/selection_publication_fault_independent_test.cpp), [tests/unit/reoptimization_selection_test.cpp](../../../../../tests/unit/reoptimization_selection_test.cpp), [docs/code_review.md](../../../../code_review.md), [docs/update_patterns.md](../../../../update_patterns.md) |

## B0029

[Lines 226–226](../../../../../src/runtime/selection.cpp#L226); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L226-L226:sha256:e0c368304a3d445f2c74d6a5a3006ecc2474da49759f6f40fa9a8ea696df20a3
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Close the \`namespace crown::runtime::selection\` scope at this exact source boundary. |
| inputs / outputs | This token introduces no callable inputs or outputs. Declarations inside \`namespace crown::runtime::selection\` define the available names, members and operations. |
| invariants | The closing brace matches the opening \`namespace crown::runtime::selection\` at its lexical source position in src/runtime/selection.cpp; it preserves C++ namespace/type nesting. |
| ownership | The closing delimiter creates no owner. Types closed by \`namespace crown::runtime::selection\` retain the lifetimes and allocator rules of their own fields and operations. |
| failure | No failure path executes at this closing delimiter. Failure and cleanup behavior belong to enclosed functions and owning types. |
| cost | The delimiter itself performs no runtime work; the enclosed initializers, methods and destructors carry their own costs. |
| Design | [docs/selection.md](../../../../selection.md), [docs/selection_binding.md](../../../../selection_binding.md), [docs/selection_accounting.md](../../../../selection_accounting.md), [docs/reoptimization.md](../../../../reoptimization.md), [docs/code_specs/subsystem_contracts.md](../../../subsystem_contracts.md) |
