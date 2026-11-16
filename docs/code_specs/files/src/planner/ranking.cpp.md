# `src/planner/ranking.cpp` — block usage map

[Source](../../../../../src/planner/ranking.cpp) · [Source index](../../../README.md) · [Subsystem contracts](../../../subsystem_contracts.md) · [Reviewed primitives](../../../primitives.md)

Rank or select within a checked candidate family using exact binding, explicit evidence and bounded local score policies.

Snapshot SHA-256: `6bd317d36a5e7f216484170c7059454b99b64181eb651420085a38b5aa16fe77`. 253 lines partitioned into 51 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [ranking](../../../subsystem_contracts.md#ranking). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/ranking.md](../../../../ranking.md), [docs/selection.md](../../../../selection.md), [docs/selection_binding.md](../../../../selection_binding.md), [docs/ranking_accounting.md](../../../../ranking_accounting.md), [docs/selection_accounting.md](../../../../selection_accounting.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–11](../../../../../src/planner/ranking.cpp#L1) | Imports dependencies; declares namespace scope. | growth new · [reviewed contract](#b0001) |
| [B0002 · 12–17](../../../../../src/planner/ranking.cpp#L12) | Callable definition: CandidateScore::CandidateScore(const resource::MemoryAccount& account,MinimumHeightCandidate value) :candidate(std::move(value)),… | calls candidate, std::move, structural_key, begin · [reviewed contract](#b0002) |
| [B0003 · 18–18](../../../../../src/planner/ranking.cpp#L18) | Callable definition: const CompiledProgram& Evidence::plan() const noexcept | calls ; returns data_-&gt;plan · [reviewed contract](#b0003) |
| [B0004 · 19–19](../../../../../src/planner/ranking.cpp#L19) | Callable definition: const EvidenceVector&lt;InputWeight&gt;& Evidence::weights() const noexcept | calls ; returns data_-&gt;weights · [reviewed contract](#b0004) |
| [B0005 · 20–20](../../../../../src/planner/ranking.cpp#L20) | Callable definition: const EvidenceVector&lt;SourceCardinality&gt;& Evidence::sources() const noexcept | calls ; returns data_-&gt;sources · [reviewed contract](#b0005) |
| [B0006 · 21–21](../../../../../src/planner/ranking.cpp#L21) | Callable definition: const EvidenceVector&lt;SourceObservation&gt;& Evidence::source_observations() const noexcept | calls ; returns data_-&gt;source_observations · [reviewed contract](#b0006) |
| [B0007 · 22–22](../../../../../src/planner/ranking.cpp#L22) | Callable definition: const EvidenceIdentity& Evidence::identity() const noexcept | calls ; returns data_-&gt;identity · [reviewed contract](#b0007) |
| [B0008 · 23–23](../../../../../src/planner/ranking.cpp#L23) | Callable definition: const CaptureAccounting& Evidence::capture_accounting() const noexcept | calls ; returns data_-&gt;accounting · [reviewed contract](#b0008) |
| [B0009 · 24–24](../../../../../src/planner/ranking.cpp#L24) | Callable definition: Reasons Evidence::depth_reasons() const noexcept | calls ; returns data_-&gt;depth_reasons · [reviewed contract](#b0009) |
| [B0010 · 25–25](../../../../../src/planner/ranking.cpp#L25) | Callable definition: Reasons Evidence::memory_reasons() const noexcept | calls ; returns data_-&gt;memory_reasons · [reviewed contract](#b0010) |
| [B0011 · 26–26](../../../../../src/planner/ranking.cpp#L26) | Callable definition: std::uint64_t Evidence::denominator() const noexcept | calls ; returns data_-&gt;denominator · [reviewed contract](#b0011) |
| [B0012 · 27–27](../../../../../src/planner/ranking.cpp#L27) | Callable definition: const Usage& Evidence::preparation_usage() const noexcept | calls ; returns data_-&gt;preparation · [reviewed contract](#b0012) |
| [B0013 · 28–28](../../../../../src/planner/ranking.cpp#L28) | Callable definition: const CandidateSnapshot& Result::snapshot() const noexcept | calls ; returns data_-&gt;snapshot · [reviewed contract](#b0013) |
| [B0014 · 29–29](../../../../../src/planner/ranking.cpp#L29) | Callable definition: const MinimumHeightCandidate& Result::selected() const noexcept | calls ; returns data_-&gt;scores\[data_-&gt;selected\].candidate · [reviewed contract](#b0014) |
| [B0015 · 30–30](../../../../../src/planner/ranking.cpp#L30) | Callable definition: std::size_t Result::selected_index() const noexcept | calls ; returns data_-&gt;selected · [reviewed contract](#b0015) |
| [B0016 · 31–31](../../../../../src/planner/ranking.cpp#L31) | Callable definition: const ScoreVector&lt;CandidateScore&gt;& Result::scores() const noexcept | calls ; returns data_-&gt;scores · [reviewed contract](#b0016) |
| [B0017 · 32–32](../../../../../src/planner/ranking.cpp#L32) | Callable definition: const resource::MemoryAccount& Result::account() const & noexcept | calls ; returns data_-&gt;account · [reviewed contract](#b0017) |
| [B0018 · 33–33](../../../../../src/planner/ranking.cpp#L33) | Callable definition: const std::optional&lt;Evidence&gt;& Result::evidence() const noexcept | calls ; returns data_-&gt;evidence · [reviewed contract](#b0018) |
| [B0019 · 34–34](../../../../../src/planner/ranking.cpp#L34) | Callable definition: const Request& Result::request() const noexcept | calls ; returns data_-&gt;request · [reviewed contract](#b0019) |
| [B0020 · 35–35](../../../../../src/planner/ranking.cpp#L35) | Callable definition: Policy Result::effective_policy() const noexcept | calls ; returns data_-&gt;effective · [reviewed contract](#b0020) |
| [B0021 · 36–36](../../../../../src/planner/ranking.cpp#L36) | Callable definition: Reasons Result::fallback_reasons() const noexcept | calls ; returns data_-&gt;fallback · [reviewed contract](#b0021) |
| [B0022 · 37–37](../../../../../src/planner/ranking.cpp#L37) | Callable definition: const Usage& Result::usage() const noexcept | calls ; returns data_-&gt;usage · [reviewed contract](#b0022) |
| [B0023 · 38–38](../../../../../src/planner/ranking.cpp#L38) | declares namespace scope. |  · [reviewed contract](#b0023) |
| [B0024 · 39–47](../../../../../src/planner/ranking.cpp#L39) | Callable definition: template&lt;class C,class Q&gt; std::string binding_impl(const C& c,const Q& q,Budget& b) | calls time, check_all, std::min, binding_detail::encode; returns result · [reviewed contract](#b0024) |
| [B0025 · 48–48](../../../../../src/planner/ranking.cpp#L48) | Callable definition: std::string binding(const Catalog& c,const Query& q,Budget& b) | calls binding_impl; returns binding_impl(c,q,b) · [reviewed contract](#b0025) |
| [B0026 · 49–49](../../../../../src/planner/ranking.cpp#L49) | Callable definition: std::string binding(const program::Catalog& c,const program::Query& q,Budget& b) | calls binding_impl; returns binding_impl(c,q,b) · [reviewed contract](#b0026) |
| [B0027 · 50–59](../../../../../src/planner/ranking.cpp#L50) | Callable definition: template&lt;class C,class Q&gt; EvidenceText native_binding_impl(const C& c,const Q& q,Budget& b,const resource::MemoryAccount& account… | calls time, check_all, std::min, binding_detail::encode; returns result · [reviewed contract](#b0027) |
| [B0028 · 60–60](../../../../../src/planner/ranking.cpp#L60) | Callable definition: EvidenceText binding(const Catalog& c,const Query& q,Budget& b,const resource::MemoryAccount& account) | calls native_binding_impl; returns native_binding_impl(c,q,b,account) · [reviewed contract](#b0028) |
| [B0029 · 61–61](../../../../../src/planner/ranking.cpp#L61) | Callable definition: EvidenceText binding(const program::Catalog& c,const program::Query& q,Budget& b,const resource::MemoryAccount& account) | calls native_binding_impl; returns native_binding_impl(c,q,b,account) · [reviewed contract](#b0029) |
| [B0030 · 62–62](../../../../../src/planner/ranking.cpp#L62) | Callable definition: ScoreText score_binding(const Catalog& c,const Query& q,Budget& b,const resource::MemoryAccount& account) | calls native_binding_impl; returns native_binding_impl(c,q,b,account,resource::MemoryPurpose::scratch,score_memory_owner) · [reviewed contract](#b0030) |
| [B0031 · 63–63](../../../../../src/planner/ranking.cpp#L63) | Callable definition: ScoreText score_binding(const program::Catalog& c,const program::Query& q,Budget& b,const resource::MemoryAccount& account) | calls native_binding_impl; returns native_binding_impl(c,q,b,account,resource::MemoryPurpose::scratch,score_memory_owner) · [reviewed contract](#b0031) |
| [B0032 · 64–65](../../../../../src/planner/ranking.cpp#L64) | Explanatory comments or spacing. | source comment (unverified): // Compare equal-length inputs byte by byte until the first mismatch; · [reviewed contract](#b0032) |
| [B0033 · 66–69](../../../../../src/planner/ranking.cpp#L66) | Callable definition: bool equal_bytes(std::string_view a,std::string_view c,Budget& b) | calls size, keys; returns false; false; 1 loop sites; source comment (unverified): // Compare equal-length inputs byte by byte until the first mismatch; · [reviewed contract](#b0033) |
| [B0034 · 70–70](../../../../../src/planner/ranking.cpp#L70) | declares namespace scope. |  · [reviewed contract](#b0034) |
| [B0035 · 71–71](../../../../../src/planner/ranking.cpp#L71) | Callable definition: void require(bool value,Stop stop=Stop::internal_error) | calls ; guard void require(bool value,Stop stop=Stop::internal_error){if(!value)throw Failure{stop};} · [reviewed contract](#b0035) |
| [B0036 · 72–72](../../../../../src/planner/ranking.cpp#L72) | Callable definition: bool supported(Policy p) | calls ; returns p==Policy::height_only \|\| p==Policy::committed_input_native_depth \|\| p==Policy::tuple_index_slots · [reviewed contract](#b0036) |
| [B0037 · 73–76](../../../../../src/planner/ranking.cpp#L73) | Callable definition: bool same_context(const CandidateContext& a,const CandidateContext& c) | calls ; returns a.updates==c.updates && a.arithmetic==c.arithmetic && a.planner==c.planner && · [reviewed contract](#b0037) |
| [B0038 · 77–81](../../../../../src/planner/ranking.cpp#L77) | Callable definition: bool key_less(std::string_view a,std::string_view c,Budget& b) | calls std::min, size, keys; returns x&lt;y; a.size()&lt;c.size(); 1 loop sites · [reviewed contract](#b0038) |
| [B0039 · 82–91](../../../../../src/planner/ranking.cpp#L82) | Callable definition: Scratch&lt;std::size_t&gt; order(const FreeConnexTree& t,Budget& b,const resource::MemoryAccount& account) | calls size, out, reserve, seen; guard if(t.nodes.empty()){require(!t.root);return out;}; returns out; out; growth push_back, reserve; 2 loop sites · [reviewed contract](#b0039) |
| [B0040 · 92–93](../../../../../src/planner/ranking.cpp#L92) | Explanatory comments or spacing. | source comment (unverified): // Physical committed inserts/erases weight native-only occurrence depths. · [reviewed contract](#b0040) |
| [B0041 · 94–122](../../../../../src/planner/ranking.cpp#L94) | Callable definition: UInt depth_score(CandidateScore& score,const Evidence& e,Budget& b) | calls get_allocator, account, query, empty; guard for(const auto& input:e.plan().inputs()){b.work();require(input.occurrence.value&lt;bases.size() && !b…; returns total; growth push_back, reserve; 4 loop sites; source comment (unverified): // Physical committed inserts/erases weight native-only occurrence depths. · [reviewed contract](#b0041) |
| [B0042 · 123–145](../../../../../src/planner/ranking.cpp#L123) | Callable definition: CompiledProgram lower(const MinimumHeightCandidate& candidate,const CompiledProgram& basis,Budget& b,const resource::MemoryAccoun… | calls time, normalized, CompiledProgram::replan_into, Budget::add; guard require(out.inputs().size()==basis.inputs().size());; returns out; 1 loop sites; source comment (unverified): // On failure native blocking calls expose no partial work count. Reserve · [reviewed contract](#b0042) |
| [B0043 · 146–146](../../../../../src/planner/ranking.cpp#L146) | Callable definition: UInt project(const UInt& value,std::size_t width,Budget& b) | calls work, zero, UInt::from; returns width==0 && !value.zero()?UInt::from(1,b):value · [reviewed contract](#b0043) |
| [B0044 · 147–148](../../../../../src/planner/ranking.cpp#L147) | Explanatory comments or spacing. | source comment (unverified): // Candidate-local population upper bounds produce abstract tuple/index · [reviewed contract](#b0044) |
| [B0045 · 149–190](../../../../../src/planner/ranking.cpp#L149) | Callable definition: UInt memory_score(CandidateScore& score,const Evidence& e,Budget& b) | calls get_allocator, account, query, empty; guard require(admitted.identity().semantic_sha256==e.plan().identity().semantic_sha256 &&; returns {}; total; growth push_back, reserve; 6 loop sites; source comment (unverified): // Candidate-local population upper bounds produce abstract tuple/index · [reviewed contract](#b0045) |
| [B0046 · 191–196](../../../../../src/planner/ranking.cpp#L191) | declares namespace scope. | source comment (unverified): // namespace · [reviewed contract](#b0046) |
| [B0047 · 197–246](../../../../../src/planner/ranking.cpp#L197) | Callable definition: Attempt rank_impl(const resource::MemoryAccount* supplied,const CandidateSnapshot& snapshot,const Request& request,const std::opt… | calls preparation_usage, emplace, work, require; guard require(supported(request.policy) && (request.fallback==Fallback::height_only \|\| request.fallback==…; returns attempt; attempt; growth emplace, emplace_back, make_accounted_shared, push_back, reserve; 4 loop sites; source comment (unverified): // Admit every retained candidate before evidence fallback/scoring. Publish · [reviewed contract](#b0047) |
| [B0048 · 247–247](../../../../../src/planner/ranking.cpp#L247) | Closes surrounding scope/type. | source comment (unverified): // namespace · [reviewed contract](#b0048) |
| [B0049 · 248–250](../../../../../src/planner/ranking.cpp#L248) | Callable definition: Attempt rank(const CandidateSnapshot& snapshot,const Request& request,const std::optional&lt;Evidence&gt;& evidence) noexcept | calls rank_impl; returns rank_impl(nullptr,snapshot,request,evidence) · [reviewed contract](#b0049) |
| [B0050 · 251–252](../../../../../src/planner/ranking.cpp#L251) | Callable definition: Attempt rank_with_account(const resource::MemoryAccount& account,const CandidateSnapshot& snapshot,const Request& request, const … | calls rank_impl; returns rank_impl(&account,snapshot,request,evidence) · [reviewed contract](#b0050) |
| [B0051 · 253–253](../../../../../src/planner/ranking.cpp#L253) | Closes surrounding scope/type. | source comment (unverified): // namespace crown::planner::ranking · [reviewed contract](#b0051) |

## B0001

[Lines 1–11](../../../../../src/planner/ranking.cpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L1-L11:sha256:ba296cf81e6151d32b165b19e4255b404965bcd57d0c8177e9717d814f03b6dd
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | make #include "ranking_detail.hpp", #include "candidate_binding.hpp", #include "ranking_payload.hpp", #include "compiled_source.hpp", #include "crown/planner/lower.hpp", #include "crown/api/error.hpp", #include "crown/resource/ownership.hpp", #include &lt;algorithm&gt;, #include &lt;new&gt; available to src/planner/ranking.cpp; open crown::planner::ranking. |
| inputs / outputs | Preprocessor directives resolve compile-time declarations. This block has no runtime call inputs or result. |
| invariants | Includes, namespace openings, aliases, and forward declarations determine C++ name visibility and type availability; they do not validate planner data or grant proof authority. |
| ownership | No runtime object is owned by the include or scope directives. Any state belongs to the types and functions declared after them. |
| failure | A missing header, incompatible declaration, or ill-formed type use fails during compilation; runtime failures remain in the called code. |
| cost | Adds preprocessing, parsing, and any later template-instantiation work in this translation unit. It adds no runtime timer, counter, branch, or allocation. |
| Design | [src/planner/ranking.cpp](../../../../../src/planner/ranking.cpp), [docs/ranking.md](../../../../ranking.md), [docs/selection_accounting.md](../../../../selection_accounting.md) |

## B0002

[Lines 12–17](../../../../../src/planner/ranking.cpp#L12); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
CandidateScore::CandidateScore(const resource::MemoryAccount& account,MinimumHeightCandidate value)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Prepare accounted score storage for one admitted candidate. |
| inputs / outputs | Moves the handle, copies its full key, reads height and starts decimal 0/1/0 fields and empty accounted vectors. |
| invariants | Candidate must already be valid; score initialization does not independently prove its query/tree. |
| ownership | Owns key/text/vectors under score account while candidate shares preexisting immutable owners. |
| failure | Allocation/candidate access can throw before the private score is appended; member RAII frees partial storage. |
| cost | O(key bytes) copy plus fixed owner/text initialization and actual allocator/control costs. |
| Design | [docs/ranking.md](../../../../ranking.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0003

[Lines 18–18](../../../../../src/planner/ranking.cpp#L18); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
const CompiledProgram& Evidence::plan() const noexcept
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Expose the captured compiled program and its original account. |
| inputs / outputs | Returns the captured compiled program and its original account directly from immutable payload. |
| invariants | Factory-produced EvidenceData is nonnull; copy-like moves retain both handles. Facts remain as-of capture; this getter performs no current-owner check. |
| ownership | Borrow valid while some Evidence payload owner survives; getter itself retains no extra owner. |
| failure | Noexcept direct access under factory invariants; no revalidation/current-owner check. |
| cost | Fixed field/reference access; no traversal, allocation or proof work. |
| Design | [docs/ranking.md](../../../../ranking.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0004

[Lines 19–19](../../../../../src/planner/ranking.cpp#L19); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
const EvidenceVector<InputWeight>& Evidence::weights() const noexcept
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Expose the captured physical input-frequency vector. |
| inputs / outputs | Returns the captured physical input-frequency vector directly from immutable payload. |
| invariants | Factory-produced EvidenceData is nonnull; copy-like moves retain both handles. Facts remain as-of capture; this getter performs no current-owner check. |
| ownership | Borrow valid while some Evidence payload owner survives; getter itself retains no extra owner. |
| failure | Noexcept direct access under factory invariants; no revalidation/current-owner check. |
| cost | Fixed field/reference access; no traversal, allocation or proof work. |
| Design | [docs/ranking.md](../../../../ranking.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0005

[Lines 20–20](../../../../../src/planner/ranking.cpp#L20); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
const EvidenceVector<SourceCardinality>& Evidence::sources() const noexcept
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Expose the available source cardinalities. |
| inputs / outputs | Returns the available source cardinalities directly from immutable payload. |
| invariants | Factory-produced EvidenceData is nonnull; copy-like moves retain both handles. Facts remain as-of capture; this getter performs no current-owner check. |
| ownership | Borrow valid while some Evidence payload owner survives; getter itself retains no extra owner. |
| failure | Noexcept direct access under factory invariants; no revalidation/current-owner check. |
| cost | Fixed field/reference access; no traversal, allocation or proof work. |
| Design | [docs/ranking.md](../../../../ranking.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0006

[Lines 21–21](../../../../../src/planner/ranking.cpp#L21); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
const EvidenceVector<SourceObservation>& Evidence::source_observations() const noexcept
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Expose the per-source availability observations. |
| inputs / outputs | Returns the per-source availability observations directly from immutable payload. |
| invariants | Factory-produced EvidenceData is nonnull; copy-like moves retain both handles. Facts remain as-of capture; this getter performs no current-owner check. |
| ownership | Borrow valid while some Evidence payload owner survives; getter itself retains no extra owner. |
| failure | Noexcept direct access under factory invariants; no revalidation/current-owner check. |
| cost | Fixed field/reference access; no traversal, allocation or proof work. |
| Design | [docs/ranking.md](../../../../ranking.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0007

[Lines 22–22](../../../../../src/planner/ranking.cpp#L22); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
const EvidenceIdentity& Evidence::identity() const noexcept
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Expose the as-of owner/interval stamp. |
| inputs / outputs | Returns the as-of owner/interval stamp directly from immutable payload. |
| invariants | Factory-produced EvidenceData is nonnull; copy-like moves retain both handles. Facts remain as-of capture; this getter performs no current-owner check. |
| ownership | Borrow valid while some Evidence payload owner survives; getter itself retains no extra owner. |
| failure | Noexcept direct access under factory invariants; no revalidation/current-owner check. |
| cost | Fixed field/reference access; no traversal, allocation or proof work. |
| Design | [docs/ranking.md](../../../../ranking.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0008

[Lines 23–23](../../../../../src/planner/ranking.cpp#L23); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
const CaptureAccounting& Evidence::capture_accounting() const noexcept
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Expose the capture request/consumption record. |
| inputs / outputs | Returns the capture request/consumption record directly from immutable payload. |
| invariants | Factory-produced EvidenceData is nonnull; copy-like moves retain both handles. Facts remain as-of capture; this getter performs no current-owner check. |
| ownership | Borrow valid while some Evidence payload owner survives; getter itself retains no extra owner. |
| failure | Noexcept direct access under factory invariants; no revalidation/current-owner check. |
| cost | Fixed field/reference access; no traversal, allocation or proof work. |
| Design | [docs/ranking.md](../../../../ranking.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0009

[Lines 24–24](../../../../../src/planner/ranking.cpp#L24); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Reasons Evidence::depth_reasons() const noexcept
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Expose the depth-policy ineligibility mask. |
| inputs / outputs | Returns the depth-policy ineligibility mask directly from immutable payload. |
| invariants | Factory-produced EvidenceData is nonnull; copy-like moves retain both handles. Facts remain as-of capture; this getter performs no current-owner check. |
| ownership | Copies fixed scalar value; referenced payload stays with handle. |
| failure | Noexcept direct access under factory invariants; no revalidation/current-owner check. |
| cost | Fixed field/reference access; no traversal, allocation or proof work. |
| Design | [docs/ranking.md](../../../../ranking.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0010

[Lines 25–25](../../../../../src/planner/ranking.cpp#L25); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Reasons Evidence::memory_reasons() const noexcept
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Expose the source-slot-policy ineligibility mask. |
| inputs / outputs | Returns the source-slot-policy ineligibility mask directly from immutable payload. |
| invariants | Factory-produced EvidenceData is nonnull; copy-like moves retain both handles. Facts remain as-of capture; this getter performs no current-owner check. |
| ownership | Copies fixed scalar value; referenced payload stays with handle. |
| failure | Noexcept direct access under factory invariants; no revalidation/current-owner check. |
| cost | Fixed field/reference access; no traversal, allocation or proof work. |
| Design | [docs/ranking.md](../../../../ranking.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0011

[Lines 26–26](../../../../../src/planner/ranking.cpp#L26); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::uint64_t Evidence::denominator() const noexcept
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Expose the shared physical committed-input denominator. |
| inputs / outputs | Returns the shared physical committed-input denominator directly from immutable payload. |
| invariants | Factory-produced EvidenceData is nonnull; copy-like moves retain both handles. Facts remain as-of capture; this getter performs no current-owner check. |
| ownership | Copies fixed scalar value; referenced payload stays with handle. |
| failure | Noexcept direct access under factory invariants; no revalidation/current-owner check. |
| cost | Fixed field/reference access; no traversal, allocation or proof work. |
| Design | [docs/ranking.md](../../../../ranking.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0012

[Lines 27–27](../../../../../src/planner/ranking.cpp#L27); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
const Usage& Evidence::preparation_usage() const noexcept
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Expose the usage already spent preparing evidence. |
| inputs / outputs | Returns the usage already spent preparing evidence directly from immutable payload. |
| invariants | Factory-produced EvidenceData is nonnull; copy-like moves retain both handles. Facts remain as-of capture; this getter performs no current-owner check. |
| ownership | Borrow valid while some Evidence payload owner survives; getter itself retains no extra owner. |
| failure | Noexcept direct access under factory invariants; no revalidation/current-owner check. |
| cost | Fixed field/reference access; no traversal, allocation or proof work. |
| Design | [docs/ranking.md](../../../../ranking.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0013

[Lines 28–28](../../../../../src/planner/ranking.cpp#L28); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
const CandidateSnapshot& Result::snapshot() const noexcept
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Expose the exact retained prefix being ranked. |
| inputs / outputs | Returns the exact retained prefix being ranked directly from immutable payload. |
| invariants | Factory-produced handles are nonnull and moves preserve source ownership; selected index refers to a complete nonempty admitted vector. |
| ownership | Borrow valid while some Result payload owner survives; getter itself retains no extra owner. |
| failure | Noexcept direct access under factory invariants; no revalidation/current-owner check. |
| cost | Fixed field/reference access; no traversal, allocation or proof work. |
| Design | [docs/ranking.md](../../../../ranking.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0014

[Lines 29–29](../../../../../src/planner/ranking.cpp#L29); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
const MinimumHeightCandidate& Result::selected() const noexcept
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Expose the chosen candidate within the complete score vector. |
| inputs / outputs | Returns the chosen candidate within the complete score vector directly from immutable payload. |
| invariants | Factory-produced handles are nonnull and moves preserve source ownership; selected index refers to a complete nonempty admitted vector. |
| ownership | Borrow valid while some Result payload owner survives; getter itself retains no extra owner. |
| failure | Noexcept direct access under factory invariants; no revalidation/current-owner check. |
| cost | Fixed field/reference access; no traversal, allocation or proof work. |
| Design | [docs/ranking.md](../../../../ranking.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0015

[Lines 30–30](../../../../../src/planner/ranking.cpp#L30); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::size_t Result::selected_index() const noexcept
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Expose the selected score-vector index. |
| inputs / outputs | Returns the selected score-vector index directly from immutable payload. |
| invariants | Factory-produced handles are nonnull and moves preserve source ownership; selected index refers to a complete nonempty admitted vector. |
| ownership | Copies fixed scalar value; referenced payload stays with handle. |
| failure | Noexcept direct access under factory invariants; no revalidation/current-owner check. |
| cost | Fixed field/reference access; no traversal, allocation or proof work. |
| Design | [docs/ranking.md](../../../../ranking.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0016

[Lines 31–31](../../../../../src/planner/ranking.cpp#L31); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
const ScoreVector<CandidateScore>& Result::scores() const noexcept
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Expose all admitted candidate score explanations. |
| inputs / outputs | Returns all admitted candidate score explanations directly from immutable payload. |
| invariants | Factory-produced handles are nonnull and moves preserve source ownership; selected index refers to a complete nonempty admitted vector. |
| ownership | Borrow valid while some Result payload owner survives; getter itself retains no extra owner. |
| failure | Noexcept direct access under factory invariants; no revalidation/current-owner check. |
| cost | Fixed field/reference access; no traversal, allocation or proof work. |
| Design | [docs/ranking.md](../../../../ranking.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0017

[Lines 32–32](../../../../../src/planner/ranking.cpp#L32); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
const resource::MemoryAccount& Result::account() const & noexcept
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Expose the receiving score-storage account. |
| inputs / outputs | Returns the receiving score-storage account directly from immutable payload. |
| invariants | Factory-produced handles are nonnull and moves preserve source ownership; selected index refers to a complete nonempty admitted vector. |
| ownership | Borrow valid while some Result payload owner survives; getter itself retains no extra owner. |
| failure | Noexcept direct access under factory invariants; no revalidation/current-owner check. |
| cost | Fixed field/reference access; no traversal, allocation or proof work. |
| Design | [docs/ranking.md](../../../../ranking.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0018

[Lines 33–33](../../../../../src/planner/ranking.cpp#L33); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
const std::optional<Evidence>& Result::evidence() const noexcept
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Expose the retained optional as-of evidence. |
| inputs / outputs | Returns the retained optional as-of evidence directly from immutable payload. |
| invariants | Factory-produced handles are nonnull and moves preserve source ownership; selected index refers to a complete nonempty admitted vector. |
| ownership | Borrow valid while some Result payload owner survives; getter itself retains no extra owner. |
| failure | Noexcept direct access under factory invariants; no revalidation/current-owner check. |
| cost | Fixed field/reference access; no traversal, allocation or proof work. |
| Design | [docs/ranking.md](../../../../ranking.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0019

[Lines 34–34](../../../../../src/planner/ranking.cpp#L34); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
const Request& Result::request() const noexcept
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Expose the original policy/fallback/limits request. |
| inputs / outputs | Returns the original policy/fallback/limits request directly from immutable payload. |
| invariants | Factory-produced handles are nonnull and moves preserve source ownership; selected index refers to a complete nonempty admitted vector. |
| ownership | Borrow valid while some Result payload owner survives; getter itself retains no extra owner. |
| failure | Noexcept direct access under factory invariants; no revalidation/current-owner check. |
| cost | Fixed field/reference access; no traversal, allocation or proof work. |
| Design | [docs/ranking.md](../../../../ranking.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0020

[Lines 35–35](../../../../../src/planner/ranking.cpp#L35); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Policy Result::effective_policy() const noexcept
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Expose the actual scoring policy after explicit fallback. |
| inputs / outputs | Returns the actual scoring policy after explicit fallback directly from immutable payload. |
| invariants | Factory-produced handles are nonnull and moves preserve source ownership; selected index refers to a complete nonempty admitted vector. |
| ownership | Copies fixed scalar value; referenced payload stays with handle. |
| failure | Noexcept direct access under factory invariants; no revalidation/current-owner check. |
| cost | Fixed field/reference access; no traversal, allocation or proof work. |
| Design | [docs/ranking.md](../../../../ranking.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0021

[Lines 36–36](../../../../../src/planner/ranking.cpp#L36); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Reasons Result::fallback_reasons() const noexcept
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Expose the recorded reasons for height fallback. |
| inputs / outputs | Returns the recorded reasons for height fallback directly from immutable payload. |
| invariants | Factory-produced handles are nonnull and moves preserve source ownership; selected index refers to a complete nonempty admitted vector. |
| ownership | Copies fixed scalar value; referenced payload stays with handle. |
| failure | Noexcept direct access under factory invariants; no revalidation/current-owner check. |
| cost | Fixed field/reference access; no traversal, allocation or proof work. |
| Design | [docs/ranking.md](../../../../ranking.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0022

[Lines 37–37](../../../../../src/planner/ranking.cpp#L37); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
const Usage& Result::usage() const noexcept
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Expose the final cumulative processing usage. |
| inputs / outputs | Returns the final cumulative processing usage directly from immutable payload. |
| invariants | Factory-produced handles are nonnull and moves preserve source ownership; selected index refers to a complete nonempty admitted vector. |
| ownership | Borrow valid while some Result payload owner survives; getter itself retains no extra owner. |
| failure | Noexcept direct access under factory invariants; no revalidation/current-owner check. |
| cost | Fixed field/reference access; no traversal, allocation or proof work. |
| Design | [docs/ranking.md](../../../../ranking.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0023

[Lines 38–38](../../../../../src/planner/ranking.cpp#L38); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L38-L38:sha256:5535809b42b9d97cdfea935b5d84662804aaab9873ce9d79d846ab3ec8a625cb
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | open detail in src/planner/ranking.cpp. |
| inputs / outputs | This namespace, scope, or declaration boundary has no runtime call inputs or outputs. |
| invariants | It changes compile-time visibility or declaration identity only; attached comments do not enforce or prove the described behavior. |
| ownership | This span creates no runtime owner. Later object definitions and calls determine storage and lifetimes. |
| failure | An invalid declaration or scope boundary fails compilation; no runtime exception or resource stop comes from this span. |
| cost | Compile-time parsing and preprocessor bookkeeping only; no runtime branch, allocation, clock read, counter debit, or engine hook. |
| Design | [src/planner/ranking.cpp](../../../../../src/planner/ranking.cpp), [docs/ranking.md](../../../../ranking.md), [docs/selection_accounting.md](../../../../selection_accounting.md) |

## B0024

[Lines 39–47](../../../../../src/planner/ranking.cpp#L39); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
template<class C,class Q> std::string binding_impl(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Encode the complete ranking model binding under remaining key/payload limits. |
| inputs / outputs | Typed Catalog/Query or native model views plus Budget return an ordinary owning std::string of complete binding bytes; this helper has no receiving-account argument. |
| invariants | Checks existing usage before subtraction, caps encoded bytes by min(remaining key,remaining payload), and debits full result payload before return. |
| ownership | Ordinary std::string owns bytes; input model remains borrowed. |
| failure | Binding Limit becomes ranking Failure; allocation propagates. Work/key debits can survive a later byte/clock failure. |
| cost | Whole model encoding including nested variable-length strings/Decimal formatting; capacity/allocator costs differ from logical bytes. |
| Design | [docs/ranking.md](../../../../ranking.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0025

[Lines 48–48](../../../../../src/planner/ranking.cpp#L48); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::string binding(const Catalog&
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Delegate ordinary typed-model binding. |
| inputs / outputs | Selects binding implementation and fixed memory purpose/attribution. |
| invariants | Retains exact complete binding bytes; digest/alpha similarity is insufficient. |
| ownership | Returned string owns bytes using the chosen ordinary/receiving account path. |
| failure | Propagates precise binding/budget/allocation failures to rank boundary. |
| cost | Fixed delegation plus full encoder/copy/allocator costs. |
| Design | [docs/ranking.md](../../../../ranking.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0026

[Lines 49–49](../../../../../src/planner/ranking.cpp#L49); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::string binding(const program::Catalog&
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Delegate ordinary native-view binding. |
| inputs / outputs | Selects binding implementation and fixed memory purpose/attribution. |
| invariants | Retains exact complete binding bytes; digest/alpha similarity is insufficient. |
| ownership | Returned string owns bytes using the chosen ordinary/receiving account path. |
| failure | Propagates precise binding/budget/allocation failures to rank boundary. |
| cost | Fixed delegation plus full encoder/copy/allocator costs. |
| Design | [docs/ranking.md](../../../../ranking.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0027

[Lines 50–59](../../../../../src/planner/ranking.cpp#L50); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
template<class C,class Q> EvidenceText native_binding_impl(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Encode the complete ranking model binding under remaining key/payload limits. |
| inputs / outputs | Typed Catalog/Query or native views plus Budget, receiving account and optional purpose/attribution return complete OwnerAllocator binding bytes; defaults are capture/evidence owner9, score callers choose scratch/score owner11. |
| invariants | Checks existing usage before subtraction, caps encoded bytes by min(remaining key,remaining payload), and debits full result payload before return. |
| ownership | Returned OwnerAllocator string retains the supplied account/purpose/attribution; source model views are borrowed only during encoding. |
| failure | Binding Limit becomes ranking Failure; allocation propagates. Work/key debits can survive a later byte/clock failure. |
| cost | Full binding traversal/output bytes with account-backed string capacity growth. Decimal encoding uses InlineDecimal and fixed at-most41-character scratch rather than ordinary Decimal/string export. Logical byte charges exclude capacity/control overhead; cooperative time is sampled around the whole encode. |
| Design | [docs/ranking.md](../../../../ranking.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0028

[Lines 60–60](../../../../../src/planner/ranking.cpp#L60); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
EvidenceText binding(const Catalog&
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Delegate capture-accounted typed-model binding. |
| inputs / outputs | Selects binding implementation and fixed memory purpose/attribution. |
| invariants | Retains exact complete binding bytes; digest/alpha similarity is insufficient. |
| ownership | Returned string owns bytes using the chosen ordinary/receiving account path. |
| failure | Propagates precise binding/budget/allocation failures to rank boundary. |
| cost | Fixed delegation plus full encoder/copy/allocator costs. |
| Design | [docs/ranking.md](../../../../ranking.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0029

[Lines 61–61](../../../../../src/planner/ranking.cpp#L61); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
EvidenceText binding(const program::Catalog&
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Delegate capture-accounted native-view binding. |
| inputs / outputs | Selects binding implementation and fixed memory purpose/attribution. |
| invariants | Retains exact complete binding bytes; digest/alpha similarity is insufficient. |
| ownership | Returned string owns bytes using the chosen ordinary/receiving account path. |
| failure | Propagates precise binding/budget/allocation failures to rank boundary. |
| cost | Fixed delegation plus full encoder/copy/allocator costs. |
| Design | [docs/ranking.md](../../../../ranking.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0030

[Lines 62–62](../../../../../src/planner/ranking.cpp#L62); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
ScoreText score_binding(const Catalog&
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Delegate score-attributed scratch typed-model binding. |
| inputs / outputs | Selects binding implementation and fixed memory purpose/attribution. |
| invariants | Retains exact complete binding bytes; digest/alpha similarity is insufficient. |
| ownership | Returned string owns bytes using the chosen ordinary/receiving account path. |
| failure | Propagates precise binding/budget/allocation failures to rank boundary. |
| cost | Fixed delegation plus full encoder/copy/allocator costs. |
| Design | [docs/ranking.md](../../../../ranking.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0031

[Lines 63–63](../../../../../src/planner/ranking.cpp#L63); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
ScoreText score_binding(const program::Catalog&
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Delegate score-attributed scratch native-view binding. |
| inputs / outputs | Selects binding implementation and fixed memory purpose/attribution. |
| invariants | Retains exact complete binding bytes; digest/alpha similarity is insufficient. |
| ownership | Returned string owns bytes using the chosen ordinary/receiving account path. |
| failure | Propagates precise binding/budget/allocation failures to rank boundary. |
| cost | Fixed delegation plus full encoder/copy/allocator costs. |
| Design | [docs/ranking.md](../../../../ranking.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0032

[Lines 64–65](../../../../../src/planner/ranking.cpp#L64); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L64-L65:sha256:4579a8b3a313bf9f05a8f9bd9a3527d283b47d2807a8647e5b25d17e985451d0
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Use the adjacent note for equal_bytes: Compare equal-length inputs byte by byte until the first mismatch; equality requires all positions. Length mismatch skips byte traversal. Confirm behavior against the declaration and implementation; comment text alone does not enforce or prove it. |
| inputs / outputs | This comment has no inputs or outputs. It accompanies equal_bytes; use the adjacent declaration and implementation for the actual values and result. |
| invariants | This is static guidance only. The comment cannot alter state or guarantee that its wording holds. |
| ownership | The note owns no storage and changes no lifetime; ownership and borrowing for equal_bytes come from its actual types and implementation. |
| failure | Reading the comment has no runtime failure path. Compile or link errors, exceptions, and resource stops belong to the adjacent code. |
| cost | The comment adds no runtime instructions, allocation, clock read, counter debit, or engine hook; only source-text processing is added. |
| Design | [src/planner/ranking.cpp](../../../../../src/planner/ranking.cpp), [docs/ranking.md](../../../../ranking.md), [docs/selection_accounting.md](../../../../selection_accounting.md) |

## B0033

[Lines 66–69](../../../../../src/planner/ranking.cpp#L66); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
bool equal_bytes(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Compare complete exact binding/key strings. |
| inputs / outputs | Length mismatch returns false; otherwise charges each examined byte until mismatch/equality. |
| invariants | No hash-only equality; a length mismatch does not charge byte traversal. |
| ownership | Borrows string views and mutates only budget. |
| failure | Budget work/key/time failure can interrupt after prior debits. |
| cost | O(examined prefix bytes), constant unequal-length fast path. |
| Design | [docs/ranking.md](../../../../ranking.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0034

[Lines 70–70](../../../../../src/planner/ranking.cpp#L70); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L70-L70:sha256:cf04d99c0f5d3521f67f7c587d20dd3592a5024b903529e1e468844f7fae8135
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | open anonymous helper namespace in src/planner/ranking.cpp. |
| inputs / outputs | This namespace, scope, or declaration boundary has no runtime call inputs or outputs. |
| invariants | It changes compile-time visibility or declaration identity only; attached comments do not enforce or prove the described behavior. |
| ownership | This span creates no runtime owner. Later object definitions and calls determine storage and lifetimes. |
| failure | An invalid declaration or scope boundary fails compilation; no runtime exception or resource stop comes from this span. |
| cost | Compile-time parsing and preprocessor bookkeeping only; no runtime branch, allocation, clock read, counter debit, or engine hook. |
| Design | [src/planner/ranking.cpp](../../../../../src/planner/ranking.cpp), [docs/ranking.md](../../../../ranking.md), [docs/selection_accounting.md](../../../../selection_accounting.md) |

## B0035

[Lines 71–71](../../../../../src/planner/ranking.cpp#L71); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void require(bool value,Stop
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Check a local ranker invariant or typed admission condition. |
| inputs / outputs | False throws Failure with requested stop, default internal_error. |
| invariants | No diagnostic string, nested recovery or implicit authority conversion. |
| ownership | Borrows/copies scalar condition/stop. |
| failure | Throws only on false. |
| cost | Fixed ordinary branch; exception path is outside successful ranking. |
| Design | [docs/ranking.md](../../../../ranking.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0036

[Lines 72–72](../../../../../src/planner/ranking.cpp#L72); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
bool supported(Policy p)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Recognize the closed built-in score policies. |
| inputs / outputs | Returns membership in height/depth/slot policies. |
| invariants | Caller-provided enum values cannot invent a model. |
| ownership | Scalar input/output. |
| failure | Returns false for unsupported values. |
| cost | Fixed comparisons. |
| Design | [docs/ranking.md](../../../../ranking.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0037

[Lines 73–76](../../../../../src/planner/ranking.cpp#L73); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
bool same_context(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Compare all current candidate-policy namespace fields. |
| inputs / outputs | Tests update/arithmetic/planner/optimization/cost-model/canonicalization strings. |
| invariants | This is context equality, not exact Catalog/Query binding or proof verification. |
| ownership | Borrows context strings. |
| failure | No local failure translation. |
| cost | Sum of inspected string lengths; no explicit per-byte budget in this helper. |
| Design | [docs/ranking.md](../../../../ranking.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0038

[Lines 77–81](../../../../../src/planner/ranking.cpp#L77); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
bool key_less(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Order ties by unsigned complete structural bytes. |
| inputs / outputs | Charges two key bytes per examined character then compares unsigned byte values/lengths. |
| invariants | Locale/char signedness cannot change deterministic tie order. |
| ownership | Borrows full keys; no stored views escape. |
| failure | Logical resource failure preserves already spent debits. |
| cost | O(common prefix bytes), then constant comparison. |
| Design | [docs/ranking.md](../../../../ranking.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0039

[Lines 82–91](../../../../../src/planner/ranking.cpp#L82); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Scratch<std::size_t> order(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Create a validated breadth-first node order for score passes. |
| inputs / outputs | Checks root/child ranges, repeated reachability and complete reachability; charges vector slots/scope scans. |
| invariants | Input is already typed/P02-checked; this traversal does not replace the query proof or all tree-rule checks. |
| ownership | Scratch vectors use receiving MemoryAllocator and retain no node borrows after return. |
| failure | Structural mismatch throws internal Failure; allocation/resource failure returns through boundary. |
| cost | O(nodes+edges+scope widths) traversal with node-sized order/seen scratch; allocator capacity separately accounted. |
| Design | [docs/ranking.md](../../../../ranking.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0040

[Lines 92–93](../../../../../src/planner/ranking.cpp#L92); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L92-L93:sha256:90a30789dbd5d19a5d54fd8779586061c37041aa3f7a4eaaf7e7aec07c1bd289
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Use the adjacent note for depth_score: Physical committed inserts/erases weight native-only occurrence depths. This workload proxy is neither measured maintenance work nor elapsed time. Confirm behavior against the declaration and implementation; comment text alone does not enforce or prove it. |
| inputs / outputs | This comment has no inputs or outputs. It accompanies depth_score; use the adjacent declaration and implementation for the actual values and result. |
| invariants | This is static guidance only. The comment cannot alter state or guarantee that its wording holds. |
| ownership | The note owns no storage and changes no lifetime; ownership and borrowing for depth_score come from its actual types and implementation. |
| failure | Reading the comment has no runtime failure path. Compile or link errors, exceptions, and resource stops belong to the adjacent code. |
| cost | The comment adds no runtime instructions, allocation, clock read, counter debit, or engine hook; only source-text processing is added. |
| Design | [src/planner/ranking.cpp](../../../../../src/planner/ranking.cpp), [docs/ranking.md](../../../../ranking.md), [docs/selection_accounting.md](../../../../selection_accounting.md) |

## B0041

[Lines 94–122](../../../../../src/planner/ranking.cpp#L94); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
UInt depth_score(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Compute the eligible committed-input/native-depth score of the executable operator while retaining original structural proof height. |
| inputs / outputs | For an ordinary route, map occurrences to physical bases and propagate native-only depths. For a nonempty contradiction, traverse canonical empty operator geometry and allocate no body-sized occurrence map. In both cases retain all physical table insert/erase weights, table depth sums/contributions and the actual common positive denominator W; a constant operator yields exact 0/W with empty occurrence depths. |
| invariants | Native roots contribute depth one and generalized nodes add zero. The result does not overwrite score.height, candidate height or the original minimum proof. Eligible evidence is checked by rank_impl before this function; a missing or zero census cannot be manufactured into valid 0/1 or 0/0 facts. |
| ownership | Geometry is borrowed from one of two lvalues; no candidate tree copy occurs. Scratch and retained decimal/table explanation fields use the score account. The candidate and evidence owners remain immutable. |
| failure | Existing input/map/shape checks and fixed-width arithmetic/resource failures abort the entire private rank result. There is no new catch or successful fallback inside this primitive. |
| cost | Ordinary geometry/input/table scans remain linear plus fixed-capacity integer operations and decimal output allocations. Constant operators skip body-node and occurrence scratch but still scan physical weights, format per-table zeros and retain W. The value is an input-frequency proxy, not elapsed or measured maintenance work. |
| Design | [docs/ranking.md §Exact score reconstruction](../../../../ranking.md), [docs/ranking.md §Budgets and availability](../../../../ranking.md), [docs/ranking_accounting.md](../../../../ranking_accounting.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0042

[Lines 123–145](../../../../../src/planner/ranking.cpp#L123); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
CompiledProgram lower(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Build a candidate-local modeled plan in the receiving account. |
| inputs / outputs | Passes remaining physical/identity/replay/normalization allowances to replan_into; verifies occurrence/base correspondence. |
| invariants | Before the blocking call, conservatively reserves complete remaining delegated allowances; on success replaces reservations with returned lowering work and recorded source identity/replay/normalization credits. Native replan aliases admitted immutable source and does not rerun those producer passes. |
| ownership | New compiled program uses receiving account; basis/candidate remain immutable retained sources. |
| failure | On failed blocking call delegated counters stay conservatively exhausted; typed errors map at rank boundary. |
| cost | Blocking exact-binding serialization/comparison, candidate tree/report freezing, physical instruction/token construction, full physical-digest serialization/hash and receiving-account allocation. Identity/binding-replay/normalization counters debit retained source work credits rather than rerunning those passes. Cooperative clock checks do not impose a hard CPU deadline. |
| Design | [docs/ranking.md](../../../../ranking.md), [docs/query_memory.md](../../../../query_memory.md), [src/ir/program_replan.inc](../../../../../src/ir/program_replan.inc), [src/ir/program.cpp](../../../../../src/ir/program.cpp), [docs/ranking_accounting.md §Native capture and lowering boundaries](../../../../ranking_accounting.md) |

## B0043

[Lines 146–146](../../../../../src/planner/ranking.cpp#L146); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
UInt project(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Bound projection cardinality, including nullary tuples. |
| inputs / outputs | Returns one for positive population projected to zero fields; otherwise same UInt. |
| invariants | Empty projection has at most one tuple and zero input stays zero. |
| ownership | Inline bounded integer by value. |
| failure | Work/bit ceiling can stop processing. |
| cost | One work charge, at most16-limb zero test and conversion. |
| Design | [docs/ranking.md](../../../../ranking.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0044

[Lines 147–148](../../../../../src/planner/ranking.cpp#L147); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L147-L148:sha256:666d5a3dae30e930fedade52c9f446692b50f61e34f5b216c2418618ef4ff1cd
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Use the adjacent note for memory_score: Candidate-local population upper bounds produce abstract tuple/index slots. Relowering and scratch have real costs; the score is not byte usage. Confirm behavior against the declaration and implementation; comment text alone does not enforce or prove it. |
| inputs / outputs | This comment has no inputs or outputs. It accompanies memory_score; use the adjacent declaration and implementation for the actual values and result. |
| invariants | This is static guidance only. The comment cannot alter state or guarantee that its wording holds. |
| ownership | The note owns no storage and changes no lifetime; ownership and borrowing for memory_score come from its actual types and implementation. |
| failure | Reading the comment has no runtime failure path. Compile or link errors, exceptions, and resource stops belong to the adjacent code. |
| cost | The comment adds no runtime instructions, allocation, clock read, counter debit, or engine hook; only source-text processing is added. |
| Design | [src/planner/ranking.cpp](../../../../../src/planner/ranking.cpp), [docs/ranking.md](../../../../ranking.md), [docs/selection_accounting.md](../../../../selection_accounting.md) |

## B0045

[Lines 149–190](../../../../../src/planner/ranking.cpp#L149); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
UInt memory_score(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Compute a candidate-local abstract tuple/index-slot bound, including an exact zero for an admitted empty executable operator. |
| inputs / outputs | Choose borrowed executable geometry, admit complete source payload, lower/replan into the score account, compare all four source identity hashes, admit compiled payload and retain modeled_plan. Only after those steps may a nonempty contradiction format slots="0" and return with empty populations/slot_terms. Ordinary routes then propagate source bounds and width-plus-one relation/index terms. |
| invariants | Candidate structural height and original proof remain unchanged. rank_impl performs candidate and evidence eligibility before entry. Zero cannot skip source binding, finite work, payload, identity or modeled-plan admission. The slot proxy excludes source/metadata/capacity/peak coexistence and is not an allocator byte bound. |
| ownership | Expected geometry is a const borrow of lvalues, avoiding ordinary-tree copies. The retained modeled program and explanation use the score account; ordinary population/source scratch is funded there. Constant operators avoid unused source-sized population scratch after mandatory admission. |
| failure | Existing lower/identity/payload/arithmetic/resource failures reject the whole ranking result before publication. The early return adds no catch, rollback mechanism or new state; existing private RAII handles unwinding. |
| cost | Source/compiled-payload walks, exact binding/digest work, native allocations and retained producer-credit debits still occur for constants; formatting zero also charges normal integer/output work. Ordinary node/edge/source/relation/index scans and fixed-capacity arithmetic remain. No constant-cost or memory-free claim follows from a zero slot value. |
| Design | [docs/ranking.md §Exact score reconstruction](../../../../ranking.md), [docs/ranking.md §Budgets and availability](../../../../ranking.md), [docs/ranking_accounting.md §Native capture and lowering boundaries](../../../../ranking_accounting.md), [docs/query_memory.md §Boundaries](../../../../query_memory.md) |

## B0046

[Lines 191–196](../../../../../src/planner/ranking.cpp#L191); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L191-L196:sha256:a9c0efef15fc63ccf4ce1b015cf40b8e319cb8b5425fbb4b9d3fa95f350403c0
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | close } // namespace detail and open anonymous helper namespace in src/planner/ranking.cpp. Attached note: Admit every retained candidate before evidence fallback/scoring. Publish all scores together; private RAII handles failure without partial selection. The note is documentation only. |
| inputs / outputs | This namespace, scope, or declaration boundary has no runtime call inputs or outputs. |
| invariants | It changes compile-time visibility or declaration identity only; attached comments do not enforce or prove the described behavior. |
| ownership | This span creates no runtime owner. Later object definitions and calls determine storage and lifetimes. |
| failure | An invalid declaration or scope boundary fails compilation; no runtime exception or resource stop comes from this span. |
| cost | Compile-time parsing and preprocessor bookkeeping only; no runtime branch, allocation, clock read, counter debit, or engine hook. |
| Design | [src/planner/ranking.cpp](../../../../../src/planner/ranking.cpp), [docs/ranking.md](../../../../ranking.md), [docs/selection_accounting.md](../../../../selection_accounting.md) |

## B0047

[Lines 197–246](../../../../../src/planner/ranking.cpp#L197); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Attempt rank_impl(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Admit and evaluate a complete retained candidate prefix before publishing one immutable result. |
| inputs / outputs | Validates limits/policy/snapshot/original proof, exact bindings/context/height/key uniqueness, evidence eligibility, all score values and stable key tie-break. |
| invariants | Structural admission precedes evidence fallback. No provider advance or partial Result; fallback applies only to unavailable evidence, never resources. |
| ownership | Private ResultData/scratch use supplied account or evidence account; pure height-only creates a separate unlimited-account owner. Old snapshot/evidence owners stay retained. |
| failure | One noexcept boundary maps Failure,bad_alloc,replan,index,Error and unknown faults; private RAII releases drafts. Attempt retains spent usage and number of completed model values. |
| cost | Complete binding checks per candidate and O(C^2) prior-key comparisons plus selected model costs; teardown/time/account creation remain real costs outside logical units. |
| Design | [docs/ranking.md](../../../../ranking.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0048

[Lines 247–247](../../../../../src/planner/ranking.cpp#L247); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L247-L247:sha256:533f16bca7d58f44b3103b92e3485d22cfbb34bbad5ea3f3fa3b5a9dcb24ec89
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | This block close the lexical scope identified by the source span. |
| inputs / outputs | A scope delimiter has no call inputs or outputs; it controls which following declarations belong to the C++ namespace, class, or helper scope. |
| invariants | The braces set lexical visibility and type boundaries only. Any attached note is documentation and does not enforce behavior. |
| ownership | The delimiter and note acquire, release, or transfer no runtime object. Member lifetimes come from the enclosed type definitions. |
| failure | An unmatched or misplaced brace fails compilation; this block adds no runtime exception or resource-stop path. |
| cost | No runtime work or allocation is added. The compiler parses the scope boundary and comment. |
| Design | [src/planner/ranking.cpp](../../../../../src/planner/ranking.cpp), [docs/ranking.md](../../../../ranking.md), [docs/selection_accounting.md](../../../../selection_accounting.md) |

## B0049

[Lines 248–250](../../../../../src/planner/ranking.cpp#L248); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Attempt rank(const CandidateSnapshot&
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Rank with derived account selection. |
| inputs / outputs | Calls rank_impl with no supplied account. |
| invariants | Same whole-prefix contract; does not add evidence capture or owner freshness. |
| ownership | Borrowed inputs; optional Result retains immutable owners. |
| failure | Noexcept stop/report boundary delegated. |
| cost | Fixed call overhead plus rank_impl. |
| Design | [docs/ranking.md](../../../../ranking.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0050

[Lines 251–252](../../../../../src/planner/ranking.cpp#L251); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Attempt rank_with_account(const resource::MemoryAccount&
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Rank into a receiving owner account. |
| inputs / outputs | Calls rank_impl with account address for this synchronous call. |
| invariants | Does not migrate or retag preexisting candidate/evidence allocations. |
| ownership | Borrowed account is copied by the budget/result before any retained ownership escapes. |
| failure | Noexcept stop/report boundary delegated. |
| cost | Fixed delegation plus rank_impl/accounted allocation costs. |
| Design | [docs/ranking.md](../../../../ranking.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0051

[Lines 253–253](../../../../../src/planner/ranking.cpp#L253); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L253-L253:sha256:6a0bca3e18fdf8e268767fe2e7b423a2ff87571e241448b7450616d4d9d67e2c
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | This block close namespace crown::planner::ranking. |
| inputs / outputs | A scope delimiter has no call inputs or outputs; it controls which following declarations belong to the C++ namespace, class, or helper scope. |
| invariants | The braces set lexical visibility and type boundaries only. Any attached note is documentation and does not enforce behavior. |
| ownership | The delimiter and note acquire, release, or transfer no runtime object. Member lifetimes come from the enclosed type definitions. |
| failure | An unmatched or misplaced brace fails compilation; this block adds no runtime exception or resource-stop path. |
| cost | No runtime work or allocation is added. The compiler parses the scope boundary and comment. |
| Design | [src/planner/ranking.cpp](../../../../../src/planner/ranking.cpp), [docs/ranking.md](../../../../ranking.md), [docs/selection_accounting.md](../../../../selection_accounting.md) |
