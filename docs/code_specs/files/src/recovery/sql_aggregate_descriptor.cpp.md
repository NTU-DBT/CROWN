# `src/recovery/sql_aggregate_descriptor.cpp` — block usage map

[Source](../../../../../src/recovery/sql_aggregate_descriptor.cpp) · [Source index](../../../README.md) · [Subsystem contracts](../../../subsystem_contracts.md) · [Reviewed primitives](../../../primitives.md)

Encode, validate and publish checkpoints, journals, generations and local delivery receipts with explicit durable authority.

Snapshot SHA-256: `abb50661398026df1a1513b71ac440ba67cb695fe532ab34df61b6a53309bf9c`. 192 lines partitioned into 30 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [recovery](../../../subsystem_contracts.md#recovery). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/checkpoints.md](../../../../checkpoints.md), [docs/journal.md](../../../../journal.md), [docs/journal-files.md](../../../../journal-files.md), [docs/generations.md](../../../../generations.md), [docs/local-sink.md](../../../../local-sink.md), [docs/history-retirement.md](../../../../history-retirement.md), [docs/update_patterns.md](../../../../update_patterns.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–17](../../../../../src/recovery/sql_aggregate_descriptor.cpp#L1) | Imports dependencies; declares namespace scope; declares aliases; declares values/defaults or compile-time conditions. |  · [reviewed contract](#b0001) |
| [B0002 · 18–20](../../../../../src/recovery/sql_aggregate_descriptor.cpp#L18) | Callable definition: std::string_view view(const std::vector&lt;std::uint8_t&gt;& bytes) | calls data, size; returns {reinterpret_cast&lt;const char*&gt;(bytes.data()),bytes.size()} · [reviewed contract](#b0002) |
| [B0003 · 21–21](../../../../../src/recovery/sql_aggregate_descriptor.cpp#L21) | Callable definition: Json limit(std::optional&lt;std::uint64_t&gt; value) | calls Json; returns value?Json(*value):Json{} · [reviewed contract](#b0003) |
| [B0004 · 22–22](../../../../../src/recovery/sql_aggregate_descriptor.cpp#L22) | Callable definition: std::uint64_t number(const Json& value) | calls io::detail::unsigned_integer; returns io::detail::unsigned_integer(value,@ ) · [reviewed contract](#b0004) |
| [B0005 · 23–23](../../../../../src/recovery/sql_aggregate_descriptor.cpp#L23) | Callable definition: std::optional&lt;std::uint64_t&gt; limit(const Json& value) | calls is_null, number; returns value.is_null()?std::nullopt:std::optional{number(value)} · [reviewed contract](#b0005) |
| [B0006 · 24–31](../../../../../src/recovery/sql_aggregate_descriptor.cpp#L24) | Callable definition: Json options_image(const Options& options) | calls limit, Json::array; returns {{@ ,options.count_limit},{@ ,limit(options.group_work_limit)}, · [reviewed contract](#b0006) |
| [B0007 · 32–42](../../../../../src/recovery/sql_aggregate_descriptor.cpp#L32) | Callable definition: Options read_options(const Json& value) | calls io::detail::fields, number, at, limit; guard const auto& w=io::detail::array(value.at("source_work"),"source_work");require(w.size()==5);; returns result · [reviewed contract](#b0007) |
| [B0008 · 43–54](../../../../../src/recovery/sql_aggregate_descriptor.cpp#L43) | Callable definition: Json recipe(const runtime::sql_aggregate::SourceSnapshot& source,const Options& options) | calls source_program, export_core, options_image, io::write_tree; returns {{@ ,1},{@ ,@ },{@ ,@ }, · [reviewed contract](#b0008) |
| [B0009 · 55–61](../../../../../src/recovery/sql_aggregate_descriptor.cpp#L55) | Callable definition: void finite(const AdmissionLimits& limits) | calls require; guard require(limits.lowering.work_limit && limits.lowering.identity.work_limit && b.work_limit && b.sour… · [reviewed contract](#b0009) |
| [B0010 · 62–67](../../../../../src/recovery/sql_aggregate_descriptor.cpp#L62) | Callable definition: void schema_limits(const frontend::SqlAggregateProgram& program,const DescriptorLimits& limits) | calls source_program, sources, require, size; guard const auto sources=program.source_program().sources();require(sources.size()&lt;=limits.image.tables,I…; 1 loop sites · [reviewed contract](#b0010) |
| [B0011 · 68–70](../../../../../src/recovery/sql_aggregate_descriptor.cpp#L68) | Explanatory comments or spacing. | source comment (unverified): // Finite producer caps already within the host caps bound actual construction. · [reviewed contract](#b0011) |
| [B0012 · 71–78](../../../../../src/recovery/sql_aggregate_descriptor.cpp#L71) | Callable definition: void lower_check(const frontend::SqlAggregateProgram& program,const FreeConnexTree& tree, const PhysicalOptions& physical,const A… | calls finite, source_program, export_core, planner::lower_tree; source comment (unverified): // Finite producer caps already within the host caps bound actual construction. · [reviewed contract](#b0012) |
| [B0013 · 79–79](../../../../../src/recovery/sql_aggregate_descriptor.cpp#L79) | Explanatory comments or spacing. | source comment (unverified): // Count/validate before the receiving allocation; all codec passes share work. · [reviewed contract](#b0013) |
| [B0014 · 80–97](../../../../../src/recovery/sql_aggregate_descriptor.cpp#L80) | Callable definition: ImageVector&lt;char&gt; encode_bytes(const resource::MemoryAccount& account,std::string_view binding,std::string_view recipe_bytes, con… | calls require, cbor, inspect, put; guard require(limits.cbor_depth&lt;=256,ImageFault::limit);detail::Cbor cbor(budget,limits);; returns bytes; growth reserve; 1 loop sites; source comment (unverified): // Count/validate before the receiving allocation; all codec passes share work. · [reviewed contract](#b0014) |
| [B0015 · 98–99](../../../../../src/recovery/sql_aggregate_descriptor.cpp#L98) | Closes surrounding scope/type. | source comment (unverified): // namespace · [reviewed contract](#b0015) |
| [B0016 · 100–110](../../../../../src/recovery/sql_aggregate_descriptor.cpp#L100) | Type/record definition: struct Descriptor::Data |  · [reviewed contract](#b0016) |
| [B0017 · 111–111](../../../../../src/recovery/sql_aggregate_descriptor.cpp#L111) | declares namespace scope. |  · [reviewed contract](#b0017) |
| [B0018 · 112–127](../../../../../src/recovery/sql_aggregate_descriptor.cpp#L112) | Type/record definition: class DescriptorFactory | guard require(bool(program) && options.capture_changes,ImageFault::binding);; returns {Descriptor(std::move(data)),std::move(live),{size,budget.used,0}}; growth make_accounted_shared; source comment (unverified): // Whole-frame descriptor identity retained by Data. · [reviewed contract](#b0018) |
| [B0019 · 128–129](../../../../../src/recovery/sql_aggregate_descriptor.cpp#L128) | Closes surrounding scope/type. | source comment (unverified): // namespace detail · [reviewed contract](#b0019) |
| [B0020 · 130–141](../../../../../src/recovery/sql_aggregate_descriptor.cpp#L130) | Callable definition: InspectedDescriptor inspect_descriptor(std::string_view bytes,DescriptorLimits limits) | calls require, size, take, integer; guard require(limits.cbor_depth&lt;=256,ImageFault::limit);require(bytes.size()&lt;=limits.image.bytes,ImageFau…; returns {binding,recipe_bytes,sha256_fixed(bytes),{bytes.size(),budget.used,0}} · [reviewed contract](#b0020) |
| [B0021 · 142–145](../../../../../src/recovery/sql_aggregate_descriptor.cpp#L142) | Callable definition: Admitted admit_into(const resource::MemoryAccount& account,frontend::SqlAggregateProgram program, const FreeConnexTree& tree,cons… | calls detail::DescriptorFactory::admit, std::move; returns detail::DescriptorFactory::admit(account,std::move(program),tree,physical,options,limits,budget) · [reviewed contract](#b0021) |
| [B0022 · 146–182](../../../../../src/recovery/sql_aggregate_descriptor.cpp#L146) | Callable definition: Admitted rebind_into(const resource::MemoryAccount& account,std::string_view bytes,const AdmissionLimits& limits) | calls finite, inspect_descriptor, Json::from_cbor, begin; guard require(catalog.tables.size()&lt;=limits.descriptor.image.tables,ImageFault::limit);; returns admitted; growth emplace_back, reserve; 2 loop sites; source comment (unverified): // Receiving work exhaustion does not invalidate the stored descriptor. · [reviewed contract](#b0022) |
| [B0023 · 183–185](../../../../../src/recovery/sql_aggregate_descriptor.cpp#L183) | Callable definition: const Descriptor::Data& Descriptor::data() const | calls require, bool; guard require(bool(data_),ImageFault::binding);return *data_;; returns *data_ · [reviewed contract](#b0023) |
| [B0024 · 186–186](../../../../../src/recovery/sql_aggregate_descriptor.cpp#L186) | Callable definition: const frontend::SqlAggregateProgram& Descriptor::program() const & | calls data; returns data().program · [reviewed contract](#b0024) |
| [B0025 · 187–187](../../../../../src/recovery/sql_aggregate_descriptor.cpp#L187) | Callable definition: const CompiledProgram& Descriptor::native_program() const & | calls data; returns data().native · [reviewed contract](#b0025) |
| [B0026 · 188–188](../../../../../src/recovery/sql_aggregate_descriptor.cpp#L188) | Callable definition: const runtime::weighted::Binding& Descriptor::native_binding() const & | calls data; returns data().binding · [reviewed contract](#b0026) |
| [B0027 · 189–189](../../../../../src/recovery/sql_aggregate_descriptor.cpp#L189) | Callable definition: const Options& Descriptor::options() const & | calls data; returns data().normal · [reviewed contract](#b0027) |
| [B0028 · 190–190](../../../../../src/recovery/sql_aggregate_descriptor.cpp#L190) | Callable definition: const Hash& Descriptor::sha256() const & | calls data; returns data().digest · [reviewed contract](#b0028) |
| [B0029 · 191–191](../../../../../src/recovery/sql_aggregate_descriptor.cpp#L191) | Callable definition: std::string_view Descriptor::bytes() const & | calls data, size; returns {b.data(),b.size()} · [reviewed contract](#b0029) |
| [B0030 · 192–192](../../../../../src/recovery/sql_aggregate_descriptor.cpp#L192) | Closes surrounding scope/type. | source comment (unverified): // namespace crown::recovery::sql_aggregate · [reviewed contract](#b0030) |

## B0001

[Lines 1–17](../../../../../src/recovery/sql_aggregate_descriptor.cpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L1-L17:sha256:2474c8ecd1e7beec5e8f651307609f381b7753f56232754977d4968586e8f37e
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Imports descriptor, digest, catalog/physical/tree serialization, lowering, ownership, CBOR, and private compiler dependencies; opens the descriptor implementation scope and aliases its JSON/options/wire magic. |
| inputs / outputs | No runtime inputs/outputs are declared by the import/scope lines themselves. |
| invariants | The listed headers and namespace membership determine compile-time name availability; any API behavior belongs to the declarations/definitions that follow. |
| ownership | No object ownership is created by the imports or namespace tokens. |
| failure | No runtime failure path. Missing/incompatible dependencies or a violated compile-time constraint fail translation/linking. |
| cost | Compile/preprocessor work only; no new per-operation runtime overhead. |
| Design | [src/recovery/sql_aggregate_descriptor.cpp](../../../../../src/recovery/sql_aggregate_descriptor.cpp), [docs/code_specs/files/src/recovery/sql_aggregate_descriptor.cpp.md](sql_aggregate_descriptor.cpp.md), [docs/sql_aggregate_descriptor.md](../../../../sql_aggregate_descriptor.md), [docs/sql_aggregate_runtime.md](../../../../sql_aggregate_runtime.md) |

## B0002

[Lines 18–20](../../../../../src/recovery/sql_aggregate_descriptor.cpp#L18); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::string_view view(const std::vector<std::uint8_t>& bytes) {
  return {reinterpret_cast<const char*>(bytes.data()),bytes.size()};
}
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Create a byte-preserving nonowning view over the CBOR encoder’s byte vector. |
| inputs / outputs | Reinterprets the already-built \`vector&lt;uint8_t&gt;\` data pointer and exact length as \`string_view\` for the envelope writer. |
| invariants | Does not convert, normalize or copy the CBOR payload. |
| ownership | The vector must remain alive and unchanged while the local view is used immediately by \`encode_bytes\`. |
| failure | No failure path or ownership transfer is added here. |
| cost | O(1), no allocation. |
| Design | [src/recovery/sql_aggregate_descriptor.cpp](../../../../../src/recovery/sql_aggregate_descriptor.cpp), [docs/sql_aggregate_descriptor.md §Wire and bounded parsing](../../../../sql_aggregate_descriptor.md) |

## B0003

[Lines 21–21](../../../../../src/recovery/sql_aggregate_descriptor.cpp#L21); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Json limit(std::optional<std::uint64_t> value) { return value?Json(*value):Json{}; }
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Encode an optional unsigned operational cap as JSON null or an unsigned integer. |
| inputs / outputs | Maps the stored optional counter limit to the corresponding JSON scalar in the recipe. |
| invariants | Absent means the original producer cap is disabled; zero remains a present, restrictive cap. |
| ownership | Returns a JSON value; no view into the Options object escapes. |
| failure | JSON value construction exceptions propagate in this cold path. |
| cost | Scalar conversion; may use ordinary JSON value storage. |
| Design | [src/recovery/sql_aggregate_descriptor.cpp](../../../../../src/recovery/sql_aggregate_descriptor.cpp), [docs/sql_aggregate_descriptor.md §What is authenticated](../../../../sql_aggregate_descriptor.md) |

## B0004

[Lines 22–22](../../../../../src/recovery/sql_aggregate_descriptor.cpp#L22); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::uint64_t number(const Json& value) { return io::detail::unsigned_integer(value,"R2 descriptor"); }
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Decode a required unsigned JSON field through the shared checked integer reader. |
| inputs / outputs | Receives a JSON value and labels malformed field errors as R2 descriptor input. |
| invariants | Negative, nonnumeric or out-of-range values do not silently convert to unsigned policy values. |
| ownership | Input is a DOM reference valid for the call; output is a scalar. |
| failure | The checked JSON reader propagates its invalid-field failure. |
| cost | Constant scalar conversion. |
| Design | [src/recovery/sql_aggregate_descriptor.cpp](../../../../../src/recovery/sql_aggregate_descriptor.cpp), [docs/sql_aggregate_descriptor.md §Wire and bounded parsing](../../../../sql_aggregate_descriptor.md) |

## B0005

[Lines 23–23](../../../../../src/recovery/sql_aggregate_descriptor.cpp#L23); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::optional<std::uint64_t> limit(const Json& value) { return value.is_null()?std::nullopt:std::optional{number(value)}; }
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Decode JSON null or an unsigned integer as the original optional policy cap. |
| inputs / outputs | Null becomes disabled; otherwise \`number\` performs checked unsigned decoding. |
| invariants | Preserves the distinction between no producer limit and a numeric zero limit. |
| ownership | Returns a value object with no borrowed storage. |
| failure | Malformed non-null fields fail through the checked number reader. |
| cost | Constant scalar conversion. |
| Design | [src/recovery/sql_aggregate_descriptor.cpp](../../../../../src/recovery/sql_aggregate_descriptor.cpp), [docs/sql_aggregate_descriptor.md §What is authenticated](../../../../sql_aggregate_descriptor.md) |

## B0006

[Lines 24–31](../../../../../src/recovery/sql_aggregate_descriptor.cpp#L24); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Json options_image(const Options& options) {
  const auto& n=options.source.native;const auto& w=options.source.source_work_limit;
  return {{"count_limit",options.count_limit},{"group_work",limit(options.group_work_limit)},
      {"memory_bytes",options.memory_limit_bytes},{"capture_changes",options.capture_changes},
      {"source_work",Json::array({w.structural_steps,w.scalar_fields,w.scalar_bytes,w.pointer_slots,w.link_actions})},
      {"native",{{"work",limit(n.work_limit)},{"multiplicity_limit",n.multiplicity_limit},
          {"memory_bytes",n.memory_limit_bytes},{"capture_changes",n.capture_changes},{"capture_events",n.capture_events}}}};
}
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Serialize every operational SQL aggregate and nested native/source policy field used by the runtime. |
| inputs / outputs | Emits count/group/memory/capture values, five source-work counters, and native work/multiplicity/memory/capture settings. |
| invariants | This is a canonical recipe representation of producer options; a later receiving account grant does not replace stored policy values. |
| ownership | Reads the caller’s Options by reference and returns an owning temporary JSON value. |
| failure | Ordinary JSON construction failures propagate before descriptor publication. |
| cost | Visits a fixed number of policy fields; creates ordinary temporary JSON storage. |
| Design | [src/recovery/sql_aggregate_descriptor.cpp](../../../../../src/recovery/sql_aggregate_descriptor.cpp), [docs/sql_aggregate_descriptor.md §What is authenticated](../../../../sql_aggregate_descriptor.md) |

## B0007

[Lines 32–42](../../../../../src/recovery/sql_aggregate_descriptor.cpp#L32); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Options read_options(const Json& value) {
  io::detail::fields(value,"normal",{"count_limit","group_work","memory_bytes","capture_changes","source_work","native"});
  Options result;result.count_limit=number(value.at("count_limit"));result.group_work_limit=limit(value.at("group_work"));
  result.memory_limit_bytes=number(value.at("memory_bytes"));result.capture_changes=value.at("capture_changes").get<bool>();
  const auto& w=io::detail::array(value.at("source_work"),"source_work");require(w.size()==5);
  result.source.source_work_limit={number(w[0]),number(w[1]),number(w[2]),number(w[3]),number(w[4])};
  const auto& native=value.at("native");io::detail::fields(native,"native",{"work","multiplicity_limit","memory_bytes","capture_changes","capture_events"});
  auto& n=result.source.native;n.work_limit=limit(native.at("work"));n.multiplicity_limit=number(native.at("multiplicity_limit"));
  n.memory_limit_bytes=number(native.at("memory_bytes"));n.capture_changes=native.at("capture_changes").get<bool>();
  n.capture_events=native.at("capture_events").get<bool>();return result;
}
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Restore the exact serialized normal runtime policy from a previously preflighted recipe DOM. |
| inputs / outputs | Requires the exact top-level and nested field sets, five source-work entries, and decodes optional work values and booleans. |
| invariants | Rejects missing/extra policy fields or wrong array width instead of importing an extensible DTO; stored memory values remain policy fields, not new grants. |
| ownership | Reads a borrowed DOM node and returns a small owning Options value. |
| failure | Malformed shape or scalar types fail before runtime construction. |
| cost | Fixed field/array traversal; DOM storage is owned by the caller and not included in codec work as compiler CPU. |
| Design | [src/recovery/sql_aggregate_descriptor.cpp](../../../../../src/recovery/sql_aggregate_descriptor.cpp), [docs/sql_aggregate_descriptor.md §What is authenticated](../../../../sql_aggregate_descriptor.md), [docs/sql_aggregate_descriptor.md §Wire and bounded parsing](../../../../sql_aggregate_descriptor.md) |

## B0008

[Lines 43–54](../../../../../src/recovery/sql_aggregate_descriptor.cpp#L43); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Json recipe(const runtime::sql_aggregate::SourceSnapshot& source,const Options& options) {
  const auto& native=source.source.native_program;const auto& binding=source.source.native_binding;
  const auto core=source.program.source_program().export_core();
  return {{"schema_version",1},{"records","CROWNAG2;1"},{"arithmetic","checked-nonnegative-bag-signed-sql-aggregates;1"},
      {"output","full-nullable-key-before-after;1"},{"normal",options_image(options)},
      {"tree",io::write_tree(planner::compiler_source_detail::tree(native.tree()),core.catalog,core.query)},
      {"physical_options",io::write_physical_options(planner::compiler_source_detail::options(native.options()))},
      {"physical_sha256",native.physical_sha256()},{"source_sha256",native.physical_source_sha256()},
      {"weighted_shape_sha256",std::string(binding.shape_sha256.data(),binding.shape_sha256.size())},
      {"weighted_sha256",std::string(binding.weighted_sha256.data(),binding.weighted_sha256.size())},
      {"multiplicity_limit",binding.multiplicity_limit}};
}
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Describe the actual runtime’s native tree, physical options, binding hashes and record policies for exact rebind. |
| inputs / outputs | Combines versioned arithmetic/output tags, original operational options, serialized genuine tree/options, physical/source hashes and weighted binding identities. |
| invariants | Tree and native hashes come from the real \`SourceSnapshot\`; recipe bytes alone never instantiate a compiled native program. |
| ownership | Borrows the snapshot/options during serialization and returns a temporary JSON DOM; final encoded bytes are separately retained by Descriptor::Data. |
| failure | Tree/physical serializer and JSON errors propagate during cold factory admission. |
| cost | Cold traversal and ordinary JSON/serializer workspace; not an update-path cost or CPU theorem. |
| Design | [src/recovery/sql_aggregate_descriptor.cpp](../../../../../src/recovery/sql_aggregate_descriptor.cpp), [include/crown/runtime/sql_aggregate.hpp](../../../../../include/crown/runtime/sql_aggregate.hpp), [docs/sql_aggregate_descriptor.md §What is authenticated](../../../../sql_aggregate_descriptor.md) |

## B0009

[Lines 55–61](../../../../../src/recovery/sql_aggregate_descriptor.cpp#L55); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void finite(const AdmissionLimits& limits) {
  const auto& b=limits.binding;
  require(limits.lowering.work_limit && limits.lowering.identity.work_limit && b.work_limit && b.source.work_limit &&
      b.source.binding.limits.work_limit && b.kernel.limits.work_limit,ImageFault::limit);
  require(b.parsing.ast_depth<=256 && b.source.binding.limits.recursion_limit<=256 &&
      b.kernel.limits.recursion_limit<=256,ImageFault::limit);
}
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Require finite compiler/lowerer work caps and supported recursion bounds before receiving descriptor construction. |
| inputs / outputs | Checks outer SQL aggregate, row-source, SQL binder, aggregate binder, physical lowering and identity work limits plus recursion-depth caps. |
| invariants | Host grants are an admission boundary and remain distinct from stored producer options. |
| ownership | Reads the AdmissionLimits object only; no state escapes. |
| failure | A missing required work cap or recursion above 256 fails with ImageFault::limit before factory work proceeds. |
| cost | Constant number of optional/size comparisons. |
| Design | [src/recovery/sql_aggregate_descriptor.cpp](../../../../../src/recovery/sql_aggregate_descriptor.cpp), [include/crown/frontend/sql_aggregate.hpp](../../../../../include/crown/frontend/sql_aggregate.hpp), [include/crown/ir/physical.hpp](../../../../../include/crown/ir/physical.hpp), [docs/sql_aggregate_descriptor.md §Ownership, failure and cost](../../../../sql_aggregate_descriptor.md) |

## B0010

[Lines 62–67](../../../../../src/recovery/sql_aggregate_descriptor.cpp#L62); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void schema_limits(const frontend::SqlAggregateProgram& program,const DescriptorLimits& limits) {
  const auto sources=program.source_program().sources();require(sources.size()<=limits.image.tables,ImageFault::limit);
  for(const auto& source:sources)require(source.columns.size()<=limits.image.fields,ImageFault::limit);
  require(program.kernel_program().group_columns().size()<=limits.image.fields &&
      program.kernel_program().outputs().size()<=limits.image.fields,ImageFault::limit);
}
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Cap actual bound source schemas and aggregate input/output widths before writing a descriptor. |
| inputs / outputs | Checks source table count, each source column count, group-column width and aggregate output width against image limits. |
| invariants | This is descriptor schema metadata admission; no physical rows are stored and the image row statistic remains zero. |
| ownership | Reads the genuine immutable program by const reference. |
| failure | A schema exceeding the descriptor cap fails with ImageFault::limit before native runtime publication. |
| cost | O(source count plus bounded column-width comparisons); no row traversal. |
| Design | [src/recovery/sql_aggregate_descriptor.cpp](../../../../../src/recovery/sql_aggregate_descriptor.cpp), [include/crown/frontend/sql_aggregate.hpp](../../../../../include/crown/frontend/sql_aggregate.hpp), [docs/sql_aggregate_descriptor.md §Wire and bounded parsing](../../../../sql_aggregate_descriptor.md) |

## B0011

[Lines 68–70](../../../../../src/recovery/sql_aggregate_descriptor.cpp#L68); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L68-L70:sha256:4d82b4a533c0726ef2f651489a0ba0b3601dee4a8cb17566ce4988ecae2e36bf
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Design note for adjacent code: Finite producer caps already within the host caps bound actual construction. Otherwise first check this deterministic input under a finite host allowance; the runtime still uses the original options, including disabled producer caps. This is caller guidance recorded as prose, not an executable result. |
| inputs / outputs | No runtime interface is implemented by these comment-only lines. They sit at src/recovery/sql_aggregate_descriptor.cpp lines 66-72; the surrounding declaration/body defines its own inputs and outputs. |
| invariants | The words record the intended use boundary only. They do not add a guard, proof, capability, transaction, durability guarantee, or account charge; verify behavior in the referenced implementation. |
| ownership | Comment text owns no data. Object lifetimes, borrows, and account attribution remain those of the adjacent source objects and their constructors. |
| failure | No failure path is implemented here. Any mentioned failure or recovery rule belongs to the adjacent operation and its existing error carrier. |
| cost | No runtime work is performed by these lines; any cost/bound in the note is not certified by this comment-only card. |
| Design | [src/recovery/sql_aggregate_descriptor.cpp](../../../../../src/recovery/sql_aggregate_descriptor.cpp), [docs/code_specs/files/src/recovery/sql_aggregate_descriptor.cpp.md](sql_aggregate_descriptor.cpp.md), [docs/sql_aggregate_descriptor.md](../../../../sql_aggregate_descriptor.md), [docs/sql_aggregate_runtime.md](../../../../sql_aggregate_runtime.md) |

## B0012

[Lines 71–78](../../../../../src/recovery/sql_aggregate_descriptor.cpp#L71); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void lower_check(const frontend::SqlAggregateProgram& program,const FreeConnexTree& tree,
    const PhysicalOptions& physical,const AdmissionLimits& limits) {
  finite(limits);const auto& stored=physical.limits;
  if(stored.work_limit && stored.identity.work_limit && *stored.work_limit<=*limits.lowering.work_limit &&
      *stored.identity.work_limit<=*limits.lowering.identity.work_limit)return;
  const auto core=program.source_program().export_core();
  static_cast<void>(planner::lower_tree(core.catalog,core.query,tree,physical,limits.lowering));
}
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Ensure the supplied genuine tree can be lowered under finite host limits without changing stored physical policy. |
| inputs / outputs | Checks all AdmissionLimits first. If both original producer work and identity caps are present and within host caps, leaves the actual runtime construction to perform the bounded lowering; otherwise performs and discards a finite host lowering pass before original-policy construction. |
| invariants | Never rewrites PhysicalOptions or caches a host-policy graph. A supplied valid free-connex tree establishes an upper height bound, not minimum-height proof. |
| ownership | Borrows compiler program/tree/options for the call; any preflight plan is discarded rather than retained. |
| failure | Missing host grants fail as ImageFault::limit; planner/lowerer validation errors propagate from the actual attempted lowering phase. |
| cost | One lowering in the already-bounded producer fast path; otherwise one finite host check plus the existing runtime’s original-policy lowering. This is cold admission work, not per-row work. |
| Design | [src/recovery/sql_aggregate_descriptor.cpp](../../../../../src/recovery/sql_aggregate_descriptor.cpp), [include/crown/planner/lower.hpp](../../../../../include/crown/planner/lower.hpp), [include/crown/ir/physical.hpp](../../../../../include/crown/ir/physical.hpp), [docs/sql_aggregate_descriptor.md §Ownership, failure and cost](../../../../sql_aggregate_descriptor.md) |

## B0013

[Lines 79–79](../../../../../src/recovery/sql_aggregate_descriptor.cpp#L79); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L79-L79:sha256:9a76a06f72a17e72e723a8f1dd671add6e42c491ee2a4982985ec9b2cf82d0a8
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Design note for adjacent code: Count/validate before the receiving allocation; all codec passes share work. This is caller guidance recorded as prose, not an executable result. |
| inputs / outputs | No runtime interface is implemented by these comment-only lines. They sit at src/recovery/sql_aggregate_descriptor.cpp lines 77-81; the surrounding declaration/body defines its own inputs and outputs. |
| invariants | The words record the intended use boundary only. They do not add a guard, proof, capability, transaction, durability guarantee, or account charge; verify behavior in the referenced implementation. |
| ownership | Comment text owns no data. Object lifetimes, borrows, and account attribution remain those of the adjacent source objects and their constructors. |
| failure | No failure path is implemented here. Any mentioned failure or recovery rule belongs to the adjacent operation and its existing error carrier. |
| cost | No runtime work is performed by these lines; any cost/bound in the note is not certified by this comment-only card. |
| Design | [src/recovery/sql_aggregate_descriptor.cpp](../../../../../src/recovery/sql_aggregate_descriptor.cpp), [docs/code_specs/files/src/recovery/sql_aggregate_descriptor.cpp.md](sql_aggregate_descriptor.cpp.md), [docs/sql_aggregate_descriptor.md](../../../../sql_aggregate_descriptor.md), [docs/sql_aggregate_runtime.md](../../../../sql_aggregate_runtime.md) |

## B0014

[Lines 80–97](../../../../../src/recovery/sql_aggregate_descriptor.cpp#L80); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
ImageVector<char> encode_bytes(const resource::MemoryAccount& account,std::string_view binding,std::string_view recipe_bytes,
    const DescriptorLimits& limits,Budget& budget) {
  require(limits.cbor_depth<=256,ImageFault::limit);detail::Cbor cbor(budget,limits);
  cbor.inspect(binding);cbor.inspect(recipe_bytes);
  const auto write=[&](Writer& writer) {
    writer.put(magic);writer.integer(1,2);writer.integer(0,2);writer.integer(0,8);
    std::array<char,64> blank{};blank.fill('0');writer.put({blank.data(),blank.size()});writer.put({blank.data(),blank.size()});
    writer.integer(binding.size(),8);writer.put(binding);writer.integer(recipe_bytes.size(),8);writer.put(recipe_bytes);
  };
  Writer measure{budget,nullptr};write(measure);require(measure.size<=SIZE_MAX,ImageFault::limit);
  ImageVector<char> bytes(image_allocator<char>(account));bytes.reserve(static_cast<std::size_t>(measure.size));
  Writer writer{budget,&bytes};write(writer);const auto body_size=bytes.size()-frame_header_size;
  for(unsigned i=0;i<8;++i)bytes[12+i]=static_cast<char>(std::uint64_t(body_size)>>(8*i));
  budget.charge(body_size);const auto body=sha256_fixed({bytes.data()+frame_header_size,body_size});
  std::copy(body.begin(),body.end(),bytes.begin()+20);budget.charge(frame_prefix_size);
  const auto prefix=sha256_fixed({bytes.data(),frame_prefix_size});std::copy(prefix.begin(),prefix.end(),bytes.begin()+frame_prefix_size);
  return bytes;
}
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Preflight two CBOR components and emit one account-owned CROWNAD2 frame with protected lengths and hashes. |
| inputs / outputs | Checks CBOR depth/items/work for binding and recipe under one Budget, measures the fixed header plus length-bearing components, reserves the exact image vector, writes it, then fills body size/body hash/prefix hash. |
| invariants | Exact byte limits and one shared budget cover validation, measurement, write and hash passes; only the resulting byte vector is retained by the image account. |
| ownership | Input views borrow their source bytes through the call; returned ImageVector owns bytes through the receiving MemoryAccount. |
| failure | ImageLimit/ImageWork failures occur before or during the funded writer; allocator failures propagate and discard the partial vector. |
| cost | Multiple linear byte/item visits under shared caps, plus Cbor key comparisons; one exact-capacity receiving vector allocation, no per-cell payload allocation. |
| Design | [src/recovery/sql_aggregate_descriptor.cpp](../../../../../src/recovery/sql_aggregate_descriptor.cpp), [src/recovery/sql_aggregate_cbor.hpp](../../../../../src/recovery/sql_aggregate_cbor.hpp), [docs/sql_aggregate_descriptor.md §Wire and bounded parsing](../../../../sql_aggregate_descriptor.md), [docs/sql_aggregate_descriptor.md §Ownership, failure and cost](../../../../sql_aggregate_descriptor.md) |

## B0015

[Lines 98–99](../../../../../src/recovery/sql_aggregate_descriptor.cpp#L98); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L98-L99:sha256:c929980d95efc152dc886ac42af0f045075441dd18a8f886364828ead327bbd3
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Closes the anonymous namespace at this source boundary; this is a lexical delimiter, not an operation. |
| inputs / outputs | No runtime input or output. Declarations following the span leave the preceding C++ scope. |
| invariants | The delimiter ends the preceding scope's visibility/linkage region; it adds no validation, publication, ownership transfer, or runtime authority. |
| ownership | The delimiter adds no owner. If it ends a function/block with live automatic objects, their normal destructors release those objects; namespace and type-definition closes change no existing object's lifetime. |
| failure | No explicit failure translation or catch is added. If a function/block exit destroys automatic objects, exception behavior follows those destructors; namespace/type closes have no runtime failure path. |
| cost | The delimiter adds no algorithmic work. A function/block exit can run existing automatic-object destructors and cleanup; namespace/type closes have no runtime cost. |
| Design | [src/recovery/sql_aggregate_descriptor.cpp](../../../../../src/recovery/sql_aggregate_descriptor.cpp), [docs/code_specs/files/src/recovery/sql_aggregate_descriptor.cpp.md](sql_aggregate_descriptor.cpp.md), [docs/sql_aggregate_descriptor.md](../../../../sql_aggregate_descriptor.md), [docs/sql_aggregate_runtime.md](../../../../sql_aggregate_runtime.md) |

## B0016

[Lines 100–110](../../../../../src/recovery/sql_aggregate_descriptor.cpp#L100); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct Descriptor::Data {
  frontend::SqlAggregateProgram program;
  CompiledProgram native;
  runtime::weighted::Binding binding;
  Options normal;
  ImageVector<char> bytes;
  Hash digest;
  Data(runtime::sql_aggregate::SourceSnapshot source,Options options,ImageVector<char> encoded)
      : program(std::move(source.program)),native(std::move(source.source.native_program)),binding(source.source.native_binding),
        normal(options),bytes(std::move(encoded)),digest(sha256_fixed({bytes.data(),bytes.size()})) {}
};
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Own the immutable descriptor payload and retain authentic metadata produced by the real runtime snapshot. |
| inputs / outputs | Stores frozen SQL program, actual CompiledProgram, weighted Binding, original runtime Options, exact frame bytes and whole-frame digest. |
| invariants | Factory-only construction keeps DTO fields from becoming native import authority; the retained byte vector and shared Data use the receiver account. |
| ownership | Descriptor handles share the account-owned Data; program/native handles retain their own immutable owners, and borrowed accessors require a live handle. |
| failure | Accounted shared allocation or preceding vector/compile failures propagate; partial objects destruct normally. |
| cost | One shared Data/control allocation and one exact frame vector, plus genuine runtime/program metadata already retained under the account. |
| Design | [src/recovery/sql_aggregate_descriptor.cpp](../../../../../src/recovery/sql_aggregate_descriptor.cpp), [include/crown/recovery/sql_aggregate_descriptor.hpp](../../../../../include/crown/recovery/sql_aggregate_descriptor.hpp), [docs/sql_aggregate_descriptor.md §Ownership, failure and cost](../../../../sql_aggregate_descriptor.md) |

## B0017

[Lines 111–111](../../../../../src/recovery/sql_aggregate_descriptor.cpp#L111); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L111-L111:sha256:5535809b42b9d97cdfea935b5d84662804aaab9873ce9d79d846ab3ec8a625cb
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Opens the private descriptor factory namespace where admit/rebind construct genuine compiler/native metadata and accounted descriptor state. |
| inputs / outputs | No runtime inputs/outputs are declared by the import/scope lines themselves. |
| invariants | The listed headers and namespace membership determine compile-time name availability; any API behavior belongs to the declarations/definitions that follow. |
| ownership | No object ownership is created by the imports or namespace tokens. |
| failure | No runtime failure path. Missing/incompatible dependencies or a violated compile-time constraint fail translation/linking. |
| cost | Compile/preprocessor work only; no new per-operation runtime overhead. |
| Design | [src/recovery/sql_aggregate_descriptor.cpp](../../../../../src/recovery/sql_aggregate_descriptor.cpp), [docs/code_specs/files/src/recovery/sql_aggregate_descriptor.cpp.md](sql_aggregate_descriptor.cpp.md), [docs/sql_aggregate_descriptor.md](../../../../sql_aggregate_descriptor.md), [docs/sql_aggregate_runtime.md](../../../../sql_aggregate_runtime.md) |

## B0018

[Lines 112–127](../../../../../src/recovery/sql_aggregate_descriptor.cpp#L112); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
class DescriptorFactory {
 public:
  static Admitted admit(const resource::MemoryAccount& account,frontend::SqlAggregateProgram program,
      const FreeConnexTree& tree,const PhysicalOptions& physical,Options options,const AdmissionLimits& limits,Budget& budget) {
    require(bool(program) && options.capture_changes,ImageFault::binding);
    require(program.binding_image().size()<=limits.descriptor.image.bytes,ImageFault::limit);
    schema_limits(program,limits.descriptor);lower_check(program,tree,physical,limits);
    auto live=runtime::SqlAggregateRuntime::create_into(account,std::move(program),tree,physical,options);
    auto source=live.source_snapshot();const auto image=Json::to_cbor(recipe(source,options));
    auto bytes=encode_bytes(account,source.program.binding_image(),view(image),limits.descriptor,budget);
    budget.charge(bytes.size()); // Whole-frame descriptor identity retained by Data.
    auto data=resource::make_accounted_shared<Descriptor::Data>(account,resource::MemoryPurpose::immutable_metadata,
        std::move(source),options,std::move(bytes));
    const auto size=data->bytes.size();return {Descriptor(std::move(data)),std::move(live),{size,budget.used,0}};
  }
};
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Orchestrate genuine descriptor admission using source factories instead of serialized native imports. |
| inputs / outputs | Private \`admit\` checks program/capture policy, frame binding-image size and schemas, invokes lower_check, builds the actual SqlAggregateRuntime, snapshots its real source/native recipe, encodes bytes and funds Descriptor::Data. |
| invariants | Returns a C0 runtime and matching descriptor. No physical checkpoint rows, WAL replay, root selection or caller-edited DTO is accepted. |
| ownership | The private factory is the sole friend that constructs Descriptor; its local runtime/source values unwind if any later serialization or account step fails. |
| failure | Fixed policy violations use ImageFailure; binder/lowerer/JSON and memory failures propagate without a catch/retry/rollback layer. |
| cost | Cold compiler/runtime construction plus bounded CBOR/frame work and retained account allocations; no normal-update hot-path field or work is added. |
| Design | [src/recovery/sql_aggregate_descriptor.cpp](../../../../../src/recovery/sql_aggregate_descriptor.cpp), [include/crown/recovery/sql_aggregate_descriptor.hpp](../../../../../include/crown/recovery/sql_aggregate_descriptor.hpp), [include/crown/runtime/sql_aggregate.hpp](../../../../../include/crown/runtime/sql_aggregate.hpp), [docs/sql_aggregate_descriptor.md §What is authenticated](../../../../sql_aggregate_descriptor.md), [docs/sql_aggregate_descriptor.md §Ownership, failure and cost](../../../../sql_aggregate_descriptor.md) |

## B0019

[Lines 128–129](../../../../../src/recovery/sql_aggregate_descriptor.cpp#L128); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L128-L129:sha256:b23afc92a44293edd31841f0512be65ae6b91c5f500f762bb06b88c959e15d1f
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Closes the namespace detail at this source boundary; this is a lexical delimiter, not an operation. |
| inputs / outputs | No runtime input or output. Declarations following the span leave the preceding C++ scope. |
| invariants | The delimiter ends the preceding scope's visibility/linkage region; it adds no validation, publication, ownership transfer, or runtime authority. |
| ownership | The delimiter adds no owner. If it ends a function/block with live automatic objects, their normal destructors release those objects; namespace and type-definition closes change no existing object's lifetime. |
| failure | No explicit failure translation or catch is added. If a function/block exit destroys automatic objects, exception behavior follows those destructors; namespace/type closes have no runtime failure path. |
| cost | The delimiter adds no algorithmic work. A function/block exit can run existing automatic-object destructors and cleanup; namespace/type closes have no runtime cost. |
| Design | [src/recovery/sql_aggregate_descriptor.cpp](../../../../../src/recovery/sql_aggregate_descriptor.cpp), [docs/code_specs/files/src/recovery/sql_aggregate_descriptor.cpp.md](sql_aggregate_descriptor.cpp.md), [docs/sql_aggregate_descriptor.md](../../../../sql_aggregate_descriptor.md), [docs/sql_aggregate_runtime.md](../../../../sql_aggregate_runtime.md) |

## B0020

[Lines 130–141](../../../../../src/recovery/sql_aggregate_descriptor.cpp#L130); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
InspectedDescriptor inspect_descriptor(std::string_view bytes,DescriptorLimits limits) {
  require(limits.cbor_depth<=256,ImageFault::limit);require(bytes.size()<=limits.image.bytes,ImageFault::limit);
  Budget budget{limits.image};Reader reader{bytes,budget};require(reader.take(8)==magic,ImageFault::version);
  require(reader.integer(2)==1 && reader.integer(2)==0,ImageFault::version);const auto size=reader.integer(8);
  const auto body_hash=reader.take(64),prefix_hash=reader.take(64);budget.charge(frame_prefix_size);
  const auto prefix=sha256_fixed(bytes.substr(0,frame_prefix_size));require(prefix_hash==std::string_view(prefix.data(),prefix.size()));
  require(size==bytes.size()-frame_header_size);budget.charge(size);const auto body=sha256_fixed(bytes.substr(frame_header_size));
  require(body_hash==std::string_view(body.data(),body.size()));
  const auto binding=reader.take(reader.size(limits.image.bytes));const auto recipe_bytes=reader.take(reader.size(limits.image.bytes));
  require(reader.position==bytes.size());detail::Cbor cbor(budget,limits);cbor.inspect(binding);cbor.inspect(recipe_bytes);
  budget.charge(bytes.size());return {binding,recipe_bytes,sha256_fixed(bytes),{bytes.size(),budget.used,0}};
}
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Validate a complete descriptor frame and both CBOR byte regions without materializing a DOM. |
| inputs / outputs | Checks depth/byte caps, CROWNAD2 version/reserved bits, protected prefix/body hashes, exact subview lengths/end, CBOR schema envelope and complete-frame SHA. |
| invariants | Returns only borrowed byte views, identity and byte/work stats; it does not bind original SQL, inspect native semantics, or authorize a durable root. |
| ownership | The input buffer must outlive all returned views; function retains no owner. |
| failure | Malformed bytes, unsupported version, schema shapes or limits fail with fixed ImageFailure. |
| cost | Linear hashing/reader passes and bounded CBOR traversal with strict key comparisons; no covered C++ heap allocation. |
| Design | [src/recovery/sql_aggregate_descriptor.cpp](../../../../../src/recovery/sql_aggregate_descriptor.cpp), [src/recovery/sql_aggregate_cbor.hpp](../../../../../src/recovery/sql_aggregate_cbor.hpp), [include/crown/recovery/sql_aggregate_descriptor.hpp](../../../../../include/crown/recovery/sql_aggregate_descriptor.hpp), [docs/sql_aggregate_descriptor.md §Wire and bounded parsing](../../../../sql_aggregate_descriptor.md) |

## B0021

[Lines 142–145](../../../../../src/recovery/sql_aggregate_descriptor.cpp#L142); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Admitted admit_into(const resource::MemoryAccount& account,frontend::SqlAggregateProgram program,
    const FreeConnexTree& tree,const PhysicalOptions& physical,Options options,const AdmissionLimits& limits) {
  Budget budget{limits.descriptor.image};return detail::DescriptorFactory::admit(account,std::move(program),tree,physical,options,limits,budget);
}
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Run the public factory path from a genuine pre-bound compiler program and caller-supplied tree. |
| inputs / outputs | Creates the first descriptor Budget from descriptor image caps and delegates the untouched program/tree/physical/runtime policies to the private factory. |
| invariants | No source tree DTO is parsed from bytes here; original tree/policies remain the input authority and capture changes is mandatory. |
| ownership | Move-passes the genuine program into the receiving runtime; account owns the returned runtime and descriptor metadata. |
| failure | All private-factory validation, lowerer and account errors propagate to the caller. |
| cost | Wrapper work is constant; substantive cold costs are those of the factory and actual runtime construction. |
| Design | [src/recovery/sql_aggregate_descriptor.cpp](../../../../../src/recovery/sql_aggregate_descriptor.cpp), [include/crown/recovery/sql_aggregate_descriptor.hpp](../../../../../include/crown/recovery/sql_aggregate_descriptor.hpp), [docs/sql_aggregate_descriptor.md §What is authenticated](../../../../sql_aggregate_descriptor.md) |

## B0022

[Lines 146–182](../../../../../src/recovery/sql_aggregate_descriptor.cpp#L146); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Admitted rebind_into(const resource::MemoryAccount& account,std::string_view bytes,const AdmissionLimits& limits) {
  finite(limits);const auto inspected=inspect_descriptor(bytes,limits.descriptor);
  Budget budget{limits.descriptor.image};budget.used=inspected.statistics.work;
  const auto binding=Json::from_cbor(inspected.binding_image.begin(),inspected.binding_image.end());
  const auto stored=Json::from_cbor(inspected.recipe.begin(),inspected.recipe.end());
  auto options=limits.binding;const auto catalog=io::read_catalog_payload(binding.at("catalog"));
  require(catalog.tables.size()<=limits.descriptor.image.tables,ImageFault::limit);
  for(const auto& table:catalog.tables)require(table.columns.size()<=limits.descriptor.image.fields,ImageFault::limit);
  const auto parameters=io::read_catalog_payload(binding.at("parameter_declarations"));
  require(parameters.tables.size()==1 && parameters.tables[0].name=="parameters",ImageFault::binding);
  options.source.binding.parameters=parameters.tables[0].columns;options.source.parameters.clear();
  const auto& values=io::detail::array(binding.at("parameter_values"),"parameter_values");
  require(values.size()==options.source.binding.parameters.size(),ImageFault::binding);
  options.source.parameters.reserve(values.size());
  for(const auto& value:values) {
    if(value.is_null())options.source.parameters.emplace_back();
    else options.source.parameters.emplace_back(io::read_scalar(value));
  }
  const auto scale=number(binding.at("kernel").at("average_scale"));require(scale<=18,ImageFault::binding);
  options.kernel.average_scale=static_cast<std::uint8_t>(scale);
  const auto sql=io::detail::string(binding.at("original_sql"),"original_sql");
  auto result=frontend::bind_sql_aggregate_into(account,sql,catalog,options);
  if(const auto* failure=std::get_if<frontend::BindingDiagnostic>(&result)) {
    // Receiving work exhaustion does not invalidate the stored descriptor.
    throw ImageFailure(failure->diagnostic.code=="resource_limit"?ImageFault::work:ImageFault::binding);
  }
  auto program=std::get<frontend::SqlAggregateProgram>(std::move(result));
  budget.charge(std::min(program.binding_image().size(),inspected.binding_image.size()));
  require(program.binding_image()==inspected.binding_image,ImageFault::binding);
  const auto core=program.source_program().export_core();
  const auto tree=io::read_tree(stored.at("tree").dump(),core.catalog,core.query);
  const auto physical=io::read_physical_options(stored.at("physical_options").dump());
  const auto normal=read_options(stored.at("normal"));
  auto admitted=detail::DescriptorFactory::admit(account,std::move(program),tree,physical,normal,limits,budget);
  budget.charge(std::min(admitted.descriptor.bytes().size(),bytes.size()));
  require(admitted.descriptor.bytes()==bytes,ImageFault::binding);admitted.statistics.work=budget.used;return admitted;
}
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Reconstruct the original bound SQL program and native descriptor from exact bytes, then compare complete factory output. |
| inputs / outputs | Requires finite limits, inspects wire first, parses bounded CBOR DOMs, rebuilds catalog/typed parameters/AVG, calls real SQL binder, checks exact binding bytes, decodes tree/physical/options, runs DescriptorFactory and checks complete frame equality. |
| invariants | Stored hashes, tree, decoder metadata and options are claims checked against recreated genuine objects; it returns a fresh C0 runtime, not state replay. |
| ownership | Input bytes are borrowed only during admission; the new runtime/descriptor and all retained metadata use the receiving account. Ordinary DOM/compiler workspace remains outside MemoryAccount accounting. |
| failure | A binder resource_limit diagnostic becomes ImageFailure(work); other binding diagnostics become ImageFailure(binding). Wire/JSON/lowering/account failures propagate and incomplete owners unwind before publication. Cold classification adds no catch or retry. |
| cost | Bounded repeated wire scans and exact byte comparisons plus real binder/DOM/tree/compiler costs; one or conditionally two lowerings according to stored producer caps. |
| Design | [src/recovery/sql_aggregate_descriptor.cpp](../../../../../src/recovery/sql_aggregate_descriptor.cpp), [include/crown/recovery/sql_aggregate_descriptor.hpp](../../../../../include/crown/recovery/sql_aggregate_descriptor.hpp), [docs/sql_aggregate_descriptor.md §What is authenticated](../../../../sql_aggregate_descriptor.md), [docs/sql_aggregate_descriptor.md §Ownership, failure and cost](../../../../sql_aggregate_descriptor.md) |

## B0023

[Lines 183–185](../../../../../src/recovery/sql_aggregate_descriptor.cpp#L183); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
const Descriptor::Data& Descriptor::data() const {
  require(bool(data_),ImageFault::binding);return *data_;
}
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Require a nonempty descriptor before any immutable metadata accessor reads private Data. |
| inputs / outputs | Returns the underlying Data object by const reference only when the shared handle is engaged. |
| invariants | No mutable state or fallback import path is exposed. |
| ownership | The Descriptor must retain its shared_ptr for the returned reference lifetime. |
| failure | An empty handle fails with ImageFault::binding. |
| cost | One boolean check and reference return. |
| Design | [src/recovery/sql_aggregate_descriptor.cpp](../../../../../src/recovery/sql_aggregate_descriptor.cpp), [include/crown/recovery/sql_aggregate_descriptor.hpp](../../../../../include/crown/recovery/sql_aggregate_descriptor.hpp), [docs/sql_aggregate_descriptor.md §Ownership, failure and cost](../../../../sql_aggregate_descriptor.md) |

## B0024

[Lines 186–186](../../../../../src/recovery/sql_aggregate_descriptor.cpp#L186); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
const frontend::SqlAggregateProgram& Descriptor::program() const & { return data().program; }
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Expose the exact factory-produced immutable SQL compiler program. |
| inputs / outputs | Returns a const reference into retained descriptor Data. |
| invariants | The handle is lvalue-only at the declaration boundary; callers cannot mutate or import a DTO through this accessor. |
| ownership | Borrow ends with the last surviving Descriptor/Data owner. |
| failure | Empty descriptor fails through \`data()\` with ImageFault::binding. |
| cost | Reference return only. |
| Design | [src/recovery/sql_aggregate_descriptor.cpp](../../../../../src/recovery/sql_aggregate_descriptor.cpp), [include/crown/recovery/sql_aggregate_descriptor.hpp](../../../../../include/crown/recovery/sql_aggregate_descriptor.hpp), [docs/sql_aggregate_descriptor.md §What is authenticated](../../../../sql_aggregate_descriptor.md), [docs/sql_aggregate_descriptor.md §Ownership, failure and cost](../../../../sql_aggregate_descriptor.md) |

## B0025

[Lines 187–187](../../../../../src/recovery/sql_aggregate_descriptor.cpp#L187); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
const CompiledProgram& Descriptor::native_program() const & { return data().native; }
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Expose the genuine compiled native program retained from actual runtime construction. |
| inputs / outputs | Returns a const reference to the retained CompiledProgram. |
| invariants | The compiled object is produced by real SQL/native factories and is not reconstructed from serialized hashes. |
| ownership | Reference is borrowed while a Descriptor owner survives. |
| failure | Empty descriptor fails with ImageFault::binding. |
| cost | Reference return only. |
| Design | [src/recovery/sql_aggregate_descriptor.cpp](../../../../../src/recovery/sql_aggregate_descriptor.cpp), [include/crown/recovery/sql_aggregate_descriptor.hpp](../../../../../include/crown/recovery/sql_aggregate_descriptor.hpp), [docs/sql_aggregate_descriptor.md §What is authenticated](../../../../sql_aggregate_descriptor.md) |

## B0026

[Lines 188–188](../../../../../src/recovery/sql_aggregate_descriptor.cpp#L188); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
const runtime::weighted::Binding& Descriptor::native_binding() const & { return data().binding; }
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Expose the genuine weighted-shape/native binding identity retained by the descriptor. |
| inputs / outputs | Returns a const reference to the two native SHA values and multiplicity limit. |
| invariants | This is identity evidence from a real native binding, not an editable plan authority. |
| ownership | Borrowed reference lasts only while descriptor Data remains alive. |
| failure | Empty descriptor fails with ImageFault::binding. |
| cost | Reference return only. |
| Design | [src/recovery/sql_aggregate_descriptor.cpp](../../../../../src/recovery/sql_aggregate_descriptor.cpp), [include/crown/runtime/weighted.hpp](../../../../../include/crown/runtime/weighted.hpp), [docs/sql_aggregate_descriptor.md §What is authenticated](../../../../sql_aggregate_descriptor.md) |

## B0027

[Lines 189–189](../../../../../src/recovery/sql_aggregate_descriptor.cpp#L189); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
const Options& Descriptor::options() const & { return data().normal; }
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Expose the exact original operational SQL aggregate options. |
| inputs / outputs | Returns the stored runtime Options, including producer arithmetic, source/native/group work, capture and standalone memory values. |
| invariants | Receiving account allocation grants remain the caller’s actual account limit; stored standalone memory numbers do not mint new grants. |
| ownership | Borrowed reference lasts while descriptor Data remains alive. |
| failure | Empty descriptor fails with ImageFault::binding. |
| cost | Reference return only. |
| Design | [src/recovery/sql_aggregate_descriptor.cpp](../../../../../src/recovery/sql_aggregate_descriptor.cpp), [include/crown/runtime/sql_aggregate.hpp](../../../../../include/crown/runtime/sql_aggregate.hpp), [docs/sql_aggregate_descriptor.md §What is authenticated](../../../../sql_aggregate_descriptor.md) |

## B0028

[Lines 190–190](../../../../../src/recovery/sql_aggregate_descriptor.cpp#L190); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
const Hash& Descriptor::sha256() const & { return data().digest; }
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Return the cached SHA256 identity of the complete encoded descriptor frame. |
| inputs / outputs | The hash is computed from the retained exact byte vector during Data construction. |
| invariants | It is a separately selectable root identity input, not proof of root selection or durable publication. |
| ownership | Borrowed reference lasts while Data remains alive. |
| failure | Empty descriptor fails with ImageFault::binding. |
| cost | Reference return; hash work was paid once when Data was built. |
| Design | [src/recovery/sql_aggregate_descriptor.cpp](../../../../../src/recovery/sql_aggregate_descriptor.cpp), [include/crown/recovery/sql_aggregate_descriptor.hpp](../../../../../include/crown/recovery/sql_aggregate_descriptor.hpp), [docs/sql_aggregate_descriptor.md §Wire and bounded parsing](../../../../sql_aggregate_descriptor.md) |

## B0029

[Lines 191–191](../../../../../src/recovery/sql_aggregate_descriptor.cpp#L191); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::string_view Descriptor::bytes() const & { const auto& b=data().bytes;return {b.data(),b.size()}; }
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Borrow exact retained descriptor bytes for a caller’s later frame/root operation. |
| inputs / outputs | Returns a string_view over the account-owned ImageVector without copying. |
| invariants | The byte view is immutable and borrowed; it does not perform file selection, write, fsync, replay or root publication. |
| ownership | Keep a Descriptor copy alive for the entire view use; shared Data may outlive any one handle if another copy exists. |
| failure | Empty descriptor fails with ImageFault::binding. |
| cost | O(1), no allocation or byte traversal. |
| Design | [src/recovery/sql_aggregate_descriptor.cpp](../../../../../src/recovery/sql_aggregate_descriptor.cpp), [include/crown/recovery/sql_aggregate_descriptor.hpp](../../../../../include/crown/recovery/sql_aggregate_descriptor.hpp), [docs/sql_aggregate_descriptor.md §Ownership, failure and cost](../../../../sql_aggregate_descriptor.md) |

## B0030

[Lines 192–192](../../../../../src/recovery/sql_aggregate_descriptor.cpp#L192); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L192-L192:sha256:92582b45ad46706cdfae3684126917692713a5a92eff88bf2e3bcc42f5a8da44
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Closes the namespace crown::recovery::sql_aggregate at this source boundary; this is a lexical delimiter, not an operation. |
| inputs / outputs | No runtime input or output. Declarations following the span leave the preceding C++ scope. |
| invariants | The delimiter ends the preceding scope's visibility/linkage region; it adds no validation, publication, ownership transfer, or runtime authority. |
| ownership | The delimiter adds no owner. If it ends a function/block with live automatic objects, their normal destructors release those objects; namespace and type-definition closes change no existing object's lifetime. |
| failure | No explicit failure translation or catch is added. If a function/block exit destroys automatic objects, exception behavior follows those destructors; namespace/type closes have no runtime failure path. |
| cost | The delimiter adds no algorithmic work. A function/block exit can run existing automatic-object destructors and cleanup; namespace/type closes have no runtime cost. |
| Design | [src/recovery/sql_aggregate_descriptor.cpp](../../../../../src/recovery/sql_aggregate_descriptor.cpp), [docs/code_specs/files/src/recovery/sql_aggregate_descriptor.cpp.md](sql_aggregate_descriptor.cpp.md), [docs/sql_aggregate_descriptor.md](../../../../sql_aggregate_descriptor.md), [docs/sql_aggregate_runtime.md](../../../../sql_aggregate_runtime.md) |
