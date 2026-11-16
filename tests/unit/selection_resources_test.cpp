#include "selection_fixture.hpp"
#include "selection_detail.hpp"
#include <array>
#include <iostream>

namespace {
using namespace c05_test; namespace sd = ps::detail;
struct Dimension { std::uint64_t pr::Usage::*used; std::uint64_t pr::Limits::*cap; };
constexpr std::array dimensions{
    Dimension{&pr::Usage::work, &pr::Limits::work}, Dimension{&pr::Usage::cells, &pr::Limits::cells},
    Dimension{&pr::Usage::binding_key_bytes, &pr::Limits::binding_key_bytes},
    Dimension{&pr::Usage::payload_bytes, &pr::Limits::payload_bytes},
    Dimension{&pr::Usage::lowering_work, &pr::Limits::lowering_work},
    Dimension{&pr::Usage::identity_work, &pr::Limits::identity_work},
    Dimension{&pr::Usage::binding_replay_work, &pr::Limits::binding_replay_work},
    Dimension{&pr::Usage::normalization_work, &pr::Limits::normalization_work}};
void same_choice(const ps::Selection& a, const ps::Selection& b) {
  check(a.selected_index() == b.selected_index() && a.selected().structural_key() == b.selected().structural_key() &&
      a.plan().physical_sha256() == b.plan().physical_sha256(), "C05 resource grant changed successful choice");
}
}
int main() { try {
  using namespace c05_test;
  // This private arithmetic fixture tests the aggregate transport equation;
  // it does not manufacture Evidence or claim an actual UINT64_MAX census.
  pr::Limits limits; pr::Usage preparation, total, returned;
  for (const auto& dimension : dimensions) {
    limits.*dimension.cap = UINT64_MAX;
    preparation.*dimension.used = UINT64_MAX - 40;
    total.*dimension.used = UINT64_MAX - 20;
    returned.*dimension.used = UINT64_MAX - 33;
  }
  preparation.active_nanoseconds = 9; total.active_nanoseconds = 9; returned.active_nanoseconds = 9;
  sd::Budget budget(limits, total); const auto delegated = budget.begin_delegate(preparation);
  for (const auto& dimension : dimensions)
    check(delegated.*dimension.cap == UINT64_MAX - 20, "C05 P+(L-U) narrowed or wrapped");
  budget.end_delegate(returned, preparation);
  for (const auto& dimension : dimensions)
    check(budget.usage.*dimension.used == UINT64_MAX - 13, "C05 V-P counted preparation twice");
  check(budget.usage.active_nanoseconds == 9 && !budget.running, "C05 untimed budget measured new time");
  bool overflow = false;
  try { budget.work(14); } catch (const sd::Failure& failure) { overflow = failure.resource == ps::Resource::work; }
  check(overflow && budget.usage.work == UINT64_MAX - 13, "C05 failed addition mutated or wrapped");
  sd::Budget wide(pr::Limits{});
  check(sd::decimal_compare("18446744073709551616", "18446744073709551615", wide) > 0 &&
      sd::decimal_compare("340282366920938463463374607431768211456", "18446744073709551616", wide) > 0 &&
      sd::decimal_compare("340282366920938463463374607431768211456", "340282366920938463463374607431768211456", wide) == 0,
      "C05 canonical comparison narrowed wide exact scores");

  const auto f = c02_test::fixture(); const auto snapshot = c02_test::candidates(f);
  const auto plan = planner::lower_tree(f.catalog, f.query, snapshot.candidate(0)->tree());
  auto owner = runtime::PhysicalRuntime::initialize(plan, f.database); heat(owner, f);
  const auto facts = capture(snapshot, owner).inputs(); const ps::Source source = ps::DirectCQ{};
  auto both = request(ps::Policy::committed_input_native_depth); both.constraint = ps::TupleIndexSlotLimit{"31"};
  const auto baseline = complete(ps::select(snapshot, source, both, facts));
  depth_oracle(assessment(baseline, pr::Policy::committed_input_native_depth));
  slot_oracle(assessment(baseline, pr::Policy::tuple_index_slots));
  check(baseline.assessments().size() == 2 && baseline.usage().active_nanoseconds == 0 &&
      baseline.preparation_timing() == ps::PreparationTiming::unmeasured, "C05 complete untimed dual assessment");
  for (const auto& dimension : dimensions) {
    std::uint64_t incremental = facts.preparation_usage().*dimension.used;
    for (const auto& item : baseline.assessments()) {
      check(item.result.usage().*dimension.used >= facts.preparation_usage().*dimension.used,
          "C05 component lost preparation accounting");
      incremental += item.result.usage().*dimension.used - facts.preparation_usage().*dimension.used;
      check(item.result.request().limits.*dimension.cap <= both.limits.aggregate.*dimension.cap,
          "C05 component received a fresh full grant");
    }
    check(baseline.usage().*dimension.used >= incremental, "C05 missing component incremental work");
    const auto used = baseline.usage().*dimension.used;
    if (!used) continue;
    auto exact = both; exact.limits.aggregate.*dimension.cap = used;
    const auto passed = complete(ps::select(snapshot, source, exact, facts)); same_choice(baseline, passed);
    check(passed.usage().*dimension.used == used, "C05 exact cap changed accounting");
    --(exact.limits.aggregate.*dimension.cap);
    const auto failed = ps::select(snapshot, source, exact, facts);
    check(!failed.selection && failed.stop == ps::Stop::resource_limit, "C05 one-under aggregate cap fell back/published");
    same_choice(baseline, complete(ps::select(snapshot, source, both, facts)));
  }
  for (const auto which : {0U, 1U}) {
    auto small = both;
    if (which == 0) small.limits.aggregate.candidates = snapshot.candidate_count() - 1;
    else small.limits.aggregate.score_bits = 1;
    const auto attempt = ps::select(snapshot, source, small, facts);
    check(!attempt.selection && attempt.stop == ps::Stop::resource_limit, "C05 candidate/bit stop activated fallback");
  }
  // First DirectCQ construction has no pre-existing identity DOM. Its known
  // source and newly created public identity/compiled payload remain capped.
  const auto height = request(ps::Policy::height_only);
  const auto direct = complete(ps::select(snapshot, source, height));
  for (const auto dimension : {dimensions[3], dimensions[4], dimensions[5]}) {
    auto exact = height; exact.limits.aggregate.*dimension.cap = direct.usage().*dimension.used;
    same_choice(direct, complete(ps::select(snapshot, source, exact)));
    --(exact.limits.aggregate.*dimension.cap);
    const auto stopped = ps::select(snapshot, source, exact);
    check(!stopped.selection && stopped.stop == ps::Stop::resource_limit, "C05 first DirectCQ payload/native cap ignored");
  }
  constexpr std::string_view maximum = "13407807929942597099574024998205846127479365820592393377723561443721764030073546976801874298166903427690031858186486050853753882811946569946433649006084095";
  auto cap = both; cap.constraint = ps::TupleIndexSlotLimit{std::string(maximum)};
  const auto wide_cap = complete(ps::select(snapshot, source, cap, facts));
  check(c02_test::shape(wide_cap.selected().tree()) == 1, "C05 512-bit cap narrowed");
  for (const auto& invalid : std::vector<std::string>{"", "00", "+1", "-1", " 1", "1 ", "1.0", std::string(maximum.substr(0, maximum.size() - 1)) + "6", std::string(156, '9')}) {
    cap.constraint = ps::TupleIndexSlotLimit{invalid};
    check(ps::select(snapshot, source, cap, facts).stop == ps::Stop::invalid_request, "C05 noncanonical/out-of-domain cap accepted");
  }
  auto timed = both; timed.limits.aggregate.active_time = std::chrono::hours(1);
  const auto timed_asof = complete(ps::select(snapshot, source, timed, facts)); same_choice(baseline, timed_asof);
  check(timed_asof.preparation_timing() == ps::PreparationTiming::unmeasured && timed_asof.usage().active_nanoseconds > 0,
      "C05 retrospectively measured old capture");
  const auto timed_current = complete(rs::select_current(snapshot, source, owner, timed));
  check(timed_current.selection().preparation_timing() == ps::PreparationTiming::measured &&
      timed_current.capture().inputs().preparation_usage().active_nanoseconds > 0 &&
      timed_current.selection().usage().active_nanoseconds >= timed_current.capture().inputs().preparation_usage().active_nanoseconds,
      "C05 current timing lost preparation");
  auto exhausted_time = height;
  exhausted_time.limits.aggregate.active_time = std::chrono::nanoseconds(timed_current.capture().inputs().preparation_usage().active_nanoseconds);
  const auto exhausted = ps::select(snapshot, source, exhausted_time, timed_current.capture().inputs());
  check(!exhausted.selection && exhausted.stop == ps::Stop::resource_limit && exhausted.resource == ps::Resource::active_time &&
      exhausted.usage == timed_current.capture().inputs().preparation_usage(), "C05 carried exact time ceiling was reset");
  exhausted_time.limits.aggregate.active_time = std::chrono::nanoseconds(0);
  check(ps::select(snapshot, source, exhausted_time).resource == ps::Resource::active_time, "C05 zero time cap ignored");
  exhausted_time.limits.aggregate.active_time = std::chrono::nanoseconds(-1);
  check(ps::select(snapshot, source, exhausted_time).stop == ps::Stop::invalid_request, "C05 negative time accepted");
  std::cout << "C05 aggregate exact/one-under, first-source admission, finite native work and optional timing contracts passed\n";
} catch (const std::exception& error) { std::cerr << error.what() << '\n'; return 1; } }
