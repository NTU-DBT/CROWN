# `apps/crown/aggregate.cpp` — block usage map

[Source](../../../../../apps/crown/aggregate.cpp) · [Source index](../../../README.md) · [Subsystem contracts](../../../subsystem_contracts.md) · [Reviewed primitives](../../../primitives.md)

Demonstrate a concrete public workflow and executable invocation using installed/native CROWN interfaces.

Snapshot SHA-256: `3aca9ae36a335b75b1249e4bc5677eb26f45cf373ec98b5359147542a52d7758`. 277 lines partitioned into 21 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [examples](../../../subsystem_contracts.md#examples). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/cli.md](../../../../cli.md), [docs/native_build.md](../../../../native_build.md), [docs/measurement.md](../../../../measurement.md), [docs/ranking_evaluation.md](../../../../ranking_evaluation.md), [docs/reoptimization.md](../../../../reoptimization.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–22](../../../../../apps/crown/aggregate.cpp#L1) | Imports dependencies; declares namespace scope; declares aliases; declares values/defaults or compile-time conditions. |  · [reviewed contract](#b0001) |
| [B0002 · 23–27](../../../../../apps/crown/aggregate.cpp#L23) | Callable definition: std::uint64_t number(std::string_view value) | calls std::from_chars, data, size, Error; returns result · [reviewed contract](#b0002) |
| [B0003 · 28–31](../../../../../apps/crown/aggregate.cpp#L28) | Callable definition: std::size_t size(std::uint64_t n) | calls Error; returns static_cast&lt;std::size_t&gt;(n) · [reviewed contract](#b0003) |
| [B0004 · 32–42](../../../../../apps/crown/aggregate.cpp#L32) | Callable definition: std::string read(const std::string& path,std::size_t limit=document_bytes) | calls input, Error, gcount, size; returns result; 1 loop sites · [reviewed contract](#b0004) |
| [B0005 · 43–64](../../../../../apps/crown/aggregate.cpp#L43) | Type/record definition: struct Arguments | returns {}; result; growth emplace, push_back; 1 loop sites · [reviewed contract](#b0005) |
| [B0006 · 65–70](../../../../../apps/crown/aggregate.cpp#L65) | Callable definition: ar::Id identity(const std::optional&lt;std::string&gt;& value,char default_digit) | calls fill, size, std::all_of, begin; returns result; (c&gt;=@ && c&lt;=@ ) \|\| (c&gt;=@ && c&lt;=@ ) · [reviewed contract](#b0006) |
| [B0007 · 71–86](../../../../../apps/crown/aggregate.cpp#L71) | Callable definition: void help() | calls  · [reviewed contract](#b0007) |
| [B0008 · 87–89](../../../../../apps/crown/aggregate.cpp#L87) | Callable definition: Json position(std::optional&lt;ar::ReaderPosition&gt; value) | calls ; returns value?Json{{@ ,value-&gt;bytes},{@ ,value-&gt;records}}:Json{} · [reviewed contract](#b0008) |
| [B0009 · 90–100](../../../../../apps/crown/aggregate.cpp#L90) | Callable definition: Json status(const ar::Session& session) | calls state, descriptor, program, identity; returns {{@ ,1},{@ ,@ },{@ ,std::string(binding.begin(),binding.end())}, · [reviewed contract](#b0009) |
| [B0010 · 101–102](../../../../../apps/crown/aggregate.cpp#L101) | Explanatory comments or spacing. | source comment (unverified): // Final report bytes are capped before append; one scalar's JSON escape · [reviewed contract](#b0010) |
| [B0011 · 103–122](../../../../../apps/crown/aggregate.cpp#L103) | Type/record definition: class Report | 1 loop sites; source comment (unverified): // Final report bytes are capped before append; one scalar's JSON escape · [reviewed contract](#b0011) |
| [B0012 · 123–140](../../../../../apps/crown/aggregate.cpp#L123) | Callable definition: void snapshot(const ar::Session& session,std::size_t max_bytes) | calls report, status, dump, pop_back; 2 loop sites · [reviewed contract](#b0012) |
| [B0013 · 141–143](../../../../../apps/crown/aggregate.cpp#L141) | Explanatory comments or spacing. | source comment (unverified): // A regular file is supplied from its original origin on every invocation. · [reviewed contract](#b0013) |
| [B0014 · 144–155](../../../../../apps/crown/aggregate.cpp#L144) | Callable definition: void seek(std::ifstream& input,ar::ReaderPosition origin) | calls max, Error, seekg, tellg; source comment (unverified): // A regular file is supplied from its original origin on every invocation. · [reviewed contract](#b0014) |
| [B0015 · 156–166](../../../../../apps/crown/aggregate.cpp#L156) | Callable definition: const char* reason(ar::RejectReason value) | calls Error; returns @; @ · [reviewed contract](#b0015) |
| [B0016 · 167–190](../../../../../apps/crown/aggregate.cpp#L167) | Callable definition: Json run(ar::Session& session,std::ifstream& input,const resource::MemoryAccount& account, std::uint64_t commands,io::SqlAggregat… | calls deliver, state, logged_reader_position, value_or; returns result; growth emplace; 1 loop sites; source comment (unverified): // Release the decoded command before native preparation. The reader · [reviewed contract](#b0016) |
| [B0017 · 191–191](../../../../../apps/crown/aggregate.cpp#L191) | Explanatory comments or spacing. |  |
| [B0018 · 192–263](../../../../../apps/crown/aggregate.cpp#L192) | Callable definition: int execute(int argc,char** argv) | calls std::string_view, help, args, Error; returns 0; 0 · [reviewed contract](#b0018) |
| [B0019 · 264–267](../../../../../apps/crown/aggregate.cpp#L264) | Closes surrounding scope/type. | source comment (unverified): // namespace · [reviewed contract](#b0019) |
| [B0020 · 268–276](../../../../../apps/crown/aggregate.cpp#L268) | Callable definition: int aggregate_main(int argc,char** argv) | calls execute, Error, what, std::string; returns execute(argc,argv); source comment (unverified): // Presentation only: fixed durable/resource failures are translated after all · [reviewed contract](#b0020) |
| [B0021 · 277–277](../../../../../apps/crown/aggregate.cpp#L277) | Closes surrounding scope/type. | source comment (unverified): // namespace crown::cli · [reviewed contract](#b0021) |

## B0001

[Lines 1–22](../../../../../apps/crown/aggregate.cpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L1-L22:sha256:e72f167638be1ec18f68f70c0d25e249c2c4c7648d92b3790dc8d2ce10b06aa0
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Prepare aggregate.cpp: include "aggregate.hpp", "crown/api/error.hpp", "crown/io/catalog.hpp", "crown/io/binding.hpp", "crown/io/normalization.hpp", "crown/io/physical.hpp", "crown/io/sql_aggregate_input.hpp", "crown/recovery/sql_aggregate_session.hpp", "crown/planner/oracle.hpp", "crown/storage/index_failure.hpp", &lt;algorithm&gt;, &lt;charconv&gt;, &lt;fstream&gt;, &lt;iostream&gt;, &lt;limits&gt;, &lt;map&gt;; bind local aliases/name imports; declare constant fixture data. |
| inputs / outputs | Compiler-visible dependencies, names and the recorded declarations in; declarations available to the following fixture/CLI/example definitions out. The source span lists the exact member/global names, types and initial values; initializers run when the enclosing object/program/thread is initialized. |
| invariants | Declarations are scoped to this source/header and its selected ABI. Included code has its own effects; names and editable fixture values do not confer proof, admission or publication authority. |
| ownership | Aliases/includes do not create a query owner. Pointers/references/views are non-owning. Containers own their elements, which can themselves be borrowed pointers or numeric IDs. Only documented owning shared-control handles retain controls; IDs/slot-handle values do not independently keep an arena/runtime alive. |
| failure | Missing headers, ill-formed names/types, failed static assertions or active #error directives stop compilation. No runtime rejection/rollback mechanism is implemented by aliases or function prototypes. |
| cost | Preprocessing and type/constraint instantiation cost compilation. Alias/prototype syntax does not invoke the declared operation; any included definitions keep their own initialization effects. These constexpr data are fixed fixture constants; quota literals are grants, not reserved bytes or measured peaks. |
| Design | [apps/crown/aggregate.cpp](../../../../../apps/crown/aggregate.cpp), [docs/aggregates.md](../../../../aggregates.md), [docs/code_review.md](../../../../code_review.md) |

## B0002

[Lines 23–27](../../../../../apps/crown/aggregate.cpp#L23); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::uint64_t number(std::string_view value) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Parse an exact unsigned CLI option. |
| inputs / outputs | String bytes enter; a uint64 is returned only when from_chars consumes every byte. |
| invariants | No signs, whitespace suffixes or silent overflow conversion are accepted. |
| ownership | Arguments and stream/Session references are synchronous borrows. Explicit local ordinary reports/options or the returned owner retain their own storage; no hidden native state mirror. |
| failure | Malformed/out-of-range text raises usage before file operations. |
| cost | Linear in option text length; no parser allocation on success. |
| Design | [apps/crown/aggregate.cpp §B0002 L23-L27](../../../../../apps/crown/aggregate.cpp), [docs/sql_aggregate_input.md](../../../../sql_aggregate_input.md), [docs/sql_aggregate_session.md](../../../../sql_aggregate_session.md), [docs/code_specs/error_handling.md](../../../error_handling.md) |

## B0003

[Lines 28–31](../../../../../apps/crown/aggregate.cpp#L28); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::size_t size(std::uint64_t n) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Admit a CLI size on the current host. |
| inputs / outputs | uint64 enters and size_t returns after its exact host bound check. |
| invariants | Narrow hosts never wrap the requested resource extent. |
| ownership | Arguments and stream/Session references are synchronous borrows. Explicit local ordinary reports/options or the returned owner retain their own storage; no hidden native state mirror. |
| failure | An out-of-domain size raises usage. |
| cost | Constant scalar work. |
| Design | [apps/crown/aggregate.cpp §B0003 L28-L31](../../../../../apps/crown/aggregate.cpp), [docs/sql_aggregate_input.md](../../../../sql_aggregate_input.md), [docs/sql_aggregate_session.md](../../../../sql_aggregate_session.md), [docs/code_specs/error_handling.md](../../../error_handling.md) |

## B0004

[Lines 32–42](../../../../../apps/crown/aggregate.cpp#L32); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::string read(const std::string& path,std::size_t limit=document_bytes) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Read one bounded cold SQL/catalog/options document. |
| inputs / outputs | A path and finite byte cap enter; owning ordinary text returns after complete stream validation. |
| invariants | The result is bounded before each append; compiler/DOM workspace is separate from the native query account. |
| ownership | Arguments and stream/Session references are synchronous borrows. Explicit local ordinary reports/options or the returned owner retain their own storage; no hidden native state mirror. |
| failure | Open/read failure is io_error; exceeding the document cap is resource_limit. |
| cost | Linear file bytes, an 8 KiB stack block and geometrically grown ordinary text. |
| Design | [apps/crown/aggregate.cpp §B0004 L32-L42](../../../../../apps/crown/aggregate.cpp), [docs/sql_aggregate_input.md](../../../../sql_aggregate_input.md), [docs/sql_aggregate_session.md](../../../../sql_aggregate_session.md), [docs/code_specs/error_handling.md](../../../error_handling.md) |

## B0005

[Lines 43–64](../../../../../apps/crown/aggregate.cpp#L43); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct Arguments {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Own and validate one aggregate command line. |
| inputs / outputs | argv paths/options are copied into a vector/map; take/integer consume known options and finish checks path count and leftovers. |
| invariants | Duplicate/missing values and inapplicable options fail before native namespace operations; help is handled earlier. |
| ownership | Arguments and stream/Session references are synchronous borrows. Explicit local ordinary reports/options or the returned owner retain their own storage; no hidden native state mirror. |
| failure | Usage errors or ordinary allocation failure propagate. |
| cost | Cold O(argc) parsing plus ordered-map/string comparisons and explicit option copies; no update-path field. |
| Design | [apps/crown/aggregate.cpp §B0005 L43-L64](../../../../../apps/crown/aggregate.cpp), [docs/sql_aggregate_input.md](../../../../sql_aggregate_input.md), [docs/sql_aggregate_session.md](../../../../sql_aggregate_session.md), [docs/code_specs/error_handling.md](../../../error_handling.md) |

## B0006

[Lines 65–70](../../../../../apps/crown/aggregate.cpp#L65); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
ar::Id identity(const std::optional<std::string>& value,char default_digit) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Validate or default an R2 identity label. |
| inputs / outputs | An optional ordinary string returns exactly 32 lower-hex bytes; absent query/sink labels use the declared repeated default digit. |
| invariants | Labels do not authenticate a caller; genuine root/descriptor/sink binding still applies. |
| ownership | Arguments and stream/Session references are synchronous borrows. Explicit local ordinary reports/options or the returned owner retain their own storage; no hidden native state mirror. |
| failure | Wrong length/alphabet raises usage before state creation/recovery. |
| cost | 32 byte checks/copies, no retained dynamic ID. |
| Design | [apps/crown/aggregate.cpp §B0006 L65-L70](../../../../../apps/crown/aggregate.cpp), [docs/sql_aggregate_input.md](../../../../sql_aggregate_input.md), [docs/sql_aggregate_session.md](../../../../sql_aggregate_session.md), [docs/code_specs/error_handling.md](../../../error_handling.md) |

## B0007

[Lines 71–86](../../../../../apps/crown/aggregate.cpp#L71); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void help() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Present the separate R2 CLI workflow and admissions. |
| inputs / outputs | Writes fixed create/run/status/snapshot/checkpoint usage and limits to stdout. |
| invariants | Help constructs no native owner and acknowledges no output. |
| ownership | Arguments and stream/Session references are synchronous borrows. Explicit local ordinary reports/options or the returned owner retain their own storage; no hidden native state mirror. |
| failure | Final process output handling detects failed writes/flushes. |
| cost | One finite help write per invocation, outside report-byte/native limits. |
| Design | [apps/crown/aggregate.cpp §B0007 L71-L86](../../../../../apps/crown/aggregate.cpp), [docs/sql_aggregate_input.md](../../../../sql_aggregate_input.md), [docs/sql_aggregate_session.md](../../../../sql_aggregate_session.md), [docs/code_specs/error_handling.md](../../../error_handling.md) |

## B0008

[Lines 87–89](../../../../../apps/crown/aggregate.cpp#L87); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Json position(std::optional<ar::ReaderPosition> value) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Render an optional reader continuation. |
| inputs / outputs | An optional bytes/records pair becomes a small JSON object or null. |
| invariants | Formatting copies metadata only and supplies no source/disposition authority. |
| ownership | Arguments and stream/Session references are synchronous borrows. Explicit local ordinary reports/options or the returned owner retain their own storage; no hidden native state mirror. |
| failure | Ordinary JSON allocation failure propagates. |
| cost | Fixed-size cold presentation work. |
| Design | [apps/crown/aggregate.cpp §B0008 L87-L89](../../../../../apps/crown/aggregate.cpp), [docs/sql_aggregate_input.md](../../../../sql_aggregate_input.md), [docs/sql_aggregate_session.md](../../../../sql_aggregate_session.md), [docs/code_specs/error_handling.md](../../../error_handling.md) |

## B0009

[Lines 90–100](../../../../../apps/crown/aggregate.cpp#L90); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Json status(const ar::Session& session) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Describe the actual recovered Session frontiers and binding. |
| inputs / outputs | A borrowed healthy Session supplies W/I/C/D, generation, pending flags, disposed/logged reader progress and storage family. |
| invariants | The result is a report of the held owner; actual recovery/repair happened in execute, and no report acknowledges delivery. |
| ownership | Arguments and stream/Session references are synchronous borrows. Explicit local ordinary reports/options or the returned owner retain their own storage; no hidden native state mirror. |
| failure | Unusable owner access or ordinary JSON allocation propagates. |
| cost | Fixed metadata/identity copying and small ordinary JSON construction; no source-row scan. |
| Design | [apps/crown/aggregate.cpp §B0009 L90-L100](../../../../../apps/crown/aggregate.cpp), [docs/sql_aggregate_input.md](../../../../sql_aggregate_input.md), [docs/sql_aggregate_session.md](../../../../sql_aggregate_session.md), [docs/code_specs/error_handling.md](../../../error_handling.md) |

## B0010

[Lines 101–102](../../../../../apps/crown/aggregate.cpp#L101); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L101-L102:sha256:3b4ed32e378471b60b2a2b3935d1e65786c53ba7511ef0f8c1691946913b8beb
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Explain the adjacent source contract: Final report bytes are capped before append; one scalar's JSON escape temporary follows the existing CLI's ordinary presentation allocation policy. |
| inputs / outputs | Human-readable source note in; no executable output or checked receipt. |
| invariants | This comment states context or a limitation. It does not itself enforce or prove the described behavior; use the adjacent implementation and its scoped contract. |
| ownership | Source text only; no object or resource lifetime is created. |
| failure | No runtime failure path in this comment; source encoding/comment syntax still belongs to compilation. |
| cost | No runtime operations from the comment. Any work described in the note belongs to the adjacent operation. |
| Design | [apps/crown/aggregate.cpp](../../../../../apps/crown/aggregate.cpp), [docs/aggregates.md](../../../../aggregates.md), [docs/code_review.md](../../../../code_review.md) |

## B0011

[Lines 103–122](../../../../../apps/crown/aggregate.cpp#L103); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
class Report {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Bound complete report bytes and render nullable typed tuples. |
| inputs / outputs | raw checks before append; json/tuple encode one scalar at a time; emit starts stdout only after the report is complete. |
| invariants | The append cap excludes one scalar escape temporary and native snapshot construction; output never revokes a durable decision. |
| ownership | Arguments and stream/Session references are synchronous borrows. Explicit local ordinary reports/options or the returned owner retain their own storage; no hidden native state mirror. |
| failure | output_limit, output_error and ordinary allocations propagate to the process boundary. |
| cost | Linear appended/escaped bytes with ordinary string capacity; one scalar JSON temporary, no second durable output queue. |
| Design | [apps/crown/aggregate.cpp §B0011 L103-L122](../../../../../apps/crown/aggregate.cpp), [docs/sql_aggregate_input.md](../../../../sql_aggregate_input.md), [docs/sql_aggregate_session.md](../../../../sql_aggregate_session.md), [docs/code_specs/error_handling.md](../../../error_handling.md) |

## B0012

[Lines 123–140](../../../../../apps/crown/aggregate.cpp#L123); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void snapshot(const ar::Session& session,std::size_t max_bytes) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Encode an eager committed aggregate snapshot for people. |
| inputs / outputs | Funds Session.snapshot, then emits frontiers, named/symbolic SQL output types and nullable group key/value rows. |
| invariants | Snapshot C may exceed delivered D; global empty-group presence differs from absent groups and null cells. |
| ownership | Arguments and stream/Session references are synchronous borrows. Explicit local ordinary reports/options or the returned owner retain their own storage; no hidden native state mirror. |
| failure | Native snapshot group/work/account limits, presentation cap and output failures propagate without changing committed state. |
| cost | Whole snapshot/group/field work plus encoded bytes. Native image is accounted; ordinary JSON scalar/name temporaries are separate. |
| Design | [apps/crown/aggregate.cpp §B0012 L123-L140](../../../../../apps/crown/aggregate.cpp), [docs/sql_aggregate_input.md](../../../../sql_aggregate_input.md), [docs/sql_aggregate_session.md](../../../../sql_aggregate_session.md), [docs/code_specs/error_handling.md](../../../error_handling.md) |

## B0013

[Lines 141–143](../../../../../apps/crown/aggregate.cpp#L141); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L141-L143:sha256:558078a7d2f02382d9e3b96159f6082c998062e6a036f9cc7fe3f65e2f1df50f
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Explain the adjacent source contract: A regular file is supplied from its original origin on every invocation. A saved offset alone is not a file-content hash; the caller preserves the consumed prefix. An unterminated final line cannot gain a second glued row. |
| inputs / outputs | Human-readable source note in; no executable output or checked receipt. |
| invariants | This comment states context or a limitation. It does not itself enforce or prove the described behavior; use the adjacent implementation and its scoped contract. |
| ownership | Source text only; no object or resource lifetime is created. |
| failure | No runtime failure path in this comment; source encoding/comment syntax still belongs to compilation. |
| cost | No runtime operations from the comment. Any work described in the note belongs to the adjacent operation. |
| Design | [apps/crown/aggregate.cpp](../../../../../apps/crown/aggregate.cpp), [docs/aggregates.md](../../../../aggregates.md), [docs/code_review.md](../../../../code_review.md) |

## B0014

[Lines 144–155](../../../../../apps/crown/aggregate.cpp#L144); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void seek(std::ifstream& input,ar::ReaderPosition origin) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Seek a regular input file to its saved original-stream position. |
| inputs / outputs | A borrowed ifstream and reader byte count select the next unread byte after checking host range/file length and, when longer, its preceding LF. |
| invariants | The consumed prefix is caller-preserved, not rehashed. A consumed unterminated last record cannot later accept appended data, even an added LF. |
| ownership | Arguments and stream/Session references are synchronous borrows. Explicit local ordinary reports/options or the returned owner retain their own storage; no hidden native state mirror. |
| failure | Short/non-boundary offsets raise invalid_input_progress; failed seeking is io_error. |
| cost | A fixed number of seeks and at most one boundary-byte read, not a prefix rescan. |
| Design | [apps/crown/aggregate.cpp §B0014 L144-L155](../../../../../apps/crown/aggregate.cpp), [docs/sql_aggregate_input.md](../../../../sql_aggregate_input.md), [docs/sql_aggregate_session.md](../../../../sql_aggregate_session.md), [docs/code_specs/error_handling.md](../../../error_handling.md) |

## B0015

[Lines 156–166](../../../../../apps/crown/aggregate.cpp#L156); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
const char* reason(ar::RejectReason value) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Name the six durable semantic Reject tags. |
| inputs / outputs | A stable RejectReason returns a static label for the report. |
| invariants | Resource/contract failures have no Reject tag. |
| ownership | Arguments and stream/Session references are synchronous borrows. Explicit local ordinary reports/options or the returned owner retain their own storage; no hidden native state mirror. |
| failure | An impossible enum raises runtime_contract. |
| cost | Constant switch; no success-path allocation. |
| Design | [apps/crown/aggregate.cpp §B0015 L156-L166](../../../../../apps/crown/aggregate.cpp), [docs/sql_aggregate_input.md](../../../../sql_aggregate_input.md), [docs/sql_aggregate_session.md](../../../../sql_aggregate_session.md), [docs/code_specs/error_handling.md](../../../error_handling.md) |

## B0016

[Lines 167–190](../../../../../apps/crown/aggregate.cpp#L167); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Json run(ar::Session& session,std::ifstream& input,const resource::MemoryAccount& account,
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Resume logged commands through the actual R2 owner. |
| inputs / outputs | Deliver a recovered spool, decide any existing WAL head, otherwise decode/log one W+1 command, release its decoded buffers, decide and deliver. |
| invariants | The limit counts decisions, including a recovered head; zero still drains existing output. CLI JSONL requires one saved reader record per W. Reject advances I/reader while C/D stay. |
| ownership | Arguments and stream/Session references are synchronous borrows. Explicit local ordinary reports/options or the returned owner retain their own storage; no hidden native state mirror. |
| failure | Failures propagate with no retry loop; Session preserves a resource-failed head or requires reopen after uncertain I/O. A later invocation resumes actual W, including after report failure. |
| cost | Per command: bounded transport passes, genuine native prepare, canonical WAL/output and sync costs. One decoded command/head overlap during log; raw-line capacity persists; no extra database. |
| Design | [apps/crown/aggregate.cpp §B0016 L167-L190](../../../../../apps/crown/aggregate.cpp), [docs/sql_aggregate_input.md](../../../../sql_aggregate_input.md), [docs/sql_aggregate_session.md](../../../../sql_aggregate_session.md), [docs/code_specs/error_handling.md](../../../error_handling.md) |

## B0018

[Lines 192–263](../../../../../apps/crown/aggregate.cpp#L192); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
int execute(int argc,char** argv) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Execute the explicit R2 file workflow. |
| inputs / outputs | Validated options route genuine SQL/catalog/tree creation or selected-descriptor recovery into create/run/status/snapshot/checkpoint and bounded reporting. |
| invariants | Contradictory sources skip tree search through their existing constant-empty route. Recovery operations may repair admissible tails unless disabled. Native normal policies are not replaced by cold rebuild grants. |
| ownership | Arguments and stream/Session references are synchronous borrows. Explicit local ordinary reports/options or the returned owner retain their own storage; no hidden native state mirror. |
| failure | Argument/admission/search/file/native/resource/report failures propagate. Durable state can precede a failed final report; an exit code is not rollback evidence. |
| cost | Cold binding/search/recovery or whole checkpoint/snapshot costs plus requested commands. One shared receiving account; caller/compiler/JSON/report workspace is separate. |
| Design | [apps/crown/aggregate.cpp §B0018 L192-L263](../../../../../apps/crown/aggregate.cpp), [docs/sql_aggregate_input.md](../../../../sql_aggregate_input.md), [docs/sql_aggregate_session.md](../../../../sql_aggregate_session.md), [docs/code_specs/error_handling.md](../../../error_handling.md) |

## B0019

[Lines 264–267](../../../../../apps/crown/aggregate.cpp#L264); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L264-L267:sha256:c9e531f14dc5381b094bc0c02a73412a9cacb663bbd6c8f8a82c3d94eb7ffce2
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Close the recorded declaration scopes in aggregate.cpp: namespace (anonymous). |
| inputs / outputs | Preceding namespace, type or initializer declarations in; completed lexical boundary out. |
| invariants | Brace-opening context is recorded in root-scope-context-v1.json. These are declaration/initializer boundaries, not an independent update, validation or recovery operation. |
| ownership | Enclosing objects and borrowed fields keep their declared ownership. This punctuation creates no new owner. |
| failure | Malformed scope syntax is a compile error. Any initializer/constructor failure belongs to the enclosing object declaration. |
| cost | No separate loop, guard or engine call is introduced by the delimiter; enclosing initialization and object lifetime still have their actual costs. |
| Design | [apps/crown/aggregate.cpp](../../../../../apps/crown/aggregate.cpp), [docs/aggregates.md](../../../../aggregates.md), [docs/code_review.md](../../../../code_review.md) |

## B0020

[Lines 268–276](../../../../../apps/crown/aggregate.cpp#L268); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
int aggregate_main(int argc,char** argv) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Translate fixed R2 failures at the CLI presentation boundary. |
| inputs / outputs | After owned command state unwinds, six concrete failure families become Error diagnostics; existing Error and unrelated exceptions continue to the primary process boundary. |
| invariants | No semantic Reject is invented; handlers do not retry, repair or undo any native/file action. |
| ownership | Arguments and stream/Session references are synchronous borrows. Explicit local ordinary reports/options or the returned owner retain their own storage; no hidden native state mirror. |
| failure | Diagnostic allocation can itself reach the final process fallback. |
| cost | Only exception presentation allocates here; normal execution is one direct call and return. |
| Design | [apps/crown/aggregate.cpp §B0020 L268-L276](../../../../../apps/crown/aggregate.cpp), [docs/sql_aggregate_input.md](../../../../sql_aggregate_input.md), [docs/sql_aggregate_session.md](../../../../sql_aggregate_session.md), [docs/code_specs/error_handling.md](../../../error_handling.md) |

## B0021

[Lines 277–277](../../../../../apps/crown/aggregate.cpp#L277); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L277-L277:sha256:439621fef6866561bd363da58ad7838963b4055e4d6ddd5b36406c2ad7483c0d
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Close the recorded declaration scopes in aggregate.cpp: namespace crown::cli. |
| inputs / outputs | Preceding namespace, type or initializer declarations in; completed lexical boundary out. |
| invariants | Brace-opening context is recorded in root-scope-context-v1.json. These are declaration/initializer boundaries, not an independent update, validation or recovery operation. |
| ownership | Enclosing objects and borrowed fields keep their declared ownership. This punctuation creates no new owner. |
| failure | Malformed scope syntax is a compile error. Any initializer/constructor failure belongs to the enclosing object declaration. |
| cost | No separate loop, guard or engine call is introduced by the delimiter; enclosing initialization and object lifetime still have their actual costs. |
| Design | [apps/crown/aggregate.cpp](../../../../../apps/crown/aggregate.cpp), [docs/aggregates.md](../../../../aggregates.md), [docs/code_review.md](../../../../code_review.md) |
