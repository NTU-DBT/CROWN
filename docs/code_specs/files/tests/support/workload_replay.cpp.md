# `tests/support/workload_replay.cpp` — block usage map

[Source](../../../../../tests/support/workload_replay.cpp) · [Source index](../../../README.md) · [Subsystem contracts](../../../subsystem_contracts.md) · [Reviewed primitives](../../../primitives.md)

Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection.

Snapshot SHA-256: `630626d9c78723cfa70711ee0cb9797686d9b98a31fc16a574deb3e2dfb8860e`. 87 lines partitioned into 8 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [tests](../../../subsystem_contracts.md#tests). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/code_review.md](../../../../code_review.md), [docs/reference_fuzz.md](../../../../reference_fuzz.md), [docs/task_ledger.md](../../../../task_ledger.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–13](../../../../../tests/support/workload_replay.cpp#L1) | Imports dependencies; declares namespace scope; declares aliases. | source comment (unverified): // Test-boundary exporter: no oracle, query-class dispatch or timing code. · [reviewed contract](#b0001) |
| [B0002 · 14–16](../../../../../tests/support/workload_replay.cpp#L14) | Callable definition: void require(bool value, const char* message) | calls Error; guard void require(bool value, const char* message) { · [reviewed contract](#b0002) |
| [B0003 · 17–29](../../../../../tests/support/workload_replay.cpp#L17) | Callable definition: std::string read(const char* path, std::size_t limit) | calls input, require, bool, gcount; guard require(bool(input), "cannot open test input");; returns text; 1 loop sites · [reviewed contract](#b0003) |
| [B0004 · 30–34](../../../../../tests/support/workload_replay.cpp#L30) | Callable definition: template&lt;class Values&gt; Json row(const Values& values) | calls Json::array, push_back, io::write_scalar_view; returns out; growth push_back; 1 loop sites · [reviewed contract](#b0004) |
| [B0005 · 35–39](../../../../../tests/support/workload_replay.cpp#L35) | Callable definition: Json snapshot(runtime::QuerySession& owner) | calls Json::array, push_back, row, values; returns out; growth push_back; 1 loop sites · [reviewed contract](#b0005) |
| [B0006 · 40–82](../../../../../tests/support/workload_replay.cpp#L40) | Callable definition: int run(int argc, char** argv) | calls require, io::read_physical, read, normalized; guard require(argc == 5, "usage: workload_replay PHYSICAL.json INPUT.jsonl delta\|maintenance reference_or…; returns std::cout ? 0 : 1; growth insert, make_unique, push_back; 3 loop sites; source comment (unverified): // This publication cap follows full DOM/string construction; it is not peak memory. · [reviewed contract](#b0006) |
| [B0007 · 83–83](../../../../../tests/support/workload_replay.cpp#L83) | Closes surrounding scope/type. | source comment (unverified): // namespace · [reviewed contract](#b0007) |
| [B0008 · 84–87](../../../../../tests/support/workload_replay.cpp#L84) | Callable definition: int main(int argc, char** argv) | calls run, what; returns run(argc, argv); 1 · [reviewed contract](#b0008) |

## B0001

[Lines 1–13](../../../../../tests/support/workload_replay.cpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L1-L13:sha256:af45eb6df54046e671792bdcf6090dec58db8d2ed55a14008f943a78ef950803
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Prepare workload_replay.cpp: include &lt;crown/api/error.hpp&gt;, &lt;crown/io/document.hpp&gt;, &lt;crown/io/physical.hpp&gt;, &lt;crown/runtime/session.hpp&gt;, "indexed_runtime_fixture.hpp", &lt;fstream&gt;, &lt;iostream&gt;, &lt;sstream&gt;; bind local aliases/name imports. |
| inputs / outputs | Compiler-visible dependencies, names and the recorded declarations in; declarations available to the following fixture/CLI/example definitions out. |
| invariants | Declarations are scoped to this source/header and its selected ABI. Included code has its own effects; names and editable fixture values do not confer proof, admission or publication authority. |
| ownership | Aliases/includes do not create a query owner. Pointers/references/views are non-owning. Containers own their elements, which can themselves be borrowed pointers or numeric IDs. Only documented owning shared-control handles retain controls; IDs/slot-handle values do not independently keep an arena/runtime alive. |
| failure | Missing headers, ill-formed names/types, failed static assertions or active #error directives stop compilation. No runtime rejection/rollback mechanism is implemented by aliases or function prototypes. |
| cost | Preprocessing and type/constraint instantiation cost compilation. Alias/prototype syntax does not invoke the declared operation; any included definitions keep their own initialization effects. |
| Design | [tests/support/workload_replay.cpp](../../../../../tests/support/workload_replay.cpp), [docs/native-replay.md](../../../../native-replay.md), [docs/code_review.md](../../../../code_review.md) |

## B0002

[Lines 14–16](../../../../../tests/support/workload_replay.cpp#L14); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void require(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Reject invalid exporter invocation/input/state with a stable test error family. |
| inputs / outputs | False throws Error(workload_replay,message); true returns. |
| invariants | This boundary error is not a runtime rollback/retry policy or expected independent oracle. |
| ownership | Borrows literal through exception construction; thrown Error owns diagnostic. |
| failure | Error/diagnostic allocation may fail and reaches main std::exception boundary. |
| cost | Fixed success branch; failure message construction/unwind. |
| Design | [tests/support/workload_replay.cpp](../../../../../tests/support/workload_replay.cpp), [tools/verify_workloads.py](../../../../../tools/verify_workloads.py), [include/crown/io/physical.hpp](../../../../../include/crown/io/physical.hpp), [include/crown/runtime/session.hpp](../../../../../include/crown/runtime/session.hpp), [docs/native-replay.md](../../../../native-replay.md), [docs/statistics.md](../../../../statistics.md), [docs/code_review.md](../../../../code_review.md) |

## B0003

[Lines 17–29](../../../../../tests/support/workload_replay.cpp#L17); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::string read(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Read one test input with a hard retained-byte limit and checked stream status. |
| inputs / outputs | Binary reads4096-byte blocks; requires count&lt;=limit-text.size before append; checks open and !bad at end. |
| invariants | Invariant text.size&lt;=limit prevents subtraction underflow. A read can consume the block exceeding cap before rejection; cap is not peak allocation or total read-byte cap. |
| ownership | Local stream owns descriptor; returned ordinary string owns all accepted bytes. |
| failure | Missing/read/limit failure throws test Error; ordinary allocation propagates; local stream closes on unwind. |
| cost | O(input bytes) actual I/O/copy/growth plus one4KiB stack block; no native account funding. |
| Design | [tests/support/workload_replay.cpp](../../../../../tests/support/workload_replay.cpp), [tools/verify_workloads.py](../../../../../tools/verify_workloads.py), [include/crown/io/physical.hpp](../../../../../include/crown/io/physical.hpp), [include/crown/runtime/session.hpp](../../../../../include/crown/runtime/session.hpp), [docs/native-replay.md](../../../../native-replay.md), [docs/statistics.md](../../../../statistics.md), [docs/code_review.md](../../../../code_review.md) |

## B0004

[Lines 30–34](../../../../../tests/support/workload_replay.cpp#L30); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
template<class Values> Json row(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Export one observed native/ordinary tuple to an owning JSON array. |
| inputs / outputs | Uses write_scalar_view for every field. |
| invariants | Preserves observed scalar serialization; does not independently evaluate query truth or type-admit inputs. |
| ownership | Input view is borrowed during traversal; returned ordinary DOM owns copied scalar/string values. |
| failure | Scalar conversion/ordinary DOM allocation failures propagate. |
| cost | O(fields+scalar bytes) export and DOM allocations; no query-account charge for ordinary JSON. |
| Design | [tests/support/workload_replay.cpp](../../../../../tests/support/workload_replay.cpp), [tools/verify_workloads.py](../../../../../tools/verify_workloads.py), [include/crown/io/physical.hpp](../../../../../include/crown/io/physical.hpp), [include/crown/runtime/session.hpp](../../../../../include/crown/runtime/session.hpp), [docs/native-replay.md](../../../../native-replay.md), [docs/statistics.md](../../../../statistics.md), [docs/code_review.md](../../../../code_review.md) |

## B0005

[Lines 35–39](../../../../../tests/support/workload_replay.cpp#L35); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Json snapshot(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Export the current real session snapshot to ordinary JSON. |
| inputs / outputs | Captures actual snapshot then exports all tuple fields through row. |
| invariants | Actual native snapshot capture owns/funds native data; output JSON is independent ordinary copied report data, not an oracle. |
| ownership | Local snapshot remains alive during borrowed row access; returned DOM owns deep copies. |
| failure | Native capture/account/grant or ordinary JSON allocation/conversion failures propagate. |
| cost | Full snapshot capture plus O(rows/scalar bytes) export and DOM storage. |
| Design | [tests/support/workload_replay.cpp](../../../../../tests/support/workload_replay.cpp), [tools/verify_workloads.py](../../../../../tools/verify_workloads.py), [include/crown/io/physical.hpp](../../../../../include/crown/io/physical.hpp), [include/crown/runtime/session.hpp](../../../../../include/crown/runtime/session.hpp), [docs/native-replay.md](../../../../native-replay.md), [docs/statistics.md](../../../../statistics.md), [docs/code_review.md](../../../../code_review.md) |

## B0006

[Lines 40–82](../../../../../tests/support/workload_replay.cpp#L40); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
int run(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Execute a bounded actual-session replay and publish observed facts for an external independent checker. |
| inputs / outputs | Accepts physical/input/mode/backend args; reads/admit plan, optionally relowers indexed normalized plan, creates owned-stream session, exports initial/epoch rows/progress/deltas and JSON report. |
| invariants | No oracle/query-class dispatch/timing. reference_ordered_v1 argument leaves supplied plan unchanged; report records actual guarantee backend. Caps records4096, total step calls10M, final serialized bytes64MiB. |
| ownership | Owns source text, istringstream, real move-only session and ordinary report DOM; program handle retains compiler admission. |
| failure | Any input/native/export/allocation/limit failure propagates to main; committed epochs remain committed privately. Final size check is after dump allocation, not peak memory bound. |
| cost | Full actual compilation/admission/replay, snapshots/output drain and ordinary serialization copies; caps are explicit trace guards, not whole CPU/memory claims. |
| Design | [tests/support/workload_replay.cpp](../../../../../tests/support/workload_replay.cpp), [tools/verify_workloads.py](../../../../../tools/verify_workloads.py), [include/crown/io/physical.hpp](../../../../../include/crown/io/physical.hpp), [include/crown/runtime/session.hpp](../../../../../include/crown/runtime/session.hpp), [docs/native-replay.md](../../../../native-replay.md), [docs/statistics.md](../../../../statistics.md), [docs/code_review.md](../../../../code_review.md) |

```text
if (backend == "indexed_chained_v1")
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Choose a real indexed physical plan when explicitly requested. |
| inputs / outputs | Requires normalized source and relowers with finite s04 runtime storage options. |
| invariants | Ordered argument does not override an already indexed artifact; actual plan backend is exported. |
| ownership | Local real Session/DOM/string owners persist through immediate borrowed accesses; report rows are ordinary deep copies. |
| failure | Native/input/ordinary allocation/assertion errors propagate; previously committed private epochs need not be rolled back. |
| cost | Actual normalized lowering/admission, not metadata relabeling. |
| Design | [tests/support/workload_replay.cpp](../../../../../tests/support/workload_replay.cpp), [tools/verify_workloads.py](../../../../../tools/verify_workloads.py), [include/crown/io/physical.hpp](../../../../../include/crown/io/physical.hpp), [include/crown/runtime/session.hpp](../../../../../include/crown/runtime/session.hpp), [docs/native-replay.md](../../../../native-replay.md), [docs/statistics.md](../../../../statistics.md), [docs/code_review.md](../../../../code_review.md) |

```text
auto owner = runtime::QuerySession::create(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Own an input-stream-backed real session for replay. |
| inputs / outputs | Copies full text into istringstream, passes actual plan/mode options into QuerySession::create. |
| invariants | Stream source authority/progress belongs to real ingestion/session code, not this exporter's JSON. |
| ownership | Local real Session/DOM/string owners persist through immediate borrowed accesses; report rows are ordinary deep copies. |
| failure | Native/input/ordinary allocation/assertion errors propagate; previously committed private epochs need not be rolled back. |
| cost | Actual session admission/native startup plus ordinary full-text stream copy. |
| Design | [tests/support/workload_replay.cpp](../../../../../tests/support/workload_replay.cpp), [tools/verify_workloads.py](../../../../../tools/verify_workloads.py), [include/crown/io/physical.hpp](../../../../../include/crown/io/physical.hpp), [include/crown/runtime/session.hpp](../../../../../include/crown/runtime/session.hpp), [docs/native-replay.md](../../../../native-replay.md), [docs/statistics.md](../../../../statistics.md), [docs/code_review.md](../../../../code_review.md) |

```text
require(status == runtime::SessionBegin::pending
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Bound real epoch replay before committing/exporting observations. |
| inputs / outputs | Requires pending and records&lt;4096; steps until prepared under one total10M-call counter; commits then drains outputs. |
| invariants | records counts physical processed epochs; step counter spans complete trace. Engine commit occurs before report DOM insertion. |
| ownership | Local real Session/DOM/string owners persist through immediate borrowed accesses; report rows are ordinary deep copies. |
| failure | Native/input/ordinary allocation/assertion errors propagate; previously committed private epochs need not be rolled back. |
| cost | All native preparation/commit/output work and ordinary signed-row DOM construction. |
| Design | [tests/support/workload_replay.cpp](../../../../../tests/support/workload_replay.cpp), [tools/verify_workloads.py](../../../../../tools/verify_workloads.py), [include/crown/io/physical.hpp](../../../../../include/crown/io/physical.hpp), [include/crown/runtime/session.hpp](../../../../../include/crown/runtime/session.hpp), [docs/native-replay.md](../../../../native-replay.md), [docs/statistics.md](../../../../statistics.md), [docs/code_review.md](../../../../code_review.md) |

```text
report["epochs"].push_back
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Retain each observed committed state/progress/delta in the report. |
| inputs / outputs | Copies sequence/source_positions and full current snapshot; moves signed delta DOM. |
| invariants | Output is observed evidence for external verify_workloads.py, not internally derived expected answers. |
| ownership | Local real Session/DOM/string owners persist through immediate borrowed accesses; report rows are ordinary deep copies. |
| failure | Native/input/ordinary allocation/assertion errors propagate; previously committed private epochs need not be rolled back. |
| cost | Full current-row capture/export plus report DOM growth per epoch. |
| Design | [tests/support/workload_replay.cpp](../../../../../tests/support/workload_replay.cpp), [tools/verify_workloads.py](../../../../../tools/verify_workloads.py), [include/crown/io/physical.hpp](../../../../../include/crown/io/physical.hpp), [include/crown/runtime/session.hpp](../../../../../include/crown/runtime/session.hpp), [docs/native-replay.md](../../../../native-replay.md), [docs/statistics.md](../../../../statistics.md), [docs/code_review.md](../../../../code_review.md) |

```text
const auto encoded = report.dump();
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Serialize complete observed report then enforce publication-size cap. |
| inputs / outputs | Creates full encoded string, requires&lt;=64MiB, writes stdout newline and returns stream status. |
| invariants | Check occurs after DOM and encoded allocation; it is not peak-memory or early streaming bound. No report is written before this phase. |
| ownership | Local real Session/DOM/string owners persist through immediate borrowed accesses; report rows are ordinary deep copies. |
| failure | Native/input/ordinary allocation/assertion errors propagate; previously committed private epochs need not be rolled back. |
| cost | Full report traversal/string allocation and output I/O; potential retained DOM+encoded copies coexist. |
| Design | [tests/support/workload_replay.cpp](../../../../../tests/support/workload_replay.cpp), [tools/verify_workloads.py](../../../../../tools/verify_workloads.py), [include/crown/io/physical.hpp](../../../../../include/crown/io/physical.hpp), [include/crown/runtime/session.hpp](../../../../../include/crown/runtime/session.hpp), [docs/native-replay.md](../../../../native-replay.md), [docs/statistics.md](../../../../statistics.md), [docs/code_review.md](../../../../code_review.md) |

## B0007

[Lines 83–83](../../../../../tests/support/workload_replay.cpp#L83); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L83-L83:sha256:533f16bca7d58f44b3103b92e3485d22cfbb34bbad5ea3f3fa3b5a9dcb24ec89
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Close the recorded declaration scopes in workload_replay.cpp: namespace (anonymous). |
| inputs / outputs | Preceding namespace, type or initializer declarations in; completed lexical boundary out. |
| invariants | Brace-opening context is recorded in root-scope-context-v1.json. These are declaration/initializer boundaries, not an independent update, validation or recovery operation. |
| ownership | Enclosing objects and borrowed fields keep their declared ownership. This punctuation creates no new owner. |
| failure | Malformed scope syntax is a compile error. Any initializer/constructor failure belongs to the enclosing object declaration. |
| cost | No separate loop, guard or engine call is introduced by the delimiter; enclosing initialization and object lifetime still have their actual costs. |
| Design | [tests/support/workload_replay.cpp](../../../../../tests/support/workload_replay.cpp), [docs/native-replay.md](../../../../native-replay.md), [docs/code_review.md](../../../../code_review.md) |

## B0008

[Lines 84–87](../../../../../tests/support/workload_replay.cpp#L84); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
int main(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Translate test executable exceptions to a failed process exit. |
| inputs / outputs | Calls run, catches std::exception, writes what() to stderr and returns1. |
| invariants | One necessary CLI diagnostic boundary; no retries/native state restoration, and non-std exceptions are not swallowed. |
| ownership | Exception diagnostic is borrowed only during catch; run-local owners already unwind. |
| failure | Standard failures become exit1; stderr flags are not explicitly checked and non-std exceptions remain uncaught. |
| cost | One boundary call; on failure exception unwind plus diagnostic I/O. |
| Design | [tests/support/workload_replay.cpp](../../../../../tests/support/workload_replay.cpp), [tools/verify_workloads.py](../../../../../tools/verify_workloads.py), [include/crown/io/physical.hpp](../../../../../include/crown/io/physical.hpp), [include/crown/runtime/session.hpp](../../../../../include/crown/runtime/session.hpp), [docs/native-replay.md](../../../../native-replay.md), [docs/statistics.md](../../../../statistics.md), [docs/code_review.md](../../../../code_review.md) |
