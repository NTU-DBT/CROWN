#pragma once
#include "crown/planner/ranking.hpp"
#include "crown/planner/lower.hpp"
#include <stdexcept>
namespace c02_test {
using namespace crown;
inline void check(bool x,const char* s){if(!x){throw std::runtime_error(s);}}
// Ordinary owning source/data DTOs; proof, candidate and runtime admission run later.
struct Fixture {Catalog catalog;Query query;Database database;};
inline Fixture fixture(){
  Fixture f;f.catalog.tables={{"R",{{"x",ScalarType::int64}}},{"S",{{"x",ScalarType::int64},{"y",ScalarType::int64}}},{"T",{{"y",ScalarType::int64}}}};
  f.query.variables={{"x",ScalarType::int64},{"y",ScalarType::int64}};
  f.query.atoms={{"R",TableId{0},{VariableId{0}}},{"S",TableId{1},{VariableId{0},VariableId{1}}},{"T",TableId{2},{VariableId{1}}}};
  f.database.tables={Relation{Row{std::int64_t{1}}},Relation{Row{std::int64_t{1},std::int64_t{1}}},Relation{Row{std::int64_t{1}}}};return f;
}
// The actual checked optimum supplies authority; height/count are only assertions.
inline planner::CandidateSnapshot candidates(const Fixture& f,std::size_t height=2,std::size_t count=3){
  planner::SearchOptions options;options.limits.producer.work=50'000'000;options.limits.replay.work=50'000'000;
  auto exact=planner::ExactSearch::create(f.catalog,f.query,options);
  for(std::size_t step=0;step<100'000 && !exact.optimum();++step){const auto a=exact.advance({1000,{}});check(a.progress.result!=planner::ResultKind::failed,"finite proof failed");}
  check(exact.optimum().has_value(),"finite proof incomplete");check(exact.optimum()->height()==height,"fixture optimum mismatch");
  auto provider=planner::CandidateProvider::create(*exact.optimum());
  for(std::size_t step=0;step<100'000 && !provider.progress().family_exhausted;++step){const auto a=provider.advance({1000,{}});check(a.progress.phase!=planner::CandidatePhase::failed,"candidate provider failed");}
  check(provider.progress().family_exhausted,"finite candidate family incomplete");if(count){check(provider.candidate_count()==count,"unexpected candidate family");}return provider.snapshot();
}
inline int shape(const FreeConnexTree& t){const auto& root=t.nodes.at(t.root->value);if(root.kind==NodeKind::native){return 0;}check(root.scope.size()==1,"unexpected generalized root");return root.scope.contains(VariableId{0})?1:2;}
}
