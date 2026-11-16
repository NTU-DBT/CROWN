# `tests/unit/source_checkpoint_test.cpp` — block usage map

[Source](../../../../../tests/unit/source_checkpoint_test.cpp) · [Source index](../../../README.md) · [Subsystem contracts](../../../subsystem_contracts.md) · [Reviewed primitives](../../../primitives.md)

Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection.

Snapshot SHA-256: `5e85851dce8510e3325fa26ede9181095d96c872dbf67313b065db98a7116a88`. 158 lines partitioned into 12 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [tests](../../../subsystem_contracts.md#tests). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/code_review.md](../../../../code_review.md), [docs/reference_fuzz.md](../../../../reference_fuzz.md), [docs/task_ledger.md](../../../../task_ledger.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–10](../../../../../tests/unit/source_checkpoint_test.cpp#L1) | Imports dependencies; declares namespace scope; declares aliases. |  · [reviewed contract](#b0001) |
| [B0002 · 11–11](../../../../../tests/unit/source_checkpoint_test.cpp#L11) | Callable definition: void check(bool value,const char* message) | calls std::runtime_error; guard void check(bool value,const char* message){if(!value)throw std::runtime_error(message);} · [reviewed contract](#b0002) |
| [B0003 · 12–15](../../../../../tests/unit/source_checkpoint_test.cpp#L12) | Callable definition: PhysicalPlan plan(bool indexed=false) | calls planner::lower_tree, s04_runtime::options; returns planner::lower_tree(catalog,Query{{},{},{},false},FreeConnexTree{},indexed?s04_runtime::options():P… · [reviewed contract](#b0003) |
| [B0004 · 16–17](../../../../../tests/unit/source_checkpoint_test.cpp#L16) | declares callable signatures; declares values/defaults or compile-time conditions. |  · [reviewed contract](#b0004) |
| [B0005 · 18–21](../../../../../tests/unit/source_checkpoint_test.cpp#L18) | Callable definition: template&lt;class Action&gt; void rejected(Action action) | calls action, check; guard check(failed,"invalid native source state accepted"); · [reviewed contract](#b0005) |
| [B0006 · 22–22](../../../../../tests/unit/source_checkpoint_test.cpp#L22) | Type/record definition: struct Profile |  · [reviewed contract](#b0006) |
| [B0007 · 23–42](../../../../../tests/unit/source_checkpoint_test.cpp#L23) | Callable definition: Profile profile(io::InputFormat format,const program::Catalog& catalog) | calls io::write_input_json, io::write_input_binary, emplace, size; returns result; growth emplace, insert · [reviewed contract](#b0007) |
| [B0008 · 43–97](../../../../../tests/unit/source_checkpoint_test.cpp#L43) | Callable definition: void reader(io::InputFormat format) | calls plan, owner, receiving, account; guard check(original.peek()-&gt;update.values==first,"reader first record differs");; 3 loop sites · [reviewed contract](#b0008) |
| [B0009 · 98–134](../../../../../tests/unit/source_checkpoint_test.cpp#L98) | Callable definition: void queue(io::QueueMode mode,bool closed) | calls plan, owner, receiving, account; guard io::TransportBatch batch({item(1)});check(original.enqueue(batch)==io::Admission::accepted,"queue f…; returns io::InputEvent{{sequence,TableId{0},SetOperation::insert,first},io::SourcePosition{source_name,sequ…; growth emplace, insert; 2 loop sites · [reviewed contract](#b0009) |
| [B0010 · 135–149](../../../../../tests/unit/source_checkpoint_test.cpp#L135) | Callable definition: void large_positions() | calls plan, owner, receiving, original; guard io::TransportBatch batch(std::move(events));check(original.enqueue(batch)==io::Admission::accepted,…; growth emplace_back, insert, reserve; 2 loop sites · [reviewed contract](#b0010) |
| [B0011 · 150–150](../../../../../tests/unit/source_checkpoint_test.cpp#L150) | Closes surrounding scope/type. |  · [reviewed contract](#b0011) |
| [B0012 · 151–158](../../../../../tests/unit/source_checkpoint_test.cpp#L151) | Callable definition: int main() | calls reader, queue, large_positions, what; returns 1; 3 loop sites · [reviewed contract](#b0012) |

## B0001

[Lines 1–10](../../../../../tests/unit/source_checkpoint_test.cpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L1-L10:sha256:71a43052ea037db63a85b56fc843b8c203a475d18cc81e910af7c66b1e7c7630
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Prepare source_checkpoint_test.cpp: include "crown/io/checkpoint.hpp", "crown/runtime/delta.hpp", "indexed_runtime_fixture.hpp", "index_allocation.hpp", &lt;iostream&gt;, &lt;optional&gt;, &lt;sstream&gt;, &lt;stdexcept&gt;; bind local aliases/name imports. |
| inputs / outputs | Compiler-visible dependencies, names and the recorded declarations in; declarations available to the following fixture/CLI/example definitions out. |
| invariants | Declarations are scoped to this source/header and its selected ABI. Included code has its own effects; names and editable fixture values do not confer proof, admission or publication authority. |
| ownership | Aliases/includes do not create a query owner. Pointers/references/views are non-owning. Containers own their elements, which can themselves be borrowed pointers or numeric IDs. Only documented owning shared-control handles retain controls; IDs/slot-handle values do not independently keep an arena/runtime alive. |
| failure | Missing headers, ill-formed names/types, failed static assertions or active #error directives stop compilation. No runtime rejection/rollback mechanism is implemented by aliases or function prototypes. |
| cost | Preprocessing and type/constraint instantiation cost compilation. Alias/prototype syntax does not invoke the declared operation; any included definitions keep their own initialization effects. |
| Design | [tests/unit/source_checkpoint_test.cpp](../../../../../tests/unit/source_checkpoint_test.cpp), [docs/checkpoints.md](../../../../checkpoints.md), [docs/code_review.md](../../../../code_review.md) |

## B0002

[Lines 11–11](../../../../../tests/unit/source_checkpoint_test.cpp#L11); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void check(bool value,const char* message)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Fail a native source checkpoint assertion without rewriting its error category. |
| inputs / outputs | A false predicate throws std::runtime_error; true returns. |
| invariants | The helper catches no ImageFailure and verifies only the local test condition. |
| ownership | Diagnostic is borrowed until exception construction. |
| failure | False is a local assertion failure. |
| cost | One branch; no fixture or account allocation. |
| Design | [tests/unit/source_checkpoint_test.cpp](../../../../../tests/unit/source_checkpoint_test.cpp), [docs/checkpoints.md § Native source and window state components](../../../../checkpoints.md), [docs/batches_windows.md § Typed ordered input](../../../../batches_windows.md), [src/io/event_reader.cpp](../../../../../src/io/event_reader.cpp), [src/io/batch.cpp](../../../../../src/io/batch.cpp), [src/io/checkpoint_detail.hpp](../../../../../src/io/checkpoint_detail.hpp), [tests/support/indexed_runtime_fixture.hpp](../../../../../tests/support/indexed_runtime_fixture.hpp), [tests/support/index_allocation.hpp](../../../../../tests/support/index_allocation.hpp) |

## B0003

[Lines 12–15](../../../../../tests/unit/source_checkpoint_test.cpp#L12); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
PhysicalPlan plan(bool indexed=false)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Build a deterministic empty-query source plan over one two-field catalog, optionally indexed. |
| inputs / outputs | Takes backend selection and lowers an empty query/tree over string/int64 input. |
| invariants | Catalog remains available for input decoding while query output avoids introducing unrelated join state. |
| ownership | Planner owns returned PhysicalPlan; temporary catalog/query inputs are caller-side fixture values. |
| failure | Invalid lowering/backend setup propagates before reader/queue tests run. |
| cost | One fixed plan build; indexed grants are fixture settings, not row copies or CPU limits. |
| Design | [tests/unit/source_checkpoint_test.cpp](../../../../../tests/unit/source_checkpoint_test.cpp), [docs/checkpoints.md § Native source and window state components](../../../../checkpoints.md), [docs/batches_windows.md § Typed ordered input](../../../../batches_windows.md), [src/io/event_reader.cpp](../../../../../src/io/event_reader.cpp), [src/io/batch.cpp](../../../../../src/io/batch.cpp), [src/io/checkpoint_detail.hpp](../../../../../src/io/checkpoint_detail.hpp), [tests/support/indexed_runtime_fixture.hpp](../../../../../tests/support/indexed_runtime_fixture.hpp), [tests/support/index_allocation.hpp](../../../../../tests/support/index_allocation.hpp) |

## B0004

[Lines 16–17](../../../../../tests/unit/source_checkpoint_test.cpp#L16); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
const Row first{std::string("alpha"),std::int64_t{7}},second{std::string("beta,tail"),std::int64_t{8}};
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Create the source-checkpoint test’s immutable translation-unit-wide name and two source rows before main. |
| inputs / outputs | Dynamically initializes source_name as 8,192 's' characters and first/second as two string-bearing Row values; profile() uses them to build source-positioned inputs. |
| invariants | These are private test executable globals in an anonymous namespace, not library startup work or a public latency promise; they are constructed once per process before main. |
| ownership | Static-lifetime const objects own their string/row data for the test process lifetime. |
| failure | No local catch surrounds initialization; an initialization/allocation failure prevents normal test startup. |
| cost | One 8 KiB string plus two small rows, once per test process; no per-event recreation for these source values. |
| Design | [tests/unit/source_checkpoint_test.cpp](../../../../../tests/unit/source_checkpoint_test.cpp), tests/unit/source_checkpoint_test.cpp:23-40, [CMakeLists.txt](../../../../../CMakeLists.txt), tests/unit/source_checkpoint_test.cpp:16-17 |

## B0005

[Lines 18–21](../../../../../tests/unit/source_checkpoint_test.cpp#L18); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
template<class Action> void rejected(Action action)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Require native source-state restoration or capture to reject malformed limits/metadata. |
| inputs / outputs | Invokes an action and accepts only recovery::ImageFailure. |
| invariants | Error-specific checks elsewhere still identify work/limit when relevant; unrelated exceptions do not count here. |
| ownership | Action and snapshots remain locally owned; no failure result is retained. |
| failure | Normal return or another exception fails the test. |
| cost | One supplied action call; its native validation work is bounded by fixture metadata limits. |
| Design | [tests/unit/source_checkpoint_test.cpp](../../../../../tests/unit/source_checkpoint_test.cpp), [docs/checkpoints.md § Native source and window state components](../../../../checkpoints.md), [docs/batches_windows.md § Typed ordered input](../../../../batches_windows.md), [src/io/event_reader.cpp](../../../../../src/io/event_reader.cpp), [src/io/batch.cpp](../../../../../src/io/batch.cpp), [src/io/checkpoint_detail.hpp](../../../../../src/io/checkpoint_detail.hpp), [tests/support/indexed_runtime_fixture.hpp](../../../../../tests/support/indexed_runtime_fixture.hpp), [tests/support/index_allocation.hpp](../../../../../tests/support/index_allocation.hpp) |

## B0006

[Lines 22–22](../../../../../tests/unit/source_checkpoint_test.cpp#L22); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct Profile
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Bundle input options and split source bytes into the pre-checkpoint prefix and caller continuation tail. |
| inputs / outputs | Profile contains AccountedInputOptions plus ordinary prefix/tail strings for a chosen format/catalog. |
| invariants | All profiles use one 8192-byte source name and two record limits; option offsets and wire encoding vary by format. |
| ownership | The struct owns input options and both strings; stream consumers borrow/copy them as their APIs require. |
| failure | Unsupported profile branches leave the fixture incomplete and are caught by later record assertions. |
| cost | Profile bytes are small except the deliberately long source name; storage is ordinary test memory before reader admission. |
| Design | [tests/unit/source_checkpoint_test.cpp](../../../../../tests/unit/source_checkpoint_test.cpp), [docs/checkpoints.md § Native source and window state components](../../../../checkpoints.md), [docs/batches_windows.md § Typed ordered input](../../../../batches_windows.md), [src/io/event_reader.cpp](../../../../../src/io/event_reader.cpp), [src/io/batch.cpp](../../../../../src/io/batch.cpp), [src/io/checkpoint_detail.hpp](../../../../../src/io/checkpoint_detail.hpp), [tests/support/indexed_runtime_fixture.hpp](../../../../../tests/support/indexed_runtime_fixture.hpp), [tests/support/index_allocation.hpp](../../../../../tests/support/index_allocation.hpp) |

## B0007

[Lines 23–42](../../../../../tests/unit/source_checkpoint_test.cpp#L23); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Profile profile(io::InputFormat format,const program::Catalog& catalog)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Construct one of eight valid stream-format profiles with one consumed-record prefix and one continuation tail. |
| inputs / outputs | Returns format settings and encoded JSONL, binary, CSV, or legacy record bytes for the same two typed input events. |
| invariants | The two source positions are 10/20 and catalog/source bindings stay fixed; CSV and legacy encodings preserve commas/headers and configured byte origin. |
| ownership | Returned options/strings own fixture data; the EventReader later imports native options and progress under the runtime account. |
| failure | Format-specific row mismatch or invalid setup is detected by reader peek/continuation assertions. |
| cost | Builds at most two encoded records and one long source name; serializer string storage is test-side, not part of EventReader's native account. |
| Design | [tests/unit/source_checkpoint_test.cpp](../../../../../tests/unit/source_checkpoint_test.cpp), [docs/checkpoints.md § Native source and window state components](../../../../checkpoints.md), [docs/batches_windows.md § Typed ordered input](../../../../batches_windows.md), [src/io/event_reader.cpp](../../../../../src/io/event_reader.cpp), [src/io/batch.cpp](../../../../../src/io/batch.cpp), [src/io/checkpoint_detail.hpp](../../../../../src/io/checkpoint_detail.hpp), [tests/support/indexed_runtime_fixture.hpp](../../../../../tests/support/indexed_runtime_fixture.hpp), [tests/support/index_allocation.hpp](../../../../../tests/support/index_allocation.hpp) |

## B0008

[Lines 43–97](../../../../../tests/unit/source_checkpoint_test.cpp#L43); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void reader(io::InputFormat format)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Capture and restore EventReader after acknowledging one record, across native source formats and limits. |
| inputs / outputs | For a format, checks peek barrier, acknowledges first event, captures counters/progress/options, restores using tail stream, and compares the next record and EOF. |
| invariants | Snapshot bytes/records keep original source origin; restore receives a continuation at next unread byte and never consumes it at saved EOF. Malformed catalog, count, size, header, work, or CSV field limit rejects. |
| ownership | Original reader owns source metadata under its plan account; ReaderCheckpoint owns native cloned progress/options; target reader uses receiving plan account; std::istringstream tail is caller-owned. |
| failure | Every measured test replacement-new fault cut for capture/restore must leave original/target resident state unchanged; corrupted snapshots and zero work reject. |
| cost | Two records per profile, finite measured replacement-new fault cuts and four metadata mutations; actual reader snapshots/options use query account, wire strings and streams are fixture copies. |
| Design | [tests/unit/source_checkpoint_test.cpp](../../../../../tests/unit/source_checkpoint_test.cpp), [docs/checkpoints.md § Native source and window state components](../../../../checkpoints.md), [docs/batches_windows.md § Typed ordered input](../../../../batches_windows.md), [src/io/event_reader.cpp](../../../../../src/io/event_reader.cpp), [src/io/batch.cpp](../../../../../src/io/batch.cpp), [src/io/checkpoint_detail.hpp](../../../../../src/io/checkpoint_detail.hpp), [tests/support/indexed_runtime_fixture.hpp](../../../../../tests/support/indexed_runtime_fixture.hpp), [tests/support/index_allocation.hpp](../../../../../tests/support/index_allocation.hpp) |

## B0009

[Lines 98–134](../../../../../tests/unit/source_checkpoint_test.cpp#L98); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void queue(io::QueueMode mode,bool closed)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Capture/restore an empty TypedQueue checkpoint at a consumed physical or window boundary, open or closed. |
| inputs / outputs | Admits one item, proves nonempty queue blocks capture, acknowledges it, optionally closes, captures, restores, tests faults/malformed binding/work, and appends next sequence if open. |
| invariants | Queue mode, catalog binding, source positions, closure and account are reconstructed; open queues retain next admission while closed queues stay terminal. |
| ownership | Queue nodes/options/progress belong to original/receiving query accounts; offered TransportBatch and stream/progress exports are caller-owned DTOs. |
| failure | Every measured test replacement-new fault cut leaves source/target state unchanged; bad catalog or zero work rejects, while restored open admission must accept sequence 2. |
| cost | One source event per normal case; one batch is compacted into native queue ownership; source-name/row test values and exported progress are extra ordinary copies; MemoryAccount quota errors are separate from bad_alloc injection. |
| Design | [tests/unit/source_checkpoint_test.cpp](../../../../../tests/unit/source_checkpoint_test.cpp), [docs/checkpoints.md § Native source and window state components](../../../../checkpoints.md), [docs/batches_windows.md § Typed ordered input](../../../../batches_windows.md), [src/io/event_reader.cpp](../../../../../src/io/event_reader.cpp), [src/io/batch.cpp](../../../../../src/io/batch.cpp), [src/io/checkpoint_detail.hpp](../../../../../src/io/checkpoint_detail.hpp), [tests/support/indexed_runtime_fixture.hpp](../../../../../tests/support/indexed_runtime_fixture.hpp), [tests/support/index_allocation.hpp](../../../../../tests/support/index_allocation.hpp) |

## B0010

[Lines 135–149](../../../../../tests/unit/source_checkpoint_test.cpp#L135); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void large_positions()
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Exercise a queue checkpoint with 1025 distinct accepted source positions against default and custom position caps. |
| inputs / outputs | Builds one 1025-item external batch, acknowledges it, expects default capture/restore limits to reject, then captures/restores with positions=2048. |
| invariants | Position count is limited independently of event/record count; raising the explicit source-position limit is required to preserve this larger accepted history. |
| ownership | TransportBatch/vector and its Rows are ordinary caller-owned input; after accepted enqueue the native TypedQueue owns compact rows/nodes under its account; QueueCheckpoint owns copied progress. |
| failure | Default limit rejection must not prevent successful custom-limit restoration with all 1025 source positions. |
| cost | Fixture reserves and builds exactly 1025 DTO events and creates 1025 native progress entries; retained native admission is account-funded, while the input batch and generated source strings are external copies. |
| Design | [tests/unit/source_checkpoint_test.cpp](../../../../../tests/unit/source_checkpoint_test.cpp), [docs/checkpoints.md § Native source and window state components](../../../../checkpoints.md), [docs/batches_windows.md § Typed ordered input](../../../../batches_windows.md), [src/io/event_reader.cpp](../../../../../src/io/event_reader.cpp), [src/io/batch.cpp](../../../../../src/io/batch.cpp), [src/io/checkpoint_detail.hpp](../../../../../src/io/checkpoint_detail.hpp), [tests/support/indexed_runtime_fixture.hpp](../../../../../tests/support/indexed_runtime_fixture.hpp), [tests/support/index_allocation.hpp](../../../../../tests/support/index_allocation.hpp) |

## B0011

[Lines 150–150](../../../../../tests/unit/source_checkpoint_test.cpp#L150); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L150-L150:sha256:412ca345ccf75bf9c0806bce695be8de808b79984251a7a54d202cf6101dd451
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Close the recorded declaration scopes in source_checkpoint_test.cpp: namespace (anonymous). |
| inputs / outputs | Preceding namespace, type or initializer declarations in; completed lexical boundary out. |
| invariants | Brace-opening context is recorded in root-scope-context-v1.json. These are declaration/initializer boundaries, not an independent update, validation or recovery operation. |
| ownership | Enclosing objects and borrowed fields keep their declared ownership. This punctuation creates no new owner. |
| failure | Malformed scope syntax is a compile error. Any initializer/constructor failure belongs to the enclosing object declaration. |
| cost | No separate loop, guard or engine call is introduced by the delimiter; enclosing initialization and object lifetime still have their actual costs. |
| Design | [tests/unit/source_checkpoint_test.cpp](../../../../../tests/unit/source_checkpoint_test.cpp), [docs/checkpoints.md](../../../../checkpoints.md), [docs/code_review.md](../../../../code_review.md) |

## B0012

[Lines 151–158](../../../../../tests/unit/source_checkpoint_test.cpp#L151); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
int main()
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Run all eight reader formats, both typed queue modes with open/closed boundaries, and the large-position regression. |
| inputs / outputs | Loops JSONL/binary/CSV/five legacy formats; queue physical/window × open/closed; then 1025-source case. |
| invariants | No journal, full session, or window-to-base join is tested here; these are lower native source-component checkpoint tests. |
| ownership | Each reader/queue and DeltaRuntime owner is local to its test function and released before the next profile. |
| failure | Any source capture/restore/continuation assertion fails the executable. |
| cost | Eight reader cases, four queue cases, and one 1025-position case; fault count depends on measured bounded allocations for each small native source graph. |
| Design | [tests/unit/source_checkpoint_test.cpp](../../../../../tests/unit/source_checkpoint_test.cpp), [docs/checkpoints.md § Native source and window state components](../../../../checkpoints.md), [docs/batches_windows.md § Typed ordered input](../../../../batches_windows.md), [src/io/event_reader.cpp](../../../../../src/io/event_reader.cpp), [src/io/batch.cpp](../../../../../src/io/batch.cpp), [src/io/checkpoint_detail.hpp](../../../../../src/io/checkpoint_detail.hpp), [tests/support/indexed_runtime_fixture.hpp](../../../../../tests/support/indexed_runtime_fixture.hpp), [tests/support/index_allocation.hpp](../../../../../tests/support/index_allocation.hpp) |
