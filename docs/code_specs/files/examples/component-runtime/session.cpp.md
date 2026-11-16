# `examples/component-runtime/session.cpp` — block usage map

[Source](../../../../../examples/component-runtime/session.cpp) · [Source index](../../../README.md) · [Subsystem contracts](../../../subsystem_contracts.md) · [Reviewed primitives](../../../primitives.md)

Own input-to-output and durable lifecycle transitions for one creator-thread query session.

Snapshot SHA-256: `5200a39a227901ab310b11f4863cce48d6be88bff6af5e8397fd2e3784e2b9bc`. 263 lines partitioned into 8 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [examples](../../../subsystem_contracts.md#examples). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/cli.md](../../../../cli.md), [docs/native_build.md](../../../../native_build.md), [docs/measurement.md](../../../../measurement.md), [docs/ranking_evaluation.md](../../../../ranking_evaluation.md), [docs/reoptimization.md](../../../../reoptimization.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–11](../../../../../examples/component-runtime/session.cpp#L1) | Imports dependencies; declares namespace scope; declares aliases. |  · [reviewed contract](#b0001) |
| [B0002 · 12–19](../../../../../examples/component-runtime/session.cpp#L12) | Type/record definition: struct Controls |  · [reviewed contract](#b0002) |
| [B0003 · 20–56](../../../../../examples/component-runtime/session.cpp#L20) | Callable definition: Controls controls(const Request& request, const runtime::DeltaOptions& options) | calls at, number, value, Json; guard require(result.batch_size &gt; 0, "transport batch size must be positive");; returns result; growth insert; 1 loop sites · [reviewed contract](#b0003) |
| [B0004 · 57–59](../../../../../examples/component-runtime/session.cpp#L57) | Callable definition: std::array&lt;char,32&gt; identity(std::string_view hash) | calls std::copy_n, begin, size; returns result · [reviewed contract](#b0004) |
| [B0005 · 60–62](../../../../../examples/component-runtime/session.cpp#L60) | Callable definition: Json progress(const io::InputProgress& value) | calls ; returns {{@ ,value.sequence},{@ ,value.source_positions}} · [reviewed contract](#b0005) |
| [B0006 · 63–258](../../../../../examples/component-runtime/session.cpp#L63) | Callable definition: int run(int argc, char** argv) | calls Clock::now, read_request, elapsed, compile_set; guard require(number(native.value("transaction_batch_size",Json(1))) == 1 &&; returns report({{@ ,1},{@ ,@ },; growth emplace, emplace_back, push_back, reserve; 10 loop sites; source comment (unverified): // Rotation retains history. This finite trace-derived grant avoids silently · [reviewed contract](#b0006) |
| [B0007 · 259–259](../../../../../examples/component-runtime/session.cpp#L259) | Closes surrounding scope/type. | source comment (unverified): // namespace · [reviewed contract](#b0007) |
| [B0008 · 260–263](../../../../../examples/component-runtime/session.cpp#L260) | Callable definition: int main(int argc, char** argv) | calls run, what; returns run(argc,argv); 1 · [reviewed contract](#b0008) |

## B0001

[Lines 1–11](../../../../../examples/component-runtime/session.cpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L1-L11:sha256:7aed031c88bc9afdfcfa54021e700396edb1dadbcf9b3bbc6fe5f4c51468f34c
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Bind the Session adapter to public typed input, generation and local sink operations. |
| inputs / outputs | Imports native helpers, Session generation/sink APIs and filesystem/optional utilities; declares local names. Includes standard thread sleep for the explicit experimental consumer wait. |
| invariants | All durability/control behavior is driven through existing actual public owners, not file-format DTO authority. |
| ownership | Includes create no files, sessions or locks; run owns those lifetimes explicitly. |
| failure | Header/link/platform incompatibility fails before workload execution. |
| cost | Compilation/type declarations only; filesystem and native operations occur at their labeled calls. |
| Design | [include/crown/runtime/session_generation.hpp](../../../../../include/crown/runtime/session_generation.hpp), [include/crown/runtime/session_local_sink.hpp](../../../../../include/crown/runtime/session_local_sink.hpp), [docs/session_lifecycle.md](../../../../session_lifecycle.md) |

## B0002

[Lines 12–19](../../../../../examples/component-runtime/session.cpp#L12); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L12-L19:sha256:4f1181cd95751fe465269a2e2df81e764ad2f28370fae612fb187f2563d03fa6
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Own the application-level session experiment controls admitted before any runtime starts. |
| inputs / outputs | Stores transport size, output action/observation, durability, checkpoint cadence, ordered recovery offsets and the caller supplied work directory. Stores bounded consumer_delay_us, default zero. |
| invariants | These describe actual public operations; transport batches preserve per-event barriers and never imply atomic net semantics. |
| ownership | Strings/set/path are ordinary cold caller metadata. No native account, lock, pending head or result row is stored in Controls. |
| failure | DTO construction may allocate; controls validates combinations before owner creation. |
| cost | Cold metadata proportional to recovery-point count and path/text size, not maintained row state. |
| Design | [docs/session_lifecycle.md](../../../../session_lifecycle.md), [docs/generations.md](../../../../generations.md), [Refactor.md §14.4](../../../../../Refactor.md) |

## B0003

[Lines 20–56](../../../../../examples/component-runtime/session.cpp#L20); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L20-L56:sha256:01da836f5acb31c066ee8b6d52301b2dc0fa1fdcebc64885354c39e005f94855
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Reject session controls that do not correspond to a supported genuine public operation schedule. |
| inputs / outputs | Reads the session object and output label, validates policies, positive transport size, aligned checkpoint/recovery points, increasing offsets and required durable directory. Admits delay0..100000us and rejects a delayed maintenance-only arm. |
| invariants | Maintenance-only means maintenance mode with no service output. Serialization requires real deltas; durable local output also requires WAL. Checkpoint/recovery cannot run volatile. Points align to empty-queue transport boundaries, with an explicit final partial boundary. |
| ownership | Returns owned cold Controls and borrows the request/options only through admission. |
| failure | Unsupported names/combinations, malformed values, duplicate/out-of-order points or allocation failures stop before runtime/file creation; no silent fallback. |
| cost | Cold selected field checks and recovery-point set insertion. No state machine hook or per-update guard framework is installed. |
| Design | [docs/session_lifecycle.md](../../../../session_lifecycle.md), [docs/local-sink.md](../../../../local-sink.md), [docs/checkpoints.md](../../../../checkpoints.md), [docs/generations.md](../../../../generations.md) |

## B0004

[Lines 57–59](../../../../../examples/component-runtime/session.cpp#L57); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L57-L59:sha256:08342b264acf41e4d835fabe0b01d362b7d00cbcc215988b07e98abb4ab2d741
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Derive fixed application query/sink labels from the actual admitted hash text. |
| inputs / outputs | Copies32 characters of a genuine64-character program SHA into the required fixed lowercase-hex ID. |
| invariants | This truncation is an external label only. Recovery still checks complete actual source/program/schema bindings; the ID alone cannot admit a plan or prove delivery. |
| ownership | Returns a fixed array with no dynamic memory or borrowing after the call. |
| failure | Requires the genuine program hash contract; no arbitrary caller short string enters this private helper. |
| cost | Constant cold copy once per invocation, not an update hash operation. |
| Design | [docs/generations.md](../../../../generations.md), [docs/local-sink.md](../../../../local-sink.md), [include/crown/ir/program.hpp](../../../../../include/crown/ir/program.hpp) |

## B0005

[Lines 60–62](../../../../../examples/component-runtime/session.cpp#L60); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L60-L62:sha256:cbc226240f46ff182404c6f298f249ec45b0af00209a2634480f03a5e79928ef
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Export actual accepted input progress without inventing wire positions. |
| inputs / outputs | Serializes the QuerySession progress sequence and its source-position map; component_event_offset is the declared physical event ordinal. |
| invariants | The offset is not a file byte count, transaction sequence, sink frontier or proof of an external CDC acknowledgment. |
| ownership | Borrows exported progress during JSON construction; the returned object owns ordinary map/text copies. |
| failure | Copy/JSON allocation failure propagates after committed work and does not advance or revert any source position. |
| cost | Explicit post-loop metadata export proportional to source-map size; excluded from native update grants. |
| Design | [docs/ingestion.md](../../../../ingestion.md), [docs/session_lifecycle.md](../../../../session_lifecycle.md) |

## B0006

[Lines 63–258](../../../../../examples/component-runtime/session.cpp#L63); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L63-L258:sha256:42c300cfdb126e33f5d6ca5ba02c684c9c2a724017ba692baf9a34ca40b4ce8c
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Exercise actual typed Session transport, output, WAL, checkpoint and reconstruction controls. |
| inputs / outputs | Compiles original set SQL, creates fresh typed owners, imports TransportBatch, begins/steps/commits every physical event, performs actual output action and committed observations, then optionally rotates or reconstructs at empty-queue boundaries. Reports real accepted progress, journal/generation/sink state and clocks. Optionally waits with the committed epoch retained; exports actual before/after recovery memory samples and a maximum of sampled owner-account peaks. |
| invariants | Transport preserves every event and source offset. WAL includes an initial checkpoint. Durable output is accepted only through actual local sink delivery/receipt, including empty epochs; ordinary transfer never bypasses it. Periodic checkpoints also run at a final partial boundary. Clean-owner recovery uses real selected-root/native replay; non-sink replay rows are consumed separately, not counted as new input. No crash/power-loss claim is added. Delay is synthetic service wait, not native work, network pressure or queue saturation. Output time includes the nested wait. Samples and maximum refer only to query-owner requested-byte accounts, not ancillary recovery allocations or process RSS. |
| ownership | QuerySession owns one account, queue, native epoch, spool and real file locks. Fresh per-pass directories use exclusive creation and remain for inspection. Snapshot/epoch borrows are released before administrative barriers. Compiler/control/input/report DTOs are ordinary cold storage; no duplicate native row ledger exists. Report JSON owns memory sample copies after old runtime owners are destroyed; no row mirror, shared-query state or engine callback is introduced. |
| failure | Actual queue full, lifecycle, resource, binding, file and output failures propagate through one CLI catch. Existing native/durable APIs own rollback and uncertainty; committed files/state are retained after presentation failure, with no deletion or retry framework. |
| cost | Shared compilation precedes passes. Initialization includes initial WAL/checkpoint/sink creation. Transport construction/import, genuine per-event API work, real transfer/JSON serialization/durable file encoding+fsync, snapshot, release, checkpoint, replay and teardown have actual phase clocks. Verification-only none-output snapshots are never executed in measure. Cardinality observations materialize the public SessionSnapshot and are labeled accordingly; loop wall also includes reporting. No total CPU, exactly-once external sink, steady-state or performance acceptance follows. Zero delay performs no wait-clock reads. Every batch copies two constant-size account statistics and updates a scalar maximum; report DTO work is in loop/process cost, outside apply/recovery clocks. A nonzero delay performs an actual sleep and two clock reads; its reported nanoseconds must not be added to output time again. |
| Design | [docs/session_lifecycle.md](../../../../session_lifecycle.md), [docs/batches_windows.md](../../../../batches_windows.md), [docs/session-journal.md](../../../../session-journal.md), [docs/generations.md](../../../../generations.md), [docs/local-sink.md](../../../../local-sink.md), [docs/checkpoints.md](../../../../checkpoints.md), [docs/measurement.md](../../../../measurement.md), [Refactor.md §8.1–8.4 and §14.4](../../../../../Refactor.md) |

## B0007

[Lines 259–259](../../../../../examples/component-runtime/session.cpp#L259); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L259-L259:sha256:533f16bca7d58f44b3103b92e3485d22cfbb34bbad5ea3f3fa3b5a9dcb24ec89
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Close the implementation helper scope before its public executable entrypoint. |
| inputs / outputs | Ends the enclosing C++ namespace; helper names retain their declared linkage. |
| invariants | The brace changes lexical scope only and grants no execution, proof or durable authority. |
| ownership | No separate runtime resource is created or released by this lexical closure. |
| failure | A malformed scope is a compilation error; no runtime handler is installed. |
| cost | No executable work. |
| Design | [examples/component-runtime/session.cpp](../../../../../examples/component-runtime/session.cpp) |

## B0008

[Lines 260–263](../../../../../examples/component-runtime/session.cpp#L260); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L260-L263:sha256:7aae8c742e4167d8eeef2e0d4abb84b0ab94a876cff8629f740bf8545de8fe8c
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Translate this session adapter process to a single checked CLI exit status. |
| inputs / outputs | Calls run once, forwards its flushed-report status, and catches std::exception to stderr/nonzero. |
| invariants | The only added exception boundary is the CLI. Zero exit is completed observation transport, not independent correctness or B04 acceptance. |
| ownership | Ordinary unwinding destroys local owners and releases locks/buffers; already committed durable files remain inspectable. |
| failure | Standard exceptions become failure status. No retry, source reapplication, rollback of committed work or fabricated success report is introduced. |
| cost | Normal call/return plus failure diagnostics; final report encoding/flush is outside native service clocks. |
| Design | [docs/measurement.md](../../../../measurement.md), [docs/legacy_baselines.md](../../../../legacy_baselines.md) |
