#include "crown/api/error.hpp"
#include "crown/io/search.hpp"
#include "crown/planner/verify.hpp"
#include "planner_probe.hpp"

#include <algorithm>
#include <cstddef>
#include <iostream>
#include <stdexcept>
#include <string>
#include <string_view>
#include <type_traits>
#include <utility>
#include <vector>

namespace {
using namespace crown;
namespace planner = crown::planner;
namespace io = crown::io;

void check(bool condition, const std::string& message) {
  if (!condition) throw std::runtime_error(message);
}

struct Fixture {
  Catalog catalog;
  Query query;
};

Fixture two_relation_fixture() {
  Fixture fixture;
  fixture.catalog.tables.push_back(Table{"R", {{"x", ScalarType::int64}, {"y", ScalarType::int64}}});
  fixture.catalog.tables.push_back(Table{"S", {{"y", ScalarType::int64}}});
  fixture.query.variables = {{"x", ScalarType::int64}, {"y", ScalarType::int64}};
  fixture.query.atoms.push_back({"r", TableId{0}, {VariableId{0}, VariableId{1}}});
  fixture.query.atoms.push_back({"s", TableId{1}, {VariableId{1}}});
  fixture.query.head.push_back({VariableId{0}, "x"});
  return fixture;
}

Fixture triangle_fixture() {
  Fixture fixture;
  for (std::size_t i = 0; i < 3; ++i) {
    fixture.catalog.tables.push_back(Table{"T" + std::to_string(i),
        {{"a", ScalarType::int64}, {"b", ScalarType::int64}}});
  }
  fixture.query.variables = {{"x", ScalarType::int64}, {"y", ScalarType::int64}, {"z", ScalarType::int64}};
  fixture.query.atoms = {
      {"xy", TableId{0}, {VariableId{0}, VariableId{1}}},
      {"yz", TableId{1}, {VariableId{1}, VariableId{2}}},
      {"xz", TableId{2}, {VariableId{0}, VariableId{2}}},
  };
  fixture.query.head = {{VariableId{0}, "x"}, {VariableId{1}, "y"}, {VariableId{2}, "z"}};
  return fixture;
}

Fixture date_fixture(bool with_catalog_metadata) {
  Fixture fixture;
  fixture.catalog.tables.push_back(Table{"D", {{"day", ScalarType::date}}});
  if (with_catalog_metadata) fixture.catalog.tables[0].source_schema_version = 2;
  fixture.query.atoms.push_back({"d", TableId{0}, {Value{Date::parse("2024-02-29")}}});
  return fixture;
}

using RecordList = std::vector<io::Json>;

std::string certificate_schema(const io::Json& document) {
  return "height-certificate-v" + std::to_string(document.at("schema_version").get<int>()) +
         ".schema.json";
}

void add_record(RecordList& records, std::string name, std::string schema, io::Json document) {
  records.push_back({{"name", std::move(name)}, {"schema", std::move(schema)},
                     {"document", std::move(document)}});
}

planner::SearchAdvance advance_to_search_completion(planner::ExactSearch& owner) {
  for (std::size_t step = 0; step < 1'000'000; ++step) {
    const auto advanced = owner.advance(planner::WorkQuantum{4096, {}});
    if (advanced.stopped_for == planner::StopReason::complete) return advanced;
    check(advanced.progress.result != planner::ResultKind::failed,
          "exact-search fixture failed before completion");
    check(advanced.stopped_for == planner::StopReason::quantum_work ||
          advanced.stopped_for == planner::StopReason::quantum_time,
          "exact-search fixture stopped for an unexpected reason");
  }
  throw std::runtime_error("exact-search fixture exceeded the transition guard");
}

planner::CheckedCertificate finish_replay(planner::CertificateReplay& owner,
                                           const std::string& label) {
  for (std::size_t step = 0; step < 1'000'000; ++step) {
    const auto advanced = owner.advance(planner::WorkQuantum{4096, {}});
    if (advanced.progress.complete) {
      check(advanced.progress.valid && owner.checked() && owner.checked()->valid(),
            label + ": replay did not publish valid checked authority");
      return *owner.checked();
    }
    check(advanced.stopped_for == planner::StopReason::quantum_work ||
          advanced.stopped_for == planner::StopReason::quantum_time,
          label + ": replay stopped for an unexpected reason");
  }
  throw std::runtime_error(label + ": replay exceeded the transition guard");
}

void reject_legacy_reader(const io::Json& document, const Fixture& fixture,
                          const std::string& label) {
  bool rejected = false;
  try {
    static_cast<void>(io::read_height_certificate(document.dump(), fixture.catalog, fixture.query));
  } catch (const Error&) {
    rejected = true;
  }
  check(rejected, label + " was accepted by the height-certificate reader");
}

RecordList build_records() {
  RecordList records;
  const auto fixture = two_relation_fixture();
  planner::SearchOptions strict_options;
  strict_options.policy = planner::SearchPolicy::strict;
  auto strict = planner::ExactSearch::create(fixture.catalog, fixture.query, strict_options);

  auto strict_admitted = io::write_search_progress(strict);
  check(strict_admitted.at("artifact") == "search_progress" &&
        strict_admitted.at("policy") == "strict" && strict_admitted.at("phase") == "admitted" &&
        strict_admitted.at("incumbent").is_null() && strict_admitted.at("certificate").is_null(),
        "admitted strict progress exposed a result or authority");
  add_record(records, "strict_admitted", "search-progress-v1.schema.json", strict_admitted);

  const auto first = strict.advance(planner::WorkQuantum{1, {}});
  check(first.stopped_for == planner::StopReason::quantum_work &&
        first.progress.result == planner::ResultKind::unfinished && !strict.incumbent() &&
        !strict.optimum() && !strict.infeasibility(),
        "unfinished strict search exposed typed authority");
  auto strict_suspended = io::write_search_progress(strict);
  check(strict_suspended.at("certificate").is_null() && strict_suspended.at("incumbent").is_null(),
        "strict suspended progress exposed an incumbent or certificate");
  add_record(records, "strict_suspended", "search-progress-v1.schema.json", strict_suspended);

  planner::SearchOptions best_options;
  best_options.policy = planner::SearchPolicy::best_found;
  auto best = planner::ExactSearch::create(fixture.catalog, fixture.query, best_options);
  io::Json best_upper_document;
  bool captured_incumbent = false;
  for (std::size_t step = 0; step < 1'000'000; ++step) {
    const auto advanced = best.advance(planner::WorkQuantum{1, {}});
    check(advanced.progress.result != planner::ResultKind::failed,
          "best-found fixture failed before exposing a checked upper");
    if (const auto upper = best.incumbent()) {
      const auto progress = best.progress();
      check(upper->valid() && upper->height() == 2 && !progress.producer_complete &&
            !progress.proof_complete && progress.result == planner::ResultKind::unfinished &&
            !best.optimum() && !best.infeasibility(),
            "best-found upper was not a validated witness published before final proof");
      const auto upper_document = io::write_validated_incumbent(*upper);
      check(upper_document.at("artifact") == "validated_incumbent" &&
            upper_document.at("height_status") == "valid_upper_bound" &&
            upper_document.at("height_upper_bound") == 2 &&
            !upper_document.contains("minimum_height") && upper_document.at("certificate").is_null(),
            "upper-bound artifact claimed a minimum or carried a certificate");
      const auto best_progress = io::write_search_progress(best);
      check(best_progress.at("policy") == "best_found" &&
            best_progress.at("incumbent") == upper_document &&
            best_progress.at("certificate").is_null(),
            "best-found progress did not carry exactly its checked upper artifact");
      add_record(records, "best_found_before_proof", "search-progress-v1.schema.json", best_progress);
      add_record(records, "validated_incumbent_upper", "search-progress-v1.schema.json", upper_document);
      best_upper_document = upper_document;
      captured_incumbent = true;
      break;
    }
    check(advanced.stopped_for == planner::StopReason::quantum_work,
          "unit-quantum best-found search stopped unexpectedly");
  }
  check(captured_incumbent, "best-found fixture never exposed a P02-validated upper before proof completion");

  const auto completed_advance = advance_to_search_completion(strict);
  check(completed_advance.progress.result == planner::ResultKind::verified_optimum &&
        completed_advance.progress.proof_complete && completed_advance.progress.heights.lower == 2 &&
        completed_advance.progress.heights.upper == 2 && !strict.incumbent() &&
        strict.optimum() && strict.optimum()->valid(),
        "strict search did not finish with verified height two and no incumbent handle");
  const auto completed_progress = io::write_search_progress(strict);
  check(completed_progress.at("certificate").is_null() &&
        completed_progress.at("incumbent").is_null() &&
        completed_progress.at("result_kind") == "verified_optimum",
        "completed progress serialized certificate or strict incumbent authority");
  add_record(records, "search_complete", "search-progress-v1.schema.json", completed_progress);

  const auto verified_document = io::write_verified_optimum(*strict.optimum());
  check(verified_document.at("algorithm") == "crown_partition_exact_v2" &&
        verified_document.at("minimum_height") == 2 &&
        verified_document.at("query_binding").at("schema_version") == 1,
        "typed optimum writer did not emit the bound, completed v2 height certificate");
  const auto decoded = io::read_height_certificate(verified_document.dump(), fixture.catalog, fixture.query);
  check(decoded.algorithm == strict.optimum()->certificate().algorithm &&
        decoded.minimum_height == strict.optimum()->certificate().minimum_height &&
        decoded.lower_bounds.size() == strict.optimum()->certificate().lower_bounds.size(),
        "legacy certificate reader did not recover the exact typed optimum certificate");
  add_record(records, "verified_optimum", certificate_schema(verified_document), verified_document);

  auto changed_catalog = fixture.catalog;
  changed_catalog.tables[0].source_schema_version = 2;
  bool binding_rejected = false;
  try {
    static_cast<void>(io::read_height_certificate(verified_document.dump(), changed_catalog, fixture.query));
  } catch (const Error& error) {
    binding_rejected = error.code() == "certificate_binding";
  }
  check(binding_rejected, "completed typed certificate lost exact catalog/query binding");

  reject_legacy_reader(best_upper_document, fixture, "validated upper-bound artifact");
  reject_legacy_reader(strict_admitted, fixture, "search progress");
  reject_legacy_reader(completed_progress, fixture, "completed search progress");

  const auto v1_result = planner::testing::minimum_tree_baseline(fixture.catalog, fixture.query);
  check(v1_result.status == planner::OracleStatus::proven_minimum && v1_result.minimum_height == 2 &&
        v1_result.certificate_verified,
        "private v1 fixture did not produce its completed baseline certificate");
  const auto v1_certificate = planner::HeightCertificate{
      v1_result.algorithm, v1_result.minimum_height, v1_result.tree, v1_result.lower_bounds};
  const auto v2_certificate = strict.optimum()->certificate();

  auto emit_replay = [&](const std::string& version, const planner::HeightCertificate& certificate,
                         bool corrupt) {
    planner::ReplayOptions replay_options;
    replay_options.limits.work = corrupt ? 10'000'000 : 32;
    replay_options.limits.active_time.reset();
    replay_options.logical_depth = 512;
    auto replay = planner::CertificateReplay::create(
        fixture.catalog, fixture.query, corrupt ? planner::HeightCertificate{
            "not-a-certificate-algorithm", certificate.minimum_height, certificate.tree,
            certificate.lower_bounds} : certificate,
        replay_options);
    planner::ReplayAdvance paused;
    bool reached_work_ceiling = false;
    if (corrupt) {
      bool failed = false;
      for (std::size_t step = 0; step < 10'000; ++step) {
        const auto advanced = replay.advance(planner::WorkQuantum{4096, {}});
        if (advanced.progress.phase == planner::ReplayPhase::failed) {
          failed = true;
          break;
        }
        check(advanced.stopped_for == planner::StopReason::quantum_work ||
              advanced.stopped_for == planner::StopReason::quantum_time,
              "corrupt replay stopped without rejecting its claim");
      }
      check(failed && !replay.checked(), "corrupt certificate created checked authority");
      add_record(records, "replay_corrupt", "search-progress-v1.schema.json",
                 io::write_replay_progress(replay));
      return;
    }
    for (std::size_t step = 0; step < 10'000; ++step) {
      paused = replay.advance(planner::WorkQuantum{4096, {}});
      if (paused.stopped_for == planner::StopReason::total_work) {
        reached_work_ceiling = true;
        break;
      }
      check(paused.stopped_for == planner::StopReason::quantum_work ||
            paused.stopped_for == planner::StopReason::quantum_time,
            version + ": replay paused unexpectedly");
    }
    check(reached_work_ceiling && !paused.progress.complete && !paused.progress.valid &&
          paused.progress.work.committed_transitions > 1 && !replay.checked(),
          version + ": replay did not suspend after making genuine progress");
    const auto paused_document = io::write_replay_progress(replay);
    check(paused_document.at("certificate").is_null(),
          version + ": paused replay progress exposed a certificate");
    add_record(records, "replay_" + version + "_paused", "search-progress-v1.schema.json", paused_document);

    replay_options.limits.work = 10'000'000;
    check(replay.raise_limits(replay_options) == planner::LimitChange::applied,
          version + ": replay work ceiling could not be extended");
    const auto checked = finish_replay(replay, version);
    check(checked.certificate().algorithm == certificate.algorithm &&
          checked.certificate().minimum_height == 2,
          version + ": resumed replay checked the wrong certificate");
    const auto complete_document = io::write_replay_progress(replay);
    check(complete_document.at("complete") == true && complete_document.at("valid") == true &&
          complete_document.at("certificate").is_null(),
          version + ": completed replay progress exposed a partial certificate");
    add_record(records, "replay_" + version + "_complete", "search-progress-v1.schema.json", complete_document);
  };
  emit_replay("v1", v1_certificate, false);
  emit_replay("v2", v2_certificate, false);
  emit_replay("corrupt", v2_certificate, true);

  const auto replay_progress = io::write_replay_progress(
      planner::CertificateReplay::create(fixture.catalog, fixture.query, v2_certificate));
  reject_legacy_reader(replay_progress, fixture, "certificate replay progress");

  const auto infeasible_fixture = triangle_fixture();
  auto infeasible_search = planner::ExactSearch::create(
      infeasible_fixture.catalog, infeasible_fixture.query, planner::SearchOptions{});
  const auto infeasible_done = advance_to_search_completion(infeasible_search);
  const auto infeasible = infeasible_search.infeasibility();
  check(infeasible_done.progress.result == planner::ResultKind::verified_infeasible &&
        infeasible_done.progress.proof_complete && infeasible && infeasible->valid() &&
        !infeasible_search.optimum(),
        "cyclic full-head query did not produce verified infeasibility authority");
  const auto infeasible_document = io::write_verified_infeasible(*infeasible);
  check(infeasible_document.at("minimum_height").is_null() && infeasible_document.at("tree").is_null(),
        "verified infeasibility did not serialize the standard empty-family certificate");
  const auto decoded_infeasible = io::read_height_certificate(
      infeasible_document.dump(), infeasible_fixture.catalog, infeasible_fixture.query);
  check(!decoded_infeasible.minimum_height && !decoded_infeasible.tree,
        "legacy certificate reader did not preserve the verified empty-family result");
  add_record(records, "verified_infeasible", certificate_schema(infeasible_document), infeasible_document);

  for (const bool metadata : {false, true}) {
    const auto typed = date_fixture(metadata);
    auto date_search = planner::ExactSearch::create(typed.catalog, typed.query);
    const auto date_done = advance_to_search_completion(date_search);
    const auto date_optimum = date_search.optimum();
    check(date_done.progress.result == planner::ResultKind::verified_optimum && date_optimum &&
          date_optimum->valid() && date_optimum->height() == 1,
          "date binding fixture did not complete with a typed optimum");
    const auto document = io::write_verified_optimum(*date_optimum);
    const auto expected_version = metadata ? 3 : 2;
    check(document.at("query_binding").at("schema_version") == expected_version &&
          document.dump().find("2024-02-29") != std::string::npos,
          "typed certificate did not retain date or expected Cq binding version");
    const auto date_decoded = io::read_height_certificate(document.dump(), typed.catalog, typed.query);
    check(date_decoded.minimum_height == 1,
          "date-format certificate did not bind and decode against its exact inputs");
    add_record(records, metadata ? "metadata_v3_optimum" : "date_v2_optimum",
               certificate_schema(document), document);
  }

  // Typed writers have no overload or public conversion that can turn an
  // upper-bound-only artifact into proof authority.
  static_assert(!std::is_convertible_v<planner::ValidatedIncumbent, planner::VerifiedOptimum>);
  static_assert(!std::is_invocable_v<decltype(&io::write_verified_optimum),
                                    const planner::ValidatedIncumbent&>);
  return records;
}

}  // namespace

int main(int argc, char** argv) {
  try {
    const auto records = build_records();
    if (argc == 2 && std::string_view(argv[1]) == "--emit") {
      std::cout << io::Json(records).dump() << '\n';
      return 0;
    }
    check(argc == 1, "usage: crown_planner_progress_test [--emit]");
    check(!records.empty(), "progress fixture produced no artifacts");
    std::cout << "typed planner progress and certificate IO assertions passed\n";
    return 0;
  } catch (const std::exception& error) {
    std::cerr << error.what() << '\n';
    return 1;
  }
}
