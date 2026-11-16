# `src/recovery/session_image.cpp` — block usage map

[Source](../../../../../src/recovery/session_image.cpp) · [Source index](../../../README.md) · [Subsystem contracts](../../../subsystem_contracts.md) · [Reviewed primitives](../../../primitives.md)

Encode, validate and publish checkpoints, journals, generations and local delivery receipts with explicit durable authority.

Snapshot SHA-256: `fd6b2e32ecb3c15672eebf269383b76fe6d776ef61d9a3a56ce7749e41a99d1e`. 391 lines partitioned into 44 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [recovery](../../../subsystem_contracts.md#recovery). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/checkpoints.md](../../../../checkpoints.md), [docs/journal.md](../../../../journal.md), [docs/journal-files.md](../../../../journal-files.md), [docs/generations.md](../../../../generations.md), [docs/local-sink.md](../../../../local-sink.md), [docs/history-retirement.md](../../../../history-retirement.md), [docs/update_patterns.md](../../../../update_patterns.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–15](../../../../../src/recovery/session_image.cpp#L1) | Imports dependencies; declares namespace scope; declares aliases; declares values/defaults or compile-time conditions. |  · [reviewed contract](#b0001) |
| [B0002 · 16–26](../../../../../src/recovery/session_image.cpp#L16) | Callable definition: bool utf8(std::string_view value) | calls size; returns false; false; 2 loop sites · [reviewed contract](#b0002) |
| [B0003 · 27–29](../../../../../src/recovery/session_image.cpp#L27) | Callable definition: void named(std::string_view value,bool empty,bool nul) | calls require, empty, find, utf8; guard require((empty \|\| !value.empty()) && (nul \|\| value.find('\0')==std::string_view::npos) && utf8(valu… · [reviewed contract](#b0003) |
| [B0004 · 30–35](../../../../../src/recovery/session_image.cpp#L30) | Callable definition: const io::AccountedInputProgress& progress(const SessionCheckpoint& value) | calls std::visit, constexpr; returns std::visit(\[\](const auto& source)-&gt;const io::AccountedInputProgress& {; source · [reviewed contract](#b0004) |
| [B0005 · 36–40](../../../../../src/recovery/session_image.cpp#L36) | Callable definition: bool canonical_typed(const io::AccountedInputOptions::Values& value) | calls empty; returns value.format==io::InputFormat::jsonl && !value.table && value.delimiter==@ && value.header &&; growth insert · [reviewed contract](#b0005) |
| [B0006 · 41–44](../../../../../src/recovery/session_image.cpp#L41) | declares types or opens a type body; declares values/defaults or compile-time conditions. |  · [reviewed contract](#b0006) |
| [B0007 · 45–47](../../../../../src/recovery/session_image.cpp#L45) | Callable definition: void window_charge(std::uint64_t amount) | calls require; guard require(window_work&lt;=state_limits.window.work && amount&lt;=state_limits.window.work-window_work,Image… · [reviewed contract](#b0007) |
| [B0008 · 48–50](../../../../../src/recovery/session_image.cpp#L48) | Callable definition: template&lt;class T&gt; void enumeration(T value,T maximum) | calls require, integer; guard require(static_cast&lt;std::uint64_t&gt;(value)&lt;=static_cast&lt;std::uint64_t&gt;(maximum));integer(static_cast… · [reviewed contract](#b0008) |
| [B0009 · 51–51](../../../../../src/recovery/session_image.cpp#L51) | Callable definition: void boolean(bool value) | calls integer · [reviewed contract](#b0009) |
| [B0010 · 52–52](../../../../../src/recovery/session_image.cpp#L52) | Callable definition: void optional(std::optional&lt;std::uint64_t&gt; value) | calls boolean, has_value, integer · [reviewed contract](#b0010) |
| [B0011 · 53–56](../../../../../src/recovery/session_image.cpp#L53) | Callable definition: void text(std::string_view value,std::uint64_t cap,bool empty=true,bool nul=true) | calls require, size, charge, named; guard require(value.size()&lt;=cap && value.size()&lt;=budget.limits.scalar_bytes,ImageFault::limit); · [reviewed contract](#b0011) |
| [B0012 · 57–57](../../../../../src/recovery/session_image.cpp#L57) | Callable definition: void hash(const std::array&lt;char,64&gt;& value) | calls require, hex, put, data; guard void hash(const std::array&lt;char,64&gt;& value){require(hex(value),ImageFault::binding);put({value.data… · [reviewed contract](#b0012) |
| [B0013 · 58–61](../../../../../src/recovery/session_image.cpp#L58) | Callable definition: void input_limits(const io::InputLimits& value) | calls integer, optional; 1 loop sites · [reviewed contract](#b0013) |
| [B0014 · 62–62](../../../../../src/recovery/session_image.cpp#L62) | Callable definition: void queue_limits(const io::QueueLimits& value) | calls integer · [reviewed contract](#b0014) |
| [B0015 · 63–72](../../../../../src/recovery/session_image.cpp#L63) | Callable definition: void input(const io::AccountedInputOptions::Values& value) | calls enumeration, input_limits, boolean, has_value; guard require(value.relation_tokens.size()&lt;=limits.relation_tokens,ImageFault::limit);integer(value.relat…; 1 loop sites · [reviewed contract](#b0015) |
| [B0016 · 73–78](../../../../../src/recovery/session_image.cpp#L73) | Callable definition: void source_progress(const io::AccountedInputProgress& value,const io::InputLimits& cap) | calls require, size, integer, text; guard require(value.source_positions.size()&lt;=state_limits.source.positions && value.source_positions.size…; 1 loop sites · [reviewed contract](#b0016) |
| [B0017 · 79–82](../../../../../src/recovery/session_image.cpp#L79) | Callable definition: void row(storage::RowView value) | calls window_charge, size, require, integer; guard budget.row();window_charge(1);window_charge(value.size());require(value.size()&lt;=budget.limits.field…; 1 loop sites · [reviewed contract](#b0017) |
| [B0018 · 83–116](../../../../../src/recovery/session_image.cpp#L83) | Callable definition: void window(const WindowCheckpoint& value) | calls require, window_charge, size, capacity; guard require(state_limits.matching_work&gt;0,ImageFault::work);window_charge(1);window_charge(options.manag…; 4 loop sites · [reviewed contract](#b0018) |
| [B0019 · 117–117](../../../../../src/recovery/session_image.cpp#L117) | Closes surrounding scope/type. |  · [reviewed contract](#b0019) |
| [B0020 · 118–172](../../../../../src/recovery/session_image.cpp#L118) | Callable definition: void write(Output& out,const SessionCheckpoint& value) | calls require, put, integer, enumeration; guard require(value.version==(value.update_patterns?SessionCheckpoint::current_version:SessionCheckpoint:…; 4 loop sites · [reviewed contract](#b0020) |
| [B0021 · 173–179](../../../../../src/recovery/session_image.cpp#L173) | declares types or opens a type body; declares values/defaults or compile-time conditions. |  · [reviewed contract](#b0021) |
| [B0022 · 180–182](../../../../../src/recovery/session_image.cpp#L180) | Callable definition: void source_charge(std::uint64_t& used,std::uint64_t amount) | calls require; guard require(used&lt;=state_limits.source.work && amount&lt;=state_limits.source.work-used,ImageFault::work);u… · [reviewed contract](#b0022) |
| [B0023 · 183–185](../../../../../src/recovery/session_image.cpp#L183) | Callable definition: void window_charge(std::uint64_t amount) | calls require; guard require(window_work&lt;=state_limits.window.work && amount&lt;=state_limits.window.work-window_work,Image… · [reviewed contract](#b0023) |
| [B0024 · 186–186](../../../../../src/recovery/session_image.cpp#L186) | Callable definition: bool boolean() | calls integer, require; guard bool boolean(){const auto value=integer(1);require(value&lt;=1);return value!=0;}; returns value!=0 · [reviewed contract](#b0024) |
| [B0025 · 187–187](../../../../../src/recovery/session_image.cpp#L187) | Callable definition: std::optional&lt;std::uint64_t&gt; optional() | calls boolean, integer; returns integer(8); std::nullopt · [reviewed contract](#b0025) |
| [B0026 · 188–190](../../../../../src/recovery/session_image.cpp#L188) | Callable definition: template&lt;class T&gt; T enumeration(T maximum) | calls integer, require; guard const auto value=integer(1);require(value&lt;=static_cast&lt;std::uint64_t&gt;(maximum));return static_cast&lt;…; returns static_cast&lt;T&gt;(value) · [reviewed contract](#b0026) |
| [B0027 · 191–193](../../../../../src/recovery/session_image.cpp#L191) | Callable definition: std::string_view text(std::uint64_t cap,bool empty=true,bool nul=true) | calls take, size, std::min, charge; returns value · [reviewed contract](#b0027) |
| [B0028 · 194–194](../../../../../src/recovery/session_image.cpp#L194) | Callable definition: std::array&lt;char,64&gt; hash() | calls take, std::copy, begin, end; guard std::array&lt;char,64&gt; hash(){std::array&lt;char,64&gt; value{};const auto bytes=take(64);std::copy(bytes.be…; returns value · [reviewed contract](#b0028) |
| [B0029 · 195–198](../../../../../src/recovery/session_image.cpp#L195) | Callable definition: io::InputLimits input_limits() | calls size, optional; returns value · [reviewed contract](#b0029) |
| [B0030 · 199–199](../../../../../src/recovery/session_image.cpp#L199) | Callable definition: io::QueueLimits queue_limits() | calls size; returns {size(SIZE_MAX),size(SIZE_MAX),size(SIZE_MAX)} · [reviewed contract](#b0030) |
| [B0031 · 200–200](../../../../../src/recovery/session_image.cpp#L200) | Type/record definition: struct InputPolicy |  · [reviewed contract](#b0031) |
| [B0032 · 201–222](../../../../../src/recovery/session_image.cpp#L201) | Callable definition: InputPolicy input_options() | calls source_charge, emplace, enumeration, input_limits; guard const auto name=text(cap.field_bytes,false);source_charge(work,name.size());budget.charge(previous.…; returns {cap,format,header,work,canonical}; growth copy_of, emplace, insert; 1 loop sites · [reviewed contract](#b0032) |
| [B0033 · 223–233](../../../../../src/recovery/session_image.cpp#L223) | Callable definition: std::uint64_t source_progress(const io::InputLimits& cap,io::AccountedInputProgress* output,std::uint64_t& work) | calls source_charge, integer, size, io::AccountedInputProgress; guard const auto name=text(cap.source_bytes,false,false);source_charge(work,1);source_charge(work,name.si…; returns sequence; 1 loop sites · [reviewed contract](#b0033) |
| [B0034 · 234–239](../../../../../src/recovery/session_image.cpp#L234) | Callable definition: storage::AccountedRow row() | calls size, window_charge, require, reserve; guard budget.row();const auto count=size(budget.limits.fields);window_charge(1);window_charge(count);requ…; returns result?storage::AccountedRow::copy_of(account,storage::RowView::borrow(cells),image_owner):storage:…; growth copy_of, push_back, reserve; 1 loop sites · [reviewed contract](#b0034) |
| [B0035 · 240–244](../../../../../src/recovery/session_image.cpp#L240) | Callable definition: std::uint64_t at(std::size_t start) | calls charge, require, size, std::uint64_t; guard budget.charge(8);require(start&lt;=input.size() && input.size()-start&gt;=8);std::uint64_t value=0;; returns value; 1 loop sites · [reviewed contract](#b0035) |
| [B0036 · 245–283](../../../../../src/recovery/session_image.cpp#L245) | Callable definition: void window(SessionImageManifest& manifest) | calls require, size, window_charge, reserve; guard require(state_limits.matching_work&gt;0,ImageFault::work);; growth copy_of, emplace, push_back, reserve; 4 loop sites · [reviewed contract](#b0036) |
| [B0037 · 284–284](../../../../../src/recovery/session_image.cpp#L284) | Closes surrounding scope/type. |  · [reviewed contract](#b0037) |
| [B0038 · 285–345](../../../../../src/recovery/session_image.cpp#L285) | Callable definition: InspectedSessionImage read(Input& in) | calls integer, require, enumeration, boolean; guard require(m.state_version==SessionCheckpoint::legacy_version \|\| m.state_version==SessionCheckpoint::c…; returns info; growth push_back, reserve; 3 loop sites · [reviewed contract](#b0038) |
| [B0039 · 346–347](../../../../../src/recovery/session_image.cpp#L346) | Closes surrounding scope/type. | source comment (unverified): // namespace · [reviewed contract](#b0039) |
| [B0040 · 348–368](../../../../../src/recovery/session_image.cpp#L348) | Callable definition: SessionImage encode_session_image(const resource::MemoryAccount& account,const SessionCheckpoint& state, const SessionCheckpointL… | calls inspect_image, data, size, require; guard require(inner.manifest.epoch==state.committed_sequence && inner.manifest.binding.policy==runtime::d…; returns image; growth reserve; 1 loop sites; source comment (unverified): // Size/validate both write passes before final account allocation. This · [reviewed contract](#b0040) |
| [B0041 · 369–380](../../../../../src/recovery/session_image.cpp#L369) | Callable definition: detail::ValidatedSessionImage detail::validate_session_image(std::string_view bytes,const SessionCheckpointLimits& native,Session… | calls require, size, take, integer; guard require(bytes.size()&lt;=limits.envelope.bytes,ImageFault::limit);Budget budget{limits.envelope};Reade…; returns {bytes,info,native,limits}; source comment (unverified): // Validation builds no decoded heap graph. Keep these exact input bytes · [reviewed contract](#b0041) |
| [B0042 · 381–383](../../../../../src/recovery/session_image.cpp#L381) | Callable definition: InspectedSessionImage inspect_session_image(std::string_view bytes,const SessionCheckpointLimits& native,SessionImageLimits limit… | calls detail::validate_session_image; returns detail::validate_session_image(bytes,native,limits).inspected · [reviewed contract](#b0042) |
| [B0043 · 384–390](../../../../../src/recovery/session_image.cpp#L384) | Callable definition: detail::DecodedSessionImage detail::materialize_session_image(const resource::MemoryAccount& account,const ValidatedSessionImage&… | calls substr, read; returns result; source comment (unverified): // Adopt only a prior validation of unchanged bytes/limits. Native metadata · [reviewed contract](#b0043) |
| [B0044 · 391–391](../../../../../src/recovery/session_image.cpp#L391) | Closes surrounding scope/type. | source comment (unverified): // namespace crown::recovery · [reviewed contract](#b0044) |

## B0001

[Lines 1–15](../../../../../src/recovery/session_image.cpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
#include "crown/recovery/session_image.hpp"
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Assemble pointer-free native session envelope codec and phase-specific helpers. |
| inputs / outputs | Session types, SHA, binary Writer/Reader/Budget, private native adoption and policy/source-state validators; fixed magic CROWNSI1. |
| invariants | Existing v1 envelope carries non-null native set session/runtime/window state, not nullable SQL-rows/aggregate transactions or W06 recovery. |
| ownership | Declarations create no heap account/runtime owner or filesystem authority. |
| failure | No handler/recovery work in includes/aliases/constants. |
| cost | No dynamic work for declarations. |
| Design | [docs/checkpoints.md](../../../../checkpoints.md), [include/crown/recovery/session_image.hpp](../../../../../include/crown/recovery/session_image.hpp), [include/crown/runtime/session_checkpoint.hpp](../../../../../include/crown/runtime/session_checkpoint.hpp), [docs/code_review.md](../../../../code_review.md) |

## B0002

[Lines 16–26](../../../../../src/recovery/session_image.cpp#L16); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
bool utf8(std::string_view value) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Validate canonical UTF-8 code-point encoding for metadata text. |
| inputs / outputs | Readable byte view returns false for invalid leading/continuation/truncated, overlong, surrogate or &gt;U+10FFFF sequences. |
| invariants | ASCII NUL is valid UTF-8 here; named separately chooses NUL/emptiness policy. Row scalar strings use raw native bytes and do not pass through this metadata helper. |
| ownership | Borrows bytes only for scan; no normalization or owned output. |
| failure | Boolean rejection, no exception/allocation in helper. |
| cost | O(text bytes), no parser/string mirror. |
| Design | [docs/checkpoints.md](../../../../checkpoints.md), [include/crown/recovery/session_image.hpp](../../../../../include/crown/recovery/session_image.hpp), [include/crown/runtime/session_checkpoint.hpp](../../../../../include/crown/runtime/session_checkpoint.hpp) |

## B0003

[Lines 27–29](../../../../../src/recovery/session_image.cpp#L27); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void named(std::string_view value,bool empty,bool nul) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Apply metadata text emptiness/NUL and UTF-8 rules. |
| inputs / outputs | string_view plus allowed-empty/allowed-NUL flags require those policies and utf8(value). |
| invariants | Source names use nonempty/no-NUL; other option fields have their declared allowances. This does not normalize text or constrain raw row strings. |
| ownership | Borrows view; stores no caller bytes. |
| failure | Fixed ImageFailure(corrupt) on rejection through binary_detail::require. |
| cost | O(text bytes) NUL/UTF-8 scans. |
| Design | [docs/checkpoints.md](../../../../checkpoints.md), [include/crown/recovery/session_image.hpp](../../../../../include/crown/recovery/session_image.hpp), [include/crown/runtime/session_checkpoint.hpp](../../../../../include/crown/runtime/session_checkpoint.hpp) |

## B0004

[Lines 30–35](../../../../../src/recovery/session_image.cpp#L30); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
const io::AccountedInputProgress& progress(const SessionCheckpoint& value) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Borrow accepted source progress from the correct checkpoint variant. |
| inputs / outputs | SessionCheckpoint source variant returns direct AccountedInputProgress or Reader/QueueCheckpoint.progress by const reference. |
| invariants | Variant-state/control compatibility is validated by write; helper itself only selects the embedded progress. |
| ownership | Borrows checkpoint; caller retains it for returned reference. |
| failure | No allocation, syscall or handler; ordinary valid variant visitation. |
| cost | Constant variant dispatch. |
| Design | [docs/checkpoints.md](../../../../checkpoints.md), [include/crown/recovery/session_image.hpp](../../../../../include/crown/recovery/session_image.hpp), [include/crown/runtime/session_checkpoint.hpp](../../../../../include/crown/runtime/session_checkpoint.hpp) |

## B0005

[Lines 36–40](../../../../../src/recovery/session_image.cpp#L36); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
bool canonical_typed(const io::AccountedInputOptions::Values& value) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Recognize the canonical options shape for typed queue input. |
| inputs / outputs | InputOptions::Values must be jsonl, no fixed table/token/null/source/offset/total-byte policy, comma/header/insert defaults. |
| invariants | Typed source limits can still vary; canonical shape prevents irrelevant text-adapter policy leaking into native queue restore. Does not compare catalogs or rows. |
| ownership | Borrows owning option graph, returns Boolean. |
| failure | No allocation or mutation. |
| cost | Fixed fields/empty-map checks. |
| Design | [docs/checkpoints.md](../../../../checkpoints.md), [include/crown/recovery/session_image.hpp](../../../../../include/crown/recovery/session_image.hpp), [include/crown/runtime/session_checkpoint.hpp](../../../../../include/crown/runtime/session_checkpoint.hpp) |

## B0006

[Lines 41–44](../../../../../src/recovery/session_image.cpp#L41); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct Output:Writer {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Extend binary Writer with native session limits and local window work accounting. |
| inputs / outputs | Output borrows envelope Budget/output pointer plus SessionCheckpointLimits/SessionImageLimits and starts window_work=0. |
| invariants | Same write code runs sizing and materialization; null output means no byte-vector mutation. Native/source/window limits remain separate domains. |
| ownership | Stack codec borrows limits and optional receiver-owned final byte vector; it owns no account. |
| failure | Helpers propagate fixed ImageFailure or actual receiver allocation failures; no local catch/partial result publication. |
| cost | Fixed fields; later methods debit visits/bytes explicitly. |
| Design | [docs/checkpoints.md](../../../../checkpoints.md), [include/crown/recovery/session_image.hpp](../../../../../include/crown/recovery/session_image.hpp), [include/crown/runtime/session_checkpoint.hpp](../../../../../include/crown/runtime/session_checkpoint.hpp), [src/recovery/binary_detail.hpp](../../../../../src/recovery/binary_detail.hpp) |

## B0007

[Lines 45–47](../../../../../src/recovery/session_image.cpp#L45); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void window_charge(std::uint64_t amount) {
    require(window_work<=state_limits.window.work && amount<=state_limits.window.work-window_work,ImageFault::work);window_work+=amount;
  }
  template<class T> void enumeration(T value,T maximum) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Debit Output window structural visits without mixing them into native update grants. |
| inputs / outputs | Amount adds to window_work iff within state_limits.window.work. |
| invariants | Fresh codec-call budget counts window row/field/managed-table visits; envelope serialized-byte budget is separate. |
| ownership | Mutates one stack counter only. |
| failure | ImageFailure(work) before over-cap/overflow. |
| cost | Constant checked add. |
| Design | [docs/checkpoints.md](../../../../checkpoints.md), [include/crown/recovery/session_image.hpp](../../../../../include/crown/recovery/session_image.hpp), [include/crown/runtime/session_checkpoint.hpp](../../../../../include/crown/runtime/session_checkpoint.hpp) |

## B0008

[Lines 48–50](../../../../../src/recovery/session_image.cpp#L48); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
template<class T> void enumeration(T value,T maximum) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Encode an enum only within its declared wire domain. |
| inputs / outputs | Enum value&lt;=maximum serializes one unsigned byte. |
| invariants | Negative/unknown values cast to U64 cannot pass valid small maximum. Closed enum range is structural, not runtime program admission. |
| ownership | Writes to sizing counter or final buffer through Writer. |
| failure | Corrupt/range/work/byte/allocation failure propagates before complete image publication. |
| cost | One comparison plus one-byte Writer cost. |
| Design | [docs/checkpoints.md](../../../../checkpoints.md), [include/crown/recovery/session_image.hpp](../../../../../include/crown/recovery/session_image.hpp), [include/crown/runtime/session_checkpoint.hpp](../../../../../include/crown/runtime/session_checkpoint.hpp) |

## B0009

[Lines 51–51](../../../../../src/recovery/session_image.cpp#L51); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void boolean(bool value){integer(value,1);}
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Encode a Boolean in canonical one-byte form. |
| inputs / outputs | bool serializes0/1 through Writer.integer width1. |
| invariants | No alternate true encodings are emitted. |
| ownership | No borrowed payload retained. |
| failure | Writer byte/work/account failure propagates. |
| cost | One byte, no standalone allocation. |
| Design | [docs/checkpoints.md](../../../../checkpoints.md), [include/crown/recovery/session_image.hpp](../../../../../include/crown/recovery/session_image.hpp), [include/crown/runtime/session_checkpoint.hpp](../../../../../include/crown/runtime/session_checkpoint.hpp) |

## B0010

[Lines 52–52](../../../../../src/recovery/session_image.cpp#L52); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void optional(std::optional<std::uint64_t> value){boolean(value.has_value());if(value)integer(*value,8);}
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Encode an optional U64 with explicit presence. |
| inputs / outputs | Writes canonical Boolean then eight-byte integer iff engaged, including zero as a present value. |
| invariants | Absence is distinct from a zero limit/value; no implicit default conversion. |
| ownership | Inline metadata only. |
| failure | Writer budget/allocation failure propagates; image remains private. |
| cost | One or nine encoded bytes. |
| Design | [docs/checkpoints.md](../../../../checkpoints.md), [include/crown/recovery/session_image.hpp](../../../../../include/crown/recovery/session_image.hpp), [include/crown/runtime/session_checkpoint.hpp](../../../../../include/crown/runtime/session_checkpoint.hpp) |

## B0011

[Lines 53–56](../../../../../src/recovery/session_image.cpp#L53); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void text(std::string_view value,std::uint64_t cap,bool empty=true,bool nul=true) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Encode bounded validated metadata text with exact byte length. |
| inputs / outputs | View, semantic cap and empty/NUL flags check cap/envelope scalar_bytes, debit validation visit bytes, validate named(), then length+payload. |
| invariants | UTF-8 metadata copied exactly without normalization. This helper is not used for native raw row string scalars. |
| ownership | Borrows source text during write; final accounted image owns copied bytes. |
| failure | Limit/corrupt/work/allocation error aborts private encoding. |
| cost | O(text bytes) scans/copies; sizing/materialization execute same validation logic. |
| Design | [docs/checkpoints.md](../../../../checkpoints.md), [include/crown/recovery/session_image.hpp](../../../../../include/crown/recovery/session_image.hpp), [include/crown/runtime/session_checkpoint.hpp](../../../../../include/crown/runtime/session_checkpoint.hpp) |

## B0012

[Lines 57–57](../../../../../src/recovery/session_image.cpp#L57); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void hash(const std::array<char,64>& value){require(hex(value),ImageFault::binding);put({value.data(),value.size()});}
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Encode a lowercase fixed-width hash binding. |
| inputs / outputs | ASCII64 array must pass hex then Writer.put64 bytes. |
| invariants | Structural digest spelling is validated; actual referenced program/source/catalog identity is checked separately. |
| ownership | Borrows fixed array, final image copies bytes. |
| failure | ImageFailure(binding) or Writer limit/work/allocation failure. |
| cost | Fixed64-byte scan/copy. |
| Design | [docs/checkpoints.md](../../../../checkpoints.md), [include/crown/recovery/session_image.hpp](../../../../../include/crown/recovery/session_image.hpp), [include/crown/runtime/session_checkpoint.hpp](../../../../../include/crown/runtime/session_checkpoint.hpp) |

## B0013

[Lines 58–61](../../../../../src/recovery/session_image.cpp#L58); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void input_limits(const io::InputLimits& value) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Serialize native input policy resource fields with explicit optional ceilings. |
| inputs / outputs | Record/field/column/source-name/source-count U64 values then optional total bytes/record count. |
| invariants | No record processing or grant reset; these are captured policy values. Semantic source admission follows restore. |
| ownership | Fixed value copies into image. |
| failure | Writer byte/work/allocation failure propagates. |
| cost | Fixed field count and up to two optional payloads. |
| Design | [docs/checkpoints.md](../../../../checkpoints.md), [include/crown/recovery/session_image.hpp](../../../../../include/crown/recovery/session_image.hpp), [include/crown/runtime/session_checkpoint.hpp](../../../../../include/crown/runtime/session_checkpoint.hpp) |

## B0014

[Lines 62–62](../../../../../src/recovery/session_image.cpp#L62); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void queue_limits(const io::QueueLimits& value){integer(value.batches,8);integer(value.events,8);integer(value.bytes,8);}
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Serialize the typed queue capacity policy. |
| inputs / outputs | QueueLimits batches/events/bytes serialize as three U64 fields. |
| invariants | Queue contents are absent at quiescent checkpoint; this policy does not invent queued events. |
| ownership | Fixed metadata, no queue owner retained. |
| failure | Writer budget/account failure only. |
| cost | 24 encoded bytes. |
| Design | [docs/checkpoints.md](../../../../checkpoints.md), [include/crown/recovery/session_image.hpp](../../../../../include/crown/recovery/session_image.hpp), [include/crown/runtime/session_checkpoint.hpp](../../../../../include/crown/runtime/session_checkpoint.hpp) |

## B0015

[Lines 63–72](../../../../../src/recovery/session_image.cpp#L63); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void input(const io::AccountedInputOptions::Values& value) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Serialize captured account-owned text/typed input options. |
| inputs / outputs | Format/limits/table/delimiter/header/op, bounded sorted relation-token map, optional null/source names and byte origin are written. |
| invariants | Caller checkpoint owns validated native options; text helper validates metadata bytes/flags, relation count obeys envelope cap. Catalog/table/format semantic matching remains restoring source responsibility. |
| ownership | Borrows option graph; image receives owned bytes, no ordinary InputOptions graph is created. |
| failure | Enum/limit/name/byte/work/allocation failure aborts encoding. |
| cost | O(option metadata/token/name bytes) traversal/copy plus policy fields; no input stream reads. |
| Design | [docs/checkpoints.md](../../../../checkpoints.md), [include/crown/recovery/session_image.hpp](../../../../../include/crown/recovery/session_image.hpp), [include/crown/runtime/session_checkpoint.hpp](../../../../../include/crown/runtime/session_checkpoint.hpp) |

## B0016

[Lines 73–78](../../../../../src/recovery/session_image.cpp#L73); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void source_progress(const io::AccountedInputProgress& value,const io::InputLimits& cap) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Encode accepted source sequence and exact per-source byte offsets. |
| inputs / outputs | Progress map count is bounded by source-state positions, input sources and accepted sequence; sequence/count and each validated name/offset are emitted. |
| invariants | Does not serialize a cached unacknowledged input or reset source counters. Ordered native map supplies canonical name order. |
| ownership | Borrows AccountedInputProgress; final image copies names/offsets. |
| failure | Cap/name/Writer failure propagates before publication. |
| cost | O(number/source-name bytes) traversal/copy; separate source_budget validates native source units in write. |
| Design | [docs/checkpoints.md](../../../../checkpoints.md), [include/crown/recovery/session_image.hpp](../../../../../include/crown/recovery/session_image.hpp), [include/crown/runtime/session_checkpoint.hpp](../../../../../include/crown/runtime/session_checkpoint.hpp) |

## B0017

[Lines 79–82](../../../../../src/recovery/session_image.cpp#L79); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void row(storage::RowView value) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Encode one non-null native window row through existing scalar wire rules. |
| inputs / outputs | RowView charges envelope row and local window1+arity, writes bounded field count and each scalar tag/payload. |
| invariants | Raw scalar string bytes, including NUL/non-UTF8, are preserved. Scalar encodings/types are the existing native image domain; metadata named() does not apply. |
| ownership | Borrows native row for call; image owns encoded scalar bytes. |
| failure | Row/field/scalar/work/byte or allocation failure aborts unpublished image. |
| cost | O(arity+scalar bytes), with inline decimal rendering bounded by native type. |
| Design | [docs/checkpoints.md](../../../../checkpoints.md), [include/crown/recovery/session_image.hpp](../../../../../include/crown/recovery/session_image.hpp), [include/crown/runtime/session_checkpoint.hpp](../../../../../include/crown/runtime/session_checkpoint.hpp), [src/recovery/binary_detail.hpp](../../../../../src/recovery/binary_detail.hpp), [tests/unit/session_image_test.cpp](../../../../../tests/unit/session_image_test.cpp) |

## B0018

[Lines 83–116](../../../../../src/recovery/session_image.cpp#L83); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void window(const WindowCheckpoint& value) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Encode only quiescent structural window checkpoint state. |
| inputs / outputs | Managed table IDs/capacity, positive width/FIFO/resource limits, independent progress/catalog/work/stopped flags, sorted positive count/label IDs and row/deadline/reference metadata serialize. |
| invariants | Reject active expansion or impossible initial progress. Capacity/labels/counts/window/envelope limits checked. Full count-reference equality, catalog row semantics and native base/window membership matching are deferred to restore; this codec does not grant owner authority. FIFO remains one byte: values 0/1 keep their old bytes/meaning; 2/3 preserve physical lifetime scope and count IDs. Older readers reject 2/3; values above 3 reject. The field layout is unchanged. Admit window enum values 0..4, preserving each earlier value and field position. |
| ownership | Borrows checkpoint options/owned rows; final image copies wire bytes without FIFO/expiration index duplication. |
| failure | Structural/budget/cap/deadline/ID failure stops private encoding. matching_work must be nonzero but actual semantic matching occurs later. |
| cost | O(M^2) managed-table duplicate checks plus row/label/count bytes; serialized window-work counts1+M+per-row arities separately from envelope bytes. |
| Design | [docs/checkpoints.md](../../../../checkpoints.md), [include/crown/recovery/session_image.hpp](../../../../../include/crown/recovery/session_image.hpp), [include/crown/runtime/session_checkpoint.hpp](../../../../../include/crown/runtime/session_checkpoint.hpp), [src/runtime/window.cpp](../../../../../src/runtime/window.cpp), [docs/update_patterns.md](../../../../update_patterns.md) |

## B0019

[Lines 117–117](../../../../../src/recovery/session_image.cpp#L117); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L117-L117:sha256:aa1d1a63390229c798347e83a0405441c9400035284ad168c1bf6cdf1d70a370
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Closes the enclosing helper type at this source boundary; this is a lexical delimiter, not an operation. |
| inputs / outputs | No runtime input or output. Declarations following the span leave the preceding C++ scope. |
| invariants | The delimiter ends the preceding scope's visibility/linkage region; it adds no validation, publication, ownership transfer, or runtime authority. |
| ownership | The delimiter adds no owner. If it ends a function/block with live automatic objects, their normal destructors release those objects; namespace and type-definition closes change no existing object's lifetime. |
| failure | No explicit failure translation or catch is added. If a function/block exit destroys automatic objects, exception behavior follows those destructors; namespace/type closes have no runtime failure path. |
| cost | The delimiter adds no algorithmic work. A function/block exit can run existing automatic-object destructors and cleanup; namespace/type closes have no runtime cost. |
| Design | [src/recovery/session_image.cpp](../../../../../src/recovery/session_image.cpp), [docs/code_specs/files/src/recovery/session_image.cpp.md](session_image.cpp.md), [docs/checkpoints.md](../../../../checkpoints.md), [docs/session_lifecycle.md](../../../../session_lifecycle.md) |

## B0020

[Lines 118–172](../../../../../src/recovery/session_image.cpp#L118); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void write(Output& out,const SessionCheckpoint& value) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Write the version-dispatched session envelope in shared sizing/materialization traversals. |
| inputs / outputs | Valid SessionCheckpoint writes header placeholders, state/input kind/flags/sequences,26 policy words and memory cap, snapshot/workload/input/source policies/progress/CSV/window and nested runtime bytes. Require version/presence agreement; emit a declaration extension after window state only for version 2. |
| invariants | Source variant must match stopped/stream/typed mode; canonical typed shape, read/accepted/committed/window progress, EOF/closure and initial state rules checked. Frame/image checksum and full program/window semantics are handled by surrounding phases/restoring session. Undeclared version 1 emits no extension. Pattern metadata has separate parse/import/copy grants and records trusted history, not authenticated proof. |
| ownership | Borrows checkpoint state and native image; final Writer buffer is receiver-account owned. No ordinary policy/row mirror or source read. |
| failure | Structural/format/policy/cap/source/window/Writer failure unwinds private encoder; caller checkpoint/session unchanged. |
| cost | O(serialized bytes) plus native metadata validation, O(CSV fields^2) uniqueness and O(managed tables^2) checks. Executed once for sizing and again for materialization. Version 2 adds bounded O(R) extension work and 97+17R+(violation?25:0) bytes per traversal; no row history is serialized. |
| Design | [docs/checkpoints.md](../../../../checkpoints.md), [include/crown/recovery/session_image.hpp](../../../../../include/crown/recovery/session_image.hpp), [include/crown/runtime/session_checkpoint.hpp](../../../../../include/crown/runtime/session_checkpoint.hpp), [src/io/checkpoint_detail.hpp](../../../../../src/io/checkpoint_detail.hpp), [src/runtime/checkpoint_policy.hpp](../../../../../src/runtime/checkpoint_policy.hpp), [docs/update_patterns.md](../../../../update_patterns.md) |

## B0021

[Lines 173–179](../../../../../src/recovery/session_image.cpp#L173); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct Input:Reader {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Extend Reader for either allocation-free inspection or receiver-account materialization. |
| inputs / outputs | Input borrows raw payload, envelope Budget, state/image limits and account; result=null means validate only, otherwise fill private DecodedSessionImage. |
| invariants | Same parsing rules serve both phases; materialization requires exact previously validated immutable bytes and unchanged limits. No generic deserialization authority is granted by public reports. |
| ownership | Reader text/runtime subviews borrow input. Materialized options/progress/window rows own receiving-account storage; runtime blob remains borrowed until native restore. |
| failure | Fixed ImageFailure/resource errors propagate; callers own private decoded state and unwind it on failure. |
| cost | Fixed parser fields; no allocation merely from constructing Input. |
| Design | [docs/checkpoints.md](../../../../checkpoints.md), [include/crown/recovery/session_image.hpp](../../../../../include/crown/recovery/session_image.hpp), [include/crown/runtime/session_checkpoint.hpp](../../../../../include/crown/runtime/session_checkpoint.hpp), [src/recovery/session_image_detail.hpp](../../../../../src/recovery/session_image_detail.hpp) |

## B0022

[Lines 180–182](../../../../../src/recovery/session_image.cpp#L180); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void source_charge(std::uint64_t& used,std::uint64_t amount) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Debit a local source-validation allowance while reading the envelope. |
| inputs / outputs | Mutable per-source used and amount check/add against state_limits.source.work. |
| invariants | Source options/positions/CSV phases choose shared or separate domain according to source tag; this is not a runtime refill or wall-clock budget. |
| ownership | Stack counters only. |
| failure | ImageFailure(work) before overflow/over-cap increment. |
| cost | Constant checked arithmetic. |
| Design | [docs/checkpoints.md](../../../../checkpoints.md), [include/crown/recovery/session_image.hpp](../../../../../include/crown/recovery/session_image.hpp), [include/crown/runtime/session_checkpoint.hpp](../../../../../include/crown/runtime/session_checkpoint.hpp) |

## B0023

[Lines 183–185](../../../../../src/recovery/session_image.cpp#L183); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void window_charge(std::uint64_t amount) {
    require(window_work<=state_limits.window.work && amount<=state_limits.window.work-window_work,ImageFault::work);window_work+=amount;
  }
  bool boolean(){const auto value=integer(1);require(value<=1);return value!=0;}
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Debit window validation visits during reading/materialization. |
| inputs / outputs | Amount adds to local window_work within state_limits.window.work. |
| invariants | Envelope byte/row/scalar and receiving-account limits remain independent. |
| ownership | Stack scalar counter. |
| failure | Fixed ImageFailure(work) on exhaustion. |
| cost | Constant arithmetic. |
| Design | [docs/checkpoints.md](../../../../checkpoints.md), [include/crown/recovery/session_image.hpp](../../../../../include/crown/recovery/session_image.hpp), [include/crown/runtime/session_checkpoint.hpp](../../../../../include/crown/runtime/session_checkpoint.hpp) |

## B0024

[Lines 186–186](../../../../../src/recovery/session_image.cpp#L186); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
bool boolean(){const auto value=integer(1);require(value<=1);return value!=0;}
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Decode only canonical Boolean0/1. |
| inputs / outputs | One Reader byte returns false/true; values&gt;1 reject. |
| invariants | Rejects alternative encodings before native state adoption. |
| ownership | Inline value; Reader only borrows input. |
| failure | Truncation/corrupt/work failure through Reader/require. |
| cost | One byte and comparison. |
| Design | [docs/checkpoints.md](../../../../checkpoints.md), [include/crown/recovery/session_image.hpp](../../../../../include/crown/recovery/session_image.hpp), [include/crown/runtime/session_checkpoint.hpp](../../../../../include/crown/runtime/session_checkpoint.hpp) |

## B0025

[Lines 187–187](../../../../../src/recovery/session_image.cpp#L187); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::optional<std::uint64_t> optional(){if(boolean())return integer(8);return std::nullopt;}
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Decode explicit optional-U64 presence/value. |
| inputs / outputs | Canonical Boolean false returns nullopt; true reads eight-byte U64 including zero. |
| invariants | No absent/present-zero conflation or default grant behavior. |
| ownership | Inline optional only. |
| failure | Reader/Boolean/work failure propagates. |
| cost | One or nine bytes. |
| Design | [docs/checkpoints.md](../../../../checkpoints.md), [include/crown/recovery/session_image.hpp](../../../../../include/crown/recovery/session_image.hpp), [include/crown/runtime/session_checkpoint.hpp](../../../../../include/crown/runtime/session_checkpoint.hpp) |

## B0026

[Lines 188–190](../../../../../src/recovery/session_image.cpp#L188); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
template<class T> T enumeration(T maximum) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Decode a bounded enum wire value. |
| inputs / outputs | One unsigned byte&lt;=maximum casts to requested enum. |
| invariants | Structural enum closure only; semantic combinations checked by read and later native/session admission. |
| ownership | Inline enum result. |
| failure | Corrupt/truncated/work failure before use. |
| cost | One byte/range check. |
| Design | [docs/checkpoints.md](../../../../checkpoints.md), [include/crown/recovery/session_image.hpp](../../../../../include/crown/recovery/session_image.hpp), [include/crown/runtime/session_checkpoint.hpp](../../../../../include/crown/runtime/session_checkpoint.hpp) |

## B0027

[Lines 191–193](../../../../../src/recovery/session_image.cpp#L191); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::string_view text(std::uint64_t cap,bool empty=true,bool nul=true) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Borrow one bounded validated metadata string from immutable image bytes. |
| inputs / outputs | Length&lt;=min(semantic cap,envelope scalar_bytes), Reader.take then validation debit and named empty/NUL/UTF8 checks. |
| invariants | Metadata view excludes wire length; raw row scalar strings use binary scalar reader instead. |
| ownership | View borrows image; materializing callers explicitly copy into accounted text before retaining. |
| failure | Limit/corrupt/work/truncation failure; no heap in this helper. |
| cost | O(text bytes) validation; zero-copy view construction. |
| Design | [docs/checkpoints.md](../../../../checkpoints.md), [include/crown/recovery/session_image.hpp](../../../../../include/crown/recovery/session_image.hpp), [include/crown/runtime/session_checkpoint.hpp](../../../../../include/crown/runtime/session_checkpoint.hpp) |

## B0028

[Lines 194–194](../../../../../src/recovery/session_image.cpp#L194); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::array<char,64> hash(){std::array<char,64> value{};const auto bytes=take(64);std::copy(bytes.begin(),bytes.end(),value.begin());require(hex(value),ImageFault::binding);return value;}
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Decode and validate a fixed ASCII64 binding digest. |
| inputs / outputs | Take64 bytes, copy into fixed array, require lowercase hex. |
| invariants | Digest format is descriptive until actual program/catalog/source binding checks. |
| ownership | Owning fixed array result, no image view retained. |
| failure | Binding/truncation/work failure, no allocation. |
| cost | Fixed64-byte scan/copy. |
| Design | [docs/checkpoints.md](../../../../checkpoints.md), [include/crown/recovery/session_image.hpp](../../../../../include/crown/recovery/session_image.hpp), [include/crown/runtime/session_checkpoint.hpp](../../../../../include/crown/runtime/session_checkpoint.hpp) |

## B0029

[Lines 195–198](../../../../../src/recovery/session_image.cpp#L195); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
io::InputLimits input_limits() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Decode source resource policy dimensions without allocation. |
| inputs / outputs | Reads five host-size-bounded limits and optional total_bytes/records into InputLimits. |
| invariants | Restoring source enforces remaining semantic option/record policy; no counters are reset by decoding. |
| ownership | Fixed value struct. |
| failure | Limit/truncation/Boolean/work failure. |
| cost | Fixed field/optional byte count. |
| Design | [docs/checkpoints.md](../../../../checkpoints.md), [include/crown/recovery/session_image.hpp](../../../../../include/crown/recovery/session_image.hpp), [include/crown/runtime/session_checkpoint.hpp](../../../../../include/crown/runtime/session_checkpoint.hpp) |

## B0030

[Lines 199–199](../../../../../src/recovery/session_image.cpp#L199); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
io::QueueLimits queue_limits(){return {size(SIZE_MAX),size(SIZE_MAX),size(SIZE_MAX)};}
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Decode typed queue capacity dimensions. |
| inputs / outputs | Three host-size-bounded lengths construct QueueLimits. |
| invariants | No queued input contents are materialized; source restore admits policy separately. |
| ownership | Inline limits only. |
| failure | Reader size/work/truncation failure. |
| cost | 24 bytes and fixed checks. |
| Design | [docs/checkpoints.md](../../../../checkpoints.md), [include/crown/recovery/session_image.hpp](../../../../../include/crown/recovery/session_image.hpp), [include/crown/runtime/session_checkpoint.hpp](../../../../../include/crown/runtime/session_checkpoint.hpp) |

## B0031

[Lines 200–200](../../../../../src/recovery/session_image.cpp#L200); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct InputPolicy {io::InputLimits limits;io::InputFormat format;bool header;std::uint64_t work;bool canonical_typed;};
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Carry parsed input-policy facts needed before account-owned options exist. |
| inputs / outputs | InputLimits, format/header, local source-work used and canonical_typed flag describe the parsed policy. |
| invariants | Inspection uses fixed facts instead of allocating ordinary InputOptions/AccountedInputOptions graph. |
| ownership | Fixed inline fields; no borrowed text or runtime pointer. |
| failure | Carrier construction adds no failure path. |
| cost | Fixed stack metadata. |
| Design | [docs/checkpoints.md](../../../../checkpoints.md), [include/crown/recovery/session_image.hpp](../../../../../include/crown/recovery/session_image.hpp), [include/crown/runtime/session_checkpoint.hpp](../../../../../include/crown/runtime/session_checkpoint.hpp) |

## B0032

[Lines 201–222](../../../../../src/recovery/session_image.cpp#L201); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
InputPolicy input_options() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Parse canonical input options and optionally adopt receiver-funded native ownership. |
| inputs / outputs | Reads format/limits/defaults/table/token count, strictly increasing validated token names, optional null/source and offset; returns InputPolicy and optionally fills state.input_options. |
| invariants | Inspection result=null never constructs AccountedInputOptions/text/map. Materialization copies into native receiving-account owners through private SessionImageAccess; typed canonical shape returned for read consistency checks. |
| ownership | Image views used only during parsing; retained token/text/control graph owns receiver storage. No ordinary intermediate options graph. |
| failure | Enum/order/name/cap/source-work/byte failure occurs without allocation in validation; materialization allocation failures unwind private result. |
| cost | O(metadata/token/name bytes) validation plus ordered native map insertion/copy in materialization. Adjacent name comparison uses declared envelope bytes. |
| Design | [docs/checkpoints.md](../../../../checkpoints.md), [include/crown/recovery/session_image.hpp](../../../../../include/crown/recovery/session_image.hpp), [include/crown/runtime/session_checkpoint.hpp](../../../../../include/crown/runtime/session_checkpoint.hpp), [src/recovery/session_image_detail.hpp](../../../../../src/recovery/session_image_detail.hpp) |

```text
for(std::size_t i=0;i<count;++i) {
      const auto name=text(cap.field_bytes,false);
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Check canonical sorted relation-token names without an inspection-time map. |
| inputs / outputs | Each bounded UTF-8 token name must be strictly greater than previous; table ID follows, optional materialization copies native text/map node. |
| invariants | Zero-allocation validation uses borrowed adjacent names; catalog membership still belongs to source restore. |
| ownership | Materialized names own receiving-account bytes; inspection retains no view after call. |
| failure | Name/order/work/size/account failure drops private candidate. |
| cost | O(total name/compared bytes) inspection, plus native ordered map inserts when materializing. |
| Design | [docs/checkpoints.md](../../../../checkpoints.md), [include/crown/recovery/session_image.hpp](../../../../../include/crown/recovery/session_image.hpp), [include/crown/runtime/session_checkpoint.hpp](../../../../../include/crown/runtime/session_checkpoint.hpp) |

## B0033

[Lines 223–233](../../../../../src/recovery/session_image.cpp#L223); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::uint64_t source_progress(const io::InputLimits& cap,io::AccountedInputProgress* output,std::uint64_t& work) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Read accepted source progress with exact sorted unique names. |
| inputs / outputs | Sequence plus count bounded by state positions/input sources/sequence parse names/offsets and optionally prepare/publish receiver-account positions. |
| invariants | Strict increasing names avoid duplicates without a scratch set. Decoding preserves accepted offsets, not cached unread records; per-source validation work stays explicit. |
| ownership | Inspection borrows views only; optional output owns native AccountedInputProgress/map/text in receiver. |
| failure | Limit/order/name/work failure before public owner; partial materialized map unwinds privately. |
| cost | O(position/name bytes) scan and adjacent comparisons; materialization adds O(P log P) native directory operations/copy. |
| Design | [docs/checkpoints.md](../../../../checkpoints.md), [include/crown/recovery/session_image.hpp](../../../../../include/crown/recovery/session_image.hpp), [include/crown/runtime/session_checkpoint.hpp](../../../../../include/crown/runtime/session_checkpoint.hpp) |

## B0034

[Lines 234–239](../../../../../src/recovery/session_image.cpp#L234); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
storage::AccountedRow row() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Validate native window scalar bytes and optionally freeze one receiving-account row. |
| inputs / outputs | Envelope row/field and window visits precede scalar parsing; result=null discards inline ScalarViews, result!=null temporarily buffers views then AccountedRow::copy_of. |
| invariants | Raw string scalar bytes remain raw; date/decimal/Boolean/tag canonicality follows binary_detail. Catalog type/decimal policy and label/count/base matching are later admission checks. |
| ownership | Inspection allocates nothing. Materialization temporary ScalarView vector and final native row use same receiving account; text views borrow immutable input only until copied. |
| failure | Structural/field/scalar/work/row/account allocation failure leaves no public result. |
| cost | O(arity+scalar bytes) parse/copy, temporary O(arity) view storage only in materialization. |
| Design | [docs/checkpoints.md](../../../../checkpoints.md), [include/crown/recovery/session_image.hpp](../../../../../include/crown/recovery/session_image.hpp), [include/crown/runtime/session_checkpoint.hpp](../../../../../include/crown/runtime/session_checkpoint.hpp), [src/recovery/binary_detail.hpp](../../../../../src/recovery/binary_detail.hpp), [src/storage/accounted_row.cpp](../../../../../src/storage/accounted_row.cpp) |

## B0035

[Lines 240–244](../../../../../src/recovery/session_image.cpp#L240); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::uint64_t at(std::size_t start) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Read a previously parsed little-endian U64 directly for allocation-free duplicate checks. |
| inputs / outputs | Payload offset is bounds checked, debited8 bytes, and read without moving Reader.position. |
| invariants | Callers pass starts of prior fixed-size managed-table/CSV fields. No extra lookup map or whole-structure clone. |
| ownership | Borrows immutable input; returns scalar. |
| failure | Corrupt/work failure before out-of-range access. |
| cost | Eight loads/shifts plus checks. |
| Design | [docs/checkpoints.md](../../../../checkpoints.md), [include/crown/recovery/session_image.hpp](../../../../../include/crown/recovery/session_image.hpp), [include/crown/runtime/session_checkpoint.hpp](../../../../../include/crown/runtime/session_checkpoint.hpp) |

## B0036

[Lines 245–283](../../../../../src/recovery/session_image.cpp#L245); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void window(SessionImageManifest& manifest) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Parse quiescent window metadata and optionally build native checkpoint rows/options. |
| inputs / outputs | Managed count/capacity and unique IDs, positive policies, matching accepted/committed/stopped progress, hash/work, sorted count/label IDs, raw rows and deadline/reference shapes parse into optional WindowCheckpoint. |
| invariants | Reject active-command representation by format design: no active fields exist. Full row uniqueness/reference totals/catalog/native-base set agreement are deferred to WindowController/DeltaRuntime restore. matching_work nonzero required here; not spent matching in codec. FIFO remains one byte: values 0/1 keep their old bytes/meaning; 2/3 preserve physical lifetime scope and count IDs. Older readers reject 2/3; values above 3 reject. The field layout is unchanged. Admit the appended unrestricted enum value without changing old policy meanings. |
| ownership | Validation uses reread offsets without dynamic set. Materialization creates receiving-account managed tables/options/count/label arrays and owning rows; no FIFO/expiration directory is serialized. |
| failure | Structural/limit/work/error or private materialization allocation drops decoded candidate; no existing runtime/source or durable file changes. |
| cost | O(M^2) fixed-ID duplicate checks plus all row bytes; owned materialization preserves explicit managed capacity and allocates O(counts+labels+row payload). |
| Design | [docs/checkpoints.md](../../../../checkpoints.md), [include/crown/recovery/session_image.hpp](../../../../../include/crown/recovery/session_image.hpp), [include/crown/runtime/session_checkpoint.hpp](../../../../../include/crown/runtime/session_checkpoint.hpp), [src/runtime/window.cpp](../../../../../src/runtime/window.cpp), [docs/update_patterns.md](../../../../update_patterns.md) |

## B0037

[Lines 284–284](../../../../../src/recovery/session_image.cpp#L284); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L284-L284:sha256:aa1d1a63390229c798347e83a0405441c9400035284ad168c1bf6cdf1d70a370
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Closes the enclosing helper type at this source boundary; this is a lexical delimiter, not an operation. |
| inputs / outputs | No runtime input or output. Declarations following the span leave the preceding C++ scope. |
| invariants | The delimiter ends the preceding scope's visibility/linkage region; it adds no validation, publication, ownership transfer, or runtime authority. |
| ownership | The delimiter adds no owner. If it ends a function/block with live automatic objects, their normal destructors release those objects; namespace and type-definition closes change no existing object's lifetime. |
| failure | No explicit failure translation or catch is added. If a function/block exit destroys automatic objects, exception behavior follows those destructors; namespace/type closes have no runtime failure path. |
| cost | The delimiter adds no algorithmic work. A function/block exit can run existing automatic-object destructors and cleanup; namespace/type closes have no runtime cost. |
| Design | [src/recovery/session_image.cpp](../../../../../src/recovery/session_image.cpp), [docs/code_specs/files/src/recovery/session_image.cpp.md](session_image.cpp.md), [docs/checkpoints.md](../../../../checkpoints.md), [docs/session_lifecycle.md](../../../../session_lifecycle.md) |

## B0038

[Lines 285–345](../../../../../src/recovery/session_image.cpp#L285); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
InspectedSessionImage read(Input& in) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Validate or materialize all session envelope body fields under one parser. |
| inputs / outputs | Reads state/version/source kind/progress,26 Delta policy words+memory cap, snapshot/workload/input/source/CSV/window, then exact bounded nested runtime blob; returns manifest/Delta options. Dispatch versions 1/2 and inspect/materialize the optional declaration extension before runtime-image bytes. |
| invariants | Source tag must match stopped/stream/typed shape; sequence/EOF/closure/initial state and canonical typed options checked. Inspection also inspects nested runtime image and requires epoch/policy equality. Materialization trusts validated unchanged bytes, borrows runtime blob and leaves full native/program/source/window semantic matching to restore_funded. Inspection binds no allocator for pattern scratch; materialization funds scratch/import from the receiving account. Native program/window admission is still required. |
| ownership | Validation result=null owns no dynamic graph. Materialization fills only private receiver-account state; nested blob is not copied. |
| failure | All Reader/enum/policy/checksum/structural/source/window/processing/account failures propagate; caller owns cleanup. No catch, filesystem mutation or partially exposed session. |
| cost | O(serialized bytes) plus O(CSV fields^2+managed tables^2) reread uniqueness, nested image inspection in validation and receiver native allocations in materialization. Version 2 adds O(R) bounded parse work and funded O(R) decoder scratch plus declaration construction; inspection itself allocates no pattern storage. |
| Design | [docs/checkpoints.md](../../../../checkpoints.md), [include/crown/recovery/session_image.hpp](../../../../../include/crown/recovery/session_image.hpp), [include/crown/runtime/session_checkpoint.hpp](../../../../../include/crown/runtime/session_checkpoint.hpp), [src/runtime/session.cpp](../../../../../src/runtime/session.cpp), [src/recovery/image.cpp](../../../../../src/recovery/image.cpp), [docs/update_patterns.md](../../../../update_patterns.md) |

```text
const auto blob=in.take(in.size(in.state_limits.image.bytes));require(in.position==in.input.size());
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Separate validated nested runtime bytes from receiving session metadata materialization. |
| inputs / outputs | Final bounded blob consumes exact remaining body. Inspection calls inspect_image and checks nested epoch/policy; materialization stores borrowed blob view for later DeltaRuntime restore. |
| invariants | No copied runtime blob or claim that structural envelope validation alone establishes matching native base/window/program semantics. |
| ownership | Blob borrows original immutable envelope through restore_funded; native metadata/rows already materialized own their account. |
| failure | Trailing/inner checksum/binding/limit failure rejects validation before output graph; later native admission failure unwinds private receivers. |
| cost | Inspection scans nested component under its limits; materialization uses constant subview instead of duplicate blob allocation. |
| Design | [docs/checkpoints.md](../../../../checkpoints.md), [include/crown/recovery/session_image.hpp](../../../../../include/crown/recovery/session_image.hpp), [include/crown/runtime/session_checkpoint.hpp](../../../../../include/crown/runtime/session_checkpoint.hpp), [src/runtime/session.cpp](../../../../../src/runtime/session.cpp) |

## B0039

[Lines 346–347](../../../../../src/recovery/session_image.cpp#L346); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L346-L347:sha256:c929980d95efc152dc886ac42af0f045075441dd18a8f886364828ead327bbd3
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Closes the anonymous namespace at this source boundary; this is a lexical delimiter, not an operation. |
| inputs / outputs | No runtime input or output. Declarations following the span leave the preceding C++ scope. |
| invariants | The delimiter ends the preceding scope's visibility/linkage region; it adds no validation, publication, ownership transfer, or runtime authority. |
| ownership | The delimiter adds no owner. If it ends a function/block with live automatic objects, their normal destructors release those objects; namespace and type-definition closes change no existing object's lifetime. |
| failure | No explicit failure translation or catch is added. If a function/block exit destroys automatic objects, exception behavior follows those destructors; namespace/type closes have no runtime failure path. |
| cost | The delimiter adds no algorithmic work. A function/block exit can run existing automatic-object destructors and cleanup; namespace/type closes have no runtime cost. |
| Design | [src/recovery/session_image.cpp](../../../../../src/recovery/session_image.cpp), [docs/code_specs/files/src/recovery/session_image.cpp.md](session_image.cpp.md), [docs/checkpoints.md](../../../../checkpoints.md), [docs/session_lifecycle.md](../../../../session_lifecycle.md) |

## B0040

[Lines 348–368](../../../../../src/recovery/session_image.cpp#L348); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
SessionImage encode_session_image(const resource::MemoryAccount& account,const SessionCheckpoint& state,
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Encode a complete owning CROWNSI1 envelope after conservative sizing/work preflight. |
| inputs / outputs | Receiver account, native SessionCheckpoint and limits inspect nested runtime bytes/epoch/policy; preflight write, reserve both write visits+payload checksum work, allocate one final byte vector, materialize, patch payload length/hash and descriptive manifest. |
| invariants | Public codec can receive a constructed SessionCheckpoint, not only session-captured state. Structural/epoch/policy checks here do not replace full program/schema/source/window admission. Existing set image format unchanged; no W06/nullable/aggregate transaction state added. |
| ownership | Final ImageVector&lt;char&gt; uses explicit receiving account; original state/native bytes borrowed for call only. Local sizing/materialization metadata do not clone the runtime graph. |
| failure | Nested structure/binding/byte/work/row/cap/source/window or allocation failure drops private image and preserves caller state. No public owning result before checksum/manifest complete. |
| cost | Nested image validation plus two complete envelope traversals and payload SHA, O(output bytes) final allocation/copy. Preflight reserves logical second-pass work; statistics are declared work, not literal CPU/allocation/RSS. |
| Design | [docs/checkpoints.md](../../../../checkpoints.md), [include/crown/recovery/session_image.hpp](../../../../../include/crown/recovery/session_image.hpp), [include/crown/runtime/session_checkpoint.hpp](../../../../../include/crown/runtime/session_checkpoint.hpp), [tests/unit/session_image_test.cpp](../../../../../tests/unit/session_image_test.cpp) |

```text
const auto size=preflight.size;require(size<=SIZE_MAX,ImageFault::limit);budget.charge(budget.used-before);budget.charge(size-session_image_header_size);
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Reserve second serialization and checksum work before final image allocation. |
| inputs / outputs | Sizing pass yields bounded size; envelope budget admits another full write-work amount and payload SHA bytes before image.reserve. |
| invariants | Materialization uses same write traversal and fresh local budget under already conservatively reserved total. Logical reserved units need not equal literal CPU work. |
| ownership | No byte-vector allocation until this full preflight passes; final buffer belongs to receiver account. |
| failure | Byte/work/size rejection leaves caller state unchanged and allocates no final image. |
| cost | Constant debit arithmetic after first O(image bytes) pass; next pass+SHA costs remain explicit. |
| Design | [docs/checkpoints.md](../../../../checkpoints.md), [include/crown/recovery/session_image.hpp](../../../../../include/crown/recovery/session_image.hpp), [include/crown/runtime/session_checkpoint.hpp](../../../../../include/crown/runtime/session_checkpoint.hpp) |

## B0041

[Lines 369–380](../../../../../src/recovery/session_image.cpp#L369); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
detail::ValidatedSessionImage detail::validate_session_image(std::string_view bytes,const SessionCheckpointLimits& native,SessionImageLimits limits) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Validate the complete envelope and nested native component before receiving-account materialization. |
| inputs / outputs | Bounded bytes verify magic/version/flags/body length/lowercase checksum and actual payload SHA, parse all body fields with result=null, reserve second body-pass work and return ValidatedSessionImage. |
| invariants | No decoded heap graph is created. Returned token/manifest is private descriptive validated syntax, not live-session/durable authority. Input bytes must remain alive and byte-identical through materialization/native restore; semantic program/source/window matching remains required. |
| ownership | Token borrows original bytes and copies limits/manifest/options. Uses an empty account because validation branches cannot allocate account-backed output. |
| failure | Fixed ImageFailure on checksum/structure/binding/limits/truncation; no catch/repair or partial owner. |
| cost | O(envelope+inner bytes) hashes/parses plus quadratic fixed-ID/CSV uniqueness; conservative byte-work reserves validation/materialization/nested inspection, independently of native matching/build grants. |
| Design | [docs/checkpoints.md](../../../../checkpoints.md), [include/crown/recovery/session_image.hpp](../../../../../include/crown/recovery/session_image.hpp), [include/crown/runtime/session_checkpoint.hpp](../../../../../include/crown/runtime/session_checkpoint.hpp), [src/recovery/session_image_detail.hpp](../../../../../src/recovery/session_image_detail.hpp), [src/runtime/session.cpp](../../../../../src/runtime/session.cpp) |

```text
Input reader{{bytes.substr(session_image_header_size),budget},native,limits,none,nullptr};auto info=read(reader);
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Run structural inspection without constructing any account-owned decoded graph. |
| inputs / outputs | Empty account and result=null select validation-only parsing; after read, reserve second-body-pass work before returning borrowed validation token. |
| invariants | Native row strings may be raw bytes; metadata names obey UTF-8. Schema/catalog/reference/native-base matching remains subsequent session admission. |
| ownership | Only fixed parser/manifest/options state and borrowed image views; no ordinary or account-backed metadata mirror. |
| failure | All malformed/limited/checksum-valid-but-structurally-invalid data reject before receiving account graph allocation. |
| cost | Full body parse/hash/uniqueness work; no materialization heap, not constant time. |
| Design | [docs/checkpoints.md](../../../../checkpoints.md), [include/crown/recovery/session_image.hpp](../../../../../include/crown/recovery/session_image.hpp), [include/crown/runtime/session_checkpoint.hpp](../../../../../include/crown/runtime/session_checkpoint.hpp), [tests/unit/session_image_test.cpp](../../../../../tests/unit/session_image_test.cpp) |

## B0042

[Lines 381–383](../../../../../src/recovery/session_image.cpp#L381); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
InspectedSessionImage inspect_session_image(std::string_view bytes,const SessionCheckpointLimits& native,SessionImageLimits limits) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Expose allocation-free descriptive inspection through the single validator. |
| inputs / outputs | Bytes/native limits/envelope limits call validate_session_image and return only InspectedSessionImage. |
| invariants | Inspection grants no native session, fd, root selection or retirement authority. Borrowed validation token is discarded on return. |
| ownership | Returned manifest/options/statistics are fixed value copies; no input view remains in public result. |
| failure | Validation errors propagate fixed ImageFailure; no fallback/implicit conversion. |
| cost | Constant forwarding plus full validator scan/hash/uniqueness costs; zero output-graph allocation. |
| Design | [docs/checkpoints.md](../../../../checkpoints.md), [include/crown/recovery/session_image.hpp](../../../../../include/crown/recovery/session_image.hpp), [include/crown/runtime/session_checkpoint.hpp](../../../../../include/crown/runtime/session_checkpoint.hpp), [tests/unit/session_image_test.cpp](../../../../../tests/unit/session_image_test.cpp) |

## B0043

[Lines 384–390](../../../../../src/recovery/session_image.cpp#L384); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
detail::DecodedSessionImage detail::materialize_session_image(const resource::MemoryAccount& account,const ValidatedSessionImage& validated) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Materialize a private decoded session graph on the actual receiving account. |
| inputs / outputs | Authentic prior ValidatedSessionImage with unchanged immutable bytes/limits reparses body with result pointer and explicit account; stores inspected native manifest and returns DecodedSessionImage. |
| invariants | Does not redo outer checksum or nested image inspection in this phase; prior validation/byte lifetime precondition is mandatory. Does not instantiate a running session or validate catalog/base/window consistency. |
| ownership | Options/progress/window rows/arrays own receiver-account bytes. runtime_bytes borrows original input until immediate native restore; no duplicate runtime-image byte buffer. |
| failure | Account/resource/structural failure destroys private decoded graph. Existing source/session/disk unchanged; publication occurs only in later restore_funded. |
| cost | Second envelope parse plus native option/position/window row allocations/copies; no whole runtime blob copy. |
| Design | [docs/checkpoints.md](../../../../checkpoints.md), [include/crown/recovery/session_image.hpp](../../../../../include/crown/recovery/session_image.hpp), [include/crown/runtime/session_checkpoint.hpp](../../../../../include/crown/runtime/session_checkpoint.hpp), [src/recovery/session_image_detail.hpp](../../../../../src/recovery/session_image_detail.hpp), [src/runtime/session.cpp](../../../../../src/runtime/session.cpp) |

## B0044

[Lines 391–391](../../../../../src/recovery/session_image.cpp#L391); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L391-L391:sha256:95bcfbb6661a8958a33a82a5dc501f63202f4524486b8395aa4ce785f3c26b07
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Closes the namespace crown::recovery at this source boundary; this is a lexical delimiter, not an operation. |
| inputs / outputs | No runtime input or output. Declarations following the span leave the preceding C++ scope. |
| invariants | The delimiter ends the preceding scope's visibility/linkage region; it adds no validation, publication, ownership transfer, or runtime authority. |
| ownership | The delimiter adds no owner. If it ends a function/block with live automatic objects, their normal destructors release those objects; namespace and type-definition closes change no existing object's lifetime. |
| failure | No explicit failure translation or catch is added. If a function/block exit destroys automatic objects, exception behavior follows those destructors; namespace/type closes have no runtime failure path. |
| cost | The delimiter adds no algorithmic work. A function/block exit can run existing automatic-object destructors and cleanup; namespace/type closes have no runtime cost. |
| Design | [src/recovery/session_image.cpp](../../../../../src/recovery/session_image.cpp), [docs/code_specs/files/src/recovery/session_image.cpp.md](session_image.cpp.md), [docs/checkpoints.md](../../../../checkpoints.md), [docs/session_lifecycle.md](../../../../session_lifecycle.md) |
