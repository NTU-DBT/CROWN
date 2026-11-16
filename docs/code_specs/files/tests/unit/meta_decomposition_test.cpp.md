# `tests/unit/meta_decomposition_test.cpp` — block usage map

[Source](../../../../../tests/unit/meta_decomposition_test.cpp) · [Source index](../../../README.md) · [Subsystem contracts](../../../subsystem_contracts.md) · [Reviewed primitives](../../../primitives.md)

Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection.

Snapshot SHA-256: `fff035df408088972c4aeed1dcd83b2e8f1945cba370734ec1442250ac67a780`. 460 lines partitioned into 40 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [tests](../../../subsystem_contracts.md#tests). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/code_review.md](../../../../code_review.md), [docs/reference_fuzz.md](../../../../reference_fuzz.md), [docs/task_ledger.md](../../../../task_ledger.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–18](../../../../../tests/unit/meta_decomposition_test.cpp#L1) | Imports dependencies; declares namespace scope; declares aliases; declares values/defaults or compile-time conditions. |  · [reviewed contract](#b0001) |
| [B0002 · 19–21](../../../../../tests/unit/meta_decomposition_test.cpp#L19) | Callable definition: void require(bool condition, const std::string& message) | calls std::runtime_error; guard void require(bool condition, const std::string& message) { · [reviewed contract](#b0002) |
| [B0003 · 22–22](../../../../../tests/unit/meta_decomposition_test.cpp#L22) | Explanatory comments or spacing. |  |
| [B0004 · 23–35](../../../../../tests/unit/meta_decomposition_test.cpp#L23) | Callable definition: const char* stop_name(meta::Stop stop) | calls ; returns @; @ · [reviewed contract](#b0004) |
| [B0005 · 36–36](../../../../../tests/unit/meta_decomposition_test.cpp#L36) | Explanatory comments or spacing. |  |
| [B0006 · 37–41](../../../../../tests/unit/meta_decomposition_test.cpp#L37) | Callable definition: Scope scope(std::initializer_list&lt;std::size_t&gt; variables) | calls insert; returns result; growth insert; 1 loop sites · [reviewed contract](#b0006) |
| [B0007 · 42–42](../../../../../tests/unit/meta_decomposition_test.cpp#L42) | Explanatory comments or spacing. |  |
| [B0008 · 43–47](../../../../../tests/unit/meta_decomposition_test.cpp#L43) | Type/record definition: struct Fixture |  · [reviewed contract](#b0008) |
| [B0009 · 48–50](../../../../../tests/unit/meta_decomposition_test.cpp#L48) | Explanatory comments or spacing. | source comment (unverified): // Build a valid direct-CQ input. Sparse test labels are renamed densely; each · [reviewed contract](#b0009) |
| [B0010 · 51–75](../../../../../tests/unit/meta_decomposition_test.cpp#L51) | Callable definition: Fixture query_for(const std::vector&lt;std::vector&lt;std::size_t&gt;&gt;& input) | calls emplace, size, push_back, std::to_string; returns fixture; growth emplace, emplace_back, insert, push_back; 5 loop sites; source comment (unverified): // Build a valid direct-CQ input. Sparse test labels are renamed densely; each · [reviewed contract](#b0010) |
| [B0011 · 76–76](../../../../../tests/unit/meta_decomposition_test.cpp#L76) | Explanatory comments or spacing. |  |
| [B0012 · 77–82](../../../../../tests/unit/meta_decomposition_test.cpp#L77) | Callable definition: meta::Node node(std::optional&lt;std::size_t&gt; occurrence, std::initializer_list&lt;std::size_t&gt; chi, std::initializer_list&lt;std::size_t&gt;… | calls scope; returns {occurrence, scope(chi), scope(kappa), parent} · [reviewed contract](#b0012) |
| [B0013 · 83–83](../../../../../tests/unit/meta_decomposition_test.cpp#L83) | Explanatory comments or spacing. |  |
| [B0014 · 84–86](../../../../../tests/unit/meta_decomposition_test.cpp#L84) | Callable definition: bool covers(const Scope& large, const Scope& small) | calls std::includes, begin, end; returns std::includes(large.begin(), large.end(), small.begin(), small.end()) · [reviewed contract](#b0014) |
| [B0015 · 87–91](../../../../../tests/unit/meta_decomposition_test.cpp#L87) | Explanatory comments or spacing. | source comment (unverified): // Inspect actual fields rather than treating either API's success flag as a · [reviewed contract](#b0015) |
| [B0016 · 92–162](../../../../../tests/unit/meta_decomposition_test.cpp#L92) | Callable definition: void inspect(const Fixture& fixture, const meta::Decomposition& m, const std::string& label) | calls size, require, occurrences, covers; guard require(count != 0 && m.root &lt; count, label + ": missing root");; returns present; growth emplace, insert; 11 loop sites; source comment (unverified): // Inspect actual fields rather than treating either API's success flag as a · [reviewed contract](#b0016) |
| [B0017 · 163–165](../../../../../tests/unit/meta_decomposition_test.cpp#L163) | Explanatory comments or spacing. | source comment (unverified): // Match by lambda (physical occurrence) or chi (minor), so an implementation · [reviewed contract](#b0017) |
| [B0018 · 166–191](../../../../../tests/unit/meta_decomposition_test.cpp#L166) | Callable definition: void expect_structure(const meta::Decomposition& actual, const meta::Decomposition& expected, const std::string& label) | calls require, size, matching, has_value; guard require(actual.nodes.size() == expected.nodes.size(), label + ": wrong node count");; 3 loop sites; source comment (unverified): // Match by lambda (physical occurrence) or chi (minor), so an implementation · [reviewed contract](#b0018) |
| [B0019 · 192–192](../../../../../tests/unit/meta_decomposition_test.cpp#L192) | Explanatory comments or spacing. |  |
| [B0020 · 193–193](../../../../../tests/unit/meta_decomposition_test.cpp#L193) | Type/record definition: struct Case |  · [reviewed contract](#b0020) |
| [B0021 · 194–194](../../../../../tests/unit/meta_decomposition_test.cpp#L194) | Explanatory comments or spacing. |  |
| [B0022 · 195–251](../../../../../tests/unit/meta_decomposition_test.cpp#L195) | Callable definition: std::vector&lt;Case&gt; paper_cases() | calls push_back, query_for, node, validate; returns cases; growth push_back; source comment (unverified): // Algorithm 1, p.12: a scope-interned special{x} reappears in a later round. · [reviewed contract](#b0022) |
| [B0023 · 252–252](../../../../../tests/unit/meta_decomposition_test.cpp#L252) | Explanatory comments or spacing. |  |
| [B0024 · 253–264](../../../../../tests/unit/meta_decomposition_test.cpp#L253) | Callable definition: void source_fixtures(const std::vector&lt;Case&gt;& cases) | calls inspect, meta::construct, require, stop_name; guard require(built.stop == meta::Stop::complete && built.decomposition,; 1 loop sites · [reviewed contract](#b0024) |
| [B0025 · 265–265](../../../../../tests/unit/meta_decomposition_test.cpp#L265) | Explanatory comments or spacing. |  |
| [B0026 · 266–270](../../../../../tests/unit/meta_decomposition_test.cpp#L266) | Callable definition: void expect_build_stop(const Fixture& fixture, meta::Stop expected, const std::string& label) | calls meta::construct, require, stop_name; guard require(built.stop == expected && !built.decomposition, · [reviewed contract](#b0026) |
| [B0027 · 271–271](../../../../../tests/unit/meta_decomposition_test.cpp#L271) | Explanatory comments or spacing. |  |
| [B0028 · 272–298](../../../../../tests/unit/meta_decomposition_test.cpp#L272) | Callable definition: void domain_cases() | calls query_for, expect_build_stop, node, meta::check; guard const auto triangle_check = meta::check(triangle.catalog, triangle.query, unguarded);; source comment (unverified): // Paper §2.1, p.4 excludes empty hyperedges. These are explicit provider · [reviewed contract](#b0028) |
| [B0029 · 299–299](../../../../../tests/unit/meta_decomposition_test.cpp#L299) | Explanatory comments or spacing. |  |
| [B0030 · 300–304](../../../../../tests/unit/meta_decomposition_test.cpp#L300) | Callable definition: void reject(const Fixture& fixture, const meta::Decomposition& bad, const std::string& label) | calls meta::check, require, stop_name; guard const auto result = meta::check(fixture.catalog, fixture.query, bad); · [reviewed contract](#b0030) |
| [B0031 · 305–305](../../../../../tests/unit/meta_decomposition_test.cpp#L305) | Explanatory comments or spacing. |  |
| [B0032 · 306–342](../../../../../tests/unit/meta_decomposition_test.cpp#L306) | Callable definition: void tampered_cases(const std::vector&lt;Case&gt;& cases) | calls at, size, reject, reset; growth insert, push_back; source comment (unverified): // Nonroot full-interface minor has all roles. · [reviewed contract](#b0032) |
| [B0033 · 343–343](../../../../../tests/unit/meta_decomposition_test.cpp#L343) | Explanatory comments or spacing. |  |
| [B0034 · 344–347](../../../../../tests/unit/meta_decomposition_test.cpp#L344) | Callable definition: void within(const meta::Usage& usage, const meta::Limits& limits, const std::string& label) | calls require; guard require(usage.work &lt;= limits.work && usage.nodes &lt;= limits.nodes && usage.scope_cells &lt;= limits.sco… · [reviewed contract](#b0034) |
| [B0035 · 348–351](../../../../../tests/unit/meta_decomposition_test.cpp#L348) | Explanatory comments or spacing. | source comment (unverified): // Exact/one-short limits concern only the header's selected metadata work, · [reviewed contract](#b0035) |
| [B0036 · 352–398](../../../../../tests/unit/meta_decomposition_test.cpp#L352) | Callable definition: void budgets(const Case& test) | calls meta::construct, require, within, expect_structure; guard require(baseline.stop == meta::Stop::complete && baseline.decomposition, "budget baseline must comp…; 3 loop sites; source comment (unverified): // Exact/one-short limits concern only the header's selected metadata work, · [reviewed contract](#b0036) |
| [B0037 · 399–399](../../../../../tests/unit/meta_decomposition_test.cpp#L399) | Explanatory comments or spacing. |  |
| [B0038 · 400–444](../../../../../tests/unit/meta_decomposition_test.cpp#L400) | Callable definition: void independent_corpus() | calls masks, std::is_sorted, begin, end; guard require(built.stop == meta::Stop::complete && built.decomposition,; growth push_back; 7 loop sites; source comment (unverified): // All 3,875 multisets of 1..4 nonempty edges over four variables, each in · [reviewed contract](#b0038) |
| [B0039 · 445–446](../../../../../tests/unit/meta_decomposition_test.cpp#L445) | Closes surrounding scope/type. | source comment (unverified): // namespace · [reviewed contract](#b0039) |
| [B0040 · 447–460](../../../../../tests/unit/meta_decomposition_test.cpp#L447) | Callable definition: int main() | calls paper_cases, source_fixtures, domain_cases, tampered_cases; returns 0; 1 · [reviewed contract](#b0040) |

## B0001

[Lines 1–18](../../../../../tests/unit/meta_decomposition_test.cpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L1-L18:sha256:2a717d304e45e12892fbbe18ae74ae40a6ff0336b9e676c00c6baf2ab025e405
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Import the metadata API and standard test helpers into one standalone unit-test translation unit. |
| inputs / outputs | Includes provide containers, diagnostics and the public meta API; local using/namespace aliases make helper names concise. |
| invariants | Test helpers have internal linkage. Importing the implementation API supplies no expected acyclicity result or prevalidated graph. |
| ownership | This scaffolding owns no live fixture or global mutable test cache. |
| failure | Dependency or naming mistakes fail compilation. Runtime failures are handled by the test helpers and main below. |
| cost | Build-time parsing only; no query/update work executes in this declarations region. |
| Design | [docs/meta_decompositions.md](../../../../meta_decompositions.md) |

## B0002

[Lines 19–21](../../../../../tests/unit/meta_decomposition_test.cpp#L19); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L19-L21:sha256:1e93bb10853211102ced622e7cf5fe087a0765e280eda599fcc6f21b46cf8385
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Keep test expectations active in every build configuration and fail with a concrete diagnostic. |
| inputs / outputs | A computed condition and diagnostic string either return normally or throw runtime_error. |
| invariants | Unlike assertions, these checks remain active with NDEBUG. The caller, not this helper, decides the expected semantic property. |
| ownership | The helper borrows the message on success; a thrown runtime_error owns its diagnostic for main to report. |
| failure | A false condition throws; main catches standard exceptions and returns nonzero. Message construction/allocation failures also propagate. |
| cost | One conditional branch after caller argument evaluation; strings may already have allocated at the call site and failure construction/unwinding has additional cost. |
| Design | [docs/meta_decompositions.md](../../../../meta_decompositions.md) |

## B0004

[Lines 23–35](../../../../../tests/unit/meta_decomposition_test.cpp#L23); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L23-L35:sha256:b1ce76c779847ca4114f681efe4573b13cbc6124a69f7e98001b176f9fe1f1e4
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Translate public stop values into stable labels for test failures. |
| inputs / outputs | A meta::Stop produces a pointer to a static string literal, with unknown as the fallback label. |
| invariants | The switch describes diagnostics only and never calculates expected class, validates metadata or alters the Stop. |
| ownership | Returned literals have static storage; callers borrow them and need not free or retain a graph. |
| failure | No explicit runtime failure is raised; an unknown enum value is rendered diagnostically rather than treated as success. |
| cost | A fixed switch over the current enumerators, with no dynamic allocation or graph scan in the helper. |
| Design | [docs/meta_decompositions.md](../../../../meta_decompositions.md) |

## B0006

[Lines 37–41](../../../../../tests/unit/meta_decomposition_test.cpp#L37); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L37-L41:sha256:24b0ffd9ac0fe4d85b4990b605e60a455dca7895deb3cb02233ab8784dc423fc
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Construct a small ordered variable set from explicit hand-written test labels. |
| inputs / outputs | An initializer list of size_t labels becomes a Scope of VariableId values. |
| invariants | Set semantics remove duplicate labels. This helper supplies fixture values and does not infer scopes from either meta API. |
| ownership | The returned Scope owns its set nodes; the initializer list is borrowed only for the call. |
| failure | Set allocation failure propagates to main. Label validity is intentionally not checked here so tests can construct malformed metadata. |
| cost | One ordered-set insertion per supplied label, with ordinary test-only allocations outside production metadata counters. |
| Design | [docs/meta_decompositions.md](../../../../meta_decompositions.md), [exact paper reference](https://arxiv.org/html/2603.15465v2#S4.Thmtheorem3) |

## B0008

[Lines 43–47](../../../../../tests/unit/meta_decomposition_test.cpp#L43); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L43-L47:sha256:2c4ca8eeb7870ae5c9fc4f3a7ed6593111fb817e54a4a40c8b07974930533d32
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Keep one admitted catalog/query alongside the independently supplied occurrence scopes used by the tests. |
| inputs / outputs | Fixture contains owning Catalog, Query and vector&lt;Scope&gt; values built from the test input labels. |
| invariants | scopes preserves atom order and variable sets independently of construct/check output; later intentional alias changes retain compatible schemas. |
| ownership | The fixture owns all schema, query and scope containers and can be copied/moved without borrowing API scratch. |
| failure | Raw aggregate state has no implicit validation; query_for performs admission, and allocation/copy errors propagate. |
| cost | Construction/copy/destruction visits the fixture containers. This test representation is not charged by the production planner budget. |
| Design | [docs/meta_decompositions.md](../../../../meta_decompositions.md), [exact paper reference](https://arxiv.org/html/2603.15465v2#S2.SS2) |

## B0009

[Lines 48–50](../../../../../tests/unit/meta_decomposition_test.cpp#L48); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L48-L50:sha256:73f6f7de564bc1bf779557d12db3e7a6a8b68fd50210403ce87aa050ead852dc
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Document dense variable renaming and occurrence preservation in the fixture builder. |
| inputs / outputs | This adjacent comment describes how query_for translates arbitrary numeric test labels into admitted direct-CQ values. |
| invariants | Renaming may change numeric labels but preserves equality/incidence; equal scopes and table aliases must not deduplicate logical occurrences. |
| ownership | The comment creates no fixture or retained owner. |
| failure | No executable failure occurs here; the adjacent builder validates its resulting catalog/query. |
| cost | No runtime instructions are required for these explanatory comments. |
| Design | [docs/meta_decompositions.md](../../../../meta_decompositions.md), [exact paper reference](https://arxiv.org/html/2603.15465v2#S2.SS1) |

## B0010

[Lines 51–75](../../../../../tests/unit/meta_decomposition_test.cpp#L51); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L51-L75:sha256:553037cbc896ee823e517af275670b08bc83aae112986ee2427ba395cd26f052
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Build admitted direct-CQ fixtures from independent edge lists, with dense variables and one occurrence per input edge. |
| inputs / outputs | Input vector-of-variable-lists produces a Fixture containing catalog tables/columns, ordered atom terms and deduplicated per-occurrence Scope sets. |
| invariants | The sorted label map gives consistent dense IDs. Atom order is retained, repeated terms stay terms but scope members deduplicate, and empty edge lists remain available for explicit domain tests. |
| ownership | The builder owns new maps, schemas, atoms and scopes, moving them into the returned fixture; it does not retain the input list or any meta output. |
| failure | crown::validate rejects an accidentally invalid generated CQ before tests use it. Map/container allocation failures propagate to main rather than being swallowed. |
| cost | Finite test-only map/set/vector construction over the listed variables/terms, including admission. These costs and allocations are separate from Limits/Usage under test. |
| Design | [docs/meta_decompositions.md](../../../../meta_decompositions.md), [exact paper reference](https://arxiv.org/html/2603.15465v2#S2.SS1), [exact paper reference](https://arxiv.org/html/2603.15465v2#S2.SS2) |

## B0012

[Lines 77–82](../../../../../tests/unit/meta_decomposition_test.cpp#L77); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L77-L82:sha256:549045c74b9662f3b5c52a6ce2858fb219a9e11230355588c9b1563b470745b7
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Assemble one explicit expected or intentionally corrupted metadata node without invoking construction. |
| inputs / outputs | Hand-written occurrence, chi labels, kappa labels and optional parent become a Node value. |
| invariants | The helper does not repair or validate arguments; occurrence zero remains a present physical ID and absent occurrence remains a minor. |
| ownership | The result owns fresh chi/kappa sets; optional indices are copied scalar values. |
| failure | Container allocation failures propagate. Invalid parent/occurrence/domain values are deliberately representable for rejection tests. |
| cost | Two finite test scope constructions plus scalar assembly; no production reduction or budget query is used to derive expected fields. |
| Design | [docs/meta_decompositions.md](../../../../meta_decompositions.md), [exact paper reference](https://arxiv.org/html/2603.15465v2#S4.Thmtheorem3) |

## B0014

[Lines 84–86](../../../../../tests/unit/meta_decomposition_test.cpp#L84); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L84-L86:sha256:293dd4d2130f81fec596a5e3e75ba5055402b327ab81ec313f181fcdd34f75de
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Use the standard ordered-set inclusion algorithm for the test's containment predicates. |
| inputs / outputs | Two borrowed Scope sets produce whether large includes every variable in small. |
| invariants | Both sets use their normal sorted unique ordering. This helper does not call the production charged contains implementation. |
| ownership | The algorithm borrows iterators, creates no owning graph/scope and leaves both inputs unchanged. |
| failure | Missing containment returns false. The standard comparison over scalar IDs has no deliberate test exception path. |
| cost | Linear iterator comparisons in the supplied set lengths, with no production work/cell accounting. |
| Design | [docs/meta_decompositions.md](../../../../meta_decompositions.md), [exact paper reference](https://arxiv.org/html/2603.15465v2#S4.Thmtheorem3) |

## B0015

[Lines 87–91](../../../../../tests/unit/meta_decomposition_test.cpp#L87); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L87-L91:sha256:a6a49588122983968bd452f7013d5364f12f5af2e6964f2f74375c401518e461
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Explain why tests inspect fields and check variable-induced edge counts instead of accepting API success flags as authority. |
| inputs / outputs | This comment introduces inspect and identifies its Definition4.3 coverage/topology/interface/C4b/C5 expectations. |
| invariants | The independent RIP criterion uses connectedness in an already established tree; it does not replay the constructor's reduction trace. |
| ownership | No fixture, matrix or graph lifetime is created by the comment. |
| failure | Comments cannot establish correctness; failed expectations are enforced by inspect's explicit require calls. |
| cost | No executable cost in this region. The bounded test inspection below owns its actual scratch and scans. |
| Design | [docs/meta_decompositions.md](../../../../meta_decompositions.md), [exact paper reference](https://arxiv.org/html/2603.15465v2#S4.Thmtheorem3), [exact paper reference](https://arxiv.org/html/2603.15465v2#S2.SS2) |

## B0016

[Lines 92–162](../../../../../tests/unit/meta_decomposition_test.cpp#L92); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L92-L162:sha256:357ea98e6b112842d471c302e7cc6beb18d4c5ef360f4ce28634b82528086630
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Inspect raw graph fields independently of both meta success flags, using parent-walk ancestry and variable-induced forest edge counts. |
| inputs / outputs | A Fixture, a proposed nonempty Decomposition and diagnostic label either pass inspection or throw an explicit test failure. |
| invariants | Checks exact occurrence coverage/scopes, variable domain, unique minors, root/parents, reachability, RIP, actual outside kappa, parent cover/highest placement and equal-interface hubs. Topology is checked before indexing/walking. It does not independently enforce the newer whole-minor anchor rule; domain_cases tests that rule separately. |
| ownership | Inputs are borrowed. The test owns seen bits, minor/interface maps, an n-by-n ancestor matrix and temporary union/interface sets, releasing them normally or on exception. |
| failure | Any violated inspected property throws runtime_error. Invalid inputs are rejected before unsafe parent traversal; allocation failures propagate. Passing this finite inspection is not a formal proof or a complete candidate-family claim. |
| cost | Test-only quadratic ancestry storage plus repeated variable/node/set scans and bounded parent walks. No Limits grant applies to this independent oracle, and its cost is not a production performance claim. |
| Design | [docs/meta_decompositions.md](../../../../meta_decompositions.md), [exact paper reference](https://arxiv.org/html/2603.15465v2#S4.Thmtheorem3), [exact paper reference](https://arxiv.org/html/2603.15465v2#S2.SS2) |

## B0017

[Lines 163–165](../../../../../tests/unit/meta_decomposition_test.cpp#L163); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L163-L165:sha256:7853b2897846a218d3b471143334d6b4d81a29ccb6cf921d024beed611a020ab
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | State that exact-structure comparisons identify nodes semantically rather than requiring implementation node numbering. |
| inputs / outputs | This comment describes matching physical nodes by occurrence and minor nodes by chi in expect_structure. |
| invariants | Expected fields are hand-derived fixture data, not values copied from construct/check or an unchecked status flag. |
| ownership | No matching vector or owner is created by this comment region. |
| failure | The comment introduces no runtime failure; explicit comparisons below enforce the described expectations. |
| cost | No executable work is performed here. |
| Design | [docs/meta_decompositions.md](../../../../meta_decompositions.md), [exact paper reference](https://arxiv.org/html/2603.15465v2#S4.Thmtheorem3), [exact paper reference](https://arxiv.org/html/2603.15465v2#algorithm1) |

## B0018

[Lines 166–191](../../../../../tests/unit/meta_decomposition_test.cpp#L166); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L166-L191:sha256:f296e113f4419c594d08049b5a6afab916050a0a5986b3806ff93696543199c1
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Compare every chi, kappa, root identity and parent identity against a hand-written expected graph while allowing different node numbering. |
| inputs / outputs | Actual and trusted expected Decomposition values plus label pass or throw; a temporary expected-to-actual index vector records unique semantic matches. |
| invariants | Node counts agree; each expected occurrence/minor has exactly one actual match, matching chi/kappa. Parent and root comparisons use mapped identities rather than raw expected indices. |
| ownership | Both graphs are borrowed read-only; only the temporary matching vector is owned locally. |
| failure | Missing/ambiguous identities or mismatched fields fail explicitly. Expected fixture indices must themselves be well-formed and are independently inspected before this helper is used. |
| cost | Quadratic node matching plus scope comparisons and linear mapped-parent checks; test-only vector allocation is outside production Limits. |
| Design | [docs/meta_decompositions.md](../../../../meta_decompositions.md), [exact paper reference](https://arxiv.org/html/2603.15465v2#S4.Thmtheorem3), [exact paper reference](https://arxiv.org/html/2603.15465v2#algorithm1) |

## B0020

[Lines 193–193](../../../../../tests/unit/meta_decomposition_test.cpp#L193); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L193-L193:sha256:9b3bd131b3847c769461edfbee9054021931501012ad12399793d6902a773cdd
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Bundle a diagnostic name, admitted fixture and independent expected graph for a source-grounded case. |
| inputs / outputs | Case stores an owning string, Fixture and hand-written Decomposition consumed by the test loops. |
| invariants | The expected graph is not constructed by the production builder; its semantics are checked before comparing production output. |
| ownership | The Case owns all its diagnostic/fixture/expected containers; vector storage can move the bundle without borrowing a meta result. |
| failure | Aggregate assembly itself does not validate the expected graph. Container allocation/copy failures propagate. |
| cost | Finite test-fixture construction/copy/destruction; not a native planner primitive or per-update structure. |
| Design | [docs/meta_decompositions.md](../../../../meta_decompositions.md), [exact paper reference](https://arxiv.org/html/2603.15465v2#S4.Thmtheorem3), [exact paper reference](https://arxiv.org/html/2603.15465v2#algorithm1) |

## B0022

[Lines 195–251](../../../../../tests/unit/meta_decomposition_test.cpp#L195); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L195-L251:sha256:3237b0824151b447951cf7dc794d279c92a4906a332162219b5dc81b55bdc4c4
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Supply eleven hand-written structures covering paper examples and explicit adapter/reduction regressions. |
| inputs / outputs | No runtime input; returns Cases for reactivation, Example4.6, nonroot full-interface minor, scope-equal special/original, nested groups, duplicate aliases, singleton, three disconnected situations and Example4.4 highest parent. |
| invariants | Paper examples preserve their incidence under numeric renaming. Additional cases are hand-derived extensions/regressions, not verbatim claims of paper coverage. Expected parents/kappas are explicit; aliases retain separate atom indices and nested groups retain both minors. |
| ownership | The returned vector owns every fixture and expected graph; temporary fixture values move into it. The deliberate alias-table rewrite remains schema-compatible and is readmitted. |
| failure | Invalid fixture admission/allocation propagates; later inspect validates expected structures. This finite list does not prove Algorithm1 correctness, enumeration completeness or generalized-height optimality. |
| cost | Eleven small cold fixtures allocate their own schemas, scopes and expected graphs. Their work is test setup, independent of production metadata resource counters. |
| Design | [docs/meta_decompositions.md](../../../../meta_decompositions.md), [exact paper reference](https://arxiv.org/html/2603.15465v2#algorithm1), [exact paper reference](https://arxiv.org/html/2603.15465v2#S4.Thmtheorem4), [exact paper reference](https://arxiv.org/html/2603.15465v2#S4.Thmtheorem6), [exact paper reference](https://arxiv.org/html/2603.15465v2#S4.Thmtheorem3) |

## B0024

[Lines 253–264](../../../../../tests/unit/meta_decomposition_test.cpp#L253); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L253-L264:sha256:d9badd957c1ba885a588159d7e233ff3ea25bec23ea428eac086649cd183da2d
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Exercise positive construction and checking against independent hand-written structures. |
| inputs / outputs | The supplied Cases are inspected, constructed, inspected again and compared exactly; each hand-written expected graph is also passed directly to check. |
| invariants | Hand expectations are inspected before any production result. Constructed outputs must have complete status, an engaged graph, independently valid fields and the expected structure; a success flag alone never suffices. |
| ownership | Cases are borrowed. Each Build/Check and its owned graph exist only for the current iteration and are released before advancing. |
| failure | Any false expectation, unexpected stop, absent graph or rejected hand structure throws. Earlier failure prevents later cases from running; no report declares unexecuted cases passed. |
| cost | A fixed small fixture loop with independent inspections and both public APIs. Its repetitions are regression work, not an amortized performance experiment. |
| Design | [docs/meta_decompositions.md](../../../../meta_decompositions.md), [exact paper reference](https://arxiv.org/html/2603.15465v2#S4.Thmtheorem3), [exact paper reference](https://arxiv.org/html/2603.15465v2#algorithm1) |

## B0026

[Lines 266–270](../../../../../tests/unit/meta_decomposition_test.cpp#L266); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L266-L270:sha256:7502515bcf0ced5bed96b5c132946518403ca710d3d2b2a738dab276e45156db
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Require a constructor domain/classification stop and absence of a partial graph. |
| inputs / outputs | A fixture, explicitly expected Stop and label call construct and pass only when both expected status and empty optional agree. |
| invariants | The expected stop is authored by the caller, never derived from construct/check output. A noncomplete result must not expose partial metadata. |
| ownership | The fixture is borrowed and the temporary Build is locally owned/released. |
| failure | Wrong status or accidental graph publication throws an explicit test failure with expected/actual labels. |
| cost | One constructor invocation plus fixed status/optional checks; actual construction work uses its default finite grants. |
| Design | [docs/meta_decompositions.md](../../../../meta_decompositions.md), [exact paper reference](https://arxiv.org/html/2603.15465v2#S2.SS1), [exact paper reference](https://arxiv.org/html/2603.15465v2#algorithm1) |

## B0028

[Lines 272–298](../../../../../tests/unit/meta_decomposition_test.cpp#L272); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L272-L298:sha256:4f25aaecb336d6a4ba6783a245071eab662344b3ea72a6f09959d2ac58a3c0c1
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Check explicit provider-domain stops and reject a cyclic body hidden by an unguarded artificial minor. |
| inputs / outputs | Hand-built empty/nullary/triangle fixtures feed construct/check; one explicit triangle proposal has a root scope containing all three variables. |
| invariants | Empty and variable-free atoms stop from both APIs regardless of a superficially valid singleton graph. Triangle acyclicity is independently false under GYO. The triangle union-minor otherwise meets literal tree/interface rules but must fail the stronger original-scope anchor condition. |
| ownership | All fixtures/proposals/results are test-owned local values; no core engine state or fallback candidate provider is changed. |
| failure | Unexpected domain status, accepted unguarded minor, published partial graph or wrong triangle classification fails explicitly. These provider stops do not assert general engine unsupportedness. |
| cost | Small fixed cases with ordinary allocation, validation and default bounded calls. No update-path or general recognition-cost theorem is measured. |
| Design | [docs/meta_decompositions.md](../../../../meta_decompositions.md), [exact paper reference](https://arxiv.org/html/2603.15465v2#S2.SS1), [exact paper reference](https://arxiv.org/html/2603.15465v2#S2.SS2), [exact paper reference](https://arxiv.org/html/2603.15465v2#S4.Thmtheorem3), [exact paper reference](https://arxiv.org/html/2603.15465v2#algorithm1) |

## B0030

[Lines 300–304](../../../../../tests/unit/meta_decomposition_test.cpp#L300); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L300-L304:sha256:e46cafa01deeec14ca2a0fd2b1ee316ed055b4b8c2926dead2cc287b957d3f5b
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Require independent checker rejection of one deliberately malformed graph. |
| inputs / outputs | A valid nonempty fixture, borrowed malformed Decomposition and label produce a Check that must be invalid_decomposition with valid=false. |
| invariants | The expected failure is authored from the mutation; a limit/domain stop cannot masquerade as successful structural rejection. |
| ownership | Inputs stay caller-owned and unchanged; the scalar Check and any internal scratch are temporary. |
| failure | Accepted malformed state or an unexpected stop throws runtime_error with a diagnostic label. |
| cost | One default-bounded checker invocation plus fixed result checks, used only in the finite regression suite. |
| Design | [docs/meta_decompositions.md](../../../../meta_decompositions.md), [exact paper reference](https://arxiv.org/html/2603.15465v2#S4.Thmtheorem3), [exact paper reference](https://arxiv.org/html/2603.15465v2#A3.SS4) |

## B0032

[Lines 306–342](../../../../../tests/unit/meta_decomposition_test.cpp#L306); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L306-L342:sha256:d633c481abaee7fdaf521443053df501c3b0c6081e2954d33d8448becd9f984c
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Mutate independently written graphs to test parent, scope, interface, identity, domain, canonical-minor and highest-parent rejection. |
| inputs / outputs | The source-grounded Case list supplies a rich full-interface-minor graph and Example4.4; each local mutation is passed to reject. |
| invariants | Each mutation starts from a fresh good graph, avoiding accidental dependence on earlier corruptions. The missing-x-hub graph retains topology/RIP/interfaces but violates C5; moving Example4.4 R5 lower violates C4b despite an ordinary valid join-tree attachment. |
| ownership | A local owning bad graph is repeatedly copied/replaced; baseline fixtures and expected graphs remain unchanged. |
| failure | All twenty malformed cases must return invalid_decomposition/false rather than crash, time out, exhaust a grant or claim validity. |
| cost | Finite small-graph copies and checker calls, with no production recovery framework added. This targeted mutation set is not exhaustive fuzzing or a formal soundness proof. |
| Design | [docs/meta_decompositions.md](../../../../meta_decompositions.md), [exact paper reference](https://arxiv.org/html/2603.15465v2#S4.Thmtheorem3), [exact paper reference](https://arxiv.org/html/2603.15465v2#S4.Thmtheorem4), [exact paper reference](https://arxiv.org/html/2603.15465v2#A3.SS4) |

## B0034

[Lines 344–347](../../../../../tests/unit/meta_decomposition_test.cpp#L344); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L344-L347:sha256:456c6fb3350ee6b3c31761fc8127f6af0a887a50b2c3c0be80328141d1443920
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Check that every reported selected counter remains within its corresponding granted limit. |
| inputs / outputs | Borrowed Usage, Limits and label pass only if work, peak nodes and cumulative scope_cells do not exceed grants. |
| invariants | Counter containment is distinct from semantic correctness and does not show that all CPU, bytes, capacity or scratch allocation were counted. |
| ownership | Only scalar counters are borrowed; the helper owns no resource account or budget authority. |
| failure | Any exceeded reported grant fails explicitly; it cannot repair counters or grant additional resources. |
| cost | Three scalar comparisons plus diagnostic handling; any message construction belongs to test cost. |
| Design | [docs/meta_decompositions.md](../../../../meta_decompositions.md) |

## B0035

[Lines 348–351](../../../../../tests/unit/meta_decomposition_test.cpp#L348); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L348-L351:sha256:64ff18200325a380ae2138174d4e34e12ef8077b23e41a51d5ee3ba79bdc2a96
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Document precisely what the exact/one-short resource regressions establish. |
| inputs / outputs | This comment introduces budgets and distinguishes selected work, peak node count and cumulative explicit scope cells from CPU/bytes. |
| invariants | Baseline Usage measures a grant boundary only; it never supplies expected semantic truth or an asymptotic complexity estimate. |
| ownership | The documentation creates no budget, allocation authority or test fixture owner. |
| failure | No failure is raised by the comment; the following function enforces the measured boundaries explicitly. |
| cost | No executable work in this region; it disclaims total-CPU and allocator-byte coverage rather than hiding those costs. |
| Design | [docs/meta_decompositions.md](../../../../meta_decompositions.md) |

## B0036

[Lines 352–398](../../../../../tests/unit/meta_decomposition_test.cpp#L352); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L352-L398:sha256:f63599cbea66d240be01389991ea7d8db59d91d20bfbe8ff8c65cf04bd331324
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Test exact, individually one-short and individually zero grants for constructor and checker without using measured usage as a semantic oracle. |
| inputs / outputs | A hand-derived positive Case supplies input and expected graph. Successful baseline counters define exact grants; each dimension is then independently reduced while the other two stay funded. |
| invariants | Baseline dimensions are nonzero. Exact construction must still match the independent expected graph; exact checking must accept that graph. Every smaller/zero grant has its specific limit stop, no graph/valid claim and usage within the grant. |
| ownership | Each Build owns only its temporary returned graph; Limits/Usage/Check are local scalar values. Repeated calls borrow the same immutable fixture/expectation. |
| failure | Any boundary mismatch, wrong stop, partial publication or reported overspend fails explicitly. Validation/allocation exceptions are not normalized into a passing limit result. |
| cost | A fixed number of cold calls over one small fixture. This measures selected charge boundaries under current deterministic code, not RSS, elapsed time, all allocations or paper complexity. |
| Design | [docs/meta_decompositions.md](../../../../meta_decompositions.md) |

## B0038

[Lines 400–444](../../../../../tests/unit/meta_decomposition_test.cpp#L400); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L400-L444:sha256:cec14ecf917779adc978d8a249d15bf3c9152775969def791be1600f67000318
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Compare metadata construction against an algorithmically separate GYO acyclicity decision on a bounded exhaustive multiset corpus. |
| inputs / outputs | Enumerates all 3,875 multisets of 1..4 nonempty scopes over four variables, invoking forward/reverse occurrence orders for 7,750 calls. Existing gyo_reduce on fixture.scopes supplies expected acyclicity before either meta API is consulted. |
| invariants | Acyclic cases require complete graph publication, independent field inspection and checker acceptance; cyclic cases require cyclic with no graph. The two orderings may coincide and do not cover all occurrence permutations. GYO independence is from the meta algorithms, not from the whole library. |
| ownership | Masks, edge lists, fixtures, Builds and Checks are owned per loop iteration; no results/cache are shared between queries. |
| failure | Any GYO disagreement or invalid graph fails with count/code/order for reproduction. The final guard checks 7,750 invocations and both classes; counts do not prove unbounded correctness, candidate-family enumeration, CROWN admission or minimum height. |
| cost | Finite enumeration up to 15^4 raw codes with multiset filtering, then 7,750 independent GYO/construction/inspection runs. Test runtime/allocations are outside production Usage; no benchmark or total-CPU bound is inferred. |
| Design | [docs/meta_decompositions.md](../../../../meta_decompositions.md), [exact paper reference](https://arxiv.org/html/2603.15465v2#S2.SS2), [exact paper reference](https://arxiv.org/html/2603.15465v2#algorithm1) |

## B0039

[Lines 445–446](../../../../../tests/unit/meta_decomposition_test.cpp#L445); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L445-L446:sha256:c929980d95efc152dc886ac42af0f045075441dd18a8f886364828ead327bbd3
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Close the test helper namespace before the process entry point. |
| inputs / outputs | The anonymous namespace ends after the corpus helper; main remains the standalone test executable entry point. |
| invariants | Helper linkage remains internal. The closure neither skips checks nor initializes a global test result. |
| ownership | Namespace closure owns/destroys no live fixture or helper-local container. |
| failure | No runtime failure or success status is produced by this brace. |
| cost | No executable work is associated with the namespace boundary. |
| Design | [docs/meta_decompositions.md](../../../../meta_decompositions.md) |

## B0040

[Lines 447–460](../../../../../tests/unit/meta_decomposition_test.cpp#L447); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L447-L460:sha256:36d8e711beb5a7878b4eeeb946544aa8573daf11d12d00043a2c00fc6a1a01a8
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Run the complete positive/domain/mutation/budget/corpus suite and expose failure through the process exit code. |
| inputs / outputs | No command-line arguments; main creates Cases and runs helpers in order, returning zero after all finish or one after a standard exception. |
| invariants | Explicit require checks remain enabled in optimized builds. Success means this finite suite completed; early failure leaves later checks unexecuted and establishes no global proof. |
| ownership | main owns the Case vector and transient diagnostics; normal returns and exception unwinding release fixture/metadata containers. |
| failure | A caught std::exception is printed to stderr and yields nonzero. Unhandled nonstandard failures do not become success; no exception is swallowed to continue with corrupted expectations. |
| cost | Cold test setup plus all invoked finite suites and diagnostic I/O. The driver itself does not meter or benchmark production update performance. |
| Design | [docs/meta_decompositions.md](../../../../meta_decompositions.md), [exact paper reference](https://arxiv.org/html/2603.15465v2#algorithm1), [exact paper reference](https://arxiv.org/html/2603.15465v2#S4.Thmtheorem3) |
