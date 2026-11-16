# `src/planner/residual.cpp` — block usage map

[Source](../../../../../src/planner/residual.cpp) · [Source index](../../../README.md) · [Subsystem contracts](../../../subsystem_contracts.md) · [Reviewed primitives](../../../primitives.md)

Generate and replay residual-reduction/reconstruction candidates as a structural aid to the exact planner.

Snapshot SHA-256: `0f28a4f49f3415b91df8a8a61d172cdf5988a7dd669e6df9abac0d6e6da94a14`. 418 lines partitioned into 55 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [residual](../../../subsystem_contracts.md#residual). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/residual_candidates.md](../../../../residual_candidates.md), [docs/planner_proofs.md](../../../../planner_proofs.md), [docs/code_review.md](../../../../code_review.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–16](../../../../../src/planner/residual.cpp#L1) | Imports dependencies; declares namespace scope; declares values/defaults or compile-time conditions. | growth new; source comment (unverified): // Public artifact getters borrow from a live owning handle. Only this null · [reviewed contract](#b0001) |
| [B0002 · 17–20](../../../../../src/planner/residual.cpp#L17) | Callable definition: template&lt;class T&gt; const T& require(const std::shared_ptr&lt;const T&gt;& value) | calls Error; guard template&lt;class T&gt; const T& require(const std::shared_ptr&lt;const T&gt;& value) {; returns *value; source comment (unverified): // Public artifact getters borrow from a live owning handle. Only this null · [reviewed contract](#b0002) |
| [B0003 · 21–24](../../../../../src/planner/residual.cpp#L21) | Callable definition: void validate_limits(const ResidualLimits& value) | calls cd::valid_ceiling, Error · [reviewed contract](#b0003) |
| [B0004 · 25–28](../../../../../src/planner/residual.cpp#L25) | Callable definition: bool monotone_exact(const ContinuationLimits& a, const ContinuationLimits& b) noexcept | calls cd::monotone_phase, cd::monotone_ceiling; returns cd::monotone_phase(a.producer, b.producer) && cd::monotone_phase(a.replay, b.replay) && · [reviewed contract](#b0004) |
| [B0005 · 29–36](../../../../../src/planner/residual.cpp#L29) | Callable definition: ResidualStatistics add(ResidualStatistics a, const ResidualStatistics& b) noexcept | calls ADD, cd::saturating_add; returns a · [reviewed contract](#b0005) |
| [B0006 · 37–44](../../../../../src/planner/residual.cpp#L37) | Callable definition: ResidualStopReason ordinary_stop(StopReason value) noexcept | calls ; returns ResidualStopReason::total_work; ResidualStopReason::total_time · [reviewed contract](#b0006) |
| [B0007 · 45–46](../../../../../src/planner/residual.cpp#L45) | declares namespace scope. | source comment (unverified): // namespace · [reviewed contract](#b0007) |
| [B0008 · 47–50](../../../../../src/planner/residual.cpp#L47) | Type/record definition: struct ArtifactFactory | returns ResidualTrace(std::move(value)); ResidualCandidate(std::move(value)) · [reviewed contract](#b0008) |
| [B0009 · 51–51](../../../../../src/planner/residual.cpp#L51) | Closes surrounding scope/type. |  · [reviewed contract](#b0009) |
| [B0010 · 52–52](../../../../../src/planner/residual.cpp#L52) | Callable definition: ResidualTrace::ResidualTrace(std::shared_ptr&lt;const rd::TraceData&gt; value) noexcept : data_(std::move(value)) | calls data_, std::move · [reviewed contract](#b0010) |
| [B0011 · 53–53](../../../../../src/planner/residual.cpp#L53) | Callable definition: bool ResidualTrace::valid() const noexcept | calls ; returns static_cast&lt;bool&gt;(data_) · [reviewed contract](#b0011) |
| [B0012 · 54–54](../../../../../src/planner/residual.cpp#L54) | Callable definition: const Catalog& ResidualTrace::catalog() const | calls require; guard const Catalog& ResidualTrace::catalog() const { return require(data_).binding-&gt;catalog; }; returns require(data_).binding-&gt;catalog · [reviewed contract](#b0012) |
| [B0013 · 55–55](../../../../../src/planner/residual.cpp#L55) | Callable definition: const Query& ResidualTrace::query() const | calls require; guard const Query& ResidualTrace::query() const { return require(data_).binding-&gt;query; }; returns require(data_).binding-&gt;query · [reviewed contract](#b0013) |
| [B0014 · 56–56](../../../../../src/planner/residual.cpp#L56) | Callable definition: const ResidualTraceRecord& ResidualTrace::record() const | calls require; guard const ResidualTraceRecord& ResidualTrace::record() const { return *require(data_).record; }; returns *require(data_).record · [reviewed contract](#b0014) |
| [B0015 · 57–57](../../../../../src/planner/residual.cpp#L57) | Callable definition: ResidualCandidate::ResidualCandidate(std::shared_ptr&lt;const rd::CandidateData&gt; value) noexcept : data_(std::move(value)) | calls data_, std::move · [reviewed contract](#b0015) |
| [B0016 · 58–58](../../../../../src/planner/residual.cpp#L58) | Callable definition: bool ResidualCandidate::valid() const noexcept | calls ; returns static_cast&lt;bool&gt;(data_) · [reviewed contract](#b0016) |
| [B0017 · 59–59](../../../../../src/planner/residual.cpp#L59) | Callable definition: const Catalog& ResidualCandidate::catalog() const | calls require; guard const Catalog& ResidualCandidate::catalog() const { return require(data_).binding-&gt;catalog; }; returns require(data_).binding-&gt;catalog · [reviewed contract](#b0017) |
| [B0018 · 60–60](../../../../../src/planner/residual.cpp#L60) | Callable definition: const Query& ResidualCandidate::query() const | calls require; guard const Query& ResidualCandidate::query() const { return require(data_).binding-&gt;query; }; returns require(data_).binding-&gt;query · [reviewed contract](#b0018) |
| [B0019 · 61–64](../../../../../src/planner/residual.cpp#L61) | Callable definition: const FreeConnexTree& ResidualCandidate::tree() const | calls require, tree; guard const auto& p = require(data_);; returns p.checked ? *p.checked-&gt;tree : p.exact_upper-&gt;tree() · [reviewed contract](#b0019) |
| [B0020 · 65–68](../../../../../src/planner/residual.cpp#L65) | Callable definition: std::size_t ResidualCandidate::height() const | calls require, height; guard const auto& p = require(data_);; returns p.checked ? p.checked-&gt;height : p.exact_upper-&gt;height() · [reviewed contract](#b0020) |
| [B0021 · 69–69](../../../../../src/planner/residual.cpp#L69) | Callable definition: ResidualOrigin ResidualCandidate::origin() const | calls require; guard ResidualOrigin ResidualCandidate::origin() const { return require(data_).origin; }; returns require(data_).origin · [reviewed contract](#b0021) |
| [B0022 · 70–70](../../../../../src/planner/residual.cpp#L70) | Callable definition: ResidualTrace ResidualCandidate::trace() const | calls rd::ArtifactFactory::trace, require; guard ResidualTrace ResidualCandidate::trace() const { return rd::ArtifactFactory::trace(require(data_).t…; returns rd::ArtifactFactory::trace(require(data_).trace) · [reviewed contract](#b0022) |
| [B0023 · 71–72](../../../../../src/planner/residual.cpp#L71) | declares types or opens a type body. |  · [reviewed contract](#b0023) |
| [B0024 · 73–77](../../../../../src/planner/residual.cpp#L73) | Type/record definition: enum class Stage |  · [reviewed contract](#b0024) |
| [B0025 · 78–101](../../../../../src/planner/residual.cpp#L78) | declares values/defaults or compile-time conditions. |  · [reviewed contract](#b0025) |
| [B0026 · 102–104](../../../../../src/planner/residual.cpp#L102) | Callable definition: Impl(std::shared_ptr&lt;const cd::BindingData&gt; input, ResidualOptions value) : binding(std::move(input)), options(value), constructi… | calls binding, std::move, options, construction; growth make_shared · [reviewed contract](#b0026) |
| [B0027 · 105–105](../../../../../src/planner/residual.cpp#L105) | Callable definition: bool terminal() const noexcept | calls ; returns stage == Stage::complete \|\| stage == Stage::failed \|\| stage == Stage::cancelled · [reviewed contract](#b0027) |
| [B0028 · 106–109](../../../../../src/planner/residual.cpp#L106) | Callable definition: ResidualStopReason terminal_reason() const noexcept | calls ; returns stage == Stage::complete ? ResidualStopReason::complete : · [reviewed contract](#b0028) |
| [B0029 · 110–110](../../../../../src/planner/residual.cpp#L110) | Callable definition: void fail(ResidualStopReason value) noexcept | calls  · [reviewed contract](#b0029) |
| [B0030 · 111–116](../../../../../src/planner/residual.cpp#L111) | Callable definition: ResidualStatistics statistics() const noexcept | calls add; returns result · [reviewed contract](#b0030) |
| [B0031 · 117–121](../../../../../src/planner/residual.cpp#L117) | Callable definition: SearchProgress exact_progress() const noexcept | calls progress; returns original-&gt;progress(); reconstruction-&gt;exact_progress() · [reviewed contract](#b0031) |
| [B0032 · 122–127](../../../../../src/planner/residual.cpp#L122) | Callable definition: std::size_t depth() const noexcept | calls current_depth; returns reduction-&gt;current_depth(); checker-&gt;current_depth() · [reviewed contract](#b0032) |
| [B0033 · 128–142](../../../../../src/planner/residual.cpp#L128) | Callable definition: ResidualPhase phase() const noexcept | calls ; returns ResidualPhase::admitted; reduction-&gt;phase() · [reviewed contract](#b0033) |
| [B0034 · 143–145](../../../../../src/planner/residual.cpp#L143) | Callable definition: void record_counter_room(std::uint64_t value) const | calls max, rd::Limited · [reviewed contract](#b0034) |
| [B0035 · 146–148](../../../../../src/planner/residual.cpp#L146) | Explanatory comments or spacing. | source comment (unverified): // One retained worker/publication operation. Never upgrade a prefix proof: · [reviewed contract](#b0035) |
| [B0036 · 149–254](../../../../../src/planner/residual.cpp#L149) | Callable definition: rd::Step unit() | calls std::move, step, trace_record, fail; returns step; step; growth make_shared, make_unique; source comment (unverified): // One retained worker/publication operation. Never upgrade a prefix proof: · [reviewed contract](#b0036) |
| [B0037 · 255–255](../../../../../src/planner/residual.cpp#L255) | Closes surrounding scope/type. |  · [reviewed contract](#b0037) |
| [B0038 · 256–256](../../../../../src/planner/residual.cpp#L256) | Callable definition: ResidualSearch::ResidualSearch(std::unique_ptr&lt;Impl&gt; value) noexcept : data_(std::move(value)) | calls data_, std::move · [reviewed contract](#b0038) |
| [B0039 · 257–261](../../../../../src/planner/residual.cpp#L257) | declares callable signatures; declares values/defaults or compile-time conditions. | source comment (unverified): // Input ownership/validation and initial allocations precede work metering; · [reviewed contract](#b0039) |
| [B0040 · 262–270](../../../../../src/planner/residual.cpp#L262) | Callable definition: ResidualSearch ResidualSearch::create(Catalog catalog, Query query, ResidualOptions options) | calls validate_limits, Error, validate, std::move; returns ResidualSearch(std::make_unique&lt;Impl&gt;(std::move(input), options)); growth make_shared, make_unique; source comment (unverified): // Input ownership/validation and initial allocations precede work metering; · [reviewed contract](#b0040) |
| [B0041 · 271–273](../../../../../src/planner/residual.cpp#L271) | Explanatory comments or spacing. | source comment (unverified): // Keep limit/bad_alloc catches: pending closures remain retryable. The final · [reviewed contract](#b0041) |
| [B0042 · 274–323](../../../../../src/planner/residual.cpp#L274) | Callable definition: ResidualAdvance ResidualSearch::advance(WorkQuantum quantum) noexcept | calls progress, answer, count, terminal; guard const auto ceiling = d.ledger.check();; returns ResidualAdvance{reason, exact, progress()}; answer(ResidualStopReason::moved_from); 1 loop sites; source comment (unverified): // Keep limit/bad_alloc catches: pending closures remain retryable. The final · [reviewed contract](#b0042) |
| [B0043 · 324–325](../../../../../src/planner/residual.cpp#L324) | Explanatory comments or spacing. | source comment (unverified): // Report original bounds only; prefix exact diagnostics never raise lower. · [reviewed contract](#b0043) |
| [B0044 · 326–351](../../../../../src/planner/residual.cpp#L326) | Callable definition: ResidualProgress ResidualSearch::progress() const noexcept | calls phase, empty, height, statistics; returns p; p; source comment (unverified): // Report original bounds only; prefix exact diagnostics never raise lower. · [reviewed contract](#b0044) |
| [B0045 · 352–355](../../../../../src/planner/residual.cpp#L352) | Callable definition: ResidualOptions ResidualSearch::options() const | calls Error; returns data_-&gt;options · [reviewed contract](#b0045) |
| [B0046 · 356–359](../../../../../src/planner/residual.cpp#L356) | Callable definition: const Catalog& ResidualSearch::catalog() const | calls Error; returns data_-&gt;binding-&gt;catalog · [reviewed contract](#b0046) |
| [B0047 · 360–363](../../../../../src/planner/residual.cpp#L360) | Callable definition: const Query& ResidualSearch::query() const | calls Error; returns data_-&gt;binding-&gt;query · [reviewed contract](#b0047) |
| [B0048 · 364–367](../../../../../src/planner/residual.cpp#L364) | Callable definition: std::optional&lt;ResidualTrace&gt; ResidualSearch::trace() const noexcept | calls rd::ArtifactFactory::trace; returns {}; rd::ArtifactFactory::trace(data_-&gt;trace_data) · [reviewed contract](#b0048) |
| [B0049 · 368–371](../../../../../src/planner/residual.cpp#L368) | Callable definition: std::optional&lt;ResidualCandidate&gt; ResidualSearch::candidate() const noexcept | calls rd::ArtifactFactory::candidate; returns {}; rd::ArtifactFactory::candidate(data_-&gt;candidate_data) · [reviewed contract](#b0049) |
| [B0050 · 372–375](../../../../../src/planner/residual.cpp#L372) | Callable definition: std::optional&lt;VerifiedOptimum&gt; ResidualSearch::exact_original() const noexcept | calls ; returns {}; data_-&gt;exact_optimum · [reviewed contract](#b0050) |
| [B0051 · 376–379](../../../../../src/planner/residual.cpp#L376) | Callable definition: std::optional&lt;VerifiedInfeasible&gt; ResidualSearch::infeasibility() const noexcept | calls ; returns {}; data_-&gt;exact_infeasibility · [reviewed contract](#b0051) |
| [B0052 · 380–399](../../../../../src/planner/residual.cpp#L380) | Callable definition: LimitChange ResidualSearch::raise_limits(ResidualLimits value) noexcept | calls terminal, cd::valid_ceiling, cd::monotone_phase, cd::monotone_ceiling; returns LimitChange::terminal; LimitChange::invalid · [reviewed contract](#b0052) |
| [B0053 · 400–401](../../../../../src/planner/residual.cpp#L400) | Explanatory comments or spacing. | source comment (unverified): // Snapshot worker history before release. Published immutable handles keep · [reviewed contract](#b0053) |
| [B0054 · 402–417](../../../../../src/planner/residual.cpp#L402) | Callable definition: void ResidualSearch::cancel() noexcept | calls terminal, add, statistics, exact_progress; source comment (unverified): // Snapshot worker history before release. Published immutable handles keep · [reviewed contract](#b0054) |
| [B0055 · 418–418](../../../../../src/planner/residual.cpp#L418) | Closes surrounding scope/type. | source comment (unverified): // namespace crown::planner · [reviewed contract](#b0055) |

## B0001

[Lines 1–16](../../../../../src/planner/residual.cpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L1-L16:sha256:7ac254a6e45379e08348118f4a8632afdc22b39dc510137deb3ce4543d26b05d
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | make #include "crown/planner/residual.hpp", #include "crown/api/error.hpp", #include "continuation_budget.hpp", #include "residual_machine.hpp", #include &lt;algorithm&gt;, #include &lt;limits&gt;, #include &lt;new&gt;, #include &lt;utility&gt; available to src/planner/residual.cpp; open crown::planner and anonymous helper namespace. Attached note: Public artifact getters borrow from a live owning handle. Only this null guard is needed here; publication already established the payload invariants. In this span, bind rd = residual_detail, cd = continuation_detail. |
| inputs / outputs | Includes supply declarations; the listed namespace aliases bind names, and any listed constexpr bounds are constant-initialized metadata. These declarations do not run a planner search or validate a query. |
| invariants | Includes, namespace openings, aliases, and forward declarations determine C++ name visibility and type availability; they do not validate planner data or grant proof authority. |
| ownership | Namespace aliases own no runtime object. Any constexpr bounds in this span are fixed scalar metadata; no query owner, mutable counter or allocation grant is created by them. |
| failure | A missing header, incompatible declaration, or ill-formed type use fails during compilation; runtime failures remain in the called code. |
| cost | Preprocessing, name lookup and compile-time constant evaluation; constexpr bounds require no dynamic initialization and can occupy fixed constant storage when used. Included definitions retain their own call/construction costs. |
| Design | [src/planner/residual.cpp](../../../../../src/planner/residual.cpp), [docs/residual_candidates.md](../../../../residual_candidates.md), [Refactor.md §5.3](../../../../../Refactor.md) |

## B0002

[Lines 17–20](../../../../../src/planner/residual.cpp#L17); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
template<class T> const T& require(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Reject dereference of a moved-from immutable artifact handle. |
| inputs / outputs | shared_ptr&lt;const T&gt; in; const T& out for this full expression. |
| invariants | A nonnull payload has been prepared privately with all required inner pointers; this check tests only the outer handle. |
| ownership | Does not retain a reference count; returned reference borrows the caller handle. |
| failure | Throws Error(invalid_residual_handle) on null. Error message construction can allocate. |
| cost | Constant-time null check/dereference on success. |
| Design | [include/crown/planner/residual.hpp](../../../../../include/crown/planner/residual.hpp) |

## B0003

[Lines 21–24](../../../../../src/planner/residual.cpp#L21); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void validate_limits(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Validate every active-time ceiling accepted by residual admission. |
| inputs / outputs | ResidualLimits in; normal return or diagnostic. |
| invariants | Checks residual and both exact phase ceilings; zero is permitted and optional absence means unbounded. |
| ownership | Borrows the passed value; stores nothing. |
| failure | Negative time throws invalid_residual_limits before a search owner is created. |
| cost | Three constant-time optional/time checks. |
| Design | [src/planner/residual_machine.hpp](../../../../../src/planner/residual_machine.hpp), [src/planner/continuation_budget.hpp](../../../../../src/planner/continuation_budget.hpp), [include/crown/planner/residual.hpp](../../../../../include/crown/planner/residual.hpp) |

## B0004

[Lines 25–28](../../../../../src/planner/residual.cpp#L25); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
bool monotone_exact(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Require an exact-search ceiling extension to preserve consumed work policy. |
| inputs / outputs | Old and proposed ContinuationLimits; Boolean result. |
| invariants | Both producer/replay phase limits and logical depth must be monotone; unbounded cannot become finite. |
| ownership | Borrows values; mutates nothing. |
| failure | Noexcept, false for any tightening. |
| cost | Fixed optional comparisons. |
| Design | [src/planner/continuation_budget.hpp](../../../../../src/planner/continuation_budget.hpp), [docs/planner_continuations.md](../../../../planner_continuations.md) |

## B0005

[Lines 29–36](../../../../../src/planner/residual.cpp#L29); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
ResidualStatistics add(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Merge diagnostic statistics without overflow or allocation. |
| inputs / outputs | First aggregate by value plus second const reference; summed copy returned. |
| invariants | All twelve fields use saturating addition; this cannot create mathematical proof evidence. |
| ownership | Owns returned scalar copy; does not change either worker. |
| failure | Noexcept; uint64 overflow saturates rather than wraps. |
| cost | Fixed twelve additions. |
| Design | [include/crown/planner/residual.hpp](../../../../../include/crown/planner/residual.hpp), [src/planner/continuation_budget.hpp](../../../../../src/planner/continuation_budget.hpp) |

## B0006

[Lines 37–44](../../../../../src/planner/residual.cpp#L37); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
ResidualStopReason ordinary_stop(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Translate outer ResourceLedger stops into residual status. |
| inputs / outputs | StopReason in; residual work/time/overflow or internal_failure out. |
| invariants | Only outer ledger reasons are expected; unmapped values fail closed as an internal failure. |
| ownership | Value-only translation. |
| failure | Noexcept; no diagnostic allocation. |
| cost | Constant switch. |
| Design | [src/planner/continuation_budget.hpp](../../../../../src/planner/continuation_budget.hpp), [include/crown/planner/residual.hpp](../../../../../include/crown/planner/residual.hpp) |

## B0007

[Lines 45–46](../../../../../src/planner/residual.cpp#L45); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L45-L46:sha256:13bab1e16ab52fd2ee3cfd8367ba2ef67c7281caaa4d1e18e1454617c8076fd3
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Close the anonymous namespace, then open residual_detail within crown::planner.  |
| inputs / outputs | This namespace, scope, or declaration boundary has no runtime call inputs or outputs. |
| invariants | It changes compile-time visibility or declaration identity only; attached comments do not enforce or prove the described behavior. |
| ownership | This span creates no runtime owner. Later object definitions and calls determine storage and lifetimes. |
| failure | An invalid declaration or scope boundary fails compilation; no runtime exception or resource stop comes from this span. |
| cost | Compile-time parsing and preprocessor bookkeeping only; no runtime branch, allocation, clock read, counter debit, or engine hook. |
| Design | [src/planner/residual.cpp](../../../../../src/planner/residual.cpp), [docs/residual_candidates.md](../../../../residual_candidates.md), [Refactor.md §5.3](../../../../../Refactor.md) |

## B0008

[Lines 47–50](../../../../../src/planner/residual.cpp#L47); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct ArtifactFactory {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Bridge private constructors after the facade has prepared immutable artifact data. |
| inputs / outputs | trace/candidate accept shared const payloads and return public handle values. |
| invariants | Factory itself performs no verification; its call sites must supply replayed TraceData or checked CandidateData. |
| ownership | Moves shared ownership into each artifact without copying payloads. |
| failure | Noexcept; no allocation. Null or inconsistent payloads are prevented by the owning caller contract. |
| cost | Constant pointer/control-block transfer. |
| Design | [include/crown/planner/residual.hpp](../../../../../include/crown/planner/residual.hpp), [src/planner/residual_machine.hpp](../../../../../src/planner/residual_machine.hpp) |

## B0009

[Lines 51–51](../../../../../src/planner/residual.cpp#L51); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L51-L51:sha256:412ca345ccf75bf9c0806bce695be8de808b79984251a7a54d202cf6101dd451
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | This block close the lexical scope identified by the source span. |
| inputs / outputs | A scope delimiter has no call inputs or outputs; it controls which following declarations belong to the C++ namespace, class, or helper scope. |
| invariants | The braces set lexical visibility and type boundaries only. Any attached note is documentation and does not enforce behavior. |
| ownership | The delimiter and note acquire, release, or transfer no runtime object. Member lifetimes come from the enclosed type definitions. |
| failure | An unmatched or misplaced brace fails compilation; this block adds no runtime exception or resource-stop path. |
| cost | No runtime work or allocation is added. The compiler parses the scope boundary and comment. |
| Design | [src/planner/residual.cpp](../../../../../src/planner/residual.cpp), [docs/residual_candidates.md](../../../../residual_candidates.md), [Refactor.md §5.3](../../../../../Refactor.md) |

## B0010

[Lines 52–52](../../../../../src/planner/residual.cpp#L52); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
ResidualTrace::ResidualTrace(std::shared_ptr<const rd::TraceData>
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Adopt the already prepared verified trace payload. |
| inputs / outputs | Shared immutable TraceData into a private ResidualTrace. |
| invariants | Called by ArtifactFactory only; replay authority is established before construction. |
| ownership | Moves shared ownership; no catalog/query/record copy. |
| failure | Noexcept; no checks beyond prior factory invariants. |
| cost | Constant-time handle construction. |
| Design | [include/crown/planner/residual.hpp](../../../../../include/crown/planner/residual.hpp), [src/planner/residual_machine.hpp](../../../../../src/planner/residual_machine.hpp) |

## B0011

[Lines 53–53](../../../../../src/planner/residual.cpp#L53); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
bool ResidualTrace::valid()
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Allow safe detection of moved-from trace handles. |
| inputs / outputs | No arguments; true iff data_ is present. |
| invariants | A true result says this privately produced handle owns data; it does not assert any tree or height. |
| ownership | Reads shared-pointer presence only. |
| failure | Noexcept and allocation-free. |
| cost | Constant-time. |
| Design | [include/crown/planner/residual.hpp](../../../../../include/crown/planner/residual.hpp), [docs/residual_candidates.md](../../../../residual_candidates.md) |

## B0012

[Lines 54–54](../../../../../src/planner/residual.cpp#L54); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
const Catalog& ResidualTrace::catalog()
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Expose the original catalog retained by the trace. |
| inputs / outputs | Returns const reference to TraceData.binding.catalog. |
| invariants | This is the full original catalog, also used by dense terminal table IDs. |
| ownership | Borrowed reference lives while some trace/binding owner remains alive. |
| failure | require throws invalid_residual_handle after move; normal access does not allocate. |
| cost | Constant-time pointer traversal. |
| Design | [include/crown/planner/residual.hpp](../../../../../include/crown/planner/residual.hpp), [src/planner/residual_machine.hpp](../../../../../src/planner/residual_machine.hpp), [src/planner/residual_view.cpp](../../../../../src/planner/residual_view.cpp) |

## B0013

[Lines 55–55](../../../../../src/planner/residual.cpp#L55); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
const Query& ResidualTrace::query()
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Expose the original query retained alongside the trace. |
| inputs / outputs | Returns const reference to the admitted Query. |
| invariants | Original terms/head/occurrence identities remain distinct from terminal_view.query. |
| ownership | Borrowed reference into shared immutable BindingData. |
| failure | Moved-from handle rejects through require. |
| cost | Constant-time; no query copy. |
| Design | [include/crown/planner/residual.hpp](../../../../../include/crown/planner/residual.hpp), [src/planner/residual_machine.hpp](../../../../../src/planner/residual_machine.hpp), [docs/residual_candidates.md](../../../../residual_candidates.md) |

## B0014

[Lines 56–56](../../../../../src/planner/residual.cpp#L56); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
const ResidualTraceRecord& ResidualTrace::record()
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Expose the completed, independently replayed trace record. |
| inputs / outputs | Returns const ResidualTraceRecord& from the immutable payload. |
| invariants | Record validity concerns reduction and mapping only. |
| ownership | Borrowed nested record reference; caller must keep an owning handle alive. |
| failure | Moved-from access throws invalid_residual_handle. |
| cost | Constant-time; no nested-container copy. |
| Design | [include/crown/planner/residual.hpp](../../../../../include/crown/planner/residual.hpp), [src/planner/residual_trace.cpp](../../../../../src/planner/residual_trace.cpp) |

## B0015

[Lines 57–57](../../../../../src/planner/residual.cpp#L57); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
ResidualCandidate::ResidualCandidate(std::shared_ptr<const rd::CandidateData>
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Adopt a fully prepared checked candidate payload. |
| inputs / outputs | Private constructor receives immutable CandidateData. |
| invariants | Payload must have exactly one tree-authority representation and an original trace/binding. |
| ownership | Moves shared ownership; previous candidates can retain different payloads. |
| failure | Noexcept; factory/call sites supply nonnull valid payloads. |
| cost | Constant pointer transfer. |
| Design | [include/crown/planner/residual.hpp](../../../../../include/crown/planner/residual.hpp), [src/planner/residual_machine.hpp](../../../../../src/planner/residual_machine.hpp) |

## B0016

[Lines 58–58](../../../../../src/planner/residual.cpp#L58); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
bool ResidualCandidate::valid()
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Test whether this candidate still owns its payload. |
| inputs / outputs | Boolean pointer-presence result. |
| invariants | A nonnull privately published payload remains immutable; this test does not report original exactness. |
| ownership | Reads the handle without retaining extra ownership. |
| failure | Noexcept and allocation-free. |
| cost | Constant-time. |
| Design | [include/crown/planner/residual.hpp](../../../../../include/crown/planner/residual.hpp), [docs/residual_candidates.md](../../../../residual_candidates.md) |

## B0017

[Lines 59–59](../../../../../src/planner/residual.cpp#L59); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
const Catalog& ResidualCandidate::catalog()
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Expose the full original catalog backing this upper witness. |
| inputs / outputs | Const Catalog& from the candidate binding. |
| invariants | Original catalog binding is retained even if a tree came from delegated exact search. |
| ownership | Borrowed reference into shared immutable candidate data. |
| failure | Moved-from access throws invalid_residual_handle. |
| cost | Constant-time; no copy. |
| Design | [include/crown/planner/residual.hpp](../../../../../include/crown/planner/residual.hpp), [src/planner/residual_machine.hpp](../../../../../src/planner/residual_machine.hpp) |

## B0018

[Lines 60–60](../../../../../src/planner/residual.cpp#L60); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
const Query& ResidualCandidate::query()
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Expose the original query certified by this upper witness. |
| inputs / outputs | Const Query& from CandidateData.binding. |
| invariants | A reconstructed candidate uses the final same-owner P02 check; this is never the induced prefix query. |
| ownership | Borrowed reference requiring a live artifact owner. |
| failure | Moved-from access rejects through require. |
| cost | Constant-time; no query allocation. |
| Design | [include/crown/planner/residual.hpp](../../../../../include/crown/planner/residual.hpp), [src/planner/residual_reconstruct.cpp](../../../../../src/planner/residual_reconstruct.cpp) |

## B0019

[Lines 61–64](../../../../../src/planner/residual.cpp#L61); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
const FreeConnexTree& ResidualCandidate::tree()
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Return the checked original-query tree in either candidate representation. |
| inputs / outputs | Uses CheckedUpper.tree when present, otherwise ValidatedIncumbent.tree(). |
| invariants | Exactly one representation is valid; the fallback optional is populated whenever checked is absent. |
| ownership | Borrowed immutable tree; its owner is retained by the candidate payload. |
| failure | Moved-from outer handle rejects. Inconsistent inner alternatives violate private construction invariants. |
| cost | Constant-time branch and pointer traversal. |
| Design | [include/crown/planner/residual.hpp](../../../../../include/crown/planner/residual.hpp), [src/planner/residual_machine.hpp](../../../../../src/planner/residual_machine.hpp), [include/crown/planner/search.hpp](../../../../../include/crown/planner/search.hpp) |

## B0020

[Lines 65–68](../../../../../src/planner/residual.cpp#L65); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::size_t ResidualCandidate::height()
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Return the independently computed native height of the candidate tree. |
| inputs / outputs | size_t from P02 CheckedUpper or a validated exact upper. |
| invariants | Uses checked metric; does not trust caller claims or infer a minimum from reduction rounds. |
| ownership | Scalar copy; no borrowing after return. |
| failure | Moved-from handle throws invalid_residual_handle. |
| cost | Constant-time. |
| Design | [include/crown/planner/residual.hpp](../../../../../include/crown/planner/residual.hpp), [src/planner/verify.cpp](../../../../../src/planner/verify.cpp), [include/crown/planner/search.hpp](../../../../../include/crown/planner/search.hpp) |

## B0021

[Lines 69–69](../../../../../src/planner/residual.cpp#L69); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
ResidualOrigin ResidualCandidate::origin()
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Report the last successful construction operation for this tree. |
| inputs / outputs | ResidualOrigin by value. |
| invariants | Later equal-height original proof preserves this construction provenance; it is not an exactness flag. |
| ownership | Scalar copy from immutable data. |
| failure | Moved-from handle rejects via require. |
| cost | Constant-time. |
| Design | [include/crown/planner/residual.hpp](../../../../../include/crown/planner/residual.hpp), [docs/residual_candidates.md](../../../../residual_candidates.md) |

## B0022

[Lines 70–70](../../../../../src/planner/residual.cpp#L70); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
ResidualTrace ResidualCandidate::trace()
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Obtain an owning copy of the verified reduction trace associated with the candidate. |
| inputs / outputs | Returns a ResidualTrace handle. |
| invariants | Shares the same original binding and frozen trace used by candidate construction. |
| ownership | Increments shared ownership; returned trace can outlive the candidate. |
| failure | Moved-from candidate throws; successful handle copy allocates nothing. |
| cost | Constant-time shared-pointer copy. |
| Design | [include/crown/planner/residual.hpp](../../../../../include/crown/planner/residual.hpp), [src/planner/residual_machine.hpp](../../../../../src/planner/residual_machine.hpp) |

## B0023

[Lines 71–72](../../../../../src/planner/residual.cpp#L71); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct ResidualSearch::Impl {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Own the facade state machine, source binding, workers, budgets and published history. |
| inputs / outputs | One shared immutable BindingData, options/ledgers, active worker pointers and distinct trace/candidate/exact artifacts. |
| invariants | original_scope becomes true only after full-query ExactSearch admission. Checked candidate and exact proof remain separate; retained statistics prevent history loss on cancel. |
| ownership | Unique facade owns Impl and workers; immutable payloads are shared with public handles. Workers retain their inputs and budget. |
| failure | Shell/publication allocation failure retains the prior stage; advance contains unexpected exceptions as terminal internal_failure. |
| cost | Several inert shell allocations plus cumulative worker storage; completed workers are retained until owner destruction/cancel, not continuously reclaimed. |
| Design | [docs/residual_candidates.md](../../../../residual_candidates.md), [include/crown/planner/residual.hpp](../../../../../include/crown/planner/residual.hpp), [src/planner/residual_machine.hpp](../../../../../src/planner/residual_machine.hpp), [src/planner/producer_cursor.hpp](../../../../../src/planner/producer_cursor.hpp) |

## B0024

[Lines 73–77](../../../../../src/planner/residual.cpp#L73); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
enum class Stage {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Drive explicit suspension and publication states inside the residual facade. |
| inputs / outputs | Private finite state covering shells, worker steps, immutable publications, exact fallback and terminals. |
| invariants | Only unit() advances semantic states. complete follows required artifact publication; failed/cancelled states cannot resume work. |
| ownership | Value in one exclusive Impl. |
| failure | Invalid states are not public inputs; phase() has a failure fallback for exhaustive mapping. |
| cost | Constant storage and dispatch. |
| Design | [docs/residual_candidates.md](../../../../residual_candidates.md), [include/crown/planner/residual.hpp](../../../../../include/crown/planner/residual.hpp) |

## B0025

[Lines 78–101](../../../../../src/planner/residual.cpp#L78); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L78-L101:sha256:94c3c3e3626e7449b855fd2ca343c7dc7a7bab8da7eb70193a704c2d7a18b97d
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Retain binding, options, construction, ledger, stage, last_stop, exact_stop, failure, revision, own_statistics, retained_statistics, retained_exact, original_scope, trace_was_complete, reduction, checker, reconstruction, original, record, trace_data, checked, candidate_data, exact_optimum, exact_infeasibility in ResidualSearch::Impl across its lifetime. |
| inputs / outputs | These are stored fields for ResidualSearch::Impl, not callable parameters or results; constructors and later methods set or consume them. |
| invariants | The fields preserve the named machine or owner state between calls; counters, cursors, and stored claims remain data until adjacent methods update or validate them. |
| ownership | shared_ptr members retain their pointees through shared ownership; this span does not deep-copy them; unique_ptr members exclusively own their implementation or child-machine objects. Populated exact_optimum and exact_infeasibility optionals contain Verified* handle values; their non-null shared backing pointers retain immutable artifact data. The optional/handle is not merely borrowed evidence. |
| failure | The declarations add no exception path by themselves. Constructing owner/container members or growing them later can fail through the surrounding object-creation or update path. |
| cost | Adds fixed per-instance storage for the listed values and owner/container handles; shared_ptr members retain shared payloads without a deep copy at this declaration; child implementation allocation occurs in its factory or constructor. |
| Design | [src/planner/residual.cpp](../../../../../src/planner/residual.cpp), [docs/residual_candidates.md](../../../../residual_candidates.md), [Refactor.md §5.3](../../../../../Refactor.md) |

## B0026

[Lines 102–104](../../../../../src/planner/residual.cpp#L102); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
  Impl(std::shared_ptr<const cd::BindingData> input, ResidualOptions value)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Initialize an inert residual owner after validated binding admission. |
| inputs / outputs | Binding and copied options become fields; creates ConstructionBudget and residual ledger. |
| invariants | No reduction, exact search or P02 work runs here. |
| ownership | Moves immutable binding ownership and owns a newly allocated shared budget. |
| failure | make_shared may throw before the facade exists. |
| cost | Constant shell work/allocation; input validation/copy happened outside this constructor. |
| Design | [docs/residual_candidates.md](../../../../residual_candidates.md), [include/crown/planner/residual.hpp](../../../../../include/crown/planner/residual.hpp), [src/planner/residual_machine.hpp](../../../../../src/planner/residual_machine.hpp) |

## B0027

[Lines 105–105](../../../../../src/planner/residual.cpp#L105); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
  bool terminal() const noexcept
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Recognize facade states that cannot accept further work or limit changes. |
| inputs / outputs | Boolean for complete, failed or cancelled. |
| invariants | Resource and allocation stops alone are nonterminal. |
| ownership | Reads stage only. |
| failure | Noexcept; no allocation. |
| cost | Constant comparisons. |
| Design | [include/crown/planner/residual.hpp](../../../../../include/crown/planner/residual.hpp), [docs/residual_candidates.md](../../../../residual_candidates.md) |

## B0028

[Lines 106–109](../../../../../src/planner/residual.cpp#L106); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
  ResidualStopReason terminal_reason() const noexcept
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Choose the stable reason for an already terminal owner. |
| inputs / outputs | complete/cancelled are explicit; failed uses retained failure. |
| invariants | Caller invokes only when terminal() is true; active states would fall through to failure. |
| ownership | Scalar result only. |
| failure | Noexcept; no allocation. |
| cost | Constant comparisons. |
| Design | [include/crown/planner/residual.hpp](../../../../../include/crown/planner/residual.hpp) |

## B0029

[Lines 110–110](../../../../../src/planner/residual.cpp#L110); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
  void fail(ResidualStopReason value) noexcept
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Make an irrecoverable residual invariant failure terminal. |
| inputs / outputs | Stores failure reason and changes stage to failed. |
| invariants | Retains already published immutable artifacts for inspection; no feasibility inference is made. |
| ownership | Does not release workers or artifact owners here. |
| failure | Noexcept assignment only. |
| cost | Constant-time. |
| Design | [docs/residual_candidates.md](../../../../residual_candidates.md), [include/crown/planner/residual.hpp](../../../../../include/crown/planner/residual.hpp) |

## B0030

[Lines 111–116](../../../../../src/planner/residual.cpp#L111); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
  ResidualStatistics statistics() const noexcept
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Combine facade, retained cancellation and still-owned worker counters. |
| inputs / outputs | ResidualStatistics snapshot by value. |
| invariants | Cancelled workers are reset after their totals enter retained_statistics, avoiding double counting. Summation saturates. |
| ownership | Copies values and borrows active workers during the call. |
| failure | Noexcept and allocation-free. |
| cost | Fixed number of twelve-field additions; no trace traversal. |
| Design | [include/crown/planner/residual.hpp](../../../../../include/crown/planner/residual.hpp), [src/planner/residual_reduce.cpp](../../../../../src/planner/residual_reduce.cpp), [src/planner/residual_reconstruct.cpp](../../../../../src/planner/residual_reconstruct.cpp) |

## B0031

[Lines 117–121](../../../../../src/planner/residual.cpp#L117); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
  SearchProgress exact_progress() const noexcept
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Report the currently relevant delegated search diagnostics. |
| inputs / outputs | Original exact progress has priority, otherwise reconstruction prefix progress, otherwise retained snapshot. |
| invariants | Scope qualification comes from original_scope; this method does not upgrade a prefix bound. |
| ownership | Copies fixed-size progress from live or retained owner. |
| failure | Noexcept; absent workers yield stored default/history. |
| cost | Constant-time fixed record copy. |
| Design | [docs/residual_candidates.md](../../../../residual_candidates.md), [include/crown/planner/search.hpp](../../../../../include/crown/planner/search.hpp), [src/planner/residual_reconstruct.cpp](../../../../../src/planner/residual_reconstruct.cpp) |

## B0032

[Lines 122–127](../../../../../src/planner/residual.cpp#L122); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
  std::size_t depth() const noexcept
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Read the currently active residual worker depth for the outer ledger. |
| inputs / outputs | Depth from reduction, replay or reconstruction; zero in shells, exact-original stages and terminals. |
| invariants | Delegated exact depth is reported in exact_progress instead of the residual ledger. |
| ownership | Borrows workers; returns size_t. |
| failure | Noexcept; stage/worker pairing is maintained by unit(). |
| cost | Constant dispatch; child depth access is fixed-time. |
| Design | [docs/residual_candidates.md](../../../../residual_candidates.md), [include/crown/planner/residual.hpp](../../../../../include/crown/planner/residual.hpp) |

## B0033

[Lines 128–142](../../../../../src/planner/residual.cpp#L128); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
  ResidualPhase phase() const noexcept
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Map private stages and worker subphases to stable public diagnostics. |
| inputs / outputs | ResidualPhase returned by progress(). |
| invariants | Publication and exact-original administrative stages remain distinct from completion. No proof is inferred from phase. |
| ownership | Scalar read; borrows active worker only where present. |
| failure | Noexcept; exhaustive switch fallback reports failed. |
| cost | Constant dispatch. |
| Design | [include/crown/planner/residual.hpp](../../../../../include/crown/planner/residual.hpp) |

## B0034

[Lines 143–145](../../../../../src/planner/residual.cpp#L143); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
  void record_counter_room(std::uint64_t value) const
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Stop before an authoritative publication/admission statistic would wrap. |
| inputs / outputs | Counter value in; normal return unless at uint64 maximum. |
| invariants | Checked before associated allocation/publication; successful mutation then increments safely. |
| ownership | Borrows scalar input; no state change. |
| failure | Throws Limited(counter_overflow), terminalized by advance. |
| cost | Constant arithmetic check; exception occurs only on exhaustion. |
| Design | [src/planner/residual_machine.hpp](../../../../../src/planner/residual_machine.hpp), [docs/residual_candidates.md](../../../../residual_candidates.md) |

## B0035

[Lines 146–148](../../../../../src/planner/residual.cpp#L146); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L146-L148:sha256:21ebc40e1ee5fdaf4d4204b058705eeef01230ebf6f110b118357d3d6ccf756d
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Use the adjacent note for unit: One retained worker/publication operation. Never upgrade a prefix proof: only a final original P02 tree can publish an upper, and only the separate full-original ExactSearch can publish minimum/infeasibility authority. Confirm behavior against the declaration and implementation; comment text alone does not enforce or prove it. |
| inputs / outputs | This comment has no inputs or outputs. It accompanies unit; use the adjacent declaration and implementation for the actual values and result. |
| invariants | This is static guidance only. The comment cannot alter state or guarantee that its wording holds. |
| ownership | The note owns no storage and changes no lifetime; ownership and borrowing for unit come from its actual types and implementation. |
| failure | Reading the comment has no runtime failure path. Compile or link errors, exceptions, and resource stops belong to the adjacent code. |
| cost | The comment adds no runtime instructions, allocation, clock read, counter debit, or engine hook; only source-text processing is added. |
| Design | [src/planner/residual.cpp](../../../../../src/planner/residual.cpp), [docs/residual_candidates.md](../../../../residual_candidates.md), [Refactor.md §5.3](../../../../../Refactor.md) |

## B0036

[Lines 149–254](../../../../../src/planner/residual.cpp#L149); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
  rd::Step unit()
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Perform one retained facade operation across reduction, replay, reconstruction, publication and exact-original proof. |
| inputs / outputs | Uses current stage/options; returns worker event or stopped/exact reason and advances state when preparation succeeds. |
| invariants | Trace must replay before publication; candidate requires full original P02. Prefix failure requests original search. Original proof contradiction is internal_failure; better exact upper replaces rather than mutates old candidates. |
| ownership | Allocates private workers/payloads then moves them into state; full-query ExactSearch owns copied Catalog/Query. Existing artifact handles keep old immutable payloads. |
| failure | Propagates retryable allocations/Limited to advance; terminalizes invalid traces or internal contradictions. Delegated counter overflow remains terminal, not exact_limit. |
| cost | One worker transition or shell/publication per call; exact gets one work unit. Original admission copies/validates full input; record ceilings charge logical objects, not all delegated allocations. |
| Design | [docs/residual_candidates.md](../../../../residual_candidates.md), [src/planner/residual_machine.hpp](../../../../../src/planner/residual_machine.hpp), [src/planner/residual_reconstruct.cpp](../../../../../src/planner/residual_reconstruct.cpp), [src/planner/residual_reduce.cpp](../../../../../src/planner/residual_reduce.cpp), [src/planner/residual_trace.cpp](../../../../../src/planner/residual_trace.cpp), [src/planner/search_session.cpp](../../../../../src/planner/search_session.cpp), [src/planner/verify.cpp](../../../../../src/planner/verify.cpp) |

## B0037

[Lines 255–255](../../../../../src/planner/residual.cpp#L255); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L255-L255:sha256:aa1d1a63390229c798347e83a0405441c9400035284ad168c1bf6cdf1d70a370
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | This block close the current class or struct and its enclosing lexical scope. |
| inputs / outputs | A scope delimiter has no call inputs or outputs; it controls which following declarations belong to the C++ namespace, class, or helper scope. |
| invariants | The braces set lexical visibility and type boundaries only. Any attached note is documentation and does not enforce behavior. |
| ownership | The delimiter and note acquire, release, or transfer no runtime object. Member lifetimes come from the enclosed type definitions. |
| failure | An unmatched or misplaced brace fails compilation; this block adds no runtime exception or resource-stop path. |
| cost | No runtime work or allocation is added. The compiler parses the scope boundary and comment. |
| Design | [src/planner/residual.cpp](../../../../../src/planner/residual.cpp), [docs/residual_candidates.md](../../../../residual_candidates.md), [Refactor.md §5.3](../../../../../Refactor.md) |

## B0038

[Lines 256–256](../../../../../src/planner/residual.cpp#L256); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
ResidualSearch::ResidualSearch(std::unique_ptr<Impl>
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Adopt a prepared exclusive residual implementation. |
| inputs / outputs | Private constructor takes unique_ptr&lt;Impl&gt;. |
| invariants | Only create constructs a new admitted owner. |
| ownership | Moves unique ownership with no extra implementation allocation. |
| failure | Noexcept; construction does not perform search or validation. |
| cost | Constant pointer move. |
| Design | [include/crown/planner/residual.hpp](../../../../../include/crown/planner/residual.hpp) |

## B0039

[Lines 257–261](../../../../../src/planner/residual.cpp#L257); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
ResidualSearch::~ResidualSearch() = default;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Implement unique ownership teardown and constant-time facade moves. |
| inputs / outputs | Default destructor, move constructor and move assignment. |
| invariants | Moved-from owner has no data_; published shared artifacts retain their payloads. Move assignment first destroys any existing target state. |
| ownership | Transfers unique Impl; destruction recursively releases worker/payload owners according to their cancellation destructors. |
| failure | Declared moves are noexcept; destructors rely on nonthrowing engine cancellation. |
| cost | Move construction is constant; destruction/move-assignment cleanup is proportional to retained data and active frames, outside advance grants. |
| Design | [include/crown/planner/residual.hpp](../../../../../include/crown/planner/residual.hpp), [src/planner/residual_machine.hpp](../../../../../src/planner/residual_machine.hpp), [src/planner/producer_cursor.hpp](../../../../../src/planner/producer_cursor.hpp), [docs/residual_candidates.md](../../../../residual_candidates.md) |

## B0040

[Lines 262–270](../../../../../src/planner/residual.cpp#L262); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
ResidualSearch ResidualSearch::create(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Admit and own a validated original Catalog/Query without running search. |
| inputs / outputs | Catalog/Query by value and options; returns move-only ResidualSearch. |
| invariants | Mode and all active-time ceilings validate before BindingData and Impl publication. Query occurrence identity/contradiction are preserved. |
| ownership | Moves validated values into immutable shared binding; caller mutations cannot affect the owner. |
| failure | Unknown mode/negative time or invalid input throw; allocations can throw. No incomplete search facade is returned. |
| cost | Full input parameter copy/move and validate scans plus binding, Impl and budget allocations; outside work/time/content metering. |
| Design | [include/crown/planner/residual.hpp](../../../../../include/crown/planner/residual.hpp), [docs/residual_candidates.md](../../../../residual_candidates.md), [include/crown/planner/search.hpp](../../../../../include/crown/planner/search.hpp) |

## B0041

[Lines 271–273](../../../../../src/planner/residual.cpp#L271); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L271-L273:sha256:b51765e2c683186c8508d93ccbf51ba72d03b8689bb6d9e8aebfc0236e709269
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Use the adjacent note for ResidualSearch: Keep limit/bad_alloc catches: pending closures remain retryable. The final catch protects this noexcept boundary and terminalizes internal invariant failures; stop reporting is fixed-size and allocates no error message. Confirm behavior against the declaration and implementation; comment text alone does not enforce or prove it. |
| inputs / outputs | This comment has no inputs or outputs. It accompanies ResidualSearch; use the adjacent declaration and implementation for the actual values and result. |
| invariants | This is static guidance only. The comment cannot alter state or guarantee that its wording holds. |
| ownership | The note owns no storage and changes no lifetime; ownership and borrowing for ResidualSearch come from its actual types and implementation. |
| failure | Reading the comment has no runtime failure path. Compile or link errors, exceptions, and resource stops belong to the adjacent code. |
| cost | The comment adds no runtime instructions, allocation, clock read, counter debit, or engine hook; only source-text processing is added. |
| Design | [src/planner/residual.cpp](../../../../../src/planner/residual.cpp), [docs/residual_candidates.md](../../../../residual_candidates.md), [Refactor.md §5.3](../../../../../Refactor.md) |

## B0042

[Lines 274–323](../../../../../src/planner/residual.cpp#L274); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
ResidualAdvance ResidualSearch::advance(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Spend a bounded grant on saved operations and report a fixed-size stop without throwing. |
| inputs / outputs | WorkQuantum in; ResidualAdvance with current progress and separate delegated reason out. |
| invariants | Moved-from/negative/zero grants return before work. Nonzero attempts are charged even on failure. Pending operation remains retryable after allocation/Limited stops; counter exhaustion and unexpected exceptions are terminal. |
| ownership | Mutates one exclusive owner; ActiveMeter samples only this call, while artifacts remain immutable. |
| failure | Retain Limited and bad_alloc catches for resumable resource semantics; catch-all protects noexcept from internal failures. Stop reporting allocates nothing. |
| cost | At most quantum.work outer attempts, cooperative time checks each loop. A delegated admission, container operation or cleanup can have variable cost between checkpoints. |
| Design | [docs/residual_candidates.md](../../../../residual_candidates.md), [docs/planner_continuations.md](../../../../planner_continuations.md), [src/planner/continuation_budget.hpp](../../../../../src/planner/continuation_budget.hpp), [src/planner/producer_cursor.hpp](../../../../../src/planner/producer_cursor.hpp), [src/planner/residual_machine.hpp](../../../../../src/planner/residual_machine.hpp) |

## B0043

[Lines 324–325](../../../../../src/planner/residual.cpp#L324); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L324-L325:sha256:af85f8a29333ea136614bcad14adff90aeffa11b6355e783a73886d6e0635b6d
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Use the adjacent note for ResidualSearch: Report original bounds only; prefix exact diagnostics never raise lower. A completed trace and a checked tree are separate publication milestones. Confirm behavior against the declaration and implementation; comment text alone does not enforce or prove it. |
| inputs / outputs | This comment has no inputs or outputs. It accompanies ResidualSearch; use the adjacent declaration and implementation for the actual values and result. |
| invariants | This is static guidance only. The comment cannot alter state or guarantee that its wording holds. |
| ownership | The note owns no storage and changes no lifetime; ownership and borrowing for ResidualSearch come from its actual types and implementation. |
| failure | Reading the comment has no runtime failure path. Compile or link errors, exceptions, and resource stops belong to the adjacent code. |
| cost | The comment adds no runtime instructions, allocation, clock read, counter debit, or engine hook; only source-text processing is added. |
| Design | [src/planner/residual.cpp](../../../../../src/planner/residual.cpp), [docs/residual_candidates.md](../../../../residual_candidates.md), [Refactor.md §5.3](../../../../../Refactor.md) |

## B0044

[Lines 326–351](../../../../../src/planner/residual.cpp#L326); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
ResidualProgress ResidualSearch::progress()
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Assemble honest original-query bounds and scope-qualified diagnostic history. |
| inputs / outputs | Fixed-size snapshot; moved-from gives failed/moved_from state. |
| invariants | Universal lower is 0 for empty body and 1 otherwise until completed original exact proof. Upper appears only after candidate publication. Prefix search/round counts never raise original lower. |
| ownership | Copies scalar state/statistics/progress; does not export tree/proof ownership. |
| failure | Noexcept; all consulted methods allocate nothing. Cancellation remains a phase rather than inventing infeasibility. |
| cost | Constant worker dispatch and fixed record copies. |
| Design | [docs/residual_candidates.md](../../../../residual_candidates.md), [include/crown/planner/residual.hpp](../../../../../include/crown/planner/residual.hpp), [include/crown/planner/search.hpp](../../../../../include/crown/planner/search.hpp) |

## B0045

[Lines 352–355](../../../../../src/planner/residual.cpp#L352); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
ResidualOptions ResidualSearch::options()
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Read the current admitted policy and extended ceilings. |
| inputs / outputs | ResidualOptions returned by value. |
| invariants | Mode is fixed; limits include all accepted raises. |
| ownership | Fixed-size value copy independent of owner afterwards. |
| failure | Moved-from facade throws invalid_residual_handle. |
| cost | Constant-time success with no allocation. |
| Design | [include/crown/planner/residual.hpp](../../../../../include/crown/planner/residual.hpp) |

## B0046

[Lines 356–359](../../../../../src/planner/residual.cpp#L356); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
const Catalog& ResidualSearch::catalog()
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Read the full original catalog owned by the search. |
| inputs / outputs | Const Catalog&. |
| invariants | Binding remains immutable through all limits, pauses and fallback searches. |
| ownership | Borrowed reference invalid after last binding owner release; keep facade or artifact alive. |
| failure | Moved-from facade throws invalid_residual_handle. |
| cost | Constant-time no-copy access. |
| Design | [include/crown/planner/residual.hpp](../../../../../include/crown/planner/residual.hpp), [src/planner/residual_machine.hpp](../../../../../src/planner/residual_machine.hpp) |

## B0047

[Lines 360–363](../../../../../src/planner/residual.cpp#L360); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
const Query& ResidualSearch::query()
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Read the original admitted query rather than a transient residual view. |
| inputs / outputs | Const Query&. |
| invariants | Resume does not accept a replacement binding. |
| ownership | Borrowed reference into immutable shared BindingData. |
| failure | Moved-from facade throws invalid_residual_handle. |
| cost | Constant-time no-copy access. |
| Design | [include/crown/planner/residual.hpp](../../../../../include/crown/planner/residual.hpp), [docs/residual_candidates.md](../../../../residual_candidates.md) |

## B0048

[Lines 364–367](../../../../../src/planner/residual.cpp#L364); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::optional<ResidualTrace> ResidualSearch::trace()
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Export trace ownership only after independent replay/publication. |
| inputs / outputs | Optional ResidualTrace; empty before publication or after facade move. |
| invariants | trace_was_complete alone is insufficient; trace_data must exist. Published trace remains available after cancellation. |
| ownership | Returned handle shares immutable binding/record ownership without copying content. |
| failure | Noexcept; empty is ordinary unavailable status. |
| cost | Constant-time shared-pointer copy, no allocation. |
| Design | [include/crown/planner/residual.hpp](../../../../../include/crown/planner/residual.hpp), [src/planner/residual_trace.cpp](../../../../../src/planner/residual_trace.cpp), [docs/residual_candidates.md](../../../../residual_candidates.md) |

## B0049

[Lines 368–371](../../../../../src/planner/residual.cpp#L368); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::optional<ResidualCandidate> ResidualSearch::candidate()
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Export the latest published original-query upper witness. |
| inputs / outputs | Optional ResidualCandidate; empty before any full checked tree is published. |
| invariants | Reconstruction/prefix private trees never escape. Old handles retain earlier checked bounds after exact improvement; cancellation preserves published candidates. |
| ownership | Shared immutable payload copy independent of facade lifetime. |
| failure | Noexcept; unavailable/moved-from yields empty. |
| cost | Constant-time handle copy, no allocation. |
| Design | [include/crown/planner/residual.hpp](../../../../../include/crown/planner/residual.hpp), [docs/residual_candidates.md](../../../../residual_candidates.md), [src/planner/residual_reconstruct.cpp](../../../../../src/planner/residual_reconstruct.cpp) |

## B0050

[Lines 372–375](../../../../../src/planner/residual.cpp#L372); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::optional<VerifiedOptimum> ResidualSearch::exact_original()
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Expose completed original-query minimum authority. |
| inputs / outputs | Optional VerifiedOptimum only when facade stage is complete. |
| invariants | Withholds proof during original completion/publication staging and after failure/cancel. No prefix optimum is returned. |
| ownership | Returned P06 handle owns original binding, checked upper and lower proof. |
| failure | Noexcept; absence is not infeasibility. |
| cost | Constant-time optional/shared-handle copy. |
| Design | [include/crown/planner/residual.hpp](../../../../../include/crown/planner/residual.hpp), [docs/residual_candidates.md](../../../../residual_candidates.md), [include/crown/planner/search.hpp](../../../../../include/crown/planner/search.hpp) |

## B0051

[Lines 376–379](../../../../../src/planner/residual.cpp#L376); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::optional<VerifiedInfeasible> ResidualSearch::infeasibility()
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Expose completed original-query infeasibility authority. |
| inputs / outputs | Optional VerifiedInfeasible only after facade complete. |
| invariants | Partial-query infeasibility and resource stops never populate this accessor. |
| ownership | Returned P06 handle owns full original binding and independent root proof. |
| failure | Noexcept; absent while unfinished/failed/moved-from or feasible. |
| cost | Constant-time handle copy. |
| Design | [include/crown/planner/residual.hpp](../../../../../include/crown/planner/residual.hpp), [docs/residual_candidates.md](../../../../residual_candidates.md), [include/crown/planner/search.hpp](../../../../../include/crown/planner/search.hpp) |

## B0052

[Lines 380–399](../../../../../src/planner/residual.cpp#L380); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
LimitChange ResidualSearch::raise_limits(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Apply a monotone limit extension without replacing the retained search. |
| inputs / outputs | New ResidualLimits in; LimitChange result. |
| invariants | Reject terminal owners, invalid times, tightened ceilings or values below consumption. Delegate exact extension before updating outer options/budget/ledger and revision. |
| ownership | Mutates exclusive owner only; published payloads and binding stay unchanged. |
| failure | Noexcept; invalid revision exhaustion rejects. Inner rejection returns before outer mutation; no allocation. |
| cost | Fixed-size checks plus at most one active ExactSearch limit update. |
| Design | [include/crown/planner/residual.hpp](../../../../../include/crown/planner/residual.hpp), [docs/residual_candidates.md](../../../../residual_candidates.md), [src/planner/continuation_budget.hpp](../../../../../src/planner/continuation_budget.hpp), [src/planner/residual_reconstruct.cpp](../../../../../src/planner/residual_reconstruct.cpp), [include/crown/planner/search.hpp](../../../../../include/crown/planner/search.hpp) |

## B0053

[Lines 400–401](../../../../../src/planner/residual.cpp#L400); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L400-L401:sha256:7f4e7e05c539368ad85d835803e97e6530b88946f0a869c110d177a6f166e6aa
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Use the adjacent note for ResidualSearch: Snapshot worker history before release. Published immutable handles keep their data; cleanup may traverse retained state and is outside work grants. Confirm behavior against the declaration and implementation; comment text alone does not enforce or prove it. |
| inputs / outputs | This comment has no inputs or outputs. It accompanies ResidualSearch; use the adjacent declaration and implementation for the actual values and result. |
| invariants | This is static guidance only. The comment cannot alter state or guarantee that its wording holds. |
| ownership | The note owns no storage and changes no lifetime; ownership and borrowing for ResidualSearch come from its actual types and implementation. |
| failure | Reading the comment has no runtime failure path. Compile or link errors, exceptions, and resource stops belong to the adjacent code. |
| cost | The comment adds no runtime instructions, allocation, clock read, counter debit, or engine hook; only source-text processing is added. |
| Design | [src/planner/residual.cpp](../../../../../src/planner/residual.cpp), [docs/residual_candidates.md](../../../../residual_candidates.md), [Refactor.md §5.3](../../../../../Refactor.md) |

## B0054

[Lines 402–417](../../../../../src/planner/residual.cpp#L402); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void ResidualSearch::cancel()
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Release unfinished workers while retaining published artifacts and diagnostic history. |
| inputs / outputs | No arguments; terminal cancelled phase for active owners. |
| invariants | Completed/failed/cancelled or moved-from calls are inert. Statistics/exact diagnostics are snapshotted before workers reset; depth becomes zero. |
| ownership | Releases private workers/unfinished trees/proofs, retains immutable trace_data/candidate_data and original binding. Existing external handles survive. |
| failure | Noexcept; leaf-first coroutine teardown avoids recursive live-frame ownership. No feasibility result is invented. |
| cost | Worker and retained scratch destruction can be size-dependent; cancellation is outside advance accounting. |
| Design | [include/crown/planner/residual.hpp](../../../../../include/crown/planner/residual.hpp), [docs/residual_candidates.md](../../../../residual_candidates.md), [src/planner/producer_cursor.hpp](../../../../../src/planner/producer_cursor.hpp), [docs/planner_continuations.md](../../../../planner_continuations.md) |

## B0055

[Lines 418–418](../../../../../src/planner/residual.cpp#L418); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L418-L418:sha256:4694e0f1e6f869fb33efbef9837cf0d20c8f194dc3c9f2b5be909714a0f5c690
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | This block close namespace crown::planner. |
| inputs / outputs | A scope delimiter has no call inputs or outputs; it controls which following declarations belong to the C++ namespace, class, or helper scope. |
| invariants | The braces set lexical visibility and type boundaries only. Any attached note is documentation and does not enforce behavior. |
| ownership | The delimiter and note acquire, release, or transfer no runtime object. Member lifetimes come from the enclosed type definitions. |
| failure | An unmatched or misplaced brace fails compilation; this block adds no runtime exception or resource-stop path. |
| cost | No runtime work or allocation is added. The compiler parses the scope boundary and comment. |
| Design | [src/planner/residual.cpp](../../../../../src/planner/residual.cpp), [docs/residual_candidates.md](../../../../residual_candidates.md), [Refactor.md §5.3](../../../../../Refactor.md) |
