# CROWN Next CLI and local CMake package

Start with the complete [SQL quickstart](quickstart.md),
[interfaces and guarantees](guarantees.md), [query contribution guide](development.md)
and [troubleshooting](troubleshooting.md). These guides describe the current
local workflow; the verification counts below retain their dated scope.

> **Status:** The original O08 checkpoint verified the selected 19-test CLI/package matrix in GCC Debug/Release, Clang18, ASan+UBSan/leaks and a clean source-only Release build, including 259 CLI checks over 34 independent events and the moved-package public consumer. Later source changes have their own dated verification scope. Full release acceptance remains separate.

## File workflow

The commands in this section are the original set workflow. The separate
[`crown aggregate` family](sql_aggregate_input.md) creates and resumes genuine R2
SQL aggregate Sessions from nullable atomic weight-replacement JSONL commands.
It has its own binding, progress and output formats; `crown aggregate --help`
lists its options.

The CLI works with local files: SQL, a standalone catalog JSON document, an ordered stream of typed physical updates, a compiled JSON artifact, a local journal/checkpoint root, and a durable local result sink. It has no database connection step.

```sh
crown compile query.sql catalog.json \
  [--admission-options admission.json] [--physical-options physical.json] \
  [--search-work N] [--max-bytes N]

crown explain compiled plan.json [--format text|json|dot|tree-json] [--proof-work N]
crown validate-plan compiled plan.json [--proof-work N]

crown run plan.json updates.jsonl ROOT SINK [EVENTS] \
  [--events N] [--input-format jsonl|binary] [--mode delta|maintenance] \
  [--spool-rows N] [--spool-bytes N] [--memory-limit-bytes N] \
  [--observe off|counters|timed|trace] [--max-bytes N]

crown snapshot plan.json updates.jsonl ROOT SINK [--memory-limit-bytes N]
crown checkpoint plan.json updates.jsonl ROOT SINK [--retire] [--memory-limit-bytes N]
crown restore plan.json updates.jsonl ROOT SINK [EVENTS] [--events N] \
  [--memory-limit-bytes N] [--proof-work N] [--max-bytes N]
crown results plan.json updates.jsonl ROOT SINK --epoch N

crown verify-trace plan.json updates.jsonl \
  [--input-format jsonl|binary] [--verify-work N] [--reference-bytes N] \
  [--verify-events N] [--memory-limit-bytes N] [--proof-work N]

crown benchmark plan.json updates.jsonl ROOT SINK [EVENTS] \
  [--events N] [--input-format jsonl|binary] [--mode delta|maintenance] \
  [--spool-rows N] [--spool-bytes N] [--memory-limit-bytes N] \
  [--observe off|counters|timed|trace] [--run-label TEXT] [--max-bytes N]
```

`EVENTS` and `--events N` are alternatives; if omitted, run, restore, and benchmark read through end of input. New `run` and `benchmark` paths must not already exist. `restore` uses the input settings saved in the checkpoint; give it the complete original input file from its beginning. Recovery validates and replays the stored checkpoint/WAL accepted prefix, then seeks the external input to the saved decoder position. The caller must preserve already consumed source bytes: recovery does not reread or authenticate that external prefix, and an edit of the same size is not detected by seek. Restore validates the checkpoint, journal, and attached sink before continuing. `snapshot` reports the recovered state without consuming new events. `checkpoint` handles any recorded pending input, rotates to a new generation, and with `--retire` removes only eligible older history after sink verification.


The default query and sink IDs are deterministic program-derived IDs scoped to
the chosen files. Use `--query-id HEX32 --sink-id HEX32` to distinguish independent
executions or destinations of the same program. IDs must contain 32 lowercase
hexadecimal characters. Supply the same IDs to every subsequent root/sink
command. Result views include the actual admitted IDs; these views cannot
authorize acknowledgment or retirement.

### Update records and catalog binding

A JSONL file contains one physical set update per line. Each record is bound to the catalog by the SHA-256 of CROWN's canonical catalog JSON bytes, not by hashing the catalog file's whitespace or original byte spelling. Records carry schema and catalog versions, table/source schema version, sequence, operation, values, and may carry a source position:

```json
{"schema_version":1,"catalog_sha256":"<64 hex characters>","catalog_version":1,"source_schema_version":1,"sequence":1,"table":"R","operation":"insert","values":[17,"é\u0000x"],"source_position":{"source":"feed-1","offset":8}}
```

Sequences follow the stream order. When present, a source position has a nonempty UTF-8 source name and an offset that increases strictly for that source. Rows must match the standalone catalog's physical column order and scalar types. The five native scalar forms are signed 64-bit integers, UTF-8 strings (including NUL), booleans, dates such as `{"date":"2026-11-10"}`, and decimals such as `{"decimal":"12.340"}`. JSON output preserves typed values with strict UTF-8 encoding. `--input-format binary` reads the versioned `CROWNUPD` physical-update record format; it is separate from the local output sink's `CROWNSK1` codec.

The compiler writes a JSON artifact containing the physical plan and a height certificate. A normal tree plan must carry an independently replayable proof that its structural height is minimum. Artifact loading replays that proof within `--proof-work` (default 10,000,000 units) and checks the tree and height. This proves original structural height only; it does not prove a cost optimum or runtime performance. A constant-empty query uses a checked constant-false operator and a null certificate. `validate-plan` reports these separately as `proven_minimum` and `checked_constant_operator`; the latter is not a minimum-height proof. `explain compiled` can render text, JSON, DOT, or tree JSON and reports the plan evidence without claiming cost or runtime optimality.

### Limits and verification

The limits control different work:

- `--search-work` bounds compile-time tree search (default 10,000,000). `--proof-work` independently bounds proof replay while loading compiled artifacts (default 10,000,000).
- `--max-bytes` bounds a complete JSON report or artifact (default 16 MiB, maximum 64 MiB). It is an export limit, not a query-memory limit.
- `--memory-limit-bytes` sets the native support/query account limit (default 256 MiB) for new runs and verify-trace. Recovery uses the saved checkpoint limit unless an explicit receiving limit overrides it. It charges the native executable metadata, storage, session, source state, output and related query allocations under the shared account. Compiler/tool DTOs, caller stream buffering, report encoding and reference verification are separate boundaries; this is not a total process/RSS limit.
- Output epoch spooling is separately limited by `--spool-rows` (default 65,536) and `--spool-bytes` (default 64 MiB). An epoch exceeding either limit fails before publication.
- `verify-trace` checks the initial result and, after each physical event, independently recomputes the relational result and compares the exact signed set delta, current rows, sequence, and source positions. Its input file is limited to 8 MiB; the reference evaluator has separate defaults of 10,000,000 work units, a 64 MiB estimated-state budget, and 4,096 events. These reference budgets are not the native query-account limit.

`verify-trace` is a bounded correctness check for a compiled SQL workflow. It does not measure query performance or verify durable restart behavior.

### Durable results and benchmark reports

`run` and `benchmark` create a generation journal/checkpoint root and a durable local sink. Each committed input event produces a sink epoch containing raw signed rows (`insert` or `delete`); `results --epoch N` reads one committed epoch and includes its query, sink, and physical-plan bindings. `snapshot` reports current rows, committed sequence, source positions, verified output sequence, generation, delivery work, sink bytes, and requested account bytes.

Stdout is a report view, not an acknowledgment. The local sink is the durable output. A stdout write failure can happen after sink publication; the diagnostic says durable results remain in the sink. File-operation failures use structured diagnostics with fault, stage, and outcome (`unchanged`, `unknown`, or `durable`) where available. If outcome is `unknown`, validate the on-disk state through restore before retrying; an exit status or missing report cannot establish whether publication occurred.

The final process boundary invokes the command once and explicitly flushes
stdout. If a command would return success but that flush fails, the process
returns 2 with a fixed `io_error` JSON diagnostic. An existing nonzero command
status is preserved. Component handlers still report their typed failures;
if their diagnostic formatting itself throws, final `main` returns 3 with
fixed JSON: `resource_limit` for C++ allocation failure or `internal_error`
for another standard exception. These fallbacks build no JSON DOM or owning
message string. An unwritable stderr can still lose the diagnostic.

This boundary adds one flush per invocation and no native update/index/cursor
work. It does not retry the command or undo completed native or file effects.
The [process regression](../tests/integration/cli_process_boundary.py) checks
small buffered writes to `/dev/full`, normal version/help output and invalid
POSIX argument bytes that cause strict diagnostic JSON encoding to throw.

`benchmark` is one native, single-process durable-file run, not a repeated comparison. It reports processed records, delivered rows, final state, runtime/backend and plan identity, height evidence, observations, cursor and committed gauges, plus a sink receipt (verified sequence, generation, byte count, and prefix SHA-256). `initialization_ns` includes artifact proof, native admission, and checkpoint/log/sink creation. `processing_ns` includes input, native epochs, WAL work, and sink synchronization; report construction is excluded. It also reports input-begin, native prepare/commit, and delivery sub-times. `--observe` defaults to `timed`; `--run-label` declares the label in run context and does not validate a benchmark protocol.

## Local CMake installation and consumer

The current package installs the CLI, public CROWN headers and libraries, CMake package files, the pinned parser archive, the vendored nlohmann JSON header, schemas, and upstream notices. A typical local install and consumer configure is:

```sh
cmake -S . -B /tmp/crown-build -DCMAKE_INSTALL_PREFIX=/tmp/crown-stage -DBUILD_TESTING=OFF
cmake --build /tmp/crown-build --target crown crown_selection_runtime --parallel
cmake --install /tmp/crown-build
cmake -S consumer -B /tmp/crown-consumer-build -DCMAKE_PREFIX_PATH=/tmp/crown-stage
cmake --build /tmp/crown-consumer-build
```

Consumer `CMakeLists.txt`:

```cmake
cmake_minimum_required(VERSION 3.25)
project(crown_consumer LANGUAGES CXX)
find_package(Crown 0.1 CONFIG REQUIRED)
add_executable(consumer main.cpp)
target_link_libraries(consumer PRIVATE CROWN::runtime CROWN::explain)
```

`CROWN::runtime` supplies QuerySession and transitively links the plan, SQL, core, JSON, parser, and Threads dependencies. Add `CROWN::explain` for plan/report explanations and their serializers. A minimal header/version check is:

```cpp
#include <crown/runtime/session.hpp>
#include <crown/observability/explain.hpp>
#include <crown/io/explain.hpp>
#include <crown/version.hpp>

int main() {
  static_assert(crown::public_api_version == 1);
  crown::runtime::SessionOptions options;
  (void)options;
  return crown::version == "0.1.0" ? 0 : 1;
}
```

The current build baseline is Linux with GCC 13 for C and C++, CMake 3.25 or newer, GNU Make, and C++23. Python 3.10 with `sqlite3` and `jsonschema` is required for repository verification tasks, not for running the installed CLI or linking a consumer. Third-party notices are installed and must remain with redistributed components. A02's project license choice remains unresolved. This is local development packaging; no release or publication is claimed.

## Runnable file-only example

From the source tree, with a built or installed `crown` on PATH:

```sh
mkdir -p build/cli-example
cp tests/workflow/full_head_self_join_loop_new_new/query.sql build/cli-example/query.sql
cp tests/workflow/full_head_self_join_loop_new_new/catalog.json build/cli-example/catalog.json
python3 tools/prepare_workflow_input.py "$(command -v crown)" build/cli-example/catalog.json tests/workflow/full_head_self_join_loop_new_new/events.template.jsonl build/cli-example/updates.jsonl
crown compile build/cli-example/query.sql build/cli-example/catalog.json > build/cli-example/compiled.json
crown validate-plan compiled build/cli-example/compiled.json
crown explain compiled build/cli-example/compiled.json --format text
crown run build/cli-example/compiled.json build/cli-example/updates.jsonl build/cli-example/state.root build/cli-example/results.sink --events 2
```

```sh
crown results build/cli-example/compiled.json build/cli-example/updates.jsonl build/cli-example/state.root build/cli-example/results.sink --epoch 2
crown checkpoint build/cli-example/compiled.json build/cli-example/updates.jsonl build/cli-example/state.root build/cli-example/results.sink
crown restore build/cli-example/compiled.json build/cli-example/updates.jsonl build/cli-example/state.root build/cli-example/results.sink --events 1
```

These commands read SQL/catalog/input data; they add no query class.
Choose fresh root/sink names for a new execution. `restore` reuses existing files.
The preparation helper only fills/validates catalog binding metadata; the native
input codec still validates full records, types, sequence and source positions.

The installed public API example lives at
`share/crown/examples/native-workflow`. Copy that directory, configure it with
`-DCMAKE_PREFIX_PATH=PREFIX`, and build `crown_native_workflow`. It takes:

```text
crown_native_workflow run|restore QUERY.sql CATALOG.json INPUT.jsonl ROOT SINK EVENTS
```

It compiles the supplied SQL with public APIs, processes the requested prefix,
delivers whole local epochs, rotates a quiescent checkpoint when possible, and
can restore in another process. It uses the same code for every supported query.
The sample reports a bounded final snapshot; full CLI commands expose the richer
command and limit controls above.

Transport shapes are in [compiled-workflow-v1.schema.json](../schemas/compiled-workflow-v1.schema.json)
and [workflow-report-v1.schema.json](../schemas/workflow-report-v1.schema.json).
Native validation establishes state and proof bindings; JSON schema validation
checks transport shape and grants no acknowledgment or retirement authority.
