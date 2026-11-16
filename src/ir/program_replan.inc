// Included after CompiledProgram::Data and its native packer are defined.
// Native lowering retains the canonical admitted source, while every new
// instruction, token, binding and construction allocation uses its account.
namespace crown::program::detail {
class NativeLowering {
  template<class T> using V=std::vector<T,resource::MemoryAllocator<T>>;
  template<class K,class T> using M=std::map<K,T,std::less<K>,resource::MemoryAllocator<std::pair<const K,T>>>;
  struct Index {
    IndexRequirementId id;RelationId relation;storage::AccountedProjection projection;V<IndexUse> uses;
  };
  CompiledProgram::Data& data_;
  const planner::MinimumHeightCandidate& candidate_;
  ReplanLimits limits_;
  storage::IndexWorkAllowance work_;
  Builder arena_;
  M<V<VariableId>,storage::AccountedLayout> scopes_;
  M<TableId,storage::AccountedLayout> physical_,logical_;
  M<std::pair<RelationId,V<FieldId>>,IndexRequirementId> index_keys_;
  V<storage::AccountedLayout> layouts_;
  V<program::PhysicalRelation> relations_;
  V<Index> indexes_;
  V<program::PhysicalInput> inputs_;
  V<V<OccurrenceId>> routes_;
  V<program::PhysicalNode> nodes_;
  V<program::PhysicalEdge> edges_;
  V<program::EnumerationStep> steps_;
  V<AssignmentSlot> output_;
  V<AssignmentEquality> equalities_;
  std::size_t enumeration_depth_=0;
  template<class T> resource::MemoryAllocator<T> allocator() const {
    return resource::MemoryAllocator<T>(data_.account,resource::MemoryPurpose::scratch,data_.attribution);
  }
  static std::optional<std::uint64_t> capped(std::optional<std::uint64_t> a,std::optional<std::uint64_t> b) {
    return b && (!a || *b<*a)?b:a;
  }
  static void admit(std::uint64_t amount,const std::optional<std::uint64_t>& cap,ReplanFault fault) {
    if(cap && amount>*cap)throw ReplanFailure(fault);
  }
  void charge() {
    if(data_.work==UINT64_MAX || (limits_.physical.work_limit && data_.work>=*limits_.physical.work_limit))
      throw ReplanFailure(ReplanFault::lowering_work);
    ++data_.work;
  }
  const program::Catalog& source_catalog() const {return data_.normalized?data_.normalized->binding.catalog:data_.catalog;}
  storage::AccountedLayout scope(std::span<const VariableId> variables) {
    charge();V<VariableId> key(variables.begin(),variables.end(),allocator<VariableId>());
    const auto found=scopes_.find(key);if(found!=scopes_.end())return found->second;
    V<storage::Field> fields(allocator<storage::Field>());fields.reserve(variables.size());
    for(const auto variable:variables) {
      charge();require(variable.value<data_.query.variables.size());fields.push_back({data_.query.variables[variable.value].type,{},variable});
    }
    auto layout=make_layout(data_.account,data_.attribution,LayoutId{layouts_.size()},fields,data_.catalog.version,
        data_.physical_sha256,{}, {},&work_);
    layouts_.push_back(layout);scopes_.emplace(std::move(key),layout);return layout;
  }
  storage::AccountedLayout table_layout(TableId table,bool physical) {
    charge();auto& cache=physical?physical_:logical_;const auto found=cache.find(table);if(found!=cache.end())return found->second;
    const auto& catalog=physical?source_catalog():data_.catalog;require(table.value<catalog.tables.size());
    const auto& source=catalog.tables[table.value];V<storage::Field> fields(allocator<storage::Field>());fields.reserve(source.columns.size());
    for(const auto& column:source.columns){require(!column.nullable);fields.push_back({column.type,column.decimal,{}});}
    auto layout=make_layout(data_.account,data_.attribution,LayoutId{layouts_.size()},fields,catalog.version,
        data_.physical_sha256,{},storage::LayoutOrigin{table,source.source_schema_version},&work_);
    layouts_.push_back(layout);cache.emplace(table,layout);return layout;
  }
  storage::AccountedProjection project(const storage::AccountedLayout& source,std::span<const VariableId> variables) {
    charge();M<VariableId,FieldId> positions(std::less<VariableId>{},allocator<std::pair<const VariableId,FieldId>>());
    for(std::size_t i=0;i<source.fields().size();++i){charge();if(source.fields()[i].variable)positions.emplace(*source.fields()[i].variable,FieldId{i});}
    V<FieldId> fields(allocator<FieldId>());
    for(const auto variable:variables){charge();const auto found=positions.find(variable);require(found!=positions.end());fields.push_back(found->second);}
    return storage::AccountedProjection::freeze(source,scope(variables),fields,data_.attribution);
  }
  RelationId relation(RelationRole role,const storage::AccountedLayout& layout,std::optional<NodeId> node={},std::optional<TableId> base={}) {
    charge();const RelationId id{relations_.size()};relations_.push_back({id,role,layout,node,base});return id;
  }
  IndexRequirementId index(RelationId relation,storage::AccountedProjection projection,IndexUse use) {
    charge();auto key=std::make_pair(relation,V<FieldId>(projection.fields().begin(),projection.fields().end(),allocator<FieldId>()));
    const auto found=index_keys_.find(key);
    if(found!=index_keys_.end()) {
      auto& value=indexes_[found->second.value];require(value.projection.target().same_token(projection.target()));
      if(std::find(value.uses.begin(),value.uses.end(),use)==value.uses.end()){value.uses.push_back(use);}return found->second;
    }
    const IndexRequirementId id{indexes_.size()};V<IndexUse> uses(allocator<IndexUse>());uses.push_back(use);
    indexes_.push_back({id,relation,std::move(projection),std::move(uses)});index_keys_.emplace(std::move(key),id);return id;
  }
  void preflight() {
    charge();
    for(const auto& table:source_catalog().tables){charge();for(const auto& column:table.columns){static_cast<void>(column);charge();}}
    for(const auto& variable:data_.query.variables){static_cast<void>(variable);charge();}
    for(const auto& atom:data_.query.atoms){charge();for(const auto& term:atom.terms){static_cast<void>(term);charge();}}
    for(const auto& output:data_.query.head){static_cast<void>(output);charge();}
    for(const auto& node:data_.tree.nodes){charge();for(const auto v:node.scope){static_cast<void>(v);charge();}for(const auto child:node.children){static_cast<void>(child);charge();}}
  }
  void compile_nodes() {
    V<TableId> bases(allocator<TableId>());
    for(std::size_t i=0;i<data_.query.atoms.size();++i){charge();bases.push_back(data_.normalized?data_.normalized->adapters[i].base:data_.query.atoms[i].table);}
    std::sort(bases.begin(),bases.end());bases.erase(std::unique(bases.begin(),bases.end()),bases.end());
    for(const auto base:bases)static_cast<void>(relation(RelationRole::physical_base,table_layout(base,true),{},base));
    V<std::optional<NodeId>> parents(data_.tree.nodes.size(),std::optional<NodeId>{},allocator<std::optional<NodeId>>());
    for(std::size_t i=0;i<data_.tree.nodes.size();++i)for(const auto child:data_.tree.nodes[i].children){charge();require(child.value<parents.size());parents[child.value]=NodeId{i};}
    V<unsigned char> connex(data_.tree.nodes.size(),0,allocator<unsigned char>()),head(data_.query.variables.size(),0,allocator<unsigned char>());
    for(const auto id:data_.validation.maximal_connex){require(id.value<connex.size());connex[id.value]=1;}
    for(const auto& value:data_.query.head){require(value.variable.value<head.size());head[value.variable.value]=1;}
    for(std::size_t i=0;i<data_.tree.nodes.size();++i) {
      charge();const NodeId id{i};const auto& source=data_.tree.nodes[i];V<VariableId> visible(allocator<VariableId>());
      for(const auto variable:source.scope){charge();require(variable.value<head.size());if(head[variable.value])visible.push_back(variable);}
      const auto layout=scope(source.scope);auto parent_key=project(layout,data_.validation.separators[i]);
      std::optional<storage::AccountedProjection> visible_key;if(connex[i])visible_key=project(layout,visible);
      const auto records=relation(source.kind==NodeKind::native?RelationRole::native_records:RelationRole::generalized_candidates,layout,id);
      const auto survivors=relation(RelationRole::survivors,layout,id),support=relation(RelationRole::parent_support,parent_key.target(),id);
      std::optional<RelationId> enumeration;if(visible_key)enumeration=relation(RelationRole::visible,visible_key->target(),id);
      const auto occurrence=source.occurrence?std::optional<OccurrenceId>{OccurrenceId{*source.occurrence}}:std::nullopt;
      nodes_.push_back({id,source.kind,occurrence,parents[i],source.children,source.scope,arena_.freeze(visible),bool(connex[i]),
          layout,std::move(parent_key),std::move(visible_key),records,survivors,support,enumeration});
    }
  }
  void compile_inputs() {
    V<NodeId> nodes(data_.query.atoms.size(),NodeId{},allocator<NodeId>());
    for(const auto& node:nodes_)if(node.occurrence){require(node.occurrence->value<nodes.size());nodes[node.occurrence->value]=node.id;}
    for(std::size_t a=0;a<data_.query.atoms.size();++a) {
      charge();const auto& atom=data_.query.atoms[a];const auto& node=nodes_[nodes[a].value];
      const auto base=data_.normalized?data_.normalized->adapters[a].base:atom.table;
      const auto physical=table_layout(base,true),logical=data_.normalized?table_layout(atom.table,false):physical;
      M<VariableId,FieldId> first(std::less<VariableId>{},allocator<std::pair<const VariableId,FieldId>>());
      V<InputEquality> equalities(allocator<InputEquality>());V<program::InputConstant> constants(allocator<program::InputConstant>());
      for(std::size_t i=0;i<atom.terms.size();++i) {
        charge();if(const auto* variable=std::get_if<VariableId>(&atom.terms[i])) {
          const auto [entry,inserted]=first.emplace(*variable,FieldId{i});if(!inserted)equalities.push_back({entry->second,FieldId{i}});
        }else if(const auto* value=std::get_if<storage::ScalarView>(&atom.terms[i]))constants.push_back({FieldId{i},*value});
      }
      V<FieldId> fields(allocator<FieldId>());for(const auto variable:node.scope){charge();const auto found=first.find(variable);require(found!=first.end());fields.push_back(found->second);}
      inputs_.push_back({OccurrenceId{a},node.id,base,atom.table,physical,
          storage::AccountedProjection::freeze(logical,node.layout,fields,data_.attribution),arena_.freeze(equalities),arena_.freeze(constants)});
      require(base.value<routes_.size());routes_[base.value].push_back(OccurrenceId{a});
    }
  }
  void compile_edges() {
    for(const auto& parent:nodes_)for(std::size_t slot=0;slot<parent.children.size();++slot) {
      charge();const auto child_id=parent.children[slot];require(child_id.value<nodes_.size());const auto& child=nodes_[child_id.value];
      V<VariableId> separator(allocator<VariableId>());
      for(const auto& field:child.parent_key.target().fields()){charge();require(field.variable.has_value());separator.push_back(*field.variable);}
      auto key=project(parent.layout,separator);require(key.target().same_token(child.parent_key.target()));
      std::optional<IndexRequirementId> reverse;
      if(parent.kind==NodeKind::native)reverse=index(parent.records,key,IndexUse::reverse_child_support);
      else require(parent.layout.same_token(child.parent_key.target()));
      edges_.push_back({parent.id,child_id,slot,std::move(key),reverse});
    }
  }
  void compile_enumeration() {
    V<std::optional<std::size_t>> positions(nodes_.size(),std::optional<std::size_t>{},allocator<std::optional<std::size_t>>());
    M<VariableId,AssignmentSlot> first(std::less<VariableId>{},allocator<std::pair<const VariableId,AssignmentSlot>>());
    for(const auto id:data_.validation.maximal_connex) {
      charge();const auto& node=nodes_[id.value];require(node.visible_projection.has_value());const auto& visible=node.visible_projection->target();
      program::EnumerationStep step{id,*node.visible_relation,1,{},{},{}};
      if(node.parent) {
        require(positions[node.parent->value].has_value());const auto parent_position=*positions[node.parent->value];const auto& parent=nodes_[node.parent->value];
        step.parent_step=parent_position;step.depth=steps_[parent_position].depth+1;
        step.parent_key=project(parent.visible_projection->target(),data_.validation.separators[id.value]);
        step.bucket_index=index(*node.visible_relation,project(visible,data_.validation.separators[id.value]),IndexUse::visible_enumeration);
        require(step.parent_key->target().same_token(node.parent_key.target()));
      }
      const auto position=steps_.size();positions[id.value]=position;
      for(std::size_t i=0;i<visible.fields().size();++i) {
        charge();require(visible.fields()[i].variable.has_value());const auto [entry,inserted]=first.emplace(*visible.fields()[i].variable,AssignmentSlot{position,FieldId{i}});
        if(!inserted)equalities_.push_back({entry->second,{position,FieldId{i}}});
      }
      enumeration_depth_=std::max(enumeration_depth_,step.depth);steps_.push_back(std::move(step));
    }
    for(const auto& value:data_.query.head){charge();const auto found=first.find(value.variable);require(found!=first.end());output_.push_back(found->second);}
  }
  void freeze_instructions() {
    data_.layouts=arena_.freeze(layouts_);data_.relations=arena_.freeze(relations_);data_.inputs=arena_.freeze(inputs_);
    data_.base_routes=arena_.freeze(routes_);data_.nodes=arena_.freeze(nodes_);data_.edges=arena_.freeze(edges_);
    data_.enumeration={arena_.freeze(steps_),arena_.freeze(output_),arena_.freeze(equalities_),enumeration_depth_};
    auto* frozen=arena_.defaults<program::IndexRequirement>(indexes_.size());
    V<storage::AccountedPlanStorage::FrozenIndexBinding> bindings(allocator<storage::AccountedPlanStorage::FrozenIndexBinding>());bindings.reserve(indexes_.size());
    for(std::size_t i=0;i<indexes_.size();++i) {
      const auto& value=indexes_[i];frozen[i]={value.id,value.relation,value.projection,arena_.freeze(value.uses)};
      bindings.push_back({value.relation,value.projection});
    }
    data_.indexes={frozen,indexes_.size()};
    V<storage::AccountedPlanStorage::RelationBinding> relations(allocator<storage::AccountedPlanStorage::RelationBinding>());relations.reserve(relations_.size());
    for(const auto& value:relations_)relations.push_back({value.role,value.layout.id(),value.node,value.base});
    data_.binding=storage::AccountedPlanStorage::freeze_native_binding(data_.account,data_.route,data_.physical_sha256,
        data_.guarantee.storage_backend,layouts_,relations,bindings,data_.options.indexed_storage,&work_,storage::MetadataWork::compiler);
    arena_.finish_native_auxiliary();
  }
  NativeLowering(CompiledProgram::Data& data,const planner::MinimumHeightCandidate& candidate,const ReplanLimits& limits)
      :data_(data),candidate_(candidate),limits_(limits),work_({UINT64_MAX,UINT64_MAX,UINT64_MAX,UINT64_MAX,UINT64_MAX},true),arena_(data,&work_),
       scopes_(std::less<V<VariableId>>{},allocator<std::pair<const V<VariableId>,storage::AccountedLayout>>()),
       physical_(std::less<TableId>{},allocator<std::pair<const TableId,storage::AccountedLayout>>()),
       logical_(std::less<TableId>{},allocator<std::pair<const TableId,storage::AccountedLayout>>()),
       index_keys_(std::less<std::pair<RelationId,V<FieldId>>>{},allocator<std::pair<const std::pair<RelationId,V<FieldId>>,IndexRequirementId>>()),
       layouts_(allocator<storage::AccountedLayout>()),relations_(allocator<program::PhysicalRelation>()),indexes_(allocator<Index>()),
       inputs_(allocator<program::PhysicalInput>()),routes_(allocator<V<OccurrenceId>>()),nodes_(allocator<program::PhysicalNode>()),
       edges_(allocator<program::PhysicalEdge>()),steps_(allocator<program::EnumerationStep>()),output_(allocator<AssignmentSlot>()),equalities_(allocator<AssignmentEquality>()) {}
  void compile() {
    const auto& basis=data_.basis;
    const auto encoded=planner::binding_detail::encode(candidate_.catalog(),candidate_.query(),data_.account,
        resource::MemoryPurpose::scratch,data_.attribution);
    const auto bound=planner::binding_detail::encode(basis.catalog(),basis.query(),data_.account,
        resource::MemoryPurpose::scratch,data_.attribution);
    // The checked candidate binds exact catalog/query structure. Policy labels
    // remain explicit source/cache fields; they do not change that proof.
    if(encoded!=bound)throw ReplanFailure(ReplanFault::binding);
    const auto& checked=candidate_.validation();
    require(checked.valid && checked.native_height==candidate_.height());
    data_.route=basis.route();data_.catalog=basis.catalog();data_.query=basis.query();data_.normalized=basis.normalized();
    data_.identity=basis.identity();data_.options=basis.options();data_.guarantee=basis.guarantee();
    data_.physical_source_digest=basis.data_->physical_source_digest;
    limits_.physical.work_limit=capped(data_.options.limits.work_limit,limits_.physical.work_limit);
    limits_.physical.identity.work_limit=capped(data_.options.limits.identity.work_limit,limits_.physical.identity.work_limit);
    // These are unchanged conservative admission credits for the already
    // verified immutable compiler source. No parse/identity mirror is created.
    admit(data_.identity.work,limits_.physical.identity.work_limit,ReplanFault::identity_work);
    if(data_.normalized) {
      admit(data_.normalized->binding.work,limits_.binding_replay_work,ReplanFault::binding_replay_work);
      admit(data_.normalized->work,limits_.normalization_work,ReplanFault::normalization_work);
    }
    // The selected proof still describes the original body. A nonempty
    // contradiction executes a separate empty operator, with its own report.
    if(data_.query.contradiction && !data_.query.atoms.empty()) {
      data_.tree=arena_.freeze(crown::FreeConnexTree{});
      planner::ValidationReport report;report.valid=true;report.native_height=0;report.edge_depth=0;
      data_.validation=arena_.freeze(report);
    } else {
      data_.tree=arena_.freeze(candidate_.tree());data_.validation=arena_.freeze(checked);
    }
    preflight();charge();
    data_.native_physical_digest=planner::native_binding_detail::digest(basis,data_.tree,data_.attribution,data_.account);
    data_.physical_sha256={data_.native_physical_digest.data(),data_.native_physical_digest.size()};
    V<VariableId> outputs(allocator<VariableId>());for(const auto& value:data_.query.head){charge();outputs.push_back(value.variable);}
    data_.result_layout=scope(outputs);
    for(std::size_t i=0;i<source_catalog().tables.size();++i)routes_.emplace_back(allocator<OccurrenceId>());
    if(data_.route==PhysicalRoute::tree){compile_nodes();compile_inputs();compile_edges();compile_enumeration();}
    else data_.guarantee.query_class="constant_result";
    freeze_instructions();
  }
 public:
  static CompiledProgram run(const resource::MemoryAccount& account,const CompiledProgram& basis,
      const planner::MinimumHeightCandidate& candidate,const ReplanLimits& limits) {
    if(!account || !basis || !candidate.valid())throw ReplanFailure(ReplanFault::binding);
    const auto owner=storage::detail::try_new_storage_owner();if(!owner)throw storage::IndexFailure(storage::IndexFault::overflow);
    const resource::MemoryAttribution tag{resource::MemoryOwnerKind::immutable_metadata,owner->value};
    const auto source=basis.data_->basis?basis.data_->basis:basis;
    auto result=resource::make_accounted_shared<CompiledProgram::Data>(tag,account,resource::MemoryPurpose::immutable_metadata,
        account,tag,source);
    NativeLowering builder(*result,candidate,limits);builder.compile();
    if(basis.data_->prepared_inputs) {
      const auto& preparation=basis.data_->prepared_inputs->limits;
      const auto usage=PreparedInputs::analyze(result->normalized,result->inputs.size(),preparation,nullptr);
      result->prepared_inputs=PreparedInputs::build(account,tag,result->normalized,result->inputs.size(),preparation,usage,nullptr);
    }
    return CompiledProgram(std::move(result));
  }
};
} // namespace crown::program::detail
