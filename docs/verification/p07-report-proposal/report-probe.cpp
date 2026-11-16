// Supplemental actual-artifact probe. No registration or P07 acceptance claim.
#include "report.hpp"
#include "crown/api/error.hpp"
#include "crown/planner/verify.hpp"
#include <iostream>
#include <stdexcept>
#include <type_traits>

namespace {
using namespace crown;
using namespace crown::planner;
namespace report = crown::io::alternatives_proposal;
void check(bool ok, const char* message) { if (!ok) throw std::runtime_error(message); }
struct Fixture { Catalog catalog; Query query; };
Fixture fixture(int version) {
  Fixture f;
  if (version == 1) {
    f.catalog.tables = {Table{"R", {{"x", ScalarType::int64}}},
        Table{"S", {{"x", ScalarType::int64}, {"y", ScalarType::int64}}},
        Table{"T", {{"y", ScalarType::int64}}}};
    f.query.variables = {{"x", ScalarType::int64}, {"y", ScalarType::int64}};
    f.query.atoms = {{"r", TableId{0}, {VariableId{0}}},
        {"s", TableId{1}, {VariableId{0}, VariableId{1}}}, {"t", TableId{2}, {VariableId{1}}}};
  } else {
    f.catalog.tables.push_back(Table{"D", {{"day", ScalarType::date}}});
    if (version == 3) f.catalog.tables[0].source_schema_version = 2;
    f.query.atoms.push_back({"d", TableId{0}, {Value{Date::parse("2024-02-29")}}});
  }
  return f;
}
VerifiedOptimum prove(const Fixture& f) {
  auto owner = ExactSearch::create(f.catalog, f.query);
  check(owner.advance({10'000'000, {}}).progress.result == ResultKind::verified_optimum,
        "report fixture did not produce P06 proof");
  return *owner.optimum();
}
void exhaust(CandidateProvider& p) {
  for (std::size_t i = 0; i < 100; ++i) {
    const auto r = p.advance({1'000'000, {}});
    if (r.stopped_for == CandidateStop::exhausted) return;
    check(r.stopped_for == CandidateStop::candidate_ready || r.stopped_for == CandidateStop::quantum_work,
          "provider stopped unexpectedly");
  }
  check(false, "provider did not exhaust");
}
static_assert(!std::is_invocable_v<decltype(&report::write_candidate_progress), const CandidateProgress&>);
static_assert(!std::is_invocable_v<decltype(&report::write_minimum_height_candidate), const ValidatedIncumbent&>);
}
int main() {
  try {
    auto documents = io::Json::array();
    bool distinct_upper = false;
    for (int version = 1; version <= 3; ++version) {
      const auto f = fixture(version);
      const auto proof = prove(f);
      const auto original = io::write_verified_optimum(proof);
      auto owner = CandidateProvider::create(proof);
      auto add = [&](const char* label, io::Json document) {
        check(document.at("query_binding").at("schema_version") == version,
              "report lost native CQ binding version");
        check(document.at("original_proof").at("certificate") == original,
              "report changed original proof or original witness");
        check(document.at("query_binding") == original.at("query_binding"), "report binding differs from proof");
        const auto decoded = io::read_height_certificate(
            document.at("original_proof").at("certificate").dump(), f.catalog, f.query);
        check(verify_height_certificate(f.catalog, f.query, decoded).valid, "embedded original certificate failed replay");
        documents.push_back({{"name", std::string(label) + "_cq" + std::to_string(version)},
                             {"document", std::move(document)}});
      };
      const auto before = owner.progress();
      add("admitted", report::write_candidate_progress(owner));
      check(owner.progress().work == before.work && owner.progress().candidate_count == 0,
            "report serialization advanced provider");
      add("empty_prefix", report::write_candidate_snapshot(owner.snapshot()));
      check(owner.advance({1'000'000, {}}).stopped_for == CandidateStop::candidate_ready,
            "first candidate unavailable");
      const auto partial = owner.snapshot();
      const auto frozen = report::write_candidate_snapshot(partial);
      add("partial_prefix", frozen);
      exhaust(owner);
      add("exhausted", report::write_candidate_progress(owner));
      add("full_prefix", report::write_candidate_snapshot(owner.snapshot()));
      check(report::write_candidate_snapshot(partial) == frozen && !partial.family_exhausted(),
            "saved snapshot serialization changed after live exhaustion");
      for (std::size_t i = 0; i < owner.candidate_count(); ++i) {
        const auto candidate = *owner.candidate(i);
        auto doc = report::write_minimum_height_candidate(candidate);
        check(candidate.height() == proof.height() && validate_tree(f.catalog, f.query, candidate.tree()).valid,
              "exported candidate is not independently valid at h*");
        check(doc.at("checked_upper").at("tree") == io::write_tree(candidate.tree(), f.catalog, f.query),
              "report replaced candidate upper");
        distinct_upper = distinct_upper || doc.at("checked_upper").at("tree") != original.at("tree");
        bool rejected = false;
        try { static_cast<void>(io::read_height_certificate(doc.dump(), f.catalog, f.query)); }
        catch (const Error&) { rejected = true; }
        check(rejected, "legacy certificate reader accepted report envelope as proof");
        add("candidate", std::move(doc));
      }
      auto cancelled = CandidateProvider::create(proof);
      cancelled.cancel();
      add("cancelled", report::write_candidate_progress(cancelled));
      auto retained = *owner.candidate(0);
      auto moved = std::move(retained);
      bool rejected = false;
      try { static_cast<void>(report::write_minimum_height_candidate(retained)); }
      catch (const Error&) { rejected = true; }
      check(rejected && moved.valid(), "writer accepted moved artifact");
    }
    check(distinct_upper, "probe never exported an alternative different from original witness");
    std::cout << documents.dump(2) << '\n';
    std::cerr << "reports=" << documents.size()
              << " CQ_versions=1,2,3 original_certificate=unchanged+replayed distinct_alternative=yes"
              << " snapshot=frozen progress=no_advance typed_gates=yes proposal_only P07=not_started\n";
  } catch (const std::exception& e) { std::cerr << e.what() << '\n'; return 1; }
}
