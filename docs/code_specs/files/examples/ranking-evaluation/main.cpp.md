# `examples/ranking-evaluation/main.cpp` — block usage map

[Source](../../../../../examples/ranking-evaluation/main.cpp) · [Source index](../../../README.md) · [Subsystem contracts](../../../subsystem_contracts.md) · [Reviewed primitives](../../../primitives.md)

Demonstrate a concrete public workflow and executable invocation using installed/native CROWN interfaces.

Snapshot SHA-256: `71aafad8aca7aee9f6b754be6abce44c79e9258b577e306c43ec67909413197c`. 167 lines partitioned into 13 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [examples](../../../subsystem_contracts.md#examples). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/cli.md](../../../../cli.md), [docs/native_build.md](../../../../native_build.md), [docs/measurement.md](../../../../measurement.md), [docs/ranking_evaluation.md](../../../../ranking_evaluation.md), [docs/reoptimization.md](../../../../reoptimization.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–23](../../../../../examples/ranking-evaluation/main.cpp#L1) | Imports dependencies; declares namespace scope; declares aliases; declares values/defaults or compile-time conditions. |  · [reviewed contract](#b0001) |
| [B0002 · 24–24](../../../../../examples/ranking-evaluation/main.cpp#L24) | Callable definition: void require(bool value,const char* message) | calls Error; guard void require(bool value,const char* message) {if(!value)throw Error("ranking_evaluation_error",mess… · [reviewed contract](#b0002) |
| [B0003 · 25–30](../../../../../examples/ranking-evaluation/main.cpp#L25) | Callable definition: std::string read(const char* path,std::size_t limit) | calls file, require, bool, gcount; guard std::ifstream file(path,std::ios::binary);require(bool(file),"cannot open evaluation input");std::s…; returns result; 1 loop sites · [reviewed contract](#b0003) |
| [B0004 · 31–34](../../../../../examples/ranking-evaluation/main.cpp#L31) | Callable definition: U64 number(const Json& object,const char* key,U64 maximum) | calls at, require, is_number_integer, is_number_unsigned; guard const auto& value=object.at(key);require(value.is_number_integer() && (value.is_number_unsigned() \|…; returns result · [reviewed contract](#b0004) |
| [B0005 · 35–37](../../../../../examples/ranking-evaluation/main.cpp#L35) | Callable definition: U64 elapsed(Clock::time_point begin,Clock::time_point end) | calls count, require; guard const auto count=std::chrono::duration_cast&lt;std::chrono::nanoseconds&gt;(end-begin).count();require(co…; returns static_cast&lt;U64&gt;(count) · [reviewed contract](#b0005) |
| [B0006 · 38–38](../../../../../examples/ranking-evaluation/main.cpp#L38) | Callable definition: template&lt;class Text&gt; std::string text(const Text& value) | calls data, size; returns {value.data(),value.size()} · [reviewed contract](#b0006) |
| [B0007 · 39–43](../../../../../examples/ranking-evaluation/main.cpp#L39) | Callable definition: Json usage(const rank::Usage& value) | calls ; returns {{@ ,value.work},{@ ,value.cells},{@ ,value.binding_key_bytes},{@ ,value.payload_bytes}, · [reviewed contract](#b0007) |
| [B0008 · 44–44](../../../../../examples/ranking-evaluation/main.cpp#L44) | Explanatory comments or spacing. | source comment (unverified): // This exports a genuine handle to editable transport; consumers must independently replay it. · [reviewed contract](#b0008) |
| [B0009 · 45–50](../../../../../examples/ranking-evaluation/main.cpp#L45) | Callable definition: Json certificate(const planner::VerifiedOptimum& proof) | calls height, upper, tree, binding; returns io::write_oracle(dto,binding.catalog(),binding.query()).at(@ ); source comment (unverified): // This exports a genuine handle to editable transport; consumers must independently replay it. · [reviewed contract](#b0009) |
| [B0010 · 51–62](../../../../../examples/ranking-evaluation/main.cpp#L51) | Callable definition: Json score(const rank::CandidateScore& value,rank::Policy policy) | calls Json::array, push_back, text, Json; returns {{@ ,text(value.structural_key)},{@ ,value.height},; growth push_back; 3 loop sites · [reviewed contract](#b0010) |
| [B0011 · 63–165](../../../../../examples/ranking-evaluation/main.cpp#L63) | Callable definition: int run(int argc,char** argv) | calls require, io::read_json, read, is_object; guard require(argc==5,"usage: crown_export_ranking QUERY.sql CATALOG.json TRAIN.jsonl REQUEST.json");; returns std::cout?0:1; growth push_back; 12 loop sites; source comment (unverified): // Only committed training facts enter these policy choices; no held-out input is opened. · [reviewed contract](#b0011) |
| [B0012 · 166–166](../../../../../examples/ranking-evaluation/main.cpp#L166) | Closes surrounding scope/type. | source comment (unverified): // namespace · [reviewed contract](#b0012) |
| [B0013 · 167–167](../../../../../examples/ranking-evaluation/main.cpp#L167) | Callable definition: int main(int argc,char** argv) | calls run, what; returns run(argc,argv); 1 · [reviewed contract](#b0013) |

## B0001

[Lines 1–23](../../../../../examples/ranking-evaluation/main.cpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

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
| Design | [examples/ranking-evaluation/main.cpp](../../../../../examples/ranking-evaluation/main.cpp), [cmake/CrownInstall.cmake](../../../../../cmake/CrownInstall.cmake), [docs/native_build.md](../../../../native_build.md), [docs/ranking_evaluation.md](../../../../ranking_evaluation.md), [docs/ranking.md](../../../../ranking.md), [docs/selection.md](../../../../selection.md) |

## B0002

[Lines 24–24](../../../../../examples/ranking-evaluation/main.cpp#L24); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void require(bool value,const char* message)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Enforce explicit exporter input/phase requirements. |
| inputs / outputs | Boolean and borrowed constant message; returns or throws ranking_evaluation_error. |
| invariants | Does not turn transport diagnostics into plan/evidence authority. |
| ownership | Error owns copied failure text; no borrow retained. |
| failure | False propagates to process boundary; no partial successful export. |
| cost | Fixed success branch. |
| Design | [examples/ranking-evaluation/main.cpp](../../../../../examples/ranking-evaluation/main.cpp), [include/crown/api/error.hpp](../../../../../include/crown/api/error.hpp), [docs/ranking_evaluation.md](../../../../ranking_evaluation.md), [docs/ranking.md](../../../../ranking.md), [docs/selection.md](../../../../selection.md) |

## B0003

[Lines 25–30](../../../../../examples/ranking-evaluation/main.cpp#L25); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::string read(const char* path,std::size_t limit)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Read one bounded request/SQL/catalog/training file. |
| inputs / outputs | Borrowed path and byte cap; returns owning binary string. |
| invariants | Accepted size&lt;=limit; buffered input/report/compiler memory is outside native execution grant. |
| ownership | Local ifstream closes on return/unwind; string owns bytes. |
| failure | Open/read/limit/host allocation failures stop export. |
| cost | Linear file read/copy with 4096-byte stack buffer and ordinary string growth. |
| Design | [examples/ranking-evaluation/main.cpp](../../../../../examples/ranking-evaluation/main.cpp), [docs/ranking_evaluation.md](../../../../ranking_evaluation.md), [docs/ranking.md](../../../../ranking.md), [docs/selection.md](../../../../selection.md) |

## B0004

[Lines 31–34](../../../../../examples/ranking-evaluation/main.cpp#L31); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
U64 number(const Json& object,const char* key,U64 maximum)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Read one strictly positive bounded exporter grant. |
| inputs / outputs | Borrowed JSON/key and maximum; returns U64. |
| invariants | Requires signed nonnegative/unsigned integer and result&gt;0; exact maxima bound candidate/work/memory/event domains independently. |
| ownership | Borrowed lookup only; scalar result owns no resource. |
| failure | Missing/type/invalid/zero/overflow grant fails before native processing. |
| cost | Object lookup and fixed numeric checks. |
| Design | [examples/ranking-evaluation/main.cpp](../../../../../examples/ranking-evaluation/main.cpp), [docs/ranking_evaluation.md](../../../../ranking_evaluation.md), [docs/ranking.md](../../../../ranking.md), [docs/selection.md](../../../../selection.md) |

## B0005

[Lines 35–37](../../../../../examples/ranking-evaluation/main.cpp#L35); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
U64 elapsed(Clock::time_point begin,Clock::time_point end)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Encode one nonnegative setup duration. |
| inputs / outputs | Steady-clock values; U64 nanoseconds. |
| invariants | Setup timings are measured exporter phases, not predictions or per-event steady-state costs. |
| ownership | Inline values only. |
| failure | Negative duration fails export. |
| cost | Fixed conversion, no clock read inside helper. |
| Design | [examples/ranking-evaluation/main.cpp](../../../../../examples/ranking-evaluation/main.cpp), [docs/ranking_evaluation.md](../../../../ranking_evaluation.md), [docs/ranking.md](../../../../ranking.md), [docs/selection.md](../../../../selection.md) |

## B0006

[Lines 38–38](../../../../../examples/ranking-evaluation/main.cpp#L38); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
template<class Text> std::string text(const Text& value)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Copy a string-like model view into an ordinary transport string. |
| inputs / outputs | Borrowed data()/size() range; returns owning std::string preserving all bytes. |
| invariants | Caller retains source handle through this call; no null-termination assumption or native metadata mutation. |
| ownership | Explicit byte copy, not shared ownership inferred from const/immutability. |
| failure | String allocation may fail. |
| cost | Linear text-byte copy. |
| Design | [examples/ranking-evaluation/main.cpp](../../../../../examples/ranking-evaluation/main.cpp), [docs/ranking_evaluation.md](../../../../ranking_evaluation.md), [docs/ranking.md](../../../../ranking.md), [docs/selection.md](../../../../selection.md) |

## B0007

[Lines 39–43](../../../../../examples/ranking-evaluation/main.cpp#L39); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Json usage(const rank::Usage& value)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Export logical selection/ranking resource usage without merging domains. |
| inputs / outputs | Borrowed Usage; returns work/cells/binding/payload/lowering/identity/replay/normalization/active-time numeric JSON. |
| invariants | Logical bytes/work are not actual allocator/RSS bytes or a disjoint measured CPU sum. |
| ownership | Ordinary JSON owns copied numbers. |
| failure | JSON allocation may throw. |
| cost | Fixed selected-field serialization. |
| Design | [examples/ranking-evaluation/main.cpp](../../../../../examples/ranking-evaluation/main.cpp), [include/crown/planner/ranking.hpp](../../../../../include/crown/planner/ranking.hpp), [include/crown/planner/selection.hpp](../../../../../include/crown/planner/selection.hpp), [include/crown/runtime/ranking_evidence.hpp](../../../../../include/crown/runtime/ranking_evidence.hpp), [docs/ranking_evaluation.md](../../../../ranking_evaluation.md), [docs/ranking.md](../../../../ranking.md), [docs/selection.md](../../../../selection.md) |

## B0008

[Lines 44–44](../../../../../examples/ranking-evaluation/main.cpp#L44); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L44-L44:sha256:76f0f84e9ca9f3015cf76bbc41326a87fba2829e3a2245bedce69340b7920c39
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Explain the adjacent source contract: This exports a genuine handle to editable transport; consumers must independently replay it. |
| inputs / outputs | Human-readable source note in; no executable output or checked receipt. |
| invariants | This comment states context or a limitation. It does not itself enforce or prove the described behavior; use the adjacent implementation and its scoped contract. |
| ownership | Source text only; no object or resource lifetime is created. |
| failure | No runtime failure path in this comment; source encoding/comment syntax still belongs to compilation. |
| cost | No runtime operations from the comment. Any work described in the note belongs to the adjacent operation. |
| Design | [examples/ranking-evaluation/main.cpp](../../../../../examples/ranking-evaluation/main.cpp), [docs/ranking.md](../../../../ranking.md), [docs/code_review.md](../../../../code_review.md) |

## B0009

[Lines 45–50](../../../../../examples/ranking-evaluation/main.cpp#L45); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Json certificate(const planner::VerifiedOptimum& proof)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Export the genuine optimum certificate as a transport DTO. |
| inputs / outputs | Live factory-produced VerifiedOptimum; copies upper tree, lower bounds and algorithm into OracleResult, then write_oracle returns certificate JSON. |
| invariants | certificate_verified=true is assigned only from this already verified handle here; the editable OracleResult/JSON does not manufacture typed proof authority. Later collector independently replays it. |
| ownership | Proof/binding handles share actual private Data; DTO tree/lower-bound/string copies and JSON own ordinary allocations. |
| failure | Invalid/moved proof access, DTO allocation or canonical serialization may fail. |
| cost | Explicit potentially deep certificate/tree DTO export and canonical encoding; no zero-allocation handle-copy claim for these containers. |
| Design | [examples/ranking-evaluation/main.cpp](../../../../../examples/ranking-evaluation/main.cpp), [include/crown/planner/search.hpp](../../../../../include/crown/planner/search.hpp), [include/crown/planner/candidates.hpp](../../../../../include/crown/planner/candidates.hpp), [src/planner/candidates.cpp](../../../../../src/planner/candidates.cpp), [include/crown/io/oracle.hpp](../../../../../include/crown/io/oracle.hpp), [src/io/document.cpp](../../../../../src/io/document.cpp), [docs/ranking_evaluation.md](../../../../ranking_evaluation.md), [docs/ranking.md](../../../../ranking.md), [docs/selection.md](../../../../selection.md) |

## B0010

[Lines 51–62](../../../../../examples/ranking-evaluation/main.cpp#L51); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Json score(const rank::CandidateScore& value,rank::Policy policy)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Export exact policy-specific proxy values and their decomposition. |
| inputs / outputs | CandidateScore and actual effective policy; produces height/depth rational/slot text, occurrence/table terms and unit label. |
| invariants | Only effective policy chooses computed field; fallback height does not expose placeholder depth/slot fields as observed zero. Units are native_height, committed_input_native_depth or tuple_index_slots, never ns/bytes. |
| ownership | Score views borrow retained assessment/result; text() and JSON own copied strings/arrays. |
| failure | Text/JSON allocation or enum-invalid downstream behavior can fail; valid native effective policy is supplied here. |
| cost | Linear depth/table/slot-term export and variable-width integer string copying. |
| Design | [examples/ranking-evaluation/main.cpp](../../../../../examples/ranking-evaluation/main.cpp), [include/crown/planner/ranking.hpp](../../../../../include/crown/planner/ranking.hpp), [include/crown/planner/selection.hpp](../../../../../include/crown/planner/selection.hpp), [include/crown/runtime/ranking_evidence.hpp](../../../../../include/crown/runtime/ranking_evidence.hpp), [docs/ranking_evaluation.md](../../../../ranking_evaluation.md), [docs/ranking.md](../../../../ranking.md), [docs/selection.md](../../../../selection.md) |

## B0011

[Lines 63–165](../../../../../examples/ranking-evaluation/main.cpp#L63); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
int run(int argc,char** argv)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Export checked candidate artifacts and three policies using training data only. |
| inputs / outputs | SQL CATALOG TRAIN REQUEST; bounded request, nonconstant admitted query, proved minimum-height family, actual training runtime/evidence; &lt;=64MiB JSON export. |
| invariants | No calibration/evaluation trace is an input. Retained family and every policy stop/fallback/constraint stay explicit; no deployment, held-out optimality or nanosecond prediction authority. |
| ownership | Search/provider/maintenance runtime/borrowed-stream reader own their resources. Evidence/result handles retain actual shared native observations; all exported artifacts/JSON are ordinary DTO copies. |
| failure | Input/admission/proof/training/evidence/resource/export failures terminate. A policy unavailable attempt is intentionally reported with stop details, not dropped or turned into success. Final report emission explicitly flushes stdout and returns failure on stream error; completed work is not rolled back. |
| cost | Exact search/prefix enumeration, one training replay/capture, three bounded selections, re-lowering/serializing all candidates, hashes/setup clocks/reporting. One final stdout flush is presentation work outside native event maintenance. |
| Design | [examples/ranking-evaluation/main.cpp](../../../../../examples/ranking-evaluation/main.cpp), [include/crown/planner/search.hpp](../../../../../include/crown/planner/search.hpp), [include/crown/planner/candidates.hpp](../../../../../include/crown/planner/candidates.hpp), [src/planner/candidates.cpp](../../../../../src/planner/candidates.cpp), [include/crown/planner/ranking.hpp](../../../../../include/crown/planner/ranking.hpp), [include/crown/planner/selection.hpp](../../../../../include/crown/planner/selection.hpp), [include/crown/runtime/ranking_evidence.hpp](../../../../../include/crown/runtime/ranking_evidence.hpp), [include/crown/runtime/delta.hpp](../../../../../include/crown/runtime/delta.hpp), [include/crown/runtime/support.hpp](../../../../../include/crown/runtime/support.hpp), [include/crown/io/ingest.hpp](../../../../../include/crown/io/ingest.hpp), [src/io/event_reader.cpp](../../../../../src/io/event_reader.cpp), [schemas/ranking-export-v1.schema.json](../../../../../schemas/ranking-export-v1.schema.json), [tools/run_ranking_evaluation.py](../../../../../tools/run_ranking_evaluation.py), [docs/ranking_evaluation.md](../../../../ranking_evaluation.md), [docs/ranking.md](../../../../ranking.md), [docs/selection.md](../../../../selection.md) |

```text
require(argc==5
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Validate exact exporter request fields and finite grants. |
| inputs / outputs | Ten fields, schema1, candidate&lt;=32, producer/replay/enumeration&lt;=100M, memory&lt;=4GiB, events&lt;=4096; positive numbers, family/fallback/slot shape and physical options. |
| invariants | slot_limit is a unitless decimal constraint string/null whose semantic validation belongs to selector; byte memory grant is separate. |
| ownership | Request/field set/options are ordinary owning compiler DTOs; no native evidence is imported. |
| failure | Missing/type/unknown/out-of-bound/physical-option failure occurs before training. |
| cost | Request parse/scans and explicit option decoding. |
| Design | [examples/ranking-evaluation/main.cpp](../../../../../examples/ranking-evaluation/main.cpp), [include/crown/planner/search.hpp](../../../../../include/crown/planner/search.hpp), [include/crown/planner/candidates.hpp](../../../../../include/crown/planner/candidates.hpp), [src/planner/candidates.cpp](../../../../../src/planner/candidates.cpp), [include/crown/planner/ranking.hpp](../../../../../include/crown/planner/ranking.hpp), [include/crown/planner/selection.hpp](../../../../../include/crown/planner/selection.hpp), [include/crown/runtime/ranking_evidence.hpp](../../../../../include/crown/runtime/ranking_evidence.hpp), [include/crown/runtime/delta.hpp](../../../../../include/crown/runtime/delta.hpp), [include/crown/runtime/support.hpp](../../../../../include/crown/runtime/support.hpp), [include/crown/io/ingest.hpp](../../../../../include/crown/io/ingest.hpp), [src/io/event_reader.cpp](../../../../../src/io/event_reader.cpp), [src/runtime/ranking_evidence.cpp](../../../../../src/runtime/ranking_evidence.cpp), [src/planner/selection.cpp](../../../../../src/planner/selection.cpp), [docs/ranking_evaluation.md](../../../../ranking_evaluation.md), [docs/ranking.md](../../../../ranking.md), [docs/selection.md](../../../../selection.md) |

```text
const auto sql=read(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Read source/catalog/training only and admit actual nonconstant SQL. |
| inputs / outputs | ParseLimits SQL, 16MiB catalog, 8MiB TRAIN; begin setup clock after file reads, parse catalog and admit SQL. |
| invariants | No evaluation/calibration stream is opened. admitted and nonconstant are required before normalized access. |
| ownership | Input/compiler strings own their bytes; normalized reference borrows live admitted.program. |
| failure | Read/admission/constant-empty rejection fails before search/runtime. |
| cost | Bounded file copies then timed catalog parse/SQL admission; file reads excluded from setup admission clock. |
| Design | [examples/ranking-evaluation/main.cpp](../../../../../examples/ranking-evaluation/main.cpp), [include/crown/planner/search.hpp](../../../../../include/crown/planner/search.hpp), [include/crown/planner/candidates.hpp](../../../../../include/crown/planner/candidates.hpp), [src/planner/candidates.cpp](../../../../../src/planner/candidates.cpp), [include/crown/planner/ranking.hpp](../../../../../include/crown/planner/ranking.hpp), [include/crown/planner/selection.hpp](../../../../../include/crown/planner/selection.hpp), [include/crown/runtime/ranking_evidence.hpp](../../../../../include/crown/runtime/ranking_evidence.hpp), [include/crown/runtime/delta.hpp](../../../../../include/crown/runtime/delta.hpp), [include/crown/runtime/support.hpp](../../../../../include/crown/runtime/support.hpp), [include/crown/io/ingest.hpp](../../../../../include/crown/io/ingest.hpp), [src/io/event_reader.cpp](../../../../../src/io/event_reader.cpp), [src/runtime/ranking_evidence.cpp](../../../../../src/runtime/ranking_evidence.cpp), [src/planner/selection.cpp](../../../../../src/planner/selection.cpp), [docs/ranking_evaluation.md](../../../../ranking_evaluation.md), [docs/ranking.md](../../../../ranking.md), [docs/selection.md](../../../../selection.md) |

```text
planner::SearchOptions search_options;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Prove original minimum native height under supplied finite producer/replay work. |
| inputs / outputs | ExactSearch over normalized source; repeats quantum 10000 until actual optimum, allowing only quantum work/time stops before proof. |
| invariants | Producer completion/incumbent alone is not optimum. Total/depth/allocation/terminal stops without proof fail honestly. |
| ownership | Search owns admitted copies/continuation; copied VerifiedOptimum retains actual shared proof Data after owner teardown. |
| failure | No proof or unexpected stop fails export; no best-found substitution. |
| cost | Timed exact proof and independent replay, with finite separate cumulative ceilings and no CPU-time guarantee. |
| Design | [examples/ranking-evaluation/main.cpp](../../../../../examples/ranking-evaluation/main.cpp), [include/crown/planner/search.hpp](../../../../../include/crown/planner/search.hpp), [include/crown/planner/candidates.hpp](../../../../../include/crown/planner/candidates.hpp), [src/planner/candidates.cpp](../../../../../src/planner/candidates.cpp), [include/crown/planner/ranking.hpp](../../../../../include/crown/planner/ranking.hpp), [include/crown/planner/selection.hpp](../../../../../include/crown/planner/selection.hpp), [include/crown/runtime/ranking_evidence.hpp](../../../../../include/crown/runtime/ranking_evidence.hpp), [include/crown/runtime/delta.hpp](../../../../../include/crown/runtime/delta.hpp), [include/crown/runtime/support.hpp](../../../../../include/crown/runtime/support.hpp), [include/crown/io/ingest.hpp](../../../../../include/crown/io/ingest.hpp), [src/io/event_reader.cpp](../../../../../src/io/event_reader.cpp), [src/runtime/ranking_evidence.cpp](../../../../../src/runtime/ranking_evidence.cpp), [src/planner/selection.cpp](../../../../../src/planner/selection.cpp), [docs/ranking_evaluation.md](../../../../ranking_evaluation.md), [docs/ranking.md](../../../../ranking.md), [docs/selection.md](../../../../selection.md) |

```text
planner::CandidateLimits candidate_options;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Enumerate a bounded retained checked minimum-height prefix. |
| inputs / outputs | Candidate count cap and enumeration work; quantum10000, stop on total_work/candidate_capacity or count/family exhaustion. |
| invariants | Nonempty prefix is required; actual exhaustion/last stop/proposed/duplicates/rejected/taller remain reported. Count reached is not completeness. |
| ownership | Move-only provider owns cursor; allocating snapshot copies handle/event vectors and retains actual shared members without a live provider borrow. |
| failure | Unexpected enumeration stop/empty family/snapshot allocation fails; finite prefix may still be returned on explicit capacity/work stop. |
| cost | Timed enumeration plus snapshot admission; memory and work scale with retained family and generated proposals. |
| Design | [examples/ranking-evaluation/main.cpp](../../../../../examples/ranking-evaluation/main.cpp), [include/crown/planner/search.hpp](../../../../../include/crown/planner/search.hpp), [include/crown/planner/candidates.hpp](../../../../../include/crown/planner/candidates.hpp), [src/planner/candidates.cpp](../../../../../src/planner/candidates.cpp), [include/crown/planner/ranking.hpp](../../../../../include/crown/planner/ranking.hpp), [include/crown/planner/selection.hpp](../../../../../include/crown/planner/selection.hpp), [include/crown/runtime/ranking_evidence.hpp](../../../../../include/crown/runtime/ranking_evidence.hpp), [include/crown/runtime/delta.hpp](../../../../../include/crown/runtime/delta.hpp), [include/crown/runtime/support.hpp](../../../../../include/crown/runtime/support.hpp), [include/crown/io/ingest.hpp](../../../../../include/crown/io/ingest.hpp), [src/io/event_reader.cpp](../../../../../src/io/event_reader.cpp), [src/runtime/ranking_evidence.cpp](../../../../../src/runtime/ranking_evidence.cpp), [src/planner/selection.cpp](../../../../../src/planner/selection.cpp), [docs/ranking_evaluation.md](../../../../ranking_evaluation.md), [docs/ranking.md](../../../../ranking.md), [docs/selection.md](../../../../selection.md) |

```text
const auto basis=planner::lower_normalized
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Build the first checked candidate as an empty maintenance-mode training owner. |
| inputs / outputs | Actual admitted source/candidate/options; finite native memory, observation off, funded EventReader and C01 counters. |
| invariants | Training basis is a real validated plan; observations are actual native facts, not supplied numeric weights. |
| ownership | DeltaRuntime owns imported executable/state; EventReader borrows local istringstream and retains owner plan/account. input is declared before reader and outlives it. |
| failure | Lowering/native/counter/reader admission failure stops before any training input. |
| cost | Checked lowering, native metadata/state/reader/statistics setup; host input stream buffers remain outside native query account. |
| Design | [examples/ranking-evaluation/main.cpp](../../../../../examples/ranking-evaluation/main.cpp), [include/crown/planner/search.hpp](../../../../../include/crown/planner/search.hpp), [include/crown/planner/candidates.hpp](../../../../../include/crown/planner/candidates.hpp), [src/planner/candidates.cpp](../../../../../src/planner/candidates.cpp), [include/crown/planner/ranking.hpp](../../../../../include/crown/planner/ranking.hpp), [include/crown/planner/selection.hpp](../../../../../include/crown/planner/selection.hpp), [include/crown/runtime/ranking_evidence.hpp](../../../../../include/crown/runtime/ranking_evidence.hpp), [include/crown/runtime/delta.hpp](../../../../../include/crown/runtime/delta.hpp), [include/crown/runtime/support.hpp](../../../../../include/crown/runtime/support.hpp), [include/crown/io/ingest.hpp](../../../../../include/crown/io/ingest.hpp), [src/io/event_reader.cpp](../../../../../src/io/event_reader.cpp), [src/runtime/ranking_evidence.cpp](../../../../../src/runtime/ranking_evidence.cpp), [src/planner/selection.cpp](../../../../../src/planner/selection.cpp), [docs/ranking_evaluation.md](../../../../ranking_evaluation.md), [docs/ranking.md](../../../../ranking.md), [docs/selection.md](../../../../selection.md) |

```text
while(const auto* event=reader.peek())
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Replay every bounded training input and acknowledge only after commit/epoch release. |
| inputs / outputs | Cached borrowed event view; begin_view imports, steps, commits local Epoch which releases at inner scope end; reader acknowledges, then events increments. |
| invariants | Training includes no-op committed inputs from empty tables. Event limit overrun/empty trace rejects; no held-out trace is consulted. |
| ownership | Reader cached row survives begin/preparation/commit. Pending/Epoch are move-only; committed epoch cleanup/discard precedes reader cache release. |
| failure | Decode/native grant/preparation failure leaves cached progress unacknowledged and terminates; committed volatile state may exist before later failure. |
| cost | Actual maintenance update work and reader decode/ack for every physical input; no result encoding/sink/WAL. |
| Design | [examples/ranking-evaluation/main.cpp](../../../../../examples/ranking-evaluation/main.cpp), [include/crown/planner/search.hpp](../../../../../include/crown/planner/search.hpp), [include/crown/planner/candidates.hpp](../../../../../include/crown/planner/candidates.hpp), [src/planner/candidates.cpp](../../../../../src/planner/candidates.cpp), [include/crown/planner/ranking.hpp](../../../../../include/crown/planner/ranking.hpp), [include/crown/planner/selection.hpp](../../../../../include/crown/planner/selection.hpp), [include/crown/runtime/ranking_evidence.hpp](../../../../../include/crown/runtime/ranking_evidence.hpp), [include/crown/runtime/delta.hpp](../../../../../include/crown/runtime/delta.hpp), [include/crown/runtime/support.hpp](../../../../../include/crown/runtime/support.hpp), [include/crown/io/ingest.hpp](../../../../../include/crown/io/ingest.hpp), [src/io/event_reader.cpp](../../../../../src/io/event_reader.cpp), [src/runtime/ranking_evidence.cpp](../../../../../src/runtime/ranking_evidence.cpp), [src/planner/selection.cpp](../../../../../src/planner/selection.cpp), [docs/ranking_evaluation.md](../../../../ranking_evaluation.md), [docs/ranking.md](../../../../ranking.md), [docs/selection.md](../../../../selection.md) |

```text
const auto captured=runtime::ranking::capture
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Capture factory-produced candidate-bound training evidence. |
| inputs / outputs | Checked snapshot and quiescent maintenance owner; requires CaptureAttempt.evidence then exports weights/source cardinalities. |
| invariants | Capture validates exact source/plan/current counter availability; absent facts remain reasons. Evidence denominator includes committed physical no-ops. |
| ownership | RuntimeEvidence owns actual shared immutable captured data and plan metadata, no mutable runtime pointer/row lease. Borrowed inputs()/spans require captured handle. |
| failure | Capture/binding/memory/work failure fails exporter instead of importing caller weights. |
| cost | Cold actual statistics/population/source scan and original-account capture allocations, followed by ordinary JSON copies. |
| Design | [examples/ranking-evaluation/main.cpp](../../../../../examples/ranking-evaluation/main.cpp), [include/crown/planner/search.hpp](../../../../../include/crown/planner/search.hpp), [include/crown/planner/candidates.hpp](../../../../../include/crown/planner/candidates.hpp), [src/planner/candidates.cpp](../../../../../src/planner/candidates.cpp), [include/crown/planner/ranking.hpp](../../../../../include/crown/planner/ranking.hpp), [include/crown/planner/selection.hpp](../../../../../include/crown/planner/selection.hpp), [include/crown/runtime/ranking_evidence.hpp](../../../../../include/crown/runtime/ranking_evidence.hpp), [include/crown/runtime/delta.hpp](../../../../../include/crown/runtime/delta.hpp), [include/crown/runtime/support.hpp](../../../../../include/crown/runtime/support.hpp), [include/crown/io/ingest.hpp](../../../../../include/crown/io/ingest.hpp), [src/io/event_reader.cpp](../../../../../src/io/event_reader.cpp), [src/runtime/ranking_evidence.cpp](../../../../../src/runtime/ranking_evidence.cpp), [src/planner/selection.cpp](../../../../../src/planner/selection.cpp), [docs/ranking_evaluation.md](../../../../ranking_evaluation.md), [docs/ranking.md](../../../../ranking.md), [docs/selection.md](../../../../selection.md) |

```text
const std::array<std::pair<ps::Policy,const char*>,3>
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Declare the three independent C05 policies to evaluate. |
| inputs / outputs | height_only, committed_input_native_depth, tuple_index_slots with stable report names. |
| invariants | No C03/C04/C06 policy is enabled by these labels; height/depth/slot units remain distinct. |
| ownership | Fixed array owns enum values and static literal pointers. |
| failure | Declaration cannot fail. |
| cost | Fixed three-entry stack storage. |
| Design | [examples/ranking-evaluation/main.cpp](../../../../../examples/ranking-evaluation/main.cpp), [include/crown/planner/search.hpp](../../../../../include/crown/planner/search.hpp), [include/crown/planner/candidates.hpp](../../../../../include/crown/planner/candidates.hpp), [src/planner/candidates.cpp](../../../../../src/planner/candidates.cpp), [include/crown/planner/ranking.hpp](../../../../../include/crown/planner/ranking.hpp), [include/crown/planner/selection.hpp](../../../../../include/crown/planner/selection.hpp), [include/crown/runtime/ranking_evidence.hpp](../../../../../include/crown/runtime/ranking_evidence.hpp), [include/crown/runtime/delta.hpp](../../../../../include/crown/runtime/delta.hpp), [include/crown/runtime/support.hpp](../../../../../include/crown/runtime/support.hpp), [include/crown/io/ingest.hpp](../../../../../include/crown/io/ingest.hpp), [src/io/event_reader.cpp](../../../../../src/io/event_reader.cpp), [src/runtime/ranking_evidence.cpp](../../../../../src/runtime/ranking_evidence.cpp), [src/planner/selection.cpp](../../../../../src/planner/selection.cpp), [docs/ranking_evaluation.md](../../../../ranking_evaluation.md), [docs/ranking.md](../../../../ranking.md), [docs/selection.md](../../../../selection.md) |

```text
ps::Request select_request;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Apply declared fallback/family/slot constraint to each bounded selection. |
| inputs / outputs | Actual evidence, candidate snapshot, runtime PhysicalBasis, aggregate work20M/payload64MiB and optional decimal slot string. |
| invariants | require_exhausted_family rejects incomplete prefix; retained_prefix scores only retained members. Slots constraint is not actual byte-memory admission. |
| ownership | PhysicalBasis copies actual CompiledProgram descriptor; selector result retains checked plan/evidence/source metadata. Constraint string is an owning request copy. |
| failure | Native select returns explicit Attempt stop/stage/resource/reasons; failure is transported, not converted to an exception merely for lack of selection. |
| cost | Per-policy constraint/score/lowering/binding work and funded result admission under explicit logical grants. |
| Design | [examples/ranking-evaluation/main.cpp](../../../../../examples/ranking-evaluation/main.cpp), [include/crown/planner/search.hpp](../../../../../include/crown/planner/search.hpp), [include/crown/planner/candidates.hpp](../../../../../include/crown/planner/candidates.hpp), [src/planner/candidates.cpp](../../../../../src/planner/candidates.cpp), [include/crown/planner/ranking.hpp](../../../../../include/crown/planner/ranking.hpp), [include/crown/planner/selection.hpp](../../../../../include/crown/planner/selection.hpp), [include/crown/runtime/ranking_evidence.hpp](../../../../../include/crown/runtime/ranking_evidence.hpp), [include/crown/runtime/delta.hpp](../../../../../include/crown/runtime/delta.hpp), [include/crown/runtime/support.hpp](../../../../../include/crown/runtime/support.hpp), [include/crown/io/ingest.hpp](../../../../../include/crown/io/ingest.hpp), [src/io/event_reader.cpp](../../../../../src/io/event_reader.cpp), [src/runtime/ranking_evidence.cpp](../../../../../src/runtime/ranking_evidence.cpp), [src/planner/selection.cpp](../../../../../src/planner/selection.cpp), [docs/ranking_evaluation.md](../../../../ranking_evaluation.md), [docs/ranking.md](../../../../ranking.md), [docs/selection.md](../../../../selection.md) |

```text
Json report{{"policy",name}
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Preserve every policy attempt and available selection decomposition. |
| inputs / outputs | Always reports native stop/stage/resource/reasons/usage/evaluation counts; only present selection adds chosen index/key/plan/effective policy/scores/decisions. |
| invariants | Unavailable policy remains an unavailable report entry; no silent candidate pruning or invented winner. Scores use each assessment effective policy. |
| ownership | Reports own JSON/text copies while assessment/result views borrow live selected result. |
| failure | Transport allocation/export can fail after successful native selection; does not deploy plan. |
| cost | Linear assessment/score/decision export and ordinary variable-width strings/arrays. |
| Design | [examples/ranking-evaluation/main.cpp](../../../../../examples/ranking-evaluation/main.cpp), [include/crown/planner/search.hpp](../../../../../include/crown/planner/search.hpp), [include/crown/planner/candidates.hpp](../../../../../include/crown/planner/candidates.hpp), [src/planner/candidates.cpp](../../../../../src/planner/candidates.cpp), [include/crown/planner/ranking.hpp](../../../../../include/crown/planner/ranking.hpp), [include/crown/planner/selection.hpp](../../../../../include/crown/planner/selection.hpp), [include/crown/runtime/ranking_evidence.hpp](../../../../../include/crown/runtime/ranking_evidence.hpp), [include/crown/runtime/delta.hpp](../../../../../include/crown/runtime/delta.hpp), [include/crown/runtime/support.hpp](../../../../../include/crown/runtime/support.hpp), [include/crown/io/ingest.hpp](../../../../../include/crown/io/ingest.hpp), [src/io/event_reader.cpp](../../../../../src/io/event_reader.cpp), [src/runtime/ranking_evidence.cpp](../../../../../src/runtime/ranking_evidence.cpp), [src/planner/selection.cpp](../../../../../src/planner/selection.cpp), [docs/ranking_evaluation.md](../../../../ranking_evaluation.md), [docs/ranking.md](../../../../ranking.md), [docs/selection.md](../../../../selection.md) |

```text
const auto selected_at=Clock::now();
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Export each actual candidate with the unchanged original height certificate. |
| inputs / outputs | Original VerifiedOptimum certificate DTO plus per-candidate checked lower/physical JSON, version2 and equal-height binding tag. |
| invariants | Does not replace original proof upper witness with candidate. Collector independently validates actual plan and replays original proof, then checks equal height. |
| ownership | PhysicalPlan owns re-lowered compiler metadata; artifact JSON/certificate copies are ordinary deep owning transport data. |
| failure | Certificate export/lowering/JSON/report allocation fails whole export, not a filtered candidate subset. |
| cost | Explicit tree/certificate DTO copying, canonical physical encoding for all members, outside evidence_and_selection setup interval. |
| Design | [examples/ranking-evaluation/main.cpp](../../../../../examples/ranking-evaluation/main.cpp), [include/crown/planner/search.hpp](../../../../../include/crown/planner/search.hpp), [include/crown/planner/candidates.hpp](../../../../../include/crown/planner/candidates.hpp), [src/planner/candidates.cpp](../../../../../src/planner/candidates.cpp), [include/crown/planner/ranking.hpp](../../../../../include/crown/planner/ranking.hpp), [include/crown/planner/selection.hpp](../../../../../include/crown/planner/selection.hpp), [include/crown/runtime/ranking_evidence.hpp](../../../../../include/crown/runtime/ranking_evidence.hpp), [include/crown/runtime/delta.hpp](../../../../../include/crown/runtime/delta.hpp), [include/crown/runtime/support.hpp](../../../../../include/crown/runtime/support.hpp), [include/crown/io/ingest.hpp](../../../../../include/crown/io/ingest.hpp), [src/io/event_reader.cpp](../../../../../src/io/event_reader.cpp), [src/runtime/ranking_evidence.cpp](../../../../../src/runtime/ranking_evidence.cpp), [src/planner/selection.cpp](../../../../../src/planner/selection.cpp), [docs/ranking_evaluation.md](../../../../ranking_evaluation.md), [docs/ranking.md](../../../../ranking.md), [docs/selection.md](../../../../selection.md) |

```text
const auto& search_status=search.progress();
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Report actual search/training scope and setup timings. |
| inputs / outputs | Original height/progress, family work/exhaustion, training identity/counts, selected policies and candidate artifacts; hashes SQL/catalog/training. |
| invariants | Finite normal-form family is not global maintenance-cost search; training-only unitless choices are not ns/byte forecasts, deployment authority or held-out performance. |
| ownership | Const reference extends temporary SearchProgress through scope; identity borrows retained evidence. JSON owns exported copies. |
| failure | Report/hash/encoding/64MiB/flushed stdout failure prevents successful export; does not mutate runtime/selection. |
| cost | Full ordinary report serialization, hashes and selected timing arithmetic outside native event work. Explicit flush completes the process report before its stream-state exit check. |
| Design | [examples/ranking-evaluation/main.cpp](../../../../../examples/ranking-evaluation/main.cpp), [include/crown/planner/search.hpp](../../../../../include/crown/planner/search.hpp), [include/crown/planner/candidates.hpp](../../../../../include/crown/planner/candidates.hpp), [src/planner/candidates.cpp](../../../../../src/planner/candidates.cpp), [include/crown/planner/ranking.hpp](../../../../../include/crown/planner/ranking.hpp), [include/crown/planner/selection.hpp](../../../../../include/crown/planner/selection.hpp), [include/crown/runtime/ranking_evidence.hpp](../../../../../include/crown/runtime/ranking_evidence.hpp), [include/crown/runtime/delta.hpp](../../../../../include/crown/runtime/delta.hpp), [include/crown/runtime/support.hpp](../../../../../include/crown/runtime/support.hpp), [include/crown/io/ingest.hpp](../../../../../include/crown/io/ingest.hpp), [src/io/event_reader.cpp](../../../../../src/io/event_reader.cpp), [src/runtime/ranking_evidence.cpp](../../../../../src/runtime/ranking_evidence.cpp), [src/planner/selection.cpp](../../../../../src/planner/selection.cpp), [docs/ranking_evaluation.md](../../../../ranking_evaluation.md), [docs/ranking.md](../../../../ranking.md), [docs/selection.md](../../../../selection.md) |

## B0012

[Lines 166–166](../../../../../examples/ranking-evaluation/main.cpp#L166); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

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
| Design | [examples/ranking-evaluation/main.cpp](../../../../../examples/ranking-evaluation/main.cpp), [docs/ranking_evaluation.md](../../../../ranking_evaluation.md), [docs/ranking.md](../../../../ranking.md), [docs/selection.md](../../../../selection.md) |

## B0013

[Lines 167–167](../../../../../examples/ranking-evaluation/main.cpp#L167); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
int main(int argc,char** argv)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Contain exporter failures at process boundary. |
| inputs / outputs | Forwards CLI and run result; std::exception prints error and returns 1. |
| invariants | No nested handler silently removes failing candidates or reuses evaluation data. |
| ownership | All run-owned objects unwind before catch; borrowed input stream remains live through reader destruction. |
| failure | Single std::exception catch; run tests immediate stdout state after dump. |
| cost | One outer handler. |
| Design | [examples/ranking-evaluation/main.cpp](../../../../../examples/ranking-evaluation/main.cpp), [docs/ranking_evaluation.md](../../../../ranking_evaluation.md), [docs/ranking.md](../../../../ranking.md), [docs/selection.md](../../../../selection.md) |
