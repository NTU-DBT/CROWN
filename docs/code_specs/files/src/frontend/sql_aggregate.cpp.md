# `src/frontend/sql_aggregate.cpp` — block usage map

[Source](../../../../../src/frontend/sql_aggregate.cpp) · [Source index](../../../README.md) · [Subsystem contracts](../../../subsystem_contracts.md) · [Reviewed primitives](../../../primitives.md)

Derive admitted source/kernel SQL through genuine binders, preserving physical grouping identity and checked foreign-AST lifetimes.

Snapshot SHA-256: `822c83582685b6388a809e2a2ce3dcd81d66f5e8c2ac438e36f42b3b3afda2d7`. 466 lines partitioned into 53 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [frontend](../../../subsystem_contracts.md#frontend). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/sql_support.md](../../../../sql_support.md), [docs/sql_parser.md](../../../../sql_parser.md), [docs/sql_binding.md](../../../../sql_binding.md), [docs/sql_normalization.md](../../../../sql_normalization.md), [docs/sql_admission.md](../../../../sql_admission.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–21](../../../../../src/frontend/sql_aggregate.cpp#L1) | Imports dependencies; declares namespace scope; declares aliases; declares types or opens a type body; declares callable signatures; declares values/defaults or compile-time conditions. | guard static_assert(PG_VERSION_NUM == 180006, "composed SQL AST requires the pinned PostgreSQL 18.6 contr…; growth new · [reviewed contract](#b0001) |
| [B0002 · 22–25](../../../../../src/frontend/sql_aggregate.cpp#L22) | Callable definition: template&lt;class T&gt; auto allocator(const resource::MemoryAccount& account) | calls ; returns resource::MemoryAllocator&lt;T&gt;(account, resource::MemoryPurpose::immutable_metadata, · [reviewed contract](#b0002) |
| [B0003 · 26–26](../../../../../src/frontend/sql_aggregate.cpp#L26) | Callable definition: \[\[noreturn\]\] void fail(const char* code, const char* message) | calls Error · [reviewed contract](#b0003) |
| [B0004 · 27–27](../../../../../src/frontend/sql_aggregate.cpp#L27) | Callable definition: template&lt;class T&gt; T* checked(T* value) | calls ; returns value · [reviewed contract](#b0004) |
| [B0005 · 28–28](../../../../../src/frontend/sql_aggregate.cpp#L28) | Callable definition: std::string_view text(upb_StringView value) | calls ; returns {value.data, value.size} · [reviewed contract](#b0005) |
| [B0006 · 29–31](../../../../../src/frontend/sql_aggregate.cpp#L29) | Explanatory comments or spacing. | source comment (unverified): // Native parser/deparser and upb storage are cold workspace, matching existing · [reviewed contract](#b0006) |
| [B0007 · 32–49](../../../../../src/frontend/sql_aggregate.cpp#L32) | Type/record definition: struct ProtoOwner | guard void require() const {; source comment (unverified): // Native parser/deparser and upb storage are cold workspace, matching existing · [reviewed contract](#b0007) |
| [B0008 · 50–56](../../../../../src/frontend/sql_aggregate.cpp#L50) | Type/record definition: struct Arena |  · [reviewed contract](#b0008) |
| [B0009 · 57–65](../../../../../src/frontend/sql_aggregate.cpp#L57) | Type/record definition: struct DeparseOwner |  · [reviewed contract](#b0009) |
| [B0010 · 66–71](../../../../../src/frontend/sql_aggregate.cpp#L66) | Callable definition: BindingDiagnostic derived(BindingDiagnostic value, std::string_view stage) | calls std::string, reset; returns value; source comment (unverified): // Derived SQL locations are not byte positions in the user's original SQL. · [reviewed contract](#b0010) |
| [B0011 · 72–75](../../../../../src/frontend/sql_aggregate.cpp#L72) | Callable definition: io::Json type_image(const SqlType& type) | calls io::Json::array; returns {{@ , static_cast&lt;int&gt;(type.kind)}, {@ , type.nullable}, · [reviewed contract](#b0011) |
| [B0012 · 76–79](../../../../../src/frontend/sql_aggregate.cpp#L76) | Callable definition: std::string cbor(const io::Json& value) | calls io::Json::to_cbor, data, size; returns {reinterpret_cast&lt;const char*&gt;(bytes.data()), bytes.size()} · [reviewed contract](#b0012) |
| [B0013 · 80–81](../../../../../src/frontend/sql_aggregate.cpp#L80) | Explanatory comments or spacing. | source comment (unverified): // SQL grouping identity is the genuine binder's physical occurrence/column, · [reviewed contract](#b0013) |
| [B0014 · 82–87](../../../../../src/frontend/sql_aggregate.cpp#L82) | Type/record definition: struct OriginKey | source comment (unverified): // SQL grouping identity is the genuine binder's physical occurrence/column, · [reviewed contract](#b0014) |
| [B0015 · 88–97](../../../../../src/frontend/sql_aggregate.cpp#L88) | Callable definition: OriginKey origin_key(const BoundSql& bound, std::size_t output) | calls at, fail; returns {column-&gt;occurrence, column-&gt;column, expression.type} · [reviewed contract](#b0015) |
| [B0016 · 98–109](../../../../../src/frontend/sql_aggregate.cpp#L98) | Callable definition: ScalarType physical_type(SqlKind kind) | calls fail; returns ScalarType::int64; ScalarType::string · [reviewed contract](#b0016) |
| [B0017 · 110–111](../../../../../src/frontend/sql_aggregate.cpp#L110) | Closes surrounding scope/type. | source comment (unverified): // namespace · [reviewed contract](#b0017) |
| [B0018 · 112–125](../../../../../src/frontend/sql_aggregate.cpp#L112) | Type/record definition: struct SqlAggregateProgram::Data |  · [reviewed contract](#b0018) |
| [B0019 · 126–137](../../../../../src/frontend/sql_aggregate.cpp#L126) | declares namespace scope; declares aliases; declares types or opens a type body; declares values/defaults or compile-time conditions. |  · [reviewed contract](#b0019) |
| [B0020 · 138–142](../../../../../src/frontend/sql_aggregate.cpp#L138) | Callable definition: void charge(std::uint64_t amount = 1) | calls fail · [reviewed contract](#b0020) |
| [B0021 · 143–151](../../../../../src/frontend/sql_aggregate.cpp#L143) | Callable definition: void keys(const Json& node, std::initializer_list&lt;std::string_view&gt; allowed) | calls charge, is_object, fail, items; 1 loop sites · [reviewed contract](#b0021) |
| [B0022 · 152–170](../../../../../src/frontend/sql_aggregate.cpp#L152) | Callable definition: void preflight() | calls charge, size, at, contains; 1 loop sites · [reviewed contract](#b0022) |
| [B0023 · 171–179](../../../../../src/frontend/sql_aggregate.cpp#L171) | Callable definition: pg_query_SelectStmt* select(pg_query_ParseResult* tree) | calls pg_query_ParseResult_mutable_stmts, pg_query_ParseResult_version, fail, pg_query_RawStmt_mutable_stmt; returns checked(pg_query_Node_mutable_select_stmt(node, arena_.value)) · [reviewed contract](#b0023) |
| [B0024 · 180–184](../../../../../src/frontend/sql_aggregate.cpp#L180) | Callable definition: upb_StringView own_text(std::string_view value) | calls charge, size, checked, upb_Arena_Malloc; returns upb_StringView_FromDataAndSize(bytes, value.size()) · [reviewed contract](#b0024) |
| [B0025 · 185–193](../../../../../src/frontend/sql_aggregate.cpp#L185) | Callable definition: pg_query_ParseResult* decode(PgQueryProtobuf wire) | calls checked, pg_query_ParseResult_new, upb_Decode, fail; returns tree · [reviewed contract](#b0025) |
| [B0026 · 194–204](../../../../../src/frontend/sql_aggregate.cpp#L194) | Callable definition: void reference(pg_query_Node* node) | calls pg_query_Node_column_ref, pg_query_ColumnRef_fields, fail, pg_query_Node_node_case; growth push_back; 1 loop sites · [reviewed contract](#b0026) |
| [B0027 · 205–221](../../../../../src/frontend/sql_aggregate.cpp#L205) | Callable definition: void argument(pg_query_Node* node, std::size_t depth = 0) | calls charge, fail, pg_query_Node_node_case, reference · [reviewed contract](#b0027) |
| [B0028 · 222–227](../../../../../src/frontend/sql_aggregate.cpp#L222) | Callable definition: std::string column_name(const pg_query_Node* node) | calls pg_query_ColumnRef_fields, pg_query_Node_column_ref, pg_query_Node_node_case, fail; returns std::string(text(pg_query_String_sval(pg_query_Node_string(fields\[size - 1\])))) · [reviewed contract](#b0028) |
| [B0029 · 228–259](../../../../../src/frontend/sql_aggregate.cpp#L228) | Callable definition: void collect(pg_query_SelectStmt* kernel) | calls pg_query_SelectStmt_mutable_group_clause, charge, pg_query_Node_node_case, fail; 3 loop sites; source comment (unverified): // Freeze original default names before cN remapping changes column text. · [reviewed contract](#b0029) |
| [B0030 · 260–276](../../../../../src/frontend/sql_aggregate.cpp#L260) | Callable definition: std::string deparse(pg_query_ParseResult* tree) | calls charge, upb_Encode, fail, owner; returns std::string(owner.value.query, length) · [reviewed contract](#b0030) |
| [B0031 · 277–287](../../../../../src/frontend/sql_aggregate.cpp#L277) | Callable definition: void source_projection(pg_query_SelectStmt* source) | calls pg_query_SelectStmt_clear_target_list, pg_query_SelectStmt_clear_group_clause, size, charge; 1 loop sites; source comment (unverified): // Same-arena leaf borrow ends at source deparse. The source SQL/factory · [reviewed contract](#b0031) |
| [B0032 · 288–294](../../../../../src/frontend/sql_aggregate.cpp#L288) | Callable definition: void remap(pg_query_Node* node, std::size_t column) | calls charge, checked, pg_query_Node_mutable_column_ref, pg_query_ColumnRef_resize_fields · [reviewed contract](#b0032) |
| [B0033 · 295–301](../../../../../src/frontend/sql_aggregate.cpp#L295) | Callable definition: void kernel_source(pg_query_SelectStmt* kernel) | calls pg_query_SelectStmt_clear_where_clause, pg_query_SelectStmt_clear_from_clause, checked, pg_query_SelectStmt_add_from_clause · [reviewed contract](#b0033) |
| [B0034 · 302–305](../../../../../src/frontend/sql_aggregate.cpp#L302) | Callable definition: public: SqlAggregateCompiler(const resource::MemoryAccount& account, const SqlSyntax& original, const Catalog& catalog, const Sql… | calls account_, original_, catalog_, options_ · [reviewed contract](#b0034) |
| [B0035 · 306–415](../../../../../src/frontend/sql_aggregate.cpp#L306) | Callable definition: SqlAggregateBindResult run() | calls preflight, native, c_str, require; guard preflight(); ProtoOwner native(original_.source.c_str()); native.require();; returns derived(*diagnostic, @ ); derived(*diagnostic, @ ); growth copy_of, emplace, make_accounted_shared, push_back; 5 loop sites; source comment (unverified): // Independent checked wire decodes avoid this pin's unsafe DeepClone/Copy. · [reviewed contract](#b0035) |
| [B0036 · 416–418](../../../../../src/frontend/sql_aggregate.cpp#L416) | Closes surrounding scope/type. | source comment (unverified): // namespace detail · [reviewed contract](#b0036) |
| [B0037 · 419–435](../../../../../src/frontend/sql_aggregate.cpp#L419) | Callable definition: SqlAggregateProgram SqlAggregateProgram::freeze(const resource::MemoryAccount& account, const SqlAggregateProgram& source) | calls resource::MemoryFailure, data, statistics, resource::AccountedText::copy_of; returns source; SqlAggregateProgram(std::move(out)); growth copy_of, make_accounted_shared · [reviewed contract](#b0037) |
| [B0038 · 436–436](../../../../../src/frontend/sql_aggregate.cpp#L436) | Explanatory comments or spacing. |  |
| [B0039 · 437–440](../../../../../src/frontend/sql_aggregate.cpp#L437) | Callable definition: const SqlAggregateProgram::Data& SqlAggregateProgram::data() const | calls fail; returns *data_ · [reviewed contract](#b0039) |
| [B0040 · 441–441](../../../../../src/frontend/sql_aggregate.cpp#L441) | Callable definition: std::string_view SqlAggregateProgram::original_sql() const & | calls data, view; returns data().original.view() · [reviewed contract](#b0040) |
| [B0041 · 442–442](../../../../../src/frontend/sql_aggregate.cpp#L442) | Callable definition: const SqlRowsProgram& SqlAggregateProgram::source_program() const & | calls data; returns data().source · [reviewed contract](#b0041) |
| [B0042 · 443–443](../../../../../src/frontend/sql_aggregate.cpp#L443) | Callable definition: const AggregateProgram& SqlAggregateProgram::kernel_program() const & | calls data; returns data().kernel · [reviewed contract](#b0042) |
| [B0043 · 444–444](../../../../../src/frontend/sql_aggregate.cpp#L444) | Callable definition: std::size_t SqlAggregateProgram::native_fields() const | calls data; returns data().native_fields · [reviewed contract](#b0043) |
| [B0044 · 445–445](../../../../../src/frontend/sql_aggregate.cpp#L445) | Callable definition: std::span&lt;const SqlAggregateInput&gt; SqlAggregateProgram::inputs() const & | calls data; returns data().inputs · [reviewed contract](#b0044) |
| [B0045 · 446–446](../../../../../src/frontend/sql_aggregate.cpp#L446) | Callable definition: std::span&lt;const std::size_t&gt; SqlAggregateProgram::reference_columns() const & | calls data; returns data().reference_columns · [reviewed contract](#b0045) |
| [B0046 · 447–447](../../../../../src/frontend/sql_aggregate.cpp#L447) | Callable definition: const SqlAggregateIdentity& SqlAggregateProgram::identity() const & | calls data; returns data().identity · [reviewed contract](#b0046) |
| [B0047 · 448–448](../../../../../src/frontend/sql_aggregate.cpp#L448) | Callable definition: std::string_view SqlAggregateProgram::binding_image() const & | calls data, view; returns data().binding.view() · [reviewed contract](#b0047) |
| [B0048 · 449–449](../../../../../src/frontend/sql_aggregate.cpp#L449) | Callable definition: std::optional&lt;std::uint64_t&gt; SqlAggregateProgram::static_source_weight() const | calls data; returns data().static_weight · [reviewed contract](#b0048) |
| [B0049 · 450–450](../../../../../src/frontend/sql_aggregate.cpp#L450) | Callable definition: SqlAggregateWork SqlAggregateProgram::work() const | calls data; returns data().work · [reviewed contract](#b0049) |
| [B0050 · 451–451](../../../../../src/frontend/sql_aggregate.cpp#L451) | Callable definition: const resource::MemoryAccount& SqlAggregateProgram::account() const & | calls data; returns data().account · [reviewed contract](#b0050) |
| [B0051 · 452–462](../../../../../src/frontend/sql_aggregate.cpp#L452) | Callable definition: SqlAggregateBindResult bind_sql_aggregate_into(const resource::MemoryAccount& account, std::string_view sql, const Catalog& catal… | calls resource::MemoryFailure, parse_sql, detail::SqlAggregateCompiler, run; returns BindingDiagnostic{@ , *diagnostic}; detail::SqlAggregateCompiler(account, std::get&lt;SqlSyntax&gt;(parse… · [reviewed contract](#b0051) |
| [B0052 · 463–465](../../../../../src/frontend/sql_aggregate.cpp#L463) | Callable definition: SqlAggregateBindResult bind_sql_aggregate(std::string_view sql, const Catalog& catalog, const SqlAggregateBindOptions& options) | calls bind_sql_aggregate_into, resource::MemoryAccount::create; returns bind_sql_aggregate_into(resource::MemoryAccount::create(options.memory_limit_bytes), sql, catalog, … · [reviewed contract](#b0052) |
| [B0053 · 466–466](../../../../../src/frontend/sql_aggregate.cpp#L466) | Closes surrounding scope/type. | source comment (unverified): // namespace crown::frontend · [reviewed contract](#b0053) |

## B0001

[Lines 1–21](../../../../../src/frontend/sql_aggregate.cpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
#include "crown/frontend/sql_aggregate.hpp"
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Version the repaired origin-preserving compiler binding as family 2. |
| inputs / outputs | Existing actual frontend/parser/ownership/digest/pg/upb imports and family/archive constants. |
| invariants | Source/kernel/decode remain actual factory products; V1 and V2 are not silently recovery-equivalent. |
| ownership | Imports/constants retain no native input or runtime owner. |
| failure | A type, compile, or link error prevents the factory; parent V2 private and maintained Debug/SAN builds passed. Native malloc-failure coverage remains untested. |
| cost | No runtime work from declarations/version constants. |
| Design | [build/verification/w06-sql-aggregate-compiler-repair-v2/design.md](../../../../../build/verification/w06-sql-aggregate-compiler-repair-v2/design.md), [build/verification/w06-sql-aggregate-compiler-repair-v2/oom-contract.md](../../../../../build/verification/w06-sql-aggregate-compiler-repair-v2/oom-contract.md), [build/verification/w06-sql-aggregate-compiler-repair-v2/receiving-findings.md](../../../../../build/verification/w06-sql-aggregate-compiler-repair-v2/receiving-findings.md), [build/verification/w06-sql-aggregate-compiler-repair-v2/private-contribution-port.md](../../../../../build/verification/w06-sql-aggregate-compiler-repair-v2/private-contribution-port.md), Refactor.md:1325-1333, [docs/sql_aggregate_binding.md §Group identity and nullable decoding](../../../../sql_aggregate_binding.md), [docs/sql_aggregate_binding.md §Foreign AST ownership and costs](../../../../sql_aggregate_binding.md), [docs/sql_aggregate_binding.md §Scope and identity](../../../../sql_aggregate_binding.md), [include/crown/frontend/sql_rows.hpp](../../../../../include/crown/frontend/sql_rows.hpp), [include/crown/frontend/aggregate.hpp](../../../../../include/crown/frontend/aggregate.hpp), [include/crown/frontend/bind.hpp](../../../../../include/crown/frontend/bind.hpp), [src/frontend/bind.cpp](../../../../../src/frontend/bind.cpp), [src/frontend/sql_rows.cpp](../../../../../src/frontend/sql_rows.cpp), [src/frontend/aggregate.cpp](../../../../../src/frontend/aggregate.cpp), [src/frontend/parser.cpp](../../../../../src/frontend/parser.cpp), [src/frontend/parser_detail.hpp](../../../../../src/frontend/parser_detail.hpp), [include/crown/resource/allocator.hpp](../../../../../include/crown/resource/allocator.hpp), [include/crown/resource/ownership.hpp](../../../../../include/crown/resource/ownership.hpp), [include/crown/resource/text.hpp](../../../../../include/crown/resource/text.hpp) |

## B0002

[Lines 22–25](../../../../../src/frontend/sql_aggregate.cpp#L22); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
template<class T> auto allocator(const resource::MemoryAccount& account) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Create immutable-metadata allocators over the original receiver. |
| inputs / outputs | MemoryAccount enters; typed MemoryAllocator with immutable_metadata purpose/attribution leaves. |
| invariants | No fresh byte allowance; every retained nested array receives this allocator explicitly. |
| ownership | Allocator retains the supplied controller. |
| failure | Invalid account/contract failures propagate during private construction. |
| cost | Constant adapter construction. |
| Design | [build/verification/w06-sql-aggregate-compiler-repair-v2/design.md](../../../../../build/verification/w06-sql-aggregate-compiler-repair-v2/design.md), [build/verification/w06-sql-aggregate-compiler-repair-v2/private-contribution-port.md](../../../../../build/verification/w06-sql-aggregate-compiler-repair-v2/private-contribution-port.md), [build/verification/w06-contract-assessment-v1/assessment.md](../../../../../build/verification/w06-contract-assessment-v1/assessment.md), Refactor.md:1317-1327, [include/crown/frontend/sql_rows.hpp](../../../../../include/crown/frontend/sql_rows.hpp), [include/crown/frontend/aggregate.hpp](../../../../../include/crown/frontend/aggregate.hpp), [src/frontend/sql_rows.cpp](../../../../../src/frontend/sql_rows.cpp), [src/frontend/aggregate.cpp](../../../../../src/frontend/aggregate.cpp), [include/crown/resource/ownership.hpp](../../../../../include/crown/resource/ownership.hpp), [include/crown/resource/allocator.hpp](../../../../../include/crown/resource/allocator.hpp), [include/crown/resource/text.hpp](../../../../../include/crown/resource/text.hpp), Refactor.md:1325-1333, [docs/sql_aggregate_binding.md §Group identity and nullable decoding](../../../../sql_aggregate_binding.md), [docs/sql_aggregate_binding.md §Foreign AST ownership and costs](../../../../sql_aggregate_binding.md), [docs/sql_aggregate_binding.md §Scope and identity](../../../../sql_aggregate_binding.md), [include/crown/frontend/bind.hpp](../../../../../include/crown/frontend/bind.hpp), [src/frontend/bind.cpp](../../../../../src/frontend/bind.cpp), [src/frontend/parser.cpp](../../../../../src/frontend/parser.cpp), [src/frontend/parser_detail.hpp](../../../../../src/frontend/parser_detail.hpp) |

## B0003

[Lines 26–26](../../../../../src/frontend/sql_aggregate.cpp#L26); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
[[noreturn]] void fail(const char* code, const char* message) { throw Error(code, message); }
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Raise a narrow semantic or contract Error before exposing a composition. |
| inputs / outputs | Stable code and message enter; Error is thrown. |
| invariants | No source/runtime state or durable output is mutated. |
| ownership | Diagnostic allocation is ordinary exception work. |
| failure | Public boundary converts semantic Error to BindingDiagnostic and rethrows parser_contract. |
| cost | Cold exceptional path. |
| Design | [build/verification/w06-sql-aggregate-compiler-repair-v2/design.md](../../../../../build/verification/w06-sql-aggregate-compiler-repair-v2/design.md), [build/verification/w06-sql-aggregate-compiler-repair-v2/private-contribution-port.md](../../../../../build/verification/w06-sql-aggregate-compiler-repair-v2/private-contribution-port.md), [build/verification/w06-contract-assessment-v1/assessment.md](../../../../../build/verification/w06-contract-assessment-v1/assessment.md), Refactor.md:1317-1327, Refactor.md:1325-1333, [docs/sql_aggregate_binding.md §Group identity and nullable decoding](../../../../sql_aggregate_binding.md), [docs/sql_aggregate_binding.md §Foreign AST ownership and costs](../../../../sql_aggregate_binding.md), [docs/sql_aggregate_binding.md §Scope and identity](../../../../sql_aggregate_binding.md), [include/crown/frontend/sql_rows.hpp](../../../../../include/crown/frontend/sql_rows.hpp), [include/crown/frontend/aggregate.hpp](../../../../../include/crown/frontend/aggregate.hpp), [include/crown/frontend/bind.hpp](../../../../../include/crown/frontend/bind.hpp), [src/frontend/bind.cpp](../../../../../src/frontend/bind.cpp), [src/frontend/sql_rows.cpp](../../../../../src/frontend/sql_rows.cpp), [src/frontend/aggregate.cpp](../../../../../src/frontend/aggregate.cpp), [src/frontend/parser.cpp](../../../../../src/frontend/parser.cpp), [src/frontend/parser_detail.hpp](../../../../../src/frontend/parser_detail.hpp), [include/crown/resource/allocator.hpp](../../../../../include/crown/resource/allocator.hpp), [include/crown/resource/ownership.hpp](../../../../../include/crown/resource/ownership.hpp), [include/crown/resource/text.hpp](../../../../../include/crown/resource/text.hpp) |

## B0004

[Lines 27–27](../../../../../src/frontend/sql_aggregate.cpp#L27); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
template<class T> T* checked(T* value) { if (!value) throw std::bad_alloc{}; return value; }
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Reject a failed upstream allocation without passing null into mutable upb operations. |
| inputs / outputs | Typed pointer enters; same nonnull pointer returns. |
| invariants | Used only for APIs whose null result means allocation failure; direct wire status has separate handling. |
| ownership | No ownership transfer; outer RAII owners remain active. |
| failure | std::bad_alloc propagates before program publication. |
| cost | Constant pointer check. |
| Design | [build/verification/w06-sql-aggregate-compiler-repair-v2/design.md](../../../../../build/verification/w06-sql-aggregate-compiler-repair-v2/design.md), [build/verification/w06-sql-aggregate-compiler-repair-v2/private-contribution-port.md](../../../../../build/verification/w06-sql-aggregate-compiler-repair-v2/private-contribution-port.md), [build/verification/w06-contract-assessment-v1/assessment.md](../../../../../build/verification/w06-contract-assessment-v1/assessment.md), Refactor.md:1317-1327, [build/verification/w06-sql-aggregate-compiler-repair-v2/source/pinned-libpg-query/pg_query.h](../../../../../build/verification/w06-sql-aggregate-compiler-repair-v2/source/pinned-libpg-query/pg_query.h), [build/verification/w06-sql-aggregate-compiler-repair-v2/source/pinned-libpg-query/protobuf/pg_query.upb.h](../../../../../build/verification/w06-sql-aggregate-compiler-repair-v2/source/pinned-libpg-query/protobuf/pg_query.upb.h), [build/verification/w06-sql-aggregate-compiler-repair-v2/source/pinned-libpg-query/vendor/upb/upb/generated_code_support.h](../../../../../build/verification/w06-sql-aggregate-compiler-repair-v2/source/pinned-libpg-query/vendor/upb/upb/generated_code_support.h), [build/verification/w06-sql-aggregate-compiler-repair-v2/source/pinned-libpg-query/vendor/upb/upb.c](../../../../../build/verification/w06-sql-aggregate-compiler-repair-v2/source/pinned-libpg-query/vendor/upb/upb.c), [build/verification/w06-sql-aggregate-compiler-repair-v2/source/pinned-libpg-query/Makefile](../../../../../build/verification/w06-sql-aggregate-compiler-repair-v2/source/pinned-libpg-query/Makefile), Refactor.md:1325-1333, [docs/sql_aggregate_binding.md §Group identity and nullable decoding](../../../../sql_aggregate_binding.md), [docs/sql_aggregate_binding.md §Foreign AST ownership and costs](../../../../sql_aggregate_binding.md), [docs/sql_aggregate_binding.md §Scope and identity](../../../../sql_aggregate_binding.md), [include/crown/frontend/sql_rows.hpp](../../../../../include/crown/frontend/sql_rows.hpp), [include/crown/frontend/aggregate.hpp](../../../../../include/crown/frontend/aggregate.hpp), [include/crown/frontend/bind.hpp](../../../../../include/crown/frontend/bind.hpp), [src/frontend/bind.cpp](../../../../../src/frontend/bind.cpp), [src/frontend/sql_rows.cpp](../../../../../src/frontend/sql_rows.cpp), [src/frontend/aggregate.cpp](../../../../../src/frontend/aggregate.cpp), [src/frontend/parser.cpp](../../../../../src/frontend/parser.cpp), [src/frontend/parser_detail.hpp](../../../../../src/frontend/parser_detail.hpp), [include/crown/resource/allocator.hpp](../../../../../include/crown/resource/allocator.hpp), [include/crown/resource/ownership.hpp](../../../../../include/crown/resource/ownership.hpp), [include/crown/resource/text.hpp](../../../../../include/crown/resource/text.hpp) |

## B0005

[Lines 28–28](../../../../../src/frontend/sql_aggregate.cpp#L28); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::string_view text(upb_StringView value) { return {value.data, value.size}; }
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Borrow a string view from a live upb StringView. |
| inputs / outputs | Data pointer and length become std::string_view. |
| invariants | Caller must keep native/arena backing alive during use. |
| ownership | No copy, retention or account change. |
| failure | No validation/ownership is implied. |
| cost | Constant. |
| Design | [build/verification/w06-sql-aggregate-compiler-repair-v2/design.md](../../../../../build/verification/w06-sql-aggregate-compiler-repair-v2/design.md), [build/verification/w06-sql-aggregate-compiler-repair-v2/private-contribution-port.md](../../../../../build/verification/w06-sql-aggregate-compiler-repair-v2/private-contribution-port.md), [build/verification/w06-contract-assessment-v1/assessment.md](../../../../../build/verification/w06-contract-assessment-v1/assessment.md), Refactor.md:1317-1327, [build/verification/w06-sql-aggregate-compiler-repair-v2/source/pinned-libpg-query/pg_query.h](../../../../../build/verification/w06-sql-aggregate-compiler-repair-v2/source/pinned-libpg-query/pg_query.h), [build/verification/w06-sql-aggregate-compiler-repair-v2/source/pinned-libpg-query/protobuf/pg_query.upb.h](../../../../../build/verification/w06-sql-aggregate-compiler-repair-v2/source/pinned-libpg-query/protobuf/pg_query.upb.h), [build/verification/w06-sql-aggregate-compiler-repair-v2/source/pinned-libpg-query/vendor/upb/upb/generated_code_support.h](../../../../../build/verification/w06-sql-aggregate-compiler-repair-v2/source/pinned-libpg-query/vendor/upb/upb/generated_code_support.h), [build/verification/w06-sql-aggregate-compiler-repair-v2/source/pinned-libpg-query/vendor/upb/upb.c](../../../../../build/verification/w06-sql-aggregate-compiler-repair-v2/source/pinned-libpg-query/vendor/upb/upb.c), [build/verification/w06-sql-aggregate-compiler-repair-v2/source/pinned-libpg-query/Makefile](../../../../../build/verification/w06-sql-aggregate-compiler-repair-v2/source/pinned-libpg-query/Makefile), Refactor.md:1325-1333, [docs/sql_aggregate_binding.md §Group identity and nullable decoding](../../../../sql_aggregate_binding.md), [docs/sql_aggregate_binding.md §Foreign AST ownership and costs](../../../../sql_aggregate_binding.md), [docs/sql_aggregate_binding.md §Scope and identity](../../../../sql_aggregate_binding.md), [include/crown/frontend/sql_rows.hpp](../../../../../include/crown/frontend/sql_rows.hpp), [include/crown/frontend/aggregate.hpp](../../../../../include/crown/frontend/aggregate.hpp), [include/crown/frontend/bind.hpp](../../../../../include/crown/frontend/bind.hpp), [src/frontend/bind.cpp](../../../../../src/frontend/bind.cpp), [src/frontend/sql_rows.cpp](../../../../../src/frontend/sql_rows.cpp), [src/frontend/aggregate.cpp](../../../../../src/frontend/aggregate.cpp), [src/frontend/parser.cpp](../../../../../src/frontend/parser.cpp), [src/frontend/parser_detail.hpp](../../../../../src/frontend/parser_detail.hpp), [include/crown/resource/allocator.hpp](../../../../../include/crown/resource/allocator.hpp), [include/crown/resource/ownership.hpp](../../../../../include/crown/resource/ownership.hpp), [include/crown/resource/text.hpp](../../../../../include/crown/resource/text.hpp) |

## B0006

[Lines 29–31](../../../../../src/frontend/sql_aggregate.cpp#L29); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text

// Native parser/deparser and upb storage are cold workspace, matching existing
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Document cold native parser/deparser/upb lifetime and allocation boundaries. |
| inputs / outputs | Imports, declarations, comments, closure or spacing in the exact stated block. |
| invariants | No SQL admission, plan authority, output publication or execution claim from this scaffolding. |
| ownership | No new executable ownership beyond declarations explicitly described in surrounding cards. |
| failure | No runtime failure is handled by these lines. |
| cost | No runtime work from comments/spacing/declarations. |
| Design | [build/verification/w06-sql-aggregate-compiler-repair-v2/design.md](../../../../../build/verification/w06-sql-aggregate-compiler-repair-v2/design.md), [build/verification/w06-sql-aggregate-compiler-repair-v2/private-contribution-port.md](../../../../../build/verification/w06-sql-aggregate-compiler-repair-v2/private-contribution-port.md), [build/verification/w06-contract-assessment-v1/assessment.md](../../../../../build/verification/w06-contract-assessment-v1/assessment.md), Refactor.md:1317-1327, Refactor.md:1325-1333, [docs/sql_aggregate_binding.md §Group identity and nullable decoding](../../../../sql_aggregate_binding.md), [docs/sql_aggregate_binding.md §Foreign AST ownership and costs](../../../../sql_aggregate_binding.md), [docs/sql_aggregate_binding.md §Scope and identity](../../../../sql_aggregate_binding.md), [include/crown/frontend/sql_rows.hpp](../../../../../include/crown/frontend/sql_rows.hpp), [include/crown/frontend/aggregate.hpp](../../../../../include/crown/frontend/aggregate.hpp), [include/crown/frontend/bind.hpp](../../../../../include/crown/frontend/bind.hpp), [src/frontend/bind.cpp](../../../../../src/frontend/bind.cpp), [src/frontend/sql_rows.cpp](../../../../../src/frontend/sql_rows.cpp), [src/frontend/aggregate.cpp](../../../../../src/frontend/aggregate.cpp), [src/frontend/parser.cpp](../../../../../src/frontend/parser.cpp), [src/frontend/parser_detail.hpp](../../../../../src/frontend/parser_detail.hpp), [include/crown/resource/allocator.hpp](../../../../../include/crown/resource/allocator.hpp), [include/crown/resource/ownership.hpp](../../../../../include/crown/resource/ownership.hpp), [include/crown/resource/text.hpp](../../../../../include/crown/resource/text.hpp) |

## B0007

[Lines 32–49](../../../../../src/frontend/sql_aggregate.cpp#L32); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct ProtoOwner {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Own authenticated original protobuf parse output and check its result after RAII is established. |
| inputs / outputs | Owned original NUL-terminated SQL enters pg_query_parse_protobuf under the shared parser gate; require checks errors/tree presence. |
| invariants | Same original bytes already passed parse_sql; unexpected semantic parse disagreement is parser_contract; memory/depth errors are resource_limit. |
| ownership | Destructor frees native error/pbuf/stderr on every later throw; copies are disabled; no parser pointer escapes. |
| failure | Result checks occur after construction so fallible error handling cannot leak the native buffer. |
| cost | One additional cold upstream parse plus result allocation/free; no receiver-funded native workspace claim. |
| Design | [build/verification/w06-sql-aggregate-compiler-repair-v2/design.md](../../../../../build/verification/w06-sql-aggregate-compiler-repair-v2/design.md), [build/verification/w06-sql-aggregate-compiler-repair-v2/private-contribution-port.md](../../../../../build/verification/w06-sql-aggregate-compiler-repair-v2/private-contribution-port.md), [build/verification/w06-contract-assessment-v1/assessment.md](../../../../../build/verification/w06-contract-assessment-v1/assessment.md), Refactor.md:1317-1327, [build/verification/w06-sql-aggregate-compiler-repair-v2/source/pinned-libpg-query/pg_query.h](../../../../../build/verification/w06-sql-aggregate-compiler-repair-v2/source/pinned-libpg-query/pg_query.h), [build/verification/w06-sql-aggregate-compiler-repair-v2/source/pinned-libpg-query/protobuf/pg_query.upb.h](../../../../../build/verification/w06-sql-aggregate-compiler-repair-v2/source/pinned-libpg-query/protobuf/pg_query.upb.h), [build/verification/w06-sql-aggregate-compiler-repair-v2/source/pinned-libpg-query/vendor/upb/upb/generated_code_support.h](../../../../../build/verification/w06-sql-aggregate-compiler-repair-v2/source/pinned-libpg-query/vendor/upb/upb/generated_code_support.h), [build/verification/w06-sql-aggregate-compiler-repair-v2/source/pinned-libpg-query/vendor/upb/upb.c](../../../../../build/verification/w06-sql-aggregate-compiler-repair-v2/source/pinned-libpg-query/vendor/upb/upb.c), [build/verification/w06-sql-aggregate-compiler-repair-v2/source/pinned-libpg-query/Makefile](../../../../../build/verification/w06-sql-aggregate-compiler-repair-v2/source/pinned-libpg-query/Makefile), Refactor.md:1325-1333, [docs/sql_aggregate_binding.md §Group identity and nullable decoding](../../../../sql_aggregate_binding.md), [docs/sql_aggregate_binding.md §Foreign AST ownership and costs](../../../../sql_aggregate_binding.md), [docs/sql_aggregate_binding.md §Scope and identity](../../../../sql_aggregate_binding.md), [include/crown/frontend/sql_rows.hpp](../../../../../include/crown/frontend/sql_rows.hpp), [include/crown/frontend/aggregate.hpp](../../../../../include/crown/frontend/aggregate.hpp), [include/crown/frontend/bind.hpp](../../../../../include/crown/frontend/bind.hpp), [src/frontend/bind.cpp](../../../../../src/frontend/bind.cpp), [src/frontend/sql_rows.cpp](../../../../../src/frontend/sql_rows.cpp), [src/frontend/aggregate.cpp](../../../../../src/frontend/aggregate.cpp), [src/frontend/parser.cpp](../../../../../src/frontend/parser.cpp), [src/frontend/parser_detail.hpp](../../../../../src/frontend/parser_detail.hpp), [include/crown/resource/allocator.hpp](../../../../../include/crown/resource/allocator.hpp), [include/crown/resource/ownership.hpp](../../../../../include/crown/resource/ownership.hpp), [include/crown/resource/text.hpp](../../../../../include/crown/resource/text.hpp) |

## B0008

[Lines 50–56](../../../../../src/frontend/sql_aggregate.cpp#L50); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct Arena {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Own ordinary cold upb storage for two independently decoded mutable trees and synthesized nodes. |
| inputs / outputs | upb_Arena_New creates storage; destructor frees it. |
| invariants | No DeepClone/DeepCopy or fixed/custom production allocator is used; both trees and all leaf borrows share this lifetime. |
| ownership | Noncopyable arena outlives every private AST use. |
| failure | A null upb_Arena_New or covered arena allocation throws std::bad_alloc before a public program. Parent linker-seam receipts denied all 8 Debug and 11 sanitizer allocations in the compiler’s first arena, restored the receiver to controller-only, and retried successfully each time; parser/deparser C malloc and global C++ new are not covered. |
| cost | Actual cold arena allocations/free, not retained receiver accounting. |
| Design | [build/verification/w06-sql-aggregate-compiler-repair-v2/design.md](../../../../../build/verification/w06-sql-aggregate-compiler-repair-v2/design.md), [build/verification/w06-sql-aggregate-compiler-repair-v2/oom-contract.md](../../../../../build/verification/w06-sql-aggregate-compiler-repair-v2/oom-contract.md), [build/verification/w06-sql-aggregate-compiler-repair-v2/receiving-findings.md](../../../../../build/verification/w06-sql-aggregate-compiler-repair-v2/receiving-findings.md), [build/verification/w06-sql-aggregate-compiler-repair-v2/private-contribution-port.md](../../../../../build/verification/w06-sql-aggregate-compiler-repair-v2/private-contribution-port.md), [build/verification/w06-sql-aggregate-compiler-repair-v2/source/pinned-libpg-query/protobuf/pg_query.upb.h](../../../../../build/verification/w06-sql-aggregate-compiler-repair-v2/source/pinned-libpg-query/protobuf/pg_query.upb.h), [build/verification/w06-sql-aggregate-compiler-repair-v2/source/pinned-libpg-query/vendor/upb/upb/generated_code_support.h](../../../../../build/verification/w06-sql-aggregate-compiler-repair-v2/source/pinned-libpg-query/vendor/upb/upb/generated_code_support.h), [build/verification/w06-sql-aggregate-compiler-repair-v2/source/pinned-libpg-query/vendor/upb/upb.c](../../../../../build/verification/w06-sql-aggregate-compiler-repair-v2/source/pinned-libpg-query/vendor/upb/upb.c), Refactor.md:1325-1333, [docs/sql_aggregate_binding.md §Group identity and nullable decoding](../../../../sql_aggregate_binding.md), [docs/sql_aggregate_binding.md §Foreign AST ownership and costs](../../../../sql_aggregate_binding.md), [docs/sql_aggregate_binding.md §Scope and identity](../../../../sql_aggregate_binding.md), [include/crown/frontend/sql_rows.hpp](../../../../../include/crown/frontend/sql_rows.hpp), [include/crown/frontend/aggregate.hpp](../../../../../include/crown/frontend/aggregate.hpp), [include/crown/frontend/bind.hpp](../../../../../include/crown/frontend/bind.hpp), [src/frontend/bind.cpp](../../../../../src/frontend/bind.cpp), [src/frontend/sql_rows.cpp](../../../../../src/frontend/sql_rows.cpp), [src/frontend/aggregate.cpp](../../../../../src/frontend/aggregate.cpp), [src/frontend/parser.cpp](../../../../../src/frontend/parser.cpp), [src/frontend/parser_detail.hpp](../../../../../src/frontend/parser_detail.hpp), [include/crown/resource/allocator.hpp](../../../../../include/crown/resource/allocator.hpp), [include/crown/resource/ownership.hpp](../../../../../include/crown/resource/ownership.hpp), [include/crown/resource/text.hpp](../../../../../include/crown/resource/text.hpp) |

## B0009

[Lines 57–65](../../../../../src/frontend/sql_aggregate.cpp#L57); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct DeparseOwner {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Own one derived AST deparse result from the pinned C API. |
| inputs / outputs | Encoded PgQueryProtobuf enters pg_query_deparse_protobuf under the same parser mutex. |
| invariants | Lock ends before child factories parse again; caller checks native error/query before use. |
| ownership | Destructor frees query/error result on all exits; input bytes remain live in the arena through the call. |
| failure | Native errors remain private for later resource/contract classification. |
| cost | Cold upstream deparse allocation/free, independent of retained receiver memory. |
| Design | [build/verification/w06-sql-aggregate-compiler-repair-v2/design.md](../../../../../build/verification/w06-sql-aggregate-compiler-repair-v2/design.md), [build/verification/w06-sql-aggregate-compiler-repair-v2/private-contribution-port.md](../../../../../build/verification/w06-sql-aggregate-compiler-repair-v2/private-contribution-port.md), [build/verification/w06-contract-assessment-v1/assessment.md](../../../../../build/verification/w06-contract-assessment-v1/assessment.md), Refactor.md:1317-1327, [build/verification/w06-sql-aggregate-compiler-repair-v2/source/pinned-libpg-query/pg_query.h](../../../../../build/verification/w06-sql-aggregate-compiler-repair-v2/source/pinned-libpg-query/pg_query.h), [build/verification/w06-sql-aggregate-compiler-repair-v2/source/pinned-libpg-query/protobuf/pg_query.upb.h](../../../../../build/verification/w06-sql-aggregate-compiler-repair-v2/source/pinned-libpg-query/protobuf/pg_query.upb.h), [build/verification/w06-sql-aggregate-compiler-repair-v2/source/pinned-libpg-query/vendor/upb/upb/generated_code_support.h](../../../../../build/verification/w06-sql-aggregate-compiler-repair-v2/source/pinned-libpg-query/vendor/upb/upb/generated_code_support.h), [build/verification/w06-sql-aggregate-compiler-repair-v2/source/pinned-libpg-query/vendor/upb/upb.c](../../../../../build/verification/w06-sql-aggregate-compiler-repair-v2/source/pinned-libpg-query/vendor/upb/upb.c), [build/verification/w06-sql-aggregate-compiler-repair-v2/source/pinned-libpg-query/Makefile](../../../../../build/verification/w06-sql-aggregate-compiler-repair-v2/source/pinned-libpg-query/Makefile), Refactor.md:1325-1333, [docs/sql_aggregate_binding.md §Group identity and nullable decoding](../../../../sql_aggregate_binding.md), [docs/sql_aggregate_binding.md §Foreign AST ownership and costs](../../../../sql_aggregate_binding.md), [docs/sql_aggregate_binding.md §Scope and identity](../../../../sql_aggregate_binding.md), [include/crown/frontend/sql_rows.hpp](../../../../../include/crown/frontend/sql_rows.hpp), [include/crown/frontend/aggregate.hpp](../../../../../include/crown/frontend/aggregate.hpp), [include/crown/frontend/bind.hpp](../../../../../include/crown/frontend/bind.hpp), [src/frontend/bind.cpp](../../../../../src/frontend/bind.cpp), [src/frontend/sql_rows.cpp](../../../../../src/frontend/sql_rows.cpp), [src/frontend/aggregate.cpp](../../../../../src/frontend/aggregate.cpp), [src/frontend/parser.cpp](../../../../../src/frontend/parser.cpp), [src/frontend/parser_detail.hpp](../../../../../src/frontend/parser_detail.hpp), [include/crown/resource/allocator.hpp](../../../../../include/crown/resource/allocator.hpp), [include/crown/resource/ownership.hpp](../../../../../include/crown/resource/ownership.hpp), [include/crown/resource/text.hpp](../../../../../include/crown/resource/text.hpp) |

## B0010

[Lines 66–71](../../../../../src/frontend/sql_aggregate.cpp#L66); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
BindingDiagnostic derived(BindingDiagnostic value, std::string_view stage) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Identify derived source/kernel diagnostics without reporting misleading original SQL coordinates. |
| inputs / outputs | Actual BindingDiagnostic plus stage prefix; copied diagnostic returns with derived stage and all coordinates reset. |
| invariants | Code/message remain actual child-factory rejection; offsets in rewritten SQL cannot identify original source positions. |
| ownership | Owns diagnostic strings only; no runtime/program changes. |
| failure | Diagnostic string allocation can propagate; no broad catch or retry. |
| cost | Cold diagnostic copy/format only. |
| Design | [build/verification/w06-sql-aggregate-compiler-repair-v2/design.md](../../../../../build/verification/w06-sql-aggregate-compiler-repair-v2/design.md), [build/verification/w06-sql-aggregate-compiler-repair-v2/private-contribution-port.md](../../../../../build/verification/w06-sql-aggregate-compiler-repair-v2/private-contribution-port.md), [build/verification/w06-contract-assessment-v1/assessment.md](../../../../../build/verification/w06-contract-assessment-v1/assessment.md), Refactor.md:1317-1327, [include/crown/frontend/sql_rows.hpp](../../../../../include/crown/frontend/sql_rows.hpp), [include/crown/frontend/aggregate.hpp](../../../../../include/crown/frontend/aggregate.hpp), [src/frontend/sql_rows.cpp](../../../../../src/frontend/sql_rows.cpp), [src/frontend/aggregate.cpp](../../../../../src/frontend/aggregate.cpp), Refactor.md:1325-1333, [docs/sql_aggregate_binding.md §Group identity and nullable decoding](../../../../sql_aggregate_binding.md), [docs/sql_aggregate_binding.md §Foreign AST ownership and costs](../../../../sql_aggregate_binding.md), [docs/sql_aggregate_binding.md §Scope and identity](../../../../sql_aggregate_binding.md), [include/crown/frontend/bind.hpp](../../../../../include/crown/frontend/bind.hpp), [src/frontend/bind.cpp](../../../../../src/frontend/bind.cpp), [src/frontend/parser.cpp](../../../../../src/frontend/parser.cpp), [src/frontend/parser_detail.hpp](../../../../../src/frontend/parser_detail.hpp), [include/crown/resource/allocator.hpp](../../../../../include/crown/resource/allocator.hpp), [include/crown/resource/ownership.hpp](../../../../../include/crown/resource/ownership.hpp), [include/crown/resource/text.hpp](../../../../../include/crown/resource/text.hpp) |

## B0011

[Lines 72–75](../../../../../src/frontend/sql_aggregate.cpp#L72); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
io::Json type_image(const SqlType& type) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Encode complete exact SqlType for binding identity. |
| inputs / outputs | SqlKind, nullable flag and optional decimal precision/scale produce JSON metadata. |
| invariants | NULL and decimal domains are never dropped when canonicalizing/hashing. |
| ownership | Ordinary cold JSON owns its copied scalar metadata. |
| failure | Cold allocation failure propagates before final Data publication. |
| cost | Constant-size type record. |
| Design | [build/verification/w06-sql-aggregate-compiler-repair-v2/design.md](../../../../../build/verification/w06-sql-aggregate-compiler-repair-v2/design.md), [build/verification/w06-sql-aggregate-compiler-repair-v2/private-contribution-port.md](../../../../../build/verification/w06-sql-aggregate-compiler-repair-v2/private-contribution-port.md), [build/verification/w06-contract-assessment-v1/assessment.md](../../../../../build/verification/w06-contract-assessment-v1/assessment.md), Refactor.md:1317-1327, [include/crown/frontend/sql_rows.hpp](../../../../../include/crown/frontend/sql_rows.hpp), [include/crown/frontend/aggregate.hpp](../../../../../include/crown/frontend/aggregate.hpp), [src/frontend/sql_rows.cpp](../../../../../src/frontend/sql_rows.cpp), [src/frontend/aggregate.cpp](../../../../../src/frontend/aggregate.cpp), Refactor.md:1325-1333, [docs/sql_aggregate_binding.md §Group identity and nullable decoding](../../../../sql_aggregate_binding.md), [docs/sql_aggregate_binding.md §Foreign AST ownership and costs](../../../../sql_aggregate_binding.md), [docs/sql_aggregate_binding.md §Scope and identity](../../../../sql_aggregate_binding.md), [include/crown/frontend/bind.hpp](../../../../../include/crown/frontend/bind.hpp), [src/frontend/bind.cpp](../../../../../src/frontend/bind.cpp), [src/frontend/parser.cpp](../../../../../src/frontend/parser.cpp), [src/frontend/parser_detail.hpp](../../../../../src/frontend/parser_detail.hpp), [include/crown/resource/allocator.hpp](../../../../../include/crown/resource/allocator.hpp), [include/crown/resource/ownership.hpp](../../../../../include/crown/resource/ownership.hpp), [include/crown/resource/text.hpp](../../../../../include/crown/resource/text.hpp) |

## B0012

[Lines 76–79](../../../../../src/frontend/sql_aggregate.cpp#L76); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::string cbor(const io::Json& value) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Serialize typed metadata with unambiguous binary framing. |
| inputs / outputs | JSON becomes CBOR bytes and an owning cold string. |
| invariants | Opaque catalog bytes are preserved; this does not authorize executable program deserialization. |
| ownership | Temporary bytes are ordinary cold workspace; retained image is explicitly copied into account later. |
| failure | JSON/ordinary allocation failure propagates without a partial public handle. |
| cost | Linear encoded metadata bytes; temporary CBOR/string overlap is real cold workspace. |
| Design | [build/verification/w06-sql-aggregate-compiler-repair-v2/design.md](../../../../../build/verification/w06-sql-aggregate-compiler-repair-v2/design.md), [build/verification/w06-sql-aggregate-compiler-repair-v2/private-contribution-port.md](../../../../../build/verification/w06-sql-aggregate-compiler-repair-v2/private-contribution-port.md), [build/verification/w06-contract-assessment-v1/assessment.md](../../../../../build/verification/w06-contract-assessment-v1/assessment.md), Refactor.md:1317-1327, [include/crown/frontend/sql_rows.hpp](../../../../../include/crown/frontend/sql_rows.hpp), [include/crown/frontend/aggregate.hpp](../../../../../include/crown/frontend/aggregate.hpp), [src/frontend/sql_rows.cpp](../../../../../src/frontend/sql_rows.cpp), [src/frontend/aggregate.cpp](../../../../../src/frontend/aggregate.cpp), Refactor.md:1325-1333, [docs/sql_aggregate_binding.md §Group identity and nullable decoding](../../../../sql_aggregate_binding.md), [docs/sql_aggregate_binding.md §Foreign AST ownership and costs](../../../../sql_aggregate_binding.md), [docs/sql_aggregate_binding.md §Scope and identity](../../../../sql_aggregate_binding.md), [include/crown/frontend/bind.hpp](../../../../../include/crown/frontend/bind.hpp), [src/frontend/bind.cpp](../../../../../src/frontend/bind.cpp), [src/frontend/parser.cpp](../../../../../src/frontend/parser.cpp), [src/frontend/parser_detail.hpp](../../../../../src/frontend/parser_detail.hpp), [include/crown/resource/allocator.hpp](../../../../../include/crown/resource/allocator.hpp), [include/crown/resource/ownership.hpp](../../../../../include/crown/resource/ownership.hpp), [include/crown/resource/text.hpp](../../../../../include/crown/resource/text.hpp) |

## B0013

[Lines 80–81](../../../../../src/frontend/sql_aggregate.cpp#L80); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
// SQL grouping identity is the genuine binder's physical occurrence/column,
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | State why raw physical origin, not value normalization, determines grouping identity. |
| inputs / outputs | Comment applies to OriginKey and genuine bound expression extraction. |
| invariants | Equality classes, shared constants and equal native values do not prove original SQL grouping equivalence. |
| ownership | No owner or caller DTO is created. |
| failure | Comment alone enforces nothing; actual helper/kernel binding perform checks. |
| cost | No executable work. |
| Design | [build/verification/w06-sql-aggregate-compiler-repair-v2/design.md](../../../../../build/verification/w06-sql-aggregate-compiler-repair-v2/design.md), [build/verification/w06-sql-aggregate-compiler-repair-v2/oom-contract.md](../../../../../build/verification/w06-sql-aggregate-compiler-repair-v2/oom-contract.md), [build/verification/w06-sql-aggregate-compiler-repair-v2/receiving-findings.md](../../../../../build/verification/w06-sql-aggregate-compiler-repair-v2/receiving-findings.md), [build/verification/w06-sql-aggregate-compiler-repair-v2/private-contribution-port.md](../../../../../build/verification/w06-sql-aggregate-compiler-repair-v2/private-contribution-port.md), [include/crown/frontend/bind.hpp](../../../../../include/crown/frontend/bind.hpp), src/frontend/bind.cpp:270-285,396-456,550-574, src/frontend/sql_rows.cpp:438-447,559-568, [src/frontend/aggregate.cpp](../../../../../src/frontend/aggregate.cpp), Refactor.md:1325-1333, [docs/sql_aggregate_binding.md §Group identity and nullable decoding](../../../../sql_aggregate_binding.md), [docs/sql_aggregate_binding.md §Foreign AST ownership and costs](../../../../sql_aggregate_binding.md), [docs/sql_aggregate_binding.md §Scope and identity](../../../../sql_aggregate_binding.md), [include/crown/frontend/sql_rows.hpp](../../../../../include/crown/frontend/sql_rows.hpp), [include/crown/frontend/aggregate.hpp](../../../../../include/crown/frontend/aggregate.hpp), [src/frontend/bind.cpp](../../../../../src/frontend/bind.cpp), [src/frontend/sql_rows.cpp](../../../../../src/frontend/sql_rows.cpp), [src/frontend/parser.cpp](../../../../../src/frontend/parser.cpp), [src/frontend/parser_detail.hpp](../../../../../src/frontend/parser_detail.hpp), [include/crown/resource/allocator.hpp](../../../../../include/crown/resource/allocator.hpp), [include/crown/resource/ownership.hpp](../../../../../include/crown/resource/ownership.hpp), [include/crown/resource/text.hpp](../../../../../include/crown/resource/text.hpp) |

## B0014

[Lines 82–87](../../../../../src/frontend/sql_aggregate.cpp#L82); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct OriginKey {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Order genuine pre-normalization physical column identities with exact SQL type. |
| inputs / outputs | OccurrenceId, ColumnId and full SqlType form OriginKey. |
| invariants | Self-join occurrences stay distinct; repeated aliases of the same physical occurrence/column/type deduplicate. ID wrappers are valid only because the real binder produced them. |
| ownership | Fixed inline cold key; no retained BoundSql or payload data. |
| failure | No normalization union or source decoder equality is consulted. |
| cost | O(log K) fixed-key map comparison per reference; no string payload copies. |
| Design | [build/verification/w06-sql-aggregate-compiler-repair-v2/design.md](../../../../../build/verification/w06-sql-aggregate-compiler-repair-v2/design.md), [build/verification/w06-sql-aggregate-compiler-repair-v2/oom-contract.md](../../../../../build/verification/w06-sql-aggregate-compiler-repair-v2/oom-contract.md), [build/verification/w06-sql-aggregate-compiler-repair-v2/receiving-findings.md](../../../../../build/verification/w06-sql-aggregate-compiler-repair-v2/receiving-findings.md), [build/verification/w06-sql-aggregate-compiler-repair-v2/private-contribution-port.md](../../../../../build/verification/w06-sql-aggregate-compiler-repair-v2/private-contribution-port.md), [include/crown/frontend/bind.hpp](../../../../../include/crown/frontend/bind.hpp), src/frontend/bind.cpp:270-285,396-456,550-574, src/frontend/sql_rows.cpp:438-447,559-568, [src/frontend/aggregate.cpp](../../../../../src/frontend/aggregate.cpp), [include/crown/ir/ids.hpp](../../../../../include/crown/ir/ids.hpp), Refactor.md:1325-1333, [docs/sql_aggregate_binding.md §Group identity and nullable decoding](../../../../sql_aggregate_binding.md), [docs/sql_aggregate_binding.md §Foreign AST ownership and costs](../../../../sql_aggregate_binding.md), [docs/sql_aggregate_binding.md §Scope and identity](../../../../sql_aggregate_binding.md), [include/crown/frontend/sql_rows.hpp](../../../../../include/crown/frontend/sql_rows.hpp), [include/crown/frontend/aggregate.hpp](../../../../../include/crown/frontend/aggregate.hpp), [src/frontend/bind.cpp](../../../../../src/frontend/bind.cpp), [src/frontend/sql_rows.cpp](../../../../../src/frontend/sql_rows.cpp), [src/frontend/parser.cpp](../../../../../src/frontend/parser.cpp), [src/frontend/parser_detail.hpp](../../../../../src/frontend/parser_detail.hpp), [include/crown/resource/allocator.hpp](../../../../../include/crown/resource/allocator.hpp), [include/crown/resource/ownership.hpp](../../../../../include/crown/resource/ownership.hpp), [include/crown/resource/text.hpp](../../../../../include/crown/resource/text.hpp) |

## B0015

[Lines 88–97](../../../../../src/frontend/sql_aggregate.cpp#L88); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
OriginKey origin_key(const BoundSql& bound, std::size_t output) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Read actual physical origin from the additional genuine source binding. |
| inputs / outputs | Read-only BoundSql and source projection ordinal yield actual BoundColumn occurrence/column plus expression.type. |
| invariants | Output/expression indices are from the same authentic source query; using_value merged refs reject explicitly; no operand/equality-class substitution. |
| ownership | Returns inline key; BoundSql remains ordinary cold local workspace and is never accepted from caller. |
| failure | Merged USING/NATURAL reference is unsupported_aggregate_join_column; unexpected non-column shape is composition contract failure before a handle returns. |
| cost | Constant indexed metadata reads; no second kernel bind. |
| Design | [build/verification/w06-sql-aggregate-compiler-repair-v2/design.md](../../../../../build/verification/w06-sql-aggregate-compiler-repair-v2/design.md), [build/verification/w06-sql-aggregate-compiler-repair-v2/oom-contract.md](../../../../../build/verification/w06-sql-aggregate-compiler-repair-v2/oom-contract.md), [build/verification/w06-sql-aggregate-compiler-repair-v2/receiving-findings.md](../../../../../build/verification/w06-sql-aggregate-compiler-repair-v2/receiving-findings.md), [build/verification/w06-sql-aggregate-compiler-repair-v2/private-contribution-port.md](../../../../../build/verification/w06-sql-aggregate-compiler-repair-v2/private-contribution-port.md), [include/crown/frontend/bind.hpp](../../../../../include/crown/frontend/bind.hpp), src/frontend/bind.cpp:270-285,396-456,550-574, src/frontend/sql_rows.cpp:438-447,559-568, [src/frontend/aggregate.cpp](../../../../../src/frontend/aggregate.cpp), Refactor.md:1325-1333, [docs/sql_aggregate_binding.md §Group identity and nullable decoding](../../../../sql_aggregate_binding.md), [docs/sql_aggregate_binding.md §Foreign AST ownership and costs](../../../../sql_aggregate_binding.md), [docs/sql_aggregate_binding.md §Scope and identity](../../../../sql_aggregate_binding.md), [include/crown/frontend/sql_rows.hpp](../../../../../include/crown/frontend/sql_rows.hpp), [include/crown/frontend/aggregate.hpp](../../../../../include/crown/frontend/aggregate.hpp), [src/frontend/bind.cpp](../../../../../src/frontend/bind.cpp), [src/frontend/sql_rows.cpp](../../../../../src/frontend/sql_rows.cpp), [src/frontend/parser.cpp](../../../../../src/frontend/parser.cpp), [src/frontend/parser_detail.hpp](../../../../../src/frontend/parser_detail.hpp), [include/crown/resource/allocator.hpp](../../../../../include/crown/resource/allocator.hpp), [include/crown/resource/ownership.hpp](../../../../../include/crown/resource/ownership.hpp), [include/crown/resource/text.hpp](../../../../../include/crown/resource/text.hpp) |

## B0016

[Lines 98–109](../../../../../src/frontend/sql_aggregate.cpp#L98); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
ScalarType physical_type(SqlKind kind) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Construct a synthetic physical schema only for actual representable source column types. |
| inputs / outputs | Source SqlKind maps to the matching ScalarType. |
| invariants | Only raw ColumnRef leaves are source-projected here, retaining their physical types. int32/unknown raw schema kinds reject. Aggregate casts remain in generated kernel SQL and its genuine binder supplies checked narrowing metadata; this switch is not the narrowing admission boundary. |
| ownership | Returns enum only. |
| failure | Unsupported type/unknown enum fails before kernel binding. |
| cost | Constant switch. |
| Design | [build/verification/w06-sql-aggregate-compiler-repair-v2/design.md](../../../../../build/verification/w06-sql-aggregate-compiler-repair-v2/design.md), [build/verification/w06-sql-aggregate-compiler-repair-v2/private-contribution-port.md](../../../../../build/verification/w06-sql-aggregate-compiler-repair-v2/private-contribution-port.md), [build/verification/w06-contract-assessment-v1/assessment.md](../../../../../build/verification/w06-contract-assessment-v1/assessment.md), Refactor.md:1317-1327, [include/crown/frontend/sql_rows.hpp](../../../../../include/crown/frontend/sql_rows.hpp), [include/crown/frontend/aggregate.hpp](../../../../../include/crown/frontend/aggregate.hpp), [src/frontend/sql_rows.cpp](../../../../../src/frontend/sql_rows.cpp), [src/frontend/aggregate.cpp](../../../../../src/frontend/aggregate.cpp), Refactor.md:1325-1333, [docs/sql_aggregate_binding.md §Group identity and nullable decoding](../../../../sql_aggregate_binding.md), [docs/sql_aggregate_binding.md §Foreign AST ownership and costs](../../../../sql_aggregate_binding.md), [docs/sql_aggregate_binding.md §Scope and identity](../../../../sql_aggregate_binding.md), [include/crown/frontend/bind.hpp](../../../../../include/crown/frontend/bind.hpp), [src/frontend/bind.cpp](../../../../../src/frontend/bind.cpp), [src/frontend/parser.cpp](../../../../../src/frontend/parser.cpp), [src/frontend/parser_detail.hpp](../../../../../src/frontend/parser_detail.hpp), [include/crown/resource/allocator.hpp](../../../../../include/crown/resource/allocator.hpp), [include/crown/resource/ownership.hpp](../../../../../include/crown/resource/ownership.hpp), [include/crown/resource/text.hpp](../../../../../include/crown/resource/text.hpp) |

## B0017

[Lines 110–111](../../../../../src/frontend/sql_aggregate.cpp#L110); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
}  // namespace

```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Close helper scope without creating another admission or ownership boundary. |
| inputs / outputs | Imports, declarations, comments, closure or spacing in the exact stated block. |
| invariants | No SQL admission, plan authority, output publication or execution claim from this scaffolding. |
| ownership | No new executable ownership beyond declarations explicitly described in surrounding cards. |
| failure | No runtime failure is handled by these lines. |
| cost | No runtime work from comments/spacing/declarations. |
| Design | [build/verification/w06-sql-aggregate-compiler-repair-v2/design.md](../../../../../build/verification/w06-sql-aggregate-compiler-repair-v2/design.md), [build/verification/w06-sql-aggregate-compiler-repair-v2/private-contribution-port.md](../../../../../build/verification/w06-sql-aggregate-compiler-repair-v2/private-contribution-port.md), [build/verification/w06-contract-assessment-v1/assessment.md](../../../../../build/verification/w06-contract-assessment-v1/assessment.md), Refactor.md:1317-1327, Refactor.md:1325-1333, [docs/sql_aggregate_binding.md §Group identity and nullable decoding](../../../../sql_aggregate_binding.md), [docs/sql_aggregate_binding.md §Foreign AST ownership and costs](../../../../sql_aggregate_binding.md), [docs/sql_aggregate_binding.md §Scope and identity](../../../../sql_aggregate_binding.md), [include/crown/frontend/sql_rows.hpp](../../../../../include/crown/frontend/sql_rows.hpp), [include/crown/frontend/aggregate.hpp](../../../../../include/crown/frontend/aggregate.hpp), [include/crown/frontend/bind.hpp](../../../../../include/crown/frontend/bind.hpp), [src/frontend/bind.cpp](../../../../../src/frontend/bind.cpp), [src/frontend/sql_rows.cpp](../../../../../src/frontend/sql_rows.cpp), [src/frontend/aggregate.cpp](../../../../../src/frontend/aggregate.cpp), [src/frontend/parser.cpp](../../../../../src/frontend/parser.cpp), [src/frontend/parser_detail.hpp](../../../../../src/frontend/parser_detail.hpp), [include/crown/resource/allocator.hpp](../../../../../include/crown/resource/allocator.hpp), [include/crown/resource/ownership.hpp](../../../../../include/crown/resource/ownership.hpp), [include/crown/resource/text.hpp](../../../../../include/crown/resource/text.hpp) |

## B0018

[Lines 112–125](../../../../../src/frontend/sql_aggregate.cpp#L112); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct SqlAggregateProgram::Data {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Own genuine source/kernel programs with origin-preserving input/decode binding and family-2 provenance. |
| inputs / outputs | Receiver text/program/array/identity/work/head/static fields; inputs now include actual physical origins. |
| invariants | No BoundSql/catalog copy, joined-row ledger, runtime state or unchecked plan authority is retained. |
| ownership | All new retained text/arrays/shared Data use the original account; actual child metadata is owned by real factories. |
| failure | Failed preparation releases private retained allocations; no partial opaque handle escapes. |
| cost | Original/source/kernel metadata plus K origin/decoder records, N mapping entries and binary image. |
| Design | [build/verification/w06-sql-aggregate-compiler-repair-v2/design.md](../../../../../build/verification/w06-sql-aggregate-compiler-repair-v2/design.md), [build/verification/w06-sql-aggregate-compiler-repair-v2/oom-contract.md](../../../../../build/verification/w06-sql-aggregate-compiler-repair-v2/oom-contract.md), [build/verification/w06-sql-aggregate-compiler-repair-v2/receiving-findings.md](../../../../../build/verification/w06-sql-aggregate-compiler-repair-v2/receiving-findings.md), [build/verification/w06-sql-aggregate-compiler-repair-v2/private-contribution-port.md](../../../../../build/verification/w06-sql-aggregate-compiler-repair-v2/private-contribution-port.md), [include/crown/frontend/bind.hpp](../../../../../include/crown/frontend/bind.hpp), src/frontend/bind.cpp:270-285,396-456,550-574, src/frontend/sql_rows.cpp:438-447,559-568, [src/frontend/aggregate.cpp](../../../../../src/frontend/aggregate.cpp), [include/crown/resource/ownership.hpp](../../../../../include/crown/resource/ownership.hpp), [include/crown/resource/allocator.hpp](../../../../../include/crown/resource/allocator.hpp), [include/crown/resource/text.hpp](../../../../../include/crown/resource/text.hpp), Refactor.md:1325-1333, [docs/sql_aggregate_binding.md §Group identity and nullable decoding](../../../../sql_aggregate_binding.md), [docs/sql_aggregate_binding.md §Foreign AST ownership and costs](../../../../sql_aggregate_binding.md), [docs/sql_aggregate_binding.md §Scope and identity](../../../../sql_aggregate_binding.md), [include/crown/frontend/sql_rows.hpp](../../../../../include/crown/frontend/sql_rows.hpp), [include/crown/frontend/aggregate.hpp](../../../../../include/crown/frontend/aggregate.hpp), [src/frontend/bind.cpp](../../../../../src/frontend/bind.cpp), [src/frontend/sql_rows.cpp](../../../../../src/frontend/sql_rows.cpp), [src/frontend/parser.cpp](../../../../../src/frontend/parser.cpp), [src/frontend/parser_detail.hpp](../../../../../src/frontend/parser_detail.hpp) |

## B0019

[Lines 126–137](../../../../../src/frontend/sql_aggregate.cpp#L126); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text

namespace detail {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Collect synchronous compiler inputs and ordinary cold AST/mapping workspace. |
| inputs / outputs | Borrowed receiving account, authenticated SqlSyntax, actual Catalog/options, private arena/reference vector and selected work counter. |
| invariants | Borrowed arguments remain live throughout run; no public DTO/edited opaque program route. |
| ownership | Arena owns all ASTs; vector owns only private node pointers valid within the arena. |
| failure | Any later failure destroys cold workspace and child program locals. |
| cost | Cold AST storage and O(N) reference pointers; retained result is separate. |
| Design | [build/verification/w06-sql-aggregate-compiler-repair-v2/design.md](../../../../../build/verification/w06-sql-aggregate-compiler-repair-v2/design.md), [build/verification/w06-sql-aggregate-compiler-repair-v2/private-contribution-port.md](../../../../../build/verification/w06-sql-aggregate-compiler-repair-v2/private-contribution-port.md), [build/verification/w06-contract-assessment-v1/assessment.md](../../../../../build/verification/w06-contract-assessment-v1/assessment.md), Refactor.md:1317-1327, [build/verification/w06-sql-aggregate-compiler-repair-v2/source/pinned-libpg-query/pg_query.h](../../../../../build/verification/w06-sql-aggregate-compiler-repair-v2/source/pinned-libpg-query/pg_query.h), [build/verification/w06-sql-aggregate-compiler-repair-v2/source/pinned-libpg-query/protobuf/pg_query.upb.h](../../../../../build/verification/w06-sql-aggregate-compiler-repair-v2/source/pinned-libpg-query/protobuf/pg_query.upb.h), [build/verification/w06-sql-aggregate-compiler-repair-v2/source/pinned-libpg-query/vendor/upb/upb/generated_code_support.h](../../../../../build/verification/w06-sql-aggregate-compiler-repair-v2/source/pinned-libpg-query/vendor/upb/upb/generated_code_support.h), [build/verification/w06-sql-aggregate-compiler-repair-v2/source/pinned-libpg-query/vendor/upb/upb.c](../../../../../build/verification/w06-sql-aggregate-compiler-repair-v2/source/pinned-libpg-query/vendor/upb/upb.c), [build/verification/w06-sql-aggregate-compiler-repair-v2/source/pinned-libpg-query/Makefile](../../../../../build/verification/w06-sql-aggregate-compiler-repair-v2/source/pinned-libpg-query/Makefile), Refactor.md:1325-1333, [docs/sql_aggregate_binding.md §Group identity and nullable decoding](../../../../sql_aggregate_binding.md), [docs/sql_aggregate_binding.md §Foreign AST ownership and costs](../../../../sql_aggregate_binding.md), [docs/sql_aggregate_binding.md §Scope and identity](../../../../sql_aggregate_binding.md), [include/crown/frontend/sql_rows.hpp](../../../../../include/crown/frontend/sql_rows.hpp), [include/crown/frontend/aggregate.hpp](../../../../../include/crown/frontend/aggregate.hpp), [include/crown/frontend/bind.hpp](../../../../../include/crown/frontend/bind.hpp), [src/frontend/bind.cpp](../../../../../src/frontend/bind.cpp), [src/frontend/sql_rows.cpp](../../../../../src/frontend/sql_rows.cpp), [src/frontend/aggregate.cpp](../../../../../src/frontend/aggregate.cpp), [src/frontend/parser.cpp](../../../../../src/frontend/parser.cpp), [src/frontend/parser_detail.hpp](../../../../../src/frontend/parser_detail.hpp), [include/crown/resource/allocator.hpp](../../../../../include/crown/resource/allocator.hpp), [include/crown/resource/ownership.hpp](../../../../../include/crown/resource/ownership.hpp), [include/crown/resource/text.hpp](../../../../../include/crown/resource/text.hpp) |

## B0020

[Lines 138–142](../../../../../src/frontend/sql_aggregate.cpp#L138); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
  void charge(std::uint64_t amount = 1) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Enforce one selected composition-work allowance across this factory call. |
| inputs / outputs | Unsigned amount increments work_ after overflow/subtraction-cap admission. |
| invariants | work_ never exceeds uint64 or a present limit; no reset per reference/child projection. |
| ownership | Inline compiler counter; not a receiving-memory grant. |
| failure | resource_limit occurs before a public handle escapes. |
| cost | Constant arithmetic per selected charge; not a full parser/CPU/allocator meter. |
| Design | [build/verification/w06-sql-aggregate-compiler-repair-v2/design.md](../../../../../build/verification/w06-sql-aggregate-compiler-repair-v2/design.md), [build/verification/w06-sql-aggregate-compiler-repair-v2/private-contribution-port.md](../../../../../build/verification/w06-sql-aggregate-compiler-repair-v2/private-contribution-port.md), [build/verification/w06-contract-assessment-v1/assessment.md](../../../../../build/verification/w06-contract-assessment-v1/assessment.md), Refactor.md:1317-1327, Refactor.md:1325-1333, [docs/sql_aggregate_binding.md §Group identity and nullable decoding](../../../../sql_aggregate_binding.md), [docs/sql_aggregate_binding.md §Foreign AST ownership and costs](../../../../sql_aggregate_binding.md), [docs/sql_aggregate_binding.md §Scope and identity](../../../../sql_aggregate_binding.md), [include/crown/frontend/sql_rows.hpp](../../../../../include/crown/frontend/sql_rows.hpp), [include/crown/frontend/aggregate.hpp](../../../../../include/crown/frontend/aggregate.hpp), [include/crown/frontend/bind.hpp](../../../../../include/crown/frontend/bind.hpp), [src/frontend/bind.cpp](../../../../../src/frontend/bind.cpp), [src/frontend/sql_rows.cpp](../../../../../src/frontend/sql_rows.cpp), [src/frontend/aggregate.cpp](../../../../../src/frontend/aggregate.cpp), [src/frontend/parser.cpp](../../../../../src/frontend/parser.cpp), [src/frontend/parser_detail.hpp](../../../../../src/frontend/parser_detail.hpp), [include/crown/resource/allocator.hpp](../../../../../include/crown/resource/allocator.hpp), [include/crown/resource/ownership.hpp](../../../../../include/crown/resource/ownership.hpp), [include/crown/resource/text.hpp](../../../../../include/crown/resource/text.hpp) |

## B0021

[Lines 143–151](../../../../../src/frontend/sql_aggregate.cpp#L143); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
  void keys(const Json& node, std::initializer_list<std::string_view> allowed) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Reject unsupported original AST keys before any structural rewrite. |
| inputs / outputs | Authenticated JSON object and explicit allowed field set. |
| invariants | Every present key is checked; no HAVING/window/etc can be erased and silently accepted. |
| ownership | Borrows original owned AST and static allowlist. |
| failure | Malformed authenticated shape is parser_contract; unsupported key is unsupported_sql. |
| cost | Cold field/allowlist visits charged to composition work. |
| Design | [build/verification/w06-sql-aggregate-compiler-repair-v2/design.md](../../../../../build/verification/w06-sql-aggregate-compiler-repair-v2/design.md), [build/verification/w06-sql-aggregate-compiler-repair-v2/private-contribution-port.md](../../../../../build/verification/w06-sql-aggregate-compiler-repair-v2/private-contribution-port.md), [build/verification/w06-contract-assessment-v1/assessment.md](../../../../../build/verification/w06-contract-assessment-v1/assessment.md), Refactor.md:1317-1327, [include/crown/frontend/sql_rows.hpp](../../../../../include/crown/frontend/sql_rows.hpp), [include/crown/frontend/aggregate.hpp](../../../../../include/crown/frontend/aggregate.hpp), [src/frontend/sql_rows.cpp](../../../../../src/frontend/sql_rows.cpp), [src/frontend/aggregate.cpp](../../../../../src/frontend/aggregate.cpp), Refactor.md:1325-1333, [docs/sql_aggregate_binding.md §Group identity and nullable decoding](../../../../sql_aggregate_binding.md), [docs/sql_aggregate_binding.md §Foreign AST ownership and costs](../../../../sql_aggregate_binding.md), [docs/sql_aggregate_binding.md §Scope and identity](../../../../sql_aggregate_binding.md), [include/crown/frontend/bind.hpp](../../../../../include/crown/frontend/bind.hpp), [src/frontend/bind.cpp](../../../../../src/frontend/bind.cpp), [src/frontend/parser.cpp](../../../../../src/frontend/parser.cpp), [src/frontend/parser_detail.hpp](../../../../../src/frontend/parser_detail.hpp), [include/crown/resource/allocator.hpp](../../../../../include/crown/resource/allocator.hpp), [include/crown/resource/ownership.hpp](../../../../../include/crown/resource/ownership.hpp), [include/crown/resource/text.hpp](../../../../../include/crown/resource/text.hpp) |

## B0022

[Lines 152–170](../../../../../src/frontend/sql_aggregate.cpp#L152); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
  void preflight() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Authenticate the admitted original top-level aggregate syntax before deriving either query. |
| inputs / outputs | Original SelectStmt/targets are checked for supported top-level flags, target count and ResTarget/FuncCall keys. |
| invariants | Only FROM/WHERE/input-column grouping/targets survive; sets, limits, DISTINCT/FILTER/OVER/ordered/other clauses remain rejected by this or real factories. |
| ownership | Reads original parse result only; changes no caller AST or program. |
| failure | Semantic/resource errors precede source/kernel construction; no native/runtime mutation. |
| cost | Original byte and top/target key charges; full parser and child binder limits remain separately real. |
| Design | [build/verification/w06-sql-aggregate-compiler-repair-v2/design.md](../../../../../build/verification/w06-sql-aggregate-compiler-repair-v2/design.md), [build/verification/w06-sql-aggregate-compiler-repair-v2/private-contribution-port.md](../../../../../build/verification/w06-sql-aggregate-compiler-repair-v2/private-contribution-port.md), [build/verification/w06-contract-assessment-v1/assessment.md](../../../../../build/verification/w06-contract-assessment-v1/assessment.md), Refactor.md:1317-1327, [include/crown/frontend/sql_rows.hpp](../../../../../include/crown/frontend/sql_rows.hpp), [include/crown/frontend/aggregate.hpp](../../../../../include/crown/frontend/aggregate.hpp), [src/frontend/sql_rows.cpp](../../../../../src/frontend/sql_rows.cpp), [src/frontend/aggregate.cpp](../../../../../src/frontend/aggregate.cpp), Refactor.md:1325-1333, [docs/sql_aggregate_binding.md §Group identity and nullable decoding](../../../../sql_aggregate_binding.md), [docs/sql_aggregate_binding.md §Foreign AST ownership and costs](../../../../sql_aggregate_binding.md), [docs/sql_aggregate_binding.md §Scope and identity](../../../../sql_aggregate_binding.md), [include/crown/frontend/bind.hpp](../../../../../include/crown/frontend/bind.hpp), [src/frontend/bind.cpp](../../../../../src/frontend/bind.cpp), [src/frontend/parser.cpp](../../../../../src/frontend/parser.cpp), [src/frontend/parser_detail.hpp](../../../../../src/frontend/parser_detail.hpp), [include/crown/resource/allocator.hpp](../../../../../include/crown/resource/allocator.hpp), [include/crown/resource/ownership.hpp](../../../../../include/crown/resource/ownership.hpp), [include/crown/resource/text.hpp](../../../../../include/crown/resource/text.hpp) |

## B0023

[Lines 171–179](../../../../../src/frontend/sql_aggregate.cpp#L171); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
  pg_query_SelectStmt* select(pg_query_ParseResult* tree) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Check actual independently decoded envelope/version/SELECT before mutable derivation. |
| inputs / outputs | A checked wire-decoded ParseResult returns its one SelectStmt. |
| invariants | Exactly one statement, pinned PG version and SELECT kind are required for both source and kernel. |
| ownership | Returned pointer borrows the common arena; no tree is a clone/copy result. |
| failure | Unexpected shape is parser_contract; mutable allocation result checked. |
| cost | Constant envelope checks. |
| Design | [build/verification/w06-sql-aggregate-compiler-repair-v2/design.md](../../../../../build/verification/w06-sql-aggregate-compiler-repair-v2/design.md), [build/verification/w06-sql-aggregate-compiler-repair-v2/oom-contract.md](../../../../../build/verification/w06-sql-aggregate-compiler-repair-v2/oom-contract.md), [build/verification/w06-sql-aggregate-compiler-repair-v2/receiving-findings.md](../../../../../build/verification/w06-sql-aggregate-compiler-repair-v2/receiving-findings.md), [build/verification/w06-sql-aggregate-compiler-repair-v2/private-contribution-port.md](../../../../../build/verification/w06-sql-aggregate-compiler-repair-v2/private-contribution-port.md), [build/verification/w06-sql-aggregate-compiler-repair-v2/source/pinned-libpg-query/protobuf/pg_query.upb.h](../../../../../build/verification/w06-sql-aggregate-compiler-repair-v2/source/pinned-libpg-query/protobuf/pg_query.upb.h), [build/verification/w06-sql-aggregate-compiler-repair-v2/source/pinned-libpg-query/vendor/upb/upb/generated_code_support.h](../../../../../build/verification/w06-sql-aggregate-compiler-repair-v2/source/pinned-libpg-query/vendor/upb/upb/generated_code_support.h), [build/verification/w06-sql-aggregate-compiler-repair-v2/source/pinned-libpg-query/vendor/upb/upb.c](../../../../../build/verification/w06-sql-aggregate-compiler-repair-v2/source/pinned-libpg-query/vendor/upb/upb.c), Refactor.md:1325-1333, [docs/sql_aggregate_binding.md §Group identity and nullable decoding](../../../../sql_aggregate_binding.md), [docs/sql_aggregate_binding.md §Foreign AST ownership and costs](../../../../sql_aggregate_binding.md), [docs/sql_aggregate_binding.md §Scope and identity](../../../../sql_aggregate_binding.md), [include/crown/frontend/sql_rows.hpp](../../../../../include/crown/frontend/sql_rows.hpp), [include/crown/frontend/aggregate.hpp](../../../../../include/crown/frontend/aggregate.hpp), [include/crown/frontend/bind.hpp](../../../../../include/crown/frontend/bind.hpp), [src/frontend/bind.cpp](../../../../../src/frontend/bind.cpp), [src/frontend/sql_rows.cpp](../../../../../src/frontend/sql_rows.cpp), [src/frontend/aggregate.cpp](../../../../../src/frontend/aggregate.cpp), [src/frontend/parser.cpp](../../../../../src/frontend/parser.cpp), [src/frontend/parser_detail.hpp](../../../../../src/frontend/parser_detail.hpp), [include/crown/resource/allocator.hpp](../../../../../include/crown/resource/allocator.hpp), [include/crown/resource/ownership.hpp](../../../../../include/crown/resource/ownership.hpp), [include/crown/resource/text.hpp](../../../../../include/crown/resource/text.hpp) |

## B0024

[Lines 180–184](../../../../../src/frontend/sql_aggregate.cpp#L180); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
  upb_StringView own_text(std::string_view value) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Copy synthesized names into the existing cold arena. |
| inputs / outputs | String view becomes arena-owned NUL-terminated bytes and upb_StringView. |
| invariants | No SQL string concatenation/unparser is used; upstream deparser quotes names correctly. |
| ownership | Arena owns copied characters through both deparses. |
| failure | Selected byte admission or allocation can fail before publication. |
| cost | Linear name bytes, charged once before copy. |
| Design | [build/verification/w06-sql-aggregate-compiler-repair-v2/design.md](../../../../../build/verification/w06-sql-aggregate-compiler-repair-v2/design.md), [build/verification/w06-sql-aggregate-compiler-repair-v2/private-contribution-port.md](../../../../../build/verification/w06-sql-aggregate-compiler-repair-v2/private-contribution-port.md), [build/verification/w06-contract-assessment-v1/assessment.md](../../../../../build/verification/w06-contract-assessment-v1/assessment.md), Refactor.md:1317-1327, [build/verification/w06-sql-aggregate-compiler-repair-v2/source/pinned-libpg-query/pg_query.h](../../../../../build/verification/w06-sql-aggregate-compiler-repair-v2/source/pinned-libpg-query/pg_query.h), [build/verification/w06-sql-aggregate-compiler-repair-v2/source/pinned-libpg-query/protobuf/pg_query.upb.h](../../../../../build/verification/w06-sql-aggregate-compiler-repair-v2/source/pinned-libpg-query/protobuf/pg_query.upb.h), [build/verification/w06-sql-aggregate-compiler-repair-v2/source/pinned-libpg-query/vendor/upb/upb/generated_code_support.h](../../../../../build/verification/w06-sql-aggregate-compiler-repair-v2/source/pinned-libpg-query/vendor/upb/upb/generated_code_support.h), [build/verification/w06-sql-aggregate-compiler-repair-v2/source/pinned-libpg-query/vendor/upb/upb.c](../../../../../build/verification/w06-sql-aggregate-compiler-repair-v2/source/pinned-libpg-query/vendor/upb/upb.c), [build/verification/w06-sql-aggregate-compiler-repair-v2/source/pinned-libpg-query/Makefile](../../../../../build/verification/w06-sql-aggregate-compiler-repair-v2/source/pinned-libpg-query/Makefile), Refactor.md:1325-1333, [docs/sql_aggregate_binding.md §Group identity and nullable decoding](../../../../sql_aggregate_binding.md), [docs/sql_aggregate_binding.md §Foreign AST ownership and costs](../../../../sql_aggregate_binding.md), [docs/sql_aggregate_binding.md §Scope and identity](../../../../sql_aggregate_binding.md), [include/crown/frontend/sql_rows.hpp](../../../../../include/crown/frontend/sql_rows.hpp), [include/crown/frontend/aggregate.hpp](../../../../../include/crown/frontend/aggregate.hpp), [include/crown/frontend/bind.hpp](../../../../../include/crown/frontend/bind.hpp), [src/frontend/bind.cpp](../../../../../src/frontend/bind.cpp), [src/frontend/sql_rows.cpp](../../../../../src/frontend/sql_rows.cpp), [src/frontend/aggregate.cpp](../../../../../src/frontend/aggregate.cpp), [src/frontend/parser.cpp](../../../../../src/frontend/parser.cpp), [src/frontend/parser_detail.hpp](../../../../../src/frontend/parser_detail.hpp), [include/crown/resource/allocator.hpp](../../../../../include/crown/resource/allocator.hpp), [include/crown/resource/ownership.hpp](../../../../../include/crown/resource/ownership.hpp), [include/crown/resource/text.hpp](../../../../../include/crown/resource/text.hpp) |

## B0025

[Lines 185–193](../../../../../src/frontend/sql_aggregate.cpp#L185); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
  pg_query_ParseResult* decode(PgQueryProtobuf wire) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Decode the same owned authenticated wire into one independent tree with actual checked OOM/depth status. |
| inputs / outputs | PgQueryProtobuf value returns a new ParseResult only after checked New and upb_Decode Ok. |
| invariants | Root is nonnull before decoder use; no DeepClone/DeepCopy/_upb_Message_Copy path. Called once for kernel and once for source. |
| ownership | Native wire owner and arena survive both calls; partial decoded storage stays private in arena. |
| failure | Checked New/null and upb_Decode status failures remain private: OutOfMemory becomes std::bad_alloc, MaxDepthExceeded resource_limit, and other non-Ok statuses parser_contract. Parent’s arena seam covered all 8 Debug and 11 sanitizer allocation positions in the first compiler arena only; it is not global parser/deparser or C++ new failure coverage. |
| cost | One cold wire decode per call with real nested/string/array allocations; actual fault tests unrun. |
| Design | [build/verification/w06-sql-aggregate-compiler-repair-v2/design.md](../../../../../build/verification/w06-sql-aggregate-compiler-repair-v2/design.md), [build/verification/w06-sql-aggregate-compiler-repair-v2/oom-contract.md](../../../../../build/verification/w06-sql-aggregate-compiler-repair-v2/oom-contract.md), [build/verification/w06-sql-aggregate-compiler-repair-v2/receiving-findings.md](../../../../../build/verification/w06-sql-aggregate-compiler-repair-v2/receiving-findings.md), [build/verification/w06-sql-aggregate-compiler-repair-v2/private-contribution-port.md](../../../../../build/verification/w06-sql-aggregate-compiler-repair-v2/private-contribution-port.md), [build/verification/w06-sql-aggregate-compiler-repair-v2/source/pinned-libpg-query/protobuf/pg_query.upb.h](../../../../../build/verification/w06-sql-aggregate-compiler-repair-v2/source/pinned-libpg-query/protobuf/pg_query.upb.h), [build/verification/w06-sql-aggregate-compiler-repair-v2/source/pinned-libpg-query/vendor/upb/upb/generated_code_support.h](../../../../../build/verification/w06-sql-aggregate-compiler-repair-v2/source/pinned-libpg-query/vendor/upb/upb/generated_code_support.h), [build/verification/w06-sql-aggregate-compiler-repair-v2/source/pinned-libpg-query/vendor/upb/upb.c](../../../../../build/verification/w06-sql-aggregate-compiler-repair-v2/source/pinned-libpg-query/vendor/upb/upb.c), Refactor.md:1325-1333, [docs/sql_aggregate_binding.md §Group identity and nullable decoding](../../../../sql_aggregate_binding.md), [docs/sql_aggregate_binding.md §Foreign AST ownership and costs](../../../../sql_aggregate_binding.md), [docs/sql_aggregate_binding.md §Scope and identity](../../../../sql_aggregate_binding.md), [include/crown/frontend/sql_rows.hpp](../../../../../include/crown/frontend/sql_rows.hpp), [include/crown/frontend/aggregate.hpp](../../../../../include/crown/frontend/aggregate.hpp), [include/crown/frontend/bind.hpp](../../../../../include/crown/frontend/bind.hpp), [src/frontend/bind.cpp](../../../../../src/frontend/bind.cpp), [src/frontend/sql_rows.cpp](../../../../../src/frontend/sql_rows.cpp), [src/frontend/aggregate.cpp](../../../../../src/frontend/aggregate.cpp), [src/frontend/parser.cpp](../../../../../src/frontend/parser.cpp), [src/frontend/parser_detail.hpp](../../../../../src/frontend/parser_detail.hpp), [include/crown/resource/allocator.hpp](../../../../../include/crown/resource/allocator.hpp), [include/crown/resource/ownership.hpp](../../../../../include/crown/resource/ownership.hpp), [include/crown/resource/text.hpp](../../../../../include/crown/resource/text.hpp) |

## B0026

[Lines 194–204](../../../../../src/frontend/sql_aggregate.cpp#L194); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
  void reference(pg_query_Node* node) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Collect original ColumnRef pointers for later physical-origin resolution. |
| inputs / outputs | Validated one/two-string ColumnRef is retained in deterministic reference order under expression cap. |
| invariants | Textual equality does not deduplicate; actual genuine bind_sql resolves origin later. |
| ownership | Pointers borrow kernel arena nodes; source projection borrows those leaves only during its earlier final read phase. |
| failure | Unsupported wildcard/qualification or capacity errors reject before publication. |
| cost | At most two identifier-kind checks plus cold pointer append; no leaf clone. |
| Design | [build/verification/w06-sql-aggregate-compiler-repair-v2/design.md](../../../../../build/verification/w06-sql-aggregate-compiler-repair-v2/design.md), [build/verification/w06-sql-aggregate-compiler-repair-v2/oom-contract.md](../../../../../build/verification/w06-sql-aggregate-compiler-repair-v2/oom-contract.md), [build/verification/w06-sql-aggregate-compiler-repair-v2/receiving-findings.md](../../../../../build/verification/w06-sql-aggregate-compiler-repair-v2/receiving-findings.md), [build/verification/w06-sql-aggregate-compiler-repair-v2/private-contribution-port.md](../../../../../build/verification/w06-sql-aggregate-compiler-repair-v2/private-contribution-port.md), [include/crown/frontend/bind.hpp](../../../../../include/crown/frontend/bind.hpp), src/frontend/bind.cpp:270-285,396-456,550-574, src/frontend/sql_rows.cpp:438-447,559-568, [src/frontend/aggregate.cpp](../../../../../src/frontend/aggregate.cpp), Refactor.md:1325-1333, [docs/sql_aggregate_binding.md §Group identity and nullable decoding](../../../../sql_aggregate_binding.md), [docs/sql_aggregate_binding.md §Foreign AST ownership and costs](../../../../sql_aggregate_binding.md), [docs/sql_aggregate_binding.md §Scope and identity](../../../../sql_aggregate_binding.md), [include/crown/frontend/sql_rows.hpp](../../../../../include/crown/frontend/sql_rows.hpp), [include/crown/frontend/aggregate.hpp](../../../../../include/crown/frontend/aggregate.hpp), [src/frontend/bind.cpp](../../../../../src/frontend/bind.cpp), [src/frontend/sql_rows.cpp](../../../../../src/frontend/sql_rows.cpp), [src/frontend/parser.cpp](../../../../../src/frontend/parser.cpp), [src/frontend/parser_detail.hpp](../../../../../src/frontend/parser_detail.hpp), [include/crown/resource/allocator.hpp](../../../../../include/crown/resource/allocator.hpp), [include/crown/resource/ownership.hpp](../../../../../include/crown/resource/ownership.hpp), [include/crown/resource/text.hpp](../../../../../include/crown/resource/text.hpp) |

## B0027

[Lines 205–221](../../../../../src/frontend/sql_aggregate.cpp#L205); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
  void argument(pg_query_Node* node, std::size_t depth = 0) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Traverse only admitted aggregate argument shapes while preserving casts/constants. |
| inputs / outputs | ColumnRef is recorded, A_Const stays in kernel, TypeCast recursively visits only its argument. |
| invariants | Recursion cap applies; aggregate parameters/computed/nested/cross-relation expressions explicitly reject; real kernel still validates cast/function/type semantics. |
| ownership | Mutates no argument value; node pointers remain arena-owned. |
| failure | Unsupported argument/expression/depth/parser-contract errors happen before program publication. |
| cost | One selected visit per traversed argument node, with bounded recursion. |
| Design | [build/verification/w06-sql-aggregate-compiler-repair-v2/design.md](../../../../../build/verification/w06-sql-aggregate-compiler-repair-v2/design.md), [build/verification/w06-sql-aggregate-compiler-repair-v2/private-contribution-port.md](../../../../../build/verification/w06-sql-aggregate-compiler-repair-v2/private-contribution-port.md), [build/verification/w06-contract-assessment-v1/assessment.md](../../../../../build/verification/w06-contract-assessment-v1/assessment.md), Refactor.md:1317-1327, [include/crown/frontend/sql_rows.hpp](../../../../../include/crown/frontend/sql_rows.hpp), [include/crown/frontend/aggregate.hpp](../../../../../include/crown/frontend/aggregate.hpp), [src/frontend/sql_rows.cpp](../../../../../src/frontend/sql_rows.cpp), [src/frontend/aggregate.cpp](../../../../../src/frontend/aggregate.cpp), Refactor.md:1325-1333, [docs/sql_aggregate_binding.md §Group identity and nullable decoding](../../../../sql_aggregate_binding.md), [docs/sql_aggregate_binding.md §Foreign AST ownership and costs](../../../../sql_aggregate_binding.md), [docs/sql_aggregate_binding.md §Scope and identity](../../../../sql_aggregate_binding.md), [include/crown/frontend/bind.hpp](../../../../../include/crown/frontend/bind.hpp), [src/frontend/bind.cpp](../../../../../src/frontend/bind.cpp), [src/frontend/parser.cpp](../../../../../src/frontend/parser.cpp), [src/frontend/parser_detail.hpp](../../../../../src/frontend/parser_detail.hpp), [include/crown/resource/allocator.hpp](../../../../../include/crown/resource/allocator.hpp), [include/crown/resource/ownership.hpp](../../../../../include/crown/resource/ownership.hpp), [include/crown/resource/text.hpp](../../../../../include/crown/resource/text.hpp) |

## B0028

[Lines 222–227](../../../../../src/frontend/sql_aggregate.cpp#L222); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
  std::string column_name(const pg_query_Node* node) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Recover the original column default output name before cN rewriting. |
| inputs / outputs | Last String field of a ColumnRef becomes an owning cold string. |
| invariants | Qualified/unqualified naming and quoted identifier bytes are preserved. |
| ownership | Copies text only into cold temporary name; it is then frozen in arena target metadata. |
| failure | Invalid/wildcard shape rejects; allocation failure propagates. |
| cost | Linear final identifier bytes. |
| Design | [build/verification/w06-sql-aggregate-compiler-repair-v2/design.md](../../../../../build/verification/w06-sql-aggregate-compiler-repair-v2/design.md), [build/verification/w06-sql-aggregate-compiler-repair-v2/private-contribution-port.md](../../../../../build/verification/w06-sql-aggregate-compiler-repair-v2/private-contribution-port.md), [build/verification/w06-contract-assessment-v1/assessment.md](../../../../../build/verification/w06-contract-assessment-v1/assessment.md), Refactor.md:1317-1327, [build/verification/w06-sql-aggregate-compiler-repair-v2/source/pinned-libpg-query/pg_query.h](../../../../../build/verification/w06-sql-aggregate-compiler-repair-v2/source/pinned-libpg-query/pg_query.h), [build/verification/w06-sql-aggregate-compiler-repair-v2/source/pinned-libpg-query/protobuf/pg_query.upb.h](../../../../../build/verification/w06-sql-aggregate-compiler-repair-v2/source/pinned-libpg-query/protobuf/pg_query.upb.h), [build/verification/w06-sql-aggregate-compiler-repair-v2/source/pinned-libpg-query/vendor/upb/upb/generated_code_support.h](../../../../../build/verification/w06-sql-aggregate-compiler-repair-v2/source/pinned-libpg-query/vendor/upb/upb/generated_code_support.h), [build/verification/w06-sql-aggregate-compiler-repair-v2/source/pinned-libpg-query/vendor/upb/upb.c](../../../../../build/verification/w06-sql-aggregate-compiler-repair-v2/source/pinned-libpg-query/vendor/upb/upb.c), [build/verification/w06-sql-aggregate-compiler-repair-v2/source/pinned-libpg-query/Makefile](../../../../../build/verification/w06-sql-aggregate-compiler-repair-v2/source/pinned-libpg-query/Makefile), Refactor.md:1325-1333, [docs/sql_aggregate_binding.md §Group identity and nullable decoding](../../../../sql_aggregate_binding.md), [docs/sql_aggregate_binding.md §Foreign AST ownership and costs](../../../../sql_aggregate_binding.md), [docs/sql_aggregate_binding.md §Scope and identity](../../../../sql_aggregate_binding.md), [include/crown/frontend/sql_rows.hpp](../../../../../include/crown/frontend/sql_rows.hpp), [include/crown/frontend/aggregate.hpp](../../../../../include/crown/frontend/aggregate.hpp), [include/crown/frontend/bind.hpp](../../../../../include/crown/frontend/bind.hpp), [src/frontend/bind.cpp](../../../../../src/frontend/bind.cpp), [src/frontend/sql_rows.cpp](../../../../../src/frontend/sql_rows.cpp), [src/frontend/aggregate.cpp](../../../../../src/frontend/aggregate.cpp), [src/frontend/parser.cpp](../../../../../src/frontend/parser.cpp), [src/frontend/parser_detail.hpp](../../../../../src/frontend/parser_detail.hpp), [include/crown/resource/allocator.hpp](../../../../../include/crown/resource/allocator.hpp), [include/crown/resource/ownership.hpp](../../../../../include/crown/resource/ownership.hpp), [include/crown/resource/text.hpp](../../../../../include/crown/resource/text.hpp) |

## B0029

[Lines 228–259](../../../../../src/frontend/sql_aggregate.cpp#L228); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
  void collect(pg_query_SelectStmt* kernel) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Collect original refs/default names before source deparse and any kernel remap. |
| inputs / outputs | GROUP BY and SELECT/argument traversal produces original kernel leaf pointers and explicit original default output names. |
| invariants | Only actual supported shapes proceed; original grouping identity is later taken from genuine BoundColumn, not normalized decoder. |
| ownership | Leaves/names stay in arena; source may borrow them only before its scoped final deparse; actual programs own independent metadata afterward. |
| failure | Shape/argument/work failures remain private; actual kernel factory validates grouping/functions/casts. |
| cost | Selected reference/name visits; no deep-copy helper or hot payload duplication. |
| Design | [build/verification/w06-sql-aggregate-compiler-repair-v2/design.md](../../../../../build/verification/w06-sql-aggregate-compiler-repair-v2/design.md), [build/verification/w06-sql-aggregate-compiler-repair-v2/oom-contract.md](../../../../../build/verification/w06-sql-aggregate-compiler-repair-v2/oom-contract.md), [build/verification/w06-sql-aggregate-compiler-repair-v2/receiving-findings.md](../../../../../build/verification/w06-sql-aggregate-compiler-repair-v2/receiving-findings.md), [build/verification/w06-sql-aggregate-compiler-repair-v2/private-contribution-port.md](../../../../../build/verification/w06-sql-aggregate-compiler-repair-v2/private-contribution-port.md), [include/crown/frontend/bind.hpp](../../../../../include/crown/frontend/bind.hpp), src/frontend/bind.cpp:270-285,396-456,550-574, src/frontend/sql_rows.cpp:438-447,559-568, [src/frontend/aggregate.cpp](../../../../../src/frontend/aggregate.cpp), Refactor.md:1325-1333, [docs/sql_aggregate_binding.md §Group identity and nullable decoding](../../../../sql_aggregate_binding.md), [docs/sql_aggregate_binding.md §Foreign AST ownership and costs](../../../../sql_aggregate_binding.md), [docs/sql_aggregate_binding.md §Scope and identity](../../../../sql_aggregate_binding.md), [include/crown/frontend/sql_rows.hpp](../../../../../include/crown/frontend/sql_rows.hpp), [include/crown/frontend/aggregate.hpp](../../../../../include/crown/frontend/aggregate.hpp), [src/frontend/bind.cpp](../../../../../src/frontend/bind.cpp), [src/frontend/sql_rows.cpp](../../../../../src/frontend/sql_rows.cpp), [src/frontend/parser.cpp](../../../../../src/frontend/parser.cpp), [src/frontend/parser_detail.hpp](../../../../../src/frontend/parser_detail.hpp), [include/crown/resource/allocator.hpp](../../../../../include/crown/resource/allocator.hpp), [include/crown/resource/ownership.hpp](../../../../../include/crown/resource/ownership.hpp), [include/crown/resource/text.hpp](../../../../../include/crown/resource/text.hpp) |

## B0030

[Lines 260–276](../../../../../src/frontend/sql_aggregate.cpp#L260); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
  std::string deparse(pg_query_ParseResult* tree) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Serialize/deparse only structurally derived authenticated ASTs using pinned upstream APIs. |
| inputs / outputs | ParseResult enters checked upb_Encode; owned C deparse query becomes capped cold SQL string. |
| invariants | Wire status is checked directly rather than ignored generated serialize return; derived SQL byte cap applies; actual factories reparse output. |
| ownership | Encoded bytes borrow arena; DeparseOwner frees query/error after copying; no native pointer escapes. |
| failure | OOM/depth become resource failures; unexpected deparser/empty output is parser_contract; native owner exists before error processing. |
| cost | Actual cold encode/deparse plus derived-byte copy/selected charge; no retained-memory accounting claim for C workspace. |
| Design | [build/verification/w06-sql-aggregate-compiler-repair-v2/design.md](../../../../../build/verification/w06-sql-aggregate-compiler-repair-v2/design.md), [build/verification/w06-sql-aggregate-compiler-repair-v2/private-contribution-port.md](../../../../../build/verification/w06-sql-aggregate-compiler-repair-v2/private-contribution-port.md), [build/verification/w06-contract-assessment-v1/assessment.md](../../../../../build/verification/w06-contract-assessment-v1/assessment.md), Refactor.md:1317-1327, [build/verification/w06-sql-aggregate-compiler-repair-v2/source/pinned-libpg-query/pg_query.h](../../../../../build/verification/w06-sql-aggregate-compiler-repair-v2/source/pinned-libpg-query/pg_query.h), [build/verification/w06-sql-aggregate-compiler-repair-v2/source/pinned-libpg-query/protobuf/pg_query.upb.h](../../../../../build/verification/w06-sql-aggregate-compiler-repair-v2/source/pinned-libpg-query/protobuf/pg_query.upb.h), [build/verification/w06-sql-aggregate-compiler-repair-v2/source/pinned-libpg-query/vendor/upb/upb/generated_code_support.h](../../../../../build/verification/w06-sql-aggregate-compiler-repair-v2/source/pinned-libpg-query/vendor/upb/upb/generated_code_support.h), [build/verification/w06-sql-aggregate-compiler-repair-v2/source/pinned-libpg-query/vendor/upb/upb.c](../../../../../build/verification/w06-sql-aggregate-compiler-repair-v2/source/pinned-libpg-query/vendor/upb/upb.c), [build/verification/w06-sql-aggregate-compiler-repair-v2/source/pinned-libpg-query/Makefile](../../../../../build/verification/w06-sql-aggregate-compiler-repair-v2/source/pinned-libpg-query/Makefile), Refactor.md:1325-1333, [docs/sql_aggregate_binding.md §Group identity and nullable decoding](../../../../sql_aggregate_binding.md), [docs/sql_aggregate_binding.md §Foreign AST ownership and costs](../../../../sql_aggregate_binding.md), [docs/sql_aggregate_binding.md §Scope and identity](../../../../sql_aggregate_binding.md), [include/crown/frontend/sql_rows.hpp](../../../../../include/crown/frontend/sql_rows.hpp), [include/crown/frontend/aggregate.hpp](../../../../../include/crown/frontend/aggregate.hpp), [include/crown/frontend/bind.hpp](../../../../../include/crown/frontend/bind.hpp), [src/frontend/bind.cpp](../../../../../src/frontend/bind.cpp), [src/frontend/sql_rows.cpp](../../../../../src/frontend/sql_rows.cpp), [src/frontend/aggregate.cpp](../../../../../src/frontend/aggregate.cpp), [src/frontend/parser.cpp](../../../../../src/frontend/parser.cpp), [src/frontend/parser_detail.hpp](../../../../../src/frontend/parser_detail.hpp), [include/crown/resource/allocator.hpp](../../../../../include/crown/resource/allocator.hpp), [include/crown/resource/ownership.hpp](../../../../../include/crown/resource/ownership.hpp), [include/crown/resource/text.hpp](../../../../../include/crown/resource/text.hpp) |

## B0031

[Lines 277–287](../../../../../src/frontend/sql_aggregate.cpp#L277); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
  void source_projection(pg_query_SelectStmt* source) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Project source targets with a bounded same-arena leaf read lifetime instead of unsafe clone calls. |
| inputs / outputs | Clear source targets/groups; each new ResTarget points at the original kernel ColumnRef leaf. |
| invariants | FROM/JOIN/WHERE stay actual; leaves still have original names. Source AST is deparsed once before any remap and has no later reader/serializer. |
| ownership | All nodes share arena lifetime; resulting source SQL and real factory metadata become independently owned before kernel mutation. |
| failure | Checked node/name allocation failure stops before deparse; no DeepClone/DeepCopy call can corrupt/drop a subtree. |
| cost | O(N) source target metadata and names, zero extra ColumnRef leaf copies. |
| Design | [build/verification/w06-sql-aggregate-compiler-repair-v2/design.md](../../../../../build/verification/w06-sql-aggregate-compiler-repair-v2/design.md), [build/verification/w06-sql-aggregate-compiler-repair-v2/oom-contract.md](../../../../../build/verification/w06-sql-aggregate-compiler-repair-v2/oom-contract.md), [build/verification/w06-sql-aggregate-compiler-repair-v2/receiving-findings.md](../../../../../build/verification/w06-sql-aggregate-compiler-repair-v2/receiving-findings.md), [build/verification/w06-sql-aggregate-compiler-repair-v2/private-contribution-port.md](../../../../../build/verification/w06-sql-aggregate-compiler-repair-v2/private-contribution-port.md), [build/verification/w06-sql-aggregate-compiler-repair-v2/source/pinned-libpg-query/protobuf/pg_query.upb.h](../../../../../build/verification/w06-sql-aggregate-compiler-repair-v2/source/pinned-libpg-query/protobuf/pg_query.upb.h), [build/verification/w06-sql-aggregate-compiler-repair-v2/source/pinned-libpg-query/vendor/upb/upb/generated_code_support.h](../../../../../build/verification/w06-sql-aggregate-compiler-repair-v2/source/pinned-libpg-query/vendor/upb/upb/generated_code_support.h), [build/verification/w06-sql-aggregate-compiler-repair-v2/source/pinned-libpg-query/vendor/upb/upb.c](../../../../../build/verification/w06-sql-aggregate-compiler-repair-v2/source/pinned-libpg-query/vendor/upb/upb.c), Refactor.md:1325-1333, [docs/sql_aggregate_binding.md §Group identity and nullable decoding](../../../../sql_aggregate_binding.md), [docs/sql_aggregate_binding.md §Foreign AST ownership and costs](../../../../sql_aggregate_binding.md), [docs/sql_aggregate_binding.md §Scope and identity](../../../../sql_aggregate_binding.md), [include/crown/frontend/sql_rows.hpp](../../../../../include/crown/frontend/sql_rows.hpp), [include/crown/frontend/aggregate.hpp](../../../../../include/crown/frontend/aggregate.hpp), [include/crown/frontend/bind.hpp](../../../../../include/crown/frontend/bind.hpp), [src/frontend/bind.cpp](../../../../../src/frontend/bind.cpp), [src/frontend/sql_rows.cpp](../../../../../src/frontend/sql_rows.cpp), [src/frontend/aggregate.cpp](../../../../../src/frontend/aggregate.cpp), [src/frontend/parser.cpp](../../../../../src/frontend/parser.cpp), [src/frontend/parser_detail.hpp](../../../../../src/frontend/parser_detail.hpp), [include/crown/resource/allocator.hpp](../../../../../include/crown/resource/allocator.hpp), [include/crown/resource/ownership.hpp](../../../../../include/crown/resource/ownership.hpp), [include/crown/resource/text.hpp](../../../../../include/crown/resource/text.hpp) |

## B0032

[Lines 288–294](../../../../../src/frontend/sql_aggregate.cpp#L288); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
  void remap(pg_query_Node* node, std::size_t column) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Remap kernel refs only after the source AST read phase and both genuine source bindings finish. |
| inputs / outputs | Kernel leaf and genuine physical-origin canonical index become synthetic cN field. |
| invariants | Same physical origin/type gets same index; normalized equality never merges different origins. No source AST serialization remains. |
| ownership | Kernel synthesized names live in arena; bound source SQL/programs own their independent data despite discarded AST leaf aliases. |
| failure | Checked allocation/work failure precedes kernel publication. |
| cost | Small field/node/name work per ref. |
| Design | [build/verification/w06-sql-aggregate-compiler-repair-v2/design.md](../../../../../build/verification/w06-sql-aggregate-compiler-repair-v2/design.md), [build/verification/w06-sql-aggregate-compiler-repair-v2/oom-contract.md](../../../../../build/verification/w06-sql-aggregate-compiler-repair-v2/oom-contract.md), [build/verification/w06-sql-aggregate-compiler-repair-v2/receiving-findings.md](../../../../../build/verification/w06-sql-aggregate-compiler-repair-v2/receiving-findings.md), [build/verification/w06-sql-aggregate-compiler-repair-v2/private-contribution-port.md](../../../../../build/verification/w06-sql-aggregate-compiler-repair-v2/private-contribution-port.md), [include/crown/frontend/bind.hpp](../../../../../include/crown/frontend/bind.hpp), src/frontend/bind.cpp:270-285,396-456,550-574, src/frontend/sql_rows.cpp:438-447,559-568, [src/frontend/aggregate.cpp](../../../../../src/frontend/aggregate.cpp), Refactor.md:1325-1333, [docs/sql_aggregate_binding.md §Group identity and nullable decoding](../../../../sql_aggregate_binding.md), [docs/sql_aggregate_binding.md §Foreign AST ownership and costs](../../../../sql_aggregate_binding.md), [docs/sql_aggregate_binding.md §Scope and identity](../../../../sql_aggregate_binding.md), [include/crown/frontend/sql_rows.hpp](../../../../../include/crown/frontend/sql_rows.hpp), [include/crown/frontend/aggregate.hpp](../../../../../include/crown/frontend/aggregate.hpp), [src/frontend/bind.cpp](../../../../../src/frontend/bind.cpp), [src/frontend/sql_rows.cpp](../../../../../src/frontend/sql_rows.cpp), [src/frontend/parser.cpp](../../../../../src/frontend/parser.cpp), [src/frontend/parser_detail.hpp](../../../../../src/frontend/parser_detail.hpp), [include/crown/resource/allocator.hpp](../../../../../include/crown/resource/allocator.hpp), [include/crown/resource/ownership.hpp](../../../../../include/crown/resource/ownership.hpp), [include/crown/resource/text.hpp](../../../../../include/crown/resource/text.hpp) |

## B0033

[Lines 295–301](../../../../../src/frontend/sql_aggregate.cpp#L295); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
  void kernel_source(pg_query_SelectStmt* kernel) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Replace kernel FROM/WHERE after source/value/origin binding. |
| inputs / outputs | One compiler-owned synthetic input RangeVar replaces source predicates/FROM. |
| invariants | Actual synthetic schema was grounded from admitted source types; no-FROM kernel stays FROM-empty pending authenticated coordinator bootstrap. |
| ownership | Names/nodes belong to arena; original source has no remaining AST read. |
| failure | Checked allocation/work failure is private; no sequence or row trust bypass. |
| cost | Constant AST replacement and name bytes. |
| Design | [build/verification/w06-sql-aggregate-compiler-repair-v2/design.md](../../../../../build/verification/w06-sql-aggregate-compiler-repair-v2/design.md), [build/verification/w06-sql-aggregate-compiler-repair-v2/oom-contract.md](../../../../../build/verification/w06-sql-aggregate-compiler-repair-v2/oom-contract.md), [build/verification/w06-sql-aggregate-compiler-repair-v2/receiving-findings.md](../../../../../build/verification/w06-sql-aggregate-compiler-repair-v2/receiving-findings.md), [build/verification/w06-sql-aggregate-compiler-repair-v2/private-contribution-port.md](../../../../../build/verification/w06-sql-aggregate-compiler-repair-v2/private-contribution-port.md), [include/crown/frontend/bind.hpp](../../../../../include/crown/frontend/bind.hpp), src/frontend/bind.cpp:270-285,396-456,550-574, src/frontend/sql_rows.cpp:438-447,559-568, [src/frontend/aggregate.cpp](../../../../../src/frontend/aggregate.cpp), Refactor.md:1325-1333, [docs/sql_aggregate_binding.md §Group identity and nullable decoding](../../../../sql_aggregate_binding.md), [docs/sql_aggregate_binding.md §Foreign AST ownership and costs](../../../../sql_aggregate_binding.md), [docs/sql_aggregate_binding.md §Scope and identity](../../../../sql_aggregate_binding.md), [include/crown/frontend/sql_rows.hpp](../../../../../include/crown/frontend/sql_rows.hpp), [include/crown/frontend/aggregate.hpp](../../../../../include/crown/frontend/aggregate.hpp), [src/frontend/bind.cpp](../../../../../src/frontend/bind.cpp), [src/frontend/sql_rows.cpp](../../../../../src/frontend/sql_rows.cpp), [src/frontend/parser.cpp](../../../../../src/frontend/parser.cpp), [src/frontend/parser_detail.hpp](../../../../../src/frontend/parser_detail.hpp), [include/crown/resource/allocator.hpp](../../../../../include/crown/resource/allocator.hpp), [include/crown/resource/ownership.hpp](../../../../../include/crown/resource/ownership.hpp), [include/crown/resource/text.hpp](../../../../../include/crown/resource/text.hpp) |

## B0034

[Lines 302–305](../../../../../src/frontend/sql_aggregate.cpp#L302); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
 public:
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Construct the private compiler over authenticated synchronous inputs. |
| inputs / outputs | Account, SqlSyntax, Catalog and options are borrowed into members; ordinary arena is already owned. |
| invariants | Only the public original-SQL factory constructs this implementation; no caller BoundSql route. |
| ownership | Inputs survive run; output owns its independently funded metadata. |
| failure | Cold arena construction allocation can propagate before run. |
| cost | Constant bindings plus normal cold arena initialization. |
| Design | [build/verification/w06-sql-aggregate-compiler-repair-v2/design.md](../../../../../build/verification/w06-sql-aggregate-compiler-repair-v2/design.md), [build/verification/w06-sql-aggregate-compiler-repair-v2/private-contribution-port.md](../../../../../build/verification/w06-sql-aggregate-compiler-repair-v2/private-contribution-port.md), [build/verification/w06-contract-assessment-v1/assessment.md](../../../../../build/verification/w06-contract-assessment-v1/assessment.md), Refactor.md:1317-1327, [build/verification/w06-sql-aggregate-compiler-repair-v2/source/pinned-libpg-query/pg_query.h](../../../../../build/verification/w06-sql-aggregate-compiler-repair-v2/source/pinned-libpg-query/pg_query.h), [build/verification/w06-sql-aggregate-compiler-repair-v2/source/pinned-libpg-query/protobuf/pg_query.upb.h](../../../../../build/verification/w06-sql-aggregate-compiler-repair-v2/source/pinned-libpg-query/protobuf/pg_query.upb.h), [build/verification/w06-sql-aggregate-compiler-repair-v2/source/pinned-libpg-query/vendor/upb/upb/generated_code_support.h](../../../../../build/verification/w06-sql-aggregate-compiler-repair-v2/source/pinned-libpg-query/vendor/upb/upb/generated_code_support.h), [build/verification/w06-sql-aggregate-compiler-repair-v2/source/pinned-libpg-query/vendor/upb/upb.c](../../../../../build/verification/w06-sql-aggregate-compiler-repair-v2/source/pinned-libpg-query/vendor/upb/upb.c), [build/verification/w06-sql-aggregate-compiler-repair-v2/source/pinned-libpg-query/Makefile](../../../../../build/verification/w06-sql-aggregate-compiler-repair-v2/source/pinned-libpg-query/Makefile), Refactor.md:1325-1333, [docs/sql_aggregate_binding.md §Group identity and nullable decoding](../../../../sql_aggregate_binding.md), [docs/sql_aggregate_binding.md §Foreign AST ownership and costs](../../../../sql_aggregate_binding.md), [docs/sql_aggregate_binding.md §Scope and identity](../../../../sql_aggregate_binding.md), [include/crown/frontend/sql_rows.hpp](../../../../../include/crown/frontend/sql_rows.hpp), [include/crown/frontend/aggregate.hpp](../../../../../include/crown/frontend/aggregate.hpp), [include/crown/frontend/bind.hpp](../../../../../include/crown/frontend/bind.hpp), [src/frontend/bind.cpp](../../../../../src/frontend/bind.cpp), [src/frontend/sql_rows.cpp](../../../../../src/frontend/sql_rows.cpp), [src/frontend/aggregate.cpp](../../../../../src/frontend/aggregate.cpp), [src/frontend/parser.cpp](../../../../../src/frontend/parser.cpp), [src/frontend/parser_detail.hpp](../../../../../src/frontend/parser_detail.hpp), [include/crown/resource/allocator.hpp](../../../../../include/crown/resource/allocator.hpp), [include/crown/resource/ownership.hpp](../../../../../include/crown/resource/ownership.hpp), [include/crown/resource/text.hpp](../../../../../include/crown/resource/text.hpp) |

## B0035

[Lines 306–415](../../../../../src/frontend/sql_aggregate.cpp#L306); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
  SqlAggregateBindResult run() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Compile with original physical grouping identity and safe independent decode lifecycle. |
| inputs / outputs | Original SQL becomes two checked decodes, scoped source SQL, real row factory, additional genuine bind_sql, origin-keyed kernel inputs, real kernel factory and receiver-owned binding. |
| invariants | Identical source SQL/Catalog/options.source.binding reach both genuine binds. Full type matches; using_value rejects; decoder equality remains only value information. Source AST has no read after its final deparse; kernel binds once. |
| ownership | Extra BoundSql is local cold workspace; actual origins/decoders/SQL/image/child programs use the original receiver. Native wire/arena lifetimes cover all reads. |
| failure | Source/origin/kernel/resource/status failures release all private data; existing ungrouped_column rejects the three reproduced invalid queries; no clone/copy APIs or partial program escape. |
| cost | Extra real cold parse/bind reported by bound.work; O(N log K) physical map, N remaps, K decode/head coverage and image bytes; no runtime per-row parse/grant. |
| Design | [build/verification/w06-sql-aggregate-compiler-repair-v2/design.md](../../../../../build/verification/w06-sql-aggregate-compiler-repair-v2/design.md), [build/verification/w06-sql-aggregate-compiler-repair-v2/oom-contract.md](../../../../../build/verification/w06-sql-aggregate-compiler-repair-v2/oom-contract.md), [build/verification/w06-sql-aggregate-compiler-repair-v2/receiving-findings.md](../../../../../build/verification/w06-sql-aggregate-compiler-repair-v2/receiving-findings.md), [build/verification/w06-sql-aggregate-compiler-repair-v2/private-contribution-port.md](../../../../../build/verification/w06-sql-aggregate-compiler-repair-v2/private-contribution-port.md), [include/crown/frontend/bind.hpp](../../../../../include/crown/frontend/bind.hpp), src/frontend/bind.cpp:270-285,396-456,550-574, src/frontend/sql_rows.cpp:438-447,559-568, [src/frontend/aggregate.cpp](../../../../../src/frontend/aggregate.cpp), [include/crown/resource/ownership.hpp](../../../../../include/crown/resource/ownership.hpp), [include/crown/resource/allocator.hpp](../../../../../include/crown/resource/allocator.hpp), [include/crown/resource/text.hpp](../../../../../include/crown/resource/text.hpp), Refactor.md:1325-1333, [docs/sql_aggregate_binding.md §Group identity and nullable decoding](../../../../sql_aggregate_binding.md), [docs/sql_aggregate_binding.md §Foreign AST ownership and costs](../../../../sql_aggregate_binding.md), [docs/sql_aggregate_binding.md §Scope and identity](../../../../sql_aggregate_binding.md), [include/crown/frontend/sql_rows.hpp](../../../../../include/crown/frontend/sql_rows.hpp), [include/crown/frontend/aggregate.hpp](../../../../../include/crown/frontend/aggregate.hpp), [src/frontend/bind.cpp](../../../../../src/frontend/bind.cpp), [src/frontend/sql_rows.cpp](../../../../../src/frontend/sql_rows.cpp), [src/frontend/parser.cpp](../../../../../src/frontend/parser.cpp), [src/frontend/parser_detail.hpp](../../../../../src/frontend/parser_detail.hpp) |

## B0036

[Lines 416–418](../../../../../src/frontend/sql_aggregate.cpp#L416); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
};
}  // namespace detail
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Close private compiler scope without adding another runtime publication mechanism. |
| inputs / outputs | Imports, declarations, comments, closure or spacing in the exact stated block. |
| invariants | No SQL admission, plan authority, output publication or execution claim from this scaffolding. |
| ownership | No new executable ownership beyond declarations explicitly described in surrounding cards. |
| failure | No runtime failure is handled by these lines. |
| cost | No runtime work from comments/spacing/declarations. |
| Design | [build/verification/w06-sql-aggregate-compiler-repair-v2/design.md](../../../../../build/verification/w06-sql-aggregate-compiler-repair-v2/design.md), [build/verification/w06-sql-aggregate-compiler-repair-v2/private-contribution-port.md](../../../../../build/verification/w06-sql-aggregate-compiler-repair-v2/private-contribution-port.md), [build/verification/w06-contract-assessment-v1/assessment.md](../../../../../build/verification/w06-contract-assessment-v1/assessment.md), Refactor.md:1317-1327, Refactor.md:1325-1333, [docs/sql_aggregate_binding.md §Group identity and nullable decoding](../../../../sql_aggregate_binding.md), [docs/sql_aggregate_binding.md §Foreign AST ownership and costs](../../../../sql_aggregate_binding.md), [docs/sql_aggregate_binding.md §Scope and identity](../../../../sql_aggregate_binding.md), [include/crown/frontend/sql_rows.hpp](../../../../../include/crown/frontend/sql_rows.hpp), [include/crown/frontend/aggregate.hpp](../../../../../include/crown/frontend/aggregate.hpp), [include/crown/frontend/bind.hpp](../../../../../include/crown/frontend/bind.hpp), [src/frontend/bind.cpp](../../../../../src/frontend/bind.cpp), [src/frontend/sql_rows.cpp](../../../../../src/frontend/sql_rows.cpp), [src/frontend/aggregate.cpp](../../../../../src/frontend/aggregate.cpp), [src/frontend/parser.cpp](../../../../../src/frontend/parser.cpp), [src/frontend/parser_detail.hpp](../../../../../src/frontend/parser_detail.hpp), [include/crown/resource/allocator.hpp](../../../../../include/crown/resource/allocator.hpp), [include/crown/resource/ownership.hpp](../../../../../include/crown/resource/ownership.hpp), [include/crown/resource/text.hpp](../../../../../include/crown/resource/text.hpp) |

## B0037

[Lines 419–435](../../../../../src/frontend/sql_aggregate.cpp#L419); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
SqlAggregateProgram SqlAggregateProgram::freeze(const resource::MemoryAccount& account, const SqlAggregateProgram& source)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Import authentic composed compiler binding once into the runtime receiving account. |
| inputs / outputs | Account + genuine SqlAggregateProgram -&gt; shared same-account or receiver copy with genuine source/kernel freeze. |
| invariants | Copies exact original/binary binding, typed value-only origin/decode/reference maps, six identities, flags and historic work; no parser/rebind or fabricated descriptors. |
| ownership | All Text, nested immutable programs/vectors/control receive one account; source initial constants and aggregate literal/name views are rebased by genuine child freezes. |
| failure | Empty account/handle, import/allocation limit propagates; old handle unchanged and incomplete receiving state released. |
| cost | Same account O(1) no allocation; foreign cold linear metadata/text copy plus actual child freezes, under original receiving cap; work() remains historic provenance. |
| Design | src/frontend/sql_aggregate.cpp:112, src/frontend/sql_rows.cpp:514, [src/frontend/aggregate.cpp](../../../../../src/frontend/aggregate.cpp), [build/verification/w06-sql-aggregate-runtime-design-v1/cost-and-lifetime.md](../../../../../build/verification/w06-sql-aggregate-runtime-design-v1/cost-and-lifetime.md), src/frontend/sql_aggregate.cpp:419, [docs/sql_aggregate_runtime.md](../../../../sql_aggregate_runtime.md), [docs/sql_aggregate_binding.md](../../../../sql_aggregate_binding.md), [docs/aggregates.md](../../../../aggregates.md) |

## B0039

[Lines 437–440](../../../../../src/frontend/sql_aggregate.cpp#L437); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
const SqlAggregateProgram::Data& SqlAggregateProgram::data() const {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Reject empty/default/moved-from composition handles. |
| inputs / outputs | Return immutable Data only when data_ is present. |
| invariants | All public borrowed accessors use this same check. |
| ownership | Returned reference borrows this surviving handle. |
| failure | invalid_sql_aggregate_program occurs before a reference returns. |
| cost | Constant. |
| Design | [build/verification/w06-sql-aggregate-compiler-repair-v2/design.md](../../../../../build/verification/w06-sql-aggregate-compiler-repair-v2/design.md), [build/verification/w06-sql-aggregate-compiler-repair-v2/private-contribution-port.md](../../../../../build/verification/w06-sql-aggregate-compiler-repair-v2/private-contribution-port.md), [build/verification/w06-contract-assessment-v1/assessment.md](../../../../../build/verification/w06-contract-assessment-v1/assessment.md), Refactor.md:1317-1327, [include/crown/frontend/sql_rows.hpp](../../../../../include/crown/frontend/sql_rows.hpp), [include/crown/frontend/aggregate.hpp](../../../../../include/crown/frontend/aggregate.hpp), [src/frontend/sql_rows.cpp](../../../../../src/frontend/sql_rows.cpp), [src/frontend/aggregate.cpp](../../../../../src/frontend/aggregate.cpp), Refactor.md:1325-1333, [docs/sql_aggregate_binding.md §Group identity and nullable decoding](../../../../sql_aggregate_binding.md), [docs/sql_aggregate_binding.md §Foreign AST ownership and costs](../../../../sql_aggregate_binding.md), [docs/sql_aggregate_binding.md §Scope and identity](../../../../sql_aggregate_binding.md), [include/crown/frontend/bind.hpp](../../../../../include/crown/frontend/bind.hpp), [src/frontend/bind.cpp](../../../../../src/frontend/bind.cpp), [src/frontend/parser.cpp](../../../../../src/frontend/parser.cpp), [src/frontend/parser_detail.hpp](../../../../../src/frontend/parser_detail.hpp), [include/crown/resource/allocator.hpp](../../../../../include/crown/resource/allocator.hpp), [include/crown/resource/ownership.hpp](../../../../../include/crown/resource/ownership.hpp), [include/crown/resource/text.hpp](../../../../../include/crown/resource/text.hpp) |

## B0040

[Lines 441–441](../../../../../src/frontend/sql_aggregate.cpp#L441); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::string_view SqlAggregateProgram::original_sql() const & { return data().original.view(); }
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Expose exact original SQL text. |
| inputs / outputs | Valid handle enters original_sql; returns AccountedText-backed string_view. |
| invariants | Borrow requires a surviving lvalue handle; comments/spacing are preserved. |
| ownership | Reads immutable Data; views borrow a surviving handle and value results own only inline metadata. |
| failure | Empty handle rejects via data(); no allocation or state mutation on valid access. |
| cost | Constant getter; no source/result clone. |
| Design | [build/verification/w06-sql-aggregate-compiler-repair-v2/design.md](../../../../../build/verification/w06-sql-aggregate-compiler-repair-v2/design.md), [build/verification/w06-sql-aggregate-compiler-repair-v2/private-contribution-port.md](../../../../../build/verification/w06-sql-aggregate-compiler-repair-v2/private-contribution-port.md), [build/verification/w06-contract-assessment-v1/assessment.md](../../../../../build/verification/w06-contract-assessment-v1/assessment.md), Refactor.md:1317-1327, [include/crown/frontend/sql_rows.hpp](../../../../../include/crown/frontend/sql_rows.hpp), [include/crown/frontend/aggregate.hpp](../../../../../include/crown/frontend/aggregate.hpp), [src/frontend/sql_rows.cpp](../../../../../src/frontend/sql_rows.cpp), [src/frontend/aggregate.cpp](../../../../../src/frontend/aggregate.cpp), Refactor.md:1325-1333, [docs/sql_aggregate_binding.md §Group identity and nullable decoding](../../../../sql_aggregate_binding.md), [docs/sql_aggregate_binding.md §Foreign AST ownership and costs](../../../../sql_aggregate_binding.md), [docs/sql_aggregate_binding.md §Scope and identity](../../../../sql_aggregate_binding.md), [include/crown/frontend/bind.hpp](../../../../../include/crown/frontend/bind.hpp), [src/frontend/bind.cpp](../../../../../src/frontend/bind.cpp), [src/frontend/parser.cpp](../../../../../src/frontend/parser.cpp), [src/frontend/parser_detail.hpp](../../../../../src/frontend/parser_detail.hpp), [include/crown/resource/allocator.hpp](../../../../../include/crown/resource/allocator.hpp), [include/crown/resource/ownership.hpp](../../../../../include/crown/resource/ownership.hpp), [include/crown/resource/text.hpp](../../../../../include/crown/resource/text.hpp) |

## B0041

[Lines 442–442](../../../../../src/frontend/sql_aggregate.cpp#L442); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
const SqlRowsProgram& SqlAggregateProgram::source_program() const & { return data().source; }
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Expose actual derived plain-bag source factory handle. |
| inputs / outputs | Valid handle enters source_program; returns const SqlRowsProgram reference. |
| invariants | A copied handle owns real metadata; no edited core export is accepted as authority. |
| ownership | Reads immutable Data; views borrow a surviving handle and value results own only inline metadata. |
| failure | Empty handle rejects via data(); no allocation or state mutation on valid access. |
| cost | Constant getter; no source/result clone. |
| Design | [build/verification/w06-sql-aggregate-compiler-repair-v2/design.md](../../../../../build/verification/w06-sql-aggregate-compiler-repair-v2/design.md), [build/verification/w06-sql-aggregate-compiler-repair-v2/private-contribution-port.md](../../../../../build/verification/w06-sql-aggregate-compiler-repair-v2/private-contribution-port.md), [build/verification/w06-contract-assessment-v1/assessment.md](../../../../../build/verification/w06-contract-assessment-v1/assessment.md), Refactor.md:1317-1327, [include/crown/frontend/sql_rows.hpp](../../../../../include/crown/frontend/sql_rows.hpp), [include/crown/frontend/aggregate.hpp](../../../../../include/crown/frontend/aggregate.hpp), [src/frontend/sql_rows.cpp](../../../../../src/frontend/sql_rows.cpp), [src/frontend/aggregate.cpp](../../../../../src/frontend/aggregate.cpp), Refactor.md:1325-1333, [docs/sql_aggregate_binding.md §Group identity and nullable decoding](../../../../sql_aggregate_binding.md), [docs/sql_aggregate_binding.md §Foreign AST ownership and costs](../../../../sql_aggregate_binding.md), [docs/sql_aggregate_binding.md §Scope and identity](../../../../sql_aggregate_binding.md), [include/crown/frontend/bind.hpp](../../../../../include/crown/frontend/bind.hpp), [src/frontend/bind.cpp](../../../../../src/frontend/bind.cpp), [src/frontend/parser.cpp](../../../../../src/frontend/parser.cpp), [src/frontend/parser_detail.hpp](../../../../../src/frontend/parser_detail.hpp), [include/crown/resource/allocator.hpp](../../../../../include/crown/resource/allocator.hpp), [include/crown/resource/ownership.hpp](../../../../../include/crown/resource/ownership.hpp), [include/crown/resource/text.hpp](../../../../../include/crown/resource/text.hpp) |

## B0042

[Lines 443–443](../../../../../src/frontend/sql_aggregate.cpp#L443); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
const AggregateProgram& SqlAggregateProgram::kernel_program() const & { return data().kernel; }
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Expose actual synthetic-input aggregate factory handle. |
| inputs / outputs | Valid handle enters kernel_program; returns const AggregateProgram reference. |
| invariants | Actual immutable argument/group/output descriptors remain authority; static input is unseeded here. |
| ownership | Reads immutable Data; views borrow a surviving handle and value results own only inline metadata. |
| failure | Empty handle rejects via data(); no allocation or state mutation on valid access. |
| cost | Constant getter; no source/result clone. |
| Design | [build/verification/w06-sql-aggregate-compiler-repair-v2/design.md](../../../../../build/verification/w06-sql-aggregate-compiler-repair-v2/design.md), [build/verification/w06-sql-aggregate-compiler-repair-v2/private-contribution-port.md](../../../../../build/verification/w06-sql-aggregate-compiler-repair-v2/private-contribution-port.md), [build/verification/w06-contract-assessment-v1/assessment.md](../../../../../build/verification/w06-contract-assessment-v1/assessment.md), Refactor.md:1317-1327, [include/crown/frontend/sql_rows.hpp](../../../../../include/crown/frontend/sql_rows.hpp), [include/crown/frontend/aggregate.hpp](../../../../../include/crown/frontend/aggregate.hpp), [src/frontend/sql_rows.cpp](../../../../../src/frontend/sql_rows.cpp), [src/frontend/aggregate.cpp](../../../../../src/frontend/aggregate.cpp), Refactor.md:1325-1333, [docs/sql_aggregate_binding.md §Group identity and nullable decoding](../../../../sql_aggregate_binding.md), [docs/sql_aggregate_binding.md §Foreign AST ownership and costs](../../../../sql_aggregate_binding.md), [docs/sql_aggregate_binding.md §Scope and identity](../../../../sql_aggregate_binding.md), [include/crown/frontend/bind.hpp](../../../../../include/crown/frontend/bind.hpp), [src/frontend/bind.cpp](../../../../../src/frontend/bind.cpp), [src/frontend/parser.cpp](../../../../../src/frontend/parser.cpp), [src/frontend/parser_detail.hpp](../../../../../src/frontend/parser_detail.hpp), [include/crown/resource/allocator.hpp](../../../../../include/crown/resource/allocator.hpp), [include/crown/resource/ownership.hpp](../../../../../include/crown/resource/ownership.hpp), [include/crown/resource/text.hpp](../../../../../include/crown/resource/text.hpp) |

## B0043

[Lines 444–444](../../../../../src/frontend/sql_aggregate.cpp#L444); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::size_t SqlAggregateProgram::native_fields() const { return data().native_fields; }
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Expose actual source head width. |
| inputs / outputs | Valid handle enters native_fields; returns size_t value. |
| invariants | Compile-time decoder coverage used this actual immutable source export; no tree authority follows. |
| ownership | Reads immutable Data; views borrow a surviving handle and value results own only inline metadata. |
| failure | Empty handle rejects via data(); no allocation or state mutation on valid access. |
| cost | Constant getter; no source/result clone. |
| Design | [build/verification/w06-sql-aggregate-compiler-repair-v2/design.md](../../../../../build/verification/w06-sql-aggregate-compiler-repair-v2/design.md), [build/verification/w06-sql-aggregate-compiler-repair-v2/private-contribution-port.md](../../../../../build/verification/w06-sql-aggregate-compiler-repair-v2/private-contribution-port.md), [build/verification/w06-contract-assessment-v1/assessment.md](../../../../../build/verification/w06-contract-assessment-v1/assessment.md), Refactor.md:1317-1327, [include/crown/frontend/sql_rows.hpp](../../../../../include/crown/frontend/sql_rows.hpp), [include/crown/frontend/aggregate.hpp](../../../../../include/crown/frontend/aggregate.hpp), [src/frontend/sql_rows.cpp](../../../../../src/frontend/sql_rows.cpp), [src/frontend/aggregate.cpp](../../../../../src/frontend/aggregate.cpp), Refactor.md:1325-1333, [docs/sql_aggregate_binding.md §Group identity and nullable decoding](../../../../sql_aggregate_binding.md), [docs/sql_aggregate_binding.md §Foreign AST ownership and costs](../../../../sql_aggregate_binding.md), [docs/sql_aggregate_binding.md §Scope and identity](../../../../sql_aggregate_binding.md), [include/crown/frontend/bind.hpp](../../../../../include/crown/frontend/bind.hpp), [src/frontend/bind.cpp](../../../../../src/frontend/bind.cpp), [src/frontend/parser.cpp](../../../../../src/frontend/parser.cpp), [src/frontend/parser_detail.hpp](../../../../../src/frontend/parser_detail.hpp), [include/crown/resource/allocator.hpp](../../../../../include/crown/resource/allocator.hpp), [include/crown/resource/ownership.hpp](../../../../../include/crown/resource/ownership.hpp), [include/crown/resource/text.hpp](../../../../../include/crown/resource/text.hpp) |

## B0044

[Lines 445–445](../../../../../src/frontend/sql_aggregate.cpp#L445); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::span<const SqlAggregateInput> SqlAggregateProgram::inputs() const & { return data().inputs; }
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Borrow the origin-preserving logical input decoder records. |
| inputs / outputs | Returns immutable SqlAggregateInput span containing actual BoundColumn origin plus separate type/normalized decoder. |
| invariants | Equal decoders across different origins are allowed; grouping admission never follows value equality. |
| ownership | Span borrows a surviving handle; payload/constant owners remain actual source facts/program. |
| failure | Empty handle rejects; no allocation or metadata mutation. |
| cost | Constant view, no payload clone. |
| Design | [build/verification/w06-sql-aggregate-compiler-repair-v2/design.md](../../../../../build/verification/w06-sql-aggregate-compiler-repair-v2/design.md), [build/verification/w06-sql-aggregate-compiler-repair-v2/oom-contract.md](../../../../../build/verification/w06-sql-aggregate-compiler-repair-v2/oom-contract.md), [build/verification/w06-sql-aggregate-compiler-repair-v2/receiving-findings.md](../../../../../build/verification/w06-sql-aggregate-compiler-repair-v2/receiving-findings.md), [build/verification/w06-sql-aggregate-compiler-repair-v2/private-contribution-port.md](../../../../../build/verification/w06-sql-aggregate-compiler-repair-v2/private-contribution-port.md), [include/crown/frontend/bind.hpp](../../../../../include/crown/frontend/bind.hpp), src/frontend/bind.cpp:270-285,396-456,550-574, src/frontend/sql_rows.cpp:438-447,559-568, [src/frontend/aggregate.cpp](../../../../../src/frontend/aggregate.cpp), Refactor.md:1325-1333, [docs/sql_aggregate_binding.md §Group identity and nullable decoding](../../../../sql_aggregate_binding.md), [docs/sql_aggregate_binding.md §Foreign AST ownership and costs](../../../../sql_aggregate_binding.md), [docs/sql_aggregate_binding.md §Scope and identity](../../../../sql_aggregate_binding.md), [include/crown/frontend/sql_rows.hpp](../../../../../include/crown/frontend/sql_rows.hpp), [include/crown/frontend/aggregate.hpp](../../../../../include/crown/frontend/aggregate.hpp), [src/frontend/bind.cpp](../../../../../src/frontend/bind.cpp), [src/frontend/sql_rows.cpp](../../../../../src/frontend/sql_rows.cpp), [src/frontend/parser.cpp](../../../../../src/frontend/parser.cpp), [src/frontend/parser_detail.hpp](../../../../../src/frontend/parser_detail.hpp), [include/crown/resource/allocator.hpp](../../../../../include/crown/resource/allocator.hpp), [include/crown/resource/ownership.hpp](../../../../../include/crown/resource/ownership.hpp), [include/crown/resource/text.hpp](../../../../../include/crown/resource/text.hpp) |

## B0045

[Lines 446–446](../../../../../src/frontend/sql_aggregate.cpp#L446); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::span<const std::size_t> SqlAggregateProgram::reference_columns() const & { return data().reference_columns; }
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Borrow original-reference to physical-origin canonical input mapping. |
| inputs / outputs | Deterministic original traversal indices map to canonical origin/type indices. |
| invariants | Qualified/unqualified same-origin refs share an index; equality/null/join normalization cannot merge different origins. |
| ownership | Mapping array is receiver-owned; view borrows immutable program. |
| failure | Empty handle rejects; no caller-edited map is accepted as authority. |
| cost | Constant view. |
| Design | [build/verification/w06-sql-aggregate-compiler-repair-v2/design.md](../../../../../build/verification/w06-sql-aggregate-compiler-repair-v2/design.md), [build/verification/w06-sql-aggregate-compiler-repair-v2/oom-contract.md](../../../../../build/verification/w06-sql-aggregate-compiler-repair-v2/oom-contract.md), [build/verification/w06-sql-aggregate-compiler-repair-v2/receiving-findings.md](../../../../../build/verification/w06-sql-aggregate-compiler-repair-v2/receiving-findings.md), [build/verification/w06-sql-aggregate-compiler-repair-v2/private-contribution-port.md](../../../../../build/verification/w06-sql-aggregate-compiler-repair-v2/private-contribution-port.md), [include/crown/frontend/bind.hpp](../../../../../include/crown/frontend/bind.hpp), src/frontend/bind.cpp:270-285,396-456,550-574, src/frontend/sql_rows.cpp:438-447,559-568, [src/frontend/aggregate.cpp](../../../../../src/frontend/aggregate.cpp), Refactor.md:1325-1333, [docs/sql_aggregate_binding.md §Group identity and nullable decoding](../../../../sql_aggregate_binding.md), [docs/sql_aggregate_binding.md §Foreign AST ownership and costs](../../../../sql_aggregate_binding.md), [docs/sql_aggregate_binding.md §Scope and identity](../../../../sql_aggregate_binding.md), [include/crown/frontend/sql_rows.hpp](../../../../../include/crown/frontend/sql_rows.hpp), [include/crown/frontend/aggregate.hpp](../../../../../include/crown/frontend/aggregate.hpp), [src/frontend/bind.cpp](../../../../../src/frontend/bind.cpp), [src/frontend/sql_rows.cpp](../../../../../src/frontend/sql_rows.cpp), [src/frontend/parser.cpp](../../../../../src/frontend/parser.cpp), [src/frontend/parser_detail.hpp](../../../../../src/frontend/parser_detail.hpp), [include/crown/resource/allocator.hpp](../../../../../include/crown/resource/allocator.hpp), [include/crown/resource/ownership.hpp](../../../../../include/crown/resource/ownership.hpp), [include/crown/resource/text.hpp](../../../../../include/crown/resource/text.hpp) |

## B0046

[Lines 447–447](../../../../../src/frontend/sql_aggregate.cpp#L447); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
const SqlAggregateIdentity& SqlAggregateProgram::identity() const & { return data().identity; }
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Expose exact origin-aware family-2 semantic/decode identities. |
| inputs / outputs | Const SqlAggregateIdentity reference contains separate original/catalog/source/kernel/decode/whole hashes. |
| invariants | Decode image binds origin occurrence/column/type and origin policy; family-2 whole binding is distinct from V1. No plan/runtime proof follows. |
| ownership | Inline hashes borrow immutable Data. |
| failure | Empty handle rejects. |
| cost | Constant. |
| Design | [build/verification/w06-sql-aggregate-compiler-repair-v2/design.md](../../../../../build/verification/w06-sql-aggregate-compiler-repair-v2/design.md), [build/verification/w06-sql-aggregate-compiler-repair-v2/oom-contract.md](../../../../../build/verification/w06-sql-aggregate-compiler-repair-v2/oom-contract.md), [build/verification/w06-sql-aggregate-compiler-repair-v2/receiving-findings.md](../../../../../build/verification/w06-sql-aggregate-compiler-repair-v2/receiving-findings.md), [build/verification/w06-sql-aggregate-compiler-repair-v2/private-contribution-port.md](../../../../../build/verification/w06-sql-aggregate-compiler-repair-v2/private-contribution-port.md), [include/crown/frontend/bind.hpp](../../../../../include/crown/frontend/bind.hpp), src/frontend/bind.cpp:270-285,396-456,550-574, src/frontend/sql_rows.cpp:438-447,559-568, [src/frontend/aggregate.cpp](../../../../../src/frontend/aggregate.cpp), Refactor.md:1325-1333, [docs/sql_aggregate_binding.md §Group identity and nullable decoding](../../../../sql_aggregate_binding.md), [docs/sql_aggregate_binding.md §Foreign AST ownership and costs](../../../../sql_aggregate_binding.md), [docs/sql_aggregate_binding.md §Scope and identity](../../../../sql_aggregate_binding.md), [include/crown/frontend/sql_rows.hpp](../../../../../include/crown/frontend/sql_rows.hpp), [include/crown/frontend/aggregate.hpp](../../../../../include/crown/frontend/aggregate.hpp), [src/frontend/bind.cpp](../../../../../src/frontend/bind.cpp), [src/frontend/sql_rows.cpp](../../../../../src/frontend/sql_rows.cpp), [src/frontend/parser.cpp](../../../../../src/frontend/parser.cpp), [src/frontend/parser_detail.hpp](../../../../../src/frontend/parser_detail.hpp), [include/crown/resource/allocator.hpp](../../../../../include/crown/resource/allocator.hpp), [include/crown/resource/ownership.hpp](../../../../../include/crown/resource/ownership.hpp), [include/crown/resource/text.hpp](../../../../../include/crown/resource/text.hpp) |

## B0047

[Lines 448–448](../../../../../src/frontend/sql_aggregate.cpp#L448); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::string_view SqlAggregateProgram::binding_image() const & { return data().binding.view(); }
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Borrow family-2 binary metadata for authenticated recovery rebinding. |
| inputs / outputs | Returns exact CBOR image with actual SQL/catalog/params/schema and origin-aware decoder policy. |
| invariants | Rebind through actual factories and require matching identities; no opaque DTO importer or implicit V1 recovery equivalence. |
| ownership | AccountedText owns bytes; returned view requires a surviving lvalue handle. |
| failure | Empty handle rejects; access is nonallocating. |
| cost | Constant view. |
| Design | [build/verification/w06-sql-aggregate-compiler-repair-v2/design.md](../../../../../build/verification/w06-sql-aggregate-compiler-repair-v2/design.md), [build/verification/w06-sql-aggregate-compiler-repair-v2/oom-contract.md](../../../../../build/verification/w06-sql-aggregate-compiler-repair-v2/oom-contract.md), [build/verification/w06-sql-aggregate-compiler-repair-v2/receiving-findings.md](../../../../../build/verification/w06-sql-aggregate-compiler-repair-v2/receiving-findings.md), [build/verification/w06-sql-aggregate-compiler-repair-v2/private-contribution-port.md](../../../../../build/verification/w06-sql-aggregate-compiler-repair-v2/private-contribution-port.md), [include/crown/frontend/bind.hpp](../../../../../include/crown/frontend/bind.hpp), src/frontend/bind.cpp:270-285,396-456,550-574, src/frontend/sql_rows.cpp:438-447,559-568, [src/frontend/aggregate.cpp](../../../../../src/frontend/aggregate.cpp), Refactor.md:1325-1333, [docs/sql_aggregate_binding.md §Group identity and nullable decoding](../../../../sql_aggregate_binding.md), [docs/sql_aggregate_binding.md §Foreign AST ownership and costs](../../../../sql_aggregate_binding.md), [docs/sql_aggregate_binding.md §Scope and identity](../../../../sql_aggregate_binding.md), [include/crown/frontend/sql_rows.hpp](../../../../../include/crown/frontend/sql_rows.hpp), [include/crown/frontend/aggregate.hpp](../../../../../include/crown/frontend/aggregate.hpp), [src/frontend/bind.cpp](../../../../../src/frontend/bind.cpp), [src/frontend/sql_rows.cpp](../../../../../src/frontend/sql_rows.cpp), [src/frontend/parser.cpp](../../../../../src/frontend/parser.cpp), [src/frontend/parser_detail.hpp](../../../../../src/frontend/parser_detail.hpp), [include/crown/resource/allocator.hpp](../../../../../include/crown/resource/allocator.hpp), [include/crown/resource/ownership.hpp](../../../../../include/crown/resource/ownership.hpp), [include/crown/resource/text.hpp](../../../../../include/crown/resource/text.hpp) |

## B0048

[Lines 449–449](../../../../../src/frontend/sql_aggregate.cpp#L449); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::optional<std::uint64_t> SqlAggregateProgram::static_source_weight() const { return data().static_weight; }
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Expose authenticated zero-occurrence source marker. |
| inputs / outputs | Valid handle enters static_source_weight; returns optional&lt;uint64_t&gt; value. |
| invariants | Present 0/1 comes from actual source contradiction; only coordinator may own singleton bootstrap. |
| ownership | Reads immutable Data; views borrow a surviving handle and value results own only inline metadata. |
| failure | Empty handle rejects via data(); no allocation or state mutation on valid access. |
| cost | Constant getter; no source/result clone. |
| Design | [build/verification/w06-sql-aggregate-compiler-repair-v2/design.md](../../../../../build/verification/w06-sql-aggregate-compiler-repair-v2/design.md), [build/verification/w06-sql-aggregate-compiler-repair-v2/private-contribution-port.md](../../../../../build/verification/w06-sql-aggregate-compiler-repair-v2/private-contribution-port.md), [build/verification/w06-contract-assessment-v1/assessment.md](../../../../../build/verification/w06-contract-assessment-v1/assessment.md), Refactor.md:1317-1327, [include/crown/frontend/sql_rows.hpp](../../../../../include/crown/frontend/sql_rows.hpp), [include/crown/frontend/aggregate.hpp](../../../../../include/crown/frontend/aggregate.hpp), [src/frontend/sql_rows.cpp](../../../../../src/frontend/sql_rows.cpp), [src/frontend/aggregate.cpp](../../../../../src/frontend/aggregate.cpp), Refactor.md:1325-1333, [docs/sql_aggregate_binding.md §Group identity and nullable decoding](../../../../sql_aggregate_binding.md), [docs/sql_aggregate_binding.md §Foreign AST ownership and costs](../../../../sql_aggregate_binding.md), [docs/sql_aggregate_binding.md §Scope and identity](../../../../sql_aggregate_binding.md), [include/crown/frontend/bind.hpp](../../../../../include/crown/frontend/bind.hpp), [src/frontend/bind.cpp](../../../../../src/frontend/bind.cpp), [src/frontend/parser.cpp](../../../../../src/frontend/parser.cpp), [src/frontend/parser_detail.hpp](../../../../../src/frontend/parser_detail.hpp), [include/crown/resource/allocator.hpp](../../../../../include/crown/resource/allocator.hpp), [include/crown/resource/ownership.hpp](../../../../../include/crown/resource/ownership.hpp), [include/crown/resource/text.hpp](../../../../../include/crown/resource/text.hpp) |

## B0049

[Lines 450–450](../../../../../src/frontend/sql_aggregate.cpp#L450); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
SqlAggregateWork SqlAggregateProgram::work() const { return data().work; }
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Expose the actual extra origin bind counter alongside existing separate work. |
| inputs / outputs | Returns SqlAggregateWork with composition/origin_binding/source_normalization/kernel_binding. |
| invariants | Origin counter comes from genuine BoundSql.work; actual row factory internal binding consumption and full cold CPU/allocations remain outside this report. |
| ownership | Returns inline counters by value. |
| failure | Empty handle rejects. |
| cost | Constant. |
| Design | [build/verification/w06-sql-aggregate-compiler-repair-v2/design.md](../../../../../build/verification/w06-sql-aggregate-compiler-repair-v2/design.md), [build/verification/w06-sql-aggregate-compiler-repair-v2/oom-contract.md](../../../../../build/verification/w06-sql-aggregate-compiler-repair-v2/oom-contract.md), [build/verification/w06-sql-aggregate-compiler-repair-v2/receiving-findings.md](../../../../../build/verification/w06-sql-aggregate-compiler-repair-v2/receiving-findings.md), [build/verification/w06-sql-aggregate-compiler-repair-v2/private-contribution-port.md](../../../../../build/verification/w06-sql-aggregate-compiler-repair-v2/private-contribution-port.md), [include/crown/frontend/bind.hpp](../../../../../include/crown/frontend/bind.hpp), src/frontend/bind.cpp:270-285,396-456,550-574, src/frontend/sql_rows.cpp:438-447,559-568, [src/frontend/aggregate.cpp](../../../../../src/frontend/aggregate.cpp), Refactor.md:1325-1333, [docs/sql_aggregate_binding.md §Group identity and nullable decoding](../../../../sql_aggregate_binding.md), [docs/sql_aggregate_binding.md §Foreign AST ownership and costs](../../../../sql_aggregate_binding.md), [docs/sql_aggregate_binding.md §Scope and identity](../../../../sql_aggregate_binding.md), [include/crown/frontend/sql_rows.hpp](../../../../../include/crown/frontend/sql_rows.hpp), [include/crown/frontend/aggregate.hpp](../../../../../include/crown/frontend/aggregate.hpp), [src/frontend/bind.cpp](../../../../../src/frontend/bind.cpp), [src/frontend/sql_rows.cpp](../../../../../src/frontend/sql_rows.cpp), [src/frontend/parser.cpp](../../../../../src/frontend/parser.cpp), [src/frontend/parser_detail.hpp](../../../../../src/frontend/parser_detail.hpp), [include/crown/resource/allocator.hpp](../../../../../include/crown/resource/allocator.hpp), [include/crown/resource/ownership.hpp](../../../../../include/crown/resource/ownership.hpp), [include/crown/resource/text.hpp](../../../../../include/crown/resource/text.hpp) |

## B0050

[Lines 451–451](../../../../../src/frontend/sql_aggregate.cpp#L451); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
const resource::MemoryAccount& SqlAggregateProgram::account() const & { return data().account; }
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Expose existing receiving account. |
| inputs / outputs | Valid handle enters account; returns const MemoryAccount reference. |
| invariants | No fresh limit or grant is created; rvalue account borrowing is deleted. |
| ownership | Reads immutable Data; views borrow a surviving handle and value results own only inline metadata. |
| failure | Empty handle rejects via data(); no allocation or state mutation on valid access. |
| cost | Constant getter; no source/result clone. |
| Design | [build/verification/w06-sql-aggregate-compiler-repair-v2/design.md](../../../../../build/verification/w06-sql-aggregate-compiler-repair-v2/design.md), [build/verification/w06-sql-aggregate-compiler-repair-v2/private-contribution-port.md](../../../../../build/verification/w06-sql-aggregate-compiler-repair-v2/private-contribution-port.md), [build/verification/w06-contract-assessment-v1/assessment.md](../../../../../build/verification/w06-contract-assessment-v1/assessment.md), Refactor.md:1317-1327, [include/crown/frontend/sql_rows.hpp](../../../../../include/crown/frontend/sql_rows.hpp), [include/crown/frontend/aggregate.hpp](../../../../../include/crown/frontend/aggregate.hpp), [src/frontend/sql_rows.cpp](../../../../../src/frontend/sql_rows.cpp), [src/frontend/aggregate.cpp](../../../../../src/frontend/aggregate.cpp), Refactor.md:1325-1333, [docs/sql_aggregate_binding.md §Group identity and nullable decoding](../../../../sql_aggregate_binding.md), [docs/sql_aggregate_binding.md §Foreign AST ownership and costs](../../../../sql_aggregate_binding.md), [docs/sql_aggregate_binding.md §Scope and identity](../../../../sql_aggregate_binding.md), [include/crown/frontend/bind.hpp](../../../../../include/crown/frontend/bind.hpp), [src/frontend/bind.cpp](../../../../../src/frontend/bind.cpp), [src/frontend/parser.cpp](../../../../../src/frontend/parser.cpp), [src/frontend/parser_detail.hpp](../../../../../src/frontend/parser_detail.hpp), [include/crown/resource/allocator.hpp](../../../../../include/crown/resource/allocator.hpp), [include/crown/resource/ownership.hpp](../../../../../include/crown/resource/ownership.hpp), [include/crown/resource/text.hpp](../../../../../include/crown/resource/text.hpp) |

## B0051

[Lines 452–462](../../../../../src/frontend/sql_aggregate.cpp#L452); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
SqlAggregateBindResult bind_sql_aggregate_into(const resource::MemoryAccount& account, std::string_view sql,
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Authenticate original SQL then enter only the actual composed compiler. |
| inputs / outputs | Existing account, original SQL, Catalog/options return opaque program or BindingDiagnostic. |
| invariants | parse_sql authenticates before rewrite; parser-contract errors propagate; only narrow semantic Error is translated; no BoundSql/raw-row admission route. |
| ownership | One existing receiver funds retained programs; original parsed/cold compiler workspace unwinds before return. |
| failure | Invalid account MemoryFailure and allocations propagate; syntax returns original coordinates; derived semantic errors use their own cleared locations. |
| cost | One original parse plus actual private compile pipeline under declared limits. |
| Design | [build/verification/w06-sql-aggregate-compiler-repair-v2/design.md](../../../../../build/verification/w06-sql-aggregate-compiler-repair-v2/design.md), [build/verification/w06-sql-aggregate-compiler-repair-v2/private-contribution-port.md](../../../../../build/verification/w06-sql-aggregate-compiler-repair-v2/private-contribution-port.md), [build/verification/w06-contract-assessment-v1/assessment.md](../../../../../build/verification/w06-contract-assessment-v1/assessment.md), Refactor.md:1317-1327, [include/crown/frontend/sql_rows.hpp](../../../../../include/crown/frontend/sql_rows.hpp), [include/crown/frontend/aggregate.hpp](../../../../../include/crown/frontend/aggregate.hpp), [src/frontend/sql_rows.cpp](../../../../../src/frontend/sql_rows.cpp), [src/frontend/aggregate.cpp](../../../../../src/frontend/aggregate.cpp), Refactor.md:1325-1333, [docs/sql_aggregate_binding.md §Group identity and nullable decoding](../../../../sql_aggregate_binding.md), [docs/sql_aggregate_binding.md §Foreign AST ownership and costs](../../../../sql_aggregate_binding.md), [docs/sql_aggregate_binding.md §Scope and identity](../../../../sql_aggregate_binding.md), [include/crown/frontend/bind.hpp](../../../../../include/crown/frontend/bind.hpp), [src/frontend/bind.cpp](../../../../../src/frontend/bind.cpp), [src/frontend/parser.cpp](../../../../../src/frontend/parser.cpp), [src/frontend/parser_detail.hpp](../../../../../src/frontend/parser_detail.hpp), [include/crown/resource/allocator.hpp](../../../../../include/crown/resource/allocator.hpp), [include/crown/resource/ownership.hpp](../../../../../include/crown/resource/ownership.hpp), [include/crown/resource/text.hpp](../../../../../include/crown/resource/text.hpp) |

## B0052

[Lines 463–465](../../../../../src/frontend/sql_aggregate.cpp#L463); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
SqlAggregateBindResult bind_sql_aggregate(std::string_view sql, const Catalog& catalog, const SqlAggregateBindOptions& options) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Provide one standalone finite receiving account for authentic aggregate composition. |
| inputs / outputs | SQL/Catalog/options delegate to _into after MemoryAccount::create(memory_limit_bytes). |
| invariants | Only this outer standalone call creates a grant; nested child factories are _into. |
| ownership | Returned opaque Data/programs retain the same receiver. |
| failure | Account/parser/factory failures propagate or return existing diagnostic shape; no partial program. |
| cost | One controller plus actual compilation and retained metadata costs. |
| Design | [build/verification/w06-sql-aggregate-compiler-repair-v2/design.md](../../../../../build/verification/w06-sql-aggregate-compiler-repair-v2/design.md), [build/verification/w06-sql-aggregate-compiler-repair-v2/private-contribution-port.md](../../../../../build/verification/w06-sql-aggregate-compiler-repair-v2/private-contribution-port.md), [build/verification/w06-contract-assessment-v1/assessment.md](../../../../../build/verification/w06-contract-assessment-v1/assessment.md), Refactor.md:1317-1327, [include/crown/frontend/sql_rows.hpp](../../../../../include/crown/frontend/sql_rows.hpp), [include/crown/frontend/aggregate.hpp](../../../../../include/crown/frontend/aggregate.hpp), [src/frontend/sql_rows.cpp](../../../../../src/frontend/sql_rows.cpp), [src/frontend/aggregate.cpp](../../../../../src/frontend/aggregate.cpp), [include/crown/resource/ownership.hpp](../../../../../include/crown/resource/ownership.hpp), [include/crown/resource/allocator.hpp](../../../../../include/crown/resource/allocator.hpp), [include/crown/resource/text.hpp](../../../../../include/crown/resource/text.hpp), Refactor.md:1325-1333, [docs/sql_aggregate_binding.md §Group identity and nullable decoding](../../../../sql_aggregate_binding.md), [docs/sql_aggregate_binding.md §Foreign AST ownership and costs](../../../../sql_aggregate_binding.md), [docs/sql_aggregate_binding.md §Scope and identity](../../../../sql_aggregate_binding.md), [include/crown/frontend/bind.hpp](../../../../../include/crown/frontend/bind.hpp), [src/frontend/bind.cpp](../../../../../src/frontend/bind.cpp), [src/frontend/parser.cpp](../../../../../src/frontend/parser.cpp), [src/frontend/parser_detail.hpp](../../../../../src/frontend/parser_detail.hpp) |

## B0053

[Lines 466–466](../../../../../src/frontend/sql_aggregate.cpp#L466); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
}  // namespace crown::frontend
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Close frontend scope; no runtime or acceptance behavior is introduced. |
| inputs / outputs | Imports, declarations, comments, closure or spacing in the exact stated block. |
| invariants | No SQL admission, plan authority, output publication or execution claim from this scaffolding. |
| ownership | No new executable ownership beyond declarations explicitly described in surrounding cards. |
| failure | No runtime failure is handled by these lines. |
| cost | No runtime work from comments/spacing/declarations. |
| Design | [build/verification/w06-sql-aggregate-compiler-repair-v2/design.md](../../../../../build/verification/w06-sql-aggregate-compiler-repair-v2/design.md), [build/verification/w06-sql-aggregate-compiler-repair-v2/private-contribution-port.md](../../../../../build/verification/w06-sql-aggregate-compiler-repair-v2/private-contribution-port.md), [build/verification/w06-contract-assessment-v1/assessment.md](../../../../../build/verification/w06-contract-assessment-v1/assessment.md), Refactor.md:1317-1327, Refactor.md:1325-1333, [docs/sql_aggregate_binding.md §Group identity and nullable decoding](../../../../sql_aggregate_binding.md), [docs/sql_aggregate_binding.md §Foreign AST ownership and costs](../../../../sql_aggregate_binding.md), [docs/sql_aggregate_binding.md §Scope and identity](../../../../sql_aggregate_binding.md), [include/crown/frontend/sql_rows.hpp](../../../../../include/crown/frontend/sql_rows.hpp), [include/crown/frontend/aggregate.hpp](../../../../../include/crown/frontend/aggregate.hpp), [include/crown/frontend/bind.hpp](../../../../../include/crown/frontend/bind.hpp), [src/frontend/bind.cpp](../../../../../src/frontend/bind.cpp), [src/frontend/sql_rows.cpp](../../../../../src/frontend/sql_rows.cpp), [src/frontend/aggregate.cpp](../../../../../src/frontend/aggregate.cpp), [src/frontend/parser.cpp](../../../../../src/frontend/parser.cpp), [src/frontend/parser_detail.hpp](../../../../../src/frontend/parser_detail.hpp), [include/crown/resource/allocator.hpp](../../../../../include/crown/resource/allocator.hpp), [include/crown/resource/ownership.hpp](../../../../../include/crown/resource/ownership.hpp), [include/crown/resource/text.hpp](../../../../../include/crown/resource/text.hpp) |
