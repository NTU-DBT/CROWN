#include "crown/io/candidates.hpp"
#include "crown/api/error.hpp"
#include "crown/planner/verify.hpp"
#include <iostream>
#include <stdexcept>
#include <string_view>
#include <type_traits>
#include <cstdlib>
#include <new>

namespace allocation_probe {
enum class Mode { normal, allocation_failure, unexpected_failure };
Mode next = Mode::normal;
struct Unexpected final : std::exception {
  const char* what() const noexcept override { return "injected allocator failure"; }
};
void* allocate(std::size_t bytes) {
  const auto mode = next;
  next = Mode::normal;
  if (mode == Mode::allocation_failure) throw std::bad_alloc{};
  if (mode == Mode::unexpected_failure) throw Unexpected{};
  if (void* value = std::malloc(bytes == 0 ? 1 : bytes)) return value;
  throw std::bad_alloc{};
}
}
void* operator new(std::size_t bytes) { return allocation_probe::allocate(bytes); }
void* operator new[](std::size_t bytes) { return allocation_probe::allocate(bytes); }
void operator delete(void* value) noexcept { std::free(value); }
void operator delete[](void* value) noexcept { std::free(value); }
void operator delete(void* value, std::size_t) noexcept { std::free(value); }
void operator delete[](void* value, std::size_t) noexcept { std::free(value); }

namespace {
using namespace crown;
using namespace crown::planner;
namespace report = crown::io;
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
    f.catalog.tables.push_back(Table{"D", {{"day", ScalarType::date},
        {"amount", ScalarType::decimal}, {"unused", ScalarType::string}}});
    if (version == 3) f.catalog.tables[0].source_schema_version = 2;
    f.query.atoms.push_back({"d", TableId{0}, {Value{Date::parse("2024-02-29")},
        Value{Decimal::parse("12.50")}, IgnoredColumn{}}});
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
int main(int argc, char** argv) {
  try {
    check(argc == 2 && std::string_view(argv[1]) == "--emit", "usage: candidates_io_test --emit");
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
        documents.push_back({{"name", std::string(label) + "_cq" + std::to_string(version) + "_" + std::to_string(documents.size())},
                             {"schema", "candidate-report-v1.schema.json"}, {"document", std::move(document)}});
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
      CandidateLimits stopped_limits;
      stopped_limits.records = 0;
      auto stopped = CandidateProvider::create(proof, {}, stopped_limits);
      check(stopped.advance({1'000'000, {}}).stopped_for == CandidateStop::record_limit,
            "report fixture did not reach a real resource stop");
      add("resource_stopped", report::write_candidate_progress(stopped));
      auto retryable = CandidateProvider::create(proof);
      allocation_probe::next = allocation_probe::Mode::allocation_failure;
      const auto allocation_stop = retryable.advance({1'000'000, {}});
      check(allocation_probe::next == allocation_probe::Mode::normal &&
                allocation_stop.stopped_for == CandidateStop::allocation_failure,
            "report fixture did not reach a real allocation stop");
      add("allocation_stopped", report::write_candidate_progress(retryable));
      check(retryable.advance({1'000'000, {}}).stopped_for == CandidateStop::candidate_ready,
            "report fixture failed same-owner allocation recovery");
      auto failed = CandidateProvider::create(proof);
      allocation_probe::next = allocation_probe::Mode::unexpected_failure;
      const auto failure = failed.advance({1'000'000, {}});
      check(allocation_probe::next == allocation_probe::Mode::normal &&
                failure.stopped_for == CandidateStop::internal_failure &&
                failure.progress.phase == CandidatePhase::failed,
            "unexpected allocator exception did not reach terminal failure handling");
      add("failed", report::write_candidate_progress(failed));
      auto retained = *owner.candidate(0);
      auto moved = std::move(retained);
      bool rejected = false;
      try { static_cast<void>(report::write_minimum_height_candidate(retained)); }
      catch (const Error&) { rejected = true; }
      check(rejected && moved.valid(), "writer accepted moved artifact");
    }
    Fixture residual_fixture;
    residual_fixture.catalog.tables = {Table{"N", {}},
        Table{"R", {{"x", ScalarType::int64}, {"y", ScalarType::int64}}},
        Table{"S", {{"x", ScalarType::int64}}}};
    residual_fixture.query.variables = {{"x", ScalarType::int64}, {"y", ScalarType::int64}};
    residual_fixture.query.atoms = {{"n", TableId{0}, {}},
        {"r", TableId{1}, {VariableId{0}, VariableId{1}}}, {"s", TableId{2}, {VariableId{0}}}};
    residual_fixture.query.head = {{VariableId{1}, "y"}};
    const auto residual_proof = prove(residual_fixture);
    ResidualOptions residual_options;
    residual_options.mode = ResidualMode::candidates_with_exact_repair;
    auto residual = ResidualSearch::create(residual_fixture.catalog, residual_fixture.query, residual_options);
    check(residual.advance({50'000'000, {}}).stopped_for == ResidualStopReason::complete &&
              residual.candidate(), "distinct residual-source fixture did not complete");
    auto alternatives = CandidateProvider::create(residual_proof, {}, {}, *residual.candidate());
    exhaust(alternatives);
    check(alternatives.candidate_count() == 2 &&
              alternatives.candidate(1)->provenance().source == CandidateSource::residual_seed,
          "distinct residual-source candidate was not published");
    const auto residual_candidate = *alternatives.candidate(1);
    auto append_extra = [&](const char* label, io::Json document) {
      const auto original = io::write_verified_optimum(residual_proof);
      check(document.at("original_proof").at("certificate") == original &&
                document.at("query_binding") == original.at("query_binding"),
            "residual/cache report changed original proof binding or witness");
      const auto decoded = io::read_height_certificate(original.dump(),
          residual_fixture.catalog, residual_fixture.query);
      check(verify_height_certificate(residual_fixture.catalog, residual_fixture.query, decoded).valid,
            "residual/cache original certificate failed independent replay");
      documents.push_back({{"name", label}, {"schema", "candidate-report-v1.schema.json"},
                           {"document", std::move(document)}});
    };
    const auto residual_report = report::write_minimum_height_candidate(residual_candidate);
    check(residual_report.at("provenance").at("residual_trace").at("audit_scope") ==
              "frozen_residual_trace_only", "residual provenance lost trace-only authority");
    append_extra("residual_distinct", residual_report);
    auto cache = CandidateCache::create(1);
    check(cache.install(alternatives.snapshot()) == CandidateCacheInstall::inserted,
          "report cache install failed");
    const auto prefix = cache.lookup(residual_proof);
    check(prefix.has_value(), "report cache lookup failed");
    auto reused = CandidateProvider::create(residual_proof, {}, {}, {}, *prefix);
    exhaust(reused);
    check(reused.candidate_count() == 2 &&
              reused.candidate(1)->provenance().source == CandidateSource::residual_seed,
          "cached seed changed its original generation provenance");
    append_extra("cached_residual_distinct", report::write_minimum_height_candidate(*reused.candidate(1)));
    check(report::write_minimum_height_candidate(*reused.candidate(1)).at("provenance") ==
              residual_report.at("provenance"), "cache reuse rewrote residual generation provenance");
    append_extra("cached_residual_snapshot", report::write_candidate_snapshot(reused.snapshot()));
    check(distinct_upper, "probe never exported an alternative different from original witness");
    std::cout << documents.dump(2) << '\n';

  } catch (const std::exception& e) {
    allocation_probe::next = allocation_probe::Mode::normal;
    std::cerr << e.what() << '\n';
    return 1;
  }
}
