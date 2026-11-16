#include "crown/recovery/sql_aggregate_descriptor.hpp"
#include "crown/ir/digest.hpp"
#include "crown/io/catalog.hpp"
#include "crown/io/physical.hpp"
#include "crown/io/tree.hpp"
#include "crown/planner/lower.hpp"
#include "crown/resource/ownership.hpp"
#include "sql_aggregate_cbor.hpp"
#include "../io/json.hpp"
#include "../planner/compiled_source.hpp"

namespace crown::recovery::sql_aggregate {
namespace {
using namespace binary_detail;
using Json = io::Json;
using Options = runtime::sql_aggregate::Options;
constexpr std::string_view magic="CROWNAD2";
std::string_view view(const std::vector<std::uint8_t>& bytes) {
  return {reinterpret_cast<const char*>(bytes.data()),bytes.size()};
}
Json limit(std::optional<std::uint64_t> value) { return value?Json(*value):Json{}; }
std::uint64_t number(const Json& value) { return io::detail::unsigned_integer(value,"R2 descriptor"); }
std::optional<std::uint64_t> limit(const Json& value) { return value.is_null()?std::nullopt:std::optional{number(value)}; }
Json options_image(const Options& options) {
  const auto& n=options.source.native;const auto& w=options.source.source_work_limit;
  return {{"count_limit",options.count_limit},{"group_work",limit(options.group_work_limit)},
      {"memory_bytes",options.memory_limit_bytes},{"capture_changes",options.capture_changes},
      {"source_work",Json::array({w.structural_steps,w.scalar_fields,w.scalar_bytes,w.pointer_slots,w.link_actions})},
      {"native",{{"work",limit(n.work_limit)},{"multiplicity_limit",n.multiplicity_limit},
          {"memory_bytes",n.memory_limit_bytes},{"capture_changes",n.capture_changes},{"capture_events",n.capture_events}}}};
}
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
void finite(const AdmissionLimits& limits) {
  const auto& b=limits.binding;
  require(limits.lowering.work_limit && limits.lowering.identity.work_limit && b.work_limit && b.source.work_limit &&
      b.source.binding.limits.work_limit && b.kernel.limits.work_limit,ImageFault::limit);
  require(b.parsing.ast_depth<=256 && b.source.binding.limits.recursion_limit<=256 &&
      b.kernel.limits.recursion_limit<=256,ImageFault::limit);
}
void schema_limits(const frontend::SqlAggregateProgram& program,const DescriptorLimits& limits) {
  const auto sources=program.source_program().sources();require(sources.size()<=limits.image.tables,ImageFault::limit);
  for(const auto& source:sources)require(source.columns.size()<=limits.image.fields,ImageFault::limit);
  require(program.kernel_program().group_columns().size()<=limits.image.fields &&
      program.kernel_program().outputs().size()<=limits.image.fields,ImageFault::limit);
}
// Finite producer caps already within the host caps bound actual construction.
// Otherwise first check this deterministic input under a finite host allowance;
// the runtime still uses the original options, including disabled producer caps.
void lower_check(const frontend::SqlAggregateProgram& program,const FreeConnexTree& tree,
    const PhysicalOptions& physical,const AdmissionLimits& limits) {
  finite(limits);const auto& stored=physical.limits;
  if(stored.work_limit && stored.identity.work_limit && *stored.work_limit<=*limits.lowering.work_limit &&
      *stored.identity.work_limit<=*limits.lowering.identity.work_limit)return;
  const auto core=program.source_program().export_core();
  static_cast<void>(planner::lower_tree(core.catalog,core.query,tree,physical,limits.lowering));
}
// Count/validate before the receiving allocation; all codec passes share work.
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
} // namespace

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
namespace detail {
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
} // namespace detail

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
Admitted admit_into(const resource::MemoryAccount& account,frontend::SqlAggregateProgram program,
    const FreeConnexTree& tree,const PhysicalOptions& physical,Options options,const AdmissionLimits& limits) {
  Budget budget{limits.descriptor.image};return detail::DescriptorFactory::admit(account,std::move(program),tree,physical,options,limits,budget);
}
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
const Descriptor::Data& Descriptor::data() const {
  require(bool(data_),ImageFault::binding);return *data_;
}
const frontend::SqlAggregateProgram& Descriptor::program() const & { return data().program; }
const CompiledProgram& Descriptor::native_program() const & { return data().native; }
const runtime::weighted::Binding& Descriptor::native_binding() const & { return data().binding; }
const Options& Descriptor::options() const & { return data().normal; }
const Hash& Descriptor::sha256() const & { return data().digest; }
std::string_view Descriptor::bytes() const & { const auto& b=data().bytes;return {b.data(),b.size()}; }
} // namespace crown::recovery::sql_aggregate
