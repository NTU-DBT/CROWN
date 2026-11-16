#include "selection_fixture.hpp"
#include "indexed_runtime_fixture.hpp"
#include "index_allocation.hpp"
#include "crown/io/candidates.hpp"
#include "crown/io/compiler_plan_artifact.hpp"
#include "crown/io/tree.hpp"
#include "crown/observability/explain.hpp"
#include "crown/observability/query_explain.hpp"
#include <iostream>

namespace {
using namespace crown;
using c02_test::check;
namespace pr=planner::ranking;
namespace ps=planner::selection;
namespace rr=runtime::ranking;
namespace rs=runtime::selection;
constexpr std::uint64_t allowance=64*1024*1024;

// Structural height belongs to the retained body, independently of the empty
// executable operator. SQL cases come from real bind/normalize factories.
struct Input {
  c02_test::Fixture core;
  std::optional<frontend::NormalizedSql> sql;
  std::size_t height;
  std::size_t candidates;
  PhysicalPlan canonical(bool indexed) const {
    auto options=indexed?s04_runtime::options():PhysicalOptions{};
    return sql?planner::lower_normalized(*sql,{},options):
        planner::lower_tree(core.catalog,core.query,{},options);
  }
};
Input unary() {
  c02_test::Fixture f;
  f.catalog.tables={{"R",{{"x",ScalarType::int64}}},{"U",{{"unused",ScalarType::int64}}}};
  f.query.variables={{"x",ScalarType::int64}};
  f.query.atoms={{"r",TableId{0},{VariableId{0}}}};
  f.query.head={{VariableId{0},"x"}};f.query.contradiction=true;
  return {std::move(f),{},1,1};
}
Input multiple() {
  auto f=c02_test::fixture();f.query.contradiction=true;
  f.catalog.tables.push_back({"U",{{"unused",ScalarType::int64}}});
  return {std::move(f),{},2,3};
}
Input normalized(bool exists) {
  auto f=unary().core;
  const auto text=exists?R"SQL(SELECT EXISTS (SELECT 1 FROM "R" r WHERE 1=0))SQL":
      R"SQL(SELECT DISTINCT r.x AS a,r.x AS b,'tag' AS marker FROM "R" r WHERE 1=0)SQL";
  auto bound=frontend::bind_sql(text,f.catalog);
  check(std::holds_alternative<frontend::BoundSql>(bound),"constant SQL did not bind");
  auto result=frontend::normalize_sql(std::get<frontend::BoundSql>(bound));
  check(std::holds_alternative<frontend::NormalizedSql>(result),"constant SQL did not normalize");
  auto sql=std::get<frontend::NormalizedSql>(std::move(result));
  f.catalog=sql.core_catalog;f.query=sql.core;
  check(f.query.contradiction && !f.query.atoms.empty(),"SQL fixture lost its contradictory body");
  return {std::move(f),std::move(sql),1,1};
}
template<class F> void rejects(F action,std::string_view code) {
  try{action();}catch(const Error& error){check(error.code()==code,"wrong constant-route rejection");return;}
  throw std::runtime_error("constant-route boundary accepted invalid input");
}
void controller_only(const resource::MemoryAccount& account) {
  account.check_invariants();const auto now=account.statistics().current;
  check(now.allocations==1 && now.requested_bytes==resource::MemoryAccount::control_bytes(),
        "constant route retained receiving-account payload after release");
}
void empty_operator(const CompiledProgram& plan) {
  check(plan.route()==PhysicalRoute::constant_false && !plan.tree().root && plan.tree().nodes.empty(),
        "constant route retained original structural geometry");
  const auto& report=plan.validation();
  check(report.valid && report.native_height==0 && report.edge_depth==0 && report.maximal_connex.empty() &&
        report.separators.empty() && report.violations.empty(),"constant operator report is not canonical");
  check(plan.nodes().empty() && plan.inputs().empty() && plan.relations().empty() && plan.indexes().empty() &&
        plan.edges().empty() && plan.enumeration().steps.empty(),"constant operator built executable tree state");
}

// The unchanged public lowerer and full artifact reader are independent
// oracles for native lowering, including work, source, backend and layouts.
void native_matrix(const Input& input,bool indexed) {
  check(input.core.query.contradiction && !input.core.query.atoms.empty() && input.height>0,
        "regression accidentally uses only an empty-body control");
  const auto family=c02_test::candidates(input.core,input.height,input.candidates);
  const auto original=io::write_candidate_snapshot(family);
  const auto expected=input.canonical(indexed);const auto image=io::write_physical(expected);
  const auto basis=CompiledProgram::standalone(expected);
  for(std::size_t i=0;i<family.candidate_count();++i) {
    const auto candidate=*family.candidate(i);const auto held=io::write_minimum_height_candidate(candidate);
    rejects([&]{static_cast<void>(planner::lower_tree(input.core.catalog,input.core.query,candidate.tree()));},"invalid_plan");
    const auto old_source_requests=basis.account().statistics().successful_allocations;
    const auto receiving=resource::MemoryAccount::create(allowance);
    {
      std::size_t calls=0;CompiledProgram plan;
      {s04_alloc::Scope count;plan=CompiledProgram::replan_into(receiving,basis,candidate);calls=s04_alloc::calls;}
      empty_operator(plan);
      check(calls>0 && calls==receiving.statistics().successful_allocations-1,
            "new constant metadata allocated outside receiving account");
      check(basis.account().statistics().successful_allocations==old_source_requests,
            "constant replan allocated in its immutable source account");
      check(io::write_physical(plan)==image,"native constant operator differs from independent public lowering");
      const auto decoded=io::read_physical(io::write_physical(plan).dump());
      check(io::write_physical(decoded)==image,"canonical constant artifact did not roundtrip");
      const auto compiler=resource::MemoryAccount::create(allowance);
      const auto artifact=io::CompilerPlanArtifact::prepare(compiler,plan);
      check(io::write_physical(artifact.program())==image,"compiler reconstruction changed constant operator");
      const auto copy_account=resource::MemoryAccount::create(allowance);
      const auto replay=io::CompilerPlanArtifact::replay(copy_account,artifact.bytes());
      check(io::write_physical(replay.program())==image,"compiler artifact replay changed source/options");
      check(plan.physical_source_sha256()==basis.physical_source_sha256(),"constant replan changed source digest");
      const auto explain=observability::PlanExplanation::create(plan);
      check(explain.height_status()==observability::HeightStatus::checked_constant_operator && explain.selected_height()==0,
            "operator report claimed original body minimum");
      rejects([&]{static_cast<void>(observability::PlanExplanation::create(plan,candidate));},"explain_candidate");
      rejects([&]{static_cast<void>(observability::PlanExplanation::create(plan,family.original_proof()));},"explain_height");
      rejects([&]{static_cast<void>(observability::PlanExplanation::create(plan,{},family));},"explain_family");
      const auto query=observability::QueryExplanation::from(family.original_proof());
      check(query.lower()==input.height && query.upper()==input.height,"original query explanation acquired operator height");
      auto corrupt=image;corrupt["tree"]=io::write_tree(candidate.tree(),input.core.catalog,input.core.query);
      rejects([&]{static_cast<void>(io::read_physical(corrupt.dump()));},"invalid_plan");
      corrupt=image;corrupt["binding"]["physical_sha256"]="tampered";
      bool rejected=false;try{static_cast<void>(io::read_physical(corrupt.dump()));}catch(const Error&){rejected=true;}
      check(rejected,"constant artifact reader ignored a changed complete artifact");
    }
    controller_only(receiving);
    check(io::write_minimum_height_candidate(candidate)==held && io::write_candidate_snapshot(family)==original,
          "native replan changed original tree/proof/key/provenance");
  }
}

void heat(runtime::PhysicalRuntime& owner) {
  owner.configure_workload_statistics(c05_test::counters());
  const auto last=owner.plan().source_catalog().tables.size()-1;
  for(const auto& event:std::array<PhysicalSetUpdate,4>{
      PhysicalSetUpdate{1,TableId{0},SetOperation::insert,Row{std::int64_t{1}}},
      PhysicalSetUpdate{2,TableId{0},SetOperation::insert,Row{std::int64_t{1}}},
      PhysicalSetUpdate{3,TableId{0},SetOperation::erase,Row{std::int64_t{99}}},
      PhysicalSetUpdate{4,TableId{last},SetOperation::insert,Row{std::int64_t{7}}}})
    static_cast<void>(owner.apply(event));
  check(!owner.has_answer() && owner.sequence()==4,"constant source updates changed empty answer/epoch");
}
void zero_scores(const pr::Result& result,std::size_t height,std::size_t count,std::size_t tables) {
  check(result.scores().size()==count && result.selected().height()==height &&
        result.snapshot().original_proof().height()==height,"ranking replaced original certified family");
  std::string best;
  for(const auto& score:result.scores()) {
    check(score.height==height && score.candidate.height()==height,"score uses operator height as original height");
    const std::string key(score.structural_key.data(),score.structural_key.size());
    if(best.empty() || key<best)best=key;
    if(result.effective_policy()==pr::Policy::committed_input_native_depth) {
      check(score.numerator=="0" && score.denominator=="4" && score.depths.empty() && score.table_depths.size()==tables,
            "constant depth did not reproduce literal0/4 with no routed occurrences");
      for(std::size_t i=0;i<tables;++i) {
        const auto& term=score.table_depths[i];
        const auto inserts=i==0?2U:i+1==tables?1U:0U;
        check(term.table==TableId{i} && term.inserts==inserts && term.erases==(i==0?1U:0U) &&
              term.depth_sum=="0" && term.contribution=="0","constant table weights/zero contributions changed");
      }
    }else if(result.effective_policy()==pr::Policy::tuple_index_slots) {
      check(score.slots=="0" && score.populations.empty() && score.slot_terms.empty() && score.modeled_plan.has_value(),
            "zero slot score skipped modeled-plan admission or invented populations");
      empty_operator(*score.modeled_plan);
    }
  }
  check(result.selected().structural_key()==best,"constant family did not use full-key deterministic tie order");
}

// Real input/no-op/unused-table traffic fixes W=4 independently of the model.
// Each source/policy/cache path must keep the original positive-height family.
void models_and_selection(const Input& input,bool indexed) {
  const auto family=c02_test::candidates(input.core,input.height,input.candidates);
  const auto original=io::write_candidate_snapshot(family);const auto compiler=input.canonical(indexed);
  Database database;database.tables.resize(compiler.source_catalog().tables.size());
  auto owner=runtime::PhysicalRuntime::initialize(compiler,database);
  pr::Request strict;strict.policy=pr::Policy::committed_input_native_depth;
  check(!rr::rank_current(family,owner,strict).result,"disabled census manufactured an exact constant depth score");
  owner.configure_workload_statistics(c05_test::counters());
  const auto zero=rr::rank_current(family,owner,strict);
  check(zero.stop==pr::Stop::evidence_unavailable && !zero.result,"empty census manufactured an exact zero/W");
  strict.fallback=pr::Fallback::height_only;
  const auto fallback=rr::rank_current(family,owner,strict);
  check(fallback.result && fallback.result->effective_policy()==pr::Policy::height_only &&
        fallback.result->fallback_reasons()!=0,"constant route bypassed configured evidence fallback");
  heat(owner);
  if(input.sql) {
    const auto rows=c05_test::answers(owner);
    const auto expected=input.sql->binding.wrapper==frontend::SqlWrapper::exists?Relation{Row{Value{false}}}:Relation{};
    check(rows==expected,"constant SQL rows/EXISTS output contract changed");
  }
  const auto facts=c05_test::capture(family,owner);
  check(facts.inputs().denominator()==4 && facts.inputs().depth_reasons()==0 && facts.inputs().memory_reasons()==0,
        "constant fixture did not capture healthy literal census");
  for(const auto policy:{pr::Policy::height_only,pr::Policy::committed_input_native_depth,pr::Policy::tuple_index_slots}) {
    pr::Request request;request.policy=policy;
    const auto ranked=pr::rank(family,request,facts.inputs());
    check(ranked.stop==pr::Stop::complete && ranked.result.has_value() && ranked.evaluated==family.candidate_count(),
          "constant ranking stopped before complete retained family");
    zero_scores(*ranked.result,input.height,input.candidates,compiler.source_catalog().tables.size());
    const auto current=rr::rank_current(family,owner,request);
    check(current.result.has_value(),"current constant ranking failed");
    zero_scores(*current.result,input.height,input.candidates,compiler.source_catalog().tables.size());
    const auto selected_policy=policy==pr::Policy::height_only?ps::Policy::height_only:
        policy==pr::Policy::committed_input_native_depth?ps::Policy::committed_input_native_depth:ps::Policy::tuple_index_slots;
    ps::Request wanted;wanted.policy=selected_policy;wanted.fallback=pr::Fallback::require_evidence;
    if(policy!=pr::Policy::height_only)wanted.constraint=ps::TupleIndexSlotLimit{"0"};
    std::vector<ps::Source> sources{ps::PhysicalBasis{compiler},ps::PhysicalBasis{owner.plan()}};
    if(!input.sql)sources.emplace_back(ps::DirectCQ{compiler.options()});
    for(const auto& source:sources) {
      auto cache=ps::PlanCache::create({2,8*1024*1024,32*1024*1024});
      const auto first=c05_test::complete(ps::select(family,source,wanted,facts.inputs(),&cache,ps::CacheUse::read_write));
      const auto cached=c05_test::complete(ps::select(family,source,wanted,facts.inputs(),&cache,ps::CacheUse::read_only));
      check(cache.statistics().hits==1 && cached.cache_observation().disposition==ps::CacheDisposition::hit,
            "constant artifact cache failed exact reuse");
      check(first.selected().height()==input.height && cached.snapshot().original_proof().height()==input.height &&
            first.selected().structural_key()==ranked.result->selected().structural_key(),"selection changed original proof/tie");
      empty_operator(first.plan());empty_operator(cached.plan());
      check(io::write_physical(first.plan())==io::write_physical(compiler) &&
            io::write_physical(io::read_physical(io::write_physical(cached.plan()).dump()))==io::write_physical(compiler),
            "selected/cached constant source/options/artifact changed");
      for(const auto& assessment:first.assessments())
        zero_scores(assessment.result,input.height,input.candidates,compiler.source_catalog().tables.size());
    }
  }
  if(input.sql) {
    ps::Request wanted;wanted.policy=ps::Policy::height_only;
    const auto incompatible=ps::select(family,ps::DirectCQ{compiler.options()},wanted,facts.inputs());
    check(!incompatible.selection && incompatible.stop==ps::Stop::binding_mismatch,
          "constant shortcut bypassed normalized source identity");
  }else {
    ps::Request wanted;wanted.policy=ps::Policy::height_only;
    const auto initial=c05_test::complete(ps::select(family,ps::DirectCQ{compiler.options()},wanted));
    empty_operator(initial.plan());check(io::write_physical(initial.plan())==io::write_physical(compiler),
                                       "DirectCQ initial compiler did not choose explicit empty operator input");
  }
  check(io::write_candidate_snapshot(family)==original,"rank/select/cache altered original family");
  static_cast<void>(owner.apply({5,TableId{compiler.source_catalog().tables.size()-1},SetOperation::insert,Row{std::int64_t{7}}}));
  check(rr::revalidate(facts,owner).boundary!=0,"constant no-op input left old actual-owner evidence current");
}

// All observed allocation positions are faulted, then retried on the same
// source/receiver. A distinct account makes accidental source-account funding visible.
void native_faults_and_limits(const Input& input,bool indexed) {
  const auto family=c02_test::candidates(input.core,input.height,input.candidates);
  const auto candidate=*family.candidate(0);const auto original=io::write_candidate_snapshot(family);
  const auto basis=CompiledProgram::standalone(input.canonical(indexed));
  const auto image=io::write_physical(input.canonical(indexed));
  const auto receiving=resource::MemoryAccount::create(allowance);
  const auto held=CompiledProgram::replan_into(receiving,basis,candidate);
  std::size_t expected=0;
  {s04_alloc::Scope count;const auto value=CompiledProgram::replan_into(receiving,basis,candidate);expected=s04_alloc::calls;}
  check(expected>0 && expected<4096,"constant native fault calibration exceeded bound");
  for(std::size_t point=0;point<=expected;++point) {
    const auto before=receiving.statistics().current;CompiledProgram value;bool failed=false;std::size_t calls=0;
    {s04_alloc::Scope fault(static_cast<std::ptrdiff_t>(point));
      try{value=CompiledProgram::replan_into(receiving,basis,candidate);}catch(const std::bad_alloc&){failed=true;}
      calls=s04_alloc::calls;
    }
    if(point<expected) {
      check(failed && calls==point+1 && !value && receiving.statistics().current==before,
            "constant native fault leaked/published a partial operator or missed its position");
      value=CompiledProgram::replan_into(receiving,basis,candidate);
    }else check(!failed && calls==expected,"constant native success sentinel did not reach every allocation");
    check(io::write_physical(value)==image && io::write_physical(held)==image &&
          io::write_candidate_snapshot(family)==original,"constant native retry changed prior result or proof");
    {s04_alloc::Scope none(0);value={};}
    check(receiving.statistics().current==before,"constant operator teardown retained new receiver payload");
  }
  const auto calibration=resource::MemoryAccount::create(allowance);
  {const auto value=CompiledProgram::replan_into(calibration,basis,candidate);empty_operator(value);}
  const auto peak=calibration.statistics().peak_requested_bytes;controller_only(calibration);
  for(const bool exact:{false,true}) {
    const auto bounded=resource::MemoryAccount::create(exact?peak:peak-1);bool denied=false;
    try{const auto value=CompiledProgram::replan_into(bounded,basis,candidate);empty_operator(value);}
    catch(const resource::MemoryFailure& error){check(error.fault()==resource::MemoryFault::limit,"wrong constant receiver cap failure");denied=true;}
    check(denied!=exact,"constant receiver exact/one-under boundary changed");controller_only(bounded);
  }
  const auto work=held.work();check(work>0,"constant lower work is not recorded");
  for(const bool exact:{false,true}) {
    program::ReplanLimits limits;limits.physical.work_limit=exact?work:work-1;bool denied=false;
    try{const auto value=CompiledProgram::replan_into(receiving,basis,candidate,limits);empty_operator(value);}
    catch(const program::ReplanFailure& error){check(error.fault()==program::ReplanFault::lowering_work,"wrong constant work failure");denied=true;}
    check(denied!=exact,"constant native exact/one-under work boundary changed");
  }
  program::ReplanLimits limits;limits.physical.identity.work_limit=0;bool denied=false;
  try{static_cast<void>(CompiledProgram::replan_into(receiving,basis,candidate,limits));}
  catch(const program::ReplanFailure& error){denied=error.fault()==program::ReplanFault::identity_work;}
  check(denied,"constant route bypassed retained identity admission credits");
  if(input.sql)for(const bool binding:{false,true}) {
    program::ReplanLimits cap;
    if(binding)cap.binding_replay_work=0;else cap.normalization_work=0;
    bool stopped=false;
    try{static_cast<void>(CompiledProgram::replan_into(receiving,basis,candidate,cap));}
    catch(const program::ReplanFailure& error){stopped=error.fault()==(binding?program::ReplanFault::binding_replay_work:program::ReplanFault::normalization_work);}
    check(stopped,"constant SQL route bypassed source admission credits");
  }
  std::cout<<"constant native indexed="<<indexed<<" sql="<<bool(input.sql)<<" fault_positions="<<expected
           <<" receiver_peak="<<peak<<" work="<<work<<'\n';
}

// A failed replacement must leave the funded warm cache, its diagnostics and
// prior result whole. This covers a different-policy miss and the zero-slot assessment.
void selection_faults(bool indexed) {
  const auto input=unary();const auto family=c02_test::candidates(input.core,1,1);
  const auto compiler=input.canonical(indexed);Database db;db.tables.resize(2);
  auto owner=runtime::PhysicalRuntime::initialize(compiler,db);heat(owner);
  const auto facts=c05_test::capture(family,owner);const ps::Source source=ps::PhysicalBasis{owner.plan()};
  ps::Request height;height.policy=ps::Policy::height_only;
  for(const auto policy:{ps::Policy::committed_input_native_depth,ps::Policy::tuple_index_slots}) {
    ps::Request wanted;wanted.policy=policy;wanted.fallback=pr::Fallback::require_evidence;
    wanted.constraint=ps::TupleIndexSlotLimit{"0"};
    std::size_t expected=0;
    {
      auto cache=ps::PlanCache::create({1,8*1024*1024,32*1024*1024});
      const auto old=c05_test::complete(ps::select(family,source,height,facts.inputs(),&cache,ps::CacheUse::read_write));
      ps::Attempt result;
      {s04_alloc::Scope count;result=ps::select(family,source,wanted,facts.inputs(),&cache,ps::CacheUse::read_write);expected=s04_alloc::calls;}
      empty_operator(c05_test::complete(std::move(result)).plan());empty_operator(old.plan());
    }
    check(expected>0 && expected<4096,"constant selection fault calibration exceeded bound");
    for(std::size_t point=0;point<=expected;++point) {
      auto cache=ps::PlanCache::create({1,8*1024*1024,32*1024*1024});
      const auto old=c05_test::complete(ps::select(family,source,height,facts.inputs(),&cache,ps::CacheUse::read_write));
      const auto cached=cache.statistics();const auto before=owner.plan().account().statistics().current;
      ps::Attempt result;std::size_t calls=0;
      {s04_alloc::Scope fault(static_cast<std::ptrdiff_t>(point));result=ps::select(family,source,wanted,facts.inputs(),&cache,ps::CacheUse::read_write);calls=s04_alloc::calls;}
      if(point<expected) {
        check(!result.selection && result.stop==ps::Stop::allocation_failure && calls==point+1 &&
              cache.statistics()==cached && owner.plan().account().statistics().current==before,
              "constant selection fault changed cache/owner or published a partial result");
        result=ps::select(family,source,wanted,facts.inputs(),&cache,ps::CacheUse::read_write);
      }else check(calls==expected,"constant selection success sentinel missed observed allocation");
      const auto selected=c05_test::complete(std::move(result));
      empty_operator(selected.plan());empty_operator(old.plan());
      check(!owner.has_answer() && owner.sequence()==4 && cache.statistics().entries==1,
            "constant selection retry mutated runtime or failed whole cache publication");
    }
    for(const bool work:{false,true}) {
      auto request=wanted;if(work)request.limits.aggregate.lowering_work=0;else request.limits.aggregate.work=0;
      const auto stopped=ps::select(family,source,request,facts.inputs());
      check(!stopped.selection && stopped.stop==ps::Stop::resource_limit,"constant zero slot bypassed processing/lowering limit");
    }
    std::cout<<"constant selection indexed="<<indexed<<" policy="<<static_cast<unsigned>(policy)
             <<" fault_positions="<<expected<<'\n';
  }
}

void owner_boundaries() {
  const auto input=unary();const auto family=c02_test::candidates(input.core,1,1);
  const auto compiler=input.canonical(false);Database db;db.tables.resize(2);
  runtime::DeltaOptions delta_options;delta_options.mode=runtime::DeltaMode::maintenance;
  auto delta=runtime::DeltaRuntime::initialize(compiler,db,delta_options);
  delta.configure_workload_statistics(c05_test::counters());
  auto output=delta.apply({1,TableId{0},SetOperation::insert,Row{std::int64_t{1}}});output.discard();
  ps::Request wanted;wanted.policy=ps::Policy::tuple_index_slots;wanted.constraint=ps::TupleIndexSlotLimit{"0"};
  const ps::Source source=ps::PhysicalBasis{compiler};
  const auto chosen=c05_test::complete(rs::select_current(family,source,delta,wanted));
  empty_operator(chosen.selection().plan());
  auto pending=delta.begin({2,TableId{1},SetOperation::insert,Row{std::int64_t{7}}});
  const auto rejected=rs::select_current(family,source,delta,wanted);
  check(!rejected.selection && rejected.stop==ps::Stop::boundary_unavailable,"constant shortcut observed private Delta state");
  pending.rollback();
  auto session=runtime::QuerySession::create_typed(compiler,db);
  const auto live=c05_test::complete(rs::select_current(family,source,*session,wanted));
  empty_operator(live.selection().plan());session->drop();
  const auto released=rs::select_current(family,source,*session,wanted);
  check(!released.selection && released.stop==ps::Stop::boundary_unavailable,"constant shortcut admitted released session");
}

void compatibility() {
  for(const bool contradiction:{false,true}) {
    c02_test::Fixture f;f.query.contradiction=contradiction;
    const auto family=c02_test::candidates(f,0,1);const auto candidate=*family.candidate(0);
    for(const bool indexed:{false,true}) {
      const auto options=indexed?s04_runtime::options():PhysicalOptions{};
      const auto old=planner::lower_tree(f.catalog,f.query,candidate.tree(),options);
      const auto base=CompiledProgram::standalone(old);const auto actual=CompiledProgram::replan(base,candidate);
      check(io::write_physical(actual)==io::write_physical(old),"empty-body raw claims/hash/counters changed");
    }
  }
  const auto f=c02_test::fixture();const auto family=c02_test::candidates(f,2,3);
  for(std::size_t i=0;i<family.candidate_count();++i) {
    const auto basis=CompiledProgram::standalone(planner::lower_tree(f.catalog,f.query,family.candidate(0)->tree()));
    const auto actual=CompiledProgram::replan(basis,*family.candidate(i));
    check(io::write_physical(actual)==io::write_physical(planner::lower_tree(f.catalog,f.query,family.candidate(i)->tree())),
          "ordinary tree route changed");
  }
}

void run() {
  const std::array<Input,4> inputs{unary(),multiple(),normalized(false),normalized(true)};
  for(const auto& input:inputs)for(const bool indexed:{false,true}) {
    native_matrix(input,indexed);models_and_selection(input,indexed);
  }
  compatibility();
  for(const bool indexed:{false,true}) {
    native_faults_and_limits(inputs[0],indexed);native_faults_and_limits(inputs[2],indexed);
    selection_faults(indexed);
  }
  owner_boundaries();
  std::cout<<"constant routes:4 nonempty fixtures x2 backends, original h1/h2, full artifacts,0/4 depth,0 slots,cache/proof/report boundaries passed\n";
}
} // namespace
int main() {
  try{run();return 0;}catch(const std::exception& error){std::cerr<<error.what()<<'\n';return 1;}
}
