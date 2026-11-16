# `src/runtime/maintenance_cost.cpp` — block usage map

[Source](../../../../../src/runtime/maintenance_cost.cpp) · [Source index](../../../README.md) · [Subsystem contracts](../../../subsystem_contracts.md) · [Reviewed primitives](../../../primitives.md)

Capture bounded distributions, workload counters, owner memory and explain observations without mislabeling partial information as exact.

Snapshot SHA-256: `91baec0964c4532229071d2dd101f58798476b804f477a4563c1483546eb089c`. 441 lines partitioned into 53 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [statistics](../../../subsystem_contracts.md#statistics). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/statistics.md](../../../../statistics.md), [docs/observability.md](../../../../observability.md), [docs/memory_reports.md](../../../../memory_reports.md), [docs/ranking_evaluation.md](../../../../ranking_evaluation.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–12](../../../../../src/runtime/maintenance_cost.cpp#L1) | Imports dependencies; declares namespace scope; declares values/defaults or compile-time conditions. |  · [reviewed contract](#b0001) |
| [B0002 · 13–15](../../../../../src/runtime/maintenance_cost.cpp#L13) | Callable definition: template&lt;class T&gt; auto allocator(const resource::MemoryAccount& a) | calls ; returns resource::OwnerAllocator&lt;T&gt;(a,resource::MemoryPurpose::capture,memory_owner) · [reviewed contract](#b0002) |
| [B0003 · 16–23](../../../../../src/runtime/maintenance_cost.cpp#L16) | Type/record definition: struct CalibrationData |  · [reviewed contract](#b0003) |
| [B0004 · 24–28](../../../../../src/runtime/maintenance_cost.cpp#L24) | Type/record definition: struct ProfileData |  · [reviewed contract](#b0004) |
| [B0005 · 29–37](../../../../../src/runtime/maintenance_cost.cpp#L29) | Type/record definition: struct ResultData |  · [reviewed contract](#b0005) |
| [B0006 · 38–42](../../../../../src/runtime/maintenance_cost.cpp#L38) | Type/record definition: struct Factory | returns Calibration(std::move(p)); Profile(std::move(p)) · [reviewed contract](#b0006) |
| [B0007 · 43–43](../../../../../src/runtime/maintenance_cost.cpp#L43) | Closes surrounding scope/type. |  · [reviewed contract](#b0007) |
| [B0008 · 44–44](../../../../../src/runtime/maintenance_cost.cpp#L44) | Callable definition: const std::array&lt;std::optional&lt;Coefficient&gt;,component_count&gt;& Calibration::coefficients() const noexcept | calls ; returns data_-&gt;coefficients · [reviewed contract](#b0008) |
| [B0009 · 45–45](../../../../../src/runtime/maintenance_cost.cpp#L45) | Callable definition: std::string_view Calibration::context() const noexcept | calls ; returns data_-&gt;context · [reviewed contract](#b0009) |
| [B0010 · 46–46](../../../../../src/runtime/maintenance_cost.cpp#L46) | Callable definition: std::string_view Calibration::backend() const noexcept | calls ; returns data_-&gt;backend · [reviewed contract](#b0010) |
| [B0011 · 47–47](../../../../../src/runtime/maintenance_cost.cpp#L47) | Callable definition: CalibrationOrigin Calibration::origin() const noexcept | calls ; returns data_-&gt;origin · [reviewed contract](#b0011) |
| [B0012 · 48–48](../../../../../src/runtime/maintenance_cost.cpp#L48) | Callable definition: const std::optional&lt;FitSummary&gt;& Calibration::fit_summary() const noexcept | calls ; returns data_-&gt;summary · [reviewed contract](#b0012) |
| [B0013 · 49–49](../../../../../src/runtime/maintenance_cost.cpp#L49) | Callable definition: std::span&lt;const FitObservation&gt; Calibration::fit_observations() const noexcept | calls ; returns data_-&gt;observations · [reviewed contract](#b0013) |
| [B0014 · 50–50](../../../../../src/runtime/maintenance_cost.cpp#L50) | Callable definition: const planner::MinimumHeightCandidate& Profile::candidate() const noexcept | calls ; returns data_-&gt;candidate · [reviewed contract](#b0014) |
| [B0015 · 51–51](../../../../../src/runtime/maintenance_cost.cpp#L51) | Callable definition: const runtime::ranking::RuntimeEvidence& Profile::evidence() const noexcept | calls ; returns data_-&gt;evidence · [reviewed contract](#b0015) |
| [B0016 · 52–52](../../../../../src/runtime/maintenance_cost.cpp#L52) | Callable definition: const resource::MemoryStatistics& Profile::memory_at_capture() const noexcept | calls ; returns data_-&gt;memory · [reviewed contract](#b0016) |
| [B0017 · 53–54](../../../../../src/runtime/maintenance_cost.cpp#L53) | Callable definition: CandidateEstimate::CandidateEstimate(const resource::MemoryAccount& a,planner::MinimumHeightCandidate c) :candidate(std::move(c))… | calls candidate, std::move, terms · [reviewed contract](#b0017) |
| [B0018 · 55–55](../../../../../src/runtime/maintenance_cost.cpp#L55) | Callable definition: const pr::ScoreVector&lt;CandidateEstimate&gt;& Result::candidates() const noexcept | calls ; returns data_-&gt;candidates · [reviewed contract](#b0018) |
| [B0019 · 56–56](../../../../../src/runtime/maintenance_cost.cpp#L56) | Callable definition: const Calibration& Result::calibration() const noexcept | calls ; returns data_-&gt;calibration · [reviewed contract](#b0019) |
| [B0020 · 57–57](../../../../../src/runtime/maintenance_cost.cpp#L57) | Callable definition: const pr::Usage& Result::usage() const noexcept | calls ; returns data_-&gt;usage · [reviewed contract](#b0020) |
| [B0021 · 58–58](../../../../../src/runtime/maintenance_cost.cpp#L58) | Callable definition: std::span&lt;const InputDemand&gt; Result::input_demand() const noexcept | calls ; returns data_-&gt;input · [reviewed contract](#b0021) |
| [B0022 · 59–59](../../../../../src/runtime/maintenance_cost.cpp#L59) | Callable definition: const OutputDemand& Result::output_demand() const noexcept | calls ; returns data_-&gt;output · [reviewed contract](#b0022) |
| [B0023 · 60–66](../../../../../src/runtime/maintenance_cost.cpp#L60) | Callable definition: std::string_view component_name(Component c) noexcept | calls size; returns i&lt;names.size()?names\[i\]:@ · [reviewed contract](#b0023) |
| [B0024 · 67–67](../../../../../src/runtime/maintenance_cost.cpp#L67) | declares namespace scope. |  · [reviewed contract](#b0024) |
| [B0025 · 68–68](../../../../../src/runtime/maintenance_cost.cpp#L68) | Callable definition: void require(bool value,pr::Stop stop=pr::Stop::invalid_limits) | calls ; guard void require(bool value,pr::Stop stop=pr::Stop::invalid_limits){if(!value)throw rd::Failure{stop};} · [reviewed contract](#b0025) |
| [B0026 · 69–69](../../../../../src/runtime/maintenance_cost.cpp#L69) | Callable definition: U64 add(U64 a,U64 b) | calls require; guard U64 add(U64 a,U64 b) {require(b&lt;=UINT64_MAX-a,pr::Stop::bit_limit);return a+b;}; returns a+b · [reviewed contract](#b0026) |
| [B0027 · 70–70](../../../../../src/runtime/maintenance_cost.cpp#L70) | Callable definition: U64 multiply(U64 a,U64 b) | calls require; guard U64 multiply(U64 a,U64 b) {require(!a \|\| b&lt;=UINT64_MAX/a,pr::Stop::bit_limit);return a*b;}; returns a*b · [reviewed contract](#b0027) |
| [B0028 · 71–71](../../../../../src/runtime/maintenance_cost.cpp#L71) | Callable definition: Ratio ratio(U64 n,U64 d=1) | calls require, std::gcd; guard Ratio ratio(U64 n,U64 d=1) {require(d!=0);const auto g=std::gcd(n,d);return {n/g,d/g};}; returns {n/g,d/g} · [reviewed contract](#b0028) |
| [B0029 · 72–75](../../../../../src/runtime/maintenance_cost.cpp#L72) | Callable definition: Ratio times(Ratio a,Ratio b) | calls std::gcd, ratio, multiply; returns ratio(multiply(a.numerator/x,b.numerator/y),multiply(a.denominator/y,b.denominator/x)) · [reviewed contract](#b0029) |
| [B0030 · 76–81](../../../../../src/runtime/maintenance_cost.cpp#L76) | Callable definition: Ratio plus(Ratio a,Ratio b) | calls std::gcd, add, multiply; returns {n/h,multiply(a.denominator/g,b.denominator/h)}; source comment (unverified): // Cancel before the final denominator multiplication. · [reviewed contract](#b0030) |
| [B0031 · 82–85](../../../../../src/runtime/maintenance_cost.cpp#L82) | Callable definition: void check_bits(Ratio value,const rd::Budget& budget) | calls require, std::bit_width; guard require(static_cast&lt;unsigned&gt;(std::bit_width(value.numerator))&lt;=budget.limits.score_bits && · [reviewed contract](#b0031) |
| [B0032 · 86–88](../../../../../src/runtime/maintenance_cost.cpp#L86) | Callable definition: bool same_candidate(const planner::MinimumHeightCandidate& a,const planner::MinimumHeightCandidate& b,rd::Budget& budget) | calls valid, rd::equal_bytes, structural_key; returns a.valid() && b.valid() && rd::equal_bytes(a.structural_key(),b.structural_key(),budget) · [reviewed contract](#b0032) |
| [B0033 · 89–105](../../../../../src/runtime/maintenance_cost.cpp#L89) | Callable definition: template&lt;class Append&gt; void components(const workload::Descriptor& descriptor,const workload::Cell& cell,Append append) | calls append, add · [reviewed contract](#b0033) |
| [B0034 · 106–151](../../../../../src/runtime/maintenance_cost.cpp#L106) | Callable definition: template&lt;class Owner&gt; CaptureAttempt capture_impl(const planner::CandidateSnapshot& snapshot,std::size_t index,const Owner& owner… | calls require, valid, candidate, has_value; guard require(snapshot.valid(),pr::Stop::invalid_handle);const auto candidate=snapshot.candidate(index);r…; returns out; out; growth emplace, make_accounted_shared; source comment (unverified): // Explicit cold diagnostic: capture and re-lower against the actual owner. · [reviewed contract](#b0034) |
| [B0035 · 152–152](../../../../../src/runtime/maintenance_cost.cpp#L152) | Type/record definition: enum class Group |  · [reviewed contract](#b0035) |
| [B0036 · 153–160](../../../../../src/runtime/maintenance_cost.cpp#L153) | Callable definition: Group group(Component c) | calls ; returns Group::annotation; Group::snapshot · [reviewed contract](#b0036) |
| [B0037 · 161–161](../../../../../src/runtime/maintenance_cost.cpp#L161) | Type/record definition: struct Sums |  · [reviewed contract](#b0037) |
| [B0038 · 162–177](../../../../../src/runtime/maintenance_cost.cpp#L162) | Callable definition: void term(CandidateEstimate& out,Sums& sums,const Calibration& calibration,Component component, std::optional&lt;Ratio&gt; units,Confid… | calls work, coefficients, times, issue; growth push_back; 1 loop sites · [reviewed contract](#b0038) |
| [B0039 · 178–181](../../../../../src/runtime/maintenance_cost.cpp#L178) | Callable definition: U64 demanded(std::span&lt;const InputDemand&gt; demand,const workload::Descriptor& descriptor,rd::Budget& budget) | calls work; returns d.inputs; 1 loop sites · [reviewed contract](#b0039) |
| [B0040 · 182–187](../../../../../src/runtime/maintenance_cost.cpp#L182) | Callable definition: std::optional&lt;std::size_t&gt; root_descriptor(const workload::Snapshot& snapshot,const workload::Descriptor& d,rd::Budget& budget) | calls descriptors, size, work; returns i; {}; 1 loop sites · [reviewed contract](#b0040) |
| [B0041 · 188–256](../../../../../src/runtime/maintenance_cost.cpp#L188) | Callable definition: void evaluate(CandidateEstimate& out,const Profile& profile,const Calibration& calibration,const Request& request,rd::Budget& bud… | calls evidence, captured, workload, descriptors; guard require(descriptors.size()==cells.size(),pr::Stop::binding_mismatch);; returns sums.unknown\[index\]?std::nullopt:std::optional&lt;Ratio&gt;{sums.values\[index\]}; x; growth reserve; 4 loop sites; source comment (unverified): // Price immutable stratum observations under caller demand assumptions. · [reviewed contract](#b0041) |
| [B0042 · 257–257](../../../../../src/runtime/maintenance_cost.cpp#L257) | Closes surrounding scope/type. |  · [reviewed contract](#b0042) |
| [B0043 · 258–273](../../../../../src/runtime/maintenance_cost.cpp#L258) | Callable definition: FeatureAttempt features(const workload::Snapshot& snapshot,pr::Limits limits) noexcept | calls emplace, work, stamp, require; guard require(!snapshot.pending() && snapshot.detail_availability()==workload::Availability::exact &&; returns out; growth emplace; 1 loop sites · [reviewed contract](#b0043) |
| [B0044 · 274–295](../../../../../src/runtime/maintenance_cost.cpp#L274) | Callable definition: CalibrationAttempt calibrate(const resource::MemoryAccount& account,std::string_view context,std::string_view backend, std::span&lt;… | calls emplace, require, bool, empty; guard budget.emplace(limits,pr::Usage{},account);auto& b=*budget;require(bool(account) && !context.empty(…; returns out; growth emplace, make_accounted_shared; 1 loop sites · [reviewed contract](#b0044) |
| [B0045 · 296–383](../../../../../src/runtime/maintenance_cost.cpp#L296) | Callable definition: CalibrationAttempt fit(const resource::MemoryAccount& account,std::string_view context,std::string_view backend, std::span&lt;const … | calls emplace, require, bool, empty; guard require(bool(account) && !context.empty() && !backend.empty() && !observations.empty());; returns out; growth emplace, make_accounted_shared; 18 loop sites; source comment (unverified): // Floating fitting is an inference over caller timings. Published rates are · [reviewed contract](#b0045) |
| [B0046 · 384–384](../../../../../src/runtime/maintenance_cost.cpp#L384) | Callable definition: CaptureAttempt capture(const planner::CandidateSnapshot& s,std::size_t i,const PhysicalRuntime& o,pr::Limits l) noexcept | calls capture_impl; returns capture_impl(s,i,o,l) · [reviewed contract](#b0046) |
| [B0047 · 385–385](../../../../../src/runtime/maintenance_cost.cpp#L385) | Callable definition: CaptureAttempt capture(const planner::CandidateSnapshot& s,std::size_t i,const DeltaRuntime& o,pr::Limits l) noexcept | calls capture_impl; returns capture_impl(s,i,o,l) · [reviewed contract](#b0047) |
| [B0048 · 386–386](../../../../../src/runtime/maintenance_cost.cpp#L386) | Callable definition: CaptureAttempt capture(const planner::CandidateSnapshot& s,std::size_t i,const QuerySession& o,pr::Limits l) noexcept | calls capture_impl; returns capture_impl(s,i,o,l) · [reviewed contract](#b0048) |
| [B0049 · 387–387](../../../../../src/runtime/maintenance_cost.cpp#L387) | Callable definition: runtime::ranking::Revalidation revalidate(const Profile& p,const PhysicalRuntime& o) noexcept | calls runtime::ranking::revalidate, evidence; returns runtime::ranking::revalidate(p.evidence(),o) · [reviewed contract](#b0049) |
| [B0050 · 388–388](../../../../../src/runtime/maintenance_cost.cpp#L388) | Callable definition: runtime::ranking::Revalidation revalidate(const Profile& p,const DeltaRuntime& o) noexcept | calls runtime::ranking::revalidate, evidence; returns runtime::ranking::revalidate(p.evidence(),o) · [reviewed contract](#b0050) |
| [B0051 · 389–389](../../../../../src/runtime/maintenance_cost.cpp#L389) | Callable definition: runtime::ranking::Revalidation revalidate(const Profile& p,const QuerySession& o) noexcept | calls runtime::ranking::revalidate, evidence; returns runtime::ranking::revalidate(p.evidence(),o) · [reviewed contract](#b0051) |
| [B0052 · 390–440](../../../../../src/runtime/maintenance_cost.cpp#L390) | Callable definition: Attempt estimate(const resource::MemoryAccount& account,const planner::CandidateSnapshot& snapshot, std::span&lt;const Profile&gt; prof… | calls emplace, require, bool, valid; guard require(bool(account) && request.memory_budget_bytes&gt;0);require(snapshot.valid(),pr::Stop::invalid_…; returns out; growth emplace, emplace_back, insert, make_accounted_shared, reserve; 7 loop sites; source comment (unverified): // Build the complete receiving-account result privately. The existing outer · [reviewed contract](#b0052) |
| [B0053 · 441–441](../../../../../src/runtime/maintenance_cost.cpp#L441) | Closes surrounding scope/type. | source comment (unverified): // namespace crown::runtime::cost · [reviewed contract](#b0053) |

## B0001

[Lines 1–12](../../../../../src/runtime/maintenance_cost.cpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
#include "crown/runtime/maintenance_cost.hpp"
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Assemble the opt-in maintenance estimator and its accounted capture attribution. |
| inputs / outputs | Includes model, ranking budget, account ownership and arithmetic helpers; binds rd to the existing ranking implementation and owner capture/42. |
| invariants | This is a local diagnostic/cost-model component. It does not enable a query operator or certify a paper time bound. |
| ownership | Declarations retain no account or runtime. Instantiated containers below retain their supplied account. |
| failure | No runtime action or error boundary is introduced by these declarations. |
| cost | No dynamic runtime cost for includes, namespace alias or attribution constant. |
| Design | [docs/maintenance_cost.md](../../../../maintenance_cost.md), [include/crown/runtime/maintenance_cost.hpp](../../../../../include/crown/runtime/maintenance_cost.hpp), [docs/code_review.md](../../../../code_review.md) |

## B0002

[Lines 13–15](../../../../../src/runtime/maintenance_cost.cpp#L13); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
template<class T> auto allocator(const resource::MemoryAccount& a) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Construct the allocator used by retained cost-model payloads. |
| inputs / outputs | A readable MemoryAccount becomes OwnerAllocator&lt;T&gt; with capture purpose and capture/42 attribution. |
| invariants | Allocator construction transfers allocation authority; it neither creates a fresh limit nor admits payload storage. |
| ownership | Returned allocator retains the same account. Coefficients, text, observations and result terms use it. |
| failure | No allocation is requested here; later container growth can fail against this account or upstream allocation. |
| cost | Constant account/allocator handle work. |
| Design | [docs/maintenance_cost.md](../../../../maintenance_cost.md), [include/crown/runtime/maintenance_cost.hpp](../../../../../include/crown/runtime/maintenance_cost.hpp), [docs/query_memory.md](../../../../query_memory.md) |

## B0003

[Lines 16–23](../../../../../src/runtime/maintenance_cost.cpp#L16); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct CalibrationData {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Own one immutable calibration, its labels, component rates and optional fit evidence. |
| inputs / outputs | Constructor takes the receiving account and initializes context/backend strings plus raw-observation vector; factories populate coefficients, origin and summary privately. |
| invariants | Missing component coefficients stay optional. Isolated measurements and inferred linear rates have different origins; fitted raw timings are not duplicated per component. |
| ownership | Text/vector payload and shared control are charged to the receiving account. Fixed arrays and summary live within this object; returned Calibration shares const Data. |
| failure | Container construction/assignment may fail before publication; the local shared owner releases partial payload. No mutable owner/query state is involved. |
| cost | Fixed component array plus retained label bytes and observation_count * component_count units; default containers start empty. |
| Design | [docs/maintenance_cost.md](../../../../maintenance_cost.md), [include/crown/runtime/maintenance_cost.hpp](../../../../../include/crown/runtime/maintenance_cost.hpp) |

## B0004

[Lines 24–28](../../../../../src/runtime/maintenance_cost.cpp#L24); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct ProfileData {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Retain the checked candidate, actual captured runtime evidence and pre-capture account observation. |
| inputs / outputs | ProfileData contains MinimumHeightCandidate, RuntimeEvidence and a by-value MemoryStatistics snapshot. |
| invariants | Memory is the owner account observed before this cost-profile capture; it is not a future peak estimate or whole-process measurement. |
| ownership | Candidate/evidence share their original immutable payloads; this object owns only their handles and copied memory counters. |
| failure | Construction occurs privately in capture_impl; account or replay failure prevents Profile publication. |
| cost | Constant handle/counter storage in addition to the already retained candidate/evidence graph. |
| Design | [docs/maintenance_cost.md](../../../../maintenance_cost.md), [include/crown/runtime/maintenance_cost.hpp](../../../../../include/crown/runtime/maintenance_cost.hpp), [src/runtime/ranking_evidence.cpp](../../../../../src/runtime/ranking_evidence.cpp), [docs/query_memory.md](../../../../query_memory.md) |

## B0005

[Lines 29–37](../../../../../src/runtime/maintenance_cost.cpp#L29); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct ResultData {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Own a completed estimate and copied demand without borrowing the caller Request. |
| inputs / outputs | Constructor takes receiver account, Calibration and OutputDemand; candidates and input vectors use capture/42 allocator. |
| invariants | Result publication follows all candidate estimates and final time admission. Missing profiles/unknown terms are represented explicitly inside a completed result. |
| ownership | Shares Calibration and candidate/profile handles; owns receiver-funded input/estimate/term arrays and by-value output/usage. |
| failure | Any pre-publication failure destroys private arrays/handles and returns an Attempt stop through estimate. |
| cost | Fixed object plus input_count, candidate_count and per-candidate term capacities; retained foreign handles keep their original accounts alive. |
| Design | [docs/maintenance_cost.md](../../../../maintenance_cost.md), [include/crown/runtime/maintenance_cost.hpp](../../../../../include/crown/runtime/maintenance_cost.hpp) |

## B0006

[Lines 38–42](../../../../../src/runtime/maintenance_cost.cpp#L38); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct Factory {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Restrict construction of Calibration, Profile and Result handles to checked private factories. |
| inputs / outputs | Three static functions accept shared_ptr&lt;const corresponding Data&gt; and move each into its public owning handle. |
| invariants | Factories assume a non-null fully initialized private payload; they perform no validation/replay themselves. |
| ownership | Moves a shared owner into the public immutable handle; no rows or runtime pointers are borrowed. |
| failure | These shared_ptr handle transfers allocate no new payload and add no recovery protocol. |
| cost | Constant handle move per factory, without payload copies. |
| Design | [docs/maintenance_cost.md](../../../../maintenance_cost.md), [include/crown/runtime/maintenance_cost.hpp](../../../../../include/crown/runtime/maintenance_cost.hpp) |

## B0007

[Lines 43–43](../../../../../src/runtime/maintenance_cost.cpp#L43); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L43-L43:sha256:412ca345ccf75bf9c0806bce695be8de808b79984251a7a54d202cf6101dd451
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Close the \`namespace detail\` scope at this exact source boundary. |
| inputs / outputs | This token introduces no callable inputs or outputs. Declarations inside \`namespace detail\` define the available names, members and operations. |
| invariants | The closing brace matches the opening \`namespace detail\` at its lexical source position in src/runtime/maintenance_cost.cpp; it preserves C++ namespace/type nesting. |
| ownership | The closing delimiter creates no owner. Types closed by \`namespace detail\` retain the lifetimes and allocator rules of their own fields and operations. |
| failure | No failure path executes at this closing delimiter. Failure and cleanup behavior belong to enclosed functions and owning types. |
| cost | The delimiter itself performs no runtime work; the enclosed initializers, methods and destructors carry their own costs. |
| Design | [docs/maintenance_cost.md](../../../../maintenance_cost.md), [docs/workloads.md](../../../../workloads.md), [docs/code_specs/subsystem_contracts.md](../../../subsystem_contracts.md) |

## B0008

[Lines 44–44](../../../../../src/runtime/maintenance_cost.cpp#L44); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
const std::array<std::optional<Coefficient>,component_count>& Calibration::coefficients() const noexcept{return data_->coefficients;}
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Read the component coefficient array from a Calibration. |
| inputs / outputs | A readable factory-produced Calibration returns its component coefficient array as const array reference. |
| invariants | Missing rates remain optional; isolated/fitted origins must be read separately. |
| ownership | Borrows immutable Calibration payload; retain a readable owning handle for the whole reference/view lifetime. Do not call through a moved-from handle. |
| failure | No validation, allocation, clock, catch or owner mutation on this accessor path. |
| cost | Constant pointer/member access; no scan or deep copy. |
| Design | [docs/maintenance_cost.md](../../../../maintenance_cost.md), [include/crown/runtime/maintenance_cost.hpp](../../../../../include/crown/runtime/maintenance_cost.hpp) |

## B0009

[Lines 45–45](../../../../../src/runtime/maintenance_cost.cpp#L45); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::string_view Calibration::context() const noexcept{return data_->context;}
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Read the environment/context label from a Calibration. |
| inputs / outputs | A readable factory-produced Calibration returns its environment/context label as string_view. |
| invariants | A caller label describes the supplied context; it does not certify measurement quality. |
| ownership | Borrows immutable Calibration payload; retain a readable owning handle for the whole reference/view lifetime. Do not call through a moved-from handle. |
| failure | No validation, allocation, clock, catch or owner mutation on this accessor path. |
| cost | Constant pointer/member access; no scan or deep copy. |
| Design | [docs/maintenance_cost.md](../../../../maintenance_cost.md), [include/crown/runtime/maintenance_cost.hpp](../../../../../include/crown/runtime/maintenance_cost.hpp) |

## B0010

[Lines 46–46](../../../../../src/runtime/maintenance_cost.cpp#L46); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::string_view Calibration::backend() const noexcept{return data_->backend;}
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Read the storage-backend label from a Calibration. |
| inputs / outputs | A readable factory-produced Calibration returns its storage-backend label as string_view. |
| invariants | evaluate compares this exact label with the captured plan backend. |
| ownership | Borrows immutable Calibration payload; retain a readable owning handle for the whole reference/view lifetime. Do not call through a moved-from handle. |
| failure | No validation, allocation, clock, catch or owner mutation on this accessor path. |
| cost | Constant pointer/member access; no scan or deep copy. |
| Design | [docs/maintenance_cost.md](../../../../maintenance_cost.md), [include/crown/runtime/maintenance_cost.hpp](../../../../../include/crown/runtime/maintenance_cost.hpp) |

## B0011

[Lines 47–47](../../../../../src/runtime/maintenance_cost.cpp#L47); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
CalibrationOrigin Calibration::origin() const noexcept{return data_->origin;}
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Read the calibration origin from a Calibration. |
| inputs / outputs | A readable factory-produced Calibration returns its calibration origin as CalibrationOrigin value. |
| invariants | Distinguishes isolated measurement ratios from fitted_linear_assumption. |
| ownership | Returns an inline enum copy; the owner retains the payload. |
| failure | No validation, allocation, clock, catch or owner mutation on this accessor path. |
| cost | Constant pointer/member access; no scan or deep copy. |
| Design | [docs/maintenance_cost.md](../../../../maintenance_cost.md), [include/crown/runtime/maintenance_cost.hpp](../../../../../include/crown/runtime/maintenance_cost.hpp) |

## B0012

[Lines 48–48](../../../../../src/runtime/maintenance_cost.cpp#L48); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
const std::optional<FitSummary>& Calibration::fit_summary() const noexcept{return data_->summary;}
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Read the optional fit options/rank/error summary from a Calibration. |
| inputs / outputs | A readable factory-produced Calibration returns its optional fit options/rank/error summary as const optional reference. |
| invariants | Absent for isolated calibration; numerical rank/errors describe the retained calibration data. |
| ownership | Borrows immutable Calibration payload; retain a readable owning handle for the whole reference/view lifetime. Do not call through a moved-from handle. |
| failure | No validation, allocation, clock, catch or owner mutation on this accessor path. |
| cost | Constant pointer/member access; no scan or deep copy. |
| Design | [docs/maintenance_cost.md](../../../../maintenance_cost.md), [include/crown/runtime/maintenance_cost.hpp](../../../../../include/crown/runtime/maintenance_cost.hpp) |

## B0013

[Lines 49–49](../../../../../src/runtime/maintenance_cost.cpp#L49); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::span<const FitObservation> Calibration::fit_observations() const noexcept{return data_->observations;}
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Read the raw joint-fit observations from a Calibration. |
| inputs / outputs | A readable factory-produced Calibration returns its raw joint-fit observations as const span. |
| invariants | Raw vectors/timings are retained only for fitted calibration; no runtime sampling occurs here. |
| ownership | Borrows immutable Calibration payload; retain a readable owning handle for the whole reference/view lifetime. Do not call through a moved-from handle. |
| failure | No validation, allocation, clock, catch or owner mutation on this accessor path. |
| cost | Constant pointer/member access; no scan or deep copy. |
| Design | [docs/maintenance_cost.md](../../../../maintenance_cost.md), [include/crown/runtime/maintenance_cost.hpp](../../../../../include/crown/runtime/maintenance_cost.hpp) |

## B0014

[Lines 50–50](../../../../../src/runtime/maintenance_cost.cpp#L50); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
const planner::MinimumHeightCandidate& Profile::candidate() const noexcept{return data_->candidate;}
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Read the checked candidate from a Profile. |
| inputs / outputs | A readable factory-produced Profile returns its checked candidate as const candidate reference. |
| invariants | Candidate membership/binding was established by capture_impl, not rechecked by the getter. |
| ownership | Borrows immutable Profile payload; retain a readable owning handle for the whole reference/view lifetime. Do not call through a moved-from handle. |
| failure | No validation, allocation, clock, catch or owner mutation on this accessor path. |
| cost | Constant pointer/member access; no scan or deep copy. |
| Design | [docs/maintenance_cost.md](../../../../maintenance_cost.md), [include/crown/runtime/maintenance_cost.hpp](../../../../../include/crown/runtime/maintenance_cost.hpp) |

## B0015

[Lines 51–51](../../../../../src/runtime/maintenance_cost.cpp#L51); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
const runtime::ranking::RuntimeEvidence& Profile::evidence() const noexcept{return data_->evidence;}
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Read the actual immutable runtime evidence from a Profile. |
| inputs / outputs | A readable factory-produced Profile returns its actual immutable runtime evidence as const evidence reference. |
| invariants | Evidence is as-of capture; call revalidate for current-owner freshness. |
| ownership | Borrows immutable Profile payload; retain a readable owning handle for the whole reference/view lifetime. Do not call through a moved-from handle. |
| failure | No validation, allocation, clock, catch or owner mutation on this accessor path. |
| cost | Constant pointer/member access; no scan or deep copy. |
| Design | [docs/maintenance_cost.md](../../../../maintenance_cost.md), [include/crown/runtime/maintenance_cost.hpp](../../../../../include/crown/runtime/maintenance_cost.hpp) |

## B0016

[Lines 52–52](../../../../../src/runtime/maintenance_cost.cpp#L52); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
const resource::MemoryStatistics& Profile::memory_at_capture() const noexcept{return data_->memory;}
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Read the owner account counters observed before profile capture from a Profile. |
| inputs / outputs | A readable factory-produced Profile returns its owner account counters observed before profile capture as const MemoryStatistics reference. |
| invariants | Counters are observations, not future memory predictions. |
| ownership | Borrows immutable Profile payload; retain a readable owning handle for the whole reference/view lifetime. Do not call through a moved-from handle. |
| failure | No validation, allocation, clock, catch or owner mutation on this accessor path. |
| cost | Constant pointer/member access; no scan or deep copy. |
| Design | [docs/maintenance_cost.md](../../../../maintenance_cost.md), [include/crown/runtime/maintenance_cost.hpp](../../../../../include/crown/runtime/maintenance_cost.hpp) |

## B0017

[Lines 53–54](../../../../../src/runtime/maintenance_cost.cpp#L53); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
CandidateEstimate::CandidateEstimate(const resource::MemoryAccount& a,planner::MinimumHeightCandidate c)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Create one candidate estimate with receiver-funded term storage. |
| inputs / outputs | Receiver MemoryAccount and owning checked candidate initialize CandidateEstimate and its empty terms vector. |
| invariants | Default unknown optionals/issues are populated by estimate/evaluate; constructing this carrier does not evaluate a candidate. |
| ownership | Moves the candidate handle; terms allocator retains the receiver account. Other optional retained profiles begin empty. |
| failure | No term payload is allocated by the empty vector; later reserve/growth can fail before Result publication. |
| cost | Constant initialization and fixed carrier size. |
| Design | [docs/maintenance_cost.md](../../../../maintenance_cost.md), [include/crown/runtime/maintenance_cost.hpp](../../../../../include/crown/runtime/maintenance_cost.hpp) |

## B0018

[Lines 55–55](../../../../../src/runtime/maintenance_cost.cpp#L55); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
const pr::ScoreVector<CandidateEstimate>& Result::candidates() const noexcept{return data_->candidates;}
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Read the candidate estimates from a Result. |
| inputs / outputs | A readable factory-produced Result returns its candidate estimates as const vector reference. |
| invariants | Every retained snapshot candidate has an entry, including profile_missing entries. |
| ownership | Borrows immutable Result payload; retain a readable owning handle for the whole reference/view lifetime. Do not call through a moved-from handle. |
| failure | No validation, allocation, clock, catch or owner mutation on this accessor path. |
| cost | Constant pointer/member access; no scan or deep copy. |
| Design | [docs/maintenance_cost.md](../../../../maintenance_cost.md), [include/crown/runtime/maintenance_cost.hpp](../../../../../include/crown/runtime/maintenance_cost.hpp) |

## B0019

[Lines 56–56](../../../../../src/runtime/maintenance_cost.cpp#L56); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
const Calibration& Result::calibration() const noexcept{return data_->calibration;}
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Read the retained Calibration from a Result. |
| inputs / outputs | A readable factory-produced Result returns its retained Calibration as const Calibration reference. |
| invariants | No calibration is recalculated or copied deeply here. |
| ownership | Borrows immutable Result payload; retain a readable owning handle for the whole reference/view lifetime. Do not call through a moved-from handle. |
| failure | No validation, allocation, clock, catch or owner mutation on this accessor path. |
| cost | Constant pointer/member access; no scan or deep copy. |
| Design | [docs/maintenance_cost.md](../../../../maintenance_cost.md), [include/crown/runtime/maintenance_cost.hpp](../../../../../include/crown/runtime/maintenance_cost.hpp) |

## B0020

[Lines 57–57](../../../../../src/runtime/maintenance_cost.cpp#L57); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
const pr::Usage& Result::usage() const noexcept{return data_->usage;}
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Read the completed estimate processing usage from a Result. |
| inputs / outputs | A readable factory-produced Result returns its completed estimate processing usage as const Usage reference. |
| invariants | Logical work/cell/payload debits describe the completed attempt, not CPU time or allocator totals. |
| ownership | Borrows immutable Result payload; retain a readable owning handle for the whole reference/view lifetime. Do not call through a moved-from handle. |
| failure | No validation, allocation, clock, catch or owner mutation on this accessor path. |
| cost | Constant pointer/member access; no scan or deep copy. |
| Design | [docs/maintenance_cost.md](../../../../maintenance_cost.md), [include/crown/runtime/maintenance_cost.hpp](../../../../../include/crown/runtime/maintenance_cost.hpp) |

## B0021

[Lines 58–58](../../../../../src/runtime/maintenance_cost.cpp#L58); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::span<const InputDemand> Result::input_demand() const noexcept{return data_->input;}
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Read the copied input demand from a Result. |
| inputs / outputs | A readable factory-produced Result returns its copied input demand as const span. |
| invariants | The Result owns these demand values independently of the original Request span. |
| ownership | Borrows immutable Result payload; retain a readable owning handle for the whole reference/view lifetime. Do not call through a moved-from handle. |
| failure | No validation, allocation, clock, catch or owner mutation on this accessor path. |
| cost | Constant pointer/member access; no scan or deep copy. |
| Design | [docs/maintenance_cost.md](../../../../maintenance_cost.md), [include/crown/runtime/maintenance_cost.hpp](../../../../../include/crown/runtime/maintenance_cost.hpp) |

## B0022

[Lines 59–59](../../../../../src/runtime/maintenance_cost.cpp#L59); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
const OutputDemand& Result::output_demand() const noexcept{return data_->output;}
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Read the copied output demand from a Result. |
| inputs / outputs | A readable factory-produced Result returns its copied output demand as const OutputDemand reference. |
| invariants | Counts are caller assumptions for a horizon, not observed future events. |
| ownership | Borrows immutable Result payload; retain a readable owning handle for the whole reference/view lifetime. Do not call through a moved-from handle. |
| failure | No validation, allocation, clock, catch or owner mutation on this accessor path. |
| cost | Constant pointer/member access; no scan or deep copy. |
| Design | [docs/maintenance_cost.md](../../../../maintenance_cost.md), [include/crown/runtime/maintenance_cost.hpp](../../../../../include/crown/runtime/maintenance_cost.hpp) |

## B0023

[Lines 60–66](../../../../../src/runtime/maintenance_cost.cpp#L60); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::string_view component_name(Component c) noexcept {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Name a cost component for diagnostic serialization. |
| inputs / outputs | Component enum returns its static spelling, or "invalid" when its numeric value lies outside component_count. |
| invariants | Array ordering follows Component; this fallback does not validate a whole calibration or term. |
| ownership | Returned string_view points into static literal storage and does not depend on a model handle. |
| failure | noexcept, with a checked array index and no dynamic diagnostic construction. |
| cost | Constant cast/range test/index lookup. |
| Design | [docs/maintenance_cost.md](../../../../maintenance_cost.md), [include/crown/runtime/maintenance_cost.hpp](../../../../../include/crown/runtime/maintenance_cost.hpp) |

## B0024

[Lines 67–67](../../../../../src/runtime/maintenance_cost.cpp#L67); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L67-L67:sha256:cf04d99c0f5d3521f67f7c587d20dd3592a5024b903529e1e468844f7fae8135
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Source usage for this declaration span in src/runtime/maintenance_cost.cpp: opens anonymous namespace with translation-unit-local linkage. |
| inputs / outputs | Compile inputs are the listed headers and namespace/type names. This span adds no result value unless a helper/type definition listed above is instantiated or called. |
| invariants | The exact import, alias, namespace and member declarations determine the local compile/link surface; stronger behavior belongs to their constructors and operations. |
| ownership | Imports, namespace aliases, forward declarations and compile guards create no object owner. Runtime ownership starts with declared object instances and their allocator/member types. |
| failure | No explicit throw/catch appears in this exact span. Includes, constructors, inline members, static initialization and callees can still fail; follow their enclosing API contracts. |
| cost | This span changes compile/link structure and type layout. Runtime initialization, allocation, exceptions and operation work follow the declared owner/callable code; no absence is inferred from declaration syntax. |
| Design | [docs/maintenance_cost.md](../../../../maintenance_cost.md), [docs/workloads.md](../../../../workloads.md), [docs/code_specs/subsystem_contracts.md](../../../subsystem_contracts.md) |

## B0025

[Lines 68–68](../../../../../src/runtime/maintenance_cost.cpp#L68); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void require(bool value,pr::Stop stop=pr::Stop::invalid_limits){if(!value)throw rd::Failure{stop};}
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Raise an internal stop when a cost-model precondition fails. |
| inputs / outputs | Boolean and Stop (default invalid_limits) return normally or throw rd::Failure{stop}. |
| invariants | This small private typed throw is consumed by the outer noexcept attempt boundary; it does not roll back query state. |
| ownership | Carries only the Stop enum, without copied messages or account ownership. |
| failure | False condition propagates rd::Failure to the current public attempt catcher. |
| cost | One success branch; failure-only exception machinery. |
| Design | [docs/maintenance_cost.md](../../../../maintenance_cost.md), [include/crown/runtime/maintenance_cost.hpp](../../../../../include/crown/runtime/maintenance_cost.hpp), [src/planner/ranking_detail.hpp](../../../../../src/planner/ranking_detail.hpp) |

## B0026

[Lines 69–69](../../../../../src/runtime/maintenance_cost.cpp#L69); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
U64 add(U64 a,U64 b) {require(b<=UINT64_MAX-a,pr::Stop::bit_limit);return a+b;}
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Add unsigned event/count arithmetic without wrap. |
| inputs / outputs | Two U64 values return their sum when b &lt;= UINT64_MAX-a. |
| invariants | Overflow stops with bit_limit; counts are never saturated or rounded for exact model arithmetic. |
| ownership | Inline operands/result; no retained state. |
| failure | bit_limit is raised before returning the wrapped sum. |
| cost | Constant comparison/subtraction/addition. |
| Design | [docs/maintenance_cost.md](../../../../maintenance_cost.md), [include/crown/runtime/maintenance_cost.hpp](../../../../../include/crown/runtime/maintenance_cost.hpp) |

## B0027

[Lines 70–70](../../../../../src/runtime/maintenance_cost.cpp#L70); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
U64 multiply(U64 a,U64 b) {require(!a || b<=UINT64_MAX/a,pr::Stop::bit_limit);return a*b;}
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Multiply unsigned model units without wrap. |
| inputs / outputs | Two U64 operands return a*b; zero a avoids division and yields zero. |
| invariants | Nonzero products must fit U64; estimate limits can be stricter after ratio normalization. |
| ownership | Inline operands/result; no retained state. |
| failure | bit_limit is raised before overflowing multiplication. |
| cost | Constant zero branch, bound division and multiplication. |
| Design | [docs/maintenance_cost.md](../../../../maintenance_cost.md), [include/crown/runtime/maintenance_cost.hpp](../../../../../include/crown/runtime/maintenance_cost.hpp) |

## B0028

[Lines 71–71](../../../../../src/runtime/maintenance_cost.cpp#L71); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Ratio ratio(U64 n,U64 d=1) {require(d!=0);const auto g=std::gcd(n,d);return {n/g,d/g};}
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Normalize a nonnegative model ratio. |
| inputs / outputs | Numerator n and nonzero denominator d return {n/gcd(n,d),d/gcd(n,d)}. |
| invariants | Every successful ratio has positive denominator and reduced terms; zero becomes 0/1. |
| ownership | Returns two inline U64 fields. |
| failure | Zero denominator raises invalid_limits before gcd/division. |
| cost | One U64 gcd plus two divisions; no heap or floating arithmetic. |
| Design | [docs/maintenance_cost.md](../../../../maintenance_cost.md), [include/crown/runtime/maintenance_cost.hpp](../../../../../include/crown/runtime/maintenance_cost.hpp) |

## B0029

[Lines 72–75](../../../../../src/runtime/maintenance_cost.cpp#L72); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Ratio times(Ratio a,Ratio b) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Multiply reduced model ratios with cross-cancellation. |
| inputs / outputs | Valid ratios a,b return reduced exact product after cancelling numerator/other-denominator gcds. |
| invariants | Inputs must have nonzero denominators. Cancellation reduces avoidable intermediate overflow; checked U64 products can still stop. |
| ownership | Local scalar arithmetic only; no mutation of published coefficients. |
| failure | bit_limit on an unrepresentable intermediate; no approximation/fallback. |
| cost | Three bounded-width gcd reductions plus checked multiply/divide operations. |
| Design | [docs/maintenance_cost.md](../../../../maintenance_cost.md), [include/crown/runtime/maintenance_cost.hpp](../../../../../include/crown/runtime/maintenance_cost.hpp) |

## B0030

[Lines 76–81](../../../../../src/runtime/maintenance_cost.cpp#L76); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Ratio plus(Ratio a,Ratio b) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Add reduced nonnegative ratios while cancelling common factors before denominator multiplication. |
| inputs / outputs | Valid reduced a,b produce their reduced sum using denominator gcd and post-numerator cancellation. |
| invariants | A checked numerator intermediate can fail even when an alternative wider algorithm could represent the final rational; the chosen exact U64 policy is explicit. |
| ownership | Only local scalar state. |
| failure | bit_limit before checked add/multiply overflow; caller private result is discarded by its boundary. |
| cost | Two U64 gcd calls plus checked arithmetic; no arbitrary-precision or heap storage. |
| Design | [docs/maintenance_cost.md](../../../../maintenance_cost.md), [include/crown/runtime/maintenance_cost.hpp](../../../../../include/crown/runtime/maintenance_cost.hpp) |

## B0031

[Lines 82–85](../../../../../src/runtime/maintenance_cost.cpp#L82); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void check_bits(Ratio value,const rd::Budget& budget) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Apply the caller arithmetic-width ceiling to one ratio. |
| inputs / outputs | Valid ratio plus ranking Budget compare numerator/denominator bit widths against limits.score_bits. |
| invariants | Storage is still U64 even when ranking permits a larger score_bits ceiling; this helper cannot enlarge it. |
| ownership | Reads the budget without consuming a work debit or retaining it. |
| failure | bit_limit when either field exceeds the configured bit ceiling. |
| cost | Two fixed-width bit_width computations and comparisons. |
| Design | [docs/maintenance_cost.md](../../../../maintenance_cost.md), [include/crown/runtime/maintenance_cost.hpp](../../../../../include/crown/runtime/maintenance_cost.hpp) |

## B0032

[Lines 86–88](../../../../../src/runtime/maintenance_cost.cpp#L86); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
bool same_candidate(const planner::MinimumHeightCandidate& a,const planner::MinimumHeightCandidate& b,rd::Budget& budget) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Compare factory-checked candidate structural keys under the same processing budget. |
| inputs / outputs | Two MinimumHeightCandidate handles return true only if both are valid and their keys are byte equal. |
| invariants | Structural equality alone does not grant source/catalog/output binding; estimate checks those separately. |
| ownership | Borrows immutable candidate keys for this call. |
| failure | Budgeted byte comparison can raise work/time limits; invalid handles short-circuit false. |
| cost | Constant handle checks plus linear compared-key byte work. |
| Design | [docs/maintenance_cost.md](../../../../maintenance_cost.md), [include/crown/runtime/maintenance_cost.hpp](../../../../../include/crown/runtime/maintenance_cost.hpp), [src/planner/ranking_detail.hpp](../../../../../src/planner/ranking_detail.hpp) |

## B0033

[Lines 89–105](../../../../../src/runtime/maintenance_cost.cpp#L89); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
template<class Append> void components(const workload::Descriptor& descriptor,const workload::Cell& cell,Append append) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Translate one workload descriptor/cell into named model event counts. |
| inputs / outputs | Physical cells emit input/change, occurrences emit visits, support roles emit count changes/crossings, and degree cells emit event count plus touched-size sum through Append. |
| invariants | Each physical-input stratum remains separate. Degree count is an event multiset, not distinct keys; logical-only descriptors and unknown support roles reject. |
| ownership | Borrows descriptor/cell and invokes caller callback synchronously; stores no rows, callbacks or collector state. |
| failure | binding_mismatch for logical kind/unsupported support role; crossing addition may bit-limit; callback failures propagate. |
| cost | Constant switch/field reads and one or two callback invocations per descriptor; no collection or scan here. |
| Design | [docs/maintenance_cost.md](../../../../maintenance_cost.md), [include/crown/runtime/maintenance_cost.hpp](../../../../../include/crown/runtime/maintenance_cost.hpp), [src/runtime/statistics_collection.cpp](../../../../../src/runtime/statistics_collection.cpp) |

## B0034

[Lines 106–151](../../../../../src/runtime/maintenance_cost.cpp#L106); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
template<class Owner> CaptureAttempt capture_impl(const planner::CandidateSnapshot& snapshot,std::size_t index,const Owner& owner,pr::Limits limits) noexcept {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Capture actual immutable owner observations and verify this candidate reproduces the owner physical binding. |
| inputs / outputs | Valid snapshot/index, quiescent PhysicalRuntime/DeltaRuntime/QuerySession and limits produce Profile or explicit CaptureAttempt stop/usage. |
| invariants | Account counters are read before profiling. Captured workload must be committed; re-lowering the selected checked candidate against actual admitted source must match physical_sha256. Lowering/replay ceilings share remaining allowance. |
| ownership | Owner rows/runtime are not exported. Profile shares candidate/evidence; its holder allocates on the actual plan account after verification. |
| failure | Noexcept maps rd::Failure, ReplanFailure, bad_alloc (including MemoryFailure) and unexpected errors to stops. RAII releases private captures. Pessimistically reserved replay/lowering usage remains consumed on a failing replan; no profile is published. |
| cost | Explicit cold diagnostic: account-statistics query, native capture, candidate replan/binding comparison and one retained holder allocation. Not a constant-time runtime hook; nested capture/replay have their own bounded costs. |
| Design | [docs/maintenance_cost.md](../../../../maintenance_cost.md), [include/crown/runtime/maintenance_cost.hpp](../../../../../include/crown/runtime/maintenance_cost.hpp), [src/runtime/ranking_evidence.cpp](../../../../../src/runtime/ranking_evidence.cpp), [src/ir/program_replan.inc](../../../../../src/ir/program_replan.inc), [src/planner/ranking_detail.hpp](../../../../../src/planner/ranking_detail.hpp), [docs/query_memory.md](../../../../query_memory.md) |

```text
const auto memory=owner.accounted_memory_statistics();
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Observe owner memory before adding profiling evidence. |
| inputs / outputs | Actual owner account snapshot becomes ProfileData.memory; QuerySession must expose an accounted native owner. |
| invariants | Read happens before runtime::ranking::capture and ProfileData allocation, so the snapshot excludes those newly retained profiling objects. |
| ownership | Copies fixed counters; does not retain mutable owner state. |
| failure | Unavailable QuerySession account stops with evidence_unavailable; query data is unchanged. |
| cost | Cost of the actual account-statistics query; this is diagnostic work rather than a measured hot update. |
| Design | [docs/maintenance_cost.md](../../../../maintenance_cost.md), [include/crown/runtime/maintenance_cost.hpp](../../../../../include/crown/runtime/maintenance_cost.hpp), [docs/query_memory.md](../../../../query_memory.md) |

```text
b.usage.lowering_work=limits.lowering_work;b.usage.identity_work=limits.identity_work;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Reserve remaining replan domains before invoking the checked candidate compiler. |
| inputs / outputs | Remaining lowering/identity/binding/normalization limits are passed to replan; successful replay replaces pessimistic usage with its reported actual debits. |
| invariants | A failed replan cannot refund already reserved work by unwinding. These logical limits are separate from real account allocation. |
| ownership | Private Budget counters only; replan returns an owning temporary compiled program. |
| failure | Replan/binding failure is translated by capture_impl; no Profile is published. |
| cost | Cold compiler/replay costs and hash comparison, with no extra runtime state mirror. |
| Design | [docs/maintenance_cost.md](../../../../maintenance_cost.md), [include/crown/runtime/maintenance_cost.hpp](../../../../../include/crown/runtime/maintenance_cost.hpp), [src/planner/ranking_detail.hpp](../../../../../src/planner/ranking_detail.hpp) |

## B0035

[Lines 152–152](../../../../../src/runtime/maintenance_cost.cpp#L152); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
enum class Group { maintenance,snapshot,delta,encoding,checkpoint,annotation,count };
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Partition estimated time into independent reporting categories. |
| inputs / outputs | Private Group enum identifies maintenance, snapshot, delta, encoding, checkpoint and annotation subtotal slots plus count. |
| invariants | Byte budgets remain separate from these time categories. |
| ownership | Compile-time enum only. |
| failure | No runtime failure or validation here. |
| cost | No dynamic storage or work. |
| Design | [docs/maintenance_cost.md](../../../../maintenance_cost.md), [include/crown/runtime/maintenance_cost.hpp](../../../../../include/crown/runtime/maintenance_cost.hpp) |

## B0036

[Lines 153–160](../../../../../src/runtime/maintenance_cost.cpp#L153); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Group group(Component c) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Assign a valid model component to its subtotal category. |
| inputs / outputs | Factory-generated Component maps to annotation, snapshot, delta, encoding, checkpoint or maintenance Group. |
| invariants | Private caller supplies a valid Component; enum ordering defines contiguous ranges. This helper is not a general invalid-enum validator. |
| ownership | Returns a scalar Group without retaining inputs. |
| failure | No throwing operation for the valid private domain. |
| cost | Constant bounded comparisons. |
| Design | [docs/maintenance_cost.md](../../../../maintenance_cost.md), [include/crown/runtime/maintenance_cost.hpp](../../../../../include/crown/runtime/maintenance_cost.hpp) |

## B0037

[Lines 161–161](../../../../../src/runtime/maintenance_cost.cpp#L161); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct Sums {std::array<Ratio,static_cast<std::size_t>(Group::count)> values{};std::array<bool,static_cast<std::size_t>(Group::count)> unknown{};};
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Accumulate exact subtotal ratios while remembering any unknown term. |
| inputs / outputs | Fixed arrays start with zero ratios and false unknown flags, indexed by Group. |
| invariants | An absent term cost marks its subtotal unavailable; it cannot silently contribute zero. |
| ownership | Stack-local arithmetic/flag arrays owned by evaluate. |
| failure | Initialization cannot allocate; later arithmetic failures unwind the private attempt. |
| cost | Fixed six-category storage/initialization. |
| Design | [docs/maintenance_cost.md](../../../../maintenance_cost.md), [include/crown/runtime/maintenance_cost.hpp](../../../../../include/crown/runtime/maintenance_cost.hpp) |

## B0038

[Lines 162–177](../../../../../src/runtime/maintenance_cost.cpp#L162); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void term(CandidateEstimate& out,Sums& sums,const Calibration& calibration,Component component,
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Append one priced or explicitly unknown term and update its subtotal. |
| inputs / outputs | CandidateEstimate, local Sums, Calibration, valid Component, optional units/confidence/issues and Budget produce one Term in out.terms. |
| invariants | Declared zero units cost exact zero without a coefficient. Positive known units require a coefficient; missing rate sets calibration_missing. Arithmetic bit checks precede publication of the complete Result. |
| ownership | Copies inline Term fields into receiver-funded vector; all input metadata is borrowed only during this call. |
| failure | Work/time/arithmetic/container failures propagate. out/Sums may be partially updated, but both belong to a private unpublished estimate, so no per-term undo/catch is needed. |
| cost | One work debit, optional exact ratio multiply/add, fixed subtotal work and one append; evaluate pre-reserves capacity so ordinary append does not repeatedly grow. |
| Design | [docs/maintenance_cost.md](../../../../maintenance_cost.md), [include/crown/runtime/maintenance_cost.hpp](../../../../../include/crown/runtime/maintenance_cost.hpp) |

## B0039

[Lines 178–181](../../../../../src/runtime/maintenance_cost.cpp#L178); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
U64 demanded(std::span<const InputDemand> demand,const workload::Descriptor& descriptor,rd::Budget& budget) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Find the caller future demand for a descriptor physical table/operation. |
| inputs / outputs | Demand span and descriptor return the matching InputDemand.inputs. |
| invariants | estimate validates the complete unique table/op demand domain before evaluate; no measured arrival rate is substituted. |
| ownership | Borrows caller Request span for the call; completed Result separately owns a copy. |
| failure | binding_mismatch if no match; earlier work debits remain spent on a later failure. |
| cost | Linear demand_count search with one work debit per inspected item. |
| Design | [docs/maintenance_cost.md](../../../../maintenance_cost.md), [include/crown/runtime/maintenance_cost.hpp](../../../../../include/crown/runtime/maintenance_cost.hpp) |

## B0040

[Lines 182–187](../../../../../src/runtime/maintenance_cost.cpp#L182); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::optional<std::size_t> root_descriptor(const workload::Snapshot& snapshot,const workload::Descriptor& d,rd::Budget& budget) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Locate the physical census root for a detailed stratum. |
| inputs / outputs | Workload Snapshot and descriptor return index of physical root sharing table and operation, or nullopt. |
| invariants | Detailed means use this initiating stratum denominator, never a uniform static-key average. |
| ownership | Returns an index into the borrowed snapshot descriptor/cell spans. |
| failure | Work/time exhaustion propagates; missing root is diagnosed by evaluate. |
| cost | Linear descriptor_count search and metered visit per examined descriptor. |
| Design | [docs/maintenance_cost.md](../../../../maintenance_cost.md), [include/crown/runtime/maintenance_cost.hpp](../../../../../include/crown/runtime/maintenance_cost.hpp) |

## B0041

[Lines 188–256](../../../../../src/runtime/maintenance_cost.cpp#L188); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void evaluate(CandidateEstimate& out,const Profile& profile,const Calibration& calibration,const Request& request,rd::Budget& budget) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Produce one candidate decomposition from immutable observations and declared horizon demand. |
| inputs / outputs | Profile, Calibration and Request fill a private CandidateEstimate with retained observations, stamps, terms, category subtotals and optional total. |
| invariants | Exact physical census and complete detailed samples use separate denominators; sampled forecasts retain sampled status. Saturated/missing/truncated/unobserved evidence stays unknown for positive demand. Zero declared demand is exact zero. Backend/mode/current-memory mismatches prevent a complete total. |
| ownership | Retains the Profile handle, copies stamps/counters, and reserves receiver-account term storage once. Borrows snapshot/Request while executing. |
| failure | Binding, arithmetic, allocation and processing failures propagate to estimate; partial fields remain private. Memory fit is as-of current requested bytes, not future-state admission. |
| cost | For D descriptors and I demand entries, repeated demanded/root_descriptor searches cost O(D*(I+D)) plus O(D) term arithmetic; ten explicit output terms and fixed subtotal reduction follow. No query-row scan or new runtime instrumentation. |
| Design | [docs/maintenance_cost.md](../../../../maintenance_cost.md), [include/crown/runtime/maintenance_cost.hpp](../../../../../include/crown/runtime/maintenance_cost.hpp), [src/runtime/workload_statistics.cpp](../../../../../src/runtime/workload_statistics.cpp), [tests/unit/maintenance_cost_statistics_test.cpp](../../../../../tests/unit/maintenance_cost_statistics_test.cpp) |

```text
std::size_t term_count=10;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Fund complete term capacity before emitting candidate terms. |
| inputs / outputs | Descriptor count/role plus empty-descriptor input fallback derive exact maximum entries including ten explicit output terms. |
| invariants | Each descriptor emits at most one/two terms under the admitted role map; checked arithmetic prevents capacity wrap. |
| ownership | Receiver-account vector reserve occurs once on a private CandidateEstimate. |
| failure | Logical cell/byte rejection or allocation failure aborts the private estimate before Result publication. |
| cost | O(D) count pass plus one reserve; avoids repeated prefix relocation during term appends. |
| Design | [docs/maintenance_cost.md](../../../../maintenance_cost.md), [include/crown/runtime/maintenance_cost.hpp](../../../../../include/crown/runtime/maintenance_cost.hpp) |

```text
auto append=[&](Component component,U64 events,bool direct=false) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Turn observed stratum events into a conditional future-unit assumption. |
| inputs / outputs | Declared inputs and complete/census denominator produce exact reduced event/denominator * inputs, direct base-input count, zero demand, or unknown units. |
| invariants | Retains basis/status/denominator/event counts; sampled observed ratios are model assumptions, not population facts or confidence bounds. |
| ownership | Synchronous reference-capturing lambda lives only inside the descriptor loop and stores no callback. |
| failure | Ratio overflow, bit/work/time or term allocation propagates to the outer unpublished estimate. |
| cost | Constant per-component arithmetic plus term cost, after linear root/demand searches. |
| Design | [docs/maintenance_cost.md](../../../../maintenance_cost.md), [include/crown/runtime/maintenance_cost.hpp](../../../../../include/crown/runtime/maintenance_cost.hpp) |

## B0042

[Lines 257–257](../../../../../src/runtime/maintenance_cost.cpp#L257); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L257-L257:sha256:412ca345ccf75bf9c0806bce695be8de808b79984251a7a54d202cf6101dd451
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Close the \`anonymous namespace in src/runtime/maintenance_cost.cpp\` scope at this exact source boundary. |
| inputs / outputs | This token introduces no callable inputs or outputs. Declarations inside \`anonymous namespace in src/runtime/maintenance_cost.cpp\` define the available names, members and operations. |
| invariants | The closing brace matches the opening \`anonymous namespace in src/runtime/maintenance_cost.cpp\` at its lexical source position in src/runtime/maintenance_cost.cpp; it preserves C++ namespace/type nesting. |
| ownership | The closing delimiter creates no owner. Types closed by \`anonymous namespace in src/runtime/maintenance_cost.cpp\` retain the lifetimes and allocator rules of their own fields and operations. |
| failure | No failure path executes at this closing delimiter. Failure and cleanup behavior belong to enclosed functions and owning types. |
| cost | The delimiter itself performs no runtime work; the enclosed initializers, methods and destructors carry their own costs. |
| Design | [docs/maintenance_cost.md](../../../../maintenance_cost.md), [docs/workloads.md](../../../../workloads.md), [docs/code_specs/subsystem_contracts.md](../../../subsystem_contracts.md) |

## B0043

[Lines 258–273](../../../../../src/runtime/maintenance_cost.cpp#L258); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
FeatureAttempt features(const workload::Snapshot& snapshot,pr::Limits limits) noexcept {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Extract an exact committed feature census for external timing calibration. |
| inputs / outputs | Workload Snapshot and limits produce fixed FeatureCensus units/stamp/modes or FeatureAttempt stop/usage. |
| invariants | Reject pending, sampled, disabled, saturated/degraded/truncated or generation-saturated intervals; every descriptor must have physical_table scope. Features are actual full-detail counts, without timing. |
| ownership | Borrows snapshot while summing into fixed local arrays; publishes only copied numeric data, no rows or runtime owner. |
| failure | Noexcept maps typed Failure to its stop and unexpected failures to internal_error. No partial census is published; spent usage survives. |
| cost | Linear availability scan plus one pass over D descriptors/one or two components each; fixed component arrays, no heap request in this implementation. Optional processing active_time may read clocks. |
| Design | [docs/maintenance_cost.md](../../../../maintenance_cost.md), [include/crown/runtime/maintenance_cost.hpp](../../../../../include/crown/runtime/maintenance_cost.hpp), [src/runtime/workload_statistics.cpp](../../../../../src/runtime/workload_statistics.cpp), [tests/unit/maintenance_cost_test.cpp](../../../../../tests/unit/maintenance_cost_test.cpp) |

## B0044

[Lines 274–295](../../../../../src/runtime/maintenance_cost.cpp#L274); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
CalibrationAttempt calibrate(const resource::MemoryAccount& account,std::string_view context,std::string_view backend,
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Build measured per-component rates from isolated caller observations. |
| inputs / outputs | Readable receiver account, nonempty context/backend labels, samples and limits produce Calibration or explicit stop. |
| invariants | Each supplied sample must have a valid component, positive units and elapsed_ns; rates are reduced sum(elapsed_ns)/sum(units). An empty sample span leaves every rate unavailable. Labels do not verify disjoint timing scopes or measurement quality. |
| ownership | Copies labels into receiver-funded private CalibrationData; retains no sample span. Shared publication follows all checks. |
| failure | Typed limits/arithmetic, bad_alloc/MemoryFailure and unexpected errors map at this noexcept boundary. RAII releases partial strings/data and earlier Calibration objects remain untouched. |
| cost | O(label bytes + sample_count) visits with fixed component array and gcd arithmetic; one shared holder plus string payload as required. Logical payload debits are separate from allocator framing. |
| Design | [docs/maintenance_cost.md](../../../../maintenance_cost.md), [include/crown/runtime/maintenance_cost.hpp](../../../../../include/crown/runtime/maintenance_cost.hpp), [tests/unit/maintenance_cost_test.cpp](../../../../../tests/unit/maintenance_cost_test.cpp), [docs/query_memory.md](../../../../query_memory.md) |

## B0045

[Lines 296–383](../../../../../src/runtime/maintenance_cost.cpp#L296); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
CalibrationAttempt fit(const resource::MemoryAccount& account,std::string_view context,std::string_view backend,
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Infer nonnegative linear rates from whole-phase timings while preserving the assumption and raw evidence. |
| inputs / outputs | Receiver account, labels, nonempty FitObservations, valid FitOptions and processing limits produce a fitted Calibration or stop. |
| invariants | Normalizes design columns, reports tolerance-dependent unregularized numerical rank, runs zero-initialized fixed-order nonnegative coordinate descent, quantizes rates to reduced U64 ratios and reports errors after quantization. Unobserved features stay unavailable; inferred zero is not proof of a free operation. |
| ownership | Copies labels/raw observations into receiver-account Data; Gram, elimination, rhs/beta/norm and counters are fixed stack arrays. Published handle shares immutable data/options/summary. |
| failure | Invalid options/empty feature rows, arithmetic/nonfinite/width errors, iteration nonconvergence, processing limits and allocation stop before Calibration publication. Three outer handler clauses translate to explicit status; no local undo framework. |
| cost | With N observations and F=component_count, O(N*F^2 + F^3 + iterations*F^2 + N*F) floating work, O(F^2) stack plus O(N*F + labels) retained storage. Work meters selected loop visits; final numerical diagnostics are approximate, not exact rank/statistical confidence. |
| Design | [docs/maintenance_cost.md](../../../../maintenance_cost.md), [include/crown/runtime/maintenance_cost.hpp](../../../../../include/crown/runtime/maintenance_cost.hpp), [tests/unit/maintenance_cost_fit_test.cpp](../../../../../tests/unit/maintenance_cost_fit_test.cpp), [tests/unit/maintenance_cost_fit_exception_test.cpp](../../../../../tests/unit/maintenance_cost_fit_exception_test.cpp) |

```text
auto elimination=gram;std::size_t row=0;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Diagnose numerical feature rank before ridge regularization. |
| inputs / outputs | Normalized Gram matrix is copied and eliminated with maximum-absolute pivots above rank_tolerance; resulting row count records numerical_rank/underdetermined. |
| invariants | Tolerance-dependent double elimination is not an exact rank proof or unique attribution guarantee. |
| ownership | Fixed local matrix copy; retained summary stores only counts/options. |
| failure | Processing limits interrupt before Calibration publication; numerical rounding remains part of the approximate fit. |
| cost | O(F^3) elimination and O(F^2) stack, F=component_count. |
| Design | [docs/maintenance_cost.md](../../../../maintenance_cost.md), [include/crown/runtime/maintenance_cost.hpp](../../../../../include/crown/runtime/maintenance_cost.hpp) |

```text
for(std::size_t iteration=0;iteration<options.max_iterations;++iteration) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Fit nonnegative rates by deterministic coordinate descent. |
| inputs / outputs | Zero-initialized beta, normalized Gram/rhs and ridge update coordinates in fixed order until relative change tolerance or iteration bound. |
| invariants | Only observed columns participate. Convergence is an algorithm stop condition; it establishes no causal/statistical model validity. |
| ownership | Fixed stack arrays mutate privately; no account allocation per iteration. |
| failure | Nonfinite coordinate raises bit_limit; nonconvergence raises work_limit after the loop; work/time limits can stop earlier. |
| cost | O(iterations*F^2) selected floating operations; processing active_time may check the clock through b.work. |
| Design | [docs/maintenance_cost.md](../../../../maintenance_cost.md), [include/crown/runtime/maintenance_cost.hpp](../../../../../include/crown/runtime/maintenance_cost.hpp) |

```text
const auto rounded=std::floor(scaled+0.5L);
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Publish nonnegative inferred rates as checked reduced rational coefficients. |
| inputs / outputs | Scaled fitted rate rounds to nearest nonnegative integer at quantization_denominator, checks below 2^64 and normalizes via ratio. |
| invariants | The quantized value is exact storage for an approximate inferred rate; unobserved columns stay absent and per-component elapsed_ns is zero for joint fits. |
| ownership | Writes fixed optional coefficient slot of private Data; raw observations remain separately owned. |
| failure | Nonfinite/out-of-range/rate-bit failure discards the entire private Calibration. |
| cost | O(F) quantization/gcd work, no per-coefficient heap allocation. |
| Design | [docs/maintenance_cost.md](../../../../maintenance_cost.md), [include/crown/runtime/maintenance_cost.hpp](../../../../../include/crown/runtime/maintenance_cost.hpp) |

```text
long double squared_error=0;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Measure in-sample fit errors using published quantized rates. |
| inputs / outputs | Each retained raw observation is priced from quantized coefficients; maximum absolute and root mean square residuals populate FitSummary. |
| invariants | These are calibration-data residuals after quantization, not held-out accuracy or statistical confidence. |
| ownership | Uses local long-double accumulators; summary copies into the private calibration holder. |
| failure | Nonfinite reported errors raise bit_limit before publication; processing stops can interrupt the pass. |
| cost | O(N*F) arithmetic; no new report arrays or timing acquisition. |
| Design | [docs/maintenance_cost.md](../../../../maintenance_cost.md), [include/crown/runtime/maintenance_cost.hpp](../../../../../include/crown/runtime/maintenance_cost.hpp) |

## B0046

[Lines 384–384](../../../../../src/runtime/maintenance_cost.cpp#L384); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
CaptureAttempt capture(const planner::CandidateSnapshot& s,std::size_t i,const PhysicalRuntime& o,pr::Limits l) noexcept{return capture_impl(s,i,o,l);}
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Expose checked cost-profile capture for PhysicalRuntime. |
| inputs / outputs | Snapshot, candidate index, readable quiescent PhysicalRuntime and limits forward once to capture_impl and return its CaptureAttempt. |
| invariants | This overload does not broaden capture admission or implement a second evidence path. |
| ownership | Borrows owner during capture; a successful profile owns immutable handles independently of owner lifetime. |
| failure | noexcept delegates all failure-to-stop translation to capture_impl. |
| cost | Constant dispatch plus complete capture/replan/allocation costs specified at capture_impl. |
| Design | [docs/maintenance_cost.md](../../../../maintenance_cost.md), [include/crown/runtime/maintenance_cost.hpp](../../../../../include/crown/runtime/maintenance_cost.hpp), [src/runtime/ranking_evidence.cpp](../../../../../src/runtime/ranking_evidence.cpp) |

## B0047

[Lines 385–385](../../../../../src/runtime/maintenance_cost.cpp#L385); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
CaptureAttempt capture(const planner::CandidateSnapshot& s,std::size_t i,const DeltaRuntime& o,pr::Limits l) noexcept{return capture_impl(s,i,o,l);}
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Expose checked cost-profile capture for DeltaRuntime. |
| inputs / outputs | Snapshot, candidate index, readable quiescent DeltaRuntime and limits forward once to capture_impl and return its CaptureAttempt. |
| invariants | This overload does not broaden capture admission or implement a second evidence path. |
| ownership | Borrows owner during capture; a successful profile owns immutable handles independently of owner lifetime. |
| failure | noexcept delegates all failure-to-stop translation to capture_impl. |
| cost | Constant dispatch plus complete capture/replan/allocation costs specified at capture_impl. |
| Design | [docs/maintenance_cost.md](../../../../maintenance_cost.md), [include/crown/runtime/maintenance_cost.hpp](../../../../../include/crown/runtime/maintenance_cost.hpp), [src/runtime/ranking_evidence.cpp](../../../../../src/runtime/ranking_evidence.cpp) |

## B0048

[Lines 386–386](../../../../../src/runtime/maintenance_cost.cpp#L386); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
CaptureAttempt capture(const planner::CandidateSnapshot& s,std::size_t i,const QuerySession& o,pr::Limits l) noexcept{return capture_impl(s,i,o,l);}
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Expose checked cost-profile capture for QuerySession. |
| inputs / outputs | Snapshot, candidate index, readable quiescent QuerySession and limits forward once to capture_impl and return its CaptureAttempt. |
| invariants | This overload does not broaden capture admission or implement a second evidence path. |
| ownership | Borrows owner during capture; a successful profile owns immutable handles independently of owner lifetime. |
| failure | noexcept delegates all failure-to-stop translation to capture_impl. |
| cost | Constant dispatch plus complete capture/replan/allocation costs specified at capture_impl. |
| Design | [docs/maintenance_cost.md](../../../../maintenance_cost.md), [include/crown/runtime/maintenance_cost.hpp](../../../../../include/crown/runtime/maintenance_cost.hpp), [src/runtime/ranking_evidence.cpp](../../../../../src/runtime/ranking_evidence.cpp) |

## B0049

[Lines 387–387](../../../../../src/runtime/maintenance_cost.cpp#L387); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
runtime::ranking::Revalidation revalidate(const Profile& p,const PhysicalRuntime& o) noexcept{return runtime::ranking::revalidate(p.evidence(),o);}
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Check whether retained cost evidence is current for PhysicalRuntime. |
| inputs / outputs | Profile and readable PhysicalRuntime forward the Profile RuntimeEvidence to runtime::ranking::revalidate and return boundary/depth/memory reasons. |
| invariants | Revalidation reports freshness; it never edits the retained Profile or updates old observations. |
| ownership | Borrows Profile/owner and returns numeric reason masks. Delegated temporary captures release on return. |
| failure | noexcept delegates conversion of capture/read failures to freshness reasons; no retry or state repair is added. |
| cost | Constant forwarding plus delegated actual-owner capture/census/binding checks, which can allocate and scan descriptors; not a constant-time getter. |
| Design | [docs/maintenance_cost.md](../../../../maintenance_cost.md), [include/crown/runtime/maintenance_cost.hpp](../../../../../include/crown/runtime/maintenance_cost.hpp), [src/runtime/ranking_evidence.cpp](../../../../../src/runtime/ranking_evidence.cpp) |

## B0050

[Lines 388–388](../../../../../src/runtime/maintenance_cost.cpp#L388); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
runtime::ranking::Revalidation revalidate(const Profile& p,const DeltaRuntime& o) noexcept{return runtime::ranking::revalidate(p.evidence(),o);}
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Check whether retained cost evidence is current for DeltaRuntime. |
| inputs / outputs | Profile and readable DeltaRuntime forward the Profile RuntimeEvidence to runtime::ranking::revalidate and return boundary/depth/memory reasons. |
| invariants | Revalidation reports freshness; it never edits the retained Profile or updates old observations. |
| ownership | Borrows Profile/owner and returns numeric reason masks. Delegated temporary captures release on return. |
| failure | noexcept delegates conversion of capture/read failures to freshness reasons; no retry or state repair is added. |
| cost | Constant forwarding plus delegated actual-owner capture/census/binding checks, which can allocate and scan descriptors; not a constant-time getter. |
| Design | [docs/maintenance_cost.md](../../../../maintenance_cost.md), [include/crown/runtime/maintenance_cost.hpp](../../../../../include/crown/runtime/maintenance_cost.hpp), [src/runtime/ranking_evidence.cpp](../../../../../src/runtime/ranking_evidence.cpp) |

## B0051

[Lines 389–389](../../../../../src/runtime/maintenance_cost.cpp#L389); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
runtime::ranking::Revalidation revalidate(const Profile& p,const QuerySession& o) noexcept{return runtime::ranking::revalidate(p.evidence(),o);}
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Check whether retained cost evidence is current for QuerySession. |
| inputs / outputs | Profile and readable QuerySession forward the Profile RuntimeEvidence to runtime::ranking::revalidate and return boundary/depth/memory reasons. |
| invariants | Revalidation reports freshness; it never edits the retained Profile or updates old observations. |
| ownership | Borrows Profile/owner and returns numeric reason masks. Delegated temporary captures release on return. |
| failure | noexcept delegates conversion of capture/read failures to freshness reasons; no retry or state repair is added. |
| cost | Constant forwarding plus delegated actual-owner capture/census/binding checks, which can allocate and scan descriptors; not a constant-time getter. |
| Design | [docs/maintenance_cost.md](../../../../maintenance_cost.md), [include/crown/runtime/maintenance_cost.hpp](../../../../../include/crown/runtime/maintenance_cost.hpp), [src/runtime/ranking_evidence.cpp](../../../../../src/runtime/ranking_evidence.cpp) |

## B0052

[Lines 390–440](../../../../../src/runtime/maintenance_cost.cpp#L390); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Attempt estimate(const resource::MemoryAccount& account,const planner::CandidateSnapshot& snapshot,
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Estimate every retained checked candidate without choosing or mutating a running plan. |
| inputs / outputs | Receiver account, valid candidate Snapshot, Profile span, Calibration and complete unique physical table/op Request produce Result or Attempt stop/usage. |
| invariants | Validates candidate count and profile membership, matching physical-source/semantic/output identities, unique demand keys and per-candidate catalog/query equality. Missing profiles produce explicit profile_missing entries; duplicate/foreign profiles reject. All result entries precede publication. |
| ownership | Retains candidate/profile/calibration handles; copies input/output demand and allocates result/term arrays on receiver. Does not clone or mutate runtime rows, candidate proof or Request. |
| failure | Noexcept maps typed stops, allocation failures and unexpected errors. Any failing private estimate/binding drops the entire unpublished Result through RAII; older results and owners survive unchanged. |
| cost | With C candidates, P profiles, I demand items and D descriptors/profile: membership/selection O(C*P) key comparisons, demand validation O(I^2), binding serialization per present candidate, and evaluate O(D*(I+D)). Explicit cold model work, not per-update overhead or automatic C05 policy. |
| Design | [docs/maintenance_cost.md](../../../../maintenance_cost.md), [include/crown/runtime/maintenance_cost.hpp](../../../../../include/crown/runtime/maintenance_cost.hpp), [tests/unit/maintenance_cost_owner_exception_test.cpp](../../../../../tests/unit/maintenance_cost_owner_exception_test.cpp), [src/planner/ranking_detail.hpp](../../../../../src/planner/ranking_detail.hpp) |

```text
for(const auto& p:profiles){b.work();const auto& plan=p.evidence().inputs().plan();
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Check that all supplied profiles price the same physical source and output meaning. |
| inputs / outputs | Compares full source table count, physical-source SHA, semantic SHA and output-contract SHA against first profile. |
| invariants | Structural key equality alone is insufficient; candidate catalog/query binding is replayed again before evaluate. |
| ownership | Borrows profiles and plan metadata; no mutable runtime access. |
| failure | binding_mismatch/processing failure stops the whole unpublished Result. |
| cost | O(P) identity checks plus compared byte lengths; no source-row scan. |
| Design | [docs/maintenance_cost.md](../../../../maintenance_cost.md), [include/crown/runtime/maintenance_cost.hpp](../../../../../include/crown/runtime/maintenance_cost.hpp) |

```text
for(std::size_t i=0;i<request.input.size();++i){b.work();const auto& d=request.input[i];
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Admit one complete, unique demand entry for each physical table and set operation. |
| inputs / outputs | Even entry count defines table_count; every key lies in \[0,tables) x {insert,erase}, and pairwise duplicate checks ensure the complete finite key domain when profiles bind that table count. |
| invariants | Missing-profile entries remain explicitly unavailable; demands are assumptions, including explicit zeroes. With no profiles this validates the internally declared domain without a source-catalog match. |
| ownership | Borrows caller input span during validation; successful Result later copies it. |
| failure | Invalid operation/table/duplicates raise binding_mismatch before result publication; prior work remains spent. |
| cost | O(I^2) pairwise key comparisons with work checks; no hidden lookup-map allocation. |
| Design | [docs/maintenance_cost.md](../../../../maintenance_cost.md), [include/crown/runtime/maintenance_cost.hpp](../../../../../include/crown/runtime/maintenance_cost.hpp) |

## B0053

[Lines 441–441](../../../../../src/runtime/maintenance_cost.cpp#L441); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L441-L441:sha256:2da2de721b233d6ff94fbde44ff46c6a2d59a881eb231ef087c8299f0f20f768
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Close the \`namespace crown::runtime::cost\` scope at this exact source boundary. |
| inputs / outputs | This token introduces no callable inputs or outputs. Declarations inside \`namespace crown::runtime::cost\` define the available names, members and operations. |
| invariants | The closing brace matches the opening \`namespace crown::runtime::cost\` at its lexical source position in src/runtime/maintenance_cost.cpp; it preserves C++ namespace/type nesting. |
| ownership | The closing delimiter creates no owner. Types closed by \`namespace crown::runtime::cost\` retain the lifetimes and allocator rules of their own fields and operations. |
| failure | No failure path executes at this closing delimiter. Failure and cleanup behavior belong to enclosed functions and owning types. |
| cost | The delimiter itself performs no runtime work; the enclosed initializers, methods and destructors carry their own costs. |
| Design | [docs/maintenance_cost.md](../../../../maintenance_cost.md), [docs/workloads.md](../../../../workloads.md), [docs/code_specs/subsystem_contracts.md](../../../subsystem_contracts.md) |
