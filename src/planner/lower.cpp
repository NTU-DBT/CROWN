#include "crown/planner/lower.hpp"

#include "crown/api/error.hpp"
#include "crown/io/tree.hpp"
#include "crown/io/physical.hpp"
#include "crown/ir/digest.hpp"
#include "compiled_source.hpp"
#include <algorithm>
#include <limits>
#include <map>
#include <utility>

namespace crown {
namespace {
// nlohmann's ordinary object/array destructor allocates a flattening stack.
// A plan can lose its final owner in noexcept cursor/output cleanup. Remove
// leaves without a stack if preparation of its fast teardown inventory failed.
// Slow construction-failure fallback: repeated descent/first-child erase
// may be quadratic, but needs neither heap scratch nor recursion.
void clear_identity_without_allocation(io::Json& root) noexcept {
  while (root.is_structured() && !root.empty()) {
    auto* parent=&root; auto child=parent->begin();
    while (child->is_structured() && !child->empty()) { parent=&*child; child=parent->begin(); }
    parent->erase(child);
  }
  root.clear();
}
}  // namespace
// Public compiler DTO owner. A native export copies ordinary graph/source
// fields while layout/projection handles retain selected accounted metadata.
struct PhysicalPlan::Data {
  Catalog catalog;
  Query query;
  FreeConnexTree tree;
  std::optional<frontend::NormalizedSql> normalized;
  PhysicalRoute route = PhysicalRoute::tree;
  planner::ValidationReport validation;
  io::QueryIdentity identity;
  std::string physical_sha256;
  std::array<char,64> physical_source_sha256{};
  PhysicalOptions options;
  GuaranteeProfile guarantee;
  std::vector<storage::TupleLayout> layouts;
  std::vector<PhysicalRelation> relations;
  std::vector<IndexRequirement> indexes;
  std::vector<PhysicalInput> inputs;
  std::vector<std::vector<OccurrenceId>> base_routes;
  std::vector<PhysicalNode> nodes;
  std::vector<PhysicalEdge> edges;
  EnumerationProgram enumeration;
  std::optional<storage::TupleLayout> result_layout;
  std::uint64_t work = 0;
  std::vector<io::Json*> identity_cleanup;
  bool identity_cleanup_ready=false;
  // One-shot after identity reaches its final address. Freeze that JSON
  // graph; partial pointer inventory is ignored unless traversal completes.
  void prepare_identity_cleanup() {
    if (identity.canonical.is_structured()) identity_cleanup.push_back(&identity.canonical);
    for (std::size_t i=0;i<identity_cleanup.size();++i)
      for (auto& child : *identity_cleanup[i]) if (child.is_structured()) identity_cleanup.push_back(&child);
    identity_cleanup_ready=true;
  }
  ~Data() {
    if (identity_cleanup_ready) {
      // Parent containers remain valid until all descendants have been cleared.
      // Destruction of an empty JSON container has no flattening allocation.
      for (auto it=identity_cleanup.rbegin();it!=identity_cleanup.rend();++it) (*it)->clear();
    } else clear_identity_without_allocation(identity.canonical);
  }
};
namespace {
void require(bool condition, std::string_view code, std::string_view message) {
  if (!condition) throw Error(std::string(code), std::string(message));
}
std::optional<std::uint64_t> capped(std::optional<std::uint64_t> producer, std::optional<std::uint64_t> host) {
  return host && (!producer || *host < *producer) ? host : producer;
}
}  // namespace

PhysicalPlan::PhysicalPlan(std::shared_ptr<const Data> data) : data_(std::move(data)) {}
// Explicit caller export, not native internal replanning. Copy ordinary
// payload, share descriptor metadata, then prepare nonallocating teardown.
PhysicalPlan PhysicalPlan::from_compiled(const CompiledProgram& source) {
  auto exported=planner::compiler_source_detail::export_program(source);
  auto result=std::make_shared<Data>();
  result->route=exported.route;
  result->catalog=std::move(exported.catalog);
  result->query=std::move(exported.query);
  result->tree=std::move(exported.tree);
  result->normalized=std::move(exported.normalized);
  result->validation=std::move(exported.validation);
  result->identity=std::move(exported.identity);
  result->physical_sha256=std::move(exported.physical_sha256);
  result->physical_source_sha256=exported.physical_source_sha256;
  result->options=std::move(exported.options);
  result->guarantee=std::move(exported.guarantee);
  result->layouts=std::move(exported.layouts);
  result->relations=std::move(exported.relations);
  result->indexes=std::move(exported.indexes);
  result->inputs=std::move(exported.inputs);
  result->base_routes=std::move(exported.base_routes);
  result->nodes=std::move(exported.nodes);
  result->edges=std::move(exported.edges);
  result->enumeration=std::move(exported.enumeration);
  result->result_layout=std::move(exported.result_layout);
  result->work=exported.work;
  result->prepare_identity_cleanup();
  return PhysicalPlan(std::move(result));
}
const PhysicalPlan::Data& PhysicalPlan::data() const {
  require(bool(data_), "invalid_physical_plan", "moved-from physical plan"); return *data_;
}
PhysicalRoute PhysicalPlan::route() const { return data().route; }
const Catalog& PhysicalPlan::catalog() const { return data().catalog; }
const Catalog& PhysicalPlan::source_catalog() const { const auto& d=data(); return d.normalized ? d.normalized->binding.catalog : d.catalog; }
const Query& PhysicalPlan::query() const { return data().query; }
const FreeConnexTree& PhysicalPlan::tree() const { return data().tree; }
const std::optional<frontend::NormalizedSql>& PhysicalPlan::normalized() const { return data().normalized; }
const planner::ValidationReport& PhysicalPlan::validation() const { return data().validation; }
const io::QueryIdentity& PhysicalPlan::identity() const { return data().identity; }
const std::string& PhysicalPlan::physical_sha256() const { return data().physical_sha256; }
std::string_view PhysicalPlan::physical_source_sha256() const {const auto& value=data().physical_source_sha256;return {value.data(),value.size()};}
const PhysicalOptions& PhysicalPlan::options() const { return data().options; }
const GuaranteeProfile& PhysicalPlan::guarantee() const { return data().guarantee; }
const std::vector<storage::TupleLayout>& PhysicalPlan::layouts() const { return data().layouts; }
const std::vector<PhysicalRelation>& PhysicalPlan::relations() const { return data().relations; }
const std::vector<IndexRequirement>& PhysicalPlan::indexes() const { return data().indexes; }
const std::vector<PhysicalInput>& PhysicalPlan::inputs() const { return data().inputs; }
const std::vector<std::vector<OccurrenceId>>& PhysicalPlan::base_routes() const { return data().base_routes; }
const std::vector<PhysicalNode>& PhysicalPlan::nodes() const { return data().nodes; }
const std::vector<PhysicalEdge>& PhysicalPlan::edges() const { return data().edges; }
const EnumerationProgram& PhysicalPlan::enumeration() const { return data().enumeration; }
const storage::TupleLayout& PhysicalPlan::result_layout() const { return *data().result_layout; }
std::uint64_t PhysicalPlan::work() const { return data().work; }

// Run the retained SQL/local CQ adapter for one occurrence. This produces
// a typed core tuple; it neither maintains joins nor maps SQL result rows.
// The frontend adapter copies query-wide constant slots before local evaluation.
std::optional<storage::Tuple> PhysicalPlan::adapt_input(OccurrenceId occurrence, const Row& row) const {
  const auto& d=data();
  require(occurrence.value<d.inputs.size(), "invalid_input_port", "physical plan has no such native occurrence input port");
  const auto& input=d.inputs[occurrence.value];
  // The local SQL program is owned, typed and replay-validated. The maintained
  // kernel receives only the numeric core program's typed tuple.
  std::optional<storage::Tuple> source;
  if (d.normalized) {
    auto adapted=frontend::adapt_row(*d.normalized,occurrence,row);
    if (!adapted) return {};
    source=input.projection.source().tuple(std::move(*adapted));
  } else source=input.physical_layout.tuple(row);
  for (const auto& pair : input.equalities) if (source->values()[pair.left.value]!=source->values()[pair.right.value]) return {};
  for (const auto& fixed : input.constants) if (source->values()[fixed.field.value]!=fixed.value) return {};
  return input.projection.apply(*source);
}
// Check compiled tokens and shared-variable equalities. The caller owns
// membership in the live visible relations; assembly does not verify it.
storage::Tuple PhysicalPlan::assemble_result(std::span<const storage::Tuple> assignments) const {
  const auto& d=data();
  require(d.route!=PhysicalRoute::constant_false, "empty_plan", "constant-false operator has no result assignment");
  require(assignments.size()==d.enumeration.steps.size(), "invalid_assignment", "result assembly needs one assignment per enumeration step");
  for (std::size_t i=0;i<assignments.size();++i) {
    const auto relation=d.enumeration.steps[i].relation;
    require(d.relations[relation.value].layout.same_token(assignments[i].layout()), "layout_mismatch", "enumeration assignment has a different compiled layout");
  }
  const auto value=[&](AssignmentSlot slot) { return assignments[slot.step].values()[slot.field.value]; };
  for (const auto& equality : d.enumeration.equalities)
    require(value(equality.left)==value(equality.right), "invalid_assignment", "enumeration assignments disagree on a shared variable");
  Row result; result.reserve(d.enumeration.output.size());
  for (const auto& slot : d.enumeration.output) result.push_back(storage::export_scalar(value(slot)));
  return d.result_layout->tuple(std::move(result));
}

namespace planner {
// Fallible private build, followed by one immutable publication. Errors
// discard the builder; per-stage rollback/catch layers are unnecessary.
class Lowering {
 public:
  static PhysicalPlan run(Catalog catalog, Query query, FreeConnexTree tree,
      std::optional<frontend::NormalizedSql> normalized, const PhysicalOptions& options,
      const std::optional<PhysicalLimits>& host) {
    Lowering builder(options,host);
    auto& d=*builder.d_;
    d.catalog=std::move(catalog); d.query=std::move(query); d.tree=std::move(tree); d.normalized=std::move(normalized);
    builder.compile(); return PhysicalPlan(std::move(builder.d_));
  }
 private:
  std::shared_ptr<PhysicalPlan::Data> d_=std::make_shared<PhysicalPlan::Data>();
  PhysicalLimits limits_;
  std::map<std::vector<VariableId>,storage::TupleLayout> scopes_;
  std::map<TableId,storage::TupleLayout> physical_layouts_, logical_layouts_;
  std::map<std::pair<RelationId,std::vector<FieldId>>,IndexRequirementId> index_keys_;
  Lowering(const PhysicalOptions& options,const std::optional<PhysicalLimits>& host) : limits_(options.limits) {
    d_->options=options;
    if (options.indexed_storage) {
      d_->guarantee.storage_backend="indexed_chained_v1";
      d_->guarantee.operation_modes={"compile_only","indexed_storage_initialization"};
      d_->guarantee.assumptions={"single_writer","nonnull_exact_binary_values",
          "distributed_hashes_for_expected_time_only","finite_work_and_component_admission"};
    }
    if (host) {
      limits_.work_limit=capped(limits_.work_limit,host->work_limit);
      limits_.identity.work_limit=capped(limits_.identity.work_limit,host->identity.work_limit);
    }
  }
  // Selected construction checkpoints only. Copies, P02, JSON/hash work,
  // container comparisons/capacity and allocator bytes are separate costs.
  void charge() {
    if (d_->work==std::numeric_limits<std::uint64_t>::max() || (limits_.work_limit && d_->work>=*limits_.work_limit))
      throw Error("resource_limit","physical lowering work limit exceeded; no partial plan published");
    ++d_->work;
  }
  const Catalog& source_catalog() const { return d_->normalized ? d_->normalized->binding.catalog : d_->catalog; }
  storage::LayoutContext context() const { return {d_->catalog.version,d_->physical_sha256}; }
  // Ordered vector identity preserves repeated/output fields. A set key
  // would incorrectly merge distinct result layouts.
  storage::TupleLayout scope(const std::vector<VariableId>& variables) {
    charge(); const auto found=scopes_.find(variables); if (found!=scopes_.end()) return found->second;
    for (const auto variable : variables) { static_cast<void>(variable); charge(); }
    auto layout=storage::scope_layout(LayoutId{d_->layouts.size()},d_->query,variables,context());
    d_->layouts.push_back(layout); scopes_.emplace(variables,layout); return layout;
  }
  // Physical and core table IDs use different catalog domains under SQL.
  // On a miss, storage::table_layout revalidates the selected whole catalog.
  storage::TupleLayout table_layout(TableId table,bool physical) {
    charge(); auto& cache=physical ? physical_layouts_ : logical_layouts_;
    const auto found=cache.find(table); if (found!=cache.end()) return found->second;
    const auto& catalog=physical ? source_catalog() : d_->catalog;
    auto layout=storage::table_layout(LayoutId{d_->layouts.size()},catalog,table,d_->physical_sha256);
    d_->layouts.push_back(layout); cache.emplace(table,layout); return layout;
  }
  storage::Projection project(const storage::TupleLayout& source,const std::vector<VariableId>& variables) {
    charge(); std::map<VariableId,FieldId> positions;
    for (std::size_t i=0;i<source.fields().size();++i) {
      charge(); if (source.fields()[i].variable) positions.emplace(*source.fields()[i].variable,FieldId{i});
    }
    std::vector<FieldId> fields;
    for (const auto variable : variables) {
      charge(); const auto found=positions.find(variable);
      require(found!=positions.end(),"lowering_contract","projection variable is outside its source layout");
      fields.push_back(found->second);
    }
    return {source,scope(variables),std::move(fields)};
  }
  RelationId relation(RelationRole role,const storage::TupleLayout& layout,std::optional<NodeId> node={},std::optional<TableId> base={}) {
    charge(); const RelationId id{d_->relations.size()}; d_->relations.push_back({id,role,layout,node,base}); return id;
  }
  // Reuse requires the same relation, ordered fields and target token.
  // Even a cache hit builds/copies a temporary vector of selected fields.
  IndexRequirementId index(RelationId relation,storage::Projection projection,IndexUse use) {
    charge(); const auto key=std::make_pair(relation,std::vector<FieldId>(projection.fields().begin(),projection.fields().end())); const auto found=index_keys_.find(key);
    if (found!=index_keys_.end()) {
      auto& existing=d_->indexes[found->second.value];
      require(existing.projection.target().same_token(projection.target()),"lowering_contract","shared index has a different key token");
      if (std::find(existing.uses.begin(),existing.uses.end(),use)==existing.uses.end()) existing.uses.push_back(use);
      return found->second;
    }
    const IndexRequirementId id{d_->indexes.size()};
    d_->indexes.push_back({id,relation,std::move(projection),{use}}); index_keys_.emplace(key,id); return id;
  }
  // Coarse dimension charges before semantic validation; these loops do
  // not establish topology, bound scalar widths or meter later validation.
  void preflight() {
    charge();
    for (const auto& table : source_catalog().tables) { charge(); for (const auto& column : table.columns) { static_cast<void>(column); charge(); } }
    for (const auto& variable : d_->query.variables) { static_cast<void>(variable); charge(); }
    for (const auto& atom : d_->query.atoms) { charge(); for (const auto& term : atom.terms) { static_cast<void>(term); charge(); } }
    for (const auto& output : d_->query.head) { static_cast<void>(output); charge(); }
    for (const auto& node : d_->tree.nodes) {
      charge(); for (const auto variable : node.scope) { static_cast<void>(variable); charge(); }
      for (const auto child : node.children) { static_cast<void>(child); charge(); }
    }
  }
  void compile() {
    preflight(); validate(d_->catalog,d_->query);
    // Canonical constant operator, not a tree certificate for the retained
    // contradictory body. Never silently discard a nonempty supplied tree.
    if (d_->query.contradiction) {
      require(!d_->tree.root && d_->tree.nodes.empty() && (!d_->tree.claimed_connex || d_->tree.claimed_connex->empty()) &&
          (!d_->tree.claimed_native_height || *d_->tree.claimed_native_height==0),"invalid_plan","constant-false lowering requires the canonical empty tree");
      d_->route=PhysicalRoute::constant_false; d_->validation.valid=true;
      d_->validation.native_height=0; d_->validation.edge_depth=0;
    } else {
      d_->validation=validate_tree(d_->catalog,d_->query,d_->tree);
      if (!d_->validation.valid) {
        const auto& first=d_->validation.violations.front();
        throw Error("invalid_plan",first.rule+": "+first.message);
      }
      if (d_->query.atoms.empty()) d_->route=PhysicalRoute::constant_true;
    }
    charge();
    d_->identity=d_->normalized ? io::query_identity(*d_->normalized,d_->options.policy,limits_.identity) :
        io::query_identity(d_->catalog,d_->query,d_->options.policy,limits_.identity);
    d_->prepare_identity_cleanup();
    // The semantic identity erases local IDs. Physical instructions additionally
    // bind those ID maps, exact supplied tree and lowerer version.
    d_->physical_source_sha256=sha256_fixed(io::write_physical_source(d_->catalog,d_->query,d_->normalized).dump());
    io::Json binding{{"domain","crown-physical-plan"},{"version",d_->options.indexed_storage ? 2 : 1},
        {"lowerer",d_->options.indexed_storage ? "crown-lower-v2" : "crown-lower-v1"},
        {"source_sha256",std::string(d_->physical_source_sha256.data(),d_->physical_source_sha256.size())},
        {"plan_cache_sha256",d_->identity.plan_cache_sha256},{"occurrence_order",d_->identity.occurrence_order},
        {"variable_order",d_->identity.variable_order},{"tree",io::write_tree(d_->tree,d_->catalog,d_->query)}};
    if (d_->options.indexed_storage) binding["options"]=io::write_physical_options(d_->options);
    d_->physical_sha256=sha256(binding.dump());
    std::vector<VariableId> outputs; for (const auto& output : d_->query.head) { charge(); outputs.push_back(output.variable); }
    d_->result_layout=scope(outputs); d_->base_routes.resize(source_catalog().tables.size());
    if (d_->route!=PhysicalRoute::tree) { d_->guarantee.query_class="constant_result"; return; }
    compile_nodes(); compile_inputs(); compile_edges(); compile_enumeration();
  }
  // Scope may contain hidden root variables. Only P02 connex members get
  // visible relations, each using the head intersection of its full scope.
  void compile_nodes() {
    std::set<TableId> bases;
    for (std::size_t a=0;a<d_->query.atoms.size();++a) {
      charge(); bases.insert(d_->normalized ? d_->normalized->adapters[a].base : d_->query.atoms[a].table);
    }
    for (const auto base : bases) static_cast<void>(relation(RelationRole::physical_base,table_layout(base,true),{},base));
    std::vector<std::optional<NodeId>> parents(d_->tree.nodes.size());
    for (std::size_t i=0;i<d_->tree.nodes.size();++i) for (const auto child : d_->tree.nodes[i].children) { charge(); parents[child.value]=NodeId{i}; }
    std::set<NodeId> connex(d_->validation.maximal_connex.begin(),d_->validation.maximal_connex.end());
    VariableSet head; for (const auto& output : d_->query.head) head.insert(output.variable);
    for (std::size_t i=0;i<d_->tree.nodes.size();++i) {
      charge(); const NodeId id{i}; const auto& source=d_->tree.nodes[i];
      std::vector<VariableId> variables(source.scope.begin(),source.scope.end()),visible;
      for (const auto variable : variables) { charge(); if (head.contains(variable)) visible.push_back(variable); }
      const auto layout=scope(variables);
      const auto& separator=d_->validation.separators[i];
      auto parent_key=project(layout,{separator.begin(),separator.end()});
      std::optional<storage::Projection> visible_key;
      if (connex.contains(id)) visible_key=project(layout,visible);
      const auto records=relation(source.kind==NodeKind::native ? RelationRole::native_records : RelationRole::generalized_candidates,layout,id);
      const auto survivors=relation(RelationRole::survivors,layout,id);
      const auto support=relation(RelationRole::parent_support,parent_key.target(),id);
      std::optional<RelationId> enumeration;
      if (visible_key) enumeration=relation(RelationRole::visible,visible_key->target(),id);
      const auto occurrence=source.occurrence ? std::optional<OccurrenceId>{OccurrenceId{*source.occurrence}} : std::nullopt;
      d_->nodes.push_back({id,source.kind,occurrence,parents[i],source.children,std::move(variables),std::move(visible),connex.contains(id),
          layout,std::move(parent_key),std::move(visible_key),records,survivors,support,enumeration});
    }
  }
  // Preserve independent native occurrences even when aliases share a base.
  // Resolved numeric fields replace name lookup in the maintained kernel.
  void compile_inputs() {
    std::vector<NodeId> nodes(d_->query.atoms.size());
    for (const auto& node : d_->nodes) if (node.occurrence) nodes[node.occurrence->value]=node.id;
    for (std::size_t a=0;a<d_->query.atoms.size();++a) {
      charge(); const auto& atom=d_->query.atoms[a]; const auto& node=d_->nodes[nodes[a].value];
      const auto base=d_->normalized ? d_->normalized->adapters[a].base : atom.table;
      const auto physical=table_layout(base,true);
      const auto logical=d_->normalized ? table_layout(atom.table,false) : physical;
      std::map<VariableId,FieldId> first; std::vector<InputEquality> equalities; std::vector<InputConstant> constants;
      for (std::size_t i=0;i<atom.terms.size();++i) {
        charge();
        if (const auto* variable=std::get_if<VariableId>(&atom.terms[i])) {
          const auto [entry,inserted]=first.emplace(*variable,FieldId{i});
          if (!inserted) equalities.push_back({entry->second,FieldId{i}});
        } else if (const auto* value=std::get_if<Value>(&atom.terms[i])) constants.push_back({FieldId{i},*value});
      }
      std::vector<FieldId> fields; for (const auto variable : node.scope) { charge(); fields.push_back(first.at(variable)); }
      d_->inputs.push_back({OccurrenceId{a},node.id,base,atom.table,physical,{logical,node.layout,std::move(fields)},std::move(equalities),std::move(constants)});
      d_->base_routes[base.value].push_back(OccurrenceId{a});
    }
  }
  // Both endpoints share an exact separator token. Guard makes a
  // generalized parent use its whole scope rather than a reverse index.
  void compile_edges() {
    for (const auto& parent : d_->nodes) for (std::size_t slot=0;slot<parent.children.size();++slot) {
      charge(); const auto child_id=parent.children[slot]; const auto& child=d_->nodes[child_id.value];
      std::vector<VariableId> separator;
      for (const auto& field : child.parent_key.target().fields()) { charge(); separator.push_back(*field.variable); }
      auto key=project(parent.layout,separator);
      require(key.target().same_token(child.parent_key.target()),"lowering_contract","edge endpoints do not share a separator token");
      std::optional<IndexRequirementId> reverse;
      if (parent.kind==NodeKind::native) reverse=index(parent.records,key,IndexUse::reverse_child_support);
      else require(parent.layout.same_token(child.parent_key.target()),"lowering_contract","generalized child does not project to its parent's whole scope");
      d_->edges.push_back({parent.id,child_id,slot,std::move(key),reverse});
    }
  }
  // P02 supplies root-connected parent-before-child C* order and output
  // coverage. This records traversal/slots; it does not enumerate results.
  void compile_enumeration() {
    auto& program=d_->enumeration; std::vector<std::optional<std::size_t>> positions(d_->nodes.size());
    std::map<VariableId,AssignmentSlot> first;
    for (const auto id : d_->validation.maximal_connex) {
      charge(); const auto& node=d_->nodes[id.value]; const auto& visible=node.visible_projection->target();
      EnumerationStep step{id,*node.visible_relation,1,{},{},{}};
      if (node.parent) {
        const auto parent_position=*positions[node.parent->value]; const auto& parent=d_->nodes[node.parent->value];
        const auto& separator=d_->validation.separators[id.value]; const std::vector<VariableId> variables(separator.begin(),separator.end());
        step.parent_step=parent_position; step.depth=program.steps[parent_position].depth+1;
        step.parent_key=project(parent.visible_projection->target(),variables);
        step.bucket_index=index(*node.visible_relation,project(visible,variables),IndexUse::visible_enumeration);
        require(step.parent_key->target().same_token(node.parent_key.target()),"lowering_contract","enumeration separator token mismatch");
      }
      const auto position=program.steps.size(); positions[id.value]=position;
      for (std::size_t i=0;i<visible.fields().size();++i) {
        charge(); const auto [entry,inserted]=first.emplace(*visible.fields()[i].variable,AssignmentSlot{position,FieldId{i}});
        if (!inserted) program.equalities.push_back({entry->second,{position,FieldId{i}}});
      }
      program.depth=std::max(program.depth,step.depth); program.steps.push_back(std::move(step));
    }
    for (const auto& output : d_->query.head) { charge(); program.output.push_back(first.at(output.variable)); }
  }
};

PhysicalPlan lower_tree(const Catalog& catalog,const Query& query,const FreeConnexTree& tree,const PhysicalOptions& options,const std::optional<PhysicalLimits>& host) {
  return Lowering::run(catalog,query,tree,{},options,host);
}
// Replay the entire artifact and ground v1 before reading its core.
// Serialization/replay/copies have costs beyond lowering checkpoints.
PhysicalPlan lower_normalized(const frontend::NormalizedSql& program,const FreeConnexTree& tree,const PhysicalOptions& options,
    const io::ProgramReadLimits& program_limits,const std::optional<PhysicalLimits>& host) {
  auto owned=io::read_sql_normalization(io::write_sql_normalization(program).dump(),program_limits);
  if (owned.schema_version==1) owned=io::upgrade_sql_normalization(owned,2,program_limits);
  auto catalog=owned.core_catalog; auto query=owned.core;
  return Lowering::run(std::move(catalog),std::move(query),tree,std::move(owned),options,host);
}
}  // namespace planner
}  // namespace crown
