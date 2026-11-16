#include "crown/io/physical.hpp"
#include "crown/annotations/policy.hpp"

#include "crown/io/layout.hpp"
#include "crown/io/tree.hpp"
#include "json.hpp"
#include <limits>

namespace crown::io {
namespace {
template <class Range> Json ids(const Range& values) {
  auto result=Json::array(); for (const auto value : values) result.push_back(value.value); return result;
}
template <class Id> Json optional_id(const std::optional<Id>& value) { return value ? Json(value->value) : Json(nullptr); }
Json projection(const storage::Projection& value) {
  return {{"source_layout",value.source().id().value},{"target_layout",value.target().id().value},{"fields",ids(value.fields())}};
}
Json slot(AssignmentSlot value) { return {{"step",value.step},{"field",value.field.value}}; }
std::string route_name(PhysicalRoute route) {
  switch (route) { case PhysicalRoute::tree: return "tree"; case PhysicalRoute::constant_true: return "constant_true"; case PhysicalRoute::constant_false: return "constant_false"; }
  throw Error("lowering_contract","unknown physical route");
}
std::string role_name(RelationRole role) {
  switch (role) {
    case RelationRole::physical_base: return "physical_base";
    case RelationRole::native_records: return "native_records";
    case RelationRole::generalized_candidates: return "generalized_candidates";
    case RelationRole::survivors: return "survivors";
    case RelationRole::parent_support: return "parent_support";
    case RelationRole::visible: return "visible";
  }
  throw Error("lowering_contract","unknown physical relation role");
}
std::optional<std::uint64_t> limit(const Json& value,const std::string& path) {
  return value.is_null() ? std::nullopt : std::optional<std::uint64_t>{detail::unsigned_integer(value,path)};
}
Json limit(std::optional<std::uint64_t> value) { return value ? Json(*value) : Json(nullptr); }
Json indexed_backend(const storage::IndexedBackendSpec& spec) {
  const auto& cap=spec.per_table;const auto& work=spec.per_operation;
  return {{"algorithm","indexed_chained_v1"},{"traversal","insertion_first_live_key_v1"},
      {"component_scope","per_table_including_undo"},{"work_scope","operation_aggregate"},
      {"limits",{{"rows",cap.rows},{"indices",cap.indices},{"keys",cap.keys},{"memberships",cap.memberships},
          {"nodes",cap.nodes},{"directory_slots",cap.directory_slots},{"arena_slots",cap.arena_slots},
          {"arena_pins",cap.arena_pins},{"journal_entries",cap.journal_entries}}},
      {"work",{{"structural_steps",work.structural_steps},{"scalar_fields",work.scalar_fields},
          {"scalar_bytes",work.scalar_bytes},{"pointer_slots",work.pointer_slots},{"link_actions",work.link_actions}}}};
}
std::size_t component_count(const Json& value,const std::string& path) {
  const auto count=detail::unsigned_integer(value,path);
  if constexpr (std::numeric_limits<std::size_t>::digits<64) {
    if (count>std::numeric_limits<std::size_t>::max()) detail::fail(path,"component count exceeds this host's size domain");
  }
  return static_cast<std::size_t>(count);
}
storage::IndexedBackendSpec read_indexed_backend(const Json& value) {
  const std::string path="$.indexed_storage";
  detail::fields(value,path,{"algorithm","traversal","component_scope","work_scope","limits","work"});
  for (const auto& [name,expected] : {std::pair{"algorithm","indexed_chained_v1"},
      {"traversal","insertion_first_live_key_v1"},{"component_scope","per_table_including_undo"},
      {"work_scope","operation_aggregate"}})
    if (detail::string(value.at(name),path+"."+name)!=expected)
      throw Error("unsupported_semantics",path+"."+name+": unsupported storage contract");
  const auto& cap=value.at("limits");const auto& work=value.at("work");
  detail::fields(cap,path+".limits",{"rows","indices","keys","memberships","nodes","directory_slots","arena_slots","arena_pins","journal_entries"});
  detail::fields(work,path+".work",{"structural_steps","scalar_fields","scalar_bytes","pointer_slots","link_actions"});
  storage::IndexedBackendSpec spec;
  spec.per_table={component_count(cap.at("rows"),path+".limits.rows"),component_count(cap.at("indices"),path+".limits.indices"),
      component_count(cap.at("keys"),path+".limits.keys"),component_count(cap.at("memberships"),path+".limits.memberships"),
      component_count(cap.at("nodes"),path+".limits.nodes"),component_count(cap.at("directory_slots"),path+".limits.directory_slots"),
      component_count(cap.at("arena_slots"),path+".limits.arena_slots"),component_count(cap.at("arena_pins"),path+".limits.arena_pins"),
      component_count(cap.at("journal_entries"),path+".limits.journal_entries")};
  spec.per_operation={detail::unsigned_integer(work.at("structural_steps"),path+".work.structural_steps"),
      detail::unsigned_integer(work.at("scalar_fields"),path+".work.scalar_fields"),
      detail::unsigned_integer(work.at("scalar_bytes"),path+".work.scalar_bytes"),
      detail::unsigned_integer(work.at("pointer_slots"),path+".work.pointer_slots"),
      detail::unsigned_integer(work.at("link_actions"),path+".work.link_actions")};
  return spec;
}
Json guarantee(const GuaranteeProfile& profile) {
  return {{"semantics",profile.semantics},{"query_class",profile.query_class},{"update_contract",profile.update_contract},
      {"arithmetic",profile.arithmetic},{"storage_backend",profile.storage_backend},{"execution_status",profile.execution_status},
      {"height_status",profile.height_status},{"state_bound",profile.state_bound},{"maintenance_bound",profile.maintenance_bound},
      {"cursor_startup_bound",profile.cursor_startup_bound},{"cursor_delay_bound",profile.cursor_delay_bound},
      {"cursor_termination_bound",profile.cursor_termination_bound},{"operation_modes",profile.operation_modes},
      {"assumptions",profile.assumptions},{"output_accounting",profile.output_accounting}};
}
}  // namespace

Json write_physical_options(const PhysicalOptions& options) {
  Json result{{"schema_version",options.indexed_storage ? 2 : 1},{"policy",{{"arithmetic",options.policy.arithmetic},{"planner",options.policy.planner},
      {"optimization",options.policy.optimization},{"cost_model",options.policy.cost_model}}},
      {"limits",{{"work",limit(options.limits.work_limit)},{"identity_work",limit(options.limits.identity.work_limit)}}}};
  if (options.indexed_storage) result["indexed_storage"]=indexed_backend(*options.indexed_storage);
  return result;
}
PhysicalOptions read_physical_options(std::string_view text) {
  const auto input=detail::parse_json(text);detail::fields(input,"$",{"schema_version","policy","limits"},{"indexed_storage"});
  const auto version=detail::unsigned_integer(input.at("schema_version"),"$.schema_version");
  if (version==1) detail::fields(input,"$",{"schema_version","policy","limits"});
  else if (version==2) {
    // Version2 is specifically the indexed contract. A relabeled legacy
    // options object remains an unsupported version of the reference format.
    if (!input.contains("indexed_storage"))
      throw Error("unsupported_version","version2 options require an explicit indexed storage contract");
    detail::fields(input,"$",{"schema_version","policy","limits","indexed_storage"});
  }
  else throw Error("unsupported_version","unknown physical options version");
  const auto& policy=input.at("policy"); detail::fields(policy,"$.policy",{"arithmetic","planner","optimization","cost_model"});
  const auto& limits=input.at("limits"); detail::fields(limits,"$.limits",{"work","identity_work"});
  PhysicalOptions options;
  options.policy={detail::string(policy.at("arithmetic"),"policy.arithmetic"),detail::string(policy.at("planner"),"policy.planner"),
      detail::string(policy.at("optimization"),"policy.optimization"),detail::string(policy.at("cost_model"),"policy.cost_model")};
  annotations::require_set_backend_policy(options.policy.arithmetic);
  if (options.policy.planner.empty() || options.policy.optimization.empty() || options.policy.cost_model.empty())
    throw Error("invalid_policy","physical lowering requires exact arithmetic and nonempty versioned planning policies");
  options.limits.work_limit=limit(limits.at("work"),"limits.work");
  options.limits.identity.work_limit=limit(limits.at("identity_work"),"limits.identity_work");
  if (version==2) options.indexed_storage=read_indexed_backend(input.at("indexed_storage"));
  return options;
}

Json write_physical_source(const Catalog& catalog,const Query& query,const std::optional<frontend::NormalizedSql>& normalized) {
  if (normalized) return {{"kind","normalized_sql"},{"program",write_sql_normalization(*normalized)}};
  else {
    Document document; document.catalog=catalog; document.query=query;
    document.initial.tables.resize(document.catalog.tables.size()); document.schema_version=3;
    return {{"kind","direct_cq"},{"document",write_document(document)}};
  }
}
Json write_physical(const PhysicalPlan& plan) {
  auto source=write_physical_source(plan.catalog(),plan.query(),plan.normalized());
  auto layouts=Json::array(); for (const auto& layout : plan.layouts()) layouts.push_back(write_layout(layout));
  auto relations=Json::array();
  for (const auto& relation : plan.relations()) relations.push_back({{"id",relation.id.value},{"role",role_name(relation.role)},
      {"layout",relation.layout.id().value},{"node",optional_id(relation.node)},{"base",optional_id(relation.base)}});
  auto indexes=Json::array();
  for (const auto& index : plan.indexes()) {
    auto uses=Json::array(); for (const auto use : index.uses) uses.push_back(use==IndexUse::reverse_child_support ? "reverse_child_support" : "visible_enumeration");
    indexes.push_back({{"id",index.id.value},{"relation",index.relation.value},{"projection",projection(index.projection)},{"uses",std::move(uses)}});
  }
  auto inputs=Json::array();
  for (const auto& input : plan.inputs()) {
    auto equalities=Json::array(), constants=Json::array();
    for (const auto& equality : input.equalities) equalities.push_back({equality.left.value,equality.right.value});
    for (const auto& constant : input.constants) constants.push_back({{"field",constant.field.value},{"value",write_scalar(constant.value)}});
    inputs.push_back({{"occurrence",input.occurrence.value},{"node",input.node.value},{"base",input.base.value},
        {"logical_table",input.logical_table.value},{"physical_layout",input.physical_layout.id().value},
        {"projection",projection(input.projection)},{"equalities",std::move(equalities)},{"constants",std::move(constants)}});
  }
  auto routes=Json::array(); for (const auto& route : plan.base_routes()) routes.push_back(ids(route));
  auto nodes=Json::array();
  for (const auto& node : plan.nodes()) nodes.push_back({{"id",node.id.value},{"kind",node.kind==NodeKind::native ? "native" : "generalized"},
      {"occurrence",optional_id(node.occurrence)},{"parent",optional_id(node.parent)},{"children",ids(node.children)},
      {"scope",ids(node.scope)},{"visible_scope",ids(node.visible_scope)},{"connex",node.connex},{"layout",node.layout.id().value},
      {"parent_key",projection(node.parent_key)},{"visible_projection",node.visible_projection ? projection(*node.visible_projection) : Json(nullptr)},
      {"records",node.records.value},{"survivors",node.survivors.value},{"parent_support",node.parent_support.value},
      {"visible_relation",optional_id(node.visible_relation)}});
  auto edges=Json::array();
  for (const auto& edge : plan.edges()) edges.push_back({{"parent",edge.parent.value},{"child",edge.child.value},{"child_slot",edge.child_slot},
      {"parent_key",projection(edge.parent_key)},{"reverse_index",optional_id(edge.reverse_index)}});
  auto steps=Json::array(), outputs=Json::array(), equalities=Json::array();
  for (const auto& step : plan.enumeration().steps) steps.push_back({{"node",step.node.value},{"relation",step.relation.value},{"depth",step.depth},
      {"parent_step",step.parent_step ? Json(*step.parent_step) : Json(nullptr)},
      {"parent_key",step.parent_key ? projection(*step.parent_key) : Json(nullptr)},{"bucket_index",optional_id(step.bucket_index)}});
  for (const auto output : plan.enumeration().output) outputs.push_back(slot(output));
  for (const auto& equality : plan.enumeration().equalities) equalities.push_back({{"left",slot(equality.left)},{"right",slot(equality.right)}});
  return {{"schema_version",plan.options().indexed_storage ? 2 : 1},
      {"lowerer",plan.options().indexed_storage ? "crown-lower-v2" : "crown-lower-v1"},{"route",route_name(plan.route())},{"source",std::move(source)},
      {"tree",write_tree(plan.tree(),plan.catalog(),plan.query())},{"options",write_physical_options(plan.options())},
      {"binding",{{"identity",write_identity(plan.identity())},{"physical_sha256",plan.physical_sha256()}}},
      {"verification",{{"kind",plan.route()==PhysicalRoute::constant_false ? "constant_operator" : "independent_tree_verifier"},
          {"valid",plan.validation().valid},{"native_height",*plan.validation().native_height},{"edge_depth",*plan.validation().edge_depth},
          {"maximal_connex",ids(plan.validation().maximal_connex)}}},
      {"layouts",std::move(layouts)},{"relations",std::move(relations)},{"indexes",std::move(indexes)},
      {"inputs",std::move(inputs)},{"base_routes",std::move(routes)},{"nodes",std::move(nodes)},{"edges",std::move(edges)},
      {"enumeration",{{"kind","nary_visible_assignments"},{"steps",std::move(steps)},{"output",std::move(outputs)},
          {"equalities",std::move(equalities)},{"depth",plan.enumeration().depth},{"result_layout",plan.result_layout().id().value}}},
      {"guarantee",guarantee(plan.guarantee())},{"work",plan.work()}};
}
Json write_physical(const CompiledProgram& plan) {
  const auto exported=PhysicalPlan::from_compiled(plan);
  return write_physical(exported);
}

PhysicalPlan read_physical(std::string_view text,const PhysicalReadLimits& limits) {
  // Source replay and verified lowering establish the result; imported flags/slots do not.
  const auto input=detail::parse_json(text);
  detail::fields(input,"$",{"schema_version","lowerer","route","source","tree","options","binding","verification", "layouts",
      "relations","indexes","inputs","base_routes","nodes","edges","enumeration","guarantee","work"});
  const auto version=detail::unsigned_integer(input.at("schema_version"),"$.schema_version");
  if (version!=1 && version!=2) throw Error("unsupported_version","unknown physical artifact version");
  if (detail::string(input.at("lowerer"),"$.lowerer")!=(version==1 ? "crown-lower-v1" : "crown-lower-v2"))
    throw Error("unsupported_version","physical lowerer and artifact version disagree");
  const auto options=read_physical_options(input.at("options").dump());
  if (options.indexed_storage.has_value()!=(version==2))
    throw Error("physical_binding","physical artifact version and storage contract disagree");
  const auto& source=input.at("source");
  if (!source.is_object() || !source.contains("kind")) detail::fail("source","expected a tagged source object");
  const auto kind=detail::string(source.at("kind"),"source.kind");
  auto rebuilt=[&]() {
    if (kind=="direct_cq") {
      detail::fields(source,"source",{"kind","document"});
      const auto document=read_document(source.at("document").dump());
      const auto tree=read_tree(input.at("tree").dump(),document.catalog,document.query);
      return planner::lower_tree(document.catalog,document.query,tree,options,limits.lowering);
    }
    if (kind=="normalized_sql") {
      detail::fields(source,"source",{"kind","program"});
      auto program=read_sql_normalization(source.at("program").dump(),limits.program);
      if (program.schema_version==1) program=upgrade_sql_normalization(program,2,limits.program);
      const auto tree=read_tree(input.at("tree").dump(),program.core_catalog,program.core);
      return planner::lower_normalized(program,tree,options,limits.program,limits.lowering);
    }
    throw Error("unsupported_semantics","unknown physical source kind");
  }();
  if (write_physical(rebuilt).dump()!=input.dump()) throw Error("physical_binding","physical artifact differs from complete verified lowering; source, slots, bindings and guarantees must all replay exactly");
  return rebuilt;
}
}  // namespace crown::io
