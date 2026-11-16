#include <crown/api/error.hpp>
#include <crown/io/candidates.hpp>
#include <crown/io/document.hpp>
#include <crown/io/residual.hpp>
#include <crown/io/search.hpp>
#include <crown/io/tree.hpp>
#include <crown/ir/digest.hpp>
#include <crown/planner/lower.hpp>
#include <crown/planner/meta_candidates.hpp>
#include <crown/planner/verify.hpp>
#include <crown/runtime/delta.hpp>
#include <crown/runtime/ranking_evidence.hpp>
#include <crown/runtime/update_view.hpp>
#include "candidate_set.hpp"
#include "tree_oracle.hpp"
#include <algorithm>
#include <chrono>
#include <fstream>
#include <iostream>
#include <optional>
#include <set>
#include <span>

namespace {
using namespace crown;
using io::Json;
using U64 = std::uint64_t;
using Clock = std::chrono::steady_clock;
namespace rank = planner::ranking;
namespace meta = planner::meta;

void require(bool value, const char* message) { if (!value) throw Error("search_experiment", message); }
U64 integer(const Json& value, U64 low, U64 high) {
  require(value.is_number_integer() && (value.is_number_unsigned() || value.get<std::int64_t>() >= 0), "expected unsigned integer");
  const auto result = value.get<U64>(); require(result >= low && result <= high, "search request grant outside finite range"); return result;
}
std::string read(const char* path) {
  std::ifstream stream(path, std::ios::binary); require(bool(stream), "cannot read search input");
  std::string text; char block[4096];
  while (stream) {
    stream.read(block, sizeof(block)); const auto count = static_cast<std::size_t>(stream.gcount());
    require(count <= 16U*1024U*1024U-text.size(), "search input exceeds16MiB"); text.append(block,count);
  }
  require(!stream.bad(), "search input read failed"); return text;
}
Json time_value(bool measure, Clock::time_point begin, Clock::time_point end) {
  if (!measure) return nullptr;
  const auto value = std::chrono::duration_cast<std::chrono::nanoseconds>(end-begin).count();
  require(value >= 0, "steady clock regressed"); return static_cast<U64>(value);
}
struct Request {
  std::string method;
  bool measure;
  U64 work, proof_work, records, cells, rank_work, memory;
  std::size_t depth, scopes, candidates, proposals;
  std::vector<U64> training;
  planner::CandidateLimits candidate_limits() const {
    planner::CandidateLimits limits; limits.enumeration.work=work; limits.records=records;
    limits.cells=cells; limits.logical_depth=depth; limits.retained_candidates=candidates; return limits;
  }
  rank::Limits rank_limits() const {
    rank::Limits limits; limits.work=rank_work; limits.cells=cells;
    limits.candidates=candidates; limits.payload_bytes=64U*1024U*1024U; return limits;
  }
};
Request request(const Json& value, std::size_t tables) {
  const std::set<std::string> fields{"schema_version","command","method","work_limit","proof_work_limit","record_limit",
      "cell_limit","depth_limit","scope_limit","candidate_limit","proposal_limit","rank_work_limit","memory_limit_bytes","training_repetitions"};
  require(value.is_object() && value.size()==fields.size(), "closed search request field mismatch");
  for (const auto& field : value.items()) require(fields.contains(field.key()), "unknown search request field");
  require(integer(value.at("schema_version"),1,1)==1, "unknown search request version");
  const auto command=value.at("command").get<std::string>(); require(command=="verify" || command=="measure", "unknown search command");
  const auto method=value.at("method").get<std::string>();
  require(method=="literal_minimum" || method=="optimized" || method=="residual" || method=="meta" || method=="literal_family", "unknown search method");
  Request result{method,command=="measure",integer(value.at("work_limit"),0,50000000),integer(value.at("proof_work_limit"),0,100000000),
    integer(value.at("record_limit"),0,10000000),integer(value.at("cell_limit"),0,100000000),integer(value.at("rank_work_limit"),0,100000000),
    integer(value.at("memory_limit_bytes"),1024U*1024U,1024ULL*1024ULL*1024ULL),
    static_cast<std::size_t>(integer(value.at("depth_limit"),0,256)),static_cast<std::size_t>(integer(value.at("scope_limit"),1,4096)),
    static_cast<std::size_t>(integer(value.at("candidate_limit"),1,128)),static_cast<std::size_t>(integer(value.at("proposal_limit"),1,10000)),{}};
  require(value.at("training_repetitions").is_array() && value.at("training_repetitions").size()==tables, "one training count per physical table required");
  for (const auto& count : value.at("training_repetitions")) result.training.push_back(integer(count,0,32));
  return result;
}
planner::SearchOptions exact_options(U64 work, const Request& ask) {
  planner::SearchOptions options; options.policy=planner::SearchPolicy::strict;
  options.limits.producer.work=work; options.limits.replay.work=work; options.limits.logical_depth=ask.depth; return options;
}
void complete(planner::ExactSearch& search) {
  for (;;) {
    const auto step=search.advance({4096,{}});
    if (step.stopped_for!=planner::StopReason::quantum_work && step.stopped_for!=planner::StopReason::quantum_time) break;
  }
}
void drain(planner::CandidateProvider& provider) {
  for (;;) {
    const auto step=provider.advance({4096,{}});
    if (step.stopped_for!=planner::CandidateStop::candidate_ready && step.stopped_for!=planner::CandidateStop::quantum_work &&
        step.stopped_for!=planner::CandidateStop::quantum_time) break;
  }
}
Json shape(const FreeConnexTree& tree) {
  std::size_t fanout=0, generalized=0; bool normalized=true;
  for (const auto& node : tree.nodes) {
    fanout=std::max(fanout,node.children.size());
    if (node.kind==NodeKind::generalized) { ++generalized; normalized=normalized && node.children.size()>=2; }
  }
  return {{"nodes",tree.nodes.size()},{"generalized_nodes",generalized},{"maximum_child_fanout",fanout},{"normalized_no_unary",normalized}};
}
Json meta_report(const meta::MetaCandidateReport& p) {
  return {{"construction_stop",static_cast<unsigned>(p.construction_stop)},
    {"construction",{{"work",p.construction_usage.work},{"nodes",p.construction_usage.nodes},{"cells",p.construction_usage.scope_cells}}},
    {"enumeration_stop",static_cast<unsigned>(p.enumeration_stop)},
    {"enumeration",{{"work",p.enumeration_usage.work},{"fragments",p.enumeration_usage.fragments},{"cells",p.enumeration_usage.cells},{"outputs",p.enumeration_usage.output_trees}}},
    {"mapping_stop",static_cast<unsigned>(p.mapping_stop)},
    {"mapping",{{"work",p.mapping_usage.work},{"fragments",p.mapping_usage.fragments},{"cells",p.mapping_usage.cells},{"outputs",p.mapping_usage.output_trees},{"peak_depth",p.mapping_usage.peak_depth}}},
    {"ordinary_exhausted",p.ordinary_exhausted},{"mapped_input_fibers_exhausted",p.mapped_input_fibers_exhausted},
    {"rooted_ordinary_trees",p.rooted_ordinary_trees},{"undirected_trees",p.undirected_trees},
    {"scope",std::string(p.scope)},{"cost_scope",std::string(p.cost_scope)}};
}

// C02 consumes an actual owner census. The declared repetitions cause real
// inserts/noops; they are not caller-manufactured Evidence or model coefficients.
Json scoring(const planner::CandidateSnapshot& snapshot, const Request& ask) {
  if (!snapshot.candidate_count()) return {{"availability","no_candidates"}};
  const auto first=*snapshot.candidate(0); const auto& catalog=first.catalog();
  for (const auto& table : catalog.tables) {
    if (!table.constraints.empty() || table.columns.size()>16 || std::any_of(table.columns.begin(),table.columns.end(),[](const Column& column) {
        return column.type!=ScalarType::int64 || column.nullable;
      })) return {{"availability","scoring_requires_unconstrained_nonnull_int64_tables_arity_at_most16"}};
  }
  auto plan=planner::lower_tree(catalog,first.query(),first.tree());
  runtime::DeltaOptions options; options.mode=runtime::DeltaMode::maintenance;
  options.physical.support.memory_limit_bytes=ask.memory;
  runtime::DeltaRuntime owner(plan,options); runtime::workload::Options collect; collect.mode=runtime::workload::Mode::counters;
  owner.configure_workload_statistics(collect); U64 sequence=0;
  for (std::size_t table=0; table<catalog.tables.size(); ++table) {
    std::vector<storage::ScalarView> cells(catalog.tables[table].columns.size(),storage::ScalarView{std::int64_t{0}});
    for (U64 repeat=0; repeat<ask.training[table]; ++repeat) {
      auto pending=owner.begin_view({++sequence,TableId{table},SetOperation::insert,
          storage::TupleValuesView::borrow(storage::RowView::borrow(std::span<const storage::ScalarView>{cells}))});
      while (pending.step()!=runtime::DeltaStep::prepared) {}
      auto epoch=pending.commit(); static_cast<void>(epoch);
    }
  }
  runtime::ranking::CaptureOptions capture_options; capture_options.source_cardinalities=false; capture_options.processing=ask.rank_limits();
  const auto captured=runtime::ranking::capture(snapshot,owner,capture_options);
  Json result{{"policy","committed_input_native_depth"},{"capture_stop",static_cast<unsigned>(captured.stop)},
      {"capture_reasons",captured.reasons},{"actual_training_events",sequence},{"availability","evidence_unavailable"}};
  if (!captured.evidence) return result;
  const auto& evidence=captured.evidence->inputs(); auto weights=Json::array();
  for (const auto& weight : evidence.weights()) weights.push_back({{"table",weight.table.value},{"inserts",weight.inserts},
      {"erases",weight.erases},{"changed",weight.changed},{"noop",weight.noop}});
  result["observed_weights"]=std::move(weights); result["denominator"]=evidence.denominator(); result["depth_reasons"]=evidence.depth_reasons();
  rank::Request rank_request; rank_request.policy=rank::Policy::committed_input_native_depth;
  rank_request.fallback=rank::Fallback::require_evidence; rank_request.limits=ask.rank_limits();
  const auto ranked=rank::rank_with_account(owner.plan().account(),snapshot,rank_request,evidence);
  result["stop"]=static_cast<unsigned>(ranked.stop); result["reasons"]=ranked.reasons; result["evaluated"]=ranked.evaluated;
  if (ranked.result) {
    result["availability"]="actual_c02_census_scores"; auto scores=Json::array();
    for (const auto& score : ranked.result->scores()) scores.push_back({{"structural_key",std::string(score.structural_key.data(),score.structural_key.size())},
      {"numerator",std::string(score.numerator.data(),score.numerator.size())},{"denominator",std::string(score.denominator.data(),score.denominator.size())}});
    result["scores"]=std::move(scores); result["selected_key"]=ranked.result->selected().structural_key();
  }
  result["native_account_peak_requested_bytes"]=owner.accounted_memory_statistics().peak_requested_bytes;
  result["scope"]="real C02 training census and structural proxy only; no C03, CPU-latency prediction, heldout fit or runtime installation";
  return result;
}

int run(int argc, char** argv) {
  require(argc==3,"usage: crown_search_components QUERY.cq.json REQUEST.json");
  const auto reading=Clock::now(); const auto source=read(argv[1]); const auto encoded=io::read_json(read(argv[2]));
  const auto document=io::read_document(source); const auto ask=request(encoded,document.catalog.tables.size());
  require(document.updates.empty() && std::all_of(document.initial.tables.begin(),document.initial.tables.end(),[](const Relation& rows){return rows.empty();}),
      "search source must have empty initial rows and no updates");
  const auto admitted=Clock::now(); std::set<VariableId> active;
  for (const auto& atom : document.query.atoms) for (const auto& term : atom.terms) if (const auto* variable=std::get_if<VariableId>(&term)) active.insert(*variable);
  Json report{{"schema_version",1},{"kind","b04_finite_search_record_v1"},{"method",ask.method},{"command",encoded.at("command")},{"request",encoded},
    {"source_sha256",sha256(source)},{"canonical_source_sha256",sha256(io::write_document(document).dump())},
    {"query",{{"native_occurrences",document.query.atoms.size()},{"declared_variables",document.query.variables.size()},
      {"active_variables",active.size()},{"head_variables",document.query.head.size()},{"physical_tables",document.catalog.tables.size()}}},
    {"status","reported"},{"original",nullptr},{"algorithm",nullptr},{"candidate_progress",nullptr},{"candidates",Json::array()},
    {"scoring",{{"availability","not_requested_without_candidates"}}},
    {"timings",{{"read_admission_ns",time_value(ask.measure,reading,admitted)},{"shared_original_proof_ns",nullptr},
      {"algorithm_ns",nullptr},{"candidate_admission_ns",nullptr},{"runtime_training_and_c02_ns",nullptr}}},
    {"qualification","finite diagnostic: separate literal/P06/residual/meta algorithms; named logical work units differ; call timers exclude host export/proposal copies/cleanup still charged in process wall; RSS includes process/source/shared proof/output/capture; no planner-only phase peak, global cost, C03 or B04 acceptance"}};
  auto emit=[&]() {const auto text=report.dump(); require(text.size()<=16U*1024U*1024U,"search report exceeds16MiB");
    std::cout<<text<<'\n';std::cout.flush();return std::cout?0:1;};
  if (document.query.atoms.size()>6 || active.size()>16 || document.catalog.tables.size()>6 || document.query.contradiction) {
    report["status"]="unsupported_diagnostic_domain"; return emit();
  }
  if (ask.method=="literal_minimum") {
    planner::SearchLimits limits; limits.work_limit=ask.work; limits.recursion_limit=ask.depth; limits.literal_scope_limit=ask.scopes;
    const auto begin=Clock::now(); const auto result=reference::exhaustive_minimum_tree(document.catalog,document.query,limits);
    report["timings"]["algorithm_ns"]=time_value(ask.measure,begin,Clock::now());
    const auto status=result.status==planner::OracleStatus::proven_minimum?"minimum":result.status==planner::OracleStatus::unsupported?"infeasible":"resource_limit";
    report["algorithm"]={{"algorithm",result.algorithm},{"status",status},{"reason",result.reason},{"work",result.statistics.work},
        {"candidates_checked",result.statistics.candidates},{"minimum_decision_complete",result.status!=planner::OracleStatus::resource_limit},
        {"height",result.minimum_height?Json(*result.minimum_height):Json{}},{"family_exhausted",false}};
    if (result.tree) {
      const auto checked=planner::validate_tree(document.catalog,document.query,*result.tree);
      require(checked.valid && checked.native_height==result.minimum_height,"literal returned an invalid height witness");
      report["algorithm"]["witness"]=io::write_tree(*result.tree,document.catalog,document.query);
      report["algorithm"]["reference_signature"]=reference::normal_form_reference_signature(*result.tree);
    }
    return emit();
  }
  const auto proof_begin=Clock::now();
  auto exact=planner::ExactSearch::create(document.catalog,document.query,exact_options(ask.method=="optimized"?ask.work:ask.proof_work,ask));
  complete(exact); const auto proof_end=Clock::now();
  report["timings"][ask.method=="optimized"?"algorithm_ns":"shared_original_proof_ns"]=time_value(ask.measure,proof_begin,proof_end);
  report["original"]={{"progress",io::write_search_progress(exact)}};
  if (const auto infeasible=exact.infeasibility()) {
    report["original"]["certificate"]=io::write_verified_infeasible(*infeasible);report["status"]="verified_infeasible";return emit();
  }
  const auto proof=exact.optimum();
  if (!proof) {report["status"]="original_minimum_unavailable";return emit();}
  report["original"]["height"]=proof->height();report["original"]["certificate"]=io::write_verified_optimum(*proof);
  std::optional<planner::CandidateProvider> provider;
  bool upstream_exhausted=false;
  auto admission_begin=Clock::now();
  if (ask.method=="optimized") {
    report["algorithm"]={{"algorithm","P06_exact_original_with_P07_family"},{"status","minimum"},{"height",proof->height()}};
    provider.emplace(planner::CandidateProvider::create(*proof,{},ask.candidate_limits()));upstream_exhausted=true;
  } else if (ask.method=="residual") {
    planner::ResidualOptions options;options.mode=planner::ResidualMode::candidates_with_exact_repair;
    options.limits.residual.work=ask.work;options.limits.exact=exact_options(ask.work,ask).limits;
    options.limits.logical_depth=ask.depth;options.limits.record_limit=ask.records;options.limits.cell_limit=ask.cells;
    const auto begin=Clock::now();auto residual=planner::ResidualSearch::create(document.catalog,document.query,options);
    while (residual.progress().result==planner::ResidualResult::unfinished) {
      const auto step=residual.advance({4096,{}});
      if (step.stopped_for!=planner::ResidualStopReason::quantum_work && step.stopped_for!=planner::ResidualStopReason::quantum_time) break;
    }
    report["timings"]["algorithm_ns"]=time_value(ask.measure,begin,Clock::now());
    report["algorithm"]={{"algorithm","actual_residual_with_exact_repair"},{"progress",io::write_residual_progress(residual)},
      {"scope","one actual residual candidate; delegated exact repair exposed, not a complete normalized family"}};
    std::vector<FreeConnexTree> proposals;
    if (const auto upper=residual.candidate()) {
      require(upper->height()>=proof->height(),"residual upper is below independently proved original minimum");
      report["algorithm"]["upper"]=io::write_residual_candidate(*upper);report["algorithm"]["height_gap"]=upper->height()-proof->height();
      proposals.push_back(upper->tree());
    }
    admission_begin=Clock::now();provider.emplace(planner::CandidateProvider::from_proposals(*proof,std::move(proposals),{},ask.candidate_limits()));
  } else if (ask.method=="meta") {
    meta::MetaCandidateLimits limits;limits.construction.work=ask.work;limits.construction.nodes=static_cast<std::size_t>(std::min<U64>(ask.records,100000));limits.construction.scope_cells=ask.cells;
    limits.enumeration.work=ask.work;limits.enumeration.fragments=ask.records;limits.enumeration.cells=ask.cells;limits.enumeration.output_trees=ask.proposals;limits.enumeration.metadata=limits.construction;
    limits.mapping.work=ask.work;limits.mapping.fragments=ask.records;limits.mapping.cells=ask.cells;limits.mapping.output_trees=ask.proposals;limits.mapping.depth=ask.depth;limits.admission=ask.candidate_limits();
    const auto begin=Clock::now();auto prepared=meta::prepare_meta_candidates(*proof,limits);
    report["timings"]["algorithm_ns"]=time_value(ask.measure,begin,Clock::now());report["algorithm"]=meta_report(prepared.report);
    upstream_exhausted=prepared.report.ordinary_exhausted && prepared.report.mapped_input_fibers_exhausted;
    admission_begin=Clock::now();if (prepared.provider) provider.emplace(std::move(*prepared.provider));
  } else {
    const auto begin=Clock::now();auto collected=reference::collect_normal_form_plan_set(document.catalog,document.query,proof->height(),{ask.work});
    report["timings"]["algorithm_ns"]=time_value(ask.measure,begin,Clock::now());
    report["algorithm"]={{"algorithm","independent_tiny_normal_form_family"},{"work",collected.work_units},{"stop",static_cast<unsigned>(collected.stop)},
        {"reference_family_exhausted",collected.exhausted},{"resource_limited",collected.resource_limited},{"proposals",collected.plans.size()},
        {"native_cap",reference::normal_form_reference_native_cap},{"active_variable_cap",reference::normal_form_reference_active_variable_cap}};
    upstream_exhausted=collected.exhausted;std::vector<FreeConnexTree> proposals;
    for (auto& candidate : collected.plans) proposals.push_back(std::move(candidate.representative));
    admission_begin=Clock::now();provider.emplace(planner::CandidateProvider::from_proposals(*proof,std::move(proposals),{},ask.candidate_limits()));
  }
  if (provider) {
    drain(*provider);report["candidate_progress"]=io::write_candidate_progress(*provider);
    report["timings"]["candidate_admission_ns"]=time_value(ask.measure,admission_begin,Clock::now());
    const auto snapshot=provider->snapshot();report["upstream_and_admission_exhausted"]=upstream_exhausted && snapshot.family_exhausted();
    for (std::size_t index=0; index<snapshot.candidate_count(); ++index) {
      const auto candidate=*snapshot.candidate(index);
      report["candidates"].push_back({{"structural_key",candidate.structural_key()},{"reference_signature",reference::normal_form_reference_signature(candidate.tree())},
        {"height",candidate.height()},{"shape",shape(candidate.tree())},{"provenance",io::write_minimum_height_candidate(candidate).at("provenance")},
        {"tree",io::write_tree(candidate.tree(),candidate.catalog(),candidate.query())}});
    }
    const auto begin=Clock::now();report["scoring"]=scoring(snapshot,ask);
    report["timings"]["runtime_training_and_c02_ns"]=time_value(ask.measure,begin,Clock::now());
  } else report["upstream_and_admission_exhausted"]=false;
  return emit();
}
} // namespace
int main(int argc, char** argv) {
  try {return run(argc,argv);}
  catch (const std::exception& error) {std::cerr<<error.what()<<'\n';return 1;}
}
