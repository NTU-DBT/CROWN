# `tests/unit/planner_fast_paths_test.cpp` — block usage map

[Source](../../../../../tests/unit/planner_fast_paths_test.cpp) · [Source index](../../../README.md) · [Subsystem contracts](../../../subsystem_contracts.md) · [Reviewed primitives](../../../primitives.md)

Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection.

Snapshot SHA-256: `16b3d88792542db6764fea42a78be8ed838c77d263d08c53eb13767ca7ca300f`. 642 lines partitioned into 55 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [tests](../../../subsystem_contracts.md#tests). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/code_review.md](../../../../code_review.md), [docs/reference_fuzz.md](../../../../reference_fuzz.md), [docs/task_ledger.md](../../../../task_ledger.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–24](../../../../../tests/unit/planner_fast_paths_test.cpp#L1) | Imports dependencies; declares namespace scope; declares aliases. |  · [reviewed contract](#b0001) |
| [B0002 · 25–27](../../../../../tests/unit/planner_fast_paths_test.cpp#L25) | Callable definition: void check(bool condition, const std::string& message) | calls std::runtime_error; guard void check(bool condition, const std::string& message) { · [reviewed contract](#b0002) |
| [B0003 · 28–28](../../../../../tests/unit/planner_fast_paths_test.cpp#L28) | Explanatory comments or spacing. |  |
| [B0004 · 29–29](../../../../../tests/unit/planner_fast_paths_test.cpp#L29) | Type/record definition: struct VarRef |  · [reviewed contract](#b0004) |
| [B0005 · 30–30](../../../../../tests/unit/planner_fast_paths_test.cpp#L30) | Type/record definition: struct Ignored |  · [reviewed contract](#b0005) |
| [B0006 · 31–33](../../../../../tests/unit/planner_fast_paths_test.cpp#L31) | declares aliases; declares values/defaults or compile-time conditions. |  · [reviewed contract](#b0006) |
| [B0007 · 34–37](../../../../../tests/unit/planner_fast_paths_test.cpp#L34) | Type/record definition: struct Fixture |  · [reviewed contract](#b0007) |
| [B0008 · 38–38](../../../../../tests/unit/planner_fast_paths_test.cpp#L38) | Explanatory comments or spacing. |  |
| [B0009 · 39–39](../../../../../tests/unit/planner_fast_paths_test.cpp#L39) | Callable definition: Slot v(std::size_t value) | calls ; returns VarRef{value} · [reviewed contract](#b0009) |
| [B0010 · 40–40](../../../../../tests/unit/planner_fast_paths_test.cpp#L40) | Callable definition: Slot c(std::int64_t value) | calls ; returns value · [reviewed contract](#b0010) |
| [B0011 · 41–41](../../../../../tests/unit/planner_fast_paths_test.cpp#L41) | Callable definition: Slot ignored() | calls ; returns Ignored{} · [reviewed contract](#b0011) |
| [B0012 · 42–42](../../../../../tests/unit/planner_fast_paths_test.cpp#L42) | Explanatory comments or spacing. |  |
| [B0013 · 43–77](../../../../../tests/unit/planner_fast_paths_test.cpp#L43) | Callable definition: Fixture fixture_for(const std::vector&lt;Occurrence&gt;& occurrences, const std::vector&lt;std::size_t&gt;& head, bool contradiction = false) | calls insert, begin, end, size; returns fixture; growth emplace, emplace_back, insert, push_back; 6 loop sites · [reviewed contract](#b0013) |
| [B0014 · 78–78](../../../../../tests/unit/planner_fast_paths_test.cpp#L78) | Explanatory comments or spacing. |  |
| [B0015 · 79–91](../../../../../tests/unit/planner_fast_paths_test.cpp#L79) | Callable definition: Fixture scoped_fixture(const std::vector&lt;std::vector&lt;std::size_t&gt;&gt;& scopes, const std::vector&lt;std::size_t&gt;& head, bool contradict… | calls reserve, size, push_back, v; returns fixture_for(occurrences, head, contradiction); growth push_back, reserve; 2 loop sites · [reviewed contract](#b0015) |
| [B0016 · 92–92](../../../../../tests/unit/planner_fast_paths_test.cpp#L92) | Explanatory comments or spacing. |  |
| [B0017 · 93–101](../../../../../tests/unit/planner_fast_paths_test.cpp#L93) | Callable definition: std::vector&lt;std::set&lt;std::size_t&gt;&gt; native_scopes(const Query& query) | calls scopes, size, insert; returns scopes; growth insert; 2 loop sites · [reviewed contract](#b0017) |
| [B0018 · 102–102](../../../../../tests/unit/planner_fast_paths_test.cpp#L102) | Explanatory comments or spacing. |  |
| [B0019 · 103–105](../../../../../tests/unit/planner_fast_paths_test.cpp#L103) | Callable definition: bool proper_subset(const std::set&lt;std::size_t&gt;& left, const std::set&lt;std::size_t&gt;& right) | calls size, std::includes, begin, end; returns left.size() &lt; right.size() && std::includes(right.begin(), right.end(), left.begin(), left.end()) · [reviewed contract](#b0019) |
| [B0020 · 106–108](../../../../../tests/unit/planner_fast_paths_test.cpp#L106) | Explanatory comments or spacing. | source comment (unverified): // Independent implementation of the incidence-set definition in the P04 · [reviewed contract](#b0020) |
| [B0021 · 109–130](../../../../../tests/unit/planner_fast_paths_test.cpp#L109) | Callable definition: bool independently_q_hierarchical(const Query& query) | calls native_scopes, incidence, size, insert; returns b.contains(occurrence); false; growth insert; 5 loop sites; source comment (unverified): // Independent implementation of the incidence-set definition in the P04 · [reviewed contract](#b0021) |
| [B0022 · 131–131](../../../../../tests/unit/planner_fast_paths_test.cpp#L131) | Explanatory comments or spacing. |  |
| [B0023 · 132–134](../../../../../tests/unit/planner_fast_paths_test.cpp#L132) | Callable definition: planner::HeightCertificate certificate_of(const planner::OracleResult& result) | calls ; returns {result.algorithm, result.minimum_height, result.tree, result.lower_bounds} · [reviewed contract](#b0023) |
| [B0024 · 135–135](../../../../../tests/unit/planner_fast_paths_test.cpp#L135) | Explanatory comments or spacing. |  |
| [B0025 · 136–149](../../../../../tests/unit/planner_fast_paths_test.cpp#L136) | Callable definition: void check_native_occurrences_once(const Fixture& fixture, const FreeConnexTree& tree, const std::string& context) | calls check, has_value, push_back, std::sort; guard check(node.occurrence.has_value(), context + ": native node lost its occurrence id");; growth push_back; 1 loop sites · [reviewed contract](#b0025) |
| [B0026 · 150–150](../../../../../tests/unit/planner_fast_paths_test.cpp#L150) | Explanatory comments or spacing. |  |
| [B0027 · 151–164](../../../../../tests/unit/planner_fast_paths_test.cpp#L151) | Callable definition: planner::OracleResult require_minimum(const Fixture& fixture, std::size_t expected, const planner::SearchLimits& limits = {}, con… | calls planner::minimum_tree, check, has_value, planner::validate_tree; guard check(result.status == planner::OracleStatus::proven_minimum, context + ": optimized search did not…; returns result · [reviewed contract](#b0027) |
| [B0028 · 165–165](../../../../../tests/unit/planner_fast_paths_test.cpp#L165) | Explanatory comments or spacing. |  |
| [B0029 · 166–186](../../../../../tests/unit/planner_fast_paths_test.cpp#L166) | Callable definition: void compare_all_three(const Fixture& fixture, const std::string& context) | calls planner::minimum_tree, planner::testing::minimum_tree_baseline, reference::exhaustive_minimum_tree, check; guard check(optimized.status != planner::OracleStatus::resource_limit && · [reviewed contract](#b0029) |
| [B0030 · 187–187](../../../../../tests/unit/planner_fast_paths_test.cpp#L187) | Explanatory comments or spacing. |  |
| [B0031 · 188–261](../../../../../tests/unit/planner_fast_paths_test.cpp#L188) | Callable definition: void exhaustive_small_differential_and_hierarchy_predicate() | calls scopes, push_back, insert, contains; guard check(optimized.status != planner::OracleStatus::resource_limit &&; growth insert, push_back; 8 loop sites · [reviewed contract](#b0031) |
| [B0032 · 262–262](../../../../../tests/unit/planner_fast_paths_test.cpp#L262) | Explanatory comments or spacing. |  |
| [B0033 · 263–265](../../../../../tests/unit/planner_fast_paths_test.cpp#L263) | Callable definition: std::vector&lt;std::vector&lt;std::size_t&gt;&gt; seven_atom_residual_scopes() | calls ; returns {{0, 1, 2, 3}, {0, 1, 2, 4}, {3}, {4}, {1, 5}, {5}, {0, 6}} · [reviewed contract](#b0033) |
| [B0034 · 266–266](../../../../../tests/unit/planner_fast_paths_test.cpp#L266) | Explanatory comments or spacing. |  |
| [B0035 · 267–270](../../../../../tests/unit/planner_fast_paths_test.cpp#L267) | Callable definition: std::vector&lt;std::vector&lt;std::size_t&gt;&gt; nine_atom_residual_scopes() | calls ; returns {{0, 1, 2, 3}, {0, 1, 2, 4}, {3}, {4}, · [reviewed contract](#b0035) |
| [B0036 · 271–271](../../../../../tests/unit/planner_fast_paths_test.cpp#L271) | Explanatory comments or spacing. |  |
| [B0037 · 272–293](../../../../../tests/unit/planner_fast_paths_test.cpp#L272) | Callable definition: Fixture disjoint_components(const std::vector&lt;std::pair&lt;std::vector&lt;std::vector&lt;std::size_t&gt;&gt;, std::vector&lt;std::size_t&gt;&gt;&gt;& compon… | calls at, std::max, push_back, std::move; returns scoped_fixture(scopes, head); growth push_back; 7 loop sites · [reviewed contract](#b0037) |
| [B0038 · 294–294](../../../../../tests/unit/planner_fast_paths_test.cpp#L294) | Explanatory comments or spacing. |  |
| [B0039 · 295–311](../../../../../tests/unit/planner_fast_paths_test.cpp#L295) | Callable definition: Fixture permuted_scopes(const std::vector&lt;std::vector&lt;std::size_t&gt;&gt;& scopes, const std::vector&lt;std::size_t&gt;& head, const std::vec… | calls reserve, size, at, std::sort; returns scoped_fixture(permuted, mapped_head); growth push_back, reserve; 3 loop sites · [reviewed contract](#b0039) |
| [B0040 · 312–312](../../../../../tests/unit/planner_fast_paths_test.cpp#L312) | Explanatory comments or spacing. |  |
| [B0041 · 313–361](../../../../../tests/unit/planner_fast_paths_test.cpp#L313) | Callable definition: void singleton_empty_and_structural_semantics() | calls scoped_fixture, require_minimum, check, at; guard check(true_result.statistics.empty_body_hits &gt; 0, "empty body did not use its dedicated path"); · [reviewed contract](#b0041) |
| [B0042 · 362–362](../../../../../tests/unit/planner_fast_paths_test.cpp#L362) | Explanatory comments or spacing. |  |
| [B0043 · 363–396](../../../../../tests/unit/planner_fast_paths_test.cpp#L363) | Callable definition: void fast_path_statistics_and_components() | calls scoped_fixture, check, independently_q_hierarchical, require_minimum; guard check(!independently_q_hierarchical(duplicate_scopes.query), "symmetry witness should not pass hier… · [reviewed contract](#b0043) |
| [B0044 · 397–397](../../../../../tests/unit/planner_fast_paths_test.cpp#L397) | Explanatory comments or spacing. |  |
| [B0045 · 398–410](../../../../../tests/unit/planner_fast_paths_test.cpp#L398) | Callable definition: void residual_counterexamples_and_branch_bound() | calls scoped_fixture, seven_atom_residual_scopes, require_minimum, check; guard check(seven_result.statistics.bound_prunes &gt; 0, · [reviewed contract](#b0045) |
| [B0046 · 411–411](../../../../../tests/unit/planner_fast_paths_test.cpp#L411) | Explanatory comments or spacing. |  |
| [B0047 · 412–458](../../../../../tests/unit/planner_fast_paths_test.cpp#L412) | Callable definition: void large_dynamic_representations() | calls push_back, scoped_fixture, require_minimum, check; guard check(singletons.query.variables.size() &gt; 64 && singletons.query.atoms.size() &gt; 64,; returns node.kind == NodeKind::generalized; growth push_back; 4 loop sites · [reviewed contract](#b0047) |
| [B0048 · 459–459](../../../../../tests/unit/planner_fast_paths_test.cpp#L459) | Explanatory comments or spacing. |  |
| [B0049 · 460–469](../../../../../tests/unit/planner_fast_paths_test.cpp#L460) | Callable definition: std::optional&lt;std::size_t&gt; find_bound(std::vector&lt;planner::LowerBoundEntry&gt;& entries, const std::vector&lt;std::size_t&gt;& occurrences… | calls std::find_if, begin, end, std::distance; returns entry.occurrences == occurrences && entry.generalized_allowed == generalized_allowed &&; std::nullo… · [reviewed contract](#b0049) |
| [B0050 · 470–470](../../../../../tests/unit/planner_fast_paths_test.cpp#L470) | Explanatory comments or spacing. |  |
| [B0051 · 471–592](../../../../../tests/unit/planner_fast_paths_test.cpp#L471) | Callable definition: void certificate_malformations() | calls scoped_fixture, require_minimum, certificate_of, std::find_if; guard check(orbit_entry != bad.lower_bounds.end(), "symmetry proof did not expose a one-member equal-scop…; returns zero + one == 1; left.occurrences.size() &lt; right.occurrences.size(); growth push_back; 1 loop sites; source comment (unverified): // The full query gives the two repeated {x,y} occurrences a global · [reviewed contract](#b0051) |
| [B0052 · 593–593](../../../../../tests/unit/planner_fast_paths_test.cpp#L593) | Explanatory comments or spacing. |  |
| [B0053 · 594–623](../../../../../tests/unit/planner_fast_paths_test.cpp#L594) | Callable definition: void budget_exhaustion_stays_explicit() | calls scoped_fixture, planner::minimum_tree, check, empty; guard check(no_work.status == planner::OracleStatus::resource_limit && !no_work.minimum_height && !no_wor… · [reviewed contract](#b0053) |
| [B0054 · 624–626](../../../../../tests/unit/planner_fast_paths_test.cpp#L624) | Closes surrounding scope/type. | source comment (unverified): // namespace · [reviewed contract](#b0054) |
| [B0055 · 627–642](../../../../../tests/unit/planner_fast_paths_test.cpp#L627) | Callable definition: int main() | calls exhaustive_small_differential_and_hierarchy_predicate, singleton_empty_and_structural_semantics, fast_path_statistics_and_components, residual_counterexamples_and_branch_bound; returns 0; 1 · [reviewed contract](#b0055) |

## B0001

[Lines 1–24](../../../../../tests/unit/planner_fast_paths_test.cpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L1-L24:sha256:9fc6108df836179bbd1d1f597854ee8bc71919c753b7b6aed9aacc2b63869093
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Prepare planner_fast_paths_test.cpp: include "crown/planner/oracle.hpp", "crown/planner/verify.hpp", "planner_probe.hpp", "tree_oracle.hpp", &lt;algorithm&gt;, &lt;chrono&gt;, &lt;cstddef&gt;, &lt;iostream&gt;, &lt;iterator&gt;, &lt;map&gt;, &lt;numeric&gt;, &lt;optional&gt;, &lt;set&gt;, &lt;stdexcept&gt;, &lt;string&gt;, &lt;tuple&gt;, &lt;utility&gt;, &lt;variant&gt;, &lt;vector&gt;; bind local aliases/name imports. |
| inputs / outputs | Compiler-visible dependencies, names and the recorded declarations in; declarations available to the following fixture/CLI/example definitions out. |
| invariants | Declarations are scoped to this source/header and its selected ABI. Included code has its own effects; names and editable fixture values do not confer proof, admission or publication authority. |
| ownership | Aliases/includes do not create a query owner. Pointers/references/views are non-owning. Containers own their elements, which can themselves be borrowed pointers or numeric IDs. Only documented owning shared-control handles retain controls; IDs/slot-handle values do not independently keep an arena/runtime alive. |
| failure | Missing headers, ill-formed names/types, failed static assertions or active #error directives stop compilation. No runtime rejection/rollback mechanism is implemented by aliases or function prototypes. |
| cost | Preprocessing and type/constraint instantiation cost compilation. Alias/prototype syntax does not invoke the declared operation; any included definitions keep their own initialization effects. |
| Design | [tests/unit/planner_fast_paths_test.cpp](../../../../../tests/unit/planner_fast_paths_test.cpp), [docs/planner_continuations.md](../../../../planner_continuations.md), [docs/code_review.md](../../../../code_review.md) |

## B0002

[Lines 25–27](../../../../../tests/unit/planner_fast_paths_test.cpp#L25); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void check(bool condition, const std::string& message) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Provide the fast-path suite assertion primitive. |
| inputs / outputs | Inputs are Boolean predicate and caller-supplied diagnostic std::string; output is normal return when true. |
| invariants | False predicate throws std::runtime_error carrying message; true returns. |
| ownership | The caller constructs message before entry; helper retains no state. |
| failure | False condition throws; message expressions are evaluated even on success. |
| cost | Body is one branch and optional exception construction; caller-side string work is outside that body. |
| Design | [tests/unit/planner_fast_paths_test.cpp](../../../../../tests/unit/planner_fast_paths_test.cpp), [CMakeLists.txt](../../../../../CMakeLists.txt), [include/crown/planner/oracle.hpp](../../../../../include/crown/planner/oracle.hpp), [src/planner/exact.cpp](../../../../../src/planner/exact.cpp), [tests/support/planner_exact_baseline.cpp](../../../../../tests/support/planner_exact_baseline.cpp), [tests/reference/tree_oracle.cpp](../../../../../tests/reference/tree_oracle.cpp), [docs/planner_proofs.md](../../../../planner_proofs.md) |

## B0004

[Lines 29–29](../../../../../tests/unit/planner_fast_paths_test.cpp#L29); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct VarRef { std::size_t value; };
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Represent a named variable reference in synthetic atom slots. |
| inputs / outputs | One size_t variable label is stored. |
| invariants | fixture_for resolves the label through its dense-name map. |
| ownership | Value-owned scalar wrapper. |
| failure | Missing label during fixture construction fails map::at. |
| cost | No meaningful runtime cost beyond storing one integer. |
| Design | [tests/unit/planner_fast_paths_test.cpp](../../../../../tests/unit/planner_fast_paths_test.cpp), [CMakeLists.txt](../../../../../CMakeLists.txt), [include/crown/planner/oracle.hpp](../../../../../include/crown/planner/oracle.hpp), [src/planner/exact.cpp](../../../../../src/planner/exact.cpp), [tests/support/planner_exact_baseline.cpp](../../../../../tests/support/planner_exact_baseline.cpp), [tests/reference/tree_oracle.cpp](../../../../../tests/reference/tree_oracle.cpp), [docs/planner_proofs.md](../../../../planner_proofs.md) |

## B0005

[Lines 30–30](../../../../../tests/unit/planner_fast_paths_test.cpp#L30); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct Ignored {};
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Represent an ignored atom column in synthetic fixtures. |
| inputs / outputs | No fields or inputs. |
| invariants | fixture_for converts this alternative to IgnoredColumn and excludes it from native variable scopes. |
| ownership | Empty value type. |
| failure | No standalone failure path. |
| cost | No meaningful work beyond variant storage/tag handling. |
| Design | [tests/unit/planner_fast_paths_test.cpp](../../../../../tests/unit/planner_fast_paths_test.cpp), [CMakeLists.txt](../../../../../CMakeLists.txt), [include/crown/planner/oracle.hpp](../../../../../include/crown/planner/oracle.hpp), [src/planner/exact.cpp](../../../../../src/planner/exact.cpp), [tests/support/planner_exact_baseline.cpp](../../../../../tests/support/planner_exact_baseline.cpp), [tests/reference/tree_oracle.cpp](../../../../../tests/reference/tree_oracle.cpp), [docs/planner_proofs.md](../../../../planner_proofs.md) |

## B0006

[Lines 31–33](../../../../../tests/unit/planner_fast_paths_test.cpp#L31); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L31-L33:sha256:33c7737eda6a7b3e247d482beaf92d3725c706f0c12765073ff4216765b6bc93
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Prepare planner_fast_paths_test.cpp: bind local aliases/name imports. |
| inputs / outputs | Compiler-visible dependencies, names and the recorded declarations in; declarations available to the following fixture/CLI/example definitions out. |
| invariants | Declarations are scoped to this source/header and its selected ABI. Included code has its own effects; names and editable fixture values do not confer proof, admission or publication authority. |
| ownership | Aliases/includes do not create a query owner. Pointers/references/views are non-owning. Containers own their elements, which can themselves be borrowed pointers or numeric IDs. Only documented owning shared-control handles retain controls; IDs/slot-handle values do not independently keep an arena/runtime alive. |
| failure | Missing headers, ill-formed names/types, failed static assertions or active #error directives stop compilation. No runtime rejection/rollback mechanism is implemented by aliases or function prototypes. |
| cost | Preprocessing and type/constraint instantiation cost compilation. Alias/prototype syntax does not invoke the declared operation; any included definitions keep their own initialization effects. |
| Design | [tests/unit/planner_fast_paths_test.cpp](../../../../../tests/unit/planner_fast_paths_test.cpp), [docs/planner_continuations.md](../../../../planner_continuations.md), [docs/code_review.md](../../../../code_review.md) |

## B0007

[Lines 34–37](../../../../../tests/unit/planner_fast_paths_test.cpp#L34); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct Fixture {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Own the catalog/query pair built by the fast-path test helpers. |
| inputs / outputs | Fields are Catalog and Query values. |
| invariants | Synthetic bindings are used as inputs to planner/oracle APIs; fixture_for preserves the passed contradiction flag. |
| ownership | Owns its containers and names; no source references retained. |
| failure | Downstream validation/search may reject malformed fixture input. |
| cost | Plain fixture storage; vector/string setup costs belong to builders. |
| Design | [tests/unit/planner_fast_paths_test.cpp](../../../../../tests/unit/planner_fast_paths_test.cpp), [CMakeLists.txt](../../../../../CMakeLists.txt), [include/crown/planner/oracle.hpp](../../../../../include/crown/planner/oracle.hpp), [src/planner/exact.cpp](../../../../../src/planner/exact.cpp), [tests/support/planner_exact_baseline.cpp](../../../../../tests/support/planner_exact_baseline.cpp), [tests/reference/tree_oracle.cpp](../../../../../tests/reference/tree_oracle.cpp), [docs/planner_proofs.md](../../../../planner_proofs.md) |

## B0009

[Lines 39–39](../../../../../tests/unit/planner_fast_paths_test.cpp#L39); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Slot v(std::size_t value) { return VarRef{value}; }
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Wrap a variable label as a Slot variant. |
| inputs / outputs | Input size_t; output VarRef alternative. |
| invariants | Does not allocate or resolve a VariableId until fixture_for. |
| ownership | Returns value-owned variant. |
| failure | No helper-level failure. |
| cost | Small variant construction. |
| Design | [tests/unit/planner_fast_paths_test.cpp](../../../../../tests/unit/planner_fast_paths_test.cpp), [CMakeLists.txt](../../../../../CMakeLists.txt), [include/crown/planner/oracle.hpp](../../../../../include/crown/planner/oracle.hpp), [src/planner/exact.cpp](../../../../../src/planner/exact.cpp), [tests/support/planner_exact_baseline.cpp](../../../../../tests/support/planner_exact_baseline.cpp), [tests/reference/tree_oracle.cpp](../../../../../tests/reference/tree_oracle.cpp), [docs/planner_proofs.md](../../../../planner_proofs.md) |

## B0010

[Lines 40–40](../../../../../tests/unit/planner_fast_paths_test.cpp#L40); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Slot c(std::int64_t value) { return value; }
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Wrap an int64 constant as a Slot variant. |
| inputs / outputs | Input int64_t; output integer alternative. |
| invariants | fixture_for materializes it as a typed Value constant and not as an incidence variable. |
| ownership | Returns value-owned variant. |
| failure | No helper-level failure. |
| cost | Small variant construction. |
| Design | [tests/unit/planner_fast_paths_test.cpp](../../../../../tests/unit/planner_fast_paths_test.cpp), [CMakeLists.txt](../../../../../CMakeLists.txt), [include/crown/planner/oracle.hpp](../../../../../include/crown/planner/oracle.hpp), [src/planner/exact.cpp](../../../../../src/planner/exact.cpp), [tests/support/planner_exact_baseline.cpp](../../../../../tests/support/planner_exact_baseline.cpp), [tests/reference/tree_oracle.cpp](../../../../../tests/reference/tree_oracle.cpp), [docs/planner_proofs.md](../../../../planner_proofs.md) |

## B0011

[Lines 41–41](../../../../../tests/unit/planner_fast_paths_test.cpp#L41); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Slot ignored() { return Ignored{}; }
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Create the ignored-column Slot alternative. |
| inputs / outputs | No inputs; output Ignored alternative. |
| invariants | Ignored slots become IgnoredColumn terms and are absent from variable incidence sets. |
| ownership | Returns value-owned variant. |
| failure | No helper-level failure. |
| cost | Small variant construction. |
| Design | [tests/unit/planner_fast_paths_test.cpp](../../../../../tests/unit/planner_fast_paths_test.cpp), [CMakeLists.txt](../../../../../CMakeLists.txt), [include/crown/planner/oracle.hpp](../../../../../include/crown/planner/oracle.hpp), [src/planner/exact.cpp](../../../../../src/planner/exact.cpp), [tests/support/planner_exact_baseline.cpp](../../../../../tests/support/planner_exact_baseline.cpp), [tests/reference/tree_oracle.cpp](../../../../../tests/reference/tree_oracle.cpp), [docs/planner_proofs.md](../../../../planner_proofs.md) |

## B0013

[Lines 43–77](../../../../../tests/unit/planner_fast_paths_test.cpp#L43); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Fixture fixture_for(const std::vector<Occurrence>& occurrences,
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Build a synthetic catalog/query from ordered occurrence slots and a head. |
| inputs / outputs | Inputs are occurrence vectors, head labels and contradiction flag; output assigns dense VariableIds, creates typed int64 tables/atoms and binds variables/constants/ignored terms. |
| invariants | Occurrence/table IDs preserve input order; repeated variable slots remain repeated terms; only distinct labels define query.variables; head order is preserved; contradiction copied verbatim. |
| ownership | Returned Fixture owns all generated containers and strings. |
| failure | Head/scope label lookup uses map::at; this helper does not call validate. |
| cost | Walks every slot/head, builds maps and appends catalog/query vectors; proportional to supplied fixture plus allocations. |
| Design | [tests/unit/planner_fast_paths_test.cpp](../../../../../tests/unit/planner_fast_paths_test.cpp), [CMakeLists.txt](../../../../../CMakeLists.txt), [include/crown/planner/oracle.hpp](../../../../../include/crown/planner/oracle.hpp), [src/planner/exact.cpp](../../../../../src/planner/exact.cpp), [tests/support/planner_exact_baseline.cpp](../../../../../tests/support/planner_exact_baseline.cpp), [tests/reference/tree_oracle.cpp](../../../../../tests/reference/tree_oracle.cpp), [docs/planner_proofs.md](../../../../planner_proofs.md) |

## B0015

[Lines 79–91](../../../../../tests/unit/planner_fast_paths_test.cpp#L79); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Fixture scoped_fixture(const std::vector<std::vector<std::size_t>>& scopes,
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Convert pure variable-scope lists into slot occurrences and delegate fixture construction. |
| inputs / outputs | Inputs are occurrence scopes, head and contradiction; output is fixture_for over each scope mapped through v(). |
| invariants | All scope entries become variable terms; no constants/ignored positions are introduced. |
| ownership | Returned Fixture owns generated query/catalog. |
| failure | Downstream map lookups or API validation may fail for invalid labels. |
| cost | Allocates an intermediate occurrence vector and one slot per scope variable before fixture_for rebuilds binding. |
| Design | [tests/unit/planner_fast_paths_test.cpp](../../../../../tests/unit/planner_fast_paths_test.cpp), [CMakeLists.txt](../../../../../CMakeLists.txt), [include/crown/planner/oracle.hpp](../../../../../include/crown/planner/oracle.hpp), [src/planner/exact.cpp](../../../../../src/planner/exact.cpp), [tests/support/planner_exact_baseline.cpp](../../../../../tests/support/planner_exact_baseline.cpp), [tests/reference/tree_oracle.cpp](../../../../../tests/reference/tree_oracle.cpp), [docs/planner_proofs.md](../../../../planner_proofs.md) |

## B0017

[Lines 93–101](../../../../../tests/unit/planner_fast_paths_test.cpp#L93); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::vector<std::set<std::size_t>> native_scopes(const Query& query) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Project each atom occurrence to its set of distinct native variable IDs for independent test predicates. |
| inputs / outputs | Input Query; output vector of sets in atom order. |
| invariants | Only VariableId terms are inserted; constants/ignored terms are omitted; occurrence slots remain distinct even for equal sets. |
| ownership | Returns owned sets; query borrowed. |
| failure | No explicit validation; malformed IDs are just numeric labels here. |
| cost | Visits every atom term and inserts into ordered sets; duplicates within a term list collapse and each set may allocate. |
| Design | [tests/unit/planner_fast_paths_test.cpp](../../../../../tests/unit/planner_fast_paths_test.cpp), [CMakeLists.txt](../../../../../CMakeLists.txt), [include/crown/planner/oracle.hpp](../../../../../include/crown/planner/oracle.hpp), [src/planner/exact.cpp](../../../../../src/planner/exact.cpp), [tests/support/planner_exact_baseline.cpp](../../../../../tests/support/planner_exact_baseline.cpp), [tests/reference/tree_oracle.cpp](../../../../../tests/reference/tree_oracle.cpp), [docs/planner_proofs.md](../../../../planner_proofs.md) |

## B0019

[Lines 103–105](../../../../../tests/unit/planner_fast_paths_test.cpp#L103); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
bool proper_subset(const std::set<std::size_t>& left, const std::set<std::size_t>& right) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Test strict set containment for incidence-set hierarchy checks. |
| inputs / outputs | Inputs sorted sets left/right; output true iff left is smaller and included in right. |
| invariants | Equality is not a proper subset; std::includes assumes set iteration order. |
| ownership | Inputs borrowed. |
| failure | No explicit failure path. |
| cost | Size check plus standard linear include comparison over ordered sets. |
| Design | [tests/unit/planner_fast_paths_test.cpp](../../../../../tests/unit/planner_fast_paths_test.cpp), [CMakeLists.txt](../../../../../CMakeLists.txt), [include/crown/planner/oracle.hpp](../../../../../include/crown/planner/oracle.hpp), [src/planner/exact.cpp](../../../../../src/planner/exact.cpp), [tests/support/planner_exact_baseline.cpp](../../../../../tests/support/planner_exact_baseline.cpp), [tests/reference/tree_oracle.cpp](../../../../../tests/reference/tree_oracle.cpp), [docs/planner_proofs.md](../../../../planner_proofs.md) |

## B0020

[Lines 106–108](../../../../../tests/unit/planner_fast_paths_test.cpp#L106); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L106-L108:sha256:0b5391148028da72b29b0afbb86f306b85ff8c6cbd9a8a67827458ef59be6fa8
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Explain the adjacent source contract: Independent implementation of the incidence-set definition in the P04 preflight. Occurrences are indices, so duplicate native scopes stay distinct. |
| inputs / outputs | Human-readable source note in; no executable output or checked receipt. |
| invariants | This comment states context or a limitation. It does not itself enforce or prove the described behavior; use the adjacent implementation and its scoped contract. |
| ownership | Source text only; no object or resource lifetime is created. |
| failure | No runtime failure path in this comment; source encoding/comment syntax still belongs to compilation. |
| cost | No runtime operations from the comment. Any work described in the note belongs to the adjacent operation. |
| Design | [tests/unit/planner_fast_paths_test.cpp](../../../../../tests/unit/planner_fast_paths_test.cpp), [docs/planner_continuations.md](../../../../planner_continuations.md), [docs/code_review.md](../../../../code_review.md) |

## B0021

[Lines 109–130](../../../../../tests/unit/planner_fast_paths_test.cpp#L109); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
bool independently_q_hierarchical(const Query& query) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Independently evaluate the P04 q-hierarchical incidence-set and free-variable closure predicate. |
| inputs / outputs | Input is a Query whose atom-term and head VariableId values are within query.variables; output is Boolean from pairwise occurrence-incidence and head-membership checks. The helper does not validate the Query. |
| invariants | Incidence elements are occurrence indices, so duplicate native scopes remain distinct; intersecting sets must be nested/equal; a free variable’s strict incidence subset must not be contained in a hidden variable incidence; disjoint pairs are allowed. |
| ownership | All scope/incidence/free vectors are local derived values; query borrowed. |
| failure | Returns false on failed incidence or free-closure checks. Out-of-range term or head VariableIds are outside its precondition and are indexed without validation. |
| cost | Builds per-occurrence sets and per-variable incidence sets, then checks variable pairs and set intersections/subsets; no complexity bound is asserted. |
| Design | [tests/unit/planner_fast_paths_test.cpp](../../../../../tests/unit/planner_fast_paths_test.cpp), [CMakeLists.txt](../../../../../CMakeLists.txt), [include/crown/planner/oracle.hpp](../../../../../include/crown/planner/oracle.hpp), [src/planner/exact.cpp](../../../../../src/planner/exact.cpp), [tests/support/planner_exact_baseline.cpp](../../../../../tests/support/planner_exact_baseline.cpp), [tests/reference/tree_oracle.cpp](../../../../../tests/reference/tree_oracle.cpp), [docs/planner_proofs.md](../../../../planner_proofs.md) |

## B0023

[Lines 132–134](../../../../../tests/unit/planner_fast_paths_test.cpp#L132); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
planner::HeightCertificate certificate_of(const planner::OracleResult& result) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Copy the certificate fields needed to independently replay an OracleResult. |
| inputs / outputs | Input OracleResult; output HeightCertificate with algorithm, minimum height, optional tree and lower bounds. |
| invariants | No other status/statistics fields are copied. |
| ownership | Returned certificate owns copies of copied members. |
| failure | No helper-level failure beyond allocation/copy errors. |
| cost | Copies algorithm/tree and lower-bound vectors; cost scales with certificate payload. |
| Design | [tests/unit/planner_fast_paths_test.cpp](../../../../../tests/unit/planner_fast_paths_test.cpp), [CMakeLists.txt](../../../../../CMakeLists.txt), [include/crown/planner/oracle.hpp](../../../../../include/crown/planner/oracle.hpp), [src/planner/exact.cpp](../../../../../src/planner/exact.cpp), [tests/support/planner_exact_baseline.cpp](../../../../../tests/support/planner_exact_baseline.cpp), [tests/reference/tree_oracle.cpp](../../../../../tests/reference/tree_oracle.cpp), [docs/planner_proofs.md](../../../../planner_proofs.md) |

## B0025

[Lines 136–149](../../../../../tests/unit/planner_fast_paths_test.cpp#L136); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void check_native_occurrences_once(const Fixture& fixture, const FreeConnexTree& tree,
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Assert the output tree contains each query atom occurrence exactly once as a native node. |
| inputs / outputs | Inputs Fixture, tree and context; output is no value on success. |
| invariants | Collects native node occurrence IDs, requires each present, sorts, and compares exactly with \[0, atom_count). |
| ownership | Tree/fixture borrowed; temporary vectors owned locally. |
| failure | Missing occurrence or mismatch throws via check. |
| cost | Scans nodes, allocates occurrence/expected vectors, sorts IDs and compares; caller diagnostic strings may be built eagerly. |
| Design | [tests/unit/planner_fast_paths_test.cpp](../../../../../tests/unit/planner_fast_paths_test.cpp), [CMakeLists.txt](../../../../../CMakeLists.txt), [include/crown/planner/oracle.hpp](../../../../../include/crown/planner/oracle.hpp), [src/planner/exact.cpp](../../../../../src/planner/exact.cpp), [tests/support/planner_exact_baseline.cpp](../../../../../tests/support/planner_exact_baseline.cpp), [tests/reference/tree_oracle.cpp](../../../../../tests/reference/tree_oracle.cpp), [docs/planner_proofs.md](../../../../planner_proofs.md) |

## B0027

[Lines 151–164](../../../../../tests/unit/planner_fast_paths_test.cpp#L151); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
planner::OracleResult require_minimum(const Fixture& fixture, std::size_t expected,
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Require optimized v2 search to return the expected independently checked minimum. |
| inputs / outputs | Inputs Fixture, expected height, optional SearchLimits and context; output is OracleResult. |
| invariants | Asserts proven_minimum, exact height/tree, algorithm crown_partition_exact_v2, P02-valid upper, valid replay of certificate_of(result), certificate_verified and each native occurrence once. |
| ownership | Result owns tree/certificate; fixture borrowed. |
| failure | Any missing result, invalid upper/certificate, algorithm mismatch or occurrence loss throws. |
| cost | Calls minimum_tree, validates upper, replays height certificate and scans/sorts native IDs; expensive search depends on fixture and limits. |
| Design | [tests/unit/planner_fast_paths_test.cpp](../../../../../tests/unit/planner_fast_paths_test.cpp), [CMakeLists.txt](../../../../../CMakeLists.txt), [include/crown/planner/oracle.hpp](../../../../../include/crown/planner/oracle.hpp), [src/planner/exact.cpp](../../../../../src/planner/exact.cpp), [tests/support/planner_exact_baseline.cpp](../../../../../tests/support/planner_exact_baseline.cpp), [tests/reference/tree_oracle.cpp](../../../../../tests/reference/tree_oracle.cpp), [docs/planner_proofs.md](../../../../planner_proofs.md), [src/planner/search_session.cpp](../../../../../src/planner/search_session.cpp) |

## B0029

[Lines 166–186](../../../../../tests/unit/planner_fast_paths_test.cpp#L166); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void compare_all_three(const Fixture& fixture, const std::string& context) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Compare optimized search with private v1 baseline and frozen P03 exhaustive minimum. |
| inputs / outputs | Input Fixture/context; output is not returned. |
| invariants | All three must avoid resource_limit and agree on status/minimum; if proven, v2 and baseline witness/proof replays are checked. It compares minimum claims, not exact tree shape. |
| ownership | Three result values and certificates are local owners. |
| failure | Any resource stop or disagreement throws. |
| cost | Runs three search implementations and sometimes two extra certificate replays; reference enumeration may be combinatorial and allocates trees/scopes. |
| Design | [tests/unit/planner_fast_paths_test.cpp](../../../../../tests/unit/planner_fast_paths_test.cpp), [CMakeLists.txt](../../../../../CMakeLists.txt), [include/crown/planner/oracle.hpp](../../../../../include/crown/planner/oracle.hpp), [src/planner/exact.cpp](../../../../../src/planner/exact.cpp), [tests/support/planner_exact_baseline.cpp](../../../../../tests/support/planner_exact_baseline.cpp), [tests/reference/tree_oracle.cpp](../../../../../tests/reference/tree_oracle.cpp), [docs/planner_proofs.md](../../../../planner_proofs.md), [tests/reference/tree_oracle.hpp](../../../../../tests/reference/tree_oracle.hpp), [tests/support/planner_probe.hpp](../../../../../tests/support/planner_probe.hpp) |

## B0031

[Lines 188–261](../../../../../tests/unit/planner_fast_paths_test.cpp#L188); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void exhaustive_small_differential_and_hierarchy_predicate() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Differentially exercise all ordered zero/one/two-scope masks over three variables and every valid head. |
| inputs / outputs | No inputs; builds each fixture, evaluates independent hierarchy predicate, optimized v2, test-only v1 and frozen P03. |
| invariants | Exactly 371 valid cases; nonempty independently hierarchical cases prove height one; the strict upward-free-closure negative fixture falls back to proved height two with hierarchy test and exact states. |
| ownership | Per-case fixture/results are local. |
| failure | Resource stops, mismatched outcomes, missing proof or changed case counts throw. |
| cost | Runs 371 triples of search and selected proof replays, plus negative witness; finite differential evidence only, not a theorem for all queries. |
| Design | [tests/unit/planner_fast_paths_test.cpp](../../../../../tests/unit/planner_fast_paths_test.cpp), [CMakeLists.txt](../../../../../CMakeLists.txt), [include/crown/planner/oracle.hpp](../../../../../include/crown/planner/oracle.hpp), [src/planner/exact.cpp](../../../../../src/planner/exact.cpp), [tests/support/planner_exact_baseline.cpp](../../../../../tests/support/planner_exact_baseline.cpp), [tests/reference/tree_oracle.cpp](../../../../../tests/reference/tree_oracle.cpp), [docs/planner_proofs.md](../../../../planner_proofs.md), [tests/support/planner_probe.hpp](../../../../../tests/support/planner_probe.hpp) |

## B0033

[Lines 263–265](../../../../../tests/unit/planner_fast_paths_test.cpp#L263); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::vector<std::vector<std::size_t>> seven_atom_residual_scopes() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Return the literal seven-atom residual counterexample scope family. |
| inputs / outputs | No inputs; returns seven ordered scopes. |
| invariants | Scope data is fixed for height-three and pruning fixtures. |
| ownership | Returned nested vectors own their storage. |
| failure | No helper-level failure. |
| cost | Copies a small fixed set of variable indices. |
| Design | [tests/unit/planner_fast_paths_test.cpp](../../../../../tests/unit/planner_fast_paths_test.cpp), [CMakeLists.txt](../../../../../CMakeLists.txt), [include/crown/planner/oracle.hpp](../../../../../include/crown/planner/oracle.hpp), [src/planner/exact.cpp](../../../../../src/planner/exact.cpp), [tests/support/planner_exact_baseline.cpp](../../../../../tests/support/planner_exact_baseline.cpp), [tests/reference/tree_oracle.cpp](../../../../../tests/reference/tree_oracle.cpp), [docs/planner_proofs.md](../../../../planner_proofs.md) |

## B0035

[Lines 267–270](../../../../../tests/unit/planner_fast_paths_test.cpp#L267); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::vector<std::vector<std::size_t>> nine_atom_residual_scopes() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Return the literal nine-atom residual counterexample scope family. |
| inputs / outputs | No inputs; returns nine ordered scopes. |
| invariants | Scope data is fixed for the height-three residual fixture. |
| ownership | Returned nested vectors own their storage. |
| failure | No helper-level failure. |
| cost | Copies a small fixed set of variable indices. |
| Design | [tests/unit/planner_fast_paths_test.cpp](../../../../../tests/unit/planner_fast_paths_test.cpp), [CMakeLists.txt](../../../../../CMakeLists.txt), [include/crown/planner/oracle.hpp](../../../../../include/crown/planner/oracle.hpp), [src/planner/exact.cpp](../../../../../src/planner/exact.cpp), [tests/support/planner_exact_baseline.cpp](../../../../../tests/support/planner_exact_baseline.cpp), [tests/reference/tree_oracle.cpp](../../../../../tests/reference/tree_oracle.cpp), [docs/planner_proofs.md](../../../../planner_proofs.md) |

## B0037

[Lines 272–293](../../../../../tests/unit/planner_fast_paths_test.cpp#L272); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Fixture disjoint_components(const std::vector<std::pair<std::vector<std::vector<std::size_t>>, std::vector<std::size_t>>>& components,
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Join separate scope/head fixtures while shifting variable labels to disjoint ranges. |
| inputs / outputs | Inputs component pairs and a component index order; output is one scoped fixture. |
| invariants | Each component width is max label plus one across scopes/head; offset advances by width; component and atom order follow order argument. |
| ownership | Intermediate scopes/head and returned fixture are owned values. |
| failure | Invalid component index throws from at(); invalid labels may fail downstream. |
| cost | Scans scope/head labels, copies and shifts each scope, then delegates construction; work grows with selected component sizes. |
| Design | [tests/unit/planner_fast_paths_test.cpp](../../../../../tests/unit/planner_fast_paths_test.cpp), [CMakeLists.txt](../../../../../CMakeLists.txt), [include/crown/planner/oracle.hpp](../../../../../include/crown/planner/oracle.hpp), [src/planner/exact.cpp](../../../../../src/planner/exact.cpp), [tests/support/planner_exact_baseline.cpp](../../../../../tests/support/planner_exact_baseline.cpp), [tests/reference/tree_oracle.cpp](../../../../../tests/reference/tree_oracle.cpp), [docs/planner_proofs.md](../../../../planner_proofs.md) |

## B0039

[Lines 295–311](../../../../../tests/unit/planner_fast_paths_test.cpp#L295); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Fixture permuted_scopes(const std::vector<std::vector<std::size_t>>& scopes,
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Permute atom order and relabel variables in a scope/head fixture. |
| inputs / outputs | Inputs scopes, head, atom order and variable map; output remapped fixture. |
| invariants | Each selected atom uses scopes.at; labels map through variable_map.at; each mapped scope and head are sorted before construction. |
| ownership | Intermediate vectors and output own their data. |
| failure | Bad atom/variable indices throw out_of_range. |
| cost | Copies selected scopes, rewrites and sorts each, maps/sorts head, then builds fixture. |
| Design | [tests/unit/planner_fast_paths_test.cpp](../../../../../tests/unit/planner_fast_paths_test.cpp), [CMakeLists.txt](../../../../../CMakeLists.txt), [include/crown/planner/oracle.hpp](../../../../../include/crown/planner/oracle.hpp), [src/planner/exact.cpp](../../../../../src/planner/exact.cpp), [tests/support/planner_exact_baseline.cpp](../../../../../tests/support/planner_exact_baseline.cpp), [tests/reference/tree_oracle.cpp](../../../../../tests/reference/tree_oracle.cpp), [docs/planner_proofs.md](../../../../planner_proofs.md) |

## B0041

[Lines 313–361](../../../../../tests/unit/planner_fast_paths_test.cpp#L313); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void singleton_empty_and_structural_semantics() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Check empty, singleton, nullary, duplicate-incidence, contradiction, constants and ignored-column semantics. |
| inputs / outputs | No inputs; creates several scoped/slot fixtures and calls require_minimum, independent predicate and differential helpers. |
| invariants | Asserts empty bodies (including contradiction) have height 0; singleton native roots height 1; multiple nullaries join under empty generalized root; duplicate occurrence IDs retained; equal mixed free/hidden incidence is q-hierarchical; nonempty contradiction keeps structure; constants/ignored/repeated terms do not change incidence sets. |
| ownership | All fixtures/results local; no global state. |
| failure | Any path shape, height, occurrence or incidence assertion throws. |
| cost | Several exact searches, certificate replays and one three-way differential case; each fixture is small, but no test runtime bound is claimed. |
| Design | [tests/unit/planner_fast_paths_test.cpp](../../../../../tests/unit/planner_fast_paths_test.cpp), [CMakeLists.txt](../../../../../CMakeLists.txt), [include/crown/planner/oracle.hpp](../../../../../include/crown/planner/oracle.hpp), [src/planner/exact.cpp](../../../../../src/planner/exact.cpp), [tests/support/planner_exact_baseline.cpp](../../../../../tests/support/planner_exact_baseline.cpp), [tests/reference/tree_oracle.cpp](../../../../../tests/reference/tree_oracle.cpp), [docs/planner_proofs.md](../../../../planner_proofs.md), [src/planner/search_session.cpp](../../../../../src/planner/search_session.cpp) |

## B0043

[Lines 363–396](../../../../../tests/unit/planner_fast_paths_test.cpp#L363); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void fast_path_statistics_and_components() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Check exact-search fast-path counters and disconnected-component maximum-height behavior. |
| inputs / outputs | No inputs; uses duplicate scopes, height-one/two/three components, permutations and a relabeled residual. |
| invariants | Requires symmetry_skips for duplicate equal scopes; component_splits for disconnected examples; combined height is max tested 2 then 3; atom/variable permutations preserve height 3. |
| ownership | Fixtures/results local. |
| failure | Missing expected counter or minimum throws. |
| cost | Repeated optimized proof/replay calls; component builders copy/shift scopes and planner builds dynamic search state. Counters are tested examples, not complexity guarantees. |
| Design | [tests/unit/planner_fast_paths_test.cpp](../../../../../tests/unit/planner_fast_paths_test.cpp), [CMakeLists.txt](../../../../../CMakeLists.txt), [include/crown/planner/oracle.hpp](../../../../../include/crown/planner/oracle.hpp), [src/planner/exact.cpp](../../../../../src/planner/exact.cpp), [tests/support/planner_exact_baseline.cpp](../../../../../tests/support/planner_exact_baseline.cpp), [tests/reference/tree_oracle.cpp](../../../../../tests/reference/tree_oracle.cpp), [docs/planner_proofs.md](../../../../planner_proofs.md) |

## B0045

[Lines 398–410](../../../../../tests/unit/planner_fast_paths_test.cpp#L398); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void residual_counterexamples_and_branch_bound() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Check height-three residual witnesses and observed branch-and-bound pruning. |
| inputs / outputs | No inputs; runs fixed seven- and nine-atom scopes with work=50,000,000, recursion=512 and literal_scope=4096. |
| invariants | Both are independently required minimum 3; seven-atom case must report bound_prunes&gt;0. |
| ownership | Limits/results/fixtures local. |
| failure | Any resource stop, changed height or no observed prune throws. |
| cost | Runs exact search and certificate replay on both fixtures under explicit budgets; positive prune count is fixture-specific, not a bound on total search. |
| Design | [tests/unit/planner_fast_paths_test.cpp](../../../../../tests/unit/planner_fast_paths_test.cpp), [CMakeLists.txt](../../../../../CMakeLists.txt), [include/crown/planner/oracle.hpp](../../../../../include/crown/planner/oracle.hpp), [src/planner/exact.cpp](../../../../../src/planner/exact.cpp), [tests/support/planner_exact_baseline.cpp](../../../../../tests/support/planner_exact_baseline.cpp), [tests/reference/tree_oracle.cpp](../../../../../tests/reference/tree_oracle.cpp), [docs/planner_proofs.md](../../../../planner_proofs.md) |

## B0047

[Lines 412–458](../../../../../tests/unit/planner_fast_paths_test.cpp#L412); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void large_dynamic_representations() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Exercise dynamic hierarchy construction beyond 64 variables, occurrences and native-scope width. |
| inputs / outputs | No inputs; creates 75 disjoint singleton scopes, a 75-leaf star, and a 70-level laminar chain. |
| invariants | Each must prove height one and record hierarchy hit; chain has &gt;64 variables/atoms, last scope width &gt;64, and &gt;2 generalized output nodes. |
| ownership | Generated vectors/fixtures/results are local. |
| failure | Any fixed-width truncation, failed certificate, wrong minimum or missing nesting throws. |
| cost | Builds 75 or 70 occurrence fixtures (chain contains 2,485 terms), then optimized search/P02/certificate replays; explicit limits are work=50,000,000, recursion=1024, literal_scope=4096. |
| Design | [tests/unit/planner_fast_paths_test.cpp](../../../../../tests/unit/planner_fast_paths_test.cpp), [CMakeLists.txt](../../../../../CMakeLists.txt), [include/crown/planner/oracle.hpp](../../../../../include/crown/planner/oracle.hpp), [src/planner/exact.cpp](../../../../../src/planner/exact.cpp), [tests/support/planner_exact_baseline.cpp](../../../../../tests/support/planner_exact_baseline.cpp), [tests/reference/tree_oracle.cpp](../../../../../tests/reference/tree_oracle.cpp), [docs/planner_proofs.md](../../../../planner_proofs.md) |

## B0049

[Lines 460–469](../../../../../tests/unit/planner_fast_paths_test.cpp#L460); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::optional<std::size_t> find_bound(std::vector<planner::LowerBoundEntry>& entries,
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Find a certificate lower-bound entry by exact state members and two permission flags. |
| inputs / outputs | Inputs mutable entry vector, occurrence list, generalized_allowed and connex_reachable; output optional index. |
| invariants | Requires all three fields to match; returns first match or nullopt. |
| ownership | Entries borrowed mutably but not modified; result is an index value. |
| failure | No explicit failure; no match is represented by nullopt. |
| cost | Linear scan over lower_bounds with vector equality for each entry; no index is built. |
| Design | [tests/unit/planner_fast_paths_test.cpp](../../../../../tests/unit/planner_fast_paths_test.cpp), [CMakeLists.txt](../../../../../CMakeLists.txt), [include/crown/planner/oracle.hpp](../../../../../include/crown/planner/oracle.hpp), [src/planner/exact.cpp](../../../../../src/planner/exact.cpp), [tests/support/planner_exact_baseline.cpp](../../../../../tests/support/planner_exact_baseline.cpp), [tests/reference/tree_oracle.cpp](../../../../../tests/reference/tree_oracle.cpp), [docs/planner_proofs.md](../../../../planner_proofs.md) |

## B0051

[Lines 471–592](../../../../../tests/unit/planner_fast_paths_test.cpp#L471); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void certificate_malformations() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Mutate optimized certificates and reject false/incomplete claims while accepting both a valid augmented shared-scope height-one bound and a finite bound for a globally infeasible residual. |
| inputs / outputs | No inputs; obtains duplicate-scope, disconnected and transport fixtures/certificates and changes orbit membership, occurrence ranges, bounds, component entries/flags, shared-scope residual and upper occurrence. |
| invariants | Rejects duplicate orbit representative, duplicate/out-of-range memberships, false root/component bounds, missing component proof, false context flags and invalid upper native ID. Accepts augmented bound 1 for feasible repeated scopes, then rejects bound 2 there; separately accepts finite bound 2 for the globally infeasible {2,3} residual. |
| ownership | Certificates are independent mutable copies; fixtures/results local. |
| failure | Malformed claims are expected invalid results; helper checks exact valid/invalid outcomes. |
| cost | Runs exact searches then multiple proof replays, each traversing lower-bound entries/tree; edits/copies vectors. It does not establish completeness of mutation coverage. |
| Design | [tests/unit/planner_fast_paths_test.cpp](../../../../../tests/unit/planner_fast_paths_test.cpp), [CMakeLists.txt](../../../../../CMakeLists.txt), [include/crown/planner/oracle.hpp](../../../../../include/crown/planner/oracle.hpp), [src/planner/exact.cpp](../../../../../src/planner/exact.cpp), [tests/support/planner_exact_baseline.cpp](../../../../../tests/support/planner_exact_baseline.cpp), [tests/reference/tree_oracle.cpp](../../../../../tests/reference/tree_oracle.cpp), [docs/planner_proofs.md](../../../../planner_proofs.md), [src/planner/search_session.cpp](../../../../../src/planner/search_session.cpp) |

## B0053

[Lines 594–623](../../../../../tests/unit/planner_fast_paths_test.cpp#L594); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void budget_exhaustion_stays_explicit() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Assert zero work/time/recursion budgets produce explicit resource-limit results without partial proof claims. |
| inputs / outputs | No inputs; applies each zero SearchLimits field to minimum_tree and zero work to replay of a complete certificate. |
| invariants | Each search returns resource_limit with no minimum/tree/lower_bounds and certificate_verified=false; replay marks resource_limit and invalid. |
| ownership | Result/certificate values local. |
| failure | Expected resource exhaustion is success; any unsupported/completed/partial result throws. |
| cost | Five planner calls: three independently zero-limited minimum_tree searches, one healthy search to obtain a complete certificate, and its zero-work verification. Entry/setup work can precede charging; zero budgets do not assert zero CPU or allocation. |
| Design | [tests/unit/planner_fast_paths_test.cpp](../../../../../tests/unit/planner_fast_paths_test.cpp), [CMakeLists.txt](../../../../../CMakeLists.txt), [include/crown/planner/oracle.hpp](../../../../../include/crown/planner/oracle.hpp), [src/planner/exact.cpp](../../../../../src/planner/exact.cpp), [tests/support/planner_exact_baseline.cpp](../../../../../tests/support/planner_exact_baseline.cpp), [tests/reference/tree_oracle.cpp](../../../../../tests/reference/tree_oracle.cpp), [docs/planner_proofs.md](../../../../planner_proofs.md), [src/planner/search_session.cpp](../../../../../src/planner/search_session.cpp) |

## B0054

[Lines 624–626](../../../../../tests/unit/planner_fast_paths_test.cpp#L624); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L624-L626:sha256:9e375a3cb3a2cbe2f9ded9c8296a6ab66848cc826fd71f919246acb17e0bd455
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Close the recorded declaration scopes in planner_fast_paths_test.cpp: namespace (anonymous). |
| inputs / outputs | Preceding namespace, type or initializer declarations in; completed lexical boundary out. |
| invariants | Brace-opening context is recorded in root-scope-context-v1.json. These are declaration/initializer boundaries, not an independent update, validation or recovery operation. |
| ownership | Enclosing objects and borrowed fields keep their declared ownership. This punctuation creates no new owner. |
| failure | Malformed scope syntax is a compile error. Any initializer/constructor failure belongs to the enclosing object declaration. |
| cost | No separate loop, guard or engine call is introduced by the delimiter; enclosing initialization and object lifetime still have their actual costs. |
| Design | [tests/unit/planner_fast_paths_test.cpp](../../../../../tests/unit/planner_fast_paths_test.cpp), [docs/planner_continuations.md](../../../../planner_continuations.md), [docs/code_review.md](../../../../code_review.md) |

## B0055

[Lines 627–642](../../../../../tests/unit/planner_fast_paths_test.cpp#L627); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
int main() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Run all fast-path, exact-fallback, large-dynamic, certificate and budget test groups. |
| inputs / outputs | No inputs; invokes the seven named test functions in order and returns process status. |
| invariants | Success text prints only after all seven groups return; a caught standard exception prints to stderr and returns 1. Other exception types are not caught by this main. |
| ownership | Each test owns its values; main owns no shared query state. |
| failure | Any thrown assertion or standard exception is caught and produces nonzero exit. |
| cost | Aggregates finite workloads from all groups; presence of this entry records source call order and is not evidence that native tests were run. |
| Design | [tests/unit/planner_fast_paths_test.cpp](../../../../../tests/unit/planner_fast_paths_test.cpp), [CMakeLists.txt](../../../../../CMakeLists.txt), [include/crown/planner/oracle.hpp](../../../../../include/crown/planner/oracle.hpp), [src/planner/exact.cpp](../../../../../src/planner/exact.cpp), [tests/support/planner_exact_baseline.cpp](../../../../../tests/support/planner_exact_baseline.cpp), [tests/reference/tree_oracle.cpp](../../../../../tests/reference/tree_oracle.cpp), [docs/planner_proofs.md](../../../../planner_proofs.md) |
