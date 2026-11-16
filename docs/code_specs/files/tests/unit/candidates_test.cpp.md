# `tests/unit/candidates_test.cpp` — block usage map

[Source](../../../../../tests/unit/candidates_test.cpp) · [Source index](../../../README.md) · [Subsystem contracts](../../../subsystem_contracts.md) · [Reviewed primitives](../../../primitives.md)

Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection.

Snapshot SHA-256: `4a6dc9800a4f7c28c45b6093c9bba403dbc3aec13ec8a297f19722470ee317bc`. 1192 lines partitioned into 69 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [tests](../../../subsystem_contracts.md#tests). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/code_review.md](../../../../code_review.md), [docs/reference_fuzz.md](../../../../reference_fuzz.md), [docs/task_ledger.md](../../../../task_ledger.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–35](../../../../../tests/unit/candidates_test.cpp#L1) | Imports dependencies; declares namespace scope; declares aliases; declares values/defaults or compile-time conditions. |  · [reviewed contract](#b0001) |
| [B0002 · 36–41](../../../../../tests/unit/candidates_test.cpp#L36) | declares callable signatures; declares values/defaults or compile-time conditions. | guard static_assert(!std::is_default_constructible_v&lt;planner::VerifiedOptimum&gt;); · [reviewed contract](#b0002) |
| [B0003 · 42–44](../../../../../tests/unit/candidates_test.cpp#L42) | Callable definition: void check(bool condition, const std::string& message) | calls std::runtime_error; guard void check(bool condition, const std::string& message) { · [reviewed contract](#b0003) |
| [B0004 · 45–45](../../../../../tests/unit/candidates_test.cpp#L45) | Explanatory comments or spacing. |  |
| [B0005 · 46–49](../../../../../tests/unit/candidates_test.cpp#L46) | Type/record definition: struct Fixture |  · [reviewed contract](#b0005) |
| [B0006 · 50–50](../../../../../tests/unit/candidates_test.cpp#L50) | Explanatory comments or spacing. |  |
| [B0007 · 51–78](../../../../../tests/unit/candidates_test.cpp#L51) | Callable definition: Fixture fixture_for(const std::vector&lt;std::vector&lt;std::size_t&gt;&gt;& scopes, const std::vector&lt;std::size_t&gt;& head, ScalarType type = … | calls names, begin, end, insert; returns fixture; growth emplace, emplace_back, insert, push_back; 5 loop sites · [reviewed contract](#b0007) |
| [B0008 · 79–79](../../../../../tests/unit/candidates_test.cpp#L79) | Explanatory comments or spacing. |  |
| [B0009 · 80–82](../../../../../tests/unit/candidates_test.cpp#L80) | Callable definition: Fixture fixture_from(const Document& document) | calls ; returns {document.catalog, document.query} · [reviewed contract](#b0009) |
| [B0010 · 83–83](../../../../../tests/unit/candidates_test.cpp#L83) | Explanatory comments or spacing. |  |
| [B0011 · 84–88](../../../../../tests/unit/candidates_test.cpp#L84) | Callable definition: std::string read_text(const std::filesystem::path& path) | calls input, check, good, string; guard check(input.good(), "cannot read fixture: " + path.string());; returns {std::istreambuf_iterator&lt;char&gt;(input), std::istreambuf_iterator&lt;char&gt;()} · [reviewed contract](#b0011) |
| [B0012 · 89–89](../../../../../tests/unit/candidates_test.cpp#L89) | Explanatory comments or spacing. |  |
| [B0013 · 90–93](../../../../../tests/unit/candidates_test.cpp#L90) | Callable definition: Document read_document(const std::filesystem::path& path) | calls read_text, io::read_document; returns io::read_document(text) · [reviewed contract](#b0013) |
| [B0014 · 94–94](../../../../../tests/unit/candidates_test.cpp#L94) | Explanatory comments or spacing. |  |
| [B0015 · 95–98](../../../../../tests/unit/candidates_test.cpp#L95) | Callable definition: FreeConnexTree read_tree(const std::filesystem::path& path, const Fixture& fixture) | calls read_text, io::read_tree; returns io::read_tree(text, fixture.catalog, fixture.query) · [reviewed contract](#b0015) |
| [B0016 · 99–99](../../../../../tests/unit/candidates_test.cpp#L99) | Explanatory comments or spacing. |  |
| [B0017 · 100–120](../../../../../tests/unit/candidates_test.cpp#L100) | Callable definition: planner::VerifiedOptimum prove(const Fixture& fixture) | calls reset, planner::ExactSearch::create, advance, optimum; guard check(result && result-&gt;valid(), "P06 exact search omitted its checked optimum");; returns *result; 1 loop sites · [reviewed contract](#b0017) |
| [B0018 · 121–121](../../../../../tests/unit/candidates_test.cpp#L121) | Explanatory comments or spacing. |  |
| [B0019 · 122–144](../../../../../tests/unit/candidates_test.cpp#L122) | Callable definition: planner::VerifiedOptimum replay_with_witness(const Fixture& fixture, const planner::VerifiedOptimum& source, FreeConnexTree witne… | calls certificate, std::move, planner::validate_tree, check; guard check(p02.valid && p02.native_height == source.height(),; returns *checked-&gt;optimum(); 1 loop sites · [reviewed contract](#b0019) |
| [B0020 · 145–145](../../../../../tests/unit/candidates_test.cpp#L145) | Explanatory comments or spacing. |  |
| [B0021 · 146–155](../../../../../tests/unit/candidates_test.cpp#L146) | Callable definition: planner::CandidateAdvance advance_until_ready(planner::CandidateProvider& provider, std::uint64_t grant = 50'000'000) | calls advance, check, std::runtime_error; guard check(advanced.stopped_for == planner::CandidateStop::quantum_work,; returns advanced; 1 loop sites · [reviewed contract](#b0021) |
| [B0022 · 156–156](../../../../../tests/unit/candidates_test.cpp#L156) | Explanatory comments or spacing. |  |
| [B0023 · 157–161](../../../../../tests/unit/candidates_test.cpp#L157) | Type/record definition: struct CandidateRun |  · [reviewed contract](#b0023) |
| [B0024 · 162–162](../../../../../tests/unit/candidates_test.cpp#L162) | Explanatory comments or spacing. |  |
| [B0025 · 163–163](../../../../../tests/unit/candidates_test.cpp#L163) | Type/record definition: enum class Slicing |  · [reviewed contract](#b0025) |
| [B0026 · 164–164](../../../../../tests/unit/candidates_test.cpp#L164) | Explanatory comments or spacing. |  |
| [B0027 · 165–171](../../../../../tests/unit/candidates_test.cpp#L165) | Callable definition: bool same_statistics(const planner::CandidateStatistics& left, const planner::CandidateStatistics& right) | calls ; returns left.proposed == right.proposed && left.rejected == right.rejected && · [reviewed contract](#b0027) |
| [B0028 · 172–172](../../../../../tests/unit/candidates_test.cpp#L172) | Explanatory comments or spacing. |  |
| [B0029 · 173–208](../../../../../tests/unit/candidates_test.cpp#L173) | Callable definition: CandidateRun drain_provider(planner::CandidateProvider& provider, Slicing slicing) | calls size, advance, check, progress; guard check(advanced.stopped_for == planner::CandidateStop::exhausted &&; returns run; growth push_back, reserve; 2 loop sites · [reviewed contract](#b0029) |
| [B0030 · 209–209](../../../../../tests/unit/candidates_test.cpp#L209) | Explanatory comments or spacing. |  |
| [B0031 · 210–278](../../../../../tests/unit/candidates_test.cpp#L210) | Callable definition: void compare_complete_case(const Fixture& fixture, const std::string& label, std::optional&lt;std::size_t&gt; expected_normal_form_coun… | calls prove, reference::exhaustive_minimum_tree, check, height; guard check(frozen.status == planner::OracleStatus::proven_minimum && frozen.minimum_height,; returns plan.signature == exact_signature; growth emplace, insert; 3 loop sites · [reviewed contract](#b0031) |
| [B0032 · 279–279](../../../../../tests/unit/candidates_test.cpp#L279) | Explanatory comments or spacing. |  |
| [B0033 · 280–312](../../../../../tests/unit/candidates_test.cpp#L280) | Callable definition: void exhaustive_three_atom_family() | calls scopes, size, push_back, fixture_for; guard check(comparisons == 225, "finite three-atom/two-variable valid-head family changed");; growth push_back; 7 loop sites · [reviewed contract](#b0033) |
| [B0034 · 313–313](../../../../../tests/unit/candidates_test.cpp#L313) | Explanatory comments or spacing. |  |
| [B0035 · 314–335](../../../../../tests/unit/candidates_test.cpp#L314) | Callable definition: void independent_reference_caps_are_incomplete() | calls fixture_for, reference::collect_normal_form_plan_set, check; guard check(zero.resource_limited && !zero.exhausted && · [reviewed contract](#b0035) |
| [B0036 · 336–336](../../../../../tests/unit/candidates_test.cpp#L336) | Explanatory comments or spacing. |  |
| [B0037 · 337–367](../../../../../tests/unit/candidates_test.cpp#L337) | Callable definition: void fixture_cases_and_slicing(const std::filesystem::path& fixture_root) | calls read_document, fixture_from, compare_complete_case, fixture_for; guard check(runs\[0\].keys == runs\[1\].keys && runs\[0\].keys == runs\[2\].keys &&; growth push_back; 1 loop sites · [reviewed contract](#b0037) |
| [B0038 · 368–368](../../../../../tests/unit/candidates_test.cpp#L368) | Explanatory comments or spacing. |  |
| [B0039 · 369–378](../../../../../tests/unit/candidates_test.cpp#L369) | Callable definition: std::string key_for_witness(const Fixture& fixture, const planner::VerifiedOptimum& original, FreeConnexTree witness) | calls replay_with_witness, std::move, planner::CandidateProvider::create, advance_until_ready; guard check(candidate && candidate-&gt;valid(), "witness provider omitted its exact checked upper");; returns candidate-&gt;structural_key() · [reviewed contract](#b0039) |
| [B0040 · 379–379](../../../../../tests/unit/candidates_test.cpp#L379) | Explanatory comments or spacing. |  |
| [B0041 · 380–486](../../../../../tests/unit/candidates_test.cpp#L380) | Callable definition: void structural_key_and_non_normal_witness(const std::filesystem::path& fixture_root) | calls fixture_from, read_document, prove, read_tree; guard check(key_for_witness(boolean, boolean_proof, native) ==; growth push_back; 4 loop sites · [reviewed contract](#b0041) |
| [B0042 · 487–487](../../../../../tests/unit/candidates_test.cpp#L487) | Explanatory comments or spacing. |  |
| [B0043 · 488–498](../../../../../tests/unit/candidates_test.cpp#L488) | Callable definition: planner::CandidateStop finish_until(planner::CandidateProvider& provider, planner::CandidateStop desired) | calls advance, std::runtime_error; returns desired; advanced.stopped_for; 1 loop sites · [reviewed contract](#b0043) |
| [B0044 · 499–499](../../../../../tests/unit/candidates_test.cpp#L499) | Explanatory comments or spacing. |  |
| [B0045 · 500–609](../../../../../tests/unit/candidates_test.cpp#L500) | Callable definition: void resource_limits_and_lifetimes() | calls fixture_for, prove, planner::CandidateProvider::create, check; guard check(no_work.advance({100, {}}).stopped_for == planner::CandidateStop::total_work &&; 1 loop sites · [reviewed contract](#b0045) |
| [B0046 · 610–610](../../../../../tests/unit/candidates_test.cpp#L610) | Explanatory comments or spacing. |  |
| [B0047 · 611–710](../../../../../tests/unit/candidates_test.cpp#L611) | Callable definition: void exact_binding_cache_fences(const std::filesystem::path& fixture_root) | calls fixture_from, read_document, prove, planner::CandidateProvider::create; guard check(cache.install(prefix) == planner::CandidateCacheInstall::inserted,; growth emplace_back; 2 loop sites · [reviewed contract](#b0047) |
| [B0048 · 711–711](../../../../../tests/unit/candidates_test.cpp#L711) | Explanatory comments or spacing. |  |
| [B0049 · 712–726](../../../../../tests/unit/candidates_test.cpp#L712) | Callable definition: Fixture distinct_residual_source_fixture() | calls push_back, validate; returns fixture; growth push_back · [reviewed contract](#b0049) |
| [B0050 · 727–727](../../../../../tests/unit/candidates_test.cpp#L727) | Explanatory comments or spacing. |  |
| [B0051 · 728–833](../../../../../tests/unit/candidates_test.cpp#L728) | Callable definition: void residual_source_and_cached_provenance() | calls distinct_residual_source_fixture, prove, check, height; guard check(first_proof.height() == 2,; returns node.kind == NodeKind::generalized; growth push_back; 4 loop sites; source comment (unverified): // Replay the same P06 lower-bound certificate with a separately P02-valid, · [reviewed contract](#b0051) |
| [B0052 · 834–834](../../../../../tests/unit/candidates_test.cpp#L834) | Explanatory comments or spacing. |  |
| [B0053 · 835–845](../../../../../tests/unit/candidates_test.cpp#L835) | Callable definition: Fixture residual_fixture(std::size_t atom_count) | calls fixture_for, std::invalid_argument; returns fixture_for({{0, 1, 2, 3}, {0, 1, 2, 4}, {3}, {4}, {1, 5}, {5}, {0, 6}},; fixture_for({{0, 1, 2, 3}… · [reviewed contract](#b0053) |
| [B0054 · 846–846](../../../../../tests/unit/candidates_test.cpp#L846) | Explanatory comments or spacing. |  |
| [B0055 · 847–919](../../../../../tests/unit/candidates_test.cpp#L847) | Callable definition: void mandatory_residual_and_wide_seed_boundaries() | calls residual_fixture, reset, planner::ResidualSearch::create, advance; guard check(advanced.progress.result != planner::ResidualResult::failed,; growth push_back, reserve; 5 loop sites · [reviewed contract](#b0055) |
| [B0056 · 920–920](../../../../../tests/unit/candidates_test.cpp#L920) | Explanatory comments or spacing. |  |
| [B0057 · 921–926](../../../../../tests/unit/candidates_test.cpp#L921) | Callable definition: std::string raw_bytes(std::initializer_list&lt;unsigned int&gt; bytes) | calls reserve, size, push_back; returns value; growth push_back, reserve; 1 loop sites · [reviewed contract](#b0057) |
| [B0058 · 927–927](../../../../../tests/unit/candidates_test.cpp#L927) | Explanatory comments or spacing. |  |
| [B0059 · 928–935](../../../../../tests/unit/candidates_test.cpp#L928) | Callable definition: Fixture string_constant_fixture(const std::string& constant) | calls push_back, validate; returns fixture; growth push_back · [reviewed contract](#b0059) |
| [B0060 · 936–936](../../../../../tests/unit/candidates_test.cpp#L936) | Explanatory comments or spacing. |  |
| [B0061 · 937–949](../../../../../tests/unit/candidates_test.cpp#L937) | Callable definition: Fixture arbitrary_string_binding_fixture() | calls raw_bytes, push_back, std::move, validate; returns fixture; growth push_back · [reviewed contract](#b0061) |
| [B0062 · 950–950](../../../../../tests/unit/candidates_test.cpp#L950) | Explanatory comments or spacing. |  |
| [B0063 · 951–960](../../../../../tests/unit/candidates_test.cpp#L951) | Callable definition: void expect_candidate_error(const std::function&lt;void()&gt;& action, const std::string& code, const std::string& context) | calls void, action, check, code; guard check(error.code() == code, context + ": wrong typed rejection " + error.code()); · [reviewed contract](#b0063) |
| [B0064 · 961–961](../../../../../tests/unit/candidates_test.cpp#L961) | Explanatory comments or spacing. |  |
| [B0065 · 962–970](../../../../../tests/unit/candidates_test.cpp#L962) | Callable definition: void require_candidate_dump_rejected(const io::Json& document, const std::string& context) | calls dump, check; guard check(rejected, context + ": invalid UTF-8 was silently escaped or replaced by JSON text output"); · [reviewed contract](#b0065) |
| [B0066 · 971–971](../../../../../tests/unit/candidates_test.cpp#L971) | Explanatory comments or spacing. |  |
| [B0067 · 972–1169](../../../../../tests/unit/candidates_test.cpp#L972) | Callable definition: void arbitrary_string_binding_domain() | calls raw_bytes, check, size, string_constant_fixture; guard check(byte_80.size() == 1 && byte_81.size() == 1 &&; returns *string; std::pair{candidate-&gt;structural_key(), *candidate}; growth emplace_back; 4 loop sites · [reviewed contract](#b0067) |
| [B0068 · 1170–1172](../../../../../tests/unit/candidates_test.cpp#L1170) | Closes surrounding scope/type. | source comment (unverified): // namespace · [reviewed contract](#b0068) |
| [B0069 · 1173–1192](../../../../../tests/unit/candidates_test.cpp#L1173) | Callable definition: int main(int argc, char** argv) | calls check, independent_reference_caps_are_incomplete, exhaustive_three_atom_family, fixture_cases_and_slicing; guard check(argc == 2, "candidate unit test requires the copied tests/candidates fixture directory");; returns 0; 1 · [reviewed contract](#b0069) |

## B0001

[Lines 1–35](../../../../../tests/unit/candidates_test.cpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L1-L35:sha256:821f18d5242758ce70faee583675bfdaaaa6d13db505ebda9cd5be8a559a5ebf
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Prepare candidates_test.cpp: include "crown/api/error.hpp", "crown/io/candidates.hpp", "crown/io/document.hpp", "crown/io/search.hpp", "crown/io/tree.hpp", "crown/planner/candidates.hpp", "crown/planner/search.hpp", "crown/planner/verify.hpp", "candidate_set.hpp", "tree_oracle.hpp", &lt;algorithm&gt;, &lt;array&gt;, &lt;chrono&gt;, &lt;cstddef&gt;, &lt;cstdint&gt;, &lt;filesystem&gt;, &lt;fstream&gt;, &lt;functional&gt;, &lt;initializer_list&gt;, &lt;iostream&gt;, &lt;iterator&gt;, &lt;map&gt;, &lt;optional&gt;, &lt;set&gt;, &lt;stdexcept&gt;, &lt;string&gt;, &lt;type_traits&gt;, &lt;utility&gt;, &lt;vector&gt;; bind local aliases/name imports. |
| inputs / outputs | Compiler-visible dependencies, names and the recorded declarations in; declarations available to the following fixture/CLI/example definitions out. |
| invariants | Declarations are scoped to this source/header and its selected ABI. Included code has its own effects; names and editable fixture values do not confer proof, admission or publication authority. |
| ownership | Aliases/includes do not create a query owner. Pointers/references/views are non-owning. Containers own their elements, which can themselves be borrowed pointers or numeric IDs. Only documented owning shared-control handles retain controls; IDs/slot-handle values do not independently keep an arena/runtime alive. |
| failure | Missing headers, ill-formed names/types, failed static assertions or active #error directives stop compilation. No runtime rejection/rollback mechanism is implemented by aliases or function prototypes. |
| cost | Preprocessing and type/constraint instantiation cost compilation. Alias/prototype syntax does not invoke the declared operation; any included definitions keep their own initialization effects. |
| Design | [tests/unit/candidates_test.cpp](../../../../../tests/unit/candidates_test.cpp), [docs/candidate_alternatives.md](../../../../candidate_alternatives.md), [docs/code_review.md](../../../../code_review.md) |

## B0002

[Lines 36–41](../../../../../tests/unit/candidates_test.cpp#L36); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L36-L41:sha256:e8381d89f285b73f4a5964409a3e4ff1b44cfa5c6e1c8ebf8ce9013257dac11d
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Prepare candidates_test.cpp: require 4 compile-time type/ABI conditions. |
| inputs / outputs | Compiler-visible dependencies, names and the recorded declarations in; declarations available to the following fixture/CLI/example definitions out. |
| invariants | Declarations are scoped to this source/header and its selected ABI. Included code has its own effects; names and editable fixture values do not confer proof, admission or publication authority. Static assertions establish only their listed C++ type properties, not query/result/recovery correctness or test execution. |
| ownership | Aliases/includes do not create a query owner. Pointers/references/views are non-owning. Containers own their elements, which can themselves be borrowed pointers or numeric IDs. Only documented owning shared-control handles retain controls; IDs/slot-handle values do not independently keep an arena/runtime alive. |
| failure | Missing headers, ill-formed names/types, failed static assertions or active #error directives stop compilation. No runtime rejection/rollback mechanism is implemented by aliases or function prototypes. |
| cost | Preprocessing and type/constraint instantiation cost compilation. Alias/prototype syntax does not invoke the declared operation; any included definitions keep their own initialization effects. |
| Design | [tests/unit/candidates_test.cpp](../../../../../tests/unit/candidates_test.cpp), [docs/candidate_alternatives.md](../../../../candidate_alternatives.md), [docs/code_review.md](../../../../code_review.md) |

## B0003

[Lines 42–44](../../../../../tests/unit/candidates_test.cpp#L42); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void check(bool condition, const std::string& message) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Provide the test assertion primitive used by the candidate suite. |
| inputs / outputs | Inputs are a Boolean predicate and a caller-supplied diagnostic std::string; output is normal return when true. |
| invariants | A false predicate throws std::runtime_error with the provided message; true does not throw. |
| ownership | The caller owns and constructs the message argument before entry; this helper retains no state. |
| failure | The false branch throws; argument construction and any concatenation happen before the call even when the predicate is true. |
| cost | The body is one conditional and one possible exception construction. Caller-side std::string construction is separate and is not failure-only. |
| Design | [tests/unit/candidates_test.cpp](../../../../../tests/unit/candidates_test.cpp), [CMakeLists.txt](../../../../../CMakeLists.txt), [include/crown/planner/candidates.hpp](../../../../../include/crown/planner/candidates.hpp), [include/crown/planner/search.hpp](../../../../../include/crown/planner/search.hpp), [src/planner/candidates.cpp](../../../../../src/planner/candidates.cpp), [docs/planner_continuations.md](../../../../planner_continuations.md) |

## B0005

[Lines 46–49](../../../../../tests/unit/candidates_test.cpp#L46); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct Fixture {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Group an owned catalog and query for planner and candidate fixtures. |
| inputs / outputs | Fields are a Catalog and Query assembled by test helpers or copied from a parsed Document. |
| invariants | Every fixture used for proofs is intended to be a valid bound query/catalog pair; fixture_for validates its result. |
| ownership | Catalog and Query are value-owned by the fixture; returned fixture copies/moves preserve their values. |
| failure | Invalid data passed into later planner APIs is rejected by their validation/admission paths. |
| cost | Plain value storage; construction and copying of vectors/strings are fixture work, not native query-runtime measurements. |
| Design | [tests/unit/candidates_test.cpp](../../../../../tests/unit/candidates_test.cpp), [CMakeLists.txt](../../../../../CMakeLists.txt), [include/crown/planner/candidates.hpp](../../../../../include/crown/planner/candidates.hpp), [include/crown/planner/search.hpp](../../../../../include/crown/planner/search.hpp), [src/planner/candidates.cpp](../../../../../src/planner/candidates.cpp), [docs/planner_continuations.md](../../../../planner_continuations.md) |

## B0007

[Lines 51–78](../../../../../tests/unit/candidates_test.cpp#L51); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Fixture fixture_for(const std::vector<std::vector<std::size_t>>& scopes,
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Build a validated synthetic catalog/query from atom scopes and a projected head. |
| inputs / outputs | Inputs are occurrence-ordered variable-name scopes, head names and optional scalar type; output maps each distinct name to a dense VariableId and creates one table/atom occurrence per scope. |
| invariants | Duplicate names across scopes share an ID; repeated entries in a scope become repeated atom terms; table/atom IDs follow occurrence order; head order follows input; validate(catalog,query) must pass. |
| ownership | Returned Fixture owns all catalog/query vectors and strings. |
| failure | Invalid generated binding propagates validation failure; out-of-range scope/head lookups fail through map::at. |
| cost | Loops over names, occurrences and columns allocate test vectors/maps and append columns/terms; work scales with the supplied fixture, without a claimed bound. |
| Design | [tests/unit/candidates_test.cpp](../../../../../tests/unit/candidates_test.cpp), [CMakeLists.txt](../../../../../CMakeLists.txt), [include/crown/planner/candidates.hpp](../../../../../include/crown/planner/candidates.hpp), [include/crown/planner/search.hpp](../../../../../include/crown/planner/search.hpp), [src/planner/candidates.cpp](../../../../../src/planner/candidates.cpp), [docs/planner_continuations.md](../../../../planner_continuations.md) |

## B0009

[Lines 80–82](../../../../../tests/unit/candidates_test.cpp#L80); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Fixture fixture_from(const Document& document) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Adapt a parsed document into the suite fixture value. |
| inputs / outputs | Input is a Document; output copies its catalog and query into Fixture. |
| invariants | The helper does no extra normalization or validation; the parsed document binding is retained as supplied. |
| ownership | The returned Fixture owns copied values; it does not borrow from Document. |
| failure | Copy/allocation exceptions propagate. |
| cost | Copies catalog/query containers and strings; no planner search is performed. |
| Design | [tests/unit/candidates_test.cpp](../../../../../tests/unit/candidates_test.cpp), [CMakeLists.txt](../../../../../CMakeLists.txt), [include/crown/planner/candidates.hpp](../../../../../include/crown/planner/candidates.hpp), [include/crown/planner/search.hpp](../../../../../include/crown/planner/search.hpp), [src/planner/candidates.cpp](../../../../../src/planner/candidates.cpp), [docs/planner_continuations.md](../../../../planner_continuations.md) |

## B0011

[Lines 84–88](../../../../../tests/unit/candidates_test.cpp#L84); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::string read_text(const std::filesystem::path& path) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Read a fixture file as text for the JSON readers. |
| inputs / outputs | Input is a filesystem path; output is all bytes read through a text-mode ifstream and stream iterators. |
| invariants | The stream must be good immediately after open; the helper then reads to EOF. |
| ownership | The returned string owns the file contents; the local stream closes on scope exit. |
| failure | Open failure throws through check with the path in its message; later stream read failures are not separately inspected. |
| cost | Performs file open, path/string formatting, and a full input copy into std::string; diagnostic path construction is eager at the check call. |
| Design | [tests/unit/candidates_test.cpp](../../../../../tests/unit/candidates_test.cpp), [CMakeLists.txt](../../../../../CMakeLists.txt), [include/crown/planner/candidates.hpp](../../../../../include/crown/planner/candidates.hpp), [include/crown/planner/search.hpp](../../../../../include/crown/planner/search.hpp), [src/planner/candidates.cpp](../../../../../src/planner/candidates.cpp), [docs/planner_continuations.md](../../../../planner_continuations.md) |

## B0013

[Lines 90–93](../../../../../tests/unit/candidates_test.cpp#L90); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Document read_document(const std::filesystem::path& path) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Parse one query/catalog fixture document. |
| inputs / outputs | Input is a path; output is io::read_document applied to read_text(path). |
| invariants | The exact text returned by the helper is supplied to the document reader. |
| ownership | Document owns parsed values; intermediate text dies after return. |
| failure | File-open errors come from read_text; parse/validation errors from io::read_document propagate. |
| cost | Reads the full fixture and parses/allocates its document representation; this is test setup. |
| Design | [tests/unit/candidates_test.cpp](../../../../../tests/unit/candidates_test.cpp), [CMakeLists.txt](../../../../../CMakeLists.txt), [include/crown/planner/candidates.hpp](../../../../../include/crown/planner/candidates.hpp), [include/crown/planner/search.hpp](../../../../../include/crown/planner/search.hpp), [src/planner/candidates.cpp](../../../../../src/planner/candidates.cpp), [docs/planner_continuations.md](../../../../planner_continuations.md), [include/crown/io/document.hpp](../../../../../include/crown/io/document.hpp) |

## B0015

[Lines 95–98](../../../../../tests/unit/candidates_test.cpp#L95); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
FreeConnexTree read_tree(const std::filesystem::path& path, const Fixture& fixture) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Parse a supplied free-connex tree against a fixture binding. |
| inputs / outputs | Inputs are a path and Fixture; output is io::read_tree(text,catalog,query). |
| invariants | Tree parsing is bound to that fixture catalog and query, not to an inferred binding. |
| ownership | Returned tree owns its nodes/scopes; fixture remains caller-owned. |
| failure | File-open, parse, and binding/tree validation errors propagate from the helpers. |
| cost | Reads and parses the whole tree document and constructs a tree; cost is per fixture file. |
| Design | [tests/unit/candidates_test.cpp](../../../../../tests/unit/candidates_test.cpp), [CMakeLists.txt](../../../../../CMakeLists.txt), [include/crown/planner/candidates.hpp](../../../../../include/crown/planner/candidates.hpp), [include/crown/planner/search.hpp](../../../../../include/crown/planner/search.hpp), [src/planner/candidates.cpp](../../../../../src/planner/candidates.cpp), [docs/planner_continuations.md](../../../../planner_continuations.md), [include/crown/io/tree.hpp](../../../../../include/crown/io/tree.hpp) |

## B0017

[Lines 100–120](../../../../../tests/unit/candidates_test.cpp#L100); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
planner::VerifiedOptimum prove(const Fixture& fixture) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Obtain a checked P06 exact-minimum proof for candidate tests. |
| inputs / outputs | Input is Fixture; output is the VerifiedOptimum returned by ExactSearch::optimum after progress reports verified_optimum. |
| invariants | Producer/replay work and logical-depth limits are cleared; each advance receives a 50,000,000 work quantum; at most 5,000,000 loop iterations; failed or unexpected stops are rejected. |
| ownership | ExactSearch owner and its internal continuation are local; returned proof is an owning value/handle. |
| failure | Throws if search fails, stops for an unrecognized reason, omits a valid optimum, or reaches the finite test guard. |
| cost | Repeatedly advances a full exact proof and replay; large configured quanta and loop guard are test controls, not measured cost or a universal completion bound. |
| Design | [tests/unit/candidates_test.cpp](../../../../../tests/unit/candidates_test.cpp), [CMakeLists.txt](../../../../../CMakeLists.txt), [include/crown/planner/candidates.hpp](../../../../../include/crown/planner/candidates.hpp), [include/crown/planner/search.hpp](../../../../../include/crown/planner/search.hpp), [src/planner/candidates.cpp](../../../../../src/planner/candidates.cpp), [docs/planner_continuations.md](../../../../planner_continuations.md), [src/planner/search_session.cpp](../../../../../src/planner/search_session.cpp), [docs/planner_proofs.md](../../../../planner_proofs.md) |

## B0019

[Lines 122–144](../../../../../tests/unit/candidates_test.cpp#L122); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
planner::VerifiedOptimum replay_with_witness(const Fixture& fixture,
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Replay the same minimum certificate with a replacement upper-tree witness. |
| inputs / outputs | Inputs are Fixture, source VerifiedOptimum and moved witness; output is the independently replayed optimum. |
| invariants | Only certificate.tree changes; replacement must pass P02 at source.height before P06 CertificateReplay; same 50,000,000 work quantum and 5,000,000-step guard. |
| ownership | Certificate/tree are copied or moved into replay; returned checked optimum owns its proof. |
| failure | P02 mismatch, failed replay, or guard exhaustion throws via check/runtime_error. |
| cost | Copies certificate data, validates the tree, then runs incremental P06 replay and its allocations; not a cheap structural-key operation. |
| Design | [tests/unit/candidates_test.cpp](../../../../../tests/unit/candidates_test.cpp), [CMakeLists.txt](../../../../../CMakeLists.txt), [include/crown/planner/candidates.hpp](../../../../../include/crown/planner/candidates.hpp), [include/crown/planner/search.hpp](../../../../../include/crown/planner/search.hpp), [src/planner/candidates.cpp](../../../../../src/planner/candidates.cpp), [docs/planner_continuations.md](../../../../planner_continuations.md), [src/planner/search_session.cpp](../../../../../src/planner/search_session.cpp), [docs/planner_proofs.md](../../../../planner_proofs.md) |

## B0021

[Lines 146–155](../../../../../tests/unit/candidates_test.cpp#L146); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
planner::CandidateAdvance advance_until_ready(planner::CandidateProvider& provider,
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Advance a candidate provider until it offers the next checked candidate. |
| inputs / outputs | Inputs are provider reference and optional work grant defaulting to 50,000,000; output is the candidate-ready advance result. |
| invariants | Only candidate_ready is success; every other intermediate stop must be quantum_work; maximum 5,000,000 advances. |
| ownership | Provider remains caller-owned and mutable; returned progress is a value. |
| failure | Unexpected stop or guard exhaustion throws. |
| cost | Loops through provider transitions and candidate validation/retention until ready; grant is a ceiling for reported work units, not wall-clock cost. |
| Design | [tests/unit/candidates_test.cpp](../../../../../tests/unit/candidates_test.cpp), [CMakeLists.txt](../../../../../CMakeLists.txt), [include/crown/planner/candidates.hpp](../../../../../include/crown/planner/candidates.hpp), [include/crown/planner/search.hpp](../../../../../include/crown/planner/search.hpp), [src/planner/candidates.cpp](../../../../../src/planner/candidates.cpp), [docs/planner_continuations.md](../../../../planner_continuations.md) |

## B0023

[Lines 157–161](../../../../../tests/unit/candidates_test.cpp#L157); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct CandidateRun {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Collect comparison outputs from one completed provider drain. |
| inputs / outputs | Fields store candidate reference signatures, structural keys, and final progress. |
| invariants | The signature/key vectors are populated in matching candidate-index order by drain_provider. |
| ownership | Vectors own their strings and progress snapshot; no candidate handles are stored. |
| failure | Allocation failures propagate; incomplete provider runs are rejected by drain_provider. |
| cost | Storage grows with the retained candidate count and encoded signature/key lengths. |
| Design | [tests/unit/candidates_test.cpp](../../../../../tests/unit/candidates_test.cpp), [CMakeLists.txt](../../../../../CMakeLists.txt), [include/crown/planner/candidates.hpp](../../../../../include/crown/planner/candidates.hpp), [include/crown/planner/search.hpp](../../../../../include/crown/planner/search.hpp), [src/planner/candidates.cpp](../../../../../src/planner/candidates.cpp), [docs/planner_continuations.md](../../../../planner_continuations.md) |

## B0025

[Lines 163–163](../../../../../tests/unit/candidates_test.cpp#L163); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
enum class Slicing { one_shot, unit, varied };
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Name the three provider grant schedules compared by the tests. |
| inputs / outputs | Values select one-shot, one-work-unit, or repeating varied grants. |
| invariants | Varied schedule is defined in drain_provider as 3,1,5,2; enum itself carries no state. |
| ownership | No owned resources. |
| failure | No failure path beyond invalid enum use in the helper logic. |
| cost | No runtime work; selecting a test schedule only. |
| Design | [tests/unit/candidates_test.cpp](../../../../../tests/unit/candidates_test.cpp), [CMakeLists.txt](../../../../../CMakeLists.txt), [include/crown/planner/candidates.hpp](../../../../../include/crown/planner/candidates.hpp), [include/crown/planner/search.hpp](../../../../../include/crown/planner/search.hpp), [src/planner/candidates.cpp](../../../../../src/planner/candidates.cpp), [docs/planner_continuations.md](../../../../planner_continuations.md) |

## B0027

[Lines 165–171](../../../../../tests/unit/candidates_test.cpp#L165); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
bool same_statistics(const planner::CandidateStatistics& left,
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Compare the selected candidate-provider statistic fields for deterministic slicing. |
| inputs / outputs | Inputs are two CandidateStatistics values; output is equality of proposed, rejected, taller, duplicates, published, topologies, scope_tuples and cache_seeded. |
| invariants | It intentionally compares only these named counters; it does not establish equality of every progress/resource field. |
| ownership | Inputs are borrowed; output is Boolean. |
| failure | No exception path in the comparison itself. |
| cost | Fixed number of scalar comparisons. |
| Design | [tests/unit/candidates_test.cpp](../../../../../tests/unit/candidates_test.cpp), [CMakeLists.txt](../../../../../CMakeLists.txt), [include/crown/planner/candidates.hpp](../../../../../include/crown/planner/candidates.hpp), [include/crown/planner/search.hpp](../../../../../include/crown/planner/search.hpp), [src/planner/candidates.cpp](../../../../../src/planner/candidates.cpp), [docs/planner_continuations.md](../../../../planner_continuations.md) |

## B0029

[Lines 173–208](../../../../../tests/unit/candidates_test.cpp#L173); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
CandidateRun drain_provider(planner::CandidateProvider& provider, Slicing slicing) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Drain a provider under one of three work-quantum schedules and independently inspect every retained candidate. |
| inputs / outputs | Inputs are provider reference and Slicing; output contains all reference signatures/keys and final progress. |
| invariants | Loops at most 10,000,000 calls; one-shot uses 50,000,000, unit uses 1, varied cycles 3,1,5,2; only candidate_ready/quantum_work may continue; termination must be explicit exhausted plus family_exhausted. |
| ownership | Provider is borrowed and mutable. candidate(index) creates local owning candidate handles for inspection; output owns copied signature/key strings and a progress value. |
| failure | Throws on unexpected stop, false exhaustion, missing/invalid handle, P02 height mismatch, or changed original P06 proof. |
| cost | Advances enumeration, then performs P02 validation and reference signature/key generation for every retained candidate; output vectors allocate. Work grant counters do not bound tree validation, encoding, allocator or total test CPU. |
| Design | [tests/unit/candidates_test.cpp](../../../../../tests/unit/candidates_test.cpp), [CMakeLists.txt](../../../../../CMakeLists.txt), [include/crown/planner/candidates.hpp](../../../../../include/crown/planner/candidates.hpp), [include/crown/planner/search.hpp](../../../../../include/crown/planner/search.hpp), [src/planner/candidates.cpp](../../../../../src/planner/candidates.cpp), [docs/planner_continuations.md](../../../../planner_continuations.md), [src/planner/candidate_generator.cpp](../../../../../src/planner/candidate_generator.cpp), [tests/reference/candidate_set.cpp](../../../../../tests/reference/candidate_set.cpp) |

## B0031

[Lines 210–278](../../../../../tests/unit/candidates_test.cpp#L210); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void compare_complete_case(const Fixture& fixture, const std::string& label,
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Compare one complete provider family with independent minimum-height and normal-form references. |
| inputs / outputs | Inputs are Fixture, label and optional expected plan count; runs P06 prove, frozen P03 minimum, P03 Prüfer normal-form collection, then CandidateProvider. |
| invariants | Requires complete uncapped reference enumeration at the proved height; admits the exact P06 witness first; compares candidate signature set with reference plans plus exact seed; every candidate preserves serialized original proof; independently checks signature↔production-key bijection. |
| ownership | This void helper retains proof, provider, reference results, CandidateRun strings, sets and maps locally and returns no object. Fixture and label are borrowed during the call. |
| failure | Any incomplete oracle/provider, invalid P02 plan, count/set/proof/key mismatch throws. |
| cost | Composes expensive exact proof/replay, finite exhaustive oracle and provider enumeration; allocates sets/maps/signatures per candidate. The finite fixtures establish these tested cases only. |
| Design | [tests/unit/candidates_test.cpp](../../../../../tests/unit/candidates_test.cpp), [CMakeLists.txt](../../../../../CMakeLists.txt), [include/crown/planner/candidates.hpp](../../../../../include/crown/planner/candidates.hpp), [include/crown/planner/search.hpp](../../../../../include/crown/planner/search.hpp), [src/planner/candidates.cpp](../../../../../src/planner/candidates.cpp), [docs/planner_continuations.md](../../../../planner_continuations.md), [tests/reference/candidate_set.cpp](../../../../../tests/reference/candidate_set.cpp), [tests/reference/candidate_set.hpp](../../../../../tests/reference/candidate_set.hpp), [tests/reference/tree_oracle.cpp](../../../../../tests/reference/tree_oracle.cpp), [docs/planner_proofs.md](../../../../planner_proofs.md) |

## B0033

[Lines 280–312](../../../../../tests/unit/candidates_test.cpp#L280); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void exhaustive_three_atom_family() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Exercise the complete candidate comparison on every valid head for three ordered two-variable atom scopes. |
| inputs / outputs | No inputs; iterates three 2-bit scope masks and a 2-bit head mask, builds Fixture and calls compare_complete_case. |
| invariants | Invalid heads containing absent variables are skipped; exactly 225 valid scope/head combinations are required. |
| ownership | Each fixture, proof and provider is local to one iteration. |
| failure | Any differential, completeness, proof, key or expected-count assertion aborts the test. |
| cost | Runs 225 full exact/P03 normal-form/provider comparisons with repeated allocations; this is a finite fixture family, not a global complexity guarantee. |
| Design | [tests/unit/candidates_test.cpp](../../../../../tests/unit/candidates_test.cpp), [CMakeLists.txt](../../../../../CMakeLists.txt), [include/crown/planner/candidates.hpp](../../../../../include/crown/planner/candidates.hpp), [include/crown/planner/search.hpp](../../../../../include/crown/planner/search.hpp), [src/planner/candidates.cpp](../../../../../src/planner/candidates.cpp), [docs/planner_continuations.md](../../../../planner_continuations.md), [tests/reference/candidate_set.cpp](../../../../../tests/reference/candidate_set.cpp), [tests/reference/tree_oracle.cpp](../../../../../tests/reference/tree_oracle.cpp) |

## B0035

[Lines 314–335](../../../../../tests/unit/candidates_test.cpp#L314); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void independent_reference_caps_are_incomplete() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Ensure capped reference enumeration reports incompleteness rather than semantic support or exhaustion. |
| inputs / outputs | Builds three small bindings: zero-work, four native occurrences, and one four-variable scope; calls reference collector. |
| invariants | Asserts distinct work_limit, native_occurrence_cap and active_variable_cap stops with resource_limited=true and exhausted=false. |
| ownership | Fixture and collection results are local values. |
| failure | Assertion failure indicates a cap was misreported; API resource stops are expected test outputs. |
| cost | Three bounded reference calls; cap checks may scan/construct a small fixture before stopping. These are reference-oracle limits, not production provider ceilings. |
| Design | [tests/unit/candidates_test.cpp](../../../../../tests/unit/candidates_test.cpp), [CMakeLists.txt](../../../../../CMakeLists.txt), [include/crown/planner/candidates.hpp](../../../../../include/crown/planner/candidates.hpp), [include/crown/planner/search.hpp](../../../../../include/crown/planner/search.hpp), [src/planner/candidates.cpp](../../../../../src/planner/candidates.cpp), [docs/planner_continuations.md](../../../../planner_continuations.md), [tests/reference/candidate_set.cpp](../../../../../tests/reference/candidate_set.cpp), [tests/reference/candidate_set.hpp](../../../../../tests/reference/candidate_set.hpp) |

## B0037

[Lines 337–367](../../../../../tests/unit/candidates_test.cpp#L337); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void fixture_cases_and_slicing(const std::filesystem::path& fixture_root) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Exercise disk fixtures, special structural cases and deterministic resumable provider slicing. |
| inputs / outputs | Input is fixture-root path; loads Boolean and equal-scope self-join JSON fixtures, adds empty/nullary/unary/disconnected/projected synthetic cases, then drains the Boolean provider three ways. |
| invariants | Fixture count assertions include three normal forms for Boolean and four for the self-join; one-shot/unit/varied produce equal ordered keys/signatures, selected statistics and committed-transition counts. |
| ownership | Each proof/provider/run owns its data locally; filesystem path is borrowed. |
| failure | File/parse/search/provider failures and any changed family/counter throw. |
| cost | Reads two query fixtures, runs multiple exact/oracle/provider comparisons, and materializes outputs three times; only the stated finite fixtures are checked. |
| Design | [tests/unit/candidates_test.cpp](../../../../../tests/unit/candidates_test.cpp), [CMakeLists.txt](../../../../../CMakeLists.txt), [include/crown/planner/candidates.hpp](../../../../../include/crown/planner/candidates.hpp), [include/crown/planner/search.hpp](../../../../../include/crown/planner/search.hpp), [src/planner/candidates.cpp](../../../../../src/planner/candidates.cpp), [docs/planner_continuations.md](../../../../planner_continuations.md), [tests/reference/candidate_set.cpp](../../../../../tests/reference/candidate_set.cpp), [tests/candidates/queries/boolean_rst.cq.json](../../../../../tests/candidates/queries/boolean_rst.cq.json), [tests/candidates/queries/self_join_equal_scope_three.cq.json](../../../../../tests/candidates/queries/self_join_equal_scope_three.cq.json) |

## B0039

[Lines 369–378](../../../../../tests/unit/candidates_test.cpp#L369); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::string key_for_witness(const Fixture& fixture,
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Compute the checked structural key for a supplied original witness. |
| inputs / outputs | Inputs are fixture, original proof and moved witness; output is the first provider candidate key. |
| invariants | Witness is P02-validated and P06-replayed by helper; provider must publish a valid exact checked upper. |
| ownership | Temporary proof/provider/candidate are local; returned key owns its bytes. |
| failure | Invalid witness, proof replay or missing candidate throws. |
| cost | Per call does a P02 validation, full proof replay and provider admission/key construction; callers intentionally repeat it across witness variants. |
| Design | [tests/unit/candidates_test.cpp](../../../../../tests/unit/candidates_test.cpp), [CMakeLists.txt](../../../../../CMakeLists.txt), [include/crown/planner/candidates.hpp](../../../../../include/crown/planner/candidates.hpp), [include/crown/planner/search.hpp](../../../../../include/crown/planner/search.hpp), [src/planner/candidates.cpp](../../../../../src/planner/candidates.cpp), [docs/planner_continuations.md](../../../../planner_continuations.md), [src/planner/candidate_key.cpp](../../../../../src/planner/candidate_key.cpp), [src/planner/search_session.cpp](../../../../../src/planner/search_session.cpp) |

## B0041

[Lines 380–486](../../../../../tests/unit/candidates_test.cpp#L380); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void structural_key_and_non_normal_witness(const std::filesystem::path& fixture_root) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Check structural-key equivalence/distinction, non-normal witness retention, exact-binding cache reuse and handle lifetime. |
| inputs / outputs | Input fixture-root path; reads Boolean/self-join tree variants and builds singleton unary-generalized and exact witnesses. |
| invariants | Node IDs/vector/child/scope order changes preserve keys; root/kind/grouping/scope and self-join occurrence changes distinguish tested keys; unary generalized upper is P02/P06 valid; exact and normal-form candidates remain separate; cached prefix is rebound to new original proof; retained handle survives cancel and cache clear. |
| ownership | Proofs, tree values, cache, provider and candidate handles use owning APIs. The retained candidate is checked after provider.cancel() and cache.clear(); the provider and cache objects themselves still exist until scope exit. |
| failure | Any invalid tree/replay, merge, lost provenance, stale proof binding, or lifetime break throws. |
| cost | Loads multiple tree fixtures and repeatedly proves/replays/admit candidates; key construction traverses checked structures; cache snapshot/lookup copies or compares bounded entries and may allocate. No claim covers all trees or all cache sizes. |
| Design | [tests/unit/candidates_test.cpp](../../../../../tests/unit/candidates_test.cpp), [CMakeLists.txt](../../../../../CMakeLists.txt), [include/crown/planner/candidates.hpp](../../../../../include/crown/planner/candidates.hpp), [include/crown/planner/search.hpp](../../../../../include/crown/planner/search.hpp), [src/planner/candidates.cpp](../../../../../src/planner/candidates.cpp), [docs/planner_continuations.md](../../../../planner_continuations.md), [src/planner/candidate_key.cpp](../../../../../src/planner/candidate_key.cpp), [src/planner/candidate_binding.hpp](../../../../../src/planner/candidate_binding.hpp), [tests/reference/candidate_set.cpp](../../../../../tests/reference/candidate_set.cpp), [tests/candidates/trees/boolean_rst_native_s_root.tree.json](../../../../../tests/candidates/trees/boolean_rst_native_s_root.tree.json), [tests/candidates/trees/self_join_left_direct.tree.json](../../../../../tests/candidates/trees/self_join_left_direct.tree.json) |

## B0043

[Lines 488–498](../../../../../tests/unit/candidates_test.cpp#L488); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
planner::CandidateStop finish_until(planner::CandidateProvider& provider,
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Advance a provider until a requested stop result or a terminal alternative. |
| inputs / outputs | Inputs are provider reference and desired CandidateStop; returns desired stop if reached. |
| invariants | Uses 50,000,000 work grants for at most 5,000,000 iterations; ready and quantum_work continue; any other stop is returned unchanged. |
| ownership | Provider remains caller-owned. |
| failure | Guard exhaustion throws; unexpected terminal state is reported to caller for its assertion. |
| cost | Repeated provider advances; runtime work per call is governed by provider accounting and may include uncharged housekeeping. |
| Design | [tests/unit/candidates_test.cpp](../../../../../tests/unit/candidates_test.cpp), [CMakeLists.txt](../../../../../CMakeLists.txt), [include/crown/planner/candidates.hpp](../../../../../include/crown/planner/candidates.hpp), [include/crown/planner/search.hpp](../../../../../include/crown/planner/search.hpp), [src/planner/candidates.cpp](../../../../../src/planner/candidates.cpp), [docs/planner_continuations.md](../../../../planner_continuations.md) |

## B0045

[Lines 500–609](../../../../../tests/unit/candidates_test.cpp#L500); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void resource_limits_and_lifetimes() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Exercise candidate limit stops, monotone resumes, inert grants and owning-handle lifetimes. |
| inputs / outputs | Builds one proof/fixture; probes total work, retained candidate capacity, logical depth, record/cell limits, active time and invalid/zero quantum; moves/cancels provider and moves candidate handle. |
| invariants | Zero ceilings stop without false exhaustion; raises extend the same provider to exhaustion. Inert invalid/zero advances preserve the six compared fields: phase, last_stop, work, records, cells and candidate_count. Candidate and snapshot remain valid after move/cancel; moving the candidate invalidates its source handle. |
| ownership | Providers own continuation state; snapshots/candidates are retained owning handles and tested after owner transitions. |
| failure | Each assertion expects a specific CandidateStop/LimitChange; unexpected stops or invalid handles throw. |
| cost | Many resume/drain loops (each up to 5,000,000 advances), provider state/candidate allocations, snapshots and P02 checks. Logical ceilings and grants are not total heap/RSS/CPU bounds. |
| Design | [tests/unit/candidates_test.cpp](../../../../../tests/unit/candidates_test.cpp), [CMakeLists.txt](../../../../../CMakeLists.txt), [include/crown/planner/candidates.hpp](../../../../../include/crown/planner/candidates.hpp), [include/crown/planner/search.hpp](../../../../../include/crown/planner/search.hpp), [src/planner/candidates.cpp](../../../../../src/planner/candidates.cpp), [docs/planner_continuations.md](../../../../planner_continuations.md) |

## B0047

[Lines 611–710](../../../../../tests/unit/candidates_test.cpp#L611); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void exact_binding_cache_fences(const std::filesystem::path& fixture_root) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Fence exact-binding cache reuse against changes to catalog/query binding and unsupported candidate contexts. |
| inputs / outputs | Input fixture-root path; creates proof/cache and applies binding mutations and invalid context profiles. |
| invariants | Cache hits require the tested identical binding; changes to identity/schema/statistics/constraints/query terms/occurrences/head or context are rejected/missed; exact bytes and context are the key boundary exercised. |
| ownership | Cache and snapshots own retained entries; fixtures/proofs are local. |
| failure | Expected lookup miss or typed candidate-context rejection; a false hit/accepted invalid context throws. |
| cost | Repeatedly builds proofs for mutated bindings and performs cache lookups/admission; cache lookup compares retained bindings and provider validation may traverse input. The finite list is not every possible binding mutation. |
| Design | [tests/unit/candidates_test.cpp](../../../../../tests/unit/candidates_test.cpp), [CMakeLists.txt](../../../../../CMakeLists.txt), [include/crown/planner/candidates.hpp](../../../../../include/crown/planner/candidates.hpp), [include/crown/planner/search.hpp](../../../../../include/crown/planner/search.hpp), [src/planner/candidates.cpp](../../../../../src/planner/candidates.cpp), [docs/planner_continuations.md](../../../../planner_continuations.md), [src/planner/candidate_binding.hpp](../../../../../src/planner/candidate_binding.hpp) |

## B0049

[Lines 712–726](../../../../../tests/unit/candidates_test.cpp#L712); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Fixture distinct_residual_source_fixture() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Build a valid three-occurrence residual-source binding with nullary, connected and projected structure. |
| inputs / outputs | No inputs; creates N(), R(x,y), S(x), with head y and validates catalog/query. |
| invariants | Occurrence order is N,R,S; R-root native residual witness is the source distinction asserted by the consumer test. |
| ownership | Returned catalog/query are value-owned. |
| failure | Validation failure propagates. |
| cost | Constructs a few tables/columns/terms and validates them; fixture-only work. |
| Design | [tests/unit/candidates_test.cpp](../../../../../tests/unit/candidates_test.cpp), [CMakeLists.txt](../../../../../CMakeLists.txt), [include/crown/planner/candidates.hpp](../../../../../include/crown/planner/candidates.hpp), [include/crown/planner/search.hpp](../../../../../include/crown/planner/search.hpp), [src/planner/candidates.cpp](../../../../../src/planner/candidates.cpp), [docs/planner_continuations.md](../../../../planner_continuations.md), [docs/planner_proofs.md](../../../../planner_proofs.md) |

## B0051

[Lines 728–833](../../../../../tests/unit/candidates_test.cpp#L728); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void residual_source_and_cached_provenance() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Verify P05 residual seed provenance remains distinct from the exact witness through P07 caching/rebinding. |
| inputs / outputs | No inputs; proves the distinct fixture, runs ResidualSearch, admits its checked seed to CandidateProvider, caches snapshot, and reuses it against an alternative P06 witness. |
| invariants | Expected minimum is two; residual tree is P02-valid native occurrence 1 with no generalized node. The first exhausted provider holds two distinct exact/residual plans; second unary exact witness plus cached prefix produces three. All reused candidates carry the second original proof; residual source, last-step and valid trace remain preserved. |
| ownership | Residual/exact providers, cache, snapshots and candidate handles use owning public handles; the original residual handle is consulted after reuse. |
| failure | Failed residual/proof, wrong source or height, provenance loss, invalid trace, stale proof binding, or missing cache candidate throws. |
| cost | Runs P06, P05 and P07 continuations plus P02 and reference signatures; cache install/lookup and candidate vectors allocate/compare. The 10,000,000 loop guard is a test guard, not a runtime bound. |
| Design | [tests/unit/candidates_test.cpp](../../../../../tests/unit/candidates_test.cpp), [CMakeLists.txt](../../../../../CMakeLists.txt), [include/crown/planner/candidates.hpp](../../../../../include/crown/planner/candidates.hpp), [include/crown/planner/search.hpp](../../../../../include/crown/planner/search.hpp), [src/planner/candidates.cpp](../../../../../src/planner/candidates.cpp), [docs/planner_continuations.md](../../../../planner_continuations.md), [src/planner/residual.cpp](../../../../../src/planner/residual.cpp) |

## B0053

[Lines 835–845](../../../../../tests/unit/candidates_test.cpp#L835); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Fixture residual_fixture(std::size_t atom_count) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Return one of the two fixed seven- or nine-atom residual counterexample bindings. |
| inputs / outputs | Input atom_count must be 7 or 9; output scope/head fixture selected by exact value. |
| invariants | Returned scopes/heads are literal test fixtures; all other counts throw invalid_argument. |
| ownership | Fixture owns generated catalog/query values. |
| failure | Unsupported atom_count throws with a diagnostic. |
| cost | Selects/copies a small constant scope list and calls fixture_for; fixture construction validates. |
| Design | [tests/unit/candidates_test.cpp](../../../../../tests/unit/candidates_test.cpp), [CMakeLists.txt](../../../../../CMakeLists.txt), [include/crown/planner/candidates.hpp](../../../../../include/crown/planner/candidates.hpp), [include/crown/planner/search.hpp](../../../../../include/crown/planner/search.hpp), [src/planner/candidates.cpp](../../../../../src/planner/candidates.cpp), [docs/planner_continuations.md](../../../../planner_continuations.md), [docs/planner_proofs.md](../../../../planner_proofs.md) |

## B0055

[Lines 847–919](../../../../../tests/unit/candidates_test.cpp#L847); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void mandatory_residual_and_wide_seed_boundaries() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Exercise mandatory residual proofs and bounded candidate continuation on 7/9 atoms plus a 70-by-70 repeated-scope query. |
| inputs / outputs | No inputs; residual mode is require_exact_original for the two residual fixtures; wide fixture has 70 occurrences each containing 70 variables. |
| invariants | Residual proof and seed must both be P02-valid at height 3; initial provider emits exact seed, two 1,000-work advances each consume at most grant and remain nonexhausted; wide P06 minimum is 1 and two grants remain explicitly nonexhausted. |
| ownership | Returned seeds/candidates/proofs are owning handles; retained candidate is checked after cancel. |
| failure | Any failure, false exhaustion, over-grant attempted delta, or lost valid retained handle throws. |
| cost | Runs two P05 proofs and bounded P07 steps, then exact search plus bounded enumeration for 4,900 repeated terms; test counts are specific fixtures. Attempts are work-counter deltas, not CPU/allocation/RSS bounds. |
| Design | [tests/unit/candidates_test.cpp](../../../../../tests/unit/candidates_test.cpp), [CMakeLists.txt](../../../../../CMakeLists.txt), [include/crown/planner/candidates.hpp](../../../../../include/crown/planner/candidates.hpp), [include/crown/planner/search.hpp](../../../../../include/crown/planner/search.hpp), [src/planner/candidates.cpp](../../../../../src/planner/candidates.cpp), [docs/planner_continuations.md](../../../../planner_continuations.md), [src/planner/residual.cpp](../../../../../src/planner/residual.cpp) |

## B0057

[Lines 921–926](../../../../../tests/unit/candidates_test.cpp#L921); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::string raw_bytes(std::initializer_list<unsigned int> bytes) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Create strings from explicit byte values, including non-UTF-8 bytes. |
| inputs / outputs | Input is an initializer list of unsigned integers; output requests reserve(bytes.size()) and appends static_cast&lt;char&gt;(byte) for each entry. |
| invariants | No UTF-8 validation or normalization occurs here; callers test byte representation explicitly. |
| ownership | Returned std::string owns the bytes. |
| failure | There is no explicit integer-range or UTF-8 check. String allocation exceptions propagate; current callers supply 0x80/0x81 and check their unsigned-char byte representations. |
| cost | One reserve and one append per input byte; used only for fixture construction. |
| Design | [tests/unit/candidates_test.cpp](../../../../../tests/unit/candidates_test.cpp), [CMakeLists.txt](../../../../../CMakeLists.txt), [include/crown/planner/candidates.hpp](../../../../../include/crown/planner/candidates.hpp), [include/crown/planner/search.hpp](../../../../../include/crown/planner/search.hpp), [src/planner/candidates.cpp](../../../../../src/planner/candidates.cpp), [docs/planner_continuations.md](../../../../planner_continuations.md) |

## B0059

[Lines 928–935](../../../../../tests/unit/candidates_test.cpp#L928); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Fixture string_constant_fixture(const std::string& constant) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Build a one-occurrence string-constant query fixture. |
| inputs / outputs | Input is an arbitrary std::string constant; output has one string column and one atom with Value{constant}. |
| invariants | The fixture is validated; constant bytes and embedded NUL are supplied as a length-aware std::string. |
| ownership | Returned binding owns copied/moved string data. |
| failure | Validation errors propagate. |
| cost | Constructs and validates a singleton catalog/query; Value{constant} copies the borrowed const std::string, then temporary binding values may move into containers. |
| Design | [tests/unit/candidates_test.cpp](../../../../../tests/unit/candidates_test.cpp), [CMakeLists.txt](../../../../../CMakeLists.txt), [include/crown/planner/candidates.hpp](../../../../../include/crown/planner/candidates.hpp), [include/crown/planner/search.hpp](../../../../../include/crown/planner/search.hpp), [src/planner/candidates.cpp](../../../../../src/planner/candidates.cpp), [docs/planner_continuations.md](../../../../planner_continuations.md), [include/crown/planner/verify.hpp](../../../../../include/crown/planner/verify.hpp) |

## B0061

[Lines 937–949](../../../../../tests/unit/candidates_test.cpp#L937); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Fixture arbitrary_string_binding_fixture() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Build a valid binding whose identifiers, alias and catalog metadata contain arbitrary byte strings. |
| inputs / outputs | No inputs; creates table/column/variable/occurrence/alias/reason values including invalid UTF-8 bytes and embedded NUL. |
| invariants | All identifiers remain length-aware std::string values; validate is required to accept the binding. |
| ownership | Returned fixture owns all strings and containers. |
| failure | Validation failure propagates; later JSON text encoding is tested separately and may reject invalid UTF-8. |
| cost | Constructs a small fixture with concatenated strings and performs binding validation. |
| Design | [tests/unit/candidates_test.cpp](../../../../../tests/unit/candidates_test.cpp), [CMakeLists.txt](../../../../../CMakeLists.txt), [include/crown/planner/candidates.hpp](../../../../../include/crown/planner/candidates.hpp), [include/crown/planner/search.hpp](../../../../../include/crown/planner/search.hpp), [src/planner/candidates.cpp](../../../../../src/planner/candidates.cpp), [docs/planner_continuations.md](../../../../planner_continuations.md), [include/crown/planner/verify.hpp](../../../../../include/crown/planner/verify.hpp) |

## B0063

[Lines 951–960](../../../../../tests/unit/candidates_test.cpp#L951); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void expect_candidate_error(const std::function<void()>& action, const std::string& code,
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Assert that an action throws the requested typed planner Error. |
| inputs / outputs | Inputs are callable, expected error code and context string; output is normal return only when caught Error.code() matches. |
| invariants | Only crown::Error is accepted as the typed rejection; a wrong code fails and no throw is failure. |
| ownership | The callable and strings are borrowed for the call; exception owns its message per API. |
| failure | A caught crown::Error with the wrong code triggers check and constructs a new std::runtime_error. No throw also produces std::runtime_error; exceptions of other types propagate. |
| cost | Invokes action once and branches on exception; caller-side context/message string construction is eager. |
| Design | [tests/unit/candidates_test.cpp](../../../../../tests/unit/candidates_test.cpp), [CMakeLists.txt](../../../../../CMakeLists.txt), [include/crown/planner/candidates.hpp](../../../../../include/crown/planner/candidates.hpp), [include/crown/planner/search.hpp](../../../../../include/crown/planner/search.hpp), [src/planner/candidates.cpp](../../../../../src/planner/candidates.cpp), [docs/planner_continuations.md](../../../../planner_continuations.md) |

## B0065

[Lines 962–970](../../../../../tests/unit/candidates_test.cpp#L962); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void require_candidate_dump_rejected(const io::Json& document, const std::string& context) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Assert that JSON DOM text encoding rejects invalid UTF-8 rather than replacing bytes. |
| inputs / outputs | Inputs are JSON DOM and context; calls document.dump(). |
| invariants | Any std::exception means rejection; DOM is only passed as const and this helper checks no exact exception subtype. |
| ownership | DOM and context remain caller-owned. dump() can allocate temporary encoding buffers before either success or rejection; no text result is retained by this helper. |
| failure | If dump succeeds, throws runtime_error; dump exceptions are swallowed as expected. |
| cost | Attempts full DOM serialization and may allocate while encoding; failure is the expected result in invalid-byte cases. |
| Design | [tests/unit/candidates_test.cpp](../../../../../tests/unit/candidates_test.cpp), [CMakeLists.txt](../../../../../CMakeLists.txt), [include/crown/planner/candidates.hpp](../../../../../include/crown/planner/candidates.hpp), [include/crown/planner/search.hpp](../../../../../include/crown/planner/search.hpp), [src/planner/candidates.cpp](../../../../../src/planner/candidates.cpp), [docs/planner_continuations.md](../../../../planner_continuations.md) |

## B0067

[Lines 972–1169](../../../../../tests/unit/candidates_test.cpp#L972); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void arbitrary_string_binding_domain() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Exercise candidate proof, structural key, exact-binding cache and JSON behavior for arbitrary string bytes. |
| inputs / outputs | No inputs; constructs invalid UTF-8 and NUL constants/identifiers, proves singleton cases, creates providers/cache, mutates identifiers, serializes progress/candidate DOMs and obtains a residual seed. |
| invariants | The exact-search proof binding and candidate APIs retain the tested arbitrary bytes; P02 validates the associated tree against its binding. Same tree shape has equal local keys across five constant bindings, while exact cache distinguishes their bytes. Report DOM retains raw bytes before text dump rejects them. After failed progress dump the test compares phase, last_stop, work, candidate_count, records and cells; candidate dump is followed by checked validity/height assertions. Changed alias rejects residual/cached prefix. |
| ownership | Proofs, providers, cache, DOMs, candidate and residual seed own or retain binding data; handles are tested after serialization attempts. |
| failure | Typed candidate_binding errors are required for mismatched cached/residual prefixes; JSON dump rejection is required; any byte normalization, stale mutation, or invalid proof throws. |
| cost | Runs several P06 searches, complete singleton providers, exact cache lookups, mutations, P05 and P02 checks; loops allocate strings/DOMs. Failure counters are assertions, not a byte/CPU ceiling. |
| Design | [tests/unit/candidates_test.cpp](../../../../../tests/unit/candidates_test.cpp), [CMakeLists.txt](../../../../../CMakeLists.txt), [include/crown/planner/candidates.hpp](../../../../../include/crown/planner/candidates.hpp), [include/crown/planner/search.hpp](../../../../../include/crown/planner/search.hpp), [src/planner/candidates.cpp](../../../../../src/planner/candidates.cpp), [docs/planner_continuations.md](../../../../planner_continuations.md), [src/planner/candidate_binding.hpp](../../../../../src/planner/candidate_binding.hpp), [src/planner/residual.cpp](../../../../../src/planner/residual.cpp), [include/crown/io/candidates.hpp](../../../../../include/crown/io/candidates.hpp), [include/crown/io/search.hpp](../../../../../include/crown/io/search.hpp), [include/crown/planner/verify.hpp](../../../../../include/crown/planner/verify.hpp) |

## B0068

[Lines 1170–1172](../../../../../tests/unit/candidates_test.cpp#L1170); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L1170-L1172:sha256:9e375a3cb3a2cbe2f9ded9c8296a6ab66848cc826fd71f919246acb17e0bd455
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Close the recorded declaration scopes in candidates_test.cpp: namespace (anonymous). |
| inputs / outputs | Preceding namespace, type or initializer declarations in; completed lexical boundary out. |
| invariants | Brace-opening context is recorded in root-scope-context-v1.json. These are declaration/initializer boundaries, not an independent update, validation or recovery operation. |
| ownership | Enclosing objects and borrowed fields keep their declared ownership. This punctuation creates no new owner. |
| failure | Malformed scope syntax is a compile error. Any initializer/constructor failure belongs to the enclosing object declaration. |
| cost | No separate loop, guard or engine call is introduced by the delimiter; enclosing initialization and object lifetime still have their actual costs. |
| Design | [tests/unit/candidates_test.cpp](../../../../../tests/unit/candidates_test.cpp), [docs/candidate_alternatives.md](../../../../candidate_alternatives.md), [docs/code_review.md](../../../../code_review.md) |

## B0069

[Lines 1173–1192](../../../../../tests/unit/candidates_test.cpp#L1173); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
int main(int argc, char** argv) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Run the candidate suite against the copied tests/candidates fixture directory. |
| inputs / outputs | Requires exactly one command-line path after program name; returns process status 0 on success. |
| invariants | Calls nine groups in source order: independent_reference_caps_are_incomplete, exhaustive_three_atom_family, fixture_cases_and_slicing, structural_key_and_non_normal_witness, resource_limits_and_lifetimes, exact_binding_cache_fences, residual_source_and_cached_provenance, mandatory_residual_and_wide_seed_boundaries, and arbitrary_string_binding_domain. Success output follows only after all return. |
| ownership | argc/argv borrowed; each called test owns its temporary objects. |
| failure | Wrong argc and standard setup/assertion failures reach the outer std::exception handler, which prints the message and returns 1. Exceptions outside that hierarchy are not caught here. |
| cost | Executes the listed finite test workloads, including repeated planner proofs and provider continuations; this entry records source call order, not a native test run. |
| Design | [tests/unit/candidates_test.cpp](../../../../../tests/unit/candidates_test.cpp), [CMakeLists.txt](../../../../../CMakeLists.txt), [include/crown/planner/candidates.hpp](../../../../../include/crown/planner/candidates.hpp), [include/crown/planner/search.hpp](../../../../../include/crown/planner/search.hpp), [src/planner/candidates.cpp](../../../../../src/planner/candidates.cpp), [docs/planner_continuations.md](../../../../planner_continuations.md) |
