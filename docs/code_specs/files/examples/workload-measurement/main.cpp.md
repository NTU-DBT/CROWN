# `examples/workload-measurement/main.cpp` — block usage map

[Source](../../../../../examples/workload-measurement/main.cpp) · [Source index](../../../README.md) · [Subsystem contracts](../../../subsystem_contracts.md) · [Reviewed primitives](../../../primitives.md)

Demonstrate a concrete public workflow and executable invocation using installed/native CROWN interfaces.

Snapshot SHA-256: `bf1d87d4d0567833046d8f07595d8fa979f73445786281988566fc5c9b0e118b`. 310 lines partitioned into 26 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [examples](../../../subsystem_contracts.md#examples). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/cli.md](../../../../cli.md), [docs/native_build.md](../../../../native_build.md), [docs/measurement.md](../../../../measurement.md), [docs/ranking_evaluation.md](../../../../ranking_evaluation.md), [docs/reoptimization.md](../../../../reoptimization.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–30](../../../../../examples/workload-measurement/main.cpp#L1) | Imports dependencies; declares namespace scope; declares aliases; declares values/defaults or compile-time conditions. |  · [reviewed contract](#b0001) |
| [B0002 · 31–31](../../../../../examples/workload-measurement/main.cpp#L31) | Callable definition: void require(bool value,const char* message) | calls Error; guard void require(bool value,const char* message) {if(!value)throw Error("measurement_error",message);} · [reviewed contract](#b0002) |
| [B0003 · 32–32](../../../../../examples/workload-measurement/main.cpp#L32) | Callable definition: U64 add(U64 a,U64 b) | calls require; guard U64 add(U64 a,U64 b) {require(b&lt;=UINT64_MAX-a,"measurement counter overflow");return a+b;}; returns a+b · [reviewed contract](#b0003) |
| [B0004 · 33–36](../../../../../examples/workload-measurement/main.cpp#L33) | Callable definition: U64 ns(Clock::time_point a,Clock::time_point b) | calls count, require; guard require(count&gt;=0,"steady clock regressed");return static_cast&lt;U64&gt;(count);; returns static_cast&lt;U64&gt;(count) · [reviewed contract](#b0004) |
| [B0005 · 37–41](../../../../../examples/workload-measurement/main.cpp#L37) | Callable definition: U64 number(const Json& object,const char* key,U64 maximum) | calls at, require, is_number_integer, is_number_unsigned; guard require(value.is_number_integer() && (!value.is_number_integer() \|\| value.is_number_unsigned() \|\| v…; returns result · [reviewed contract](#b0005) |
| [B0006 · 42–48](../../../../../examples/workload-measurement/main.cpp#L42) | Callable definition: std::string read(const char* path,std::size_t limit) | calls input, require, bool, gcount; guard std::ifstream input(path,std::ios::binary);require(bool(input),"cannot open measurement input");; returns text; 1 loop sites · [reviewed contract](#b0006) |
| [B0007 · 49–49](../../../../../examples/workload-measurement/main.cpp#L49) | Explanatory comments or spacing. | source comment (unverified): // Cold artifact admission keeps the original proof separate from the actual upper. · [reviewed contract](#b0007) |
| [B0008 · 50–54](../../../../../examples/workload-measurement/main.cpp#L50) | Type/record definition: struct Artifact | source comment (unverified): // Cold artifact admission keeps the original proof separate from the actual upper. · [reviewed contract](#b0008) |
| [B0009 · 55–79](../../../../../examples/workload-measurement/main.cpp#L55) | Callable definition: Artifact artifact(const Json& data) | calls require, is_object, at, is_number_integer; guard require(data.is_object() && data.at("schema_version").is_number_integer(),"expected compiled workfl…; returns {std::move(plan),{},false}; {std::move(plan),optimum-&gt;height(),upper_only} · [reviewed contract](#b0009) |
| [B0010 · 80–82](../../../../../examples/workload-measurement/main.cpp#L80) | Callable definition: template&lt;class Values&gt; Json row(const Values& values) | calls Json::array, push_back, io::write_scalar_view; returns result; growth push_back; 1 loop sites · [reviewed contract](#b0010) |
| [B0011 · 83–85](../../../../../examples/workload-measurement/main.cpp#L83) | Callable definition: std::set&lt;std::string&gt; rows(const Json& values) | calls require, insert, dump; guard std::set&lt;std::string&gt; result;for(const auto& value:values)require(result.insert(value.dump()).secon…; returns result; growth insert; 1 loop sites · [reviewed contract](#b0011) |
| [B0012 · 86–88](../../../../../examples/workload-measurement/main.cpp#L86) | Callable definition: Json current(runtime::DeltaRuntime& owner) | calls Json::array, results, next, push_back; returns result; growth push_back; 1 loop sites · [reviewed contract](#b0012) |
| [B0013 · 89–93](../../../../../examples/workload-measurement/main.cpp#L89) | Callable definition: Json memory(const resource::MemoryStatistics& value) | calls ; returns {{@ ,value.limit_bytes},{@ ,value.current.requested_bytes}, · [reviewed contract](#b0013) |
| [B0014 · 94–97](../../../../../examples/workload-measurement/main.cpp#L94) | Callable definition: Json arena(const storage::ArenaStatistics& value) | calls ; returns {{@ ,value.slots},{@ ,value.live_records},{@ ,value.retained_records}, · [reviewed contract](#b0014) |
| [B0015 · 98–100](../../../../../examples/workload-measurement/main.cpp#L98) | Callable definition: Json storage_statistics(const runtime::PhysicalStorageStatistics& value) | calls arena; returns {{@ ,arena(value.source)},{@ ,arena(value.support)},{@ ,value.derivation_keys}} · [reviewed contract](#b0015) |
| [B0016 · 101–105](../../../../../examples/workload-measurement/main.cpp#L101) | Callable definition: const char* availability(runtime::MetricAvailability value) | calls ; returns @; @ · [reviewed contract](#b0016) |
| [B0017 · 106–113](../../../../../examples/workload-measurement/main.cpp#L106) | Callable definition: Json observations(const runtime::ObservationSnapshot& value) | calls Json::object, runtime::observation_registry, metric, std::string; returns result; 1 loop sites · [reviewed contract](#b0017) |
| [B0018 · 114–119](../../../../../examples/workload-measurement/main.cpp#L114) | Callable definition: Json mandatory(const runtime::DeltaMetrics& value) | calls ; returns {{@ ,value.work},{@ ,value.stages},{@ ,value.journal_records}, · [reviewed contract](#b0018) |
| [B0019 · 120–142](../../../../../examples/workload-measurement/main.cpp#L120) | Callable definition: Json workload(const runtime::workload::Snapshot& snapshot) | calls Json::array, descriptors, cells, require; guard require(keys.size()==cells.size(),"workload descriptor mismatch");; returns {{@ ,snapshot.options().mode==runtime::workload::Mode::off?@ :@ },; growth push_back; 1 loop sites · [reviewed contract](#b0019) |
| [B0020 · 143–144](../../../../../examples/workload-measurement/main.cpp#L143) | Explanatory comments or spacing. | source comment (unverified): // External collector writes are not a native durable sink: no WAL or fsync. · [reviewed contract](#b0020) |
| [B0021 · 145–164](../../../../../examples/workload-measurement/main.cpp#L145) | Type/record definition: struct Sink | guard if(active && kind=="file") {descriptor=::open(path,O_WRONLY\|O_CREAT\|O_EXCL\|O_CLOEXEC,0600);require(…; 1 loop sites; source comment (unverified): // External collector writes are not a native durable sink: no WAL or fsync. · [reviewed contract](#b0021) |
| [B0022 · 165–165](../../../../../examples/workload-measurement/main.cpp#L165) | Explanatory comments or spacing. | source comment (unverified): // Host-owned records keep raw calls; their buffers are outside the native query grant. · [reviewed contract](#b0022) |
| [B0023 · 166–172](../../../../../examples/workload-measurement/main.cpp#L166) | Type/record definition: struct Record | source comment (unverified): // Host-owned records keep raw calls; their buffers are outside the native query grant. · [reviewed contract](#b0023) |
| [B0024 · 173–308](../../../../../examples/workload-measurement/main.cpp#L173) | Callable definition: int run(int argc,char** argv) | calls require, io::read_json, read, is_object; guard require(argc==6,"usage: crown_measure_workload COMPILED.json INPUT.jsonl REQUEST.json EXPECTED.json…; returns (c&gt;=@ && c&lt;=@ ) \|\| (c&gt;=@ && c&lt;=@ ); verify?Clock::time_point{}:Clock::now(); growth emplace, emplace_back, insert, make_unique, push_back, reserve; 9 loop sites; source comment (unverified): // This checks digest shape only; the controlled runner verifies the receipt linkage. · [reviewed contract](#b0024) |
| [B0025 · 309–309](../../../../../examples/workload-measurement/main.cpp#L309) | Closes surrounding scope/type. | source comment (unverified): // namespace · [reviewed contract](#b0025) |
| [B0026 · 310–310](../../../../../examples/workload-measurement/main.cpp#L310) | Callable definition: int main(int argc,char** argv) | calls run, what; returns run(argc,argv); 1 · [reviewed contract](#b0026) |

## B0001

[Lines 1–30](../../../../../examples/workload-measurement/main.cpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

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
| Design | [examples/workload-measurement/main.cpp](../../../../../examples/workload-measurement/main.cpp), [cmake/CrownInstall.cmake](../../../../../cmake/CrownInstall.cmake), [docs/native_build.md](../../../../native_build.md), [docs/measurement.md](../../../../measurement.md), [docs/session_lifecycle.md](../../../../session_lifecycle.md), [docs/planner_continuations.md](../../../../planner_continuations.md) |

## B0002

[Lines 31–31](../../../../../examples/workload-measurement/main.cpp#L31); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void require(bool value,const char* message)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Enforce one collector request/measurement invariant. |
| inputs / outputs | Boolean and borrowed constant message; success returns. |
| invariants | Failure is explicit and terminates this collector run, not native retry or input acknowledgment. |
| ownership | No retained borrow; Error owns message text. |
| failure | False throws measurement_error; allocation while forming error can throw. |
| cost | Fixed success check; error construction only on failure. |
| Design | [examples/workload-measurement/main.cpp](../../../../../examples/workload-measurement/main.cpp), [include/crown/api/error.hpp](../../../../../include/crown/api/error.hpp), [docs/measurement.md](../../../../measurement.md), [docs/session_lifecycle.md](../../../../session_lifecycle.md), [docs/planner_continuations.md](../../../../planner_continuations.md) |

## B0003

[Lines 32–32](../../../../../examples/workload-measurement/main.cpp#L32); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
U64 add(U64 a,U64 b)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Add report counters without unsigned wrap. |
| inputs / outputs | Two U64 values; returns exact sum. |
| invariants | Checks b&lt;=UINT64_MAX-a before addition; no saturation is silently presented as an exact count. |
| ownership | Inline scalar values only. |
| failure | Overflow throws measurement_error before counter update. |
| cost | Fixed arithmetic/guard. |
| Design | [examples/workload-measurement/main.cpp](../../../../../examples/workload-measurement/main.cpp), [docs/measurement.md](../../../../measurement.md), [docs/session_lifecycle.md](../../../../session_lifecycle.md), [docs/planner_continuations.md](../../../../planner_continuations.md) |

## B0004

[Lines 33–36](../../../../../examples/workload-measurement/main.cpp#L33); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
U64 ns(Clock::time_point a,Clock::time_point b)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Convert a nonnegative clock interval to report nanoseconds. |
| inputs / outputs | Two steady-clock points; returns duration_cast count as U64. |
| invariants | Verify mode deliberately uses zero points; zero values there are not measured latency. |
| ownership | Copies time points, retains no clock object. |
| failure | Negative converted duration throws measurement_error. |
| cost | Fixed duration conversion; no clock read inside helper. |
| Design | [examples/workload-measurement/main.cpp](../../../../../examples/workload-measurement/main.cpp), [docs/measurement.md](../../../../measurement.md), [docs/session_lifecycle.md](../../../../session_lifecycle.md), [docs/planner_continuations.md](../../../../planner_continuations.md) |

## B0005

[Lines 37–41](../../../../../examples/workload-measurement/main.cpp#L37); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
U64 number(const Json& object,const char* key,U64 maximum)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Read one finite nonnegative collector grant. |
| inputs / outputs | Borrowed request/key and inclusive maximum; returns U64, including zero if caller permits. |
| invariants | Accepts signed nonnegative or unsigned JSON integers, rejects other types/negative/out-of-bound. Caller separately requires positive memory and output-call grants. |
| ownership | Borrows JSON only during lookup/conversion. |
| failure | Missing key/type conversion throws JSON error; invalid numeric grant throws measurement_error. |
| cost | One object lookup, numeric type/value checks; no iteration over events. |
| Design | [examples/workload-measurement/main.cpp](../../../../../examples/workload-measurement/main.cpp), [docs/measurement.md](../../../../measurement.md), [docs/session_lifecycle.md](../../../../session_lifecycle.md), [docs/planner_continuations.md](../../../../planner_continuations.md) |

## B0006

[Lines 42–48](../../../../../examples/workload-measurement/main.cpp#L42); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::string read(const char* path,std::size_t limit)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Read a bounded artifact/input/request/oracle file. |
| inputs / outputs | Borrowed path and byte ceiling; returns owning ordinary binary string. |
| invariants | Accepted accumulated size&lt;=limit; does not make the file/string/report part of the native query account. |
| ownership | Local ifstream closes on unwind; returned string owns bytes. |
| failure | Open/read/limit errors throw measurement_error; string allocation may fail. |
| cost | Linear IO/copy through 4096-byte stack block and growing string. |
| Design | [examples/workload-measurement/main.cpp](../../../../../examples/workload-measurement/main.cpp), [docs/measurement.md](../../../../measurement.md), [docs/session_lifecycle.md](../../../../session_lifecycle.md), [docs/planner_continuations.md](../../../../planner_continuations.md) |

## B0007

[Lines 49–49](../../../../../examples/workload-measurement/main.cpp#L49); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L49-L49:sha256:135e945ec5e2c4d519ca263dc12bf33f079faba6dd0f6f685ec6a0d8d30a1316
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Describe the cold distinction between original proof authority and supplied physical upper. |
| inputs / outputs | A source comment introduces Artifact and artifact(). |
| invariants | The original certificate is retained and replayed; the candidate tree is never substituted into it. |
| ownership | The comment owns no state; the following result owns the admitted plan. |
| failure | No executable admission or handler is installed by this line. |
| cost | No runtime work; the following cold reader pays reconstruction and proof replay. |
| Design | [docs/measurement.md](../../../../measurement.md), [docs/planner_proofs.md](../../../../planner_proofs.md), [docs/physical_plans.md](../../../../physical_plans.md), [Refactor.md §5.4 and §14.1–14.4](../../../../../Refactor.md), [schemas/compiled-experimental-upper-v3.schema.json](../../../../../schemas/compiled-experimental-upper-v3.schema.json) |

## B0008

[Lines 50–54](../../../../../examples/workload-measurement/main.cpp#L50); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L50-L54:sha256:e5acddaf316de8204defbf716271f5e7aa143beaed17b0fe8a64ce4206081e16
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Carry the verified physical artifact and separate original-height/experimental labels to the collector. |
| inputs / outputs | Artifact contains a PhysicalPlan, optional original height and upper_only flag. |
| invariants | Only artifact() constructs results in this translation unit. A constant-false V1 has no original height; upper_only requires a completed original optimum replay. |
| ownership | The result owns its plan; scalar metadata is copied. run borrows the plan while this result remains alive. |
| failure | Plan creation/move follows its ordinary owning API; the struct introduces no retry or exception mechanism. |
| cost | One cold result and fixed scalar metadata; no per-event engine state or new public minimum-candidate type. |
| Design | [docs/measurement.md](../../../../measurement.md), [docs/planner_proofs.md](../../../../planner_proofs.md), [docs/physical_plans.md](../../../../physical_plans.md), [Refactor.md §5.4 and §14.1–14.4](../../../../../Refactor.md), [schemas/compiled-experimental-upper-v3.schema.json](../../../../../schemas/compiled-experimental-upper-v3.schema.json) |

## B0009

[Lines 55–79](../../../../../examples/workload-measurement/main.cpp#L55); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L55-L79:sha256:29b2eea97f17b57561e71971a01aa1fcee1823dc88ded8ad4a69ae39794cac0e
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Admit exact-witness V1, equal-height V2 and explicit experimental-upper V3 through separate height gates. |
| inputs / outputs | Receives one parsed compiled-artifact JSON object; returns an owning Artifact after physical replay and certificate replay. |
| invariants | Exact integer version/closed field count/tag are required. io::read_physical rebuilds the actual source/tree/options and checks all descriptors. CertificateReplay binds and proves the unchanged original query. V3 requires h*&lt;=actual native height; V1/V2 require equality and V1 additionally exact witness equality. Constant false is V1/null only. |
| ownership | JSON is borrowed for this call; decoded plan, claim and replay own their data. Returned plan outlives all local proof scratch, with original_height copied from typed optimum. |
| failure | Wrong format/binding/tree/height, incomplete replay or allocation failure propagates to the existing single CLI catch before owner, sink or successful report publication. Ten-million replay work is a finite admission ceiling, not a successful timeout fallback. |
| cost | Cold JSON decoding, complete physical re-lowering/P02 verification and potentially exponential independent certificate replay allocate host/planner storage. Input file caps and replay defaults remain. No per-update calls or runtime maintenance changes. |
| Design | [docs/measurement.md](../../../../measurement.md), [docs/planner_proofs.md](../../../../planner_proofs.md), [docs/physical_plans.md](../../../../physical_plans.md), [Refactor.md §5.4 and §14.1–14.4](../../../../../Refactor.md), [schemas/compiled-experimental-upper-v3.schema.json](../../../../../schemas/compiled-experimental-upper-v3.schema.json) |

## B0010

[Lines 80–82](../../../../../examples/workload-measurement/main.cpp#L80); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
template<class Values> Json row(const Values& values)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Export one tuple-value range to ordinary JSON scalars. |
| inputs / outputs | Borrowed live value range; returns owning JSON array. |
| invariants | Preserves native scalar codec representation; no native row or proof is constructed. |
| ownership | Input values must remain live during iteration; output copies scalar/text bytes and survives them. |
| failure | Scalar encoding/JSON allocation may throw; caller selects timed or verification scope. |
| cost | Linear fields/string-byte export plus ordinary JSON allocations. |
| Design | [examples/workload-measurement/main.cpp](../../../../../examples/workload-measurement/main.cpp), [include/crown/io/document.hpp](../../../../../include/crown/io/document.hpp), [include/crown/storage/tuple_values.hpp](../../../../../include/crown/storage/tuple_values.hpp), [docs/measurement.md](../../../../measurement.md), [docs/session_lifecycle.md](../../../../session_lifecycle.md), [docs/planner_continuations.md](../../../../planner_continuations.md) |

## B0011

[Lines 83–85](../../../../../examples/workload-measurement/main.cpp#L83); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::set<std::string> rows(const Json& values)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Build duplicate-rejecting canonical row strings for unordered oracle comparison. |
| inputs / outputs | Borrowed JSON row array; returns sorted owning dumped row strings. |
| invariants | Duplicate identical JSON encodings fail rather than being hidden by set comparison; this fixture compares exact-set rows/signed records. |
| ownership | Set owns encoded copies; no native tuple pins remain. |
| failure | Duplicate row throws measurement_error; malformed JSON/allocations may throw. |
| cost | Per-row dump and ordered-set insertion/comparison; used outside active measurement in verification. |
| Design | [examples/workload-measurement/main.cpp](../../../../../examples/workload-measurement/main.cpp), [docs/measurement.md](../../../../measurement.md), [docs/session_lifecycle.md](../../../../session_lifecycle.md), [docs/planner_continuations.md](../../../../planner_continuations.md) |

## B0012

[Lines 86–88](../../../../../examples/workload-measurement/main.cpp#L86); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Json current(runtime::DeltaRuntime& owner)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Enumerate actual committed SQL results for independent verification. |
| inputs / outputs | Exclusive committed DeltaRuntime; returns ordinary JSON array of all result rows. |
| invariants | Cursor leases block mutation until exhaustion/destruction; does not infer current rows from expected fixtures. |
| ownership | Local cursor owns lease and returned storage::Tuple payloads; row() exports ordinary values before each temporary is released. |
| failure | Cursor limits/native allocation/encoding failure unwinds and releases lease; no source acknowledgment occurs here. |
| cost | Full cursor startup/enumeration/termination and scalar JSON copies, not a constant-time snapshot. |
| Design | [examples/workload-measurement/main.cpp](../../../../../examples/workload-measurement/main.cpp), [include/crown/runtime/delta.hpp](../../../../../include/crown/runtime/delta.hpp), [include/crown/runtime/support.hpp](../../../../../include/crown/runtime/support.hpp), [include/crown/storage/layout.hpp](../../../../../include/crown/storage/layout.hpp), [docs/measurement.md](../../../../measurement.md), [docs/session_lifecycle.md](../../../../session_lifecycle.md), [docs/planner_continuations.md](../../../../planner_continuations.md) |

## B0013

[Lines 89–93](../../../../../examples/workload-measurement/main.cpp#L89); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Json memory(const resource::MemoryStatistics& value)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Serialize selected account statistics as numeric report fields. |
| inputs / outputs | Borrowed captured statistics; returns owning JSON object of limit/current/peak/allocation counters. |
| invariants | Requested/payload bytes and cumulative peak remain distinct; not RSS or an independently subtractable phase peak. |
| ownership | Copies only numeric observations; does not retain the account itself. |
| failure | JSON allocation may fail. |
| cost | Fixed field export; no allocator ledger scan is performed by this serializer. |
| Design | [examples/workload-measurement/main.cpp](../../../../../examples/workload-measurement/main.cpp), [include/crown/resource/memory.hpp](../../../../../include/crown/resource/memory.hpp), [docs/measurement.md](../../../../measurement.md), [docs/session_lifecycle.md](../../../../session_lifecycle.md), [docs/planner_continuations.md](../../../../planner_continuations.md) |

## B0014

[Lines 94–97](../../../../../examples/workload-measurement/main.cpp#L94); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Json arena(const storage::ArenaStatistics& value) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Export six existing arena population counters as ordinary JSON. |
| inputs / outputs | ArenaStatistics in; slots/live/retained/pins/free/exhausted counters out. |
| invariants | Counts are populations, not visits or allocator bytes. |
| ownership | JSON owns scalar copies; input borrowed. |
| failure | JSON allocation errors propagate. |
| cost | Fixed fields plus JSON allocations. |
| Design | [examples/workload-measurement/main.cpp](../../../../../examples/workload-measurement/main.cpp), [schemas/workload-measurement-v2.schema.json](../../../../../schemas/workload-measurement-v2.schema.json), [docs/adversarial_scalability.md](../../../../adversarial_scalability.md), Refactor.md:1393-1395 |

## B0015

[Lines 98–100](../../../../../examples/workload-measurement/main.cpp#L98); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Json storage_statistics(const runtime::PhysicalStorageStatistics& value) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Serialize source/support arena samples and derivation-key count. |
| inputs / outputs | PhysicalStorageStatistics in; nested JSON object out. |
| invariants | Formatter does not collect runtime state; caller obtains sample separately and preserves arena separation. |
| ownership | JSON owns copies; input borrowed. |
| failure | JSON allocation errors propagate. |
| cost | Two arena exports and one scalar. |
| Design | [examples/workload-measurement/main.cpp](../../../../../examples/workload-measurement/main.cpp), [schemas/workload-measurement-v2.schema.json](../../../../../schemas/workload-measurement-v2.schema.json), [docs/adversarial_scalability.md](../../../../adversarial_scalability.md), Refactor.md:1393-1395 |

## B0016

[Lines 101–105](../../../../../examples/workload-measurement/main.cpp#L101); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
const char* availability(runtime::MetricAvailability value)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Map optional metric availability to stable report text. |
| inputs / outputs | Enum; returns static available/disabled/unavailable literal. |
| invariants | Default fallback is unavailable; unavailable/disabled values are never upgraded to measured zero. |
| ownership | Returned literal has static lifetime; no allocation. |
| failure | No exception path. |
| cost | Fixed enum switch. |
| Design | [examples/workload-measurement/main.cpp](../../../../../examples/workload-measurement/main.cpp), [include/crown/runtime/observation.hpp](../../../../../include/crown/runtime/observation.hpp), [docs/measurement.md](../../../../measurement.md), [docs/session_lifecycle.md](../../../../session_lifecycle.md), [docs/planner_continuations.md](../../../../planner_continuations.md) |

## B0017

[Lines 106–113](../../../../../examples/workload-measurement/main.cpp#L106); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Json observations(const runtime::ObservationSnapshot& value)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Export the registered optional metrics with their availability and scope. |
| inputs / outputs | Borrowed ObservationSnapshot; one JSON cell per observation_registry descriptor. |
| invariants | Uses last attempt when present; no last attempt plus off marks disabled, otherwise default unavailable. Includes saturation/units/includes/scope verbatim. |
| ownership | Registry strings are borrowed only during ordinary JSON key/value copying; snapshot retains its own actual immutable contexts. |
| failure | JSON/string allocation may fail; absence stays explicit. |
| cost | Linear registry scan and JSON allocation; no fresh trace capture or runtime mutation. |
| Design | [examples/workload-measurement/main.cpp](../../../../../examples/workload-measurement/main.cpp), [include/crown/runtime/observation.hpp](../../../../../include/crown/runtime/observation.hpp), [src/runtime/observation.cpp](../../../../../src/runtime/observation.cpp), [docs/measurement.md](../../../../measurement.md), [docs/session_lifecycle.md](../../../../session_lifecycle.md), [docs/planner_continuations.md](../../../../planner_continuations.md) |

## B0018

[Lines 114–119](../../../../../examples/workload-measurement/main.cpp#L114); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Json mandatory(const runtime::DeltaMetrics& value)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Export mandatory epoch work and spool/replay counters. |
| inputs / outputs | Borrowed captured DeltaMetrics; returns selected numeric JSON fields. |
| invariants | Counters keep their native domains and inclusive relationships; serializer does not add them into a claimed disjoint total. |
| ownership | Copies numbers only, owns ordinary JSON object. |
| failure | JSON allocation may fail. |
| cost | Fixed selected-field construction. |
| Design | [examples/workload-measurement/main.cpp](../../../../../examples/workload-measurement/main.cpp), [include/crown/runtime/delta.hpp](../../../../../include/crown/runtime/delta.hpp), [include/crown/runtime/support.hpp](../../../../../include/crown/runtime/support.hpp), [docs/measurement.md](../../../../measurement.md), [docs/session_lifecycle.md](../../../../session_lifecycle.md), [docs/planner_continuations.md](../../../../planner_continuations.md) |

## B0019

[Lines 120–142](../../../../../examples/workload-measurement/main.cpp#L120); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Json workload(const runtime::workload::Snapshot& snapshot)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Export exact recorded C01 descriptors/cells and status. |
| inputs / outputs | Factory-produced retained workload snapshot; checks parallel spans then writes every descriptor/cell and selected metadata/stamp fields. |
| invariants | Preserves saturation/completeness/truncation and collection mode; no arrival rate, confidence, proof or native row authority follows. |
| ownership | Descriptor/cell spans borrow retained snapshot Data. Output owns JSON copies; snapshot handle copies share its actual private shared_ptr Data. |
| failure | Descriptor length mismatch throws measurement_error; JSON/string/array allocation can fail. |
| cost | Linear descriptor/cell/histogram export and ordinary JSON storage; factory workload capture before this call is a separate funded scan/copy. |
| Design | [examples/workload-measurement/main.cpp](../../../../../examples/workload-measurement/main.cpp), [include/crown/runtime/workload_statistics.hpp](../../../../../include/crown/runtime/workload_statistics.hpp), [src/runtime/workload_statistics.cpp](../../../../../src/runtime/workload_statistics.cpp), [docs/measurement.md](../../../../measurement.md), [docs/session_lifecycle.md](../../../../session_lifecycle.md), [docs/planner_continuations.md](../../../../planner_continuations.md) |

## B0020

[Lines 143–144](../../../../../examples/workload-measurement/main.cpp#L143); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L143-L144:sha256:25d11b4e8fef155e50df2dd76642c751da15c46f2a4ee777b3fd58c9930d2e9c
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Explain the adjacent source contract: External collector writes are not a native durable sink: no WAL or fsync. This run-local fd owner is never copied. |
| inputs / outputs | Human-readable source note in; no executable output or checked receipt. |
| invariants | This comment states context or a limitation. It does not itself enforce or prove the described behavior; use the adjacent implementation and its scoped contract. |
| ownership | Source text only; no object or resource lifetime is created. |
| failure | No runtime failure path in this comment; source encoding/comment syntax still belongs to compilation. |
| cost | No runtime operations from the comment. Any work described in the note belongs to the adjacent operation. |
| Design | [examples/workload-measurement/main.cpp](../../../../../examples/workload-measurement/main.cpp), [docs/measurement.md](../../../../measurement.md), [docs/code_review.md](../../../../code_review.md) |

## B0021

[Lines 145–164](../../../../../examples/workload-measurement/main.cpp#L145); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct Sink {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Own one local collector output descriptor and its byte/call accounting. |
| inputs / outputs | Run-local file/discard sink, optional per-record wait and total encoded-byte ceiling. |
| invariants | Used only as a stack-local noncopied object. The type has implicit copy operations that would duplicate its fd integer, so callers must not copy it. Files are not fsynced or a durable native sink. |
| ownership | Owns an opened POSIX fd until explicit close or destructor; string arguments are borrowed only during construction/consume. Scalar byte/call counters are local collector facts. |
| failure | Exclusive open/write/close/limit checks can fail; destructor best-effort closes without throwing. Errors do not roll back already committed volatile epochs or written file prefix. |
| cost | Optional file open, per-row delay/write loop and close; discard still accounts bytes/calls and optional wait. |
| Design | [examples/workload-measurement/main.cpp](../../../../../examples/workload-measurement/main.cpp), [docs/measurement.md](../../../../measurement.md), [docs/session_lifecycle.md](../../../../session_lifecycle.md), [docs/planner_continuations.md](../../../../planner_continuations.md) |

```text
int descriptor=-1;bool enabled{};U64 delay_us{},bytes{},calls{},byte_limit{};
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Store sink resource state and finite collector counters. |
| inputs / outputs | descriptor=-1 means no open file; enabled gates consume; delay_us requests wait; bytes/calls accumulate successful consumes; byte_limit caps encoded bytes. |
| invariants | bytes&lt;=byte_limit is maintained before subtraction; caller bounds delay to 100000 us. Enabled discard has no fd but still counts. |
| ownership | fd integer is an owning resource token in this noncopied local object; other members are inline values. |
| failure | Declarations themselves do not fail; consume performs overflow/limit checks. |
| cost | Fixed inline storage, no per-member heap allocation. |
| Design | [examples/workload-measurement/main.cpp](../../../../../examples/workload-measurement/main.cpp), [docs/measurement.md](../../../../measurement.md), [docs/session_lifecycle.md](../../../../session_lifecycle.md), [docs/planner_continuations.md](../../../../planner_continuations.md) |

```text
Sink(bool active,const std::string& kind,const char* path,U64 delay,U64 limit)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Configure discard/disabled output or exclusively create a file. |
| inputs / outputs | Validated kind, borrowed path, active flag, delay and byte grant; opens file only for active file mode. |
| invariants | O_EXCL prevents overwriting an existing path; mode 0600 and O_CLOEXEC are requested. Verification keeps sink disabled and creates no file. |
| ownership | Acquires fd on successful open; borrows kind/path for call only. |
| failure | Failed open throws measurement_error; no descriptor is retained on failure. |
| cost | One optional POSIX open and fixed initialization; no fsync. |
| Design | [examples/workload-measurement/main.cpp](../../../../../examples/workload-measurement/main.cpp), [docs/measurement.md](../../../../measurement.md), [docs/session_lifecycle.md](../../../../session_lifecycle.md), [docs/planner_continuations.md](../../../../planner_continuations.md) |

```text
~Sink()
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Release an open collector descriptor during normal or exceptional teardown. |
| inputs / outputs | Local live Sink; closes only descriptor&gt;=0. |
| invariants | Destructor never retries, throws or claims durable persistence; explicit close is used for measured success checks. |
| ownership | Releases this object fd; no copying occurs in run. |
| failure | close result is deliberately ignored during destructor cleanup. |
| cost | At most one close syscall; no heap allocation. |
| Design | [examples/workload-measurement/main.cpp](../../../../../examples/workload-measurement/main.cpp), [docs/measurement.md](../../../../measurement.md), [docs/session_lifecycle.md](../../../../session_lifecycle.md), [docs/planner_continuations.md](../../../../planner_continuations.md) |

```text
void consume(const std::string& text)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Consume one encoded output record, including controlled wait and partial-write retry. |
| inputs / outputs | Borrowed encoded string; disabled is no-op, discard counts, file writes complete bytes; updates bytes/calls after successful write loop. |
| invariants | Checks remaining byte grant before waiting/writing. EINTR retries only interrupted writes; positive partial writes advance offset. Empty strings still count/wait when enabled. |
| ownership | Borrows text until return, retains only counts; fd stays owned by Sink. |
| failure | Limit/overflow/zero-or-failed write throws; an already written prefix is not rolled back or retried as a whole record. |
| cost | Requested sleep plus O(bytes) writes, possibly multiple syscalls; discard avoids write syscalls. Counter checks are fixed. |
| Design | [examples/workload-measurement/main.cpp](../../../../../examples/workload-measurement/main.cpp), [docs/measurement.md](../../../../measurement.md), [docs/session_lifecycle.md](../../../../session_lifecycle.md), [docs/planner_continuations.md](../../../../planner_continuations.md) |

```text
void close()
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Close the output file once and surface close failure before success report. |
| inputs / outputs | Live sink; sets descriptor=-1 then checks close result. |
| invariants | Invalidating fd before check prevents destructor double-close after failure; no fsync or retry-after-close is added. |
| ownership | Releases owned fd once; discard/disabled have none. |
| failure | Nonzero close result throws measurement_error after descriptor release; written prefix may remain. |
| cost | At most one close syscall; record writing is outside this helper. |
| Design | [examples/workload-measurement/main.cpp](../../../../../examples/workload-measurement/main.cpp), [docs/measurement.md](../../../../measurement.md), [docs/session_lifecycle.md](../../../../session_lifecycle.md), [docs/planner_continuations.md](../../../../planner_continuations.md) |

## B0022

[Lines 165–165](../../../../../examples/workload-measurement/main.cpp#L165); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L165-L165:sha256:3e0ed366fc27955403427d91b736adc06b141d4caa4e34bff0cbae64c0a20186
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Explain the adjacent source contract: Host-owned records keep raw calls; their buffers are outside the native query grant. |
| inputs / outputs | Human-readable source note in; no executable output or checked receipt. |
| invariants | This comment states context or a limitation. It does not itself enforce or prove the described behavior; use the adjacent implementation and its scoped contract. |
| ownership | Source text only; no object or resource lifetime is created. |
| failure | No runtime failure path in this comment; source encoding/comment syntax still belongs to compilation. |
| cost | No runtime operations from the comment. Any work described in the note belongs to the adjacent operation. |
| Design | [examples/workload-measurement/main.cpp](../../../../../examples/workload-measurement/main.cpp), [docs/measurement.md](../../../../measurement.md), [docs/code_review.md](../../../../code_review.md) |

## B0023

[Lines 166–172](../../../../../examples/workload-measurement/main.cpp#L166); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct Record {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Retain each verify/measure event's statistics and post-ack storage snapshot. Measure later encodes event frames; verify returns a common receipt without those frames. |
| inputs / outputs | Zero-initialized timing/count fields, phase, output-call vector, memory/core/observation snapshots, PhysicalStorageStatistics snapshot and cursor work. |
| invariants | Timings represent explicit scopes and may overlap inclusive active/loop totals; verification uses zero clock values. Storage is a copied collector DTO, not a native owner or slot-visit counter. |
| ownership | Owns std::string/vector and value snapshots including source/support arena counts; copies of owning string/vector can allocate. |
| failure | Default fields do not fail; string/vector growth/copy and JSON conversion can allocate and fail. |
| cost | Both verify and measure retain collector Records and storage values until return; collector timing clocks are zero in verify. Host memory grows with events, output calls and copied observations outside the query account. Only measure materializes frame JSON. Vector moves transfer owned buffers. |
| Design | [examples/workload-measurement/main.cpp](../../../../../examples/workload-measurement/main.cpp), [include/crown/runtime/observation.hpp](../../../../../include/crown/runtime/observation.hpp), [include/crown/runtime/delta.hpp](../../../../../include/crown/runtime/delta.hpp), [docs/measurement.md](../../../../measurement.md), [schemas/workload-measurement-v2.schema.json](../../../../../schemas/workload-measurement-v2.schema.json) |

```text
U64 sequence{},decode{},native{},setup{},enumerate{},encoding{},sink{},release{},epoch_release{},ack{},active{},diagnostics{},output_rows{};
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Store event identity, disjoint phase timings, inclusive active time and output cardinality. |
| inputs / outputs | sequence identifies accepted physical input; timing members are nanoseconds; output_rows counts present cursor/spool values. |
| invariants | active includes decode through acknowledge; individual times must not be added again to active or loop wall. diagnostics is sampled afterward. |
| ownership | Inline U64 values, no retained row/runtime borrow. |
| failure | Population uses checked duration/add helpers; fields alone cannot validate timing quality. |
| cost | Fixed record storage. |
| Design | [examples/workload-measurement/main.cpp](../../../../../examples/workload-measurement/main.cpp), [docs/measurement.md](../../../../measurement.md), [docs/session_lifecycle.md](../../../../session_lifecycle.md), [docs/planner_continuations.md](../../../../planner_continuations.md) |

```text
std::string phase;std::vector<std::pair<U64,bool>> calls;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Own the declared phase label and raw successful/terminal output-call observations. |
| inputs / outputs | Phase copied from request; calls append {nanoseconds,returned_row}, including the final false result. |
| invariants | Labels are caller metadata; calls are bounded by global max_output_calls, not by result row count alone. |
| ownership | Ordinary string/vector own their bytes; copy duplicates buffers and move transfers them. |
| failure | Append/copy may throw allocation; failed measurement is not silently truncated. |
| cost | Memory proportional to label bytes and output calls; this host storage is outside the query account. |
| Design | [examples/workload-measurement/main.cpp](../../../../../examples/workload-measurement/main.cpp), [docs/measurement.md](../../../../measurement.md), [docs/session_lifecycle.md](../../../../session_lifecycle.md), [docs/planner_continuations.md](../../../../planner_continuations.md) |

```text
resource::MemoryStatistics bytes;runtime::DeltaMetrics core;runtime::ObservationSnapshot observation;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Keep diagnostic values taken at explicit commit/post-ack boundaries. |
| inputs / outputs | core is copied at commit; bytes and observation are captured after ack outside active timing. |
| invariants | Native current/cumulative peak and availability/saturation remain distinct from caller allocation/RSS; no independent phase peak is inferred. |
| ownership | Memory/core are value snapshots. ObservationSnapshot retains actual shared immutable context handles and inline summaries, with no mutable row lease. |
| failure | Field copies are declared noexcept/value operations; owner diagnostic API/capture may impose its own guards. |
| cost | Fixed record values plus retained context lifetime; final context release can free native metadata. |
| Design | [examples/workload-measurement/main.cpp](../../../../../examples/workload-measurement/main.cpp), [include/crown/runtime/observation.hpp](../../../../../include/crown/runtime/observation.hpp), [include/crown/resource/memory.hpp](../../../../../include/crown/resource/memory.hpp), [docs/measurement.md](../../../../measurement.md), [docs/session_lifecycle.md](../../../../session_lifecycle.md), [docs/planner_continuations.md](../../../../planner_continuations.md) |

```text
U64 cursor_startup_work{},cursor_result_work{},cursor_termination_work{};
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Keep the full cursor work domains separate. |
| inputs / outputs | Copies cursor metrics before cursor reset; delta/maintenance without cursor keep zeros. |
| invariants | Counters are recorded native work domains, not time predictions or additional disjoint work to add to inclusive runtime totals. |
| ownership | Inline values survive cursor lease release. |
| failure | No allocation or exception in field storage. |
| cost | Fixed three-counter copy. |
| Design | [examples/workload-measurement/main.cpp](../../../../../examples/workload-measurement/main.cpp), [include/crown/runtime/delta.hpp](../../../../../include/crown/runtime/delta.hpp), [include/crown/runtime/support.hpp](../../../../../include/crown/runtime/support.hpp), [docs/measurement.md](../../../../measurement.md), [docs/session_lifecycle.md](../../../../session_lifecycle.md), [docs/planner_continuations.md](../../../../planner_continuations.md) |

```text
runtime::PhysicalStorageStatistics storage{};
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Add a value-initialized storage snapshot to each retained collector Record. |
| inputs / outputs | No input; provides the source/support/derivation-key fields assigned at the diagnostic boundary. |
| invariants | This is collector-owned report data; it does not add a field or callback to the native update engine. |
| ownership | Record owns the value copy. |
| failure | Value initialization does not fail; assignment/API sampling may fail through the caller. |
| cost | Fixed-size value member per recorded event. |
| Design | [examples/workload-measurement/main.cpp](../../../../../examples/workload-measurement/main.cpp), [include/crown/runtime/delta.hpp](../../../../../include/crown/runtime/delta.hpp), [schemas/workload-measurement-v2.schema.json](../../../../../schemas/workload-measurement-v2.schema.json), [docs/adversarial_scalability.md](../../../../adversarial_scalability.md), Refactor.md:1393-1395 |

## B0024

[Lines 173–308](../../../../../examples/workload-measurement/main.cpp#L173); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
int run(int argc,char** argv)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Verify or measure a bounded volatile native workload and emit arena-aware raw report v2. |
| inputs / outputs | COMPILED INPUT REQUEST EXPECTED\|- SINK_PATH; verify compares the independent oracle without timing/sink, while measure emits a &lt;=64 MiB raw v2 report with post-ack storage snapshots. |
| invariants | Starts with empty physical tables, JSONL buffered before loop, no WAL/checkpoint/fsync. Request remains v1. Storage sampling occurs in collector diagnostics after ack; report encoding stays outside event timing. Raw report alone is not controlled-runner provenance. |
| ownership | Owns DeltaRuntime, borrowed-stream EventReader, local Sink and ordinary file/JSON/Record buffers, including per-event storage values. Reader is destroyed before runtime/input; native program/reader share original query grant. |
| failure | Any request/proof/decode/native/output/diagnostic failure stops main with error; earlier volatile commits or external sink prefix are not rolled back. No nested catch continues. Final report emission explicitly flushes stdout and returns failure on stream error; completed work is not rolled back. |
| cost | Explicit setup/proof/runtime/cursor/encode/write/release/ack/diagnostic/teardown phases plus outside-account collector memory. Storage statistics are measured as diagnostics; no engine update hook or accounting overhead is introduced by this collector change. Grants are not whole-process RSS/time. One final stdout flush is presentation work outside native event maintenance. |
| Design | [examples/workload-measurement/main.cpp](../../../../../examples/workload-measurement/main.cpp), [include/crown/runtime/delta.hpp](../../../../../include/crown/runtime/delta.hpp), [include/crown/runtime/support.hpp](../../../../../include/crown/runtime/support.hpp), [include/crown/io/ingest.hpp](../../../../../include/crown/io/ingest.hpp), [src/io/event_reader.cpp](../../../../../src/io/event_reader.cpp), [tools/run_measurements.py](../../../../../tools/run_measurements.py), [schemas/workload-measurement-v1.schema.json](../../../../../schemas/workload-measurement-v1.schema.json), [schemas/workload-measurement-v2.schema.json](../../../../../schemas/workload-measurement-v2.schema.json), [docs/measurement.md](../../../../measurement.md), [docs/session_lifecycle.md](../../../../session_lifecycle.md), [docs/planner_continuations.md](../../../../planner_continuations.md) |

```text
require(argc==6
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Validate the closed request schema and finite resource grants. |
| inputs / outputs | Checks all 15 exact fields, schema/action/mode/codec/sink, numeric maxima, labels and phase count/length. |
| invariants | Zero events is allowed; memory and output-call grants must be positive. max_events&lt;=4096, calls&lt;=1M, encoded bytes&lt;=1GiB, native memory&lt;=4GiB, delay&lt;=100000us. |
| ownership | Request/sets/phase strings are ordinary owning JSON/STL buffers outside native grant. |
| failure | Missing/type/unknown/limit error fails before runtime or sink creation. |
| cost | Request parse/field scans and ordinary metadata copies. |
| Design | [examples/workload-measurement/main.cpp](../../../../../examples/workload-measurement/main.cpp), [include/crown/runtime/delta.hpp](../../../../../include/crown/runtime/delta.hpp), [include/crown/runtime/support.hpp](../../../../../include/crown/runtime/support.hpp), [include/crown/io/ingest.hpp](../../../../../include/crown/io/ingest.hpp), [src/io/event_reader.cpp](../../../../../src/io/event_reader.cpp), [include/crown/runtime/observation.hpp](../../../../../include/crown/runtime/observation.hpp), [tools/run_measurements.py](../../../../../tools/run_measurements.py), [docs/measurement.md](../../../../measurement.md), [docs/session_lifecycle.md](../../../../session_lifecycle.md), [docs/planner_continuations.md](../../../../planner_continuations.md) |

```text
const auto& preflight=request.at
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Validate the optional preflight receipt digest shape. |
| inputs / outputs | Requires null or exactly 64 lowercase hex characters; retains request as supplied. |
| invariants | Collector does not load/check the earlier receipt or assert it actually verified this run; tools/run_measurements.py performs packet linkage. |
| ownership | Borrowed reference into live request; report later copies request. |
| failure | Invalid shape fails before input processing. |
| cost | At most 64-character scan; no receipt IO. |
| Design | [examples/workload-measurement/main.cpp](../../../../../examples/workload-measurement/main.cpp), [include/crown/runtime/delta.hpp](../../../../../include/crown/runtime/delta.hpp), [include/crown/runtime/support.hpp](../../../../../include/crown/runtime/support.hpp), [include/crown/io/ingest.hpp](../../../../../include/crown/io/ingest.hpp), [src/io/event_reader.cpp](../../../../../src/io/event_reader.cpp), [include/crown/runtime/observation.hpp](../../../../../include/crown/runtime/observation.hpp), [tools/run_measurements.py](../../../../../tools/run_measurements.py), [docs/measurement.md](../../../../measurement.md), [docs/session_lifecycle.md](../../../../session_lifecycle.md), [docs/planner_continuations.md](../../../../planner_continuations.md) |

```text
auto binding_request=request;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Prepare request binding and turn off clock sampling for verification. |
| inputs / outputs | Copies request, removes command/preflight fields; now lambda returns zero time points in verify and steady_clock::now in measure. |
| invariants | Verify/measure can share the same semantic configuration digest; verification zeros are not timing samples. |
| ownership | binding_request owns deep JSON copies; lambda borrows immutable verify flag for run lifetime. |
| failure | JSON copy/erase allocation can fail before processing. |
| cost | Ordinary request copy; each measured now reads the clock. |
| Design | [examples/workload-measurement/main.cpp](../../../../../examples/workload-measurement/main.cpp), [include/crown/runtime/delta.hpp](../../../../../include/crown/runtime/delta.hpp), [include/crown/runtime/support.hpp](../../../../../include/crown/runtime/support.hpp), [include/crown/io/ingest.hpp](../../../../../include/crown/io/ingest.hpp), [src/io/event_reader.cpp](../../../../../src/io/event_reader.cpp), [include/crown/runtime/observation.hpp](../../../../../include/crown/runtime/observation.hpp), [tools/run_measurements.py](../../../../../tools/run_measurements.py), [docs/measurement.md](../../../../measurement.md), [docs/session_lifecycle.md](../../../../session_lifecycle.md), [docs/planner_continuations.md](../../../../planner_continuations.md) |

```text
const auto files_begin=now();
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Read bounded artifact/input files and independently admit the artifact. |
| inputs / outputs | 16MiB artifact and 8MiB JSONL buffers; separately clocks file reads and artifact validation. |
| invariants | Input remains buffered in memory; artifact() checks actual plan/proof rather than trusting JSON schema alone. |
| ownership | Strings and JSON are compiler/caller buffers; checked plan retains its metadata. |
| failure | Read/JSON/physical/proof failures stop before native initialization. |
| cost | Full file copies, parsing, lowering/validation and independent certificate replay. |
| Design | [examples/workload-measurement/main.cpp](../../../../../examples/workload-measurement/main.cpp), [include/crown/runtime/delta.hpp](../../../../../include/crown/runtime/delta.hpp), [include/crown/runtime/support.hpp](../../../../../include/crown/runtime/support.hpp), [include/crown/io/ingest.hpp](../../../../../include/crown/io/ingest.hpp), [src/io/event_reader.cpp](../../../../../src/io/event_reader.cpp), [include/crown/runtime/observation.hpp](../../../../../include/crown/runtime/observation.hpp), [tools/run_measurements.py](../../../../../tools/run_measurements.py), [docs/measurement.md](../../../../measurement.md), [docs/session_lifecycle.md](../../../../session_lifecycle.md), [docs/planner_continuations.md](../../../../planner_continuations.md) |

```text
Json expected;if(verify)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Load the independent expected result only in verification mode. |
| inputs / outputs | EXPECTED cannot be dash in verify; file &lt;=64MiB and epochs count equals declared phases. |
| invariants | Expected results come from controlled-runner fixtures; collector compares actual initial/current/delta data, does not manufacture native facts from them. |
| ownership | Ordinary oracle JSON owns rows independently from runtime. |
| failure | Bad/missing oracle/count fails before processing. |
| cost | Verification-only file read/JSON allocation; measure does not read expected file. |
| Design | [examples/workload-measurement/main.cpp](../../../../../examples/workload-measurement/main.cpp), [include/crown/runtime/delta.hpp](../../../../../include/crown/runtime/delta.hpp), [include/crown/runtime/support.hpp](../../../../../include/crown/runtime/support.hpp), [include/crown/io/ingest.hpp](../../../../../include/crown/io/ingest.hpp), [src/io/event_reader.cpp](../../../../../src/io/event_reader.cpp), [include/crown/runtime/observation.hpp](../../../../../include/crown/runtime/observation.hpp), [tools/run_measurements.py](../../../../../tools/run_measurements.py), [docs/measurement.md](../../../../measurement.md), [docs/session_lifecycle.md](../../../../session_lifecycle.md), [docs/planner_continuations.md](../../../../planner_continuations.md) |

```text
runtime::DeltaOptions options;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Configure actual native output mode, observation and memory grant. |
| inputs / outputs | delta selects DeltaMode::delta; maintenance/snapshot use maintenance; observation is off/counters/timed. |
| invariants | Snapshot is a collector output choice over maintenance owner. Optional observation does not disable mandatory work/account admission. |
| ownership | Inline options; runtime later retains requested/resolved configuration. |
| failure | Unknown observe/workload flag or downstream native option admission fails explicitly. |
| cost | Fixed configuration; actual instrumentation overhead occurs during runtime. |
| Design | [examples/workload-measurement/main.cpp](../../../../../examples/workload-measurement/main.cpp), [include/crown/runtime/delta.hpp](../../../../../include/crown/runtime/delta.hpp), [include/crown/runtime/support.hpp](../../../../../include/crown/runtime/support.hpp), [include/crown/io/ingest.hpp](../../../../../include/crown/io/ingest.hpp), [src/io/event_reader.cpp](../../../../../src/io/event_reader.cpp), [include/crown/runtime/observation.hpp](../../../../../include/crown/runtime/observation.hpp), [tools/run_measurements.py](../../../../../tools/run_measurements.py), [docs/measurement.md](../../../../measurement.md), [docs/session_lifecycle.md](../../../../session_lifecycle.md), [docs/planner_continuations.md](../../../../planner_continuations.md) |

```text
auto owner=std::make_unique<runtime::DeltaRuntime>
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Initialize the empty runtime, funded EventReader, workload collector and external sink. |
| inputs / outputs | Checked plan and memory grant; istringstream over buffered JSONL; reader derives original account from owner.plan(); Sink disabled in verify. |
| invariants | Stream outlives EventReader. Runtime starts empty and all load events are charged; initial result oracle check is verification-only. |
| ownership | Unique runtime/reader own native resources; reader borrows local istringstream and retains plan. Ordinary istringstream/input buffers are outside native account. |
| failure | Initialization/statistics/sink-open/initial-oracle failures unwind all acquired resources. |
| cost | Metadata import/empty state/reader/counters allocation plus optional exclusive file open and initial verification enumeration. |
| Design | [examples/workload-measurement/main.cpp](../../../../../examples/workload-measurement/main.cpp), [include/crown/runtime/delta.hpp](../../../../../include/crown/runtime/delta.hpp), [include/crown/runtime/support.hpp](../../../../../include/crown/runtime/support.hpp), [include/crown/io/ingest.hpp](../../../../../include/crown/io/ingest.hpp), [src/io/event_reader.cpp](../../../../../src/io/event_reader.cpp), [include/crown/runtime/observation.hpp](../../../../../include/crown/runtime/observation.hpp), [tools/run_measurements.py](../../../../../tools/run_measurements.py), [docs/measurement.md](../../../../measurement.md), [docs/session_lifecycle.md](../../../../session_lifecycle.md), [docs/planner_continuations.md](../../../../planner_continuations.md) |

```text
const auto initial_memory=owner->accounted_memory_statistics()
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Sample initial native account and allocate host event records. |
| inputs / outputs | Captures account statistics and reserves records for phases; initializes loop totals. |
| invariants | Account bytes exclude std::vector&lt;Record&gt;, JSON, buffered input and process overhead. Peak is cumulative, not a fresh per-phase peak. |
| ownership | Value statistics plus ordinary record vector; no borrowed rows. |
| failure | Host reserve may fail; no native event has been consumed. |
| cost | Account accessor plus ordinary reserve proportional to declared event count. |
| Design | [examples/workload-measurement/main.cpp](../../../../../examples/workload-measurement/main.cpp), [include/crown/runtime/delta.hpp](../../../../../include/crown/runtime/delta.hpp), [include/crown/runtime/support.hpp](../../../../../include/crown/runtime/support.hpp), [include/crown/io/ingest.hpp](../../../../../include/crown/io/ingest.hpp), [src/io/event_reader.cpp](../../../../../src/io/event_reader.cpp), [include/crown/runtime/observation.hpp](../../../../../include/crown/runtime/observation.hpp), [tools/run_measurements.py](../../../../../tools/run_measurements.py), [docs/measurement.md](../../../../measurement.md), [docs/session_lifecycle.md](../../../../session_lifecycle.md), [docs/planner_continuations.md](../../../../planner_continuations.md) |

```text
Record record;const auto begin=now();
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Peek and validate one event without accepting it. |
| inputs / outputs | Reader returns borrowed cached InputEventView or validated EOF; record stores decode interval/sequence/phase. |
| invariants | Cached event remains live until acknowledge; decoder failures are sticky. EOF decode is separately recorded, no fake epoch is added. |
| ownership | Event view borrows reader; phase string copies request label. Runtime has not accepted this event yet. |
| failure | Decode/sequence/catalog/resource or event/phase-limit errors stop without acknowledgment. |
| cost | Native decode/validation and funded cached row/source progress preparation. |
| Design | [examples/workload-measurement/main.cpp](../../../../../examples/workload-measurement/main.cpp), [include/crown/runtime/delta.hpp](../../../../../include/crown/runtime/delta.hpp), [include/crown/runtime/support.hpp](../../../../../include/crown/runtime/support.hpp), [include/crown/io/ingest.hpp](../../../../../include/crown/io/ingest.hpp), [src/io/event_reader.cpp](../../../../../src/io/event_reader.cpp), [include/crown/runtime/observation.hpp](../../../../../include/crown/runtime/observation.hpp), [tools/run_measurements.py](../../../../../tools/run_measurements.py), [docs/measurement.md](../../../../measurement.md), [docs/session_lifecycle.md](../../../../session_lifecycle.md), [docs/planner_continuations.md](../../../../planner_continuations.md) |

```text
std::optional<runtime::DeltaRuntime::PendingEpoch> pending
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Import the cached update into private native storage, prepare and commit. |
| inputs / outputs | begin_view borrows values for call only; pending owns its prepared rows, loops step, commit returns owning Epoch; pending.reset precedes native timer end. |
| invariants | No output is visible before commit. Borrowed source event is still cached and is not yet acknowledged. |
| ownership | Pending/Epoch are move-only owners; private destruction aborts uncommitted work; committed epoch survives pending reset. |
| failure | Native grant/validation/preparation failure unwinds without accepting reader progress; commit precedes any later external-output failure. |
| cost | Timed native begin/import/step/commit plus pending release, including private delta spool preparation. |
| Design | [examples/workload-measurement/main.cpp](../../../../../examples/workload-measurement/main.cpp), [include/crown/runtime/delta.hpp](../../../../../include/crown/runtime/delta.hpp), [include/crown/runtime/support.hpp](../../../../../include/crown/runtime/support.hpp), [include/crown/io/ingest.hpp](../../../../../include/crown/io/ingest.hpp), [src/io/event_reader.cpp](../../../../../src/io/event_reader.cpp), [include/crown/runtime/observation.hpp](../../../../../include/crown/runtime/observation.hpp), [tools/run_measurements.py](../../../../../tools/run_measurements.py), [docs/measurement.md](../../../../measurement.md), [docs/session_lifecycle.md](../../../../session_lifecycle.md), [docs/planner_continuations.md](../../../../planner_continuations.md) |

```text
Json actual_delta=Json::array();
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Select maintenance-only, full-snapshot cursor or committed-delta output. |
| inputs / outputs | Snapshot constructs results cursor; delta reads epoch; maintenance skips output loop. |
| invariants | Snapshot cursor lease blocks mutation through exhaustion/release. Delta spool records are owning committed results, not private speculative output. |
| ownership | Optional move-only cursor retains lease; optional storage::Tuple/SignedResult owns each row payload. |
| failure | Cursor startup/work/native allocation failure stops after commit with reader still unacknowledged. |
| cost | Snapshot setup clock is separate from successful/terminal next-call clocks; maintenance does no result enumeration. |
| Design | [examples/workload-measurement/main.cpp](../../../../../examples/workload-measurement/main.cpp), [include/crown/runtime/delta.hpp](../../../../../include/crown/runtime/delta.hpp), [include/crown/runtime/support.hpp](../../../../../include/crown/runtime/support.hpp), [include/crown/io/ingest.hpp](../../../../../include/crown/io/ingest.hpp), [src/io/event_reader.cpp](../../../../../src/io/event_reader.cpp), [include/crown/runtime/observation.hpp](../../../../../include/crown/runtime/observation.hpp), [tools/run_measurements.py](../../../../../tools/run_measurements.py), [docs/measurement.md](../../../../measurement.md), [docs/session_lifecycle.md](../../../../session_lifecycle.md), [docs/planner_continuations.md](../../../../planner_continuations.md) |

```text
require(output_calls<max_calls
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Bound and time every successful and terminal output call. |
| inputs / outputs | Global call counter includes final null; records {call_ns,present}; counts actual returned rows. |
| invariants | A row count limit alone would miss termination; raw calls preserve startup/results/termination behavior. |
| ownership | Returned tuple owns payload; tuple.values() borrows it for immediate export. Host calls vector stores numeric copies. |
| failure | Grant exhaustion/cursor or spool failure aborts measurement after committed native input. |
| cost | One native next operation, clock reads and outside-next-scope host vector append. |
| Design | [examples/workload-measurement/main.cpp](../../../../../examples/workload-measurement/main.cpp), [include/crown/runtime/delta.hpp](../../../../../include/crown/runtime/delta.hpp), [include/crown/runtime/support.hpp](../../../../../include/crown/runtime/support.hpp), [include/crown/io/ingest.hpp](../../../../../include/crown/io/ingest.hpp), [src/io/event_reader.cpp](../../../../../src/io/event_reader.cpp), [include/crown/runtime/observation.hpp](../../../../../include/crown/runtime/observation.hpp), [tools/run_measurements.py](../../../../../tools/run_measurements.py), [docs/measurement.md](../../../../measurement.md), [docs/session_lifecycle.md](../../../../session_lifecycle.md), [docs/planner_continuations.md](../../../../planner_continuations.md) |

```text
if(verify && mode=="delta")
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Verify signed deltas or externally encode/write each measured row. |
| inputs / outputs | Verification appends operation/value JSON; measurement optionally encodes JSONL and calls external Sink even when encoded string is empty. |
| invariants | Encoding/sink clocks are separate from native next. codec none creates no JSONL but enabled sink still counts/waits per present row. |
| ownership | Tuple borrow stays valid through export; encoded string/verification JSON own ordinary bytes; Sink retains no row. |
| failure | Encoding/byte-limit/write failure leaves committed state and possibly partial external file; no source ack or durable-sink claim. |
| cost | O(fields/text bytes) optional JSON encoding plus delay/write; release of returned row is separately timed. |
| Design | [examples/workload-measurement/main.cpp](../../../../../examples/workload-measurement/main.cpp), [include/crown/runtime/delta.hpp](../../../../../include/crown/runtime/delta.hpp), [include/crown/runtime/support.hpp](../../../../../include/crown/runtime/support.hpp), [include/crown/io/ingest.hpp](../../../../../include/crown/io/ingest.hpp), [src/io/event_reader.cpp](../../../../../src/io/event_reader.cpp), [include/crown/runtime/observation.hpp](../../../../../include/crown/runtime/observation.hpp), [tools/run_measurements.py](../../../../../tools/run_measurements.py), [docs/measurement.md](../../../../measurement.md), [docs/session_lifecycle.md](../../../../session_lifecycle.md), [docs/planner_continuations.md](../../../../planner_continuations.md) |

```text
if(cursor){const auto& metrics=cursor->metrics()
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Capture cursor work and explicitly time cursor/epoch release before input acknowledgment. |
| inputs / outputs | Copies startup/results/termination work, resets cursor and epoch, then acknowledges cached event. |
| invariants | Cursor/epoch cleanup and spool discard finish before next mutation. Maintenance may discard output only by its actual native mode semantics; no rollback occurs. |
| ownership | Owning optionals release payloads/lease; acknowledge publishes prepaid source position and releases reader cache. |
| failure | Valid acknowledgment is noexcept/nonallocating publication but includes actual release cost. Earlier committed/output errors bypass it and terminate run. |
| cost | Separately timed row/cursor release, committed epoch release and reader acknowledgment; active spans decode through ack. |
| Design | [examples/workload-measurement/main.cpp](../../../../../examples/workload-measurement/main.cpp), [include/crown/runtime/delta.hpp](../../../../../include/crown/runtime/delta.hpp), [include/crown/runtime/support.hpp](../../../../../include/crown/runtime/support.hpp), [include/crown/io/ingest.hpp](../../../../../include/crown/io/ingest.hpp), [src/io/event_reader.cpp](../../../../../src/io/event_reader.cpp), [include/crown/runtime/observation.hpp](../../../../../include/crown/runtime/observation.hpp), [tools/run_measurements.py](../../../../../tools/run_measurements.py), [docs/measurement.md](../../../../measurement.md), [docs/session_lifecycle.md](../../../../session_lifecycle.md), [docs/planner_continuations.md](../../../../planner_continuations.md) |

```text
if(verify){const auto& frame=
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Compare committed actual rows/deltas against the independent per-epoch oracle. |
| inputs / outputs | Requires sequence match, duplicate-free unordered current-row equality and signed-delta equality in delta mode. |
| invariants | Runs after native commit/reader acknowledgment and outside measured mode; mismatch invalidates the verification report. |
| ownership | Fresh native cursor/ordinary JSON/set strings own their resources until comparison returns. |
| failure | Mismatch or native/export limit fails this separate verification run; no failed verification receipt is emitted as successful. |
| cost | Full actual-result traversal, scalar serialization, ordered-set construction and comparison. |
| Design | [examples/workload-measurement/main.cpp](../../../../../examples/workload-measurement/main.cpp), [include/crown/runtime/delta.hpp](../../../../../include/crown/runtime/delta.hpp), [include/crown/runtime/support.hpp](../../../../../include/crown/runtime/support.hpp), [include/crown/io/ingest.hpp](../../../../../include/crown/io/ingest.hpp), [src/io/event_reader.cpp](../../../../../src/io/event_reader.cpp), [include/crown/runtime/observation.hpp](../../../../../include/crown/runtime/observation.hpp), [tools/run_measurements.py](../../../../../tools/run_measurements.py), [docs/measurement.md](../../../../measurement.md), [docs/session_lifecycle.md](../../../../session_lifecycle.md), [docs/planner_continuations.md](../../../../planner_continuations.md) |

```text
const auto diagnostic=now();record.bytes=
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Sample account, optional and physical-storage diagnostics after input acknowledgment. |
| inputs / outputs | Committed/acknowledged runtime in; memory, observation and source/support arena snapshots stored on Record; diagnostics_ns elapsed value out. |
| invariants | Storage counts are explicit tool diagnostics after the timed epoch and ack. The diagnostic visits logical tables/nodes per the source comment, not every historical arena slot; it is outside event_active_ns and inside loop wall. No engine update hook was added. |
| ownership | Copies returned statistics into the host-side Record; owner remains the native runtime owner. |
| failure | A statistics/clock failure terminates collection after the epoch may already be committed and acknowledged; no rollback is attempted. |
| cost | Adds the statistics calls and value copies per event; their elapsed time is included in diagnostics_ns, not native_prepare_commit_ns or event_active_ns. |
| Design | [examples/workload-measurement/main.cpp](../../../../../examples/workload-measurement/main.cpp), [include/crown/runtime/delta.hpp](../../../../../include/crown/runtime/delta.hpp), [schemas/workload-measurement-v2.schema.json](../../../../../schemas/workload-measurement-v2.schema.json), [docs/measurement.md](../../../../measurement.md) |

```text
const auto loop_end=now();
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Validate exact horizon and bind actual physical/input/request identity. |
| inputs / outputs | Requires input EOF at exact phase count; reads native backend/physical digest and exports accepted progress; hashes physical_sha+input_sha+canonical binding_request dump. |
| invariants | Digest binds this configuration/trace; it does not authenticate a preflight receipt. Exported progress is ordinary caller-owned DTO, not shared native text. |
| ownership | Progress map/string export and JSON/hash strings own ordinary bytes; native InputPositions remain in reader. |
| failure | Premature horizon/export/hash allocation fails after processing; no durable output exists in this collector. |
| cost | Final account sample, accepted progress map/name copies, input hash and request serialization. |
| Design | [examples/workload-measurement/main.cpp](../../../../../examples/workload-measurement/main.cpp), [include/crown/runtime/delta.hpp](../../../../../include/crown/runtime/delta.hpp), [include/crown/runtime/support.hpp](../../../../../include/crown/runtime/support.hpp), [include/crown/io/ingest.hpp](../../../../../include/crown/io/ingest.hpp), [src/io/event_reader.cpp](../../../../../src/io/event_reader.cpp), [include/crown/runtime/observation.hpp](../../../../../include/crown/runtime/observation.hpp), [tools/run_measurements.py](../../../../../tools/run_measurements.py), [docs/measurement.md](../../../../measurement.md), [docs/session_lifecycle.md](../../../../session_lifecycle.md), [docs/planner_continuations.md](../../../../planner_continuations.md) |

```text
if(verify){report["verified"]=true;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Emit only the successful verification receipt and skip measurement report work. |
| inputs / outputs | Successful oracle checks and matching horizon; write verified=true, flush stdout and return its resulting stream state. This short report must detect buffered write failure. |
| invariants | Zero clocks and disabled Sink are never presented as raw measured phase samples. |
| ownership | Receipt owns ordinary JSON; return unwinds reader/runtime/disabled sink in lifetime order. |
| failure | Flushed stream-state failure returns 1; output/report allocation may throw. |
| cost | Verification receipt dump and process teardown only. Explicit flush completes the process report before its stream-state exit check. |
| Design | [examples/workload-measurement/main.cpp](../../../../../examples/workload-measurement/main.cpp), [include/crown/runtime/delta.hpp](../../../../../include/crown/runtime/delta.hpp), [include/crown/runtime/support.hpp](../../../../../include/crown/runtime/support.hpp), [include/crown/io/ingest.hpp](../../../../../include/crown/io/ingest.hpp), [src/io/event_reader.cpp](../../../../../src/io/event_reader.cpp), [include/crown/runtime/observation.hpp](../../../../../include/crown/runtime/observation.hpp), [tools/run_measurements.py](../../../../../tools/run_measurements.py), [docs/measurement.md](../../../../measurement.md), [docs/session_lifecycle.md](../../../../session_lifecycle.md), [docs/planner_continuations.md](../../../../planner_continuations.md) |

```text
const auto final_diagnostics_begin=now();
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Capture final workload, close external sink and encode retained event frames. |
| inputs / outputs | Measurement only; times workload capture/export and sink.close separately, then creates JSON frames from all Records. |
| invariants | final_memory precedes this capture; later diagnostic allocations are outside that sample. File close is checked but not fsynced. |
| ownership | Temporary workload snapshot/JSON and frames own their data; no runtime/cursor row borrow escapes. |
| failure | Capture/export/close/allocation failure prevents successful report while prior file bytes persist. |
| cost | Workload descriptor/cell export, one optional close syscall, and O(events+output_calls) ordinary frame allocation. |
| Design | [examples/workload-measurement/main.cpp](../../../../../examples/workload-measurement/main.cpp), [include/crown/runtime/delta.hpp](../../../../../include/crown/runtime/delta.hpp), [include/crown/runtime/support.hpp](../../../../../include/crown/runtime/support.hpp), [include/crown/io/ingest.hpp](../../../../../include/crown/io/ingest.hpp), [src/io/event_reader.cpp](../../../../../src/io/event_reader.cpp), [include/crown/runtime/observation.hpp](../../../../../include/crown/runtime/observation.hpp), [tools/run_measurements.py](../../../../../tools/run_measurements.py), [docs/measurement.md](../../../../measurement.md), [docs/session_lifecycle.md](../../../../session_lifecycle.md), [docs/planner_continuations.md](../../../../planner_continuations.md) |

```text
const auto teardown_begin=now();
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Release reader before runtime and record actual process context. |
| inputs / outputs | Explicit reader.reset then owner.reset; collects uname, sched_getaffinity and optional /proc/self/status Threads. |
| invariants | Input stream remains alive; no reader borrows a destroyed runtime owner. Environment observations describe this process, not archive flags/build provenance. |
| ownership | Native owners release storage; retained Record observation contexts can keep their actual metadata alive. Host record/JSON buffers remain for report. |
| failure | uname/affinity failures or thread-text conversion fail explicitly; missing proc Threads leaves that optional field absent. |
| cost | Measured native facade teardown plus separate host syscalls/scans outside it; not whole-process final destruction. |
| Design | [examples/workload-measurement/main.cpp](../../../../../examples/workload-measurement/main.cpp), [include/crown/runtime/delta.hpp](../../../../../include/crown/runtime/delta.hpp), [include/crown/runtime/support.hpp](../../../../../include/crown/runtime/support.hpp), [include/crown/io/ingest.hpp](../../../../../include/crown/io/ingest.hpp), [src/io/event_reader.cpp](../../../../../src/io/event_reader.cpp), [include/crown/runtime/observation.hpp](../../../../../include/crown/runtime/observation.hpp), [tools/run_measurements.py](../../../../../tools/run_measurements.py), [docs/measurement.md](../../../../measurement.md), [docs/session_lifecycle.md](../../../../session_lifecycle.md), [docs/planner_continuations.md](../../../../planner_continuations.md) |

```text
report["scope"]=
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Qualify volatile timing/memory scopes and bound the final encoded report. |
| inputs / outputs | Adds runtime options/environment/qualifications, dumps JSON and checks &lt;=64MiB before stdout. |
| invariants | Report encoding/host allocation is excluded from native event timing; raw report requires controlled correctness/build/repetition packet and claims no speedup. |
| ownership | Ordinary JSON/string output owns encoded copies outside query account. |
| failure | Report overflow/allocation/flushed stdout state returns failure after processing; byte cap is checked after dump allocation. |
| cost | Full report serialization proportional to raw event/call records; no extra native mutation. Explicit flush completes the process report before its stream-state exit check. |
| Design | [examples/workload-measurement/main.cpp](../../../../../examples/workload-measurement/main.cpp), [include/crown/runtime/delta.hpp](../../../../../include/crown/runtime/delta.hpp), [include/crown/runtime/support.hpp](../../../../../include/crown/runtime/support.hpp), [include/crown/io/ingest.hpp](../../../../../include/crown/io/ingest.hpp), [src/io/event_reader.cpp](../../../../../src/io/event_reader.cpp), [include/crown/runtime/observation.hpp](../../../../../include/crown/runtime/observation.hpp), [tools/run_measurements.py](../../../../../tools/run_measurements.py), [docs/measurement.md](../../../../measurement.md), [docs/session_lifecycle.md](../../../../session_lifecycle.md), [docs/planner_continuations.md](../../../../planner_continuations.md) |

```text
Json report{{"schema_version",2}
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Start raw collector report in workload-measurement version 2. |
| inputs / outputs | Includes request/digests/modes/backend/counts/source positions collected by run(). |
| invariants | Raw report is v2 for verification and measurement; request stays v1. Verify returns common receipt; measure adds timed frames/environment. |
| ownership | Ordinary JSON owns copied fields; run owns native runtime. |
| failure | Digest/JSON errors propagate to main exception boundary. |
| cost | Hashes input/artifact text and the normalized binding-request serialization after omitting command and preflight_receipt_sha256, then copies the full request (including its variable phases array) and accepted source positions into the envelope. Metadata byte volume follows those inputs; per-epoch frame materialization occurs later. |
| Design | [examples/workload-measurement/main.cpp](../../../../../examples/workload-measurement/main.cpp), [schemas/workload-measurement-v1.schema.json](../../../../../schemas/workload-measurement-v1.schema.json), [schemas/workload-measurement-v2.schema.json](../../../../../schemas/workload-measurement-v2.schema.json), [docs/adversarial_scalability.md](../../../../adversarial_scalability.md), Refactor.md:1393-1395 |

```text
{"storage",storage_statistics(record.storage)}
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Add captured source/support arena sample to each measured epoch. |
| inputs / outputs | Record statistics in; nested JSON in frame. |
| invariants | Captured after ack/active timing; population sample is not slot visits or allocator bytes. |
| ownership | Frame JSON owns copies; Record owns value until encoding. |
| failure | Formatter/JSON failures stop output. |
| cost | One small object per epoch; final encoding is outside active event time. |
| Design | [examples/workload-measurement/main.cpp](../../../../../examples/workload-measurement/main.cpp), [schemas/workload-measurement-v2.schema.json](../../../../../schemas/workload-measurement-v2.schema.json), [docs/adversarial_scalability.md](../../../../adversarial_scalability.md), Refactor.md:1393-1395 |

```text
report["qualification"]=
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Emit report-level qualification for native accounts, arena counts and timing scopes. |
| inputs / outputs | No args; adds a text qualification to measurement report after frame encoding. |
| invariants | Separates native account bytes from caller/compiler/report/input DTOs and RSS; calls arena slots populations, excludes allocator bytes/visits, includes diagnostic/record storage in loop wall and makes no speedup claim. |
| ownership | Report JSON owns the string. |
| failure | JSON allocation errors propagate. |
| cost | One bounded string field. |
| Design | [examples/workload-measurement/main.cpp](../../../../../examples/workload-measurement/main.cpp), [schemas/workload-measurement-v2.schema.json](../../../../../schemas/workload-measurement-v2.schema.json), [tools/run_measurements.py](../../../../../tools/run_measurements.py), [docs/measurement.md](../../../../measurement.md), [docs/adversarial_scalability.md](../../../../adversarial_scalability.md), Refactor.md:1393-1395 |

```text
@source-span:L199-L199:sha256:01287c671de303ff06a13a184e7d2465541357b218960f3e6b7a104f67adca16
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Retain the complete checked artifact while borrowing its plan for one collector run. |
| inputs / outputs | Parsed artifact_text enters artifact(); compiled owns the result and plan aliases its PhysicalPlan. |
| invariants | The artifact timer covers reconstruction, proof replay and admission. No runtime owner is created until this completes. |
| ownership | compiled remains local through report construction and teardown; the plan reference does not escape run. |
| failure | Admission failure propagates before sink construction or report output. |
| cost | One cold result and alias; no added event-loop work. Clock sampling remains disabled in verify mode. |
| Design | [docs/measurement.md](../../../../measurement.md), [docs/planner_proofs.md](../../../../planner_proofs.md), [docs/physical_plans.md](../../../../physical_plans.md), [Refactor.md §5.4 and §14.1–14.4](../../../../../Refactor.md), [schemas/compiled-experimental-upper-v3.schema.json](../../../../../schemas/compiled-experimental-upper-v3.schema.json) |

```text
@source-span:L268-L272:sha256:60f3f3d1bfb5cb26a987f1172fb396729be74a7b5d9a293f130ab34da723b408
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Label explicitly requested V3 results as separately checked original-lower/actual-upper observations. |
| inputs / outputs | Reads the admitted upper_only result, typed original optimum height and physical validation height; adds experimental_height to the report. |
| invariants | Only V3 enters this branch. Its status remains checked_upper_only even at zero gap. h*&lt;=actual was already established, so actual-original cannot underflow. V1/V2 and constant-false report shapes are unchanged. |
| ownership | The report owns copied scalar/string JSON values; it retains no replay handle or source-borrowed payload. |
| failure | Report allocation can fail before final stdout; the existing CLI boundary returns failure. No proof authority is minted by this formatting. |
| cost | One cold fixed-size JSON object per invocation, outside native runtime funding; no additional work per update. |
| Design | [docs/measurement.md](../../../../measurement.md), [docs/planner_proofs.md](../../../../planner_proofs.md), [docs/physical_plans.md](../../../../physical_plans.md), [Refactor.md §5.4 and §14.1–14.4](../../../../../Refactor.md), [schemas/compiled-experimental-upper-v3.schema.json](../../../../../schemas/compiled-experimental-upper-v3.schema.json) |

```text
@source-span:L173-L308:sha256:0a1791bf8300f94e44506aece6f3b187f6e48feb5ab2f73800a1ccfbfc4c87dc
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Run the existing bounded B03 collector with V3 admission and explicit upper-only report metadata. |
| inputs / outputs | Receives artifact, JSONL events, closed request, independent expected file or dash, and sink path. Produces one verification or raw measurement report. |
| invariants | Artifact validation precedes owner/sink construction. Verify compares initial/current rows and, in delta mode, signed output against every independent oracle prefix. Measurement mode retains old clocks, funding, mode/codec/sink and diagnostics. Preflight digest shape alone is not independent correctness authority. Only the admitted V3 result adds experimental_height. |
| ownership | Input strings, report/records and collector sink are host-owned; one DeltaRuntime and funded EventReader own native state. Pending/epoch/cursor lifetimes close before input acknowledgment. Teardown occurs before final measurement output. |
| failure | Request/file/work/output/account errors propagate through the single existing main catch. Verification creates no sink and emits no success until every prefix agrees. Stream flush failure returns nonzero; no new retry/rollback framework is introduced. |
| cost | Existing finite files/events/calls/bytes/memory grants remain. Reconstruction/proof is charged in artifact_validation_ns. Enumeration, encoding, sink wait and diagnostics keep their existing separate boundaries. No speedup or B04 acceptance follows from the raw record. |
| Design | [docs/measurement.md](../../../../measurement.md), [docs/planner_proofs.md](../../../../planner_proofs.md), [docs/physical_plans.md](../../../../physical_plans.md), [Refactor.md §5.4 and §14.1–14.4](../../../../../Refactor.md), [schemas/compiled-experimental-upper-v3.schema.json](../../../../../schemas/compiled-experimental-upper-v3.schema.json) |

## B0025

[Lines 309–309](../../../../../examples/workload-measurement/main.cpp#L309); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

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
| Design | [examples/workload-measurement/main.cpp](../../../../../examples/workload-measurement/main.cpp), [docs/measurement.md](../../../../measurement.md), [docs/session_lifecycle.md](../../../../session_lifecycle.md), [docs/planner_continuations.md](../../../../planner_continuations.md) |

## B0026

[Lines 310–310](../../../../../examples/workload-measurement/main.cpp#L310); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
int main(int argc,char** argv)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Run collector under one process exception boundary. |
| inputs / outputs | Forwards argc/argv and run return status; errors write what() to stderr and return 1. |
| invariants | No error is converted to a partial successful timing report; no manual native recovery/acknowledgment. |
| ownership | run locals unwind before catch; RAII releases epoch/cursor/runtime/reader/fd resources. |
| failure | Catches std::exception only; run checks immediate stdout stream state on success. |
| cost | One boundary catch has no per-event success-path handling loop. |
| Design | [examples/workload-measurement/main.cpp](../../../../../examples/workload-measurement/main.cpp), [docs/measurement.md](../../../../measurement.md), [docs/session_lifecycle.md](../../../../session_lifecycle.md), [docs/planner_continuations.md](../../../../planner_continuations.md) |
