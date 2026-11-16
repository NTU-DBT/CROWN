# `src/observability/explain.cpp` — block usage map

[Source](../../../../../src/observability/explain.cpp) · [Source index](../../../README.md) · [Subsystem contracts](../../../subsystem_contracts.md) · [Reviewed primitives](../../../primitives.md)

Capture bounded distributions, workload counters, owner memory and explain observations without mislabeling partial information as exact.

Snapshot SHA-256: `6fa3897186d408b241b4ec5d84eb6f6524a6ce93a7cdea94359a620274f08cab`. 276 lines partitioned into 58 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [statistics](../../../subsystem_contracts.md#statistics). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/statistics.md](../../../../statistics.md), [docs/observability.md](../../../../observability.md), [docs/memory_reports.md](../../../../memory_reports.md), [docs/ranking_evaluation.md](../../../../ranking_evaluation.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–9](../../../../../src/observability/explain.cpp#L1) | Imports dependencies; declares namespace scope. |  · [reviewed contract](#b0001) |
| [B0002 · 10–12](../../../../../src/observability/explain.cpp#L10) | Callable definition: void require(bool condition,const char* code,const char* message) | calls Error; guard void require(bool condition,const char* code,const char* message) { · [reviewed contract](#b0002) |
| [B0003 · 13–17](../../../../../src/observability/explain.cpp#L13) | Callable definition: template&lt;class A,class B,class Equal&gt; bool same_range(const A& a,const B& b,Equal equal) | calls size, equal; returns false; false; 1 loop sites · [reviewed contract](#b0003) |
| [B0004 · 18–18](../../../../../src/observability/explain.cpp#L18) | Callable definition: template&lt;class A,class B&gt; bool equal_items(const A& a,const B& b) | calls std::ranges::equal; returns std::ranges::equal(a,b) · [reviewed contract](#b0004) |
| [B0005 · 19–21](../../../../../src/observability/explain.cpp#L19) | Callable definition: template&lt;class A,class B&gt; bool equal_optional_items(const A& a,const B& b) | calls has_value, equal_items; returns a.has_value()==b.has_value() && (!a \|\| equal_items(*a,*b)) · [reviewed contract](#b0005) |
| [B0006 · 22–31](../../../../../src/observability/explain.cpp#L22) | Callable definition: template&lt;class A,class B&gt; bool same_constraint(const A& a,const B& b) | calls index, equal_items; returns false; x-&gt;name==y.name && equal_items(x-&gt;columns,y.columns) && x-&gt;status==y.status · [reviewed contract](#b0006) |
| [B0007 · 32–33](../../../../../src/observability/explain.cpp#L32) | Explanatory comments or spacing. | source comment (unverified): // Exact ordered metadata, including hints/statistics and constraint status; · [reviewed contract](#b0007) |
| [B0008 · 34–47](../../../../../src/observability/explain.cpp#L34) | Callable definition: template&lt;class A,class B&gt; bool same_catalog(const A& a,const B& b) | calls same_range, same_constraint, equal_items; returns a.version==b.version && same_range(a.tables,b.tables,\[\](const auto& x,const auto& y) {; x.name==y.n…; source comment (unverified): // Exact ordered metadata, including hints/statistics and constraint status; · [reviewed contract](#b0008) |
| [B0009 · 48–51](../../../../../src/observability/explain.cpp#L48) | Callable definition: template&lt;class Scalar&gt; storage::ScalarView scalar_view(const Scalar& value) | calls constexpr, storage::borrow_scalar; returns storage::borrow_scalar(value); value · [reviewed contract](#b0009) |
| [B0010 · 52–57](../../../../../src/observability/explain.cpp#L52) | Callable definition: template&lt;class A,class B&gt; bool same_term(const A& a,const B& b) | calls index, scalar_view; returns false; *id==std::get&lt;0&gt;(b) · [reviewed contract](#b0010) |
| [B0011 · 58–65](../../../../../src/observability/explain.cpp#L58) | Callable definition: template&lt;class A,class B&gt; bool same_query(const A& a,const B& b) | calls same_range, same_term; returns a.contradiction==b.contradiction &&; x.name==y.name && x.type==y.type · [reviewed contract](#b0011) |
| [B0012 · 66–66](../../../../../src/observability/explain.cpp#L66) | Explanatory comments or spacing. | source comment (unverified): // Claim metadata and ordering are part of this exact tree comparison. · [reviewed contract](#b0012) |
| [B0013 · 67–73](../../../../../src/observability/explain.cpp#L67) | Callable definition: template&lt;class A,class B&gt; bool same_tree(const A& a,const B& b) | calls equal_optional_items, same_range, equal_items; returns a.root==b.root && equal_optional_items(a.claimed_connex,b.claimed_connex) && a.claimed_native_heigh…; source comment (unverified): // Claim metadata and ordering are part of this exact tree comparison. · [reviewed contract](#b0013) |
| [B0014 · 74–77](../../../../../src/observability/explain.cpp#L74) | Callable definition: void binding(const runtime::CompiledProgram& plan,const planner::SearchBinding& value) | calls require, valid, same_catalog, catalog; guard require(value.valid() && same_catalog(plan.catalog(),value.catalog()) && same_query(plan.query(),va… · [reviewed contract](#b0014) |
| [B0015 · 78–84](../../../../../src/observability/explain.cpp#L78) | Callable definition: void context(const runtime::CompiledProgram& plan,const planner::CandidateContext& value) | calls options, require; guard require(value.updates==planner::CandidateUpdateProfile::mixed_full_row_set_v1 && · [reviewed contract](#b0015) |
| [B0016 · 85–89](../../../../../src/observability/explain.cpp#L85) | Callable definition: std::optional&lt;planner::VerifiedOptimum&gt; proof(const HeightEvidence& evidence) | calls original_proof; returns *value; value-&gt;original_proof() · [reviewed contract](#b0016) |
| [B0017 · 90–90](../../../../../src/observability/explain.cpp#L90) | Closes surrounding scope/type. |  · [reviewed contract](#b0017) |
| [B0018 · 91–100](../../../../../src/observability/explain.cpp#L91) | Type/record definition: struct ModeDescriptor::Data |  · [reviewed contract](#b0018) |
| [B0019 · 101–101](../../../../../src/observability/explain.cpp#L101) | Callable definition: ModeDescriptor::ModeDescriptor(std::shared_ptr&lt;const Data&gt; value):data_(std::move(value)) | calls data_, std::move · [reviewed contract](#b0019) |
| [B0020 · 102–102](../../../../../src/observability/explain.cpp#L102) | Callable definition: const ModeDescriptor::Data& ModeDescriptor::data() const | calls require, bool; guard const ModeDescriptor::Data& ModeDescriptor::data() const { require(bool(data_),"invalid_explanation…; returns *data_ · [reviewed contract](#b0020) |
| [B0021 · 103–111](../../../../../src/observability/explain.cpp#L103) | Callable definition: ModeDescriptor ModeDescriptor::compile_only(PhysicalPlan plan) | calls resource::MemoryAccount::create, work, runtime::CompiledProgram::freeze, ModeDescriptor; returns ModeDescriptor(resource::make_accounted_shared&lt;Data&gt;({resource::MemoryOwnerKind::capture,6},account,; growth make_accounted_shared; source comment (unverified): // Compiler-only reports own standalone immutable metadata. Runtime captures · [reviewed contract](#b0021) |
| [B0022 · 112–116](../../../../../src/observability/explain.cpp#L112) | Callable definition: ModeDescriptor ModeDescriptor::compile_only(runtime::CompiledProgram plan) | calls account, ModeDescriptor, std::move; returns ModeDescriptor(resource::make_accounted_shared&lt;Data&gt;({resource::MemoryOwnerKind::capture,6},account,; growth make_accounted_shared · [reviewed contract](#b0022) |
| [B0023 · 117–124](../../../../../src/observability/explain.cpp#L117) | Callable definition: ModeDescriptor ModeDescriptor::capture(const runtime::DeltaRuntime& runtime) | calls compiled_program, account, owner, sequence; returns ModeDescriptor(std::move(result)); growth make_accounted_shared · [reviewed contract](#b0023) |
| [B0024 · 125–128](../../../../../src/observability/explain.cpp#L125) | Callable definition: ModeDescriptor ModeDescriptor::capture(const runtime::QuerySession& session) | calls report_metadata, status, from_session; returns from_session(meta,status) · [reviewed contract](#b0024) |
| [B0025 · 129–130](../../../../../src/observability/explain.cpp#L129) | Explanatory comments or spacing. | source comment (unverified): // running records retained native state; a stopped session can still have it. · [reviewed contract](#b0025) |
| [B0026 · 131–139](../../../../../src/observability/explain.cpp#L131) | Callable definition: ModeDescriptor ModeDescriptor::from_session(const runtime::SessionReportMetadata& meta,const runtime::SessionStatus& status) | calls plan, account, state, has_value; returns ModeDescriptor(std::move(result)); growth make_accounted_shared; source comment (unverified): // running records retained native state; a stopped session can still have it. · [reviewed contract](#b0026) |
| [B0027 · 140–140](../../../../../src/observability/explain.cpp#L140) | Callable definition: const runtime::CompiledProgram& ModeDescriptor::plan() const | calls data; returns data().plan · [reviewed contract](#b0027) |
| [B0028 · 141–141](../../../../../src/observability/explain.cpp#L141) | Callable definition: bool ModeDescriptor::running() const | calls data; returns data().running · [reviewed contract](#b0028) |
| [B0029 · 142–142](../../../../../src/observability/explain.cpp#L142) | Callable definition: std::uint64_t ModeDescriptor::owner() const | calls data; returns data().owner · [reviewed contract](#b0029) |
| [B0030 · 143–143](../../../../../src/observability/explain.cpp#L143) | Callable definition: std::uint64_t ModeDescriptor::sequence() const | calls data; returns data().sequence · [reviewed contract](#b0030) |
| [B0031 · 144–144](../../../../../src/observability/explain.cpp#L144) | Callable definition: std::optional&lt;runtime::DeltaState&gt; ModeDescriptor::state() const | calls data; returns data().state · [reviewed contract](#b0031) |
| [B0032 · 145–145](../../../../../src/observability/explain.cpp#L145) | Callable definition: RuntimePresence ModeDescriptor::presence() const | calls data; returns data().presence · [reviewed contract](#b0032) |
| [B0033 · 146–146](../../../../../src/observability/explain.cpp#L146) | Callable definition: const std::optional&lt;runtime::DeltaOptions&gt;& ModeDescriptor::options() const | calls data; returns data().options · [reviewed contract](#b0033) |
| [B0034 · 147–147](../../../../../src/observability/explain.cpp#L147) | Callable definition: const std::optional&lt;runtime::DeltaRuntimeProfile&gt;& ModeDescriptor::profile() const | calls data; returns data().profile · [reviewed contract](#b0034) |
| [B0035 · 148–164](../../../../../src/observability/explain.cpp#L148) | Type/record definition: struct PlanExplanation::Data |  · [reviewed contract](#b0035) |
| [B0036 · 165–165](../../../../../src/observability/explain.cpp#L165) | Callable definition: PlanExplanation::PlanExplanation(std::shared_ptr&lt;const Data&gt; value):data_(std::move(value)) | calls data_, std::move · [reviewed contract](#b0036) |
| [B0037 · 166–166](../../../../../src/observability/explain.cpp#L166) | Callable definition: const PlanExplanation::Data& PlanExplanation::data() const | calls require, bool; guard const PlanExplanation::Data& PlanExplanation::data() const { require(bool(data_),"invalid_explanati…; returns *data_ · [reviewed contract](#b0037) |
| [B0038 · 167–215](../../../../../src/observability/explain.cpp#L167) | Callable definition: PlanExplanation PlanExplanation::make(ModeDescriptor mode,HeightEvidence evidence, std::optional&lt;planner::CandidateSnapshot&gt; fami… | calls plan, require, tree, size; guard require(plan.tree().nodes.size()&lt;=limits.nodes,"resource_limit","EXPLAIN node limit exceeded");; returns PlanExplanation(std::move(result)); growth make_accounted_shared; source comment (unverified): // P08's immutable handle is the authority for validity. No report or imported · [reviewed contract](#b0038) |
| [B0039 · 216–218](../../../../../src/observability/explain.cpp#L216) | Callable definition: PlanExplanation PlanExplanation::create(PhysicalPlan plan,HeightEvidence evidence,std::optional&lt;planner::CandidateSnapshot&gt; famil… | calls make, ModeDescriptor::compile_only, std::move; returns make(ModeDescriptor::compile_only(std::move(plan)),std::move(evidence),std::move(family),{},limits) · [reviewed contract](#b0039) |
| [B0040 · 219–221](../../../../../src/observability/explain.cpp#L219) | Callable definition: PlanExplanation PlanExplanation::create(runtime::CompiledProgram plan,HeightEvidence evidence,std::optional&lt;planner::CandidateSna… | calls make, ModeDescriptor::compile_only, std::move; returns make(ModeDescriptor::compile_only(std::move(plan)),std::move(evidence),std::move(family),{},limits) · [reviewed contract](#b0040) |
| [B0041 · 222–239](../../../../../src/observability/explain.cpp#L222) | Callable definition: PlanExplanation PlanExplanation::capture(const runtime::DeltaRuntime& runtime,HeightEvidence evidence,std::optional&lt;planner::Cand… | calls require, workload_statistics_options, ModeDescriptor::capture, capture_observation_trace; guard require(runtime.workload_statistics_options().mode==runtime::workload::Mode::off,; returns make(std::move(mode),std::move(evidence),std::move(family),std::move(observation),limits,; source comment (unverified): // Caller serializes capture with owner advance, mode changes, drains and callbacks. · [reviewed contract](#b0041) |
| [B0042 · 240–251](../../../../../src/observability/explain.cpp#L240) | Callable definition: PlanExplanation PlanExplanation::capture(const runtime::QuerySession& session,HeightEvidence evidence, std::optional&lt;planner::Can… | calls require, workload_statistics_options, ModeDescriptor::capture, capture_observation_trace; guard require(session.workload_statistics_options().mode==runtime::workload::Mode::off,; returns make(std::move(mode),std::move(evidence),std::move(family),std::move(observation),limits, · [reviewed contract](#b0042) |
| [B0043 · 252–252](../../../../../src/observability/explain.cpp#L252) | Callable definition: const runtime::CapturedTraceRecords& PlanExplanation::trace_records() const | calls data; returns data().trace · [reviewed contract](#b0043) |
| [B0044 · 253–262](../../../../../src/observability/explain.cpp#L253) | Callable definition: PlanExplanation PlanExplanation::capture_statistics_context(const runtime::DeltaRuntime& runtime,ExplainLimits limits) | calls ModeDescriptor::capture, capture_observation_trace, require, options; guard require(trace.snapshot.options==runtime.options().physical.support.observation,"explain_mode","runt…; returns make(std::move(mode),{},{},std::move(trace.snapshot),limits,ExplanationKind::runtime,; source comment (unverified): // Skip legacy node/base gauge traversal; v3 admits its own state-capture work. · [reviewed contract](#b0044) |
| [B0045 · 263–263](../../../../../src/observability/explain.cpp#L263) | Callable definition: ExplanationKind PlanExplanation::kind() const | calls data; returns data().kind · [reviewed contract](#b0045) |
| [B0046 · 264–264](../../../../../src/observability/explain.cpp#L264) | Callable definition: GaugeAvailability PlanExplanation::gauge_availability() const | calls data; returns data().gauge_availability · [reviewed contract](#b0046) |
| [B0047 · 265–265](../../../../../src/observability/explain.cpp#L265) | Callable definition: const std::optional&lt;runtime::CapturedStateGauges&gt;& PlanExplanation::gauges() const | calls data; returns data().gauges · [reviewed contract](#b0047) |
| [B0048 · 266–266](../../../../../src/observability/explain.cpp#L266) | Callable definition: const std::optional&lt;runtime::CursorObservation&gt;& PlanExplanation::cursor() const | calls data; returns data().cursor · [reviewed contract](#b0048) |
| [B0049 · 267–267](../../../../../src/observability/explain.cpp#L267) | Callable definition: const std::optional&lt;runtime::SessionStatus&gt;& PlanExplanation::session_status() const | calls data; returns data().session · [reviewed contract](#b0049) |
| [B0050 · 268–268](../../../../../src/observability/explain.cpp#L268) | Callable definition: const runtime::CompiledProgram& PlanExplanation::plan() const | calls data, plan; returns data().mode.plan() · [reviewed contract](#b0050) |
| [B0051 · 269–269](../../../../../src/observability/explain.cpp#L269) | Callable definition: const ModeDescriptor& PlanExplanation::mode() const | calls data; returns data().mode · [reviewed contract](#b0051) |
| [B0052 · 270–270](../../../../../src/observability/explain.cpp#L270) | Callable definition: HeightStatus PlanExplanation::height_status() const | calls data; returns data().status · [reviewed contract](#b0052) |
| [B0053 · 271–271](../../../../../src/observability/explain.cpp#L271) | Callable definition: std::size_t PlanExplanation::selected_height() const | calls data; returns data().height · [reviewed contract](#b0053) |
| [B0054 · 272–272](../../../../../src/observability/explain.cpp#L272) | Callable definition: const HeightEvidence& PlanExplanation::evidence() const | calls data; returns data().evidence · [reviewed contract](#b0054) |
| [B0055 · 273–273](../../../../../src/observability/explain.cpp#L273) | Callable definition: std::optional&lt;planner::VerifiedOptimum&gt; PlanExplanation::optimum() const | calls proof, data; returns proof(data().evidence) · [reviewed contract](#b0055) |
| [B0056 · 274–274](../../../../../src/observability/explain.cpp#L274) | Callable definition: const std::optional&lt;planner::CandidateSnapshot&gt;& PlanExplanation::family() const | calls data; returns data().family · [reviewed contract](#b0056) |
| [B0057 · 275–275](../../../../../src/observability/explain.cpp#L275) | Callable definition: const std::optional&lt;runtime::ObservationSnapshot&gt;& PlanExplanation::observation() const | calls data; returns data().observation · [reviewed contract](#b0057) |
| [B0058 · 276–276](../../../../../src/observability/explain.cpp#L276) | Closes surrounding scope/type. | source comment (unverified): // namespace crown::observability · [reviewed contract](#b0058) |

## B0001

[Lines 1–9](../../../../../src/observability/explain.cpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L1-L9:sha256:f83bbc9e23b1cd17e3aa3f15198131d244dc5bf0b1cf24a295e0d3ab6cd1f5a1
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Imports compile-time dependencies (crown/observability/explain.hpp, crown/resource/ownership.hpp, crown/api/error.hpp, algorithm, type_traits, utility) and opens crown::observability scope for the declarations or definitions that follow. |
| inputs / outputs | No runtime inputs/outputs are declared by the import/scope lines themselves. |
| invariants | The listed headers and namespace membership determine compile-time name availability; any API behavior belongs to the declarations/definitions that follow. |
| ownership | No object ownership is created by the imports or namespace tokens. |
| failure | No runtime failure path. Missing/incompatible dependencies or a violated compile-time constraint fail translation/linking. |
| cost | Compile/preprocessor work only; no new per-operation runtime overhead. |
| Design | [src/observability/explain.cpp](../../../../../src/observability/explain.cpp), [docs/code_specs/files/src/observability/explain.cpp.md](explain.cpp.md), [docs/observability.md](../../../../observability.md), [docs/statistics.md](../../../../statistics.md) |

## B0002

[Lines 10–12](../../../../../src/observability/explain.cpp#L10); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void require(bool condition,const char* code,const char* message)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Enforce one explicit typed-report admission predicate. |
| inputs / outputs | True returns; false constructs Error with supplied category and message. |
| invariants | Used for validity/binding/resource gates, not exception-driven success or a rollback framework. |
| ownership | Borrows immutable source/report metadata synchronously; only local result/output state changes. Does not advance a producer, runtime, cursor, journal or work allowance. |
| failure | Throws supplied Error; diagnostic allocation can itself fail before any report publication. |
| cost | Fixed successful branch; diagnostic construction/throw only on rejection. |
| Design | [include/crown/observability/explain.hpp](../../../../../include/crown/observability/explain.hpp), [docs/observability.md §Reports, ownership, and committed gauges](../../../../observability.md) |

## B0003

[Lines 13–17](../../../../../src/observability/explain.cpp#L13); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
template<class A,class B,class Equal> bool same_range(const A& a,const B& b,Equal equal)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Compare two ordered indexed ranges using a supplied field equality. |
| inputs / outputs | Size mismatch returns false; otherwise stops at first unequal pair. |
| invariants | Caller supplies immutable size/index ranges and pure comparison; no reordering, canonicalization or alpha-equivalence. |
| ownership | Borrows immutable source/report metadata synchronously; only local result/output state changes. Does not advance a producer, runtime, cursor, journal or work allowance. |
| failure | No explicit throw; element/equality contract faults propagate without mutation. |
| cost | O(compared elements plus their scalar/string comparison cost), early exit, no helper-owned allocation. |
| Design | [include/crown/observability/explain.hpp](../../../../../include/crown/observability/explain.hpp), [docs/observability.md §Reports, ownership, and committed gauges](../../../../observability.md) |

## B0004

[Lines 18–18](../../../../../src/observability/explain.cpp#L18); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
template<class A,class B> bool equal_items(const A& a,const B& b)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Compare ordered item ranges across ordinary/native representations. |
| inputs / outputs | std::ranges::equal tests exact sequence equality. |
| invariants | Preserves length/order/repeated IDs; does not compare a digest or unordered set. |
| ownership | Borrows immutable source/report metadata synchronously; only local result/output state changes. Does not advance a producer, runtime, cursor, journal or work allowance. |
| failure | Underlying range/element failures propagate; no explicit error allocation on success. |
| cost | O(compared items and their comparison widths), no copied range. |
| Design | [include/crown/observability/explain.hpp](../../../../../include/crown/observability/explain.hpp), [docs/observability.md §Reports, ownership, and committed gauges](../../../../observability.md) |

## B0005

[Lines 19–21](../../../../../src/observability/explain.cpp#L19); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
template<class A,class B> bool equal_optional_items(const A& a,const B& b)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Compare both presence and contents of optional ordered sequences. |
| inputs / outputs | Equal engagement plus equal_items for present values yields true. |
| invariants | Absent and present-empty remain different; claimed tree metadata therefore cannot be silently dropped. |
| ownership | Borrows immutable source/report metadata synchronously; only local result/output state changes. Does not advance a producer, runtime, cursor, journal or work allowance. |
| failure | Underlying comparison errors propagate; no owner mutation. |
| cost | Fixed optional checks plus present sequence comparison, no allocation. |
| Design | [include/crown/observability/explain.hpp](../../../../../include/crown/observability/explain.hpp), [docs/observability.md §Reports, ownership, and committed gauges](../../../../observability.md) |

## B0006

[Lines 22–31](../../../../../src/observability/explain.cpp#L22); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
template<class A,class B> bool same_constraint(const A& a,const B& b)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Compare exact admitted UNIQUE or foreign-key metadata across catalog carriers. |
| inputs / outputs | Variant index/name/ordered columns/status must match; foreign keys additionally match referenced table/columns. |
| invariants | Admitted variants are not valueless. Trust status and reference column ordering are semantic binding input, not an optimization hint to ignore. |
| ownership | Borrows immutable source/report metadata synchronously; only local result/output state changes. Does not advance a producer, runtime, cursor, journal or work allowance. |
| failure | No explicit throw for valid catalogs; invalid variant access propagates rather than inventing matching metadata. |
| cost | O(column IDs and name bytes), early exit, borrowed comparison only. |
| Design | [include/crown/ir/model.hpp](../../../../../include/crown/ir/model.hpp), [include/crown/observability/explain.hpp](../../../../../include/crown/observability/explain.hpp), [docs/observability.md §Reports, ownership, and committed gauges](../../../../observability.md) |

## B0007

[Lines 32–33](../../../../../src/observability/explain.cpp#L32); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L32-L33:sha256:8586bf78f155c81c8e5c910bfcabc0a81eafbbfca950b4293fced06e7c08538f
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Design note for adjacent code: Exact ordered metadata, including hints/statistics and constraint status; compare borrowed carriers directly, without JSON, hashes or deep exports. This is caller guidance recorded as prose, not an executable result. |
| inputs / outputs | No runtime interface is implemented by these comment-only lines. They sit at src/observability/explain.cpp lines 30-35; the surrounding declaration/body defines its own inputs and outputs. |
| invariants | The words record the intended use boundary only. They do not add a guard, proof, capability, transaction, durability guarantee, or account charge; verify behavior in the referenced implementation. |
| ownership | Comment text owns no data. Object lifetimes, borrows, and account attribution remain those of the adjacent source objects and their constructors. |
| failure | No failure path is implemented here. Any mentioned failure or recovery rule belongs to the adjacent operation and its existing error carrier. |
| cost | No runtime work is performed by these lines; any cost/bound in the note is not certified by this comment-only card. |
| Design | [src/observability/explain.cpp](../../../../../src/observability/explain.cpp), [docs/code_specs/files/src/observability/explain.cpp.md](explain.cpp.md), [docs/observability.md](../../../../observability.md), [docs/statistics.md](../../../../statistics.md) |

## B0008

[Lines 34–47](../../../../../src/observability/explain.cpp#L34); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
template<class A,class B> bool same_catalog(const A& a,const B& b)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Compare complete ordered catalog identity for proof binding. |
| inputs / outputs | Checks version, ordered table/source versions, full column types/names/nullability/collation/typemods, constraints, statistics and key hints. |
| invariants | Catalog metadata is exact, not merely equivalent row layout or matching hash; ordinary SearchBinding and immutable program views are compared directly without export/copy. |
| ownership | Borrows immutable source/report metadata synchronously; only local result/output state changes. Does not advance a producer, runtime, cursor, journal or work allowance. |
| failure | Access, binding, encoding, resource or allocation errors propagate. Local RAII releases partial result/output; no producer or committed runtime state is rolled back or published. |
| cost | O(compared catalog metadata and string/column-list bytes), no helper-owned allocation or catalog rewrite. |
| Design | [include/crown/ir/model.hpp](../../../../../include/crown/ir/model.hpp), [include/crown/ir/program_model.hpp](../../../../../include/crown/ir/program_model.hpp), [include/crown/observability/explain.hpp](../../../../../include/crown/observability/explain.hpp), [docs/observability.md §Reports, ownership, and committed gauges](../../../../observability.md) |

## B0009

[Lines 48–51](../../../../../src/observability/explain.cpp#L48); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
template<class Scalar> storage::ScalarView scalar_view(const Scalar& value)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Borrow a common scalar representation for cross-carrier equality. |
| inputs / outputs | Ordinary Value delegates storage::borrow_scalar; native ScalarView passes through by value. |
| invariants | String bytes remain borrowed; date/int/bool/InlineDecimal are inline. No owning Decimal/string export or normalization is introduced. |
| ownership | Returned string view needs original scalar owner; caller compares it synchronously. |
| failure | Malformed/valueless scalar contract failures propagate from the borrowed conversion. |
| cost | Fixed alternative dispatch/inline bounded decimal copy, no successful payload allocation. |
| Design | [include/crown/storage/accounted_row.hpp](../../../../../include/crown/storage/accounted_row.hpp) |

## B0010

[Lines 52–57](../../../../../src/observability/explain.cpp#L52); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
template<class A,class B> bool same_term(const A& a,const B& b)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Compare exact query-term alternatives across ordinary/native carriers. |
| inputs / outputs | Variant kind must match; variables compare ID, constants compare borrowed scalar, ignored-column markers match. |
| invariants | No variable renaming, coercion, string copy or ignored-column-to-constant rewrite. |
| ownership | Borrows immutable source/report metadata synchronously; only local result/output state changes. Does not advance a producer, runtime, cursor, journal or work allowance. |
| failure | Access, binding, encoding, resource or allocation errors propagate. Local RAII releases partial result/output; no producer or committed runtime state is rolled back or published. |
| cost | Fixed variant dispatch plus scalar-width comparison, no owning conversion. |
| Design | [include/crown/ir/model.hpp](../../../../../include/crown/ir/model.hpp), [include/crown/ir/program_model.hpp](../../../../../include/crown/ir/program_model.hpp), [include/crown/observability/explain.hpp](../../../../../include/crown/observability/explain.hpp), [docs/observability.md §Reports, ownership, and committed gauges](../../../../observability.md) |

## B0011

[Lines 58–65](../../../../../src/observability/explain.cpp#L58); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
template<class A,class B> bool same_query(const A& a,const B& b)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Compare the exact original core query used by height evidence. |
| inputs / outputs | Checks contradiction flag, ordered variable names/types, atom occurrence/table/terms, ordered head variables and aliases. |
| invariants | Equal semantics under renaming/reordering do not authorize evidence reuse. SQL source/output adapters remain part of already admitted plan, not reconstructed from a report. |
| ownership | Borrows immutable source/report metadata synchronously; only local result/output state changes. Does not advance a producer, runtime, cursor, journal or work allowance. |
| failure | Access, binding, encoding, resource or allocation errors propagate. Local RAII releases partial result/output; no producer or committed runtime state is rolled back or published. |
| cost | O(query/term/head metadata and constant/name bytes), borrowed early-exit comparison. |
| Design | [include/crown/ir/model.hpp](../../../../../include/crown/ir/model.hpp), [docs/observability.md §Height, cost, and proof scope](../../../../observability.md), [docs/planner_proofs.md §P06 retained execution and authority](../../../../planner_proofs.md) |

## B0012

[Lines 66–66](../../../../../src/observability/explain.cpp#L66); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L66-L66:sha256:37c5dbec7aaaf7abdc4db796ac9a171ab3ec972bd0d635ba11289adba34cf1c7
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Design note for adjacent code: Claim metadata and ordering are part of this exact tree comparison. This is caller guidance recorded as prose, not an executable result. |
| inputs / outputs | No runtime interface is implemented by these comment-only lines. They sit at src/observability/explain.cpp lines 64-68; the surrounding declaration/body defines its own inputs and outputs. |
| invariants | The words record the intended use boundary only. They do not add a guard, proof, capability, transaction, durability guarantee, or account charge; verify behavior in the referenced implementation. |
| ownership | Comment text owns no data. Object lifetimes, borrows, and account attribution remain those of the adjacent source objects and their constructors. |
| failure | No failure path is implemented here. Any mentioned failure or recovery rule belongs to the adjacent operation and its existing error carrier. |
| cost | No runtime work is performed by these lines; any cost/bound in the note is not certified by this comment-only card. |
| Design | [src/observability/explain.cpp](../../../../../src/observability/explain.cpp), [docs/code_specs/files/src/observability/explain.cpp.md](explain.cpp.md), [docs/observability.md](../../../../observability.md), [docs/statistics.md](../../../../statistics.md) |

## B0013

[Lines 67–73](../../../../../src/observability/explain.cpp#L67); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
template<class A,class B> bool same_tree(const A& a,const B& b)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Compare the selected tree exactly with a typed incumbent/candidate tree. |
| inputs / outputs | Checks root, optional claimed connex/height, ordered node IDs/kinds/scopes/children/occurrences and optional claimed separators. |
| invariants | Includes claim metadata and ordering, not only graph shape. This equality is separate from independent tree validation and minimum-height proof. |
| ownership | Borrows immutable source/report metadata synchronously; only local result/output state changes. Does not advance a producer, runtime, cursor, journal or work allowance. |
| failure | Access, binding, encoding, resource or allocation errors propagate. Local RAII releases partial result/output; no producer or committed runtime state is rolled back or published. |
| cost | O(tree nodes and stored ID/label arrays), no graph clone or recognizer invocation. |
| Design | [docs/observability.md §Height, cost, and proof scope](../../../../observability.md), [docs/planner_proofs.md §P06 retained execution and authority](../../../../planner_proofs.md) |

## B0014

[Lines 74–77](../../../../../src/observability/explain.cpp#L74); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void binding(const runtime::CompiledProgram& plan,const planner::SearchBinding& value)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Bind typed search evidence to the actual compiled core catalog/query. |
| inputs / outputs | Requires a valid SearchBinding plus complete same_catalog and same_query against plan core metadata. |
| invariants | No JSON flag, digest, alpha-equivalence or caller-supplied source label can substitute for exact typed binding. |
| ownership | Borrows immutable source/report metadata synchronously; only local result/output state changes. Does not advance a producer, runtime, cursor, journal or work allowance. |
| failure | explain_binding on invalid/mismatched binding; borrowed values remain unchanged. |
| cost | O(compared catalog/query bytes), no deep copy or certificate replay. |
| Design | [include/crown/observability/explain.hpp](../../../../../include/crown/observability/explain.hpp), [docs/observability.md §Reports, ownership, and committed gauges](../../../../observability.md), [docs/observability.md §Height, cost, and proof scope](../../../../observability.md), [docs/planner_proofs.md §P06 retained execution and authority](../../../../planner_proofs.md) |

## B0015

[Lines 78–84](../../../../../src/observability/explain.cpp#L78); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void context(const runtime::CompiledProgram& plan,const planner::CandidateContext& value)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Require candidate context to match selected physical policy. |
| inputs / outputs | Checks mixed_full_row_set_v1 update profile, arithmetic/planner/optimization/cost strings and structural-tree-key-v1 canonicalization. |
| invariants | Matching tree shape alone cannot reuse a candidate/family under a different policy context. This is compatibility, not cost-model optimality evidence. |
| ownership | Borrows immutable source/report metadata synchronously; only local result/output state changes. Does not advance a producer, runtime, cursor, journal or work allowance. |
| failure | explain_context on any context mismatch before report publication. |
| cost | Fixed profile checks plus policy string bytes. |
| Design | [include/crown/planner/candidates.hpp](../../../../../include/crown/planner/candidates.hpp), [docs/observability.md §Height, cost, and proof scope](../../../../observability.md), [docs/planner_proofs.md §P06 retained execution and authority](../../../../planner_proofs.md) |

## B0016

[Lines 85–89](../../../../../src/observability/explain.cpp#L85); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::optional<planner::VerifiedOptimum> proof(const HeightEvidence& evidence)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Extract genuine original minimum proof authority from HeightEvidence. |
| inputs / outputs | VerifiedOptimum returns itself; MinimumHeightCandidate returns original_proof; upper-only/monostate returns none. |
| invariants | A validated incumbent is an upper witness and cannot mint a minimum. A candidate retains original proof rather than relying on candidate family exhaustion. |
| ownership | Returned optional retains the immutable original proof owner; it may have a separate pre-existing allocation authority. |
| failure | Invalid moved-from candidate/proof access can propagate; no new authority is fabricated. |
| cost | Fixed variant tests and owning proof-handle copy, no replay/certificate traversal. |
| Design | [docs/observability.md §Height, cost, and proof scope](../../../../observability.md), [docs/planner_proofs.md §P06 retained execution and authority](../../../../planner_proofs.md) |

## B0017

[Lines 90–90](../../../../../src/observability/explain.cpp#L90); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L90-L90:sha256:412ca345ccf75bf9c0806bce695be8de808b79984251a7a54d202cf6101dd451
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Closes the enclosing implementation scope at this source boundary; this is a lexical delimiter, not an operation. |
| inputs / outputs | No runtime input or output. Declarations following the span leave the preceding C++ scope. |
| invariants | The delimiter ends the preceding scope's visibility/linkage region; it adds no validation, publication, ownership transfer, or runtime authority. |
| ownership | The delimiter adds no owner. If it ends a function/block with live automatic objects, their normal destructors release those objects; namespace and type-definition closes change no existing object's lifetime. |
| failure | No explicit failure translation or catch is added. If a function/block exit destroys automatic objects, exception behavior follows those destructors; namespace/type closes have no runtime failure path. |
| cost | The delimiter adds no algorithmic work. A function/block exit can run existing automatic-object destructors and cleanup; namespace/type closes have no runtime cost. |
| Design | [src/observability/explain.cpp](../../../../../src/observability/explain.cpp), [docs/code_specs/files/src/observability/explain.cpp.md](explain.cpp.md), [docs/observability.md](../../../../observability.md), [docs/statistics.md](../../../../statistics.md) |

## B0018

[Lines 91–100](../../../../../src/observability/explain.cpp#L91); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct ModeDescriptor::Data
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Own immutable mode metadata independently of the mutable runtime facade. |
| inputs / outputs | Data retains compiled program, owner/sequence/state/presence, optional requested options/profile and a running flag; constructor starts compile-only. |
| invariants | plan keeps actual account/schema alive. Live/session factories populate consistent option/profile metadata; running denotes retained native state and is not SessionState::running. |
| ownership | Shared const Data owns program and metadata copies; mode/profile text and aliases retain their documented original lifetimes. |
| failure | Factory allocation can fail before publishing this owner; no runtime state changes. |
| cost | One funded shared Data/control plus fixed metadata/owning aliases; no mutable runtime pointer. |
| Design | [docs/observability.md §Native retained report ownership](../../../../observability.md), [docs/memory_accounts.md §Native retained trace, gauge and report graphs](../../../../memory_accounts.md) |

## B0019

[Lines 101–101](../../../../../src/observability/explain.cpp#L101); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
ModeDescriptor::ModeDescriptor(std::shared_ptr<const Data> value):data_(std::move(value))
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Adopt the already constructed immutable mode Data owner. |
| inputs / outputs | Moves a shared_ptr&lt;const Data&gt; into the private descriptor. |
| invariants | Only factories construct public valid descriptors; this private adoption performs no admission or snapshot scan. |
| ownership | Descriptor retains shared immutable Data; argument handle is consumed. |
| failure | No explicit failure path in this handle move. |
| cost | Fixed shared owner move, no new allocation. |
| Design | [docs/observability.md §Native retained report ownership](../../../../observability.md), [docs/memory_accounts.md §Native retained trace, gauge and report graphs](../../../../memory_accounts.md) |

## B0020

[Lines 102–102](../../../../../src/observability/explain.cpp#L102); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
const ModeDescriptor::Data& ModeDescriptor::data() const
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Gate all ModeDescriptor access on its retained owner. |
| inputs / outputs | Returns const Data& or invalid_explanation when moved-from. |
| invariants | Getters cannot silently return fabricated default owner/options after a move. |
| ownership | Borrowed reference remains valid while descriptor Data is retained. |
| failure | invalid_explanation for an empty descriptor. |
| cost | Fixed pointer gate; failure diagnostic only. |
| Design | [include/crown/observability/explain.hpp](../../../../../include/crown/observability/explain.hpp), [docs/observability.md §Reports, ownership, and committed gauges](../../../../observability.md) |

## B0021

[Lines 103–111](../../../../../src/observability/explain.cpp#L103); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
ModeDescriptor ModeDescriptor::compile_only(PhysicalPlan plan)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Build an explicit standalone compiler-only mode report from PhysicalPlan. |
| inputs / outputs | Creates standalone maximum account/work allowance, freezes immutable program metadata and funds mode capture control. |
| invariants | This compiler boundary is not an execution cap refill. Runtime captures and CompiledProgram overload use original receiving account; no update or proof search is run. |
| ownership | Returned descriptor owns standalone immutable compiled program/account, independent of input PhysicalPlan handle lifetime. |
| failure | Freeze/work/memory/allocation errors unwind local owners before descriptor publication. |
| cost | Full program metadata freeze/copy/work validation plus standalone account/control allocations. |
| Design | [docs/observability.md §Native retained report ownership](../../../../observability.md), [docs/memory_accounts.md §Native retained trace, gauge and report graphs](../../../../memory_accounts.md) |

## B0022

[Lines 112–116](../../../../../src/observability/explain.cpp#L112); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
ModeDescriptor ModeDescriptor::compile_only(runtime::CompiledProgram plan)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Build a compile-only mode report using an existing compiled program grant. |
| inputs / outputs | Retains program and funds shared mode Data under plan.account(). |
| invariants | Preserves finite original allowance and metadata; no standalone replacement account or deep program export. |
| ownership | Descriptor retains the passed program/account and metadata; it owns no mutable runtime. |
| failure | Invalid program/account or allocation failure returns no descriptor and leaves caller aliases valid. |
| cost | One funded shared Data/control plus immutable program-handle move. |
| Design | [docs/observability.md §Native retained report ownership](../../../../observability.md), [docs/memory_accounts.md §Native retained trace, gauge and report graphs](../../../../memory_accounts.md) |

## B0023

[Lines 117–124](../../../../../src/observability/explain.cpp#L117); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
ModeDescriptor ModeDescriptor::capture(const runtime::DeltaRuntime& runtime)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Capture actual DeltaRuntime mode/owner metadata under its original account. |
| inputs / outputs | Retains compiled program, marks live presence/running and copies owner/sequence/state/options/profile. |
| invariants | Caller serializes owner access; no cursor/update/proof advance or gauge/trace traversal occurs here. Requested options and resolved profile remain separate. |
| ownership | Owning immutable descriptor survives runtime destruction; it retains program/account, not the mutable runtime. |
| failure | Owner readiness/moved-from/access/allocation errors propagate without changing runtime. |
| cost | One funded shared Data/control, fixed metadata access/copies; profile producer costs remain separate. |
| Design | [include/crown/observability/explain.hpp](../../../../../include/crown/observability/explain.hpp), [docs/observability.md §Reports, ownership, and committed gauges](../../../../observability.md), [docs/observability.md §Native retained report ownership](../../../../observability.md), [docs/memory_accounts.md §Native retained trace, gauge and report graphs](../../../../memory_accounts.md) |

## B0024

[Lines 125–128](../../../../../src/observability/explain.cpp#L125); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
ModeDescriptor ModeDescriptor::capture(const runtime::QuerySession& session)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Capture session mode from the actual session metadata and lifecycle. |
| inputs / outputs | Calls session.report_metadata/status then private from_session. |
| invariants | Existing thread/reentry/exclusive caller discipline supplies a consistent capture; no supplied-plan/hash join or new lock layer. |
| ownership | Borrows immutable source/report metadata synchronously; only local result/output state changes. Does not advance a producer, runtime, cursor, journal or work allowance. |
| failure | Session thread/reentry/access or allocation failure propagates; no session mutation. |
| cost | Two guarded fixed metadata reads plus funded descriptor construction. |
| Design | [include/crown/observability/explain.hpp](../../../../../include/crown/observability/explain.hpp), [docs/observability.md §Reports, ownership, and committed gauges](../../../../observability.md) |

## B0025

[Lines 129–130](../../../../../src/observability/explain.cpp#L129); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L129-L130:sha256:ca9c31fd147a1f6b5375aae8358f9f701d1aa17a53dcb30c470d55af0b552c8e
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Design note for adjacent code: running records retained native state; a stopped session can still have it. Lifecycle presence remains a separate current/retained metadata field. This is caller guidance recorded as prose, not an executable result. |
| inputs / outputs | No runtime interface is implemented by these comment-only lines. They sit at src/observability/explain.cpp lines 127-132; the surrounding declaration/body defines its own inputs and outputs. |
| invariants | The words record the intended use boundary only. They do not add a guard, proof, capability, transaction, durability guarantee, or account charge; verify behavior in the referenced implementation. |
| ownership | Comment text owns no data. Object lifetimes, borrows, and account attribution remain those of the adjacent source objects and their constructors. |
| failure | No failure path is implemented here. Any mentioned failure or recovery rule belongs to the adjacent operation and its existing error carrier. |
| cost | No runtime work is performed by these lines; any cost/bound in the note is not certified by this comment-only card. |
| Design | [src/observability/explain.cpp](../../../../../src/observability/explain.cpp), [docs/code_specs/files/src/observability/explain.cpp.md](explain.cpp.md), [docs/observability.md](../../../../observability.md), [docs/statistics.md](../../../../statistics.md) |

## B0026

[Lines 131–139](../../../../../src/observability/explain.cpp#L131); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
ModeDescriptor ModeDescriptor::from_session(const runtime::SessionReportMetadata& meta,const runtime::SessionStatus& status)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Preserve live/stopped/released session metadata in an owning mode descriptor. |
| inputs / outputs | Copies actual retained plan/account/options/profile/owner/sequence/state and derives RuntimePresence from SessionStatus. |
| invariants | Dropped session uses retained metadata with no live state; stopped can retain native state. running=state.has_value is distinct from session actively executing input. |
| ownership | Retains original program account even after runtime release; immutable aliases may keep additional metadata alive. |
| failure | Receiving-account allocation failure returns no descriptor; supplied session metadata remains valid. |
| cost | One funded Data/control and fixed metadata/owner-handle copies. |
| Design | [include/crown/observability/explain.hpp](../../../../../include/crown/observability/explain.hpp), [docs/observability.md §Reports, ownership, and committed gauges](../../../../observability.md), [docs/observability.md §Native retained report ownership](../../../../observability.md), [docs/memory_accounts.md §Native retained trace, gauge and report graphs](../../../../memory_accounts.md) |

## B0027

[Lines 140–140](../../../../../src/observability/explain.cpp#L140); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
const runtime::CompiledProgram& ModeDescriptor::plan() const
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Read ModeDescriptor compiled plan. |
| inputs / outputs | Valid descriptor returns const CompiledProgram& retaining the admitted core/source metadata. |
| invariants | Reads the captured immutable value; does not poll mutable runtime or infer proof/cost authority. |
| ownership | Borrowed immutable program remains owned by descriptor Data. |
| failure | Empty/moved-from descriptor throws invalid_explanation through data(). |
| cost | Fixed gate/field access, no successful allocation or scan. |
| Design | [include/crown/observability/explain.hpp](../../../../../include/crown/observability/explain.hpp), [docs/observability.md §Reports, ownership, and committed gauges](../../../../observability.md) |

## B0028

[Lines 141–141](../../../../../src/observability/explain.cpp#L141); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
bool ModeDescriptor::running() const
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Read ModeDescriptor native-state presence flag. |
| inputs / outputs | Valid descriptor returns copied running Boolean; stopped sessions may still return true. |
| invariants | Reads the captured immutable value; does not poll mutable runtime or infer proof/cost authority. |
| ownership | Copied scalar; it is not SessionState::running. |
| failure | Empty/moved-from descriptor throws invalid_explanation through data(). |
| cost | Fixed gate/field access, no successful allocation or scan. |
| Design | [include/crown/observability/explain.hpp](../../../../../include/crown/observability/explain.hpp), [docs/observability.md §Reports, ownership, and committed gauges](../../../../observability.md) |

## B0029

[Lines 142–142](../../../../../src/observability/explain.cpp#L142); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::uint64_t ModeDescriptor::owner() const
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Read ModeDescriptor support owner identity. |
| inputs / outputs | Valid descriptor returns copied process-local uint64 owner. |
| invariants | Reads the captured immutable value; does not poll mutable runtime or infer proof/cost authority. |
| ownership | Copied identifier, no mutable owner pointer. |
| failure | Empty/moved-from descriptor throws invalid_explanation through data(). |
| cost | Fixed gate/field access, no successful allocation or scan. |
| Design | [include/crown/observability/explain.hpp](../../../../../include/crown/observability/explain.hpp), [docs/observability.md §Reports, ownership, and committed gauges](../../../../observability.md) |

## B0030

[Lines 143–143](../../../../../src/observability/explain.cpp#L143); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::uint64_t ModeDescriptor::sequence() const
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Read ModeDescriptor committed sequence. |
| inputs / outputs | Valid descriptor returns copied captured uint64 sequence. |
| invariants | Reads the captured immutable value; does not poll mutable runtime or infer proof/cost authority. |
| ownership | Copied scalar, no fresh live-runtime read. |
| failure | Empty/moved-from descriptor throws invalid_explanation through data(). |
| cost | Fixed gate/field access, no successful allocation or scan. |
| Design | [include/crown/observability/explain.hpp](../../../../../include/crown/observability/explain.hpp), [docs/observability.md §Reports, ownership, and committed gauges](../../../../observability.md) |

## B0031

[Lines 144–144](../../../../../src/observability/explain.cpp#L144); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::optional<runtime::DeltaState> ModeDescriptor::state() const
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Read ModeDescriptor captured Delta state. |
| inputs / outputs | Valid descriptor returns optional copied DeltaState. |
| invariants | Reads the captured immutable value; does not poll mutable runtime or infer proof/cost authority. |
| ownership | Copied optional; released metadata can be disengaged. |
| failure | Empty/moved-from descriptor throws invalid_explanation through data(). |
| cost | Fixed gate/field access, no successful allocation or scan. |
| Design | [include/crown/observability/explain.hpp](../../../../../include/crown/observability/explain.hpp), [docs/observability.md §Reports, ownership, and committed gauges](../../../../observability.md) |

## B0032

[Lines 145–145](../../../../../src/observability/explain.cpp#L145); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
RuntimePresence ModeDescriptor::presence() const
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Read ModeDescriptor runtime presence classification. |
| inputs / outputs | Valid descriptor returns copied compile_only/live/stopped_retained/released enum. |
| invariants | Reads the captured immutable value; does not poll mutable runtime or infer proof/cost authority. |
| ownership | Copied enum, separate from observation/gauge availability. |
| failure | Empty/moved-from descriptor throws invalid_explanation through data(). |
| cost | Fixed gate/field access, no successful allocation or scan. |
| Design | [include/crown/observability/explain.hpp](../../../../../include/crown/observability/explain.hpp), [docs/observability.md §Reports, ownership, and committed gauges](../../../../observability.md) |

## B0033

[Lines 146–146](../../../../../src/observability/explain.cpp#L146); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
const std::optional<runtime::DeltaOptions>& ModeDescriptor::options() const
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Read ModeDescriptor requested options. |
| inputs / outputs | Valid descriptor returns const optional&lt;DeltaOptions&gt;&. |
| invariants | Reads the captured immutable value; does not poll mutable runtime or infer proof/cost authority. |
| ownership | Borrowed immutable options within descriptor Data. |
| failure | Empty/moved-from descriptor throws invalid_explanation through data(). |
| cost | Fixed gate/field access, no successful allocation or scan. |
| Design | [include/crown/observability/explain.hpp](../../../../../include/crown/observability/explain.hpp), [docs/observability.md §Reports, ownership, and committed gauges](../../../../observability.md) |

## B0034

[Lines 147–147](../../../../../src/observability/explain.cpp#L147); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
const std::optional<runtime::DeltaRuntimeProfile>& ModeDescriptor::profile() const
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Read ModeDescriptor resolved profile. |
| inputs / outputs | Valid descriptor returns const optional&lt;DeltaRuntimeProfile&gt;&. |
| invariants | Reads the captured immutable value; does not poll mutable runtime or infer proof/cost authority. |
| ownership | Borrowed immutable profile; static text/aliases follow their original lifetime contracts. |
| failure | Empty/moved-from descriptor throws invalid_explanation through data(). |
| cost | Fixed gate/field access, no successful allocation or scan. |
| Design | [include/crown/observability/explain.hpp](../../../../../include/crown/observability/explain.hpp), [docs/observability.md §Reports, ownership, and committed gauges](../../../../observability.md) |

## B0035

[Lines 148–164](../../../../../src/observability/explain.cpp#L148); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct PlanExplanation::Data
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Own a complete immutable physical/runtime/session report graph. |
| inputs / outputs | Data retains mode, typed evidence/family, observation, kind/gauge availability, optional captured gauges/cursor/session, funded trace array and admitted height/status. |
| invariants | Mode/report controls and native captured arrays use original program account; explicitly supplied evidence/family and metadata aliases retain their own existing owners. No runtime pointer, row pin or JSON DOM is stored. |
| ownership | Shared const Data owns complete capture; trace allocator is initialized from retained program account before any optional incoming move. |
| failure | Constructor/control allocation failure unwinds private owners; no public partial report. |
| cost | One funded shared Data/control, immutable handle copies and retained trace/gauge arrays; final release can tear down the retained graph. |
| Design | [docs/observability.md §Native retained report ownership](../../../../observability.md), [docs/memory_accounts.md §Native retained trace, gauge and report graphs](../../../../memory_accounts.md) |

## B0036

[Lines 165–165](../../../../../src/observability/explain.cpp#L165); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
PlanExplanation::PlanExplanation(std::shared_ptr<const Data> value):data_(std::move(value))
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Adopt a fully prepared immutable PlanExplanation owner. |
| inputs / outputs | Moves private shared_ptr&lt;const Data&gt; into the facade. |
| invariants | Admission and capture occurred before this handle publication; no arbitrary public Data constructor. |
| ownership | Report retains its immutable Data independently of runtime/session lifetime. |
| failure | No explicit failure in this private handle move. |
| cost | Fixed shared owner move, no new allocation. |
| Design | [docs/observability.md §Native retained report ownership](../../../../observability.md), [docs/memory_accounts.md §Native retained trace, gauge and report graphs](../../../../memory_accounts.md) |

## B0037

[Lines 166–166](../../../../../src/observability/explain.cpp#L166); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
const PlanExplanation::Data& PlanExplanation::data() const
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Gate PlanExplanation getters on a retained Data owner. |
| inputs / outputs | Returns const Data& or invalid_explanation on empty/moved-from report. |
| invariants | Never invents default proof/state/trace metadata after ownership was moved. |
| ownership | Returned reference borrows report-owned immutable Data. |
| failure | invalid_explanation when report has no Data. |
| cost | Fixed shared-pointer gate. |
| Design | [include/crown/observability/explain.hpp](../../../../../include/crown/observability/explain.hpp), [docs/observability.md §Reports, ownership, and committed gauges](../../../../observability.md) |

## B0038

[Lines 167–215](../../../../../src/observability/explain.cpp#L167); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
PlanExplanation PlanExplanation::make(ModeDescriptor mode,HeightEvidence evidence,
    std::optional<planner::CandidateSnapshot> family,std::optional<runtime::ObservationSnapshot> observation,ExplainLimits limits,
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Admit exact typed plan/evidence/family and publish one owning report. |
| inputs / outputs | Checks node cap/admitted plan height, valid evidence and exact original core binding; incumbent/candidate must equal selected tree; evidence height matches selected height; family needs original proof and matching context/height. A selected MinimumHeightCandidate must have the same family as the supplied family snapshot. |
| invariants | VerifiedOptimum may retain a different original witness with the same proved minimum; candidate/incumbent require exact selected tree. Constant-false operator status without original evidence stays separate. Typed immutable plan/proof handles, not JSON/hash flags, establish authority. |
| ownership | Moves mode/evidence/family/observation/gauge/cursor/session and funded trace into shared const Data. Source proof/family owners can remain separate accounts; no mutable runtime retained. |
| failure | Resource/plan/evidence/binding/context/tree/height/family failures precede public report return; local RAII releases all prepared ownership without engine rollback. Cross-family selected evidence raises explain_family. |
| cost | O(exact catalog/query/tree/context comparisons, possibly repeated for evidence/family) plus funded report control and owning moves. This factory neither reruns validation/search/replay nor meters earlier trace/gauge capture; node cap bounds admitted tree counts only. Family comparison uses the existing owning provenance getter; copying residual trace can allocate and costs its trace size. This is cold report admission, not a runtime update hook. |
| Design | [include/crown/observability/explain.hpp](../../../../../include/crown/observability/explain.hpp), [docs/observability.md §Reports, ownership, and committed gauges](../../../../observability.md), [docs/observability.md §Height, cost, and proof scope](../../../../observability.md), [docs/planner_proofs.md §P06 retained execution and authority](../../../../planner_proofs.md), [docs/observability.md §Native retained report ownership](../../../../observability.md), [docs/memory_accounts.md §Native retained trace, gauge and report graphs](../../../../memory_accounts.md), [docs/candidate_alternatives.md](../../../../candidate_alternatives.md), [docs/meta_decompositions.md](../../../../meta_decompositions.md) |

## B0039

[Lines 216–218](../../../../../src/observability/explain.cpp#L216); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
PlanExplanation PlanExplanation::create(PhysicalPlan plan,HeightEvidence evidence,std::optional<planner::CandidateSnapshot> family,ExplainLimits limits)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Create a compiler-only physical report from an admitted PhysicalPlan. |
| inputs / outputs | Builds standalone compile-only mode, then admits evidence/family under requested node cap. |
| invariants | Standalone metadata freeze is explicit compiler work, not runtime grant replacement or certificate import. |
| ownership | Returned report owns standalone compiled metadata and supplied typed evidence aliases. |
| failure | Access, binding, encoding, resource or allocation errors propagate. Local RAII releases partial result/output; no producer or committed runtime state is rolled back or published. |
| cost | Full compiler-only program freeze plus make exact comparisons/control allocation. |
| Design | [include/crown/observability/explain.hpp](../../../../../include/crown/observability/explain.hpp), [docs/observability.md §Reports, ownership, and committed gauges](../../../../observability.md), [docs/observability.md §Native retained report ownership](../../../../observability.md), [docs/memory_accounts.md §Native retained trace, gauge and report graphs](../../../../memory_accounts.md) |

## B0040

[Lines 219–221](../../../../../src/observability/explain.cpp#L219); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
PlanExplanation PlanExplanation::create(runtime::CompiledProgram plan,HeightEvidence evidence,std::optional<planner::CandidateSnapshot> family,ExplainLimits limits)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Create a compiler-only report from existing funded immutable CompiledProgram. |
| inputs / outputs | Retains original account through compile_only(program), then admits evidence/family. |
| invariants | No hidden new allowance or mutable runtime; same typed core binding rules as PhysicalPlan form. |
| ownership | Retains existing program/account and typed evidence/family owner graph. |
| failure | Access, binding, encoding, resource or allocation errors propagate. Local RAII releases partial result/output; no producer or committed runtime state is rolled back or published. |
| cost | Funded mode/report controls plus make metadata comparisons; immutable program is shared. |
| Design | [include/crown/observability/explain.hpp](../../../../../include/crown/observability/explain.hpp), [docs/observability.md §Reports, ownership, and committed gauges](../../../../observability.md), [docs/observability.md §Native retained report ownership](../../../../observability.md), [docs/memory_accounts.md §Native retained trace, gauge and report graphs](../../../../memory_accounts.md) |

## B0041

[Lines 222–239](../../../../../src/observability/explain.cpp#L222); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
PlanExplanation PlanExplanation::capture(const runtime::DeltaRuntime& runtime,HeightEvidence evidence,std::optional<planner::CandidateSnapshot> family,ExplainLimits limits)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Capture a full legacy v2 runtime explanation at its actual owner boundary. |
| inputs / outputs | Requires C01 off, captures mode/trace/observation, validates options, classifies private work, captures committed gauges only when readable, retains latest cursor and calls make. |
| invariants | Exclusive caller discipline prevents interleaving; capture does not advance/drain. Pending state exposes no tentative gauges. C01-enabled runtime must select StatisticsExplanation. Node-limit admission happens after these capture operations. |
| ownership | Returned immutable report retains copied numeric trace/gauges/configuration/cursor/program and original account, not mutable runtime. |
| failure | Version/mode/private-owner/resource/allocation/evidence error returns no report; earlier capture allocations/scans may already have happened but runtime/attempt state remains unchanged. |
| cost | Funded mode/report controls, O(retained trace) copy and O(nodes + physical source tables) gauge arrays/maintained size reads when committed, then exact evidence comparisons. Legacy diagnostic traversal has no selected work grant; no resident-row enumeration is performed. |
| Design | [include/crown/observability/explain.hpp](../../../../../include/crown/observability/explain.hpp), [docs/observability.md §Reports, ownership, and committed gauges](../../../../observability.md), [docs/observability.md §Native retained report ownership](../../../../observability.md), [docs/memory_accounts.md §Native retained trace, gauge and report graphs](../../../../memory_accounts.md), [src/runtime/observation.cpp](../../../../../src/runtime/observation.cpp), [src/runtime/physical.cpp](../../../../../src/runtime/physical.cpp), [src/runtime/support.cpp](../../../../../src/runtime/support.cpp) |

## B0042

[Lines 240–251](../../../../../src/observability/explain.cpp#L240); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
PlanExplanation PlanExplanation::capture(const runtime::QuerySession& session,HeightEvidence evidence, std::optional<planner::CandidateSnapshot> family,ExplainLimits limits)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Capture a full legacy v2 explanation from actual QuerySession ownership. |
| inputs / outputs | Requires C01 off, captures session mode/trace/status/optional gauges/latest cursor and admits typed evidence/family. |
| invariants | Session guards/thread discipline apply to each actual read. Dropped runtime marks gauges released; live private work marks pending; stopped retained state can remain readable. No caller-supplied plan/hash binding. |
| ownership | Report can survive stop/drop/destruction using original account and captured native metadata/arrays. |
| failure | C01 version/thread/reentry/access/account/evidence errors propagate before report return; session accepted/pending state is not changed. |
| cost | Guarded metadata plus funded controls/trace and optional O(nodes + source tables) gauge arrays, then exact make comparisons; no row enumeration, update or drain. |
| Design | [include/crown/observability/explain.hpp](../../../../../include/crown/observability/explain.hpp), [docs/observability.md §Reports, ownership, and committed gauges](../../../../observability.md), [docs/observability.md §Native retained report ownership](../../../../observability.md), [docs/memory_accounts.md §Native retained trace, gauge and report graphs](../../../../memory_accounts.md), [src/runtime/session.cpp](../../../../../src/runtime/session.cpp) |

## B0043

[Lines 252–252](../../../../../src/observability/explain.cpp#L252); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
const runtime::CapturedTraceRecords& PlanExplanation::trace_records() const
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Borrow retained numeric causal trace records. |
| inputs / outputs | Returns const CapturedTraceRecords& after data() validation. |
| invariants | Records contain numeric IDs/flags, not tuple pins or complete durable history; capture disposition/truncation stays in observation. |
| ownership | Span/vector reference remains report-owned; caller keeps report owner alive. |
| failure | Moved-from report throws invalid_explanation. |
| cost | Fixed owner/field access, no copy/scan. |
| Design | [include/crown/observability/explain.hpp](../../../../../include/crown/observability/explain.hpp), [docs/observability.md §Reports, ownership, and committed gauges](../../../../observability.md) |

## B0044

[Lines 253–262](../../../../../src/observability/explain.cpp#L253); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
PlanExplanation PlanExplanation::capture_statistics_context(const runtime::DeltaRuntime& runtime,ExplainLimits limits)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Build the private runtime context used by statistics-aware v3 reporting. |
| inputs / outputs | Captures mode/trace/current observation binding and latest cursor, classifies pending state, then calls make with no evidence/family/gauges. |
| invariants | Deliberately skips legacy node/base gauge traversal; later explicit budgeted statistics capture supplies its own state facts. This private context is not exported as full legacy v2 and still retains trace ownership. |
| ownership | Retains actual program/account and captured trace/observation; consumed by private StatisticsExplanation construction. |
| failure | Mode/options/account/resource errors propagate without changing live owner; no C01-off legacy gate applies to this private path. |
| cost | Funded controls + O(retained trace) copy and fixed metadata; no legacy gauge arrays or resident-row scan. |
| Design | [include/crown/observability/explain.hpp](../../../../../include/crown/observability/explain.hpp), [docs/observability.md §Reports, ownership, and committed gauges](../../../../observability.md), [docs/observability.md §Native retained report ownership](../../../../observability.md), [docs/memory_accounts.md §Native retained trace, gauge and report graphs](../../../../memory_accounts.md), [src/observability/statistics_explain.cpp](../../../../../src/observability/statistics_explain.cpp) |

## B0045

[Lines 263–263](../../../../../src/observability/explain.cpp#L263); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
ExplanationKind PlanExplanation::kind() const
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Read PlanExplanation kind. |
| inputs / outputs | Valid report returns copied physical/runtime/session ExplanationKind. |
| invariants | Getter reads admitted captured state only; it does not advance search/runtime or upgrade proof/freshness authority. |
| ownership | Copied enum. |
| failure | Moved-from/empty report throws invalid_explanation; invalid retained typed proof contract can also propagate for optimum(). |
| cost | Fixed Data/field access; proof() at optimum additionally copies an existing immutable shared handle. No successful deep allocation. |
| Design | [include/crown/observability/explain.hpp](../../../../../include/crown/observability/explain.hpp), [docs/observability.md §Reports, ownership, and committed gauges](../../../../observability.md) |

## B0046

[Lines 264–264](../../../../../src/observability/explain.cpp#L264); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
GaugeAvailability PlanExplanation::gauge_availability() const
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Read PlanExplanation gauge availability. |
| inputs / outputs | Valid report returns copied available/compile_only/pending_private_state/runtime_released classification. |
| invariants | Getter reads admitted captured state only; it does not advance search/runtime or upgrade proof/freshness authority. |
| ownership | Copied enum; separate from optional payload. |
| failure | Moved-from/empty report throws invalid_explanation; invalid retained typed proof contract can also propagate for optimum(). |
| cost | Fixed Data/field access; proof() at optimum additionally copies an existing immutable shared handle. No successful deep allocation. |
| Design | [include/crown/observability/explain.hpp](../../../../../include/crown/observability/explain.hpp), [docs/observability.md §Reports, ownership, and committed gauges](../../../../observability.md) |

## B0047

[Lines 265–265](../../../../../src/observability/explain.cpp#L265); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
const std::optional<runtime::CapturedStateGauges>& PlanExplanation::gauges() const
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Read PlanExplanation committed gauges. |
| inputs / outputs | Valid report returns const optional&lt;CapturedStateGauges&gt;&. |
| invariants | Getter reads admitted captured state only; it does not advance search/runtime or upgrade proof/freshness authority. |
| ownership | Borrowed owning capture handle within Data; value copy uses its own native account semantics. |
| failure | Moved-from/empty report throws invalid_explanation; invalid retained typed proof contract can also propagate for optimum(). |
| cost | Fixed Data/field access; proof() at optimum additionally copies an existing immutable shared handle. No successful deep allocation. |
| Design | [include/crown/observability/explain.hpp](../../../../../include/crown/observability/explain.hpp), [docs/observability.md §Reports, ownership, and committed gauges](../../../../observability.md) |

## B0048

[Lines 266–266](../../../../../src/observability/explain.cpp#L266); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
const std::optional<runtime::CursorObservation>& PlanExplanation::cursor() const
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Read PlanExplanation latest cursor metadata. |
| inputs / outputs | Valid report returns const optional&lt;CursorObservation&gt;&. |
| invariants | Getter reads admitted captured state only; it does not advance search/runtime or upgrade proof/freshness authority. |
| ownership | Borrowed numeric snapshot, not a live cursor lease. |
| failure | Moved-from/empty report throws invalid_explanation; invalid retained typed proof contract can also propagate for optimum(). |
| cost | Fixed Data/field access; proof() at optimum additionally copies an existing immutable shared handle. No successful deep allocation. |
| Design | [include/crown/observability/explain.hpp](../../../../../include/crown/observability/explain.hpp), [docs/observability.md §Reports, ownership, and committed gauges](../../../../observability.md) |

## B0049

[Lines 267–267](../../../../../src/observability/explain.cpp#L267); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
const std::optional<runtime::SessionStatus>& PlanExplanation::session_status() const
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Read PlanExplanation session lifecycle. |
| inputs / outputs | Valid report returns const optional&lt;SessionStatus&gt;&. |
| invariants | Getter reads admitted captured state only; it does not advance search/runtime or upgrade proof/freshness authority. |
| ownership | Borrowed captured scalar/optional metadata, not a mutable session. |
| failure | Moved-from/empty report throws invalid_explanation; invalid retained typed proof contract can also propagate for optimum(). |
| cost | Fixed Data/field access; proof() at optimum additionally copies an existing immutable shared handle. No successful deep allocation. |
| Design | [include/crown/observability/explain.hpp](../../../../../include/crown/observability/explain.hpp), [docs/observability.md §Reports, ownership, and committed gauges](../../../../observability.md) |

## B0050

[Lines 268–268](../../../../../src/observability/explain.cpp#L268); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
const runtime::CompiledProgram& PlanExplanation::plan() const
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Read PlanExplanation compiled plan. |
| inputs / outputs | Valid report returns const CompiledProgram& from retained mode. |
| invariants | Getter reads admitted captured state only; it does not advance search/runtime or upgrade proof/freshness authority. |
| ownership | Borrowed immutable metadata/program/account owner. |
| failure | Moved-from/empty report throws invalid_explanation; invalid retained typed proof contract can also propagate for optimum(). |
| cost | Fixed Data/field access; proof() at optimum additionally copies an existing immutable shared handle. No successful deep allocation. |
| Design | [include/crown/observability/explain.hpp](../../../../../include/crown/observability/explain.hpp), [docs/observability.md §Reports, ownership, and committed gauges](../../../../observability.md) |

## B0051

[Lines 269–269](../../../../../src/observability/explain.cpp#L269); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
const ModeDescriptor& PlanExplanation::mode() const
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Read PlanExplanation mode descriptor. |
| inputs / outputs | Valid report returns const ModeDescriptor&. |
| invariants | Getter reads admitted captured state only; it does not advance search/runtime or upgrade proof/freshness authority. |
| ownership | Borrowed immutable owning descriptor within Data. |
| failure | Moved-from/empty report throws invalid_explanation; invalid retained typed proof contract can also propagate for optimum(). |
| cost | Fixed Data/field access; proof() at optimum additionally copies an existing immutable shared handle. No successful deep allocation. |
| Design | [include/crown/observability/explain.hpp](../../../../../include/crown/observability/explain.hpp), [docs/observability.md §Reports, ownership, and committed gauges](../../../../observability.md) |

## B0052

[Lines 270–270](../../../../../src/observability/explain.cpp#L270); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
HeightStatus PlanExplanation::height_status() const
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Read PlanExplanation height authority status. |
| inputs / outputs | Valid report returns copied checked_upper/verified_original_minimum/checked_constant_operator. |
| invariants | Getter reads admitted captured state only; it does not advance search/runtime or upgrade proof/freshness authority. |
| ownership | Copied enum; does not run a verifier. |
| failure | Moved-from/empty report throws invalid_explanation; invalid retained typed proof contract can also propagate for optimum(). |
| cost | Fixed Data/field access; proof() at optimum additionally copies an existing immutable shared handle. No successful deep allocation. |
| Design | [include/crown/observability/explain.hpp](../../../../../include/crown/observability/explain.hpp), [docs/observability.md §Reports, ownership, and committed gauges](../../../../observability.md) |

## B0053

[Lines 271–271](../../../../../src/observability/explain.cpp#L271); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::size_t PlanExplanation::selected_height() const
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Read PlanExplanation selected native height. |
| inputs / outputs | Valid report returns copied admitted size_t height. |
| invariants | Getter reads admitted captured state only; it does not advance search/runtime or upgrade proof/freshness authority. |
| ownership | Copied scalar in declared executable/query scope. |
| failure | Moved-from/empty report throws invalid_explanation; invalid retained typed proof contract can also propagate for optimum(). |
| cost | Fixed Data/field access; proof() at optimum additionally copies an existing immutable shared handle. No successful deep allocation. |
| Design | [include/crown/observability/explain.hpp](../../../../../include/crown/observability/explain.hpp), [docs/observability.md §Reports, ownership, and committed gauges](../../../../observability.md) |

## B0054

[Lines 272–272](../../../../../src/observability/explain.cpp#L272); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
const HeightEvidence& PlanExplanation::evidence() const
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Read PlanExplanation typed height evidence. |
| inputs / outputs | Valid report returns const HeightEvidence&. |
| invariants | Getter reads admitted captured state only; it does not advance search/runtime or upgrade proof/freshness authority. |
| ownership | Borrowed typed immutable owner variant; diagnostic JSON cannot replace it. |
| failure | Moved-from/empty report throws invalid_explanation; invalid retained typed proof contract can also propagate for optimum(). |
| cost | Fixed Data/field access; proof() at optimum additionally copies an existing immutable shared handle. No successful deep allocation. |
| Design | [include/crown/observability/explain.hpp](../../../../../include/crown/observability/explain.hpp), [docs/observability.md §Reports, ownership, and committed gauges](../../../../observability.md) |

## B0055

[Lines 273–273](../../../../../src/observability/explain.cpp#L273); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::optional<planner::VerifiedOptimum> PlanExplanation::optimum() const
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Read PlanExplanation original minimum proof. |
| inputs / outputs | Valid report returns optional VerifiedOptimum from proof(data().evidence). |
| invariants | Getter reads admitted captured state only; it does not advance search/runtime or upgrade proof/freshness authority. |
| ownership | Owning immutable proof handle copy can outlive report. |
| failure | Moved-from/empty report throws invalid_explanation; invalid retained typed proof contract can also propagate for optimum(). |
| cost | Fixed Data/field access; proof() at optimum additionally copies an existing immutable shared handle. No successful deep allocation. |
| Design | [include/crown/observability/explain.hpp](../../../../../include/crown/observability/explain.hpp), [docs/observability.md §Reports, ownership, and committed gauges](../../../../observability.md) |

## B0056

[Lines 274–274](../../../../../src/observability/explain.cpp#L274); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
const std::optional<planner::CandidateSnapshot>& PlanExplanation::family() const
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Read PlanExplanation candidate-family snapshot. |
| inputs / outputs | Valid report returns const optional&lt;CandidateSnapshot&gt;&. |
| invariants | Getter reads admitted captured state only; it does not advance search/runtime or upgrade proof/freshness authority. |
| ownership | Borrowed immutable snapshot owner, without global cost completeness. |
| failure | Moved-from/empty report throws invalid_explanation; invalid retained typed proof contract can also propagate for optimum(). |
| cost | Fixed Data/field access; proof() at optimum additionally copies an existing immutable shared handle. No successful deep allocation. |
| Design | [include/crown/observability/explain.hpp](../../../../../include/crown/observability/explain.hpp), [docs/observability.md §Reports, ownership, and committed gauges](../../../../observability.md) |

## B0057

[Lines 275–275](../../../../../src/observability/explain.cpp#L275); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
const std::optional<runtime::ObservationSnapshot>& PlanExplanation::observation() const
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Read PlanExplanation observation snapshot. |
| inputs / outputs | Valid report returns const optional&lt;ObservationSnapshot&gt;&. |
| invariants | Getter reads admitted captured state only; it does not advance search/runtime or upgrade proof/freshness authority. |
| ownership | Borrowed owning numeric/configuration snapshot, not live observer state. |
| failure | Moved-from/empty report throws invalid_explanation; invalid retained typed proof contract can also propagate for optimum(). |
| cost | Fixed Data/field access; proof() at optimum additionally copies an existing immutable shared handle. No successful deep allocation. |
| Design | [include/crown/observability/explain.hpp](../../../../../include/crown/observability/explain.hpp), [docs/observability.md §Reports, ownership, and committed gauges](../../../../observability.md) |

## B0058

[Lines 276–276](../../../../../src/observability/explain.cpp#L276); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L276-L276:sha256:15ac899d66e81241a264aee901694a508b7370147772ee46125ef9b6e5307ec5
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Closes the namespace crown::observability at this source boundary; this is a lexical delimiter, not an operation. |
| inputs / outputs | No runtime input or output. Declarations following the span leave the preceding C++ scope. |
| invariants | The delimiter ends the preceding scope's visibility/linkage region; it adds no validation, publication, ownership transfer, or runtime authority. |
| ownership | The delimiter adds no owner. If it ends a function/block with live automatic objects, their normal destructors release those objects; namespace and type-definition closes change no existing object's lifetime. |
| failure | No explicit failure translation or catch is added. If a function/block exit destroys automatic objects, exception behavior follows those destructors; namespace/type closes have no runtime failure path. |
| cost | The delimiter adds no algorithmic work. A function/block exit can run existing automatic-object destructors and cleanup; namespace/type closes have no runtime cost. |
| Design | [src/observability/explain.cpp](../../../../../src/observability/explain.cpp), [docs/code_specs/files/src/observability/explain.cpp.md](explain.cpp.md), [docs/observability.md](../../../../observability.md), [docs/statistics.md](../../../../statistics.md) |
