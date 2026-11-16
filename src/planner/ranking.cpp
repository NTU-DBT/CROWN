#include "ranking_detail.hpp"
#include "candidate_binding.hpp"
#include "ranking_payload.hpp"
#include "compiled_source.hpp"
#include "crown/planner/lower.hpp"
#include "crown/api/error.hpp"
#include "crown/resource/ownership.hpp"
#include <algorithm>
#include <new>

namespace crown::planner::ranking {
CandidateScore::CandidateScore(const resource::MemoryAccount& account,MinimumHeightCandidate value)
    :candidate(std::move(value)),structural_key(candidate.structural_key().begin(),candidate.structural_key().end(),detail::score_allocator<char>(account)),
     height(candidate.height()),numerator("0",detail::score_allocator<char>(account)),denominator("1",detail::score_allocator<char>(account)),
     slots("0",detail::score_allocator<char>(account)),depths(detail::score_allocator<OccurrenceDepth>(account)),
     table_depths(detail::score_allocator<TableDepth>(account)),populations(detail::score_allocator<PopulationBound>(account)),
     slot_terms(detail::score_allocator<SlotTerm>(account)) {}
const CompiledProgram& Evidence::plan() const noexcept{return data_->plan;}
const EvidenceVector<InputWeight>& Evidence::weights() const noexcept{return data_->weights;}
const EvidenceVector<SourceCardinality>& Evidence::sources() const noexcept{return data_->sources;}
const EvidenceVector<SourceObservation>& Evidence::source_observations() const noexcept{return data_->source_observations;}
const EvidenceIdentity& Evidence::identity() const noexcept{return data_->identity;}
const CaptureAccounting& Evidence::capture_accounting() const noexcept{return data_->accounting;}
Reasons Evidence::depth_reasons() const noexcept{return data_->depth_reasons;}
Reasons Evidence::memory_reasons() const noexcept{return data_->memory_reasons;}
std::uint64_t Evidence::denominator() const noexcept{return data_->denominator;}
const Usage& Evidence::preparation_usage() const noexcept{return data_->preparation;}
const CandidateSnapshot& Result::snapshot() const noexcept{return data_->snapshot;}
const MinimumHeightCandidate& Result::selected() const noexcept{return data_->scores[data_->selected].candidate;}
std::size_t Result::selected_index() const noexcept{return data_->selected;}
const ScoreVector<CandidateScore>& Result::scores() const noexcept{return data_->scores;}
const resource::MemoryAccount& Result::account() const & noexcept{return data_->account;}
const std::optional<Evidence>& Result::evidence() const noexcept{return data_->evidence;}
const Request& Result::request() const noexcept{return data_->request;}
Policy Result::effective_policy() const noexcept{return data_->effective;}
Reasons Result::fallback_reasons() const noexcept{return data_->fallback;}
const Usage& Result::usage() const noexcept{return data_->usage;}
namespace detail {
template<class C,class Q> std::string binding_impl(const C& c,const Q& q,Budget& b) {
  b.time();b.check_all();
  const auto room=std::min(b.limits.binding_key_bytes-b.usage.binding_key_bytes,
      b.limits.payload_bytes-b.usage.payload_bytes);
  binding_detail::Budget cap{b.usage.work,b.usage.binding_key_bytes,b.limits.work,
      b.usage.binding_key_bytes+room};
  try {auto result=binding_detail::encode(c,q,&cap);b.bytes(static_cast<std::uint64_t>(result.size()));b.time();return result;}
  catch(const binding_detail::Limit& stop){throw Failure{stop.kind==binding_detail::LimitKind::work?Stop::work_limit:Stop::byte_limit};}
}
std::string binding(const Catalog& c,const Query& q,Budget& b) {return binding_impl(c,q,b);}
std::string binding(const program::Catalog& c,const program::Query& q,Budget& b) {return binding_impl(c,q,b);}
template<class C,class Q> EvidenceText native_binding_impl(const C& c,const Q& q,Budget& b,const resource::MemoryAccount& account,
    resource::MemoryPurpose purpose=resource::MemoryPurpose::capture,resource::MemoryAttribution owner=evidence_memory_owner) {
  b.time();b.check_all();
  const auto room=std::min(b.limits.binding_key_bytes-b.usage.binding_key_bytes,b.limits.payload_bytes-b.usage.payload_bytes);
  binding_detail::Budget cap{b.usage.work,b.usage.binding_key_bytes,b.limits.work,b.usage.binding_key_bytes+room};
  try {
    auto result=binding_detail::encode(c,q,account,purpose,owner,&cap);
    b.bytes(static_cast<std::uint64_t>(result.size()));b.time();return result;
  }catch(const binding_detail::Limit& stop){throw Failure{stop.kind==binding_detail::LimitKind::work?Stop::work_limit:Stop::byte_limit};}
}
EvidenceText binding(const Catalog& c,const Query& q,Budget& b,const resource::MemoryAccount& account) {return native_binding_impl(c,q,b,account);}
EvidenceText binding(const program::Catalog& c,const program::Query& q,Budget& b,const resource::MemoryAccount& account) {return native_binding_impl(c,q,b,account);}
ScoreText score_binding(const Catalog& c,const Query& q,Budget& b,const resource::MemoryAccount& account) {return native_binding_impl(c,q,b,account,resource::MemoryPurpose::scratch,score_memory_owner);}
ScoreText score_binding(const program::Catalog& c,const program::Query& q,Budget& b,const resource::MemoryAccount& account) {return native_binding_impl(c,q,b,account,resource::MemoryPurpose::scratch,score_memory_owner);}
// Compare equal-length inputs byte by byte until the first mismatch;
// equality requires all positions. Length mismatch skips byte traversal.
bool equal_bytes(std::string_view a,std::string_view c,Budget& b) {
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
bool key_less(std::string_view a,std::string_view c,Budget& b) {
  const auto n=std::min(a.size(),c.size());
  for(std::size_t i=0;i<n;++i){b.keys(2);const auto x=static_cast<unsigned char>(a[i]),y=static_cast<unsigned char>(c[i]);if(x!=y)return x<y;}
  return a.size()<c.size();
}
Scratch<std::size_t> order(const FreeConnexTree& t,Budget& b,const resource::MemoryAccount& account) {
  b.vector_items<std::size_t>(t.nodes.size());b.vector_items<unsigned char>(t.nodes.size());
  Scratch<std::size_t> out(scratch_allocator<std::size_t>(account));out.reserve(t.nodes.size());
  Scratch<unsigned char> seen(t.nodes.size(),0,scratch_allocator<unsigned char>(account));
  if(t.nodes.empty()){require(!t.root);return out;}
  require(t.root && t.root->value<t.nodes.size());out.push_back(t.root->value);seen[t.root->value]=1;
  for(std::size_t i=0;i<out.size();++i){b.work();const auto& node=t.nodes[out[i]];b.work(static_cast<std::uint64_t>(node.scope.size()));
    for(const auto c:node.children){b.work();require(c.value<t.nodes.size() && !seen[c.value]);seen[c.value]=1;out.push_back(c.value);}}
  require(out.size()==t.nodes.size());return out;
}
// Physical committed inserts/erases weight native-only occurrence depths.
// This workload proxy is neither measured maintenance work nor elapsed time.
UInt depth_score(CandidateScore& score,const Evidence& e,Budget& b) {
  const auto account=score.depths.get_allocator().account();const auto& query=score.candidate.query();
  const bool constant=query.contradiction && !query.atoms.empty();
  // The body keeps its proof height; only executable geometry is empty.
  const FreeConnexTree empty;
  const auto& tree=constant?empty:score.candidate.tree();const auto sorted=order(tree,b,account);
  b.vector_items<std::uint64_t>(tree.nodes.size());Scratch<std::uint64_t> depths(tree.nodes.size(),0,scratch_allocator<std::uint64_t>(account));
  const auto occurrences=constant?std::size_t{0}:query.atoms.size();
  b.vector_items<std::optional<TableId>>(occurrences);
  Scratch<std::optional<TableId>> bases(occurrences,std::optional<TableId>{},scratch_allocator<std::optional<TableId>>(account));
  for(const auto& input:e.plan().inputs()){b.work();require(input.occurrence.value<bases.size() && !bases[input.occurrence.value]);bases[input.occurrence.value]=input.base;}
  b.vector_items<UInt>(e.weights().size());Scratch<UInt> table_sums(e.weights().size(),UInt{},scratch_allocator<UInt>(account));
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
    score.table_depths.push_back({w.table,w.inserts,w.erases,table_sums[r].decimal(b,account),term.decimal(b,account)});
  }
  score.numerator=total.decimal(b,account);score.denominator=UInt::from(e.denominator(),b).decimal(b,account);return total;
}
CompiledProgram lower(const MinimumHeightCandidate& candidate,const CompiledProgram& basis,Budget& b,const resource::MemoryAccount& account) {
  b.time();const auto prior=b.usage;
  PhysicalLimits host;host.work_limit=b.limits.lowering_work-prior.lowering_work;host.identity.work_limit=b.limits.identity_work-prior.identity_work;
  program::ReplanLimits limits;limits.physical=host;
  limits.binding_replay_work=b.limits.binding_replay_work-prior.binding_replay_work;
  limits.normalization_work=b.limits.normalization_work-prior.normalization_work;
  // On failure native blocking calls expose no partial work count. Reserve
  // their complete remaining allowances; refund unused amounts only on success.
  b.usage.lowering_work=b.limits.lowering_work;b.usage.identity_work=b.limits.identity_work;
  if(basis.normalized()){b.usage.binding_replay_work=b.limits.binding_replay_work;b.usage.normalization_work=b.limits.normalization_work;}
  auto out=CompiledProgram::replan_into(account,basis,candidate,limits);
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
// Candidate-local population upper bounds produce abstract tuple/index
// slots. Relowering and scratch have real costs; the score is not byte usage.
UInt memory_score(CandidateScore& score,const Evidence& e,Budget& b) {
  const auto account=score.depths.get_allocator().account();const auto& query=score.candidate.query();
  const bool constant=query.contradiction && !query.atoms.empty();
  // The body keeps its proof height; only executable geometry is empty.
  const FreeConnexTree empty;
  const auto& tree=constant?empty:score.candidate.tree();const auto sorted=order(tree,b,account);
  plan_source_payload(score.candidate,e.plan(),b);
  auto admitted=lower(score.candidate,e.plan(),b,account);
  require(admitted.identity().semantic_sha256==e.plan().identity().semantic_sha256 &&
      admitted.identity().output_contract_sha256==e.plan().identity().output_contract_sha256 &&
      admitted.identity().cost_inputs_sha256==e.plan().identity().cost_inputs_sha256 &&
      admitted.identity().plan_cache_sha256==e.plan().identity().plan_cache_sha256);
  plan_compiled_payload(admitted,b);
  score.modeled_plan=std::move(admitted);const auto& p=*score.modeled_plan;
  // Eligibility, lowering, identity and payload admission still precede this
  // exact zero. No executable populations need source-sized scratch arrays.
  if(constant) {score.slots=UInt{}.decimal(b,account);return {};}
  b.vector_items<std::optional<std::uint64_t>>(p.source_catalog().tables.size());
  Scratch<std::optional<std::uint64_t>> rows(p.source_catalog().tables.size(),std::optional<std::uint64_t>{},scratch_allocator<std::optional<std::uint64_t>>(account));
  for(const auto& r:e.sources()){b.work();require(r.table.value<rows.size() && !rows[r.table.value]);rows[r.table.value]=r.rows;}
  struct Bounds {UInt records,survivors,parent;std::optional<UInt> visible;};
  b.vector_items<Bounds>(p.nodes().size());Scratch<Bounds> nodes(p.nodes().size(),Bounds{},scratch_allocator<Bounds>(account));
  b.vector_items<UInt>(p.relations().size());Scratch<UInt> relations(p.relations().size(),UInt{},scratch_allocator<UInt>(account));
  for(auto it=sorted.rbegin();it!=sorted.rend();++it){b.work();require(*it<p.nodes().size());const auto& n=p.nodes()[*it];auto& v=nodes[*it];
    if(n.kind==NodeKind::native){require(n.occurrence && n.occurrence->value<p.inputs().size());const auto base=p.inputs()[n.occurrence->value].base;require(base.value<rows.size() && rows[base.value]);v.records=project(UInt::from(*rows[base.value],b),n.layout.fields().size(),b);}
    else {UInt sum;for(const auto child:n.children){b.work();require(child.value<nodes.size());sum=UInt::add(sum,nodes[child.value].parent,b);}v.records=project(sum,n.layout.fields().size(),b);}
    v.survivors=v.records;v.parent=project(v.records,n.parent_key.target().fields().size(),b);
    require(n.records.value<relations.size() && n.survivors.value<relations.size() && n.parent_support.value<relations.size());
    relations[n.records.value]=v.records;relations[n.survivors.value]=v.survivors;relations[n.parent_support.value]=v.parent;
    if(n.visible_relation){require(n.visible_projection && n.visible_relation->value<relations.size());v.visible=project(v.records,n.visible_projection->target().fields().size(),b);relations[n.visible_relation->value]=*v.visible;}
  }
  b.vector_items<PopulationBound>(p.nodes().size());score.populations.reserve(p.nodes().size());
  for(std::size_t i=0;i<nodes.size();++i){const auto& v=nodes[i];score.populations.push_back({NodeId{i},v.records.decimal(b,account),v.survivors.decimal(b,account),v.parent.decimal(b,account),v.visible?std::optional<ScoreText>{v.visible->decimal(b,account)}:std::nullopt});}
  UInt total;
  const auto append=[&](RelationId relation,std::optional<IndexRequirementId> index,std::size_t width){require(relation.value<relations.size());b.vector_items<SlotTerm>(1);
    const auto factor=UInt::add(UInt::from(static_cast<std::uint64_t>(width),b),UInt::from(1,b),b);
    const auto term=UInt::multiply(relations[relation.value],factor,b);total=UInt::add(total,term,b);
    score.slot_terms.push_back({relation,index,width,relations[relation.value].decimal(b,account),term.decimal(b,account)});};
  for(const auto& r:p.relations()){b.work();if(r.role!=RelationRole::physical_base)append(r.id,{},r.layout.fields().size());}
  for(std::size_t i=0;i<p.indexes().size();++i){b.work();const auto& x=p.indexes()[i];require(x.id.value==i);append(x.relation,x.id,x.projection.fields().size());}
  score.slots=total.decimal(b,account);return total;
}
} // namespace
} // namespace detail

namespace {
// Admit every retained candidate before evidence fallback/scoring. Publish
// all scores together; private RAII handles failure without partial selection.
Attempt rank_impl(const resource::MemoryAccount* supplied,const CandidateSnapshot& snapshot,const Request& request,const std::optional<Evidence>& evidence) noexcept {
  using namespace detail;Attempt attempt;std::optional<Budget> budget;
  try{
    attempt.usage=evidence?evidence->preparation_usage():Usage{};
    budget.emplace(request.limits,attempt.usage);auto& b=*budget;b.work();
    require(supported(request.policy) && (request.fallback==Fallback::height_only || request.fallback==Fallback::require_evidence),Stop::invalid_limits);
    require(snapshot.valid(),Stop::invalid_handle);const auto proof=snapshot.original_proof();require(proof.valid(),Stop::invalid_handle);
    const auto count=snapshot.candidate_count();require(count<=request.limits.candidates,Stop::candidate_limit);
    if(!count){attempt.stop=Stop::no_candidates;attempt.usage=b.usage;return attempt;}
    if(supplied)require(bool(*supplied),Stop::invalid_limits);
    const auto account=supplied?*supplied:(evidence?evidence->plan().account():resource::MemoryAccount::create(UINT64_MAX));b.memory=account;
    const auto proof_binding=proof.binding();const auto encoded=score_binding(proof_binding.catalog(),proof_binding.query(),b,account);
    if(evidence)require(equal_bytes(encoded,Factory::data(*evidence).binding,b),Stop::binding_mismatch);
    b.vector_items<CandidateScore>(count);b.vector_items<UInt>(count);b.bytes(sizeof(ResultData));
    auto data=resource::make_accounted_shared<ResultData>(score_memory_owner,account,resource::MemoryPurpose::capture,account,snapshot,request,evidence);
    data->scores.reserve(count);Scratch<UInt> values(scratch_allocator<UInt>(account));values.reserve(count);
    // Complete structural admission, including binding/key checks, precedes
    // evidence eligibility and every score calculation.
    for(std::size_t i=0;i<count;++i){b.work();auto c=snapshot.candidate(i);require(c && c->valid(),Stop::invalid_handle);
      require(c->height()==proof.height() && c->original_proof().height()==proof.height() && same_context(c->context(),snapshot.context()));
      require(equal_bytes(encoded,score_binding(c->catalog(),c->query(),b,account),b),Stop::binding_mismatch);
      // Full-key uniqueness scans earlier candidates: O(C^2) comparisons,
      // each with variable byte width; the candidate cap remains explicit.
      for(const auto& old:data->scores)require(!equal_bytes(old.structural_key,c->structural_key(),b));
      b.keys(static_cast<std::uint64_t>(c->structural_key().size()));b.bytes(static_cast<std::uint64_t>(c->structural_key().size()));
      data->scores.emplace_back(account,*c);
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
   catch(const program::ReplanFailure& error){attempt.stop=error.fault()==program::ReplanFault::binding?Stop::binding_mismatch:Stop::lowering_limit;}
   catch(const storage::IndexFailure& error){attempt.stop=(error.code()=="storage_work_limit" || error.code()=="storage_capacity" ||
       error.code()=="storage_overflow")?Stop::lowering_limit:Stop::internal_error;}
   catch(const Error& error){attempt.stop=error.code()=="resource_limit"?Stop::lowering_limit:Stop::internal_error;}
   catch(...){attempt.stop=Stop::internal_error;}
  if(budget){attempt.usage=budget->usage;}
  return attempt;
}
} // namespace
Attempt rank(const CandidateSnapshot& snapshot,const Request& request,const std::optional<Evidence>& evidence) noexcept {
  return rank_impl(nullptr,snapshot,request,evidence);
}
Attempt rank_with_account(const resource::MemoryAccount& account,const CandidateSnapshot& snapshot,const Request& request,
    const std::optional<Evidence>& evidence) noexcept {return rank_impl(&account,snapshot,request,evidence);}
} // namespace crown::planner::ranking
