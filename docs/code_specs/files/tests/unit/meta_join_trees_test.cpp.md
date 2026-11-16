# `tests/unit/meta_join_trees_test.cpp` — block usage map

[Source](../../../../../tests/unit/meta_join_trees_test.cpp) · [Source index](../../../README.md) · [Subsystem contracts](../../../subsystem_contracts.md) · [Reviewed primitives](../../../primitives.md)

Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection.

Snapshot SHA-256: `82b4cd123269158eb1f1665da90718f40157313f29f028d6c57ead677296eceb`. 592 lines partitioned into 64 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [tests](../../../subsystem_contracts.md#tests). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/code_review.md](../../../../code_review.md), [docs/reference_fuzz.md](../../../../reference_fuzz.md), [docs/task_ledger.md](../../../../task_ledger.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–25](../../../../../tests/unit/meta_join_trees_test.cpp#L1) | Imports dependencies; declares namespace scope; declares aliases; declares values/defaults or compile-time conditions. |  · [reviewed contract](#b0001) |
| [B0002 · 26–28](../../../../../tests/unit/meta_join_trees_test.cpp#L26) | Callable definition: void require(bool condition, const std::string& message) | calls std::runtime_error; guard void require(bool condition, const std::string& message) { · [reviewed contract](#b0002) |
| [B0003 · 29–29](../../../../../tests/unit/meta_join_trees_test.cpp#L29) | Explanatory comments or spacing. |  |
| [B0004 · 30–43](../../../../../tests/unit/meta_join_trees_test.cpp#L30) | Callable definition: const char* stop_name(meta::EnumerationStop stop) | calls ; returns @; @ · [reviewed contract](#b0004) |
| [B0005 · 44–44](../../../../../tests/unit/meta_join_trees_test.cpp#L44) | Explanatory comments or spacing. |  |
| [B0006 · 45–49](../../../../../tests/unit/meta_join_trees_test.cpp#L45) | Callable definition: Edges canonical(Edges edges) | calls std::swap, std::sort, begin, end; returns edges; 1 loop sites · [reviewed contract](#b0006) |
| [B0007 · 50–52](../../../../../tests/unit/meta_join_trees_test.cpp#L50) | Explanatory comments or spacing. | source comment (unverified): // Expected-family keys retain atom labels and a physical root. An undirected · [reviewed contract](#b0007) |
| [B0008 · 53–57](../../../../../tests/unit/meta_join_trees_test.cpp#L53) | Type/record definition: struct Key | source comment (unverified): // Expected-family keys retain atom labels and a physical root. An undirected · [reviewed contract](#b0008) |
| [B0009 · 58–59](../../../../../tests/unit/meta_join_trees_test.cpp#L58) | declares aliases; declares values/defaults or compile-time conditions. |  · [reviewed contract](#b0009) |
| [B0010 · 60–65](../../../../../tests/unit/meta_join_trees_test.cpp#L60) | Callable definition: std::string describe(const Key& key) | calls str; returns text.str(); 1 loop sites · [reviewed contract](#b0010) |
| [B0011 · 66–66](../../../../../tests/unit/meta_join_trees_test.cpp#L66) | Explanatory comments or spacing. |  |
| [B0012 · 67–74](../../../../../tests/unit/meta_join_trees_test.cpp#L67) | Callable definition: void same_keys(const Keys& actual, const Keys& expected, const std::string& label) | calls contains, describe, std::runtime_error, std::to_string; 2 loop sites · [reviewed contract](#b0012) |
| [B0013 · 75–77](../../../../../tests/unit/meta_join_trees_test.cpp#L75) | Explanatory comments or spacing. | source comment (unverified): // Independent graph oracle: breadth-first reachability restricted to allowed · [reviewed contract](#b0013) |
| [B0014 · 78–92](../../../../../tests/unit/meta_join_trees_test.cpp#L78) | Callable definition: bool connected(const std::vector&lt;bool&gt;& allowed, const Edges& edges) | calls std::find, begin, end, seen; returns true; seen == allowed; growth push_back; 2 loop sites; source comment (unverified): // Independent graph oracle: breadth-first reachability restricted to allowed · [reviewed contract](#b0014) |
| [B0015 · 93–93](../../../../../tests/unit/meta_join_trees_test.cpp#L93) | Explanatory comments or spacing. |  |
| [B0016 · 94–98](../../../../../tests/unit/meta_join_trees_test.cpp#L94) | Callable definition: bool tree(std::size_t count, const Edges& edges) | calls size, connected; returns false; false; 1 loop sites · [reviewed contract](#b0016) |
| [B0017 · 99–101](../../../../../tests/unit/meta_join_trees_test.cpp#L99) | Explanatory comments or spacing. | source comment (unverified): // Ordinary join-tree definition, P3v2 §2.2 (PDF pp.4–5): every variable's · [reviewed contract](#b0017) |
| [B0018 · 102–111](../../../../../tests/unit/meta_join_trees_test.cpp#L102) | Callable definition: bool running_intersection(const std::vector&lt;Scope&gt;& scopes, const Edges& edges) | calls insert, begin, end, push_back; returns false; true; growth insert, push_back; 3 loop sites; source comment (unverified): // Ordinary join-tree definition, P3v2 §2.2 (PDF pp.4–5): every variable's · [reviewed contract](#b0018) |
| [B0019 · 112–116](../../../../../tests/unit/meta_join_trees_test.cpp#L112) | Explanatory comments or spacing. | source comment (unverified): // Exhaust all labelled Prüfer codes, n&lt;=5. Decode by absence from the remaining · [reviewed contract](#b0019) |
| [B0020 · 117–146](../../../../../tests/unit/meta_join_trees_test.cpp#L117) | Callable definition: Trees prufer_trees(std::size_t count) | calls require, code, insert, size; guard require(count &gt;= 1 && count &lt;= 5, "Pruefer oracle exceeds its explicit small domain");; returns {Edges{}}; std::find(suffix, code.end(), vertex) == code.end(); growth emplace_back, insert; 5 loop sites; source comment (unverified): // Exhaust all labelled Prüfer codes, n&lt;=5. Decode by absence from the remaining · [reviewed contract](#b0020) |
| [B0021 · 147–149](../../../../../tests/unit/meta_join_trees_test.cpp#L147) | Explanatory comments or spacing. | source comment (unverified): // This second topology oracle enumerates subsets of complete-graph edges, · [reviewed contract](#b0021) |
| [B0022 · 150–163](../../../../../tests/unit/meta_join_trees_test.cpp#L150) | Callable definition: Trees edge_subset_trees(std::size_t count) | calls require, emplace_back, size, std::popcount; guard require(count &gt;= 1 && count &lt;= 5, "edge-subset oracle exceeds its small domain");; returns trees; growth emplace_back, insert, push_back; 4 loop sites; source comment (unverified): // This second topology oracle enumerates subsets of complete-graph edges, · [reviewed contract](#b0022) |
| [B0023 · 164–165](../../../../../tests/unit/meta_join_trees_test.cpp#L164) | declares aliases; declares values/defaults or compile-time conditions. |  · [reviewed contract](#b0023) |
| [B0024 · 166–178](../../../../../tests/unit/meta_join_trees_test.cpp#L166) | Callable definition: Universe checked_universe() | calls prufer_trees, require, edge_subset_trees, size; guard require(result\[count\] == edge_subset_trees(count), "Pruefer and edge-subset topology oracles disagr…; returns result; 1 loop sites · [reviewed contract](#b0024) |
| [B0025 · 179–179](../../../../../tests/unit/meta_join_trees_test.cpp#L179) | Explanatory comments or spacing. |  |
| [B0026 · 180–185](../../../../../tests/unit/meta_join_trees_test.cpp#L180) | Callable definition: Trees ordinary_oracle(const std::vector&lt;Scope&gt;& scopes, const Universe& universe) | calls require, empty, size, running_intersection; guard require(!scopes.empty() && scopes.size() &lt;= 5, "ordinary oracle requires one to five atoms");; returns expected; growth insert; 1 loop sites · [reviewed contract](#b0026) |
| [B0027 · 186–186](../../../../../tests/unit/meta_join_trees_test.cpp#L186) | Explanatory comments or spacing. |  |
| [B0028 · 187–191](../../../../../tests/unit/meta_join_trees_test.cpp#L187) | Callable definition: Keys all_roots(std::size_t count, const Trees& trees) | calls insert; returns result; growth insert; 2 loop sites · [reviewed contract](#b0028) |
| [B0029 · 192–192](../../../../../tests/unit/meta_join_trees_test.cpp#L192) | Explanatory comments or spacing. |  |
| [B0030 · 193–193](../../../../../tests/unit/meta_join_trees_test.cpp#L193) | Type/record definition: struct Fixture |  · [reviewed contract](#b0030) |
| [B0031 · 194–196](../../../../../tests/unit/meta_join_trees_test.cpp#L194) | Explanatory comments or spacing. | source comment (unverified): // The supplied incidence lists determine expected scopes before any meta API. · [reviewed contract](#b0031) |
| [B0032 · 197–220](../../../../../tests/unit/meta_join_trees_test.cpp#L197) | Callable definition: Fixture query_for(const std::vector&lt;std::vector&lt;std::size_t&gt;&gt;& input) | calls emplace, size, push_back, std::to_string; returns fixture; growth emplace, emplace_back, insert, push_back; 5 loop sites; source comment (unverified): // The supplied incidence lists determine expected scopes before any meta API. · [reviewed contract](#b0032) |
| [B0033 · 221–221](../../../../../tests/unit/meta_join_trees_test.cpp#L221) | Explanatory comments or spacing. |  |
| [B0034 · 222–226](../../../../../tests/unit/meta_join_trees_test.cpp#L222) | Callable definition: meta::Decomposition metadata_for(const Fixture& fixture, const std::string& label) | calls meta::construct, require, std::move; guard require(built.stop == meta::Stop::complete && built.decomposition, label + ": metadata construction…; returns std::move(*built.decomposition) · [reviewed contract](#b0034) |
| [B0035 · 227–230](../../../../../tests/unit/meta_join_trees_test.cpp#L227) | Explanatory comments or spacing. | source comment (unverified): // Inspect every returned parent vector independently, before forming its key. · [reviewed contract](#b0035) |
| [B0036 · 231–251](../../../../../tests/unit/meta_join_trees_test.cpp#L231) | Callable definition: Key inspect(const meta::JoinTree& actual, const Fixture& fixture, const std::string& label) | calls size, require, emplace_back, canonical; guard require(actual.parent.size() == count && actual.root &lt; count, label + ": wrong atom count or root");; returns {actual.root, std::move(edges)}; growth emplace_back; 3 loop sites; source comment (unverified): // Inspect every returned parent vector independently, before forming its key. · [reviewed contract](#b0036) |
| [B0037 · 252–252](../../../../../tests/unit/meta_join_trees_test.cpp#L252) | Explanatory comments or spacing. |  |
| [B0038 · 253–259](../../../../../tests/unit/meta_join_trees_test.cpp#L253) | Callable definition: void within(const meta::Enumeration& run, const meta::EnumerationLimits& limits, const std::string& label) | calls require, size; guard require(run.usage.work &lt;= limits.work && run.usage.fragments &lt;= limits.fragments && run.usage.cells… · [reviewed contract](#b0038) |
| [B0039 · 260–260](../../../../../tests/unit/meta_join_trees_test.cpp#L260) | Explanatory comments or spacing. |  |
| [B0040 · 261–271](../../../../../tests/unit/meta_join_trees_test.cpp#L261) | Callable definition: std::vector&lt;Key&gt; output_keys(const meta::Enumeration& run, const Fixture& fixture, const std::string& label) | calls inspect, insert, std::runtime_error, describe; returns result; growth insert, push_back; 1 loop sites · [reviewed contract](#b0040) |
| [B0041 · 272–272](../../../../../tests/unit/meta_join_trees_test.cpp#L272) | Explanatory comments or spacing. |  |
| [B0042 · 273–279](../../../../../tests/unit/meta_join_trees_test.cpp#L273) | Callable definition: void complete_family(const meta::Enumeration& run, const Fixture& fixture, const Keys& expected, const std::string& label) | calls require, stop_name, output_keys, same_keys; guard require(run.metadata.stop == meta::Stop::complete && run.metadata.valid, label + ": metadata not ad… · [reviewed contract](#b0042) |
| [B0043 · 280–280](../../../../../tests/unit/meta_join_trees_test.cpp#L280) | Explanatory comments or spacing. |  |
| [B0044 · 281–281](../../../../../tests/unit/meta_join_trees_test.cpp#L281) | Type/record definition: struct Case |  · [reviewed contract](#b0044) |
| [B0045 · 282–282](../../../../../tests/unit/meta_join_trees_test.cpp#L282) | Explanatory comments or spacing. |  |
| [B0046 · 283–336](../../../../../tests/unit/meta_join_trees_test.cpp#L283) | Callable definition: std::vector&lt;Case&gt; literal_cases(const Universe& universe) | calls push_back, query_for, validate, std::move; guard require(endpoints.size() == 20 && variants.size() == 45, "hand-derived Cartesian/variant counts dis…; returns cases; growth insert, push_back; 2 loop sites; source comment (unverified): // Full-interface nonroot minor needs a typed external parent. Removing its · [reviewed contract](#b0046) |
| [B0047 · 337–339](../../../../../tests/unit/meta_join_trees_test.cpp#L337) | Explanatory comments or spacing. | source comment (unverified): // Metadata node indices are separate from atom labels. Reverse only the former · [reviewed contract](#b0047) |
| [B0048 · 340–349](../../../../../tests/unit/meta_join_trees_test.cpp#L340) | Callable definition: meta::Decomposition reversed_metadata(const meta::Decomposition& original) | calls size; returns result; 1 loop sites; source comment (unverified): // Metadata node indices are separate from atom labels. Reverse only the former · [reviewed contract](#b0048) |
| [B0049 · 350–350](../../../../../tests/unit/meta_join_trees_test.cpp#L350) | Explanatory comments or spacing. |  |
| [B0050 · 351–373](../../../../../tests/unit/meta_join_trees_test.cpp#L351) | Callable definition: void literal_families(const std::vector&lt;Case&gt;& cases, const Universe& universe) | calls size, all_roots, require, same_keys; guard require(expected.size() == rooted_counts\[i\], test.label + ": literal rooted count changed");; 1 loop sites; source comment (unverified): // Ordinary body coverage is independent of the later CROWN/head admission. · [reviewed contract](#b0050) |
| [B0051 · 374–374](../../../../../tests/unit/meta_join_trees_test.cpp#L374) | Explanatory comments or spacing. |  |
| [B0052 · 375–421](../../../../../tests/unit/meta_join_trees_test.cpp#L375) | Callable definition: void metadata_controls(const Case& test) | calls metadata_for, size, meta::enumerate, require; guard require(run.stop == meta::EnumerationStop::invalid_metadata && !run.metadata.valid && run.trees.emp…; 2 loop sites · [reviewed contract](#b0052) |
| [B0053 · 422–422](../../../../../tests/unit/meta_join_trees_test.cpp#L422) | Explanatory comments or spacing. |  |
| [B0054 · 423–430](../../../../../tests/unit/meta_join_trees_test.cpp#L423) | Callable definition: void valid_prefix(const meta::Enumeration& run, const Fixture& fixture, const std::vector&lt;Key&gt;& baseline, const meta::Enumeration… | calls require, within, output_keys, size; guard require(run.metadata.stop == meta::Stop::complete && run.metadata.valid, label + ": metadata grant … · [reviewed contract](#b0054) |
| [B0055 · 431–433](../../../../../tests/unit/meta_join_trees_test.cpp#L431) | Explanatory comments or spacing. | source comment (unverified): // These budgets count selected checkpoints, cumulative fragments/vector cells · [reviewed contract](#b0055) |
| [B0056 · 434–477](../../../../../tests/unit/meta_join_trees_test.cpp#L434) | Callable definition: void expansion_limits(const Case& test) | calls metadata_for, meta::enumerate, all_roots, size; guard require(keys.size() &gt; 1 && baseline.usage.work && baseline.usage.fragments && baseline.usage.cells,; 2 loop sites; source comment (unverified): // These budgets count selected checkpoints, cumulative fragments/vector cells · [reviewed contract](#b0056) |
| [B0057 · 478–480](../../../../../tests/unit/meta_join_trees_test.cpp#L478) | Explanatory comments or spacing. | source comment (unverified): // A canonical root is sufficient for inverse fibers. This mode must preserve · [reviewed contract](#b0057) |
| [B0058 · 481–505](../../../../../tests/unit/meta_join_trees_test.cpp#L481) | Callable definition: void canonical_families(const std::vector&lt;Case&gt;& cases) | calls metadata_for, size, meta::enumerate, require; guard require(run.stop == meta::EnumerationStop::complete && !run.all_roots && run.trees.size() == test.e…; growth insert; 3 loop sites; source comment (unverified): // A canonical root is sufficient for inverse fibers. This mode must preserve · [reviewed contract](#b0058) |
| [B0059 · 506–508](../../../../../tests/unit/meta_join_trees_test.cpp#L506) | Explanatory comments or spacing. | source comment (unverified): // Literal Definition4.3 permits this layout, but Algorithm1 minor-first · [reviewed contract](#b0059) |
| [B0060 · 509–526](../../../../../tests/unit/meta_join_trees_test.cpp#L509) | Callable definition: void noncanonical_parenting(const Universe& universe) | calls query_for, require, meta::check, all_roots; guard require(meta::check(f.catalog,f.query,m).valid,"noncanonical literal no longer satisfies structural…; source comment (unverified): // Literal Definition4.3 permits this layout, but Algorithm1 minor-first · [reviewed contract](#b0060) |
| [B0061 · 527–527](../../../../../tests/unit/meta_join_trees_test.cpp#L527) | Explanatory comments or spacing. |  |
| [B0062 · 528–574](../../../../../tests/unit/meta_join_trees_test.cpp#L528) | Callable definition: void exhaustive_families(const Universe& universe) | calls masks, std::is_sorted, begin, end; guard require(built.stop == meta::Stop::cyclic && !built.decomposition, label + ": no ordinary join tree …; growth push_back; 7 loop sites; source comment (unverified): // All 3,875 multisets of 1..4 nonempty scopes over 4 variables. Forward/reverse · [reviewed contract](#b0062) |
| [B0063 · 575–576](../../../../../tests/unit/meta_join_trees_test.cpp#L575) | Closes surrounding scope/type. | source comment (unverified): // namespace · [reviewed contract](#b0063) |
| [B0064 · 577–592](../../../../../tests/unit/meta_join_trees_test.cpp#L577) | Callable definition: int main() | calls checked_universe, literal_cases, literal_families, metadata_controls; returns 0; 1 · [reviewed contract](#b0064) |

## B0001

[Lines 1–25](../../../../../tests/unit/meta_join_trees_test.cpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L1-L25:sha256:ca2481a7e5c5b60754813c448f18fb7883fff1133990b5f7f9dbae1ec3d62523
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Import the ordinary enumeration API and define local test graph/container names. |
| inputs / outputs | Includes supply standard containers, bit operations and diagnostics; namespace aliases bind Scope, meta, Edge, Edges and Trees. |
| invariants | Helpers have translation-unit linkage. An Edge uses atom indices and Trees retains labelled undirected edge vectors; no meta family is accepted by these aliases. |
| ownership | Directives/aliases open no runtime owner or cross-test cache; later concrete containers own their allocations. |
| failure | Missing headers or incompatible declarations fail compilation, not a runtime recovery path. |
| cost | Build-time parsing only. This region contributes no native update hook or planner execution. |
| Design | [docs/meta_candidate_adapter.md](../../../../meta_candidate_adapter.md), [exact paper reference](https://arxiv.org/html/2603.15465v2#S2.SS2) |

## B0002

[Lines 26–28](../../../../../tests/unit/meta_join_trees_test.cpp#L26); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L26-L28:sha256:1e93bb10853211102ced622e7cf5fe087a0765e280eda599fcc6f21b46cf8385
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Enforce test expectations in optimized and debug builds alike. |
| inputs / outputs | A boolean condition and diagnostic string return normally or throw runtime_error. |
| invariants | Checks remain active under NDEBUG; the helper does not calculate an expected family or treat a report flag as proof. |
| ownership | The message is borrowed on success and copied into the owning exception on failure. |
| failure | False conditions throw to main; allocation/diagnostic exceptions propagate normally. |
| cost | One branch after argument evaluation; caller-created diagnostic strings and failure unwinding retain their ordinary costs. |
| Design | [docs/meta_candidate_adapter.md](../../../../meta_candidate_adapter.md) |

## B0004

[Lines 30–43](../../../../../tests/unit/meta_join_trees_test.cpp#L30); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L30-L43:sha256:044262f678bcd0036c8765585793f574e8d291dbf9087593d876f4ad07c8818e
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Render enumeration stops in actionable test diagnostics. |
| inputs / outputs | EnumerationStop, including the added noncanonical_metadata result, produces a pointer to a static label, with unknown as fallback. |
| invariants | The switch names results only; it neither validates metadata nor infers missing candidate families. |
| ownership | Returned strings are borrowed static literals and require no owning allocation. |
| failure | Unknown values remain visible diagnostically rather than being converted into complete. |
| cost | A fixed enum switch with no graph scans or dynamic string creation in this helper. |
| Design | [docs/meta_candidate_adapter.md](../../../../meta_candidate_adapter.md) |

## B0006

[Lines 45–49](../../../../../tests/unit/meta_join_trees_test.cpp#L45); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L45-L49:sha256:5cc970f3b8a93c3720a154134a526d296003276a028c0d521b2e3572ad697677
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Canonicalize undirected edge endpoint/order representation while preserving every supplied edge. |
| inputs / outputs | An owning Edges value returns with smaller endpoint first and its vector sorted lexicographically. |
| invariants | Atom labels remain unchanged. Duplicate edges are not erased, so normalization cannot silently repair an invalid graph. |
| ownership | The function mutates its by-value vector and returns that owned storage; callers choose whether to copy or move their input. |
| failure | No validity check is performed here; malformed endpoints remain for the graph/output validators to reject. |
| cost | Linear endpoint normalization plus sorting over the small test edge vector; no production Usage charges apply. |
| Design | [docs/meta_candidate_adapter.md](../../../../meta_candidate_adapter.md), [exact paper reference](https://arxiv.org/html/2603.15465v2#S2.SS2) |

## B0007

[Lines 50–52](../../../../../tests/unit/meta_join_trees_test.cpp#L50); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L50-L52:sha256:1cc6312cf4897a702c42d7152df06daac8e80733b428b3c604130ee21965b020
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Document the labelled root/edge key and the exclusion of minor identities from ordinary outputs. |
| inputs / outputs | The comment introduces Key as an undirected ordinary tree plus one physical root. |
| invariants | A rooted key fixes parent orientation uniquely only after topology has been validated; scope equality must not merge occurrence labels. |
| ownership | The comment creates no key or graph owner. |
| failure | No executable failure occurs here; inspect and key comparisons enforce the stated representation. |
| cost | No runtime work is performed by this documentation region. |
| Design | [docs/meta_candidate_adapter.md](../../../../meta_candidate_adapter.md), [exact paper reference](https://arxiv.org/html/2603.15465v2#S2.SS2), [exact paper reference](https://arxiv.org/html/2603.15465v2#A3.SS1.SSS3) |

## B0008

[Lines 53–57](../../../../../tests/unit/meta_join_trees_test.cpp#L53); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L53-L57:sha256:745c3c103cde1e3834c29b0b2020539afbbcf68336385e772eab2598e637ce55
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Represent exact rooted ordinary topology for set equality and duplicate detection. |
| inputs / outputs | Key stores a physical root index and an owning canonical undirected edge vector; default comparison orders both fields. |
| invariants | Labels are original atom positions. Different roots or labelled edges remain distinct even for aliases/equal scopes. |
| ownership | The key owns its vector; copying duplicates edges and moving transfers them. |
| failure | Raw keys are not self-validating. Container allocation/copy failures propagate; inspect supplies admitted topology before actual output keys are used. |
| cost | Root comparison is scalar; edge comparison/copy/destruction scales with the edge vector. Test keys are outside the production metadata budget. |
| Design | [docs/meta_candidate_adapter.md](../../../../meta_candidate_adapter.md), [exact paper reference](https://arxiv.org/html/2603.15465v2#S2.SS2), [exact paper reference](https://arxiv.org/html/2603.15465v2#A3.SS1.SSS3) |

## B0009

[Lines 58–59](../../../../../tests/unit/meta_join_trees_test.cpp#L58); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L58-L59:sha256:5e476ae74f0db0635dfc34ae652c7610ab216c0b1e812e505a63e7e28dd5559b
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Define the ordered set type used for exact rooted-family comparisons. |
| inputs / outputs | Keys aliases set&lt;Key&gt;, using Key comparison to retain one record per labelled topology/root pair. |
| invariants | Set uniqueness is a diagnostic representation; output_keys separately rejects duplicates before set insertion could hide them. |
| ownership | The alias itself owns nothing; instantiated Keys values own their tree nodes and Key vectors. |
| failure | No runtime failure occurs at declaration; later set allocation/comparison costs and failures belong to their callers. |
| cost | Compile-time aliasing only; actual set insertion/comparison is not claimed constant-time. |
| Design | [docs/meta_candidate_adapter.md](../../../../meta_candidate_adapter.md), [exact paper reference](https://arxiv.org/html/2603.15465v2#S2.SS2) |

## B0010

[Lines 60–65](../../../../../tests/unit/meta_join_trees_test.cpp#L60); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L60-L65:sha256:fec56e66792c9aafd38b7796ab3b38a34fc6de1ebc03d638331018d10aade4b6
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Describe one missing, extra or duplicated rooted key in human-readable form. |
| inputs / outputs | A borrowed Key produces an owning string naming its root and every atom edge. |
| invariants | Formatting preserves literal atom labels and never substitutes scope or graph-isomorphism identities. |
| ownership | A local string stream owns formatting scratch; the returned string owns the diagnostic bytes. |
| failure | Stream/string allocation failures propagate. This helper does not change pass/fail expectations. |
| cost | Linear formatting in edge count plus stream/string allocation; called for exceptional family diagnostics rather than an engine primitive. |
| Design | [docs/meta_candidate_adapter.md](../../../../meta_candidate_adapter.md) |

## B0012

[Lines 67–74](../../../../../tests/unit/meta_join_trees_test.cpp#L67); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L67-L74:sha256:dd28495c92fdd419bb3f9fc991812874ec8c834f12370ac96a24f23f822118dd
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Compare exact rooted-key sets and report a concrete missing/extra topology. |
| inputs / outputs | Actual/expected Keys plus a label either return on equality or throw with cardinalities and first differences. |
| invariants | Equality checks the complete finite labelled family, not only counts or reported completion flags. |
| ownership | Both sets are borrowed read-only; only failure-detail strings are locally owned. |
| failure | Any set mismatch throws runtime_error. The helper does not discard unexpected keys to make a comparison pass. |
| cost | Ordered-set equality and bounded first-difference searches, with failure-only formatting; costs are test work outside EnumerationUsage. |
| Design | [docs/meta_candidate_adapter.md](../../../../meta_candidate_adapter.md), [exact paper reference](https://arxiv.org/html/2603.15465v2#algorithm2), [exact paper reference](https://arxiv.org/html/2603.15465v2#A3.SS7) |

## B0013

[Lines 75–77](../../../../../tests/unit/meta_join_trees_test.cpp#L75); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L75-L77:sha256:a70a40e8f3707528caeb37e0c8d8a2f3f445d65f4188675a6a74b566c93ecffd
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | State the independent BFS connectivity basis used by the oracle. |
| inputs / outputs | The comment distinguishes variable-restricted reachability below from production induced-edge counting. |
| invariants | Shared mathematical RIP is expected; implementation/control-flow independence comes from the separate reachability algorithm. |
| ownership | No graph, visited state or owner is created by the comment. |
| failure | No executable check happens here; connected below supplies the actual boolean. |
| cost | The comment has no executable cost or performance assertion. |
| Design | [docs/meta_candidate_adapter.md](../../../../meta_candidate_adapter.md), [exact paper reference](https://arxiv.org/html/2603.15465v2#S2.SS2) |

## B0014

[Lines 78–92](../../../../../tests/unit/meta_join_trees_test.cpp#L78); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L78-L92:sha256:1bdd34435308af1b3c3853b4204b1c9f0bdea65ee2f7557054156dfe7bb08b41
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Check whether allowed occurrence vertices form one connected induced graph. |
| inputs / outputs | An allowed-vertex bit vector and graph edges return reachability equality; an empty allowed set returns true. |
| invariants | Only allowed vertices are visited. Queue scans actual incident edges, ignoring edges leading outside the allowed set. |
| ownership | Input vectors are borrowed; visited bits and BFS queue are local owning scratch. |
| failure | Disconnected induced vertices return false. Callers supply graph endpoints in the bounded test domain; allocation failures propagate. |
| cost | Repeated queue/edge scans over at most five vertices in oracle use, plus bit/queue allocations; no production selected-work accounting. |
| Design | [docs/meta_candidate_adapter.md](../../../../meta_candidate_adapter.md), [exact paper reference](https://arxiv.org/html/2603.15465v2#S2.SS2) |

## B0016

[Lines 94–98](../../../../../tests/unit/meta_join_trees_test.cpp#L94); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L94-L98:sha256:478ef9fe8ba0669830d475383015999974789cc98cbee70bc5ac6c4764d41bed
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Recognize a nonempty undirected labelled tree independently of production fragment validation. |
| inputs / outputs | A vertex count and edge vector return true only for n-1 edges, in-range nonself endpoints and full BFS connectivity. |
| invariants | Connectedness with n-1 edge occurrences establishes the tree condition; endpoint checks precede reachability. |
| ownership | The helper borrows edges and owns only the temporary all-allowed bit vector and nested BFS scratch. |
| failure | Empty, malformed or disconnected graphs return false rather than being normalized into a tree. |
| cost | Endpoint scan plus independent BFS; finite small-graph test work with normal allocation costs. |
| Design | [docs/meta_candidate_adapter.md](../../../../meta_candidate_adapter.md), [exact paper reference](https://arxiv.org/html/2603.15465v2#S2.SS2) |

## B0017

[Lines 99–101](../../../../../tests/unit/meta_join_trees_test.cpp#L99); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L99-L101:sha256:b22daebb99ce6e896ba2861f82392a21fb47816fcb4001002afc90eb89ea31b6
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Identify the ordinary running-intersection property and the oracle dependency boundary. |
| inputs / outputs | The comment introduces variable-induced connectedness using only input scopes and graph edges. |
| invariants | No meta construction, checking, GYO or normal-form algorithm supplies the expected-family decision. |
| ownership | No scope or graph owner is created by this explanatory region. |
| failure | Comments do not certify a result; the following explicit BFS implementation computes the property. |
| cost | No executable work occurs in these source comments. |
| Design | [docs/meta_candidate_adapter.md](../../../../meta_candidate_adapter.md), [exact paper reference](https://arxiv.org/html/2603.15465v2#S2.SS2) |

## B0018

[Lines 102–111](../../../../../tests/unit/meta_join_trees_test.cpp#L102); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L102-L111:sha256:f582f21a55cc9bbf66642a405a561a9510cd6bb7ab0a0b40a02d330ec19b31d1
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Check RIP independently by BFS on every variable-containing occurrence set. |
| inputs / outputs | Borrowed original scopes and bounded topology edges return whether each variable-induced subgraph is connected. |
| invariants | Variables come from the scope union; singleton incidence is connected. Actual graph topology/domain is validated separately before this helper is used. |
| ownership | The scope union and per-variable allowed vectors are owned scratch; original scopes and graph edges remain unchanged. |
| failure | One disconnected variable returns false. Scope/vector allocation failures propagate instead of becoming expected cyclic classification. |
| cost | Scope-union construction plus one independent BFS per variable. These test allocations/scans are not counted by the implementation grants. |
| Design | [docs/meta_candidate_adapter.md](../../../../meta_candidate_adapter.md), [exact paper reference](https://arxiv.org/html/2603.15465v2#S2.SS2) |

## B0019

[Lines 112–116](../../../../../tests/unit/meta_join_trees_test.cpp#L112); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L112-L116:sha256:bb389d85d88851296e8a6623b6e29040529e7c0a3fe251a34b20919b77118b59
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Document the small labelled Prüfer oracle and its distinct suffix-membership decoder. |
| inputs / outputs | The comment gives the n&lt;=5 domain, paper location and separate edge-subset cross-check. |
| invariants | The test does not reproduce production degree-counter control flow or rely on erroneous printed source indices. |
| ownership | No code vector, topology set or owner is created here. |
| failure | The adjacent function enforces the stated bound with Release-active checks; the comment itself cannot fail. |
| cost | No executable cost; exhaustive enumeration below remains explicitly small and finite. |
| Design | [docs/meta_candidate_adapter.md](../../../../meta_candidate_adapter.md), [exact paper reference](https://arxiv.org/html/2603.15465v2#A3.SS1.SSS2) |

## B0020

[Lines 117–146](../../../../../tests/unit/meta_join_trees_test.cpp#L117); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L117-L146:sha256:4e8929c910a25a8ea08997e3995b9a350a6a29475064b0d44215c9641a115887
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Generate every labelled undirected tree for one to five vertices using independently decoded Prüfer codes. |
| inputs / outputs | A bounded count produces Trees; singleton returns one empty edge vector and two vertices use the empty-code base case. |
| invariants | A leaf is the smallest remaining label absent from the code suffix. Each code yields an actual tree and must insert a unique canonical edge key. |
| ownership | Code vectors, remaining-label sets, edge lists and the returned tree set are owned locally or transferred to the caller. |
| failure | Out-of-domain sizes, missing leaves, wrong terminal cardinality, invalid trees or duplicate codes throw explicit failures; allocation errors propagate. |
| cost | At most 125 codes for n=5, with small suffix/remaining-label scans and ordinary test allocations; no production meta/GYO/normal-form dependency. |
| Design | [docs/meta_candidate_adapter.md](../../../../meta_candidate_adapter.md), [exact paper reference](https://arxiv.org/html/2603.15465v2#A3.SS1.SSS2), [exact paper reference](https://arxiv.org/html/2603.15465v2#S2.SS2) |

## B0021

[Lines 147–149](../../../../../tests/unit/meta_join_trees_test.cpp#L147); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L147-L149:sha256:5afe5256f400c88c7179b0874ea17554073e9612daac19fc2d3da5d2025442a5
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Explain the second, edge-subset topology oracle and its finite mask domain. |
| inputs / outputs | The comment bounds the complete graph to ten edges and distinguishes subset enumeration from Prüfer decoding. |
| invariants | The mask bound is test-only and never restricts an engine query or production enumerator. |
| ownership | No mask state, graph or owning container is created by this comment. |
| failure | The function below explicitly enforces its bound rather than relying on the comment for shift safety. |
| cost | No executable work is performed by the documentation. |
| Design | [docs/meta_candidate_adapter.md](../../../../meta_candidate_adapter.md), [exact paper reference](https://arxiv.org/html/2603.15465v2#S2.SS2), [exact paper reference](https://arxiv.org/html/2603.15465v2#A3.SS1.SSS2) |

## B0022

[Lines 150–163](../../../../../tests/unit/meta_join_trees_test.cpp#L150); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L150-L163:sha256:296a66ea9e40452b29cd8ba83bf9c3ec99e8bc5b08e9da6712d24f43f08d8105
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Cross-check the Prüfer universe by enumerating all n-1 subsets of complete-graph edges. |
| inputs / outputs | A count from one to five produces every subset that passes the independent tree predicate. |
| invariants | There are at most ten possible edges, so uint32 masks/shifts stay inside an explicit finite bound. No degree/suffix decoding is shared with prufer_trees. |
| ownership | The choices vector, candidate edge vectors and returned set own their storage. |
| failure | Invalid count/mask bounds throw; nontree subsets are skipped; allocation failures propagate. |
| cost | At most 2^10 subset masks plus tree checks. This is a bounded oracle cross-check, not a production complexity claim. |
| Design | [docs/meta_candidate_adapter.md](../../../../meta_candidate_adapter.md), [exact paper reference](https://arxiv.org/html/2603.15465v2#S2.SS2), [exact paper reference](https://arxiv.org/html/2603.15465v2#A3.SS1.SSS2) |

## B0023

[Lines 164–165](../../../../../tests/unit/meta_join_trees_test.cpp#L164); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L164-L165:sha256:14342f0248e4463fe3972e1242084f5bf67c972bc166f2acaf9b0b780a397d8d
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Store labelled topology universes by small vertex count. |
| inputs / outputs | Universe aliases a six-entry array of Trees, using indices1..5 and leaving index0 unused. |
| invariants | The fixed array bound is solely an oracle fixture domain, not an engine supported-arity limit. |
| ownership | Concrete Universe values own all topology sets; the alias creates no allocation itself. |
| failure | Callers check count bounds before indexing the array; declaration alone does not validate a universe. |
| cost | Type declaration has no runtime work; populating/copying the sets has its ordinary test costs. |
| Design | [docs/meta_candidate_adapter.md](../../../../meta_candidate_adapter.md), [exact paper reference](https://arxiv.org/html/2603.15465v2#S2.SS2) |

## B0024

[Lines 166–178](../../../../../tests/unit/meta_join_trees_test.cpp#L166); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L166-L178:sha256:f0dd71445c6672d93144bb668bb11e62ddaf03a90efe451147c9ba48c27d1007
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Validate and retain the complete small labelled topology universe before querying the implementation. |
| inputs / outputs | No external input; returns Universes for n1..5 after Prüfer/subset equality and exact counts1,1,3,16,125. |
| invariants | All146 unrooted labelled trees are cross-checked; the expected counts precede production enumeration and are independent of its reports. |
| ownership | The returned array owns all sets; temporary subset universes are released during each iteration. |
| failure | A decoder disagreement or count mismatch throws immediately, preventing a broken oracle from certifying later output. |
| cost | One finite cross-check per size through five; setup allocations and scans are test costs, not charged production work. |
| Design | [docs/meta_candidate_adapter.md](../../../../meta_candidate_adapter.md), [exact paper reference](https://arxiv.org/html/2603.15465v2#S2.SS2), [exact paper reference](https://arxiv.org/html/2603.15465v2#A3.SS1.SSS2) |

## B0026

[Lines 180–185](../../../../../tests/unit/meta_join_trees_test.cpp#L180); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L180-L185:sha256:906c90dc159cc33c8bf9ea444c3a2986d30e83048a7ac77d8df26be1b4afa994
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Calculate the exact finite ordinary family from incidence scopes and the independently checked topology universe. |
| inputs / outputs | One to five original scopes plus Universe produce every topology whose variable-induced graph satisfies BFS RIP. |
| invariants | No meta API, GYO classification or normal-form candidate family enters expected-family calculation. An empty returned set means no ordinary tree in this exhaustive finite universe. |
| ownership | Input scopes/universe are borrowed; the returned Trees owns copies of accepted edge vectors. |
| failure | Out-of-domain arity throws. Failing RIP excludes a topology; allocation failures propagate instead of classifying the body. |
| cost | Up to125 candidate topologies and bounded BFS checks per fixture; test-only finite enumeration, not an all-input theorem. |
| Design | [docs/meta_candidate_adapter.md](../../../../meta_candidate_adapter.md), [exact paper reference](https://arxiv.org/html/2603.15465v2#S2.SS2), [exact paper reference](https://arxiv.org/html/2603.15465v2#algorithm2) |

## B0028

[Lines 187–191](../../../../../tests/unit/meta_join_trees_test.cpp#L187); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L187-L191:sha256:0d1cf5b904aade0c177a6df9101372cc49da9dda8206f7c50943d3eef54bd1c3
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Lift exact undirected expected topologies into all physical rooted keys. |
| inputs / outputs | A vertex count and Trees produce the Cartesian set of every edge vector with roots0..n-1. |
| invariants | Every root is included, including the currently existing orientation and singleton root; labels are not quotiented by graph isomorphism. |
| ownership | The result owns copies of root/edge keys and borrows the unrooted input family. |
| failure | Container allocation failures propagate. Topology/domain validity is established by the oracle or hand fixtures before this lifting step. |
| cost | Exactly n times the unrooted-family size in expected keys, with their normal allocation/copy costs. |
| Design | [docs/meta_candidate_adapter.md](../../../../meta_candidate_adapter.md), [exact paper reference](https://arxiv.org/html/2603.15465v2#A3.SS1.SSS3), [exact paper reference](https://arxiv.org/html/2603.15465v2#algorithm2) |

## B0030

[Lines 193–193](../../../../../tests/unit/meta_join_trees_test.cpp#L193); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L193-L193:sha256:ed84ee76387385d115d135847842bbe1b5b95b00830f4794245508a8813302b1
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Keep admitted CQ data beside independently supplied scopes for actual-versus-expected comparisons. |
| inputs / outputs | Fixture stores owning Catalog, Query and one scope per original atom. |
| invariants | Scope incidence/order derives from fixture inputs and stays distinct from production-generated metadata or output parent vectors. |
| ownership | All three members own their containers; moving/copying a Fixture retains no borrowed enumerator scratch. |
| failure | Raw aggregate construction does not validate the fixture; query_for admits it and allocation errors propagate. |
| cost | Fixture copy/destruction scales with its schema/query/scope contents, outside native selected counters. |
| Design | [docs/meta_candidate_adapter.md](../../../../meta_candidate_adapter.md), [exact paper reference](https://arxiv.org/html/2603.15465v2#S2.SS2) |

## B0031

[Lines 194–196](../../../../../tests/unit/meta_join_trees_test.cpp#L194); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L194-L196:sha256:c19b143860f2020b7520bd2f602f9b36ed115fa6911e39565e956b9e970c745c
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Document independent incidence inputs and dense label renaming in fixture construction. |
| inputs / outputs | The comment introduces query_for and states preservation of original occurrence order and duplicate scopes. |
| invariants | Renaming changes numeric variable IDs consistently while preserving equality/incidence; expected family membership never comes from meta output. |
| ownership | No fixture or variable map is created by this comment. |
| failure | The following function admits its generated CQ; the comment itself supplies no executable validation. |
| cost | No runtime work or allocation occurs in this documentation block. |
| Design | [docs/meta_candidate_adapter.md](../../../../meta_candidate_adapter.md), [exact paper reference](https://arxiv.org/html/2603.15465v2#S2.SS2) |

## B0032

[Lines 197–220](../../../../../tests/unit/meta_join_trees_test.cpp#L197); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L197-L220:sha256:dc7a616fb61aeea789f45ad7e556e437e313a91958227008185757247170bea7
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Build valid direct-CQ fixtures from independent incidence lists with dense variable IDs. |
| inputs / outputs | Edge-label vectors produce catalog tables/columns, atoms/terms and deduplicated scopes in original atom order. |
| invariants | The same sorted mapping renames every variable use; duplicate scopes/terms keep their logical occurrences. Empty/nullary inputs remain representable for explicit domain tests. |
| ownership | The builder owns new maps, schema, query and scope containers and transfers the finished Fixture to its caller. |
| failure | crown::validate rejects accidental fixture mistakes; allocation failures propagate. Validation admits types/binding, not expected join-tree completeness. |
| cost | Finite map/set/vector construction plus input admission, with ordinary test allocation costs outside EnumerationUsage. |
| Design | [docs/meta_candidate_adapter.md](../../../../meta_candidate_adapter.md), [exact paper reference](https://arxiv.org/html/2603.15465v2#S2.SS2) |

## B0034

[Lines 222–226](../../../../../tests/unit/meta_join_trees_test.cpp#L222); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L222-L226:sha256:b9766dc3dccf6b34495fe2391d64c3c599e9245b4c783a7f766203dc0725e523
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Obtain metadata for the actual implementation path without using it to calculate expected families. |
| inputs / outputs | An admitted Fixture and label call construct and return its moved Decomposition only after complete with an engaged optional. |
| invariants | This helper serves the actual-side input; the independent universe/RIP oracle has already determined expected structure separately. |
| ownership | The returned graph owns moved node/scope containers; the temporary Build is released without retaining fixture references. |
| failure | Unexpected construction stop or absent graph throws; validation/allocation exceptions propagate to main. |
| cost | One default-bounded cold metadata construction, distinct from the independent oracle and enumerator grant measurements. |
| Design | [docs/meta_candidate_adapter.md](../../../../meta_candidate_adapter.md), [exact paper reference](https://arxiv.org/html/2603.15465v2#algorithm2) |

## B0035

[Lines 227–230](../../../../../tests/unit/meta_join_trees_test.cpp#L227); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L227-L230:sha256:ff996f7ec51b1ecabb0f360a128d68bf3ab389caacb6810e0a4ff6163c675ffb
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Document the output parent-vector and physical-label inspection boundary. |
| inputs / outputs | The comment introduces independent validation before actual outputs become comparison keys. |
| invariants | Only the physical root may use the self sentinel; metadata/dummy labels cannot be accepted as extra ordinary vertices. |
| ownership | No output tree, key or traversal scratch is owned by this comment. |
| failure | Actual enforcement belongs to inspect below, not to this description or a production success flag. |
| cost | No executable cost is performed in this region. |
| Design | [docs/meta_candidate_adapter.md](../../../../meta_candidate_adapter.md), [exact paper reference](https://arxiv.org/html/2603.15465v2#S2.SS2), [exact paper reference](https://arxiv.org/html/2603.15465v2#A3.SS6) |

## B0036

[Lines 231–251](../../../../../tests/unit/meta_join_trees_test.cpp#L231); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L231-L251:sha256:fca0ef53501a0eb4820d63ebd9db902ca00faa80a61e420e2599492b0ccd1db7
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Validate each returned ordinary parent vector independently and convert it into a labelled root/edge key. |
| inputs / outputs | JoinTree, Fixture and label pass only with one entry per atom, valid physical root/parents, one root-self sentinel, connected topology, root-reaching parent walks and BFS RIP. |
| invariants | Bounds and sentinel checks precede parent indexing/walks. Physical identities are dense vector positions, and canonicalization retains duplicate edges for rejection rather than repairing them. |
| ownership | The tree/fixture are borrowed; edge vector and nested traversal scratch are owned locally and moved into the returned Key. |
| failure | Any malformed topology, cycle, foreign label or RIP failure throws explicitly. Allocation failure propagates; no rejected graph is counted as a valid prefix. |
| cost | Small edge normalization, independent connectivity/RIP scans and bounded parent walks, with test-only allocation costs outside production grants. |
| Design | [docs/meta_candidate_adapter.md](../../../../meta_candidate_adapter.md), [exact paper reference](https://arxiv.org/html/2603.15465v2#S2.SS2), [exact paper reference](https://arxiv.org/html/2603.15465v2#A3.SS6) |

## B0038

[Lines 253–259](../../../../../tests/unit/meta_join_trees_test.cpp#L253); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L253-L259:sha256:0afeaceed1ee2c9596f0aeb09ab9246d7bd7b22533b87ebeb5bf2df9e82e551e
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Check reported enumeration/metadata grants separately and reconcile published output accounting. |
| inputs / outputs | An Enumeration, its EnumerationLimits and label must satisfy each selected counter limit and output_trees==trees.size(). |
| invariants | Metadata work/nodes/cells are separate from expansion work/fragments/cells. Counter consistency does not prove total CPU, allocator bytes or unreported capacity bounds. |
| ownership | Only borrowed scalar reports and the output vector size are inspected; no budget authority is created or refilled. |
| failure | Any exceeded grant or mismatched published-tree count throws; this helper cannot repair or normalize reported usage. |
| cost | Fixed scalar comparisons and vector-size inspection plus diagnostics, independent of actual expansion/metadata work. |
| Design | [docs/meta_candidate_adapter.md](../../../../meta_candidate_adapter.md) |

## B0040

[Lines 261–271](../../../../../tests/unit/meta_join_trees_test.cpp#L261); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L261-L271:sha256:3f3ba15b6047ba76b1d38b94790e660baad9ceb19fb14cde8e3916b0334cd065
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Inspect every returned record and reject repeated labelled root/topology outputs before constructing the family set. |
| inputs / outputs | Enumeration plus Fixture and label produce an owning vector of validated Keys in original output order. |
| invariants | Every record passes inspect; a uniqueness set detects duplicate raw output that final set equality would otherwise hide. Original order is retained for prefix tests. |
| ownership | Inputs are borrowed. The ordered vector and local uniqueness set own key/edge copies; the set dies on return. |
| failure | Invalid records and duplicate keys fail explicitly, with duplicate formatting on the failure path. Allocation failures propagate. |
| cost | One independent inspection and set insertion per actual output, with small key copies; these are regression costs outside production counters. |
| Design | [docs/meta_candidate_adapter.md](../../../../meta_candidate_adapter.md), [exact paper reference](https://arxiv.org/html/2603.15465v2#S2.SS2), [exact paper reference](https://arxiv.org/html/2603.15465v2#algorithm2) |

## B0042

[Lines 273–279](../../../../../tests/unit/meta_join_trees_test.cpp#L273); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L273-L279:sha256:8e3afd57a8136ba55187a77c730464f2928b8391c5e0de7e74fbb17f77e68045
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Require successful actual enumeration and exact equality with an independently supplied finite expected rooted family. |
| inputs / outputs | A run, Fixture, expected Keys and label must pass metadata admission, complete status, per-record validation/uniqueness and whole-set equality. |
| invariants | Flags are necessary control checks, not correctness authority; exact inspected keys decide family agreement within the explicit oracle domain. |
| ownership | Inputs remain borrowed; ordered and set-form output keys are temporary owning values. |
| failure | Wrong metadata/stop, invalid or duplicate outputs, and missing/extra keys throw. No partial output is accepted as a complete expected family. |
| cost | Inspection/set construction/comparison over the finite returned family; this establishes no unbounded completeness or complexity theorem. |
| Design | [docs/meta_candidate_adapter.md](../../../../meta_candidate_adapter.md), [exact paper reference](https://arxiv.org/html/2603.15465v2#algorithm2), [exact paper reference](https://arxiv.org/html/2603.15465v2#A3.SS7) |

## B0044

[Lines 281–281](../../../../../tests/unit/meta_join_trees_test.cpp#L281); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L281-L281:sha256:2210dd103548a1ef3306d1bcfd6914bf14052fa5b15ce84672864f6844064514
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Package a labelled fixture with a hand-derived or independently filtered expected undirected family. |
| inputs / outputs | Case contains a diagnostic label, Fixture and Trees used by literal, canonical and resource controls. |
| invariants | Expected edges come from explicit constraints/topology universe, never from production parent vectors. |
| ownership | The aggregate owns all diagnostic, CQ and expected-family containers. |
| failure | Aggregate creation itself supplies no semantic validation; later literal/oracle agreement checks catch bad expected data. |
| cost | Finite fixture/family copy and destruction costs, separate from native planner resource accounting. |
| Design | [docs/meta_candidate_adapter.md](../../../../meta_candidate_adapter.md), [exact paper reference](https://arxiv.org/html/2603.15465v2#S2.SS2), [exact paper reference](https://arxiv.org/html/2603.15465v2#algorithm2) |

## B0046

[Lines 283–336](../../../../../tests/unit/meta_join_trees_test.cpp#L283); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L283-L336:sha256:e0fc018bc2b24034aede8f7ea96c3e88c71e2f51c0d68c3a41367f1e509e652a
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Define thirteen exact ordinary-family fixtures covering paper examples and endpoint/placeholder/identity regressions. |
| inputs / outputs | Universe produces Cases for singleton, aliases/equal scopes, disconnected roots, special/original scope equality, nested groups, typed dummy, rebranching and Cartesian child variants. |
| invariants | Explicit edge sets retain labels. Endpoint cases force01/23 (20 unrooted) or a connected0/1/2 block (45 unrooted). Paper examples use incidence-preserving numeric renaming; added cases are local regressions, not paper-domain proof extensions. |
| ownership | Returned Cases own all fixtures and expected edge families; temporary alias changes are schema-compatible and readmitted. |
| failure | Wrong endpoint/variant counts, changed fixture inventory, invalid CQ admission or allocation failure stop the test before production results can define expectations. |
| cost | Thirteen small fixtures and a scan of125 independent five-vertex topologies. Setup is cold test work, with no claimed native delay/complexity bound. |
| Design | [docs/meta_candidate_adapter.md](../../../../meta_candidate_adapter.md), [exact paper reference](https://arxiv.org/html/2603.15465v2#S2.SS2), [exact paper reference](https://arxiv.org/html/2603.15465v2#algorithm2), [exact paper reference](https://arxiv.org/html/2603.15465v2#S4.Thmtheorem4), [exact paper reference](https://arxiv.org/html/2603.15465v2#S4.Thmtheorem6), [exact paper reference](https://arxiv.org/html/2603.15465v2#algorithm5) |

## B0047

[Lines 337–339](../../../../../tests/unit/meta_join_trees_test.cpp#L337); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L337-L339:sha256:7535a5d12d967517a4fede6b89009db788b672871e77b8aab15159f9898b5db9
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Explain metadata-node renumbering as distinct from physical occurrence relabelling. |
| inputs / outputs | The comment introduces reversal of metadata storage with remapped root/parent indices. |
| invariants | Atom labels and expected ordinary edges stay fixed, so storage order cannot silently define public physical identity. |
| ownership | The comment creates no graph copy or remapping array. |
| failure | No executable failure occurs here; the following helper and family checks exercise the stated transformation. |
| cost | No runtime work is performed by the comment. |
| Design | [docs/meta_candidate_adapter.md](../../../../meta_candidate_adapter.md), [exact paper reference](https://arxiv.org/html/2603.15465v2#algorithm2) |

## B0048

[Lines 340–349](../../../../../tests/unit/meta_join_trees_test.cpp#L340); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L340-L349:sha256:c350dabea04b5729eca3f4be07e227c87282b3489d93de4e44da3e62348f6e20
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Reverse metadata node storage while preserving atom identities and parent/root topology. |
| inputs / outputs | An admitted nonempty Decomposition returns an owning copy whose node index i maps to n-1-i. |
| invariants | Only metadata indices move; occurrence IDs, scopes and interfaces are retained. Parent/root scalar indices are remapped consistently. |
| ownership | The result owns copied nodes and scopes; original metadata is borrowed unchanged. |
| failure | The helper assumes the constructed source graph is nonempty/admitted; copy allocation failures propagate, and enumerate independently readmits the remapped proposal. |
| cost | One full metadata copy plus a linear node rewrite; this is a test transformation, not a production normalization pass. |
| Design | [docs/meta_candidate_adapter.md](../../../../meta_candidate_adapter.md), [exact paper reference](https://arxiv.org/html/2603.15465v2#algorithm2) |

## B0050

[Lines 351–373](../../../../../tests/unit/meta_join_trees_test.cpp#L351); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L351-L373:sha256:2f27aced11b78895ca5d6ae9c908df1f5cd9cb001be2e748a7f1494fa4c5a434
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Compare all literal rooted families with the independent oracle and actual enumeration under both metadata numberings. |
| inputs / outputs | Cases and Universe feed hand/Pruefer-RIP agreement, default enumeration, reversed-node enumeration and a projected-head control. |
| invariants | Literal counts1,9,64,2,16,2,6,15,20,20,40,100,225 are checked before actual calls. All physical roots survive; the ordinary body family is independent of later CROWN/head admission. |
| ownership | Cases/universe are borrowed; metadata, enumeration results, expected keys and the copied projected fixture are locally owned. |
| failure | Any oracle/literal mismatch, metadata failure, incomplete/invalid output, lost rooting or renumbering difference throws explicitly. |
| cost | Finite positive/renumber/head controls with normal test container work and default bounded cold API calls; no generalized-family completeness follows. |
| Design | [docs/meta_candidate_adapter.md](../../../../meta_candidate_adapter.md), [exact paper reference](https://arxiv.org/html/2603.15465v2#S2.SS2), [exact paper reference](https://arxiv.org/html/2603.15465v2#algorithm2), [exact paper reference](https://arxiv.org/html/2603.15465v2#A3.SS7), [exact paper reference](https://arxiv.org/html/2603.15465v2#A3.SS1.SSS3) |

## B0052

[Lines 375–421](../../../../../tests/unit/meta_join_trees_test.cpp#L375); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L375-L421:sha256:3460b5355cdea3b15adf06ab23e79f33ee25609eaead67c67574050deb3d29d2
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Exercise metadata/domain admission and its independent resource boundary before ordinary expansion. |
| inputs / outputs | A positive fixture supplies metadata; edited root, unguarded triangle, empty/nullary inputs and exact/one-short/zero metadata grants feed enumerate. |
| invariants | Metadata rejection/limits publish no trees and consume no expansion counters. The whole-scope anchor rejects a cyclic union-minor. Exact metadata Usage defines grant boundaries, not expected families. |
| ownership | All fixtures, edited graphs and reports are local owners; the original fixture and good metadata stay unchanged. |
| failure | Wrong public/underlying stop, accepted malformed/domain metadata, nonempty rejected output, early expansion charges or overspent grants throw explicitly. |
| cost | Fixed small admission controls plus repeated bounded calls. Metadata counters exclude allocating input validation and do not establish total CPU/byte limits. |
| Design | [docs/meta_candidate_adapter.md](../../../../meta_candidate_adapter.md), [exact paper reference](https://arxiv.org/html/2603.15465v2#S2.SS2), [exact paper reference](https://arxiv.org/html/2603.15465v2#algorithm2) |

## B0054

[Lines 423–430](../../../../../tests/unit/meta_join_trees_test.cpp#L423); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L423-L430:sha256:3d488dfaa7851aa231b5556913da42b3162169bfaf5369c64a42b5810e3c400a
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Validate a stopped run as a unique, semantically valid ordered prefix of the same completed invocation. |
| inputs / outputs | A run, Fixture, baseline ordered Keys, its grants and label require admitted metadata, bounded counters and equal leading validated keys. |
| invariants | Prefix records pass independent topology/RIP checks and duplicate rejection. Baseline output is a sequence reference, not the expected-family oracle used for full correctness. |
| ownership | All inputs are borrowed; extracted prefix keys are temporary owning vectors/sets. |
| failure | Grant/metadata violations, invalid records, duplicates, oversized or reordered prefixes throw rather than being labelled complete. |
| cost | Independent inspection plus linear prefix comparison over returned records, outside production selected counters. |
| Design | [docs/meta_candidate_adapter.md](../../../../meta_candidate_adapter.md), [exact paper reference](https://arxiv.org/html/2603.15465v2#algorithm2) |

## B0055

[Lines 431–433](../../../../../tests/unit/meta_join_trees_test.cpp#L431); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L431-L433:sha256:860cd6d41b121951f701fab96fd4287176838d243f90307233b0b8183a307883
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Qualify the exact resource-boundary checks as selected logical counters. |
| inputs / outputs | The comment introduces expansion_limits and names checkpoints, cumulative fragments/vector cells and published records. |
| invariants | Exact grants are not byte/RSS/time measurements or an imported paper delay theorem. |
| ownership | The comment creates no budget, resource account or graph owner. |
| failure | No executable failure occurs here; the following function enforces those bounded dimensions explicitly. |
| cost | No runtime work in the comment; unaccounted allocator/CPU costs remain explicitly outside these counters. |
| Design | [docs/meta_candidate_adapter.md](../../../../meta_candidate_adapter.md) |

## B0056

[Lines 434–477](../../../../../tests/unit/meta_join_trees_test.cpp#L434); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L434-L477:sha256:eb6ca530a0794a469c8bc1ce9dcb7251e8ce98eff44f163e76e6ef80425c9e1b
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Check exact/one-short/zero expansion grants, exact output caps and fresh-call behavior after stops. |
| inputs / outputs | A Cartesian endpoint fixture supplies an independently expected family. Successful Usage defines individual work/fragment/cell grants; output caps are0,1,N-1,N. |
| invariants | Exact grants retain exact expected coverage. Every denied dimension has its specific stop and bounded valid prefix; late work denial preserves earlier records. Raising grants starts a fresh call with no duplicated continuation prefix. |
| ownership | Each returned Enumeration owns its output; limits/counters/keys and metadata are local values, with no retained resumable state. |
| failure | Wrong stop, invalid/duplicate/incorrect prefix, lost already published output, wrong cap cardinality or failed complete rerun throws. |
| cost | A fixed number of bounded cold calls plus independent output checks. Measured grants concern selected counters only, never allocator bytes, full comparisons or total CPU. |
| Design | [docs/meta_candidate_adapter.md](../../../../meta_candidate_adapter.md), [exact paper reference](https://arxiv.org/html/2603.15465v2#algorithm2) |

## B0057

[Lines 478–480](../../../../../tests/unit/meta_join_trees_test.cpp#L478); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L478-L480:sha256:339a08cb84d9096adfcdf6577e660b12cca713539567180bc6ad273136a8b2d1
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Document canonical root0 mode as an undirected-family representation for inverse fibers. |
| inputs / outputs | The comment introduces canonical_families and the intended avoidance of materializing discarded ordinary orientations. |
| invariants | One representative root can describe each undirected tree; adjacent tests check returned coverage/counts, while allocation avoidance additionally requires source inspection. |
| ownership | No canonical output or inverse-mapping owner is created by the comment. |
| failure | The comment makes no executable completeness proof; exact finite tests below enforce their explicit expectations. |
| cost | No runtime work here. The stated optimization concerns production orientation output, not a new test allocation meter. |
| Design | [docs/meta_candidate_adapter.md](../../../../meta_candidate_adapter.md), [exact paper reference](https://arxiv.org/html/2603.15465v2#algorithm2), [exact paper reference](https://arxiv.org/html/2603.15465v2#A3.SS1.SSS3) |

## B0058

[Lines 481–505](../../../../../tests/unit/meta_join_trees_test.cpp#L481); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L481-L505:sha256:678b14fee4f24044a33283f5909cdbc3b824ccbbc7dfd759c5418c6cf28204dd
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Require canonical mode to return exactly root0 for every expected undirected literal topology and preserve its requested mode on stops. |
| inputs / outputs | Each Case is enumerated with all_roots=false and output cap equal to its undirected-family count; outputs are independently inspected and compared with root0 keys. |
| invariants | Complete canonical coverage is distinct from all-root coverage. Every returned root is0 and unique. Invalid-metadata and zero-work runs retain all_roots=false as requested-mode metadata, not exhaustion authority. |
| ownership | Cases are borrowed; copied metadata, local limits, run outputs and actual/expected sets are owned for one iteration. |
| failure | Lost topology, extra orientation, wrong root/duplicate, changed mode flag or wrong rejection/resource status throws explicitly. |
| cost | Thirteen bounded canonical runs and early-stop controls, inspecting one output per expected undirected tree. Tests do not measure all intermediate allocations or prove general inverse coverage. |
| Design | [docs/meta_candidate_adapter.md](../../../../meta_candidate_adapter.md), [exact paper reference](https://arxiv.org/html/2603.15465v2#S2.SS2), [exact paper reference](https://arxiv.org/html/2603.15465v2#algorithm2), [exact paper reference](https://arxiv.org/html/2603.15465v2#A3.SS1.SSS3) |

## B0059

[Lines 506–508](../../../../../tests/unit/meta_join_trees_test.cpp#L506); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L506-L508:sha256:ddcea1371ee83e320e270029857c5ababb88d54c0c79fdc1251eba8b5fa86e9c
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Document the distinction between literal structural validity and the canonical parenting required by this expansion. |
| inputs / outputs | The comment introduces the four-atom regression whose earlier expansion falsely reported32 of64 rooted trees complete. |
| invariants | Algorithm1 minor-first parenting is an additional input invariant; Definition4.3 validity alone is insufficient for the ordinary-family partition. |
| ownership | No metadata graph, expected family or owner is created by this comment. |
| failure | The adjacent function checks rejection and the query's supported canonical replacement; the comment itself is not a native receipt. |
| cost | No executable work occurs in these comments, and no additional runtime update machinery is implied. |
| Design | [docs/meta_candidate_adapter.md](../../../../meta_candidate_adapter.md), [exact paper reference](https://arxiv.org/html/2603.15465v2#algorithm1), [exact paper reference](https://arxiv.org/html/2603.15465v2#S4.Thmtheorem3), [exact paper reference](https://arxiv.org/html/2603.15465v2#algorithm2) |

## B0060

[Lines 509–526](../../../../../tests/unit/meta_join_trees_test.cpp#L509); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L509-L526:sha256:88e2d22a458e29d834a06bdf3fcf780720c10a526d7f73a75059f1f90044016b
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Reject a structurally valid noncanonical graph without losing support for its original ordinary query. |
| inputs / outputs | A hand-written R-root/minor-x/A-B/C layout passes meta::check; the independent Prüfer/RIP oracle establishes64 rooted keys. enumerate must return noncanonical_metadata with admitted metadata and empty output. |
| invariants | Structural Check.valid and expansion-domain admission are distinct. The constructor-generated canonical representation of the same body must still produce exactly all64 independently expected keys. |
| ownership | The fixture, edited metadata, canonical replacement and expected/output containers are owned locally; no shared provider or proof capability is created. |
| failure | Checker rejection of the intended structurally valid control, wrong oracle count, false complete/partial publication, wrong canonical stop or lost query support throws explicitly. |
| cost | One small independent family calculation and bounded metadata/enumeration calls. The guard's selected work is separate from metadata checking; no all-input completeness proof is inferred. |
| Design | [docs/meta_candidate_adapter.md](../../../../meta_candidate_adapter.md), [exact paper reference](https://arxiv.org/html/2603.15465v2#algorithm1), [exact paper reference](https://arxiv.org/html/2603.15465v2#S4.Thmtheorem3), [exact paper reference](https://arxiv.org/html/2603.15465v2#S2.SS2), [exact paper reference](https://arxiv.org/html/2603.15465v2#algorithm2), [exact paper reference](https://arxiv.org/html/2603.15465v2#A3.SS7) |

## B0062

[Lines 528–574](../../../../../tests/unit/meta_join_trees_test.cpp#L528); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L528-L574:sha256:e41e60e985ec6a046485faaf9dc5104d6673adf5128cfc49658881c25366e2d8
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Compare exact ordinary families over all bounded scope multisets using only independent topology/RIP expectations. |
| inputs / outputs | Enumerates3,875 multisets of1..4 nonempty scopes over four variables in forward/reverse order, yielding7,750 calls and expected112,286 rooted records. |
| invariants | The oracle precedes construct/enumerate and uses no GYO or normal-form path. Cyclic inputs require construction cyclic with no graph; acyclic inputs require exact inspected rooted families. Two orders are not all labelled permutations. |
| ownership | Masks, incidence lists, fixtures, expected families and actual outputs are local per iteration; no query-shared cache supplies expected answers. |
| failure | Class/family disagreements fail with n/code/order. Final totals7750/7114/636 and28814 unrooted/112286 rooted expose skipped corpus work; they are finite observations, not unbounded completeness proof. |
| cost | At most15^4 raw codes filtered to multisets, then7,750 small comparisons. Independent oracle and actual-call allocations are regression costs, not production performance guarantees. |
| Design | [docs/meta_candidate_adapter.md](../../../../meta_candidate_adapter.md), [exact paper reference](https://arxiv.org/html/2603.15465v2#S2.SS2), [exact paper reference](https://arxiv.org/html/2603.15465v2#algorithm2), [exact paper reference](https://arxiv.org/html/2603.15465v2#A3.SS7) |

## B0063

[Lines 575–576](../../../../../tests/unit/meta_join_trees_test.cpp#L575); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L575-L576:sha256:c929980d95efc152dc886ac42af0f045075441dd18a8f886364828ead327bbd3
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Close internal test helper linkage before the executable entry point. |
| inputs / outputs | The anonymous namespace ends after exhaustive_families; main remains externally visible as the test driver. |
| invariants | This closure changes lookup/linkage only and does not publish a test status or skip a helper call. |
| ownership | Namespace closure itself owns or destroys no runtime object. |
| failure | There is no runtime exception or success result in this region. |
| cost | No executable instruction or allocation is attributable to the namespace brace. |
| Design | [docs/meta_candidate_adapter.md](../../../../meta_candidate_adapter.md) |

## B0064

[Lines 577–592](../../../../../tests/unit/meta_join_trees_test.cpp#L577); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L577-L592:sha256:08d2198ef018b92ea66078e32792b0c8002f8175de8611394df5759da40b1faa
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Run topology cross-checks, literal/domain/resource/canonical controls and the exhaustive finite corpus with process-visible failure. |
| inputs / outputs | No CLI inputs; main constructs the checked universe/Cases, invokes literal/domain/resource/canonical/noncanonical/corpus suites in order and returns zero only after all finish. |
| invariants | Explicit failures remain active under NDEBUG. Success reports completion of this finite current suite, not general completeness, mapping/height authority or a native performance theorem. |
| ownership | main owns the universe, Case containers and transient diagnostics; normal exit and unwinding release all ordinary metadata/test storage. |
| failure | A standard exception is printed to stderr and returns one. Early failure leaves later suites unexecuted rather than recording them as passed. |
| cost | Cold fixture/oracle setup plus every invoked finite check and diagnostic I/O; no runtime update workload or byte/latency benchmark is run. |
| Design | [docs/meta_candidate_adapter.md](../../../../meta_candidate_adapter.md), [exact paper reference](https://arxiv.org/html/2603.15465v2#algorithm2), [exact paper reference](https://arxiv.org/html/2603.15465v2#A3.SS7) |
