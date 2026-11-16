# `tests/reference/sql_aggregate_runtime_driver.cpp` — block usage map

[Source](../../../../../tests/reference/sql_aggregate_runtime_driver.cpp) · [Source index](../../../README.md) · [Subsystem contracts](../../../subsystem_contracts.md) · [Reviewed primitives](../../../primitives.md)

Drive authentic physical aggregate batches and export full keys and epochs.

Snapshot SHA-256: `6b1637b5d5dd2ac45153baeb6528f6812b6b48000fb477ec1492c44ba49548bf`. 201 lines partitioned into 14 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [tests](../../../subsystem_contracts.md#tests). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/code_review.md](../../../../code_review.md), [docs/reference_fuzz.md](../../../../reference_fuzz.md), [docs/task_ledger.md](../../../../task_ledger.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–14](../../../../../tests/reference/sql_aggregate_runtime_driver.cpp#L1) | Imports dependencies; declares namespace scope; declares aliases; declares values/defaults or compile-time conditions. |  · [reviewed contract](#b0001) |
| [B0002 · 15–19](../../../../../tests/reference/sql_aggregate_runtime_driver.cpp#L15) | Callable definition: Json tuple(const ag::Tuple& value) | calls Json::array, view, push_back, io::write_scalar_view; returns result; growth push_back; 1 loop sites · [reviewed contract](#b0002) |
| [B0003 · 20–26](../../../../../tests/reference/sql_aggregate_runtime_driver.cpp#L20) | Callable definition: Json changes(const runtime::sql_aggregate::Epoch& epoch) | calls Json::array, push_back, tuple; returns result; growth push_back; 1 loop sites · [reviewed contract](#b0003) |
| [B0004 · 27–31](../../../../../tests/reference/sql_aggregate_runtime_driver.cpp#L27) | Callable definition: template&lt;class Engine&gt; Json snapshot(const Engine& runtime) | calls Json::array, push_back, tuple, std::move; returns {{@ , source.sequence}, {@ , std::move(groups)}}; growth push_back; 1 loop sites · [reviewed contract](#b0004) |
| [B0005 · 32–33](../../../../../tests/reference/sql_aggregate_runtime_driver.cpp#L32) | Explanatory comments or spacing. | source comment (unverified): // Test transport only: Python independently decodes the actual durable spool, · [reviewed contract](#b0005) |
| [B0006 · 34–37](../../../../../tests/reference/sql_aggregate_runtime_driver.cpp#L34) | Callable definition: std::string hex(std::string_view bytes) | calls reserve, size, push_back; returns result; growth push_back, reserve; 1 loop sites; source comment (unverified): // Test transport only: Python independently decodes the actual durable spool, · [reviewed contract](#b0006) |
| [B0007 · 38–39](../../../../../tests/reference/sql_aggregate_runtime_driver.cpp#L38) | Explanatory comments or spacing. | source comment (unverified): // Each optional barrier rebuilds from the complete physical image, then the · [reviewed contract](#b0007) |
| [B0008 · 40–52](../../../../../tests/reference/sql_aggregate_runtime_driver.cpp#L40) | Callable definition: void rebuild(runtime::SqlAggregateRuntime& engine, const runtime::sql_aggregate::Options& options) | calls source_snapshot, options, runtime::SqlAggregateRuntime::rebuild_into, resource::MemoryAccount::create; source comment (unverified): // Each optional barrier rebuilds from the complete physical image, then the · [reviewed contract](#b0008) |
| [B0009 · 53–54](../../../../../tests/reference/sql_aggregate_runtime_driver.cpp#L53) | Explanatory comments or spacing. | source comment (unverified): // DTO anchors here exercise image/native reconstruction only. The independent · [reviewed contract](#b0009) |
| [B0010 · 55–72](../../../../../tests/reference/sql_aggregate_runtime_driver.cpp#L55) | Callable definition: void checkpoint(runtime::SqlAggregateRuntime& engine,const recovery::sql_aggregate::Descriptor& descriptor, const runtime::sql_ag… | calls fill, sha256, sequence, progress; source comment (unverified): // DTO anchors here exercise image/native reconstruction only. The independent · [reviewed contract](#b0010) |
| [B0011 · 73–76](../../../../../tests/reference/sql_aggregate_runtime_driver.cpp#L73) | Callable definition: Json type(const frontend::SqlType& value) | calls Json::array; returns {{@ , static_cast&lt;int&gt;(value.kind)}, {@ , value.nullable}, · [reviewed contract](#b0011) |
| [B0012 · 77–190](../../../../../tests/reference/sql_aggregate_runtime_driver.cpp#L77) | Callable definition: Json evaluate(const Json& request) | calls io::read_catalog_payload, at, contains, Json::array; guard assert(session-&gt;state().pending && session-&gt;state().logged==next);; returns sessions?snapshot(*session):snapshot(*runtime); {{@ , request.at(@ )}, {@ , actual.original_sql()},; growth emplace, emplace_back, push_back, reserve; 9 loop sites; source comment (unverified): // Metadata observations below use the receiving owner's genuine import. · [reviewed contract](#b0012) |
| [B0013 · 191–192](../../../../../tests/reference/sql_aggregate_runtime_driver.cpp#L191) | Closes surrounding scope/type. | source comment (unverified): // namespace · [reviewed contract](#b0013) |
| [B0014 · 193–201](../../../../../tests/reference/sql_aggregate_runtime_driver.cpp#L193) | Callable definition: int main() | calls std::getline, evaluate, io::read_json, dump; returns 0; 1; 1 loop sites · [reviewed contract](#b0014) |

## B0001

[Lines 1–14](../../../../../tests/reference/sql_aggregate_runtime_driver.cpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
#include "crown/runtime/sql_aggregate.hpp" #include "crown/recovery/sql_aggregate_checkpoint.hpp" #include "crown/recovery/sql_aggregate_session.hpp" #include "crown/api/error.hpp"
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Import the authentic runtime, checkpoint and R2 Session APIs alongside the driver error boundary. |
| inputs / outputs | Core runtime/checkpoint/session/error headers plus existing catalog/planner/test-fixture headers in; API declarations for the reference driver out. |
| invariants | The session mode uses the public Session factory and recovery owner; no private codec bypass or in-memory mock coordinator is introduced. |
| ownership | Compile-time dependency only; runtime ownership remains in Session and the receiving account. |
| failure | Missing public API fails compilation. |
| cost | Compile-time dependency only. |
| Design | [tests/reference/sql_aggregate_runtime_driver.cpp](../../../../../tests/reference/sql_aggregate_runtime_driver.cpp), [include/crown/recovery/sql_aggregate_session.hpp](../../../../../include/crown/recovery/sql_aggregate_session.hpp), [docs/sql_aggregate_session.md](../../../../sql_aggregate_session.md) |

## B0002

[Lines 15–19](../../../../../tests/reference/sql_aggregate_runtime_driver.cpp#L15); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Json tuple(const ag::Tuple& value)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Export one real owning nullable aggregate Tuple through existing scalar serialization. |
| inputs / outputs | Tuple -&gt; JSON array with NULL/typed decimal values. |
| invariants | No export conversion to ordinary core rows or hidden NULL identity loss. |
| ownership | JSON is explicit caller/test-owned output, Tuple handle remains genuine. |
| failure | Scalar/JSON allocation failure aborts driver process. |
| cost | O(tuple fields/string bytes), external output work. |
| Design | include/crown/io/document.hpp:20, tests/reference/sql_aggregate_runtime_driver.cpp:12, [docs/sql_aggregate_runtime.md](../../../../sql_aggregate_runtime.md), [tests/reference/sql_rows_driver.cpp](../../../../../tests/reference/sql_rows_driver.cpp), [tests/integration/sql_rows_oracle.py](../../../../../tests/integration/sql_rows_oracle.py), [tests/integration/aggregate_sql_oracle.py](../../../../../tests/integration/aggregate_sql_oracle.py), [docs/sql_aggregate_binding.md](../../../../sql_aggregate_binding.md), [tests/integration/sql_aggregate_runtime_oracle.py](../../../../../tests/integration/sql_aggregate_runtime_oracle.py), [tests/reference/sql_aggregate_runtime_driver.cpp](../../../../../tests/reference/sql_aggregate_runtime_driver.cpp) |

## B0003

[Lines 20–26](../../../../../tests/reference/sql_aggregate_runtime_driver.cpp#L20); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Json changes(const runtime::sql_aggregate::Epoch& epoch)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Export actual sealed/committed full-key aggregate output events. |
| inputs / outputs | Genuine Epoch -&gt; array of key/before/after records. |
| invariants | Absent is JSON null, present NULL cells remain arrays; no projected-value dedup. |
| ownership | Copies real output Tuples to external JSON. |
| failure | Export failure fails driver, no fabricated events. |
| cost | O(requested G*output fields/bytes), external harness work. |
| Design | include/crown/runtime/sql_aggregate.hpp:17, tests/reference/sql_aggregate_runtime_driver.cpp:17, [docs/sql_aggregate_runtime.md](../../../../sql_aggregate_runtime.md), [tests/reference/sql_rows_driver.cpp](../../../../../tests/reference/sql_rows_driver.cpp), [tests/integration/sql_rows_oracle.py](../../../../../tests/integration/sql_rows_oracle.py), [tests/integration/aggregate_sql_oracle.py](../../../../../tests/integration/aggregate_sql_oracle.py), [docs/sql_aggregate_binding.md](../../../../sql_aggregate_binding.md), [tests/integration/sql_aggregate_runtime_oracle.py](../../../../../tests/integration/sql_aggregate_runtime_oracle.py), [tests/reference/sql_aggregate_runtime_driver.cpp](../../../../../tests/reference/sql_aggregate_runtime_driver.cpp) |

## B0004

[Lines 27–31](../../../../../tests/reference/sql_aggregate_runtime_driver.cpp#L27); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
template<class Engine> Json snapshot(const Engine& runtime)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Export one eager public snapshot from either the genuine aggregate runtime or genuine Session facade. |
| inputs / outputs | Engine with \`snapshot()\` in; JSON sequence and full-key group/value arrays out. |
| invariants | This generalizes the old runtime-only serializer to Session's public native snapshot; it does not expose private storage or report W/I/C/D. Full hidden group keys remain present. |
| ownership | Temporary snapshot owns aggregate tuples; the returned JSON is independent test output. |
| failure | Runtime/work/memory/snapshot/JSON failure aborts the reference driver operation. |
| cost | Explicit O(all reported groups and tuple fields/bytes) export; not maintenance cost. |
| Design | [include/crown/runtime/sql_aggregate.hpp](../../../../../include/crown/runtime/sql_aggregate.hpp), [include/crown/recovery/sql_aggregate_session.hpp](../../../../../include/crown/recovery/sql_aggregate_session.hpp), [tests/reference/sql_aggregate_runtime_driver.cpp](../../../../../tests/reference/sql_aggregate_runtime_driver.cpp), [docs/sql_aggregate_runtime.md](../../../../sql_aggregate_runtime.md), [docs/sql_aggregate_session.md](../../../../sql_aggregate_session.md) |

## B0005

[Lines 32–33](../../../../../tests/reference/sql_aggregate_runtime_driver.cpp#L32); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L32-L33:sha256:61f6bad4bdb902f0538ee255a78fec8be63ff5592238abd0ccf30128c638c5fa
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Explain the adjacent source contract: Test transport only: Python independently decodes the actual durable spool, including its protected framing, before comparing SQL before/after changes. |
| inputs / outputs | Human-readable source note in; no executable output or checked receipt. |
| invariants | This comment states context or a limitation. It does not itself enforce or prove the described behavior; use the adjacent implementation and its scoped contract. |
| ownership | Source text only; no object or resource lifetime is created. |
| failure | No runtime failure path in this comment; source encoding/comment syntax still belongs to compilation. |
| cost | No runtime operations from the comment. Any work described in the note belongs to the adjacent operation. |
| Design | [tests/reference/sql_aggregate_runtime_driver.cpp](../../../../../tests/reference/sql_aggregate_runtime_driver.cpp), [docs/aggregates.md](../../../../aggregates.md), [docs/code_review.md](../../../../code_review.md) |

## B0006

[Lines 34–37](../../../../../tests/reference/sql_aggregate_runtime_driver.cpp#L34); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::string hex(std::string_view bytes)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Expose the actual durable Session group-epoch spool to Python as bounded lowercase hexadecimal test transport. |
| inputs / outputs | Frame bytes in; two lowercase hex digits per byte out. |
| invariants | Copies bytes only for the reference response; the Python side independently checks framing and hashes. The string is not a receipt or authority token. |
| ownership | Returns a test-owned std::string; does not retain a native frame or alter the sink. |
| failure | String allocation failure aborts the driver request. |
| cost | O(frame bytes) CPU and 2x output storage before JSON serialization. |
| Design | [tests/reference/sql_aggregate_runtime_driver.cpp](../../../../../tests/reference/sql_aggregate_runtime_driver.cpp), [tests/integration/sql_aggregate_runtime_oracle.py](../../../../../tests/integration/sql_aggregate_runtime_oracle.py) |

## B0007

[Lines 38–39](../../../../../tests/reference/sql_aggregate_runtime_driver.cpp#L38); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L38-L39:sha256:6f8bbf0bb39aae189d0824741a08a590b16b45346c40cf39e62cafdd93934dd3
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Explain the adjacent source contract: Each optional barrier rebuilds from the complete physical image, then the mature SQL oracle checks this state and the following epoch's exact diff. |
| inputs / outputs | Human-readable source note in; no executable output or checked receipt. |
| invariants | This comment states context or a limitation. It does not itself enforce or prove the described behavior; use the adjacent implementation and its scoped contract. |
| ownership | Source text only; no object or resource lifetime is created. |
| failure | No runtime failure path in this comment; source encoding/comment syntax still belongs to compilation. |
| cost | No runtime operations from the comment. Any work described in the note belongs to the adjacent operation. |
| Design | [tests/reference/sql_aggregate_runtime_driver.cpp](../../../../../tests/reference/sql_aggregate_runtime_driver.cpp), [docs/aggregates.md](../../../../aggregates.md), [docs/code_review.md](../../../../code_review.md) |

## B0008

[Lines 40–52](../../../../../tests/reference/sql_aggregate_runtime_driver.cpp#L40); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void rebuild(runtime::SqlAggregateRuntime& engine, const runtime::sql_aggregate::Options& options)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Replace one reference driver runtime at an explicit cold barrier after comparing the committed public snapshot. |
| inputs / outputs | A live runtime/options -&gt; owning source_snapshot, finite source/native/group grants (indexed grant only for indexed image), fresh receiving account and rebuilt runtime. |
| invariants | Uses actual source image and public rebuild factory; compares sequence+full groups before move-assigning engine. Image rows/tuples remain input borrows during synchronous reconstruction; no private grant observer or logical fact setter. |
| ownership | Local SourceSnapshot owns/retains immutable row/program handles; restored runtime has a separate receiver. The engine assignment occurs only after comparison passes. |
| failure | Snapshot/factory/comparison errors throw before replacing current engine; restored local dies on mismatch, current owner remains live. |
| cost | A complete cold rebuild plus eager snapshot comparison at each selected barrier; large explicit cold grants are driver-fixture controls, not defaults or resource bounds. |
| Design | [tests/reference/sql_aggregate_runtime_driver.cpp](../../../../../tests/reference/sql_aggregate_runtime_driver.cpp), [include/crown/runtime/sql_aggregate.hpp](../../../../../include/crown/runtime/sql_aggregate.hpp), [docs/sql_source_images.md §Recovery boundary](../../../../sql_source_images.md), [build/verification/w06-sql-aggregate-cold-rebuild-design-v1/design.md §Direct closed factory](../../../../../build/verification/w06-sql-aggregate-cold-rebuild-design-v1/design.md) |

## B0009

[Lines 53–54](../../../../../tests/reference/sql_aggregate_runtime_driver.cpp#L53); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L53-L54:sha256:7500d6803af2d4a503c51a78e4b7ecd8d60ff6c7b89477c94144704b542c6a37
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Explain the adjacent source contract: DTO anchors here exercise image/native reconstruction only. The independent SQL comparison does not pretend this in-memory fixture has an actual sink. |
| inputs / outputs | Human-readable source note in; no executable output or checked receipt. |
| invariants | This comment states context or a limitation. It does not itself enforce or prove the described behavior; use the adjacent implementation and its scoped contract. |
| ownership | Source text only; no object or resource lifetime is created. |
| failure | No runtime failure path in this comment; source encoding/comment syntax still belongs to compilation. |
| cost | No runtime operations from the comment. Any work described in the note belongs to the adjacent operation. |
| Design | [tests/reference/sql_aggregate_runtime_driver.cpp](../../../../../tests/reference/sql_aggregate_runtime_driver.cpp), [docs/aggregates.md](../../../../aggregates.md), [docs/code_review.md](../../../../code_review.md) |

## B0010

[Lines 55–72](../../../../../tests/reference/sql_aggregate_runtime_driver.cpp#L55); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void checkpoint(runtime::SqlAggregateRuntime& engine
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | At a selected test frontier, serialize the actual runtime source image and replace the driver runtime with genuine cold restoration. |
| inputs / outputs | Reads live runtime/descriptor/original Options; creates C=I metadata and a synthetic delivery DTO, encodes source_snapshot, restores under generous separate rebuild caps, compares exported snapshot/progress, then moves restored runtime into engine. |
| invariants | The fake anchor is test DTO data, not an actual sink receipt. SQL oracle mode counts the initial frontier and each post-command frontier; no native row/group mirror is supplied. |
| ownership | Encoded image bytes are charged to the current engine account until this helper returns; restoration uses a newly created receiver account from the original memory policy. Replacing engine releases the previous facade after comparison. |
| failure | Descriptor, source, codec/account, rebuild, and explicit snapshot mismatch failures propagate to the JSONL driver boundary. |
| cost | One real full source encode and cold restore per selected frontier, including key sorting, frame hashing, final constraints and build work; test-only path, not update overhead. |
| Design | [tests/reference/sql_aggregate_runtime_driver.cpp](../../../../../tests/reference/sql_aggregate_runtime_driver.cpp), [include/crown/recovery/sql_aggregate_checkpoint.hpp](../../../../../include/crown/recovery/sql_aggregate_checkpoint.hpp), [tests/integration/sql_aggregate_runtime_oracle.py](../../../../../tests/integration/sql_aggregate_runtime_oracle.py), [docs/sql_aggregate_checkpoint.md §State and authority](../../../../sql_aggregate_checkpoint.md), [docs/sql_aggregate_checkpoint.md §Verification boundaries](../../../../sql_aggregate_checkpoint.md) |

## B0011

[Lines 73–76](../../../../../tests/reference/sql_aggregate_runtime_driver.cpp#L73); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Json type(const frontend::SqlType& value)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Expose actual immutable output/key type and declared numeric scale. |
| inputs / outputs | Genuine SqlType -&gt; kind/nullable/decimal JSON. |
| invariants | Uses authentic receiving metadata; no input program/descriptor constructed. |
| ownership | Copies scalar metadata only. |
| failure | JSON allocation failure propagates. |
| cost | O(1) metadata fields. |
| Design | include/crown/frontend/bind.hpp:9, tests/reference/sql_aggregate_runtime_driver.cpp:29, [docs/sql_aggregate_runtime.md](../../../../sql_aggregate_runtime.md), [tests/reference/sql_rows_driver.cpp](../../../../../tests/reference/sql_rows_driver.cpp), [tests/integration/sql_rows_oracle.py](../../../../../tests/integration/sql_rows_oracle.py), [tests/integration/aggregate_sql_oracle.py](../../../../../tests/integration/aggregate_sql_oracle.py), [docs/sql_aggregate_binding.md](../../../../sql_aggregate_binding.md), [tests/integration/sql_aggregate_runtime_oracle.py](../../../../../tests/integration/sql_aggregate_runtime_oracle.py), [tests/reference/sql_aggregate_runtime_driver.cpp](../../../../../tests/reference/sql_aggregate_runtime_driver.cpp) |

## B0012

[Lines 77–190](../../../../../tests/reference/sql_aggregate_runtime_driver.cpp#L77); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Json evaluate(const Json& request)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Run the requested authentic SQL aggregate case through direct runtime, physical-rebuild/checkpoint controls or the new real Session lifecycle control. |
| inputs / outputs | One test JSON request in; metadata, sequence/group snapshots, per-epoch changes and mode counters out. |
| invariants | Original SQL/catalog/parameters are bound by the actual frontend and checked planner tree. Session mode constructs a real Session, drops the caller program before reporting from the receiving descriptor, logs each command, reopens from persisted root/descriptor/checkpoint/WAL, decides, reopens and compares exact spool bytes, delivers through the real sink, reopens, checkpoints and reopens again. The four reopens per committed epoch and initial-plus-each-epoch durable checkpoint count are local test assertions. The old checkpoint-only delivery DTO remains a synthetic fixture and is not used as Session sink evidence. The receiving MemoryAccount is created only for the Session or checkpoint branches; the plain/rebuild path does not allocate an unused account controller. This driver does not report W/I/C/D to Python and is not the product CLI. Parameter/source NULLs directly emplace disengaged optionals and present decoded Values directly emplace through std::in_place. All owned batch rows are complete before borrowed Cell/string views and replacement spans are formed. Source ordering, scalar tags, weights and native batch/session semantics are unchanged; the three temporary-optional ternary loops are removed. The Python caller admits mutually exclusive rebuild/checkpoint/Session modes. |
| ownership | Only Session/checkpoint mode creates the receiving account; the plain runtime path keeps its prior owner behavior. In Session mode the test directory and Session own actual files/locks; Python receives copied JSON and spool hex only. Ordinary parameter Values remain owned until actual binding. Owned batch rows and borrowed vectors remain stable through synchronous prepare/commit or Session.log; the genuine Session owns logged rows before reopen. No borrowed scalar view outlives its owned input in these loops. |
| failure | Binding/planner/session/file/recovery failures, spool mismatch or assertion aborts the request and reach the existing process-level error boundary. Direct nullable emplacement retains the same decode/allocation error propagation and top-level boundary; GCC13 O3 warning avoidance adds no warning suppression or per-cell catch. |
| cost | Session mode performs four full cold reopens and one checkpoint rotation for each committed command, in addition to real log/native/sink work. The receiving account controller is created only when a Session/checkpoint owns it. Fixture grants and counts are verification controls, not production cost or timing claims. Input DTO work remains proportional to field/scalar width with the existing reserves. Direct emplacement removes temporary optional wrappers; no native runtime algorithm, state or work grant changes. |
| Design | [tests/reference/sql_aggregate_runtime_driver.cpp](../../../../../tests/reference/sql_aggregate_runtime_driver.cpp), [include/crown/recovery/sql_aggregate_session.hpp](../../../../../include/crown/recovery/sql_aggregate_session.hpp), [include/crown/runtime/sql_aggregate.hpp](../../../../../include/crown/runtime/sql_aggregate.hpp), Refactor.md:1325, [docs/sql_aggregate_session.md](../../../../sql_aggregate_session.md) |

## B0013

[Lines 191–192](../../../../../tests/reference/sql_aggregate_runtime_driver.cpp#L191); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
} // namespace
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Close the driver’s private helper namespace after tuple, result and evaluate serializers. |
| inputs / outputs | C++ scope close only. |
| invariants | Main remains the sole line-oriented process boundary. |
| ownership | No ownership action. |
| failure | Compile-time scope validation. |
| cost | Zero runtime work. |
| Design | [tests/integration/sql_rows_oracle.py](../../../../../tests/integration/sql_rows_oracle.py), [tests/integration/aggregate_sql_oracle.py](../../../../../tests/integration/aggregate_sql_oracle.py), tests/reference/sql_aggregate_runtime_driver.cpp:103, [docs/sql_aggregate_runtime.md](../../../../sql_aggregate_runtime.md), [tests/reference/sql_rows_driver.cpp](../../../../../tests/reference/sql_rows_driver.cpp), [docs/sql_aggregate_binding.md](../../../../sql_aggregate_binding.md), [tests/integration/sql_aggregate_runtime_oracle.py](../../../../../tests/integration/sql_aggregate_runtime_oracle.py), [tests/reference/sql_aggregate_runtime_driver.cpp](../../../../../tests/reference/sql_aggregate_runtime_driver.cpp) |

## B0014

[Lines 193–201](../../../../../tests/reference/sql_aggregate_runtime_driver.cpp#L193); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
int main()
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Stream strict JSONL requests through the authentic C++ driver and report one process-level failure. |
| inputs / outputs | Input JSONL requests -&gt; one JSON response per fully evaluated request; malformed/failed request reports stderr and exit 1. |
| invariants | Uses shared duplicate-key/depth-aware read_json; no per-batch catch/retry or success response for a failed evaluation. |
| ownership | Each evaluate call owns and tears down ordinary request objects/runtime; stdout JSON belongs to caller. |
| failure | Single std::exception boundary is only process reporting; it does not swallow errors or certify allocation seams. |
| cost | Bounded streaming line handling and JSON serialization outside CROWN account. |
| Design | tests/reference/sql_rows_driver.cpp:62, include/crown/io/document.hpp:12, tests/reference/sql_aggregate_runtime_driver.cpp:105, [docs/sql_aggregate_runtime.md](../../../../sql_aggregate_runtime.md), [tests/reference/sql_rows_driver.cpp](../../../../../tests/reference/sql_rows_driver.cpp), [tests/integration/sql_rows_oracle.py](../../../../../tests/integration/sql_rows_oracle.py), [tests/integration/aggregate_sql_oracle.py](../../../../../tests/integration/aggregate_sql_oracle.py), [docs/sql_aggregate_binding.md](../../../../sql_aggregate_binding.md), [tests/integration/sql_aggregate_runtime_oracle.py](../../../../../tests/integration/sql_aggregate_runtime_oracle.py), [tests/reference/sql_aggregate_runtime_driver.cpp](../../../../../tests/reference/sql_aggregate_runtime_driver.cpp) |
