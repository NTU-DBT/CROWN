#include "crown/observability/query_explain.hpp"
#include "crown/api/error.hpp"
#include <utility>
namespace crown::observability {
using namespace planner;
// Shared typed evidence keeps its original scope; capture creates no new proof.
struct QueryExplanation::Data {
  SearchBinding binding;
  QueryExplainSource source;
  std::optional<SearchProgress> search;
  std::optional<ReplayProgress> replay;
  std::optional<SearchPolicy> policy;
  std::optional<ContinuationLimits> search_limits;
  std::optional<ReplayOptions> replay_limits;
  std::optional<ValidatedIncumbent> witness;
  std::optional<VerifiedOptimum> optimum;
  std::optional<VerifiedInfeasible> infeasible;
  std::optional<CheckedCertificate> checked;
  Data(SearchBinding b,QueryExplainSource s):binding(std::move(b)),source(s) {}
};
QueryExplanation::QueryExplanation(std::shared_ptr<const Data> value):data_(std::move(value)) {}
const QueryExplanation::Data& QueryExplanation::data() const {
  if(!data_)throw Error("invalid_query_explanation","moved-from query explanation");
  return *data_;
}
// Normalize existing handles; these count checks do not cap all retained bytes.
QueryExplanation QueryExplanation::finish(std::shared_ptr<Data> d,QueryExplainLimits limits) {
  if(!d->binding.valid())throw Error("invalid_query_explanation","moved-from original binding");
  if(d->checked){d->optimum=d->checked->optimum();d->infeasible=d->checked->infeasibility();}
  if(d->optimum)d->witness=d->optimum->upper();
  if(d->witness && d->witness->tree().nodes.size()>limits.witness_nodes)
    throw Error("resource_limit","query EXPLAIN witness-node limit exceeded");
  const HeightCertificate* proof=d->optimum?&d->optimum->certificate():d->infeasible?&d->infeasible->certificate():nullptr;
  if(proof && (proof->lower_bounds.size()>limits.certificate_entries ||
      (proof->tree && proof->tree->nodes.size()>limits.witness_nodes)))
    throw Error("resource_limit","query EXPLAIN certificate size limit exceeded");
  return QueryExplanation(std::move(d));
}
// Exclusive producer read: fixed metadata/handle copies, no search advancement.
QueryExplanation QueryExplanation::capture(const ExactSearch& owner,QueryExplainLimits limits) {
  auto d=std::make_shared<Data>(owner.binding(),QueryExplainSource::exact_search);
  d->search=owner.progress();d->policy=owner.policy();d->search_limits=owner.limits();
  d->witness=owner.incumbent();d->optimum=owner.optimum();d->infeasible=owner.infeasibility();
  return finish(std::move(d),limits);
}
QueryExplanation QueryExplanation::capture(const CertificateReplay& owner,QueryExplainLimits limits) {
  auto d=std::make_shared<Data>(owner.binding(),QueryExplainSource::certificate_replay);
  d->replay=owner.progress();d->replay_limits=owner.limits();d->checked=owner.checked();
  return finish(std::move(d),limits);
}
QueryExplanation QueryExplanation::from(ValidatedIncumbent value,QueryExplainLimits limits) {
  auto d=std::make_shared<Data>(value.binding(),QueryExplainSource::checked_upper);d->witness=std::move(value);return finish(std::move(d),limits);
}
QueryExplanation QueryExplanation::from(VerifiedOptimum value,QueryExplainLimits limits) {
  auto d=std::make_shared<Data>(value.binding(),QueryExplainSource::verified_optimum);d->optimum=std::move(value);return finish(std::move(d),limits);
}
QueryExplanation QueryExplanation::from(VerifiedInfeasible value,QueryExplainLimits limits) {
  auto d=std::make_shared<Data>(value.binding(),QueryExplainSource::verified_infeasible);d->infeasible=std::move(value);return finish(std::move(d),limits);
}
QueryExplanation QueryExplanation::from(CheckedCertificate value,QueryExplainLimits limits) {
  auto d=std::make_shared<Data>(value.binding(),QueryExplainSource::checked_certificate);d->checked=std::move(value);return finish(std::move(d),limits);
}
const SearchBinding& QueryExplanation::binding() const {return data().binding;}
QueryExplainSource QueryExplanation::source() const {return data().source;}
QueryHeightStatus QueryExplanation::height_status() const {
  const auto& d=data();
  if(d.optimum)return QueryHeightStatus::verified_optimum;
  if(d.infeasible)return QueryHeightStatus::verified_infeasible;
  if(d.witness)return QueryHeightStatus::checked_upper;
  if(d.search && d.search->heights.upper)return QueryHeightStatus::owner_checked_upper_unpublished;
  return QueryHeightStatus::unknown;
}
std::optional<std::size_t> QueryExplanation::lower() const {
  const auto& d=data();if(d.infeasible)return {};if(d.optimum)return d.optimum->height();
  // P06's universal bound, not structural recognition or producer advancement.
  return d.binding.query().atoms.empty()?0:1;
}
std::optional<std::size_t> QueryExplanation::upper() const {
  const auto& d=data();if(d.optimum)return d.optimum->height();if(d.witness)return d.witness->height();
  return d.search?d.search->heights.upper:std::nullopt;
}
const std::optional<SearchProgress>& QueryExplanation::search_progress() const {return data().search;}
const std::optional<ReplayProgress>& QueryExplanation::replay_progress() const {return data().replay;}
const std::optional<SearchPolicy>& QueryExplanation::policy() const {return data().policy;}
const std::optional<ContinuationLimits>& QueryExplanation::search_limits() const {return data().search_limits;}
const std::optional<ReplayOptions>& QueryExplanation::replay_limits() const {return data().replay_limits;}
const std::optional<ValidatedIncumbent>& QueryExplanation::witness() const {return data().witness;}
const std::optional<VerifiedOptimum>& QueryExplanation::optimum() const {return data().optimum;}
const std::optional<VerifiedInfeasible>& QueryExplanation::infeasibility() const {return data().infeasible;}
const std::optional<CheckedCertificate>& QueryExplanation::checked_certificate() const {return data().checked;}
const HeightCertificate* QueryExplanation::certificate() const {
  const auto& d=data();return d.optimum?&d.optimum->certificate():d.infeasible?&d.infeasible->certificate():nullptr;
}
} // namespace crown::observability
