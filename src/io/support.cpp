#include "crown/io/support.hpp"

#include "json.hpp"
#include <map>

namespace crown::io {
namespace {
const storage::TupleLayout& readable(const storage::TupleLayout& layout){return layout;}
storage::TupleLayout readable(const storage::AccountedLayout& layout){return layout.descriptor();}
Json row(storage::RowView values) { auto output=Json::array(); for (const auto& value : values.cells()) output.push_back(write_scalar_view(value)); return output; }
Json row(storage::TupleValuesView values) { auto output=Json::array(); for (const auto& value : values) output.push_back(write_scalar_view(value)); return output; }
std::string role(runtime::SupportRole role) {
  switch (role) {
    case runtime::SupportRole::records: return "records";
    case runtime::SupportRole::survivors: return "survivors";
    case runtime::SupportRole::parent_support: return "parent_support";
    case runtime::SupportRole::visible: return "visible";
  }
  throw Error("runtime_contract","unknown support handle role");
}
Json handle(runtime::SupportHandle value) {
  return {{"owner",value.owner.value},{"node",value.node.value},{"role",role(value.role)},{"tuple",value.tuple.value}};
}
std::string operation(SetOperation operation) {
  switch (operation) {
    case SetOperation::insert: return "insert";
    case SetOperation::erase: return "erase";
  }
  throw Error("runtime_contract","unknown support set operation");
}
std::string event_kind(runtime::SupportEventKind kind) {
  switch (kind) {
    case runtime::SupportEventKind::native_update: return "native_update";
    case runtime::SupportEventKind::child_key: return "child_key";
  }
  throw Error("runtime_contract","unknown support event kind");
}
Json value_state(const runtime::SupportValueState& value) {
  return {{"member",value.member},
      {"satisfied_children",value.satisfied ? Json(value.satisfied->value) : Json(nullptr)},
      {"child_present",value.child_present},
      {"support",value.support ? Json(value.support->value) : Json(nullptr)}};
}
Json journal(const runtime::SupportJournal& value) {
  auto records=Json::array(),events=Json::array();
  for (const auto& record : value.records) records.push_back({{"ordinal",record.ordinal},{"cause",record.cause},
      {"handle",handle(record.handle)},{"values",row(record.tuple().values())},
      {"before",value_state(record.before)},{"after",value_state(record.after)}});
  for (const auto& event : value.events) events.push_back({{"id",event.id},{"cause",event.cause},
      {"sequence",event.sequence},{"applied_ordinal",event.applied_ordinal},
      {"kind",event_kind(event.kind)},
      {"target",event.target.value},{"child_slot",event.child_slot ? Json(*event.child_slot) : Json(nullptr)},
      {"source",handle(event.source)},{"operation",operation(event.operation)},
      {"values",row(event.key.values())},{"before",event.before},{"after",event.after}});
  return {{"sequence",value.sequence},{"records",std::move(records)},{"events",std::move(events)}};
}
Json keys(const std::vector<runtime::ProjectionKeySnapshot>& values) {
  auto output=Json::array();
  for (const auto& value : values) output.push_back({{"key",row(value.key.values())},{"support",value.support.value},{"handle",handle(value.handle)}});
  return output;
}
}  // namespace
template<class Plan> SupportTrace read_support_trace_impl(std::string_view text,const Plan& plan,std::size_t max_updates) {
  // Diagnostic Rows/DOM own ordinary storage; native descriptors only supply validation.
  const auto input=detail::parse_json(text); detail::fields(input,"$",{"schema_version","updates"},{"options"});
  detail::version(input.at("schema_version"),"$.schema_version");
  const auto& updates=detail::array(input.at("updates"),"$.updates");
  if (updates.size()>max_updates) throw Error("resource_limit","logical diagnostic trace exceeds its host update limit");
  SupportTrace trace;
  if (input.contains("options")) {
    const auto& options=input.at("options"); detail::fields(options,"$.options",{},{"work_limit","support_limit","order","capture_transitions","memory_limit_bytes"});
    if (options.contains("memory_limit_bytes")) trace.options.memory_limit_bytes=detail::unsigned_integer(options.at("memory_limit_bytes"),"options.memory_limit_bytes");
    if (options.contains("work_limit")) trace.options.work_limit=options.at("work_limit").is_null() ? std::nullopt : std::optional<std::uint64_t>{detail::unsigned_integer(options.at("work_limit"),"options.work_limit")};
    if (options.contains("support_limit")) {
      trace.options.support_limit=detail::unsigned_integer(options.at("support_limit"),"options.support_limit");
      if (trace.options.support_limit==0) throw Error("invalid_options","support limit must be positive");
    }
    if (options.contains("order")) {
      const auto name=detail::string(options.at("order"),"options.order");
      if (name!="fifo" && name!="lifo") throw Error("invalid_options","propagation order must be fifo or lifo");
      trace.options.order=name=="fifo" ? runtime::PropagationOrder::fifo : runtime::PropagationOrder::lifo;
    }
    if (options.contains("capture_transitions")) {
      if (!options.at("capture_transitions").is_boolean()) detail::fail("options.capture_transitions","expected boolean");
      trace.options.capture_transitions=options.at("capture_transitions").get<bool>();
    }
  }
  std::map<std::string,NodeId> nodes;
  for (std::size_t i=0;i<plan.tree().nodes.size();++i) nodes.emplace(plan.tree().nodes[i].id,NodeId{i});
  for (const auto& update : updates) {
    detail::fields(update,"update",{"sequence","node","operation","values"});
    const auto sequence=detail::unsigned_integer(update.at("sequence"),"update.sequence");
    if (sequence!=trace.updates.size()+1) throw Error("invalid_sequence","logical diagnostic sequence must be contiguous from one");
    const auto name=detail::string(update.at("node"),"update.node"); const auto found=nodes.find(name);
    if (found==nodes.end() || plan.nodes()[found->second.value].kind!=NodeKind::native) throw Error("invalid_native_update","logical update must name a native node");
    const auto operation=detail::string(update.at("operation"),"update.operation");
    if (operation!="insert" && operation!="erase") throw Error("invalid_native_update","native operation must be insert or erase");
    Row values; for (const auto& value : detail::array(update.at("values"),"update.values")) values.push_back(read_scalar(value));
    readable(plan.nodes()[found->second.value].layout).validate(values);
    trace.updates.push_back({sequence,found->second,operation=="insert" ? SetOperation::insert : SetOperation::erase,std::move(values)});
  }
  return trace;
}
SupportTrace read_support_trace(std::string_view text,const PhysicalPlan& plan,std::size_t max_updates){return read_support_trace_impl(text,plan,max_updates);}
SupportTrace read_support_trace(std::string_view text,const CompiledProgram& plan,std::size_t max_updates){return read_support_trace_impl(text,plan,max_updates);}

Json write_support_options(const runtime::SupportOptions& options) {
  Json result{{"work_limit",options.work_limit ? Json(*options.work_limit) : Json(nullptr)},
      {"support_limit",options.support_limit},{"order",options.order==runtime::PropagationOrder::fifo ? "fifo" : "lifo"},
      {"capture_transitions",options.capture_transitions}};
  if (options.memory_limit_bytes!=runtime::SupportOptions{}.memory_limit_bytes) result["memory_limit_bytes"]=options.memory_limit_bytes;
  return result;
}
template<class Plan> Json write_support_snapshot_impl(const runtime::SupportSnapshot& snapshot,const Plan& plan) {
  auto nodes=Json::array();
  for (const auto& node : snapshot.nodes) {
    auto records=Json::array(),survivors=Json::array();
    for (const auto& record : node.records) records.push_back({{"values",row(record.tuple.values())},{"handle",handle(record.handle)},
        {"satisfied_children",record.satisfied.value},{"child_present",record.child_present},{"survives",record.survives}});
    for (const auto& tuple : node.survivors) survivors.push_back(row(tuple.values()));
    nodes.push_back({{"id",node.node.value},{"node",plan.tree().nodes.at(node.node.value).id},{"kind",node.kind==NodeKind::native ? "native" : "generalized"},
        {"records",std::move(records)},{"survivors",std::move(survivors)},{"parent_keys",keys(node.parent_keys)},
        {"visible_keys",node.visible_keys ? keys(*node.visible_keys) : Json(nullptr)}});
  }
  return {{"sequence",snapshot.sequence},{"has_answer",snapshot.has_answer},{"nodes",std::move(nodes)}};
}
Json write_support_snapshot(const runtime::SupportSnapshot& snapshot,const PhysicalPlan& plan){return write_support_snapshot_impl(snapshot,plan);}
Json write_support_snapshot(const runtime::SupportSnapshot& snapshot,const CompiledProgram& plan){return write_support_snapshot_impl(snapshot,plan);}

Json write_support_epoch(const runtime::SupportEpoch& epoch) {
  const auto& m=epoch.metrics; auto transitions=Json::array();
  for (const auto& transition : epoch.transitions) transitions.push_back({{"cause",transition.cause},
      {"handle",handle(transition.handle)},{"operation",operation(transition.operation)},
      {"values",row(transition.tuple.values())}});
  const Json retained_journal=epoch.journal ? journal(*epoch.journal) : Json(nullptr);
  return {{"sequence",epoch.sequence},{"native_changed",epoch.native_changed},{"has_answer",epoch.has_answer},
      {"transitions",std::move(transitions)},{"journal",retained_journal},
      {"metrics",{{"work",m.work},{"copied_rows",m.copied_rows},{"copied_index_memberships",m.copied_index_memberships},
          {"copied_metadata_entries",m.copied_metadata_entries},{"copied_child_flags",m.copied_child_flags},
          {"native_record_visits",m.native_record_visits},{"child_key_probes",m.child_key_probes},{"child_key_events",m.child_key_events},
          {"survivor_transitions",m.survivor_transitions},{"parent_key_transitions",m.parent_key_transitions},
          {"visible_key_transitions",m.visible_key_transitions},{"candidates_created",m.candidates_created},
          {"candidates_reclaimed",m.candidates_reclaimed},{"storage_changes",m.storage_changes},
          {"metadata_changes",m.metadata_changes},{"saved_child_flags",m.saved_child_flags},
          {"journal_records",m.journal_records},{"events_enqueued",m.events_enqueued},
          {"events_applied",m.events_applied},{"queue_peak",m.queue_peak}}}};
}
}  // namespace crown::io
