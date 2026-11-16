# `src/io/sql_aggregate_input.cpp` — block usage map

[Source](../../../../../src/io/sql_aggregate_input.cpp) · [Source index](../../../README.md) · [Subsystem contracts](../../../subsystem_contracts.md) · [Reviewed primitives](../../../primitives.md)

Admit bounded external documents/records and serialize explicit public representations at the engine boundary.

Snapshot SHA-256: `20d191b85caa66bc2ed0a4ff1b991d55556ffb857fe29e218a9b6769fbff352b`. 200 lines partitioned into 23 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [io](../../../subsystem_contracts.md#io). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/ingestion.md](../../../../ingestion.md), [docs/query_identity.md](../../../../query_identity.md), [docs/schema_evolution.md](../../../../schema_evolution.md), [docs/cli.md](../../../../cli.md), [docs/query_memory.md](../../../../query_memory.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–12](../../../../../src/io/sql_aggregate_input.cpp#L1) | Imports dependencies; declares namespace scope; declares aliases; declares types or opens a type body; declares values/defaults or compile-time conditions. |  · [reviewed contract](#b0001) |
| [B0002 · 13–15](../../../../../src/io/sql_aggregate_input.cpp#L13) | Callable definition: template&lt;class T&gt; auto allocator(const resource::MemoryAccount& account) | calls ; returns resource::MemoryAllocator&lt;T&gt;(account,resource::MemoryPurpose::scratch) · [reviewed contract](#b0002) |
| [B0003 · 16–18](../../../../../src/io/sql_aggregate_input.cpp#L16) | Callable definition: void require(bool valid,const char* code,const char* message) | calls Error; guard void require(bool valid,const char* code,const char* message) { · [reviewed contract](#b0003) |
| [B0004 · 19–28](../../../../../src/io/sql_aggregate_input.cpp#L19) | Callable definition: void fields(const Json& value,std::initializer_list&lt;std::string_view&gt; required, std::initializer_list&lt;std::string_view&gt; optional=… | calls require, is_object, contains, begin; guard require(value.is_object(),"invalid_document","aggregate input requires an object");; 2 loop sites · [reviewed contract](#b0004) |
| [B0005 · 29–33](../../../../../src/io/sql_aggregate_input.cpp#L29) | Callable definition: std::uint64_t number(const Json& value) | calls require, is_number_unsigned, is_number_integer; guard require(value.is_number_unsigned() \|\| (value.is_number_integer() && value.get&lt;std::int64_t&gt;()&gt;=0),; returns value.get&lt;std::uint64_t&gt;() · [reviewed contract](#b0005) |
| [B0006 · 34–37](../../../../../src/io/sql_aggregate_input.cpp#L34) | Callable definition: const std::string& text(const Json& value) | calls require, is_string; guard require(value.is_string(),"invalid_document","aggregate input requires a string");; returns value.get_ref&lt;const std::string&&gt;() · [reviewed contract](#b0006) |
| [B0007 · 38–39](../../../../../src/io/sql_aggregate_input.cpp#L38) | Explanatory comments or spacing. | source comment (unverified): // Inline scalars borrow only the DOM's TEXT. All such borrows are copied into · [reviewed contract](#b0007) |
| [B0008 · 40–59](../../../../../src/io/sql_aggregate_input.cpp#L40) | Callable definition: Cell scalar(const Json& value,std::size_t field_bytes) | calls is_null, is_string, require, text; guard require(text(value).size()&lt;=field_bytes,"resource_limit","aggregate scalar string byte limit exceed…; returns {}; storage::ScalarView{std::string_view(text(value))}; source comment (unverified): // Inline scalars borrow only the DOM's TEXT. All such borrows are copied into · [reviewed contract](#b0008) |
| [B0009 · 60–66](../../../../../src/io/sql_aggregate_input.cpp#L60) | Callable definition: const frontend::SqlRowsSource& source(const frontend::SqlAggregateProgram& program,const Json& name) | calls text, source_program, sources, std::find_if; guard require(found!=sources.end(),"unknown_table","aggregate input table is not a physical source name");; returns s.name==exact; *found · [reviewed contract](#b0009) |
| [B0010 · 67–68](../../../../../src/io/sql_aggregate_input.cpp#L67) | Closes surrounding scope/type. | source comment (unverified): // namespace · [reviewed contract](#b0010) |
| [B0011 · 69–84](../../../../../src/io/sql_aggregate_input.cpp#L69) | Type/record definition: struct SqlAggregateJsonCommand::Data | returns value.empty()?std::string_view{}:std::string_view(text.data()+begin,value.size()); growth insert; source comment (unverified): // Empty TEXT needs no pointer arithmetic on an empty vector's null data. · [reviewed contract](#b0011) |
| [B0012 · 85–103](../../../../../src/io/sql_aggregate_input.cpp#L85) | Type/record definition: struct SqlAggregateJsonlReader::Data | guard require(limits.record_bytes&lt;std::numeric_limits&lt;std::size_t&gt;::max(),"invalid_options","record byte … · [reviewed contract](#b0012) |
| [B0013 · 104–104](../../../../../src/io/sql_aggregate_input.cpp#L104) | Explanatory comments or spacing. |  |
| [B0014 · 105–105](../../../../../src/io/sql_aggregate_input.cpp#L105) | Callable definition: SqlAggregateJsonCommand::SqlAggregateJsonCommand(resource::AccountedUnique&lt;Data&gt; data) noexcept:data_(std::move(data)) | calls data_, std::move · [reviewed contract](#b0014) |
| [B0015 · 106–108](../../../../../src/io/sql_aggregate_input.cpp#L106) | declares callable signatures; declares values/defaults or compile-time conditions. |  · [reviewed contract](#b0015) |
| [B0016 · 109–112](../../../../../src/io/sql_aggregate_input.cpp#L109) | Callable definition: ar::InputView SqlAggregateJsonCommand::view() const & | calls require, bool; guard require(bool(data_),"invalid_input_state","aggregate command is moved from");; returns {data_-&gt;sequence,data_-&gt;replacements,data_-&gt;source,data_-&gt;reader} · [reviewed contract](#b0016) |
| [B0017 · 113–116](../../../../../src/io/sql_aggregate_input.cpp#L113) | Callable definition: SqlAggregateJsonlReader::SqlAggregateJsonlReader(std::istream& stream,const resource::MemoryAccount& account, const frontend::Sql… | calls data_; growth make_accounted_unique · [reviewed contract](#b0017) |
| [B0018 · 117–119](../../../../../src/io/sql_aggregate_input.cpp#L117) | declares callable signatures; declares values/defaults or compile-time conditions. |  · [reviewed contract](#b0018) |
| [B0019 · 120–120](../../../../../src/io/sql_aggregate_input.cpp#L120) | Callable definition: bool SqlAggregateJsonlReader::requires_reopen() const noexcept | calls ; returns !data_ \|\| data_-&gt;poison · [reviewed contract](#b0019) |
| [B0020 · 121–123](../../../../../src/io/sql_aggregate_input.cpp#L121) | Callable definition: ar::ReaderPosition SqlAggregateJsonlReader::position() const | calls require; guard require(data_ && !data_-&gt;poison,"invalid_input_state","aggregate reader requires reopen");return da…; returns data_-&gt;position · [reviewed contract](#b0020) |
| [B0021 · 124–124](../../../../../src/io/sql_aggregate_input.cpp#L124) | Explanatory comments or spacing. |  |
| [B0022 · 125–199](../../../../../src/io/sql_aggregate_input.cpp#L125) | Callable definition: std::optional&lt;SqlAggregateJsonCommand&gt; SqlAggregateJsonlReader::next() | calls require, clear, get, eof; guard require(data_ && !data_-&gt;poison,"invalid_input_state","aggregate reader requires reopen");; returns {}; {}; growth make_accounted_unique, push_back, reserve; 5 loop sites; source comment (unverified): // Bound the line during framing, including one optional trailing CR. Logical · [reviewed contract](#b0022) |
| [B0023 · 200–200](../../../../../src/io/sql_aggregate_input.cpp#L200) | Closes surrounding scope/type. | source comment (unverified): // namespace crown::io · [reviewed contract](#b0023) |

## B0001

[Lines 1–12](../../../../../src/io/sql_aggregate_input.cpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L1-L12:sha256:9e9bb3b0b3b1ae602a5ddb12f0c91c113418b3d4f456f4190b826cbcdd9a56d2
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Imports compile-time dependencies (crown/io/sql_aggregate_input.hpp, crown/io/document.hpp, crown/api/error.hpp, ../frontend/sql_rows_value.hpp, algorithm, limits) and opens crown::io scope for the declarations or definitions that follow. |
| inputs / outputs | No runtime inputs/outputs are declared by the import/scope lines themselves. |
| invariants | The listed headers and namespace membership determine compile-time name availability; any API behavior belongs to the declarations/definitions that follow. |
| ownership | No object ownership is created by the imports or namespace tokens. |
| failure | No runtime failure path. Missing/incompatible dependencies or a violated compile-time constraint fail translation/linking. |
| cost | Compile/preprocessor work only; no new per-operation runtime overhead. |
| Design | [src/io/sql_aggregate_input.cpp](../../../../../src/io/sql_aggregate_input.cpp), [docs/code_specs/files/src/io/sql_aggregate_input.cpp.md](sql_aggregate_input.cpp.md), [docs/sql_aggregate_input.md](../../../../sql_aggregate_input.md), [docs/sql_aggregate_records.md](../../../../sql_aggregate_records.md) |

## B0002

[Lines 13–15](../../../../../src/io/sql_aggregate_input.cpp#L13); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
template<class T> auto allocator(const resource::MemoryAccount& account) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Adapt the receiving account into the allocator used by retained line and command vectors. |
| inputs / outputs | A MemoryAccount reference produces a MemoryAllocator&lt;T&gt; tagged scratch for the requested element type. |
| invariants | Only containers instantiated with this allocator are charged to the account; this helper does not make nlohmann Json or standard parser workspace account-aware. |
| ownership | The allocator object borrows/retains the account according to MemoryAllocator ownership semantics. The resulting vectors own their allocations and release them through that allocator. |
| failure | Account admission failure propagates from container allocation. The helper adds no catch or translation. |
| cost | Constructing the adapter is constant work; allocation and deallocation costs arise at vector growth and are recorded as actual account requests, not as exact vector size or RSS. |
| Design | [docs/sql_aggregate_input.md §Ownership, failure and cost](../../../../sql_aggregate_input.md), [docs/sql_aggregate_session.md §Resource and performance scope](../../../../sql_aggregate_session.md), [docs/query_memory.md §Boundaries](../../../../query_memory.md) |

## B0003

[Lines 16–18](../../../../../src/io/sql_aggregate_input.cpp#L16); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void require(bool valid,const char* code,const char* message) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Convert a failed local JSONL validation predicate into the project Error boundary. |
| inputs / outputs | Receives a boolean and borrowed diagnostic code/message literals; returns normally when true, otherwise throws Error with those values. |
| invariants | It has no parser or Session authority and does not recover, poison or advance state itself. Its callers place it before publishing decoded progress. |
| ownership | The helper borrows the char arrays. Error owns its presented diagnostic; no error object is retained on success. |
| failure | The exception and its owning message are constructed only when valid is false and may allocate then. No Error is caught here; callers observe the failure. |
| cost | A passing check is constant work. A failing check includes Error/exception construction and unwinding, so this is not a no-allocation guarantee for malformed input. |
| Design | [docs/sql_aggregate_input.md §Ownership, failure and cost](../../../../sql_aggregate_input.md), [docs/sql_aggregate_input.md §Workflow](../../../../sql_aggregate_input.md), [docs/code_review.md §Coverage and retained evidence](../../../../code_review.md) |

## B0004

[Lines 19–28](../../../../../src/io/sql_aggregate_input.cpp#L19); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void fields(const Json& value,std::initializer_list<std::string_view> required,
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Require an object with all mandatory keys and no keys outside the explicit optional set. |
| inputs / outputs | Takes a DOM value and required/optional key views; returns no value after checking object shape, required membership and each actual key. |
| invariants | Used at envelope, replacement and source-position levels to make accepted fields exact. Duplicate-key rejection belongs to the earlier strict read_json parser, not this DOM-level key loop. |
| ownership | Key views borrow static call-site literals. The input Json remains owned by the caller and this helper retains no key or object. |
| failure | Wrong shape, a missing key or an unknown key throws invalid_document through require(); the diagnostic may allocate on failure. |
| cost | Checks object membership and iterates present keys; work scales with the object key count and the small declared required/optional lists. |
| Design | [docs/sql_aggregate_input.md §One atomic JSONL command](../../../../sql_aggregate_input.md), [docs/sql_aggregate_input.md §Ownership, failure and cost](../../../../sql_aggregate_input.md), [src/io/document.cpp §read_json definition, lines 19–20](../../../../../src/io/document.cpp), [schemas/sql-aggregate-input-v1.schema.json](../../../../../schemas/sql-aggregate-input-v1.schema.json) |

## B0005

[Lines 29–33](../../../../../src/io/sql_aggregate_input.cpp#L29); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::uint64_t number(const Json& value) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Decode an unsigned JSON integer used for versions, sequences, offsets, schema versions and weights. |
| inputs / outputs | Accepts an unsigned JSON number or a signed integer whose value is nonnegative, then returns uint64_t. |
| invariants | Negative numbers, fractions and noninteger values are not admitted. This conversion does not check application-specific sequence continuity or before/after semantics. |
| ownership | The scalar is read from a caller-owned DOM and copied by value; no borrowed reference escapes. |
| failure | Invalid JSON number category/value throws invalid_document; caller-specific range or identity checks are separate. |
| cost | Constant-size type/range checks and conversion; no dynamic storage on success. |
| Design | [docs/sql_aggregate_input.md §One atomic JSONL command](../../../../sql_aggregate_input.md), [docs/aggregates.md §SQL and numeric contract](../../../../aggregates.md), [docs/sql_aggregate_input.md §Ownership, failure and cost](../../../../sql_aggregate_input.md), [schemas/sql-aggregate-input-v1.schema.json](../../../../../schemas/sql-aggregate-input-v1.schema.json) |

## B0006

[Lines 34–37](../../../../../src/io/sql_aggregate_input.cpp#L34); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
const std::string& text(const Json& value) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Validate a JSON string and return a borrowed reference to its DOM-owned string. |
| inputs / outputs | Takes a Json node and returns const std::string& when it is a string. |
| invariants | The return borrows the node’s string and must not outlive or be invalidated by mutation/destruction of that DOM. |
| ownership | The helper copies no payload and retains no owner; the caller must copy any bytes needed by SqlAggregateJsonCommand before the DOM is released. |
| failure | A non-string throws invalid_document; later callers may apply UTF8, SQL type or byte-limit checks. |
| cost | Constant checks plus reference return; it does not copy string bytes. |
| Design | [docs/sql_aggregate_input.md §One atomic JSONL command](../../../../sql_aggregate_input.md), [docs/sql_aggregate_input.md §Ownership, failure and cost](../../../../sql_aggregate_input.md), [src/io/document.cpp §read_json definition, lines 19–20](../../../../../src/io/document.cpp) |

## B0007

[Lines 38–39](../../../../../src/io/sql_aggregate_input.cpp#L38); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L38-L39:sha256:1a17db28751b6b2feda2a1a00868adfc54c6645e9d9559b5e4cc07e7dbc0f1e6
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Design note for adjacent code: Inline scalars borrow only the DOM's TEXT. All such borrows are copied into the command's single text buffer before the temporary DOM is released. This is caller guidance recorded as prose, not an executable result. |
| inputs / outputs | No runtime interface is implemented by these comment-only lines. They sit at src/io/sql_aggregate_input.cpp lines 36-41; the surrounding declaration/body defines its own inputs and outputs. |
| invariants | The words record the intended use boundary only. They do not add a guard, proof, capability, transaction, durability guarantee, or account charge; verify behavior in the referenced implementation. |
| ownership | Comment text owns no data. Object lifetimes, borrows, and account attribution remain those of the adjacent source objects and their constructors. |
| failure | No failure path is implemented here. Any mentioned failure or recovery rule belongs to the adjacent operation and its existing error carrier. |
| cost | No runtime work is performed by these lines; any cost/bound in the note is not certified by this comment-only card. |
| Design | [src/io/sql_aggregate_input.cpp](../../../../../src/io/sql_aggregate_input.cpp), [docs/code_specs/files/src/io/sql_aggregate_input.cpp.md](sql_aggregate_input.cpp.md), [docs/sql_aggregate_input.md](../../../../sql_aggregate_input.md), [docs/sql_aggregate_records.md](../../../../sql_aggregate_records.md) |

## B0008

[Lines 40–59](../../../../../src/io/sql_aggregate_input.cpp#L40); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Cell scalar(const Json& value,std::size_t field_bytes) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Decode one nullable physical SQL scalar into the runtime’s borrowed ScalarView cell form. |
| inputs / outputs | Accepts JSON null, string, bool, signed or bounded unsigned integer, and one-key date/decimal tag objects; returns an empty cell for NULL and a ScalarView otherwise. |
| invariants | Unsigned integers must fit INT64_MAX. String and tag text respect field_bytes. Arrays, floats, multi-key/unknown tags and implicit conversions reject. Full source column type/nullability/domain checks are applied by the caller after conversion. |
| ownership | A JSON string returns a view into the temporary DOM; DATE and InlineDecimal are inline typed values. The command builder later copies every TEXT view into its owned flat text buffer. |
| failure | Unsupported categories throw invalid_document/resource_limit, while Date/InlineDecimal parsers may reject malformed typed text. Error construction occurs on failure; no catch/retry is added. |
| cost | Visits one scalar and its text extent for the relevant check/parse. The reader deliberately performs a validation pass and a later materialization pass; JSON parser allocations are outside MemoryAccount. |
| Design | [docs/sql_aggregate_input.md §One atomic JSONL command](../../../../sql_aggregate_input.md), [docs/sql_aggregate_input.md §Ownership, failure and cost](../../../../sql_aggregate_input.md), [docs/aggregates.md §SQL and numeric contract](../../../../aggregates.md), [docs/sql_aggregate_records.md §Wire contract](../../../../sql_aggregate_records.md), [docs/query_memory.md §Boundaries](../../../../query_memory.md), [schemas/sql-aggregate-input-v1.schema.json](../../../../../schemas/sql-aggregate-input-v1.schema.json) |

## B0009

[Lines 60–66](../../../../../src/io/sql_aggregate_input.cpp#L60); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
const frontend::SqlRowsSource& source(const frontend::SqlAggregateProgram& program,const Json& name) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Resolve a JSON replacement table name to an exact physical source in the genuine aggregate program. |
| inputs / outputs | Reads the required string name and returns a borrowed SqlRowsSource reference from the frozen program’s source program. |
| invariants | Resolution is exact physical source-name matching; an SQL alias or unrelated name does not bind. Program identity is checked separately against the envelope binding hash. |
| ownership | The returned source borrows program-owned immutable schema metadata; the Json name borrows DOM text only during the comparison. |
| failure | A missing/unknown or non-string physical name is rejected; unknown names use unknown_table. No fallback or table creation occurs. |
| cost | Linear scan over the program’s physical source list for each lookup. next() resolves each replacement during both validation and copy passes. |
| Design | [docs/sql_aggregate_input.md §One atomic JSONL command](../../../../sql_aggregate_input.md), [docs/sql_aggregate_input.md §Ownership, failure and cost](../../../../sql_aggregate_input.md), [docs/aggregates.md §Logical input and publication](../../../../aggregates.md) |

## B0010

[Lines 67–68](../../../../../src/io/sql_aggregate_input.cpp#L67); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L67-L68:sha256:c929980d95efc152dc886ac42af0f045075441dd18a8f886364828ead327bbd3
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Closes the anonymous namespace at this source boundary; this is a lexical delimiter, not an operation. |
| inputs / outputs | No runtime input or output. Declarations following the span leave the preceding C++ scope. |
| invariants | The delimiter ends the preceding scope's visibility/linkage region; it adds no validation, publication, ownership transfer, or runtime authority. |
| ownership | The delimiter adds no owner. If it ends a function/block with live automatic objects, their normal destructors release those objects; namespace and type-definition closes change no existing object's lifetime. |
| failure | No explicit failure translation or catch is added. If a function/block exit destroys automatic objects, exception behavior follows those destructors; namespace/type closes have no runtime failure path. |
| cost | The delimiter adds no algorithmic work. A function/block exit can run existing automatic-object destructors and cleanup; namespace/type closes have no runtime cost. |
| Design | [src/io/sql_aggregate_input.cpp](../../../../../src/io/sql_aggregate_input.cpp), [docs/code_specs/files/src/io/sql_aggregate_input.cpp.md](sql_aggregate_input.cpp.md), [docs/sql_aggregate_input.md](../../../../sql_aggregate_input.md), [docs/sql_aggregate_records.md](../../../../sql_aggregate_records.md) |

## B0011

[Lines 69–84](../../../../../src/io/sql_aggregate_input.cpp#L69); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct SqlAggregateJsonCommand::Data {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Store the private flat owners that back one decoded command and every InputView borrow. |
| inputs / outputs | Stores command sequence and reader position, account-allocated text/cell/replacement vectors and optional source position. copy() appends borrowed text and returns a view into the flat buffer. |
| invariants | Cell string views, SourcePosition text and replacement spans refer to these owned vectors. The builder reserves validated total extents before filling so backing arrays remain stable for the returned command. |
| ownership | Data is itself held by AccountedUnique; its vectors use the supplied receiving account with scratch purpose. No Json DOM is retained. |
| failure | Account failure while creating/reserving/filling propagates; partially constructed owners unwind and release funded buffers. There is no catch that publishes incomplete command state. |
| cost | Retained payload is O(TEXT/source bytes + cells + replacements), plus actual vector capacity and owner request. Appending/copying touches input text; no whole source document mirror is kept. |
| Design | [docs/sql_aggregate_input.md §Ownership, failure and cost](../../../../sql_aggregate_input.md), [docs/sql_aggregate_records.md §Ownership, failure and cost](../../../../sql_aggregate_records.md), [docs/query_memory.md §Boundaries](../../../../query_memory.md) |

## B0012

[Lines 85–103](../../../../../src/io/sql_aggregate_input.cpp#L85); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct SqlAggregateJsonlReader::Data {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Keep reader-owned stream/schema/progress state, an accounted raw-line buffer and poison/EOF flags. |
| inputs / outputs | Data retains a stream reference, account, frozen genuine program, limits, logged W, ReaderPosition, line vector and poison/ended flags; construction checks record-limit representability and origin consistency. |
| invariants | Origin byte and record counters must be within configured cumulative caps, records may not exceed logged W, and byte/record zero-ness must agree. The stream is borrowed, not owned; poison prevents retry after partial consumption. |
| ownership | The account and frozen program are retained by the reader; line storage uses the account’s scratch allocator. The caller owns stream lifetime and its physical positioning. |
| failure | Invalid cap/origin fails construction. next() sets poison before reading and clears it only after complete success or clean EOF; thrown errors leave the progress position unchanged and require reopen. |
| cost | Reader owner plus retained raw-line capacity consume receiving-account requests. Program freezing may retain metadata under that account; the parser DOM created later is separate ordinary workspace. |
| Design | [docs/sql_aggregate_input.md §Ownership, failure and cost](../../../../sql_aggregate_input.md), [docs/sql_aggregate_session.md §State and command usage](../../../../sql_aggregate_session.md), [docs/sql_aggregate_session.md §Recovery and failure boundaries](../../../../sql_aggregate_session.md), [docs/sql_aggregate_session.md §Resource and performance scope](../../../../sql_aggregate_session.md), [docs/query_memory.md §Boundaries](../../../../query_memory.md) |

## B0014

[Lines 105–105](../../../../../src/io/sql_aggregate_input.cpp#L105); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
SqlAggregateJsonCommand::SqlAggregateJsonCommand(resource::AccountedUnique<Data> data) noexcept:data_(std::move(data)) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Transfer the already built private command owner into the public move-only facade. |
| inputs / outputs | Consumes an AccountedUnique&lt;Data&gt; and moves it into data_; it creates no new command payload. |
| invariants | The constructor is noexcept and leaves the backing heap addresses under the facade’s ownership. |
| ownership | Ownership of Data and its account-backed buffers moves from the caller’s unique owner to the command. |
| failure | No validation or diagnostic path is present here; failures happen during the earlier funded build. |
| cost | Constant-time ownership transfer; no payload copy or new allocation is performed by this body. |
| Design | [docs/sql_aggregate_input.md §Ownership, failure and cost](../../../../sql_aggregate_input.md), [docs/sql_aggregate_records.md §Ownership, failure and cost](../../../../sql_aggregate_records.md) |

## B0015

[Lines 106–108](../../../../../src/io/sql_aggregate_input.cpp#L106); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L106-L108:sha256:5c48a64af33867a3d2081c8b9a0c6e8d4fbaa52ac694c5724f4b4082f41fef28
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Defines the out-of-line default destructor and noexcept move operations for SqlAggregateJsonCommand; ownership moves with data_ and destruction releases its accounted owner. |
| inputs / outputs | Defaulted special members destroy or move the private data_ handle; move construction/assignment accepts the same wrapper type and returns the destination object. |
| invariants | Moves transfer the existing private owner; a moved-from wrapper has no usable reader/command state. |
| ownership | The resource::AccountedUnique owner is transferred; replacement/destruction releases any previously held state through its owner. |
| failure | These special members add no translation or recovery catch. Constructor allocation and reader/command operation failures remain at their explicit factory/call sites. |
| cost | No wrapper-level allocation; moves/destruction perform the contained owner transfer or cleanup. |
| Design | [src/io/sql_aggregate_input.cpp](../../../../../src/io/sql_aggregate_input.cpp), [docs/code_specs/files/src/io/sql_aggregate_input.cpp.md](sql_aggregate_input.cpp.md), [docs/sql_aggregate_input.md](../../../../sql_aggregate_input.md), [docs/sql_aggregate_records.md](../../../../sql_aggregate_records.md) |

## B0016

[Lines 109–112](../../../../../src/io/sql_aggregate_input.cpp#L109); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
ar::InputView SqlAggregateJsonCommand::view() const & {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Expose a synchronous borrowed recovery InputView from a live command owner. |
| inputs / outputs | Returns sequence, replacement span, optional source position and reader continuation from Data. |
| invariants | The view does not own any buffers and remains valid only while the command’s backing Data lives and is not moved/destroyed. The API deletes rvalue view() to prevent immediate dangling borrows. |
| ownership | All referenced text and cell/replacement storage remains owned by the command’s Data. |
| failure | Moved-from/no-data command throws invalid_input_state. Error diagnostics may allocate only on that failure path. |
| cost | Constant-size metadata/span construction; it does not duplicate rows or text. |
| Design | [docs/sql_aggregate_input.md §One atomic JSONL command](../../../../sql_aggregate_input.md), [docs/sql_aggregate_input.md §Ownership, failure and cost](../../../../sql_aggregate_input.md), [docs/sql_aggregate_records.md §Wire contract](../../../../sql_aggregate_records.md), [docs/sql_aggregate_records.md §Ownership, failure and cost](../../../../sql_aggregate_records.md) |

## B0017

[Lines 113–116](../../../../../src/io/sql_aggregate_input.cpp#L113); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
SqlAggregateJsonlReader::SqlAggregateJsonlReader(std::istream& stream,const resource::MemoryAccount& account,
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Create reader state from a caller-positioned stream, receiving account and genuine program. |
| inputs / outputs | Forwards stream, account, program, logged W, origin and limits into an AccountedUnique reader Data owner tagged scratch. |
| invariants | The stream must already be at origin.bytes. The program is frozen into the receiving account; origin and limit validation occurs in Data construction. |
| ownership | Reader owns its private Data/account/schema and line buffer, but borrows the stream. No command is produced until next(). |
| failure | Owner allocation, program freeze or invalid origin/cap may fail; construction propagates rather than returning a partial reader. |
| cost | Construction funds one reader owner and whatever metadata freeze requires; existing same-account immutable data may be shared. It does not parse the JSONL input yet. |
| Design | [docs/sql_aggregate_input.md §Ownership, failure and cost](../../../../sql_aggregate_input.md), [docs/sql_aggregate_input.md §Workflow](../../../../sql_aggregate_input.md), [docs/query_memory.md §Boundaries](../../../../query_memory.md) |

## B0018

[Lines 117–119](../../../../../src/io/sql_aggregate_input.cpp#L117); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L117-L119:sha256:0e7d99980b61db0ed9956181c18dd89f7e19fd04c916caf66adf63dd9905b094
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Defines the out-of-line default destructor and noexcept move operations for SqlAggregateJsonlReader; moving transfers its private reader state and destruction releases it. |
| inputs / outputs | Defaulted special members destroy or move the private data_ handle; move construction/assignment accepts the same wrapper type and returns the destination object. |
| invariants | Moves transfer the existing private owner; a moved-from wrapper has no usable reader/command state. |
| ownership | The resource::AccountedUnique owner is transferred; replacement/destruction releases any previously held state through its owner. |
| failure | These special members add no translation or recovery catch. Constructor allocation and reader/command operation failures remain at their explicit factory/call sites. |
| cost | No wrapper-level allocation; moves/destruction perform the contained owner transfer or cleanup. |
| Design | [src/io/sql_aggregate_input.cpp](../../../../../src/io/sql_aggregate_input.cpp), [docs/code_specs/files/src/io/sql_aggregate_input.cpp.md](sql_aggregate_input.cpp.md), [docs/sql_aggregate_input.md](../../../../sql_aggregate_input.md), [docs/sql_aggregate_records.md](../../../../sql_aggregate_records.md) |

## B0019

[Lines 120–120](../../../../../src/io/sql_aggregate_input.cpp#L120); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
bool SqlAggregateJsonlReader::requires_reopen() const noexcept {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Report whether the reader is moved-from or poisoned after an incomplete/failed operation. |
| inputs / outputs | Returns true when Data is absent or its poison flag is set; otherwise false. |
| invariants | A false value does not mean a command has been logged, decided or delivered. Clean EOF remains a healthy reader state. |
| ownership | Reads its own Data flag; it returns no borrowed data. |
| failure | The accessor is noexcept and has no failure branch. |
| cost | Constant-time flag read. |
| Design | [docs/sql_aggregate_input.md §Ownership, failure and cost](../../../../sql_aggregate_input.md), [docs/sql_aggregate_session.md §State and command usage](../../../../sql_aggregate_session.md), [docs/sql_aggregate_session.md §Recovery and failure boundaries](../../../../sql_aggregate_session.md) |

## B0020

[Lines 121–123](../../../../../src/io/sql_aggregate_input.cpp#L121); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
ar::ReaderPosition SqlAggregateJsonlReader::position() const {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Expose the byte/record position last published by a successful decode or the supplied origin. |
| inputs / outputs | Returns the stored ReaderPosition pair when Data exists and is not poisoned. |
| invariants | Position is not the current stream tell position and does not advance on a failed next(). It counts logical consumed record bytes including line terminators only after publication. |
| ownership | Returns a fixed value copy; it borrows no stream or buffer. |
| failure | Moved-from or poisoned reader throws invalid_input_state; the owning diagnostic is a failure-path allocation. |
| cost | Constant-size value return. |
| Design | [docs/sql_aggregate_input.md §Ownership, failure and cost](../../../../sql_aggregate_input.md), [docs/sql_aggregate_session.md §State and command usage](../../../../sql_aggregate_session.md), [docs/sql_aggregate_session.md §Recovery and failure boundaries](../../../../sql_aggregate_session.md), [apps/crown/aggregate.cpp §run reader/session loop, lines 167–190](../../../../../apps/crown/aggregate.cpp) |

## B0022

[Lines 125–199](../../../../../src/io/sql_aggregate_input.cpp#L125); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::optional<SqlAggregateJsonCommand> SqlAggregateJsonlReader::next() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Frame, parse, bind and validate one JSONL record, then publish an owning physical command and continuation. |
| inputs / outputs | Consumes bytes through one LF or EOF; accepts CRLF and a final unterminated JSON object, rejects blank records, and checks cumulative bytes/records, W+1, binding hash, strict keys, physical source/schema version, full row arity/types, scalar tags/limits and optional source position. On success it returns a funded command and advances reader position/logged sequence; clean EOF returns empty. |
| invariants | Poison is set before consuming input. Progress is updated only after validation, exact sizing, command funding and materialization complete. A rejected transport command does not create a Session Reject or decide native state. Source before/after weights are parsed here; current-weight and aggregate arithmetic remain Session/native decisions. |
| ownership | Raw line and returned flat command buffers use the receiving account. JSON DOM, duplicate-key tracking and parser workspace from read_json use ordinary storage; command TEXT is copied out before DOM destruction. The input stream remains borrowed. |
| failure | Read, cap, parse, binding, type, progress or allocation errors propagate and leave requires_reopen true. The method has no catch/retry; callers reopen from durable W/reader progress. A clean empty EOF clears poison, marks ended and is repeatable. |
| cost | Framing is byte-linear; validation/materialization scan fields and cells in two passes and each replacement resolves a source by linear source-list search. Reader line capacity and command extents are charged by actual receiving-account requests; DOM workspace is excluded. No CPU/delay theorem is asserted. |
| Design | [docs/sql_aggregate_input.md §One atomic JSONL command](../../../../sql_aggregate_input.md), [docs/sql_aggregate_input.md §Ownership, failure and cost](../../../../sql_aggregate_input.md), [src/io/document.cpp §read_json definition, lines 19–20](../../../../../src/io/document.cpp), [apps/crown/aggregate.cpp §run reader/session loop, lines 167–190](../../../../../apps/crown/aggregate.cpp), [docs/sql_aggregate_session.md §State and command usage](../../../../sql_aggregate_session.md), [docs/sql_aggregate_session.md §Resource and performance scope](../../../../sql_aggregate_session.md), [docs/query_memory.md §Boundaries](../../../../query_memory.md), [apps/crown/aggregate.cpp §seek continuation line-boundary guard, lines 141–155](../../../../../apps/crown/aggregate.cpp) |

## B0023

[Lines 200–200](../../../../../src/io/sql_aggregate_input.cpp#L200); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L200-L200:sha256:39c2bd587239794e92def2b2ebc5cce8f0acd397d817bceec761a8f61bea3e66
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Closes the namespace crown::io at this source boundary; this is a lexical delimiter, not an operation. |
| inputs / outputs | No runtime input or output. Declarations following the span leave the preceding C++ scope. |
| invariants | The delimiter ends the preceding scope's visibility/linkage region; it adds no validation, publication, ownership transfer, or runtime authority. |
| ownership | The delimiter adds no owner. If it ends a function/block with live automatic objects, their normal destructors release those objects; namespace and type-definition closes change no existing object's lifetime. |
| failure | No explicit failure translation or catch is added. If a function/block exit destroys automatic objects, exception behavior follows those destructors; namespace/type closes have no runtime failure path. |
| cost | The delimiter adds no algorithmic work. A function/block exit can run existing automatic-object destructors and cleanup; namespace/type closes have no runtime cost. |
| Design | [src/io/sql_aggregate_input.cpp](../../../../../src/io/sql_aggregate_input.cpp), [docs/code_specs/files/src/io/sql_aggregate_input.cpp.md](sql_aggregate_input.cpp.md), [docs/sql_aggregate_input.md](../../../../sql_aggregate_input.md), [docs/sql_aggregate_records.md](../../../../sql_aggregate_records.md) |
