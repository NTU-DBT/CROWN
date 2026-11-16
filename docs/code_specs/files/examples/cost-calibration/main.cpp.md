# `examples/cost-calibration/main.cpp` — block usage map

[Source](../../../../../examples/cost-calibration/main.cpp) · [Source index](../../../README.md) · [Subsystem contracts](../../../subsystem_contracts.md) · [Reviewed primitives](../../../primitives.md)

Demonstrate a concrete public workflow and executable invocation using installed/native CROWN interfaces.

Snapshot SHA-256: `e0939f81fda7105af62a51714135c653811443058674b392e751c39738b14c38`. 161 lines partitioned into 10 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [examples](../../../subsystem_contracts.md#examples). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/cli.md](../../../../cli.md), [docs/native_build.md](../../../../native_build.md), [docs/measurement.md](../../../../measurement.md), [docs/ranking_evaluation.md](../../../../ranking_evaluation.md), [docs/reoptimization.md](../../../../reoptimization.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–20](../../../../../examples/cost-calibration/main.cpp#L1) | Imports dependencies; declares namespace scope; declares aliases; declares values/defaults or compile-time conditions. |  · [reviewed contract](#b0001) |
| [B0002 · 21–21](../../../../../examples/cost-calibration/main.cpp#L21) | Callable definition: void require(bool value,std::string_view message) | calls Error, std::string; guard void require(bool value,std::string_view message){if(!value)throw Error("calibration_failed",std::s… · [reviewed contract](#b0002) |
| [B0003 · 22–26](../../../../../examples/cost-calibration/main.cpp#L22) | Callable definition: std::string read(const char* path,std::size_t limit) | calls file, require, bool, gcount; guard std::ifstream file(path,std::ios::binary);require(bool(file),"cannot open input file");std::string …; returns result; 1 loop sites · [reviewed contract](#b0003) |
| [B0004 · 27–30](../../../../../examples/cost-calibration/main.cpp#L27) | Callable definition: U64 number(const char* text,U64 minimum,U64 maximum) | calls value, std::from_chars, data, size; guard require(parsed.ec==std::errc{} && parsed.ptr==value.data()+value.size() && result&gt;=minimum && resul…; returns result · [reviewed contract](#b0004) |
| [B0005 · 31–33](../../../../../examples/cost-calibration/main.cpp#L31) | Callable definition: U64 elapsed(Clock::time_point begin,Clock::time_point end) | calls count, require; guard const auto value=std::chrono::duration_cast&lt;std::chrono::nanoseconds&gt;(end-begin).count();require(va…; returns static_cast&lt;U64&gt;(value) · [reviewed contract](#b0005) |
| [B0006 · 34–44](../../../../../examples/cost-calibration/main.cpp#L34) | Callable definition: planner::CandidateSnapshot candidates(const frontend::NormalizedSql& normalized,std::size_t count) | calls planner::ExactSearch::create, optimum, advance, require; guard for(std::size_t i=0;i&lt;10000 && !exact.optimum();++i){const auto progress=exact.advance({1000,{}});r…; returns provider.snapshot(); 2 loop sites · [reviewed contract](#b0006) |
| [B0007 · 45–48](../../../../../examples/cost-calibration/main.cpp#L45) | Callable definition: io::Json ratio(const std::optional&lt;model::Ratio&gt;& value) | calls ; returns nullptr; {{@ ,value-&gt;numerator},{@ ,value-&gt;denominator}} · [reviewed contract](#b0007) |
| [B0008 · 49–159](../../../../../examples/cost-calibration/main.cpp#L49) | Callable definition: int run(int argc,char** argv) | calls require, number, io::read_catalog, read; guard require(argc&gt;=4 && argc&lt;=7,"usage: crown_cost_calibrate QUERY.sql CATALOG.json INPUT.jsonl \[EVENTS&lt;…; returns std::cout?0:1; growth make_unique, push_back; 10 loop sites; source comment (unverified): // This timer includes owning output temporaries; JSON encoding and sinks are absent. · [reviewed contract](#b0008) |
| [B0009 · 160–160](../../../../../examples/cost-calibration/main.cpp#L160) | Closes surrounding scope/type. |  · [reviewed contract](#b0009) |
| [B0010 · 161–161](../../../../../examples/cost-calibration/main.cpp#L161) | Callable definition: int main(int argc,char** argv) | calls run, what; returns run(argc,argv); 1 · [reviewed contract](#b0010) |

## B0001

[Lines 1–20](../../../../../examples/cost-calibration/main.cpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
#include <crown/api/error.hpp>
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Import the public APIs and local host utilities used by this standalone client. |
| inputs / outputs | Public headers, standard/POSIX declarations and namespace/type aliases; no execution request. |
| invariants | Aliases do not create runtime owners or proof authority. Measurement/ranking collectors use Linux/POSIX facilities where declared. |
| ownership | Declarations only; actual owners and buffers are created inside helpers/run/main. |
| failure | Compilation requires the installed public target closure and a supporting compiler/platform. |
| cost | No per-event runtime action; included definitions and instantiated APIs determine compiled dependencies. |
| Design | [examples/cost-calibration/main.cpp](../../../../../examples/cost-calibration/main.cpp), [cmake/CrownInstall.cmake](../../../../../cmake/CrownInstall.cmake), [docs/native_build.md](../../../../native_build.md), [docs/maintenance_cost.md](../../../../maintenance_cost.md), [docs/candidate_alternatives.md](../../../../candidate_alternatives.md) |

## B0002

[Lines 21–21](../../../../../examples/cost-calibration/main.cpp#L21); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void require(bool value,std::string_view message)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Enforce explicit calibration input/counter/model conditions. |
| inputs / outputs | Boolean and borrowed message; success returns, false creates calibration_failed Error. |
| invariants | No condition upgrades fitted assumptions into native facts or suppresses unavailable coefficients. |
| ownership | Message is copied into Error only on failure. |
| failure | False throws to main; error allocation can fail. |
| cost | Fixed success branch. |
| Design | [examples/cost-calibration/main.cpp](../../../../../examples/cost-calibration/main.cpp), [include/crown/api/error.hpp](../../../../../include/crown/api/error.hpp), [docs/maintenance_cost.md](../../../../maintenance_cost.md), [docs/candidate_alternatives.md](../../../../candidate_alternatives.md) |

## B0003

[Lines 22–26](../../../../../examples/cost-calibration/main.cpp#L22); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::string read(const char* path,std::size_t limit)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Read a bounded compiler/input file into ordinary memory. |
| inputs / outputs | Borrowed path and ceiling; returns binary std::string. |
| invariants | Accepted size remains &lt;=limit; no query account/RSS guarantee. |
| ownership | Local stream closes; returned string owns bytes, including the complete buffered JSONL trace. |
| failure | Open/read/limit errors become calibration_failed; host string growth may throw. |
| cost | Linear 4096-byte-block read/copy and string capacity growth. |
| Design | [examples/cost-calibration/main.cpp](../../../../../examples/cost-calibration/main.cpp), [docs/maintenance_cost.md](../../../../maintenance_cost.md), [docs/candidate_alternatives.md](../../../../candidate_alternatives.md) |

## B0004

[Lines 27–30](../../../../../examples/cost-calibration/main.cpp#L27); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
U64 number(const char* text,U64 minimum,U64 maximum)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Parse a fully consumed bounded unsigned CLI argument. |
| inputs / outputs | Borrowed NUL-terminated argument and inclusive range; returns U64. |
| invariants | Rejects signs/trailing text/overflow/out-of-range; callers bound events 1..256, repeats 1..5, candidates 1..8. |
| ownership | string_view borrows argv during call only. |
| failure | Invalid parse/grant throws calibration_failed before file processing. |
| cost | Linear numeric parse, no heap storage. |
| Design | [examples/cost-calibration/main.cpp](../../../../../examples/cost-calibration/main.cpp), [docs/maintenance_cost.md](../../../../maintenance_cost.md), [docs/candidate_alternatives.md](../../../../candidate_alternatives.md) |

## B0005

[Lines 31–33](../../../../../examples/cost-calibration/main.cpp#L31); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
U64 elapsed(Clock::time_point begin,Clock::time_point end)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Convert one measured nonnegative steady-clock interval to nanoseconds. |
| inputs / outputs | Time point values; returns U64 duration. |
| invariants | No timing-quality, confidence or cross-machine comparability follows from nonnegative duration. |
| ownership | Inline value copies. |
| failure | Negative duration throws calibration_failed. |
| cost | Fixed duration conversion, no clock read inside helper. |
| Design | [examples/cost-calibration/main.cpp](../../../../../examples/cost-calibration/main.cpp), [docs/maintenance_cost.md](../../../../maintenance_cost.md), [docs/candidate_alternatives.md](../../../../candidate_alternatives.md) |

## B0006

[Lines 34–44](../../../../../examples/cost-calibration/main.cpp#L34); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
planner::CandidateSnapshot candidates(const frontend::NormalizedSql& normalized,std::size_t count)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Prove original minimum height and retain a finite checked candidate prefix. |
| inputs / outputs | Borrowed admitted normalized SQL/count; producer/replay ceilings 10M and &lt;=10000 calls of quantum 1000 per proof/enumeration loop. |
| invariants | Requires a real optimum and at least one member; reaching requested count is not family exhaustion. Candidate provider retains its actual exhaustion state. |
| ownership | Search/provider own admission copies/continuations; returned snapshot explicitly copies handle/event vectors, then retains actual shared private Data after provider destruction. |
| failure | Proof failure/noncompletion, failed enumeration/empty prefix and snapshot allocation fail explicitly; no unchecked seed is substituted. |
| cost | Blocking exact proof/enumeration and allocating prefix admission; subsequent handle copies share actual Data. |
| Design | [examples/cost-calibration/main.cpp](../../../../../examples/cost-calibration/main.cpp), [include/crown/planner/search.hpp](../../../../../include/crown/planner/search.hpp), [include/crown/planner/candidates.hpp](../../../../../include/crown/planner/candidates.hpp), [src/planner/candidates.cpp](../../../../../src/planner/candidates.cpp), [docs/maintenance_cost.md](../../../../maintenance_cost.md), [docs/candidate_alternatives.md](../../../../candidate_alternatives.md) |

## B0007

[Lines 45–48](../../../../../examples/cost-calibration/main.cpp#L45); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
io::Json ratio(const std::optional<model::Ratio>& value)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Encode an available exact model ratio or unavailable null. |
| inputs / outputs | Optional stored Ratio; returns numerator/denominator JSON or null. |
| invariants | Does not normalize/validate arbitrary public Ratio; it serializes factory-produced values here. Null remains unknown, not zero. |
| ownership | Borrows optional for call; output owns numeric JSON. |
| failure | JSON allocation may throw. |
| cost | Fixed field serialization. |
| Design | [examples/cost-calibration/main.cpp](../../../../../examples/cost-calibration/main.cpp), [include/crown/runtime/maintenance_cost.hpp](../../../../../include/crown/runtime/maintenance_cost.hpp), [src/runtime/maintenance_cost.cpp](../../../../../src/runtime/maintenance_cost.cpp), [docs/maintenance_cost.md](../../../../maintenance_cost.md), [docs/candidate_alternatives.md](../../../../candidate_alternatives.md) |

## B0008

[Lines 49–159](../../../../../examples/cost-calibration/main.cpp#L49); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
int run(int argc,char** argv)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Measure native replay phases and fit a qualified in-sample cost model. |
| inputs / outputs | SQL CATALOG JSONL \[EVENTS\] \[REPETITIONS\] \[CANDIDATES\]; emits &lt;=16MiB calibration report. |
| invariants | Actual admitted nonconstant SQL/checkable candidates and nonempty physical trace are required. Replays start empty, volatile, delta mode, exact C01 counters, observation off; no WAL/sink. |
| ownership | Each repetition creates its own native session/account; final profile retains actual candidate-bound evidence after session destruction. Explicit 64MiB receiver owns calibration/result storage; observations/reports are ordinary host vectors/JSON. |
| failure | Read/admission/proof/counter/timing/replay/fit/estimate/report failure terminates with no partial successful model. No native plan deployment occurs. Final report emission explicitly flushes stdout and returns failure on stream error; completed work is not rolled back. |
| cost | Candidate/repetition/event replay, three timed phases/event, outside-clock counter capture/snapshots/profile scans and bounded fitting/estimate/reporting. One final stdout flush is presentation work outside native event maintenance. |
| Design | [examples/cost-calibration/main.cpp](../../../../../examples/cost-calibration/main.cpp), [include/crown/runtime/session.hpp](../../../../../include/crown/runtime/session.hpp), [src/runtime/session.cpp](../../../../../src/runtime/session.cpp), [include/crown/runtime/maintenance_cost.hpp](../../../../../include/crown/runtime/maintenance_cost.hpp), [src/runtime/maintenance_cost.cpp](../../../../../src/runtime/maintenance_cost.cpp), [schemas/cost-calibration-v1.schema.json](../../../../../schemas/cost-calibration-v1.schema.json), [docs/maintenance_cost.md](../../../../maintenance_cost.md), [docs/candidate_alternatives.md](../../../../candidate_alternatives.md) |

```text
require(argc>=4
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Validate optional finite calibration arguments and load/admit actual SQL. |
| inputs / outputs | Defaults events=64, repetitions=3, candidates=3; bounded catalog/SQL/input buffers; rejects constant-empty route. |
| invariants | No tree calibration workload exists here for constant-empty or no physical input; retained prefix is not an exhaustive cost search. |
| ownership | Owning compiler/input DTOs and checked candidate snapshot; explicit model account is separate from each runtime account. |
| failure | Usage/read/admission/proof/resource rejection occurs before measured sessions. |
| cost | File parsing, exact proof/prefix admission and 64MiB model-account creation. |
| Design | [examples/cost-calibration/main.cpp](../../../../../examples/cost-calibration/main.cpp), [include/crown/runtime/maintenance_cost.hpp](../../../../../include/crown/runtime/maintenance_cost.hpp), [src/runtime/maintenance_cost.cpp](../../../../../src/runtime/maintenance_cost.cpp), [include/crown/runtime/session.hpp](../../../../../include/crown/runtime/session.hpp), [src/runtime/session.cpp](../../../../../src/runtime/session.cpp), [include/crown/storage/layout.hpp](../../../../../include/crown/storage/layout.hpp), [src/storage/layout.cpp](../../../../../src/storage/layout.cpp), [docs/maintenance_cost.md](../../../../maintenance_cost.md), [docs/candidate_alternatives.md](../../../../candidate_alternatives.md) |

```text
for(std::size_t index=0;index<snapshot.candidate_count();
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Lower each checked candidate and allocate host fitting observations. |
| inputs / outputs | Candidate snapshot index; actual normalized source and tree lower into PhysicalPlan; vector/raw JSON/profile/totals start fresh per candidate. |
| invariants | No handwritten alternative physical plan is trusted; plan identity stays candidate/source bound. |
| ownership | Candidate descriptor copy retains actual checked shared payload; PhysicalPlan metadata and ordinary vectors/JSON own their storage. |
| failure | Lowering/host allocation failure stops the candidate report rather than dropping it silently. |
| cost | One checked lowering plus ordinary per-candidate collection setup. |
| Design | [examples/cost-calibration/main.cpp](../../../../../examples/cost-calibration/main.cpp), [include/crown/runtime/maintenance_cost.hpp](../../../../../include/crown/runtime/maintenance_cost.hpp), [src/runtime/maintenance_cost.cpp](../../../../../src/runtime/maintenance_cost.cpp), [include/crown/runtime/session.hpp](../../../../../include/crown/runtime/session.hpp), [src/runtime/session.cpp](../../../../../src/runtime/session.cpp), [include/crown/storage/layout.hpp](../../../../../include/crown/storage/layout.hpp), [src/storage/layout.cpp](../../../../../src/storage/layout.cpp), [docs/maintenance_cost.md](../../../../maintenance_cost.md), [docs/candidate_alternatives.md](../../../../candidate_alternatives.md) |

```text
for(U64 repetition=0;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Create a fresh empty native delta session and exact initial counter census. |
| inputs / outputs | Buffered istringstream over same input; observation off, C01 counters enabled, start; requires initial exact feature census. |
| invariants | No warm-up is discarded. Each fresh owner has independent original account/identity; observations are compared within that owner interval. |
| ownership | QuerySession owns unique copied stream; native imports use its own grant. FeatureCensus is an inline numeric copy; workload capture is separate. |
| failure | Session/counter admission or unavailable exact census fails before timed events for that repetition. |
| cost | Native initialization and initial funded workload/feature capture outside event timers. |
| Design | [examples/cost-calibration/main.cpp](../../../../../examples/cost-calibration/main.cpp), [include/crown/runtime/maintenance_cost.hpp](../../../../../include/crown/runtime/maintenance_cost.hpp), [src/runtime/maintenance_cost.cpp](../../../../../src/runtime/maintenance_cost.cpp), [include/crown/runtime/session.hpp](../../../../../include/crown/runtime/session.hpp), [src/runtime/session.cpp](../../../../../src/runtime/session.cpp), [include/crown/storage/layout.hpp](../../../../../include/crown/storage/layout.hpp), [src/storage/layout.cpp](../../../../../src/storage/layout.cpp), [docs/maintenance_cost.md](../../../../maintenance_cost.md), [docs/candidate_alternatives.md](../../../../candidate_alternatives.md) |

```text
const auto begin=Clock::now();if(!session->begin_next()
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Measure physical decode, native preparation and commit. |
| inputs / outputs | Started session; at most event_limit successful inputs, step to prepared then commit; end clock immediately after commit. |
| invariants | EOF decode stops without emitting a fake timed observation. Input decoding/import and native delta spool preparation are included. |
| ownership | Session owns input/pending/output state; no row borrow escapes. |
| failure | Decode/native allocation/work/commit failure aborts calibration; no successful partial model. |
| cost | Timed complete begin/step/commit path; no WAL/sink/delivery work. |
| Design | [examples/cost-calibration/main.cpp](../../../../../examples/cost-calibration/main.cpp), [include/crown/runtime/maintenance_cost.hpp](../../../../../include/crown/runtime/maintenance_cost.hpp), [src/runtime/maintenance_cost.cpp](../../../../../src/runtime/maintenance_cost.cpp), [include/crown/runtime/session.hpp](../../../../../include/crown/runtime/session.hpp), [src/runtime/session.cpp](../../../../../src/runtime/session.cpp), [include/crown/storage/layout.hpp](../../../../../include/crown/storage/layout.hpp), [src/storage/layout.cpp](../../../../../src/storage/layout.cpp), [docs/maintenance_cost.md](../../../../maintenance_cost.md), [docs/candidate_alternatives.md](../../../../candidate_alternatives.md) |

```text
U64 output_rows=0;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Measure complete committed-output-spool reads. |
| inputs / outputs | while(next_output()) counts rows until terminal null; separate clock interval. |
| invariants | Owns/destroys each returned optional SignedResult within the loop; those immediate row releases are included. No JSON encoding/sink is measured. |
| ownership | Returned tuple owns native immutable payload; session retains/relinquishes committed spool according to output API. |
| failure | Output failure aborts calibration after committed input; no output callback retries. |
| cost | Per-record/terminal reads and returned temporary release, separate from private spool creation in native preparation. |
| Design | [examples/cost-calibration/main.cpp](../../../../../examples/cost-calibration/main.cpp), [include/crown/runtime/maintenance_cost.hpp](../../../../../include/crown/runtime/maintenance_cost.hpp), [src/runtime/maintenance_cost.cpp](../../../../../src/runtime/maintenance_cost.cpp), [include/crown/runtime/session.hpp](../../../../../include/crown/runtime/session.hpp), [src/runtime/session.cpp](../../../../../src/runtime/session.cpp), [include/crown/storage/layout.hpp](../../../../../include/crown/storage/layout.hpp), [src/storage/layout.cpp](../../../../../src/storage/layout.cpp), [docs/maintenance_cost.md](../../../../maintenance_cost.md), [docs/candidate_alternatives.md](../../../../candidate_alternatives.md) |

```text
const auto captured=model::features(*session->workload_statistics());
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Derive one exact committed maintenance feature delta. |
| inputs / outputs | Post-output feature census; checks owner/reset/config/segment equal and every cumulative component nondecreasing, then subtracts before. |
| invariants | Requires exactly one base_input; sampled/truncated/saturated/incomplete/private counters cannot become timing features. |
| ownership | Captured snapshot owns funded numeric arrays; FeatureCensus/observations copy inline values into ordinary vector. |
| failure | Unavailable census or interval regression/mismatch stops the run instead of manufacturing zeros. |
| cost | Outside timers: funded workload capture, feature validation/scan and component subtraction. |
| Design | [examples/cost-calibration/main.cpp](../../../../../examples/cost-calibration/main.cpp), [include/crown/runtime/maintenance_cost.hpp](../../../../../include/crown/runtime/maintenance_cost.hpp), [src/runtime/maintenance_cost.cpp](../../../../../src/runtime/maintenance_cost.cpp), [include/crown/runtime/session.hpp](../../../../../include/crown/runtime/session.hpp), [src/runtime/session.cpp](../../../../../src/runtime/session.cpp), [include/crown/storage/layout.hpp](../../../../../include/crown/storage/layout.hpp), [src/storage/layout.cpp](../../../../../src/storage/layout.cpp), [docs/maintenance_cost.md](../../../../maintenance_cost.md), [docs/candidate_alternatives.md](../../../../candidate_alternatives.md) |

```text
output.units[static_cast<std::size_t>(model::Component::delta_start)]
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Attach explicit output phase units and store raw measured records. |
| inputs / outputs | Delta start=1, rows=actual output count, end=1; adds maintenance/output FitObservations and raw JSON phase labels. |
| invariants | These units describe the measured whole phases; regression later attributes cost by model assumption, not isolated per-feature measurement. |
| ownership | Ordinary observation vector/raw JSON own numeric copies; no runtime row retained. |
| failure | Host vector/JSON allocation can fail outside timers. |
| cost | O(component_count) vector copies and raw array serialization. |
| Design | [examples/cost-calibration/main.cpp](../../../../../examples/cost-calibration/main.cpp), [include/crown/runtime/maintenance_cost.hpp](../../../../../include/crown/runtime/maintenance_cost.hpp), [src/runtime/maintenance_cost.cpp](../../../../../src/runtime/maintenance_cost.cpp), [include/crown/runtime/session.hpp](../../../../../include/crown/runtime/session.hpp), [src/runtime/session.cpp](../../../../../src/runtime/session.cpp), [include/crown/storage/layout.hpp](../../../../../include/crown/storage/layout.hpp), [src/storage/layout.cpp](../../../../../src/storage/layout.cpp), [docs/maintenance_cost.md](../../../../maintenance_cost.md), [docs/candidate_alternatives.md](../../../../candidate_alternatives.md) |

```text
const auto snapshot_begin=Clock::now();
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Measure full committed snapshot construction separately. |
| inputs / outputs | Timed session.snapshot call; stores start/row/end feature units and actual rows count. |
| invariants | Returned snapshot destruction occurs later outside this timer. Construction includes native result traversal/collection plus exported progress DTO; not constant-time borrowing. |
| ownership | SessionRows owns shared native collection/tuples; progress owns ordinary map/text. state remains live through end of event iteration. |
| failure | Snapshot row/byte/cursor/memory/export limits abort calibration. |
| cost | Funded snapshot materialization and progress copies during clock, followed by outside-clock observation/report storage. |
| Design | [examples/cost-calibration/main.cpp](../../../../../examples/cost-calibration/main.cpp), [include/crown/runtime/maintenance_cost.hpp](../../../../../include/crown/runtime/maintenance_cost.hpp), [src/runtime/maintenance_cost.cpp](../../../../../src/runtime/maintenance_cost.cpp), [include/crown/runtime/session.hpp](../../../../../include/crown/runtime/session.hpp), [src/runtime/session.cpp](../../../../../src/runtime/session.cpp), [include/crown/storage/layout.hpp](../../../../../include/crown/storage/layout.hpp), [src/storage/layout.cpp](../../../../../src/storage/layout.cpp), [docs/maintenance_cost.md](../../../../maintenance_cost.md), [docs/candidate_alternatives.md](../../../../candidate_alternatives.md) |

```text
session->pause();const auto captured=model::capture
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Capture actual candidate-bound final profile and compare repeated results. |
| inputs / outputs | Quiescent session, snapshot/index; model::capture must produce Profile. Exports final rows and checks records/delta rows/snapshot rows/exact JSON equality against prior repetition. |
| invariants | Profile physical binding is re-lowered against actual source. Repeated equality validates this replay horizon, not independent statistical samples or future behavior. |
| ownership | Profile shared Data retains actual evidence beyond session destruction; exported rows are ordinary JSON; replacing profile releases prior graph as ownership dictates. |
| failure | Capture/profile/binding/final snapshot or repetition mismatch aborts the report. |
| cost | Cold statistics/population/candidate-binding scan plus final snapshot/export outside all phase timers. |
| Design | [examples/cost-calibration/main.cpp](../../../../../examples/cost-calibration/main.cpp), [include/crown/runtime/maintenance_cost.hpp](../../../../../include/crown/runtime/maintenance_cost.hpp), [src/runtime/maintenance_cost.cpp](../../../../../src/runtime/maintenance_cost.cpp), [include/crown/runtime/session.hpp](../../../../../include/crown/runtime/session.hpp), [src/runtime/session.cpp](../../../../../src/runtime/session.cpp), [include/crown/storage/layout.hpp](../../../../../include/crown/storage/layout.hpp), [src/storage/layout.cpp](../../../../../src/storage/layout.cpp), [docs/maintenance_cost.md](../../../../maintenance_cost.md), [docs/candidate_alternatives.md](../../../../candidate_alternatives.md) |

```text
model::FitOptions fitting;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Fit nonnegative model coefficients from whole-phase observations. |
| inputs / outputs | Exact captured mode facts, all repetition observations, backend/context label, explicit model account and 20M work ceiling. |
| invariants | Fixed-order nonnegative fitting uses approximate floating point and quantizes rates; correlated features/rank/underdetermination remain explicit. Label is caller context, not measurement certification. |
| ownership | Calibration factory owns model-account coefficient/raw observation storage; implicit handle copies share real shared Data. Host observations remain separate. |
| failure | No calibration on budget/arithmetic/convergence/allocation failure; require stops the example. |
| cost | Bounded iterative fitting and quantization, storage admission and diagnostics outside replay timers. |
| Design | [examples/cost-calibration/main.cpp](../../../../../examples/cost-calibration/main.cpp), [include/crown/runtime/maintenance_cost.hpp](../../../../../include/crown/runtime/maintenance_cost.hpp), [src/runtime/maintenance_cost.cpp](../../../../../src/runtime/maintenance_cost.cpp), [include/crown/runtime/session.hpp](../../../../../include/crown/runtime/session.hpp), [src/runtime/session.cpp](../../../../../src/runtime/session.cpp), [include/crown/storage/layout.hpp](../../../../../include/crown/storage/layout.hpp), [src/storage/layout.cpp](../../../../../src/storage/layout.cpp), [docs/maintenance_cost.md](../../../../maintenance_cost.md), [docs/candidate_alternatives.md](../../../../candidate_alternatives.md) |

```text
std::vector<model::InputDemand> demand;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Estimate one repeated replay horizon using the final profile and fitted calibration. |
| inputs / outputs | Physical table/operation counts from final profile; delta epochs/rows and snapshot counts/totals from checked one-repetition totals; 20M estimate work. |
| invariants | Calibration pools all repetitions but estimate demand is one replay horizon. Missing facts/coefficients stay issues; memory bytes are separate and future_memory_unknown=true. |
| ownership | InputDemand vector is ordinary temporary; estimate result owns copied demand and retains profile/calibration handles under explicit receiver semantics. |
| failure | No result on resource/arithmetic failure; unavailable per-candidate terms are reported as issues/null, not zero. |
| cost | Descriptor demand scan, checked rational feature/model evaluation for retained family and funded result construction. |
| Design | [examples/cost-calibration/main.cpp](../../../../../examples/cost-calibration/main.cpp), [include/crown/runtime/maintenance_cost.hpp](../../../../../include/crown/runtime/maintenance_cost.hpp), [src/runtime/maintenance_cost.cpp](../../../../../src/runtime/maintenance_cost.cpp), [include/crown/runtime/session.hpp](../../../../../include/crown/runtime/session.hpp), [src/runtime/session.cpp](../../../../../src/runtime/session.cpp), [include/crown/storage/layout.hpp](../../../../../include/crown/storage/layout.hpp), [src/storage/layout.cpp](../../../../../src/storage/layout.cpp), [docs/maintenance_cost.md](../../../../maintenance_cost.md), [docs/candidate_alternatives.md](../../../../candidate_alternatives.md) |

```text
io::Json coefficients=io::Json::object();
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Export coefficient provenance, rank/residual diagnostics and qualified predictions. |
| inputs / outputs | Factory calibration/result and raw observations; coefficients retain fitted_linear_assumption and unknowns are null. |
| invariants | Reports calibration-data errors only, numerical rank tolerance and ridge/quantization settings; no held-out accuracy, time guarantee or future peak-memory forecast. |
| ownership | Ordinary JSON/strings own all transport copies; score/profile views borrow retained result graph during export. |
| failure | Export/allocation/report size failure discards successful stdout output, not native state (sessions are volatile). |
| cost | Component/candidate/raw observation scans, string/rational encoding and full JSON storage. |
| Design | [examples/cost-calibration/main.cpp](../../../../../examples/cost-calibration/main.cpp), [include/crown/runtime/maintenance_cost.hpp](../../../../../include/crown/runtime/maintenance_cost.hpp), [src/runtime/maintenance_cost.cpp](../../../../../src/runtime/maintenance_cost.cpp), [include/crown/runtime/session.hpp](../../../../../include/crown/runtime/session.hpp), [src/runtime/session.cpp](../../../../../src/runtime/session.cpp), [include/crown/storage/layout.hpp](../../../../../include/crown/storage/layout.hpp), [src/storage/layout.cpp](../../../../../src/storage/layout.cpp), [docs/maintenance_cost.md](../../../../maintenance_cost.md), [docs/candidate_alternatives.md](../../../../candidate_alternatives.md) |

```text
struct utsname system{};
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Record limited environment/compiler context and emit the bounded report. |
| inputs / outputs | uname optional fallback unknown; compiler macro/C++/pointer data, hashes, horizon, scope/qualification and NDEBUG flag; dump &lt;=16MiB. |
| invariants | Collector metadata does not introspect archive flags, pin CPU/cache, add warmups or create controlled-benchmark evidence. |
| ownership | Fixed uname struct plus ordinary report/string; no native row or process resource retained. |
| failure | uname failure is represented unknown; report dump/limit/flushed stdout state can fail after calibration. |
| cost | Input/SQL hashing and full report encoding outside replay clocks; byte check follows allocation. Explicit flush completes the process report before its stream-state exit check. |
| Design | [examples/cost-calibration/main.cpp](../../../../../examples/cost-calibration/main.cpp), [include/crown/runtime/maintenance_cost.hpp](../../../../../include/crown/runtime/maintenance_cost.hpp), [src/runtime/maintenance_cost.cpp](../../../../../src/runtime/maintenance_cost.cpp), [include/crown/runtime/session.hpp](../../../../../include/crown/runtime/session.hpp), [src/runtime/session.cpp](../../../../../src/runtime/session.cpp), [include/crown/storage/layout.hpp](../../../../../include/crown/storage/layout.hpp), [src/storage/layout.cpp](../../../../../src/storage/layout.cpp), [docs/maintenance_cost.md](../../../../maintenance_cost.md), [docs/candidate_alternatives.md](../../../../candidate_alternatives.md) |

## B0009

[Lines 160–160](../../../../../examples/cost-calibration/main.cpp#L160); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
}
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
| Design | [examples/cost-calibration/main.cpp](../../../../../examples/cost-calibration/main.cpp), [docs/maintenance_cost.md](../../../../maintenance_cost.md), [docs/candidate_alternatives.md](../../../../candidate_alternatives.md) |

## B0010

[Lines 161–161](../../../../../examples/cost-calibration/main.cpp#L161); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
int main(int argc,char** argv)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Contain calibration failures at the executable boundary. |
| inputs / outputs | Forwards CLI; returns run status; std::exception prints what() and returns 1. |
| invariants | Does not catch inside event/model loops or continue after an invalid observation. |
| ownership | run locals release native owners, retained profiles and host buffers on unwind. |
| failure | Single std::exception catch; immediate successful stdout state checked by run. |
| cost | One process boundary handler. |
| Design | [examples/cost-calibration/main.cpp](../../../../../examples/cost-calibration/main.cpp), [docs/maintenance_cost.md](../../../../maintenance_cost.md), [docs/candidate_alternatives.md](../../../../candidate_alternatives.md) |
