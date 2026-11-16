# `src/recovery/sql_aggregate_checkpoint.cpp` — block usage map

[Source](../../../../../src/recovery/sql_aggregate_checkpoint.cpp) · [Source index](../../../README.md) · [Subsystem contracts](../../../subsystem_contracts.md) · [Reviewed primitives](../../../primitives.md)

Encode, validate and publish checkpoints, journals, generations and local delivery receipts with explicit durable authority.

Snapshot SHA-256: `dab12267d11ec7652fa614d39b6fd46a2ee5830c5b527c2c8c016a54740cf082`. 214 lines partitioned into 29 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [recovery](../../../subsystem_contracts.md#recovery). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/checkpoints.md](../../../../checkpoints.md), [docs/journal.md](../../../../journal.md), [docs/journal-files.md](../../../../journal-files.md), [docs/generations.md](../../../../generations.md), [docs/local-sink.md](../../../../local-sink.md), [docs/history-retirement.md](../../../../history-retirement.md), [docs/update_patterns.md](../../../../update_patterns.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–8](../../../../../src/recovery/sql_aggregate_checkpoint.cpp#L1) | Imports dependencies; declares namespace scope. |  · [reviewed contract](#b0001) |
| [B0002 · 9–13](../../../../../src/recovery/sql_aggregate_checkpoint.cpp#L9) | Type/record definition: struct CheckpointAccess | returns Checkpoint(std::move(bytes),std::move(info)) · [reviewed contract](#b0002) |
| [B0003 · 14–19](../../../../../src/recovery/sql_aggregate_checkpoint.cpp#L14) | declares namespace scope; declares aliases; declares values/defaults or compile-time conditions. | source comment (unverified): // namespace detail · [reviewed contract](#b0003) |
| [B0004 · 20–26](../../../../../src/recovery/sql_aggregate_checkpoint.cpp#L20) | Callable definition: void metadata_valid(const Descriptor& descriptor,const CheckpointMetadata& value) | calls require, bool, hex, sha256; guard require(bool(descriptor),ImageFault::binding); · [reviewed contract](#b0004) |
| [B0005 · 27–29](../../../../../src/recovery/sql_aggregate_checkpoint.cpp#L27) | Callable definition: void reader_valid(const std::optional&lt;ReaderPosition&gt;& reader,std::uint64_t command) | calls require; guard if(reader)require(reader-&gt;records&lt;=command && (reader-&gt;bytes&gt;0 \|\| reader-&gt;records==0)); · [reviewed contract](#b0005) |
| [B0006 · 30–36](../../../../../src/recovery/sql_aggregate_checkpoint.cpp#L30) | Callable definition: auto columns(const Descriptor& descriptor,std::uint64_t table,const CheckpointLimits& limits) | calls program, source_program, sources, require; guard require(sources.size()&lt;=limits.image.tables,ImageFault::limit);; returns result · [reviewed contract](#b0006) |
| [B0007 · 37–40](../../../../../src/recovery/sql_aggregate_checkpoint.cpp#L37) | Callable definition: void name_valid(Budget& budget,std::string_view name,const CheckpointLimits& limits) | calls require, empty, size, charge; guard require(!name.empty() && name.size()&lt;=limits.source_bytes,ImageFault::limit); · [reviewed contract](#b0007) |
| [B0008 · 41–43](../../../../../src/recovery/sql_aggregate_checkpoint.cpp#L41) | Callable definition: bool less(Budget& budget,std::string_view a,std::string_view b) | calls charge, std::min, size; returns a&lt;b · [reviewed contract](#b0008) |
| [B0009 · 44–47](../../../../../src/recovery/sql_aggregate_checkpoint.cpp#L44) | Callable definition: void cell_valid(Budget& budget,const Cell& cell,const frontend::SqlType& type) | calls charge, size, require, frontend::rows_detail::fits; guard require(frontend::rows_detail::fits(cell,type),ImageFault::scalar); · [reviewed contract](#b0009) |
| [B0010 · 48–49](../../../../../src/recovery/sql_aggregate_checkpoint.cpp#L48) | Explanatory comments or spacing. | source comment (unverified): // Cold key scratch contains no ownership handles. Only index is used after its · [reviewed contract](#b0010) |
| [B0011 · 50–50](../../../../../src/recovery/sql_aggregate_checkpoint.cpp#L50) | Type/record definition: struct RowKey | source comment (unverified): // Cold key scratch contains no ownership handles. Only index is used after its · [reviewed contract](#b0011) |
| [B0012 · 51–54](../../../../../src/recovery/sql_aggregate_checkpoint.cpp#L51) | declares types or opens a type body; declares values/defaults or compile-time conditions. |  · [reviewed contract](#b0012) |
| [B0013 · 55–55](../../../../../src/recovery/sql_aggregate_checkpoint.cpp#L55) | Callable definition: void hash(std::span&lt;const char&gt; bytes) | calls require, hex, put, data; guard void hash(std::span&lt;const char&gt; bytes) {require(hex(bytes),ImageFault::binding);put({bytes.data(),b… · [reviewed contract](#b0013) |
| [B0014 · 56–63](../../../../../src/recovery/sql_aggregate_checkpoint.cpp#L56) | Callable definition: void row(const runtime::sql_rows::SourceEntry& entry) | calls require, bool, columns, view; guard budget.row();require(bool(entry.row));const auto types=columns(descriptor,entry.source.value,limits…; 1 loop sites · [reviewed contract](#b0014) |
| [B0015 · 64–88](../../../../../src/recovery/sql_aggregate_checkpoint.cpp#L64) | Callable definition: void frame(const Source& source,const CheckpointMetadata& metadata,const io::AccountedInputProgress& progress, const std::optiona… | calls metadata_valid, require, reader_valid, size; guard metadata_valid(descriptor,metadata);require(source.source.sequence==metadata.physical_sequence &&; 2 loop sites · [reviewed contract](#b0015) |
| [B0016 · 89–98](../../../../../src/recovery/sql_aggregate_checkpoint.cpp#L89) | declares types or opens a type body; declares values/defaults or compile-time conditions. | source comment (unverified): // Inspection uses only transient scalar/string views. Materialization reuses one · [reviewed contract](#b0016) |
| [B0017 · 99–99](../../../../../src/recovery/sql_aggregate_checkpoint.cpp#L99) | Callable definition: bool boolean() | calls integer, require; guard bool boolean() {const auto value=integer(1);require(value&lt;=1);return value!=0;}; returns value!=0 · [reviewed contract](#b0017) |
| [B0018 · 100–102](../../../../../src/recovery/sql_aggregate_checkpoint.cpp#L100) | Callable definition: template&lt;std::size_t N&gt; std::array&lt;char,N&gt; hash() | calls take, std::copy, begin, end; guard std::array&lt;char,N&gt; value{};const auto bytes=take(N);std::copy(bytes.begin(),bytes.end(),value.begin…; returns value · [reviewed contract](#b0018) |
| [B0019 · 103–116](../../../../../src/recovery/sql_aggregate_checkpoint.cpp#L103) | Callable definition: std::string_view row(std::uint64_t table,InspectedCheckpoint& info) | calls columns, size, require, std::max; guard require(count==types.size(),ImageFault::binding);info.max_fields=std::max(info.max_fields,static_ca…; returns input.substr(begin,position-begin); growth push_back; 1 loop sites; source comment (unverified): // Full prior inspection already checked the materializing pass. · [reviewed contract](#b0019) |
| [B0020 · 117–144](../../../../../src/recovery/sql_aggregate_checkpoint.cpp#L117) | Callable definition: InspectedCheckpoint body() | calls integer, metadata_valid, boolean, reader_valid; guard if(i)require(less(budget,previous,name));; returns info; growth copy_of, push_back; 2 loop sites · [reviewed contract](#b0020) |
| [B0021 · 145–145](../../../../../src/recovery/sql_aggregate_checkpoint.cpp#L145) | Closes surrounding scope/type. |  · [reviewed contract](#b0021) |
| [B0022 · 146–156](../../../../../src/recovery/sql_aggregate_checkpoint.cpp#L146) | Callable definition: InspectedCheckpoint inspect(const Descriptor& descriptor,std::string_view bytes,const CheckpointLimits& limits,Budget& budget) | calls require, bool, size, take; guard require(bool(descriptor),ImageFault::binding);require(bytes.size()&lt;=limits.image.bytes,ImageFault::…; returns info · [reviewed contract](#b0022) |
| [B0023 · 157–174](../../../../../src/recovery/sql_aggregate_checkpoint.cpp#L157) | Callable definition: ImageVector&lt;RowKey&gt; order_rows(const resource::MemoryAccount& account,const Descriptor& descriptor,const Source& source, const Ch… | calls require, size, row, packed; guard require(source.source.rows.size()&lt;=limits.image.rows,ImageFault::limit);Output measure{{budget,null…; returns std::string_view(packed.data()+entry.begin,entry.size); x&lt;y \|\| (x==y && less(budget,key(a),key(b))); growth push_back, reserve; 3 loop sites · [reviewed contract](#b0023) |
| [B0024 · 175–184](../../../../../src/recovery/sql_aggregate_checkpoint.cpp#L175) | Callable definition: void source_binding(const Descriptor& descriptor,const Source& source,Budget& budget) | calls require, bool, charge, std::min; guard require(bool(descriptor) && bool(source.program) && bool(source.source.program) && bool(source.sour… · [reviewed contract](#b0024) |
| [B0025 · 185–186](../../../../../src/recovery/sql_aggregate_checkpoint.cpp#L185) | Closes surrounding scope/type. | source comment (unverified): // namespace · [reviewed contract](#b0025) |
| [B0026 · 187–199](../../../../../src/recovery/sql_aggregate_checkpoint.cpp#L187) | Callable definition: Checkpoint encode_checkpoint(const resource::MemoryAccount& account,const Descriptor& descriptor,const Source& source, const Chec… | calls source_binding, order_rows, frame, require; guard require(measure.size&lt;=SIZE_MAX,ImageFault::limit);ImageVector&lt;char&gt; bytes(image_allocator&lt;char&gt;(acc…; returns detail::CheckpointAccess::make(std::move(bytes),std::move(info)); growth reserve; 1 loop sites · [reviewed contract](#b0026) |
| [B0027 · 200–202](../../../../../src/recovery/sql_aggregate_checkpoint.cpp#L200) | Callable definition: InspectedCheckpoint inspect_checkpoint(const Descriptor& descriptor,std::string_view bytes,CheckpointLimits limits) | calls inspect; returns inspect(descriptor,bytes,limits,budget) · [reviewed contract](#b0027) |
| [B0028 · 203–213](../../../../../src/recovery/sql_aggregate_checkpoint.cpp#L203) | Callable definition: RestoredCheckpoint restore_checkpoint_into(const resource::MemoryAccount& account,const Descriptor& descriptor, std::string_view … | calls inspect, require, progress, program; guard Budget budget{limits.image};auto info=inspect(descriptor,bytes,limits,budget);require(info.metadata…; returns {std::move(restored),std::move(progress),info.reader,info.metadata,{bytes.size(),budget.used,budget…; growth reserve · [reviewed contract](#b0028) |
| [B0029 · 214–214](../../../../../src/recovery/sql_aggregate_checkpoint.cpp#L214) | Closes surrounding scope/type. | source comment (unverified): // namespace crown::recovery::sql_aggregate · [reviewed contract](#b0029) |

## B0001

[Lines 1–8](../../../../../src/recovery/sql_aggregate_checkpoint.cpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L1-L8:sha256:b12c08aa6fdaa68f4fc970bcccd2ba63ad09ab829af12c64173bc466d5801efe
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Imports checkpoint, digest, binary budget, SQL cell validation, and algorithm dependencies; opens the aggregate recovery namespace and detail namespace for checkpoint access. |
| inputs / outputs | No runtime inputs/outputs are declared by the import/scope lines themselves. |
| invariants | The listed headers and namespace membership determine compile-time name availability; any API behavior belongs to the declarations/definitions that follow. |
| ownership | No object ownership is created by the imports or namespace tokens. |
| failure | No runtime failure path. Missing/incompatible dependencies or a violated compile-time constraint fail translation/linking. |
| cost | Compile/preprocessor work only; no new per-operation runtime overhead. |
| Design | [src/recovery/sql_aggregate_checkpoint.cpp](../../../../../src/recovery/sql_aggregate_checkpoint.cpp), [docs/code_specs/files/src/recovery/sql_aggregate_checkpoint.cpp.md](sql_aggregate_checkpoint.cpp.md), [docs/sql_aggregate_checkpoint.md](../../../../sql_aggregate_checkpoint.md), [docs/sql_source_images.md](../../../../sql_source_images.md) |

## B0002

[Lines 9–13](../../../../../src/recovery/sql_aggregate_checkpoint.cpp#L9); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct CheckpointAccess
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Privately construct the public Checkpoint after the encoded vector and fixed info are complete. |
| inputs / outputs | Moves ImageVector&lt;char&gt; and InspectedCheckpoint into Checkpoint; no byte copy is requested. |
| invariants | The friend gate is the sole constructor path, preserving a completed-frame invariant for public handles. |
| ownership | Ownership of the backing vector and info transfers into the returned facade; the moved-from source objects remain valid but unspecified. |
| failure | No new error translation; vector/info construction failures propagate. |
| cost | Constant handle moves; backing allocation was already made by encode. |
| Design | [src/recovery/sql_aggregate_checkpoint.cpp](../../../../../src/recovery/sql_aggregate_checkpoint.cpp), [include/crown/recovery/sql_aggregate_checkpoint.hpp](../../../../../include/crown/recovery/sql_aggregate_checkpoint.hpp), [docs/sql_aggregate_checkpoint.md §Lifecycle and ownership](../../../../sql_aggregate_checkpoint.md) |

## B0003

[Lines 14–19](../../../../../src/recovery/sql_aggregate_checkpoint.cpp#L14); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L14-L19:sha256:8a25e966f49dc406bafa9d1363ba2db2b5a8c3e6c0ca8a3ffa1b6cb4f010cfb3
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Closes private CheckpointAccess, opens the anonymous codec namespace, aliases the binary budget, cell, and source snapshot types, and defines the CROWNAC2 frame magic. |
| inputs / outputs | No external runtime input/output is performed by the declaration itself; callable signatures in the block describe future use. |
| invariants | The declaration fixes the source-local names and member/type shape; runtime validation and authority remain with the actual implementations. |
| ownership | No owner is added merely by a declaration. Typed fields keep the ownership behavior of their C++ types and any explicit account allocator. |
| failure | No runtime catch or translation is added here; constructor/member failures remain in their implementation. |
| cost | Declaration-only compile/link work, except that constructing a declared type later may initialize or allocate its members. |
| Design | [src/recovery/sql_aggregate_checkpoint.cpp](../../../../../src/recovery/sql_aggregate_checkpoint.cpp), [docs/code_specs/files/src/recovery/sql_aggregate_checkpoint.cpp.md](sql_aggregate_checkpoint.cpp.md), [docs/sql_aggregate_checkpoint.md](../../../../sql_aggregate_checkpoint.md), [docs/sql_source_images.md](../../../../sql_source_images.md) |

## B0004

[Lines 20–26](../../../../../src/recovery/sql_aggregate_checkpoint.cpp#L20); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void metadata_valid(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Check a checkpoint’s descriptive binding/frontier/delivery tuple against its genuine Descriptor. |
| inputs / outputs | Reads descriptor hash and fixed metadata fields; produces no value. |
| invariants | Requires valid descriptor, lowercase IDs/hashes, nonzero generation, C &lt;= I, delivery sequence=C and positive described extent; it cannot observe a real sink. |
| ownership | All inputs are borrowed values/references; no retained state. |
| failure | Any failed condition raises the codec’s ImageFault::binding path. |
| cost | Fixed number of field/hash checks. |
| Design | [src/recovery/sql_aggregate_checkpoint.cpp](../../../../../src/recovery/sql_aggregate_checkpoint.cpp), [docs/sql_aggregate_checkpoint.md §State and authority](../../../../sql_aggregate_checkpoint.md) |

## B0005

[Lines 27–29](../../../../../src/recovery/sql_aggregate_checkpoint.cpp#L27); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void reader_valid(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Validate optional stream-reader progress against command frontier I. |
| inputs / outputs | Reads optional bytes/records and I; accepts absent reader or checks present position. |
| invariants | records&lt;=I; records&gt;0 requires bytes&gt;0, while zero records may include header bytes. |
| ownership | Only reads the value; no ownership. |
| failure | Invalid position is a wire validation failure. |
| cost | Constant checks. |
| Design | [src/recovery/sql_aggregate_checkpoint.cpp](../../../../../src/recovery/sql_aggregate_checkpoint.cpp), [docs/sql_aggregate_checkpoint.md §State and authority](../../../../sql_aggregate_checkpoint.md) |

## B0006

[Lines 30–36](../../../../../src/recovery/sql_aggregate_checkpoint.cpp#L30); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
auto columns(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Resolve and cap one physical table’s original typed columns from the genuine descriptor. |
| inputs / outputs | Uses numeric TableId, original sources and table/field limits; returns that table’s column schema. |
| invariants | Rejects an out-of-range/mismatched table identity and oversized schema before scalar interpretation. |
| ownership | Returns a schema value/view from immutable program metadata; descriptor outlives the call. |
| failure | Invalid IDs/bounds fail via ImageFault. |
| cost | Fixed span lookup/indexing for the selected table plus bounded field-count checks; no source-row traversal. |
| Design | [src/recovery/sql_aggregate_checkpoint.cpp](../../../../../src/recovery/sql_aggregate_checkpoint.cpp), [docs/sql_aggregate_checkpoint.md §Wire contract](../../../../sql_aggregate_checkpoint.md) |

## B0007

[Lines 37–40](../../../../../src/recovery/sql_aggregate_checkpoint.cpp#L37); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void name_valid(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Validate one progress-source name and charge its UTF8 extent to codec work. |
| inputs / outputs | Takes shared Budget, name bytes and source-name limit; no result. |
| invariants | Name must be nonempty, within \`source_bytes\`, UTF8/text-valid and NUL-free through \`text_fits\`. |
| ownership | Name is a borrowed string_view into the caller map or input frame; no retained copy here. |
| failure | Invalid name or work cap uses ImageFailure. |
| cost | Charges the actual name byte extent then validates those bytes. |
| Design | [src/recovery/sql_aggregate_checkpoint.cpp](../../../../../src/recovery/sql_aggregate_checkpoint.cpp), [docs/sql_aggregate_checkpoint.md §Wire contract](../../../../sql_aggregate_checkpoint.md), [docs/sql_aggregate_checkpoint.md §Limits and cost](../../../../sql_aggregate_checkpoint.md) |

## B0008

[Lines 41–43](../../../../../src/recovery/sql_aggregate_checkpoint.cpp#L41); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
bool less(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Compare ordered source names or canonical row-key slices while accounting selected comparison extent. |
| inputs / outputs | Takes Budget and two string_views; returns bytewise lexicographic order. |
| invariants | Charges min(left size,right size); caller supplies previous/next names or already typed canonical row wire bytes. |
| ownership | Views borrow either input bytes or packed scratch and remain live for comparison only. |
| failure | Budget limit failure stops inspection/encoding. |
| cost | Comparison work bounded by charged common prefix extent. |
| Design | [src/recovery/sql_aggregate_checkpoint.cpp](../../../../../src/recovery/sql_aggregate_checkpoint.cpp), [docs/sql_aggregate_checkpoint.md §Wire contract](../../../../sql_aggregate_checkpoint.md), [docs/sql_aggregate_checkpoint.md §Limits and cost](../../../../sql_aggregate_checkpoint.md) |

## B0009

[Lines 44–47](../../../../../src/recovery/sql_aggregate_checkpoint.cpp#L44); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void cell_valid(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Check a nullable physical cell against its original SQL type and charge retained TEXT extent. |
| inputs / outputs | Takes Budget, Cell and SqlType; does not return a converted value. |
| invariants | Present string_view bytes are charged, then \`rows_detail::fits\` enforces declared type, nullability and scalar domain. |
| ownership | Cell/string storage is borrowed from SourceSnapshot or the unchanged wire buffer; no copy occurs here. |
| failure | Type/domain/extent violations use ImageFailure; work exhaustion stops the pass. |
| cost | One scalar/domain check plus TEXT extent charge where applicable. |
| Design | [src/recovery/sql_aggregate_checkpoint.cpp](../../../../../src/recovery/sql_aggregate_checkpoint.cpp), [docs/sql_aggregate_checkpoint.md §Wire contract](../../../../sql_aggregate_checkpoint.md), [docs/sql_aggregate_checkpoint.md §Limits and cost](../../../../sql_aggregate_checkpoint.md) |

## B0010

[Lines 48–49](../../../../../src/recovery/sql_aggregate_checkpoint.cpp#L48); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L48-L49:sha256:98a6a220545d421343338129f6ac1d1bcd7b8a7518d09512c561d29fd8296739
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Design note for adjacent code: Cold key scratch contains no ownership handles. Only index is used after its packed key buffer dies; encoding borrows the unchanged source rows throughout. This is caller guidance recorded as prose, not an executable result. |
| inputs / outputs | No runtime interface is implemented by these comment-only lines. They sit at src/recovery/sql_aggregate_checkpoint.cpp lines 46-51; the surrounding declaration/body defines its own inputs and outputs. |
| invariants | The words record the intended use boundary only. They do not add a guard, proof, capability, transaction, durability guarantee, or account charge; verify behavior in the referenced implementation. |
| ownership | Comment text owns no data. Object lifetimes, borrows, and account attribution remain those of the adjacent source objects and their constructors. |
| failure | No failure path is implemented here. Any mentioned failure or recovery rule belongs to the adjacent operation and its existing error carrier. |
| cost | No runtime work is performed by these lines; any cost/bound in the note is not certified by this comment-only card. |
| Design | [src/recovery/sql_aggregate_checkpoint.cpp](../../../../../src/recovery/sql_aggregate_checkpoint.cpp), [docs/code_specs/files/src/recovery/sql_aggregate_checkpoint.cpp.md](sql_aggregate_checkpoint.cpp.md), [docs/sql_aggregate_checkpoint.md](../../../../sql_aggregate_checkpoint.md), [docs/sql_source_images.md](../../../../sql_source_images.md) |

## B0011

[Lines 50–50](../../../../../src/recovery/sql_aggregate_checkpoint.cpp#L50); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct RowKey
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Index one physical entry and its packed canonical wire-row slice during encode sorting. |
| inputs / outputs | Stores source-row index plus byte begin/size offsets. |
| invariants | Offsets are used only while the packed key vector remains alive; the scratch record owns no row or bytes. |
| ownership | The account-backed RowKey vector is returned from order_rows and remains live through encode frame measure/write; it is released when encode returns. Offsets are read only while packed key bytes are alive inside order_rows. |
| failure | No independent failure behavior; bounds are established by writer insertion. |
| cost | Fixed-size per-row record, one slot in the temporary index vector. |
| Design | [src/recovery/sql_aggregate_checkpoint.cpp](../../../../../src/recovery/sql_aggregate_checkpoint.cpp), [docs/sql_aggregate_checkpoint.md §Lifecycle and ownership](../../../../sql_aggregate_checkpoint.md) |

## B0012

[Lines 51–54](../../../../../src/recovery/sql_aggregate_checkpoint.cpp#L51); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct Output : Writer {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Hold descriptor/limit references and the transient writer budget/output used by one complete encode pass. |
| inputs / outputs | Carries references to Descriptor and CheckpointLimits, max_fields, and row/frame writer helpers. |
| invariants | The output sink may be null for a measuring pass or point at a temporary packed/frame vector for a writing pass; neither writer persists in Checkpoint. |
| ownership | Only references plus writer state; caller owns referenced descriptor/limits and sink vector. |
| failure | Writer budget/limit checks propagate during measure or write. |
| cost | No independent payload allocation; work/storage are determined by the selected temporary writer sink. |
| Design | [src/recovery/sql_aggregate_checkpoint.cpp](../../../../../src/recovery/sql_aggregate_checkpoint.cpp), [docs/sql_aggregate_checkpoint.md §Lifecycle and ownership](../../../../sql_aggregate_checkpoint.md) |

## B0013

[Lines 55–55](../../../../../src/recovery/sql_aggregate_checkpoint.cpp#L55); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void hash(std::span<const char> bytes)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Validate and emit a fixed lowercase ASCII hexadecimal hash field through the frame writer. |
| inputs / outputs | Accepts a span plus inherited writer; emits those bytes and returns void. |
| invariants | Hash fields are validated before they become frame identity metadata. |
| ownership | Bytes are borrowed during the write; writer output owns the copied representation. |
| failure | Nonhex fields fail binding validation; writer/work failures propagate. |
| cost | Visits a fixed-width field. |
| Design | [src/recovery/sql_aggregate_checkpoint.cpp](../../../../../src/recovery/sql_aggregate_checkpoint.cpp), [docs/sql_aggregate_checkpoint.md §Wire contract](../../../../sql_aggregate_checkpoint.md) |

## B0014

[Lines 56–63](../../../../../src/recovery/sql_aggregate_checkpoint.cpp#L56); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void row(const runtime::sql_rows::SourceEntry& entry)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Write one complete nullable original physical row and validate it against actual schema. |
| inputs / outputs | Reads one SourceEntry and descriptor columns; writes field count, null flags and exact scalar tags to the optional writer. |
| invariants | Field count equals original columns; each cell fits its declared SQL type; max_fields contributes to the fixed InspectedCheckpoint summary; the separate Input parser sizes its restore scratch from its own inspection. |
| ownership | SourceEntry and its tuple are borrowed. Output bytes go to the temporary measure/frame writer, not retained as another row object. |
| failure | Invalid table, row width, type/domain or codec budget fails before publishing a Checkpoint. |
| cost | Linear in cells and selected TEXT extents per pass. |
| Design | [src/recovery/sql_aggregate_checkpoint.cpp](../../../../../src/recovery/sql_aggregate_checkpoint.cpp), [docs/sql_aggregate_checkpoint.md §Wire contract](../../../../sql_aggregate_checkpoint.md), [docs/sql_aggregate_checkpoint.md §Limits and cost](../../../../sql_aggregate_checkpoint.md) |

## B0015

[Lines 64–88](../../../../../src/recovery/sql_aggregate_checkpoint.cpp#L64); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void frame(const Source& source
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Write metadata, C/I progress, ordered source offsets, original table count and canonically ordered physical entries. |
| inputs / outputs | Takes complete source, checkpoint metadata, progress, optional reader and a pre-sorted RowKey span; emits one body. |
| invariants | Source sequence=C and progress.sequence=I; C0 has no rows; source count/table/row bounds hold; table/row key order is strict and weights are positive within multiplicity cap. |
| ownership | Borrows every input, progress name and order index through the measure/write pass; writer owns only the output frame bytes. |
| failure | Any identity, cap, ordering or budget violation prevents handle construction. |
| cost | Traverses metadata, source positions and rows once per measure/write phase; all visits share the operation Budget. |
| Design | [src/recovery/sql_aggregate_checkpoint.cpp](../../../../../src/recovery/sql_aggregate_checkpoint.cpp), [docs/sql_aggregate_checkpoint.md §Wire contract](../../../../sql_aggregate_checkpoint.md), [docs/sql_aggregate_checkpoint.md §Limits and cost](../../../../sql_aggregate_checkpoint.md) |

## B0016

[Lines 89–98](../../../../../src/recovery/sql_aggregate_checkpoint.cpp#L89); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct Input : Reader {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Share the validated byte reader across inspection and second-pass materialization. |
| inputs / outputs | Carries descriptor/limit references and optional pointers to progress, source, reusable Cell vector and receiving account. |
| invariants | Inspection leaves materialization pointers null; restore supplies them only after a full prior inspection and expected-metadata match over unchanged bytes. |
| ownership | Input borrows frame and descriptor for one call; optional output objects live in the caller stack and use receiver ownership. |
| failure | Malformed content, budget exhaustion, account Tuple copy errors and schema failures propagate from the phase that encounters them. |
| cost | One parser object; its optional Cell buffer capacity is reused over rows, while each decoded Tuple is an owning cold copy. |
| Design | [src/recovery/sql_aggregate_checkpoint.cpp](../../../../../src/recovery/sql_aggregate_checkpoint.cpp), [docs/sql_aggregate_checkpoint.md §Lifecycle and ownership](../../../../sql_aggregate_checkpoint.md) |

## B0017

[Lines 99–99](../../../../../src/recovery/sql_aggregate_checkpoint.cpp#L99); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
bool boolean()
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Decode one canonical one-byte Boolean in the frame parser. |
| inputs / outputs | Reads one integer byte and returns false/true. |
| invariants | Only encoded 0 and 1 are accepted; all other byte values are malformed. |
| ownership | Reader borrows the immutable frame input. |
| failure | Malformed values fail ImageFailure before further state is exposed. |
| cost | One byte read. |
| Design | [src/recovery/sql_aggregate_checkpoint.cpp](../../../../../src/recovery/sql_aggregate_checkpoint.cpp), [docs/sql_aggregate_checkpoint.md §Wire contract](../../../../sql_aggregate_checkpoint.md) |

## B0018

[Lines 100–102](../../../../../src/recovery/sql_aggregate_checkpoint.cpp#L100); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
template<std::size_t N> std::array<char,N> hash()
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Read and validate a fixed-width lowercase hexadecimal identity from the input. |
| inputs / outputs | Consumes exactly N bytes, copies into a fixed array and returns it. |
| invariants | No variable allocation; each stored hash field must be lowercase hex before metadata checks proceed. |
| ownership | Returned fixed array is owned by parser/result metadata. |
| failure | Short input or nonhex bytes fail wire/binding validation. |
| cost | Fixed N-byte read/copy. |
| Design | [src/recovery/sql_aggregate_checkpoint.cpp](../../../../../src/recovery/sql_aggregate_checkpoint.cpp), [docs/sql_aggregate_checkpoint.md §Wire contract](../../../../sql_aggregate_checkpoint.md) |

## B0019

[Lines 103–116](../../../../../src/recovery/sql_aggregate_checkpoint.cpp#L103); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::string_view row(std::uint64_t table
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Parse one nullable typed row and return its exact encoded row-key slice. |
| inputs / outputs | Reads declared field count and cells using the actual descriptor schema; optionally appends validated Cells to one reusable materialization vector. |
| invariants | Inspection validates cell domains; materialization relies on the completed prior inspection of unchanged bytes and charges one unit/cell plus each retained TEXT extent. Returned slice includes field count/null/scalar bytes but not table ID or weight. |
| ownership | The slice borrows the unchanged checkpoint input. Cell values borrow scalar bytes until copied into an account-owned Tuple by body(). |
| failure | Malformed row/schema/budget fails before the current physical image can be restored. |
| cost | Linear in fields and value bytes; vector capacity is reused across rows. |
| Design | [src/recovery/sql_aggregate_checkpoint.cpp](../../../../../src/recovery/sql_aggregate_checkpoint.cpp), [docs/sql_aggregate_checkpoint.md §Lifecycle and ownership](../../../../sql_aggregate_checkpoint.md), [docs/sql_aggregate_checkpoint.md §Limits and cost](../../../../sql_aggregate_checkpoint.md) |

## B0020

[Lines 117–144](../../../../../src/recovery/sql_aggregate_checkpoint.cpp#L117); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
InspectedCheckpoint body()
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Parse and validate the complete CROWNAC2 body, optionally producing input progress and physical source rows. |
| inputs / outputs | Reads binding/C/I/delivery/reader, source positions, table and row counts, ordered rows and weights; returns fixed InspectedCheckpoint. |
| invariants | Checks all identities, strict source-name and (TableId,row-wire) ordering, exact table count, domain/weight rules, exact end-of-input; when materializing, fills progress and SourceSnapshot, but final UNIQUE/FK/math validation is deferred to genuine rebuild. |
| ownership | Input/descriptor borrow the wire. Optional progress/source own names/decoded Tuples under receiving account; each Tuple is only a cold temporary before the factory’s complete-copy pass. |
| failure | Image/schema/domain/order failures stop; account or tuple copy failures propagate with caller stack cleanup. |
| cost | One pass over every field and source record; materializing mode reserves one reusable Cell vector and charges row copy units/TEXT extents. |
| Design | [src/recovery/sql_aggregate_checkpoint.cpp](../../../../../src/recovery/sql_aggregate_checkpoint.cpp), [docs/sql_aggregate_checkpoint.md §Lifecycle and ownership](../../../../sql_aggregate_checkpoint.md), [docs/sql_aggregate_checkpoint.md §Limits and cost](../../../../sql_aggregate_checkpoint.md) |

## B0021

[Lines 145–145](../../../../../src/recovery/sql_aggregate_checkpoint.cpp#L145); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L145-L145:sha256:aa1d1a63390229c798347e83a0405441c9400035284ad168c1bf6cdf1d70a370
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Closes the enclosing helper type at this source boundary; this is a lexical delimiter, not an operation. |
| inputs / outputs | No runtime input or output. Declarations following the span leave the preceding C++ scope. |
| invariants | The delimiter ends the preceding scope's visibility/linkage region; it adds no validation, publication, ownership transfer, or runtime authority. |
| ownership | The delimiter adds no owner. If it ends a function/block with live automatic objects, their normal destructors release those objects; namespace and type-definition closes change no existing object's lifetime. |
| failure | No explicit failure translation or catch is added. If a function/block exit destroys automatic objects, exception behavior follows those destructors; namespace/type closes have no runtime failure path. |
| cost | The delimiter adds no algorithmic work. A function/block exit can run existing automatic-object destructors and cleanup; namespace/type closes have no runtime cost. |
| Design | [src/recovery/sql_aggregate_checkpoint.cpp](../../../../../src/recovery/sql_aggregate_checkpoint.cpp), [docs/code_specs/files/src/recovery/sql_aggregate_checkpoint.cpp.md](sql_aggregate_checkpoint.cpp.md), [docs/sql_aggregate_checkpoint.md](../../../../sql_aggregate_checkpoint.md), [docs/sql_source_images.md](../../../../sql_source_images.md) |

## B0022

[Lines 146–156](../../../../../src/recovery/sql_aggregate_checkpoint.cpp#L146); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
InspectedCheckpoint inspect(const Descriptor& descriptor
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Verify complete envelope hashes and parse the full body under one shared codec Budget. |
| inputs / outputs | Takes descriptor, frame bytes and limits by view/reference; returns fixed inspected summary and full-frame hash. |
| invariants | Requires exact magic/version/reserved fields, prefix/body digests, declared body size, valid body and no trailing data. It never constructs a runtime or a source owner. |
| ownership | Frame bytes are borrowed through hashing and parse. Output summary is fixed data only. |
| failure | Malformed header/hash/body or limits fail with ImageFailure; no catch/retry. |
| cost | Hashes prefix/body/full frame and parses full admitted bytes. Successful allocation-free behavior is only under the measured C++ \`new\` seam. |
| Design | [src/recovery/sql_aggregate_checkpoint.cpp](../../../../../src/recovery/sql_aggregate_checkpoint.cpp), [docs/sql_aggregate_checkpoint.md §Lifecycle and ownership](../../../../sql_aggregate_checkpoint.md), [docs/sql_aggregate_checkpoint.md §Limits and cost](../../../../sql_aggregate_checkpoint.md) |

## B0023

[Lines 157–174](../../../../../src/recovery/sql_aggregate_checkpoint.cpp#L157); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
ImageVector<RowKey> order_rows(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Build account-backed temporary canonical physical-row keys and return strict sorted entry indices. |
| inputs / outputs | Measures encoded row lengths, reserves one packed key byte buffer and RowKey vector, writes each row, sorts by numeric table then typed row bytes, and rejects duplicate keys. |
| invariants | Weight is excluded from identity key; duplicate complete physical identities fail even with different weights. Row counter resets between structural passes but shared work budget does not. |
| ownership | The packed key-byte buffer is charged to the image account and dies when this helper returns; its returned RowKey index vector remains alive in encode_checkpoint through frame measure/write, then is released on return. |
| failure | Row caps, work/account limits and duplicates fail before final frame creation. |
| cost | Two O(R) row-key passes plus O(R log R) sorting/duplicate comparisons; packed-byte scratch is O(encoded key bytes), returned index storage O(R). |
| Design | [src/recovery/sql_aggregate_checkpoint.cpp](../../../../../src/recovery/sql_aggregate_checkpoint.cpp), [docs/sql_aggregate_checkpoint.md §Lifecycle and ownership](../../../../sql_aggregate_checkpoint.md), [docs/sql_aggregate_checkpoint.md §Limits and cost](../../../../sql_aggregate_checkpoint.md) |

## B0024

[Lines 175–184](../../../../../src/recovery/sql_aggregate_checkpoint.cpp#L175); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void source_binding(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Require that the supplied mutable SourceSnapshot still represents the Descriptor’s genuine source/native binding. |
| inputs / outputs | Compares authentic SQL binding image, source identity, physical/source hashes and full weighted binding; charges selected bytes/fixed hashes. |
| invariants | Editable snapshot fields cannot substitute an unrelated program or native tree; source rows are separately checked and final constraints remain rebuild responsibility. |
| ownership | Borrows descriptor and source for the call; retains no binding copy. |
| failure | Mismatch fails with ImageFault::binding before row serialization. |
| cost | Compares selected binding-image bytes and fixed hash/binding values. |
| Design | [src/recovery/sql_aggregate_checkpoint.cpp](../../../../../src/recovery/sql_aggregate_checkpoint.cpp), [include/crown/recovery/sql_aggregate_descriptor.hpp](../../../../../include/crown/recovery/sql_aggregate_descriptor.hpp), [docs/sql_aggregate_checkpoint.md §State and authority](../../../../sql_aggregate_checkpoint.md) |

## B0025

[Lines 185–186](../../../../../src/recovery/sql_aggregate_checkpoint.cpp#L185); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L185-L186:sha256:c929980d95efc152dc886ac42af0f045075441dd18a8f886364828ead327bbd3
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Closes the anonymous namespace at this source boundary; this is a lexical delimiter, not an operation. |
| inputs / outputs | No runtime input or output. Declarations following the span leave the preceding C++ scope. |
| invariants | The delimiter ends the preceding scope's visibility/linkage region; it adds no validation, publication, ownership transfer, or runtime authority. |
| ownership | The delimiter adds no owner. If it ends a function/block with live automatic objects, their normal destructors release those objects; namespace and type-definition closes change no existing object's lifetime. |
| failure | No explicit failure translation or catch is added. If a function/block exit destroys automatic objects, exception behavior follows those destructors; namespace/type closes have no runtime failure path. |
| cost | The delimiter adds no algorithmic work. A function/block exit can run existing automatic-object destructors and cleanup; namespace/type closes have no runtime cost. |
| Design | [src/recovery/sql_aggregate_checkpoint.cpp](../../../../../src/recovery/sql_aggregate_checkpoint.cpp), [docs/code_specs/files/src/recovery/sql_aggregate_checkpoint.cpp.md](sql_aggregate_checkpoint.cpp.md), [docs/sql_aggregate_checkpoint.md](../../../../sql_aggregate_checkpoint.md), [docs/sql_source_images.md](../../../../sql_source_images.md) |

## B0026

[Lines 187–199](../../../../../src/recovery/sql_aggregate_checkpoint.cpp#L187); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Checkpoint encode_checkpoint(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Validate, canonically order, encode and account-own one complete CROWNAC2 physical image. |
| inputs / outputs | Consumes supplied image account, genuine descriptor/source, C/I metadata, AccountedInputProgress, optional reader and limits; returns Checkpoint. |
| invariants | Source binding, sequence, schemas, row domains, positive bounded weights, duplicate identities, source order and frame metadata all checked; no group/join/native mirror or sink receipt is encoded. |
| ownership | Input state borrows through the call; returned frame is owned by the image account. The packed key bytes are released before frame allocation, while the RowKey index vector stays live through frame measure/write and is released when encode returns. |
| failure | ImageFailure/account/standard allocation errors propagate without new catches or retry. |
| cost | Two packed-key measure/write traversals, O(R log R) sort and duplicate checks, then two frame row traversals (count/measure and write), source metadata passes, and SHA256 framing under one cumulative byte-work grant. |
| Design | [src/recovery/sql_aggregate_checkpoint.cpp](../../../../../src/recovery/sql_aggregate_checkpoint.cpp), [include/crown/recovery/sql_aggregate_checkpoint.hpp](../../../../../include/crown/recovery/sql_aggregate_checkpoint.hpp), [docs/sql_aggregate_checkpoint.md §Wire contract](../../../../sql_aggregate_checkpoint.md), [docs/sql_aggregate_checkpoint.md §Lifecycle and ownership](../../../../sql_aggregate_checkpoint.md) |

## B0027

[Lines 200–202](../../../../../src/recovery/sql_aggregate_checkpoint.cpp#L200); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
InspectedCheckpoint inspect_checkpoint(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Expose complete bounded wire inspection as the public checkpoint validator. |
| inputs / outputs | Descriptor, immutable byte view and CheckpointLimits in; fixed InspectedCheckpoint out. |
| invariants | Uses only real descriptor schema; no DOM import, runtime construction, sink check or root-selection authority. |
| ownership | Frame view borrowed only during call; output contains no wire spans. |
| failure | Fixed image failure on malformed/over-cap bytes; allocation failures are not caught. |
| cost | Full-frame hashing and one parse; success uses no covered C++ \`new\`, not a global malloc/syscall guarantee. |
| Design | [src/recovery/sql_aggregate_checkpoint.cpp](../../../../../src/recovery/sql_aggregate_checkpoint.cpp), [include/crown/recovery/sql_aggregate_checkpoint.hpp](../../../../../include/crown/recovery/sql_aggregate_checkpoint.hpp), [docs/sql_aggregate_checkpoint.md §Verification boundaries](../../../../sql_aggregate_checkpoint.md) |

## B0028

[Lines 203–213](../../../../../src/recovery/sql_aggregate_checkpoint.cpp#L203); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
RestoredCheckpoint restore_checkpoint_into(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Preflight and then reconstruct a whole physical source image into a fresh receiver. |
| inputs / outputs | Receiving account, Descriptor, frame, expected metadata, RebuildLimits and CheckpointLimits in; runtime/progress/reader/metadata/stats out. |
| invariants | Inspection and exact metadata comparison happen before receiving allocations; complete physical rows are rebuilt once at C through genuine factory, enforcing final source constraints and aggregate arithmetic. |
| ownership | Input wire borrowed through call; receiving progress and decoded rows funded by account. Temporary decode tuples overlap the factory’s live-source copies then die; returned runtime survives input destruction. |
| failure | Wire/metadata failure before materialization; memory, lowering, native, constraint and arithmetic failures propagate and unwind local owners. |
| cost | Full inspect + decode/tuple materialization + actual cold source/native/indexed/group build. Codec work is separate from compiler/build grants and is not CPU cost. |
| Design | [src/recovery/sql_aggregate_checkpoint.cpp](../../../../../src/recovery/sql_aggregate_checkpoint.cpp), [include/crown/recovery/sql_aggregate_checkpoint.hpp](../../../../../include/crown/recovery/sql_aggregate_checkpoint.hpp), [docs/sql_aggregate_checkpoint.md §Lifecycle and ownership](../../../../sql_aggregate_checkpoint.md), [docs/sql_aggregate_checkpoint.md §Limits and cost](../../../../sql_aggregate_checkpoint.md) |

## B0029

[Lines 214–214](../../../../../src/recovery/sql_aggregate_checkpoint.cpp#L214); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L214-L214:sha256:92582b45ad46706cdfae3684126917692713a5a92eff88bf2e3bcc42f5a8da44
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Closes the namespace crown::recovery::sql_aggregate at this source boundary; this is a lexical delimiter, not an operation. |
| inputs / outputs | No runtime input or output. Declarations following the span leave the preceding C++ scope. |
| invariants | The delimiter ends the preceding scope's visibility/linkage region; it adds no validation, publication, ownership transfer, or runtime authority. |
| ownership | The delimiter adds no owner. If it ends a function/block with live automatic objects, their normal destructors release those objects; namespace and type-definition closes change no existing object's lifetime. |
| failure | No explicit failure translation or catch is added. If a function/block exit destroys automatic objects, exception behavior follows those destructors; namespace/type closes have no runtime failure path. |
| cost | The delimiter adds no algorithmic work. A function/block exit can run existing automatic-object destructors and cleanup; namespace/type closes have no runtime cost. |
| Design | [src/recovery/sql_aggregate_checkpoint.cpp](../../../../../src/recovery/sql_aggregate_checkpoint.cpp), [docs/code_specs/files/src/recovery/sql_aggregate_checkpoint.cpp.md](sql_aggregate_checkpoint.cpp.md), [docs/sql_aggregate_checkpoint.md](../../../../sql_aggregate_checkpoint.md), [docs/sql_source_images.md](../../../../sql_source_images.md) |
