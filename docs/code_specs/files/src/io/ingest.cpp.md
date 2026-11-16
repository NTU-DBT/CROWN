# `src/io/ingest.cpp` — block usage map

[Source](../../../../../src/io/ingest.cpp) · [Source index](../../../README.md) · [Subsystem contracts](../../../subsystem_contracts.md) · [Reviewed primitives](../../../primitives.md)

Admit bounded external documents/records and serialize explicit public representations at the engine boundary.

Snapshot SHA-256: `9237e5a367bf38cc67b94d4466454a503c8f54b8a4dff409c859a82cba1bd1ea`. 470 lines partitioned into 74 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [io](../../../subsystem_contracts.md#io). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/ingestion.md](../../../../ingestion.md), [docs/query_identity.md](../../../../query_identity.md), [docs/schema_evolution.md](../../../../schema_evolution.md), [docs/cli.md](../../../../cli.md), [docs/query_memory.md](../../../../query_memory.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–30](../../../../../src/io/ingest.cpp#L1) | Imports dependencies; declares namespace scope; declares aliases; declares callable signatures; declares values/defaults or compile-time conditions. | guard static_assert(std::variant_size_v&lt;Value&gt; == 5 && · [reviewed contract](#b0001) |
| [B0002 · 31–33](../../../../../src/io/ingest.cpp#L31) | Callable definition: void require(bool condition,std::string_view code,std::string_view message) | calls Error, std::string; guard void require(bool condition,std::string_view code,std::string_view message) { · [reviewed contract](#b0002) |
| [B0003 · 34–36](../../../../../src/io/ingest.cpp#L34) | Callable definition: void bounded(std::size_t size,std::size_t limit,std::string_view description) | calls require; guard void bounded(std::size_t size,std::size_t limit,std::string_view description) { · [reviewed contract](#b0003) |
| [B0004 · 37–40](../../../../../src/io/ingest.cpp#L37) | Callable definition: std::size_t sum(std::size_t left,std::size_t right) | calls require, max; guard require(right&lt;=std::numeric_limits&lt;std::size_t&gt;::max()-left,"resource_limit","input size accounting…; returns left+right · [reviewed contract](#b0004) |
| [B0005 · 41–45](../../../../../src/io/ingest.cpp#L41) | Callable definition: void source_name(std::string_view name,const InputLimits& limits) | calls bounded, size, require, empty; guard bounded(name.size(),limits.source_bytes,"input source identifier exceeds its byte limit"); · [reviewed contract](#b0005) |
| [B0006 · 46–49](../../../../../src/io/ingest.cpp#L46) | Callable definition: const auto& table_at(const auto& catalog,TableId table) | calls require, size; guard require(table.value&lt;catalog.tables.size(),"unknown_table","physical input table ID is outside the c…; returns catalog.tables\[table.value\] · [reviewed contract](#b0006) |
| [B0007 · 50–73](../../../../../src/io/ingest.cpp#L50) | Callable definition: void validate_event(const InputEvent& event,const auto& catalog,const InputLimits& limits) | calls table_at, require, bounded, size; guard require(event.update.sequence!=0,"invalid_sequence","input sequence must be positive");; growth insert; 1 loop sites; source comment (unverified): // A lower bound valid in every admitted encoding. · [reviewed contract](#b0007) |
| [B0008 · 74–78](../../../../../src/io/ingest.cpp#L74) | Callable definition: void check_binding(std::uint64_t catalog_version,std::uint64_t source_version,std::string_view fingerprint, TableId id,const auto… | calls require, table_at; guard require(catalog_version==catalog.version && source_version==table_at(catalog,id).source_schema_vers… · [reviewed contract](#b0008) |
| [B0009 · 79–84](../../../../../src/io/ingest.cpp#L79) | declares types or opens a type body; declares callable signatures; declares values/defaults or compile-time conditions. | source comment (unverified): // Public DTO codecs use SAX and direct canonical output, without a JSON DOM. · [reviewed contract](#b0009) |
| [B0010 · 85–87](../../../../../src/io/ingest.cpp#L85) | Callable definition: void raw(std::string_view text) | calls bounded, sum, size, append; guard bounded(sum(output.size(),text.size()),limit,"JSON output exceeds record byte limit"); output.appen… · [reviewed contract](#b0010) |
| [B0011 · 88–107](../../../../../src/io/ingest.cpp#L88) | Callable definition: void text(std::string_view value) | calls require_utf8, raw, std::string_view; 1 loop sites · [reviewed contract](#b0011) |
| [B0012 · 108–111](../../../../../src/io/ingest.cpp#L108) | Callable definition: void number(std::uint64_t value) | calls std::to_chars, std::begin, std::end, raw · [reviewed contract](#b0012) |
| [B0013 · 112–115](../../../../../src/io/ingest.cpp#L112) | Callable definition: void signed_number(std::int64_t value) | calls std::to_chars, std::begin, std::end, raw · [reviewed contract](#b0013) |
| [B0014 · 116–116](../../../../../src/io/ingest.cpp#L116) | Closes surrounding scope/type. |  · [reviewed contract](#b0014) |
| [B0015 · 117–121](../../../../../src/io/ingest.cpp#L117) | Callable definition: void names(auto& out,const auto& table,const auto& columns) | calls raw, text; 1 loop sites · [reviewed contract](#b0015) |
| [B0016 · 122–123](../../../../../src/io/ingest.cpp#L122) | Explanatory comments or spacing. | source comment (unverified): // Full metadata, including hints/statistics and constraint status, binds v1. · [reviewed contract](#b0016) |
| [B0017 · 124–168](../../../../../src/io/ingest.cpp#L124) | Callable definition: void canonical_catalog_to(const auto& catalog,auto& out) | calls raw, number, text, type_name; 5 loop sites; source comment (unverified): // Full metadata, including hints/statistics and constraint status, binds v1. · [reviewed contract](#b0017) |
| [B0018 · 169–171](../../../../../src/io/ingest.cpp#L169) | Callable definition: std::string canonical_catalog(const auto& catalog) | calls catalog::validate_catalog, canonical_catalog_to, std::move; returns std::move(out.output) · [reviewed contract](#b0018) |
| [B0019 · 172–173](../../../../../src/io/ingest.cpp#L172) | declares types or opens a type body. | source comment (unverified): // Public owning DTO parser; operational readers use the funded JsonReader. · [reviewed contract](#b0019) |
| [B0020 · 174–174](../../../../../src/io/ingest.cpp#L174) | Type/record definition: enum class Context |  · [reviewed contract](#b0020) |
| [B0021 · 175–175](../../../../../src/io/ingest.cpp#L175) | Type/record definition: enum class Key |  · [reviewed contract](#b0021) |
| [B0022 · 176–184](../../../../../src/io/ingest.cpp#L176) | declares values/defaults or compile-time conditions. | growth insert · [reviewed contract](#b0022) |
| [B0023 · 185–185](../../../../../src/io/ingest.cpp#L185) | Callable definition: explicit EventSax(const InputLimits& budget):limits(budget) | calls limits · [reviewed contract](#b0023) |
| [B0024 · 186–186](../../../../../src/io/ingest.cpp#L186) | Callable definition: \[\[noreturn\]\] static void invalid() | calls Error · [reviewed contract](#b0024) |
| [B0025 · 187–190](../../../../../src/io/ingest.cpp#L187) | Callable definition: void value(Value item) | calls bounded, sum, size, push_back; guard bounded(sum(event.update.values.size(),1),limits.columns,"physical input column limit exceeded");; growth push_back · [reviewed contract](#b0025) |
| [B0026 · 191–206](../../../../../src/io/ingest.cpp#L191) | Callable definition: bool unsigned_value(std::uint64_t item) | calls require, max, value, invalid; guard require(item&lt;=static_cast&lt;std::uint64_t&gt;(std::numeric_limits&lt;std::int64_t&gt;::max()),"invalid_documen…; returns true; true · [reviewed contract](#b0026) |
| [B0027 · 207–207](../../../../../src/io/ingest.cpp#L207) | Callable definition: bool null() override | calls invalid · [reviewed contract](#b0027) |
| [B0028 · 208–208](../../../../../src/io/ingest.cpp#L208) | Callable definition: bool boolean(bool item) override | calls invalid, value; returns true · [reviewed contract](#b0028) |
| [B0029 · 209–213](../../../../../src/io/ingest.cpp#L209) | Callable definition: bool number_integer(number_integer_t item) override | calls value, invalid, unsigned_value; returns true; unsigned_value(static_cast&lt;std::uint64_t&gt;(item)) · [reviewed contract](#b0029) |
| [B0030 · 214–214](../../../../../src/io/ingest.cpp#L214) | Callable definition: bool number_unsigned(number_unsigned_t item) override | calls unsigned_value; returns unsigned_value(item) · [reviewed contract](#b0030) |
| [B0031 · 215–215](../../../../../src/io/ingest.cpp#L215) | Callable definition: bool number_float(number_float_t,const string_t&) override | calls invalid · [reviewed contract](#b0031) |
| [B0032 · 216–238](../../../../../src/io/ingest.cpp#L216) | Callable definition: bool string(string_t& item) override | calls bounded, size, value, Date::parse; guard bounded(item.size(),limits.field_bytes,"input string field exceeds its byte limit"); value(Value{it…; returns true; true · [reviewed contract](#b0032) |
| [B0033 · 239–239](../../../../../src/io/ingest.cpp#L239) | Callable definition: bool binary(binary_t&) override | calls invalid · [reviewed contract](#b0033) |
| [B0034 · 240–246](../../../../../src/io/ingest.cpp#L240) | Callable definition: bool start_object(std::size_t) override | calls clear, reset, invalid; returns true · [reviewed contract](#b0034) |
| [B0035 · 247–260](../../../../../src/io/ingest.cpp#L247) | Callable definition: bool key(string_t& item) override | calls std::find, begin, end, invalid; guard require((seen&(1U&lt;&lt;index))==0,"invalid_document","duplicate input JSON field"); seen\|=1U&lt;&lt;index; ro…; returns true · [reviewed contract](#b0035) |
| [B0036 · 261–271](../../../../../src/io/ingest.cpp#L261) | Callable definition: bool end_object() override | calls ~, require, has_value, value; guard require((seen&required)==required,"invalid_document","physical input JSON is missing required field…; returns true · [reviewed contract](#b0036) |
| [B0037 · 272–275](../../../../../src/io/ingest.cpp#L272) | Callable definition: bool start_array(std::size_t) override | calls invalid; returns true · [reviewed contract](#b0037) |
| [B0038 · 276–276](../../../../../src/io/ingest.cpp#L276) | Callable definition: bool end_array() override | calls invalid; returns true · [reviewed contract](#b0038) |
| [B0039 · 277–279](../../../../../src/io/ingest.cpp#L277) | Callable definition: bool parse_error(std::size_t,const std::string&,const nlohmann::detail::exception& error) override | calls Error, what · [reviewed contract](#b0039) |
| [B0040 · 280–280](../../../../../src/io/ingest.cpp#L280) | Closes surrounding scope/type. |  · [reviewed contract](#b0040) |
| [B0041 · 281–290](../../../../../src/io/ingest.cpp#L281) | Callable definition: InputEvent json_event(std::string_view text,const auto& catalog,const InputLimits& limits,std::string_view fingerprint) | calls bounded, size, sax, require; guard bounded(text.size(),limits.record_bytes,"JSON input record exceeds its byte limit");; returns std::move(sax.event); growth insert · [reviewed contract](#b0041) |
| [B0042 · 291–307](../../../../../src/io/ingest.cpp#L291) | Type/record definition: struct BinaryReader | guard require(count&lt;=input.size()-position,"invalid_document","truncated binary input record");; returns result; result; 1 loop sites · [reviewed contract](#b0042) |
| [B0043 · 308–347](../../../../../src/io/ingest.cpp#L308) | Callable definition: InputEvent binary_event(std::string_view bytes,const auto& catalog,const InputLimits& limits,std::string_view fingerprint) | calls bounded, size, require, take; guard bounded(bytes.size(),limits.record_bytes,"binary input record exceeds its byte limit");; returns event; growth emplace_back, insert, reserve; 1 loop sites · [reviewed contract](#b0043) |
| [B0044 · 348–362](../../../../../src/io/ingest.cpp#L348) | Type/record definition: struct BinaryWriter | guard bounded(sum(output.size(),bytes.size()),limit,"binary input record exceeds its byte limit"); output…; growth push_back; 1 loop sites · [reviewed contract](#b0044) |
| [B0045 · 363–365](../../../../../src/io/ingest.cpp#L363) | declares namespace scope. | source comment (unverified): // namespace · [reviewed contract](#b0045) |
| [B0046 · 366–369](../../../../../src/io/ingest.cpp#L366) | Callable definition: template&lt;class CatalogView&gt; std::array&lt;char,64&gt; native_catalog_digest(const resource::MemoryAccount& account,const CatalogView& s… | calls catalog::validate_catalog, Buffer, canonical_catalog_to, sha256_fixed; returns sha256_fixed(out.output.view()) · [reviewed contract](#b0046) |
| [B0047 · 370–372](../../../../../src/io/ingest.cpp#L370) | Callable definition: std::array&lt;char,64&gt; catalog_digest(const resource::MemoryAccount& account,const Catalog& schema,bool admitted) | calls native_catalog_digest; returns native_catalog_digest(account,schema,admitted) · [reviewed contract](#b0047) |
| [B0048 · 373–375](../../../../../src/io/ingest.cpp#L373) | Callable definition: std::array&lt;char,64&gt; catalog_digest(const resource::MemoryAccount& account,const program::Catalog& schema,bool admitted) | calls native_catalog_digest; returns native_catalog_digest(account,schema,admitted) · [reviewed contract](#b0048) |
| [B0049 · 376–383](../../../../../src/io/ingest.cpp#L376) | Callable definition: resource::AccountedText catalog_fingerprint(const resource::MemoryAccount& account,const CatalogSource& catalog,bool admitted) | calls catalog_source_detail::read, catalog::validate_catalog, Buffer, canonical_catalog_to; returns catalog_source_detail::read(catalog,\[&\](const auto& schema) {; resource::AccountedText::copy_of(acc…; growth copy_of · [reviewed contract](#b0049) |
| [B0050 · 384–385](../../../../../src/io/ingest.cpp#L384) | Closes surrounding scope/type. | source comment (unverified): // namespace input_detail · [reviewed contract](#b0050) |
| [B0051 · 386–388](../../../../../src/io/ingest.cpp#L386) | Callable definition: template&lt;class CatalogView&gt; std::string input_catalog_sha256_impl(const CatalogView& catalog) | calls sha256, canonical_catalog; returns sha256(canonical_catalog(catalog)) · [reviewed contract](#b0051) |
| [B0052 · 389–389](../../../../../src/io/ingest.cpp#L389) | Callable definition: std::string input_catalog_sha256(const Catalog& catalog) | calls input_catalog_sha256_impl; returns input_catalog_sha256_impl(catalog) · [reviewed contract](#b0052) |
| [B0053 · 390–390](../../../../../src/io/ingest.cpp#L390) | Callable definition: std::string input_catalog_sha256(const program::Catalog& catalog) | calls input_catalog_sha256_impl; returns input_catalog_sha256_impl(catalog) · [reviewed contract](#b0053) |
| [B0054 · 391–391](../../../../../src/io/ingest.cpp#L391) | Explanatory comments or spacing. |  |
| [B0055 · 392–394](../../../../../src/io/ingest.cpp#L392) | Callable definition: template&lt;class CatalogView&gt; void validate_input_event_impl(const InputEvent& event,const CatalogView& catalog,InputLimits limits) | calls validate_event · [reviewed contract](#b0055) |
| [B0056 · 395–395](../../../../../src/io/ingest.cpp#L395) | Callable definition: void validate_input_event(const InputEvent& event,const Catalog& catalog,InputLimits limits) | calls validate_input_event_impl; returns validate_input_event_impl(event,catalog,limits) · [reviewed contract](#b0056) |
| [B0057 · 396–396](../../../../../src/io/ingest.cpp#L396) | Callable definition: void validate_input_event(const InputEvent& event,const program::Catalog& catalog,InputLimits limits) | calls validate_input_event_impl; returns validate_input_event_impl(event,catalog,limits) · [reviewed contract](#b0057) |
| [B0058 · 397–397](../../../../../src/io/ingest.cpp#L397) | Explanatory comments or spacing. |  |
| [B0059 · 398–401](../../../../../src/io/ingest.cpp#L398) | Callable definition: template&lt;class CatalogView&gt; InputEvent read_input_json_impl(std::string_view text,const CatalogView& catalog,InputLimits limits) | calls bounded, size, json_event, input_catalog_sha256; guard bounded(text.size(),limits.record_bytes,"JSON input record exceeds its byte limit");; returns json_event(text,catalog,limits,input_catalog_sha256(catalog)) · [reviewed contract](#b0059) |
| [B0060 · 402–402](../../../../../src/io/ingest.cpp#L402) | Callable definition: InputEvent read_input_json(std::string_view text,const Catalog& catalog,InputLimits limits) | calls read_input_json_impl; returns read_input_json_impl(text,catalog,limits) · [reviewed contract](#b0060) |
| [B0061 · 403–403](../../../../../src/io/ingest.cpp#L403) | Callable definition: InputEvent read_input_json(std::string_view text,const program::Catalog& catalog,InputLimits limits) | calls read_input_json_impl; returns read_input_json_impl(text,catalog,limits) · [reviewed contract](#b0061) |
| [B0062 · 404–404](../../../../../src/io/ingest.cpp#L404) | Explanatory comments or spacing. |  |
| [B0063 · 405–430](../../../../../src/io/ingest.cpp#L405) | Callable definition: template&lt;class CatalogView&gt; std::string write_input_json_impl(const InputEvent& event,const CatalogView& catalog,InputLimits limi… | calls input_catalog_sha256, validate_event, raw, text; returns std::move(out.output); growth insert; 1 loop sites · [reviewed contract](#b0063) |
| [B0064 · 431–431](../../../../../src/io/ingest.cpp#L431) | Callable definition: std::string write_input_json(const InputEvent& event,const Catalog& catalog,InputLimits limits) | calls write_input_json_impl; returns write_input_json_impl(event,catalog,limits) · [reviewed contract](#b0064) |
| [B0065 · 432–432](../../../../../src/io/ingest.cpp#L432) | Callable definition: std::string write_input_json(const InputEvent& event,const program::Catalog& catalog,InputLimits limits) | calls write_input_json_impl; returns write_input_json_impl(event,catalog,limits) · [reviewed contract](#b0065) |
| [B0066 · 433–433](../../../../../src/io/ingest.cpp#L433) | Explanatory comments or spacing. |  |
| [B0067 · 434–437](../../../../../src/io/ingest.cpp#L434) | Callable definition: template&lt;class CatalogView&gt; InputEvent read_input_binary_impl(std::string_view bytes,const CatalogView& catalog,InputLimits limit… | calls bounded, size, binary_event, input_catalog_sha256; guard bounded(bytes.size(),limits.record_bytes,"binary input record exceeds its byte limit");; returns binary_event(bytes,catalog,limits,input_catalog_sha256(catalog)) · [reviewed contract](#b0067) |
| [B0068 · 438–438](../../../../../src/io/ingest.cpp#L438) | Callable definition: InputEvent read_input_binary(std::string_view bytes,const Catalog& catalog,InputLimits limits) | calls read_input_binary_impl; returns read_input_binary_impl(bytes,catalog,limits) · [reviewed contract](#b0068) |
| [B0069 · 439–439](../../../../../src/io/ingest.cpp#L439) | Callable definition: InputEvent read_input_binary(std::string_view bytes,const program::Catalog& catalog,InputLimits limits) | calls read_input_binary_impl; returns read_input_binary_impl(bytes,catalog,limits) · [reviewed contract](#b0069) |
| [B0070 · 440–440](../../../../../src/io/ingest.cpp#L440) | Explanatory comments or spacing. |  |
| [B0071 · 441–465](../../../../../src/io/ingest.cpp#L441) | Callable definition: template&lt;class CatalogView&gt; std::string write_input_binary_impl(const InputEvent& event,const CatalogView& catalog,InputLimits li… | calls input_catalog_sha256, validate_event, raw, integer; guard bounded(event.update.values.size(),std::numeric_limits&lt;std::uint32_t&gt;::max(),"binary column count e…; returns std::move(out.output); growth insert; 2 loop sites · [reviewed contract](#b0071) |
| [B0072 · 466–466](../../../../../src/io/ingest.cpp#L466) | Callable definition: std::string write_input_binary(const InputEvent& event,const Catalog& catalog,InputLimits limits) | calls write_input_binary_impl; returns write_input_binary_impl(event,catalog,limits) · [reviewed contract](#b0072) |
| [B0073 · 467–467](../../../../../src/io/ingest.cpp#L467) | Callable definition: std::string write_input_binary(const InputEvent& event,const program::Catalog& catalog,InputLimits limits) | calls write_input_binary_impl; returns write_input_binary_impl(event,catalog,limits) · [reviewed contract](#b0073) |
| [B0074 · 468–470](../../../../../src/io/ingest.cpp#L468) | Closes surrounding scope/type. | source comment (unverified): // namespace crown::io · [reviewed contract](#b0074) |

## B0001

[Lines 1–30](../../../../../src/io/ingest.cpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
constexpr std::string_view magic="CROWNUPD";
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Fix the physical wire v1 framing and scalar-tag ABI. |
| inputs / outputs | Defines eight-byte CROWNUPD magic and fourteen-byte frame header; static_assert pins Value alternative order/types. |
| invariants | Tags 0..4 are int64/string/bool/date/decimal. Changing Value alternatives requires explicit wire review; no host struct or pointer layout is serialized. |
| ownership | Only static constants/type assertions; no owner or allocation. |
| failure | An incompatible Value alternative change fails compilation. |
| cost | Compile-time/static literal and size facts, no per-event runtime state. |
| Design | [docs/ingestion.md §Version-1 binary frame](../../../../ingestion.md) |

## B0002

[Lines 31–33](../../../../../src/io/ingest.cpp#L31); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void require(bool condition,std::string_view code,std::string_view message)
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

[Lines 34–36](../../../../../src/io/ingest.cpp#L34); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void bounded(std::size_t size,std::size_t limit,std::string_view description)
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

[Lines 37–40](../../../../../src/io/ingest.cpp#L37); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::size_t sum(std::size_t left,std::size_t right)
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

[Lines 41–45](../../../../../src/io/ingest.cpp#L41); `callable`; `contains_scoped_manual_contract`.

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

## B0006

[Lines 46–49](../../../../../src/io/ingest.cpp#L46); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
const auto& table_at(const auto& catalog,TableId table)
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

## B0007

[Lines 50–73](../../../../../src/io/ingest.cpp#L50); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void validate_event(const InputEvent& event,const auto& catalog,const InputLimits& limits)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Validate a complete caller-owned physical set event and minimum payload budget. |
| inputs / outputs | Checks table, positive sequence, insert/delete, column limit, full arity/types/decimal domain, scalar field/lower-bound record bytes, UTF-8, table name and optional source ID. |
| invariants | This is the non-null full source row; no projection, logical alias, compressed multiplicity or W05 nullable SQL row. Minimum int/bool bytes are one; fixed int/bool do not consume string field_bytes. No stream continuity/source-order check here. |
| ownership | Borrows stable caller input/catalog synchronously; only local private parser/output state changes. No physical runtime, accepted source sequence or source position is published here. |
| failure | Validation, scalar, size, encoding or allocation errors propagate; local owned scratch is released by RAII. No partial public event/text or accepted source progress is returned. |
| cost | O(full row width + string bytes + scalar spellings); date/owning decimal to_string can allocate. validate_row checks schema but does not revalidate all catalog metadata. |
| Design | [include/crown/io/ingest.hpp](../../../../../include/crown/io/ingest.hpp), [docs/ingestion.md](../../../../ingestion.md) |

## B0008

[Lines 74–78](../../../../../src/io/ingest.cpp#L74); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void check_binding(std::uint64_t catalog_version,std::uint64_t source_version,std::string_view fingerprint, TableId id,const auto& catalog,std::string_view expected)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Require the exact catalog/source-schema wire binding. |
| inputs / outputs | Wire catalog version, table source version and fingerprint must equal the supplied catalog/expected hash. |
| invariants | Fingerprint includes full canonical metadata; exact equality is a binding check, not authenticated transport or proof authority. |
| ownership | Borrows stable caller input/catalog synchronously; only local private parser/output state changes. No physical runtime, accepted source sequence or source position is published here. |
| failure | Validation, scalar, size, encoding or allocation errors propagate; local owned scratch is released by RAII. No partial public event/text or accepted source progress is returned. |
| cost | Fixed version comparisons and up to hash bytes; checked table lookup when earlier conditions pass. |
| Design | [include/crown/io/ingest.hpp](../../../../../include/crown/io/ingest.hpp), [docs/ingestion.md](../../../../ingestion.md) |

## B0009

[Lines 79–84](../../../../../src/io/ingest.cpp#L79); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
template<class String=std::string> struct JsonWriter {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Stream canonical JSON without constructing a JSON DOM. |
| inputs / outputs | Owns an output String and byte ceiling; public DTO uses std::string, native fingerprinting supplies account-backed Buffer. |
| invariants | raw admits full encoded length before append. Field escaping and canonical catalog structure are explicit, with no container-DOM teardown during unwinding. |
| ownership | String owns the growing private output. Native Buffer uses the supplied account; ordinary DTO output belongs to caller transport. |
| failure | Size/UTF-8/append allocation failure destroys private output and publishes no artifact. |
| cost | Amortized output growth and emitted bytes; no DOM, key sort or per-field wrapper allocation. |
| Design | [include/crown/io/ingest.hpp](../../../../../include/crown/io/ingest.hpp), [docs/ingestion.md](../../../../ingestion.md) |

## B0010

[Lines 85–87](../../../../../src/io/ingest.cpp#L85); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void raw(std::string_view text)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Admit and append canonical JSON bytes. |
| inputs / outputs | Checks overflow-safe output.size()+text.size() against limit, then appends. |
| invariants | Ceiling counts encoded length, not capacity/allocator overhead; earlier private appends stay local on error. |
| ownership | Borrows stable caller input/catalog synchronously; only local private parser/output state changes. No physical runtime, accepted source sequence or source position is published here. |
| failure | Validation, scalar, size, encoding or allocation errors propagate; local owned scratch is released by RAII. No partial public event/text or accepted source progress is returned. |
| cost | O(span bytes) plus possible output capacity relocation. |
| Design | [include/crown/io/ingest.hpp](../../../../../include/crown/io/ingest.hpp), [docs/ingestion.md](../../../../ingestion.md) |

## B0011

[Lines 88–107](../../../../../src/io/ingest.cpp#L88); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void text(std::string_view value)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Quote one valid UTF-8 string with deterministic JSON escapes. |
| inputs / outputs | Escapes quote, slash-control characters and remaining ASCII controls; valid non-control UTF-8 bytes are preserved. |
| invariants | NUL scalar strings become escaped JSON, not truncation; source-name rejection is separate. raw checks every escaping expansion. |
| ownership | Borrows stable caller input/catalog synchronously; only local private parser/output state changes. No physical runtime, accepted source sequence or source position is published here. |
| failure | Validation, scalar, size, encoding or allocation errors propagate; local owned scratch is released by RAII. No partial public event/text or accepted source progress is returned. |
| cost | UTF-8 pass plus O(input/output bytes); output growth depends on String allocator. |
| Design | [docs/ingestion.md §Version-1 JSONL event](../../../../ingestion.md), [schemas/physical-update-v1.schema.json](../../../../../schemas/physical-update-v1.schema.json) |

## B0012

[Lines 108–111](../../../../../src/io/ingest.cpp#L108); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void number(std::uint64_t value)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Encode one uint64 as exact JSON decimal digits. |
| inputs / outputs | to_chars writes into a 32-byte local buffer and appends the produced span. |
| invariants | 32 bytes exceed every uint64 decimal spelling; this fixed private numeric type needs no locale, heap stream or floating conversion. |
| ownership | Borrows stable caller input/catalog synchronously; only local private parser/output state changes. No physical runtime, accepted source sequence or source position is published here. |
| failure | Validation, scalar, size, encoding or allocation errors propagate; local owned scratch is released by RAII. No partial public event/text or accepted source progress is returned. |
| cost | Bounded integer conversion and at most twenty digits plus output growth. |
| Design | [docs/ingestion.md §Version-1 JSONL event](../../../../ingestion.md), [schemas/physical-update-v1.schema.json](../../../../../schemas/physical-update-v1.schema.json) |

## B0013

[Lines 112–115](../../../../../src/io/ingest.cpp#L112); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void signed_number(std::int64_t value)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Encode one int64 as exact JSON decimal digits. |
| inputs / outputs | to_chars uses a 32-byte local buffer, including sign and INT64_MIN. |
| invariants | Fixed buffer exceeds signed 64-bit spelling; no float/locale/coercion. |
| ownership | Borrows stable caller input/catalog synchronously; only local private parser/output state changes. No physical runtime, accepted source sequence or source position is published here. |
| failure | Validation, scalar, size, encoding or allocation errors propagate; local owned scratch is released by RAII. No partial public event/text or accepted source progress is returned. |
| cost | Bounded conversion/digit append; no separate formatting heap buffer. |
| Design | [docs/ingestion.md §Version-1 JSONL event](../../../../ingestion.md), [schemas/physical-update-v1.schema.json](../../../../../schemas/physical-update-v1.schema.json) |

## B0014

[Lines 116–116](../../../../../src/io/ingest.cpp#L116); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L116-L116:sha256:aa1d1a63390229c798347e83a0405441c9400035284ad168c1bf6cdf1d70a370
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Closes the enclosing helper type at this source boundary; this is a lexical delimiter, not an operation. |
| inputs / outputs | No runtime input or output. Declarations following the span leave the preceding C++ scope. |
| invariants | The delimiter ends the preceding scope's visibility/linkage region; it adds no validation, publication, ownership transfer, or runtime authority. |
| ownership | The delimiter adds no owner. If it ends a function/block with live automatic objects, their normal destructors release those objects; namespace and type-definition closes change no existing object's lifetime. |
| failure | No explicit failure translation or catch is added. If a function/block exit destroys automatic objects, exception behavior follows those destructors; namespace/type closes have no runtime failure path. |
| cost | The delimiter adds no algorithmic work. A function/block exit can run existing automatic-object destructors and cleanup; namespace/type closes have no runtime cost. |
| Design | [src/io/ingest.cpp](../../../../../src/io/ingest.cpp), [docs/code_specs/files/src/io/ingest.cpp.md](ingest.cpp.md), [docs/ingestion.md](../../../../ingestion.md), [docs/session_lifecycle.md](../../../../session_lifecycle.md) |

## B0015

[Lines 117–121](../../../../../src/io/ingest.cpp#L117); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void names(auto& out,const auto& table,const auto& columns)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Encode an ordered catalog column-ID list by source column names. |
| inputs / outputs | Borrows table and already validated IDs and writes a string-name array. |
| invariants | IDs must be within that table; order/repeats from the catalog are retained, not re-sorted. |
| ownership | Borrows stable caller input/catalog synchronously; only local private parser/output state changes. No physical runtime, accepted source sequence or source position is published here. |
| failure | Validation, scalar, size, encoding or allocation errors propagate; local owned scratch is released by RAII. No partial public event/text or accepted source progress is returned. |
| cost | O(list length + name escaping/output bytes), no extra vector. |
| Design | [src/catalog/catalog.cpp](../../../../../src/catalog/catalog.cpp), [include/crown/io/ingest.hpp](../../../../../include/crown/io/ingest.hpp), [docs/ingestion.md](../../../../ingestion.md) |

## B0016

[Lines 122–123](../../../../../src/io/ingest.cpp#L122); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L122-L123:sha256:d369e3553008b9330b32b773f2cd1af25b9e3540673bc2c2ecbeae1b0004e38f
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Design note for adjacent code: Full metadata, including hints/statistics and constraint status, binds v1. Callers validate the catalog or retain an already admitted immutable owner. This is caller guidance recorded as prose, not an executable result. |
| inputs / outputs | No runtime interface is implemented by these comment-only lines. They sit at src/io/ingest.cpp lines 120-125; the surrounding declaration/body defines its own inputs and outputs. |
| invariants | The words record the intended use boundary only. They do not add a guard, proof, capability, transaction, durability guarantee, or account charge; verify behavior in the referenced implementation. |
| ownership | Comment text owns no data. Object lifetimes, borrows, and account attribution remain those of the adjacent source objects and their constructors. |
| failure | No failure path is implemented here. Any mentioned failure or recovery rule belongs to the adjacent operation and its existing error carrier. |
| cost | No runtime work is performed by these lines; any cost/bound in the note is not certified by this comment-only card. |
| Design | [src/io/ingest.cpp](../../../../../src/io/ingest.cpp), [docs/code_specs/files/src/io/ingest.cpp.md](ingest.cpp.md), [docs/ingestion.md](../../../../ingestion.md), [docs/session_lifecycle.md](../../../../session_lifecycle.md) |

## B0017

[Lines 124–168](../../../../../src/io/ingest.cpp#L124); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void canonical_catalog_to(const auto& catalog,auto& out)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Serialize the complete canonical catalog binding used by input wire v1. |
| inputs / outputs | Writes ordered tables/columns, type/nullability/binary collation/decimal specs, constraints/targets, hints, source versions and statistics under schema_version 1. |
| invariants | Catalog validity is established by caller or admitted program. Full metadata, including hints/statistics/untrusted status, contributes to binding; not just row layout or table names. |
| ownership | Borrows stable caller input/catalog synchronously; only local private parser/output state changes. No physical runtime, accepted source sequence or source position is published here. |
| failure | Validation, scalar, size, encoding or allocation errors propagate; local owned scratch is released by RAII. No partial public event/text or accepted source progress is returned. |
| cost | O(catalog metadata/name bytes + encoded output); deterministic field order, no DOM or lookup-map construction. |
| Design | [include/crown/io/ingest.hpp](../../../../../include/crown/io/ingest.hpp), [docs/ingestion.md](../../../../ingestion.md) |

## B0018

[Lines 169–171](../../../../../src/io/ingest.cpp#L169); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::string canonical_catalog(const auto& catalog)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Validate a catalog and materialize its canonical DTO JSON. |
| inputs / outputs | Runs catalog::validate_catalog before streaming into ordinary std::string. |
| invariants | This explicit public/hash preparation has catalog-wide validation cost; native admitted readers reuse separate funded hashing paths. |
| ownership | Returns an owning ordinary string; caller catalog is borrowed only during construction. |
| failure | Validation, scalar, size, encoding or allocation errors propagate; local owned scratch is released by RAII. No partial public event/text or accepted source progress is returned. |
| cost | Catalog validation scratch plus O(catalog/encoded bytes) output allocation. |
| Design | [src/catalog/catalog.cpp](../../../../../src/catalog/catalog.cpp), [include/crown/io/ingest.hpp](../../../../../include/crown/io/ingest.hpp), [docs/ingestion.md](../../../../ingestion.md) |

## B0019

[Lines 172–173](../../../../../src/io/ingest.cpp#L172); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct EventSax : nlohmann::json_sax<Json> {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Implement the public owning-event JSON SAX schema callbacks. |
| inputs / outputs | Third-party tokenizer invokes fixed schema callbacks; the eventual result is an owning InputEvent DTO. |
| invariants | No nlohmann DOM is retained. This public path still uses ordinary parser tokens, strings/vectors and diagnostics; it is not the account-backed operational JsonReader. |
| ownership | SAX owns partial DTO strings/scalars/event; limits is borrowed through the parse. |
| failure | Callbacks throw directly on schema/number/size/domain errors; no event is returned after a failed parse. |
| cost | O(record tokens/bytes + scalar copies) with bounded schema state, no arbitrary object graph retention. |
| Design | [docs/ingestion.md §Version-1 JSONL event](../../../../ingestion.md), [schemas/physical-update-v1.schema.json](../../../../../schemas/physical-update-v1.schema.json) |

## B0020

[Lines 174–174](../../../../../src/io/ingest.cpp#L174); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
enum class Context
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Name the finite public SAX nesting state. |
| inputs / outputs | none/root/values/scalar/source/done describe admitted positions. |
| invariants | Only root, values, tagged scalar and source-position nesting is legal; done requires complete root fields. |
| ownership | Inline enum state within EventSax; no independent ownership. |
| failure | Invalid transitions are rejected by callbacks, not this declaration. |
| cost | Enum state only, no dynamic parse stack owned by this schema. |
| Design | [docs/ingestion.md §Version-1 JSONL event](../../../../ingestion.md), [schemas/physical-update-v1.schema.json](../../../../../schemas/physical-update-v1.schema.json) |

## B0021

[Lines 175–175](../../../../../src/io/ingest.cpp#L175); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
enum class Key
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Fix root-field ordinals shared by SAX key lookup and duplicate bitset. |
| inputs / outputs | Key order corresponds exactly to the nine names array in key(); none is the initial unset value. |
| invariants | Ordinal bits identify required fields; source is optional. Reordering one side without the other would change admission. |
| ownership | Inline discriminant, no ownership. |
| failure | Callbacks validate keys/duplicates before consuming their values. |
| cost | Compile-time enum/bit positions, no allocation. |
| Design | [docs/ingestion.md §Version-1 JSONL event](../../../../ingestion.md), [schemas/physical-update-v1.schema.json](../../../../../schemas/physical-update-v1.schema.json) |

## B0022

[Lines 176–184](../../../../../src/io/ingest.cpp#L176); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
  const InputLimits& limits;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Retain the SAX schema state and partial owning DTO. |
| inputs / outputs | Stores borrowed limits, current/root/source keys, seen masks, pending tagged scalar, binding strings/versions and initially empty event. |
| invariants | Context and seen masks enforce one exact root/source/tagged shape; partially assembled ordinary DTO state remains private until json_event succeeds. |
| ownership | EventSax owns all partial strings/row values; only limits is borrowed. |
| failure | Destruction releases partial ordinary values; it neither acknowledges a reader nor mutates an engine. |
| cost | Fixed fields plus dynamic strings/row vector as tokens arrive; not funded native runtime storage. |
| Design | [docs/ingestion.md §Version-1 JSONL event](../../../../ingestion.md), [schemas/physical-update-v1.schema.json](../../../../../schemas/physical-update-v1.schema.json) |

## B0023

[Lines 185–185](../../../../../src/io/ingest.cpp#L185); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
explicit EventSax(const InputLimits& budget):limits(budget)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Start SAX parsing with borrowed immutable limits. |
| inputs / outputs | Stores the budget reference; other partial fields retain defaults. |
| invariants | Caller keeps limits alive through sax_parse; constructor does not admit a record or consume stream bytes. |
| ownership | Borrows stable caller input/catalog synchronously; only local private parser/output state changes. No physical runtime, accepted source sequence or source position is published here. |
| failure | No explicit schema error; later callbacks perform admission. |
| cost | Fixed reference/default initialization. |
| Design | [docs/ingestion.md §Version-1 JSONL event](../../../../ingestion.md), [schemas/physical-update-v1.schema.json](../../../../../schemas/physical-update-v1.schema.json) |

## B0024

[Lines 186–186](../../../../../src/io/ingest.cpp#L186); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
[[noreturn]] static void invalid()
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Reject a schema-incompatible public JSON token/transition. |
| inputs / outputs | Always throws invalid_document with fixed physical-event schema message. |
| invariants | No recovery, fallback field coercion or guessed default event. |
| ownership | Borrows stable caller input/catalog synchronously; only local private parser/output state changes. No physical runtime, accepted source sequence or source position is published here. |
| failure | Always throws; public diagnostic allocation can itself fail. |
| cost | Failure-only diagnostic construction/throw. |
| Design | [docs/ingestion.md §Version-1 JSONL event](../../../../ingestion.md), [schemas/physical-update-v1.schema.json](../../../../../schemas/physical-update-v1.schema.json) |

## B0025

[Lines 187–190](../../../../../src/io/ingest.cpp#L187); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void value(Value item)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Append one owning scalar after admitting the next column. |
| inputs / outputs | Checks current count+1 against columns, then moves/copies Value into event row. |
| invariants | Column cap precedes vector growth; source schema arity/type validation happens after complete parsing. |
| ownership | Borrows stable caller input/catalog synchronously; only local private parser/output state changes. No physical runtime, accepted source sequence or source position is published here. |
| failure | Validation, scalar, size, encoding or allocation errors propagate; local owned scratch is released by RAII. No partial public event/text or accepted source progress is returned. |
| cost | Amortized vector growth plus Value ownership/copy cost; owning Decimal/string may allocate. |
| Design | [docs/ingestion.md §Version-1 JSONL event](../../../../ingestion.md), [schemas/physical-update-v1.schema.json](../../../../../schemas/physical-update-v1.schema.json) |

## B0026

[Lines 191–206](../../../../../src/io/ingest.cpp#L191); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
bool unsigned_value(std::uint64_t item)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Route an unsigned integer token to a scalar or envelope field. |
| inputs / outputs | Row value requires &lt;=INT64_MAX; source offset takes uint64; root version/catalog/source version/sequence accept uint64. |
| invariants | Numbers in other context/keys reject; no signed wrap or Boolean/numeric conflation. |
| ownership | Borrows stable caller input/catalog synchronously; only local private parser/output state changes. No physical runtime, accepted source sequence or source position is published here. |
| failure | Validation, scalar, size, encoding or allocation errors propagate; local owned scratch is released by RAII. No partial public event/text or accepted source progress is returned. |
| cost | Fixed dispatch plus optional row append. |
| Design | [docs/ingestion.md §Version-1 JSONL event](../../../../ingestion.md), [schemas/physical-update-v1.schema.json](../../../../../schemas/physical-update-v1.schema.json) |

## B0027

[Lines 207–207](../../../../../src/io/ingest.cpp#L207); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
bool null() override
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Reject JSON null for the non-null physical input wire. |
| inputs / outputs | Any null token calls invalid(). |
| invariants | Nullable W05 SQL rows use a separate family; null is never converted to an absent scalar or zero here. |
| ownership | Borrows stable caller input/catalog synchronously; only local private parser/output state changes. No physical runtime, accepted source sequence or source position is published here. |
| failure | Always invalid_document (or failure during diagnostic construction). |
| cost | Failure-only fixed dispatch. |
| Design | [docs/ingestion.md §Version-1 JSONL event](../../../../ingestion.md), [schemas/physical-update-v1.schema.json](../../../../../schemas/physical-update-v1.schema.json) |

## B0028

[Lines 208–208](../../../../../src/io/ingest.cpp#L208); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
bool boolean(bool item) override
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Admit a Boolean only as a row scalar. |
| inputs / outputs | Values context appends bool; every other context rejects. |
| invariants | No Boolean envelope versions/offsets, and bool remains its exact Value alternative. |
| ownership | Borrows stable caller input/catalog synchronously; only local private parser/output state changes. No physical runtime, accepted source sequence or source position is published here. |
| failure | Validation, scalar, size, encoding or allocation errors propagate; local owned scratch is released by RAII. No partial public event/text or accepted source progress is returned. |
| cost | Fixed context check plus row append. |
| Design | [docs/ingestion.md §Version-1 JSONL event](../../../../ingestion.md), [schemas/physical-update-v1.schema.json](../../../../../schemas/physical-update-v1.schema.json) |

## B0029

[Lines 209–213](../../../../../src/io/ingest.cpp#L209); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
bool number_integer(number_integer_t item) override
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Admit signed JSON integers while preserving envelope unsigned domains. |
| inputs / outputs | Row context appends int64; elsewhere negative values reject and nonnegative values delegate unsigned_value. |
| invariants | Negative zero is numerically zero in tokenizer semantics; no float accepts an integer field. |
| ownership | Borrows stable caller input/catalog synchronously; only local private parser/output state changes. No physical runtime, accepted source sequence or source position is published here. |
| failure | Validation, scalar, size, encoding or allocation errors propagate; local owned scratch is released by RAII. No partial public event/text or accepted source progress is returned. |
| cost | Fixed dispatch plus delegated append/envelope assignment. |
| Design | [docs/ingestion.md §Version-1 JSONL event](../../../../ingestion.md), [schemas/physical-update-v1.schema.json](../../../../../schemas/physical-update-v1.schema.json) |

## B0030

[Lines 214–214](../../../../../src/io/ingest.cpp#L214); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
bool number_unsigned(number_unsigned_t item) override
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Delegate a uint64 JSON token through the exact envelope/row rules. |
| inputs / outputs | Calls unsigned_value without narrowing. |
| invariants | Large positive row scalars reject while valid uint64 sequence/offset remains representable. |
| ownership | Borrows stable caller input/catalog synchronously; only local private parser/output state changes. No physical runtime, accepted source sequence or source position is published here. |
| failure | Validation, scalar, size, encoding or allocation errors propagate; local owned scratch is released by RAII. No partial public event/text or accepted source progress is returned. |
| cost | Fixed forwarding plus delegated checks. |
| Design | [docs/ingestion.md §Version-1 JSONL event](../../../../ingestion.md), [schemas/physical-update-v1.schema.json](../../../../../schemas/physical-update-v1.schema.json) |

## B0031

[Lines 215–215](../../../../../src/io/ingest.cpp#L215); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
bool number_float(number_float_t,const string_t&) override
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Reject every floating JSON numeric token. |
| inputs / outputs | number_float always calls invalid(), including 1.0/exponent spellings. |
| invariants | No float-to-integer or float-to-exact-decimal fallback. |
| ownership | Borrows stable caller input/catalog synchronously; only local private parser/output state changes. No physical runtime, accepted source sequence or source position is published here. |
| failure | Always invalid_document; no row published. |
| cost | Failure-only dispatch. |
| Design | [docs/ingestion.md §Version-1 JSONL event](../../../../ingestion.md), [schemas/physical-update-v1.schema.json](../../../../../schemas/physical-update-v1.schema.json) |

## B0032

[Lines 216–238](../../../../../src/io/ingest.cpp#L216); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
bool string(string_t& item) override
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Route a JSON string to exact row, tagged scalar, source or binding fields. |
| inputs / outputs | Values become owning text under field cap; tagged date/decimal parse exact values; source names validate; root accepts hash/table/insert-delete operation only. |
| invariants | Hash length must be 64 before later exact comparison. Date/decimal aliases normalize through their parsers; raw string does not coerce to another column type. |
| ownership | Borrows stable caller input/catalog synchronously; only local private parser/output state changes. No physical runtime, accepted source sequence or source position is published here. |
| failure | Validation, scalar, size, encoding or allocation errors propagate; local owned scratch is released by RAII. No partial public event/text or accepted source progress is returned. |
| cost | O(token/scalar bytes), ordinary copies/parsing and possible Value allocations. |
| Design | [docs/ingestion.md §Version-1 JSONL event](../../../../ingestion.md), [schemas/physical-update-v1.schema.json](../../../../../schemas/physical-update-v1.schema.json) |

## B0033

[Lines 239–239](../../../../../src/io/ingest.cpp#L239); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
bool binary(binary_t&) override
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Reject binary-valued SAX input tokens. |
| inputs / outputs | binary callback always calls invalid(). |
| invariants | This JSON text schema has no binary token encoding; the separately framed binary wire has its own decoder. |
| ownership | Borrows stable caller input/catalog synchronously; only local private parser/output state changes. No physical runtime, accepted source sequence or source position is published here. |
| failure | Always invalid_document. |
| cost | Failure-only dispatch. |
| Design | [docs/ingestion.md §Version-1 JSONL event](../../../../ingestion.md), [schemas/physical-update-v1.schema.json](../../../../../schemas/physical-update-v1.schema.json) |

## B0034

[Lines 240–246](../../../../../src/io/ingest.cpp#L240); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
bool start_object(std::size_t) override
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Enter only an admitted root/source/tagged-scalar object. |
| inputs / outputs | none becomes root; root source opens its optional position; values opens one tagged scalar. |
| invariants | Other nested objects reject. Tagged state clears old key/value before parsing; source offset/name remain private until root success. |
| ownership | Borrows stable caller input/catalog synchronously; only local private parser/output state changes. No physical runtime, accepted source sequence or source position is published here. |
| failure | Validation, scalar, size, encoding or allocation errors propagate; local owned scratch is released by RAII. No partial public event/text or accepted source progress is returned. |
| cost | Fixed state changes plus default optional/string state; no DOM allocation. |
| Design | [docs/ingestion.md §Version-1 JSONL event](../../../../ingestion.md), [schemas/physical-update-v1.schema.json](../../../../../schemas/physical-update-v1.schema.json) |

## B0035

[Lines 247–260](../../../../../src/io/ingest.cpp#L247); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
bool key(string_t& item) override
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Validate object keys and reject unknown/duplicate fields. |
| inputs / outputs | Root maps nine exact names to Key/bits; source allows source/offset once; scalar allows exactly one date/decimal key. |
| invariants | Bitset/one-key checks happen before consuming the matching value; no key map or case folding is used. |
| ownership | Borrows stable caller input/catalog synchronously; only local private parser/output state changes. No physical runtime, accepted source sequence or source position is published here. |
| failure | Validation, scalar, size, encoding or allocation errors propagate; local owned scratch is released by RAII. No partial public event/text or accepted source progress is returned. |
| cost | Fixed nine-name scan/root or two-name checks, string comparisons/copy for tagged key. |
| Design | [docs/ingestion.md §Version-1 JSONL event](../../../../ingestion.md), [schemas/physical-update-v1.schema.json](../../../../../schemas/physical-update-v1.schema.json) |

## B0036

[Lines 261–271](../../../../../src/io/ingest.cpp#L261); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
bool end_object() override
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Close an object only after its mandatory fields are complete. |
| inputs / outputs | Root requires all fields except source; source requires both members; scalar requires a parsed value then appends it. |
| invariants | Closing a root transitions done; source returns root and scalar returns values. Empty/malformed tagged/source objects cannot publish default values. |
| ownership | Borrows stable caller input/catalog synchronously; only local private parser/output state changes. No physical runtime, accepted source sequence or source position is published here. |
| failure | Validation, scalar, size, encoding or allocation errors propagate; local owned scratch is released by RAII. No partial public event/text or accepted source progress is returned. |
| cost | Fixed mask/state checks plus optional row append. |
| Design | [docs/ingestion.md §Version-1 JSONL event](../../../../ingestion.md), [schemas/physical-update-v1.schema.json](../../../../../schemas/physical-update-v1.schema.json) |

## B0037

[Lines 272–275](../../../../../src/io/ingest.cpp#L272); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
bool start_array(std::size_t) override
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Enter the sole legal values array. |
| inputs / outputs | Only root at Key::values may open an array. |
| invariants | No nested arrays, extra sequence payloads or array-form tagged scalars. |
| ownership | Borrows stable caller input/catalog synchronously; only local private parser/output state changes. No physical runtime, accepted source sequence or source position is published here. |
| failure | Validation, scalar, size, encoding or allocation errors propagate; local owned scratch is released by RAII. No partial public event/text or accepted source progress is returned. |
| cost | Fixed context transition. |
| Design | [docs/ingestion.md §Version-1 JSONL event](../../../../ingestion.md), [schemas/physical-update-v1.schema.json](../../../../../schemas/physical-update-v1.schema.json) |

## B0038

[Lines 276–276](../../../../../src/io/ingest.cpp#L276); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
bool end_array() override
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Close the values array and return to root. |
| inputs / outputs | Only values context succeeds. |
| invariants | Array completion is separate from final row schema/type/arity validation. |
| ownership | Borrows stable caller input/catalog synchronously; only local private parser/output state changes. No physical runtime, accepted source sequence or source position is published here. |
| failure | Validation, scalar, size, encoding or allocation errors propagate; local owned scratch is released by RAII. No partial public event/text or accepted source progress is returned. |
| cost | Fixed state transition. |
| Design | [docs/ingestion.md §Version-1 JSONL event](../../../../ingestion.md), [schemas/physical-update-v1.schema.json](../../../../../schemas/physical-update-v1.schema.json) |

## B0039

[Lines 277–279](../../../../../src/io/ingest.cpp#L277); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
bool parse_error(std::size_t,const std::string&,const nlohmann::detail::exception& error) override
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Translate tokenizer syntax errors to public invalid_document. |
| inputs / outputs | SAX parse_error throws Error using the third-party diagnostic text. |
| invariants | This public DTO path retains tokenizer wording; native JsonReader intentionally uses stable fixed syntax text. |
| ownership | Borrows stable caller input/catalog synchronously; only local private parser/output state changes. No physical runtime, accepted source sequence or source position is published here. |
| failure | Always throws invalid_document; allocation failure in diagnostic construction can propagate. |
| cost | Failure-only copying/throw, no DOM cleanup. |
| Design | [docs/ingestion.md §Version-1 JSONL event](../../../../ingestion.md), [schemas/physical-update-v1.schema.json](../../../../../schemas/physical-update-v1.schema.json) |

## B0040

[Lines 280–280](../../../../../src/io/ingest.cpp#L280); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L280-L280:sha256:aa1d1a63390229c798347e83a0405441c9400035284ad168c1bf6cdf1d70a370
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Closes the enclosing helper type at this source boundary; this is a lexical delimiter, not an operation. |
| inputs / outputs | No runtime input or output. Declarations following the span leave the preceding C++ scope. |
| invariants | The delimiter ends the preceding scope's visibility/linkage region; it adds no validation, publication, ownership transfer, or runtime authority. |
| ownership | The delimiter adds no owner. If it ends a function/block with live automatic objects, their normal destructors release those objects; namespace and type-definition closes change no existing object's lifetime. |
| failure | No explicit failure translation or catch is added. If a function/block exit destroys automatic objects, exception behavior follows those destructors; namespace/type closes have no runtime failure path. |
| cost | The delimiter adds no algorithmic work. A function/block exit can run existing automatic-object destructors and cleanup; namespace/type closes have no runtime cost. |
| Design | [src/io/ingest.cpp](../../../../../src/io/ingest.cpp), [docs/code_specs/files/src/io/ingest.cpp.md](ingest.cpp.md), [docs/ingestion.md](../../../../ingestion.md), [docs/session_lifecycle.md](../../../../session_lifecycle.md) |

## B0041

[Lines 281–290](../../../../../src/io/ingest.cpp#L281); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
InputEvent json_event(std::string_view text,const auto& catalog,const InputLimits& limits,std::string_view fingerprint)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Decode one complete JSON DTO event against the exact supplied catalog. |
| inputs / outputs | Checks record length, parses via SAX, requires completed root/version1, resolves physical table, checks full binding and validates complete event. |
| invariants | No source continuity/acknowledgement occurs; row/domain validation follows token ownership and binding. Caller supplies expected canonical fingerprint. |
| ownership | Returns owning InputEvent by moving SAX state; it borrows neither input text nor caller catalog afterward. |
| failure | Validation, scalar, size, encoding or allocation errors propagate; local owned scratch is released by RAII. No partial public event/text or accepted source progress is returned. |
| cost | O(record tokens/bytes + full-row validation + physical table/catalog lookup); public find_table can validate catalog with ordinary scratch. |
| Design | [docs/ingestion.md §Version-1 JSONL event](../../../../ingestion.md), [schemas/physical-update-v1.schema.json](../../../../../schemas/physical-update-v1.schema.json) |

## B0042

[Lines 291–307](../../../../../src/io/ingest.cpp#L291); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct BinaryReader
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Read bounded little-endian binary fields into public DTO values. |
| inputs / outputs | take returns borrowed slices and advances position; integer decodes fixed 1/2/4/8 byte widths; string validates uint32 length/UTF-8 then owns a copy. |
| invariants | position &lt;= input.size() is maintained; private integer callers pass width&lt;=8. Length cap precedes payload take/copy; no host ABI reinterpretation. |
| ownership | Reader borrows one immutable complete frame. Only string() returns owning ordinary text. |
| failure | Truncation, length cap, text or allocation errors leave only private position/partial event state. |
| cost | O(bytes taken/string UTF-8/copy), fixed-width integer work; returned string may allocate. |
| Design | [docs/ingestion.md §Version-1 binary frame](../../../../ingestion.md) |

## B0043

[Lines 308–347](../../../../../src/io/ingest.cpp#L308); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
InputEvent binary_event(std::string_view bytes,const auto& catalog,const InputLimits& limits,std::string_view fingerprint)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Decode one complete canonical version1 binary DTO event. |
| inputs / outputs | Checks frame/magic/version/exact length, catalog/source hash, sequence/table/operation/position, schema arity/remaining payload, tags and no trailing bytes. |
| invariants | Row count/schema/minimum remaining bytes are checked before reserve. Bool flags are 0/1; signed bits preserve int64; date is ten bytes; decimal spelling must already be canonical. Full domain/source checks follow parsing. |
| ownership | Returns a fully owning InputEvent independent of borrowed bytes; partial DTO is released on failure. |
| failure | Validation, scalar, size, encoding or allocation errors propagate; local owned scratch is released by RAII. No partial public event/text or accepted source progress is returned. |
| cost | O(frame/row/scalar bytes + public catalog/hash/table validation costs); owns ordinary row/text and decimal temporaries. |
| Design | [docs/ingestion.md §Version-1 binary frame](../../../../ingestion.md) |

## B0044

[Lines 348–362](../../../../../src/io/ingest.cpp#L348); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct BinaryWriter
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Encode one byte-capped public binary frame through explicit little-endian primitives. |
| inputs / outputs | raw appends spans; integer writes low count bytes; string writes uint32 length then payload. |
| invariants | Private integer widths are fixed &lt;=8 and callers validate length/arity before narrowing. Each append checks overflow/cap; native pointers, object layout and host endian never enter wire bytes. |
| ownership | BinaryWriter uniquely owns private ordinary output until public encoder moves it out. |
| failure | Overflow, uint32-length, byte cap or append allocation errors return no partial frame. |
| cost | O(output bytes) with amortized ordinary string growth; fixed-width integer shifting, no DOM. |
| Design | [docs/ingestion.md §Version-1 binary frame](../../../../ingestion.md) |

## B0045

[Lines 363–365](../../../../../src/io/ingest.cpp#L363); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L363-L365:sha256:787bdb4523501d1f3f8472719fbdef0de4dc78de38215420ea9df778ff3464d3
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Closes the top-level JSON/binary codec helper namespace and opens input_detail for catalog fingerprint, account-owned canonical metadata, and native input helpers. |
| inputs / outputs | No external runtime input/output is performed by the declaration itself; callable signatures in the block describe future use. |
| invariants | The declaration fixes the source-local names and member/type shape; runtime validation and authority remain with the actual implementations. |
| ownership | No owner is added merely by a declaration. Typed fields keep the ownership behavior of their C++ types and any explicit account allocator. |
| failure | No runtime catch or translation is added here; constructor/member failures remain in their implementation. |
| cost | Declaration-only compile/link work, except that constructing a declared type later may initialize or allocate its members. |
| Design | [src/io/ingest.cpp](../../../../../src/io/ingest.cpp), [docs/code_specs/files/src/io/ingest.cpp.md](ingest.cpp.md), [docs/ingestion.md](../../../../ingestion.md), [docs/session_lifecycle.md](../../../../session_lifecycle.md) |

## B0046

[Lines 366–369](../../../../../src/io/ingest.cpp#L366); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
template<class CatalogView> std::array<char,64> native_catalog_digest(const resource::MemoryAccount& account,const CatalogView& schema,bool admitted)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Compute native canonical catalog SHA using funded serialization scratch. |
| inputs / outputs | Supplied account/catalog plus admitted flag produces a fixed 64-character hash array. |
| invariants | Non-admitted catalogs validate first; admitted immutable catalog bypasses repeated validation. Canonical full metadata is unchanged across DTO/native representations. |
| ownership | Borrows account/catalog for synchronous work; temporary Buffer consumes the supplied account and fixed array owns returned digest bytes. |
| failure | Validation, scalar, size, encoding or allocation errors propagate; local owned scratch is released by RAII. No partial public event/text or accepted source progress is returned. |
| cost | O(catalog/canonical bytes), account-backed Buffer capacity plus fixed digest output; validation scratch remains separate when requested. |
| Design | [docs/ingestion.md §Native reader API and memory grant](../../../../ingestion.md), [docs/memory_accounts.md §Native streaming input ownership](../../../../memory_accounts.md) |

## B0047

[Lines 370–372](../../../../../src/io/ingest.cpp#L370); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::array<char,64> catalog_digest(const resource::MemoryAccount& account,const Catalog& schema,bool admitted)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Dispatch funded digest computation for owned Catalog. |
| inputs / outputs | Forwards account/schema/admitted flag to native_catalog_digest. |
| invariants | No second grant or duplicate canonical format is created by this overload. |
| ownership | Borrows stable caller input/catalog synchronously; only local private parser/output state changes. No physical runtime, accepted source sequence or source position is published here. |
| failure | Validation, scalar, size, encoding or allocation errors propagate; local owned scratch is released by RAII. No partial public event/text or accepted source progress is returned. |
| cost | Fixed forwarding plus catalog serialization/hash/optional validation. |
| Design | [docs/ingestion.md §Native reader API and memory grant](../../../../ingestion.md), [docs/memory_accounts.md §Native streaming input ownership](../../../../memory_accounts.md) |

## B0048

[Lines 373–375](../../../../../src/io/ingest.cpp#L373); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::array<char,64> catalog_digest(const resource::MemoryAccount& account,const program::Catalog& schema,bool admitted)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Dispatch funded digest computation for immutable program::Catalog. |
| inputs / outputs | Forwards account/schema/admitted flag to native_catalog_digest. |
| invariants | No second grant or duplicate canonical format is created by this overload. |
| ownership | Borrows stable caller input/catalog synchronously; only local private parser/output state changes. No physical runtime, accepted source sequence or source position is published here. |
| failure | Validation, scalar, size, encoding or allocation errors propagate; local owned scratch is released by RAII. No partial public event/text or accepted source progress is returned. |
| cost | Fixed forwarding plus catalog serialization/hash/optional validation. |
| Design | [docs/ingestion.md §Native reader API and memory grant](../../../../ingestion.md), [docs/memory_accounts.md §Native streaming input ownership](../../../../memory_accounts.md) |

## B0049

[Lines 376–383](../../../../../src/io/ingest.cpp#L376); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
resource::AccountedText catalog_fingerprint(const resource::MemoryAccount& account,const CatalogSource& catalog,bool admitted)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Retain the reader catalog fingerprint under its receiving account. |
| inputs / outputs | Visits actual CatalogSource, optionally validates, serializes through funded Buffer and copies fixed digest into AccountedText. |
| invariants | Catalog hash covers all metadata; once retained it is reused per record. AccountedText is immutable metadata, not ordinary ambient digest storage. |
| ownership | Returned AccountedText owns its real bytes under the supplied account; catalog remains owned by CatalogSource. |
| failure | Validation, scalar, size, encoding or allocation errors propagate; local owned scratch is released by RAII. No partial public event/text or accepted source progress is returned. |
| cost | O(catalog bytes) hashing plus funded canonical-buffer and 64-byte text ownership; happens at construction/binding, not each native event. |
| Design | [docs/ingestion.md §Native reader API and memory grant](../../../../ingestion.md), [docs/memory_accounts.md §Native streaming input ownership](../../../../memory_accounts.md) |

## B0050

[Lines 384–385](../../../../../src/io/ingest.cpp#L384); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L384-L385:sha256:e6598feae9bc0557681d378e8c0ef2fc043e60aeee7c785dd11f562a6c464244
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Closes the namespace input_detail at this source boundary; this is a lexical delimiter, not an operation. |
| inputs / outputs | No runtime input or output. Declarations following the span leave the preceding C++ scope. |
| invariants | The delimiter ends the preceding scope's visibility/linkage region; it adds no validation, publication, ownership transfer, or runtime authority. |
| ownership | The delimiter adds no owner. If it ends a function/block with live automatic objects, their normal destructors release those objects; namespace and type-definition closes change no existing object's lifetime. |
| failure | No explicit failure translation or catch is added. If a function/block exit destroys automatic objects, exception behavior follows those destructors; namespace/type closes have no runtime failure path. |
| cost | The delimiter adds no algorithmic work. A function/block exit can run existing automatic-object destructors and cleanup; namespace/type closes have no runtime cost. |
| Design | [src/io/ingest.cpp](../../../../../src/io/ingest.cpp), [docs/code_specs/files/src/io/ingest.cpp.md](ingest.cpp.md), [docs/ingestion.md](../../../../ingestion.md), [docs/session_lifecycle.md](../../../../session_lifecycle.md) |

## B0051

[Lines 386–388](../../../../../src/io/ingest.cpp#L386); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
template<class CatalogView> std::string input_catalog_sha256_impl(const CatalogView& catalog)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Compute the public DTO catalog SHA string from full canonical JSON. |
| inputs / outputs | Validates/serializes catalog, hashes it and returns owning hexadecimal string. |
| invariants | This explicit public helper may allocate ordinary catalog scratch/output; it is not a native update-path account or proof identity. |
| ownership | Caller owns returned hash; input catalog is borrowed. |
| failure | Validation, scalar, size, encoding or allocation errors propagate; local owned scratch is released by RAII. No partial public event/text or accepted source progress is returned. |
| cost | O(catalog/canonical bytes), full temporary canonical string plus digest allocation. |
| Design | [include/crown/io/ingest.hpp](../../../../../include/crown/io/ingest.hpp), [docs/ingestion.md](../../../../ingestion.md) |

## B0052

[Lines 389–389](../../../../../src/io/ingest.cpp#L389); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::string input_catalog_sha256(const Catalog& catalog)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Expose public catalog fingerprinting for Catalog. |
| inputs / outputs | Forwards the borrowed catalog to input_catalog_sha256_impl. |
| invariants | Both catalog representations produce the same full canonical wire binding. |
| ownership | Returned std::string owns the hash; no catalog pointer escapes. |
| failure | Validation, scalar, size, encoding or allocation errors propagate; local owned scratch is released by RAII. No partial public event/text or accepted source progress is returned. |
| cost | Fixed overload forwarding plus whole-catalog validation/serialization/hash. |
| Design | [include/crown/io/ingest.hpp](../../../../../include/crown/io/ingest.hpp), [docs/ingestion.md](../../../../ingestion.md) |

## B0053

[Lines 390–390](../../../../../src/io/ingest.cpp#L390); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::string input_catalog_sha256(const program::Catalog& catalog)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Expose public catalog fingerprinting for program::Catalog. |
| inputs / outputs | Forwards the borrowed catalog to input_catalog_sha256_impl. |
| invariants | Both catalog representations produce the same full canonical wire binding. |
| ownership | Returned std::string owns the hash; no catalog pointer escapes. |
| failure | Validation, scalar, size, encoding or allocation errors propagate; local owned scratch is released by RAII. No partial public event/text or accepted source progress is returned. |
| cost | Fixed overload forwarding plus whole-catalog validation/serialization/hash. |
| Design | [include/crown/io/ingest.hpp](../../../../../include/crown/io/ingest.hpp), [docs/ingestion.md](../../../../ingestion.md) |

## B0055

[Lines 392–394](../../../../../src/io/ingest.cpp#L392); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
template<class CatalogView> void validate_input_event_impl(const InputEvent& event,const CatalogView& catalog,InputLimits limits)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Apply typed full-event validation without wire serialization. |
| inputs / outputs | Forwards event/catalog and copied InputLimits to validate_event. |
| invariants | Positive sequence/domain checks do not establish stream continuity or source-offset order; source owner supplies those separately. |
| ownership | Borrows stable caller input/catalog synchronously; only local private parser/output state changes. No physical runtime, accepted source sequence or source position is published here. |
| failure | Validation, scalar, size, encoding or allocation errors propagate; local owned scratch is released by RAII. No partial public event/text or accepted source progress is returned. |
| cost | Full-row/field validation and scalar spelling costs; no encoded-record allocation. |
| Design | [include/crown/io/ingest.hpp](../../../../../include/crown/io/ingest.hpp), [docs/ingestion.md](../../../../ingestion.md) |

## B0056

[Lines 395–395](../../../../../src/io/ingest.cpp#L395); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void validate_input_event(const InputEvent& event,const Catalog& catalog,InputLimits limits)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Expose typed full-event validation for Catalog. |
| inputs / outputs | Delegates unchanged event/catalog/limits to validate_input_event_impl. |
| invariants | No wire/hash recomputation or source acknowledgement in this wrapper. |
| ownership | Borrows stable caller input/catalog synchronously; only local private parser/output state changes. No physical runtime, accepted source sequence or source position is published here. |
| failure | Validation, scalar, size, encoding or allocation errors propagate; local owned scratch is released by RAII. No partial public event/text or accepted source progress is returned. |
| cost | Fixed forwarding plus delegated complete row/domain/budget checks. |
| Design | [include/crown/io/ingest.hpp](../../../../../include/crown/io/ingest.hpp), [docs/ingestion.md](../../../../ingestion.md) |

## B0057

[Lines 396–396](../../../../../src/io/ingest.cpp#L396); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void validate_input_event(const InputEvent& event,const program::Catalog& catalog,InputLimits limits)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Expose typed full-event validation for program::Catalog. |
| inputs / outputs | Delegates unchanged event/catalog/limits to validate_input_event_impl. |
| invariants | No wire/hash recomputation or source acknowledgement in this wrapper. |
| ownership | Borrows stable caller input/catalog synchronously; only local private parser/output state changes. No physical runtime, accepted source sequence or source position is published here. |
| failure | Validation, scalar, size, encoding or allocation errors propagate; local owned scratch is released by RAII. No partial public event/text or accepted source progress is returned. |
| cost | Fixed forwarding plus delegated complete row/domain/budget checks. |
| Design | [include/crown/io/ingest.hpp](../../../../../include/crown/io/ingest.hpp), [docs/ingestion.md](../../../../ingestion.md) |

## B0059

[Lines 398–401](../../../../../src/io/ingest.cpp#L398); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
template<class CatalogView> InputEvent read_input_json_impl(std::string_view text,const CatalogView& catalog,InputLimits limits)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Prepare exact catalog binding then decode one public JSON DTO. |
| inputs / outputs | Admits raw record size before canonical catalog hashing and json_event. |
| invariants | Each explicit public call recomputes/validates its catalog; native EventReader caches its fingerprint separately. |
| ownership | Returns an owning event; neither text nor catalog storage is retained. |
| failure | Validation, scalar, size, encoding or allocation errors propagate; local owned scratch is released by RAII. No partial public event/text or accepted source progress is returned. |
| cost | Catalog-wide validation/hash plus JSON record/full-row parsing and owning allocations. |
| Design | [docs/ingestion.md §Version-1 JSONL event](../../../../ingestion.md), [schemas/physical-update-v1.schema.json](../../../../../schemas/physical-update-v1.schema.json) |

## B0060

[Lines 402–402](../../../../../src/io/ingest.cpp#L402); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
InputEvent read_input_json(std::string_view text,const Catalog& catalog,InputLimits limits)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Expose JSON DTO read for Catalog. |
| inputs / outputs | Forwards borrowed record bytes, catalog and copied limits to the shared read implementation. |
| invariants | Wire shape, full-row/domain/binding rules and error order are shared; this overload adds no native account, stream ordering or fallback. |
| ownership | Returns owning InputEvent independent of caller input/catalog lifetime. |
| failure | Validation, scalar, size, encoding or allocation errors propagate; local owned scratch is released by RAII. No partial public event/text or accepted source progress is returned. |
| cost | Fixed forwarding plus catalog hashing and complete JSON codec cost. |
| Design | [docs/ingestion.md §Version-1 JSONL event](../../../../ingestion.md), [schemas/physical-update-v1.schema.json](../../../../../schemas/physical-update-v1.schema.json) |

## B0061

[Lines 403–403](../../../../../src/io/ingest.cpp#L403); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
InputEvent read_input_json(std::string_view text,const program::Catalog& catalog,InputLimits limits)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Expose JSON DTO read for program::Catalog. |
| inputs / outputs | Forwards borrowed record bytes, catalog and copied limits to the shared read implementation. |
| invariants | Wire shape, full-row/domain/binding rules and error order are shared; this overload adds no native account, stream ordering or fallback. |
| ownership | Returns owning InputEvent independent of caller input/catalog lifetime. |
| failure | Validation, scalar, size, encoding or allocation errors propagate; local owned scratch is released by RAII. No partial public event/text or accepted source progress is returned. |
| cost | Fixed forwarding plus catalog hashing and complete JSON codec cost. |
| Design | [docs/ingestion.md §Version-1 JSONL event](../../../../ingestion.md), [schemas/physical-update-v1.schema.json](../../../../../schemas/physical-update-v1.schema.json) |

## B0063

[Lines 405–430](../../../../../src/io/ingest.cpp#L405); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
template<class CatalogView> std::string write_input_json_impl(const InputEvent& event,const CatalogView& catalog,InputLimits limits)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Encode a validated full physical DTO event as canonical version1 JSON. |
| inputs / outputs | Computes catalog hash, validates event, writes exact envelope/optional source and ordered scalars under record_bytes, without newline. |
| invariants | int64/bool types retain numeric/Boolean tokens; date/decimal are explicit tagged strings; source/table binding and full row are preserved. No implicit NULL, multiplicity or UPDATE representation. |
| ownership | Moves a complete ordinary string to caller; input event/catalog remain unchanged. |
| failure | Validation, scalar, size, encoding or allocation errors propagate; local owned scratch is released by RAII. No partial public event/text or accepted source progress is returned. |
| cost | Whole catalog validation/hash + complete event validation + emitted bytes; repeated scalar spelling and ordinary output growth are explicit. |
| Design | [docs/ingestion.md §Version-1 JSONL event](../../../../ingestion.md), [schemas/physical-update-v1.schema.json](../../../../../schemas/physical-update-v1.schema.json) |

## B0064

[Lines 431–431](../../../../../src/io/ingest.cpp#L431); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::string write_input_json(const InputEvent& event,const Catalog& catalog,InputLimits limits)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Expose JSON DTO write for Catalog. |
| inputs / outputs | Forwards borrowed full InputEvent, catalog and copied limits to the shared write implementation. |
| invariants | Wire shape, full-row/domain/binding rules and error order are shared; this overload adds no native account, stream ordering or fallback. |
| ownership | Returns owning std::string independent of caller input/catalog lifetime. |
| failure | Validation, scalar, size, encoding or allocation errors propagate; local owned scratch is released by RAII. No partial public event/text or accepted source progress is returned. |
| cost | Fixed forwarding plus catalog hashing and complete JSON codec cost. |
| Design | [docs/ingestion.md §Version-1 JSONL event](../../../../ingestion.md), [schemas/physical-update-v1.schema.json](../../../../../schemas/physical-update-v1.schema.json) |

## B0065

[Lines 432–432](../../../../../src/io/ingest.cpp#L432); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::string write_input_json(const InputEvent& event,const program::Catalog& catalog,InputLimits limits)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Expose JSON DTO write for program::Catalog. |
| inputs / outputs | Forwards borrowed full InputEvent, catalog and copied limits to the shared write implementation. |
| invariants | Wire shape, full-row/domain/binding rules and error order are shared; this overload adds no native account, stream ordering or fallback. |
| ownership | Returns owning std::string independent of caller input/catalog lifetime. |
| failure | Validation, scalar, size, encoding or allocation errors propagate; local owned scratch is released by RAII. No partial public event/text or accepted source progress is returned. |
| cost | Fixed forwarding plus catalog hashing and complete JSON codec cost. |
| Design | [docs/ingestion.md §Version-1 JSONL event](../../../../ingestion.md), [schemas/physical-update-v1.schema.json](../../../../../schemas/physical-update-v1.schema.json) |

## B0067

[Lines 434–437](../../../../../src/io/ingest.cpp#L434); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
template<class CatalogView> InputEvent read_input_binary_impl(std::string_view bytes,const CatalogView& catalog,InputLimits limits)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Prepare binding then decode one complete public binary DTO frame. |
| inputs / outputs | Admits byte size before catalog hashing and binary_event. |
| invariants | Exactly one independently framed record is required; concatenated streams belong to EventReader.frame. |
| ownership | Returned event owns all row/source bytes independent of the frame. |
| failure | Validation, scalar, size, encoding or allocation errors propagate; local owned scratch is released by RAII. No partial public event/text or accepted source progress is returned. |
| cost | Catalog validation/hash plus full frame/row parsing and ordinary DTO allocations. |
| Design | [docs/ingestion.md §Version-1 binary frame](../../../../ingestion.md) |

## B0068

[Lines 438–438](../../../../../src/io/ingest.cpp#L438); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
InputEvent read_input_binary(std::string_view bytes,const Catalog& catalog,InputLimits limits)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Expose binary DTO read for Catalog. |
| inputs / outputs | Forwards borrowed record bytes, catalog and copied limits to the shared read implementation. |
| invariants | Wire shape, full-row/domain/binding rules and error order are shared; this overload adds no native account, stream ordering or fallback. |
| ownership | Returns owning InputEvent independent of caller input/catalog lifetime. |
| failure | Validation, scalar, size, encoding or allocation errors propagate; local owned scratch is released by RAII. No partial public event/text or accepted source progress is returned. |
| cost | Fixed forwarding plus catalog hashing and complete binary codec cost. |
| Design | [docs/ingestion.md §Version-1 binary frame](../../../../ingestion.md) |

## B0069

[Lines 439–439](../../../../../src/io/ingest.cpp#L439); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
InputEvent read_input_binary(std::string_view bytes,const program::Catalog& catalog,InputLimits limits)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Expose binary DTO read for program::Catalog. |
| inputs / outputs | Forwards borrowed record bytes, catalog and copied limits to the shared read implementation. |
| invariants | Wire shape, full-row/domain/binding rules and error order are shared; this overload adds no native account, stream ordering or fallback. |
| ownership | Returns owning InputEvent independent of caller input/catalog lifetime. |
| failure | Validation, scalar, size, encoding or allocation errors propagate; local owned scratch is released by RAII. No partial public event/text or accepted source progress is returned. |
| cost | Fixed forwarding plus catalog hashing and complete binary codec cost. |
| Design | [docs/ingestion.md §Version-1 binary frame](../../../../ingestion.md) |

## B0071

[Lines 441–465](../../../../../src/io/ingest.cpp#L441); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
template<class CatalogView> std::string write_input_binary_impl(const InputEvent& event,const CatalogView& catalog,InputLimits limits)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Encode one canonical version1 binary full-event DTO frame. |
| inputs / outputs | Validates catalog/event, writes magic/version/placeholder length, exact binding/envelope/tagged row, then fills four length bytes. |
| invariants | Full record is capped; strings/arity/payload length fit uint32 before narrowing. Static Value alternative order defines tags; signed integers use exact bit_cast bits. No partial frame is published. |
| ownership | Private BinaryWriter owns output until moved to caller; input event remains borrowed. |
| failure | Validation, scalar, size, encoding or allocation errors propagate; local owned scratch is released by RAII. No partial public event/text or accepted source progress is returned. |
| cost | Catalog hash and complete event validation plus O(wire bytes), scalar spelling/owning string growth and fixed length backfill. |
| Design | [docs/ingestion.md §Version-1 binary frame](../../../../ingestion.md) |

## B0072

[Lines 466–466](../../../../../src/io/ingest.cpp#L466); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::string write_input_binary(const InputEvent& event,const Catalog& catalog,InputLimits limits)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Expose binary DTO write for Catalog. |
| inputs / outputs | Forwards borrowed full InputEvent, catalog and copied limits to the shared write implementation. |
| invariants | Wire shape, full-row/domain/binding rules and error order are shared; this overload adds no native account, stream ordering or fallback. |
| ownership | Returns owning std::string independent of caller input/catalog lifetime. |
| failure | Validation, scalar, size, encoding or allocation errors propagate; local owned scratch is released by RAII. No partial public event/text or accepted source progress is returned. |
| cost | Fixed forwarding plus catalog hashing and complete binary codec cost. |
| Design | [docs/ingestion.md §Version-1 binary frame](../../../../ingestion.md) |

## B0073

[Lines 467–467](../../../../../src/io/ingest.cpp#L467); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::string write_input_binary(const InputEvent& event,const program::Catalog& catalog,InputLimits limits)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Expose binary DTO write for program::Catalog. |
| inputs / outputs | Forwards borrowed full InputEvent, catalog and copied limits to the shared write implementation. |
| invariants | Wire shape, full-row/domain/binding rules and error order are shared; this overload adds no native account, stream ordering or fallback. |
| ownership | Returns owning std::string independent of caller input/catalog lifetime. |
| failure | Validation, scalar, size, encoding or allocation errors propagate; local owned scratch is released by RAII. No partial public event/text or accepted source progress is returned. |
| cost | Fixed forwarding plus catalog hashing and complete binary codec cost. |
| Design | [docs/ingestion.md §Version-1 binary frame](../../../../ingestion.md) |

## B0074

[Lines 468–470](../../../../../src/io/ingest.cpp#L468); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L468-L470:sha256:a1ed385b644da38539368255d668292553f77af97118aab006a02724405a9970
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Closes the namespace crown::io at this source boundary; this is a lexical delimiter, not an operation. |
| inputs / outputs | No runtime input or output. Declarations following the span leave the preceding C++ scope. |
| invariants | The delimiter ends the preceding scope's visibility/linkage region; it adds no validation, publication, ownership transfer, or runtime authority. |
| ownership | The delimiter adds no owner. If it ends a function/block with live automatic objects, their normal destructors release those objects; namespace and type-definition closes change no existing object's lifetime. |
| failure | No explicit failure translation or catch is added. If a function/block exit destroys automatic objects, exception behavior follows those destructors; namespace/type closes have no runtime failure path. |
| cost | The delimiter adds no algorithmic work. A function/block exit can run existing automatic-object destructors and cleanup; namespace/type closes have no runtime cost. |
| Design | [src/io/ingest.cpp](../../../../../src/io/ingest.cpp), [docs/code_specs/files/src/io/ingest.cpp.md](ingest.cpp.md), [docs/ingestion.md](../../../../ingestion.md), [docs/session_lifecycle.md](../../../../session_lifecycle.md) |
