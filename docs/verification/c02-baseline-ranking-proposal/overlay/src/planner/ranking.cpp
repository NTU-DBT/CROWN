#include "ranking_detail.hpp"
#include "candidate_binding.hpp"
#include "ranking_payload.hpp"
#include "crown/planner/lower.hpp"
#include "crown/api/error.hpp"
#include <algorithm>
#include <new>

namespace crown::planner::ranking {
const PhysicalPlan& Evidence::plan() const noexcept{return data_->plan;}
const std::vector<InputWeight>& Evidence::weights() const noexcept{return data_->weights;}
const std::vector<SourceCardinality>& Evidence::sources() const noexcept{return data_->sources;}
const std::vector<SourceObservation>& Evidence::source_observations() const noexcept{return data_->source_observations;}
const EvidenceIdentity& Evidence::identity() const noexcept{return data_->identity;}
const CaptureAccounting& Evidence::capture_accounting() const noexcept{return data_->accounting;}
Reasons Evidence::depth_reasons() const noexcept{return data_->depth_reasons;}
Reasons Evidence::memory_reasons() const noexcept{return data_->memory_reasons;}
std::uint64_t Evidence::denominator() const noexcept{return data_->denominator;}
const Usage& Evidence::preparation_usage() const noexcept{return data_->preparation;}
const CandidateSnapshot& Result::snapshot() const noexcept{return data_->snapshot;}
const MinimumHeightCandidate& Result::selected() const noexcept{return data_->scores[data_->selected].candidate;}
std::size_t Result::selected_index() const noexcept{return data_->selected;}
const std::vector<CandidateScore>& Result::scores() const noexcept{return data_->scores;}
const std::optional<Evidence>& Result::evidence() const noexcept{return data_->evidence;}
const Request& Result::request() const noexcept{return data_->request;}
Policy Result::effective_policy() const noexcept{return data_->effective;}
Reasons Result::fallback_reasons() const noexcept{return data_->fallback;}
const Usage& Result::usage() const noexcept{return data_->usage;}
namespace detail {
std::string binding(const Catalog& c,const Query& q,Budget& b) {
  b.time();b.check_all();
  const auto room=std::min(b.limits.binding_key_bytes-b.usage.binding_key_bytes,
      b.limits.payload_bytes-b.usage.payload_bytes);
  binding_detail::Budget cap{b.usage.work,b.usage.binding_key_bytes,b.limits.work,
      b.usage.binding_key_bytes+room};
  try {auto result=binding_detail::encode(c,q,&cap);b.bytes(static_cast<std::uint64_t>(result.size()));b.time();return result;}
  catch(const binding_detail::Limit& stop){throw Failure{stop.kind==binding_detail::LimitKind::work?Stop::work_limit:Stop::byte_limit};}
}
bool equal_bytes(const std::string& a,const std::string& c,Budget& b) {
  if(a.size()!=c.size())return false;
  for(std::size_t i=0;i<a.size();++i){b.keys(1);if(a[i]!=c[i])return false;}return true;
}
namespace {
void require(bool value,Stop stop=Stop::internal_error){if(!value)throw Failure{stop};}
bool supported(Policy p){return p==Policy::height_only || p==Policy::committed_input_native_depth || p==Policy::tuple_index_slots;}
bool same_context(const CandidateContext& a,const CandidateContext& c) {
  return a.updates==c.updates && a.arithmetic==c.arithmetic && a.planner==c.planner &&
      a.optimization==c.optimization && a.cost_model==c.cost_model && a.canonicalization==c.canonicalization;
}
bool key_less(const std::string& a,const std::string& c,Budget& b) {
  const auto n=std::min(a.size(),c.size());
  for(std::size_t i=0;i<n;++i){b.keys(2);const auto x=static_cast<unsigned char>(a[i]),y=static_cast<unsigned char>(c[i]);if(x!=y)return x<y;}
  return a.size()<c.size();
}
std::vector<std::size_t> order(const FreeConnexTree& t,Budget& b) {
  b.vector_items<std::size_t>(t.nodes.size());b.vector_items<unsigned char>(t.nodes.size());
  std::vector<std::size_t> out;out.reserve(t.nodes.size());std::vector<unsigned char> seen(t.nodes.size());
  if(t.nodes.empty()){require(!t.root);return out;}
  require(t.root && t.root->value<t.nodes.size());out.push_back(t.root->value);seen[t.root->value]=1;
  for(std::size_t i=0;i<out.size();++i){b.work();const auto& node=t.nodes[out[i]];b.work(static_cast<std::uint64_t>(node.scope.size()));
    for(const auto c:node.children){b.work();require(c.value<t.nodes.size() && !seen[c.value]);seen[c.value]=1;out.push_back(c.value);}}
  require(out.size()==t.nodes.size());return out;
}
UInt depth_score(CandidateScore& score,const Evidence& e,Budget& b) {
  const auto& tree=score.candidate.tree();const auto sorted=order(tree,b);
  b.vector_items<std::uint64_t>(tree.nodes.size());std::vector<std::uint64_t> depths(tree.nodes.size());
  b.vector_items<std::optional<TableId>>(score.candidate.query().atoms.size());
  std::vector<std::optional<TableId>> bases(score.candidate.query().atoms.size());
  for(const auto& input:e.plan().inputs()){b.work();require(input.occurrence.value<bases.size() && !bases[input.occurrence.value]);bases[input.occurrence.value]=input.base;}
  b.vector_items<UInt>(e.weights().size());std::vector<UInt> table_sums(e.weights().size());
  b.vector_items<OccurrenceDepth>(e.plan().inputs().size());score.depths.reserve(e.plan().inputs().size());
  for(const auto id:sorted){b.work();const auto& n=tree.nodes[id];
    if(n.kind==NodeKind::native){require(depths[id]!=UINT64_MAX);++depths[id];require(n.occurrence && *n.occurrence<bases.size() && bases[*n.occurrence]);
      const auto base=*bases[*n.occurrence];require(base.value<table_sums.size() && e.weights()[base.value].table==base);
      score.depths.push_back({OccurrenceId{*n.occurrence},base,depths[id]});
      table_sums[base.value]=UInt::add(table_sums[base.value],UInt::from(depths[id],b),b);}
    for(const auto child:n.children)depths[child.value]=depths[id];
  }
  require(score.depths.size()==e.plan().inputs().size());
  b.vector_items<TableDepth>(e.weights().size());score.table_depths.reserve(e.weights().size());UInt total;
  for(std::size_t r=0;r<e.weights().size();++r){const auto& w=e.weights()[r];
    const auto weight=UInt::add(UInt::from(w.inserts,b),UInt::from(w.erases,b),b);
    const auto term=UInt::multiply(weight,table_sums[r],b);total=UInt::add(total,term,b);
    score.table_depths.push_back({w.table,w.inserts,w.erases,table_sums[r].decimal(b),term.decimal(b)});
  }
  score.numerator=total.decimal(b);score.denominator=UInt::from(e.denominator(),b).decimal(b);return total;
}
PhysicalPlan lower(const MinimumHeightCandidate& candidate,const PhysicalPlan& basis,Budget& b) {
  b.time();const auto prior=b.usage;
  PhysicalLimits host;host.work_limit=b.limits.lowering_work-prior.lowering_work;host.identity.work_limit=b.limits.identity_work-prior.identity_work;
  io::ProgramReadLimits replay;
  replay.binding.work_limit=b.limits.binding_replay_work-prior.binding_replay_work;
  replay.normalization.work_limit=b.limits.normalization_work-prior.normalization_work;
  if(basis.normalized()){
    replay.binding.expression_limit=basis.normalized()->binding.limits.expression_limit;
    replay.binding.recursion_limit=basis.normalized()->binding.limits.recursion_limit;
  }
  // On failure native blocking calls expose no partial work count. Reserve
  // their complete remaining allowances; refund unused amounts only on success.
  b.usage.lowering_work=b.limits.lowering_work;b.usage.identity_work=b.limits.identity_work;
  if(basis.normalized()){b.usage.binding_replay_work=b.limits.binding_replay_work;b.usage.normalization_work=b.limits.normalization_work;}
  PhysicalPlan out=basis.normalized()?lower_normalized(*basis.normalized(),candidate.tree(),basis.options(),replay,host):
      lower_tree(candidate.catalog(),candidate.query(),candidate.tree(),basis.options(),host);
  b.usage.lowering_work=prior.lowering_work;b.usage.identity_work=prior.identity_work;
  Budget::add(b.usage.lowering_work,out.work(),b.limits.lowering_work,Stop::lowering_limit);
  Budget::add(b.usage.identity_work,out.identity().work,b.limits.identity_work,Stop::lowering_limit);
  if(out.normalized()){
    b.usage.binding_replay_work=prior.binding_replay_work;b.usage.normalization_work=prior.normalization_work;
    Budget::add(b.usage.binding_replay_work,out.normalized()->binding.work,b.limits.binding_replay_work,Stop::lowering_limit);
    Budget::add(b.usage.normalization_work,out.normalized()->work,b.limits.normalization_work,Stop::lowering_limit);
  }
  require(out.inputs().size()==basis.inputs().size());
  for(std::size_t i=0;i<out.inputs().size();++i){b.work();require(out.inputs()[i].occurrence==basis.inputs()[i].occurrence && out.inputs()[i].base==basis.inputs()[i].base,Stop::binding_mismatch);}
  b.time();return out;
}
UInt project(const UInt& value,std::size_t width,Budget& b){b.work();return width==0 && !value.zero()?UInt::from(1,b):value;}
UInt memory_score(CandidateScore& score,const Evidence& e,Budget& b) {
  const auto sorted=order(score.candidate.tree(),b);
  plan_source_payload(score.candidate,e.plan(),b);
  auto admitted=lower(score.candidate,e.plan(),b);
  require(admitted.identity().semantic_sha256==e.plan().identity().semantic_sha256 &&
      admitted.identity().output_contract_sha256==e.plan().identity().output_contract_sha256 &&
      admitted.identity().cost_inputs_sha256==e.plan().identity().cost_inputs_sha256 &&
      admitted.identity().plan_cache_sha256==e.plan().identity().plan_cache_sha256);
  plan_compiled_payload(admitted,b);
  score.modeled_plan=std::move(admitted);const auto& p=*score.modeled_plan;
  b.vector_items<std::optional<std::uint64_t>>(p.source_catalog().tables.size());
  std::vector<std::optional<std::uint64_t>> rows(p.source_catalog().tables.size());
  for(const auto& r:e.sources()){b.work();require(r.table.value<rows.size() && !rows[r.table.value]);rows[r.table.value]=r.rows;}
  struct Bounds {UInt records,survivors,parent;std::optional<UInt> visible;};
  b.vector_items<Bounds>(p.nodes().size());std::vector<Bounds> nodes(p.nodes().size());
  b.vector_items<UInt>(p.relations().size());std::vector<UInt> relations(p.relations().size());
  for(auto it=sorted.rbegin();it!=sorted.rend();++it){b.work();require(*it<p.nodes().size());const auto& n=p.nodes()[*it];auto& v=nodes[*it];
    if(n.kind==NodeKind::native){require(n.occurrence && n.occurrence->value<p.inputs().size());const auto base=p.inputs()[n.occurrence->value].base;require(base.value<rows.size() && rows[base.value]);v.records=project(UInt::from(*rows[base.value],b),n.layout.fields().size(),b);}
    else {UInt sum;for(const auto child:n.children){b.work();require(child.value<nodes.size());sum=UInt::add(sum,nodes[child.value].parent,b);}v.records=project(sum,n.layout.fields().size(),b);}
    v.survivors=v.records;v.parent=project(v.records,n.parent_key.target().fields().size(),b);
    require(n.records.value<relations.size() && n.survivors.value<relations.size() && n.parent_support.value<relations.size());
    relations[n.records.value]=v.records;relations[n.survivors.value]=v.survivors;relations[n.parent_support.value]=v.parent;
    if(n.visible_relation){require(n.visible_projection && n.visible_relation->value<relations.size());v.visible=project(v.records,n.visible_projection->target().fields().size(),b);relations[n.visible_relation->value]=*v.visible;}
  }
  b.vector_items<PopulationBound>(p.nodes().size());score.populations.reserve(p.nodes().size());
  for(std::size_t i=0;i<nodes.size();++i){const auto& v=nodes[i];score.populations.push_back({NodeId{i},v.records.decimal(b),v.survivors.decimal(b),v.parent.decimal(b),v.visible?std::optional<std::string>{v.visible->decimal(b)}:std::nullopt});}
  UInt total;
  const auto append=[&](RelationId relation,std::optional<IndexRequirementId> index,std::size_t width){require(relation.value<relations.size());b.vector_items<SlotTerm>(1);
    const auto factor=UInt::add(UInt::from(static_cast<std::uint64_t>(width),b),UInt::from(1,b),b);
    const auto term=UInt::multiply(relations[relation.value],factor,b);total=UInt::add(total,term,b);
    score.slot_terms.push_back({relation,index,width,relations[relation.value].decimal(b),term.decimal(b)});};
  for(const auto& r:p.relations()){b.work();if(r.role!=RelationRole::physical_base)append(r.id,{},r.layout.fields().size());}
  for(std::size_t i=0;i<p.indexes().size();++i){b.work();const auto& x=p.indexes()[i];require(x.id.value==i);append(x.relation,x.id,x.projection.fields().size());}
  score.slots=total.decimal(b);return total;
}
} // namespace
} // namespace detail

Attempt rank(const CandidateSnapshot& snapshot,const Request& request,const std::optional<Evidence>& evidence) noexcept {
  using namespace detail;Attempt attempt;std::optional<Budget> budget;
  try{
    attempt.usage=evidence?evidence->preparation_usage():Usage{};
    budget.emplace(request.limits,attempt.usage);auto& b=*budget;b.work();
    require(supported(request.policy) && (request.fallback==Fallback::height_only || request.fallback==Fallback::require_evidence),Stop::invalid_limits);
    require(snapshot.valid(),Stop::invalid_handle);const auto proof=snapshot.original_proof();require(proof.valid(),Stop::invalid_handle);
    const auto count=snapshot.candidate_count();require(count<=request.limits.candidates,Stop::candidate_limit);
    if(!count){attempt.stop=Stop::no_candidates;attempt.usage=b.usage;return attempt;}
    const auto proof_binding=proof.binding();const auto encoded=binding(proof_binding.catalog(),proof_binding.query(),b);
    if(evidence)require(equal_bytes(encoded,Factory::data(*evidence).binding,b),Stop::binding_mismatch);
    b.vector_items<CandidateScore>(count);b.vector_items<UInt>(count);b.bytes(sizeof(ResultData));
    auto data=std::make_shared<ResultData>(snapshot,request,evidence);data->scores.reserve(count);std::vector<UInt> values;values.reserve(count);
    // Complete structural admission, including binding/key checks, precedes
    // evidence eligibility and every score calculation.
    for(std::size_t i=0;i<count;++i){b.work();auto c=snapshot.candidate(i);require(c && c->valid(),Stop::invalid_handle);
      require(c->height()==proof.height() && c->original_proof().height()==proof.height() && same_context(c->context(),snapshot.context()));
      require(equal_bytes(encoded,binding(c->catalog(),c->query(),b),b),Stop::binding_mismatch);
      for(const auto& old:data->scores)require(!equal_bytes(old.structural_key,c->structural_key(),b));
      b.keys(static_cast<std::uint64_t>(c->structural_key().size()));b.bytes(static_cast<std::uint64_t>(c->structural_key().size()));
      data->scores.push_back(CandidateScore{*c,c->structural_key(),c->height(),"0","1","0",{},{},{},{},{}});
    }
    Reasons unavailable=0;
    if(request.policy!=Policy::height_only)unavailable=evidence?(request.policy==Policy::committed_input_native_depth?evidence->depth_reasons():evidence->memory_reasons()):reason(Reason::not_captured);
    if(unavailable){attempt.reasons=unavailable;if(request.fallback==Fallback::require_evidence){attempt.stop=Stop::evidence_unavailable;attempt.usage=b.usage;return attempt;}data->effective=Policy::height_only;data->fallback=unavailable;}
    for(auto& score:data->scores){UInt value;
      if(data->effective==Policy::committed_input_native_depth)value=depth_score(score,*evidence,b);
      else if(data->effective==Policy::tuple_index_slots)value=memory_score(score,*evidence,b);
      values.push_back(value);++attempt.evaluated;
    }
    std::size_t selected=0;
    for(std::size_t i=1;i<count;++i){const auto cmp=UInt::compare(values[i],values[selected],b);
      if(cmp<0 || (cmp==0 && key_less(data->scores[i].structural_key,data->scores[selected].structural_key,b)))selected=i;}
    b.time();data->selected=selected;data->usage=b.usage;
    attempt.result=Factory::result(std::move(data));attempt.stop=Stop::complete;
  }catch(const Failure& failure){attempt.stop=failure.stop;}
   catch(const std::bad_alloc&){attempt.stop=Stop::allocation_failure;}
   catch(const Error& error){attempt.stop=error.code()=="resource_limit"?Stop::lowering_limit:Stop::internal_error;}
   catch(...){attempt.stop=Stop::internal_error;}
  if(budget){attempt.usage=budget->usage;}
  return attempt;
}
} // namespace crown::planner::ranking
