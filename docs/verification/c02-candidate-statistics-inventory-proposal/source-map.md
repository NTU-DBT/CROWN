# Source map

Paths below are current native headers/sources or existing fixtures. Exact
SHA-256 values for files read are in `input-pins.sha256`.

| Area | Source | What it establishes |
| --- | --- | --- |
| Typed candidate API | `include/crown/planner/candidates.hpp` | `VerifiedOptimum`-based provider, contexts, limits, candidates, snapshots, provenance, structural-key accessor, family completion semantics. |
| Optional residual seed | `include/crown/planner/residual.hpp`, `src/planner/residual.cpp` | Residual candidate is an upper-bound seed with its own provenance; CandidateProvider still validates it against the original binding and target height. |
| Proof authority | `include/crown/planner/search.hpp`, `include/crown/planner/oracle.hpp` | Private checked handles; exact search/replay entry points; public certificate aggregates are claims rather than authority handles. |
| Candidate admission | `src/planner/candidates.cpp` | Exact binding/context checks; target certified height; source order; P02 validation, height gate, key generation, dedup and family exhaustion. |
| Typed proof producers | `src/planner/search_session.cpp`, `src/planner/certificate.cpp` | `ExactSearch::optimum()` and replay publication of `CheckedCertificate`, which can carry a verified optimum. |
| Normal-form generator and key | `src/planner/candidate_generator.cpp`, `src/planner/candidate_key.cpp`, `src/planner/candidate_key.hpp`, `src/planner/candidate_machine.hpp` | Candidate tree enumeration and deterministic versioned canonical structural key; key is not proof or global identity. |
| P02 and height | `include/crown/planner/verify.hpp`, `src/planner/verify.cpp`, `src/planner/certificate.cpp` | Independent tree validation, global native height/edge depth, and independent certificate replay. |
| Tree and ID model | `include/crown/ir/tree.hpp`, `include/crown/ir/model.hpp`, `include/crown/ir/ids.hpp` | `FreeConnexTree`, node kind/scope/occurrence, query atom occurrence, plan-scoped numeric IDs. |
| Physical plan mapping | `include/crown/planner/lower.hpp`, `include/crown/ir/physical.hpp`, `src/planner/lower.cpp` | Candidate-specific `lower_tree`; `PhysicalInput`, `base_routes`, nodes, edges, indexes, and physical/logical table mapping. |
| Candidate fixture coverage | `tests/unit/candidates_test.cpp` | Existing complete-family counts and structural-key behavior tests. |
| Depth/tree examples | `tests/candidates/trees/boolean_rst_native_s_root.tree.json`, `tests/candidates/trees/boolean_rst_generalized_x_root.tree.json`, `tests/candidates/trees/boolean_rst_generalized_y_root.tree.json` | Existing Boolean R/S/T tree shapes used for the manual depth table. |
| Alias example | `tests/candidates/queries/self_join_equal_scope_three.cq.json`, `tests/candidates/trees/self_join_left_direct.tree.json` | Three distinct occurrences over one physical `Edge` table and one tree preserving their occurrence identity. |
| Owner statistics values | `include/crown/runtime/statistics.hpp`, `include/crown/runtime/owner_statistics.hpp`, `src/runtime/statistics.cpp` | Shared limits, exact/incomplete distributions, projected NDV/multiplicity histogram/heavy keys, compiled index degree distributions, typed scopes, components, owner stamp and freshness API. |
| Owner entry points | `include/crown/runtime/support.hpp`, `include/crown/runtime/physical.hpp`, `include/crown/runtime/delta.hpp`, `src/runtime/owner_statistics_detail.hpp`, `src/runtime/owner_statistics.cpp`, `src/runtime/physical.cpp`, `src/runtime/support.cpp`, `src/runtime/delta.cpp` | Actual owner captures, source/occurrence/node/index extraction, shared request budget, lower-only unavailable scopes, Delta delegation and committed owner freshness. |
| Workload statistics API | `include/crown/runtime/workload_statistics.hpp`, `src/runtime/workload_statistics.cpp`, `src/runtime/workload_statistics_detail.hpp` | Options, descriptors, cells, stamp/metadata, availability, denominator and ratio APIs; physical/logical scope distinction. |
| Workload collection | `src/runtime/statistics_collection.hpp`, `src/runtime/statistics_collection.cpp` | Attempt ordinal sampling, root input/changed/noop staging, abort/truncation behavior, complete-detail sample inputs, saturation. |
| Combined capture | `include/crown/runtime/combined_statistics.hpp`, `src/runtime/combined_statistics.cpp` | Immutable packaging of state and workload domains without merging their availability or interval semantics. |
| Current owner tests | `tests/unit/owner_statistics_test.cpp`, `tests/unit/owner_statistics_fixture.hpp` | Existing owner state, scope, freshness, budget and independent-fact coverage. |
| Current workload tests | `tests/unit/workload_statistics_test.cpp`, `tests/unit/workload_statistics_fixture.hpp` | Existing strata, sampling, no-op, abort/truncation, denominators and saturation coverage. |
| Historical preparation notes | `docs/verification/c01-statistics-owner-boundaries-2026-11-07.md`, `docs/verification/c01-statistics-owner-root-results-2026-11-07.md`, `docs/verification/c01-statistics-online-root-results-2026-11-07.md` | Earlier owner/workload slice constraints and preparation evidence. These predate current native C01 integration and are not current integration status. |

The packet's claims are limited to declarations/implementation/fixture
inspection. It did not execute these tests or regenerate the fixtures.
