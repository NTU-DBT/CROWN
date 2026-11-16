# `src/observability/query_explain.cpp` — block usage map

[Source](../../../../../src/observability/query_explain.cpp) · [Source index](../../../README.md) · [Subsystem contracts](../../../subsystem_contracts.md) · [Reviewed primitives](../../../primitives.md)

Capture bounded distributions, workload counters, owner memory and explain observations without mislabeling partial information as exact.

Snapshot SHA-256: `b3614c023242b061785c089d9a48f94a5598c451a9b830b0eb7defe60df02865`. 94 lines partitioned into 29 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [statistics](../../../subsystem_contracts.md#statistics). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/statistics.md](../../../../statistics.md), [docs/observability.md](../../../../observability.md), [docs/memory_reports.md](../../../../memory_reports.md), [docs/ranking_evaluation.md](../../../../ranking_evaluation.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–6](../../../../../src/observability/query_explain.cpp#L1) | Imports dependencies; declares namespace scope; declares aliases. | source comment (unverified): // Shared typed evidence keeps its original scope; capture creates no new proof. · [reviewed contract](#b0001) |
| [B0002 · 7–20](../../../../../src/observability/query_explain.cpp#L7) | Type/record definition: struct QueryExplanation::Data | source comment (unverified): // Shared typed evidence keeps its original scope; capture creates no new proof. · [reviewed contract](#b0002) |
| [B0003 · 21–21](../../../../../src/observability/query_explain.cpp#L21) | Callable definition: QueryExplanation::QueryExplanation(std::shared_ptr&lt;const Data&gt; value):data_(std::move(value)) | calls data_, std::move · [reviewed contract](#b0003) |
| [B0004 · 22–25](../../../../../src/observability/query_explain.cpp#L22) | Callable definition: const QueryExplanation::Data& QueryExplanation::data() const | calls Error; returns *data_ · [reviewed contract](#b0004) |
| [B0005 · 26–26](../../../../../src/observability/query_explain.cpp#L26) | Explanatory comments or spacing. | source comment (unverified): // Normalize existing handles; these count checks do not cap all retained bytes. · [reviewed contract](#b0005) |
| [B0006 · 27–38](../../../../../src/observability/query_explain.cpp#L27) | Callable definition: QueryExplanation QueryExplanation::finish(std::shared_ptr&lt;Data&gt; d,QueryExplainLimits limits) | calls valid, Error, optimum, infeasibility; returns QueryExplanation(std::move(d)); source comment (unverified): // Normalize existing handles; these count checks do not cap all retained bytes. · [reviewed contract](#b0006) |
| [B0007 · 39–39](../../../../../src/observability/query_explain.cpp#L39) | Explanatory comments or spacing. | source comment (unverified): // Exclusive producer read: fixed metadata/handle copies, no search advancement. · [reviewed contract](#b0007) |
| [B0008 · 40–45](../../../../../src/observability/query_explain.cpp#L40) | Callable definition: QueryExplanation QueryExplanation::capture(const ExactSearch& owner,QueryExplainLimits limits) | calls binding, progress, policy, limits; returns finish(std::move(d),limits); growth make_shared; source comment (unverified): // Exclusive producer read: fixed metadata/handle copies, no search advancement. · [reviewed contract](#b0008) |
| [B0009 · 46–50](../../../../../src/observability/query_explain.cpp#L46) | Callable definition: QueryExplanation QueryExplanation::capture(const CertificateReplay& owner,QueryExplainLimits limits) | calls binding, progress, limits, checked; returns finish(std::move(d),limits); growth make_shared · [reviewed contract](#b0009) |
| [B0010 · 51–53](../../../../../src/observability/query_explain.cpp#L51) | Callable definition: QueryExplanation QueryExplanation::from(ValidatedIncumbent value,QueryExplainLimits limits) | calls binding, std::move, finish; returns finish(std::move(d),limits); growth make_shared · [reviewed contract](#b0010) |
| [B0011 · 54–56](../../../../../src/observability/query_explain.cpp#L54) | Callable definition: QueryExplanation QueryExplanation::from(VerifiedOptimum value,QueryExplainLimits limits) | calls binding, std::move, finish; returns finish(std::move(d),limits); growth make_shared · [reviewed contract](#b0011) |
| [B0012 · 57–59](../../../../../src/observability/query_explain.cpp#L57) | Callable definition: QueryExplanation QueryExplanation::from(VerifiedInfeasible value,QueryExplainLimits limits) | calls binding, std::move, finish; returns finish(std::move(d),limits); growth make_shared · [reviewed contract](#b0012) |
| [B0013 · 60–62](../../../../../src/observability/query_explain.cpp#L60) | Callable definition: QueryExplanation QueryExplanation::from(CheckedCertificate value,QueryExplainLimits limits) | calls binding, std::move, finish; returns finish(std::move(d),limits); growth make_shared · [reviewed contract](#b0013) |
| [B0014 · 63–63](../../../../../src/observability/query_explain.cpp#L63) | Callable definition: const SearchBinding& QueryExplanation::binding() const | calls data; returns data().binding · [reviewed contract](#b0014) |
| [B0015 · 64–64](../../../../../src/observability/query_explain.cpp#L64) | Callable definition: QueryExplainSource QueryExplanation::source() const | calls data; returns data().source · [reviewed contract](#b0015) |
| [B0016 · 65–72](../../../../../src/observability/query_explain.cpp#L65) | Callable definition: QueryHeightStatus QueryExplanation::height_status() const | calls data; returns QueryHeightStatus::verified_optimum; QueryHeightStatus::verified_infeasible · [reviewed contract](#b0016) |
| [B0017 · 73–77](../../../../../src/observability/query_explain.cpp#L73) | Callable definition: std::optional&lt;std::size_t&gt; QueryExplanation::lower() const | calls data, height, query, empty; returns {}; d.optimum-&gt;height(); source comment (unverified): // P06's universal bound, not structural recognition or producer advancement. · [reviewed contract](#b0017) |
| [B0018 · 78–81](../../../../../src/observability/query_explain.cpp#L78) | Callable definition: std::optional&lt;std::size_t&gt; QueryExplanation::upper() const | calls data, height; returns d.optimum-&gt;height(); d.witness-&gt;height() · [reviewed contract](#b0018) |
| [B0019 · 82–82](../../../../../src/observability/query_explain.cpp#L82) | Callable definition: const std::optional&lt;SearchProgress&gt;& QueryExplanation::search_progress() const | calls data; returns data().search · [reviewed contract](#b0019) |
| [B0020 · 83–83](../../../../../src/observability/query_explain.cpp#L83) | Callable definition: const std::optional&lt;ReplayProgress&gt;& QueryExplanation::replay_progress() const | calls data; returns data().replay · [reviewed contract](#b0020) |
| [B0021 · 84–84](../../../../../src/observability/query_explain.cpp#L84) | Callable definition: const std::optional&lt;SearchPolicy&gt;& QueryExplanation::policy() const | calls data; returns data().policy · [reviewed contract](#b0021) |
| [B0022 · 85–85](../../../../../src/observability/query_explain.cpp#L85) | Callable definition: const std::optional&lt;ContinuationLimits&gt;& QueryExplanation::search_limits() const | calls data; returns data().search_limits · [reviewed contract](#b0022) |
| [B0023 · 86–86](../../../../../src/observability/query_explain.cpp#L86) | Callable definition: const std::optional&lt;ReplayOptions&gt;& QueryExplanation::replay_limits() const | calls data; returns data().replay_limits · [reviewed contract](#b0023) |
| [B0024 · 87–87](../../../../../src/observability/query_explain.cpp#L87) | Callable definition: const std::optional&lt;ValidatedIncumbent&gt;& QueryExplanation::witness() const | calls data; returns data().witness · [reviewed contract](#b0024) |
| [B0025 · 88–88](../../../../../src/observability/query_explain.cpp#L88) | Callable definition: const std::optional&lt;VerifiedOptimum&gt;& QueryExplanation::optimum() const | calls data; returns data().optimum · [reviewed contract](#b0025) |
| [B0026 · 89–89](../../../../../src/observability/query_explain.cpp#L89) | Callable definition: const std::optional&lt;VerifiedInfeasible&gt;& QueryExplanation::infeasibility() const | calls data; returns data().infeasible · [reviewed contract](#b0026) |
| [B0027 · 90–90](../../../../../src/observability/query_explain.cpp#L90) | Callable definition: const std::optional&lt;CheckedCertificate&gt;& QueryExplanation::checked_certificate() const | calls data; returns data().checked · [reviewed contract](#b0027) |
| [B0028 · 91–93](../../../../../src/observability/query_explain.cpp#L91) | Callable definition: const HeightCertificate* QueryExplanation::certificate() const | calls data, certificate; returns d.optimum?&d.optimum-&gt;certificate():d.infeasible?&d.infeasible-&gt;certificate():nullptr · [reviewed contract](#b0028) |
| [B0029 · 94–94](../../../../../src/observability/query_explain.cpp#L94) | Closes surrounding scope/type. | source comment (unverified): // namespace crown::observability · [reviewed contract](#b0029) |

## B0001

[Lines 1–6](../../../../../src/observability/query_explain.cpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L1-L6:sha256:2d6d3f168b8fc326abf737bf112e3b94e012553d31f2cd8ccf6c8e19c16165a0
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Imports compile-time dependencies (crown/observability/query_explain.hpp, crown/api/error.hpp, utility) and opens crown::observability scope for the declarations or definitions that follow. Embedded source note records intended usage: Shared typed evidence keeps its original scope; capture creates no new proof. Treat that prose as guidance, not as independently verified executable behavior. |
| inputs / outputs | No runtime inputs/outputs are declared by the import/scope lines themselves. |
| invariants | The listed headers and namespace membership determine compile-time name availability; any API behavior belongs to the declarations/definitions that follow. |
| ownership | No object ownership is created by the imports or namespace tokens. |
| failure | No runtime failure path. Missing/incompatible dependencies or a violated compile-time constraint fail translation/linking. |
| cost | Compile/preprocessor work only; no new per-operation runtime overhead. |
| Design | [src/observability/query_explain.cpp](../../../../../src/observability/query_explain.cpp), [docs/code_specs/files/src/observability/query_explain.cpp.md](query_explain.cpp.md), [docs/observability.md](../../../../observability.md), [docs/statistics.md](../../../../statistics.md) |

## B0002

[Lines 7–20](../../../../../src/observability/query_explain.cpp#L7); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct QueryExplanation::Data
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Own one immutable query explanation envelope with producer-scoped typed evidence. |
| inputs / outputs | Data stores SearchBinding/source and optional search/replay progress, policy/limits, checked upper, optimum/infeasibility and checked-certificate handles; constructor moves binding and records source. |
| invariants | Only private capture/from factories populate it; no public editable progress/tree/flag/OracleResult constructor. Handle sharing retains existing exact binding/evidence rather than independently proving it. |
| ownership | Report Data owns fixed progress/options and shared immutable typed handles. Retained binding/tree/proof graphs survive producer destruction; no reference to the mutable producer or its execution machine is stored. |
| failure | Moved-from producer/typed-handle or report access Error and allocation failures propagate. No advance/replay/recognition or producer mutation occurs; private report preparation releases on failure. |
| cost | Fixed-size Data; one ordinary make_shared allocation at each public capture/from. Shared references retain potentially large original immutable models/proofs; report limits are count checks, not a total-memory cap. |
| Design | [include/crown/observability/query_explain.hpp](../../../../../include/crown/observability/query_explain.hpp), [docs/observability.md §Reports, ownership, and committed gauges](../../../../observability.md), [include/crown/planner/search.hpp](../../../../../include/crown/planner/search.hpp), [src/planner/search_session.cpp](../../../../../src/planner/search_session.cpp), [docs/planner_continuations.md §Authority and policies](../../../../planner_continuations.md), [src/planner/continuation_machine.hpp](../../../../../src/planner/continuation_machine.hpp), [docs/planner_continuations.md §Lifetime and output](../../../../planner_continuations.md) |

## B0003

[Lines 21–21](../../../../../src/observability/query_explain.cpp#L21); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
QueryExplanation::QueryExplanation(std::shared_ptr<const Data> value):data_(std::move(value))
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Publish a privately prepared immutable Data owner. |
| inputs / outputs | Moves shared_ptr&lt;const Data&gt; into QueryExplanation; called only by finish after its checks. |
| invariants | No implicit public constructor accepts arbitrary Data or claims. Moving an explanation can empty the source, which accessors detect. |
| ownership | Report Data owns fixed progress/options and shared immutable typed handles. Retained binding/tree/proof graphs survive producer destruction; no reference to the mutable producer or its execution machine is stored. |
| failure | No local validation or handler; private caller supplies validated nonnull Data. |
| cost | Fixed shared-pointer move, no deep model/tree/proof copy or new allocation here. |
| Design | [include/crown/observability/query_explain.hpp](../../../../../include/crown/observability/query_explain.hpp), [docs/observability.md §Reports, ownership, and committed gauges](../../../../observability.md), [src/planner/continuation_machine.hpp](../../../../../src/planner/continuation_machine.hpp), [docs/planner_continuations.md §Lifetime and output](../../../../planner_continuations.md) |

## B0004

[Lines 22–25](../../../../../src/observability/query_explain.cpp#L22); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
const QueryExplanation::Data& QueryExplanation::data() const
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Require a live explanation envelope before access. |
| inputs / outputs | Returns const Data& or throws invalid_query_explanation for moved-from/empty data_. |
| invariants | Does not refresh producer progress, compare bindings or manufacture evidence; all report reads stay at captured state. |
| ownership | Returned reference borrows report Data; retain a live copy sharing that Data while using it. |
| failure | Error(invalid_query_explanation) on empty report; allocation failure can supersede diagnostic construction. |
| cost | Fixed pointer check/reference access; failure-only Error diagnostic can allocate. |
| Design | [include/crown/observability/query_explain.hpp](../../../../../include/crown/observability/query_explain.hpp), [docs/observability.md §Reports, ownership, and committed gauges](../../../../observability.md) |

## B0005

[Lines 26–26](../../../../../src/observability/query_explain.cpp#L26); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L26-L26:sha256:68f5c01a27a5d03cf1a5df68f593a485fc085377fab13d4126a92f0e96d02234
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Design note for adjacent code: Normalize existing handles; these count checks do not cap all retained bytes. This is caller guidance recorded as prose, not an executable result. |
| inputs / outputs | No runtime interface is implemented by these comment-only lines. They sit at src/observability/query_explain.cpp lines 24-28; the surrounding declaration/body defines its own inputs and outputs. |
| invariants | The words record the intended use boundary only. They do not add a guard, proof, capability, transaction, durability guarantee, or account charge; verify behavior in the referenced implementation. |
| ownership | Comment text owns no data. Object lifetimes, borrows, and account attribution remain those of the adjacent source objects and their constructors. |
| failure | No failure path is implemented here. Any mentioned failure or recovery rule belongs to the adjacent operation and its existing error carrier. |
| cost | No runtime work is performed by these lines; any cost/bound in the note is not certified by this comment-only card. |
| Design | [src/observability/query_explain.cpp](../../../../../src/observability/query_explain.cpp), [docs/code_specs/files/src/observability/query_explain.cpp.md](query_explain.cpp.md), [docs/observability.md](../../../../observability.md), [docs/statistics.md](../../../../statistics.md) |

## B0006

[Lines 27–38](../../../../../src/observability/query_explain.cpp#L27); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
QueryExplanation QueryExplanation::finish(std::shared_ptr<Data> d,QueryExplainLimits limits)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Normalize existing typed evidence and enforce report count ceilings. |
| inputs / outputs | Requires valid original SearchBinding, extracts optimum/infeasibility from checked certificate, derives witness from optimum, then checks witness/proof-tree node counts and proof lower-bound entry count. |
| invariants | No independent replay or structural recognition. Private factories supply mutually bound genuine handles; optimum witness takes precedence. Caps do not bound all occurrence lists, text lengths or retained bytes, and Data allocation already happened before these checks. |
| ownership | Report Data owns fixed progress/options and shared immutable typed handles. Retained binding/tree/proof graphs survive producer destruction; no reference to the mutable producer or its execution machine is stored. |
| failure | Error on invalid binding or resource_limit after private report allocation; producer and already published evidence stay unchanged. |
| cost | Fixed optional/shared-handle operations and vector::size reads, no tree/certificate enumeration or deep copy. Final owner publication shares retained graphs. |
| Design | [include/crown/observability/query_explain.hpp](../../../../../include/crown/observability/query_explain.hpp), [docs/observability.md §Reports, ownership, and committed gauges](../../../../observability.md), [include/crown/planner/search.hpp](../../../../../include/crown/planner/search.hpp), [src/planner/search_session.cpp](../../../../../src/planner/search_session.cpp), [docs/planner_continuations.md §Authority and policies](../../../../planner_continuations.md), [src/planner/continuation_machine.hpp](../../../../../src/planner/continuation_machine.hpp), [docs/planner_continuations.md §Lifetime and output](../../../../planner_continuations.md) |

## B0007

[Lines 39–39](../../../../../src/observability/query_explain.cpp#L39); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L39-L39:sha256:d3e2333e9ece8462e753f0d1940a32326321acff602e288f6474cc8e2dd4aa8d
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Design note for adjacent code: Exclusive producer read: fixed metadata/handle copies, no search advancement. This is caller guidance recorded as prose, not an executable result. |
| inputs / outputs | No runtime interface is implemented by these comment-only lines. They sit at src/observability/query_explain.cpp lines 37-41; the surrounding declaration/body defines its own inputs and outputs. |
| invariants | The words record the intended use boundary only. They do not add a guard, proof, capability, transaction, durability guarantee, or account charge; verify behavior in the referenced implementation. |
| ownership | Comment text owns no data. Object lifetimes, borrows, and account attribution remain those of the adjacent source objects and their constructors. |
| failure | No failure path is implemented here. Any mentioned failure or recovery rule belongs to the adjacent operation and its existing error carrier. |
| cost | No runtime work is performed by these lines; any cost/bound in the note is not certified by this comment-only card. |
| Design | [src/observability/query_explain.cpp](../../../../../src/observability/query_explain.cpp), [docs/code_specs/files/src/observability/query_explain.cpp.md](query_explain.cpp.md), [docs/observability.md](../../../../observability.md), [docs/statistics.md](../../../../statistics.md) |

## B0008

[Lines 40–45](../../../../../src/observability/query_explain.cpp#L40); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
QueryExplanation QueryExplanation::capture(const ExactSearch& owner,QueryExplainLimits limits)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Capture exact-search progress and currently published typed results. |
| inputs / outputs | Actual ExactSearch supplies binding/progress/policy/limits, optional best-found upper and completed optimum/infeasibility into a new report. |
| invariants | Requires the producer exclusive caller discipline. Strict policy can expose numeric checked upper while withholding witness; completed optimum supplies its typed upper during finish. No advance or proof work runs. |
| ownership | Report Data owns fixed progress/options and shared immutable typed handles. Retained binding/tree/proof graphs survive producer destruction; no reference to the mutable producer or its execution machine is stored. |
| failure | Moved-from producer/typed-handle or report access Error and allocation failures propagate. No advance/replay/recognition or producer mutation occurs; private report preparation releases on failure. |
| cost | One ordinary shared Data allocation, fixed progress/options copies and shared-handle retains; no catalog/tree/proof scan or deep payload clone. |
| Design | [include/crown/observability/query_explain.hpp](../../../../../include/crown/observability/query_explain.hpp), [docs/observability.md §Reports, ownership, and committed gauges](../../../../observability.md), [include/crown/planner/search.hpp](../../../../../include/crown/planner/search.hpp), [src/planner/search_session.cpp](../../../../../src/planner/search_session.cpp), [docs/planner_continuations.md §Authority and policies](../../../../planner_continuations.md), [src/planner/continuation_machine.hpp](../../../../../src/planner/continuation_machine.hpp), [docs/planner_continuations.md §Lifetime and output](../../../../planner_continuations.md) |

## B0009

[Lines 46–50](../../../../../src/observability/query_explain.cpp#L46); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
QueryExplanation QueryExplanation::capture(const CertificateReplay& owner,QueryExplainLimits limits)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Capture proof-replay progress and only a fully published checked artifact. |
| inputs / outputs | Actual CertificateReplay supplies binding/progress/replay limits and owner.checked(); finish derives typed optimum/infeasibility only if checked is present. |
| invariants | A complete failed replay or checked prefix does not imply valid whole proof. Exclusive caller discipline makes these separate reads consistent; capture performs no replay step. |
| ownership | Report Data owns fixed progress/options and shared immutable typed handles. Retained binding/tree/proof graphs survive producer destruction; no reference to the mutable producer or its execution machine is stored. |
| failure | Moved-from producer/typed-handle or report access Error and allocation failures propagate. No advance/replay/recognition or producer mutation occurs; private report preparation releases on failure. |
| cost | One ordinary shared Data allocation plus fixed metadata and shared-owner copies, no certificate traversal or DOM. |
| Design | [include/crown/observability/query_explain.hpp](../../../../../include/crown/observability/query_explain.hpp), [docs/observability.md §Reports, ownership, and committed gauges](../../../../observability.md), [include/crown/planner/search.hpp](../../../../../include/crown/planner/search.hpp), [src/planner/search_session.cpp](../../../../../src/planner/search_session.cpp), [docs/planner_continuations.md §Authority and policies](../../../../planner_continuations.md), [src/planner/continuation_machine.hpp](../../../../../src/planner/continuation_machine.hpp), [docs/planner_continuations.md §Lifetime and output](../../../../planner_continuations.md) |

## B0010

[Lines 51–53](../../../../../src/observability/query_explain.cpp#L51); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
QueryExplanation QueryExplanation::from(ValidatedIncumbent value,QueryExplainLimits limits)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Create an explanation from a genuine checked upper-bound handle. |
| inputs / outputs | Moves ValidatedIncumbent into a new envelope with its own exact binding and checked_upper source. |
| invariants | The typed tree proves an upper only. It does not supply minimum height, lower-proof completion, cost rank or a runtime plan installation. |
| ownership | Report Data owns fixed progress/options and shared immutable typed handles. Retained binding/tree/proof graphs survive producer destruction; no reference to the mutable producer or its execution machine is stored. |
| failure | Moved-from producer/typed-handle or report access Error and allocation failures propagate. No advance/replay/recognition or producer mutation occurs; private report preparation releases on failure. |
| cost | One ordinary shared Data allocation and shared-handle retains; node-count admission reads size only. |
| Design | [include/crown/observability/query_explain.hpp](../../../../../include/crown/observability/query_explain.hpp), [docs/observability.md §Reports, ownership, and committed gauges](../../../../observability.md), [include/crown/planner/search.hpp](../../../../../include/crown/planner/search.hpp), [src/planner/search_session.cpp](../../../../../src/planner/search_session.cpp), [docs/planner_continuations.md §Authority and policies](../../../../planner_continuations.md) |

## B0011

[Lines 54–56](../../../../../src/observability/query_explain.cpp#L54); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
QueryExplanation QueryExplanation::from(VerifiedOptimum value,QueryExplainLimits limits)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Create an explanation from a genuine independently verified optimum. |
| inputs / outputs | Moves VerifiedOptimum with its exact binding; finish derives matching typed upper and checks witness/proof counts. |
| invariants | Upper/lower proof authority remains bound to that admitted query. Prefix-scoped proof cannot be relabeled as the original larger query. |
| ownership | Report Data owns fixed progress/options and shared immutable typed handles. Retained binding/tree/proof graphs survive producer destruction; no reference to the mutable producer or its execution machine is stored. |
| failure | Moved-from producer/typed-handle or report access Error and allocation failures propagate. No advance/replay/recognition or producer mutation occurs; private report preparation releases on failure. |
| cost | One ordinary Data allocation, fixed shared-owner operations and size checks; no new search/replay or tree copy. |
| Design | [include/crown/observability/query_explain.hpp](../../../../../include/crown/observability/query_explain.hpp), [docs/observability.md §Reports, ownership, and committed gauges](../../../../observability.md), [include/crown/planner/search.hpp](../../../../../include/crown/planner/search.hpp), [src/planner/search_session.cpp](../../../../../src/planner/search_session.cpp), [docs/planner_continuations.md §Authority and policies](../../../../planner_continuations.md), [docs/planner_proofs.md §Independent lower-bound evidence and strict limits](../../../../planner_proofs.md) |

## B0012

[Lines 57–59](../../../../../src/observability/query_explain.cpp#L57); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
QueryExplanation QueryExplanation::from(VerifiedInfeasible value,QueryExplainLimits limits)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Create a no-tree explanation from genuine verified infeasibility. |
| inputs / outputs | Moves VerifiedInfeasible and its exact binding into an envelope; finish checks lower-bound entry count. |
| invariants | Only this typed whole-proof result establishes no admissible structural tree. Missing witness, failed search or cancelled replay alone do not. |
| ownership | Report Data owns fixed progress/options and shared immutable typed handles. Retained binding/tree/proof graphs survive producer destruction; no reference to the mutable producer or its execution machine is stored. |
| failure | Moved-from producer/typed-handle or report access Error and allocation failures propagate. No advance/replay/recognition or producer mutation occurs; private report preparation releases on failure. |
| cost | One ordinary Data allocation and shared owner/size reads; no lower-bound traversal or replay. |
| Design | [include/crown/observability/query_explain.hpp](../../../../../include/crown/observability/query_explain.hpp), [docs/observability.md §Reports, ownership, and committed gauges](../../../../observability.md), [include/crown/planner/search.hpp](../../../../../include/crown/planner/search.hpp), [src/planner/search_session.cpp](../../../../../src/planner/search_session.cpp), [docs/planner_continuations.md §Authority and policies](../../../../planner_continuations.md), [docs/planner_proofs.md §Independent lower-bound evidence and strict limits](../../../../planner_proofs.md) |

## B0013

[Lines 60–62](../../../../../src/observability/query_explain.cpp#L60); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
QueryExplanation QueryExplanation::from(CheckedCertificate value,QueryExplainLimits limits)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Create an explanation from a fully checked external certificate artifact. |
| inputs / outputs | Moves CheckedCertificate with its binding; finish extracts the already published positive or infeasible typed result and matching witness. |
| invariants | Arbitrary HeightCertificate aggregates/Boolean flags cannot enter this factory. Parsing a serialized certificate is a separate untrusted-claim boundary. |
| ownership | Report Data owns fixed progress/options and shared immutable typed handles. Retained binding/tree/proof graphs survive producer destruction; no reference to the mutable producer or its execution machine is stored. |
| failure | Moved-from producer/typed-handle or report access Error and allocation failures propagate. No advance/replay/recognition or producer mutation occurs; private report preparation releases on failure. |
| cost | One ordinary Data allocation plus fixed shared handles/size checks; certificate bytes are not reparsed or copied. |
| Design | [include/crown/observability/query_explain.hpp](../../../../../include/crown/observability/query_explain.hpp), [docs/observability.md §Reports, ownership, and committed gauges](../../../../observability.md), [include/crown/planner/search.hpp](../../../../../include/crown/planner/search.hpp), [src/planner/search_session.cpp](../../../../../src/planner/search_session.cpp), [docs/planner_continuations.md §Authority and policies](../../../../planner_continuations.md), [include/crown/io/oracle.hpp](../../../../../include/crown/io/oracle.hpp), [include/crown/planner/oracle.hpp](../../../../../include/crown/planner/oracle.hpp), [docs/tree_oracle.md §Height certificate](../../../../tree_oracle.md) |

## B0014

[Lines 63–63](../../../../../src/observability/query_explain.cpp#L63); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
const SearchBinding& QueryExplanation::binding() const
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Borrow the exact immutable binding retained by the report. |
| inputs / outputs | Returns const SearchBinding& after live-report check. |
| invariants | Retains the admitted Catalog/Query scope without upgrading a prefix or comparing against a caller-selected plan. |
| ownership | Reference borrows Data; copying SearchBinding explicitly retains the immutable underlying owner. |
| failure | Moved-from report Error; otherwise no new validation or resource charge. |
| cost | Fixed reference access, no allocation or model scan. |
| Design | [include/crown/observability/query_explain.hpp](../../../../../include/crown/observability/query_explain.hpp), [docs/observability.md §Reports, ownership, and committed gauges](../../../../observability.md), [include/crown/planner/search.hpp](../../../../../include/crown/planner/search.hpp), [src/planner/search_session.cpp](../../../../../src/planner/search_session.cpp), [docs/planner_continuations.md §Authority and policies](../../../../planner_continuations.md) |

## B0015

[Lines 64–64](../../../../../src/observability/query_explain.cpp#L64); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
QueryExplainSource QueryExplanation::source() const
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Read the report construction route. |
| inputs / outputs | Returns captured QueryExplainSource enum by value. |
| invariants | Source distinguishes owner capture versus typed-handle factory; status/authority must still be read from retained typed evidence, not route alone. |
| ownership | Returned enum owns its scalar value. |
| failure | Moved-from report Error. |
| cost | Fixed field copy, no allocation. |
| Design | [include/crown/observability/query_explain.hpp](../../../../../include/crown/observability/query_explain.hpp), [docs/observability.md §Reports, ownership, and committed gauges](../../../../observability.md) |

## B0016

[Lines 65–72](../../../../../src/observability/query_explain.cpp#L65); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
QueryHeightStatus QueryExplanation::height_status() const
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Classify retained typed height evidence separately from numeric producer progress. |
| inputs / outputs | Priority is optimum, infeasibility, typed witness, then exact-search numeric upper with unpublished witness, otherwise unknown. |
| invariants | owner_checked_upper_unpublished never promises a tree export. Search/replay phase/complete flags alone cannot establish optimum or infeasibility. |
| ownership | Returns copied enum; shared evidence remains in report. |
| failure | Moved-from report Error. |
| cost | Fixed optional-presence tests, no structural traversal, replay or allocation. |
| Design | [include/crown/observability/query_explain.hpp](../../../../../include/crown/observability/query_explain.hpp), [docs/observability.md §Reports, ownership, and committed gauges](../../../../observability.md), [include/crown/planner/search.hpp](../../../../../include/crown/planner/search.hpp), [src/planner/search_session.cpp](../../../../../src/planner/search_session.cpp), [docs/planner_continuations.md §Authority and policies](../../../../planner_continuations.md) |

## B0017

[Lines 73–77](../../../../../src/observability/query_explain.cpp#L73); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::optional<std::size_t> QueryExplanation::lower() const
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Read verified or universal lower-height evidence without producer work. |
| inputs / outputs | Infeasible returns null; optimum returns exact height; otherwise empty bound query body gives 0 and nonempty gives universal 1. |
| invariants | Universal bound is the local P06 starting bound, not recognition, constant-false operator height, a strengthened finite proof or progress lower from a caller DTO. |
| ownership | Returns optional size value; no borrowed payload escapes. |
| failure | Moved-from report/invalid typed handle Error only. |
| cost | Fixed typed-handle/atoms.empty access, no query scan, allocation or producer advancement. |
| Design | [include/crown/observability/query_explain.hpp](../../../../../include/crown/observability/query_explain.hpp), [docs/observability.md §Reports, ownership, and committed gauges](../../../../observability.md), [include/crown/planner/search.hpp](../../../../../include/crown/planner/search.hpp), [src/planner/search_session.cpp](../../../../../src/planner/search_session.cpp), [docs/planner_continuations.md §Authority and policies](../../../../planner_continuations.md), [docs/planner_proofs.md §P06 retained execution and authority](../../../../planner_proofs.md) |

## B0018

[Lines 78–81](../../../../../src/observability/query_explain.cpp#L78); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::optional<std::size_t> QueryExplanation::upper() const
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Read the best retained upper while preserving publication scope. |
| inputs / outputs | Optimum height takes precedence, then typed witness height, then captured ExactSearch scalar upper; replay without published artifact has no upper here. |
| invariants | Numeric strict-owner upper may exist without a public witness; this getter does not synthesize one or claim minimum. |
| ownership | Returns copied optional size. |
| failure | Moved-from report/invalid typed handle Error only. |
| cost | Fixed optional/handle/field accesses, no scan or allocation. |
| Design | [include/crown/observability/query_explain.hpp](../../../../../include/crown/observability/query_explain.hpp), [docs/observability.md §Reports, ownership, and committed gauges](../../../../observability.md), [include/crown/planner/search.hpp](../../../../../include/crown/planner/search.hpp), [src/planner/search_session.cpp](../../../../../src/planner/search_session.cpp), [docs/planner_continuations.md §Authority and policies](../../../../planner_continuations.md) |

## B0019

[Lines 82–82](../../../../../src/observability/query_explain.cpp#L82); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
const std::optional<SearchProgress>& QueryExplanation::search_progress() const
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Borrow the exact-search progress captured at report construction. |
| inputs / outputs | Returns const optional&lt;SearchProgress&gt;&; absent for other construction routes. |
| invariants | Fixed diagnostic counters/intervals are frozen values. Editing another progress DTO cannot mutate report evidence or grants. |
| ownership | Reference borrows immutable Data, valid while a sharing report copy survives. |
| failure | Moved-from report Error. |
| cost | Fixed reference access; no refresh, producer work or allocation. |
| Design | [include/crown/observability/query_explain.hpp](../../../../../include/crown/observability/query_explain.hpp), [docs/observability.md §Reports, ownership, and committed gauges](../../../../observability.md), [include/crown/planner/search.hpp](../../../../../include/crown/planner/search.hpp), [src/planner/search_session.cpp](../../../../../src/planner/search_session.cpp), [docs/planner_continuations.md §Authority and policies](../../../../planner_continuations.md) |

## B0020

[Lines 83–83](../../../../../src/observability/query_explain.cpp#L83); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
const std::optional<ReplayProgress>& QueryExplanation::replay_progress() const
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Borrow captured replay progress without running the checker. |
| inputs / outputs | Returns const optional&lt;ReplayProgress&gt;&, populated only from replay-owner capture. |
| invariants | complete may describe rejection; valid whole-proof authority comes from checked artifact, not a supplied progress flag. |
| ownership | Reference borrows immutable report Data. |
| failure | Moved-from report Error. |
| cost | Fixed reference access, no allocation or proof traversal. |
| Design | [include/crown/observability/query_explain.hpp](../../../../../include/crown/observability/query_explain.hpp), [docs/observability.md §Reports, ownership, and committed gauges](../../../../observability.md), [include/crown/planner/search.hpp](../../../../../include/crown/planner/search.hpp), [src/planner/search_session.cpp](../../../../../src/planner/search_session.cpp), [docs/planner_continuations.md §Authority and policies](../../../../planner_continuations.md) |

## B0021

[Lines 84–84](../../../../../src/observability/query_explain.cpp#L84); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
const std::optional<SearchPolicy>& QueryExplanation::policy() const
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Borrow the exact-search exposure policy recorded in this report. |
| inputs / outputs | Returns optional SearchPolicy by const reference; absent for standalone typed artifact/replay routes. |
| invariants | Policy describes incumbent exposure, not a new algorithm flag, resource allowance or proof result. |
| ownership | Reference borrows report Data. |
| failure | Moved-from report Error. |
| cost | Fixed reference access, no allocation. |
| Design | [include/crown/observability/query_explain.hpp](../../../../../include/crown/observability/query_explain.hpp), [docs/observability.md §Reports, ownership, and committed gauges](../../../../observability.md), [include/crown/planner/search.hpp](../../../../../include/crown/planner/search.hpp), [src/planner/search_session.cpp](../../../../../src/planner/search_session.cpp), [docs/planner_continuations.md §Authority and policies](../../../../planner_continuations.md) |

## B0022

[Lines 85–85](../../../../../src/observability/query_explain.cpp#L85); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
const std::optional<ContinuationLimits>& QueryExplanation::search_limits() const
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Borrow the captured producer/replay ceilings for exact-search capture. |
| inputs / outputs | Returns const optional&lt;ContinuationLimits&gt;& with copied phase work/time/depth ceilings. |
| invariants | Snapshot limits do not extend or refill the owner; no retained-byte bound follows from controlled-transition or logical-depth units. |
| ownership | Reference borrows report Data. |
| failure | Moved-from report Error. |
| cost | Fixed reference access, no allocation or resource change. |
| Design | [include/crown/observability/query_explain.hpp](../../../../../include/crown/observability/query_explain.hpp), [docs/observability.md §Reports, ownership, and committed gauges](../../../../observability.md), [docs/planner_continuations.md §Resource accounting](../../../../planner_continuations.md) |

## B0023

[Lines 86–86](../../../../../src/observability/query_explain.cpp#L86); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
const std::optional<ReplayOptions>& QueryExplanation::replay_limits() const
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Borrow replay-only ceilings recorded at capture. |
| inputs / outputs | Returns optional ReplayOptions by const reference; absent for non-replay routes. |
| invariants | Descriptions of configured work/active-time/depth do not revalidate proof or alter the actual owner. |
| ownership | Reference borrows report Data. |
| failure | Moved-from report Error. |
| cost | Fixed reference access, no allocation. |
| Design | [include/crown/observability/query_explain.hpp](../../../../../include/crown/observability/query_explain.hpp), [docs/observability.md §Reports, ownership, and committed gauges](../../../../observability.md), [include/crown/planner/search.hpp](../../../../../include/crown/planner/search.hpp), [src/planner/search_session.cpp](../../../../../src/planner/search_session.cpp), [docs/planner_continuations.md §Authority and policies](../../../../planner_continuations.md) |

## B0024

[Lines 87–87](../../../../../src/observability/query_explain.cpp#L87); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
const std::optional<ValidatedIncumbent>& QueryExplanation::witness() const
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Borrow the optional published checked tree handle. |
| inputs / outputs | Returns const optional&lt;ValidatedIncumbent&gt;&, including optimum-derived upper normalized by finish. |
| invariants | Only genuine typed witness supports tree export; a scalar upper without this handle does not. |
| ownership | Reference borrows Data; copying handle explicitly retains immutable tree/binding. |
| failure | Moved-from report Error. |
| cost | Fixed reference access, no tree copy/scan/allocation. |
| Design | [include/crown/observability/query_explain.hpp](../../../../../include/crown/observability/query_explain.hpp), [docs/observability.md §Reports, ownership, and committed gauges](../../../../observability.md), [include/crown/planner/search.hpp](../../../../../include/crown/planner/search.hpp), [src/planner/search_session.cpp](../../../../../src/planner/search_session.cpp), [docs/planner_continuations.md §Authority and policies](../../../../planner_continuations.md) |

## B0025

[Lines 88–88](../../../../../src/observability/query_explain.cpp#L88); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
const std::optional<VerifiedOptimum>& QueryExplanation::optimum() const
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Borrow the optional independently verified optimum handle. |
| inputs / outputs | Returns const optional&lt;VerifiedOptimum&gt;&; empty unless original producer/artifact published matching whole proof. |
| invariants | Does not infer optimum from equal numeric bounds or a legacy certificate_verified Boolean. |
| ownership | Reference borrows Data; copied typed handle retains underlying evidence. |
| failure | Moved-from report Error. |
| cost | Fixed reference access, no proof replay or allocation. |
| Design | [include/crown/observability/query_explain.hpp](../../../../../include/crown/observability/query_explain.hpp), [docs/observability.md §Reports, ownership, and committed gauges](../../../../observability.md), [include/crown/planner/search.hpp](../../../../../include/crown/planner/search.hpp), [src/planner/search_session.cpp](../../../../../src/planner/search_session.cpp), [docs/planner_continuations.md §Authority and policies](../../../../planner_continuations.md) |

## B0026

[Lines 89–89](../../../../../src/observability/query_explain.cpp#L89); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
const std::optional<VerifiedInfeasible>& QueryExplanation::infeasibility() const
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Borrow the optional independently verified no-tree result. |
| inputs / outputs | Returns const optional&lt;VerifiedInfeasible&gt;&. |
| invariants | Only retained typed infeasibility carries authority; unknown/failed/cancelled states remain distinct. |
| ownership | Reference borrows Data; copied handle retains proof/binding. |
| failure | Moved-from report Error. |
| cost | Fixed reference access, no allocation. |
| Design | [include/crown/observability/query_explain.hpp](../../../../../include/crown/observability/query_explain.hpp), [docs/observability.md §Reports, ownership, and committed gauges](../../../../observability.md), [include/crown/planner/search.hpp](../../../../../include/crown/planner/search.hpp), [src/planner/search_session.cpp](../../../../../src/planner/search_session.cpp), [docs/planner_continuations.md §Authority and policies](../../../../planner_continuations.md) |

## B0027

[Lines 90–90](../../../../../src/observability/query_explain.cpp#L90); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
const std::optional<CheckedCertificate>& QueryExplanation::checked_certificate() const
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Borrow a fully published checked certificate artifact when retained. |
| inputs / outputs | Returns const optional&lt;CheckedCertificate&gt;& for replay or checked-certificate factory routes. |
| invariants | No raw HeightCertificate aggregate is promoted by this accessor; search captures can have optimum without this specific wrapper. |
| ownership | Reference borrows Data; copied handle retains its immutable checked graph. |
| failure | Moved-from report Error. |
| cost | Fixed reference access, no certificate copy/replay/allocation. |
| Design | [include/crown/observability/query_explain.hpp](../../../../../include/crown/observability/query_explain.hpp), [docs/observability.md §Reports, ownership, and committed gauges](../../../../observability.md), [include/crown/planner/search.hpp](../../../../../include/crown/planner/search.hpp), [src/planner/search_session.cpp](../../../../../src/planner/search_session.cpp), [docs/planner_continuations.md §Authority and policies](../../../../planner_continuations.md) |

## B0028

[Lines 91–93](../../../../../src/observability/query_explain.cpp#L91); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
const HeightCertificate* QueryExplanation::certificate() const
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Borrow the whole proof only from a retained verified outcome. |
| inputs / outputs | Returns optimum certificate pointer, otherwise infeasibility certificate pointer, otherwise nullptr. |
| invariants | The pointed HeightCertificate remains an editable aggregate type in other contexts; this const view is backed by genuine immutable typed authority, not parsed caller flags. |
| ownership | Pointer borrows report-retained proof; retain report or separately copied typed result through use. |
| failure | Moved-from report/invalid typed handle Error; nullptr is normal without a verified outcome. |
| cost | Fixed optional/handle lookup, no proof copy or enumeration. |
| Design | [include/crown/observability/query_explain.hpp](../../../../../include/crown/observability/query_explain.hpp), [docs/observability.md §Reports, ownership, and committed gauges](../../../../observability.md), [include/crown/planner/search.hpp](../../../../../include/crown/planner/search.hpp), [src/planner/search_session.cpp](../../../../../src/planner/search_session.cpp), [docs/planner_continuations.md §Authority and policies](../../../../planner_continuations.md) |

## B0029

[Lines 94–94](../../../../../src/observability/query_explain.cpp#L94); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L94-L94:sha256:15ac899d66e81241a264aee901694a508b7370147772ee46125ef9b6e5307ec5
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Closes the namespace crown::observability at this source boundary; this is a lexical delimiter, not an operation. |
| inputs / outputs | No runtime input or output. Declarations following the span leave the preceding C++ scope. |
| invariants | The delimiter ends the preceding scope's visibility/linkage region; it adds no validation, publication, ownership transfer, or runtime authority. |
| ownership | The delimiter adds no owner. If it ends a function/block with live automatic objects, their normal destructors release those objects; namespace and type-definition closes change no existing object's lifetime. |
| failure | No explicit failure translation or catch is added. If a function/block exit destroys automatic objects, exception behavior follows those destructors; namespace/type closes have no runtime failure path. |
| cost | The delimiter adds no algorithmic work. A function/block exit can run existing automatic-object destructors and cleanup; namespace/type closes have no runtime cost. |
| Design | [src/observability/query_explain.cpp](../../../../../src/observability/query_explain.cpp), [docs/code_specs/files/src/observability/query_explain.cpp.md](query_explain.cpp.md), [docs/observability.md](../../../../observability.md), [docs/statistics.md](../../../../statistics.md) |
