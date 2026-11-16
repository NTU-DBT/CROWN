# `tests/support/selection_independent_fixture.hpp` — block usage map

[Source](../../../../../tests/support/selection_independent_fixture.hpp) · [Source index](../../../README.md) · [Subsystem contracts](../../../subsystem_contracts.md) · [Reviewed primitives](../../../primitives.md)

Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection.

Snapshot SHA-256: `b3689fc082b1e981bc6c72bfa4bf59f7cf07d712e1de760c30d31a8ffcd71336`. 282 lines partitioned into 36 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [tests](../../../subsystem_contracts.md#tests). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/code_review.md](../../../../code_review.md), [docs/reference_fuzz.md](../../../../reference_fuzz.md), [docs/task_ledger.md](../../../../task_ledger.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–32](../../../../../tests/support/selection_independent_fixture.hpp#L1) | Imports dependencies; guards repeated header inclusion. | source comment (unverified): // Literal row/shape lineage: the reviewer's accepted C02 independent public · [reviewed contract](#b0001) |
| [B0002 · 33–41](../../../../../tests/support/selection_independent_fixture.hpp#L33) | declares namespace scope; declares aliases; declares values/defaults or compile-time conditions. |  · [reviewed contract](#b0002) |
| [B0003 · 42–44](../../../../../tests/support/selection_independent_fixture.hpp#L42) | Callable definition: inline void check(bool condition, const char* message) | calls std::runtime_error; guard inline void check(bool condition, const char* message) { · [reviewed contract](#b0003) |
| [B0004 · 45–49](../../../../../tests/support/selection_independent_fixture.hpp#L45) | Callable definition: inline std::string read(const std::filesystem::path& path) | calls input, check, good; guard check(input.good(), "independent fixture file is unreadable");; returns {std::istreambuf_iterator&lt;char&gt;{input}, std::istreambuf_iterator&lt;char&gt;{}} · [reviewed contract](#b0004) |
| [B0005 · 50–52](../../../../../tests/support/selection_independent_fixture.hpp#L50) | Callable definition: template&lt;class Text&gt; inline std::string caller_text(const Text& text) | calls data, size; returns std::string{text.data(), text.size()} · [reviewed contract](#b0005) |
| [B0006 · 53–70](../../../../../tests/support/selection_independent_fixture.hpp#L53) | Callable definition: inline p::VerifiedOptimum prove(const Catalog& catalog, const Query& query) | calls p::ExactSearch::create, advance, optimum, check; guard check(result && result-&gt;valid(), "P06 failed to publish its real checked proof");; returns *result; 1 loop sites · [reviewed contract](#b0006) |
| [B0007 · 71–79](../../../../../tests/support/selection_independent_fixture.hpp#L71) | Callable definition: inline p::CandidateProvider provider(p::VerifiedOptimum proof) | calls p::CandidateProvider::create, std::move; returns p::CandidateProvider::create(std::move(proof), {}, limits) · [reviewed contract](#b0007) |
| [B0008 · 80–89](../../../../../tests/support/selection_independent_fixture.hpp#L80) | Callable definition: inline void finish(p::CandidateProvider& value) | calls advance, check, std::runtime_error; guard check(next.stopped_for == p::CandidateStop::candidate_ready \|\|; 1 loop sites · [reviewed contract](#b0008) |
| [B0009 · 90–94](../../../../../tests/support/selection_independent_fixture.hpp#L90) | Callable definition: inline p::CandidateSnapshot candidates(const Catalog& catalog, const Query& query) | calls provider, prove, finish, snapshot; returns value.snapshot() · [reviewed contract](#b0009) |
| [B0010 · 95–107](../../../../../tests/support/selection_independent_fixture.hpp#L95) | Callable definition: inline std::string shape_node(const FreeConnexTree& tree, NodeId id) | calls at, std::to_string, push_back, std::sort; returns out + @; growth push_back; 3 loop sites · [reviewed contract](#b0010) |
| [B0011 · 108–110](../../../../../tests/support/selection_independent_fixture.hpp#L108) | Callable definition: inline std::string shape(const FreeConnexTree& tree) | calls shape_node; returns tree.root ? shape_node(tree, *tree.root) : @ · [reviewed contract](#b0011) |
| [B0012 · 111–112](../../../../../tests/support/selection_independent_fixture.hpp#L111) | Explanatory comments or spacing. | source comment (unverified): // Aggregate copies deep-copy DTO/maps/rows while typed proof-prefix handles share · [reviewed contract](#b0012) |
| [B0013 · 113–119](../../../../../tests/support/selection_independent_fixture.hpp#L113) | Type/record definition: struct BooleanFixture | source comment (unverified): // Aggregate copies deep-copy DTO/maps/rows while typed proof-prefix handles share · [reviewed contract](#b0013) |
| [B0014 · 120–154](../../../../../tests/support/selection_independent_fixture.hpp#L120) | Callable definition: inline BooleanFixture boolean_fixture(const std::filesystem::path& root) | calls io::read_document, read, prove, check; guard check(proof.height() == 2, "literal Boolean optimum differs from two");; returns result; growth emplace; 3 loop sites · [reviewed contract](#b0014) |
| [B0015 · 155–157](../../../../../tests/support/selection_independent_fixture.hpp#L155) | Callable definition: inline PhysicalPlan lower(const p::MinimumHeightCandidate& member, const PhysicalOptions& options = {}) | calls p::lower_tree, catalog, query, tree; returns p::lower_tree(member.catalog(), member.query(), member.tree(), options) · [reviewed contract](#b0015) |
| [B0016 · 158–162](../../../../../tests/support/selection_independent_fixture.hpp#L158) | Callable definition: inline r::workload::Options counters() | calls ; returns result · [reviewed contract](#b0016) |
| [B0017 · 163–167](../../../../../tests/support/selection_independent_fixture.hpp#L163) | Callable definition: inline void noop(r::PhysicalRuntime& owner, std::size_t table, const Row& row, unsigned count) | calls check, apply, sequence; guard check(!owner.apply({owner.sequence() + 1, TableId{table}, SetOperation::insert, row}).input.physica…; growth insert; 1 loop sites · [reviewed contract](#b0017) |
| [B0018 · 168–173](../../../../../tests/support/selection_independent_fixture.hpp#L168) | Callable definition: inline void hot(r::PhysicalRuntime& owner, const BooleanFixture& fixture, bool hot_r = true) | calls configure_workload_statistics, counters, noop, begin · [reviewed contract](#b0018) |
| [B0019 · 174–179](../../../../../tests/support/selection_independent_fixture.hpp#L174) | Callable definition: inline Relation answers(const r::PhysicalRuntime& owner) | calls results, next, insert, crown::storage::export_row; returns result; growth insert; 1 loop sites · [reviewed contract](#b0019) |
| [B0020 · 180–186](../../../../../tests/support/selection_independent_fixture.hpp#L180) | Callable definition: template&lt;class Runtime&gt; capture::RuntimeEvidence capture_checked(const p::CandidateSnapshot& snapshot, const Runtime& owner, cons… | calls capture::capture, check, has_value; guard check(result.stop == rank::Stop::complete && result.evidence.has_value(), "real owner capture faile…; returns *result.evidence · [reviewed contract](#b0020) |
| [B0021 · 187–187](../../../../../tests/support/selection_independent_fixture.hpp#L187) | Explanatory comments or spacing. | source comment (unverified): // Returned reference borrows the Attempt. Copy the typed handle to retain it. · [reviewed contract](#b0021) |
| [B0022 · 188–191](../../../../../tests/support/selection_independent_fixture.hpp#L188) | Callable definition: inline const s::Selection& complete(const s::Attempt& result) | calls check, has_value; guard check(result.stop == s::Stop::complete && result.selection.has_value(), "C05 did not publish a comp…; returns *result.selection; source comment (unverified): // Returned reference borrows the Attempt. Copy the typed handle to retain it. · [reviewed contract](#b0022) |
| [B0023 · 192–192](../../../../../tests/support/selection_independent_fixture.hpp#L192) | Explanatory comments or spacing. | source comment (unverified): // Returned reference borrows the Attempt; it does not extend temporary lifetime. · [reviewed contract](#b0023) |
| [B0024 · 193–196](../../../../../tests/support/selection_independent_fixture.hpp#L193) | Callable definition: inline const current::CurrentSelection& complete(const current::Attempt& result) | calls check, has_value; guard check(result.stop == s::Stop::complete && result.selection.has_value(), "C05 did not publish a comp…; returns *result.selection; source comment (unverified): // Returned reference borrows the Attempt; it does not extend temporary lifetime. · [reviewed contract](#b0024) |
| [B0025 · 197–199](../../../../../tests/support/selection_independent_fixture.hpp#L197) | Callable definition: inline bool has(rank::Reasons value, rank::Reason flag) | calls rank::reason; returns (value & rank::reason(flag)) != 0 · [reviewed contract](#b0025) |
| [B0026 · 200–204](../../../../../tests/support/selection_independent_fixture.hpp#L200) | Callable definition: inline s::Request height() | calls ; returns result · [reviewed contract](#b0026) |
| [B0027 · 205–209](../../../../../tests/support/selection_independent_fixture.hpp#L205) | Callable definition: inline s::Request depth() | calls ; returns result · [reviewed contract](#b0027) |
| [B0028 · 210–214](../../../../../tests/support/selection_independent_fixture.hpp#L210) | Callable definition: inline s::Request slots() | calls depth; returns result · [reviewed contract](#b0028) |
| [B0029 · 215–217](../../../../../tests/support/selection_independent_fixture.hpp#L215) | Callable definition: inline std::string label(const BooleanFixture& fixture, const s::Selection& result) | calls at, selected, structural_key; returns fixture.label_by_key.at(result.selected().structural_key()) · [reviewed contract](#b0029) |
| [B0030 · 218–223](../../../../../tests/support/selection_independent_fixture.hpp#L218) | Callable definition: inline const rank::Result& assessment(const s::Selection& result, s::AssessmentPurpose purpose) | calls std::find_if, assessments, begin, end; guard check(found != result.assessments().end(), "required complete assessment is missing");; returns value.purpose == purpose; found-&gt;result · [reviewed contract](#b0030) |
| [B0031 · 224–233](../../../../../tests/support/selection_independent_fixture.hpp#L224) | Callable definition: inline void literal_depth(const BooleanFixture& fixture, const rank::Result& result, bool hot_r = true) | calls check, scores, size, effective_policy; guard check(result.scores().size() == 3 && result.effective_policy() == rank::Policy::committed_input_nat…; 1 loop sites · [reviewed contract](#b0031) |
| [B0032 · 234–240](../../../../../tests/support/selection_independent_fixture.hpp#L234) | Callable definition: inline void literal_slots(const BooleanFixture& fixture, const rank::Result& result) | calls check, scores, size, effective_policy; guard check(result.scores().size() == 3 && result.effective_policy() == rank::Policy::tuple_index_slots,; 1 loop sites · [reviewed contract](#b0032) |
| [B0033 · 241–242](../../../../../tests/support/selection_independent_fixture.hpp#L241) | Explanatory comments or spacing. | source comment (unverified): // tie tuples borrow fields only through these immediate comparisons; arrays stay owned · [reviewed contract](#b0033) |
| [B0034 · 243–265](../../../../../tests/support/selection_independent_fixture.hpp#L243) | Callable definition: inline bool same_workload(const r::workload::Snapshot& a, const r::workload::Snapshot& b) | calls std::tie, plan, physical_sha256, stamp; returns std::tie(x.attempts,x.committed,x.aborted,x.selected,x.complete,x.aborted_selected,; std::tie(x.own…; source comment (unverified): // tie tuples borrow fields only through these immediate comparisons; arrays stay owned · [reviewed contract](#b0034) |
| [B0035 · 266–281](../../../../../tests/support/selection_independent_fixture.hpp#L266) | Callable definition: inline p::VerifiedOptimum replay(const Catalog& catalog, const Query& query, p::HeightCertificate certificate) | calls p::CertificateReplay::create, std::move, advance, checked; guard check(checked && checked-&gt;valid() && checked-&gt;optimum(), "real replay did not verify the supplied r…; returns *checked-&gt;optimum(); 1 loop sites · [reviewed contract](#b0035) |
| [B0036 · 282–282](../../../../../tests/support/selection_independent_fixture.hpp#L282) | Closes surrounding scope/type. | source comment (unverified): // namespace c05_independent · [reviewed contract](#b0036) |

## B0001

[Lines 1–32](../../../../../tests/support/selection_independent_fixture.hpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L1-L32:sha256:3a359e45a0ea9165fcdec986502b2b100476f4bcc506d22bc6d58c7dce540291
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Prepare selection_independent_fixture.hpp: include "crown/api/error.hpp", "crown/frontend/bind.hpp", "crown/frontend/normalize.hpp", "crown/io/document.hpp", "crown/io/tree.hpp", "crown/planner/lower.hpp", "crown/planner/search.hpp", "crown/planner/selection.hpp", "crown/runtime/selection.hpp", &lt;algorithm&gt;, &lt;array&gt;, &lt;chrono&gt;, &lt;cstddef&gt;, &lt;cstdint&gt;, &lt;filesystem&gt;, &lt;fstream&gt;, &lt;iterator&gt;, &lt;map&gt;, &lt;optional&gt;, &lt;set&gt;, &lt;stdexcept&gt;, &lt;string&gt;, &lt;tuple&gt;, &lt;type_traits&gt;, &lt;utility&gt;, &lt;vector&gt;. |
| inputs / outputs | Compiler-visible dependencies, names and the recorded declarations in; declarations available to the following fixture/CLI/example definitions out. |
| invariants | Declarations are scoped to this source/header and its selected ABI. Included code has its own effects; names and editable fixture values do not confer proof, admission or publication authority. |
| ownership | Aliases/includes do not create a query owner. Pointers/references/views are non-owning. Containers own their elements, which can themselves be borrowed pointers or numeric IDs. Only documented owning shared-control handles retain controls; IDs/slot-handle values do not independently keep an arena/runtime alive. |
| failure | Missing headers, ill-formed names/types, failed static assertions or active #error directives stop compilation. No runtime rejection/rollback mechanism is implemented by aliases or function prototypes. |
| cost | Preprocessing and type/constraint instantiation cost compilation. Alias/prototype syntax does not invoke the declared operation; any included definitions keep their own initialization effects. |
| Design | [tests/support/selection_independent_fixture.hpp](../../../../../tests/support/selection_independent_fixture.hpp), [docs/selection.md](../../../../selection.md), [docs/code_review.md](../../../../code_review.md) |

## B0002

[Lines 33–41](../../../../../tests/support/selection_independent_fixture.hpp#L33); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L33-L41:sha256:9101d8318e1f82713a8724e27339a5b08f5a72b8796d4731326fa1695e0c1412
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Prepare selection_independent_fixture.hpp: bind local aliases/name imports. |
| inputs / outputs | Compiler-visible dependencies, names and the recorded declarations in; declarations available to the following fixture/CLI/example definitions out. |
| invariants | Declarations are scoped to this source/header and its selected ABI. Included code has its own effects; names and editable fixture values do not confer proof, admission or publication authority. |
| ownership | Aliases/includes do not create a query owner. Pointers/references/views are non-owning. Containers own their elements, which can themselves be borrowed pointers or numeric IDs. Only documented owning shared-control handles retain controls; IDs/slot-handle values do not independently keep an arena/runtime alive. |
| failure | Missing headers, ill-formed names/types, failed static assertions or active #error directives stop compilation. No runtime rejection/rollback mechanism is implemented by aliases or function prototypes. |
| cost | Preprocessing and type/constraint instantiation cost compilation. Alias/prototype syntax does not invoke the declared operation; any included definitions keep their own initialization effects. |
| Design | [tests/support/selection_independent_fixture.hpp](../../../../../tests/support/selection_independent_fixture.hpp), [docs/selection.md](../../../../selection.md), [docs/code_review.md](../../../../code_review.md) |

## B0003

[Lines 42–44](../../../../../tests/support/selection_independent_fixture.hpp#L42); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
inline void check(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Require one independent public-fixture assertion without converting it into admission authority. |
| inputs / outputs | Throws runtime_error(message) when condition is false; otherwise returns. |
| invariants | Only actual public checked producers create proof/candidate/selection handles. This check is a test outcome, not a private factory. |
| ownership | Diagnostic pointer is borrowed until exception construction copies its content. |
| failure | Failure message allocation can itself fail; fixture has no catch or fallback. |
| cost | Fixed success branch; failure allocates/throws ordinary diagnostic. |
| Design | [tests/support/selection_independent_fixture.hpp](../../../../../tests/support/selection_independent_fixture.hpp), [tests/unit/selection_public_independent_test.cpp](../../../../../tests/unit/selection_public_independent_test.cpp), [tests/unit/selection_binding_independent_test.cpp](../../../../../tests/unit/selection_binding_independent_test.cpp), [tests/unit/selection_publication_fault_independent_test.cpp](../../../../../tests/unit/selection_publication_fault_independent_test.cpp), [tests/candidates/queries/boolean_rst.cq.json](../../../../../tests/candidates/queries/boolean_rst.cq.json), [tests/candidates/trees/boolean_rst_native_s_root.tree.json](../../../../../tests/candidates/trees/boolean_rst_native_s_root.tree.json), [tests/candidates/trees/boolean_rst_generalized_x_root.tree.json](../../../../../tests/candidates/trees/boolean_rst_generalized_x_root.tree.json), [tests/candidates/trees/boolean_rst_generalized_y_root.tree.json](../../../../../tests/candidates/trees/boolean_rst_generalized_y_root.tree.json), [include/crown/planner/search.hpp](../../../../../include/crown/planner/search.hpp), [include/crown/planner/candidates.hpp](../../../../../include/crown/planner/candidates.hpp), [include/crown/planner/selection.hpp](../../../../../include/crown/planner/selection.hpp), [include/crown/runtime/selection.hpp](../../../../../include/crown/runtime/selection.hpp), [docs/planner_continuations.md](../../../../planner_continuations.md), [docs/candidate_alternatives.md](../../../../candidate_alternatives.md), [docs/selection.md](../../../../selection.md), [docs/statistics.md](../../../../statistics.md), [docs/code_review.md](../../../../code_review.md) |

## B0004

[Lines 45–49](../../../../../tests/support/selection_independent_fixture.hpp#L45); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
inline std::string read(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Read fixture bytes through an ordinary input file stream. |
| inputs / outputs | Opens path, checks initial stream.good(), then constructs std::string from the remaining character iterator range. |
| invariants | Initial readability is asserted; the helper does not enable fail/bad exceptions or verify a final read/close success, so later I/O faults need not be reported here. Parsing/admission remains in real io readers. |
| ownership | Result owns independent bytes; local stream closes at return. Filesystem/path are caller-selected, with no stored stream borrow. |
| failure | Open assertion, path/string/allocation errors propagate. A malformed/truncated resulting document is rejected by its actual reader later. |
| cost | Full file read and ordinary growing string allocation; no input limit or native MemoryAccount is installed. |
| Design | [tests/support/selection_independent_fixture.hpp](../../../../../tests/support/selection_independent_fixture.hpp), [tests/unit/selection_public_independent_test.cpp](../../../../../tests/unit/selection_public_independent_test.cpp), [tests/unit/selection_binding_independent_test.cpp](../../../../../tests/unit/selection_binding_independent_test.cpp), [tests/unit/selection_publication_fault_independent_test.cpp](../../../../../tests/unit/selection_publication_fault_independent_test.cpp), [tests/candidates/queries/boolean_rst.cq.json](../../../../../tests/candidates/queries/boolean_rst.cq.json), [tests/candidates/trees/boolean_rst_native_s_root.tree.json](../../../../../tests/candidates/trees/boolean_rst_native_s_root.tree.json), [tests/candidates/trees/boolean_rst_generalized_x_root.tree.json](../../../../../tests/candidates/trees/boolean_rst_generalized_x_root.tree.json), [tests/candidates/trees/boolean_rst_generalized_y_root.tree.json](../../../../../tests/candidates/trees/boolean_rst_generalized_y_root.tree.json), [include/crown/planner/search.hpp](../../../../../include/crown/planner/search.hpp), [include/crown/planner/candidates.hpp](../../../../../include/crown/planner/candidates.hpp), [include/crown/planner/selection.hpp](../../../../../include/crown/planner/selection.hpp), [include/crown/runtime/selection.hpp](../../../../../include/crown/runtime/selection.hpp), [docs/planner_continuations.md](../../../../planner_continuations.md), [docs/candidate_alternatives.md](../../../../candidate_alternatives.md), [docs/selection.md](../../../../selection.md), [docs/statistics.md](../../../../statistics.md), [docs/code_review.md](../../../../code_review.md) |

## B0005

[Lines 50–52](../../../../../tests/support/selection_independent_fixture.hpp#L50); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
template<class Text> inline std::string caller_text(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Copy exact native score/key byte ranges into independent caller text for literal lookup. |
| inputs / outputs | Returns std::string(text.data(),text.size()), including embedded NUL. |
| invariants | Producer text must remain stable through copy; shared typed handle identity does not make the exported bytes shared. |
| ownership | Ordinary owning string is independent of score/account text storage. |
| failure | Allocation failures propagate, with no recapture/validation fallback. |
| cost | O(text bytes) copying and possible ordinary allocation; no small-string guarantee assumed. |
| Design | [tests/support/selection_independent_fixture.hpp](../../../../../tests/support/selection_independent_fixture.hpp), [tests/unit/selection_public_independent_test.cpp](../../../../../tests/unit/selection_public_independent_test.cpp), [tests/unit/selection_binding_independent_test.cpp](../../../../../tests/unit/selection_binding_independent_test.cpp), [tests/unit/selection_publication_fault_independent_test.cpp](../../../../../tests/unit/selection_publication_fault_independent_test.cpp), [tests/candidates/queries/boolean_rst.cq.json](../../../../../tests/candidates/queries/boolean_rst.cq.json), [tests/candidates/trees/boolean_rst_native_s_root.tree.json](../../../../../tests/candidates/trees/boolean_rst_native_s_root.tree.json), [tests/candidates/trees/boolean_rst_generalized_x_root.tree.json](../../../../../tests/candidates/trees/boolean_rst_generalized_x_root.tree.json), [tests/candidates/trees/boolean_rst_generalized_y_root.tree.json](../../../../../tests/candidates/trees/boolean_rst_generalized_y_root.tree.json), [include/crown/planner/search.hpp](../../../../../include/crown/planner/search.hpp), [include/crown/planner/candidates.hpp](../../../../../include/crown/planner/candidates.hpp), [include/crown/planner/selection.hpp](../../../../../include/crown/planner/selection.hpp), [include/crown/runtime/selection.hpp](../../../../../include/crown/runtime/selection.hpp), [docs/planner_continuations.md](../../../../planner_continuations.md), [docs/candidate_alternatives.md](../../../../candidate_alternatives.md), [docs/selection.md](../../../../selection.md), [docs/statistics.md](../../../../statistics.md), [docs/code_review.md](../../../../code_review.md) |

## B0006

[Lines 53–70](../../../../../tests/support/selection_independent_fixture.hpp#L53); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
inline p::VerifiedOptimum prove(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Acquire genuine checked minimum-height authority for the supplied original catalog/query. |
| inputs / outputs | Creates ExactSearch with 100M producer/replay work and logical depth64, advances at most 2000 quanta of 100,000, accepts only published verified_optimum with valid handle; intermediate stops must be quantum work/time. |
| invariants | Does not manufacture a proof from fixture expectations/raw trees or accept verified infeasibility/resource failure as a positive proof. Guard exhaustion fails explicitly. Source binding is the actual public search admission. |
| ownership | Search owns admitted binding/evidence; returned VerifiedOptimum shared control outlives search. Copies retain actual immutable proof graph; default move can empty the moved-from handle. |
| failure | Invalid input, unsupported/failed search, nonquantum resource stop, missing/invalid publication and allocation failure reject; no catch/skip. |
| cost | Actual bounded exact search and independent certificate replay with allocations and active-time checks; driver call bound is not a CPU/time/allocator-byte guarantee. |
| Design | [tests/support/selection_independent_fixture.hpp](../../../../../tests/support/selection_independent_fixture.hpp), [tests/unit/selection_public_independent_test.cpp](../../../../../tests/unit/selection_public_independent_test.cpp), [tests/unit/selection_binding_independent_test.cpp](../../../../../tests/unit/selection_binding_independent_test.cpp), [tests/unit/selection_publication_fault_independent_test.cpp](../../../../../tests/unit/selection_publication_fault_independent_test.cpp), [tests/candidates/queries/boolean_rst.cq.json](../../../../../tests/candidates/queries/boolean_rst.cq.json), [tests/candidates/trees/boolean_rst_native_s_root.tree.json](../../../../../tests/candidates/trees/boolean_rst_native_s_root.tree.json), [tests/candidates/trees/boolean_rst_generalized_x_root.tree.json](../../../../../tests/candidates/trees/boolean_rst_generalized_x_root.tree.json), [tests/candidates/trees/boolean_rst_generalized_y_root.tree.json](../../../../../tests/candidates/trees/boolean_rst_generalized_y_root.tree.json), [include/crown/planner/search.hpp](../../../../../include/crown/planner/search.hpp), [include/crown/planner/candidates.hpp](../../../../../include/crown/planner/candidates.hpp), [include/crown/planner/selection.hpp](../../../../../include/crown/planner/selection.hpp), [include/crown/runtime/selection.hpp](../../../../../include/crown/runtime/selection.hpp), [docs/planner_continuations.md](../../../../planner_continuations.md), [docs/candidate_alternatives.md](../../../../candidate_alternatives.md), [docs/selection.md](../../../../selection.md), [docs/statistics.md](../../../../statistics.md), [docs/code_review.md](../../../../code_review.md) |

## B0007

[Lines 71–79](../../../../../tests/support/selection_independent_fixture.hpp#L71); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
inline p::CandidateProvider provider(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Create a real public alternative provider from an owning checked original optimum. |
| inputs / outputs | Takes proof by value, installs enumeration work100M/depth64/records1M/cells10M/retained32 limits, then moves proof to CandidateProvider::create with default context. |
| invariants | Only typed VerifiedOptimum authority supplies required height; raw certificate/tree/label cannot substitute. Provider owns fresh continuation state; limits do not claim complete family until exhausted. |
| ownership | Lvalue proof argument copies its shared control; moving into provider transfers that local handle. Provider is move-only and owns its own enumeration/admitted metadata. |
| failure | Invalid/moved proof, limits/admission/allocation failures propagate without fixture fallback. |
| cost | Actual provider binding/continuation admission and allocations plus fixed limits setup; no candidate is enumerated merely by this wrapper. |
| Design | [tests/support/selection_independent_fixture.hpp](../../../../../tests/support/selection_independent_fixture.hpp), [tests/unit/selection_public_independent_test.cpp](../../../../../tests/unit/selection_public_independent_test.cpp), [tests/unit/selection_binding_independent_test.cpp](../../../../../tests/unit/selection_binding_independent_test.cpp), [tests/unit/selection_publication_fault_independent_test.cpp](../../../../../tests/unit/selection_publication_fault_independent_test.cpp), [tests/candidates/queries/boolean_rst.cq.json](../../../../../tests/candidates/queries/boolean_rst.cq.json), [tests/candidates/trees/boolean_rst_native_s_root.tree.json](../../../../../tests/candidates/trees/boolean_rst_native_s_root.tree.json), [tests/candidates/trees/boolean_rst_generalized_x_root.tree.json](../../../../../tests/candidates/trees/boolean_rst_generalized_x_root.tree.json), [tests/candidates/trees/boolean_rst_generalized_y_root.tree.json](../../../../../tests/candidates/trees/boolean_rst_generalized_y_root.tree.json), [include/crown/planner/search.hpp](../../../../../include/crown/planner/search.hpp), [include/crown/planner/candidates.hpp](../../../../../include/crown/planner/candidates.hpp), [include/crown/planner/selection.hpp](../../../../../include/crown/planner/selection.hpp), [include/crown/runtime/selection.hpp](../../../../../include/crown/runtime/selection.hpp), [docs/planner_continuations.md](../../../../planner_continuations.md), [docs/candidate_alternatives.md](../../../../candidate_alternatives.md), [docs/selection.md](../../../../selection.md), [docs/statistics.md](../../../../statistics.md), [docs/code_review.md](../../../../code_review.md) |

## B0008

[Lines 80–89](../../../../../tests/support/selection_independent_fixture.hpp#L80); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
inline void finish(p::CandidateProvider& value)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Advance a finite public candidate family until explicit exhaustion. |
| inputs / outputs | Up to2000 quanta of100,000; exhausted returns, only candidate_ready/quantum_work/quantum_time are accepted intermediate stops. |
| invariants | Candidate count alone does not establish family completeness. Resource/failure/cancelled stops or exhausted call guard fail the fixture, preserving no false completed label. |
| ownership | Borrows mutable move-only provider; no output snapshot or borrowed candidate is retained here. |
| failure | Unexpected stop/guard exhaustion throws; provider's own allocation/diagnostic failures propagate. |
| cost | Real enumeration/tree validation/key canonicalization and provider publication; each quantum can allocate and cross soft time boundaries. |
| Design | [tests/support/selection_independent_fixture.hpp](../../../../../tests/support/selection_independent_fixture.hpp), [tests/unit/selection_public_independent_test.cpp](../../../../../tests/unit/selection_public_independent_test.cpp), [tests/unit/selection_binding_independent_test.cpp](../../../../../tests/unit/selection_binding_independent_test.cpp), [tests/unit/selection_publication_fault_independent_test.cpp](../../../../../tests/unit/selection_publication_fault_independent_test.cpp), [tests/candidates/queries/boolean_rst.cq.json](../../../../../tests/candidates/queries/boolean_rst.cq.json), [tests/candidates/trees/boolean_rst_native_s_root.tree.json](../../../../../tests/candidates/trees/boolean_rst_native_s_root.tree.json), [tests/candidates/trees/boolean_rst_generalized_x_root.tree.json](../../../../../tests/candidates/trees/boolean_rst_generalized_x_root.tree.json), [tests/candidates/trees/boolean_rst_generalized_y_root.tree.json](../../../../../tests/candidates/trees/boolean_rst_generalized_y_root.tree.json), [include/crown/planner/search.hpp](../../../../../include/crown/planner/search.hpp), [include/crown/planner/candidates.hpp](../../../../../include/crown/planner/candidates.hpp), [include/crown/planner/selection.hpp](../../../../../include/crown/planner/selection.hpp), [include/crown/runtime/selection.hpp](../../../../../include/crown/runtime/selection.hpp), [docs/planner_continuations.md](../../../../planner_continuations.md), [docs/candidate_alternatives.md](../../../../candidate_alternatives.md), [docs/selection.md](../../../../selection.md), [docs/statistics.md](../../../../statistics.md), [docs/code_review.md](../../../../code_review.md) |

## B0009

[Lines 90–94](../../../../../tests/support/selection_independent_fixture.hpp#L90); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
inline p::CandidateSnapshot candidates(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Obtain a complete owning public candidate snapshot via actual proof and enumeration. |
| inputs / outputs | Calls provider(prove(catalog,query)), finish(value), then value.snapshot(). |
| invariants | Completion is actual provider exhaustion, not an expected count shortcut; original typed proof remains attached to all alternatives. |
| ownership | Snapshot construction allocates/copies handle/event arrays; returned Snapshot copies share immutable SnapshotData, default moves may empty source. No live provider cursor is transplanted. |
| failure | Any proof/provider/finish/snapshot failure aborts fixture; no synthetic result or incomplete acceptance. |
| cost | Full prove+enumerate workload and snapshot admission, not a fixed shared-handle copy alone. |
| Design | [tests/support/selection_independent_fixture.hpp](../../../../../tests/support/selection_independent_fixture.hpp), [tests/unit/selection_public_independent_test.cpp](../../../../../tests/unit/selection_public_independent_test.cpp), [tests/unit/selection_binding_independent_test.cpp](../../../../../tests/unit/selection_binding_independent_test.cpp), [tests/unit/selection_publication_fault_independent_test.cpp](../../../../../tests/unit/selection_publication_fault_independent_test.cpp), [tests/candidates/queries/boolean_rst.cq.json](../../../../../tests/candidates/queries/boolean_rst.cq.json), [tests/candidates/trees/boolean_rst_native_s_root.tree.json](../../../../../tests/candidates/trees/boolean_rst_native_s_root.tree.json), [tests/candidates/trees/boolean_rst_generalized_x_root.tree.json](../../../../../tests/candidates/trees/boolean_rst_generalized_x_root.tree.json), [tests/candidates/trees/boolean_rst_generalized_y_root.tree.json](../../../../../tests/candidates/trees/boolean_rst_generalized_y_root.tree.json), [include/crown/planner/search.hpp](../../../../../include/crown/planner/search.hpp), [include/crown/planner/candidates.hpp](../../../../../include/crown/planner/candidates.hpp), [include/crown/planner/selection.hpp](../../../../../include/crown/planner/selection.hpp), [include/crown/runtime/selection.hpp](../../../../../include/crown/runtime/selection.hpp), [docs/planner_continuations.md](../../../../planner_continuations.md), [docs/candidate_alternatives.md](../../../../candidate_alternatives.md), [docs/selection.md](../../../../selection.md), [docs/statistics.md](../../../../statistics.md), [docs/code_review.md](../../../../code_review.md) |

## B0010

[Lines 95–107](../../../../../tests/support/selection_independent_fixture.hpp#L95); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
inline std::string shape_node(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Render child-order-insensitive geometry for admitted literal trees without reusing the production structural-key helper. |
| inputs / outputs | Recursively encodes node native/generalized kind, optional occurrence, ordered variable scope, and sorted child shape strings with delimiters. |
| invariants | Requires finite valid tree IDs/acyclic structure; it does not validate cycles or impose a recursion cap. Omits source binding/query constants/head/proof/context/display IDs and is not a global candidate key or authority token. |
| ownership | Borrows tree; returns ordinary owning recursively built strings/vectors and sorted child copies. |
| failure | at() rejects out-of-range IDs; recursion/ordinary allocation/sort failures propagate. No validator/repair layer is added. |
| cost | Visits nodes recursively and sorts siblings; repeated subtree/string concatenation/copies can cost total rendered-path bytes beyond node count, with actual ordinary allocations. |
| Design | [tests/support/selection_independent_fixture.hpp](../../../../../tests/support/selection_independent_fixture.hpp), [tests/unit/selection_public_independent_test.cpp](../../../../../tests/unit/selection_public_independent_test.cpp), [tests/unit/selection_binding_independent_test.cpp](../../../../../tests/unit/selection_binding_independent_test.cpp), [tests/unit/selection_publication_fault_independent_test.cpp](../../../../../tests/unit/selection_publication_fault_independent_test.cpp), [tests/candidates/queries/boolean_rst.cq.json](../../../../../tests/candidates/queries/boolean_rst.cq.json), [tests/candidates/trees/boolean_rst_native_s_root.tree.json](../../../../../tests/candidates/trees/boolean_rst_native_s_root.tree.json), [tests/candidates/trees/boolean_rst_generalized_x_root.tree.json](../../../../../tests/candidates/trees/boolean_rst_generalized_x_root.tree.json), [tests/candidates/trees/boolean_rst_generalized_y_root.tree.json](../../../../../tests/candidates/trees/boolean_rst_generalized_y_root.tree.json), [include/crown/planner/search.hpp](../../../../../include/crown/planner/search.hpp), [include/crown/planner/candidates.hpp](../../../../../include/crown/planner/candidates.hpp), [include/crown/planner/selection.hpp](../../../../../include/crown/planner/selection.hpp), [include/crown/runtime/selection.hpp](../../../../../include/crown/runtime/selection.hpp), [docs/planner_continuations.md](../../../../planner_continuations.md), [docs/candidate_alternatives.md](../../../../candidate_alternatives.md), [docs/selection.md](../../../../selection.md), [docs/statistics.md](../../../../statistics.md), [docs/code_review.md](../../../../code_review.md) |

## B0011

[Lines 108–110](../../../../../tests/support/selection_independent_fixture.hpp#L108); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
inline std::string shape(const FreeConnexTree& tree)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Render the literal root geometry or explicit empty-tree label. |
| inputs / outputs | Calls shape_node(tree,*root) if engaged, otherwise returns empty. |
| invariants | Empty label describes this fixture geometry only, not query truth/structural infeasibility or checked minimum height. |
| ownership | Returned std::string owns bytes; tree remains borrowed. |
| failure | Delegated at/recursive/allocation failures propagate; no local handler. |
| cost | Fixed branch plus complete recursive shape rendering when nonempty; string label allocation follows implementation. |
| Design | [tests/support/selection_independent_fixture.hpp](../../../../../tests/support/selection_independent_fixture.hpp), [tests/unit/selection_public_independent_test.cpp](../../../../../tests/unit/selection_public_independent_test.cpp), [tests/unit/selection_binding_independent_test.cpp](../../../../../tests/unit/selection_binding_independent_test.cpp), [tests/unit/selection_publication_fault_independent_test.cpp](../../../../../tests/unit/selection_publication_fault_independent_test.cpp), [tests/candidates/queries/boolean_rst.cq.json](../../../../../tests/candidates/queries/boolean_rst.cq.json), [tests/candidates/trees/boolean_rst_native_s_root.tree.json](../../../../../tests/candidates/trees/boolean_rst_native_s_root.tree.json), [tests/candidates/trees/boolean_rst_generalized_x_root.tree.json](../../../../../tests/candidates/trees/boolean_rst_generalized_x_root.tree.json), [tests/candidates/trees/boolean_rst_generalized_y_root.tree.json](../../../../../tests/candidates/trees/boolean_rst_generalized_y_root.tree.json), [include/crown/planner/search.hpp](../../../../../include/crown/planner/search.hpp), [include/crown/planner/candidates.hpp](../../../../../include/crown/planner/candidates.hpp), [include/crown/planner/selection.hpp](../../../../../include/crown/planner/selection.hpp), [include/crown/runtime/selection.hpp](../../../../../include/crown/runtime/selection.hpp), [docs/planner_continuations.md](../../../../planner_continuations.md), [docs/candidate_alternatives.md](../../../../candidate_alternatives.md), [docs/selection.md](../../../../selection.md), [docs/statistics.md](../../../../statistics.md), [docs/code_review.md](../../../../code_review.md) |

## B0012

[Lines 111–112](../../../../../tests/support/selection_independent_fixture.hpp#L111); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L111-L112:sha256:2f8398b0af6f77c3060b091a0a5a2bbaf5dcf7838ea1bd827e9b3482e765269d
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Explain the adjacent source contract: Aggregate copies deep-copy DTO/maps/rows while typed proof-prefix handles share their real immutable controls. Copied map keys are ordinary independent strings. |
| inputs / outputs | Human-readable source note in; no executable output or checked receipt. |
| invariants | This comment states context or a limitation. It does not itself enforce or prove the described behavior; use the adjacent implementation and its scoped contract. |
| ownership | Source text only; no object or resource lifetime is created. |
| failure | No runtime failure path in this comment; source encoding/comment syntax still belongs to compilation. |
| cost | No runtime operations from the comment. Any work described in the note belongs to the adjacent operation. |
| Design | [tests/support/selection_independent_fixture.hpp](../../../../../tests/support/selection_independent_fixture.hpp), [docs/selection.md](../../../../selection.md), [docs/code_review.md](../../../../code_review.md) |

## B0013

[Lines 113–119](../../../../../tests/support/selection_independent_fixture.hpp#L113); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct BooleanFixture {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Own real public Boolean source/proof-prefix artifacts alongside independent literal labels/data. |
| inputs / outputs | Document owns catalog/query; all/partial/empty are immutable typed CandidateSnapshot handles; label_by_key owns copied structural-key/label strings, by_label owns label keys plus MinimumHeightCandidate handles; initial owns ordinary Relation rows. |
| invariants | No custom special members: aggregate copying deep-copies Document/maps/row payload while snapshot/candidate handle copies share their actual controls; default moves of these typed handles may empty source. Label/key strings and input rows are not generically shared. Expected labels are never proof authority. |
| ownership | All retained source/data/map nodes are ordinary owning values; actual proof/candidate graphs retain admitted binding independently of producer. No live runtime pointer/account/grant is stored. |
| failure | Any nested copy/allocation failure propagates; no fallback binding or partial accepted fixture. |
| cost | Copying can allocate proportional to document/maps/rows/text despite cheap embedded handle copies. Fixture construction also performs real public proof/enumeration/validation. |
| Design | [tests/support/selection_independent_fixture.hpp](../../../../../tests/support/selection_independent_fixture.hpp), [tests/unit/selection_public_independent_test.cpp](../../../../../tests/unit/selection_public_independent_test.cpp), [tests/unit/selection_binding_independent_test.cpp](../../../../../tests/unit/selection_binding_independent_test.cpp), [tests/unit/selection_publication_fault_independent_test.cpp](../../../../../tests/unit/selection_publication_fault_independent_test.cpp), [tests/candidates/queries/boolean_rst.cq.json](../../../../../tests/candidates/queries/boolean_rst.cq.json), [tests/candidates/trees/boolean_rst_native_s_root.tree.json](../../../../../tests/candidates/trees/boolean_rst_native_s_root.tree.json), [tests/candidates/trees/boolean_rst_generalized_x_root.tree.json](../../../../../tests/candidates/trees/boolean_rst_generalized_x_root.tree.json), [tests/candidates/trees/boolean_rst_generalized_y_root.tree.json](../../../../../tests/candidates/trees/boolean_rst_generalized_y_root.tree.json), [include/crown/planner/search.hpp](../../../../../include/crown/planner/search.hpp), [include/crown/planner/candidates.hpp](../../../../../include/crown/planner/candidates.hpp), [include/crown/planner/selection.hpp](../../../../../include/crown/planner/selection.hpp), [include/crown/runtime/selection.hpp](../../../../../include/crown/runtime/selection.hpp), [docs/planner_continuations.md](../../../../planner_continuations.md), [docs/candidate_alternatives.md](../../../../candidate_alternatives.md), [docs/selection.md](../../../../selection.md), [docs/statistics.md](../../../../statistics.md), [docs/code_review.md](../../../../code_review.md) |

## B0014

[Lines 120–154](../../../../../tests/support/selection_independent_fixture.hpp#L120); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
inline BooleanFixture boolean_fixture(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Bind the actual three-candidate Boolean R/S/T family to independently read raw-tree labels. |
| inputs / outputs | Reads string-typed Boolean document, proves height2, snapshots actual empty prefix, advances to exactly one and snapshots partial, finishes to exhausted three; reads/validates each literal tree height2 and maps independent shape to label, then maps actual candidate keys/handles and creates x/y witness rows. |
| invariants | Literal geometry and upper validation alone do not prove optimality: actual VerifiedOptimum supplies it. Each real family member must be valid height2 and match exactly one native_s/generalized_x/generalized_y literal geometry. Empty/partial snapshots retain their earlier completion state. |
| ownership | Result owns moved Document, copied Snapshot handles, ordinary key/label maps, candidate handles and independent string row set. Real search/provider owners can close afterward; no borrowed file/producer pointer escapes. |
| failure | Read/parse/public proof/provider/upper validation/key collision/unexpected member/count/allocation errors throw. No private C05 factory, production score helper or synthetic authority is used. |
| cost | Multiple file reads/parses, actual search/replay/enumeration/snapshot allocations, recursive shapes/map inserts and ordinary string/key/data copies; fixture setup is substantial cold test work. |
| Design | [tests/support/selection_independent_fixture.hpp](../../../../../tests/support/selection_independent_fixture.hpp), [tests/unit/selection_public_independent_test.cpp](../../../../../tests/unit/selection_public_independent_test.cpp), [tests/unit/selection_binding_independent_test.cpp](../../../../../tests/unit/selection_binding_independent_test.cpp), [tests/unit/selection_publication_fault_independent_test.cpp](../../../../../tests/unit/selection_publication_fault_independent_test.cpp), [tests/candidates/queries/boolean_rst.cq.json](../../../../../tests/candidates/queries/boolean_rst.cq.json), [tests/candidates/trees/boolean_rst_native_s_root.tree.json](../../../../../tests/candidates/trees/boolean_rst_native_s_root.tree.json), [tests/candidates/trees/boolean_rst_generalized_x_root.tree.json](../../../../../tests/candidates/trees/boolean_rst_generalized_x_root.tree.json), [tests/candidates/trees/boolean_rst_generalized_y_root.tree.json](../../../../../tests/candidates/trees/boolean_rst_generalized_y_root.tree.json), [include/crown/planner/search.hpp](../../../../../include/crown/planner/search.hpp), [include/crown/planner/candidates.hpp](../../../../../include/crown/planner/candidates.hpp), [include/crown/planner/selection.hpp](../../../../../include/crown/planner/selection.hpp), [include/crown/runtime/selection.hpp](../../../../../include/crown/runtime/selection.hpp), [docs/planner_continuations.md](../../../../planner_continuations.md), [docs/candidate_alternatives.md](../../../../candidate_alternatives.md), [docs/selection.md](../../../../selection.md), [docs/statistics.md](../../../../statistics.md), [docs/code_review.md](../../../../code_review.md) |

## B0015

[Lines 155–157](../../../../../tests/support/selection_independent_fixture.hpp#L155); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
inline PhysicalPlan lower(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Lower a genuine retained candidate using its own original bound source. |
| inputs / outputs | Calls public lower_tree(member.catalog(),member.query(),member.tree(),options). |
| invariants | Borrowed source/tree come from actual MinimumHeightCandidate; lowering still validates them. It does not replace candidate.original_proof or claim a different structural optimum. |
| ownership | Returns owning immutable compiler PhysicalPlan; normal copies share plan control, default moves may empty source. Native runtime initialization later imports into its own query account. |
| failure | Moved/invalid member or lowering/identity/limit/allocation failures propagate. |
| cost | Full compiler lowering/source binding/plan allocation plus fixed member access; no source rows are read yet. |
| Design | [tests/support/selection_independent_fixture.hpp](../../../../../tests/support/selection_independent_fixture.hpp), [tests/unit/selection_public_independent_test.cpp](../../../../../tests/unit/selection_public_independent_test.cpp), [tests/unit/selection_binding_independent_test.cpp](../../../../../tests/unit/selection_binding_independent_test.cpp), [tests/unit/selection_publication_fault_independent_test.cpp](../../../../../tests/unit/selection_publication_fault_independent_test.cpp), [tests/candidates/queries/boolean_rst.cq.json](../../../../../tests/candidates/queries/boolean_rst.cq.json), [tests/candidates/trees/boolean_rst_native_s_root.tree.json](../../../../../tests/candidates/trees/boolean_rst_native_s_root.tree.json), [tests/candidates/trees/boolean_rst_generalized_x_root.tree.json](../../../../../tests/candidates/trees/boolean_rst_generalized_x_root.tree.json), [tests/candidates/trees/boolean_rst_generalized_y_root.tree.json](../../../../../tests/candidates/trees/boolean_rst_generalized_y_root.tree.json), [include/crown/planner/search.hpp](../../../../../include/crown/planner/search.hpp), [include/crown/planner/candidates.hpp](../../../../../include/crown/planner/candidates.hpp), [include/crown/planner/selection.hpp](../../../../../include/crown/planner/selection.hpp), [include/crown/runtime/selection.hpp](../../../../../include/crown/runtime/selection.hpp), [docs/planner_continuations.md](../../../../planner_continuations.md), [docs/candidate_alternatives.md](../../../../candidate_alternatives.md), [docs/selection.md](../../../../selection.md), [docs/statistics.md](../../../../statistics.md), [docs/code_review.md](../../../../code_review.md) |

## B0016

[Lines 158–162](../../../../../tests/support/selection_independent_fixture.hpp#L158); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
inline r::workload::Options counters()
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Request real workload counters with unchanged default sampling/detail ceilings. |
| inputs / outputs | Returns Options with mode=counters and other fields at defaults. |
| invariants | This options DTO does not itself collect roots, admit descriptors or manufacture RuntimeEvidence. |
| ownership | Only inline scalar metadata; no row/account/pointer. |
| failure | Real configure admission is deferred to hot()/caller. |
| cost | Fixed options setup; no runtime scan or array allocation. |
| Design | [tests/support/selection_independent_fixture.hpp](../../../../../tests/support/selection_independent_fixture.hpp), [tests/unit/selection_public_independent_test.cpp](../../../../../tests/unit/selection_public_independent_test.cpp), [tests/unit/selection_binding_independent_test.cpp](../../../../../tests/unit/selection_binding_independent_test.cpp), [tests/unit/selection_publication_fault_independent_test.cpp](../../../../../tests/unit/selection_publication_fault_independent_test.cpp), [tests/candidates/queries/boolean_rst.cq.json](../../../../../tests/candidates/queries/boolean_rst.cq.json), [tests/candidates/trees/boolean_rst_native_s_root.tree.json](../../../../../tests/candidates/trees/boolean_rst_native_s_root.tree.json), [tests/candidates/trees/boolean_rst_generalized_x_root.tree.json](../../../../../tests/candidates/trees/boolean_rst_generalized_x_root.tree.json), [tests/candidates/trees/boolean_rst_generalized_y_root.tree.json](../../../../../tests/candidates/trees/boolean_rst_generalized_y_root.tree.json), [include/crown/planner/search.hpp](../../../../../include/crown/planner/search.hpp), [include/crown/planner/candidates.hpp](../../../../../include/crown/planner/candidates.hpp), [include/crown/planner/selection.hpp](../../../../../include/crown/planner/selection.hpp), [include/crown/runtime/selection.hpp](../../../../../include/crown/runtime/selection.hpp), [docs/planner_continuations.md](../../../../planner_continuations.md), [docs/candidate_alternatives.md](../../../../candidate_alternatives.md), [docs/selection.md](../../../../selection.md), [docs/statistics.md](../../../../statistics.md), [docs/code_review.md](../../../../code_review.md) |

## B0017

[Lines 163–167](../../../../../tests/support/selection_independent_fixture.hpp#L163); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
inline void noop(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Generate and explicitly assert actual duplicate-insert no-op inputs. |
| inputs / outputs | Repeats count owner.apply(sequence+1,table,insert,row), requiring physical_changed=false each time. |
| invariants | Requires writer-ready owner and existing source row. Every successful call still consumes a committed sequence and contributes a physical input; it is not fabricated zero-cost statistics. |
| ownership | Input Row is borrowed then copied into update as needed; temporary epochs own their release. Caller retains runtime. |
| failure | Actual engine/input/account/sequence errors or unexpected change abort after prior successful events; no aggregate fixture rollback. |
| cost | count real updates with row copies/native gates/observation root lifecycle; no-op data change does not imply zero CPU/allocation/work. |
| Design | [tests/support/selection_independent_fixture.hpp](../../../../../tests/support/selection_independent_fixture.hpp), [tests/unit/selection_public_independent_test.cpp](../../../../../tests/unit/selection_public_independent_test.cpp), [tests/unit/selection_binding_independent_test.cpp](../../../../../tests/unit/selection_binding_independent_test.cpp), [tests/unit/selection_publication_fault_independent_test.cpp](../../../../../tests/unit/selection_publication_fault_independent_test.cpp), [tests/candidates/queries/boolean_rst.cq.json](../../../../../tests/candidates/queries/boolean_rst.cq.json), [tests/candidates/trees/boolean_rst_native_s_root.tree.json](../../../../../tests/candidates/trees/boolean_rst_native_s_root.tree.json), [tests/candidates/trees/boolean_rst_generalized_x_root.tree.json](../../../../../tests/candidates/trees/boolean_rst_generalized_x_root.tree.json), [tests/candidates/trees/boolean_rst_generalized_y_root.tree.json](../../../../../tests/candidates/trees/boolean_rst_generalized_y_root.tree.json), [include/crown/planner/search.hpp](../../../../../include/crown/planner/search.hpp), [include/crown/planner/candidates.hpp](../../../../../include/crown/planner/candidates.hpp), [include/crown/planner/selection.hpp](../../../../../include/crown/planner/selection.hpp), [include/crown/runtime/selection.hpp](../../../../../include/crown/runtime/selection.hpp), [docs/planner_continuations.md](../../../../planner_continuations.md), [docs/candidate_alternatives.md](../../../../candidate_alternatives.md), [docs/selection.md](../../../../selection.md), [docs/statistics.md](../../../../statistics.md), [docs/code_review.md](../../../../code_review.md) |

## B0018

[Lines 168–173](../../../../../tests/support/selection_independent_fixture.hpp#L168); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
inline void hot(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Create independent literal 90/5/5 workload weights without changing initialized Boolean data. |
| inputs / outputs | Configures default counters then runs noop for R,S,T using first initial rows, with hot R or T. |
| invariants | Explicit noop assertions verify source membership unchanged. Actual 100 committed inputs establish denominator100 and chosen native-depth weights; ordinary labels alone cannot create them. |
| ownership | Borrowed fixture/runtime; actual collector arrays/account and event owners are owned by runtime. |
| failure | Configuration/noop failures propagate; already committed inputs remain and no automatic reset/retry occurs. |
| cost | Configuration plus100 actual input operations; counters have dense root lifecycle cost even when source set does not change. |
| Design | [tests/support/selection_independent_fixture.hpp](../../../../../tests/support/selection_independent_fixture.hpp), [tests/unit/selection_public_independent_test.cpp](../../../../../tests/unit/selection_public_independent_test.cpp), [tests/unit/selection_binding_independent_test.cpp](../../../../../tests/unit/selection_binding_independent_test.cpp), [tests/unit/selection_publication_fault_independent_test.cpp](../../../../../tests/unit/selection_publication_fault_independent_test.cpp), [tests/candidates/queries/boolean_rst.cq.json](../../../../../tests/candidates/queries/boolean_rst.cq.json), [tests/candidates/trees/boolean_rst_native_s_root.tree.json](../../../../../tests/candidates/trees/boolean_rst_native_s_root.tree.json), [tests/candidates/trees/boolean_rst_generalized_x_root.tree.json](../../../../../tests/candidates/trees/boolean_rst_generalized_x_root.tree.json), [tests/candidates/trees/boolean_rst_generalized_y_root.tree.json](../../../../../tests/candidates/trees/boolean_rst_generalized_y_root.tree.json), [include/crown/planner/search.hpp](../../../../../include/crown/planner/search.hpp), [include/crown/planner/candidates.hpp](../../../../../include/crown/planner/candidates.hpp), [include/crown/planner/selection.hpp](../../../../../include/crown/planner/selection.hpp), [include/crown/runtime/selection.hpp](../../../../../include/crown/runtime/selection.hpp), [docs/planner_continuations.md](../../../../planner_continuations.md), [docs/candidate_alternatives.md](../../../../candidate_alternatives.md), [docs/selection.md](../../../../selection.md), [docs/statistics.md](../../../../statistics.md), [docs/code_review.md](../../../../code_review.md) |

## B0019

[Lines 174–179](../../../../../tests/support/selection_independent_fixture.hpp#L174); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
inline Relation answers(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Independently export committed current answers to ordinary set semantics. |
| inputs / outputs | Consumes a real result cursor, deep-exports each native tuple and inserts into Relation. |
| invariants | Stable readable owner required; terminal cursor releases its lease. This is a result-data oracle, not a structural proof/freshness authority. |
| ownership | Owns independent ordinary rows/scalar bytes/set nodes; cursor borrows native owner/pins during enumeration only. |
| failure | Native work/reader/account/export/ordinary allocation failures propagate; local cursor/Relation release through RAII. |
| cost | Actual full result enumeration plus deep payload export and ordered set insertion/comparison; no generic allocation-free answer check. |
| Design | [tests/support/selection_independent_fixture.hpp](../../../../../tests/support/selection_independent_fixture.hpp), [tests/unit/selection_public_independent_test.cpp](../../../../../tests/unit/selection_public_independent_test.cpp), [tests/unit/selection_binding_independent_test.cpp](../../../../../tests/unit/selection_binding_independent_test.cpp), [tests/unit/selection_publication_fault_independent_test.cpp](../../../../../tests/unit/selection_publication_fault_independent_test.cpp), [tests/candidates/queries/boolean_rst.cq.json](../../../../../tests/candidates/queries/boolean_rst.cq.json), [tests/candidates/trees/boolean_rst_native_s_root.tree.json](../../../../../tests/candidates/trees/boolean_rst_native_s_root.tree.json), [tests/candidates/trees/boolean_rst_generalized_x_root.tree.json](../../../../../tests/candidates/trees/boolean_rst_generalized_x_root.tree.json), [tests/candidates/trees/boolean_rst_generalized_y_root.tree.json](../../../../../tests/candidates/trees/boolean_rst_generalized_y_root.tree.json), [include/crown/planner/search.hpp](../../../../../include/crown/planner/search.hpp), [include/crown/planner/candidates.hpp](../../../../../include/crown/planner/candidates.hpp), [include/crown/planner/selection.hpp](../../../../../include/crown/planner/selection.hpp), [include/crown/runtime/selection.hpp](../../../../../include/crown/runtime/selection.hpp), [docs/planner_continuations.md](../../../../planner_continuations.md), [docs/candidate_alternatives.md](../../../../candidate_alternatives.md), [docs/selection.md](../../../../selection.md), [docs/statistics.md](../../../../statistics.md), [docs/code_review.md](../../../../code_review.md) |

## B0020

[Lines 180–186](../../../../../tests/support/selection_independent_fixture.hpp#L180); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
capture::RuntimeEvidence capture_checked(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Require genuine runtime ranking capture from a typed supported owner. |
| inputs / outputs | Calls capture::capture(snapshot,owner,options), requires complete stop/evidence and returns owning RuntimeEvidence. |
| invariants | Owner/source/pending/typed snapshot binding is performed by actual production public capture; no fixture private factory or editable numeric proof substitute. |
| ownership | Evidence copies share real immutable Data while captured state/workload arrays/keys remain owning/funded. Owner itself is only borrowed synchronously. |
| failure | Incomplete/failing capture throws fixture check; actual allocation/work/owner errors have their real public stop boundary. |
| cost | Full bounded actual-owner state/census processing and allocations, then fixed handle copy; not a free revalidation token. |
| Design | [tests/support/selection_independent_fixture.hpp](../../../../../tests/support/selection_independent_fixture.hpp), [tests/unit/selection_public_independent_test.cpp](../../../../../tests/unit/selection_public_independent_test.cpp), [tests/unit/selection_binding_independent_test.cpp](../../../../../tests/unit/selection_binding_independent_test.cpp), [tests/unit/selection_publication_fault_independent_test.cpp](../../../../../tests/unit/selection_publication_fault_independent_test.cpp), [tests/candidates/queries/boolean_rst.cq.json](../../../../../tests/candidates/queries/boolean_rst.cq.json), [tests/candidates/trees/boolean_rst_native_s_root.tree.json](../../../../../tests/candidates/trees/boolean_rst_native_s_root.tree.json), [tests/candidates/trees/boolean_rst_generalized_x_root.tree.json](../../../../../tests/candidates/trees/boolean_rst_generalized_x_root.tree.json), [tests/candidates/trees/boolean_rst_generalized_y_root.tree.json](../../../../../tests/candidates/trees/boolean_rst_generalized_y_root.tree.json), [include/crown/planner/search.hpp](../../../../../include/crown/planner/search.hpp), [include/crown/planner/candidates.hpp](../../../../../include/crown/planner/candidates.hpp), [include/crown/planner/selection.hpp](../../../../../include/crown/planner/selection.hpp), [include/crown/runtime/selection.hpp](../../../../../include/crown/runtime/selection.hpp), [docs/planner_continuations.md](../../../../planner_continuations.md), [docs/candidate_alternatives.md](../../../../candidate_alternatives.md), [docs/selection.md](../../../../selection.md), [docs/statistics.md](../../../../statistics.md), [docs/code_review.md](../../../../code_review.md) |

## B0021

[Lines 187–187](../../../../../tests/support/selection_independent_fixture.hpp#L187); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L187-L187:sha256:6ae035d8af09e548c47fb3a4b688f6598a8272eb98c5050c8994b994e3067b72
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Explain the adjacent source contract: Returned reference borrows the Attempt. Copy the typed handle to retain it. |
| inputs / outputs | Human-readable source note in; no executable output or checked receipt. |
| invariants | This comment states context or a limitation. It does not itself enforce or prove the described behavior; use the adjacent implementation and its scoped contract. |
| ownership | Source text only; no object or resource lifetime is created. |
| failure | No runtime failure path in this comment; source encoding/comment syntax still belongs to compilation. |
| cost | No runtime operations from the comment. Any work described in the note belongs to the adjacent operation. |
| Design | [tests/support/selection_independent_fixture.hpp](../../../../../tests/support/selection_independent_fixture.hpp), [docs/selection.md](../../../../selection.md), [docs/code_review.md](../../../../code_review.md) |

## B0022

[Lines 188–191](../../../../../tests/support/selection_independent_fixture.hpp#L188); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
inline const s::Selection& complete(const s::Attempt& result)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Borrow a complete published Selection from an existing Attempt. |
| inputs / outputs | Requires complete stop and engaged optional, then returns const reference to its value. |
| invariants | Unlike value-taking c05_test::complete, this does not return an owning handle. A temporary Attempt can be used only while its lifetime lasts; callers retaining a result by value explicitly copy the actual shared typed handle. |
| ownership | Reference borrows Attempt/optional payload and must not outlive it. Actual Selection/CurrentSelection copy-like moves retain source validity, but that does not extend a destroyed Attempt by reference. |
| failure | Missing/noncomplete result throws runtime_error via check; no synthetic choice or fallback. |
| cost | Fixed check/reference return; no key/array clone on success. Copying the returned typed handle is cheap; unrelated image export is not. |
| Design | [tests/support/selection_independent_fixture.hpp](../../../../../tests/support/selection_independent_fixture.hpp), [tests/unit/selection_public_independent_test.cpp](../../../../../tests/unit/selection_public_independent_test.cpp), [tests/unit/selection_binding_independent_test.cpp](../../../../../tests/unit/selection_binding_independent_test.cpp), [tests/unit/selection_publication_fault_independent_test.cpp](../../../../../tests/unit/selection_publication_fault_independent_test.cpp), [tests/candidates/queries/boolean_rst.cq.json](../../../../../tests/candidates/queries/boolean_rst.cq.json), [tests/candidates/trees/boolean_rst_native_s_root.tree.json](../../../../../tests/candidates/trees/boolean_rst_native_s_root.tree.json), [tests/candidates/trees/boolean_rst_generalized_x_root.tree.json](../../../../../tests/candidates/trees/boolean_rst_generalized_x_root.tree.json), [tests/candidates/trees/boolean_rst_generalized_y_root.tree.json](../../../../../tests/candidates/trees/boolean_rst_generalized_y_root.tree.json), [include/crown/planner/search.hpp](../../../../../include/crown/planner/search.hpp), [include/crown/planner/candidates.hpp](../../../../../include/crown/planner/candidates.hpp), [include/crown/planner/selection.hpp](../../../../../include/crown/planner/selection.hpp), [include/crown/runtime/selection.hpp](../../../../../include/crown/runtime/selection.hpp), [docs/planner_continuations.md](../../../../planner_continuations.md), [docs/candidate_alternatives.md](../../../../candidate_alternatives.md), [docs/selection.md](../../../../selection.md), [docs/statistics.md](../../../../statistics.md), [docs/code_review.md](../../../../code_review.md) |

## B0023

[Lines 192–192](../../../../../tests/support/selection_independent_fixture.hpp#L192); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L192-L192:sha256:bc079ba589081551c963a47859370b23a8ef8e4215cf52fef61107c1c0348ad7
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Explain the adjacent source contract: Returned reference borrows the Attempt; it does not extend temporary lifetime. |
| inputs / outputs | Human-readable source note in; no executable output or checked receipt. |
| invariants | This comment states context or a limitation. It does not itself enforce or prove the described behavior; use the adjacent implementation and its scoped contract. |
| ownership | Source text only; no object or resource lifetime is created. |
| failure | No runtime failure path in this comment; source encoding/comment syntax still belongs to compilation. |
| cost | No runtime operations from the comment. Any work described in the note belongs to the adjacent operation. |
| Design | [tests/support/selection_independent_fixture.hpp](../../../../../tests/support/selection_independent_fixture.hpp), [docs/selection.md](../../../../selection.md), [docs/code_review.md](../../../../code_review.md) |

## B0024

[Lines 193–196](../../../../../tests/support/selection_independent_fixture.hpp#L193); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
inline const current::CurrentSelection& complete(const current::Attempt& result)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Borrow a complete published CurrentSelection from an existing Attempt. |
| inputs / outputs | Requires complete stop and engaged optional, then returns const reference to its value. |
| invariants | Unlike value-taking c05_test::complete, this does not return an owning handle. A temporary Attempt can be used only while its lifetime lasts; callers retaining a result by value explicitly copy the actual shared typed handle. |
| ownership | Reference borrows Attempt/optional payload and must not outlive it. Actual Selection/CurrentSelection copy-like moves retain source validity, but that does not extend a destroyed Attempt by reference. |
| failure | Missing/noncomplete result throws runtime_error via check; no synthetic choice or fallback. |
| cost | Fixed check/reference return; no key/array clone on success. Copying the returned typed handle is cheap; unrelated image export is not. |
| Design | [tests/support/selection_independent_fixture.hpp](../../../../../tests/support/selection_independent_fixture.hpp), [tests/unit/selection_public_independent_test.cpp](../../../../../tests/unit/selection_public_independent_test.cpp), [tests/unit/selection_binding_independent_test.cpp](../../../../../tests/unit/selection_binding_independent_test.cpp), [tests/unit/selection_publication_fault_independent_test.cpp](../../../../../tests/unit/selection_publication_fault_independent_test.cpp), [tests/candidates/queries/boolean_rst.cq.json](../../../../../tests/candidates/queries/boolean_rst.cq.json), [tests/candidates/trees/boolean_rst_native_s_root.tree.json](../../../../../tests/candidates/trees/boolean_rst_native_s_root.tree.json), [tests/candidates/trees/boolean_rst_generalized_x_root.tree.json](../../../../../tests/candidates/trees/boolean_rst_generalized_x_root.tree.json), [tests/candidates/trees/boolean_rst_generalized_y_root.tree.json](../../../../../tests/candidates/trees/boolean_rst_generalized_y_root.tree.json), [include/crown/planner/search.hpp](../../../../../include/crown/planner/search.hpp), [include/crown/planner/candidates.hpp](../../../../../include/crown/planner/candidates.hpp), [include/crown/planner/selection.hpp](../../../../../include/crown/planner/selection.hpp), [include/crown/runtime/selection.hpp](../../../../../include/crown/runtime/selection.hpp), [docs/planner_continuations.md](../../../../planner_continuations.md), [docs/candidate_alternatives.md](../../../../candidate_alternatives.md), [docs/selection.md](../../../../selection.md), [docs/statistics.md](../../../../statistics.md), [docs/code_review.md](../../../../code_review.md) |

## B0025

[Lines 197–199](../../../../../tests/support/selection_independent_fixture.hpp#L197); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
inline bool has(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Test one named ranking-reason bit without changing evidence usability. |
| inputs / outputs | Returns (value & reason(flag))!=0. |
| invariants | Bitsets are descriptive diagnostics; this predicate does not make incomplete/missing owner facts valid. |
| ownership | Inline reason values only. |
| failure | No throwing operation or handler. |
| cost | Fixed bit mask/test, no allocation. |
| Design | [tests/support/selection_independent_fixture.hpp](../../../../../tests/support/selection_independent_fixture.hpp), [tests/unit/selection_public_independent_test.cpp](../../../../../tests/unit/selection_public_independent_test.cpp), [tests/unit/selection_binding_independent_test.cpp](../../../../../tests/unit/selection_binding_independent_test.cpp), [tests/unit/selection_publication_fault_independent_test.cpp](../../../../../tests/unit/selection_publication_fault_independent_test.cpp), [tests/candidates/queries/boolean_rst.cq.json](../../../../../tests/candidates/queries/boolean_rst.cq.json), [tests/candidates/trees/boolean_rst_native_s_root.tree.json](../../../../../tests/candidates/trees/boolean_rst_native_s_root.tree.json), [tests/candidates/trees/boolean_rst_generalized_x_root.tree.json](../../../../../tests/candidates/trees/boolean_rst_generalized_x_root.tree.json), [tests/candidates/trees/boolean_rst_generalized_y_root.tree.json](../../../../../tests/candidates/trees/boolean_rst_generalized_y_root.tree.json), [include/crown/planner/search.hpp](../../../../../include/crown/planner/search.hpp), [include/crown/planner/candidates.hpp](../../../../../include/crown/planner/candidates.hpp), [include/crown/planner/selection.hpp](../../../../../include/crown/planner/selection.hpp), [include/crown/runtime/selection.hpp](../../../../../include/crown/runtime/selection.hpp), [docs/planner_continuations.md](../../../../planner_continuations.md), [docs/candidate_alternatives.md](../../../../candidate_alternatives.md), [docs/selection.md](../../../../selection.md), [docs/statistics.md](../../../../statistics.md), [docs/code_review.md](../../../../code_review.md) |

## B0026

[Lines 200–204](../../../../../tests/support/selection_independent_fixture.hpp#L200); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
inline s::Request height()
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Choose height-only policy with normal request defaults. |
| inputs / outputs | Default Request then policy=height_only. |
| invariants | Editable request settings establish no proof/evidence/actual owner capability and execute no policy until select/rank. |
| ownership | Returned Request owns ordinary fixed/default limit metadata; no borrowed row/source graph. |
| failure | No local admission/catch; actual API validates limits and policy. |
| cost | Fixed initialization/enum changes, no search/capture/lowering. |
| Design | [tests/support/selection_independent_fixture.hpp](../../../../../tests/support/selection_independent_fixture.hpp), [tests/unit/selection_public_independent_test.cpp](../../../../../tests/unit/selection_public_independent_test.cpp), [tests/unit/selection_binding_independent_test.cpp](../../../../../tests/unit/selection_binding_independent_test.cpp), [tests/unit/selection_publication_fault_independent_test.cpp](../../../../../tests/unit/selection_publication_fault_independent_test.cpp), [tests/candidates/queries/boolean_rst.cq.json](../../../../../tests/candidates/queries/boolean_rst.cq.json), [tests/candidates/trees/boolean_rst_native_s_root.tree.json](../../../../../tests/candidates/trees/boolean_rst_native_s_root.tree.json), [tests/candidates/trees/boolean_rst_generalized_x_root.tree.json](../../../../../tests/candidates/trees/boolean_rst_generalized_x_root.tree.json), [tests/candidates/trees/boolean_rst_generalized_y_root.tree.json](../../../../../tests/candidates/trees/boolean_rst_generalized_y_root.tree.json), [include/crown/planner/search.hpp](../../../../../include/crown/planner/search.hpp), [include/crown/planner/candidates.hpp](../../../../../include/crown/planner/candidates.hpp), [include/crown/planner/selection.hpp](../../../../../include/crown/planner/selection.hpp), [include/crown/runtime/selection.hpp](../../../../../include/crown/runtime/selection.hpp), [docs/planner_continuations.md](../../../../planner_continuations.md), [docs/candidate_alternatives.md](../../../../candidate_alternatives.md), [docs/selection.md](../../../../selection.md), [docs/statistics.md](../../../../statistics.md), [docs/code_review.md](../../../../code_review.md) |

## B0027

[Lines 205–209](../../../../../tests/support/selection_independent_fixture.hpp#L205); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
inline s::Request depth()
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Require actual evidence for the default committed-input native-depth policy. |
| inputs / outputs | Default Request then fallback=require_evidence; current Request default policy is committed_input_native_depth. |
| invariants | Editable request settings establish no proof/evidence/actual owner capability and execute no policy until select/rank. |
| ownership | Returned Request owns ordinary fixed/default limit metadata; no borrowed row/source graph. |
| failure | No local admission/catch; actual API validates limits and policy. |
| cost | Fixed initialization/enum changes, no search/capture/lowering. |
| Design | [tests/support/selection_independent_fixture.hpp](../../../../../tests/support/selection_independent_fixture.hpp), [tests/unit/selection_public_independent_test.cpp](../../../../../tests/unit/selection_public_independent_test.cpp), [tests/unit/selection_binding_independent_test.cpp](../../../../../tests/unit/selection_binding_independent_test.cpp), [tests/unit/selection_publication_fault_independent_test.cpp](../../../../../tests/unit/selection_publication_fault_independent_test.cpp), [tests/candidates/queries/boolean_rst.cq.json](../../../../../tests/candidates/queries/boolean_rst.cq.json), [tests/candidates/trees/boolean_rst_native_s_root.tree.json](../../../../../tests/candidates/trees/boolean_rst_native_s_root.tree.json), [tests/candidates/trees/boolean_rst_generalized_x_root.tree.json](../../../../../tests/candidates/trees/boolean_rst_generalized_x_root.tree.json), [tests/candidates/trees/boolean_rst_generalized_y_root.tree.json](../../../../../tests/candidates/trees/boolean_rst_generalized_y_root.tree.json), [include/crown/planner/search.hpp](../../../../../include/crown/planner/search.hpp), [include/crown/planner/candidates.hpp](../../../../../include/crown/planner/candidates.hpp), [include/crown/planner/selection.hpp](../../../../../include/crown/planner/selection.hpp), [include/crown/runtime/selection.hpp](../../../../../include/crown/runtime/selection.hpp), [docs/planner_continuations.md](../../../../planner_continuations.md), [docs/candidate_alternatives.md](../../../../candidate_alternatives.md), [docs/selection.md](../../../../selection.md), [docs/statistics.md](../../../../statistics.md), [docs/code_review.md](../../../../code_review.md) |

## B0028

[Lines 210–214](../../../../../tests/support/selection_independent_fixture.hpp#L210); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
inline s::Request slots()
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Require actual evidence for candidate-local tuple/index slot proxy. |
| inputs / outputs | Starts depth() then policy=tuple_index_slots. |
| invariants | Editable request settings establish no proof/evidence/actual owner capability and execute no policy until select/rank. |
| ownership | Returned Request owns ordinary fixed/default limit metadata; no borrowed row/source graph. |
| failure | No local admission/catch; actual API validates limits and policy. |
| cost | Fixed initialization/enum changes, no search/capture/lowering. |
| Design | [tests/support/selection_independent_fixture.hpp](../../../../../tests/support/selection_independent_fixture.hpp), [tests/unit/selection_public_independent_test.cpp](../../../../../tests/unit/selection_public_independent_test.cpp), [tests/unit/selection_binding_independent_test.cpp](../../../../../tests/unit/selection_binding_independent_test.cpp), [tests/unit/selection_publication_fault_independent_test.cpp](../../../../../tests/unit/selection_publication_fault_independent_test.cpp), [tests/candidates/queries/boolean_rst.cq.json](../../../../../tests/candidates/queries/boolean_rst.cq.json), [tests/candidates/trees/boolean_rst_native_s_root.tree.json](../../../../../tests/candidates/trees/boolean_rst_native_s_root.tree.json), [tests/candidates/trees/boolean_rst_generalized_x_root.tree.json](../../../../../tests/candidates/trees/boolean_rst_generalized_x_root.tree.json), [tests/candidates/trees/boolean_rst_generalized_y_root.tree.json](../../../../../tests/candidates/trees/boolean_rst_generalized_y_root.tree.json), [include/crown/planner/search.hpp](../../../../../include/crown/planner/search.hpp), [include/crown/planner/candidates.hpp](../../../../../include/crown/planner/candidates.hpp), [include/crown/planner/selection.hpp](../../../../../include/crown/planner/selection.hpp), [include/crown/runtime/selection.hpp](../../../../../include/crown/runtime/selection.hpp), [docs/planner_continuations.md](../../../../planner_continuations.md), [docs/candidate_alternatives.md](../../../../candidate_alternatives.md), [docs/selection.md](../../../../selection.md), [docs/statistics.md](../../../../statistics.md), [docs/code_review.md](../../../../code_review.md) |

## B0029

[Lines 215–217](../../../../../tests/support/selection_independent_fixture.hpp#L215); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
inline std::string label(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Resolve a selected genuine candidate to its independently established fixture geometry label. |
| inputs / outputs | Looks up selected().structural_key in fixture.label_by_key and returns the stored label by value. |
| invariants | Mapping is bound to this specific source/family/context; structural-key bytes alone are not global identity or proof authority. |
| ownership | Result is an ordinary independent label string copy; source map/key and Selection are borrowed. |
| failure | Missing key throws out_of_range; copying label can allocate. No fallback unknown label. |
| cost | Ordered map lookup including compared key bytes plus label copy; no production score computation. |
| Design | [tests/support/selection_independent_fixture.hpp](../../../../../tests/support/selection_independent_fixture.hpp), [tests/unit/selection_public_independent_test.cpp](../../../../../tests/unit/selection_public_independent_test.cpp), [tests/unit/selection_binding_independent_test.cpp](../../../../../tests/unit/selection_binding_independent_test.cpp), [tests/unit/selection_publication_fault_independent_test.cpp](../../../../../tests/unit/selection_publication_fault_independent_test.cpp), [tests/candidates/queries/boolean_rst.cq.json](../../../../../tests/candidates/queries/boolean_rst.cq.json), [tests/candidates/trees/boolean_rst_native_s_root.tree.json](../../../../../tests/candidates/trees/boolean_rst_native_s_root.tree.json), [tests/candidates/trees/boolean_rst_generalized_x_root.tree.json](../../../../../tests/candidates/trees/boolean_rst_generalized_x_root.tree.json), [tests/candidates/trees/boolean_rst_generalized_y_root.tree.json](../../../../../tests/candidates/trees/boolean_rst_generalized_y_root.tree.json), [include/crown/planner/search.hpp](../../../../../include/crown/planner/search.hpp), [include/crown/planner/candidates.hpp](../../../../../include/crown/planner/candidates.hpp), [include/crown/planner/selection.hpp](../../../../../include/crown/planner/selection.hpp), [include/crown/runtime/selection.hpp](../../../../../include/crown/runtime/selection.hpp), [docs/planner_continuations.md](../../../../planner_continuations.md), [docs/candidate_alternatives.md](../../../../candidate_alternatives.md), [docs/selection.md](../../../../selection.md), [docs/statistics.md](../../../../statistics.md), [docs/code_review.md](../../../../code_review.md) |

## B0030

[Lines 218–223](../../../../../tests/support/selection_independent_fixture.hpp#L218); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
inline const rank::Result& assessment(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Borrow the first retained assessment with the exact semantic purpose. |
| inputs / outputs | Uses find_if over selection.assessments for purpose, requires found, returns its Result reference. |
| invariants | Purpose distinguishes primary and constraint evaluations; it does not rerun or validate arbitrary evidence/scoring. |
| ownership | Reference borrows immutable Selection graph; keep its owner alive. |
| failure | Missing purpose throws fixture check, no substitute assessment. |
| cost | Linear retained assessments, fixed enum comparisons; no successful allocation or graph copy. |
| Design | [tests/support/selection_independent_fixture.hpp](../../../../../tests/support/selection_independent_fixture.hpp), [tests/unit/selection_public_independent_test.cpp](../../../../../tests/unit/selection_public_independent_test.cpp), [tests/unit/selection_binding_independent_test.cpp](../../../../../tests/unit/selection_binding_independent_test.cpp), [tests/unit/selection_publication_fault_independent_test.cpp](../../../../../tests/unit/selection_publication_fault_independent_test.cpp), [tests/candidates/queries/boolean_rst.cq.json](../../../../../tests/candidates/queries/boolean_rst.cq.json), [tests/candidates/trees/boolean_rst_native_s_root.tree.json](../../../../../tests/candidates/trees/boolean_rst_native_s_root.tree.json), [tests/candidates/trees/boolean_rst_generalized_x_root.tree.json](../../../../../tests/candidates/trees/boolean_rst_generalized_x_root.tree.json), [tests/candidates/trees/boolean_rst_generalized_y_root.tree.json](../../../../../tests/candidates/trees/boolean_rst_generalized_y_root.tree.json), [include/crown/planner/search.hpp](../../../../../include/crown/planner/search.hpp), [include/crown/planner/candidates.hpp](../../../../../include/crown/planner/candidates.hpp), [include/crown/planner/selection.hpp](../../../../../include/crown/planner/selection.hpp), [include/crown/runtime/selection.hpp](../../../../../include/crown/runtime/selection.hpp), [docs/planner_continuations.md](../../../../planner_continuations.md), [docs/candidate_alternatives.md](../../../../candidate_alternatives.md), [docs/selection.md](../../../../selection.md), [docs/statistics.md](../../../../statistics.md), [docs/code_review.md](../../../../code_review.md) |

## B0031

[Lines 224–233](../../../../../tests/support/selection_independent_fixture.hpp#L224); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
inline void literal_depth(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Check independent literal weighted native-depth scores for actual hot R/T census. |
| inputs / outputs | Builds ordinary expected label map, requires three scores/effective depth policy, each height2, denominator100 and labeled numerators native_s195/generalized_x105/generalized_y190 (x/y swapped for hot T). |
| invariants | Numbers use native path depth, not arbitrary tree-node depth, measured time or a new minimum-height proof. Expected scores are literal fixture values independent of production score helper. |
| ownership | Expected map and caller_text key copies own ordinary memory; result and fixture labels are borrowed. |
| failure | Map misses, allocation or assertion errors propagate after actual selection/capture. |
| cost | Map/string allocations plus linear scores and key-byte comparisons; no new runtime population scan or production reranking. |
| Design | [tests/support/selection_independent_fixture.hpp](../../../../../tests/support/selection_independent_fixture.hpp), [tests/unit/selection_public_independent_test.cpp](../../../../../tests/unit/selection_public_independent_test.cpp), [tests/unit/selection_binding_independent_test.cpp](../../../../../tests/unit/selection_binding_independent_test.cpp), [tests/unit/selection_publication_fault_independent_test.cpp](../../../../../tests/unit/selection_publication_fault_independent_test.cpp), [tests/candidates/queries/boolean_rst.cq.json](../../../../../tests/candidates/queries/boolean_rst.cq.json), [tests/candidates/trees/boolean_rst_native_s_root.tree.json](../../../../../tests/candidates/trees/boolean_rst_native_s_root.tree.json), [tests/candidates/trees/boolean_rst_generalized_x_root.tree.json](../../../../../tests/candidates/trees/boolean_rst_generalized_x_root.tree.json), [tests/candidates/trees/boolean_rst_generalized_y_root.tree.json](../../../../../tests/candidates/trees/boolean_rst_generalized_y_root.tree.json), [include/crown/planner/search.hpp](../../../../../include/crown/planner/search.hpp), [include/crown/planner/candidates.hpp](../../../../../include/crown/planner/candidates.hpp), [include/crown/planner/selection.hpp](../../../../../include/crown/planner/selection.hpp), [include/crown/runtime/selection.hpp](../../../../../include/crown/runtime/selection.hpp), [docs/planner_continuations.md](../../../../planner_continuations.md), [docs/candidate_alternatives.md](../../../../candidate_alternatives.md), [docs/selection.md](../../../../selection.md), [docs/statistics.md](../../../../statistics.md), [docs/code_review.md](../../../../code_review.md) |

## B0032

[Lines 234–240](../../../../../tests/support/selection_independent_fixture.hpp#L234); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
inline void literal_slots(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Check independent literal candidate-local slot proxies and retained modeled plans. |
| inputs / outputs | Requires three scores/effective slot policy; native_s slots24, generalized labels slots32, every score has modeled_plan. |
| invariants | Proxy is logical tuple/index slots, not allocator requested bytes, actual allocation count, latency or changed proof authority. |
| ownership | Borrows result/fixture maps; caller_text materializes independent ordinary key copies for label lookup. |
| failure | Missing key/plan or mismatched score fails check; ordinary key-copy allocation errors propagate. |
| cost | Linear scores with ordered map key-byte comparisons/copies; no new native capture or lower here. |
| Design | [tests/support/selection_independent_fixture.hpp](../../../../../tests/support/selection_independent_fixture.hpp), [tests/unit/selection_public_independent_test.cpp](../../../../../tests/unit/selection_public_independent_test.cpp), [tests/unit/selection_binding_independent_test.cpp](../../../../../tests/unit/selection_binding_independent_test.cpp), [tests/unit/selection_publication_fault_independent_test.cpp](../../../../../tests/unit/selection_publication_fault_independent_test.cpp), [tests/candidates/queries/boolean_rst.cq.json](../../../../../tests/candidates/queries/boolean_rst.cq.json), [tests/candidates/trees/boolean_rst_native_s_root.tree.json](../../../../../tests/candidates/trees/boolean_rst_native_s_root.tree.json), [tests/candidates/trees/boolean_rst_generalized_x_root.tree.json](../../../../../tests/candidates/trees/boolean_rst_generalized_x_root.tree.json), [tests/candidates/trees/boolean_rst_generalized_y_root.tree.json](../../../../../tests/candidates/trees/boolean_rst_generalized_y_root.tree.json), [include/crown/planner/search.hpp](../../../../../include/crown/planner/search.hpp), [include/crown/planner/candidates.hpp](../../../../../include/crown/planner/candidates.hpp), [include/crown/planner/selection.hpp](../../../../../include/crown/planner/selection.hpp), [include/crown/runtime/selection.hpp](../../../../../include/crown/runtime/selection.hpp), [docs/planner_continuations.md](../../../../planner_continuations.md), [docs/candidate_alternatives.md](../../../../candidate_alternatives.md), [docs/selection.md](../../../../selection.md), [docs/statistics.md](../../../../statistics.md), [docs/code_review.md](../../../../code_review.md) |

## B0033

[Lines 241–242](../../../../../tests/support/selection_independent_fixture.hpp#L241); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L241-L242:sha256:b2de0301e59207960fddfbb904dab025567ff437a57a0d11d191e5b30acbcc2d
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Explain the adjacent source contract: tie tuples borrow fields only through these immediate comparisons; arrays stay owned by snapshots. Component capacity bytes are not whole-query allocator statistics. |
| inputs / outputs | Human-readable source note in; no executable output or checked receipt. |
| invariants | This comment states context or a limitation. It does not itself enforce or prove the described behavior; use the adjacent implementation and its scoped contract. |
| ownership | Source text only; no object or resource lifetime is created. |
| failure | No runtime failure path in this comment; source encoding/comment syntax still belongs to compilation. |
| cost | No runtime operations from the comment. Any work described in the note belongs to the adjacent operation. |
| Design | [tests/support/selection_independent_fixture.hpp](../../../../../tests/support/selection_independent_fixture.hpp), [docs/selection.md](../../../../selection.md), [docs/code_review.md](../../../../code_review.md) |

## B0034

[Lines 243–265](../../../../../tests/support/selection_independent_fixture.hpp#L243); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
inline bool same_workload(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Compare every exposed workload snapshot field used by independent failure/publication scenarios. |
| inputs / outputs | Compares physical SHA, owner/interval/options/modes, descriptor/current/previous arrays, complete lifecycle metadata, component capacity report, pending/history/prior bounds/detail availability. |
| invariants | Metadata/stamp/memory lambdas return tie tuples borrowing input fields only for the immediate comparison. This content equality is not query-row equality, allocation-ledger equality, future freshness or authority to create evidence. |
| ownership | Borrowed immutable snapshots and temporary reference tuples; no detached snapshot clone or key sharing assumption. |
| failure | No assertion inside: returns false on mismatch; valid numeric/span comparisons add no successful allocation. Caller decides failure diagnostic. |
| cost | Linear descriptors/current+previous Cells (each fixed histogram) plus fixed metadata/hash, no row/account-ledger scan. |
| Design | [tests/support/selection_independent_fixture.hpp](../../../../../tests/support/selection_independent_fixture.hpp), [tests/unit/selection_public_independent_test.cpp](../../../../../tests/unit/selection_public_independent_test.cpp), [tests/unit/selection_binding_independent_test.cpp](../../../../../tests/unit/selection_binding_independent_test.cpp), [tests/unit/selection_publication_fault_independent_test.cpp](../../../../../tests/unit/selection_publication_fault_independent_test.cpp), [tests/candidates/queries/boolean_rst.cq.json](../../../../../tests/candidates/queries/boolean_rst.cq.json), [tests/candidates/trees/boolean_rst_native_s_root.tree.json](../../../../../tests/candidates/trees/boolean_rst_native_s_root.tree.json), [tests/candidates/trees/boolean_rst_generalized_x_root.tree.json](../../../../../tests/candidates/trees/boolean_rst_generalized_x_root.tree.json), [tests/candidates/trees/boolean_rst_generalized_y_root.tree.json](../../../../../tests/candidates/trees/boolean_rst_generalized_y_root.tree.json), [include/crown/planner/search.hpp](../../../../../include/crown/planner/search.hpp), [include/crown/planner/candidates.hpp](../../../../../include/crown/planner/candidates.hpp), [include/crown/planner/selection.hpp](../../../../../include/crown/planner/selection.hpp), [include/crown/runtime/selection.hpp](../../../../../include/crown/runtime/selection.hpp), [docs/planner_continuations.md](../../../../planner_continuations.md), [docs/candidate_alternatives.md](../../../../candidate_alternatives.md), [docs/selection.md](../../../../selection.md), [docs/statistics.md](../../../../statistics.md), [docs/code_review.md](../../../../code_review.md) |

## B0035

[Lines 266–281](../../../../../tests/support/selection_independent_fixture.hpp#L266); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
inline p::VerifiedOptimum replay(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Regain checked optimum authority only by actual public independent certificate replay. |
| inputs / outputs | Moves raw HeightCertificate to CertificateReplay with100M work, advances at most2000 quanta of100,000, requires complete checked valid certificate with optimum; intermediate stops must be quantum work/time. |
| invariants | Caller certificate is an unverified claim until real replay succeeds for this catalog/query. Raw tree equivalence, expected labels or a report certificate_verified flag cannot manufacture VerifiedOptimum. |
| ownership | Certificate by-value lvalue copy deep-copies raw tree/lower-bound vectors/strings; replay takes local ownership. Returned proof shares actual checked immutable control beyond replay lifetime; default moves may empty source. |
| failure | Invalid/infeasible/resource/failed replay, absent optimum, guard exhaustion and actual allocation errors fail fixture; no recovery or partial proof accepted. |
| cost | Raw certificate copying plus real bounded independent replay over all proof cells and final handle copy, with actual allocations/timing checks. |
| Design | [tests/support/selection_independent_fixture.hpp](../../../../../tests/support/selection_independent_fixture.hpp), [tests/unit/selection_public_independent_test.cpp](../../../../../tests/unit/selection_public_independent_test.cpp), [tests/unit/selection_binding_independent_test.cpp](../../../../../tests/unit/selection_binding_independent_test.cpp), [tests/unit/selection_publication_fault_independent_test.cpp](../../../../../tests/unit/selection_publication_fault_independent_test.cpp), [tests/candidates/queries/boolean_rst.cq.json](../../../../../tests/candidates/queries/boolean_rst.cq.json), [tests/candidates/trees/boolean_rst_native_s_root.tree.json](../../../../../tests/candidates/trees/boolean_rst_native_s_root.tree.json), [tests/candidates/trees/boolean_rst_generalized_x_root.tree.json](../../../../../tests/candidates/trees/boolean_rst_generalized_x_root.tree.json), [tests/candidates/trees/boolean_rst_generalized_y_root.tree.json](../../../../../tests/candidates/trees/boolean_rst_generalized_y_root.tree.json), [include/crown/planner/search.hpp](../../../../../include/crown/planner/search.hpp), [include/crown/planner/candidates.hpp](../../../../../include/crown/planner/candidates.hpp), [include/crown/planner/selection.hpp](../../../../../include/crown/planner/selection.hpp), [include/crown/runtime/selection.hpp](../../../../../include/crown/runtime/selection.hpp), [docs/planner_continuations.md](../../../../planner_continuations.md), [docs/candidate_alternatives.md](../../../../candidate_alternatives.md), [docs/selection.md](../../../../selection.md), [docs/statistics.md](../../../../statistics.md), [docs/code_review.md](../../../../code_review.md) |

## B0036

[Lines 282–282](../../../../../tests/support/selection_independent_fixture.hpp#L282); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L282-L282:sha256:de2eb719cb8550686fd9747257b6f112f8168ff719149b0d90868a1db6709a2a
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Close the recorded declaration scopes in selection_independent_fixture.hpp: namespace c05_independent. |
| inputs / outputs | Preceding namespace, type or initializer declarations in; completed lexical boundary out. |
| invariants | Brace-opening context is recorded in root-scope-context-v1.json. These are declaration/initializer boundaries, not an independent update, validation or recovery operation. |
| ownership | Enclosing objects and borrowed fields keep their declared ownership. This punctuation creates no new owner. |
| failure | Malformed scope syntax is a compile error. Any initializer/constructor failure belongs to the enclosing object declaration. |
| cost | No separate loop, guard or engine call is introduced by the delimiter; enclosing initialization and object lifetime still have their actual costs. |
| Design | [tests/support/selection_independent_fixture.hpp](../../../../../tests/support/selection_independent_fixture.hpp), [docs/selection.md](../../../../selection.md), [docs/code_review.md](../../../../code_review.md) |
