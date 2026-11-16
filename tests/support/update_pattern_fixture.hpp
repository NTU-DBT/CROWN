#pragma once

#include "ranking_fixture.hpp"
#include <array>

namespace crown::pattern_test {
// Refactor 5.3's seven-atom obstruction, expressed as ordinary typed DTOs.
// Structural authority is supplied by the actual search/provider below.
inline c02_test::Fixture height_three_fixture() {
  c02_test::Fixture fixture;
  const std::array<std::vector<std::size_t>, 7> scopes{{
      {0,1,2,3}, {0,1,2,4}, {3}, {4}, {1,5}, {5}, {0,6}}};
  for(std::size_t v=0;v<7;++v)fixture.query.variables.push_back({"x"+std::to_string(v),ScalarType::int64});
  for(std::size_t t=0;t<scopes.size();++t) {
    Table table{"R"+std::to_string(t),{}};Atom atom{"r"+std::to_string(t),TableId{t},{}};
    for(const auto v:scopes[t]) {
      table.columns.push_back({"x"+std::to_string(v),ScalarType::int64});atom.terms.emplace_back(VariableId{v});
    }
    fixture.catalog.tables.push_back(std::move(table));fixture.query.atoms.push_back(std::move(atom));
  }
  for(const auto v:{0U,1U,6U})fixture.query.head.push_back({VariableId{v},"out"+std::to_string(v)});
  return fixture;
}
// Prove the original minimum, then retain one genuine candidate. The finite
// prefix is not claimed to exhaust all compatible shapes or minimize cost.
inline planner::CandidateSnapshot height_three_family(const c02_test::Fixture& fixture) {
  planner::SearchOptions options;options.limits.producer.work=50'000'000;options.limits.replay.work=50'000'000;
  auto exact=planner::ExactSearch::create(fixture.catalog,fixture.query,options);
  for(std::size_t step=0;step<100'000 && !exact.optimum();++step) {
    const auto next=exact.advance({1000,{}});
    c02_test::check(next.progress.result!=planner::ResultKind::failed,"height-three proof failed");
  }
  c02_test::check(exact.optimum().has_value() && exact.optimum()->height()==3,"height-three proof did not complete");
  auto provider=planner::CandidateProvider::create(*exact.optimum());
  for(std::size_t step=0;step<100'000 && !provider.candidate_count();++step)static_cast<void>(provider.advance({1000,{}}));
  c02_test::check(provider.candidate_count()==1,"height-three candidate missing");return provider.snapshot();
}
} // namespace crown::pattern_test
