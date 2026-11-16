# `examples/component-runtime/aggregate.cpp` — block usage map

[Source](../../../../../examples/component-runtime/aggregate.cpp) · [Source index](../../../README.md) · [Subsystem contracts](../../../subsystem_contracts.md) · [Reviewed primitives](../../../primitives.md)

Demonstrate a concrete public workflow and executable invocation using installed/native CROWN interfaces.

Snapshot SHA-256: `034720303a4009d95ef6fa4989751930cc0dd9fb7d52d4f808c13384f789754e`. 204 lines partitioned into 11 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [examples](../../../subsystem_contracts.md#examples). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/cli.md](../../../../cli.md), [docs/native_build.md](../../../../native_build.md), [docs/measurement.md](../../../../measurement.md), [docs/ranking_evaluation.md](../../../../ranking_evaluation.md), [docs/reoptimization.md](../../../../reoptimization.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–18](../../../../../examples/component-runtime/aggregate.cpp#L1) | Imports dependencies; declares namespace scope; declares aliases; declares values/defaults or compile-time conditions. | source comment (unverified): // Export only observations. The returned ordinary JSON is caller/report memory, · [reviewed contract](#b0001) |
| [B0002 · 19–23](../../../../../examples/component-runtime/aggregate.cpp#L19) | Callable definition: Json tuple(const ag::Tuple& value) | calls Json::array, view, push_back, io::write_scalar_view; returns output; growth push_back; 1 loop sites; source comment (unverified): // Export only observations. The returned ordinary JSON is caller/report memory, · [reviewed contract](#b0002) |
| [B0003 · 24–27](../../../../../examples/component-runtime/aggregate.cpp#L24) | Callable definition: Json memory(const resource::MemoryStatistics& value) | calls ; returns {{@ , value.limit_bytes}, {@ , value.current.requested_bytes}, · [reviewed contract](#b0003) |
| [B0004 · 28–31](../../../../../examples/component-runtime/aggregate.cpp#L28) | Explanatory comments or spacing. | source comment (unverified): // COUNT-only source presentation is a guarded component ablation. The genuine · [reviewed contract](#b0004) |
| [B0005 · 32–44](../../../../../examples/component-runtime/aggregate.cpp#L32) | Callable definition: void source_count_contract(const frontend::AggregateProgram& kernel) | calls require, full_input_group_key, group_columns, empty; guard require(kernel.full_input_group_key() && !kernel.group_columns().empty(),; 1 loop sites; source comment (unverified): // COUNT-only source presentation is a guarded component ablation. The genuine · [reviewed contract](#b0005) |
| [B0006 · 45–47](../../../../../examples/component-runtime/aggregate.cpp#L45) | Explanatory comments or spacing. | source comment (unverified): // Public SQL rows retain repeated SELECT/GROUP BY references. Select the · [reviewed contract](#b0006) |
| [B0007 · 48–63](../../../../../examples/component-runtime/aggregate.cpp#L48) | Callable definition: Json source_group(const runtime::sql_rows::Result& row, const frontend::SqlAggregateProgram& program) | calls kernel_program, inputs, view, Json::array; returns {{@ , std::move(key)}, {@ , std::move(output)}}; growth push_back; 2 loop sites; source comment (unverified): // Public SQL rows retain repeated SELECT/GROUP BY references. Select the · [reviewed contract](#b0007) |
| [B0008 · 64–64](../../../../../examples/component-runtime/aggregate.cpp#L64) | Explanatory comments or spacing. |  |
| [B0009 · 65–199](../../../../../examples/component-runtime/aggregate.cpp#L65) | Callable definition: int run(int argc, char** argv) | calls Clock::now, read_request, elapsed, at; guard require(mode == "groups_full" \|\| mode == "groups_replacements", "aggregate output mode is unsupport…; returns std::cout ? 0 : 1; growth emplace, push_back, reserve; 7 loop sites; source comment (unverified): // Shared cold SQL/proof work is charged once per invocation, never per pass. · [reviewed contract](#b0009) |
| [B0010 · 200–200](../../../../../examples/component-runtime/aggregate.cpp#L200) | Closes surrounding scope/type. | source comment (unverified): // namespace · [reviewed contract](#b0010) |
| [B0011 · 201–204](../../../../../examples/component-runtime/aggregate.cpp#L201) | Callable definition: int main(int argc, char** argv) | calls run, what; returns run(argc,argv); 1 · [reviewed contract](#b0011) |

## B0001

[Lines 1–18](../../../../../examples/component-runtime/aggregate.cpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L1-L18:sha256:a7a163afa77f24bf3fd048e41a030f777b034a62ca6b93bd696e6f432283c935
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Bind the optional aggregate observer to public SQL/source/runtime and JSON APIs. |
| inputs / outputs | Includes the shared transport helper, genuine catalog/physical/tree IO, exact tree chooser and SqlAggregateRuntime; establishes local aliases. |
| invariants | The application links existing runtime components; it registers no handwritten query class, operator hook or alternate compiler authority. |
| ownership | Imports/aliases own no mutable query state. Subsequent functions own their explicit observations. |
| failure | Missing headers/ABI/link closure fail build before any workload runs. |
| cost | Compilation/link and later cold class/library startup; no maintenance bound is claimed by these includes. |
| Design | [docs/sql_aggregate_binding.md](../../../../sql_aggregate_binding.md), [docs/sql_aggregate_runtime.md](../../../../sql_aggregate_runtime.md), [docs/measurement.md](../../../../measurement.md) |

## B0002

[Lines 19–23](../../../../../examples/component-runtime/aggregate.cpp#L19); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L19-L23:sha256:f161fc20508f7dcd689ec32912d6d263b79713aac1bf519d0126e77ec2687dd4
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Export an owning native nullable result tuple into ordinary JSON observation cells. |
| inputs / outputs | Walks Tuple.view; non-NULL ScalarViews pass through the public scalar writer and absent cells become JSON null. |
| invariants | Field order, exact scalar representation and NULL presence are preserved; no set conversion or row deduplication occurs. |
| ownership | The tuple is borrowed during the call. Returned JSON owns ordinary payload copies outside its query account. |
| failure | Invalid tuple/access/scalar/JSON allocations propagate to the CLI; this exporter cannot undo a committed event. |
| cost | Work/copying follows tuple width and scalar/string extents and may allocate per JSON cell. It runs only for captured verification observations. |
| Design | [docs/sql_aggregate_runtime.md](../../../../sql_aggregate_runtime.md), [docs/scalars.md](../../../../scalars.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0003

[Lines 24–27](../../../../../examples/component-runtime/aggregate.cpp#L24); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L24-L27:sha256:5de4cb71bec484c85ef3fb9e00663092691d8315761ac69bd464ddfd17d409ee
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Record selected receiving-account diagnostics before owner teardown. |
| inputs / outputs | Converts limit, current requested bytes, cumulative peak requested bytes and current allocations to JSON. |
| invariants | These are native account statistics, not process RSS, standalone compiler memory or a subtractable phase peak. |
| ownership | Borrows a MemoryStatistics value and returns an independent caller-owned JSON object. |
| failure | JSON allocation failure stops reporting without reverting prior source events. |
| cost | Constant selected field export; the caller samples after the processing loop, outside API phase clocks. |
| Design | [docs/query_memory.md](../../../../query_memory.md), [docs/measurement.md](../../../../measurement.md) |

## B0004

[Lines 28–31](../../../../../examples/component-runtime/aggregate.cpp#L28); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L28-L31:sha256:a7b003986a888ee2ca7f716a2b01da3d8c38077b4ab38e87f66812b1843112df
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | State the deliberately narrow equivalence used by the source-only COUNT ablation. |
| inputs / outputs | The note identifies original-program.source_program as the sole bag producer. |
| invariants | The optimization is complete group-key COUNT(*) presentation, not a rewrite for DISTINCT/SUM/AVG or an arbitrary aggregate theorem. |
| ownership | No row/key owner or alternate source is created in this comment region. |
| failure | Actual guard/rejection is implemented by source_count_contract immediately below. |
| cost | No executable work; the conditional execution/cursor costs belong to run. |
| Design | [docs/weighted_enumeration.md](../../../../weighted_enumeration.md), [docs/sql_aggregate_binding.md](../../../../sql_aggregate_binding.md), [docs/sql_aggregate_runtime.md](../../../../sql_aggregate_runtime.md) |

## B0005

[Lines 32–44](../../../../../examples/component-runtime/aggregate.cpp#L32); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L32-L44:sha256:2584013dc204fc0c51a9c0701ab8cdc0d8400fd1505b0c89cf4b4b885b4cf44a
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Reject source-only presentation unless compressed bag multiplicity exactly determines every requested aggregate result. |
| inputs / outputs | Inspects genuine kernel grouping/input/measure/output metadata; requires a complete nonempty input group key, no measures, at least one COUNT(*) and only group/count-all outputs. |
| invariants | No hidden non-grouped logical input or nullable COUNT(argument), SUM, AVG or aggregate DISTINCT can be silently represented as multiplicity. This is a cold capability guard, not program construction. This guard speaks about canonical kernel inputs; it does not identify public SQL tuple positions. source_group must still use the original compiler source_output mapping. |
| ownership | Borrows factory-owned immutable metadata; retains no per-row/group state. |
| failure | Any unmet condition raises a local application rejection before runtime construction. |
| cost | Linear in output metadata plus existing accessor checks, once per invocation; no per-update guard structure is installed. |
| Design | [docs/weighted_enumeration.md](../../../../weighted_enumeration.md), [include/crown/frontend/aggregate.hpp](../../../../../include/crown/frontend/aggregate.hpp), [docs/sql_aggregate_runtime.md](../../../../sql_aggregate_runtime.md) |

## B0006

[Lines 45–47](../../../../../examples/component-runtime/aggregate.cpp#L45); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L45-L47:sha256:7bbfb10a98223df490fe9ac3d74a598e472c33295ec2f6a97ba289085f7f6539
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Explain the distinct coordinate systems at the COUNT-source output boundary. |
| inputs / outputs | Documents decoded public source output positions, canonical aggregate input columns and native payload/presence positions before source_group. |
| invariants | Repeated SQL references may widen the public tuple; only SqlAggregateInput.source_output connects canonical kernel inputs to decoded source outputs. Native decode fields belong to native core facts. |
| ownership | This comment adds no owner, mapping cache, retained row or runtime instrumentation. |
| failure | The explanation creates no new check or exception; existing compiler ownership and source cursor contracts supply valid mapping metadata. |
| cost | No executable work. Actual verification conversion is charged to explicit output observation, outside measured native apply. |
| Design | [include/crown/frontend/sql_aggregate.hpp](../../../../../include/crown/frontend/sql_aggregate.hpp), [src/frontend/sql_aggregate.cpp](../../../../../src/frontend/sql_aggregate.cpp), [docs/sql_aggregate_binding.md](../../../../sql_aggregate_binding.md) |

## B0007

[Lines 48–63](../../../../../examples/component-runtime/aggregate.cpp#L48); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L48-L63:sha256:dc410e62e398d9987625bfafd796a0d9ae5eef06e7608b1a80e9ba496f50b8e5
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Render one guarded COUNT-source result with the exact canonical aggregate group key and original SELECT output order. |
| inputs / outputs | Receives a genuine SqlRowsRuntime Result and its SqlAggregateProgram. For each kernel group column it selects row.tuple\[program.inputs()\[column\].source_output\], builds that nullable canonical key once, then renders group outputs from key\[field.index\] and COUNT(*) from row.multiplicity. |
| invariants | The caller passed source_count_contract and checked multiplicity against the signed count cap. Public SQL source outputs may repeat GROUP BY or SELECT references: neither kernel input column numbers nor native payload/presence slots index that public tuple. The authenticated source_output mapping preserves reordered/duplicate original references and constant/NULL decoding. Full canonical-input grouping and complete native-head coverage make source-row multiplicity equal this one complete group COUNT. |
| ownership | Borrows one owning source result and immutable compiler metadata through the call. Key and values are ordinary caller JSON copies, returned together without retaining source cells or a group/row ledger. |
| failure | Scalar encoding, JSON allocation or C++ contract misuse propagate to the single CLI catch after native input commitment. No group state is mutated and observation failure cannot roll back an accepted input. |
| cost | Verification-only work follows canonical key width, SELECT width and copied scalar extents. A key is encoded once, then selected output fields copy its JSON cells. No helper call or mapping lookup is added to the measure branch; genuine compressed cursor/output ownership costs remain separate. |
| Design | [docs/sql_aggregate_binding.md](../../../../sql_aggregate_binding.md), [docs/sql_aggregate_runtime.md](../../../../sql_aggregate_runtime.md), [docs/weighted_enumeration.md](../../../../weighted_enumeration.md), [include/crown/frontend/sql_aggregate.hpp](../../../../../include/crown/frontend/sql_aggregate.hpp), [src/frontend/sql_aggregate.cpp](../../../../../src/frontend/sql_aggregate.cpp), [src/runtime/sql_aggregate.cpp](../../../../../src/runtime/sql_aggregate.cpp), [src/runtime/sql_rows.cpp](../../../../../src/runtime/sql_rows.cpp) |

## B0009

[Lines 65–199](../../../../../examples/component-runtime/aggregate.cpp#L65); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L65-L199:sha256:ce8447bc9bdf7f5527de8838991919cbee878cfcd26e4cb2140db28750b90b1e
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Execute fresh-owner original-SQL aggregate passes, optionally replacing only the guarded COUNT coordinator with its genuine compressed source. |
| inputs / outputs | Reads the full canonical catalog/SQL, selects PhysicalOptions{} only for omitted or exactly empty-object options, otherwise calls the existing strict reader, binds an authentic program, chooses a proved source tree unless contradiction, resolves transport tables, then applies one unit physical NetBatch/update per event. Emits full groups, final before/after group changes or guarded source counts with phase/account observations. Verification source-only observations call source_group to produce the kernel-order key and original SELECT values from the authenticated decode/source-output mapping. |
| invariants | Query family is a label; actual factories/tree checks confer admission. All self-join aliases share one native epoch. Replacement capture is enabled in both verify/measure only when requested. Every requested full output is consumed once per input; source-only has no replacement port. No correctness flag, row mirror, WAL or new operator hook is created. The default adapter is restricted to is_object() && empty(); null, empty arrays/strings and incomplete/nonempty DTOs cannot bypass strict options admission. Repeated grouping columns or output references do not widen the emitted canonical aggregate key or shift the selected cell; all COUNT-source JSON conversion is verify-only. |
| ownership | Cold program remains a separate compiler owner. Each pass creates one finite receiving account and fresh SqlAggregateRuntime or SqlRowsRuntime. Input cell borrows end at synchronous prepare/apply; snapshots/epochs are explicitly released before the next event. Verification JSON and accumulated report records are caller-owned; the account sample precedes teardown. |
| failure | Catalog/binding/proof/domain/cap/allocation/engine/output failures propagate to the sole CLI catch. Native preparation uses existing transactional rollback; after commit, observation/report failure terminates without pretending to revert source state. Outer source/proof/cold allocations have their existing separate limits. Supplied nonobject or nonempty options preserve the strict reader's ordinary rejection behavior; the adapter does not catch or reinterpret those failures. |
| cost | Shared SQL/proof/options/target preparation is charged once. Apply includes actual source/native/D-fact/group work; full snapshot render or compressed cursor is output work, with source cursor/local row release included there. Snapshot/epoch reset is separate release. Loop wall additionally contains clocks/record construction. Measure does not build per-row JSON observations. Report encoding is outside service; account bytes exclude compiler/input/report DTOs and are not RSS. No runtime/CPU/delay/speedup theorem follows. Default detection adds one cold JSON type/emptiness branch per invocation and no update-path storage or allocation. The mapping correction adds only verification output formatting; measure-mode cursor draining, record/count-limit checks and phase clocks are unchanged. |
| Design | [docs/sql_aggregate_binding.md](../../../../sql_aggregate_binding.md), [docs/sql_aggregate_runtime.md](../../../../sql_aggregate_runtime.md), [docs/sql_rows_batches.md](../../../../sql_rows_batches.md), [docs/weighted_enumeration.md](../../../../weighted_enumeration.md), [docs/query_memory.md](../../../../query_memory.md), [docs/measurement.md](../../../../measurement.md), [Refactor.md §11.11 B04 and §14.3–14.4](../../../../../Refactor.md), [include/crown/io/physical.hpp](../../../../../include/crown/io/physical.hpp), [src/io/physical.cpp](../../../../../src/io/physical.cpp) |

## B0010

[Lines 200–200](../../../../../examples/component-runtime/aggregate.cpp#L200); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L200-L200:sha256:c7bfe2f3de133d78a2bc8bb1c4a08450563986ee8254facee698e1dcc57e8162
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | End the implementation-local helper namespace before the executable entrypoint. |
| inputs / outputs | Closes the anonymous namespace containing result export, guards and run. |
| invariants | Scope closure does not expose internal native state or confer proof authority. |
| ownership | No query/runtime object is independently created by this brace. |
| failure | Malformed scope would be a compile error; no catch or cleanup is installed here. |
| cost | No runtime work. |
| Design | [examples/component-runtime/aggregate.cpp](../../../../../examples/component-runtime/aggregate.cpp) |

## B0011

[Lines 201–204](../../../../../examples/component-runtime/aggregate.cpp#L201); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L201-L204:sha256:7aae8c742e4167d8eeef2e0d4abb84b0ab94a876cff8629f740bf8545de8fe8c
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Translate the optional aggregate application's process boundary to a success/failure exit code. |
| inputs / outputs | Calls run once; catches std::exception to stderr and returns one, otherwise forwards run's flushed-stdout result. |
| invariants | This is the only added C++ CLI catch; it neither retries nor installs production recovery. A zero exit reports completed observations, not independent correctness acceptance. |
| ownership | Stack unwinding retires application owners; returned JSON/output files are under the runner's external ownership. |
| failure | Standard exceptions become nonzero process status. Native fatal signals/nonstandard failures retain ordinary process behavior; no successful report is fabricated. |
| cost | Normal call/return; diagnostic formatting only on failure. Final report encoding/flush occurs in run outside service timing. |
| Design | [docs/measurement.md](../../../../measurement.md), [docs/legacy_baselines.md](../../../../legacy_baselines.md) |
