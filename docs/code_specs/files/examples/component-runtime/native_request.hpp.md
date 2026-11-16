# `examples/component-runtime/native_request.hpp` — block usage map

[Source](../../../../../examples/component-runtime/native_request.hpp) · [Source index](../../../README.md) · [Subsystem contracts](../../../subsystem_contracts.md) · [Reviewed primitives](../../../primitives.md)

Demonstrate a concrete public workflow and executable invocation using installed/native CROWN interfaces.

Snapshot SHA-256: `71b2ddb2338020061e09c1ac988fbd1604f3d9e7b529abd8eab86e58411ec4a7`. 116 lines partitioned into 14 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [examples](../../../subsystem_contracts.md#examples). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/cli.md](../../../../cli.md), [docs/native_build.md](../../../../native_build.md), [docs/measurement.md](../../../../measurement.md), [docs/ranking_evaluation.md](../../../../ranking_evaluation.md), [docs/reoptimization.md](../../../../reoptimization.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–15](../../../../../examples/component-runtime/native_request.hpp#L1) | Imports dependencies; guards repeated header inclusion; declares namespace scope; declares aliases. | source comment (unverified): // Cold native admission and observation helpers. Baseline adapters continue to · [reviewed contract](#b0001) |
| [B0002 · 16–20](../../../../../examples/component-runtime/native_request.hpp#L16) | Type/record definition: struct SetProgram |  · [reviewed contract](#b0002) |
| [B0003 · 21–24](../../../../../examples/component-runtime/native_request.hpp#L21) | Callable definition: inline PhysicalOptions physical_options(const Json& native) | calls value, Json::object, is_object, empty; returns encoded.is_object() && encoded.empty() ? PhysicalOptions{} : io::read_physical_options(encoded.dump… · [reviewed contract](#b0003) |
| [B0004 · 25–49](../../../../../examples/component-runtime/native_request.hpp#L25) | Callable definition: inline SetProgram compile_set(const Json& document) | calls at, io::read_catalog, dump, frontend::admit_sql; guard require(admitted.status == frontend::AdmissionStatus::admitted && admitted.program.has_value(),; returns {std::move(catalog), options, std::move(compiled)}; source comment (unverified): // Imported flags are insufficient. Replay the whole artifact and compare its · [reviewed contract](#b0004) |
| [B0005 · 50–74](../../../../../examples/component-runtime/native_request.hpp#L50) | Callable definition: inline runtime::DeltaOptions delta_options(const Json& native) | calls number, at, value, Json; guard require(mode == "delta" \|\| mode == "maintenance", "unknown native set mode");; returns options · [reviewed contract](#b0005) |
| [B0006 · 75–85](../../../../../examples/component-runtime/native_request.hpp#L75) | Callable definition: inline std::vector&lt;TableId&gt; target_tables(const Request& request, const Catalog& catalog) | calls size, emplace, reserve, find; guard require(found != names.end(), "component event names an unknown table");; returns result; growth emplace, push_back, reserve; 2 loop sites · [reviewed contract](#b0006) |
| [B0007 · 86–88](../../../../../examples/component-runtime/native_request.hpp#L86) | Callable definition: inline SetOperation operation(const Event& event) | calls ; returns event.operation == @ ? SetOperation::insert : SetOperation::erase; growth insert · [reviewed contract](#b0007) |
| [B0008 · 89–93](../../../../../examples/component-runtime/native_request.hpp#L89) | Callable definition: inline Json tuple_values(storage::TupleValuesView values) | calls Json::array, push_back, io::write_scalar_view; returns result; growth push_back; 1 loop sites · [reviewed contract](#b0008) |
| [B0009 · 94–96](../../../../../examples/component-runtime/native_request.hpp#L94) | Callable definition: inline Json signed_values(SetOperation sign, storage::TupleValuesView values) | calls tuple_values; returns {{@ , sign == SetOperation::insert ? @ : @ }, {@ , tuple_values(values)}}; growth insert · [reviewed contract](#b0009) |
| [B0010 · 97–101](../../../../../examples/component-runtime/native_request.hpp#L97) | Callable definition: template&lt;class Cells&gt; Json nullable_values(const Cells& values) | calls Json::array, push_back, io::write_scalar_view; returns result; growth push_back; 1 loop sites · [reviewed contract](#b0010) |
| [B0011 · 102–105](../../../../../examples/component-runtime/native_request.hpp#L102) | Callable definition: inline Json memory(const resource::MemoryStatistics& value) | calls ; returns {{@ , value.limit_bytes}, {@ , value.current.requested_bytes}, · [reviewed contract](#b0011) |
| [B0012 · 106–111](../../../../../examples/component-runtime/native_request.hpp#L106) | Callable definition: inline void admit_capture(const Json& actual, U64& captured, const Request& request) | calls dump, size, require; guard require(bytes &lt;= request.max_bytes-captured, "component capture-byte limit exceeded"); · [reviewed contract](#b0012) |
| [B0013 · 112–115](../../../../../examples/component-runtime/native_request.hpp#L112) | Callable definition: inline int report(Json value) | calls dump, flush; returns std::cout ? 0 : 1 · [reviewed contract](#b0013) |
| [B0014 · 116–116](../../../../../examples/component-runtime/native_request.hpp#L116) | Closes surrounding scope/type. | source comment (unverified): // namespace component · [reviewed contract](#b0014) |

## B0001

[Lines 1–15](../../../../../examples/component-runtime/native_request.hpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L1-L15:sha256:d62e41674b94adf65333bc5d592217b398934046c71fe5f14b824b38d6948e25
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Introduce compiler, unweighted runtime and observation dependencies for the three new native adapters. |
| inputs / outputs | Includes the unchanged cold transport helper and public admission/catalog/physical/lowering/tree/delta APIs; opens component with crown names. |
| invariants | Baseline adapters continue to include only component_request.hpp. This header adds no virtual runtime, registered query class, core hook or baseline dependency. |
| ownership | Includes/aliases retain no native rows. Later SetProgram and runtime owners retain their own explicit compiler/query accounts. |
| failure | Missing public headers or link closure fails compilation; no handler or retry is installed here. |
| cost | Compile-time work only. Cold parsing/lowering and observation operations are charged at their actual helper calls. |
| Design | [examples/component-runtime/component_request.hpp](../../../../../examples/component-runtime/component_request.hpp), [docs/native_build.md](../../../../native_build.md), [Refactor.md §3](../../../../../Refactor.md) |

## B0002

[Lines 16–20](../../../../../examples/component-runtime/native_request.hpp#L16); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L16-L20:sha256:9f48320fb81f82c41021e687056559b5f04a103f96f33d99c29032f9ae84b66d
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Keep the genuine set compiler result and the original catalog/backend options together for application admission. |
| inputs / outputs | Holds ordinary Catalog and PhysicalOptions plus an immutable CompiledProgram produced by compile_set. |
| invariants | The catalog is the actual request catalog used for name resolution; the executable is genuine factory output, not mutable plan flags or a digest. |
| ownership | Ordinary catalog/options own their cold DTO payload; CompiledProgram shares its compiler account. Each execution later freezes into its separate finite query owner. |
| failure | Construction/copy may allocate in existing compiler/DTO conventions. Partial construction unwinds through ordinary field owners. |
| cost | Retained compiler metadata follows query/catalog size; copying and final release are not promised constant-cost. |
| Design | [include/crown/ir/program.hpp](../../../../../include/crown/ir/program.hpp), [docs/query_memory.md](../../../../query_memory.md), [docs/physical_plans.md](../../../../physical_plans.md) |

## B0003

[Lines 21–24](../../../../../examples/component-runtime/native_request.hpp#L21); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L21-L24:sha256:1449e4fab8e4524efd5d8b3657b261393e9de3417650ad25b7f6fdc16675b38a
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Admit the requested physical backend using the existing strict options reader. |
| inputs / outputs | Omitted or exactly empty-object native.physical_options selects PhysicalOptions{}; every other JSON value is serialized through read_physical_options. |
| invariants | Null, empty arrays/strings and incomplete nonempty objects do not bypass strict admission. Backend selection remains actual compiler input. |
| ownership | Borrows native JSON and returns an ordinary owned options DTO before a query account exists. |
| failure | JSON conversion/strict reader/allocation failures propagate to the sole CLI catch; no default fallback follows a failed read. |
| cost | One cold JSON type/emptiness decision plus optional DTO serialization/parse. No update-path work or state. |
| Design | [include/crown/io/physical.hpp](../../../../../include/crown/io/physical.hpp), [src/io/physical.cpp](../../../../../src/io/physical.cpp), [docs/indexed_storage.md](../../../../indexed_storage.md) |

## B0004

[Lines 25–49](../../../../../examples/component-runtime/native_request.hpp#L25); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L25-L49:sha256:1d7f2d8723245a447c10606ee65fe559d239a6d6e340bb19c2d7df1cdc26f706
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Compile the actual original SQL into an unweighted executable, preserving a genuinely supplied tree choice. |
| inputs / outputs | Reads full catalog/SQL, calls admit_sql, optionally reconstructs compiled_set and compares complete original normalization, otherwise proves a minimum tree; lower_normalized applies the requested backend, then standalone owns compiler metadata. |
| invariants | Family labels, hashes and valid flags never authorize source/tree substitution. A supplied tree remains a checked upper unless its separate proof says more. Re-lowering under requested options makes storage comparisons use the actual requested backend. |
| ownership | Cold catalog, admission DTOs and tree are locally owned. Returned immutable program retains its compiler account; runtime creation imports into its own original execution account. |
| failure | Admission/resource/proof/source mismatch or genuine lowering rejection stops before runtime construction. Existing errors propagate without fallback or catch layers. |
| cost | Shared once-per-invocation SQL/replay/proof/lowering/copy/hash work. Factory grants bound named selected work, not all parser CPU or peak cold allocator memory. |
| Design | [docs/planner_proofs.md](../../../../planner_proofs.md), [docs/physical_plans.md](../../../../physical_plans.md), [include/crown/planner/lower.hpp](../../../../../include/crown/planner/lower.hpp), [src/io/physical.cpp](../../../../../src/io/physical.cpp), [Refactor.md §5](../../../../../Refactor.md) |

## B0005

[Lines 50–74](../../../../../examples/component-runtime/native_request.hpp#L50); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L50-L74:sha256:5130e0c896e797d614f580b4931b4bff9e97e0d516d319d8d7a40bf1824f0d53
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Build the exact unweighted runtime policy requested by the new set/session adapters. |
| inputs / outputs | Reads finite memory/work/spool settings and explicit maintenance/delta, live-maintenance and completion names; fixes the result view to original SQL output. |
| invariants | Unknown policy names reject. No backend or delay theorem is inferred from options; the actual runtime still checks supported combinations and bounds. |
| ownership | Returns a fixed options value with no row payload or query owner. The runtime owns its account and retained grants after construction. |
| failure | Malformed values or unknown policies fail cold; runtime resource/domain failures remain the existing public API diagnostics. |
| cost | Constant cold field parsing and small policy branches. Per-row work is performed only by the real runtime and explicit consumers. |
| Design | [include/crown/runtime/delta.hpp](../../../../../include/crown/runtime/delta.hpp), [docs/ordered_delta.md](../../../../ordered_delta.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0006

[Lines 75–85](../../../../../examples/component-runtime/native_request.hpp#L75); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L75-L85:sha256:616a102cec1c0fb6d6fe135436ef0851de28d279c7478190843928ead4269053
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Resolve every transport relation name to its original physical table before execution clocks. |
| inputs / outputs | Builds a catalog name index and returns one TableId per already admitted event. |
| invariants | Events name physical base tables, not SQL aliases or tree occurrences. Unknown names cannot silently route to a different source. |
| ownership | Temporary ordered map is released after resolution; returned target vector is ordinary immutable application input beside the request. |
| failure | Unknown table or allocation failure stops before owner creation; no partial source event is applied. |
| cost | Cold O(tables + events) visits with ordered-map comparison costs and vector storage. This is shared request setup, not intrinsic baseline parse cost. |
| Design | [docs/ingestion.md](../../../../ingestion.md), [docs/catalog.md](../../../../catalog.md), [Refactor.md §14.3](../../../../../Refactor.md) |

## B0007

[Lines 86–88](../../../../../examples/component-runtime/native_request.hpp#L86); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L86-L88:sha256:dd3132388fc061d6f6dc477f0c14329a25ed67c4547c3171937b9a8cef12c26a
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Translate one cold-validated unit-set event sign to the native set enum. |
| inputs / outputs | Maps + to insert and the read_request-admitted - to erase. |
| invariants | Requires a successfully read_request-validated Event; this helper is not an independent parser for arbitrary event DTOs. |
| ownership | Borrows the event string only through the call and returns a scalar enum. |
| failure | Installs no handler or independent error path; invalid external signs already reject at transport admission. |
| cost | One sign comparison per physical input, included in actual application/update preparation. |
| Design | [examples/component-runtime/component_request.hpp](../../../../../examples/component-runtime/component_request.hpp), [docs/ingestion.md](../../../../ingestion.md) |

## B0008

[Lines 89–93](../../../../../examples/component-runtime/native_request.hpp#L89); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L89-L93:sha256:4c77947b8e8f1974f66eb4cfc342814be27a85c7aee97692cc40e9f861a07397
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Export an actual nonnull native tuple view as ordered JSON observation cells. |
| inputs / outputs | Visits TupleValuesView and encodes each exact scalar through write_scalar_view. |
| invariants | Preserves field order and values; does not canonicalize, deduplicate or reinterpret a count as a row. |
| ownership | The view borrows its actual owning tuple/source for the call; JSON copies are ordinary caller/report storage. |
| failure | Scalar/JSON allocation or later text encoding failure propagates after any committed input; output conversion does not roll back state. |
| cost | Explicit output work follows tuple width and scalar extents; no native account or constant-delay claim covers ordinary JSON copies. |
| Design | [docs/scalars.md](../../../../scalars.md), [include/crown/storage/tuple_values.hpp](../../../../../include/crown/storage/tuple_values.hpp), [docs/measurement.md](../../../../measurement.md) |

## B0009

[Lines 94–96](../../../../../examples/component-runtime/native_request.hpp#L94); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L94-L96:sha256:eab68c936d514100b100ebe81e3a83a08a9b00b3d52c5133c43e1ef111d17107
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Encode one genuine signed set output with its exact row. |
| inputs / outputs | Receives a real producer SetOperation and tuple view; returns operation +/- plus ordered values. |
| invariants | The sign belongs to a completed set delta/local epoch, not a bag multiplicity. This encoding creates no commit or durable-delivery authority. |
| ownership | Borrows the row while copying caller-owned JSON; retains no tuple, cursor or Session owner. |
| failure | JSON/scalar failures propagate to the application boundary; a committed epoch remains committed. |
| cost | One small object plus exact tuple encoding; used only for explicit serialization or captured verification. |
| Design | [docs/ordered_delta.md](../../../../ordered_delta.md), [docs/local-sink.md](../../../../local-sink.md), [docs/measurement.md](../../../../measurement.md) |

## B0010

[Lines 97–101](../../../../../examples/component-runtime/native_request.hpp#L97); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L97-L101:sha256:bc2f91ecf9a1b3639592251c4fc85a65f309de1fcec1d1a02f4acf1b0d617655
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Export already decoded nullable SQL-row cells without applying native decode coordinates again. |
| inputs / outputs | Receives a nullable cell range from the actual SQL result tuple; emits JSON null or exact scalar in the same order. |
| invariants | NULL presence is represented independently of payload. Native payload/presence slots and canonical aggregate input indices do not index this public tuple. |
| ownership | Borrows the owning SQL row through the call; returned JSON owns ordinary value copies. |
| failure | Scalar/JSON failures stop observation without changing native source ownership or retrying input. |
| cost | Verification conversion follows output width and copied scalar extents; measurement compressed-row discard avoids these JSON cells. |
| Design | [include/crown/frontend/sql_rows.hpp](../../../../../include/crown/frontend/sql_rows.hpp), [docs/sql_rows_runtime.md](../../../../sql_rows_runtime.md), [docs/sql_aggregate_binding.md](../../../../sql_aggregate_binding.md) |

## B0011

[Lines 102–105](../../../../../examples/component-runtime/native_request.hpp#L102); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L102-L105:sha256:decc694b5d0b56618b8e3f61140103f900de9beb55737bcf4aa5de9d40bca835
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Capture selected real account statistics for a pass before teardown. |
| inputs / outputs | Exports limit, current/peak requested bytes and current allocation count from MemoryStatistics. |
| invariants | These are native requested-byte account facts; they are not RSS, allocator usable bytes or a subtractable phase peak. |
| ownership | Borrows a numeric statistics value and returns ordinary caller-owned JSON. |
| failure | JSON allocation failure stops reporting but does not undo earlier native or durable commits. |
| cost | Constant field export after the loop; obtaining the actual owner statistics remains a separate public read. |
| Design | [docs/query_memory.md](../../../../query_memory.md), [docs/measurement.md](../../../../measurement.md) |

## B0012

[Lines 106–111](../../../../../examples/component-runtime/native_request.hpp#L106); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L106-L111:sha256:19d4d4baf1785d3a286537404e0ceff9fc875ed2f3452cec44ccbea6025bd0c3
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Bound retained verification observations by their actual encoded JSON length. |
| inputs / outputs | In verify mode dumps the completed actual observation, checks remaining output_bytes and advances the cumulative byte count; measure returns immediately. |
| invariants | A partial encoding is never accepted as a captured result. Encoded bytes do not bound JSON capacities, report metadata or total process memory. |
| ownership | Reads ordinary JSON; temporary encoded text dies on return. No query tuples are retained by this quota helper. |
| failure | Encoding/allocation/cap failure propagates after any committed input; no input replay or presentation rollback is fabricated. |
| cost | Verification-only serialization/copying outside native apply clocks; full loop wall includes actual report work. It is not accepted benchmark timing. |
| Design | [docs/measurement.md](../../../../measurement.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0013

[Lines 112–115](../../../../../examples/component-runtime/native_request.hpp#L112); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L112-L115:sha256:172010e5550a0b612704ad0de727dc6d65e3fa53d1b8323ec540eb60233ebbaf
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Publish one complete adapter report and detect buffered output failure. |
| inputs / outputs | Dumps caller-owned JSON, writes newline, explicitly flushes stdout and returns zero only for a healthy stream. |
| invariants | A successful exit means the report was written, not that an independent oracle or performance gate accepted it. |
| ownership | Takes the completed report value; local destruction releases report copies after the output attempt. |
| failure | Encoding exceptions reach the single main catch. Stream failure returns nonzero; accepted runtime/durable work is not rolled back. |
| cost | Final report encoding/flush is outside measured native service phases and may allocate or block. |
| Design | [docs/measurement.md](../../../../measurement.md), [docs/legacy_baselines.md](../../../../legacy_baselines.md) |

## B0014

[Lines 116–116](../../../../../examples/component-runtime/native_request.hpp#L116); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L116-L116:sha256:738b9fdfc7545b5c800448a10d54a94035d473bc7d31ec9d15b586cfdd93f75e
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Close the shared native helper namespace after its cold and observation definitions. |
| inputs / outputs | Ends the enclosing C++ namespace; helper names retain their declared linkage. |
| invariants | The brace changes lexical scope only and grants no execution, proof or durable authority. |
| ownership | No separate runtime resource is created or released by this lexical closure. |
| failure | A malformed scope is a compilation error; no runtime handler is installed. |
| cost | No executable work. |
| Design | [examples/component-runtime/native_request.hpp](../../../../../examples/component-runtime/native_request.hpp) |
