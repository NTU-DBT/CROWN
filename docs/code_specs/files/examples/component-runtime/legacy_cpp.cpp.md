# `examples/component-runtime/legacy_cpp.cpp` — block usage map

[Source](../../../../../examples/component-runtime/legacy_cpp.cpp) · [Source index](../../../README.md) · [Subsystem contracts](../../../subsystem_contracts.md) · [Reviewed primitives](../../../primitives.md)

Demonstrate a concrete public workflow and executable invocation using installed/native CROWN interfaces.

Snapshot SHA-256: `a1922b85e64da03797d2196cb6b74bd6340f16f2158701257ca6a412638628d2`. 95 lines partitioned into 6 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [examples](../../../subsystem_contracts.md#examples). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/cli.md](../../../../cli.md), [docs/native_build.md](../../../../native_build.md), [docs/measurement.md](../../../../measurement.md), [docs/ranking_evaluation.md](../../../../ranking_evaluation.md), [docs/reoptimization.md](../../../../reoptimization.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–13](../../../../../examples/component-runtime/legacy_cpp.cpp#L1) | Imports dependencies; declares namespace scope; declares aliases. | source comment (unverified): // Template ownership keeps the published concrete destructor. CrownBase has no · [reviewed contract](#b0001) |
| [B0002 · 14–53](../../../../../examples/component-runtime/legacy_cpp.cpp#L14) | Callable definition: template&lt;class Factory&gt; Json passes(const Request& request, const std::vector&lt;std::string&gt;& lines, Factory create) | calls Json::array, Clock::now, sink, output; guard require(output.good(),"legacy component output failed");; returns output_passes; growth push_back; 2 loop sites; source comment (unverified): // Template ownership keeps the published concrete destructor. CrownBase has no · [reviewed contract](#b0002) |
| [B0003 · 54–54](../../../../../examples/component-runtime/legacy_cpp.cpp#L54) | Explanatory comments or spacing. |  |
| [B0004 · 55–90](../../../../../examples/component-runtime/legacy_cpp.cpp#L55) | Callable definition: int run(int argc, char** argv) | calls Clock::now, read_request, elapsed, at; guard require((family == "l5_distinct_count" && mode == "cardinality") \|\|; returns std::make_unique&lt;CrownLine5cd&gt;(output,true); std::make_unique&lt;CrownLine5gc&gt;(output,true,mode == @ ); growth make_unique, push_back, reserve; 2 loop sites · [reviewed contract](#b0004) |
| [B0005 · 91–91](../../../../../examples/component-runtime/legacy_cpp.cpp#L91) | Closes surrounding scope/type. | source comment (unverified): // namespace · [reviewed contract](#b0005) |
| [B0006 · 92–95](../../../../../examples/component-runtime/legacy_cpp.cpp#L92) | Callable definition: int main(int argc, char** argv) | calls run, what; returns run(argc,argv); 1 · [reviewed contract](#b0006) |

## B0001

[Lines 1–13](../../../../../examples/component-runtime/legacy_cpp.cpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L1-L13:sha256:8a459f72e710063117201193b8136f639e90e24363f2a857441810cd7251392d
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Import the exact published C++ query classes and shared observer transport, and state safe owner deletion. |
| inputs / outputs | Includes sealed CrownLine5cd/GC headers, common JSON/clock/sink utilities and standard stream/unique_ptr support; introduces the templated pass-loop contract. |
| invariants | CrownBase has no virtual destructor. Concrete owners must be retained and deleted as their actual published type; this region does not patch that baseline header. |
| ownership | Imports own no state; later factory return types determine unique ownership. |
| failure | ABI/header/archive mismatch fails compilation/linking; no fallback implementation is selected. |
| cost | Build and code-generation work only; the template below shares one observation loop without a new query implementation. |
| Design | [docs/legacy_baselines.md](../../../../legacy_baselines.md), [examples/component-runtime/component_request.hpp](../../../../../examples/component-runtime/component_request.hpp), [Refactor.md §11.11 B04 and §14.3–14.4](../../../../../Refactor.md) |

## B0002

[Lines 14–53](../../../../../examples/component-runtime/legacy_cpp.cpp#L14); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L14-L53:sha256:8d04058141e784ca27566e37f7b68ae0f537cb221e4a2a79da27f7dfb069b1f7
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Run matched physical-event observation passes over unchanged, concretely owned legacy C++ queries. |
| inputs / outputs | Factory constructs CD or GC with the bounded ostream; every prebuilt input string calls process then milestone. Captures raw frames only in verify and records real bytes/newlines, API/milestone/loop/teardown times per pass. |
| invariants | Owner is fresh per pass and deleted through its concrete type. Intrinsic parse and delta formatting stay inside process; full formatting stays in milestone. There are no fabricated original-main headers, diagnostic VmPeak probes, signed-delta conversions or correctness flags. |
| ownership | Each pass owns sink, borrowing ostream and concrete unique_ptr in safe destruction order. Verify JSON copies each frame before reuse; measure sink retains no text. Allocator/process state may persist between fresh logical owners. |
| failure | Ostream bad/fail exceptions, output caps, allocation and baseline errors terminate through the CLI. Baseline state can already have changed when observation fails; no rollback/retry is promised. |
| cost | Real published index/annotation work plus intrinsic string/format/sink work. Counts are actual printed records, not expanded paths. Metadata JSON is outside selected API clocks but inside loop wall; observer initialization and concrete destruction are separately timed. No native memory account or pure-dispatch comparison is inferred. |
| Design | [docs/legacy_baselines.md](../../../../legacy_baselines.md), [docs/measurement.md](../../../../measurement.md), [examples/component-runtime/component_request.hpp](../../../../../examples/component-runtime/component_request.hpp) |

## B0004

[Lines 55–90](../../../../../examples/component-runtime/legacy_cpp.cpp#L55); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L55-L90:sha256:2969f8d5680844a418db5bc991163ad23762fee48317f8c7552d428d1e829c48
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Admit only the named fixed C++ comparison routes, prepare intrinsic text inputs once and publish their raw report. |
| inputs / outputs | Reads common request; dispatches l5_distinct_count/cardinality or l5_group_count/full/replacements; requires graph positive uint32 pairs and insert-only CD. Prepares +\|src\|dst strings before timed passes and emits one flushed JSON report. |
| invariants | SQL remains manifest metadata because these are fixed published classes; generic SQL execution is not claimed. +/- unit-set legality comes from the cold common prepass. The selected class/mode is explicit and output phases remain local API observations, not original CLI timing. |
| ownership | Request and prepared string vector are caller-owned. The templated loop owns concrete queries and copies observations; no extra operational row graph or baseline-source mutation is introduced. |
| failure | Unsupported family/mode/table/sign/ID, allocation, baseline or stdout errors produce nonzero status through the single entrypoint. Input preparation precedes owner creation. |
| cost | Request parsing and ordered cold admission are read_request work; integer-to-text preparation is separately timed once. Per-pass work is delegated unchanged. Final JSON encoding/flush lies outside service; no compile latency is invented for prebuilt legacy code. |
| Design | [docs/legacy_baselines.md](../../../../legacy_baselines.md), [docs/measurement.md](../../../../measurement.md), [benchmarks/legacy/dynagox/queries/L5-CNTD.sql](../../../../../benchmarks/legacy/dynagox/queries/L5-CNTD.sql), [benchmarks/legacy/dynagox/queries/L5-CNT-GB.sql](../../../../../benchmarks/legacy/dynagox/queries/L5-CNT-GB.sql) |

## B0005

[Lines 91–91](../../../../../examples/component-runtime/legacy_cpp.cpp#L91); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L91-L91:sha256:c7bfe2f3de133d78a2bc8bb1c4a08450563986ee8254facee698e1dcc57e8162
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Close the local C++ legacy observer implementation namespace. |
| inputs / outputs | Ends helper/template/run declarations before main. |
| invariants | This is a structural scope boundary, not a virtual destruction or baseline cleanup operation. |
| ownership | No owner is independently retained by this declaration boundary. |
| failure | Only compilation can reject malformed scope here. |
| cost | No runtime work. |
| Design | [examples/component-runtime/legacy_cpp.cpp](../../../../../examples/component-runtime/legacy_cpp.cpp) |

## B0006

[Lines 92–95](../../../../../examples/component-runtime/legacy_cpp.cpp#L92); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L92-L95:sha256:7aae8c742e4167d8eeef2e0d4abb84b0ab94a876cff8629f740bf8545de8fe8c
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Expose one CLI failure boundary for the fixed legacy C++ observer. |
| inputs / outputs | Invokes run once; catches standard exceptions, writes one error line and returns one; otherwise forwards the final flushed-output status. |
| invariants | No retry, baseline patch, rollback layer or self-certified correctness verdict is supplied. |
| ownership | Stack unwinding preserves concrete owner deletion from the templated loop; the runner owns captured stdout/stderr. |
| failure | Standard failures become nonzero; process exits/signals inside published code remain external process failures. |
| cost | Constant normal entry/return plus failure-only diagnostics; actual result formatting remains in measured legacy calls. |
| Design | [docs/legacy_baselines.md](../../../../legacy_baselines.md), [docs/measurement.md](../../../../measurement.md) |
