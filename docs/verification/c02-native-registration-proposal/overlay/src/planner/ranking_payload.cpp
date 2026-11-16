#include "ranking_payload.hpp"
#include <type_traits>
#include <variant>

namespace crown::planner::ranking::detail {
namespace {
template<class T> void fixed(Budget& b){b.work();b.bytes(sizeof(T));}
template<class T> void sequence(const std::vector<T>& v,Budget& b){b.work(static_cast<std::uint64_t>(v.size()));b.vector_items<T>(v.size());}
void string(const std::string& s,Budget& b){b.work(static_cast<std::uint64_t>(s.size()));b.bytes(static_cast<std::uint64_t>(s.size()));}
void scalar(const Value& value,Budget& b){
  b.work();if(const auto* text=std::get_if<std::string>(&value))string(*text,b);
  // Decimal's private canonical coefficient owns at most 38 character bytes.
  // Its public formatting API would allocate, so admit that fixed conservative
  // coefficient allowance before the native copy instead of formatting here.
  else if(std::holds_alternative<Decimal>(value)){b.work(38);b.bytes(38);}
}
void variables(const VariableSet& v,Budget& b){b.work(static_cast<std::uint64_t>(v.size()));b.vector_items<VariableId>(v.size());}
void catalog(const Catalog& c,Budget& b){
  sequence(c.tables,b);
  for(const auto& t:c.tables){string(t.name,b);sequence(t.columns,b);for(const auto& c2:t.columns)string(c2.name,b);
    sequence(t.constraints,b);for(const auto& c2:t.constraints)std::visit([&](const auto& constraint){string(constraint.name,b);sequence(constraint.columns,b);
      if constexpr(std::is_same_v<std::decay_t<decltype(constraint)>,ForeignKeyConstraint>)sequence(constraint.referenced_columns,b);},c2);
    sequence(t.statistics.distinct_counts,b);for(const auto& d:t.statistics.distinct_counts)sequence(d.columns,b);
    sequence(t.key_hints,b);for(const auto& h:t.key_hints){sequence(h.columns,b);string(h.reason,b);}}
}
void query(const Query& q,Budget& b){
  sequence(q.variables,b);for(const auto& v:q.variables)string(v.name,b);
  sequence(q.atoms,b);for(const auto& a:q.atoms){string(a.occurrence,b);sequence(a.terms,b);for(const auto& t:a.terms)if(const auto* v=std::get_if<Value>(&t))scalar(*v,b);}
  sequence(q.head,b);for(const auto& h:q.head)string(h.alias,b);
}
void tree(const FreeConnexTree& t,Budget& b){
  sequence(t.nodes,b);for(const auto& n:t.nodes){string(n.id,b);variables(n.scope,b);sequence(n.children,b);if(n.claimed_separator)variables(*n.claimed_separator,b);}
  if(t.claimed_connex)sequence(*t.claimed_connex,b);
}
void normalized(const frontend::NormalizedSql& n,Budget& b){
  const auto& q=n.binding;catalog(q.catalog,b);string(q.source,b);string(q.wrapper_alias,b);
  sequence(q.parameters,b);sequence(q.occurrences,b);sequence(q.expressions,b);sequence(q.predicates,b);sequence(q.outputs,b);
  for(const auto& o:q.occurrences){string(o.alias,b);sequence(o.column_names,b);for(const auto& s:o.column_names)string(s,b);}
  for(const auto& e:q.expressions){if(const auto* literal=std::get_if<frontend::BoundLiteral>(&e.node)){if(literal->value)scalar(*literal->value,b);}
    else if(const auto* operation=std::get_if<frontend::BoundOperation>(&e.node))sequence(operation->arguments,b);}
  for(const auto& o:q.outputs)string(o.name,b);
  sequence(n.parameters,b);sequence(n.constants,b);for(const auto& v:n.parameters)if(v)scalar(*v,b);for(const auto& v:n.constants)if(v)scalar(*v,b);
  catalog(n.core_catalog,b);query(n.core,b);
  sequence(n.adapters,b);for(const auto& a:n.adapters){sequence(a.predicates,b);sequence(a.non_null_columns,b);sequence(a.equal_columns,b);sequence(a.column_classes,b);sequence(a.projection,b);sequence(a.program,b);sequence(a.constant_columns,b);for(const auto& v:a.constant_columns)scalar(v.value,b);}
  sequence(n.base_routes,b);for(const auto& route:n.base_routes)sequence(route,b);
  sequence(n.outputs,b);for(const auto& o:n.outputs){string(o.name,b);if(const auto* v=std::get_if<frontend::ConstantOutput>(&o.value))scalar(v->value,b);}
}
// A bounded iterative visitor; even the scratch pointer inventory is charged.
// Keys and nodes are a logical DOM model, not std::map node overhead.
void canonical(const io::Json& root,Budget& b){
  fixed<std::vector<io::Json*>>(b);
  b.vector_items<const io::Json*>(1);std::vector<const io::Json*> pending{&root};
  while(!pending.empty()){
    const auto* item=pending.back();pending.pop_back();b.work();b.cells();b.bytes(sizeof(io::Json));
    if(item->is_structured())b.vector_items<io::Json*>(1);
    if(item->is_string())string(item->get_ref<const io::Json::string_t&>(),b);
    else if(item->is_object()){
      const auto& object=item->get_ref<const io::Json::object_t&>();
      for(const auto& entry:object){b.bytes(sizeof(std::string));string(entry.first,b);b.vector_items<const io::Json*>(1);pending.push_back(&entry.second);}
    }else if(item->is_array()){
      const auto& array=item->get_ref<const io::Json::array_t&>();for(const auto& child:array){b.vector_items<const io::Json*>(1);pending.push_back(&child);}
    }else if(item->is_binary())throw Failure{Stop::internal_error};
  }
}
void identity(const io::QueryIdentity& id,Budget& b){
  fixed<io::QueryIdentity>(b);canonical(id.canonical,b);string(id.semantic_sha256,b);string(id.output_contract_sha256,b);string(id.cost_inputs_sha256,b);string(id.plan_cache_sha256,b);
  sequence(id.occurrence_order,b);sequence(id.variable_order,b);
}
void projection(const storage::Projection& p,Budget& b){fixed<storage::TupleLayout>(b);fixed<storage::TupleLayout>(b);fixed<std::vector<FieldId>>(b);sequence(p.fields(),b);}
void strings(const std::vector<std::string>& values,Budget& b){sequence(values,b);for(const auto& s:values)string(s,b);}
} // namespace

void plan_source_payload(const MinimumHeightCandidate& c,const PhysicalPlan& basis,Budget& b){
  fixed<PhysicalPlan>(b);fixed<Catalog>(b);fixed<Query>(b);fixed<FreeConnexTree>(b);fixed<std::optional<frontend::NormalizedSql>>(b);
  catalog(c.catalog(),b);query(c.query(),b);tree(c.tree(),b);
  if(basis.normalized())normalized(*basis.normalized(),b);
  // Exact binding, identical owned program and options give the same semantic
  // identity independent of the candidate tree. Charge its complete content
  // before native construction; the output is checked again after lowering.
  identity(basis.identity(),b);
}
void plan_compiled_payload(const PhysicalPlan& p,Budget& b){
  fixed<PhysicalOptions>(b);const auto& policy=p.options().policy;string(policy.arithmetic,b);string(policy.planner,b);string(policy.optimization,b);string(policy.cost_model,b);
  fixed<GuaranteeProfile>(b);const auto& g=p.guarantee();string(g.semantics,b);string(g.query_class,b);string(g.update_contract,b);string(g.arithmetic,b);string(g.storage_backend,b);string(g.execution_status,b);string(g.height_status,b);string(g.state_bound,b);string(g.maintenance_bound,b);string(g.cursor_startup_bound,b);string(g.cursor_delay_bound,b);string(g.cursor_termination_bound,b);strings(g.operation_modes,b);strings(g.assumptions,b);strings(g.output_accounting,b);
  fixed<planner::ValidationReport>(b);const auto& v=p.validation();sequence(v.maximal_connex,b);sequence(v.separators,b);for(const auto& s:v.separators)variables(s,b);
  sequence(v.violations,b);for(const auto& issue:v.violations){string(issue.rule,b);string(issue.message,b);}
  fixed<std::string>(b);string(p.physical_sha256(),b);
  fixed<std::vector<storage::TupleLayout>>(b);sequence(p.layouts(),b);
  for(const auto& layout:p.layouts()){
    fixed<LayoutId>(b);fixed<storage::LayoutContext>(b);fixed<std::optional<storage::LayoutOrigin>>(b);fixed<std::vector<storage::Field>>(b);sequence(layout.fields(),b);string(layout.context().binding,b);
    // TupleLayout privately retains one pair per repeated variable. At most
    // one pair is added for a field; this linear conservative allowance also
    // covers repeated ordered heads without an unbounded duplicate scan.
    fixed<std::vector<std::pair<FieldId,FieldId>>>(b);b.vector_items<std::pair<FieldId,FieldId>>(layout.fields().size());
  }
  fixed<std::vector<PhysicalRelation>>(b);sequence(p.relations(),b);
  fixed<std::vector<IndexRequirement>>(b);sequence(p.indexes(),b);for(const auto& i:p.indexes()){projection(i.projection,b);sequence(i.uses,b);}
  fixed<std::vector<PhysicalInput>>(b);sequence(p.inputs(),b);for(const auto& i:p.inputs()){projection(i.projection,b);sequence(i.equalities,b);sequence(i.constants,b);for(const auto& c:i.constants)scalar(c.value,b);}
  fixed<std::vector<std::vector<OccurrenceId>>>(b);sequence(p.base_routes(),b);for(const auto& route:p.base_routes())sequence(route,b);
  fixed<std::vector<PhysicalNode>>(b);sequence(p.nodes(),b);for(const auto& n:p.nodes()){sequence(n.children,b);sequence(n.scope,b);sequence(n.visible_scope,b);projection(n.parent_key,b);if(n.visible_projection)projection(*n.visible_projection,b);}
  fixed<std::vector<PhysicalEdge>>(b);sequence(p.edges(),b);for(const auto& e:p.edges())projection(e.parent_key,b);
  fixed<EnumerationProgram>(b);const auto& e=p.enumeration();sequence(e.steps,b);sequence(e.output,b);sequence(e.equalities,b);for(const auto& step:e.steps)if(step.parent_key)projection(*step.parent_key,b);
  fixed<std::optional<storage::TupleLayout>>(b);
  // Shared projection data may be charged repeatedly by distinct published
  // references; this is deliberate conservative component accounting.
}
} // namespace crown::planner::ranking::detail
