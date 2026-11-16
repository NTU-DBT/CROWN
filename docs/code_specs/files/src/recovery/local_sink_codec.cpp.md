# `src/recovery/local_sink_codec.cpp` — block usage map

[Source](../../../../../src/recovery/local_sink_codec.cpp) · [Source index](../../../README.md) · [Subsystem contracts](../../../subsystem_contracts.md) · [Reviewed primitives](../../../primitives.md)

Encode, validate and publish checkpoints, journals, generations and local delivery receipts with explicit durable authority.

Snapshot SHA-256: `f4a0ebe12f94df8bd8e6ef34f0d1a2d57b2d4c2b72c7ce7ce5a263c489c95182`. 144 lines partitioned into 27 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [recovery](../../../subsystem_contracts.md#recovery). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/checkpoints.md](../../../../checkpoints.md), [docs/journal.md](../../../../journal.md), [docs/journal-files.md](../../../../journal-files.md), [docs/generations.md](../../../../generations.md), [docs/local-sink.md](../../../../local-sink.md), [docs/history-retirement.md](../../../../history-retirement.md), [docs/update_patterns.md](../../../../update_patterns.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–10](../../../../../src/recovery/local_sink_codec.cpp#L1) | Imports dependencies; declares namespace scope; declares aliases; declares values/defaults or compile-time conditions. |  · [reviewed contract](#b0001) |
| [B0002 · 11–21](../../../../../src/recovery/local_sink_codec.cpp#L11) | Callable definition: bool utf8(std::string_view value) | calls size; returns false; false; 2 loop sites · [reviewed contract](#b0002) |
| [B0003 · 22–22](../../../../../src/recovery/local_sink_codec.cpp#L22) | Explanatory comments or spacing. | source comment (unverified): // File derives the schema hash; here check supplied identity/type data. · [reviewed contract](#b0003) |
| [B0004 · 23–28](../../../../../src/recovery/local_sink_codec.cpp#L23) | Callable definition: void header_valid(const Header& header,std::span&lt;const ScalarType&gt; schema) | calls require, hex, size, runtime::detail::checkpoint_options; guard require(hex(header.query_id) && hex(header.sink_id) && hex(header.binding.physical_sha256) && hex(h…; 1 loop sites; source comment (unverified): // File derives the schema hash; here check supplied identity/type data. · [reviewed contract](#b0004) |
| [B0005 · 29–29](../../../../../src/recovery/local_sink_codec.cpp#L29) | Callable definition: void hash(Writer& writer,std::span&lt;const char&gt; text) | calls put, data, size · [reviewed contract](#b0005) |
| [B0006 · 30–33](../../../../../src/recovery/local_sink_codec.cpp#L30) | Callable definition: void framing(Writer& writer) | calls put, integer, fill, data · [reviewed contract](#b0006) |
| [B0007 · 34–39](../../../../../src/recovery/local_sink_codec.cpp#L34) | Callable definition: void header_body(Writer& writer,const Header& h,std::span&lt;const ScalarType&gt; schema) | calls integer, hash; 2 loop sites · [reviewed contract](#b0007) |
| [B0008 · 40–42](../../../../../src/recovery/local_sink_codec.cpp#L40) | Callable definition: void epoch_prefix(Writer& writer,std::uint64_t ordinal,std::uint64_t generation,std::uint64_t sequence,std::uint64_t rows) | calls require, integer; guard require(ordinal&gt;0 && generation&gt;0 && sequence&gt;0);writer.integer(1,1);writer.integer(ordinal,8);writ… · [reviewed contract](#b0008) |
| [B0009 · 43–51](../../../../../src/recovery/local_sink_codec.cpp#L43) | Callable definition: void row(Writer& writer,const RowView& value,std::span&lt;const ScalarType&gt; schema) | calls require, size, integer, storage::type_of; guard writer.budget.row();require(static_cast&lt;unsigned&gt;(value.operation)&lt;=1 && value.values.size()==schem…; 1 loop sites · [reviewed contract](#b0009) |
| [B0010 · 52–57](../../../../../src/recovery/local_sink_codec.cpp#L52) | Callable definition: void finish(ImageVector&lt;char&gt;& bytes,Budget& budget) | calls size, charge, sha256_fixed, data; 1 loop sites · [reviewed contract](#b0010) |
| [B0011 · 58–58](../../../../../src/recovery/local_sink_codec.cpp#L58) | Callable definition: void compare_charge(Budget& budget,std::size_t size) | calls require, charge; guard void compare_charge(Budget& budget,std::size_t size) {require(size&lt;=(UINT64_MAX-1)/2,ImageFault::wo… · [reviewed contract](#b0011) |
| [B0012 · 59–61](../../../../../src/recovery/local_sink_codec.cpp#L59) | Callable definition: template&lt;std::size_t N&gt; std::array&lt;char,N&gt; read_hash(Reader& reader) | calls take, require, hex, data; guard std::array&lt;char,N&gt; result{};const auto bytes=reader.take(N);require(hex({bytes.data(),bytes.size()}…; returns result · [reviewed contract](#b0012) |
| [B0013 · 62–67](../../../../../src/recovery/local_sink_codec.cpp#L62) | Callable definition: std::uint64_t prefix(std::string_view bytes,Budget& budget) | calls require, size, take, integer; guard require(bytes.size()&gt;=frame_header_size);Reader reader{bytes,budget};require(reader.take(8)==magic)…; returns body+frame_header_size · [reviewed contract](#b0013) |
| [B0014 · 68–68](../../../../../src/recovery/local_sink_codec.cpp#L68) | Explanatory comments or spacing. | source comment (unverified): // Inspect checks canonical bytes; decoded native rows own deep payload copies. · [reviewed contract](#b0014) |
| [B0015 · 69–104](../../../../../src/recovery/local_sink_codec.cpp#L69) | Callable definition: detail::Inspected parse(std::string_view bytes,std::span&lt;const ScalarType&gt; schema,Budget& budget,Epoch* decoded,const resource::M… | calls require, prefix, size, charge; guard require(budget.limits.bytes&gt;=frame_header_size+9,ImageFault::limit);const auto total=prefix(bytes,b…; returns info; growth copy_of, push_back, reserve; 4 loop sites; source comment (unverified): // Inspect checks canonical bytes; decoded native rows own deep payload copies. · [reviewed contract](#b0015) |
| [B0016 · 105–105](../../../../../src/recovery/local_sink_codec.cpp#L105) | Closes surrounding scope/type. | source comment (unverified): // namespace · [reviewed contract](#b0016) |
| [B0017 · 106–110](../../../../../src/recovery/local_sink_codec.cpp#L106) | Callable definition: std::array&lt;char,64&gt; schema_sha256(const resource::MemoryAccount& account,std::span&lt;const ScalarType&gt; schema) | calls bytes, reserve, size, binary_detail::require; guard for(const auto type:schema){binary_detail::require(static_cast&lt;unsigned&gt;(type)&lt;=4,ImageFault::scala…; returns sha256_fixed({bytes.data(),bytes.size()}); growth push_back, reserve; 1 loop sites · [reviewed contract](#b0017) |
| [B0018 · 111–111](../../../../../src/recovery/local_sink_codec.cpp#L111) | declares namespace scope. |  · [reviewed contract](#b0018) |
| [B0019 · 112–117](../../../../../src/recovery/local_sink_codec.cpp#L112) | Callable definition: Encoded encode_header(const resource::MemoryAccount& account,const Header& header,std::span&lt;const ScalarType&gt; schema,ImageLimits … | calls charge, require, size, header_valid; guard Budget pre{limits};pre.charge(1024);require(schema.size()&lt;=limits.fields,ImageFault::limit);pre.cha…; returns result; growth reserve · [reviewed contract](#b0019) |
| [B0020 · 118–119](../../../../../src/recovery/local_sink_codec.cpp#L118) | Explanatory comments or spacing. | source comment (unverified): // Sort views of complete signed row bytes. Scratch and final bytes overlap · [reviewed contract](#b0020) |
| [B0021 · 120–133](../../../../../src/recovery/local_sink_codec.cpp#L120) | Callable definition: Encoded encode_epoch(const resource::MemoryAccount& account,std::uint64_t ordinal,std::uint64_t generation,std::uint64_t sequence… | calls require, size, framing, epoch_prefix; guard require(rows.size()&lt;=limits.rows && schema.size()&lt;=limits.fields,ImageFault::limit);Budget pre{limi…; returns std::string_view(values.data()+segment.offset,segment.size); text(a)&lt;text(b); growth push_back, reserve; 4 loop sites; source comment (unverified): // Sort views of complete signed row bytes. Scratch and final bytes overlap · [reviewed contract](#b0021) |
| [B0022 · 134–134](../../../../../src/recovery/local_sink_codec.cpp#L134) | Callable definition: Inspected inspect(std::string_view bytes,std::span&lt;const ScalarType&gt; schema,ImageLimits limits) | calls parse; returns parse(bytes,schema,budget,nullptr,{}) · [reviewed contract](#b0022) |
| [B0023 · 135–135](../../../../../src/recovery/local_sink_codec.cpp#L135) | Explanatory comments or spacing. | source comment (unverified): // This path admits two complete parse/checksum passes in one record grant. · [reviewed contract](#b0023) |
| [B0024 · 136–138](../../../../../src/recovery/local_sink_codec.cpp#L136) | Callable definition: Epoch decode(const resource::MemoryAccount& account,std::string_view bytes,std::span&lt;const ScalarType&gt; schema,ImageLimits limits) | calls inspect, require, charge, parse; guard const auto info=inspect(bytes,schema,limits);require(!info.header);Budget budget{limits};budget.cha…; returns result; source comment (unverified): // This path admits two complete parse/checksum passes in one record grant. · [reviewed contract](#b0024) |
| [B0025 · 139–139](../../../../../src/recovery/local_sink_codec.cpp#L139) | Explanatory comments or spacing. | source comment (unverified): // Validate protected length without requiring or inspecting the whole body. · [reviewed contract](#b0025) |
| [B0026 · 140–142](../../../../../src/recovery/local_sink_codec.cpp#L140) | Callable definition: std::uint64_t frame_size(std::string_view bytes,ImageLimits limits,std::uint64_t& work) | calls require, prefix; guard require(limits.bytes&gt;=frame_header_size+9,ImageFault::limit);Budget budget{limits};const auto resul…; returns result; source comment (unverified): // Validate protected length without requiring or inspecting the whole body. · [reviewed contract](#b0026) |
| [B0027 · 143–144](../../../../../src/recovery/local_sink_codec.cpp#L143) | Closes surrounding scope/type. | source comment (unverified): // namespace detail · [reviewed contract](#b0027) |

## B0001

[Lines 1–10](../../../../../src/recovery/local_sink_codec.cpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
constexpr std::string_view magic="CROWNSK1";
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Bind durable local-sink frame serialization to its CROWNSK1/version-1 wire. |
| inputs / outputs | Local signature and shared bounded Writer/Reader helpers are used for header/epoch frames; no executable initialization. |
| invariants | These codecs expect the File-admitted immutable schema; they do not own a file lock, append/sync an epoch or mint a private Receipt. Native producer correctness is checked by the session separately. |
| ownership | Borrows immutable input synchronously; changes only private codec preparation. Returned fixed metadata owns its fields. No filesystem or native query state changes. |
| failure | ImageFailure propagates with fixed shared codec diagnostic; MemoryFailure/bad_alloc propagate unchanged. Private preparation unwinds without a partial public result or file mutation. |
| cost | Static fixed view and declarations, no allocation or I/O. |
| Design | [include/crown/recovery/local_sink.hpp](../../../../../include/crown/recovery/local_sink.hpp), [docs/local-sink.md](../../../../local-sink.md), [src/recovery/local_sink_codec.hpp](../../../../../src/recovery/local_sink_codec.hpp) |

## B0002

[Lines 11–21](../../../../../src/recovery/local_sink_codec.cpp#L11); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
bool utf8(std::string_view value)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Validate UTF8 scalar strings while permitting embedded NUL. |
| inputs / outputs | Returns true for shortest-form valid Unicode scalar sequences, including empty text and ASCII zero; false for malformed bytes. |
| invariants | Unlike journal source names, row strings may contain NUL. No normalization, collation transform or source/path acceptance occurs. |
| ownership | Borrows immutable input synchronously; changes only private codec preparation. Returned fixed metadata owns its fields. No filesystem or native query state changes. |
| failure | Boolean rejection only; no exception or diagnostic construction. |
| cost | O(text bytes), constant stack and no allocation; encode/parse callers precharge validation byte work. |
| Design | [include/crown/recovery/local_sink.hpp](../../../../../include/crown/recovery/local_sink.hpp), [docs/local-sink.md](../../../../local-sink.md) |

## B0003

[Lines 22–22](../../../../../src/recovery/local_sink_codec.cpp#L22); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L22-L22:sha256:0646b34ea3198fa274f85cc9d8822a2849ebf650a65678183ef34745ab77106d
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Design note for adjacent code: File derives the schema hash; here check supplied identity/type data. This is caller guidance recorded as prose, not an executable result. |
| inputs / outputs | No runtime interface is implemented by these comment-only lines. They sit at src/recovery/local_sink_codec.cpp lines 20-24; the surrounding declaration/body defines its own inputs and outputs. |
| invariants | The words record the intended use boundary only. They do not add a guard, proof, capability, transaction, durability guarantee, or account charge; verify behavior in the referenced implementation. |
| ownership | Comment text owns no data. Object lifetimes, borrows, and account attribution remain those of the adjacent source objects and their constructors. |
| failure | No failure path is implemented here. Any mentioned failure or recovery rule belongs to the adjacent operation and its existing error carrier. |
| cost | No runtime work is performed by these lines; any cost/bound in the note is not certified by this comment-only card. |
| Design | [src/recovery/local_sink_codec.cpp](../../../../../src/recovery/local_sink_codec.cpp), [docs/code_specs/files/src/recovery/local_sink_codec.cpp.md](local_sink_codec.cpp.md), [docs/local-sink.md](../../../../local-sink.md), [docs/journal-files.md](../../../../journal-files.md) |

## B0004

[Lines 23–28](../../../../../src/recovery/local_sink_codec.cpp#L23); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void header_valid(const Header& header,std::span<const ScalarType> schema)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Check structural sink identity, output arity and runtime policy. |
| inputs / outputs | Header and supplied type span must have valid fixed hex fields, positive catalog/first generation, matching fields and supported scalar tags; decodes 26 policy words. |
| invariants | schema_sha256 is checked for syntax here, not recomputed. File construction derives/checks it against the actual schema; actual session binding/native output verification remains separate. |
| ownership | Borrows immutable input synchronously; changes only private codec preparation. Returned fixed metadata owns its fields. No filesystem or native query state changes. |
| failure | ImageFailure propagates for binding/scalar/policy faults; no local exception translation. |
| cost | Fixed hash/policy visits plus O(schema width) enum checks, no owning allocation or I/O. |
| Design | [include/crown/recovery/local_sink.hpp](../../../../../include/crown/recovery/local_sink.hpp), [docs/local-sink.md](../../../../local-sink.md), [src/runtime/checkpoint_policy.hpp](../../../../../src/runtime/checkpoint_policy.hpp), [include/crown/recovery/image.hpp](../../../../../include/crown/recovery/image.hpp) |

## B0005

[Lines 29–29](../../../../../src/recovery/local_sink_codec.cpp#L29); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void hash(Writer& writer,std::span<const char> text)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Append or count the supplied fixed hash/identity field. |
| inputs / outputs | Writes the complete character span through shared Writer::put. |
| invariants | This helper performs no hex or width validation; header_valid and fixed-size Header arrays establish those preconditions before encoding. |
| ownership | Borrows immutable input synchronously; changes only private codec preparation. Returned fixed metadata owns its fields. No filesystem or native query state changes. |
| failure | ImageFailure propagates with fixed shared codec diagnostic; MemoryFailure/bad_alloc propagate unchanged. Private preparation unwinds without a partial public result or file mutation. |
| cost | O(field bytes) counted/copied, bounded Writer work/bytes; actual field widths are fixed. |
| Design | [include/crown/recovery/local_sink.hpp](../../../../../include/crown/recovery/local_sink.hpp), [docs/local-sink.md](../../../../local-sink.md), [src/recovery/binary_detail.hpp](../../../../../src/recovery/binary_detail.hpp), [src/recovery/local_sink.cpp](../../../../../src/recovery/local_sink.cpp) |

## B0006

[Lines 30–33](../../../../../src/recovery/local_sink_codec.cpp#L30); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void framing(Writer& writer)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Write protected-header placeholders for one sink frame. |
| inputs / outputs | Outputs CROWNSK1, version 1, flags zero, placeholder body size and 128 ASCII zero hash bytes. |
| invariants | finish replaces length and both digests only after complete body materialization. This is a codec header, not a durable file publication. |
| ownership | Borrows immutable input synchronously; changes only private codec preparation. Returned fixed metadata owns its fields. No filesystem or native query state changes. |
| failure | ImageFailure propagates with fixed shared codec diagnostic; MemoryFailure/bad_alloc propagate unchanged. Private preparation unwinds without a partial public result or file mutation. |
| cost | 148 byte writes/counts and fixed stack zero array; no independent allocation. |
| Design | [include/crown/recovery/local_sink.hpp](../../../../../include/crown/recovery/local_sink.hpp), [docs/local-sink.md](../../../../local-sink.md), [src/recovery/binary_detail.hpp](../../../../../src/recovery/binary_detail.hpp), [src/recovery/local_sink.cpp](../../../../../src/recovery/local_sink.cpp) |

## B0007

[Lines 34–39](../../../../../src/recovery/local_sink_codec.cpp#L34); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void header_body(Writer& writer,const Header& h,std::span<const ScalarType> schema)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Serialize the complete sink header payload in canonical fixed order. |
| inputs / outputs | Writes kind/ordinal zero, fixed identities/binding, arithmetic version 1, policy words, starting generation/base, arity/schema hash and supplied scalar tags. |
| invariants | Caller must first validate Header/type span. Header schema hash is supplied data here; File owns derivation and expected-header matching. |
| ownership | Borrows immutable input synchronously; changes only private codec preparation. Returned fixed metadata owns its fields. No filesystem or native query state changes. |
| failure | ImageFailure propagates with fixed shared codec diagnostic; MemoryFailure/bad_alloc propagate unchanged. Private preparation unwinds without a partial public result or file mutation. |
| cost | Fixed header bytes plus one byte per schema field, repeated for sizing/final serialization; no scalar rows or I/O. |
| Design | [include/crown/recovery/local_sink.hpp](../../../../../include/crown/recovery/local_sink.hpp), [docs/local-sink.md](../../../../local-sink.md), [src/recovery/binary_detail.hpp](../../../../../src/recovery/binary_detail.hpp), [src/recovery/local_sink.cpp](../../../../../src/recovery/local_sink.cpp) |

## B0008

[Lines 40–42](../../../../../src/recovery/local_sink_codec.cpp#L40); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void epoch_prefix(Writer& writer,std::uint64_t ordinal,std::uint64_t generation,std::uint64_t sequence,std::uint64_t rows)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Write one positive epoch identity and row-count prefix. |
| inputs / outputs | Requires ordinal/generation/physical sequence &gt;0, then writes kind 1, ordinal, generation, sequence and row count. |
| invariants | Ordinal-versus-base and monotone file generation/sequence continuity are enforced by File; this helper does not inspect previous frames. |
| ownership | Borrows immutable input synchronously; changes only private codec preparation. Returned fixed metadata owns its fields. No filesystem or native query state changes. |
| failure | ImageFailure propagates with fixed shared codec diagnostic; MemoryFailure/bad_alloc propagate unchanged. Private preparation unwinds without a partial public result or file mutation. |
| cost | 33 bytes counted/copied, fixed scalar checks, no allocation. |
| Design | [include/crown/recovery/local_sink.hpp](../../../../../include/crown/recovery/local_sink.hpp), [docs/local-sink.md](../../../../local-sink.md) |

## B0009

[Lines 43–51](../../../../../src/recovery/local_sink_codec.cpp#L43); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void row(Writer& writer,const RowView& value,std::span<const ScalarType> schema)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Validate and serialize one signed native output tuple. |
| inputs / outputs | Requires legal set operation and exact schema arity/type per ScalarView, validates UTF8 string bytes, then emits operation, width and exact scalar wire. |
| invariants | Same-sign exact duplicates are rejected during canonical sorting, not here. Opposite signs remain distinct rows; no bag multiplicities/null cells or SQL collation semantics are introduced. |
| ownership | Borrows immutable tuple/schema only during encoding; writer retains only copied canonical byte output. |
| failure | ImageFailure for operation/schema/type/scalar/limit/work faults; allocation errors propagate from account vector writes. |
| cost | O(fields plus encoded scalar/text bytes); UTF8 validation has its own precharge. Each row consumes a row unit; stack decimal rendering adds no owning string. |
| Design | [include/crown/recovery/local_sink.hpp](../../../../../include/crown/recovery/local_sink.hpp), [docs/local-sink.md](../../../../local-sink.md), [src/recovery/binary_detail.hpp](../../../../../src/recovery/binary_detail.hpp), [src/recovery/local_sink.cpp](../../../../../src/recovery/local_sink.cpp) |

## B0010

[Lines 52–57](../../../../../src/recovery/local_sink_codec.cpp#L52); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void finish(ImageVector<char>& bytes,Budget& budget)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Fill a fully materialized sink frame length and both SHA256 fields. |
| inputs / outputs | Receives frame bytes with complete 148-byte header and body; writes little-endian body size, body digest and digest of first 84 bytes. |
| invariants | Caller owns framing/size validity and final buffer. Finishing hashes establishes byte integrity, not file sync, native correctness or authentication. |
| ownership | Mutates only private receiving-account frame bytes; no borrowed view escapes. |
| failure | Work rejection may leave private buffer incomplete; no public Encoded/file state is committed. |
| cost | O(body bytes) SHA256 plus fixed prefix hashing; charges body and 84+136 work units before digest/overwrite visits. Fixed stack digests; no full-frame clone. |
| Design | [include/crown/recovery/local_sink.hpp](../../../../../include/crown/recovery/local_sink.hpp), [docs/local-sink.md](../../../../local-sink.md), [src/recovery/binary_detail.hpp](../../../../../src/recovery/binary_detail.hpp), [src/recovery/local_sink.cpp](../../../../../src/recovery/local_sink.cpp) |

## B0011

[Lines 58–58](../../../../../src/recovery/local_sink_codec.cpp#L58); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void compare_charge(Budget& budget,std::size_t size)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Reserve worst-case lexicographic row-comparison visits without overflowing. |
| inputs / outputs | For comparison length n, requires n&lt;=(UINT64_MAX-1)/2 then charges 2*n+1 units. |
| invariants | This is an abstract comparison allowance; actual string comparison may stop at the first differing byte. It is not a CPU-time or allocator bound. |
| ownership | Borrows immutable input synchronously; changes only private codec preparation. Returned fixed metadata owns its fields. No filesystem or native query state changes. |
| failure | ImageFailure propagates with fixed shared codec diagnostic; MemoryFailure/bad_alloc propagate unchanged. Private preparation unwinds without a partial public result or file mutation. |
| cost | Fixed checked arithmetic; the later comparator performs up to O(n) byte visits, no allocation. |
| Design | [include/crown/recovery/local_sink.hpp](../../../../../include/crown/recovery/local_sink.hpp), [docs/local-sink.md](../../../../local-sink.md), [src/recovery/binary_detail.hpp](../../../../../src/recovery/binary_detail.hpp), [src/recovery/local_sink.cpp](../../../../../src/recovery/local_sink.cpp) |

## B0012

[Lines 59–61](../../../../../src/recovery/local_sink_codec.cpp#L59); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
template<std::size_t N> std::array<char,N> read_hash(Reader& reader)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Read one syntax-checked fixed digest/identity from the sink body/header. |
| inputs / outputs | Consumes N bytes via Reader, validates lowercase hexadecimal and copies into fixed array. |
| invariants | Bounds/work checked before access; valid text is not recomputation or equality against a native program. |
| ownership | Borrows immutable input synchronously; changes only private codec preparation. Returned fixed metadata owns its fields. No filesystem or native query state changes. |
| failure | ImageFailure propagates with fixed shared codec diagnostic; MemoryFailure/bad_alloc propagate unchanged. Private preparation unwinds without a partial public result or file mutation. |
| cost | O(N) bounded read/hex/copy with fixed stack storage; actual N is 32/64. |
| Design | [include/crown/recovery/local_sink.hpp](../../../../../include/crown/recovery/local_sink.hpp), [docs/local-sink.md](../../../../local-sink.md), [src/recovery/binary_detail.hpp](../../../../../src/recovery/binary_detail.hpp), [src/recovery/local_sink.cpp](../../../../../src/recovery/local_sink.cpp) |

## B0013

[Lines 62–67](../../../../../src/recovery/local_sink_codec.cpp#L62); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::uint64_t prefix(std::string_view bytes,Budget& budget)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Validate the protected fixed sink header before trusting declared body length. |
| inputs / outputs | Requires at least 148 available bytes, exact signature/version/flags, bounded body &gt;=9, syntax-valid body/protected hashes, and matching SHA256(first 84 bytes); returns total declared size. |
| invariants | Caller must establish ImageLimits.bytes&gt;=157 to avoid subtraction underflow; parse/frame_size do. The body may be absent/incomplete here and is not hashed or parsed. |
| ownership | Borrows immutable input synchronously; changes only private codec preparation. Returned fixed metadata owns its fields. No filesystem or native query state changes. |
| failure | ImageFailure propagates with fixed shared codec diagnostic; MemoryFailure/bad_alloc propagate unchanged. Private preparation unwinds without a partial public result or file mutation. |
| cost | Fixed 148-byte read plus 84-byte hash, no allocation or I/O; records consumed work in the supplied Budget. |
| Design | [include/crown/recovery/local_sink.hpp](../../../../../include/crown/recovery/local_sink.hpp), [docs/local-sink.md](../../../../local-sink.md), [src/recovery/binary_detail.hpp](../../../../../src/recovery/binary_detail.hpp), [src/recovery/local_sink.cpp](../../../../../src/recovery/local_sink.cpp) |

## B0014

[Lines 68–68](../../../../../src/recovery/local_sink_codec.cpp#L68); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L68-L68:sha256:b501d39ce3686e2722bd3aa4e211d50606fb73245aaa68b65ad4932bcb06cdbd
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Design note for adjacent code: Inspect checks canonical bytes; decoded native rows own deep payload copies. This is caller guidance recorded as prose, not an executable result. |
| inputs / outputs | No runtime interface is implemented by these comment-only lines. They sit at src/recovery/local_sink_codec.cpp lines 66-70; the surrounding declaration/body defines its own inputs and outputs. |
| invariants | The words record the intended use boundary only. They do not add a guard, proof, capability, transaction, durability guarantee, or account charge; verify behavior in the referenced implementation. |
| ownership | Comment text owns no data. Object lifetimes, borrows, and account attribution remain those of the adjacent source objects and their constructors. |
| failure | No failure path is implemented here. Any mentioned failure or recovery rule belongs to the adjacent operation and its existing error carrier. |
| cost | No runtime work is performed by these lines; any cost/bound in the note is not certified by this comment-only card. |
| Design | [src/recovery/local_sink_codec.cpp](../../../../../src/recovery/local_sink_codec.cpp), [docs/code_specs/files/src/recovery/local_sink_codec.cpp.md](local_sink_codec.cpp.md), [docs/local-sink.md](../../../../local-sink.md), [docs/journal-files.md](../../../../journal-files.md) |

## B0015

[Lines 69–104](../../../../../src/recovery/local_sink_codec.cpp#L69); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
detail::Inspected parse(std::string_view bytes,std::span<const ScalarType> schema,Budget& budget,Epoch* decoded,const resource::MemoryAccount& account)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Inspect a complete canonical header or epoch, optionally materializing native row ownership. |
| inputs / outputs | Validates both hashes/exact frame length, kind/ordinal, header/schema or positive epoch identity, row count, exact typed scalars, UTF8 strings and strictly increasing serialized row bytes; requires full body consumption. |
| invariants | Canonical order is lexicographic exact operation/arity/scalar wire bytes, not numeric tuple ordering. Equal same-sign rows reject. Epoch parsing expects the File-admitted schema: empty epochs do not independently validate every supplied schema enum/width. File/session match schema hash, epoch continuity and actual program/native output. |
| ownership | Input/schema borrow synchronously. Previous/current row strings point into frame only during comparisons; decoded rows deep-own receiving-account values and retain no frame views. |
| failure | ImageFailure for checksums/structure/schema/scalars/order/resource grants; account faults propagate. Partial Epoch remains private and unwinds without changing file/session. |
| cost | O(frame bytes plus schema width and adjacent row-comparison bytes); fixed hashes and body traversal. Inspection allocates nothing; decode reserves row owners and one reusable descriptor vector, then deep-copies each AccountedRow. |
| Design | [include/crown/recovery/local_sink.hpp](../../../../../include/crown/recovery/local_sink.hpp), [docs/local-sink.md](../../../../local-sink.md), [src/recovery/binary_detail.hpp](../../../../../src/recovery/binary_detail.hpp), [src/recovery/local_sink.cpp](../../../../../src/recovery/local_sink.cpp) |

## B0016

[Lines 105–105](../../../../../src/recovery/local_sink_codec.cpp#L105); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L105-L105:sha256:533f16bca7d58f44b3103b92e3485d22cfbb34bbad5ea3f3fa3b5a9dcb24ec89
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Closes the anonymous namespace at this source boundary; this is a lexical delimiter, not an operation. |
| inputs / outputs | No runtime input or output. Declarations following the span leave the preceding C++ scope. |
| invariants | The delimiter ends the preceding scope's visibility/linkage region; it adds no validation, publication, ownership transfer, or runtime authority. |
| ownership | The delimiter adds no owner. If it ends a function/block with live automatic objects, their normal destructors release those objects; namespace and type-definition closes change no existing object's lifetime. |
| failure | No explicit failure translation or catch is added. If a function/block exit destroys automatic objects, exception behavior follows those destructors; namespace/type closes have no runtime failure path. |
| cost | The delimiter adds no algorithmic work. A function/block exit can run existing automatic-object destructors and cleanup; namespace/type closes have no runtime cost. |
| Design | [src/recovery/local_sink_codec.cpp](../../../../../src/recovery/local_sink_codec.cpp), [docs/code_specs/files/src/recovery/local_sink_codec.cpp.md](local_sink_codec.cpp.md), [docs/local-sink.md](../../../../local-sink.md), [docs/journal-files.md](../../../../journal-files.md) |

## B0017

[Lines 106–110](../../../../../src/recovery/local_sink_codec.cpp#L106); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::array<char,64> schema_sha256(const resource::MemoryAccount& account,std::span<const ScalarType> schema)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Compute the SHA256 identity of the scalar-type tag sequence. |
| inputs / outputs | Validates each ScalarType&lt;=4, copies one byte per type into an account vector and hashes that exact sequence; returns fixed ASCII64 digest. |
| invariants | Only the type list is hashed: no names, table data or native output. This standalone helper has no ImageLimits/work parameter; caller File schema/record/account admission is separate. |
| ownership | Temporary type-tag bytes are receiving-account funded; returned fixed digest owns its characters. |
| failure | ImageFailure on unsupported enum; MemoryFailure/bad_alloc propagate, no returned partial hash. |
| cost | O(schema width) type visits, byte copies and SHA256; temporary account ImageVector capacity of schema width, then released. Not allocation-free. |
| Design | [include/crown/recovery/local_sink.hpp](../../../../../include/crown/recovery/local_sink.hpp), [docs/local-sink.md](../../../../local-sink.md), [src/recovery/local_sink.cpp](../../../../../src/recovery/local_sink.cpp) |

## B0018

[Lines 111–111](../../../../../src/recovery/local_sink_codec.cpp#L111); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L111-L111:sha256:5535809b42b9d97cdfea935b5d84662804aaab9873ce9d79d846ab3ec8a625cb
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Opens the internal sink codec detail namespace for header/epoch encoding, inspection, and decoding helpers. |
| inputs / outputs | No runtime inputs/outputs are declared by the import/scope lines themselves. |
| invariants | The listed headers and namespace membership determine compile-time name availability; any API behavior belongs to the declarations/definitions that follow. |
| ownership | No object ownership is created by the imports or namespace tokens. |
| failure | No runtime failure path. Missing/incompatible dependencies or a violated compile-time constraint fail translation/linking. |
| cost | Compile/preprocessor work only; no new per-operation runtime overhead. |
| Design | [src/recovery/local_sink_codec.cpp](../../../../../src/recovery/local_sink_codec.cpp), [docs/code_specs/files/src/recovery/local_sink_codec.cpp.md](local_sink_codec.cpp.md), [docs/local-sink.md](../../../../local-sink.md), [docs/journal-files.md](../../../../journal-files.md) |

## B0019

[Lines 112–117](../../../../../src/recovery/local_sink_codec.cpp#L112); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Encoded encode_header(const resource::MemoryAccount& account,const Header& header,std::span<const ScalarType> schema,ImageLimits limits)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Encode one complete sink header under record/account grants. |
| inputs / outputs | Checks header/schema and preflights exact frame size, reserves receiving-account final bytes, writes header again and fills protected hashes; returns Encoded bytes/work. |
| invariants | Policy/type validation occurs before final-buffer allocation. Supplied schema hash is not independently derived here; File constructor compares schema_sha256 before invoking this internal codec. |
| ownership | Encoded owns receiving-account final bytes; header/schema are borrowed only through the synchronous call. |
| failure | ImageFailure or account allocation failure propagates; private buffer released, no file publication performed. |
| cost | O(schema width plus fixed header bytes), two serialization passes and body/prefix hashes. Precharged fixed 1024/header and schema work is abstract; one final reserved vector with no row-sort scratch. |
| Design | [include/crown/recovery/local_sink.hpp](../../../../../include/crown/recovery/local_sink.hpp), [docs/local-sink.md](../../../../local-sink.md), [src/recovery/binary_detail.hpp](../../../../../src/recovery/binary_detail.hpp), [src/recovery/local_sink.cpp](../../../../../src/recovery/local_sink.cpp) |

## B0020

[Lines 118–119](../../../../../src/recovery/local_sink_codec.cpp#L118); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L118-L119:sha256:599730401ca95bc68f4de52006c34194737fb442ddd6f7265994a0ec24f7ad19
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Design note for adjacent code: Sort views of complete signed row bytes. Scratch and final bytes overlap under the receiving account until assembly finishes. This is caller guidance recorded as prose, not an executable result. |
| inputs / outputs | No runtime interface is implemented by these comment-only lines. They sit at src/recovery/local_sink_codec.cpp lines 116-121; the surrounding declaration/body defines its own inputs and outputs. |
| invariants | The words record the intended use boundary only. They do not add a guard, proof, capability, transaction, durability guarantee, or account charge; verify behavior in the referenced implementation. |
| ownership | Comment text owns no data. Object lifetimes, borrows, and account attribution remain those of the adjacent source objects and their constructors. |
| failure | No failure path is implemented here. Any mentioned failure or recovery rule belongs to the adjacent operation and its existing error carrier. |
| cost | No runtime work is performed by these lines; any cost/bound in the note is not certified by this comment-only card. |
| Design | [src/recovery/local_sink_codec.cpp](../../../../../src/recovery/local_sink_codec.cpp), [docs/code_specs/files/src/recovery/local_sink_codec.cpp.md](local_sink_codec.cpp.md), [docs/local-sink.md](../../../../local-sink.md), [docs/journal-files.md](../../../../journal-files.md) |

## B0021

[Lines 120–133](../../../../../src/recovery/local_sink_codec.cpp#L120); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Encoded encode_epoch(const resource::MemoryAccount& account,std::uint64_t ordinal,std::uint64_t generation,std::uint64_t sequence,std::span<const RowView> rows,std::span<const ScalarType> schema,ImageLimits limits) {
  require(rows.size()<=limits.rows && schema.size()<=limits.fields,ImageFault::limit);Budget pre{limits};Writer sizing{pre,nullptr};framing(sizing);epoch_prefix(sizing,ordinal,generation,sequence,rows.size());
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Canonicalize and encode one complete output epoch without ordinary Row/string mirrors. |
| inputs / outputs | Preflights all immutable signed row views/schema, materializes row bytes and offset/size segments, sorts segments by exact byte strings, rejects duplicates, then assembles final protected frame. |
| invariants | Rows are not reordered/mutated in caller storage. Supplied schema is File-admitted; an empty epoch does not inspect its enum elements. Canonical bytes include sign, arity and scalar tags/values; opposite signs are distinct. File handles ordinal/base/generation continuity and exact stored-frame replay comparison. |
| ownership | All scratch/final buffers use receiving-account ImageVector; scratch releases after return while Encoded retains only final bytes. Borrowed tuple/schema must stay immutable through both traversals. |
| failure | ImageFailure on invalid/duplicate/oversized/work-limited payload, or account failure during scratch/final allocation. std::sort may leave only private segment order changed; file is untouched. |
| cost | Two scalar serialization/validation passes, O(R log R) row comparisons with per-comparison byte-length charges, adjacent duplicate checks, copy of sorted bytes, body/prefix hashes. Peak includes account segments O(R), complete row bytes and final frame simultaneously; byte limit is not a total heap cap. |
| Design | [include/crown/recovery/local_sink.hpp](../../../../../include/crown/recovery/local_sink.hpp), [docs/local-sink.md](../../../../local-sink.md), [src/recovery/binary_detail.hpp](../../../../../src/recovery/binary_detail.hpp), [src/recovery/local_sink.cpp](../../../../../src/recovery/local_sink.cpp) |

## B0022

[Lines 134–134](../../../../../src/recovery/local_sink_codec.cpp#L134); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Inspected inspect(std::string_view bytes,std::span<const ScalarType> schema,ImageLimits limits)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Expose complete canonical sink frame inspection without owning rows. |
| inputs / outputs | Creates copied ImageLimits Budget and invokes parse with null Epoch destination; returns fixed Inspected. |
| invariants | No allocation, I/O, file continuity check or Receipt authority. Input/schema must remain immutable for the synchronous call. |
| ownership | Borrows immutable input synchronously; changes only private codec preparation. Returned fixed metadata owns its fields. No filesystem or native query state changes. |
| failure | ImageFailure propagates unchanged; no local handler or partial result. |
| cost | Prefix/body SHA256, structural/scalar/UTF8 reads and adjacent serialized-row comparisons; bounded by admitted abstract record work. |
| Design | [include/crown/recovery/local_sink.hpp](../../../../../include/crown/recovery/local_sink.hpp), [docs/local-sink.md](../../../../local-sink.md), [src/recovery/binary_detail.hpp](../../../../../src/recovery/binary_detail.hpp), [src/recovery/local_sink.cpp](../../../../../src/recovery/local_sink.cpp) |

## B0023

[Lines 135–135](../../../../../src/recovery/local_sink_codec.cpp#L135); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L135-L135:sha256:7a42313f9afb01d9f1d3f5c7b20dc01fb715fae83336401e65e85f589ed411e2
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Design note for adjacent code: This path admits two complete parse/checksum passes in one record grant. This is caller guidance recorded as prose, not an executable result. |
| inputs / outputs | No runtime interface is implemented by these comment-only lines. They sit at src/recovery/local_sink_codec.cpp lines 133-137; the surrounding declaration/body defines its own inputs and outputs. |
| invariants | The words record the intended use boundary only. They do not add a guard, proof, capability, transaction, durability guarantee, or account charge; verify behavior in the referenced implementation. |
| ownership | Comment text owns no data. Object lifetimes, borrows, and account attribution remain those of the adjacent source objects and their constructors. |
| failure | No failure path is implemented here. Any mentioned failure or recovery rule belongs to the adjacent operation and its existing error carrier. |
| cost | No runtime work is performed by these lines; any cost/bound in the note is not certified by this comment-only card. |
| Design | [src/recovery/local_sink_codec.cpp](../../../../../src/recovery/local_sink_codec.cpp), [docs/code_specs/files/src/recovery/local_sink_codec.cpp.md](local_sink_codec.cpp.md), [docs/local-sink.md](../../../../local-sink.md), [docs/journal-files.md](../../../../journal-files.md) |

## B0024

[Lines 136–138](../../../../../src/recovery/local_sink_codec.cpp#L136); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Epoch decode(const resource::MemoryAccount& account,std::string_view bytes,std::span<const ScalarType> schema,ImageLimits limits)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Decode one fully validated epoch into receiving-account native rows. |
| inputs / outputs | Runs inspect and requires an epoch, precharges that full inspection work into a second Budget, then reparses/checksums while materializing Epoch. |
| invariants | Shared work limit must cover both complete parse passes; a record can inspect successfully yet fail decode for insufficient remaining work. Repeated checksum/validation is actual existing work, not a single-pass claim. |
| ownership | Returned Epoch and every native row/string byte remain receiving-account owned and usable after input/file/session destruction. |
| failure | ImageFailure rejects header/work/format; MemoryFailure/bad_alloc propagate. Partial receiving Epoch releases on failure without file mutation. |
| cost | Two full prefix/body hashes and structural parses, twice scalar/adjacent comparisons; account row-owner vector, reusable descriptor vector and per-row combined AccountedRow allocations. No full-frame owning copy. |
| Design | [include/crown/recovery/local_sink.hpp](../../../../../include/crown/recovery/local_sink.hpp), [docs/local-sink.md](../../../../local-sink.md), [src/recovery/binary_detail.hpp](../../../../../src/recovery/binary_detail.hpp), [src/recovery/local_sink.cpp](../../../../../src/recovery/local_sink.cpp) |

## B0025

[Lines 139–139](../../../../../src/recovery/local_sink_codec.cpp#L139); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L139-L139:sha256:3a43f53140555ec319f5aa62a8267f1634be231de94c7f8b936e60f7160aac6e
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Design note for adjacent code: Validate protected length without requiring or inspecting the whole body. This is caller guidance recorded as prose, not an executable result. |
| inputs / outputs | No runtime interface is implemented by these comment-only lines. They sit at src/recovery/local_sink_codec.cpp lines 137-141; the surrounding declaration/body defines its own inputs and outputs. |
| invariants | The words record the intended use boundary only. They do not add a guard, proof, capability, transaction, durability guarantee, or account charge; verify behavior in the referenced implementation. |
| ownership | Comment text owns no data. Object lifetimes, borrows, and account attribution remain those of the adjacent source objects and their constructors. |
| failure | No failure path is implemented here. Any mentioned failure or recovery rule belongs to the adjacent operation and its existing error carrier. |
| cost | No runtime work is performed by these lines; any cost/bound in the note is not certified by this comment-only card. |
| Design | [src/recovery/local_sink_codec.cpp](../../../../../src/recovery/local_sink_codec.cpp), [docs/code_specs/files/src/recovery/local_sink_codec.cpp.md](local_sink_codec.cpp.md), [docs/local-sink.md](../../../../local-sink.md), [docs/journal-files.md](../../../../journal-files.md) |

## B0026

[Lines 140–142](../../../../../src/recovery/local_sink_codec.cpp#L140); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::uint64_t frame_size(std::string_view bytes,ImageLimits limits,std::uint64_t& work)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Expose the declared frame size only after protected-header validation. |
| inputs / outputs | Validates minimum record-byte grant, then prefix; assigns work out-parameter only after success and returns declared header+body size. |
| invariants | Does not require body availability, hash the body, check row/schema content or classify a torn tail by itself. File::open supplies complete/incomplete framing policy. |
| ownership | Borrows provided header view synchronously and returns copied numeric metadata. |
| failure | ImageFailure propagates; work out-parameter remains unchanged if prefix rejects. |
| cost | Fixed header/84-byte hash work; constant stack, no allocation or I/O. |
| Design | [include/crown/recovery/local_sink.hpp](../../../../../include/crown/recovery/local_sink.hpp), [docs/local-sink.md](../../../../local-sink.md), [src/recovery/binary_detail.hpp](../../../../../src/recovery/binary_detail.hpp), [src/recovery/local_sink.cpp](../../../../../src/recovery/local_sink.cpp) |

## B0027

[Lines 143–144](../../../../../src/recovery/local_sink_codec.cpp#L143); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L143-L144:sha256:268b60662c3821d37145940e6b0a0ad0e73c9f139e4feb2b18bba6170741db8a
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Closes the sink codec detail namespace and outer sink namespace after the frame-size helper. |
| inputs / outputs | No external runtime input/output is performed by the declaration itself; callable signatures in the block describe future use. |
| invariants | The declaration fixes the source-local names and member/type shape; runtime validation and authority remain with the actual implementations. |
| ownership | No owner is added merely by a declaration. Typed fields keep the ownership behavior of their C++ types and any explicit account allocator. |
| failure | No runtime catch or translation is added here; constructor/member failures remain in their implementation. |
| cost | Declaration-only compile/link work, except that constructing a declared type later may initialize or allocate its members. |
| Design | [src/recovery/local_sink_codec.cpp](../../../../../src/recovery/local_sink_codec.cpp), [docs/code_specs/files/src/recovery/local_sink_codec.cpp.md](local_sink_codec.cpp.md), [docs/local-sink.md](../../../../local-sink.md), [docs/journal-files.md](../../../../journal-files.md) |
