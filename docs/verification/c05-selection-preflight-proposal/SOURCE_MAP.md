# Source grounding and proposed layers

All native paths below are read-only inputs to this packet. Proposed paths are
plain future-path text, not existing files or an application map. No source,
target, test registration, schema or native documentation is installed here.
`source-files.sha256` records the selected exact implementation/fixture inputs;
`INPUT_SHA256SUMS` additionally pins contracts, package manifests and immutable
root receipts. The C02 freeze receipt binds the larger native closure without
rechecking any predecessor manifest's historical entries.

## Existing authority and behavior

| Source | Grounded fact used by C05 |
| --- | --- |
| `Refactor.md`, C05 and §§3.3, 9.1–9.4 | Minimum height precedes cost; baseline C02 is sufficient with C03 off; cache includes semantics/context; memory-budget failure must be honest; switching is C06 |
| `include/crown/planner/search.hpp`, `src/planner/search_session.cpp` | Opaque VerifiedOptimum/checked upper and original binding; evidence cannot be synthesized from an aggregate |
| `include/crown/planner/oracle.hpp` | Editable certificate/result records are not replacement typed authority |
| `include/crown/planner/candidates.hpp`, `src/planner/candidates.cpp` | Immutable typed alternatives/snapshot; exact required height; finite retained family and real exhaustion; no provider progress in a snapshot |
| `src/planner/candidate_binding.hpp` | Complete injective P07 v2 Catalog/Query binding, arbitrary raw byte strings, bounded optional encoder seam; legacy encoding must stay unchanged |
| `include/crown/ir/model.hpp`, `tree.hpp`, `scalar.hpp` | All full source/tree field domains; Decimal internals are private, canonical public text is bounded; raw tree representation differs from structural key |
| `include/crown/planner/lower.hpp`, `src/planner/lower.cpp` | Independent structural admission, finite host ceilings, normalized replay, deterministic current layout/index sharing and full tree/ID-dependent physical identity |
| `include/crown/ir/physical.hpp` | Privately originated immutable complete PhysicalPlan and producer options; low-level height_status remains valid_upper_bound |
| `include/crown/storage/layout.hpp`, `src/storage/layout.cpp` | Layout token identity differs from descriptor equivalence; actual repeated-field equalities own storage |
| `include/crown/frontend/bind.hpp`, `normalize.hpp`; `src/frontend/bind.cpp`, `normalize.cpp` | Owned SQL source, physical aliases, parameters, predicates, constant/repeated outputs and finite replay limits are part of source semantics |
| `include/crown/io/normalization.hpp`, `src/io/normalization.cpp` | Full program replay and v1 grounding; mutable normalized IR is not admitted merely because it has a plausible core |
| `include/crown/io/identity.hpp`, `src/io/identity.cpp` | Canonical identity erases some representation details, has finite work; hashes cannot prove exact cache equality |
| `include/crown/io/physical.hpp`, `src/io/physical.cpp` | Complete versioned physical output/replay; no new cache import authority or format is needed |
| `include/crown/planner/ranking.hpp`, `src/planner/ranking.cpp` | Full retained-set structural admission before cost; exact N/W and Q terms; explicit fallback/resources; Q already lowers each candidate |
| `src/planner/ranking_detail.hpp`, `ranking_integer.cpp` | Exact bounded arithmetic and carried preparation Usage; initial Usage check and soft time semantics |
| `src/planner/ranking_payload.hpp`, `ranking_payload.cpp`; `docs/ranking_accounting.md` | Public component payload pre/post admission, Decimal/equality allowances and explicit allocator/temporary exclusions |
| `include/crown/runtime/ranking_evidence.hpp`, `src/runtime/ranking_evidence.cpp` | Actual owner capture; independent source/workload eligibility; current-only exact root census; revalidate has no caller budget/Usage |
| `include/crown/runtime/combined_statistics.hpp`, `src/runtime/combined_statistics.cpp` | Private actual-owner joint construction checks owner/epoch/plan/pending agreement |
| `include/crown/runtime/owner_statistics.hpp`, `workload_statistics.hpp` | State scope/availability, raw owner sequence, current versus prior interval, saturation and complete input denominator |
| `include/crown/runtime/physical.hpp`, `delta.hpp`, `session.hpp` | Actual owner interfaces; dropped versus stopped session and retained context/plan lifetime; single-writer boundary |
| `CMakeLists.txt`, `dependencies.lock.json` | Current graph: pure ranking separate from matching optional runtime bridges; active patched JSON lock and strict flags |
| `third_party/nlohmann/json.hpp`, original header, local patch/notice | One coherent exceptions-enabled header closure; allocation-free nonrecursive fallback cleanup is already required under persistent OOM |

The private CombinedCapture constructor already rejects inconsistent paired
owner/sequence/plan/pending inputs. C05 current selection additionally checks
the returned actual layer/scope and session metadata, and compares full source
identity rather than promoting that internal digest consistency check into
cache equality. It uses public immutable fields and actual factory origin;
no new user-settable provenance flag is needed.

## Proposed implementation map after review

| Proposed native destination | Responsibility/dependencies |
| --- | --- |
| `include/crown/planner/selection.hpp` | Pure request, explicit source, constraints, immutable Selection, bounded PlanCache and nonallocating attempt diagnostics |
| `src/planner/selection.cpp` | Full admission, C02 delegation, aggregate usage, constraint decision, bounded final lower and prepared publication transaction |
| `src/planner/selection_binding.cpp` | Exact full source/tree/options/family/evidence key and bounded full equality; no JSON DOM for key encoding |
| `src/planner/selection_cache.cpp` | Private deterministic FIFO, entry accounting, staged counters/evictions and no-throw commit |
| `src/planner/selection_detail.hpp` | Private shared preparation/transaction and scalar reason utilities; inaccessible as public authority |
| `include/crown/runtime/selection.hpp` | Actual Physical/Delta/Session overloads and private CurrentSelection owning the capture |
| `src/runtime/selection.cpp` | One fresh bounded actual capture, actual committed boundary/source checks, shared aggregate allowance and wrapper commit |
| `tests/unit/selection_*_test.cpp` | Concrete policy/constraint/key/freshness/resource/fault tests in ACCEPTANCE.md; exact file split decided when authored |
| `tests/examples/selection_usage.cpp` | Public pure, explicit as-of and actual-owner examples, compiled against production and testing variants |
| `docs/selection.md` | Truthful usage, cache/freshness/partial-family/units and resource documentation |

The initial pure implementation can call existing private C02 bounded payload
walkers and exact integer helpers where needed without changing their public
contracts or duplicating their arithmetic. Any refactor to share those helpers
must preserve old bytes/semantics and receive a separately reviewed source map;
no such refactor is authorized or performed by this preflight. New source-key
visitors must enumerate every normalized field rather than substituting existing
canonical identity hashes. Original P07 CandidateCache stays separate and unchanged.

## Proposed target direction

| Target | Public link direction | ABI variant |
| --- | --- | --- |
| `crown_selection` | `crown_ranking` → `crown_plan` → existing SQL/core dependencies | No runtime macro or report dependency |
| `crown_selection_runtime` | `crown_selection` + `crown_ranking_runtime` (which links production runtime) | Production only |
| `crown_selection_runtime_testing` | `crown_selection` + `crown_ranking_runtime_testing` | CROWN_RUNTIME_TESTING inherited consistently; BUILD_TESTING only |

Pure selection must neither include runtime/session headers nor link report,
runtime or CLI objects. The actual-owner bridge has no report dependency;
SessionStatisticsContext already resides on the runtime-only seam. No base
runtime/report source-list expansion is required for these opt-in bridges.
The current 14-unit runtime and 6-unit report graphs retain their direction.
All project C++ objects use the single active patched nlohmann header; parser C
reuse, if any, must match pinned configuration. Separate direct build recipes
and later native registration must name every source/object/macro/archive.

No C05 serialization schema, cache persistence, EXPLAIN optimality field, CLI
policy switch, deployment endpoint, background optimizer or C03 hook is required
to claim the proposed baseline. Public immutable accessors already provide exact
terms, chosen policy and reasons. An optional future report must not accept a
cached key or serialized diagnostic as proof. Native publication and matrix
work remain later tasks, after root accepts the design and excluded implementation.
