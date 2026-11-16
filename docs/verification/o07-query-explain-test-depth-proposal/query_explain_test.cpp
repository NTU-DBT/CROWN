#include "crown/io/query_explain.hpp"
#include "crown/api/error.hpp"
#include "tree_oracle.hpp"
#include "query_families.hpp"
#include <algorithm>
#include <cstdlib>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <limits>
#include <new>
#include <set>
#include <sstream>
#include <string>
#include <type_traits>
#include <utility>

namespace fault {
thread_local bool armed=false, unexpected=false;
thread_local std::size_t remaining=0;
struct Unexpected {};
void check(){if(armed){if(remaining==0){if(unexpected)throw Unexpected{};throw std::bad_alloc{};}--remaining;}}
void* allocate(std::size_t n){check();if(void* p=std::malloc(n==0?1:n))return p;throw std::bad_alloc{};}
}
void* operator new(std::size_t n){return fault::allocate(n);}
void* operator new[](std::size_t n){return fault::allocate(n);}
void operator delete(void* p) noexcept{std::free(p);}
void operator delete[](void* p) noexcept{std::free(p);}
void operator delete(void* p,std::size_t) noexcept{std::free(p);}
void operator delete[](void* p,std::size_t) noexcept{std::free(p);}
void* operator new(std::size_t n,std::align_val_t a){fault::check();void* p=nullptr;if(posix_memalign(&p,static_cast<std::size_t>(a),n==0?1:n)!=0)throw std::bad_alloc{};return p;}
void* operator new[](std::size_t n,std::align_val_t a){return ::operator new(n,a);}
void operator delete(void* p,std::align_val_t) noexcept{std::free(p);}
void operator delete[](void* p,std::align_val_t) noexcept{std::free(p);}
void operator delete(void* p,std::size_t,std::align_val_t) noexcept{std::free(p);}
void operator delete[](void* p,std::size_t,std::align_val_t) noexcept{std::free(p);}

namespace {
using namespace crown;
using namespace crown::planner;
using namespace crown::observability;
namespace fx=crown::query_explain_fixture;
using Report=QueryExplanation;
static_assert(!std::is_default_constructible_v<Report>);
static_assert(!std::is_constructible_v<Report,SearchProgress>);
static_assert(!std::is_constructible_v<Report,ReplayProgress>);
static_assert(!std::is_constructible_v<Report,OracleResult>);
static_assert(!std::is_constructible_v<Report,HeightCertificate>);
static_assert(!std::is_constructible_v<Report,FreeConnexTree>);
static_assert(!std::is_constructible_v<Report,bool,bool>);
template<class T> concept ReportFrom=requires(T v){Report::from(v);};
static_assert(!ReportFrom<SearchProgress> && !ReportFrom<ReplayProgress> && !ReportFrom<HeightCertificate> && !ReportFrom<OracleResult>);
void require(bool value,const char* reason){if(!value)throw std::runtime_error(reason);}
template<class F> void rejects(F&& f,const char* code=nullptr){bool caught=false;try{f();}catch(const Error& e){caught=true;if(code)require(e.code()==code,"wrong rejection code");}require(caught,"expected rejection");}
bool same(const SearchStatistics& a,const SearchStatistics& b){return a.work==b.work&&a.states==b.states&&a.partitions==b.partitions&&a.candidates==b.candidates&&a.cache_hits==b.cache_hits&&a.certificate_work==b.certificate_work&&a.hierarchy_tests==b.hierarchy_tests&&a.hierarchy_hits==b.hierarchy_hits&&a.singleton_hits==b.singleton_hits&&a.empty_body_hits==b.empty_body_hits&&a.component_splits==b.component_splits&&a.symmetry_skips==b.symmetry_skips&&a.bound_prunes==b.bound_prunes;}
bool same(const SearchProgress& a,const SearchProgress& b){return a.phase==b.phase&&a.last_stop==b.last_stop&&a.result==b.result&&a.heights==b.heights&&a.producer_complete==b.producer_complete&&a.proof_complete==b.proof_complete&&a.producer==b.producer&&a.replay==b.replay&&same(a.structural,b.structural)&&a.limit_revision==b.limit_revision;}
bool same(const ReplayProgress& a,const ReplayProgress& b){return a.phase==b.phase&&a.last_stop==b.last_stop&&a.complete==b.complete&&a.valid==b.valid&&a.checked_claims==b.checked_claims&&a.work==b.work&&a.limit_revision==b.limit_revision;}
ContinuationLimits unlimited(){ContinuationLimits l;l.producer.work.reset();l.replay.work.reset();l.logical_depth.reset();return l;}
ReplayOptions replay_unlimited(){ReplayOptions o;o.limits.work.reset();o.logical_depth.reset();return o;}
SearchOptions options(SearchPolicy policy=SearchPolicy::strict){SearchOptions o;o.policy=policy;o.limits=unlimited();return o;}
Report capture(const ExactSearch& s){const auto before=s.progress();auto r=Report::capture(s);require(same(before,s.progress()),"capture advanced search");require(same(before,*r.search_progress()),"search progress copy mismatch");require(&r.binding().catalog()==&s.binding().catalog(),"binding catalog identity lost");require(&r.binding().query()==&s.binding().query(),"binding query identity lost");return r;}
Report capture(const CertificateReplay& s){const auto before=s.progress();auto r=Report::capture(s);require(same(before,s.progress()),"capture advanced replay");require(same(before,*r.replay_progress()),"replay progress copy mismatch");return r;}
void no_tree(const Report& r){require(!r.witness(),"unexpected witness");rejects([&]{static_cast<void>(io::write_query_explain_tree_json(r));},"query_explain_no_witness");rejects([&]{static_cast<void>(io::write_query_explain_dot(r));},"query_explain_no_witness");}
std::filesystem::path destination;
std::size_t serial=0;
void file(const std::filesystem::path& p,const std::string& value){std::ofstream out(p,std::ios::binary);out.write(value.data(),static_cast<std::streamsize>(value.size()));require(static_cast<bool>(out),"write corpus");}
using Export=std::string(*)(const Report&,io::QueryExplainTextLimits);
void boundary(const Report& r,Export fn){const auto text=fn(r,{});require(!text.empty(),"empty export");require(fn(r,{text.size()})==text,"exact output boundary rejected");rejects([&]{static_cast<void>(fn(r,{text.size()-1}));},"resource_limit");rejects([&]{static_cast<void>(fn(r,{0}));},"resource_limit");}
std::string hex(std::string_view text){std::string out;constexpr char digits[]="0123456789abcdef";for(char c:text){auto v=static_cast<unsigned char>(c);out+=digits[v>>4U];out+=digits[v&15U];}return out.empty()?"-":out;}
template<class T> void opt(std::ostream& out,const std::optional<T>& x){if(x)out<<*x;else out<<"null";}
template<class Range> void ids(std::ostream& out,const Range& xs){out<<xs.size();for(auto x:xs)out<<' '<<x.value;}
void expected(const Report& r,const std::filesystem::path& path){std::ostringstream out;out<<"status "<<static_cast<int>(r.height_status())<<" source "<<static_cast<int>(r.source())<<" lower ";opt(out,r.lower());out<<" upper ";opt(out,r.upper());out<<'\n';
 if(r.witness()){const auto& t=r.witness()->tree();out<<"tree ";if(t.root)out<<t.root->value;else out<<"null";out<<' ';opt(out,t.claimed_native_height);out<<' '<<t.nodes.size()<<'\n';out<<"connex ";if(t.claimed_connex)ids(out,*t.claimed_connex);else out<<"null";out<<'\n';for(const auto& n:t.nodes){out<<"node "<<hex(n.id)<<' '<<static_cast<int>(n.kind)<<' ';opt(out,n.occurrence);out<<' ';ids(out,n.scope);out<<' ';ids(out,n.children);out<<' ';if(n.claimed_separator)ids(out,*n.claimed_separator);else out<<"null";out<<'\n';}}
 if(const auto* c=r.certificate()){out<<"certificate "<<hex(c->algorithm)<<' ';opt(out,c->minimum_height);out<<' '<<c->lower_bounds.size()<<'\n';for(const auto& e:c->lower_bounds){out<<"claim "<<e.generalized_allowed<<' '<<e.connex_reachable<<' ';opt(out,e.bound);out<<' '<<e.occurrences.size();for(auto v:e.occurrences)out<<' '<<v;out<<'\n';}}
 const auto count=[&](const char* name,const WorkCounters& c){out<<name<<' '<<c.attempted<<' '<<c.committed_transitions<<' '<<c.allocation_failures<<' '<<c.active_nanoseconds<<' '<<c.current_depth<<' '<<c.peak_depth<<'\n';};if(r.search_progress()){count("producer",r.search_progress()->producer);count("search_replay",r.search_progress()->replay);}if(r.replay_progress())count("replay",r.replay_progress()->work);file(path,out.str());}
void emit(const Report& r,const std::string& label){
 const auto base=destination/(std::to_string(serial++)+"-"+label);
 expected(r,base.string()+".expected");
 file(base.string()+".report.json",io::write_query_explain_json(r));file(base.string()+".txt",io::write_query_explain_text(r));
 if(r.witness()){file(base.string()+".tree.json",io::write_query_explain_tree_json(r));file(base.string()+".dot",io::write_query_explain_dot(r));}else no_tree(r);
}
void complete(ExactSearch& s,std::uint64_t quantum=17){while(s.progress().result==ResultKind::unfinished){const auto a=s.advance({quantum,{}});require(a.stopped_for==StopReason::quantum_work||a.stopped_for==StopReason::complete,"unexpected search resource/failure outcome");auto r=capture(s);require(!r.optimum()||r.search_progress()->proof_complete,"premature optimum");}require(s.progress().phase==SearchPhase::complete,"search did not complete");}
void complete(CertificateReplay& r,std::uint64_t quantum=13){while(!r.progress().complete){const auto a=r.advance({quantum,{}});require(a.stopped_for==StopReason::quantum_work||a.stopped_for==StopReason::complete,"unexpected replay resource/failure outcome");static_cast<void>(capture(r));}require(r.progress().valid&&r.checked().has_value(),"valid certificate did not replay");}
void terminal_matches(const Report& r,const OracleResult& expected){require(expected.status!=OracleStatus::resource_limit,"reference resource result is NOT an accepted skip");if(expected.status==OracleStatus::proven_minimum){require(r.optimum().has_value(),"reference positive disagreement");require(r.lower()==expected.minimum_height&&r.upper()==expected.minimum_height,"independent literal height mismatch");require(r.witness()->height()==*expected.minimum_height,"witness height mismatch");}else{require(r.infeasibility().has_value(),"reference negative disagreement");require(!r.lower()&&!r.upper()&&!r.witness(),"negative minted witness/bounds");}}
void family(){
 auto fixtures=fx::finite_three_variable_family();require(fixtures.size()==426,"finite family cardinality");auto anchors=fx::anchors();require(anchors.size()==11,"anchor cardinality");for(auto& f:anchors)fixtures.push_back(std::move(f));
 SearchLimits limits;limits.work_limit.reset();limits.recursion_limit.reset();limits.literal_scope_limit.reset();limits.time_limit.reset();
 std::size_t done=0;
 for(const auto& f:fixtures){
  const auto expected=reference::exhaustive_minimum_tree(f.catalog,f.query,limits);require(expected.status!=OracleStatus::resource_limit,"reference exhausted: no family skips allowed");
  if(f.expected_admissible)require(*f.expected_admissible==(expected.status==OracleStatus::proven_minimum),"anchor expectation disagrees with literal oracle");
  for(const auto policy:{SearchPolicy::strict,SearchPolicy::best_found}){
   auto s=ExactSearch::create(f.catalog,f.query,options(policy));auto early=capture(s);const auto early_progress=*early.search_progress();complete(s);require(same(early_progress,*early.search_progress()),"earlier report changed during family search");auto r=capture(s);terminal_matches(r,expected);
   auto replay=CertificateReplay::create(f.catalog,f.query,*r.certificate(),replay_unlimited());auto pending=capture(replay);no_tree(pending);complete(replay);auto checked=capture(replay);terminal_matches(checked,expected);
   auto typed=Report::from(*replay.checked());terminal_matches(typed,expected);
   if(f.name!="raw_native_string_constant"){emit(r,"family-search");emit(checked,"family-replay");}else{rejects([&]{static_cast<void>(io::write_query_explain_json(r));});}
  }
  ++done;std::cout<<"family "<<done<<"/437 "<<f.name<<'\n';
 }
 require(done==437,"family was capped");
}
void states(){
 const auto f=fx::hypergraph({3,6},7,"path");
 for(const auto policy:{SearchPolicy::strict,SearchPolicy::best_found}){
  auto s=ExactSearch::create(f.catalog,f.query,options(policy));auto initial=capture(s);const auto initial_json=io::write_query_explain_json(initial);emit(initial,"admitted");no_tree(initial);
  for(const auto q:{WorkQuantum{0,{}},WorkQuantum{1,std::chrono::nanoseconds{0}},WorkQuantum{1,std::chrono::nanoseconds{-1}}}){const auto before=s.progress();const auto a=s.advance(q);require(a.stopped_for==(q.work==0?StopReason::quantum_work:q.active_time->count()==0?StopReason::quantum_time:StopReason::invalid_quantum),"zero/invalid quantum result");require(same(before,s.progress()),"nonmutating quantum changed owner");}
  bool upper=false,publication_gap=false,preprocess=false,searching=false;std::set<SearchPhase> emitted;
  while(s.progress().result==ResultKind::unfinished){const auto a=s.advance({1,{}});require(a.stopped_for==StopReason::quantum_work||a.stopped_for==StopReason::complete,"single step unexpected stop");auto r=capture(s);const auto p=s.progress();
   preprocess=preprocess||p.phase==SearchPhase::preprocess;searching=searching||p.phase==SearchPhase::search;
   if(emitted.insert(p.phase).second)emit(r,"phase");
   if(p.heights.upper&&!p.proof_complete){upper=true;require(!r.optimum()&&!r.certificate(),"unpublished proof exposed");if(policy==SearchPolicy::strict){require(r.height_status()==QueryHeightStatus::owner_checked_upper_unpublished,"strict hidden upper classification");no_tree(r);}else{require(r.witness().has_value(),"best found upper missing");auto typed=Report::from(*r.witness());require(typed.height_status()==QueryHeightStatus::checked_upper&&!typed.optimum(),"upper minted optimum");emit(typed,"typed-upper");auto upper=*r.witness();auto upper_moved=std::move(upper);rejects([&]{static_cast<void>(Report::from(upper));});require(upper_moved.valid(),"upper move invalidated destination");} }
   if(p.producer_complete&&!p.proof_complete){publication_gap=true;require(!r.optimum()&&!r.infeasibility(),"producer completion minted proof");}
  }
  require(upper&&publication_gap&&preprocess&&searching,"required real lifecycle states not observed");require(io::write_query_explain_json(initial)==initial_json,"snapshot mutated");
  auto final=capture(s);auto optimum=*s.optimum();auto typed=Report::from(optimum);emit(typed,"typed-optimum");boundary(typed,io::write_query_explain_json);boundary(typed,io::write_query_explain_text);boundary(typed,io::write_query_explain_tree_json);boundary(typed,io::write_query_explain_dot);
  rejects([&]{static_cast<void>(Report::capture(s,{0,0}));},"resource_limit");require(same(*final.search_progress(),s.progress()),"capture cap mutated owner");
  auto moved=std::move(s);rejects([&]{static_cast<void>(Report::capture(s));});auto report_moved=std::move(final);rejects([&]{static_cast<void>(final.binding());},"invalid_query_explanation");auto handle_moved=std::move(optimum);rejects([&]{static_cast<void>(Report::from(optimum));});require(handle_moved.height()==*typed.upper(),"handle movement");
  moved.cancel();require(report_moved.optimum().has_value(),"report lost proof after cancellation");
 }
 // Positive quantum-time stop is an actual clock boundary; zero quantum was checked separately.
 {auto s=ExactSearch::create(f.catalog,f.query,options());const auto a=s.advance({UINT64_MAX,std::chrono::nanoseconds{1}});require(a.stopped_for==StopReason::quantum_time,"positive quantum-time stop");emit(capture(s),"quantum-time-search");}
 for(auto policy:{SearchPolicy::strict,SearchPolicy::best_found}){auto o=options(policy);o.limits.replay.active_time=std::chrono::nanoseconds{0};auto s=ExactSearch::create(f.catalog,f.query,o);StopReason stop;do{stop=s.advance({31,{}}).stopped_for;}while(stop==StopReason::quantum_work);require(stop==StopReason::total_time,"post-upper replay time gate");auto old=capture(s);require(old.upper().has_value()&&!old.optimum(),"post-upper time bound");emit(old,"post-upper-time");s.cancel();auto cancelled=capture(s);require(cancelled.upper()==old.upper()&&!cancelled.optimum(),"cancel lost upper or minted optimum");if(policy==SearchPolicy::strict)no_tree(cancelled);else require(cancelled.witness().has_value(),"cancel lost published upper");emit(cancelled,"post-upper-cancel");}
 // Resource ceilings before and after a genuinely checked upper, including replay gate.
 for(auto policy:{SearchPolicy::strict,SearchPolicy::best_found})for(int which=0;which<4;++which){auto o=options(policy);if(which==0)o.limits.producer.work=0;if(which==1)o.limits.producer.active_time=std::chrono::nanoseconds{0};if(which==2)o.limits.logical_depth=0;if(which==3)o.limits.replay.work=0;
  auto s=ExactSearch::create(f.catalog,f.query,o);StopReason stop=StopReason::none;do{stop=s.advance({100,{}}).stopped_for;}while(stop==StopReason::quantum_work);
  require(stop==(which==1?StopReason::total_time:which==2?StopReason::depth_limit:StopReason::total_work),"resource stop mismatch");auto before=capture(s);emit(before,"resource-search");if(which==3){require(before.upper().has_value()&&!before.optimum(),"replay ceiling failed to hold proof");if(policy==SearchPolicy::strict)no_tree(before);else require(before.witness().has_value(),"budget lost published upper");}auto less=s.limits();less.producer.work=0;require(s.raise_limits(less)!=LimitChange::applied||which==0,"limit decrease accepted");require(s.raise_limits(unlimited())==LimitChange::applied,"raise failed");complete(s);require(before.search_progress()->limit_revision==0,"old limit revision changed");emit(capture(s),"raised-search");}
 // Explicit ordered four-variable path. First checked upper precedes later producer recursion.
 // The ceiling is measured at the real first upper, never edited into progress or lowered on a live owner.
 {fx::Fixture depth_case{"central_first_three_atom_four_variable_path",{},{},{true}};
  depth_case.query.variables={{"x",ScalarType::int64},{"y",ScalarType::int64},{"z",ScalarType::int64},{"w",ScalarType::int64}};
  const std::vector<std::vector<std::size_t>> scopes={{1,2},{0,1},{2,3}};
  for(const auto& scope:scopes){Table table;table.name="D"+std::to_string(depth_case.catalog.tables.size());Atom atom{"d"+std::to_string(depth_case.query.atoms.size()),TableId{depth_case.catalog.tables.size()}, {}};for(auto v:scope){table.columns.push_back({depth_case.query.variables[v].name,ScalarType::int64});atom.terms.push_back(VariableId{v});}depth_case.catalog.tables.push_back(std::move(table));depth_case.query.atoms.push_back(std::move(atom));}
  for(std::size_t v=0;v<4;++v)depth_case.query.head.push_back({VariableId{v},depth_case.query.variables[v].name});
  SearchLimits reference_limits;reference_limits.work_limit.reset();reference_limits.recursion_limit.reset();reference_limits.literal_scope_limit.reset();reference_limits.time_limit.reset();
  const auto literal=reference::exhaustive_minimum_tree(depth_case.catalog,depth_case.query,reference_limits);require(literal.status==OracleStatus::proven_minimum&&literal.minimum_height==2,"extra depth fixture independent literal optimum");
  auto baseline=ExactSearch::create(depth_case.catalog,depth_case.query,options(SearchPolicy::best_found));std::optional<std::size_t> first_upper_depth;
  while(baseline.progress().result==ResultKind::unfinished){const auto step=baseline.advance({1,{}});require(step.stopped_for==StopReason::quantum_work||step.stopped_for==StopReason::complete,"depth baseline unexpected stop");if(step.progress.heights.upper&&!first_upper_depth)first_upper_depth=std::max<std::size_t>(1,step.progress.producer.peak_depth);}
  terminal_matches(capture(baseline),literal);require(first_upper_depth&&baseline.progress().producer.peak_depth>*first_upper_depth,"explicit fixture must deepen after first upper");
  std::cout<<"depth fixture first_upper_depth="<<*first_upper_depth<<" final_producer_peak="<<baseline.progress().producer.peak_depth<<" replay_peak="<<baseline.progress().replay.peak_depth<<'\n';
  for(auto policy:{SearchPolicy::strict,SearchPolicy::best_found}){auto o=options(policy);o.limits.logical_depth=*first_upper_depth;auto bounded=ExactSearch::create(depth_case.catalog,depth_case.query,o);StopReason stop;do{stop=bounded.advance({17,{}}).stopped_for;}while(stop==StopReason::quantum_work);require(stop==StopReason::depth_limit,"post-upper depth stop absent");auto retained=capture(bounded);const auto old_progress=*retained.search_progress();require(retained.upper()==2&&!retained.optimum()&&!retained.certificate()&&old_progress.phase==SearchPhase::search&&!old_progress.producer_complete,"post-upper producer-depth authority/state");if(policy==SearchPolicy::strict){require(retained.height_status()==QueryHeightStatus::owner_checked_upper_unpublished,"strict depth upper visibility");no_tree(retained);}else require(retained.witness().has_value()&&retained.height_status()==QueryHeightStatus::checked_upper,"best-found depth upper visibility");const auto frozen_json=io::write_query_explain_json(retained);emit(retained,"post-upper-depth");require(bounded.raise_limits(unlimited())==LimitChange::applied,"depth resume limit raise");complete(bounded);terminal_matches(capture(bounded),literal);require(same(old_progress,*retained.search_progress())&&io::write_query_explain_json(retained)==frozen_json,"depth-limit snapshot changed after resume");emit(capture(bounded),"post-upper-depth-resumed");}
 }
 auto cancelled=ExactSearch::create(f.catalog,f.query,options());static_cast<void>(cancelled.advance({7,{}}));cancelled.cancel();auto cancelled_report=capture(cancelled);require(cancelled_report.search_progress()->phase==SearchPhase::cancelled,"cancel phase");emit(cancelled_report,"cancel-search");
 auto negative=fx::hypergraph({3,6,5},7,"negative");negative.query.contradiction=true;auto n=ExactSearch::create(negative.catalog,negative.query,options());require(capture(n).lower()==1,"contradiction structural lower");complete(n);require(n.infeasibility().has_value(),"contradiction structural negative lost");emit(Report::from(*n.infeasibility()),"typed-negative");auto negative_handle=*n.infeasibility();auto negative_moved=std::move(negative_handle);rejects([&]{static_cast<void>(Report::from(negative_handle));});require(negative_moved.valid(),"negative move");rejects([&]{static_cast<void>(Report::from(negative_moved,{100000,0}));},"resource_limit");
 auto positive=ExactSearch::create(f.catalog,f.query,options());complete(positive);const auto cert=positive.optimum()->certificate();
 for(int which=0;which<4;++which){auto o=replay_unlimited();if(which==0)o.limits.work=0;if(which==1)o.limits.active_time=std::chrono::nanoseconds{0};if(which==2)o.logical_depth=0;auto r=CertificateReplay::create(f.catalog,f.query,cert,o);auto initial=capture(r);no_tree(initial);emit(initial,"replay-admitted");
  const auto before=r.progress();for(const auto q:{WorkQuantum{0,{}},WorkQuantum{1,std::chrono::nanoseconds{0}},WorkQuantum{1,std::chrono::nanoseconds{-1}}}){static_cast<void>(r.advance(q));require(same(before,r.progress()),"zero replay quantum mutated");}
  if(which<3){auto decreasing=r.limits();decreasing.limits.work=0;if(which!=0)require(r.raise_limits(decreasing)==LimitChange::not_monotone,"replay lowering accepted");const auto a=r.advance({100000,{}});require(a.stopped_for==(which==1?StopReason::total_time:which==2?StopReason::depth_limit:StopReason::total_work),"replay budget stop");emit(capture(r),"resource-replay");require(r.raise_limits(replay_unlimited())==LimitChange::applied,"replay raise");complete(r);}else{static_cast<void>(r.advance({5,{}}));emit(capture(r),"partial-replay");r.cancel();emit(capture(r),"cancel-replay");continue;}
  auto final=capture(r);emit(final,"valid-replay");emit(Report::from(*r.checked()),"typed-checked");auto moved=std::move(r);rejects([&]{static_cast<void>(Report::capture(r));});require(moved.checked().has_value(),"replay move lost checked");}
 {auto r=CertificateReplay::create(f.catalog,f.query,cert,replay_unlimited());bool partial_claims=false;std::set<ReplayPhase> phases;while(!r.progress().complete){const auto a=r.advance({1,{}});require(a.stopped_for==StopReason::quantum_work||a.stopped_for==StopReason::complete,"replay transition");auto report=capture(r);if(phases.insert(r.progress().phase).second)emit(report,"replay-phase");if(r.progress().checked_claims>0&&!r.progress().valid){partial_claims=true;require(!report.checked_certificate()&&!report.certificate(),"partial claims minted checked root");no_tree(report);}}require(partial_claims,"partial checked-claim state not observed");auto checked=*r.checked();auto moved=std::move(checked);rejects([&]{static_cast<void>(Report::from(checked));});require(Report::from(moved).optimum().has_value(),"moved checked authority");}
 {auto r=CertificateReplay::create(f.catalog,f.query,cert,replay_unlimited());const auto a=r.advance({UINT64_MAX,std::chrono::nanoseconds{1}});require(a.stopped_for==StopReason::quantum_time,"positive replay quantum time");emit(capture(r),"quantum-time-replay");}
 for(int corrupt=0;corrupt<4;++corrupt){auto bad=cert;if(corrupt==0)bad.algorithm="unrecognized";if(corrupt==1)bad.minimum_height=999;if(corrupt==2)bad.tree->root=NodeId{999};if(corrupt==3){require(!bad.lower_bounds.empty(),"corruption needs claims");bad.lower_bounds.front().bound=999;}
  auto r=CertificateReplay::create(f.catalog,f.query,bad,replay_unlimited());while(!r.progress().complete&&r.progress().phase!=ReplayPhase::failed){const auto a=r.advance({17,{}});require(a.stopped_for==StopReason::quantum_work||a.stopped_for==StopReason::invalid_certificate||a.stopped_for==StopReason::complete,"bad replay unexpected stop");}auto invalid=capture(r);require(!invalid.checked_certificate()&&!invalid.optimum()&&!invalid.infeasibility(),"invalid replay minted authority");no_tree(invalid);emit(invalid,"invalid-replay");}
 // Keep copied proof/binding after all producer owners have been destroyed.
 auto retained=[&]{auto s=ExactSearch::create(f.catalog,f.query,options());complete(s);return capture(s);}();require(retained.optimum().has_value()&&retained.binding().query().atoms.size()==2,"drop lifetime");emit(retained,"owner-dropped");
}
void metadata(){
 Catalog c;c.version=19;Table parent;parent.name="parent";parent.source_schema_version=7;parent.columns={{"id",ScalarType::int64}};parent.constraints.push_back(UniqueConstraint{"pk",{ColumnId{0}},ConstraintStatus::enforced});c.tables.push_back(parent);
 Table t;t.name=std::string("child\0\"\\\n",9);t.source_schema_version=23;t.columns={{"id",ScalarType::int64},{"s",ScalarType::string},{"b",ScalarType::boolean},{"d",ScalarType::date},{"money",ScalarType::decimal,false,Collation::binary,DecimalSpec{38,6}},{"ignored",ScalarType::int64},{"minimum",ScalarType::int64}};
 t.constraints.push_back(ForeignKeyConstraint{"fk",{ColumnId{0}},TableId{0},{ColumnId{0}},ConstraintStatus::enforced});t.constraints.push_back(UniqueConstraint{"untrusted",{ColumnId{1}},ConstraintStatus::untrusted});t.statistics.row_count=std::numeric_limits<std::uint64_t>::max();t.statistics.distinct_counts.push_back({{ColumnId{1},ColumnId{0}},123456});t.key_hints.push_back({{ColumnId{1}},std::string("hint\0reason",11)});c.tables.push_back(t);
 Query q;q.variables={{std::string("v\0name",6),ScalarType::int64}};q.atoms={{std::string("a\0\"\\\n",6),TableId{1},{VariableId{0},Value{std::string("str\0\"\\\n",7)},Value{true},Value{Date::parse("0001-01-01")},Value{Decimal::parse("-123456789012345678901234567890.123456")},IgnoredColumn{},Value{std::numeric_limits<std::int64_t>::min()}}}};q.head={{VariableId{0},"duplicate"},{VariableId{0},"duplicate"}};
 auto s=ExactSearch::create(c,q,options());auto before=capture(s);complete(s);auto r=capture(s);const auto& b=r.binding();const auto& bt=b.catalog().tables[1];require(b.catalog().version==19&&bt.name==t.name&&bt.source_schema_version==23,"catalog/name/version binding");require(bt.columns[4].decimal==t.columns[4].decimal&&!bt.columns[4].nullable&&bt.columns[4].collation==Collation::binary,"column metadata");const auto& fk=std::get<ForeignKeyConstraint>(bt.constraints[0]);require(fk.status==ConstraintStatus::enforced&&fk.referenced_table==TableId{0}&&fk.columns==std::vector<ColumnId>{ColumnId{0}}&&fk.referenced_columns==fk.columns,"foreign-key binding");require(std::get<UniqueConstraint>(bt.constraints[1]).status==ConstraintStatus::untrusted,"constraint trust");require(bt.statistics.row_count==t.statistics.row_count&&bt.statistics.distinct_counts[0].columns==t.statistics.distinct_counts[0].columns&&bt.statistics.distinct_counts[0].estimate==123456&&bt.key_hints[0].reason==t.key_hints[0].reason,"statistics/hints binding");require(b.query().head.size()==2&&b.query().head[0].alias==b.query().head[1].alias&&b.query().variables[0].name==q.variables[0].name,"aliases/variables binding");for(std::size_t i=1;i<5;++i)require(std::get<Value>(b.query().atoms[0].terms[i])==std::get<Value>(q.atoms[0].terms[i]),"exact scalar binding");require(std::holds_alternative<IgnoredColumn>(b.query().atoms[0].terms[5]),"ignored term");emit(before,"metadata-admitted");emit(r,"metadata-terminal");boundary(r,io::write_query_explain_json);boundary(r,io::write_query_explain_text);boundary(r,io::write_query_explain_tree_json);boundary(r,io::write_query_explain_dot);
 // Raw invalid-byte values and identifiers remain legal native bindings. Each malformed UTF-8 class is rejected only by text transport.
 for(const auto& raw:std::vector<std::string>{std::string(1,static_cast<char>(0xff)),"\xc0\x80","\xed\xa0\x80","\xf4\x90\x80\x80","\xe2\x82","\x80"}){
  auto bytes=fx::anchors().back();std::get<Value>(bytes.query.atoms[0].terms[0])=raw;auto owner=ExactSearch::create(bytes.catalog,bytes.query,options());auto report=capture(owner);require(std::get<std::string>(std::get<Value>(report.binding().query().atoms[0].terms[0]))==raw,"raw bytes changed at capture");const auto frozen=owner.progress();rejects([&]{static_cast<void>(io::write_query_explain_json(report));},"text_encoding");rejects([&]{static_cast<void>(io::write_query_explain_text(report));},"text_encoding");complete(owner);auto checked=capture(owner);rejects([&]{static_cast<void>(io::write_query_explain_tree_json(checked));},"text_encoding");static_cast<void>(io::write_query_explain_dot(checked));require(same(*report.search_progress(),frozen),"failed export changed old report");
  bytes.catalog.tables[0].name=raw;bytes.query.atoms[0].occurrence=raw;auto identifier=ExactSearch::create(bytes.catalog,bytes.query,options());auto ir=capture(identifier);require(ir.binding().catalog().tables[0].name==raw&&ir.binding().query().atoms[0].occurrence==raw,"raw identifier admission");rejects([&]{static_cast<void>(io::write_query_explain_json(ir));},"text_encoding");
 }
}
template<class F> void sweep(F&& operation){
 std::size_t failures=0;
 for(std::size_t point=0;;++point){bool failed=false;fault::remaining=point;fault::unexpected=false;fault::armed=true;try{operation();}catch(const std::bad_alloc&){failed=true;}catch(...){fault::armed=false;throw;}fault::armed=false;if(!failed){require(failures>0,"fault sweep never failed");break;}++failures;operation();require(point!=std::numeric_limits<std::size_t>::max(),"fault position overflow");}
}
void faults(){
 auto f=fx::hypergraph({3,6},7,"fault");auto owner=ExactSearch::create(f.catalog,f.query,options(SearchPolicy::best_found));complete(owner);const auto frozen=owner.progress();auto report=capture(owner);const auto baseline=io::write_query_explain_json(report);
 // Every failure stays armed during unwinding and destruction of intermediates. Publication is an optional set only after full success.
 sweep([&]{std::optional<Report> result;result.emplace(Report::capture(owner));});require(same(frozen,owner.progress()),"capture failure mutated owner");
 for(const Export fn:{io::write_query_explain_json,io::write_query_explain_text,io::write_query_explain_tree_json,io::write_query_explain_dot}){sweep([&]{auto output=fn(report,{});static_cast<void>(output);});require(io::write_query_explain_json(report)==baseline&&same(frozen,owner.progress()),"export failure changed report/owner");}
 sweep([&]{rejects([&]{static_cast<void>(Report::capture(owner,{0,0}));},"resource_limit");});
 auto replay=CertificateReplay::create(f.catalog,f.query,*report.certificate(),replay_unlimited());complete(replay);const auto rp=replay.progress();sweep([&]{auto r=Report::capture(replay);static_cast<void>(r);});require(same(rp,replay.progress()),"replay capture failure mutation");sweep([&]{auto r=Report::from(*replay.checked());static_cast<void>(r);});
 // A real continuation allocation stop and same-owner recovery, then a non-bad_alloc unexpected exception -> genuine terminal failed state.
 for(bool unexpected:{false,true}){auto s=ExactSearch::create(f.catalog,f.query,options(SearchPolicy::best_found));fault::remaining=0;fault::unexpected=unexpected;fault::armed=true;const auto a=s.advance({100000,{}});fault::armed=false;fault::unexpected=false;require(a.stopped_for==(unexpected?StopReason::internal_failure:StopReason::allocation_failure),"injected owner failure not observed");auto r=capture(s);emit(r,unexpected?"internal-failed-search":"allocation-search");if(unexpected){require(s.progress().phase==SearchPhase::failed&&!r.optimum()&&!r.infeasibility(),"internal failure minted proof");}else{require(s.progress().producer.allocation_failures>0,"allocation counter absent");complete(s);require(s.optimum().has_value(),"allocation same-owner recovery");}}
 for(bool unexpected:{false,true}){auto r=CertificateReplay::create(f.catalog,f.query,*report.certificate(),replay_unlimited());fault::remaining=0;fault::unexpected=unexpected;fault::armed=true;const auto a=r.advance({100000,{}});fault::armed=false;fault::unexpected=false;require(a.stopped_for==(unexpected?StopReason::internal_failure:StopReason::allocation_failure),"injected replay failure not observed");emit(capture(r),unexpected?"internal-failed-replay":"allocation-replay");if(!unexpected)complete(r);else require(r.progress().phase==ReplayPhase::failed&&!r.checked(),"failed replay authority");}
 // Raw-domain capture itself is also swept: no hidden JSON UTF-8 validation/admission or allocating JSON destructor.
 auto raw=fx::anchors().back();auto raw_owner=ExactSearch::create(raw.catalog,raw.query,options());sweep([&]{auto r=Report::capture(raw_owner);require(std::get<std::string>(std::get<Value>(r.binding().query().atoms[0].terms[0])).size()==1,"raw capture");});auto raw_report=capture(raw_owner);sweep([&]{rejects([&]{static_cast<void>(io::write_query_explain_json(raw_report));},"text_encoding");});
}
} // namespace
int main(int argc,char** argv){try{require(argc>=2,"usage: test OUTPUT_DIR [states|metadata|faults|family|all]");destination=argv[1];std::filesystem::create_directories(destination);const std::string group=argc>2?argv[2]:"all";if(group=="all"||group=="states")states();if(group=="all"||group=="metadata")metadata();if(group=="all"||group=="faults")faults();if(group=="all"||group=="family")family();require(group=="all"||group=="states"||group=="metadata"||group=="faults"||group=="family","unknown group");std::cout<<"PASS "<<group<<" reports="<<serial<<'\n';return 0;}catch(const std::exception& e){fault::armed=false;std::cerr<<"FAIL: "<<e.what()<<'\n';return 1;}catch(...){fault::armed=false;std::cerr<<"FAIL: unexpected exception\n";return 2;}}
