# `src/recovery/sql_rows_records.cpp` — block usage map

[Source](../../../../../src/recovery/sql_rows_records.cpp) · [Source index](../../../README.md) · [Subsystem contracts](../../../subsystem_contracts.md) · [Reviewed primitives](../../../primitives.md)

Encode, validate and publish checkpoints, journals, generations and local delivery receipts with explicit durable authority.

Snapshot SHA-256: `2648f9cf7a4ceece0fa7b4e129fc44b430449971fe73f18ea79ff29683c7f00e`. 398 lines partitioned into 51 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [recovery](../../../subsystem_contracts.md#recovery). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/checkpoints.md](../../../../checkpoints.md), [docs/journal.md](../../../../journal.md), [docs/journal-files.md](../../../../journal-files.md), [docs/generations.md](../../../../generations.md), [docs/local-sink.md](../../../../local-sink.md), [docs/history-retirement.md](../../../../history-retirement.md), [docs/update_patterns.md](../../../../update_patterns.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–9](../../../../../src/recovery/sql_rows_records.cpp#L1) | Imports dependencies; declares namespace scope. | source comment (unverified): // Only validated codec factories construct immutable owned frames/borrow sets. · [reviewed contract](#b0001) |
| [B0002 · 10–19](../../../../../src/recovery/sql_rows_records.cpp#L10) | Type/record definition: struct FrameAccess | returns Frame(std::move(bytes),std::move(info)); DecodedInput(std::move(frame),std::move(cells),std::move(r…; source comment (unverified): // Only validated codec factories construct immutable owned frames/borrow sets. · [reviewed contract](#b0002) |
| [B0003 · 20–27](../../../../../src/recovery/sql_rows_records.cpp#L20) | declares namespace scope; declares aliases; declares values/defaults or compile-time conditions. | source comment (unverified): // namespace detail · [reviewed contract](#b0003) |
| [B0004 · 28–30](../../../../../src/recovery/sql_rows_records.cpp#L28) | Callable definition: void valid(const Binding& value) | calls require, hex; guard require(hex(value.query_id) && hex(value.descriptor_sha256),ImageFault::binding);; source comment (unverified): // Fixed-size metadata validators do not allocate or infer native provenance. · [reviewed contract](#b0004) |
| [B0005 · 31–35](../../../../../src/recovery/sql_rows_records.cpp#L31) | Callable definition: void valid(const WalHeader& value) | calls require, hex; guard require(value.generation&gt;0 && hex(value.checkpoint_sha256) && · [reviewed contract](#b0005) |
| [B0006 · 36–36](../../../../../src/recovery/sql_rows_records.cpp#L36) | Callable definition: void valid(const SinkHeader& value) | calls require, hex; guard void valid(const SinkHeader& value) { valid(value.binding);require(hex(value.sink_id),ImageFault::b… · [reviewed contract](#b0006) |
| [B0007 · 37–41](../../../../../src/recovery/sql_rows_records.cpp#L37) | Callable definition: void valid(const Commit& value) | calls require, hex; guard require(value.input_ordinal&gt;0 && value.physical_sequence&gt;0 && · [reviewed contract](#b0007) |
| [B0008 · 42–46](../../../../../src/recovery/sql_rows_records.cpp#L42) | Callable definition: void valid(const Reject& value) | calls require, hex; guard require(value.input_ordinal&gt;0 && value.physical_sequence&lt;value.command_sequence && · [reviewed contract](#b0008) |
| [B0009 · 47–51](../../../../../src/recovery/sql_rows_records.cpp#L47) | Callable definition: void valid(const RowInfo& value) | calls require, hex; guard require(value.generation&gt;0 && value.physical_sequence&gt;0 && value.physical_sequence&lt;=value.input_seq… · [reviewed contract](#b0009) |
| [B0010 · 52–56](../../../../../src/recovery/sql_rows_records.cpp#L52) | Callable definition: void program_valid(const Program& program,const Limits& limits) | calls require, bool, binding_image, empty; guard require(bool(program),ImageFault::binding); · [reviewed contract](#b0010) |
| [B0011 · 57–57](../../../../../src/recovery/sql_rows_records.cpp#L57) | Explanatory comments or spacing. | source comment (unverified): // The genuine source/output supply SqlTypes without allocating a schema copy. · [reviewed contract](#b0011) |
| [B0012 · 58–62](../../../../../src/recovery/sql_rows_records.cpp#L58) | Callable definition: auto source_columns(const Program& program,std::uint64_t table) | calls sources, require, size; guard require(table&lt;sources.size() && sources\[static_cast&lt;std::size_t&gt;(table)\].table.value==table,ImageFa…; returns sources\[static_cast&lt;std::size_t&gt;(table)\].columns; source comment (unverified): // The genuine source/output supply SqlTypes without allocating a schema copy. · [reviewed contract](#b0012) |
| [B0013 · 63–63](../../../../../src/recovery/sql_rows_records.cpp#L63) | Callable definition: std::size_t fields(const Program& program) | calls outputs, size; returns program.outputs().size() · [reviewed contract](#b0013) |
| [B0014 · 64–64](../../../../../src/recovery/sql_rows_records.cpp#L64) | Callable definition: frontend::SqlType field_type(const Program& program,std::size_t i) | calls outputs; returns program.outputs()\[i\].type · [reviewed contract](#b0014) |
| [B0015 · 65–69](../../../../../src/recovery/sql_rows_records.cpp#L65) | Callable definition: void cell_valid(Budget& budget,const Cell& cell,const frontend::SqlType& type) | calls charge, size, require, frontend::rows_detail::fits; guard require(frontend::rows_detail::fits(cell,type),ImageFault::scalar);; source comment (unverified): // UTF8 pass in fits. · [reviewed contract](#b0015) |
| [B0016 · 70–72](../../../../../src/recovery/sql_rows_records.cpp#L70) | Callable definition: bool ordered(Budget& budget,std::string_view a,std::string_view b) | calls charge, std::min, size; returns a&lt;b · [reviewed contract](#b0016) |
| [B0017 · 73–73](../../../../../src/recovery/sql_rows_records.cpp#L73) | Type/record definition: struct KeySlice |  · [reviewed contract](#b0017) |
| [B0018 · 74–79](../../../../../src/recovery/sql_rows_records.cpp#L74) | Type/record definition: struct EncodedRows |  · [reviewed contract](#b0018) |
| [B0019 · 80–88](../../../../../src/recovery/sql_rows_records.cpp#L80) | Callable definition: void constant_valid(Budget& budget,const Program& program,std::size_t i,const Cell& cell) | calls outputs, initial_values, charge, std::min; guard require(cell==expected,ImageFault::scalar); · [reviewed contract](#b0019) |
| [B0020 · 89–93](../../../../../src/recovery/sql_rows_records.cpp#L89) | Callable definition: void change_valid(const Program& program,const runtime::weighted::SignedMagnitude& change) | calls require, semantics, wrapper; guard require(change.magnitude.value&gt;0,ImageFault::scalar); · [reviewed contract](#b0020) |
| [B0021 · 94–102](../../../../../src/recovery/sql_rows_records.cpp#L94) | declares types or opens a type body; declares values/defaults or compile-time conditions. | source comment (unverified): // Count-only and materializing passes share validation and byte/work admissions. · [reviewed contract](#b0021) |
| [B0022 · 103–105](../../../../../src/recovery/sql_rows_records.cpp#L103) | Callable definition: void hash(std::span&lt;const char&gt; value) | calls require, hex, put, data; guard require(hex(value),ImageFault::binding);put({value.data(),value.size()}); · [reviewed contract](#b0022) |
| [B0023 · 106–113](../../../../../src/recovery/sql_rows_records.cpp#L106) | Callable definition: template&lt;class TypeAt&gt; void row(std::span&lt;const Cell&gt; cells,std::size_t expected,TypeAt type_at) | calls require, size, integer, cell_valid; guard budget.row();require(cells.size()==expected,ImageFault::binding);; 1 loop sites · [reviewed contract](#b0023) |
| [B0024 · 114–117](../../../../../src/recovery/sql_rows_records.cpp#L114) | Callable definition: void output_row(std::span&lt;const Cell&gt; cells) | calls row, fields, field_type, size; returns field_type(program,i); 1 loop sites · [reviewed contract](#b0024) |
| [B0025 · 118–121](../../../../../src/recovery/sql_rows_records.cpp#L118) | Callable definition: void write(const WalHeader& value) | calls valid, hash, integer · [reviewed contract](#b0025) |
| [B0026 · 122–124](../../../../../src/recovery/sql_rows_records.cpp#L122) | Callable definition: void write(const SinkHeader& value) | calls valid, hash, integer · [reviewed contract](#b0026) |
| [B0027 · 125–149](../../../../../src/recovery/sql_rows_records.cpp#L125) | Callable definition: void write(const InputView& value) | calls require, integer, size, source_columns; guard require(value.command_sequence&gt;0);integer(value.command_sequence,8);; returns columns\[i\].type; 1 loop sites; source comment (unverified): // Arithmetic/constraints belong to native prepare. · [reviewed contract](#b0027) |
| [B0028 · 150–154](../../../../../src/recovery/sql_rows_records.cpp#L150) | Callable definition: void write(const Commit& value) | calls valid, integer, hash · [reviewed contract](#b0028) |
| [B0029 · 155–158](../../../../../src/recovery/sql_rows_records.cpp#L155) | Callable definition: void write(const Reject& value) | calls valid, integer, hash · [reviewed contract](#b0029) |
| [B0030 · 159–169](../../../../../src/recovery/sql_rows_records.cpp#L159) | Callable definition: void write(const RowEpochView& value) | calls require, size, valid, integer; guard require(encoded!=nullptr,ImageFault::binding);const auto count=encoded-&gt;order.size();; 1 loop sites · [reviewed contract](#b0030) |
| [B0031 · 170–189](../../../../../src/recovery/sql_rows_records.cpp#L170) | Callable definition: Inspected frame(std::uint64_t ordinal,const PayloadView& payload) | calls index, require, put, integer; guard require((kind==Kind::wal_header \|\| kind==Kind::sink_header)==(ordinal==0));; returns result · [reviewed contract](#b0031) |
| [B0032 · 190–198](../../../../../src/recovery/sql_rows_records.cpp#L190) | declares types or opens a type body; declares values/defaults or compile-time conditions. | source comment (unverified): // Parser borrows bytes. Null output pointers keep inspection allocation-free; · [reviewed contract](#b0032) |
| [B0033 · 199–199](../../../../../src/recovery/sql_rows_records.cpp#L199) | Callable definition: bool boolean() | calls integer, require; guard bool boolean() { const auto value=integer(1);require(value&lt;=1);return value!=0; }; returns value!=0 · [reviewed contract](#b0033) |
| [B0034 · 200–203](../../../../../src/recovery/sql_rows_records.cpp#L200) | Callable definition: template&lt;std::size_t N&gt; std::array&lt;char,N&gt; hash() | calls take, std::copy, begin, end; guard std::copy(text.begin(),text.end(),result.begin());require(hex(result),ImageFault::binding);return r…; returns result · [reviewed contract](#b0034) |
| [B0035 · 204–204](../../../../../src/recovery/sql_rows_records.cpp#L204) | Callable definition: Binding binding() | calls ; returns {hash&lt;32&gt;(),hash&lt;64&gt;()} · [reviewed contract](#b0035) |
| [B0036 · 205–213](../../../../../src/recovery/sql_rows_records.cpp#L205) | Callable definition: template&lt;class TypeAt&gt; std::string_view row(std::size_t expected,TypeAt type_at) | calls size, require, boolean, binary_detail::scalar; guard require(count==expected,ImageFault::binding);; returns input.substr(start,position-start); growth push_back; 1 loop sites · [reviewed contract](#b0036) |
| [B0037 · 214–237](../../../../../src/recovery/sql_rows_records.cpp#L214) | Callable definition: InputInfo item() | calls integer, require, size, source_columns; guard InputInfo value;value.command_sequence=integer(8);require(value.command_sequence&gt;0);; returns columns\[j\].type; value; growth push_back; 1 loop sites; source comment (unverified): // Even zero-column replacements need table/field-count/before/after words. · [reviewed contract](#b0037) |
| [B0038 · 238–266](../../../../../src/recovery/sql_rows_records.cpp#L238) | Callable definition: RowInfo rows() | calls integer, boolean, size, valid; guard if(program.wrapper()==frontend::SqlWrapper::exists)require(value.rows==0 \|\| value.rows==2);; returns value; 2 loop sites; source comment (unverified): // Parse one typed row inline: inspection uses no row-sized allocation. · [reviewed contract](#b0038) |
| [B0039 · 267–289](../../../../../src/recovery/sql_rows_records.cpp#L267) | Callable definition: Inspected body() | calls integer, require, binding, valid; guard const auto tag=integer(1);require(tag&lt;=static_cast&lt;unsigned&gt;(Kind::row_epoch));; returns value · [reviewed contract](#b0039) |
| [B0040 · 290–293](../../../../../src/recovery/sql_rows_records.cpp#L290) | Closes surrounding scope/type. | source comment (unverified): // Protect the length before using it. Exact frames reject trailing bytes; · [reviewed contract](#b0040) |
| [B0041 · 294–306](../../../../../src/recovery/sql_rows_records.cpp#L294) | Callable definition: Inspected inspect_frame(const Program& program,std::string_view bytes,const Limits& limits,Budget& budget) | calls program_valid, require, size, take; guard program_valid(program,limits);require(bytes.size()&lt;=limits.record.bytes,ImageFault::limit);; returns info; source comment (unverified): // Protect the length before using it. Exact frames reject trailing bytes; · [reviewed contract](#b0041) |
| [B0042 · 307–309](../../../../../src/recovery/sql_rows_records.cpp#L307) | Explanatory comments or spacing. | source comment (unverified): // Decode genuine SQL output once into one borrowed scratch row. Retain packed · [reviewed contract](#b0042) |
| [B0043 · 310–342](../../../../../src/recovery/sql_rows_records.cpp#L310) | Callable definition: EncodedRows output_rows(const resource::MemoryAccount& account,const Program& program, const PayloadView& payload,const Limits& l… | calls result, require, active, output_size; guard require(epoch-&gt;output && epoch-&gt;output-&gt;active(),ImageFault::binding);; returns result; std::string_view(result.keys.data()+item.begin,item.size); growth push_back, reserve, resize; 2 loop sites; source comment (unverified): // Decode genuine SQL output once into one borrowed scratch row. Retain packed · [reviewed contract](#b0043) |
| [B0044 · 343–344](../../../../../src/recovery/sql_rows_records.cpp#L343) | Closes surrounding scope/type. | source comment (unverified): // namespace · [reviewed contract](#b0044) |
| [B0045 · 345–360](../../../../../src/recovery/sql_rows_records.cpp#L345) | Callable definition: Frame encode(const resource::MemoryAccount& account,const Program& program,std::uint64_t ordinal, const PayloadView& payload,Limi… | calls program_valid, output_rows, frame, require; guard require(measure.size&lt;=SIZE_MAX,ImageFault::limit);ImageVector&lt;char&gt; bytes(image_allocator&lt;char&gt;(acc…; returns detail::FrameAccess::frame(std::move(bytes),std::move(info)); growth reserve; 1 loop sites · [reviewed contract](#b0045) |
| [B0046 · 361–363](../../../../../src/recovery/sql_rows_records.cpp#L361) | Callable definition: Inspected inspect(const Program& program,std::string_view bytes,Limits limits) | calls inspect_frame; returns inspect_frame(program,bytes,limits,budget) · [reviewed contract](#b0046) |
| [B0047 · 364–376](../../../../../src/recovery/sql_rows_records.cpp#L364) | Callable definition: DecodedInput decode_input(const resource::MemoryAccount& account,const Program& program, std::string_view bytes,Limits limits) | calls inspect_frame, require, charge, size; guard Budget budget{limits.record};auto info=inspect_frame(program,bytes,limits,budget);require(info.kind…; returns detail::FrameAccess::input(detail::FrameAccess::frame(std::move(owned),std::move(info)),; growth reserve · [reviewed contract](#b0047) |
| [B0048 · 377–389](../../../../../src/recovery/sql_rows_records.cpp#L377) | Callable definition: DecodedInput encode_input(const resource::MemoryAccount& account,const Program& program, std::uint64_t ordinal,const InputView& v… | calls encode, info, require, cells; guard const auto metadata=std::get&lt;InputInfo&gt;(frame.info().payload);require(metadata.cells&lt;=SIZE_MAX,Imag…; returns detail::FrameAccess::input(std::move(frame),std::move(cells),std::move(replacements)); growth reserve; source comment (unverified): // The encoded frame is already owned; only flat views are materialized here. · [reviewed contract](#b0048) |
| [B0049 · 390–392](../../../../../src/recovery/sql_rows_records.cpp#L390) | Callable definition: DecodedInput::DecodedInput(Frame frame,ImageVector&lt;Cell&gt; cells, ImageVector&lt;runtime::sql_rows::SourceReplacement&gt; replacements) n… | calls frame_, std::move, cells_, replacements_ · [reviewed contract](#b0049) |
| [B0050 · 393–397](../../../../../src/recovery/sql_rows_records.cpp#L393) | Callable definition: InputView DecodedInput::view() const & | calls info, bytes, substr; returns {info.command_sequence,replacements_,source,info.reader} · [reviewed contract](#b0050) |
| [B0051 · 398–398](../../../../../src/recovery/sql_rows_records.cpp#L398) | Closes surrounding scope/type. | source comment (unverified): // namespace crown::recovery::sql_rows · [reviewed contract](#b0051) |

## B0001

[Lines 1–9](../../../../../src/recovery/sql_rows_records.cpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L1-L9:sha256:6d869de67c1e53fef533604d7344e91431041915e293feee785f01c80b989cbf
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Include record implementation dependencies and open detail namespace. |
| inputs / outputs | Include row records, fixed digest, binary helpers, SQL value validation and algorithm declarations. |
| invariants | Includes/namespaces execute no codec/native work. |
| ownership | No new runtime backing storage from declarations; actual declared views/handles obey their named type lifetimes. |
| failure | Compile-time checking only in this span; invoked member/helper operations have separately specified failures. |
| cost | Include/type/signature/constant declarations only; no executed codec/binder/hash/sort/native work or backing allocation. |
| Design | [src/recovery/sql_rows_records.cpp](../../../../../src/recovery/sql_rows_records.cpp) |

## B0002

[Lines 10–19](../../../../../src/recovery/sql_rows_records.cpp#L10); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L10-L19:sha256:822889576ba22bb94e49a0f3b0dbd82086e07e763b11602c2d48e1467dc99f31
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Restrict immutable frame/flat-view construction to the validated record factories. |
| inputs / outputs | Static helpers move already funded bytes/metadata/flat vectors into private constructors; FrameAccess also assigns stored work. |
| invariants | No validation/hash/parse occurs here; callers must have completed it. |
| ownership | Moves given owners; stored work update is scalar. No extra owner/storage is created. |
| failure | No intentional validation failure; member move/noexcept rules apply. |
| cost | Fixed ownership/metadata moves or scalar assignment; no explicit allocation/native work. |
| Design | [src/recovery/sql_rows_records.cpp](../../../../../src/recovery/sql_rows_records.cpp) |

## B0003

[Lines 20–27](../../../../../src/recovery/sql_rows_records.cpp#L20); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L20-L27:sha256:b47774447aa825026b190ceaa8c558f8b60d3ed58b36bfaea82a93754e22fdcc
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Declare local record aliases and CROWNRW2 magic. |
| inputs / outputs | Close detail, open anonymous namespace and alias binary helpers, Cell, Program; set wire magic. |
| invariants | Constants/aliases alone validate no frame. |
| ownership | No new runtime backing storage from declarations; actual declared views/handles obey their named type lifetimes. |
| failure | Compile-time checking only in this span; invoked member/helper operations have separately specified failures. |
| cost | Include/type/signature/constant declarations only; no executed codec/binder/hash/sort/native work or backing allocation. |
| Design | [src/recovery/sql_rows_records.cpp](../../../../../src/recovery/sql_rows_records.cpp) |

## B0004

[Lines 28–30](../../../../../src/recovery/sql_rows_records.cpp#L28); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L28-L30:sha256:0776281a5d89dfe5c9924587c69d9c34b7ccb3e4224293a313d1cf64a9483082
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Check the fixed query ID and descriptor hash are lowercase hexadecimal. |
| inputs / outputs | Const Binding reference -&gt; void after checks. |
| invariants | Ensures only hex(query_id) and hex(descriptor_sha256). It does not inspect an actual frame, program, native state or file. |
| ownership | Borrows one fixed value; retains nothing. |
| failure | ImageFailure(binding) when the stated fixed identity/frontier conditions fail; no catch or mutation. |
| cost | Fixed-width scalar/hex checks; no allocation or payload/native work. |
| Design | [src/recovery/sql_rows_records.cpp](../../../../../src/recovery/sql_rows_records.cpp) |

## B0005

[Lines 31–35](../../../../../src/recovery/sql_rows_records.cpp#L31); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L31-L35:sha256:32e813b67c20c79672785d8468353e5d5b42be905db32f35ca8f0ac41aab4d6b
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Check a WAL header binding, generation, checkpoint hash and C&lt;=I. |
| inputs / outputs | Const WalHeader reference -&gt; void after checks. |
| invariants | Ensures only valid(binding), generation&gt;0, hex(checkpoint_sha256) and C&lt;=I. It does not inspect an actual frame, program, native state or file. |
| ownership | Borrows one fixed value; retains nothing. |
| failure | ImageFailure(binding) when the stated fixed identity/frontier conditions fail; no catch or mutation. |
| cost | Fixed-width scalar/hex checks; no allocation or payload/native work. |
| Design | [src/recovery/sql_rows_records.cpp](../../../../../src/recovery/sql_rows_records.cpp) |

## B0006

[Lines 36–36](../../../../../src/recovery/sql_rows_records.cpp#L36); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L36-L36:sha256:5a7417e16dbe3b7b690b2c8c2edea17278b32a83e2091beaf38c12b06663cf8b
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Check a sink header binding and sink ID. |
| inputs / outputs | Const SinkHeader reference -&gt; void after checks. |
| invariants | Ensures only valid(binding) and hex(sink_id). It does not inspect an actual frame, program, native state or file. |
| ownership | Borrows one fixed value; retains nothing. |
| failure | ImageFailure(binding) when the stated fixed identity/frontier conditions fail; no catch or mutation. |
| cost | Fixed-width scalar/hex checks; no allocation or payload/native work. |
| Design | [src/recovery/sql_rows_records.cpp](../../../../../src/recovery/sql_rows_records.cpp) |

## B0007

[Lines 37–41](../../../../../src/recovery/sql_rows_records.cpp#L37); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L37-L41:sha256:54f59dfebe462d23747f2a85fc5b61ee411cec47bbba4b5edd314779e043b2a3
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Check a Commit input reference, positive C&lt;=I, minimum output frame size and hashes. |
| inputs / outputs | Const Commit reference -&gt; void after checks. |
| invariants | Ensures only input_ordinal&gt;0, 0&lt;C&lt;=I, output_bytes&gt;=255 and both lowercase-hex hashes. It does not inspect an actual frame, program, native state or file. |
| ownership | Borrows one fixed value; retains nothing. |
| failure | ImageFailure(corrupt) for stated ordinal/frontier/count/flag/reason conditions, or binding for invalid hexadecimal identity; no catch/mutation. |
| cost | Fixed-width scalar/hex checks; no allocation or payload/native work. |
| Design | [src/recovery/sql_rows_records.cpp](../../../../../src/recovery/sql_rows_records.cpp) |

## B0008

[Lines 42–46](../../../../../src/recovery/sql_rows_records.cpp#L42); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L42-L46:sha256:eb5b4dbeee21f52bab9ad78ae50ce11d2b5a5b5bf100e8def07acec57ba715d5
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Check a Reject input reference, C&lt;I, allowed reason and input hash. |
| inputs / outputs | Const Reject reference -&gt; void after checks. |
| invariants | Ensures only input_ordinal&gt;0, C&lt;I, reason&lt;=annotation_overflow and lowercase-hex input hash. It does not inspect an actual frame, program, native state or file. |
| ownership | Borrows one fixed value; retains nothing. |
| failure | ImageFailure(corrupt) for stated ordinal/frontier/count/flag/reason conditions, or binding for invalid hexadecimal identity; no catch/mutation. |
| cost | Fixed-width scalar/hex checks; no allocation or payload/native work. |
| Design | [src/recovery/sql_rows_records.cpp](../../../../../src/recovery/sql_rows_records.cpp) |

## B0009

[Lines 47–51](../../../../../src/recovery/sql_rows_records.cpp#L47); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L47-L51:sha256:e9e36f49bdd5ab0ef3a7ab4488082fb156a82ca04f8be23e36ceeb92e6f9746d
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Check epoch generation/C/I, count/change consistency and input hash. |
| inputs / outputs | Const RowInfo reference -&gt; void after checks. |
| invariants | Ensures only generation&gt;0, 0&lt;C&lt;=I, output_changed==(rows!=0), output_changed implies changed and lowercase-hex input hash. It does not inspect an actual frame, program, native state or file. |
| ownership | Borrows one fixed value; retains nothing. |
| failure | ImageFailure(corrupt) for stated ordinal/frontier/count/flag/reason conditions, or binding for invalid hexadecimal identity; no catch/mutation. |
| cost | Fixed-width scalar/hex checks; no allocation or payload/native work. |
| Design | [src/recovery/sql_rows_records.cpp](../../../../../src/recovery/sql_rows_records.cpp) |

## B0010

[Lines 52–56](../../../../../src/recovery/sql_rows_records.cpp#L52); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L52-L56:sha256:c786ab1368a3ec9211f11d0b1c212c5b167477558367b50a3f79ca7f9fd39d22
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Require a genuine program with retained durable binding bytes and admitted source count. |
| inputs / outputs | Program+record Limits → void after handle/source table count checks. |
| invariants | Checks genuine handle presence, nonempty binding_image() and original source table count. No SQL recompilation/full binding scan occurs; each row is typed elsewhere. |
| ownership | Borrows program/limits. |
| failure | ImageFailure(binding) on absent handle or retained image, limit on source count. |
| cost | Fixed handle/string-view/span-size checks; no allocation, full binding comparison or schema traversal. |
| Design | [src/recovery/sql_rows_records.cpp](../../../../../src/recovery/sql_rows_records.cpp) |

## B0011

[Lines 57–57](../../../../../src/recovery/sql_rows_records.cpp#L57); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L57-L57:sha256:05fd7ae1e876c84e350486a8f8b19c103ad012a378e103b7d00eba4240d967b3
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Document the adjacent block boundary. |
| inputs / outputs | Comment/spacing only. |
| invariants | Text is not an executed check or proof. |
| ownership | No ownership operation. |
| failure | No executable failure path. |
| cost | No runtime work/allocation. |
| Design | [src/recovery/sql_rows_records.cpp](../../../../../src/recovery/sql_rows_records.cpp) |

## B0012

[Lines 58–62](../../../../../src/recovery/sql_rows_records.cpp#L58); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L58-L62:sha256:20b85b2f75e7849487704941693df1fdc63071d7e0448c238aad311ab8e34302
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Resolve one actual original physical source table and its complete nullable SQL columns. |
| inputs / outputs | Program and uint64 table index -&gt; borrowed source-column span. |
| invariants | Checks table index in range and original table identity equals that index. Genuine immutable program metadata is a premise; field-count limits are enforced by row serialization/parsing. |
| ownership | Returned columns borrow the genuine program metadata (through Descriptor for checkpoint); this helper creates no storage. |
| failure | ImageFailure(binding) on table/index mismatch; program handle access keeps its existing empty-handle rule. |
| cost | Fixed indexed/span-size access and explicit cap/index checks; no allocation, column-value traversal or native work. |
| Design | [src/recovery/sql_rows_records.cpp](../../../../../src/recovery/sql_rows_records.cpp) |

## B0013

[Lines 63–63](../../../../../src/recovery/sql_rows_records.cpp#L63); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L63-L63:sha256:448f46a0ca2a73bec058f8baa218bbc5a7f7ee83ea85e163526f164c8d76da61
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Read the immutable ordered SQL output width. |
| inputs / outputs | Genuine Program -&gt; size_t output width. |
| invariants | Reads outputs().size(); genuine live program is a caller premise. |
| ownership | Returns copied size_t; immutable Program is borrowed for the call. |
| failure | No explicit require here; program getter keeps its existing invalid-handle rule. |
| cost | Fixed output-span size read; no allocation or payload/native traversal. |
| Design | [src/recovery/sql_rows_records.cpp](../../../../../src/recovery/sql_rows_records.cpp) |

## B0014

[Lines 64–64](../../../../../src/recovery/sql_rows_records.cpp#L64); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L64-L64:sha256:da560e85dcea9b26d63ae1aed0d736427f4b008e28f64833408d8e71d31a2ed8
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Read one genuine ordered SQL output type. |
| inputs / outputs | Genuine Program and in-range output index i -&gt; copied SqlType. |
| invariants | Caller must supply i&lt;outputs().size(); operator\[\] supplies no local bounds check. |
| ownership | Returns copied SqlType (kind/nullability/decimal specification); Program is borrowed for the call. |
| failure | No local failure carrier or index validation; program getter keeps its existing invalid-handle rule. |
| cost | Fixed indexed metadata read/copy; no allocation or payload/native traversal. |
| Design | [src/recovery/sql_rows_records.cpp](../../../../../src/recovery/sql_rows_records.cpp) |

## B0015

[Lines 65–69](../../../../../src/recovery/sql_rows_records.cpp#L65); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L65-L69:sha256:a23a6a0ca01755037e178b5fc8a9acd6aaec731dea13457bd90c12e91390a1b9
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Admit NULL/type/decimal/TEXT domain and charge the actual UTF8 validation extent. |
| inputs / outputs | Budget, optional ScalarView Cell and SqlType → void after fits. |
| invariants | Charges TEXT UTF8 visits; checks only this cell against supplied type, not row identity/constraints. |
| ownership | Cell/text/type borrowed, no retained copy. |
| failure | ImageFailure(work) if TEXT-byte charge fails; ImageFailure(scalar) if this nullable value does not fit the supplied SqlType. |
| cost | Fixed scalar/decimal checks or linear TEXT byte validation; no allocation. |
| Design | [src/recovery/sql_rows_records.cpp](../../../../../src/recovery/sql_rows_records.cpp), [src/frontend/sql_rows_value.hpp](../../../../../src/frontend/sql_rows_value.hpp) |

## B0016

[Lines 70–72](../../../../../src/recovery/sql_rows_records.cpp#L70); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L70-L72:sha256:c43e4ec0b3ee752126804d3a468ccffa153c533f97485d5feda15e70248873ea
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Charge the shorter key extent and return its lexical ordering comparison. |
| inputs / outputs | Budget and two string_view keys → Boolean lexical a&lt;b. |
| invariants | Charges min(key lengths) before comparison; does not validate key encoding or uniqueness alone. |
| ownership | Keys borrowed; no retained state beyond Budget.used. |
| failure | ImageFailure(work) if charge fails. |
| cost | Actual lexical comparison up to minimum extent and fixed budget arithmetic; no allocation. |
| Design | [src/recovery/sql_rows_records.cpp](../../../../../src/recovery/sql_rows_records.cpp) |

## B0017

[Lines 73–73](../../../../../src/recovery/sql_rows_records.cpp#L73); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L73-L73:sha256:29e8f0aa95ddac969bc956b55c7574b065cbb5317e76515d93eaa27bac52cb0a
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Index packed canonical output row bytes and their exact unsigned sign/magnitude, without an owning SQL row. |
| inputs / outputs | KeySlice fields are packed-key begin, packed-key size and SignedMagnitude change. |
| invariants | This plain struct implements no key bounds/order/duplicate/sign validation. |
| ownership | Offsets borrow meaning from caller-owned packed bytes; change is a copied fixed value. |
| failure | No executable failure path. |
| cost | Fixed scalar record; vector backing allocation belongs to output_rows. |
| Design | [src/recovery/sql_rows_records.cpp](../../../../../src/recovery/sql_rows_records.cpp) |

## B0018

[Lines 74–79](../../../../../src/recovery/sql_rows_records.cpp#L74); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L74-L79:sha256:6e4f5f427e22c8ee16cfa08fd894740fc5f64eb85a79b841eb46c2f87fb0abc7
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Own bounded packed output row bytes and sorting metadata under the actual receiver. |
| inputs / outputs | Account → empty key/index vectors using image_allocator. |
| invariants | Constructor does not validate/fill/sort any rows. |
| ownership | Two vector allocator/account handles; later vector backing owns its actual receiver allocations. |
| failure | No intentional validation; allocator handle construction rules apply. |
| cost | Fixed vector/allocator construction; backing allocations occur only in later fills. |
| Design | [src/recovery/sql_rows_records.cpp](../../../../../src/recovery/sql_rows_records.cpp) |

## B0019

[Lines 80–88](../../../../../src/recovery/sql_rows_records.cpp#L80); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L80-L88:sha256:51e48bf139a045da5376737fcb984cd06b332667bfc1f8a0f232b7eeb9c817e2
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Check selected constant/parameter output equals its genuine immutable constant, including NULL. |
| inputs / outputs | Budget/program/output index/cell → void; nonconstant fields take no further check. |
| invariants | Caller supplies an in-range output index into genuine metadata. Nonconstant slots return. A constant ExpressionId checks exact optional equality and charges relevant string comparison bytes; no other fields are checked. |
| ownership | Borrows immutable initial slot and supplied cell. |
| failure | ImageFailure(work) on constant/string comparison charge; ImageFailure(scalar) on unequal constant. Output index/ExpressionId validity is a genuine metadata caller premise. |
| cost | Fixed descriptor/optional checks plus actual constant string comparison extent; no allocation. |
| Design | [src/recovery/sql_rows_records.cpp](../../../../../src/recovery/sql_rows_records.cpp) |

## B0020

[Lines 89–93](../../../../../src/recovery/sql_rows_records.cpp#L89); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L89-L93:sha256:79c252e18374cbe3fdedefbef8209e2f6be2c3fcfe932c23727093a5024ae89c
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Require nonzero exact unsigned magnitude; DISTINCT and EXISTS changes must have magnitude one. |
| inputs / outputs | Program presentation mode + SignedMagnitude → void. |
| invariants | Requires magnitude&gt;0 and unit magnitude for set/EXISTS; does not determine actual before/after result semantics. |
| ownership | Only borrowed fixed values. |
| failure | ImageFailure(scalar) for zero magnitude or nonunit DISTINCT/EXISTS magnitude; no Budget/account/native operation. |
| cost | Fixed tests; no allocation or row/native traversal. |
| Design | [src/recovery/sql_rows_records.cpp](../../../../../src/recovery/sql_rows_records.cpp) |

## B0021

[Lines 94–102](../../../../../src/recovery/sql_rows_records.cpp#L94); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L94-L102:sha256:7d7090d6c3a7709d6abbfa2b791beb6b58e2d765f804825755eaf171d1eafeca
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Declare record Writer context and document nullable signed-magnitude encoding. |
| inputs / outputs | Open Output : Writer with borrowed Program/Limits/EncodedRows context and fixed InputInfo accumulator. |
| invariants | Declaring fields performs no validation or output capture; methods specify later serialization. |
| ownership | No new runtime backing storage from declarations; actual declared views/handles obey their named type lifetimes. |
| failure | Compile-time checking only in this span; invoked member/helper operations have separately specified failures. |
| cost | Include/type/signature/constant declarations only; no executed codec/binder/hash/sort/native work or backing allocation. |
| Design | [src/recovery/sql_rows_records.cpp](../../../../../src/recovery/sql_rows_records.cpp) |

## B0022

[Lines 103–105](../../../../../src/recovery/sql_rows_records.cpp#L103); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L103-L105:sha256:e5bd5c7cc5a66e94c950b80639d894850494f0ca5aa55d1755d3096fd4c4023f
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Validate and append an existing hexadecimal identity span. |
| inputs / outputs | Fixed char span → Writer append after lowercase-hex validation. |
| invariants | Does not compute a hash or authenticate identity. |
| ownership | Span borrowed; Writer.size/Budget advance; a materializing Writer appends to its caller-owned vector and can allocate if capacity is insufficient. A measure Writer owns no output. |
| failure | ImageFailure(binding) for nonhex input; delegated Writer::put can reject byte/work limits or propagate vector allocation. No hash is computed. |
| cost | Fixed-width hex check and actual byte append; no native work. |
| Design | [src/recovery/sql_rows_records.cpp](../../../../../src/recovery/sql_rows_records.cpp) |

## B0023

[Lines 106–113](../../../../../src/recovery/sql_rows_records.cpp#L106); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L106-L113:sha256:7ad6102bb76b04c90e8ea1105a41acba508c4ed6617ca3005d58dc98c6c01650
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Serialize one complete typed nullable row under row/field caps. |
| inputs / outputs | Cell span, expected width and SqlType resolver -&gt; Writer row bytes. |
| invariants | Checks row count admission, exact span width, field cap and each nullable cell against the supplied type resolver. It does not check constants or source constraints. |
| ownership | Caller cells/types remain borrowed. Writer size/Budget advance; measure mode stores no bytes, materializing mode appends to its caller vector. |
| failure | Fixed ImageFailure rejects the stated wire/domain/work checks; this block adds no catch or recovery action. Materializing vector allocation failures propagate. |
| cost | Visit actual fields and scalar/TEXT validation+wire byte extents; no token decode, tuple copy, sort or hash. |
| Design | [src/recovery/sql_rows_records.cpp](../../../../../src/recovery/sql_rows_records.cpp) |

## B0024

[Lines 114–117](../../../../../src/recovery/sql_rows_records.cpp#L114); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L114-L117:sha256:f1d4389c855f8a6c9d993f534c315ab9b71f146ed6ebd87120614be4a302197a
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Encode one ordered SQL presentation row, enforcing its fixed outputs as well as nullable types. |
| inputs / outputs | SQL Cell span → typed row serialization plus per-field constant checks. |
| invariants | Checks this ordered row against actual output width/types/constants; no token decode or sorting occurs here. |
| ownership | Input bytes/cells and program metadata are borrowed for the call; no returned borrow outlives its backing owner. Writer.size/Budget advance; a materializing Writer appends to its caller-owned vector and can allocate if capacity is insufficient. A measure Writer owns no output. |
| failure | Fixed ImageFailure rejects the stated wire/domain/work checks; this block adds no catch or recovery action. Output vector growth may allocate. |
| cost | Actual field/scalar/TEXT validation+write+constant comparison extents; no owning tuple created. |
| Design | [src/recovery/sql_rows_records.cpp](../../../../../src/recovery/sql_rows_records.cpp) |

## B0025

[Lines 118–121](../../../../../src/recovery/sql_rows_records.cpp#L118); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L118-L121:sha256:e4dd11b620a4b0b67aed5f44814a862d4b359a43d993582eaaee344ec28f259c
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Serialize a validated WAL header payload. |
| inputs / outputs | Const WalHeader payload -&gt; append exactly its fixed wire fields to Writer. |
| invariants | Calls that fixed value’s validator; no runtime/file publication or hash computation. |
| ownership | Writer.size/Budget advance; a materializing Writer appends to its caller-owned vector and can allocate if capacity is insufficient. A measure Writer owns no output. |
| failure | Fixed ImageFailure rejects the stated wire/domain/work checks; this block adds no catch or recovery action. Materializing append allocation failures propagate. |
| cost | Fixed-width validation/writes; no SQL parsing, row sort or native work. |
| Design | [src/recovery/sql_rows_records.cpp](../../../../../src/recovery/sql_rows_records.cpp) |

## B0026

[Lines 122–124](../../../../../src/recovery/sql_rows_records.cpp#L122); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L122-L124:sha256:cb4bd2a2b741a0067c9cf09aafe963cea0a49dd5f754e660428b5ccf668e2ea0
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Serialize a validated sink header payload. |
| inputs / outputs | Const SinkHeader payload -&gt; append exactly its fixed wire fields to Writer. |
| invariants | Calls that fixed value’s validator; no runtime/file publication or hash computation. |
| ownership | Writer.size/Budget advance; a materializing Writer appends to its caller-owned vector and can allocate if capacity is insufficient. A measure Writer owns no output. |
| failure | Fixed ImageFailure rejects the stated wire/domain/work checks; this block adds no catch or recovery action. Materializing append allocation failures propagate. |
| cost | Fixed-width validation/writes; no SQL parsing, row sort or native work. |
| Design | [src/recovery/sql_rows_records.cpp](../../../../../src/recovery/sql_rows_records.cpp) |

## B0027

[Lines 125–149](../../../../../src/recovery/sql_rows_records.cpp#L125); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L125-L149:sha256:7e82542e71fca1595f0e85786f56051c35ea17fdde04627fb3763b46582aadac
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Serialize ordered complete input replacements and optional source/reader metadata. |
| inputs / outputs | Borrowed InputView → append ordered full physical edits and optional source/reader metadata; populate InputInfo offsets/counts. |
| invariants | Checks command&gt;0, complete typed source rows and stated name/reader rules. Does not authenticate old weights, constraints or operational source offsets. |
| ownership | Writer.size/Budget advance; a materializing Writer appends to its caller-owned vector and can allocate if capacity is insufficient. A measure Writer owns no output. |
| failure | Fixed ImageFailure rejects the stated wire/domain/work checks; this block adds no catch or recovery action. Materializing append allocation failures propagate. |
| cost | Actual edit fields/TEXT/source-name bytes and fixed before/after words; no native transaction or sorting. |
| Design | [src/recovery/sql_rows_records.cpp](../../../../../src/recovery/sql_rows_records.cpp) |

## B0028

[Lines 150–154](../../../../../src/recovery/sql_rows_records.cpp#L150); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L150-L154:sha256:d6033c4f8cbbc31f259ba0b8b19290587be84de48dcfe615203feb8896778900
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Serialize a validated Commit payload. |
| inputs / outputs | Const Commit payload -&gt; append exactly its fixed wire fields to Writer. |
| invariants | Calls that fixed value’s validator; no runtime/file publication or hash computation. |
| ownership | Writer.size/Budget advance; a materializing Writer appends to its caller-owned vector and can allocate if capacity is insufficient. A measure Writer owns no output. |
| failure | Fixed ImageFailure rejects the stated wire/domain/work checks; this block adds no catch or recovery action. Materializing append allocation failures propagate. |
| cost | Fixed-width validation/writes; no SQL parsing, row sort or native work. |
| Design | [src/recovery/sql_rows_records.cpp](../../../../../src/recovery/sql_rows_records.cpp) |

## B0029

[Lines 155–158](../../../../../src/recovery/sql_rows_records.cpp#L155); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L155-L158:sha256:480c119f9b51625ccb3a6c663e1161685c36d69dbf184dc15e9b96950fcb87ef
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Serialize a validated semantic Reject payload. |
| inputs / outputs | Const Reject payload -&gt; append exactly its fixed wire fields to Writer. |
| invariants | Calls that fixed value’s validator; no runtime/file publication or hash computation. |
| ownership | Writer.size/Budget advance; a materializing Writer appends to its caller-owned vector and can allocate if capacity is insufficient. A measure Writer owns no output. |
| failure | Fixed ImageFailure rejects the stated wire/domain/work checks; this block adds no catch or recovery action. Materializing append allocation failures propagate. |
| cost | Fixed-width validation/writes; no SQL parsing, row sort or native work. |
| Design | [src/recovery/sql_rows_records.cpp](../../../../../src/recovery/sql_rows_records.cpp) |

## B0030

[Lines 159–169](../../../../../src/recovery/sql_rows_records.cpp#L159); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L159-L169:sha256:41af966d767c7d7a6e2837f4ed3975ddf772e33d4baac6a8595d7f79161b9f15
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Serialize epoch metadata and already canonical packed output entries. |
| inputs / outputs | RowEpoch metadata and existing EncodedRows → append prefix, packed key bytes and stored signs/magnitudes. |
| invariants | Requires encoded pointer and valid RowInfo flags/counts. Caller already built/sorted/validated keys; this block does not read the token, decode SQL or sort. |
| ownership | Writer.size/Budget advance; a materializing Writer appends to its caller-owned vector and can allocate if capacity is insufficient. A measure Writer owns no output. |
| failure | Fixed ImageFailure rejects the stated wire/domain/work checks; this block adds no catch or recovery action. Materializing append allocation failures propagate. |
| cost | Measure mode charges/counts packed byte extents; materializing mode also copies them. Fixed prefix and sign/magnitude words per row; no token decode, new scratch or sort. |
| Design | [src/recovery/sql_rows_records.cpp](../../../../../src/recovery/sql_rows_records.cpp) |

## B0031

[Lines 170–189](../../../../../src/recovery/sql_rows_records.cpp#L170); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L170-L189:sha256:888e04ef031c9e2e62a2cf3ad0a094effab7446cd3477aa22318d598b0bac457
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Write the distinct CROWNRW2 protected envelope, kind/ordinal and its matching typed payload. |
| inputs / outputs | Ordinal+typed PayloadView and precomputed encoded keys → append header/body, return Inspected metadata. |
| invariants | Checks kind/ordinal, decision input ordinal and RowEpoch C=ordinal. It does not fill final length/checksums or perform native preparation. |
| ownership | Writer.size/Budget advance; a materializing Writer appends to its caller-owned vector and can allocate if capacity is insufficient. A measure Writer owns no output. |
| failure | Fixed ImageFailure rejects the stated wire/domain/work checks; this block adds no catch or recovery action. Delegated writes may allocate in materializing mode. |
| cost | Concrete payload write plus fixed header/variant dispatch; no separate sorting or hashing. |
| Design | [src/recovery/sql_rows_records.cpp](../../../../../src/recovery/sql_rows_records.cpp) |

## B0032

[Lines 190–198](../../../../../src/recovery/sql_rows_records.cpp#L190); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L190-L198:sha256:0a0cceffe11cd9782fa370f328fac1eae704789941f7285580c4da6d30f28e26
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Declare borrowed record parser context and optional materialization targets. |
| inputs / outputs | Close Output; open Input : Reader with borrowed Program/Limits and nullable Cell/replacement vector pointers. |
| invariants | Null pointers select inspection; methods implement validation/materialization. Field declaration itself reads nothing. |
| ownership | No new runtime backing storage from declarations; actual declared views/handles obey their named type lifetimes. |
| failure | Compile-time checking only in this span; invoked member/helper operations have separately specified failures. |
| cost | Include/type/signature/constant declarations only; no executed codec/binder/hash/sort/native work or backing allocation. |
| Design | [src/recovery/sql_rows_records.cpp](../../../../../src/recovery/sql_rows_records.cpp) |

## B0033

[Lines 199–199](../../../../../src/recovery/sql_rows_records.cpp#L199); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L199-L199:sha256:239310424c1a449a9c5bae1ad15a6d0f62566862d1eba2a1884b6d5132518ea0
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Accept only the exact zero/one wire flag. |
| inputs / outputs | Reader next byte → Boolean. |
| invariants | Accepts only0/1; no other state is validated. |
| ownership | Reader.position and the shared Budget advance; rejection may retain consumed work but returns no completed parse result. |
| failure | Reader bounded take can throw ImageFailure(corrupt/work); a byte outside0/1 throws corrupt. No allocation/error translation. |
| cost | One bounded byte read; no allocation. |
| Design | [src/recovery/sql_rows_records.cpp](../../../../../src/recovery/sql_rows_records.cpp) |

## B0034

[Lines 200–203](../../../../../src/recovery/sql_rows_records.cpp#L200); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L200-L203:sha256:92c4d35d5a6aa1818bcba8245e4f8f9bbbfc617cae8e4514f43cb9d950538a8d
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Read and check one fixed-width hexadecimal array. |
| inputs / outputs | Reader bytes → fixed-size returned char array after hex validation. |
| invariants | Bounds/hex are checked; no hash is computed. |
| ownership | Copies a fixed array, advances reader/Budget; retains no borrow. |
| failure | Reader bounded take can throw ImageFailure(corrupt/work); nonhex bytes throw binding. No allocation/error translation. |
| cost | Fixed N-byte read/check/copy; no allocation. |
| Design | [src/recovery/sql_rows_records.cpp](../../../../../src/recovery/sql_rows_records.cpp) |

## B0035

[Lines 204–204](../../../../../src/recovery/sql_rows_records.cpp#L204); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L204-L204:sha256:64864582608cd02914a49b3db5f39096a76fbef4504ad6d6c188371e8b4f1836
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Decode the fixed transport query/descriptor identity. |
| inputs / outputs | Reader → Binding{Id32,Hash64} via the two fixed hash readers. |
| invariants | Hex/extent only; no descriptor authority is created. |
| ownership | Returned fixed arrays own their copies; reader/Budget advance. |
| failure | Delegated hash readers propagate ImageFailure(corrupt/work/binding); no native admission or other check. |
| cost | Fixed96-byte read/check; no allocation. |
| Design | [src/recovery/sql_rows_records.cpp](../../../../../src/recovery/sql_rows_records.cpp) |

## B0036

[Lines 205–213](../../../../../src/recovery/sql_rows_records.cpp#L205); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L205-L213:sha256:4622987a0fc3f5b6f301b0826509c1d25d43de62f6f3261876ac02e2cccc95bf
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Parse a complete typed nullable input row and optionally append flat cell views. |
| inputs / outputs | Reader, expected width and SqlType resolver -&gt; borrowed complete row-byte slice; optional cells vector appends Cell views. |
| invariants | Checks row cap, exact encoded field count and each nullable scalar/type. Caller supplies valid immutable type resolver; no source constraints/native semantics are checked. |
| ownership | Reader position/Budget advance. Row slice and TEXT cells borrow input backing; optional flat vector owns only Cell descriptors. |
| failure | Fixed ImageFailure rejects the stated wire/domain/work checks; this block adds no catch or recovery action. Optional vector materialization can allocate if caller reservation is insufficient. |
| cost | Actual field/scalar/TEXT decode and validation, plus optional descriptor pushes; no tuple copy, sort/hash or runtime call. |
| Design | [src/recovery/sql_rows_records.cpp](../../../../../src/recovery/sql_rows_records.cpp) |

## B0037

[Lines 214–237](../../../../../src/recovery/sql_rows_records.cpp#L214); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L214-L237:sha256:0f3ea0f2ba3edae03b88ba50a6ca54a955a412de7e78e29a3dd178e45d8b1ee8
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Decode the ordered complete physical replacement chain and optional source/reader transport metadata. |
| inputs / outputs | Reader → InputInfo; optional owned-frame cell/replacement arrays receive borrowed views. |
| invariants | Checks input sequence&gt;0, count/extent/schema, optional source name/reader fields. Preserves edit order; before/after semantic checks are not done. |
| ownership | Reader.position and the shared Budget advance; rejection may retain consumed work but returns no completed parse result. Flat vectors own descriptors only; their strings borrow frame input. |
| failure | Fixed ImageFailure rejects the stated wire/domain/work checks; this block adds no catch or recovery action. Materializing vector allocation can propagate if not pre-reserved. |
| cost | Linear actual replacement/cell/scalar/name visits; no native/update/account grant creation. |
| Design | [src/recovery/sql_rows_records.cpp](../../../../../src/recovery/sql_rows_records.cpp) |

## B0038

[Lines 238–266](../../../../../src/recovery/sql_rows_records.cpp#L238); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L238-L266:sha256:21701f21794387be2d627e520bc15d38f23fb9bf7d3c23663ee69ae117aacd8d
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Inspect strictly sorted SQL output rows, nonzero signed uint64 changes and complete Boolean replacement rules. |
| inputs / outputs | Reader/program/limits → fixed RowInfo while consuming presented row bytes. |
| invariants | Checks RowInfo flags/C/I/hash, exact output fields/constants, strictly ordered unique keys, nonzero/unit magnitudes and EXISTS two opposite Boolean changes. Does not read a PreparedBatch or prove delta correctness against native state. |
| ownership | Reader.position and the shared Budget advance; rejection may retain consumed work but returns no completed parse result. All row/key/TEXT values are temporary borrowed views; returned metadata is fixed. |
| failure | Fixed ImageFailure rejects the stated wire/domain/work checks; this block adds no catch or recovery action. |
| cost | Allocation-free loops over admitted encoded rows/fields/scalar bytes and key/constant comparisons; no token decode, scratch vector, key allocation, sorting or native call. |
| Design | [src/recovery/sql_rows_records.cpp](../../../../../src/recovery/sql_rows_records.cpp) |

## B0039

[Lines 267–289](../../../../../src/recovery/sql_rows_records.cpp#L267); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L267-L289:sha256:ace3ee9846353e185cc339c2e1984ee999a154120e7e40442b260bb3c8420b85
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Dispatch the closed row-record kind set and require exact end-of-frame consumption. |
| inputs / outputs | Reader → concrete fixed Inspected payload after closed kind dispatch. |
| invariants | Checks exact EOF and kind/ordinal/decision/row consistency; relies on caller to verify protected frame hashes. |
| ownership | Reader.position and the shared Budget advance; rejection may retain consumed work but returns no completed parse result. No retained frame/cell owner is created in inspection mode. |
| failure | Fixed ImageFailure rejects the stated wire/domain/work checks; this block adds no catch or recovery action. |
| cost | Actual selected payload parse/validation visits; no hash, sort or native factory. |
| Design | [src/recovery/sql_rows_records.cpp](../../../../../src/recovery/sql_rows_records.cpp) |

## B0040

[Lines 290–293](../../../../../src/recovery/sql_rows_records.cpp#L290); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L290-L293:sha256:566d44b24c148bf2de92fd296ca76677a8006099dd9c432c965d4bf7b6d640c9
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Close the stated namespace/type scope. |
| inputs / outputs | No runtime input or output. |
| invariants | No new checks or state transitions. |
| ownership | No ownership operation. |
| failure | No executable failure path. |
| cost | No runtime work/allocation. |
| Design | [src/recovery/sql_rows_records.cpp](../../../../../src/recovery/sql_rows_records.cpp) |

## B0041

[Lines 294–306](../../../../../src/recovery/sql_rows_records.cpp#L294); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L294-L306:sha256:495b69654610581977e98c52e4e4e94595daaa519008ee4010c94264dac93818
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Validate length-bearing prefix and complete body hashes before typed payload interpretation. |
| inputs / outputs | Genuine Program, borrowed complete bytes, Limits and shared Budget -&gt; fixed Inspected record summary. |
| invariants | Verifies family/version/protected length/body/prefix and exact typed payload; checksum/DTO validity grants no native/file authority. |
| ownership | Input/header/parser views borrow unchanged bytes for the call. Returned Inspected owns fixed payload metadata/body hash/statistics and retains no input slice. |
| failure | Fixed ImageFailure rejects the stated wire/domain/work checks; this block adds no catch or recovery action. |
| cost | Allocation-free full prefix/body hash and typed payload inspection within byte/work/row limits; no whole-frame digest, native factory, sorting or scratch/key allocation. |
| Design | [src/recovery/sql_rows_records.cpp](../../../../../src/recovery/sql_rows_records.cpp) |

## B0042

[Lines 307–309](../../../../../src/recovery/sql_rows_records.cpp#L307); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L307-L309:sha256:06650fda0d60a27b293f681bc6948c74d7a9fcdcd1de599458770ad00dbb6994
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Document the adjacent block boundary. |
| inputs / outputs | Comment/spacing only. |
| invariants | Text is not an executed check or proof. |
| ownership | No ownership operation. |
| failure | No executable failure path. |
| cost | No runtime work/allocation. |
| Design | [src/recovery/sql_rows_records.cpp](../../../../../src/recovery/sql_rows_records.cpp) |

## B0043

[Lines 310–342](../../../../../src/recovery/sql_rows_records.cpp#L310); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L310-L342:sha256:7ae60e60fd72db9fa590761c2acb2e7871501ed596c509690a00919f74b23cbf
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Read genuine prepared output once per row, reuse one scratch row, pack/sort canonical row keys and reject duplicates. |
| inputs / outputs | Account/program/PayloadView/limits/shared Budget → EncodedRows packed byte+index owners; non-RowEpoch payload returns empty vectors. |
| invariants | For RowEpoch requires active output-prepared token, finite presented size and nonempty retained binding bytes on both token and codec program before pointer-fast/exact fallback identity. Checks sequence/source-changed and row limits, reads each presented row once, validates presentation, sorts/rejects duplicate keys. No commit or snapshot recomputation. |
| ownership | One accounted Cell scratch row and packed key/index vectors; token/program remain borrowed. Shared identity backing avoids full byte comparison, distinct backing gets exact comparison. |
| failure | Fixed ImageFailure rejects the stated wire/domain/work checks; this block adds no catch or recovery action. Output-limit/decoder and allocation failures propagate; token remains caller-owned. |
| cost | One token read per output, actual field/TEXT encoding and O(rows log rows) charged key comparisons. Packed storage grows under receiver; no second owning SQL tuple vector. |
| Design | [src/recovery/sql_rows_records.cpp](../../../../../src/recovery/sql_rows_records.cpp) |

## B0044

[Lines 343–344](../../../../../src/recovery/sql_rows_records.cpp#L343); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L343-L344:sha256:c929980d95efc152dc886ac42af0f045075441dd18a8f886364828ead327bbd3
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Close the stated namespace/type scope. |
| inputs / outputs | No runtime input or output. |
| invariants | No new checks or state transitions. |
| ownership | No ownership operation. |
| failure | No executable failure path. |
| cost | No runtime work/allocation. |
| Design | [src/recovery/sql_rows_records.cpp](../../../../../src/recovery/sql_rows_records.cpp) |

## B0045

[Lines 345–360](../../../../../src/recovery/sql_rows_records.cpp#L345); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L345-L360:sha256:896bf82d99fc478b6055ed7804ad31f9f2165c0735077f02ea358eff0f15fd07
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Fund one immutable whole record after measured serialization; prepared output and codec work remain separate finite grants. |
| inputs / outputs | Account/program/ordinal/PayloadView/limits → one immutable owned CROWNRW2 Frame. |
| invariants | Validates program; output_rows prepares row payload if requested; measure/write and length/body/prefix checksum complete before return. Does not publish native/file state. |
| ownership | Final frame, optional packed output buffers and scratch use receiver. Input/program/token borrowed until call ends; packed buffers are temporary. |
| failure | Fixed ImageFailure rejects the stated wire/domain/work checks; this block adds no catch or recovery action. Native output decoder/account failures propagate without consuming caller token ownership. |
| cost | Actual output_rows preparation, two frame passes/hash bytes and final reserve/allocation; no binder/lowerer or full result snapshot. |
| Design | [src/recovery/sql_rows_records.cpp](../../../../../src/recovery/sql_rows_records.cpp) |

## B0046

[Lines 361–363](../../../../../src/recovery/sql_rows_records.cpp#L361); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L361-L363:sha256:88c86d8146b07debc3df719d3e4c96199df56230781c108c52353f5bb88a9a89
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Perform allocation-free bounded complete record validation against a genuine program. |
| inputs / outputs | Genuine Program, borrowed complete bytes and by-value Limits -&gt; Inspected. |
| invariants | Constructs local Budget{limits.record}, then delegates to inspect_frame; no additional checks or interpretation. |
| ownership | Only local Budget and fixed returned summary; frame/program remain borrowed through the delegated call. |
| failure | inspect_frame failures propagate unchanged; wrapper adds no error translation. |
| cost | Fixed Budget initialization plus complete delegated bounded inspect_frame work; no allocation/native operation. |
| Design | [src/recovery/sql_rows_records.cpp](../../../../../src/recovery/sql_rows_records.cpp) |

## B0047

[Lines 364–376](../../../../../src/recovery/sql_rows_records.cpp#L364); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L364-L376:sha256:e9b0cf10e5ad4319c1f137e8218881d587d223b0bccf6b5bc765a44807ed309b
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Inspect all input bytes before owning one frame and two reserved flat borrow arrays. |
| inputs / outputs | Account/program/complete bytes/limits → owned DecodedInput. |
| invariants | Full inspect must succeed and kind=input before allocation. Copies frame once, reserves exact flat arrays and parses views again; does not admit weights/constraints. |
| ownership | One receiving frame plus cell/replacement arrays; TEXT/source spans borrow owned frame, independent of caller bytes. |
| failure | Fixed ImageFailure rejects the stated wire/domain/work checks; this block adds no catch or recovery action. Allocation failures propagate; no native/file mutation. |
| cost | Full inspect, one byte copy and typed materializing parse with reserved flat storage; no sort/native operation. |
| Design | [src/recovery/sql_rows_records.cpp](../../../../../src/recovery/sql_rows_records.cpp) |

## B0048

[Lines 377–389](../../../../../src/recovery/sql_rows_records.cpp#L377); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L377-L389:sha256:cc87625ecdf4bd60d175f61c8e39390882bcc48b003d17c71fd8dce8e6f911e9
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Fund the logged input directly, then materialize its flat views without another owned frame copy. |
| inputs / outputs | Account/program/ordinal/InputView/limits → directly funded owned DecodedInput. |
| invariants | Calls encode, then parses the owned frame into flat views under the same cumulative codec work. No encode-then-copy second frame or native admission. |
| ownership | Encoded Frame owns bytes; two receiver arrays retain frame borrows. Caller cells/TEXT can expire after return. |
| failure | Fixed ImageFailure rejects the stated wire/domain/work checks; this block adds no catch or recovery action. Frame/array allocation failures propagate. |
| cost | Input encode plus flat typed parse/reserves; no output token/sort/native work. |
| Design | [src/recovery/sql_rows_records.cpp](../../../../../src/recovery/sql_rows_records.cpp) |

## B0049

[Lines 390–392](../../../../../src/recovery/sql_rows_records.cpp#L390); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L390-L392:sha256:710826fbcc51dd6a23250722ac999083a37e676030bc6ef4d1c875bfc78aa67b
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Move the frame and flat cell/replacement arrays without rebasing their stable heap addresses. |
| inputs / outputs | Frame and two funded flat vectors → DecodedInput members. |
| invariants | Caller established valid offsets/borrows; constructor itself performs no validation. |
| ownership | Moves all three owners; existing heap addresses stay stable. |
| failure | Declared noexcept moves; no intentional failure. |
| cost | Fixed vector/frame metadata moves; no byte/cell copy or allocation. |
| Design | [src/recovery/sql_rows_records.cpp](../../../../../src/recovery/sql_rows_records.cpp) |

## B0050

[Lines 393–397](../../../../../src/recovery/sql_rows_records.cpp#L393); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L393-L397:sha256:120183d9d78bccc6de4abf461552b0cd3cf4e9e2c9a2a4ef4c772498b17551a1
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Return a borrow into this unmoved input/frame owner, preserving exact complete physical replacements. |
| inputs / outputs | This input Frame metadata/replacement vector → InputView with optional source slice/reader position. |
| invariants | Assumes stored frame is input with valid offsets; does not re-inspect it. |
| ownership | Returned spans/source string_view borrow this live unmoved owner. |
| failure | std::get fails if the private invariant is violated; no custom validation here. |
| cost | Fixed metadata/optional/view construction; no allocation or byte/native traversal. |
| Design | [src/recovery/sql_rows_records.cpp](../../../../../src/recovery/sql_rows_records.cpp) |

## B0051

[Lines 398–398](../../../../../src/recovery/sql_rows_records.cpp#L398); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L398-L398:sha256:5a88989d646de8c904ac4cbcd84db92dc85500003eb77614a29dedc10d8206dd
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Close the stated namespace/type scope. |
| inputs / outputs | No runtime input or output. |
| invariants | No new checks or state transitions. |
| ownership | No ownership operation. |
| failure | No executable failure path. |
| cost | No runtime work/allocation. |
| Design | [src/recovery/sql_rows_records.cpp](../../../../../src/recovery/sql_rows_records.cpp) |
