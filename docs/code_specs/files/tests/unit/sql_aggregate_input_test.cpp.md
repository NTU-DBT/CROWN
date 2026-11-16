# `tests/unit/sql_aggregate_input_test.cpp` — block usage map

[Source](../../../../../tests/unit/sql_aggregate_input_test.cpp) · [Source index](../../../README.md) · [Subsystem contracts](../../../subsystem_contracts.md) · [Reviewed primitives](../../../primitives.md)

Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection.

Snapshot SHA-256: `2528690ca493ed269fedd1c3c2b709f273a17b5336e277d4aef4b8520b0973ca`. 175 lines partitioned into 16 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [tests](../../../subsystem_contracts.md#tests). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/code_review.md](../../../../code_review.md), [docs/reference_fuzz.md](../../../../reference_fuzz.md), [docs/task_ledger.md](../../../../task_ledger.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–14](../../../../../tests/unit/sql_aggregate_input_test.cpp#L1) | Imports dependencies; declares namespace scope; declares aliases; declares values/defaults or compile-time conditions. |  · [reviewed contract](#b0001) |
| [B0002 · 15–15](../../../../../tests/unit/sql_aggregate_input_test.cpp#L15) | Callable definition: template&lt;class T&gt; concept RvalueView=requires(const T&& value) | calls view · [reviewed contract](#b0002) |
| [B0003 · 16–17](../../../../../tests/unit/sql_aggregate_input_test.cpp#L16) | declares callable signatures; declares values/defaults or compile-time conditions. | guard static_assert(!RvalueView&lt;io::SqlAggregateJsonCommand&gt;); · [reviewed contract](#b0003) |
| [B0004 · 18–24](../../../../../tests/unit/sql_aggregate_input_test.cpp#L18) | Callable definition: frontend::SqlAggregateProgram bind_program() | calls frontend::bind_sql_aggregate, assert, std::move; guard assert(std::holds_alternative&lt;frontend::SqlAggregateProgram&gt;(bound));return std::get&lt;frontend::SqlA…; returns std::get&lt;frontend::SqlAggregateProgram&gt;(std::move(bound)) · [reviewed contract](#b0004) |
| [B0005 · 25–31](../../../../../tests/unit/sql_aggregate_input_test.cpp#L25) | Callable definition: Json record(const frontend::SqlAggregateProgram& program,std::uint64_t sequence=1) | calls identity, std::string, begin, end; returns {{@ ,1},{@ ,std::string(binding.begin(),binding.end())},{@ ,sequence}, · [reviewed contract](#b0005) |
| [B0006 · 32–34](../../../../../tests/unit/sql_aggregate_input_test.cpp#L32) | Callable definition: template&lt;class Action&gt; void error(Action action,std::string_view expected={}) | calls action, empty, assert, code; guard bool refused=false;try {action();}catch(const Error& failure) {refused=true;if(!expected.empty())as… · [reviewed contract](#b0006) |
| [B0007 · 35–36](../../../../../tests/unit/sql_aggregate_input_test.cpp#L35) | Explanatory comments or spacing. | source comment (unverified): // A returned command survives reader/stream/DOM destruction and later decoding; · [reviewed contract](#b0007) |
| [B0008 · 37–59](../../../../../tests/unit/sql_aggregate_input_test.cpp#L37) | Callable definition: void ownership(const frontend::SqlAggregateProgram& schema) | calls resource::MemoryAccount::create, statistics, record, dump; guard saved=reader.next();assert(saved);const auto one=saved-&gt;view();assert(one.reader==ar::ReaderPositio…; source comment (unverified): // A returned command survives reader/stream/DOM destruction and later decoding; · [reviewed contract](#b0008) |
| [B0009 · 60–89](../../../../../tests/unit/sql_aggregate_input_test.cpp#L60) | Callable definition: void malformed(const frontend::SqlAggregateProgram& schema) | calls resource::MemoryAccount::create, record, push_back, erase; guard error(\[&\]{(void)reader.next();});assert(reader.requires_reopen());; growth push_back; 4 loop sites · [reviewed contract](#b0009) |
| [B0010 · 90–122](../../../../../tests/unit/sql_aggregate_input_test.cpp#L90) | Callable definition: void limits(const frontend::SqlAggregateProgram& schema) | calls resource::MemoryAccount::create, record, erase, dump; guard assert(reader.next() && !reader.next());; growth push_back; 1 loop sites; source comment (unverified): // Remove TEXT to isolate the tagged scalar cap before DATE/DECIMAL parsing. · [reviewed contract](#b0010) |
| [B0011 · 123–125](../../../../../tests/unit/sql_aggregate_input_test.cpp#L123) | Explanatory comments or spacing. | source comment (unverified): // Deny every observed C++ allocation in constructor/decode. DOM destruction can · [reviewed contract](#b0011) |
| [B0012 · 126–156](../../../../../tests/unit/sql_aggregate_input_test.cpp#L126) | Callable definition: void allocation_cuts(const frontend::SqlAggregateProgram& schema) | calls resource::MemoryAccount::create, record, dump, statistics; guard {std::istringstream stream(line);s04_alloc::Scope count;{Reader reader(stream,account,schema);asser…; returns receiving.statistics().peak_requested_bytes; 1 loop sites; source comment (unverified): // Deny every observed C++ allocation in constructor/decode. DOM destruction can · [reviewed contract](#b0012) |
| [B0013 · 157–158](../../../../../tests/unit/sql_aggregate_input_test.cpp#L157) | Explanatory comments or spacing. | source comment (unverified): // Integration fixture only: persist a real Input or Commit through public APIs, · [reviewed contract](#b0013) |
| [B0014 · 159–168](../../../../../tests/unit/sql_aggregate_input_test.cpp#L159) | Callable definition: void leave(int argc,char** argv) | calls assert, resource::MemoryAccount::create, fill, ar::Session::recover_into; guard assert(argc==5 \|\| argc==6);const auto account=resource::MemoryAccount::create(256ULL*1024*1024);; source comment (unverified): // Integration fixture only: persist a real Input or Commit through public APIs, · [reviewed contract](#b0014) |
| [B0015 · 169–169](../../../../../tests/unit/sql_aggregate_input_test.cpp#L169) | Closes surrounding scope/type. | source comment (unverified): // namespace · [reviewed contract](#b0015) |
| [B0016 · 170–175](../../../../../tests/unit/sql_aggregate_input_test.cpp#L170) | Callable definition: int main(int argc,char** argv) | calls leave, bind_program, ownership, malformed; returns 0; 0 · [reviewed contract](#b0016) |

## B0001

[Lines 1–14](../../../../../tests/unit/sql_aggregate_input_test.cpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L1-L14:sha256:2e8ebc7ccf10ee436bfc92c9c68f79d4b7c9d9b5ef5a60cea7149966fcb4f554
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Prepare sql_aggregate_input_test.cpp: include "crown/io/sql_aggregate_input.hpp", "crown/io/document.hpp", "crown/api/error.hpp", "sql_aggregate_session_fixture.hpp", "index_allocation.hpp", &lt;fstream&gt;, &lt;iostream&gt;, &lt;sstream&gt;; bind local aliases/name imports. |
| inputs / outputs | Compiler-visible dependencies, names and the recorded declarations in; declarations available to the following fixture/CLI/example definitions out. |
| invariants | Declarations are scoped to this source/header and its selected ABI. Included code has its own effects; names and editable fixture values do not confer proof, admission or publication authority. |
| ownership | Aliases/includes do not create a query owner. Pointers/references/views are non-owning. Containers own their elements, which can themselves be borrowed pointers or numeric IDs. Only documented owning shared-control handles retain controls; IDs/slot-handle values do not independently keep an arena/runtime alive. |
| failure | Missing headers, ill-formed names/types, failed static assertions or active #error directives stop compilation. No runtime rejection/rollback mechanism is implemented by aliases or function prototypes. |
| cost | Preprocessing and type/constraint instantiation cost compilation. Alias/prototype syntax does not invoke the declared operation; any included definitions keep their own initialization effects. |
| Design | [tests/unit/sql_aggregate_input_test.cpp](../../../../../tests/unit/sql_aggregate_input_test.cpp), [docs/aggregates.md](../../../../aggregates.md), [docs/code_review.md](../../../../code_review.md) |

## B0002

[Lines 15–15](../../../../../tests/unit/sql_aggregate_input_test.cpp#L15); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
template<class T> concept RvalueView=requires(const T&& value){std::move(value).view();};
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Define a compile-time probe for whether an rvalue owner exposes view(). |
| inputs / outputs | The concept is instantiated by static_assert for SqlAggregateJsonCommand; adjacent assertions also check Reader is noncopyable and nothrow movable. |
| invariants | The compile-time checks protect borrowed-view lifetime and reader ownership traits. They say nothing about runtime decoding or all command traits beyond the asserted expressions. |
| ownership | The assertions allocate nothing and create no runtime state. |
| failure | A changed API that permits the probed rvalue call or changes asserted Reader traits makes compilation fail; this test does not exercise the thrown moved-from path. |
| cost | Compile-time type checking only; no runtime cost or native behavior claim. |
| Design | [docs/sql_aggregate_input.md §One atomic JSONL command](../../../../sql_aggregate_input.md), [docs/code_review.md §Coverage and retained evidence](../../../../code_review.md) |

## B0003

[Lines 16–17](../../../../../tests/unit/sql_aggregate_input_test.cpp#L16); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L16-L17:sha256:db18a0dd81a561522d3bc8659f26ed3dd4adbe5882fa45114a85b7c6916b5224
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Prepare sql_aggregate_input_test.cpp: require 2 compile-time type/ABI conditions. |
| inputs / outputs | Compiler-visible dependencies, names and the recorded declarations in; declarations available to the following fixture/CLI/example definitions out. |
| invariants | Declarations are scoped to this source/header and its selected ABI. Included code has its own effects; names and editable fixture values do not confer proof, admission or publication authority. Static assertions establish only their listed C++ type properties, not query/result/recovery correctness or test execution. |
| ownership | Aliases/includes do not create a query owner. Pointers/references/views are non-owning. Containers own their elements, which can themselves be borrowed pointers or numeric IDs. Only documented owning shared-control handles retain controls; IDs/slot-handle values do not independently keep an arena/runtime alive. |
| failure | Missing headers, ill-formed names/types, failed static assertions or active #error directives stop compilation. No runtime rejection/rollback mechanism is implemented by aliases or function prototypes. |
| cost | Preprocessing and type/constraint instantiation cost compilation. Alias/prototype syntax does not invoke the declared operation; any included definitions keep their own initialization effects. |
| Design | [tests/unit/sql_aggregate_input_test.cpp](../../../../../tests/unit/sql_aggregate_input_test.cpp), [docs/aggregates.md](../../../../aggregates.md), [docs/code_review.md](../../../../code_review.md) |

## B0004

[Lines 18–24](../../../../../tests/unit/sql_aggregate_input_test.cpp#L18); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
frontend::SqlAggregateProgram bind_program() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Build one genuine frozen-bindable SQL aggregate fixture with representative physical scalar columns. |
| inputs / outputs | Catalog table r has nullable string g, int64 id, bool flag, date d, decimal(6,2) n and nullable int64 x. It binds SELECT g,COUNT(*),SUM(id) FROM r GROUP BY g and returns the program variant. |
| invariants | SUM uses admitted integer id; date and decimal appear as physical source cells rather than new aggregate expression support. The fixture’s schema version and source name are fixed for downstream records. |
| ownership | Catalog, bind result and returned program are local owning values; no global schema is shared. |
| failure | Binding not producing SqlAggregateProgram fails the assert; this helper does not test rejection diagnostics for unsupported SQL. |
| cost | One small cold catalog bind per test main. It is fixture setup, not a compile/runtime benchmark. |
| Design | [docs/aggregates.md §SQL and numeric contract](../../../../aggregates.md), [docs/sql_aggregate_input.md §One atomic JSONL command](../../../../sql_aggregate_input.md), [docs/aggregates.md §Logical input and publication](../../../../aggregates.md) |

## B0005

[Lines 25–31](../../../../../tests/unit/sql_aggregate_input_test.cpp#L25); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Json record(const frontend::SqlAggregateProgram& program,std::uint64_t sequence=1) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Construct a valid JSONL record tied to the test program’s exact binding identity. |
| inputs / outputs | Builds schema_version 1, binding hash, supplied sequence, one complete six-cell row replacement (before 0, after 3) and source position; date and decimal use one-key tags. |
| invariants | The record follows physical catalog column order and includes TEXT long enough to exercise owned non-small-string storage. It is a deterministic fixture builder, not a general encoder or oracle. |
| ownership | Returns an owning Json object; its values belong to the test fixture until serialized or destroyed. |
| failure | No decoder failure is handled here; malformed fixtures are modified in malformed() and limits(). |
| cost | Constructs a small test DOM and string values; its allocation is test setup outside the reader account. |
| Design | [docs/sql_aggregate_input.md §One atomic JSONL command](../../../../sql_aggregate_input.md), [docs/sql_aggregate_input.md §Ownership, failure and cost](../../../../sql_aggregate_input.md), [docs/aggregates.md §SQL and numeric contract](../../../../aggregates.md), [schemas/sql-aggregate-input-v1.schema.json](../../../../../schemas/sql-aggregate-input-v1.schema.json) |

## B0006

[Lines 32–34](../../../../../tests/unit/sql_aggregate_input_test.cpp#L32); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
template<class Action> void error(Action action,std::string_view expected={}) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Assert that an action throws crown::api::Error and optionally has one exact code. |
| inputs / outputs | Invokes the action, catches Error, optionally compares code(), and asserts a refusal occurred. |
| invariants | When expected is empty the helper verifies only Error type, not a particular code or message. Other exception types propagate. |
| ownership | The action and expected code are borrowed for the call; failure exception is owned by the catch scope. |
| failure | No Error, wrong exact code or an unexpected exception fails/escapes the test. This helper does not check state unless the caller adds assertions. |
| cost | One action invocation and exception-path work when the expected failure occurs. |
| Design | [docs/code_review.md §Coverage and retained evidence](../../../../code_review.md), [docs/sql_aggregate_input.md §Ownership, failure and cost](../../../../sql_aggregate_input.md) |

## B0007

[Lines 35–36](../../../../../tests/unit/sql_aggregate_input_test.cpp#L35); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L35-L36:sha256:da67649e916c3e5d45b1ecfbf5dd320d75310f46979bf2f154e4e27d07ee0ea6
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Explain the adjacent source contract: A returned command survives reader/stream/DOM destruction and later decoding; exact LF/CRLF byte counters are independent of command/native frontiers. |
| inputs / outputs | Human-readable source note in; no executable output or checked receipt. |
| invariants | This comment states context or a limitation. It does not itself enforce or prove the described behavior; use the adjacent implementation and its scoped contract. |
| ownership | Source text only; no object or resource lifetime is created. |
| failure | No runtime failure path in this comment; source encoding/comment syntax still belongs to compilation. |
| cost | No runtime operations from the comment. Any work described in the note belongs to the adjacent operation. |
| Design | [tests/unit/sql_aggregate_input_test.cpp](../../../../../tests/unit/sql_aggregate_input_test.cpp), [docs/aggregates.md](../../../../aggregates.md), [docs/code_review.md](../../../../code_review.md) |

## B0008

[Lines 37–59](../../../../../tests/unit/sql_aggregate_input_test.cpp#L37); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void ownership(const frontend::SqlAggregateProgram& schema) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Exercise command borrow ownership, move behavior, line-position accounting and clean EOF on a finite fixture. |
| inputs / outputs | Reads a CRLF record and a no-replacement LF record, checks exact logical ReaderPosition, repeated EOF, command/view fields, TEXT/date/decimal values, move-from invalid state and account-current restoration after owners die. |
| invariants | The first returned command remains usable after reader, stream and temporary Json objects leave scope; views must remain tied to the moved command owner. Sequence and reader frontiers are transport metadata, independent of Session/native frontiers. |
| ownership | Commands own their backing buffers and retain the receiving account; the stream and fixture Json remain local and are not retained. The measured baseline/current assertions bracket all command owners. |
| failure | Assertions fail the test on incorrect ownership/value/position; moved-from view must throw invalid_input_state. The case does not induce arbitrary allocator refusal. |
| cost | Two small records, bounded account statistics and one complete command inspection; no repeated-row or whole-engine scan. |
| Design | [docs/sql_aggregate_input.md §Ownership, failure and cost](../../../../sql_aggregate_input.md), [docs/query_memory.md §Boundaries](../../../../query_memory.md), [docs/sql_aggregate_records.md §Wire contract](../../../../sql_aggregate_records.md), [docs/code_review.md §Coverage and retained evidence](../../../../code_review.md) |

## B0009

[Lines 60–89](../../../../../tests/unit/sql_aggregate_input_test.cpp#L60); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void malformed(const frontend::SqlAggregateProgram& schema) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Check representative malformed envelopes, sequence/binding/schema/row/source values, malformed JSON and bad stream state. |
| inputs / outputs | Mutates finite fixtures for missing/extra keys, unsupported schema, wrong/negative sequence, wrong binding, malformed replacement/table/schema version/weights, NUL/type/range/date/decimal/arity and source-position errors; also checks blank, trailing, duplicate-key JSON and badbit input. |
| invariants | The test requires an Error and a poisoned reader for the per-record cases, then checks retry and position report invalid_input_state. Only selected expected codes are exact: io_error and invalid_input_state; most malformed fixture codes are intentionally not asserted. |
| ownership | Each case owns its input stream, reader and Json fixture; account-backed state unwinds before the next case. |
| failure | Unexpected success or failure to poison/reopen fails assertions; the finite list is representative coverage, not proof for all parser inputs or all Error categories. |
| cost | Runs a fixed vector of small malformed documents and one bad-stream case. JSON construction and iteration are test costs outside the native query path. |
| Design | [docs/sql_aggregate_input.md §One atomic JSONL command](../../../../sql_aggregate_input.md), [docs/sql_aggregate_input.md §Ownership, failure and cost](../../../../sql_aggregate_input.md), [src/io/document.cpp §read_json definition, lines 19–20](../../../../../src/io/document.cpp), [docs/code_review.md §Coverage and retained evidence](../../../../code_review.md), [schemas/sql-aggregate-input-v1.schema.json](../../../../../schemas/sql-aggregate-input-v1.schema.json) |

## B0010

[Lines 90–122](../../../../../tests/unit/sql_aggregate_input_test.cpp#L90); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void limits(const frontend::SqlAggregateProgram& schema) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Exercise exact and one-under JSONL admission caps plus zero-input and resumed progress boundaries. |
| inputs / outputs | Sets exact record/total bytes, records, replacement/cell and scalar field caps; lowers each relevant cap; isolates tagged date/decimal lengths; accepts empty EOF with zero byte/record caps; rejects an invalid origin; resumes sequence 8 from logged 7 at origin (1000,7). |
| invariants | The exact CRLF fixture includes both terminator bytes in cumulative bytes and excludes them from record_bytes. Resume position is computed from the original byte origin and records; no stream tellg/read-ahead value is used. |
| ownership | Reader/input fixtures are local; each cap case creates a fresh reader and account. Account ownership is not a claim that parser DOM is accounted. |
| failure | Over-cap cases expect resource_limit, invalid origin expects invalid_input_progress. These are deterministic boundary samples, not combinatorial proof of every option interaction. |
| cost | A fixed number of tiny records are decoded once per configured case; cost is fixture setup plus parser/reader work. |
| Design | [docs/sql_aggregate_input.md §One atomic JSONL command](../../../../sql_aggregate_input.md), [docs/sql_aggregate_input.md §Ownership, failure and cost](../../../../sql_aggregate_input.md), [apps/crown/aggregate.cpp §help limits and resume text, lines 71–85](../../../../../apps/crown/aggregate.cpp), [docs/query_memory.md §Boundaries](../../../../query_memory.md) |

## B0011

[Lines 123–125](../../../../../tests/unit/sql_aggregate_input_test.cpp#L123); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L123-L125:sha256:df1559d9c1e007d0aab1d60c912c4065d78b00612e6fa403b354ae1080c9a709
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Explain the adjacent source contract: Deny every observed C++ allocation in constructor/decode. DOM destruction can fall back without propagating allocation failure: require a correct command or an exception, and exact receiving-account restoration in either case. |
| inputs / outputs | Human-readable source note in; no executable output or checked receipt. |
| invariants | This comment states context or a limitation. It does not itself enforce or prove the described behavior; use the adjacent implementation and its scoped contract. |
| ownership | Source text only; no object or resource lifetime is created. |
| failure | No runtime failure path in this comment; source encoding/comment syntax still belongs to compilation. |
| cost | No runtime operations from the comment. Any work described in the note belongs to the adjacent operation. |
| Design | [tests/unit/sql_aggregate_input_test.cpp](../../../../../tests/unit/sql_aggregate_input_test.cpp), [docs/aggregates.md](../../../../aggregates.md), [docs/code_review.md](../../../../code_review.md) |

## B0012

[Lines 126–156](../../../../../tests/unit/sql_aggregate_input_test.cpp#L126); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void allocation_cuts(const frontend::SqlAggregateProgram& schema) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Sweep every counted covered C++ operator-new attempt in one reader construction/decode and inspect both refusal propagation and cleanup fallback. |
| inputs / outputs | First counts attempts across construction and next(). For each cut, requires the cut to trigger and accepts either propagated bad_alloc or a correct command/view after JSON cleanup fallback; every path must restore receiving-account current bytes exactly. It also measures peak_requested_bytes at the exact accepted cap and requires one byte less to raise MemoryFailure. |
| invariants | The replacement hook counts/denies covered C++ operator-new attempts only; it is not malloc denial and does not make JSON DOM/workspace part of the native account. A successful cut is accepted only after verifying the decoded sequence, replacement and long TEXT. |
| ownership | Each iteration uses a fresh stream and Scope; the MemoryAccount is checked after owners unwind. The helper override is test-executable-only; production code is unchanged. |
| failure | A cut may propagate bad_alloc or be absorbed by JSON destructor fallback while returning the correct command. Requiring every cut was triggered and exact account restoration checks cleanup, not universal failure safety for arbitrary external libraries. |
| cost | One baseline pass, one iteration per observed operator-new call, then exact-cap and one-under-cap passes. Reports observed counters/peak when run; no RSS, libc malloc count or DOM-wide memory total is inferred. |
| Design | [docs/sql_aggregate_input.md §Ownership, failure and cost](../../../../sql_aggregate_input.md), [docs/query_memory.md §Boundaries](../../../../query_memory.md), [tests/support/index_allocation.hpp §s04_alloc::Scope and operator new replacements, lines 11–58](../../../../../tests/support/index_allocation.hpp), [docs/code_review.md §Coverage and retained evidence](../../../../code_review.md) |

## B0013

[Lines 157–158](../../../../../tests/unit/sql_aggregate_input_test.cpp#L157); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L157-L158:sha256:c15bb27c73d103a096dc8130280cf90aaeb6894c3596bc8dd5db790137d9596d
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Explain the adjacent source contract: Integration fixture only: persist a real Input or Commit through public APIs, then release locks so the actual CLI must resume it without duplicate logging. |
| inputs / outputs | Human-readable source note in; no executable output or checked receipt. |
| invariants | This comment states context or a limitation. It does not itself enforce or prove the described behavior; use the adjacent implementation and its scoped contract. |
| ownership | Source text only; no object or resource lifetime is created. |
| failure | No runtime failure path in this comment; source encoding/comment syntax still belongs to compilation. |
| cost | No runtime operations from the comment. Any work described in the note belongs to the adjacent operation. |
| Design | [tests/unit/sql_aggregate_input_test.cpp](../../../../../tests/unit/sql_aggregate_input_test.cpp), [docs/aggregates.md](../../../../aggregates.md), [docs/code_review.md](../../../../code_review.md) |

## B0014

[Lines 159–168](../../../../../tests/unit/sql_aggregate_input_test.cpp#L159); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void leave(int argc,char** argv) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Create a deterministic recovery fixture by persisting a pending Input or a nonrejected Commit through the public Session API. |
| inputs / outputs | Recovers a real Session, seeks the JSONL stream to its logged ReaderPosition, decodes one command with the public reader, calls Session::log(), and for --leave-output calls decide() and asserts it was not rejected. Returning releases locks for a later CLI invocation. |
| invariants | This exercises public durable boundaries with a genuine program/session. It is a normal helper return/process handoff, not an injected crash, EIO, power-loss or arbitrary write cut. It does not deliver the committed spool in this process. |
| ownership | Session, account, stream, reader and command are local owners; Session owns durable files/locks only for the helper lifetime. The command borrow is passed synchronously to log(). |
| failure | Fixture assumptions are assertions; Session/File/Memory failures propagate to main’s error handling. Whether an Input or output remains pending is asserted by the integration harness after handoff. |
| cost | One command is framed/logged and optionally decided; cold recovery/replay and CLI resume costs belong to the separately invoked process. |
| Design | [docs/sql_aggregate_session.md §State and command usage](../../../../sql_aggregate_session.md), [docs/sql_aggregate_session.md §Recovery and failure boundaries](../../../../sql_aggregate_session.md), [include/crown/recovery/sql_aggregate_session.hpp §Session log/decide/deliver declarations, lines 81–85](../../../../../include/crown/recovery/sql_aggregate_session.hpp), [src/recovery/sql_aggregate_session.cpp §Session log/decide implementation, lines 128–153](../../../../../src/recovery/sql_aggregate_session.cpp), [apps/crown/aggregate.cpp §run reader/session loop, lines 167–190](../../../../../apps/crown/aggregate.cpp), [docs/sql_aggregate_input.md §Ownership, failure and cost](../../../../sql_aggregate_input.md) |

## B0015

[Lines 169–169](../../../../../tests/unit/sql_aggregate_input_test.cpp#L169); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L169-L169:sha256:533f16bca7d58f44b3103b92e3485d22cfbb34bbad5ea3f3fa3b5a9dcb24ec89
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Close the recorded declaration scopes in sql_aggregate_input_test.cpp: namespace (anonymous). |
| inputs / outputs | Preceding namespace, type or initializer declarations in; completed lexical boundary out. |
| invariants | Brace-opening context is recorded in root-scope-context-v1.json. These are declaration/initializer boundaries, not an independent update, validation or recovery operation. |
| ownership | Enclosing objects and borrowed fields keep their declared ownership. This punctuation creates no new owner. |
| failure | Malformed scope syntax is a compile error. Any initializer/constructor failure belongs to the enclosing object declaration. |
| cost | No separate loop, guard or engine call is introduced by the delimiter; enclosing initialization and object lifetime still have their actual costs. |
| Design | [tests/unit/sql_aggregate_input_test.cpp](../../../../../tests/unit/sql_aggregate_input_test.cpp), [docs/aggregates.md](../../../../aggregates.md), [docs/code_review.md](../../../../code_review.md) |

## B0016

[Lines 170–175](../../../../../tests/unit/sql_aggregate_input_test.cpp#L170); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
int main(int argc,char** argv) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Dispatch either the helper’s one-command durable fixture mode or the finite reader unit cases. |
| inputs / outputs | With extra arguments calls leave() and returns; otherwise binds the fixture program and runs ownership, malformed, limits and allocation_cuts. std::exception is presented on stderr with status 1. |
| invariants | Successful process exit only says this test executable completed its assertions for that invocation. This source review does not claim that it was executed, and its finite cases are not proof of all inputs. |
| ownership | All test resources are scoped under the selected helper/test call; process exit releases remaining fixture owners. |
| failure | Unexpected exceptions or assertions fail the test; expected Error handling is local to case helpers. |
| cost | Runs bounded deterministic unit fixtures; allocation_cuts deliberately multiplies work by observed operator-new attempt count. |
| Design | [docs/code_review.md §Coverage and retained evidence](../../../../code_review.md), [docs/sql_aggregate_input.md §Ownership, failure and cost](../../../../sql_aggregate_input.md) |
