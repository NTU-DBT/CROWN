# `src/recovery/sql_rows_checkpoint.cpp` — block usage map

[Source](../../../../../src/recovery/sql_rows_checkpoint.cpp) · [Source index](../../../README.md) · [Subsystem contracts](../../../subsystem_contracts.md) · [Reviewed primitives](../../../primitives.md)

Encode, validate and publish checkpoints, journals, generations and local delivery receipts with explicit durable authority.

Snapshot SHA-256: `3fc4aebf47a0db50fcc3304216042ed577a5b8c92acc29a93d05e98a3df9eefe`. 214 lines partitioned into 29 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [recovery](../../../subsystem_contracts.md#recovery). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/checkpoints.md](../../../../checkpoints.md), [docs/journal.md](../../../../journal.md), [docs/journal-files.md](../../../../journal-files.md), [docs/generations.md](../../../../generations.md), [docs/local-sink.md](../../../../local-sink.md), [docs/history-retirement.md](../../../../history-retirement.md), [docs/update_patterns.md](../../../../update_patterns.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–8](../../../../../src/recovery/sql_rows_checkpoint.cpp#L1) | Imports dependencies; declares namespace scope. |  · [reviewed contract](#b0001) |
| [B0002 · 9–13](../../../../../src/recovery/sql_rows_checkpoint.cpp#L9) | Type/record definition: struct CheckpointAccess | returns Checkpoint(std::move(bytes),std::move(info)) · [reviewed contract](#b0002) |
| [B0003 · 14–19](../../../../../src/recovery/sql_rows_checkpoint.cpp#L14) | declares namespace scope; declares aliases; declares values/defaults or compile-time conditions. | source comment (unverified): // namespace detail · [reviewed contract](#b0003) |
| [B0004 · 20–26](../../../../../src/recovery/sql_rows_checkpoint.cpp#L20) | Callable definition: void metadata_valid(const Descriptor& descriptor,const CheckpointMetadata& value) | calls require, bool, hex, sha256; guard require(bool(descriptor),ImageFault::binding); · [reviewed contract](#b0004) |
| [B0005 · 27–29](../../../../../src/recovery/sql_rows_checkpoint.cpp#L27) | Callable definition: void reader_valid(const std::optional&lt;ReaderPosition&gt;& reader,std::uint64_t command) | calls require; guard if(reader)require(reader-&gt;records&lt;=command && (reader-&gt;bytes&gt;0 \|\| reader-&gt;records==0)); · [reviewed contract](#b0005) |
| [B0006 · 30–36](../../../../../src/recovery/sql_rows_checkpoint.cpp#L30) | Callable definition: auto columns(const Descriptor& descriptor,std::uint64_t table,const CheckpointLimits& limits) | calls program, sources, require, size; guard require(sources.size()&lt;=limits.image.tables,ImageFault::limit);; returns result · [reviewed contract](#b0006) |
| [B0007 · 37–40](../../../../../src/recovery/sql_rows_checkpoint.cpp#L37) | Callable definition: void name_valid(Budget& budget,std::string_view name,const CheckpointLimits& limits) | calls require, empty, size, charge; guard require(!name.empty() && name.size()&lt;=limits.source_bytes,ImageFault::limit); · [reviewed contract](#b0007) |
| [B0008 · 41–43](../../../../../src/recovery/sql_rows_checkpoint.cpp#L41) | Callable definition: bool less(Budget& budget,std::string_view a,std::string_view b) | calls charge, std::min, size; returns a&lt;b · [reviewed contract](#b0008) |
| [B0009 · 44–47](../../../../../src/recovery/sql_rows_checkpoint.cpp#L44) | Callable definition: void cell_valid(Budget& budget,const Cell& cell,const frontend::SqlType& type) | calls charge, size, require, frontend::rows_detail::fits; guard require(frontend::rows_detail::fits(cell,type),ImageFault::scalar); · [reviewed contract](#b0009) |
| [B0010 · 48–49](../../../../../src/recovery/sql_rows_checkpoint.cpp#L48) | Explanatory comments or spacing. | source comment (unverified): // Cold key scratch contains no ownership handles. Only index is used after its · [reviewed contract](#b0010) |
| [B0011 · 50–50](../../../../../src/recovery/sql_rows_checkpoint.cpp#L50) | Type/record definition: struct RowKey | source comment (unverified): // Cold key scratch contains no ownership handles. Only index is used after its · [reviewed contract](#b0011) |
| [B0012 · 51–54](../../../../../src/recovery/sql_rows_checkpoint.cpp#L51) | declares types or opens a type body; declares values/defaults or compile-time conditions. |  · [reviewed contract](#b0012) |
| [B0013 · 55–55](../../../../../src/recovery/sql_rows_checkpoint.cpp#L55) | Callable definition: void hash(std::span&lt;const char&gt; bytes) | calls require, hex, put, data; guard void hash(std::span&lt;const char&gt; bytes) {require(hex(bytes),ImageFault::binding);put({bytes.data(),b… · [reviewed contract](#b0013) |
| [B0014 · 56–63](../../../../../src/recovery/sql_rows_checkpoint.cpp#L56) | Callable definition: void row(const runtime::sql_rows::SourceEntry& entry) | calls require, bool, columns, view; guard budget.row();require(bool(entry.row));const auto types=columns(descriptor,entry.source.value,limits…; 1 loop sites · [reviewed contract](#b0014) |
| [B0015 · 64–88](../../../../../src/recovery/sql_rows_checkpoint.cpp#L64) | Callable definition: void frame(const Source& source,const CheckpointMetadata& metadata,const io::AccountedInputProgress& progress, const std::optiona… | calls metadata_valid, require, reader_valid, size; guard metadata_valid(descriptor,metadata);require(source.sequence==metadata.physical_sequence &&; 2 loop sites · [reviewed contract](#b0015) |
| [B0016 · 89–98](../../../../../src/recovery/sql_rows_checkpoint.cpp#L89) | declares types or opens a type body; declares values/defaults or compile-time conditions. | source comment (unverified): // Inspection uses only transient scalar/string views. Materialization reuses one · [reviewed contract](#b0016) |
| [B0017 · 99–99](../../../../../src/recovery/sql_rows_checkpoint.cpp#L99) | Callable definition: bool boolean() | calls integer, require; guard bool boolean() {const auto value=integer(1);require(value&lt;=1);return value!=0;}; returns value!=0 · [reviewed contract](#b0017) |
| [B0018 · 100–102](../../../../../src/recovery/sql_rows_checkpoint.cpp#L100) | Callable definition: template&lt;std::size_t N&gt; std::array&lt;char,N&gt; hash() | calls take, std::copy, begin, end; guard std::array&lt;char,N&gt; value{};const auto bytes=take(N);std::copy(bytes.begin(),bytes.end(),value.begin…; returns value · [reviewed contract](#b0018) |
| [B0019 · 103–116](../../../../../src/recovery/sql_rows_checkpoint.cpp#L103) | Callable definition: std::string_view row(std::uint64_t table,InspectedCheckpoint& info) | calls columns, size, require, std::max; guard require(count==types.size(),ImageFault::binding);info.max_fields=std::max(info.max_fields,static_ca…; returns input.substr(begin,position-begin); growth push_back; 1 loop sites; source comment (unverified): // Full prior inspection already checked the materializing pass. · [reviewed contract](#b0019) |
| [B0020 · 117–144](../../../../../src/recovery/sql_rows_checkpoint.cpp#L117) | Callable definition: InspectedCheckpoint body() | calls integer, metadata_valid, boolean, reader_valid; guard if(i)require(less(budget,previous,name));; returns info; growth copy_of, push_back; 2 loop sites · [reviewed contract](#b0020) |
| [B0021 · 145–145](../../../../../src/recovery/sql_rows_checkpoint.cpp#L145) | Closes surrounding scope/type. |  · [reviewed contract](#b0021) |
| [B0022 · 146–156](../../../../../src/recovery/sql_rows_checkpoint.cpp#L146) | Callable definition: InspectedCheckpoint inspect(const Descriptor& descriptor,std::string_view bytes,const CheckpointLimits& limits,Budget& budget) | calls require, bool, size, take; guard require(bool(descriptor),ImageFault::binding);require(bytes.size()&lt;=limits.image.bytes,ImageFault::…; returns info · [reviewed contract](#b0022) |
| [B0023 · 157–174](../../../../../src/recovery/sql_rows_checkpoint.cpp#L157) | Callable definition: ImageVector&lt;RowKey&gt; order_rows(const resource::MemoryAccount& account,const Descriptor& descriptor,const Source& source, const Ch… | calls require, size, row, packed; guard require(source.rows.size()&lt;=limits.image.rows,ImageFault::limit);Output measure{{budget,nullptr},de…; returns std::string_view(packed.data()+entry.begin,entry.size); x&lt;y \|\| (x==y && less(budget,key(a),key(b))); growth push_back, reserve; 3 loop sites · [reviewed contract](#b0023) |
| [B0024 · 175–184](../../../../../src/recovery/sql_rows_checkpoint.cpp#L175) | Callable definition: void source_binding(const Descriptor& descriptor,const Source& source,Budget& budget) | calls require, bool, charge, std::min; guard require(bool(descriptor) && bool(source.program) && bool(source.native_program),ImageFault::binding… · [reviewed contract](#b0024) |
| [B0025 · 185–186](../../../../../src/recovery/sql_rows_checkpoint.cpp#L185) | Closes surrounding scope/type. | source comment (unverified): // namespace · [reviewed contract](#b0025) |
| [B0026 · 187–199](../../../../../src/recovery/sql_rows_checkpoint.cpp#L187) | Callable definition: Checkpoint encode_checkpoint(const resource::MemoryAccount& account,const Descriptor& descriptor,const Source& source, const Chec… | calls source_binding, order_rows, frame, require; guard require(measure.size&lt;=SIZE_MAX,ImageFault::limit);ImageVector&lt;char&gt; bytes(image_allocator&lt;char&gt;(acc…; returns detail::CheckpointAccess::make(std::move(bytes),std::move(info)); growth reserve; 1 loop sites · [reviewed contract](#b0026) |
| [B0027 · 200–202](../../../../../src/recovery/sql_rows_checkpoint.cpp#L200) | Callable definition: InspectedCheckpoint inspect_checkpoint(const Descriptor& descriptor,std::string_view bytes,CheckpointLimits limits) | calls inspect; returns inspect(descriptor,bytes,limits,budget) · [reviewed contract](#b0027) |
| [B0028 · 203–213](../../../../../src/recovery/sql_rows_checkpoint.cpp#L203) | Callable definition: RestoredCheckpoint restore_checkpoint_into(const resource::MemoryAccount& account,const Descriptor& descriptor, std::string_view … | calls inspect, require, progress, source; guard Budget budget{limits.image};auto info=inspect(descriptor,bytes,limits,budget);require(info.metadata…; returns {std::move(restored),std::move(progress),info.reader,info.metadata,{bytes.size(),budget.used,budget…; growth reserve · [reviewed contract](#b0028) |
| [B0029 · 214–214](../../../../../src/recovery/sql_rows_checkpoint.cpp#L214) | Closes surrounding scope/type. | source comment (unverified): // namespace crown::recovery::sql_rows · [reviewed contract](#b0029) |

## B0001

[Lines 1–8](../../../../../src/recovery/sql_rows_checkpoint.cpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L1-L8:sha256:98ed9fdb0d746921a59fad7794eed7df3efc967190ad6288d93f0c66ac4abac7
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Include checkpoint implementation dependencies and open detail scope. |
| inputs / outputs | Own checkpoint, digest, binary, SQL value and algorithm declarations become available. |
| invariants | No row/frame/native operation executes here. |
| ownership | No new runtime backing storage from declarations; actual declared views/handles obey their named type lifetimes. |
| failure | Compile-time checking only in this span; invoked member/helper operations have separately specified failures. |
| cost | Include/type/signature/constant declarations only; no executed codec/binder/hash/sort/native work or backing allocation. |
| Design | [src/recovery/sql_rows_checkpoint.cpp](../../../../../src/recovery/sql_rows_checkpoint.cpp) |

## B0002

[Lines 9–13](../../../../../src/recovery/sql_rows_checkpoint.cpp#L9); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L9-L13:sha256:550b0ae14f5433d6b9cc7ede3498247a7d6eadecf100f101b9e0dbacec45b179
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Restrict physical checkpoint construction to validated encoding. |
| inputs / outputs | Funded byte vector and InspectedCheckpoint -&gt; Checkpoint by private constructor. |
| invariants | No validation/hash/parse occurs here; callers must have completed it. |
| ownership | Moves exactly the two supplied members. It retains no separate owner/buffer and does not update any work counter. |
| failure | No intentional validation failure; member move/noexcept rules apply. |
| cost | Fixed ownership/metadata moves or scalar assignment; no explicit allocation/native work. |
| Design | [src/recovery/sql_rows_checkpoint.cpp](../../../../../src/recovery/sql_rows_checkpoint.cpp) |

## B0003

[Lines 14–19](../../../../../src/recovery/sql_rows_checkpoint.cpp#L14); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L14-L19:sha256:4ccc63ead5b0f88875506dde66bca4e7a764585ec0e37b49e177ee656428f69a
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Declare checkpoint helper aliases and CROWNRC2 magic. |
| inputs / outputs | Close detail, open anonymous namespace; import binary helpers and alias Cell/Source. |
| invariants | Wire magic/aliases alone validate no checkpoint. |
| ownership | No new runtime backing storage from declarations; actual declared views/handles obey their named type lifetimes. |
| failure | Compile-time checking only in this span; invoked member/helper operations have separately specified failures. |
| cost | Include/type/signature/constant declarations only; no executed codec/binder/hash/sort/native work or backing allocation. |
| Design | [src/recovery/sql_rows_checkpoint.cpp](../../../../../src/recovery/sql_rows_checkpoint.cpp) |

## B0004

[Lines 20–26](../../../../../src/recovery/sql_rows_checkpoint.cpp#L20); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L20-L26:sha256:ac070135712071ff38707935c58199cd5e27a8a696bab9421741f0b26b44ae5f
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Bind query/descriptor, generation, independent C/I and the described sink delivery anchor; the DTO is not a receipt. |
| inputs / outputs | Descriptor and CheckpointMetadata -&gt; void after presence, query/descriptor identity, generation, C&lt;=I and described delivery-anchor checks. |
| invariants | Requires hex query_id, matching descriptor_sha256, generation&gt;0, C&lt;=I, hex sink_id/content_sha256, delivery.sequence=C and delivery.bytes&gt;0. No actual sink receipt/root/file is observed. |
| ownership | Borrows fixed metadata/Descriptor. |
| failure | ImageFailure(binding) when these fixed consistency checks fail; no work traversal, allocation or catch. |
| cost | Fixed arrays/scalars/handle checks; no row traversal or allocation. |
| Design | [src/recovery/sql_rows_checkpoint.cpp](../../../../../src/recovery/sql_rows_checkpoint.cpp) |

## B0005

[Lines 27–29](../../../../../src/recovery/sql_rows_checkpoint.cpp#L27); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L27-L29:sha256:b978eb6c1aaf86d4f205ee87de01836121b36b059215331c8de11084091dabfd
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Admit independent stream bytes/records with records bounded by disposed command I. |
| inputs / outputs | Optional ReaderPosition+I → void. |
| invariants | Checks records≤I and nonzero bytes unless record count0; no file seek/content/progress monotonicity is checked. |
| ownership | Borrowed optional fixed value. |
| failure | ImageFailure(corrupt) if an engaged reader has records&gt;I or has zero bytes with nonzero records; no catch/mutation. |
| cost | Fixed tests; no allocation/I/O. |
| Design | [src/recovery/sql_rows_checkpoint.cpp](../../../../../src/recovery/sql_rows_checkpoint.cpp) |

## B0006

[Lines 30–36](../../../../../src/recovery/sql_rows_checkpoint.cpp#L30); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L30-L36:sha256:3a8dbe0571feb3f39998b423a61e395ed7ed9455b35eb6b75275cbc90caef4bf
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Resolve the genuine original physical table/columns under receiving schema limits. |
| inputs / outputs | Descriptor, uint64 source table and CheckpointLimits -&gt; borrowed source-column span. |
| invariants | Checks source count cap, in-range original table identity and this table column cap. Caller supplies a genuine Descriptor; no source row or constraint validation here. |
| ownership | Returned columns borrow the genuine program metadata (through Descriptor for checkpoint); this helper creates no storage. |
| failure | ImageFailure(limit) on table/field cap; binding on table identity/index. Descriptor getter rejects empty handle with binding. |
| cost | Fixed indexed/span-size access and explicit cap/index checks; no allocation, column-value traversal or native work. |
| Design | [src/recovery/sql_rows_checkpoint.cpp](../../../../../src/recovery/sql_rows_checkpoint.cpp) |

## B0007

[Lines 37–40](../../../../../src/recovery/sql_rows_checkpoint.cpp#L37); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L37-L40:sha256:b5cdc89efa646d11c7a0816834fa7f8189cec03fd9cbee96b3785061bab1c96f
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Bound and validate nonempty UTF8 source names before owning them. |
| inputs / outputs | Budget/source-name string_view/CheckpointLimits → void. |
| invariants | Checks nonempty admitted extent and SQL UTF8 without NUL; no source progress is published. |
| ownership | Name borrowed; Budget only mutates. |
| failure | ImageFailure(limit) on empty/oversize name, work on byte-charge exhaustion, scalar on invalid UTF8/NUL. No receiving allocation here. |
| cost | Linear name UTF8 bytes plus size checks; no allocation. |
| Design | [src/recovery/sql_rows_checkpoint.cpp](../../../../../src/recovery/sql_rows_checkpoint.cpp) |

## B0008

[Lines 41–43](../../../../../src/recovery/sql_rows_checkpoint.cpp#L41); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L41-L43:sha256:06e69e3712b7754d579fa7e608315f68e0c134c0b0614556cebaaa45bf4b0c27
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Charge the shorter key extent and return its lexical ordering comparison. |
| inputs / outputs | Budget and two string_view keys → Boolean lexical a&lt;b. |
| invariants | Charges min(key lengths) before comparison; does not validate key encoding or uniqueness alone. |
| ownership | Keys borrowed; no retained state beyond Budget.used. |
| failure | ImageFailure(work) if charge fails. |
| cost | Actual lexical comparison up to minimum extent and fixed budget arithmetic; no allocation. |
| Design | [src/recovery/sql_rows_checkpoint.cpp](../../../../../src/recovery/sql_rows_checkpoint.cpp) |

## B0009

[Lines 44–47](../../../../../src/recovery/sql_rows_checkpoint.cpp#L44); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L44-L47:sha256:7bde3299c7a604a2d547b352ba6411ee819ae5c71420609875e1dcef4df04fc4
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Validate full physical NULL/type/domain/TEXT cells and charge validation bytes. |
| inputs / outputs | Budget, optional ScalarView Cell and SqlType → void after fits. |
| invariants | Charges TEXT UTF8 visits; checks only this cell against supplied type, not row identity/constraints. |
| ownership | Cell/text/type borrowed, no retained copy. |
| failure | ImageFailure(work) if TEXT-byte charge fails; ImageFailure(scalar) if this nullable value does not fit the supplied SqlType. |
| cost | Fixed scalar/decimal checks or linear TEXT byte validation; no allocation. |
| Design | [src/recovery/sql_rows_checkpoint.cpp](../../../../../src/recovery/sql_rows_checkpoint.cpp), [src/frontend/sql_rows_value.hpp](../../../../../src/frontend/sql_rows_value.hpp) |

## B0010

[Lines 48–49](../../../../../src/recovery/sql_rows_checkpoint.cpp#L48); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L48-L49:sha256:98a6a220545d421343338129f6ac1d1bcd7b8a7518d09512c561d29fd8296739
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Document the adjacent block boundary. |
| inputs / outputs | Comment/spacing only. |
| invariants | Text is not an executed check or proof. |
| ownership | No ownership operation. |
| failure | No executable failure path. |
| cost | No runtime work/allocation. |
| Design | [src/recovery/sql_rows_checkpoint.cpp](../../../../../src/recovery/sql_rows_checkpoint.cpp) |

## B0011

[Lines 50–50](../../../../../src/recovery/sql_rows_checkpoint.cpp#L50); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L50-L50:sha256:e0bb14c774bbd058ee326b02a67f4a8b5de033fd8c75beb197d4664f91b8fe5c
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Index source rows plus temporary packed key slices for canonical sorting; frame encoding later uses only source indices. |
| inputs / outputs | RowKey contains source-row index, packed-key begin and packed-key size. |
| invariants | Plain offsets/indices only; no bounds, table, type, order or uniqueness check is implemented by the struct. |
| ownership | Does not own source rows or packed key bytes; caller supplies both owners. |
| failure | No executable failure path. |
| cost | Three size_t values; backing index vector allocation belongs to order_rows. |
| Design | [src/recovery/sql_rows_checkpoint.cpp](../../../../../src/recovery/sql_rows_checkpoint.cpp) |

## B0012

[Lines 51–54](../../../../../src/recovery/sql_rows_checkpoint.cpp#L51); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L51-L54:sha256:6c4137aad13c80d1989df9e7b7b3270f304155d5509dfb92c1a229c24c76b3de
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Declare checkpoint Writer context and max-field accumulator. |
| inputs / outputs | Open Output : Writer with borrowed Descriptor/Limits and max_fields initially zero. |
| invariants | No row is read or validated by field declaration; methods perform work later. |
| ownership | No new runtime backing storage from declarations; actual declared views/handles obey their named type lifetimes. |
| failure | Compile-time checking only in this span; invoked member/helper operations have separately specified failures. |
| cost | Include/type/signature/constant declarations only; no executed codec/binder/hash/sort/native work or backing allocation. |
| Design | [src/recovery/sql_rows_checkpoint.cpp](../../../../../src/recovery/sql_rows_checkpoint.cpp) |

## B0013

[Lines 55–55](../../../../../src/recovery/sql_rows_checkpoint.cpp#L55); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L55-L55:sha256:2b7fbabe22e48592479d0c3538c87522c103b280116886a0c4b602d6d80c0bb9
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Validate and append an existing hexadecimal identity span. |
| inputs / outputs | Fixed char span → Writer append after lowercase-hex validation. |
| invariants | Does not compute a hash or authenticate identity. |
| ownership | Span borrowed; Writer.size/Budget advance; a materializing Writer appends to its caller-owned vector and can allocate if capacity is insufficient. A measure Writer owns no output. |
| failure | ImageFailure(binding) for nonhex input; delegated Writer::put can reject byte/work limits or propagate vector allocation. No hash is computed. |
| cost | Fixed-width hex check and actual byte append; no native work. |
| Design | [src/recovery/sql_rows_checkpoint.cpp](../../../../../src/recovery/sql_rows_checkpoint.cpp) |

## B0014

[Lines 56–63](../../../../../src/recovery/sql_rows_checkpoint.cpp#L56); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L56-L63:sha256:5ab9e9b9e9d0bb0bd6e4062cea4d63353f4232ded206bfab126e380e45103169
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Serialize one original physical source row and update maximum field count. |
| inputs / outputs | One SourceEntry -&gt; row-count/width prefix and nullable scalar bytes in Writer, updating max_fields. |
| invariants | Requires an owning row, admitted original source table and exact width/types. It neither checks entry weight nor copies an owning Tuple; frame() handles weight. |
| ownership | Borrow SourceEntry/Tuple/program. Writer size/Budget and max_fields advance; optional output vector is caller-owned. |
| failure | Fixed ImageFailure rejects the stated wire/domain/work checks; this block adds no catch or recovery action. Materializing vector allocation failures propagate. |
| cost | Loop actual physical cells and encoded/validated scalar/TEXT byte extents; measure mode counts, materializing mode writes. No native rebuild, key sort, hash or Tuple allocation. |
| Design | [src/recovery/sql_rows_checkpoint.cpp](../../../../../src/recovery/sql_rows_checkpoint.cpp) |

## B0015

[Lines 64–88](../../../../../src/recovery/sql_rows_checkpoint.cpp#L64); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L64-L88:sha256:684fcddf9317e4c766e1aba3fd42e5539b0e94d3d1710522dca72b6150248b1a
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Serialize CROWNRC2 metadata/progress and canonical positive full physical weights, with no joined/output state mirror. |
| inputs / outputs | Borrowed SourceSnapshot/metadata/progress/reader and canonical source indices → append complete checkpoint fields. |
| invariants | Checks C/I, zero-source C0, described anchor, source names, tables and positive domain weights. Prior source_binding/order checks are caller premises; no runtime rebuild or actual sink validation. |
| ownership | Writer.size/Budget advance; a materializing Writer appends to its caller-owned vector and can allocate if capacity is insufficient. A measure Writer owns no output. Source rows/progress remain borrowed. |
| failure | Fixed ImageFailure rejects the stated wire/domain/work checks; this block adds no catch or recovery action. Output append allocations propagate. |
| cost | Traverse source positions and selected physical entries, type/byte-validate/write them; no key sort/hash/native factory here. |
| Design | [src/recovery/sql_rows_checkpoint.cpp](../../../../../src/recovery/sql_rows_checkpoint.cpp) |

## B0016

[Lines 89–98](../../../../../src/recovery/sql_rows_checkpoint.cpp#L89); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L89-L98:sha256:5e2cf5d73116f2c921e082bbb984db514c75ecda61c160a345d0541371347895
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Declare checkpoint Reader context and optional receiving targets. |
| inputs / outputs | Close Output; open Input : Reader with Descriptor/Limits and nullable progress/source/cells/account pointers. |
| invariants | Null receiving pointers select inspection. Materializing callers must have fully inspected the same bytes before use. |
| ownership | No new runtime backing storage from declarations; actual declared views/handles obey their named type lifetimes. |
| failure | Compile-time checking only in this span; invoked member/helper operations have separately specified failures. |
| cost | Include/type/signature/constant declarations only; no executed codec/binder/hash/sort/native work or backing allocation. |
| Design | [src/recovery/sql_rows_checkpoint.cpp](../../../../../src/recovery/sql_rows_checkpoint.cpp) |

## B0017

[Lines 99–99](../../../../../src/recovery/sql_rows_checkpoint.cpp#L99); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L99-L99:sha256:ea0755dd3813205dc4d0b5d06e37e0b472b748ffcc0ff0c26bd0ab804b6023bd
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Accept only exact zero/one presence/reader flags. |
| inputs / outputs | Reader next byte → Boolean. |
| invariants | Accepts only0/1; no other state is validated. |
| ownership | Reader.position and the shared Budget advance; rejection may retain consumed work but returns no completed parse result. |
| failure | Reader bounded take can throw ImageFailure(corrupt/work); a byte outside0/1 throws corrupt. No allocation/error translation. |
| cost | One bounded byte read; no allocation. |
| Design | [src/recovery/sql_rows_checkpoint.cpp](../../../../../src/recovery/sql_rows_checkpoint.cpp) |

## B0018

[Lines 100–102](../../../../../src/recovery/sql_rows_checkpoint.cpp#L100); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L100-L102:sha256:2e97b7f59c1e69348364218abd8eb2989c5f088fda4eb6a86ebd68ea10fe0218
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Read and check one fixed-width hexadecimal array. |
| inputs / outputs | Reader bytes → fixed-size returned char array after hex validation. |
| invariants | Bounds/hex are checked; no hash is computed. |
| ownership | Copies a fixed array, advances reader/Budget; retains no borrow. |
| failure | Reader bounded take can throw ImageFailure(corrupt/work); nonhex bytes throw binding. No allocation/error translation. |
| cost | Fixed N-byte read/check/copy; no allocation. |
| Design | [src/recovery/sql_rows_checkpoint.cpp](../../../../../src/recovery/sql_rows_checkpoint.cpp) |

## B0019

[Lines 103–116](../../../../../src/recovery/sql_rows_checkpoint.cpp#L103); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L103-L116:sha256:d2d6fcae2a14b86f97833bf5612c481ba4354e4dafb03966b8f3f177057f670c
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Parse one physical source row into borrowed cell views and optionally refill scratch. |
| inputs / outputs | Physical table index and mutable InspectedCheckpoint -&gt; borrowed full row-byte key; max_fields grows and optional Cell scratch is cleared/refilled. |
| invariants | Checks row/field count and table/schema. In inspection mode each cell type is checked; materialization relies on complete prior inspection and charges the later owning copy. This method itself does not allocate a Tuple or rebuild. |
| ownership | Reader position/Budget and max_fields advance. TEXT/key views borrow input; optional vector retains only cell views. |
| failure | Fixed ImageFailure rejects the stated wire/domain/work checks; this block adds no catch or recovery action. Optional vector materialization can allocate if caller reservation is insufficient. |
| cost | Actual scalar decode/type or materializing descriptor-copy/TEXT byte charges; optional scratch pushes use caller capacity. No hash, sort, Tuple allocation or native call. |
| Design | [src/recovery/sql_rows_checkpoint.cpp](../../../../../src/recovery/sql_rows_checkpoint.cpp) |

## B0020

[Lines 117–144](../../../../../src/recovery/sql_rows_checkpoint.cpp#L117); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L117-L144:sha256:8ba24082e69efcca8e2399d1ec419ca648d5c2fd9f12a4f5efd5d6fc9858a2a4
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Inspect canonical source positions and unique complete physical row identities, optionally materializing receiving-owned rows/progress. |
| inputs / outputs | Reader → InspectedCheckpoint; optional progress/source/cell receivers are populated. |
| invariants | Validates metadata, source-name order, table count, canonical unique physical row keys, positive weights and EOF. Does not hash envelope or rebuild native state. |
| ownership | Reader.position and the shared Budget advance; rejection may retain consumed work but returns no completed parse result. In materializing mode source names/Tuples are receiver-owned; rows briefly borrow input before Tuple::copy_of. |
| failure | Fixed ImageFailure rejects the stated wire/domain/work checks; this block adds no catch or recovery action. Materialization can allocate names/rows/tuples through receiver. |
| cost | Linear actual encoded fields/names/key comparisons; materialization copies cells/TEXT and allocates receiving tuples/progress. No sort/native rebuild. |
| Design | [src/recovery/sql_rows_checkpoint.cpp](../../../../../src/recovery/sql_rows_checkpoint.cpp) |

## B0021

[Lines 145–145](../../../../../src/recovery/sql_rows_checkpoint.cpp#L145); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L145-L145:sha256:aa1d1a63390229c798347e83a0405441c9400035284ad168c1bf6cdf1d70a370
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Close the stated namespace/type scope. |
| inputs / outputs | No runtime input or output. |
| invariants | No new checks or state transitions. |
| ownership | No ownership operation. |
| failure | No executable failure path. |
| cost | No runtime work/allocation. |
| Design | [src/recovery/sql_rows_checkpoint.cpp](../../../../../src/recovery/sql_rows_checkpoint.cpp) |

## B0022

[Lines 146–156](../../../../../src/recovery/sql_rows_checkpoint.cpp#L146); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L146-L156:sha256:f8c05ec5fe5aca8da67b56c8c1da087028463307855ad30dfd3193ed74086567
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Validate the exact protected checkpoint envelope and complete typed physical contents before any restoration. |
| inputs / outputs | Genuine Descriptor, borrowed complete bytes, CheckpointLimits and shared Budget -&gt; InspectedCheckpoint. |
| invariants | Verifies family/version/protected length/body/prefix and exact typed payload; checksum/DTO validity grants no native/file authority. |
| ownership | Header/parser views borrow unchanged input for the call. Returned InspectedCheckpoint owns fixed metadata/counts/whole hash/statistics and retains no input slices. |
| failure | Fixed ImageFailure rejects the stated wire/domain/work checks; this block adds no catch or recovery action. |
| cost | Allocation-free full prefix/body/whole-frame hashes and typed checkpoint validation within limits; no native factory, sort or scratch/key allocation. |
| Design | [src/recovery/sql_rows_checkpoint.cpp](../../../../../src/recovery/sql_rows_checkpoint.cpp) |

## B0023

[Lines 157–174](../../../../../src/recovery/sql_rows_checkpoint.cpp#L157); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L157-L174:sha256:14857973474dbc0bc4fec4609cb17f41fdb31ac66089370be9b4e00735182b43
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Sort numeric TableId plus packed nullable row bytes; reject duplicate complete physical identities regardless of weight. |
| inputs / outputs | Account/Descriptor/SourceSnapshot/limits/Budget → canonical RowKey index vector. |
| invariants | Typed-row checks precede key sorting; numeric table plus full row bytes must be strictly unique. Does not validate source binding or constraints/rebuild. |
| ownership | Owns temporary accounted packed keys+indices; packed keys die before return and only source indices are later used. Source rows borrowed/stable. |
| failure | Fixed ImageFailure rejects the stated wire/domain/work checks; this block adds no catch or recovery action. Scratch allocations propagate. |
| cost | Two physical-key serialization passes, O(rows log rows) actual key comparisons and temporary key/index allocation; no frame hash/native work. |
| Design | [src/recovery/sql_rows_checkpoint.cpp](../../../../../src/recovery/sql_rows_checkpoint.cpp) |

## B0024

[Lines 175–184](../../../../../src/recovery/sql_rows_checkpoint.cpp#L175); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L175-L184:sha256:a80dc30e8e3d00fa5fbc4af45d36b21a5389bb7889d25df0723d2b8bfd5cbdbc
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Match actual immutable SQL binding, native source/physical identities and weighted policy before encoding editable source data. |
| inputs / outputs | Descriptor+SourceSnapshot+Budget → void after binding/image/native policy identity equality. |
| invariants | Checks handle presence/full binding and native hashes/weighted binding. Editable physical rows are not semantically validated here. |
| ownership | Borrows metadata only; retains no copy. |
| failure | ImageFailure(binding) on missing/mismatched handles or identity; work on shared Budget debit. No row admission, allocation or catch. |
| cost | Actual full binding comparison plus fixed hash/binding comparisons and budget debits; no allocation/row scan. |
| Design | [src/recovery/sql_rows_checkpoint.cpp](../../../../../src/recovery/sql_rows_checkpoint.cpp) |

## B0025

[Lines 185–186](../../../../../src/recovery/sql_rows_checkpoint.cpp#L185); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L185-L186:sha256:c929980d95efc152dc886ac42af0f045075441dd18a8f886364828ead327bbd3
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Close the stated namespace/type scope. |
| inputs / outputs | No runtime input or output. |
| invariants | No new checks or state transitions. |
| ownership | No ownership operation. |
| failure | No executable failure path. |
| cost | No runtime work/allocation. |
| Design | [src/recovery/sql_rows_checkpoint.cpp](../../../../../src/recovery/sql_rows_checkpoint.cpp) |

## B0026

[Lines 187–199](../../../../../src/recovery/sql_rows_checkpoint.cpp#L187); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L187-L199:sha256:183f05c36d5eda61bfa73640d507431edc874f47edba159e10994d0a363764d0
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Fund a canonical complete physical checkpoint and whole-frame identity after all codec preflight passes. |
| inputs / outputs | Account/Descriptor/full SourceSnapshot/C-I-progress-anchor/limits → owned Checkpoint. |
| invariants | Checks source identity, canonical physical keys and frame metadata/types/domain, then fills length/body/prefix/whole hashes. Does not enforce final native constraints or select files. |
| ownership | Receiving frame/index/key scratch funded here; source/program/progress borrowed and stable for call. |
| failure | Fixed ImageFailure rejects the stated wire/domain/work checks; this block adds no catch or recovery action. Allocation/metadata helper failures propagate; no native publication. |
| cost | Full source/key sort, measure/write/hash passes and actual frame/scratch allocations; no SQL binder/runtime rebuild. |
| Design | [src/recovery/sql_rows_checkpoint.cpp](../../../../../src/recovery/sql_rows_checkpoint.cpp) |

## B0027

[Lines 200–202](../../../../../src/recovery/sql_rows_checkpoint.cpp#L200); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L200-L202:sha256:ae7e9bffa573836498306bd601f224af49a30fa804dea71ea2b2ca678ddcf5dd
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Expose allocation-free checkpoint inspection without native/file authority. |
| inputs / outputs | Descriptor/borrowed frame/limits → InspectedCheckpoint. |
| invariants | Creates a Budget and delegates to the complete allocation-free inspect helper; no restore/receipt authority. |
| ownership | Borrows inputs, returns fixed metadata. |
| failure | Fixed ImageFailure rejects the stated wire/domain/work checks; this block adds no catch or recovery action. |
| cost | Fixed wrapper plus complete delegated bounded frame validation; no allocation/native factory. |
| Design | [src/recovery/sql_rows_checkpoint.cpp](../../../../../src/recovery/sql_rows_checkpoint.cpp) |

## B0028

[Lines 203–213](../../../../../src/recovery/sql_rows_checkpoint.cpp#L203); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L203-L213:sha256:841801c75bab3c73b129f51107568b96932850df21efffd6ce1de3e4e303532a
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Match expected complete metadata before allocation, own all decoded physical rows and call genuine cold rebuild exactly once at C. |
| inputs / outputs | Receiver/Descriptor/bytes/expected metadata/cold build+codec limits → runtime+progress+reader/metadata/statistics. |
| invariants | Complete inspect/expected metadata match precede receiving allocation; then physical rows are owned and genuine rebuild rechecks constraints/arithmetic at C. Does not observe/repair files or validate an actual sink receipt. |
| ownership | Temporary decoded rows and rebuilt rows overlap; returned runtime/progress own receiver storage and no borrow of caller bytes survives. |
| failure | Fixed ImageFailure rejects the stated wire/domain/work checks; this block adds no catch or recovery action. Cold rebuild/constraint/native/account errors propagate; no partially returned owner. |
| cost | Full inspect/materialization/owning copy plus actual genuine cold rebuild with its separate grants. No snapshot of joined/output state is stored. |
| Design | [src/recovery/sql_rows_checkpoint.cpp](../../../../../src/recovery/sql_rows_checkpoint.cpp) |

## B0029

[Lines 214–214](../../../../../src/recovery/sql_rows_checkpoint.cpp#L214); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L214-L214:sha256:5a88989d646de8c904ac4cbcd84db92dc85500003eb77614a29dedc10d8206dd
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Close the stated namespace/type scope. |
| inputs / outputs | No runtime input or output. |
| invariants | No new checks or state transitions. |
| ownership | No ownership operation. |
| failure | No executable failure path. |
| cost | No runtime work/allocation. |
| Design | [src/recovery/sql_rows_checkpoint.cpp](../../../../../src/recovery/sql_rows_checkpoint.cpp) |
