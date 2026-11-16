# `tests/unit/ranking_public_independent_test.cpp` — block usage map

[Source](../../../../../tests/unit/ranking_public_independent_test.cpp) · [Source index](../../../README.md) · [Subsystem contracts](../../../subsystem_contracts.md) · [Reviewed primitives](../../../primitives.md)

Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection.

Snapshot SHA-256: `bbc4ba426abf99bd0f6612d983146b7637e8bd766f7e62ae9ac42d2d493b4022`. 744 lines partitioned into 57 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [tests](../../../subsystem_contracts.md#tests). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/code_review.md](../../../../code_review.md), [docs/reference_fuzz.md](../../../../reference_fuzz.md), [docs/task_ledger.md](../../../../task_ledger.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–30](../../../../../tests/unit/ranking_public_independent_test.cpp#L1) | Imports dependencies. |  · [reviewed contract](#b0001) |
| [B0002 · 31–45](../../../../../tests/unit/ranking_public_independent_test.cpp#L31) | declares namespace scope; declares aliases; declares callable signatures; declares values/defaults or compile-time conditions. | guard static_assert(!std::is_default_constructible_v&lt;ranking::Evidence&gt;); · [reviewed contract](#b0002) |
| [B0003 · 46–48](../../../../../tests/unit/ranking_public_independent_test.cpp#L46) | Callable definition: void require(bool value, const std::string& message) | calls std::runtime_error; guard void require(bool value, const std::string& message) { · [reviewed contract](#b0003) |
| [B0004 · 49–49](../../../../../tests/unit/ranking_public_independent_test.cpp#L49) | Explanatory comments or spacing. |  |
| [B0005 · 50–54](../../../../../tests/unit/ranking_public_independent_test.cpp#L50) | Callable definition: std::string read(const std::filesystem::path& path) | calls input, require, good, string; guard require(input.good(), "cannot read fixture " + path.string());; returns {std::istreambuf_iterator&lt;char&gt;{input}, std::istreambuf_iterator&lt;char&gt;{}} · [reviewed contract](#b0005) |
| [B0006 · 55–55](../../../../../tests/unit/ranking_public_independent_test.cpp#L55) | Explanatory comments or spacing. |  |
| [B0007 · 56–74](../../../../../tests/unit/ranking_public_independent_test.cpp#L56) | Callable definition: p::VerifiedOptimum prove(const Catalog& catalog, const Query& query) | calls p::ExactSearch::create, advance, optimum, require; guard require(proof && proof-&gt;valid(), "P06 omitted its checked optimum");; returns *proof; 1 loop sites · [reviewed contract](#b0007) |
| [B0008 · 75–75](../../../../../tests/unit/ranking_public_independent_test.cpp#L75) | Explanatory comments or spacing. |  |
| [B0009 · 76–86](../../../../../tests/unit/ranking_public_independent_test.cpp#L76) | Callable definition: void finish(p::CandidateProvider& provider) | calls advance, require, std::runtime_error; guard require(result.stopped_for == p::CandidateStop::candidate_ready \|\|; 1 loop sites · [reviewed contract](#b0009) |
| [B0010 · 87–87](../../../../../tests/unit/ranking_public_independent_test.cpp#L87) | Explanatory comments or spacing. |  |
| [B0011 · 88–96](../../../../../tests/unit/ranking_public_independent_test.cpp#L88) | Callable definition: p::CandidateProvider provider(p::VerifiedOptimum proof) | calls p::CandidateProvider::create, std::move; returns p::CandidateProvider::create(std::move(proof), {}, limits) · [reviewed contract](#b0011) |
| [B0012 · 97–100](../../../../../tests/unit/ranking_public_independent_test.cpp#L97) | Explanatory comments or spacing. | source comment (unverified): // Independent shape fingerprint, not the production structural-key encoding. · [reviewed contract](#b0012) |
| [B0013 · 101–113](../../../../../tests/unit/ranking_public_independent_test.cpp#L101) | Callable definition: std::string shape_node(const FreeConnexTree& tree, NodeId id) | calls at, std::to_string, push_back, std::sort; returns out + @; growth push_back; 3 loop sites; source comment (unverified): // Independent shape fingerprint, not the production structural-key encoding. · [reviewed contract](#b0013) |
| [B0014 · 114–114](../../../../../tests/unit/ranking_public_independent_test.cpp#L114) | Explanatory comments or spacing. |  |
| [B0015 · 115–117](../../../../../tests/unit/ranking_public_independent_test.cpp#L115) | Callable definition: std::string shape(const FreeConnexTree& tree) | calls shape_node; returns tree.root ? shape_node(tree, *tree.root) : @ · [reviewed contract](#b0015) |
| [B0016 · 118–118](../../../../../tests/unit/ranking_public_independent_test.cpp#L118) | Explanatory comments or spacing. |  |
| [B0017 · 119–127](../../../../../tests/unit/ranking_public_independent_test.cpp#L119) | Type/record definition: struct BooleanFixture |  · [reviewed contract](#b0017) |
| [B0018 · 128–128](../../../../../tests/unit/ranking_public_independent_test.cpp#L128) | Explanatory comments or spacing. |  |
| [B0019 · 129–168](../../../../../tests/unit/ranking_public_independent_test.cpp#L129) | Callable definition: BooleanFixture boolean_fixture(const std::filesystem::path& root) | calls io::read_document, read, prove, require; guard require(proof.height() == 2, "independently checked Boolean optimum is not 2");; returns fixture; growth emplace, insert, resize; 3 loop sites · [reviewed contract](#b0019) |
| [B0020 · 169–169](../../../../../tests/unit/ranking_public_independent_test.cpp#L169) | Explanatory comments or spacing. |  |
| [B0021 · 170–172](../../../../../tests/unit/ranking_public_independent_test.cpp#L170) | Callable definition: PhysicalPlan lower(const p::MinimumHeightCandidate& candidate) | calls p::lower_tree, catalog, query, tree; returns p::lower_tree(candidate.catalog(), candidate.query(), candidate.tree()) · [reviewed contract](#b0021) |
| [B0022 · 173–173](../../../../../tests/unit/ranking_public_independent_test.cpp#L173) | Explanatory comments or spacing. |  |
| [B0023 · 174–180](../../../../../tests/unit/ranking_public_independent_test.cpp#L174) | Callable definition: r::workload::Options counters(std::uint64_t period = 1, std::uint64_t offset = 0) | calls ; returns options · [reviewed contract](#b0023) |
| [B0024 · 181–181](../../../../../tests/unit/ranking_public_independent_test.cpp#L181) | Explanatory comments or spacing. |  |
| [B0025 · 182–188](../../../../../tests/unit/ranking_public_independent_test.cpp#L182) | Callable definition: template&lt;class Runtime&gt; evidence::RuntimeEvidence capture_checked(const p::CandidateSnapshot& candidates, const Runtime& owner, c… | calls evidence::capture, require, has_value; guard require(captured.stop == ranking::Stop::complete && captured.evidence.has_value(), "runtime capture…; returns *captured.evidence · [reviewed contract](#b0025) |
| [B0026 · 189–189](../../../../../tests/unit/ranking_public_independent_test.cpp#L189) | Explanatory comments or spacing. |  |
| [B0027 · 190–200](../../../../../tests/unit/ranking_public_independent_test.cpp#L190) | Callable definition: ranking::Result rank(const p::CandidateSnapshot& candidates, ranking::Policy policy, const std::optional&lt;ranking::Evidence&gt;& inpu… | calls ranking::rank, require, has_value, candidate_count; guard require(result.stop == ranking::Stop::complete && result.result.has_value(), "ranking did not publi…; returns *result.result · [reviewed contract](#b0027) |
| [B0028 · 201–201](../../../../../tests/unit/ranking_public_independent_test.cpp#L201) | Explanatory comments or spacing. |  |
| [B0029 · 202–204](../../../../../tests/unit/ranking_public_independent_test.cpp#L202) | Callable definition: bool has(ranking::Reasons reasons, ranking::Reason reason) | calls ranking::reason; returns (reasons & ranking::reason(reason)) != 0 · [reviewed contract](#b0029) |
| [B0030 · 205–206](../../../../../tests/unit/ranking_public_independent_test.cpp#L205) | declares aliases; declares values/defaults or compile-time conditions. |  · [reviewed contract](#b0030) |
| [B0031 · 207–214](../../../../../tests/unit/ranking_public_independent_test.cpp#L207) | Callable definition: std::map&lt;std::size_t, WeightRow&gt; weights(const ranking::Evidence& value) | calls require, emplace; guard require(result.emplace(row.table.value, WeightRow{row.inserts, row.erases, row.changed, row.noop}).…; returns result; growth emplace; 1 loop sites · [reviewed contract](#b0031) |
| [B0032 · 215–215](../../../../../tests/unit/ranking_public_independent_test.cpp#L215) | Explanatory comments or spacing. |  |
| [B0033 · 216–220](../../../../../tests/unit/ranking_public_independent_test.cpp#L216) | Callable definition: std::map&lt;std::size_t, std::uint64_t&gt; sources(const ranking::Evidence& value) | calls require, emplace; guard for (const auto& row : value.sources()) require(result.emplace(row.table.value, row.rows).second, "…; returns result; growth emplace; 1 loop sites · [reviewed contract](#b0033) |
| [B0034 · 221–221](../../../../../tests/unit/ranking_public_independent_test.cpp#L221) | Explanatory comments or spacing. |  |
| [B0035 · 222–227](../../../../../tests/unit/ranking_public_independent_test.cpp#L222) | Callable definition: Relation answers(const r::PhysicalRuntime& owner) | calls results, next, insert, crown::storage::export_row; returns rows; growth insert; 1 loop sites · [reviewed contract](#b0035) |
| [B0036 · 228–228](../../../../../tests/unit/ranking_public_independent_test.cpp#L228) | Explanatory comments or spacing. |  |
| [B0037 · 229–234](../../../../../tests/unit/ranking_public_independent_test.cpp#L229) | Callable definition: void noop(r::PhysicalRuntime& owner, std::size_t table, const Row& row, unsigned count) | calls apply, sequence, require; guard require(!epoch.input.physical_changed, "literal duplicate insert unexpectedly changed source");; growth insert; 1 loop sites · [reviewed contract](#b0037) |
| [B0038 · 235–235](../../../../../tests/unit/ranking_public_independent_test.cpp#L235) | Explanatory comments or spacing. |  |
| [B0039 · 236–259](../../../../../tests/unit/ranking_public_independent_test.cpp#L236) | Callable definition: void verify_depth_scores(const BooleanFixture& fixture, const ranking::Result& result, bool hot_r) | calls require, effective_policy, fallback_reasons, scores; guard require(result.effective_policy() == ranking::Policy::committed_input_native_depth && result.fallba…; growth insert; 2 loop sites · [reviewed contract](#b0039) |
| [B0040 · 260–260](../../../../../tests/unit/ranking_public_independent_test.cpp#L260) | Explanatory comments or spacing. |  |
| [B0041 · 261–277](../../../../../tests/unit/ranking_public_independent_test.cpp#L261) | Callable definition: void candidate_semantics_and_height(const BooleanFixture& fixture) | calls ranking::rank, require, rank, snapshot; guard require(empty.stop == ranking::Stop::no_candidates && !empty.result, "empty actual snapshot publish…; growth insert; 1 loop sites · [reviewed contract](#b0041) |
| [B0042 · 278–278](../../../../../tests/unit/ranking_public_independent_test.cpp#L278) | Explanatory comments or spacing. |  |
| [B0043 · 279–378](../../../../../tests/unit/ranking_public_independent_test.cpp#L279) | Callable definition: void hot_reversal_and_memory(const BooleanFixture& fixture) | calls r::PhysicalRuntime::initialize, lower, at, configure_workload_statistics; guard require(hot_r.inputs().identity().owner == owner.owner().value && hot_r.inputs().identity().epoch =…; returns node.visible_relation.has_value(); growth emplace; 3 loop sites · [reviewed contract](#b0043) |
| [B0044 · 379–379](../../../../../tests/unit/ranking_public_independent_test.cpp#L379) | Explanatory comments or spacing. |  |
| [B0045 · 380–413](../../../../../tests/unit/ranking_public_independent_test.cpp#L380) | Callable definition: void changed_noop_abort_and_freshness(const BooleanFixture& fixture) | calls r::PhysicalRuntime::initialize, lower, at, configure_workload_statistics; guard require(weights(before.inputs()).at(0) == WeightRow{2, 2, 2, 2} && before.inputs().denominator() ==…; growth insert · [reviewed contract](#b0045) |
| [B0046 · 414–414](../../../../../tests/unit/ranking_public_independent_test.cpp#L414) | Explanatory comments or spacing. |  |
| [B0047 · 415–529](../../../../../tests/unit/ranking_public_independent_test.cpp#L415) | Callable definition: void unavailable_and_resources(const BooleanFixture& fixture) | calls r::PhysicalRuntime::initialize, lower, at, capture_checked; guard require(has(off.inputs().depth_reasons(), ranking::Reason::disabled) && off.inputs().memory_reasons…; 3 loop sites · [reviewed contract](#b0047) |
| [B0048 · 530–530](../../../../../tests/unit/ranking_public_independent_test.cpp#L530) | Explanatory comments or spacing. |  |
| [B0049 · 531–602](../../../../../tests/unit/ranking_public_independent_test.cpp#L531) | Callable definition: void normalized_alias_mapping() | calls frontend::bind_sql, require, frontend::normalize_sql, std::move; guard require(std::holds_alternative&lt;frontend::BoundSql&gt;(binding), "independent SQL alias binding failed"…; growth insert, resize; 7 loop sites; source comment (unverified): // The memory contract requests distinct routed bases only. Unused physical · [reviewed contract](#b0049) |
| [B0050 · 603–603](../../../../../tests/unit/ranking_public_independent_test.cpp#L603) | Explanatory comments or spacing. |  |
| [B0051 · 604–637](../../../../../tests/unit/ranking_public_independent_test.cpp#L604) | Callable definition: void statistical_ties_and_binding(const BooleanFixture& fixture) | calls r::PhysicalRuntime::initialize, lower, at, configure_workload_statistics; guard require(tied.selected().structural_key() == std::min(x, y), "equal statistical score ignored full s…; 2 loop sites · [reviewed contract](#b0051) |
| [B0052 · 638–638](../../../../../tests/unit/ranking_public_independent_test.cpp#L638) | Explanatory comments or spacing. |  |
| [B0053 · 639–676](../../../../../tests/unit/ranking_public_independent_test.cpp#L639) | Callable definition: void mode_reset_drop(const BooleanFixture& fixture) | calls lower, at, r::DeltaRuntime::initialize, configure_workload_statistics; guard require(before.inputs().identity().modes.delta_owner && evidence::revalidate(before, owner).all_fac…; growth insert · [reviewed contract](#b0053) |
| [B0054 · 677–677](../../../../../tests/unit/ranking_public_independent_test.cpp#L677) | Explanatory comments or spacing. |  |
| [B0055 · 678–723](../../../../../tests/unit/ranking_public_independent_test.cpp#L678) | Callable definition: void decimal_and_repeated_output_payload() | calls Decimal::parse, provider, prove, finish; guard require(snapshot.candidate_count() == 1 && snapshot.original_proof().height() == 1, "decimal fixtur…; growth insert, resize · [reviewed contract](#b0055) |
| [B0056 · 724–725](../../../../../tests/unit/ranking_public_independent_test.cpp#L724) | Closes surrounding scope/type. | source comment (unverified): // namespace · [reviewed contract](#b0056) |
| [B0057 · 726–744](../../../../../tests/unit/ranking_public_independent_test.cpp#L726) | Callable definition: int main(int argc, char** argv) | calls require, boolean_fixture, candidate_semantics_and_height, hot_reversal_and_memory; guard require(argc == 2, "usage: ranking_public_independent_test REPOSITORY_ROOT");; returns 0; 1 · [reviewed contract](#b0057) |

## B0001

[Lines 1–30](../../../../../tests/unit/ranking_public_independent_test.cpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L1-L30:sha256:132048cfb743c0ad1bb93e88880331684b5b97280f793d5790421f6700980a33
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Prepare ranking_public_independent_test.cpp: include "crown/api/error.hpp", "crown/frontend/bind.hpp", "crown/frontend/normalize.hpp", "crown/io/document.hpp", "crown/io/tree.hpp", "crown/planner/lower.hpp", "crown/planner/ranking.hpp", "crown/planner/search.hpp", "crown/runtime/ranking_evidence.hpp", &lt;algorithm&gt;, &lt;array&gt;, &lt;chrono&gt;, &lt;cstddef&gt;, &lt;cstdint&gt;, &lt;filesystem&gt;, &lt;fstream&gt;, &lt;iostream&gt;, &lt;iterator&gt;, &lt;map&gt;, &lt;optional&gt;, &lt;set&gt;, &lt;sstream&gt;, &lt;stdexcept&gt;, &lt;string&gt;, &lt;tuple&gt;, &lt;type_traits&gt;, &lt;utility&gt;, &lt;vector&gt;. |
| inputs / outputs | Compiler-visible dependencies, names and the recorded declarations in; declarations available to the following fixture/CLI/example definitions out. |
| invariants | Declarations are scoped to this source/header and its selected ABI. Included code has its own effects; names and editable fixture values do not confer proof, admission or publication authority. |
| ownership | Aliases/includes do not create a query owner. Pointers/references/views are non-owning. Containers own their elements, which can themselves be borrowed pointers or numeric IDs. Only documented owning shared-control handles retain controls; IDs/slot-handle values do not independently keep an arena/runtime alive. |
| failure | Missing headers, ill-formed names/types, failed static assertions or active #error directives stop compilation. No runtime rejection/rollback mechanism is implemented by aliases or function prototypes. |
| cost | Preprocessing and type/constraint instantiation cost compilation. Alias/prototype syntax does not invoke the declared operation; any included definitions keep their own initialization effects. |
| Design | [tests/unit/ranking_public_independent_test.cpp](../../../../../tests/unit/ranking_public_independent_test.cpp), [docs/ranking.md](../../../../ranking.md), [docs/code_review.md](../../../../code_review.md) |

## B0002

[Lines 31–45](../../../../../tests/unit/ranking_public_independent_test.cpp#L31); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L31-L45:sha256:53cbf2f6157e0d5f5f2fcae101fa307f8794e68aa76e99b49599e5da9fed5b4d
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Prepare ranking_public_independent_test.cpp: bind local aliases/name imports; require 7 compile-time type/ABI conditions. |
| inputs / outputs | Compiler-visible dependencies, names and the recorded declarations in; declarations available to the following fixture/CLI/example definitions out. |
| invariants | Declarations are scoped to this source/header and its selected ABI. Included code has its own effects; names and editable fixture values do not confer proof, admission or publication authority. Static assertions establish only their listed C++ type properties, not query/result/recovery correctness or test execution. |
| ownership | Aliases/includes do not create a query owner. Pointers/references/views are non-owning. Containers own their elements, which can themselves be borrowed pointers or numeric IDs. Only documented owning shared-control handles retain controls; IDs/slot-handle values do not independently keep an arena/runtime alive. |
| failure | Missing headers, ill-formed names/types, failed static assertions or active #error directives stop compilation. No runtime rejection/rollback mechanism is implemented by aliases or function prototypes. |
| cost | Preprocessing and type/constraint instantiation cost compilation. Alias/prototype syntax does not invoke the declared operation; any included definitions keep their own initialization effects. |
| Design | [tests/unit/ranking_public_independent_test.cpp](../../../../../tests/unit/ranking_public_independent_test.cpp), [docs/ranking.md](../../../../ranking.md), [docs/code_review.md](../../../../code_review.md) |

## B0003

[Lines 46–48](../../../../../tests/unit/ranking_public_independent_test.cpp#L46); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void require(bool value, const std::string& message) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Turn a failed fixture assertion into a test exception. |
| inputs / outputs | A Boolean condition and a const std::string diagnostic are inputs; success returns, while false throws std::runtime_error with that diagnostic. |
| invariants | The diagnostic parameter is already a std::string when the helper body begins. Literal call arguments are converted at the call site, before the condition branch. |
| ownership | Borrows the message during the call; a thrown runtime_error retains its own error text. It owns no query, evidence, or result handle. |
| failure | False throws; construction of the diagnostic temporary or runtime_error may itself fail. Callers do not receive a status value. |
| cost | One condition branch per call. The const std::string argument is materialized eagerly by callers and longer diagnostics may allocate even on a passing assertion. |
| Design | [tests/unit/ranking_public_independent_test.cpp](../../../../../tests/unit/ranking_public_independent_test.cpp), [docs/ranking.md](../../../../ranking.md) |

## B0005

[Lines 50–54](../../../../../tests/unit/ranking_public_independent_test.cpp#L50); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::string read(const std::filesystem::path& path) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Read one JSON or tree fixture into an owning string for the test parser. |
| inputs / outputs | A filesystem path selects a file under the supplied repository root; the complete stream range is returned as std::string. |
| invariants | The only explicit check is that the ifstream opens successfully; the helper does not impose a file-size ceiling or parse the content. |
| ownership | The path is borrowed through the const-reference parameter; the ifstream is local and closes on return. The returned string owns the copied file bytes. |
| failure | An unreadable/open-failing path triggers require and throws; stream, string allocation, and filesystem failures also propagate. |
| cost | Reads and stores O(file bytes) with stream/string growth; the open-check diagnostic also calls path.string() and concatenates eagerly. Cost follows fixture/path size and allocator behavior, not a test constant. |
| Design | [tests/unit/ranking_public_independent_test.cpp](../../../../../tests/unit/ranking_public_independent_test.cpp), [tests/candidates/queries/boolean_rst.cq.json](../../../../../tests/candidates/queries/boolean_rst.cq.json), [tests/candidates/trees/boolean_rst_native_s_root.tree.json](../../../../../tests/candidates/trees/boolean_rst_native_s_root.tree.json) |

## B0007

[Lines 56–74](../../../../../tests/unit/ranking_public_independent_test.cpp#L56); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
p::VerifiedOptimum prove(const Catalog& catalog, const Query& query) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Build a checked minimum-height proof used to admit the independent candidate fixture. |
| inputs / outputs | A Catalog and Query are passed by const reference. A strict ExactSearch uses producer/replay work ceilings of 100,000,000 and logical depth 64, advances in 100,000-work quanta for at most 2,000 calls, and returns its VerifiedOptimum. |
| invariants | Only a valid verified optimum is returned. Intermediate quantum_work or quantum_time stops may continue; the fixture does not infer proof from a partial result. |
| ownership | The returned proof is an owning checked artifact; the caller still owns the Catalog and Query supplied to the search. |
| failure | Unexpected terminal reasons, absent/invalid optimum, or guard exhaustion throw runtime_error; search creation and proof operations can also fail through their APIs. |
| cost | Up to 2,000 search advances plus proof access, under logical work/depth ceilings. These charged search resources do not bound host CPU time, allocation bytes, or every recursive helper cost. |
| Design | [tests/unit/ranking_public_independent_test.cpp](../../../../../tests/unit/ranking_public_independent_test.cpp), [include/crown/planner/search.hpp](../../../../../include/crown/planner/search.hpp), [src/planner/search_session.cpp](../../../../../src/planner/search_session.cpp), [docs/planner_continuations.md](../../../../planner_continuations.md) |

## B0009

[Lines 76–86](../../../../../tests/unit/ranking_public_independent_test.cpp#L76); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void finish(p::CandidateProvider& provider) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Advance the supplied candidate provider until this finite fixture's family is exhausted. |
| inputs / outputs | A mutable CandidateProvider is advanced with 100,000-work quanta for at most 2,000 calls; exhaustion returns normally. |
| invariants | candidate_ready, quantum_work, and quantum_time are the only accepted nonterminal results. This helper consumes provider progress and does not rank candidates. |
| ownership | The provider remains caller-owned and retains its proof/family state; each later snapshot is a separate owning handle. |
| failure | An unexpected stop or exhausted guard throws runtime_error. Provider advancement may report its own allocation/resource stops. |
| cost | At most 2,000 calls; work is limited by the CandidateLimits established by provider(), while candidate generation and comparisons vary with the family. |
| Design | [tests/unit/ranking_public_independent_test.cpp](../../../../../tests/unit/ranking_public_independent_test.cpp), [include/crown/planner/candidates.hpp](../../../../../include/crown/planner/candidates.hpp), [include/crown/planner/search.hpp](../../../../../include/crown/planner/search.hpp), [docs/ranking.md](../../../../ranking.md) |

## B0011

[Lines 88–96](../../../../../tests/unit/ranking_public_independent_test.cpp#L88); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
p::CandidateProvider provider(p::VerifiedOptimum proof) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Create the bounded candidate-family provider for a checked proof. |
| inputs / outputs | Consumes a VerifiedOptimum by value and creates a provider with enumeration work 100,000,000, logical depth 64, record limit 1,000,000, cell limit 10,000,000, and retained-candidate limit 32. |
| invariants | The provider receives the checked proof authority and starts without an asserted complete family; callers advance it and request snapshots explicitly. |
| ownership | Moves the proof into the returned provider, which owns continuation state and its retained candidates. |
| failure | Provider setup may fail or throw through its creation API; this wrapper has no fallback path. |
| cost | Provider construction allocates its continuation state; later enumeration is separately bounded by the configured logical limits and fixture call guards. |
| Design | [tests/unit/ranking_public_independent_test.cpp](../../../../../tests/unit/ranking_public_independent_test.cpp), [include/crown/planner/candidates.hpp](../../../../../include/crown/planner/candidates.hpp), [src/planner/search_session.cpp](../../../../../src/planner/search_session.cpp), [docs/ranking.md](../../../../ranking.md) |

## B0012

[Lines 97–100](../../../../../tests/unit/ranking_public_independent_test.cpp#L97); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L97-L100:sha256:6a7107234e75f452f640d84a50db152ebad36778e93f7625516da2a9f1d211ce
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Explain the adjacent source contract: Independent shape fingerprint, not the production structural-key encoding. Labels/node vector positions are ignored; scopes and occurrence identities remain literal, and unordered children are compared as full strings. |
| inputs / outputs | Human-readable source note in; no executable output or checked receipt. |
| invariants | This comment states context or a limitation. It does not itself enforce or prove the described behavior; use the adjacent implementation and its scoped contract. |
| ownership | Source text only; no object or resource lifetime is created. |
| failure | No runtime failure path in this comment; source encoding/comment syntax still belongs to compilation. |
| cost | No runtime operations from the comment. Any work described in the note belongs to the adjacent operation. |
| Design | [tests/unit/ranking_public_independent_test.cpp](../../../../../tests/unit/ranking_public_independent_test.cpp), [docs/ranking.md](../../../../ranking.md), [docs/code_review.md](../../../../code_review.md) |

## B0013

[Lines 101–113](../../../../../tests/unit/ranking_public_independent_test.cpp#L101); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::string shape_node(const FreeConnexTree& tree, NodeId id) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Fingerprint one tree node independently of production structural-key encoding. |
| inputs / outputs | A tree and node ID produce a string containing node kind, optional occurrence, ordered scope IDs, and recursively fingerprinted children sorted by their full strings. |
| invariants | Labels and node-vector positions are omitted; occurrence IDs and scope iteration remain literal. Child order is normalized by sorting full child fingerprints. The caller must supply a finite acyclic tree; this helper does not validate it or detect cycles/depth. |
| ownership | The returned string and temporary child vector own their storage; the input tree is borrowed. |
| failure | An out-of-range node index can throw through vector::at, and string/vector allocation failures can propagate. There is no visited set or recursion-depth limit; cyclic or excessively deep malformed graphs are outside the helper precondition, and stack exhaustion is not converted into a defined exception. |
| cost | Visits each reachable child edge/node recursively and sorts each node's child fingerprints; string size and sort work depend on tree shape. Fixture use is finite and does not establish a general depth bound. |
| Design | [tests/unit/ranking_public_independent_test.cpp](../../../../../tests/unit/ranking_public_independent_test.cpp), [include/crown/planner/candidates.hpp](../../../../../include/crown/planner/candidates.hpp), [tests/candidates/trees/boolean_rst_native_s_root.tree.json](../../../../../tests/candidates/trees/boolean_rst_native_s_root.tree.json) |

## B0015

[Lines 115–117](../../../../../tests/unit/ranking_public_independent_test.cpp#L115); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::string shape(const FreeConnexTree& tree) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Fingerprint a complete fixture tree or encode an absent root as the literal empty marker. |
| inputs / outputs | A borrowed FreeConnexTree returns "empty" when it has no root; otherwise it delegates to shape_node at the root. |
| invariants | This is an independent test fingerprint and is not the production structural key or a semantic proof. |
| ownership | Returns an owning std::string; the tree remains caller-owned. |
| failure | Propagates shape_node bounds and allocation failures. |
| cost | One root dispatch plus the recursive node/child sorting and string construction described by shape_node. |
| Design | [tests/unit/ranking_public_independent_test.cpp](../../../../../tests/unit/ranking_public_independent_test.cpp), [tests/candidates/trees/boolean_rst_native_s_root.tree.json](../../../../../tests/candidates/trees/boolean_rst_native_s_root.tree.json), [include/crown/planner/candidates.hpp](../../../../../include/crown/planner/candidates.hpp) |

## B0017

[Lines 119–127](../../../../../tests/unit/ranking_public_independent_test.cpp#L119); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct BooleanFixture {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Group the parsed Boolean query, three provider snapshots, structural-label indexes, and literal initial database. |
| inputs / outputs | Fields hold a Document, all/partial/empty CandidateSnapshots, maps from structural keys and labels to candidates, and the initial Database. |
| invariants | The partial snapshot is intentionally a one-candidate nonexhausted prefix; the complete snapshot is a separate provider snapshot with three candidates. |
| ownership | The fixture owns the document, snapshots, maps, candidate handles, and database value; candidate artifacts retain their own shared proof/provider backing. |
| failure | Member construction can allocate or propagate failures from owning handles; this aggregate declares no custom recovery. |
| cost | Value/member construction cost follows catalog, query, candidate, map-key, and database contents; this type itself introduces no traversal loop. |
| Design | [tests/unit/ranking_public_independent_test.cpp](../../../../../tests/unit/ranking_public_independent_test.cpp), [include/crown/planner/candidates.hpp](../../../../../include/crown/planner/candidates.hpp), [tests/candidates/queries/boolean_rst.cq.json](../../../../../tests/candidates/queries/boolean_rst.cq.json) |

## B0019

[Lines 129–168](../../../../../tests/unit/ranking_public_independent_test.cpp#L129); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
BooleanFixture boolean_fixture(const std::filesystem::path& root) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Construct and cross-check the three-candidate Boolean fixture against literal checked tree files. |
| inputs / outputs | Reads boolean_rst.cq.json, proves height 2, captures an empty snapshot, advances to a one-candidate prefix, finishes the provider, and validates/labels the three literal trees. It returns a Database with one row in each of three physical tables. |
| invariants | The complete snapshot must contain exactly the three unique fixture geometries and retain the original height-2 proof; the saved prefix remains one candidate and nonexhausted after provider completion. |
| ownership | The returned fixture owns the Document, snapshots, maps, and initial Database. Provider state is local; snapshots/candidate handles keep their immutable backing alive. |
| failure | Any proof, provider, file-read, parse, validation, shape-collision, or cardinality assertion failure throws; setup is not infallible. |
| cost | Runs the bounded proof/provider loops (up to 2,000 advances at each stated guard), reads one query plus three tree fixtures, validates three trees, and maps the retained candidates. Work limits are logical search caps, not CPU or heap bounds. |
| Design | [tests/unit/ranking_public_independent_test.cpp](../../../../../tests/unit/ranking_public_independent_test.cpp), [tests/candidates/queries/boolean_rst.cq.json](../../../../../tests/candidates/queries/boolean_rst.cq.json), [tests/candidates/trees/boolean_rst_native_s_root.tree.json](../../../../../tests/candidates/trees/boolean_rst_native_s_root.tree.json), [tests/candidates/trees/boolean_rst_generalized_x_root.tree.json](../../../../../tests/candidates/trees/boolean_rst_generalized_x_root.tree.json), [tests/candidates/trees/boolean_rst_generalized_y_root.tree.json](../../../../../tests/candidates/trees/boolean_rst_generalized_y_root.tree.json), [include/crown/planner/candidates.hpp](../../../../../include/crown/planner/candidates.hpp) |

## B0021

[Lines 170–172](../../../../../tests/unit/ranking_public_independent_test.cpp#L170); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
PhysicalPlan lower(const p::MinimumHeightCandidate& candidate) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Lower one retained candidate to a physical plan for runtime semantic assertions. |
| inputs / outputs | A borrowed MinimumHeightCandidate supplies its Catalog, Query, and tree to lower_tree; the PhysicalPlan is returned by value. |
| invariants | The lowered plan uses that candidate's own geometry and binding; this helper does not choose or rank candidates. |
| ownership | The returned plan owns its compiled data; the candidate remains owned by its fixture/snapshot. |
| failure | Lowering validation, work, or allocation failures propagate to the test group. |
| cost | Cost follows candidate tree/layout/source size and lowerer work; no fixed timing or allocation claim is made. |
| Design | [tests/unit/ranking_public_independent_test.cpp](../../../../../tests/unit/ranking_public_independent_test.cpp), [include/crown/planner/lower.hpp](../../../../../include/crown/planner/lower.hpp), [src/planner/lower.cpp](../../../../../src/planner/lower.cpp) |

## B0023

[Lines 174–180](../../../../../tests/unit/ranking_public_independent_test.cpp#L174); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
r::workload::Options counters(std::uint64_t period = 1, std::uint64_t offset = 0) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Create workload-counter options with a caller-selected sample period and offset. |
| inputs / outputs | Period and offset are copied into Options with mode set to counters; the value is returned. |
| invariants | The helper changes only these fields; it does not claim every input gets detailed sampling or that counters measure CPU work. |
| ownership | Returns an ordinary options value; runtime configuration owns its later copy. |
| failure | No local failure path; later owner configuration can reject or allocate according to its API. |
| cost | Fixed scalar assignments and value return; it creates no fixture loop or runtime owner. |
| Design | [tests/unit/ranking_public_independent_test.cpp](../../../../../tests/unit/ranking_public_independent_test.cpp), [include/crown/runtime/ranking_evidence.hpp](../../../../../include/crown/runtime/ranking_evidence.hpp), [docs/ranking.md](../../../../ranking.md) |

## B0025

[Lines 182–188](../../../../../tests/unit/ranking_public_independent_test.cpp#L182); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
template<class Runtime>
evidence::RuntimeEvidence capture_checked(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Require the runtime capture attempt itself to complete and return an owning RuntimeEvidence handle. |
| inputs / outputs | A CandidateSnapshot, runtime owner of the selected template type, and optional CaptureOptions are passed to capture; the returned RuntimeEvidence is copied from the optional result. |
| invariants | Only Stop::complete with evidence present is accepted. This does not require every fact to be usable: input-census reasons and source-cardinality capture state remain separate inside the returned evidence. |
| ownership | Returns a shared immutable RuntimeEvidence handle whose nested evidence/capture retains its plan account; owner and input snapshot remain caller-owned. |
| failure | A noncomplete stop or missing handle throws runtime_error; capture failure remains a test exception and is not converted to evidence. |
| cost | One synchronous capture call whose cost follows captured workload descriptors/cells, source selections, bindings, and processing limits; the helper adds one eager diagnostic argument. |
| Design | [tests/unit/ranking_public_independent_test.cpp](../../../../../tests/unit/ranking_public_independent_test.cpp), [include/crown/runtime/ranking_evidence.hpp](../../../../../include/crown/runtime/ranking_evidence.hpp), [src/runtime/ranking_evidence.cpp](../../../../../src/runtime/ranking_evidence.cpp), [docs/ranking_accounting.md](../../../../ranking_accounting.md) |

## B0027

[Lines 190–200](../../../../../tests/unit/ranking_public_independent_test.cpp#L190); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
ranking::Result rank(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Run pure ranking for a snapshot and require a result that evaluated every candidate in that retained prefix. |
| inputs / outputs | Sets policy and fallback in a default Request, passes optional owning Evidence, and returns the Result from ranking::rank after checking complete stop, handle presence, evaluated count, and score count. |
| invariants | The helper does not advance CandidateProvider or assert family exhaustion; completeness is only for the supplied snapshot. The default evidence policy is require_evidence unless the caller selects fallback. |
| ownership | Returned Result shares immutable result data and retains the snapshot, proof, request, optional evidence, and score graph; caller owns the input handles too. |
| failure | Unavailable evidence, resource/binding/handle failures, or an incomplete result throw runtime_error through require; no partial result is returned by this helper. |
| cost | For C retained candidates, rank checks each candidate and re-encodes/compares its catalog-query binding; structural-key uniqueness scans all earlier keys, giving O(C²) key comparisons with variable byte widths. It then computes every score and allocates score/output storage; tuple-index-slots also relowers each candidate. Cost varies with bindings, trees and plans; no host CPU or allocator-byte bound is implied. |
| Design | [tests/unit/ranking_public_independent_test.cpp](../../../../../tests/unit/ranking_public_independent_test.cpp), [include/crown/planner/ranking.hpp](../../../../../include/crown/planner/ranking.hpp), [src/planner/ranking.cpp](../../../../../src/planner/ranking.cpp), [docs/ranking.md](../../../../ranking.md) |

## B0029

[Lines 202–204](../../../../../tests/unit/ranking_public_independent_test.cpp#L202); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
bool has(ranking::Reasons reasons, ranking::Reason reason) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Test whether a single reason bit is present in a combined reason mask. |
| inputs / outputs | A reason mask and one Reason enum are converted to the public bit value; the function returns the bitwise membership result. |
| invariants | It is a reason-mask predicate only and does not decide evidence freshness or policy usability. |
| ownership | Scalar values only; no owner or evidence is retained. |
| failure | No local failure path. |
| cost | One bitwise AND and comparison. |
| Design | [tests/unit/ranking_public_independent_test.cpp](../../../../../tests/unit/ranking_public_independent_test.cpp), [include/crown/planner/ranking.hpp](../../../../../include/crown/planner/ranking.hpp), [include/crown/runtime/ranking_evidence.hpp](../../../../../include/crown/runtime/ranking_evidence.hpp) |

## B0030

[Lines 205–206](../../../../../tests/unit/ranking_public_independent_test.cpp#L205); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L205-L206:sha256:2eb9231fd63e3876b3cf357e34f333ae726e7a205424e6f1d63a6c8730e25b85
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Prepare ranking_public_independent_test.cpp: bind local aliases/name imports. |
| inputs / outputs | Compiler-visible dependencies, names and the recorded declarations in; declarations available to the following fixture/CLI/example definitions out. |
| invariants | Declarations are scoped to this source/header and its selected ABI. Included code has its own effects; names and editable fixture values do not confer proof, admission or publication authority. |
| ownership | Aliases/includes do not create a query owner. Pointers/references/views are non-owning. Containers own their elements, which can themselves be borrowed pointers or numeric IDs. Only documented owning shared-control handles retain controls; IDs/slot-handle values do not independently keep an arena/runtime alive. |
| failure | Missing headers, ill-formed names/types, failed static assertions or active #error directives stop compilation. No runtime rejection/rollback mechanism is implemented by aliases or function prototypes. |
| cost | Preprocessing and type/constraint instantiation cost compilation. Alias/prototype syntax does not invoke the declared operation; any included definitions keep their own initialization effects. |
| Design | [tests/unit/ranking_public_independent_test.cpp](../../../../../tests/unit/ranking_public_independent_test.cpp), [docs/ranking.md](../../../../ranking.md), [docs/code_review.md](../../../../code_review.md) |

## B0031

[Lines 207–214](../../../../../tests/unit/ranking_public_independent_test.cpp#L207); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::map<std::size_t, WeightRow> weights(const ranking::Evidence& value) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Index captured workload weights by physical table and preserve insert, erase, changed, and no-op counts for assertions. |
| inputs / outputs | Iterates Evidence::weights and returns a map from numeric table ID to a four-counter tuple. |
| invariants | Each table ID must be unique; changed/no-op/input meaning comes from captured evidence and is not recomputed here. |
| ownership | Returns an owning std::map and tuple values; borrows Evidence only during traversal. |
| failure | Duplicate table IDs fail through require; map allocation or eager diagnostic construction may also fail. |
| cost | One loop over weight rows with ordered-map insertion/comparison and retained map storage; work grows with returned table count and key comparisons. |
| Design | [tests/unit/ranking_public_independent_test.cpp](../../../../../tests/unit/ranking_public_independent_test.cpp), [include/crown/planner/ranking.hpp](../../../../../include/crown/planner/ranking.hpp), [src/runtime/ranking_evidence.cpp](../../../../../src/runtime/ranking_evidence.cpp), [docs/ranking.md](../../../../ranking.md) |

## B0033

[Lines 216–220](../../../../../tests/unit/ranking_public_independent_test.cpp#L216); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::map<std::size_t, std::uint64_t> sources(const ranking::Evidence& value) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Index captured physical source cardinalities by table for literal-fixture assertions. |
| inputs / outputs | Iterates Evidence::sources and returns table ID to row-count pairs. |
| invariants | Duplicate table observations are rejected; these values are physical source cardinalities, not filtered query-result counts. |
| ownership | Returns an owning std::map and scalar values; the Evidence handle is borrowed. |
| failure | Duplicate table IDs throw through require; map allocation failures propagate. |
| cost | One ordered-map insertion per source record; comparisons and output size depend on the number of captured source tables. |
| Design | [tests/unit/ranking_public_independent_test.cpp](../../../../../tests/unit/ranking_public_independent_test.cpp), [include/crown/planner/ranking.hpp](../../../../../include/crown/planner/ranking.hpp), [src/runtime/ranking_evidence.cpp](../../../../../src/runtime/ranking_evidence.cpp), [docs/ranking.md](../../../../ranking.md) |

## B0035

[Lines 222–227](../../../../../tests/unit/ranking_public_independent_test.cpp#L222); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Relation answers(const r::PhysicalRuntime& owner) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Materialize the current physical runtime result into the test's exported-row Relation form. |
| inputs / outputs | A const PhysicalRuntime is read through a result cursor; each row view is exported and inserted into a returned Relation. |
| invariants | This helper observes query output only; it does not compare internal storage or alter the owner. |
| ownership | The returned Relation owns exported values; cursor and source views are local and the runtime remains caller-owned. |
| failure | Cursor/export/container allocation failures propagate; there is no partial-result status wrapper. |
| cost | Walks every output row and exports its fields; time and memory depend on query result cardinality and row widths. |
| Design | [tests/unit/ranking_public_independent_test.cpp](../../../../../tests/unit/ranking_public_independent_test.cpp), [include/crown/runtime/ranking_evidence.hpp](../../../../../include/crown/runtime/ranking_evidence.hpp), [docs/ranking.md](../../../../ranking.md) |

## B0037

[Lines 229–234](../../../../../tests/unit/ranking_public_independent_test.cpp#L229); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void noop(r::PhysicalRuntime& owner, std::size_t table, const Row& row, unsigned count) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Apply a caller-selected number of duplicate inserts and assert they leave physical membership unchanged. |
| inputs / outputs | A mutable PhysicalRuntime, table index, borrowed Row, and count drive sequential inserts at owner.sequence()+1. |
| invariants | Every returned input record must report physical_changed=false; these committed no-op inputs still contribute to workload census tests. |
| ownership | The runtime owns committed input/census state; Row is borrowed for each synchronous apply. |
| failure | Unexpected physical change throws runtime_error; runtime apply can fail or reject individual input and propagates its exception. |
| cost | Exactly count apply calls; each traverses the runtime's input/update path, so no-op does not mean zero runtime work or zero elapsed time. |
| Design | [tests/unit/ranking_public_independent_test.cpp](../../../../../tests/unit/ranking_public_independent_test.cpp), [src/runtime/ranking_evidence.cpp](../../../../../src/runtime/ranking_evidence.cpp), [docs/ranking.md](../../../../ranking.md), [docs/ranking_accounting.md](../../../../ranking_accounting.md) |

## B0039

[Lines 236–259](../../../../../tests/unit/ranking_public_independent_test.cpp#L236); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void verify_depth_scores(const BooleanFixture& fixture, const ranking::Result& result, bool hot_r) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Check the three literal Boolean candidates' captured depth score fields and deterministic winner for one of two physical-input weightings. |
| inputs / outputs | A fixture, owning Result, and hot-table selector choose hard-coded per-label numerator expectations; every score's denominator is 100, height is 2, and three occurrence depths are checked against fixture arrays. |
| invariants | The helper covers only the supplied three candidate shapes and specified R90/S5/T5 or R5/S5/T90 captured weights; it is not a general score oracle or performance theorem. |
| ownership | Borrows fixture/result; maps and seen sets are temporary test-side values. Result and candidate evidence remain owned by their handles. |
| failure | Missing structural labels, wrong score/evidence, or wrong winner throws runtime_error; allocation and map lookup exceptions propagate. |
| cost | Scans each retained score and three depth entries, with ordered-map/set lookups and temporary bookkeeping; cost is small for this fixture but not a bound for other snapshots. |
| Design | [tests/unit/ranking_public_independent_test.cpp](../../../../../tests/unit/ranking_public_independent_test.cpp), [include/crown/planner/ranking.hpp](../../../../../include/crown/planner/ranking.hpp), [src/planner/ranking.cpp](../../../../../src/planner/ranking.cpp), [tests/candidates/trees/boolean_rst_native_s_root.tree.json](../../../../../tests/candidates/trees/boolean_rst_native_s_root.tree.json), [docs/ranking.md](../../../../ranking.md) |

## B0041

[Lines 261–277](../../../../../tests/unit/ranking_public_independent_test.cpp#L261); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void candidate_semantics_and_height(const BooleanFixture& fixture) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Exercise empty, partial, and complete candidate snapshots under height-only ranking and check runtime semantics for all three literal trees. |
| inputs / outputs | Ranks the empty snapshot directly, ranks the one-candidate prefix and complete three-candidate family, then initializes a runtime per labeled candidate and deletes/reinserts the sole S witness. |
| invariants | Empty input yields no_candidates; prefix ranking preserves nonexhausted state; complete height ties use the full structural key while retaining the proof. Runtime rows return to the original database after reinsertion. |
| ownership | Fixture retains snapshots and source database; each loop-local PhysicalRuntime owns its lowered plan/state and is destroyed at iteration end. |
| failure | Any stop, wrong snapshot/proof, literal answer, or recovery mismatch throws; lowering/runtime setup can fail independently. |
| cost | Makes three rank attempts: the empty snapshot (0 candidates, expected no_candidates), the saved prefix (1), and the complete snapshot (3). It then lowers each of the three candidates into a runtime and applies one delete plus one reinsertion to each (six apply calls). Runtime join/update work depends on plan/database; the fixture does not measure CPU or allocations. |
| Design | [tests/unit/ranking_public_independent_test.cpp](../../../../../tests/unit/ranking_public_independent_test.cpp), [include/crown/planner/ranking.hpp](../../../../../include/crown/planner/ranking.hpp), [src/planner/ranking.cpp](../../../../../src/planner/ranking.cpp), [src/planner/lower.cpp](../../../../../src/planner/lower.cpp), [docs/ranking.md](../../../../ranking.md) |

## B0043

[Lines 279–378](../../../../../tests/unit/ranking_public_independent_test.cpp#L279); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void hot_reversal_and_memory(const BooleanFixture& fixture) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Check workload-driven depth winner reversal, current capture binding, candidate-local slot-model output, payload-limit transactionality, and evidence retention across owner reset. |
| inputs / outputs | On a physical owner it commits 90/5/5 no-op inputs, captures epoch-100 evidence, verifies depth scores and rank_current, then ranks tuple/index slots. It applies exact modeled-payload and one-byte-under requests, resets workload statistics, commits 5/5/90 more no-ops, and checks new versus old evidence at epochs 200 and 100. |
| invariants | The Boolean fixture's three candidate models preserve each topology, index/population/slot term and yield 24 for native_s and 32 for each generalized form. Generalized records/survivors use the sum-of-child parent-support upper bound of 2, not observed distinct keys; these are abstract slot proxies, not measured bytes or multiplicities. The one-under payload request stops without a result and leaves the prior owning Result unchanged; reset stales the depth interval but not unchanged source-cardinality facts. |
| ownership | PhysicalRuntime owns mutable committed state and workload collector; RuntimeEvidence and planner Results are immutable owning handles. Local modeled plans/results retain their own score/evidence backing and are released at function exit. |
| failure | Every capture/rank/model/assertion is checked; byte-limit failure is expected only for the decremented cap. Runtime input, capture, lower, or allocation failure can abort the group; the function does not catch or convert them. |
| cost | Applies 100 no-op events before first capture and 100 after reset, ranks three candidates under multiple policies, inspects each modeled plan's nodes/relations/indexes, then runs two payload-cap calls. Logical payload/work accounting is not actual allocator bytes, RSS, or CPU time. |
| Design | [tests/unit/ranking_public_independent_test.cpp](../../../../../tests/unit/ranking_public_independent_test.cpp), [include/crown/planner/ranking.hpp](../../../../../include/crown/planner/ranking.hpp), [src/planner/ranking.cpp](../../../../../src/planner/ranking.cpp), [src/runtime/ranking_evidence.cpp](../../../../../src/runtime/ranking_evidence.cpp), [docs/ranking.md](../../../../ranking.md), [docs/ranking_accounting.md](../../../../ranking_accounting.md) |

## B0045

[Lines 380–413](../../../../../tests/unit/ranking_public_independent_test.cpp#L380); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void changed_noop_abort_and_freshness(const BooleanFixture& fixture) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Check changed and no-op input accounting, private pending capture, rollback, stale/fresh owner identities, rebuild isolation, and saved evidence after move. |
| inputs / outputs | A physical owner adds a new row, repeats it as a no-op, erases it, then erases it again; the capture expects table-0 counts {2 inserts,2 erases,2 changed,2 no-op} and denominator 4. A pending erase is captured before rollback, followed by a successful no-op, rebuilt owner, and moved owner. |
| invariants | Pending private facts are unavailable; rollback preserves committed epoch/data and prior evidence; a committed no-op advances/stales its epoch; rebuilt data has a foreign owner identity; moved owner accepts its newly captured evidence while old evidence retains its prior epoch and denominator. |
| ownership | The local owner initially holds the runtime state; pending is a prepared update handle for that same owner. rebuilt is a separate runtime owner built from equal data. After moved = std::move(owner), moved owns the original owner state and owner is moved-from. Captured RuntimeEvidence handles retain immutable as-of facts. |
| failure | Any mismatch in counts, freshness reason, rollback state, owner identity, or retained history throws. prepare/apply/rebuild/capture may also fail through runtime APIs. |
| cost | Performs four initial apply attempts, one pending prepare/capture/rollback, one committed no-op, one rebuild, and captures on original/moved owners; runtime work follows the plan/update path. |
| Design | [tests/unit/ranking_public_independent_test.cpp](../../../../../tests/unit/ranking_public_independent_test.cpp), [include/crown/runtime/ranking_evidence.hpp](../../../../../include/crown/runtime/ranking_evidence.hpp), [src/runtime/ranking_evidence.cpp](../../../../../src/runtime/ranking_evidence.cpp), [docs/ranking.md](../../../../ranking.md) |

## B0047

[Lines 415–529](../../../../../tests/unit/ranking_public_independent_test.cpp#L415); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void unavailable_and_resources(const BooleanFixture& fixture) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Exercise depth versus source-cardinality availability, explicit height fallback, C02 and native capture resource stops, and revalidation after collector changes. |
| inputs / outputs | Uses a counters-off owner, then period-64/offset-63 sampling, zero-work processing, omitted source capture, zero-work/zero-byte source capture, and cardinality-only capture; it tries work/cell/payload/candidate/bit limits, exact/one-under work, zero/negative time, and a reconfigured interval. |
| invariants | Unavailable depth does not erase independently usable memory facts; source-budget exhaustion stays a reason; resource stops never produce fallback results; row/key scan limits of zero still permit exact cardinality-only capture for these sources. All checks are specific to this three-table fixture and these request settings. |
| ownership | The PhysicalRuntime owns counters and source state; each capture/result owns its immutable evidence. Request/CaptureOptions values are local copies; no ranking call mutates the owner. |
| failure | Unexpected stop, reason, component count, cap result, or owner sequence throws. Expected native source unavailability remains a complete bounded capture, while C02 processing failure has no evidence. |
| cost | Runs repeated rankings/captures and five resource-limited rank requests: work=0, cells=0, payload_bytes=0, candidates=2 for this three-candidate snapshot, and score_bits=1 (only the first three are zero caps). It also exercises exact/one-under work, zero/negative active time, C02 processing work=0 capture, source_cardinalities=false, source-state work=0 and accounted_bytes=0, and cardinality-only rows=0/distinct_keys=0 capture, followed by source fallback/rank checks and interval revalidation. Logical counters/time are not whole-host CPU or allocator measurements. |
| Design | [tests/unit/ranking_public_independent_test.cpp](../../../../../tests/unit/ranking_public_independent_test.cpp), [include/crown/planner/ranking.hpp](../../../../../include/crown/planner/ranking.hpp), [include/crown/runtime/ranking_evidence.hpp](../../../../../include/crown/runtime/ranking_evidence.hpp), [src/runtime/ranking_evidence.cpp](../../../../../src/runtime/ranking_evidence.cpp), [src/planner/ranking.cpp](../../../../../src/planner/ranking.cpp), [docs/ranking_accounting.md](../../../../ranking_accounting.md) |

## B0049

[Lines 531–602](../../../../../tests/unit/ranking_public_independent_test.cpp#L531); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void normalized_alias_mapping() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Check SQL alias normalization, physical-base routing, workload denominator/cardinality mapping, candidate-local normalized models, and independent lowering sublimits. |
| inputs / outputs | Binds/normalizes a self-join SQL query over physical table r plus an unused table; proves/enumerates candidates, lowers a normalized candidate, builds a two-table database/runtime, records no-ops and absent deletes, captures evidence, then tests four zeroed lowering/identity/replay/normalization sublimits. |
| invariants | The two logical aliases both route to physical base table 1; unused physical table 0 remains in input denominator but is omitted from source scan. The fixture expects depth 10/7, physical cardinality 2, and candidate models retaining normalized adapter context. These literals cover this inline query only. |
| ownership | Bound/normalized program, candidate snapshots, physical plan, and runtime are local owning values; returned Evidence/Results retain immutable copies/handles. Database and runtime own the test rows. |
| failure | Binding, normalization, proof/provider, lower, capture, and ranking failures propagate or fail an assertion; each zero sublimit is expected to stop at lowering_limit without a result. |
| cost | Binds/normalizes one SQL statement, runs the proof/provider setup, performs two ordinary rankings (depth and slots) plus four separately sublimit-constrained slot rankings, and makes one core-only capture attempt whose owner-stamp comparison is conditional on returned evidence. It also applies seven no-op/absent events and inspects captured evidence/candidate scores. No row/time/CPU bound follows from logical counters. |
| Design | [tests/unit/ranking_public_independent_test.cpp](../../../../../tests/unit/ranking_public_independent_test.cpp), [src/frontend/bind.cpp](../../../../../src/frontend/bind.cpp), [src/frontend/normalize.cpp](../../../../../src/frontend/normalize.cpp), [include/crown/planner/lower.hpp](../../../../../include/crown/planner/lower.hpp), [src/planner/ranking.cpp](../../../../../src/planner/ranking.cpp), [docs/ranking.md](../../../../ranking.md) |

## B0051

[Lines 604–637](../../../../../tests/unit/ranking_public_independent_test.cpp#L604); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void statistical_ties_and_binding(const BooleanFixture& fixture) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Check a three-way equal-input-weight score, structural-key tie break, partial-prefix ranking, evidence binding mismatch, and moved-from snapshot rejection. |
| inputs / outputs | Commits one no-op per physical table, captures/ranks the complete snapshot, ranks the saved partial snapshot, creates a second provider after incrementing Catalog version, checks rank/capture binding mismatch, then moves and reuses a snapshot handle. |
| invariants | Equal statistical scores select min(full structural key); the prefix remains one candidate and nonexhausted; evidence for a different catalog version is rejected without fallback; moved-from snapshot is invalid and grants no rank authority. |
| ownership | Fixture retains original snapshots/evidence; the versioned provider and moved-from/retained handles have separate ownership. Results share their snapshot/proof backing. |
| failure | Any unexpected result/stop/reason throws. Search/provider creation or capture can also fail. |
| cost | Three no-op updates; four ranking attempts: complete tied family, saved prefix, different-binding request, and moved-from snapshot rejection. It also runs one second bounded proof/provider campaign, one capture-mismatch attempt and snapshot moves. Candidate score/key work depends on each valid prefix; the last invalid-handle attempt is still a rank call. |
| Design | [tests/unit/ranking_public_independent_test.cpp](../../../../../tests/unit/ranking_public_independent_test.cpp), [include/crown/planner/ranking.hpp](../../../../../include/crown/planner/ranking.hpp), [src/planner/ranking.cpp](../../../../../src/planner/ranking.cpp), [src/runtime/ranking_evidence.cpp](../../../../../src/runtime/ranking_evidence.cpp), [docs/ranking.md](../../../../ranking.md) |

## B0053

[Lines 639–676](../../../../../tests/unit/ranking_public_independent_test.cpp#L639); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void mode_reset_drop(const BooleanFixture& fixture) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Check Delta mode interval rotation and QuerySession drop behavior while saved live evidence remains readable as historical input. |
| inputs / outputs | Creates a maintenance-mode DeltaRuntime, commits a no-op, captures, switches to delta mode, recaptures an empty interval, then captures a QuerySession before drop and captures it after release; it ranks both released fallback and old as-of evidence. |
| invariants | Mode rotation leaves sequence/data and source-cardinality usability intact while invalidating depth interval. Drop marks new facts released and revalidation boundary released, yet the old owning session context/evidence stays readable for pure as-of ranking. |
| ownership | DeltaRuntime and QuerySession own mutable mode/lifecycle state; RuntimeEvidence, SessionStatisticsContext, and planner Results are immutable shared handles that can outlive the state transition. |
| failure | Unexpected mode/currentness/released/fallback/history state throws; runtime owner construction, capture, mode change, and drop can fail through their APIs. |
| cost | Creates two owners, applies one Delta update, performs captures around one mode change and one drop, and runs two historical/current rankings on three candidates; costs follow state capture and score policy. |
| Design | [tests/unit/ranking_public_independent_test.cpp](../../../../../tests/unit/ranking_public_independent_test.cpp), [include/crown/runtime/ranking_evidence.hpp](../../../../../include/crown/runtime/ranking_evidence.hpp), [src/runtime/ranking_evidence.cpp](../../../../../src/runtime/ranking_evidence.cpp), [include/crown/planner/ranking.hpp](../../../../../include/crown/planner/ranking.hpp), [docs/ranking.md](../../../../ranking.md) |

## B0055

[Lines 678–723](../../../../../tests/unit/ranking_public_independent_test.cpp#L678); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void decimal_and_repeated_output_payload() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Exercise a decimal-valued unary plan with a repeated output variable and its candidate-local slot model/payload boundary. |
| inputs / outputs | Creates one inline Catalog/Query, proves and enumerates its candidate, initializes a two-row Decimal database, captures physical source cardinality, and ranks tuple/index slots at exact modeled payload then one byte below. |
| invariants | The literal runtime output repeats the same value in both output columns; source cardinality is 2 despite filtering; this fixture's candidate score is 13 slots. The modeled layout enforces equality on repeated output fields. These are fixture assertions, not general bounds. |
| ownership | Local Catalog, Query, proof/provider snapshot, compiled plan, runtime, evidence, and Result own their respective values/handles; the Result remains alive across the later failed rank. |
| failure | Decimal parsing, proof/provider, lowering/capture/ranking, unequal repeated tuple validation, and cap checks may fail; the one-under cap is expected to return byte_limit with no partial result. |
| cost | Parses two large Decimal constants, performs one bounded proof/provider setup, evaluates one candidate and result, formats/checks the repeated tuple, and runs exact plus one-under payload ranks. Decimal digit/plan payload cost depends on values and ABI model. |
| Design | [tests/unit/ranking_public_independent_test.cpp](../../../../../tests/unit/ranking_public_independent_test.cpp), [include/crown/planner/ranking.hpp](../../../../../include/crown/planner/ranking.hpp), [src/planner/ranking.cpp](../../../../../src/planner/ranking.cpp), [src/planner/ranking_payload.cpp](../../../../../src/planner/ranking_payload.cpp), [docs/ranking.md](../../../../ranking.md), [docs/ranking_accounting.md](../../../../ranking_accounting.md) |

## B0056

[Lines 724–725](../../../../../tests/unit/ranking_public_independent_test.cpp#L724); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L724-L725:sha256:c2bd7638f09d52cb034ed574f539304035fc6fab162bf8d5fa20a35d8c7288a1
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Close the recorded declaration scopes in ranking_public_independent_test.cpp: namespace (anonymous). |
| inputs / outputs | Preceding namespace, type or initializer declarations in; completed lexical boundary out. |
| invariants | Brace-opening context is recorded in root-scope-context-v1.json. These are declaration/initializer boundaries, not an independent update, validation or recovery operation. |
| ownership | Enclosing objects and borrowed fields keep their declared ownership. This punctuation creates no new owner. |
| failure | Malformed scope syntax is a compile error. Any initializer/constructor failure belongs to the enclosing object declaration. |
| cost | No separate loop, guard or engine call is introduced by the delimiter; enclosing initialization and object lifetime still have their actual costs. |
| Design | [tests/unit/ranking_public_independent_test.cpp](../../../../../tests/unit/ranking_public_independent_test.cpp), [docs/ranking.md](../../../../ranking.md), [docs/code_review.md](../../../../code_review.md) |

## B0057

[Lines 726–744](../../../../../tests/unit/ranking_public_independent_test.cpp#L726); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
int main(int argc, char** argv) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Schedule the public ranking test's fixture setup and eight assertion groups. |
| inputs / outputs | Requires one repository-root argument, builds BooleanFixture, then calls candidate semantics, hot reversal/memory, changed/no-op/abort freshness, unavailable/resources, statistical ties/binding, normalized alias mapping, mode reset/drop, and decimal/repeated-output groups in that source order; returns 0 after the summary line. |
| invariants | The eight groups cover this checked fixture set only. A successful source-level schedule is not evidence that this executable was run or that general ranking behavior is proved. |
| ownership | Main owns BooleanFixture for all groups; each group owns its temporary runtimes, captures, and results. |
| failure | Wrong argc or a caught std::exception from a group prints a diagnostic and returns 1; the handler does not catch non-std exceptions. This packet does not execute main. |
| cost | Runs one proof/provider fixture setup and eight groups; nested update/capture/rank/lowering loops have the per-helper costs above. There is no single fixed CPU or total-allocation estimate. |
| Design | [tests/unit/ranking_public_independent_test.cpp](../../../../../tests/unit/ranking_public_independent_test.cpp), [src/planner/ranking.cpp](../../../../../src/planner/ranking.cpp), [src/runtime/ranking_evidence.cpp](../../../../../src/runtime/ranking_evidence.cpp), [docs/ranking.md](../../../../ranking.md) |
