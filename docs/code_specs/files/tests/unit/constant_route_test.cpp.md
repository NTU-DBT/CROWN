# `tests/unit/constant_route_test.cpp` — block usage map

[Source](../../../../../tests/unit/constant_route_test.cpp) · [Source index](../../../README.md) · [Subsystem contracts](../../../subsystem_contracts.md) · [Reviewed primitives](../../../primitives.md)

Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection.

Snapshot SHA-256: `c33aae68f71b8c27e1a58442585156715d211acf2e56101744a10a44151107d9`. 404 lines partitioned into 27 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [tests](../../../subsystem_contracts.md#tests). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/code_review.md](../../../../code_review.md), [docs/reference_fuzz.md](../../../../reference_fuzz.md), [docs/task_ledger.md](../../../../task_ledger.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–21](../../../../../tests/unit/constant_route_test.cpp#L1) | Imports dependencies; declares namespace scope; declares aliases; declares values/defaults or compile-time conditions. | source comment (unverified): // Structural height belongs to the retained body, independently of the empty · [reviewed contract](#b0001) |
| [B0002 · 22–32](../../../../../tests/unit/constant_route_test.cpp#L22) | Type/record definition: struct Input | returns sql?planner::lower_normalized(*sql,{},options):; source comment (unverified): // Structural height belongs to the retained body, independently of the empty · [reviewed contract](#b0002) |
| [B0003 · 33–40](../../../../../tests/unit/constant_route_test.cpp#L33) | Callable definition: Input unary() | calls std::move; returns {std::move(f),{},1,1} · [reviewed contract](#b0003) |
| [B0004 · 41–45](../../../../../tests/unit/constant_route_test.cpp#L41) | Callable definition: Input multiple() | calls c02_test::fixture, push_back, std::move; returns {std::move(f),{},2,3}; growth push_back · [reviewed contract](#b0004) |
| [B0005 · 46–58](../../../../../tests/unit/constant_route_test.cpp#L46) | Callable definition: Input normalized(bool exists) | calls unary, frontend::bind_sql, check, frontend::normalize_sql; guard check(std::holds_alternative&lt;frontend::BoundSql&gt;(bound),"constant SQL did not bind");; returns {std::move(f),std::move(sql),1,1} · [reviewed contract](#b0005) |
| [B0006 · 59–62](../../../../../tests/unit/constant_route_test.cpp#L59) | Callable definition: template&lt;class F&gt; void rejects(F action,std::string_view code) | calls action, check, code, std::runtime_error; guard try{action();}catch(const Error& error){check(error.code()==code,"wrong constant-route rejection");… · [reviewed contract](#b0006) |
| [B0007 · 63–67](../../../../../tests/unit/constant_route_test.cpp#L63) | Callable definition: void controller_only(const resource::MemoryAccount& account) | calls check_invariants, statistics, check, resource::MemoryAccount::control_bytes; guard check(now.allocations==1 && now.requested_bytes==resource::MemoryAccount::control_bytes(), · [reviewed contract](#b0007) |
| [B0008 · 68–76](../../../../../tests/unit/constant_route_test.cpp#L68) | Callable definition: void empty_operator(const CompiledProgram& plan) | calls check, route, tree, empty; guard check(plan.route()==PhysicalRoute::constant_false && !plan.tree().root && plan.tree().nodes.empty(), · [reviewed contract](#b0008) |
| [B0009 · 77–79](../../../../../tests/unit/constant_route_test.cpp#L77) | Explanatory comments or spacing. | source comment (unverified): // The unchanged public lowerer and full artifact reader are independent · [reviewed contract](#b0009) |
| [B0010 · 80–128](../../../../../tests/unit/constant_route_test.cpp#L80) | Callable definition: void native_matrix(const Input& input,bool indexed) | calls check, empty, c02_test::candidates, io::write_candidate_snapshot; guard check(input.core.query.contradiction && !input.core.query.atoms.empty() && input.height&gt;0,; 1 loop sites; source comment (unverified): // The unchanged public lowerer and full artifact reader are independent · [reviewed contract](#b0010) |
| [B0011 · 129–129](../../../../../tests/unit/constant_route_test.cpp#L129) | Explanatory comments or spacing. |  |
| [B0012 · 130–140](../../../../../tests/unit/constant_route_test.cpp#L130) | Callable definition: void heat(runtime::PhysicalRuntime& owner) | calls configure_workload_statistics, c05_test::counters, plan, source_catalog; guard check(!owner.has_answer() && owner.sequence()==4,"constant source updates changed empty answer/epoc…; growth insert; 1 loop sites · [reviewed contract](#b0012) |
| [B0013 · 141–165](../../../../../tests/unit/constant_route_test.cpp#L141) | Callable definition: void zero_scores(const pr::Result& result,std::size_t height,std::size_t count,std::size_t tables) | calls check, scores, size, selected; guard check(result.scores().size()==count && result.selected().height()==height &&; 2 loop sites · [reviewed contract](#b0013) |
| [B0014 · 166–168](../../../../../tests/unit/constant_route_test.cpp#L166) | Explanatory comments or spacing. | source comment (unverified): // Real input/no-op/unused-table traffic fixes W=4 independently of the model. · [reviewed contract](#b0014) |
| [B0015 · 169–237](../../../../../tests/unit/constant_route_test.cpp#L169) | Callable definition: void models_and_selection(const Input& input,bool indexed) | calls c02_test::candidates, io::write_candidate_snapshot, canonical, resize; guard check(!rr::rank_current(family,owner,strict).result,"disabled census manufactured an exact constant…; growth emplace_back, insert, resize; 3 loop sites; source comment (unverified): // Real input/no-op/unused-table traffic fixes W=4 independently of the model. · [reviewed contract](#b0015) |
| [B0016 · 238–240](../../../../../tests/unit/constant_route_test.cpp#L238) | Explanatory comments or spacing. | source comment (unverified): // All observed allocation positions are faulted, then retried on the same · [reviewed contract](#b0016) |
| [B0017 · 241–297](../../../../../tests/unit/constant_route_test.cpp#L241) | Callable definition: void native_faults_and_limits(const Input& input,bool indexed) | calls c02_test::candidates, candidate, io::write_candidate_snapshot, CompiledProgram::standalone; guard check(expected&gt;0 && expected&lt;4096,"constant native fault calibration exceeded bound");; 4 loop sites; source comment (unverified): // All observed allocation positions are faulted, then retried on the same · [reviewed contract](#b0017) |
| [B0018 · 298–300](../../../../../tests/unit/constant_route_test.cpp#L298) | Explanatory comments or spacing. | source comment (unverified): // A failed replacement must leave the funded warm cache, its diagnostics and · [reviewed contract](#b0018) |
| [B0019 · 301–344](../../../../../tests/unit/constant_route_test.cpp#L301) | Callable definition: void selection_faults(bool indexed) | calls unary, c02_test::candidates, canonical, resize; guard check(expected&gt;0 && expected&lt;4096,"constant selection fault calibration exceeded bound");; growth resize; 3 loop sites; source comment (unverified): // A failed replacement must leave the funded warm cache, its diagnostics and · [reviewed contract](#b0019) |
| [B0020 · 345–345](../../../../../tests/unit/constant_route_test.cpp#L345) | Explanatory comments or spacing. |  |
| [B0021 · 346–366](../../../../../tests/unit/constant_route_test.cpp#L346) | Callable definition: void owner_boundaries() | calls unary, c02_test::candidates, canonical, resize; guard check(!rejected.selection && rejected.stop==ps::Stop::boundary_unavailable,"constant shortcut obser…; growth insert, resize · [reviewed contract](#b0021) |
| [B0022 · 367–367](../../../../../tests/unit/constant_route_test.cpp#L367) | Explanatory comments or spacing. |  |
| [B0023 · 368–386](../../../../../tests/unit/constant_route_test.cpp#L368) | Callable definition: void compatibility() | calls c02_test::candidates, candidate, s04_runtime::options, planner::lower_tree; guard check(io::write_physical(actual)==io::write_physical(old),"empty-body raw claims/hash/counters chan…; 3 loop sites · [reviewed contract](#b0023) |
| [B0024 · 387–387](../../../../../tests/unit/constant_route_test.cpp#L387) | Explanatory comments or spacing. |  |
| [B0025 · 388–400](../../../../../tests/unit/constant_route_test.cpp#L388) | Callable definition: void run() | calls unary, multiple, normalized, native_matrix; 3 loop sites · [reviewed contract](#b0025) |
| [B0026 · 401–401](../../../../../tests/unit/constant_route_test.cpp#L401) | Closes surrounding scope/type. | source comment (unverified): // namespace · [reviewed contract](#b0026) |
| [B0027 · 402–404](../../../../../tests/unit/constant_route_test.cpp#L402) | Callable definition: int main() | calls run, what; returns 0; 1 · [reviewed contract](#b0027) |

## B0001

[Lines 1–21](../../../../../tests/unit/constant_route_test.cpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
constexpr std::uint64_t allowance=64*1024*1024;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Define test-only subsystem aliases and the explicit 64 MiB receiver budget. |
| inputs / outputs | Imports reusable selection/runtime/global-allocation-fault fixtures and names their APIs; allowance is a literal byte ceiling for separately created test accounts. |
| invariants | The test translation unit alone replaces operator new/delete through index_allocation.hpp. Aliases add no production abstractions or implicit accounts. |
| ownership | Fixture/global fault hooks are process-local; per-case owners are explicit local values. |
| failure | There is no handler in this scaffolding; test assertions and entry-point reporting handle failures. |
| cost | Compile-time names and one scalar constant; fault instrumentation exists only in this test binary. |
| Design | [docs/query_memory.md](../../../../query_memory.md) |

## B0002

[Lines 22–32](../../../../../tests/unit/constant_route_test.cpp#L22); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct Input {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Keep the source fixture, optional real normalized SQL and literal structural oracle for one nonempty contradiction case. |
| inputs / outputs | Owns core Catalog/Query, optional NormalizedSql, expected original height and expected candidate count; canonical() supplies the independent public physical lowering oracle. |
| invariants | height describes the retained body (one or two), not the empty operator. Normalized cases must originate from bind/normalize factories, not manual flag edits. |
| ownership | The aggregate owns compiler DTOs; each invocation later admits independent native owners. |
| failure | Construction and member moves may allocate through DTOs; no production exception layer is introduced. |
| cost | Test-only retained source metadata plus scalar expectations; copies/moves follow the underlying compiler DTO costs. |
| Design | [docs/physical_plans.md §Admission and routes](../../../../physical_plans.md), [docs/candidate_alternatives.md](../../../../candidate_alternatives.md) |

```text
PhysicalPlan canonical(bool indexed) const {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Create a constant-false artifact through the unchanged public lowerer with an explicit canonical empty tree. |
| inputs / outputs | Backend flag selects reference defaults or the established indexed options; optional SQL selects lower_normalized, otherwise lower_tree receives the exact core model. |
| invariants | This oracle does not derive its geometry from the new native replan/rank/select branches. Source/options/backend and empty-tree admission remain independently checked. |
| ownership | Returns an immutable compiler PhysicalPlan; input source is borrowed for the call. |
| failure | Public validation/resource/allocation errors propagate to the test runner. |
| cost | Public source replay/validation/lowering and compiler allocations; the oracle is explicit test work, not an execution-path primitive. |
| Design | [docs/physical_plans.md §Admission and routes](../../../../physical_plans.md) |

## B0003

[Lines 33–40](../../../../../tests/unit/constant_route_test.cpp#L33); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Input unary() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Build the smallest body-bearing contradiction with a physical unused-table denominator control. |
| inputs / outputs | Returns R(x) with head x, contradiction=true and unused U; expected structural minimum is one and retained candidate count is one. |
| invariants | The body is deliberately nonempty so the regression cannot pass by exercising only the old empty-body route. |
| ownership | Returns owning catalog/query DTOs using local move construction. |
| failure | Standard fixture allocation may throw; no local recovery is needed. |
| cost | Fixed small test metadata construction. |
| Design | [docs/physical_plans.md §Admission and routes](../../../../physical_plans.md), [docs/planner_proofs.md §Independent lower-bound evidence and strict limits](../../../../planner_proofs.md) |

## B0004

[Lines 41–45](../../../../../tests/unit/constant_route_test.cpp#L41); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Input multiple() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Extend the established three-atom fixture into a multi-candidate contradiction regression. |
| inputs / outputs | Retains R/S/T structure, marks contradiction, adds unused U and returns literal structural height two with three candidates. |
| invariants | The family must retain three distinct original raw trees and deterministic full-key tie behavior even though all executable operators are empty. |
| ownership | Owns the returned compiler DTOs; existing fixture is moved into the aggregate. |
| failure | Fixture allocation propagates to the runner. |
| cost | Small source construction; later exact candidate generation is separate test work. |
| Design | [docs/physical_plans.md §Admission and routes](../../../../physical_plans.md), [docs/candidate_alternatives.md](../../../../candidate_alternatives.md) |

## B0005

[Lines 46–58](../../../../../tests/unit/constant_route_test.cpp#L46); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Input normalized(bool exists) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Exercise real SQL normalization of a false predicate for both rows and EXISTS output. |
| inputs / outputs | Bind quoted R against a typed catalog, normalize WHERE 1=0, retain either repeated x output plus a constant column or the EXISTS wrapper, then return expected structural height/count one. |
| invariants | Asserts the normalized core still has a contradictory nonempty body. Rows and EXISTS semantics remain distinct, and no manually forged normalized record is accepted. |
| ownership | Owns BoundSql/NormalizedSql intermediates and the returned core/normalized source. |
| failure | Variant admission assertions stop the test if bind/normalize rejects; allocation/errors propagate. |
| cost | Real compiler binding and normalization with ordinary DTO allocations; this is a source-boundary test, not runtime parsing. |
| Design | [docs/physical_plans.md §Admission and routes](../../../../physical_plans.md), [docs/sql_normalization.md](../../../../sql_normalization.md), [docs/sql_binding.md](../../../../sql_binding.md) |

## B0006

[Lines 59–62](../../../../../tests/unit/constant_route_test.cpp#L59); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
template<class F> void rejects(F action,std::string_view code) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Require a public boundary to reject with one exact Error diagnostic code. |
| inputs / outputs | Invoke action; accept only crown::Error carrying the expected borrowed code. A successful action or wrong code throws a test failure. |
| invariants | Other exception types propagate and cannot accidentally satisfy the expected invalid-input assertion. |
| ownership | The callable and expected string_view are borrowed during the call; caught exception owns its diagnostic. |
| failure | One test-only catch verifies the error contract; it performs no recovery or production error conversion. |
| cost | One invocation plus failure-path diagnostic comparison; successful test rejection is not timed as production work. |
| Design | [docs/physical_plans.md §Admission and routes](../../../../physical_plans.md) |

## B0007

[Lines 63–67](../../../../../tests/unit/constant_route_test.cpp#L63); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void controller_only(const resource::MemoryAccount& account) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Verify that releasing a result returns its dedicated receiver to the funded controller alone. |
| inputs / outputs | Check account invariants, then require one allocation and exactly MemoryAccount::control_bytes current requested bytes. |
| invariants | Checks current resident ownership, not cumulative allocation history or RSS; the controller remains legitimately charged. |
| ownership | Borrows the receiver account and retains no result storage. |
| failure | Invariant/assertion failure reaches the test runner. |
| cost | Explicit account diagnostic work; never installed in production hot paths. |
| Design | [docs/query_memory.md](../../../../query_memory.md) |

## B0008

[Lines 68–76](../../../../../tests/unit/constant_route_test.cpp#L68); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void empty_operator(const CompiledProgram& plan) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Assert the canonical empty physical representation independently of original query-body height. |
| inputs / outputs | Requires constant_false, no root/nodes, a valid zero-height/zero-edge-depth empty report, and no executable node/input/relation/index/edge/enumeration-step arrays. |
| invariants | A zero-result route label alone is insufficient: retained body geometry or stale validation report must fail the assertion. |
| ownership | Borrows immutable program spans and reads scalar/vector sizes. |
| failure | One test assertion identifies any noncanonical geometry; no mutation/cleanup occurs here. |
| cost | Fixed metadata/empty-array checks; this is a test predicate. |
| Design | [docs/physical_plans.md §Admission and routes](../../../../physical_plans.md) |

## B0009

[Lines 77–79](../../../../../tests/unit/constant_route_test.cpp#L77); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L77-L79:sha256:cb6cd78ad384801dea92e9dab11cbf007af5792da0ff056faaf006a19de4fc86
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Explain the adjacent source contract: The unchanged public lowerer and full artifact reader are independent oracles for native lowering, including work, source, backend and layouts. |
| inputs / outputs | Human-readable source note in; no executable output or checked receipt. |
| invariants | This comment states context or a limitation. It does not itself enforce or prove the described behavior; use the adjacent implementation and its scoped contract. |
| ownership | Source text only; no object or resource lifetime is created. |
| failure | No runtime failure path in this comment; source encoding/comment syntax still belongs to compilation. |
| cost | No runtime operations from the comment. Any work described in the note belongs to the adjacent operation. |
| Design | [tests/unit/constant_route_test.cpp](../../../../../tests/unit/constant_route_test.cpp), [docs/physical_plans.md](../../../../physical_plans.md), [docs/code_review.md](../../../../code_review.md) |

## B0010

[Lines 80–128](../../../../../tests/unit/constant_route_test.cpp#L80); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void native_matrix(const Input& input,bool indexed) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Compare native replan and artifact/report boundaries with an independent public constant-operator oracle. |
| inputs / outputs | Admit the literal positive-height family, assert raw nonempty public-lowerer rejection, replan every candidate into a distinct receiver, compare full physical JSON, read/replay compiler artifacts, verify explain boundaries and reject tree/hash tampering. |
| invariants | Counts every new native operator allocation in the receiver while the immutable source account stays unchanged. Original candidate/family JSON and positive-height QueryExplanation remain unchanged; PlanExplanation reports checked_constant_operator and rejects incompatible original-body evidence. |
| ownership | Retains the source/family, places the new native operator in a separate funded account, scopes compiler replay owners, then verifies receiver cleanup. |
| failure | All assertion/public validation/allocation failures fail the case; expected malformed-artifact and explanation rejections use the test helper. |
| cost | Full public/native compilation, serialization, artifact replay and explicit diagnostics for every retained candidate/backend; no performance benchmark is claimed. |
| Design | [docs/physical_plans.md §Admission and routes](../../../../physical_plans.md), [docs/query_memory.md](../../../../query_memory.md), [docs/observability.md](../../../../observability.md), [docs/candidate_alternatives.md](../../../../candidate_alternatives.md) |

## B0012

[Lines 130–140](../../../../../tests/unit/constant_route_test.cpp#L130); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void heat(runtime::PhysicalRuntime& owner) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Create a literal four-input committed workload census for the constant operator. |
| inputs / outputs | Enable counters, insert R(1), repeat that insertion, erase absent R(99), then insert into the final unused table; require sequence four and no core answers. |
| invariants | Duplicate/absent no-ops and unused-table input remain physical input events. They establish W=4 independently of any ranking calculation. |
| ownership | Mutates the supplied actual runtime through ordinary committed apply operations; temporary public rows live only through each call. |
| failure | Runtime or assertion failures propagate without a test-local recovery layer. |
| cost | Four real update admissions/commits plus counter configuration; test workload setup is separate from the model score. |
| Design | [docs/ranking.md §Exact score reconstruction](../../../../ranking.md), [docs/physical_runtime.md §Input and source-row identity](../../../../physical_runtime.md) |

## B0013

[Lines 141–165](../../../../../tests/unit/constant_route_test.cpp#L141); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void zero_scores(const pr::Result& result,
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Check literal constant-operator scores and the unchanged original positive-height family. |
| inputs / outputs | Require the expected candidate count/height, compute the smallest complete structural key, then check depth 0/4 with all table weights/zero terms or slots 0 with empty bound/term arrays and an owned canonical modeled plan. |
| invariants | Read fields only under their effective policy. Original proof/candidate/score heights remain one or two; placeholder fields from a different policy are not evidence. Full-key order resolves all constant-score ties. |
| ownership | Borrows immutable Result/score/model owners; only the local best-key string is test-owned scratch. |
| failure | Any score/provenance/geometry mismatch throws a test assertion. |
| cost | Linear retained-score/table scans and explicit key copies; assertion instrumentation is test-only. |
| Design | [docs/ranking.md §Exact score reconstruction](../../../../ranking.md), [docs/selection.md](../../../../selection.md) |

## B0014

[Lines 166–168](../../../../../tests/unit/constant_route_test.cpp#L166); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L166-L168:sha256:64c01c488cb0c045b8562b943aa0ca19f0a04a2b032ac1e730aaa10faada2611
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Explain the adjacent source contract: Real input/no-op/unused-table traffic fixes W=4 independently of the model. Each source/policy/cache path must keep the original positive-height family. |
| inputs / outputs | Human-readable source note in; no executable output or checked receipt. |
| invariants | This comment states context or a limitation. It does not itself enforce or prove the described behavior; use the adjacent implementation and its scoped contract. |
| ownership | Source text only; no object or resource lifetime is created. |
| failure | No runtime failure path in this comment; source encoding/comment syntax still belongs to compilation. |
| cost | No runtime operations from the comment. Any work described in the note belongs to the adjacent operation. |
| Design | [tests/unit/constant_route_test.cpp](../../../../../tests/unit/constant_route_test.cpp), [docs/physical_plans.md](../../../../physical_plans.md), [docs/code_review.md](../../../../code_review.md) |

## B0015

[Lines 169–237](../../../../../tests/unit/constant_route_test.cpp#L169); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void models_and_selection(const Input& input,bool indexed) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Cover whole-family ranking, source variants, mandatory zero-slot constraints and exact cache reuse on real constant owners. |
| inputs / outputs | Initialize the independent canonical plan over empty source tables; reject disabled/empty census as depth facts and verify configured height fallback. Heat W=4, check the SQL view returned directly by the public results cursor (including EXISTS false), rank pure/current policies, select from DTO/native bases and valid DirectCQ sources, then cold-write/read-only-hit each exact cache entry. |
| invariants | All candidates are evaluated and literal zero-score checks preserve original h1/h2 proof and full-key ties. SQL DirectCQ mismatch rejects; pure DirectCQ without evidence exercises initial compiler lowering. Later committed no-op makes the old actual-owner evidence stale. PhysicalRuntime::results already applies SQL output mapping; the test must not map those public rows a second time. |
| ownership | Local runtime owns source state; captures, returned selections and caches retain their funded immutable payloads. Source/family JSON remains unchanged. |
| failure | Expected unavailable/mismatched states must publish no improper result; any unexpected stop or artifact mismatch fails the test. |
| cost | Several full captures/model/lower/cache paths per policy/source/backend with explicit JSON comparison; this is semantic coverage, not timing evidence. |
| Design | [docs/ranking.md §Exact score reconstruction](../../../../ranking.md), [docs/selection.md](../../../../selection.md), [docs/selection_accounting.md §Atomic publication](../../../../selection_accounting.md) |

## B0016

[Lines 238–240](../../../../../tests/unit/constant_route_test.cpp#L238); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L238-L240:sha256:5c4d7e4e73ecdbebc2398572c067b4d5db3de2d9484612545155fed458ba4f85
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Explain the adjacent source contract: All observed allocation positions are faulted, then retried on the same source/receiver. A distinct account makes accidental source-account funding visible. |
| inputs / outputs | Human-readable source note in; no executable output or checked receipt. |
| invariants | This comment states context or a limitation. It does not itself enforce or prove the described behavior; use the adjacent implementation and its scoped contract. |
| ownership | Source text only; no object or resource lifetime is created. |
| failure | No runtime failure path in this comment; source encoding/comment syntax still belongs to compilation. |
| cost | No runtime operations from the comment. Any work described in the note belongs to the adjacent operation. |
| Design | [tests/unit/constant_route_test.cpp](../../../../../tests/unit/constant_route_test.cpp), [docs/physical_plans.md](../../../../physical_plans.md), [docs/code_review.md](../../../../code_review.md) |

## B0017

[Lines 241–297](../../../../../tests/unit/constant_route_test.cpp#L241); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void native_faults_and_limits(const Input& input,bool indexed) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Sweep native construction failure positions and exact receiver/work/source-credit admission boundaries. |
| inputs / outputs | Calibrate native allocation count, inject failure at every observed position plus a success sentinel, retry on the same source/receiver, compare full artifacts and preserved family, and destroy under allocation denial. Calibrate peak bytes for exact/one-under caps, check exact/one-under lower work, and reject zero identity or applicable SQL replay/normalize credits. |
| invariants | Failure cannot publish a partial operator, alter held results/proof/source, leak current receiver payload or require teardown allocation. Counters distinguish real new allocations from retained immutable source ownership. |
| ownership | Keeps an independently held result and explicit source/receiver accounts; each trial result is released before current resident state is compared. |
| failure | Expected std::bad_alloc, MemoryFailure(limit) and dimension-specific ReplanFailure are checked by test-only catches. A missed position or wrong fault category fails rather than being swallowed. |
| cost | One complete native construction per fault position plus retries and explicit artifact/diagnostic work; exhaustive sweep cost is test-only and bounded by the calibrated count assertion. |
| Design | [docs/physical_plans.md §Admission and routes](../../../../physical_plans.md), [docs/query_memory.md](../../../../query_memory.md), [docs/ranking_accounting.md §Native capture and lowering boundaries](../../../../ranking_accounting.md) |

## B0018

[Lines 298–300](../../../../../tests/unit/constant_route_test.cpp#L298); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L298-L300:sha256:5185d742eed0b6a70764a4335544db072cba8dd69a533156e29435547767432a
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Explain the adjacent source contract: A failed replacement must leave the funded warm cache, its diagnostics and prior result whole. This covers a different-policy miss and the zero-slot assessment. |
| inputs / outputs | Human-readable source note in; no executable output or checked receipt. |
| invariants | This comment states context or a limitation. It does not itself enforce or prove the described behavior; use the adjacent implementation and its scoped contract. |
| ownership | Source text only; no object or resource lifetime is created. |
| failure | No runtime failure path in this comment; source encoding/comment syntax still belongs to compilation. |
| cost | No runtime operations from the comment. Any work described in the note belongs to the adjacent operation. |
| Design | [tests/unit/constant_route_test.cpp](../../../../../tests/unit/constant_route_test.cpp), [docs/physical_plans.md](../../../../physical_plans.md), [docs/code_review.md](../../../../code_review.md) |

## B0019

[Lines 301–344](../../../../../tests/unit/constant_route_test.cpp#L301); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void selection_faults(bool indexed) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Check atomic whole-cache replacement and retry for constant depth/slot selection under allocation denial. |
| inputs / outputs | Warm a one-entry cache with height selection, calibrate a different policy with mandatory slots&lt;=0, fault each observed allocation plus the success sentinel, then retry. Also deny aggregate processing or native lowering work and require resource_limit. |
| invariants | A failed replacement preserves the old selection, complete cache statistics/content ownership, current runtime account storage and actual sequence/empty answers. Success leaves one complete cache entry; zero slot value cannot bypass processing/lowering limits. |
| ownership | Each trial owns its warm cache and prior selection while the actual source runtime/capture are retained. Failed private drafts must release their storage before comparison. |
| failure | Expected selection allocation_failure/resource_limit are explicit result checks, not a broad catch accepting any error. Any partial result or changed cache/runtime fails the test. |
| cost | Calibration plus one full replacement attempt and retry per observed allocation; fault hooks and repeated cache setup live only in this binary. |
| Design | [docs/selection_accounting.md §Atomic publication](../../../../selection_accounting.md), [docs/query_memory.md](../../../../query_memory.md), [docs/ranking.md §Exact score reconstruction](../../../../ranking.md) |

## B0021

[Lines 346–366](../../../../../tests/unit/constant_route_test.cpp#L346); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void owner_boundaries() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Verify that constant-slot shortcuts still honor Delta and session current-owner boundaries. |
| inputs / outputs | Build a unary constant Delta owner, commit one update, select at its committed state, reject selection while a second epoch is pending, roll back, then select from a live typed session and reject after drop. |
| invariants | A constant result does not authorize observing private prefixes or released owners. Slot zero still requires the documented current-owner capture boundary. |
| ownership | Local Delta/session owners and pending token own their runtime/private state; rollback releases the pending prefix explicitly. |
| failure | Expected private/released calls must return boundary_unavailable with no selection; all other failures stop the test. |
| cost | A small real Delta/session lifecycle plus current captures and modeled lowering; no new production lease or lock is introduced. |
| Design | [docs/selection.md](../../../../selection.md), [docs/physical_runtime.md §Prepare, busy reads, and commit](../../../../physical_runtime.md) |

## B0023

[Lines 368–386](../../../../../tests/unit/constant_route_test.cpp#L368); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void compatibility() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Protect existing empty-body raw artifacts and ordinary noncontradictory tree lowering. |
| inputs / outputs | For true/false empty bodies and both backends, compare complete native-replan artifacts with public lowering including optional claims/hash/counters; for the established ordinary h2 family compare every candidate with its own public lowered artifact. |
| invariants | The repair substitutes geometry only for nonempty contradictions. Existing empty-body claims and ordinary candidate trees must remain byte-equivalent. |
| ownership | Each comparison owns independent compiler/native immutable plans and borrows checked family handles. |
| failure | Any source/options/work/hash/geometry difference is a test failure. |
| cost | Several small public/native lowerings and full serialization comparisons; no broad source replay benchmark. |
| Design | [docs/physical_plans.md §Admission and routes](../../../../physical_plans.md), [docs/candidate_alternatives.md](../../../../candidate_alternatives.md) |

## B0025

[Lines 388–400](../../../../../tests/unit/constant_route_test.cpp#L388); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void run() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Compose the nonempty contradiction regression matrix and its compatibility/failure-boundary controls. |
| inputs / outputs | Run unary, three-atom, normalized rows and normalized EXISTS cases on reference/indexed backends; execute native/artifact and ranking/selection matrices, compatibility controls, unary/SQL native fault sweeps, policy replacement faults and owner-boundary checks. |
| invariants | The fixed fixture dimensions prevent accidental reduction to the historically passing empty-body-only route. A final success message is emitted only after every subcase returns. |
| ownership | The runner owns the fixed input array; case-local scopes release their native/test payloads. |
| failure | Any subcase exception propagates to main, which returns a failing process status. |
| cost | Aggregate test matrix and fault sweeps; the printed dimensions are coverage metadata, not measured throughput. |
| Design | [docs/physical_plans.md §Admission and routes](../../../../physical_plans.md), [docs/ranking.md §Exact score reconstruction](../../../../ranking.md), [docs/selection.md](../../../../selection.md) |

## B0026

[Lines 401–401](../../../../../tests/unit/constant_route_test.cpp#L401); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L401-L401:sha256:533f16bca7d58f44b3103b92e3485d22cfbb34bbad5ea3f3fa3b5a9dcb24ec89
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Close the recorded declaration scopes in constant_route_test.cpp: namespace (anonymous). |
| inputs / outputs | Preceding namespace, type or initializer declarations in; completed lexical boundary out. |
| invariants | Brace-opening context is recorded in root-scope-context-v1.json. These are declaration/initializer boundaries, not an independent update, validation or recovery operation. |
| ownership | Enclosing objects and borrowed fields keep their declared ownership. This punctuation creates no new owner. |
| failure | Malformed scope syntax is a compile error. Any initializer/constructor failure belongs to the enclosing object declaration. |
| cost | No separate loop, guard or engine call is introduced by the delimiter; enclosing initialization and object lifetime still have their actual costs. |
| Design | [tests/unit/constant_route_test.cpp](../../../../../tests/unit/constant_route_test.cpp), [docs/physical_plans.md](../../../../physical_plans.md), [docs/code_review.md](../../../../code_review.md) |

## B0027

[Lines 402–404](../../../../../tests/unit/constant_route_test.cpp#L402); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
int main() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Expose the regression suite as a normal CTest process result. |
| inputs / outputs | Invoke run and return zero; print the original std::exception message and return one on a test failure. |
| invariants | The single presentation catch exists only at the test executable boundary and does not change production diagnostics or resource behavior. |
| ownership | Automatic test owners unwind before the process reports failure. |
| failure | Unexpected non-std exceptions retain normal process failure semantics; expected per-case rejections are checked inside their case. |
| cost | One call and terminal message/status output. |
| Design | [docs/code_specs/error_handling.md](../../../error_handling.md) |
