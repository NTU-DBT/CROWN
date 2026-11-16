# `include/crown/io/candidates.hpp` — block usage map

[Source](../../../../../../include/crown/io/candidates.hpp) · [Source index](../../../../README.md) · [Subsystem contracts](../../../../subsystem_contracts.md) · [Reviewed primitives](../../../../primitives.md)

Retain and enumerate checked minimum-height candidate alternatives under bounded content budgets.

Snapshot SHA-256: `830af78896ea5d2d1d7339b2c768d8e22c37c6a7c37a600bb0080e360d56beac`. 11 lines partitioned into 1 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [io](../../../../subsystem_contracts.md#io). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/ingestion.md](../../../../../ingestion.md), [docs/query_identity.md](../../../../../query_identity.md), [docs/schema_evolution.md](../../../../../schema_evolution.md), [docs/cli.md](../../../../../cli.md), [docs/query_memory.md](../../../../../query_memory.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–11](../../../../../../include/crown/io/candidates.hpp#L1) | Imports dependencies; guards repeated header inclusion; declares namespace scope; declares callable signatures; declares values/defaults or compile-time conditions. | source comment (unverified): // Allocating export is outside advance quanta. Progress accepts the live owner, · [reviewed contract](#b0001) |

## B0001

[Lines 1–11](../../../../../../include/crown/io/candidates.hpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
[[nodiscard]] Json write_candidate_progress(const planner::CandidateProvider&);
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Declare diagnostic exports for the live candidate provider, one checked candidate, and an immutable candidate snapshot. |
| inputs / outputs | The overloads accept a provider owner, a \`MinimumHeightCandidate\`, or a \`CandidateSnapshot\` and return JSON for progress, a candidate, or the saved prefix. |
| invariants | Candidate serialization does not advance enumeration or rerun proof/tree verification. The candidate writer checks its height and canonical binding against the retained original proof, then serializes an addressable tree; exported JSON grants no checked-token authority. |
| ownership | The result DOM owns copied catalog/query/proof/tree/counters and nested prefix entries; provider and candidate retain their own immutable owners. |
| failure | Moved-from candidates/snapshots, unknown report enum values, mismatched original proof binding/height, or missing snapshot prefix entries are rejected. |
| cost | Serialization allocates and copies query binding, tree/proof fields, and each prefix candidate; it runs outside provider \`advance\` quanta. |
| Design | [include/crown/io/candidates.hpp §writer overloads](../../../../../../include/crown/io/candidates.hpp), [src/io/candidates.cpp §candidate and progress serialization](../../../../../../src/io/candidates.cpp), [src/planner/candidates.cpp §checked candidates](../../../../../../src/planner/candidates.cpp), [docs/candidate_alternatives.md §original proof and snapshots](../../../../../candidate_alternatives.md) |
