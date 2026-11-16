# `tests/support/update_pattern_fixture.hpp` — block usage map

[Source](../../../../../tests/support/update_pattern_fixture.hpp) · [Source index](../../../README.md) · [Subsystem contracts](../../../subsystem_contracts.md) · [Reviewed primitives](../../../primitives.md)

Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection.

Snapshot SHA-256: `e3301fe28ef7c47e28668b3880f4f1de759cca29f4e1c51eae2ea6cab9e0bcd4`. 38 lines partitioned into 5 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [tests](../../../subsystem_contracts.md#tests). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/code_review.md](../../../../code_review.md), [docs/reference_fuzz.md](../../../../reference_fuzz.md), [docs/task_ledger.md](../../../../task_ledger.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–8](../../../../../tests/support/update_pattern_fixture.hpp#L1) | Imports dependencies; guards repeated header inclusion; declares namespace scope. | source comment (unverified): // Refactor 5.3's seven-atom obstruction, expressed as ordinary typed DTOs. · [reviewed contract](#b0001) |
| [B0002 · 9–23](../../../../../tests/support/update_pattern_fixture.hpp#L9) | Callable definition: inline c02_test::Fixture height_three_fixture() | calls push_back, std::to_string, size, emplace_back; returns fixture; growth emplace_back, push_back; 4 loop sites; source comment (unverified): // Refactor 5.3's seven-atom obstruction, expressed as ordinary typed DTOs. · [reviewed contract](#b0002) |
| [B0003 · 24–25](../../../../../tests/support/update_pattern_fixture.hpp#L24) | Explanatory comments or spacing. | source comment (unverified): // Prove the original minimum, then retain one genuine candidate. The finite · [reviewed contract](#b0003) |
| [B0004 · 26–37](../../../../../tests/support/update_pattern_fixture.hpp#L26) | Callable definition: inline planner::CandidateSnapshot height_three_family(const c02_test::Fixture& fixture) | calls planner::ExactSearch::create, optimum, advance, c02_test::check; guard c02_test::check(next.progress.result!=planner::ResultKind::failed,"height-three proof failed");; returns provider.snapshot(); 2 loop sites; source comment (unverified): // Prove the original minimum, then retain one genuine candidate. The finite · [reviewed contract](#b0004) |
| [B0005 · 38–38](../../../../../tests/support/update_pattern_fixture.hpp#L38) | Closes surrounding scope/type. | source comment (unverified): // namespace crown::pattern_test · [reviewed contract](#b0005) |

## B0001

[Lines 1–8](../../../../../tests/support/update_pattern_fixture.hpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L1-L8:sha256:d5d91db409152a0baa91400ac6ba29fc0cd060c861f9c80538c0e5b1822868d5
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Set up the test-only pattern fixture namespace and its ordinary fixture dependencies. |
| inputs / outputs | Includes ranking_fixture definitions and std::array, then opens crown::pattern_test for the shared helpers. |
| invariants | The seven-atom description is context only; this block creates no checked tree, candidate, or proof authority. |
| ownership | Includes and namespace aliases retain no runtime query owner. |
| failure | Missing dependencies or ill-formed declarations fail compilation; there is no runtime boundary here. |
| cost | Preprocessing and compilation only; namespace/include declarations add no execution work. |
| Design | [tests/support/ranking_fixture.hpp](../../../../../tests/support/ranking_fixture.hpp), [build/verification/v53-taller-mixed-proof-v1/proof.md](../../../../../build/verification/v53-taller-mixed-proof-v1/proof.md), [docs/update_patterns.md](../../../../update_patterns.md) |

## B0002

[Lines 9–23](../../../../../tests/support/update_pattern_fixture.hpp#L9); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L9-L23:sha256:d0ad3b0655b988755aa5b8c9367c560e77175e4ae0f03ad69ecdc39f3b29a6d9
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Build the ordinary typed DTO for the proof packet’s seven-atom example. |
| inputs / outputs | No input; returns a c02_test::Fixture with seven int64 variables, seven relation/atom pairs using the listed scopes, and head variables x0, x1, and x6. |
| invariants | Dense table and variable IDs are built together; the scopes encode the fixed test query. The DTO alone proves no minimum height or runtime property. |
| ownership | Fixture vectors and strings own their metadata; normal copies duplicate ordinary containers. No MemoryAccount is involved. |
| failure | Vector/string allocation failures propagate; no validation or catch layer is added in the fixture builder. |
| cost | Linear in the seven variables, seven atoms, and fifteen scoped columns/terms, plus ordinary vector/string allocation. |
| Design | [tests/support/ranking_fixture.hpp](../../../../../tests/support/ranking_fixture.hpp), [build/verification/v53-taller-mixed-proof-v1/proof.md](../../../../../build/verification/v53-taller-mixed-proof-v1/proof.md), [docs/update_patterns.md](../../../../update_patterns.md) |

## B0003

[Lines 24–25](../../../../../tests/support/update_pattern_fixture.hpp#L24); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L24-L25:sha256:2ce014f1e53e8051d579eccd11f755dacf92c3fd36b6625dc8cbb1c89a3434c8
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Document that minimum-height and candidate authority come from the search/provider helper. |
| inputs / outputs | Two source comments state how the adjacent family helper establishes its witness and limit. |
| invariants | The comment expressly disclaims exhaustion of all compatible shapes and cost optimality; comments enforce nothing. |
| ownership | Source text only; no owner or lifetime. |
| failure | No runtime failure path; comment syntax remains subject to compilation. |
| cost | No runtime cost. |
| Design | [build/verification/v53-taller-mixed-proof-v1/proof.md](../../../../../build/verification/v53-taller-mixed-proof-v1/proof.md), [docs/planner_continuations.md](../../../../planner_continuations.md), [docs/candidate_alternatives.md](../../../../candidate_alternatives.md) |

## B0004

[Lines 26–37](../../../../../tests/support/update_pattern_fixture.hpp#L26); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L26-L37:sha256:be79fb54f12dd5e7e56bf51607a2d91c2d7008d0b042a302eede9dea176c4629
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Prove the supplied fixture’s exact optimum is height three, then retain one real candidate. |
| inputs / outputs | Takes a const fixture; advances ExactSearch in bounded quanta until an optimum or the 100,000-step guard, checks each result, requires optimum height 3, creates CandidateProvider, advances until a candidate appears, requires exactly one retained candidate, and returns its snapshot. |
| invariants | ExactSearch supplies the minimum proof; CandidateProvider supplies a genuine candidate. The helper intentionally does not assert family exhaustion or global cost optimality. |
| ownership | Search/provider are local owners; the returned snapshot retains its checked candidate/proof handles. The fixture is borrowed. |
| failure | Failed search/provider assertions throw through c02_test::check; allocation or planner failures are not caught or converted to a skip. |
| cost | Potentially substantial exact-search and provider work, capped by configured logical work and loop counts; no timing or optimal-maintenance-cost claim. |
| Design | [tests/support/ranking_fixture.hpp](../../../../../tests/support/ranking_fixture.hpp), [include/crown/planner/search.hpp](../../../../../include/crown/planner/search.hpp), [include/crown/planner/candidates.hpp](../../../../../include/crown/planner/candidates.hpp), [build/verification/v53-taller-mixed-proof-v1/proof.md](../../../../../build/verification/v53-taller-mixed-proof-v1/proof.md), [docs/planner_continuations.md](../../../../planner_continuations.md) |

## B0005

[Lines 38–38](../../../../../tests/support/update_pattern_fixture.hpp#L38); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L38-L38:sha256:3679efc5da0430d71d66839be947a8a4cfc86d56a5155c2f5a46b68201505f2f
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Close the test-only namespace. |
| inputs / outputs | No input or output; closes crown::pattern_test. |
| invariants | Structural delimiter only; it does not certify the preceding helpers. |
| ownership | No runtime ownership. |
| failure | Mismatched syntax fails compilation. |
| cost | No runtime cost. |
| Design | [tests/support/update_pattern_fixture.hpp](../../../../../tests/support/update_pattern_fixture.hpp), [docs/code_review.md](../../../../code_review.md) |
