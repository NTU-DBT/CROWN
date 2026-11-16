#include "crown/frontend/sql_aggregate.hpp"
#include "parser_detail.hpp"
#include "crown/api/error.hpp"
#include "crown/io/catalog.hpp"
#include "crown/ir/digest.hpp"
#include "crown/resource/ownership.hpp"
#include "crown/resource/text.hpp"
#include <algorithm>
#include <cstring>
#include <map>
#include <new>
#include <pg_query.h>
#include <protobuf/pg_query.upb.h>

namespace crown::frontend {
namespace {
static_assert(PG_VERSION_NUM == 180006, "composed SQL AST requires the pinned PostgreSQL 18.6 contract");
constexpr std::string_view family = "CROWN-SQL-AGGREGATE;2";
constexpr std::string_view parser_archive = "2d3486cf6a9d3955b53e66235db39d62b54216c820cd392ab66dc842c5b1316d";
constexpr std::string_view input_table = "crown_aggregate_input";
template<class T> using Items = std::vector<T, resource::MemoryAllocator<T>>;
template<class T> auto allocator(const resource::MemoryAccount& account) {
  return resource::MemoryAllocator<T>(account, resource::MemoryPurpose::immutable_metadata,
      {resource::MemoryOwnerKind::immutable_metadata, 0});
}
[[noreturn]] void fail(const char* code, const char* message) { throw Error(code, message); }
template<class T> T* checked(T* value) { if (!value) throw std::bad_alloc{}; return value; }
std::string_view text(upb_StringView value) { return {value.data, value.size}; }

// Native parser/deparser and upb storage are cold workspace, matching existing
// frontend conventions. Every returned native result/arena is freed on exit.
struct ProtoOwner {
  PgQueryProtobufParseResult value{};
  explicit ProtoOwner(const char* sql) {
    const std::lock_guard lock(parser_detail::mutex()); value = pg_query_parse_protobuf(sql);
  }
  void require() const {
    if (value.error) {
      const std::string_view message = value.error->message ? value.error->message : "protobuf parser failed";
      if (message.find("memory") != std::string::npos || message.find("stack depth") != std::string::npos)
        fail("resource_limit", "protobuf parser exhausted cold workspace or depth");
      fail("parser_contract", "authenticated SQL did not parse through the pinned protobuf API");
    }
    if (!value.parse_tree.data || !value.parse_tree.len) fail("parser_contract", "protobuf parser returned no authenticated tree");
  }
  ~ProtoOwner() { pg_query_free_protobuf_parse_result(value); }
  ProtoOwner(const ProtoOwner&) = delete;
  ProtoOwner& operator=(const ProtoOwner&) = delete;
};
struct Arena {
  upb_Arena* value = checked(upb_Arena_New());
  ~Arena() { upb_Arena_Free(value); }
  Arena() = default;
  Arena(const Arena&) = delete;
  Arena& operator=(const Arena&) = delete;
};
struct DeparseOwner {
  PgQueryDeparseResult value{};
  explicit DeparseOwner(PgQueryProtobuf bytes) {
    const std::lock_guard lock(parser_detail::mutex()); value = pg_query_deparse_protobuf(bytes);
  }
  ~DeparseOwner() { pg_query_free_deparse_result(value); }
  DeparseOwner(const DeparseOwner&) = delete;
  DeparseOwner& operator=(const DeparseOwner&) = delete;
};
BindingDiagnostic derived(BindingDiagnostic value, std::string_view stage) {
  value.phase = std::string(stage) + '/' + value.phase;
  // Derived SQL locations are not byte positions in the user's original SQL.
  value.diagnostic.byte_offset.reset(); value.diagnostic.character_position.reset();
  value.diagnostic.line.reset(); value.diagnostic.column.reset(); return value;
}
io::Json type_image(const SqlType& type) {
  return {{"kind", static_cast<int>(type.kind)}, {"nullable", type.nullable},
      {"decimal", type.decimal ? io::Json::array({type.decimal->precision, type.decimal->scale}) : io::Json{}}};
}
std::string cbor(const io::Json& value) {
  const auto bytes = io::Json::to_cbor(value);
  return {reinterpret_cast<const char*>(bytes.data()), bytes.size()};
}
// SQL grouping identity is the genuine binder's physical occurrence/column,
// never a later equality class, constant slot or equal native payload value.
struct OriginKey {
  OccurrenceId occurrence;
  ColumnId column;
  SqlType type;
  auto operator<=>(const OriginKey&) const = default;
};
OriginKey origin_key(const BoundSql& bound, std::size_t output) {
  const auto id = bound.outputs.at(output).expression;
  const auto& expression = bound.expressions.at(id.value);
  if (const auto* column = std::get_if<BoundColumn>(&expression.node))
    return {column->occurrence, column->column, expression.type};
  if (const auto* operation = std::get_if<BoundOperation>(&expression.node);
      operation && operation->operation == SqlOperator::using_value)
    fail("unsupported_aggregate_join_column", "merged USING/NATURAL aggregate references require separate grouping identity admission");
  fail("aggregate_composition_contract", "source ColumnRef did not resolve to a physical SQL column");
}
ScalarType physical_type(SqlKind kind) {
  switch (kind) {
    case SqlKind::int64: return ScalarType::int64;
    case SqlKind::string: return ScalarType::string;
    case SqlKind::boolean: return ScalarType::boolean;
    case SqlKind::date: return ScalarType::date;
    case SqlKind::decimal: return ScalarType::decimal;
    case SqlKind::int32: case SqlKind::unknown:
      fail("unsupported_aggregate_input_type", "catalog cannot represent this aggregate logical input type");
  }
  fail("aggregate_composition_contract", "unknown aggregate logical input kind");
}
}  // namespace

struct SqlAggregateProgram::Data {
  resource::MemoryAccount account;
  resource::AccountedText original, binding;
  SqlRowsProgram source;
  AggregateProgram kernel;
  Items<SqlAggregateInput> inputs;
  Items<std::size_t> reference_columns;
  SqlAggregateIdentity identity{};
  SqlAggregateWork work;
  std::size_t native_fields = 0;
  std::optional<std::uint64_t> static_weight;
  explicit Data(const resource::MemoryAccount& owner)
      : account(owner), inputs(allocator<SqlAggregateInput>(owner)), reference_columns(allocator<std::size_t>(owner)) {}
};

namespace detail {
class SqlAggregateCompiler {
  using Json = nlohmann::json;
  const resource::MemoryAccount& account_;
  const SqlSyntax& original_;
  const Catalog& catalog_;
  const SqlAggregateBindOptions& options_;
  Arena arena_;
  std::vector<pg_query_Node*> references_;
  std::uint64_t work_ = 0;

  void charge(std::uint64_t amount = 1) {
    if (amount > UINT64_MAX - work_ || (options_.work_limit && amount > *options_.work_limit - work_))
      fail("resource_limit", "SQL aggregate composition work limit exceeded");
    work_ += amount;
  }
  void keys(const Json& node, std::initializer_list<std::string_view> allowed) {
    charge();
    if (!node.is_object()) fail("parser_contract", "expected authenticated SQL AST object");
    for (const auto& [key, unused] : node.items()) {
      static_cast<void>(unused); charge();
      if (std::find(allowed.begin(), allowed.end(), key) == allowed.end())
        fail("unsupported_sql", "unsupported composed aggregate SQL clause");
    }
  }
  void preflight() {
    charge(original_.source.size());
    const auto& statement = original_.ast.at("stmts")[0].at("stmt");
    if (!statement.contains("SelectStmt")) fail("unsupported_statement", "aggregate composition requires SELECT");
    const auto& select = statement.at("SelectStmt");
    keys(select, {"targetList", "fromClause", "whereClause", "groupClause", "limitOption", "op"});
    if (select.value("op", std::string{"SETOP_NONE"}) != "SETOP_NONE" ||
        select.value("limitOption", std::string{"LIMIT_OPTION_DEFAULT"}) != "LIMIT_OPTION_DEFAULT")
      fail("unsupported_sql", "aggregate set/limit operations are not admitted");
    if (!select.contains("targetList") || select.at("targetList").empty())
      fail("unsupported_sql", "aggregate composition requires an aggregate output");
    if (select.at("targetList").size() > options_.kernel.limits.expression_limit)
      fail("resource_limit", "too many aggregate composition outputs");
    for (const auto& node : select.at("targetList")) {
      const auto& target = node.at("ResTarget"); keys(target, {"name", "val", "location"});
      if (target.at("val").contains("FuncCall"))
        keys(target.at("val").at("FuncCall"), {"funcname", "args", "agg_star", "agg_distinct", "funcformat", "location"});
    }
  }
  pg_query_SelectStmt* select(pg_query_ParseResult* tree) {
    std::size_t count = 0; auto stmts = pg_query_ParseResult_mutable_stmts(tree, &count);
    if (pg_query_ParseResult_version(tree) != PG_VERSION_NUM || count != 1 || !stmts)
      fail("parser_contract", "unexpected protobuf SQL envelope");
    auto node = pg_query_RawStmt_mutable_stmt(stmts[0], arena_.value);
    if (!node || pg_query_Node_node_case(node) != pg_query_Node_node_select_stmt)
      fail("parser_contract", "authenticated SELECT changed protobuf node kind");
    return checked(pg_query_Node_mutable_select_stmt(node, arena_.value));
  }
  upb_StringView own_text(std::string_view value) {
    charge(value.size()); auto bytes = checked(static_cast<char*>(upb_Arena_Malloc(arena_.value, value.size() + 1)));
    std::memcpy(bytes, value.data(), value.size()); bytes[value.size()] = '\0';
    return upb_StringView_FromDataAndSize(bytes, value.size());
  }
  pg_query_ParseResult* decode(PgQueryProtobuf wire) {
    auto tree = checked(pg_query_ParseResult_new(arena_.value));
    const auto status = upb_Decode(wire.data, wire.len, reinterpret_cast<upb_Message*>(tree),
        &pg_0query__ParseResult_msg_init, nullptr, 0, arena_.value);
    if (status == kUpb_DecodeStatus_OutOfMemory) throw std::bad_alloc{};
    if (status == kUpb_DecodeStatus_MaxDepthExceeded) fail("resource_limit", "SQL protobuf decoding exceeded its cold depth limit");
    if (status != kUpb_DecodeStatus_Ok) fail("parser_contract", "authenticated protobuf tree failed decoding");
    return tree;
  }
  void reference(pg_query_Node* node) {
    const auto column = pg_query_Node_column_ref(node);
    std::size_t count = 0; const auto fields = pg_query_ColumnRef_fields(column, &count);
    if (count < 1 || count > 2) fail("unsupported_qualification", "aggregate columns use name or alias.name");
    for (std::size_t i = 0; i < count; ++i)
      if (pg_query_Node_node_case(fields[i]) != pg_query_Node_node_string)
        fail("unsupported_argument", "wildcard/grouping expressions are not aggregate columns");
    if (references_.size() >= options_.kernel.limits.expression_limit)
      fail("resource_limit", "too many aggregate composition references");
    references_.push_back(node);
  }
  void argument(pg_query_Node* node, std::size_t depth = 0) {
    charge();
    if (depth >= options_.kernel.limits.recursion_limit)
      fail("resource_limit", "aggregate composition argument depth exceeded");
    switch (pg_query_Node_node_case(node)) {
      case pg_query_Node_node_column_ref: reference(node); return;
      case pg_query_Node_node_a_const: return;
      case pg_query_Node_node_type_cast: {
        auto cast = pg_query_Node_mutable_type_cast(node, arena_.value);
        if (!cast || !pg_query_TypeCast_has_arg(cast)) fail("parser_contract", "aggregate cast lacks its argument");
        argument(checked(pg_query_TypeCast_mutable_arg(cast, arena_.value)), depth + 1); return;
      }
      case pg_query_Node_node_param_ref:
        fail("unsupported_argument", "aggregate argument parameters are not admitted; source predicates may bind parameters");
      default: fail("unsupported_expression", "aggregate arguments must be columns or constants with admitted casts; computed/cross-relation arguments are unsupported");
    }
  }
  std::string column_name(const pg_query_Node* node) {
    std::size_t size = 0; const auto fields = pg_query_ColumnRef_fields(pg_query_Node_column_ref(node), &size);
    if (!size || pg_query_Node_node_case(fields[size - 1]) != pg_query_Node_node_string)
      fail("unsupported_argument", "aggregate output is not a named input column");
    return std::string(text(pg_query_String_sval(pg_query_Node_string(fields[size - 1]))));
  }
  void collect(pg_query_SelectStmt* kernel) {
    std::size_t size = 0; auto groups = pg_query_SelectStmt_mutable_group_clause(kernel, &size);
    for (std::size_t i = 0; i < size; ++i) {
      charge();
      if (pg_query_Node_node_case(groups[i]) != pg_query_Node_node_column_ref)
        fail("unsupported_expression", "GROUP BY requires resolved input columns");
      reference(groups[i]);
    }
    auto targets = pg_query_SelectStmt_mutable_target_list(kernel, &size);
    for (std::size_t i = 0; i < size; ++i) {
      charge();
      if (pg_query_Node_node_case(targets[i]) != pg_query_Node_node_res_target)
        fail("parser_contract", "authenticated target changed protobuf node kind");
      auto target = checked(pg_query_Node_mutable_res_target(targets[i], arena_.value));
      auto node = checked(pg_query_ResTarget_mutable_val(target, arena_.value)); std::string name;
      if (pg_query_Node_node_case(node) == pg_query_Node_node_func_call) {
        auto call = pg_query_Node_mutable_func_call(node, arena_.value);
        std::size_t names = 0; const auto function = pg_query_FuncCall_funcname(call, &names);
        if (names != 1 || pg_query_Node_node_case(function[0]) != pg_query_Node_node_string)
          fail("unsupported_function", "aggregate functions must be unqualified COUNT, SUM or AVG");
        name = text(pg_query_String_sval(pg_query_Node_string(function[0])));
        std::size_t arguments = 0; auto args = pg_query_FuncCall_mutable_args(call, &arguments);
        for (std::size_t a = 0; a < arguments; ++a) argument(args[a]);
      } else {
        if (pg_query_Node_node_case(node) != pg_query_Node_node_column_ref)
          fail("unsupported_expression", "aggregate outputs require group columns or COUNT/SUM/AVG");
        reference(node); name = column_name(node);
      }
      // Freeze original default names before cN remapping changes column text.
      if (text(pg_query_ResTarget_name(target)).empty()) pg_query_ResTarget_set_name(target, own_text(name));
    }
  }
  std::string deparse(pg_query_ParseResult* tree) {
    charge(); char* bytes = nullptr; std::size_t size = 0;
    const auto status = upb_Encode(reinterpret_cast<const upb_Message*>(tree),
        &pg_0query__ParseResult_msg_init, 0, arena_.value, &bytes, &size);
    if (status != kUpb_EncodeStatus_Ok) fail("resource_limit", "SQL protobuf encoding exceeded cold workspace/depth limits");
    DeparseOwner owner({size, bytes});
    if (owner.value.error) {
      const std::string_view message = owner.value.error->message ? owner.value.error->message : "deparser failed";
      if (message.find("memory") != std::string_view::npos || message.find("stack depth") != std::string_view::npos)
        fail("resource_limit", "SQL deparser exhausted cold workspace or depth");
      fail("parser_contract", "pinned SQL deparser rejected a derived AST");
    }
    if (!owner.value.query) fail("parser_contract", "SQL deparser returned no derived query");
    const auto length = std::strlen(owner.value.query);
    if (length > options_.derived_sql_bytes) fail("resource_limit", "derived aggregate SQL exceeds its byte limit");
    charge(length); return std::string(owner.value.query, length);
  }
  void source_projection(pg_query_SelectStmt* source) {
    pg_query_SelectStmt_clear_target_list(source); pg_query_SelectStmt_clear_group_clause(source);
    for (std::size_t i = 0; i < references_.size(); ++i) {
      charge(); auto node = checked(pg_query_SelectStmt_add_target_list(source, arena_.value));
      auto target = checked(pg_query_Node_mutable_res_target(node, arena_.value));
      pg_query_ResTarget_set_name(target, own_text("crown_ref_" + std::to_string(i)));
      // Same-arena leaf borrow ends at source deparse. The source SQL/factory
      // metadata is complete before kernel remap; this AST is never read again.
      pg_query_ResTarget_set_val(target, references_[i]);
    }
  }
  void remap(pg_query_Node* node, std::size_t column) {
    charge(); auto ref = checked(pg_query_Node_mutable_column_ref(node, arena_.value));
    auto fields = checked(pg_query_ColumnRef_resize_fields(ref, 1, arena_.value));
    fields[0] = checked(pg_query_Node_new(arena_.value));
    auto value = checked(pg_query_Node_mutable_string(fields[0], arena_.value));
    pg_query_String_set_sval(value, own_text("c" + std::to_string(column)));
  }
  void kernel_source(pg_query_SelectStmt* kernel) {
    pg_query_SelectStmt_clear_where_clause(kernel); pg_query_SelectStmt_clear_from_clause(kernel);
    auto node = checked(pg_query_SelectStmt_add_from_clause(kernel, arena_.value));
    auto table = checked(pg_query_Node_mutable_range_var(node, arena_.value));
    pg_query_RangeVar_set_relname(table, own_text(input_table));
    pg_query_RangeVar_set_inh(table, true); pg_query_RangeVar_set_relpersistence(table, own_text("p"));
  }
 public:
  SqlAggregateCompiler(const resource::MemoryAccount& account, const SqlSyntax& original,
      const Catalog& catalog, const SqlAggregateBindOptions& options)
      : account_(account), original_(original), catalog_(catalog), options_(options) {}
  SqlAggregateBindResult run() {
    preflight(); ProtoOwner native(original_.source.c_str()); native.require();
    // Independent checked wire decodes avoid this pin's unsafe DeepClone/Copy.
    auto kernel_tree = decode(native.value.parse_tree);
    auto kernel_select = select(kernel_tree); collect(kernel_select);
    std::string source_sql;
    {
      auto source_tree = decode(native.value.parse_tree);
      source_projection(select(source_tree)); source_sql = deparse(source_tree);
    } // Last source AST use. Borrowed kernel leaves still have original names.
    auto source_result = bind_sql_rows_into(account_, source_sql, catalog_, options_.source);
    if (auto diagnostic = std::get_if<BindingDiagnostic>(&source_result)) return derived(*diagnostic, "aggregate_source");
    auto source = std::get<SqlRowsProgram>(std::move(source_result));
    if (source.source() != source_sql || source.semantics() != SqlSemantics::bag ||
        source.wrapper() != SqlWrapper::rows || source.outputs().size() != references_.size())
      fail("aggregate_composition_contract", "derived source is not the expected plain logical bag");
    // This is an additional genuine pre-normalization binding, not a DTO
    // reconstruction. Exactly the same SQL/catalog/BindOptions reach the source
    // factory above; actual parameter values remain admitted only by that factory.
    auto origin_result = bind_sql(source_sql, catalog_, options_.source.binding);
    if (auto diagnostic = std::get_if<BindingDiagnostic>(&origin_result)) return derived(*diagnostic, "aggregate_origin");
    const auto& bound = std::get<BoundSql>(origin_result);
    if (bound.source != source_sql || bound.semantics != SqlSemantics::bag ||
        bound.wrapper != SqlWrapper::rows || bound.outputs.size() != source.outputs().size())
      fail("aggregate_composition_contract", "origin binding differs from the genuine source query");
    std::vector<std::size_t> representatives, mapping;
    std::vector<OriginKey> origins;
    std::map<OriginKey, std::size_t> canonical;
    Catalog kernel_catalog{1, {{std::string(input_table), {}}}};
    for (std::size_t i = 0; i < references_.size(); ++i) {
      charge(); const auto& output = source.outputs()[i];
      const auto origin = origin_key(bound, i);
      if (origin.type != output.type) fail("aggregate_composition_contract", "bound physical origin and normalized source SqlType differ");
      const auto [position, inserted] = canonical.emplace(origin, representatives.size());
      const auto column = position->second;
      if (inserted) {
        representatives.push_back(i); origins.push_back(origin);
        kernel_catalog.tables[0].columns.push_back({"c" + std::to_string(column), physical_type(output.type.kind),
            output.type.nullable, Collation::binary, output.type.decimal});
      }
      mapping.push_back(column); remap(references_[i], column);
    }
    kernel_source(kernel_select); const auto kernel_sql = deparse(kernel_tree);
    auto kernel_result = bind_aggregate_sql_into(account_, kernel_sql, kernel_catalog, options_.kernel);
    if (auto diagnostic = std::get_if<BindingDiagnostic>(&kernel_result)) return derived(*diagnostic, "aggregate_kernel");
    auto kernel = std::get<AggregateProgram>(std::move(kernel_result));
    if (!kernel.has_input() || kernel.input_types().size() != representatives.size())
      fail("aggregate_composition_contract", "kernel does not bind the canonical logical source schema");
    auto out = resource::make_accounted_shared<SqlAggregateProgram::Data>(account_, resource::MemoryPurpose::immutable_metadata, account_);
    out->source = std::move(source); out->kernel = std::move(kernel);
    charge(mapping.size()); out->reference_columns.assign(mapping.begin(), mapping.end());
    io::Json decode = io::Json::array();
    for (std::size_t c = 0; c < representatives.size(); ++c) {
      charge(); const auto i = representatives[c]; const auto& output = out->source.outputs()[i];
      if (out->kernel.input_types()[c] != output.type) fail("aggregate_composition_contract", "kernel/source SqlType including NULL differs");
      const auto& origin = origins[c];
      io::Json field{{"type", type_image(output.type)}, {"source_output", i},
          {"occurrence", origin.occurrence.value}, {"column", origin.column.value}};
      if (const auto* value = std::get_if<SqlRowsResultField>(&output.value)) {
        out->inputs.push_back({output.type, {origin.occurrence, origin.column}, i, *value});
        field["payload"] = value->payload; field["presence"] = value->presence ? io::Json(*value->presence) : io::Json{};
      } else if (const auto* value = std::get_if<ExpressionId>(&output.value)) {
        out->inputs.push_back({output.type, {origin.occurrence, origin.column}, i, *value}); field["constant"] = value->value;
      } else fail("aggregate_composition_contract", "EXISTS output cannot feed an aggregate source");
      decode.push_back(std::move(field));
    }
    // Physical-origin inputs cover every actual source head field. For valid source
    // facts, a NULL's payload is the adapter's unique typed zero/default, so
    // discarding that payload on decode cannot merge two distinct native facts.
    out->native_fields = out->source.export_core().query.head.size();
    charge(out->native_fields); std::vector<bool> covered(out->native_fields);
    for (const auto& input : out->inputs) if (const auto* field = std::get_if<SqlRowsResultField>(&input.value)) {
      charge();
      if (field->payload >= covered.size() || (field->presence && *field->presence >= covered.size()))
        fail("aggregate_composition_contract", "source decode field exceeds the actual native head");
      covered[field->payload] = true; if (field->presence) covered[*field->presence] = true;
    }
    if (std::find(covered.begin(), covered.end(), false) != covered.end())
      fail("aggregate_composition_contract", "canonical aggregate decode omits a native source head field");
    charge(original_.source.size());
    out->original = resource::AccountedText::copy_of(account_, original_.source,
        {resource::MemoryOwnerKind::immutable_metadata, 0}, resource::MemoryPurpose::immutable_metadata);
    const auto catalog_image = io::write_catalog_payload(catalog_); const auto kernel_schema = io::write_catalog_payload(kernel_catalog);
    io::Json kernel_binding{{"sql", out->kernel.source()}, {"catalog", kernel_schema}, {"average_scale", out->kernel.average_scale()}};
    io::Json decoder{{"encoding", "nullable-default-payload-head;1"},
        {"identity", "bound-occurrence-column-type;1"}, {"native_fields", out->native_fields},
        {"inputs", std::move(decode)}, {"references", mapping}};
    auto& id = out->identity; id.original_sql = sha256_fixed(original_.source); id.catalog = sha256_fixed(cbor(catalog_image));
    const auto source_key = out->source.source_sha256();
    if (source_key.size() != id.source.size()) fail("aggregate_composition_contract", "source key is not a SHA-256 digest");
    std::copy(source_key.begin(), source_key.end(), id.source.begin());
    id.kernel = sha256_fixed(cbor(kernel_binding)); id.decode = sha256_fixed(cbor(decoder));
    if (out->source.occurrences().empty()) out->static_weight = out->source.contradiction() ? std::uint64_t{0} : std::uint64_t{1};
    Catalog parameter_catalog{1, {{"parameters", options_.source.binding.parameters}}};
    for (std::size_t i = 0; i < parameter_catalog.tables[0].columns.size(); ++i)
      parameter_catalog.tables[0].columns[i].name = "$" + std::to_string(i + 1);
    io::Json parameters = io::Json::array();
    for (const auto& value : options_.source.parameters) parameters.push_back(value ? io::write_scalar(*value) : io::Json{});
    io::Json binding{{"family", family}, {"parser_archive", parser_archive}, {"pg_version", PG_VERSION_NUM},
        {"original_sql", original_.source}, {"catalog", catalog_image}, {"source_sql", out->source.source()},
        {"source_key", source_key}, {"source_contradiction", out->source.contradiction()},
        {"kernel", kernel_binding}, {"decode", decoder},
        {"parameter_declarations", io::write_catalog_payload(parameter_catalog)}, {"parameter_values", parameters},
        {"static_source_weight", out->static_weight ? io::Json(*out->static_weight) : io::Json{}}};
    const auto image = cbor(binding); charge(image.size()); id.binding = sha256_fixed(image);
    out->binding = resource::AccountedText::copy_of(account_, image,
        {resource::MemoryOwnerKind::immutable_metadata, 0}, resource::MemoryPurpose::immutable_metadata);
    out->work = {work_, bound.work, out->source.work(), out->kernel.work()};
    return SqlAggregateProgram(std::move(out));
  }
};
}  // namespace detail

SqlAggregateProgram SqlAggregateProgram::freeze(const resource::MemoryAccount& account, const SqlAggregateProgram& source) {
  if (!account) throw resource::MemoryFailure(resource::MemoryFault::contract);
  const auto& old = source.data();
  if (account.statistics().owner == old.account.statistics().owner) return source;
  auto out = resource::make_accounted_shared<Data>(account, resource::MemoryPurpose::immutable_metadata, account);
  out->original = resource::AccountedText::copy_of(account, old.original.view(),
      {resource::MemoryOwnerKind::immutable_metadata, 0}, resource::MemoryPurpose::immutable_metadata);
  out->binding = resource::AccountedText::copy_of(account, old.binding.view(),
      {resource::MemoryOwnerKind::immutable_metadata, 0}, resource::MemoryPurpose::immutable_metadata);
  out->source = SqlRowsProgram::freeze(account, old.source);
  out->kernel = AggregateProgram::freeze(account, old.kernel);
  out->inputs.assign(old.inputs.begin(), old.inputs.end());
  out->reference_columns.assign(old.reference_columns.begin(), old.reference_columns.end());
  out->identity = old.identity; out->work = old.work; out->native_fields = old.native_fields;
  out->static_weight = old.static_weight;
  return SqlAggregateProgram(std::move(out));
}

const SqlAggregateProgram::Data& SqlAggregateProgram::data() const {
  if (!data_) fail("invalid_sql_aggregate_program", "composed aggregate program handle is empty");
  return *data_;
}
std::string_view SqlAggregateProgram::original_sql() const & { return data().original.view(); }
const SqlRowsProgram& SqlAggregateProgram::source_program() const & { return data().source; }
const AggregateProgram& SqlAggregateProgram::kernel_program() const & { return data().kernel; }
std::size_t SqlAggregateProgram::native_fields() const { return data().native_fields; }
std::span<const SqlAggregateInput> SqlAggregateProgram::inputs() const & { return data().inputs; }
std::span<const std::size_t> SqlAggregateProgram::reference_columns() const & { return data().reference_columns; }
const SqlAggregateIdentity& SqlAggregateProgram::identity() const & { return data().identity; }
std::string_view SqlAggregateProgram::binding_image() const & { return data().binding.view(); }
std::optional<std::uint64_t> SqlAggregateProgram::static_source_weight() const { return data().static_weight; }
SqlAggregateWork SqlAggregateProgram::work() const { return data().work; }
const resource::MemoryAccount& SqlAggregateProgram::account() const & { return data().account; }
SqlAggregateBindResult bind_sql_aggregate_into(const resource::MemoryAccount& account, std::string_view sql,
    const Catalog& catalog, const SqlAggregateBindOptions& options) {
  if (!account) throw resource::MemoryFailure(resource::MemoryFault::contract);
  const auto parsed = parse_sql(sql, options.parsing);
  if (const auto* diagnostic = std::get_if<SqlDiagnostic>(&parsed)) return BindingDiagnostic{"syntax", *diagnostic};
  try { return detail::SqlAggregateCompiler(account, std::get<SqlSyntax>(parsed), catalog, options).run(); }
  catch (const Error& error) {
    if (error.code() == "parser_contract") throw;
    return BindingDiagnostic{"aggregate_composition", {error.code(), error.what(), {}, {}, {}, {}}};
  }
}
SqlAggregateBindResult bind_sql_aggregate(std::string_view sql, const Catalog& catalog, const SqlAggregateBindOptions& options) {
  return bind_sql_aggregate_into(resource::MemoryAccount::create(options.memory_limit_bytes), sql, catalog, options);
}
}  // namespace crown::frontend
