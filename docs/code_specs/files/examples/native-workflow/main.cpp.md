# `examples/native-workflow/main.cpp` — block usage map

[Source](../../../../../examples/native-workflow/main.cpp) · [Source index](../../../README.md) · [Subsystem contracts](../../../subsystem_contracts.md) · [Reviewed primitives](../../../primitives.md)

Demonstrate a concrete public workflow and executable invocation using installed/native CROWN interfaces.

Snapshot SHA-256: `983df4c9ec68cf2f4898321379fca902e87bb33adf89fdab38c48b8a18e88e68`. 84 lines partitioned into 6 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [examples](../../../subsystem_contracts.md#examples). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/cli.md](../../../../cli.md), [docs/native_build.md](../../../../native_build.md), [docs/measurement.md](../../../../measurement.md), [docs/ranking_evaluation.md](../../../../ranking_evaluation.md), [docs/reoptimization.md](../../../../reoptimization.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–17](../../../../../examples/native-workflow/main.cpp#L1) | Imports dependencies; declares namespace scope; declares aliases. |  · [reviewed contract](#b0001) |
| [B0002 · 18–24](../../../../../examples/native-workflow/main.cpp#L18) | Callable definition: std::string read(const char* path,std::size_t limit) | calls file, Error, gcount, size; returns result; 1 loop sites · [reviewed contract](#b0002) |
| [B0003 · 25–29](../../../../../examples/native-workflow/main.cpp#L25) | Callable definition: std::unique_ptr&lt;std::istream&gt; input(const char* path) | calls Error; returns result; growth make_unique · [reviewed contract](#b0003) |
| [B0004 · 30–32](../../../../../examples/native-workflow/main.cpp#L30) | Callable definition: void deliver(runtime::QuerySession& session) | calls local_sink_state, status, deliver_local_epoch; 1 loop sites · [reviewed contract](#b0004) |
| [B0005 · 33–33](../../../../../examples/native-workflow/main.cpp#L33) | Closes surrounding scope/type. |  · [reviewed contract](#b0005) |
| [B0006 · 34–84](../../../../../examples/native-workflow/main.cpp#L34) | Callable definition: int main(int argc,char** argv) | calls std::string_view, Error, count, std::from_chars; returns planner::lower_normalized(*admitted.program,FreeConnexTree{}); planner::lower_normalized(*admitted.…; growth push_back; 4 loop sites; source comment (unverified): // Nonconstant queries need the actual proved witness; unfinished inputs stop here. · [reviewed contract](#b0006) |

## B0001

[Lines 1–17](../../../../../examples/native-workflow/main.cpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
#include <crown/version.hpp>
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Import the public APIs and local host utilities used by this standalone client. |
| inputs / outputs | Public headers, standard/POSIX declarations and namespace/type aliases; no execution request. |
| invariants | Aliases do not create runtime owners or proof authority. Measurement/ranking collectors use Linux/POSIX facilities where declared. |
| ownership | Declarations only; actual owners and buffers are created inside helpers/run/main. |
| failure | Compilation requires the installed public target closure and a supporting compiler/platform. |
| cost | No per-event runtime action; included definitions and instantiated APIs determine compiled dependencies. |
| Design | [examples/native-workflow/main.cpp](../../../../../examples/native-workflow/main.cpp), [cmake/CrownInstall.cmake](../../../../../cmake/CrownInstall.cmake), [docs/native_build.md](../../../../native_build.md), [docs/cli.md](../../../../cli.md), [docs/session_lifecycle.md](../../../../session_lifecycle.md), [docs/generations.md](../../../../generations.md), [docs/local-sink.md](../../../../local-sink.md) |

## B0002

[Lines 18–24](../../../../../examples/native-workflow/main.cpp#L18); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::string read(const char* path,std::size_t limit)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Read one bounded SQL/catalog document as binary bytes. |
| inputs / outputs | Borrowed NUL-terminated path and maximum accepted bytes; returns an owning std::string. |
| invariants | The accumulated result never exceeds limit; subtracting result.size() is safe after each accepted append. Limit is acceptance, not total process-memory accounting. |
| ownership | Local ifstream closes on return/unwind; returned string owns copied bytes and ordinary copies may allocate. |
| failure | Open/read errors become io_error; a block exceeding remaining allowance becomes resource_limit; string allocation can throw. |
| cost | Linear file read/copy with a 4096-byte stack block and a growing ordinary string. |
| Design | [examples/native-workflow/main.cpp](../../../../../examples/native-workflow/main.cpp), [include/crown/api/error.hpp](../../../../../include/crown/api/error.hpp), [docs/cli.md](../../../../cli.md), [docs/session_lifecycle.md](../../../../session_lifecycle.md), [docs/generations.md](../../../../generations.md), [docs/local-sink.md](../../../../local-sink.md) |

## B0003

[Lines 25–29](../../../../../examples/native-workflow/main.cpp#L25); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::unique_ptr<std::istream> input(const char* path)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Open the continued JSONL source for session ownership. |
| inputs / outputs | Borrowed path; returns a unique owning stream suitable for create/restore. |
| invariants | Binary opening does not validate JSONL/catalog/sequence; EventReader performs that work later. |
| ownership | make_unique creates an ifstream; ownership moves into QuerySession and is not a borrowed temporary. |
| failure | Open failure throws io_error; allocation/open can fail before session construction. |
| cost | One ordinary stream allocation/open; records are decoded lazily. |
| Design | [examples/native-workflow/main.cpp](../../../../../examples/native-workflow/main.cpp), [include/crown/io/ingest.hpp](../../../../../include/crown/io/ingest.hpp), [src/io/event_reader.cpp](../../../../../src/io/event_reader.cpp), [docs/cli.md](../../../../cli.md), [docs/session_lifecycle.md](../../../../session_lifecycle.md), [docs/generations.md](../../../../generations.md), [docs/local-sink.md](../../../../local-sink.md) |

## B0004

[Lines 30–32](../../../../../examples/native-workflow/main.cpp#L30); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void deliver(runtime::QuerySession& session)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Deliver every committed epoch not yet verified by the attached local sink. |
| inputs / outputs | Exclusive mutable session with healthy local sink; returns when verified_sequence reaches committed_sequence. |
| invariants | Includes recovered and empty epochs; whole-epoch sink acceptance precedes advancing its verified frontier. |
| ownership | Borrows session only. Session owns committed/recovered spool, funded delivery scratch and durable sink. |
| failure | Delivery errors propagate; this loop neither retries an uncertain append nor rolls back a committed input. |
| cost | Repeated whole-epoch validation/encoding and file publication; work, memory and retained sink-log limits apply. |
| Design | [examples/native-workflow/main.cpp](../../../../../examples/native-workflow/main.cpp), [include/crown/runtime/session.hpp](../../../../../include/crown/runtime/session.hpp), [src/runtime/session.cpp](../../../../../src/runtime/session.cpp), [include/crown/runtime/session_local_sink.hpp](../../../../../include/crown/runtime/session_local_sink.hpp), [src/recovery/local_sink.cpp](../../../../../src/recovery/local_sink.cpp), [docs/cli.md](../../../../cli.md), [docs/session_lifecycle.md](../../../../session_lifecycle.md), [docs/generations.md](../../../../generations.md), [docs/local-sink.md](../../../../local-sink.md) |

## B0005

[Lines 33–33](../../../../../examples/native-workflow/main.cpp#L33); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

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
| Design | [examples/native-workflow/main.cpp](../../../../../examples/native-workflow/main.cpp), [docs/cli.md](../../../../cli.md), [docs/session_lifecycle.md](../../../../session_lifecycle.md), [docs/generations.md](../../../../generations.md), [docs/local-sink.md](../../../../local-sink.md) |

## B0006

[Lines 34–84](../../../../../examples/native-workflow/main.cpp#L34); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
int main(int argc,char** argv)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Compile supplied SQL and execute or restore a finite durable session prefix. |
| inputs / outputs | run\|restore SQL CATALOG JSONL ROOT SINK EVENTS; emits one bounded final-state/report JSON and returns process status. |
| invariants | Fresh run requires unused durable paths; restore uses the same admitted source, sink identity and complete origin input. Native library recovery determines durable outcomes. |
| ownership | Owns compiler DTOs, standalone CompiledProgram, unique QuerySession/stream, snapshot collection and ordinary report JSON. |
| failure | One std::exception boundary prints what() and returns 1; prior durable commits are not undone. Report-size/stream checks occur after execution. Final report emission explicitly flushes stdout and returns failure on stream error; completed work is not rolled back. |
| cost | Bounded document reads, exact height proof/lowering, funded session import, per-event prepare/commit/delivery, optional checkpoint rotation, snapshot and report export. One final stdout flush is presentation work outside native event maintenance. |
| Design | [examples/native-workflow/main.cpp](../../../../../examples/native-workflow/main.cpp), [include/crown/runtime/session.hpp](../../../../../include/crown/runtime/session.hpp), [src/runtime/session.cpp](../../../../../src/runtime/session.cpp), [include/crown/planner/lower.hpp](../../../../../include/crown/planner/lower.hpp), [include/crown/ir/physical.hpp](../../../../../include/crown/ir/physical.hpp), [include/crown/ir/program.hpp](../../../../../include/crown/ir/program.hpp), [include/crown/runtime/session_generation.hpp](../../../../../include/crown/runtime/session_generation.hpp), [docs/cli.md](../../../../cli.md), [docs/session_lifecycle.md](../../../../session_lifecycle.md), [docs/generations.md](../../../../generations.md), [docs/local-sink.md](../../../../local-sink.md) |

```text
if(argc!=8
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Validate action/arity and parse the requested unsigned physical-event prefix. |
| inputs / outputs | argv strings; fills events through full-consumption from_chars. |
| invariants | Zero events is allowed; plus/minus/trailing characters and overflow are rejected. Numeric magnitude is not a wall-time bound. |
| ownership | string_view borrows argv for main lifetime; events is an inline scalar. |
| failure | Usage errors throw before opening source or durable files. |
| cost | Linear numeric parse; no event storage. |
| Design | [examples/native-workflow/main.cpp](../../../../../examples/native-workflow/main.cpp), [docs/cli.md](../../../../cli.md), [docs/session_lifecycle.md](../../../../session_lifecycle.md), [docs/generations.md](../../../../generations.md), [docs/local-sink.md](../../../../local-sink.md) |

```text
const auto catalog=io::read_catalog
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Admit SQL against the supplied physical catalog. |
| inputs / outputs | Catalog document &lt;= 16 MiB and SQL bounded by ParseLimits::source_bytes; obtains actual AdmissionResult. |
| invariants | Requires admitted status before dereferencing normalized program; unsupported/rejected SQL is not replaced with a demo query. |
| ownership | Catalog/normalized program are owning compiler-side DTOs, distinct from later receiving-account executable metadata. |
| failure | Read/parse/catalog/SQL admission failure stops before durable creation. |
| cost | Document parsing, normalization and validation can scan/allocate ordinary compiler objects. |
| Design | [examples/native-workflow/main.cpp](../../../../../examples/native-workflow/main.cpp), [include/crown/frontend/admission.hpp](../../../../../include/crown/frontend/admission.hpp), [include/crown/io/catalog.hpp](../../../../../include/crown/io/catalog.hpp), [docs/cli.md](../../../../cli.md), [docs/session_lifecycle.md](../../../../session_lifecycle.md), [docs/generations.md](../../../../generations.md), [docs/local-sink.md](../../../../local-sink.md) |

```text
auto plan=[&]
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Obtain and lower the actual admitted query plan. |
| inputs / outputs | Normalized admitted SQL; constant-empty route lowers an empty tree, otherwise public minimum_tree supplies the returned proven witness. |
| invariants | The nonconstant path requires proven_minimum and a present tree; lowering independently validates the complete physical plan. An edited OracleResult alone is not equivalent authority. |
| ownership | Temporary oracle/tree/compiler objects own their allocations; returned PhysicalPlan retains actual metadata. |
| failure | Unfinished proof is resource_limit; proof/lowering/validation and allocation may fail before session creation. |
| cost | Blocking exact proof plus checked lowering/metadata construction; no constant search-time claim. |
| Design | [examples/native-workflow/main.cpp](../../../../../examples/native-workflow/main.cpp), [include/crown/planner/lower.hpp](../../../../../include/crown/planner/lower.hpp), [include/crown/ir/physical.hpp](../../../../../include/crown/ir/physical.hpp), [include/crown/planner/oracle.hpp](../../../../../include/crown/planner/oracle.hpp), [docs/tree_oracle.md](../../../../tree_oracle.md), [docs/cli.md](../../../../cli.md), [docs/session_lifecycle.md](../../../../session_lifecycle.md), [docs/generations.md](../../../../generations.md), [docs/local-sink.md](../../../../local-sink.md) |

```text
auto program=CompiledProgram::standalone
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Freeze executable metadata and derive the example journal/sink IDs. |
| inputs / outputs | Checked PhysicalPlan; standalone program, first 32 textual source-digest characters as query ID and first 32 physical-digest characters as sink ID. |
| invariants | These are deterministic example identity conventions, not hex decoding, security credentials or independent plan/proof checks. |
| ownership | CompiledProgram retains compiler metadata funded by standalone's separate UINT64_MAX account; copies use its actual shared Data. The later session imports into its finite native grant. The two ID arrays/options own inline bytes. |
| failure | Standalone freezing can fail allocation/validation; copying fixed 32-byte prefixes follows valid digest lengths. |
| cost | Explicit metadata allocation/copy followed by fixed-width digest-character copies. |
| Design | [examples/native-workflow/main.cpp](../../../../../examples/native-workflow/main.cpp), [include/crown/ir/program.hpp](../../../../../include/crown/ir/program.hpp), [src/ir/program.cpp](../../../../../src/ir/program.cpp), [docs/cli.md](../../../../cli.md), [docs/session_lifecycle.md](../../../../session_lifecycle.md), [docs/generations.md](../../../../generations.md), [docs/local-sink.md](../../../../local-sink.md) |

```text
if(std::string_view(argv[1])=="run")
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Create a new managed generation or restore the selected existing generation. |
| inputs / outputs | Program, input path, root/sink paths and deterministic IDs; produces a session owning source/durable state. |
| invariants | Restore sets seek_source_from_origin and supplies the whole source; selected durable binding and sink prefix are checked by the native API before continuation. |
| ownership | Owner receives unique stream; native runtime imports into its query account. Recovery locks and durable handles stay owned by session. |
| failure | Creation/recovery/file/admission failure propagates. Uncertain durable selection retains library recovery-required semantics; no root rewrite is attempted. |
| cost | Native executable import, empty-state setup or checkpoint/WAL/sink replay, origin-source positioning and actual durable IO. |
| Design | [examples/native-workflow/main.cpp](../../../../../examples/native-workflow/main.cpp), [include/crown/runtime/session.hpp](../../../../../include/crown/runtime/session.hpp), [src/runtime/session.cpp](../../../../../src/runtime/session.cpp), [include/crown/runtime/session_generation.hpp](../../../../../include/crown/runtime/session_generation.hpp), [include/crown/runtime/session_local_sink.hpp](../../../../../include/crown/runtime/session_local_sink.hpp), [docs/cli.md](../../../../cli.md), [docs/session_lifecycle.md](../../../../session_lifecycle.md), [docs/generations.md](../../../../generations.md), [docs/local-sink.md](../../../../local-sink.md) |

```text
deliver(*session);session->start();
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Satisfy recovered delivery obligations before admitting new input. |
| inputs / outputs | New/restored paused/created session; verifies outstanding local output, then starts. |
| invariants | A new physical input cannot bypass recovered whole-epoch delivery. |
| ownership | No owner export; deliver borrows the retained session. |
| failure | Sink/start failure stops the process without advancing an unverified delivery frontier. |
| cost | Delivery cost is proportional to real recovered epochs/rows; start is the control-state transition. |
| Design | [examples/native-workflow/main.cpp](../../../../../examples/native-workflow/main.cpp), [include/crown/runtime/session.hpp](../../../../../include/crown/runtime/session.hpp), [src/runtime/session.cpp](../../../../../src/runtime/session.cpp), [docs/cli.md](../../../../cli.md), [docs/session_lifecycle.md](../../../../session_lifecycle.md), [docs/generations.md](../../../../generations.md), [docs/local-sink.md](../../../../local-sink.md) |

```text
for(std::uint64_t i=0;i<events;++i)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Commit and deliver at most EVENTS physical inputs. |
| inputs / outputs | Started session; begin_next stops at validated EOF, step loops to prepared, commit publishes, deliver accepts whole epochs. |
| invariants | Prepared is a private native barrier, not output durability; only commit then sink delivery advances those separate frontiers. |
| ownership | Session owns decoded rows, pending epochs and spool. No borrowed row escapes the iteration. |
| failure | Decode/prepare/commit/delivery failures propagate; earlier committed inputs survive. No skip or manual acknowledge is added. |
| cost | Decode plus native delta preparation/spooling, commit and durable output for each event; step grant counts are not CPU-time limits. |
| Design | [examples/native-workflow/main.cpp](../../../../../examples/native-workflow/main.cpp), [include/crown/runtime/session.hpp](../../../../../include/crown/runtime/session.hpp), [src/runtime/session.cpp](../../../../../src/runtime/session.cpp), [docs/cli.md](../../../../cli.md), [docs/session_lifecycle.md](../../../../session_lifecycle.md), [docs/generations.md](../../../../generations.md), [docs/local-sink.md](../../../../local-sink.md) |

```text
session->pause();if(!session->status().end_of_input)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Pause at a delivered boundary and rotate a resumable generation when input is unfinished. |
| inputs / outputs | Session with no pending input/output; conditionally creates a new checkpoint/WAL/root selection. |
| invariants | Validated end-of-input prevents rotation here; paused state and current accepted progress remain bound. |
| ownership | Session owns old/new checkpoint buffers and durable generation handles during preparation. |
| failure | Rotation/IO/resource failure propagates with native unchanged/selected/uncertain outcome rules; report failure cannot undo a selected generation. |
| cost | Full checkpoint/image encoding and synced durable files/root publication; old/new resources can coexist. |
| Design | [examples/native-workflow/main.cpp](../../../../../examples/native-workflow/main.cpp), [include/crown/runtime/session.hpp](../../../../../include/crown/runtime/session.hpp), [src/runtime/session.cpp](../../../../../src/runtime/session.cpp), [docs/cli.md](../../../../cli.md), [docs/session_lifecycle.md](../../../../session_lifecycle.md), [docs/generations.md](../../../../generations.md), [docs/local-sink.md](../../../../local-sink.md) |

```text
const auto state=session->snapshot();
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Materialize the committed final snapshot and export report JSON. |
| inputs / outputs | Paused committed session; converts scalar views to ordinary rows, captures PlanExplanation and emits &lt;=16 MiB encoded JSON. |
| invariants | Snapshot sequence, exported source positions and sink receipt describe separate validated boundaries; report fields confer no restore/delivery authority. |
| ownership | SessionRows is an owning shared collection; snapshot progress is an ordinary owning map/string DTO. Tuple values borrow retained payloads during export. JSON/report strings own copies. |
| failure | Snapshot bounds, capture/export/JSON encoding, size and flushed stream-state failures occur after durable work and do not roll it back. |
| cost | Funded result traversal/tuple ownership plus ordinary progress/JSON scalar copying, explanation capture/encoding/parse and final dump; the size check follows allocation. Explicit flush completes the process report before its stream-state exit check. |
| Design | [examples/native-workflow/main.cpp](../../../../../examples/native-workflow/main.cpp), [include/crown/runtime/session.hpp](../../../../../include/crown/runtime/session.hpp), [src/runtime/session.cpp](../../../../../src/runtime/session.cpp), [include/crown/storage/layout.hpp](../../../../../include/crown/storage/layout.hpp), [src/storage/layout.cpp](../../../../../src/storage/layout.cpp), [include/crown/observability/explain.hpp](../../../../../include/crown/observability/explain.hpp), [docs/cli.md](../../../../cli.md), [docs/session_lifecycle.md](../../../../session_lifecycle.md), [docs/generations.md](../../../../generations.md), [docs/local-sink.md](../../../../local-sink.md) |
