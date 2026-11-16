# `examples/input-specialization/main.cpp` — block usage map

[Source](../../../../../examples/input-specialization/main.cpp) · [Source index](../../../README.md) · [Subsystem contracts](../../../subsystem_contracts.md) · [Reviewed primitives](../../../primitives.md)

Demonstrate a concrete public workflow and executable invocation using installed/native CROWN interfaces.

Snapshot SHA-256: `92dd597209eec4beec3703e75028fc7cd2e5c7632ecc9e37467b64195e2267b4`. 183 lines partitioned into 12 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [examples](../../../subsystem_contracts.md#examples). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/cli.md](../../../../cli.md), [docs/native_build.md](../../../../native_build.md), [docs/measurement.md](../../../../measurement.md), [docs/ranking_evaluation.md](../../../../ranking_evaluation.md), [docs/reoptimization.md](../../../../reoptimization.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–23](../../../../../examples/input-specialization/main.cpp#L1) | Imports dependencies; declares namespace scope; declares aliases; declares values/defaults or compile-time conditions. |  · [reviewed contract](#b0001) |
| [B0002 · 24–24](../../../../../examples/input-specialization/main.cpp#L24) | Callable definition: void require(bool value,const char* message) | calls Error; guard void require(bool value,const char* message) {if(!value)throw Error("input_specialization",message)… · [reviewed contract](#b0002) |
| [B0003 · 25–28](../../../../../examples/input-specialization/main.cpp#L25) | Callable definition: U64 integer(const Json& value,U64 maximum) | calls require, is_number_integer, is_number_unsigned; guard require(value.is_number_integer() && (value.is_number_unsigned() \|\| value.get&lt;std::int64_t&gt;()&gt;=0),"…; returns result · [reviewed contract](#b0003) |
| [B0004 · 29–35](../../../../../examples/input-specialization/main.cpp#L29) | Callable definition: std::string read(const char* path,std::size_t maximum) | calls stream, require, bool, gcount; guard std::ifstream stream(path,std::ios::binary);require(bool(stream),"cannot read specialization input"…; returns text; 1 loop sites · [reviewed contract](#b0004) |
| [B0005 · 36–39](../../../../../examples/input-specialization/main.cpp#L36) | Callable definition: void closed(const Json& value,const std::set&lt;std::string&gt;& fields) | calls require, is_object, size, items; guard require(value.is_object() && value.size()==fields.size(),"closed specialization request fields diff…; 1 loop sites · [reviewed contract](#b0005) |
| [B0006 · 40–42](../../../../../examples/input-specialization/main.cpp#L40) | Callable definition: Json row(storage::TupleValuesView values) | calls Json::array, push_back, io::write_scalar_view; returns result; growth push_back; 1 loop sites · [reviewed contract](#b0006) |
| [B0007 · 43–48](../../../../../examples/input-specialization/main.cpp#L43) | Callable definition: Json current(runtime::DeltaRuntime& owner,U64 work,U64& records,U64 limit,bool verify) | calls Json::array, results, next, require; guard while(auto tuple=cursor.next()) {require(records&lt;limit,"specialization output record grant exhauste…; returns result; growth push_back; 1 loop sites · [reviewed contract](#b0007) |
| [B0008 · 49–52](../../../../../examples/input-specialization/main.cpp#L49) | Callable definition: Json memory(const resource::MemoryStatistics& value) | calls ; returns {{@ ,value.limit_bytes},{@ ,value.current.requested_bytes}, · [reviewed contract](#b0008) |
| [B0009 · 53–56](../../../../../examples/input-specialization/main.cpp#L53) | Callable definition: Json work(storage::IndexWork value) | calls ; returns {{@ ,value.structural_steps},{@ ,value.scalar_fields},{@ ,value.scalar_bytes}, · [reviewed contract](#b0009) |
| [B0010 · 57–179](../../../../../examples/input-specialization/main.cpp#L57) | Callable definition: int run(int argc,char** argv) | calls Clock::now, require, io::read_json, read; guard require(argc==5,"usage: crown_input_specialization SQL CATALOG BOUND_INPUT.jsonl REQUEST.json");; returns verify?Clock::time_point{}:Clock::now(); static_cast&lt;U64&gt;(value); growth emplace, insert, push_back; 5 loop sites · [reviewed contract](#b0010) |
| [B0011 · 180–180](../../../../../examples/input-specialization/main.cpp#L180) | Closes surrounding scope/type. | source comment (unverified): // namespace · [reviewed contract](#b0011) |
| [B0012 · 181–183](../../../../../examples/input-specialization/main.cpp#L181) | Callable definition: int main(int argc,char** argv) | calls run, what; returns run(argc,argv); 1 · [reviewed contract](#b0012) |

## B0001

[Lines 1–23](../../../../../examples/input-specialization/main.cpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L1-L23:sha256:002cb84add889021edaeb08cc186a3a599958f7dedd8176dab7ed4568444747b
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Bind the standalone matched-execution diagnostic to existing public SQL/planner/runtime/IO APIs. |
| inputs / outputs | Public dependencies and local Json/U64/steady_clock aliases. |
| invariants | No alternate engine, caller code, support propagation, parser or output pipeline is introduced. |
| ownership | No runtime owner in includes/aliases; later code owns finite accounts. |
| failure | Build/link diagnostics only. |
| cost | Compile-time dependencies; both modes share one executable image. |
| Design | [docs/sql_normalization.md](../../../../sql_normalization.md), [docs/sql_support.md](../../../../sql_support.md), [docs/scalars.md](../../../../scalars.md), [src/frontend/sql_scalar.hpp](../../../../../src/frontend/sql_scalar.hpp), [docs/query_memory.md](../../../../query_memory.md), [docs/memory_accounts.md](../../../../memory_accounts.md), [include/crown/storage/index_work.hpp](../../../../../include/crown/storage/index_work.hpp) |

## B0002

[Lines 24–24](../../../../../examples/input-specialization/main.cpp#L24); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L24-L24:sha256:627415530fbfdfd222191b1ccc659eafb2264d299e2febc80222d0f8644e07b9
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Reject diagnostic contract violations with a stable error code. |
| inputs / outputs | Condition/message; crown::Error(input_specialization, message) when false. |
| invariants | Failures stop the cold driver and cannot emit a success report. |
| ownership | Exception owns diagnostic; source borrowed. |
| failure | Error reaches one outer main catch/nonzero exit. |
| cost | One branch per cold diagnostic check; no core hook. |
| Design | [Refactor.md §14.1–14.4](../../../../../Refactor.md), [docs/measurement.md](../../../../measurement.md), [build/verification/v61-b04-completion-audit-v1/requirement-matrix-v1.json](../../../../../build/verification/v61-b04-completion-audit-v1/requirement-matrix-v1.json) |

## B0003

[Lines 25–28](../../../../../examples/input-specialization/main.cpp#L25); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L25-L28:sha256:96594c9dd298817d71e613bc8d0ebb9854f54b351d12886d53d8612b06d3c678
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Read an exact bounded nonnegative JSON integer. |
| inputs / outputs | JSON scalar and finite maximum; U64 result. |
| invariants | Boolean/float/negative/out-of-bound values reject; schema version cannot accept true as one. |
| ownership | No retained JSON view escapes. |
| failure | Contract or JSON conversion failures reach main nonzero exit. |
| cost | Constant cold scalar validation. |
| Design | [Refactor.md §14.1–14.4](../../../../../Refactor.md), [docs/measurement.md](../../../../measurement.md), [build/verification/v61-b04-completion-audit-v1/requirement-matrix-v1.json](../../../../../build/verification/v61-b04-completion-audit-v1/requirement-matrix-v1.json) |

## B0004

[Lines 29–35](../../../../../examples/input-specialization/main.cpp#L29); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L29-L35:sha256:29a4aa7312ce9455a74aee606766bd3664be412f289e4f719c846609c9a02c25
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Read one input file under an explicit byte grant. |
| inputs / outputs | Path and finite maximum; owned binary text. |
| invariants | Chunk growth is checked against remaining bytes before append; stream badbit/open errors reject. |
| ownership | Function owns file stream/text; returned text remains alive for parse/readers. |
| failure | Read/size/allocation errors propagate before native study executes. |
| cost | One full bounded file copy; cost belongs to whole-child/read scope. |
| Design | [Refactor.md §14.1–14.4](../../../../../Refactor.md), [docs/measurement.md](../../../../measurement.md), [build/verification/v61-b04-completion-audit-v1/requirement-matrix-v1.json](../../../../../build/verification/v61-b04-completion-audit-v1/requirement-matrix-v1.json) |

## B0005

[Lines 36–39](../../../../../examples/input-specialization/main.cpp#L36); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L36-L39:sha256:b169c054c6b3f8aee76b6e50646bfdd62662a214381a41f64779127ded999916
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Enforce the closed diagnostic request object shape. |
| inputs / outputs | JSON object and exact allowed-key set. |
| invariants | Object size and every key must match; unknown/missing fields do not silently default. |
| ownership | Borrows JSON and key set for the call. |
| failure | Contract failure reaches main. |
| cost | Cold object/key traversal; no per-input engine overhead. |
| Design | [Refactor.md §14.1–14.4](../../../../../Refactor.md), [docs/measurement.md](../../../../measurement.md), [build/verification/v61-b04-completion-audit-v1/requirement-matrix-v1.json](../../../../../build/verification/v61-b04-completion-audit-v1/requirement-matrix-v1.json) |

## B0006

[Lines 40–42](../../../../../examples/input-specialization/main.cpp#L40); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L40-L42:sha256:fdde9a1e22421ecf0f8a9c3e7468d2a5fdf51d19b833b1df47ffd5a9218f23ac
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Serialize a real native tuple through its public inline scalar view iterator. |
| inputs / outputs | TupleValuesView; JSON array of write_scalar_view outputs. |
| invariants | No RowView conversion or owning Row mirror is assumed; scalar wire spelling remains the shared public serializer. |
| ownership | Borrows tuple cells during call; JSON owns encoded values. |
| failure | Serializer/allocation failures abort diagnostic. |
| cost | Linear row/cell and scalar-byte encoding cost; verify capture only. |
| Design | [docs/sql_normalization.md](../../../../sql_normalization.md), [docs/sql_support.md](../../../../sql_support.md), [docs/scalars.md](../../../../scalars.md), [src/frontend/sql_scalar.hpp](../../../../../src/frontend/sql_scalar.hpp) |

## B0007

[Lines 43–48](../../../../../examples/input-specialization/main.cpp#L43); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L43-L48:sha256:2316736126421610d165bc9b411eb15f945f1a376619e929736044f68fef3bea
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Drain the actual native SQL snapshot in both verification and measurement. |
| inputs / outputs | Owner, finite cursor work, cumulative record counter/cap and verify flag; optionally materialized JSON rows. |
| invariants | Both modes drain identical cursor; each tuple consumes output obligation. Measure omits capture allocation but still enumerates; zero remaining output capacity rejects before count overflow. |
| ownership | Cursor lease is local; verification JSON owns scalar encoding. |
| failure | Native cursor/work/account/output-cap failures stop driver. |
| cost | Actual output enumeration in both modes; encoding only in verify. Initial drain is in initialize timer. |
| Design | [docs/sql_normalization.md](../../../../sql_normalization.md), [docs/sql_support.md](../../../../sql_support.md), [docs/scalars.md](../../../../scalars.md), [src/frontend/sql_scalar.hpp](../../../../../src/frontend/sql_scalar.hpp), [Refactor.md §14.1–14.4](../../../../../Refactor.md), [docs/measurement.md](../../../../measurement.md), [build/verification/v61-b04-completion-audit-v1/requirement-matrix-v1.json](../../../../../build/verification/v61-b04-completion-audit-v1/requirement-matrix-v1.json) |

## B0008

[Lines 49–52](../../../../../examples/input-specialization/main.cpp#L49); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L49-L52:sha256:ae0a26ec79271993e0160a216feaf63122a9d6baf2114cab05bdd77f9b77a9fa
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Expose native requested-byte account scope distinctly from child RSS. |
| inputs / outputs | MemoryStatistics; finite limit/current/peak requested bytes and allocation count JSON. |
| invariants | Requested bytes exclude allocator/OS overhead and are not RSS or a provider-only peak. |
| ownership | Copies scalar counters; JSON owns fields. |
| failure | JSON allocation failures propagate. |
| cost | Fixed scalar reporting outside engine execution. |
| Design | [docs/query_memory.md](../../../../query_memory.md), [docs/memory_accounts.md](../../../../memory_accounts.md), [include/crown/storage/index_work.hpp](../../../../../include/crown/storage/index_work.hpp) |

## B0009

[Lines 53–56](../../../../../examples/input-specialization/main.cpp#L53); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L53-L56:sha256:6fa29acd9cb73f0f4975afff9d74caf7128d26d25045169f186ef87d195a1778
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Spell the five native IndexWork domains without converting units. |
| inputs / outputs | IndexWork value; structural/scalar-field/scalar-byte/pointer-slot/link-action JSON. |
| invariants | These are logical admitted units, not CPU instructions, time or bytes of full memory. |
| ownership | Value input and owning JSON output. |
| failure | JSON allocation failures propagate. |
| cost | Fixed five-field encoding. |
| Design | [docs/query_memory.md](../../../../query_memory.md), [docs/memory_accounts.md](../../../../memory_accounts.md), [include/crown/storage/index_work.hpp](../../../../../include/crown/storage/index_work.hpp) |

## B0010

[Lines 57–179](../../../../../examples/input-specialization/main.cpp#L57); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L57-L179:sha256:a2a71de6024d9642ed63d16e882e152cc0615b2ce07ae060a9ec422356e4925a
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Run an exact matched native program with explicit setup, output and execution-policy boundaries. |
| inputs / outputs | SQL CATALOG BOUND_INPUT.jsonl REQUEST; closed finite verify/measure request. Admits real SQL and genuine minimum for active route, canonical empty operator for constant false. Emits b04_input_specialization_report_v1. |
| invariants | Both modes share SQL/source/tree/backend/trace/output and explicit cold receiving grant. Threaded selection is automatic prepare_inputs, interpreter is freeze. Each fresh owner freezes selected mode. Begin/prepare/commit precedes signed delta drain, epoch release, full SQL snapshot, then input acknowledgement. Verify clocks are null; measure clocks surround actual phases. Epoch output_records/delta_records count signed delta; snapshot_records and pass total include full observation. No global cache/JIT/full-B04 or speedup claim. |
| ownership | Finite compiler, receiving program and per-owner query accounts; input texts outlive readers; pending epoch destroyed before observation, committed epoch released before snapshot; report owns captures. metadata_bytes is extra table capacity only; complete account and child RSS scopes are separate. |
| failure | Closed request, byte/record/event/work/account/SQL/proof/stream/output failures propagate to one outer catch; no partial success JSON or retry. Cold copy failure leaves basis unchanged. |
| cost | shared_program_ns includes SQL/proof/lower/base compile. execution_prepare_ns includes base receiving freeze plus optional preparation; base work separately reported. Per-pass initialize includes owner reconstruction/initial snapshot, apply native CP, output delta+snapshot, release epoch, teardown owner. Whole-child additionally includes IO/report/warmups; no pure worker or dispatch-only timer. |
| Design | [docs/sql_normalization.md](../../../../sql_normalization.md), [docs/sql_support.md](../../../../sql_support.md), [docs/scalars.md](../../../../scalars.md), [src/frontend/sql_scalar.hpp](../../../../../src/frontend/sql_scalar.hpp), [docs/query_memory.md](../../../../query_memory.md), [docs/memory_accounts.md](../../../../memory_accounts.md), [include/crown/storage/index_work.hpp](../../../../../include/crown/storage/index_work.hpp), [Refactor.md §14.1–14.4](../../../../../Refactor.md), [docs/measurement.md](../../../../measurement.md), [build/verification/v61-b04-completion-audit-v1/requirement-matrix-v1.json](../../../../../build/verification/v61-b04-completion-audit-v1/requirement-matrix-v1.json) |

## B0011

[Lines 180–180](../../../../../examples/input-specialization/main.cpp#L180); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L180-L180:sha256:533f16bca7d58f44b3103b92e3485d22cfbb34bbad5ea3f3fa3b5a9dcb24ec89
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Close the diagnostic implementation scope. |
| inputs / outputs | Namespace closure only. |
| invariants | No additional native API exported. |
| ownership | No owner. |
| failure | No failure. |
| cost | No runtime work. |
| Design | [Refactor.md §14.1–14.4](../../../../../Refactor.md), [docs/measurement.md](../../../../measurement.md), [build/verification/v61-b04-completion-audit-v1/requirement-matrix-v1.json](../../../../../build/verification/v61-b04-completion-audit-v1/requirement-matrix-v1.json) |

## B0012

[Lines 181–183](../../../../../examples/input-specialization/main.cpp#L181); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L181-L183:sha256:a984d60e1a44fe13bb731ab81c96187ffc4fe13ef5dd388d0d9d60ebc19cc7bc
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Map diagnostic success/failure to a flushed CLI protocol. |
| inputs / outputs | Process arguments; run exit status, stderr exception diagnostic on failure. |
| invariants | run flushes stdout and checks stream state; exceptions cannot be formatted as success JSON. |
| ownership | Stack unwinding releases local native owners; OS process owns streams. |
| failure | std::exception reaches stderr/nonzero; buffered output failure returns one. |
| cost | One outer catch; no nested retry/error framework. |
| Design | [Refactor.md §14.1–14.4](../../../../../Refactor.md), [docs/measurement.md](../../../../measurement.md), [build/verification/v61-b04-completion-audit-v1/requirement-matrix-v1.json](../../../../../build/verification/v61-b04-completion-audit-v1/requirement-matrix-v1.json) |
