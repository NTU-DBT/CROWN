#include "crown/runtime/sql_aggregate.hpp"
#include "crown/recovery/sql_aggregate_checkpoint.hpp"
#include "crown/recovery/sql_aggregate_session.hpp"
#include "crown/api/error.hpp"
#include "crown/io/catalog.hpp"
#include "crown/planner/oracle.hpp"
#include "indexed_runtime_fixture.hpp"
#include "sql_aggregate_file_fixture.hpp"
#include <iostream>

namespace {
using namespace crown;
using io::Json;
namespace ag = runtime::aggregate;
Json tuple(const ag::Tuple& value) {
  Json result = Json::array();
  for (const auto& cell : value.view()) result.push_back(cell ? io::write_scalar_view(*cell) : Json{});
  return result;
}
Json changes(const runtime::sql_aggregate::Epoch& epoch) {
  Json result = Json::array();
  for (const auto& group : epoch.output)
    result.push_back({{"key", tuple(group.key)}, {"before", group.before ? tuple(*group.before) : Json{}},
        {"after", group.after ? tuple(*group.after) : Json{}}});
  return result;
}
template<class Engine> Json snapshot(const Engine& runtime) {
  const auto source = runtime.snapshot(); Json groups = Json::array();
  for (const auto& group : source.groups) groups.push_back({{"key", tuple(group.key)}, {"values", tuple(group.values)}});
  return {{"sequence", source.sequence}, {"groups", std::move(groups)}};
}
// Test transport only: Python independently decodes the actual durable spool,
// including its protected framing, before comparing SQL before/after changes.
std::string hex(std::string_view bytes) {
  constexpr std::string_view digits="0123456789abcdef";std::string result;result.reserve(2*bytes.size());
  for(const char value:bytes) {const auto byte=static_cast<unsigned char>(value);result.push_back(digits[byte>>4]);result.push_back(digits[byte&15]);}return result;
}
// Each optional barrier rebuilds from the complete physical image, then the
// mature SQL oracle checks this state and the following epoch's exact diff.
void rebuild(runtime::SqlAggregateRuntime& engine, const runtime::sql_aggregate::Options& options) {
  const auto image=engine.source_snapshot();
  runtime::sql_aggregate::RebuildLimits limits;
  limits.source.source_work={10000000,10000000,64ULL*1024*1024,10000000,10000000};
  limits.source.native_work=10000000;limits.group_work=10000000;
  if (image.source.native_program.options().indexed_storage)
    limits.source.indexed_work=storage::IndexWork{1000000000,1000000000,1000000000,1000000000,1000000000};
  auto restored=runtime::SqlAggregateRuntime::rebuild_into(
      resource::MemoryAccount::create(options.memory_limit_bytes),image,options,limits);
  if (snapshot(restored)!=snapshot(engine))
    throw Error("oracle_rebuild","physical source rebuild changed the committed snapshot");
  engine=std::move(restored);
}
// DTO anchors here exercise image/native reconstruction only. The independent
// SQL comparison does not pretend this in-memory fixture has an actual sink.
void checkpoint(runtime::SqlAggregateRuntime& engine,const recovery::sql_aggregate::Descriptor& descriptor,
    const runtime::sql_aggregate::Options& options) {
  namespace ar=recovery::sql_aggregate;
  ar::CheckpointMetadata metadata;metadata.binding.query_id.fill('0');metadata.binding.descriptor_sha256=descriptor.sha256();
  metadata.generation=1;metadata.physical_sequence=metadata.command_sequence=engine.sequence();
  metadata.delivery.sink_id.fill('1');metadata.delivery.sequence=engine.sequence();metadata.delivery.bytes=1;metadata.delivery.content_sha256.fill('a');
  io::AccountedInputProgress progress(engine.account());progress.sequence=engine.sequence();
  const auto image=ar::encode_checkpoint(engine.account(),descriptor,engine.source_snapshot(),metadata,progress);
  runtime::sql_aggregate::RebuildLimits limits;
  limits.source.source_work={10000000,10000000,64ULL*1024*1024,10000000,10000000};
  limits.source.native_work=10000000;limits.group_work=10000000;
  if(descriptor.native_program().options().indexed_storage)
    limits.source.indexed_work=storage::IndexWork{1000000000,1000000000,1000000000,1000000000,1000000000};
  auto restored=ar::restore_checkpoint_into(resource::MemoryAccount::create(options.memory_limit_bytes),descriptor,image.bytes(),metadata,limits);
  if(snapshot(restored.runtime)!=snapshot(engine) || restored.progress.sequence!=engine.sequence())
    throw Error("oracle_checkpoint","physical checkpoint changed native groups or command progress");
  engine=std::move(restored.runtime);
}
Json type(const frontend::SqlType& value) {
  return {{"kind", static_cast<int>(value.kind)}, {"nullable", value.nullable},
      {"decimal", value.decimal ? Json::array({value.decimal->precision, value.decimal->scale}) : Json{}}};
}
Json evaluate(const Json& request) {
  const auto catalog = io::read_catalog_payload(request.at("catalog"));
  frontend::SqlAggregateBindOptions binding;
  binding.kernel.average_scale = request.at("average_scale").get<std::uint8_t>();
  if (request.contains("parameter_columns")) {
    const auto parameters = io::read_catalog_payload({{"version", 1}, {"tables", Json::array({
        {{"name", "parameters"}, {"columns", request.at("parameter_columns")}}})}});
    binding.source.binding.parameters = parameters.tables[0].columns;
    for (const auto& value : request.at("parameters")) {
      if (value.is_null()) binding.source.parameters.emplace_back();
      else binding.source.parameters.emplace_back(std::in_place, io::read_scalar(value));
    }
  }
  auto bound = frontend::bind_sql_aggregate(request.at("sql").get<std::string>(), catalog, binding);
  if (const auto* failure = std::get_if<frontend::BindingDiagnostic>(&bound))
    throw Error(failure->diagnostic.code, failure->diagnostic.message);
  auto program = std::get<frontend::SqlAggregateProgram>(std::move(bound));
  FreeConnexTree tree;
  if (!program.source_program().contradiction()) {
    const auto core = program.source_program().export_core();
    const auto choice = planner::minimum_tree(core.catalog, core.query);
    if (choice.status != planner::OracleStatus::proven_minimum || !choice.tree)
      throw Error("oracle_tree", "original SQL oracle fixture has no admissible checked CROWN source tree");
    tree = *choice.tree;
  }
  runtime::sql_aggregate::Options options; options.capture_changes = true;
  options.source.native.multiplicity_limit = request.value("multiplicity_limit", UINT64_MAX);
  options.count_limit = request.value("count_limit", static_cast<std::uint64_t>(INT64_MAX));
  const bool checkpoints=request.value("checkpoint_every_epoch",false);
  const bool sessions=request.value("session_every_epoch",false);
  recovery::sql_aggregate::Descriptor descriptor;
  const auto physical=request.value("indexed",false)?s04_runtime::options():PhysicalOptions{};
  namespace ar=recovery::sql_aggregate;
  const auto account=sessions || checkpoints?resource::MemoryAccount::create(options.memory_limit_bytes):resource::MemoryAccount{};
  std::optional<sql_aggregate_file_test::Directory> directory;std::string root_path,sink_path;
  std::optional<runtime::SqlAggregateRuntime> runtime;std::optional<ar::Session> session;
  ar::SessionIdentity identity;identity.query_id.fill('1');identity.sink_id.fill('2');ar::SessionLimits limits;
  limits.history_generations=request.at("batches").size()+2;
  limits.rebuild.source.source_work={10000000,10000000,64ULL*1024*1024,10000000,10000000};
  limits.rebuild.source.native_work=10000000;limits.rebuild.group_work=10000000;
  if(request.value("indexed",false))limits.rebuild.source.indexed_work=storage::IndexWork{1000000000,1000000000,1000000000,1000000000,1000000000};
  if(sessions) {
    directory.emplace();root_path=directory->file("query.root");sink_path=directory->file("groups.sink");
    session.emplace(ar::Session::create_into(account,{root_path,sink_path},identity,program,tree,physical,options,limits));
  } else if(checkpoints) {
    auto admitted=ar::admit_into(account,program,tree,physical,options);
    descriptor=std::move(admitted.descriptor);runtime.emplace(std::move(admitted.runtime));
  } else runtime.emplace(program,tree,physical,options);
  program = {}; // Metadata observations below use the receiving owner's genuine import.
  const auto actual = sessions?session->descriptor().program():runtime->program(); const auto& kernel = actual.kernel_program();
  Json types = Json::array(), key_types = Json::array(), names = Json::array();
  for (const auto& output : kernel.outputs()) { types.push_back(type(output.type)); names.push_back(output.name); }
  for (const auto column : kernel.group_columns()) key_types.push_back(type(kernel.input_types()[column.value]));
  const bool reconstruct=request.value("rebuild_every_epoch",false);
  std::uint64_t rebuilds=0,checkpoint_count=0,reopens=0,durable_checkpoints=sessions?1:0;
  const auto reopen=[&] {session.reset();session.emplace(ar::Session::recover_into(account,{root_path,sink_path},identity.query_id,limits));++reopens;};
  const auto current=[&] {return sessions?snapshot(*session):snapshot(*runtime);};
  if (reconstruct) {rebuild(*runtime,options);++rebuilds;}
  if (checkpoints) {checkpoint(*runtime,descriptor,options);++checkpoint_count;}
  Json trace = Json::array({current()}), epochs = Json::array();
  for (const auto& command : request.at("batches")) {
    const auto& edits = command.at("edits");
    std::vector<ag::Row> owned; owned.reserve(edits.size());
    for (const auto& edit : edits) {
      auto& row = owned.emplace_back(); row.reserve(edit.at("values").size());
      for (const auto& cell : edit.at("values")) {
        if (cell.is_null()) row.emplace_back();
        else row.emplace_back(std::in_place, io::read_scalar(cell));
      }
    }
    std::vector<std::vector<runtime::sql_rows::Cell>> borrowed; borrowed.reserve(owned.size());
    for (const auto& row : owned) {
      auto& values = borrowed.emplace_back(); values.reserve(row.size());
      for (const auto& cell : row) {
        if (cell) values.emplace_back(std::in_place, storage::borrow_scalar(*cell));
        else values.emplace_back();
      }
    }
    std::vector<runtime::sql_rows::SourceReplacement> replacements; replacements.reserve(edits.size());
    for (std::size_t i = 0; i < edits.size(); ++i)
      replacements.push_back({TableId{edits[i].at("table").get<std::size_t>()}, borrowed[i],
          edits[i].at("before").get<std::uint64_t>(), edits[i].at("after").get<std::uint64_t>()});
    if(sessions) {
      const auto next=session->state().disposed+1;session->log({next,replacements,{},{}});reopen();
      assert(session->state().pending && session->state().logged==next);
      const auto decision=session->decide();assert(!decision.rejected);const auto output=std::string(*session->output());
      const auto info=std::get<ar::GroupInfo>(ar::inspect(actual,output).payload);reopen();assert(session->output()==output);
      epochs.push_back({{"sequence",decision.physical_sequence},{"native_sequence",session->state().committed},
          {"changed",info.changed},{"group_changed",info.group_changed},{"captured",true},{"native_bag_retained",false},{"frame_hex",hex(output)}});
      assert(session->deliver());reopen();assert(session->state().delivered==decision.physical_sequence && !session->output());
      const auto before=current();static_cast<void>(session->checkpoint());++durable_checkpoints;reopen();assert(current()==before);
    } else {
    auto prepared = runtime->prepare_batch({runtime->sequence() + 1, replacements});
    const auto preview = changes(prepared.preview());
    const auto changed = prepared.preview().changed, group_changed = prepared.preview().group_changed;
    const auto epoch = prepared.commit();
    auto output = changes(epoch);
    if (preview != output || changed != epoch.changed || group_changed != epoch.group_changed)
      throw Error("oracle_preview", "prepared and committed aggregate batch outputs differ");
    epochs.push_back({{"sequence", epoch.sequence}, {"native_sequence", epoch.native.sequence},
        {"changed", epoch.changed}, {"group_changed", epoch.group_changed}, {"captured", epoch.captured},
        {"native_bag_retained", bool(epoch.native.bag_deltas)}, {"output", std::move(output)}});
    if (reconstruct) {rebuild(*runtime,options);++rebuilds;}
    if (checkpoints) {checkpoint(*runtime,descriptor,options);++checkpoint_count;}
    }
    trace.push_back(current());
  }
  return {{"id", request.at("id")}, {"original_sql", actual.original_sql()},
      {"source_sql", actual.source_program().source()}, {"kernel_sql", kernel.source()},
      {"binding", std::string(actual.identity().binding.begin(), actual.identity().binding.end())},
      {"types", std::move(types)}, {"key_types", std::move(key_types)}, {"names", std::move(names)},
      {"epochs", std::move(epochs)}, {"trace", std::move(trace)}, {"rebuilds", rebuilds}, {"checkpoints",checkpoint_count},
      {"session_reopens",reopens},{"durable_checkpoints",durable_checkpoints}};
}
}  // namespace

int main() {
  try {
    for (std::string line; std::getline(std::cin, line);)
      std::cout << evaluate(io::read_json(line)).dump() << '\n';
    return 0;
  } catch (const std::exception& failure) {
    std::cerr << failure.what() << '\n'; return 1;
  }
}
