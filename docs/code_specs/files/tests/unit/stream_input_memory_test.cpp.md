# `tests/unit/stream_input_memory_test.cpp` — block usage map

[Source](../../../../../tests/unit/stream_input_memory_test.cpp) · [Source index](../../../README.md) · [Subsystem contracts](../../../subsystem_contracts.md) · [Reviewed primitives](../../../primitives.md)

Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection.

Snapshot SHA-256: `e659a4da9b328fc485e501fda7ef4c13b6aba3e3c4d875849790a717a01298f7`. 203 lines partitioned into 22 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [tests](../../../subsystem_contracts.md#tests). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/code_review.md](../../../../code_review.md), [docs/reference_fuzz.md](../../../../reference_fuzz.md), [docs/task_ledger.md](../../../../task_ledger.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–13](../../../../../tests/unit/stream_input_memory_test.cpp#L1) | Imports dependencies; declares namespace scope; declares aliases. |  · [reviewed contract](#b0001) |
| [B0002 · 14–14](../../../../../tests/unit/stream_input_memory_test.cpp#L14) | Callable definition: void check(bool ok,std::string_view message) | calls std::runtime_error, std::string; guard void check(bool ok,std::string_view message) {if(!ok)throw std::runtime_error(std::string(message))… · [reviewed contract](#b0002) |
| [B0003 · 15–16](../../../../../tests/unit/stream_input_memory_test.cpp#L15) | Callable definition: Catalog schema() | calls ; returns Catalog{1,{{@ ,{{@ ,ScalarType::int64},{@ ,ScalarType::string},{@ ,ScalarType::boolean}, · [reviewed contract](#b0003) |
| [B0004 · 17–17](../../../../../tests/unit/stream_input_memory_test.cpp#L17) | Callable definition: PhysicalPlan plan(bool indexed) | calls planner::lower_tree, schema, s04_runtime::options; returns planner::lower_tree(schema(),Query{{},{},{},false},FreeConnexTree{},indexed?s04_runtime::options():… · [reviewed contract](#b0004) |
| [B0005 · 18–18](../../../../../tests/unit/stream_input_memory_test.cpp#L18) | Callable definition: DeltaOptions runtime_options(std::uint64_t cap=64*1024*1024) | calls ; returns value · [reviewed contract](#b0005) |
| [B0006 · 19–20](../../../../../tests/unit/stream_input_memory_test.cpp#L19) | declares values/defaults or compile-time conditions. |  · [reviewed contract](#b0006) |
| [B0007 · 21–23](../../../../../tests/unit/stream_input_memory_test.cpp#L21) | Callable definition: std::string quote(std::string_view input) | calls ; returns result+@; 1 loop sites · [reviewed contract](#b0007) |
| [B0008 · 24–27](../../../../../tests/unit/stream_input_memory_test.cpp#L24) | declares types or opens a type body. |  · [reviewed contract](#b0008) |
| [B0009 · 28–56](../../../../../tests/unit/stream_input_memory_test.cpp#L28) | Callable definition: explicit Fixture(io::InputFormat format,std::size_t payload=8192) | calls std::string, emplace, Date::parse, Decimal::parse; growth emplace, insert, reserve; 1 loop sites · [reviewed contract](#b0009) |
| [B0010 · 57–57](../../../../../tests/unit/stream_input_memory_test.cpp#L57) | Closes surrounding scope/type. |  · [reviewed contract](#b0010) |
| [B0011 · 58–61](../../../../../tests/unit/stream_input_memory_test.cpp#L58) | Callable definition: bool same(const io::InputEventView& actual,const io::InputEvent& expected) | calls ; returns actual.update.sequence==expected.update.sequence && actual.update.table==expected.update.table && · [reviewed contract](#b0011) |
| [B0012 · 62–65](../../../../../tests/unit/stream_input_memory_test.cpp#L62) | Callable definition: void controller_only(const resource::MemoryAccount& account) | calls check_invariants, statistics, check, resource::MemoryAccount::control_bytes; guard check(usage.allocations==1 && usage.requested_bytes==resource::MemoryAccount::control_bytes(),"stre… · [reviewed contract](#b0012) |
| [B0013 · 66–69](../../../../../tests/unit/stream_input_memory_test.cpp#L66) | Callable definition: void accept(io::EventReader& reader,DeltaRuntime& runtime) | calls peek, check, begin_view, drain; guard const auto* event=reader.peek();check(event,"stream reader lost cached event");auto pending=runtime… · [reviewed contract](#b0013) |
| [B0014 · 70–96](../../../../../tests/unit/stream_input_memory_test.cpp#L70) | Callable definition: void ownership(bool indexed,io::InputFormat format) | calls fixture, runtime, plan, runtime_options; guard check(calls&gt;0 && calls==account.statistics().successful_allocations-before && reader-&gt;account().sta…; growth emplace · [reviewed contract](#b0014) |
| [B0015 · 97–119](../../../../../tests/unit/stream_input_memory_test.cpp#L97) | Callable definition: void limits(bool indexed,io::InputFormat format) | calls big, runtime, plan, runtime_options; guard const auto setup=runtime.plan().account().statistics().peak_requested_bytes;check(reader.peek()!=nu… · [reviewed contract](#b0015) |
| [B0016 · 120–151](../../../../../tests/unit/stream_input_memory_test.cpp#L120) | Callable definition: void faults(bool indexed,io::InputFormat format) | calls fixture, runtime, plan, runtime_options; guard if(construction)check(stream.tellg()==0 && !reader && account.statistics().current==baseline,"faile…; growth emplace; 2 loop sites · [reviewed contract](#b0016) |
| [B0017 · 152–154](../../../../../tests/unit/stream_input_memory_test.cpp#L152) | Callable definition: std::string replaced(std::string value,std::string_view from,std::string_view to) | calls find, check, replace, size; guard const auto at=value.find(from);check(at!=std::string::npos,"bad parser parity fixture");value.repla…; returns value · [reviewed contract](#b0017) |
| [B0018 · 155–157](../../../../../tests/unit/stream_input_memory_test.cpp#L155) | Callable definition: template&lt;class Action&gt; std::pair&lt;std::string,std::string&gt; diagnostic(Action&& action) | calls action, code, what; returns {}; {error.code(),error.what()} · [reviewed contract](#b0018) |
| [B0019 · 158–180](../../../../../tests/unit/stream_input_memory_test.cpp#L158) | Callable definition: void json_parity(bool indexed) | calls fixture, io::write_input_json, schema, find; guard check(native.first==reference.first,"native JSON parser error code differs from unchanged public co…; 1 loop sites · [reviewed contract](#b0019) |
| [B0020 · 181–193](../../../../../tests/unit/stream_input_memory_test.cpp#L181) | Callable definition: void retained_options(bool indexed) | calls fixture, QuerySession::create, plan, std::move; guard check(held-&gt;input.account().statistics().owner==account.statistics().owner && held-&gt;input.get().rel…; growth make_unique · [reviewed contract](#b0020) |
| [B0021 · 194–194](../../../../../tests/unit/stream_input_memory_test.cpp#L194) | Closes surrounding scope/type. | source comment (unverified): // namespace · [reviewed contract](#b0021) |
| [B0022 · 195–203](../../../../../tests/unit/stream_input_memory_test.cpp#L195) | Callable definition: int main() | calls ownership, limits, faults, json_parity; returns 1; 2 loop sites · [reviewed contract](#b0022) |

## B0001

[Lines 1–13](../../../../../tests/unit/stream_input_memory_test.cpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L1-L13:sha256:064d16655cc6021cc43779bbf8d93a20b4fc0c391f634dc4cc72fa3a4c9dd3cb
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Prepare stream_input_memory_test.cpp: include "crown/runtime/session.hpp", "crown/runtime/replay.hpp", "indexed_runtime_fixture.hpp", "index_allocation.hpp", &lt;array&gt;, &lt;iostream&gt;, &lt;optional&gt;, &lt;sstream&gt;, &lt;stdexcept&gt;; bind local aliases/name imports. |
| inputs / outputs | Compiler-visible dependencies, names and the recorded declarations in; declarations available to the following fixture/CLI/example definitions out. |
| invariants | Declarations are scoped to this source/header and its selected ABI. Included code has its own effects; names and editable fixture values do not confer proof, admission or publication authority. |
| ownership | Aliases/includes do not create a query owner. Pointers/references/views are non-owning. Containers own their elements, which can themselves be borrowed pointers or numeric IDs. Only documented owning shared-control handles retain controls; IDs/slot-handle values do not independently keep an arena/runtime alive. |
| failure | Missing headers, ill-formed names/types, failed static assertions or active #error directives stop compilation. No runtime rejection/rollback mechanism is implemented by aliases or function prototypes. |
| cost | Preprocessing and type/constraint instantiation cost compilation. Alias/prototype syntax does not invoke the declared operation; any included definitions keep their own initialization effects. |
| Design | [tests/unit/stream_input_memory_test.cpp](../../../../../tests/unit/stream_input_memory_test.cpp), [docs/ingestion.md](../../../../ingestion.md), [docs/code_review.md](../../../../code_review.md) |

## B0002

[Lines 14–14](../../../../../tests/unit/stream_input_memory_test.cpp#L14); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void check(bool ok,std::string_view message) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Turn one failed test predicate into a named exception. |
| inputs / outputs | Boolean predicate and borrowed message in; no value out. |
| invariants | Successful predicates return normally; no runtime error is translated. |
| ownership | Message is read only during the call; exception owns its copied diagnostic text. |
| failure | False throws std::runtime_error; allocation failure while constructing it propagates. |
| cost | One branch and, on failure, message construction. |
| Design | [tests/unit/stream_input_memory_test.cpp § lines 14-14](../../../../../tests/unit/stream_input_memory_test.cpp) |

## B0003

[Lines 15–16](../../../../../tests/unit/stream_input_memory_test.cpp#L15); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Catalog schema() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Build the five-column physical input catalog used by every stream fixture. |
| inputs / outputs | No inputs; Catalog with id:int64, text:string, flag:boolean, day:date and amount:decimal(38,2) out. |
| invariants | One table named input, version 1; amount is nonnullable binary-collated decimal. |
| ownership | Returned Catalog owns its names and column descriptors. |
| failure | Container allocation failures propagate. |
| cost | Fixed one-table/five-column metadata construction. |
| Design | [tests/unit/stream_input_memory_test.cpp § lines 15-16](../../../../../tests/unit/stream_input_memory_test.cpp), [include/crown/ir/model.hpp § lines 60-76](../../../../../include/crown/ir/model.hpp) |

## B0004

[Lines 17–17](../../../../../tests/unit/stream_input_memory_test.cpp#L17); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
PhysicalPlan plan(bool indexed) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Lower the fixed empty-query plan for either selector profile. |
| inputs / outputs | indexed flag in; PhysicalPlan out. |
| invariants | Uses the catalog above, empty Query/FreeConnexTree, and either s04_runtime::options() or default PhysicalOptions. Selector configuration is not a test execution result. |
| ownership | Returned plan owns lowered metadata; temporary schema/query/tree are local. |
| failure | Lowering or allocation errors propagate. |
| cost | One fixed lowering operation over one table and five columns; no timing bound. |
| Design | [tests/unit/stream_input_memory_test.cpp § lines 17-17](../../../../../tests/unit/stream_input_memory_test.cpp), [tests/support/indexed_runtime_fixture.hpp § lines 4-20](../../../../../tests/support/indexed_runtime_fixture.hpp), [include/crown/planner/lower.hpp § lines 1-16](../../../../../include/crown/planner/lower.hpp) |

## B0005

[Lines 18–18](../../../../../tests/unit/stream_input_memory_test.cpp#L18); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
DeltaOptions runtime_options(std::uint64_t cap=64*1024*1024) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Set the query memory ceiling used by stream runtime fixtures. |
| inputs / outputs | Requested byte cap in; DeltaOptions with physical.support.memory_limit_bytes set. |
| invariants | Only the support memory limit is overwritten. |
| ownership | Returned options value is local; runtime later receives a copy/move. |
| failure | No custom failure handling; value construction errors propagate. |
| cost | Scalar option assignment. |
| Design | [tests/unit/stream_input_memory_test.cpp § lines 18-18](../../../../../tests/unit/stream_input_memory_test.cpp), [include/crown/runtime/delta.hpp § lines 1-80](../../../../../include/crown/runtime/delta.hpp) |

## B0006

[Lines 19–20](../../../../../tests/unit/stream_input_memory_test.cpp#L19); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L19-L20:sha256:902af2f06b8e4988e6cb1b28df073142b240955863d8558c868042ec001aee7b
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Prepare stream_input_memory_test.cpp: declare constant fixture data. |
| inputs / outputs | Compiler-visible dependencies, names and the recorded declarations in; declarations available to the following fixture/CLI/example definitions out. The source span lists the exact member/global names, types and initial values; initializers run when the enclosing object/program/thread is initialized. |
| invariants | Declarations are scoped to this source/header and its selected ABI. Included code has its own effects; names and editable fixture values do not confer proof, admission or publication authority. |
| ownership | Aliases/includes do not create a query owner. Pointers/references/views are non-owning. Containers own their elements, which can themselves be borrowed pointers or numeric IDs. Only documented owning shared-control handles retain controls; IDs/slot-handle values do not independently keep an arena/runtime alive. |
| failure | Missing headers, ill-formed names/types, failed static assertions or active #error directives stop compilation. No runtime rejection/rollback mechanism is implemented by aliases or function prototypes. |
| cost | Preprocessing and type/constraint instantiation cost compilation. Alias/prototype syntax does not invoke the declared operation; any included definitions keep their own initialization effects. These constexpr data are fixed fixture constants; quota literals are grants, not reserved bytes or measured peaks. |
| Design | [tests/unit/stream_input_memory_test.cpp](../../../../../tests/unit/stream_input_memory_test.cpp), [docs/ingestion.md](../../../../ingestion.md), [docs/code_review.md](../../../../code_review.md) |

## B0007

[Lines 21–23](../../../../../tests/unit/stream_input_memory_test.cpp#L21); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::string quote(std::string_view input) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Encode one fixture field using CSV/legacy doubled-quote spelling. |
| inputs / outputs | Borrowed input bytes in; owning string wrapped in double quotes out. |
| invariants | Every embedded quote is duplicated; all other bytes, including NUL/newline/UTF-8, are copied. |
| ownership | Input is borrowed; output owns a separate copy. |
| failure | String allocation failures propagate. |
| cost | Scans and copies each input byte once. |
| Design | [tests/unit/stream_input_memory_test.cpp § lines 21-23](../../../../../tests/unit/stream_input_memory_test.cpp), [docs/ingestion.md § CSV and explicit legacy profiles, lines 91-113](../../../../ingestion.md) |

## B0008

[Lines 24–27](../../../../../tests/unit/stream_input_memory_test.cpp#L24); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L24-L27:sha256:5d683dbef2e8cd25dfdda11d0c9ba5f6b341c8286b2082debd8fb80c0c89df84
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Prepare stream_input_memory_test.cpp: declare fixture state/default initializers. |
| inputs / outputs | Compiler-visible dependencies, names and the recorded declarations in; declarations available to the following fixture/CLI/example definitions out. The source span lists the exact member/global names, types and initial values; initializers run when the enclosing object/program/thread is initialized. |
| invariants | Declarations are scoped to this source/header and its selected ABI. Included code has its own effects; names and editable fixture values do not confer proof, admission or publication authority. |
| ownership | Aliases/includes do not create a query owner. Pointers/references/views are non-owning. Containers own their elements, which can themselves be borrowed pointers or numeric IDs. Only documented owning shared-control handles retain controls; IDs/slot-handle values do not independently keep an arena/runtime alive. |
| failure | Missing headers, ill-formed names/types, failed static assertions or active #error directives stop compilation. No runtime rejection/rollback mechanism is implemented by aliases or function prototypes. Actual object construction and explicit initializers keep the failure contracts of their declared types/called helpers; this card supplies no extra rollback. |
| cost | Preprocessing and type/constraint instantiation cost compilation. Alias/prototype syntax does not invoke the declared operation; any included definitions keep their own initialization effects. Member/global initialization follows the shown C++ types and expressions when its enclosing object/program is constructed; owning containers can allocate. Default member declarations do not themselves instantiate a fixture. Copies and teardown follow the owning types. |
| Design | [tests/unit/stream_input_memory_test.cpp](../../../../../tests/unit/stream_input_memory_test.cpp), [docs/ingestion.md](../../../../ingestion.md), [docs/code_review.md](../../../../code_review.md) |

## B0009

[Lines 28–56](../../../../../tests/unit/stream_input_memory_test.cpp#L28); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
explicit Fixture(io::InputFormat format,std::size_t payload=8192) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Construct a two-record byte fixture and matching expected native events for one input profile. |
| inputs / outputs | InputFormat and text payload length in; InputOptions, encoded bytes, and two owning InputEvent expectations in the Fixture. |
| invariants | Covers JSONL, binary, CSV and five explicit legacy formats. Text profiles use a 120-byte source and 97-byte relation token; CSV header is permuted. Each row carries embedded NUL/newline/quote, UTF-8, bool, date and 38-digit decimal; offsets are sequence for wire formats, record-start byte positions for ordinary text, and 99+i for timestamp flags. |
| ownership | Fixture owns encoded bytes, options and expected rows/source names; temporary row/text values are moved or copied into them. |
| failure | Codec, Date/Decimal parse and allocation failures propagate. |
| cost | Builds exactly two full records; string work grows with payload and encoded form. The 131072-byte limit test passes a larger payload; no CPU-time claim. |
| Design | [tests/unit/stream_input_memory_test.cpp § lines 24-56](../../../../../tests/unit/stream_input_memory_test.cpp), [src/io/event_reader.cpp § lines 281-395](../../../../../src/io/event_reader.cpp), [docs/ingestion.md § CSV and explicit legacy profiles, lines 91-131](../../../../ingestion.md), [docs/ingestion.md § Reader acceptance and engine replay, lines 144-161](../../../../ingestion.md) |

## B0010

[Lines 57–57](../../../../../tests/unit/stream_input_memory_test.cpp#L57); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L57-L57:sha256:aa1d1a63390229c798347e83a0405441c9400035284ad168c1bf6cdf1d70a370
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Close the recorded declaration scopes in stream_input_memory_test.cpp: struct Fixture. |
| inputs / outputs | Preceding namespace, type or initializer declarations in; completed lexical boundary out. |
| invariants | Brace-opening context is recorded in root-scope-context-v1.json. These are declaration/initializer boundaries, not an independent update, validation or recovery operation. |
| ownership | Enclosing objects and borrowed fields keep their declared ownership. This punctuation creates no new owner. |
| failure | Malformed scope syntax is a compile error. Any initializer/constructor failure belongs to the enclosing object declaration. |
| cost | No separate loop, guard or engine call is introduced by the delimiter; enclosing initialization and object lifetime still have their actual costs. |
| Design | [tests/unit/stream_input_memory_test.cpp](../../../../../tests/unit/stream_input_memory_test.cpp), [docs/ingestion.md](../../../../ingestion.md), [docs/code_review.md](../../../../code_review.md) |

## B0011

[Lines 58–61](../../../../../tests/unit/stream_input_memory_test.cpp#L58); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
bool same(const io::InputEventView& actual,const io::InputEvent& expected) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Compare a borrowed decoded event with its owning expected fixture. |
| inputs / outputs | InputEventView and InputEvent in; equality result out. |
| invariants | Checks sequence, table, operation, complete typed row and optional source position. |
| ownership | Both inputs are borrowed for the call; no row or string is retained. |
| failure | View access/comparison errors propagate. |
| cost | Compares five scalar fields and the source-position value. |
| Design | [tests/unit/stream_input_memory_test.cpp § lines 58-61](../../../../../tests/unit/stream_input_memory_test.cpp), [include/crown/io/input_view.hpp § lines 1-39](../../../../../include/crown/io/input_view.hpp) |

## B0012

[Lines 62–65](../../../../../tests/unit/stream_input_memory_test.cpp#L62); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void controller_only(const resource::MemoryAccount& account) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Assert the native stream/session owners have released everything except the account controller. |
| inputs / outputs | Existing MemoryAccount handle in; no value out. |
| invariants | Checks account invariants and exactly one live allocation whose requested bytes equal control_bytes(). |
| ownership | Account is borrowed; this helper creates no owner. |
| failure | Mismatch throws test runtime_error; account diagnostic failures propagate. |
| cost | One explicit invariant scan plus current-account statistics; run only at fixture teardown. |
| Design | [tests/unit/stream_input_memory_test.cpp § lines 62-65](../../../../../tests/unit/stream_input_memory_test.cpp), [include/crown/resource/memory.hpp § lines 80-142](../../../../../include/crown/resource/memory.hpp), [src/resource/memory.cpp § lines 82-104](../../../../../src/resource/memory.cpp), [docs/query_memory.md § Query memory contract, lines 19-33](../../../../query_memory.md) |

## B0013

[Lines 66–69](../../../../../tests/unit/stream_input_memory_test.cpp#L66); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void accept(io::EventReader& reader,DeltaRuntime& runtime) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Apply the currently peeked stream update and acknowledge it only after engine commit. |
| inputs / outputs | EventReader and DeltaRuntime in; commits one physical event and consumes/discards its Epoch. |
| invariants | Requires a cached event; pending work is drained before commit. Commit, reader acknowledgement and epoch discard execute while replacement ordinary new is forbidden. |
| ownership | Reader/runtime are borrowed; PendingEpoch/Epoch are local RAII owners. |
| failure | Missing head fails through check; runtime errors propagate; failed commit leaves acknowledgement uncalled. |
| cost | One full pending drain for one event, then the fixed publication path. |
| Design | [tests/unit/stream_input_memory_test.cpp § lines 66-69](../../../../../tests/unit/stream_input_memory_test.cpp), [include/crown/io/ingest.hpp § lines 117-126](../../../../../include/crown/io/ingest.hpp), [src/io/event_reader.cpp § lines 457-484](../../../../../src/io/event_reader.cpp), [src/runtime/delta.cpp § lines 1582-1594](../../../../../src/runtime/delta.cpp), [tests/support/index_allocation.hpp § lines 11-45](../../../../../tests/support/index_allocation.hpp) |

## B0014

[Lines 70–96](../../../../../tests/unit/stream_input_memory_test.cpp#L70); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void ownership(bool indexed,io::InputFormat format) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Check stream constructor/decode requests, stable peek, accepted-progress copies and post-destruction lifetime for one profile. |
| inputs / outputs | Selector and format in; asserts request-owner identity, event values, counters, progress snapshots and final release. |
| invariants | For two rows: constructor and peek replacement-new counts equal successful allocations in the same account; repeated peek returns the same pointer; peek alone leaves accepted sequence 0 though records_read is 1; each commit precedes ack; progress snapshots are charged, retain prior values, and survive reader/runtime/session-scope destruction. EOF byte count equals fixture bytes. |
| ownership | Runtime plan supplies the one account; EventReader borrows the std::istream and retains native catalog/options/decoder/progress under that account. held/closed progress own account-funded copies after reader destruction; clearing them leaves only controller. |
| failure | Any request mismatch/value/progress drift fails by check; decode/engine/allocation exceptions propagate. |
| cost | One constructor, two decodes/commits, two progress copies and one EOF check. It uses a two-event stream, not a throughput probe. |
| Design | [tests/unit/stream_input_memory_test.cpp § lines 70-96](../../../../../tests/unit/stream_input_memory_test.cpp), [tests/support/index_allocation.hpp § lines 11-45](../../../../../tests/support/index_allocation.hpp), [include/crown/io/ingest.hpp § lines 95-137](../../../../../include/crown/io/ingest.hpp), [src/io/event_reader.cpp § lines 457-484](../../../../../src/io/event_reader.cpp), [src/io/input_progress.cpp § lines 45-88](../../../../../src/io/input_progress.cpp), [docs/ingestion.md § Reader acceptance and engine replay, lines 144-161](../../../../ingestion.md), [docs/ingestion.md § Native reader API and memory grant, lines 217-242](../../../../ingestion.md), [docs/query_memory.md § Account boundary, lines 19-55](../../../../query_memory.md) |

## B0015

[Lines 97–119](../../../../../tests/unit/stream_input_memory_test.cpp#L97); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void limits(bool indexed,io::InputFormat format) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Compare measured account peaks at an exact limit and one byte below for one large stream record. |
| inputs / outputs | Selector and format in; checks exact acceptance, one-under MemoryFailure, unchanged accepted/runtime prefix, explicit smaller reader recreation and controller-only release. |
| invariants | Fixture has two 131072-byte-payload rows. The cap is measured peak requested bytes from the same profile/format fixture; exact cap preserves that peak, cap-1 denies peek without accepting sequence/record or changing canonical engine state. A newly constructed small reader retries sequence 1 on the same original account limit. |
| ownership | Each runtime owns its original plan account; caller stream/fixture bytes remain external. Failed reader closes before retry; account handle outlives runtime for final release check. |
| failure | Only MemoryFailure(limit) is accepted as denial; wrong fault or changed prefix fails. Other errors propagate. |
| cost | Two fixture runs for calibration/exact cap and one cap-1 run; bounded by two records and one 131072-byte payload per row. Values are runtime-measured, not fixed byte constants or RSS. |
| Design | [tests/unit/stream_input_memory_test.cpp § lines 97-119](../../../../../tests/unit/stream_input_memory_test.cpp), [include/crown/resource/memory.hpp § lines 80-142](../../../../../include/crown/resource/memory.hpp), [src/resource/memory.cpp § lines 82-104,192-231](../../../../../src/resource/memory.cpp), [src/io/event_reader.cpp § lines 281-317,457-475](../../../../../src/io/event_reader.cpp), [docs/query_memory.md § Query memory contract, lines 19-33](../../../../query_memory.md), [docs/ingestion.md § Native reader API and memory grant, lines 217-242](../../../../ingestion.md) |

## B0016

[Lines 120–151](../../../../../tests/unit/stream_input_memory_test.cpp#L120); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void faults(bool indexed,io::InputFormat format) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Sweep constructor and first-peek replacement-new failure positions for one short stream fixture. |
| inputs / outputs | Selector and format in; requires failed positions and one successful endpoint separately for construction and decode. |
| invariants | For each phase fresh runtime/account/stream setup is outside the injected operation. Constructor bad_alloc must leave stream at byte zero, optional empty and account current unchanged. Peek bad_alloc must leave reader sticky-failed with no accepted sequence/record or runtime sequence; close releases decoder/options/source. Explicit recreation reads and commits the same first expected event. Sweep stops at first success or rejects after 512 positions. |
| ownership | Each trial owns its runtime, account handle, stream and optional reader. Recovery is explicit recreation on the same runtime/account; no new allowance is created. |
| failure | Only std::bad_alloc is classified as an injected failure; wrong state, sticky error code, missing failures or no successful point by 512 fail. |
| cost | At most 512 fresh fixtures per phase, each constructor or one peek; fault positions index replacement-new calls only, not malloc/system work or CPU time. |
| Design | [tests/unit/stream_input_memory_test.cpp § lines 120-151](../../../../../tests/unit/stream_input_memory_test.cpp), [tests/support/index_allocation.hpp § lines 11-45](../../../../../tests/support/index_allocation.hpp), [src/io/event_reader.cpp § lines 457-484,543-551](../../../../../src/io/event_reader.cpp), [include/crown/resource/memory.hpp § lines 80-142](../../../../../include/crown/resource/memory.hpp), [docs/ingestion.md § Reader acceptance and engine replay, lines 144-161](../../../../ingestion.md), [docs/query_memory.md § Boundaries, lines 35-55](../../../../query_memory.md) |

## B0017

[Lines 152–154](../../../../../tests/unit/stream_input_memory_test.cpp#L152); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::string replaced(std::string value,std::string_view from,std::string_view to) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Create one mutated JSON fixture by replacing its first marker. |
| inputs / outputs | Owning JSON text plus borrowed old/new text in; modified owning string out. |
| invariants | The marker must exist; only its first occurrence is replaced. |
| ownership | Input is passed by value and mutated locally; returned string owns the result. |
| failure | Absent marker throws test runtime_error through check; string growth failures propagate. |
| cost | One find and one replacement over fixture text. |
| Design | [tests/unit/stream_input_memory_test.cpp § lines 152-154](../../../../../tests/unit/stream_input_memory_test.cpp) |

## B0018

[Lines 155–157](../../../../../tests/unit/stream_input_memory_test.cpp#L155); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
template<class Action> std::pair<std::string,std::string> diagnostic(Action&& action) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Capture a CROWN Error as the exact code/message pair used for codec parity. |
| inputs / outputs | Callable in; pair of owning strings out. |
| invariants | Catches only crown::Error; successful action returns two empty strings and all other exception types escape. |
| ownership | Callable is forwarded and invoked; returned strings own code/message. |
| failure | Error string construction or non-CROWN exceptions propagate. |
| cost | One action invocation and two string copies only on CROWN Error. |
| Design | [tests/unit/stream_input_memory_test.cpp § lines 155-157](../../../../../tests/unit/stream_input_memory_test.cpp), [include/crown/api/error.hpp § lines 1-16](../../../../../include/crown/api/error.hpp) |

## B0019

[Lines 158–180](../../../../../tests/unit/stream_input_memory_test.cpp#L158); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void json_parity(bool indexed) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Compare native JSONL reader values/error codes with the unchanged owning JSON codec on directed documents. |
| inputs / outputs | Selector in; 19 JSON cases each produce either matching event values or matching error code, plus accepted-prefix checks. |
| invariants | Cases cover canonical and BOM documents, arbitrary field order, escaped and supplementary Unicode, wrong sequence/schema/operation/table, null/float/out-of-range integers, extra/duplicate fields, negative offset, invalid surrogate/UTF-8 and truncation. The public codec diagnostic code is compared; message text is not compared here. Malformed native heads leave sequence/runtime at zero. |
| ownership | Case strings/expected owning events are external test data; each EventReader owns one native account-bound decode while its stream/runtime are local. |
| failure | Parity mismatch or unexpected malformed acceptance fails; codec/parser/runtime errors are captured only when crown::Error. |
| cost | 19 iterations, each with one public decode and one native peek; bounded directed fixtures, no corpus-wide or timing claim. |
| Design | [tests/unit/stream_input_memory_test.cpp § lines 158-180](../../../../../tests/unit/stream_input_memory_test.cpp), [include/crown/io/ingest.hpp § lines 75-85](../../../../../include/crown/io/ingest.hpp), [src/io/ingest.cpp § lines 392-432](../../../../../src/io/ingest.cpp), [src/io/event_reader.cpp § lines 457-475](../../../../../src/io/event_reader.cpp), [src/io/native_decode.cpp § lines 262-265](../../../../../src/io/native_decode.cpp), [docs/ingestion.md § Version-1 JSONL event, lines 21-59](../../../../ingestion.md), [docs/ingestion.md § Native reader API and memory grant, lines 235-242](../../../../ingestion.md) |

## B0020

[Lines 181–193](../../../../../tests/unit/stream_input_memory_test.cpp#L181); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void retained_options(bool indexed) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Verify shared session run-context input options keep their original native owner after session destruction. |
| inputs / outputs | Selector in; QuerySession owns a stream-profile runtime; retained run-context input values are exported and checked after stop/drop/reset. |
| invariants | Uses legacy_relations with one token mapping, long source and null token. Input option owner ID equals the session runtime account owner. A zero-new copy succeeds; after session/runtime destruction exported values remain exact; clearing held context leaves only the account controller. |
| ownership | The session owns the stream/runtime. Shared const SessionRunContext and AccountedInputOptions outlive session, while account handle preserves the original controller. |
| failure | Creation/export mismatch fails; session, IO and allocation failures propagate. |
| cost | One session creation, one retained options copy/export and final release check; no full stream is consumed. |
| Design | [tests/unit/stream_input_memory_test.cpp § lines 181-193](../../../../../tests/unit/stream_input_memory_test.cpp), [include/crown/runtime/session.hpp § lines 180-270](../../../../../include/crown/runtime/session.hpp), [src/runtime/session.cpp § lines 396-413,1529-1531](../../../../../src/runtime/session.cpp), [include/crown/io/input_options.hpp § lines 1-45](../../../../../include/crown/io/input_options.hpp), [docs/ingestion.md § Native reader API and memory grant, lines 217-233](../../../../ingestion.md), [docs/query_memory.md § Boundaries, lines 35-55](../../../../query_memory.md) |

## B0021

[Lines 194–194](../../../../../tests/unit/stream_input_memory_test.cpp#L194); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L194-L194:sha256:533f16bca7d58f44b3103b92e3485d22cfbb34bbad5ea3f3fa3b5a9dcb24ec89
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Close the recorded declaration scopes in stream_input_memory_test.cpp: namespace (anonymous). |
| inputs / outputs | Preceding namespace, type or initializer declarations in; completed lexical boundary out. |
| invariants | Brace-opening context is recorded in root-scope-context-v1.json. These are declaration/initializer boundaries, not an independent update, validation or recovery operation. |
| ownership | Enclosing objects and borrowed fields keep their declared ownership. This punctuation creates no new owner. |
| failure | Malformed scope syntax is a compile error. Any initializer/constructor failure belongs to the enclosing object declaration. |
| cost | No separate loop, guard or engine call is introduced by the delimiter; enclosing initialization and object lifetime still have their actual costs. |
| Design | [tests/unit/stream_input_memory_test.cpp](../../../../../tests/unit/stream_input_memory_test.cpp), [docs/ingestion.md](../../../../ingestion.md), [docs/code_review.md](../../../../code_review.md) |

## B0022

[Lines 195–203](../../../../../tests/unit/stream_input_memory_test.cpp#L195); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
int main() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Run stream ownership, cap, fault, JSON parity and retained-option checks under both plan selectors. |
| inputs / outputs | No arguments; returns 0 after all checks, 1 after caught std::exception. |
| invariants | For each of two selectors, calls ownership/limits/faults for all eight input profiles, then JSON parity and retained options once. This is source scope only; the packet makes no execution claim. |
| ownership | Fixtures/runtimes are owned by called helpers and destruct before main returns. |
| failure | Catches std::exception, prints message and returns 1; otherwise prints a summary and returns 0. |
| cost | 16 selector/profile combinations for three checks plus two parity/options calls; fault sweeps have per-phase cap 512. No elapsed-time threshold. |
| Design | [tests/unit/stream_input_memory_test.cpp § lines 195-203](../../../../../tests/unit/stream_input_memory_test.cpp), [tests/support/indexed_runtime_fixture.hpp § lines 4-20](../../../../../tests/support/indexed_runtime_fixture.hpp) |
