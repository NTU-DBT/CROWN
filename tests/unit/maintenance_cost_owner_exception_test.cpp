// Persistent allocation failures for public cost::capture and cost::estimate.
#include "ranking_fixture.hpp"
#include "indexed_runtime_fixture.hpp"
#include "crown/resource/memory.hpp"
#include "crown/runtime/maintenance_cost.hpp"
#include "crown/storage/tuple_values.hpp"

#include <array>
#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <iostream>
#include <new>
#include <optional>
#include <stdexcept>
#include <string>
#include <string_view>
#include <tuple>
#include <utility>
#include <vector>

namespace c03_owner_fault {
thread_local std::ptrdiff_t fail_after = -1;
thread_local std::size_t allocations = 0;
thread_local bool triggered = false;

[[gnu::noinline]] void* allocate(std::size_t bytes) {
  ++allocations;
  // Keep failing every later allocation after the selected position.
  if (fail_after == 0) {
    triggered = true;
    throw std::bad_alloc{};
  }
  if (fail_after > 0) --fail_after;
  if (void* pointer = std::malloc(bytes ? bytes : 1)) return pointer;
  throw std::bad_alloc{};
}

struct Fault {
  explicit Fault(std::size_t position) {
    allocations = 0;
    triggered = false;
    fail_after = static_cast<std::ptrdiff_t>(position);
  }
  ~Fault() { fail_after = -1; }
  Fault(const Fault&) = delete;
  Fault& operator=(const Fault&) = delete;
};
}  // namespace c03_owner_fault

void* operator new(std::size_t bytes) { return c03_owner_fault::allocate(bytes); }
void* operator new[](std::size_t bytes) { return c03_owner_fault::allocate(bytes); }
void* operator new(std::size_t bytes, const std::nothrow_t&) noexcept {
  try { return c03_owner_fault::allocate(bytes); } catch (...) { return nullptr; }
}
void* operator new[](std::size_t bytes, const std::nothrow_t&) noexcept {
  try { return c03_owner_fault::allocate(bytes); } catch (...) { return nullptr; }
}
void operator delete(void* pointer) noexcept { std::free(pointer); }
void operator delete[](void* pointer) noexcept { std::free(pointer); }
void operator delete(void* pointer, std::size_t) noexcept { std::free(pointer); }
void operator delete[](void* pointer, std::size_t) noexcept { std::free(pointer); }
void operator delete(void* pointer, const std::nothrow_t&) noexcept { std::free(pointer); }
void operator delete[](void* pointer, const std::nothrow_t&) noexcept { std::free(pointer); }

namespace {
using namespace c02_test;
namespace model = crown::runtime::cost;
namespace pr = crown::planner::ranking;
namespace ws = crown::runtime::workload;
namespace stats = crown::runtime::statistics;
using Account = crown::resource::MemoryAccount;
using Profile = model::Profile;
using Result = model::Result;

void check(bool condition, std::string_view message) {
  if (!condition) throw std::runtime_error(std::string(message));
}

auto stamp_image(const ws::Stamp& value) {
  return std::tuple{value.owner.value, value.committed_epoch, value.interval_start_epoch,
      value.reset_generation, value.configuration_generation, value.segment, value.format_version,
      value.reset_saturated, value.configuration_saturated, value.segment_saturated};
}
auto metadata_image(const ws::Metadata& value) {
  return std::tuple{value.attempts, value.committed, value.aborted, value.selected, value.complete,
      value.aborted_selected, value.truncated, value.committed_truncated, value.guards,
      value.detail_actions, value.cleared_cells, value.merged_cells, value.saturated,
      value.invalid_descriptor, value.protocol_error, value.ordinal_exhausted};
}
auto workload_memory_image(const ws::Memory& value) {
  return std::tuple{value.object_bytes, value.descriptors_bytes, value.committed_bytes,
      value.attempt_bytes, value.previous_bytes, value.retained_payload_bytes, value.routes_bytes};
}
auto owner_usage_image(const stats::Usage& value) {
  return std::tuple{value.work, value.rows, value.distinct_keys, value.accounted_bytes,
      value.max_row_capacity, value.max_histogram_capacity, value.max_heavy_capacity};
}
auto owner_limits_image(const stats::Limits& value) {
  return std::tuple{value.work, value.rows, value.distinct_keys, value.accounted_bytes,
      value.projection_width, value.heavy_keys};
}
auto ranking_usage_image(const pr::Usage& value) {
  return std::tuple{value.work, value.cells, value.binding_key_bytes, value.payload_bytes,
      value.lowering_work, value.identity_work, value.binding_replay_work,
      value.normalization_work, value.active_nanoseconds};
}
auto ranking_limits_image(const pr::Limits& value) {
  const std::optional<std::int64_t> time = value.active_time
      ? std::optional<std::int64_t>{value.active_time->count()} : std::nullopt;
  return std::tuple{value.work, value.cells, value.binding_key_bytes, value.payload_bytes,
      value.lowering_work, value.identity_work, value.binding_replay_work,
      value.normalization_work, value.candidates, value.score_bits, time};
}
auto mode_identity_image(const pr::ModeIdentity& value) {
  return std::tuple{value.delta_owner, value.requested_mode, value.resolved_mode,
      value.requested_completion, value.resolved_completion, value.live_maintenance, value.view};
}
auto evidence_identity_image(const pr::EvidenceIdentity& value) {
  return std::tuple{value.owner, value.epoch, value.interval_start, value.reset,
      value.configuration, value.segment, value.format, value.collection_mode,
      value.max_cells, value.period, value.offset, value.detail_budget,
      mode_identity_image(value.modes), value.pending, value.reset_saturated,
      value.configuration_saturated, value.segment_saturated};
}
auto capture_accounting_image(const pr::CaptureAccounting& value) {
  return std::tuple{ranking_limits_image(value.processing_limits), value.state,
      value.state_requested, value.requested_components, value.returned_components,
      value.state_work_limit, value.state_rows_limit, value.state_keys_limit,
      value.state_bytes_limit, value.state_projection_width, value.state_heavy_keys,
      value.state_work, value.state_rows, value.state_keys, value.state_bytes,
      value.snapshot_descriptors, value.snapshot_cells};
}
auto owner_stamp_image(const stats::OwnerStamp& value) {
  return std::tuple{value.owner.value, value.sequence, value.layer};
}

struct WorkloadImage {
  std::string physical_hash;
  decltype(stamp_image(std::declval<const ws::Stamp&>())) stamp;
  ws::Options options;
  ws::ModeFacts modes, previous_modes;
  std::vector<ws::Descriptor> descriptors;
  std::vector<ws::Cell> cells, previous_cells;
  decltype(metadata_image(std::declval<const ws::Metadata&>())) metadata, previous_metadata;
  decltype(workload_memory_image(std::declval<const ws::Memory&>())) memory;
  bool pending{}, has_previous{}, replaced{};
  std::uint64_t previous_start{}, previous_end{};
  ws::Availability detail_availability{};
  bool operator==(const WorkloadImage&) const = default;
};

WorkloadImage workload_image(const ws::Snapshot& value) {
  const auto descriptors = value.descriptors();
  const auto cells = value.cells();
  const auto previous = value.previous_cells();
  return {std::string(value.plan().physical_sha256()), stamp_image(value.stamp()), value.options(),
      value.modes(), value.previous_modes(), {descriptors.begin(), descriptors.end()},
      {cells.begin(), cells.end()}, {previous.begin(), previous.end()},
      metadata_image(value.metadata()), metadata_image(value.previous_metadata()),
      workload_memory_image(value.memory()), value.pending(), value.has_previous(),
      value.replaced_history(), value.previous_interval_start_epoch(),
      value.previous_interval_end_epoch(), value.detail_availability()};
}

struct OwnerImage {
  std::string physical_hash;
  decltype(owner_stamp_image(std::declval<const stats::OwnerStamp&>())) stamp;
  stats::Availability availability{}, physical_source_scope{};
  decltype(owner_usage_image(std::declval<const stats::Usage&>())) usage;
  decltype(owner_limits_image(std::declval<const stats::Limits&>())) limits;
  std::size_t requested_components{}, component_count{};
  bool operator==(const OwnerImage&) const = default;
};

struct InputWeightImage {
  std::size_t table{};
  std::uint64_t inserts{}, erases{}, changed{}, noop{};
  bool operator==(const InputWeightImage&) const = default;
};
struct SourceObservationImage {
  std::size_t table{};
  pr::CaptureState state{};
  std::optional<std::uint64_t> cardinality;
  bool operator==(const SourceObservationImage&) const = default;
};
struct SourceCardinalityImage {
  std::size_t table{};
  std::uint64_t rows{};
  bool operator==(const SourceCardinalityImage&) const = default;
};
struct EvidenceImage {
  std::string physical_hash;
  std::vector<InputWeightImage> weights;
  std::vector<SourceObservationImage> source_observations;
  std::vector<SourceCardinalityImage> sources;
  decltype(evidence_identity_image(std::declval<const pr::EvidenceIdentity&>())) identity;
  decltype(capture_accounting_image(std::declval<const pr::CaptureAccounting&>())) accounting;
  pr::Reasons depth_reasons{}, memory_reasons{};
  std::uint64_t denominator{};
  decltype(ranking_usage_image(std::declval<const pr::Usage&>())) preparation_usage;
  OwnerImage owner;
  WorkloadImage workload;
  bool has_session_context{};
  bool operator==(const EvidenceImage&) const = default;
};

struct CandidateContextImage {
  planner::CandidateUpdateProfile updates{};
  std::string arithmetic, planner, optimization, cost_model, canonicalization;
  bool operator==(const CandidateContextImage&) const = default;
};
struct CandidateImage {
  std::string structural_key;
  std::size_t height{};
  CandidateContextImage context;
  planner::CandidateSource source{};
  planner::CandidateFamily family{};
  std::uint64_t provenance_sequence{};
  bool operator==(const CandidateImage&) const = default;
};
struct ProfileImage {
  CandidateImage candidate;
  EvidenceImage evidence;
  crown::resource::MemoryStatistics memory;
  bool operator==(const ProfileImage&) const = default;
};

auto limits_image(const stats::Limits& value) { return owner_limits_image(value); }

OwnerImage owner_image(const stats::OwnerCapture& value) {
  // cost::capture requests no source-state components; preserve that explicit
  // shape so an unexpected partial component set cannot be silently ignored.
  check(value.components().empty(), "cost::capture unexpectedly returned state components");
  return {std::string(value.plan().physical_sha256()), owner_stamp_image(value.stamp()),
      value.availability(), value.physical_source_scope(), owner_usage_image(value.usage()),
      limits_image(value.limits()), value.requested_components(), value.components().size()};
}

EvidenceImage evidence_image(const runtime::ranking::RuntimeEvidence& value) {
  const auto& inputs = value.inputs();
  const auto& captured = value.captured();
  check(!value.session_context(),
      "PhysicalRuntime cost profile unexpectedly retained QuerySession context");
  check(captured.has_value(), "physical cost profile lost its combined capture");
  const auto& state = captured->state();
  const auto& workload = captured->workload();
  std::vector<InputWeightImage> weights;
  for (const auto& item : inputs.weights())
    weights.push_back({item.table.value, item.inserts, item.erases, item.changed, item.noop});
  std::vector<SourceObservationImage> observations;
  for (const auto& item : inputs.source_observations())
    observations.push_back({item.table.value, item.state, item.cardinality});
  std::vector<SourceCardinalityImage> sources;
  for (const auto& item : inputs.sources()) sources.push_back({item.table.value, item.rows});
  return {std::string(inputs.plan().physical_sha256()), std::move(weights),
      std::move(observations), std::move(sources), evidence_identity_image(inputs.identity()),
      capture_accounting_image(inputs.capture_accounting()), inputs.depth_reasons(),
      inputs.memory_reasons(), inputs.denominator(), ranking_usage_image(inputs.preparation_usage()),
      owner_image(state), workload_image(workload), value.session_context().has_value()};
}

CandidateImage candidate_image(const planner::MinimumHeightCandidate& value) {
  const auto& context = value.context();
  const auto provenance = value.provenance();
  return {value.structural_key(), value.height(),
      {context.updates, context.arithmetic, context.planner, context.optimization,
       context.cost_model, context.canonicalization}, provenance.source, provenance.family,
      provenance.sequence};
}

ProfileImage profile_image(const model::Profile& value) {
  return {candidate_image(value.candidate()), evidence_image(value.evidence()), value.memory_at_capture()};
}

struct CoefficientImage {
  model::Ratio rate;
  std::uint64_t samples{}, units{}, elapsed_ns{};
  bool operator==(const CoefficientImage&) const = default;
};
struct CalibrationImage {
  std::string context, backend;
  std::array<std::optional<CoefficientImage>, model::component_count> coefficients{};
  model::CalibrationOrigin origin{};
  bool has_fit_summary{};
  std::size_t raw_observation_count{};
  bool operator==(const CalibrationImage&) const = default;
};

CalibrationImage calibration_image(const model::Calibration& value) {
  check(!value.fit_summary() && value.fit_observations().empty(),
      "estimate fixture calibration should be isolated, without fitted observations");
  CalibrationImage result{std::string(value.context()), std::string(value.backend()), {},
      value.origin(), value.fit_summary().has_value(), value.fit_observations().size()};
  for (std::size_t i = 0; i < model::component_count; ++i) {
    const auto& coefficient = value.coefficients()[i];
    if (coefficient) result.coefficients[i] = CoefficientImage{coefficient->nanoseconds_per_unit,
        coefficient->samples, coefficient->units, coefficient->elapsed_ns};
  }
  return result;
}

struct ConfidenceImage {
  model::Basis basis{};
  ws::Availability availability{};
  std::uint64_t complete_inputs{}, observed_events{};
  bool operator==(const ConfidenceImage&) const = default;
};
struct TermImage {
  model::Component component{};
  std::optional<std::size_t> descriptor;
  std::optional<model::Ratio> units, nanoseconds;
  ConfidenceImage confidence;
  model::Issues issues{};
  bool operator==(const TermImage&) const = default;
};
struct CandidateEstimateImage {
  CandidateImage candidate;
  std::optional<ProfileImage> observations;
  std::vector<TermImage> terms;
  std::optional<model::Ratio> maintenance_ns, snapshot_ns, delta_ns, encoding_ns,
      checkpoint_ns, annotation_ns, total_ns;
  std::optional<decltype(stamp_image(std::declval<const ws::Stamp&>()))> observed_stamp;
  std::optional<ws::ModeFacts> observed_modes;
  std::uint64_t memory_budget_bytes{};
  std::optional<crown::resource::MemoryStatistics> memory_at_capture;
  bool future_memory_unknown{};
  model::Issues issues{};
  bool operator==(const CandidateEstimateImage&) const = default;
};

CandidateEstimateImage candidate_estimate_image(const model::CandidateEstimate& value) {
  std::optional<ProfileImage> profile;
  if (value.observations) profile = profile_image(*value.observations);
  std::vector<TermImage> terms;
  for (const auto& item : value.terms)
    terms.push_back({item.component, item.descriptor, item.units, item.nanoseconds,
        {item.confidence.basis, item.confidence.availability, item.confidence.complete_inputs,
         item.confidence.observed_events}, item.issues});
  std::optional<decltype(stamp_image(std::declval<const ws::Stamp&>()))> stamp;
  if (value.observed_stamp) stamp = stamp_image(*value.observed_stamp);
  return {candidate_image(value.candidate), std::move(profile), std::move(terms),
      value.maintenance_ns, value.snapshot_ns, value.delta_ns, value.encoding_ns,
      value.checkpoint_ns, value.annotation_ns, value.total_ns, std::move(stamp),
      value.observed_modes, value.memory_budget_bytes, value.memory_at_capture,
      value.future_memory_unknown, value.issues};
}

using InputDemandImage = std::tuple<std::size_t, ws::Operation, std::uint64_t>;
auto output_demand_image(const model::OutputDemand& value) {
  return std::tuple{value.snapshot_requests, value.snapshot_rows_per_request,
      value.delta_epochs, value.delta_rows, value.encoded_bytes, value.checkpoint_requests,
      value.checkpoint_bytes, value.annotation_changes, value.snapshot_rows_total};
}
struct ResultImage {
  CalibrationImage calibration;
  std::vector<CandidateEstimateImage> candidates;
  std::vector<InputDemandImage> input;
  decltype(output_demand_image(std::declval<const model::OutputDemand&>())) output;
  decltype(ranking_usage_image(std::declval<const pr::Usage&>())) usage;
  bool operator==(const ResultImage&) const = default;
};

ResultImage result_image(const model::Result& value) {
  std::vector<CandidateEstimateImage> candidates;
  for (const auto& item : value.candidates()) candidates.push_back(candidate_estimate_image(item));
  std::vector<InputDemandImage> input;
  for (const auto& item : value.input_demand()) input.emplace_back(item.table.value, item.operation, item.inputs);
  return {calibration_image(value.calibration()), std::move(candidates), std::move(input),
      output_demand_image(value.output_demand()), ranking_usage_image(value.usage())};
}

using Relation = crown::Relation;
Relation current_result(const runtime::PhysicalRuntime& owner) {
  Relation result;
  auto cursor = owner.results();
  while (auto tuple = cursor.next()) result.insert(crown::storage::export_row(tuple->values()));
  return result;
}

struct RuntimeImage {
  std::uint64_t sequence{};
  bool ready{}, has_answer{};
  runtime::CanonicalPhysicalState canonical;
  Relation current_result;
  WorkloadImage workload;
  bool operator==(const RuntimeImage&) const = default;
};
RuntimeImage runtime_image(const runtime::PhysicalRuntime& owner) {
  const auto workload = owner.workload_statistics();
  return {owner.sequence(), owner.ready(), owner.has_answer(), owner.canonical_state(),
      current_result(owner), workload_image(workload)};
}

void verify_new_profile(const model::Profile& profile,const ProfileImage& expected,
    const crown::resource::MemoryStatistics& before) {
  auto image=profile_image(profile);
  check(image.memory==before,"new profile did not record actual pre-capture memory statistics");
  auto comparable=expected;comparable.memory=before;
  check(image==comparable,"new profile changed immutable candidate/evidence facts");
}

std::size_t count_capture_allocations(Account& account, const crown::resource::MemoryUsage& baseline,
    const planner::CandidateSnapshot& candidates, std::size_t candidate,
    runtime::PhysicalRuntime& owner, const ProfileImage& expected) {
  c03_owner_fault::allocations = 0;
  const auto memory_before=account.statistics();
  auto counted = model::capture(candidates, candidate, owner);
  const auto count = c03_owner_fault::allocations;
  check(counted.stop == pr::Stop::complete && counted.profile,"successful capture count failed");
  verify_new_profile(*counted.profile,expected,memory_before);
  check(count > 0 && count < 8192, "capture fault sweep allocation count outside guard");
  counted.profile.reset();
  check(account.statistics().current == baseline,
      "allocation-count capture retained a temporary Profile");
  return count;
}

std::size_t sweep_capture(Account& account, const crown::resource::MemoryUsage& baseline,
    const planner::CandidateSnapshot& candidates, std::size_t candidate,
    runtime::PhysicalRuntime& owner, const Profile& retained, const ProfileImage& expected_profile,
    const Result& retained_result, const ResultImage& expected_result, const Account& result_account,
    const crown::resource::MemoryUsage& expected_result_usage, const RuntimeImage& expected_runtime) {
  const auto allocation_count = count_capture_allocations(account, baseline, candidates, candidate,
      owner, expected_profile);
  std::size_t positions = 0;
  for (std::size_t position = 0; position < allocation_count; ++position) {
    const auto before = account.statistics().current;
    model::CaptureAttempt failed;
    std::size_t attempted = 0;
    bool triggered = false;
    {
      c03_owner_fault::Fault fault(position);
      failed = model::capture(candidates, candidate, owner);
      attempted = c03_owner_fault::allocations;
      triggered = c03_owner_fault::triggered;
    }
    check(triggered && attempted >= position + 1, "capture allocation position was not reached");
    check(failed.stop == pr::Stop::allocation_failure && !failed.profile,
        "capture failure returned a partial Profile or wrong stop code");
    check(account.statistics().current == before, "failed capture leaked receiving-account bytes");
    check(account.statistics().current == baseline, "failed capture changed retained Profile account usage");
    check(result_account.statistics().current == expected_result_usage,
        "capture failure changed the independent estimate account");
    check(profile_image(retained) == expected_profile, "earlier successful Profile changed during capture failure");
    check(result_image(retained_result) == expected_result, "earlier successful Result changed during capture failure");
    check(runtime_image(owner) == expected_runtime, "capture failure changed runtime, current result, or workload facts");
    ++positions;
  }
  const auto memory_before=account.statistics();
  auto retry = model::capture(candidates, candidate, owner);
  check(retry.stop == pr::Stop::complete && retry.profile,"unfaulted capture retry failed");
  verify_new_profile(*retry.profile,expected_profile,memory_before);
  retry.profile.reset();
  check(account.statistics().current == baseline, "successful capture retry did not release to retained baseline");
  return positions;
}

std::size_t count_estimate_allocations(Account& account, const crown::resource::MemoryUsage& baseline,
    const planner::CandidateSnapshot& candidates, std::span<const model::Profile> profiles,
    const model::Calibration& calibration, const model::Request& request,
    const ResultImage& expected) {
  c03_owner_fault::allocations = 0;
  auto counted = model::estimate(account, candidates, profiles, calibration, request);
  const auto count = c03_owner_fault::allocations;
  check(counted.stop == pr::Stop::complete && counted.result &&
      result_image(*counted.result) == expected, "successful estimate count differed from baseline result");
  check(count > 0 && count < 16384, "estimate fault sweep allocation count outside guard");
  counted.result.reset();
  check(account.statistics().current == baseline,
      "allocation-count estimate retained a temporary Result");
  return count;
}

std::size_t sweep_estimate(Account& account, const crown::resource::MemoryUsage& baseline,
    const planner::CandidateSnapshot& candidates, std::span<const model::Profile> profiles,
    const model::Calibration& calibration, const model::Request& request,
    const Result& retained, const ResultImage& expected_result,
    const Profile& retained_profile, const ProfileImage& expected_profile,
    const Account& owner_account, const crown::resource::MemoryUsage& expected_owner_usage,
    runtime::PhysicalRuntime& owner, const RuntimeImage& expected_runtime) {
  const auto allocation_count = count_estimate_allocations(account, baseline, candidates, profiles,
      calibration, request, expected_result);
  std::size_t positions = 0;
  for (std::size_t position = 0; position < allocation_count; ++position) {
    const auto before = account.statistics().current;
    model::Attempt failed;
    std::size_t attempted = 0;
    bool triggered = false;
    {
      c03_owner_fault::Fault fault(position);
      failed = model::estimate(account, candidates, profiles, calibration, request);
      attempted = c03_owner_fault::allocations;
      triggered = c03_owner_fault::triggered;
    }
    check(triggered && attempted >= position + 1, "estimate allocation position was not reached");
    check(failed.stop == pr::Stop::allocation_failure && !failed.result,
        "estimate failure returned a partial Result or wrong stop code");
    check(account.statistics().current == before, "failed estimate leaked receiving-account bytes");
    check(account.statistics().current == baseline, "failed estimate changed retained Result account usage");
    check(owner_account.statistics().current == expected_owner_usage,
        "estimate failure changed source Profile account usage");
    check(result_image(retained) == expected_result, "earlier successful Result changed during estimate failure");
    check(profile_image(retained_profile) == expected_profile, "estimate failure changed source Profile");
    check(runtime_image(owner) == expected_runtime, "estimate failure changed runtime, current result, or workload facts");
    ++positions;
  }
  auto retry = model::estimate(account, candidates, profiles, calibration, request);
  check(retry.stop == pr::Stop::complete && retry.result &&
      result_image(*retry.result) == expected_result, "unfaulted estimate retry differed from baseline");
  retry.result.reset();
  check(account.statistics().current == baseline, "successful estimate retry did not release to retained baseline");
  return positions;
}

void run(bool indexed) {
  const auto fixture = c02_test::fixture();
  const auto candidates = c02_test::candidates(fixture);
  std::size_t native = SIZE_MAX;
  for (std::size_t i = 0; i < candidates.candidate_count(); ++i) {
    const auto candidate = candidates.candidate(i);
    check(candidate.has_value(), "fixture candidate missing");
    if (c02_test::shape(candidate->tree()) == 0) native = i;
  }
  check(native != SIZE_MAX, "fixture has no native candidate");
  const auto candidate = *candidates.candidate(native);
  auto plan = planner::lower_tree(fixture.catalog, fixture.query, candidate.tree(),indexed?crown::s04_runtime::options():crown::PhysicalOptions{});
  runtime::PhysicalRuntime owner = runtime::PhysicalRuntime::initialize(plan, fixture.database);
  ws::Options collection;
  collection.mode = ws::Mode::counters;
  owner.configure_workload_statistics(collection);
  static_cast<void>(owner.apply({1, {0}, crown::SetOperation::insert, crown::Row{std::int64_t{2}}}));

  Account owner_account = owner.plan().account();
  auto first_profile = model::capture(candidates, native, owner);
  check(first_profile.stop == pr::Stop::complete && first_profile.profile,
      "baseline real-owner Profile capture failed");
  model::Profile retained_profile = *first_profile.profile;
  first_profile.profile.reset();
  const auto expected_profile = profile_image(retained_profile);
  const auto expected_runtime = runtime_image(owner);
  const auto owner_usage = owner_account.statistics().current;

  Account result_account = Account::create(64U * 1024U * 1024U);
  std::array<model::CalibrationSample, model::component_count> samples{};
  for (std::size_t i = 0; i < samples.size(); ++i)
    samples[i] = {static_cast<model::Component>(i), 1, 1};
  auto calibration_attempt = model::calibrate(result_account, "owner result fault fixture",
      plan.guarantee().storage_backend, samples);
  check(calibration_attempt.stop == pr::Stop::complete && calibration_attempt.calibration,
      "estimate fixture calibration failed");
  model::Calibration calibration = *calibration_attempt.calibration;
  calibration_attempt.calibration.reset();

  std::array<model::InputDemand, 6> demands{{
      {{0}, ws::Operation::insert, 2}, {{0}, ws::Operation::erase, 0},
      {{1}, ws::Operation::insert, 0}, {{1}, ws::Operation::erase, 0},
      {{2}, ws::Operation::insert, 0}, {{2}, ws::Operation::erase, 0}}};
  model::Request request;
  request.input = demands;
  const std::array<model::Profile, 1> profiles{retained_profile};
  auto first_result = model::estimate(result_account, candidates, profiles, calibration, request);
  check(first_result.stop == pr::Stop::complete && first_result.result &&
      first_result.result->candidates().size() == candidates.candidate_count(),
      "baseline owner estimate failed");
  for (std::size_t i = 0; i < candidates.candidate_count(); ++i) {
    const auto& estimate = first_result.result->candidates()[i];
    if (i == native) check(estimate.observations.has_value(), "captured candidate profile missing from estimate");
    else check(!estimate.total_ns &&
        (estimate.issues & model::issue(model::Issue::profile_missing)),
        "uncaptured candidate was not explicitly marked profile_missing");
  }
  model::Result retained_result = *first_result.result;
  first_result.result.reset();
  const auto expected_result = result_image(retained_result);
  const auto result_usage = result_account.statistics().current;
  check(owner_account.statistics().current == owner_usage,
      "estimate changed the source owner account after Profile capture");
  check(runtime_image(owner) == expected_runtime,
      "baseline capture/estimate changed runtime, current result, or complete workload facts");

  const auto capture_positions = sweep_capture(owner_account, owner_usage, candidates, native,
      owner, retained_profile, expected_profile, retained_result, expected_result, result_account,
      result_usage, expected_runtime);
  const auto estimate_positions = sweep_estimate(result_account, result_usage, candidates, profiles,
      calibration, request, retained_result, expected_result, retained_profile, expected_profile,
      owner_account, owner_usage, owner, expected_runtime);
  std::cout << "C03 indexed=" << indexed << " capture allocations=" << capture_positions
            << " estimate allocations=" << estimate_positions << '\n';
}
}  // namespace

int main() {
  try {
    for(bool indexed:{false,true})run(indexed);
  } catch (const std::exception& error) {
    std::cerr << error.what() << '\n';
    return 1;
  }
}
