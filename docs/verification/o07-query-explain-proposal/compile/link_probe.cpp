#include "crown/io/query_explain.hpp"
#include "../fixtures/query_families.hpp"
// Link-only consumer. No main-time query, search, replay or export execution.
void query_explain_link_probe(const crown::planner::ExactSearch& search,
    const crown::planner::CertificateReplay& replay,
    crown::planner::ValidatedIncumbent upper,crown::planner::VerifiedOptimum optimum,
    crown::planner::VerifiedInfeasible infeasible,crown::planner::CheckedCertificate checked) {
  using crown::observability::QueryExplanation;
  const auto a=QueryExplanation::capture(search);const auto b=QueryExplanation::capture(replay);
  const auto c=QueryExplanation::from(upper);const auto d=QueryExplanation::from(optimum);
  const auto e=QueryExplanation::from(infeasible);const auto f=QueryExplanation::from(checked);
  static_cast<void>(crown::io::write_query_explain_json(a));
  static_cast<void>(crown::io::write_query_explain_text(b));
  static_cast<void>(crown::io::write_query_explain_tree_json(c));
  static_cast<void>(crown::io::write_query_explain_dot(d));
  static_cast<void>(crown::io::write_query_explain_json(e));
  static_cast<void>(crown::io::write_query_explain_json(f));
}
int main(){return 0;}
