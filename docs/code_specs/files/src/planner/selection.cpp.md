# `src/planner/selection.cpp` — block usage map

[Source](../../../../../src/planner/selection.cpp) · [Source index](../../../README.md) · [Subsystem contracts](../../../subsystem_contracts.md) · [Reviewed primitives](../../../primitives.md)

Rank or select within a checked candidate family using exact binding, explicit evidence and bounded local score policies.

Snapshot SHA-256: `dc9352b8e1aceb1dfef2f50272493f13d3cd99d7c4fec906922d96b83b0b0b3d`. 413 lines partitioned into 56 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [ranking](../../../subsystem_contracts.md#ranking). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/ranking.md](../../../../ranking.md), [docs/selection.md](../../../../selection.md), [docs/selection_binding.md](../../../../selection_binding.md), [docs/ranking_accounting.md](../../../../ranking_accounting.md), [docs/selection_accounting.md](../../../../selection_accounting.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–9](../../../../../src/planner/selection.cpp#L1) | Imports dependencies; declares namespace scope. | growth new; source comment (unverified): // Copy all physical policy text into the receiving account. See docs/selection.md. · [reviewed contract](#b0001) |
| [B0002 · 10–14](../../../../../src/planner/selection.cpp#L10) | Callable definition: CapturedCachePolicy::CapturedCachePolicy(const resource::MemoryAccount& account,const io::CachePolicy& value) :arithmetic(value.a… | calls arithmetic, planner, optimization, cost_model; source comment (unverified): // Copy all physical policy text into the receiving account. See docs/selection.md. · [reviewed contract](#b0002) |
| [B0003 · 15–16](../../../../../src/planner/selection.cpp#L15) | Callable definition: CapturedPhysicalOptions::CapturedPhysicalOptions(const resource::MemoryAccount& account,const PhysicalOptions& value) :policy(acc… | calls policy, limits, indexed_storage · [reviewed contract](#b0003) |
| [B0004 · 17–17](../../../../../src/planner/selection.cpp#L17) | Explanatory comments or spacing. | source comment (unverified): // Capture an admitted request with native slot-cap text. See docs/selection.md. · [reviewed contract](#b0004) |
| [B0005 · 18–25](../../../../../src/planner/selection.cpp#L18) | Callable definition: CapturedRequest::CapturedRequest(const resource::MemoryAccount& account,const Request& value) :policy(value.policy),fallback(valu… | calls policy, fallback, family, layout; growth copy_of; source comment (unverified): // Capture an admitted request with native slot-cap text. See docs/selection.md. · [reviewed contract](#b0005) |
| [B0006 · 26–26](../../../../../src/planner/selection.cpp#L26) | Callable definition: const CandidateSnapshot& Selection::snapshot() const noexcept | calls ; returns data_-&gt;snapshot · [reviewed contract](#b0006) |
| [B0007 · 27–27](../../../../../src/planner/selection.cpp#L27) | Callable definition: const MinimumHeightCandidate& Selection::selected() const noexcept | calls ; returns *data_-&gt;chosen · [reviewed contract](#b0007) |
| [B0008 · 28–28](../../../../../src/planner/selection.cpp#L28) | Callable definition: std::size_t Selection::selected_index() const noexcept | calls ; returns data_-&gt;selected · [reviewed contract](#b0008) |
| [B0009 · 29–29](../../../../../src/planner/selection.cpp#L29) | Callable definition: const CompiledProgram& Selection::plan() const noexcept | calls ; returns *data_-&gt;plan · [reviewed contract](#b0009) |
| [B0010 · 30–30](../../../../../src/planner/selection.cpp#L30) | Callable definition: const CapturedSource& Selection::source() const noexcept | calls ; returns data_-&gt;source · [reviewed contract](#b0010) |
| [B0011 · 31–31](../../../../../src/planner/selection.cpp#L31) | Callable definition: const CapturedRequest& Selection::request() const noexcept | calls ; returns data_-&gt;request · [reviewed contract](#b0011) |
| [B0012 · 32–32](../../../../../src/planner/selection.cpp#L32) | Callable definition: const resource::MemoryAccount& Selection::account() const & noexcept | calls ; returns data_-&gt;account · [reviewed contract](#b0012) |
| [B0013 · 33–33](../../../../../src/planner/selection.cpp#L33) | Explanatory comments or spacing. | source comment (unverified): // Export explicit caller-owned source configuration. See docs/selection.md. · [reviewed contract](#b0013) |
| [B0014 · 34–41](../../../../../src/planner/selection.cpp#L34) | Callable definition: Source Selection::export_source() const | calls std::string, std::move; returns DirectCQ{std::move(out)}; std::get&lt;PhysicalBasis&gt;(data_-&gt;source); source comment (unverified): // Export explicit caller-owned source configuration. See docs/selection.md. · [reviewed contract](#b0014) |
| [B0015 · 42–42](../../../../../src/planner/selection.cpp#L42) | Explanatory comments or spacing. | source comment (unverified): // Export captured request into ordinary caller storage. See docs/selection.md. · [reviewed contract](#b0015) |
| [B0016 · 43–48](../../../../../src/planner/selection.cpp#L43) | Callable definition: Request Selection::export_request() const | calls std::string; returns out; source comment (unverified): // Export captured request into ordinary caller storage. See docs/selection.md. · [reviewed contract](#b0016) |
| [B0017 · 49–49](../../../../../src/planner/selection.cpp#L49) | Callable definition: const SelectionVector&lt;Assessment&gt;& Selection::assessments() const noexcept | calls ; returns data_-&gt;assessments · [reviewed contract](#b0017) |
| [B0018 · 50–50](../../../../../src/planner/selection.cpp#L50) | Callable definition: const SelectionVector&lt;CandidateDecision&gt;& Selection::decisions() const noexcept | calls ; returns data_-&gt;decisions · [reviewed contract](#b0018) |
| [B0019 · 51–51](../../../../../src/planner/selection.cpp#L51) | Callable definition: const SelectionVector&lt;patterns::Analysis&gt;& Selection::pattern_analyses() const noexcept | calls ; returns data_-&gt;pattern_analyses · [reviewed contract](#b0019) |
| [B0020 · 52–56](../../../../../src/planner/selection.cpp#L52) | Callable definition: std::optional&lt;PatternGuarantee&gt; Selection::pattern_guarantee() const noexcept | calls empty, PatternGuarantee; returns {}; PatternGuarantee(data_) · [reviewed contract](#b0020) |
| [B0021 · 57–57](../../../../../src/planner/selection.cpp#L57) | Callable definition: const patterns::Analysis& PatternGuarantee::analysis() const & noexcept | calls ; returns data_-&gt;pattern_analyses\[data_-&gt;selected\] · [reviewed contract](#b0021) |
| [B0022 · 58–58](../../../../../src/planner/selection.cpp#L58) | Callable definition: const CompiledProgram& PatternGuarantee::plan() const & noexcept | calls ; returns *data_-&gt;plan · [reviewed contract](#b0022) |
| [B0023 · 59–59](../../../../../src/planner/selection.cpp#L59) | Callable definition: const std::optional&lt;rank::Evidence&gt;& Selection::evidence() const noexcept | calls ; returns data_-&gt;evidence · [reviewed contract](#b0023) |
| [B0024 · 60–60](../../../../../src/planner/selection.cpp#L60) | Callable definition: EvidenceUse Selection::evidence_use() const noexcept | calls ; returns data_-&gt;evidence ? EvidenceUse::as_of : EvidenceUse::absent · [reviewed contract](#b0024) |
| [B0025 · 61–61](../../../../../src/planner/selection.cpp#L61) | Callable definition: rank::Policy Selection::effective_policy() const noexcept | calls ; returns data_-&gt;effective · [reviewed contract](#b0025) |
| [B0026 · 62–62](../../../../../src/planner/selection.cpp#L62) | Callable definition: rank::Reasons Selection::fallback_reasons() const noexcept | calls ; returns data_-&gt;fallback · [reviewed contract](#b0026) |
| [B0027 · 63–63](../../../../../src/planner/selection.cpp#L63) | Callable definition: const rank::Usage& Selection::usage() const noexcept | calls ; returns data_-&gt;usage · [reviewed contract](#b0027) |
| [B0028 · 64–64](../../../../../src/planner/selection.cpp#L64) | Callable definition: PreparationTiming Selection::preparation_timing() const noexcept | calls ; returns data_-&gt;timing · [reviewed contract](#b0028) |
| [B0029 · 65–65](../../../../../src/planner/selection.cpp#L65) | Callable definition: const CacheObservation& Selection::cache_observation() const noexcept | calls ; returns data_-&gt;cache · [reviewed contract](#b0029) |
| [B0030 · 66–66](../../../../../src/planner/selection.cpp#L66) | Callable definition: const std::optional&lt;SelectionText&gt;& Selection::cache_binding() const noexcept | calls ; returns data_-&gt;key · [reviewed contract](#b0030) |
| [B0031 · 67–69](../../../../../src/planner/selection.cpp#L67) | declares namespace scope. | source comment (unverified): // Prepare account-backed result storage with complete source/request/evidence owners. See · [reviewed contract](#b0031) |
| [B0032 · 70–76](../../../../../src/planner/selection.cpp#L70) | Callable definition: SelectionData::SelectionData(const resource::MemoryAccount& a,const CandidateSnapshot& s,const Source& p, const Request& r,const … | calls account, snapshot, source, std::visit; returns CapturedDirectCQ{CapturedPhysicalOptions(a,input.options)}; input; source comment (unverified): // Prepare account-backed result storage with complete source/request/evidence owners. See · [reviewed contract](#b0032) |
| [B0033 · 77–77](../../../../../src/planner/selection.cpp#L77) | declares namespace scope. |  · [reviewed contract](#b0033) |
| [B0034 · 78–82](../../../../../src/planner/selection.cpp#L78) | Callable definition: void strings(const io::CachePolicy& policy, Budget& b) | calls work, size, bytes; 1 loop sites · [reviewed contract](#b0034) |
| [B0035 · 83–84](../../../../../src/planner/selection.cpp#L83) | Explanatory comments or spacing. | source comment (unverified): // Choose the receiving allocation account without minting an internal query refill. See · [reviewed contract](#b0035) |
| [B0036 · 85–95](../../../../../src/planner/selection.cpp#L85) | Callable definition: resource::MemoryAccount operation_account(const Source& source,const std::optional&lt;rank::Evidence&gt;& evidence, const resource::Mem… | calls plan, account, require, bool; guard require(bool(*native),Stop::invalid_handle);return native-&gt;account();; returns receiving; evidence-&gt;plan().account(); source comment (unverified): // Choose the receiving allocation account without minting an internal query refill. See · [reviewed contract](#b0036) |
| [B0037 · 96–97](../../../../../src/planner/selection.cpp#L96) | Explanatory comments or spacing. | source comment (unverified): // Lower/replan exactly the chosen candidate under remaining aggregate native work. See · [reviewed contract](#b0037) |
| [B0038 · 98–174](../../../../../src/planner/selection.cpp#L98) | Callable definition: CompiledProgram lower_winner(const MinimumHeightCandidate& candidate, const Source& source, const std::optional&lt;rank::Evidence&gt;& … | calls sample, std::visit, source_payload, direct_source_payload; returns plan.normalized().has_value(); result; source comment (unverified): // Lower/replan exactly the chosen candidate under remaining aggregate native work. See · [reviewed contract](#b0038) |
| [B0039 · 175–177](../../../../../src/planner/selection.cpp#L175) | Closes surrounding scope/type. | source comment (unverified): // Bind one synchronous transaction and its initial preparation usage/account. See · [reviewed contract](#b0039) |
| [B0040 · 178–184](../../../../../src/planner/selection.cpp#L178) | Callable definition: Operation::Operation(const CandidateSnapshot& s, const Source& p, const Request& r, const std::optional&lt;rank::Evidence&gt;& e, PlanC… | calls snapshot, source, request, cache; guard if (use != CacheUse::bypass) require(c != nullptr, Stop::invalid_request);; source comment (unverified): // Bind one synchronous transaction and its initial preparation usage/account. See · [reviewed contract](#b0040) |
| [B0041 · 185–186](../../../../../src/planner/selection.cpp#L185) | Explanatory comments or spacing. | source comment (unverified): // Validate supported request and the typed original-proof family before speculative work. See · [reviewed contract](#b0041) |
| [B0042 · 187–216](../../../../../src/planner/selection.cpp#L187) | Callable definition: void Operation::admit() | calls work, require, valueless_by_exception, bool; guard require(request.policy == Policy::height_only \|\| request.policy == Policy::committed_input_native_d…; source comment (unverified): // Validate supported request and the typed original-proof family before speculative work. See · [reviewed contract](#b0042) |
| [B0043 · 217–218](../../../../../src/planner/selection.cpp#L217) | Explanatory comments or spacing. | source comment (unverified): // Attach a freshly prepared runtime-bridge evidence owner exactly once. See · [reviewed contract](#b0043) |
| [B0044 · 219–222](../../../../../src/planner/selection.cpp#L219) | Callable definition: void Operation::attach(const rank::Evidence& value) | calls require, has_value, preparation_timing; guard require(!evidence.has_value()); evidence = value;; source comment (unverified): // Attach a freshly prepared runtime-bridge evidence owner exactly once. See · [reviewed contract](#b0044) |
| [B0045 · 223–225](../../../../../src/planner/selection.cpp#L223) | Callable definition: bool Operation::needs_sources() const noexcept | calls ; returns request.policy == Policy::tuple_index_slots \|\| std::holds_alternative&lt;TupleIndexSlotLimit&gt;(request.… · [reviewed contract](#b0045) |
| [B0046 · 226–227](../../../../../src/planner/selection.cpp#L226) | Explanatory comments or spacing. | source comment (unverified): // Evaluate the full retained family, choose an eligible winner and privately prepare its · [reviewed contract](#b0046) |
| [B0047 · 228–352](../../../../../src/planner/selection.cpp#L228) | Callable definition: Prepared Operation::prepare() | calls source_binding, work, require, matches; guard require(request.update_patterns-&gt;matches(native), Stop::binding_mismatch);; returns index; prepared; growth make_accounted_shared, push_back, reserve; 3 loop sites; source comment (unverified): // Evaluate the full retained family, choose an eligible winner and privately prepare its · [reviewed contract](#b0047) |
| [B0048 · 353–354](../../../../../src/planner/selection.cpp#L353) | Explanatory comments or spacing. | source comment (unverified): // Publish result/cache only after the final cooperative deadline check. See · [reviewed contract](#b0048) |
| [B0049 · 355–363](../../../../../src/planner/selection.cpp#L355) | Callable definition: void Operation::finalize(Prepared& prepared) | calls sample, commit; source comment (unverified): // Publish result/cache only after the final cooperative deadline check. See · [reviewed contract](#b0049) |
| [B0050 · 364–367](../../../../../src/planner/selection.cpp#L364) | Callable definition: void Operation::note(const Failure& failure) noexcept | calls  · [reviewed contract](#b0050) |
| [B0051 · 368–370](../../../../../src/planner/selection.cpp#L368) | Callable definition: void Operation::note(rank::Stop stop) noexcept | calls note, component_diagnostic · [reviewed contract](#b0051) |
| [B0052 · 371–372](../../../../../src/planner/selection.cpp#L371) | Explanatory comments or spacing. | source comment (unverified): // Capture final diagnostic elapsed/usage after success or failure. See · [reviewed contract](#b0052) |
| [B0053 · 373–373](../../../../../src/planner/selection.cpp#L373) | Callable definition: void Operation::finish() noexcept | calls finish; source comment (unverified): // Capture final diagnostic elapsed/usage after success or failure. See · [reviewed contract](#b0053) |
| [B0054 · 374–376](../../../../../src/planner/selection.cpp#L374) | Closes surrounding scope/type. | source comment (unverified): // namespace detail · [reviewed contract](#b0054) |
| [B0055 · 377–412](../../../../../src/planner/selection.cpp#L377) | Callable definition: Attempt select(const CandidateSnapshot& snapshot, const Source& source, const Request& request, const std::optional&lt;rank::Evidenc… | calls preparation_usage, detail::preparation_timing, emplace, admit; returns operation-&gt;diagnostic; out; growth emplace; source comment (unverified): // Execute pure synchronous selection as an atomic result/cache transaction. See · [reviewed contract](#b0055) |
| [B0056 · 413–413](../../../../../src/planner/selection.cpp#L413) | Closes surrounding scope/type. | source comment (unverified): // namespace crown::planner::selection · [reviewed contract](#b0056) |

## B0001

[Lines 1–9](../../../../../src/planner/selection.cpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L1-L9:sha256:7565a65e4144ad91490217f64cc5fbf49a4826b9b4aa0117be98a459949ce6e4
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Import selection ownership/binding, compiled source and private pattern analysis visitors, lowering and existing error/new declarations; open the selection implementation namespace. |
| inputs / outputs | Preprocessor directives resolve compile-time declarations. This block has no runtime call inputs or result. |
| invariants | Includes, namespace openings, aliases, and forward declarations determine C++ name visibility and type availability; they do not validate planner data or grant proof authority. |
| ownership | No runtime object is owned by the include or scope directives. Any state belongs to the types and functions declared after them. |
| failure | A missing header, incompatible declaration, or ill-formed type use fails during compilation; runtime failures remain in the called code. |
| cost | Adds preprocessing, parsing, and any later template-instantiation work in this translation unit. It adds no runtime timer, counter, branch, or allocation. |
| Design | [src/planner/selection.cpp](../../../../../src/planner/selection.cpp), [docs/selection.md](../../../../selection.md), [docs/selection_accounting.md](../../../../selection_accounting.md), [docs/selection_binding.md](../../../../selection_binding.md), [docs/update_patterns.md](../../../../update_patterns.md) |

## B0002

[Lines 10–14](../../../../../src/planner/selection.cpp#L10); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
CapturedCachePolicy::CapturedCachePolicy(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Copy all physical policy text into the receiving account. |
| inputs / outputs | Constructs four SelectionText members with capture attribution. |
| invariants | Storage conversion enables no unsupported arithmetic/model. |
| ownership | Each text retains original account for release. |
| failure | Allocation failure destroys completed members before publication. |
| cost | Sum of policy bytes plus real string capacity/framing. |
| Design | [docs/selection.md](../../../../selection.md), [docs/query_memory.md §Boundaries](../../../../query_memory.md) |

## B0003

[Lines 15–16](../../../../../src/planner/selection.cpp#L15); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
CapturedPhysicalOptions::CapturedPhysicalOptions(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Capture physical policy and exact scalar/backend options. |
| inputs / outputs | Captures policy, copies limits and indexed_storage. |
| invariants | No option normalization or backend instantiation. |
| ownership | Owns text and copied scalar configuration. |
| failure | Policy/account allocation may throw. |
| cost | Policy bytes plus fixed option copies. |
| Design | [docs/selection.md](../../../../selection.md), [docs/query_memory.md §Boundaries](../../../../query_memory.md) |

## B0004

[Lines 17–17](../../../../../src/planner/selection.cpp#L17); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L17-L17:sha256:807ace4b58a1e5abbf0c6217e800974a4f3f59e6c477bc6dd4d83f1ed741a490
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Use the adjacent note for CapturedRequest: Capture an admitted request with native slot-cap text. Confirm behavior against the declaration and implementation; comment text alone does not enforce or prove it. |
| inputs / outputs | This comment has no inputs or outputs. It accompanies CapturedRequest; use the adjacent declaration and implementation for the actual values and result. |
| invariants | This is static guidance only. The comment cannot alter state or guarantee that its wording holds. |
| ownership | The note owns no storage and changes no lifetime; ownership and borrowing for CapturedRequest come from its actual types and implementation. |
| failure | Reading the comment has no runtime failure path. Compile or link errors, exceptions, and resource stops belong to the adjacent code. |
| cost | The comment adds no runtime instructions, allocation, clock read, counter debit, or engine hook; only source-text processing is added. |
| Design | [src/planner/selection.cpp](../../../../../src/planner/selection.cpp), [docs/selection.md](../../../../selection.md), [docs/selection_accounting.md](../../../../selection_accounting.md), [docs/selection_binding.md](../../../../selection_binding.md) |

## B0005

[Lines 18–25](../../../../../src/planner/selection.cpp#L18); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
CapturedRequest::CapturedRequest(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Capture admitted request text and optional source-bound rules into the receiving account. |
| inputs / outputs | Copy scalar policy/limits, native slot text and, when present, Declaration::copy_of(account, declaration). |
| invariants | Constructor itself does not validate arbitrary caller tags; successful caller admission precedes retained capture. Direct public capture owns no processing grant: the caller must pre-admit declaration copy_usage and copied text. Stored limits are metadata; select() performs these admissions under its aggregate grant. |
| ownership | Captured text and the cloned declaration Data/rules retain the receiving account. Other copied handles share their existing owners. |
| failure | Public raw construction still confers no admission authority. Invalid supplied declaration or allocation can throw before Data publication; Operation pre-admits copy_usage for valid inputs. |
| cost | Fixed options plus cap-byte and O(R) metadata copy; no scope directory or sort. |
| Design | [docs/selection.md](../../../../selection.md), [docs/query_memory.md §Boundaries](../../../../query_memory.md), [docs/update_patterns.md](../../../../update_patterns.md) |

## B0006

[Lines 26–26](../../../../../src/planner/selection.cpp#L26); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
const CandidateSnapshot& Selection::snapshot() const noexcept
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Borrow the full retained checked candidate family. |
| inputs / outputs | CandidateSnapshot reference. |
| invariants | The original proof and family context remain separate from cost selection. |
| ownership | Borrow requires some surviving SelectionData owner; returned reference adds no ownership. |
| failure | Noexcept getters assume the trusted non-null published Data; moves intentionally preserve source ownership. |
| cost | Fixed saved-field/reference access; explicit copying or last-owner release has separate payload costs. |
| Design | [docs/selection.md](../../../../selection.md), [docs/query_memory.md §Boundaries](../../../../query_memory.md) |

## B0007

[Lines 27–27](../../../../../src/planner/selection.cpp#L27); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
const MinimumHeightCandidate& Selection::selected() const noexcept
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Borrow the chosen checked minimum-height candidate. |
| inputs / outputs | Dereferences completed chosen optional. |
| invariants | Data publication guarantees chosen; C05 creates no new lower proof. |
| ownership | Borrow requires some surviving SelectionData owner; returned reference adds no ownership. |
| failure | Noexcept getters assume the trusted non-null published Data; moves intentionally preserve source ownership. |
| cost | Fixed saved-field/reference access; explicit copying or last-owner release has separate payload costs. |
| Design | [docs/selection.md](../../../../selection.md), [docs/query_memory.md §Boundaries](../../../../query_memory.md) |

## B0008

[Lines 28–28](../../../../../src/planner/selection.cpp#L28); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::size_t Selection::selected_index() const noexcept
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Read the chosen index in retained snapshot order. |
| inputs / outputs | Returns selected scalar. |
| invariants | Index refers to this snapshot, not a provider current position. |
| ownership | Returns an independent scalar. |
| failure | Noexcept getters assume the trusted non-null published Data; moves intentionally preserve source ownership. |
| cost | Fixed saved-field/reference access; explicit copying or last-owner release has separate payload costs. |
| Design | [docs/selection.md](../../../../selection.md), [docs/query_memory.md §Boundaries](../../../../query_memory.md) |

## B0009

[Lines 29–29](../../../../../src/planner/selection.cpp#L29); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
const CompiledProgram& Selection::plan() const noexcept
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Borrow the whole chosen immutable native program. |
| inputs / outputs | Dereferences completed plan optional. |
| invariants | Program may be a cache-shared artifact under its original account; this does not install it in a runtime. |
| ownership | Borrow requires some surviving SelectionData owner; returned reference adds no ownership. |
| failure | Noexcept getters assume the trusted non-null published Data; moves intentionally preserve source ownership. |
| cost | Fixed saved-field/reference access; explicit copying or last-owner release has separate payload costs. |
| Design | [docs/selection.md](../../../../selection.md), [docs/query_memory.md §Boundaries](../../../../query_memory.md) |

## B0010

[Lines 30–30](../../../../../src/planner/selection.cpp#L30); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
const CapturedSource& Selection::source() const noexcept
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Borrow retained exact physical/direct source context. |
| inputs / outputs | CapturedSource reference. |
| invariants | Captured DirectCQ derives original proof model; a basis preserves complete native/normalized source. |
| ownership | Borrow requires some surviving SelectionData owner; returned reference adds no ownership. |
| failure | Noexcept getters assume the trusted non-null published Data; moves intentionally preserve source ownership. |
| cost | Fixed saved-field/reference access; explicit copying or last-owner release has separate payload costs. |
| Design | [docs/selection.md](../../../../selection.md), [docs/query_memory.md §Boundaries](../../../../query_memory.md) |

## B0011

[Lines 31–31](../../../../../src/planner/selection.cpp#L31); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
const CapturedRequest& Selection::request() const noexcept
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Borrow the exact retained account-backed request. |
| inputs / outputs | CapturedRequest reference. |
| invariants | Read-only fields cannot change policy, cap or result. |
| ownership | Borrow requires some surviving SelectionData owner; returned reference adds no ownership. |
| failure | Noexcept getters assume the trusted non-null published Data; moves intentionally preserve source ownership. |
| cost | Fixed saved-field/reference access; explicit copying or last-owner release has separate payload costs. |
| Design | [docs/selection.md](../../../../selection.md), [docs/query_memory.md §Boundaries](../../../../query_memory.md) |

## B0012

[Lines 32–32](../../../../../src/planner/selection.cpp#L32); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
const resource::MemoryAccount& Selection::account() const & noexcept
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Borrow the receiving account retained by result data. |
| inputs / outputs | Lvalue-only account reference. |
| invariants | This shares no new allowance and need not equal an already funded cache-hit program account. |
| ownership | Borrow requires some surviving SelectionData owner; returned reference adds no ownership. |
| failure | Noexcept getters assume the trusted non-null published Data; moves intentionally preserve source ownership. |
| cost | Fixed saved-field/reference access; explicit copying or last-owner release has separate payload costs. |
| Design | [docs/selection.md](../../../../selection.md), [docs/query_memory.md §Boundaries](../../../../query_memory.md) |

## B0013

[Lines 33–33](../../../../../src/planner/selection.cpp#L33); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L33-L33:sha256:58844ce5f4154b2e05373556e65e636997d44fdbb0c7d36f8c6fc5228ae3ab95
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Use the adjacent note for Selection: Export explicit caller-owned source configuration. Confirm behavior against the declaration and implementation; comment text alone does not enforce or prove it. |
| inputs / outputs | This comment has no inputs or outputs. It accompanies Selection; use the adjacent declaration and implementation for the actual values and result. |
| invariants | This is static guidance only. The comment cannot alter state or guarantee that its wording holds. |
| ownership | The note owns no storage and changes no lifetime; ownership and borrowing for Selection come from its actual types and implementation. |
| failure | Reading the comment has no runtime failure path. Compile or link errors, exceptions, and resource stops belong to the adjacent code. |
| cost | The comment adds no runtime instructions, allocation, clock read, counter debit, or engine hook; only source-text processing is added. |
| Design | [src/planner/selection.cpp](../../../../../src/planner/selection.cpp), [docs/selection.md](../../../../selection.md), [docs/selection_accounting.md](../../../../selection_accounting.md), [docs/selection_binding.md](../../../../selection_binding.md) |

## B0014

[Lines 34–41](../../../../../src/planner/selection.cpp#L34); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Source Selection::export_source() const {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Export explicit caller-owned source configuration. |
| inputs / outputs | Direct source copies native text to ordinary PhysicalOptions; basis returns shared plan variant. |
| invariants | Export does not create validation/import/proof authority or install a plan. |
| ownership | Returned DirectCQ owns ordinary strings; basis shares existing immutable program/DTO. |
| failure | Ordinary string/variant allocation can throw outside selection processing grant. |
| cost | Copies policy bytes or handles; no implicit full native program export. |
| Design | [docs/selection.md](../../../../selection.md), [docs/query_memory.md §Boundaries](../../../../query_memory.md) |

## B0015

[Lines 42–42](../../../../../src/planner/selection.cpp#L42); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L42-L42:sha256:4b2857ea8b02bffad5e267f92c2180281046e0e6c3c016a1b5297ac75d422f16
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Use the adjacent note for Selection: Export captured request into ordinary caller storage. Confirm behavior against the declaration and implementation; comment text alone does not enforce or prove it. |
| inputs / outputs | This comment has no inputs or outputs. It accompanies Selection; use the adjacent declaration and implementation for the actual values and result. |
| invariants | This is static guidance only. The comment cannot alter state or guarantee that its wording holds. |
| ownership | The note owns no storage and changes no lifetime; ownership and borrowing for Selection come from its actual types and implementation. |
| failure | Reading the comment has no runtime failure path. Compile or link errors, exceptions, and resource stops belong to the adjacent code. |
| cost | The comment adds no runtime instructions, allocation, clock read, counter debit, or engine hook; only source-text processing is added. |
| Design | [src/planner/selection.cpp](../../../../../src/planner/selection.cpp), [docs/selection.md](../../../../selection.md), [docs/selection_accounting.md](../../../../selection_accounting.md), [docs/selection_binding.md](../../../../selection_binding.md) |

## B0016

[Lines 43–48](../../../../../src/planner/selection.cpp#L43); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Request Selection::export_request() const {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Export captured request into ordinary caller storage. |
| inputs / outputs | Copy scalar choices, convert native cap text to std::string, and share the immutable captured optional Declaration. |
| invariants | Returned edits affect no retained Selection. |
| ownership | Caller owns exported cap text; the Declaration handle retains its original captured owner. No borrowed rule pointer escapes. |
| failure | Caller export allocation may throw. |
| cost | Cap-byte copy plus fixed fields/handle retention, outside selection processing counters. A deep ordinary rule export is a separate explicit export_record call. |
| Design | [docs/selection.md](../../../../selection.md), [docs/query_memory.md §Boundaries](../../../../query_memory.md), [docs/update_patterns.md](../../../../update_patterns.md) |

## B0017

[Lines 49–49](../../../../../src/planner/selection.cpp#L49); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
const SelectionVector<Assessment>& Selection::assessments() const noexcept
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Borrow full complete C02 assessments with their roles. |
| inputs / outputs | Native vector reference. |
| invariants | C02 winner can differ from constrained C05 chosen; read scores by effective policy. |
| ownership | Borrow requires some surviving SelectionData owner; returned reference adds no ownership. |
| failure | Noexcept getters assume the trusted non-null published Data; moves intentionally preserve source ownership. |
| cost | Fixed saved-field/reference access; explicit copying or last-owner release has separate payload costs. |
| Design | [docs/selection.md](../../../../selection.md), [docs/query_memory.md §Boundaries](../../../../query_memory.md) |

## B0018

[Lines 50–50](../../../../../src/planner/selection.cpp#L50); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
const SelectionVector<CandidateDecision>& Selection::decisions() const noexcept
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Borrow complete retained-candidate eligibility decisions. |
| inputs / outputs | Native vector reference aligned with snapshot. |
| invariants | Mandatory cap exclusions are never bypassed by fallback. |
| ownership | Borrow requires some surviving SelectionData owner; returned reference adds no ownership. |
| failure | Noexcept getters assume the trusted non-null published Data; moves intentionally preserve source ownership. |
| cost | Fixed saved-field/reference access; explicit copying or last-owner release has separate payload costs. |
| Design | [docs/selection.md](../../../../selection.md), [docs/query_memory.md §Boundaries](../../../../query_memory.md) |

## B0019

[Lines 51–51](../../../../../src/planner/selection.cpp#L51); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L51-L51:sha256:de3c69dd556dc5c5670271d75fa9a1514bd93f1df86faeeb8b4b4c3e601472ac
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Borrow the published conditional analysis context for all retained candidates. |
| inputs / outputs | Valid Selection in; const reference to Data.pattern_analyses out. Empty when no declaration was requested, otherwise ordered like the snapshot candidates. |
| invariants | Plain reports identify candidate/declaration; they grant neither runtime compliance nor proof authority. Caller cannot mutate the vector through this getter. |
| ownership | Returned vector/report/edge references borrow surviving Selection Data ownership; no independent copy/retention occurs at the getter. |
| failure | Noexcept under the existing valid Selection backing invariant; using a reference after final Data release is caller misuse. |
| cost | Fixed field access, no allocation, scan, serialization, clock read or grant debit. |
| Design | [docs/selection.md](../../../../selection.md), [docs/update_patterns.md](../../../../update_patterns.md) |

## B0020

[Lines 52–56](../../../../../src/planner/selection.cpp#L52); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L52-L56:sha256:bfcb518feb5ecd09d77ef374f07d92270ce1cfee67a9aa47af22cea896334c3e
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Publish a profile only for a selected proved pattern case. |
| inputs / outputs | Read the selected retained analysis; return none for absent/unknown conditions, otherwise share SelectionData in an optional PatternGuarantee. |
| invariants | Selection construction supplies a valid selected index. No case is recomputed, no unknown becomes positive and no declaration is treated as observed enforcement. |
| ownership | Result shares the existing immutable owner; no input pointer escapes without its graph owner. |
| failure | Noexcept; no allocation or new diagnostic boundary. |
| cost | O(1) lookup/reference operations; no edge/rule scan or graph copy. |
| Design | docs/update_patterns.md#support-action-guarantee-profile, [docs/selection.md](../../../../selection.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0021

[Lines 57–57](../../../../../src/planner/selection.cpp#L57); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L57-L57:sha256:2545a12c2375319a213630217b47e754b6ead6a02a381af3483a8dc91ab8f132
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Borrow the exact selected conditional analysis. |
| inputs / outputs | Return pattern_analyses\[selected\] by const reference, preserving candidate, source-bound rules, transfer and edge premises. |
| invariants | Private profile construction ensures that entry exists and has a proved case. It is still conditional. |
| ownership | Borrow remains valid while a profile/selection Data owner survives; rvalue call is deleted. |
| failure | Noexcept on a valid profile; no new checks or exceptions. |
| cost | O(1), no allocation or scan. |
| Design | docs/update_patterns.md#support-action-guarantee-profile, [docs/selection.md](../../../../selection.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0022

[Lines 58–58](../../../../../src/planner/selection.cpp#L58); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L58-L58:sha256:de38f89b6abf0f712e7770bf52755dce058686893b0af211b8e73d708c709f19
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Borrow the exact compiled selected program. |
| inputs / outputs | Return the admitted selected plan by const reference. |
| invariants | The selected Data already contains a complete plan. Its operator tree may be empty for a contradictory retained body; no original-height proof is replaced. |
| ownership | Existing Data owns the immutable native program; getter borrow requires a surviving profile owner. |
| failure | Noexcept on valid profile; no new failure path. |
| cost | O(1), no export, row copy or allocation. |
| Design | docs/update_patterns.md#support-action-guarantee-profile, [docs/selection.md](../../../../selection.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0023

[Lines 59–59](../../../../../src/planner/selection.cpp#L59); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
const std::optional<rank::Evidence>& Selection::evidence() const noexcept
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Borrow retained as-of evidence if supplied/captured. |
| inputs / outputs | Optional Evidence reference. |
| invariants | Pure result promises no actual-owner freshness after return. |
| ownership | Borrow requires some surviving SelectionData owner; returned reference adds no ownership. |
| failure | Noexcept getters assume the trusted non-null published Data; moves intentionally preserve source ownership. |
| cost | Fixed saved-field/reference access; explicit copying or last-owner release has separate payload costs. |
| Design | [docs/selection.md](../../../../selection.md), [docs/query_memory.md §Boundaries](../../../../query_memory.md) |

## B0024

[Lines 60–60](../../../../../src/planner/selection.cpp#L60); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
EvidenceUse Selection::evidence_use() const noexcept
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Report evidence presence as absent or as-of. |
| inputs / outputs | Returns scalar from optional presence. |
| invariants | Even current-owner capture becomes immutable history after return. |
| ownership | Returns an independent scalar. |
| failure | Noexcept getters assume the trusted non-null published Data; moves intentionally preserve source ownership. |
| cost | Fixed saved-field/reference access; explicit copying or last-owner release has separate payload costs. |
| Design | [docs/selection.md](../../../../selection.md), [docs/query_memory.md §Boundaries](../../../../query_memory.md) |

## B0025

[Lines 61–61](../../../../../src/planner/selection.cpp#L61); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
rank::Policy Selection::effective_policy() const noexcept
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Read the effective primary scoring baseline. |
| inputs / outputs | Returns saved rank policy. |
| invariants | Height fallback labels scoring only; required original minimum height remains unchanged. |
| ownership | Returns an independent scalar. |
| failure | Noexcept getters assume the trusted non-null published Data; moves intentionally preserve source ownership. |
| cost | Fixed saved-field/reference access; explicit copying or last-owner release has separate payload costs. |
| Design | [docs/selection.md](../../../../selection.md), [docs/query_memory.md §Boundaries](../../../../query_memory.md) |

## B0026

[Lines 62–62](../../../../../src/planner/selection.cpp#L62); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
rank::Reasons Selection::fallback_reasons() const noexcept
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Read recorded primary fact-unavailability reasons. |
| inputs / outputs | Returns saved bitmask. |
| invariants | Processing failures cannot be converted to successful fallback. |
| ownership | Returns an independent scalar. |
| failure | Noexcept getters assume the trusted non-null published Data; moves intentionally preserve source ownership. |
| cost | Fixed saved-field/reference access; explicit copying or last-owner release has separate payload costs. |
| Design | [docs/selection.md](../../../../selection.md), [docs/query_memory.md §Boundaries](../../../../query_memory.md) |

## B0027

[Lines 63–63](../../../../../src/planner/selection.cpp#L63); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
const rank::Usage& Selection::usage() const noexcept
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Borrow final aggregate logical processing/time usage. |
| inputs / outputs | Usage reference saved before no-fail commit. |
| invariants | Usage is not allocator peak or observed event cost; post-publication cleanup is separate. |
| ownership | Borrow requires some surviving SelectionData owner; returned reference adds no ownership. |
| failure | Noexcept getters assume the trusted non-null published Data; moves intentionally preserve source ownership. |
| cost | Fixed saved-field/reference access; explicit copying or last-owner release has separate payload costs. |
| Design | [docs/selection.md](../../../../selection.md), [docs/query_memory.md §Boundaries](../../../../query_memory.md) |

## B0028

[Lines 64–64](../../../../../src/planner/selection.cpp#L64); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
PreparationTiming Selection::preparation_timing() const noexcept
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Read whether historical preparation timing was measured. |
| inputs / outputs | Returns saved timing category. |
| invariants | Unmeasured is not a zero-duration measurement. |
| ownership | Returns an independent scalar. |
| failure | Noexcept getters assume the trusted non-null published Data; moves intentionally preserve source ownership. |
| cost | Fixed saved-field/reference access; explicit copying or last-owner release has separate payload costs. |
| Design | [docs/selection.md](../../../../selection.md), [docs/query_memory.md §Boundaries](../../../../query_memory.md) |

## B0029

[Lines 65–65](../../../../../src/planner/selection.cpp#L65); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
const CacheObservation& Selection::cache_observation() const noexcept
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Borrow this result cache diagnostics/caps. |
| inputs / outputs | CacheObservation reference independent of live cache. |
| invariants | Observation grants neither artifact import nor owner freshness. |
| ownership | Borrow requires some surviving SelectionData owner; returned reference adds no ownership. |
| failure | Noexcept getters assume the trusted non-null published Data; moves intentionally preserve source ownership. |
| cost | Fixed saved-field/reference access; explicit copying or last-owner release has separate payload costs. |
| Design | [docs/selection.md](../../../../selection.md), [docs/query_memory.md §Boundaries](../../../../query_memory.md) |

## B0030

[Lines 66–66](../../../../../src/planner/selection.cpp#L66); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
const std::optional<SelectionText>& Selection::cache_binding() const noexcept
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Borrow full diagnostic artifact bytes when caching generated them. |
| inputs / outputs | Optional account-backed key reference. |
| invariants | Bytes are not an insertion/proof/import capability; cache bypass/disabled can have no key. |
| ownership | Borrow requires some surviving SelectionData owner; returned reference adds no ownership. |
| failure | Noexcept getters assume the trusted non-null published Data; moves intentionally preserve source ownership. |
| cost | Fixed saved-field/reference access; explicit copying or last-owner release has separate payload costs. |
| Design | [docs/selection.md](../../../../selection.md), [docs/query_memory.md §Boundaries](../../../../query_memory.md) |

## B0031

[Lines 67–69](../../../../../src/planner/selection.cpp#L67); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L67-L69:sha256:5a88ce84b1105838377286804da8b6c2a3ed524167a8a44644350f0cbbdafeb3
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | open detail in src/planner/selection.cpp. Attached note: Prepare account-backed result storage with complete source/request/evidence owners. The note is documentation only. |
| inputs / outputs | This namespace, scope, or declaration boundary has no runtime call inputs or outputs. |
| invariants | It changes compile-time visibility or declaration identity only; attached comments do not enforce or prove the described behavior. |
| ownership | This span creates no runtime owner. Later object definitions and calls determine storage and lifetimes. |
| failure | An invalid declaration or scope boundary fails compilation; no runtime exception or resource stop comes from this span. |
| cost | Compile-time parsing and preprocessor bookkeeping only; no runtime branch, allocation, clock read, counter debit, or engine hook. |
| Design | [src/planner/selection.cpp](../../../../../src/planner/selection.cpp), [docs/selection.md](../../../../selection.md), [docs/selection_accounting.md](../../../../selection_accounting.md), [docs/selection_binding.md](../../../../selection_binding.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0032

[Lines 70–76](../../../../../src/planner/selection.cpp#L70); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
SelectionData::SelectionData(const resource::MemoryAccount& a,
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Prepare account-backed result storage with complete source/request/evidence owners. |
| inputs / outputs | Share snapshot/evidence/source handles, capture direct options and request including optional receiving-account declaration, and construct empty assessment/decision/analysis vectors. |
| invariants | No chosen/plan publication occurs in this constructor; caller has admitted inputs. |
| ownership | Data retains receiving account and original shared input owners. |
| failure | Any capture/allocation failure destroys unexposed members. |
| cost | Retained text and optional O(R) rule copy; empty new vector allocates no backing cells. Large immutable proof/source owners remain shared. |
| Design | [docs/query_memory.md §Boundaries](../../../../query_memory.md), [docs/selection_accounting.md §Atomic publication](../../../../selection_accounting.md), [docs/update_patterns.md](../../../../update_patterns.md) |

```text
[&](const auto& input)->CapturedSource {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Choose account-backed direct capture or immutable basis sharing. |
| inputs / outputs | DirectCQ becomes CapturedDirectCQ; PhysicalBasis is copied as a handle. |
| invariants | No ordinary retained source mirror is introduced for native input. Source-variant capture is unchanged; optional request-declaration cloning is a separate member constructor. |
| ownership | Borrows source during constructor; returned capture owns text/handles. |
| failure | Native text allocation may throw before Data exists. |
| cost | Policy-byte copy or fixed handle retention. |
| Design | [docs/query_memory.md §Boundaries](../../../../query_memory.md), [docs/update_patterns.md](../../../../update_patterns.md) |

## B0033

[Lines 77–77](../../../../../src/planner/selection.cpp#L77); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L77-L77:sha256:cf04d99c0f5d3521f67f7c587d20dd3592a5024b903529e1e468844f7fae8135
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | open anonymous helper namespace in src/planner/selection.cpp. |
| inputs / outputs | This namespace, scope, or declaration boundary has no runtime call inputs or outputs. |
| invariants | It changes compile-time visibility or declaration identity only; attached comments do not enforce or prove the described behavior. |
| ownership | This span creates no runtime owner. Later object definitions and calls determine storage and lifetimes. |
| failure | An invalid declaration or scope boundary fails compilation; no runtime exception or resource stop comes from this span. |
| cost | Compile-time parsing and preprocessor bookkeeping only; no runtime branch, allocation, clock read, counter debit, or engine hook. |
| Design | [src/planner/selection.cpp](../../../../../src/planner/selection.cpp), [docs/selection.md](../../../../selection.md), [docs/selection_accounting.md](../../../../selection_accounting.md), [docs/selection_binding.md](../../../../selection_binding.md) |

## B0034

[Lines 78–82](../../../../../src/planner/selection.cpp#L78); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void strings(const io::CachePolicy& policy,
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Admit known policy-string copy bytes. |
| inputs / outputs | Charges work and payload for all four text lengths. |
| invariants | Logical byte charges do not include capacity/control framing. |
| ownership | Borrows strings without copying them. |
| failure | Budget failure precedes retention/lower copies. |
| cost | Fixed four-length walk with width-based debits. |
| Design | [docs/selection_accounting.md §Exact charge primitives](../../../../selection_accounting.md) |

## B0035

[Lines 83–84](../../../../../src/planner/selection.cpp#L83); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L83-L84:sha256:c89e721b67a493b8afb232a3e5fa4d5868a73876eec63f84341bfd20cd0b1eb0
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Use the adjacent note for operation_account: Choose the receiving allocation account without minting an internal query refill. Confirm behavior against the declaration and implementation; comment text alone does not enforce or prove it. |
| inputs / outputs | This comment has no inputs or outputs. It accompanies operation_account; use the adjacent declaration and implementation for the actual values and result. |
| invariants | This is static guidance only. The comment cannot alter state or guarantee that its wording holds. |
| ownership | The note owns no storage and changes no lifetime; ownership and borrowing for operation_account come from its actual types and implementation. |
| failure | Reading the comment has no runtime failure path. Compile or link errors, exceptions, and resource stops belong to the adjacent code. |
| cost | The comment adds no runtime instructions, allocation, clock read, counter debit, or engine hook; only source-text processing is added. |
| Design | [src/planner/selection.cpp](../../../../../src/planner/selection.cpp), [docs/selection.md](../../../../selection.md), [docs/selection_accounting.md](../../../../selection_accounting.md), [docs/selection_binding.md](../../../../selection_binding.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0036

[Lines 85–95](../../../../../src/planner/selection.cpp#L85); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
resource::MemoryAccount operation_account(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Choose the receiving allocation account without minting an internal query refill. |
| inputs / outputs | Priority: explicit receiving account, evidence program account, native basis account, otherwise standalone UINT64_MAX component account. |
| invariants | Only initial standalone compiler path creates an account; supplied immutable input artifacts remain boundaries. |
| ownership | Returns a shared account handle; no caller account borrow escapes. |
| failure | Invalid native basis rejects; standalone account construction can allocate/fail before Operation construction. |
| cost | Handle reads or one standalone account setup, not model traversal. |
| Design | [docs/query_memory.md §Boundaries](../../../../query_memory.md) |

## B0037

[Lines 96–97](../../../../../src/planner/selection.cpp#L96); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L96-L97:sha256:fca2572fe884aad609c34b6c819b2e91075788169842948d9d5cd236e4d02832
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Use the adjacent note for lower_winner: Lower/replan exactly the chosen candidate under remaining aggregate native work. Confirm behavior against the declaration and implementation; comment text alone does not enforce or prove it. |
| inputs / outputs | This comment has no inputs or outputs. It accompanies lower_winner; use the adjacent declaration and implementation for the actual values and result. |
| invariants | This is static guidance only. The comment cannot alter state or guarantee that its wording holds. |
| ownership | The note owns no storage and changes no lifetime; ownership and borrowing for lower_winner come from its actual types and implementation. |
| failure | Reading the comment has no runtime failure path. Compile or link errors, exceptions, and resource stops belong to the adjacent code. |
| cost | The comment adds no runtime instructions, allocation, clock read, counter debit, or engine hook; only source-text processing is added. |
| Design | [src/planner/selection.cpp](../../../../../src/planner/selection.cpp), [docs/selection.md](../../../../selection.md), [docs/selection_accounting.md](../../../../selection_accounting.md), [docs/selection_binding.md](../../../../selection_binding.md) |

## B0038

[Lines 98–174](../../../../../src/planner/selection.cpp#L98); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
CompiledProgram lower_winner(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Build the chosen candidate's executable operator under the remaining aggregate native work limits. |
| inputs / outputs | Admit source/model payload, reserve remaining lower/identity/replay/normalization caps, then replan a native basis or use the initial DirectCQ compiler. For a nonempty contradictory body only, DirectCQ explicitly supplies an empty operator tree. Success replaces reservations with the actual lower work and retained producer credits. |
| invariants | The original candidate and positive structural minimum are unchanged. Native replan performs its own exact source/candidate admission. Empty-body raw claims and ordinary tree inputs are preserved. Full normalized source, expression/recursion limits, options and backend remain attached; binding faults remain distinct from resources. |
| ownership | The local empty tree and candidate tree are lvalues borrowed by a const reference, so selecting geometry never deep-copies an ordinary tree. Any newly frozen program belongs to b.memory; supplied immutable native inputs remain retained. |
| failure | The existing narrow ReplanFailure translator preserves binding_mismatch and each resource dimension. Conservative delegated reservations remain spent on a failed opaque lower call. Other allocation/lower failures propagate to the existing selection entry boundary; private owners clean up. |
| cost | Source/payload scans, delegated native construction, receiving-account allocations and producer-credit debits remain. The new route decision is fixed scalar work and an empty aggregate; it adds no heap allocation, catch, wrapper, or ordinary-tree copy. Initial compiler workspace remains its documented boundary. |
| Design | [docs/physical_plans.md §Admission and routes](../../../../physical_plans.md), [docs/selection_accounting.md §Delegated budget equation](../../../../selection_accounting.md), [docs/selection_accounting.md §Exact charge primitives](../../../../selection_accounting.md), [docs/query_memory.md §Boundaries](../../../../query_memory.md) |

## B0039

[Lines 175–177](../../../../../src/planner/selection.cpp#L175); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L175-L177:sha256:ff6695b782f71f4b8e77932812dcd45ade6d09215ac562aae24906fcc0b8e6d9
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | This block close the lexical scope identified by the source span. Its attached note introduces nearby behavior: Bind one synchronous transaction and its initial preparation usage/account. |
| inputs / outputs | A scope delimiter has no call inputs or outputs; it controls which following declarations belong to the C++ namespace, class, or helper scope. |
| invariants | The braces set lexical visibility and type boundaries only. Any attached note is documentation and does not enforce behavior. |
| ownership | The delimiter and note acquire, release, or transfer no runtime object. Member lifetimes come from the enclosed type definitions. |
| failure | An unmatched or misplaced brace fails compilation; this block adds no runtime exception or resource-stop path. |
| cost | No runtime work or allocation is added. The compiler parses the scope boundary and comment. |
| Design | [src/planner/selection.cpp](../../../../../src/planner/selection.cpp), [docs/selection.md](../../../../selection.md), [docs/selection_accounting.md](../../../../selection_accounting.md), [docs/selection_binding.md](../../../../selection_binding.md) |

## B0040

[Lines 178–184](../../../../../src/planner/selection.cpp#L178); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Operation::Operation(const CandidateSnapshot& s,
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Bind one synchronous transaction and its initial preparation usage/account. |
| inputs / outputs | Borrows snapshot/source/request, resolves optional cache, retains evidence and creates Budget from carried P. |
| invariants | Required cache pointer is checked; full request/family admission follows separately. |
| ownership | Caller inputs/cache remain stable/exclusive; evidence/account are shared owners. |
| failure | Construction can fail before optional Operation exists; entry point then retains only preexisting scalar diagnostics. |
| cost | Account selection, fixed budget checks and handle copies, with optional timing start. |
| Design | [docs/selection.md](../../../../selection.md), [docs/selection_accounting.md §Delegated budget equation](../../../../selection_accounting.md), [docs/query_memory.md §Boundaries](../../../../query_memory.md) |

## B0041

[Lines 185–186](../../../../../src/planner/selection.cpp#L185); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L185-L186:sha256:a7e021efd6c818160730f006f11b07c6568501bd0cec9daab180004547de17f0
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Use the adjacent note for Operation: Validate supported request and the typed original-proof family before speculative work. Confirm behavior against the declaration and implementation; comment text alone does not enforce or prove it. |
| inputs / outputs | This comment has no inputs or outputs. It accompanies Operation; use the adjacent declaration and implementation for the actual values and result. |
| invariants | This is static guidance only. The comment cannot alter state or guarantee that its wording holds. |
| ownership | The note owns no storage and changes no lifetime; ownership and borrowing for Operation come from its actual types and implementation. |
| failure | Reading the comment has no runtime failure path. Compile or link errors, exceptions, and resource stops belong to the adjacent code. |
| cost | The comment adds no runtime instructions, allocation, clock read, counter debit, or engine hook; only source-text processing is added. |
| Design | [src/planner/selection.cpp](../../../../../src/planner/selection.cpp), [docs/selection.md](../../../../selection.md), [docs/selection_accounting.md](../../../../selection_accounting.md), [docs/selection_binding.md](../../../../selection_binding.md) |

## B0042

[Lines 187–216](../../../../../src/planner/selection.cpp#L187); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void Operation::admit() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Validate supported request and the typed original-proof family before speculative work. |
| inputs / outputs | Charges first work; rejects model/bytes/layout/tags/cache/handles, bounds retained count, exhaustion mode and slot text. A requested declaration must be valid and use PhysicalBasis holding a real CompiledProgram; unsupported caller/ordinary-plan sources are refused. |
| invariants | No new height proof or provider advancement; typed snapshot.original_proof remains authority. Unsupported byte prediction is never slot fallback. These are API admission checks, not live trace compliance or a query impossibility result. |
| ownership | Borrows immutable inputs and exclusive cache. |
| failure | Fixed Failure identifies unsupported/invalid/no-candidate/incomplete-family/resource outcomes before mutation. |
| cost | Fixed checks plus bounded cap-digit scan; original proof is retained rather than replayed anew. |
| Design | [docs/selection.md](../../../../selection.md), [docs/selection_accounting.md §Exact charge primitives](../../../../selection_accounting.md), [docs/update_patterns.md](../../../../update_patterns.md) |

## B0043

[Lines 217–218](../../../../../src/planner/selection.cpp#L217); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L217-L218:sha256:f110c34ac711cce931fccb1dddf8db43176e6b60e823b41fbb064c5de83c2e2e
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Use the adjacent note for Operation: Attach a freshly prepared runtime-bridge evidence owner exactly once. Confirm behavior against the declaration and implementation; comment text alone does not enforce or prove it. |
| inputs / outputs | This comment has no inputs or outputs. It accompanies Operation; use the adjacent declaration and implementation for the actual values and result. |
| invariants | This is static guidance only. The comment cannot alter state or guarantee that its wording holds. |
| ownership | The note owns no storage and changes no lifetime; ownership and borrowing for Operation come from its actual types and implementation. |
| failure | Reading the comment has no runtime failure path. Compile or link errors, exceptions, and resource stops belong to the adjacent code. |
| cost | The comment adds no runtime instructions, allocation, clock read, counter debit, or engine hook; only source-text processing is added. |
| Design | [src/planner/selection.cpp](../../../../../src/planner/selection.cpp), [docs/selection.md](../../../../selection.md), [docs/selection_accounting.md](../../../../selection_accounting.md), [docs/selection_binding.md](../../../../selection_binding.md) |

## B0044

[Lines 219–222](../../../../../src/planner/selection.cpp#L219); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void Operation::attach(const rank::Evidence& value) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Attach a freshly prepared runtime-bridge evidence owner exactly once. |
| inputs / outputs | Requires absent evidence, copies handle and updates timing category. |
| invariants | Caller has already accounted capture through the shared budget; attach itself adds no preparation grant or freshness proof. |
| ownership | Shares evidence/history account. |
| failure | Duplicate attach is internal_error. |
| cost | Handle copy and metadata read. |
| Design | [docs/selection.md](../../../../selection.md), [docs/selection_accounting.md §Delegated budget equation](../../../../selection_accounting.md) |

## B0045

[Lines 223–225](../../../../../src/planner/selection.cpp#L223); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
bool Operation::needs_sources() const noexcept
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Determine whether mandatory or primary slots require physical cardinality capture. |
| inputs / outputs | True for slot policy or TupleIndexSlotLimit constraint. |
| invariants | Depth/height policy alone does not request slot cardinalities. |
| ownership | Reads scalar request/variant. |
| failure | Noexcept. |
| cost | Fixed tests. |
| Design | [docs/selection.md](../../../../selection.md) |

## B0046

[Lines 226–227](../../../../../src/planner/selection.cpp#L226); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L226-L227:sha256:09fc15897b6e3fbf7e60cef8f9bc39a10d30a193970814a9c26a5883410d5419
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Use the adjacent note for Operation: Evaluate the full retained family, choose an eligible winner and privately prepare its exact artifact/cache action. Confirm behavior against the declaration and implementation; comment text alone does not enforce or prove it. |
| inputs / outputs | This comment has no inputs or outputs. It accompanies Operation; use the adjacent declaration and implementation for the actual values and result. |
| invariants | This is static guidance only. The comment cannot alter state or guarantee that its wording holds. |
| ownership | The note owns no storage and changes no lifetime; ownership and borrowing for Operation come from its actual types and implementation. |
| failure | Reading the comment has no runtime failure path. Compile or link errors, exceptions, and resource stops belong to the adjacent code. |
| cost | The comment adds no runtime instructions, allocation, clock read, counter debit, or engine hook; only source-text processing is added. |
| Design | [src/planner/selection.cpp](../../../../../src/planner/selection.cpp), [docs/selection.md](../../../../selection.md), [docs/selection_accounting.md](../../../../selection_accounting.md), [docs/selection_binding.md](../../../../selection_binding.md) |

## B0047

[Lines 228–352](../../../../../src/planner/selection.cpp#L228); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Prepared Operation::prepare() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Evaluate the full retained family, choose an eligible winner and privately prepare its exact artifact/cache action. |
| inputs / outputs | Check full source binding once; bind and pre-admit one optional declaration copy; retain conditional analyses for every candidate; perform complete C02 slot/primary assessments; exclude slot failures and unproved pattern cases; prepare/lower/cache the compatible winner and verify exact source/tree. |
| invariants | Both slot and requested pattern conditions restrict winner choice even after ranking fallback. Original P02/P07 height/family remains authority; analyses are conditional reports, not proof or live-monitor tokens. Every cache lookup follows fresh analysis and complete required assessments. An all-ineligible request is refused before unnecessary primary ranking; complete C02 assessments cover the full snapshot when invoked. |
| ownership | Prepared privately owns account-backed Data, one declaration copy, per-candidate reports/edges and any cache insertion. Reports share existing candidate/declaration owners; no source/tree or rule deep copy per candidate. |
| failure | Binding/grant/component/allocation failure or no eligible candidate destroys private preparation and preserves cache. No partial analysis/assessment prefix is successful. |
| cost | Original family ranking/lowering plus optional O(R) copy, O(N) report storage and each candidate transfer/sort/search/edge work under the same cumulative grant. No per-input runtime monitoring, row history, new catch or independent grant. |
| Design | [docs/selection.md](../../../../selection.md), [docs/selection_binding.md §Physical source and artifact frames](../../../../selection_binding.md), [docs/selection_accounting.md §Delegated budget equation](../../../../selection_accounting.md), [docs/selection_accounting.md §Atomic publication](../../../../selection_accounting.md), [docs/update_patterns.md](../../../../update_patterns.md) |

```text
const auto assess = [&](rank::Policy policy,
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Delegate one complete C02 assessment from the remaining aggregate grant. |
| inputs / outputs | Sets diagnostic stage, builds D=P+(L-U), ranks under receiving account, merges V-P, requires complete result then retains assessment. |
| invariants | Evaluation counts are diagnostic even on failed components; successful result covers the whole retained snapshot. Mandatory slots force require_evidence. Pattern filtering does not truncate the snapshot passed to C02; ranking still covers the full retained family under the residual aggregate grant. An all-ineligible request is refused before unnecessary primary ranking; complete C02 assessments cover the full snapshot when invoked. |
| ownership | Shares immutable returned Result in reserved native assessment vector. |
| failure | Merge/timing failure occurs before component failure mapping; unsuccessful result unwinds via necessary component_failure boundary. |
| cost | Complete delegated work plus fixed handle publication; no second independent preparation charge. |
| Design | [docs/selection_accounting.md §Delegated budget equation](../../../../selection_accounting.md), [docs/selection_accounting.md §Atomic publication](../../../../selection_accounting.md), [docs/update_patterns.md](../../../../update_patterns.md) |

## B0048

[Lines 353–354](../../../../../src/planner/selection.cpp#L353); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L353-L354:sha256:4b4cb933f62f6f3cfa272fec5d8b642c2820831fcdf7a9ab7e1f529880a76e00
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Use the adjacent note for Operation: Publish result/cache only after the final cooperative deadline check. Confirm behavior against the declaration and implementation; comment text alone does not enforce or prove it. |
| inputs / outputs | This comment has no inputs or outputs. It accompanies Operation; use the adjacent declaration and implementation for the actual values and result. |
| invariants | This is static guidance only. The comment cannot alter state or guarantee that its wording holds. |
| ownership | The note owns no storage and changes no lifetime; ownership and borrowing for Operation come from its actual types and implementation. |
| failure | Reading the comment has no runtime failure path. Compile or link errors, exceptions, and resource stops belong to the adjacent code. |
| cost | The comment adds no runtime instructions, allocation, clock read, counter debit, or engine hook; only source-text processing is added. |
| Design | [src/planner/selection.cpp](../../../../../src/planner/selection.cpp), [docs/selection.md](../../../../selection.md), [docs/selection_accounting.md](../../../../selection_accounting.md), [docs/selection_binding.md](../../../../selection_binding.md) |

## B0049

[Lines 355–363](../../../../../src/planner/selection.cpp#L355); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void Operation::finalize(Prepared& prepared) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Publish result/cache only after the final cooperative deadline check. |
| inputs / outputs | Samples/checks budget, saves final usage and complete diagnostic, commits funded FIFO/counters, then disables timer. |
| invariants | Public result wrapper must already exist. No throwing operation follows commit; retired native graph release cannot revoke success. |
| ownership | Prepared/Data retain all owners through barrier. |
| failure | Precommit sample can reject with cache unchanged; commit is noexcept. |
| cost | Final sample plus O(evictions) links; later payload-dependent cleanup is outside measured publication. |
| Design | [docs/selection_accounting.md §Atomic publication](../../../../selection_accounting.md), [docs/selection_accounting.md §Optional active time](../../../../selection_accounting.md) |

## B0050

[Lines 364–367](../../../../../src/planner/selection.cpp#L364); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void Operation::note(const Failure& failure) noexcept
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Copy a fixed failure category into operation diagnostics. |
| inputs / outputs | Assigns stop/resource/component/reasons. |
| invariants | No rollback, cache mutation or authority publication occurs. |
| ownership | Scalar fields only. |
| failure | Noexcept; preserves originating category. |
| cost | Fixed assignments. |
| Design | [docs/selection_accounting.md §Atomic publication](../../../../selection_accounting.md) |

## B0051

[Lines 368–370](../../../../../src/planner/selection.cpp#L368); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void Operation::note(rank::Stop stop)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Translate a ranking component stop into the selection diagnostic fields. |
| inputs / outputs | rank::Stop in; diagnostic.stop/resource/component/reasons assigned via note(Failure). |
| invariants | The mapping must exactly match component_failure, including complete→internal_error and byte_limit→resource_limit with Resource::none. |
| ownership | Only fixed enum/optional fields are copied; no query state, cache entry or undo owner is changed. |
| failure | Calls the noexcept component_diagnostic value mapper directly. component_failure separately throws that same mapped value for callers that need unwinding; no rollback/error category is removed. |
| cost | O(1) scalar enum mapping/field assignment. The previous throw-then-local-catch detour is removed; no benchmark speedup is claimed. |
| Design | [docs/selection.md](../../../../selection.md), [docs/selection_accounting.md](../../../../selection_accounting.md) |

## B0052

[Lines 371–372](../../../../../src/planner/selection.cpp#L371); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L371-L372:sha256:6ea950e414ea3f565c7122b839c3661bfca44dc3d8b8b77da267ef05c2feb322
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Use the adjacent note for finish: Capture final diagnostic elapsed/usage after success or failure. Confirm behavior against the declaration and implementation; comment text alone does not enforce or prove it. |
| inputs / outputs | This comment has no inputs or outputs. It accompanies finish; use the adjacent declaration and implementation for the actual values and result. |
| invariants | This is static guidance only. The comment cannot alter state or guarantee that its wording holds. |
| ownership | The note owns no storage and changes no lifetime; ownership and borrowing for finish come from its actual types and implementation. |
| failure | Reading the comment has no runtime failure path. Compile or link errors, exceptions, and resource stops belong to the adjacent code. |
| cost | The comment adds no runtime instructions, allocation, clock read, counter debit, or engine hook; only source-text processing is added. |
| Design | [src/planner/selection.cpp](../../../../../src/planner/selection.cpp), [docs/selection.md](../../../../selection.md), [docs/selection_accounting.md](../../../../selection_accounting.md), [docs/selection_binding.md](../../../../selection_binding.md) |

## B0053

[Lines 373–373](../../../../../src/planner/selection.cpp#L373); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void Operation::finish() noexcept
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Capture final diagnostic elapsed/usage after success or failure. |
| inputs / outputs | Budget.finish samples only if still running, then copies Usage. |
| invariants | Successful finalize disabled timing; failed cleanup can cross the soft deadline and is reported without changing the original stop. |
| ownership | Owns scalar diagnostics. |
| failure | Noexcept and does not perform a new ceiling check. |
| cost | Optional clock sample plus fixed copy. |
| Design | [docs/selection_accounting.md §Optional active time](../../../../selection_accounting.md) |

## B0054

[Lines 374–376](../../../../../src/planner/selection.cpp#L374); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L374-L376:sha256:90e1ea9b61e037ab12e1bb21e90a1e57a284d853063216168d90530b718430ec
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | This block close namespace detail. Its attached note introduces nearby behavior: Execute pure synchronous selection as an atomic result/cache transaction. |
| inputs / outputs | A scope delimiter has no call inputs or outputs; it controls which following declarations belong to the C++ namespace, class, or helper scope. |
| invariants | The braces set lexical visibility and type boundaries only. Any attached note is documentation and does not enforce behavior. |
| ownership | The delimiter and note acquire, release, or transfer no runtime object. Member lifetimes come from the enclosed type definitions. |
| failure | An unmatched or misplaced brace fails compilation; this block adds no runtime exception or resource-stop path. |
| cost | No runtime work or allocation is added. The compiler parses the scope boundary and comment. |
| Design | [src/planner/selection.cpp](../../../../../src/planner/selection.cpp), [docs/selection.md](../../../../selection.md), [docs/selection_accounting.md](../../../../selection_accounting.md), [docs/selection_binding.md](../../../../selection_binding.md) |

## B0055

[Lines 377–412](../../../../../src/planner/selection.cpp#L377); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Attempt select(const CandidateSnapshot& snapshot,
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Execute pure synchronous selection as an atomic result/cache transaction. |
| inputs / outputs | Constructs Operation, admits/prepares, creates immutable wrapper, finalizes, then publishes Attempt.selection; maps fixed/native/ordinary exceptions. |
| invariants | All possible preparation failures precede commit. No actual-owner mutation/freshness check or new proof occurs. After commit shared-handle transfer and native cleanup cannot fail. |
| ownership | Borrows inputs/cache for call; result owns native captures and shared artifacts. |
| failure | Noexcept: Failure maps fixed fields even before construction and bad_alloc maps allocation_failure. With a constructed Operation, ranking/native/Error/other catches update its diagnostics; other preconstruction categories retain default internal_error plus prior preparation metadata. |
| cost | Complete blocking work with optional clocks; failed private cleanup may be large, and successful postcommit cleanup is outside measured grant. |
| Design | [docs/selection.md](../../../../selection.md), [docs/selection_accounting.md §Atomic publication](../../../../selection_accounting.md), [docs/query_memory.md §Boundaries](../../../../query_memory.md) |

## B0056

[Lines 413–413](../../../../../src/planner/selection.cpp#L413); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L413-L413:sha256:70b35c91dce7a7d0b2c8767e851ed7eaa860feac0749a6e5256d5b2b4dc5de1e
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | This block close namespace crown::planner::selection. |
| inputs / outputs | A scope delimiter has no call inputs or outputs; it controls which following declarations belong to the C++ namespace, class, or helper scope. |
| invariants | The braces set lexical visibility and type boundaries only. Any attached note is documentation and does not enforce behavior. |
| ownership | The delimiter and note acquire, release, or transfer no runtime object. Member lifetimes come from the enclosed type definitions. |
| failure | An unmatched or misplaced brace fails compilation; this block adds no runtime exception or resource-stop path. |
| cost | No runtime work or allocation is added. The compiler parses the scope boundary and comment. |
| Design | [src/planner/selection.cpp](../../../../../src/planner/selection.cpp), [docs/selection.md](../../../../selection.md), [docs/selection_accounting.md](../../../../selection_accounting.md), [docs/selection_binding.md](../../../../selection_binding.md) |
