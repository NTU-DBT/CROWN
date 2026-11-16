# `src/io/native_decode.cpp` — block usage map

[Source](../../../../../src/io/native_decode.cpp) · [Source index](../../../README.md) · [Subsystem contracts](../../../subsystem_contracts.md) · [Reviewed primitives](../../../primitives.md)

Parse exact scalar fields directly into compact native values.

Snapshot SHA-256: `29fea3302db04c7d97072ab4bf3054fe11ec532283b5a48f3238ad130e77f9e9`. 268 lines partitioned into 38 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [io](../../../subsystem_contracts.md#io). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/ingestion.md](../../../../ingestion.md), [docs/query_identity.md](../../../../query_identity.md), [docs/schema_evolution.md](../../../../schema_evolution.md), [docs/cli.md](../../../../cli.md), [docs/query_memory.md](../../../../query_memory.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–14](../../../../../src/io/native_decode.cpp#L1) | Imports dependencies; declares namespace scope. |  · [reviewed contract](#b0001) |
| [B0002 · 15–17](../../../../../src/io/native_decode.cpp#L15) | Callable definition: void require(bool ok,std::string_view code,std::string_view message) | calls Error, std::string; guard void require(bool ok,std::string_view code,std::string_view message) { · [reviewed contract](#b0002) |
| [B0003 · 18–20](../../../../../src/io/native_decode.cpp#L18) | Callable definition: void bounded(std::size_t size,std::size_t limit,std::string_view message) | calls require; guard void bounded(std::size_t size,std::size_t limit,std::string_view message) { · [reviewed contract](#b0003) |
| [B0004 · 21–24](../../../../../src/io/native_decode.cpp#L21) | Type/record definition: struct Cell |  · [reviewed contract](#b0004) |
| [B0005 · 25–26](../../../../../src/io/native_decode.cpp#L25) | Explanatory comments or spacing. | source comment (unverified): // Cell/text views stay backed until the compact row owns every payload. · [reviewed contract](#b0005) |
| [B0006 · 27–49](../../../../../src/io/native_decode.cpp#L27) | Type/record definition: struct Builder | returns std::move(decoded); growth copy_of, push_back, reserve; 1 loop sites; source comment (unverified): // Cell/text views stay backed until the compact row owns every payload. · [reviewed contract](#b0006) |
| [B0007 · 50–56](../../../../../src/io/native_decode.cpp#L50) | Callable definition: TableId native_table(const auto& catalog,std::string_view name) | calls size, Error, std::string; returns TableId{i}; 1 loop sites; source comment (unverified): // The reader validated a standalone catalog once, or retained an admitted · [reviewed contract](#b0007) |
| [B0008 · 57–60](../../../../../src/io/native_decode.cpp#L57) | Callable definition: void binding(std::uint64_t version,std::uint64_t source,std::string_view hash,TableId id,const auto& catalog,std::string_view exp… | calls require; guard require(version==catalog.version && source==catalog.tables\[id.value\].source_schema_version && hash=… · [reviewed contract](#b0008) |
| [B0009 · 61–64](../../../../../src/io/native_decode.cpp#L61) | declares types or opens a type body. | source comment (unverified): // The event schema bounds nesting to root/source/tagged scalar/values. · [reviewed contract](#b0009) |
| [B0010 · 65–65](../../../../../src/io/native_decode.cpp#L65) | Type/record definition: struct Integer |  · [reviewed contract](#b0010) |
| [B0011 · 66–74](../../../../../src/io/native_decode.cpp#L66) | declares values/defaults or compile-time conditions. |  · [reviewed contract](#b0011) |
| [B0012 · 75–75](../../../../../src/io/native_decode.cpp#L75) | Callable definition: \[\[noreturn\]\] static void invalid() | calls Error · [reviewed contract](#b0012) |
| [B0013 · 76–76](../../../../../src/io/native_decode.cpp#L76) | Callable definition: \[\[noreturn\]\] static void syntax() | calls Error · [reviewed contract](#b0013) |
| [B0014 · 77–77](../../../../../src/io/native_decode.cpp#L77) | Callable definition: void space() | calls size; 1 loop sites · [reviewed contract](#b0014) |
| [B0015 · 78–78](../../../../../src/io/native_decode.cpp#L78) | Callable definition: bool accept(char ch) | calls space, size; returns false; true · [reviewed contract](#b0015) |
| [B0016 · 79–79](../../../../../src/io/native_decode.cpp#L79) | Callable definition: void expect(char ch) | calls accept, syntax · [reviewed contract](#b0016) |
| [B0017 · 80–80](../../../../../src/io/native_decode.cpp#L80) | Callable definition: char take() | calls size, syntax; returns input_\[at_++\] · [reviewed contract](#b0017) |
| [B0018 · 81–86](../../../../../src/io/native_decode.cpp#L81) | Callable definition: static unsigned digit(char ch) | calls syntax; returns static_cast&lt;unsigned&gt;(ch-@ ); static_cast&lt;unsigned&gt;(ch-@ +10) · [reviewed contract](#b0018) |
| [B0019 · 87–87](../../../../../src/io/native_decode.cpp#L87) | Callable definition: std::uint32_t hex() | calls digit, take; returns result; 1 loop sites · [reviewed contract](#b0019) |
| [B0020 · 88–98](../../../../../src/io/native_decode.cpp#L88) | Callable definition: void utf8(std::uint32_t code) | calls push_back; growth push_back · [reviewed contract](#b0020) |
| [B0021 · 99–100](../../../../../src/io/native_decode.cpp#L99) | Explanatory comments or spacing. | source comment (unverified): // Borrowed result expires on the next string token; field acceptance is later, · [reviewed contract](#b0021) |
| [B0022 · 101–129](../../../../../src/io/native_decode.cpp#L101) | Callable definition: std::string_view string() | calls space, size, invalid, clear; returns token_.view(); growth push_back; 1 loop sites; source comment (unverified): // Borrowed result expires on the next string token; field acceptance is later, · [reviewed contract](#b0022) |
| [B0023 · 130–140](../../../../../src/io/native_decode.cpp#L130) | Callable definition: Integer integer() | calls space, size, invalid, std::from_chars; returns {magnitude,negative}; 1 loop sites · [reviewed contract](#b0023) |
| [B0024 · 141–143](../../../../../src/io/native_decode.cpp#L141) | Callable definition: std::uint64_t unsigned_integer() | calls integer, invalid; returns value.magnitude · [reviewed contract](#b0024) |
| [B0025 · 144–144](../../../../../src/io/native_decode.cpp#L144) | Explanatory comments or spacing. | source comment (unverified): // Callbacks classify/copy each borrowed key before parsing another string. · [reviewed contract](#b0025) |
| [B0026 · 145–149](../../../../../src/io/native_decode.cpp#L145) | Callable definition: template&lt;class Fn&gt; void members(Fn member) | calls accept, invalid, string, expect; 1 loop sites; source comment (unverified): // Callbacks classify/copy each borrowed key before parsing another string. · [reviewed contract](#b0026) |
| [B0027 · 150–162](../../../../../src/io/native_decode.cpp#L150) | Callable definition: void position() | calls members, require, unsigned_integer, string; guard require(field!=0 && !(seen&field),"invalid_document","unknown or duplicate source-position field");…; growth copy_of · [reviewed contract](#b0027) |
| [B0028 · 163–184](../../../../../src/io/native_decode.cpp#L163) | Callable definition: void scalar() | calls space, size, syntax, bounded; guard bounded(builder_.cells.size()+1,limits_.columns,"physical input column limit exceeded"); · [reviewed contract](#b0028) |
| [B0029 · 185–189](../../../../../src/io/native_decode.cpp#L185) | Callable definition: void values() | calls accept, invalid, scalar, expect; 1 loop sites · [reviewed contract](#b0029) |
| [B0030 · 190–192](../../../../../src/io/native_decode.cpp#L190) | Callable definition: public: JsonReader(const resource::MemoryAccount& account,std::string_view text,const InputLimits& limits) :account_(account),inp… | calls account_, input_, limits_, token_ · [reviewed contract](#b0030) |
| [B0031 · 193–218](../../../../../src/io/native_decode.cpp#L193) | Callable definition: Decoded decode(const auto& catalog,std::string_view fingerprint) | calls bounded, size, starts_with, members; guard bounded(input_.size(),limits_.record_bytes,"JSON input record exceeds its byte limit");; returns builder_.finish(catalog,limits_); growth copy_of, insert · [reviewed contract](#b0031) |
| [B0032 · 219–219](../../../../../src/io/native_decode.cpp#L219) | Closes surrounding scope/type. |  · [reviewed contract](#b0032) |
| [B0033 · 220–235](../../../../../src/io/native_decode.cpp#L220) | Type/record definition: struct BinaryReader | guard require(count&lt;=input.size()-position,"invalid_document","truncated binary input record");const auto…; returns result; result; 1 loop sites · [reviewed contract](#b0033) |
| [B0034 · 236–260](../../../../../src/io/native_decode.cpp#L236) | Callable definition: Decoded binary(const resource::MemoryAccount& account,std::string_view bytes,const auto& catalog,const InputLimits& limits,std::s… | calls bounded, size, require, take; guard bounded(bytes.size(),limits.record_bytes,"binary input record exceeds its byte limit");BinaryReader…; returns builder.finish(catalog,limits); growth insert, reserve; 1 loop sites · [reviewed contract](#b0034) |
| [B0035 · 261–261](../../../../../src/io/native_decode.cpp#L261) | Closes surrounding scope/type. | source comment (unverified): // namespace · [reviewed contract](#b0035) |
| [B0036 · 262–264](../../../../../src/io/native_decode.cpp#L262) | Callable definition: Decoded decode_json(const resource::MemoryAccount& account,std::string_view text,const CatalogSource& catalog,const InputLimits& … | calls catalog_source_detail::read, JsonReader, decode; returns catalog_source_detail::read(catalog,\[&\](const auto& schema){return JsonReader(account,text,limits).… · [reviewed contract](#b0036) |
| [B0037 · 265–267](../../../../../src/io/native_decode.cpp#L265) | Callable definition: Decoded decode_binary(const resource::MemoryAccount& account,std::string_view text,const CatalogSource& catalog,const InputLimits… | calls catalog_source_detail::read, binary; returns catalog_source_detail::read(catalog,\[&\](const auto& schema){return binary(account,text,schema,limit… · [reviewed contract](#b0037) |
| [B0038 · 268–268](../../../../../src/io/native_decode.cpp#L268) | Closes surrounding scope/type. | source comment (unverified): // namespace crown::io::input_detail · [reviewed contract](#b0038) |

## B0001

[Lines 1–14](../../../../../src/io/native_decode.cpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L1-L14:sha256:4a89d2c5098ee231e131b7877a7cc4575d0c2136c1b048a7055e27d315e04f86
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Imports compile-time dependencies (native_input.hpp, input_native.hpp, catalog_source.hpp, ingest_text.hpp, crown/api/error.hpp, crown/catalog/catalog.hpp) and opens crown::io::input_detail scope for the declarations or definitions that follow. |
| inputs / outputs | No runtime inputs/outputs are declared by the import/scope lines themselves. |
| invariants | The listed headers and namespace membership determine compile-time name availability; any API behavior belongs to the declarations/definitions that follow. |
| ownership | No object ownership is created by the imports or namespace tokens. |
| failure | No runtime failure path. Missing/incompatible dependencies or a violated compile-time constraint fail translation/linking. |
| cost | Compile/preprocessor work only; no new per-operation runtime overhead. |
| Design | [src/io/native_decode.cpp](../../../../../src/io/native_decode.cpp), [docs/code_specs/files/src/io/native_decode.cpp.md](native_decode.cpp.md), [docs/ingestion.md](../../../../ingestion.md), [docs/session_lifecycle.md](../../../../session_lifecycle.md) |

## B0002

[Lines 15–17](../../../../../src/io/native_decode.cpp#L15); `callable`; `contains_scoped_manual_contract`.

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

[Lines 18–20](../../../../../src/io/native_decode.cpp#L18); `callable`; `contains_scoped_manual_contract`.

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

[Lines 21–24](../../../../../src/io/native_decode.cpp#L21); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct Cell
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Keep one parsed native cell and any owning text backing its borrowed view. |
| inputs / outputs | Cell holds AccountedText plus inline ScalarView, initialized to integer zero before assignment. |
| invariants | String-view bytes are retained by the accompanying AccountedText heap block; vector moves transfer ownership without moving character addresses. Nonstring alternatives are inline. |
| ownership | Cell owns text under decoder account; ScalarView borrows it only while Cell/Builder retains the block. |
| failure | Text creation/vector insertion may fail before cell retention; RAII releases uncommitted backing. |
| cost | Fixed descriptor plus optional funded text request; no owning ordinary Value/Decimal. |
| Design | [docs/ingestion.md §Native reader API and memory grant](../../../../ingestion.md), [docs/memory_accounts.md §Native streaming input ownership](../../../../memory_accounts.md) |

## B0005

[Lines 25–26](../../../../../src/io/native_decode.cpp#L25); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L25-L26:sha256:20fea2709e02552bd69fab74741428a243c5e51385cba06ce6debe0d4c63b270
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Design note for adjacent code: Cell/text views stay backed until the compact row owns every payload. Full row/domain validation follows this freeze and can still reject it. This is caller guidance recorded as prose, not an executable result. |
| inputs / outputs | No runtime interface is implemented by these comment-only lines. They sit at src/io/native_decode.cpp lines 23-28; the surrounding declaration/body defines its own inputs and outputs. |
| invariants | The words record the intended use boundary only. They do not add a guard, proof, capability, transaction, durability guarantee, or account charge; verify behavior in the referenced implementation. |
| ownership | Comment text owns no data. Object lifetimes, borrows, and account attribution remain those of the adjacent source objects and their constructors. |
| failure | No failure path is implemented here. Any mentioned failure or recovery rule belongs to the adjacent operation and its existing error carrier. |
| cost | No runtime work is performed by these lines; any cost/bound in the note is not certified by this comment-only card. |
| Design | [src/io/native_decode.cpp](../../../../../src/io/native_decode.cpp), [docs/code_specs/files/src/io/native_decode.cpp.md](native_decode.cpp.md), [docs/ingestion.md](../../../../ingestion.md), [docs/session_lifecycle.md](../../../../session_lifecycle.md) |

## B0006

[Lines 27–49](../../../../../src/io/native_decode.cpp#L27); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct Builder
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Assemble one native event and freeze it into a compact owning row. |
| inputs / outputs | Builder owns funded Cell vector/Decoded; value adds inline cell, text first copies backing, source owns source bytes, finish gathers views and copies one AccountedRow then validates full event. |
| invariants | Freeze occurs before full row/domain/source validation in finish, so invalid rows can consume temporary account memory first. Returned views are rebased to decoded.row/source, not transient cells/input tokens. |
| ownership | Borrows account reference synchronously; cells own temporary string bytes and returned Decoded owns final compact row/source independently. |
| failure | Any allocation/domain/field/source error unwinds private Builder/Decoded and publishes no event; no cleanup catch or ordinary row mirror. |
| cost | O(row width + text bytes) with cell/vector/backing/view scratch plus compact-row/source requests overlapping under one account; exact validation adds row/payload scans. |
| Design | [docs/ingestion.md §Native reader API and memory grant](../../../../ingestion.md), [docs/memory_accounts.md §Native streaming input ownership](../../../../memory_accounts.md), [src/io/input_view.cpp](../../../../../src/io/input_view.cpp) |

## B0007

[Lines 50–56](../../../../../src/io/native_decode.cpp#L50); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
TableId native_table(const auto& catalog,std::string_view name)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Resolve an exact physical table name in an already admitted reader catalog. |
| inputs / outputs | Linear comparison across retained catalog tables returns dense TableId or unknown_table. |
| invariants | Avoids public find_table full catalog revalidation; constructor already validated a standalone catalog or retained admitted immutable program. No alias/case-fold mapping. |
| ownership | Borrows stable caller input/catalog synchronously; only local private parser/output state changes. No physical runtime, accepted source sequence or source position is published here. |
| failure | Unknown table constructs public diagnostic text and throws; other private metadata remains unpublished. |
| cost | O(table count and compared name bytes), no successful lookup-map/string allocation. |
| Design | [docs/ingestion.md §Native reader API and memory grant](../../../../ingestion.md), [docs/memory_accounts.md §Native streaming input ownership](../../../../memory_accounts.md) |

## B0008

[Lines 57–60](../../../../../src/io/native_decode.cpp#L57); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void binding(std::uint64_t version,std::uint64_t source,std::string_view hash,TableId id,const auto& catalog,std::string_view expected)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Require native record exact catalog/source hash binding. |
| inputs / outputs | Checks catalog version, resolved source version and wire hash against expected retained fingerprint. |
| invariants | Resolved table ID must be valid from native_table; exact bytes imply canonical expected hash, without a separate authentication protocol. |
| ownership | Borrows stable caller input/catalog synchronously; only local private parser/output state changes. No physical runtime, accepted source sequence or source position is published here. |
| failure | Validation, scalar, size, encoding or allocation errors propagate; local owned scratch is released by RAII. No partial public event/text or accepted source progress is returned. |
| cost | Fixed version comparisons plus up to 64 hash bytes. |
| Design | [docs/ingestion.md §Version-1 JSONL event](../../../../ingestion.md), [schemas/physical-update-v1.schema.json](../../../../../schemas/physical-update-v1.schema.json), [docs/ingestion.md §Version-1 binary frame](../../../../ingestion.md) |

## B0009

[Lines 61–64](../../../../../src/io/native_decode.cpp#L61); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
class JsonReader {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Parse only the fixed physical-event JSON schema using funded scratch. |
| inputs / outputs | Borrows one capped record/account/limits, owns reusable token Buffer and Builder plus binding fields. |
| invariants | Schema nesting is root/source/tagged scalar/values; no generic DOM or arbitrary recursive nesting stack. Successful native payload/token storage uses supplied account; public error diagnostics may allocate ordinary strings. |
| ownership | Parser is local; returned Decoded must own final row/source before input/token/Builder release. |
| failure | Fixed schema/syntax diagnostics or resource/allocation faults propagate to sticky EventReader.peek; no partial event publication. |
| cost | O(record bytes/tokens + row/catalog-name validation), bounded schema depth and account-funded capacity; token can reach record_bytes before narrower field acceptance. |
| Design | [docs/ingestion.md §Version-1 JSONL event](../../../../ingestion.md), [schemas/physical-update-v1.schema.json](../../../../../schemas/physical-update-v1.schema.json), [docs/ingestion.md §Native reader API and memory grant](../../../../ingestion.md), [docs/memory_accounts.md §Native streaming input ownership](../../../../memory_accounts.md) |

## B0010

[Lines 65–65](../../../../../src/io/native_decode.cpp#L65); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct Integer
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Represent one parsed JSON integer before deciding envelope versus signed scalar domain. |
| inputs / outputs | Stores uint64 magnitude and a separate negative flag. |
| invariants | Allows INT64_MIN magnitude and numerical negative zero without signed overflow; does not represent floats/exponents. |
| ownership | Copied inline parser result, no ownership. |
| failure | Parsing/consumer checks decide range; declaration itself does not throw. |
| cost | Fixed inline two-field value. |
| Design | [docs/ingestion.md §Version-1 JSONL event](../../../../ingestion.md), [schemas/physical-update-v1.schema.json](../../../../../schemas/physical-update-v1.schema.json) |

## B0011

[Lines 66–74](../../../../../src/io/native_decode.cpp#L66); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
  const resource::MemoryAccount& account_;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Retain bounded native JSON parse state and owning binding scratch. |
| inputs / outputs | Stores borrowed account/input/limits, byte offset, funded reusable token/Builder/hash/table and exact versions/seen mask. |
| invariants | Input/account/limits must survive decode; token views expire at next token parse. Keys are converted to finite field selectors before callbacks reuse token storage. |
| ownership | Local parser owns funded buffers/text and Builder; all borrowed references are synchronous. |
| failure | RAII frees funded partial state after error; no accepted reader progress is changed by this parser. |
| cost | Fixed metadata plus funded token/cell/binding capacities; no ambient allocator context or ordinary retained JSON values. |
| Design | [docs/ingestion.md §Version-1 JSONL event](../../../../ingestion.md), [schemas/physical-update-v1.schema.json](../../../../../schemas/physical-update-v1.schema.json), [docs/ingestion.md §Native reader API and memory grant](../../../../ingestion.md), [docs/memory_accounts.md §Native streaming input ownership](../../../../memory_accounts.md) |

## B0012

[Lines 75–75](../../../../../src/io/native_decode.cpp#L75); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
[[noreturn]] static void invalid()
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Reject a native schema-token violation. |
| inputs / outputs | Always throws invalid_document with fixed physical event schema text. |
| invariants | Stable native wording does not expose third-party parser internals; no permissive fallback/coercion. |
| ownership | Borrows stable caller input/catalog synchronously; only local private parser/output state changes. No physical runtime, accepted source sequence or source position is published here. |
| failure | Always throws invalid_document; diagnostic construction may itself fail allocation. |
| cost | Failure-only diagnostic construction/throw. |
| Design | [docs/ingestion.md §Version-1 JSONL event](../../../../ingestion.md), [schemas/physical-update-v1.schema.json](../../../../../schemas/physical-update-v1.schema.json) |

## B0013

[Lines 76–76](../../../../../src/io/native_decode.cpp#L76); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
[[noreturn]] static void syntax()
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Reject a native JSON syntax violation. |
| inputs / outputs | Always throws invalid_document with fixed invalid physical event JSON text. |
| invariants | Stable native wording does not expose third-party parser internals; no permissive fallback/coercion. |
| ownership | Borrows stable caller input/catalog synchronously; only local private parser/output state changes. No physical runtime, accepted source sequence or source position is published here. |
| failure | Always throws invalid_document; diagnostic construction may itself fail allocation. |
| cost | Failure-only diagnostic construction/throw. |
| Design | [docs/ingestion.md §Version-1 JSONL event](../../../../ingestion.md), [schemas/physical-update-v1.schema.json](../../../../../schemas/physical-update-v1.schema.json) |

## B0014

[Lines 77–77](../../../../../src/io/native_decode.cpp#L77); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void space()
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Skip only JSON-defined ASCII whitespace. |
| inputs / outputs | Advances at_ across space/tab/CR/LF while within input. |
| invariants | Does not normalize bytes inside strings or accept arbitrary locale whitespace; at_ never exceeds input size. |
| ownership | Borrows stable caller input/catalog synchronously; only local private parser/output state changes. No physical runtime, accepted source sequence or source position is published here. |
| failure | No explicit failure path; later token reader diagnoses missing required content. |
| cost | O(skipped whitespace), inline scanning, no allocation. |
| Design | [docs/ingestion.md §Version-1 JSONL event](../../../../ingestion.md), [schemas/physical-update-v1.schema.json](../../../../../schemas/physical-update-v1.schema.json) |

## B0015

[Lines 78–78](../../../../../src/io/native_decode.cpp#L78); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
bool accept(char ch)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Optionally consume one expected JSON delimiter. |
| inputs / outputs | Skips whitespace; matching byte advances and returns true, absent/different returns false. |
| invariants | No advance beyond end; caller decides whether a mismatch is optional or a syntax failure. |
| ownership | Borrows stable caller input/catalog synchronously; only local private parser/output state changes. No physical runtime, accepted source sequence or source position is published here. |
| failure | No explicit exception; preserves private cursor on nonmatching non-whitespace byte. |
| cost | O(skipped whitespace) plus fixed byte check. |
| Design | [docs/ingestion.md §Version-1 JSONL event](../../../../ingestion.md), [schemas/physical-update-v1.schema.json](../../../../../schemas/physical-update-v1.schema.json) |

## B0016

[Lines 79–79](../../../../../src/io/native_decode.cpp#L79); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void expect(char ch)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Require one exact JSON delimiter. |
| inputs / outputs | Calls accept and throws fixed syntax failure on false. |
| invariants | Mismatched closing/separating characters cannot silently terminate a record. |
| ownership | Borrows stable caller input/catalog synchronously; only local private parser/output state changes. No physical runtime, accepted source sequence or source position is published here. |
| failure | Validation, scalar, size, encoding or allocation errors propagate; local owned scratch is released by RAII. No partial public event/text or accepted source progress is returned. |
| cost | Whitespace scan plus fixed delimiter check. |
| Design | [docs/ingestion.md §Version-1 JSONL event](../../../../ingestion.md), [schemas/physical-update-v1.schema.json](../../../../../schemas/physical-update-v1.schema.json) |

## B0017

[Lines 80–80](../../../../../src/io/native_decode.cpp#L80); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
char take()
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Consume one raw JSON byte with end-of-record protection. |
| inputs / outputs | Returns input_\[at_++\] after checking at_ != size. |
| invariants | Does not skip whitespace; escape/string readers use it for exact byte grammar. |
| ownership | Borrows stable caller input/catalog synchronously; only local private parser/output state changes. No physical runtime, accepted source sequence or source position is published here. |
| failure | Truncated token throws invalid_document syntax diagnostic. |
| cost | Fixed check/index/increment, no successful allocation. |
| Design | [docs/ingestion.md §Version-1 JSONL event](../../../../ingestion.md), [schemas/physical-update-v1.schema.json](../../../../../schemas/physical-update-v1.schema.json) |

## B0018

[Lines 81–86](../../../../../src/io/native_decode.cpp#L81); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
static unsigned digit(char ch)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Decode one hexadecimal escape digit. |
| inputs / outputs | ASCII 0..9/a..f/A..F returns 0..15. |
| invariants | Rejects every other byte; no locale/floating/string conversion. |
| ownership | Borrows stable caller input/catalog synchronously; only local private parser/output state changes. No physical runtime, accepted source sequence or source position is published here. |
| failure | Invalid digit calls syntax(); no output code point is returned. |
| cost | Fixed comparisons/arithmetic. |
| Design | [docs/ingestion.md §Version-1 JSONL event](../../../../ingestion.md), [schemas/physical-update-v1.schema.json](../../../../../schemas/physical-update-v1.schema.json) |

## B0019

[Lines 87–87](../../../../../src/io/native_decode.cpp#L87); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::uint32_t hex()
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Decode exactly four hexadecimal escape digits. |
| inputs / outputs | Combines four take()/digit() results into uint32 code unit. |
| invariants | Each step consumes one checked byte; result is at most 0xFFFF and surrogate admission belongs to string(). |
| ownership | Borrows stable caller input/catalog synchronously; only local private parser/output state changes. No physical runtime, accepted source sequence or source position is published here. |
| failure | Validation, scalar, size, encoding or allocation errors propagate; local owned scratch is released by RAII. No partial public event/text or accepted source progress is returned. |
| cost | Exactly four iterations, no successful allocation. |
| Design | [docs/ingestion.md §Version-1 JSONL event](../../../../ingestion.md), [schemas/physical-update-v1.schema.json](../../../../../schemas/physical-update-v1.schema.json) |

## B0020

[Lines 88–98](../../../../../src/io/native_decode.cpp#L88); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void utf8(std::uint32_t code)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Append one admitted Unicode scalar as UTF-8 to funded token storage. |
| inputs / outputs | Writes 1..4 bytes according to code value. |
| invariants | Private string caller excludes lone surrogates and combines valid pairs to &lt;=U+10FFFF before this call; function is not an unchecked public Unicode validator. |
| ownership | Mutates only reusable token Buffer under original decoder account. |
| failure | Validation, scalar, size, encoding or allocation errors propagate; local owned scratch is released by RAII. No partial public event/text or accepted source progress is returned. |
| cost | At most four funded Buffer pushes/capacity growth. |
| Design | [docs/ingestion.md §Version-1 JSONL event](../../../../ingestion.md), [schemas/physical-update-v1.schema.json](../../../../../schemas/physical-update-v1.schema.json), [docs/ingestion.md §Native reader API and memory grant](../../../../ingestion.md), [docs/memory_accounts.md §Native streaming input ownership](../../../../memory_accounts.md) |

## B0021

[Lines 99–100](../../../../../src/io/native_decode.cpp#L99); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L99-L100:sha256:a401e14937e20a993bc19c59e371c71bbd82b732129a7d0c17ebf4b462a49d62
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Design note for adjacent code: Borrowed result expires on the next string token; field acceptance is later, so token scratch can approach record_bytes before field_bytes rejects it. This is caller guidance recorded as prose, not an executable result. |
| inputs / outputs | No runtime interface is implemented by these comment-only lines. They sit at src/io/native_decode.cpp lines 97-102; the surrounding declaration/body defines its own inputs and outputs. |
| invariants | The words record the intended use boundary only. They do not add a guard, proof, capability, transaction, durability guarantee, or account charge; verify behavior in the referenced implementation. |
| ownership | Comment text owns no data. Object lifetimes, borrows, and account attribution remain those of the adjacent source objects and their constructors. |
| failure | No failure path is implemented here. Any mentioned failure or recovery rule belongs to the adjacent operation and its existing error carrier. |
| cost | No runtime work is performed by these lines; any cost/bound in the note is not certified by this comment-only card. |
| Design | [src/io/native_decode.cpp](../../../../../src/io/native_decode.cpp), [docs/code_specs/files/src/io/native_decode.cpp.md](native_decode.cpp.md), [docs/ingestion.md](../../../../ingestion.md), [docs/session_lifecycle.md](../../../../session_lifecycle.md) |

## B0022

[Lines 101–129](../../../../../src/io/native_decode.cpp#L101); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::string_view string()
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Decode one JSON string into reusable account-backed token storage. |
| inputs / outputs | Consumes quotes, escapes and valid surrogate pairs, rejects raw controls/bad escapes, validates final UTF-8 and returns borrowed token view. |
| invariants | Raw NUL/control must be escaped; Unicode scalar bytes preserve exact content. Result becomes invalid when next string clears/reuses token. field_bytes acceptance is caller-side after lexing, so scratch may approach record_bytes. |
| ownership | Returned string_view borrows JsonReader.token_; callers copy needed text or finish key classification before parsing another token. |
| failure | Syntax/UTF-8/account/allocation failure leaves private cursor/token partial; enclosing peek becomes sticky after raw stream consumption. |
| cost | O(encoded+decoded token bytes), funded geometric buffer capacity and final UTF-8 scan; no owning ordinary string. |
| Design | [docs/ingestion.md §Version-1 JSONL event](../../../../ingestion.md), [schemas/physical-update-v1.schema.json](../../../../../schemas/physical-update-v1.schema.json), [docs/ingestion.md §Native reader API and memory grant](../../../../ingestion.md), [docs/memory_accounts.md §Native streaming input ownership](../../../../memory_accounts.md) |

## B0023

[Lines 130–140](../../../../../src/io/native_decode.cpp#L130); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Integer integer()
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Parse strict JSON integer syntax into magnitude and sign. |
| inputs / outputs | Consumes optional minus and at least one digit, with JSON leading-zero behavior; from_chars checks uint64 and signed-negative magnitude bounds. |
| invariants | No plus/floating/exponent spelling. Subsequent delimiters reject extra leading-zero digits. EOF/nondigit rejection precedes digit consumption; the zero branch advances once and the nonzero loop consumes at least one digit. No later operation rewinds at_. The unreachable final empty-span guard and its otherwise unused begin capture are removed. |
| ownership | Borrows stable caller input/catalog synchronously; only local private parser/output state changes. No physical runtime, accepted source sequence or source position is published here. |
| failure | Bad grammar/range still rejects with invalid_document at the existing checks. Removing the dominated final guard changes no admitted token or diagnostic category. |
| cost | O(digit bytes), fixed inline state and from_chars; no successful owning text allocation. |
| Design | [docs/ingestion.md §Version-1 JSONL event](../../../../ingestion.md), [schemas/physical-update-v1.schema.json](../../../../../schemas/physical-update-v1.schema.json) |

## B0024

[Lines 141–143](../../../../../src/io/native_decode.cpp#L141); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::uint64_t unsigned_integer()
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Read an unsigned envelope integer with compatible negative-zero handling. |
| inputs / outputs | Delegates integer(); a genuinely negative nonzero value rejects, zero returns uint64 zero. |
| invariants | No unchecked narrowing or signed overflow; sequence positivity is validated later, source offset zero remains valid. |
| ownership | Borrows stable caller input/catalog synchronously; only local private parser/output state changes. No physical runtime, accepted source sequence or source position is published here. |
| failure | Validation, scalar, size, encoding or allocation errors propagate; local owned scratch is released by RAII. No partial public event/text or accepted source progress is returned. |
| cost | Integer token parse plus fixed sign/magnitude branch. |
| Design | [docs/ingestion.md §Version-1 JSONL event](../../../../ingestion.md), [schemas/physical-update-v1.schema.json](../../../../../schemas/physical-update-v1.schema.json) |

## B0025

[Lines 144–144](../../../../../src/io/native_decode.cpp#L144); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L144-L144:sha256:34fe185383e5ae828ea744bf8517d70ae1dcafd197d2a8e060609e0359930bcc
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Design note for adjacent code: Callbacks classify/copy each borrowed key before parsing another string. This is caller guidance recorded as prose, not an executable result. |
| inputs / outputs | No runtime interface is implemented by these comment-only lines. They sit at src/io/native_decode.cpp lines 142-146; the surrounding declaration/body defines its own inputs and outputs. |
| invariants | The words record the intended use boundary only. They do not add a guard, proof, capability, transaction, durability guarantee, or account charge; verify behavior in the referenced implementation. |
| ownership | Comment text owns no data. Object lifetimes, borrows, and account attribution remain those of the adjacent source objects and their constructors. |
| failure | No failure path is implemented here. Any mentioned failure or recovery rule belongs to the adjacent operation and its existing error carrier. |
| cost | No runtime work is performed by these lines; any cost/bound in the note is not certified by this comment-only card. |
| Design | [src/io/native_decode.cpp](../../../../../src/io/native_decode.cpp), [docs/code_specs/files/src/io/native_decode.cpp.md](native_decode.cpp.md), [docs/ingestion.md](../../../../ingestion.md), [docs/session_lifecycle.md](../../../../session_lifecycle.md) |

## B0026

[Lines 145–149](../../../../../src/io/native_decode.cpp#L145); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
template<class Fn> void members(Fn member)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Iterate exactly one bounded-schema JSON object without a DOM. |
| inputs / outputs | Requires {, reads string key/colon, invokes member callback, then } or comma. |
| invariants | Callback must classify/copy borrowed key before calling string again. Unknown/duplicate keys and legal nested shapes are caller-specific; generic object loop does not skip unrecognized values. |
| ownership | Borrowed key view is valid only until token reuse; synchronous callback owns any needed retained text. |
| failure | Bad punctuation/token/callback faults propagate with local partial state only. |
| cost | O(object token bytes/member count) plus callback work; stack depth bounded by fixed schema callers. |
| Design | [docs/ingestion.md §Version-1 JSONL event](../../../../ingestion.md), [schemas/physical-update-v1.schema.json](../../../../../schemas/physical-update-v1.schema.json), [docs/ingestion.md §Native reader API and memory grant](../../../../ingestion.md), [docs/memory_accounts.md §Native streaming input ownership](../../../../memory_accounts.md) |

## B0027

[Lines 150–162](../../../../../src/io/native_decode.cpp#L150); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void position()
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Decode an optional exact source-position object into owned native source bytes. |
| inputs / outputs | Requires source and offset once each; source name fits cap, is nonempty/no NUL and already UTF-8 decoded. |
| invariants | Offset remains uint64, including zero. Source string is copied before key/token reuse and event view is rebased after move. |
| ownership | Borrows stable caller input/catalog synchronously; only local private parser/output state changes. No physical runtime, accepted source sequence or source position is published here. |
| failure | Validation, scalar, size, encoding or allocation errors propagate; local owned scratch is released by RAII. No partial public event/text or accepted source progress is returned. |
| cost | O(source/key bytes), funded source backing and fixed seen mask; source monotonicity is Data.order responsibility. |
| Design | [docs/ingestion.md §Version-1 JSONL event](../../../../ingestion.md), [schemas/physical-update-v1.schema.json](../../../../../schemas/physical-update-v1.schema.json), [docs/ingestion.md §Native reader API and memory grant](../../../../ingestion.md), [docs/memory_accounts.md §Native streaming input ownership](../../../../memory_accounts.md) |

## B0028

[Lines 163–184](../../../../../src/io/native_decode.cpp#L163); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void scalar()
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Decode one non-null JSON row scalar under column/field limits. |
| inputs / outputs | String owns funded backing; tagged date/inline decimal requires one field; true/false are inline; strict integer fits signed int64. |
| invariants | Checks next column before retaining value. NULL/arrays/floats never produce scalars. Exact row type/arity/decimal catalog domain are validated in Builder.finish after freeze. |
| ownership | Borrows stable caller input/catalog synchronously; only local private parser/output state changes. No physical runtime, accepted source sequence or source position is published here. |
| failure | Validation, scalar, size, encoding or allocation errors propagate; local owned scratch is released by RAII. No partial public event/text or accepted source progress is returned. |
| cost | O(token/scalar bytes), funded string backing/vector capacity for text, inline native numeric/date/decimal values. |
| Design | [docs/ingestion.md §Version-1 JSONL event](../../../../ingestion.md), [schemas/physical-update-v1.schema.json](../../../../../schemas/physical-update-v1.schema.json), [docs/ingestion.md §Native reader API and memory grant](../../../../ingestion.md), [docs/memory_accounts.md §Native streaming input ownership](../../../../memory_accounts.md) |

## B0029

[Lines 185–189](../../../../../src/io/native_decode.cpp#L185); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void values()
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Decode the ordered full values array. |
| inputs / outputs | Requires \[, processes scalar() entries separated by commas, accepts empty array for later arity check. |
| invariants | Column limit is enforced per scalar; nested arrays and malformed separators reject, no projection/deduplication. |
| ownership | Borrows stable caller input/catalog synchronously; only local private parser/output state changes. No physical runtime, accepted source sequence or source position is published here. |
| failure | Validation, scalar, size, encoding or allocation errors propagate; local owned scratch is released by RAII. No partial public event/text or accepted source progress is returned. |
| cost | O(array width + scalar parsing/owned scratch costs). |
| Design | [docs/ingestion.md §Version-1 JSONL event](../../../../ingestion.md), [schemas/physical-update-v1.schema.json](../../../../../schemas/physical-update-v1.schema.json), [docs/ingestion.md §Native reader API and memory grant](../../../../ingestion.md), [docs/memory_accounts.md §Native streaming input ownership](../../../../memory_accounts.md) |

## B0030

[Lines 190–192](../../../../../src/io/native_decode.cpp#L190); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
 public:
  JsonReader(const resource::MemoryAccount& account,std::string_view text,const InputLimits& limits)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Initialize the local native JSON parser with borrowed immutable context. |
| inputs / outputs | Retains account/input/limits references and creates funded empty token/Builder scratch. |
| invariants | Public wrappers/reader keep all borrowed context alive through decode; constructor does not return a borrowed event or read a stream. |
| ownership | Borrows stable caller input/catalog synchronously; only local private parser/output state changes. No physical runtime, accepted source sequence or source position is published here. |
| failure | No explicit schema admission here; account-backed object initializations follow their normal failure contracts. |
| cost | Fixed reference/default initialization; later capacity growth consumes supplied account. |
| Design | [docs/ingestion.md §Version-1 JSONL event](../../../../ingestion.md), [schemas/physical-update-v1.schema.json](../../../../../schemas/physical-update-v1.schema.json), [docs/ingestion.md §Native reader API and memory grant](../../../../ingestion.md), [docs/memory_accounts.md §Native streaming input ownership](../../../../memory_accounts.md) |

## B0031

[Lines 193–218](../../../../../src/io/native_decode.cpp#L193); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Decoded decode(const auto& catalog,std::string_view fingerprint)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Decode exactly one fixed-schema native JSON record against retained binding. |
| inputs / outputs | Checks record cap/BOM, nine exact root fields and duplicates, version1, resolved table/full hash binding, trailing whitespace/end, then freezes/validates complete event. |
| invariants | Root callbacks derive finite field ID before token reuse. source_position is the only optional root field. Operation exactly insert/delete; hash length64 then exact expected match. Default switch terminate is unreachable after bounded name lookup. |
| ownership | Returned Decoded owns compact row/source and rebased views, independent of caller record/token/Builder lifetime. |
| failure | Schema/version/binding/domain/resource/allocation errors return no partial event. Consuming reader owns sticky failure; this local parser adds no catch. |
| cost | O(record/token/scalar bytes + table-name scan + complete-row freeze/validation); funded scratch/binding text and final row overlap under supplied account. |
| Design | [docs/ingestion.md §Version-1 JSONL event](../../../../ingestion.md), [schemas/physical-update-v1.schema.json](../../../../../schemas/physical-update-v1.schema.json), [docs/ingestion.md §Native reader API and memory grant](../../../../ingestion.md), [docs/memory_accounts.md §Native streaming input ownership](../../../../memory_accounts.md) |

## B0032

[Lines 219–219](../../../../../src/io/native_decode.cpp#L219); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L219-L219:sha256:aa1d1a63390229c798347e83a0405441c9400035284ad168c1bf6cdf1d70a370
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Closes the enclosing helper type at this source boundary; this is a lexical delimiter, not an operation. |
| inputs / outputs | No runtime input or output. Declarations following the span leave the preceding C++ scope. |
| invariants | The delimiter ends the preceding scope's visibility/linkage region; it adds no validation, publication, ownership transfer, or runtime authority. |
| ownership | The delimiter adds no owner. If it ends a function/block with live automatic objects, their normal destructors release those objects; namespace and type-definition closes change no existing object's lifetime. |
| failure | No explicit failure translation or catch is added. If a function/block exit destroys automatic objects, exception behavior follows those destructors; namespace/type closes have no runtime failure path. |
| cost | The delimiter adds no algorithmic work. A function/block exit can run existing automatic-object destructors and cleanup; namespace/type closes have no runtime cost. |
| Design | [src/io/native_decode.cpp](../../../../../src/io/native_decode.cpp), [docs/code_specs/files/src/io/native_decode.cpp.md](native_decode.cpp.md), [docs/ingestion.md](../../../../ingestion.md), [docs/session_lifecycle.md](../../../../session_lifecycle.md) |

## B0033

[Lines 220–235](../../../../../src/io/native_decode.cpp#L220); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct BinaryReader
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Borrow checked little-endian binary fields for native decoding. |
| inputs / outputs | take advances bounded view position; integer decodes private fixed widths&lt;=8; string reads/caps uint32 length, validates UTF-8 and returns borrowed bytes. |
| invariants | position&lt;=input.size(); no implicit owning string or host ABI decoding. Borrowed bytes must be frozen by Builder before frame release. |
| ownership | All returned string_view values borrow immutable input frame; Builder.text/source acquire native backing where required. |
| failure | Truncation, field limit or UTF-8 diagnostics propagate; only local position advances. |
| cost | O(bytes scanned for fields), fixed-width integers and UTF-8 validation; no successful allocation in this reader struct. |
| Design | [docs/ingestion.md §Version-1 binary frame](../../../../ingestion.md), [docs/ingestion.md §Native reader API and memory grant](../../../../ingestion.md), [docs/memory_accounts.md §Native streaming input ownership](../../../../memory_accounts.md) |

## B0034

[Lines 236–260](../../../../../src/io/native_decode.cpp#L236); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Decoded binary(const resource::MemoryAccount& account,std::string_view bytes,const auto& catalog,const InputLimits& limits,std::string_view fingerprint)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Decode one exact native version1 binary full-row event. |
| inputs / outputs | Admits frame/header/length/catalog binding, operation/source flag/schema fields/remaining bytes, each scalar tag and complete end, then freezes/validates. |
| invariants | Row reserve follows schema count and minimum-payload checks. Strings/source are copied from frame before release. Decimal uses inline parse+fixed render equality for canonical wire text; no nullable or multiplicity encoding. |
| ownership | Returned Decoded owns all row/source storage under the supplied account; no raw frame view escapes. |
| failure | Framing/type/tag/domain/binding/size/account/allocation failure unwinds local Builder; accepted source progress is unchanged. |
| cost | O(frame/row/scalar bytes + catalog name comparisons), funded cells/text/final-row overlap; inline numeric/date/decimal decoding avoids ordinary successful scalar text ownership. |
| Design | [docs/ingestion.md §Version-1 binary frame](../../../../ingestion.md), [docs/ingestion.md §Native reader API and memory grant](../../../../ingestion.md), [docs/memory_accounts.md §Native streaming input ownership](../../../../memory_accounts.md) |

## B0035

[Lines 261–261](../../../../../src/io/native_decode.cpp#L261); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L261-L261:sha256:533f16bca7d58f44b3103b92e3485d22cfbb34bbad5ea3f3fa3b5a9dcb24ec89
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Closes the anonymous namespace at this source boundary; this is a lexical delimiter, not an operation. |
| inputs / outputs | No runtime input or output. Declarations following the span leave the preceding C++ scope. |
| invariants | The delimiter ends the preceding scope's visibility/linkage region; it adds no validation, publication, ownership transfer, or runtime authority. |
| ownership | The delimiter adds no owner. If it ends a function/block with live automatic objects, their normal destructors release those objects; namespace and type-definition closes change no existing object's lifetime. |
| failure | No explicit failure translation or catch is added. If a function/block exit destroys automatic objects, exception behavior follows those destructors; namespace/type closes have no runtime failure path. |
| cost | The delimiter adds no algorithmic work. A function/block exit can run existing automatic-object destructors and cleanup; namespace/type closes have no runtime cost. |
| Design | [src/io/native_decode.cpp](../../../../../src/io/native_decode.cpp), [docs/code_specs/files/src/io/native_decode.cpp.md](native_decode.cpp.md), [docs/ingestion.md](../../../../ingestion.md), [docs/session_lifecycle.md](../../../../session_lifecycle.md) |

## B0036

[Lines 262–264](../../../../../src/io/native_decode.cpp#L262); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Decoded decode_json(const resource::MemoryAccount& account,std::string_view text,const CatalogSource& catalog,const InputLimits& limits,std::string_view fingerprint)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Dispatch native JSON decode against the actual CatalogSource variant. |
| inputs / outputs | Visits owned Catalog or retained program catalog and invokes local funded JsonReader. |
| invariants | No full catalog revalidation per event; caller already admitted/retained catalog and expected fingerprint. |
| ownership | Returned Decoded owns payload; account/text/catalog/limits are borrowed only synchronously. |
| failure | Validation, scalar, size, encoding or allocation errors propagate; local owned scratch is released by RAII. No partial public event/text or accepted source progress is returned. |
| cost | Fixed variant dispatch plus whole native record parsing/freeze/validation. |
| Design | [docs/ingestion.md §Version-1 JSONL event](../../../../ingestion.md), [schemas/physical-update-v1.schema.json](../../../../../schemas/physical-update-v1.schema.json), [docs/ingestion.md §Native reader API and memory grant](../../../../ingestion.md), [docs/memory_accounts.md §Native streaming input ownership](../../../../memory_accounts.md) |

## B0037

[Lines 265–267](../../../../../src/io/native_decode.cpp#L265); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Decoded decode_binary(const resource::MemoryAccount& account,std::string_view text,const CatalogSource& catalog,const InputLimits& limits,std::string_view fingerprint)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Dispatch native binary decode against the actual CatalogSource variant. |
| inputs / outputs | Visits retained catalog and invokes local funded binary decoder with fixed fingerprint. |
| invariants | Does not change the wire or acquire a new account; invalid empty catalog owner rejects in common visitor. |
| ownership | Returned Decoded owns native payload independent of raw frame/catalog view lifetime. |
| failure | Validation, scalar, size, encoding or allocation errors propagate; local owned scratch is released by RAII. No partial public event/text or accepted source progress is returned. |
| cost | Fixed variant dispatch plus whole native frame parsing/freeze/validation. |
| Design | [docs/ingestion.md §Version-1 binary frame](../../../../ingestion.md), [docs/ingestion.md §Native reader API and memory grant](../../../../ingestion.md), [docs/memory_accounts.md §Native streaming input ownership](../../../../memory_accounts.md) |

## B0038

[Lines 268–268](../../../../../src/io/native_decode.cpp#L268); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L268-L268:sha256:023a3ff631933cc0067e8faa10af3c5d55957439c9e0aa528b685ba5a3c9f0e9
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Closes the namespace crown::io::input_detail at this source boundary; this is a lexical delimiter, not an operation. |
| inputs / outputs | No runtime input or output. Declarations following the span leave the preceding C++ scope. |
| invariants | The delimiter ends the preceding scope's visibility/linkage region; it adds no validation, publication, ownership transfer, or runtime authority. |
| ownership | The delimiter adds no owner. If it ends a function/block with live automatic objects, their normal destructors release those objects; namespace and type-definition closes change no existing object's lifetime. |
| failure | No explicit failure translation or catch is added. If a function/block exit destroys automatic objects, exception behavior follows those destructors; namespace/type closes have no runtime failure path. |
| cost | The delimiter adds no algorithmic work. A function/block exit can run existing automatic-object destructors and cleanup; namespace/type closes have no runtime cost. |
| Design | [src/io/native_decode.cpp](../../../../../src/io/native_decode.cpp), [docs/code_specs/files/src/io/native_decode.cpp.md](native_decode.cpp.md), [docs/ingestion.md](../../../../ingestion.md), [docs/session_lifecycle.md](../../../../session_lifecycle.md) |
