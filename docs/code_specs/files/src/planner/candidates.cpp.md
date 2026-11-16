# `src/planner/candidates.cpp` — block usage map

[Source](../../../../../src/planner/candidates.cpp) · [Source index](../../../README.md) · [Subsystem contracts](../../../subsystem_contracts.md) · [Reviewed primitives](../../../primitives.md)

Retain and enumerate checked minimum-height candidate alternatives under bounded content budgets.

Snapshot SHA-256: `54eb1629e27f484a8df59f1870715563b051af46426dcde8302a1575e3cbb21c`. 681 lines partitioned into 85 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [search](../../../subsystem_contracts.md#search). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/planner_proofs.md](../../../../planner_proofs.md), [docs/tree_oracle.md](../../../../tree_oracle.md), [docs/planner_continuations.md](../../../../planner_continuations.md), [docs/candidate_alternatives.md](../../../../candidate_alternatives.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–25](../../../../../src/planner/candidates.cpp#L1) | Imports dependencies; declares namespace scope; declares callable signatures; declares values/defaults or compile-time conditions. | growth new; source comment (unverified): // Admission serialization, snapshots and cache operations are explicit allocating · [reviewed contract](#b0001) |
| [B0002 · 26–26](../../../../../src/planner/candidates.cpp#L26) | Type/record definition: struct Stopped |  · [reviewed contract](#b0002) |
| [B0003 · 27–29](../../../../../src/planner/candidates.cpp#L27) | Callable definition: void room(std::uint64_t value) | calls  · [reviewed contract](#b0003) |
| [B0004 · 30–33](../../../../../src/planner/candidates.cpp#L30) | Callable definition: template&lt;class T&gt; const T& require(const std::shared_ptr&lt;const T&gt;& p) | calls Error; guard template&lt;class T&gt; const T& require(const std::shared_ptr&lt;const T&gt;& p) {; returns *p · [reviewed contract](#b0004) |
| [B0005 · 34–40](../../../../../src/planner/candidates.cpp#L34) | Callable definition: void context_valid(const CandidateContext& c) | calls Error · [reviewed contract](#b0005) |
| [B0006 · 41–45](../../../../../src/planner/candidates.cpp#L41) | Callable definition: bool same_context(const CandidateContext& a, const CandidateContext& b) noexcept | calls ; returns a.updates == b.updates && a.arithmetic == b.arithmetic && a.planner == b.planner && · [reviewed contract](#b0006) |
| [B0007 · 46–48](../../../../../src/planner/candidates.cpp#L46) | Callable definition: std::string binding_bytes(const Catalog& catalog, const Query& query) | calls binding_detail::encode; returns binding_detail::encode(catalog,query) · [reviewed contract](#b0007) |
| [B0008 · 49–58](../../../../../src/planner/candidates.cpp#L49) | Callable definition: CandidateStop translate(cand::GeneratorStop reason) noexcept | calls ; returns CandidateStop::depth_limit; CandidateStop::record_limit · [reviewed contract](#b0008) |
| [B0009 · 59–67](../../../../../src/planner/candidates.cpp#L59) | Callable definition: CandidateStop translate(cand::KeyStop reason) noexcept | calls ; returns CandidateStop::depth_limit; CandidateStop::record_limit · [reviewed contract](#b0009) |
| [B0010 · 68–75](../../../../../src/planner/candidates.cpp#L68) | Callable definition: CandidateStop translate(StopReason reason) noexcept | calls ; returns CandidateStop::total_work; CandidateStop::total_time · [reviewed contract](#b0010) |
| [B0011 · 76–81](../../../../../src/planner/candidates.cpp#L76) | declares namespace scope. | source comment (unverified): // namespace · [reviewed contract](#b0011) |
| [B0012 · 82–88](../../../../../src/planner/candidates.cpp#L82) | Type/record definition: struct InputData | source comment (unverified): // No live facade, seed holder or SnapshotData is reachable from InputData. · [reviewed contract](#b0012) |
| [B0013 · 89–94](../../../../../src/planner/candidates.cpp#L89) | Type/record definition: struct CandidateData |  · [reviewed contract](#b0013) |
| [B0014 · 95–95](../../../../../src/planner/candidates.cpp#L95) | Type/record definition: enum class ReuseOutcome |  · [reviewed contract](#b0014) |
| [B0015 · 96–100](../../../../../src/planner/candidates.cpp#L96) | Type/record definition: struct ReuseEvent |  · [reviewed contract](#b0015) |
| [B0016 · 101–102](../../../../../src/planner/candidates.cpp#L101) | Explanatory comments or spacing. | source comment (unverified): // Snapshot admission copies handle/event vectors, shares immutable payloads, · [reviewed contract](#b0016) |
| [B0017 · 103–109](../../../../../src/planner/candidates.cpp#L103) | Type/record definition: struct SnapshotData | source comment (unverified): // Snapshot admission copies handle/event vectors, shares immutable payloads, · [reviewed contract](#b0017) |
| [B0018 · 110–121](../../../../../src/planner/candidates.cpp#L110) | Type/record definition: struct Factory | guard static const SnapshotData& snapshot_data(const CandidateSnapshot& s) { return require(s.data_); }; returns MinimumHeightCandidate(std::move(p)); CandidateSnapshot(std::move(p)) · [reviewed contract](#b0018) |
| [B0019 · 122–123](../../../../../src/planner/candidates.cpp#L122) | Closes surrounding scope/type. | source comment (unverified): // namespace candidate_detail · [reviewed contract](#b0019) |
| [B0020 · 124–125](../../../../../src/planner/candidates.cpp#L124) | Callable definition: MinimumHeightCandidate::MinimumHeightCandidate( std::shared_ptr&lt;const cand::CandidateData&gt; p) noexcept : data_(std::move(p)) | calls data_, std::move · [reviewed contract](#b0020) |
| [B0021 · 126–126](../../../../../src/planner/candidates.cpp#L126) | Callable definition: bool MinimumHeightCandidate::valid() const noexcept | calls bool; returns bool(data_) · [reviewed contract](#b0021) |
| [B0022 · 127–127](../../../../../src/planner/candidates.cpp#L127) | Callable definition: const Catalog& MinimumHeightCandidate::catalog() const | calls require; guard const Catalog& MinimumHeightCandidate::catalog() const { return require(data_).input-&gt;binding-&gt;cata…; returns require(data_).input-&gt;binding-&gt;catalog · [reviewed contract](#b0022) |
| [B0023 · 128–128](../../../../../src/planner/candidates.cpp#L128) | Callable definition: const Query& MinimumHeightCandidate::query() const | calls require; guard const Query& MinimumHeightCandidate::query() const { return require(data_).input-&gt;binding-&gt;query; }; returns require(data_).input-&gt;binding-&gt;query · [reviewed contract](#b0023) |
| [B0024 · 129–129](../../../../../src/planner/candidates.cpp#L129) | Callable definition: const FreeConnexTree& MinimumHeightCandidate::tree() const | calls require; guard const FreeConnexTree& MinimumHeightCandidate::tree() const { return *require(data_).upper-&gt;tree; }; returns *require(data_).upper-&gt;tree · [reviewed contract](#b0024) |
| [B0025 · 130–130](../../../../../src/planner/candidates.cpp#L130) | Callable definition: const ValidationReport& MinimumHeightCandidate::validation() const | calls require; guard const ValidationReport& MinimumHeightCandidate::validation() const {return *require(data_).upper-&gt;r…; returns *require(data_).upper-&gt;report · [reviewed contract](#b0025) |
| [B0026 · 131–131](../../../../../src/planner/candidates.cpp#L131) | Callable definition: std::size_t MinimumHeightCandidate::height() const | calls require; guard std::size_t MinimumHeightCandidate::height() const { return require(data_).upper-&gt;height; }; returns require(data_).upper-&gt;height · [reviewed contract](#b0026) |
| [B0027 · 132–132](../../../../../src/planner/candidates.cpp#L132) | Callable definition: const std::string& MinimumHeightCandidate::structural_key() const | calls require; guard const std::string& MinimumHeightCandidate::structural_key() const { return *require(data_).key; }; returns *require(data_).key · [reviewed contract](#b0027) |
| [B0028 · 133–133](../../../../../src/planner/candidates.cpp#L133) | Callable definition: const CandidateContext& MinimumHeightCandidate::context() const | calls require; guard const CandidateContext& MinimumHeightCandidate::context() const { return require(data_).input-&gt;cont…; returns require(data_).input-&gt;context · [reviewed contract](#b0028) |
| [B0029 · 134–134](../../../../../src/planner/candidates.cpp#L134) | Callable definition: CandidateProvenance MinimumHeightCandidate::provenance() const | calls require; guard CandidateProvenance MinimumHeightCandidate::provenance() const { return require(data_).provenance; }; returns require(data_).provenance · [reviewed contract](#b0029) |
| [B0030 · 135–135](../../../../../src/planner/candidates.cpp#L135) | Callable definition: VerifiedOptimum MinimumHeightCandidate::original_proof() const | calls require; guard VerifiedOptimum MinimumHeightCandidate::original_proof() const { return require(data_).input-&gt;proof…; returns require(data_).input-&gt;proof · [reviewed contract](#b0030) |
| [B0031 · 136–137](../../../../../src/planner/candidates.cpp#L136) | Callable definition: CandidateSnapshot::CandidateSnapshot( std::shared_ptr&lt;const cand::SnapshotData&gt; p) noexcept : data_(std::move(p)) | calls data_, std::move · [reviewed contract](#b0031) |
| [B0032 · 138–138](../../../../../src/planner/candidates.cpp#L138) | Callable definition: bool CandidateSnapshot::valid() const noexcept | calls bool; returns bool(data_) · [reviewed contract](#b0032) |
| [B0033 · 139–139](../../../../../src/planner/candidates.cpp#L139) | Callable definition: std::size_t CandidateSnapshot::candidate_count() const | calls require, size; guard std::size_t CandidateSnapshot::candidate_count() const { return require(data_).candidates.size(); }; returns require(data_).candidates.size() · [reviewed contract](#b0033) |
| [B0034 · 140–144](../../../../../src/planner/candidates.cpp#L140) | Callable definition: std::optional&lt;MinimumHeightCandidate&gt; CandidateSnapshot::candidate(std::size_t i) const | calls require, size; guard const auto& d = require(data_);; returns {}; d.candidates\[i\] · [reviewed contract](#b0034) |
| [B0035 · 145–145](../../../../../src/planner/candidates.cpp#L145) | Callable definition: bool CandidateSnapshot::family_exhausted() const | calls require; guard bool CandidateSnapshot::family_exhausted() const { return require(data_).exhausted; }; returns require(data_).exhausted · [reviewed contract](#b0035) |
| [B0036 · 146–148](../../../../../src/planner/candidates.cpp#L146) | Callable definition: CandidateFamily CandidateSnapshot::family() const | calls require; guard return require(data_).family;; returns require(data_).family · [reviewed contract](#b0036) |
| [B0037 · 149–149](../../../../../src/planner/candidates.cpp#L149) | Callable definition: const CandidateContext& CandidateSnapshot::context() const | calls require; guard const CandidateContext& CandidateSnapshot::context() const { return require(data_).input-&gt;context; }; returns require(data_).input-&gt;context · [reviewed contract](#b0037) |
| [B0038 · 150–150](../../../../../src/planner/candidates.cpp#L150) | Callable definition: VerifiedOptimum CandidateSnapshot::original_proof() const | calls require; guard VerifiedOptimum CandidateSnapshot::original_proof() const { return require(data_).input-&gt;proof; }; returns require(data_).input-&gt;proof · [reviewed contract](#b0038) |
| [B0039 · 151–161](../../../../../src/planner/candidates.cpp#L151) | declares types or opens a type body. | source comment (unverified): // One unit dispatches one saved stage or delegated worker step. Full-key set · [reviewed contract](#b0039) |
| [B0040 · 162–166](../../../../../src/planner/candidates.cpp#L162) | Type/record definition: enum class Stage | growth reserve · [reviewed contract](#b0040) |
| [B0041 · 167–167](../../../../../src/planner/candidates.cpp#L167) | Type/record definition: enum class Origin |  · [reviewed contract](#b0041) |
| [B0042 · 168–169](../../../../../src/planner/candidates.cpp#L168) | Explanatory comments or spacing. | source comment (unverified): // Ordered dedup uses complete string bytes: O(key width) per comparison, · [reviewed contract](#b0042) |
| [B0043 · 170–175](../../../../../src/planner/candidates.cpp#L170) | Type/record definition: struct KeyLess | returns *a &lt; *b; source comment (unverified): // Ordered dedup uses complete string bytes: O(key width) per comparison, · [reviewed contract](#b0043) |
| [B0044 · 176–207](../../../../../src/planner/candidates.cpp#L176) | declares values/defaults or compile-time conditions. | source comment (unverified): // These holders never become part of InputData or a new candidate payload. · [reviewed contract](#b0044) |
| [B0045 · 208–212](../../../../../src/planner/candidates.cpp#L208) | Callable definition: Impl(std::shared_ptr&lt;const cand::InputData&gt; in, CandidateLimits l, std::shared_ptr&lt;const ResidualCandidate&gt; r, std::optional&lt;Cand… | calls input, std::move, residual, prefix; growth make_shared · [reviewed contract](#b0045) |
| [B0046 · 213–215](../../../../../src/planner/candidates.cpp#L213) | Callable definition: bool terminal() const noexcept | calls ; returns stage == Stage::complete \|\| stage == Stage::failed \|\| stage == Stage::cancelled · [reviewed contract](#b0046) |
| [B0047 · 216–219](../../../../../src/planner/candidates.cpp#L216) | Callable definition: CandidateStop terminal_reason() const noexcept | calls ; returns stage == Stage::complete ? CandidateStop::exhausted : · [reviewed contract](#b0047) |
| [B0048 · 220–220](../../../../../src/planner/candidates.cpp#L220) | Callable definition: void fail(CandidateStop r) noexcept | calls  · [reviewed contract](#b0048) |
| [B0049 · 221–226](../../../../../src/planner/candidates.cpp#L221) | Callable definition: std::size_t depth() const noexcept | calls current_depth; returns validator-&gt;current_depth(); canonicalizer-&gt;current_depth() · [reviewed contract](#b0049) |
| [B0050 · 227–244](../../../../../src/planner/candidates.cpp#L227) | Callable definition: CandidatePhase phase() const noexcept | calls ; returns CandidatePhase::exact_seed; CandidatePhase::residual_seed; growth reserve · [reviewed contract](#b0050) |
| [B0051 · 245–247](../../../../../src/planner/candidates.cpp#L245) | Callable definition: void outcome(cand::ReuseOutcome o) noexcept | calls  · [reviewed contract](#b0051) |
| [B0052 · 248–249](../../../../../src/planner/candidates.cpp#L248) | Explanatory comments or spacing. | source comment (unverified): // Drop temporary gate owners only. Published handles, seen membership and · [reviewed contract](#b0052) |
| [B0053 · 250–254](../../../../../src/planner/candidates.cpp#L250) | Callable definition: void discard() noexcept | calls reset; source comment (unverified): // Drop temporary gate owners only. Published handles, seen membership and · [reviewed contract](#b0053) |
| [B0054 · 255–257](../../../../../src/planner/candidates.cpp#L255) | Explanatory comments or spacing. | source comment (unverified): // One retained stage/child step. Every source re-enters original P02/height/ · [reviewed contract](#b0054) |
| [B0055 · 258–434](../../../../../src/planner/candidates.cpp#L258) | Callable definition: CandidateStop unit() | calls upper, tree, origin, trace; returns translate(result.reason); CandidateStop::depth_limit; growth insert, make_shared, make_unique, push_back, reserve; source comment (unverified): // One retained stage/child step. Every source re-enters original P02/height/ · [reviewed contract](#b0055) |
| [B0056 · 435–435](../../../../../src/planner/candidates.cpp#L435) | Closes surrounding scope/type. |  · [reviewed contract](#b0056) |
| [B0057 · 436–436](../../../../../src/planner/candidates.cpp#L436) | Callable definition: CandidateProvider::CandidateProvider(std::unique_ptr&lt;Impl&gt; p) noexcept : data_(std::move(p)) | calls data_, std::move · [reviewed contract](#b0057) |
| [B0058 · 437–442](../../../../../src/planner/candidates.cpp#L437) | declares callable signatures; declares values/defaults or compile-time conditions. | source comment (unverified): // Whole binding serialization/comparisons and owned Catalog/Query admission · [reviewed contract](#b0058) |
| [B0059 · 443–467](../../../../../src/planner/candidates.cpp#L443) | Callable definition: CandidateProvider CandidateProvider::create(VerifiedOptimum proof, CandidateContext context, CandidateLimits limits, std::optiona… | calls context_valid, valid, Error, cd::valid_ceiling; returns CandidateProvider(std::make_unique&lt;Impl&gt;(std::move(input), limits, std::move(seed), std::move(prefi…; growth make_shared, make_unique; source comment (unverified): // Whole binding serialization/comparisons and owned Catalog/Query admission · [reviewed contract](#b0059) |
| [B0060 · 468–475](../../../../../src/planner/candidates.cpp#L468) | Callable definition: CandidateProvider CandidateProvider::from_proposals(VerifiedOptimum proof, std::vector&lt;FreeConnexTree&gt; proposals, CandidateContex… | calls create, std::move; returns owner · [reviewed contract](#b0060) |
| [B0061 · 476–478](../../../../../src/planner/candidates.cpp#L476) | Explanatory comments or spacing. | source comment (unverified): // Keep resource/allocation catches: workers retain the same pending operation. · [reviewed contract](#b0061) |
| [B0062 · 479–544](../../../../../src/planner/candidates.cpp#L479) | Callable definition: CandidateAdvance CandidateProvider::advance(WorkQuantum quantum) noexcept | calls progress, answer, count, terminal; guard const auto limit = d.ledger.check();; returns CandidateAdvance{s, progress()}; answer(CandidateStop::moved_from); 1 loop sites; source comment (unverified): // Keep resource/allocation catches: workers retain the same pending operation. · [reviewed contract](#b0062) |
| [B0063 · 545–554](../../../../../src/planner/candidates.cpp#L545) | Callable definition: CandidateProgress CandidateProvider::progress() const noexcept | calls phase, records, cells, size; returns p; p · [reviewed contract](#b0063) |
| [B0064 · 555–555](../../../../../src/planner/candidates.cpp#L555) | Callable definition: std::size_t CandidateProvider::candidate_count() const noexcept | calls size; returns data_ ? data_-&gt;published.size() : 0 · [reviewed contract](#b0064) |
| [B0065 · 556–557](../../../../../src/planner/candidates.cpp#L556) | Explanatory comments or spacing. | source comment (unverified): // Return an owning value, never a vector element borrow. Tree/key/report owners · [reviewed contract](#b0065) |
| [B0066 · 558–561](../../../../../src/planner/candidates.cpp#L558) | Callable definition: std::optional&lt;MinimumHeightCandidate&gt; CandidateProvider::candidate(std::size_t i) const noexcept | calls size; returns {}; data_-&gt;published\[i\]; source comment (unverified): // Return an owning value, never a vector element borrow. Tree/key/report owners · [reviewed contract](#b0066) |
| [B0067 · 562–565](../../../../../src/planner/candidates.cpp#L562) | Callable definition: VerifiedOptimum CandidateProvider::original_proof() const | calls Error; returns data_-&gt;input-&gt;proof · [reviewed contract](#b0067) |
| [B0068 · 566–569](../../../../../src/planner/candidates.cpp#L566) | Callable definition: const CandidateContext& CandidateProvider::context() const | calls Error; returns data_-&gt;input-&gt;context · [reviewed contract](#b0068) |
| [B0069 · 570–573](../../../../../src/planner/candidates.cpp#L570) | Callable definition: CandidateLimits CandidateProvider::limits() const | calls Error; returns data_-&gt;limits · [reviewed contract](#b0069) |
| [B0070 · 574–592](../../../../../src/planner/candidates.cpp#L574) | Callable definition: LimitChange CandidateProvider::raise_limits(CandidateLimits next) noexcept | calls terminal, cd::valid_ceiling, cd::monotone_phase, cd::monotone_ceiling; returns LimitChange::terminal; LimitChange::invalid · [reviewed contract](#b0070) |
| [B0071 · 593–601](../../../../../src/planner/candidates.cpp#L593) | Callable definition: void CandidateProvider::cancel() noexcept | calls terminal, cancel, discard, reset · [reviewed contract](#b0071) |
| [B0072 · 602–603](../../../../../src/planner/candidates.cpp#L602) | Explanatory comments or spacing. | source comment (unverified): // Explicit allocating admission outside work/content grants. Vector-copy failure · [reviewed contract](#b0072) |
| [B0073 · 604–609](../../../../../src/planner/candidates.cpp#L604) | Callable definition: CandidateSnapshot CandidateProvider::snapshot() const | calls Error, cand::Factory::snapshot; returns cand::Factory::snapshot(std::make_shared&lt;const cand::SnapshotData&gt;(cand::SnapshotData{; growth make_shared; source comment (unverified): // Explicit allocating admission outside work/content grants. Vector-copy failure · [reviewed contract](#b0073) |
| [B0074 · 610–610](../../../../../src/planner/candidates.cpp#L610) | Explanatory comments or spacing. |  |
| [B0075 · 611–616](../../../../../src/planner/candidates.cpp#L611) | Type/record definition: struct CandidateCache::Impl |  · [reviewed contract](#b0075) |
| [B0076 · 617–617](../../../../../src/planner/candidates.cpp#L617) | Callable definition: CandidateCache::CandidateCache(std::unique_ptr&lt;Impl&gt; p) noexcept : data_(std::move(p)) | calls data_, std::move · [reviewed contract](#b0076) |
| [B0077 · 618–620](../../../../../src/planner/candidates.cpp#L618) | declares callable signatures; declares values/defaults or compile-time conditions. |  · [reviewed contract](#b0077) |
| [B0078 · 621–621](../../../../../src/planner/candidates.cpp#L621) | Callable definition: CandidateCache CandidateCache::create(std::size_t capacity) | calls CandidateCache; returns CandidateCache(std::make_unique&lt;Impl&gt;(capacity)); growth make_unique · [reviewed contract](#b0078) |
| [B0079 · 622–623](../../../../../src/planner/candidates.cpp#L622) | Explanatory comments or spacing. | source comment (unverified): // Full source encoding plus linear FIFO scan; each comparison is variable-width. · [reviewed contract](#b0079) |
| [B0080 · 624–642](../../../../../src/planner/candidates.cpp#L624) | Callable definition: std::optional&lt;CandidateSnapshot&gt; CandidateCache::lookup(const VerifiedOptimum& proof, const CandidateContext& context) | calls Error, context_valid, valid, binding; returns snapshot; {}; 1 loop sites; source comment (unverified): // Full source encoding plus linear FIFO scan; each comparison is variable-width. · [reviewed contract](#b0080) |
| [B0081 · 643–645](../../../../../src/planner/candidates.cpp#L643) | Explanatory comments or spacing. | source comment (unverified): // Replacement preserves FIFO order. Prepare a new list node before splice and · [reviewed contract](#b0081) |
| [B0082 · 646–675](../../../../../src/planner/candidates.cpp#L646) | Callable definition: CandidateCacheInstall CandidateCache::install(const CandidateSnapshot& snapshot) | calls Error, cand::Factory::snapshot_data, same_context, std::move; returns CandidateCacheInstall::disabled; CandidateCacheInstall::replaced; growth push_back; 1 loop sites; source comment (unverified): // Replacement preserves FIFO order. Prepare a new list node before splice and · [reviewed contract](#b0082) |
| [B0083 · 676–679](../../../../../src/planner/candidates.cpp#L676) | Callable definition: CandidateCacheStatistics CandidateCache::statistics() const noexcept | calls size; returns {}; stats · [reviewed contract](#b0083) |
| [B0084 · 680–680](../../../../../src/planner/candidates.cpp#L680) | Callable definition: void CandidateCache::clear() noexcept | calls clear · [reviewed contract](#b0084) |
| [B0085 · 681–681](../../../../../src/planner/candidates.cpp#L681) | Closes surrounding scope/type. | source comment (unverified): // namespace crown::planner · [reviewed contract](#b0085) |

## B0001

[Lines 1–25](../../../../../src/planner/candidates.cpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L1-L25:sha256:eb0b46f6e624f635a3fe8e0dfb8644fbb1374ba7a98d5cb1f73c76434215ae6c
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | make #include "crown/planner/candidates.hpp", #include "candidate_machine.hpp", #include "candidate_key.hpp", #include "candidate_binding.hpp", #include "continuation_budget.hpp", #include "crown/api/error.hpp", #include &lt;algorithm&gt;, #include &lt;climits&gt;, #include &lt;list&gt;, #include &lt;limits&gt;, #include &lt;new&gt;, #include &lt;set&gt;, #include &lt;string_view&gt;, #include &lt;utility&gt;, #include &lt;vector&gt; available to src/planner/candidates.cpp; open crown::planner and anonymous helper namespace. Attached note: Admission serialization, snapshots and cache operations are explicit allocating work outside advance(). Keep complete binding bytes: a digest or an alpha- equivalent binding is not authority to reuse an original-query certificate. In this span, bind cd = continuation_detail, cand = candidate_detail. Define constexpr bounds maximum. |
| inputs / outputs | Includes supply declarations; the listed namespace aliases bind names, and any listed constexpr bounds are constant-initialized metadata. These declarations do not run a planner search or validate a query. |
| invariants | Includes, namespace openings, aliases, and forward declarations determine C++ name visibility and type availability; they do not validate planner data or grant proof authority. |
| ownership | Namespace aliases own no runtime object. Any constexpr bounds in this span are fixed scalar metadata; no query owner, mutable counter or allocation grant is created by them. |
| failure | A missing header, incompatible declaration, or ill-formed type use fails during compilation; runtime failures remain in the called code. |
| cost | Preprocessing, name lookup and compile-time constant evaluation; constexpr bounds require no dynamic initialization and can occupy fixed constant storage when used. Included definitions retain their own call/construction costs. |
| Design | [src/planner/candidates.cpp](../../../../../src/planner/candidates.cpp), [docs/planner_proofs.md](../../../../planner_proofs.md), [docs/residual_candidates.md](../../../../residual_candidates.md), [docs/planner_continuations.md](../../../../planner_continuations.md) |

## B0002

[Lines 26–26](../../../../../src/planner/candidates.cpp#L26); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct Stopped {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Carry a fixed provider stop through private stage dispatch. |
| inputs / outputs | One CandidateStop reason. |
| invariants | Internal invariant/overflow reasons terminalize; ordinary returned resource stops retain the stage. |
| ownership | Scalar-only local exception object. |
| failure | No message allocation. |
| cost | Constant payload. |
| Design | [include/crown/planner/candidates.hpp](../../../../../include/crown/planner/candidates.hpp) |

## B0003

[Lines 27–29](../../../../../src/planner/candidates.cpp#L27); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void room(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Preflight a provider counter increment. |
| inputs / outputs | uint64 value compared to maximum. |
| invariants | Runs before corresponding state publication; failure leaves counter unchanged. |
| ownership | Read-only scalar input. |
| failure | Throws Stopped(counter_overflow). |
| cost | Constant comparison. |
| Design | [include/crown/planner/candidates.hpp](../../../../../include/crown/planner/candidates.hpp), [docs/candidate_alternatives.md](../../../../candidate_alternatives.md) |

## B0004

[Lines 30–33](../../../../../src/planner/candidates.cpp#L30); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
template<class T> const T& require(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Reject moved-from public candidate/snapshot handles before dereference. |
| inputs / outputs | Shared immutable payload in; const payload reference out. |
| invariants | Privately published nonnull payload already satisfies inner ownership invariants. |
| ownership | Returns a borrow without retaining another owner. |
| failure | Throws invalid_candidate_handle; successful access allocates nothing. |
| cost | Constant null check and dereference. |
| Design | [include/crown/planner/candidates.hpp](../../../../../include/crown/planner/candidates.hpp) |

## B0005

[Lines 34–40](../../../../../src/planner/candidates.cpp#L34); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void context_valid(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Reject unsupported semantic/cache namespace profiles at admission. |
| inputs / outputs | CandidateContext input; normal return for supported exact strings/profile. |
| invariants | All six context fields must match known versions; namespace acceptance does not establish cost ranking or runtime complexity. |
| ownership | Borrows strings during call. |
| failure | Throws invalid_candidate_context for any mismatch. |
| cost | Fixed number of variable-width string comparisons. |
| Design | [include/crown/planner/candidates.hpp](../../../../../include/crown/planner/candidates.hpp), [docs/candidate_alternatives.md](../../../../candidate_alternatives.md) |

## B0006

[Lines 41–45](../../../../../src/planner/candidates.cpp#L41); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
bool same_context(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Require full context equality when reusing cached candidates. |
| inputs / outputs | Two contexts; Boolean. |
| invariants | Compares update profile and every string field, with no digest/partial match. |
| ownership | Borrows immutable contexts only. |
| failure | Noexcept; string equality does not allocate. |
| cost | Fixed field count, variable character comparisons. |
| Design | [include/crown/planner/candidates.hpp](../../../../../include/crown/planner/candidates.hpp), [docs/candidate_alternatives.md](../../../../candidate_alternatives.md) |

## B0007

[Lines 46–48](../../../../../src/planner/candidates.cpp#L46); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::string binding_bytes(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Obtain complete deterministic source identity bytes for admission/cache fences. |
| inputs / outputs | Catalog/Query; owning encoded string. |
| invariants | Delegates private v2 exact field/type/length encoding; output is identity data, not proof or a durable checkpoint. |
| ownership | Returned string owns its bytes; inputs borrowed for traversal. |
| failure | Encoder/ordinary allocation exceptions propagate before cache/provider publication. |
| cost | Traverses/copies complete binding content; variable-width admission outside advance. |
| Design | [src/planner/candidate_binding.hpp](../../../../../src/planner/candidate_binding.hpp), [docs/candidate_alternatives.md](../../../../candidate_alternatives.md) |

## B0008

[Lines 49–58](../../../../../src/planner/candidates.cpp#L49); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
CandidateStop translate(cand::GeneratorStop
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Translate generator resource reasons into provider stops. |
| inputs / outputs | GeneratorStop to CandidateStop. |
| invariants | None/unknown value fails closed as internal_failure; overflow remains terminal. |
| ownership | Scalar translation. |
| failure | Noexcept; allocates no diagnostic. |
| cost | Constant switch. |
| Design | [src/planner/candidate_machine.hpp](../../../../../src/planner/candidate_machine.hpp), [include/crown/planner/candidates.hpp](../../../../../include/crown/planner/candidates.hpp) |

## B0009

[Lines 59–67](../../../../../src/planner/candidates.cpp#L59); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
CandidateStop translate(cand::KeyStop
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Translate key-worker resource reasons without hiding invalid/cancelled worker state. |
| inputs / outputs | KeyStop to CandidateStop. |
| invariants | Depth/record/cell/overflow preserved; every other reason becomes internal_failure. |
| ownership | Value only. |
| failure | Noexcept. |
| cost | Constant switch. |
| Design | [src/planner/candidate_key.hpp](../../../../../src/planner/candidate_key.hpp), [include/crown/planner/candidates.hpp](../../../../../include/crown/planner/candidates.hpp) |

## B0010

[Lines 68–75](../../../../../src/planner/candidates.cpp#L68); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
CandidateStop translate(StopReason
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Translate outer ledger work/time/overflow checks. |
| inputs / outputs | StopReason to CandidateStop. |
| invariants | Unexpected exact-search/lifecycle reasons are internal_failure; provider performs no delegated exact search. |
| ownership | Scalar translation. |
| failure | Noexcept. |
| cost | Constant switch. |
| Design | [src/planner/continuation_budget.hpp](../../../../../src/planner/continuation_budget.hpp), [include/crown/planner/candidates.hpp](../../../../../include/crown/planner/candidates.hpp) |

## B0011

[Lines 76–81](../../../../../src/planner/candidates.cpp#L76); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L76-L81:sha256:66fd0214c0662183e53fedeb2225302999c40853d34e26a187dbf105998d3a98
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Close the anonymous namespace, then open candidate_detail within crown::planner. The attached note is caller guidance: No live facade, seed holder or SnapshotData is reachable from InputData. Immutable source/proof namespace only. Excluding residual/prefix/provider holders prevents cached reuse from retaining a chain of old snapshots. |
| inputs / outputs | This namespace, scope, or declaration boundary has no runtime call inputs or outputs. |
| invariants | It changes compile-time visibility or declaration identity only; attached comments do not enforce or prove the described behavior. |
| ownership | This span creates no runtime owner. Later object definitions and calls determine storage and lifetimes. |
| failure | An invalid declaration or scope boundary fails compilation; no runtime exception or resource stop comes from this span. |
| cost | Compile-time parsing and preprocessor bookkeeping only; no runtime branch, allocation, clock read, counter debit, or engine hook. |
| Design | [src/planner/candidates.cpp](../../../../../src/planner/candidates.cpp), [docs/planner_proofs.md](../../../../planner_proofs.md), [docs/residual_candidates.md](../../../../residual_candidates.md), [docs/planner_continuations.md](../../../../planner_continuations.md) |

## B0012

[Lines 82–88](../../../../../src/planner/candidates.cpp#L82); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct InputData {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Retain immutable original proof, exact binding/context identity and known height. |
| inputs / outputs | VerifiedOptimum, owned context, independent copied BindingData, full binding bytes, height. |
| invariants | No live provider/residual holder/old SnapshotData is reachable here; new cached candidates attach this provider proof. |
| ownership | Shares original proof payload and separately owns source copy/context/identity bytes. |
| failure | Prepared completely during create before publication; private aggregate does not replay proof anew. |
| cost | Full source/context/identity storage plus retained original proof; admission excluded from logical content budget. |
| Design | [include/crown/planner/candidates.hpp](../../../../../include/crown/planner/candidates.hpp), [docs/candidate_alternatives.md](../../../../candidate_alternatives.md), [include/crown/planner/search.hpp](../../../../../include/crown/planner/search.hpp) |

## B0013

[Lines 89–94](../../../../../src/planner/candidates.cpp#L89); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct CandidateData {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Own one accepted alternative with its canonical key and generation provenance. |
| inputs / outputs | Shared InputData/CheckedUpper/full key plus provenance. |
| invariants | CheckedUpper binding equals InputData binding and height equals supplied minimum. Alternative never replaces original proof witness. |
| ownership | Shared immutable owners avoid raw borrowed tree/key lifetimes; provenance may retain a ResidualTrace only. |
| failure | Constructed privately after gates; allocation failure leaves dedup membership uncommitted. |
| cost | Constant owner payload plus transitive tree/report/key/proof storage. |
| Design | [include/crown/planner/candidates.hpp](../../../../../include/crown/planner/candidates.hpp), [docs/candidate_alternatives.md](../../../../candidate_alternatives.md), [src/planner/verify.cpp](../../../../../src/planner/verify.cpp) |

## B0014

[Lines 95–95](../../../../../src/planner/candidates.cpp#L95); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
enum class ReuseOutcome {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Distinguish pending and completed checks of cached-prefix entries. |
| inputs / outputs | pending/published/duplicate/rejected/taller. |
| invariants | Reuse result is diagnostic; a cache hit is not unchecked publication. |
| ownership | Scalar in each ReuseEvent. |
| failure | No failure in enum. |
| cost | Constant storage. |
| Design | [docs/candidate_alternatives.md](../../../../candidate_alternatives.md) |

## B0015

[Lines 96–100](../../../../../src/planner/candidates.cpp#L96); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct ReuseEvent {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Retain cache replay context without retaining a former snapshot/provider chain. |
| inputs / outputs | Prefix index, copied generation provenance and outcome. |
| invariants | Copied provenance carries only scalar fields/optional trace; it does not retain MinimumHeightCandidate or SnapshotData. |
| ownership | Owns generation value; snapshot may copy these events. |
| failure | Append is budgeted/prepared before origin/draft cursor changes. |
| cost | Constant record/one logical cell plus optional shared trace owner. |
| Design | [docs/candidate_alternatives.md](../../../../candidate_alternatives.md), [include/crown/planner/candidates.hpp](../../../../../include/crown/planner/candidates.hpp) |

## B0016

[Lines 101–102](../../../../../src/planner/candidates.cpp#L101); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L101-L102:sha256:1dabcd780b8c71c3abef639cdc031852ebf17a0454e332c2a937e1e6c2cb04bf
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Use the adjacent note for SnapshotData: Snapshot admission copies handle/event vectors, shares immutable payloads, and records real exhaustion; it never captures the active generator cursor. Confirm behavior against the declaration and implementation; comment text alone does not enforce or prove it. |
| inputs / outputs | This comment has no inputs or outputs. It accompanies SnapshotData; use the adjacent declaration and implementation for the actual values and result. |
| invariants | This is static guidance only. The comment cannot alter state or guarantee that its wording holds. |
| ownership | The note owns no storage and changes no lifetime; ownership and borrowing for SnapshotData come from its actual types and implementation. |
| failure | Reading the comment has no runtime failure path. Compile or link errors, exceptions, and resource stops belong to the adjacent code. |
| cost | The comment adds no runtime instructions, allocation, clock read, counter debit, or engine hook; only source-text processing is added. |
| Design | [src/planner/candidates.cpp](../../../../../src/planner/candidates.cpp), [docs/planner_proofs.md](../../../../planner_proofs.md), [docs/residual_candidates.md](../../../../residual_candidates.md), [docs/planner_continuations.md](../../../../planner_continuations.md) |

## B0017

[Lines 103–109](../../../../../src/planner/candidates.cpp#L103); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct SnapshotData {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Freeze one provider prefix plus actual family completion and reuse diagnostics. |
| inputs / outputs | Shared InputData, candidate vector, reuse vector, exhausted flag. The immutable family field records the originating provider route. |
| invariants | No live generator/cursor or old SnapshotData is stored. All candidate handles already passed this provider gates. |
| ownership | Owns vector copies of immutable handles/events and shared input. |
| failure | Snapshot allocation/copies may throw without changing provider. |
| cost | O(candidate+reuse counts) copied records outside advance; transitive history remains explicitly retained. |
| Design | [include/crown/planner/candidates.hpp](../../../../../include/crown/planner/candidates.hpp), [docs/candidate_alternatives.md](../../../../candidate_alternatives.md), [docs/meta_decompositions.md](../../../../meta_decompositions.md) |

## B0018

[Lines 110–121](../../../../../src/planner/candidates.cpp#L110); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct Factory {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Bridge private artifact constructors and internal retained-tree access. |
| inputs / outputs | candidate/snapshot adopt owners; snapshot_data borrows; tree returns shared checked tree. |
| invariants | Does no P02 or proof replay; call sites must establish gates before construction. |
| ownership | Moves/copies shared owners; borrow requires source handle remain alive. |
| failure | Constructors noexcept; require rejects moved-from internal access. |
| cost | Constant owner operations, no payload copying. |
| Design | [include/crown/planner/candidates.hpp](../../../../../include/crown/planner/candidates.hpp), [docs/candidate_alternatives.md](../../../../candidate_alternatives.md) |

## B0019

[Lines 122–123](../../../../../src/planner/candidates.cpp#L122); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L122-L123:sha256:3f2467eddffb7ecca4ad77c9257094e3ac07c9834a52be644f8e3710af06fa09
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | This block close namespace candidate_detail. |
| inputs / outputs | A scope delimiter has no call inputs or outputs; it controls which following declarations belong to the C++ namespace, class, or helper scope. |
| invariants | The braces set lexical visibility and type boundaries only. Any attached note is documentation and does not enforce behavior. |
| ownership | The delimiter and note acquire, release, or transfer no runtime object. Member lifetimes come from the enclosed type definitions. |
| failure | An unmatched or misplaced brace fails compilation; this block adds no runtime exception or resource-stop path. |
| cost | No runtime work or allocation is added. The compiler parses the scope boundary and comment. |
| Design | [src/planner/candidates.cpp](../../../../../src/planner/candidates.cpp), [docs/planner_proofs.md](../../../../planner_proofs.md), [docs/residual_candidates.md](../../../../residual_candidates.md), [docs/planner_continuations.md](../../../../planner_continuations.md) |

## B0020

[Lines 124–125](../../../../../src/planner/candidates.cpp#L124); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
MinimumHeightCandidate::MinimumHeightCandidate(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Adopt a fully prepared accepted candidate payload. |
| inputs / outputs | Shared const CandidateData moved into private handle. |
| invariants | Only Factory can construct; all upper/height/key gates precede this call. |
| ownership | Moves immutable shared ownership. |
| failure | Noexcept; no allocation/validation. |
| cost | Constant-time. |
| Design | [include/crown/planner/candidates.hpp](../../../../../include/crown/planner/candidates.hpp) |

## B0021

[Lines 126–126](../../../../../src/planner/candidates.cpp#L126); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
bool MinimumHeightCandidate::valid()
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Detect moved-from candidate handles. |
| inputs / outputs | True iff payload owner exists. |
| invariants | Presence denotes privately created handle, not a new proof computation. |
| ownership | Reads shared pointer. |
| failure | Noexcept. |
| cost | Constant-time. |
| Design | [include/crown/planner/candidates.hpp](../../../../../include/crown/planner/candidates.hpp) |

## B0022

[Lines 127–127](../../../../../src/planner/candidates.cpp#L127); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
const Catalog& MinimumHeightCandidate::catalog()
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Expose the accepted original catalog. |
| inputs / outputs | Const Catalog& from InputData binding. |
| invariants | Matches the supplied original query proof and P02 binding. |
| ownership | Borrow into immutable retained input; keep handle alive. |
| failure | Moved-from access throws invalid_candidate_handle. |
| cost | Constant pointer traversal. |
| Design | [include/crown/planner/candidates.hpp](../../../../../include/crown/planner/candidates.hpp), [docs/candidate_alternatives.md](../../../../candidate_alternatives.md) |

## B0023

[Lines 128–128](../../../../../src/planner/candidates.cpp#L128); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
const Query& MinimumHeightCandidate::query()
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Expose the original query certified for the alternative. |
| inputs / outputs | Const Query& from input binding. |
| invariants | Original occurrence/variable/head identity remains exact; no alpha-remapped transplant. |
| ownership | Borrow backed by live shared input. |
| failure | Moved-from getter rejects. |
| cost | Constant access without copying. |
| Design | [include/crown/planner/candidates.hpp](../../../../../include/crown/planner/candidates.hpp), [docs/candidate_alternatives.md](../../../../candidate_alternatives.md) |

## B0024

[Lines 129–129](../../../../../src/planner/candidates.cpp#L129); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
const FreeConnexTree& MinimumHeightCandidate::tree()
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Read this checked alternative upper tree. |
| inputs / outputs | Const tree reference from CheckedUpper. |
| invariants | This is separate from original_proof certificate witness. |
| ownership | Borrow retains no extra owner; candidate upper backs its lifetime. |
| failure | Moved-from handle rejects. |
| cost | Constant access. |
| Design | [include/crown/planner/candidates.hpp](../../../../../include/crown/planner/candidates.hpp), [src/planner/verify.cpp](../../../../../src/planner/verify.cpp), [docs/candidate_alternatives.md](../../../../candidate_alternatives.md) |

## B0025

[Lines 130–130](../../../../../src/planner/candidates.cpp#L130); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
const ValidationReport& MinimumHeightCandidate::validation()
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Observe the completed independent upper report. |
| inputs / outputs | Const ValidationReport& already owned by CheckedUpper. |
| invariants | Does not allocate a new report or manufacture fresh authority. |
| ownership | Borrow tied to checked upper owner. |
| failure | Moved-from handle rejects; private payload guarantees nonnull report. |
| cost | Constant access, no report copy. |
| Design | [include/crown/planner/candidates.hpp](../../../../../include/crown/planner/candidates.hpp), [src/planner/verify.cpp](../../../../../src/planner/verify.cpp) |

## B0026

[Lines 131–131](../../../../../src/planner/candidates.cpp#L131); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::size_t MinimumHeightCandidate::height()
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Read measured native height of accepted upper. |
| inputs / outputs | size_t from CheckedUpper. |
| invariants | Publication gate matched this value to supplied original optimum; no enumeration inference. |
| ownership | Scalar copy. |
| failure | Moved-from rejects. |
| cost | Constant-time. |
| Design | [include/crown/planner/candidates.hpp](../../../../../include/crown/planner/candidates.hpp), [docs/candidate_alternatives.md](../../../../candidate_alternatives.md) |

## B0027

[Lines 132–132](../../../../../src/planner/candidates.cpp#L132); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
const std::string& MinimumHeightCandidate::structural_key()
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Read complete checked-tree identity bytes in this binding/context namespace. |
| inputs / outputs | Const string& retained by payload. |
| invariants | Key alone is not global query identity, proof or cost evidence. |
| ownership | Borrow from immutable shared key owner. |
| failure | Moved-from rejects. |
| cost | Constant getter; callers comparing/copying bytes pay their width. |
| Design | [include/crown/planner/candidates.hpp](../../../../../include/crown/planner/candidates.hpp), [src/planner/candidate_key.hpp](../../../../../src/planner/candidate_key.hpp), [docs/candidate_alternatives.md](../../../../candidate_alternatives.md) |

## B0028

[Lines 133–133](../../../../../src/planner/candidates.cpp#L133); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
const CandidateContext& MinimumHeightCandidate::context()
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Read supported identity namespace for this candidate. |
| inputs / outputs | Const CandidateContext&. |
| invariants | All context fields participated in admission/reuse fences. |
| ownership | Borrow into shared InputData. |
| failure | Moved-from rejects. |
| cost | Constant access; no string copy. |
| Design | [include/crown/planner/candidates.hpp](../../../../../include/crown/planner/candidates.hpp), [docs/candidate_alternatives.md](../../../../candidate_alternatives.md) |

## B0029

[Lines 134–134](../../../../../src/planner/candidates.cpp#L134); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
CandidateProvenance MinimumHeightCandidate::provenance()
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Copy original generation provenance for reporting/cache reuse. |
| inputs / outputs | CandidateProvenance value. |
| invariants | Cached candidates preserve this provenance while owning the new provider proof. |
| ownership | Copies scalar fields and optional owning trace handle. |
| failure | Moved-from rejects; successful copy allocates no payload. |
| cost | Constant-time shared-handle/value copy. |
| Design | [include/crown/planner/candidates.hpp](../../../../../include/crown/planner/candidates.hpp), [docs/candidate_alternatives.md](../../../../candidate_alternatives.md) |

## B0030

[Lines 135–135](../../../../../src/planner/candidates.cpp#L135); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
VerifiedOptimum MinimumHeightCandidate::original_proof()
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Return unchanged original-query lower+upper authority. |
| inputs / outputs | Owning VerifiedOptimum copy. |
| invariants | Certificate retains its original witness; alternative tree is never substituted. |
| ownership | Returned handle retains proof/binding beyond candidate/provider lifetime. |
| failure | Moved-from rejects; shared handle copy does not allocate. |
| cost | Constant-time. |
| Design | [include/crown/planner/candidates.hpp](../../../../../include/crown/planner/candidates.hpp), [include/crown/planner/search.hpp](../../../../../include/crown/planner/search.hpp), [docs/candidate_alternatives.md](../../../../candidate_alternatives.md) |

## B0031

[Lines 136–137](../../../../../src/planner/candidates.cpp#L136); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
CandidateSnapshot::CandidateSnapshot(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Adopt a prepared immutable snapshot. |
| inputs / outputs | Shared SnapshotData into private handle. |
| invariants | Factory call follows complete input/vector preparation; no live cursor is borrowed. |
| ownership | Moves shared ownership. |
| failure | Noexcept. |
| cost | Constant-time. |
| Design | [include/crown/planner/candidates.hpp](../../../../../include/crown/planner/candidates.hpp) |

## B0032

[Lines 138–138](../../../../../src/planner/candidates.cpp#L138); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
bool CandidateSnapshot::valid()
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Detect moved-from snapshots. |
| inputs / outputs | Boolean payload presence. |
| invariants | Does not claim family completion or create authority. |
| ownership | Reads pointer only. |
| failure | Noexcept. |
| cost | Constant-time. |
| Design | [include/crown/planner/candidates.hpp](../../../../../include/crown/planner/candidates.hpp) |

## B0033

[Lines 139–139](../../../../../src/planner/candidates.cpp#L139); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::size_t CandidateSnapshot::candidate_count()
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Read retained prefix length. |
| inputs / outputs | Vector size. |
| invariants | Count is distinct from exhaustion or globally complete search. |
| ownership | Scalar copy from immutable snapshot. |
| failure | Moved-from rejects. |
| cost | Constant-time. |
| Design | [include/crown/planner/candidates.hpp](../../../../../include/crown/planner/candidates.hpp), [docs/candidate_alternatives.md](../../../../candidate_alternatives.md) |

## B0034

[Lines 140–144](../../../../../src/planner/candidates.cpp#L140); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::optional<MinimumHeightCandidate> CandidateSnapshot::candidate(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Copy one retained checked candidate by prefix index. |
| inputs / outputs | Index; owning optional candidate or empty if out of range. |
| invariants | Vector element itself is never exposed by reference or iterator. |
| ownership | Returned shared handle survives snapshot release. |
| failure | Moved-from snapshot rejects; bad index is ordinary absence. |
| cost | Constant handle copy; no allocation. |
| Design | [include/crown/planner/candidates.hpp](../../../../../include/crown/planner/candidates.hpp), [docs/candidate_alternatives.md](../../../../candidate_alternatives.md) |

## B0035

[Lines 145–145](../../../../../src/planner/candidates.cpp#L145); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
bool CandidateSnapshot::family_exhausted()
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Read the actual completion flag captured from its provider. |
| inputs / outputs | Boolean. |
| invariants | Completion covers only the family retained in this snapshot: consumed proposals or admitted seeds plus normal form. Cached-prefix reuse never transplants its cursor or completion. |
| ownership | Scalar copy. |
| failure | Moved-from rejects. |
| cost | Constant-time. |
| Design | [include/crown/planner/candidates.hpp](../../../../../include/crown/planner/candidates.hpp), [docs/candidate_alternatives.md](../../../../candidate_alternatives.md), [docs/meta_decompositions.md](../../../../meta_decompositions.md) |

## B0036

[Lines 146–148](../../../../../src/planner/candidates.cpp#L146); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
CandidateFamily CandidateSnapshot::family()
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Name the supported family for a valid snapshot. |
| inputs / outputs | Return the stored immutable family after the handle guard. |
| invariants | No caller-supplied family flag is trusted. |
| ownership | Scalar return. |
| failure | A moved-from snapshot rejects; there is no hard-coded normal-form fallback. |
| cost | Constant-time. |
| Design | [include/crown/planner/candidates.hpp](../../../../../include/crown/planner/candidates.hpp), [docs/candidate_alternatives.md](../../../../candidate_alternatives.md), [docs/meta_decompositions.md](../../../../meta_decompositions.md) |

## B0037

[Lines 149–149](../../../../../src/planner/candidates.cpp#L149); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
const CandidateContext& CandidateSnapshot::context()
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Borrow immutable snapshot namespace. |
| inputs / outputs | Const context reference from shared input. |
| invariants | Matches original proof binding/context used by retained candidates. |
| ownership | Borrow requires retained snapshot/input owner. |
| failure | Moved-from rejects. |
| cost | Constant getter, no string copy. |
| Design | [include/crown/planner/candidates.hpp](../../../../../include/crown/planner/candidates.hpp) |

## B0038

[Lines 150–150](../../../../../src/planner/candidates.cpp#L150); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
VerifiedOptimum CandidateSnapshot::original_proof()
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Copy the supplied original optimum retained by the snapshot. |
| inputs / outputs | VerifiedOptimum handle. |
| invariants | Independent of prefix length/completion and unchanged original certificate witness. |
| ownership | Owning shared proof copy. |
| failure | Moved-from rejects; successful copy nonallocating. |
| cost | Constant-time. |
| Design | [include/crown/planner/candidates.hpp](../../../../../include/crown/planner/candidates.hpp), [include/crown/planner/search.hpp](../../../../../include/crown/planner/search.hpp), [docs/candidate_alternatives.md](../../../../candidate_alternatives.md) |

## B0039

[Lines 151–161](../../../../../src/planner/candidates.cpp#L151); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct CandidateProvider::Impl {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Own saved seed/generation/validation/key/publication stages and avoid snapshot ownership chains. |
| inputs / outputs | Shared immutable input; optional residual/prefix holders, shared content budget, ledger, published vector/seen set/reuse diagnostics and active workers/draft/payload. |
| invariants | Input/candidate payload never contains live seed/prefix holders. Draft upper/key/payload remains private until atomic publication; seen stores full keys independently of vector addresses. The proposal route owns its finite input vector and index, with the actual family retained separately; unpublished input never enters a candidate payload. |
| ownership | Unique pimpl owns workers; immutable publications share input/upper/key. Public API copies vector elements; no published element borrow/iterator is retained across reserve. |
| failure | Resource/allocation failures retain stage/pending worker. Internal contradictions terminalize with existing published handles intact. |
| cost | Retained candidates/keys/proof plus workers/scratch; full-key ordering, vector reserve relocation and cleanup have variable cost. |
| Design | [include/crown/planner/candidates.hpp](../../../../../include/crown/planner/candidates.hpp), [docs/candidate_alternatives.md](../../../../candidate_alternatives.md), [src/planner/candidate_key.hpp](../../../../../src/planner/candidate_key.hpp), [src/planner/verify.cpp](../../../../../src/planner/verify.cpp), [src/planner/producer_cursor.hpp](../../../../../src/planner/producer_cursor.hpp), [docs/meta_decompositions.md](../../../../meta_decompositions.md) |

## B0040

[Lines 162–166](../../../../../src/planner/candidates.cpp#L162); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
  enum class Stage {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Drive retained provider operations through explicit publication states. |
| inputs / outputs | Seed/generator/proposal/P02/height/key/dedup/reserve/payload/publish/release and terminals. proposals denotes finite batch admission before the shared validation stages. |
| invariants | reserve/payload complete before seen insertion; no allocation follows successful membership commit. |
| ownership | Scalar in exclusive Impl. |
| failure | Private invalid stage execution throws internal_failure. |
| cost | Constant dispatch state. |
| Design | [docs/candidate_alternatives.md](../../../../candidate_alternatives.md), [docs/meta_decompositions.md](../../../../meta_decompositions.md) |

## B0041

[Lines 167–167](../../../../../src/planner/candidates.cpp#L167); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
  enum class Origin {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Remember which seed/generator cursor to advance after a gate result. |
| inputs / outputs | exact/residual/cache/generated. proposal advances only the finite batch index after releasing the current draft. |
| invariants | Separate from public primary provenance, which survives cached reuse. |
| ownership | Scalar owned by Impl. |
| failure | No exception/validation in enum. |
| cost | Constant storage. |
| Design | [docs/candidate_alternatives.md](../../../../candidate_alternatives.md), [docs/meta_decompositions.md](../../../../meta_decompositions.md) |

## B0042

[Lines 168–169](../../../../../src/planner/candidates.cpp#L168); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L168-L169:sha256:c4af25e1b3f47a9b06215939ad3f724aa9ecc10a39cbaf7ae2002f25a61d0dc1
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Use the adjacent note for KeyLess: Ordered dedup uses complete string bytes: O(key width) per comparison, repeated logarithmically by the set; pointer/digest equality is insufficient. Confirm behavior against the declaration and implementation; comment text alone does not enforce or prove it. |
| inputs / outputs | This comment has no inputs or outputs. It accompanies KeyLess; use the adjacent declaration and implementation for the actual values and result. |
| invariants | This is static guidance only. The comment cannot alter state or guarantee that its wording holds. |
| ownership | The note owns no storage and changes no lifetime; ownership and borrowing for KeyLess come from its actual types and implementation. |
| failure | Reading the comment has no runtime failure path. Compile or link errors, exceptions, and resource stops belong to the adjacent code. |
| cost | The comment adds no runtime instructions, allocation, clock read, counter debit, or engine hook; only source-text processing is added. |
| Design | [src/planner/candidates.cpp](../../../../../src/planner/candidates.cpp), [docs/planner_proofs.md](../../../../planner_proofs.md), [docs/residual_candidates.md](../../../../residual_candidates.md), [docs/planner_continuations.md](../../../../planner_continuations.md) |

## B0043

[Lines 170–175](../../../../../src/planner/candidates.cpp#L170); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
  struct KeyLess {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Order dedup keys by complete structural bytes. |
| inputs / outputs | Two shared nonnull strings; lexicographic Boolean. |
| invariants | Compares full content, never pointer address or digest. Tree input was P02-checked before key construction. |
| ownership | Borrows pointed strings during comparison; set owns shared keys. |
| failure | Noexcept; private callers guarantee nonnull keys. |
| cost | Variable-width string comparison, repeated O(log C) times per set lookup/insert. |
| Design | [src/planner/candidate_key.hpp](../../../../../src/planner/candidate_key.hpp), [docs/candidate_alternatives.md](../../../../candidate_alternatives.md) |

## B0044

[Lines 176–207](../../../../../src/planner/candidates.cpp#L176); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
  std::shared_ptr<const cand::InputData> input;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Retain provider fields that separate immutable input/publications from temporary seed/worker ownership. |
| inputs / outputs | Input, residual/prefix, budgets/stage/stats, published/seen/reuse, active workers and private pending payload. |
| invariants | Published vector elements are shared handles returned by value. No worker stores pointers/references/iterators to vector elements, so reserve relocation preserves semantic owners. |
| ownership | Impl owns mutable state; immutable payloads exclude residual/prefix holders and reference input/checked tree/key directly. The owning proposal vector is facade scratch, excluded from immutable InputData; published tree owners do not retain the whole vector. |
| failure | Field teardown allocates no diagnostics; cancellation releases workers/holders but retains published vector and seen/reuse history. |
| cost | Storage includes duplicate validation/key scratch and seed prefix until release/destruction; vector capacity and key widths are outside logical cell ceilings. Caller-supplied batch storage is a separate admission cost outside content grants. |
| Design | [include/crown/planner/candidates.hpp](../../../../../include/crown/planner/candidates.hpp), [docs/candidate_alternatives.md](../../../../candidate_alternatives.md), [src/planner/candidate_machine.hpp](../../../../../src/planner/candidate_machine.hpp), [src/planner/candidate_key.hpp](../../../../../src/planner/candidate_key.hpp), [docs/meta_decompositions.md](../../../../meta_decompositions.md) |

## B0045

[Lines 208–212](../../../../../src/planner/candidates.cpp#L208); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
  Impl(std::shared_ptr<const cand::InputData> in,
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Initialize inert provider ledger/budget and owning seed holders. |
| inputs / outputs | Input, limits, optional residual shared owner and snapshot moved into fields. |
| invariants | No P02/generation/key computation runs during construction. |
| ownership | Owns shared content budget and moved immutable inputs/seeds. |
| failure | Budget allocation may throw before facade publication. |
| cost | Constant shell work, one budget allocation. |
| Design | [include/crown/planner/candidates.hpp](../../../../../include/crown/planner/candidates.hpp), [docs/candidate_alternatives.md](../../../../candidate_alternatives.md), [src/planner/candidate_machine.hpp](../../../../../src/planner/candidate_machine.hpp) |

## B0046

[Lines 213–215](../../../../../src/planner/candidates.cpp#L213); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
  bool terminal() const noexcept
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Recognize exhausted/failed/cancelled owners. |
| inputs / outputs | Boolean over three stage values. |
| invariants | Candidate/capacity/resource stops remain resumable. |
| ownership | Reads scalar stage. |
| failure | Noexcept. |
| cost | Constant-time. |
| Design | [include/crown/planner/candidates.hpp](../../../../../include/crown/planner/candidates.hpp), [docs/candidate_alternatives.md](../../../../candidate_alternatives.md) |

## B0047

[Lines 216–219](../../../../../src/planner/candidates.cpp#L216); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
  CandidateStop terminal_reason() const noexcept
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Choose stable terminal stop. |
| inputs / outputs | exhausted/cancelled or retained failure. |
| invariants | Caller invokes only after terminal(). |
| ownership | Scalar return. |
| failure | Noexcept. |
| cost | Constant-time. |
| Design | [include/crown/planner/candidates.hpp](../../../../../include/crown/planner/candidates.hpp) |

## B0048

[Lines 220–220](../../../../../src/planner/candidates.cpp#L220); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
  void fail(CandidateStop r) noexcept
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Make an internal contradiction or logical exhaustion terminal. |
| inputs / outputs | Sets failed stage and retained reason. |
| invariants | Existing original proof/candidates remain valid; failure is not query infeasibility. |
| ownership | Does not release payloads/workers here. |
| failure | Noexcept assignment. |
| cost | Constant-time. |
| Design | [docs/candidate_alternatives.md](../../../../candidate_alternatives.md), [include/crown/planner/candidates.hpp](../../../../../include/crown/planner/candidates.hpp) |

## B0049

[Lines 221–226](../../../../../src/planner/candidates.cpp#L221); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
  std::size_t depth() const noexcept
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Sample only the worker active in the current stage. |
| inputs / outputs | P02/key/generator depth or zero elsewhere. |
| invariants | Unrelated suspended generator and blocked requested pushes are excluded. |
| ownership | Borrowed worker calls yield scalar depth. |
| failure | Noexcept. |
| cost | Constant dispatch/getters. |
| Design | [docs/candidate_alternatives.md](../../../../candidate_alternatives.md), [src/planner/candidate_machine.hpp](../../../../../src/planner/candidate_machine.hpp), [src/planner/candidate_key.hpp](../../../../../src/planner/candidate_key.hpp) |

## B0050

[Lines 227–244](../../../../../src/planner/candidates.cpp#L227); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
  CandidatePhase phase() const noexcept
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Map private stage to observable activity. |
| inputs / outputs | Seed/enumerate/validate/canonicalize/publish/terminal phase. The proposal-input stage reports enumerate. |
| invariants | Completion only follows actual generator exhausted event; proof height already known independently. |
| ownership | Scalar result. |
| failure | Noexcept fallback failed for unreachable state. |
| cost | Constant dispatch. |
| Design | [include/crown/planner/candidates.hpp](../../../../../include/crown/planner/candidates.hpp), [docs/candidate_alternatives.md](../../../../candidate_alternatives.md), [docs/meta_decompositions.md](../../../../meta_decompositions.md) |

## B0051

[Lines 245–247](../../../../../src/planner/candidates.cpp#L245); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
  void outcome(cand::ReuseOutcome o) noexcept
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Update the diagnostic for the currently replayed cache entry. |
| inputs / outputs | If reuse_pos exists, assigns its outcome. |
| invariants | Index was recorded after successful reuse append and stays valid across vector relocations. |
| ownership | Stores numeric index rather than element reference. |
| failure | Noexcept; private cursor invariant ensures bounds. |
| cost | Constant vector indexing. |
| Design | [docs/candidate_alternatives.md](../../../../candidate_alternatives.md) |

## B0052

[Lines 248–249](../../../../../src/planner/candidates.cpp#L248); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L248-L249:sha256:0b41d76cb0bcb7ad7d559a14399b201932b62b0974d4946ba5316a88e5ff8ef9
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Use the adjacent note for discard: Drop temporary gate owners only. Published handles, seen membership and reuse history stay valid; releasing the last worker/tree/key can be costly. Confirm behavior against the declaration and implementation; comment text alone does not enforce or prove it. |
| inputs / outputs | This comment has no inputs or outputs. It accompanies discard; use the adjacent declaration and implementation for the actual values and result. |
| invariants | This is static guidance only. The comment cannot alter state or guarantee that its wording holds. |
| ownership | The note owns no storage and changes no lifetime; ownership and borrowing for discard come from its actual types and implementation. |
| failure | Reading the comment has no runtime failure path. Compile or link errors, exceptions, and resource stops belong to the adjacent code. |
| cost | The comment adds no runtime instructions, allocation, clock read, counter debit, or engine hook; only source-text processing is added. |
| Design | [src/planner/candidates.cpp](../../../../../src/planner/candidates.cpp), [docs/planner_proofs.md](../../../../planner_proofs.md), [docs/residual_candidates.md](../../../../residual_candidates.md), [docs/planner_continuations.md](../../../../planner_continuations.md) |

## B0053

[Lines 250–254](../../../../../src/planner/candidates.cpp#L250); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
  void discard() noexcept
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Release unpublished gate state after rejection/duplicate/publication. |
| inputs / outputs | Resets private payload/key/upper/draft/key/P02 workers/reuse position/provenance. |
| invariants | Published vector/seen membership/reuse history remain. Logical content is never refunded. |
| ownership | Releases temporary shared owners; accepted candidate independently retains tree/key/input. |
| failure | Noexcept with current standard members; no diagnostic or callback allocation. |
| cost | Size-dependent worker/key/tree cleanup may occur inside one release stage. |
| Design | [docs/candidate_alternatives.md](../../../../candidate_alternatives.md), [src/planner/candidate_key.hpp](../../../../../src/planner/candidate_key.hpp), [src/planner/verify.cpp](../../../../../src/planner/verify.cpp), [src/planner/producer_cursor.hpp](../../../../../src/planner/producer_cursor.hpp) |

## B0054

[Lines 255–257](../../../../../src/planner/candidates.cpp#L255); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L255-L257:sha256:4c0955fe999866b2e867bda806372c40370958d1e7d4efd48af637b5a696ced0
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Use the adjacent note for unit: One retained stage/child step. Every source re-enters original P02/height/ key gates. The supplied proof remains unchanged. Reserve output capacity and prepare payload before seen insertion; no allocation follows its commit. Confirm behavior against the declaration and implementation; comment text alone does not enforce or prove it. |
| inputs / outputs | This comment has no inputs or outputs. It accompanies unit; use the adjacent declaration and implementation for the actual values and result. |
| invariants | This is static guidance only. The comment cannot alter state or guarantee that its wording holds. |
| ownership | The note owns no storage and changes no lifetime; ownership and borrowing for unit come from its actual types and implementation. |
| failure | Reading the comment has no runtime failure path. Compile or link errors, exceptions, and resource stops belong to the adjacent code. |
| cost | The comment adds no runtime instructions, allocation, clock read, counter debit, or engine hook; only source-text processing is added. |
| Design | [src/planner/candidates.cpp](../../../../../src/planner/candidates.cpp), [docs/planner_proofs.md](../../../../planner_proofs.md), [docs/residual_candidates.md](../../../../residual_candidates.md), [docs/planner_continuations.md](../../../../planner_continuations.md) |

## B0055

[Lines 258–434](../../../../../src/planner/candidates.cpp#L258); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
  CandidateStop unit() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Perform one saved facade stage or delegated generator/P02/key operation. |
| inputs / outputs | Uses limits/context and returns none, candidate_ready or resource stop. |
| invariants | All seeds recheck original P02, reject taller, fail below proved minimum, recanonicalize/dedup full keys. Reserve vector and payload before seen insertion; publication then has no throwing allocation. Cache retains provenance but new input proof. Supplied proposals allocate their independent owner before moving the draft; failed allocation leaves the same vector entry intact. Invalid untrusted drafts discard; release advances exactly one batch position; only input exhaustion marks this family complete. |
| ownership | Draft aliases retain seed/proof owners; generated/cached trees shared independently. New CandidateData owns input/upper/key without seed/snapshot chains. |
| failure | Limits preserve stage; invalid seeded uppers/binding/proof-height contradictions fail. Generation rejects ordinary invalid proposals. Allocation before membership commit leaves candidate pending. |
| cost | Full-key set operations have variable-width comparisons. Geometric vector growth gives amortized constant handle relocation per publication, but an individual reserve remains linear and can allocate spare capacity. P02/key generation is saved; seed identity admission is outside this method; release cleanup is variable. Content counters do not cap allocator bytes or elapsed time. Each proposal owner spends one logical record; vector admission/storage and P02 scratch remain explicitly outside these construction charges. |
| Design | [docs/candidate_alternatives.md](../../../../candidate_alternatives.md), [include/crown/planner/candidates.hpp](../../../../../include/crown/planner/candidates.hpp), [src/planner/candidate_machine.hpp](../../../../../src/planner/candidate_machine.hpp), [src/planner/candidate_key.hpp](../../../../../src/planner/candidate_key.hpp), [src/planner/verify.cpp](../../../../../src/planner/verify.cpp), [docs/planner_proofs.md](../../../../planner_proofs.md), [docs/meta_decompositions.md](../../../../meta_decompositions.md) |

## B0056

[Lines 435–435](../../../../../src/planner/candidates.cpp#L435); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L435-L435:sha256:aa1d1a63390229c798347e83a0405441c9400035284ad168c1bf6cdf1d70a370
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | This block close the current class or struct and its enclosing lexical scope. |
| inputs / outputs | A scope delimiter has no call inputs or outputs; it controls which following declarations belong to the C++ namespace, class, or helper scope. |
| invariants | The braces set lexical visibility and type boundaries only. Any attached note is documentation and does not enforce behavior. |
| ownership | The delimiter and note acquire, release, or transfer no runtime object. Member lifetimes come from the enclosed type definitions. |
| failure | An unmatched or misplaced brace fails compilation; this block adds no runtime exception or resource-stop path. |
| cost | No runtime work or allocation is added. The compiler parses the scope boundary and comment. |
| Design | [src/planner/candidates.cpp](../../../../../src/planner/candidates.cpp), [docs/planner_proofs.md](../../../../planner_proofs.md), [docs/residual_candidates.md](../../../../residual_candidates.md), [docs/planner_continuations.md](../../../../planner_continuations.md) |

## B0057

[Lines 436–436](../../../../../src/planner/candidates.cpp#L436); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
CandidateProvider::CandidateProvider(std::unique_ptr<Impl> p)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Adopt a prepared exclusive provider implementation. |
| inputs / outputs | Unique Impl pointer moved into private facade. |
| invariants | create performs all input admission first. |
| ownership | Moves unique ownership. |
| failure | Noexcept. |
| cost | Constant-time. |
| Design | [include/crown/planner/candidates.hpp](../../../../../include/crown/planner/candidates.hpp) |

## B0058

[Lines 437–442](../../../../../src/planner/candidates.cpp#L437); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
CandidateProvider::~CandidateProvider() = default;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Implement provider unique ownership moves and final cleanup. |
| inputs / outputs | Default destructor/move constructor/move assignment. |
| invariants | Moved-from facade data_ is null; public returned handles retain independent immutable owners. |
| ownership | Moves unique Impl; target replacement/final destruction releases all workers and retained containers. |
| failure | Noexcept moves; generator/key destructors cancel active frames. |
| cost | Move construction constant; destruction/replaced target cleanup proportional to retained state, outside advance grants. |
| Design | [include/crown/planner/candidates.hpp](../../../../../include/crown/planner/candidates.hpp), [docs/candidate_alternatives.md](../../../../candidate_alternatives.md), [src/planner/producer_cursor.hpp](../../../../../src/planner/producer_cursor.hpp) |

## B0059

[Lines 443–467](../../../../../src/planner/candidates.cpp#L443); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
CandidateProvider CandidateProvider::create(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Admit exact original proof/context/binding and optional seed prefix without enumeration. |
| inputs / outputs | VerifiedOptimum by value plus context/limits/residual/snapshot; move-only provider out. |
| invariants | Valid proof and supported context required. Residual full binding bytes must match; prefix binding/context/height match. Current provider proof is retained independently of prior cache proof/completion. A cached prefix must have the original normal-form family as well as exact binding/context/height. |
| ownership | Copies full Catalog/Query into separate immutable binding, stores full bytes/context/proof, holds optional seeds privately. |
| failure | Invalid handles/context/time/binding reject; ordinary allocations/encoding can throw before any provider exists. |
| cost | Whole binding serialization/comparison and copied source/proof-owner storage outside work/content metering; creates inert pimpl/budget only. |
| Design | [include/crown/planner/candidates.hpp](../../../../../include/crown/planner/candidates.hpp), [docs/candidate_alternatives.md](../../../../candidate_alternatives.md), [src/planner/candidate_binding.hpp](../../../../../src/planner/candidate_binding.hpp), [include/crown/planner/search.hpp](../../../../../include/crown/planner/search.hpp), [docs/meta_decompositions.md](../../../../meta_decompositions.md) |

## B0060

[Lines 468–475](../../../../../src/planner/candidates.cpp#L468); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L468-L475:sha256:e0b30e77dd0505077a4c3b90195e79e0b0d835a5b1052759e5501ff2ec1bc462
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Admit an owned finite unchecked proposal batch without implicit seeds or generation tail. |
| inputs / outputs | Genuine VerifiedOptimum, tree vector, supported context and limits in; exclusive proposal provider out. |
| invariants | Reuse exact source/context admission, then set family and initial proposal stage before publication; no enumeration has run. |
| ownership | The facade owns the moved vector; accepted tree payloads later own individual drafts. |
| failure | Existing admission and owner allocation failures propagate; no partially returned provider exists. |
| cost | Cold proof/binding/context admission plus vector move; upstream batch production/storage is outside advance grants. |
| Design | [docs/candidate_alternatives.md](../../../../candidate_alternatives.md), [docs/meta_decompositions.md](../../../../meta_decompositions.md), [Refactor.md](../../../../../Refactor.md) |

## B0061

[Lines 476–478](../../../../../src/planner/candidates.cpp#L476); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L476-L478:sha256:e24681d7991b14562e4eea9004c8ea6da9bbf88e438a99a2128b4d1d74d36dad
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Use the adjacent note for CandidateProvider: Keep resource/allocation catches: workers retain the same pending operation. Logical counters stop before wrap; final catch protects this noexcept public boundary with terminal internal_failure and no allocated diagnostic message. Confirm behavior against the declaration and implementation; comment text alone does not enforce or prove it. |
| inputs / outputs | This comment has no inputs or outputs. It accompanies CandidateProvider; use the adjacent declaration and implementation for the actual values and result. |
| invariants | This is static guidance only. The comment cannot alter state or guarantee that its wording holds. |
| ownership | The note owns no storage and changes no lifetime; ownership and borrowing for CandidateProvider come from its actual types and implementation. |
| failure | Reading the comment has no runtime failure path. Compile or link errors, exceptions, and resource stops belong to the adjacent code. |
| cost | The comment adds no runtime instructions, allocation, clock read, counter debit, or engine hook; only source-text processing is added. |
| Design | [src/planner/candidates.cpp](../../../../../src/planner/candidates.cpp), [docs/planner_proofs.md](../../../../planner_proofs.md), [docs/residual_candidates.md](../../../../residual_candidates.md), [docs/planner_continuations.md](../../../../planner_continuations.md) |

## B0062

[Lines 479–544](../../../../../src/planner/candidates.cpp#L479); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
CandidateAdvance CandidateProvider::advance(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Spend a cooperative grant and stop at a new publication, resource stop or real exhaustion. |
| inputs / outputs | WorkQuantum in; fixed CandidateAdvance out. |
| invariants | Negative/zero grants return before mutation/clock; attempts charged even on failed transition. Saved closures preserve retry. Original minimum remains unchanged throughout enumeration. |
| ownership | Exclusive mutation of owned stage/workers, with immutable public handles unaffected. |
| failure | Retain ContentStop/Stopped/bad_alloc catches; failure-counter/logic overflow terminalizes. Final catch protects noexcept with internal_failure and no allocated diagnostics. |
| cost | At most quantum work attempts; time checked between units. Whole comparisons/reserve/cleanup can cross a deadline; active clock includes their execution. |
| Design | [docs/candidate_alternatives.md](../../../../candidate_alternatives.md), [include/crown/planner/candidates.hpp](../../../../../include/crown/planner/candidates.hpp), [src/planner/continuation_budget.hpp](../../../../../src/planner/continuation_budget.hpp), [src/planner/producer_cursor.hpp](../../../../../src/planner/producer_cursor.hpp), [src/planner/candidate_machine.hpp](../../../../../src/planner/candidate_machine.hpp), [src/planner/candidate_key.hpp](../../../../../src/planner/candidate_key.hpp) |

## B0063

[Lines 545–554](../../../../../src/planner/candidates.cpp#L545); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
CandidateProgress CandidateProvider::progress()
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Assemble allocation-free diagnostics from retained counters/state. |
| inputs / outputs | Moved-from marker or current original height, exhaustion, work/content/stats/count. Reports the actual provider family, including finite batches. |
| invariants | Height is supplied proof result; only family_complete reflects natural exhaustion. Snapshot cannot create authority. |
| ownership | Fixed scalar/optional copy. |
| failure | Noexcept. |
| cost | Constant-time field copies/getters. |
| Design | [include/crown/planner/candidates.hpp](../../../../../include/crown/planner/candidates.hpp), [docs/candidate_alternatives.md](../../../../candidate_alternatives.md), [docs/meta_decompositions.md](../../../../meta_decompositions.md) |

## B0064

[Lines 555–555](../../../../../src/planner/candidates.cpp#L555); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::size_t CandidateProvider::candidate_count()
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Read currently published alternative count. |
| inputs / outputs | Vector size or zero for moved-from. |
| invariants | Does not count pending payload/dedup key. |
| ownership | Scalar copy. |
| failure | Noexcept. |
| cost | Constant-time. |
| Design | [include/crown/planner/candidates.hpp](../../../../../include/crown/planner/candidates.hpp) |

## B0065

[Lines 556–557](../../../../../src/planner/candidates.cpp#L556); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L556-L557:sha256:a4c1b45e762ab7b82a27945c44793d9a286bd3c06782c8a0d31deedaac494344
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Use the adjacent note for CandidateProvider: Return an owning value, never a vector element borrow. Tree/key/report owners are independent of published-vector relocation during capacity preparation. Confirm behavior against the declaration and implementation; comment text alone does not enforce or prove it. |
| inputs / outputs | This comment has no inputs or outputs. It accompanies CandidateProvider; use the adjacent declaration and implementation for the actual values and result. |
| invariants | This is static guidance only. The comment cannot alter state or guarantee that its wording holds. |
| ownership | The note owns no storage and changes no lifetime; ownership and borrowing for CandidateProvider come from its actual types and implementation. |
| failure | Reading the comment has no runtime failure path. Compile or link errors, exceptions, and resource stops belong to the adjacent code. |
| cost | The comment adds no runtime instructions, allocation, clock read, counter debit, or engine hook; only source-text processing is added. |
| Design | [src/planner/candidates.cpp](../../../../../src/planner/candidates.cpp), [docs/planner_proofs.md](../../../../planner_proofs.md), [docs/residual_candidates.md](../../../../residual_candidates.md), [docs/planner_continuations.md](../../../../planner_continuations.md) |

## B0066

[Lines 558–561](../../../../../src/planner/candidates.cpp#L558); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::optional<MinimumHeightCandidate> CandidateProvider::candidate(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Copy one accepted candidate by index. |
| inputs / outputs | Optional handle or empty on moved-from/out of range. |
| invariants | Returns no element reference/iterator; reserve can relocate internal handles safely. |
| ownership | Copy retains immutable input/tree/key/proof beyond provider lifetime. |
| failure | Noexcept and nonallocating. |
| cost | Constant handle copy. |
| Design | [include/crown/planner/candidates.hpp](../../../../../include/crown/planner/candidates.hpp), [docs/candidate_alternatives.md](../../../../candidate_alternatives.md) |

## B0067

[Lines 562–565](../../../../../src/planner/candidates.cpp#L562); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
VerifiedOptimum CandidateProvider::original_proof()
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Return the originally supplied proof unchanged. |
| inputs / outputs | Owning VerifiedOptimum copy. |
| invariants | Proof known before enumeration and independent of count/exhaustion; original witness preserved. |
| ownership | Shared owner copy. |
| failure | Moved-from provider throws invalid_candidate_provider. |
| cost | Constant-time successful copy. |
| Design | [include/crown/planner/candidates.hpp](../../../../../include/crown/planner/candidates.hpp), [include/crown/planner/search.hpp](../../../../../include/crown/planner/search.hpp), [docs/candidate_alternatives.md](../../../../candidate_alternatives.md) |

## B0068

[Lines 566–569](../../../../../src/planner/candidates.cpp#L566); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
const CandidateContext& CandidateProvider::context()
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Borrow provider semantic/version namespace. |
| inputs / outputs | Const context reference. |
| invariants | Immutable after admission; limit raises do not change identity. |
| ownership | Borrow into retained InputData. |
| failure | Moved-from rejects. |
| cost | Constant no-copy access. |
| Design | [include/crown/planner/candidates.hpp](../../../../../include/crown/planner/candidates.hpp) |

## B0069

[Lines 570–573](../../../../../src/planner/candidates.cpp#L570); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
CandidateLimits CandidateProvider::limits()
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Copy current accepted provider ceilings. |
| inputs / outputs | CandidateLimits value. |
| invariants | Consumed counters never reset by a limit extension. |
| ownership | Fixed value copy. |
| failure | Moved-from rejects. |
| cost | Constant-time. |
| Design | [include/crown/planner/candidates.hpp](../../../../../include/crown/planner/candidates.hpp) |

## B0070

[Lines 574–592](../../../../../src/planner/candidates.cpp#L574); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
LimitChange CandidateProvider::raise_limits(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Apply monotone work/time/depth/content/count extension to the same cursor. |
| inputs / outputs | CandidateLimits in; LimitChange out. |
| invariants | Reject terminal/tightened/below-consumed limits before mutation. Budget raises and ledger/options update preserve all retained work. |
| ownership | Mutates limits/budget/ledger/revision only. |
| failure | Noexcept; revision exhaustion terminalizes counter_overflow. Invalid budget raise returns invalid. |
| cost | Constant arithmetic/optional checks, no restart or allocation. |
| Design | [include/crown/planner/candidates.hpp](../../../../../include/crown/planner/candidates.hpp), [docs/candidate_alternatives.md](../../../../candidate_alternatives.md), [src/planner/continuation_budget.hpp](../../../../../src/planner/continuation_budget.hpp), [src/planner/candidate_machine.hpp](../../../../../src/planner/candidate_machine.hpp) |

## B0071

[Lines 593–601](../../../../../src/planner/candidates.cpp#L593); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void CandidateProvider::cancel()
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Release unfinished workers/seeds while preserving published alternatives and diagnostics. |
| inputs / outputs | No-op on moved-from/terminal; cancels generator/key, discards gate state, releases prefix/residual, sets depth0/cancelled. |
| invariants | Exhausted/failed cancellation is inert. Published candidate proof/data remain valid; cancellation does not mark family exhausted. |
| ownership | Releases temporary workers/holders, retains input/published/seen/reuse/statistics. Nonterminal cancellation also swaps out unpublished proposal vector storage. |
| failure | Noexcept; no new allocation. |
| cost | Cleanup proportional to unfinished state; outside per-call work accounting. |
| Design | [include/crown/planner/candidates.hpp](../../../../../include/crown/planner/candidates.hpp), [docs/candidate_alternatives.md](../../../../candidate_alternatives.md), [src/planner/producer_cursor.hpp](../../../../../src/planner/producer_cursor.hpp), [docs/meta_decompositions.md](../../../../meta_decompositions.md) |

## B0072

[Lines 602–603](../../../../../src/planner/candidates.cpp#L602); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L602-L603:sha256:1fe1c7020186dbb42ba5cb5534c01b4f0d9cbf3bc2702d2549b5c23615bc880b
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Use the adjacent note for CandidateProvider: Explicit allocating admission outside work/content grants. Vector-copy failure leaves provider and all earlier snapshots/candidates unchanged. Confirm behavior against the declaration and implementation; comment text alone does not enforce or prove it. |
| inputs / outputs | This comment has no inputs or outputs. It accompanies CandidateProvider; use the adjacent declaration and implementation for the actual values and result. |
| invariants | This is static guidance only. The comment cannot alter state or guarantee that its wording holds. |
| ownership | The note owns no storage and changes no lifetime; ownership and borrowing for CandidateProvider come from its actual types and implementation. |
| failure | Reading the comment has no runtime failure path. Compile or link errors, exceptions, and resource stops belong to the adjacent code. |
| cost | The comment adds no runtime instructions, allocation, clock read, counter debit, or engine hook; only source-text processing is added. |
| Design | [src/planner/candidates.cpp](../../../../../src/planner/candidates.cpp), [docs/planner_proofs.md](../../../../planner_proofs.md), [docs/residual_candidates.md](../../../../residual_candidates.md), [docs/planner_continuations.md](../../../../planner_continuations.md) |

## B0073

[Lines 604–609](../../../../../src/planner/candidates.cpp#L604); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
CandidateSnapshot CandidateProvider::snapshot()
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Allocate an immutable copy of current checked prefix and actual completion. |
| inputs / outputs | Snapshot of input, published handles, reuse history, actual family_complete and family enum. |
| invariants | No cursor or provider borrow is retained; cache reuse restarts enumeration. |
| ownership | New SnapshotData copies handle/event vectors, shares immutable input/payloads. |
| failure | Moved-from rejects; allocation failure leaves provider unchanged. |
| cost | O(prefix+reuse count) value copies and allocations outside advance quanta/content caps. |
| Design | [include/crown/planner/candidates.hpp](../../../../../include/crown/planner/candidates.hpp), [docs/candidate_alternatives.md](../../../../candidate_alternatives.md), [docs/meta_decompositions.md](../../../../meta_decompositions.md) |

## B0075

[Lines 611–616](../../../../../src/planner/candidates.cpp#L611); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct CandidateCache::Impl {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Own explicit FIFO entry count limit and cumulative cache diagnostics. |
| inputs / outputs | Capacity,list of CandidateSnapshots,stats; constructor stores capacity. |
| invariants | List order changes only on new insertion/eviction; hit/replacement preserve position. |
| ownership | Unique pimpl owns nodes/shared snapshot handles. |
| failure | No source admission in constructor; list node allocation later can throw. |
| cost | O(entries) list storage plus transitively retained snapshots/proofs/trees/keys, not byte-bounded. |
| Design | [include/crown/planner/candidates.hpp](../../../../../include/crown/planner/candidates.hpp), [docs/candidate_alternatives.md](../../../../candidate_alternatives.md) |

## B0076

[Lines 617–617](../../../../../src/planner/candidates.cpp#L617); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
CandidateCache::CandidateCache(std::unique_ptr<Impl> p)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Adopt prepared cache implementation. |
| inputs / outputs | Unique Impl pointer. |
| invariants | Only create allocates a new cache facade. |
| ownership | Moves unique ownership. |
| failure | Noexcept. |
| cost | Constant-time. |
| Design | [include/crown/planner/candidates.hpp](../../../../../include/crown/planner/candidates.hpp) |

## B0077

[Lines 618–620](../../../../../src/planner/candidates.cpp#L618); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
CandidateCache::~CandidateCache() = default;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Implement exclusive cache teardown/moves. |
| inputs / outputs | Default destructor/move constructor/move assignment. |
| invariants | External returned snapshots survive node eviction/destruction. |
| ownership | Moves unique pimpl; replacing/destroying it releases list-held owners. |
| failure | Noexcept moves and standard cleanup. |
| cost | Move construction constant; final/replaced cache cleanup traverses entries and any last-owned payloads. |
| Design | [include/crown/planner/candidates.hpp](../../../../../include/crown/planner/candidates.hpp), [docs/candidate_alternatives.md](../../../../candidate_alternatives.md) |

## B0078

[Lines 621–621](../../../../../src/planner/candidates.cpp#L621); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
CandidateCache CandidateCache::create(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Allocate an empty bounded FIFO cache. |
| inputs / outputs | size_t capacity; move-only cache. |
| invariants | Capacity0 disables installation, but lookup/admission validation still applies. |
| ownership | Unique pimpl with empty list/counters. |
| failure | Shell allocation may throw. |
| cost | One constant-size shell allocation. |
| Design | [include/crown/planner/candidates.hpp](../../../../../include/crown/planner/candidates.hpp), [docs/candidate_alternatives.md](../../../../candidate_alternatives.md) |

## B0079

[Lines 622–623](../../../../../src/planner/candidates.cpp#L622); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L622-L623:sha256:d6147f00f69e410644db2144badbf23dd0434ed98b750d92659a7adc800da8af
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Use the adjacent note for CandidateCache: Full source encoding plus linear FIFO scan; each comparison is variable-width. Hits retain insertion position and return an owning prefix, not gate bypass. Confirm behavior against the declaration and implementation; comment text alone does not enforce or prove it. |
| inputs / outputs | This comment has no inputs or outputs. It accompanies CandidateCache; use the adjacent declaration and implementation for the actual values and result. |
| invariants | This is static guidance only. The comment cannot alter state or guarantee that its wording holds. |
| ownership | The note owns no storage and changes no lifetime; ownership and borrowing for CandidateCache come from its actual types and implementation. |
| failure | Reading the comment has no runtime failure path. Compile or link errors, exceptions, and resource stops belong to the adjacent code. |
| cost | The comment adds no runtime instructions, allocation, clock read, counter debit, or engine hook; only source-text processing is added. |
| Design | [src/planner/candidates.cpp](../../../../../src/planner/candidates.cpp), [docs/planner_proofs.md](../../../../planner_proofs.md), [docs/residual_candidates.md](../../../../residual_candidates.md), [docs/planner_continuations.md](../../../../planner_continuations.md) |

## B0080

[Lines 624–642](../../../../../src/planner/candidates.cpp#L624); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::optional<CandidateSnapshot> CandidateCache::lookup(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Find exact binding/context prefix without moving FIFO order. |
| inputs / outputs | VerifiedOptimum/context; optional owning snapshot. |
| invariants | Re-encodes full source and compares complete bytes/context, then rejects conflicting proved heights. Returned prefix proof is valid historical authority; new provider attaches its own proof after rechecking. |
| ownership | Temporary identity string owned for call; result shares immutable snapshot. |
| failure | Moved-from/invalid proof/context/conflict/counter overflow reject. Encoding/allocation failure leaves entries/order/stats unchanged. |
| cost | Full binding admission encoding plus linear entry scan with variable-width equality; hit/miss increment only after result determination. |
| Design | [include/crown/planner/candidates.hpp](../../../../../include/crown/planner/candidates.hpp), [docs/candidate_alternatives.md](../../../../candidate_alternatives.md), [src/planner/candidate_binding.hpp](../../../../../src/planner/candidate_binding.hpp) |

## B0081

[Lines 643–645](../../../../../src/planner/candidates.cpp#L643); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L643-L645:sha256:dcbd5de249ffee126325a9e72bc5f9fa83803f270476ec53015a5293917d1226
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Use the adjacent note for CandidateCache: Replacement preserves FIFO order. Prepare a new list node before splice and eviction; allocation failure must leave entries, order and counters unchanged. Entry count bounds nodes, not transitive snapshot/proof/tree/key bytes. Confirm behavior against the declaration and implementation; comment text alone does not enforce or prove it. |
| inputs / outputs | This comment has no inputs or outputs. It accompanies CandidateCache; use the adjacent declaration and implementation for the actual values and result. |
| invariants | This is static guidance only. The comment cannot alter state or guarantee that its wording holds. |
| ownership | The note owns no storage and changes no lifetime; ownership and borrowing for CandidateCache come from its actual types and implementation. |
| failure | Reading the comment has no runtime failure path. Compile or link errors, exceptions, and resource stops belong to the adjacent code. |
| cost | The comment adds no runtime instructions, allocation, clock read, counter debit, or engine hook; only source-text processing is added. |
| Design | [src/planner/candidates.cpp](../../../../../src/planner/candidates.cpp), [docs/planner_proofs.md](../../../../planner_proofs.md), [docs/residual_candidates.md](../../../../residual_candidates.md), [docs/planner_continuations.md](../../../../planner_continuations.md) |

## B0082

[Lines 646–675](../../../../../src/planner/candidates.cpp#L646); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
CandidateCacheInstall CandidateCache::install(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Install or replace an immutable prefix with strong allocation-failure preservation. |
| inputs / outputs | Valid CandidateSnapshot; disabled/inserted/replaced. |
| invariants | Even disabled cache requires valid snapshot. Exact binding/context replacement checks equal verified height and preserves FIFO position. New node allocates fully before splice/eviction/counter changes. Reject a finite-proposal snapshot with candidate_binding before capacity or entry mutation, including disabled caches. |
| ownership | List retains shared snapshot owner; evicted payloads may survive caller copies. |
| failure | Invalid handles/conflict/counter/max-size errors throw. bad_alloc before splice preserves old contents/order/counters; no new allocation after splice. |
| cost | Linear exact-byte/context scan; replacement handle move constant plus possible old payload cleanup. New insertion one list node, optional eviction; retained bytes unbounded by entry count. |
| Design | [include/crown/planner/candidates.hpp](../../../../../include/crown/planner/candidates.hpp), [docs/candidate_alternatives.md](../../../../candidate_alternatives.md), [docs/meta_decompositions.md](../../../../meta_decompositions.md) |

## B0083

[Lines 676–679](../../../../../src/planner/candidates.cpp#L676); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
CandidateCacheStatistics CandidateCache::statistics()
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Return cumulative counters and live entry count. |
| inputs / outputs | Default on moved-from; stats copy with entries recomputed from fifo.size(). |
| invariants | Clear preserves activity counters while entry count follows actual list. |
| ownership | Independent scalar value. |
| failure | Noexcept. |
| cost | Constant-time list size/record copy. |
| Design | [include/crown/planner/candidates.hpp](../../../../../include/crown/planner/candidates.hpp) |

## B0084

[Lines 680–680](../../../../../src/planner/candidates.cpp#L680); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void CandidateCache::clear()
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Remove all installed prefixes without resetting activity history. |
| inputs / outputs | No-op moved-from; clears list. |
| invariants | Capacity and cumulative statistics remain; external snapshot/candidate handles stay valid. |
| ownership | Releases list-held shared owners; last-owner payloads may be destroyed. |
| failure | Noexcept standard cleanup; no error allocation. |
| cost | O(entries) node cleanup plus transitive last-owned storage teardown. |
| Design | [include/crown/planner/candidates.hpp](../../../../../include/crown/planner/candidates.hpp), [docs/candidate_alternatives.md](../../../../candidate_alternatives.md) |

## B0085

[Lines 681–681](../../../../../src/planner/candidates.cpp#L681); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L681-L681:sha256:acb95521e5c8cc117a4f60f87ae076d39f48ab1ff02f31d3b8a4ada933fd3da0
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | This block close namespace crown::planner. |
| inputs / outputs | A scope delimiter has no call inputs or outputs; it controls which following declarations belong to the C++ namespace, class, or helper scope. |
| invariants | The braces set lexical visibility and type boundaries only. Any attached note is documentation and does not enforce behavior. |
| ownership | The delimiter and note acquire, release, or transfer no runtime object. Member lifetimes come from the enclosed type definitions. |
| failure | An unmatched or misplaced brace fails compilation; this block adds no runtime exception or resource-stop path. |
| cost | No runtime work or allocation is added. The compiler parses the scope boundary and comment. |
| Design | [src/planner/candidates.cpp](../../../../../src/planner/candidates.cpp), [docs/planner_proofs.md](../../../../planner_proofs.md), [docs/residual_candidates.md](../../../../residual_candidates.md), [docs/planner_continuations.md](../../../../planner_continuations.md) |
