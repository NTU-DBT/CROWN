# `src/io/candidates.cpp` — block usage map

[Source](../../../../../src/io/candidates.cpp) · [Source index](../../../README.md) · [Subsystem contracts](../../../subsystem_contracts.md) · [Reviewed primitives](../../../primitives.md)

Retain and enumerate checked minimum-height candidate alternatives under bounded content budgets.

Snapshot SHA-256: `39e865d75705ec4d7488100832a9c02f0e31f5ca824ac17e382fbe635df0dc81`. 154 lines partitioned into 19 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [io](../../../subsystem_contracts.md#io). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/ingestion.md](../../../../ingestion.md), [docs/query_identity.md](../../../../query_identity.md), [docs/schema_evolution.md](../../../../schema_evolution.md), [docs/cli.md](../../../../cli.md), [docs/query_memory.md](../../../../query_memory.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–9](../../../../../src/io/candidates.cpp#L1) | Imports dependencies; controls preprocessing; declares namespace scope; declares aliases. | returns #Value · [reviewed contract](#b0001) |
| [B0002 · 10–20](../../../../../src/io/candidates.cpp#L10) | Callable definition: const char* name(CandidatePhase value) | calls ENUM_CASE, Error · [reviewed contract](#b0002) |
| [B0003 · 21–34](../../../../../src/io/candidates.cpp#L21) | Callable definition: const char* name(CandidateStop value) | calls ENUM_CASE, Error · [reviewed contract](#b0003) |
| [B0004 · 35–42](../../../../../src/io/candidates.cpp#L35) | Callable definition: const char* name(CandidateSource value) | calls ENUM_CASE, Error · [reviewed contract](#b0004) |
| [B0005 · 43–50](../../../../../src/io/candidates.cpp#L43) | Callable definition: const char* name(ResidualOrigin value) | calls ENUM_CASE, Error · [reviewed contract](#b0005) |
| [B0006 · 51–51](../../../../../src/io/candidates.cpp#L51) | Member/declaration region. |  · [reviewed contract](#b0006) |
| [B0007 · 52–59](../../../../../src/io/candidates.cpp#L52) | Callable definition: const char* family(CandidateFamily value) | calls Error; returns @; @ · [reviewed contract](#b0007) |
| [B0008 · 60–67](../../../../../src/io/candidates.cpp#L60) | Callable definition: const char* exhaustion_scope(CandidateFamily value) | calls Error; returns @; @ · [reviewed contract](#b0008) |
| [B0009 · 68–77](../../../../../src/io/candidates.cpp#L68) | Callable definition: Json context(const CandidateContext& c) | calls Error; returns {{@ , @ }, {@ , c.arithmetic}, · [reviewed contract](#b0009) |
| [B0010 · 78–79](../../../../../src/io/candidates.cpp#L78) | Explanatory comments or spacing. | source comment (unverified): // Each report owns another catalog/query/proof export. Rendering does not · [reviewed contract](#b0010) |
| [B0011 · 80–89](../../../../../src/io/candidates.cpp#L80) | Callable definition: Json common(const char* artifact, const VerifiedOptimum& proof, const CandidateContext& c, CandidateFamily f) | calls binding, detail::query_binding, catalog, query; returns {{@ , 1}, {@ , artifact}, {@ , @ },; source comment (unverified): // Each report owns another catalog/query/proof export. Rendering does not · [reviewed contract](#b0011) |
| [B0012 · 90–94](../../../../../src/io/candidates.cpp#L90) | Callable definition: Json counters(const WorkCounters& v) | calls ; returns {{@ , v.attempted}, {@ , v.committed_transitions}, · [reviewed contract](#b0012) |
| [B0013 · 95–95](../../../../../src/io/candidates.cpp#L95) | Callable definition: template&lt;class T&gt; Json optional_number(const std::optional&lt;T&gt;& v) | calls Json; returns v ? Json(*v) : Json(nullptr) · [reviewed contract](#b0013) |
| [B0014 · 96–101](../../../../../src/io/candidates.cpp#L96) | Callable definition: Json limits(const CandidateLimits& v) | calls optional_number, Json, count; returns {{@ , {{@ , optional_number(v.enumeration.work)}, · [reviewed contract](#b0014) |
| [B0015 · 102–102](../../../../../src/io/candidates.cpp#L102) | Closes surrounding scope/type. |  · [reviewed contract](#b0015) |
| [B0016 · 103–120](../../../../../src/io/candidates.cpp#L103) | Callable definition: Json write_minimum_height_candidate(const planner::MinimumHeightCandidate& value) | calls valid, Error, original_proof, height; returns result · [reviewed contract](#b0016) |
| [B0017 · 121–138](../../../../../src/io/candidates.cpp#L121) | Callable definition: Json write_candidate_progress(const planner::CandidateProvider& owner) | calls progress, common, original_proof, context; returns result · [reviewed contract](#b0017) |
| [B0018 · 139–153](../../../../../src/io/candidates.cpp#L139) | Callable definition: Json write_candidate_snapshot(const planner::CandidateSnapshot& value) | calls valid, Error, common, original_proof; returns result; growth push_back; 1 loop sites · [reviewed contract](#b0018) |
| [B0019 · 154–154](../../../../../src/io/candidates.cpp#L154) | Closes surrounding scope/type. | source comment (unverified): // namespace crown::io · [reviewed contract](#b0019) |

## B0001

[Lines 1–9](../../../../../src/io/candidates.cpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L1-L9:sha256:cfb874c861bf8ed501bab29b6b8f281b3ce6778b076452b9d0333f47e999c537
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Imports candidate/residual reporting dependencies, opens crown::io and its private helper namespace, aliases planner types, and defines a local enum-to-name macro used only by the following switch helpers. |
| inputs / outputs | No runtime inputs/outputs are declared by the import/scope lines themselves. |
| invariants | The listed headers and namespace membership determine compile-time name availability; any API behavior belongs to the declarations/definitions that follow. |
| ownership | No object ownership is created by the imports or namespace tokens. |
| failure | No runtime failure path. Missing/incompatible dependencies or a violated compile-time constraint fail translation/linking. |
| cost | Compile/preprocessor work only; no new per-operation runtime overhead. |
| Design | [src/io/candidates.cpp](../../../../../src/io/candidates.cpp), [docs/code_specs/files/src/io/candidates.cpp.md](candidates.cpp.md), [docs/residual_candidates.md](../../../../residual_candidates.md), [docs/planner_proofs.md](../../../../planner_proofs.md) |

## B0002

[Lines 10–20](../../../../../src/io/candidates.cpp#L10); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
const char* name(CandidatePhase value) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Name the supported CandidatePhase diagnostic tag exactly. |
| inputs / outputs | Switches the valid producer enum to static source-spelled report labels; an unknown cast rejects. |
| invariants | Labels describe provider/provenance state, not proof completeness, runtime ownership or a command to advance enumeration. |
| ownership | Returned const char* points to static literal bytes; the caller JSON owns any later copy. |
| failure | Unknown tag throws public invalid_candidate_report; no silent unknown/default label or recovery. |
| cost | A bounded enum switch with no population scan or success allocation; error-message construction can allocate. |
| Design | [src/io/candidates.cpp](../../../../../src/io/candidates.cpp), [include/crown/planner/candidates.hpp](../../../../../include/crown/planner/candidates.hpp), [src/planner/candidates.cpp](../../../../../src/planner/candidates.cpp), [src/io/query_binding.hpp](../../../../../src/io/query_binding.hpp), [src/io/search.cpp](../../../../../src/io/search.cpp), [src/io/document.cpp](../../../../../src/io/document.cpp), [tests/unit/candidates_io_test.cpp](../../../../../tests/unit/candidates_io_test.cpp), [docs/candidate_alternatives.md](../../../../candidate_alternatives.md), [docs/code_review.md](../../../../code_review.md) |

## B0003

[Lines 21–34](../../../../../src/io/candidates.cpp#L21); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
const char* name(CandidateStop value) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Name the supported CandidateStop diagnostic tag exactly. |
| inputs / outputs | Switches the valid producer enum to static source-spelled report labels; an unknown cast rejects. |
| invariants | Labels describe provider/provenance state, not proof completeness, runtime ownership or a command to advance enumeration. |
| ownership | Returned const char* points to static literal bytes; the caller JSON owns any later copy. |
| failure | Unknown tag throws public invalid_candidate_report; no silent unknown/default label or recovery. |
| cost | A bounded enum switch with no population scan or success allocation; error-message construction can allocate. |
| Design | [src/io/candidates.cpp](../../../../../src/io/candidates.cpp), [include/crown/planner/candidates.hpp](../../../../../include/crown/planner/candidates.hpp), [src/planner/candidates.cpp](../../../../../src/planner/candidates.cpp), [src/io/query_binding.hpp](../../../../../src/io/query_binding.hpp), [src/io/search.cpp](../../../../../src/io/search.cpp), [src/io/document.cpp](../../../../../src/io/document.cpp), [tests/unit/candidates_io_test.cpp](../../../../../tests/unit/candidates_io_test.cpp), [docs/candidate_alternatives.md](../../../../candidate_alternatives.md), [docs/code_review.md](../../../../code_review.md) |

## B0004

[Lines 35–42](../../../../../src/io/candidates.cpp#L35); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
const char* name(CandidateSource value) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Name the supported CandidateSource diagnostic tag exactly. |
| inputs / outputs | Switches the valid producer enum to static source-spelled report labels; an unknown cast rejects. |
| invariants | Labels describe provider/provenance state, not proof completeness, runtime ownership or a command to advance enumeration. |
| ownership | Returned const char* points to static literal bytes; the caller JSON owns any later copy. |
| failure | Unknown tag throws public invalid_candidate_report; no silent unknown/default label or recovery. |
| cost | A bounded enum switch with no population scan or success allocation; error-message construction can allocate. |
| Design | [src/io/candidates.cpp](../../../../../src/io/candidates.cpp), [include/crown/planner/candidates.hpp](../../../../../include/crown/planner/candidates.hpp), [src/planner/candidates.cpp](../../../../../src/planner/candidates.cpp), [src/io/query_binding.hpp](../../../../../src/io/query_binding.hpp), [src/io/search.cpp](../../../../../src/io/search.cpp), [src/io/document.cpp](../../../../../src/io/document.cpp), [tests/unit/candidates_io_test.cpp](../../../../../tests/unit/candidates_io_test.cpp), [docs/candidate_alternatives.md](../../../../candidate_alternatives.md), [docs/code_review.md](../../../../code_review.md) |

## B0005

[Lines 43–50](../../../../../src/io/candidates.cpp#L43); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
const char* name(ResidualOrigin value) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Name the supported ResidualOrigin diagnostic tag exactly. |
| inputs / outputs | Switches the valid producer enum to static source-spelled report labels; an unknown cast rejects. |
| invariants | Labels describe provider/provenance state, not proof completeness, runtime ownership or a command to advance enumeration. |
| ownership | Returned const char* points to static literal bytes; the caller JSON owns any later copy. |
| failure | Unknown tag throws public invalid_candidate_report; no silent unknown/default label or recovery. |
| cost | A bounded enum switch with no population scan or success allocation; error-message construction can allocate. |
| Design | [src/io/candidates.cpp](../../../../../src/io/candidates.cpp), [include/crown/planner/candidates.hpp](../../../../../include/crown/planner/candidates.hpp), [src/planner/candidates.cpp](../../../../../src/planner/candidates.cpp), [src/io/query_binding.hpp](../../../../../src/io/query_binding.hpp), [src/io/search.cpp](../../../../../src/io/search.cpp), [src/io/document.cpp](../../../../../src/io/document.cpp), [tests/unit/candidates_io_test.cpp](../../../../../tests/unit/candidates_io_test.cpp), [docs/candidate_alternatives.md](../../../../candidate_alternatives.md), [docs/code_review.md](../../../../code_review.md) |

## B0006

[Lines 51–51](../../../../../src/io/candidates.cpp#L51); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L51-L51:sha256:55109587e92becba926870d0ce46d4d4f28742dafda44e4446d419222a4477d5
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Ends the local preprocessor definition of ENUM_CASE; subsequent translation-unit code cannot use that macro expansion. |
| inputs / outputs | No runtime values are exchanged; a preprocessor macro is removed for later source text in this translation unit. |
| invariants | The macro expansion is available only before this directive; later code must use ordinary declarations or a fresh definition. |
| ownership | No runtime state. |
| failure | No runtime error. Preprocessing/compilation can fail if later tokens depended on the removed macro. |
| cost | Preprocessing only. |
| Design | [src/io/candidates.cpp](../../../../../src/io/candidates.cpp), [docs/code_specs/files/src/io/candidates.cpp.md](candidates.cpp.md), [docs/residual_candidates.md](../../../../residual_candidates.md), [docs/planner_proofs.md](../../../../planner_proofs.md) |

## B0007

[Lines 52–59](../../../../../src/io/candidates.cpp#L52); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
const char* family(CandidateFamily value) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Render supported candidate-family versions and reject unknown values. |
| inputs / outputs | Original family maps to exact-seed/residual-seed/normal-form-v1; supplied batch maps to finite-proposals-v1. |
| invariants | The reported family limits only its own provider route, never an upstream algorithm or all possible trees. |
| ownership | Static literal result retains no provider/proof owner. |
| failure | Unknown family throws invalid_candidate_report before a report is returned. |
| cost | Fixed enum check and literal pointer; no enumeration or successful allocation. |
| Design | [src/io/candidates.cpp](../../../../../src/io/candidates.cpp), [include/crown/planner/candidates.hpp](../../../../../include/crown/planner/candidates.hpp), [src/planner/candidates.cpp](../../../../../src/planner/candidates.cpp), [src/io/query_binding.hpp](../../../../../src/io/query_binding.hpp), [src/io/search.cpp](../../../../../src/io/search.cpp), [src/io/document.cpp](../../../../../src/io/document.cpp), [tests/unit/candidates_io_test.cpp](../../../../../tests/unit/candidates_io_test.cpp), [docs/candidate_alternatives.md](../../../../candidate_alternatives.md), [docs/code_review.md](../../../../code_review.md), [docs/meta_decompositions.md](../../../../meta_decompositions.md) |

## B0008

[Lines 60–67](../../../../../src/io/candidates.cpp#L60); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L60-L67:sha256:1729e1907106edbe7f2515852981fbf716c59fa42a34e43bf2f6314ae25f5449
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Name the exact exhaustion scope of the actual typed candidate family. |
| inputs / outputs | Supported family enum in; original-route or supplied-finite-batch static label out. |
| invariants | No supplied-batch exhaustion label implies upstream or all-tree completeness. |
| ownership | Static literals; no retained payload. |
| failure | Unknown enum throws invalid_candidate_report. |
| cost | Fixed switch and literal borrow; error construction may allocate. |
| Design | [docs/candidate_alternatives.md](../../../../candidate_alternatives.md), [docs/meta_decompositions.md](../../../../meta_decompositions.md), [Refactor.md](../../../../../Refactor.md) |

## B0009

[Lines 68–77](../../../../../src/io/candidates.cpp#L68); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Json context(const CandidateContext& c) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Validate and serialize the supported candidate policy context. |
| inputs / outputs | Requires the fixed update profile and arithmetic/planner/optimization/cost/canonicalization versions, then creates their JSON labels. |
| invariants | Context labels bind this report family; they do not select a new optimizer or replace typed VerifiedOptimum authority. |
| ownership | The returned ordinary owning JSON tree copies its exposed strings/arrays/objects; it retains no live runtime, grant or typed proof capability. |
| failure | Unsupported policy/context or ordinary DOM allocation rejects; no default policy substitution. |
| cost | A fixed number of string/enum comparisons and copied labels, with actual string lengths; no candidate search. |
| Design | [src/io/candidates.cpp](../../../../../src/io/candidates.cpp), [include/crown/planner/candidates.hpp](../../../../../include/crown/planner/candidates.hpp), [src/planner/candidates.cpp](../../../../../src/planner/candidates.cpp), [src/io/query_binding.hpp](../../../../../src/io/query_binding.hpp), [src/io/search.cpp](../../../../../src/io/search.cpp), [src/io/document.cpp](../../../../../src/io/document.cpp), [tests/unit/candidates_io_test.cpp](../../../../../tests/unit/candidates_io_test.cpp), [docs/candidate_alternatives.md](../../../../candidate_alternatives.md), [docs/code_review.md](../../../../code_review.md) |

## B0010

[Lines 78–79](../../../../../src/io/candidates.cpp#L78); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L78-L79:sha256:0077d7147391b1be50e79cb18c3251cf6778b29f6e874a21b310dd0d258a1b27
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Design note for adjacent code: Each report owns another catalog/query/proof export. Rendering does not advance a provider or turn the returned editable JSON into a checked token. This is caller guidance recorded as prose, not an executable result. |
| inputs / outputs | No runtime interface is implemented by these comment-only lines. They sit at src/io/candidates.cpp lines 64-69; the surrounding declaration/body defines its own inputs and outputs. |
| invariants | The words record the intended use boundary only. They do not add a guard, proof, capability, transaction, durability guarantee, or account charge; verify behavior in the referenced implementation. |
| ownership | Comment text owns no data. Object lifetimes, borrows, and account attribution remain those of the adjacent source objects and their constructors. |
| failure | No failure path is implemented here. Any mentioned failure or recovery rule belongs to the adjacent operation and its existing error carrier. |
| cost | No runtime work is performed by these lines; any cost/bound in the note is not certified by this comment-only card. |
| Design | [src/io/candidates.cpp](../../../../../src/io/candidates.cpp), [docs/code_specs/files/src/io/candidates.cpp.md](candidates.cpp.md), [docs/residual_candidates.md](../../../../residual_candidates.md), [docs/planner_proofs.md](../../../../planner_proofs.md) |

## B0011

[Lines 80–89](../../../../../src/io/candidates.cpp#L80); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Json common(const char* artifact, const VerifiedOptimum& proof,
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Attach the original checked optimum and exact query binding to each report. |
| inputs / outputs | Uses VerifiedOptimum.binding(), serialized full query/catalog binding, versioned family/context and write_verified_optimum certificate under structural_height_only scope. |
| invariants | The typed checked proof is authority before rendering. The output JSON is editable evidence, not a checked token; this helper does not rerun search/replay or advance a provider. |
| ownership | The returned ordinary owning JSON tree copies its exposed strings/arrays/objects; it retains no live runtime, grant or typed proof capability. |
| failure | Moved/invalid proof access, binding/context/family serialization or allocation failures propagate; no manufactured proof fallback. |
| cost | Full query-binding/document and certificate serialization/copies plus context DOM. Each caller/report invocation pays this cost again; this is not a fixed-size status envelope. |
| Design | [src/io/candidates.cpp](../../../../../src/io/candidates.cpp), [include/crown/planner/candidates.hpp](../../../../../include/crown/planner/candidates.hpp), [src/planner/candidates.cpp](../../../../../src/planner/candidates.cpp), [src/io/query_binding.hpp](../../../../../src/io/query_binding.hpp), [src/io/search.cpp](../../../../../src/io/search.cpp), [src/io/document.cpp](../../../../../src/io/document.cpp), [tests/unit/candidates_io_test.cpp](../../../../../tests/unit/candidates_io_test.cpp), [docs/candidate_alternatives.md](../../../../candidate_alternatives.md), [docs/code_review.md](../../../../code_review.md) |

## B0012

[Lines 90–94](../../../../../src/io/candidates.cpp#L90); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Json counters(const WorkCounters& v) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Render stored continuation work counters as diagnostic numbers. |
| inputs / outputs | Copies attempted/committed/allocation-failure/time/current-depth/peak-depth fields into ordinary JSON. |
| invariants | Counters are observed facts from the supplied producer; serialization does not update them or establish completeness. |
| ownership | The returned ordinary owning JSON tree copies its exposed strings/arrays/objects; it retains no live runtime, grant or typed proof capability. |
| failure | Shape/type/version, parser/serialization or ordinary allocation failures propagate; this boundary adds no catch, fallback or retry. |
| cost | Fixed number of integer fields and small DOM allocations, not a history scan. |
| Design | [src/io/candidates.cpp](../../../../../src/io/candidates.cpp), [include/crown/planner/candidates.hpp](../../../../../include/crown/planner/candidates.hpp), [src/planner/candidates.cpp](../../../../../src/planner/candidates.cpp), [src/io/query_binding.hpp](../../../../../src/io/query_binding.hpp), [src/io/search.cpp](../../../../../src/io/search.cpp), [src/io/document.cpp](../../../../../src/io/document.cpp), [tests/unit/candidates_io_test.cpp](../../../../../tests/unit/candidates_io_test.cpp), [docs/candidate_alternatives.md](../../../../candidate_alternatives.md), [docs/code_review.md](../../../../code_review.md) |

## B0013

[Lines 95–95](../../../../../src/io/candidates.cpp#L95); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
template<class T> Json optional_number(const std::optional<T>& v) { return v ? Json(*v) : Json(nullptr); }
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Preserve optional candidate limit/count presence. |
| inputs / outputs | Template emits the stored numeric value or null. |
| invariants | A missing bound differs from zero; the helper does not validate, consume or refill a grant. |
| ownership | JSON scalar result owns no provider/proof. |
| failure | Shape/type/version, parser/serialization or ordinary allocation failures propagate; this boundary adds no catch, fallback or retry. |
| cost | Fixed scalar/null construction. |
| Design | [src/io/candidates.cpp](../../../../../src/io/candidates.cpp), [include/crown/planner/candidates.hpp](../../../../../include/crown/planner/candidates.hpp), [src/planner/candidates.cpp](../../../../../src/planner/candidates.cpp), [src/io/query_binding.hpp](../../../../../src/io/query_binding.hpp), [src/io/search.cpp](../../../../../src/io/search.cpp), [src/io/document.cpp](../../../../../src/io/document.cpp), [tests/unit/candidates_io_test.cpp](../../../../../tests/unit/candidates_io_test.cpp), [docs/candidate_alternatives.md](../../../../candidate_alternatives.md), [docs/code_review.md](../../../../code_review.md) |

## B0014

[Lines 96–101](../../../../../src/io/candidates.cpp#L96); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Json limits(const CandidateLimits& v) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Describe provider operational ceilings without admitting work. |
| inputs / outputs | Exports optional enumeration work/time, logical depth, records, cells and retained candidate limits. |
| invariants | These values describe provider admission, not an output DOM byte limit or total serializer CPU/memory cap. |
| ownership | The returned ordinary owning JSON tree copies its exposed strings/arrays/objects; it retains no live runtime, grant or typed proof capability. |
| failure | Shape/type/version, parser/serialization or ordinary allocation failures propagate; this boundary adds no catch, fallback or retry. |
| cost | Fixed number of optional scalar conversions/DOM fields; no provider advance, trace or candidate traversal. |
| Design | [src/io/candidates.cpp](../../../../../src/io/candidates.cpp), [include/crown/planner/candidates.hpp](../../../../../include/crown/planner/candidates.hpp), [src/planner/candidates.cpp](../../../../../src/planner/candidates.cpp), [src/io/query_binding.hpp](../../../../../src/io/query_binding.hpp), [src/io/search.cpp](../../../../../src/io/search.cpp), [src/io/document.cpp](../../../../../src/io/document.cpp), [tests/unit/candidates_io_test.cpp](../../../../../tests/unit/candidates_io_test.cpp), [docs/candidate_alternatives.md](../../../../candidate_alternatives.md), [docs/code_review.md](../../../../code_review.md) |

## B0015

[Lines 102–102](../../../../../src/io/candidates.cpp#L102); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L102-L102:sha256:412ca345ccf75bf9c0806bce695be8de808b79984251a7a54d202cf6101dd451
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Closes the enclosing implementation scope at this source boundary; this is a lexical delimiter, not an operation. |
| inputs / outputs | No runtime input or output. Declarations following the span leave the preceding C++ scope. |
| invariants | The delimiter ends the preceding scope's visibility/linkage region; it adds no validation, publication, ownership transfer, or runtime authority. |
| ownership | The delimiter adds no owner. If it ends a function/block with live automatic objects, their normal destructors release those objects; namespace and type-definition closes change no existing object's lifetime. |
| failure | No explicit failure translation or catch is added. If a function/block exit destroys automatic objects, exception behavior follows those destructors; namespace/type closes have no runtime failure path. |
| cost | The delimiter adds no algorithmic work. A function/block exit can run existing automatic-object destructors and cleanup; namespace/type closes have no runtime cost. |
| Design | [src/io/candidates.cpp](../../../../../src/io/candidates.cpp), [docs/code_specs/files/src/io/candidates.cpp.md](candidates.cpp.md), [docs/residual_candidates.md](../../../../residual_candidates.md), [docs/planner_proofs.md](../../../../planner_proofs.md) |

## B0016

[Lines 103–120](../../../../../src/io/candidates.cpp#L103); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Json write_minimum_height_candidate(const planner::MinimumHeightCandidate& value) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Export a checked-height candidate with its distinct original minimum proof. |
| inputs / outputs | Requires valid candidate, matching height and full query/catalog binding to its supplied VerifiedOptimum, then exports checked-upper tree, structural key, source/sequence and optional residual provenance. |
| invariants | Candidate upper witness need not be the original proof tree. Export says checked_upper_matches_supplied_original_minimum and keeps upper-only tree separate from original lower proof. JSON cannot replace typed verification. |
| ownership | The returned ordinary owning JSON tree copies its exposed strings/arrays/objects; it retains no live runtime, grant or typed proof capability. |
| failure | Moved candidate, binding/height/context/provenance mismatch or serialization/allocation failure rejects before a complete report escapes. |
| cost | Repeated full candidate/proof query binding construction/comparison, original certificate export, tree addressability/schema serialization and optional trace/key copies. No search or proof replay occurs in this writer. |
| Design | [src/io/candidates.cpp](../../../../../src/io/candidates.cpp), [include/crown/planner/candidates.hpp](../../../../../include/crown/planner/candidates.hpp), [src/planner/candidates.cpp](../../../../../src/planner/candidates.cpp), [src/io/query_binding.hpp](../../../../../src/io/query_binding.hpp), [src/io/search.cpp](../../../../../src/io/search.cpp), [src/io/document.cpp](../../../../../src/io/document.cpp), [tests/unit/candidates_io_test.cpp](../../../../../tests/unit/candidates_io_test.cpp), [docs/candidate_alternatives.md](../../../../candidate_alternatives.md), [docs/code_review.md](../../../../code_review.md) |

## B0017

[Lines 121–138](../../../../../src/io/candidates.cpp#L121); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Json write_candidate_progress(const planner::CandidateProvider& owner) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Export current candidate enumeration diagnostics without advancing the owner. |
| inputs / outputs | Snapshots progress/counters/statistics/records/cells/limits and attaches original checked proof, exact context, current phase and stop reason. |
| invariants | family_exhausted and exhaustion_scope describe the actual typed provider family only. A partial prefix or consumed supplied batch creates no global completeness proof. |
| ownership | The returned ordinary owning JSON tree copies its exposed strings/arrays/objects; it retains no live runtime, grant or typed proof capability. |
| failure | Invalid/moved owner access, unsupported context/tag or ordinary serialization/allocation failures propagate; no progress retry or mutation. |
| cost | Fixed progress values plus repeated full query/proof serialization and owning JSON. There is no final output-byte/item cap in this API. |
| Design | [src/io/candidates.cpp](../../../../../src/io/candidates.cpp), [include/crown/planner/candidates.hpp](../../../../../include/crown/planner/candidates.hpp), [src/planner/candidates.cpp](../../../../../src/planner/candidates.cpp), [src/io/query_binding.hpp](../../../../../src/io/query_binding.hpp), [src/io/search.cpp](../../../../../src/io/search.cpp), [src/io/document.cpp](../../../../../src/io/document.cpp), [tests/unit/candidates_io_test.cpp](../../../../../tests/unit/candidates_io_test.cpp), [docs/candidate_alternatives.md](../../../../candidate_alternatives.md), [docs/code_review.md](../../../../code_review.md), [docs/meta_decompositions.md](../../../../meta_decompositions.md) |

## B0018

[Lines 139–153](../../../../../src/io/candidates.cpp#L139); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Json write_candidate_snapshot(const planner::CandidateSnapshot& value) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Export an immutable candidate prefix with explicit missing-record rejection. |
| inputs / outputs | Requires valid snapshot, exports original proof/context/count/scope, then serializes each candidate(i), rejecting any absent prefix entry. |
| invariants | Snapshot describes its admitted immutable prefix; an editable JSON count/family_exhausted flag has no provider or proof authority. Prefix members retain their own matching family/source and separately serialized unchanged original proof. |
| ownership | The returned ordinary owning JSON tree copies its exposed strings/arrays/objects; it retains no live runtime, grant or typed proof capability. |
| failure | Moved snapshot, missing candidate, nested candidate mismatch or allocation failure discards partial local DOM; source snapshot is unchanged. |
| cost | Visits every retained candidate and repeats that candidate's full query/proof/tree/trace export. Output can grow with prefix times repeated proof/catalog size, not only unique tree cells. |
| Design | [src/io/candidates.cpp](../../../../../src/io/candidates.cpp), [include/crown/planner/candidates.hpp](../../../../../include/crown/planner/candidates.hpp), [src/planner/candidates.cpp](../../../../../src/planner/candidates.cpp), [src/io/query_binding.hpp](../../../../../src/io/query_binding.hpp), [src/io/search.cpp](../../../../../src/io/search.cpp), [src/io/document.cpp](../../../../../src/io/document.cpp), [tests/unit/candidates_io_test.cpp](../../../../../tests/unit/candidates_io_test.cpp), [docs/candidate_alternatives.md](../../../../candidate_alternatives.md), [docs/code_review.md](../../../../code_review.md), [docs/meta_decompositions.md](../../../../meta_decompositions.md) |

## B0019

[Lines 154–154](../../../../../src/io/candidates.cpp#L154); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L154-L154:sha256:39c2bd587239794e92def2b2ebc5cce8f0acd397d817bceec761a8f61bea3e66
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Closes the namespace crown::io at this source boundary; this is a lexical delimiter, not an operation. |
| inputs / outputs | No runtime input or output. Declarations following the span leave the preceding C++ scope. |
| invariants | The delimiter ends the preceding scope's visibility/linkage region; it adds no validation, publication, ownership transfer, or runtime authority. |
| ownership | The delimiter adds no owner. If it ends a function/block with live automatic objects, their normal destructors release those objects; namespace and type-definition closes change no existing object's lifetime. |
| failure | No explicit failure translation or catch is added. If a function/block exit destroys automatic objects, exception behavior follows those destructors; namespace/type closes have no runtime failure path. |
| cost | The delimiter adds no algorithmic work. A function/block exit can run existing automatic-object destructors and cleanup; namespace/type closes have no runtime cost. |
| Design | [src/io/candidates.cpp](../../../../../src/io/candidates.cpp), [docs/code_specs/files/src/io/candidates.cpp.md](candidates.cpp.md), [docs/residual_candidates.md](../../../../residual_candidates.md), [docs/planner_proofs.md](../../../../planner_proofs.md) |
