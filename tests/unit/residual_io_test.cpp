#include "crown/api/error.hpp"
#include "crown/io/residual.hpp"

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

Fixture residual_fixture() {
  Fixture fixture;
  fixture.catalog.tables = {
      Table{"R", {{"x", ScalarType::int64}, {"y", ScalarType::int64}, {"z", ScalarType::int64},
                   {"r", ScalarType::int64}, {"day", ScalarType::date}, {"label", ScalarType::string},
                   {"amount", ScalarType::decimal}, {"ignored", ScalarType::string}}},
      Table{"S", {{"x", ScalarType::int64}, {"y", ScalarType::int64}, {"z", ScalarType::int64}, {"s", ScalarType::int64}}},
      Table{"L", {{"r", ScalarType::int64}}},
      Table{"V", {{"s", ScalarType::int64}}},
      Table{"T", {{"y", ScalarType::int64}, {"b", ScalarType::int64}}},
      Table{"B", {{"b", ScalarType::int64}}},
      Table{"E", {{"x", ScalarType::int64}, {"w", ScalarType::int64}}},
  };
  fixture.query.variables = {
      {"x", ScalarType::int64}, {"y", ScalarType::int64}, {"z", ScalarType::int64},
      {"r", ScalarType::int64}, {"s", ScalarType::int64}, {"b", ScalarType::int64},
      {"w", ScalarType::int64},
  };
  fixture.query.atoms = {
      {"R0", TableId{0}, {VariableId{0}, VariableId{1}, VariableId{2}, VariableId{3},
                           Value{Date::parse("2024-02-29")}, Value{std::string("snow")},
                           Value{Decimal::parse("12.50")}, IgnoredColumn{}}},
      {"S0", TableId{1}, {VariableId{0}, VariableId{1}, VariableId{2}, VariableId{4}}},
      {"L0", TableId{2}, {VariableId{3}}},
      {"V0", TableId{3}, {VariableId{4}}},
      {"T0", TableId{4}, {VariableId{1}, VariableId{5}}},
      {"B0", TableId{5}, {VariableId{5}}},
      {"E0", TableId{6}, {VariableId{0}, VariableId{6}}},
  };
  fixture.query.head = {{VariableId{0}, "first_x"}, {VariableId{0}, "again_x"},
                        {VariableId{1}, "y"}, {VariableId{6}, "w"}};
  fixture.query.contradiction = true;
  return fixture;
}

Fixture optimum_fixture() {
  Fixture fixture;
  fixture.catalog.tables = {
      Table{"R", {{"x", ScalarType::int64}, {"y", ScalarType::int64}}},
      Table{"S", {{"y", ScalarType::int64}}},
  };
  fixture.query.variables = {{"x", ScalarType::int64}, {"y", ScalarType::int64}};
  fixture.query.atoms = {
      {"r", TableId{0}, {VariableId{0}, VariableId{1}}},
      {"s", TableId{1}, {VariableId{1}}},
  };
  fixture.query.head = {{VariableId{0}, "x"}};
  return fixture;
}

Fixture infeasible_fixture() {
  Fixture fixture;
  for (std::size_t table = 0; table < 3; ++table) {
    fixture.catalog.tables.push_back(Table{"T" + std::to_string(table),
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

planner::ResidualOptions options(planner::ResidualMode mode) {
  planner::ResidualOptions value;
  value.mode = mode;
  value.limits.residual.work = 50'000'000;
  value.limits.residual.active_time.reset();
  value.limits.logical_depth = 1024;
  value.limits.record_limit = 1'000'000;
  value.limits.cell_limit = 10'000'000;
  value.limits.exact.producer.work = 50'000'000;
  value.limits.exact.producer.active_time.reset();
  value.limits.exact.replay.work = 50'000'000;
  value.limits.exact.replay.active_time.reset();
  value.limits.exact.logical_depth = 1024;
  return value;
}

void advance_to_trace(planner::ResidualSearch& owner, const std::string& label) {
  for (std::size_t step = 0; step < 1'000'000; ++step) {
    const auto update = owner.advance({1'000'000, {}});
    check(update.progress.result != planner::ResidualResult::failed,
          label + ": provider failed before publishing its checked trace");
    if (owner.trace()) return;
    check(update.stopped_for == planner::ResidualStopReason::quantum_work ||
              update.stopped_for == planner::ResidualStopReason::quantum_time,
          label + ": provider stopped unexpectedly before its trace was published");
  }
  throw std::runtime_error(label + ": trace publication exceeded the transition guard");
}

void finish(planner::ResidualSearch& owner, const std::string& label) {
  for (std::size_t step = 0; step < 5'000'000; ++step) {
    const auto update = owner.advance({4096, {}});
    check(update.progress.result != planner::ResidualResult::failed,
          label + ": provider failed before completion");
    if (update.progress.result != planner::ResidualResult::unfinished) {
      check(update.stopped_for == planner::ResidualStopReason::complete,
            label + ": terminal result did not report complete");
      return;
    }
    check(update.stopped_for == planner::ResidualStopReason::quantum_work ||
              update.stopped_for == planner::ResidualStopReason::quantum_time,
          label + ": provider stopped for a resource ceiling");
  }
  throw std::runtime_error(label + ": completion exceeded the transition guard");
}

using Records = std::vector<io::Json>;

void add_record(Records& records, std::string name, std::string schema, io::Json document) {
  records.push_back({{"name", std::move(name)}, {"schema", std::move(schema)},
                     {"document", std::move(document)}});
}

Records build_records() {
  static_assert(!std::is_default_constructible_v<planner::ResidualTrace>);
  static_assert(!std::is_default_constructible_v<planner::ResidualCandidate>);
  static_assert(!std::is_convertible_v<planner::ResidualCandidate, planner::VerifiedOptimum>);
  static_assert(!std::is_invocable_v<decltype(&io::write_verified_optimum),
                                      const planner::ResidualCandidate&>);
  static_assert(!std::is_invocable_v<decltype(&io::write_residual_progress),
                                      const planner::ResidualProgress&>);

  Records records;

  const auto residual = residual_fixture();
  auto candidate_owner = planner::ResidualSearch::create(
      residual.catalog, residual.query,
      options(planner::ResidualMode::candidates_with_exact_repair));
  advance_to_trace(candidate_owner, "candidate fixture");
  const auto checked_trace = candidate_owner.trace();
  check(checked_trace && checked_trace->valid(), "candidate fixture did not expose its immutable trace handle");
  const auto trace = io::write_residual_trace(*checked_trace);
  const auto& native_trace = checked_trace->record();
  check(trace.at("artifact") == "residual_trace" &&
            trace.at("audit_scope") == "frozen_residual_trace_only" &&
            trace.at("query_binding").at("schema_version") == 2 &&
            trace.at("query_binding").at("query").at("atoms").size() == residual.query.atoms.size(),
        "trace artifact lost its original query binding or overstated its audit scope");
  check(trace.at("original_scopes").size() == native_trace.original_scopes.size() &&
            trace.at("layers").size() == native_trace.layers.size() &&
            trace.at("terminal") == "hierarchical" &&
            trace.at("terminal_members").size() == native_trace.terminal_members.size(),
        "trace artifact omitted original scopes, frozen rounds or terminal membership");
  check(!native_trace.layers.empty() && !native_trace.layers.front().ears.empty() &&
            !native_trace.layers.front().deletions.empty(),
        "fixture must exercise typed ears, anchors and deterministic deletion records");
  const auto& local = native_trace.terminal_view;
  check(trace.at("terminal_view").at("original_occurrences").size() == local.original_occurrences.size() &&
            trace.at("terminal_view").at("original_variables").size() == local.original_variables.size() &&
            trace.at("terminal_view").at("occurrence_to_local").size() == local.occurrence_to_local.size() &&
            trace.at("terminal_view").at("variable_to_local").size() == local.variable_to_local.size(),
        "trace artifact lost one of the dense terminal-view maps");
  check(trace.at("terminal_view").at("query").at("contradiction") == residual.query.contradiction &&
            trace.at("terminal_view").at("query").at("head").size() == local.query.head.size() &&
            trace.at("terminal_view").at("query").at("variables").size() == local.query.variables.size() &&
            trace.dump().find("2024-02-29") != std::string::npos &&
            trace.dump().find("again_x") != std::string::npos,
        "terminal dense query lost typed literals, contradiction or ordered head aliases");
  add_record(records, "residual_trace", "residual-report-v1.schema.json", trace);

  auto admitted_owner = planner::ResidualSearch::create(
      optimum_fixture().catalog, optimum_fixture().query,
      options(planner::ResidualMode::candidates_with_exact_repair));
  const auto admitted_document = io::write_residual_progress(admitted_owner);
  check(admitted_document.at("phase") == "admitted" && admitted_document.at("certificate").is_null(),
        "admitted progress exposed result authority");
  add_record(records, "admitted", "residual-report-v1.schema.json", admitted_document);

  finish(candidate_owner, "candidate fixture");
  const auto candidate_progress = candidate_owner.progress();
  auto candidate_handle = candidate_owner.candidate();
  check(candidate_progress.result == planner::ResidualResult::checked_candidate &&
            candidate_progress.proof_status == planner::ResidualProofStatus::checked_upper_only &&
            !candidate_owner.exact_original() && !candidate_owner.infeasibility() && candidate_handle,
        "candidate fixture did not complete with upper-bound-only authority");
  const auto candidate = io::write_residual_candidate(*candidate_handle);
  check(candidate.at("proof_status") == "checked_upper_only" &&
            candidate.at("height_status") == "valid_upper_bound" &&
            candidate.at("height_upper_bound") == candidate_handle->height() &&
            candidate.at("certificate").is_null() && !candidate.contains("minimum_height") &&
            !candidate.contains("height_lower_bound"),
        "candidate artifact claimed anything beyond a checked upper bound");
  add_record(records, "candidate_upper", "residual-report-v1.schema.json", candidate);

  const auto candidate_progress_document = io::write_residual_progress(candidate_owner);
  check(candidate_progress_document.at("proof_status") == "checked_upper_only" &&
            candidate_progress_document.at("height_upper_bound") == candidate_handle->height() &&
            candidate_progress_document.at("lower_evidence") == "universal" &&
            candidate_progress_document.at("exact_scope_original") == false &&
            candidate_progress_document.at("exact_diagnostic").at("scope_original") == false &&
            candidate_progress_document.at("certificate").is_null() &&
            candidate_progress_document.at("trace").is_object(),
        "candidate progress confused a residual exact diagnostic with original-query evidence");
  check(candidate_progress_document.at("height_lower_bound") !=
            candidate_progress_document.at("statistics").at("rounds").get<std::uint64_t>() + 1,
        "residual rounds were serialized as an original-query lower bound");
  add_record(records, "candidate_progress", "residual-report-v1.schema.json", candidate_progress_document);

  auto moved_candidate = std::move(*candidate_handle);
  auto moved_candidate_target = std::move(moved_candidate);
  static_cast<void>(moved_candidate_target);
  bool invalid_candidate_rejected = false;
  try {
    static_cast<void>(io::write_residual_candidate(moved_candidate));
  } catch (const Error& error) {
    invalid_candidate_rejected = error.code() == "invalid_residual_handle";
  }
  check(invalid_candidate_rejected, "candidate writer accepted a moved-from immutable handle");

  const auto optimum = optimum_fixture();
  auto exact_owner = planner::ResidualSearch::create(
      optimum.catalog, optimum.query,
      options(planner::ResidualMode::require_exact_original));
  const auto pending = exact_owner.advance({1, {}});
  check(pending.progress.result == planner::ResidualResult::unfinished &&
            !exact_owner.exact_original() && !exact_owner.infeasibility(),
        "unit residual quantum unexpectedly published original-query authority");
  const auto pending_document = io::write_residual_progress(exact_owner);
  check(pending_document.at("certificate").is_null() &&
            pending_document.at("proof_status") != "exact_original_verified",
        "unfinished original search serialized a certificate");
  add_record(records, "exact_original_pending", "residual-report-v1.schema.json", pending_document);

  finish(exact_owner, "exact optimum fixture");
  const auto verified_optimum = exact_owner.exact_original();
  check(verified_optimum && verified_optimum->valid(),
        "exact-required fixture did not publish immutable original-query authority");
  const auto exact_progress_document = io::write_residual_progress(exact_owner);
  const auto optimum_certificate = io::write_verified_optimum(*verified_optimum);
  check(exact_progress_document.at("result") == "verified_optimum" &&
            exact_progress_document.at("proof_status") == "exact_original_verified" &&
            exact_progress_document.at("exact_scope_original") == true &&
            exact_progress_document.at("certificate") == optimum_certificate &&
            exact_progress_document.at("height_lower_bound") == verified_optimum->height() &&
            exact_progress_document.at("height_upper_bound") == verified_optimum->height(),
        "only completed exact-original authority may carry the verified minimum certificate");
  add_record(records, "exact_original_progress", "residual-report-v1.schema.json", exact_progress_document);
  add_record(records, "verified_optimum", "height-certificate-v2.schema.json", optimum_certificate);

  auto metadata_fixture = optimum_fixture();
  metadata_fixture.catalog.tables[0].source_schema_version = 2;
  auto metadata_owner = planner::ResidualSearch::create(
      metadata_fixture.catalog, metadata_fixture.query,
      options(planner::ResidualMode::require_exact_original));
  finish(metadata_owner, "metadata exact fixture");
  const auto metadata_progress_document = io::write_residual_progress(metadata_owner);
  check(metadata_progress_document.at("query_binding").at("schema_version") == 3 &&
            metadata_progress_document.at("certificate").at("query_binding").at("schema_version") == 3,
        "metadata/source binding did not retain direct-CQ format v3");
  add_record(records, "metadata_v3_progress", "residual-report-v1.schema.json", metadata_progress_document);

  const auto upper = exact_owner.candidate();
  check(upper.has_value(), "exact optimum fixture did not retain its checked upper witness");
  const auto upper_document = io::write_residual_candidate(*upper);
  check(upper_document.at("proof_status") == "checked_upper_only" &&
            upper_document.at("certificate").is_null() &&
            !upper_document.contains("minimum_height"),
        "standalone candidate changed into a minimum certificate after exact search completion");
  add_record(records, "candidate_after_exact", "residual-report-v1.schema.json", upper_document);

  const auto impossible = infeasible_fixture();
  auto infeasible_owner = planner::ResidualSearch::create(
      impossible.catalog, impossible.query,
      options(planner::ResidualMode::require_exact_original));
  finish(infeasible_owner, "exact infeasibility fixture");
  const auto verified_infeasible = infeasible_owner.infeasibility();
  check(verified_infeasible && verified_infeasible->valid() && !infeasible_owner.exact_original(),
        "exact-required cyclic fixture did not publish typed infeasibility authority");
  const auto infeasible_progress_document = io::write_residual_progress(infeasible_owner);
  const auto infeasible_certificate = io::write_verified_infeasible(*verified_infeasible);
  check(infeasible_progress_document.at("result") == "verified_infeasible" &&
            infeasible_progress_document.at("proof_status") == "exact_original_verified" &&
            infeasible_progress_document.at("exact_scope_original") == true &&
            infeasible_progress_document.at("height_lower_bound").is_null() &&
            infeasible_progress_document.at("height_upper_bound").is_null() &&
            infeasible_progress_document.at("infeasible") == true &&
            infeasible_progress_document.at("certificate") == infeasible_certificate,
        "verified infeasibility was not bound to completed original-query proof authority");
  add_record(records, "exact_infeasible_progress", "residual-report-v1.schema.json", infeasible_progress_document);
  add_record(records, "verified_infeasible", "height-certificate-v2.schema.json", infeasible_certificate);

  auto cancelled_owner = planner::ResidualSearch::create(
      optimum.catalog, optimum.query,
      options(planner::ResidualMode::require_exact_original));
  static_cast<void>(cancelled_owner.advance({1, {}}));
  cancelled_owner.cancel();
  const auto cancelled_document = io::write_residual_progress(cancelled_owner);
  check(cancelled_document.at("phase") == "cancelled" &&
            cancelled_document.at("certificate").is_null(),
        "cancelled progress exposed completed proof authority");
  add_record(records, "cancelled", "residual-report-v1.schema.json", cancelled_document);

  auto moved_trace_owner = planner::ResidualSearch::create(
      residual.catalog, residual.query,
      options(planner::ResidualMode::candidates_with_exact_repair));
  advance_to_trace(moved_trace_owner, "moved trace fixture");
  auto trace_handle = moved_trace_owner.trace();
  check(trace_handle.has_value(), "moved trace fixture did not publish its trace");
  auto moved_trace = std::move(*trace_handle);
  const auto moved_from_trace = std::move(moved_trace);
  static_cast<void>(moved_from_trace);
  bool invalid_trace_rejected = false;
  try {
    static_cast<void>(io::write_residual_trace(moved_trace));
  } catch (const Error& error) {
    invalid_trace_rejected = error.code() == "invalid_residual_handle";
  }
  check(invalid_trace_rejected, "trace writer accepted a moved-from immutable handle");

  auto moved_owner = planner::ResidualSearch::create(
      optimum.catalog, optimum.query,
      options(planner::ResidualMode::require_exact_original));
  auto moved_owner_target = std::move(moved_owner);
  static_cast<void>(moved_owner_target);
  bool moved_owner_rejected = false;
  try {
    static_cast<void>(io::write_residual_progress(moved_owner));
  } catch (const Error& error) {
    moved_owner_rejected = error.code() == "invalid_residual_handle";
  }
  check(moved_owner_rejected, "progress writer did not follow moved-from owner IO behavior");

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
    check(argc == 1, "usage: crown_residual_io_test [--emit]");
    check(!records.empty(), "residual IO fixture emitted no artifacts");
    std::cout << "typed residual trace, candidate and progress IO assertions passed\n";
    return 0;
  } catch (const std::exception& error) {
    std::cerr << error.what() << '\n';
    return 1;
  }
}
