#include "crown/api/error.hpp"
#include "crown/io/oracle.hpp"
#include "planner_probe.hpp"
#include <iostream>
#include <stdexcept>

namespace {
using namespace crown;
void check(bool yes,const char* message) { if (!yes) throw std::runtime_error(message); }
template<class F> void rejects(F action,std::string_view code) {
  try { action(); }
  catch (const Error& error) { check(error.code()==code,"unexpected certificate codec error"); return; }
  throw std::runtime_error("malformed certificate was accepted");
}
void run() {
  Catalog c{1,{{"R",{{"x",ScalarType::int64},{"y",ScalarType::int64}}},
               {"S",{{"y",ScalarType::int64}}}}};
  Query q{{{"x",ScalarType::int64},{"y",ScalarType::int64}},
          {{"r",TableId{0},{VariableId{0},VariableId{1}}},{"s",TableId{1},{VariableId{1}}}},
          {{VariableId{0},"x"}},false};
  const auto optimized=planner::minimum_tree(c,q);
  const auto baseline=planner::testing::minimum_tree_baseline(c,q);
  check(optimized.certificate_verified && baseline.certificate_verified &&
        optimized.minimum_height==2 && baseline.minimum_height==2,"codec fixture has no independently checked optimum");
  for (const auto* result : {&baseline,&optimized}) {
    const auto encoded=io::write_oracle(*result,c,q);
    const auto& proof=encoded.at("certificate");
    const auto version=result==&baseline?1:2;
    check(proof.at("schema_version")==version,"wrong version emitted for proof semantics");
    check(encoded.at("schema_version")==1,"oracle result envelope changed unexpectedly");
    const auto read=io::read_height_certificate(proof.dump(),c,q);
    check(planner::verify_height_certificate(c,q,read).valid,"versioned proof did not independently replay");
  }
  const auto good=io::write_oracle(optimized,c,q).at("certificate");
  auto bad=good; bad["schema_version"]=1;
  rejects([&]{static_cast<void>(io::read_height_certificate(bad.dump(),c,q));},"unsupported_version");
  bad=good; bad["algorithm"]="crown_partition_exact_v1";
  rejects([&]{static_cast<void>(io::read_height_certificate(bad.dump(),c,q));},"unsupported_version");
  bad=good; bad["schema_version"]=3;
  rejects([&]{static_cast<void>(io::read_height_certificate(bad.dump(),c,q));},"unsupported_version");
  bad=good; bad["schema_version"]=2.0;
  rejects([&]{static_cast<void>(io::read_height_certificate(bad.dump(),c,q));},"invalid_document");
  bad=good; bad["schema_version"]=true;
  rejects([&]{static_cast<void>(io::read_height_certificate(bad.dump(),c,q));},"invalid_document");
  bad=good; bad["trusted_symmetry"]=true;
  rejects([&]{static_cast<void>(io::read_height_certificate(bad.dump(),c,q));},"invalid_document");
  bad=good; bad["lower_bounds"][0]["connex_reachable"]=1;
  rejects([&]{static_cast<void>(io::read_height_certificate(bad.dump(),c,q));},"invalid_document");
  bad=good; bad["lower_bounds"][0]["occurrences"][0]=0.0;
  rejects([&]{static_cast<void>(io::read_height_certificate(bad.dump(),c,q));},"invalid_document");
  bad=io::write_oracle(baseline,c,q).at("certificate"); bad["algorithm"]="unknown";
  const auto unknown=io::read_height_certificate(bad.dump(),c,q);
  check(!planner::verify_height_certificate(c,q,unknown).valid,"unknown legacy algorithm acquired proof authority");
  auto fake=optimized; fake.algorithm="unknown";
  rejects([&]{static_cast<void>(io::write_oracle(fake,c,q));},"invalid_search_certificate");
  auto limits=planner::SearchLimits{}; limits.work_limit=0;
  const auto stopped=io::write_oracle(planner::minimum_tree(c,q,limits),c,q);
  check(stopped.at("certificate").is_null() && stopped.at("tree").is_null() &&
        stopped.at("height_status")=="resource_limit","resource stop emitted a partial proof");
}
}
int main() {
  try { run(); std::cout<<"height certificate v1/v2 codec and strict version checks passed\n"; }
  catch(const std::exception& error) { std::cerr<<error.what()<<'\n'; return 1; }
}
