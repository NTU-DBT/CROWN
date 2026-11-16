# `src/recovery/sql_aggregate_records.cpp` — block usage map

[Source](../../../../../src/recovery/sql_aggregate_records.cpp) · [Source index](../../../README.md) · [Subsystem contracts](../../../subsystem_contracts.md) · [Reviewed primitives](../../../primitives.md)

Encode, validate and publish checkpoints, journals, generations and local delivery receipts with explicit durable authority.

Snapshot SHA-256: `c4da0791b4b9ce3e5bc17de3bd7a178b199a6209c4e2cd23e61874deb5de39ae`. 360 lines partitioned into 49 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [recovery](../../../subsystem_contracts.md#recovery). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/checkpoints.md](../../../../checkpoints.md), [docs/journal.md](../../../../journal.md), [docs/journal-files.md](../../../../journal-files.md), [docs/generations.md](../../../../generations.md), [docs/local-sink.md](../../../../local-sink.md), [docs/history-retirement.md](../../../../history-retirement.md), [docs/update_patterns.md](../../../../update_patterns.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–9](../../../../../src/recovery/sql_aggregate_records.cpp#L1) | Imports dependencies; declares namespace scope. | source comment (unverified): // Only validated codec factories construct immutable owned frames/borrow sets. · [reviewed contract](#b0001) |
| [B0002 · 10–19](../../../../../src/recovery/sql_aggregate_records.cpp#L10) | Type/record definition: struct FrameAccess | returns Frame(std::move(bytes),std::move(info)); DecodedInput(std::move(frame),std::move(cells),std::move(r…; source comment (unverified): // Only validated codec factories construct immutable owned frames/borrow sets. · [reviewed contract](#b0002) |
| [B0003 · 20–27](../../../../../src/recovery/sql_aggregate_records.cpp#L20) | declares namespace scope; declares aliases; declares values/defaults or compile-time conditions. | source comment (unverified): // namespace detail · [reviewed contract](#b0003) |
| [B0004 · 28–30](../../../../../src/recovery/sql_aggregate_records.cpp#L28) | Callable definition: void valid(const Binding& value) | calls require, hex; guard require(hex(value.query_id) && hex(value.descriptor_sha256),ImageFault::binding);; source comment (unverified): // Fixed-size metadata validators do not allocate or infer native provenance. · [reviewed contract](#b0004) |
| [B0005 · 31–35](../../../../../src/recovery/sql_aggregate_records.cpp#L31) | Callable definition: void valid(const WalHeader& value) | calls require, hex; guard require(value.generation&gt;0 && hex(value.checkpoint_sha256) && · [reviewed contract](#b0005) |
| [B0006 · 36–36](../../../../../src/recovery/sql_aggregate_records.cpp#L36) | Callable definition: void valid(const SinkHeader& value) | calls require, hex; guard void valid(const SinkHeader& value) { valid(value.binding);require(hex(value.sink_id),ImageFault::b… · [reviewed contract](#b0006) |
| [B0007 · 37–41](../../../../../src/recovery/sql_aggregate_records.cpp#L37) | Callable definition: void valid(const Commit& value) | calls require, hex; guard require(value.input_ordinal&gt;0 && value.physical_sequence&gt;0 && · [reviewed contract](#b0007) |
| [B0008 · 42–46](../../../../../src/recovery/sql_aggregate_records.cpp#L42) | Callable definition: void valid(const Reject& value) | calls require, hex; guard require(value.input_ordinal&gt;0 && value.physical_sequence&lt;value.command_sequence && · [reviewed contract](#b0008) |
| [B0009 · 47–52](../../../../../src/recovery/sql_aggregate_records.cpp#L47) | Callable definition: void valid(const GroupInfo& value) | calls require, hex; guard require(value.generation&gt;0 && value.physical_sequence&gt;0 && value.physical_sequence&lt;=value.input_seq… · [reviewed contract](#b0009) |
| [B0010 · 53–56](../../../../../src/recovery/sql_aggregate_records.cpp#L53) | Callable definition: void program_valid(const Program& program,const Limits& limits) | calls require, bool, source_program, sources; guard require(bool(program),ImageFault::binding); · [reviewed contract](#b0010) |
| [B0011 · 57–57](../../../../../src/recovery/sql_aggregate_records.cpp#L57) | Explanatory comments or spacing. | source comment (unverified): // The genuine source/kernel supply SqlTypes without allocating a schema copy. · [reviewed contract](#b0011) |
| [B0012 · 58–62](../../../../../src/recovery/sql_aggregate_records.cpp#L58) | Callable definition: auto source_columns(const Program& program,std::uint64_t table) | calls source_program, sources, require, size; guard require(table&lt;sources.size() && sources\[static_cast&lt;std::size_t&gt;(table)\].table.value==table,ImageFa…; returns sources\[static_cast&lt;std::size_t&gt;(table)\].columns; source comment (unverified): // The genuine source/kernel supply SqlTypes without allocating a schema copy. · [reviewed contract](#b0012) |
| [B0013 · 63–66](../../../../../src/recovery/sql_aggregate_records.cpp#L63) | Callable definition: std::size_t fields(const Program& program,bool key) | calls kernel_program, group_columns, size, outputs; returns key?kernel.group_columns().size():kernel.outputs().size() · [reviewed contract](#b0013) |
| [B0014 · 67–70](../../../../../src/recovery/sql_aggregate_records.cpp#L67) | Callable definition: frontend::SqlType field_type(const Program& program,bool key,std::size_t i) | calls kernel_program, input_types, group_columns, outputs; returns key?kernel.input_types()\[kernel.group_columns()\[i\].value\]:kernel.outputs()\[i\].type · [reviewed contract](#b0014) |
| [B0015 · 71–75](../../../../../src/recovery/sql_aggregate_records.cpp#L71) | Callable definition: void cell_valid(Budget& budget,const Cell& cell,const frontend::SqlType& type) | calls charge, size, require, frontend::rows_detail::fits; guard require(frontend::rows_detail::fits(cell,type),ImageFault::scalar);; source comment (unverified): // UTF8 pass in fits. · [reviewed contract](#b0015) |
| [B0016 · 76–78](../../../../../src/recovery/sql_aggregate_records.cpp#L76) | Callable definition: bool ordered(Budget& budget,std::string_view a,std::string_view b) | calls charge, std::min, size; returns a&lt;b · [reviewed contract](#b0016) |
| [B0017 · 79–79](../../../../../src/recovery/sql_aggregate_records.cpp#L79) | Type/record definition: struct KeySlice |  · [reviewed contract](#b0017) |
| [B0018 · 80–87](../../../../../src/recovery/sql_aggregate_records.cpp#L80) | declares types or opens a type body; declares values/defaults or compile-time conditions. | source comment (unverified): // Count-only and materializing passes share validation and byte/work admissions. · [reviewed contract](#b0018) |
| [B0019 · 88–90](../../../../../src/recovery/sql_aggregate_records.cpp#L88) | Callable definition: void hash(std::span&lt;const char&gt; value) | calls require, hex, put, data; guard require(hex(value),ImageFault::binding);put({value.data(),value.size()}); · [reviewed contract](#b0019) |
| [B0020 · 91–98](../../../../../src/recovery/sql_aggregate_records.cpp#L91) | Callable definition: template&lt;class TypeAt&gt; void row(std::span&lt;const Cell&gt; cells,std::size_t expected,TypeAt type_at) | calls require, size, integer, cell_valid; guard budget.row();require(cells.size()==expected,ImageFault::binding);; 1 loop sites · [reviewed contract](#b0020) |
| [B0021 · 99–101](../../../../../src/recovery/sql_aggregate_records.cpp#L99) | Callable definition: void group_row(const runtime::aggregate::Tuple& tuple,bool key) | calls require, bool, row, view; guard require(bool(tuple));row(tuple.view(),fields(program,key),\[&\](std::size_t i){return field_type(prog…; returns field_type(program,key,i) · [reviewed contract](#b0021) |
| [B0022 · 102–105](../../../../../src/recovery/sql_aggregate_records.cpp#L102) | Callable definition: void write(const WalHeader& value) | calls valid, hash, integer · [reviewed contract](#b0022) |
| [B0023 · 106–108](../../../../../src/recovery/sql_aggregate_records.cpp#L106) | Callable definition: void write(const SinkHeader& value) | calls valid, hash, integer · [reviewed contract](#b0023) |
| [B0024 · 109–133](../../../../../src/recovery/sql_aggregate_records.cpp#L109) | Callable definition: void write(const InputView& value) | calls require, integer, size, source_columns; guard require(value.command_sequence&gt;0);integer(value.command_sequence,8);; returns columns\[i\].type; 1 loop sites; source comment (unverified): // Arithmetic/constraints belong to native prepare. · [reviewed contract](#b0024) |
| [B0025 · 134–138](../../../../../src/recovery/sql_aggregate_records.cpp#L134) | Callable definition: void write(const Commit& value) | calls valid, integer, hash · [reviewed contract](#b0025) |
| [B0026 · 139–142](../../../../../src/recovery/sql_aggregate_records.cpp#L139) | Callable definition: void write(const Reject& value) | calls valid, integer, hash · [reviewed contract](#b0026) |
| [B0027 · 143–162](../../../../../src/recovery/sql_aggregate_records.cpp#L143) | Callable definition: void write(const GroupEpochView& value) | calls valid, size, require, integer; guard require(order.size()==value.groups.size());integer(value.generation,8);integer(value.input_sequence…; 2 loop sites · [reviewed contract](#b0027) |
| [B0028 · 163–179](../../../../../src/recovery/sql_aggregate_records.cpp#L163) | Callable definition: Inspected frame(std::uint64_t ordinal,const PayloadView& payload) | calls index, require, put, integer; guard require((kind==Kind::wal_header \|\| kind==Kind::sink_header)==(ordinal==0));; returns result · [reviewed contract](#b0028) |
| [B0029 · 180–188](../../../../../src/recovery/sql_aggregate_records.cpp#L180) | declares types or opens a type body; declares values/defaults or compile-time conditions. | source comment (unverified): // Parser borrows bytes. Null output pointers keep inspection allocation-free; · [reviewed contract](#b0029) |
| [B0030 · 189–189](../../../../../src/recovery/sql_aggregate_records.cpp#L189) | Callable definition: bool boolean() | calls integer, require; guard bool boolean() { const auto value=integer(1);require(value&lt;=1);return value!=0; }; returns value!=0 · [reviewed contract](#b0030) |
| [B0031 · 190–193](../../../../../src/recovery/sql_aggregate_records.cpp#L190) | Callable definition: template&lt;std::size_t N&gt; std::array&lt;char,N&gt; hash() | calls take, std::copy, begin, end; guard std::copy(text.begin(),text.end(),result.begin());require(hex(result),ImageFault::binding);return r…; returns result · [reviewed contract](#b0031) |
| [B0032 · 194–194](../../../../../src/recovery/sql_aggregate_records.cpp#L194) | Callable definition: Binding binding() | calls ; returns {hash&lt;32&gt;(),hash&lt;64&gt;()} · [reviewed contract](#b0032) |
| [B0033 · 195–203](../../../../../src/recovery/sql_aggregate_records.cpp#L195) | Callable definition: template&lt;class TypeAt&gt; std::string_view row(std::size_t expected,TypeAt type_at) | calls size, require, boolean, binary_detail::scalar; guard require(count==expected,ImageFault::binding);; returns input.substr(start,position-start); growth push_back; 1 loop sites · [reviewed contract](#b0033) |
| [B0034 · 204–206](../../../../../src/recovery/sql_aggregate_records.cpp#L204) | Callable definition: std::string_view group_row(bool key) | calls row, fields, field_type; returns row(fields(program,key),\[&\](std::size_t i){return field_type(program,key,i) · [reviewed contract](#b0034) |
| [B0035 · 207–230](../../../../../src/recovery/sql_aggregate_records.cpp#L207) | Callable definition: InputInfo item() | calls integer, require, size, source_columns; guard InputInfo value;value.command_sequence=integer(8);require(value.command_sequence&gt;0);; returns columns\[j\].type; value; growth push_back; 1 loop sites; source comment (unverified): // Even zero-column replacements need table/field-count/before/after words. · [reviewed contract](#b0035) |
| [B0036 · 231–243](../../../../../src/recovery/sql_aggregate_records.cpp#L231) | Callable definition: GroupInfo groups() | calls integer, boolean, size, valid; guard const auto key=group_row(true);if(i&gt;0)require(ordered(budget,previous,key));previous=key;; returns value; 1 loop sites · [reviewed contract](#b0036) |
| [B0037 · 244–266](../../../../../src/recovery/sql_aggregate_records.cpp#L244) | Callable definition: Inspected body() | calls integer, require, binding, valid; guard const auto tag=integer(1);require(tag&lt;=static_cast&lt;unsigned&gt;(Kind::group_epoch));; returns value · [reviewed contract](#b0037) |
| [B0038 · 267–270](../../../../../src/recovery/sql_aggregate_records.cpp#L267) | Closes surrounding scope/type. | source comment (unverified): // Protect the length before using it. Exact frames reject trailing bytes; · [reviewed contract](#b0038) |
| [B0039 · 271–283](../../../../../src/recovery/sql_aggregate_records.cpp#L271) | Callable definition: Inspected inspect_frame(const Program& program,std::string_view bytes,const Limits& limits,Budget& budget) | calls program_valid, require, size, take; guard program_valid(program,limits);require(bytes.size()&lt;=limits.record.bytes,ImageFault::limit);; returns info; source comment (unverified): // Protect the length before using it. Exact frames reject trailing bytes; · [reviewed contract](#b0039) |
| [B0040 · 284–286](../../../../../src/recovery/sql_aggregate_records.cpp#L284) | Explanatory comments or spacing. | source comment (unverified): // One compact key buffer plus one index vector; no per-group owning allocation. · [reviewed contract](#b0040) |
| [B0041 · 287–304](../../../../../src/recovery/sql_aggregate_records.cpp#L287) | Callable definition: ImageVector&lt;KeySlice&gt; key_order(const resource::MemoryAccount& account,const Program& program, const PayloadView& payload,const L… | calls order, require, size, group_row; guard require(epoch-&gt;groups.size()&lt;=limits.record.rows,ImageFault::limit);; returns order; std::string_view(keys.data()+entry.begin,entry.size); growth push_back, reserve; 3 loop sites; source comment (unverified): // One compact key buffer plus one index vector; no per-group owning allocation. · [reviewed contract](#b0041) |
| [B0042 · 305–306](../../../../../src/recovery/sql_aggregate_records.cpp#L305) | Closes surrounding scope/type. | source comment (unverified): // namespace · [reviewed contract](#b0042) |
| [B0043 · 307–322](../../../../../src/recovery/sql_aggregate_records.cpp#L307) | Callable definition: Frame encode(const resource::MemoryAccount& account,const Program& program,std::uint64_t ordinal, const PayloadView& payload,Limi… | calls program_valid, key_order, frame, require; guard require(measure.size&lt;=SIZE_MAX,ImageFault::limit);ImageVector&lt;char&gt; bytes(image_allocator&lt;char&gt;(acc…; returns detail::FrameAccess::frame(std::move(bytes),std::move(info)); growth reserve; 1 loop sites · [reviewed contract](#b0043) |
| [B0044 · 323–325](../../../../../src/recovery/sql_aggregate_records.cpp#L323) | Callable definition: Inspected inspect(const Program& program,std::string_view bytes,Limits limits) | calls inspect_frame; returns inspect_frame(program,bytes,limits,budget) · [reviewed contract](#b0044) |
| [B0045 · 326–338](../../../../../src/recovery/sql_aggregate_records.cpp#L326) | Callable definition: DecodedInput decode_input(const resource::MemoryAccount& account,const Program& program, std::string_view bytes,Limits limits) | calls inspect_frame, require, charge, size; guard Budget budget{limits.record};auto info=inspect_frame(program,bytes,limits,budget);require(info.kind…; returns detail::FrameAccess::input(detail::FrameAccess::frame(std::move(owned),std::move(info)),; growth reserve · [reviewed contract](#b0045) |
| [B0046 · 339–351](../../../../../src/recovery/sql_aggregate_records.cpp#L339) | Callable definition: DecodedInput encode_input(const resource::MemoryAccount& account,const Program& program, std::uint64_t ordinal,const InputView& v… | calls encode, info, require, cells; guard const auto metadata=std::get&lt;InputInfo&gt;(frame.info().payload);require(metadata.cells&lt;=SIZE_MAX,Imag…; returns detail::FrameAccess::input(std::move(frame),std::move(cells),std::move(replacements)); growth reserve; source comment (unverified): // The encoded frame is already owned; only flat views are materialized here. · [reviewed contract](#b0046) |
| [B0047 · 352–354](../../../../../src/recovery/sql_aggregate_records.cpp#L352) | Callable definition: DecodedInput::DecodedInput(Frame frame,ImageVector&lt;Cell&gt; cells, ImageVector&lt;runtime::sql_rows::SourceReplacement&gt; replacements) n… | calls frame_, std::move, cells_, replacements_ · [reviewed contract](#b0047) |
| [B0048 · 355–359](../../../../../src/recovery/sql_aggregate_records.cpp#L355) | Callable definition: InputView DecodedInput::view() const & | calls info, bytes, substr; returns {info.command_sequence,replacements_,source,info.reader} · [reviewed contract](#b0048) |
| [B0049 · 360–360](../../../../../src/recovery/sql_aggregate_records.cpp#L360) | Closes surrounding scope/type. | source comment (unverified): // namespace crown::recovery::sql_aggregate · [reviewed contract](#b0049) |

## B0001

[Lines 1–9](../../../../../src/recovery/sql_aggregate_records.cpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L1-L9:sha256:039dc941201c023c7dce3a19fef2d0c253c3fb53b6941e72daa4342c76d0228d
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Imports record codec, digest, binary reader/writer, SQL row validation, and algorithm dependencies; begins the private FrameAccess factory in the aggregate recovery detail namespace. Embedded source note records intended usage: Only validated codec factories construct immutable owned frames/borrow sets. Treat that prose as guidance, not as independently verified executable behavior. |
| inputs / outputs | No runtime inputs/outputs are declared by the import/scope lines themselves. |
| invariants | The listed headers and namespace membership determine compile-time name availability; any API behavior belongs to the declarations/definitions that follow. |
| ownership | No object ownership is created by the imports or namespace tokens. |
| failure | No runtime failure path. Missing/incompatible dependencies or a violated compile-time constraint fail translation/linking. |
| cost | Compile/preprocessor work only; no new per-operation runtime overhead. |
| Design | [src/recovery/sql_aggregate_records.cpp](../../../../../src/recovery/sql_aggregate_records.cpp), [docs/code_specs/files/src/recovery/sql_aggregate_records.cpp.md](sql_aggregate_records.cpp.md), [docs/sql_aggregate_records.md](../../../../sql_aggregate_records.md), [docs/sql_aggregate_session.md](../../../../sql_aggregate_session.md) |

## B0002

[Lines 10–19](../../../../../src/recovery/sql_aggregate_records.cpp#L10); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct FrameAccess {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Provide the only internal constructor/access bridge for validated Frames and DecodedInputs and their work statistic. |
| inputs / outputs | Declaration: \`struct FrameAccess\`. Inputs/outputs: Provide the only internal constructor/access bridge for validated Frames and DecodedInputs and their work statistic. |
| invariants | Only validated codec factories call these bridges; FrameAccess itself is not public admission authority. |
| ownership | Moves vectors/metadata into private Frame/DecodedInput members; no payload copy is introduced. |
| failure | Vector moves are nonthrowing; the bridge adds no error translation. |
| cost | Moves a fixed number of owner objects; no payload scan. |
| Design | [src/recovery/sql_aggregate_records.cpp](../../../../../src/recovery/sql_aggregate_records.cpp), [include/crown/recovery/sql_aggregate_records.hpp](../../../../../include/crown/recovery/sql_aggregate_records.hpp), [include/crown/recovery/image.hpp](../../../../../include/crown/recovery/image.hpp), [src/recovery/binary_detail.hpp](../../../../../src/recovery/binary_detail.hpp), [src/frontend/sql_rows_value.hpp](../../../../../src/frontend/sql_rows_value.hpp), [include/crown/frontend/sql_aggregate.hpp](../../../../../include/crown/frontend/sql_aggregate.hpp), [docs/sql_aggregate_records.md § Wire contract](../../../../sql_aggregate_records.md), [docs/sql_aggregate_records.md § Ownership, failure and cost](../../../../sql_aggregate_records.md) |

## B0003

[Lines 20–27](../../../../../src/recovery/sql_aggregate_records.cpp#L20); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L20-L27:sha256:47eb2bfb90246c038739277c76c52d3069b2116eadbf73cf2ad1beb9a923ece0
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Closes FrameAccess, opens the anonymous codec namespace, aliases binary/cell/compiler types, defines the CROWNAG2 magic, and introduces fixed metadata validators. Embedded source note records intended usage: Fixed-size metadata validators do not allocate or infer native provenance. Treat that prose as guidance, not as independently verified executable behavior. |
| inputs / outputs | No external runtime input/output is performed by the declaration itself; callable signatures in the block describe future use. |
| invariants | The declaration fixes the source-local names and member/type shape; runtime validation and authority remain with the actual implementations. |
| ownership | No owner is added merely by a declaration. Typed fields keep the ownership behavior of their C++ types and any explicit account allocator. |
| failure | No runtime catch or translation is added here; constructor/member failures remain in their implementation. |
| cost | Declaration-only compile/link work, except that constructing a declared type later may initialize or allocate its members. |
| Design | [src/recovery/sql_aggregate_records.cpp](../../../../../src/recovery/sql_aggregate_records.cpp), [docs/code_specs/files/src/recovery/sql_aggregate_records.cpp.md](sql_aggregate_records.cpp.md), [docs/sql_aggregate_records.md](../../../../sql_aggregate_records.md), [docs/sql_aggregate_session.md](../../../../sql_aggregate_session.md) |

## B0004

[Lines 28–30](../../../../../src/recovery/sql_aggregate_records.cpp#L28); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void valid(const Binding& value) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Require lowercase hexadecimal query and descriptor identifiers in a Binding. |
| inputs / outputs | Declaration: \`void valid(const Binding& value)\`. Inputs/outputs: Require lowercase hexadecimal query and descriptor identifiers in a Binding. |
| invariants | Both query_id and descriptor_sha256 must be lowercase ASCII hexadecimal; failure is ImageFault::binding. |
| ownership | All input references/spans are borrowed for the call unless the purpose names an owned return; no fixture/runtime owner escapes this local helper. |
| failure | Invalid hex raises ImageFailure(binding). |
| cost | Scans 96 fixed characters total. |
| Design | [src/recovery/sql_aggregate_records.cpp](../../../../../src/recovery/sql_aggregate_records.cpp), [include/crown/recovery/sql_aggregate_records.hpp](../../../../../include/crown/recovery/sql_aggregate_records.hpp), [include/crown/recovery/image.hpp](../../../../../include/crown/recovery/image.hpp), [src/recovery/binary_detail.hpp](../../../../../src/recovery/binary_detail.hpp), [src/frontend/sql_rows_value.hpp](../../../../../src/frontend/sql_rows_value.hpp), [include/crown/frontend/sql_aggregate.hpp](../../../../../include/crown/frontend/sql_aggregate.hpp), [docs/sql_aggregate_records.md § Wire contract](../../../../sql_aggregate_records.md), [docs/sql_aggregate_records.md § Ownership, failure and cost](../../../../sql_aggregate_records.md) |

## B0005

[Lines 31–35](../../../../../src/recovery/sql_aggregate_records.cpp#L31); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void valid(const WalHeader& value) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Require a bound positive generation, lowercase checkpoint hash, and nondecreasing physical/command frontiers. |
| inputs / outputs | Declaration: \`void valid(const WalHeader& value)\`. Inputs/outputs: Require a bound positive generation, lowercase checkpoint hash, and nondecreasing physical/command frontiers. |
| invariants | generation must be positive, hashes lowercase hex, and physical_sequence&lt;=command_sequence; this is transport shape validation only. |
| ownership | All input references/spans are borrowed for the call unless the purpose names an owned return; no fixture/runtime owner escapes this local helper. |
| failure | Invalid generation/hash/frontier raises ImageFailure(binding). |
| cost | Scans fixed hash arrays and compares two integers. |
| Design | [src/recovery/sql_aggregate_records.cpp](../../../../../src/recovery/sql_aggregate_records.cpp), [include/crown/recovery/sql_aggregate_records.hpp](../../../../../include/crown/recovery/sql_aggregate_records.hpp), [include/crown/recovery/image.hpp](../../../../../include/crown/recovery/image.hpp), [src/recovery/binary_detail.hpp](../../../../../src/recovery/binary_detail.hpp), [src/frontend/sql_rows_value.hpp](../../../../../src/frontend/sql_rows_value.hpp), [include/crown/frontend/sql_aggregate.hpp](../../../../../include/crown/frontend/sql_aggregate.hpp), [docs/sql_aggregate_records.md § Wire contract](../../../../sql_aggregate_records.md), [docs/sql_aggregate_records.md § Ownership, failure and cost](../../../../sql_aggregate_records.md) |

## B0006

[Lines 36–36](../../../../../src/recovery/sql_aggregate_records.cpp#L36); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void valid(const SinkHeader& value) { valid(value.binding);require(hex(value.sink_id),ImageFault::binding); }
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Validate the SinkHeader binding and fixed lowercase sink ID. |
| inputs / outputs | Declaration: \`void valid(const SinkHeader& value)\`. Inputs/outputs: Validate the SinkHeader binding and fixed lowercase sink ID. |
| invariants | The nested binding and sink ID must be valid lowercase hexadecimal arrays. |
| ownership | All input references/spans are borrowed for the call unless the purpose names an owned return; no fixture/runtime owner escapes this local helper. |
| failure | Invalid binding or sink ID raises ImageFailure(binding). |
| cost | Scans nested fixed arrays only. |
| Design | [src/recovery/sql_aggregate_records.cpp](../../../../../src/recovery/sql_aggregate_records.cpp), [include/crown/recovery/sql_aggregate_records.hpp](../../../../../include/crown/recovery/sql_aggregate_records.hpp), [include/crown/recovery/image.hpp](../../../../../include/crown/recovery/image.hpp), [src/recovery/binary_detail.hpp](../../../../../src/recovery/binary_detail.hpp), [src/frontend/sql_rows_value.hpp](../../../../../src/frontend/sql_rows_value.hpp), [include/crown/frontend/sql_aggregate.hpp](../../../../../include/crown/frontend/sql_aggregate.hpp), [docs/sql_aggregate_records.md § Wire contract](../../../../sql_aggregate_records.md), [docs/sql_aggregate_records.md § Ownership, failure and cost](../../../../sql_aggregate_records.md) |

## B0007

[Lines 37–41](../../../../../src/recovery/sql_aggregate_records.cpp#L37); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void valid(const Commit& value) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Validate positive input/physical IDs, C&lt;=I, minimum complete-output frame size, and lowercase digests. |
| inputs / outputs | Declaration: \`void valid(const Commit& value)\`. Inputs/outputs: Validate positive input/physical IDs, C&lt;=I, minimum complete-output frame size, and lowercase digests. |
| invariants | input_ordinal and physical_sequence are positive, physical&lt;=command, output frame length is at least header+107, and both hashes are lowercase hex. |
| ownership | All input references/spans are borrowed for the call unless the purpose names an owned return; no fixture/runtime owner escapes this local helper. |
| failure | Malformed Commit metadata raises ImageFailure(binding); no referenced output is opened or read. |
| cost | Checks fixed fields and two fixed digests. |
| Design | [src/recovery/sql_aggregate_records.cpp](../../../../../src/recovery/sql_aggregate_records.cpp), [include/crown/recovery/sql_aggregate_records.hpp](../../../../../include/crown/recovery/sql_aggregate_records.hpp), [include/crown/recovery/image.hpp](../../../../../include/crown/recovery/image.hpp), [src/recovery/binary_detail.hpp](../../../../../src/recovery/binary_detail.hpp), [src/frontend/sql_rows_value.hpp](../../../../../src/frontend/sql_rows_value.hpp), [include/crown/frontend/sql_aggregate.hpp](../../../../../include/crown/frontend/sql_aggregate.hpp), [docs/sql_aggregate_records.md § Wire contract](../../../../sql_aggregate_records.md), [docs/sql_aggregate_records.md § Ownership, failure and cost](../../../../sql_aggregate_records.md) |

## B0008

[Lines 42–46](../../../../../src/recovery/sql_aggregate_records.cpp#L42); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void valid(const Reject& value) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Validate a supported semantic Reject reason, positive input ordinal, C&lt;I, and input hash. |
| inputs / outputs | Declaration: \`void valid(const Reject& value)\`. Inputs/outputs: Validate a supported semantic Reject reason, positive input ordinal, C&lt;I, and input hash. |
| invariants | reason must not exceed annotation_overflow and physical_sequence must be strictly below command_sequence; unsupported/runtime resource errors are not mapped here. |
| ownership | All input references/spans are borrowed for the call unless the purpose names an owned return; no fixture/runtime owner escapes this local helper. |
| failure | Malformed Reject metadata/reason raises ImageFailure(binding). |
| cost | Checks fixed fields, one enum and one fixed digest. |
| Design | [src/recovery/sql_aggregate_records.cpp](../../../../../src/recovery/sql_aggregate_records.cpp), [include/crown/recovery/sql_aggregate_records.hpp](../../../../../include/crown/recovery/sql_aggregate_records.hpp), [include/crown/recovery/image.hpp](../../../../../include/crown/recovery/image.hpp), [src/recovery/binary_detail.hpp](../../../../../src/recovery/binary_detail.hpp), [src/frontend/sql_rows_value.hpp](../../../../../src/frontend/sql_rows_value.hpp), [include/crown/frontend/sql_aggregate.hpp](../../../../../include/crown/frontend/sql_aggregate.hpp), [docs/sql_aggregate_records.md § Wire contract](../../../../sql_aggregate_records.md), [docs/sql_aggregate_records.md § Ownership, failure and cost](../../../../sql_aggregate_records.md) |

## B0009

[Lines 47–52](../../../../../src/recovery/sql_aggregate_records.cpp#L47); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void valid(const GroupInfo& value) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Validate group-epoch sequence and flags, including changed/group-changed consistency and input hash. |
| inputs / outputs | Declaration: \`void valid(const GroupInfo& value)\`. Inputs/outputs: Validate group-epoch sequence and flags, including changed/group-changed consistency and input hash. |
| invariants | group_changed implies changed; nonempty group list implies both flags; physical&lt;=input and generation/physical are positive. |
| ownership | All input references/spans are borrowed for the call unless the purpose names an owned return; no fixture/runtime owner escapes this local helper. |
| failure | Inconsistent group flags/frontiers/hash raises ImageFailure(binding). |
| cost | Checks one fixed summary and hash. |
| Design | [src/recovery/sql_aggregate_records.cpp](../../../../../src/recovery/sql_aggregate_records.cpp), [include/crown/recovery/sql_aggregate_records.hpp](../../../../../include/crown/recovery/sql_aggregate_records.hpp), [include/crown/recovery/image.hpp](../../../../../include/crown/recovery/image.hpp), [src/recovery/binary_detail.hpp](../../../../../src/recovery/binary_detail.hpp), [src/frontend/sql_rows_value.hpp](../../../../../src/frontend/sql_rows_value.hpp), [include/crown/frontend/sql_aggregate.hpp](../../../../../include/crown/frontend/sql_aggregate.hpp), [docs/sql_aggregate_records.md § Wire contract](../../../../sql_aggregate_records.md), [docs/sql_aggregate_records.md § Ownership, failure and cost](../../../../sql_aggregate_records.md) |

## B0010

[Lines 53–56](../../../../../src/recovery/sql_aggregate_records.cpp#L53); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void program_valid(const Program& program,const Limits& limits) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Require a genuine bound aggregate program and admit its source-table count under record limits. |
| inputs / outputs | Declaration: \`void program_valid(const Program& program,const Limits& limits)\`. Inputs/outputs: Require a genuine bound aggregate program and admit its source-table count under record limits. |
| invariants | No schema is copied or inferred from a mutable DTO; table admission compares the genuine source program with \`limits.record.tables\`. |
| ownership | All input references/spans are borrowed for the call unless the purpose names an owned return; no fixture/runtime owner escapes this local helper. |
| failure | Missing program or source-table limit failure raises ImageFailure(binding/limit). |
| cost | Reads program metadata and compares source count to one limit. |
| Design | [src/recovery/sql_aggregate_records.cpp](../../../../../src/recovery/sql_aggregate_records.cpp), [include/crown/recovery/sql_aggregate_records.hpp](../../../../../include/crown/recovery/sql_aggregate_records.hpp), [include/crown/recovery/image.hpp](../../../../../include/crown/recovery/image.hpp), [src/recovery/binary_detail.hpp](../../../../../src/recovery/binary_detail.hpp), [src/frontend/sql_rows_value.hpp](../../../../../src/frontend/sql_rows_value.hpp), [include/crown/frontend/sql_aggregate.hpp](../../../../../include/crown/frontend/sql_aggregate.hpp), [docs/sql_aggregate_records.md § Wire contract](../../../../sql_aggregate_records.md), [docs/sql_aggregate_records.md § Ownership, failure and cost](../../../../sql_aggregate_records.md) |

## B0011

[Lines 57–57](../../../../../src/recovery/sql_aggregate_records.cpp#L57); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L57-L57:sha256:1e833819f7ddabad490e1a9bf64d47e10706cc0e7f5462f40f0ef236bcba45a3
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Design note for adjacent code: The genuine source/kernel supply SqlTypes without allocating a schema copy. This is caller guidance recorded as prose, not an executable result. |
| inputs / outputs | No runtime interface is implemented by these comment-only lines. They sit at src/recovery/sql_aggregate_records.cpp lines 55-59; the surrounding declaration/body defines its own inputs and outputs. |
| invariants | The words record the intended use boundary only. They do not add a guard, proof, capability, transaction, durability guarantee, or account charge; verify behavior in the referenced implementation. |
| ownership | Comment text owns no data. Object lifetimes, borrows, and account attribution remain those of the adjacent source objects and their constructors. |
| failure | No failure path is implemented here. Any mentioned failure or recovery rule belongs to the adjacent operation and its existing error carrier. |
| cost | No runtime work is performed by these lines; any cost/bound in the note is not certified by this comment-only card. |
| Design | [src/recovery/sql_aggregate_records.cpp](../../../../../src/recovery/sql_aggregate_records.cpp), [docs/code_specs/files/src/recovery/sql_aggregate_records.cpp.md](sql_aggregate_records.cpp.md), [docs/sql_aggregate_records.md](../../../../sql_aggregate_records.md), [docs/sql_aggregate_session.md](../../../../sql_aggregate_session.md) |

## B0012

[Lines 58–62](../../../../../src/recovery/sql_aggregate_records.cpp#L58); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
auto source_columns(const Program& program,std::uint64_t table) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Resolve a physical table ID against the genuine program and reject a mismatched/nonexistent identity. |
| inputs / outputs | Declaration: \`auto source_columns(const Program& program,std::uint64_t table)\`. Inputs/outputs: Resolve a physical table ID against the genuine program and reject a mismatched/nonexistent identity. |
| invariants | A table is accepted only when vector index and declared TableId agree; invalid identities raise ImageFailure(binding). |
| ownership | Returns a borrowed columns span into the genuine immutable Program; Program must outlive its use. |
| failure | Unknown/mismatched table ID raises ImageFailure(binding). |
| cost | Indexes source metadata and compares one identity. |
| Design | [src/recovery/sql_aggregate_records.cpp](../../../../../src/recovery/sql_aggregate_records.cpp), [include/crown/recovery/sql_aggregate_records.hpp](../../../../../include/crown/recovery/sql_aggregate_records.hpp), [include/crown/recovery/image.hpp](../../../../../include/crown/recovery/image.hpp), [src/recovery/binary_detail.hpp](../../../../../src/recovery/binary_detail.hpp), [src/frontend/sql_rows_value.hpp](../../../../../src/frontend/sql_rows_value.hpp), [include/crown/frontend/sql_aggregate.hpp](../../../../../include/crown/frontend/sql_aggregate.hpp), [docs/sql_aggregate_records.md § Wire contract](../../../../sql_aggregate_records.md), [docs/sql_aggregate_records.md § Ownership, failure and cost](../../../../sql_aggregate_records.md) |

## B0013

[Lines 63–66](../../../../../src/recovery/sql_aggregate_records.cpp#L63); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::size_t fields(const Program& program,bool key) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Return the genuine program's group-key field count or projected output field count. |
| inputs / outputs | Declaration: \`std::size_t fields(const Program& program,bool key)\`. Inputs/outputs: Return the genuine program's group-key field count or projected output field count. |
| invariants | Counts come from immutable kernel group columns and outputs; no caller-declared count is trusted. |
| ownership | Returns one field count by value; retains no program state. |
| failure | Pure metadata access; no error path for an admitted Program. |
| cost | Reads a vector size from immutable metadata. |
| Design | [src/recovery/sql_aggregate_records.cpp](../../../../../src/recovery/sql_aggregate_records.cpp), [include/crown/recovery/sql_aggregate_records.hpp](../../../../../include/crown/recovery/sql_aggregate_records.hpp), [include/crown/recovery/image.hpp](../../../../../include/crown/recovery/image.hpp), [src/recovery/binary_detail.hpp](../../../../../src/recovery/binary_detail.hpp), [src/frontend/sql_rows_value.hpp](../../../../../src/frontend/sql_rows_value.hpp), [include/crown/frontend/sql_aggregate.hpp](../../../../../include/crown/frontend/sql_aggregate.hpp), [docs/sql_aggregate_records.md § Wire contract](../../../../sql_aggregate_records.md), [docs/sql_aggregate_records.md § Ownership, failure and cost](../../../../sql_aggregate_records.md) |

## B0014

[Lines 67–70](../../../../../src/recovery/sql_aggregate_records.cpp#L67); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
frontend::SqlType field_type(const Program& program,bool key,std::size_t i) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Resolve a key field from immutable kernel input types or a value field from projected output types. |
| inputs / outputs | Declaration: \`frontend::SqlType field_type(const Program& program,bool key,std::size_t i)\`. Inputs/outputs: Resolve a key field from immutable kernel input types or a value field from projected output types. |
| invariants | Key types follow kernel input type at each group column; output types follow the projected aggregate output schema. |
| ownership | Returns one SqlType value copied from immutable program metadata. |
| failure | Pure metadata access for an in-range field index; called only after matching row arity. |
| cost | Reads one SQL type from immutable metadata. |
| Design | [src/recovery/sql_aggregate_records.cpp](../../../../../src/recovery/sql_aggregate_records.cpp), [include/crown/recovery/sql_aggregate_records.hpp](../../../../../include/crown/recovery/sql_aggregate_records.hpp), [include/crown/recovery/image.hpp](../../../../../include/crown/recovery/image.hpp), [src/recovery/binary_detail.hpp](../../../../../src/recovery/binary_detail.hpp), [src/frontend/sql_rows_value.hpp](../../../../../src/frontend/sql_rows_value.hpp), [include/crown/frontend/sql_aggregate.hpp](../../../../../include/crown/frontend/sql_aggregate.hpp), [docs/sql_aggregate_records.md § Wire contract](../../../../sql_aggregate_records.md), [docs/sql_aggregate_records.md § Ownership, failure and cost](../../../../sql_aggregate_records.md) |

## B0015

[Lines 71–75](../../../../../src/recovery/sql_aggregate_records.cpp#L71); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void cell_valid(Budget& budget,const Cell& cell,const frontend::SqlType& type) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Charge borrowed TEXT bytes and require the nullable cell to fit the selected SQL type/specification. |
| inputs / outputs | Declaration: \`void cell_valid(Budget& budget,const Cell& cell,const frontend::SqlType& type)\`. Inputs/outputs: Charge borrowed TEXT bytes and require the nullable cell to fit the selected SQL type/specification. |
| invariants | TEXT length is charged before SQL-type/nullability/UTF8/decimal fit validation; bad values raise ImageFailure. |
| ownership | All input references/spans are borrowed for the call unless the purpose names an owned return; no fixture/runtime owner escapes this local helper. |
| failure | Work/type/nullability/UTF8/decimal violation raises ImageFailure(work/scalar). |
| cost | Checks one cell; scans TEXT bytes once when present. |
| Design | [src/recovery/sql_aggregate_records.cpp](../../../../../src/recovery/sql_aggregate_records.cpp), [include/crown/recovery/sql_aggregate_records.hpp](../../../../../include/crown/recovery/sql_aggregate_records.hpp), [include/crown/recovery/image.hpp](../../../../../include/crown/recovery/image.hpp), [src/recovery/binary_detail.hpp](../../../../../src/recovery/binary_detail.hpp), [src/frontend/sql_rows_value.hpp](../../../../../src/frontend/sql_rows_value.hpp), [include/crown/frontend/sql_aggregate.hpp](../../../../../include/crown/frontend/sql_aggregate.hpp), [docs/sql_aggregate_records.md § Wire contract](../../../../sql_aggregate_records.md), [docs/sql_aggregate_records.md § Ownership, failure and cost](../../../../sql_aggregate_records.md) |

## B0016

[Lines 76–78](../../../../../src/recovery/sql_aggregate_records.cpp#L76); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
bool ordered(Budget& budget,std::string_view a,std::string_view b) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Charge the common compared byte prefix and compare two encoded keys lexicographically. |
| inputs / outputs | Declaration: \`bool ordered(Budget& budget,std::string_view a,std::string_view b)\`. Inputs/outputs: Charge the common compared byte prefix and compare two encoded keys lexicographically. |
| invariants | Comparison work charges min(a.size(),b.size()) bytes, then uses bytewise string_view ordering rather than SQL collation. |
| ownership | All input references/spans are borrowed for the call unless the purpose names an owned return; no fixture/runtime owner escapes this local helper. |
| failure | Insufficient work budget raises ImageFailure(work). |
| cost | Compares two keys; charges only the compared prefix bytes. |
| Design | [src/recovery/sql_aggregate_records.cpp](../../../../../src/recovery/sql_aggregate_records.cpp), [include/crown/recovery/sql_aggregate_records.hpp](../../../../../include/crown/recovery/sql_aggregate_records.hpp), [include/crown/recovery/image.hpp](../../../../../include/crown/recovery/image.hpp), [src/recovery/binary_detail.hpp](../../../../../src/recovery/binary_detail.hpp), [src/frontend/sql_rows_value.hpp](../../../../../src/frontend/sql_rows_value.hpp), [include/crown/frontend/sql_aggregate.hpp](../../../../../include/crown/frontend/sql_aggregate.hpp), [docs/sql_aggregate_records.md § Wire contract](../../../../sql_aggregate_records.md), [docs/sql_aggregate_records.md § Ownership, failure and cost](../../../../sql_aggregate_records.md) |

## B0017

[Lines 79–79](../../../../../src/recovery/sql_aggregate_records.cpp#L79); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct KeySlice { std::size_t index,begin,size; };
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Describe one key slice by source group index and packed-buffer byte extent. |
| inputs / outputs | Declaration: \`struct KeySlice\`. Inputs/outputs: Describe one key slice by source group index and packed-buffer byte extent. |
| invariants | KeySlice is a non-owning index/offset/size into per-encode packed buffers. |
| ownership | Fixed index/begin/size values are used while sorting inside key_order; the packed key buffer is local and no key view is returned. |
| failure | Value-only declaration has no error path. |
| cost | Fixed three-size metadata. |
| Design | [src/recovery/sql_aggregate_records.cpp](../../../../../src/recovery/sql_aggregate_records.cpp), [include/crown/recovery/sql_aggregate_records.hpp](../../../../../include/crown/recovery/sql_aggregate_records.hpp), [include/crown/recovery/image.hpp](../../../../../include/crown/recovery/image.hpp), [src/recovery/binary_detail.hpp](../../../../../src/recovery/binary_detail.hpp), [src/frontend/sql_rows_value.hpp](../../../../../src/frontend/sql_rows_value.hpp), [include/crown/frontend/sql_aggregate.hpp](../../../../../include/crown/frontend/sql_aggregate.hpp), [docs/sql_aggregate_records.md § Wire contract](../../../../sql_aggregate_records.md), [docs/sql_aggregate_records.md § Ownership, failure and cost](../../../../sql_aggregate_records.md) |

## B0018

[Lines 80–87](../../../../../src/recovery/sql_aggregate_records.cpp#L80); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L80-L87:sha256:6b0209c4c20c74100121c18d5f2c2ef161f2f72113731423abb3c0c0d08c40bf
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Begins Output, a Writer subclass holding borrowed compiler/limits references, a borrowed group-order span, and value-owned InputInfo before its count/materialization methods. Embedded source note records intended usage: Count-only and materializing passes share validation and byte/work admissions. Every row gets one presence byte per cell; absent tuples use a separate byte. Treat that prose as guidance, not as independently verified executable behavior. |
| inputs / outputs | This span declares a helper type and its member layout; it does not call its operations. Member signatures and constructors in the enclosing file define the actual input/output boundary. |
| invariants | The type is an implementation detail at this scope; callers must use its neighboring validated factory/owner path rather than treat the declaration as a proof. |
| ownership | Views/spans/pointers declared here borrow their backing source; any owned buffers are the explicitly typed account-backed members and follow their own allocator. |
| failure | The declaration itself does not translate runtime errors; construction and member operations may fail according to their definitions and allocation sources. |
| cost | No per-call cost is incurred by the declaration. Object construction/member operations may allocate or traverse according to their concrete member types and definitions. |
| Design | [src/recovery/sql_aggregate_records.cpp](../../../../../src/recovery/sql_aggregate_records.cpp), [docs/code_specs/files/src/recovery/sql_aggregate_records.cpp.md](sql_aggregate_records.cpp.md), [docs/sql_aggregate_records.md](../../../../sql_aggregate_records.md), [docs/sql_aggregate_session.md](../../../../sql_aggregate_session.md) |

## B0019

[Lines 88–90](../../../../../src/recovery/sql_aggregate_records.cpp#L88); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
  void hash(std::span<const char> value) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Validate and append one fixed-width lowercase hash to the output writer. |
| inputs / outputs | Declaration: \`void hash(std::span&lt;const char&gt; value)\`. Inputs/outputs: Validate and append one fixed-width lowercase hash to the output writer. |
| invariants | Invalid digest alphabet raises ImageFault::binding; valid bytes are appended to the writer and charged as visited output. |
| ownership | All input references/spans are borrowed for the call unless the purpose names an owned return; no fixture/runtime owner escapes this local helper. |
| failure | Invalid hex raises ImageFailure(binding); Writer append can propagate std::bad_alloc from its account-backed vector. |
| cost | Scans and writes one fixed hash. |
| Design | [src/recovery/sql_aggregate_records.cpp](../../../../../src/recovery/sql_aggregate_records.cpp), [include/crown/recovery/sql_aggregate_records.hpp](../../../../../include/crown/recovery/sql_aggregate_records.hpp), [include/crown/recovery/image.hpp](../../../../../include/crown/recovery/image.hpp), [src/recovery/binary_detail.hpp](../../../../../src/recovery/binary_detail.hpp), [src/frontend/sql_rows_value.hpp](../../../../../src/frontend/sql_rows_value.hpp), [include/crown/frontend/sql_aggregate.hpp](../../../../../include/crown/frontend/sql_aggregate.hpp), [docs/sql_aggregate_records.md § Wire contract](../../../../sql_aggregate_records.md), [docs/sql_aggregate_records.md § Ownership, failure and cost](../../../../sql_aggregate_records.md) |

## B0020

[Lines 91–98](../../../../../src/recovery/sql_aggregate_records.cpp#L91); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
  template<class TypeAt> void row(std::span<const Cell> cells,std::size_t expected,TypeAt type_at) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Count a complete typed nullable row and optionally serialize it under field/row/work/byte limits. |
| inputs / outputs | Declaration: \`template&lt;class TypeAt&gt; void row(std::span&lt;const Cell&gt; cells,std::size_t expected,TypeAt type_at)\`. Inputs/outputs: Count a complete typed nullable row and optionally serialize it under field/row/work/byte limits. |
| invariants | Each row consumes a row admission and exact field count; cell values use genuine SQL types and Writer enforces bytes/work ceilings. |
| ownership | All input references/spans are borrowed for the call unless the purpose names an owned return; no fixture/runtime owner escapes this local helper. |
| failure | Shape/type/limit errors raise ImageFailure; materializing output can propagate std::bad_alloc. |
| cost | Visits one row's fields/cells and charges each field/byte pass. |
| Design | [src/recovery/sql_aggregate_records.cpp](../../../../../src/recovery/sql_aggregate_records.cpp), [include/crown/recovery/sql_aggregate_records.hpp](../../../../../include/crown/recovery/sql_aggregate_records.hpp), [include/crown/recovery/image.hpp](../../../../../include/crown/recovery/image.hpp), [src/recovery/binary_detail.hpp](../../../../../src/recovery/binary_detail.hpp), [src/frontend/sql_rows_value.hpp](../../../../../src/frontend/sql_rows_value.hpp), [include/crown/frontend/sql_aggregate.hpp](../../../../../include/crown/frontend/sql_aggregate.hpp), [docs/sql_aggregate_records.md § Wire contract](../../../../sql_aggregate_records.md), [docs/sql_aggregate_records.md § Ownership, failure and cost](../../../../sql_aggregate_records.md) |

## B0021

[Lines 99–101](../../../../../src/recovery/sql_aggregate_records.cpp#L99); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
  void group_row(const runtime::aggregate::Tuple& tuple,bool key) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Require a live aggregate tuple and serialize its typed key or projected values row. |
| inputs / outputs | Declaration: \`void group_row(const runtime::aggregate::Tuple& tuple,bool key)\`. Inputs/outputs: Require a live aggregate tuple and serialize its typed key or projected values row. |
| invariants | Tuple must be engaged; key/value arity and each cell type are checked by row(). |
| ownership | All input references/spans are borrowed for the call unless the purpose names an owned return; no fixture/runtime owner escapes this local helper. |
| failure | Disengaged Tuple or invalid row raises ImageFailure; writer allocation may propagate std::bad_alloc. |
| cost | Visits one tuple row and its fields. |
| Design | [src/recovery/sql_aggregate_records.cpp](../../../../../src/recovery/sql_aggregate_records.cpp), [include/crown/recovery/sql_aggregate_records.hpp](../../../../../include/crown/recovery/sql_aggregate_records.hpp), [include/crown/recovery/image.hpp](../../../../../include/crown/recovery/image.hpp), [src/recovery/binary_detail.hpp](../../../../../src/recovery/binary_detail.hpp), [src/frontend/sql_rows_value.hpp](../../../../../src/frontend/sql_rows_value.hpp), [include/crown/frontend/sql_aggregate.hpp](../../../../../include/crown/frontend/sql_aggregate.hpp), [docs/sql_aggregate_records.md § Wire contract](../../../../sql_aggregate_records.md), [docs/sql_aggregate_records.md § Ownership, failure and cost](../../../../sql_aggregate_records.md) |

## B0022

[Lines 102–105](../../../../../src/recovery/sql_aggregate_records.cpp#L102); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
  void write(const WalHeader& value) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Validate and serialize the WalHeader payload fields in wire order. |
| inputs / outputs | Declaration: \`void write(const WalHeader& value)\`. Inputs/outputs: Validate and serialize the WalHeader payload fields in wire order. |
| invariants | All digest/binding/frontier fields are validated before fixed-width serialization in the documented order. |
| ownership | All input references/spans are borrowed for the call unless the purpose names an owned return; no fixture/runtime owner escapes this local helper. |
| failure | Invalid binding/frontier/hash raises ImageFailure; output-buffer allocation propagates std::bad_alloc. |
| cost | Writes fixed header fields. |
| Design | [src/recovery/sql_aggregate_records.cpp](../../../../../src/recovery/sql_aggregate_records.cpp), [include/crown/recovery/sql_aggregate_records.hpp](../../../../../include/crown/recovery/sql_aggregate_records.hpp), [include/crown/recovery/image.hpp](../../../../../include/crown/recovery/image.hpp), [src/recovery/binary_detail.hpp](../../../../../src/recovery/binary_detail.hpp), [src/frontend/sql_rows_value.hpp](../../../../../src/frontend/sql_rows_value.hpp), [include/crown/frontend/sql_aggregate.hpp](../../../../../include/crown/frontend/sql_aggregate.hpp), [docs/sql_aggregate_records.md § Wire contract](../../../../sql_aggregate_records.md), [docs/sql_aggregate_records.md § Ownership, failure and cost](../../../../sql_aggregate_records.md) |

## B0023

[Lines 106–108](../../../../../src/recovery/sql_aggregate_records.cpp#L106); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
  void write(const SinkHeader& value) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Validate and serialize the SinkHeader payload fields in wire order. |
| inputs / outputs | Declaration: \`void write(const SinkHeader& value)\`. Inputs/outputs: Validate and serialize the SinkHeader payload fields in wire order. |
| invariants | Binding, lowercase sink ID and base sequence are serialized after header validation. |
| ownership | All input references/spans are borrowed for the call unless the purpose names an owned return; no fixture/runtime owner escapes this local helper. |
| failure | Invalid sink metadata raises ImageFailure; output-buffer allocation propagates std::bad_alloc. |
| cost | Writes fixed sink-header fields. |
| Design | [src/recovery/sql_aggregate_records.cpp](../../../../../src/recovery/sql_aggregate_records.cpp), [include/crown/recovery/sql_aggregate_records.hpp](../../../../../include/crown/recovery/sql_aggregate_records.hpp), [include/crown/recovery/image.hpp](../../../../../include/crown/recovery/image.hpp), [src/recovery/binary_detail.hpp](../../../../../src/recovery/binary_detail.hpp), [src/frontend/sql_rows_value.hpp](../../../../../src/frontend/sql_rows_value.hpp), [include/crown/frontend/sql_aggregate.hpp](../../../../../include/crown/frontend/sql_aggregate.hpp), [docs/sql_aggregate_records.md § Wire contract](../../../../sql_aggregate_records.md), [docs/sql_aggregate_records.md § Ownership, failure and cost](../../../../sql_aggregate_records.md) |

## B0024

[Lines 109–133](../../../../../src/recovery/sql_aggregate_records.cpp#L109); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
  void write(const InputView& value) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Validate and serialize one InputView, copying replacement/source/reader fields into one transport frame. |
| inputs / outputs | Declaration: \`void write(const InputView& value)\`. Inputs/outputs: Validate and serialize one InputView, copying replacement/source/reader fields into one transport frame. |
| invariants | command_sequence must be positive; replacements/source bytes are bounded and type-checked; source names are UTF8; before/after arithmetic remains runtime work. |
| ownership | All input references/spans are borrowed for the call unless the purpose names an owned return; no fixture/runtime owner escapes this local helper. |
| failure | Invalid sequence/table/type/source/reader/budget raises ImageFailure; output allocation propagates std::bad_alloc. |
| cost | Scans one input's replacements/cells and optional source bytes. |
| Design | [src/recovery/sql_aggregate_records.cpp](../../../../../src/recovery/sql_aggregate_records.cpp), [include/crown/recovery/sql_aggregate_records.hpp](../../../../../include/crown/recovery/sql_aggregate_records.hpp), [include/crown/recovery/image.hpp](../../../../../include/crown/recovery/image.hpp), [src/recovery/binary_detail.hpp](../../../../../src/recovery/binary_detail.hpp), [src/frontend/sql_rows_value.hpp](../../../../../src/frontend/sql_rows_value.hpp), [include/crown/frontend/sql_aggregate.hpp](../../../../../include/crown/frontend/sql_aggregate.hpp), [docs/sql_aggregate_records.md § Wire contract](../../../../sql_aggregate_records.md), [docs/sql_aggregate_records.md § Ownership, failure and cost](../../../../sql_aggregate_records.md) |

## B0025

[Lines 134–138](../../../../../src/recovery/sql_aggregate_records.cpp#L134); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
  void write(const Commit& value) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Validate and serialize a Commit identity, sequences, and output frame digest/length. |
| inputs / outputs | Declaration: \`void write(const Commit& value)\`. Inputs/outputs: Validate and serialize a Commit identity, sequences, and output frame digest/length. |
| invariants | Commit validity is structural and digest syntax only; it does not verify the referenced sink bytes or durable sync. |
| ownership | All input references/spans are borrowed for the call unless the purpose names an owned return; no fixture/runtime owner escapes this local helper. |
| failure | Invalid fields raise ImageFailure; output allocation propagates std::bad_alloc. |
| cost | Writes fixed commit fields. |
| Design | [src/recovery/sql_aggregate_records.cpp](../../../../../src/recovery/sql_aggregate_records.cpp), [include/crown/recovery/sql_aggregate_records.hpp](../../../../../include/crown/recovery/sql_aggregate_records.hpp), [include/crown/recovery/image.hpp](../../../../../include/crown/recovery/image.hpp), [src/recovery/binary_detail.hpp](../../../../../src/recovery/binary_detail.hpp), [src/frontend/sql_rows_value.hpp](../../../../../src/frontend/sql_rows_value.hpp), [include/crown/frontend/sql_aggregate.hpp](../../../../../include/crown/frontend/sql_aggregate.hpp), [docs/sql_aggregate_records.md § Wire contract](../../../../sql_aggregate_records.md), [docs/sql_aggregate_records.md § Ownership, failure and cost](../../../../sql_aggregate_records.md) |

## B0026

[Lines 139–142](../../../../../src/recovery/sql_aggregate_records.cpp#L139); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
  void write(const Reject& value) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Validate and serialize a Reject identity, unchanged physical sequence, and allowlisted reason. |
| inputs / outputs | Declaration: \`void write(const Reject& value)\`. Inputs/outputs: Validate and serialize a Reject identity, unchanged physical sequence, and allowlisted reason. |
| invariants | Reject accepts only the stable semantic allowlist; resource/contract failure has no encoded rejection reason. |
| ownership | All input references/spans are borrowed for the call unless the purpose names an owned return; no fixture/runtime owner escapes this local helper. |
| failure | Invalid tag fields raise ImageFailure; output allocation propagates std::bad_alloc. |
| cost | Writes fixed reject fields. |
| Design | [src/recovery/sql_aggregate_records.cpp](../../../../../src/recovery/sql_aggregate_records.cpp), [include/crown/recovery/sql_aggregate_records.hpp](../../../../../include/crown/recovery/sql_aggregate_records.hpp), [include/crown/recovery/image.hpp](../../../../../include/crown/recovery/image.hpp), [src/recovery/binary_detail.hpp](../../../../../src/recovery/binary_detail.hpp), [src/frontend/sql_rows_value.hpp](../../../../../src/frontend/sql_rows_value.hpp), [include/crown/frontend/sql_aggregate.hpp](../../../../../include/crown/frontend/sql_aggregate.hpp), [docs/sql_aggregate_records.md § Wire contract](../../../../sql_aggregate_records.md), [docs/sql_aggregate_records.md § Ownership, failure and cost](../../../../sql_aggregate_records.md) |

## B0027

[Lines 143–162](../../../../../src/recovery/sql_aggregate_records.cpp#L143); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
  void write(const GroupEpochView& value) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Validate and serialize a GroupEpochView using its precomputed canonical key order. |
| inputs / outputs | Declaration: \`void write(const GroupEpochView& value)\`. Inputs/outputs: Validate and serialize a GroupEpochView using its precomputed canonical key order. |
| invariants | GroupEpoch metadata must be consistent; every key/value row is complete and type checked, and encoded order comes from \`order\`. |
| ownership | All input references/spans are borrowed for the call unless the purpose names an owned return; no fixture/runtime owner escapes this local helper. |
| failure | Invalid change metadata/key/value/order raises ImageFailure; output allocation propagates std::bad_alloc. |
| cost | Scans each changed key and optional before/after values. |
| Design | [src/recovery/sql_aggregate_records.cpp](../../../../../src/recovery/sql_aggregate_records.cpp), [include/crown/recovery/sql_aggregate_records.hpp](../../../../../include/crown/recovery/sql_aggregate_records.hpp), [include/crown/recovery/image.hpp](../../../../../include/crown/recovery/image.hpp), [src/recovery/binary_detail.hpp](../../../../../src/recovery/binary_detail.hpp), [src/frontend/sql_rows_value.hpp](../../../../../src/frontend/sql_rows_value.hpp), [include/crown/frontend/sql_aggregate.hpp](../../../../../include/crown/frontend/sql_aggregate.hpp), [docs/sql_aggregate_records.md § Wire contract](../../../../sql_aggregate_records.md), [docs/sql_aggregate_records.md § Ownership, failure and cost](../../../../sql_aggregate_records.md) |

## B0028

[Lines 163–179](../../../../../src/recovery/sql_aggregate_records.cpp#L163); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
  Inspected frame(std::uint64_t ordinal,const PayloadView& payload) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Build one payload body under a record ordinal, selecting its wire tag and retaining compact decoded metadata. |
| inputs / outputs | Declaration: \`Inspected frame(std::uint64_t ordinal,const PayloadView& payload)\`. Inputs/outputs: Build one payload body under a record ordinal, selecting its wire tag and retaining compact decoded metadata. |
| invariants | Only WalHeader/SinkHeader are allowed at ordinal zero; Commit/Reject must reference an earlier ordinal; kind derives from variant index. |
| ownership | Returns fixed Inspected metadata by value; payload views are summarized into owned fixed fields rather than retaining InputView/GroupEpochView spans. |
| failure | Ordinal/tag/payload contract errors raise ImageFailure; output allocation propagates std::bad_alloc. |
| cost | Builds one record payload and checks ordinal/tag fields. |
| Design | [src/recovery/sql_aggregate_records.cpp](../../../../../src/recovery/sql_aggregate_records.cpp), [include/crown/recovery/sql_aggregate_records.hpp](../../../../../include/crown/recovery/sql_aggregate_records.hpp), [include/crown/recovery/image.hpp](../../../../../include/crown/recovery/image.hpp), [src/recovery/binary_detail.hpp](../../../../../src/recovery/binary_detail.hpp), [src/frontend/sql_rows_value.hpp](../../../../../src/frontend/sql_rows_value.hpp), [include/crown/frontend/sql_aggregate.hpp](../../../../../include/crown/frontend/sql_aggregate.hpp), [docs/sql_aggregate_records.md § Wire contract](../../../../sql_aggregate_records.md), [docs/sql_aggregate_records.md § Ownership, failure and cost](../../../../sql_aggregate_records.md) |

## B0029

[Lines 180–188](../../../../../src/recovery/sql_aggregate_records.cpp#L180); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L180-L188:sha256:0a0cceffe11cd9782fa370f328fac1eae704789941f7285580c4da6d30f28e26
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Begins Input, a Reader subclass that borrows the compiler/limits and optional caller-owned destination vectors for cells and source replacements; null destinations support inspection without materialization. Embedded source note records intended usage: Parser borrows bytes. Null output pointers keep inspection allocation-free; decode reserves both flat arrays before this same typed parsing pass. Treat that prose as guidance, not as independently verified executable behavior. |
| inputs / outputs | This span declares a helper type and its member layout; it does not call its operations. Member signatures and constructors in the enclosing file define the actual input/output boundary. |
| invariants | The type is an implementation detail at this scope; callers must use its neighboring validated factory/owner path rather than treat the declaration as a proof. |
| ownership | Views/spans/pointers declared here borrow their backing source; any owned buffers are the explicitly typed account-backed members and follow their own allocator. |
| failure | The declaration itself does not translate runtime errors; construction and member operations may fail according to their definitions and allocation sources. |
| cost | No per-call cost is incurred by the declaration. Object construction/member operations may allocate or traverse according to their concrete member types and definitions. |
| Design | [src/recovery/sql_aggregate_records.cpp](../../../../../src/recovery/sql_aggregate_records.cpp), [docs/code_specs/files/src/recovery/sql_aggregate_records.cpp.md](sql_aggregate_records.cpp.md), [docs/sql_aggregate_records.md](../../../../sql_aggregate_records.md), [docs/sql_aggregate_session.md](../../../../sql_aggregate_session.md) |

## B0030

[Lines 189–189](../../../../../src/recovery/sql_aggregate_records.cpp#L189); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
  bool boolean() { const auto value=integer(1);require(value<=1);return value!=0; }
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Read and validate a single 0/1 presence or Boolean flag. |
| inputs / outputs | Declaration: \`bool boolean()\`. Inputs/outputs: Read and validate a single 0/1 presence or Boolean flag. |
| invariants | Every flag byte must be exactly 0 or 1; larger values raise ImageFailure. |
| ownership | All input references/spans are borrowed for the call unless the purpose names an owned return; no fixture/runtime owner escapes this local helper. |
| failure | Flag values above one raise ImageFailure(corrupt). |
| cost | Reads one byte. |
| Design | [src/recovery/sql_aggregate_records.cpp](../../../../../src/recovery/sql_aggregate_records.cpp), [include/crown/recovery/sql_aggregate_records.hpp](../../../../../include/crown/recovery/sql_aggregate_records.hpp), [include/crown/recovery/image.hpp](../../../../../include/crown/recovery/image.hpp), [src/recovery/binary_detail.hpp](../../../../../src/recovery/binary_detail.hpp), [src/frontend/sql_rows_value.hpp](../../../../../src/frontend/sql_rows_value.hpp), [include/crown/frontend/sql_aggregate.hpp](../../../../../include/crown/frontend/sql_aggregate.hpp), [docs/sql_aggregate_records.md § Wire contract](../../../../sql_aggregate_records.md), [docs/sql_aggregate_records.md § Ownership, failure and cost](../../../../sql_aggregate_records.md) |

## B0031

[Lines 190–193](../../../../../src/recovery/sql_aggregate_records.cpp#L190); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
  template<std::size_t N> std::array<char,N> hash() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Read exactly N borrowed bytes into an owning fixed array and require lowercase hex. |
| inputs / outputs | Declaration: \`template&lt;std::size_t N&gt; std::array&lt;char,N&gt; hash()\`. Inputs/outputs: Read exactly N borrowed bytes into an owning fixed array and require lowercase hex. |
| invariants | take(N) is bounds/work checked and the copied array must be lowercase ASCII hex. |
| ownership | Returns a fixed std::array by value; read input is borrowed during the call. |
| failure | Short input raises ImageFailure(corrupt); non-hex raises ImageFailure(binding). |
| cost | Reads/copies N bytes and scans them for hex. |
| Design | [src/recovery/sql_aggregate_records.cpp](../../../../../src/recovery/sql_aggregate_records.cpp), [include/crown/recovery/sql_aggregate_records.hpp](../../../../../include/crown/recovery/sql_aggregate_records.hpp), [include/crown/recovery/image.hpp](../../../../../include/crown/recovery/image.hpp), [src/recovery/binary_detail.hpp](../../../../../src/recovery/binary_detail.hpp), [src/frontend/sql_rows_value.hpp](../../../../../src/frontend/sql_rows_value.hpp), [include/crown/frontend/sql_aggregate.hpp](../../../../../include/crown/frontend/sql_aggregate.hpp), [docs/sql_aggregate_records.md § Wire contract](../../../../sql_aggregate_records.md), [docs/sql_aggregate_records.md § Ownership, failure and cost](../../../../sql_aggregate_records.md) |

## B0032

[Lines 194–194](../../../../../src/recovery/sql_aggregate_records.cpp#L194); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
  Binding binding() { return {hash<32>(),hash<64>()}; }
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Read the fixed 32-byte query ID and 64-byte descriptor hash into a Binding. |
| inputs / outputs | Declaration: \`Binding binding()\`. Inputs/outputs: Read the fixed 32-byte query ID and 64-byte descriptor hash into a Binding. |
| invariants | Binding byte order is query ID 32 followed by descriptor digest 64. |
| ownership | Returns a fixed Binding value by value; no input bytes are retained. |
| failure | Short input or invalid binding digest raises ImageFailure. |
| cost | Reads 96 fixed bytes. |
| Design | [src/recovery/sql_aggregate_records.cpp](../../../../../src/recovery/sql_aggregate_records.cpp), [include/crown/recovery/sql_aggregate_records.hpp](../../../../../include/crown/recovery/sql_aggregate_records.hpp), [include/crown/recovery/image.hpp](../../../../../include/crown/recovery/image.hpp), [src/recovery/binary_detail.hpp](../../../../../src/recovery/binary_detail.hpp), [src/frontend/sql_rows_value.hpp](../../../../../src/frontend/sql_rows_value.hpp), [include/crown/frontend/sql_aggregate.hpp](../../../../../include/crown/frontend/sql_aggregate.hpp), [docs/sql_aggregate_records.md § Wire contract](../../../../sql_aggregate_records.md), [docs/sql_aggregate_records.md § Ownership, failure and cost](../../../../sql_aggregate_records.md) |

## B0033

[Lines 195–203](../../../../../src/recovery/sql_aggregate_records.cpp#L195); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
  template<class TypeAt> std::string_view row(std::size_t expected,TypeAt type_at) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Read a typed nullable row, optionally materialize its cells, and return its borrowed encoded extent. |
| inputs / outputs | Declaration: \`template&lt;class TypeAt&gt; std::string_view row(std::size_t expected,TypeAt type_at)\`. Inputs/outputs: Read a typed nullable row, optionally materialize its cells, and return its borrowed encoded extent. |
| invariants | Count equals genuine schema arity; each presence/scalar is parsed and validated; returned bytes alias input. |
| ownership | Returns a string_view into the parser's borrowed input; caller input must outlive the view. |
| failure | Truncation, wrong arity, malformed scalar/type, limit/work violation raises ImageFailure; optional vector growth can throw std::bad_alloc. |
| cost | Scans one row's fields and scalar bytes. |
| Design | [src/recovery/sql_aggregate_records.cpp](../../../../../src/recovery/sql_aggregate_records.cpp), [include/crown/recovery/sql_aggregate_records.hpp](../../../../../include/crown/recovery/sql_aggregate_records.hpp), [include/crown/recovery/image.hpp](../../../../../include/crown/recovery/image.hpp), [src/recovery/binary_detail.hpp](../../../../../src/recovery/binary_detail.hpp), [src/frontend/sql_rows_value.hpp](../../../../../src/frontend/sql_rows_value.hpp), [include/crown/frontend/sql_aggregate.hpp](../../../../../include/crown/frontend/sql_aggregate.hpp), [docs/sql_aggregate_records.md § Wire contract](../../../../sql_aggregate_records.md), [docs/sql_aggregate_records.md § Ownership, failure and cost](../../../../sql_aggregate_records.md) |

## B0034

[Lines 204–206](../../../../../src/recovery/sql_aggregate_records.cpp#L204); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
  std::string_view group_row(bool key) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Read a group key or projected-value row using types from the genuine immutable program. |
| inputs / outputs | Declaration: \`std::string_view group_row(bool key)\`. Inputs/outputs: Read a group key or projected-value row using types from the genuine immutable program. |
| invariants | Group-key rows use complete grouping-key input types; before/after rows use projected output types. |
| ownership | Returns a row string_view into the parser's borrowed input; no row bytes are copied here. |
| failure | Malformed/incomplete row or SQL type mismatch raises ImageFailure. |
| cost | Scans one group row's fields and scalar bytes. |
| Design | [src/recovery/sql_aggregate_records.cpp](../../../../../src/recovery/sql_aggregate_records.cpp), [include/crown/recovery/sql_aggregate_records.hpp](../../../../../include/crown/recovery/sql_aggregate_records.hpp), [include/crown/recovery/image.hpp](../../../../../include/crown/recovery/image.hpp), [src/recovery/binary_detail.hpp](../../../../../src/recovery/binary_detail.hpp), [src/frontend/sql_rows_value.hpp](../../../../../src/frontend/sql_rows_value.hpp), [include/crown/frontend/sql_aggregate.hpp](../../../../../include/crown/frontend/sql_aggregate.hpp), [docs/sql_aggregate_records.md § Wire contract](../../../../sql_aggregate_records.md), [docs/sql_aggregate_records.md § Ownership, failure and cost](../../../../sql_aggregate_records.md) |

## B0035

[Lines 207–230](../../../../../src/recovery/sql_aggregate_records.cpp#L207); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
  InputInfo item() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Decode one Input body, recording replacement/source extents and reader progress while materializing requested cells. |
| inputs / outputs | Declaration: \`InputInfo item()\`. Inputs/outputs: Decode one Input body, recording replacement/source extents and reader progress while materializing requested cells. |
| invariants | Replacement count, rows, source bytes and counters are bounded; returned source/name extents are offsets into borrowed input bytes. |
| ownership | Returns InputInfo metadata by value; source text is represented by offsets into borrowed frame bytes. |
| failure | Bad sequence/count/table/source/reader/UTF8/work raises ImageFailure; decoded vector insertion may throw std::bad_alloc. |
| cost | Scans one input record and its replacements/source metadata. |
| Design | [src/recovery/sql_aggregate_records.cpp](../../../../../src/recovery/sql_aggregate_records.cpp), [include/crown/recovery/sql_aggregate_records.hpp](../../../../../include/crown/recovery/sql_aggregate_records.hpp), [include/crown/recovery/image.hpp](../../../../../include/crown/recovery/image.hpp), [src/recovery/binary_detail.hpp](../../../../../src/recovery/binary_detail.hpp), [src/frontend/sql_rows_value.hpp](../../../../../src/frontend/sql_rows_value.hpp), [include/crown/frontend/sql_aggregate.hpp](../../../../../include/crown/frontend/sql_aggregate.hpp), [docs/sql_aggregate_records.md § Wire contract](../../../../sql_aggregate_records.md), [docs/sql_aggregate_records.md § Ownership, failure and cost](../../../../sql_aggregate_records.md) |

## B0036

[Lines 231–243](../../../../../src/recovery/sql_aggregate_records.cpp#L231); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
  GroupInfo groups() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Decode group-epoch metadata and require strictly ascending distinct encoded keys and valid before/after rows. |
| inputs / outputs | Declaration: \`GroupInfo groups()\`. Inputs/outputs: Decode group-epoch metadata and require strictly ascending distinct encoded keys and valid before/after rows. |
| invariants | Group metadata must satisfy valid(); each full wire key strictly exceeds the previous, at least one side exists, and present sides differ bytewise. |
| ownership | Returns fixed GroupInfo metadata by value; group row bytes are not retained. |
| failure | Invalid epoch flags, key order/duplicate, row shape, or unchanged before/after pair raises ImageFailure. |
| cost | Scans each group key/value row and compares sorted key extents. |
| Design | [src/recovery/sql_aggregate_records.cpp](../../../../../src/recovery/sql_aggregate_records.cpp), [include/crown/recovery/sql_aggregate_records.hpp](../../../../../include/crown/recovery/sql_aggregate_records.hpp), [include/crown/recovery/image.hpp](../../../../../include/crown/recovery/image.hpp), [src/recovery/binary_detail.hpp](../../../../../src/recovery/binary_detail.hpp), [src/frontend/sql_rows_value.hpp](../../../../../src/frontend/sql_rows_value.hpp), [include/crown/frontend/sql_aggregate.hpp](../../../../../include/crown/frontend/sql_aggregate.hpp), [docs/sql_aggregate_records.md § Wire contract](../../../../sql_aggregate_records.md), [docs/sql_aggregate_records.md § Ownership, failure and cost](../../../../sql_aggregate_records.md) |

## B0037

[Lines 244–266](../../../../../src/recovery/sql_aggregate_records.cpp#L244); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
  Inspected body() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Decode one known record kind, validate all payload fields/ordinals, and reject trailing bytes. |
| inputs / outputs | Declaration: \`Inspected body()\`. Inputs/outputs: Decode one known record kind, validate all payload fields/ordinals, and reject trailing bytes. |
| invariants | Unknown tags, invalid fields, ordinal violations, and any trailing bytes raise ImageFailure; no native decision is replayed. |
| ownership | Returns fixed Inspected metadata by value; no input span or decoded cell vector is retained. |
| failure | Unknown kind, invalid payload, sequence relation or trailing bytes raises ImageFailure. |
| cost | Scans one complete payload and requires exact exhaustion. |
| Design | [src/recovery/sql_aggregate_records.cpp](../../../../../src/recovery/sql_aggregate_records.cpp), [include/crown/recovery/sql_aggregate_records.hpp](../../../../../include/crown/recovery/sql_aggregate_records.hpp), [include/crown/recovery/image.hpp](../../../../../include/crown/recovery/image.hpp), [src/recovery/binary_detail.hpp](../../../../../src/recovery/binary_detail.hpp), [src/frontend/sql_rows_value.hpp](../../../../../src/frontend/sql_rows_value.hpp), [include/crown/frontend/sql_aggregate.hpp](../../../../../include/crown/frontend/sql_aggregate.hpp), [docs/sql_aggregate_records.md § Wire contract](../../../../sql_aggregate_records.md), [docs/sql_aggregate_records.md § Ownership, failure and cost](../../../../sql_aggregate_records.md) |

## B0038

[Lines 267–270](../../../../../src/recovery/sql_aggregate_records.cpp#L267); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L267-L270:sha256:566d44b24c148bf2de92fd296ca76677a8006099dd9c432c965d4bf7b6d640c9
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Closes the enclosing helper type at this source boundary; this is a lexical delimiter, not an operation. Trailing source note states: Protect the length before using it. Exact frames reject trailing bytes; complete corruption is distinct from a file owner's future torn-tail policy. It remains prose guidance, not a certified executable claim. |
| inputs / outputs | No runtime input or output. Declarations following the span leave the preceding C++ scope. |
| invariants | The delimiter ends the preceding scope's visibility/linkage region; it adds no validation, publication, ownership transfer, or runtime authority. Any trailing comment in this block is guidance only and adds no runtime invariant. |
| ownership | The delimiter adds no owner. If it ends a function/block with live automatic objects, their normal destructors release those objects; namespace and type-definition closes change no existing object's lifetime. |
| failure | No explicit failure translation or catch is added. If a function/block exit destroys automatic objects, exception behavior follows those destructors; namespace/type closes have no runtime failure path. |
| cost | The delimiter adds no algorithmic work. A function/block exit can run existing automatic-object destructors and cleanup; namespace/type closes have no runtime cost. |
| Design | [src/recovery/sql_aggregate_records.cpp](../../../../../src/recovery/sql_aggregate_records.cpp), [docs/code_specs/files/src/recovery/sql_aggregate_records.cpp.md](sql_aggregate_records.cpp.md), [docs/sql_aggregate_records.md](../../../../sql_aggregate_records.md), [docs/sql_aggregate_session.md](../../../../sql_aggregate_session.md) |

## B0039

[Lines 271–283](../../../../../src/recovery/sql_aggregate_records.cpp#L271); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Inspected inspect_frame(const Program& program,std::string_view bytes,const Limits& limits,Budget& budget) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Validate a complete frame's magic/version, prefix/body hashes, exact length, program schema, payload, and charged statistics. |
| inputs / outputs | Declaration: \`Inspected inspect_frame(const Program& program,std::string_view bytes,const Limits& limits,Budget& budget)\`. Inputs/outputs: Validate a complete frame's magic/version, prefix/body hashes, exact length, program schema, payload, and charged statistics. |
| invariants | The exact length and both SHA256 checksums are required before the complete typed payload is returned; stats report byte/work/row admissions only. |
| ownership | Returns fixed Inspected metadata by value; bytes/program are borrowed only for the call. |
| failure | Malformed frame/program/limit/work failures raise ImageFailure; no payload allocation is made here. |
| cost | Visits the frame prefix/body for checksums and parse; work admissions record those byte visits. |
| Design | [src/recovery/sql_aggregate_records.cpp](../../../../../src/recovery/sql_aggregate_records.cpp), [include/crown/recovery/sql_aggregate_records.hpp](../../../../../include/crown/recovery/sql_aggregate_records.hpp), [include/crown/recovery/image.hpp](../../../../../include/crown/recovery/image.hpp), [src/recovery/binary_detail.hpp](../../../../../src/recovery/binary_detail.hpp), [src/frontend/sql_rows_value.hpp](../../../../../src/frontend/sql_rows_value.hpp), [include/crown/frontend/sql_aggregate.hpp](../../../../../include/crown/frontend/sql_aggregate.hpp), [docs/sql_aggregate_records.md § Wire contract](../../../../sql_aggregate_records.md), [docs/sql_aggregate_records.md § Ownership, failure and cost](../../../../sql_aggregate_records.md) |

## B0040

[Lines 284–286](../../../../../src/recovery/sql_aggregate_records.cpp#L284); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L284-L286:sha256:715dc403fccd3db1bc4a77def1cf2354a7f56951d4e92659b73571d67cca649d
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Design note for adjacent code: One compact key buffer plus one index vector; no per-group owning allocation. Sorting compares full nullable typed wire keys, independent of producer order. This is caller guidance recorded as prose, not an executable result. |
| inputs / outputs | No runtime interface is implemented by these comment-only lines. They sit at src/recovery/sql_aggregate_records.cpp lines 282-288; the surrounding declaration/body defines its own inputs and outputs. |
| invariants | The words record the intended use boundary only. They do not add a guard, proof, capability, transaction, durability guarantee, or account charge; verify behavior in the referenced implementation. |
| ownership | Comment text owns no data. Object lifetimes, borrows, and account attribution remain those of the adjacent source objects and their constructors. |
| failure | No failure path is implemented here. Any mentioned failure or recovery rule belongs to the adjacent operation and its existing error carrier. |
| cost | No runtime work is performed by these lines; any cost/bound in the note is not certified by this comment-only card. |
| Design | [src/recovery/sql_aggregate_records.cpp](../../../../../src/recovery/sql_aggregate_records.cpp), [docs/code_specs/files/src/recovery/sql_aggregate_records.cpp.md](sql_aggregate_records.cpp.md), [docs/sql_aggregate_records.md](../../../../sql_aggregate_records.md), [docs/sql_aggregate_session.md](../../../../sql_aggregate_session.md) |

## B0041

[Lines 287–304](../../../../../src/recovery/sql_aggregate_records.cpp#L287); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
ImageVector<KeySlice> key_order(const resource::MemoryAccount& account,const Program& program,
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Canonicalize GroupEpoch changes with one packed key buffer and index array, charging sort/comparison work and rejecting duplicate keys. |
| inputs / outputs | Declaration: \`ImageVector&lt;KeySlice&gt; key_order(const resource::MemoryAccount& account,const Program& program, const PayloadView& payload,const Limits& limits,Budget& budget)\`. Inputs/outputs: Canonicalize GroupEpoch changes with one packed key buffer and index array, charging sort/comparison work and rejecting duplicate keys. |
| invariants | Only group keys are packed/sorted; sort is strict byte order and duplicate full encodings reject; caller account funds key/index buffers. |
| ownership | Returned ImageVector owns fixed index/begin/size values; the packed key buffer is local and destroyed on return. Later encoding consumes each sorted index only; no key view escapes. |
| failure | Malformed key/cell, budget failure, account denial or vector allocation can fail; ImageFailure/std::bad_alloc propagate without translation. |
| cost | Two key materialization passes plus index sort and strict adjacent duplicate check; comparison-byte cost is charged. |
| Design | [src/recovery/sql_aggregate_records.cpp](../../../../../src/recovery/sql_aggregate_records.cpp), [include/crown/recovery/sql_aggregate_records.hpp](../../../../../include/crown/recovery/sql_aggregate_records.hpp), [include/crown/recovery/image.hpp](../../../../../include/crown/recovery/image.hpp), [src/recovery/binary_detail.hpp](../../../../../src/recovery/binary_detail.hpp), [src/frontend/sql_rows_value.hpp](../../../../../src/frontend/sql_rows_value.hpp), [include/crown/frontend/sql_aggregate.hpp](../../../../../include/crown/frontend/sql_aggregate.hpp), [docs/sql_aggregate_records.md § Wire contract](../../../../sql_aggregate_records.md), [docs/sql_aggregate_records.md § Ownership, failure and cost](../../../../sql_aggregate_records.md) |

## B0042

[Lines 305–306](../../../../../src/recovery/sql_aggregate_records.cpp#L305); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L305-L306:sha256:c929980d95efc152dc886ac42af0f045075441dd18a8f886364828ead327bbd3
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Closes the anonymous namespace at this source boundary; this is a lexical delimiter, not an operation. |
| inputs / outputs | No runtime input or output. Declarations following the span leave the preceding C++ scope. |
| invariants | The delimiter ends the preceding scope's visibility/linkage region; it adds no validation, publication, ownership transfer, or runtime authority. |
| ownership | The delimiter adds no owner. If it ends a function/block with live automatic objects, their normal destructors release those objects; namespace and type-definition closes change no existing object's lifetime. |
| failure | No explicit failure translation or catch is added. If a function/block exit destroys automatic objects, exception behavior follows those destructors; namespace/type closes have no runtime failure path. |
| cost | The delimiter adds no algorithmic work. A function/block exit can run existing automatic-object destructors and cleanup; namespace/type closes have no runtime cost. |
| Design | [src/recovery/sql_aggregate_records.cpp](../../../../../src/recovery/sql_aggregate_records.cpp), [docs/code_specs/files/src/recovery/sql_aggregate_records.cpp.md](sql_aggregate_records.cpp.md), [docs/sql_aggregate_records.md](../../../../sql_aggregate_records.md), [docs/sql_aggregate_session.md](../../../../sql_aggregate_session.md) |

## B0043

[Lines 307–322](../../../../../src/recovery/sql_aggregate_records.cpp#L307); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Frame encode(const resource::MemoryAccount& account,const Program& program,std::uint64_t ordinal,
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Encode and account one complete R2 record using count/write passes and final length/body/prefix hashes. |
| inputs / outputs | Declaration: \`Frame encode(const resource::MemoryAccount& account,const Program& program,std::uint64_t ordinal, const PayloadView& payload,Limits limits)\`. Inputs/outputs: Encode and account one complete R2 record using count/write passes and final length/body/prefix hashes. |
| invariants | Count and write passes share work admission; final header embeds exact body length/body digest/prefix digest, and account owns output bytes. |
| ownership | Returned Frame owns its receiving-account byte vector. |
| failure | Malformed input, budgets, account denial or vector allocation can fail; ImageFailure/resource failure/std::bad_alloc propagate. |
| cost | Count pass, write pass, body checksum and prefix checksum; work is bounded by ImageLimits, not CPU time. |
| Design | [src/recovery/sql_aggregate_records.cpp](../../../../../src/recovery/sql_aggregate_records.cpp), [include/crown/recovery/sql_aggregate_records.hpp](../../../../../include/crown/recovery/sql_aggregate_records.hpp), [include/crown/recovery/image.hpp](../../../../../include/crown/recovery/image.hpp), [src/recovery/binary_detail.hpp](../../../../../src/recovery/binary_detail.hpp), [src/frontend/sql_rows_value.hpp](../../../../../src/frontend/sql_rows_value.hpp), [include/crown/frontend/sql_aggregate.hpp](../../../../../include/crown/frontend/sql_aggregate.hpp), [docs/sql_aggregate_records.md § Wire contract](../../../../sql_aggregate_records.md), [docs/sql_aggregate_records.md § Ownership, failure and cost](../../../../sql_aggregate_records.md) |

## B0044

[Lines 323–325](../../../../../src/recovery/sql_aggregate_records.cpp#L323); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Inspected inspect(const Program& program,std::string_view bytes,Limits limits) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Inspect one complete frame without materializing owned storage or validating WAL sequence history. |
| inputs / outputs | Declaration: \`Inspected inspect(const Program& program,std::string_view bytes,Limits limits)\`. Inputs/outputs: Inspect one complete frame without materializing owned storage or validating WAL sequence history. |
| invariants | Inspection borrows input bytes and returns fixed metadata; sequence ordering belongs to WalCursor, and there is no retained decode. |
| ownership | Returns fixed metadata by value; input string_view is borrowed only for the call. |
| failure | ImageFailure reports malformed/limit/work; function adds no catch and does not materialize C++ output vectors. |
| cost | One full frame inspection/hash/parse under byte/work/row admissions. |
| Design | [src/recovery/sql_aggregate_records.cpp](../../../../../src/recovery/sql_aggregate_records.cpp), [include/crown/recovery/sql_aggregate_records.hpp](../../../../../include/crown/recovery/sql_aggregate_records.hpp), [include/crown/recovery/image.hpp](../../../../../include/crown/recovery/image.hpp), [src/recovery/binary_detail.hpp](../../../../../src/recovery/binary_detail.hpp), [src/frontend/sql_rows_value.hpp](../../../../../src/frontend/sql_rows_value.hpp), [include/crown/frontend/sql_aggregate.hpp](../../../../../include/crown/frontend/sql_aggregate.hpp), [docs/sql_aggregate_records.md § Wire contract](../../../../sql_aggregate_records.md), [docs/sql_aggregate_records.md § Ownership, failure and cost](../../../../sql_aggregate_records.md) |

## B0045

[Lines 326–338](../../../../../src/recovery/sql_aggregate_records.cpp#L326); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
DecodedInput decode_input(const resource::MemoryAccount& account,const Program& program,
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Validate external input bytes first, then copy the frame and materialize flat account-owned cells/replacements that borrow it. |
| inputs / outputs | Declaration: \`DecodedInput decode_input(const resource::MemoryAccount& account,const Program& program, std::string_view bytes,Limits limits)\`. Inputs/outputs: Validate external input bytes first, then copy the frame and materialize flat account-owned cells/replacements that borrow it. |
| invariants | Full inspect succeeds before owned copy/materialization; TEXT/source string_views point into the owned frame; all three vectors use the supplied account. |
| ownership | DecodedInput owns frame/cell/replacement vectors through supplied account; string_views/span inside cells borrow the owned frame. |
| failure | Invalid frame raises ImageFailure; account denial/vector allocation may throw resource failure/std::bad_alloc, with local owners unwound. |
| cost | Inspect pass, frame copy, and decode pass; all owned storage is accounted, but no whole-session cost claim. |
| Design | [src/recovery/sql_aggregate_records.cpp](../../../../../src/recovery/sql_aggregate_records.cpp), [include/crown/recovery/sql_aggregate_records.hpp](../../../../../include/crown/recovery/sql_aggregate_records.hpp), [include/crown/recovery/image.hpp](../../../../../include/crown/recovery/image.hpp), [src/recovery/binary_detail.hpp](../../../../../src/recovery/binary_detail.hpp), [src/frontend/sql_rows_value.hpp](../../../../../src/frontend/sql_rows_value.hpp), [include/crown/frontend/sql_aggregate.hpp](../../../../../include/crown/frontend/sql_aggregate.hpp), [docs/sql_aggregate_records.md § Wire contract](../../../../sql_aggregate_records.md), [docs/sql_aggregate_records.md § Ownership, failure and cost](../../../../sql_aggregate_records.md) |

## B0046

[Lines 339–351](../../../../../src/recovery/sql_aggregate_records.cpp#L339); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
DecodedInput encode_input(const resource::MemoryAccount& account,const Program& program,
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Encode an InputView directly into its owned frame, then materialize flat views without an encode-then-copy byte buffer. |
| inputs / outputs | Declaration: \`DecodedInput encode_input(const resource::MemoryAccount& account,const Program& program, std::uint64_t ordinal,const InputView& view,Limits limits)\`. Inputs/outputs: Encode an InputView directly into its owned frame, then materialize flat views without an encode-then-copy byte buffer. |
| invariants | InputView and its source/text buffers are borrowed during the call; output frame and flat arrays own/account their storage, with text slices into frame. |
| ownership | InputView is borrowed during encode; returned Frame and decoded vectors own receiving-account storage, with string_views into that frame. |
| failure | Encoding/validation can raise ImageFailure; account denial/vector allocation may throw, with local frame/arrays unwound. |
| cost | Encode and parse passes plus flat-array materialization; no second owned command-byte copy. |
| Design | [src/recovery/sql_aggregate_records.cpp](../../../../../src/recovery/sql_aggregate_records.cpp), [include/crown/recovery/sql_aggregate_records.hpp](../../../../../include/crown/recovery/sql_aggregate_records.hpp), [include/crown/recovery/image.hpp](../../../../../include/crown/recovery/image.hpp), [src/recovery/binary_detail.hpp](../../../../../src/recovery/binary_detail.hpp), [src/frontend/sql_rows_value.hpp](../../../../../src/frontend/sql_rows_value.hpp), [include/crown/frontend/sql_aggregate.hpp](../../../../../include/crown/frontend/sql_aggregate.hpp), [docs/sql_aggregate_records.md § Wire contract](../../../../sql_aggregate_records.md), [docs/sql_aggregate_records.md § Ownership, failure and cost](../../../../sql_aggregate_records.md) |

## B0047

[Lines 352–354](../../../../../src/recovery/sql_aggregate_records.cpp#L352); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
DecodedInput::DecodedInput(Frame frame,ImageVector<Cell> cells,
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Move an already-owned frame and its account-owned decoded arrays into a DecodedInput facade. |
| inputs / outputs | Declaration: \`DecodedInput::DecodedInput(Frame frame,ImageVector&lt;Cell&gt; cells, ImageVector&lt;runtime::sql_rows::SourceReplacement&gt; replacements) noexcept :frame_(std::move(frame)),cells_(std::move…\`. Inputs/outputs: Move an already-owned frame and its account-owned decoded arrays into a DecodedInput facade. |
| invariants | Constructor is noexcept and transfers the three already-created owners into member order; it does not allocate or copy payloads. |
| ownership | Transfers constructor arguments into members; no retaining alias outside the facade is created. |
| failure | Declared noexcept move construction has no failure path. |
| cost | Moves three owner values only. |
| Design | [src/recovery/sql_aggregate_records.cpp](../../../../../src/recovery/sql_aggregate_records.cpp), [include/crown/recovery/sql_aggregate_records.hpp](../../../../../include/crown/recovery/sql_aggregate_records.hpp), [include/crown/recovery/image.hpp](../../../../../include/crown/recovery/image.hpp), [src/recovery/binary_detail.hpp](../../../../../src/recovery/binary_detail.hpp), [src/frontend/sql_rows_value.hpp](../../../../../src/frontend/sql_rows_value.hpp), [include/crown/frontend/sql_aggregate.hpp](../../../../../include/crown/frontend/sql_aggregate.hpp), [docs/sql_aggregate_records.md § Wire contract](../../../../sql_aggregate_records.md), [docs/sql_aggregate_records.md § Ownership, failure and cost](../../../../sql_aggregate_records.md) |

## B0048

[Lines 355–359](../../../../../src/recovery/sql_aggregate_records.cpp#L355); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
InputView DecodedInput::view() const & {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Return a borrowed InputView whose source/text slices and replacement span depend on the live DecodedInput frame/arrays. |
| inputs / outputs | Declaration: \`InputView DecodedInput::view() const &\`. Inputs/outputs: Return a borrowed InputView whose source/text slices and replacement span depend on the live DecodedInput frame/arrays. |
| invariants | Returned span/string_views borrow member arrays and frame bytes; they expire when the owner is destroyed/reassigned, and a prior view is not independently owning. |
| ownership | Returns a borrowed view into \`frame_\` and \`replacements_\`; owner must remain alive and unmoved while the view is used. |
| failure | Accesses validated InputInfo alternative; no error translation or explicit allocation. |
| cost | Builds two optional/reference descriptors and one span from existing member storage. |
| Design | [src/recovery/sql_aggregate_records.cpp](../../../../../src/recovery/sql_aggregate_records.cpp), [include/crown/recovery/sql_aggregate_records.hpp](../../../../../include/crown/recovery/sql_aggregate_records.hpp), [include/crown/recovery/image.hpp](../../../../../include/crown/recovery/image.hpp), [src/recovery/binary_detail.hpp](../../../../../src/recovery/binary_detail.hpp), [src/frontend/sql_rows_value.hpp](../../../../../src/frontend/sql_rows_value.hpp), [include/crown/frontend/sql_aggregate.hpp](../../../../../include/crown/frontend/sql_aggregate.hpp), [docs/sql_aggregate_records.md § Wire contract](../../../../sql_aggregate_records.md), [docs/sql_aggregate_records.md § Ownership, failure and cost](../../../../sql_aggregate_records.md) |

## B0049

[Lines 360–360](../../../../../src/recovery/sql_aggregate_records.cpp#L360); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L360-L360:sha256:92582b45ad46706cdfae3684126917692713a5a92eff88bf2e3bcc42f5a8da44
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Closes the namespace crown::recovery::sql_aggregate at this source boundary; this is a lexical delimiter, not an operation. |
| inputs / outputs | No runtime input or output. Declarations following the span leave the preceding C++ scope. |
| invariants | The delimiter ends the preceding scope's visibility/linkage region; it adds no validation, publication, ownership transfer, or runtime authority. |
| ownership | The delimiter adds no owner. If it ends a function/block with live automatic objects, their normal destructors release those objects; namespace and type-definition closes change no existing object's lifetime. |
| failure | No explicit failure translation or catch is added. If a function/block exit destroys automatic objects, exception behavior follows those destructors; namespace/type closes have no runtime failure path. |
| cost | The delimiter adds no algorithmic work. A function/block exit can run existing automatic-object destructors and cleanup; namespace/type closes have no runtime cost. |
| Design | [src/recovery/sql_aggregate_records.cpp](../../../../../src/recovery/sql_aggregate_records.cpp), [docs/code_specs/files/src/recovery/sql_aggregate_records.cpp.md](sql_aggregate_records.cpp.md), [docs/sql_aggregate_records.md](../../../../sql_aggregate_records.md), [docs/sql_aggregate_session.md](../../../../sql_aggregate_session.md) |
