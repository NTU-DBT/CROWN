# `examples/meta-candidates/main.cpp` — block usage map

[Source](../../../../../examples/meta-candidates/main.cpp) · [Source index](../../../README.md) · [Subsystem contracts](../../../subsystem_contracts.md) · [Reviewed primitives](../../../primitives.md)

Demonstrate a concrete public workflow and executable invocation using installed/native CROWN interfaces.

Snapshot SHA-256: `e095bc24754b5a45fd976e88404d748caa6f7ceb5e5deecd57aca2ae73c7b638`. 45 lines partitioned into 2 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [examples](../../../subsystem_contracts.md#examples). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/cli.md](../../../../cli.md), [docs/native_build.md](../../../../native_build.md), [docs/measurement.md](../../../../measurement.md), [docs/ranking_evaluation.md](../../../../ranking_evaluation.md), [docs/reoptimization.md](../../../../reoptimization.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–7](../../../../../examples/meta-candidates/main.cpp#L1) | Imports dependencies. | source comment (unverified): // Boolean R(x),S(y): ordinary rooted trees have height2, whereas the empty · [reviewed contract](#b0001) |
| [B0002 · 8–45](../../../../../examples/meta-candidates/main.cpp#L8) | Callable definition: int main() | calls planner::ExactSearch::create, advance, optimum, std::runtime_error; returns std::cout ? 0 : 1; 1; 1 loop sites; source comment (unverified): // Boolean R(x),S(y): ordinary rooted trees have height2, whereas the empty · [reviewed contract](#b0002) |

## B0001

[Lines 1–7](../../../../../examples/meta-candidates/main.cpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L1-L7:sha256:e4b1d1158a47e6deee72cc34251b97c49303ba34480da897a145f2cd85c9cdd4
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Import the optional meta-candidate API, candidate serialization, and standard facilities for the standalone example. |
| inputs / outputs | Includes provide the public planner and I/O entry points used by main(). |
| invariants | The example is a consumer of the public target; it does not reach into private implementation headers. |
| ownership | Includes retain no runtime state. |
| failure | Missing installed public headers fail during compilation. |
| cost | Compilation/dependency cost only. |
| Design | [docs/meta_candidate_adapter.md](../../../../meta_candidate_adapter.md), [cmake/CrownInstall.cmake](../../../../../cmake/CrownInstall.cmake) |

## B0002

[Lines 8–45](../../../../../examples/meta-candidates/main.cpp#L8); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L8-L45:sha256:eeaf966f67838a925ce061d2d31dcc7183ff7f471796bd490ce61b37c5ff656f
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Demonstrate finite meta-candidate preparation for Boolean R(x), S(y) and emit its bounded status/result summary. |
| inputs / outputs | Builds a Boolean query with two disjoint unary atoms and an empty head, obtains an ExactSearch VerifiedOptimum, prepares the meta family, consumes the provider, checks the single candidate and exhaustion, then writes JSON containing ordinary-rooted/undirected counts, mode, exhaustion flags, heuristic/global-cost flags, family scope, and candidate. |
| invariants | For this example, the generalized empty root gives checked upper height one while an ordinary rooted tree has two levels; the sample's successful status is an instance, not a universal comparison theorem. Global cost optimality is explicitly false and the family is finite proposals. |
| ownership | Catalog, query, proof, prepared result, provider, and serialized candidate are owned by main's local values. |
| failure | Missing proof/provider, unexpected candidate count/status, serialization failure, or bad output stream returns failure; the example reports its own failure code. |
| cost | A two-atom example with bounded exact-search/provider steps; this is explanatory sample work, not a planner runtime bound. |
| Design | [docs/meta_candidate_adapter.md](../../../../meta_candidate_adapter.md), [docs/candidate_alternatives.md](../../../../candidate_alternatives.md), [docs/planner_proofs.md](../../../../planner_proofs.md) |
