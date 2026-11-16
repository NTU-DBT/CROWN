# `src/recovery/journal.cpp` — block usage map

[Source](../../../../../src/recovery/journal.cpp) · [Source index](../../../README.md) · [Subsystem contracts](../../../subsystem_contracts.md) · [Reviewed primitives](../../../primitives.md)

Encode, validate and publish checkpoints, journals, generations and local delivery receipts with explicit durable authority.

Snapshot SHA-256: `3d405643ff32c643aa57d82d6dc290824dbb85732c4339de869f83561b679809`. 321 lines partitioned into 43 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [recovery](../../../subsystem_contracts.md#recovery). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/checkpoints.md](../../../../checkpoints.md), [docs/journal.md](../../../../journal.md), [docs/journal-files.md](../../../../journal-files.md), [docs/generations.md](../../../../generations.md), [docs/local-sink.md](../../../../local-sink.md), [docs/history-retirement.md](../../../../history-retirement.md), [docs/update_patterns.md](../../../../update_patterns.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–11](../../../../../src/recovery/journal.cpp#L1) | Imports dependencies; declares namespace scope; declares aliases; declares values/defaults or compile-time conditions. |  · [reviewed contract](#b0001) |
| [B0002 · 12–22](../../../../../src/recovery/journal.cpp#L12) | Callable definition: bool utf8(std::string_view value) | calls size; returns false; false; 2 loop sites · [reviewed contract](#b0002) |
| [B0003 · 23–23](../../../../../src/recovery/journal.cpp#L23) | Callable definition: void source_name(std::string_view value) | calls require, empty, utf8; guard void source_name(std::string_view value) {require(!value.empty() && utf8(value));} · [reviewed contract](#b0003) |
| [B0004 · 24–30](../../../../../src/recovery/journal.cpp#L24) | Callable definition: void valid_header(const Header& value) | calls require, hex, runtime::detail::checkpoint_options; guard require(hex(value.query_id) && value.generation&gt;0 && hex(value.binding.physical_sha256) && hex(valu… · [reviewed contract](#b0004) |
| [B0005 · 31–33](../../../../../src/recovery/journal.cpp#L31) | declares types or opens a type body; declares values/defaults or compile-time conditions. | source comment (unverified): // A null output validates/counts; both encode passes borrow the same payload. · [reviewed contract](#b0005) |
| [B0006 · 34–34](../../../../../src/recovery/journal.cpp#L34) | Callable definition: void hash(std::span&lt;const char&gt; value) | calls require, hex, put, data; guard void hash(std::span&lt;const char&gt; value){require(hex(value),ImageFault::binding);put({value.data(),va… · [reviewed contract](#b0006) |
| [B0007 · 35–38](../../../../../src/recovery/journal.cpp#L35) | Callable definition: void row(storage::TupleValuesView value) | calls require, size, integer, scalar; guard budget.row();require(value.size()&lt;=limits.record.fields,ImageFault::limit);integer(value.size(),8);; 1 loop sites · [reviewed contract](#b0007) |
| [B0008 · 39–43](../../../../../src/recovery/journal.cpp#L39) | Callable definition: void write(const Header& value) | calls valid_header, hash, integer; 1 loop sites · [reviewed contract](#b0008) |
| [B0009 · 44–80](../../../../../src/recovery/journal.cpp#L44) | Callable definition: void write(const InputView& value) | calls integer, index, std::visit, constexpr; guard sequence=item.update.sequence;require(sequence&gt;0);integer(sequence,8);; 2 loop sites · [reviewed contract](#b0009) |
| [B0010 · 81–85](../../../../../src/recovery/journal.cpp#L81) | Callable definition: void write(const Commit& value) | calls require, integer, hash; guard require(value.input_ordinal&gt;0 && static_cast&lt;unsigned&gt;(value.kind)&lt;=1); · [reviewed contract](#b0010) |
| [B0011 · 86–86](../../../../../src/recovery/journal.cpp#L86) | Callable definition: void write(const Checkpoint& value) | calls integer, hash · [reviewed contract](#b0011) |
| [B0012 · 87–92](../../../../../src/recovery/journal.cpp#L87) | Callable definition: void frame(std::uint64_t ordinal,const PayloadView& value) | calls require, index, put, integer; guard require((value.index()==0)==(ordinal==0)); · [reviewed contract](#b0012) |
| [B0013 · 93–97](../../../../../src/recovery/journal.cpp#L93) | declares types or opens a type body; declares values/defaults or compile-time conditions. |  · [reviewed contract](#b0013) |
| [B0014 · 98–98](../../../../../src/recovery/journal.cpp#L98) | Callable definition: bool boolean() | calls integer, require; guard bool boolean(){const auto value=integer(1);require(value&lt;=1);return value!=0;}; returns value!=0 · [reviewed contract](#b0014) |
| [B0015 · 99–101](../../../../../src/recovery/journal.cpp#L99) | Callable definition: template&lt;std::size_t N&gt; std::array&lt;char,N&gt; hash() | calls take, std::copy, begin, end; guard std::array&lt;char,N&gt; value{};const auto text=take(N);std::copy(text.begin(),text.end(),value.begin())…; returns value · [reviewed contract](#b0015) |
| [B0016 · 102–102](../../../../../src/recovery/journal.cpp#L102) | Explanatory comments or spacing. | source comment (unverified): // Inspect keeps scalar views transient; decode copies them into a funded row. · [reviewed contract](#b0016) |
| [B0017 · 103–109](../../../../../src/recovery/journal.cpp#L103) | Callable definition: void row(InputMetadata& metadata) | calls size, require, reserve, binary_detail::scalar; guard budget.row();const auto fields=size(limits.record.fields);require(fields&lt;=input.size()-position);me…; growth copy_of, push_back, reserve; 1 loop sites; source comment (unverified): // Inspect keeps scalar views transient; decode copies them into a funded row. · [reviewed contract](#b0017) |
| [B0018 · 110–115](../../../../../src/recovery/journal.cpp#L110) | Callable definition: Header header() | calls integer, require, valid_header; guard value.binding.catalog_version=integer(8);require(integer(2)==1,ImageFault::version);for(auto& word:…; returns value; 1 loop sites · [reviewed contract](#b0018) |
| [B0019 · 116–148](../../../../../src/recovery/journal.cpp#L116) | Callable definition: InputMetadata item() | calls integer, require, size, row; guard InputMetadata value;const auto tag=integer(1);require(tag&lt;=1);value.window=tag!=0;value.sequence=in…; returns value; growth push_back, reserve; 3 loop sites · [reviewed contract](#b0019) |
| [B0020 · 149–162](../../../../../src/recovery/journal.cpp#L149) | Callable definition: Inspected read() | calls integer, require, header, item; guard Inspected value;const auto kind=integer(1);require(kind&lt;=3);value.kind=static_cast&lt;Kind&gt;(kind);valu…; returns value · [reviewed contract](#b0020) |
| [B0021 · 163–164](../../../../../src/recovery/journal.cpp#L163) | Closes surrounding scope/type. | source comment (unverified): // Admit both structural passes and checksums before final-buffer allocation. · [reviewed contract](#b0021) |
| [B0022 · 165–173](../../../../../src/recovery/journal.cpp#L165) | Callable definition: Encoded encode_impl(const resource::MemoryAccount& account,std::uint64_t ordinal,const PayloadView& value,Limits limits) | calls frame, require, charge, reserve; guard const auto size=preflight.size,visits=budget.used;require(size&lt;=SIZE_MAX,ImageFault::limit);budget.…; returns result; growth reserve; 1 loop sites; source comment (unverified): // Admit both structural passes and checksums before final-buffer allocation. · [reviewed contract](#b0022) |
| [B0023 · 174–183](../../../../../src/recovery/journal.cpp#L174) | Callable definition: Inspected inspect_impl(std::string_view bytes,Limits limits) | calls require, size, take, integer; guard require(bytes.size()&lt;=limits.record.bytes,ImageFault::limit);Budget budget{limits.record};Reader fr…; returns value · [reviewed contract](#b0023) |
| [B0024 · 184–187](../../../../../src/recovery/journal.cpp#L184) | Callable definition: Decoded decode_impl(const resource::MemoryAccount& account,std::string_view bytes,Limits limits) | calls inspect_impl, substr, read; returns result · [reviewed contract](#b0024) |
| [B0025 · 188–189](../../../../../src/recovery/journal.cpp#L188) | Explanatory comments or spacing. | source comment (unverified): // Structural continuity only; pending.frame borrows caller bytes. · [reviewed contract](#b0025) |
| [B0026 · 190–250](../../../../../src/recovery/journal.cpp#L190) | Callable definition: bool next_record(Scanned& result,std::string_view tail,const ScanLimits& limits,const Header* expected,bool allow_torn) | calls require, size, charge, std::min; guard require(result.consumed&lt;=limits.bytes && tail.size()&lt;=limits.bytes-result.consumed && limits.record…; returns false; true; 1 loop sites; source comment (unverified): // Structural continuity only; pending.frame borrows caller bytes. · [reviewed contract](#b0026) |
| [B0027 · 251–256](../../../../../src/recovery/journal.cpp#L251) | Callable definition: Scanned scan_impl(std::string_view bytes,ScanLimits limits,const Header* expected) | calls require, size, next_record, substr; guard require(bytes.size()&lt;=limits.bytes && limits.record.record.bytes&gt;=frame_header_size+9,ImageFault::l…; returns result; result; 1 loop sites · [reviewed contract](#b0027) |
| [B0028 · 257–261](../../../../../src/recovery/journal.cpp#L257) | Callable definition: Scanned advance_impl(const Scanned& before,std::string_view frame,ScanLimits limits,const Header* expected) | calls require, next_record, size; guard require(next_record(result,frame,limits,expected,false) && result.consumed-before.consumed==frame.s…; returns result · [reviewed contract](#b0028) |
| [B0029 · 262–264](../../../../../src/recovery/journal.cpp#L262) | Callable definition: template&lt;class Action&gt; auto guarded(Action&& action) | calls action, Failure, fault; returns action() · [reviewed contract](#b0029) |
| [B0030 · 265–265](../../../../../src/recovery/journal.cpp#L265) | Closes surrounding scope/type. | source comment (unverified): // namespace · [reviewed contract](#b0030) |
| [B0031 · 266–268](../../../../../src/recovery/journal.cpp#L266) | Callable definition: Encoded encode(const resource::MemoryAccount& account,std::uint64_t ordinal,const PayloadView& value,Limits limits) | calls guarded, encode_impl; returns guarded(\[&\]{return encode_impl(account,ordinal,value,limits) · [reviewed contract](#b0031) |
| [B0032 · 269–269](../../../../../src/recovery/journal.cpp#L269) | Callable definition: Inspected inspect(std::string_view bytes,Limits limits) | calls guarded, inspect_impl; returns guarded(\[&\]{return inspect_impl(bytes,limits) · [reviewed contract](#b0032) |
| [B0033 · 270–272](../../../../../src/recovery/journal.cpp#L270) | Callable definition: Decoded decode(const resource::MemoryAccount& account,std::string_view bytes,Limits limits) | calls guarded, decode_impl; returns guarded(\[&\]{return decode_impl(account,bytes,limits) · [reviewed contract](#b0033) |
| [B0034 · 273–273](../../../../../src/recovery/journal.cpp#L273) | Callable definition: Scanned scan(std::string_view bytes,ScanLimits limits,const Header* expected) | calls guarded, scan_impl; returns guarded(\[&\]{return scan_impl(bytes,limits,expected) · [reviewed contract](#b0034) |
| [B0035 · 274–274](../../../../../src/recovery/journal.cpp#L274) | Callable definition: Cursor::Cursor(ScanLimits limits,const Header* expected):limits_(limits),expected_(expected?std::optional&lt;Header&gt;{*expected}:std:… | calls limits_, expected_ · [reviewed contract](#b0035) |
| [B0036 · 275–276](../../../../../src/recovery/journal.cpp#L275) | Callable definition: Cursor::Cursor(Cursor&& other) noexcept :limits_(other.limits_),expected_(other.expected_),state_(other.state_),active_(other.act… | calls limits_, expected_, state_, active_ · [reviewed contract](#b0036) |
| [B0037 · 277–280](../../../../../src/recovery/journal.cpp#L277) | Callable definition: Cursor& Cursor::operator=(Cursor&& other) noexcept | returns *this · [reviewed contract](#b0037) |
| [B0038 · 281–281](../../../../../src/recovery/journal.cpp#L281) | Explanatory comments or spacing. | source comment (unverified): // Publish the copied continuation only after one complete frame validates. · [reviewed contract](#b0038) |
| [B0039 · 282–286](../../../../../src/recovery/journal.cpp#L282) | Callable definition: Scanned Cursor::feed(std::string_view frame) & | calls Failure, guarded, advance_impl, std::move; returns advance_impl(state_,frame,limits_,expected_?&*expected_:nullptr); state_; source comment (unverified): // Publish the copied continuation only after one complete frame validates. · [reviewed contract](#b0039) |
| [B0040 · 287–294](../../../../../src/recovery/journal.cpp#L287) | Callable definition: Scanned Cursor::finish_tail(std::string_view tail) & | calls Failure, empty, guarded, next_record; returns state_; next_record(next,tail,limits_,expected_?&*expected_:nullptr,true) · [reviewed contract](#b0040) |
| [B0041 · 295–295](../../../../../src/recovery/journal.cpp#L295) | Explanatory comments or spacing. | source comment (unverified): // Returned views borrow Decoded storage; native admission checks actual policy. · [reviewed contract](#b0041) |
| [B0042 · 296–320](../../../../../src/recovery/journal.cpp#L296) | Callable definition: InputView Decoded::input_view() const & | calls size, empty, Failure, source_name; returns result; source comment (unverified): // Returned views borrow Decoded storage; native admission checks actual policy. · [reviewed contract](#b0042) |
| [B0043 · 321–321](../../../../../src/recovery/journal.cpp#L321) | Closes surrounding scope/type. | source comment (unverified): // namespace crown::recovery::journal · [reviewed contract](#b0043) |

## B0001

[Lines 1–11](../../../../../src/recovery/journal.cpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
constexpr std::string_view magic="CROWNWAL";
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Bind the journal implementation to the version-1 protected record format and shared bounded scalar codec. |
| inputs / outputs | Local CROWNWAL signature is consumed by frame encoding, inspection and prefix checks; no public result or executable initialization. |
| invariants | Journal records use their own format; shared binary helpers and policy decoding do not supply query admission, native transition proof or persistence. |
| ownership | Borrows immutable input synchronously; changes only private codec preparation. Returned fixed metadata owns its fields. No filesystem or native query state changes. |
| failure | ImageFailure propagates with its fixed diagnostic; public journal wrappers translate that type only. MemoryFailure/bad_alloc propagate unchanged; private preparation is released and no result is published. |
| cost | Fixed static string_view plus compile-time declarations; no dynamic allocation or I/O. |
| Design | [include/crown/recovery/journal.hpp](../../../../../include/crown/recovery/journal.hpp), [docs/journal.md §Format 1](../../../../journal.md), [src/runtime/checkpoint_policy.hpp](../../../../../src/runtime/checkpoint_policy.hpp), [include/crown/recovery/image.hpp](../../../../../include/crown/recovery/image.hpp) |

## B0002

[Lines 12–22](../../../../../src/recovery/journal.cpp#L12); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
bool utf8(std::string_view value)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Validate the stricter source-name byte domain. |
| inputs / outputs | Returns whether all bytes form shortest-form UTF8 with valid Unicode scalar values and no NUL; empty input returns true here. |
| invariants | Checks continuation lengths, overlong encodings, surrogate range and Unicode maximum. Nonemptiness belongs to source_name, while row strings use raw-byte scalar encoding. |
| ownership | Borrows immutable input synchronously; changes only private codec preparation. Returned fixed metadata owns its fields. No filesystem or native query state changes. |
| failure | Returns false for malformed or NUL-containing bytes; performs no exception construction. |
| cost | O(name bytes) byte visits, constant stack and no allocation; caller precharges source-validation visits. |
| Design | [include/crown/recovery/journal.hpp](../../../../../include/crown/recovery/journal.hpp), [docs/journal.md §Format 1](../../../../journal.md) |

## B0003

[Lines 23–23](../../../../../src/recovery/journal.cpp#L23); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void source_name(std::string_view value)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Require a usable optional source identity. |
| inputs / outputs | Nonempty strict UTF8/nonNUL name returns; otherwise calls the shared corrupt predicate. |
| invariants | Only validates name syntax. Does not compare source history, offset monotonicity, stream contents or native source policy. |
| ownership | Borrows immutable input synchronously; changes only private codec preparation. Returned fixed metadata owns its fields. No filesystem or native query state changes. |
| failure | ImageFailure propagates with its fixed diagnostic; public journal wrappers translate that type only. MemoryFailure/bad_alloc propagate unchanged; private preparation is released and no result is published. |
| cost | O(name bytes), no allocation; name-size and validation-work charges belong to input encode/decode callers. |
| Design | [include/crown/recovery/journal.hpp](../../../../../include/crown/recovery/journal.hpp), [docs/journal.md §Format 1](../../../../journal.md) |

## B0004

[Lines 24–30](../../../../../src/recovery/journal.cpp#L24); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void valid_header(const Header& value)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Validate the journal header projection before writing or accepting it. |
| inputs / outputs | Checks query/checkpoint/program/source hexadecimal fields, generation/catalog, input-kind range, sequence relation and all 26 policy words. |
| invariants | Nonwindow physical/command bases must agree. Valid hashes and policy encodings establish structural binding data, not a match to an actual compiled/native session. |
| ownership | Borrows immutable input synchronously; changes only private codec preparation. Returned fixed metadata owns its fields. No filesystem or native query state changes. |
| failure | ImageFailure propagates with its fixed diagnostic; public journal wrappers translate that type only. MemoryFailure/bad_alloc propagate unchanged; private preparation is released and no result is published. |
| cost | Fixed-size hash scans and 26-word options decoding; stack DeltaOptions, no account allocation or filesystem access. |
| Design | [include/crown/recovery/journal.hpp](../../../../../include/crown/recovery/journal.hpp), [docs/journal.md §Format 1](../../../../journal.md), [src/runtime/checkpoint_policy.hpp](../../../../../src/runtime/checkpoint_policy.hpp), [include/crown/recovery/image.hpp](../../../../../include/crown/recovery/image.hpp) |

## B0005

[Lines 31–33](../../../../../src/recovery/journal.cpp#L31); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct Output:Writer {
  const Limits& limits;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Carry the shared writer state and the journal-specific limits through both sizing and materialization. |
| inputs / outputs | Base Writer borrows Budget and either a final byte vector or nullptr; this extension borrows journal Limits. |
| invariants | Null output still validates and counts every emitted byte. The same immutable payload and limits must be used in both passes. |
| ownership | References live only within encode_impl; output vector, if present, is owned by the Encoded preparation. |
| failure | Construction adds no handler or failure path; inherited operations enforce record/work limits. |
| cost | Constant-size adapter; actual row/scalar/name/CSV work is in its methods, with no independent allocation. |
| Design | [docs/journal.md §Resources and evidence](../../../../journal.md), [src/recovery/binary_detail.hpp](../../../../../src/recovery/binary_detail.hpp) |

## B0006

[Lines 34–34](../../../../../src/recovery/journal.cpp#L34); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void hash(std::span<const char> value)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Emit one fixed hexadecimal journal identity or digest. |
| inputs / outputs | A caller-provided fixed-size character span must be lowercase hexadecimal; appends/counts exactly its length. |
| invariants | All callers supply the declared 32/64-byte fields. This is a syntax check, not recomputation or authentication of that value. |
| ownership | Borrows immutable input synchronously; changes only private codec preparation. Returned fixed metadata owns its fields. No filesystem or native query state changes. |
| failure | ImageFailure propagates with its fixed diagnostic; public journal wrappers translate that type only. MemoryFailure/bad_alloc propagate unchanged; private preparation is released and no result is published. |
| cost | O(span length) hex validation and output/count visits; actual calls have fixed lengths. |
| Design | [include/crown/recovery/journal.hpp](../../../../../include/crown/recovery/journal.hpp), [docs/journal.md §Format 1](../../../../journal.md), [docs/journal.md §Resources and evidence](../../../../journal.md), [src/recovery/binary_detail.hpp](../../../../../src/recovery/binary_detail.hpp) |

## B0007

[Lines 35–38](../../../../../src/recovery/journal.cpp#L35); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void row(storage::TupleValuesView value)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Encode one physical or window-insert tuple. |
| inputs / outputs | Consumes a logical row unit, checks field limit, writes arity-u64 followed by exact tagged ScalarViews. |
| invariants | No table/schema/domain lookup; raw strings and already typed dates/inline decimals follow the shared scalar wire. Empty rows still consume one row unit. |
| ownership | Borrows immutable input synchronously; changes only private codec preparation. Returned fixed metadata owns its fields. No filesystem or native query state changes. |
| failure | ImageFailure propagates with its fixed diagnostic; public journal wrappers translate that type only. MemoryFailure/bad_alloc propagate unchanged; private preparation is released and no result is published. |
| cost | O(fields plus encoded scalar bytes); inline decimals render in fixed stack storage. Sizing allocates nothing; materialization writes the reserved final vector. |
| Design | [include/crown/recovery/journal.hpp](../../../../../include/crown/recovery/journal.hpp), [docs/journal.md §Format 1](../../../../journal.md), [docs/journal.md §Resources and evidence](../../../../journal.md), [src/recovery/binary_detail.hpp](../../../../../src/recovery/binary_detail.hpp) |

## B0008

[Lines 39–43](../../../../../src/recovery/journal.cpp#L39); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void write(const Header& value)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Encode all header fields in the fixed version-1 order. |
| inputs / outputs | Validated Header yields query/generation/binding, arithmetic version 1, 26 policy words, checkpoint and two sequence bases plus input tag. |
| invariants | Called within ordinal-zero frame; field checks preserve policy canonicality and nonwindow base equality. No live runtime options are changed. |
| ownership | Borrows immutable input synchronously; changes only private codec preparation. Returned fixed metadata owns its fields. No filesystem or native query state changes. |
| failure | ImageFailure propagates with its fixed diagnostic; public journal wrappers translate that type only. MemoryFailure/bad_alloc propagate unchanged; private preparation is released and no result is published. |
| cost | Fixed-size encoding and validation; runs once in preflight and once in materialization. |
| Design | [include/crown/recovery/journal.hpp](../../../../../include/crown/recovery/journal.hpp), [docs/journal.md §Format 1](../../../../journal.md), [src/runtime/checkpoint_policy.hpp](../../../../../src/runtime/checkpoint_policy.hpp), [include/crown/recovery/image.hpp](../../../../../include/crown/recovery/image.hpp) |

## B0009

[Lines 44–80](../../../../../src/recovery/journal.cpp#L44); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void write(const InputView& value)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Encode a borrowed input plus optional source and buffered-reader continuation. |
| inputs / outputs | Handles physical update or nonempty window insert/withdraw/watermark, positive sequence/labels, optional nonempty name/offset and physical reader metadata. |
| invariants | Reader records equal input sequence; absent CSV header implies empty permutation; each index is in-range and unique. Stream/window consistency across records belongs to scan, catalog/domain/source acceptance to the native caller. |
| ownership | All tuple/name/CSV spans borrow the caller for the complete synchronous encode; only the final Encoded buffer retains copied wire bytes. |
| failure | ImageFailure propagates with its fixed diagnostic; public journal wrappers translate that type only. MemoryFailure/bad_alloc propagate unchanged; private preparation is released and no result is published. |
| cost | O(encoded payload plus source validation plus F squared CSV comparisons); charges 8 per prior-index comparison before comparing. No retained DTO copy; two encode passes revisit the borrowed payload. |
| Design | [include/crown/recovery/journal.hpp](../../../../../include/crown/recovery/journal.hpp), [docs/journal.md §Format 1](../../../../journal.md), [docs/journal.md §Resources and evidence](../../../../journal.md), [src/recovery/binary_detail.hpp](../../../../../src/recovery/binary_detail.hpp) |

## B0010

[Lines 81–85](../../../../../src/recovery/journal.cpp#L81); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void write(const Commit& value)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Encode one input-bound decision marker. |
| inputs / outputs | Requires positive input ordinal and valid physical/metadata kind, then writes input body digest, physical/command sequences, substep and completion flag. |
| invariants | frame additionally requires input ordinal earlier than this record; matching pending input, sequence increments and window completion rules are enforced by scan/native replay. |
| ownership | Borrows immutable input synchronously; changes only private codec preparation. Returned fixed metadata owns its fields. No filesystem or native query state changes. |
| failure | ImageFailure propagates with its fixed diagnostic; public journal wrappers translate that type only. MemoryFailure/bad_alloc propagate unchanged; private preparation is released and no result is published. |
| cost | Fixed bytes, fixed digest scan and no independent allocation. |
| Design | [include/crown/recovery/journal.hpp](../../../../../include/crown/recovery/journal.hpp), [docs/journal.md §Format 1](../../../../journal.md) |

## B0011

[Lines 86–86](../../../../../src/recovery/journal.cpp#L86); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void write(const Checkpoint& value)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Encode one checkpoint marker projection. |
| inputs / outputs | Writes physical/command frontiers and a syntactically valid checkpoint digest. |
| invariants | No checkpoint file is read, selected or made durable. Pending-input/frontier continuity is enforced only when scanning the record in a prefix. |
| ownership | Borrows immutable input synchronously; changes only private codec preparation. Returned fixed metadata owns its fields. No filesystem or native query state changes. |
| failure | ImageFailure propagates with its fixed diagnostic; public journal wrappers translate that type only. MemoryFailure/bad_alloc propagate unchanged; private preparation is released and no result is published. |
| cost | Fixed-size writes/hash syntax scan; no I/O or allocation beyond the supplied final vector. |
| Design | [include/crown/recovery/journal.hpp](../../../../../include/crown/recovery/journal.hpp), [docs/journal.md §Format 1](../../../../journal.md) |

## B0012

[Lines 87–92](../../../../../src/recovery/journal.cpp#L87); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void frame(std::uint64_t ordinal,const PayloadView& value)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Build an entire record with reserved checksum fields. |
| inputs / outputs | Header iff ordinal zero; commit input ordinal must precede it. Writes signature/version/flags, placeholder size/hashes, kind/ordinal and matching payload. |
| invariants | Payload variant order is the version-1 kind encoding. Checksums and body length are filled only by encode_impl after complete materialization. |
| ownership | Borrows immutable input synchronously; changes only private codec preparation. Returned fixed metadata owns its fields. No filesystem or native query state changes. |
| failure | ImageFailure propagates with its fixed diagnostic; public journal wrappers translate that type only. MemoryFailure/bad_alloc propagate unchanged; private preparation is released and no result is published. |
| cost | O(encoded frame plus payload validation), repeated by sizing/materialization; fixed stack zero-hash array. |
| Design | [include/crown/recovery/journal.hpp](../../../../../include/crown/recovery/journal.hpp), [docs/journal.md §Format 1](../../../../journal.md), [docs/journal.md §Resources and evidence](../../../../journal.md), [src/recovery/binary_detail.hpp](../../../../../src/recovery/binary_detail.hpp) |

## B0013

[Lines 93–97](../../../../../src/recovery/journal.cpp#L93); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct Input:Reader {
  const Limits& limits;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Carry inspection or receiving-account decoding state through one complete body parse. |
| inputs / outputs | Base Reader borrows immutable body and Budget; extension borrows Limits and copies an account handle, with optional Decoded destination. |
| invariants | output==nullptr skips owning row/source/CSV construction while retaining all structural checks. A nonnull destination remains private until parse success. |
| ownership | Reader byte views cannot outlive the synchronous parse. Decoded receives deep-owned bytes; this parser object owns only its account handle. |
| failure | No local recovery handler; parse/resource/allocation failures unwind private owning storage. |
| cost | Constant-size adapter; optional row descriptor/native-row/source/CSV allocations are attributed to the receiving account. |
| Design | [docs/journal.md §Resources and evidence](../../../../journal.md), [src/recovery/binary_detail.hpp](../../../../../src/recovery/binary_detail.hpp) |

## B0014

[Lines 98–98](../../../../../src/recovery/journal.cpp#L98); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
bool boolean()
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Read a canonical wire boolean. |
| inputs / outputs | Consumes one byte; accepts only 0/1 and returns bool. |
| invariants | Rejects other encodings before treating them as source/reader/commit-completion presence. |
| ownership | Borrows immutable input synchronously; changes only private codec preparation. Returned fixed metadata owns its fields. No filesystem or native query state changes. |
| failure | ImageFailure propagates with its fixed diagnostic; public journal wrappers translate that type only. MemoryFailure/bad_alloc propagate unchanged; private preparation is released and no result is published. |
| cost | One bounded byte read and predicate, no allocation. |
| Design | [include/crown/recovery/journal.hpp](../../../../../include/crown/recovery/journal.hpp), [docs/journal.md §Format 1](../../../../journal.md) |

## B0015

[Lines 99–101](../../../../../src/recovery/journal.cpp#L99); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
template<std::size_t N> std::array<char,N> hash()
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Copy one fixed-width hexadecimal field from a journal body. |
| inputs / outputs | Reads N bytes into a stack std::array and validates lowercase hexadecimal; actual instantiations are 32 and 64. |
| invariants | Reader bounds and work admission precede access. A valid digest string is descriptive until compared/recomputed by its caller. |
| ownership | Borrows immutable input synchronously; changes only private codec preparation. Returned fixed metadata owns its fields. No filesystem or native query state changes. |
| failure | ImageFailure propagates with its fixed diagnostic; public journal wrappers translate that type only. MemoryFailure/bad_alloc propagate unchanged; private preparation is released and no result is published. |
| cost | O(N) read/copy/hex visits with fixed stack output; no heap allocation. |
| Design | [include/crown/recovery/journal.hpp](../../../../../include/crown/recovery/journal.hpp), [docs/journal.md §Format 1](../../../../journal.md), [docs/journal.md §Resources and evidence](../../../../journal.md), [src/recovery/binary_detail.hpp](../../../../../src/recovery/binary_detail.hpp) |

## B0016

[Lines 102–102](../../../../../src/recovery/journal.cpp#L102); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L102-L102:sha256:ecebeed22b6af87965cfe5eb6764c9c5b8b74a68fd0adba9d712f3be65bfd24e
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Design note for adjacent code: Inspect keeps scalar views transient; decode copies them into a funded row. This is caller guidance recorded as prose, not an executable result. |
| inputs / outputs | No runtime interface is implemented by these comment-only lines. They sit at src/recovery/journal.cpp lines 100-104; the surrounding declaration/body defines its own inputs and outputs. |
| invariants | The words record the intended use boundary only. They do not add a guard, proof, capability, transaction, durability guarantee, or account charge; verify behavior in the referenced implementation. |
| ownership | Comment text owns no data. Object lifetimes, borrows, and account attribution remain those of the adjacent source objects and their constructors. |
| failure | No failure path is implemented here. Any mentioned failure or recovery rule belongs to the adjacent operation and its existing error carrier. |
| cost | No runtime work is performed by these lines; any cost/bound in the note is not certified by this comment-only card. |
| Design | [src/recovery/journal.cpp](../../../../../src/recovery/journal.cpp), [docs/code_specs/files/src/recovery/journal.cpp.md](journal.cpp.md), [docs/journal.md](../../../../journal.md), [docs/journal-files.md](../../../../journal-files.md) |

## B0017

[Lines 103–109](../../../../../src/recovery/journal.cpp#L103); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void row(InputMetadata& metadata)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Inspect or materialize one native row without an ordinary Row/string shadow. |
| inputs / outputs | Reads bounded field count and scalar sequence into metadata; decoding reserves temporary ScalarViews then copies them into AccountedRow. |
| invariants | At least one remaining tag byte per field is required. Shared scalar reader checks tags, bool/date/decimal domains and scalar limits; table-specific arity/types remain native admission. |
| ownership | Scalar string views borrow input during parsing; AccountedRow::copy_of deep-copies descriptors/string bytes into receiving-account recovery attribution before returning. |
| failure | ImageFailure propagates with its fixed diagnostic; public journal wrappers translate that type only. MemoryFailure/bad_alloc propagate unchanged; private preparation is released and no result is published. |
| cost | O(fields plus scalar bytes), one temporary account descriptor vector and at most one owned combined row allocation when output is present. Temporary descriptors overlap the final native row; inspection allocates nothing. |
| Design | [include/crown/recovery/journal.hpp](../../../../../include/crown/recovery/journal.hpp), [docs/journal.md §Format 1](../../../../journal.md), [docs/journal.md §Resources and evidence](../../../../journal.md), [src/recovery/binary_detail.hpp](../../../../../src/recovery/binary_detail.hpp), [include/crown/storage/accounted_row.hpp](../../../../../include/crown/storage/accounted_row.hpp) |

## B0018

[Lines 110–115](../../../../../src/recovery/journal.cpp#L110); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Header header()
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Decode and validate the header body projection. |
| inputs / outputs | Copies fixed identities/digests, reads generation/catalog/policy/frontiers/input tag, then applies valid_header. |
| invariants | Arithmetic-policy version must be 1; all option words and input enum must be representable. No expected program/session is inferred from syntactic validity. |
| ownership | Borrows immutable input synchronously; changes only private codec preparation. Returned fixed metadata owns its fields. No filesystem or native query state changes. |
| failure | ImageFailure propagates with its fixed diagnostic; public journal wrappers translate that type only. MemoryFailure/bad_alloc propagate unchanged; private preparation is released and no result is published. |
| cost | Fixed-size read/copy/validation, no account allocation. |
| Design | [include/crown/recovery/journal.hpp](../../../../../include/crown/recovery/journal.hpp), [docs/journal.md §Format 1](../../../../journal.md), [src/runtime/checkpoint_policy.hpp](../../../../../src/runtime/checkpoint_policy.hpp), [include/crown/recovery/image.hpp](../../../../../include/crown/recovery/image.hpp) |

## B0019

[Lines 116–148](../../../../../src/recovery/journal.cpp#L116); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
InputMetadata item()
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Inspect or materialize one input record and reader continuation. |
| inputs / outputs | Reads physical/window tag, positive sequence, exact command fields, optional source and optional physical reader state; returns fixed InputMetadata. |
| invariants | Source bytes are limit-checked/precharged then UTF8/nonNUL-validated; CSV list is an in-range unique permutation and records equals input sequence. It does not verify CSV columns against an external catalog or consume the source. |
| ownership | Decoded source/CSV/native row use receiving-account allocators; all temporary text views borrow immutable input only during this call. |
| failure | ImageFailure propagates with its fixed diagnostic; public journal wrappers translate that type only. MemoryFailure/bad_alloc propagate unchanged; private preparation is released and no result is published. |
| cost | O(payload bytes plus F squared CSV duplicate checks), rereading 8 bytes for each previous index. Decode owns source vector/CSV vector and at most one row; inspect keeps no variable storage. |
| Design | [include/crown/recovery/journal.hpp](../../../../../include/crown/recovery/journal.hpp), [docs/journal.md §Format 1](../../../../journal.md), [docs/journal.md §Resources and evidence](../../../../journal.md), [src/recovery/binary_detail.hpp](../../../../../src/recovery/binary_detail.hpp) |

## B0020

[Lines 149–162](../../../../../src/recovery/journal.cpp#L149); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Inspected read()
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Dispatch and fully consume one journal record body. |
| inputs / outputs | Reads kind/ordinal and header/input/commit/checkpoint fields; returns Inspected only when no trailing bytes remain. |
| invariants | Kind 0 iff ordinal 0; commits reference positive earlier input ordinal and legal commit kind. This single-record parse does not establish contiguous history, active input linkage or native semantics. |
| ownership | Borrows immutable input synchronously; changes only private codec preparation. Returned fixed metadata owns its fields. No filesystem or native query state changes. |
| failure | ImageFailure propagates with its fixed diagnostic; public journal wrappers translate that type only. MemoryFailure/bad_alloc propagate unchanged; private preparation is released and no result is published. |
| cost | O(body structural read plus name/CSV/scalar checks), optional account materialization under the parser destination. Fixed-size Inspected return. |
| Design | [include/crown/recovery/journal.hpp](../../../../../include/crown/recovery/journal.hpp), [docs/journal.md §Format 1](../../../../journal.md), [docs/journal.md §Resources and evidence](../../../../journal.md), [src/recovery/binary_detail.hpp](../../../../../src/recovery/binary_detail.hpp) |

## B0021

[Lines 163–164](../../../../../src/recovery/journal.cpp#L163); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L163-L164:sha256:be814f3ca5353d2f6b7f9ec5d8afe320064bfeb50fb4ee024fd8196c7d0ef35f
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Closes the enclosing helper type at this source boundary; this is a lexical delimiter, not an operation. Trailing source note states: Admit both structural passes and checksums before final-buffer allocation. It remains prose guidance, not a certified executable claim. |
| inputs / outputs | No runtime input or output. Declarations following the span leave the preceding C++ scope. |
| invariants | The delimiter ends the preceding scope's visibility/linkage region; it adds no validation, publication, ownership transfer, or runtime authority. Any trailing comment in this block is guidance only and adds no runtime invariant. |
| ownership | The delimiter adds no owner. If it ends a function/block with live automatic objects, their normal destructors release those objects; namespace and type-definition closes change no existing object's lifetime. |
| failure | No explicit failure translation or catch is added. If a function/block exit destroys automatic objects, exception behavior follows those destructors; namespace/type closes have no runtime failure path. |
| cost | The delimiter adds no algorithmic work. A function/block exit can run existing automatic-object destructors and cleanup; namespace/type closes have no runtime cost. |
| Design | [src/recovery/journal.cpp](../../../../../src/recovery/journal.cpp), [docs/code_specs/files/src/recovery/journal.cpp.md](journal.cpp.md), [docs/journal.md](../../../../journal.md), [docs/journal-files.md](../../../../journal-files.md) |

## B0022

[Lines 165–173](../../../../../src/recovery/journal.cpp#L165); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Encoded encode_impl(const resource::MemoryAccount& account,std::uint64_t ordinal,const PayloadView& value,Limits limits)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Preflight, allocate and finish one complete protected journal record. |
| inputs / outputs | Receives account, ordinal, immutable PayloadView and copied Limits; returns owning Encoded with bytes and byte/work/row statistics. |
| invariants | Before allocation, reserves two structural traversals, body checksum and protected-prefix checksum in the work grant; final traversal size/work must equal preflight. Header is 148 bytes with 84-byte protected prefix. |
| ownership | Encoded retains receiving-account ImageVector bytes. Caller views stay immutable through both passes and are not retained. |
| failure | Invalid payload/work/byte limits reject during preflight before buffer allocation. Account allocation or invariant failure unwinds the private buffer; memory faults are not translated by guarded. |
| cost | Two full serialization/validation passes plus SHA256(body) and SHA256(first 84 bytes), including quadratic CSV comparisons in each pass. One reserved final ImageVector; no temporary full-frame mirror. |
| Design | [include/crown/recovery/journal.hpp](../../../../../include/crown/recovery/journal.hpp), [docs/journal.md §Format 1](../../../../journal.md), [docs/journal.md §Resources and evidence](../../../../journal.md), [src/recovery/binary_detail.hpp](../../../../../src/recovery/binary_detail.hpp), [include/crown/ir/digest.hpp](../../../../../include/crown/ir/digest.hpp) |

## B0023

[Lines 174–183](../../../../../src/recovery/journal.cpp#L174); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Inspected inspect_impl(std::string_view bytes,Limits limits)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Validate a complete protected frame without constructing variable owning storage. |
| inputs / outputs | Checks record byte limit, signature/version/flags, protected-header checksum, exact declared body size/body checksum, then full body parse; returns Inspected statistics and body digest. |
| invariants | Both checksum fields must be lowercase hexadecimal; exact frame length/no trailing body bytes required. Statistics reserve a second structural pass for subsequent decode, so inspect alone does less work than its admitted abstract total. |
| ownership | Borrows immutable input synchronously; changes only private codec preparation. Returned fixed metadata owns its fields. No filesystem or native query state changes. |
| failure | ImageFailure propagates with its fixed diagnostic; public journal wrappers translate that type only. MemoryFailure/bad_alloc propagate unchanged; private preparation is released and no result is published. |
| cost | SHA256 of prefix and body plus one structural parse; charges structural parse work a second time. O(bytes plus CSV comparisons), constant stack and no successful heap allocation. |
| Design | [include/crown/recovery/journal.hpp](../../../../../include/crown/recovery/journal.hpp), [docs/journal.md §Format 1](../../../../journal.md), [docs/journal.md §Resources and evidence](../../../../journal.md), [src/recovery/binary_detail.hpp](../../../../../src/recovery/binary_detail.hpp) |

## B0024

[Lines 184–187](../../../../../src/recovery/journal.cpp#L184); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Decoded decode_impl(const resource::MemoryAccount& account,std::string_view bytes,Limits limits)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Deep-decode an already fully validated frame in the receiving account. |
| inputs / outputs | inspect_impl first checks the entire frame and admits materialization work; a fresh body parser then fills Decoded row/source/CSV while retaining the inspected fixed metadata. |
| invariants | Immutable bytes must remain unchanged between both passes. Returns no borrowed frame byte; it does not admit values against a compiled catalog or establish durable persistence. |
| ownership | Decoded owns all variable payload bytes via receiving-account allocators; inspect metadata is copied. Native consumers may later borrow only while Decoded survives. |
| failure | ImageFailure propagates with its fixed diagnostic; public journal wrappers translate that type only. MemoryFailure/bad_alloc propagate unchanged; private preparation is released and no result is published. |
| cost | One full inspection/checksums plus another body traversal; account vectors for source/CSV/temporary cells and combined native row where present. No full input-frame copy. |
| Design | [include/crown/recovery/journal.hpp](../../../../../include/crown/recovery/journal.hpp), [docs/journal.md §Format 1](../../../../journal.md), [docs/journal.md §Resources and evidence](../../../../journal.md), [src/recovery/binary_detail.hpp](../../../../../src/recovery/binary_detail.hpp) |

## B0025

[Lines 188–189](../../../../../src/recovery/journal.cpp#L188); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L188-L189:sha256:dd37143a66a1579d789f5a05b83e6dbc044fa20a9ae1ac00adfbe037ad822396
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Design note for adjacent code: Structural continuity only; pending.frame borrows caller bytes. File repair and native transition validation belong to file/session owners. This is caller guidance recorded as prose, not an executable result. |
| inputs / outputs | No runtime interface is implemented by these comment-only lines. They sit at src/recovery/journal.cpp lines 186-191; the surrounding declaration/body defines its own inputs and outputs. |
| invariants | The words record the intended use boundary only. They do not add a guard, proof, capability, transaction, durability guarantee, or account charge; verify behavior in the referenced implementation. |
| ownership | Comment text owns no data. Object lifetimes, borrows, and account attribution remain those of the adjacent source objects and their constructors. |
| failure | No failure path is implemented here. Any mentioned failure or recovery rule belongs to the adjacent operation and its existing error carrier. |
| cost | No runtime work is performed by these lines; any cost/bound in the note is not certified by this comment-only card. |
| Design | [src/recovery/journal.cpp](../../../../../src/recovery/journal.cpp), [docs/code_specs/files/src/recovery/journal.cpp.md](journal.cpp.md), [docs/journal.md](../../../../journal.md), [docs/journal-files.md](../../../../journal-files.md) |

## B0026

[Lines 190–250](../../../../../src/recovery/journal.cpp#L190); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
bool next_record(Scanned& result,std::string_view tail,const ScanLimits& limits,const Header* expected,bool allow_torn)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Advance one bounded ordered-prefix state through a complete record or compatible torn tail. |
| inputs / outputs | Mutates private Scanned candidate with copied limits and optional exact expected header. Reads fixed available prefix, checks protected length/hash, inspects complete frame, and binds contiguous ordinal/input/commit/checkpoint transitions. |
| invariants | First record must be complete header. Pending input cannot be replaced; sequence/substep/input digest and physical versus metadata/window completion are checked. A later compatible short header/body can set torn_tail; complete corruption always rejects. This is structural history, not native transition or durability proof. |
| ownership | Scanned owns fixed metadata; pending.frame borrows the caller frame bytes until completion or owner destruction. Caller wrappers pass a private state copy to prevent partial public update on failure. |
| failure | Shared ImageFailure on malformed/limit/work/binding data. Internal candidate may have accumulated charges/fields before failure; scan/advance/Cursor do not publish it on rejection. |
| cost | O(frame bytes plus record CSV comparisons), allocation-free. Cumulative byte/work/record admission includes fixed-prefix checks plus inspect statistics; fixed header is revisited for checksum validation. No prior frame scan. |
| Design | [include/crown/recovery/journal.hpp](../../../../../include/crown/recovery/journal.hpp), [docs/journal.md §Format 1](../../../../journal.md), [docs/journal.md §Resources and evidence](../../../../journal.md), [src/recovery/binary_detail.hpp](../../../../../src/recovery/binary_detail.hpp) |

## B0027

[Lines 251–256](../../../../../src/recovery/journal.cpp#L251); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Scanned scan_impl(std::string_view bytes,ScanLimits limits,const Header* expected)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Validate a whole caller-provided journal prefix under one copied allowance. |
| inputs / outputs | Walks bytes from consumed offset through next_record, returning a nonempty complete prefix or later compatible torn suffix. |
| invariants | No empty/partial initial header; each next record shares cumulative work and record counts. Returned boundaries/pending metadata do not authorize repair, truncation, native query admission or retirement. |
| ownership | Result contains a borrowed pending frame into immutable caller bytes; caller must retain those bytes through use of that pending view. |
| failure | ImageFailure propagates with its fixed diagnostic; public journal wrappers translate that type only. MemoryFailure/bad_alloc propagate unchanged; private preparation is released and no result is published. |
| cost | O(all supplied complete frame visits plus per-record CSV quadratic comparisons and bounded suffix checks), no heap allocation or filesystem reads. |
| Design | [include/crown/recovery/journal.hpp](../../../../../include/crown/recovery/journal.hpp), [docs/journal.md §Format 1](../../../../journal.md), [docs/journal.md §Resources and evidence](../../../../journal.md), [src/recovery/binary_detail.hpp](../../../../../src/recovery/binary_detail.hpp) |

## B0028

[Lines 257–261](../../../../../src/recovery/journal.cpp#L257); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Scanned advance_impl(const Scanned& before,std::string_view frame,ScanLimits limits,const Header* expected)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Prepare exactly one complete incremental record update. |
| inputs / outputs | Copies prior Scanned state, clears its torn_tail flag and calls next_record with allow_torn=false; exact consumed delta must equal supplied frame size. |
| invariants | Rejects concatenated frames, short tails and out-of-order continuation without mutating before. Copied snapshots cannot create a Cursor or replace its private grant. |
| ownership | Pending views in prior/new state remain borrowed from their original frames. Feed callers must preserve the owning byte storage; copying state does not copy payload bytes. |
| failure | ImageFailure propagates with its fixed diagnostic; public journal wrappers translate that type only. MemoryFailure/bad_alloc propagate unchanged; private preparation is released and no result is published. |
| cost | Fixed metadata copy plus one complete record validation; no reread of earlier bytes or allocation. |
| Design | [include/crown/recovery/journal.hpp](../../../../../include/crown/recovery/journal.hpp), [docs/journal.md §Format 1](../../../../journal.md), [docs/journal.md §Resources and evidence](../../../../journal.md), [src/recovery/binary_detail.hpp](../../../../../src/recovery/binary_detail.hpp) |

## B0029

[Lines 262–264](../../../../../src/recovery/journal.cpp#L262); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
template<class Action> auto guarded(Action&& action)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Translate only the shared image-codec exception at journal public boundaries. |
| inputs / outputs | Invokes the supplied synchronous action; ImageFailure becomes journal::Failure with the same fault enum and fixed message. |
| invariants | MemoryFailure/bad_alloc and unrelated exceptions propagate unchanged. This one narrow adapter does not retry, suppress or perform rollback. |
| ownership | Borrows immutable input synchronously; changes only private codec preparation. Returned fixed metadata owns its fields. No filesystem or native query state changes. |
| failure | Throws journal::Failure for ImageFailure; every other exception propagates. Required public error vocabulary, not removable cleanup complexity. |
| cost | Fixed successful try boundary; one small exception translation only when ImageFailure is thrown, no owning diagnostic string. |
| Design | [include/crown/recovery/journal.hpp](../../../../../include/crown/recovery/journal.hpp), [docs/journal.md §Format 1](../../../../journal.md) |

## B0030

[Lines 265–265](../../../../../src/recovery/journal.cpp#L265); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L265-L265:sha256:533f16bca7d58f44b3103b92e3485d22cfbb34bbad5ea3f3fa3b5a9dcb24ec89
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Closes the anonymous namespace at this source boundary; this is a lexical delimiter, not an operation. |
| inputs / outputs | No runtime input or output. Declarations following the span leave the preceding C++ scope. |
| invariants | The delimiter ends the preceding scope's visibility/linkage region; it adds no validation, publication, ownership transfer, or runtime authority. |
| ownership | The delimiter adds no owner. If it ends a function/block with live automatic objects, their normal destructors release those objects; namespace and type-definition closes change no existing object's lifetime. |
| failure | No explicit failure translation or catch is added. If a function/block exit destroys automatic objects, exception behavior follows those destructors; namespace/type closes have no runtime failure path. |
| cost | The delimiter adds no algorithmic work. A function/block exit can run existing automatic-object destructors and cleanup; namespace/type closes have no runtime cost. |
| Design | [src/recovery/journal.cpp](../../../../../src/recovery/journal.cpp), [docs/code_specs/files/src/recovery/journal.cpp.md](journal.cpp.md), [docs/journal.md](../../../../journal.md), [docs/journal-files.md](../../../../journal-files.md) |

## B0031

[Lines 266–268](../../../../../src/recovery/journal.cpp#L266); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Encoded encode(const resource::MemoryAccount& account,std::uint64_t ordinal,const PayloadView& value,Limits limits)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Expose preflighted journal record encoding with journal failure categories. |
| inputs / outputs | Forwards account, ordinal, borrowed payload and copied Limits to encode_impl under guarded; returns owning Encoded. |
| invariants | Format/checksum construction is separate from append/fsync/root selection and from native value admission. |
| ownership | Result owns receiving-account bytes; input payload is synchronously borrowed only. |
| failure | ImageFailure translated to journal::Failure; allocation failures remain unchanged; no file or runtime update. |
| cost | Wrapper adds fixed forwarding; inherited two serialization passes/checksums and one final account buffer allocation. |
| Design | [include/crown/recovery/journal.hpp](../../../../../include/crown/recovery/journal.hpp), [docs/journal.md §Format 1](../../../../journal.md), [docs/journal.md §Resources and evidence](../../../../journal.md), [src/recovery/binary_detail.hpp](../../../../../src/recovery/binary_detail.hpp) |

## B0032

[Lines 269–269](../../../../../src/recovery/journal.cpp#L269); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Inspected inspect(std::string_view bytes,Limits limits)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Expose allocation-free complete-record inspection. |
| inputs / outputs | Immutable bytes and copied Limits produce fixed Inspected metadata via guarded inspect_impl. |
| invariants | Checks structure/checksums and admits reserved materialization work, without proving a native session transition or persistence. |
| ownership | Borrows immutable input synchronously; changes only private codec preparation. Returned fixed metadata owns its fields. No filesystem or native query state changes. |
| failure | ImageFailure becomes journal::Failure; no partial result is returned. |
| cost | Fixed wrapper plus complete prefix/body hashes and structural scan; no successful variable allocation. |
| Design | [include/crown/recovery/journal.hpp](../../../../../include/crown/recovery/journal.hpp), [docs/journal.md §Format 1](../../../../journal.md), [docs/journal.md §Resources and evidence](../../../../journal.md), [src/recovery/binary_detail.hpp](../../../../../src/recovery/binary_detail.hpp) |

## B0033

[Lines 270–272](../../../../../src/recovery/journal.cpp#L270); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Decoded decode(const resource::MemoryAccount& account,std::string_view bytes,Limits limits)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Expose receiving-account ownership of a fully validated record payload. |
| inputs / outputs | Immutable bytes/account/limits produce Decoded with native row/source/CSV ownership via guarded decode_impl. |
| invariants | Full validation precedes variable allocation; caller still performs table/domain/source/native transition checks before accepting input. |
| ownership | Returned Decoded owns all copied variable values. Input frame may be released after return. |
| failure | Shared codec faults become journal::Failure; MemoryFailure/bad_alloc propagate; partial Decoded releases via RAII. |
| cost | Fixed wrapper plus complete inspection and second body traversal; actual temporary/final account allocations are bounded by payload and account. |
| Design | [include/crown/recovery/journal.hpp](../../../../../include/crown/recovery/journal.hpp), [docs/journal.md §Format 1](../../../../journal.md), [docs/journal.md §Resources and evidence](../../../../journal.md), [src/recovery/binary_detail.hpp](../../../../../src/recovery/binary_detail.hpp) |

## B0034

[Lines 273–273](../../../../../src/recovery/journal.cpp#L273); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Scanned scan(std::string_view bytes,ScanLimits limits,const Header* expected)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Expose whole-prefix structural validation without file mutation. |
| inputs / outputs | Immutable byte view, copied ScanLimits and optional expected Header yield Scanned under guarded scan_impl. |
| invariants | Expected Header compares every field; returned report remains descriptive. Borrowing and cumulative accounting match scan_impl. |
| ownership | Only a pending frame view borrows the caller prefix. Expected header is read synchronously; no pointer retention. |
| failure | ImageFailure becomes journal::Failure; invalid prefixes return no partial report. |
| cost | Fixed wrapper plus full prefix visit/CSV checks, no successful allocation or I/O. |
| Design | [include/crown/recovery/journal.hpp](../../../../../include/crown/recovery/journal.hpp), [docs/journal.md §Format 1](../../../../journal.md), [docs/journal.md §Resources and evidence](../../../../journal.md), [src/recovery/binary_detail.hpp](../../../../../src/recovery/binary_detail.hpp) |

## B0035

[Lines 274–274](../../../../../src/recovery/journal.cpp#L274); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Cursor::Cursor(ScanLimits limits,const Header* expected):limits_(limits),expected_(expected?std::optional<Header>{*expected}:std::nullopt)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Start a private cumulative incremental validation owner. |
| inputs / outputs | Copies ScanLimits and, if provided, the complete expected Header into a fresh active Cursor; initial state is empty. |
| invariants | No Scanned import or allowance refill API; constructor does not validate an initial record or touch files. Expected pointer need not survive construction. |
| ownership | Cursor owns grant/continuation and expected-header values. Payload bytes fed later remain externally owned. |
| failure | No validation failure is introduced by construction; first feed enforces record/header/limits. |
| cost | Fixed-size limits/header/metadata initialization, no heap allocation. |
| Design | [include/crown/recovery/journal.hpp](../../../../../include/crown/recovery/journal.hpp), [docs/journal.md §Format 1](../../../../journal.md) |

## B0036

[Lines 275–276](../../../../../src/recovery/journal.cpp#L275); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Cursor::Cursor(Cursor&& other) noexcept :limits_(other.limits_),expected_(other.expected_),state_(other.state_),active_(other.active_)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Transfer incremental validator state and disable the moved-from owner. |
| inputs / outputs | Move construction copies fixed limits/expected/state/active flag; source becomes inactive with empty state. |
| invariants | Does not clone continuation authority into two active owners; pending frame byte lifetime is not extended or transferred into ownership. |
| ownership | Destination now owns the private continuation; pending frame views still borrow caller storage. |
| failure | noexcept; later feed/tail on inactive source rejects with journal::Failure. |
| cost | Fixed-size metadata copy/reset, noexcept and no allocation. |
| Design | [include/crown/recovery/journal.hpp](../../../../../include/crown/recovery/journal.hpp), [docs/journal.md §Format 1](../../../../journal.md) |

## B0037

[Lines 277–280](../../../../../src/recovery/journal.cpp#L277); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Cursor& Cursor::operator=(Cursor&& other) noexcept
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Replace one cursor with another private continuation by move. |
| inputs / outputs | Nonself move copies limits/header/state/active then clears/deactivates source; self-move returns the same owner unchanged. |
| invariants | Discarded target has no owned frame payload or I/O resource. Move does not make borrowed frames durable or independently owned. |
| ownership | Only destination retains the transferred active continuation; caller still owns all pending frame bytes. |
| failure | noexcept; no exception-handling machinery. |
| cost | Fixed-size metadata copy/reset, no allocation or parsing. |
| Design | [include/crown/recovery/journal.hpp](../../../../../include/crown/recovery/journal.hpp), [docs/journal.md §Format 1](../../../../journal.md) |

## B0038

[Lines 281–281](../../../../../src/recovery/journal.cpp#L281); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L281-L281:sha256:ee75c9b4c76b064984c2286a06d453f469309dfdfa52465b73fc48a148942830
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Design note for adjacent code: Publish the copied continuation only after one complete frame validates. This is caller guidance recorded as prose, not an executable result. |
| inputs / outputs | No runtime interface is implemented by these comment-only lines. They sit at src/recovery/journal.cpp lines 279-283; the surrounding declaration/body defines its own inputs and outputs. |
| invariants | The words record the intended use boundary only. They do not add a guard, proof, capability, transaction, durability guarantee, or account charge; verify behavior in the referenced implementation. |
| ownership | Comment text owns no data. Object lifetimes, borrows, and account attribution remain those of the adjacent source objects and their constructors. |
| failure | No failure path is implemented here. Any mentioned failure or recovery rule belongs to the adjacent operation and its existing error carrier. |
| cost | No runtime work is performed by these lines; any cost/bound in the note is not certified by this comment-only card. |
| Design | [src/recovery/journal.cpp](../../../../../src/recovery/journal.cpp), [docs/code_specs/files/src/recovery/journal.cpp.md](journal.cpp.md), [docs/journal.md](../../../../journal.md), [docs/journal-files.md](../../../../journal-files.md) |

## B0039

[Lines 282–286](../../../../../src/recovery/journal.cpp#L282); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Scanned Cursor::feed(std::string_view frame) &
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Commit one valid complete frame to the private Cursor continuation. |
| inputs / outputs | Active lvalue receives one complete frame, computes advance_impl on copied state and assigns only after success; returns a descriptive state copy. |
| invariants | Failure preserves previous private state/grant. No filesystem append/repair or native query transition occurs. Cumulative byte/work/record counters cannot be reset by editing returned metadata. |
| ownership | Cursor owns continuation, not frame bytes. A pending input view must retain immutable caller storage until no longer pending. |
| failure | Inactive source throws journal::Failure directly; guarded codec failures reject without state publication. |
| cost | One frame inspection/continuity validation plus fixed metadata copies; no allocation and no prior-prefix rescan. |
| Design | [include/crown/recovery/journal.hpp](../../../../../include/crown/recovery/journal.hpp), [docs/journal.md §Format 1](../../../../journal.md), [docs/journal.md §Resources and evidence](../../../../journal.md), [src/recovery/binary_detail.hpp](../../../../../src/recovery/binary_detail.hpp) |

## B0040

[Lines 287–294](../../../../../src/recovery/journal.cpp#L287); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Scanned Cursor::finish_tail(std::string_view tail) &
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Validate only a compatible incomplete suffix and retain its spent validation work. |
| inputs / outputs | Active Cursor returns state unchanged for empty tail; otherwise validates on a copy and accepts only when next_record classifies a torn suffix. |
| invariants | A complete supplied record is rejected here; first incomplete header rejects. This method does not close/freeze the Cursor or repair a file; a later feed may validate the replacement full frame with cumulative limits. |
| ownership | New state retains any earlier pending frame view, with its original external lifetime. No ownership of tail bytes is acquired. |
| failure | Inactive cursor, complete record or incompatible tail rejects with journal::Failure; prior Cursor state preserved. |
| cost | At most available fixed-prefix/hash checks for an incomplete tail, no owning allocation; fixed state copies. |
| Design | [include/crown/recovery/journal.hpp](../../../../../include/crown/recovery/journal.hpp), [docs/journal.md §Format 1](../../../../journal.md), [docs/journal.md §Resources and evidence](../../../../journal.md), [src/recovery/binary_detail.hpp](../../../../../src/recovery/binary_detail.hpp) |

## B0041

[Lines 295–295](../../../../../src/recovery/journal.cpp#L295); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L295-L295:sha256:25ecb8ffb1ebe1c921f836fc95978d1ed94e254c9d72f4da0424c9e79a75233a
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Design note for adjacent code: Returned views borrow Decoded storage; native admission checks actual policy. This is caller guidance recorded as prose, not an executable result. |
| inputs / outputs | No runtime interface is implemented by these comment-only lines. They sit at src/recovery/journal.cpp lines 293-297; the surrounding declaration/body defines its own inputs and outputs. |
| invariants | The words record the intended use boundary only. They do not add a guard, proof, capability, transaction, durability guarantee, or account charge; verify behavior in the referenced implementation. |
| ownership | Comment text owns no data. Object lifetimes, borrows, and account attribution remain those of the adjacent source objects and their constructors. |
| failure | No failure path is implemented here. Any mentioned failure or recovery rule belongs to the adjacent operation and its existing error carrier. |
| cost | No runtime work is performed by these lines; any cost/bound in the note is not certified by this comment-only card. |
| Design | [src/recovery/journal.cpp](../../../../../src/recovery/journal.cpp), [docs/code_specs/files/src/recovery/journal.cpp.md](journal.cpp.md), [docs/journal.md](../../../../journal.md), [docs/journal-files.md](../../../../journal-files.md) |

## B0042

[Lines 296–320](../../../../../src/recovery/journal.cpp#L296); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
InputView Decoded::input_view() const &
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Borrow a typed input view from a decoded owning input record. |
| inputs / outputs | Lvalue-only Decoded checks input kind/sequence/host table range and row/source/CSV sizes, then selects physical or window view plus optional source/reader. |
| invariants | Guards basic metadata/storage coherence and operation/window tag; it is not full revalidation of mutable public metadata or schema/domain/source authority. Downstream native admission still checks real policy. |
| ownership | Returned tuple/name/CSV views borrow this Decoded row and vectors; retain owner through consumption. Rvalue overload is deleted in the header. |
| failure | Explicit journal::Failure on checked incoherence; otherwise returns borrowed views. No progress is acknowledged here. |
| cost | Constant-time metadata/variant construction and size reads; no row scan, scalar formatting, payload copy or allocation. |
| Design | [include/crown/recovery/journal.hpp](../../../../../include/crown/recovery/journal.hpp), [docs/journal.md §Format 1](../../../../journal.md), [src/runtime/session.cpp](../../../../../src/runtime/session.cpp), [docs/native-replay.md](../../../../native-replay.md), [docs/session-journal.md](../../../../session-journal.md) |

## B0043

[Lines 321–321](../../../../../src/recovery/journal.cpp#L321); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L321-L321:sha256:ade4c7e26c3c86f66e5229b8a85c7b0beb63c4bdd3dee7de6f59075c925502ba
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Closes the namespace crown::recovery::journal at this source boundary; this is a lexical delimiter, not an operation. |
| inputs / outputs | No runtime input or output. Declarations following the span leave the preceding C++ scope. |
| invariants | The delimiter ends the preceding scope's visibility/linkage region; it adds no validation, publication, ownership transfer, or runtime authority. |
| ownership | The delimiter adds no owner. If it ends a function/block with live automatic objects, their normal destructors release those objects; namespace and type-definition closes change no existing object's lifetime. |
| failure | No explicit failure translation or catch is added. If a function/block exit destroys automatic objects, exception behavior follows those destructors; namespace/type closes have no runtime failure path. |
| cost | The delimiter adds no algorithmic work. A function/block exit can run existing automatic-object destructors and cleanup; namespace/type closes have no runtime cost. |
| Design | [src/recovery/journal.cpp](../../../../../src/recovery/journal.cpp), [docs/code_specs/files/src/recovery/journal.cpp.md](journal.cpp.md), [docs/journal.md](../../../../journal.md), [docs/journal-files.md](../../../../journal-files.md) |
