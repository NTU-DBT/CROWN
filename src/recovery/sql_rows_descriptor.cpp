#include "crown/recovery/sql_rows_descriptor.hpp"
#include "crown/ir/digest.hpp"
#include "crown/io/catalog.hpp"
#include "crown/io/physical.hpp"
#include "crown/io/tree.hpp"
#include "crown/planner/lower.hpp"
#include "crown/resource/ownership.hpp"
#include "sql_rows_cbor.hpp"
#include "../io/json.hpp"
#include "../planner/compiled_source.hpp"

namespace crown::recovery::sql_rows {
namespace {
using namespace binary_detail;
using Json = io::Json;
using Options = runtime::sql_rows::Options;
constexpr std::string_view magic="CROWNRD2";
// Same pinned parser archive/PG18.6 AST contract as SQL aggregate composition
// and the project dependency lock. This cold provenance does not change the
// existing SQL-row source key. Parser upgrades need explicit descriptor
// compatibility/new admission rather than relabeling old durable bytes.
constexpr std::string_view parser_archive="2d3486cf6a9d3955b53e66235db39d62b54216c820cd392ab66dc842c5b1316d";
constexpr std::uint64_t pg_version=180006;
std::string_view view(const std::vector<std::uint8_t>& bytes) {
  return {reinterpret_cast<const char*>(bytes.data()),bytes.size()};
}
Json limit(std::optional<std::uint64_t> value) { return value?Json(*value):Json{}; }
std::uint64_t number(const Json& value) { return io::detail::unsigned_integer(value,"R2 descriptor"); }
std::optional<std::uint64_t> limit(const Json& value) { return value.is_null()?std::nullopt:std::optional{number(value)}; }
Json options_image(const Options& options) {
  const auto& n=options.native;const auto& w=options.source_work_limit;
  return {{"source_work",Json::array({w.structural_steps,w.scalar_fields,w.scalar_bytes,w.pointer_slots,w.link_actions})},
      {"native",{{"work",limit(n.work_limit)},{"multiplicity_limit",n.multiplicity_limit},
          {"memory_bytes",n.memory_limit_bytes},{"capture_changes",n.capture_changes},{"capture_events",n.capture_events}}}};
}
Options read_options(const Json& value) {
  io::detail::fields(value,"normal",{"source_work","native"});Options result;
  const auto& w=io::detail::array(value.at("source_work"),"source_work");require(w.size()==5);
  result.source_work_limit={number(w[0]),number(w[1]),number(w[2]),number(w[3]),number(w[4])};
  const auto& native=value.at("native");io::detail::fields(native,"native",{"work","multiplicity_limit","memory_bytes","capture_changes","capture_events"});
  auto& n=result.native;n.work_limit=limit(native.at("work"));n.multiplicity_limit=number(native.at("multiplicity_limit"));
  n.memory_limit_bytes=number(native.at("memory_bytes"));n.capture_changes=native.at("capture_changes").get<bool>();
  n.capture_events=native.at("capture_events").get<bool>();return result;
}
Json recipe(const runtime::sql_rows::SourceSnapshot& source,const Options& options,runtime::sql_rows::OutputLimits output) {
  const auto& native=source.native_program;const auto& binding=source.native_binding;
  const auto core=source.program.export_core();
  return {{"schema_version",1},{"parser_archive",parser_archive},{"pg_version",pg_version},{"records","CROWNRW2;1"},{"arithmetic","checked-nonnegative-bag-sql-rows;1"},
      {"output","nullable-sql-tuple-signed-uint64;1"},{"normal",options_image(options)},
      {"output_limits",{{"rows",output.rows},{"work",output.work}}},
      {"tree",io::write_tree(planner::compiler_source_detail::tree(native.tree()),core.catalog,core.query)},
      {"physical_options",io::write_physical_options(planner::compiler_source_detail::options(native.options()))},
      {"physical_sha256",native.physical_sha256()},{"source_sha256",native.physical_source_sha256()},
      {"weighted_shape_sha256",std::string(binding.shape_sha256.data(),binding.shape_sha256.size())},
      {"weighted_sha256",std::string(binding.weighted_sha256.data(),binding.weighted_sha256.size())},
      {"multiplicity_limit",binding.multiplicity_limit}};
}
void finite(const AdmissionLimits& limits) {
  const auto& b=limits.binding;
  require(limits.lowering.work_limit && limits.lowering.identity.work_limit && b.work_limit &&
      b.binding.limits.work_limit,ImageFault::limit);
  require(b.binding.limits.recursion_limit<=256,ImageFault::limit);
}
void schema_limits(const frontend::SqlRowsProgram& program,const DescriptorLimits& limits) {
  const auto sources=program.sources();require(sources.size()<=limits.image.tables,ImageFault::limit);
  for(const auto& source:sources)require(source.columns.size()<=limits.image.fields,ImageFault::limit);
  require(program.outputs().size()<=limits.image.fields,ImageFault::limit);
}
// Finite producer caps already within the host caps bound actual construction.
// Otherwise first check this deterministic input under a finite host allowance;
// the runtime still uses the original options, including disabled producer caps.
void lower_check(const frontend::SqlRowsProgram& program,const FreeConnexTree& tree,
    const PhysicalOptions& physical,const AdmissionLimits& limits) {
  finite(limits);const auto& stored=physical.limits;
  if(stored.work_limit && stored.identity.work_limit && *stored.work_limit<=*limits.lowering.work_limit &&
      *stored.identity.work_limit<=*limits.lowering.identity.work_limit)return;
  const auto core=program.export_core();
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
  frontend::SqlRowsProgram program;
  CompiledProgram native;
  runtime::weighted::Binding binding;
  Options normal;
  runtime::sql_rows::OutputLimits output;
  ImageVector<char> bytes;
  Hash digest;
  Data(runtime::sql_rows::SourceSnapshot source,Options options,runtime::sql_rows::OutputLimits requested_output,ImageVector<char> encoded)
      : program(std::move(source.program)),native(std::move(source.native_program)),binding(source.native_binding),
        normal(options),output(requested_output),bytes(std::move(encoded)),digest(sha256_fixed({bytes.data(),bytes.size()})) {}
};
namespace detail {
class DescriptorFactory {
 public:
  static Admitted admit(const resource::MemoryAccount& account,frontend::SqlRowsProgram program,
      const FreeConnexTree& tree,const PhysicalOptions& physical,Options options,runtime::sql_rows::OutputLimits output,const AdmissionLimits& limits,Budget& budget) {
    require(bool(program),ImageFault::binding);
    require(!program.binding_image().empty(),ImageFault::binding);
    require(program.binding_image().size()<=limits.descriptor.image.bytes,ImageFault::limit);
    schema_limits(program,limits.descriptor);lower_check(program,tree,physical,limits);
    auto live=runtime::SqlRowsRuntime::create_into(account,std::move(program),tree,physical,options);
    auto source=live.source_snapshot();const auto image=Json::to_cbor(recipe(source,options,output));
    auto bytes=encode_bytes(account,source.program.binding_image(),view(image),limits.descriptor,budget);
    budget.charge(bytes.size()); // Whole-frame descriptor identity retained by Data.
    auto data=resource::make_accounted_shared<Descriptor::Data>(account,resource::MemoryPurpose::immutable_metadata,
        std::move(source),options,output,std::move(bytes));
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
Admitted admit_into(const resource::MemoryAccount& account,frontend::SqlRowsProgram program,
    const FreeConnexTree& tree,const PhysicalOptions& physical,Options options,runtime::sql_rows::OutputLimits output,const AdmissionLimits& limits) {
  Budget budget{limits.descriptor.image};return detail::DescriptorFactory::admit(account,std::move(program),tree,physical,options,output,limits,budget);
}
Admitted rebind_into(const resource::MemoryAccount& account,std::string_view bytes,const AdmissionLimits& limits) {
  finite(limits);const auto inspected=::crown::recovery::sql_rows::inspect_descriptor(bytes,limits.descriptor);
  Budget budget{limits.descriptor.image};budget.used=inspected.statistics.work;
  const auto binding=Json::from_cbor(inspected.binding_image.begin(),inspected.binding_image.end());
  const auto stored=Json::from_cbor(inspected.recipe.begin(),inspected.recipe.end());
  auto options=limits.binding;options.retain_binding_image=true;const auto catalog=io::read_catalog_payload(binding.at("catalog"));
  require(catalog.tables.size()<=limits.descriptor.image.tables,ImageFault::limit);
  for(const auto& table:catalog.tables)require(table.columns.size()<=limits.descriptor.image.fields,ImageFault::limit);
  options.binding.parameters.clear();options.parameters.clear();
  const auto& parameters=io::detail::array(binding.at("parameters"),"parameters");
  require(parameters.size()<=limits.descriptor.image.fields,ImageFault::limit);
  options.binding.parameters.reserve(parameters.size());options.parameters.reserve(parameters.size());
  for(const auto& parameter:parameters) {
    io::detail::fields(parameter,"parameter",{"kind","nullable","decimal","value"});
    const auto kind=number(parameter.at("kind"));ScalarType type;
    switch(kind) {
      case static_cast<unsigned>(frontend::SqlKind::int64):type=ScalarType::int64;break;
      case static_cast<unsigned>(frontend::SqlKind::string):type=ScalarType::string;break;
      case static_cast<unsigned>(frontend::SqlKind::boolean):type=ScalarType::boolean;break;
      case static_cast<unsigned>(frontend::SqlKind::date):type=ScalarType::date;break;
      case static_cast<unsigned>(frontend::SqlKind::decimal):type=ScalarType::decimal;break;
      default:throw ImageFailure(ImageFault::binding); // Genuine physical parameter declarations never use int32/unknown.
    }
    std::optional<DecimalSpec> decimal;
    if(!parameter.at("decimal").is_null()) {
      const auto& specification=io::detail::array(parameter.at("decimal"),"decimal");require(specification.size()==2);
      const auto precision=number(specification[0]),scale=number(specification[1]);
      require(precision>=1 && precision<=38 && scale<=precision,ImageFault::binding);
      decimal=DecimalSpec{static_cast<std::uint32_t>(precision),static_cast<std::uint32_t>(scale)};
    }
    options.binding.parameters.push_back({"parameter",type,parameter.at("nullable").get<bool>(),Collation::binary,decimal});
    const auto& value=parameter.at("value");
    if(value.is_null())options.parameters.emplace_back();else options.parameters.emplace_back(io::read_scalar(value));
  }
  const auto sql=io::detail::string(binding.at("source"),"source");
  auto result=frontend::bind_sql_rows_into(account,sql,catalog,options);
  if(const auto* failure=std::get_if<frontend::BindingDiagnostic>(&result)) {
    // Cold resource refusal remains work, never semantic corruption/Reject.
    throw ImageFailure(failure->diagnostic.code=="resource_limit"?ImageFault::work:ImageFault::binding);
  }
  auto program=std::get<frontend::SqlRowsProgram>(std::move(result));
  budget.charge(std::min(program.binding_image().size(),inspected.binding_image.size()));
  require(program.binding_image()==inspected.binding_image,ImageFault::binding);
  const auto core=program.export_core();
  const auto tree=io::read_tree(stored.at("tree").dump(),core.catalog,core.query);
  const auto physical=io::read_physical_options(stored.at("physical_options").dump());
  const auto normal=read_options(stored.at("normal"));
  const auto& policy=stored.at("output_limits");io::detail::fields(policy,"output_limits",{"rows","work"});
  const runtime::sql_rows::OutputLimits output{number(policy.at("rows")),number(policy.at("work"))};
  auto admitted=detail::DescriptorFactory::admit(account,std::move(program),tree,physical,normal,output,limits,budget);
  budget.charge(std::min(admitted.descriptor.bytes().size(),bytes.size()));
  require(admitted.descriptor.bytes()==bytes,ImageFault::binding);admitted.statistics.work=budget.used;return admitted;
}
const Descriptor::Data& Descriptor::data() const {
  require(bool(data_),ImageFault::binding);return *data_;
}
const frontend::SqlRowsProgram& Descriptor::program() const & { return data().program; }
const CompiledProgram& Descriptor::native_program() const & { return data().native; }
const runtime::weighted::Binding& Descriptor::native_binding() const & { return data().binding; }
const Options& Descriptor::options() const & { return data().normal; }
const runtime::sql_rows::OutputLimits& Descriptor::output_limits() const & { return data().output; }
const Hash& Descriptor::sha256() const & { return data().digest; }
std::string_view Descriptor::bytes() const & { const auto& b=data().bytes;return {b.data(),b.size()}; }
} // namespace crown::recovery::sql_rows
