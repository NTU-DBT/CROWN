# `tests/unit/physical_api_test.cpp` — block usage map

[Source](../../../../../tests/unit/physical_api_test.cpp) · [Source index](../../../README.md) · [Subsystem contracts](../../../subsystem_contracts.md) · [Reviewed primitives](../../../primitives.md)

Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection.

Snapshot SHA-256: `9aad3c65cb1e8a551be3c57d9d142f9ec380c473347b6f24ab641d80ad03acb2`. 422 lines partitioned into 29 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [tests](../../../subsystem_contracts.md#tests). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/code_review.md](../../../../code_review.md), [docs/reference_fuzz.md](../../../../reference_fuzz.md), [docs/task_ledger.md](../../../../task_ledger.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–23](../../../../../tests/unit/physical_api_test.cpp#L1) | Imports dependencies; declares namespace scope; declares aliases. |  · [reviewed contract](#b0001) |
| [B0002 · 24–26](../../../../../tests/unit/physical_api_test.cpp#L24) | Callable definition: void check(bool condition, const std::string& message) | calls std::runtime_error; guard void check(bool condition, const std::string& message) { · [reviewed contract](#b0002) |
| [B0003 · 27–34](../../../../../tests/unit/physical_api_test.cpp#L27) | Callable definition: void error(const std::function&lt;void()&gt;& action, std::string_view code) | calls void, action, check, code; guard check(failure.code() == code, "wrong error: " + failure.code() + ", expected " + std::string(code)); · [reviewed contract](#b0003) |
| [B0004 · 35–35](../../../../../tests/unit/physical_api_test.cpp#L35) | Callable definition: Value n(std::int64_t value) | calls ; returns value · [reviewed contract](#b0004) |
| [B0005 · 36–36](../../../../../tests/unit/physical_api_test.cpp#L36) | Callable definition: Value s(std::string value) | calls ; returns value · [reviewed contract](#b0005) |
| [B0006 · 37–41](../../../../../tests/unit/physical_api_test.cpp#L37) | Callable definition: std::string read_file(const std::filesystem::path& path) | calls stream, check, bool, string; guard check(bool(stream), "cannot open fixture: " + path.string());; returns {std::istreambuf_iterator&lt;char&gt;{stream}, std::istreambuf_iterator&lt;char&gt;{}} · [reviewed contract](#b0006) |
| [B0007 · 42–56](../../../../../tests/unit/physical_api_test.cpp#L42) | declares callable signatures; declares values/defaults or compile-time conditions. | guard static_assert(!std::is_default_constructible_v&lt;PhysicalPlan&gt;); · [reviewed contract](#b0007) |
| [B0008 · 57–63](../../../../../tests/unit/physical_api_test.cpp#L57) | Type/record definition: struct DirectFixture |  · [reviewed contract](#b0008) |
| [B0009 · 64–76](../../../../../tests/unit/physical_api_test.cpp#L64) | Callable definition: DirectFixture direct_fixture() | calls s; returns fixture · [reviewed contract](#b0009) |
| [B0010 · 77–81](../../../../../tests/unit/physical_api_test.cpp#L77) | Callable definition: Row typed_row(std::int64_t first, std::int64_t again, std::string label = "keep", bool enabled = true, Date day = Date::parse("20… | calls Date::parse, Decimal::parse, n, s; returns {n(first), n(again), n(fixed), s(std::move(label)), Value{enabled}, Value{day}, Value{amount}, s(st… · [reviewed contract](#b0010) |
| [B0011 · 82–94](../../../../../tests/unit/physical_api_test.cpp#L82) | Callable definition: DirectFixture pair_fixture() | calls ; returns fixture · [reviewed contract](#b0011) |
| [B0012 · 95–95](../../../../../tests/unit/physical_api_test.cpp#L95) | Explanatory comments or spacing. |  |
| [B0013 · 96–135](../../../../../tests/unit/physical_api_test.cpp#L96) | Callable definition: void direct_inputs_and_result_assembly() | calls direct_fixture, planner::lower_tree, check, route; guard check(plan.route() == PhysicalRoute::tree && plan.validation().valid && plan.validation().native_he… · [reviewed contract](#b0013) |
| [B0014 · 136–136](../../../../../tests/unit/physical_api_test.cpp#L136) | Explanatory comments or spacing. |  |
| [B0015 · 137–175](../../../../../tests/unit/physical_api_test.cpp#L137) | Callable definition: void native_child_keys_and_storage() | calls pair_fixture, planner::lower_tree, check, edges; guard check(plan.edges().size() == 1 && plan.edges()\[0\].parent == NodeId{0} && plan.edges()\[0\].child == N…; growth insert; 1 loop sites · [reviewed contract](#b0015) |
| [B0016 · 176–176](../../../../../tests/unit/physical_api_test.cpp#L176) | Explanatory comments or spacing. |  |
| [B0017 · 177–182](../../../../../tests/unit/physical_api_test.cpp#L177) | Callable definition: bool same_identity(const io::QueryIdentity& left, const io::QueryIdentity& right) | calls ; returns left.canonical == right.canonical && left.semantic_sha256 == right.semantic_sha256 && · [reviewed contract](#b0017) |
| [B0018 · 183–194](../../../../../tests/unit/physical_api_test.cpp#L183) | Callable definition: frontend::NormalizedSql normalized_self_join() | calls frontend::bind_sql, std::runtime_error, frontend::normalize_sql, std::move; returns std::get&lt;frontend::NormalizedSql&gt;(std::move(normalized)) · [reviewed contract](#b0018) |
| [B0019 · 195–209](../../../../../tests/unit/physical_api_test.cpp#L195) | Callable definition: FreeConnexTree normalized_self_join_tree(const Query& query) | calls check, size; guard check(query.variables.size() == 3 && query.atoms.size() == 2, "normalized self-join has three core …; returns {NodeId{0}, { · [reviewed contract](#b0019) |
| [B0020 · 210–210](../../../../../tests/unit/physical_api_test.cpp#L210) | Explanatory comments or spacing. |  |
| [B0021 · 211–277](../../../../../tests/unit/physical_api_test.cpp#L211) | Callable definition: void normalized_replay_identity_and_ownership() | calls normalized_self_join, io::write_sql_normalization, dump, io::query_identity; guard check(plan.normalized() && plan.normalized()-&gt;schema_version == 2 && plan.validation().valid && · [reviewed contract](#b0021) |
| [B0022 · 278–278](../../../../../tests/unit/physical_api_test.cpp#L278) | Explanatory comments or spacing. |  |
| [B0023 · 279–340](../../../../../tests/unit/physical_api_test.cpp#L279) | Callable definition: void physical_options_and_replay_boundaries() | calls direct_fixture, planner::lower_tree, check, work; guard check(baseline.work() &gt; 1 && baseline.identity().work &gt; 0, "lowering and identity report completed … · [reviewed contract](#b0023) |
| [B0024 · 341–341](../../../../../tests/unit/physical_api_test.cpp#L341) | Explanatory comments or spacing. |  |
| [B0025 · 342–368](../../../../../tests/unit/physical_api_test.cpp#L342) | Callable definition: void physical_artifact_rejects_corruption() | calls direct_fixture, io::write_physical, planner::lower_tree, void · [reviewed contract](#b0025) |
| [B0026 · 369–369](../../../../../tests/unit/physical_api_test.cpp#L369) | Explanatory comments or spacing. |  |
| [B0027 · 370–404](../../../../../tests/unit/physical_api_test.cpp#L370) | Callable definition: void tree_validation_and_legacy_grounding(const std::filesystem::path& root) | calls direct_fixture, clear, planner::validate_tree, check; guard check(!caller_report.valid, "invalid fixture produces a failed caller-side report"); · [reviewed contract](#b0027) |
| [B0028 · 405–407](../../../../../tests/unit/physical_api_test.cpp#L405) | Closes surrounding scope/type. | source comment (unverified): // namespace · [reviewed contract](#b0028) |
| [B0029 · 408–422](../../../../../tests/unit/physical_api_test.cpp#L408) | Callable definition: int main(int argc, char** argv) | calls check, direct_inputs_and_result_assembly, native_child_keys_and_storage, normalized_replay_identity_and_ownership; guard check(argc == 2, "usage: crown_physical_api_test REPOSITORY");; returns 1 · [reviewed contract](#b0029) |

## B0001

[Lines 1–23](../../../../../tests/unit/physical_api_test.cpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L1-L23:sha256:38c6c9d36c81a0c7a93f85c3d1991313f0ac9ce80f3cfa9b77485c0ad3561dae
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Prepare physical_api_test.cpp: include "crown/api/error.hpp", "crown/frontend/bind.hpp", "crown/frontend/normalize.hpp", "crown/io/normalization.hpp", "crown/io/physical.hpp", "crown/planner/lower.hpp", "crown/planner/verify.hpp", "crown/storage/physical.hpp", &lt;algorithm&gt;, &lt;filesystem&gt;, &lt;fstream&gt;, &lt;functional&gt;, &lt;iostream&gt;, &lt;iterator&gt;, &lt;stdexcept&gt;, &lt;type_traits&gt;, &lt;utility&gt;; bind local aliases/name imports. |
| inputs / outputs | Compiler-visible dependencies, names and the recorded declarations in; declarations available to the following fixture/CLI/example definitions out. |
| invariants | Declarations are scoped to this source/header and its selected ABI. Included code has its own effects; names and editable fixture values do not confer proof, admission or publication authority. |
| ownership | Aliases/includes do not create a query owner. Pointers/references/views are non-owning. Containers own their elements, which can themselves be borrowed pointers or numeric IDs. Only documented owning shared-control handles retain controls; IDs/slot-handle values do not independently keep an arena/runtime alive. |
| failure | Missing headers, ill-formed names/types, failed static assertions or active #error directives stop compilation. No runtime rejection/rollback mechanism is implemented by aliases or function prototypes. |
| cost | Preprocessing and type/constraint instantiation cost compilation. Alias/prototype syntax does not invoke the declared operation; any included definitions keep their own initialization effects. |
| Design | [tests/unit/physical_api_test.cpp](../../../../../tests/unit/physical_api_test.cpp), [docs/physical_runtime.md](../../../../physical_runtime.md), [docs/code_review.md](../../../../code_review.md) |

## B0002

[Lines 24–26](../../../../../tests/unit/physical_api_test.cpp#L24); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void check(bool condition, const std::string& message) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Fail a physical API fixture assertion when its condition is false. |
| inputs / outputs | Takes a Boolean and borrowed diagnostic string; returns void. |
| invariants | Does not catch exceptions from the expression that produced condition. |
| ownership | The diagnostic is borrowed for this call; no test state is retained. |
| failure | False throws std::runtime_error containing the message. |
| cost | One branch; exception construction occurs only on failure. |
| Design | tests/unit/physical_api_test.cpp:24-26 |

## B0003

[Lines 27–34](../../../../../tests/unit/physical_api_test.cpp#L27); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void error(const std::function<void()>& action, std::string_view code) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Require one action to throw crown::Error with the requested code. |
| inputs / outputs | Takes a callable and borrowed code; invokes the callable once and returns on exact code match. |
| invariants | Only crown::Error is caught. A different code fails through check; no error produces runtime_error; other exception types propagate. |
| ownership | The std::function and code view are used only during this call. |
| failure | Wrong code or no crown::Error throws std::runtime_error. |
| cost | One action invocation and code comparison on the expected-error path. |
| Design | tests/unit/physical_api_test.cpp:27-34 |

## B0004

[Lines 35–35](../../../../../tests/unit/physical_api_test.cpp#L35); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Value n(std::int64_t value) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Construct the integer Value used in physical-plan fixtures. |
| inputs / outputs | Takes one int64 and returns it as crown::Value. |
| invariants | Preserves the explicitly supplied integer value and tag. |
| ownership | Returns the scalar by value. |
| failure | No conversion failure is injected or asserted. |
| cost | One scalar Value construction. |
| Design | tests/unit/physical_api_test.cpp:35-35 |

## B0005

[Lines 36–36](../../../../../tests/unit/physical_api_test.cpp#L36); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Value s(std::string value) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Construct a string Value used in physical-plan fixtures. |
| inputs / outputs | Takes a string by value and returns it as crown::Value. |
| invariants | Preserves the supplied string value and tag. |
| ownership | Returned Value owns its string payload; parameter is local. |
| failure | No conversion failure is injected or asserted. |
| cost | One scalar Value construction; string storage depends on the value. |
| Design | tests/unit/physical_api_test.cpp:36-36 |

## B0006

[Lines 37–41](../../../../../tests/unit/physical_api_test.cpp#L37); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::string read_file(const std::filesystem::path& path) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Read a repository fixture into an owning string for legacy replay. |
| inputs / outputs | Takes a path by reference and returns all bytes consumed from an ifstream. |
| invariants | Checks that the stream opened; does not separately classify stream state after iterator consumption. |
| ownership | Stream is local; returned string owns consumed bytes. |
| failure | Open failure throws std::runtime_error through check; later read errors are not explicitly classified. |
| cost | One open and sequential read proportional to fixture bytes. |
| Design | tests/unit/physical_api_test.cpp:37-41 |

## B0007

[Lines 42–56](../../../../../tests/unit/physical_api_test.cpp#L42); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L42-L56:sha256:2b73093d8400139c53aec3072c654bceaa95707dd1c7214b4644ccb33ff0b6be
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Prepare physical_api_test.cpp: require 13 compile-time type/ABI conditions. |
| inputs / outputs | Compiler-visible dependencies, names and the recorded declarations in; declarations available to the following fixture/CLI/example definitions out. |
| invariants | Declarations are scoped to this source/header and its selected ABI. Included code has its own effects; names and editable fixture values do not confer proof, admission or publication authority. Static assertions establish only their listed C++ type properties, not query/result/recovery correctness or test execution. |
| ownership | Aliases/includes do not create a query owner. Pointers/references/views are non-owning. Containers own their elements, which can themselves be borrowed pointers or numeric IDs. Only documented owning shared-control handles retain controls; IDs/slot-handle values do not independently keep an arena/runtime alive. |
| failure | Missing headers, ill-formed names/types, failed static assertions or active #error directives stop compilation. No runtime rejection/rollback mechanism is implemented by aliases or function prototypes. |
| cost | Preprocessing and type/constraint instantiation cost compilation. Alias/prototype syntax does not invoke the declared operation; any included definitions keep their own initialization effects. |
| Design | [tests/unit/physical_api_test.cpp](../../../../../tests/unit/physical_api_test.cpp), [docs/physical_runtime.md](../../../../physical_runtime.md), [docs/code_review.md](../../../../code_review.md) |

## B0008

[Lines 57–63](../../../../../tests/unit/physical_api_test.cpp#L57); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct DirectFixture {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Bundle catalog, query, manual tree, and typed constants for direct physical API cases. |
| inputs / outputs | Contains Catalog, Query, FreeConnexTree, Date defaulted from 2024-02-29, and Decimal defaulted from 123.40. |
| invariants | This record is test data; its definition does not validate its members. |
| ownership | The record owns its values and is returned/copied by fixture helpers. |
| failure | Invalid date or decimal defaults would fail in parse; the shown literals are the selected valid values. |
| cost | Stores fixed fixture objects and two parsed scalars. |
| Design | tests/unit/physical_api_test.cpp:57-63, [include/crown/ir/physical.hpp](../../../../../include/crown/ir/physical.hpp) |

## B0009

[Lines 64–76](../../../../../tests/unit/physical_api_test.cpp#L64); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
DirectFixture direct_fixture() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Build the one-table CQ fixture for repeated-variable, typed-constant, and input checks. |
| inputs / outputs | Returns catalog v17 with one eight-field typed table, query with repeated variable 0 plus constants/ignored column, and one native node. |
| invariants | Field order is first, again, fixed_number, label, enabled, day, amount, ignored; decimal is (6,2), and x maps to first/again. |
| ownership | Returned fixture owns its catalog, query, tree, date and decimal values. |
| failure | No failure is expected from the fixed fixture construction. |
| cost | Constructs one catalog, query and one-node tree. |
| Design | tests/unit/physical_api_test.cpp:64-76, [include/crown/ir/physical.hpp](../../../../../include/crown/ir/physical.hpp), [include/crown/planner/lower.hpp](../../../../../include/crown/planner/lower.hpp) |

## B0010

[Lines 77–81](../../../../../tests/unit/physical_api_test.cpp#L77); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Row typed_row(std::int64_t first, std::int64_t again, std::string label = "keep", bool enabled = true,
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Build an eight-slot physical row matching DirectFixture field order. |
| inputs / outputs | Takes two integers plus label, Boolean, Date, Decimal, ignored string and fixed integer; returns the matching Row. |
| invariants | Defaults are keep, true, 2024-02-29, 123.40, arbitrary and 17; this helper does not validate against a catalog. |
| ownership | Returned Row owns its Value strings; parameters are local. |
| failure | Malformed-row errors are not tested here; callers select mismatch values for adapt_input. |
| cost | Constructs eight Values; omitted Date/Decimal default expressions are evaluated per call. |
| Design | tests/unit/physical_api_test.cpp:77-81 |

## B0011

[Lines 82–94](../../../../../tests/unit/physical_api_test.cpp#L82); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
DirectFixture pair_fixture() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Build a two-table native join fixture with a shared y separator. |
| inputs / outputs | Returns catalog v4 with left(x,y), right(y,z), query/head x,y,z, and native left-parent/right-child tree. |
| invariants | The child separator is VariableId 1; one directed edge is supplied. |
| ownership | Returned fixture owns catalog, query and tree. |
| failure | No failure is expected from this fixed fixture construction. |
| cost | Constructs two schemas, one two-atom query and a two-node tree. |
| Design | tests/unit/physical_api_test.cpp:82-94, [include/crown/ir/physical.hpp](../../../../../include/crown/ir/physical.hpp), [include/crown/planner/lower.hpp](../../../../../include/crown/planner/lower.hpp) |

## B0013

[Lines 96–135](../../../../../tests/unit/physical_api_test.cpp#L96); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void direct_inputs_and_result_assembly() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Check direct CQ lowering, typed input adaptation, repeated-variable filtering and ordered result reconstruction. |
| inputs / outputs | Lowers DirectFixture; accepts row (8,8) as core (8); filters unequal repeats, fixed integer 18, label other, false, date 2024-03-01 and decimal 123.41; occurrence 1 expects invalid_input_port; one assignment assembles (8,8). |
| invariants | Checks one native node/input, eight physical fields, decimal(6,2), one repeated-column equality, five tagged constants, and a two-slot repeated head. |
| ownership | Fixture and plan are local; adapted and assembled rows are owning values. |
| failure | Only invalid occurrence is expected to throw invalid_input_port; listed value mismatches return empty optional. |
| cost | One lowering, eight adaptation calls, one assignment tuple and one assembly. |
| Design | tests/unit/physical_api_test.cpp:96-135, [include/crown/ir/physical.hpp](../../../../../include/crown/ir/physical.hpp), [include/crown/planner/lower.hpp](../../../../../include/crown/planner/lower.hpp), [src/planner/lower.cpp](../../../../../src/planner/lower.cpp) |

## B0015

[Lines 137–175](../../../../../tests/unit/physical_api_test.cpp#L137); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void native_child_keys_and_storage() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Check compiled child-key/reverse-index descriptors and their use by reference plan storage. |
| inputs / outputs | Lowers pair_fixture; inserts parent row (3,7), probes child key (7), checks unknown relation/index IDs, then move-constructs and self-move-assigns storage. |
| invariants | The one edge is parent 0 to child 1; key targets share a token; reverse index is attached to parent records with the child's projection. |
| ownership | ReferencePlanStorage owns the plan and tables; tuple/key values are local. |
| failure | Only out-of-range table and index access expect unknown_relation and unknown_index. |
| cost | One lowering/insertion, one bucket probe, invariant checks and scan of the finite index list. |
| Design | tests/unit/physical_api_test.cpp:137-175, [include/crown/ir/physical.hpp](../../../../../include/crown/ir/physical.hpp), [include/crown/planner/lower.hpp](../../../../../include/crown/planner/lower.hpp), [include/crown/storage/physical.hpp](../../../../../include/crown/storage/physical.hpp), [src/storage/physical.cpp](../../../../../src/storage/physical.cpp), [include/crown/storage/reference.hpp](../../../../../include/crown/storage/reference.hpp) |

## B0017

[Lines 177–182](../../../../../tests/unit/physical_api_test.cpp#L177); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
bool same_identity(const io::QueryIdentity& left, const io::QueryIdentity& right) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Compare every QueryIdentity field asserted by the normalized-plan case. |
| inputs / outputs | Takes two borrowed identities and returns equality of canonical JSON, four digest strings, occurrence-order and variable-order vectors, and work. |
| invariants | Compares the listed fields; does not recompute digests. |
| ownership | Identity references are borrowed; result owns no state. |
| failure | No failure path is introduced. |
| cost | One JSON equality, four string equalities, two vector equalities and one scalar equality, evaluated with short circuit. JSON/string/vector comparison work depends on the compared contents. |
| Design | tests/unit/physical_api_test.cpp:177-182, [include/crown/io/identity.hpp](../../../../../include/crown/io/identity.hpp) |

## B0018

[Lines 183–194](../../../../../tests/unit/physical_api_test.cpp#L183); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
frontend::NormalizedSql normalized_self_join() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Bind and normalize the finite SQL self-join fixture for replay and ownership checks. |
| inputs / outputs | Uses catalog v23 with r(x int64,y int64,flag Boolean) and SQL selecting DISTINCT l.x,l.y,q.y AS z,l.x AS again, joined on l.y=q.x with l.flag IS TRUE. |
| invariants | Binding/normalization diagnostics become std::runtime_error containing code and message. |
| ownership | Catalog, SQL and returned program are local owning values. |
| failure | A binding or normalization diagnostic fails the fixture immediately. |
| cost | One bind and one normalize of the fixed SQL. |
| Design | tests/unit/physical_api_test.cpp:183-194, [include/crown/frontend/bind.hpp](../../../../../include/crown/frontend/bind.hpp), [src/frontend/bind.cpp](../../../../../src/frontend/bind.cpp), [include/crown/frontend/normalize.hpp](../../../../../include/crown/frontend/normalize.hpp), [src/frontend/normalize.cpp](../../../../../src/frontend/normalize.cpp) |

## B0019

[Lines 195–209](../../../../../tests/unit/physical_api_test.cpp#L195); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
FreeConnexTree normalized_self_join_tree(const Query& query) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Build the caller-supplied generalized-root tree after checking exact normalized core/output IDs. |
| inputs / outputs | Takes Query and returns three nodes: generalized y root, native (x,y) left alias, native (y,z) right alias. |
| invariants | Requires 3 variables, 2 atoms with IDs (0,1)/(1,2), and outputs (0,1,2,0); exact to this fixture. |
| ownership | Input query is borrowed; returned tree owns its vectors. |
| failure | Fixture-shape mismatch throws std::runtime_error through check. |
| cost | Three shape checks and one three-node tree construction. |
| Design | tests/unit/physical_api_test.cpp:195-209, [include/crown/ir/physical.hpp](../../../../../include/crown/ir/physical.hpp) |

## B0021

[Lines 211–277](../../../../../tests/unit/physical_api_test.cpp#L211); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void normalized_replay_identity_and_ownership() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Check normalized lowering, alias routing, assignment assembly, v2 replay, ownership, and moved-from behavior for one SQL self-join. |
| inputs / outputs | Uses normalized_self_join and its tree; tests left/right rows, one inconsistent assignment key 99, one forged output label, caller-buffer mutation after plan copy, then physical write/read. |
| invariants | Checks schema v2, source catalog v23, aliases on base 0/logical 0 and 1, full expected identity, 3 nodes, local TRUE filtering, output (10,20,30,10), not-implemented runtime bounds, byte-identical replay, and descriptor-equal/token-distinct restored layouts. |
| ownership | Plan owns normalized source/AST/core/adapters; copy and move preserve stored program. Restored layout tokens are independent. |
| failure | Expected codes: invalid_assignment, invalid_document for forged program, invalid_physical_plan for moved-from route. |
| cost | One bind/normalize and lower, three input adaptations, two assemblies, copy/move, and one serialization replay. |
| Design | tests/unit/physical_api_test.cpp:211-277, [include/crown/ir/physical.hpp](../../../../../include/crown/ir/physical.hpp), [include/crown/planner/lower.hpp](../../../../../include/crown/planner/lower.hpp), [src/planner/lower.cpp](../../../../../src/planner/lower.cpp), [include/crown/io/physical.hpp](../../../../../include/crown/io/physical.hpp), [src/io/physical.cpp](../../../../../src/io/physical.cpp), [include/crown/io/identity.hpp](../../../../../include/crown/io/identity.hpp), [src/io/identity.cpp](../../../../../src/io/identity.cpp) |

## B0023

[Lines 279–340](../../../../../tests/unit/physical_api_test.cpp#L279); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void physical_options_and_replay_boundaries() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Check exact lowering/identity work boundaries, host caps, imported replay caps, and producer-options schema errors. |
| inputs / outputs | Measures direct-fixture counters; exact caps pass; tests work one below, identity one below/zero, host work one below, host identity one below, import identity one below; round-trips unlimited producer options and mutates version/arithmetic/planner. |
| invariants | Host caps constrain these calls without rewriting producer limits or caller policy tags; import caps preserve serialized producer options. |
| ownership | Options, limits, documents and plans are local; no external configuration is changed. |
| failure | Listed cap failures expect resource_limit; malformed options expect unsupported_version or invalid_policy. |
| cost | Several fixed plan lowerings and one physical/options write-read pair; counters are fixture-derived, not benchmarked. |
| Design | tests/unit/physical_api_test.cpp:279-340, [include/crown/ir/physical.hpp](../../../../../include/crown/ir/physical.hpp), [include/crown/planner/lower.hpp](../../../../../include/crown/planner/lower.hpp), [include/crown/io/physical.hpp](../../../../../include/crown/io/physical.hpp), [src/io/physical.cpp](../../../../../src/io/physical.cpp) |

## B0025

[Lines 342–368](../../../../../tests/unit/physical_api_test.cpp#L342); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void physical_artifact_rejects_corruption() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Reject selected edits to a serialized direct physical-plan artifact. |
| inputs / outputs | Edits projection field, layout type, work, three digests, two guarantee claims, node scope and verification.valid; also tries unknown field, version 999 and duplicate schema_version text. |
| invariants | Ten binding edits expect physical_binding; future field and duplicate key expect invalid_document; version 999 expects unsupported_version. |
| ownership | Each modified Json is a local copy; no artifact is persisted. |
| failure | Only the enumerated corruption mutations and codes are asserted. |
| cost | One lowering/write, ten binding mutations and three document-level malformed reads. |
| Design | tests/unit/physical_api_test.cpp:342-368, [include/crown/ir/physical.hpp](../../../../../include/crown/ir/physical.hpp), [include/crown/io/physical.hpp](../../../../../include/crown/io/physical.hpp), [src/io/physical.cpp](../../../../../src/io/physical.cpp), [include/crown/planner/lower.hpp](../../../../../include/crown/planner/lower.hpp) |

## B0027

[Lines 370–404](../../../../../tests/unit/physical_api_test.cpp#L370); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void tree_validation_and_legacy_grounding(const std::filesystem::path& root) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Check caller validation, mandatory revalidation and replay of one frozen v1 normalized fixture after v2 grounding. |
| inputs / outputs | Takes repository root; clears direct-tree scope; reads normalized-v1-fixed-head.json; tries stale/empty trees and one grounded tree; adapts rows (1,7) and (2,7). |
| invariants | Caller report is invalid and forging its valid flag does not bypass lower_tree. Upgrade gives schema v2, two core variables, one core head slot, one constant input-adapter column and two SQL outputs; row (1,7) emits (7), row (2,7) filters. |
| ownership | Report/tree/plan and loaded bytes are local; frozen JSON is read only. |
| failure | Expected invalid_plan for invalid direct, stale and empty trees; read_file fails if fixture cannot be opened. |
| cost | One validation/lower attempt, one read/upgrade, three normalized lowerings and two adaptations. |
| Design | tests/unit/physical_api_test.cpp:370-404, [include/crown/planner/verify.hpp](../../../../../include/crown/planner/verify.hpp), [src/planner/verify.cpp](../../../../../src/planner/verify.cpp), [include/crown/planner/lower.hpp](../../../../../include/crown/planner/lower.hpp), [include/crown/io/normalization.hpp](../../../../../include/crown/io/normalization.hpp), [include/crown/io/physical.hpp](../../../../../include/crown/io/physical.hpp), [tests/frontend/schema/normalized-v1-fixed-head.json](../../../../../tests/frontend/schema/normalized-v1-fixed-head.json) |

## B0028

[Lines 405–407](../../../../../tests/unit/physical_api_test.cpp#L405); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L405-L407:sha256:9e375a3cb3a2cbe2f9ded9c8296a6ab66848cc826fd71f919246acb17e0bd455
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Close the recorded declaration scopes in physical_api_test.cpp: namespace (anonymous). |
| inputs / outputs | Preceding namespace, type or initializer declarations in; completed lexical boundary out. |
| invariants | Brace-opening context is recorded in root-scope-context-v1.json. These are declaration/initializer boundaries, not an independent update, validation or recovery operation. |
| ownership | Enclosing objects and borrowed fields keep their declared ownership. This punctuation creates no new owner. |
| failure | Malformed scope syntax is a compile error. Any initializer/constructor failure belongs to the enclosing object declaration. |
| cost | No separate loop, guard or engine call is introduced by the delimiter; enclosing initialization and object lifetime still have their actual costs. |
| Design | [tests/unit/physical_api_test.cpp](../../../../../tests/unit/physical_api_test.cpp), [docs/physical_runtime.md](../../../../physical_runtime.md), [docs/code_review.md](../../../../code_review.md) |

## B0029

[Lines 408–422](../../../../../tests/unit/physical_api_test.cpp#L408); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
int main(int argc, char** argv) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Provide the physical API test executable's finite entry sequence. |
| inputs / outputs | Requires one repository argument, then calls the six named test bodies in source order and returns an integer status. |
| invariants | A std::exception is printed and maps to 1; success prints a fixed line and returns 0. |
| ownership | Process and test fixtures are local; no cross-process state is asserted. |
| failure | Wrong argc fails through check; escaping std::exception from a test is caught. |
| cost | One argc check and six test calls; no benchmark. |
| Design | tests/unit/physical_api_test.cpp:408-422 |
