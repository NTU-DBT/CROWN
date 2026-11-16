#include "crown/planner/meta_candidates.hpp"
#include "crown/planner/selection.hpp"
#include "crown/planner/verify.hpp"
#include "crown/io/candidates.hpp"
#include "crown/io/explain.hpp"
#include "candidate_set.hpp"
#include <algorithm>
#include <functional>
#include <iostream>
#include <map>
#include <set>
#include <stdexcept>
#include <string>
#include <vector>

namespace {
using namespace crown;
using namespace crown::planner;
namespace meta = crown::planner::meta;
namespace selection = crown::planner::selection;
void require(bool value,const std::string& message) { if (!value) throw std::runtime_error(message); }
struct Fixture { Catalog catalog; Query query; };
Fixture fixture(const std::vector<std::vector<std::size_t>>& edges,
                const std::vector<std::size_t>& head = {}) {
  Fixture f; std::map<std::size_t,VariableId> variables;
  for (const auto& edge : edges) for (auto x : edge) variables.emplace(x,VariableId{0});
  for (auto& [label,id] : variables) {
    id = VariableId{f.query.variables.size()};
    f.query.variables.push_back({"v"+std::to_string(label),ScalarType::int64});
  }
  for (std::size_t i = 0; i < edges.size(); ++i) {
    Table table{"R"+std::to_string(i),{}}; Atom atom{"r"+std::to_string(i),TableId{i},{}};
    for (auto x : edges[i]) {
      table.columns.push_back({"c"+std::to_string(table.columns.size()),ScalarType::int64});
      atom.terms.emplace_back(variables.at(x));
    }
    f.catalog.tables.push_back(std::move(table)); f.query.atoms.push_back(std::move(atom));
  }
  for (auto x : head) f.query.head.push_back({variables.at(x),"h"+std::to_string(x)});
  validate(f.catalog,f.query); return f;
}
VerifiedOptimum prove(const Fixture& f) {
  auto exact = ExactSearch::create(f.catalog,f.query);
  const auto done = exact.advance({50'000'000,{}});
  require(done.progress.result == ResultKind::verified_optimum && exact.optimum(),"independent original proof did not complete");
  return *exact.optimum();
}
void finish(CandidateProvider& owner) {
  for (std::size_t i = 0; i < 10000; ++i) {
    const auto stop = owner.advance({1'000'000,{}}).stopped_for;
    if (stop == CandidateStop::exhausted) return;
    require(stop == CandidateStop::candidate_ready || stop == CandidateStop::quantum_work,"unexpected mapped admission stop");
  }
  throw std::runtime_error("mapped candidate batch did not exhaust");
}
std::set<std::string> signatures(const Fixture& f,const CandidateSnapshot& snapshot,std::size_t height) {
  std::set<std::string> result;
  for (std::size_t i = 0; i < snapshot.candidate_count(); ++i) {
    const auto c = snapshot.candidate(i); require(c.has_value(),"published mapped candidate missing");
    const auto checked = validate_tree(f.catalog,f.query,c->tree());
    require(checked.valid && checked.native_height == height && c->height() == height,"mapped candidate bypassed P02/height");
    require(c->provenance().source == CandidateSource::supplied_proposal &&
            c->provenance().family == CandidateFamily::finite_proposals_v1,"mapper added a fallback seed");
    require(result.insert(reference::normal_form_reference_signature(c->tree())).second,"mapped duplicate escaped structural gate");
  }
  return result;
}
void complete(const meta::PreparedMetaCandidates& prepared) {
  require(prepared.report.construction_stop == meta::Stop::complete && prepared.report.ordinary_exhausted &&
          prepared.report.mapping_stop == meta::MappingStop::complete && prepared.report.mapped_input_fibers_exhausted,
          "unbounded small mapping did not finish preparation");
  require(!prepared.report.heuristic_used,"exact local mapping reported a heuristic");
}
void reference_case(const Fixture& f,const std::string& label) {
  const auto proof = prove(f); const auto frozen = io::write_verified_optimum(proof);
  auto prepared = meta::prepare_meta_candidates(proof); complete(prepared);
  require(!prepared.report.all_ordinary_roots_materialized &&
          prepared.report.rooted_ordinary_trees == prepared.report.undirected_trees,
          label+": adapter materialized discarded ordinary rootings");
  require(prepared.provider && !prepared.normalized_minimum_family_exhausted(),label+": preparation pretended P02 completion");
  finish(*prepared.provider);
  require(prepared.normalized_minimum_family_exhausted(),label+": complete mapping/admission lost coverage status");
  const auto actual = signatures(f,prepared.provider->snapshot(),proof.height());
  const auto independent = reference::collect_normal_form_plan_set(f.catalog,f.query,proof.height());
  require(independent.exhausted && !independent.resource_limited,label+": independent normalized oracle stopped");
  std::set<std::string> expected;
  for (const auto& plan : independent.plans) expected.insert(plan.signature);
  require(!expected.empty() && actual == expected,label+": inverse contractions miss or invent a normalized minimum shape");
  for (std::size_t i = 0; i < prepared.provider->candidate_count(); ++i)
    require(io::write_verified_optimum(prepared.provider->candidate(i)->original_proof()) == frozen,label+": mapping changed original certificate");
  std::cout << label << " h=" << proof.height() << " normalized_minima=" << actual.size() << '\n';
}

// Independent hierarchical set partitions, not inverse contractions or a join
// tree traversal. On identical scopes every hierarchy is P02-valid at height1.
std::vector<FreeConnexTree> hierarchies(const std::vector<std::size_t>& leaves) {
  if (leaves.size() == 1) return {{NodeId{0},{{"n",NodeKind::native,{VariableId{0}},{},leaves[0],{}}},{},{}}};
  std::vector<FreeConnexTree> result;
  std::vector<std::vector<std::size_t>> blocks;
  const auto partitions = [&](auto&& self,std::size_t i) -> void {
    if (i != leaves.size()) {
      const auto count = blocks.size();
      for (std::size_t j = 0; j < count; ++j) { blocks[j].push_back(leaves[i]); self(self,i+1); blocks[j].pop_back(); }
      blocks.push_back({leaves[i]}); self(self,i+1); blocks.pop_back(); return;
    }
    if (blocks.size() < 2) return;
    std::vector<std::vector<FreeConnexTree>> options;
    for (const auto& block : blocks) options.push_back(hierarchies(block));
    FreeConnexTree base{NodeId{0},{{"g",NodeKind::generalized,{VariableId{0}},{},{},{}}},{},{}};
    const auto choose = [&](auto&& next,std::size_t k,const FreeConnexTree& prefix) -> void {
      if (k == options.size()) { result.push_back(prefix); return; }
      for (const auto& child : options[k]) {
        auto tree = prefix; const auto offset = tree.nodes.size();
        tree.nodes[0].children.push_back(NodeId{offset+child.root->value});
        for (auto node : child.nodes) {
          for (auto& id : node.children) id.value += offset;
          node.id += std::to_string(tree.nodes.size()); tree.nodes.push_back(std::move(node));
        }
        next(next,k+1,tree);
      }
    };
    choose(choose,0,base);
  };
  partitions(partitions,0); return result;
}
void four_leaf_fiber() {
  const auto f = fixture({{0},{0},{0},{0}}); const auto proof = prove(f);
  require(proof.height() == 1,"four-leaf literal lower/upper control");
  const auto expected_trees = hierarchies({0,1,2,3}); std::set<std::string> expected;
  for (const auto& tree : expected_trees) {
    require(validate_tree(f.catalog,f.query,tree).valid,"independent hierarchy fixture invalid");
    expected.insert(reference::normal_form_reference_signature(tree));
  }
  require(expected.size() == 26 && expected_trees.size() == 26,"independent four-leaf hierarchy count");
  auto prepared = meta::prepare_meta_candidates(proof); complete(prepared); require(prepared.provider.has_value(),"four-leaf provider absent");
  finish(*prepared.provider);
  require(prepared.normalized_minimum_family_exhausted() && signatures(f,prepared.provider->snapshot(),1) == expected,
          "nested/nonbinary generalized fibers are incomplete");
}
void grants_and_status() {
  const auto f = fixture({{0},{0},{0}}); const auto proof = prove(f);
  auto full = meta::prepare_meta_candidates(proof); complete(full); require(full.provider.has_value(),"budget baseline provider");
  const auto usage = full.report.mapping_usage;
  meta::MetaCandidateLimits exact;
  exact.mapping = {usage.work,usage.fragments,usage.cells,usage.output_trees,usage.peak_depth};
  auto baseline = meta::prepare_meta_candidates(proof,exact); complete(baseline);
  require(baseline.provider.has_value(),"exact mapping grants omitted provider"); finish(*baseline.provider);
  const auto expected = signatures(f,baseline.provider->snapshot(),proof.height());
  meta::MetaCandidateLimits all_roots; all_roots.enumeration.all_roots = true;
  auto rooted = meta::prepare_meta_candidates(proof,all_roots); complete(rooted);
  require(rooted.provider && rooted.report.all_ordinary_roots_materialized &&
          rooted.report.rooted_ordinary_trees == f.query.atoms.size()*rooted.report.undirected_trees,
          "explicit all-root mode lost its orientation count");
  finish(*rooted.provider);
  require(signatures(f,rooted.provider->snapshot(),proof.height()) == expected,
          "canonical representatives changed normalized CROWN coverage");
  const auto stops = {meta::MappingStop::work_limit,meta::MappingStop::fragment_limit,meta::MappingStop::cell_limit,
                      meta::MappingStop::output_limit,meta::MappingStop::depth_limit};
  for (auto reason : stops) for (bool zero : {false,true}) {
    auto tight = exact;
    if (reason == meta::MappingStop::work_limit) tight.mapping.work = zero ? 0 : usage.work-1;
    if (reason == meta::MappingStop::fragment_limit) tight.mapping.fragments = zero ? 0 : usage.fragments-1;
    if (reason == meta::MappingStop::cell_limit) tight.mapping.cells = zero ? 0 : usage.cells-1;
    if (reason == meta::MappingStop::output_limit) tight.mapping.output_trees = zero ? 0 : usage.output_trees-1;
    if (reason == meta::MappingStop::depth_limit) tight.mapping.depth = zero ? 0 : usage.peak_depth-1;
    auto partial = meta::prepare_meta_candidates(proof,tight);
    require(partial.report.mapping_stop == reason && !partial.report.mapped_input_fibers_exhausted &&
            !partial.normalized_minimum_family_exhausted(),"mapping limit mislabeled completion");
    require(partial.report.mapping_usage.work <= tight.mapping.work && partial.report.mapping_usage.fragments <= tight.mapping.fragments &&
            partial.report.mapping_usage.cells <= tight.mapping.cells && partial.report.mapping_usage.output_trees <= tight.mapping.output_trees &&
            partial.report.mapping_usage.peak_depth <= tight.mapping.depth,"mapping exceeded a grant");
    if (partial.provider) {
      finish(*partial.provider); const auto actual = signatures(f,partial.provider->snapshot(),proof.height());
      require(std::includes(expected.begin(),expected.end(),actual.begin(),actual.end()) &&
              !partial.normalized_minimum_family_exhausted(),"partial input fiber claimed full coverage after batch completion");
    }
  }
  meta::MetaCandidateLimits limited;
  limited.enumeration.output_trees = 1;
  auto ordinary_prefix = meta::prepare_meta_candidates(proof,limited);
  require(!ordinary_prefix.report.ordinary_exhausted && !ordinary_prefix.normalized_minimum_family_exhausted(),"ordinary limit mislabeled full search");
  if (ordinary_prefix.provider) {
    finish(*ordinary_prefix.provider);
    require(ordinary_prefix.provider->snapshot().family_exhausted() && !ordinary_prefix.normalized_minimum_family_exhausted(),
            "consumed supplied batch was confused with upstream meta coverage");
  }
  limited = {}; limited.admission.retained_candidates = 1;
  auto stopped = meta::prepare_meta_candidates(proof,limited); complete(stopped);
  require(stopped.provider && stopped.provider->advance({1'000'000,{}}).stopped_for == CandidateStop::candidate_ready,"admission cap fixture");
  require(stopped.provider->advance({1'000'000,{}}).stopped_for == CandidateStop::candidate_capacity &&
          !stopped.normalized_minimum_family_exhausted(),"admission cap lost independent coverage status");
  auto raised = stopped.provider->limits(); raised.retained_candidates = 128;
  require(stopped.provider->raise_limits(raised) == LimitChange::applied,"mapping admission grant extension");
  finish(*stopped.provider); require(stopped.normalized_minimum_family_exhausted(),"resumed checked fiber completion");
}
void selection_and_domains() {
  const auto f = fixture({{0},{0,1},{1}}); const auto proof = prove(f);
  auto prepared = meta::prepare_meta_candidates(proof); complete(prepared); require(prepared.provider.has_value(),"selection fixture provider");
  finish(*prepared.provider); const auto snapshot = prepared.provider->snapshot();
  selection::Request request; request.policy = selection::Policy::height_only;
  request.family = selection::FamilyPolicy::require_exhausted_family;
  auto cache = selection::PlanCache::create();
  const auto picked = selection::select(snapshot,selection::DirectCQ{},request,{},&cache,selection::CacheUse::read_write);
  require(picked.selection && picked.stop == selection::Stop::complete && picked.selection->selected().height() == proof.height(),
          "meta family did not integrate with existing C02/C05");
  const auto report = observability::PlanExplanation::create(picked.selection->plan(),picked.selection->selected(),snapshot);
  const auto json = io::Json::parse(io::write_explain_json(report));
  require(json.at("candidate_family").at("family") == "finite-proposals-v1" &&
          json.at("candidate_family").at("global_cost_complete") == false,"meta selection invented global cost coverage");
  auto moved = std::move(*prepared.provider); finish(moved);
  require(!prepared.normalized_minimum_family_exhausted(),"moved-out provider retained stale completion authority");
  for (const auto& edges : {std::vector<std::vector<std::size_t>>{},std::vector<std::vector<std::size_t>>{{}}}) {
    const auto input = fixture(edges); const auto original = prove(input); auto skipped = meta::prepare_meta_candidates(original);
    require(!skipped.provider && !skipped.normalized_minimum_family_exhausted() &&
            skipped.report.construction_stop == (edges.empty() ? meta::Stop::empty_body : meta::Stop::nullary_occurrence),
            "paper-domain boundary rejected engine semantics or invented a fallback");
    require(original.valid(),"unsupported meta domain destroyed original exact authority");
  }
}
} // namespace
int main() {
  try {
    for (const auto& head : std::vector<std::vector<std::size_t>>{{},{0},{1},{0,1}})
      reference_case(fixture({{0},{0,1},{1}},head),"chain/head"+std::to_string(head.size()));
    for (const auto& head : std::vector<std::vector<std::size_t>>{{},{0},{1},{0,1}})
      reference_case(fixture({{0},{1}},head),"disconnected/head"+std::to_string(head.size()));
    reference_case(fixture({{0},{0},{0}}),"equal scopes nested prefix");
    reference_case(fixture({{0},{0,1},{0,1}},{1}),"nested scopes hidden-root/head");
    reference_case(fixture({{0,1},{1,2},{1}},{0}),"nonhead separator forces native root");
    auto aliases = fixture({{0},{0},{0,1}}); aliases.query.atoms[1].table = TableId{0};
    reference_case(aliases,"duplicate physical table aliases");
    four_leaf_fiber(); grants_and_status(); selection_and_domains();
    std::cout << "meta CROWN adapter: independent normalized families, limits, head/P02 and C02/C05 passed\n";
  } catch (const std::exception& error) { std::cerr << error.what() << '\n'; return 1; }
}
