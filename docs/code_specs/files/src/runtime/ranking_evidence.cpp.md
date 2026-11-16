# `src/runtime/ranking_evidence.cpp` — block usage map

[Source](../../../../../src/runtime/ranking_evidence.cpp) · [Source index](../../../README.md) · [Subsystem contracts](../../../subsystem_contracts.md) · [Reviewed primitives](../../../primitives.md)

Capture bounded distributions, workload counters, owner memory and explain observations without mislabeling partial information as exact.

Snapshot SHA-256: `3ab97e75cb18e25d2049c1ca0c257f1f32f77da8d7ef38912606ef5d2477ebbf`. 246 lines partitioned into 46 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [statistics](../../../subsystem_contracts.md#statistics). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/statistics.md](../../../../statistics.md), [docs/observability.md](../../../../observability.md), [docs/memory_reports.md](../../../../memory_reports.md), [docs/ranking_evaluation.md](../../../../ranking_evaluation.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–12](../../../../../src/runtime/ranking_evidence.cpp#L1) | Imports dependencies; declares namespace scope; declares values/defaults or compile-time conditions. | growth new · [reviewed contract](#b0001) |
| [B0002 · 13–16](../../../../../src/runtime/ranking_evidence.cpp#L13) | Type/record definition: struct OwnerAccess | returns owner.compiled_program(); owner.compiled_program() · [reviewed contract](#b0002) |
| [B0003 · 17–23](../../../../../src/runtime/ranking_evidence.cpp#L17) | Type/record definition: struct Data |  · [reviewed contract](#b0003) |
| [B0004 · 24–24](../../../../../src/runtime/ranking_evidence.cpp#L24) | Type/record definition: struct Factory | returns RuntimeEvidence(std::move(value)) · [reviewed contract](#b0004) |
| [B0005 · 25–25](../../../../../src/runtime/ranking_evidence.cpp#L25) | Closes surrounding scope/type. |  · [reviewed contract](#b0005) |
| [B0006 · 26–26](../../../../../src/runtime/ranking_evidence.cpp#L26) | Callable definition: const pr::Evidence& RuntimeEvidence::inputs() const noexcept | calls ; returns data_-&gt;inputs · [reviewed contract](#b0006) |
| [B0007 · 27–27](../../../../../src/runtime/ranking_evidence.cpp#L27) | Callable definition: const std::optional&lt;statistics::CombinedCapture&gt;& RuntimeEvidence::captured() const noexcept | calls ; returns data_-&gt;captured · [reviewed contract](#b0007) |
| [B0008 · 28–28](../../../../../src/runtime/ranking_evidence.cpp#L28) | Callable definition: const std::optional&lt;SessionStatisticsContext&gt;& RuntimeEvidence::session_context() const noexcept | calls ; returns data_-&gt;session · [reviewed contract](#b0008) |
| [B0009 · 29–31](../../../../../src/runtime/ranking_evidence.cpp#L29) | declares namespace scope; declares aliases; declares types or opens a type body; declares values/defaults or compile-time conditions. |  · [reviewed contract](#b0009) |
| [B0010 · 32–34](../../../../../src/runtime/ranking_evidence.cpp#L32) | Callable definition: template&lt;class T&gt; resource::MemoryAllocator&lt;T&gt; scratch_allocator(const resource::MemoryAccount& account) | calls ; returns resource::MemoryAllocator&lt;T&gt;(account,resource::MemoryPurpose::scratch,rd::evidence_memory_owner) · [reviewed contract](#b0010) |
| [B0011 · 35–35](../../../../../src/runtime/ranking_evidence.cpp#L35) | Callable definition: void require(bool value,pr::Stop stop=pr::Stop::internal_error) | calls ; guard void require(bool value,pr::Stop stop=pr::Stop::internal_error){if(!value){throw rd::Failure{stop};… · [reviewed contract](#b0011) |
| [B0012 · 36–36](../../../../../src/runtime/ranking_evidence.cpp#L36) | Callable definition: CompiledProgram actual_plan(const PhysicalRuntime& owner) | calls detail::OwnerAccess::program; returns detail::OwnerAccess::program(owner) · [reviewed contract](#b0012) |
| [B0013 · 37–37](../../../../../src/runtime/ranking_evidence.cpp#L37) | Callable definition: CompiledProgram actual_plan(const DeltaRuntime& owner) | calls detail::OwnerAccess::program; returns detail::OwnerAccess::program(owner) · [reviewed contract](#b0013) |
| [B0014 · 38–38](../../../../../src/runtime/ranking_evidence.cpp#L38) | Callable definition: CompiledProgram actual_plan(const QuerySession& owner) | calls report_metadata, plan; returns owner.report_metadata().plan() · [reviewed contract](#b0014) |
| [B0015 · 39–39](../../../../../src/runtime/ranking_evidence.cpp#L39) | Type/record definition: struct NativeCapture |  · [reviewed contract](#b0015) |
| [B0016 · 40–40](../../../../../src/runtime/ranking_evidence.cpp#L40) | Callable definition: NativeCapture actual_capture(const PhysicalRuntime& owner,statistics::OwnerRequestView r,statistics::Limits l) | calls capture_combined_statistics_view; returns {owner.capture_combined_statistics_view(r,l),{}} · [reviewed contract](#b0016) |
| [B0017 · 41–41](../../../../../src/runtime/ranking_evidence.cpp#L41) | Callable definition: NativeCapture actual_capture(const DeltaRuntime& owner,statistics::OwnerRequestView r,statistics::Limits l) | calls capture_combined_statistics_view; returns {owner.capture_combined_statistics_view(r,l),{}} · [reviewed contract](#b0017) |
| [B0018 · 42–44](../../../../../src/runtime/ranking_evidence.cpp#L42) | Callable definition: NativeCapture actual_capture(const QuerySession& owner,statistics::OwnerRequestView r,statistics::Limits l) | calls capture_statistics_context_view, combined, std::move; returns {context.combined(),std::move(context)} · [reviewed contract](#b0018) |
| [B0019 · 45–45](../../../../../src/runtime/ranking_evidence.cpp#L45) | Callable definition: std::optional&lt;statistics::Freshness&gt; actual_freshness(const PhysicalRuntime& owner,const statistics::OwnerCapture& c) | calls statistics_freshness; returns owner.statistics_freshness(c,0) · [reviewed contract](#b0019) |
| [B0020 · 46–46](../../../../../src/runtime/ranking_evidence.cpp#L46) | Callable definition: std::optional&lt;statistics::Freshness&gt; actual_freshness(const DeltaRuntime& owner,const statistics::OwnerCapture& c) | calls statistics_freshness; returns owner.statistics_freshness(c,0) · [reviewed contract](#b0020) |
| [B0021 · 47–47](../../../../../src/runtime/ranking_evidence.cpp#L47) | Callable definition: std::optional&lt;statistics::Freshness&gt; actual_freshness(const QuerySession& owner,const statistics::OwnerCapture& c) | calls statistics_freshness; returns owner.statistics_freshness(c,0) · [reviewed contract](#b0021) |
| [B0022 · 48–52](../../../../../src/runtime/ranking_evidence.cpp#L48) | Callable definition: pr::ModeIdentity modes(const workload::ModeFacts& m) | calls ; returns {m.delta_owner,static_cast&lt;std::uint64_t&gt;(m.requested_mode),static_cast&lt;std::uint64_t&gt;(m.resolved_m… · [reviewed contract](#b0022) |
| [B0023 · 53–58](../../../../../src/runtime/ranking_evidence.cpp#L53) | Callable definition: pr::EvidenceIdentity identity(const statistics::CombinedCapture& c) | calls workload, stamp, options, modes; returns {s.owner.value,s.committed_epoch,s.interval_start_epoch,s.reset_generation,s.configuration_generati… · [reviewed contract](#b0023) |
| [B0024 · 59–59](../../../../../src/runtime/ranking_evidence.cpp#L59) | Callable definition: Reasons interval_saturated(const workload::Snapshot& s) | calls stamp, reason; returns x.reset_saturated \|\| x.configuration_saturated \|\| x.segment_saturated?reason(Reason::interval_satur… · [reviewed contract](#b0024) |
| [B0025 · 60–60](../../../../../src/runtime/ranking_evidence.cpp#L60) | declares aliases; declares values/defaults or compile-time conditions. |  · [reviewed contract](#b0025) |
| [B0026 · 61–102](../../../../../src/runtime/ranking_evidence.cpp#L61) | Callable definition: Census census(const workload::Snapshot& s,rd::Budget& b) | calls plan, account, out, options; returns out; out; growth insert, push_back, reserve; 4 loop sites; source comment (unverified): // Exact input census uses all physical roots, including no-ops. Numeric · [reviewed contract](#b0026) |
| [B0027 · 103–107](../../../../../src/runtime/ranking_evidence.cpp#L103) | Type/record definition: struct SourceSelections | returns statistics::OwnerRequestView(std::span&lt;const statistics::Selection&gt;(values.data(),count)) · [reviewed contract](#b0027) |
| [B0028 · 108–118](../../../../../src/runtime/ranking_evidence.cpp#L108) | Callable definition: SourceSelections selections(const CompiledProgram& p,bool wanted,rd::Budget& b,Reasons& reasons) | calls reason, source_catalog, size, used; guard for(const auto& input:p.inputs()){b.work();require(input.base.value&lt;used.size());if(!used\[input.bas…; returns out; out; 2 loop sites · [reviewed contract](#b0028) |
| [B0029 · 119–125](../../../../../src/runtime/ranking_evidence.cpp#L119) | Callable definition: pr::CaptureState capture_state(statistics::Availability a) | calls ; returns pr::CaptureState::available; pr::CaptureState::budget_exhausted · [reviewed contract](#b0029) |
| [B0030 · 126–149](../../../../../src/runtime/ranking_evidence.cpp#L126) | Callable definition: void state(const statistics::CombinedCapture& native,statistics::OwnerRequestView request,rd::EvidenceData& data,rd::Budget& b) | calls capture_state, availability, requested_components, components; growth push_back, reserve; 2 loop sites · [reviewed contract](#b0030) |
| [B0031 · 150–190](../../../../../src/runtime/ranking_evidence.cpp#L150) | Callable definition: template&lt;class Owner&gt; CaptureAttempt capture_impl(const planner::CandidateSnapshot& snapshot,const Owner& owner,const CaptureOpti… | calls emplace, work, require, valid; guard budget.emplace(options.processing);auto& b=*budget;b.work();require(snapshot.valid(),pr::Stop::inva…; returns result; growth emplace, make_accounted_shared; source comment (unverified): // Explicit actual-owner diagnostic: bind metadata, capture native facts and · [reviewed contract](#b0031) |
| [B0032 · 191–199](../../../../../src/runtime/ranking_evidence.cpp#L191) | Callable definition: Reasons freshness(std::optional&lt;statistics::Freshness&gt; f) | calls reason; returns reason(Reason::released); 0 · [reviewed contract](#b0032) |
| [B0033 · 200–223](../../../../../src/runtime/ranking_evidence.cpp#L200) | Callable definition: template&lt;class Owner&gt; Revalidation revalidate_impl(const RuntimeEvidence& old,const Owner& owner) noexcept | calls inputs, depth_reasons, memory_reasons, captured; returns out; out; source comment (unverified): // Boundary, depth and memory remain separate. A depth-only census failure · [reviewed contract](#b0033) |
| [B0034 · 224–234](../../../../../src/runtime/ranking_evidence.cpp#L224) | Callable definition: template&lt;class Owner&gt; pr::Attempt current_impl(const planner::CandidateSnapshot& snapshot,const Owner& owner,const pr::Request& r… | calls actual_plan, pr::rank_with_account, account, capture_impl; returns pr::rank_with_account(plan.account(),snapshot,request); {pr::Stop::allocation_failure,{},{},0,0} · [reviewed contract](#b0034) |
| [B0035 · 235–235](../../../../../src/runtime/ranking_evidence.cpp#L235) | Closes surrounding scope/type. | source comment (unverified): // namespace · [reviewed contract](#b0035) |
| [B0036 · 236–236](../../../../../src/runtime/ranking_evidence.cpp#L236) | Callable definition: detail::Census detail::classify_census(const workload::Snapshot& s,rd::Budget& b) | calls census; returns census(s,b) · [reviewed contract](#b0036) |
| [B0037 · 237–237](../../../../../src/runtime/ranking_evidence.cpp#L237) | Callable definition: CaptureAttempt capture(const planner::CandidateSnapshot& s,const PhysicalRuntime& o,const CaptureOptions& l) noexcept | calls capture_impl; returns capture_impl(s,o,l) · [reviewed contract](#b0037) |
| [B0038 · 238–238](../../../../../src/runtime/ranking_evidence.cpp#L238) | Callable definition: CaptureAttempt capture(const planner::CandidateSnapshot& s,const DeltaRuntime& o,const CaptureOptions& l) noexcept | calls capture_impl; returns capture_impl(s,o,l) · [reviewed contract](#b0038) |
| [B0039 · 239–239](../../../../../src/runtime/ranking_evidence.cpp#L239) | Callable definition: CaptureAttempt capture(const planner::CandidateSnapshot& s,const QuerySession& o,const CaptureOptions& l) noexcept | calls capture_impl; returns capture_impl(s,o,l) · [reviewed contract](#b0039) |
| [B0040 · 240–240](../../../../../src/runtime/ranking_evidence.cpp#L240) | Callable definition: Revalidation revalidate(const RuntimeEvidence& e,const PhysicalRuntime& o) noexcept | calls revalidate_impl; returns revalidate_impl(e,o) · [reviewed contract](#b0040) |
| [B0041 · 241–241](../../../../../src/runtime/ranking_evidence.cpp#L241) | Callable definition: Revalidation revalidate(const RuntimeEvidence& e,const DeltaRuntime& o) noexcept | calls revalidate_impl; returns revalidate_impl(e,o) · [reviewed contract](#b0041) |
| [B0042 · 242–242](../../../../../src/runtime/ranking_evidence.cpp#L242) | Callable definition: Revalidation revalidate(const RuntimeEvidence& e,const QuerySession& o) noexcept | calls revalidate_impl; returns revalidate_impl(e,o) · [reviewed contract](#b0042) |
| [B0043 · 243–243](../../../../../src/runtime/ranking_evidence.cpp#L243) | Callable definition: pr::Attempt rank_current(const planner::CandidateSnapshot& s,const PhysicalRuntime& o,const pr::Request& r,statistics::Limits l) … | calls current_impl; returns current_impl(s,o,r,l) · [reviewed contract](#b0043) |
| [B0044 · 244–244](../../../../../src/runtime/ranking_evidence.cpp#L244) | Callable definition: pr::Attempt rank_current(const planner::CandidateSnapshot& s,const DeltaRuntime& o,const pr::Request& r,statistics::Limits l) noe… | calls current_impl; returns current_impl(s,o,r,l) · [reviewed contract](#b0044) |
| [B0045 · 245–245](../../../../../src/runtime/ranking_evidence.cpp#L245) | Callable definition: pr::Attempt rank_current(const planner::CandidateSnapshot& s,const QuerySession& o,const pr::Request& r,statistics::Limits l) noe… | calls current_impl; returns current_impl(s,o,r,l) · [reviewed contract](#b0045) |
| [B0046 · 246–246](../../../../../src/runtime/ranking_evidence.cpp#L246) | Closes surrounding scope/type. | source comment (unverified): // namespace crown::runtime::ranking · [reviewed contract](#b0046) |

## B0001

[Lines 1–12](../../../../../src/runtime/ranking_evidence.cpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
#include "crown/runtime/ranking_evidence.hpp"
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Assemble actual-owner ranking evidence without new height/proof authority. |
| inputs / outputs | Runtime evidence, private census, existing ranking budget/binding and accounted ownership helpers; rd aliases planner ranking detail. |
| invariants | Observed input counts/source cardinalities and their policy models remain distinct from the retained candidate snapshot minimum-height proof. This file does not search/prove a new height. |
| ownership | Declarations retain no runtime/account. Later immutable evidence shares actual plan/captures, not owner pointers. |
| failure | No dynamic failure or handler at includes/aliases. |
| cost | Compile-time setup only. |
| Design | [docs/ranking.md](../../../../ranking.md), [docs/ranking_accounting.md](../../../../ranking_accounting.md), [include/crown/runtime/ranking_evidence.hpp](../../../../../include/crown/runtime/ranking_evidence.hpp), [docs/code_review.md](../../../../code_review.md) |

## B0002

[Lines 13–16](../../../../../src/runtime/ranking_evidence.cpp#L13); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct OwnerAccess {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Borrow immutable compiled metadata from actual native physical/delta owners. |
| inputs / outputs | Two private friend OwnerAccess functions return owner.compiled_program() by const reference. |
| invariants | Does not export an ordinary PhysicalPlan graph or infer current source identity from a report. Public owner validity/single-writer contract applies. |
| ownership | References borrow actual runtime metadata; actual_plan makes an owning handle copy before further work. |
| failure | Owner state errors propagate from accessor; no translation/rollback here. |
| cost | Constant access, with no compiler reconstruction or row scan. |
| Design | [docs/ranking.md](../../../../ranking.md), [docs/ranking_accounting.md](../../../../ranking_accounting.md), [include/crown/runtime/ranking_evidence.hpp](../../../../../include/crown/runtime/ranking_evidence.hpp) |

## B0003

[Lines 17–23](../../../../../src/runtime/ranking_evidence.cpp#L17); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct Data {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Retain immutable planner inputs and actual joint/session observations. |
| inputs / outputs | Data constructor moves pr::Evidence, optional CombinedCapture and optional SessionStatisticsContext into shared const storage. |
| invariants | Capture may be explicitly unavailable/released; optional absence and reason flags remain observable. No runtime rows, mutable owner pointer, cursor or lease retained. |
| ownership | Shares original-account evidence/plan/capture/context graphs; Data holder is separately accounted in capture_impl. |
| failure | Private construction precedes public RuntimeEvidence publication; failures unwind handles. |
| cost | Fixed handles/optionals plus retained existing graphs; no deep copy of source rows. |
| Design | [docs/ranking.md](../../../../ranking.md), [docs/ranking_accounting.md](../../../../ranking_accounting.md), [include/crown/runtime/ranking_evidence.hpp](../../../../../include/crown/runtime/ranking_evidence.hpp) |

## B0004

[Lines 24–24](../../../../../src/runtime/ranking_evidence.cpp#L24); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct Factory {static RuntimeEvidence make(std::shared_ptr<const Data> value){return RuntimeEvidence(std::move(value));}};
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Restrict RuntimeEvidence handle construction to checked private capture. |
| inputs / outputs | Shared const Data moves into the private RuntimeEvidence constructor. |
| invariants | Assumes non-null fully built payload; factory alone does not validate source/proof/census. |
| ownership | Transfers shared owner, no new runtime/account. |
| failure | No payload allocation/catch during handle move. |
| cost | Constant shared-pointer transfer. |
| Design | [docs/ranking.md](../../../../ranking.md), [docs/ranking_accounting.md](../../../../ranking_accounting.md), [include/crown/runtime/ranking_evidence.hpp](../../../../../include/crown/runtime/ranking_evidence.hpp) |

## B0005

[Lines 25–25](../../../../../src/runtime/ranking_evidence.cpp#L25); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L25-L25:sha256:412ca345ccf75bf9c0806bce695be8de808b79984251a7a54d202cf6101dd451
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Close the \`namespace detail\` scope at this exact source boundary. |
| inputs / outputs | This token introduces no callable inputs or outputs. Declarations inside \`namespace detail\` define the available names, members and operations. |
| invariants | The closing brace matches the opening \`namespace detail\` at its lexical source position in src/runtime/ranking_evidence.cpp; it preserves C++ namespace/type nesting. |
| ownership | The closing delimiter creates no owner. Types closed by \`namespace detail\` retain the lifetimes and allocator rules of their own fields and operations. |
| failure | No failure path executes at this closing delimiter. Failure and cleanup behavior belong to enclosed functions and owning types. |
| cost | The delimiter itself performs no runtime work; the enclosed initializers, methods and destructors carry their own costs. |
| Design | [docs/selection.md](../../../../selection.md), [docs/selection_binding.md](../../../../selection_binding.md), [docs/selection_accounting.md](../../../../selection_accounting.md), [docs/reoptimization.md](../../../../reoptimization.md), [docs/code_specs/subsystem_contracts.md](../../../subsystem_contracts.md) |

## B0006

[Lines 26–26](../../../../../src/runtime/ranking_evidence.cpp#L26); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
const pr::Evidence& RuntimeEvidence::inputs() const noexcept{return data_->inputs;}
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Borrow RuntimeEvidence planner evidence inputs. |
| inputs / outputs | Readable factory-produced handle returns const reference to its planner evidence inputs. |
| invariants | Binding/identity/weights/source facts and explicit unavailability reasons are immutable as-of capture. |
| ownership | Reference lifetime requires any sharing RuntimeEvidence handle. Public copy-like moves leave both handles readable. |
| failure | noexcept, no allocation/read of a live owner/counter update. |
| cost | Constant pointer/member access. |
| Design | [docs/ranking.md](../../../../ranking.md), [docs/ranking_accounting.md](../../../../ranking_accounting.md), [include/crown/runtime/ranking_evidence.hpp](../../../../../include/crown/runtime/ranking_evidence.hpp) |

## B0007

[Lines 27–27](../../../../../src/runtime/ranking_evidence.cpp#L27); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
const std::optional<statistics::CombinedCapture>& RuntimeEvidence::captured() const noexcept{return data_->captured;}
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Borrow RuntimeEvidence optional actual joint capture. |
| inputs / outputs | Readable factory-produced handle returns const reference to its optional actual joint capture. |
| invariants | Retains native state/workload snapshots; absence can mean released owner, not a fabricated empty database. |
| ownership | Reference lifetime requires any sharing RuntimeEvidence handle. Public copy-like moves leave both handles readable. |
| failure | noexcept, no allocation/read of a live owner/counter update. |
| cost | Constant pointer/member access. |
| Design | [docs/ranking.md](../../../../ranking.md), [docs/ranking_accounting.md](../../../../ranking_accounting.md), [include/crown/runtime/ranking_evidence.hpp](../../../../../include/crown/runtime/ranking_evidence.hpp) |

## B0008

[Lines 28–28](../../../../../src/runtime/ranking_evidence.cpp#L28); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
const std::optional<SessionStatisticsContext>& RuntimeEvidence::session_context() const noexcept{return data_->session;}
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Borrow RuntimeEvidence optional session context. |
| inputs / outputs | Readable factory-produced handle returns const reference to its optional session context. |
| invariants | Only actual session capture provides it; context is immutable metadata, not mutable session authority. |
| ownership | Reference lifetime requires any sharing RuntimeEvidence handle. Public copy-like moves leave both handles readable. |
| failure | noexcept, no allocation/read of a live owner/counter update. |
| cost | Constant pointer/member access. |
| Design | [docs/ranking.md](../../../../ranking.md), [docs/ranking_accounting.md](../../../../ranking_accounting.md), [include/crown/runtime/ranking_evidence.hpp](../../../../../include/crown/runtime/ranking_evidence.hpp) |

## B0009

[Lines 29–31](../../../../../src/runtime/ranking_evidence.cpp#L29); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
namespace {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Name reason bits and original-account scratch containers. |
| inputs / outputs | Reason/Reasons/reason aliases plus Scratch&lt;T&gt; using MemoryAllocator&lt;T&gt;. |
| invariants | Aliases add no fallback, evidence/proof import or independent allocation grant. |
| ownership | No retained account until a scratch container is instantiated. |
| failure | No runtime action here. |
| cost | Compile-time aliases only. |
| Design | [docs/ranking.md](../../../../ranking.md), [docs/ranking_accounting.md](../../../../ranking_accounting.md), [include/crown/runtime/ranking_evidence.hpp](../../../../../include/crown/runtime/ranking_evidence.hpp) |

## B0010

[Lines 32–34](../../../../../src/runtime/ranking_evidence.cpp#L32); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
template<class T> resource::MemoryAllocator<T> scratch_allocator(const resource::MemoryAccount& account) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Construct capture scratch allocators on the actual plan account. |
| inputs / outputs | Readable MemoryAccount returns scratch-purpose MemoryAllocator&lt;T&gt; attributed to ranking evidence. |
| invariants | No hidden fresh account or budget refill; logical C02 byte/cell debits remain separate from actual allocation. |
| ownership | Allocator retains same account and immutable attribution. |
| failure | Invalid account/purpose ownership contract may fail construction; no payload allocation here. |
| cost | Constant account handle setup. |
| Design | [docs/ranking.md](../../../../ranking.md), [docs/ranking_accounting.md](../../../../ranking_accounting.md), [include/crown/runtime/ranking_evidence.hpp](../../../../../include/crown/runtime/ranking_evidence.hpp), [include/crown/resource/allocator.hpp](../../../../../include/crown/resource/allocator.hpp) |

## B0011

[Lines 35–35](../../../../../src/runtime/ranking_evidence.cpp#L35); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void require(bool value,pr::Stop stop=pr::Stop::internal_error){if(!value){throw rd::Failure{stop};}}
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Raise an internal ranking stop for a failed evidence precondition. |
| inputs / outputs | Boolean plus Stop (default internal_error) return or throw rd::Failure{stop}. |
| invariants | Typed fixed stop is caught at existing public noexcept capture boundary; no query rollback occurs. |
| ownership | Enum-only error carrier, no copied diagnostic string. |
| failure | False throws; preparation owners unwind. |
| cost | One success branch, failure-only exception machinery. |
| Design | [docs/ranking.md](../../../../ranking.md), [docs/ranking_accounting.md](../../../../ranking_accounting.md), [include/crown/runtime/ranking_evidence.hpp](../../../../../include/crown/runtime/ranking_evidence.hpp) |

## B0012

[Lines 36–36](../../../../../src/runtime/ranking_evidence.cpp#L36); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
CompiledProgram actual_plan(const PhysicalRuntime& owner){return detail::OwnerAccess::program(owner);}
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Retain actual immutable plan metadata from PhysicalRuntime. |
| inputs / outputs | Readable PhysicalRuntime returns CompiledProgram handle via friend compiled-program access. |
| invariants | Owner plan supplies original account/source/operator binding; does not reconstruct/export a compiler DTO or prove a new tree. |
| ownership | Owning metadata handle copy survives runtime access boundary; no source rows/pins. |
| failure | Existing owner/session state/thread/reentry errors propagate to outer capture/rank boundary. |
| cost | Constant metadata-handle work plus session metadata carrier when applicable; no plan lowering. |
| Design | [docs/ranking.md](../../../../ranking.md), [docs/ranking_accounting.md](../../../../ranking_accounting.md), [include/crown/runtime/ranking_evidence.hpp](../../../../../include/crown/runtime/ranking_evidence.hpp) |

## B0013

[Lines 37–37](../../../../../src/runtime/ranking_evidence.cpp#L37); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
CompiledProgram actual_plan(const DeltaRuntime& owner){return detail::OwnerAccess::program(owner);}
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Retain actual immutable plan metadata from DeltaRuntime. |
| inputs / outputs | Readable DeltaRuntime returns CompiledProgram handle via friend compiled-program access. |
| invariants | Owner plan supplies original account/source/operator binding; does not reconstruct/export a compiler DTO or prove a new tree. |
| ownership | Owning metadata handle copy survives runtime access boundary; no source rows/pins. |
| failure | Existing owner/session state/thread/reentry errors propagate to outer capture/rank boundary. |
| cost | Constant metadata-handle work plus session metadata carrier when applicable; no plan lowering. |
| Design | [docs/ranking.md](../../../../ranking.md), [docs/ranking_accounting.md](../../../../ranking_accounting.md), [include/crown/runtime/ranking_evidence.hpp](../../../../../include/crown/runtime/ranking_evidence.hpp) |

## B0014

[Lines 38–38](../../../../../src/runtime/ranking_evidence.cpp#L38); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
CompiledProgram actual_plan(const QuerySession& owner){return owner.report_metadata().plan();}
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Retain actual immutable plan metadata from QuerySession. |
| inputs / outputs | Readable QuerySession returns CompiledProgram handle via guarded report_metadata().plan(). |
| invariants | Owner plan supplies original account/source/operator binding; does not reconstruct/export a compiler DTO or prove a new tree. |
| ownership | Owning metadata handle copy survives runtime access boundary; no source rows/pins. |
| failure | Existing owner/session state/thread/reentry errors propagate to outer capture/rank boundary. |
| cost | Constant metadata-handle work plus session metadata carrier when applicable; no plan lowering. |
| Design | [docs/ranking.md](../../../../ranking.md), [docs/ranking_accounting.md](../../../../ranking_accounting.md), [include/crown/runtime/ranking_evidence.hpp](../../../../../include/crown/runtime/ranking_evidence.hpp) |

## B0015

[Lines 39–39](../../../../../src/runtime/ranking_evidence.cpp#L39); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct NativeCapture {std::optional<statistics::CombinedCapture> combined;std::optional<SessionStatisticsContext> session;};
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Carry the joint actual-owner capture and optional session context through one synchronous read. |
| inputs / outputs | NativeCapture has optional CombinedCapture and SessionStatisticsContext. |
| invariants | Separate native state/workload availability domains stay intact; a dropped session can supply context without live joint capture. |
| ownership | Owning immutable handles only; no mutable runtime pointer or row borrow. |
| failure | Private result unwinds if later binding/census/admission fails. |
| cost | Fixed handles plus delegated retained capture graph. |
| Design | [docs/ranking.md](../../../../ranking.md), [docs/ranking_accounting.md](../../../../ranking_accounting.md), [include/crown/runtime/ranking_evidence.hpp](../../../../../include/crown/runtime/ranking_evidence.hpp) |

## B0016

[Lines 40–40](../../../../../src/runtime/ranking_evidence.cpp#L40); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
NativeCapture actual_capture(const PhysicalRuntime& owner,statistics::OwnerRequestView r,statistics::Limits l){return {owner.capture_combined_statistics_view(r,l),{}};}
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Obtain synchronized actual-owner statistics from PhysicalRuntime. |
| inputs / outputs | OwnerRequestView and native limits call combined_statistics_view (or session statistics_context_view) and package owning joint/context handles. |
| invariants | Sampling/state availability and owner-private marker are actual observations. C01 limits are distinct from C02 processing and actual memory account. |
| ownership | Borrow request only during synchronous read; return owns numeric/metadata graphs and no owner row/cursor/lease. |
| failure | Native/session/thread/account failures propagate; partial/unavailable C01 results can still be valid typed observations. |
| cost | Delegated explicit capture can allocate/copy workload slabs and scan selected state; not an O(1) getter. |
| Design | [docs/ranking.md](../../../../ranking.md), [docs/ranking_accounting.md](../../../../ranking_accounting.md), [include/crown/runtime/ranking_evidence.hpp](../../../../../include/crown/runtime/ranking_evidence.hpp), [include/crown/runtime/combined_statistics.hpp](../../../../../include/crown/runtime/combined_statistics.hpp) |

## B0017

[Lines 41–41](../../../../../src/runtime/ranking_evidence.cpp#L41); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
NativeCapture actual_capture(const DeltaRuntime& owner,statistics::OwnerRequestView r,statistics::Limits l){return {owner.capture_combined_statistics_view(r,l),{}};}
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Obtain synchronized actual-owner statistics from DeltaRuntime. |
| inputs / outputs | OwnerRequestView and native limits call combined_statistics_view (or session statistics_context_view) and package owning joint/context handles. |
| invariants | Sampling/state availability and owner-private marker are actual observations. C01 limits are distinct from C02 processing and actual memory account. |
| ownership | Borrow request only during synchronous read; return owns numeric/metadata graphs and no owner row/cursor/lease. |
| failure | Native/session/thread/account failures propagate; partial/unavailable C01 results can still be valid typed observations. |
| cost | Delegated explicit capture can allocate/copy workload slabs and scan selected state; not an O(1) getter. |
| Design | [docs/ranking.md](../../../../ranking.md), [docs/ranking_accounting.md](../../../../ranking_accounting.md), [include/crown/runtime/ranking_evidence.hpp](../../../../../include/crown/runtime/ranking_evidence.hpp), [include/crown/runtime/combined_statistics.hpp](../../../../../include/crown/runtime/combined_statistics.hpp) |

## B0018

[Lines 42–44](../../../../../src/runtime/ranking_evidence.cpp#L42); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
NativeCapture actual_capture(const QuerySession& owner,statistics::OwnerRequestView r,statistics::Limits l){
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Obtain synchronized actual-owner statistics from QuerySession. |
| inputs / outputs | OwnerRequestView and native limits call combined_statistics_view (or session statistics_context_view) and package owning joint/context handles. |
| invariants | Sampling/state availability and owner-private marker are actual observations. C01 limits are distinct from C02 processing and actual memory account. |
| ownership | Borrow request only during synchronous read; return owns numeric/metadata graphs and no owner row/cursor/lease. |
| failure | Native/session/thread/account failures propagate; partial/unavailable C01 results can still be valid typed observations. |
| cost | Delegated explicit capture can allocate/copy workload slabs and scan selected state; not an O(1) getter. |
| Design | [docs/ranking.md](../../../../ranking.md), [docs/ranking_accounting.md](../../../../ranking_accounting.md), [include/crown/runtime/ranking_evidence.hpp](../../../../../include/crown/runtime/ranking_evidence.hpp), [include/crown/runtime/combined_statistics.hpp](../../../../../include/crown/runtime/combined_statistics.hpp) |

## B0019

[Lines 45–45](../../../../../src/runtime/ranking_evidence.cpp#L45); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::optional<statistics::Freshness> actual_freshness(const PhysicalRuntime& owner,const statistics::OwnerCapture& c){return owner.statistics_freshness(c,0);}
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Query zero-lag freshness of a retained state capture against PhysicalRuntime. |
| inputs / outputs | Actual owner and OwnerCapture forward statistics_freshness(c,0), returning optional Freshness. |
| invariants | Current boundary is owner/sequence/scope based; does not refresh stored observations or certify every statistical policy usable. |
| ownership | Borrows capture/owner only; returns fixed enum optional. |
| failure | Owner read/thread/state errors propagate to revalidate_impl reason boundary. |
| cost | Delegated freshness metadata check; no new native capture in this wrapper. |
| Design | [docs/ranking.md](../../../../ranking.md), [docs/ranking_accounting.md](../../../../ranking_accounting.md), [include/crown/runtime/ranking_evidence.hpp](../../../../../include/crown/runtime/ranking_evidence.hpp) |

## B0020

[Lines 46–46](../../../../../src/runtime/ranking_evidence.cpp#L46); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::optional<statistics::Freshness> actual_freshness(const DeltaRuntime& owner,const statistics::OwnerCapture& c){return owner.statistics_freshness(c,0);}
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Query zero-lag freshness of a retained state capture against DeltaRuntime. |
| inputs / outputs | Actual owner and OwnerCapture forward statistics_freshness(c,0), returning optional Freshness. |
| invariants | Current boundary is owner/sequence/scope based; does not refresh stored observations or certify every statistical policy usable. |
| ownership | Borrows capture/owner only; returns fixed enum optional. |
| failure | Owner read/thread/state errors propagate to revalidate_impl reason boundary. |
| cost | Delegated freshness metadata check; no new native capture in this wrapper. |
| Design | [docs/ranking.md](../../../../ranking.md), [docs/ranking_accounting.md](../../../../ranking_accounting.md), [include/crown/runtime/ranking_evidence.hpp](../../../../../include/crown/runtime/ranking_evidence.hpp) |

## B0021

[Lines 47–47](../../../../../src/runtime/ranking_evidence.cpp#L47); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::optional<statistics::Freshness> actual_freshness(const QuerySession& owner,const statistics::OwnerCapture& c){return owner.statistics_freshness(c,0);}
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Query zero-lag freshness of a retained state capture against QuerySession. |
| inputs / outputs | Actual owner and OwnerCapture forward statistics_freshness(c,0), returning optional Freshness. |
| invariants | Current boundary is owner/sequence/scope based; does not refresh stored observations or certify every statistical policy usable. |
| ownership | Borrows capture/owner only; returns fixed enum optional. |
| failure | Owner read/thread/state errors propagate to revalidate_impl reason boundary. |
| cost | Delegated freshness metadata check; no new native capture in this wrapper. |
| Design | [docs/ranking.md](../../../../ranking.md), [docs/ranking_accounting.md](../../../../ranking_accounting.md), [include/crown/runtime/ranking_evidence.hpp](../../../../../include/crown/runtime/ranking_evidence.hpp) |

## B0022

[Lines 48–52](../../../../../src/runtime/ranking_evidence.cpp#L48); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
pr::ModeIdentity modes(const workload::ModeFacts& m) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Copy all workload mode facts into ranking identity. |
| inputs / outputs | delta-owner, requested/resolved mode/completion, live policy and result view become fixed integer/Boolean ModeIdentity. |
| invariants | Requested and actual mode meanings remain separate; no mode switch or normalization performed. |
| ownership | Fixed value copy. |
| failure | No allocation/catch for admitted enum inputs. |
| cost | Constant field conversions. |
| Design | [docs/ranking.md](../../../../ranking.md), [docs/ranking_accounting.md](../../../../ranking_accounting.md), [include/crown/runtime/ranking_evidence.hpp](../../../../../include/crown/runtime/ranking_evidence.hpp) |

## B0023

[Lines 53–58](../../../../../src/runtime/ranking_evidence.cpp#L53); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
pr::EvidenceIdentity identity(const statistics::CombinedCapture& c) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Bind ranking evidence to the exact captured workload interval and configuration. |
| inputs / outputs | CombinedCapture workload stamp/options/modes/pending/saturation fields form EvidenceIdentity. |
| invariants | Owner/committed epoch, interval start/reset/configuration/segment/format and sampling/cell limits all remain explicit. Identity is descriptive and not proof/authority import. |
| ownership | Copies fixed values, shares no view. |
| failure | No runtime access/allocation beyond borrowed capture getters. |
| cost | Constant field copies. |
| Design | [docs/ranking.md](../../../../ranking.md), [docs/ranking_accounting.md](../../../../ranking_accounting.md), [include/crown/runtime/ranking_evidence.hpp](../../../../../include/crown/runtime/ranking_evidence.hpp) |

## B0024

[Lines 59–59](../../../../../src/runtime/ranking_evidence.cpp#L59); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Reasons interval_saturated(const workload::Snapshot& s){const auto& x=s.stamp();return x.reset_saturated || x.configuration_saturated || x.segment_saturated?reason(Reason::interval_saturated):0;}
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Classify interval identity saturation explicitly. |
| inputs / outputs | Reset/configuration/segment saturation in Snapshot stamp returns interval_saturated reason if any. |
| invariants | Repeated numeric maximum cannot certify a unique fresh interval; no counter wrap or silent exactness. |
| ownership | Fixed borrowed stamp reads. |
| failure | No allocation or failure. |
| cost | Constant Boolean tests. |
| Design | [docs/ranking.md](../../../../ranking.md), [docs/ranking_accounting.md](../../../../ranking_accounting.md), [include/crown/runtime/ranking_evidence.hpp](../../../../../include/crown/runtime/ranking_evidence.hpp) |

## B0025

[Lines 60–60](../../../../../src/runtime/ranking_evidence.cpp#L60); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
using Census=detail::Census;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Use the private numeric census carrier across isolated classifier tests and production capture. |
| inputs / outputs | Alias Census to detail::Census with reasons,total and account-funded InputWeight vector. |
| invariants | Private classifier seam cannot manufacture public actual-owner RuntimeEvidence or a height proof. |
| ownership | Alias retains no account until Census is constructed. |
| failure | No runtime action in declaration. |
| cost | Compile-time only. |
| Design | [docs/ranking.md](../../../../ranking.md), [docs/ranking_accounting.md](../../../../ranking_accounting.md), [include/crown/runtime/ranking_evidence.hpp](../../../../../include/crown/runtime/ranking_evidence.hpp), [src/runtime/ranking_evidence_detail.hpp](../../../../../src/runtime/ranking_evidence_detail.hpp) |

## B0026

[Lines 61–102](../../../../../src/runtime/ranking_evidence.cpp#L61); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Census census(const workload::Snapshot& s,rd::Budget& b) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Validate exact physical input census and preserve explicit unusable reasons. |
| inputs / outputs | Workload Snapshot and shared C02 Budget inspect physical roots, table/op completeness, input=changed+noop, saturation/protocol/pending/interval flags, total denominator and per-table weights. |
| invariants | Requires both insert/erase root for every source table, including unused ones. Noops count as inputs. Overflow makes total unavailable; it never wraps. Logical-only/disabled/incomplete roots cannot price a fabricated exact depth model. |
| ownership | InputWeight output and seen/root scratch use actual plan account; captures remain immutable. Returned numeric census owns its vector only. |
| failure | C02 work/cell/byte/time/account failures throw to public capture; protocol/data loss usually returns reason bits rather than a partial exact claim. |
| cost | O(tables+descriptors+physical roots*descriptors) because each native input_share scans all descriptors; each repeated scan is explicitly debited. Actual vector/control framing is separate. |
| Design | [docs/ranking.md](../../../../ranking.md), [docs/ranking_accounting.md](../../../../ranking_accounting.md), [include/crown/runtime/ranking_evidence.hpp](../../../../../include/crown/runtime/ranking_evidence.hpp), [src/runtime/workload_statistics.cpp](../../../../../src/runtime/workload_statistics.cpp), [tests/unit/ranking_census_test.cpp](../../../../../tests/unit/ranking_census_test.cpp) |

```text
for(const auto i:roots){
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Validate each physical denominator using the actual helper cost,not an O(1) fiction. |
| inputs / outputs | Every physical root calls Snapshot.input_share and compares all-input denominator scope/value/status with census total. |
| invariants | Helper scans entire descriptor array; explicit b.work(D) charges each repeated scan. Invalid/saturated denominator never becomes an exact forecast input. |
| ownership | Borrowed snapshot and root-index scratch only. |
| failure | Work/time exhaustion propagates; denominator disagreement returns unusability reason. |
| cost | O(number physical roots *descriptors),even when final source-cardinality selection is small. |
| Design | [docs/ranking.md](../../../../ranking.md), [docs/ranking_accounting.md](../../../../ranking_accounting.md), [include/crown/runtime/ranking_evidence.hpp](../../../../../include/crown/runtime/ranking_evidence.hpp), [src/runtime/workload_statistics.cpp](../../../../../src/runtime/workload_statistics.cpp) |

## B0027

[Lines 103–107](../../../../../src/runtime/ranking_evidence.cpp#L103); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct SourceSelections {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Carry a bounded source-cardinality request without heap selection storage. |
| inputs / outputs | Fixed array of256 Selection plus count; view borrows prefix span as OwnerRequestView. |
| invariants | count&lt;=256 is established by selections; no request may outlive this stack carrier. |
| ownership | Fixed stack array; no native owner/cursor retained. |
| failure | View construction does not allocate; malformed private count is outside contract. |
| cost | Fixed256-entry stack storage; constant view construction. |
| Design | [docs/ranking.md](../../../../ranking.md), [docs/ranking_accounting.md](../../../../ranking_accounting.md), [include/crown/runtime/ranking_evidence.hpp](../../../../../include/crown/runtime/ranking_evidence.hpp) |

## B0028

[Lines 108–118](../../../../../src/runtime/ranking_evidence.cpp#L108); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
SourceSelections selections(const CompiledProgram& p,bool wanted,rd::Budget& b,Reasons& reasons) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Select unique physical source tables used by admitted core input occurrences. |
| inputs / outputs | Plan,wanted,Budget,reasons produce &lt;=256 no-projection SourceScope selections; disabled request sets not_captured, excess used tables sets source_limit. |
| invariants | Source table IDs are validated dense inputs; unused catalog tables need no cardinality request even though full input census covers them. No approximation when source cap exceeded. |
| ownership | Original-account byte-mark scratch plus fixed output selection array; view remains local through synchronous capture. |
| failure | C02 processing/allocation/invalid input-base failure aborts public capture; request omission/size cap stays explicit unavailability. |
| cost | O(source tables+inputs) visits/marks and up to256 output selections, no row/cardinality scan here. |
| Design | [docs/ranking.md](../../../../ranking.md), [docs/ranking_accounting.md](../../../../ranking_accounting.md), [include/crown/runtime/ranking_evidence.hpp](../../../../../include/crown/runtime/ranking_evidence.hpp) |

## B0029

[Lines 119–125](../../../../../src/runtime/ranking_evidence.cpp#L119); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
pr::CaptureState capture_state(statistics::Availability a) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Map native statistics availability to planner capture status. |
| inputs / outputs | available/budget_exhausted/pending_private_state preserve tags; unavailable/not_applicable/unknown fallback map unavailable. |
| invariants | Budget exhaustion is evidence availability, distinct from C02 processing failure or a valid zero cardinality. |
| ownership | Inline enums only. |
| failure | No allocation/exception. |
| cost | Constant switch. |
| Design | [docs/ranking.md](../../../../ranking.md), [docs/ranking_accounting.md](../../../../ranking_accounting.md), [include/crown/runtime/ranking_evidence.hpp](../../../../../include/crown/runtime/ranking_evidence.hpp) |

## B0030

[Lines 126–149](../../../../../src/runtime/ranking_evidence.cpp#L126); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void state(const statistics::CombinedCapture& native,statistics::OwnerRequestView request,rd::EvidenceData& data,rd::Budget& b) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Retain actual source-cardinality observations and their availability without inventing complete facts. |
| inputs / outputs | Joint capture/request fill EvidenceData accounting, per-component observations, pending/layer/source-scope reasons and exact requested SourceCardinality values where available. |
| invariants | Reject pending or foreign logical layer for both memory/depth; source budget/incomplete/missing/projection mismatch marks memory unusable. Engaged cardinality0 is valid, absent cardinality is unavailable. |
| ownership | Receiver is existing private EvidenceData on actual plan account; arrays reserve before append and share no runtime rows. |
| failure | Processing/allocation errors propagate and discard entire Evidence; bounded C01 partial statuses remain retained observations. |
| cost | O(returned components) scans/copies plus vector capacity; underlying native capture had its separate row/key/work/byte cost. |
| Design | [docs/ranking.md](../../../../ranking.md), [docs/ranking_accounting.md](../../../../ranking_accounting.md), [include/crown/runtime/ranking_evidence.hpp](../../../../../include/crown/runtime/ranking_evidence.hpp) |

## B0031

[Lines 150–190](../../../../../src/runtime/ranking_evidence.cpp#L150); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
template<class Owner> CaptureAttempt capture_impl(const planner::CandidateSnapshot& snapshot,const Owner& owner,const CaptureOptions& options) noexcept {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Capture candidate-bound actual-owner evidence transactionally under original account and processing limits. |
| inputs / outputs | Valid candidate snapshot/original proof and owner/options compare complete catalog/query binding, select native sources, capture joint state, classify census/source observations and publish immutable RuntimeEvidence. |
| invariants | Minimum-height proof comes from snapshot; statistics are as-of observations/models. Actual captured physical SHA must match actual plan. Dropped session context reports released rather than synthetic empty state. Native and processing work domains remain distinct. |
| ownership | EvidenceData binding/arrays/captures and public holder use original plan account; owning plan/capture/session metadata survive owner destruction. No ordinary plan/row mirror. |
| failure | Public noexcept maps typed processing stop, bad_alloc/MemoryFailure and unexpected error to explicit stop. Partial private graphs unwind, no Evidence on processing/allocation failure; native bounded unavailable observations can publish with reasons. |
| cost | Explicit cold binding serialization/comparison, actual native capture/slab copies, census scans and two accounted holders/arrays; optional processing-time checks. Not per-update or constant-time. |
| Design | [docs/ranking.md](../../../../ranking.md), [docs/ranking_accounting.md](../../../../ranking_accounting.md), [include/crown/runtime/ranking_evidence.hpp](../../../../../include/crown/runtime/ranking_evidence.hpp), [src/runtime/session.cpp](../../../../../src/runtime/session.cpp), [src/planner/ranking_detail.hpp](../../../../../src/planner/ranking_detail.hpp) |

```text
auto native=actual_capture(owner,request,options.state_limits);b.time();
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Keep native capture limits and actual allocated workload snapshot separate from later planner processing. |
| inputs / outputs | One synchronous state/workload capture runs with six native limits and actual owner account; b.time checks processing boundary after call. |
| invariants | Native collector slab-copy allocation is constrained by configured state/account,not retroactively by C02 logical payload cap. Captures can be explicitly partial/unavailable. |
| ownership | Private owning joint/session handles are retained only after all later classification/holder checks pass. |
| failure | Throwing processing/account failure drops entire public Evidence; native bounded unavailable status can survive as typed reasons. |
| cost | Actual state selection visits and full configured workload slab copies; explicit cold diagnostic. |
| Design | [docs/ranking.md](../../../../ranking.md), [docs/ranking_accounting.md](../../../../ranking_accounting.md), [include/crown/runtime/ranking_evidence.hpp](../../../../../include/crown/runtime/ranking_evidence.hpp) |

## B0032

[Lines 191–199](../../../../../src/runtime/ranking_evidence.cpp#L191); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Reasons freshness(std::optional<statistics::Freshness> f) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Translate actual freshness reports into policy reason bits. |
| inputs / outputs | Optional current/lag/stale/foreign/future/scope enum maps to0 or released/stale/foreign_owner/future_sequence/layer_mismatch, unknown to read_failed. |
| invariants | Zero-lag request means within_lag is still stale for current evidence. Does not mutate/refresh capture. |
| ownership | Fixed optional/bitmask only. |
| failure | No allocation/throw in switch. |
| cost | Constant enum tests. |
| Design | [docs/ranking.md](../../../../ranking.md), [docs/ranking_accounting.md](../../../../ranking_accounting.md), [include/crown/runtime/ranking_evidence.hpp](../../../../../include/crown/runtime/ranking_evidence.hpp) |

## B0033

[Lines 200–223](../../../../../src/runtime/ranking_evidence.cpp#L200); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
template<class Owner> Revalidation revalidate_impl(const RuntimeEvidence& old,const Owner& owner) noexcept {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Revalidate a retained evidence boundary while preserving independent depth/memory usability. |
| inputs / outputs | Old RuntimeEvidence+owner initialize old policy reasons, query actual freshness/current joint capture, compare pending/physical source/interval/config/mode/saturation and classify current census. |
| invariants | Boundary faults affect both policies; interval/mode/census faults affect depth without unnecessarily invalidating still-usable as-of memory facts. Height-only policy does not require statistical facts. Old evidence stays immutable. |
| ownership | Temporary actual capture/census can allocate on original owner account; no rows/runtime pointers escape. Return fixed masks. |
| failure | Outer catch marks boundary read_failed; inner census catch marks only depth read_failed so a depth-only processing/allocation failure does not erase independently valid boundary/memory status. |
| cost | Explicit diagnostic capture, full workload/identity checks and bounded census repeated scans; not constant-time/no-allocation revalidation. |
| Design | [docs/ranking.md](../../../../ranking.md), [docs/ranking_accounting.md](../../../../ranking_accounting.md), [include/crown/runtime/ranking_evidence.hpp](../../../../../include/crown/runtime/ranking_evidence.hpp), [src/runtime/workload_statistics.cpp](../../../../../src/runtime/workload_statistics.cpp) |

```text
try{rd::Budget b(pr::Limits{});out.depth|=census(c.workload(),b).reasons;}
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Contain current depth-census failure without discarding independent boundary/memory checks. |
| inputs / outputs | Fresh bounded classifier augments only depth reasons; any classifier exception sets depth read_failed. |
| invariants | Outer owner read/freshness failure affects both policies. The inner catch is intentionally narrower than the outer boundary. |
| ownership | Private census scratch releases on unwind; old/current immutable capture ownership remains. |
| failure | No error is silently treated as exact zero data; reason mask preserves unavailability. |
| cost | Full census scans/allocations as above; exception boundary adds no success-path row scan. |
| Design | [docs/ranking.md](../../../../ranking.md), [docs/ranking_accounting.md](../../../../ranking_accounting.md), [include/crown/runtime/ranking_evidence.hpp](../../../../../include/crown/runtime/ranking_evidence.hpp) |

## B0034

[Lines 224–234](../../../../../src/runtime/ranking_evidence.cpp#L224); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
template<class Owner> pr::Attempt current_impl(const planner::CandidateSnapshot& snapshot,const Owner& owner,const pr::Request& request,statistics::Limits state_limits) noexcept {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Rank current actual-owner candidates with only the facts needed by the requested policy. |
| inputs / outputs | Height-only obtains plan account and directly rank_with_account; depth or slot policy captures actual evidence (sources only for slots) then calls planner rank. |
| invariants | Does not convert count/depth/slot score into forecast time or fabricate height authority. Capture failure returns its stop/usage/reasons without partial rank. |
| ownership | Shares actual plan/evidence handles; result allocations stay on actual account through planner APIs. |
| failure | Height-only wrapper maps bad_alloc/unexpected errors into noexcept Attempt; capture/rank APIs own their native stop boundaries for statistical policies. |
| cost | Constant dispatch plus selected binding/capture/rank/lowering costs; avoids optional state capture on height-only path. |
| Design | [docs/ranking.md](../../../../ranking.md), [docs/ranking_accounting.md](../../../../ranking_accounting.md), [include/crown/runtime/ranking_evidence.hpp](../../../../../include/crown/runtime/ranking_evidence.hpp) |

## B0035

[Lines 235–235](../../../../../src/runtime/ranking_evidence.cpp#L235); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L235-L235:sha256:533f16bca7d58f44b3103b92e3485d22cfbb34bbad5ea3f3fa3b5a9dcb24ec89
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Close the \`anonymous namespace in src/runtime/ranking_evidence.cpp\` scope at this exact source boundary. |
| inputs / outputs | This token introduces no callable inputs or outputs. Declarations inside \`anonymous namespace in src/runtime/ranking_evidence.cpp\` define the available names, members and operations. |
| invariants | The closing brace matches the opening \`anonymous namespace in src/runtime/ranking_evidence.cpp\` at its lexical source position in src/runtime/ranking_evidence.cpp; it preserves C++ namespace/type nesting. |
| ownership | The closing delimiter creates no owner. Types closed by \`anonymous namespace in src/runtime/ranking_evidence.cpp\` retain the lifetimes and allocator rules of their own fields and operations. |
| failure | No failure path executes at this closing delimiter. Failure and cleanup behavior belong to enclosed functions and owning types. |
| cost | The delimiter itself performs no runtime work; the enclosed initializers, methods and destructors carry their own costs. |
| Design | [docs/selection.md](../../../../selection.md), [docs/selection_binding.md](../../../../selection_binding.md), [docs/selection_accounting.md](../../../../selection_accounting.md), [docs/reoptimization.md](../../../../reoptimization.md), [docs/code_specs/subsystem_contracts.md](../../../subsystem_contracts.md) |

## B0036

[Lines 236–236](../../../../../src/runtime/ranking_evidence.cpp#L236); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
detail::Census detail::classify_census(const workload::Snapshot& s,rd::Budget& b){return census(s,b);}
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Expose the private numeric census classifier for isolated boundary tests. |
| inputs / outputs | Snapshot and shared processing Budget forward to census and return owning numeric Census. |
| invariants | Cannot construct actual-owner public Evidence or manufacture proof/freshness authority. |
| ownership | Output vector uses snapshot plan account; inputs borrowed for call. |
| failure | Typed budget/allocation errors propagate; no extra catch. |
| cost | Constant forwarding plus complete census scans/allocations. |
| Design | [docs/ranking.md](../../../../ranking.md), [docs/ranking_accounting.md](../../../../ranking_accounting.md), [include/crown/runtime/ranking_evidence.hpp](../../../../../include/crown/runtime/ranking_evidence.hpp) |

## B0037

[Lines 237–237](../../../../../src/runtime/ranking_evidence.cpp#L237); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
CaptureAttempt capture(const planner::CandidateSnapshot& s,const PhysicalRuntime& o,const CaptureOptions& l) noexcept{return capture_impl(s,o,l);}
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Expose synchronized candidate-bound capture for PhysicalRuntime. |
| inputs / outputs | Snapshot,actual owner,CaptureOptions forward once to capture_impl and return CaptureAttempt. |
| invariants | No alternate admission, synthetic observations, height proof or owner mutation added by overload. |
| ownership | Owner borrowed during call; returned Evidence owns immutable original-account payload. |
| failure | noexcept delegates failure classification to capture_impl. |
| cost | Constant dispatch plus full capture/binding/census costs. |
| Design | [docs/ranking.md](../../../../ranking.md), [docs/ranking_accounting.md](../../../../ranking_accounting.md), [include/crown/runtime/ranking_evidence.hpp](../../../../../include/crown/runtime/ranking_evidence.hpp) |

## B0038

[Lines 238–238](../../../../../src/runtime/ranking_evidence.cpp#L238); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
CaptureAttempt capture(const planner::CandidateSnapshot& s,const DeltaRuntime& o,const CaptureOptions& l) noexcept{return capture_impl(s,o,l);}
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Expose synchronized candidate-bound capture for DeltaRuntime. |
| inputs / outputs | Snapshot,actual owner,CaptureOptions forward once to capture_impl and return CaptureAttempt. |
| invariants | No alternate admission, synthetic observations, height proof or owner mutation added by overload. |
| ownership | Owner borrowed during call; returned Evidence owns immutable original-account payload. |
| failure | noexcept delegates failure classification to capture_impl. |
| cost | Constant dispatch plus full capture/binding/census costs. |
| Design | [docs/ranking.md](../../../../ranking.md), [docs/ranking_accounting.md](../../../../ranking_accounting.md), [include/crown/runtime/ranking_evidence.hpp](../../../../../include/crown/runtime/ranking_evidence.hpp) |

## B0039

[Lines 239–239](../../../../../src/runtime/ranking_evidence.cpp#L239); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
CaptureAttempt capture(const planner::CandidateSnapshot& s,const QuerySession& o,const CaptureOptions& l) noexcept{return capture_impl(s,o,l);}
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Expose synchronized candidate-bound capture for QuerySession. |
| inputs / outputs | Snapshot,actual owner,CaptureOptions forward once to capture_impl and return CaptureAttempt. |
| invariants | No alternate admission, synthetic observations, height proof or owner mutation added by overload. |
| ownership | Owner borrowed during call; returned Evidence owns immutable original-account payload. |
| failure | noexcept delegates failure classification to capture_impl. |
| cost | Constant dispatch plus full capture/binding/census costs. |
| Design | [docs/ranking.md](../../../../ranking.md), [docs/ranking_accounting.md](../../../../ranking_accounting.md), [include/crown/runtime/ranking_evidence.hpp](../../../../../include/crown/runtime/ranking_evidence.hpp) |

## B0040

[Lines 240–240](../../../../../src/runtime/ranking_evidence.cpp#L240); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Revalidation revalidate(const RuntimeEvidence& e,const PhysicalRuntime& o) noexcept{return revalidate_impl(e,o);}
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Expose typed actual-owner revalidation for PhysicalRuntime. |
| inputs / outputs | RuntimeEvidence/owner forward to revalidate_impl; returns boundary/depth/memory reasons. |
| invariants | Reports current usability without modifying old evidence or granting a new plan/source boundary. |
| ownership | Borrows handles; delegated temporary capture owns/releases its own original-account memory. |
| failure | noexcept delegates read/processing failures to reason boundaries. |
| cost | Constant wrapper plus potentially allocating full revalidation diagnostic. |
| Design | [docs/ranking.md](../../../../ranking.md), [docs/ranking_accounting.md](../../../../ranking_accounting.md), [include/crown/runtime/ranking_evidence.hpp](../../../../../include/crown/runtime/ranking_evidence.hpp) |

## B0041

[Lines 241–241](../../../../../src/runtime/ranking_evidence.cpp#L241); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Revalidation revalidate(const RuntimeEvidence& e,const DeltaRuntime& o) noexcept{return revalidate_impl(e,o);}
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Expose typed actual-owner revalidation for DeltaRuntime. |
| inputs / outputs | RuntimeEvidence/owner forward to revalidate_impl; returns boundary/depth/memory reasons. |
| invariants | Reports current usability without modifying old evidence or granting a new plan/source boundary. |
| ownership | Borrows handles; delegated temporary capture owns/releases its own original-account memory. |
| failure | noexcept delegates read/processing failures to reason boundaries. |
| cost | Constant wrapper plus potentially allocating full revalidation diagnostic. |
| Design | [docs/ranking.md](../../../../ranking.md), [docs/ranking_accounting.md](../../../../ranking_accounting.md), [include/crown/runtime/ranking_evidence.hpp](../../../../../include/crown/runtime/ranking_evidence.hpp) |

## B0042

[Lines 242–242](../../../../../src/runtime/ranking_evidence.cpp#L242); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Revalidation revalidate(const RuntimeEvidence& e,const QuerySession& o) noexcept{return revalidate_impl(e,o);}
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Expose typed actual-owner revalidation for QuerySession. |
| inputs / outputs | RuntimeEvidence/owner forward to revalidate_impl; returns boundary/depth/memory reasons. |
| invariants | Reports current usability without modifying old evidence or granting a new plan/source boundary. |
| ownership | Borrows handles; delegated temporary capture owns/releases its own original-account memory. |
| failure | noexcept delegates read/processing failures to reason boundaries. |
| cost | Constant wrapper plus potentially allocating full revalidation diagnostic. |
| Design | [docs/ranking.md](../../../../ranking.md), [docs/ranking_accounting.md](../../../../ranking_accounting.md), [include/crown/runtime/ranking_evidence.hpp](../../../../../include/crown/runtime/ranking_evidence.hpp) |

## B0043

[Lines 243–243](../../../../../src/runtime/ranking_evidence.cpp#L243); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
pr::Attempt rank_current(const planner::CandidateSnapshot& s,const PhysicalRuntime& o,const pr::Request& r,statistics::Limits l) noexcept{return current_impl(s,o,r,l);}
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Expose current ranking against PhysicalRuntime through the common policy path. |
| inputs / outputs | Snapshot,actual owner,Request,state limits forward to current_impl. |
| invariants | Policy controls needed facts; no automatic C03/time forecast or bypass of structural proof/binding. |
| ownership | Returned ranking Result owns original-account data; no mutable owner retained. |
| failure | noexcept common rank/capture stops, without another handler layer. |
| cost | Constant dispatch plus selected capture/rank/lowering work. |
| Design | [docs/ranking.md](../../../../ranking.md), [docs/ranking_accounting.md](../../../../ranking_accounting.md), [include/crown/runtime/ranking_evidence.hpp](../../../../../include/crown/runtime/ranking_evidence.hpp) |

## B0044

[Lines 244–244](../../../../../src/runtime/ranking_evidence.cpp#L244); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
pr::Attempt rank_current(const planner::CandidateSnapshot& s,const DeltaRuntime& o,const pr::Request& r,statistics::Limits l) noexcept{return current_impl(s,o,r,l);}
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Expose current ranking against DeltaRuntime through the common policy path. |
| inputs / outputs | Snapshot,actual owner,Request,state limits forward to current_impl. |
| invariants | Policy controls needed facts; no automatic C03/time forecast or bypass of structural proof/binding. |
| ownership | Returned ranking Result owns original-account data; no mutable owner retained. |
| failure | noexcept common rank/capture stops, without another handler layer. |
| cost | Constant dispatch plus selected capture/rank/lowering work. |
| Design | [docs/ranking.md](../../../../ranking.md), [docs/ranking_accounting.md](../../../../ranking_accounting.md), [include/crown/runtime/ranking_evidence.hpp](../../../../../include/crown/runtime/ranking_evidence.hpp) |

## B0045

[Lines 245–245](../../../../../src/runtime/ranking_evidence.cpp#L245); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
pr::Attempt rank_current(const planner::CandidateSnapshot& s,const QuerySession& o,const pr::Request& r,statistics::Limits l) noexcept{return current_impl(s,o,r,l);}
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Expose current ranking against QuerySession through the common policy path. |
| inputs / outputs | Snapshot,actual owner,Request,state limits forward to current_impl. |
| invariants | Policy controls needed facts; no automatic C03/time forecast or bypass of structural proof/binding. |
| ownership | Returned ranking Result owns original-account data; no mutable owner retained. |
| failure | noexcept common rank/capture stops, without another handler layer. |
| cost | Constant dispatch plus selected capture/rank/lowering work. |
| Design | [docs/ranking.md](../../../../ranking.md), [docs/ranking_accounting.md](../../../../ranking_accounting.md), [include/crown/runtime/ranking_evidence.hpp](../../../../../include/crown/runtime/ranking_evidence.hpp) |

## B0046

[Lines 246–246](../../../../../src/runtime/ranking_evidence.cpp#L246); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L246-L246:sha256:c7273f0ff9fe9c4dd8862e0cedd6c9cf2494b27833f48915bf60e4e1c502d71e
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Close the \`namespace crown::runtime::ranking\` scope at this exact source boundary. |
| inputs / outputs | This token introduces no callable inputs or outputs. Declarations inside \`namespace crown::runtime::ranking\` define the available names, members and operations. |
| invariants | The closing brace matches the opening \`namespace crown::runtime::ranking\` at its lexical source position in src/runtime/ranking_evidence.cpp; it preserves C++ namespace/type nesting. |
| ownership | The closing delimiter creates no owner. Types closed by \`namespace crown::runtime::ranking\` retain the lifetimes and allocator rules of their own fields and operations. |
| failure | No failure path executes at this closing delimiter. Failure and cleanup behavior belong to enclosed functions and owning types. |
| cost | The delimiter itself performs no runtime work; the enclosed initializers, methods and destructors carry their own costs. |
| Design | [docs/selection.md](../../../../selection.md), [docs/selection_binding.md](../../../../selection_binding.md), [docs/selection_accounting.md](../../../../selection_accounting.md), [docs/reoptimization.md](../../../../reoptimization.md), [docs/code_specs/subsystem_contracts.md](../../../subsystem_contracts.md) |
