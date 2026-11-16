# Source map and integration seams

Paths below are repository-relative. Their exact bytes, including complete
headers/implementations rather than only the quoted sections, are pinned in
`INPUT_SHA256SUMS`. This map identifies existing contracts; the proposed files
at the end do not exist as native C02 implementation in this packet.

| Existing input | Source-grounded consequence |
| --- | --- |
| `Refactor.md`, sections 9.1/9.2 and cards C02/C03/C05/C07 | Separate validity, certified height, and proxy ranking; keep the native-depth baseline, unknown fallback, conditional event calibration, deployment, and measured regret distinct. |
| `include/crown/planner/search.hpp`, `SearchBinding`, `ValidatedIncumbent`, `VerifiedOptimum`, `PhaseCeiling` | Immutable original binding and proof are typed; an incumbent is only an upper bound. Resource/time progress is not proof authority. |
| `include/crown/planner/candidates.hpp`, `MinimumHeightCandidate`, `CandidateSnapshot`, `CandidateProvider` | Published members are already P02/height checked. Snapshot owns the retained prefix/completeness, but contains no last stop reason. Moves can invalidate handles. |
| `src/planner/candidates.cpp`, `context_valid`, `BindingEncoder`, `binding_bytes`, provider admission/publication, cache | Only the existing structural/no-cost profile is admitted. Full binding is a private, raw-byte, framed format. Catalog statistics and hints are included. Cache does not store ranking decisions. |
| `src/planner/candidate_key.cpp` and `.hpp` | Complete canonical tokens preserve root, node kind, variable scopes, occurrence identities, and grouping; node/child ordering and display IDs are removed. Numeric IDs alone are not portable identities. |
| `docs/candidate_alternatives.md` | Declared finite normal-form family plus admitted seeds has honest partial/exhausted status; some minimum-height representative is covered, not every minimum-cost tree. Cache prefix is not continuation state. |
| `include/crown/ir/tree.hpp`, `src/planner/verify.cpp`, phases `above`, `guard`, `property_finish`, `maximal_*` | Native height counts native nodes, generalized nodes add zero and have no native ancestor. Generalized scope is included in every child scope. Visible connex traversal depends on output-only separators. |
| `include/crown/ir/model.hpp`, `include/crown/catalog/catalog.hpp` | Physical table, logical atom, alias, source schema, typed constants, and estimates are distinct inputs. Aliases remain distinct occurrences. |
| `include/crown/frontend/normalize.hpp`, `OccurrenceAdapter`, `NormalizedSql` | Source adapters/base routes need the actual normalized program; logical core table numbers do not by themselves identify physical sources. |
| `include/crown/ir/physical.hpp`, `PhysicalInput`, `PhysicalNode`, `PhysicalRelation`, `IndexRequirement` | Actual input mapping, local relation/layout roles, and shared index identities exist. `PhysicalPlan` is owning/private-factory metadata, not a minimum-height certificate. |
| `include/crown/planner/lower.hpp`, `src/planner/lower.cpp`, `compile_nodes`, `compile_inputs`, `compile_edges`, `compile_enumeration` | Alternative plans can be lowered from their checked trees; normalized programs are replayed. Reverse indexes belong to native parent records, visible indexes to their own E relation, and matching requirements are shared. |
| `include/crown/io/identity.hpp`, `IdentityLimits`, `QueryIdentity` | Identity canonicalization has its own finite work limit and reported work. Its alpha-erasing semantic hashes cannot replace P07's exact binding comparison. |
| `include/crown/runtime/statistics.hpp` | Finite request limits and exact/incomplete distribution semantics. Accounted bytes are a component model. No new arbitrary-precision score implementation is implied. |
| `include/crown/runtime/owner_statistics.hpp`, `src/runtime/owner_statistics.cpp` | Source cardinality uses `SourceScope` with absent fields, maximum 256 selections. Owner/sequence/layer freshness is distinct from storage invalidation revision. |
| `src/runtime/physical.cpp`, `capture_statistics`, `statistics_freshness` | Reads actual source stores; compares against the real owner and committed sequence. Occurrence counts are a different scoped population. |
| `src/runtime/support.cpp`, `child`, `presence`, invariant inspection | Generalized records are child-P-key union members; zero-presence candidates are reclaimed. S is a record subset. These facts justify a structural union bound, not transplanted observed degrees. |
| `include/crown/runtime/workload_statistics.hpp`, `src/runtime/workload_statistics.cpp` | Distinct physical/logical descriptor scopes; per-source/op roots; native occurrence routing; exact physical input shares; current/previous segment metadata; no arrival Hz. |
| `src/runtime/statistics_collection.cpp`, `physical_fact`, `finish`, `detail`, `reset`, `rotate` | Root input facts publish on outer commit, including no-ops; aborted attempts do not merge. Root census is independent of selected/untruncated detail publication. Reset/configuration/segment changes have separate identities. |
| `include/crown/runtime/combined_statistics.hpp`, `src/runtime/combined_statistics.cpp` | Private combined factory checks owner, epoch, plan hash, and pending alignment. Different availability/interval domains remain separate. |
| `include/crown/runtime/session.hpp`, `src/runtime/session.cpp`, statistics accessors | One-guard actual session capture; pending metadata, committed unread output, stopped/live owner, and released owner are distinct. Dropped old artifacts remain readable, not current. |
| `include/crown/runtime/physical.hpp`, `support.hpp`, `delta.hpp` | Actual capture and freshness accessors; storage-only Support cannot supply physical-source evidence. No borrowed runtime callback is needed in a pure scorer. |
| `include/crown/ir/scalar.hpp`, `ids.hpp`, `include/crown/storage/layout.hpp` | Decimal is bounded canonical value storage, not a general score type. IDs/widths use size_t; P07 bounds that domain to <=64 bits. Derived scores require exact wider arithmetic. |
| `CMakeLists.txt` | Existing direction is core -> SQL/plan -> runtime -> explain; production/testing runtime archives are distinct. P07 is in core. C02 must not introduce runtime/report dependencies into core or mix runtime variants. |
| `docs/statistics.md` | Published component-accounting, population, saturation, no-clock, freshness, and lifecycle limits match the evidence rules above. Native matrix pending wording is historical at this packet's pin time. |
| `tests/unit/candidates_test.cpp`, `tests/reference/candidate_set.*`, `tests/reference/tree_oracle.*` | Existing independent family enumeration and signature oracle, proof replay, key invariance, caps, slicing, bindings, and cache tests can be reused without using the production scorer as expected output. |
| `tests/candidates/queries/boolean_rst.cq.json` and three native/generalized root trees | Existing equal-height alternatives support a literal hot-input reversal and distinct memory-proxy ordering. |
| `tests/candidates/queries/self_join_equal_scope_three.cq.json` and direct/permuted trees | Existing alias and structural-key fixtures support route multiplicity and tie invariance tests. |
| `tests/unit/combined_statistics_test.cpp`, `scalar_statistics_test.cpp`, `workload_statistics_test.cpp` and fixtures | Existing public owner/interval/failed-admission/scalar tests guide focused C02 adapter tests; they do not already prove ranking. |

## Proposed implementation layout

1. Factor P07's existing full-binding encoder into an internal core helper
   usable by candidates and C02. Preserve byte-for-byte output and every P07
   admission/cache rule. Add an explicitly bounded comparison/encoding path
   for ranking; no new public certificate constructor, JSON import, or digest-
   only equivalence API. Test all binding fields, including statistics, raw
   strings with NUL/high bytes, typed dates/Decimal, aliases, and repeated head.
2. Add proposed `include/crown/planner/ranking.hpp` and
   `src/planner/ranking.cpp` in a `crown_ranking` library depending on
   `crown_plan`/`crown_core`, with the usual private build options. It handles
   typed candidate admission, bounded exact wide arithmetic, depth walks, candidate-local
   lowering/slot terms, deterministic comparison, immutable reproduction
   records, and transactional publication. Its headers/implementation must not
   include runtime statistics or observability.
3. Add proposed `include/crown/runtime/ranking_evidence.hpp` and
   `src/runtime/ranking_evidence.cpp` in a `crown_ranking_runtime` bridge linked
   to `crown_ranking` and `crown_runtime`. It captures actual owners and validates
   C01 availability/freshness/intervals before constructing ranking input. Keep
   private factories and neutral owned score inputs in the pure layer; retain
   native capture handles in the bridge when live reuse needs freshness checks.
   A pure-layer reproduction result never asserts current liveness.
4. If test-only C01 seams are needed, build a matching
   `crown_ranking_runtime_testing` bridge against `crown_runtime_testing` with
   its PUBLIC `CROWN_RUNTIME_TESTING` propagation. Never link both runtime
   variants into one executable. The pure ranking library should not acquire
   macro-dependent layout. No report archive is necessary for ranking.
5. Add focused unit/runtime/exception tests and documentation only after the
   C01 native matrix is complete and the implementation's own exact sources
   are frozen for root validation. Preserve existing CTests. A command that
   installs a chosen runtime, changes layouts/index options, or adds plan-cache
   decisions belongs to C05; do not sneak it into a score test.

The proposed public shape should offer: height-only ranking from a typed
snapshot; explicit immutable as-of statistical ranking; and a runtime bridge
that captures/revalidates live evidence. It should distinguish a completed
`RankingResult` carrying a typed candidate from a `RankingAttempt` with no
selection and a concrete unavailable/resource/admission reason. Exact C++
signatures and enum names are implementation work. This packet intentionally
does not promise constructors or getters that the current headers lack.

No changes to C01 v3 or legacy v2 report schemas are required for this baseline.
Any later ranking export should have its own version and exact integer/byte
transport tests and remain non-authoritative on import. A SHA is useful for
pinning artifacts, not for replacing a proof or cross-binding equality check.
