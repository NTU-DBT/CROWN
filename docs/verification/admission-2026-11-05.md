# F06 SQL admission verification packet, 2026-11-05

Historical F06 checkpoint. The subsequent typed layout/reference-storage
checkpoint and current fingerprints are in
[storage verification](storage-2026-11-05.md).

Input revision: uncommitted `master` worktree based on
`e369a623517723b3be3ea3e9806779f3c591e7f9`. F06 is verified at the declared
frontend/structural boundary. Current source/build/contract/fixture
fingerprints are in [admission-sources.sha256](admission-sources.sha256).
The full 78-card Refactor.md scope remains active. Physical lowering,
maintained SQL execution and R0/R1 release gates remain open.
All 377 source/build/contract/fixture checksums pass. Mutable handoff/ledger
and verification packets/manifests are excluded as at prior checkpoints.

## Acceptance audit

| Required artifact or behavior | Evidence |
| --- | --- |
| Structured admission result | `frontend/admission.hpp`, `src/frontend/admission.cpp`, `src/io/admission.cpp`, `sql-admission-v1.schema.json`, `admit-sql` and `admit-normalized`. Seven statuses retain stage/diagnostic information. Every report fixes its scope to frontend/structure and execution to `not_lowered`. |
| Parser versus semantic versus unsupported failures | SQL syntax/encoding/statement-boundary failures preserve parser codes. Name/ambiguity/type/literal/parameter errors remain semantic. Unsupported SQL/types/casts/bags/NULL policies preserve precise unsupported codes. Invalid AST/contracts remain internal errors. CLI malformed files/options/artifacts use stderr/exit 2, distinct from declared admission exit 1. |
| Cyclic body versus non-free-connex head | Complete bounded GYO evaluates H and H+F separately, with full witnesses and failed cores. A triangle with a full head still rejects as cyclic; the projected endpoint path rejects as non-free-connex. Synthetic head edges never add an input table. |
| Honest resource exhaustion | Shared recognition budget covers scope building and both reductions; exhaustion returns no partial class or route. Unit exact-budget/n−1 checks and zero parser/binding/normalization/recognition limits cover each stage. Legacy grounding has an independent host cap; stored unlimited cannot disable it. Legacy classify/GYO APIs retain unlimited behavior. |
| Supported SQL matrix | Machine-readable corpus contains 59 SQL cases across 57 feature groups. Expected statuses: 23 admitted, one non-free-connex, one cyclic, 21 unsupported, seven semantic errors, three syntax errors and three resource stops. All checks match the expected class/reason. Plain bags never become DISTINCT. |
| Independent structure and SQL checks | Fifty SQL-generated hypergraph/head families use literal spanning-tree/running-intersection enumeration for expected classes without calling GYO. Twenty-two manual answer checks and 20 applicable SQLite comparisons verify admitted programs through independent local-expression interpretation and A04. Full GYO witnesses are independently replayed. |
| Constant-bound head completeness | A concrete format-1 path retained its fixed output column as a free variable and was classified non-free-connex. Format 2 grounds the final class in every input and output: `Q(1,c):R(1,b),S(b,c)` now has H={{b},{b,c}}, F={c} and is admitted. Independent CQ/manual rows and physical last-support deletions agree. |
| Fixed classes preserve identity/supports | Explicit per-column guards cover every member/alias, fixed variables leave core scopes/projections, and outputs retain constants/order/repetition. Every mutable atom remains, including nullary inputs. Self-join supports stay separate and physical fan-out still commits together. |
| Version compatibility | V1 replay keeps its original geometry, IDs, fields and counters. Both frozen v1 artifacts validate unchanged. `upgrade-normalized` explicitly supports 1→2, rejects downgrades and preserves before/after SQL semantics. Admission grounds validated legacy input before classification. Plan/certificate bindings must be regenerated for changed core geometry. |
| Diagnostic examples and ownership | `docs/sql_admission.md` contains commands/status meanings and options. Ambiguous names preserve byte/Unicode coordinates. Global structural failures retain failed-core indices and source occurrence locations. Results own source/catalog/program/witnesses through copy/move. |

## Final matrix

| Configuration | Outcome | CTest time |
| --- | --- | --- |
| GCC 13.3 Debug | 23/23 pass | 13.09 s |
| GCC 13.3 Release | 23/23 pass | 3.13 s |
| ASan/UBSan including parser C | 23/23 pass | 95.28 s |
| Clang 18.1.3 C/C++ Debug | 23/23 pass | 10.98 s |
| Fresh source-only Release | 23/23 pass | 3.23 s |

The final clean configure/build/test took 149.59 s and removed its temporary
source/build tree. Final matrix logs include the additional legacy grounding
host-cap regression; earlier intermediate runs are not the final source
record. Sanitizers halt on errors and enable leak detection for project C++
and parser C. All previous direct-CQ, scalar/catalog, parser/binding,
normalization, schema/identity, independent GYO and exact-tree tests pass.

The admission runner also passes under `python -O`, using explicit checks
throughout. The optional JSON Schema audit passes 12 schema meta-checks,
26 normalized artifacts (17 current-v2 successes, seven v1 diagnostics, two
frozen v1 successes), 19 identity artifacts and all 59 admission artifacts.
Schema validation complements native replay and independent witness checking.

```sh
cmake --build --preset debug --parallel 2
ctest --preset debug
cmake --build --preset release --parallel 2
ctest --preset release
cmake --build --preset sanitize --parallel 2
ctest --preset sanitize
cmake --build build/clang-debug --parallel 2
ctest --test-dir build/clang-debug --output-on-failure
python3 -O tests/integration/admission.py build/debug/crown .
python3 tools/verify_schemas.py build/debug/crown
python3 tools/verify_clean_build.py --log build/verification/admission-clean-source.log
```

Full outputs are under ignored `build/verification/admission-*.log`. The clean
snapshot contains source, fixtures, schemas, build/tool inputs and pinned
dependencies, with no prior build/cache/VCS/legacy tree. Fingerprints exclude
verification packets/manifests and mutable handoff/ledger files as before.

## Boundaries and next work

The admitted class is the grounded normalized equality CQ plus supported
local adapters and the declared SQL wrapper. Recognition does not prove
general SQL equivalence or predicate implication, choose/certify a height,
lower a physical plan or install a runtime. A contradiction can use the
constant-empty route while its actual shape remains cyclic. Unsupported
features are never discarded to reach that route. Nullable source policy,
row bags, arithmetic/functions, richer SQL and other extensions remain
rejected as documented.

V2 fixes the demonstrated equality-constant geometry gap, with explicit
compatibility rules rather than changing v1 replay. Host limits are abstract
work/expression/depth caps, not a wall-time/memory guarantee. Artifact replay
costs are separate from stored producer work counters. Admission JSON is a
report, not an untrusted physical-plan import format.

Continue with S01/S02 typed layouts/projection/storage foundations and the
generic physical lowering/runtime dependencies. A02 provenance/license
disposition, P04/P06 partial features and G2/V02 independent review remain
open. Completing F01–F06 does not close release gates or the full refactor.
