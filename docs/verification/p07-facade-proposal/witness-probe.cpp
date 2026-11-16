// Excluded proposal probe: obtain all authority through public P06 replay.
#include "../p07-api-proposal-2026-11-07.hpp"
#include "crown/io/search.hpp"
#include "crown/planner/verify.hpp"
#include <iostream>
#include <stdexcept>

namespace {
using namespace crown;
using namespace crown::planner;
void require(bool condition, const char* message) {
  if (!condition) throw std::runtime_error(message);
}
void finish(CandidateProvider& provider) {
  for (std::size_t i = 0; i < 1000; ++i) {
    const auto update = provider.advance({1'000'000, {}});
    if (update.stopped_for == CandidateStop::exhausted) return;
    require(update.stopped_for == CandidateStop::candidate_ready ||
                update.stopped_for == CandidateStop::quantum_work,
            "proposal provider stopped unexpectedly");
  }
  throw std::runtime_error("proposal provider exceeded probe guard");
}
}  // namespace

int main() {
  try {
    Catalog catalog;
    catalog.tables.push_back(Table{"R", {{"x", ScalarType::int64}}});
    Query query;
    query.variables.push_back(Variable{"x", ScalarType::int64});
    query.atoms.push_back(Atom{"r", TableId{0}, {VariableId{0}}});
    auto exact = ExactSearch::create(catalog, query);
    require(exact.advance({1'000'000, {}}).progress.result == ResultKind::verified_optimum,
            "P06 did not prove singleton optimum");
    const auto normal_proof = *exact.optimum();
    auto claim = normal_proof.certificate();
    require(claim.tree && claim.tree->root && claim.tree->nodes.size() == 1,
            "unexpected singleton proof witness");
    const auto old_root = *claim.tree->root;
    claim.tree->nodes.push_back(TreeNode{"unary-generalized", NodeKind::generalized,
        {VariableId{0}}, {old_root}, {}, {}});
    claim.tree->root = NodeId{1};
    claim.tree->claimed_connex.reset();
    claim.tree->claimed_native_height.reset();
    const auto checked_tree = validate_tree(catalog, query, *claim.tree);
    require(checked_tree.valid && checked_tree.native_height == 1,
            "untrusted unary witness failed independent P02");
    auto replay = CertificateReplay::create(catalog, query, std::move(claim));
    const auto replayed = replay.advance({1'000'000, {}});
    require(replayed.progress.complete && replayed.progress.valid && replay.checked() &&
                replay.checked()->optimum(),
            "independent public P06 replay rejected unary minimum witness");
    const auto unary_proof = *replay.checked()->optimum();
    const auto certificate = io::write_verified_optimum(unary_proof);
    const auto native_certificate = io::write_verified_optimum(normal_proof);
    require(certificate != native_certificate, "non-normal witness was silently replaced");
    auto provider = CandidateProvider::create(unary_proof);
    finish(provider);
    require(provider.candidate_count() == 2 && provider.progress().family_exhausted,
            "normal form plus separately admitted unary seed was not retained");
    const auto retained = *provider.candidate(0);
    require(retained.tree().nodes.size() == 2 &&
                retained.provenance().source == CandidateSource::exact_witness,
            "first candidate did not preserve supplied unary exact witness");
    for (std::size_t i = 0; i < provider.candidate_count(); ++i) {
      const auto candidate = *provider.candidate(i);
      require(candidate.height() == 1 &&
                  validate_tree(catalog, query, candidate.tree()).valid &&
                  io::write_verified_optimum(candidate.original_proof()) == certificate,
              "alternative mutated original checked witness or proof");
    }
    const auto snapshot = provider.snapshot();
    auto cache = CandidateCache::create(1);
    require(cache.install(snapshot) == CandidateCacheInstall::inserted,
            "snapshot cache install failed");
    const auto cached = cache.lookup(normal_proof);
    require(cached.has_value(), "same binding with independently checked witness missed cache");
    auto fresh = CandidateProvider::create(normal_proof, {}, {}, {}, *cached);
    finish(fresh);
    require(fresh.candidate_count() == 2 && fresh.progress().family_exhausted,
            "cached non-normal seed was lost or falsely duplicated");
    for (std::size_t i = 0; i < fresh.candidate_count(); ++i) {
      require(io::write_verified_optimum(fresh.candidate(i)->original_proof()) == native_certificate,
              "cache reuse transplanted a former provider's proof witness");
    }
    provider.cancel();
    cache.clear();
    require(retained.tree().nodes.size() == 2 &&
                io::write_verified_optimum(retained.original_proof()) == certificate,
            "retained unary candidate changed after cancellation/cache clear");
    std::cout << "non_normal_seed=P06_replay unary_witness=preserved height=1 family_plus_seed=2\n"
              << "candidate_certificate=unchanged cache_reuse=new_provider_proof retained_handle=stable\n"
              << "proposal_only P07=not_started\n";
  } catch (const std::exception& error) {
    std::cerr << error.what() << '\n';
    return 1;
  }
}
