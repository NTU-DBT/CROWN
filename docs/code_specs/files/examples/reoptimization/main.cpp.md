# `examples/reoptimization/main.cpp` — block usage map

[Source](../../../../../examples/reoptimization/main.cpp) · [Source index](../../../README.md) · [Subsystem contracts](../../../subsystem_contracts.md) · [Reviewed primitives](../../../primitives.md)

Demonstrate a concrete public workflow and executable invocation using installed/native CROWN interfaces.

Snapshot SHA-256: `e56c7325149b907fb03c23de41b8915bb68507d5db51db61d55e45be4f743bda`. 97 lines partitioned into 11 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [examples](../../../subsystem_contracts.md#examples). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/cli.md](../../../../cli.md), [docs/native_build.md](../../../../native_build.md), [docs/measurement.md](../../../../measurement.md), [docs/ranking_evaluation.md](../../../../ranking_evaluation.md), [docs/reoptimization.md](../../../../reoptimization.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–12](../../../../../examples/reoptimization/main.cpp#L1) | Imports dependencies; declares namespace scope; declares aliases. |  · [reviewed contract](#b0001) |
| [B0002 · 13–13](../../../../../examples/reoptimization/main.cpp#L13) | Callable definition: void check(bool value,const char* message) | calls std::runtime_error; guard void check(bool value,const char* message) {if(!value)throw std::runtime_error(message);} · [reviewed contract](#b0002) |
| [B0003 · 14–27](../../../../../examples/reoptimization/main.cpp#L14) | Callable definition: planner::CandidateSnapshot candidates(const Catalog& catalog,const Query& query) | calls planner::ExactSearch::create, advance, optimum, check; guard else check(next.stopped_for==planner::StopReason::quantum_work,"example exact search exhausted its …; returns provider.snapshot(); 2 loop sites · [reviewed contract](#b0003) |
| [B0004 · 28–34](../../../../../examples/reoptimization/main.cpp#L28) | Callable definition: PhysicalOptions physical_options(bool indexed) | calls ; returns value · [reviewed contract](#b0004) |
| [B0005 · 35–38](../../../../../examples/reoptimization/main.cpp#L35) | Callable definition: SessionGenerationOptions generation_options() | calls std::copy, begin, end; returns value · [reviewed contract](#b0005) |
| [B0006 · 39–42](../../../../../examples/reoptimization/main.cpp#L39) | Callable definition: SessionLocalSinkOptions sink_options() | calls std::copy, begin, end; returns value · [reviewed contract](#b0006) |
| [B0007 · 43–47](../../../../../examples/reoptimization/main.cpp#L43) | Callable definition: void update(QuerySession& session,std::uint64_t sequence,TableId table,SetOperation operation,Row row) | calls batch, std::move, check, enqueue; guard check(session.enqueue(batch)==io::Admission::accepted && session.begin_next(),"example update was n…; 1 loop sites · [reviewed contract](#b0007) |
| [B0008 · 48–48](../../../../../examples/reoptimization/main.cpp#L48) | Explanatory comments or spacing. | source comment (unverified): // Fixed data, IDs and forecast values are demo inputs; all native admission still runs. · [reviewed contract](#b0008) |
| [B0009 · 49–92](../../../../../examples/reoptimization/main.cpp#L49) | Callable definition: void execute(std::string_view action,const std::filesystem::path& directory,bool indexed) | calls frontend::admit_sql, check, candidates, candidate_count; guard check(admitted.status==frontend::AdmissionStatus::admitted,"example SQL was not admitted");const au…; growth insert; 2 loop sites; source comment (unverified): // Fixed data, IDs and forecast values are demo inputs; all native admission still runs. · [reviewed contract](#b0009) |
| [B0010 · 93–93](../../../../../examples/reoptimization/main.cpp#L93) | Closes surrounding scope/type. | source comment (unverified): // namespace · [reviewed contract](#b0010) |
| [B0011 · 94–97](../../../../../examples/reoptimization/main.cpp#L94) | Callable definition: int main(int argc,char** argv) | calls check, execute, flush, what; guard try {check(argc==4,"usage: crown_reoptimization run\|resume DIRECTORY reference\|indexed");const std:…; returns std::cout?0:1; 1 · [reviewed contract](#b0011) |

## B0001

[Lines 1–12](../../../../../examples/reoptimization/main.cpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
#include "crown/frontend/admission.hpp"
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Import the public APIs and local host utilities used by this standalone client. |
| inputs / outputs | Public headers, standard/POSIX declarations and namespace/type aliases; no execution request. |
| invariants | Aliases do not create runtime owners or proof authority. Measurement/ranking collectors use Linux/POSIX facilities where declared. |
| ownership | Declarations only; actual owners and buffers are created inside helpers/run/main. |
| failure | Compilation requires the installed public target closure and a supporting compiler/platform. |
| cost | No per-event runtime action; included definitions and instantiated APIs determine compiled dependencies. |
| Design | [examples/reoptimization/main.cpp](../../../../../examples/reoptimization/main.cpp), [cmake/CrownInstall.cmake](../../../../../cmake/CrownInstall.cmake), [docs/native_build.md](../../../../native_build.md), [docs/reoptimization.md](../../../../reoptimization.md), [docs/selection.md](../../../../selection.md), [docs/candidate_alternatives.md](../../../../candidate_alternatives.md) |

## B0002

[Lines 13–13](../../../../../examples/reoptimization/main.cpp#L13); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void check(bool value,const char* message)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Fail an explicit demo precondition/assertion. |
| inputs / outputs | Boolean and borrowed static message; returns on success. |
| invariants | No check turns demo inputs or JSON into native authority. |
| ownership | Does not retain message; runtime_error owns failure text. |
| failure | False throws runtime_error to main; no local recovery. |
| cost | Fixed successful branch; failure exception may allocate. |
| Design | [examples/reoptimization/main.cpp](../../../../../examples/reoptimization/main.cpp), [docs/reoptimization.md](../../../../reoptimization.md), [docs/selection.md](../../../../selection.md), [docs/candidate_alternatives.md](../../../../candidate_alternatives.md) |

## B0003

[Lines 14–27](../../../../../examples/reoptimization/main.cpp#L14); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
planner::CandidateSnapshot candidates(const Catalog& catalog,const Query& query)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Prove the demo query optimum and exhaust its declared checked candidate family. |
| inputs / outputs | Borrowed catalog/query; independently owned search/provider; returns a retained CandidateSnapshot only on exhausted enumeration. |
| invariants | Each phase has &lt;=2000 calls of work quantum 10000 and underlying finite limits. Family exhaustion is not every physical implementation or global cost optimality. |
| ownership | Search/provider own admission copies/continuations. VerifiedOptimum/candidate handles share actual private Data; snapshot admission copies handle/event vectors before provider destruction. |
| failure | Unexpected/total/depth/allocation stops and call-bound exhaustion throw; snapshot admission itself can allocate/fail. |
| cost | Exact proof plus normal-form candidate enumeration; explicit snapshot construction allocates its vectors, later snapshot copies retain shared Data. |
| Design | [examples/reoptimization/main.cpp](../../../../../examples/reoptimization/main.cpp), [include/crown/planner/search.hpp](../../../../../include/crown/planner/search.hpp), [include/crown/planner/candidates.hpp](../../../../../include/crown/planner/candidates.hpp), [src/planner/candidates.cpp](../../../../../src/planner/candidates.cpp), [docs/reoptimization.md](../../../../reoptimization.md), [docs/selection.md](../../../../selection.md), [docs/candidate_alternatives.md](../../../../candidate_alternatives.md) |

## B0004

[Lines 28–34](../../../../../examples/reoptimization/main.cpp#L28); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
PhysicalOptions physical_options(bool indexed)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Choose reference defaults or the explicit indexed fixture capacities/grants. |
| inputs / outputs | Boolean backend choice; returns PhysicalOptions with optional fixed IndexedBackendSpec. |
| invariants | The numeric spec is a finite demonstration configuration; it is not an observed memory/time estimate or universal workload sizing. |
| ownership | Owns inline option values; native admission later owns/charges actual indexed storage. |
| failure | Helper does not validate all downstream capacity/budget needs; lowering/admission can reject them. |
| cost | Fixed option construction; actual directory/block allocation and indexed work occur during runtime admission/use. |
| Design | [examples/reoptimization/main.cpp](../../../../../examples/reoptimization/main.cpp), [include/crown/storage/backend.hpp](../../../../../include/crown/storage/backend.hpp), [include/crown/planner/lower.hpp](../../../../../include/crown/planner/lower.hpp), [include/crown/ir/physical.hpp](../../../../../include/crown/ir/physical.hpp), [docs/reoptimization.md](../../../../reoptimization.md), [docs/selection.md](../../../../selection.md), [docs/candidate_alternatives.md](../../../../candidate_alternatives.md) |

## B0005

[Lines 35–38](../../../../../examples/reoptimization/main.cpp#L35); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
SessionGenerationOptions generation_options()
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Declare reproducible demo journal identity and retained-history bound. |
| inputs / outputs | No input; returns options with the literal 32-character query ID and retained_generations=3. |
| invariants | Use a separate directory per backend/run; fixed IDs are example inputs, not fresh identity generation. |
| ownership | Returned options own fixed arrays/scalars; no borrowed string remains. |
| failure | No IO or semantic generation operation here; API validation occurs at use. |
| cost | Fixed 32-byte copy; no generation scan/allocation. |
| Design | [examples/reoptimization/main.cpp](../../../../../examples/reoptimization/main.cpp), [include/crown/runtime/session_generation.hpp](../../../../../include/crown/runtime/session_generation.hpp), [docs/reoptimization.md](../../../../reoptimization.md), [docs/selection.md](../../../../selection.md), [docs/candidate_alternatives.md](../../../../candidate_alternatives.md) |

## B0006

[Lines 39–42](../../../../../examples/reoptimization/main.cpp#L39); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
SessionLocalSinkOptions sink_options()
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Declare reproducible demo sink identity and retained epoch bound. |
| inputs / outputs | No input; returns fixed sink_id and file.epochs=64. |
| invariants | The immutable origin sink identity persists across switching/rotation/recovery; this helper never rewrites an existing header. |
| ownership | Inline options own copied bytes; attached session later owns durable sink. |
| failure | No IO here; create/restore/delivery enforce actual sink limits. |
| cost | Fixed option/32-byte copy. |
| Design | [examples/reoptimization/main.cpp](../../../../../examples/reoptimization/main.cpp), [include/crown/runtime/session_local_sink.hpp](../../../../../include/crown/runtime/session_local_sink.hpp), [docs/reoptimization.md](../../../../reoptimization.md), [docs/selection.md](../../../../selection.md), [docs/candidate_alternatives.md](../../../../candidate_alternatives.md) |

## B0007

[Lines 43–47](../../../../../examples/reoptimization/main.cpp#L43); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void update(QuerySession& session,std::uint64_t sequence,TableId table,SetOperation operation,Row row)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Submit one typed fixture row, commit it and verify whole-epoch local delivery. |
| inputs / outputs | Running session and sequence/table/op/owning Row; source name wire and offset sequence*10; current callers use sequences 1..10. |
| invariants | Requires accepted batch and successful begin; preserves duplicate-insert no-op physical epochs and delivery. This private fixture multiplier is safe only for its small declared calls. |
| ownership | Row moves into the ordinary TransportBatch DTO; accepted enqueue imports native queue storage and consumes batch according to its API. Session owns pending/output state. |
| failure | Admission/preparation/commit/delivery/check errors propagate; committed physical input is not rolled back after later delivery failure. |
| cost | Ordinary batch/row construction plus native validation/import, prepare, commit and durable sink append, including empty output epochs. |
| Design | [examples/reoptimization/main.cpp](../../../../../examples/reoptimization/main.cpp), [include/crown/runtime/session.hpp](../../../../../include/crown/runtime/session.hpp), [src/runtime/session.cpp](../../../../../src/runtime/session.cpp), [include/crown/io/batch.hpp](../../../../../include/crown/io/batch.hpp), [include/crown/runtime/session_local_sink.hpp](../../../../../include/crown/runtime/session_local_sink.hpp), [docs/reoptimization.md](../../../../reoptimization.md), [docs/selection.md](../../../../selection.md), [docs/candidate_alternatives.md](../../../../candidate_alternatives.md) |

## B0008

[Lines 48–48](../../../../../examples/reoptimization/main.cpp#L48); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L48-L48:sha256:08783f0aa178c2f3d9d61cc0c8c988e7c964a696da8c27494e9dee310ea5ca18
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Explain the adjacent source contract: Fixed data, IDs and forecast values are demo inputs; all native admission still runs. |
| inputs / outputs | Human-readable source note in; no executable output or checked receipt. |
| invariants | This comment states context or a limitation. It does not itself enforce or prove the described behavior; use the adjacent implementation and its scoped contract. |
| ownership | Source text only; no object or resource lifetime is created. |
| failure | No runtime failure path in this comment; source encoding/comment syntax still belongs to compilation. |
| cost | No runtime operations from the comment. Any work described in the note belongs to the adjacent operation. |
| Design | [examples/reoptimization/main.cpp](../../../../../examples/reoptimization/main.cpp), [docs/reoptimization.md](../../../../reoptimization.md), [docs/code_review.md](../../../../code_review.md) |

## B0009

[Lines 49–92](../../../../../examples/reoptimization/main.cpp#L49); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void execute(std::string_view action,const std::filesystem::path& directory,bool indexed)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Run the fixed SQL EXISTS switching fixture or recover it in a separate process. |
| inputs / outputs | run\|resume, state directory and backend; outputs actual sequence/sink/generation/EXISTS/source-offset JSON. |
| invariants | SQL/catalog/initial rows, grants, IDs and forecasts are demo inputs. Real admission, checked candidates, measured selection, exact native verification and durable-root recovery still execute. |
| ownership | Unique session owns its original native account and lock/queue/sink; compiler artifact is a separate move-only owner; reports are ordinary JSON DTOs. |
| failure | Any failing check/API/filesystem action propagates to main. Earlier durable changes persist; this function performs no rollback on report or retirement failure. |
| cost | Exact search, full family, startup/import, nine or one updates, capture/ranking/rebuild/equivalence/compiler export/publication or locked replay; no performance claim. |
| Design | [examples/reoptimization/main.cpp](../../../../../examples/reoptimization/main.cpp), [include/crown/runtime/session.hpp](../../../../../include/crown/runtime/session.hpp), [src/runtime/session.cpp](../../../../../src/runtime/session.cpp), [include/crown/planner/search.hpp](../../../../../include/crown/planner/search.hpp), [include/crown/planner/candidates.hpp](../../../../../include/crown/planner/candidates.hpp), [src/planner/candidates.cpp](../../../../../src/planner/candidates.cpp), [include/crown/io/compiler_plan_artifact.hpp](../../../../../include/crown/io/compiler_plan_artifact.hpp), [include/crown/runtime/selection.hpp](../../../../../include/crown/runtime/selection.hpp), [docs/reoptimization.md](../../../../reoptimization.md), [docs/selection.md](../../../../selection.md), [docs/candidate_alternatives.md](../../../../candidate_alternatives.md) |

```text
const Catalog catalog{41
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Admit the fixed three-relation SQL EXISTS source and select a native-root starting tree. |
| inputs / outputs | Catalog R(x), S(x,y), T(y), version 41; actual SQL admission and checked candidate family; lower first candidate with native root when found. |
| invariants | original_index defaults to 0 if no native-root member is found. Actual later switch/shape checks validate this particular fixture outcome. |
| ownership | Compiler catalog/SQL objects own ordinary data; family owns shared checked payloads; PhysicalPlan retains lowered metadata. |
| failure | Admission/search/candidate/lowering failures abort before state creation. |
| cost | Exact proof/enumeration plus one family scan and checked lowering. |
| Design | [examples/reoptimization/main.cpp](../../../../../examples/reoptimization/main.cpp), [include/crown/planner/search.hpp](../../../../../include/crown/planner/search.hpp), [include/crown/planner/candidates.hpp](../../../../../include/crown/planner/candidates.hpp), [src/planner/candidates.cpp](../../../../../src/planner/candidates.cpp), [include/crown/planner/lower.hpp](../../../../../include/crown/planner/lower.hpp), [include/crown/ir/physical.hpp](../../../../../include/crown/ir/physical.hpp), [docs/reoptimization.md](../../../../reoptimization.md), [docs/selection.md](../../../../selection.md), [docs/candidate_alternatives.md](../../../../candidate_alternatives.md) |

```text
if(action=="run")
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Initialize the true EXISTS database and durable typed session. |
| inputs / outputs | Creates directory, loads x/(x,y)/y, delta mode and 32 MiB native grant; starts session, creates root and local sink, enables counters with detail_budget=0. |
| invariants | Initial SQL result is true. No-op physical inserts still commit and are included in workload weights and durable output epochs. |
| ownership | Ordinary initial database is imported into the original native account; session exclusively owns typed queue, delta state, journal/root and sink. |
| failure | Directory/create/import/journal/sink/configuration failure propagates; any already published files retain native outcome rules. |
| cost | Initial row import/live setup and durable creation plus eight typed duplicate inserts/deliveries. |
| Design | [examples/reoptimization/main.cpp](../../../../../examples/reoptimization/main.cpp), [include/crown/runtime/session.hpp](../../../../../include/crown/runtime/session.hpp), [src/runtime/session.cpp](../../../../../src/runtime/session.cpp), [docs/reoptimization.md](../../../../reoptimization.md), [docs/selection.md](../../../../selection.md), [docs/candidate_alternatives.md](../../../../candidate_alternatives.md) |

```text
planner::selection::Request request;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Capture actual current evidence and perform measured C05 selection. |
| inputs / outputs | Checked family, current session CompiledProgram basis and require_evidence request; demands complete selection result. |
| invariants | select_for_reoptimization measures capture/ranking/lowering/cache/temporary teardown; its C02 scores remain unitless. |
| ownership | Source copies a real CompiledProgram descriptor. CurrentSelection retains actual shared evidence/selection, not mutable runtime rows or a writer lease. |
| failure | Missing evidence, budget/staleness/selection stop yields failed fixture check before migration. |
| cost | Cold statistics/population capture, ranking and lowering scans/allocations; original-account execution context retained. |
| Design | [examples/reoptimization/main.cpp](../../../../../examples/reoptimization/main.cpp), [include/crown/runtime/selection.hpp](../../../../../include/crown/runtime/selection.hpp), [src/runtime/selection.cpp](../../../../../src/runtime/selection.cpp), [include/crown/planner/ranking.hpp](../../../../../include/crown/planner/ranking.hpp), [include/crown/planner/selection.hpp](../../../../../include/crown/planner/selection.hpp), [include/crown/runtime/ranking_evidence.hpp](../../../../../include/crown/runtime/ranking_evidence.hpp), [docs/reoptimization.md](../../../../reoptimization.md), [docs/selection.md](../../../../selection.md), [docs/candidate_alternatives.md](../../../../candidate_alternatives.md) |

```text
reoptimization::Options migration;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Declare forecast assumptions and verify a paused native migration at the barrier. |
| inputs / outputs | Forecast {1000000,1,1000000}, current measured choice; pause, begin migration, request barrier, advance with quantum 100000. |
| invariants | Forecast is caller prediction, never measured C02 cost. verified means exact same-epoch source/result equality and eligibility; it does not publish the plan. |
| ownership | Original session/account retain both owners and funded staging/equivalence resources until switch/cancel. No exported source-row replay is supplied. |
| failure | Stale/current-owner checks, rebuild, backlog, work/memory or forecast failure propagate/return nonverified and fail the fixture; original native failure rules remain. |
| cost | Snapshot/rebuild, catch-up, exact comparison and measured preparation with simultaneous original/target memory. |
| Design | [examples/reoptimization/main.cpp](../../../../../examples/reoptimization/main.cpp), [include/crown/runtime/reoptimization.hpp](../../../../../include/crown/runtime/reoptimization.hpp), [include/crown/runtime/session_reoptimization.hpp](../../../../../include/crown/runtime/session_reoptimization.hpp), [include/crown/runtime/session.hpp](../../../../../include/crown/runtime/session.hpp), [src/runtime/session.cpp](../../../../../src/runtime/session.cpp), [docs/reoptimization.md](../../../../reoptimization.md), [docs/selection.md](../../../../selection.md), [docs/candidate_alternatives.md](../../../../candidate_alternatives.md) |

```text
const auto compiler=resource::MemoryAccount::create
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Prepare the explicit compiler boundary and durably publish the verified target. |
| inputs / outputs | Separate 32 MiB compiler account and selected native plan; CompilerPlanArtifact::prepare then publish_reoptimization. |
| invariants | Artifact must match verified target source/physical identities. Complete publication preserves pause and must change the physical digest in this fixture. |
| ownership | Artifact uniquely owns compiler-account executable metadata/opaque bytes. Native publication imports into the original receiving account; standard export DTO temporaries are outside it. |
| failure | Compiler/prepublication failure preserves native retry semantics. Ambiguous/selected root outcomes remain authoritative; no caller root rollback is attempted. |
| cost | Native-to-compiler DTO export, canonical re-lowering/serialization/teardown and funded file/publication preparation; measured selection/compiler costs are reported. |
| Design | [examples/reoptimization/main.cpp](../../../../../examples/reoptimization/main.cpp), [include/crown/io/compiler_plan_artifact.hpp](../../../../../include/crown/io/compiler_plan_artifact.hpp), [src/io/compiler_plan_artifact.cpp](../../../../../src/io/compiler_plan_artifact.cpp), [include/crown/runtime/session.hpp](../../../../../include/crown/runtime/session.hpp), [src/runtime/session.cpp](../../../../../src/runtime/session.cpp), [docs/reoptimization.md](../../../../reoptimization.md), [docs/selection.md](../../../../selection.md), [docs/candidate_alternatives.md](../../../../candidate_alternatives.md) |

```text
session->start();update(*session,9
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Exercise the switched plan and retire old generation history. |
| inputs / outputs | Resume after paused switch; erase S(x,y) at sequence 9, deliver false EXISTS epoch, rotate and retire history. |
| invariants | Normal output uses immutable original sink lineage; private migration output is not delivered. Retirement follows native verified lineage/dependency checks. |
| ownership | Session keeps source/queue/account/sink identity while current runtime owner changes; generation holder owns selected descriptor. |
| failure | Update, rotation or retirement failure propagates after any earlier durable selection; cleanup is not an atomic undo of the run. |
| cost | One native/durable update, full checkpoint rotation and validated historical-file retirement. |
| Design | [examples/reoptimization/main.cpp](../../../../../examples/reoptimization/main.cpp), [include/crown/runtime/session.hpp](../../../../../include/crown/runtime/session.hpp), [src/runtime/session.cpp](../../../../../src/runtime/session.cpp), [docs/reoptimization.md](../../../../reoptimization.md), [docs/selection.md](../../../../selection.md), [docs/candidate_alternatives.md](../../../../candidate_alternatives.md) |

```text
check(action=="resume"
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Recover the selected compiler artifact under the same root lock. |
| inputs / outputs | Existing directory/backend/source; acquire LockedGenerationRecovery, replay borrowed artifact on explicit compiler account, consume lock into sink-aware restore, update sequence 10. |
| invariants | Expected original program identifies source; the selected durable descriptor chooses the physical plan. Retain lock across replay and admission before tail repair. |
| ownership | Locked package uniquely owns lock/receiving context; artifact bytes borrow it until replay returns. std::move consumes package; restored session retains lock and imported metadata. |
| failure | Bad action/source/binding/artifact, receiving allocation or sink-prefix rejection aborts native recovery; native library alone decides permitted repair/outcome. |
| cost | Source/compiler preparation, descriptor read/hash/replay, receiving-account native admission/WAL-sink checks and one delivered update. |
| Design | [examples/reoptimization/main.cpp](../../../../../examples/reoptimization/main.cpp), [include/crown/runtime/session.hpp](../../../../../include/crown/runtime/session.hpp), [src/runtime/session.cpp](../../../../../src/runtime/session.cpp), [include/crown/runtime/session_generation.hpp](../../../../../include/crown/runtime/session_generation.hpp), [include/crown/io/compiler_plan_artifact.hpp](../../../../../include/crown/io/compiler_plan_artifact.hpp), [docs/reoptimization.md](../../../../reoptimization.md), [docs/selection.md](../../../../selection.md), [docs/candidate_alternatives.md](../../../../candidate_alternatives.md) |

```text
const auto snapshot=session->snapshot();
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Inspect the committed fixture result and publish a diagnostic report. |
| inputs / outputs | Owning snapshot must have one one-column Boolean row; reads generation selection, verified sink frontier, immutable origin and accepted wire offset. |
| invariants | These diagnostics are observations, not root/sink receipts or authorization for manual deletion. |
| ownership | Snapshot rows retain funded native collection/payload; exported progress/report objects own ordinary copies. Immediate values() reads borrow the snapshot tuple. |
| failure | Snapshot bound/shape/type/key/export failure reaches main after durable effects; final ostream state is not checked explicitly. |
| cost | Snapshot traversal and ordinary JSON/string export/dump plus generation/sink state copies. |
| Design | [examples/reoptimization/main.cpp](../../../../../examples/reoptimization/main.cpp), [include/crown/runtime/session.hpp](../../../../../include/crown/runtime/session.hpp), [src/runtime/session.cpp](../../../../../src/runtime/session.cpp), [include/crown/storage/layout.hpp](../../../../../include/crown/storage/layout.hpp), [docs/reoptimization.md](../../../../reoptimization.md), [docs/selection.md](../../../../selection.md), [docs/candidate_alternatives.md](../../../../candidate_alternatives.md) |

## B0010

[Lines 93–93](../../../../../examples/reoptimization/main.cpp#L93); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
} // namespace
int main
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Close private helper scope before the process entry point. |
| inputs / outputs | Ends the unnamed namespace; the following main has global linkage. |
| invariants | No control-flow, cleanup or authority transition occurs at this brace. |
| ownership | Namespace scope does not extend any automatic object lifetime. |
| failure | No execution or failure path. |
| cost | No runtime work or allocation. |
| Design | [examples/reoptimization/main.cpp](../../../../../examples/reoptimization/main.cpp), [docs/reoptimization.md](../../../../reoptimization.md), [docs/selection.md](../../../../selection.md), [docs/candidate_alternatives.md](../../../../candidate_alternatives.md) |

## B0011

[Lines 94–97](../../../../../examples/reoptimization/main.cpp#L94); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
int main(int argc,char** argv)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Validate fixture CLI and contain its process-level failures. |
| inputs / outputs | Exactly action DIRECTORY reference\|indexed; invoke execute, explicitly flush the final report and return 0 only with a healthy stdout stream. |
| invariants | Backend is validated before execute; run/resume is enforced there. Output failure can occur after durable commits and does not undo that prefix. |
| ownership | argv string_view borrows main arguments; filesystem path conversion owns its path; execute owns runtime resources. |
| failure | Existing std::exception boundary prints what() and returns1. A failed final stdout flush returns1 silently; no extra catch, retry or rollback is introduced. |
| cost | Fixed dispatch and one final report flush plus execute; no new native maintenance work. |
| Design | [examples/reoptimization/main.cpp](../../../../../examples/reoptimization/main.cpp), [tests/integration/installed_reoptimization.py](../../../../../tests/integration/installed_reoptimization.py), [docs/reoptimization.md](../../../../reoptimization.md), [docs/selection.md](../../../../selection.md), [docs/candidate_alternatives.md](../../../../candidate_alternatives.md) |
