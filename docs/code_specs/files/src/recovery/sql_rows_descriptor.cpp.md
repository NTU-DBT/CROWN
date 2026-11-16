# `src/recovery/sql_rows_descriptor.cpp` — block usage map

[Source](../../../../../src/recovery/sql_rows_descriptor.cpp) · [Source index](../../../README.md) · [Subsystem contracts](../../../subsystem_contracts.md) · [Reviewed primitives](../../../primitives.md)

Encode, validate and publish checkpoints, journals, generations and local delivery receipts with explicit durable authority.

Snapshot SHA-256: `1e3455fdc24de013294e34ee55df3870a30fa1271c87c4d0240b4f570d834e2f`. 212 lines partitioned into 31 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [recovery](../../../subsystem_contracts.md#recovery). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/checkpoints.md](../../../../checkpoints.md), [docs/journal.md](../../../../journal.md), [docs/journal-files.md](../../../../journal-files.md), [docs/generations.md](../../../../generations.md), [docs/local-sink.md](../../../../local-sink.md), [docs/history-retirement.md](../../../../history-retirement.md), [docs/update_patterns.md](../../../../update_patterns.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–23](../../../../../src/recovery/sql_rows_descriptor.cpp#L1) | Imports dependencies; declares namespace scope; declares aliases; declares values/defaults or compile-time conditions. | source comment (unverified): // Same pinned parser archive/PG18.6 AST contract as SQL aggregate composition · [reviewed contract](#b0001) |
| [B0002 · 24–26](../../../../../src/recovery/sql_rows_descriptor.cpp#L24) | Callable definition: std::string_view view(const std::vector&lt;std::uint8_t&gt;& bytes) | calls data, size; returns {reinterpret_cast&lt;const char*&gt;(bytes.data()),bytes.size()} · [reviewed contract](#b0002) |
| [B0003 · 27–27](../../../../../src/recovery/sql_rows_descriptor.cpp#L27) | Callable definition: Json limit(std::optional&lt;std::uint64_t&gt; value) | calls Json; returns value?Json(*value):Json{} · [reviewed contract](#b0003) |
| [B0004 · 28–28](../../../../../src/recovery/sql_rows_descriptor.cpp#L28) | Callable definition: std::uint64_t number(const Json& value) | calls io::detail::unsigned_integer; returns io::detail::unsigned_integer(value,@ ) · [reviewed contract](#b0004) |
| [B0005 · 29–29](../../../../../src/recovery/sql_rows_descriptor.cpp#L29) | Callable definition: std::optional&lt;std::uint64_t&gt; limit(const Json& value) | calls is_null, number; returns value.is_null()?std::nullopt:std::optional{number(value)} · [reviewed contract](#b0005) |
| [B0006 · 30–35](../../../../../src/recovery/sql_rows_descriptor.cpp#L30) | Callable definition: Json options_image(const Options& options) | calls Json::array, limit; returns {{@ ,Json::array({w.structural_steps,w.scalar_fields,w.scalar_bytes,w.pointer_slots,w.link_actions}… · [reviewed contract](#b0006) |
| [B0007 · 36–44](../../../../../src/recovery/sql_rows_descriptor.cpp#L36) | Callable definition: Options read_options(const Json& value) | calls io::detail::fields, io::detail::array, at, require; guard const auto& w=io::detail::array(value.at("source_work"),"source_work");require(w.size()==5);; returns result · [reviewed contract](#b0007) |
| [B0008 · 45–57](../../../../../src/recovery/sql_rows_descriptor.cpp#L45) | Callable definition: Json recipe(const runtime::sql_rows::SourceSnapshot& source,const Options& options,runtime::sql_rows::OutputLimits output) | calls export_core, options_image, io::write_tree, planner::compiler_source_detail::tree; returns {{@ ,1},{@ ,parser_archive},{@ ,pg_version},{@ ,@ },{@ ,@ }, · [reviewed contract](#b0008) |
| [B0009 · 58–63](../../../../../src/recovery/sql_rows_descriptor.cpp#L58) | Callable definition: void finite(const AdmissionLimits& limits) | calls require; guard require(limits.lowering.work_limit && limits.lowering.identity.work_limit && b.work_limit && · [reviewed contract](#b0009) |
| [B0010 · 64–68](../../../../../src/recovery/sql_rows_descriptor.cpp#L64) | Callable definition: void schema_limits(const frontend::SqlRowsProgram& program,const DescriptorLimits& limits) | calls sources, require, size, outputs; guard const auto sources=program.sources();require(sources.size()&lt;=limits.image.tables,ImageFault::limit);; 1 loop sites · [reviewed contract](#b0010) |
| [B0011 · 69–71](../../../../../src/recovery/sql_rows_descriptor.cpp#L69) | Explanatory comments or spacing. | source comment (unverified): // Finite producer caps already within the host caps bound actual construction. · [reviewed contract](#b0011) |
| [B0012 · 72–79](../../../../../src/recovery/sql_rows_descriptor.cpp#L72) | Callable definition: void lower_check(const frontend::SqlRowsProgram& program,const FreeConnexTree& tree, const PhysicalOptions& physical,const Admiss… | calls finite, export_core, planner::lower_tree; source comment (unverified): // Finite producer caps already within the host caps bound actual construction. · [reviewed contract](#b0012) |
| [B0013 · 80–80](../../../../../src/recovery/sql_rows_descriptor.cpp#L80) | Explanatory comments or spacing. | source comment (unverified): // Count/validate before the receiving allocation; all codec passes share work. · [reviewed contract](#b0013) |
| [B0014 · 81–98](../../../../../src/recovery/sql_rows_descriptor.cpp#L81) | Callable definition: ImageVector&lt;char&gt; encode_bytes(const resource::MemoryAccount& account,std::string_view binding,std::string_view recipe_bytes, con… | calls require, cbor, inspect, put; guard require(limits.cbor_depth&lt;=256,ImageFault::limit);detail::Cbor cbor(budget,limits);; returns bytes; growth reserve; 1 loop sites; source comment (unverified): // Count/validate before the receiving allocation; all codec passes share work. · [reviewed contract](#b0014) |
| [B0015 · 99–100](../../../../../src/recovery/sql_rows_descriptor.cpp#L99) | Closes surrounding scope/type. | source comment (unverified): // namespace · [reviewed contract](#b0015) |
| [B0016 · 101–112](../../../../../src/recovery/sql_rows_descriptor.cpp#L101) | Type/record definition: struct Descriptor::Data |  · [reviewed contract](#b0016) |
| [B0017 · 113–113](../../../../../src/recovery/sql_rows_descriptor.cpp#L113) | declares namespace scope. |  · [reviewed contract](#b0017) |
| [B0018 · 114–130](../../../../../src/recovery/sql_rows_descriptor.cpp#L114) | Type/record definition: class DescriptorFactory | guard require(bool(program),ImageFault::binding);; returns {Descriptor(std::move(data)),std::move(live),{size,budget.used,0}}; growth make_accounted_shared; source comment (unverified): // Whole-frame descriptor identity retained by Data. · [reviewed contract](#b0018) |
| [B0019 · 131–132](../../../../../src/recovery/sql_rows_descriptor.cpp#L131) | Closes surrounding scope/type. | source comment (unverified): // namespace detail · [reviewed contract](#b0019) |
| [B0020 · 133–144](../../../../../src/recovery/sql_rows_descriptor.cpp#L133) | Callable definition: InspectedDescriptor inspect_descriptor(std::string_view bytes,DescriptorLimits limits) | calls require, size, take, integer; guard require(limits.cbor_depth&lt;=256,ImageFault::limit);require(bytes.size()&lt;=limits.image.bytes,ImageFau…; returns {binding,recipe_bytes,sha256_fixed(bytes),{bytes.size(),budget.used,0}} · [reviewed contract](#b0020) |
| [B0021 · 145–148](../../../../../src/recovery/sql_rows_descriptor.cpp#L145) | Callable definition: Admitted admit_into(const resource::MemoryAccount& account,frontend::SqlRowsProgram program, const FreeConnexTree& tree,const Phy… | calls detail::DescriptorFactory::admit, std::move; returns detail::DescriptorFactory::admit(account,std::move(program),tree,physical,options,output,limits,bud… · [reviewed contract](#b0021) |
| [B0022 · 149–201](../../../../../src/recovery/sql_rows_descriptor.cpp#L149) | Callable definition: Admitted rebind_into(const resource::MemoryAccount& account,std::string_view bytes,const AdmissionLimits& limits) | calls finite, crown::recovery::sql_rows::inspect_descriptor, Json::from_cbor, begin; guard require(catalog.tables.size()&lt;=limits.descriptor.image.tables,ImageFault::limit);; returns admitted; growth emplace_back, push_back, reserve; 2 loop sites; source comment (unverified): // Genuine physical parameter declarations never use int32/unknown. · [reviewed contract](#b0022) |
| [B0023 · 202–204](../../../../../src/recovery/sql_rows_descriptor.cpp#L202) | Callable definition: const Descriptor::Data& Descriptor::data() const | calls require, bool; guard require(bool(data_),ImageFault::binding);return *data_;; returns *data_ · [reviewed contract](#b0023) |
| [B0024 · 205–205](../../../../../src/recovery/sql_rows_descriptor.cpp#L205) | Callable definition: const frontend::SqlRowsProgram& Descriptor::program() const & | calls data; returns data().program · [reviewed contract](#b0024) |
| [B0025 · 206–206](../../../../../src/recovery/sql_rows_descriptor.cpp#L206) | Callable definition: const CompiledProgram& Descriptor::native_program() const & | calls data; returns data().native · [reviewed contract](#b0025) |
| [B0026 · 207–207](../../../../../src/recovery/sql_rows_descriptor.cpp#L207) | Callable definition: const runtime::weighted::Binding& Descriptor::native_binding() const & | calls data; returns data().binding · [reviewed contract](#b0026) |
| [B0027 · 208–208](../../../../../src/recovery/sql_rows_descriptor.cpp#L208) | Callable definition: const Options& Descriptor::options() const & | calls data; returns data().normal · [reviewed contract](#b0027) |
| [B0028 · 209–209](../../../../../src/recovery/sql_rows_descriptor.cpp#L209) | Callable definition: const runtime::sql_rows::OutputLimits& Descriptor::output_limits() const & | calls data; returns data().output · [reviewed contract](#b0028) |
| [B0029 · 210–210](../../../../../src/recovery/sql_rows_descriptor.cpp#L210) | Callable definition: const Hash& Descriptor::sha256() const & | calls data; returns data().digest · [reviewed contract](#b0029) |
| [B0030 · 211–211](../../../../../src/recovery/sql_rows_descriptor.cpp#L211) | Callable definition: std::string_view Descriptor::bytes() const & | calls data, size; returns {b.data(),b.size()} · [reviewed contract](#b0030) |
| [B0031 · 212–212](../../../../../src/recovery/sql_rows_descriptor.cpp#L212) | Closes surrounding scope/type. | source comment (unverified): // namespace crown::recovery::sql_rows · [reviewed contract](#b0031) |

## B0001

[Lines 1–23](../../../../../src/recovery/sql_rows_descriptor.cpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L1-L23:sha256:6b6b7e5c386061f0bed5c4b23c8248070c78ee9b24da67fcd4d392c536d4d8ab
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Declare cold descriptor dependencies, aliases, magic and existing parser pins. |
| inputs / outputs | Include own descriptor, digest/catalog/physical/tree/lowering/account/shared-CBOR/JSON/source helpers; define Json/Options, CROWNRD2, archive hash and PG180006 constants. |
| invariants | Pins duplicate the existing project lock/aggregate compiler and do not change SQL-row source_sha256. A future parser change requires explicit descriptor compatibility/admission. |
| ownership | No new runtime backing storage from declarations; actual declared views/handles obey their named type lifetimes. |
| failure | Compile-time checking only in this span; invoked member/helper operations have separately specified failures. |
| cost | Include/type/signature/constant declarations only; no executed codec/binder/hash/sort/native work or backing allocation. |
| Design | [src/recovery/sql_rows_descriptor.cpp](../../../../../src/recovery/sql_rows_descriptor.cpp) |

## B0002

[Lines 24–26](../../../../../src/recovery/sql_rows_descriptor.cpp#L24); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L24-L26:sha256:f11e3856b41f0dd1b35651da8bbeeda0cec30aec2d97d6066e22e35d624d87ee
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Borrow the exact bytes of a cold CBOR vector. |
| inputs / outputs | Const byte vector → string_view over exactly its data/size. |
| invariants | No validation or transformation. |
| ownership | Returned view borrows the vector backing. |
| failure | No intentional failure for a live vector. |
| cost | Fixed pointer/length access; no allocation/hash/native work. |
| Design | [src/recovery/sql_rows_descriptor.cpp](../../../../../src/recovery/sql_rows_descriptor.cpp) |

## B0003

[Lines 27–27](../../../../../src/recovery/sql_rows_descriptor.cpp#L27); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L27-L27:sha256:e91f4f0f517bca54cbf017f2bb95bfc72c8e1a0bcbeee274657d041ac86b63a9
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Preserve an optional uint64 grant as JSON integer or NULL without refilling it. |
| inputs / outputs | Optional uint64 → Json integer or JSON null. |
| invariants | No limit is consumed/refilled and no policy is admitted. |
| ownership | Returned Json owns a scalar/null. |
| failure | No intentional validation failure; Json construction follows its ordinary semantics. |
| cost | Fixed scalar construction; no native/account allocation or traversal. |
| Design | [src/recovery/sql_rows_descriptor.cpp](../../../../../src/recovery/sql_rows_descriptor.cpp) |

## B0004

[Lines 28–28](../../../../../src/recovery/sql_rows_descriptor.cpp#L28); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L28-L28:sha256:f1a643546bb277f1797068f8e400abcfb32693a6cf4485e1ccd84b65b78a9442
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Read one exact unsigned descriptor integer through the existing cold JSON boundary. |
| inputs / outputs | Const Json scalar → uint64_t via io::detail::unsigned_integer. |
| invariants | Checks integer kind and rejects a negative signed value; creates no runtime/descriptor. |
| ownership | Borrows Json and returns a scalar; retains no data. |
| failure | Existing cold invalid_document Error on invalid number; error formatting/allocation can propagate. |
| cost | Scalar JSON checks/access and a short diagnostic helper argument; no account allocation, binder, lowerer or image traversal. |
| Design | [src/recovery/sql_rows_descriptor.cpp](../../../../../src/recovery/sql_rows_descriptor.cpp), [src/io/json.hpp](../../../../../src/io/json.hpp) |

## B0005

[Lines 29–29](../../../../../src/recovery/sql_rows_descriptor.cpp#L29); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L29-L29:sha256:bfb11e583a48f02ca638397b801036d7f514d700097834cd6f9cdd325b9888b0
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Decode JSON null as a disabled limit or one checked unsigned scalar as an engaged limit. |
| inputs / outputs | Const Json → empty optional for null, otherwise number(Json). |
| invariants | Null means disabled counter; other values get only number’s unsigned check. |
| ownership | Scalar optional owns its value; Json borrowed. |
| failure | number propagates cold invalid_document errors for invalid scalars. |
| cost | Fixed null test/scalar conversion; no binder/runtime/account allocation. |
| Design | [src/recovery/sql_rows_descriptor.cpp](../../../../../src/recovery/sql_rows_descriptor.cpp) |

## B0006

[Lines 30–35](../../../../../src/recovery/sql_rows_descriptor.cpp#L30); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L30-L35:sha256:3777a14d314da014d92118008de67c71263c907d4f762ff073fd39b5a190ea60
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Serialize original source/native operational limits and capture choices, independently of the receiving account cap. |
| inputs / outputs | SqlRows Options → ordinary Json object for five source-work fields and original native work/multiplicity/memory/capture fields. |
| invariants | Serializes policy values; does not validate them or create a grant/runtime. |
| ownership | Returned DOM owns ordinary nodes; options borrowed. |
| failure | Ordinary JSON allocation failures propagate. |
| cost | Fixed number of object/array fields and scalar writes; ordinary DOM allocations, no SQL binding/lowering. |
| Design | [src/recovery/sql_rows_descriptor.cpp](../../../../../src/recovery/sql_rows_descriptor.cpp) |

## B0007

[Lines 36–44](../../../../../src/recovery/sql_rows_descriptor.cpp#L36); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L36-L44:sha256:a464380f960bb10c07af35772e0b9ed880458af71bd6b8c7300889b6113f485d
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Read the exact original source/native policy fields and leave genuine runtime admission to the real factory. |
| inputs / outputs | Const Json policy object → SqlRows Options with native/source fields populated. |
| invariants | Requires exact object fields, source_work length5 and unsigned/scalar conversions. Runtime-domain validity is checked later by real creation. |
| ownership | Returns values only; DOM borrowed. |
| failure | ImageFailure for explicit array-width check; io invalid_document/JSON type errors propagate. |
| cost | Fixed field lookups/conversions and array5 read; no native/account allocation or binder. |
| Design | [src/recovery/sql_rows_descriptor.cpp](../../../../../src/recovery/sql_rows_descriptor.cpp), [src/io/json.hpp](../../../../../src/io/json.hpp) |

## B0008

[Lines 45–57](../../../../../src/recovery/sql_rows_descriptor.cpp#L45); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L45-L57:sha256:ee17560a13fc33b87447bd86a9bc75668dc848ca9823fd88ea6bf5df99fb1857
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Serialize the actual native recipe, normal/output policies and existing parser/format provenance pins. |
| inputs / outputs | SourceSnapshot metadata, original Options and OutputLimits → ordinary Json recipe with native tree/options/hashes and parser/format/output pins. |
| invariants | Caller supplies genuine snapshot metadata. This block serializes it; it does not verify a tree, admit a runtime or establish minimum height. |
| ownership | Exports cold core/tree/options DTOs and owns the resulting ordinary DOM/string copies; borrows input handles. |
| failure | Export/serialization/allocation errors propagate. |
| cost | Traverse exported program/core/tree/options and copy identity strings into DOM; cold allocations occur. No new runtime or physical row scan. |
| Design | [src/recovery/sql_rows_descriptor.cpp](../../../../../src/recovery/sql_rows_descriptor.cpp) |

## B0009

[Lines 58–63](../../../../../src/recovery/sql_rows_descriptor.cpp#L58); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L58-L63:sha256:2af75379aa26d00d9a4119dcc4f03baa18eb93e87204eb0df685417ea65d19ed
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Require finite receiving binder/lowerer work and bounded recursion before cold construction. |
| inputs / outputs | AdmissionLimits → void after checking engaged binder/lowering/identity work limits and recursion≤256. |
| invariants | Engaged zero is still finite. Does not spend any grant or validate/compile SQL. |
| ownership | Borrows limits only. |
| failure | ImageFailure(limit) when the explicit conditions fail. |
| cost | Fixed option/number checks; no allocation. |
| Design | [src/recovery/sql_rows_descriptor.cpp](../../../../../src/recovery/sql_rows_descriptor.cpp) |

## B0010

[Lines 64–68](../../../../../src/recovery/sql_rows_descriptor.cpp#L64); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L64-L68:sha256:568d5106a1701a861fb87121349b6ffe34adb487f7147cb6c412adbdcde786b0
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Check counts in an already genuine program against descriptor table/field caps. |
| inputs / outputs | Genuine program+DescriptorLimits → void after source count, per-source columns and output width checks. |
| invariants | Reads genuine program sources/outputs and checks source count, each column count and output width. This helper runs after that program exists; it does not preflight all prior DOM/catalog/binder allocation. |
| ownership | Borrows program spans/limits only. |
| failure | ImageFailure(limit) on the stated counts. |
| cost | O(number of sources) count reads; no column-content/row traversal, binder or allocation. |
| Design | [src/recovery/sql_rows_descriptor.cpp](../../../../../src/recovery/sql_rows_descriptor.cpp) |

## B0011

[Lines 69–71](../../../../../src/recovery/sql_rows_descriptor.cpp#L69); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L69-L71:sha256:4d82b4a533c0726ef2f651489a0ba0b3601dee4a8cb17566ce4988ecae2e36bf
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Document the adjacent block boundary. |
| inputs / outputs | Comment/spacing only. |
| invariants | Text is not an executed check or proof. |
| ownership | No ownership operation. |
| failure | No executable failure path. |
| cost | No runtime work/allocation. |
| Design | [src/recovery/sql_rows_descriptor.cpp](../../../../../src/recovery/sql_rows_descriptor.cpp) |

## B0012

[Lines 72–79](../../../../../src/recovery/sql_rows_descriptor.cpp#L72); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L72-L79:sha256:e98fb88d8dd5b2847da7ffaae254cca10688c764f4989571ee4733a7f2c94872
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Use already-bounded original lowering or one finite host validation pass while preserving the original physical policy. |
| inputs / outputs | Genuine program/tree/PhysicalOptions/AdmissionLimits → void. |
| invariants | Calls finite; returns when original compile caps are within host caps. Otherwise exports core and performs/discards one host-bounded lower_tree result. Does not rewrite original options or claim a minimum. |
| ownership | Borrows inputs; temporary core/lowered plan own cold metadata and die locally. |
| failure | Limit check/lowering/identity/native allocation errors propagate. |
| cost | Fixed comparisons on fast path; otherwise actual core export and one lowering/identity pass with its allocations. No runtime construction. |
| Design | [src/recovery/sql_rows_descriptor.cpp](../../../../../src/recovery/sql_rows_descriptor.cpp) |

## B0013

[Lines 80–80](../../../../../src/recovery/sql_rows_descriptor.cpp#L80); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L80-L80:sha256:9a76a06f72a17e72e723a8f1dd671add6e42c491ee2a4982985ec9b2cf82d0a8
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Document the adjacent block boundary. |
| inputs / outputs | Comment/spacing only. |
| invariants | Text is not an executed check or proof. |
| ownership | No ownership operation. |
| failure | No executable failure path. |
| cost | No runtime work/allocation. |
| Design | [src/recovery/sql_rows_descriptor.cpp](../../../../../src/recovery/sql_rows_descriptor.cpp) |

## B0014

[Lines 81–98](../../../../../src/recovery/sql_rows_descriptor.cpp#L81); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L81-L98:sha256:44ea68248921f21eef1e2bf0c313f6c6e7f337b7d94eda3281072673e4e24f23
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Preflight both definite CBOR objects, measure/fund one distinct CROWNRD2 envelope and protect its length/body. |
| inputs / outputs | Account, borrowed binding+recipe bytes, limits and shared Budget → one accounted protected CROWNRD2 byte vector. |
| invariants | Shared CBOR inspection precedes measure/allocation; length/body/prefix hashes are written. Does not bind SQL or compare a regenerated recipe. |
| ownership | Owns final byte vector; shared validator borrows budget/limits, input views remain borrowed. |
| failure | Fixed ImageFailure rejects the stated wire/domain/work checks; this block adds no catch or recovery action. Receiving vector allocation failures propagate. |
| cost | CBOR visits, two frame writes, body/prefix hashes and one reserved frame allocation; no binder/lowerer/native state. |
| Design | [src/recovery/sql_rows_descriptor.cpp](../../../../../src/recovery/sql_rows_descriptor.cpp), [src/recovery/sql_aggregate_cbor.hpp](../../../../../src/recovery/sql_aggregate_cbor.hpp) |

## B0015

[Lines 99–100](../../../../../src/recovery/sql_rows_descriptor.cpp#L99); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L99-L100:sha256:c929980d95efc152dc886ac42af0f045075441dd18a8f886364828ead327bbd3
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Close the stated namespace/type scope. |
| inputs / outputs | No runtime input or output. |
| invariants | No new checks or state transitions. |
| ownership | No ownership operation. |
| failure | No executable failure path. |
| cost | No runtime work/allocation. |
| Design | [src/recovery/sql_rows_descriptor.cpp](../../../../../src/recovery/sql_rows_descriptor.cpp) |

## B0016

[Lines 101–112](../../../../../src/recovery/sql_rows_descriptor.cpp#L101); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L101-L112:sha256:e0321a8a4b8e67147e2ddeae452ff982612b2dc41c0033d5e693431b18d638a8
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Retain genuine program/native binding, original normal/output policy and immutable exact protected bytes. |
| inputs / outputs | SourceSnapshot metadata, original normal/output policy and funded encoded bytes → stored Data fields plus whole-byte digest. |
| invariants | Computes digest of moved bytes but does not validate frame/binding or create the runtime; factory establishes those premises. |
| ownership | Moves genuine program/native handles/byte vector, copies fixed policies/binding; retains their existing accounts. |
| failure | No custom validation; hash/member operations follow their own rules. |
| cost | O(encoded frame bytes) hash plus fixed moves/copies; no SQL bind/lower or physical row scan. |
| Design | [src/recovery/sql_rows_descriptor.cpp](../../../../../src/recovery/sql_rows_descriptor.cpp) |

## B0017

[Lines 113–113](../../../../../src/recovery/sql_rows_descriptor.cpp#L113); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L113-L113:sha256:5535809b42b9d97cdfea935b5d84662804aaab9873ce9d79d846ab3ec8a625cb
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Open the row descriptor detail namespace. |
| inputs / outputs | Namespace scope only. |
| invariants | No checks or state transition. |
| ownership | No new runtime backing storage from declarations; actual declared views/handles obey their named type lifetimes. |
| failure | Compile-time checking only in this span; invoked member/helper operations have separately specified failures. |
| cost | Include/type/signature/constant declarations only; no executed codec/binder/hash/sort/native work or backing allocation. |
| Design | [src/recovery/sql_rows_descriptor.cpp](../../../../../src/recovery/sql_rows_descriptor.cpp) |

## B0018

[Lines 114–130](../../../../../src/recovery/sql_rows_descriptor.cpp#L114); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L114-L130:sha256:14624ffde8d7341f1d47ed86b482957ae0f5570bc5e45151983d4ef99316f482
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Construct a C0 SqlRowsRuntime and receiving-owned descriptor through genuine factories. |
| inputs / outputs | Account/genuine program/tree/physical/normal/output policy/host limits/Budget → Admitted descriptor, C0 runtime and stats. |
| invariants | Requires genuine program and nonempty retained binding before extent/schema/lowering checks or runtime allocation. Constructs real C0 SqlRowsRuntime, captures source metadata and encodes actual binding/recipe. Rebind whole-byte equality is a separate later step; no minimum proof or file authority. |
| ownership | Receiver owns native state/immutable Descriptor::Data/frame; temporary source/DOM die locally. |
| failure | Image/native/helper/allocation failures propagate and local owners unwind; no SQL binder invocation or durable mutation occurs in this block. |
| cost | Actual cold lower/runtime construction, source metadata capture, DOM/CBOR/frame passes/hash and receiving allocations. |
| Design | [src/recovery/sql_rows_descriptor.cpp](../../../../../src/recovery/sql_rows_descriptor.cpp) |

## B0019

[Lines 131–132](../../../../../src/recovery/sql_rows_descriptor.cpp#L131); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L131-L132:sha256:b23afc92a44293edd31841f0512be65ae6b91c5f500f762bb06b88c959e15d1f
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Close the stated namespace/type scope. |
| inputs / outputs | No runtime input or output. |
| invariants | No new checks or state transitions. |
| ownership | No ownership operation. |
| failure | No executable failure path. |
| cost | No runtime work/allocation. |
| Design | [src/recovery/sql_rows_descriptor.cpp](../../../../../src/recovery/sql_rows_descriptor.cpp) |

## B0020

[Lines 133–144](../../../../../src/recovery/sql_rows_descriptor.cpp#L133); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L133-L144:sha256:1efa8e67c84a45e0f3870729f8ebbc554e20ed7d7f70d039a2e6e7e620b0310c
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Inspect exact frame hashes and bounded canonical CBOR without allocating a DOM or constructing a runtime. |
| inputs / outputs | Borrowed frame+DescriptorLimits → borrowed binding/recipe slices, whole-frame hash and ImageStatistics. |
| invariants | Checks exact CROWNRD2 version/length/hashes/EOF and bounded CBOR subset. Does not establish that SQL/recipe is genuine. |
| ownership | No owned output or DOM; slices borrow unchanged input. |
| failure | Fixed ImageFailure rejects the stated wire/domain/work checks; this block adds no catch or recovery action. |
| cost | Linear admitted frame/CBOR/hash/key-compare visits with bounded depth; no allocation/native factory. |
| Design | [src/recovery/sql_rows_descriptor.cpp](../../../../../src/recovery/sql_rows_descriptor.cpp), [src/recovery/sql_aggregate_cbor.hpp](../../../../../src/recovery/sql_aggregate_cbor.hpp) |

## B0021

[Lines 145–148](../../../../../src/recovery/sql_rows_descriptor.cpp#L145); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L145-L148:sha256:7ee25e66274d2520f64558e2bc530e40b18d5ad33b8b26c87469c24c4bbbca18
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Construct a genuine empty/static SqlRowsRuntime and factory-owned descriptor with original normal/output policies. |
| inputs / outputs | Account, genuine program/tree/physical/normal/output policy and limits → DescriptorFactory::admit result. |
| invariants | Creates one codec Budget and delegates; this wrapper adds no independent checks. |
| ownership | Arguments/returned owning members follow the called factory; no extra buffer or owner here. |
| failure | Factory failures propagate unchanged. |
| cost | Fixed wrapper/budget construction plus actual delegated factory work. |
| Design | [src/recovery/sql_rows_descriptor.cpp](../../../../../src/recovery/sql_rows_descriptor.cpp) |

## B0022

[Lines 149–201](../../../../../src/recovery/sql_rows_descriptor.cpp#L149); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L149-L201:sha256:3d488958cb98d813f2384e29c4779bb38c9bf95ac68c2e4ab44ffa2f0bb8abb2
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Rebind genuine original SQL/catalog/typed parameters, preserve compiler resource_limit as ImageFault::work, then require exact parser/native/policy frame bytes. |
| inputs / outputs | Account, protected descriptor bytes and receiving limits → genuine re-created C0 runtime+Descriptor+codec statistics. |
| invariants | Bounded complete frame/CBOR inspection precedes Json DOM creation. read_catalog_payload creates ordinary Catalog DTO before table/column caps. Local copy of receiving bind options forces retain_binding_image=true; actual binder/lowering/factory regeneration plus whole-frame equality establish returned descriptor identity. No caller normal/output limit rewrite, minimum proof or receipt authority. |
| ownership | Caller keeps bytes unchanged and alive through the call. Temporary ordinary DOM/catalog/parameter owners die locally; returned Descriptor/runtime own receiver state and retain no borrow of caller frame. |
| failure | Compiler resource_limit diagnostic→ImageFailure(work); other compiler diagnostics→binding. Explicit byte/native mismatch, cold JSON/native/allocation errors propagate; no semantic Reject/file mutation. |
| cost | Full inspect/DOM/genuine rebind including explicitly retained canonical binding bytes/native construction/re-encoding/equality with actual ordinary and account-funded allocations. Cold compiler limits stay separate from stored normal/output policy. |
| Design | [src/recovery/sql_rows_descriptor.cpp](../../../../../src/recovery/sql_rows_descriptor.cpp) |

## B0023

[Lines 202–204](../../../../../src/recovery/sql_rows_descriptor.cpp#L202); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L202-L204:sha256:598e3ad4220b8896caf222c5ed1fee63fc84ba8e3ebe8a7a7462e63824722ebc
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Reject an empty descriptor handle before exposing immutable retained state. |
| inputs / outputs | This Descriptor handle → const Data&. |
| invariants | Only checks handle presence. |
| ownership | Returns borrow of shared immutable Data. |
| failure | ImageFailure(binding) for empty handle. |
| cost | Fixed pointer check/dereference; no allocation. |
| Design | [src/recovery/sql_rows_descriptor.cpp](../../../../../src/recovery/sql_rows_descriptor.cpp) |

## B0024

[Lines 205–205](../../../../../src/recovery/sql_rows_descriptor.cpp#L205); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L205-L205:sha256:39b68f3d1e571f842d047bba94cd229e98d2b1ab738fea885aabd572e10a38ec
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Borrow the genuine retained SQL-row compiler handle. |
| inputs / outputs | This Descriptor -&gt; const frontend::SqlRowsProgram& referencing Data::program. |
| invariants | Calls data() to require a nonempty handle; returns stored values unchanged. No validation/hash/factory is rerun. |
| ownership | The reference borrows Data::program from retained shared immutable Data; keep that backing owner alive. The getter creates no copy or byte-vector view. |
| failure | Empty handle uses data() ImageFailure(binding). |
| cost | Fixed access/handle or pointer-length reads; no allocation or SQL/native work. |
| Design | [src/recovery/sql_rows_descriptor.cpp](../../../../../src/recovery/sql_rows_descriptor.cpp) |

## B0025

[Lines 206–206](../../../../../src/recovery/sql_rows_descriptor.cpp#L206); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L206-L206:sha256:59821980a312d03d0d6c8e49f12db84c1ce7c94e8a31110d9ffe33757b21d8df
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Borrow the actual lowered native executable metadata. |
| inputs / outputs | This Descriptor -&gt; const CompiledProgram& referencing Data::native. |
| invariants | Calls data() to require a nonempty handle; returns stored values unchanged. No validation/hash/factory is rerun. |
| ownership | The reference borrows Data::native from retained shared immutable Data; keep that backing owner alive. The getter creates no copy or byte-vector view. |
| failure | Empty handle uses data() ImageFailure(binding). |
| cost | Fixed access/handle or pointer-length reads; no allocation or SQL/native work. |
| Design | [src/recovery/sql_rows_descriptor.cpp](../../../../../src/recovery/sql_rows_descriptor.cpp) |

## B0026

[Lines 207–207](../../../../../src/recovery/sql_rows_descriptor.cpp#L207); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L207-L207:sha256:365b9e022b9d881f727839fe115ab4e08ae17eade06e2d8935f3def7f7fb7498
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Borrow the actual native weighted binding and multiplicity domain. |
| inputs / outputs | This Descriptor -&gt; const runtime::weighted::Binding& referencing Data::binding. |
| invariants | Calls data() to require a nonempty handle; returns stored values unchanged. No validation/hash/factory is rerun. |
| ownership | The reference borrows Data::binding from retained shared immutable Data; keep that backing owner alive. The getter creates no copy or byte-vector view. |
| failure | Empty handle uses data() ImageFailure(binding). |
| cost | Fixed access/handle or pointer-length reads; no allocation or SQL/native work. |
| Design | [src/recovery/sql_rows_descriptor.cpp](../../../../../src/recovery/sql_rows_descriptor.cpp) |

## B0027

[Lines 208–208](../../../../../src/recovery/sql_rows_descriptor.cpp#L208); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L208-L208:sha256:6b0995419230462d1d30b72586a58c60d535d2715a8ffe41028f540598a0719c
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Borrow original operational policy; stored memory values do not mint a receiving grant. |
| inputs / outputs | This Descriptor -&gt; const runtime::sql_rows::Options& referencing Data::normal. |
| invariants | Calls data() to require a nonempty handle; returns stored values unchanged. No validation/hash/factory is rerun. |
| ownership | The reference borrows Data::normal from retained shared immutable Data; keep that backing owner alive. The getter creates no copy or byte-vector view. |
| failure | Empty handle uses data() ImageFailure(binding). |
| cost | Fixed access/handle or pointer-length reads; no allocation or SQL/native work. |
| Design | [src/recovery/sql_rows_descriptor.cpp](../../../../../src/recovery/sql_rows_descriptor.cpp) |

## B0028

[Lines 209–209](../../../../../src/recovery/sql_rows_descriptor.cpp#L209); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L209-L209:sha256:f862ba852c416c5f134487b75bd16496a8862d32ccefec032036880391ec120f
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Borrow the fixed original per-command presentation row/work limits. |
| inputs / outputs | This Descriptor -&gt; const runtime::sql_rows::OutputLimits& referencing Data::output. |
| invariants | Calls data() to require a nonempty handle; returns stored values unchanged. No validation/hash/factory is rerun. |
| ownership | The reference borrows Data::output from retained shared immutable Data; keep that backing owner alive. The getter creates no copy or byte-vector view. |
| failure | Empty handle uses data() ImageFailure(binding). |
| cost | Fixed access/handle or pointer-length reads; no allocation or SQL/native work. |
| Design | [src/recovery/sql_rows_descriptor.cpp](../../../../../src/recovery/sql_rows_descriptor.cpp) |

## B0029

[Lines 210–210](../../../../../src/recovery/sql_rows_descriptor.cpp#L210); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L210-L210:sha256:957015257e421ce7c4fdfa59acc53d3e25e387e37d2eba8076351e375e70e78b
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Borrow the complete protected descriptor frame identity. |
| inputs / outputs | This Descriptor -&gt; const Hash& referencing Data::digest. |
| invariants | Calls data() to require a nonempty handle; returns stored values unchanged. No validation/hash/factory is rerun. |
| ownership | The reference borrows Data::digest from retained shared immutable Data; keep that backing owner alive. The getter creates no copy or byte-vector view. |
| failure | Empty handle uses data() ImageFailure(binding). |
| cost | Fixed access/handle or pointer-length reads; no allocation or SQL/native work. |
| Design | [src/recovery/sql_rows_descriptor.cpp](../../../../../src/recovery/sql_rows_descriptor.cpp) |

## B0030

[Lines 211–211](../../../../../src/recovery/sql_rows_descriptor.cpp#L211); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L211-L211:sha256:e09333fc2d09e3c4653b65b9542e97807fe2fa1c7cb8e7b22cc27ef539aa5e8c
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Borrow exact immutable descriptor bytes while their owner survives. |
| inputs / outputs | This Descriptor -&gt; string_view over the exact data/size of Data::bytes. |
| invariants | Calls data() to require a nonempty handle; returns stored values unchanged. No validation/hash/factory is rerun. |
| ownership | Returned byte view borrows the retained vector in shared immutable Data; keep that backing unchanged and alive. |
| failure | Empty handle uses data() ImageFailure(binding). |
| cost | Fixed access/handle or pointer-length reads; no allocation or SQL/native work. |
| Design | [src/recovery/sql_rows_descriptor.cpp](../../../../../src/recovery/sql_rows_descriptor.cpp) |

## B0031

[Lines 212–212](../../../../../src/recovery/sql_rows_descriptor.cpp#L212); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L212-L212:sha256:5a88989d646de8c904ac4cbcd84db92dc85500003eb77614a29dedc10d8206dd
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Close the stated namespace/type scope. |
| inputs / outputs | No runtime input or output. |
| invariants | No new checks or state transitions. |
| ownership | No ownership operation. |
| failure | No executable failure path. |
| cost | No runtime work/allocation. |
| Design | [src/recovery/sql_rows_descriptor.cpp](../../../../../src/recovery/sql_rows_descriptor.cpp) |
