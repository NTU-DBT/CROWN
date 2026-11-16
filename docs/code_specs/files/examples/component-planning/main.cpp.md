# `examples/component-planning/main.cpp` — block usage map

[Source](../../../../../examples/component-planning/main.cpp) · [Source index](../../../README.md) · [Subsystem contracts](../../../subsystem_contracts.md) · [Reviewed primitives](../../../primitives.md)

Demonstrate a concrete public workflow and executable invocation using installed/native CROWN interfaces.

Snapshot SHA-256: `87a775b682b92f91ea28970622c9ae168ecf5468ff7c91fbe69defff08b1852c`. 482 lines partitioned into 36 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [examples](../../../subsystem_contracts.md#examples). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/cli.md](../../../../cli.md), [docs/native_build.md](../../../../native_build.md), [docs/measurement.md](../../../../measurement.md), [docs/ranking_evaluation.md](../../../../ranking_evaluation.md), [docs/reoptimization.md](../../../../reoptimization.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–33](../../../../../examples/component-planning/main.cpp#L1) | Imports dependencies; declares namespace scope; declares aliases; declares values/defaults or compile-time conditions. | source comment (unverified): // This executable is a cold experiment exporter. It never installs a choice, · [reviewed contract](#b0001) |
| [B0002 · 34–36](../../../../../examples/component-planning/main.cpp#L34) | Callable definition: void require(bool value,std::string_view message) | calls Error, std::string; guard void require(bool value,std::string_view message) {; source comment (unverified): // This executable is a cold experiment exporter. It never installs a choice, · [reviewed contract](#b0002) |
| [B0003 · 37–45](../../../../../examples/component-planning/main.cpp#L37) | Callable definition: std::string read(const char* path,std::size_t limit) | calls file, require, bool, gcount; guard std::ifstream file(path,std::ios::binary);require(bool(file),"cannot open component input");; returns result; 1 loop sites · [reviewed contract](#b0003) |
| [B0004 · 46–49](../../../../../examples/component-planning/main.cpp#L46) | Callable definition: U64 integer(const Json& value,U64 minimum,U64 maximum) | calls require, is_number_integer, is_number_unsigned; guard require(value.is_number_integer() && (value.is_number_unsigned() \|\| value.get&lt;std::int64_t&gt;()&gt;=0),"…; returns result · [reviewed contract](#b0004) |
| [B0005 · 50–52](../../../../../examples/component-planning/main.cpp#L50) | Callable definition: U64 grant(const Json& request,const char* key,U64 fallback,U64 minimum,U64 maximum) | calls contains, integer, at; returns request.contains(key)?integer(request.at(key),minimum,maximum):fallback · [reviewed contract](#b0005) |
| [B0006 · 53–56](../../../../../examples/component-planning/main.cpp#L53) | Callable definition: U64 elapsed(Clock::time_point begin,Clock::time_point end) | calls count, require; guard require(count&gt;=0,"component clock regressed");return static_cast&lt;U64&gt;(count);; returns static_cast&lt;U64&gt;(count) · [reviewed contract](#b0006) |
| [B0007 · 57–57](../../../../../examples/component-planning/main.cpp#L57) | Callable definition: template&lt;class Text&gt; std::string text(const Text& value) | calls data, size; returns {value.data(),value.size()} · [reviewed contract](#b0007) |
| [B0008 · 58–60](../../../../../examples/component-planning/main.cpp#L58) | Callable definition: Json ratio(const std::optional&lt;cost::Ratio&gt;& value) | calls Json; returns value?Json{{@ ,value-&gt;numerator},{@ ,value-&gt;denominator}}:Json(nullptr) · [reviewed contract](#b0008) |
| [B0009 · 61–66](../../../../../examples/component-planning/main.cpp#L61) | Callable definition: Json usage(const rank::Usage& value) | calls ; returns {{@ ,value.work},{@ ,value.cells},{@ ,value.payload_bytes}, · [reviewed contract](#b0009) |
| [B0010 · 67–70](../../../../../examples/component-planning/main.cpp#L67) | Callable definition: Json stamp(const runtime::workload::Stamp& value) | calls ; returns {{@ ,value.owner.value},{@ ,value.committed_epoch},{@ ,value.interval_start_epoch}, · [reviewed contract](#b0010) |
| [B0011 · 71–76](../../../../../examples/component-planning/main.cpp#L71) | Callable definition: Json modes(const runtime::workload::ModeFacts& value) | calls ; returns {{@ ,value.delta_owner},{@ ,static_cast&lt;unsigned&gt;(value.requested_mode)}, · [reviewed contract](#b0011) |
| [B0012 · 77–79](../../../../../examples/component-planning/main.cpp#L77) | Explanatory comments or spacing. | source comment (unverified): // All bounds are finite. Logical planner grants and native account bytes are · [reviewed contract](#b0012) |
| [B0013 · 80–98](../../../../../examples/component-planning/main.cpp#L80) | Type/record definition: struct Request | returns result; result; source comment (unverified): // All bounds are finite. Logical planner grants and native account bytes are · [reviewed contract](#b0013) |
| [B0014 · 99–120](../../../../../examples/component-planning/main.cpp#L99) | Callable definition: Request parse_request(const Json& json) | calls require, is_object, items, contains; guard require(json.is_object(),"component request must be an object");; returns r; 1 loop sites · [reviewed contract](#b0014) |
| [B0015 · 121–124](../../../../../examples/component-planning/main.cpp#L121) | Callable definition: void emit(const Json& report) | calls dump, require, size, flush; guard const auto encoded=report.dump();require(encoded.size()&lt;=64U*1024U*1024U,"component report exceeds6… · [reviewed contract](#b0015) |
| [B0016 · 125–127](../../../../../examples/component-planning/main.cpp#L125) | Explanatory comments or spacing. | source comment (unverified): // The original certificate keeps its original witness. V3 is explicitly an · [reviewed contract](#b0016) |
| [B0017 · 128–132](../../../../../examples/component-planning/main.cpp#L128) | Callable definition: Json artifact(const PhysicalPlan& plan,const Json& certificate,bool minimum) | calls io::write_physical; returns {{@ ,minimum?2:3},; source comment (unverified): // The original certificate keeps its original witness. V3 is explicitly an · [reviewed contract](#b0017) |
| [B0018 · 133–137](../../../../../examples/component-planning/main.cpp#L133) | Callable definition: Json shape(const FreeConnexTree& tree) | calls std::max, size; returns {{@ ,tree.nodes.size()},{@ ,generalized},{@ ,fanout}}; 1 loop sites · [reviewed contract](#b0018) |
| [B0019 · 138–144](../../../../../examples/component-planning/main.cpp#L138) | Callable definition: void drain(planner::CandidateProvider& provider,std::size_t count) | calls candidate_count, progress, advance; 1 loop sites · [reviewed contract](#b0019) |
| [B0020 · 145–145](../../../../../examples/component-planning/main.cpp#L145) | Type/record definition: struct Family |  · [reviewed contract](#b0020) |
| [B0021 · 146–151](../../../../../examples/component-planning/main.cpp#L146) | Callable definition: Family family(std::string id,planner::CandidateProvider provider,const Request& request,Json preparation) | calls Clock::now, drain, std::move, elapsed; returns {std::move(id),provider.snapshot(),std::move(report)} · [reviewed contract](#b0021) |
| [B0022 · 152–164](../../../../../examples/component-planning/main.cpp#L152) | Callable definition: Json meta_report(const meta::MetaCandidateReport& p) | calls std::string; returns {{@ ,static_cast&lt;unsigned&gt;(p.construction_stop)}, · [reviewed contract](#b0022) |
| [B0023 · 165–173](../../../../../examples/component-planning/main.cpp#L165) | Callable definition: FreeConnexTree ordinary_tree(const Query& query,const meta::JoinTree& join) | calls size, insert, push_back, std::to_string; returns tree; growth insert, push_back; 3 loop sites · [reviewed contract](#b0023) |
| [B0024 · 174–176](../../../../../examples/component-planning/main.cpp#L174) | Explanatory comments or spacing. | source comment (unverified): // A profile always comes from this actual candidate's lowered owner. A stale · [reviewed contract](#b0024) |
| [B0025 · 177–177](../../../../../examples/component-planning/main.cpp#L177) | Type/record definition: struct Training | source comment (unverified): // A profile always comes from this actual candidate's lowered owner. A stale · [reviewed contract](#b0025) |
| [B0026 · 178–208](../../../../../examples/component-planning/main.cpp#L178) | Callable definition: Training train(const Family& family,std::size_t index,const PhysicalPlan& plan,const std::string& input, const Request& request,s… | calls owner, runtime_options, configure_workload_statistics, stream; guard require(count&lt;request.event_limit,"training input exceeds event grant");; returns {std::move(profile),std::move(report)}; growth push_back; 3 loop sites · [reviewed contract](#b0026) |
| [B0027 · 209–212](../../../../../examples/component-planning/main.cpp#L209) | Explanatory comments or spacing. | source comment (unverified): // All calibration observations use committed full-detail census features. The · [reviewed contract](#b0027) |
| [B0028 · 213–235](../../../../../examples/component-planning/main.cpp#L213) | Callable definition: Json measure_calibration(const std::vector&lt;PhysicalPlan&gt;& plans,const std::string& input,const Request& request) | calls Json::array, std::min, size, owner; guard auto initial=cost::features(owner.workload_statistics(),request.model_limits());require(initial.cen…; returns raw; growth push_back; 5 loop sites; source comment (unverified): // All calibration observations use committed full-detail census features. The · [reviewed contract](#b0028) |
| [B0029 · 236–249](../../../../../examples/component-planning/main.cpp#L236) | Callable definition: std::vector&lt;cost::FitObservation&gt; observations(const Json& raw) | calls require, is_array, empty, size; guard require(raw.is_array() && !raw.empty() && raw.size()&lt;=65536,"invalid frozen calibration observation…; returns result; growth push_back, reserve; 3 loop sites · [reviewed contract](#b0029) |
| [B0030 · 250–264](../../../../../examples/component-planning/main.cpp#L250) | Callable definition: Json calibration_report(const cost::CalibrationAttempt& fitted) | calls usage, Json::object, coefficients, std::string; returns report; report; 1 loop sites · [reviewed contract](#b0030) |
| [B0031 · 265–279](../../../../../examples/component-planning/main.cpp#L265) | Callable definition: Json ranking(const planner::CandidateSnapshot& snapshot,const resource::MemoryAccount& account, const std::optional&lt;rank::Evidenc… | calls model_limits, rank::rank_with_account, usage, Json::array; returns report; growth push_back; 1 loop sites · [reviewed contract](#b0031) |
| [B0032 · 280–293](../../../../../examples/component-planning/main.cpp#L280) | Callable definition: Json estimates(const cost::Attempt& attempt) | calls usage, Json::array, candidates, push_back; returns report; growth push_back; 2 loop sites · [reviewed contract](#b0032) |
| [B0033 · 294–294](../../../../../examples/component-planning/main.cpp#L294) | Explanatory comments or spacing. |  |
| [B0034 · 295–478](../../../../../examples/component-planning/main.cpp#L295) | Callable definition: int run(int argc,char** argv) | calls require, io::read_json, read, parse_request; guard require(argc==6,"usage: crown_export_components QUERY.sql CATALOG.json TRAIN.jsonl CALIBRATION.json…; returns 0; x.physical_sha256()==plan.physical_sha256(); growth emplace, insert, push_back; 10 loop sites; source comment (unverified): // Common calibration initialization is not an implicit member of any family. · [reviewed contract](#b0034) |
| [B0035 · 479–479](../../../../../examples/component-planning/main.cpp#L479) | Closes surrounding scope/type. | source comment (unverified): // namespace · [reviewed contract](#b0035) |
| [B0036 · 480–482](../../../../../examples/component-planning/main.cpp#L480) | Callable definition: int main(int argc,char** argv) | calls run, what; returns run(argc,argv); 1 · [reviewed contract](#b0036) |

## B0001

[Lines 1–33](../../../../../examples/component-planning/main.cpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L1-L33:sha256:665037a5db980ccbb0b1c1b697465eafb4fc4ee353e5683d1b82016b9ed047c6
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Import the explicit public planner, native runtime, IO and standard-library dependencies for a cold experiment CLI. |
| inputs / outputs | Public headers and local aliases establish types/names used below; no query or runtime is constructed here. |
| invariants | The exporter adds no production update hook and receives no evaluation path. Local namespace aliases are not proof or policy authority. |
| ownership | Headers and type aliases have no per-call payload ownership; runtime objects are owned in later explicit scopes. |
| failure | Missing/incompatible public dependencies are a compilation/link failure, not a successful omitted experiment arm. |
| cost | Compile-time include/type resolution only; the comments make no runtime no-allocation claim for the functions below. |
| Design | [docs/measurement.md](../../../../measurement.md), [build/verification/v58-b04-design-review-v1/README.md](../../../../../build/verification/v58-b04-design-review-v1/README.md) |

## B0002

[Lines 34–36](../../../../../examples/component-planning/main.cpp#L34); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L34-L36:sha256:c53133faa44f29b2e7625441976233e90d6f7236b0482c171f27a32f384b2b88
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Reject a violated CLI precondition at the single external diagnostic boundary. |
| inputs / outputs | Boolean condition and borrowed message produce normal return or an owning component_planning_error exception. |
| invariants | A diagnostic is never a candidate, proof or unavailable-as-zero estimate. |
| ownership | The message is borrowed on success and copied into Error on failure. |
| failure | False conditions throw; Error construction may itself allocate. main reports the failure and exits nonzero. |
| cost | One branch on success; failure constructs owning standard exception/message storage. This helper is confined to the cold exporter. |
| Design | [docs/measurement.md](../../../../measurement.md), [build/verification/v58-b04-design-review-v1/README.md](../../../../../build/verification/v58-b04-design-review-v1/README.md) |

## B0003

[Lines 37–45](../../../../../examples/component-planning/main.cpp#L37); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L37-L45:sha256:ed4de95b30aa50f715fa8a1c514d819d40f5c55e2b485a1f39b6ff2c9fb24dc5
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Read one external input under its declared byte grant. |
| inputs / outputs | Path and maximum bytes produce an owning binary string with exact file bytes. |
| invariants | Before appending, count must fit limit minus the already retained size. No partial oversized input becomes an admitted document. |
| ownership | ifstream owns its descriptor and the returned std::string owns ordinary heap bytes, outside native owner accounts. |
| failure | Open, bad read or byte overflow throws. RAII closes the file on every exit; allocation failure propagates. |
| cost | O(file bytes) read/copy with standard string capacity growth and a4096byte stack block; the byte grant does not bound all allocator overhead. |
| Design | [docs/measurement.md](../../../../measurement.md), [build/verification/v58-b04-design-review-v1/README.md](../../../../../build/verification/v58-b04-design-review-v1/README.md) |

## B0004

[Lines 46–49](../../../../../examples/component-planning/main.cpp#L46); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L46-L49:sha256:f07332aee85c5a1e7544f901d7b0d97238c4dcbbc7a2dbff79571b51aeeab61e
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Admit one exact bounded nonnegative JSON integer. |
| inputs / outputs | JSON numeric value and inclusive bounds produce uint64_t. |
| invariants | Reject floating point, booleans, negative signed values and values outside the supplied finite interval before using them as grants or demand. |
| ownership | Borrows the JSON value and returns a scalar; no retained source view. |
| failure | Wrong type/range or JSON conversion failure propagates to main as an unsuccessful command. |
| cost | Fixed scalar validation/conversion plus error formatting only on failure. |
| Design | [docs/measurement.md](../../../../measurement.md), [build/verification/v58-b04-design-review-v1/README.md](../../../../../build/verification/v58-b04-design-review-v1/README.md) |

## B0005

[Lines 50–52](../../../../../examples/component-planning/main.cpp#L50); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L50-L52:sha256:07ff70a94b2e8059ca579fafe697fe479e4b554444db47867d9195cb8f8be0ab
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Resolve an optional finite request grant without treating a missing field as a measured zero. |
| inputs / outputs | Request/key/default/min/max produce the admitted value or the fixed documented default. |
| invariants | The caller supplies a valid finite default. Present values pass integer validation; defaults are separately disclosed by the request contract/effective grants. |
| ownership | Borrows request and key; returns one scalar. |
| failure | Malformed present values throw; absence takes the documented default. |
| cost | One JSON object lookup and optional scalar validation; JSON lookup complexity follows its container. |
| Design | [docs/measurement.md](../../../../measurement.md), [build/verification/v58-b04-design-review-v1/README.md](../../../../../build/verification/v58-b04-design-review-v1/README.md) |

## B0006

[Lines 53–56](../../../../../examples/component-planning/main.cpp#L53); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L53-L56:sha256:e29de770740990383f68cea86bd782884858e656733986012066e850f0d39086
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Convert one nonnegative steady-clock interval to nanoseconds. |
| inputs / outputs | Start/end time_points produce uint64_t elapsed nanoseconds. |
| invariants | The exporter records raw local phase time, never a paper CPU bound or a C01 arrival rate. |
| ownership | Scalar input/output only. |
| failure | A negative duration rejects the command. The supported steady-clock measurement interval must fit its duration representation. |
| cost | Fixed duration conversion and comparison; the measured operation itself is outside this helper. |
| Design | [docs/measurement.md](../../../../measurement.md), [build/verification/v58-b04-design-review-v1/README.md](../../../../../build/verification/v58-b04-design-review-v1/README.md) |

## B0007

[Lines 57–57](../../../../../examples/component-planning/main.cpp#L57); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L57-L57:sha256:5b8014b0bd6dabd2ec6893215be418c62437646cc769d3ebe415015607dde65b
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Copy an account-backed score text view into ordinary JSON-presentation text. |
| inputs / outputs | A readable data()/size() text object yields a new std::string preserving all bytes. |
| invariants | The source handle remains live throughout the copy. Decimal score text is not converted to floating point. |
| ownership | Borrows the source and returns ordinary owning heap storage, separate from the original receiving account. |
| failure | Standard allocation/length failure propagates; no score fallback is manufactured. |
| cost | O(text bytes) copy and possible allocation, executed only during cold report encoding. |
| Design | [docs/maintenance_cost.md](../../../../maintenance_cost.md), [include/crown/runtime/maintenance_cost.hpp](../../../../../include/crown/runtime/maintenance_cost.hpp), [build/verification/v58-b04-design-review-v1/README.md](../../../../../build/verification/v58-b04-design-review-v1/README.md) |

## B0008

[Lines 58–60](../../../../../examples/component-planning/main.cpp#L58); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L58-L60:sha256:f29dcceecb0d859c424dd6db6866d6c349e14014687a9ad86f65dd93599cd1ac
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Encode a present exact C03 ratio or an explicit unavailable value. |
| inputs / outputs | optional Ratio produces numerator/denominator JSON or null. |
| invariants | Null remains unknown. No division, floating comparison or conversion of missing estimates to zero occurs. |
| ownership | Borrows a ratio and returns ordinary owning JSON. |
| failure | JSON allocation failure propagates; valid native Ratio outputs are assumed to carry a positive denominator. |
| cost | Fixed numeric payload plus JSON node allocation; later exact comparison belongs to the Python offline selector. |
| Design | [docs/maintenance_cost.md](../../../../maintenance_cost.md), [include/crown/runtime/maintenance_cost.hpp](../../../../../include/crown/runtime/maintenance_cost.hpp), [build/verification/v58-b04-design-review-v1/README.md](../../../../../build/verification/v58-b04-design-review-v1/README.md) |

## B0009

[Lines 61–66](../../../../../examples/component-planning/main.cpp#L61); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L61-L66:sha256:54cfeee92df577c761f3a24cd762f58cf44f540d0392550541691501c3d699c2
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Render native ranking/model accounting without merging incompatible resource units. |
| inputs / outputs | rank::Usage produces named work/cell/byte/lowering/identity/time counters. |
| invariants | Selected checkpoint work, payload bytes and active nanoseconds stay separate; they do not establish total CPU/RSS. |
| ownership | Borrows the usage record and owns its JSON copy. |
| failure | JSON allocation/encoding failure propagates. |
| cost | Fixed number of numeric fields and ordinary JSON allocations. |
| Design | [docs/maintenance_cost.md](../../../../maintenance_cost.md), [include/crown/runtime/maintenance_cost.hpp](../../../../../include/crown/runtime/maintenance_cost.hpp), [build/verification/v58-b04-design-review-v1/README.md](../../../../../build/verification/v58-b04-design-review-v1/README.md) |

## B0010

[Lines 67–70](../../../../../examples/component-planning/main.cpp#L67); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L67-L70:sha256:9e5e00b2f990555070424cf8b0d885f71d5fc0056baddd1f65a3fcdad53a7532
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Expose the actual captured workload owner/epoch/interval generations. |
| inputs / outputs | Native immutable workload Stamp produces numeric diagnostic JSON. |
| invariants | A stamp describes captured history; rendering it does not make old evidence current or authenticate prior enforcement. |
| ownership | Scalar copy into ordinary JSON; no owner mutation or new evidence handle. |
| failure | JSON allocation failure propagates. |
| cost | Fixed field count; original capture cost is elsewhere. |
| Design | [docs/maintenance_cost.md](../../../../maintenance_cost.md), [include/crown/runtime/maintenance_cost.hpp](../../../../../include/crown/runtime/maintenance_cost.hpp), [build/verification/v58-b04-design-review-v1/README.md](../../../../../build/verification/v58-b04-design-review-v1/README.md) |

## B0011

[Lines 71–76](../../../../../examples/component-planning/main.cpp#L71); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L71-L76:sha256:4636426d288fdd6184bcfbf30bf7cdb670f81725f60720b610d71b99cbe5c460
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Render actual runtime mode facts for calibration and profile compatibility. |
| inputs / outputs | Native ModeFacts produces enum-coded requested/resolved owner, completion, live-maintenance and view fields. |
| invariants | These are actual native facts, not caller-edited ModeFacts admitted as a capability. Calibration identity must match them exactly. |
| ownership | Copies scalars into ordinary JSON. |
| failure | JSON allocation failure propagates; the runtime supplies supported enums. |
| cost | Fixed field count without clocks or mutation. |
| Design | [docs/maintenance_cost.md](../../../../maintenance_cost.md), [include/crown/runtime/maintenance_cost.hpp](../../../../../include/crown/runtime/maintenance_cost.hpp), [build/verification/v58-b04-design-review-v1/README.md](../../../../../build/verification/v58-b04-design-review-v1/README.md) |

## B0012

[Lines 77–79](../../../../../examples/component-planning/main.cpp#L77); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L77-L79:sha256:270f1a3412af3587ad1e868b419a05d38fdd87a5e154900abbb58ab58e9ad175
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | State the distinct logical-grant/native-byte/ordinary-presentation accounting boundaries. |
| inputs / outputs | Source comments provide inspection context, no executable inputs/outputs. |
| invariants | Finite work/content grants do not become wall time or whole-process memory guarantees. |
| ownership | No owned runtime payload. |
| failure | No executable failure path. |
| cost | No runtime effect; substantive cost is assigned by the Request methods below. |
| Design | [docs/measurement.md](../../../../measurement.md), [build/verification/v58-b04-design-review-v1/README.md](../../../../../build/verification/v58-b04-design-review-v1/README.md) |

## B0013

[Lines 80–98](../../../../../examples/component-planning/main.cpp#L80); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L80-L98:sha256:3074ad1258756afd806c59c1a4bc9f6dfc149a108a20cc0c97cd14f4cd7dfc40
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Hold resolved finite experiment options and construct existing public owner/grant records. |
| inputs / outputs | Physical options and scalar/context grants produce rank limits, CandidateLimits and maintenance-only DeltaOptions. |
| invariants | C05 event-cost is not enabled. Native observation is off; C01 collection is explicitly configured by each replay. Candidate/planner grants are not a shared global memory cap. |
| ownership | Request owns its PhysicalOptions/context. Returned option records are copied/moved into their actual native owner; independent owners have independent explicitly reported caps. |
| failure | Native creation/admission failures remain native errors; this aggregate adds no retry/catch framework. |
| cost | Cold scalar/option copies; later runtime/account construction and lowerings retain their documented costs. |
| Design | [docs/measurement.md](../../../../measurement.md), [build/verification/v58-b04-design-review-v1/README.md](../../../../../build/verification/v58-b04-design-review-v1/README.md), [docs/maintenance_cost.md](../../../../maintenance_cost.md), [include/crown/runtime/maintenance_cost.hpp](../../../../../include/crown/runtime/maintenance_cost.hpp), [build/verification/v58-b04-design-review-v1/README.md](../../../../../build/verification/v58-b04-design-review-v1/README.md) |

## B0014

[Lines 99–120](../../../../../examples/component-planning/main.cpp#L99); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L99-L120:sha256:47c5190d8e2b24145af417e85b01970817fb76709f56c0b3ee301860681cf18a
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Admit a closed versioned request and resolve all finite defaults. |
| inputs / outputs | JSON object with required version/options/context/demand and optional grants produces Request. |
| invariants | Unknown top-level keys reject; sample offset must be below period. With bounded operands, max_events*repetitions*plan_limit is at most65536; future demand is not inferred from evaluation. |
| ownership | Request owns copied options/context; input JSON remains caller-owned for report/demand parsing. |
| failure | Wrong shape/key/type/range, missing required field or unsupported physical options throws; malformed requests cannot produce choices. |
| cost | O(number of request keys/options bytes) checks and cold ordinary allocations. Limits bound selected resource dimensions, not all parser/JSON allocations. |
| Design | [docs/measurement.md](../../../../measurement.md), [build/verification/v58-b04-design-review-v1/README.md](../../../../../build/verification/v58-b04-design-review-v1/README.md) |

## B0015

[Lines 121–124](../../../../../examples/component-planning/main.cpp#L121); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L121-L124:sha256:88f3d41d65da051743e6235a815cca31cccbead79e62119a4e33a21e7725f274
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Serialize and flush exactly one bounded successful report. |
| inputs / outputs | Complete JSON report produces one stdout JSON line; it returns only if flush succeeds. |
| invariants | At most64MiB encoded report bytes are accepted. A buffered output failure cannot return success. |
| ownership | dump creates a separate ordinary owning encoded string; the caller retains the JSON graph until return. |
| failure | Encoding/size/stream failures throw to main. Partial external stdout may exist on I/O failure; no complete success is claimed. |
| cost | O(report bytes) serialization/copy/write and blocking flush. The size check follows dump and does not cap pre-encoding temporary memory. |
| Design | [docs/measurement.md](../../../../measurement.md), [build/verification/v58-b04-design-review-v1/README.md](../../../../../build/verification/v58-b04-design-review-v1/README.md) |

## B0016

[Lines 125–127](../../../../../examples/component-planning/main.cpp#L125); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L125-L127:sha256:d5f36cb28f347596f4b8ab6ad77184648f60f04eea95d5d81b60607f834da958
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Document the certificate-witness versus experiment-upper boundary before artifact encoding. |
| inputs / outputs | Source comments describe V2/V3 semantics, no executed inputs/outputs. |
| invariants | V3 is upper-only and never a MinimumHeightCandidate; the original certificate witness stays unchanged. |
| ownership | No payload ownership. |
| failure | No executable failure path. |
| cost | No runtime effect. |
| Design | [docs/candidate_alternatives.md](../../../../candidate_alternatives.md), [include/crown/planner/candidates.hpp](../../../../../include/crown/planner/candidates.hpp), [build/verification/v58-b04-design-review-v1/README.md](../../../../../build/verification/v58-b04-design-review-v1/README.md), [docs/meta_candidate_adapter.md](../../../../meta_candidate_adapter.md), [docs/meta_decompositions.md](../../../../meta_decompositions.md), [exact paper reference](https://arxiv.org/pdf/2301.04003v2), [exact paper reference](https://arxiv.org/pdf/2603.15465v2), [build/verification/v58-b04-design-review-v1/README.md](../../../../../build/verification/v58-b04-design-review-v1/README.md) |

## B0017

[Lines 128–132](../../../../../examples/component-planning/main.cpp#L128); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L128-L132:sha256:492de72468fec3d1158fdb6d07e2186d6a5a2a91ecf3122a4e99cb3d25105089
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Export the actual independently lowered physical tree together with the unchanged original certificate. |
| inputs / outputs | PhysicalPlan, typed-origin certificate JSON and minimum flag produce experimental V2 or V3 DTO. |
| invariants | V2 uses independently_checked_equal_height_upper_v1 for genuine checked minimum members. V3 uses independently_checked_original_lower_actual_upper_v1 and is only a checked actual upper with independently proved original lower. Editable JSON conveys no proof authority; receiver independently rebuilds/replays. |
| ownership | Returned JSON owns physical/certificate copies and may duplicate large metadata; no proof handle is modified. |
| failure | Serialization/allocation errors propagate. Receiver rejection is distinct from this cold serialization succeeding. |
| cost | Full physical/certificate export scales with source/tree/proof bytes; no update-path overhead or constant-cost claim. |
| Design | [docs/candidate_alternatives.md](../../../../candidate_alternatives.md), [include/crown/planner/candidates.hpp](../../../../../include/crown/planner/candidates.hpp), [build/verification/v58-b04-design-review-v1/README.md](../../../../../build/verification/v58-b04-design-review-v1/README.md), [docs/meta_candidate_adapter.md](../../../../meta_candidate_adapter.md), [docs/meta_decompositions.md](../../../../meta_decompositions.md), [exact paper reference](https://arxiv.org/pdf/2301.04003v2), [exact paper reference](https://arxiv.org/pdf/2603.15465v2), [build/verification/v58-b04-design-review-v1/README.md](../../../../../build/verification/v58-b04-design-review-v1/README.md) |

## B0018

[Lines 133–137](../../../../../examples/component-planning/main.cpp#L133); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L133-L137:sha256:51e84697e26e491daa524c246575b16d4d8f80c1dc1321501e6cd0c0a93a70d2
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Record actual candidate topology sizes for planning/structure comparisons. |
| inputs / outputs | Owning proposed/checked tree produces node count, generalized count and maximum child fanout. |
| invariants | These are literal shape diagnostics, not search completeness, height authority or data-dependent runtime fanout. |
| ownership | Borrows tree nodes/children and returns scalar JSON. |
| failure | JSON allocation failure propagates; existing native trees supply readable metadata. |
| cost | O(tree nodes) plus scalar JSON allocations; it reads child-vector sizes without traversing runtime records. |
| Design | [docs/measurement.md](../../../../measurement.md), [build/verification/v58-b04-design-review-v1/README.md](../../../../../build/verification/v58-b04-design-review-v1/README.md) |

## B0019

[Lines 138–144](../../../../../examples/component-planning/main.cpp#L138); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L138-L144:sha256:22e5a783c772b4b49ac911bd4bc697d8e390bab8e6e448b87f2da01ab5521bf2
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Advance one actual candidate provider to the retained-count request or its first non-quantum resource/terminal stop. |
| inputs / outputs | Exclusive provider and finite count mutate its cursor/progress and retained candidate prefix. |
| invariants | candidate_ready and quantum stops continue; count reached is not exhaustion. No resource raise, alternate-family cache seed or hidden fallback is performed. |
| ownership | Provider retains the original proof, generator and immutable candidates; this helper borrows it exclusively. |
| failure | Non-quantum stops remain in actual progress. Native noexcept allocation/internal stops are not reclassified as successful exhaustion. |
| cost | Potentially exponential cold enumeration under existing work/depth/record/cell/candidate grants; no total CPU/byte bound follows. |
| Design | [docs/candidate_alternatives.md](../../../../candidate_alternatives.md), [include/crown/planner/candidates.hpp](../../../../../include/crown/planner/candidates.hpp), [build/verification/v58-b04-design-review-v1/README.md](../../../../../build/verification/v58-b04-design-review-v1/README.md) |

## B0020

[Lines 145–145](../../../../../examples/component-planning/main.cpp#L145); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L145-L145:sha256:ff6f6a0cc8b75bfb95ab8b1450633a3741c4c06c7374d390bcec106478c818cd
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Keep an external experiment family ID beside its actual immutable provider snapshot and report. |
| inputs / outputs | Owning ID, actual CandidateSnapshot and JSON produce a retained family record. |
| invariants | Exact versus residual versus meta IDs do not rewrite CandidateFamily/provenance. Two finite-proposal batches remain distinct external experiment families. |
| ownership | Owns ordinary ID/report and shared immutable snapshot handles; no live cursor is shared. |
| failure | Construction/copying ordinary report strings/JSON can allocate and fail. |
| cost | Handle moves are cheap; JSON/source/proof ownership and eventual destruction are separate cold costs. |
| Design | [docs/candidate_alternatives.md](../../../../candidate_alternatives.md), [include/crown/planner/candidates.hpp](../../../../../include/crown/planner/candidates.hpp), [build/verification/v58-b04-design-review-v1/README.md](../../../../../build/verification/v58-b04-design-review-v1/README.md) |

## B0021

[Lines 146–151](../../../../../examples/component-planning/main.cpp#L146); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L146-L151:sha256:9be5f5cf044de63188732a1bf00be7655443e59cb3c61bc05b1c20b601624d7e
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Drain and snapshot a concrete provider while preserving its typed family/proof and live progress report. |
| inputs / outputs | Owned provider, external ID, request and preparation JSON produce Family. |
| invariants | Admission clock surrounds only provider advances, not snapshot/report serialization or upstream preparation; actual completion is retained, never inferred from count. |
| ownership | Owns provider until snapshot/report construction completes; returned snapshot retains published candidates after provider destruction. |
| failure | Native provider stops remain explicit; snapshot/JSON admission allocation failures propagate. |
| cost | Enumeration plus separately excluded cold snapshot/IO copies and provider cleanup. Upstream preparation cost remains separately reported. |
| Design | [docs/candidate_alternatives.md](../../../../candidate_alternatives.md), [include/crown/planner/candidates.hpp](../../../../../include/crown/planner/candidates.hpp), [build/verification/v58-b04-design-review-v1/README.md](../../../../../build/verification/v58-b04-design-review-v1/README.md) |

## B0022

[Lines 152–164](../../../../../examples/component-planning/main.cpp#L152); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L152-L164:sha256:4dd4f5ee2a39b385b45f010fcdae6eea72aa7f97b26aeb3e7b840d70b4147e7a
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Serialize C04 preparation diagnostics with each resource/coverage boundary intact. |
| inputs / outputs | Actual MetaCandidateReport produces construction/metadata/enumeration/mapping usage, stops and coverage JSON. |
| invariants | Upstream ordinary/fiber completion is distinct from finite-provider admission. Scope excludes unary-generalized shapes/global cost guarantees. Diagnostic booleans are not proof tokens. |
| ownership | Reads the adapter-owned report before provider move; returns ordinary JSON. |
| failure | Allocation/serialization errors propagate; unsupported or partial native stops are preserved. |
| cost | Fixed number of counter/status fields; underlying possibly exponential work belongs to C04 preparation. |
| Design | [docs/meta_candidate_adapter.md](../../../../meta_candidate_adapter.md), [docs/meta_decompositions.md](../../../../meta_decompositions.md), [exact paper reference](https://arxiv.org/pdf/2301.04003v2), [exact paper reference](https://arxiv.org/pdf/2603.15465v2), [build/verification/v58-b04-design-review-v1/README.md](../../../../../build/verification/v58-b04-design-review-v1/README.md) |

## B0023

[Lines 165–173](../../../../../examples/component-planning/main.cpp#L165); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L165-L173:sha256:0dc591674ebd1459bc5876adeabd69c1c7a686fc353da1fd48e2420a90d4484d
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Translate an occurrence-labelled rooted ordinary join tree into an unchecked all-native CROWN proposal. |
| inputs / outputs | Validated query and actual meta::enumerate JoinTree produce FreeConnexTree. |
| invariants | Each original occurrence gets exactly one native node, including equal scopes/self aliases; scopes contain variable terms only. Parent/root indices come from the independently checked ordinary enumerator. P02 still decides head/Connex validity before any executable export. |
| ownership | Owns new IDs/scopes/child vectors; borrows query/join only during construction. |
| failure | Container/scalar allocation failures propagate. This helper does not admit arbitrary edited parent arrays and does not itself certify a tree. |
| cost | O(atom terms plus ordinary edges) traversal with ordered scope insertions and ordinary heap allocation; width/scalar costs remain explicit. |
| Design | [docs/meta_candidate_adapter.md](../../../../meta_candidate_adapter.md), [docs/meta_decompositions.md](../../../../meta_decompositions.md), [exact paper reference](https://arxiv.org/pdf/2301.04003v2), [exact paper reference](https://arxiv.org/pdf/2603.15465v2), [build/verification/v58-b04-design-review-v1/README.md](../../../../../build/verification/v58-b04-design-review-v1/README.md) |

## B0024

[Lines 174–176](../../../../../examples/component-planning/main.cpp#L174); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L174-L176:sha256:e448ceeeddf44fa0b53844dbf558d73a749924b4869d887aa46ca1a79d48a058
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | State the actual-owner training and retained-as-of profile boundary. |
| inputs / outputs | Comments introduce the Training carrier and train operation. |
| invariants | Every cost profile is captured from that candidate actual physical owner; stale profiles are not edited to become current. |
| ownership | No executable ownership change. |
| failure | No executable failure path. |
| cost | No runtime effect. |
| Design | [docs/maintenance_cost.md](../../../../maintenance_cost.md), [include/crown/runtime/maintenance_cost.hpp](../../../../../include/crown/runtime/maintenance_cost.hpp), [build/verification/v58-b04-design-review-v1/README.md](../../../../../build/verification/v58-b04-design-review-v1/README.md) |

## B0025

[Lines 177–177](../../../../../examples/component-planning/main.cpp#L177); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L177-L177:sha256:09b3734756811438a7ebe078245709e288f27bf028ed1fa85f5e96e293955d8d
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Retain one optional genuine candidate-bound profile beside its training/freshness diagnostics. |
| inputs / outputs | Factory-produced optional Profile and owning JSON produce Training. |
| invariants | Missing profile remains missing; report fields do not create observation authority. |
| ownership | The immutable Profile retains its original funded owner/evidence after runtime destruction; JSON is ordinary separate storage. |
| failure | Handle/report construction allocation failure propagates. |
| cost | Profile handle transfer plus ordinary JSON ownership; last release may destroy retained funded payload. |
| Design | [docs/maintenance_cost.md](../../../../maintenance_cost.md), [include/crown/runtime/maintenance_cost.hpp](../../../../../include/crown/runtime/maintenance_cost.hpp), [build/verification/v58-b04-design-review-v1/README.md](../../../../../build/verification/v58-b04-design-review-v1/README.md) |

## B0026

[Lines 178–208](../../../../../examples/component-planning/main.cpp#L178); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L178-L208:sha256:ced393fcb403ec2b4965047c72cb7062fc29f402d98151329801671c4d09fb7c
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Replay the complete bounded training trace on this candidate and capture full, sampled, stale-prefix or disabled observations. |
| inputs / outputs | Family snapshot/index, matching lowered plan, training bytes, request and variant produce optional cost Profile and actual capture/revalidation diagnostics. |
| invariants | All runtimes start empty with maintenance mode/observation off. Stale capture happens at the requested prefix before actual suffix events; prefix at/after EOF may actually be fresh and is_stale reports that. No edited sampled/census handle or current install is constructed. |
| ownership | Local DeltaRuntime/reader/input own mutation state; profile retains immutable funded snapshots after owner teardown. Temporary epochs/pending tokens die before later capture/update. |
| failure | Oversized/empty training trace or native admission/update failure rejects the command. Capture stops remain optional/unavailable; absent stats never become zero observations. Native commit/rollback semantics remain unchanged. |
| cost | Four cold replay variants per retained candidate, bounded events/owner memory. Real native updates plus capture/revalidation scans/JSON cost occur outside benchmark timing; no new production per-update hooks. |
| Design | [docs/maintenance_cost.md](../../../../maintenance_cost.md), [include/crown/runtime/maintenance_cost.hpp](../../../../../include/crown/runtime/maintenance_cost.hpp), [build/verification/v58-b04-design-review-v1/README.md](../../../../../build/verification/v58-b04-design-review-v1/README.md) |

## B0027

[Lines 209–212](../../../../../examples/component-planning/main.cpp#L209); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L209-L212:sha256:81a6803a554f4d7c265f499ad745e5f29e9dae10a9d00dad459926cb10f8c126
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Declare the exact measured phase and required full-feature calibration scope. |
| inputs / outputs | Comments constrain measure_calibration below. |
| invariants | Native begin/prepare/commit/epoch cleanup is measured; decode, feature capture, setup, fitting, output and durability are excluded. Full census is required to call features. |
| ownership | No executable payload ownership. |
| failure | No executable failure path. |
| cost | No runtime effect. |
| Design | [docs/maintenance_cost.md](../../../../maintenance_cost.md), [include/crown/runtime/maintenance_cost.hpp](../../../../../include/crown/runtime/maintenance_cost.hpp), [build/verification/v58-b04-design-review-v1/README.md](../../../../../build/verification/v58-b04-design-review-v1/README.md) |

## B0028

[Lines 213–235](../../../../../examples/component-planning/main.cpp#L213); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L213-L235:sha256:d641f75c30d83b6518747e8ed38bc7e70e22c892638c07822fafe225640857af
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Measure one pooled set of actual maintenance-only native phases with complete committed census feature differences. |
| inputs / outputs | Unique lowered plans, calibration bytes and bounded request produce raw per-event plan/repetition/sequence/features/nanoseconds observations. |
| invariants | The pool is measured once, not once per statistics/family variant. Every phase contains exactly one physical input and unchanged runtime modes; selected native counters cannot regress. EventReader peek is outside the timer; epoch cleanup is inside. No held-out trace is opened. |
| ownership | Each replay owns a fresh empty runtime/reader; raw observations own ordinary numeric JSON, not borrowed counter snapshots. |
| failure | Missing exact features, mode/counter inconsistency, empty/oversized trace, runtime/resource/allocation failures reject the command; root preserves failure records. No fabricated feature vector or rate fallback. |
| cost | At most event_limit*repetitions*plan_limit&lt;=65536 measured events plus explicit capture/JSON overhead. Native limits and input byte limits are separate; fitting/rank are later cold work. |
| Design | [docs/maintenance_cost.md](../../../../maintenance_cost.md), [include/crown/runtime/maintenance_cost.hpp](../../../../../include/crown/runtime/maintenance_cost.hpp), [build/verification/v58-b04-design-review-v1/README.md](../../../../../build/verification/v58-b04-design-review-v1/README.md) |

## B0029

[Lines 236–249](../../../../../examples/component-planning/main.cpp#L236); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L236-L249:sha256:4598eca1b71b61ce95b62f86e1fe7dad17c233e2a7b283fff56f947e91a6efe1
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Admit locally measured or explicitly imported frozen maintenance observation vectors for fitting. |
| inputs / outputs | Nonempty JSON array&lt;=65536 with exact-width unit vectors and nonnegative elapsed_ns produces owning FitObservation vector. |
| invariants | base_input is exactly1 and annotation/output/checkpoint/encoding units are0. Imported numbers remain caller-supplied measurements, not independently authenticated native facts. No estimate is fabricated from an unavailable coefficient. |
| ownership | Owns ordinary numeric observations copied from raw JSON; fit later copies funded data into its receiving account. |
| failure | Wrong count/width/type/domain/maintenance scope throws; allocation failures propagate. |
| cost | O(observations*component_count) scalar checks/copy and ordinary vector allocation; fixed22component width follows current cost API. |
| Design | [docs/maintenance_cost.md](../../../../maintenance_cost.md), [include/crown/runtime/maintenance_cost.hpp](../../../../../include/crown/runtime/maintenance_cost.hpp), [build/verification/v58-b04-design-review-v1/README.md](../../../../../build/verification/v58-b04-design-review-v1/README.md) |

## B0030

[Lines 250–264](../../../../../examples/component-planning/main.cpp#L250); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L250-L264:sha256:b4f8d40639ffb4f324385fc31ff8646e2aa0621446db02943a8932c454b40d31
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Render the actual pooled calibration attempt, exact coefficients and fit diagnostics. |
| inputs / outputs | CalibrationAttempt produces actual stop/usage plus coefficients and numerical rank/residual/underdetermination if published. |
| invariants | Missing columns remain null; fitted rates are linear attributions, not isolated component measurements, confidence guarantees or complete CPU predictions. |
| ownership | Reads retained immutable calibration; report owns ordinary JSON copies of coefficients/diagnostics. |
| failure | An unpublished fit returns only its actual stop; serialization/allocation failure rejects the command. |
| cost | O(component_count) report construction; fitting work is not repeated by this rendering helper. |
| Design | [docs/maintenance_cost.md](../../../../maintenance_cost.md), [include/crown/runtime/maintenance_cost.hpp](../../../../../include/crown/runtime/maintenance_cost.hpp), [build/verification/v58-b04-design-review-v1/README.md](../../../../../build/verification/v58-b04-design-review-v1/README.md) |

## B0031

[Lines 265–279](../../../../../examples/component-planning/main.cpp#L265); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L265-L279:sha256:3ddf6a9872607ea839ac0a89fff48ff5c455a22808f460053679c5231efa9d9c
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Run genuine C02 height or committed-input-depth ranking on exactly this snapshot. |
| inputs / outputs | Actual snapshot, receiving account, optional genuine Evidence, policy and limits produce explicit stop/reasons/scores/choice JSON. |
| invariants | Fallback is require_evidence. Depth is a conditional as-of score; the report does not assert current owner admission. Decimal exact scores remain strings, and no slots proxy is relabelled C03. |
| ownership | rank_with_account owns funded score/evidence data until serialization; returned JSON owns presentation copies. |
| failure | Native resource/evidence failures remain no-result stops; no successful substitute choice is silently inserted. JSON allocation failure propagates. |
| cost | Bounded native candidate scans/exact arithmetic plus explicit report copy. No provider advancement, proof construction, cache mutation or runtime installation. |
| Design | [docs/ranking.md](../../../../ranking.md), [include/crown/planner/ranking.hpp](../../../../../include/crown/planner/ranking.hpp), [build/verification/v58-b04-design-review-v1/README.md](../../../../../build/verification/v58-b04-design-review-v1/README.md) |

## B0032

[Lines 280–293](../../../../../examples/component-planning/main.cpp#L280); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L280-L293:sha256:ee149ee64898258c013fe79ded11b589e85dea7021681aa7400171a4b1824058
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Export every actual C03 candidate decomposition without selecting or suppressing unknown candidates. |
| inputs / outputs | Cost Attempt yields stop/usage and all retained candidate key/ratio/issue/term/confidence/as-of memory records when Result exists. |
| invariants | Null ratios and issue bits stay visible. Memory budget is a separate constraint and future_memory_unknown stays true; as-of requested bytes are neither RSS nor a future feasibility proof. No rational comparison or C05 enablement occurs. |
| ownership | Borrows the funded Result while building ordinary JSON; returned JSON owns its copies after Result destruction. |
| failure | Unpublished native estimates remain actual stops, not empty successful known-zero scores. Serialization/allocation failure propagates. |
| cost | O(retained candidates plus component terms) reporting, decimal/scalar copies and ordinary allocations; native estimation work is separately in usage. |
| Design | [docs/maintenance_cost.md](../../../../maintenance_cost.md), [include/crown/runtime/maintenance_cost.hpp](../../../../../include/crown/runtime/maintenance_cost.hpp), [build/verification/v58-b04-design-review-v1/README.md](../../../../../build/verification/v58-b04-design-review-v1/README.md) |

## B0034

[Lines 295–478](../../../../../examples/component-planning/main.cpp#L295); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L295-L478:sha256:35cb78ff1fba57218fcc4978646cb29c642b83c34829df1b19d36923a487cde7
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Coordinate cold source admission, original proof, honest separate candidate families, ordinary uppers, one shared calibration and conditional statistics/policy exports. |
| inputs / outputs | Exactly five input paths (SQL/catalog/train/calibration/request) produce one flushed versioned report or explicit CLI failure. |
| invariants | No evaluation trace is accepted. Only genuine independently checked original proof authorizes minimum families. Exact/residual/meta identities remain separate; residual exact repair is visible; V3 ordinary uppers cannot enter minimum handles. One pooled full-census calibration is reused; unavailable C03 values remain explicit. C05 maintenance_cost and production runtime code are unchanged. |
| ownership | Local planner owners and immutable handles own their input/proof/frontier; candidate-specific native runtimes and Profiles use their original finite accounts. Model fit/rank/estimate share an explicit receiving account; DTO/JSON/process storage is separately scoped. |
| failure | Limited original proof returns honest progress without candidates. Later native/allocation/IO/schema failures propagate to one main boundary; partial families and published model stops are retained rather than called exhaustive/known-zero. Output flush is checked. |
| cost | Cold potentially exponential bounded planning plus finite calibration/training replays, account capture/scoring and large JSON exports. Setup clocks have named scopes; no global CPU/RSS bound, hot update hook, new rational framework or automatic optimizer policy is added. |
| Design | [docs/measurement.md](../../../../measurement.md), [build/verification/v58-b04-design-review-v1/README.md](../../../../../build/verification/v58-b04-design-review-v1/README.md), [docs/maintenance_cost.md](../../../../maintenance_cost.md), [include/crown/runtime/maintenance_cost.hpp](../../../../../include/crown/runtime/maintenance_cost.hpp), [build/verification/v58-b04-design-review-v1/README.md](../../../../../build/verification/v58-b04-design-review-v1/README.md), [docs/candidate_alternatives.md](../../../../candidate_alternatives.md), [include/crown/planner/candidates.hpp](../../../../../include/crown/planner/candidates.hpp), [build/verification/v58-b04-design-review-v1/README.md](../../../../../build/verification/v58-b04-design-review-v1/README.md), [docs/meta_candidate_adapter.md](../../../../meta_candidate_adapter.md), [docs/meta_decompositions.md](../../../../meta_decompositions.md), [exact paper reference](https://arxiv.org/pdf/2301.04003v2), [exact paper reference](https://arxiv.org/pdf/2603.15465v2), [build/verification/v58-b04-design-review-v1/README.md](../../../../../build/verification/v58-b04-design-review-v1/README.md) |

```text
@source-span:L296-L327:sha256:65b1924edbeb89e0d5e8a57e87afc01451d2cbe71973aad00b4a85c475559656
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Admit exact sources and acquire independently replayed original minimum evidence. |
| inputs / outputs | Bounded five input files produce normalized set SQL, ExactSearch progress and optional real original proof/certificate. |
| invariants | Best-found is not a minimum claim. No-proof terminal/resource stop emits progress only; search counters and actual limits are retained. Typed write_verified_optimum directly returns the original certificate object. |
| ownership | SQL/catalog/trace/request strings are ordinary owned input; ExactSearch owns copied original binding and continuations. |
| failure | Malformed/nonconstant-unsupported source rejects; proof-budget stops return status original_minimum_unavailable, not an invented fallback. |
| cost | Input reading is outside named admission/proof clocks; the outer process clock must charge it. P06 producer/replay ceilings are separate checkpoint grants. |
| Design | [docs/measurement.md](../../../../measurement.md), [build/verification/v58-b04-design-review-v1/README.md](../../../../../build/verification/v58-b04-design-review-v1/README.md), [docs/candidate_alternatives.md](../../../../candidate_alternatives.md), [include/crown/planner/candidates.hpp](../../../../../include/crown/planner/candidates.hpp), [build/verification/v58-b04-design-review-v1/README.md](../../../../../build/verification/v58-b04-design-review-v1/README.md) |

```text
@source-span:L328-L336:sha256:f36c65d6d52af8a705bffe7980e417ed444378397017dda60b761c981edbe678
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Establish common calibration basis and exact-family provider without seeding another family. |
| inputs / outputs | Real original proof creates its lowered witness calibration basis and separate existing P07 provider. |
| invariants | A witness used for common calibration setup does not become an implicit member of residual/meta. Shared proof cost remains separately named. |
| ownership | Calibration plans retain immutable PhysicalPlan handles; the exact family retains its own snapshot/proof. |
| failure | Lowering/provider/snapshot/report failure rejects; actual resource stops remain provider diagnostics. |
| cost | Original witness lowering, provider creation, advance and report/copy costs are cold and distinct; physical-plan dedup scans only the bounded calibration pool. |
| Design | [docs/candidate_alternatives.md](../../../../candidate_alternatives.md), [include/crown/planner/candidates.hpp](../../../../../include/crown/planner/candidates.hpp), [build/verification/v58-b04-design-review-v1/README.md](../../../../../build/verification/v58-b04-design-review-v1/README.md), [docs/maintenance_cost.md](../../../../maintenance_cost.md), [include/crown/runtime/maintenance_cost.hpp](../../../../../include/crown/runtime/maintenance_cost.hpp), [build/verification/v58-b04-design-review-v1/README.md](../../../../../build/verification/v58-b04-design-review-v1/README.md) |

```text
@source-span:L338-L355:sha256:58fd2cf0e70c5d9a69f92aa15bd29c319c3aac3e0ffa715ec38d0b5af453684a
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Expose bounded residual search, actual repair provenance and its one finite proposal. |
| inputs / outputs | Original source plus ResidualOptions yield actual progress, possible checked upper and from_proposals family. |
| invariants | Both residual paths may run exact fallback; progress/origin/exact scope remain explicit. Taller upper exports as V3 and is rejected by minimum-provider height admission, never silently relabelled minimum. |
| ownership | Residual owner owns trace/workers; exported checked residual/progress and immutable finite candidates retain actual original binding. |
| failure | Resource stop returns only actual available candidate/status. Upper below proven original height is an invariant failure. No normal-form/exact seed is substituted. |
| cost | Residual construction plus delegated exact work, finite admission and cold IO are retained; no pure-heuristic cost or paper unconditional-height shortcut is claimed. |
| Design | [docs/candidate_alternatives.md](../../../../candidate_alternatives.md), [include/crown/planner/candidates.hpp](../../../../../include/crown/planner/candidates.hpp), [build/verification/v58-b04-design-review-v1/README.md](../../../../../build/verification/v58-b04-design-review-v1/README.md), [docs/residual_candidates.md](../../../../residual_candidates.md) |

```text
@source-span:L357-L368:sha256:fb94c14fb3573a22a74826a7ca312048391d3b530dab7afab4204dbf68972c47
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Prepare the real bounded paper/local-inverse-fiber meta family and retain actual P02 admission completion. |
| inputs / outputs | Real original proof plus separate construction/enumeration/mapping/admission limits yield report and optional finite provider. |
| invariants | Combined normalized exhaustion requires both upstream completeness booleans and actual admitted provider exhaustion. Move does not let a mutable diagnostic manufacture authority. No hidden fallback. |
| ownership | Prepared adapter owns completed drafts/provider; Family takes actual provider and snapshots retained checked handles. |
| failure | Unsupported/limited preparation remains meta_unavailable or partial scope with actual stops; admission/resource failures do not become complete coverage. |
| cost | Possibly exponential cold stages retain separate work/cells/fragments/depth/output limits; scope is normalized no-unary original minimum, not global cost. |
| Design | [docs/meta_candidate_adapter.md](../../../../meta_candidate_adapter.md), [docs/meta_decompositions.md](../../../../meta_decompositions.md), [exact paper reference](https://arxiv.org/pdf/2301.04003v2), [exact paper reference](https://arxiv.org/pdf/2603.15465v2), [build/verification/v58-b04-design-review-v1/README.md](../../../../../build/verification/v58-b04-design-review-v1/README.md), [docs/candidate_alternatives.md](../../../../candidate_alternatives.md), [include/crown/planner/candidates.hpp](../../../../../include/crown/planner/candidates.hpp), [build/verification/v58-b04-design-review-v1/README.md](../../../../../build/verification/v58-b04-design-review-v1/README.md) |

```text
@source-span:L370-L392:sha256:4b86ba052f03ab2569ad72814b710c6e1d8dee48bf6f5f784442273db1310e9e
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Export all-root ordinary proposals as independently checked upper-only comparison arms. |
| inputs / outputs | Actual metadata construction and all_roots enumeration produce native-only proposals, P02 rejections or V3 physical uppers. |
| invariants | Every exported ordinary tree passes original-binding P02 and actual lowering; actualheight&gt;=independent original h*. Rejection rules remain visible; ordinary exhaustion means ordinary enumerator completion, not generalized/CROWN-root admission completeness. |
| ownership | Temporary unchecked trees and validation reports own ordinary storage; artifact JSON copies actual checked physical plans/certificate. |
| failure | P02-invalid roots are retained as diagnostic rejections. Resource/unsupported enumeration stops remain explicit; no nullary or cyclic output is fabricated. |
| cost | Separate metadata/enumeration/P02/lowering/JSON cost; all-roots mode can emit n rootings per ordinary tree under finite output cap. |
| Design | [docs/meta_candidate_adapter.md](../../../../meta_candidate_adapter.md), [docs/meta_decompositions.md](../../../../meta_decompositions.md), [exact paper reference](https://arxiv.org/pdf/2301.04003v2), [exact paper reference](https://arxiv.org/pdf/2603.15465v2), [build/verification/v58-b04-design-review-v1/README.md](../../../../../build/verification/v58-b04-design-review-v1/README.md), [docs/candidate_alternatives.md](../../../../candidate_alternatives.md), [include/crown/planner/candidates.hpp](../../../../../include/crown/planner/candidates.hpp), [build/verification/v58-b04-design-review-v1/README.md](../../../../../build/verification/v58-b04-design-review-v1/README.md) |

```text
@source-span:L394-L416:sha256:b9185c57d8f975e4c6193c23b6bf3fe22ff80fea0ca9334a922e0955011e8fd1
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Bind exported minimum artifacts and future demand to actual original candidate/source identities. |
| inputs / outputs | Every actual snapshot member yields V2 artifact/key/provenance/shape; declared source-table/op demand becomes a complete vector. |
| invariants | No cross-family cached prefix is installed. Duplicate/foreign/missing demand strata reject, including omitted zero operations. Counts are declared training/horizon assumptions, never held-out facts. |
| ownership | Family snapshots retain checked handles; plans and certificate JSON copies are ordinary compiler/presentation storage. Demand vector owns numeric copies. |
| failure | Lowering/serialization failures propagate; malformed demand rejects the whole export instead of silently changing the objective. |
| cost | Candidate lowering/copy/dedup and O(demand strata) checks are cold setup; calibration-plan limit is independent from candidate-family output count. |
| Design | [docs/candidate_alternatives.md](../../../../candidate_alternatives.md), [include/crown/planner/candidates.hpp](../../../../../include/crown/planner/candidates.hpp), [build/verification/v58-b04-design-review-v1/README.md](../../../../../build/verification/v58-b04-design-review-v1/README.md), [docs/maintenance_cost.md](../../../../maintenance_cost.md), [include/crown/runtime/maintenance_cost.hpp](../../../../../include/crown/runtime/maintenance_cost.hpp), [build/verification/v58-b04-design-review-v1/README.md](../../../../../build/verification/v58-b04-design-review-v1/README.md) |

```text
@source-span:L418-L443:sha256:8d334ba2eea296cf29df8a21b34a5cd5db1d03050b9f4d5748e94b3c549e45b0
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Freeze one context-bound pooled calibration and reuse exactly its observations across all downstream variants. |
| inputs / outputs | Actual fresh mode facts and request/build/query/context identity plus measured or explicit prior raw observations yield one cost::fit attempt. |
| invariants | Prior identity and observation SHA must match; imported measurements remain unremeasured caller claims bound by outer actual provenance. Full census only, one-input maintenance vectors, output demand0, fixed fit options and unchanged compiler/backend/options are explicit. Coefficient digest excludes variable accounting clocks. |
| ownership | A separate native mode owner supplies real modes. Receiving MemoryAccount funds immutable fitted data; raw JSON/observations are separate ordinary copies. |
| failure | Context/hash/vector mismatch rejects; actual fit failure remains no published calibration. No refit on evaluation or on separate stats variants, no missing coefficient=0. |
| cost | One measured pool or identical frozen-data fit plus cold feature/IO/fit overhead; calibration clock includes its local setup/validation and is separate from predicted maintenance phases. |
| Design | [docs/maintenance_cost.md](../../../../maintenance_cost.md), [include/crown/runtime/maintenance_cost.hpp](../../../../../include/crown/runtime/maintenance_cost.hpp), [build/verification/v58-b04-design-review-v1/README.md](../../../../../build/verification/v58-b04-design-review-v1/README.md) |

```text
@source-span:L445-L466:sha256:bc6058f04ca615b026e7252943b4eca9217c3c0d6076373240b71d6d0e77bdb7
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Evaluate all four actual training evidence variants against the same family and frozen calibration. |
| inputs / outputs | Candidate-specific replays produce full/sample/stale/off profiles, native C02 choices and optional C03 decompositions for every snapshot member. |
| invariants | Same fit/context/demand is reused. Native height/depth require_evidence results keep stops. Stale profiles are pure as-of evidence with actual revalidation; no current selection/install. External Fraction/key selection must preserve unknown candidates/fallback scope. |
| ownership | Profiles retain independent original owner accounts; each scoring Attempt owns funded results until ordinary serialization, then releases them. |
| failure | Unpublished captures/estimates remain unavailable; empty finite family remains no_candidates. Native update/admission/IO failures reject and must be retained by the driver. |
| cost | Finite four-variant replay/capture/rank/estimate loops, not measured hot-path work. Evaluation instrumentation is held fixed separately for policy-quality comparisons. |
| Design | [docs/maintenance_cost.md](../../../../maintenance_cost.md), [include/crown/runtime/maintenance_cost.hpp](../../../../../include/crown/runtime/maintenance_cost.hpp), [build/verification/v58-b04-design-review-v1/README.md](../../../../../build/verification/v58-b04-design-review-v1/README.md), [docs/ranking.md](../../../../ranking.md) |

```text
@source-span:L467-L478:sha256:30c7239609d207081f814dbadc52c75a8968f6d0122e2d7dacbb18dc74724c31
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Report cold cost/account scope and publish the conditional export with checked stdout completion. |
| inputs / outputs | Completed reports plus receiving-account statistics produce named timing/memory/qualification fields and one output line. |
| invariants | Model account peak is not whole-process RSS or total candidate-owner memory. Objective is maintenance-only with explicitly zero output/annotation/checkpoint/encoding demand. C05 maintenance_cost remains unsupported. Source readiness is not held-out/B04 acceptance. |
| ownership | JSON owns final presentation copies; runtime/planner/account handles die after report publication in documented cleanup scopes. |
| failure | dump/byte/flush failure rejects; final owner teardown is outside named maintenance/calibration phase and not silently priced by C03. |
| cost | Account statistic scan and report encoding/output are explicit cold costs. External controlled process resource/timing records remain necessary. |
| Design | [docs/measurement.md](../../../../measurement.md), [build/verification/v58-b04-design-review-v1/README.md](../../../../../build/verification/v58-b04-design-review-v1/README.md), [docs/maintenance_cost.md](../../../../maintenance_cost.md), [include/crown/runtime/maintenance_cost.hpp](../../../../../include/crown/runtime/maintenance_cost.hpp), [build/verification/v58-b04-design-review-v1/README.md](../../../../../build/verification/v58-b04-design-review-v1/README.md) |

## B0035

[Lines 479–479](../../../../../examples/component-planning/main.cpp#L479); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L479-L479:sha256:533f16bca7d58f44b3103b92e3485d22cfbb34bbad5ea3f3fa3b5a9dcb24ec89
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Close the exporter implementation namespace without creating public production symbols. |
| inputs / outputs | Source scope boundary has no executable inputs or outputs. |
| invariants | Helpers remain local to this example translation unit. |
| ownership | No payload ownership. |
| failure | No executable failure path. |
| cost | No runtime effect. |
| Design | [docs/measurement.md](../../../../measurement.md), [build/verification/v58-b04-design-review-v1/README.md](../../../../../build/verification/v58-b04-design-review-v1/README.md) |

## B0036

[Lines 480–482](../../../../../examples/component-planning/main.cpp#L480); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L480-L482:sha256:84b7a29503bed9e6247b57a1ca1b9da7238b5e0b51641e851a4b5a1468587d00
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Translate a failed cold export into one visible process failure. |
| inputs / outputs | argc/argv invoke run; normal success returns0, standard exception prints its diagnostic to stderr and returns1. |
| invariants | No catch converts an unavailable estimate or malformed input into a successful candidate/benchmark claim. Release builds keep all require checks active. |
| ownership | Stack unwinding releases local planner/runtime/stream owners; stdout success was explicitly flushed in emit. |
| failure | Catches std::exception at the CLI boundary only. A failure can leave partial external stdout; the outer runner must use exit status and retain stderr rather than parse it as accepted output. |
| cost | One outer exception boundary per process; no per-update exception framework or production handler is added. |
| Design | [docs/measurement.md](../../../../measurement.md), [build/verification/v58-b04-design-review-v1/README.md](../../../../../build/verification/v58-b04-design-review-v1/README.md) |
