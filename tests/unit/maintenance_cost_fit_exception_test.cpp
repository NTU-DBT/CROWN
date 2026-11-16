// Persistent allocation failures for the public calibration factories.
#include "crown/resource/memory.hpp"
#include "crown/runtime/maintenance_cost.hpp"

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
#include <utility>

namespace c03_fit_fault {
thread_local std::ptrdiff_t fail_after = -1;
thread_local std::size_t allocations = 0;
thread_local bool triggered = false;

[[gnu::noinline]] void* allocate(std::size_t bytes) {
  ++allocations;
  // Keep failing every later allocation after the selected position. This
  // detects a catch-and-continue path that would otherwise hide partial work.
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
}  // namespace c03_fit_fault

void* operator new(std::size_t bytes) { return c03_fit_fault::allocate(bytes); }
void* operator new[](std::size_t bytes) { return c03_fit_fault::allocate(bytes); }
void* operator new(std::size_t bytes, const std::nothrow_t&) noexcept {
  try { return c03_fit_fault::allocate(bytes); } catch (...) { return nullptr; }
}
void* operator new[](std::size_t bytes, const std::nothrow_t&) noexcept {
  try { return c03_fit_fault::allocate(bytes); } catch (...) { return nullptr; }
}
void operator delete(void* pointer) noexcept { std::free(pointer); }
void operator delete[](void* pointer) noexcept { std::free(pointer); }
void operator delete(void* pointer, std::size_t) noexcept { std::free(pointer); }
void operator delete[](void* pointer, std::size_t) noexcept { std::free(pointer); }
void operator delete(void* pointer, const std::nothrow_t&) noexcept { std::free(pointer); }
void operator delete[](void* pointer, const std::nothrow_t&) noexcept { std::free(pointer); }

namespace {
namespace model = crown::runtime::cost;
namespace pr = crown::planner::ranking;
using Account = crown::resource::MemoryAccount;

void check(bool condition, std::string_view message) {
  if (!condition) throw std::runtime_error(std::string(message));
}

bool same_fit_options(const model::FitOptions& left, const model::FitOptions& right) {
  return left.max_iterations == right.max_iterations &&
      left.relative_tolerance == right.relative_tolerance &&
      left.rank_tolerance == right.rank_tolerance && left.ridge == right.ridge &&
      left.quantization_denominator == right.quantization_denominator && left.modes == right.modes;
}

struct CalibrationImage {
  std::array<std::optional<model::Coefficient>, model::component_count> coefficients{};
  std::optional<model::FitSummary> summary;
  std::array<model::FitObservation, 4> observations{};
  std::size_t observation_count{};
  model::CalibrationOrigin origin{};
  std::string_view context, backend;
};

CalibrationImage image_of(const model::Calibration& value,
    std::string_view context, std::string_view backend) {
  CalibrationImage result;
  result.coefficients = value.coefficients();
  result.summary = value.fit_summary();
  result.origin = value.origin();
  result.context = context;
  result.backend = backend;
  const auto raw = value.fit_observations();
  check(raw.size() <= result.observations.size(), "fixture raw observations exceed image capacity");
  result.observation_count = raw.size();
  for (std::size_t i = 0; i < raw.size(); ++i) result.observations[i] = raw[i];
  return result;
}

bool same_calibration(const model::Calibration& value, const CalibrationImage& expected) {
  if (value.context() != expected.context || value.backend() != expected.backend ||
      value.origin() != expected.origin || value.fit_summary().has_value() != expected.summary.has_value())
    return false;
  const auto& coefficients = value.coefficients();
  for (std::size_t i = 0; i < model::component_count; ++i) {
    if (coefficients[i].has_value() != expected.coefficients[i].has_value()) return false;
    if (coefficients[i]) {
      const auto& a = *coefficients[i];
      const auto& b = *expected.coefficients[i];
      if (a.nanoseconds_per_unit != b.nanoseconds_per_unit || a.samples != b.samples ||
          a.units != b.units || a.elapsed_ns != b.elapsed_ns) return false;
    }
  }
  if (value.fit_summary()) {
    const auto& a = *value.fit_summary();
    const auto& b = *expected.summary;
    if (!same_fit_options(a.options, b.options) || a.observations != b.observations ||
        a.observed_features != b.observed_features || a.numerical_rank != b.numerical_rank ||
        a.iterations != b.iterations || a.total_elapsed_ns != b.total_elapsed_ns ||
        a.underdetermined != b.underdetermined ||
        a.root_mean_square_error_ns != b.root_mean_square_error_ns ||
        a.maximum_absolute_error_ns != b.maximum_absolute_error_ns) return false;
  }
  const auto raw = value.fit_observations();
  if (raw.size() != expected.observation_count) return false;
  for (std::size_t i = 0; i < raw.size(); ++i) {
    if (raw[i].units != expected.observations[i].units ||
        raw[i].elapsed_ns != expected.observations[i].elapsed_ns) return false;
  }
  return true;
}

template <class Invoke, class Verify>
std::size_t count_successful_allocations(const Account& account,
    const crown::resource::MemoryUsage& retained_usage, Invoke invoke, Verify verify) {
  c03_fit_fault::allocations = 0;
  auto counted = invoke();
  const auto count = c03_fit_fault::allocations;
  verify(counted);
  check(count > 0 && count < 4096, "calibration fault sweep allocation count outside guard");
  counted.calibration.reset();
  check(account.statistics().current == retained_usage,
      "allocation-count calibration retained a temporary Calibration");
  return count;
}

template <class Invoke, class Verify>
std::size_t sweep(const Account& account, const model::Calibration& retained,
    const CalibrationImage& expected, std::string_view label, Invoke invoke, Verify verify) {
  const auto retained_usage = account.statistics().current;
  const auto allocation_count = count_successful_allocations(account, retained_usage, invoke, verify);
  std::size_t positions = 0;
  for (std::size_t position = 0; position < allocation_count; ++position) {
    const auto before = account.statistics().current;
    model::CalibrationAttempt failed;
    std::size_t attempted_allocations = 0;
    bool triggered = false;
    {
      c03_fit_fault::Fault fault(position);
      failed = invoke();
      attempted_allocations = c03_fit_fault::allocations;
      triggered = c03_fit_fault::triggered;
    }
    check(triggered && attempted_allocations >= position + 1,
        "selected allocation position was not reached");
    check(failed.stop == pr::Stop::allocation_failure && !failed.calibration,
        "allocation failure returned a partial Calibration or wrong stop code");
    check(account.statistics().current == before,
        "failed calibration changed receiving-account current usage");
    check(same_calibration(retained, expected),
        "earlier successful coefficients or raw observations changed during fault sweep");
    ++positions;
  }
  auto retry = invoke();
  verify(retry);
  check(same_calibration(*retry.calibration, expected), "unfaulted retry differs from retained calibration image");
  retry.calibration.reset();
  check(account.statistics().current == retained_usage,
      "retry Calibration did not release back to retained baseline");
  std::cout << label << " allocation positions=" << positions << '\n';
  return positions;
}

std::array<model::FitObservation, 4> fit_observations() {
  std::array<model::FitObservation, 4> result{};
  result[0].units[static_cast<std::size_t>(model::Component::base_input)] = 1;
  result[0].elapsed_ns = 5;
  result[1].units[static_cast<std::size_t>(model::Component::edge_lookup)] = 1;
  result[1].elapsed_ns = 2;
  result[2].units[static_cast<std::size_t>(model::Component::snapshot_row)] = 1;
  result[2].elapsed_ns = 7;
  result[3].units[static_cast<std::size_t>(model::Component::base_input)] = 2;
  result[3].units[static_cast<std::size_t>(model::Component::edge_lookup)] = 3;
  result[3].units[static_cast<std::size_t>(model::Component::snapshot_row)] = 1;
  result[3].elapsed_ns = 23;  // 2*5 + 3*2 + 1*7
  return result;
}

std::array<model::CalibrationSample, 4> isolated_samples() {
  return {{{model::Component::base_input, 2, 4},
           {model::Component::base_input, 4, 8},
           {model::Component::edge_lookup, 3, 15},
           {model::Component::snapshot_row, 2, 14}}};
}

void fit_faults() {
  const auto account = Account::create(64U * 1024U * 1024U);
  const std::string context(80, 'f');
  const std::string backend(72, 'b');  // Both names exceed common SBO capacities.
  const auto observations = fit_observations();
  const auto invoke = [&] { return model::fit(account, context, backend, observations); };
  auto first = invoke();
  check(first.stop == pr::Stop::complete && first.calibration,
      "fit baseline Calibration was not created");
  const model::Calibration retained = *first.calibration;
  first.calibration.reset();
  const auto expected = image_of(retained, context, backend);
  check(retained.origin() == model::CalibrationOrigin::fitted_linear_assumption &&
      retained.fit_summary() && retained.fit_observations().size() == observations.size(),
      "fit baseline omitted summary or raw observations");
  check(retained.fit_summary()->observed_features == 3 && retained.fit_summary()->numerical_rank == 3 &&
      !retained.fit_summary()->underdetermined, "fit baseline did not retain its identifiable rank");
  const auto& coefficients = retained.coefficients();
  check(coefficients[static_cast<std::size_t>(model::Component::base_input)] &&
      coefficients[static_cast<std::size_t>(model::Component::base_input)]->nanoseconds_per_unit == model::Ratio{5, 1},
      "fit baseline base-input rate differs from its literal data");
  check(coefficients[static_cast<std::size_t>(model::Component::edge_lookup)] &&
      coefficients[static_cast<std::size_t>(model::Component::edge_lookup)]->nanoseconds_per_unit == model::Ratio{2, 1},
      "fit baseline edge-lookup rate differs from its literal data");
  check(coefficients[static_cast<std::size_t>(model::Component::snapshot_row)] &&
      coefficients[static_cast<std::size_t>(model::Component::snapshot_row)]->nanoseconds_per_unit == model::Ratio{7, 1},
      "fit baseline snapshot-row rate differs from its literal data");
  for (std::size_t i = 0; i < observations.size(); ++i)
    check(retained.fit_observations()[i].units == observations[i].units &&
        retained.fit_observations()[i].elapsed_ns == observations[i].elapsed_ns,
        "fit baseline raw observation differs from its input");
  const auto verify = [&](const model::CalibrationAttempt& attempt) {
    check(attempt.stop == pr::Stop::complete && attempt.calibration,
        "fit operation did not succeed outside the fault scope");
    check(same_calibration(*attempt.calibration, expected),
        "fit retry changed coefficients, summary, or raw observations");
  };
  static_cast<void>(sweep(account, retained, expected, "fit", invoke, verify));
}

void isolated_calibration_faults() {
  const auto account = Account::create(64U * 1024U * 1024U);
  const std::string context(88, 'c');
  const std::string backend(76, 'k');  // Force both owned strings to allocate.
  const auto samples = isolated_samples();
  const auto invoke = [&] { return model::calibrate(account, context, backend, samples); };
  auto first = invoke();
  check(first.stop == pr::Stop::complete && first.calibration,
      "isolated-calibration baseline was not created");
  const model::Calibration retained = *first.calibration;
  first.calibration.reset();
  const auto expected = image_of(retained, context, backend);
  check(retained.origin() == model::CalibrationOrigin::isolated_measurement_ratios &&
      !retained.fit_summary() && retained.fit_observations().empty(),
      "isolated calibration retained fitted-only fields");
  const auto& coefficients = retained.coefficients();
  const auto base = coefficients[static_cast<std::size_t>(model::Component::base_input)];
  const auto edge = coefficients[static_cast<std::size_t>(model::Component::edge_lookup)];
  const auto snapshot = coefficients[static_cast<std::size_t>(model::Component::snapshot_row)];
  check(base && base->nanoseconds_per_unit == model::Ratio{2, 1} && base->samples == 2 &&
      base->units == 6 && base->elapsed_ns == 12, "isolated base-input coefficient is not literal");
  check(edge && edge->nanoseconds_per_unit == model::Ratio{5, 1} && edge->samples == 1,
      "isolated edge-lookup coefficient is not literal");
  check(snapshot && snapshot->nanoseconds_per_unit == model::Ratio{7, 1} && snapshot->samples == 1,
      "isolated snapshot-row coefficient is not literal");
  const auto verify = [&](const model::CalibrationAttempt& attempt) {
    check(attempt.stop == pr::Stop::complete && attempt.calibration,
        "isolated calibration did not succeed outside the fault scope");
    check(same_calibration(*attempt.calibration, expected),
        "isolated retry changed coefficients or raw calibration state");
  };
  static_cast<void>(sweep(account, retained, expected, "isolated calibrate", invoke, verify));
}
}  // namespace

int main() {
  try {
    fit_faults();
    isolated_calibration_faults();
  } catch (const std::exception& error) {
    std::cerr << error.what() << '\n';
    return 1;
  }
}
