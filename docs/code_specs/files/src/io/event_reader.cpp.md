# `src/io/event_reader.cpp` — block usage map

[Source](../../../../../src/io/event_reader.cpp) · [Source index](../../../README.md) · [Subsystem contracts](../../../subsystem_contracts.md) · [Reviewed primitives](../../../primitives.md)

Decode bounded stream records into funded native updates while retaining input progress.

Snapshot SHA-256: `ee8efb9492551bcfb5e8a55739d216302818425311d16202659f6f6b94652b45`. 555 lines partitioned into 52 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [io](../../../subsystem_contracts.md#io). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/ingestion.md](../../../../ingestion.md), [docs/query_identity.md](../../../../query_identity.md), [docs/schema_evolution.md](../../../../schema_evolution.md), [docs/cli.md](../../../../cli.md), [docs/query_memory.md](../../../../query_memory.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–16](../../../../../src/io/event_reader.cpp#L1) | Imports dependencies; declares namespace scope. |  · [reviewed contract](#b0001) |
| [B0002 · 17–19](../../../../../src/io/event_reader.cpp#L17) | Callable definition: void require(bool ok,std::string_view code,std::string_view message) | calls Error, std::string; guard void require(bool ok,std::string_view code,std::string_view message) { · [reviewed contract](#b0002) |
| [B0003 · 20–20](../../../../../src/io/event_reader.cpp#L20) | Callable definition: void bounded(std::size_t size,std::size_t limit,std::string_view message) | calls require; guard void bounded(std::size_t size,std::size_t limit,std::string_view message) {require(size&lt;=limit,"res… · [reviewed contract](#b0003) |
| [B0004 · 21–23](../../../../../src/io/event_reader.cpp#L21) | Callable definition: std::size_t sum(std::size_t a,std::size_t b) | calls require, max; guard require(b&lt;=std::numeric_limits&lt;std::size_t&gt;::max()-a,"resource_limit","input size accounting exhaus…; returns a+b · [reviewed contract](#b0004) |
| [B0005 · 24–24](../../../../../src/io/event_reader.cpp#L24) | Callable definition: \[\[noreturn\]\] void invalid_document(const char* message) | calls Error · [reviewed contract](#b0005) |
| [B0006 · 25–25](../../../../../src/io/event_reader.cpp#L25) | Callable definition: \[\[noreturn\]\] void resource_limit(const char* message) | calls Error · [reviewed contract](#b0006) |
| [B0007 · 26–26](../../../../../src/io/event_reader.cpp#L26) | Callable definition: \[\[noreturn\]\] void invalid_scalar(const char* message) | calls Error · [reviewed contract](#b0007) |
| [B0008 · 27–31](../../../../../src/io/event_reader.cpp#L27) | Callable definition: void source_name(std::string_view name,const InputLimits& limits) | calls bounded, size, require, empty; guard bounded(name.size(),limits.source_bytes,"input source identifier exceeds its byte limit"); · [reviewed contract](#b0008) |
| [B0009 · 32–34](../../../../../src/io/event_reader.cpp#L32) | Callable definition: const auto& table_at(const auto& catalog,TableId id) | calls require, size; guard require(id.value&lt;catalog.tables.size(),"unknown_table","physical input table ID is outside the cata…; returns catalog.tables\[id.value\] · [reviewed contract](#b0009) |
| [B0010 · 35–35](../../../../../src/io/event_reader.cpp#L35) | declares aliases. |  · [reviewed contract](#b0010) |
| [B0011 · 36–66](../../../../../src/io/event_reader.cpp#L36) | Callable definition: std::int64_t parse_int64(std::string_view text) | calls empty, invalid_scalar, size, max; returns static_cast&lt;std::int64_t&gt;(magnitude); std::numeric_limits&lt;std::int64_t&gt;::min(); 1 loop sites · [reviewed contract](#b0011) |
| [B0012 · 67–67](../../../../../src/io/event_reader.cpp#L67) | Explanatory comments or spacing. |  |
| [B0013 · 68–172](../../../../../src/io/event_reader.cpp#L68) | Callable definition: template&lt;class Read&gt; std::optional&lt;input_detail::Vector&lt;resource::AccountedText&gt;&gt; read_delimited_native(const resource::MemoryAcc… | calls Error, fields, field, read; returns std::nullopt; value; growth copy_of, push_back; 1 loop sites · [reviewed contract](#b0013) |
| [B0014 · 173–173](../../../../../src/io/event_reader.cpp#L173) | Explanatory comments or spacing. |  |
| [B0015 · 174–195](../../../../../src/io/event_reader.cpp#L174) | Callable definition: storage::ScalarView read_native_cell(std::string_view text,const auto& column,const InputLimits& limits) | calls bounded, size, require_utf8, parse_int64; guard bounded(text.size(),limits.field_bytes,"decoded text cell exceeds configured byte limit");require_u…; returns parse_int64(text); text · [reviewed contract](#b0015) |
| [B0016 · 196–211](../../../../../src/io/event_reader.cpp#L196) | declares types or opens a type body; declares values/defaults or compile-time conditions. | source comment (unverified): // namespace · [reviewed contract](#b0016) |
| [B0017 · 212–217](../../../../../src/io/event_reader.cpp#L212) | Callable definition: template&lt;class Progress&gt; Data(const resource::MemoryAccount& memory,std::istream& stream,CatalogSource schema, const AccountedInp… | calls account, input, catalog, std::move · [reviewed contract](#b0017) |
| [B0018 · 218–262](../../../../../src/io/event_reader.cpp#L218) | Callable definition: static void initialize(const auto& catalog,const AccountedInputOptions::Values& options,const AccountedInputProgress& progress) | calls require, empty, bounded, size; guard require(format==InputFormat::jsonl \|\| format==InputFormat::binary \|\| format==InputFormat::csv \|\|; growth insert; 2 loop sites · [reviewed contract](#b0018) |
| [B0019 · 263–280](../../../../../src/io/event_reader.cpp#L263) | Callable definition: std::optional&lt;char&gt; byte() | calls peek, eof, bad, Error; guard require(input-&gt;eof() && !input-&gt;bad(),"input_io_error","input stream failed before clean EOF"); ret…; returns {}; {}; source comment (unverified): // Throwing streams can signal clean EOF; real I/O errors retain their category. · [reviewed contract](#b0019) |
| [B0020 · 281–297](../../../../../src/io/event_reader.cpp#L281) | Callable definition: std::optional&lt;input_detail::Buffer&gt; line() | calls value, bounded, sum, size; guard bounded(sum(value.size(),1),options.limits.record_bytes,"JSONL input record exceeds its byte limit"…; returns value; any?std::optional&lt;input_detail::Buffer&gt;{std::move(value)}:std::nullopt; growth push_back; 1 loop sites; source comment (unverified): // A single LF or CRLF frames the JSON object and is not part of its · [reviewed contract](#b0020) |
| [B0021 · 298–318](../../../../../src/io/event_reader.cpp#L298) | Callable definition: std::optional&lt;input_detail::Buffer&gt; frame() | calls byte, bounded, data, push_back; guard bounded(header_size,options.limits.record_bytes,"binary header exceeds record limit");; returns {}; value; growth push_back, reserve; 3 loop sites; source comment (unverified): // All header-view reads finish before reserve can relocate its bytes. · [reviewed contract](#b0021) |
| [B0022 · 319–322](../../../../../src/io/event_reader.cpp#L319) | Callable definition: std::uint64_t offset() const | calls require, max; guard require(bytes&lt;=std::numeric_limits&lt;std::uint64_t&gt;::max()-options.byte_offset,"resource_limit","inpu…; returns options.byte_offset+bytes · [reviewed contract](#b0022) |
| [B0023 · 323–326](../../../../../src/io/event_reader.cpp#L323) | Callable definition: std::uint64_t next_sequence() const | calls require, max; guard require(progress.sequence!=std::numeric_limits&lt;std::uint64_t&gt;::max(),"sequence_overflow","physical …; returns progress.sequence+1 · [reviewed contract](#b0023) |
| [B0024 · 327–395](../../../../../src/io/event_reader.cpp#L327) | Callable definition: std::optional&lt;input_detail::Decoded&gt; delimited(const auto& catalog) | calls offset, sum, read_delimited_native, byte; guard require(nullary \|\| record-&gt;size()==columns.size(),"invalid_document","CSV header must name every ph…; returns byte(); {}; growth copy_of, insert, push_back, reserve; 3 loop sites; source comment (unverified): // Explicit one-time header mapping scans names per column (O(C^2)). · [reviewed contract](#b0024) |
| [B0025 · 396–397](../../../../../src/io/event_reader.cpp#L396) | Explanatory comments or spacing. | source comment (unverified): // Prepare a new source node before engine work; accepted offsets stay unchanged · [reviewed contract](#b0025) |
| [B0026 · 398–406](../../../../../src/io/event_reader.cpp#L398) | Callable definition: void order(const InputEventView& event) | calls require, next_sequence, find, end; guard require(event.update.sequence==next_sequence(),"invalid_sequence","physical input sequence must be …; source comment (unverified): // Prepare a new source node before engine work; accepted offsets stay unchanged · [reviewed contract](#b0026) |
| [B0027 · 407–407](../../../../../src/io/event_reader.cpp#L407) | Closes surrounding scope/type. |  · [reviewed contract](#b0027) |
| [B0028 · 408–409](../../../../../src/io/event_reader.cpp#L408) | Callable definition: EventReader::EventReader(std::istream& input,CatalogSource catalog,InputOptions options,InputProgress progress) :EventReader(reso… | calls EventReader, resource::MemoryAccount::create, max, std::move · [reviewed contract](#b0028) |
| [B0029 · 410–411](../../../../../src/io/event_reader.cpp#L410) | Callable definition: EventReader::EventReader(const resource::MemoryAccount& account,std::istream& input,CatalogSource catalog,InputOptions options,In… | calls EventReader, std::move, AccountedInputOptions · [reviewed contract](#b0029) |
| [B0030 · 412–414](../../../../../src/io/event_reader.cpp#L412) | Callable definition: EventReader::EventReader(const resource::MemoryAccount& account,std::istream& input,CatalogSource catalog,const AccountedInputOpt… | calls data_, std::move; growth make_accounted_unique · [reviewed contract](#b0030) |
| [B0031 · 415–415](../../../../../src/io/event_reader.cpp#L415) | declares callable signatures; declares values/defaults or compile-time conditions. |  · [reviewed contract](#b0031) |
| [B0032 · 416–418](../../../../../src/io/event_reader.cpp#L416) | Callable definition: void EventReader::validate_options(const CatalogSource& catalog,const AccountedInputOptions& options,const AccountedInputProgress… | calls catalog_source_detail::read, Data::initialize, get · [reviewed contract](#b0032) |
| [B0033 · 419–443](../../../../../src/io/event_reader.cpp#L419) | Callable definition: EventReader::EventReader(const resource::MemoryAccount& account,std::istream& input,CatalogSource catalog, const ReaderCheckpoint… | calls data_, positions, get, options; guard checkpoint_detail::require(state.csv_fields.size()&lt;=budget.limits.csv_fields,recovery::ImageFault::…; returns table_at(schema,*result-&gt;options.table).columns.size(); result; growth make_accounted_unique; 2 loop sites · [reviewed contract](#b0033) |
| [B0034 · 444–444](../../../../../src/io/event_reader.cpp#L444) | Callable definition: ReaderCheckpoint EventReader::checkpoint_state() const | calls checkpoint_state; returns checkpoint_state(SourceStateLimits{}) · [reviewed contract](#b0034) |
| [B0035 · 445–454](../../../../../src/io/event_reader.cpp#L445) | Callable definition: ReaderCheckpoint EventReader::checkpoint_state(const SourceStateLimits& limits) const | calls checkpoint_detail::require, bool, positions, options; guard checkpoint_detail::require(bool(data_));const auto& d=*data_;; returns result · [reviewed contract](#b0035) |
| [B0036 · 455–456](../../../../../src/io/event_reader.cpp#L455) | declares callable signatures; declares values/defaults or compile-time conditions. |  · [reviewed contract](#b0036) |
| [B0037 · 457–476](../../../../../src/io/event_reader.cpp#L457) | Callable definition: const InputEventView* EventReader::peek() | calls require, bool, line, input_detail::decode_json; guard require(bool(data_),"invalid_input_reader","moved-from physical input reader");auto& d=*data_;; returns &d.cached-&gt;event; nullptr; growth emplace; source comment (unverified): // Failure during peek preparation may follow byte consumption. Only a complete · [reviewed contract](#b0037) |
| [B0038 · 477–478](../../../../../src/io/event_reader.cpp#L477) | Explanatory comments or spacing. | source comment (unverified): // No input read or allocation: publish only the already prepared acceptance. · [reviewed contract](#b0038) |
| [B0039 · 479–484](../../../../../src/io/event_reader.cpp#L479) | Callable definition: void EventReader::acknowledge() noexcept | calls publish, reset; source comment (unverified): // No input read or allocation: publish only the already prepared acceptance. · [reviewed contract](#b0039) |
| [B0040 · 485–536](../../../../../src/io/event_reader.cpp#L485) | Callable definition: std::uint64_t EventReader::stage_replay(const InputEventView& event,ReaderPositionView position,const SourceStateLimits& limits) | calls require, bool, checkpoint_detail::replay_input, size; guard require(bool(data_));auto& d=*data_;require(!d.cached && !d.broken && !d.ended);; returns entry.second==event.update.table; budget.used; growth copy_of, emplace, insert; 3 loop sites; source comment (unverified): // delimiters plus mandatory header terminator · [reviewed contract](#b0040) |
| [B0041 · 537–540](../../../../../src/io/event_reader.cpp#L537) | Callable definition: ReaderPositionView EventReader::decoder_position() const & | calls require, bool; guard require(bool(data_),"invalid_input_reader","moved-from physical input reader");const auto& d=*data_;; returns {d.bytes,d.records,d.header_read,d.fields} · [reviewed contract](#b0041) |
| [B0042 · 541–541](../../../../../src/io/event_reader.cpp#L541) | Callable definition: bool EventReader::failed() const noexcept | calls ; returns data_ && data_-&gt;broken · [reviewed contract](#b0042) |
| [B0043 · 542–542](../../../../../src/io/event_reader.cpp#L542) | Explanatory comments or spacing. | source comment (unverified): // Move accepted native ownership out; discard cached input without acceptance. · [reviewed contract](#b0043) |
| [B0044 · 543–547](../../../../../src/io/event_reader.cpp#L543) | Callable definition: AccountedInputProgress EventReader::close() noexcept | calls static_assert, std::move, reset; guard static_assert(std::is_nothrow_move_constructible_v&lt;AccountedInputProgress&gt;);; returns {}; result; source comment (unverified): // Move accepted native ownership out; discard cached input without acceptance. · [reviewed contract](#b0044) |
| [B0045 · 548–548](../../../../../src/io/event_reader.cpp#L548) | Callable definition: const AccountedInputProgress& EventReader::progress() const | calls require, bool; guard const AccountedInputProgress& EventReader::progress() const {require(bool(data_),"invalid_input_rea…; returns data_-&gt;progress · [reviewed contract](#b0045) |
| [B0046 · 549–549](../../../../../src/io/event_reader.cpp#L549) | Callable definition: const CatalogSource& EventReader::catalog() const | calls require, bool; guard const CatalogSource& EventReader::catalog() const {require(bool(data_),"invalid_input_reader","move…; returns data_-&gt;catalog · [reviewed contract](#b0046) |
| [B0047 · 550–550](../../../../../src/io/event_reader.cpp#L550) | Callable definition: std::string_view EventReader::catalog_sha256() const | calls require, bool, view; guard std::string_view EventReader::catalog_sha256() const {require(bool(data_),"invalid_input_reader","m…; returns data_-&gt;fingerprint.view() · [reviewed contract](#b0047) |
| [B0048 · 551–551](../../../../../src/io/event_reader.cpp#L551) | Callable definition: const resource::MemoryAccount& EventReader::account() const | calls require, bool; guard const resource::MemoryAccount& EventReader::account() const {require(bool(data_),"invalid_input_rea…; returns data_-&gt;account · [reviewed contract](#b0048) |
| [B0049 · 552–552](../../../../../src/io/event_reader.cpp#L552) | Callable definition: const AccountedInputOptions& EventReader::native_options() const & | calls require, bool; guard const AccountedInputOptions& EventReader::native_options() const & {require(bool(data_),"invalid_in…; returns data_-&gt;retained_options · [reviewed contract](#b0049) |
| [B0050 · 553–553](../../../../../src/io/event_reader.cpp#L553) | Callable definition: std::uint64_t EventReader::bytes_read() const | calls require, bool; guard std::uint64_t EventReader::bytes_read() const {require(bool(data_),"invalid_input_reader","moved-fr…; returns data_-&gt;bytes · [reviewed contract](#b0050) |
| [B0051 · 554–554](../../../../../src/io/event_reader.cpp#L554) | Callable definition: std::uint64_t EventReader::records_read() const | calls require, bool; guard std::uint64_t EventReader::records_read() const {require(bool(data_),"invalid_input_reader","moved-…; returns data_-&gt;records · [reviewed contract](#b0051) |
| [B0052 · 555–555](../../../../../src/io/event_reader.cpp#L555) | Closes surrounding scope/type. | source comment (unverified): // namespace crown::io · [reviewed contract](#b0052) |

## B0001

[Lines 1–16](../../../../../src/io/event_reader.cpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L1-L16:sha256:636c0c962e3f2228d3d638567e04348b484b0fae4018e24015d5a2e1c64fc09d
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Imports compile-time dependencies (crown/io/ingest.hpp, crown/io/input_options.hpp, native_input.hpp, checkpoint_detail.hpp, input_native.hpp, catalog_source.hpp) and opens crown::io scope for the declarations or definitions that follow. |
| inputs / outputs | No runtime inputs/outputs are declared by the import/scope lines themselves. |
| invariants | The listed headers and namespace membership determine compile-time name availability; any API behavior belongs to the declarations/definitions that follow. |
| ownership | No object ownership is created by the imports or namespace tokens. |
| failure | No runtime failure path. Missing/incompatible dependencies or a violated compile-time constraint fail translation/linking. |
| cost | Compile/preprocessor work only; no new per-operation runtime overhead. |
| Design | [src/io/event_reader.cpp](../../../../../src/io/event_reader.cpp), [docs/code_specs/files/src/io/event_reader.cpp.md](event_reader.cpp.md), [docs/ingestion.md](../../../../ingestion.md), [docs/session_lifecycle.md](../../../../session_lifecycle.md) |

## B0002

[Lines 17–19](../../../../../src/io/event_reader.cpp#L17); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void require(bool ok,std::string_view code,std::string_view message)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Raise a public input diagnostic only when an explicit predicate fails. |
| inputs / outputs | Condition plus code/message in; successful condition returns, false constructs and throws Error. |
| invariants | Failure construction may use ordinary diagnostic strings; this is not a catch, rollback layer, MemoryAccount refill or successful-row allocation. |
| ownership | Borrows stable caller input/catalog synchronously; only local private parser/output state changes. No physical runtime, accepted source sequence or source position is published here. |
| failure | False throws the supplied public category/message; diagnostic construction itself can fail allocation. No local exception translation. |
| cost | Fixed successful branch; failure construction/copy/throw costs are separate. |
| Design | [include/crown/io/ingest.hpp](../../../../../include/crown/io/ingest.hpp), [docs/ingestion.md](../../../../ingestion.md) |

## B0003

[Lines 20–20](../../../../../src/io/event_reader.cpp#L20); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void bounded(std::size_t size,std::size_t limit,std::string_view message)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Enforce one inclusive input-size ceiling. |
| inputs / outputs | Observed size and limit in; success iff size &lt;= limit, otherwise resource_limit. |
| invariants | Equal boundary is admitted. The caller chooses bytes/columns/sources; this helper does not infer memory usage or charge engine work. |
| ownership | Borrows stable caller input/catalog synchronously; only local private parser/output state changes. No physical runtime, accepted source sequence or source position is published here. |
| failure | Validation, scalar, size, encoding or allocation errors propagate; local owned scratch is released by RAII. No partial public event/text or accepted source progress is returned. |
| cost | Fixed comparison plus failure-only diagnostic construction. |
| Design | [include/crown/io/ingest.hpp](../../../../../include/crown/io/ingest.hpp), [docs/ingestion.md](../../../../ingestion.md) |

## B0004

[Lines 21–23](../../../../../src/io/event_reader.cpp#L21); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::size_t sum(std::size_t a,std::size_t b)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Add input sizes without wrapping size_t. |
| inputs / outputs | Two nonnegative sizes yield their exact sum after subtraction-based overflow admission. |
| invariants | Rejects arithmetic exhaustion as resource_limit before an unsafe sum; unrelated caps remain the caller responsibility. |
| ownership | Borrows stable caller input/catalog synchronously; only local private parser/output state changes. No physical runtime, accepted source sequence or source position is published here. |
| failure | Validation, scalar, size, encoding or allocation errors propagate; local owned scratch is released by RAII. No partial public event/text or accepted source progress is returned. |
| cost | Fixed arithmetic/branch, no successful allocation. |
| Design | [include/crown/io/ingest.hpp](../../../../../include/crown/io/ingest.hpp), [docs/ingestion.md](../../../../ingestion.md) |

## B0005

[Lines 24–24](../../../../../src/io/event_reader.cpp#L24); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
[[noreturn]] void invalid_document(const char* message)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Reject delimited grammar/framing failure with its public category. |
| inputs / outputs | Always throws invalid_document using supplied diagnostic text. |
| invariants | A direct failure helper, not exception-based successful control flow or a recovery framework. |
| ownership | Borrows stable caller input/catalog synchronously; only local private parser/output state changes. No physical runtime, accepted source sequence or source position is published here. |
| failure | Always throws; enclosing peek makes a consuming-reader failure sticky. |
| cost | Failure-only diagnostic construction and throw. |
| Design | [include/crown/io/ingest.hpp](../../../../../include/crown/io/ingest.hpp), [docs/ingestion.md](../../../../ingestion.md) |

## B0006

[Lines 25–25](../../../../../src/io/event_reader.cpp#L25); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
[[noreturn]] void resource_limit(const char* message)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Reject delimited record/field/column budget failure with its public category. |
| inputs / outputs | Always throws resource_limit using supplied diagnostic text. |
| invariants | A direct failure helper, not exception-based successful control flow or a recovery framework. |
| ownership | Borrows stable caller input/catalog synchronously; only local private parser/output state changes. No physical runtime, accepted source sequence or source position is published here. |
| failure | Always throws; enclosing peek makes a consuming-reader failure sticky. |
| cost | Failure-only diagnostic construction and throw. |
| Design | [include/crown/io/ingest.hpp](../../../../../include/crown/io/ingest.hpp), [docs/ingestion.md](../../../../ingestion.md) |

## B0007

[Lines 26–26](../../../../../src/io/event_reader.cpp#L26); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
[[noreturn]] void invalid_scalar(const char* message)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Reject textual scalar grammar failure with its public category. |
| inputs / outputs | Always throws invalid_scalar using supplied diagnostic text. |
| invariants | A direct failure helper, not exception-based successful control flow or a recovery framework. |
| ownership | Borrows stable caller input/catalog synchronously; only local private parser/output state changes. No physical runtime, accepted source sequence or source position is published here. |
| failure | Always throws; enclosing peek makes a consuming-reader failure sticky. |
| cost | Failure-only diagnostic construction and throw. |
| Design | [include/crown/io/ingest.hpp](../../../../../include/crown/io/ingest.hpp), [docs/ingestion.md](../../../../ingestion.md) |

## B0008

[Lines 27–31](../../../../../src/io/event_reader.cpp#L27); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void source_name(std::string_view name,const InputLimits& limits)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Validate one explicit upstream source identifier. |
| inputs / outputs | Borrowed name must fit source_bytes, be nonempty, contain no NUL and be valid UTF-8. |
| invariants | Names are exact bytes with no case folding/normalization. Offset validity/order is separate; this helper does not retain or advance a source. |
| ownership | Borrows stable caller input/catalog synchronously; only local private parser/output state changes. No physical runtime, accepted source sequence or source position is published here. |
| failure | Validation, scalar, size, encoding or allocation errors propagate; local owned scratch is released by RAII. No partial public event/text or accepted source progress is returned. |
| cost | O(name bytes) for NUL/UTF-8 scans; no successful owning copy. |
| Design | [docs/ingestion.md §Reader acceptance and engine replay](../../../../ingestion.md) |

## B0009

[Lines 32–34](../../../../../src/io/event_reader.cpp#L32); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
const auto& table_at(const auto& catalog,TableId id)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Borrow an existing physical table after checking its dense ID. |
| inputs / outputs | Catalog plus TableId returns a const table reference or unknown_table. |
| invariants | ID is a physical source, not an occurrence alias; reference lifetime remains that of the catalog. |
| ownership | Returns a borrowed table reference; callers keep the supplied catalog owner alive. |
| failure | Out-of-range ID throws unknown_table; no row or source progress changes. |
| cost | Fixed bounds/index access, no successful allocation or catalog revalidation. |
| Design | [include/crown/io/ingest.hpp](../../../../../include/crown/io/ingest.hpp), [docs/ingestion.md](../../../../ingestion.md) |

## B0010

[Lines 35–35](../../../../../src/io/event_reader.cpp#L35); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
using ingest_detail::require_utf8;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Reuse the common strict UTF-8 validator for text-input admission. |
| inputs / outputs | Private alias binds shared encoding validation used by fields/options/source names. |
| invariants | Name binding only; no second decoder, normalization rule, allocation or runtime state. |
| ownership | No owner or storage. |
| failure | No runtime failure in this declaration; called validator owns its diagnostics. |
| cost | Compile-time lookup only. |
| Design | [src/io/ingest_text.hpp](../../../../../src/io/ingest_text.hpp) |

## B0011

[Lines 36–66](../../../../../src/io/event_reader.cpp#L36); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::int64_t parse_int64(std::string_view text)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Parse strict signed decimal int64 text without intermediate owning strings. |
| inputs / outputs | Optional ASCII +/− followed by digits is accumulated with unsigned magnitude and sign-specific bound. |
| invariants | Accepts INT64_MIN exactly; rejects empty/sign-only/non-digit text and overflow before multiply/add. No whitespace trimming, locale or floating conversion. |
| ownership | Borrows stable caller input/catalog synchronously; only local private parser/output state changes. No physical runtime, accepted source sequence or source position is published here. |
| failure | invalid_scalar for grammar and scalar_overflow for range; direct propagation leaves local record unpublished. |
| cost | O(text bytes), fixed inline arithmetic, no successful allocation. |
| Design | [docs/ingestion.md §CSV and explicit legacy profiles](../../../../ingestion.md) |

## B0013

[Lines 68–172](../../../../../src/io/event_reader.cpp#L68); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
template<class Read>
std::optional<input_detail::Vector<resource::AccountedText>> read_delimited_native(const resource::MemoryAccount& account,
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Decode one complete quoted delimited record into funded owning fields. |
| inputs / outputs | Borrowed byte callback, delimiter and limits return optional account-backed field vector; clean initial EOF returns none. |
| invariants | Four finite states handle doubled quotes, embedded quoted newlines, delimiters and LF/CRLF. Outside quoted fields bare CR/trailing junk/quote-in-unquoted reject. Raw bytes include syntax/terminator; decoded field bytes/columns have independent caps and UTF-8 checks. |
| ownership | Returned vector owns AccountedText bytes under supplied account; callback/limits/account references are used synchronously. |
| failure | Read/grammar/size/text/allocation failure unwinds local fields; callback may already have consumed stream bytes, so EventReader.peek must poison continuation. |
| cost | O(raw/decoded record bytes + field count) with account-backed vector/buffer and per-field copies; scratch and retained field blocks overlap temporarily. |
| Design | [docs/ingestion.md §CSV and explicit legacy profiles](../../../../ingestion.md), [docs/ingestion.md §Native reader API and memory grant](../../../../ingestion.md), [docs/memory_accounts.md §Native streaming input ownership](../../../../memory_accounts.md) |

## B0015

[Lines 174–195](../../../../../src/io/event_reader.cpp#L174); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
storage::ScalarView read_native_cell(std::string_view text,const auto& column,const InputLimits& limits)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Decode one text field to the schema exact native scalar alternative. |
| inputs / outputs | Field cap/UTF-8 precede int64/string/bool/date/inline-decimal conversion; decimal must fit declared precision/scale. |
| invariants | String result borrows text; other alternatives are inline. Boolean is exactly true/false. NULL-token rejection occurs in caller before this conversion; no nullable/core coercion or rounding. |
| ownership | Returned string_view remains valid only while the owning delimited field lives; caller freezes a complete compact row before releasing fields. |
| failure | Validation, scalar, size, encoding or allocation errors propagate; local owned scratch is released by RAII. No partial public event/text or accepted source progress is returned. |
| cost | O(field bytes), fixed inline integer/date/decimal work; successful string path makes no owning copy. |
| Design | [docs/ingestion.md §CSV and explicit legacy profiles](../../../../ingestion.md), [docs/ingestion.md §Native reader API and memory grant](../../../../ingestion.md), [docs/memory_accounts.md §Native streaming input ownership](../../../../memory_accounts.md) |

## B0016

[Lines 196–211](../../../../../src/io/event_reader.cpp#L196); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct EventReader::Data {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Own one native decoder continuation with accepted and cached state separated. |
| inputs / outputs | Retains account/catalog/options/progress/fingerprint, borrowed stream, optional decoded row, prepared source node, CSV permutation, raw/decoded counters and lifecycle flags. |
| invariants | Heap-stable Data keeps options reference bound to retained_options. Only acknowledge publishes accepted progress; bytes/records/header/cached state describe decoding, not engine commitment. |
| ownership | Data owns native controls/rows/text/options/progress; borrows istream through caller-maintained lifetime. Moving the EventReader handle leaves Data/storage addresses stable. |
| failure | Construction/preparation failures release local owned state; after consuming peek failure broken is sticky. No engine state is owned or rolled back here. |
| cost | One account-funded control plus bounded options/record/progress/permutation payload and metadata; stream buffering stays externally owned. |
| Design | [docs/ingestion.md §Native reader API and memory grant](../../../../ingestion.md), [docs/memory_accounts.md §Native streaming input ownership](../../../../memory_accounts.md), [docs/ingestion.md §Reader acceptance and engine replay](../../../../ingestion.md) |

## B0017

[Lines 212–217](../../../../../src/io/event_reader.cpp#L212); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
  template<class Progress> Data(const resource::MemoryAccount& memory,std::istream& stream,CatalogSource schema,
      const AccountedInputOptions& config,const Progress& initial,bool admitted)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Construct the funded reader state before any byte consumption. |
| inputs / outputs | Retains schema/options, copies supplied progress under account, computes funded fingerprint and validates options/progress. |
| invariants | admitted suppresses redundant full catalog validation only for an admitted immutable source. Construction reads no stream record and cannot advance its accepted prefix. |
| ownership | Heap Data retains config owner and its const Values reference; external stream is borrowed. |
| failure | Option/catalog/size/allocation errors destroy partially constructed state without consuming stream bytes. |
| cost | O(catalog canonical bytes + options/progress names), control/progress/fingerprint allocations under supplied grant; optional catalog validation scratch. |
| Design | [docs/ingestion.md §Native reader API and memory grant](../../../../ingestion.md), [docs/memory_accounts.md §Native streaming input ownership](../../../../memory_accounts.md) |

## B0018

[Lines 218–262](../../../../../src/io/event_reader.cpp#L218); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
static void initialize(const auto& catalog,const AccountedInputOptions::Values& options,const AccountedInputProgress& progress)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Validate exact format-specific reader options and initial source directory. |
| inputs / outputs | Checks eight formats, unrelated option defaults, source/null UTF-8/caps, required table or relation map, delimiter/CSV-operation/header/timestamp restrictions. |
| invariants | Wire records carry their own table/position. CSV/legacy settings are not silently ignored. Initial accepted progress is caller-supplied metadata; this does not authenticate a checkpoint or source origin. |
| ownership | Borrows stable caller input/catalog synchronously; only local private parser/output state changes. No physical runtime, accepted source sequence or source position is published here. |
| failure | Validation, scalar, size, encoding or allocation errors propagate; local owned scratch is released by RAII. No partial public event/text or accepted source progress is returned. |
| cost | O(source/relation-map entries/name bytes and addressed table metadata); no stream read, fingerprint rebuild or engine work. |
| Design | [include/crown/io/ingest.hpp](../../../../../include/crown/io/ingest.hpp), [docs/ingestion.md](../../../../ingestion.md) |

## B0019

[Lines 263–280](../../../../../src/io/event_reader.cpp#L263); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::optional<char> byte()
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Consume one raw stream byte with explicit clean-EOF and I/O diagnostics. |
| inputs / outputs | peek detects EOF; raw total-byte/uint64 cap is checked before get; successful get increments bytes once. |
| invariants | EOF with eof && !bad is clean, including throwing streams. Other ios failures become input_io_error. bytes counts consumed raw framing as well as payload, independently of acceptance. |
| ownership | Borrows external istream, mutates its cursor/state and Data.bytes only. |
| failure | Two ios_base::failure catches distinguish clean EOF and translate real I/O errors; keep both. Later peek boundary records sticky failure; cannot undo consumed bytes. |
| cost | One peek/get per byte plus stream implementation buffering/I/O and fixed accounting; no successful decoder-owned allocation. |
| Design | [docs/ingestion.md §Reader acceptance and engine replay](../../../../ingestion.md) |

## B0020

[Lines 281–297](../../../../../src/io/event_reader.cpp#L281); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::optional<input_detail::Buffer> line()
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Frame one JSONL body while excluding LF/CRLF from record_bytes. |
| inputs / outputs | Reads funded body Buffer; single pending CR is withheld until its following byte decides framing; final unterminated body is allowed. |
| invariants | LF or CRLF ends record without consuming body budget; lone CR at EOF/body is retained. Blank line produces an empty body that decoder rejects, not skipped input. Total bytes still include framing. |
| ownership | Returns one owning funded raw body; stream/counters advance independently of accepted progress. |
| failure | Validation, scalar, size, encoding or allocation errors propagate; local owned scratch is released by RAII. No partial public event/text or accepted source progress is returned. |
| cost | O(raw bytes), account-backed Buffer growth bounded by body limit; holds one CR scalar instead of extra body capacity. |
| Design | [docs/ingestion.md §Version-1 JSONL event](../../../../ingestion.md), [schemas/physical-update-v1.schema.json](../../../../../schemas/physical-update-v1.schema.json), [docs/ingestion.md §Native reader API and memory grant](../../../../ingestion.md), [docs/memory_accounts.md §Native streaming input ownership](../../../../memory_accounts.md) |

## B0021

[Lines 298–318](../../../../../src/io/event_reader.cpp#L298); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::optional<input_detail::Buffer> frame()
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Frame one binary record before native decode. |
| inputs / outputs | Reads fourteen-byte header, validates magic/version/length, checks payload fits record cap before reserve, then reads exact payload. |
| invariants | Clean initial EOF returns none; short header/payload rejects. Header integer view is used before reserve can relocate its Buffer; no caller-declared large frame allocation occurs before size admission. |
| ownership | Returned Buffer owns raw frame under account; temporary header view is borrowed only before reserve. |
| failure | Validation, scalar, size, encoding or allocation errors propagate; local owned scratch is released by RAII. No partial public event/text or accepted source progress is returned. |
| cost | O(full frame bytes), funded raw buffer capacity; each byte uses Data.byte accounting and stream I/O. |
| Design | [docs/ingestion.md §Version-1 binary frame](../../../../ingestion.md), [docs/ingestion.md §Native reader API and memory grant](../../../../ingestion.md), [docs/memory_accounts.md §Native streaming input ownership](../../../../memory_accounts.md) |

## B0022

[Lines 319–322](../../../../../src/io/event_reader.cpp#L319); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::uint64_t offset() const
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Compute a text-profile source byte offset without uint64 wrap. |
| inputs / outputs | Returns configured byte_offset + consumed raw bytes after checked admission. |
| invariants | This is decoder positioning, not source acknowledgement; timestamp-flags caller uses its explicit timestamp instead. |
| ownership | Borrows stable caller input/catalog synchronously; only local private parser/output state changes. No physical runtime, accepted source sequence or source position is published here. |
| failure | resource_limit on offset overflow; no accepted progress changes. |
| cost | Fixed arithmetic/branch, no successful allocation. |
| Design | [docs/ingestion.md §CSV and explicit legacy profiles](../../../../ingestion.md) |

## B0023

[Lines 323–326](../../../../../src/io/event_reader.cpp#L323); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::uint64_t next_sequence() const
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Compute exactly the next accepted physical input sequence. |
| inputs / outputs | Returns progress.sequence + 1 unless UINT64_MAX. |
| invariants | Based on accepted progress, so a repeated peek/cached retry does not create a new sequence. |
| ownership | Borrows stable caller input/catalog synchronously; only local private parser/output state changes. No physical runtime, accepted source sequence or source position is published here. |
| failure | sequence_overflow at exhausted accepted sequence. |
| cost | Fixed integer check/add. |
| Design | [docs/ingestion.md §Reader acceptance and engine replay](../../../../ingestion.md) |

## B0024

[Lines 327–395](../../../../../src/io/event_reader.cpp#L327); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::optional<input_detail::Decoded> delimited(const auto& catalog)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Route a complete delimited source row through an explicit CSV/legacy profile. |
| inputs / outputs | May consume/map one CSV header, interpret exact sign/relation/flag/timestamp prefixes, permute all physical columns, reject configured NULL marker, freeze row and optional source. |
| invariants | CSV header must be a complete unique permutation; nullary CSV has its explicit empty-field case. Legacy * controls reject. Input remains full physical source order, not logical occurrence projection. Strings are frozen before field vector release. |
| ownership | Accounted compact row/source own output; intermediate ScalarViews borrow record fields only until copy_of completes. |
| failure | Any header/profile/domain/NULL/UTF-8/size/allocation error propagates after possible stream consumption; enclosing peek poisons decoder, accepted progress stays unchanged. |
| cost | O(raw/decoded/scalar bytes + row width); initial header mapping uses find/count for every column (O(C^2) name comparisons); funded field/row/source/permutation storage overlaps. No engine-work allowance is charged. |
| Design | [docs/ingestion.md §CSV and explicit legacy profiles](../../../../ingestion.md), [docs/ingestion.md §Native reader API and memory grant](../../../../ingestion.md), [docs/memory_accounts.md §Native streaming input ownership](../../../../memory_accounts.md) |

## B0025

[Lines 396–397](../../../../../src/io/event_reader.cpp#L396); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L396-L397:sha256:feaa8eed9a9f1b44eda1ae46290d2de153b0d0c2b6cfedfc1eedcddccc10a49c
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Design note for adjacent code: Prepare a new source node before engine work; accepted offsets stay unchanged until acknowledge links that node or publishes an existing scalar offset. This is caller guidance recorded as prose, not an executable result. |
| inputs / outputs | No runtime interface is implemented by these comment-only lines. They sit at src/io/event_reader.cpp lines 394-399; the surrounding declaration/body defines its own inputs and outputs. |
| invariants | The words record the intended use boundary only. They do not add a guard, proof, capability, transaction, durability guarantee, or account charge; verify behavior in the referenced implementation. |
| ownership | Comment text owns no data. Object lifetimes, borrows, and account attribution remain those of the adjacent source objects and their constructors. |
| failure | No failure path is implemented here. Any mentioned failure or recovery rule belongs to the adjacent operation and its existing error carrier. |
| cost | No runtime work is performed by these lines; any cost/bound in the note is not certified by this comment-only card. |
| Design | [src/io/event_reader.cpp](../../../../../src/io/event_reader.cpp), [docs/code_specs/files/src/io/event_reader.cpp.md](event_reader.cpp.md), [docs/ingestion.md](../../../../ingestion.md), [docs/session_lifecycle.md](../../../../session_lifecycle.md) |

## B0026

[Lines 398–406](../../../../../src/io/event_reader.cpp#L398); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void order(const InputEventView& event)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Prepare source-order publication after a complete event decodes. |
| inputs / outputs | Requires contiguous sequence and strictly increasing offsets per existing source; admits source count and obtains prepared new map node or existing iterator. |
| invariants | InputPositions.prepare does not link/update accepted directory. All allocation needed for eventual source insertion precedes engine work and acknowledge. |
| ownership | prepared_position retains unlinked node or borrowed iterator into reader-owned accepted map until ack/release. |
| failure | Sequence/source/count/allocation failure leaves accepted positions unchanged; consuming peek becomes sticky. |
| cost | O(log S) ordered-map searches/comparisons with source-byte cost; new source key/node funded under reader account, existing source uses scalar/iterator staging. |
| Design | [docs/ingestion.md §Reader acceptance and engine replay](../../../../ingestion.md), [src/io/input_progress.cpp](../../../../../src/io/input_progress.cpp) |

## B0027

[Lines 407–407](../../../../../src/io/event_reader.cpp#L407); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L407-L407:sha256:aa1d1a63390229c798347e83a0405441c9400035284ad168c1bf6cdf1d70a370
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Closes the enclosing helper type at this source boundary; this is a lexical delimiter, not an operation. |
| inputs / outputs | No runtime input or output. Declarations following the span leave the preceding C++ scope. |
| invariants | The delimiter ends the preceding scope's visibility/linkage region; it adds no validation, publication, ownership transfer, or runtime authority. |
| ownership | The delimiter adds no owner. If it ends a function/block with live automatic objects, their normal destructors release those objects; namespace and type-definition closes change no existing object's lifetime. |
| failure | No explicit failure translation or catch is added. If a function/block exit destroys automatic objects, exception behavior follows those destructors; namespace/type closes have no runtime failure path. |
| cost | The delimiter adds no algorithmic work. A function/block exit can run existing automatic-object destructors and cleanup; namespace/type closes have no runtime cost. |
| Design | [src/io/event_reader.cpp](../../../../../src/io/event_reader.cpp), [docs/code_specs/files/src/io/event_reader.cpp.md](event_reader.cpp.md), [docs/ingestion.md](../../../../ingestion.md), [docs/session_lifecycle.md](../../../../session_lifecycle.md) |

## B0028

[Lines 408–409](../../../../../src/io/event_reader.cpp#L408); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
EventReader::EventReader(std::istream& input,CatalogSource catalog,InputOptions options,InputProgress progress)
    :EventReader(resource::MemoryAccount::create(std::numeric_limits<std::uint64_t>::max()),input,std::move(catalog),std::move(options),std::move(progress),false) {}
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Create an explicit standalone catalog/stream reader with its own component account. |
| inputs / outputs | Public CatalogSource/options/progress path delegates using an explicit maximum-limit standalone account. |
| invariants | This is an external/compiler adapter boundary; a by-value standalone Catalog retains its ordinary caller/compiler metadata. Execution constructors elsewhere share immutable program authority and original finite account; this does not refill an existing query. |
| ownership | Owns native reader state; catalog is retained, input stream remains borrowed. |
| failure | Construction errors release local state and consume no input bytes. |
| cost | Account controller plus funded Data/options/progress/catalog-hash preparation; standalone Catalog value/alias transfer and any caller-side ordinary copy are separate. |
| Design | [docs/ingestion.md §Native reader API and memory grant](../../../../ingestion.md), [docs/memory_accounts.md §Native streaming input ownership](../../../../memory_accounts.md) |

## B0029

[Lines 410–411](../../../../../src/io/event_reader.cpp#L410); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
EventReader::EventReader(const resource::MemoryAccount& account,std::istream& input,CatalogSource catalog,InputOptions options,InputProgress progress,bool admitted)
    :EventReader(account,input,std::move(catalog),AccountedInputOptions(account,options),std::move(progress),admitted) {}
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Fund immutable reader options then construct native state in supplied account. |
| inputs / outputs | Copies ordinary InputOptions into AccountedInputOptions and delegates catalog/progress/admitted state. |
| invariants | Actual receiving grant is preserved; no replacement per-record account or ordinary retained options mirror. |
| ownership | Temporary accounted options shares its immutable funded owner with Data; external stream remains borrowed. |
| failure | Any option/account/construction error precedes stream consumption. |
| cost | O(option map/text bytes) funded copy plus Data/hash/progress construction. |
| Design | [docs/ingestion.md §Native reader API and memory grant](../../../../ingestion.md), [docs/memory_accounts.md §Native streaming input ownership](../../../../memory_accounts.md) |

## B0030

[Lines 412–414](../../../../../src/io/event_reader.cpp#L412); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
EventReader::EventReader(const resource::MemoryAccount& account,std::istream& input,CatalogSource catalog,const AccountedInputOptions& options,InputProgress progress,bool admitted)
    :data_(resource::make_accounted_unique<Data>(input_detail::memory_owner,account,resource::MemoryPurpose::support_metadata,
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Allocate the stable reader Data control in the receiving account. |
| inputs / outputs | Uses make_accounted_unique attribution session:2/support_metadata with retained catalog/options and copied progress. |
| invariants | Private callers establish compatible option-account authority. Data owns all persistent decoder fields before the handle is published. |
| ownership | EventReader uniquely owns Data; it never owns the external stream object. |
| failure | Factory frees partially constructed raw control on construction failure; no extra cleanup catch needed here. |
| cost | One funded control construction plus Data metadata/hash/progress preparation. |
| Design | [docs/ingestion.md §Native reader API and memory grant](../../../../ingestion.md), [docs/memory_accounts.md §Native streaming input ownership](../../../../memory_accounts.md) |

## B0031

[Lines 415–415](../../../../../src/io/event_reader.cpp#L415); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
EventReader::~EventReader()=default;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Release reader continuation without accepting cached input. |
| inputs / outputs | Default unique Data destruction releases cached row/source, prepared node, options and accepted directory. |
| invariants | Does not advance accepted sequence, acknowledge an engine event or destroy the borrowed stream. Retained options/progress snapshots can keep their funded owners alive. |
| ownership | Drops this reader unique owner; independent retained snapshots/options account for their remaining lifetime. |
| failure | Ordinary RAII destruction; underlying owned types have nonthrowing teardown contracts. |
| cost | Cleanup proportional to retained directory/options/record state and account release; no successful allocation implied by destruction. |
| Design | [docs/ingestion.md §Native reader API and memory grant](../../../../ingestion.md), [docs/memory_accounts.md §Native streaming input ownership](../../../../memory_accounts.md) |

## B0032

[Lines 416–418](../../../../../src/io/event_reader.cpp#L416); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void EventReader::validate_options(const CatalogSource& catalog,const AccountedInputOptions& options,const AccountedInputProgress& progress)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Validate a native option/progress pair against its real catalog owner. |
| inputs / outputs | Visits CatalogSource and calls Data::initialize with read-only native values. |
| invariants | No Data/control construction or stream consumption; this is option/schema validation only. |
| ownership | Borrows stable caller input/catalog synchronously; only local private parser/output state changes. No physical runtime, accepted source sequence or source position is published here. |
| failure | Validation, scalar, size, encoding or allocation errors propagate; local owned scratch is released by RAII. No partial public event/text or accepted source progress is returned. |
| cost | Selected source/mapping/name/table scans from initialize; no catalog fingerprint or new account. |
| Design | [include/crown/io/ingest.hpp](../../../../../include/crown/io/ingest.hpp), [docs/ingestion.md](../../../../ingestion.md) |

## B0033

[Lines 419–443](../../../../../src/io/event_reader.cpp#L419); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
EventReader::EventReader(const resource::MemoryAccount& account,std::istream& input,CatalogSource catalog,
    const ReaderCheckpoint& state,const SourceStateLimits& limits,bool admitted)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Restore a reader continuation after explicit checkpoint metadata admission. |
| inputs / outputs | Charges SourceStateLimits positions/options/CSV fields, funds options/Data, verifies catalog digest/raw/record caps and header permutation, then installs counters/header/ended state. |
| invariants | Caller stream must already begin at next unread byte; constructor neither seeks nor verifies external bytes. CSV permutation is complete/distinct and ties to restored header. No cached unacknowledged event is imported. |
| ownership | New unique Data owns copied native continuation under receiver; ReaderCheckpoint and external stream are borrowed only as specified. |
| failure | Image limit/work/binding/corruption, option, account or allocation error destroys local result before public handle; consumes no stream record. |
| cost | Catalog hashing/progress/options copies + O(C^2) permutation duplicate checks charged pairwise; restored arrays/control consume supplied account. |
| Design | [include/crown/io/checkpoint.hpp](../../../../../include/crown/io/checkpoint.hpp), [docs/native-replay.md](../../../../native-replay.md), [src/io/checkpoint_detail.hpp](../../../../../src/io/checkpoint_detail.hpp), [docs/ingestion.md §Native reader API and memory grant](../../../../ingestion.md), [docs/memory_accounts.md §Native streaming input ownership](../../../../memory_accounts.md) |

## B0034

[Lines 444–444](../../../../../src/io/event_reader.cpp#L444); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
ReaderCheckpoint EventReader::checkpoint_state() const
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Capture reader checkpoint metadata with default source-state limits. |
| inputs / outputs | Forwards to checkpoint_state(SourceStateLimits{}). |
| invariants | Default is an explicit bounded capture, not an engine commit or source seek. |
| ownership | Borrows stable caller input/catalog synchronously; only local private parser/output state changes. No physical runtime, accepted source sequence or source position is published here. |
| failure | Validation, scalar, size, encoding or allocation errors propagate; local owned scratch is released by RAII. No partial public event/text or accepted source progress is returned. |
| cost | Fixed forwarding plus bounded native checkpoint capture. |
| Design | [include/crown/io/checkpoint.hpp](../../../../../include/crown/io/checkpoint.hpp), [docs/native-replay.md](../../../../native-replay.md), [src/io/checkpoint_detail.hpp](../../../../../src/io/checkpoint_detail.hpp) |

## B0035

[Lines 445–454](../../../../../src/io/event_reader.cpp#L445); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
ReaderCheckpoint EventReader::checkpoint_state(const SourceStateLimits& limits) const
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Capture an owning decoder continuation only at an accepted reader boundary. |
| inputs / outputs | Requires valid Data with no cached record and no broken state; charges positions/options/CSV fields then copies accepted progress/permutation/counters/digest. |
| invariants | A decoded unacknowledged row blocks capture. ended is descriptive EOF state; bytes/records become checkpoint continuation only through this admitted boundary. |
| ownership | ReaderCheckpoint shares immutable funded options and owns copied progress/CSV fields; caller can retain it independently. |
| failure | Boundary/image-work/limit/allocation failure returns no partial checkpoint and does not consume/acknowledge input. |
| cost | O(progress names + options descriptors + permutation fields), funded owning copies under reader account and selected SourceStateLimits work. |
| Design | [include/crown/io/checkpoint.hpp](../../../../../include/crown/io/checkpoint.hpp), [docs/native-replay.md](../../../../native-replay.md), [src/io/checkpoint_detail.hpp](../../../../../src/io/checkpoint_detail.hpp), [docs/ingestion.md §Native reader API and memory grant](../../../../ingestion.md), [docs/memory_accounts.md §Native streaming input ownership](../../../../memory_accounts.md) |

## B0036

[Lines 455–456](../../../../../src/io/event_reader.cpp#L455); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
EventReader::EventReader(EventReader&&) noexcept=default;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Transfer the heap-stable reader continuation without copying source state. |
| inputs / outputs | Default move construction/assignment transfers the unique Data handle; assignment first releases old destination continuation. |
| invariants | Internal options reference and row/source views remain valid because Data/payload addresses do not move. Source becomes moved-from and its accessors/peek reject; acknowledge remains a no-op. |
| ownership | Exactly one EventReader owns each Data after move; external stream lifetime remains caller responsibility. |
| failure | noexcept; release of previous state follows nonthrowing owned teardown. |
| cost | Fixed handle transfer, plus destination old-state teardown on assignment; no deep copy/allocation. |
| Design | [docs/ingestion.md §Native reader API and memory grant](../../../../ingestion.md), [docs/memory_accounts.md §Native streaming input ownership](../../../../memory_accounts.md) |

## B0037

[Lines 457–476](../../../../../src/io/event_reader.cpp#L457); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
const InputEventView* EventReader::peek()
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Return one stable decoded native event or sticky terminal EOF/failure. |
| inputs / outputs | Returns same cached event without reading; otherwise frames/decodes one record, admits record count, prepares source order, caches ownership and increments decoded count. |
| invariants | No accepted progress advances. EOF marks ended. Every exception in consuming preparation, including decode, record-limit/source-order checks and cache publication, latches broken and rethrows because stream/counters/header may already have changed. Engine apply happens after return and can retry a complete cached event. |
| ownership | Returned const pointer/view borrows cached row/source and survives repeated peek until acknowledge, close, destruction or handle replacement. |
| failure | Keep the single catch-all: it latches broken after potentially consumed input and preserves the original error. Further peeks reject input_failed; recreation is explicit. |
| cost | Native raw/decode/validate/source-map preparation cost with account-funded storage; cached repeat is fixed presence/pointer work. No whole-input history or per-update engine work grant. |
| Design | [docs/ingestion.md §Reader acceptance and engine replay](../../../../ingestion.md), [docs/ingestion.md §Native reader API and memory grant](../../../../ingestion.md), [docs/memory_accounts.md §Native streaming input ownership](../../../../memory_accounts.md) |

## B0038

[Lines 477–478](../../../../../src/io/event_reader.cpp#L477); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L477-L478:sha256:0e5eb611da69ebc0697e28d643875652acb0d6fbb0b76b21a09d45d06fd0107d
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Design note for adjacent code: No input read or allocation: publish only the already prepared acceptance. Releasing cached payload still has its ordinary account/cleanup cost. This is caller guidance recorded as prose, not an executable result. |
| inputs / outputs | No runtime interface is implemented by these comment-only lines. They sit at src/io/event_reader.cpp lines 475-480; the surrounding declaration/body defines its own inputs and outputs. |
| invariants | The words record the intended use boundary only. They do not add a guard, proof, capability, transaction, durability guarantee, or account charge; verify behavior in the referenced implementation. |
| ownership | Comment text owns no data. Object lifetimes, borrows, and account attribution remain those of the adjacent source objects and their constructors. |
| failure | No failure path is implemented here. Any mentioned failure or recovery rule belongs to the adjacent operation and its existing error carrier. |
| cost | No runtime work is performed by these lines; any cost/bound in the note is not certified by this comment-only card. |
| Design | [src/io/event_reader.cpp](../../../../../src/io/event_reader.cpp), [docs/code_specs/files/src/io/event_reader.cpp.md](event_reader.cpp.md), [docs/ingestion.md](../../../../ingestion.md), [docs/session_lifecycle.md](../../../../session_lifecycle.md) |

## B0039

[Lines 479–484](../../../../../src/io/event_reader.cpp#L479); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void EventReader::acknowledge() noexcept
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Publish only the already prepared cached input acceptance. |
| inputs / outputs | No cached record is a no-op; otherwise links prepared source node or changes existing offset, assigns accepted sequence and releases cache/token. |
| invariants | All throwing source allocation/order/domain preparation happened in peek/stage_replay. Acknowledge does not read, skip or apply an event; caller invokes it only after actual engine publication. |
| ownership | Accepted directory takes staged node ownership; cached row/source views become invalid on release. |
| failure | noexcept; relies on prepared map ownership/comparator invariants, invalid/empty reader is an idempotent no-op. |
| cost | Prepared ordered-map node link/lookup comparisons or scalar update plus cached payload/account-release cost; allocation-free and nonthrowing, not a blanket constant-time cleanup. |
| Design | [docs/ingestion.md §Reader acceptance and engine replay](../../../../ingestion.md), [src/io/input_progress.cpp](../../../../../src/io/input_progress.cpp) |

## B0040

[Lines 485–536](../../../../../src/io/event_reader.cpp#L485); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::uint64_t EventReader::stage_replay(const InputEventView& event,ReaderPositionView position,const SourceStateLimits& limits)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Stage one already validated replay input and its decoder continuation before session commit. |
| inputs / outputs | Requires healthy uncached/unended reader, charges conservative source work, checks next records/bytes/sequence/caps, catalog/domain/CSV/header/source/profile binding, owns row/source/fields and prepares source order. |
| invariants | Does not read/seek stream or acknowledge. All throwing validation/copies and InputPositions preparation precede fields swap/cache/counter publication. New CSV header offset is constrained by admitted encoded header bounds; timestamp source positions retain their profile semantics. |
| ownership | Copies borrowed replay row/source into receiving account and rebases event views; publication uses nonthrowing owning moves/swap and retained prepared map node. |
| failure | Image/domain/binding/work/account/allocation failure occurs before published decoder state; accepted progress remains old and no stream byte is consumed. This private path needs no consuming-peek poison catch. |
| cost | O(row/scalar/source/mapping bytes + conservative directory searches), O(C^2) CSV permutation checks and bounded header scans, funded row/source/field allocations. SourceStateLimits meters named conservative actions, not complete CPU/I/O. |
| Design | [include/crown/io/checkpoint.hpp](../../../../../include/crown/io/checkpoint.hpp), [docs/native-replay.md](../../../../native-replay.md), [src/io/checkpoint_detail.hpp](../../../../../src/io/checkpoint_detail.hpp), [docs/ingestion.md §Reader acceptance and engine replay](../../../../ingestion.md), [docs/ingestion.md §Native reader API and memory grant](../../../../ingestion.md), [docs/memory_accounts.md §Native streaming input ownership](../../../../memory_accounts.md) |

## B0041

[Lines 537–540](../../../../../src/io/event_reader.cpp#L537); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
ReaderPositionView EventReader::decoder_position() const &
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Borrow current decoder continuation without accepting or allocating. |
| inputs / outputs | Returns bytes/decoded records/header flag and span of CSV permutation fields. |
| invariants | Includes an already cached unacknowledged record; not alone an accepted checkpoint. Span must not survive reader operation/move/destruction. |
| ownership | Reader owns the borrowed CSV vector; caller uses view synchronously. |
| failure | Moved-from/closed reader throws invalid_input_reader. |
| cost | Fixed scalar/span construction. |
| Design | [docs/ingestion.md §Reader acceptance and engine replay](../../../../ingestion.md), [include/crown/io/checkpoint.hpp](../../../../../include/crown/io/checkpoint.hpp), [docs/native-replay.md](../../../../native-replay.md), [src/io/checkpoint_detail.hpp](../../../../../src/io/checkpoint_detail.hpp) |

## B0042

[Lines 541–541](../../../../../src/io/event_reader.cpp#L541); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
bool EventReader::failed() const noexcept
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Inspect the sticky consuming-reader failure flag. |
| inputs / outputs | Returns true only when Data exists and broken is set. |
| invariants | Moved-from/closed reader reports false; engine rejection of a cached event does not set this flag. |
| ownership | Returns a copied Boolean; no owner transfer. |
| failure | noexcept, no allocation or error path. |
| cost | Fixed nullable-handle/Boolean read. |
| Design | [docs/ingestion.md §Reader acceptance and engine replay](../../../../ingestion.md) |

## B0043

[Lines 542–542](../../../../../src/io/event_reader.cpp#L542); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L542-L542:sha256:0ffd2a24feb0d7eec5623da79561f3217d51ef26267a658910ea79a696c8e22e
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Design note for adjacent code: Move accepted native ownership out; discard cached input without acceptance. This is caller guidance recorded as prose, not an executable result. |
| inputs / outputs | No runtime interface is implemented by these comment-only lines. They sit at src/io/event_reader.cpp lines 540-544; the surrounding declaration/body defines its own inputs and outputs. |
| invariants | The words record the intended use boundary only. They do not add a guard, proof, capability, transaction, durability guarantee, or account charge; verify behavior in the referenced implementation. |
| ownership | Comment text owns no data. Object lifetimes, borrows, and account attribution remain those of the adjacent source objects and their constructors. |
| failure | No failure path is implemented here. Any mentioned failure or recovery rule belongs to the adjacent operation and its existing error carrier. |
| cost | No runtime work is performed by these lines; any cost/bound in the note is not certified by this comment-only card. |
| Design | [src/io/event_reader.cpp](../../../../../src/io/event_reader.cpp), [docs/code_specs/files/src/io/event_reader.cpp.md](event_reader.cpp.md), [docs/ingestion.md](../../../../ingestion.md), [docs/session_lifecycle.md](../../../../session_lifecycle.md) |

## B0044

[Lines 543–547](../../../../../src/io/event_reader.cpp#L543); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
AccountedInputProgress EventReader::close() noexcept
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Close reader without accepting pending input and retain native accepted progress. |
| inputs / outputs | Moves progress out, destroys Data/cache/preparation/options; empty reader returns default progress. |
| invariants | No stream ownership/seek/acknowledgement; cached unaccepted event is discarded. Repeated close is empty; returned accepted state can outlive all reader/runtime owners. |
| ownership | Returns owning AccountedInputProgress under original account, without exporting an ordinary map/string DTO. |
| failure | noexcept; compile-time assertion requires nonthrowing progress move. |
| cost | Fixed noexcept progress-handle move plus retained record/options/directory cleanup; no allocation, not necessarily constant-time teardown. |
| Design | [docs/ingestion.md §Native reader API and memory grant](../../../../ingestion.md), [docs/memory_accounts.md §Native streaming input ownership](../../../../memory_accounts.md), [docs/ingestion.md §Reader acceptance and engine replay](../../../../ingestion.md) |

## B0045

[Lines 548–548](../../../../../src/io/event_reader.cpp#L548); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
const AccountedInputProgress& EventReader::progress() const
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Inspect reader accepted progress. |
| inputs / outputs | Valid reader returns const AccountedInputProgress reference, not a detached snapshot. |
| invariants | Accessor never reads input, accepts an event, measures engine work or creates a new memory grant. |
| ownership | Borrowed native progress remains owned by Data and changes on acknowledge. |
| failure | Moved-from/closed reader throws invalid_input_reader; no successful allocation. |
| cost | Fixed handle/field access; value copying of a returned owner/reference, if requested separately, has its own documented cost. |
| Design | [docs/ingestion.md §Reader acceptance and engine replay](../../../../ingestion.md), [docs/ingestion.md §Native reader API and memory grant](../../../../ingestion.md), [docs/memory_accounts.md §Native streaming input ownership](../../../../memory_accounts.md) |

## B0046

[Lines 549–549](../../../../../src/io/event_reader.cpp#L549); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
const CatalogSource& EventReader::catalog() const
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Inspect reader catalog owner. |
| inputs / outputs | Valid reader returns const CatalogSource reference retains actual source catalog authority. |
| invariants | Accessor never reads input, accepts an event, measures engine work or creates a new memory grant. |
| ownership | Borrowed variant/reference requires live reader; copying an alias is a separate ownership act. |
| failure | Moved-from/closed reader throws invalid_input_reader; no successful allocation. |
| cost | Fixed handle/field access; value copying of a returned owner/reference, if requested separately, has its own documented cost. |
| Design | [docs/ingestion.md §Reader acceptance and engine replay](../../../../ingestion.md), [docs/ingestion.md §Native reader API and memory grant](../../../../ingestion.md), [docs/memory_accounts.md §Native streaming input ownership](../../../../memory_accounts.md) |

## B0047

[Lines 550–550](../../../../../src/io/event_reader.cpp#L550); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::string_view EventReader::catalog_sha256() const
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Inspect reader catalog fingerprint. |
| inputs / outputs | Valid reader returns string_view of the retained canonical 64-character fingerprint. |
| invariants | Accessor never reads input, accepts an event, measures engine work or creates a new memory grant. |
| ownership | Borrowed immutable text is valid while its owning Data/text remains alive. |
| failure | Moved-from/closed reader throws invalid_input_reader; no successful allocation. |
| cost | Fixed handle/field access; value copying of a returned owner/reference, if requested separately, has its own documented cost. |
| Design | [docs/ingestion.md §Reader acceptance and engine replay](../../../../ingestion.md), [docs/ingestion.md §Native reader API and memory grant](../../../../ingestion.md), [docs/memory_accounts.md §Native streaming input ownership](../../../../memory_accounts.md) |

## B0048

[Lines 551–551](../../../../../src/io/event_reader.cpp#L551); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
const resource::MemoryAccount& EventReader::account() const
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Inspect reader receiving memory account. |
| inputs / outputs | Valid reader returns const MemoryAccount reference for the original reader grant. |
| invariants | Accessor never reads input, accepts an event, measures engine work or creates a new memory grant. |
| ownership | Borrowed account reference; caller can explicitly copy its native handle to retain authority. |
| failure | Moved-from/closed reader throws invalid_input_reader; no successful allocation. |
| cost | Fixed handle/field access; value copying of a returned owner/reference, if requested separately, has its own documented cost. |
| Design | [docs/ingestion.md §Reader acceptance and engine replay](../../../../ingestion.md), [docs/ingestion.md §Native reader API and memory grant](../../../../ingestion.md), [docs/memory_accounts.md §Native streaming input ownership](../../../../memory_accounts.md) |

## B0049

[Lines 552–552](../../../../../src/io/event_reader.cpp#L552); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
const AccountedInputOptions& EventReader::native_options() const &
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Inspect reader immutable native options. |
| inputs / outputs | Valid reader returns const AccountedInputOptions lvalue reference. |
| invariants | Accessor never reads input, accepts an event, measures engine work or creates a new memory grant. |
| ownership | Borrowed shared option owner; its value copy retains funded metadata without a deep ordinary DTO export. |
| failure | Moved-from/closed reader throws invalid_input_reader; no successful allocation. |
| cost | Fixed handle/field access; value copying of a returned owner/reference, if requested separately, has its own documented cost. |
| Design | [docs/ingestion.md §Reader acceptance and engine replay](../../../../ingestion.md), [docs/ingestion.md §Native reader API and memory grant](../../../../ingestion.md), [docs/memory_accounts.md §Native streaming input ownership](../../../../memory_accounts.md) |

## B0050

[Lines 553–553](../../../../../src/io/event_reader.cpp#L553); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::uint64_t EventReader::bytes_read() const
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Inspect reader consumed raw byte count. |
| inputs / outputs | Valid reader returns Copied uint64 bytes including framing/possibly failed input consumption. |
| invariants | Accessor never reads input, accepts an event, measures engine work or creates a new memory grant. |
| ownership | Copied scalar; no lifetime dependency after return. |
| failure | Moved-from/closed reader throws invalid_input_reader; no successful allocation. |
| cost | Fixed handle/field access; value copying of a returned owner/reference, if requested separately, has its own documented cost. |
| Design | [docs/ingestion.md §Reader acceptance and engine replay](../../../../ingestion.md), [docs/ingestion.md §Native reader API and memory grant](../../../../ingestion.md), [docs/memory_accounts.md §Native streaming input ownership](../../../../memory_accounts.md) |

## B0051

[Lines 554–554](../../../../../src/io/event_reader.cpp#L554); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::uint64_t EventReader::records_read() const
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Inspect reader decoded record count. |
| inputs / outputs | Valid reader returns Copied uint64 records including an unacknowledged cached record. |
| invariants | Accessor never reads input, accepts an event, measures engine work or creates a new memory grant. |
| ownership | Copied scalar; accepted source sequence remains a separate field. |
| failure | Moved-from/closed reader throws invalid_input_reader; no successful allocation. |
| cost | Fixed handle/field access; value copying of a returned owner/reference, if requested separately, has its own documented cost. |
| Design | [docs/ingestion.md §Reader acceptance and engine replay](../../../../ingestion.md), [docs/ingestion.md §Native reader API and memory grant](../../../../ingestion.md), [docs/memory_accounts.md §Native streaming input ownership](../../../../memory_accounts.md) |

## B0052

[Lines 555–555](../../../../../src/io/event_reader.cpp#L555); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L555-L555:sha256:39c2bd587239794e92def2b2ebc5cce8f0acd397d817bceec761a8f61bea3e66
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Closes the namespace crown::io at this source boundary; this is a lexical delimiter, not an operation. |
| inputs / outputs | No runtime input or output. Declarations following the span leave the preceding C++ scope. |
| invariants | The delimiter ends the preceding scope's visibility/linkage region; it adds no validation, publication, ownership transfer, or runtime authority. |
| ownership | The delimiter adds no owner. If it ends a function/block with live automatic objects, their normal destructors release those objects; namespace and type-definition closes change no existing object's lifetime. |
| failure | No explicit failure translation or catch is added. If a function/block exit destroys automatic objects, exception behavior follows those destructors; namespace/type closes have no runtime failure path. |
| cost | The delimiter adds no algorithmic work. A function/block exit can run existing automatic-object destructors and cleanup; namespace/type closes have no runtime cost. |
| Design | [src/io/event_reader.cpp](../../../../../src/io/event_reader.cpp), [docs/code_specs/files/src/io/event_reader.cpp.md](event_reader.cpp.md), [docs/ingestion.md](../../../../ingestion.md), [docs/session_lifecycle.md](../../../../session_lifecycle.md) |
