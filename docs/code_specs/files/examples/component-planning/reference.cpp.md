# `examples/component-planning/reference.cpp` — block usage map

[Source](../../../../../examples/component-planning/reference.cpp) · [Source index](../../../README.md) · [Subsystem contracts](../../../subsystem_contracts.md) · [Reviewed primitives](../../../primitives.md)

Demonstrate a concrete public workflow and executable invocation using installed/native CROWN interfaces.

Snapshot SHA-256: `116e1ec57ee73a97390146ba6ae9d7a87c80191a4b616e379a5e04dca49a8108`. 280 lines partitioned into 18 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [examples](../../../subsystem_contracts.md#examples). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/cli.md](../../../../cli.md), [docs/native_build.md](../../../../native_build.md), [docs/measurement.md](../../../../measurement.md), [docs/ranking_evaluation.md](../../../../ranking_evaluation.md), [docs/reoptimization.md](../../../../reoptimization.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–31](../../../../../examples/component-planning/reference.cpp#L1) | Imports dependencies; declares namespace scope; declares aliases; declares values/defaults or compile-time conditions. |  · [reviewed contract](#b0001) |
| [B0002 · 32–32](../../../../../examples/component-planning/reference.cpp#L32) | Callable definition: void require(bool value, const char* message) | calls Error; guard void require(bool value, const char* message) { if (!value) throw Error("search_experiment", messag… · [reviewed contract](#b0002) |
| [B0003 · 33–36](../../../../../examples/component-planning/reference.cpp#L33) | Callable definition: U64 integer(const Json& value, U64 low, U64 high) | calls require, is_number_integer, is_number_unsigned; guard require(value.is_number_integer() && (value.is_number_unsigned() \|\| value.get&lt;std::int64_t&gt;() &gt;= 0)…; returns result · [reviewed contract](#b0003) |
| [B0004 · 37–45](../../../../../examples/component-planning/reference.cpp#L37) | Callable definition: std::string read(const char* path) | calls stream, require, bool, gcount; guard std::ifstream stream(path, std::ios::binary); require(bool(stream), "cannot read search input");; returns text; 1 loop sites · [reviewed contract](#b0004) |
| [B0005 · 46–50](../../../../../examples/component-planning/reference.cpp#L46) | Callable definition: Json time_value(bool measure, Clock::time_point begin, Clock::time_point end) | calls count, require; guard require(value &gt;= 0, "steady clock regressed"); return static_cast&lt;U64&gt;(value);; returns nullptr; static_cast&lt;U64&gt;(value) · [reviewed contract](#b0005) |
| [B0006 · 51–65](../../../../../examples/component-planning/reference.cpp#L51) | Type/record definition: struct Request | returns limits; limits · [reviewed contract](#b0006) |
| [B0007 · 66–83](../../../../../examples/component-planning/reference.cpp#L66) | Callable definition: Request request(const Json& value, std::size_t tables) | calls require, is_object, size, items; guard require(value.is_object() && value.size()==fields.size(), "closed search request field mismatch");; returns result; growth push_back; 2 loop sites · [reviewed contract](#b0007) |
| [B0008 · 84–87](../../../../../examples/component-planning/reference.cpp#L84) | Callable definition: planner::SearchOptions exact_options(U64 work, const Request& ask) | calls ; returns options · [reviewed contract](#b0008) |
| [B0009 · 88–93](../../../../../examples/component-planning/reference.cpp#L88) | Callable definition: void complete(planner::ExactSearch& search) | calls advance; 1 loop sites · [reviewed contract](#b0009) |
| [B0010 · 94–100](../../../../../examples/component-planning/reference.cpp#L94) | Callable definition: void drain(planner::CandidateProvider& provider) | calls advance; 1 loop sites · [reviewed contract](#b0010) |
| [B0011 · 101–108](../../../../../examples/component-planning/reference.cpp#L101) | Callable definition: Json shape(const FreeConnexTree& tree) | calls std::max, size; returns {{@ ,tree.nodes.size()},{@ ,generalized},{@ ,fanout},{@ ,normalized}}; 1 loop sites · [reviewed contract](#b0011) |
| [B0012 · 109–119](../../../../../examples/component-planning/reference.cpp#L109) | Callable definition: Json meta_report(const meta::MetaCandidateReport& p) | calls std::string; returns {{@ ,static_cast&lt;unsigned&gt;(p.construction_stop)}, · [reviewed contract](#b0012) |
| [B0013 · 120–122](../../../../../examples/component-planning/reference.cpp#L120) | Explanatory comments or spacing. | source comment (unverified): // C02 consumes an actual owner census. The declared repetitions cause real · [reviewed contract](#b0013) |
| [B0014 · 123–167](../../../../../examples/component-planning/reference.cpp#L123) | Callable definition: Json scoring(const planner::CandidateSnapshot& snapshot, const Request& ask) | calls candidate_count, candidate, catalog, empty; returns {{@ ,@ }}; column.type!=ScalarType::int64 \|\| column.nullable; growth insert, push_back; 6 loop sites; source comment (unverified): // C02 consumes an actual owner census. The declared repetitions cause real · [reviewed contract](#b0014) |
| [B0015 · 168–168](../../../../../examples/component-planning/reference.cpp#L168) | Explanatory comments or spacing. |  |
| [B0016 · 169–275](../../../../../examples/component-planning/reference.cpp#L169) | Callable definition: int run(int argc, char** argv) | calls require, Clock::now, read, io::read_json; guard require(argc==3,"usage: crown_search_components QUERY.cq.json REQUEST.json");; returns rows.empty(); std::cout?0:1; growth emplace, insert, push_back; 5 loop sites · [reviewed contract](#b0016) |
| [B0017 · 276–276](../../../../../examples/component-planning/reference.cpp#L276) | Closes surrounding scope/type. | source comment (unverified): // namespace · [reviewed contract](#b0017) |
| [B0018 · 277–280](../../../../../examples/component-planning/reference.cpp#L277) | Callable definition: int main(int argc, char** argv) | calls run, what; returns run(argc,argv); 1 · [reviewed contract](#b0018) |

## B0001

[Lines 1–31](../../../../../examples/component-planning/reference.cpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L1-L31:sha256:58f1f8f5d7545fcf18062a0c861f840f812ad3b85999a73a069a520405ebd6c8
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Declare a diagnostic executable using real IO, P06/residual/meta, independent test references and native C02 capture. |
| inputs / outputs | Imports public production APIs and two existing test-reference headers; declares local JSON, uint64, steady-clock and namespace aliases. |
| invariants | Reference routines stay diagnostic-only. Existing CLI tree-oracle is not used as the literal comparator; no runtime algorithm or dispatch hook is added. |
| ownership | Types and namespace aliases have translation-unit scope. Per-query search/runtime objects are created and destroyed by later calls. |
| failure | Missing public/test declarations fail compilation; there is no source fallback or replacement reference implementation. |
| cost | Compile/link dependencies only; importing declarations performs no query work or per-update instrumentation. |
| Design | [Refactor.md §14.1–14.4](../../../../../Refactor.md), [docs/measurement.md](../../../../measurement.md), [docs/planner_proofs.md](../../../../planner_proofs.md), [docs/residual_candidates.md](../../../../residual_candidates.md), [docs/meta_candidate_adapter.md](../../../../meta_candidate_adapter.md), [docs/ranking.md](../../../../ranking.md), [tests/reference/tree_oracle.cpp](../../../../../tests/reference/tree_oracle.cpp), [tests/reference/candidate_set.cpp](../../../../../tests/reference/candidate_set.cpp), [exact paper reference](https://arxiv.org/pdf/2301.04003v2#page=3), [exact paper reference](https://arxiv.org/html/2603.14754v1), [exact paper reference](https://arxiv.org/html/2603.15465v2) |

## B0002

[Lines 32–32](../../../../../examples/component-planning/reference.cpp#L32); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L32-L32:sha256:bc8d88e6956a633f3d27d869a65595c604b06b8c41e819087ab41dde35953ebb
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Reject a violated diagnostic input or output condition with the repository error type. |
| inputs / outputs | A Boolean and fixed message either return normally or throw search_experiment Error. |
| invariants | This helper never converts an unproved tree, malformed request or unavailable score into a valid result. |
| ownership | Borrows the message during Error construction; it creates no persistent query owner. |
| failure | False throws to the one outer CLI handler; no retry or catch-and-continue loop. |
| cost | One branch; error allocation occurs only on a rejecting cold path. |
| Design | [Refactor.md §14.1–14.4](../../../../../Refactor.md), [docs/measurement.md](../../../../measurement.md), [docs/planner_proofs.md](../../../../planner_proofs.md), [docs/residual_candidates.md](../../../../residual_candidates.md), [docs/meta_candidate_adapter.md](../../../../meta_candidate_adapter.md), [docs/ranking.md](../../../../ranking.md), [tests/reference/tree_oracle.cpp](../../../../../tests/reference/tree_oracle.cpp), [tests/reference/candidate_set.cpp](../../../../../tests/reference/candidate_set.cpp), [exact paper reference](https://arxiv.org/pdf/2301.04003v2#page=3), [exact paper reference](https://arxiv.org/html/2603.14754v1), [exact paper reference](https://arxiv.org/html/2603.15465v2) |

## B0003

[Lines 33–36](../../../../../examples/component-planning/reference.cpp#L33); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L33-L36:sha256:45c63301fba0d7fc1ceb8d202e4e072db2038f0bc4a5a1b8ac6e83f7a9f1a7cf
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Decode finite unsigned grants while excluding JSON Boolean, negative, floating and out-of-range values. |
| inputs / outputs | A JSON value plus inclusive low/high bounds produce one uint64 value. |
| invariants | is_number_integer excludes bool; signed values must be nonnegative before conversion; all declared grants are checked before narrowing. |
| ownership | Borrows JSON and returns a scalar; no retained source or account ownership. |
| failure | Wrong JSON category or grant range rejects the request through require. |
| cost | Constant-size scalar checks and conversion, outside native algorithms. |
| Design | [Refactor.md §14.1–14.4](../../../../../Refactor.md), [docs/measurement.md](../../../../measurement.md), [docs/planner_proofs.md](../../../../planner_proofs.md), [docs/residual_candidates.md](../../../../residual_candidates.md), [docs/meta_candidate_adapter.md](../../../../meta_candidate_adapter.md), [docs/ranking.md](../../../../ranking.md), [tests/reference/tree_oracle.cpp](../../../../../tests/reference/tree_oracle.cpp), [tests/reference/candidate_set.cpp](../../../../../tests/reference/candidate_set.cpp), [exact paper reference](https://arxiv.org/pdf/2301.04003v2#page=3), [exact paper reference](https://arxiv.org/html/2603.14754v1), [exact paper reference](https://arxiv.org/html/2603.15465v2) |

## B0004

[Lines 37–45](../../../../../examples/component-planning/reference.cpp#L37); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L37-L45:sha256:d7294fc91bc9a903230d9a7cec53c21bf127181e5df756c1bd30ee023bbf9df0
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Read a source or request file with a hard sixteen-MiB diagnostic input cap. |
| inputs / outputs | A filesystem path yields exact binary file bytes in an owning string. |
| invariants | Before each append, the count fits the remaining cap; text.size never exceeds the cap, so subtraction is safe. |
| ownership | Local ifstream closes on return or exception; the returned string owns bytes independently of the file. |
| failure | Open, stream badbit, cap or allocation errors propagate before native admission; truncated success is never emitted. |
| cost | Linear read and string growth in file bytes, bounded by sixteen MiB per input; separate from native requested-memory accounts. |
| Design | [Refactor.md §14.1–14.4](../../../../../Refactor.md), [docs/measurement.md](../../../../measurement.md), [docs/planner_proofs.md](../../../../planner_proofs.md), [docs/residual_candidates.md](../../../../residual_candidates.md), [docs/meta_candidate_adapter.md](../../../../meta_candidate_adapter.md), [docs/ranking.md](../../../../ranking.md), [tests/reference/tree_oracle.cpp](../../../../../tests/reference/tree_oracle.cpp), [tests/reference/candidate_set.cpp](../../../../../tests/reference/candidate_set.cpp), [exact paper reference](https://arxiv.org/pdf/2301.04003v2#page=3), [exact paper reference](https://arxiv.org/html/2603.14754v1), [exact paper reference](https://arxiv.org/html/2603.15465v2) |

## B0005

[Lines 46–50](../../../../../examples/component-planning/reference.cpp#L46); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L46-L50:sha256:e56fa6c8577a0c288b4f77867e740fbd6147fa4b3fc8dca78f2116b5de5a9fcf
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Expose phase nanoseconds only for the explicit measure command. |
| inputs / outputs | Measure flag and two steady-clock points produce null in verify mode or a nonnegative uint64 duration. |
| invariants | Verify records never expose these call timers as eligible observations. A clock regression rejects instead of wrapping. |
| ownership | Returns one owning JSON scalar with no query/runtime references. |
| failure | Negative duration or JSON allocation failure aborts the diagnostic. |
| cost | One duration conversion per named phase; call boundaries exclude host export/copy/cleanup, all still present in child process wall. |
| Design | [Refactor.md §14.1–14.4](../../../../../Refactor.md), [docs/measurement.md](../../../../measurement.md), [docs/planner_proofs.md](../../../../planner_proofs.md), [docs/residual_candidates.md](../../../../residual_candidates.md), [docs/meta_candidate_adapter.md](../../../../meta_candidate_adapter.md), [docs/ranking.md](../../../../ranking.md), [tests/reference/tree_oracle.cpp](../../../../../tests/reference/tree_oracle.cpp), [tests/reference/candidate_set.cpp](../../../../../tests/reference/candidate_set.cpp), [exact paper reference](https://arxiv.org/pdf/2301.04003v2#page=3), [exact paper reference](https://arxiv.org/html/2603.14754v1), [exact paper reference](https://arxiv.org/html/2603.15465v2) |

## B0006

[Lines 51–65](../../../../../examples/component-planning/reference.cpp#L51); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L51-L65:sha256:ec5e58028c755d5839d9b8dc5d979b4a4ee70ebc7e7f7020642799ce166b13ce
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Own the decoded experiment grants and translate them directly into existing candidate and rank limit DTOs. |
| inputs / outputs | Request stores method, command flag, finite work/memory/depth/cap values and physical-table training repetitions. |
| invariants | Candidate enumeration uses work/record/cell/depth/candidate caps; rank uses its own work/candidate/cell cap and fixed64MiB payload cap. These are different logical phases, not equal CPU budgets. |
| ownership | Owns method/training storage; returned limit structures copy only scalar grants and retain no Request pointer. |
| failure | No failure conversion here; allocations during Request construction propagate to the outer CLI handler. |
| cost | Scalar limit translation plus owning vector storage proportional to physical-table count; not hot-path engine design. |
| Design | [Refactor.md §14.1–14.4](../../../../../Refactor.md), [docs/measurement.md](../../../../measurement.md), [docs/planner_proofs.md](../../../../planner_proofs.md), [docs/residual_candidates.md](../../../../residual_candidates.md), [docs/meta_candidate_adapter.md](../../../../meta_candidate_adapter.md), [docs/ranking.md](../../../../ranking.md), [tests/reference/tree_oracle.cpp](../../../../../tests/reference/tree_oracle.cpp), [tests/reference/candidate_set.cpp](../../../../../tests/reference/candidate_set.cpp), [exact paper reference](https://arxiv.org/pdf/2301.04003v2#page=3), [exact paper reference](https://arxiv.org/html/2603.14754v1), [exact paper reference](https://arxiv.org/html/2603.15465v2) |

## B0007

[Lines 66–83](../../../../../examples/component-planning/reference.cpp#L66); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L66-L83:sha256:2be1595cab497bee8242d449528763332199d5a6ccf8edc187febbb95f34087f
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Admit the closed native search request and all finite per-phase grants. |
| inputs / outputs | A JSON object and physical-table count produce an owning Request for exactly five methods and verify/measure. |
| invariants | Exactly fourteen named fields are required; schema version1 is a real integer. Every grant is bounded; training has exactly one count0..32 per physical table. |
| ownership | Copies method and scalar training counts; input JSON remains borrowed and unchanged. |
| failure | Unknown/missing fields, method/command/type/range errors reject before any search; no permissive default or fallback method. |
| cost | Visits fourteen fields and the finite training vector. Admission/file bytes are measured separately from algorithm calls. |
| Design | [Refactor.md §14.1–14.4](../../../../../Refactor.md), [docs/measurement.md](../../../../measurement.md), [docs/planner_proofs.md](../../../../planner_proofs.md), [docs/residual_candidates.md](../../../../residual_candidates.md), [docs/meta_candidate_adapter.md](../../../../meta_candidate_adapter.md), [docs/ranking.md](../../../../ranking.md), [tests/reference/tree_oracle.cpp](../../../../../tests/reference/tree_oracle.cpp), [tests/reference/candidate_set.cpp](../../../../../tests/reference/candidate_set.cpp), [exact paper reference](https://arxiv.org/pdf/2301.04003v2#page=3), [exact paper reference](https://arxiv.org/html/2603.14754v1), [exact paper reference](https://arxiv.org/html/2603.15465v2) |

## B0008

[Lines 84–87](../../../../../examples/component-planning/reference.cpp#L84); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L84-L87:sha256:bbb9f4f568a513ab93f9c1f7cc6182fcc7340c46eb91cbb1b786788b4aa7a67d
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Construct the strict real P06 producer/replay limits used by original-minimum search or residual exact repair. |
| inputs / outputs | A phase work grant and Request logical depth produce strict SearchOptions. |
| invariants | Producer and independent replay each receive the explicit named grant. No best-effort incumbent is presented as a verified optimum. |
| ownership | Returns a value DTO; catalog/query ownership belongs to ExactSearch creation. |
| failure | No local recovery or synthesized proof on limits; real P06 stop reports remain authoritative. |
| cost | Constant-size cold option construction; grants bound existing work counters rather than elapsed CPU. |
| Design | [Refactor.md §14.1–14.4](../../../../../Refactor.md), [docs/measurement.md](../../../../measurement.md), [docs/planner_proofs.md](../../../../planner_proofs.md), [docs/residual_candidates.md](../../../../residual_candidates.md), [docs/meta_candidate_adapter.md](../../../../meta_candidate_adapter.md), [docs/ranking.md](../../../../ranking.md), [tests/reference/tree_oracle.cpp](../../../../../tests/reference/tree_oracle.cpp), [tests/reference/candidate_set.cpp](../../../../../tests/reference/candidate_set.cpp), [exact paper reference](https://arxiv.org/pdf/2301.04003v2#page=3), [exact paper reference](https://arxiv.org/html/2603.14754v1), [exact paper reference](https://arxiv.org/html/2603.15465v2) |

## B0009

[Lines 88–93](../../../../../examples/component-planning/reference.cpp#L88); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L88-L93:sha256:f29350ea21fbf0c79cebe782c0e20f8b35ffde5eef853def5108aec3c957a4cd
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Advance a real retained ExactSearch through quantum-only yields until a substantive stop. |
| inputs / outputs | A mutable search owner receives4096-work quanta until stop is neither quantum_work nor quantum_time. |
| invariants | Only explicit continuation yields resume. Resource, proof, infeasible and completed stops remain visible to callers. |
| ownership | Borrows one retained ExactSearch; its catalog/query/proof owners remain alive for the entire loop. |
| failure | Does not swallow allocation/internal/limit stops or restart work; exceptions propagate. |
| cost | Actual producer/replay transitions are bounded by configured phase limits. Quantum looping adds no timestamp hooks to engine code. |
| Design | [Refactor.md §14.1–14.4](../../../../../Refactor.md), [docs/measurement.md](../../../../measurement.md), [docs/planner_proofs.md](../../../../planner_proofs.md), [docs/residual_candidates.md](../../../../residual_candidates.md), [docs/meta_candidate_adapter.md](../../../../meta_candidate_adapter.md), [docs/ranking.md](../../../../ranking.md), [tests/reference/tree_oracle.cpp](../../../../../tests/reference/tree_oracle.cpp), [tests/reference/candidate_set.cpp](../../../../../tests/reference/candidate_set.cpp), [exact paper reference](https://arxiv.org/pdf/2301.04003v2#page=3), [exact paper reference](https://arxiv.org/html/2603.14754v1), [exact paper reference](https://arxiv.org/html/2603.15465v2) |

## B0010

[Lines 94–100](../../../../../examples/component-planning/reference.cpp#L94); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L94-L100:sha256:f52986d0dce6f372966988531e4c106ccd5fd5620bb85af5d76d2cb14f903591
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Drain real candidate publication until exhaustion or a substantive resource/failure stop. |
| inputs / outputs | A mutable CandidateProvider receives4096-work quanta and resumes only candidate_ready or quantum yields. |
| invariants | Candidate capacity, work, records, cells, depth and OOM stop states remain intact; this helper does not imply family completeness. |
| ownership | Borrows the sole provider; published candidates and retained progress remain owned by that provider and later snapshot. |
| failure | Never raises limits, drops proposals or supplies a fallback to recover an empty prefix. |
| cost | Work equals actual admitted provider transitions under configured grants; finite emitted candidate cap is128. |
| Design | [Refactor.md §14.1–14.4](../../../../../Refactor.md), [docs/measurement.md](../../../../measurement.md), [docs/planner_proofs.md](../../../../planner_proofs.md), [docs/residual_candidates.md](../../../../residual_candidates.md), [docs/meta_candidate_adapter.md](../../../../meta_candidate_adapter.md), [docs/ranking.md](../../../../ranking.md), [tests/reference/tree_oracle.cpp](../../../../../tests/reference/tree_oracle.cpp), [tests/reference/candidate_set.cpp](../../../../../tests/reference/candidate_set.cpp), [exact paper reference](https://arxiv.org/pdf/2301.04003v2#page=3), [exact paper reference](https://arxiv.org/html/2603.14754v1), [exact paper reference](https://arxiv.org/html/2603.15465v2) |

## B0011

[Lines 101–108](../../../../../examples/component-planning/reference.cpp#L101); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L101-L108:sha256:2e2e4b4246ad94edef3e7f1170609949b3f8ec689de8ea8284ff6973c94d548b
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Describe the actual emitted tree shape and the local normalized-family predicate. |
| inputs / outputs | A checked FreeConnexTree produces node count, generalized count, maximum child fanout and no-unary-generalized flag. |
| invariants | Generalized nodes count zero in native height; normalized_no_unary requires at least two children for each generalized node. This is diagnostic classification, not independent P02 authority. |
| ownership | Borrows an existing checked tree and returns scalar JSON; no topology mutation or owner alias is retained. |
| failure | JSON allocation failures propagate; it does not repair or silently normalize a tree. |
| cost | One pass over tree nodes, with constant work per node. |
| Design | [Refactor.md §14.1–14.4](../../../../../Refactor.md), [docs/measurement.md](../../../../measurement.md), [docs/planner_proofs.md](../../../../planner_proofs.md), [docs/residual_candidates.md](../../../../residual_candidates.md), [docs/meta_candidate_adapter.md](../../../../meta_candidate_adapter.md), [docs/ranking.md](../../../../ranking.md), [tests/reference/tree_oracle.cpp](../../../../../tests/reference/tree_oracle.cpp), [tests/reference/candidate_set.cpp](../../../../../tests/reference/candidate_set.cpp), [exact paper reference](https://arxiv.org/pdf/2301.04003v2#page=3), [exact paper reference](https://arxiv.org/html/2603.14754v1), [exact paper reference](https://arxiv.org/html/2603.15465v2) |

## B0012

[Lines 109–119](../../../../../examples/component-planning/reference.cpp#L109); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L109-L119:sha256:7a5af6b16d744290d16f6b04e1c9955d4a8a245f6640252efdfbc8c6e82fda86
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Serialize real meta construction, ordinary enumeration and generalized mapping stops and resource usage separately. |
| inputs / outputs | MetaCandidateReport yields exact enum values, actual work/node/cell/fragment/output/depth counts, ordinary/fiber exhaustion and scope/cost labels. |
| invariants | Preparation exhaustion is kept distinct from later P02/height/provider exhaustion. The local inverse-fiber proof is not attributed to a P3 generalized or event-cost theorem. |
| ownership | Copies scalar counters and scope strings into owning JSON; the report owner may then be destroyed. |
| failure | No missing phase is relabelled success; JSON allocation failures abort. |
| cost | Finite metadata serialization only; does not enumerate additional trees or introduce runtime costs. |
| Design | [Refactor.md §14.1–14.4](../../../../../Refactor.md), [docs/measurement.md](../../../../measurement.md), [docs/planner_proofs.md](../../../../planner_proofs.md), [docs/residual_candidates.md](../../../../residual_candidates.md), [docs/meta_candidate_adapter.md](../../../../meta_candidate_adapter.md), [docs/ranking.md](../../../../ranking.md), [tests/reference/tree_oracle.cpp](../../../../../tests/reference/tree_oracle.cpp), [tests/reference/candidate_set.cpp](../../../../../tests/reference/candidate_set.cpp), [exact paper reference](https://arxiv.org/pdf/2301.04003v2#page=3), [exact paper reference](https://arxiv.org/html/2603.14754v1), [exact paper reference](https://arxiv.org/html/2603.15465v2) |

## B0013

[Lines 120–122](../../../../../examples/component-planning/reference.cpp#L120); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L120-L122:sha256:a79a5ddc80cba7cc493784cbe3cb9d7a3ea5b8c45fd02119b344c569ad82d304
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | State the authority of the following C02 census and the absence of caller-manufactured Evidence. |
| inputs / outputs | Documentation connects declared per-physical-table repetition counts to actual inserts/noops committed by scoring. |
| invariants | The actual runtime capture factory, not a hand-written weight object, supplies admissible C02 Evidence. |
| ownership | Comment-only block; executable ownership is specified by scoring. |
| failure | No executable failure behavior. |
| cost | No generated code or execution overhead. |
| Design | [Refactor.md §14.1–14.4](../../../../../Refactor.md), [docs/measurement.md](../../../../measurement.md), [docs/planner_proofs.md](../../../../planner_proofs.md), [docs/residual_candidates.md](../../../../residual_candidates.md), [docs/meta_candidate_adapter.md](../../../../meta_candidate_adapter.md), [docs/ranking.md](../../../../ranking.md), [tests/reference/tree_oracle.cpp](../../../../../tests/reference/tree_oracle.cpp), [tests/reference/candidate_set.cpp](../../../../../tests/reference/candidate_set.cpp), [exact paper reference](https://arxiv.org/pdf/2301.04003v2#page=3), [exact paper reference](https://arxiv.org/html/2603.14754v1), [exact paper reference](https://arxiv.org/html/2603.15465v2) |

## B0014

[Lines 123–167](../../../../../examples/component-planning/reference.cpp#L123); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L123-L167:sha256:e4fc7d8664709d384199da57c92287dfc3dea9cbd8e5ae667e529ac7dfa5eae3
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Score the actual retained family with genuine committed-input C02 census evidence. |
| inputs / outputs | A checked snapshot plus Request lowers its first tree, runs actual all-zero inserts/noops in physical-table order, captures Evidence, ranks all retained candidates and emits exact scores/choice or explicit unavailability. |
| invariants | Only unconstrained nonnullable int64 tables of arity&lt;=16 are scored. Training count includes noops and aliases use physical-table weights per native occurrence. Capture/rank preconditions remain native. This is structural-depth quality, never C03/ns or a complete latency theorem. |
| ownership | Owns local lowered plan, DeltaRuntime, pending/committed epochs, capture and rank results. Pending borrows local cells only through completed commit. Snapshot remains alive; JSON copies keys/ratios before local destruction. |
| failure | No candidates or unsupported scoring schema return explicit availability. Capture/rank stops preserve real reasons. Other errors propagate; no zero score or fallback estimate is invented. |
| cost | Charges actual training, capture and rank together in its named call timer; whole-child wall includes destruction. Native requested-byte peak belongs to this local owner, not total process RSS or search-only memory. |
| Design | [Refactor.md §14.1–14.4](../../../../../Refactor.md), [docs/measurement.md](../../../../measurement.md), [docs/planner_proofs.md](../../../../planner_proofs.md), [docs/residual_candidates.md](../../../../residual_candidates.md), [docs/meta_candidate_adapter.md](../../../../meta_candidate_adapter.md), [docs/ranking.md](../../../../ranking.md), [tests/reference/tree_oracle.cpp](../../../../../tests/reference/tree_oracle.cpp), [tests/reference/candidate_set.cpp](../../../../../tests/reference/candidate_set.cpp), [exact paper reference](https://arxiv.org/pdf/2301.04003v2#page=3), [exact paper reference](https://arxiv.org/html/2603.14754v1), [exact paper reference](https://arxiv.org/html/2603.15465v2) |

## B0016

[Lines 169–275](../../../../../examples/component-planning/reference.cpp#L169); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L169-L275:sha256:9098b07868de69377c49db61353e5f44784c96309a7bda4dee3de150ee6b20b7
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Execute one bounded finite search diagnostic with real algorithms, original-proof authority and independently named literal controls. |
| inputs / outputs | QUERY and closed REQUEST yield one source-bound b04_finite_search_record_v1. literal_minimum calls genuine exhaustive labelled topology/full-scope-powerset reference; other methods obtain typed original P06 optimum, then P07/residual/meta or tiny literal-family candidates and actual C02 scores. |
| invariants | Input rows/updates must be empty; domain&lt;=6occurrences,16active variables,6tables and no contradiction. Literal complete no-tree maps to infeasible, resource stop keeps nullheight. Residual upper must&gt;=originalh* and from_proposals only admits minima; meta ordinary+fiber exhaustion also needs provider exhaustion. Tiny reference caps remain3atoms/3activevars. Every published candidate uses actual P02/key/height admission; no proof flag or paper recipe is trusted. |
| ownership | Owns exact file bytes, decoded document/request, real search/proof/provider/snapshot/results and final JSON. Typed proofs keep bindings alive. Proposal vectors move into owning provider. Output strings own copied payloads; no borrowed tree survives its provider. |
| failure | Malformed input rejects. Algorithm resource/infeasibility/unavailable prefixes remain success records with exact native stops. Host/OOM/output cap/flush failures return nonzero; no silent candidate deletion, implicit exact/meta fallback or timing retry. |
| cost | Each child actually reruns its shared proof and retains that separate timer. Named algorithm/admission/scoring calls are disjoint; export/proposal copies/startup/cleanup stay in processwall. Report&lt;=16MiB. Finite work/records/cells/depth/candidate limits bound named APIs, not all process allocations or global execution complexity. |
| Design | [Refactor.md §14.1–14.4](../../../../../Refactor.md), [docs/measurement.md](../../../../measurement.md), [docs/planner_proofs.md](../../../../planner_proofs.md), [docs/residual_candidates.md](../../../../residual_candidates.md), [docs/meta_candidate_adapter.md](../../../../meta_candidate_adapter.md), [docs/ranking.md](../../../../ranking.md), [tests/reference/tree_oracle.cpp](../../../../../tests/reference/tree_oracle.cpp), [tests/reference/candidate_set.cpp](../../../../../tests/reference/candidate_set.cpp), [exact paper reference](https://arxiv.org/pdf/2301.04003v2#page=3), [exact paper reference](https://arxiv.org/html/2603.14754v1), [exact paper reference](https://arxiv.org/html/2603.15465v2) |

## B0017

[Lines 276–276](../../../../../examples/component-planning/reference.cpp#L276); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L276-L276:sha256:533f16bca7d58f44b3103b92e3485d22cfbb34bbad5ea3f3fa3b5a9dcb24ec89
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | End the diagnostic translation-unit namespace. |
| inputs / outputs | Closes the anonymous namespace before the process entry point. |
| invariants | Helpers remain translation-unit local; the public process interface is main. |
| ownership | No runtime state or owner is created. |
| failure | No executable failure behavior. |
| cost | No execution overhead. |
| Design | [Refactor.md §14.1–14.4](../../../../../Refactor.md), [docs/measurement.md](../../../../measurement.md), [docs/planner_proofs.md](../../../../planner_proofs.md), [docs/residual_candidates.md](../../../../residual_candidates.md), [docs/meta_candidate_adapter.md](../../../../meta_candidate_adapter.md), [docs/ranking.md](../../../../ranking.md), [tests/reference/tree_oracle.cpp](../../../../../tests/reference/tree_oracle.cpp), [tests/reference/candidate_set.cpp](../../../../../tests/reference/candidate_set.cpp), [exact paper reference](https://arxiv.org/pdf/2301.04003v2#page=3), [exact paper reference](https://arxiv.org/html/2603.14754v1), [exact paper reference](https://arxiv.org/html/2603.15465v2) |

## B0018

[Lines 277–280](../../../../../examples/component-planning/reference.cpp#L277); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L277-L280:sha256:708cc0cac18e7e869ec90995d40497b8e7d3be21698606f8a6d6109f85884c0f
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Provide a single ordinary CLI error boundary for the diagnostic. |
| inputs / outputs | main forwards argv to run, returns its status, and prints propagated standard exceptions to stderr with exit1. |
| invariants | An input/algorithm/output error never prints a synthetic successful report. There is no retry or native engine exception framework. |
| ownership | Stack-owned diagnostic owners unwind before the catch reports failure. |
| failure | All standard exceptions terminate this invocation nonzero; normal run also checks output flush success. |
| cost | Process entry/exit only; cleanup remains part of child process wall. |
| Design | [Refactor.md §14.1–14.4](../../../../../Refactor.md), [docs/measurement.md](../../../../measurement.md), [docs/planner_proofs.md](../../../../planner_proofs.md), [docs/residual_candidates.md](../../../../residual_candidates.md), [docs/meta_candidate_adapter.md](../../../../meta_candidate_adapter.md), [docs/ranking.md](../../../../ranking.md), [tests/reference/tree_oracle.cpp](../../../../../tests/reference/tree_oracle.cpp), [tests/reference/candidate_set.cpp](../../../../../tests/reference/candidate_set.cpp), [exact paper reference](https://arxiv.org/pdf/2301.04003v2#page=3), [exact paper reference](https://arxiv.org/html/2603.14754v1), [exact paper reference](https://arxiv.org/html/2603.15465v2) |
