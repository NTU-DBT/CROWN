# `tests/unit/statistics_report_fixture.hpp` — block usage map

[Source](../../../../../tests/unit/statistics_report_fixture.hpp) · [Source index](../../../README.md) · [Subsystem contracts](../../../subsystem_contracts.md) · [Reviewed primitives](../../../primitives.md)

Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection.

Snapshot SHA-256: `6dcaba03600ad201bd0268c2eb0fa6b539316b3413758ac82cfe378357a54aa1`. 26 lines partitioned into 8 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [tests](../../../subsystem_contracts.md#tests). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/code_review.md](../../../../code_review.md), [docs/reference_fuzz.md](../../../../reference_fuzz.md), [docs/task_ledger.md](../../../../task_ledger.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–11](../../../../../tests/unit/statistics_report_fixture.hpp#L1) | Imports dependencies; guards repeated header inclusion; declares namespace scope; declares aliases; declares values/defaults or compile-time conditions. |  · [reviewed contract](#b0001) |
| [B0002 · 12–12](../../../../../tests/unit/statistics_report_fixture.hpp#L12) | Callable definition: inline Capture requested(const PhysicalPlan& value) | calls request; returns options · [reviewed contract](#b0002) |
| [B0003 · 13–13](../../../../../tests/unit/statistics_report_fixture.hpp#L13) | Callable definition: inline void write(const std::filesystem::path& path,const std::string& value) | calls out, check, bool; guard inline void write(const std::filesystem::path& path,const std::string& value){std::ofstream out(pat… · [reviewed contract](#b0003) |
| [B0004 · 14–17](../../../../../tests/unit/statistics_report_fixture.hpp#L14) | Callable definition: inline Report emit(const std::filesystem::path& dir,const char* label,Report report) | calls write, std::string, io::write_statistics_json, io::write_statistics_text; returns report · [reviewed contract](#b0004) |
| [B0005 · 18–18](../../../../../tests/unit/statistics_report_fixture.hpp#L18) | Callable definition: inline void literal(const Report& report,const Database& db,std::uint64_t sequence) | calls check, combined, has_value, facts; guard inline void literal(const Report& report,const Database& db,std::uint64_t sequence){check(report.co… · [reviewed contract](#b0005) |
| [B0006 · 19–21](../../../../../tests/unit/statistics_report_fixture.hpp#L19) | Callable definition: inline void enqueue(QuerySession& session,PhysicalSetUpdate update) | calls batch, std::move, check; guard io::TransportBatch batch({io::InputEvent{std::move(update),{}}});check(session.enqueue(batch)==io::… · [reviewed contract](#b0006) |
| [B0007 · 22–25](../../../../../tests/unit/statistics_report_fixture.hpp#L22) | Callable definition: inline void legacy_pair(const std::filesystem::path& dir,DeltaRuntime& runtime,const QuerySession& session) | calls write, io::write_explain_json, observability::PlanExplanation::capture · [reviewed contract](#b0007) |
| [B0008 · 26–26](../../../../../tests/unit/statistics_report_fixture.hpp#L26) | Closes surrounding scope/type. |  · [reviewed contract](#b0008) |

## B0001

[Lines 1–11](../../../../../tests/unit/statistics_report_fixture.hpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L1-L11:sha256:189714b511aeeb5de3b3616a6bea8f44ff12bcfc227401ea83764c5bf188cb68
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Prepare statistics_report_fixture.hpp: include "combined_statistics_fixture.hpp", "crown/io/statistics_explain.hpp", "crown/io/explain.hpp", &lt;filesystem&gt;, &lt;fstream&gt;; bind local aliases/name imports. |
| inputs / outputs | Compiler-visible dependencies, names and the recorded declarations in; declarations available to the following fixture/CLI/example definitions out. |
| invariants | Declarations are scoped to this source/header and its selected ABI. Included code has its own effects; names and editable fixture values do not confer proof, admission or publication authority. |
| ownership | Aliases/includes do not create a query owner. Pointers/references/views are non-owning. Containers own their elements, which can themselves be borrowed pointers or numeric IDs. Only documented owning shared-control handles retain controls; IDs/slot-handle values do not independently keep an arena/runtime alive. |
| failure | Missing headers, ill-formed names/types, failed static assertions or active #error directives stop compilation. No runtime rejection/rollback mechanism is implemented by aliases or function prototypes. |
| cost | Preprocessing and type/constraint instantiation cost compilation. Alias/prototype syntax does not invoke the declared operation; any included definitions keep their own initialization effects. |
| Design | [tests/unit/statistics_report_fixture.hpp](../../../../../tests/unit/statistics_report_fixture.hpp), [docs/statistics.md](../../../../statistics.md), [docs/code_review.md](../../../../code_review.md) |

## B0002

[Lines 12–12](../../../../../tests/unit/statistics_report_fixture.hpp#L12); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
inline Capture requested(const PhysicalPlan& value){Capture options;options.state=request(value);return options;}
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Create report-capture options requesting the shared owner fixture selections. |
| inputs / outputs | Borrowed PhysicalPlan enters; Capture exits with state request populated by owner_fixture::request. |
| invariants | Request identities are taken from the same compiled plan; default state limits remain explicit library defaults. |
| ownership | Returned options own the request vectors; plan is borrowed only while constructing them. |
| failure | Request construction/allocation errors propagate. |
| cost | Copies seven fixed scopes and scans plan edges for the selected reverse index. |
| Design | [docs/statistics.md](../../../../statistics.md), [docs/observability.md](../../../../observability.md), [Refactor.md](../../../../../Refactor.md) |

## B0003

[Lines 13–13](../../../../../tests/unit/statistics_report_fixture.hpp#L13); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
inline void write(const std::filesystem::path& path,const std::string& value){std::ofstream out(path,std::ios::binary);out<<value;check(bool(out));}
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Write exact serialized report bytes to a binary output file. |
| inputs / outputs | Filesystem path and string bytes enter; file write completes or stream assertion fails. |
| invariants | Binary mode preserves NUL/high bytes and exact serializer output; checks stream state after insertion. |
| ownership | Path/string are borrowed; ofstream owns the file handle only during the call. |
| failure | Open/write failure is reported by fixture check as runtime_error. |
| cost | Opens one file and writes the full string length. |
| Design | [docs/statistics.md](../../../../statistics.md), [docs/observability.md](../../../../observability.md), [Refactor.md](../../../../../Refactor.md) |

## B0004

[Lines 14–17](../../../../../tests/unit/statistics_report_fixture.hpp#L14); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
inline Report emit(const std::filesystem::path& dir,const char* label,Report report){
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Serialize one StatisticsExplanation to JSON and text artifacts and return the same owning report. |
| inputs / outputs | Directory, label, and Report-by-value enter; two files are emitted and Report value exits. |
| invariants | Uses public JSON/text encoders; does not alter the report or replace its owner/interval stamps. |
| ownership | Moves/copies an owning report; serialized strings and ofstreams are temporary. |
| failure | Serialization, allocation, or filesystem errors propagate. |
| cost | Runs both encoders and writes both full outputs; cost scales with report size, independent of native capture. |
| Design | [docs/statistics.md](../../../../statistics.md), [docs/observability.md](../../../../observability.md), [Refactor.md](../../../../../Refactor.md) |

## B0005

[Lines 18–18](../../../../../tests/unit/statistics_report_fixture.hpp#L18); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
inline void literal(const Report& report,const Database& db,std::uint64_t sequence){check(report.combined().has_value());facts(*report.combined(),db,sequence);}
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Require a report to contain a CombinedCapture matching literal fixture facts and sequence. |
| inputs / outputs | Borrowed Report, Database, and sequence enter; assertion-only result exits. |
| invariants | Requires combined report then delegates to combined binding and owner map oracle. |
| ownership | Report and Database are borrowed; their owners remain outside this helper. |
| failure | Missing combined value or failed facts assertion throws runtime_error. |
| cost | Scans fixed fixture relations and compares exact component distributions. |
| Design | [docs/statistics.md](../../../../statistics.md), [docs/observability.md](../../../../observability.md), [Refactor.md](../../../../../Refactor.md) |

## B0006

[Lines 19–21](../../../../../tests/unit/statistics_report_fixture.hpp#L19); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
inline void enqueue(QuerySession& session,PhysicalSetUpdate update){
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Enqueue one physical update as a typed TransportBatch on a QuerySession. |
| inputs / outputs | Borrowed session and owning PhysicalSetUpdate value enter; Admission result must be accepted. |
| invariants | Command identity/table/operation/row are retained in the batch; admission is checked before execution. |
| ownership | Batch owns/moves the update payload during enqueue; session retains its own queued input. |
| failure | Rejected admission throws fixture runtime_error; serialization/native errors propagate. |
| cost | Constructs one event and one batch, then performs one queue admission. |
| Design | [docs/statistics.md](../../../../statistics.md), [docs/observability.md](../../../../observability.md), [Refactor.md](../../../../../Refactor.md) |

## B0007

[Lines 22–25](../../../../../tests/unit/statistics_report_fixture.hpp#L22); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
inline void legacy_pair(const std::filesystem::path& dir,DeltaRuntime& runtime,const QuerySession& session){
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Emit legacy PlanExplanation JSON for both a DeltaRuntime and a QuerySession. |
| inputs / outputs | Output directory and borrowed live runtime/session enter; two legacy v2 JSON files are written. |
| invariants | Uses only PlanExplanation capture/write, so this helper does not imply C01 statistics-aware report behavior. |
| ownership | Runtime/session remain owners of engine state; JSON strings/files are transient. |
| failure | Capture, serialization, or file errors propagate. |
| cost | Per owner captures and serializes one plan explanation; no owner-state statistics request is added. |
| Design | [docs/statistics.md](../../../../statistics.md), [docs/observability.md](../../../../observability.md), [Refactor.md](../../../../../Refactor.md) |

## B0008

[Lines 26–26](../../../../../tests/unit/statistics_report_fixture.hpp#L26); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L26-L26:sha256:412ca345ccf75bf9c0806bce695be8de808b79984251a7a54d202cf6101dd451
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Close the recorded declaration scopes in statistics_report_fixture.hpp: namespace report_fixture. |
| inputs / outputs | Preceding namespace, type or initializer declarations in; completed lexical boundary out. |
| invariants | Brace-opening context is recorded in root-scope-context-v1.json. These are declaration/initializer boundaries, not an independent update, validation or recovery operation. |
| ownership | Enclosing objects and borrowed fields keep their declared ownership. This punctuation creates no new owner. |
| failure | Malformed scope syntax is a compile error. Any initializer/constructor failure belongs to the enclosing object declaration. |
| cost | No separate loop, guard or engine call is introduced by the delimiter; enclosing initialization and object lifetime still have their actual costs. |
| Design | [tests/unit/statistics_report_fixture.hpp](../../../../../tests/unit/statistics_report_fixture.hpp), [docs/statistics.md](../../../../statistics.md), [docs/code_review.md](../../../../code_review.md) |
